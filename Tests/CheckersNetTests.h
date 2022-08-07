#pragma once

#include <gtest/gtest.h>

#include <memory>
#include <string>
using namespace std;

#include "../Core/framework.h"

class CheckersNetTests : public ::testing::Test
{
protected:
	void SetUp() override {
		server = make_unique<NetServer>();
		client = make_unique<NetClient>();

		server->Setup(port);
		client->Setup(ip, port);
	}

	// void TearDown() override {}

	const string ip = "127.0.0.1";
	const int port = 11999;

	unique_ptr<NetClient> client;
	unique_ptr<NetServer> server;
};

TEST_F(CheckersNetTests, MessageTest)
{
	string message = "a3b4";

	client->SetMessage(message);

	string received;
	for (int t = 0; t < 10; t++) {
		received = server->GetMessage();
		if (!received.empty())
			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	EXPECT_EQ(received, message);
}
