{
    TFile* f = TFile::Open("data/training_sample_full_8samples.root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    Float_t n1, n2, n3, n4, n5, n6, nup, ndown, dead, layer, pnCells;
    Float_t un1, un2, un3, un4, un5, un6;
    Float_t dn1, dn2, dn3, dn4, dn5, dn6;
    t->SetBranchAddress( "MLlayer", &layer );
    t->SetBranchAddress( "MLn1", &n1 );
    t->SetBranchAddress( "MLn2", &n2 );
    t->SetBranchAddress( "MLn3", &n3 );
    t->SetBranchAddress( "MLn4", &n4 );
    t->SetBranchAddress( "MLn5", &n5 );
    t->SetBranchAddress( "MLn6", &n6 );
    t->SetBranchAddress( "MLnup", &nup );
    t->SetBranchAddress( "MLndown", &ndown );
    t->SetBranchAddress( "MLdead", &dead);
    t->SetBranchAddress( "MLun1", &un1 );
    t->SetBranchAddress( "MLun2", &un2 );
    t->SetBranchAddress( "MLun3", &un3 );
    t->SetBranchAddress( "MLun4", &un4 );
    t->SetBranchAddress( "MLun5", &un5 );
    t->SetBranchAddress( "MLun6", &un6 );
    t->SetBranchAddress( "MLdn1", &dn1 );
    t->SetBranchAddress( "MLdn2", &dn2 );
    t->SetBranchAddress( "MLdn3", &dn3 );
    t->SetBranchAddress( "MLdn4", &dn4 );
    t->SetBranchAddress( "MLdn5", &dn5 );
    t->SetBranchAddress( "MLdn6", &dn6 );


    TFile* fout = new TFile("data/converted_training_sample_full_8samples.root","RECREATE");
    TTree* t1 = new TTree("t1","sample");
    Float_t previousLayer, nextLayer, sameLayer;
    t1->Branch("previousLayer",&previousLayer,"previousLayer/F");
    t1->Branch("nextLayer",&nextLayer,"nextLayer/F");
    t1->Branch("sameLayer",&sameLayer,"sameLayer/F");
    t1->Branch("pnCells",&pnCells,"pnCells/F");
    t1->Branch("layer",&layer,"layer/F");
    t1->Branch("dead",&dead,"dead/F");

    for (int i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        previousLayer = dn1+dn2+dn3+dn4+dn5+dn6+ndown;
        nextLayer = un1+un2+un3+un4+un5+un6+nup;
        sameLayer = n1+n2+n3+n4+n5+n6;
        pnCells = nup+ndown;
        t1->Fill();
    }
    fout->cd();
    fout->Write();
    fout->Close();
}
