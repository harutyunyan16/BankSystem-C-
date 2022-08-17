#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include "bank.h"


void login();
void account_info();
void action();
bool witdraw();
void account_resolving();
void request();
void request_sort(std::string str);


account a;
account current_acc;
void account::set_name(std::string tmp)
{
    name = tmp;
}

void account::set_surname(std::string tmp)
{
    surname = tmp;
}

void account::set_acc_number(std::string tmp)
{
    acc_number = tmp;
}

void account::set_balance(std::string tmp)
{
    balance = tmp;
}

void account::set_password(std::string tmp)
{
    password = tmp;
}

void account::set_request(std::string tmp)
{
    request = tmp;
}




std::string account::get_name()
{
    return this -> name;
}

std::string account::get_surname()
{
    return this -> surname;
}

std::string account::get_acc_number()
{
    return this -> acc_number;
}

std::string account::get_balance()
{
    return this -> balance;
}

std::string account::get_password()
{
    return this -> password;
}

std::string account::get_request()
{
    return this -> request;
}




std::vector <account> accounts;


void account_resolving()
{
    std::ifstream fayl("accounts.txt");
    std::string line;

    

    while(std::getline(fayl,line))
    {
        account tmp_obj;
        std::vector <std::string> info;
        int i{};
        
        while(line[i] != '\0' || line[i + 1] != '\0')
        {
            std::string tmp;

            while(line[i] != '-' && line[i] != '\0')
            {
                tmp += line[i];
                i++;
            }
            info.push_back(tmp);
            i++;
        }
        tmp_obj.set_name(info[0]);
        tmp_obj.set_surname(info[1]);
        tmp_obj.set_acc_number(info[2]);
        tmp_obj.set_password(info[3]);
        tmp_obj.set_balance(info[4]);
        tmp_obj.set_request(info[5]);
        accounts.push_back(tmp_obj);
    }
    fayl.close();
    
}



bool witdraw()
{
    system("clear");
    account_info();
    witdraw_again:
    std::cout << "Type the sum to withdraw ('exit' - for exiting) :  ";
    std::string sum;
    std::cin >> sum;
    if(sum == "exit")
    {
        return false;
    }
    for(int i = 0;i < sum.length();i++)
    {
        if(sum[i] >= '0' && sum[i] <='9')
        {
            continue;
        }else
        {
            std::cout << "Incorrect type !" << std::endl;
            goto witdraw_again;
        }
    }
    int sum_integer = std::stoi(sum);
    int sum_account = std::stoi(current_acc.get_balance());
    if(sum_integer > sum_account)
    {
        std::cout << "Number is greater the balance !" << std::endl;
        goto witdraw_again;
    }else
    {
        current_acc.set_balance(std::to_string(sum_account - sum_integer));
    }
    return true;
}




void request(std::vector <std::string> request_info)
{
    system("clear");
    account_info();
    std::cout << std::endl;
    std::cout << "[REQUESTS]" << std::endl << std::endl;
    std::cout << "Account number  :  " << request_info[0] << std::endl;
    std::cout << "Value           :  " << request_info[1] << std::endl;
    std::cout << "Request type    :  " << request_info[2] << std::endl;
    std::cout << "yes - accept : no - reject : exit - exit" << std::endl;
    
    std::string command;
    std::cin >> command;
    int curent_money = std::stoi(current_acc.get_balance());
    int add_money = std::stoi(request_info[1]);
    if(request_info[2] == "input")
    {
        if(command == "yes" || command[0] == 'y')
        {
            current_acc.set_balance(std::to_string(curent_money + add_money));
            std::cout << "Request is succesfuly accepeted !" << std::endl;
            current_acc.set_request("");
        }else if(command == "no" || command[0] == 'n')
        {
            for(account& obj : accounts)
            {
                if(obj.get_acc_number() == request_info[0])
                {
                    obj.set_balance(std::to_string(std::stoi(obj.get_balance()) + add_money));
                    break;
                }
            }
            current_acc.set_request("");

            std::cout << "Request is succesfuly rejected !" << std::endl;

        }else if(command == "exit" || command[0] == 'e')
        {
            return;
        }
    }else if(request_info[2] == "output")
    {
        if(command == "yes" || command[0] == 'y')
        {
            if(add_money < curent_money)
            {
                current_acc.set_balance(std::to_string(curent_money - add_money));
                std::cout << "Request is succesfuly accepeted !" << std::endl;
                current_acc.set_request("");
                for(account& obj : accounts)
                {
                    if(obj.get_acc_number() == request_info[0])
                    {
                        obj.set_balance(std::to_string(std::stoi(obj.get_balance()) + add_money));
                    }
                }
            }
        }else if(command == "no" || command[0] == 'n')
        {
            current_acc.set_request("");
            std::cout << "Request is succesfuly rejected !" << std::endl;
        }else if(command == "exit" || command[0] == 'e')
        {
            return;
        } 
    }
}

