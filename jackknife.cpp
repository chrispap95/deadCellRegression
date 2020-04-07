void jackknife(int n_rebin){//TH1F* hist){
    /* range:
    ** 5.04  at 5 GeV
    ** 5.04  at 10 GeV
    ** 6.96  at 15 GeV
    ** 9.96  at 20 GeV
    ** 15.00 at 30 GeV
    ** 15.00 at 40 GeV
    ** 15.00 at 60 GeV
    ** 20.04 at 80 GeV
    ** 20.04 at 100 GeV
    */
    TH1F* hist = new TH1F("hist","test",1000,-10,10);
    hist->FillRandom("gaus",10000);
    Float_t energy = 0;
    Float_t range = 10;
    Float_t binWidth = hist->GetBinWidth(1);
    Int_t nbins = 2*range/binWidth;
    TH1F* htemp = new TH1F("htemp","htemp",nbins,energy-range,energy+range);
    for (int i = 1; i<=nbins; ++i) {
        Float_t eBin = hist->GetBinContent(hist->GetXaxis()->FindBin(energy-range+(i-1)*binWidth));
        htemp->SetBinContent(i,eBin);
    }
/*    TCanvas* c = new TCanvas("c","c",1);
    c->Divide(2,2);
    c->cd(1);
    hist->Draw();
    c->cd(2);
    htemp->Draw();

    c->cd(3);*/

    Float_t lhd = 0; //likelihood
    Float_t lhd_check = 1; //likelihood to compare
    //Int_t n_rebin = 1;
//    while(lhd < lhd_check) {
        lhd_check = lhd;
        TH1F* htemp2 = (TH1F*)hist->Clone();
        htemp2->SetBinContent(100,100);
        htemp2->Rebin(n_rebin);//n_rebin++);
        //htemp2->Draw();

        Float_t alpha = 1.0; //smoothing factor
        Float_t n_tot = htemp2->GetEntries(); //total number of datapoints
        Float_t delta = htemp2->GetBinWidth(1); //bin width

        for(int i = 1; i<=nbins; ++i){
            if(htemp2->GetBinContent(i)!=0) {
                lhd+=htemp2->GetBinContent(i)*TMath::Log(htemp2->GetBinContent(i)+alpha-1);
            }
        }
        lhd-=n_tot*TMath::Log(delta*(n_tot+alpha*nbins));
        cout << lhd << endl;
    //}
}
