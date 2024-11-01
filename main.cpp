#include <crow.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string load_html(const string& path);

int main() {
    crow::SimpleApp app;
    
    CROW_ROUTE(app, "/echo")([]() {
        string html_content;
        try {
            html_content = load_html("index.html");
        }
        catch (invalid_argument) {
            return crow::response(502, "");
        }
        return crow::response(200, html_content);
    });

    CROW_ROUTE(app, "/echo_helper")([]() {
        cout << "ECHO" << endl;
        crow::response res(302);
        res.set_header("Location", "/echo");
        return res;
    });

    app.port(8000).multithreaded().run();

    return 0;
}

string load_html(const string& path) {
    fstream file(path);
    if (!file.is_open()) {
        throw invalid_argument("Provided file path is invalid");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

