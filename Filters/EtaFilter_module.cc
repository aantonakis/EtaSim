////////////////////////////////////////////////////////////////////////
//// Class:       EtaFilter
//// Plugin Type: filter (art v3_05_01)
//// File:        EtaFilter_module.cc
////
//////////////////////////////////////////////////////////////////////////



#include "art/Framework/Core/EDFilter.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include "nusimdata/SimulationBase/MCTruth.h"

#include <memory>


class EtaFilter;

class EtaFilter : public art::EDFilter {
public:
  explicit EtaFilter(fhicl::ParameterSet const& p);

  EtaFilter(EtaFilter const&) = delete;
  EtaFilter(EtaFilter&&) = delete;
  EtaFilter& operator=(EtaFilter const&) = delete;
  EtaFilter& operator=(EtaFilter&&) = delete;

  bool filter(art::Event& e) override;

  // Selected optional functions.
  void beginJob() override;
  void endJob() override;
  
private:


};



EtaFilter::EtaFilter(fhicl::ParameterSet const& p)
  : EDFilter{p}  // ,

{
  // Call appropriate produces<>() functions here.
  //   // Call appropriate consumes<>() for any products to be retrieved by this module.
  //     //fMCTproducer = p.get<art::InputTag>("MCTproducer");
  //       //fMCTproducer = p.get<art::InputTag>("largeant");
  //
}


bool EtaFilter::filter(art::Event& e)
{
  auto const &mct_h = e.getValidHandle<std::vector<simb::MCTruth>>("generator");

  int neta = 0; // initialize eta count

 for (long unsigned int p = 0; p < mct_h->size(); ++p) {

    auto mct = mct_h->at(p);

    //Check if it's a neutrino
    if (!mct.NeutrinoSet()) continue;

    size_t npart = mct.NParticles();

    for (size_t i = 0; i < npart; i++) {
    
      auto const &part = mct.GetParticle(i);

      if (part.PdgCode() == 221)
        neta += 1; 

    }// for all MCParticles

  } // loop over the truths
  if (neta == 0) return false;

  return true;

}

void EtaFilter::beginJob()
{
  // Implementation of optional member function here.
}

void EtaFilter::endJob()
{
  // Implementation of optional member function here.
}

DEFINE_ART_MODULE(EtaFilter)








