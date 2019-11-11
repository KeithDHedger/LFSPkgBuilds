One or more OpenVPN config files should be installed in this directory
as files ending in ".conf" (i.e. client.conf, server.conf, etc.).

Have a look in sample-config-files for some more examples of how to
configure OpenVPN.

To start OpenVPN, use this command as root:
sh /etc/rc.d/rc.openvpn start

To make OpenVPN start automatically at boot, change the script permissions:
chmod 755 /etc/rc.d/rc.openvpn

See "man openvpn" and the other docs for more information.
