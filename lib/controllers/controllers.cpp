#include <iostream>
#include <string>

#include "../webserver/webserver.h"
#include "../socket/src/Socket.h"
#include "../nlohmann/json.hpp"

#include "../services/data/data.h"

#include "controllers.h"
#include "../services/store/store.h"

using nlohmann::json; // Important for sending back JSON

/// Logger
void Logger(webserver::http_request *r, std::map<std::string, std::string> json_map_response)
{

    /*  What we're logging
    *  - Route
    *  - Method
    *  - Params
    *  - Body data
    *  - Expected response 
    */

    using namespace std; // Make our lives simpler from std::cout and std::endl

    cout
        << "----------------------------------------------" << endl;
    cout << "Route: " << r->path_ << endl;
    cout << "Method: " << r->method_ << endl;

    string params = DataService::mapToString(r->params_);

    if (params.length() > 2)
    {
        cout << "Route params: " << endl;
        cout << params << endl;
    }

    if (r->raw_body_data_.length() > 0)
    {
        cout << "Body data: " << endl;

        auto extracted_json = json::parse(r->raw_body_data_);
        cout << extracted_json.dump(4) << endl;
    }

    cout << "What we're about to send out: " << endl;
    cout << DataService::mapToString(json_map_response) << endl;

    cout
        << "----------------------------------------------" << endl;
}
/// Logger

void Controller::Request_Handler(webserver::http_request *r)
{
    Socket s = *(r->s_);

    // Mapping Request methods to repective handlers
    if (r->method_ == "POST")
        POST_handler(r);
    else if (r->method_ == "GET")
        GET_handler(r);
    else if (r->method_ == "PUT")
        PUT_handler(r);
    else if (r->method_ == "DELETE")
        DELETE_handler(r);
    else
        Handle_404(r);
};

void Controller::GET_handler(webserver::http_request *r)
{

    Socket s = *(r->s_);

    std::string params;

    if (r->params_.size() > 0)
    {
        params = DataService::mapToString(r->params_);
    }

    std::map<std::string, std::string> json_map_response;

    // --------------------------------------- //
    // std::cout << "------------------------------------------" << std::endl;
    //  && && extracted_json["id"].size() > 0 std::cout << "r->path_.find('db'): " << r->path_.find("db") << std::endl;

    // std::cout << "r->path_.find('all') == std::string::npos : " << (r->path_.find("all") == std::string::npos) << std::endl;
    // std::cout << "------------------------------------------" << std::endl;
    // --------------------------------------- //

    if (r->path_ == "/")
    {
        json_map_response = {{"path", "index"}, {"route", "/"}};
    }
    else if (r->path_ == "/get-json")
    {
        json_map_response = {{"status", "200 OK"}};
    }
    // Local database ops
    else if (r->path_.find("db") != std::string::npos) // Big numbers eg. 48598349834, garbage
    {
        if (r->path_.find("all") != std::string::npos) // Return all objects
        {
            Store::animal_map all = Store::readItems();

            if (all.size() != 0)
            {
                json_map_response["items"] = DataService::mapToVectorString(all);
            };

            // json_map_response returned below
        }
        else if (r->path_.find("all") == std::string::npos && params.length() > 0 && r->params_["id"].length() > 0)
        // Params found in GET requests
        {
            std::string id_string = r->params_["id"];
            int id = std::stoi(id_string);

            Store::animal_map res = Store::readItem(id);

            if (res[id] != "")
                json_map_response = {{"id", id_string}, {"item", res[id]}};

            // else, will send json_map_response {};
        }
        else
        {
            Handle_404(r);
            return;
        }
    }
    // Local database ops
    else
    {
        Handle_404(r);
        return;
    }

    Logger(r, json_map_response);
    r->answer_ = DataService::mapToString(json_map_response); // Find out how to receive data
}

