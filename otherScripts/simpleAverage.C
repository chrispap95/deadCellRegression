TGraph* simpleAverage(TGraph* gr){
    Int_t rebin = 10;
    Int_t n = gr->GetN();
    TGraph* gr_av = new TGraph(n/rebin-1);
    Float_t temp = 0;
    for(int i = 0; i <= n; i++){
        Double_t x, y;
        gr->GetPoint(i,x,y);
        temp+=y;
        if((i+1)%rebin==0) {
            gr_av->SetPoint(i/rebin-1,x,temp/rebin);
            temp=0;
        }
    }
    gr_av->SetMarkerStyle(8);
    gr_av->SetMarkerSize(0.5);
    return gr_av;
}
