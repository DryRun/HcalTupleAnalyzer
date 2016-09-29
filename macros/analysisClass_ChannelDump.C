#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HFDigi.h"
#include "HBHEDigi.h"
#include "HODigi.h"
#include "RBXMap.h"

struct ChannelCoordinates {
	int ieta;
	int iphi;
	int depth;
};
bool operator<(const ChannelCoordinates& l, const ChannelCoordinates& r) {
     return (l.ieta<r.ieta || (l.ieta==r.ieta && l.iphi<r.iphi) || (l.ieta==r.ieta && l.iphi==r.iphi && l.depth<r.depth));
}

void analysisClass::loop(){

	int max_event_histograms = 200;
	std::vector<ChannelCoordinates> HBHE_channels;
	std::vector<ChannelCoordinates> HF_channels;
	std::vector<ChannelCoordinates> HO_channels;


	std::vector<ChannelCoordinates> interesting_HO_channels;
	interesting_HO_channels.push_back({-14, 67,4});
	interesting_HO_channels.push_back({-7, 68, 4});
	interesting_HO_channels.push_back({-6, 46, 4});
	interesting_HO_channels.push_back({15, 46, 4});
	interesting_HO_channels.push_back({15, 55, 4});
	interesting_HO_channels.push_back({5, 9, 4});
	interesting_HO_channels.push_back({-3, 26, 4});
	interesting_HO_channels.push_back({-3, 25, 4});
	interesting_HO_channels.push_back({-3, 24, 4});


	//--------------------------------------------------------------------------------
	// Declare HCAL tree(s)
	//--------------------------------------------------------------------------------

	HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
	int n_events = tuple_tree -> fChain -> GetEntries();
	std::cout << "n events = " << n_events << std::endl;

	//--------------------------------------------------------------------------------
	// Turn on/off branches
	//--------------------------------------------------------------------------------
	

	tuple_tree -> fChain -> SetBranchStatus("*", kFALSE);
	tuple_tree -> fChain -> SetBranchStatus("run", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("event", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("ls", kTRUE);

	tuple_tree->fChain->SetBranchStatus("HODigiEta", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiPhi", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiRecEnergy", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiRecTime", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiAllFC", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiEnergy", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiFC", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiGain", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiNomFC", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiPedFC", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiRCGain", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiDepth", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiElectronicsID", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiFiberIdleOffset", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiIEta", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiIPhi", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiPresamples", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiRawID", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiSize", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiSubdet", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiADC", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiCapID", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiDV", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiER", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiFiber", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiFiberChan", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiLADC", 1);
	tuple_tree->fChain->SetBranchStatus("HODigiRaw", 1);

	tuple_tree->fChain->SetBranchStatus("HBHEDigiEta", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiPhi", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiRecEnergy", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiRecTime", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiAllFC", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiEnergy", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiFC", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiGain", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiNomFC", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiPedFC", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiRCGain", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiDepth", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiElectronicsID", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiFiberIdleOffset", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiIEta", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiIPhi", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiPresamples", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiRawID", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiSize", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiSubdet", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiADC", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiCapID", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiDV", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiER", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiFiber", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiFiberChan", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiLADC", 1);
	tuple_tree->fChain->SetBranchStatus("HBHEDigiRaw", 1);

	tuple_tree->fChain->SetBranchStatus("HFDigiEta", 1);
	tuple_tree->fChain->SetBranchStatus("HFDigiPhi", 1);
	tuple_tree->fChain->SetBranchStatus("HFDigiRecEnergy", 1);
	tuple_tree->fChain->SetBranchStatus("HFDigiRecTime", 1);
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
	tuple_tree->fChain->SetBranchStatus("HFDigiADC", 1);
	tuple_tree->fChain->SetBranchStatus("HFDigiCapID", 1);
	tuple_tree->fChain->SetBranchStatus("HFDigiDV", 1);
	tuple_tree->fChain->SetBranchStatus("HFDigiER", 1);
	tuple_tree->fChain->SetBranchStatus("HFDigiFiber", 1);
	tuple_tree->fChain->SetBranchStatus("HFDigiFiberChan", 1);
	tuple_tree->fChain->SetBranchStatus("HFDigiLADC", 1);
	tuple_tree->fChain->SetBranchStatus("HFDigiRaw", 1);

	//--------------------------------------------------------------------------------
	// Make histograms
	//--------------------------------------------------------------------------------

	TH2F * h_occupancy_NDV = makeTH2F ("hf_occupancy_NDV", 85, -42.5, 42.5, 72, 0.5, 72.5 );
	TH2F * h_occupancy_ER  = makeTH2F ("hf_occupancy_ER" , 85, -42.5, 42.5, 72, 0.5, 72.5 );
	TH2F * h_occupancy_CAP = makeTH2F ("hf_occupancy_CAP", 85, -42.5, 42.5, 72, 0.5, 72.5 );
	std::vector<TString> digi_types;
	digi_types.push_back("HBHE");
	digi_types.push_back("HO");
	digi_types.push_back("HF");
	std::map<TString, std::map<int, TH2F*> > h_digi_average_readings;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_energy;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_recHitTime ;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_presamples;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_electronicsId;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_rawId;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_fcTotal;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_adcTotal;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_time;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_time12;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_time34;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_charge12;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_charge34;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_isSignal;
	std::map<TString, std::map<int, TH2F*> > h_digi_average_maxADC;
	std::map<TString, std::map<int, TH2F*> > h_rechit_average_energy;
	std::map<TString, std::map<int, TH2F*> > h_rechit_average_time;
	std::map<TString, std::map<int, std::map<int, TH2F*> > > h_digi_average_fc;
	std::map<TString, std::map<int, std::map<int, TH2F*> > > h_digi_average_adc;
	std::map<TString, std::map<int, std::map<int, TH2F*> > > h_digi_average_dv;
	std::map<TString, std::map<int, std::map<int, TH2F*> > > h_digi_average_er;
	std::map<TString, std::map<int, std::map<int, TH2F*> > > h_digi_average_capid;

	// Random event histograms. Map is depth : event#
	std::map<TString, std::map<int, std::map<int, TH2F*> > > h_digi_event_adcTotal;
	for (auto& it_digi_type : digi_types) {
		for (int depth = 1; depth <= 4; ++depth) {
			char hname[100];
			sprintf(hname, "h_" + it_digi_type + "_rechit_average_energy_d%d", depth);
			h_rechit_average_energy[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			sprintf(hname, "h_" + it_digi_type + "_rechit_average_time_d%d", depth);
			h_rechit_average_time[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

			sprintf(hname, "h_" + it_digi_type + "_digi_average_readings_d%d", depth);
			h_digi_average_readings[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

			sprintf(hname, "h_" + it_digi_type + "_digi_average_energy_d%d", depth);
			h_digi_average_energy[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_recHitTime_d%d", depth);
			h_digi_average_recHitTime [it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_presamples_d%d", depth);
			h_digi_average_presamples[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_electronicsId_d%d", depth);
			h_digi_average_electronicsId[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_rawId_d%d", depth);
			h_digi_average_rawId[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_fcTotal_d%d", depth);
			h_digi_average_fcTotal[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_adcTotal_d%d", depth);
			h_digi_average_adcTotal[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_time_d%d", depth);
			h_digi_average_time[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_time12_d%d", depth);
			h_digi_average_time12[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_time34_d%d", depth);
			h_digi_average_time34[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_charge12_d%d", depth);
			h_digi_average_charge12[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_charge34_d%d", depth);
			h_digi_average_charge34[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_isSignal_d%d", depth);
			h_digi_average_isSignal[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			
			sprintf(hname, "h_" + it_digi_type + "_digi_average_maxADC_d%d", depth);
			h_digi_average_maxADC[it_digi_type][depth] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

			for (int ts = 0; ts <= 10; ++ts) {
				sprintf(hname, "h_" + it_digi_type + "_digi_average_fc_d%d_ts%d", depth, ts);
				h_digi_average_fc[it_digi_type][depth][ts] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

				sprintf(hname, "h_" + it_digi_type + "_digi_average_adc_d%d_ts%d", depth, ts);
				h_digi_average_adc[it_digi_type][depth][ts] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

				sprintf(hname, "h_" + it_digi_type + "_digi_average_dv_d%d_ts%d", depth, ts);
				h_digi_average_dv[it_digi_type][depth][ts] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);

				sprintf(hname, "h_" + it_digi_type + "_digi_average_er_d%d_ts%d", depth, ts);
				h_digi_average_er[it_digi_type][depth][ts] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
				;

				sprintf(hname, "h_" + it_digi_type + "_digi_average_capid_d%d_ts%d", depth, ts);
				h_digi_average_capid[it_digi_type][depth][ts] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
			}
		}
	}

	//--------------------------------------------------------------------------------
	// Loop
	//--------------------------------------------------------------------------------

	for (int i = 0; i < n_events; ++i) {
		tuple_tree -> GetEntry(i);
		if ( (i + 1) % 100 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;
		
		// Random event histograms: want 100 of them.
		//	for (int depth = 1; depth <= 4; ++depth) {
		//		char hname[100];
		//		sprintf(hname, "h_digi_event_adcTotal_d%d_event%d", depth, tuple_tree->event);
		//		h_digi_event_adcTotal[depth][tuple_tree->event] = makeTH2F(hname, 85, -42.5, 42.5, 72, 0.5, 72.5);
		//	}
		//}


		CollectionPtr hfDigis (new Collection(*tuple_tree, tuple_tree -> HFDigiIEta -> size()));
		int n_hf_digis = hfDigis->GetSize();
		for (int i_digi = 0; i_digi < n_hf_digis; ++i_digi) {
			HFDigi this_digi = hfDigis->GetConstituent<HFDigi>(i_digi);
			int ieta = this_digi.ieta();
			int iphi = this_digi.iphi();
			int depth = this_digi.depth();
			h_digi_average_readings["HF"][depth]->Fill(ieta, iphi);
			//h_digi_average_energy["HF"][depth]->Fill(ieta, iphi, this_digi.energy());
			//h_digi_average_recHitTime ["HF"][depth]->Fill(ieta, iphi, this_digi.recHitTime());
			h_digi_average_presamples["HF"][depth]->Fill(ieta, iphi, this_digi.presamples());
			h_digi_average_electronicsId["HF"][depth]->Fill(ieta, iphi, this_digi.electronicsId());
			h_digi_average_rawId["HF"][depth]->Fill(ieta, iphi, this_digi.rawId());
			h_digi_average_fcTotal["HF"][depth]->Fill(ieta, iphi, this_digi.fcTotal());
			h_digi_average_adcTotal["HF"][depth]->Fill(ieta, iphi, this_digi.adcTotal());
			h_digi_average_time["HF"][depth]->Fill(ieta, iphi, this_digi.time());
			h_digi_average_time12["HF"][depth]->Fill(ieta, iphi, this_digi.time12());
			h_digi_average_time34["HF"][depth]->Fill(ieta, iphi, this_digi.time34());
			h_digi_average_charge12["HF"][depth]->Fill(ieta, iphi, this_digi.charge12());
			h_digi_average_charge34["HF"][depth]->Fill(ieta, iphi, this_digi.charge34());
			h_digi_average_isSignal["HF"][depth]->Fill(ieta, iphi, this_digi.isSignal());
			h_digi_average_maxADC["HF"][depth]->Fill(ieta, iphi, this_digi.maxADC());
			for (int ts = 0; ts < this_digi.size(); ++ts) {
				h_digi_average_fc["HF"][depth][ts]->Fill(ieta, iphi, this_digi.fc(ts));
				h_digi_average_adc["HF"][depth][ts]->Fill(ieta, iphi, this_digi.adc(ts));
				h_digi_average_dv["HF"][depth][ts]->Fill(ieta, iphi, this_digi.dv(ts));
				h_digi_average_er["HF"][depth][ts]->Fill(ieta, iphi, this_digi.er(ts));
				h_digi_average_capid["HF"][depth][ts]->Fill(ieta, iphi, this_digi.capid(ts));
			}

			//if (i % (TMath::FloorNint(n_events / 100)) == 0) {
			//	h_digi_event_adcTotal[depth][tuple_tree->event]->Fill(ieta, iphi, this_digi.adcTotal());
			//}
		} // End loop over HF digis

		CollectionPtr hbheDigis (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
		int n_hbhe_digis = hbheDigis->GetSize();
		for (int i_digi = 0; i_digi < n_hbhe_digis; ++i_digi) {
			HBHEDigi this_digi = hbheDigis->GetConstituent<HBHEDigi>(i_digi);
			int ieta = this_digi.ieta();
			int iphi = this_digi.iphi();
			int depth = this_digi.depth();
			h_digi_average_readings["HBHE"][depth]->Fill(ieta, iphi);
			//h_digi_average_energy[depth]->Fill(ieta, iphi, this_digi.energy());
			//h_digi_average_recHitTime [depth]->Fill(ieta, iphi, this_digi.recHitTime());
			h_digi_average_presamples["HBHE"][depth]->Fill(ieta, iphi, this_digi.presamples());
			h_digi_average_electronicsId["HBHE"][depth]->Fill(ieta, iphi, this_digi.electronicsId());
			h_digi_average_rawId["HBHE"][depth]->Fill(ieta, iphi, this_digi.rawId());
			h_digi_average_fcTotal["HBHE"][depth]->Fill(ieta, iphi, this_digi.fcTotal());
			h_digi_average_adcTotal["HBHE"][depth]->Fill(ieta, iphi, this_digi.adcTotal());
			h_digi_average_time["HBHE"][depth]->Fill(ieta, iphi, this_digi.time());
			h_digi_average_time12["HBHE"][depth]->Fill(ieta, iphi, this_digi.time12());
			h_digi_average_time34["HBHE"][depth]->Fill(ieta, iphi, this_digi.time34());
			h_digi_average_charge12["HBHE"][depth]->Fill(ieta, iphi, this_digi.charge12());
			h_digi_average_charge34["HBHE"][depth]->Fill(ieta, iphi, this_digi.charge34());
			h_digi_average_isSignal["HBHE"][depth]->Fill(ieta, iphi, this_digi.isSignal());
			h_digi_average_maxADC["HBHE"][depth]->Fill(ieta, iphi, this_digi.maxADC());
			for (int ts = 0; ts < this_digi.size(); ++ts) {
				h_digi_average_fc["HBHE"][depth][ts]->Fill(ieta, iphi, this_digi.fc(ts));
				h_digi_average_adc["HBHE"][depth][ts]->Fill(ieta, iphi, this_digi.adc(ts));
				h_digi_average_dv["HBHE"][depth][ts]->Fill(ieta, iphi, this_digi.dv(ts));
				h_digi_average_er["HBHE"][depth][ts]->Fill(ieta, iphi, this_digi.er(ts));
				h_digi_average_capid["HBHE"][depth][ts]->Fill(ieta, iphi, this_digi.capid(ts));
			}

			//if (i % (TMath::FloorNint(n_events / 100)) == 0) {
			//	h_digi_event_adcTotal["HBHE"][depth][tuple_tree->event]->Fill(ieta, iphi, this_digi.adcTotal());
			//}
		} // End loop over HBHE digis

		CollectionPtr hoDigis (new Collection(*tuple_tree, tuple_tree -> HODigiIEta -> size()));
		int n_ho_digis = hoDigis->GetSize();
		for (int i_digi = 0; i_digi < n_ho_digis; ++i_digi) {
			HODigi this_digi = hoDigis->GetConstituent<HODigi>(i_digi);
			int ieta = this_digi.ieta();
			int iphi = this_digi.iphi();
			int depth = this_digi.depth();
			h_digi_average_readings["HO"][depth]->Fill(ieta, iphi);
			//h_digi_average_energy[depth]->Fill(ieta, iphi, this_digi.energy());
			//h_digi_average_recHitTime [depth]->Fill(ieta, iphi, this_digi.recHitTime());
			h_digi_average_presamples["HO"][depth]->Fill(ieta, iphi, this_digi.presamples());
			h_digi_average_electronicsId["HO"][depth]->Fill(ieta, iphi, this_digi.electronicsId());
			h_digi_average_rawId["HO"][depth]->Fill(ieta, iphi, this_digi.rawId());
			h_digi_average_fcTotal["HO"][depth]->Fill(ieta, iphi, this_digi.fcTotal());
			h_digi_average_adcTotal["HO"][depth]->Fill(ieta, iphi, this_digi.adcTotal());
			h_digi_average_time["HO"][depth]->Fill(ieta, iphi, this_digi.time());
			h_digi_average_time12["HO"][depth]->Fill(ieta, iphi, this_digi.time12());
			h_digi_average_time34["HO"][depth]->Fill(ieta, iphi, this_digi.time34());
			h_digi_average_charge12["HO"][depth]->Fill(ieta, iphi, this_digi.charge12());
			h_digi_average_charge34["HO"][depth]->Fill(ieta, iphi, this_digi.charge34());
			h_digi_average_isSignal["HO"][depth]->Fill(ieta, iphi, this_digi.isSignal());
			h_digi_average_maxADC["HO"][depth]->Fill(ieta, iphi, this_digi.maxADC());
			for (int ts = 0; ts < this_digi.size(); ++ts) {
				h_digi_average_fc["HO"][depth][ts]->Fill(ieta, iphi, this_digi.fc(ts));
				h_digi_average_adc["HO"][depth][ts]->Fill(ieta, iphi, this_digi.adc(ts));
				h_digi_average_dv["HO"][depth][ts]->Fill(ieta, iphi, this_digi.dv(ts));
				h_digi_average_er["HO"][depth][ts]->Fill(ieta, iphi, this_digi.er(ts));
				h_digi_average_capid["HO"][depth][ts]->Fill(ieta, iphi, this_digi.capid(ts));
			}

			// Record detailed information for a limited number of events
			if (i % (TMath::FloorNint(n_events / max_event_histograms)) == 0) {
				for (auto& it_channel : interesting_HO_channels) {
					if ((ieta == it_channel.ieta) && (iphi == it_channel.iphi) && (depth == it_channel.depth)) {
						char hname[100];
						sprintf(hname, "h_HO_interesting_channels_fc_%d_%d_%d_%d", it_channel.ieta, it_channel.iphi, it_channel.depth, tuple_tree->event);
						TH1F* h_HO_interesting_channels_fc = makeTH1F(hname, this_digi.size(), -0.5, this_digi.size() - 0.5);

						sprintf(hname, "h_HO_interesting_channels_adc_%d_%d_%d_%d", it_channel.ieta, it_channel.iphi, it_channel.depth, tuple_tree->event);
						TH1F* h_HO_interesting_channels_adc = makeTH1F(hname, this_digi.size(), -0.5, this_digi.size() - 0.5);

						sprintf(hname, "h_HO_interesting_channels_dv_%d_%d_%d_%d", it_channel.ieta, it_channel.iphi, it_channel.depth, tuple_tree->event);
						TH1F* h_HO_interesting_channels_dv = makeTH1F(hname, this_digi.size(), -0.5, this_digi.size() - 0.5);

						sprintf(hname, "h_HO_interesting_channels_er_%d_%d_%d_%d", it_channel.ieta, it_channel.iphi, it_channel.depth, tuple_tree->event);
						TH1F* h_HO_interesting_channels_er = makeTH1F(hname, this_digi.size(), -0.5, this_digi.size() - 0.5);

						sprintf(hname, "h_HO_interesting_channels_capid_%d_%d_%d_%d", it_channel.ieta, it_channel.iphi, it_channel.depth, tuple_tree->event);
						TH1F* h_HO_interesting_channels_capid = makeTH1F(hname, this_digi.size(), -0.5, this_digi.size() - 0.5);

						for (int ts = 0; ts < this_digi.size(); ++ts) {
							h_HO_interesting_channels_fc->Fill(ts, this_digi.fc(ts));
							h_HO_interesting_channels_adc->Fill(ts, this_digi.adc(ts));
							h_HO_interesting_channels_dv->Fill(ts, this_digi.dv(ts));
							h_HO_interesting_channels_er->Fill(ts, this_digi.er(ts));
							h_HO_interesting_channels_capid->Fill(ts, this_digi.capid(ts));
						}
					}
				}
			}
			//if (i % (TMath::FloorNint(n_events / 100)) == 0) {
			//	h_digi_event_adcTotal["HO"][depth][tuple_tree->event]->Fill(ieta, iphi, this_digi.adcTotal());
			//}
		} // End loop over HO digis
	} // End loop over events
	for (auto& it_digi_type : digi_types) {
		for (int depth = 1; depth <= 4; ++depth) {
			h_digi_average_readings[it_digi_type][depth]->Scale(1. / n_events);
			//h_digi_average_energy[it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_recHitTime [it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_presamples[it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_electronicsId[it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_rawId[it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_fcTotal[it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_adcTotal[it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_time[it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_time12[it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_time34[it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_charge12[it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_charge34[it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_isSignal[it_digi_type][depth]->Scale(1. / n_events);
			h_digi_average_maxADC[it_digi_type][depth]->Scale(1. / n_events);
			for (int ts = 0; ts <= 3; ++ts) {
				h_digi_average_fc[it_digi_type][depth][ts]->Scale(1. / n_events);
				h_digi_average_adc[it_digi_type][depth][ts]->Scale(1. / n_events);
				h_digi_average_dv[it_digi_type][depth][ts]->Scale(1. / n_events);
				h_digi_average_er[it_digi_type][depth][ts]->Scale(1. / n_events);
				h_digi_average_capid[it_digi_type][depth][ts]->Scale(1. / n_events);
			}
		}
	}
}
