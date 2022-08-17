#include <string>
#include <vector>
class account
{
    private:
        std::string name;
        std::string surname;
        std::string acc_number;
        std::string password;
        std::string balance;
        std::string request;
    public:
        void set_name(std::string tmp);
        void set_surname(std::string tmp);
        void set_acc_number(std::string tmp);
        void set_balance(std::string tmp);
        void set_password(std::string tmp);
        void set_request(std::string tmp);
    public:
        std::string get_name();
        std::string get_surname();
        std::string get_acc_number();
        std::string get_password();
        std::string get_balance();
        std::string get_request();
};

void login();
void account_info();
void action();
bool witdraw();
void account_resolving();
void request(std::vector <std::string> request_info);
void request_sort(std::string str);
