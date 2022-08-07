#pragma once

#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
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

#define MAX_PACKET_SIZE 4096

class NetServer
{
public:
	NetServer() = default;

	~NetServer() {
		close(socket_fd);
		close(new_socket_fd);
	}

	bool Setup(int port)
	{
		atomic<bool> done { false };
		thread th ([this, port, &done](){

			if (socket_fd < 0) {
				socket_fd = socket(AF_INET, SOCK_STREAM, 0);
				if (socket_fd == 0) {
					cerr << "Server create socket failed" << endl;
					done = true;
					return;
				}
			}

			memset(&serverAddress, 0, sizeof(serverAddress));

			serverAddress.sin_family = AF_INET;
			serverAddress.sin_addr.s_addr = INADDR_ANY;
			serverAddress.sin_port = htons(port);

			if (bind(socket_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
				cerr << "bind failed" << endl;
				done = true;
				return;
			}

			if (listen(socket_fd, 5) < 0) {
				cerr << "listen failed" << endl;
				done = true;
				return;
			}

			socklen_t socket_size = sizeof(clientAddress);
			if (new_socket_fd < 0)
			{
				new_socket_fd = accept(socket_fd, (struct sockaddr *) &clientAddress, &socket_size);
				if (new_socket_fd < 0)
				{
					cerr << "Socket accept failed" << endl;
					done = true;
					return;
				}
			}

			char msg[MAX_PACKET_SIZE];
			while (true)
			{
				ssize_t received = recv(new_socket_fd, msg, MAX_PACKET_SIZE, 0);
				if (received <= 0)
					break;
				msg[received] = 0;
				{
					lock_guard lock { messageMutex };
					message = string(msg);
					cout << "Server: receive message " << message << endl;
				}

				read = false;
				while (!read) { // wait while message was read
					this_thread::sleep_for(100ms);
				}
				read = false;
				Clean();

				string data;
				while (data.empty()) {
					{
						lock_guard lock { messageMutex };
						data = message;
					}
					this_thread::sleep_for(100ms);
				}
				read = false;
				Clean();

				if (!Send(data))
					break;

				sending = false;
				Clean();
			}

			close(new_socket_fd);
			new_socket_fd = -1;

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
	struct sockaddr_in serverAddress = {};
	struct sockaddr_in clientAddress = {};
	int socket_fd = -1;
	int new_socket_fd = -1;

	mutex messageMutex;
	static string message;
	atomic<bool> read = false;
	atomic<bool> sending = false;

	bool Send(const string & msg) {
		socklen_t socket_size = sizeof(clientAddress);
		if (new_socket_fd < 0)
		{
			new_socket_fd = accept(socket_fd, (struct sockaddr *) &clientAddress, &socket_size);
			if (new_socket_fd < 0)
			{
				cerr << "Socket accept failed" << endl;
				return false;
			}
		}

		send(new_socket_fd, msg.c_str(), msg.length(), 0);

		cout << "Server: send message " << msg << endl;

		return true;
	}

	void Clean() {
		lock_guard lock { messageMutex };
		message = "";
	}

};
