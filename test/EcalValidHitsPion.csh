#! /bin/csh
eval `scramv1 runtime -csh`

setenv ECALDATADIR /afs/cern.ch/cms/data/CMSSW/Validation/EcalHits/data

echo "===========> Validating Ecal Simhits with 60GeV  Pion ......."
cp  ${ECALDATADIR}/Pion_Pt60GeV_all.root  testinput.root
cmsRun valid_ecal_simhit.cfg
root -b -p -q SimhitPion_all.C
setenv REFFILE "../data/PionSimHitHisto.root"
setenv CURFILE "PionSimHitHisto.root"
root -b -p -q DoCompare.C\(\"Pion\"\)
mv  simhitoutput.root   Pion_Pt60GeV_all_simevent.root
if ( -e testinput.root ) /bin/rm testinput.root

