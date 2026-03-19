# Clear any running ports
echo "Clear any running ports"
sudo fuser -k 21/tcp

# Copy Executables
echo "Copying Executables for VxWorks filesystem"
mkdir -p outputs
find ./source -name "*.vxe" -exec cp {} outputs/ \;

# Start FTP server
echo "Starting FTP server"
sudo python3 -m pyftpdlib -p 21 -u target -P vxTarget -i 127.0.0.1 -d outputs > /dev/null 2>&1 &

# Start QEMU
echo "Starting QEMU"
qemu-system-x86_64 -m 1024M -kernel wrsdk-vxworks7-qemu/vxsdk/bsps/itl_generic_3_0_0_4/vxWorks \
-net nic -net user,hostfwd=tcp::1534-:1534,hostfwd=tcp::2345-:2345 \
-display none -serial stdio -monitor none \
-append "bootline:fs(0,0)host:vxWorks h=10.0.2.2 e=10.0.2.15 u=target pw=vxTarget o=gei0" 

# Clear any running ports
sudo fuser -k 21/tcp