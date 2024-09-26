// Project UID c1f28c309e55405daf00c565d57ff9ad
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class OHQueue {
public:
    void readRoutes();
    void readAllQueuePositions();
    void readHead();
    void createTail(const string& uniqname, const string& location);
    void deleteHead();

private:
    struct Student {
        string uniqname;
        string location;
    };
    list<Student> queue;
};

void OHQueue::readRoutes() {
    json response = {
        {"queue_head_url", "http://localhost/queue/head/"},
        {"queue_list_url", "http://localhost/queue/"},
        {"queue_tail_url", "http://localhost/queue/tail/"}
    };

    string str2 = response.dump(4) + "\n";
    size_t content_length = str2.length();

    cout << "HTTP/1.1 200 OK" << endl;
    cout << "Content-Type: application/json; charset=utf-8" << endl;
    cout << "Content-Length: " << content_length << endl;
    cout << endl;
    cout << str2;
}

void OHQueue::readAllQueuePositions() {
  json response;
  if (queue.empty()) {
    json n;
    response = {
      {"count", 0},
      {"results", n}
    };

    string str2 = response.dump(4) + "\n";
    size_t content_length = str2.length();
    cout << "HTTP/1.1 200 OK" << endl;
    cout << "Content-Type: application/json; charset=utf-8" << endl;
    cout << "Content-Length: " << content_length << endl;
    cout << endl;
    cout << str2;
  } else {
    response["count"] = queue.size();
    int position = 1;
    for (const auto& student : queue) {
        json student_info = {
            {"location", student.location},
            {"position", position},
            {"uniqname", student.uniqname}
        };
        response["results"].push_back(student_info);
        ++position;
    }
    string str2 = response.dump(4) + "\n";
    size_t content_length = str2.length();
    cout << "HTTP/1.1 200 OK" << endl;
    cout << "Content-Type: application/json; charset=utf-8" << endl;
    cout << "Content-Length: " << content_length << endl;
    cout << endl;
    cout << str2;
  }
}

void OHQueue::readHead() {
  if (queue.empty()) {
    cout << "HTTP/1.1 400 Bad Request" << endl;
    cout << "Content-Type: application/json; charset=utf-8" << endl;
    cout << "Content-Length: 0" << endl;
    cout << endl;
  } else {
    const auto& student = queue.front();
    json response = {
      {"location", student.location},
      {"position", 1},
      {"uniqname", student.uniqname}
    };
    
    string str2 = response.dump(4) + "\n";
    size_t content_length = str2.length();
    cout << "HTTP/1.1 200 OK" << endl;
    cout << "Content-Type: application/json; charset=utf-8" << endl;
    cout << "Content-Length: " << content_length << endl;
    cout << endl;
    cout << str2;
  }
}

void OHQueue::createTail(const string& uniqname, const string& location) {
  Student new_student = { uniqname, location };
  queue.push_back(new_student);
  json response = {
    {"location", location},
    {"position", queue.size()},
    {"uniqname", uniqname}
  };

  string str2 = response.dump(4) + "\n";
  size_t content_length = str2.length();
  cout << "HTTP/1.1 201 Created" << endl;
  cout << "Content-Type: application/json; charset=utf-8" << endl;
  cout << "Content-Length: " << content_length << endl;
  cout << endl;
  cout << str2;
}


void OHQueue::deleteHead() {
  if (queue.empty()) {
    cout << "HTTP/1.1 400 Bad Request" << endl;
    cout << "Content-Type: application/json; charset=utf-8" << endl;
    cout << "Content-Length: 0" << endl;
    cout << endl;
  } else {
    queue.pop_front();
    cout << "HTTP/1.1 204 No Content" << endl;
    cout << "Content-Type: application/json; charset=utf-8" << endl;
    cout << "Content-Length: 0" << endl;
    cout << endl;
  }
}

void printBadRequest() {
  cout << "HTTP/1.1 400 Bad Request" << endl;
  cout << "Content-Type: application/json; charset=utf-8" << endl;
  cout << "Content-Length: 0" << endl;
  cout << endl;
}

void handleGetRequest(OHQueue& queue, const string& path) {
  json data;
  if (path == "/api/") {
    queue.readRoutes();
  } else if (path == "/api/queue/") {
    queue.readAllQueuePositions();
  } else if (path == "/api/queue/head/") {
    queue.readHead();
  } else {
    printBadRequest();
  }
}

void handlePostRequest(OHQueue& queue, const string& path) {
  json data;
  if (path == "/api/queue/tail/") {
    string line;
    getline(cin, line); // Read the rest of the first line
    getline(cin, line); // Read second line
    getline(cin, line); // Read the third line
    if (line.find("application/json") != string::npos) {
      getline(cin, line); 
      int content_length = stoi(line.substr(line.find(":") + 1));
      string json_str;
      for (int i = 0; i < content_length; i++) {
        json_str.push_back(cin.get());
      }
      data = json::parse(json_str);
      string uniqname = data["uniqname"];
      string location = data["location"];
      queue.createTail(uniqname, location);
    }
  } else {
    printBadRequest();
  }
}

int main() {
  OHQueue queue;
  string request;
  while (cin >> request) {
    if (request == "GET") {
      string path;
      cin >> path;
      handleGetRequest(queue, path);
    } else if (request == "POST") {
      string path;
      cin >> path;
      handlePostRequest(queue, path);
    } else if (request == "DELETE") {
      string path;
      cin >> path;
      if (path == "/api/queue/head/") {
        queue.deleteHead();
      } else {
        printBadRequest();
      }
    } 
  }
  return 0;
}

