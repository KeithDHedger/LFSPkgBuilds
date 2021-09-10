# LFSPkgBuilds

Mount a clean partion somewhere ( e.g. /mnt/LFS ).<br>
CD into the mounted partition:<br>
cd /mnt/LFS<br>
Make sure you have rw perms:<br>
sudo chown $USER .<br>

Checkout the code:
git clone https://github.com/KeithDHedger/LFSPkgBuilds.git<br>
Or for a single branch:<br>
git clone https://github.com/KeithDHedger/LFSPkgBuilds.git --branch 10.1 --single-branch<br>

Depending on what init style you want to use you should first make a symlink from LFSPkgBuilds/LFSScripts/SysVBuild or LFSPkgBuilds/LFSScripts/SystemDBuild or LFSPkgBuilds/LFSScripts/LFSInitBuild or LFSPkgBuilds/LFSScripts/PiBuild to LFSScripts<br>

E.G:<br>
ln -sfvn LFSPkgBuilds/LFSScripts/SysVBuild LFSScripts<br>
ln -sfvn LFSPkgBuilds/LFSPkgBuildScripts LFSPkgBuildScripts<br>

For convienience you may want to also make a symlink to the HowTo, EG:<br>
ln -sfvn LFSScripts/HowTo-EFI HowTo

Follow the instructions in LFSScripts/HowTo
