{
    //gStyle->SetOptStat(0);
    gStyle->SetOptFit(1111);

    TCanvas* c = new TCanvas("c","c",1300,500);
    c->Divide(2,1);
    c->cd(1);
    TFile* f = TFile::Open("training_sample_new.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    float dead;
    t->SetBranchAddress("MLdead",&dead);
    TH1F* h1 = new TH1F("h1","MLdead",50,0,40);

    for (long i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        if (dead > 0) h1->Fill(dead);
    }
    h1->Draw();
    TF1* f1 = new TF1("f1","[0]/x+[1]/pow(x,2)+[4]/pow(x,3)+[5]/pow(x,4)+[3]",0,40);
    f1->SetMinimum(0);
    h1->Fit("f1");

    double a0 = f1->GetParameter(0);
    double a1 = f1->GetParameter(1);
    double a2 = f1->GetParameter(2);
    double a3 = f1->GetParameter(3);
    double a4 = f1->GetParameter(4);
    double a5 = f1->GetParameter(5);

    TH1F* h2 = new TH1F("h1","weighted MLdead",50,0,40);
    for (long i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        double feval = a0/dead+a1/pow(dead,2)+a4/pow(dead,3)+a5/pow(dead,4)+a3;
        if (dead > 0 && dead < 30) h2->Fill(dead,1/feval);
    }
    c->cd(2);
    h2->Draw();
    //h2->Fit("pol0");
    cout << "\n\n" << h2->GetMaximum() << " " << h2->GetMinimum() << endl;
}
