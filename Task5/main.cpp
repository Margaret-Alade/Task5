//
//  main.cpp
//  Task5
//
//  Created by Маргарет  on 12.04.2024.
//

#include <iostream>
#include <pqxx/pqxx>

class Database {
public:
    Database() = default;
    void create_table_person(pqxx::work& work1) {
        work1.exec("CREATE TABLE IF NOT EXISTS Person (id serial PRIMARY KEY, name varchar(20) NOT NULL, surname varchar(20) NOT NULL, email varchar(50) NOT NULL);");
        work1.commit();
    }
    
    void create_table_person_info(pqxx::work& work1) {
        work1.exec("CREATE TABLE IF NOT EXISTS PersonInfo (id serial PRIMARY KEY, person_id integer NOT NULL REFERENCES Person(id), number varchar(20));");
        work1.commit();
    }
    
    void insert_person(pqxx::work& work1, std::string str_query) {
        work1.exec(str_query);
        work1.commit();
    }
    
    void insert_num(pqxx::work& work1, std::string str_query) {
        work1.exec(str_query);
        work1.commit();
    }
    
    void update_person(pqxx::work& work1, std::string str_query) {
        work1.exec(str_query);
        work1.commit();
    }
    
    void update_num(pqxx::work& work1, std::string str_query) {
        work1.exec(str_query);
        work1.commit();
    }
    
    void delet_person(pqxx::work& work1, std::string str_query) {
        work1.exec(str_query);
        work1.commit();
    }
    
    void delet_num(pqxx::work& work1, std::string str_query) {
        work1.exec(str_query);
        work1.commit();
    }
    
    void select_person(pqxx::work& work1, pqxx::result& rows) {
        rows = work1.exec("SELECT id, name, surname, email FROM Person");
    }
    
    void select_person_info(pqxx::work& work1, pqxx::result& rows) {
        rows = work1.exec("SELECT id, person_id, number FROM PersonInfo WHERE number IS NOT NULL");
    }
};


int main() {
    
    try {
    pqxx::connection con (
        "host=MacBook-Air-Margaret.local "
        "port=5432 "
        "dbname=task5 "
        "user=postgres "
        "password=8563"
    );
        
        std::cout << "Connection is established" << "\n";
        Database database;
        pqxx::work work1(con);
        database.create_table_person(work1);
        pqxx::work work2(con);
        database.create_table_person_info(work2);
        
        std::string name, surname, email, num;
        
        std::cout << "Введите имя 1 клиента:";
        std::cin >> name;
        std::cout << "Введите фамилию 1 клиента:";
        std::cin >> surname;
        std::cout << "Введите email 1 клиента:";
        std::cin >> email;
        pqxx::work work3(con);
        database.insert_person(work3, "INSERT INTO Person(name, surname, email) "
                                  "VALUES('" + work3.esc(name) + "', '" + work3.esc(surname) + "', '" + work3.esc(email) + "')");
        do {
            std::cout << "Введите номер телефона 1 клиента. Поставьте 0, если не хотите вводить номер. Поставьте 0, если у клиента больше нет номеров:";
            std::cin >> num;
            
            if (num != "0") {
                pqxx::work work4(con);
                database.insert_num(work4, "INSERT INTO PersonInfo(person_id, number) "
                                    "VALUES(1,'" + work4.esc(num) + "')");
            }
        } while (num != "0");
        
        std::cout << "Введите имя 2 клиента:";
        std::cin >> name;
        std::cout << "Введите фамилию 2 клиента:";
        std::cin >> surname;
        std::cout << "Введите email 2 клиента:";
        std::cin >> email;
        pqxx::work work5(con);
        database.insert_person(work5, "INSERT INTO Person(name, surname, email) "
                                  "VALUES('" + work5.esc(name) + "', '" + work5.esc(surname) + "', '" + work5.esc(email) + "')");
        do {
            std::cout << "Введите номер телефона 2 клиента. Поставьте 0, если не хотите вводить номер. Поставьте 0, если у клиента больше нет номеров:";
            std::cin >> num;
            
            if (num != "0") {
                pqxx::work work6(con);
                database.insert_num(work6, "INSERT INTO PersonInfo(person_id, number) "
                                    "VALUES(2,'" + work6.esc(num) + "')");
            }
        } while (num != "0");
        
        pqxx::result rows;
        pqxx::work work7(con);
        database.select_person(work7, rows);
        std::cout << "Список клиентов:" << "\n";
        for (int i = 0; i < rows.size(); i++) {
            auto[id, name, surname, email] = rows[i].as<int, std::string, std::string, std::string>();
            std::cout << id << ", " << name << ", " << surname <<  ", " << email << "\n";
        }
        
        pqxx::result rows2;
        database.select_person_info(work7, rows2);
        
        std::cout << "Список номеров клиентов:" << "\n";
        
        for (int i = 0; i < rows2.size(); i++) {
            auto[id, person_id, number] = rows2[i].as<int, int, std::string>();
            std::cout << id << ", " << person_id << ", " << number << "\n";
        }
        
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
    
    
                    
    
    
    
    
    
    
    
    
}


