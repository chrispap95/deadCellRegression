#include "simpleAverage.C"
#include "jackknife_ver2.C"

void likelihood(int En, int df){
    Int_t nbin = 500;
    Float_t lhd_1p0[500];
    Float_t bins[500];

    TString filein = "data/cmssw/RegressionResults/flatRegressionResult_"+to_string(En)+"GeV_d0"+to_string(df)+"0.root";

    Float_t lhd_max = jackknife_ver2(filein,En,10);
    Int_t n_max = 10;

    for(int n = 10; n < nbin+10; n++){
        bins[n-10] = n;
        lhd_1p0[n-10] = jackknife_ver2(filein,En,n);
        if (lhd_1p0[n-10]>lhd_max) {
            lhd_max=lhd_1p0[n-10];
            n_max = n;
        }
    }

    //TCanvas* c = new TCanvas("c","c",1);
    TMultiGraph* mg = new TMultiGraph();
    TGraph* gr_1p0 = new TGraph(nbin,bins,lhd_1p0);

    //mg->Add(gr_1p0);
    //mg->Draw("a");
    //mg->SetTitle(filein+";bins;Log(L)");
    //c->SetLeftMargin(0.13);
    //TString s_out = "trainedNNs/Plots/likelihood/likelihood_"+to_string(En)+"GeV_d0"+to_string(df)+"0_nodead.pdf";
    //c->SaveAs(s_out);

    //c->Clear();
    TGraph* avr_1p0 = simpleAverage(gr_1p0);
    TMultiGraph* mavr = new TMultiGraph();
    //mavr->Add(avr_1p0);
    //mavr->SetTitle("simpleAverage - "+filein+";bins;Log(L)");
    //mavr->Draw("a");
    //s_out = "trainedNNs/Plots/likelihood/simpleAverage_"+to_string(En)+"GeV_d0"+to_string(df)+"0_nodead.pdf";
    //c->SaveAs(s_out);
    cout << lhd_max << ", " << n_max << endl;
}
