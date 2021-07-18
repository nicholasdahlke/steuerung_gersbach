#include <string>
#include <cpr/cpr.h>

class Controller {
public:
    Controller();
    void setIp(std::string const& ip);
    void setPort(std::string const& port);
    int getConnectionStatus();
private:
    std::string ip_addr;
    std::string port;
    std::string getRequest(std::string url, std::string port, std::map<std::string, std::string> parameters);

};


