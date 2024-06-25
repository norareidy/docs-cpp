#include <cstdint>
#include <iostream>
#include <vector>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

int main() {
    mongocxx::instance instance{};
    mongocxx::uri uri("<connection string>");
    mongocxx::client client(uri);

    // start-db-coll
    auto db = client["sample_restaurants"];
    auto collection = db["restaurants"];
    // end-db-coll

    // start-insert-one
    auto result = collection.insert_one(make_document(kvp("name", "Mongo's Burgers")));
    // end-insert-one

    // start-insert-many
    std::vector<bsoncxx::document::value> restaurants;
    restaurants.push_back(make_document(kvp("name", "Mongo's Burgers")));
    restaurants.push_back(make_document(kvp("name", "Mongo's Pizza")));

    auto result = collection.insert_many(restaurants);
    // end-insert-many

    // start-cursor
    auto cursor = collection.find(make_document(kvp("founded_year", 1970)));
    for(auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << "\n" << std::endl;
    }
    // end-cursor
 
   // start-modify
    mongocxx::options::find opts;
    opts.limit(5);
    auto cursor = collection.find(make_document(kvp("number_of_employees", 1000)), opts);
   // end-modify

}