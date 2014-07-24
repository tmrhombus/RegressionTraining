
#ifndef BDTreader_h
#define BDTreader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class BDTreader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           eventNumber;
   Int_t           N_ECALClusters;
   Int_t           nVtx;
   Float_t         rho;
   Int_t           N_PSClusters;
   Int_t           scIndex;
   Float_t         scRawEnergy;
   Float_t         scCalibratedEnergy;
   Float_t         scPreshowerEnergy;
   Float_t         scPreshowerEnergyPlane1;
   Float_t         scPreshowerEnergyPlane2;
   Int_t           scIsEB;
   Float_t         scEta;
   Float_t         scPhi;
   Float_t         scR;
   Float_t         scPhiWidth;
   Float_t         scEtaWidth;
   Float_t         scSeedRawEnergy;
   Float_t         scSeedCalibratedEnergy;
   Float_t         scSeedEta;
   Float_t         scSeedPhi;
   Int_t           scSeedSize;
   Float_t         scSeedR9;
   Float_t         scSeedEmax;
   Float_t         scSeedE2nd;
   Float_t         scSeedLeftRightAsym;
   Float_t         scSeedTopBottomAsym;
   Float_t         scSeedE2x5max;
   Float_t         scSeed2x5LeftRightAsym;
   Float_t         scSeed2x5TopBottomAsym;
   Float_t         scSeedSigmaIetaIeta;
   Float_t         scSeedSigmaIetaIphi;
   Float_t         scSeedSigmaIphiIphi;
   Float_t         scSeedCryEta;
   Float_t         scSeedCryPhi;
   Float_t         scSeedCryIeta;
   Float_t         scSeedCryIphi;
   Float_t         scSeedCryX;
   Float_t         scSeedCryY;
   Float_t         scSeedCryIx;
   Float_t         scSeedCryIy;
   Float_t         clusterRawEnergy[11];   //[N_ECALClusters]
   Float_t         clusterCalibEnergy[11];   //[N_ECALClusters]
   Float_t         clusterEta[11];   //[N_ECALClusters]
   Float_t         clusterPhi[11];   //[N_ECALClusters]
   Float_t         clusterDPhiToSeed[11];   //[N_ECALClusters]
   Float_t         clusterDEtaToSeed[11];   //[N_ECALClusters]
   Float_t         clusterDPhiToCentroid[11];   //[N_ECALClusters]
   Float_t         clusterDEtaToCentroid[11];   //[N_ECALClusters]
   Int_t           clusterInMustache[11];   //[N_ECALClusters]
   Int_t           clusterInDynDPhi[11];   //[N_ECALClusters]
   Int_t           clusterLeakage[11];   //[N_ECALClusters]
   Float_t         clusterMaxDR;
   Float_t         clusterMaxDRDPhi;
   Float_t         clusterMaxDRDEta;
   Float_t         clusterMaxDRRawEnergy;
   Float_t         clustersMeanRawEnergy;
   Float_t         clustersRMSRawEnergy;
   Float_t         clustersMeanDRToSeed;
   Float_t         clustersMeanDEtaToSeed;
   Float_t         clustersMeanDPhiToSeed;
   Float_t         psClusterRawEnergy[90];   //[N_PSClusters]
   Float_t         psClusterEta[90];   //[N_PSClusters]
   Float_t         psClusterPhi[90];   //[N_PSClusters]
   Int_t           isMatched;
   Float_t         genPt;
   Float_t         genEta;
   Float_t         genPhi;
   Float_t         genEnergy;
   Float_t         genDEoE;
   Float_t         genDRToCentroid;
   Float_t         genDRToSeed;
   Float_t         clusterDPhiToGen[11];   //[N_ECALClusters]
   Float_t         clusterDEtaToGen[11];   //[N_ECALClusters]

   // List of branches
   TBranch        *b_eventNumber;   //!
   TBranch        *b_N_ECALClusters;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_N_PSClusters;   //!
   TBranch        *b_scIndex;   //!
   TBranch        *b_scRawEnergy;   //!
   TBranch        *b_scCalibratedEnergy;   //!
   TBranch        *b_scPreshowerEnergy;   //!
   TBranch        *b_scPreshowerEnergyPlane1;   //!
   TBranch        *b_scPreshowerEnergyPlane2;   //!
   TBranch        *b_scIsEB;   //!
   TBranch        *b_scEta;   //!
   TBranch        *b_scPhi;   //!
   TBranch        *b_scR;   //!
   TBranch        *b_scPhiWidth;   //!
   TBranch        *b_scEtaWidth;   //!
   TBranch        *b_scSeedRawEnergy;   //!
   TBranch        *b_scSeedCalibratedEnergy;   //!
   TBranch        *b_scSeedEta;   //!
   TBranch        *b_scSeedPhi;   //!
   TBranch        *b_scSeedSize;   //!
   TBranch        *b_scSeedR9;   //!
   TBranch        *b_scSeedEmax;   //!
   TBranch        *b_scSeedE2nd;   //!
   TBranch        *b_scSeedLeftRightAsym;   //!
   TBranch        *b_scSeedTopBottomAsym;   //!
   TBranch        *b_scSeedE2x5max;   //!
   TBranch        *b_scSeed2x5LeftRightAsym;   //!
   TBranch        *b_scSeed2x5TopBottomAsym;   //!
   TBranch        *b_scSeedSigmaIetaIeta;   //!
   TBranch        *b_scSeedSigmaIetaIphi;   //!
   TBranch        *b_scSeedSigmaIphiIphi;   //!
   TBranch        *b_scSeedCryEta;   //!
   TBranch        *b_scSeedCryPhi;   //!
   TBranch        *b_scSeedCryIeta;   //!
   TBranch        *b_scSeedCryIphi;   //!
   TBranch        *b_scSeedCryX;   //!
   TBranch        *b_scSeedCryY;   //!
   TBranch        *b_scSeedCryIx;   //!
   TBranch        *b_scSeedCryIy;   //!
   TBranch        *b_clusterRawEnergy;   //!
   TBranch        *b_clusterCalibEnergy;   //!
   TBranch        *b_clusterEta;   //!
   TBranch        *b_clusterPhi;   //!
   TBranch        *b_clusterDPhiToSeed;   //!
   TBranch        *b_clusterDEtaToSeed;   //!
   TBranch        *b_clusterDPhiToCentroid;   //!
   TBranch        *b_clusterDEtaToCentroid;   //!
   TBranch        *b_clusterInMustache;   //!
   TBranch        *b_clusterInDynDPhi;   //!
   TBranch        *b_clusterLeakage;   //!
   TBranch        *b_clusterMaxDR;   //!
   TBranch        *b_clusterMaxDRDPhi;   //!
   TBranch        *b_clusterMaxDRDEta;   //!
   TBranch        *b_clusterMaxDRRawEnergy;   //!
   TBranch        *b_clustersMeanRawEnergy;   //!
   TBranch        *b_clustersRMSRawEnergy;   //!
   TBranch        *b_clustersMeanDRToSeed;   //!
   TBranch        *b_clustersMeanDEtaToSeed;   //!
   TBranch        *b_clustersMeanDPhiToSeed;   //!
   TBranch        *b_psClusterRawEnergy;   //!
   TBranch        *b_psClusterEta;   //!
   TBranch        *b_psClusterPhi;   //!
   TBranch        *b_isMatched;   //!
   TBranch        *b_genPt;   //!
   TBranch        *b_genEta;   //!
   TBranch        *b_genPhi;   //!
   TBranch        *b_genEnergy;   //!
   TBranch        *b_genDEoE;   //!
   TBranch        *b_genDRToCentroid;   //!
   TBranch        *b_genDRToSeed;   //!
   TBranch        *b_clusterDPhiToGen;   //!
   TBranch        *b_clusterDEtaToGen;   //!

   BDTreader(TTree *tree=0);
   virtual ~BDTreader();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   //void test();
};

