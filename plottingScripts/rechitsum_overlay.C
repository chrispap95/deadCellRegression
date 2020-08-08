#include "rechitsum_hist.C"
#include "RootStyle.cc"

void rechitsum_overlay(){
    //set_root_style();
    //set_tdr_style();
    set_vasu_style();
    //setTDRStyle();

    TCanvas* c = new TCanvas("c","c",1);
    /*
    gStyle->SetOptStat(0);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    */

    TH1F* h0 = rechitsum_hist(200,0,100,50,0);
    TH1F* h5 = rechitsum_hist(200,5,100,50,0);
    TH1F* h5av = rechitsum_hist(200,5,100,50,1);
    TH1F* h5LSav = rechitsum_hist(200,5,100,50,2);
    TH1F* h5ML = rechitsum_hist(200,5,100,50,3);
    /*
    h1->GetXaxis()->SetTitleOffset(1.15);
    h1->GetXaxis()->SetTitleSize(0.044);
    h1->GetYaxis()->SetTitleSize(0.044);
    */

    h5->SetLineColor(kRed);
    h5av->SetLineColor(kMagenta);
    h5ML->SetLineColor(kGreen);
    h5LSav->SetLineColor(kYellow);
    h0->Draw();
    h5->Draw("same");
    h5av->Draw("same");
    h5LSav->Draw("same");
    h5ML->Draw("same");

    TLegend* legend = new TLegend(0.12,0.7,0.3,0.88);
    legend->SetBorderSize(0);
    legend->AddEntry(h0,"0% dead cells","l");
    legend->AddEntry(h5,"5% dead cells","l");
    legend->AddEntry(h5av,"5% dead cells + average corr.","l");
    legend->AddEntry(h5LSav,"5% dead cells + LS average corr.","l");
    legend->AddEntry(h5ML,"5% dead cells + ML corr.","l");
    legend->Draw();
}
