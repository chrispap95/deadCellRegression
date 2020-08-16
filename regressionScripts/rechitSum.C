std::vector<double> rechitSum(int En, int df, int range, int bins = 100,
                              double fit_cut = 1.5, TString method = "none"){
  // Get the data file and input the TTree
  // If working on 0% use the 1% file
  TString filename = "";
  TString inputPath = "root://cmseos.fnal.gov//store/user/ksturge/DeadCellsSamples_correct/EvaluationSamples/";
  if(df) {
    filename = inputPath+"out_E"+(TString)to_string(En)+"Eta1p62_df0"+(TString)to_string(df)+".root";
  }else {
    filename = inputPath+"out_E"+(TString)to_string(En)+"Eta1p62_df01.root";
  }
  TFile* fin = TFile::Open(filename);
  TTree* t1 = dynamic_cast< TTree* >(fin->Get("t1"));
  Float_t rechitsum, truth, regression, event, nup, ndown;
  Float_t  n1,  n2,  n3,  n4,  n5,  n6;
  Float_t un1, un2, un3, un4, un5, un6;
  Float_t dn1, dn2, dn3, dn4, dn5, dn6;
  t1->SetBranchAddress("rechitsum",&rechitsum);
  t1->SetBranchAddress("dead",&truth);
  t1->SetBranchAddress("event",&event);
  t1->SetBranchAddress("nup",&nup);
  t1->SetBranchAddress("ndown",&ndown);
  t1->SetBranchAddress("regression",&regression);
  t1->SetBranchAddress("n1" ,&n1);
  t1->SetBranchAddress("n2" ,&n2);
  t1->SetBranchAddress("n3" ,&n3);
  t1->SetBranchAddress("n4" ,&n4);
  t1->SetBranchAddress("n5" ,&n5);
  t1->SetBranchAddress("n6" ,&n6);
  t1->SetBranchAddress("un1",&un1);
  t1->SetBranchAddress("un2",&un2);
  t1->SetBranchAddress("un3",&un3);
  t1->SetBranchAddress("un4",&un4);
  t1->SetBranchAddress("un5",&un5);
  t1->SetBranchAddress("un6",&un6);
  t1->SetBranchAddress("dn1",&dn1);
  t1->SetBranchAddress("dn2",&dn2);
  t1->SetBranchAddress("dn3",&dn3);
  t1->SetBranchAddress("dn4",&dn4);
  t1->SetBranchAddress("dn5",&dn5);
  t1->SetBranchAddress("dn6",&dn6);

  // Loop over dead cell entries
  TString histname = "single gamma "+to_string(En)+"GeV;recHitSum [GeV];Entries";
  TH1F* h1 = new TH1F("h1",histname,bins,En-range,En+range);
  int n = t1->GetEntries();
  Float_t event_tmp;
  Float_t rechitsum_truth  = 0;
  Float_t rechitsum_aver   = 0;
  Float_t rechitsum_LSaver = 0;
  Float_t rechitsum_MLregr = 0;
  for(int i = 0; i <= n; ++i){
    t1->GetEntry(i);

    // Assign 0 rechit to dead neighbors
    if (nup < 0) nup = 0;
    if (ndown < 0) ndown = 0;
    if (n1 < 0) n1 = 0;
    if (n2 < 0) n2 = 0;
    if (n3 < 0) n3 = 0;
    if (n4 < 0) n4 = 0;
    if (n5 < 0) n5 = 0;
    if (n6 < 0) n6 = 0;
    if (un1 < 0) un1 = 0;
    if (un2 < 0) un2 = 0;
    if (un3 < 0) un3 = 0;
    if (un4 < 0) un4 = 0;
    if (un5 < 0) un5 = 0;
    if (un6 < 0) un6 = 0;
    if (dn1 < 0) dn1 = 0;
    if (dn2 < 0) dn2 = 0;
    if (dn3 < 0) dn3 = 0;
    if (dn4 < 0) dn4 = 0;
    if (dn5 < 0) dn5 = 0;
    if (dn6 < 0) dn6 = 0;

    // Calculate for LS average
    Float_t layer_up = un1 + un2 + un3 + un4 + un5 + un6 + nup;
    Float_t layer_dn = dn1 + dn2 + dn3 + dn4 + dn5 + dn6 + ndown;
    Float_t layer_nn =  n1 +  n2 +  n3 +  n4 +  n5 + n6;
    float averLS = layer_up/2.+layer_dn/2.-layer_nn;

    // Calculate for average
    float aver = nup/2.+ndown/2.;

    // Assign new rechitsum value when changing event
    // If the event remains the same then only add correction ot the rechitsum
    if(i == 0) {
      event_tmp = event;
      rechitsum_truth  = rechitsum;
      rechitsum_aver   = rechitsum;
      rechitsum_LSaver = rechitsum;
      rechitsum_MLregr = rechitsum;
    }
    if(event_tmp != event) {
      if (df) {
        if (method == "none") {
          h1->Fill(rechitsum);
        }
        else if (method == "MLregr") {
          h1->Fill(rechitsum_MLregr);
        }
        else if (method == "LSaver") {
          h1->Fill(rechitsum_LSaver);
        }
        else if (method == "aver") {
          h1->Fill(rechitsum_aver);
        }
        else {
            cerr << "Something bad happened. Method " + method + " not recognized!";
        }
      } else {
        // Only for 0% case
        h1->Fill(rechitsum_truth);
      }
      rechitsum_truth  =  rechitsum;
      rechitsum_truth  += truth;
      rechitsum_aver   =  rechitsum;
      rechitsum_aver   += aver;
      rechitsum_LSaver =  rechitsum;
      if(averLS > 0) rechitsum_LSaver += averLS;
      rechitsum_MLregr =  rechitsum;
      rechitsum_MLregr += regression;
      event_tmp = event;
    }else{
      rechitsum_truth  += truth;
      rechitsum_aver   += aver;
      if(averLS > 0)rechitsum_LSaver += averLS;
      rechitsum_MLregr += regression;
    }
  }

  // Draw, fit and export the result
  h1->Draw();
  h1->GetXaxis()->SetTitleOffset(1.2);
  h1->GetXaxis()->SetTitleSize(0.044);
  h1->GetYaxis()->SetTitleSize(0.044);
  TFitResultPtr r = h1->Fit("gaus","Sq","");
  r = h1->Fit("gaus","Sq","",r->Parameter(1)-fit_cut*r->Parameter(2),r->Parameter(1)+3*r->Parameter(2));

  std::vector<double> output_vector;
  double a0  = r->Parameter(0);
  double a1  = r->Parameter(1);
  double a2  = r->Parameter(2);
  double a0e = r->ParError(0);
  double a1e = r->ParError(1);
  double a2e = r->ParError(2);
  output_vector.push_back(a0);
  output_vector.push_back(a1);
  output_vector.push_back(a2);
  output_vector.push_back(a0e);
  output_vector.push_back(a1e);
  output_vector.push_back(a2e);

  return output_vector;
}
