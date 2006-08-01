#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH2F.h"
#include "TH2F.h"

void Simhit30GeV_all()
{
 char* filename ="simhitoutput.root";
 char * treename="Events";
 TFile * file = new TFile(filename);
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
 static const int NHisto = 38; 
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
 label[12] = "Ecal_EEOverETotal";
 label[13] = "Ecal_EPOverETotal";
 label[14] = "Ecal_EBEEEPOverETotal";
 label[15] = "PreShower_EHit_L1zp";
 label[16] = "PreShower_EHit_L2zp";
 label[17] = "Preshower_NHit_L1zp";
 label[18] = "Preshower_NHit_L2zp";
 label[19] = "Endcap_E1x1";
 label[20] = "Endcap_E2x2";
 label[21] = "Endcap_E3x3";
 label[22] = "Endcap_E4x4";
 label[23] = "Endcap_E5x5";
 label[24] = "Endcap_E1OverE4";
 label[25] = "Endcap_E4OverE9";
 label[26] = "Endcap_E9OverE16";
 label[27] = "Endcap_E16OverE25";
 label[28] = "Endcap_E1OverE25";
 label[29] = "Endcap_E9OverE25";
 label[30] = "PreShower_EHit_L1zm";
 label[31] = "PreShower_EHit_L2zm";
 label[32] = "Preshower_NHit_L1zm";
 label[33] = "Preshower_NHit_L2zm";
 label[34] = "Preshower_E1alphaE2_zm";
 label[35] = "Preshower_E1alphaE2_zp";
 label[36] = "Preshower_E2OverE1_zm";
 label[37] = "Preshower_E2OverE1_zp";


 TH1F * h1[NHisto];
 
 h1[0] = new TH1F(label[0],"E1x1",50, 0.8e+4, 3.5e+4);
 h1[1] = new TH1F(label[1],"E2x2",50, 0.8e+4, 3.5e+4);
 h1[2] = new TH1F(label[2],"E3x3",50, 0.8e+4, 3.5e+4);
 h1[3] = new TH1F(label[3],"E4x4",50, 0.8e+4, 3.5e+4);
 h1[4] = new TH1F(label[4],"E5x5",50, 0.8e+4, 3.5e+4);

 h1[5] = new TH1F(label[5],"E1/E4"   ,50, 0.2, 1.1);
 h1[6] = new TH1F(label[6],"E4/E9"   ,50, 0.4, 1.1);
 h1[7] = new TH1F(label[7],"E9/E16"  ,50, 0.4, 1.1);
 h1[8] = new TH1F(label[8],"E16/E25" ,50, 0.4, 1.1);
 h1[9] = new TH1F(label[9],"E1/E25"  ,50, 0.2, 1.1);
 h1[10] = new TH1F(label[10] ,"E9/E25"  ,100, 0.4, 1.1);

 h1[11] = new TH1F(label[11],"#frac{E_{Barrel}}{E_{Inci}}", 60 , 0.8 , 1.02);
 h1[12] = new TH1F(label[12],"#frac{E_{Endcap}}{E_{Inci}}", 60 , 0.8 , 1.02);
 h1[13] = new TH1F(label[13],"#frac{E_{Preshower}}{E_{Inci}}", 60 , 0. , 0.001);
 h1[14] = new TH1F(label[14],"#frac{E_{Barrel}+E_{Endcap}+ E_{Preshower}}{E_{Inci}}", 60 , 0.8 , 1.02);

 h1[15] = new TH1F(label[15], "Energy Sepctrum of the 1st Layer",50, 0, 10);
 h1[16] = new TH1F(label[16], "Energy Sepctrum of the 2nd Layer",50, 0, 10);;
 h1[17] = new TH1F(label[17], "Multiplicity of the 1st Layer",50, 0, 30);
 h1[18] = new TH1F(label[18], "Multiplicity of the 2nd Layer",50, 0, 30);

 h1[19] = new TH1F(label[19],"E1x1",50, 0.8e+4, 3.5e+4);
 h1[20] = new TH1F(label[20],"E2x2",50, 0.8e+4, 3.5e+4);
 h1[21] = new TH1F(label[21],"E3x3",50, 0.8e+4, 3.5e+4);
 h1[22] = new TH1F(label[22],"E4x4",50, 0.8e+4, 3.5e+4);
 h1[23] = new TH1F(label[23],"E5x5",50, 0.8e+4, 3.5e+4);

 h1[24] =new TH1F(label[24],"E1/E4"   ,50, 0.2, 1.1);
 h1[25] = new TH1F(label[25],"E4/E9"   ,50, 0.4, 1.1);
 h1[26] = new TH1F(label[26],"E9/E16"  ,50, 0.4, 1.1);
 h1[27] = new TH1F(label[27],"E16/E25" ,50, 0.4, 1.1);
 h1[28] = new TH1F(label[28],"E1/E25"  ,50, 0.2, 1.1);
 h1[29] = new TH1F(label[29] ,"E9/E25"  ,50, 0.4, 1.1);


 h1[30] = new TH1F(label[30], "Energy Sepctrum of the 1st Layer",50, 0, 10);
 h1[31] = new TH1F(label[31], "Energy Sepctrum of the 2nd Layer",50, 0, 10);;
 h1[32] = new TH1F(label[32], "Multiplicity of the 1st Layer",20, 0, 30);
 h1[33] = new TH1F(label[33], "Multiplicity of the 2nd Layer",20, 0, 30);

 h1[34] = new TH1F(label[34], "(E1+ 0.7*E2) in ZMius",30, 0, 50);
 h1[35] = new TH1F(label[35], "(E1+ 0.7*E2) in ZPlus",30, 0, 50);

 h1[36] = new TH1F(label[36], "E2/E1 in ZMius",50, 0, 10);
 h1[37] = new TH1F(label[37], "E2/E1 in ZPlus",50, 0, 10);


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
   h1[12]->Fill(ee/pe);
   h1[13]->Fill(se/pe);
   h1[14]->Fill(tote/pe);
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

   for (int i = 0; i<nhit1es;i++){ h1[15]->Fill(ehit1es[i]); }
   for (int i = 0; i<nhit2es;i++){ h1[16]->Fill(ehit2es[i]); }
   h1[17]->Fill(nhit1es);
   h1[18]->Fill(nhit2es);
 }