void send()
{
    std::string adress;
    std::string value = "0";
    std::string type;
    bool a = false;
    int tmp_obj;
    while(adress != "exit")
    {
        std::cout << "Type the adress : ";
        std::cin >> adress;
        if(adress == current_acc.get_acc_number())
        {
            std::cout << "It is your number !" << std::endl;
            continue;
        }

        for(int i = 0;i < accounts.size();i++)
        {
            if(accounts[i].get_acc_number() == adress)
            {
                a = true;
                tmp_obj = i;
                break;
            }
        }
        if(a == true)
            break;
    }
    if(adress == "exit")
        return;

    while(1)
    {
        std::cout << "Type the type   : ";
        std::cin >> type;
        if(type == "exit")
        {
            return;
        }
        if(type != "output" && type != "input")
        {
            std::cout << "Incorrect type !" << std::endl;
        }
        if(type == "input" || type == "output")
        {
            break;
        }
    }

    if(type == "input")
    {
        again:
        std::cout << "Type the value : ";
        std::cin >> value;
        for(int i = 0;i < value.length();i++)
        {
            if(value[i] >= '0' && value[i] <= '9')
            {
                continue;
            }else
            {
                std::cout << "Incorrect type !" << std::endl;
                goto again;
            }
        }
        if(std::stoi(current_acc.get_balance()) < std::stoi(value))
        {
            std::cout << "Too much cash !" << std::endl;
            goto again;
        }
        current_acc.set_balance(std::to_string(std::stoi(current_acc.get_balance()) - std::stoi(value)));
    }else if(type == "output")
    {
        again_o:
        std::cout << "Type the value : ";
        std::cin >> value;
        for(int i = 0;i < value.length();i++)
        {
            if(value[i] >= '0' && value[i] <= '9')
            {
                continue;
            }else   
            {
                std::cout << "Incorrect type !" << std::endl;
                goto again_o;
            }
        }
    }
    accounts[tmp_obj].set_request(current_acc.get_acc_number() + ":" + value + ":" + type + "?");
}



void action()
{
    
    std::string command;
    account_info();

    while(command != "exit" || command[0] != 'e')
    {
        std::cout << std::endl << "Type the action :" << std::endl;
        std::cout << "(withdraw - 00 )" << std::endl;
        std::cout << "(send another account - 01)" << std::endl; 
        std::cout << "(see requests - 02)" << std::endl;
        std::cout << "->";
        std::cin >> command;
        
        if(command == "00")
        {
            if(witdraw())
            {
                system("clear");
                account_info();
                
            }
        }else if(command == "02")
        {
            system("clear");
            account_info();
            if(current_acc.get_request() != "")
            {
                request_sort(current_acc.get_request());
                system("clear");
                account_info();
                continue;
            }
            std::cout << "There are not requests !" << std::endl;
        }else if(command == "01")
        {
            system("clear");
            account_info();
            send();
            system("clear");
            account_info();
            std::cout << std::endl <<"Request sent !" << std::endl;
        }
    }
    system("clear");
}



void account_info()
{
    std::cout << "Person name      :  " << current_acc.get_name() << std::endl;
    std::cout << "Person surname   :  " << current_acc.get_surname() << std::endl;
    std::cout << "Account balance  :  " << current_acc.get_balance() << "$" << std::endl;
    return;
}



void request_sort(std::string str)
{

    std::vector <std::string> request_info;
    std::string from = str.substr(0,8);
    std::string value;
    std::string type;

    str = str.substr(9);
    int i{0};
 
    while(str[i] != ':')
    {
        value += str[i];
        i++;
    }
    str = str.substr(i + 1);
    int index = str.find('?');
    type = str.substr(0,index);
   
    request_info.push_back(from);
    request_info.push_back(value);
    request_info.push_back(type);
    request(request_info);
}






void login()
{
    std::string login;
    std::string password;
    int line_index{};

    while(1)
    {
        system("clear");
        std::cout << "Login : ";
        std::cin >> login;
        if(login == "exit")
        {
            break;
        }
        for(auto& acc : accounts)
        {
            line_index++;
            if(login == acc.get_acc_number())
            {
                system("clear");
                std::cout << "Password : ";
                std::cin >> password;
                if(password == "exit")
                {
                    break;
                }
                if(password == acc.get_password())
                {

                    system("clear");
                    std::cout << "Acces denied !" << std::endl;
                    current_acc = acc;  
                    action();
                    break;
                }
            }
        } 
    }
    std::ofstream fayl("accounts.txt");

    for(int i = 0;i < accounts.size();i++)
    {
        if(line_index == i + 1)
        {
            fayl << current_acc.get_name() << "-" << current_acc.get_surname() << "-" << current_acc.get_acc_number() << "-" << current_acc.get_password() << "-" << current_acc.get_balance() << "-" << current_acc.get_request() << std::endl;
            continue;
        }
        fayl << accounts[i].get_name() << "-" << accounts[i].get_surname() << "-" << accounts[i].get_acc_number() << "-" << accounts[i].get_password() << "-" << accounts[i].get_balance() << "-" << accounts[i].get_request() << std::endl;
    }
    
    return;
}