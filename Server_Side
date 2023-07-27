#include <iostream>
#include <string>
#include <WS2tcpip.h>   // Header for Windows Sockets API

#include <fstream>
#include <stdio.h>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")   // Linking the Windows Sockets library

using namespace std;

// Structure to store personal data
struct personal_data {
	string userName = {};
	string password = {};
};

// Structure to store customer data
struct customer_data_base {
	string customer_number = {};
	string customer_name = {};
	string customer_balance = {};
	string bank_name = {};
	string customer_ID = {};
	string password = {};
};

void main() {

	personal_data personal_data;
	customer_data_base customer_data_base, customer_data;

	// Initializing Winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);   // Requesting version 2.2 of Winsock

	int ws0k = WSAStartup(ver, &wsData);   // Initializing Winsock with the requested version

	if (ws0k != 0) {
		cerr << "Can't Initialize winsock! Quitting..." << endl;
		return;
	}

	// Creating a socket for listening to incoming connections
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

	if (listening == INVALID_SOCKET) {
		cerr << "Can't create a socket! Quitting..." << endl;
		return;
	}

	// Setting up the server address and port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(5004);   // Specifying the port to listen on (5004)
	hint.sin_addr.S_un.S_addr = INADDR_ANY;   // Binding to all available interfaces

	// Binding the socket to the specified address and port
	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Start listening for incoming connections
	listen(listening, SOMAXCONN);

	// Accepting incoming connection request and establishing a new socket for communication with the client
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	// Getting the client's IP address and port
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		cout << host << " connected on port " << service << endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " <<
			ntohs(client.sin_port) << endl;
	}

	// Closing the listening socket as we don't need it anymore
	closesocket(listening);

	// Variables for receiving and processing data
	char buf[4096];
	int status = 0;
	string amount;
	int size;
	string result_str = {};
	string operation = {};
	string string1 = "1";
	string string2 = "2";
	string string3 = "3";
	string sending = {};
	int amount_int;
	int balance_int;
	int next_state = 0;
	char delimiter;
	string line;
	int select = 0;

	while (true) {
		// Clear the buffer before receiving data.
		ZeroMemory(buf, 4096);

		// Receive data from the clientSocket.
		int byteRecieved = recv(clientSocket, buf, 4096, 0);
		if (byteRecieved == SOCKET_ERROR) {
			cerr << "Error in recv(). Quitting..." << endl;
			break;
		}
		if (byteRecieved == 0) {
			cout << "Client is Disconnetedé!" << endl;
			break;
		}

		// Display the received data and the number of bytes received.
		cout << "buf: " << string(buf, 0, byteRecieved) << endl;
		cout << "byterecieved: " << byteRecieved << endl;

		// Check the status to determine the state of the communication.
		if (status == 0) {
			// Receive the username from the client and store it in personal_data.userName.
			personal_data.userName = buf;
			// Clear the buffer and send back the received username to the client.
			ZeroMemory(buf, 4096);
			sprintf_s(buf, "%s", personal_data.userName.c_str());
			send(clientSocket, buf, byteRecieved + 1, 0);
			status++;
		}
		else if (status == 1) {

			// Receive the password from the client and store it in personal_data.password.
			personal_data.password = buf;

			//status++;
			//ZeroMemory(buf, 4096);
			//sprintf_s(buf, "%s", personal_data.password.c_str());
			//send(clientSocket, buf, byteRecieved + 1, 0);

			ifstream file("customer_data_base.txt");
			if (file.is_open()) {
				while (getline(file, line)) {
					delimiter = '	';
					stringstream ss(line);
					getline(ss, customer_data_base.customer_ID, delimiter);
					getline(ss, customer_data_base.customer_name, delimiter);
					getline(ss, customer_data_base.password, delimiter);
					getline(ss, customer_data_base.customer_number, delimiter);
					getline(ss, customer_data_base.customer_balance, delimiter);
					getline(ss, customer_data_base.bank_name);

					if (personal_data.password == customer_data_base.password && personal_data.userName == customer_data_base.customer_name) {
						cout << line << endl;
						ZeroMemory(buf, 4096);
						size = sizeof(line);
						sprintf_s(buf, "%s", line.c_str());
						send(clientSocket, buf, size + 1, 0);
						status++;
						next_state = 1;
					}
				}
			}
			file.close();


		}

		if (status == 2) {

			ifstream file1("customer_data_base.txt");
			ofstream temp1("temp.txt");

			if (file1.is_open() && temp1.is_open()) {
				while (getline(file1, line)) {
					delimiter = '	';
					stringstream sss(line);
					getline(sss, customer_data_base.customer_ID, delimiter);
					getline(sss, customer_data_base.customer_name, delimiter);
					getline(sss, customer_data_base.password, delimiter);
					getline(sss, customer_data_base.customer_number, delimiter);
					getline(sss, customer_data_base.customer_balance, delimiter);
					getline(sss, customer_data_base.bank_name);


					if (next_state == 1) {
						ZeroMemory(buf, 4096);
						byteRecieved = recv(clientSocket, buf, 4096, 0);
						next_state++;
						operation = buf;
						if (strcmp(operation.c_str(), string3.c_str()) == 0) {
							select = 0;
						}
						else {
							select = 1;
						}
					}
					//cout << "operation : " << operation << endl;
					if (next_state == 2 && select == 0) {
						ZeroMemory(buf, 4096);
						byteRecieved = recv(clientSocket, buf, 4096, 0);
						next_state++;
						customer_data.customer_name = buf;
					}
					//cout << "customer name: " << customer_data.customer_name << endl;
					if (next_state == 3 && select == 0) {
						ZeroMemory(buf, 4096);
						byteRecieved = recv(clientSocket, buf, 4096, 0);
						next_state++;
						customer_data.customer_number = buf;
					}
					//cout << "customer number: " << customer_data.customer_number << endl;
					if (next_state == 4 && select == 0) {
						ZeroMemory(buf, 4096);
						byteRecieved = recv(clientSocket, buf, 4096, 0);
						next_state++;
						amount = buf;
					}
					//cout << "amount: " << amount << endl;


					if (strcmp(operation.c_str(), string3.c_str()) == 0) {

						if (personal_data.userName == customer_data_base.customer_name) {
							amount_int = std::stoi(amount);
							balance_int = std::stoi(customer_data_base.customer_balance);
							if ((balance_int - amount_int) > 0) {
								result_str = std::to_string(balance_int - amount_int);
								line = customer_data_base.customer_ID + "	" + customer_data_base.customer_name + "	" + customer_data_base.password + "	" + customer_data_base.customer_number + "	" + result_str + "	" + customer_data_base.bank_name;
								
								cout << "Your transaction has been completed successfully." << endl;
								ZeroMemory(buf, 4096);
								sending = "Your transaction has been completed successfully.";
								size = sizeof(sending);
								sprintf_s(buf, "%s", sending.c_str());
								send(clientSocket, buf, size + 1, 0);
								operation = {};
								cout << "line:" << line << endl;

							}
							else {
								cout << "You don't have enough money." << endl;
								ZeroMemory(buf, 4096);
								sending = "You don't have enough money.";
								size = sizeof(sending);
								sprintf_s(buf, "%s", sending.c_str());
								send(clientSocket, buf, size + 1, 0);
								operation = {};
							}
							personal_data.password = {};
							personal_data.userName = {};
							
						}




						//cout << "customer data base name : " << customer_data_base.customer_name;

						if (customer_data.customer_name == customer_data_base.customer_name) {
							//cout << "customer ismi eslesti." << endl;

							if (customer_data.customer_number == customer_data_base.customer_number) {
								amount_int = std::stoi(amount);
								balance_int = std::stoi(customer_data_base.customer_balance);
								cout << "customer numarasi eslesti." << endl;
								result_str = std::to_string(amount_int + balance_int);
								line = customer_data_base.customer_ID + "	" + customer_data_base.customer_name + "	" + customer_data_base.password + "	" + customer_data_base.customer_number + "	" + result_str + "	" + customer_data_base.bank_name;
								cout << "Your transaction has been completed successfully." << endl;
								ZeroMemory(buf, 4096);
								sending = "Your transaction has been completed successfully.";
								size = sizeof(sending);
								sprintf_s(buf, "%s", sending.c_str());
								send(clientSocket, buf, size + 1, 0);

								cout << "line:" << line << endl;



								customer_data.customer_name = {};
								customer_data.customer_number = {};

							}
						}

						temp1 << line << endl;
						next_state = 0;
						select = 0;
						status = 0;

					}
					else if ((strcmp(operation.c_str(), string1.c_str()) == 0) || (strcmp(operation.c_str(), string2.c_str()) == 0)) {

						if (next_state == 2) {
							ZeroMemory(buf, 4096);
							byteRecieved = recv(clientSocket, buf, 4096, 0);
							amount = buf;
							next_state++;
						}

						amount_int = std::stoi(amount);
						balance_int = std::stoi(customer_data_base.customer_balance);

						if (personal_data.userName == customer_data_base.customer_name){
							if (strcmp(operation.c_str(), string1.c_str()) == 0) {
							cout << "amount:" << amount << endl;
							cout << "result: " << amount_int + balance_int << endl;
							result_str = std::to_string(amount_int + balance_int);
							line = customer_data_base.customer_ID + "	" + customer_data_base.customer_name + "	" + customer_data_base.password + "	" + customer_data_base.customer_number + "	" + result_str + "	" + customer_data_base.bank_name;
							cout << "Your transaction has been completed successfully." << endl;
							ZeroMemory(buf, 4096);
							sending = "Your transaction has been completed successfully.";
							size = sizeof(sending);
							sprintf_s(buf, "%s", sending.c_str());
							send(clientSocket, buf, size + 1, 0);
							operation = {};
							next_state = 0;
							select = 0;
							status = 0;
							personal_data.userName = {};
							personal_data.password = {};
						}
						else {
							if ((balance_int - amount_int) >= 0) {
								cout << "amount:" << amount << endl;
								cout << "result: " << balance_int - amount_int << endl;
								result_str = std::to_string(balance_int - amount_int);
								line = customer_data_base.customer_ID + "	" + customer_data_base.customer_name + "	" + customer_data_base.password + "	" + customer_data_base.customer_number + "	" + result_str + "	" + customer_data_base.bank_name;
								cout << "Your transaction has been completed successfully." << endl;
								ZeroMemory(buf, 4096);
								sending = "Your transaction has been completed successfully.";
								size = sizeof(sending);
								sprintf_s(buf, "%s", sending.c_str());
								send(clientSocket, buf, size + 1, 0);
								operation = {};
								next_state = 0;
								select = 0;
								status = 0;
								personal_data.userName = {};
								personal_data.password = {};
							}
							else {
								cout << "You don't have enough money." << endl;
								ZeroMemory(buf, 4096);
								sending = "You don't have enough money.";
								size = sizeof(sending);
								sprintf_s(buf, "%s", sending.c_str());
								send(clientSocket, buf, size + 1, 0);
								operation = {};
								next_state = 0;
								select = 0;
								status = 0;
								personal_data.userName = {};
								personal_data.password = {};

							}
						}
						}

						

						//cout << "line:" << line << endl;

						temp1 << line << endl;

						

					}
					else {
						temp1 << line << endl;
						next_state = 0;
						select = 0;
						status = 0;
					}
				}
			}

			file1.close();
			temp1.close();
			remove("customer_data_base.txt");
			rename("temp.txt", "customer_data_base.txt");
			personal_data.userName;
			personal_data.password;

		}
		cout << "peronal data user name: " << personal_data.userName << endl;
		cout << "peronal data password: " << personal_data.password << endl;
	}
	closesocket(clientSocket);
	WSACleanup();
	//system("pause");
}
