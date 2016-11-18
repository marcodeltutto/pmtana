////////////////////////////////////////////////////////////////////////
// Class:       PMTAnalyzer
// Plugin Type: analyzer (art v2_04_00)
// File:        PMTAnalyzer_module.cc
//
// Generated at Fri Nov 18 08:21:40 2016 by Marco Del Tutto using cetskelgen
// from cetlib version v1_20_00.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include "art/Framework/Services/Optional/TFileService.h"
#include "lardata/DetectorInfoServices/DetectorClocksService.h"

#include "TTree.h"

#include "PMTAna/PMTAna.hh"

class PMTAnalyzer;


class PMTAnalyzer : public art::EDAnalyzer {
public:
  explicit PMTAnalyzer(fhicl::ParameterSet const & p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  PMTAnalyzer(PMTAnalyzer const &) = delete;
  PMTAnalyzer(PMTAnalyzer &&) = delete;
  PMTAnalyzer & operator = (PMTAnalyzer const &) = delete;
  PMTAnalyzer & operator = (PMTAnalyzer &&) = delete;

  // Required functions.
  void analyze(art::Event const & e) override;

private:

  // Declare member data here.
//  PrintRelevantInfo();
  pmt::PMTAna fMyAnalysisObj;
  TTree* _tree;
  int _run, _subrun, _event;
};


PMTAnalyzer::PMTAnalyzer(fhicl::ParameterSet const & p)
  :
  EDAnalyzer(p)  // ,
 // More initializers here.
{
    art::ServiceHandle<art::TFileService> tfs;
    _tree = tfs->make<TTree>("myanatree","MyAnalysis Tree");
    
    fMyAnalysisObj.SetupOutputTree(_tree);

    _tree->Branch("run",    &_run,    "run/I");
    _tree->Branch("subrun", &_subrun, "subrun/I");
    _tree->Branch("event",  &_event,  "event/I");

}

void PMTAnalyzer::analyze(art::Event const & e)
{

    _run    = e.id().run();
    _subrun = e.id().subRun();
    _event  = e.id().event();

    art::Handle<std::vector<raw::OpDetWaveform> > waveformHandle;
    e.getByLabel("pmtreadout","OpdetCosmicHighGain",waveformHandle);
    if(!waveformHandle.isValid()) {
        std::cerr << "ERROR: can't find waveform from " << "?" << std::endl;
        throw std::exception();
    }
    std::vector<raw::OpDetWaveform> const& waveformVector(*waveformHandle);

    // Get the detector clock service
    auto const& detectorClocks (*lar::providerFrom< detinfo::DetectorClocksService >());
    std::cout << "Trigger Time: " << detectorClocks.TriggerTime() << std::endl;
    std::cout << "Tick Period:  " << detectorClocks.OpticalClock().TickPeriod() << std::endl;

    fMyAnalysisObj.RunAnalysis(waveformVector, detectorClocks);
}


DEFINE_ART_MODULE(PMTAnalyzer)
