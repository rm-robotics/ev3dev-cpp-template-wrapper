#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <utilities.hpp>
#include <sys/ioctl.h>

#ifndef EV3WRAPBLUETOOTH_SOCKET_HPP_
#define EV3WRAPBLUETOOTH_SOCKET_HPP_
#define BLUETOOTH_PORT 20
#define CHAR_ARRAY_SIZE 32
namespace Ev3Wrap {

class BluetoothSocket {
public:
    // file descriptors for sockets
    // otherSocket is used for sending and receiving messages.
    // mySocket is the one initialised for binding and listening etc.
    // they are equal if awokenFirst = false
    int mySocket, otherSocket;
    // the MAC address of the other socket. Here for debugging purposes only
    char otherSocketMAC[18];
    // send a char* buffer of data to the address.
    // It is recommended that the msg char* be of length CHAR_ARRAY_SIZE.
    // If the char* buffer size is above CHAR_ARRAY_SIZE, a custom size must be given
    bool send(char* msg, int size = CHAR_ARRAY_SIZE);
    // read the value of a socket and copy it into a char array.
    // It is recommended that the msg char* be of length CHAR_ARRAY_SIZE.
    // readValue returns false when there is no valid data to be read.
    // readValue will not throw an error if the socket is disconnected; check hasDisconnected for that
    // if the char* buffer size should NOT be under CHAR_ARRAY_SIZE (unless the sender is sending smaller messages) 
    bool readValue(char* msg, int size = CHAR_ARRAY_SIZE);
    // if the socket has been disconnected
    bool hasDisconnected;
    // if this is true, it is a server socket which is meant to be turned on first, so that a client can connect to it
    bool awokenFirst;
    static void listDetectedDevices();
    // Create a bluetooth socket. dest (destination) is not required if it is a server socket (awokenFirst = true)
    static BluetoothSocket CreateBluetoothSocket(std::string dest = "", bool awokenFirst = true);
    ~BluetoothSocket();
private:
    BluetoothSocket(std::string dest = "", bool awokenFirst = true);
};

} // namespace Ev3Wrap

#endif