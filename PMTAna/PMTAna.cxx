#ifndef TEST_USERANALYSIS_CXX
#define TEST_USERANALYSIS_CXX

#include "PMTAna.hh"
#include <iostream>

pmt::PMTAna::PMTAna()
  : fAlgName("PMTAna")
{}

void pmt::PMTAna::SetupOutputTree(TTree* tfs_tree){
  fTree = tfs_tree;

  std::string title = fAlgName + " Tree";
  fTree->SetObject(fTree->GetName(),title.c_str());
}

void pmt::PMTAna::RunAnalysis(){
  PrintInfo();
}

void pmt::PMTAna::PrintInfo(){
  std::cout << "\n================================== PMTAna ==========================" << std::endl;
  std::cout << "This is a ub_PMTAna class called " << fAlgName << std::endl;
  std::cout << "\tThere is an output tree called "
	    << fTree->GetName() << " (" << fTree->GetTitle() << ")" << std::endl;
  std::cout << "==========================================================================\n" << std::endl;
}

#endif
