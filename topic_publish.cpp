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

using namespace std;

const string DFLT_SERVER_ADDRESS   { "tcp://test.mosquitto.org:1883" };

const string CLIENTID { "Raspberry zero office" };

const string TOPIC { "WPL" };
const int QOS = 1;

const char* PAYLOADS[] = {
	"Hello World! WPL",
	"Hi there! WPL",
	"Is anyone listening? WPL",
	"Someone is always listening. WPL",
	nullptr
};

const auto TIMEOUT = std::chrono::seconds(10);


int main()
{
    cout << "\n... used server ---> " << DFLT_SERVER_ADDRESS << " <---" << endl;
    cout << "    TOPIC:      ---> " << TOPIC << " <---\n" << endl;

	cout << "Initializing for server '" << DFLT_SERVER_ADDRESS << "'..." << endl;

    mqtt::async_client cli(DFLT_SERVER_ADDRESS, CLIENTID);

	cout << "  ...OK" << endl;

	try {
		cout << "\nConnecting..." << endl;
		cli.connect()->wait();
		cout << "  ...OK" << endl;

		cout << "\nPublishing messages..." << endl;

		mqtt::topic top(cli, TOPIC, QOS);
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

