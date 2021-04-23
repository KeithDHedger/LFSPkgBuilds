# LFSPkgBuilds

Mount a clean partion somewhere ( e.g. /mnt/LFS ).
CD into the mounted partition:
cd /mnt/LFS
Make sure you have rw perms:
sudo chown $USER .

Checkout the code:
git clone https://github.com/KeithDHedger/LFSPkgBuilds.git
Or for a single branch:
git clone https://github.com/KeithDHedger/LFSPkgBuilds.git --branch 10.1 --single-branch

Depending on what init style you want to use you should first make a symlink from LFSPkgBuilds/LFSScripts/SysVBuild or LFSPkgBuilds/LFSScripts/SystemDBuild or LFSPkgBuilds/LFSScripts/LFSInitBuild or LFSPkgBuilds/LFSScripts/PiBuild to LFSScripts

E.G:<br>
ln -sfvn LFSPkgBuilds/LFSScripts/SysVBuild LFSScripts<br>
ln -sfvn LFSPkgBuilds/LFSPkgBuildScripts LFSPkgBuildScripts<br>

Follow the instructions in LFSScripts/HowTo
