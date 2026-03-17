# Update APT repo
sudo apt-get update

# Download and extract SDK
wget https://d13321s3lxgewa.cloudfront.net/wrsdk-vxworks7-qemu-1.16.tar.bz2
tar -xf wrsdk-vxworks7-qemu-1.16.tar.bz2

# Install dependencies
sudo dpkg --add-architecture i386
sudo apt install build-essential libc6:i386
sudo apt install python3-pip
sudo apt install python3-pyftpdlib
sudo apt install pipx
sudo apt install qemu-system-x86

# Patch SDK for WSL
sed -i 's/echo "The default shell is dash/echo "" #echo "The default shell is dash/' wrsdk-vxworks7-qemu/sdkenv.sh
sed -i 's/return 1/#return 1/' wrsdk-vxworks7-qemu/sdkenv.sh