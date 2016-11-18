/**
 * \file PMTAna.h
 *
 * 
 * \brief Little sample program for establishing a user analysis space.
 *
 * @author wketchum
*/

#ifndef TEST_USERANALYSIS_H
#define TEST_USERANALYSIS_H

#include <string>

#include "TTree.h"

namespace pmt{
  class PMTAna;
}

class pmt::PMTAna{
  
public:
  
  /// Default constructor
  PMTAna();

  /// Default destructor
  virtual ~PMTAna(){};

  void RunAnalysis();
  void SetupOutputTree(TTree*);
  
 private:

  std::string fAlgName;
  TTree*      fTree;
  
  void PrintInfo();

  
};

#endif
