#! /bin/csh

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

