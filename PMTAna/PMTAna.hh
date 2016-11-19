/**
 * \file PMTAna.h
 *
 * 
 * \brief Class to analyize PMT waveforms.
 *
 * @author mdeltutt
*/

#ifndef TEST_USERANALYSIS_H
#define TEST_USERANALYSIS_H

#include <string>

#include "TTree.h"

#include "lardataobj/RawData/OpDetWaveform.h"
#include "lardata/DetectorInfo/DetectorClocks.h"
#include "larcore/Geometry/GeometryCore.h"

namespace pmt{
  class PMTAna;
}

class pmt::PMTAna{
  
public:
  
  /// Default constructor
  PMTAna();

  /// Default destructor
  virtual ~PMTAna(){};

  void RunAnalysis(std::vector<raw::OpDetWaveform> const&, detinfo::DetectorClocks const&  detectorClocks, geo::GeometryCore const&);
  void SetupOutputTree(TTree*);
  
 private:

  std::string fAlgName;
  TTree*      fWaveformTree;
  Double_t    _waveform_start_time;
  UInt_t      _waveform_channel;
  UInt_t      _waveform_opdet;
  UInt_t      _waveform_size;
  Double_t    _waveform_peak_time;
  Short_t     _waveform_peak_value;
  Double_t    _waveform_relative_time;
  std::vector<short> _waveform;

  void PrintInfo();
  void AnalyzeWaveform(raw::OpDetWaveform const&, detinfo::DetectorClocks const&, geo::GeometryCore const&);
  
};

#endif
