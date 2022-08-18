// publish_2.cpp
//
// This is a Paho MQTT C++ client, sample application.
//
// It's an example of how to send messages as an MQTT publisher using the
// C++ asynchronous client interface using a 'topic' object to repeatedly
// send data to the same topic.
//
// The sample demonstrates:
//  - Connecting to an MQTT server/broker via user and password
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

const string DFLT_SERVER_ADDRESS { "tcp://" + MQTT_SRV + ":" + MQTT_PORT }; // credentials.h
const string CLIENTID { "Raspberry zero office" };
const string TOPIC { "WPL_TOPIC" };

const int QOS = 1;
const auto TIMEOUT = std::chrono::seconds(10);


// ######################################
// A callback class for use with the main MQTT client
// ######################################
class callback : public virtual mqtt::callback
{
public:
    void connection_lost(const std::string& cause) override {
        std::cout << "\nConnection lost" << std::endl;
        if (!cause.empty())
            std::cout << "\tcause: " << cause << std::endl;
    }

    void delivery_complete(mqtt::delivery_token_ptr tok) override {
        std::cout << "\tDelivery complete for token: "
                  << (tok ? tok->get_message_id() : -1) << std::endl;
    }
};


int main()
{
    cout << "\ntry to connect to server ---> " << DFLT_SERVER_ADDRESS << " <---" << endl;
    cout << "                  TOPIC: ---> " << TOPIC << " <---\n" << endl;

    // ######################################
    // Initializing server
    // ######################################
    cout << "Initializing server      ---> " << MQTT_SRV << " <---" << endl;
    mqtt::async_client client(DFLT_SERVER_ADDRESS, CLIENTID);

    callback cb;
    client.set_callback(cb);

    // ######################################
    // Build the connect options
    // ######################################
    auto connectOptions = mqtt::connect_options_builder().user_name(MQTT_USR).password(MQTT_PSW).finalize();
    cout << "\nconnect options          ---> OK <---" << endl;

    try {
        // ######################################
        // Connecting to server
        // ######################################
        cout << "\nConnecting ..." << endl;
        mqtt::token_ptr connectToken;
        connectToken = client.connect(connectOptions);
        cout << "\nWaiting for the connection ..." << endl;
        connectToken->wait();
        cout << "\nconnection               ---> OK <---" << endl;

        // ######################################
        // Publish a message
        // ######################################
        cout << "\nPublishing message..." << endl;
        string myMessage_1 = { "This is my message #111 from Raspberry zero in the office"};
        auto msg_1 = mqtt::make_message(TOPIC, myMessage_1, QOS, false);

        string myMessage_2 = { "This is my message #222 from Raspberry zero in the office"};
        auto msg_2 = mqtt::make_message(TOPIC, myMessage_2, QOS, false);

        for(int i = 0; i < 10; i++){
            client.publish(msg_1)->wait_for(TIMEOUT);
            client.publish(msg_2)->wait_for(TIMEOUT);
            // cout << "\npublishing messages ---> OK <---" << endl;
        }

        // ######################################
        // Disconnect from server
        // ######################################
        cout << "\nDisconnecting..." << endl;
        client.disconnect()->wait();
        cout << "\nDisconnected from server ---> OK <---" << endl;
    }
    catch (const mqtt::exception& exc) {
        cerr << exc.what() << endl;
        return 1;
    }

    return 0;
}
