#include "analysisClass.h"
#include "HcalTupleTree.h"
#include "HBHEDigi.h"
#include "HFDigi.h"
#include <map>
#include "TH2F.h"
#include "TH3F.h"
#include "TMath.h"

int findIndex ( const int & id, const std::vector<int> * ids ){
	std::vector<int>::const_iterator lower_bound = ids -> begin();
	std::vector<int>::const_iterator upper_bound = ids -> end();
	std::vector<int>::const_iterator mid_point;

	int distance = std::distance(lower_bound, upper_bound);
	int half_distance, retval;

	while ( distance > 0 ) { 
		half_distance = distance / 2;
		mid_point = lower_bound;
		std::advance(mid_point, half_distance);
		if ( *mid_point < id ) {
			lower_bound = mid_point;
			++lower_bound;
			distance = distance - half_distance - 1;
		}
		else { 
			distance = half_distance;
		}
	}

	retval = (*mid_point == id) ? std::distance ( ids -> begin(), lower_bound ) : -1;
	return retval;
}

void analysisClass::loop(){
	bool do_hf = false;
	//--------------------------------------------------------------------------------
	// Declare HCAL tree(s)
	//--------------------------------------------------------------------------------

	HcalTupleTree * tuple_tree = getTree<HcalTupleTree>("tuple_tree");
	int n_events = tuple_tree -> fChain -> GetEntries();

	//--------------------------------------------------------------------------------
	// Turn on/off branches
	//--------------------------------------------------------------------------------
	
	tuple_tree -> fChain -> SetBranchStatus("*"               , kFALSE);
	tuple_tree -> fChain -> SetBranchStatus("run", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("event", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("ls", kTRUE);

	//tuple_tree -> fChain -> SetBranchStatus("HFDigiEta", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiPhi", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiRecEnergy", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiRecTime", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiAllFC", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiEnergy", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiFC", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiGain", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiNomFC", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiPedFC", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiRCGain", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiDepth", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiFiberIdleOffset", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiIEta", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiIPhi", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiPresamples", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiSize", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiADC", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiCapID", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiDV", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiER", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiFiber", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiFiberChan", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiRaw", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiRawID", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HFDigiElectronicsID", kTRUE);

	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiEta", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPhi", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecEnergy", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRecTime", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiAllFC", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiEnergy", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFC", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiGain", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiNomFC", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPedFC", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRCGain", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDepth", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFiberIdleOffset", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIEta", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiIPhi", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HBHEDigiPresamples", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiSize", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiADC", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HBHEDigiCapID", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HBHEDigiDV", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HBHEDigiER", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFiber", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HBHEDigiFiberChan", kTRUE);
	tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRaw", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HBHEDigiRawID", kTRUE);
	//tuple_tree -> fChain -> SetBranchStatus("HBHEDigiElectronicsID", kTRUE);
	
	if (do_hf) {
		tuple_tree -> fChain -> SetBranchStatus("HFDigiEta", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiPhi", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiAllFC", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiEnergy", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiFC", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiGain", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiNomFC", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiPedFC", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiRCGain", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiDepth", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiIEta", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiIPhi", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiSize", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiADC", kTRUE);
		tuple_tree -> fChain -> SetBranchStatus("HFDigiRaw", kTRUE);
	}
	//--------------------------------------------------------------------------------
	// Make histograms
	//--------------------------------------------------------------------------------

	TH2F * h_utca_average_adcTotal = makeTH2F ("utca_average_adcTotal", 85, -42.5, 42.5, 72,  0.5, 72.5 );
	std::map<int, TH3F*> h_utca_event_adcTotal_index;
	std::map<int, TH3F*> h_utca_event_adcTotal_actual;
	std::map<int, std::map<int, TH3F*> > h_utca_event_adcSlices_index;
	TH1F* h_utca_adc50 = makeTH1F("utca_adc50", 6121, -0.5, 6120.5);
	TH1F* h_utca_adc100 = makeTH1F("utca_adc100", 6121, -0.5, 6120.5);
	TH1F* h_utca_adc200 = makeTH1F("utca_adc200", 6121, -0.5, 6120.5);
	std::vector<int> events_15adc50;
	std::vector<int> events_30adc100;
	std::vector<int> events_30adc200;

	// HF plots
	std::map<int, TH3F*> h_hf_event_adcTotal_index;
	std::map<int, std::map<int, TH3F*> > h_hf_event_adcSlices_index;

	//--------------------------------------------------------------------------------
	// Loop
	//--------------------------------------------------------------------------------
	
	for (int i = 0; i < n_events; ++i){
		
		tuple_tree -> GetEntry(i);
		if ( (i + 1) % 100 == 0 ) std::cout << "Processing event " << i + 1 << "/" << n_events << std::endl;


		CollectionPtr hbhe_digis  (new Collection(*tuple_tree, tuple_tree -> HBHEDigiIEta -> size()));
		int n_hbhe_digis = hbhe_digis -> GetSize();
		int n_digis_adc50 = 0;
		int n_digis_adc100 = 0;
		int n_digis_adc200 = 0;
		for (int i_digi = 0; i_digi < n_hbhe_digis; ++i_digi ) {
			HBHEDigi this_digi = hbhe_digis -> GetConstituent<HBHEDigi>(i_digi);
			h_utca_average_adcTotal->Fill(this_digi.ieta(), this_digi.iphi(), this_digi.adcTotal());
			if (this_digi.adcTotal() > 50) {
				++n_digis_adc50;
			}
			if (this_digi.adcTotal() > 100) {
				++n_digis_adc100;
			}
			if (this_digi.adcTotal() > 200) {
				++n_digis_adc200;
			}
		}
		h_utca_adc50->Fill(n_digis_adc50);
		h_utca_adc100->Fill(n_digis_adc100);
		h_utca_adc200->Fill(n_digis_adc200);

		// Record more info for events with many hot channels
		if (n_digis_adc50 > 15 || i % TMath::FloorNint(n_events / 200.) == 0) {
			events_15adc50.push_back(tuple_tree->event);
			TString hname = "utca_event_";
			hname += tuple_tree->event;
			hname += "_adcTotal_index";
			h_utca_event_adcTotal_index[i] = makeTH3F(hname, 85, -42.5, 42.5, 72,  0.5, 72.5, 3, 0.5, 3.5 );

			hname = "utca_event_";
			hname += tuple_tree->event;
			hname += "_adcTotal_actual";
			h_utca_event_adcTotal_actual[i] = makeTH3F(hname, 85 * 4, -5., 5., 72 * 5,  -3.5, 3.5, 3, 0.5, 3.5);

			hname = "utca_event_";
			hname += tuple_tree->event;
			hname += "_adcSlices_index_depth1";
			h_utca_event_adcSlices_index[i][1] = makeTH3F(hname, 85, -42.5, 42.5, 72,  0.5, 72.5, 10, -0.5, 9.5);
			hname = "utca_event_";
			hname += tuple_tree->event;
			hname += "_adcSlices_index_depth2";
			h_utca_event_adcSlices_index[i][2] = makeTH3F(hname, 85, -42.5, 42.5, 72,  0.5, 72.5, 10, -0.5, 9.5);
			hname = "utca_event_";
			hname += tuple_tree->event;
			hname += "_adcSlices_index_depth3";
			h_utca_event_adcSlices_index[i][3] = makeTH3F(hname, 85, -42.5, 42.5, 72,  0.5, 72.5, 10, -0.5, 9.5);

			for (int i_digi = 0; i_digi < n_hbhe_digis; ++i_digi ) {
				HBHEDigi this_digi = hbhe_digis -> GetConstituent<HBHEDigi>(i_digi);
				h_utca_event_adcTotal_index[i]->Fill(this_digi.ieta(), this_digi.iphi(), this_digi.depth(), this_digi.adcTotal());
				h_utca_event_adcTotal_actual[i]->Fill(this_digi.eta(), this_digi.phi(), this_digi.depth(), this_digi.adcTotal());
				for (int i_slice = 0; i_slice < 4; ++i_slice) {
					h_utca_event_adcSlices_index[i][this_digi.depth()]->Fill(this_digi.ieta(), this_digi.iphi(), i_slice, this_digi.adc(i_slice));
				}
			}
		}
		if (n_digis_adc100 > 30) {
			events_30adc100.push_back(tuple_tree->event);
		} 
		if (n_digis_adc200 > 30) {
			events_30adc200.push_back(tuple_tree->event);
		} 

		// HF: make 100 histograms of random events
		if (do_hf) {
			if (i % TMath::FloorNint(n_events / 100) == 0) {
				TString hname = "hf_event_";
				hname += tuple_tree->event;
				hname += "_adcTotal_index";
				h_hf_event_adcTotal_index[i] = makeTH3F(hname, 85, -42.5, 42.5, 72,  0.5, 72.5, 2, 0.5, 2.5 );

				hname = "hf_event_";
				hname += tuple_tree->event;
				hname += "_adcSlices_index_depth1";
				h_hf_event_adcSlices_index[i][1] = makeTH3F(hname, 85, -42.5, 42.5, 72,  0.5, 72.5, 4, -0.5, 3.5);
				hname = "hf_event_";
				hname += tuple_tree->event;
				hname += "_adcSlices_index_depth2";
				h_hf_event_adcSlices_index[i][2] = makeTH3F(hname, 85, -42.5, 42.5, 72,  0.5, 72.5, 4, -0.5, 3.5);

				CollectionPtr hf_digis  (new Collection(*tuple_tree, tuple_tree -> HFDigiIEta -> size()));
				int n_hf_digis = hf_digis -> GetSize();

				for (int i_digi = 0; i_digi < n_hf_digis; ++i_digi ) {
					HFDigi this_digi = hf_digis -> GetConstituent<HFDigi>(i_digi);
					h_hf_event_adcTotal_index[i]->Fill(this_digi.ieta(), this_digi.iphi(), this_digi.depth(), this_digi.adcTotal());
					for (int i_slice = 0; i_slice < 4; ++i_slice) {
						h_hf_event_adcSlices_index[i][this_digi.depth()]->Fill(this_digi.ieta(), this_digi.iphi(), i_slice, this_digi.adc(i_slice));
					}
				}
			}
		}
	} // End loop over events
	h_utca_average_adcTotal->Scale(1. / n_events);
	std::cout << "Events with at least 30 channels with ADC > 100:" << std::endl;
	for (auto it_evt : events_30adc100) {
		std::cout << "\t" << it_evt << std::endl;
	}
	std::cout << "Events with at least 30 channels with ADC > 200:" << std::endl;
	for (auto it_evt : events_30adc200) {
		std::cout << "\t" << it_evt << std::endl;
	}
}
