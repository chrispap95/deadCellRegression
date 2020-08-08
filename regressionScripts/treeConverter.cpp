void treeConverter(TString input){
    TFile* f = TFile::Open(input+".root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    Float_t n1, n2, n3, n4, n5, n6, nup, ndown, dead, layer, pnCells, rechitsum;
    Float_t un1, un2, un3, un4, un5, un6;
    Float_t dn1, dn2, dn3, dn4, dn5, dn6;
    t->SetBranchAddress( "layer", &layer );
    t->SetBranchAddress( "n1", &n1 );
    t->SetBranchAddress( "n2", &n2 );
    t->SetBranchAddress( "n3", &n3 );
    t->SetBranchAddress( "n4", &n4 );
    t->SetBranchAddress( "n5", &n5 );
    t->SetBranchAddress( "n6", &n6 );
    t->SetBranchAddress( "nup", &nup );
    t->SetBranchAddress( "ndown", &ndown );
    t->SetBranchAddress( "dead", &dead);
    t->SetBranchAddress( "un1", &un1 );
    t->SetBranchAddress( "un2", &un2 );
    t->SetBranchAddress( "un3", &un3 );
    t->SetBranchAddress( "un4", &un4 );
    t->SetBranchAddress( "un5", &un5 );
    t->SetBranchAddress( "un6", &un6 );
    t->SetBranchAddress( "dn1", &dn1 );
    t->SetBranchAddress( "dn2", &dn2 );
    t->SetBranchAddress( "dn3", &dn3 );
    t->SetBranchAddress( "dn4", &dn4 );
    t->SetBranchAddress( "dn5", &dn5 );
    t->SetBranchAddress( "dn6", &dn6 );
    t->SetBranchAddress( "rechitsum", &rechitsum );

    TFile* fout = new TFile(input+"_converted.root","RECREATE");
    TTree* t1 = new TTree("t1","sample");
    t1->Branch("n1",&n1,"n1/F");
    t1->Branch("n2",&n2,"n2/F");
    t1->Branch("n3",&n3,"n3/F");
    t1->Branch("n4",&n4,"n4/F");
    t1->Branch("n5",&n5,"n5/F");
    t1->Branch("n6",&n6,"n6/F");
    t1->Branch("dn1",&dn1,"dn1/F");
    t1->Branch("dn2",&dn2,"dn2/F");
    t1->Branch("dn3",&dn3,"dn3/F");
    t1->Branch("dn4",&dn4,"dn4/F");
    t1->Branch("dn5",&dn5,"dn5/F");
    t1->Branch("dn6",&dn6,"dn6/F");
    t1->Branch("un1",&un1,"un1/F");
    t1->Branch("un2",&un2,"un2/F");
    t1->Branch("un3",&un3,"un3/F");
    t1->Branch("un4",&un4,"un4/F");
    t1->Branch("un5",&un5,"un5/F");
    t1->Branch("un6",&un6,"un6/F");
    t1->Branch("nup",&nup,"nup/F");
    t1->Branch("ndown",&ndown,"ndown/F");
    t1->Branch("rechitsum",&rechitsum,"rechitsum/F");

    for (int i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        t1->Fill();
    }
    fout->cd();
    fout->Write();
    fout->Close();
}
