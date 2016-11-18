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

namespace pmt{
  class PMTAna;
}

class pmt::PMTAna{
  
public:
  
  /// Default constructor
  PMTAna();

  /// Default destructor
  virtual ~PMTAna(){};

  void RunAnalysis(std::vector<raw::OpDetWaveform> const&);
  void SetupOutputTree(TTree*);
  
 private:

  std::string fAlgName;
  TTree*      fWaveformTree;
  Double_t    waveform_start_time;
  UInt_t      waveform_channel;
  UInt_t      waveform_size;
  Double_t    waveform_peak_time;
  Short_t     waveform_peak_value;
  
  void PrintInfo();
  void AnalyzeWaveform(raw::OpDetWaveform const&);
  
};

#endif
