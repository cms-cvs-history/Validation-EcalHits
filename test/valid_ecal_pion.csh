#! /bin/csh
 
eval `scramv1 ru -csh`

setenv ECALDATADIR /afs/cern.ch/cms/data/CMSSW/Validation/EcalHits/data
setenv ECALREFDIR  /afs/cern.ch/cms/data/CMSSW/Validation/EcalHits/data

echo "===========> Validating Ecal Simhits with 30 GeV Photon ......."
cp  ${ECALDATADIR}/Pion_Pt60GeV_all.root  testinput.root

cmsRun valid_ecal_simhit.cfg
setenv SAMPLEFILE  simhitoutput.root
setenv REFERFILE   simhitoutput.root #${ECALREFDIR}/PionSimHit_Pt60GeV_all.root
root -b -p -q  EcalSimHitPlotsForPion.C
mv  simhitoutput.root   PionSimHit_Pt60GeV_all.root
if ( -e testinput.root ) /bin/rm testinput.root

echo "...ooo0000ooo......ooo0000ooo......ooo0000ooo......ooo0000ooo..."

