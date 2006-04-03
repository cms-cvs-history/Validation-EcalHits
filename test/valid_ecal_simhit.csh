#! /bin/csh
 
eval `scramv1 ru -csh`

cmsRun valid_ecal_simhit.cfg

root -b -p -q  cmssw_all_ecal.C

