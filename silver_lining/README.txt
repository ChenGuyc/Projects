# Silver Lining - An enterprise cloud solution

Silver Lining project allows smart enterprise cloud, 
utilizing existing free storage in organization machines, the machines can be any IOT device that has storage device and network device. 


version - 0.1 - initial app, NBD proxy driver & RAM storage device
(1) In order to run the program follow the following steps:
* sudo modprobe nbd
* sudo ./a.Debug.out <size of storage in MB>/dev/nbd0
Open another terminal window
* sudo mkfs.ext4 /dev/nbd0
* sudo mount /dev/nbd0 mnt


version - 0.11 - adding logger (in singleton aka handleton model)


## Running notes

Before running the app, make sure you have installed NBD or similar solution to your system.
Then you can run (from src folder):
./a.Debug.com [arg1] [arg2]
When arg1 is the file to which NBD (or similar) is related to
And arg2 is size of storage in MB
For example:
./a.Debug.com /dev/nbd0 128



