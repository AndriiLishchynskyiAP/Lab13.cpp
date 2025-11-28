#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <stdexcept>
#include <string>

#include "FilterData.hpp"
#include "Filter.hpp"
#include "LowPassFilter.hpp"
#include "BandPassFilter.hpp"

class FileException : public std::runtime_error {
public:
    FileException(const std::string& m) : std::runtime_error(m) {}
};

class InvalidIndex : public std::out_of_range {
public:
    InvalidIndex(const std::string& m) : std::out_of_range(m) {}
};

class InvalidInput : public std::invalid_argument {
public:
    InvalidInput(const std::string& m) : std::invalid_argument(m) {}
};

std::vector<FilterData> readDataFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw FileException("Неможливо відкрити файл: " + filename);
    }

    std::vector<FilterData> vec;
    std::string line;
    int line_num = 0;
    while (std::getline(ifs, line)) {
        line_num++;
        if (line.empty() || line.rfind("//", 0) == 0 || line.rfind("#", 0) == 0) continue;
        
        std::istringstream iss(line);
        FilterData d;
        if (!(iss >> d.type >> d.name >> d.f1 >> d.f2 >> d.r)) {
            throw InvalidInput("Некоректний формат у рядку " + std::to_string(line_num) + " файлу: " + filename);
        }
        vec.push_back(d);
    }
    return vec;
}

void writeDataFile(const std::string& filename, const std::vector<FilterData>& data) {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        throw FileException("Неможливо створити або відкрити файл для запису: " + filename);
    }
    
    ofs << "Вихідні дані фільтрів\n";
    for (const auto& d : data) {
        ofs << d.toString() << "\n";
    }
}

class FilterContainer {
public:
    void add(const FilterData& d) {
        vec.push_back(d);
    }
    const std::vector<FilterData>& data() const {
        return vec;
    }
    size_t size() const {
        return vec.size();
    }
    FilterData operator[](size_t index) const {
        if (index >= vec.size()) {
            throw InvalidIndex("Індекс поза діапазоном у FilterContainer.");
        }
        return vec[index];
    }
private:
    std::vector<FilterData> vec;
};

int main() {
    const std::string INPUT_FILENAME = "filters_input.txt";
    const std::string OUTPUT_FILENAME = "filters_output.txt";

    try {
        
        std::cout << "--- Етап 1: Читання даних із файлу ---\n";
        std::vector<FilterData> input_data = readDataFile(INPUT_FILENAME);
        std::cout << "Успішно прочитано " << input_data.size() << " записів фільтрів із " << INPUT_FILENAME << ".\n";

        FilterContainer c;
        for (const auto& x : input_data) {
            c.add(x);
        }

        std::vector<std::unique_ptr<Filter>> arr;

        std::cout << "\n--- Етап 2: Створення об'єктів фільтрів ---\n";
        for (const auto& d : c.data()) {
            if (d.type == "LP") {
                auto p = std::make_unique<LowPassFilter>();
                p->loadFromData(d);
                arr.push_back(std::move(p));
            } else if (d.type == "BP") {
                auto p = std::make_unique<BandPassFilter>();
                p->loadFromData(d);
                arr.push_back(std::move(p));
            } else {
                throw InvalidInput("Знайдено невідомий тип фільтра: " + d.type + " у файлі.");
            }
        }
        
        std::cout << "\n--- Етап 3: Вивід створених об'єктів (Поліморфізм) ---\n";
        for (const auto& f : arr) {
            std::cout << *f;
        }
        
        std::vector<FilterData> output_data = input_data;
        
        std::cout << "\n--- Етап 4: Перевантаження оператора та обробка даних ---\n";
        if (c.size() >= 2) {
            FilterData merged = c[0] + c[1];
            output_data.push_back(merged);
            std::cout << "Успішно об'єднано два фільтри (використовуючи оператор +):\n";
            std::cout << "  Об'єднані дані: " << merged.toString() << "\n";
        } else {
            std::cout << "Недостатньо записів (потрібно мінімум 2) для виконання операції об'єднання.\n";
        }
        
        std::cout << "\n--- Етап 5: Запис результатів у файл ---\n";
        writeDataFile(OUTPUT_FILENAME, output_data);
        std::cout << "Успішно записано " << output_data.size() << " записів у файл " << OUTPUT_FILENAME << ".\n";

    }
    catch (const FileException& e) {
        std::cerr << "ПОМИЛКА ФАЙЛУ: " << e.what() << "\n";
        return 1;
    }
    catch (const InvalidInput& e) {
        std::cerr << "ПОМИЛКА ВХІДНИХ ДАНИХ: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "ЗАГАЛЬНА ПОМИЛКА: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
