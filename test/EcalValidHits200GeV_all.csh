#! /bin/csh

eval `scramv1 runtime -csh`

setenv ECALDATADIR /afs/cern.ch/cms/data/CMSSW/Validation/EcalHits/data

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

