#include "crow.h"
#include <filesystem>

int main() {
    crow::SimpleApp app;

    // Serve files, appending ".html" if necessary and if no other file type is found
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

    app.port(18080).multithreaded().run();
}
