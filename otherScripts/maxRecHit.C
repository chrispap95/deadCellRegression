{
    Float_t energy[] = {     5,   10,   15,   20,  30,    40,   60,   80, 100,  140,  200,  280,  400,  550, 750, 1000,1400,2000,2800};
    Float_t max_recHit[] = {   0.9, 1.37, 1.75, 2.17, 3.02, 3.63, 5.24, 6.45, 8.2,11.22,14.67,19.81,27.48,   35, 44};
    Float_t max_simHit[] = {0.0036,0.007,0.009,0.011,0.011,0.012,0.016,0.017,0.02,0.025,0.037,0.045,0.063,0.085,0.12,0.145, 0.2,0.28,0.35};
    Float_t simHitsSum[17] =     {0.0275394,0.0652204,0.105804,0.143022,0.220462,0.298214,0.448014,0.594486,0.762748,1.05681,1.52212,2.14624,3.09057,4.19154,5.78214,7.73284,10.9172};
    Float_t simHitsSum_gauss[] = {0.0375,0.081,0.1245,0.158,0.231,0.324,0.474,0.648,0.81,1.134,1.62,2.268,3.24,4.455};
    Float_t simHitsSumRatio[15];
    Float_t simHitsSumRatio_gauss[15];
    Float_t max_ratio[15];
    for (int i = 0; i < 15; ++i){
        max_ratio[i] = max_simHit[i]/energy[i];
        simHitsSumRatio_gauss[i] = simHitsSum_gauss[i]/energy[i];
    }

    TCanvas* c = new TCanvas("c","c",1000,800);
    TGraph* gr = new TGraph(14,energy,simHitsSumRatio_gauss);
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    gr->SetTitle("Most probable simHit ratio to E;E[GeV];#frac{most probable SimHit}{Energy}");
    //gr->SetTitle("Most probable simHit vs E;E[GeV];most probable SimHit");
    //c->SetLogy();
    //c->SetLogx();
    gr->Draw("AP");

    //TF1* f = new TF1("f","[0]+[1]*pow(x,[2])");
    //TF1* f = new TF1("f","[0]+[1]/x");
    //TF1* f = new TF1("f","[0]+[1]/pow(x,1)+[2]/pow(x,2)");
    //TF1* f = new TF1("f","[0]+[1]*x");
    gr->Fit("pol1","","");

    /*cout << "550GeV:  " << f->Eval(max_simHit[13]) << "\n"
         << "750GeV:  "  << f->Eval(max_simHit[14]) << "\n"
         << "1000GeV:  " << f->Eval(max_simHit[15]) << "\n"
         << "1400GeV:  " << f->Eval(max_simHit[16]) << "\n"
         << "2000GeV:  " << f->Eval(max_simHit[17]) << "\n"
         << "2800GeV:  " << f->Eval(max_simHit[18]) << "\n";*/
}
