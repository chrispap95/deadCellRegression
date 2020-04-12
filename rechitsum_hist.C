TH1F* rechitsum_hist(int En, int df, int bins, int range, int correction){
    TString filename = "";
    if(df) {
        filename = "data/cmssw/RegressionResults/flatRegressionResult_"+to_string(En)+"GeV_d0"+to_string(df)+"0_excludeDead2.root";
    }else {
        filename = "data/cmssw/RegressionResults/flatRegressionResult_"+to_string(En)+"GeV_d010_excludeDead2.root";
    }
    TFile* fin = TFile::Open(filename);
    TTree* t1 = dynamic_cast< TTree* >(fin->Get("t1"));
    Float_t rechitsum, truth, regression, event, nup, ndown;
    Float_t  n1,  n2,  n3,  n4,  n5,  n6;
    Float_t un1, un2, un3, un4, un5, un6;
    Float_t dn1, dn2, dn3, dn4, dn5, dn6;
    t1->SetBranchAddress("MLrechitsum",&rechitsum);
    t1->SetBranchAddress("MLdead",&truth);
    t1->SetBranchAddress("MLevent",&event);
    t1->SetBranchAddress("MLnup",&nup);
    t1->SetBranchAddress("MLndown",&ndown);
    t1->SetBranchAddress("regression",&regression);
    t1->SetBranchAddress("MLn1" ,&n1);
    t1->SetBranchAddress("MLn2" ,&n2);
    t1->SetBranchAddress("MLn3" ,&n3);
    t1->SetBranchAddress("MLn4" ,&n4);
    t1->SetBranchAddress("MLn5" ,&n5);
    t1->SetBranchAddress("MLn6" ,&n6);
    t1->SetBranchAddress("MLun1",&un1);
    t1->SetBranchAddress("MLun2",&un2);
    t1->SetBranchAddress("MLun3",&un3);
    t1->SetBranchAddress("MLun4",&un4);
    t1->SetBranchAddress("MLun5",&un5);
    t1->SetBranchAddress("MLun6",&un6);
    t1->SetBranchAddress("MLdn1",&dn1);
    t1->SetBranchAddress("MLdn2",&dn2);
    t1->SetBranchAddress("MLdn3",&dn3);
    t1->SetBranchAddress("MLdn4",&dn4);
    t1->SetBranchAddress("MLdn5",&dn5);
    t1->SetBranchAddress("MLdn6",&dn6);

    TString histname = ";recHitSum [GeV];Entries";
    TH1F* h1 = new TH1F("h1",histname,bins,160,230);
    int n = t1->GetEntries();
    Float_t event_tmp;
    Float_t rechitsum_truth  = 0;
    Float_t rechitsum_aver   = 0;
    Float_t rechitsum_LSaver = 0;
    Float_t rechitsum_MLregr = 0;
    for(int i = 0; i <= n; ++i){
        t1->GetEntry(i);

        Float_t layer_up = un1 + un2 + un3 + un4 + un5 + un6 + nup;
        Float_t layer_dn = dn1 + dn2 + dn3 + dn4 + dn5 + dn6 + ndown;
        Float_t layer_nn =  n1 +  n2 +  n3 +  n4 +  n5 + n6;
        float averLS = layer_up/2.+layer_dn/2.-layer_nn;
        float aver = nup/2.+ndown/2.;
        if(i == 0) {
            event_tmp = event;
            rechitsum_truth  = rechitsum;
            rechitsum_aver   = rechitsum;
            rechitsum_LSaver = rechitsum;
            rechitsum_MLregr = rechitsum;
        }
        if(event_tmp != event) {
            if(!df) h1->Fill(rechitsum_truth);
            else {
                if(correction == 0) h1->Fill(rechitsum);
                else if(correction == 1) h1->Fill(rechitsum_aver);
                else if(correction == 2) h1->Fill(rechitsum_LSaver);
                else if(correction == 3) h1->Fill(rechitsum_MLregr);
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

    return h1;
}
