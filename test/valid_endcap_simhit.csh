#! /bin/csh
 
eval `scramv1 ru -csh`

setenv ECALDATADIR /afs/cern.ch/cms/data/CMSSW/Validation/EcalHits/data
setenv ECALREFDIR  /afs/cern.ch/cms/data/CMSSW/Validation/EcalHits/data

echo "===========> Validating Endcap's Simhits with 30 GeV Photon (Eta=2.2)......."
cp  ${ECALDATADIR}/Photon_E30GeV_endcap.root  testinput.root

cmsRun valid_ecal_simhit.cfg
setenv SAMPLEFILE  simhitoutput.root
setenv REFERFILE   simhitoutput.root #${ECALREFDIR}/PhotonSimHit_E30GeV_2.2.root
root -b -p -q  EndcapSimHitPlots.C
mv  simhitoutput.root   PhotonSimHit_E30GeV_2.2.root
if ( -e testinput.root ) /bin/rm testinput.root

echo "...ooo0000ooo......ooo0000ooo......ooo0000ooo......ooo0000ooo..."

