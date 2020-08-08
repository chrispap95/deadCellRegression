{
    TCanvas* c = new TCanvas("c","c",1);
    Float_t E_standalone[] = {
        10*2.82, 20*2.82, 40*2.82, 60*2.82, 100*2.82//,150*2.82,200*2.82
    };
    Float_t adq_aver_standalone[] = {
        0.165641, 0.228185, 0.36116, 0.46218, 0.643959//, 0.907093, 1.08439
    };
    Float_t adq_ML_standalone[] = {
        0.186505, 0.269452, 0.326703, 0.355838, 0.453029
    };
    Float_t adq_ML_lowEn_standalone[] = {
        0.227413, 0.26873, 0.378884, 0.573759, 1.05534
    };
    Float_t E_cmssw[] = {
        5, 10, 15, 20, 30, 40, 60, 80, 100
    };
    Float_t adq_aver_cmssw[] = {
        0.059487, 0.0768011, 0.0941982, 0.106819, 0.120149, 0.143355, 0.178331, 0.211646, 0.229316
    };
    Float_t adq_ML_cmssw[] = {
        0.0550125, 0.071419, 0.086776, 0.0961538, 0.100117, 0.114584, 0.124953, 0.152837, 0.153855
    };

    TGraph* gr1 = new TGraph(5,E_standalone,adq_aver_standalone);
    TGraph* gr2 = new TGraph(5,E_standalone,adq_ML_standalone);
    TGraph* gr3 = new TGraph(9,E_cmssw,adq_aver_cmssw);
    TGraph* gr4 = new TGraph(9,E_cmssw,adq_ML_cmssw);
    TGraph* gr5 = new TGraph(5,E_standalone,adq_ML_lowEn_standalone);
    gr3->SetMarkerColor(kRed);
    gr3->SetLineColor(kRed);
    gr2->SetMarkerColor(kGreen);
    gr2->SetLineColor(kGreen);
    gr4->SetMarkerColor(kMagenta);
    gr4->SetLineColor(kMagenta);
    gr5->SetMarkerColor(kCyan);
    gr5->SetLineColor(kCyan);

    TMultiGraph* mgr = new TMultiGraph();
    mgr->Add(gr1);
    mgr->Add(gr2);
    mgr->Add(gr3);
    mgr->Add(gr4);
    mgr->Add(gr5);

    mgr->SetTitle("Average quadratic deviation VS True energy;E [GeV];#sqrt{#sum#frac{(RecHit_{true}-RecHit_{av})^{2}}{N}}");
    mgr->GetXaxis()->SetTitleSize(0.046);
    mgr->GetYaxis()->SetTitleSize(0.04);
    mgr->GetYaxis()->SetTitleOffset(1.3);
    mgr->Draw("ALP*");

    TLegend* lg = new TLegend(0.15, 0.55, 0.6, 0.88);
    lg->SetBorderSize(0);
    lg->AddEntry(gr1,"standalone average","l");
    lg->AddEntry(gr2,"standalone ML","l");
    lg->AddEntry(gr5,"standalone ML (train <100 GeV)","l");
    lg->AddEntry(gr3,"CMSSW average","l");
    lg->AddEntry(gr4,"CMSSW ML","l");
    lg->Draw();
}
