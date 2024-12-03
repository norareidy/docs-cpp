#include <iostream>

#include <bson/bson.h>
#include <mongoc/mongoc.h>


int main() {
    mongocxx::instance instance;
    mongocxx::uri uri("<connection string>");
    mongocxx::client client(uri);
    mongocxx::database database = client["db"];

    {
        // start-access-database-method
        auto db = client.database("test_database");
        // end-access-database-method
    }

    {
        // start-access-database-operator
        auto db = client["test_database"];
        // end-access-database-operator
    }

    {
        // start-access-collection-method
        auto coll = database.collection("test_collection");
        // end-access-collection-method
    }

    {
        // start-access-collection-operator
        auto coll = database["test_collection"];
        // end-access-collection-operator
    }

    {
        // start-create-collection
        auto coll = database.create_collection("example_collection");
        // end-create-collection
    }

    {
        // start-find-collections
        auto cursor = database.list_collections();

        for(auto&& doc : cursor) {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        }
        // end-find-collections
    }

    {
        // start-find-collection-names
        auto list = database.list_collection_names();

        for(auto&& name : list) {
            std::cout << bsoncxx::to_json(name) << std::endl;
        }
        // end-find-collection-names
    }

    {
        // start-delete-collection
        auto coll = database["test_collection"];
        coll.drop();
        // end-delete-collection
    }

    {
        mongoc_client_t *client = mongoc_client_new ("<connection string URI>");
        mongoc_database_t *database = mongoc_client_get_database (client, "test_database");
        // start-database-read-prefs
        mongoc_read_prefs_t *read_prefs = mongoc_read_prefs_new (MONGOC_READ_PRIMARY_PREFERRED);
        mongoc_database_set_read_prefs (database, read_prefs);
        // end-database-read-prefs
        mongoc_read_prefs_destroy (read_prefs);
        mongoc_database_destroy (database);
        mongoc_client_destroy (client);
    }

    {
        mongoc_client_t *client = mongoc_client_new ("<connection string URI>");
        mongoc_database_t *database = mongoc_client_get_database (client, "test_database");
        mongoc_collection_t *collection = mongoc_database_get_collection (database, "test_collection");
        // start-collection-read-prefs
        mongoc_read_prefs_t *read_prefs = mongoc_read_prefs_new (MONGOC_READ_PRIMARY_PREFERRED);
        mongoc_collection_set_read_prefs(collection, read_prefs);
        // end-collection-read-prefs
        mongoc_read_prefs_destroy (read_prefs);
        mongoc_collection_destroy (collection);
        mongoc_database_destroy (database);
        mongoc_client_destroy (client);
    }

    {
        // start-tags
        mongoc_read_prefs_t *read_prefs = mongoc_read_prefs_new (MONGOC_READ_SECONDARY_PREFERRED);
        bson_t *tags = BCON_NEW ("DC", BCON_UTF8("ny"), "DC", BCON_UTF8("sf"));
        // end-tags
        mongoc_read_prefs_destroy (read_prefs);
    }

    {
        // start-local-threshold
        const char *uri_string = "mongodb://localhost:27017/?localThresholdMS=35";
        mongoc_client_t *client = mongoc_client_new (uri_string);
        // end-local-threshold
        mongoc_client_destroy (client);
    }

    mongoc_cleanup ();

    return EXIT_SUCCESS;
}