#include <httplib.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "rand.h"

int main(void)
{

    Gen *a[] = {
        new MidSquare(12345678),
        new MidMulti(12345678),
        new MixSum(1234567890),
        new LCG(1)
    };

    /*std::string out = "rand";
    std::ofstream csv;
    for (int i = 0; i < 4; i++)
    {
        out = "rand";
        for (int j = 0; j < 10000; j++) {
            out += '\n' + std::to_string((*a[i]).next());
        }
        csv.open("Z:/rand"+std::to_string(i)+".csv");
        csv << out;
        csv.close();
    }*/


    //return 0;




    using namespace httplib;

    Server svr;

    svr.Get("/1", [a](const Request& req, Response& res) {
        int n = 100;
        if (req.has_param("N")) {
            n = std::stoi(req.get_param_value("N"));
        }
        std::cout << n;
        std::string out = "rand";
            for (int j = 0; j < n; j++) {
                out += '\n' + std::to_string((*a[0]).next());
            }
        res.set_content(out, "text/plain");
    });

    svr.Get("/hi", [](const Request& req, Response& res) {
        res.set_content("Hello World!", "text/plain");
        });
    svr.Get("/sleep", [](const Request& req, Response& res) {
        Sleep(10000);
        res.set_content("wake up!", "text/plain");
        });

    svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
        auto numbers = req.matches[1];
        res.set_content(numbers, "text/plain");
        });

    svr.Get("/body-header-param", [](const Request& req, Response& res) {
        if (req.has_header("Content-Length")) {
            auto val = req.get_header_value("Content-Length");
        }
        if (req.has_param("key")) {
            auto val = req.get_param_value("key");
        }
        auto val = req.get_param_value("key");
        res.set_content(val, "text/plain");
        });

    svr.Get("/get", [](const Request& req, Response& res) {
        std::string body = "params:";

        for (const auto& kv : req.params) {
            body += '\n' + kv.first + ": " + kv.second;
        }

        res.set_content(body, "text/plain");
        });

    svr.Get("/stop", [&](const Request& req, Response& res) {
        svr.stop();
        });

    svr.listen("localhost", 4444);
}