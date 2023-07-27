#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main() {
	// Define the server's IP address and port number
	string Host = "127.0.0.1";
	int port = 5004;

	// Initialize Winsock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0) {
		cerr << "Can't start winsock, error #" << wsResult << endl;
		return;
	}

	// Create a socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		cerr << "Can't create socket, Error #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Set up server information
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, Host.c_str(), &hint.sin_addr);

	// Connect to the server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		cerr << "Can't connect to server, Error #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	// Define the buffer
	char buf[4096];
	string userinput;
	string amount;

	do {
		int sendResult;
		int bytesReceived;
		int operation = 0;
		cout << "> ";

		// Get and send the username to the server
		cout << "Enter the username:";
		getline(cin, userinput);
		if (userinput.size() > 0) {
			sendResult = send(sock, userinput.c_str(), userinput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {
				ZeroMemory(buf, 4096);
				bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived) {
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
				}
			}
		}

		// Get and send the password to the server
		cout << "Enter the password:";
		getline(cin, userinput);
		if (userinput.size() > 0) {
			sendResult = send(sock, userinput.c_str(), userinput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR) {
				ZeroMemory(buf, 4096);
				bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived) {
					cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
				}
			}
		}

		// Display options for user actions
		cout << "*******************************************" << endl;
		cout << " What do you want to do ?" << endl;
		cout << "1. Deposit into account." << endl;
		cout << "2. Withdraw money from account." << endl;
		cout << "3. Deposit to another user." << endl;
		cout << "*******************************************" << endl;
		getline(cin, userinput);

		// Process user action based on the selected option
		int string_result = userinput.compare("1");
		int string_result_1 = userinput.compare("2");
		int string_result_2 = userinput.compare("3");

		if (string_result == 0) {
			// User wants to deposit into the account
			if (userinput.size() > 0) {
				sendResult = send(sock, userinput.c_str(), userinput.size() + 1, 0);
			}
			cout << "The amount you want to deposit ?" << endl;
			getline(cin, amount);

			if (amount.size() > 0) {
				sendResult = send(sock, amount.c_str(), amount.size() + 1, 0);
			}
			ZeroMemory(buf, 4096);
			bytesReceived = recv(sock, buf, 4096, 0);
			if (bytesReceived) {
				cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
			}
			string_result = 1;
		}

		if (string_result_1 == 0) {
			// User wants to withdraw money from the account
			if (userinput.size() > 0) {
				sendResult = send(sock, userinput.c_str(), userinput.size() + 1, 0);
			}
			cout << "The amount you want to withdraw ?" << endl;
			getline(cin, amount);

			if (amount.size() > 0) {
				sendResult = send(sock, amount.c_str(), amount.size() + 1, 0);
			}
			ZeroMemory(buf, 4096);
			bytesReceived = recv(sock, buf, 4096, 0);
			if (bytesReceived) {
				cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
			}
			string_result_1 = 1;
		}

		if (string_result_2 == 0) {
			// User wants to deposit to another user's account
			if (userinput.size() > 0) {
				sendResult = send(sock, userinput.c_str(), userinput.size() + 1, 0);
			}
			cout << "Enter the name and surname of the person you want to send: " << endl;
			getline(cin, userinput);
			if (userinput.size() > 0) {
				sendResult = send(sock, userinput.c_str(), userinput.size() + 1, 0);
			}
			cout << "Enter the account number of the person you want to send: " << endl;
			getline(cin, userinput);
			if (userinput.size() > 0) {
				sendResult = send(sock, userinput.c_str(), userinput.size() + 1, 0);
			}
			cout << "Enter the amount you want to send: " << endl;
			getline(cin, amount);
			if (amount.size() > 0) {
				sendResult = send(sock, amount.c_str(), amount.size() + 1, 0);
			}
			ZeroMemory(buf, 4096);
			bytesReceived = recv(sock, buf, 4096, 0);
			if (bytesReceived > 0) {
				cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
			}
			string_result_2 = 1;
		}
	} while (userinput.size() > 0);

	// Close the socket and clean up Winsock
	closesocket(sock);
	WSACleanup();
}
