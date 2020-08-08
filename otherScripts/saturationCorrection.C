{
    // Create recHit spectrum histogram
    TCanvas* c = new TCanvas("c","c",1000,800);
    Float_t binWidth = 0.5;
    Float_t saturation1 = 27.775;
    Float_t saturation2 = 41.38;
    Int_t nbins = 280;
    Float_t xmax = binWidth*nbins;
    if(1){
        xmax=66;
        binWidth=0.4;
        nbins=(int)(xmax/binWidth);
    }
    TH1F* h = new TH1F("h","recHit spectrum;recHit[GeV];Hits",nbins,0,xmax);
    //TF1* f = new TF1("f","[0]*x*exp([1]*x)");
    //f->SetParameters(1,-1);
    //f->SetParLimits(1,0,-100000000);
    //TF1* f = new TF1("f","[0]+[1]/x+[2]/pow(x,2)+[3]/pow(x,3)+[4]/pow(x,4)");
    //TF1* f = new TF1("f","[0]+[1]/x+[2]/pow(x,2)+[3]/pow(x,3)+[4]/pow(x,4)+[5]/pow(x,5)");
    TF1* f = new TF1("f","[0]+[1]/x+[2]/pow(x,2)+[3]/pow(x,3)+[4]/pow(x,4)+[5]/pow(x,5)+[6]/pow(x,6)");
    f->SetParLimits(0,-10000,10000);
    f->SetParLimits(1,-10000,10000);
    f->SetParLimits(2,-10000,10000);
    f->SetParLimits(3,-10000,10000);
    f->SetParLimits(4,-10000,10000);
    f->SetParLimits(5,-10000,10000);
    f->SetParLimits(6,-10000,10000);
    //TF1* f = new TF1("f","[0]+[1]/x+[2]/pow(x,2)+[3]/pow(x,3)+[4]/pow(x,4)+[5]/pow(x,5)+[6]/pow(x,6)+[7]/pow(x,7)");
    c->SetLogy();
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(1);

    // Loop over data and populate histogram
    TFile* fin = TFile::Open("data/cmssw/EvaluationSamples/out_E750Eta1p7_df07.root");
    TTree* t1 = dynamic_cast< TTree* >(fin->Get("t1"));
    Float_t recHit;
    t1->SetBranchAddress("MLdead",&recHit);
    int n = t1->GetEntries();
    int cr1 = 0;
    int cr2 = 0;
    for(int i = 0; i <= n; ++i){
        t1->GetEntry(i);
        h->Fill(recHit);
        if(recHit>saturation1-0.01 && recHit<saturation1+0.01) cr1++;
        if(recHit>saturation2-0.02 && recHit<saturation2+0.02) cr2++;

    }

    // Calculate starting x for second histogram
    Int_t nlim = (int)(saturation1/binWidth)+1;
    Float_t xlim = (nlim-1)*binWidth;

    // Plot and fit histogram
    h->Draw();
    h->Fit("f","0","",binWidth/2.,saturation1-binWidth);
    f->SetRange(binWidth/2.,xmax);
    f->Draw("same");
    cr1-=f->Eval(saturation1);

    // Calculate correction histogram
    Int_t nbins2 = (int)(xmax-xlim)/binWidth;
    TH1F* hcr1 = new TH1F("hcr1","recHit spectrum",nbins2,xlim,xmax);
    hcr1->FillRandom("f",cr1);
    hcr1->SetBinContent(1,f->Eval(saturation1));
    for (int i = nlim+1; i <= nbins; ++i) {
        //if ((i-nlim-1)*binWidth<saturation2-2*binWidth || (i-nlim)*binWidth>saturation2+2*binWidth) {
            hcr1->SetBinContent(i-nlim,hcr1->GetBinContent(i-nlim)+h->GetBinContent(i));
        //}
    }
    hcr1->SetLineColor(kGreen);
    hcr1->Draw("same");

    cout << "|======== Calculations =========|\n"
         << "| nbins  \t=\t " << nbins  << "\t|\n"
         << "| xmax   \t=\t " << xmax   << "\t|\n"
         << "| nlim   \t=\t " << nlim   << "\t|\n"
         << "| xlim   \t=\t " << xlim   << "\t|\n"
         << "| cr1    \t=\t " << cr1    << "\t|\n"
         << "| cr2    \t=\t " << cr2    << "\t|\n"
         << "| nbins2 \t=\t " << nbins2 << "\t|\n"
         << "|===============================|\n";
}
