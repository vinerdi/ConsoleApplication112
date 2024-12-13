#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class CountryCityManager {
private:
    unordered_map<string, vector<string>> data;

public:
    void loadData(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file" << endl;
            return;
        }
        string country, city;
        while (file >> country >> city) {
            data[country].push_back(city);
        }
        file.close();
    }

    void saveData(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file" << endl;
            return;
        }
        for (const auto& pair : data) {
            for (const auto& city : pair.second) {
                file << pair.first << " " << city << endl;
            }
        }
        file.close();
    }

    void findCities(const string& country) {
        auto it = data.find(country);
        if (it != data.end()) {
            for_each(it->second.begin(), it->second.end(), [](const string& city) {
                cout << city << endl;
            });
        } else {
            cout << "Country not found" << endl;
        }
    }

    void replaceCity(const string& country, const string& oldCity, const string& newCity) {
        auto it = data.find(country);
        if (it != data.end()) {
            auto cityIt = find(it->second.begin(), it->second.end(), oldCity);
            if (cityIt != it->second.end()) {
                *cityIt = newCity;
            } else {
                cout << "City not found" << endl;
            }
        } else {
            cout << "Country not found" << endl;
        }
    }

    void addCity(const string& country, const string& city) {
        data[country].push_back(city);
    }

    void addCountry(const string& country) {
        if (data.find(country) == data.end()) {
            data[country] = vector<string>();
        } else {
            cout << "Country already exists" << endl;
        }
    }

    void deleteCity(const string& country, const string& city) {
        auto it = data.find(country);
        if (it != data.end()) {
            it->second.erase(remove(it->second.begin(), it->second.end(), city), it->second.end());
        } else {
            cout << "Country not found" << endl;
        }
    }

    void deleteCountry(const string& country) {
        data.erase(country);
    }

    void countCities(const string& country) {
        auto it = data.find(country);
        if (it != data.end()) {
            cout << "Number of cities: " << it->second.size() << endl;
        } else {
            cout << "Country not found" << endl;
        }
    }

    void listCountries() {
        for_each(data.begin(), data.end(), [](const auto& pair) {
            cout << pair.first << endl;
        });
    }
};

int main() {
    CountryCityManager manager;
    manager.loadData("data.txt");

    // Example usage
    manager.listCountries();
    manager.findCities("USA");
    manager.addCity("USA", "NewCity");
    manager.replaceCity("USA", "OldCity", "NewCity");
    manager.deleteCity("USA", "NewCity");
    manager.countCities("USA");
    manager.saveData("data.txt");

    return 0;
}
