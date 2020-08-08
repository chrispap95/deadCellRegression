{
    TFile* f = TFile::Open("data/TrainingSamples/TrainingSamples_excludeDead2/out_E0to3000Eta1p7_df07.root");
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


    TFile* fout = new TFile("data/TrainingSamples/TrainingSamples_excludeDead2/out_E0to3000Eta1p7_df07_converted.root","RECREATE");
    TTree* t1 = new TTree("t1","sample");
    //Float_t previousLayer, nextLayer, sameLayer;
    //Float_t sum1, sum2, sum3, sum4, sum5, sum6;
    /*t1->Branch("previousLayer",&previousLayer,"previousLayer/F");
    t1->Branch("nextLayer",&nextLayer,"nextLayer/F");
    t1->Branch("sameLayer",&sameLayer,"sameLayer/F");
    t1->Branch("pnCells",&pnCells,"pnCells/F");*/
    t1->Branch("layer",&layer,"layer/F");
    t1->Branch("dead",&dead,"dead/F");
    /*t1->Branch("sum1",&sum1,"sum1/F");
    t1->Branch("sum2",&sum2,"sum2/F");
    t1->Branch("sum3",&sum3,"sum3/F");
    t1->Branch("sum4",&sum4,"sum4/F");
    t1->Branch("sum5",&sum5,"sum5/F");
    t1->Branch("sum6",&sum6,"sum6/F");*/
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

    for (int i = 0; i < t->GetEntries(); ++i) {
        t->GetEntry(i);
        /*previousLayer = dn1+dn2+dn3+dn4+dn5+dn6+ndown;
        nextLayer = un1+un2+un3+un4+un5+un6+nup;
        sameLayer = n1+n2+n3+n4+n5+n6;
        pnCells = nup+ndown;
        sum1 = dn1+un1+n1;
        sum2 = dn2+un2+n2;
        sum3 = dn3+un3+n3;
        sum4 = dn4+un4+n4;
        sum5 = dn5+un5+n5;
        sum6 = dn6+un6+n6;
        dead/=0.93;*/
        t1->Fill();
    }
    fout->cd();
    fout->Write();
    fout->Close();
}
