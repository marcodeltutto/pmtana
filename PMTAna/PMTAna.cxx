#ifndef TEST_USERANALYSIS_CXX
#define TEST_USERANALYSIS_CXX

#include "PMTAna.hh"
#include <iostream>

pmt::PMTAna::PMTAna()
  : fAlgName("PMTAna")
{}

void pmt::PMTAna::SetupOutputTree(TTree* tfs_tree){
  fWaveformTree = tfs_tree;

  std::string title = fAlgName + "Waveform Tree";
  fWaveformTree->SetObject(fWaveformTree->GetName(),title.c_str());

  fWaveformTree->Branch("waveform_start_time",&_waveform_start_time,"waveform_start_time/D");
  fWaveformTree->Branch("waveform_channel",&_waveform_channel,"waveform_channel/i");
  fWaveformTree->Branch("waveform_size",&_waveform_size,"waveform_size/i");
  fWaveformTree->Branch("waveform_peak_time",&_waveform_peak_time,"waveform_peak_time/D");
  fWaveformTree->Branch("waveform_peak_value",&_waveform_peak_value,"waveform_peak_value/S");
  fWaveformTree->Branch("waveform_relative_time",&_waveform_relative_time,"waveform_relative_time/D");
  fWaveformTree->Branch("waveform","std::vector<short>",&_waveform);
}

void pmt::PMTAna::RunAnalysis(std::vector<raw::OpDetWaveform> const& waveform_vec, detinfo::DetectorClocks const&  detectorClocks){
  PrintInfo();

  for( auto const& waveform : waveform_vec)
    AnalyzeWaveform(waveform, detectorClocks);

}

void pmt::PMTAna::AnalyzeWaveform(raw::OpDetWaveform const& waveform, detinfo::DetectorClocks const&  detectorClocks){

  _waveform_peak_time = 0;
  _waveform_peak_value = -999;

  for(size_t i_w=0; i_w<waveform.size(); i_w++){
    if(waveform[i_w]>_waveform_peak_value){
      _waveform_peak_value = waveform[i_w];
      _waveform_peak_time = (Double_t)i_w;
    }
  }
  _waveform_size = waveform.size();
  _waveform_start_time = waveform.TimeStamp();
  _waveform_channel = waveform.ChannelNumber();

  //std::vector<short> & temp = waveform.Waveform();
  _waveform = waveform;



  // Reconstruct time
  double absTime = waveform.TimeStamp() 
                   + _waveform_peak_time * detectorClocks.OpticalClock().TickPeriod();

  double relTime = absTime - detectorClocks.TriggerTime();

  _waveform_relative_time = relTime;


  fWaveformTree->Fill();                  
}

void pmt::PMTAna::PrintInfo(){
  std::cout << "\n================================== PMTAna ==========================" << std::endl;
  std::cout << "This is a ub_PMTAna class called " << fAlgName << std::endl;
  std::cout << "\tThere is an output tree called "
	    << fWaveformTree->GetName() << " (" << fWaveformTree->GetTitle() << ")" << std::endl;
  std::cout << "==========================================================================\n" << std::endl;
}

#endif
