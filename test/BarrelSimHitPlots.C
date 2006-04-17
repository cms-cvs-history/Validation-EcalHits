#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH2F.h"
#include "TH2F.h"

void BarrelSimHitPlots()
{

  gROOT ->Reset();
 char* sfilename ="$SAMPLEFILE";
 char* rfilename ="$REFERFILE"; 
 char * treename="Events";        //The Title of Tree.

 delete gROOT->GetListOfFiles()->FindObject(sfilename);
 delete gROOT->GetListOfFiles()->FindObject(rfilename);
 
 TText* te = new TText();
 te->SetTextSize(0.1);
 
 TFile * sfile = new TFile(sfilename);
 TFile * rfile = new TFile(rfilename);

 TTree * sevents = dynamic_cast<TTree*>(sfile->Get("Events"));
 assert(sevents != 0);
 TTree * revents = dynamic_cast<TTree*>(rfile->Get("Events"));
 assert(revents != 0);

 TBranch * sbranch = sevents->GetBranch( "PEcalValidInfo_r_EcalValidInfo.obj");
 assert(sbranch != 0);
 TBranch * rbranch = revents->GetBranch( "PEcalValidInfo_r_EcalValidInfo.obj");
 assert(rbranch != 0);

 int snev = sevents->GetEntries();
 int rnev = revents->GetEntries();

 PEcalValidInfo  sEcalInfo;
 sbranch->SetAddress( &sEcalInfo);

 PEcalValidInfo  rEcalInfo;
 rbranch->SetAddress( &rEcalInfo);

//Check the Energy of Particle
   sbranch ->GetEntry(1);
   float sampleE = sEcalInfo.momentum().e();
   rbranch ->GetEntry(1);
   float referE = sEcalInfo.momentum().e();
   if ( sampleE != referE ) {
       std::cout<<"Warning:: The Sample and reference sample use different Energy of incident Particle!!"<<std::endl;
       return;
    }


////////////////////////////////////////////////////////////////
//                                                            //
//     Plot Histograms for three kinds of sub-detectors       // 
//                                                            //
////////////////////////////////////////////////////////////////

//Barrel's  Transverse Profile of showers

if (1) {

 TCanvas * Ecal = new TCanvas("Ecal","Ecal",800,1000);
 Ecal->Divide(2,3);

 float se[5],re[5];
 TH1F*  she1[5];
 TH1F*  rhe1[5];

  she1[0] = new TH1F("barrel_sample_e1","E1x1",50, 0.8e+4, 3.5e+4);
  she1[1] = new TH1F("barrel_sample_e4","E2x2",50, 0.8e+4, 3.5e+4);
  she1[2] = new TH1F("barrel_sample_e9","E3x3",50, 0.8e+4, 3.5e+4);
  she1[3] = new TH1F("barrel_sample_e16","E4x4",50, 0.8e+4, 3.5e+4);
  she1[4] = new TH1F("barrel_sample_e25","E5x5",50, 0.8e+4, 3.5e+4);

  rhe1[0] = new TH1F("barrel_ref_e1","E1x1",50, 0.8e+4, 3.5e+4);
  rhe1[1] = new TH1F("barrel_ref_e4","E2x2",50, 0.8e+4, 3.5e+4);
  rhe1[2] = new TH1F("barrel_ref_e9","E3x3",50, 0.8e+4, 3.5e+4);
  rhe1[3] = new TH1F("barrel_ref_e16","E4x4",50, 0.8e+4, 3.5e+4);
  rhe1[4] = new TH1F("barrel_ref_e25","E5x5",50, 0.8e+4, 3.5e+4);

 for ( int n=0; n<5; n++){
        she1[n]->GetXaxis()->SetTitle("MeV");
        she1[n]->GetXaxis()->CenterTitle(true);
        she1[n]->GetYaxis()->SetTitle("Counts");
        she1[n]->GetYaxis()->CenterTitle(true);
        rhe1[n]->GetXaxis()->SetTitle("MeV");
        rhe1[n]->GetXaxis()->CenterTitle(true);
        rhe1[n]->GetYaxis()->SetTitle("Counts");
        rhe1[n]->GetYaxis()->CenterTitle(true);
 }

 for (Int_t i=0;i<snev;i++) {
    sbranch -> GetEntry(i);
    se[0] = sEcalInfo.eb1x1();
    se[1] = sEcalInfo.eb2x2();
    se[2] = sEcalInfo.eb3x3();
    se[3] = sEcalInfo.eb4x4();
    se[4] = sEcalInfo.eb5x5();

    for (int j =0; j<5; j++) {
          she1[j]->Fill( se[j]);
    }
 }

 for (Int_t i=0;i<rnev;i++) {
    rbranch -> GetEntry(i);
    re[0] = rEcalInfo.eb1x1();
    re[1] = rEcalInfo.eb2x2();
    re[2] = rEcalInfo.eb3x3();
    re[3] = rEcalInfo.eb4x4();
    re[4] = rEcalInfo.eb5x5();

    for (int j =0; j<5; j++) {
          rhe1[j]->Fill( re[j]);
    }
 }
for( int i =0 ;i<5; i++){
   she1[i]->SetLineColor(2);
   rhe1[i]->SetLineColor(4);
   rhe1[i]->SetLineStyle(2);
 }

  for(int i =0 ; i<5; i++ ) {
    Ecal->cd(i+1);
    she1[i]->Draw();
    rhe1[i]->Draw("sames");

    double pv = rhe1[i]->Chi2Test(she1[i],"OU");
    std::strstream buf;
    std::string value;
    buf<<"PV="<<pv<<std::endl;
    buf>>value;
    te->DrawTextNDC(0.2,0.7, value.c_str());
    std::cout << "[OVAL] " << rhe1[i]->GetName() << " PV = " << pv << std::endl;
  }

 Ecal->Print("Barrel_Transverse.eps");
}


 //Barrel's Ratios of the Energy Depostion in different Clusters

if (1) { 

 TCanvas * Ecal = new TCanvas("Ecal","Ecal",800,1000);
 Ecal->Divide(2,3);

 TH1F*  she2[6];
 TH1F*  rhe2[6];
	    
 she2[0] = new TH1F("barrel_sample_e1/e4"  ,"E1/E4"   ,100, 0.4, 1.1);
 she2[1] = new TH1F("barrel_sample_e4/e9"  ,"E4/E9"   ,100, 0.4, 1.1);
 she2[2] = new TH1F("barrel_sample_e9/e16" ,"E9/E16"  ,100, 0.4, 1.1);
 she2[3] = new TH1F("barrel_sample_e16/e25","E16/E25" ,100, 0.4, 1.1);
 she2[4] = new TH1F("barrel_sample_e1/e25" ,"E1/E25"  ,100, 0.4, 1.1);
 she2[5] = new TH1F("barrel_sample_e9/e25" ,"E9/E25"  ,100, 0.4, 1.1);

 rhe2[0] = new TH1F("barrel_ref_e1/e4"  ,"E1/E4"   ,100, 0.4, 1.1);
 rhe2[1] = new TH1F("barrel_ref_e4/e9"  ,"E4/E9"   ,100, 0.4, 1.1);
 rhe2[2] = new TH1F("barrel_ref_e9/e16" ,"E9/E16"  ,100, 0.4, 1.1);
 rhe2[3] = new TH1F("barrel_ref_e16/e25","E16/E25" ,100, 0.4, 1.1);
 rhe2[4] = new TH1F("barrel_ref_e1/e25" ,"E1/E25"  ,100, 0.4, 1.1);
 rhe2[5] = new TH1F("barrel_ref_e9/e25" ,"E9/E25"  ,100, 0.4, 1.1);
	  
 for (int n =0; n<6;n++){
  she2[n]->GetXaxis()->SetTitle("Ratio");
  she2[n]->GetYaxis()->SetTitle("Counts");
  she2[n]->GetXaxis()->CenterTitle(true);
  she2[n]->GetYaxis()->CenterTitle(true);
  rhe2[n]->GetXaxis()->SetTitle("Ratio");
  rhe2[n]->GetYaxis()->SetTitle("Counts");
  rhe2[n]->GetXaxis()->CenterTitle(true);
  rhe2[n]->GetYaxis()->CenterTitle(true);
 }


 for (Int_t i=0;i<rnev;i++) {
  sbranch->GetEntry( i);
  float se[5];
  se[0] = sEcalInfo.eb1x1();
  se[1] = sEcalInfo.eb2x2();
  se[2] = sEcalInfo.eb3x3();
  se[3] = sEcalInfo.eb4x4();
  se[4] = sEcalInfo.eb5x5();

  rbranch->GetEntry( i);
  float re[5];
  re[0] = rEcalInfo.eb1x1();
  re[1] = rEcalInfo.eb2x2();
  re[2] = rEcalInfo.eb3x3();
  re[3] = rEcalInfo.eb4x4();
  re[4] = rEcalInfo.eb5x5();

  if( (se[1] != 0) &&  (se[2] != 0) && (se[3] != 0)  && (se[4] != 0)  ){  
      she2[0]->Fill(se[0]/se[1]);
      she2[1]->Fill(se[1]/se[2]);
      she2[2]->Fill(se[2]/se[3]);
      she2[3]->Fill(se[3]/se[4]);
      she2[4]->Fill(se[0]/se[4]);
      she2[5]->Fill(se[2]/se[4]);
  }
  if( re[1] != 0 && re[2] != 0 && re[3] != 0 && re[4] != 0 ) {
      rhe2[0]->Fill(re[0]/re[1]);
      rhe2[1]->Fill(re[1]/re[2]);
      rhe2[2]->Fill(re[2]/re[3]);
      rhe2[3]->Fill(re[3]/re[4]);
      rhe2[4]->Fill(re[0]/re[4]);
      rhe2[5]->Fill(re[2]/re[4]);

  }
 }

  for (int i= 0; i<6; i++){
    she2[i]->SetLineColor(2);
    rhe2[i]->SetLineColor(4);
    rhe2[i]->SetLineStyle(2);
  }


  for(int i =0 ; i<6; i++ ) {
    Ecal->cd(i+1);
    she2[i]->Draw();
    rhe2[i]->Draw("sames");

    double pv = rhe2[i]->Chi2Test(she2[i],"OU");
    std::strstream buf;
    std::string value;
    buf<<"PV="<<pv<<std::endl;
    buf>>value;
    te->DrawTextNDC(0.2,0.7, value.c_str());
    std::cout << "[OVAL] " << rhe2[i]->GetName() << " PV = " << pv << std::endl;
  }

  Ecal->Print("Barrel_ClusterRatio.eps");

 } 

// Barrel's  Longitudinal Profile of Showers

 if (1) {

 TCanvas * Ecal = new TCanvas("Ecal","Ecal",800,600);
 TH2F * slongitudinal = new TH2F("barrel_sample_longi","Longitudinal Profile",26,0,26, 100, 0, 3000);
 slongitudinal->SetMarkerColor(2);
 slongitudinal->SetMarkerStyle(26);
 slongitudinal->GetXaxis()->SetTitle("X0");
 slongitudinal->GetXaxis()->CenterTitle(true);
 slongitudinal->GetYaxis()->SetTitle("MeV");
 slongitudinal->GetYaxis()->CenterTitle(true);

 float ssum[26];
 for ( int i = 0; i<26; i++) {
       ssum[i] = 0.0;
 }

 for ( int j = 0; j< snev; j++) {
   sbranch -> GetEntry(j);
   if ( sEcalInfo.eb1x1() != 0 ) {
       std::vector<float>  X0 = sEcalInfo.bX0();
       for (Int_t ii=0;ii< 26;ii++ ) {
          ssum[ii] += X0[ii];
       }
   }
 }

 TH2F * rlongitudinal = new TH2F("barrel_ref_longi","Longitudinal Profile",26,0,26, 100, 0, 3000);
 rlongitudinal->SetMarkerColor(4);
 rlongitudinal->SetMarkerStyle(30);
 rlongitudinal->GetXaxis()->SetTitle("X0");
 rlongitudinal->GetXaxis()->CenterTitle(true);
 rlongitudinal->GetYaxis()->SetTitle("MeV");
 rlongitudinal->GetYaxis()->CenterTitle(true);
 
 float rsum1[26];
 for ( int i = 0; i<26; i++) {
       rsum1[i] = 0.0;
 }
 for ( int j = 0; j< rnev; j++) {
   rbranch -> GetEntry(j);
   if ( rEcalInfo.eb1x1() != 0 ) {
        std::vector<float>  X0 = rEcalInfo.bX0();
        for (Int_t ii=0;ii< 26;ii++ ) {
            rsum1[ii] += X0[ii];
        }
   }

 }

 for ( int n = 0; n< 26; n++){
    slongitudinal->Fill(n , ssum[n]/snev);
    rlongitudinal->Fill(n , rsum1[n]/rnev);
 }


 slongitudinal->Draw();
 rlongitudinal->Draw("sames");
 
 double pv = rlongitudinal->Chi2Test(slongitudinal,"OU");
 std::strstream buf;
 std::string value;
 buf<<"PV="<<pv<<std::endl;
 buf>>value;

 te->DrawTextNDC(0.5,0.5, value.c_str());
 std::cout << "[OVAL] " << rlongitudinal->GetName() << " PV = " << pv << std::endl;

 Ecal->Print("Barrel_Longitudinal.eps");

 }


// Barrel's fraction of the Energy Depositon 

 if(1) {

TCanvas * Ecal = new TCanvas("Ecal","Ecal",800,1000);
 Ecal->Divide(2,2);

 TH1F * sbp = new TH1F("barrel_sample_eb/ep","#frac{E_{Barrel}}{E_{Inci}}", 50 , 0.8 , 1.0);
 sbp->GetXaxis()->SetTitle("Ratio");
 sbp->GetXaxis()->CenterTitle(true);
 sbp->GetYaxis()->SetTitle("Counts");
 sbp->GetYaxis()->CenterTitle(true);
 sbp->SetLineColor(2);

 TH1F * sep = new TH1F("barrel_sample_ee/ep","#frac{E_{Endcap}}{E_{Inci}}", 50 , 0. , 0.001);
 sep->GetXaxis()->SetTitle("Ratio");
 sep->GetXaxis()->CenterTitle(true);
 sep->GetYaxis()->SetTitle("Counts");
 sep->GetYaxis()->CenterTitle(true);
 sep->SetLineColor(2);


 TH1F * ssp = new TH1F("barrel_sample_es/ep","#frac{E_{Preshower}}{E_{Inci}}", 50 , 0. , 0.001);
 ssp->GetXaxis()->SetTitle("Ratio");
 ssp->GetXaxis()->CenterTitle(true);
 ssp->GetYaxis()->SetTitle("Counts");
 ssp->GetYaxis()->CenterTitle(true);
 ssp->SetLineColor(2);

 TH1F * sssum = new TH1F("barrel_sample_etoal/ep","#frac{E_{Barrel}+E_{Endcap}+ E_{Preshower}}{E_{Inci}}", 50 , 0.8 , 1.0);
 sssum->GetXaxis()->SetTitle("Ratio");
 sssum->GetXaxis()->CenterTitle(true);
 sssum->GetYaxis()->SetTitle("Counts");
 sssum->GetYaxis()->CenterTitle(true);
 sssum->SetLineColor(2);

 TH1F * rbp = new TH1F("barrel_ref_eb/ep","#frac{E_{Barrel}}{E_{Inci}}", 50 , 0.8 , 1.);
 rbp->GetXaxis()->SetTitle("Ratio");
 rbp->GetXaxis()->CenterTitle(true);
 rbp->GetYaxis()->SetTitle("Counts");
 rbp->GetYaxis()->CenterTitle(true);
 rbp->SetLineColor(4);
 rbp->SetLineStyle(2);

 TH1F * rep = new TH1F("barrel_ref_ee/ep","#frac{E_{Endcap}}{E_{Inci}}", 50 , 0. , 0.001);
 rep->GetXaxis()->SetTitle("Ratio");
 rep->GetXaxis()->CenterTitle(true);
 rep->GetYaxis()->SetTitle("Counts");
 rep->GetYaxis()->CenterTitle(true);
 rep->SetLineColor(4);
 rep->SetLineStyle(2);

 TH1F * rsp = new TH1F("barrel_ref_es/ep","#frac{E_{Preshower}}{E_{Inci}}", 50 , 0. , 0.001);
 rsp->GetXaxis()->SetTitle("Ratio");
 rsp->GetXaxis()->CenterTitle(true);
 rsp->GetYaxis()->SetTitle("Counts");
 rsp->GetYaxis()->CenterTitle(true);
 rsp->SetLineColor(4);
 rsp->SetLineStyle(2);

 TH1F * rsum = new TH1F("barrel_ref_etotal/ep","#frac{E_{Barrel}+E_{Endcap}+ E_{Preshower}}{E_{Inci}}", 50 , 0.8 , 1.0);
 rsum->GetXaxis()->SetTitle("Ratio");
 rsum->GetXaxis()->CenterTitle(true);
 rsum->GetYaxis()->SetTitle("Counts");
 rsum->GetYaxis()->CenterTitle(true);
 rsum->SetLineColor(4);
 rsum->SetLineStyle(2);

 float see,sbe, sse, spe;
 float ree,rbe, rse, rpe;

 for ( int j = 0; j < snev; j++){
   sbranch ->GetEntry(j);
   spe = sEcalInfo.momentum().e();
   see = sEcalInfo.eInEE();
   sbe = sEcalInfo.eInEB();
   sse = sEcalInfo.eInES();
   float stote = sbe + see +sse;
   sbp->Fill(sbe/spe);
   sep->Fill(see/spe);
   ssp->Fill(sse/spe);
   sssum->Fill(stote/spe);
 }

 for ( int j = 0; j < rnev; j++){
   rbranch ->GetEntry(j);
   rpe = rEcalInfo.momentum().e();
   ree = rEcalInfo.eInEE();
   rbe = rEcalInfo.eInEB();
   rse = rEcalInfo.eInES();
   float rtote = rbe + ree +rse;
   rbp->Fill(rbe/rpe);
   rep->Fill(ree/rpe);
   rsp->Fill(rse/rpe);
   rsum->Fill(rtote/rpe);
 }
 
 Ecal->cd(1);

 double bpv = rbp->Chi2Test(sbp,"OU");
 std::strstream bbuf;
 std::string bvalue;
 bbuf<<"PV="<<bpv<<std::endl;
 bbuf>>bvalue;

 sbp->Draw();
 rbp->Draw("sames");
 te->DrawTextNDC(0.2,0.7, bvalue.c_str());
 std::cout << "[OVAL] " << rbp->GetName() << " PV = " << pv << std::endl;
 Ecal->cd(2);
 double epv = rep->Chi2Test(sep,"OU");
 std::strstream ebuf;
 std::string evalue;
 ebuf<<"PV="<<epv<<std::endl;
 ebuf>>evalue;

 sep->Draw();
 rep->Draw("sames");
 te->DrawTextNDC(0.2,0.7, evalue.c_str());
 std::cout << "[OVAL] " << rep->GetName() << " PV = " << pv << std::endl;
 Ecal->cd(3);

 double spv = rsp->Chi2Test(ssp,"OU");
 std::strstream sbuf;
 std::string svalue;
 sbuf<<"PV="<<spv<<std::endl;
 sbuf>>svalue;

 ssp->Draw();
 rsp->Draw("sames");
 te->DrawTextNDC(0.2,0.7, svalue.c_str());
 std::cout << "[OVAL] " << rsp->GetName() << " PV = " << pv << std::endl;

 Ecal->cd(4);
 double pv = rsum->Chi2Test(sssum,"OU");
 std::strstream buf;
 std::string value;
 buf<<"PV="<<pv<<std::endl;
 buf>>value;

 sssum->Draw();
 rsum->Draw("sames");
 te->DrawTextNDC(0.2,0.7, value.c_str());
 std::cout << "[OVAL] " << rsum->GetName() << " PV = " << pv << std::endl;

 Ecal->Print("Barrel_Epercentage.eps");

 }

//Barrel's Occupancy of the CaloG4Hits ( Phi vs. Eta)

 if(1){

 TCanvas * Ecal = new TCanvas("Ecal","Ecal",800,1000);
 Ecal->Divide(1,2);

 TH2F*  soccp = new TH2F("barrel_sample_occu", "Occupancy", 100, -3, 3, 100,-3.15, 3.15);
 soccp->SetMarkerColor(8);
 soccp->GetXaxis()->SetTitle("Eta");
 soccp->GetXaxis()->CenterTitle(true);
 soccp->GetYaxis()->SetTitle("Phi");
 soccp->GetYaxis()->CenterTitle(true);

 std::vector<float>  seta;
 std::vector<float>  sphi;
 int  stotalhits;

 for ( int j = 0; j < snev; j++){
    sbranch ->GetEntry(j);
    stotalhits = sEcalInfo.hitsInEB();
    seta = sEcalInfo.etaOfEBHits();
    sphi = sEcalInfo.phiOfEBHits();

   for (int i = 0; i<stotalhits;i++){
     soccp->Fill(seta[i], sphi[i]);
   }

 }
 TH2F*  roccp = new TH2F("barrel_ref_occu", "Occupancy", 100, -3, 3, 100,-3.15, 3.15);
 roccp->SetMarkerColor(8);
 roccp->GetXaxis()->SetTitle("Eta");
 roccp->GetXaxis()->CenterTitle(true);
 roccp->GetYaxis()->SetTitle("Phi");
 roccp->GetYaxis()->CenterTitle(true);

 std::vector<float>  reta;
 std::vector<float>  rphi;
 int  rtotalhits;

 for ( int j = 0; j < rnev; j++){
    rbranch ->GetEntry(j);
    rtotalhits = rEcalInfo.hitsInEB();
    reta = rEcalInfo.etaOfEBHits();
    rphi = rEcalInfo.phiOfEBHits();

   for (int i = 0; i<rtotalhits;i++){
     roccp->Fill(reta[i], rphi[i]);
   }

 }

 double pv = roccp->Chi2Test(soccp,"OU");
 std::strstream buf;
 std::string value;
 buf<<"PV="<<pv<<std::endl;
 buf>>value;

 Ecal->cd(1);
 soccp->SetMarkerColor(2);
 soccp->Draw();
 te->DrawTextNDC(0.2,0.7, value.c_str());
 
 Ecal->cd(2);
 roccp->SetMarkerColor(4);
 roccp->Draw();
 te->DrawTextNDC(0.2,0.7, value.c_str());
 std::cout << "[OVAL] " << roccp->GetName() << " PV = " << pv << std::endl;

 Ecal->Print("Barrel_Occupancy.eps");
 }//if

}
