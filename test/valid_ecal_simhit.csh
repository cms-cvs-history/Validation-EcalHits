#! /bin/csh
 
eval `scramv1 ru -csh`

setenv SAMPLEFILE  simhitoutput.root
setenv REFERFILE   simhitoutput.root
setenv ECALDATADIR /afs/cern.ch/user/f/fabiocos/public/Validation/samples

echo "===========> Validating Ecal Simhits with 30 GeV Photon ......."
cp  ${ECALDATADIR}/Photon_E30GeV_all.root   testinput.root
cmsRun valid_ecal_simhit.cfg
root -b -p -q  EcalSimHitPlots.C
mv  simhitoutput.root   PhotonSimHit_E30GeV_all.root
if ( -e testinput.root ) /bin/rm testinput.root

echo "===========> Validating Ecal Simhits with 200 GeV Photon ......."
cp   ${ECALDATADIR}/Photon_E200GeV_all.root  testinput.root
sed 's/maxEvents=2000/maxEvents=200/' valid_ecal_simhit.cfg > & ! valid_ecal_simhit_200GeV.cfg
cmsRun valid_ecal_simhit_200GeV.cfg
root -b -p -q  EcalSimHitPlots.C
mv  simhitoutput.root   PhotonSimHit_E200GeV_all.root
if ( -e testinput.root ) /bin/rm testinput.root
if ( -e valid_ecal_simhit_200GeV.cfg ) /bin/rm valid_ecal_simhit_200GeV.cfg

echo "===========> Validating Ecal Simhits with 400 GeV Photon ......."
cp  ${ECALDATADIR}/Photon_E400GeV_all.root   testinput.root
sed 's/maxEvents=2000/maxEvents=200/' valid_ecal_simhit.cfg > & ! valid_ecal_simhit_400GeV.cfg
cmsRun valid_ecal_simhit_400GeV.cfg
root -b -p -q  EcalSimHitPlots.C
mv  simhitoutput.root   PhotonSimHit_E400GeV_all.root
if ( -e testinput.root ) /bin/rm testinput.root
if ( -e  valid_ecal_simhit_400GeV.cfg ) /bin/rm valid_ecal_simhit_400GeV.cfg


echo "...ooo0000ooo......ooo0000ooo......ooo0000ooo......ooo0000ooo..."