void Controller::POST_handler(webserver::http_request *r)
{

    Socket s = *(r->s_);

    json extracted_json;
    std::map<std::string, std::string> json_map_response;

    if (r->raw_body_data_.length() > 0)
        extracted_json = json::parse(r->raw_body_data_); // create JSON object from string literal

    if (r->path_ == "/db" && extracted_json.size() > 0)
    {
        std::string id = extracted_json["id"];
        std::string item = extracted_json["item"];

        if (id.length() > 0 && item.length() > 0)
        {
            int result = Store::modifyItem(std::stoi(id), item);

            json_map_response = {{"status", "200 OK"}, {"id", id}};

            // // DEBUGGING Get the entire map
            // std::cout << "Full db :" << std::endl;
            // Store::animal_map all = Store::readItems();
            // json jmap(all);
            // std::cout << jmap.dump(4) << std::endl;
            // // DEBUGGING Get the entire map
            if (result != 0)
            {
                r->status_ = "401 Unauthorized";
                json_map_response = {{"status", "401 Unauthorized"}};
            }
        }
        else
        {
            // Default response
            r->status_ = "401 Unauthorized";
            json_map_response = {{"status", "401 Unauthorized"}};
        }
    }
    else
    {
        Handle_404(r);
        return;
    }

    Logger(r, json_map_response);
    r->answer_ = DataService::mapToString(json_map_response); // Find out how to receive data
}

void Controller::PUT_handler(webserver::http_request *r)
{

    Socket s = *(r->s_);

    json extracted_json;

    if (r->raw_body_data_.length() > 0)
        extracted_json = json::parse(r->raw_body_data_); // create JSON object from string literal

    std::map<std::string, std::string> json_map_response;

    // // --------------------------------------- //
    // std::cout << "------------------------------------------" << std::endl;

    // std::cout << "extracted_json : " << std::endl;
    // std::cout << extracted_json << std::endl;

    // std::cout
    //     << "extracted_json['id'] extracted_json['item']: "
    //     << extracted_json["id"]
    //     << " "
    //     << extracted_json["item"]
    //     << std::endl;

    // std::cout
    //     << "------------------------------------------" << std::endl;
    // // --------------------------------------- //

    // Only allowing put requests to local database
    // Putting to the database only needs extracted json
    // Route allowed is only db
    if (r->path_ == "/db")
    {
        std::string id = extracted_json["id"];
        std::string item = extracted_json["item"];

        if (id.length() > 0 && item.length() > 0)
        {
            Store::addItem(std::stoi(id), item);

            // // DEBUGGING Get the entire map
            // std::cout << "Full db :" << std::endl;
            // Store::animal_map all = Store::readItems();
            // json jmap(all);
            // std::cout << jmap.dump(4) << std::endl;
            // // DEBUGGING Get the entire map

            json_map_response = {{"status", "200 OK"}, {"id", id}};
        }
        else
        {
            // Default response
            r->status_ = "401 Unauthorized";
            json_map_response = {{"status", "401 Unauthorized"}};
        }
    }
    else
    {
        Handle_404(r);
        return;
    };

    Logger(r, json_map_response);
    r->answer_ = DataService::mapToString(json_map_response); // Find out how to receive data
}

void Controller::DELETE_handler(webserver::http_request *r)
{
    Socket s = *(r->s_);
    std::string params;

    if (r->params_.size() > 0)
    {
        params = DataService::mapToString(r->params_);
    }

    std::map<std::string, std::string> json_map_response;

    if (r->path_.find("all") == std::string::npos && r->path_.find("db") != std::string::npos && params.length() > 2 && r->params_["id"].length() > 0)
    {

        std::string id_string = r->params_["id"];
        int id = std::stoi(id_string);

        int result = Store::removeItem(id);

        if (result == 0) // Successful
            json_map_response = {{"status", "200 OK"}, {"id", id_string}};
        else
        {
            r->status_ = "500 Server Error";
            json_map_response = {{"status", "500 Server Error"}};
        }
    }
    else if (r->path_ == "/db/all" && params.length() == 0)
    {
        Store::removeEverything();

        json_map_response = {{"status", "200 OK"}};
    }
    else
    {
        Handle_404(r);
        return;
    }

    Logger(r, json_map_response);
    r->answer_ = DataService::mapToString(json_map_response); // Find out how to receive data
};

void Controller::Handle_404(webserver::http_request *r)
{

    std::map<std::string, std::string> json_map_response;

    r->status_ = "404 Not Found";
    json_map_response = {{"status", "404 Not Found"}};

    Logger(r, json_map_response);
    r->answer_ = DataService::mapToString(json_map_response); // Find out how to receive data
}
