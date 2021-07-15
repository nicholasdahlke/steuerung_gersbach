#include <cpr/cpr.h>
#include <iostream>
#include "controller.h"

Controller::Controller() {

}
void Controller::setIp(std::string& ip) {
    if (ip == "")
        return;
    Controller::ip_addr = ip;
}
void Controller::setPort(std::string &port) {
    if(port == "")
        return;
    Controller::port = port;
}
int Controller::getConnectionStatus() {
    std::cout << getRequest(ip_addr, port, {{"test", "text"},{"text","texttt"}}) << std::endl;
}

std::string Controller::getRequest(std::string url, std::string port, std::map<std::string, std::string> parameters) {

    cpr::Response response = cpr::Get(cpr::Url{std::string((port == "443") ? "https" : "http") + "://" + url + ":" + port},parameters);
    return (response.status_code == 200) ? response.text : "Error";
}

