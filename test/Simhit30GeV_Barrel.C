#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH2F.h"
#include "TH2F.h"

void Simhit30GeV_Barrel()
{
 char* filename ="simhitoutput.root";
 char * treename="Events";
 TFile * file = new TFile(filename);
 TTree * events = dynamic_cast<TTree*>(file->Get("Events"));
 assert(events != 0);
 TBranch * branch = events->GetBranch( "PEcalValidInfo_SimG4Object_EcalValidInfo_EcalHitsValid.obj");
 assert(branch != 0);
 int nev = events->GetEntries();

 PEcalValidInfo  EcalInfo;
 branch->SetAddress( &EcalInfo);

 branch ->GetEntry(1);
 float  TotalE = EcalInfo.momentum().e();

 //1-Dimension Histograms.
 static const int NHisto = 12; 
 char* label[NHisto];
 
 label[0] = "Barrel_E1x1";
 label[1] = "Barrel_E2x2";
 label[2] = "Barrel_E3x3";
 label[3] = "Barrel_E4x4";
 label[4] = "Barrel_E5x5";
 label[5] = "Barrel_E1OverE4";
 label[6] = "Barrel_E4OverE9";
 label[7] = "Barrel_E9OverE16";
 label[8] = "Barrel_E16OverE25";
 label[9] = "Barrel_E1OverE25";
 label[10] = "Barrel_E9OverE25";
 label[11] = "Ecal_EBOverETotal";


 TH1F * h1[NHisto];
 
 h1[0] = new TH1F(label[0],"E1x1",50, 0.8e+4, 3.5e+4);
 h1[1] = new TH1F(label[1],"E2x2",50, 0.8e+4, 3.5e+4);
 h1[2] = new TH1F(label[2],"E3x3",50, 0.8e+4, 3.5e+4);
 h1[3] = new TH1F(label[3],"E4x4",50, 0.8e+4, 3.5e+4);
 h1[4] = new TH1F(label[4],"E5x5",50, 0.8e+4, 3.5e+4);

 h1[5] = new TH1F(label[5],"E1/E4"   ,100, 0.2, 1.1);
 h1[6] = new TH1F(label[6],"E4/E9"   ,100, 0.4, 1.1);
 h1[7] = new TH1F(label[7],"E9/E16"  ,100, 0.4, 1.1);
 h1[8] = new TH1F(label[8],"E16/E25" ,100, 0.4, 1.1);
 h1[9] = new TH1F(label[9],"E1/E25"  ,100, 0.2, 1.1);
 h1[10] = new TH1F(label[10] ,"E9/E25"  ,100, 0.4, 1.1);

 h1[11] = new TH1F(label[11],"#frac{E_{Barrel}}{E_{Inci}}", 100 , 0.8 , 1.02);


 float  ebcluster[5];

 for (Int_t i=0;i<nev;i++) {
    branch -> GetEntry(i);
    ebcluster[0] = EcalInfo.eb1x1();
    ebcluster[1] = EcalInfo.eb2x2();
    ebcluster[2] = EcalInfo.eb3x3();
    ebcluster[3] = EcalInfo.eb4x4();
    ebcluster[4] = EcalInfo.eb5x5();
    //transvers profile
    for (int j =0; j<5; j++) {  h1[j]->Fill( ebcluster[j]); }
    //ratio of transvers profile
    if( (ebcluster[1] != 0) &&  (ebcluster[2] != 0) && (ebcluster[3] != 0)  && (ebcluster[4] != 0)  ){
         h1[5] ->Fill(ebcluster[0]/ebcluster[1]);
         h1[6] ->Fill(ebcluster[1]/ebcluster[2]);
         h1[7] ->Fill(ebcluster[2]/ebcluster[3]);
         h1[8] ->Fill(ebcluster[3]/ebcluster[4]);
         h1[9] ->Fill(ebcluster[0]/ebcluster[4]);
         h1[10]->Fill(ebcluster[2]/ebcluster[4]);
    }
 }

 float ee,be, se, pe;
 for ( int j = 0; j < nev; j++){
   branch -> GetEntry(j);
   pe = EcalInfo.momentum().e();
   ee = EcalInfo.eInEE();
   be = EcalInfo.eInEB();
   se = EcalInfo.eInES();
   float tote = be + ee +se;
   h1[11]->Fill(be/pe);
 }

 //2-Dimention Histograms
 static const int NHisto2 = 2;

  char* label2[NHisto2];
  label2[0] = "Barrel_Longitudinal";
  label2[1] = "Barrel_Occupancy";

 TH2F* h2[NHisto2];
 h2[0] = new TH2F(label2[0], "Longitudinal Profile",26,0,26, 100, 0, 3000);
 h2[1] = new TH2F(label2[1], "Occupancy", 100, -3, 3, 100,-3.15, 3.15);


 //Barrel longitudianl profile.
 float eRLength[26];
 for ( int i = 0; i<26; i++) { eRLength[i] = 0.0; }
 for ( int j = 0; j< nev; j++) {
   branch ->GetEntry(j);
   if ( EcalInfo.eb1x1() != 0 ) {
       std::vector<float>  X0 = EcalInfo.bX0();
       for (Int_t ii=0;ii< 26;ii++ ) { eRLength[ii] += X0[ii]; }
   }
 }

 for ( int n = 0; n< 26; n++){ h2[0]->Fill(n , eRLength[n]/nev); }
 
 //Barrel Occupancy distribution.
 std::vector<float>  eta;
 std::vector<float>  phi;
 int  totalhits;

 for ( int j = 0; j < nev; j++){
    branch ->GetEntry(j);
    totalhits = EcalInfo.hitsInEB();
    eta = EcalInfo.etaOfEBHits();
    phi = EcalInfo.phiOfEBHits();
    for (int i = 0; i<totalhits;i++){ h2[1]->Fill(eta[i], phi[i]); }
 }


 TFile OutFile("EcalSimHitHisto_30GeV_Barrel.root","RECREATE") ;

  for ( int ih  =0; ih < NHisto;  ih++ )  { h1[ih] ->Write(); }
  for ( int ih2 =0; ih2< NHisto2; ih2++ ) { h2[ih2]->Write(); }

  OutFile.Write() ;
  OutFile.Close() ;

  cout << "Histogram file created!! " << endl ; 

}