#endif

#ifdef BDTreader_cxx
BDTreader::BDTreader(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/afs/hep.wisc.edu/cms/tperry/HLT_slc6_481_CMSSW_7_1_0_pre5/src/Regression/RegressionTrees/test/hlt_reco.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/afs/hep.wisc.edu/cms/tperry/HLT_slc6_481_CMSSW_7_1_0_pre5/src/Regression/RegressionTrees/test/hlt_reco.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/afs/hep.wisc.edu/cms/tperry/HLT_slc6_481_CMSSW_7_1_0_pre5/src/Regression/RegressionTrees/test/hlt_reco.root:/RECO_mustacheSCTree");
      dir->GetObject("SuperClusterTree",tree);

   }
   Init(tree);
}

BDTreader::~BDTreader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t BDTreader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t BDTreader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void BDTreader::Init(TTree *tree)
{
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("N_ECALClusters", &N_ECALClusters, &b_N_ECALClusters);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("N_PSClusters", &N_PSClusters, &b_N_PSClusters);
   fChain->SetBranchAddress("scIndex", &scIndex, &b_scIndex);
   fChain->SetBranchAddress("scRawEnergy", &scRawEnergy, &b_scRawEnergy);
   fChain->SetBranchAddress("scCalibratedEnergy", &scCalibratedEnergy, &b_scCalibratedEnergy);
   fChain->SetBranchAddress("scPreshowerEnergy", &scPreshowerEnergy, &b_scPreshowerEnergy);
   fChain->SetBranchAddress("scPreshowerEnergyPlane1", &scPreshowerEnergyPlane1, &b_scPreshowerEnergyPlane1);
   fChain->SetBranchAddress("scPreshowerEnergyPlane2", &scPreshowerEnergyPlane2, &b_scPreshowerEnergyPlane2);
   fChain->SetBranchAddress("scIsEB", &scIsEB, &b_scIsEB);
   fChain->SetBranchAddress("scEta", &scEta, &b_scEta);
   fChain->SetBranchAddress("scPhi", &scPhi, &b_scPhi);
   fChain->SetBranchAddress("scR", &scR, &b_scR);
   fChain->SetBranchAddress("scPhiWidth", &scPhiWidth, &b_scPhiWidth);
   fChain->SetBranchAddress("scEtaWidth", &scEtaWidth, &b_scEtaWidth);
   fChain->SetBranchAddress("scSeedRawEnergy", &scSeedRawEnergy, &b_scSeedRawEnergy);
   fChain->SetBranchAddress("scSeedCalibratedEnergy", &scSeedCalibratedEnergy, &b_scSeedCalibratedEnergy);
   fChain->SetBranchAddress("scSeedEta", &scSeedEta, &b_scSeedEta);
   fChain->SetBranchAddress("scSeedPhi", &scSeedPhi, &b_scSeedPhi);
   fChain->SetBranchAddress("scSeedSize", &scSeedSize, &b_scSeedSize);
   fChain->SetBranchAddress("scSeedR9", &scSeedR9, &b_scSeedR9);
   fChain->SetBranchAddress("scSeedEmax", &scSeedEmax, &b_scSeedEmax);
   fChain->SetBranchAddress("scSeedE2nd", &scSeedE2nd, &b_scSeedE2nd);
   fChain->SetBranchAddress("scSeedLeftRightAsym", &scSeedLeftRightAsym, &b_scSeedLeftRightAsym);
   fChain->SetBranchAddress("scSeedTopBottomAsym", &scSeedTopBottomAsym, &b_scSeedTopBottomAsym);
   fChain->SetBranchAddress("scSeedE2x5max", &scSeedE2x5max, &b_scSeedE2x5max);
   fChain->SetBranchAddress("scSeed2x5LeftRightAsym", &scSeed2x5LeftRightAsym, &b_scSeed2x5LeftRightAsym);
   fChain->SetBranchAddress("scSeed2x5TopBottomAsym", &scSeed2x5TopBottomAsym, &b_scSeed2x5TopBottomAsym);
   fChain->SetBranchAddress("scSeedSigmaIetaIeta", &scSeedSigmaIetaIeta, &b_scSeedSigmaIetaIeta);
   fChain->SetBranchAddress("scSeedSigmaIetaIphi", &scSeedSigmaIetaIphi, &b_scSeedSigmaIetaIphi);
   fChain->SetBranchAddress("scSeedSigmaIphiIphi", &scSeedSigmaIphiIphi, &b_scSeedSigmaIphiIphi);
   fChain->SetBranchAddress("scSeedCryEta", &scSeedCryEta, &b_scSeedCryEta);
   fChain->SetBranchAddress("scSeedCryPhi", &scSeedCryPhi, &b_scSeedCryPhi);
   fChain->SetBranchAddress("scSeedCryIeta", &scSeedCryIeta, &b_scSeedCryIeta);
   fChain->SetBranchAddress("scSeedCryIphi", &scSeedCryIphi, &b_scSeedCryIphi);
   fChain->SetBranchAddress("scSeedCryX", &scSeedCryX, &b_scSeedCryX);
   fChain->SetBranchAddress("scSeedCryY", &scSeedCryY, &b_scSeedCryY);
   fChain->SetBranchAddress("scSeedCryIx", &scSeedCryIx, &b_scSeedCryIx);
   fChain->SetBranchAddress("scSeedCryIy", &scSeedCryIy, &b_scSeedCryIy);
   fChain->SetBranchAddress("clusterRawEnergy", clusterRawEnergy, &b_clusterRawEnergy);
   fChain->SetBranchAddress("clusterCalibEnergy", clusterCalibEnergy, &b_clusterCalibEnergy);
   fChain->SetBranchAddress("clusterEta", clusterEta, &b_clusterEta);
   fChain->SetBranchAddress("clusterPhi", clusterPhi, &b_clusterPhi);
   fChain->SetBranchAddress("clusterDPhiToSeed", clusterDPhiToSeed, &b_clusterDPhiToSeed);
   fChain->SetBranchAddress("clusterDEtaToSeed", clusterDEtaToSeed, &b_clusterDEtaToSeed);
   fChain->SetBranchAddress("clusterDPhiToCentroid", clusterDPhiToCentroid, &b_clusterDPhiToCentroid);
   fChain->SetBranchAddress("clusterDEtaToCentroid", clusterDEtaToCentroid, &b_clusterDEtaToCentroid);
   fChain->SetBranchAddress("clusterInMustache", clusterInMustache, &b_clusterInMustache);
   fChain->SetBranchAddress("clusterInDynDPhi", clusterInDynDPhi, &b_clusterInDynDPhi);
   fChain->SetBranchAddress("clusterLeakage", clusterLeakage, &b_clusterLeakage);
   fChain->SetBranchAddress("clusterMaxDR", &clusterMaxDR, &b_clusterMaxDR);
   fChain->SetBranchAddress("clusterMaxDRDPhi", &clusterMaxDRDPhi, &b_clusterMaxDRDPhi);
   fChain->SetBranchAddress("clusterMaxDRDEta", &clusterMaxDRDEta, &b_clusterMaxDRDEta);
   fChain->SetBranchAddress("clusterMaxDRRawEnergy", &clusterMaxDRRawEnergy, &b_clusterMaxDRRawEnergy);
   fChain->SetBranchAddress("clustersMeanRawEnergy", &clustersMeanRawEnergy, &b_clustersMeanRawEnergy);
   fChain->SetBranchAddress("clustersRMSRawEnergy", &clustersRMSRawEnergy, &b_clustersRMSRawEnergy);
   fChain->SetBranchAddress("clustersMeanDRToSeed", &clustersMeanDRToSeed, &b_clustersMeanDRToSeed);
   fChain->SetBranchAddress("clustersMeanDEtaToSeed", &clustersMeanDEtaToSeed, &b_clustersMeanDEtaToSeed);
   fChain->SetBranchAddress("clustersMeanDPhiToSeed", &clustersMeanDPhiToSeed, &b_clustersMeanDPhiToSeed);
   fChain->SetBranchAddress("psClusterRawEnergy", psClusterRawEnergy, &b_psClusterRawEnergy);
   fChain->SetBranchAddress("psClusterEta", psClusterEta, &b_psClusterEta);
   fChain->SetBranchAddress("psClusterPhi", psClusterPhi, &b_psClusterPhi);
   fChain->SetBranchAddress("isMatched", &isMatched, &b_isMatched);
   fChain->SetBranchAddress("genPt", &genPt, &b_genPt);
   fChain->SetBranchAddress("genEta", &genEta, &b_genEta);
   fChain->SetBranchAddress("genPhi", &genPhi, &b_genPhi);
   fChain->SetBranchAddress("genEnergy", &genEnergy, &b_genEnergy);
   fChain->SetBranchAddress("genDEoE", &genDEoE, &b_genDEoE);
   fChain->SetBranchAddress("genDRToCentroid", &genDRToCentroid, &b_genDRToCentroid);
   fChain->SetBranchAddress("genDRToSeed", &genDRToSeed, &b_genDRToSeed);
   fChain->SetBranchAddress("clusterDPhiToGen", clusterDPhiToGen, &b_clusterDPhiToGen);
   fChain->SetBranchAddress("clusterDEtaToGen", clusterDEtaToGen, &b_clusterDEtaToGen);
   Notify();
}

Bool_t BDTreader::Notify()
{
   return kTRUE;
}

void BDTreader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
#endif // #ifdef BDTreader_cxx
