/*
** Function that converts files for ML training and regression
**     - input: filename to process without the '.root' extension
**     - isTraining: if true then prepare the file for training
**     - prefix: in older code all the variables have the prefix "ML"
*/

void treeConverter(TString input, bool isTraining, TString prefix=""){
    TFile* f = TFile::Open(input+".root");
    TTree* t1 = dynamic_cast< TTree* >(f->Get("t1"));
    Float_t nup, ndown, dead, layer;
    Float_t waferU, waferV, cellU, cellV;
    Float_t ieta, iphi;
    Float_t n1, n2, n3, n4, n5, n6;
    Float_t un1, un2, un3, un4, un5, un6;
    Float_t dn1, dn2, dn3, dn4, dn5, dn6;
    Float_t event, rechitsum, thickness;
    t1->SetBranchAddress( prefix+"layer", &layer );
    t1->SetBranchAddress( prefix+"waferU", &waferU );
    t1->SetBranchAddress( prefix+"waferV", &waferV );
    t1->SetBranchAddress( prefix+"cellU", &cellU );
    t1->SetBranchAddress( prefix+"cellV", &cellV );
    t1->SetBranchAddress( prefix+"ieta", &ieta );
    t1->SetBranchAddress( prefix+"iphi", &iphi );
    t1->SetBranchAddress( prefix+"n1", &n1 );
    t1->SetBranchAddress( prefix+"n2", &n2 );
    t1->SetBranchAddress( prefix+"n3", &n3 );
    t1->SetBranchAddress( prefix+"n4", &n4 );
    t1->SetBranchAddress( prefix+"n5", &n5 );
    t1->SetBranchAddress( prefix+"n6", &n6 );
    t1->SetBranchAddress( prefix+"n7", &n7 );
    t1->SetBranchAddress( prefix+"n8", &n8 );
    t1->SetBranchAddress( prefix+"nup", &nup );
    t1->SetBranchAddress( prefix+"ndown", &ndown );
    t1->SetBranchAddress( prefix+"dead", &dead);
    t1->SetBranchAddress( prefix+"un1", &un1 );
    t1->SetBranchAddress( prefix+"un2", &un2 );
    t1->SetBranchAddress( prefix+"un3", &un3 );
    t1->SetBranchAddress( prefix+"un4", &un4 );
    t1->SetBranchAddress( prefix+"un5", &un5 );
    t1->SetBranchAddress( prefix+"un6", &un6 );
    t1->SetBranchAddress( prefix+"un7", &un7 );
    t1->SetBranchAddress( prefix+"un8", &un8 );
    t1->SetBranchAddress( prefix+"dn1", &dn1 );
    t1->SetBranchAddress( prefix+"dn2", &dn2 );
    t1->SetBranchAddress( prefix+"dn3", &dn3 );
    t1->SetBranchAddress( prefix+"dn4", &dn4 );
    t1->SetBranchAddress( prefix+"dn5", &dn5 );
    t1->SetBranchAddress( prefix+"dn6", &dn6 );
    t1->SetBranchAddress( prefix+"dn7", &dn7 );
    t1->SetBranchAddress( prefix+"dn8", &dn8 );
    t1->SetBranchAddress( prefix+"event", &event );
    t1->SetBranchAddress( prefix+"rechitsum", &rechitsum );
    t1->SetBranchAddress( prefix+"thickness", &thickness );

    TFile* fout = new TFile(input+"_converted.root","RECREATE");
    TTree* tree = new TTree("tree","sample");
    tree->Branch("layer",&layer,"layer/F");
    tree->Branch("n1",&n1,"n1/F");
    tree->Branch("n2",&n2,"n2/F");
    tree->Branch("n3",&n3,"n3/F");
    tree->Branch("n4",&n4,"n4/F");
    tree->Branch("n5",&n5,"n5/F");
    tree->Branch("n6",&n6,"n6/F");
    tree->Branch("n7",&n7,"n7/F");
    tree->Branch("n8",&n8,"n8/F");
    tree->Branch("dn1",&dn1,"dn1/F");
    tree->Branch("dn2",&dn2,"dn2/F");
    tree->Branch("dn3",&dn3,"dn3/F");
    tree->Branch("dn4",&dn4,"dn4/F");
    tree->Branch("dn5",&dn5,"dn5/F");
    tree->Branch("dn6",&dn6,"dn6/F");
    tree->Branch("dn7",&dn7,"dn7/F");
    tree->Branch("dn8",&dn8,"dn8/F");
    tree->Branch("un1",&un1,"un1/F");
    tree->Branch("un2",&un2,"un2/F");
    tree->Branch("un3",&un3,"un3/F");
    tree->Branch("un4",&un4,"un4/F");
    tree->Branch("un5",&un5,"un5/F");
    tree->Branch("un6",&un6,"un6/F");
    tree->Branch("un7",&un7,"un7/F");
    tree->Branch("un8",&un8,"un8/F");
    tree->Branch("nup",&nup,"nup/F");
    tree->Branch("ndown",&ndown,"ndown/F");
    tree->Branch("event",&event,"event/F");
    tree->Branch("thickness",&thickness,"thickness/F");
    tree->Branch("rechitsum",&rechitsum,"rechitsum/F");
    tree->Branch("dead",&dead,"dead/F");

    for (int i = 0; i < t->GetEntries(); ++i) {
        t1->GetEntry(i);
        /*
        ** If not training, keep all hits.
        ** If creating a training sample, reject the saturation region
        ** and only keep normal hits (not the buffer hits with layer = -1).
        */
        if (!isTraining) tree->Fill();
        else if (isTraining && layer > 0 && rechitsum < 700 && dead < 27.6) tree->Fill();
    }
    fout->cd();
    fout->Write();
    fout->Close();
}