// Energy spectrum and Multiplicity in ZMinus side of Preshower
 for ( int j = 0; j < nev; j++){
   branch ->GetEntry(j);
   nhit1es = EcalInfo.hitsIn1ESzm();
   ehit1es = EcalInfo.eIn1ESzm();
   nhit2es = EcalInfo.hitsIn2ESzm();
   ehit2es = EcalInfo.eIn2ESzm();

   for (int i = 0; i<nhit1es;i++){ h1[30]->Fill(ehit1es[i]); }
   for (int i = 0; i<nhit2es;i++){ h1[31]->Fill(ehit2es[i]); }
   h1[32]->Fill(nhit1es);
   h1[33]->Fill(nhit2es);
 }


 //Transvers Profiles in Endcap
 float  eecluster[5];

 for (Int_t i=0;i<nev;i++) {
    branch -> GetEntry(i);
    eecluster[0] = EcalInfo.ee1x1();
    eecluster[1] = EcalInfo.ee2x2();
    eecluster[2] = EcalInfo.ee3x3();
    eecluster[3] = EcalInfo.ee4x4();
    eecluster[4] = EcalInfo.ee5x5();
    //transvers profile
    for (int j =0; j<5; j++) {  h1[j+19]->Fill( eecluster[j]); }
    //ratio of transvers profile
    if( (eecluster[1] != 0) &&  (eecluster[2] != 0) && (eecluster[3] != 0)  && (eecluster[4] != 0)  ){
         h1[24] ->Fill(eecluster[0]/eecluster[1]);
         h1[25] ->Fill(eecluster[1]/eecluster[2]);
         h1[26] ->Fill(eecluster[2]/eecluster[3]);
         h1[27] ->Fill(eecluster[3]/eecluster[4]);
         h1[28] ->Fill(eecluster[0]/eecluster[4]);
         h1[29]->Fill(eecluster[2]/eecluster[4]);
    }
 }

 //2-Dimention Histograms
 static const int NHisto2 = 4;

  char* label2[NHisto2];
  label2[0] = "Barrel_Longitudinal";
  label2[1] = "Barrel_Occupancy";
  label2[2] = "Endcap_Longitudinal";
  label2[3] = "Endcap_Occupancy";


 TH2F* h2[NHisto2];
 h2[0] = new TH2F(label2[0], "Longitudinal Profile",26,0,26, 100, 0, 3000);
 h2[1] = new TH2F(label2[1], "Occupancy", 100, -3, 3, 100,-3.15, 3.15);
 h2[2] = new TH2F(label2[2], "Longitudinal Profile",26,0,26, 100, 0, 3000);
 h2[3] = new TH2F(label2[3], "Occupancy", 100, -3, 3, 100,-3.15, 3.15);



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

 //Endcap Longitudinal profile
 for ( int i = 0; i<26; i++) { eRLength[i] = 0.0; }
 for ( int j = 0; j< nev; j++) {
   branch ->GetEntry(j);
   if ( EcalInfo.ee1x1() != 0 ) {
       std::vector<float>  X0 = EcalInfo.eX0();
       for (Int_t ii=0;ii< 26;ii++ ) { eRLength[ii] += X0[ii]; }
   }
 }
 for ( int n = 0; n< 26; n++){ h2[2]->Fill(n , eRLength[n]/nev); }



 //Endcap Occupancy distribution.
 std::vector<float>  eta2;
 std::vector<float>  phi2;
 int  totalhits2;

 for ( int j = 0; j < nev; j++){
    branch ->GetEntry(j);
    totalhits2 = EcalInfo.hitsInEE();
    eta2 = EcalInfo.etaOfEEHits();
    phi2 = EcalInfo.phiOfEEHits();
    for (int i = 0; i<totalhits2;i++){ h2[3]->Fill(eta2[i], phi2[i]); }
 }


 //TProfiles 
  static const int NHisto3 = 2;
  char* label3[NHisto3];
  label3[0] = "Preshower_EEOverES_zp";
  label3[1] = "Preshower_EEOverES_zm";


 TProfile*  pro[NHisto3];
 pro[0] = new TProfile(label3[0],"Preshower EE vs ES energy z+(sample)"   ,100, 0, 300., 0., 35000.);
 pro[1] = new TProfile(label3[1],"Preshower EE vs ES energy z-(sample)"   ,100, 0, 300., 0., 35000.);

 for ( int j = 0; j < nev; j++){
    int nhit1eszm;
    int nhit2eszm;
    int nhit1eszp;
    int nhit2eszp;
    float totale1eszm=0.;
    float totale2eszm=0.;
    float totaleeezm =0.;
    float totale1eszp=0.;
    float totale2eszp=0.;
    float totaleeezp =0.;

    std::vector<float>  ehit1eszm;
    std::vector<float>  ehit2eszm;
    std::vector<float>  ehit1eszp;
    std::vector<float>  ehit2eszp;

    branch ->GetEntry(j);
    nhit1eszm = EcalInfo.hitsIn1ESzm();
    ehit1eszm = EcalInfo.eIn1ESzm();
    nhit2eszm = EcalInfo.hitsIn2ESzm();
    ehit2eszm = EcalInfo.eIn2ESzm();
    totaleeezm =EcalInfo.eInEEzm();

    nhit1eszp = EcalInfo.hitsIn1ESzp();
    ehit1eszp = EcalInfo.eIn1ESzp();
    nhit2eszp = EcalInfo.hitsIn2ESzp();
    ehit2eszp = EcalInfo.eIn2ESzp();
    totaleeezp = EcalInfo.eInEEzp();


    double theta = EcalInfo.momentum().vect().theta();
    double peta   = -log(tan(theta * 0.5));

   for (int i = 0; i<nhit1eszm;i++){ totale1eszm += ehit1eszm[i]; }
   for (int i = 0; i<nhit2eszm;i++){ totale2eszm += ehit2eszm[i]; }
   for (int i = 0; i<nhit1eszp;i++){ totale1eszp += ehit1eszp[i]; }
   for (int i = 0; i<nhit2eszp;i++){ totale2eszp += ehit2eszp[i]; }
   if ( peta > -2.6 && peta< -1.653 )  {
          pro[0]->Fill((totale1eszm+0.7*totale2eszm)/0.09,totaleeezm);
          h1[34]->Fill(totale1eszm+0.7*totale2eszm);
          if(totale1eszm != 0.0) h1[36]->Fill(totale2eszm/totale1eszm);         
   }

   if ( peta > 1.653 && peta < 2.6 )  {
         pro[1]->Fill((totale1eszp+0.7*totale2eszp)/0.09,totaleeezp);
         h1[35]->Fill(totale1eszp+0.7*totale2eszp);
         if( totale1eszp != 0.0) h1[37]->Fill(totale2eszp/totale1eszp);
   }
 }

 cout<<"Total E = "<<TotalE<<endl;

 TFile OutFile("EcalSimHitHisto_30GeV.root","RECREATE") ;

  for ( int ih  =0; ih < NHisto;  ih++ )  { h1[ih] ->Write(); }
  for ( int ih2 =0; ih2< NHisto2; ih2++ ) { h2[ih2]->Write(); }
  for ( int ih3 =0; ih3< NHisto3; ih3++ ) { pro[ih3] ->Write(); }

  OutFile.Write() ;
  OutFile.Close() ;

  cout << "Histogram file created!! " << endl ; 

}

