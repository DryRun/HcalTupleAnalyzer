#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"
#include "HFDigi.h"
#include "RBXMap.h"

void analysisClass::loop(){
  //--------------------------------------------------------------------------------
  // Declare HCAL tree(s)
  //--------------------------------------------------------------------------------

  HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
  int n_events = tuple_tree -> fChain -> GetEntries();
  std::cout << "n events = " << n_events << std::endl;

  //--------------------------------------------------------------------------------
  // Turn on/off branches
  //--------------------------------------------------------------------------------
  

  tuple_tree -> fChain -> SetBranchStatus("*"               , kFALSE);
  tuple_tree -> fChain -> SetBranchStatus("run", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("event", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("ls", kTRUE);

  tuple_tree->fChain->SetBranchStatus("HFDigiEta", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiPhi", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiRecEnergy", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiRecTime", 1);
  tuple_tree->fChain->SetBranchStatus("HFRecHitEnergy", 1);
  tuple_tree->fChain->SetBranchStatus("HFRecHitEta", 1);
  tuple_tree->fChain->SetBranchStatus("HFRecHitPhi", 1);
  tuple_tree->fChain->SetBranchStatus("HFRecHitTime", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiAllFC", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiEnergy", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiFC", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiGain", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiNomFC", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiPedFC", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiRCGain", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiDepth", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiElectronicsID", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiFiberIdleOffset", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiIEta", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiIPhi", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiPresamples", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiRawID", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiSize", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiSubdet", 1);
  tuple_tree->fChain->SetBranchStatus("HFRecHitAux", 1);
  tuple_tree->fChain->SetBranchStatus("HFRecHitDepth", 1);
  tuple_tree->fChain->SetBranchStatus("HFRecHitFlags", 1);
  tuple_tree->fChain->SetBranchStatus("HFRecHitHPDid", 1);
  tuple_tree->fChain->SetBranchStatus("HFRecHitIEta", 1);
  tuple_tree->fChain->SetBranchStatus("HFRecHitIPhi", 1);
  tuple_tree->fChain->SetBranchStatus("HFRecHitRBXid", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiADC", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiCapID", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiDV", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiER", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiFiber", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiFiberChan", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiLADC", 1);
  tuple_tree->fChain->SetBranchStatus("HFDigiRaw", 1);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRecTime", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiAllFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiEnergy", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiNomFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiPedFC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRCGain", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiDepth", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFiberIdleOffset", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIEta", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiIPhi", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiPresamples", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiSize", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiADC", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiCapID", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiDV", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiER", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFiber", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiFiberChan", kTRUE);
  tuple_tree -> fChain -> SetBranchStatus("HFDigiRaw", kTRUE);
  
  //--------------------------------------------------------------------------------
  // Declare and load RBX map
  //--------------------------------------------------------------------------------

  RBXMap map;
  //map.LoadFile("data/emaps/version_G_emap_all.txt");
  map.LoadFile ( "data/emaps/HCALmapHBEF_E.txt" );
  map.LoadFile ( "data/emaps/HCALmapHO_E.txt" );

  //--------------------------------------------------------------------------------
  // Make histograms
  //--------------------------------------------------------------------------------

  TH2F * h_hf_occupancy_NDV = makeTH2F ("hf_occupancy_NDV", 85, -42.5, 42.5, 72, 0.5, 72.5 );
  TH2F * h_hf_occupancy_ER  = makeTH2F ("hf_occupancy_ER" , 85, -42.5, 42.5, 72, 0.5, 72.5 );
  TH2F * h_hf_occupancy_CAP = makeTH2F ("hf_occupancy_CAP", 85, -42.5, 42.5, 72, 0.5, 72.5 );
  std::map<int, TH2F*> h_hf_digi_average_readings;
  std::map<int, TH2F*> h_hf_digi_average_energy;
  std::map<int, TH2F*> h_hf_digi_average_recHitTime ;
  std::map<int, TH2F*> h_hf_digi_average_presamples;
  std::map<int, TH2F*> h_hf_digi_average_electronicsId;
  std::map<int, TH2F*> h_hf_digi_average_rawId;
  std::map<int, TH2F*> h_hf_digi_average_fcTotal;
  std::map<int, TH2F*> h_hf_digi_average_adcTotal;
  std::map<int, TH2F*> h_hf_digi_average_time;
  std::map<int, TH2F*> h_hf_digi_average_time12;
  std::map<int, TH2F*> h_hf_digi_average_time34;
  std::map<int, TH2F*> h_hf_digi_average_charge12;
  std::map<int, TH2F*> h_hf_digi_average_charge34;
  std::map<int, TH2F*> h_hf_digi_average_isSignal;
  std::map<int, TH2F*> h_hf_digi_average_maxADC;
  std::map<int, std::map<int, TH2F*> > h_hf_digi_average_fc;
  std::map<int, std::map<int, TH2F*> > h_hf_digi_average_adc;
  std::map<int, std::map<int, TH2F*> > h_hf_digi_average_dv;
  std::map<int, std::map<int, TH2F*> > h_hf_digi_average_er;
  std::map<int, std::map<int, TH2F*> > h_hf_digi_average_capid;

  for (int depth = 1; depth <= 2; ++depth) {
    char hname[100];
    
    sprintf(hname, "h_hf_digi_average_readings_d%d", depth);
    h_hf_digi_average_readings[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

    sprintf(hname, "h_hf_digi_average_energy_d%d", depth);
    h_hf_digi_average_energy[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_recHitTime_d%d", depth);
    h_hf_digi_average_recHitTime [depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_presamples_d%d", depth);
    h_hf_digi_average_presamples[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_electronicsId_d%d", depth);
    h_hf_digi_average_electronicsId[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_rawId_d%d", depth);
    h_hf_digi_average_rawId[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_fcTotal_d%d", depth);
    h_hf_digi_average_fcTotal[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_adcTotal_d%d", depth);
    h_hf_digi_average_adcTotal[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_time_d%d", depth);
    h_hf_digi_average_time[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_time12_d%d", depth);
    h_hf_digi_average_time12[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_time34_d%d", depth);
    h_hf_digi_average_time34[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_charge12_d%d", depth);
    h_hf_digi_average_charge12[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_charge34_d%d", depth);
    h_hf_digi_average_charge34[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_isSignal_d%d", depth);
    h_hf_digi_average_isSignal[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
    
    sprintf(hname, "h_hf_digi_average_maxADC_d%d", depth);
    h_hf_digi_average_maxADC[depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

    for (int ts = 0; ts <= 3; ++ts) {
      sprintf(hname, "h_hf_digi_average_fc_d%d_ts%d", depth, ts);
      h_hf_digi_average_fc[depth][ts] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

      sprintf(hname, "h_hf_digi_average_adc_d%d_ts%d", depth, ts);
      h_hf_digi_average_adc[depth][ts] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

      sprintf(hname, "h_hf_digi_average_dv_d%d_ts%d", depth, ts);
      h_hf_digi_average_dv[depth][ts] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

      sprintf(hname, "h_hf_digi_average_er_d%d_ts%d", depth, ts);
      h_hf_digi_average_er[depth][ts] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

      sprintf(hname, "h_hf_digi_average_capid_d%d_ts%d", depth, ts);
      h_hf_digi_average_capid[depth][ts] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

    }
  }

  //--------------------------------------------------------------------------------
  // Loop
  //--------------------------------------------------------------------------------

  for (int i = 0; i < n_events; ++i) {
    
    tuple_tree -> GetEntry(i);
    if ( (i + 1) % 100 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;
    
    CollectionPtr hfDigis (new Collection(*tuple_tree, tuple_tree -> HFDigiIEta -> size()));
    int n_digis = hfDigis->GetSize();
    for (int i_digi = 0; i_digi < n_digis; ++i_digi) {
      HFDigi this_digi = hfDigis->GetConstituent<HFDigi>(i_digi);
      int ieta = this_digi.ieta();
      int iphi = this_digi.iphi();
      int depth = this_digi.depth();
      h_hf_digi_average_readings[depth]->Fill(ieta, iphi);
      h_hf_digi_average_energy[depth]->Fill(ieta, iphi, this_digi.energy());
      h_hf_digi_average_recHitTime [depth]->Fill(ieta, iphi, this_digi.recHitTime());
      h_hf_digi_average_presamples[depth]->Fill(ieta, iphi, this_digi.presamples());
      h_hf_digi_average_electronicsId[depth]->Fill(ieta, iphi, this_digi.electronicsId());
      h_hf_digi_average_rawId[depth]->Fill(ieta, iphi, this_digi.rawId());
      h_hf_digi_average_fcTotal[depth]->Fill(ieta, iphi, this_digi.fcTotal());
      h_hf_digi_average_adcTotal[depth]->Fill(ieta, iphi, this_digi.adcTotal());
      h_hf_digi_average_time[depth]->Fill(ieta, iphi, this_digi.time());
      h_hf_digi_average_time12[depth]->Fill(ieta, iphi, this_digi.time12());
      h_hf_digi_average_time34[depth]->Fill(ieta, iphi, this_digi.time34());
      h_hf_digi_average_charge12[depth]->Fill(ieta, iphi, this_digi.charge12());
      h_hf_digi_average_charge34[depth]->Fill(ieta, iphi, this_digi.charge34());
      h_hf_digi_average_isSignal[depth]->Fill(ieta, iphi, this_digi.isSignal());
      h_hf_digi_average_maxADC[depth]->Fill(ieta, iphi, this_digi.maxADC());
      for (int ts = 0; ts < this_digi.size(); ++ts) {
        h_hf_digi_average_fc[depth][ts]->Fill(ieta, iphi, this_digi.fc(ts));
        h_hf_digi_average_adc[depth][ts]->Fill(ieta, iphi, this_digi.adc(ts));
        h_hf_digi_average_dv[depth][ts]->Fill(ieta, iphi, this_digi.dv(ts));
        h_hf_digi_average_er[depth][ts]->Fill(ieta, iphi, this_digi.er(ts));
        h_hf_digi_average_capid[depth][ts]->Fill(ieta, iphi, this_digi.capid(ts));
      }
    }
  } // End loop over events
  for (int depth = 1; depth <= 2; ++depth) {
    h_hf_digi_average_readings[depth]->Scale(1. / n_events);
    h_hf_digi_average_energy[depth]->Scale(1. / n_events);
    h_hf_digi_average_recHitTime [depth]->Scale(1. / n_events);
    h_hf_digi_average_presamples[depth]->Scale(1. / n_events);
    h_hf_digi_average_electronicsId[depth]->Scale(1. / n_events);
    h_hf_digi_average_rawId[depth]->Scale(1. / n_events);
    h_hf_digi_average_fcTotal[depth]->Scale(1. / n_events);
    h_hf_digi_average_adcTotal[depth]->Scale(1. / n_events);
    h_hf_digi_average_time[depth]->Scale(1. / n_events);
    h_hf_digi_average_time12[depth]->Scale(1. / n_events);
    h_hf_digi_average_time34[depth]->Scale(1. / n_events);
    h_hf_digi_average_charge12[depth]->Scale(1. / n_events);
    h_hf_digi_average_charge34[depth]->Scale(1. / n_events);
    h_hf_digi_average_isSignal[depth]->Scale(1. / n_events);
    h_hf_digi_average_maxADC[depth]->Scale(1. / n_events);
    for (int ts = 0; ts <= 3; ++ts) {
      h_hf_digi_average_fc[depth][ts]->Scale(1. / n_events);
      h_hf_digi_average_adc[depth][ts]->Scale(1. / n_events);
      h_hf_digi_average_dv[depth][ts]->Scale(1. / n_events);
      h_hf_digi_average_er[depth][ts]->Scale(1. / n_events);
      h_hf_digi_average_capid[depth][ts]->Scale(1. / n_events);
    }
  }
}
