#include <crow.h>
#include <filesystem>
#include <fstream>

int main() {
    crow::SimpleApp app;

    // Serve static files from the "public" directory
    CROW_ROUTE(app, "/<string>")
    ([](const crow::request&, crow::response& res, std::string path){
        // std::string file_path = "templates/" + path;
        
        // // Check if file exists and is not a directory
        // if (std::filesystem::exists(file_path) && !std::filesystem::is_directory(file_path)) {
        //     res.set_static_file_info(file_path);
        //     res.end();
        // } else {
        //     res.code = 404;
            
        //     res.end("File not found");
        // }
        std::string file_path = "templates/" + path;
        std::ifstream file(file_path);
        if(!file.is_open()) {
            res.code = 404;
            res.end("File not found");
        }
        std::string fileContent((std::istreambuf_iterator<char>(file)), 
                       std::istreambuf_iterator<char>()); 
        res.write(fileContent);
        res.end();
    });

    // Default route to serve index.html
    CROW_ROUTE(app, "/")
    ([](const crow::request&, crow::response& res){
        std::string file_path = "public/index.html";
        
        // Check if index.html exists
        if (std::filesystem::exists(file_path) && !std::filesystem::is_directory(file_path)) {
            res.set_static_file_info(file_path);
            res.end();
        } else {
            res.code = 404;
            res.end("File not found");
        }
    });

    app.port(8080).multithreaded().run();
}
