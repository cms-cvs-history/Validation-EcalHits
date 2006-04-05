#! /bin/csh
 
eval `scramv1 ru -csh`

echo "===========> Validating Ecal Simhits with 30 GeV Photon ......."
cp  Photon_Whole_Ecal30.root   testinput.root
cmsRun valid_ecal_simhit.cfg
setenv SAMPLEFILE  simhitoutput.root
setenv REFERFILE   simhitoutput.root
root -b -p -q  cmssw_all_ecal.C
mv  simhitoutput.root   30GevPhotonSimHit.root
if ( -e testinput.root ) /bin/rm testinput.root

echo "===========> Validating Ecal Simhits with 200 GeV Photon ......."
cp  Photon_Whole_Ecal200.root   testinput.root
cmsRun valid_ecal_simhit.cfg
setenv SAMPLEFILE  simhitoutput.root
setenv REFERFILE   simhitoutput.root
root -b -p -q  cmssw_all_ecal.C
mv  simhitoutput.root   200GevPhotonSimHit.root
if ( -e testinput.root ) /bin/rm testinput.root

echo "===========> Validating Ecal Simhits with 400 GeV Photon ......."
cp  Photon_Whole_Ecal400.root   testinput.root
cmsRun valid_ecal_simhit.cfg
setenv SAMPLEFILE  simhitoutput.root
setenv REFERFILE   simhitoutput.root
root -b -p -q  cmssw_all_ecal.C
mv  simhitoutput.root   400GevPhotonSimHit.root
if ( -e testinput.root ) /bin/rm testinput.root

echo "...ooo0000ooo......ooo0000ooo......ooo0000ooo......ooo0000ooo..."

