#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH2F.h"
#include "TH2F.h"

void Simhit30GeV_Endcap(TString inputfile="simhitoutput.root",
                        TString outputfile="EcalSimHitHisto_30GeV_Endcap.root")
{
// char* filename ="simhitoutput.root";
 char * treename="Events";
 TFile * file = new TFile(inputfile);
 TTree * events = dynamic_cast<TTree*>(file->Get("Events"));
 assert(events != 0);
 TBranch * branch = events->GetBranch( "PEcalValidInfo_g4SimHits_EcalValidInfo_EcalHitsValid.obj");
 assert(branch != 0);
 int nev = events->GetEntries();

 PEcalValidInfo  EcalInfo;
 branch->SetAddress( &EcalInfo);

 branch ->GetEntry(1);
 float  TotalE = EcalInfo.momentum().e();

 //1-Dimension Histograms.
 const int NHisto = 23; 
 char* label[NHisto];
 
 label[0] = "Ecal_EEOverETotal";
 label[1] = "Ecal_EPOverETotal";
 label[2] = "Ecal_EBEEEPOverETotal";
 label[3] = "PreShower_EHit_L1zp";
 label[4] = "PreShower_EHit_L2zp";
 label[5] = "Preshower_NHit_L1zp";
 label[6] = "Preshower_NHit_L2zp";
 label[7] = "Endcap_E1x1";
 label[8] = "Endcap_E2x2";
 label[9] = "Endcap_E3x3";
 label[10] = "Endcap_E4x4";
 label[11] = "Endcap_E5x5";
 label[12] = "Endcap_E1OverE4";
 label[13] = "Endcap_E4OverE9";
 label[14] = "Endcap_E9OverE16";
 label[15] = "Endcap_E16OverE25";
 label[16] = "Endcap_E1OverE25";
 label[17] = "Endcap_E9OverE25";
 label[18] = "Preshower_E1alphaE2_zp";
 label[19] = "Preshower_E2OverE1_zp";
 label[20] = "EndcapZPlus_HitMultiplicity";
 label[21] = "EndcapZPlus_HitEnergy";
 label[22] = "EndcapZPlus_CryMultiplicity";


 TH1F * h1[NHisto];
 

 h1[0] = new TH1F(label[0],"#frac{E_{Endcap}}{E_{Inci}}", 100 , 0.8 , 1.02);
 h1[1] = new TH1F(label[1],"#frac{E_{Preshower}}{E_{Inci}}", 100 , 0. , 0.001);
 h1[2] = new TH1F(label[2],"#frac{E_{Barrel}+E_{Endcap}+ E_{Preshower}}{E_{Inci}}", 100 , 0.8 , 1.02);

 h1[3] = new TH1F(label[3], "Energy Sepctrum of the 1st Layer",50, 0, 10);
 h1[4] = new TH1F(label[4], "Energy Sepctrum of the 2nd Layer",50, 0, 10);;
 h1[5] = new TH1F(label[5], "Multiplicity of the 1st Layer",50, 0, 30);
 h1[6] = new TH1F(label[6], "Multiplicity of the 2nd Layer",50, 0, 30);

 h1[7] = new TH1F(label[7],"E1x1",50, 0.8e+4, 3.5e+4);
 h1[8] = new TH1F(label[8],"E2x2",50, 0.8e+4, 3.5e+4);
 h1[9] = new TH1F(label[9],"E3x3",50, 0.8e+4, 3.5e+4);
 h1[10] = new TH1F(label[10],"E4x4",50, 0.8e+4, 3.5e+4);
 h1[11] = new TH1F(label[11],"E5x5",50, 0.8e+4, 3.5e+4);

 h1[12] =new TH1F(label[12],"E1/E4"   ,100, 0.2, 1.1);
 h1[13] = new TH1F(label[13],"E4/E9"   ,100, 0.4, 1.1);
 h1[14] = new TH1F(label[14],"E9/E16"  ,100, 0.4, 1.1);
 h1[15] = new TH1F(label[15],"E16/E25" ,100, 0.4, 1.1);
 h1[16] = new TH1F(label[16],"E1/E25"  ,100, 0.2, 1.1);
 h1[17] = new TH1F(label[17] ,"E9/E25"  ,100, 0.4, 1.1);
 h1[18] = new TH1F(label[18], "(E1+ 0.7*E2) in ZPlus",30, 0, 50);
 h1[19] = new TH1F(label[19], "E2/E1 in ZPlus",50, 0, 10);

 h1[20] = new TH1F(label[20], "Endcap Zplus Hit Multiplicity",50, 0, 600);
 h1[21] = new TH1F(label[21], "Endcap Zplus Hit Energy Spectrum",50, 0, 30000);
 h1[22] = new TH1F(label[22], "Endcap Zplus Crystal Multiplicity",50, 0, 300);



 float ee,be, se, pe;
 for ( int j = 0; j < nev; j++){
   branch -> GetEntry(j);
   pe = EcalInfo.momentum().e();
   ee = EcalInfo.eInEE();
   be = EcalInfo.eInEB();
   se = EcalInfo.eInES();
   float tote = be + ee +se;
   h1[0]->Fill(ee/pe);
   h1[1]->Fill(se/pe);
   h1[2]->Fill(tote/pe);
 }

 // Energy spectrum and Multiplicity in ZPlus side of Preshower
 int nhit1es , nhit2es;
 std::vector<float>  ehit1es;
 std::vector<float>  ehit2es;

 for ( int j = 0; j < nev; j++){
   branch ->GetEntry(j);
   nhit1es = EcalInfo.hitsIn1ESzp();
   ehit1es = EcalInfo.eIn1ESzp();
   nhit2es = EcalInfo.hitsIn2ESzp();
   ehit2es = EcalInfo.eIn2ESzp();

   for (int i = 0; i<nhit1es;i++){ h1[3]->Fill(ehit1es[i]); }
   for (int i = 0; i<nhit2es;i++){ h1[4]->Fill(ehit2es[i]); }
   h1[5]->Fill(nhit1es);
   h1[6]->Fill(nhit2es);
 }


 //Transvers Profiles in Endcap
 float  eecluster[5];
 std::vector<float>  ehiteezp;
 int nhiteezp;
 int ncryeezp;

 for (Int_t i=0;i<nev;i++) {
    branch -> GetEntry(i);
    eecluster[0] = EcalInfo.ee1x1();
    eecluster[1] = EcalInfo.ee2x2();
    eecluster[2] = EcalInfo.ee3x3();
    eecluster[3] = EcalInfo.ee4x4();
    eecluster[4] = EcalInfo.ee5x5();
    //transvers profile
    for (int j =0; j<5; j++) {  h1[j+7]->Fill( eecluster[j]); }
    //ratio of transvers profile
    if( (eecluster[1] != 0) &&  (eecluster[2] != 0) && (eecluster[3] != 0)  && (eecluster[4] != 0)  ){
         h1[12] ->Fill(eecluster[0]/eecluster[1]);
         h1[13] ->Fill(eecluster[1]/eecluster[2]);
         h1[14] ->Fill(eecluster[2]/eecluster[3]);
         h1[15] ->Fill(eecluster[3]/eecluster[4]);
         h1[16] ->Fill(eecluster[0]/eecluster[4]);
         h1[17]->Fill(eecluster[2]/eecluster[4]);
    }
    
    ehiteezp = EcalInfo.eOfEEPlusHits();
    ncryeezp = EcalInfo.crystalInEEzp();
    nhiteezp = ehiteezp.size();
    h1[20] -> Fill( nhiteezp );
    for ( int n=0; n<nhiteezp; n++) {
       h1[21] -> Fill ( ehiteezp[n] );
    }
    h1[22] -> Fill( ncryeezp );



 }

 //2-Dimention Histograms
 const int NHisto2 = 2;

  char* label2[NHisto2];
  label2[0] = "Endcap_Longitudinal";
  label2[1] = "Endcap_Occupancy";


 TH2F* h2[NHisto2];
 h2[0] = new TH2F(label2[0], "Longitudinal Profile",26,0,26, 100, 0, 3000);
 h2[1] = new TH2F(label2[1], "Occupancy", 100, -3, 3, 100,-3.15, 3.15);

 //Endcap Longitudinal profile
 float eRLength[26];
 for ( int i = 0; i<26; i++) { eRLength[i] = 0.0; }
 for ( int j = 0; j< nev; j++) {
   branch ->GetEntry(j);
   if ( EcalInfo.ee1x1() != 0 ) {
       std::vector<float>  X0 = EcalInfo.eX0();
       for (Int_t ii=0;ii< 26;ii++ ) { eRLength[ii] += X0[ii]; }
   }
 }
 for ( int n = 0; n< 26; n++){ h2[0]->Fill(n , eRLength[n]/nev); }



 //Endcap Occupancy distribution.
 std::vector<float>  eta2;
 std::vector<float>  phi2;
 int  totalhits2;

 for ( int j = 0; j < nev; j++){
    branch ->GetEntry(j);
    totalhits2 = EcalInfo.hitsInEE();
    eta2 = EcalInfo.etaOfEEHits();
    phi2 = EcalInfo.phiOfEEHits();
    for (int i = 0; i<totalhits2;i++){ h2[1]->Fill(eta2[i], phi2[i]); }
 }


 //TProfiles 
  const int NHisto3 = 1;
  char* label3[NHisto3];
  label3[0] = "Preshower_EEOverES_zp";


 TProfile*  pro[NHisto3];
 pro[0] = new TProfile(label3[0],"Preshower EE vs ES energy z+(sample)"   ,100, 0, 300., 0., 35000.);

 for ( int j = 0; j < nev; j++){
    int nhit1eszp;
    int nhit2eszp;
    float totale1eszp=0.;
    float totale2eszp=0.;
    float totaleeezp =0.;

    std::vector<float>  ehit1eszp;
    std::vector<float>  ehit2eszp;

    branch ->GetEntry(j);
    nhit1eszp = EcalInfo.hitsIn1ESzp();
    ehit1eszp = EcalInfo.eIn1ESzp();
    nhit2eszp = EcalInfo.hitsIn2ESzp();
    ehit2eszp = EcalInfo.eIn2ESzp();
    totaleeezp = EcalInfo.eInEEzp();


    double theta = EcalInfo.momentum().vect().theta();
    double peta   = -log(tan(theta * 0.5));

   for (int i = 0; i<nhit1eszp;i++){ totale1eszp += ehit1eszp[i]; }
   for (int i = 0; i<nhit2eszp;i++){ totale2eszp += ehit2eszp[i]; }
   if ( peta > 1.653 && peta < 2.6 )  {
       pro[0]->Fill((totale1eszp+0.7*totale2eszp)/0.09,totaleeezp);
       h1[18]->Fill(totale1eszp+0.7*totale2eszp);
       if( totale1eszp != 0.0) h1[19]->Fill(totale2eszp/totale1eszp);

   } 
 }

 cout<<"Total E = "<<TotalE<<endl;

  TFile OutFile("EcalSimHitHisto_30GeV_Endcap.root","RECREATE") ;
  for ( int ih  =0; ih < NHisto;  ih++ )  { h1[ih] ->Write(); }
  for ( int ih2 =0; ih2< NHisto2; ih2++ ) { h2[ih2]->Write(); }
  for ( int ih3 =0; ih3< NHisto3; ih3++ ) { pro[ih3] ->Write(); }

  OutFile.Write() ;
  OutFile.Close() ;

  cout << "Histogram file created!! " << endl ; 

}

