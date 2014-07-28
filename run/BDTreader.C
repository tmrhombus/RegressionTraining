#define BDTreader_cxx
#include "BDTreader.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <stdlib.h> // for fabs()
#include <iostream> // for std::cout

#include <vector>
#include <string>

#include "GBRTree.h"
#include "GBRForest.h"

void BDTreader::Loop()
{
   if (fChain == 0) return;
    TFile *outfile = new TFile("./roots/BDTout_HLT_old.root","RECREATE");
    //TFile* RECO_forestFile = TFile::Open("/afs/hep.wisc.edu/cms/tperry/HLT_slc6_481_CMSSW_7_1_2/src/RegressionTraining/roots/ELE_712_PU25_RECO_results.root");
    //TFile* HLT_forestFile  = TFile::Open("/afs/hep.wisc.edu/cms/tperry/HLT_slc6_481_CMSSW_7_1_2/src/RegressionTraining/roots/ELE_712_PU25_HLT_results.root");
    TFile* RECO_forestFile = TFile::Open("/afs/hep.wisc.edu/cms/tperry/HLT_slc6_481_CMSSW_7_1_2/src/RegressionTraining/roots/ELE_710_RECO_results.root");
    TFile* HLT_forestFile  = TFile::Open("/afs/hep.wisc.edu/cms/tperry/HLT_slc6_481_CMSSW_7_1_2/src/RegressionTraining/roots/ELE_710_HLT_results.root");

    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t nbytes = 0, nb = 0;

    if(!RECO_forestFile)
    {
        std::cout<<"ERROR: Cannot open RECO BDT file\n";
        return;
    }
    if(!HLT_forestFile)
    {
        std::cout<<"ERROR: Cannot open HLT BDT file\n";
        return;
    }

    GBRForest* RECO_forestEB = NULL;
    GBRForest* RECO_forestEE = NULL;
    GBRForest* HLT_forestEB = NULL;
    GBRForest* HLT_forestEE = NULL;
    RECO_forestFile->GetObject("EBCorrection", RECO_forestEB);
    RECO_forestFile->GetObject("EECorrection", RECO_forestEE);
    HLT_forestFile->GetObject("EBCorrection", HLT_forestEB);
    HLT_forestFile->GetObject("EECorrection", HLT_forestEE);
    if(!RECO_forestEB)
    {
        std::cout<<"ERROR: Cannot find RECO_forestEB in file \n";
        return;
    }
    if(!RECO_forestEE)
    {
        std::cout<<"ERROR: Cannot find RECO_forestEE in file \n";
        return;
    }
    if(!HLT_forestEB)
    {
        std::cout<<"ERROR: Cannot find HLT_forestEB in file \n";
        return;
    }
    if(!HLT_forestEE)
    {
        std::cout<<"ERROR: Cannot find HLT_forestEE in file \n";
        return;
    }

    vector<string>* bdtVariablesEB= NULL;
    vector<string>* bdtVariablesEE= NULL;
    RECO_forestFile->GetObject("varlistEB", bdtVariablesEB);
    RECO_forestFile->GetObject("varlistEE", bdtVariablesEE);
    if(!bdtVariablesEE)
    {
        std::cout<<"ERROR: Cannot find variable list EE \n";
        return;
    }
    if(!bdtVariablesEB)
    {
        std::cout<<"ERROR: Cannot find variable list EB \n";
        return;
    }

    int res_nbins, nvtx_nbins, rho_nbins;
    float res_bmin, nvtx_bmin, rho_bmin;
    float res_bmax, nvtx_bmax, rho_bmax;

    res_nbins = 100;
    res_bmin = -0.5;
    res_bmax = 0.5; 

    nvtx_nbins = 20;
    nvtx_bmin = 0.;
    nvtx_bmax = 20.;

    rho_nbins = 50;
    rho_bmin = 0.;
    rho_bmax = 2.;

    TH1F* res_preEB  = new TH1F("res_preEB","",res_nbins,res_bmin,res_bmax);
    TH1F* res_recoEB = new TH1F("res_recoEB","",res_nbins,res_bmin,res_bmax);
    TH1F* res_hltEB  = new TH1F("res_hltEB","",res_nbins,res_bmin,res_bmax);
    TH1F* res_preEE  = new TH1F("res_preEE","",res_nbins,res_bmin,res_bmax);
    TH1F* res_recoEE = new TH1F("res_recoEE","",res_nbins,res_bmin,res_bmax);
    TH1F* res_hltEE  = new TH1F("res_hltEE","",res_nbins,res_bmin,res_bmax);

    TH2F* res_v_nvtx_preEB  = new TH2F("res_v_nvtx_preEB","",res_nbins,res_bmin,res_bmax,nvtx_nbins,nvtx_bmin,nvtx_bmax);
    TH2F* res_v_nvtx_recoEB = new TH2F("res_v_nvtx_recoEB","",res_nbins,res_bmin,res_bmax,nvtx_nbins,nvtx_bmin,nvtx_bmax);
    TH2F* res_v_nvtx_hltEB  = new TH2F("res_v_nvtx_hltEB","",res_nbins,res_bmin,res_bmax,nvtx_nbins,nvtx_bmin,nvtx_bmax);
    TH2F* res_v_nvtx_preEE  = new TH2F("res_v_nvtx_preEE","",res_nbins,res_bmin,res_bmax,nvtx_nbins,nvtx_bmin,nvtx_bmax);
    TH2F* res_v_nvtx_recoEE = new TH2F("res_v_nvtx_recoEE","",res_nbins,res_bmin,res_bmax,nvtx_nbins,nvtx_bmin,nvtx_bmax);
    TH2F* res_v_nvtx_hltEE  = new TH2F("res_v_nvtx_hltEE","",res_nbins,res_bmin,res_bmax,nvtx_nbins,nvtx_bmin,nvtx_bmax);

    TH2F* res_v_rho_preEB  = new TH2F("res_v_rho_preEB","",res_nbins,res_bmin,res_bmax,rho_nbins,rho_bmin,rho_bmax);
    TH2F* res_v_rho_recoEB = new TH2F("res_v_rho_recoEB","",res_nbins,res_bmin,res_bmax,rho_nbins,rho_bmin,rho_bmax);
    TH2F* res_v_rho_hltEB  = new TH2F("res_v_rho_hltEB","",res_nbins,res_bmin,res_bmax,rho_nbins,rho_bmin,rho_bmax);
    TH2F* res_v_rho_preEE  = new TH2F("res_v_rho_preEE","",res_nbins,res_bmin,res_bmax,rho_nbins,rho_bmin,rho_bmax);
    TH2F* res_v_rho_recoEE = new TH2F("res_v_rho_recoEE","",res_nbins,res_bmin,res_bmax,rho_nbins,rho_bmin,rho_bmax);
    TH2F* res_v_rho_hltEE  = new TH2F("res_v_rho_hltEE","",res_nbins,res_bmin,res_bmax,rho_nbins,rho_bmin,rho_bmax);

    int nVarsEB = bdtVariablesEB->size();
    int nVarsEE = bdtVariablesEE->size();
    std::cout<<"nVars: "<<nVarsEB<<" "<<nVarsEE<<std::endl;
    double RECO_responseEB_avg, HLT_responseEB_avg, RECO_responseEE_avg, HLT_responseEE_avg;
    int counter; counter = 1;

    for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     counter++;
    
     float varListEB[] = {
         nVtx
         ,scEta
         ,scPhi
         ,scEtaWidth
         ,scPhiWidth
         ,scSeedR9
         ,scSeedRawEnergy/scRawEnergy
         ,scSeedEmax/scRawEnergy
         ,scSeedE2nd/scRawEnergy
         ,scSeedLeftRightAsym
         ,scSeedTopBottomAsym
         ,scSeedSigmaIetaIeta
         ,scSeedSigmaIetaIphi
         ,scSeedSigmaIphiIphi
         ,N_ECALClusters
         ,clusterMaxDR
         ,clusterMaxDRDPhi
         ,clusterMaxDRDEta
         ,clusterMaxDRRawEnergy/scRawEnergy
         ,clusterRawEnergy[0]/scRawEnergy
         ,clusterRawEnergy[1]/scRawEnergy
         ,clusterRawEnergy[2]/scRawEnergy
         ,clusterDPhiToSeed[0]
         ,clusterDPhiToSeed[1]
         ,clusterDPhiToSeed[2]
         ,clusterDEtaToSeed[0]
         ,clusterDEtaToSeed[1]
         ,clusterDEtaToSeed[2]
         ,scSeedCryEta
         ,scSeedCryPhi
         ,scSeedCryIeta
         ,scSeedCryIphi
         ,scRawEnergy
        };

     float varListEE[] = {
         nVtx
         ,scEta
         ,scPhi
         ,scEtaWidth
         ,scPhiWidth
         ,scSeedR9
         ,scSeedRawEnergy/scRawEnergy
         ,scSeedEmax/scRawEnergy
         ,scSeedE2nd/scRawEnergy
         ,scSeedLeftRightAsym
         ,scSeedTopBottomAsym
         ,scSeedSigmaIetaIeta
         ,scSeedSigmaIetaIphi
         ,scSeedSigmaIphiIphi
         ,N_ECALClusters
         ,clusterMaxDR
         ,clusterMaxDRDPhi
         ,clusterMaxDRDEta
         ,clusterMaxDRRawEnergy/scRawEnergy
         ,clusterRawEnergy[0]/scRawEnergy
         ,clusterRawEnergy[1]/scRawEnergy
         ,clusterRawEnergy[2]/scRawEnergy
         ,clusterDPhiToSeed[0]
         ,clusterDPhiToSeed[1]
         ,clusterDPhiToSeed[2]
         ,clusterDEtaToSeed[0]
         ,clusterDEtaToSeed[1]
         ,clusterDEtaToSeed[2]
         ,scPreshowerEnergy/scRawEnergy
         ,scRawEnergy
        };

     float* varsEB = new float[nVarsEB];
     float* varsEE = new float[nVarsEE];
     for(int i=0;i<nVarsEB;++i){varsEB[i] = varListEB[i];}
     for(int i=0;i<nVarsEE;++i){varsEE[i] = varListEE[i];}

     //for(int i=0;i<nVarsEB;++i)
     //{
     // std::cout<<i<<" "<<varsEB[i]<<" "<<varListEB[i]<<std::endl;
     //};

     double RECO_responseEB = RECO_forestEB->GetResponse(varsEB);
     double RECO_responseEE = RECO_forestEE->GetResponse(varsEE);
     double HLT_responseEB = HLT_forestEB->GetResponse(varsEB);
     double HLT_responseEE = HLT_forestEE->GetResponse(varsEE);
     RECO_responseEB_avg+=RECO_responseEB;
     HLT_responseEB_avg+=HLT_responseEB;
     RECO_responseEE_avg+=RECO_responseEE;
     HLT_responseEE_avg+=HLT_responseEE;

     //std::cout<<HLT_responseEB<<" "<<HLT_responseEE<<std::endl;
     //std::cout<<RECO_responseEB<<" "<<RECO_responseEE<<std::endl<<std::endl;

     if( scIsEB ){ 
      res_preEB->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy) ) / genEnergy );
      res_recoEB->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy)*RECO_responseEB ) / genEnergy );
       res_hltEB->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy)*HLT_responseEB  ) / genEnergy );

      res_v_nvtx_preEB->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy) ) / genEnergy , nVtx );
      res_v_nvtx_recoEB->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy)*RECO_responseEB ) / genEnergy , nVtx );
       res_v_nvtx_hltEB->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy)*HLT_responseEB  ) / genEnergy , nVtx );

      res_v_rho_preEB->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy) ) / genEnergy , rho );
      res_v_rho_recoEB->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy)*RECO_responseEB ) / genEnergy , rho );
       res_v_rho_hltEB->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy)*HLT_responseEB  ) / genEnergy , rho );
     }
     if( !scIsEB ){ 
      res_preEE->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy) ) / genEnergy );
      res_recoEE->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy)*RECO_responseEE ) / genEnergy );
       res_hltEE->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy)*HLT_responseEE  ) / genEnergy );

      res_v_nvtx_preEE->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy) ) / genEnergy , nVtx );
      res_v_nvtx_recoEE->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy)*RECO_responseEE ) / genEnergy , nVtx );
       res_v_nvtx_hltEE->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy)*HLT_responseEE  ) / genEnergy , nVtx );

      res_v_rho_preEE->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy) ) / genEnergy , rho );
      res_v_rho_recoEE->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy)*RECO_responseEE ) / genEnergy , rho );
       res_v_rho_hltEE->Fill( (genEnergy- (scRawEnergy+scPreshowerEnergy)*HLT_responseEE  ) / genEnergy , rho );
     }

    }
    RECO_responseEB_avg/=counter;
    HLT_responseEB_avg/=counter;
    RECO_responseEE_avg/=counter;
    HLT_responseEE_avg/=counter;
    std::cout<<"EB"<<std::endl;
    std::cout<<" RECO Avg SF: "<<RECO_responseEB_avg<<std::endl;
    std::cout<<" HLT Avg SF: "<<HLT_responseEB_avg<<std::endl;
    std::cout<<"EE"<<std::endl;
    std::cout<<" RECO Avg SF: "<<RECO_responseEE_avg<<std::endl;
    std::cout<<" HLT Avg SF: "<<HLT_responseEE_avg<<std::endl;

    outfile->cd();

    res_preEB->Write();
    res_recoEB->Write();
    res_hltEB->Write();

    res_preEE->Write();
    res_recoEE->Write();
    res_hltEE->Write();
      
    res_v_nvtx_preEB->Write();
    res_v_nvtx_recoEB->Write();
    res_v_nvtx_hltEB->Write();
      
    res_v_rho_preEB->Write();
    res_v_rho_recoEB->Write();
    res_v_rho_hltEB->Write();
      
    res_v_nvtx_preEE->Write();
    res_v_nvtx_recoEE->Write();
    res_v_nvtx_hltEE->Write();
      
    res_v_rho_preEE->Write();
    res_v_rho_recoEE->Write();
    res_v_rho_hltEE->Write();

    outfile->Close();
    RECO_forestFile->Close();
    HLT_forestFile->Close();
}

