#! /bin/csh

eval `scramv1 runtime -csh`

setenv ECALDATADIR /afs/cern.ch/cms/data/CMSSW/Validation/EcalHits/data

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

