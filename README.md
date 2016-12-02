Kernel module to detect various types of TCP scans generated using nmap. It uses netfilter framework and intercepts TCP recon packets.


Scans tested
1. NULL Scan `nmap -sN ip P`
2. FIN Scan  `nmap -sF ip P`
3. XMAS Scan `nmap -sX ip P`
4. ACK Scan  `nmap -sA ip P`

ip = ip of destination machine.
P = any port of destination machine.

Run using `make` and clean using `make clean`.
See kernel logs using `dmesg info` or `tail /var/log/kern.log`.

Assumptions:
===========
1. In nmap scans, for example `nmap -sA localhost X` localhost and port X can be used for checking that the kernel module is setup properly.
2. UFW or any other firewall should be put down, as it may block some of the nmap scans. `sudo service ufw stop`

References:
==========

1.	http://www.paulkiddie.com/2010/02/update-on-setting-up-ubuntu-in-order-to-build-kernel-modules/
2.	http://www.paulkiddie.com/2009/10/creating-a-simple-hello-world-netfilter-module/
3.	https://nmap.org/book/man-port-scanning-techniques.html
