/*
** Function that converts files for ML training and regression
**     - input: filename to process without the .root
**     - isTraining: if true then prepare the file for training
*/

void treeConverter(TString input, bool isTraining){
    TFile* f = TFile::Open(input+".root");
    TTree* t = dynamic_cast< TTree* >(f->Get("t1"));
    Float_t n1, n2, n3, n4, n5, n6, nup, ndown, dead, layer, pnCells, rechitsum;
    Float_t un1, un2, un3, un4, un5, un6;
    Float_t dn1, dn2, dn3, dn4, dn5, dn6;
    TString prefix = ""; // or for older code prefix = "ML"
    t->SetBranchAddress( prefix+"layer", &layer );
    t->SetBranchAddress( prefix+"n1", &n1 );
    t->SetBranchAddress( prefix+"n2", &n2 );
    t->SetBranchAddress( prefix+"n3", &n3 );
    t->SetBranchAddress( prefix+"n4", &n4 );
    t->SetBranchAddress( prefix+"n5", &n5 );
    t->SetBranchAddress( prefix+"n6", &n6 );
    t->SetBranchAddress( prefix+"nup", &nup );
    t->SetBranchAddress( prefix+"ndown", &ndown );
    t->SetBranchAddress( prefix+"dead", &dead);
    t->SetBranchAddress( prefix+"un1", &un1 );
    t->SetBranchAddress( prefix+"un2", &un2 );
    t->SetBranchAddress( prefix+"un3", &un3 );
    t->SetBranchAddress( prefix+"un4", &un4 );
    t->SetBranchAddress( prefix+"un5", &un5 );
    t->SetBranchAddress( prefix+"un6", &un6 );
    t->SetBranchAddress( prefix+"dn1", &dn1 );
    t->SetBranchAddress( prefix+"dn2", &dn2 );
    t->SetBranchAddress( prefix+"dn3", &dn3 );
    t->SetBranchAddress( prefix+"dn4", &dn4 );
    t->SetBranchAddress( prefix+"dn5", &dn5 );
    t->SetBranchAddress( prefix+"dn6", &dn6 );
    t->SetBranchAddress( prefix+"rechitsum", &rechitsum );

    TFile* fout = new TFile(input+"_converted.root","RECREATE");
    TTree* tree = new TTree("tree","sample");
    tree->Branch("layer",&layer,"layer/F");
    tree->Branch("n1",&n1,"n1/F");
    tree->Branch("n2",&n2,"n2/F");
    tree->Branch("n3",&n3,"n3/F");
    tree->Branch("n4",&n4,"n4/F");
    tree->Branch("n5",&n5,"n5/F");
    tree->Branch("n6",&n6,"n6/F");
    tree->Branch("dn1",&dn1,"dn1/F");
    tree->Branch("dn2",&dn2,"dn2/F");
    tree->Branch("dn3",&dn3,"dn3/F");
    tree->Branch("dn4",&dn4,"dn4/F");
    tree->Branch("dn5",&dn5,"dn5/F");
    tree->Branch("dn6",&dn6,"dn6/F");
    tree->Branch("un1",&un1,"un1/F");
    tree->Branch("un2",&un2,"un2/F");
    tree->Branch("un3",&un3,"un3/F");
    tree->Branch("un4",&un4,"un4/F");
    tree->Branch("un5",&un5,"un5/F");
    tree->Branch("un6",&un6,"un6/F");
    tree->Branch("nup",&nup,"nup/F");
    tree->Branch("ndown",&ndown,"ndown/F");
    tree->Branch("rechitsum",&rechitsum,"rechitsum/F");
    tree->Branch("dead",&dead,"dead/F");

    for (int i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        if (!isTraining) tree->Fill();
        else if (isTraining && layer > 0) tree->Fill();
    }
    fout->cd();
    fout->Write();
    fout->Close();
}
