#include <string>
#include <iostream>
#include <pqxx/pqxx>
#include <json-c/json.h>
#include <crow/json.h>

struct jobjs {
    json_object* jname;
    json_object* jage;
    json_object* jemail;
    json_object* jbalance;
};

struct persondata {
    char* name;
    char* age;
    char* email;
    char* balance;
};

int main()
{
    std::string connectionString = " port=5432 dbname=test user=soethiha password=sirsoe11197 hostaddr=127.0.0.1";
    json_object *root = json_object_from_file("test.json");
    persondata pd;
    jobjs jd;
    try
    {
        jd.jname = json_object_object_get(root,  "name");
        jd.jage = json_object_object_get(root,  "age");
        jd.jemail = json_object_object_get(root,  "email");
        jd.jbalance = json_object_object_get(root,  "balance");
        // Store the string values of these json_objects in our char arrays
        pd.name = strdup(json_object_get_string(jd.jname));
        pd.age = strdup(json_object_get_string(jd.jage));
        pd.email = strdup(json_object_get_string(jd.jemail));
        pd.balance = strdup(json_object_get_string(jd.jbalance));

        pqxx::connection connectionObject(connectionString.c_str());

        pqxx::work worker(connectionObject);
        std::string execstring = "INSERT INTO niggatable(name,age,email,balance)" + std::string(" VALUES(\'") + pd.name + std::string("\',") + pd.age + std::string(",\'") + pd.email + std::string("\',") + pd.balance + std::string(");");
        std::cout << execstring << "\n";
        pqxx::result response = worker.exec(execstring.c_str());

        worker.commit();
        json_object_put(root);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        json_object_put(root);
    }

}
