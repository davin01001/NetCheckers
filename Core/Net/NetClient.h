#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <optional>
#include <chrono>
using namespace std;
using namespace chrono_literals;

class NetClient
{
public:
	NetClient() : port(0), server_addr {} {}

	~NetClient() {
		close(client_fd);
		close(sock);
	}

	bool Setup(const string & ip_, int port_) {
		ip = ip_;
		port = port_;

		atomic<bool> done { false };
		thread th ([this, &done](){

			if (sock < 0)
			{
				sock = socket(AF_INET, SOCK_STREAM, 0);
				if (sock < 0) {
					cerr << "Socket creation error" << endl;
					done = true;
					return;
				}
			}

			if (inet_addr(ip.c_str()) == -1)
			{
				struct hostent *he;
				struct in_addr **addr_list;
				if ((he = gethostbyname(ip.c_str())) == nullptr)
				{
					done = true;
					return;
				}
				addr_list = (struct in_addr **)he->h_addr_list;
				if (addr_list[0]) {
					server_addr.sin_addr = *addr_list[0];
				}
			}
			else
			{
				server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
			}

			server_addr.sin_family = AF_INET;
			server_addr.sin_port = htons(port);

			if (client_fd < 0)
			{
				client_fd = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
				if (client_fd < 0)
				{
					cerr << "Connect to server failed" << endl;
					done = true;
					return;
				}
			}

			while (true) {
				string data;
				while (data.empty()) {
					{
						lock_guard lock { messageMutex };
						data = message;
					}
					this_thread::sleep_for(100ms);
				}
				if (!Send(data)) {
					break;
				}
				sending = false;
				read = false;
				Clean();

				auto om = Read();
				if (om.has_value()) {
					lock_guard lock { messageMutex };
					message = string(om.value());
					cout << "Client: receive message " << message << endl;
				}

				read = false;
				while (!read) { // wait while message was read
					this_thread::sleep_for(100ms);
				}
				read = false;
				Clean();

				this_thread::sleep_for(100ms);
			}

			done = true;
		});
		th.detach();

		this_thread::sleep_for(500ms);

		return !done;
	}

	string GetMessage() {
		if (sending)
			return "";
		string returnMessage;
		{
			lock_guard lock { messageMutex };
			returnMessage = message;
			if (!message.empty())
				read = true;
		}
		return returnMessage;
	}

	void SetMessage(const string & msg) {
		lock_guard lock { messageMutex };
		message = msg;
		sending = true;
	}

private:
	int client_fd = -1;
	int sock = -1;
	struct sockaddr_in server_addr;

	string ip;
	int port;

	mutex messageMutex;
	static string message;
	atomic<bool> read = false;
	atomic<bool> sending = false;

	[[nodiscard]] bool Send(const string & data) const {
		if (sock < 0)
			return false;

		cout << "Client: send message " << data << endl;

		ssize_t sent = send(sock, data.c_str(), data.length(), 0);
		if (sent < 0)
		{
			cerr << "Send failed" << endl;
			return false;
		}

		return true;
	}

	[[nodiscard]] optional<string> Read() const {
		char buffer[1] = {};
		string reply;
		while (buffer[0] != '\n')
		{
			ssize_t received = recv(sock, buffer, sizeof(buffer), 0);
			if (received < 0)
			{
				cerr << "Receive failed" << endl;
				return nullptr;
			}
			reply += buffer[0];
		}
		return reply;
	}

	void Clean() {
		lock_guard lock { messageMutex };
		message = "";
	}

};
