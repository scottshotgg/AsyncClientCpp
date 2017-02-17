// asynchronous client event loop

#include <iostream>
#include <thread>
#include <map>

// fkin boosted m8
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/array.hpp>


using boost::asio::ip::tcp;


std::thread t;
//std::map <boost::uuids::uuid, tcp::socket> clientList;
std::map <boost::uuids::uuid, boost::shared_ptr<tcp::socket>> clientList;

boost::uuids::random_generator generator;




// tid = 1
void clientManager() {
	try {
			boost::asio::io_service io_service;

			tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 60000));

			for (;;) {
				tcp::socket socket(io_service);
				acceptor.accept(socket);
				boost::uuids::uuid uuid1 = generator();

				std::cout << "accepted client at " << socket.remote_endpoint() << " with UUID " << uuid1 << std::endl;

				boost::shared_ptr<tcp::socket> ptr(new tcp::socket());
				clientList[uuid1] = ptr;
				//boost::system::error_code ignored_error;
				//boost::asio::write(socket, boost::asio::buffer(message),
				//boost::asio::transfer_all(), ignored_error);

				std::string message = "this is a cool message";
				boost::array<char, 128> buf;
				std::copy(message.begin(),message.end(),buf.begin());
				boost::system::error_code error;
				//tcp::socket& newClient = *clientList[uuid1];
				//newClient.write_some(boost::asio::buffer(buf, message.size()), error);
			}
		}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

void beginExport(int id) {
	printf("i am thread %d\n", id);
}

// tid = 0
int main(int argc, char* argv[]) {
	printf("loop test \n");	

	//int i = 1;
	// for(int i = 1; i < 100; i++) {
	// 	t[i] = std::thread(beginExport, i);
	// }

	// for(int i = 1; i < 100; i++) {
	// 	t[i].join();
	// }
	int i = 1;
	t = std::thread(clientManager);
	t.join();
}





// void quitThread() {

//   UDPClient tempClient(io_service, ip.c_str(), "6000");

//   //tempClient.Send(std::string(cmd + "\n"));
//   //printf("this is the command: %s", cmd.c_str());

//   std::string returnstring;
//   while(quit == 0) {
//     returnstring = tempClient.Recv();

//     if(returnstring[0] == 'd' && returnstring[1] == 'o' && returnstring[2] == 'n' && returnstring[3] == 'e') {
//       break;
//     }
//     //printf("this is the return string: %s", returnstring.c_str());
//     sync_cout << returnstring << sync_endl;
//   }
//   //sync_cout << "Thread" << id << " done!" << sync_endl;
// }


// //void beginExport(std::string cmd, std::string token, int id, UDPClient client) {
// void beginExport(std::string cmd, std::string token, UDPClient* client) {

//   client->Send(std::string(cmd + "\n"));
//   //printf("this is the command: %s", cmd.c_str());

//   std::string returnstring;
//   while(quit == 0) {
//     returnstring = client->Recv();

//     if(returnstring[0] == 'd' && returnstring[1] == 'o' && returnstring[2] == 'n' && returnstring[3] == 'e' && token != "bench") {
//       break;
//     } else if(returnstring[0] == 'b' && returnstring[1] == 'd' && returnstring[2] == 'o' && returnstring[3] == 'n' && returnstring[4] == 'e' && token == "bench") {
//       break;
//     }
//     //printf("this is the return string: %s", returnstring.c_str());
//     sync_cout << returnstring << sync_endl;
//   }

//   //sync_cout << "Thread" << id << " done!" << sync_endl;
// }


// void UCI::loop(int argc, char* argv[]) {

//   #ifdef WIN32
//     WSAStartup(MAKEWORD(2, 2), &wsaData);
//   #endif

//   UDPClient client(io_service, ip.c_str(), "6000");
  
//   Position pos;
//   string token, cmd;

//   pos.set(StartFEN, false, &States->back(), Threads.main());

//   for (int i = 1; i < argc; ++i)
//       cmd += std::string(argv[i]) + " ";

//   do {  
//       // Block here waiting for input or EOF
//       if (argc == 1 && !getline(cin, cmd))
//         cmd = "quit";

//       istringstream is(cmd);
//       token.clear(); // getline() could return empty or blank line
//       is >> skipws >> token;

//       if (token == "quit") {
//         //std::thread t1(quitThread, "stop", tid);
//         std::thread t1(quitThread);
//         quit = 1;
//         t1.join();
//         Search::Signals.stop = true;
//         Threads.main()->start_searching(true);

//       } else {
//         //std::thread t1(beginExport, cmd, token, tid, client);
//         std::thread t1(beginExport, cmd, token, &client);
//         //sync_cout << "Thread " << tid <<  " waiting..." << sync_endl;
//         tid++;
//         t1.detach();
//       } 
//   } while (token != "quit" && argc == 1);

//   // may want to make a function like this that waits for everything
//   //waitForJoin()

//   quit = 1;
//   Threads.main()->wait_for_search_finished();
// }
