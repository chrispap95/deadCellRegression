Float_t jackknife_ver2(TString filein, int En, int nbins, float alpha = 1){
    TFile* fin = TFile::Open(filein);
    TTree* t1 = dynamic_cast< TTree* >(fin->Get("t1"));
    Float_t rechitsum, truth, regression, event;
    t1->SetBranchAddress("MLrechitsum",&rechitsum);
    t1->SetBranchAddress("MLdead",&truth);
    t1->SetBranchAddress("MLevent",&event);
    t1->SetBranchAddress("regression",&regression);

    TH1F* h1 = new TH1F("h1","h1",nbins,En*0.3,En*1.5);
    int n = t1->GetEntries();
    Float_t event_tmp;
    Float_t truth_sum = 0;
    for(int i = 0; i < n; ++i){
        t1->GetEntry(i);
        cout << event << endl;
        if(i == 0) {
            event_tmp = event;
        }
        if(event_tmp != event) {
            h1->Fill(rechitsum+truth_sum);
            truth_sum = truth;
            event_tmp = event;
        }else{
            truth_sum += truth;
        }
    }

/*
 *        TH1F* htemp2 = new TH1F("htemp2","h1",nbins,-10,10);
 *        TF1* f1 = new TF1("f1","gaus(0)",-10,10);
 *        TF1* f2 = new TF1("f2","gaus(0)",-10,10);
 *        f1->SetParameters(1,-4,2);
 *        f2->SetParameters(1,4,2);
 *        htemp2->FillRandom("f1",10000);
 *        htemp2->FillRandom("f2",10000);
*/

    if (nbins == 100) h1->Draw();

    Float_t n_tot = h1->GetEntries(); //total number of datapoints
    Float_t delta = h1->GetBinWidth(1); //bin width
    Float_t lhd = 0;
    for(int i = 1; i<=nbins; ++i){
        if(h1->GetBinContent(i)!=0) {
            lhd+=h1->GetBinContent(i)*TMath::Log(h1->GetBinContent(i)+alpha-1);
        }
    }
    lhd-=n_tot*TMath::Log(delta*(n_tot+alpha*nbins));
    return lhd;
}
