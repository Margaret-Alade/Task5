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
    void create_table_person(pqxx::connection& con) {
        pqxx::work work1(con);
        work1.exec("CREATE TABLE IF NOT EXISTS Person (id serial PRIMARY KEY, name varchar(20) NOT NULL, surname varchar(20) NOT NULL, email varchar(50) NOT NULL);");
        work1.commit();
    }
    
    void create_table_person_info(pqxx::connection& con) {
        pqxx::work work1(con);
        work1.exec("CREATE TABLE IF NOT EXISTS PersonInfo (id serial PRIMARY KEY, person_id integer NOT NULL REFERENCES Person(id), number varchar(20));");
        work1.commit();
    }
    
    void insert(pqxx::connection& con, std::string str_query) {
        pqxx::work work1(con);
        work1.exec(str_query);
        work1.commit();
    }
    
    void update(pqxx::connection& con, std::string str_query) {
        pqxx::work work1(con);
        work1.exec(str_query);
        work1.commit();
    }
    
    void delet(pqxx::connection& con, std::string str_query) {
        pqxx::work work1(con);
        work1.exec(str_query);
        work1.commit();
    }
    
    void select (pqxx::connection& con, std::string str_query, pqxx::result& rows) {
        pqxx::work work1(con);
        rows = work1.exec(str_query);
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
        
        database.create_table_person(con);
        database.create_table_person_info(con);
        database.insert(con, "INSERT INTO Person(name,surname,email) "
                          "VALUES('Петр', 'Тимофеев', 'petrtimofeev@gmail.com')");
        database.insert(con, "INSERT INTO Person(name,surname,email) "
                          "VALUES('Максим', 'Прончев', 'maxpronchev@yandex.ru')");
        database.insert(con, "INSERT INTO Person(name,surname,email) "
                          "VALUES('Ольга', 'Сарокина', 'olga.soroka@yandex.ru')");
        database.update(con,"UPDATE Person SET surname='Сорокина' WHERE surname='Сарокина'");

        database.insert(con, "INSERT INTO PersonInfo(person_id, number) "
                          "VALUES(1, '+79156094521')");
        database.insert(con, "INSERT INTO PersonInfo(person_id, number) "
                          "VALUES(1, '+79995018063')");
        database.insert(con, "INSERT INTO PersonInfo(person_id) "
                          "VALUES(2)");
        database.insert(con, "INSERT INTO PersonInfo(person_id, number) "
                          "VALUES(3, '+79015320921')");
        pqxx::result rows;
        database.select(con, "SELECT id, name, surname FROM Person", rows);
        
        std::cout << "Список клиентов:" << "\n";
        
        for (int i = 0; i < rows.size(); i++) {
            auto[id, name, surname] = rows[i].as<int, std::string, std::string>();
            std::cout << id << ", " << name << ", " << surname << "\n";
        }
        pqxx::result rows2;
        database.select(con, "SELECT id, person_id, number FROM PersonInfo WHERE number IS NOT NULL", rows2);
        
        std::cout << "Список номеров клиентов:" << "\n";
        
        for (int i = 0; i < rows2.size(); i++) {
            auto[id, person_id, number] = rows2[i].as<int, int, std::string>();
            std::cout << id << ", " << person_id << ", " << number << "\n";
        }
        
        
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
    
    
                    
    
    
    
    
    
    
    
    
}


