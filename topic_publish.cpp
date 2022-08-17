// topic_publish.cpp
//
// This is a Paho MQTT C++ client, sample application.
//
// It's an example of how to send messages as an MQTT publisher using the
// C++ asynchronous client interface using a 'topic' object to repeatedly
// send data to the same topic.
//
// The sample demonstrates:
//  - Connecting to an MQTT server/broker
//  - Publishing messages
//  - Use of the 'topic' class
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>	// For sleep
#include <atomic>
#include <chrono>
#include <cstring>
#include "mqtt/async_client.h"
#include "credentials.h"

using namespace std;

// const string DFLT_SERVER_ADDRESS { "tcp://192.168.1.39:1883" };
const string DFLT_SERVER_ADDRESS_2 { "tcp://" + mqtt_srv + ":" + mqtt_port }; // credentials.h
const string DFLT_SERVER_ADDRESS { "tcp://test.mosquitto.org:1883" };

const string TOPIC { "test" };
const int QOS = 1;

const char* PAYLOADS[] = {
	"Hello World! WPL",
	"Hi there! WPL",
	"Is anyone listening? WPL",
	"Someone is always listening. WPL",
	nullptr
};

const auto TIMEOUT = std::chrono::seconds(10);

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	string address = (argc > 1) ? string(argv[1]) : DFLT_SERVER_ADDRESS;

    cout << "\n---> " << DFLT_SERVER_ADDRESS << " <---" << endl;
    cout << "---> " << DFLT_SERVER_ADDRESS_2 << " <---\n" << endl;

	cout << "Initializing for server '" << address << "'..." << endl;
	mqtt::async_client cli(address, "");

	cout << "  ...OK" << endl;

	try {
		cout << "\nConnecting..." << endl;
		cli.connect()->wait();
		cout << "  ...OK" << endl;

		cout << "\nPublishing messages..." << endl;

		mqtt::topic top(cli, "test", QOS);
		mqtt::token_ptr tok;

		size_t i = 0;
		while (PAYLOADS[i]) {
			tok = top.publish(PAYLOADS[i++]);
		}
		tok->wait();	// Just wait for the last one to complete.
		cout << "OK" << endl;

		// Disconnect
		cout << "\nDisconnecting..." << endl;
		cli.disconnect()->wait();
		cout << "  ...OK" << endl;
	}
	catch (const mqtt::exception& exc) {
		cerr << exc << endl;
		return 1;
	}

 	return 0;
}

