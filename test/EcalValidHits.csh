#! /bin/csh

source /afs/fnal.gov/files/code/cms/setup/cshrc uaf
cd /uscms/home/huangxt/work/CMSSW_0_7_1/src/Validation/EcalHits/test

eval `scramv1 runtime -csh`

setenv ECALDATADIR /afs/cern.ch/cms/data/CMSSW/Validation/EcalHits/data

echo "===========> Validating Ecal Simhits with 30 GeV Photon ......."
cp  ${ECALDATADIR}/Photon_E30GeV_all.root   testinput.root
cmsRun valid_ecal_simhit.cfg
root -b -p -q Simhit30GeV_all.C
setenv REFFILE "../data/EcalSimHitHisto_30GeV.root"
setenv CURFILE "EcalSimHitHisto_30GeV.root"
root -b -p -q DoCompare.C\(\"30GeV\"\)
mv  simhitoutput.root   Photon_E30GeV_all_simevent.root
if ( -e testinput.root ) /bin/rm testinput.root

echo "===========> Validating Barrel Ecal Simhits with 30 GeV Photon ......."
cp  ${ECALDATADIR}/Photon_E30GeV_barrel.root   testinput.root
cmsRun valid_ecal_simhit.cfg
root -b -p -q Simhit30GeV_Barrel.C
setenv REFFILE "../data/EcalSimHitHisto_30GeV_Barrel.root"
setenv CURFILE "EcalSimHitHisto_30GeV_Barrel.root"
root -b -p -q DoCompare.C\(\"30GeVBarrel\"\)
mv  simhitoutput.root Photon_E30GeV_barrel_simevent.root 
if ( -e testinput.root ) /bin/rm testinput.root

echo "===========> Validating Endcap Ecal Simhits with 30 GeV Photon ......."
cp  ${ECALDATADIR}/Photon_E30GeV_endcap.root   testinput.root
cmsRun valid_ecal_simhit.cfg
root -b -p -q Simhit30GeV_Endcap.C
setenv REFFILE "../data/EcalSimHitHisto_30GeV_Endcap.root"
setenv CURFILE "EcalSimHitHisto_30GeV_Endcap.root"
root -b -p -q DoCompare.C\(\"30GeVEndcap\"\)
mv  simhitoutput.root Photon_E30GeV_endcap_simevent.root
if ( -e testinput.root ) /bin/rm testinput.root

echo "===========> Validating Ecal Simhits with 200 GeV Photon ......."
cp   ${ECALDATADIR}/Photon_E200GeV_all.root  testinput.root
sed 's/maxEvents= 2000/maxEvents=200/' valid_ecal_simhit.cfg > & ! valid_ecal_simhit_200GeV.cfg
cmsRun valid_ecal_simhit_200GeV.cfg
root -b -p -q Simhit200GeV_all.C
setenv REFFILE "../data/EcalSimHitHisto_200GeV.root"
setenv CURFILE "EcalSimHitHisto_200GeV.root"
root -b -p -q DoCompare.C\(\"200GeV\"\)
mv  simhitoutput.root   Photon_E200GeV_all_simevent.root
if ( -e testinput.root ) /bin/rm testinput.root

echo "===========> Validating Ecal Simhits with 400 GeV Photon ......."
cp  ${ECALDATADIR}/Photon_E400GeV_all.root   testinput.root
sed 's/maxEvents= 2000/maxEvents=200/' valid_ecal_simhit.cfg > & ! valid_ecal_simhit_400GeV.cfg
cmsRun valid_ecal_simhit_400GeV.cfg
root -b -p -q Simhit400GeV_all.C
setenv REFFILE "../data/EcalSimHitHisto_400GeV.root"
setenv CURFILE "EcalSimHitHisto_400GeV.root"
root -b -p -q DoCompare.C\(\"400GeV\"\)
mv  simhitoutput.root   Photon_E400GeV_all_simevent.root
if ( -e testinput.root ) /bin/rm testinput.root

echo "===========> Validating Ecal Simhits with 60GeV  Pion ......."
cp  ${ECALDATADIR}/Pion_Pt60GeV_all.root  testinput.root
cmsRun valid_ecal_simhit.cfg
root -b -p -q SimhitPion_all.C
setenv REFFILE "../data/PionSimHitHisto.root"
setenv CURFILE "PionSimHitHisto.root"
root -b -p -q DoCompare.C\(\"Pion\"\)
mv  simhitoutput.root   Pion_Pt60GeV_all_simevent.root
if ( -e testinput.root ) /bin/rm testinput.root

