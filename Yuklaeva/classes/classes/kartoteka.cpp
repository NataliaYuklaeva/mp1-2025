/*
файл input.txt:
title=Robinson_Crusoe author=Daniel_Defoe year=1719 pages=256
title=Frankenstein author=Mary_Shelley year=1818 pages=384
title=Alice's_Adventures_in_Wonderland author=Lewis_Carroll year=1865 pages=192
*/
/*#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <clocale>

class Book {
public:
    std::string title;
    std::string author;
    int year = 0;
    int pages = 0;

    void parseFromString(const std::string& line) {
        std::istringstream iss(line);
        std::string token, key, value;

        while (iss >> token) {
            size_t pos = token.find('=');
            if (pos != std::string::npos) {
                key = token.substr(0, pos);
                value = token.substr(pos + 1);

                if (key == "title") {
                    title = value;
                }
                else if (key == "author") {
                    author = value;
                }
                else if (key == "year") {
                    try {
                        year = std::stoi(value);
                    }
                    catch (...) {}
                }
                else if (key == "pages") {
                    try {
                        pages = std::stoi(value);
                    }
                    catch (...) {}
                }
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Book& b) {
        os << b.title << " by " << b.author << " (" << b.year << ") [" << b.pages << " страниц]";
        return os;
    }
};

class Library {
private:
    std::vector<Book> books;

public:
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Ошибка открытия файла.");
        }

        std::string line;
        while (std::getline(file, line)) {
            Book new_book;
            new_book.parseFromString(line);
            books.push_back(new_book);
        }
        file.close();
    }

    void printAllBooks() const {
        std::cout << "\nВсего загружено книг: " << books.size() << "\n";
        for (size_t i = 0; i < books.size(); ++i) {
            std::cout << i + 1 << ". " << books[i] << "\n";
        }
    }

    void findBooksByAuthor(const std::string& author) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.author == author) {
                std::cout << book << "\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "Нет книг данного автора.\n";
        }
    }

    void findBooksAfterYear(int year) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.year >= year) {
                std::cout << book << "\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "Нет книг, изданных позже указанного года.\n";
        }
    }

    void findBooksWithMinPages(int min_pages) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.pages >= min_pages) {
                std::cout << book << "\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "Нет книг с указанным количеством страниц.\n";
        }
    }
    void saveToFile(const std::string& filename) const {
        std::ofstream out_file(filename);
        if (!out_file.is_open())
            throw std::runtime_error("Ошибка открытия выходного файла.");

        out_file << "Номер\tНазвание\tАвтор\tГод\tСтраниц\n";
        for (size_t i = 0; i < books.size(); ++i) {
            out_file << i + 1 << "\t" << books[i].title << "\t" << books[i].author << "\t" << books[i].year << "\t" << books[i].pages << "\n";
        }
        out_file.close();
    }
};

int main() {
    std::setlocale(LC_ALL, "Russian");
    try {
        Library library;
        library.loadFromFile("D:\\input.txt"); // Обязательно укажите верный путь к файлу
        library.printAllBooks();
        library.saveToFile("D:\\output.txt");

        std::string search_author;
        int search_year, search_pages;

        std::cout << "\nВведите имя автора для поиска книг: ";
        std::cin >> search_author;
        library.findBooksByAuthor(search_author);

        std::cout << "\nВведите год, начиная с которого искать книги: ";
        std::cin >> search_year;
        library.findBooksAfterYear(search_year);

        std::cout << "\nВведите минимальное количество страниц для поиска книг: ";
        std::cin >> search_pages;
        library.findBooksWithMinPages(search_pages);
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
    }

    return 0;
}*/