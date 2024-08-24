#include <crow.h>
#include <crow/http_response.h>
#include <crow/json.h> // Include the nlohmann/json library header
#include <crow/mustache.h>
#include <filesystem>

int main() {
    crow::SimpleApp app;
    crow::mustache::set_base("templates/");
    // Define a route to handle POST requests with JSON data
    CROW_ROUTE(app, "/sigin")
        .methods(crow::HTTPMethod::Post)([](const crow::request& req) {
            // Parse the JSON data
            auto json_data = crow::json::load(req.body);
            if (!json_data) {
                return crow::response(404,"Invalid json");
            }

            // Extract data from the JSON object
            std::string name = json_data["username"].s();
            std::string password = json_data["password"].s();

            // Process the data (e.g., print it)
            std::cout << "Received name: " << name << ", password: " << password << std::endl;

            // Create a JSON response
            // crow::json::wvalue response;
            // response["status"] = "success";
            // response["received_name"] = name;
            // response["received_age"] = password;
            crow::mustache::context ctx;
            ctx["username"] = name;
            auto page = crow::mustache::load("welcome.html");
            crow::response res(page.render(ctx));
            res.add_header("Cache-Control", "no-cache, no-store, must-revalidate");
            res.add_header("Content-type", "text/html");
            
            return res;
            // return crow::response(response);
        });
    CROW_ROUTE(app, "/<path>")
    ([](const crow::request&, crow::response& res, std::string path){
        std::string file_path = "templates/" + path;

        // Check if the file exists directly (e.g., CSS, JS, images, etc.)
        if (std::filesystem::exists(file_path) && !std::filesystem::is_directory(file_path)) {
            res.set_static_file_info(file_path);
            res.end();
        }
        // Check if appending ".html" results in a valid file
        else if (std::filesystem::exists(file_path + ".html") && !std::filesystem::is_directory(file_path + ".html")) {
            res.set_static_file_info(file_path + ".html");
            res.end();
        }
        else {
            res.code = 404;
            res.end("File not found");
        }
    });

    // Default route to serve index.html
    CROW_ROUTE(app, "/")
    ([](const crow::request&, crow::response& res){
        std::string file_path = "templates/index.html";

        // Check if index.html exists
        if (std::filesystem::exists(file_path) && !std::filesystem::is_directory(file_path)) {
            res.set_static_file_info(file_path);
            res.end();
        } else {
            res.code = 404;
            res.end("File not found");
        }
    });

    // Run the app on port 18080
    app.port(18080).multithreaded().run();

    return 0;
}
