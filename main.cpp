#include <iostream>
#include <string>
#include<map>
#include<vector>
using namespace std;

#include <cstdlib>
#include<fstream>
#define CURL_STATICLIB
#include<curl/curl.h>
#include<nlohmann/json.hpp>
using json = nlohmann::json;

size_t my_write(void *ptr, size_t size, size_t count, void *stream) {
    ((string*)stream)->append((char*)ptr, 0, size*count);
    return size*count;
}

json get_exchange_rates() {
    string result;
	CURL* curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.cbr-xml-daily.ru/daily_json.js");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (CURLE_OK != res) {
			cerr << "CURL error: " << res << '\n';
		}
	}
	curl_global_cleanup();
	json j_complete = json::parse(result);
    return j_complete;
}



vector<pair<string, double>> json_to_rates(json json_file) {
    vector<pair<string, double>> res;
    for (const auto &item : json_file["Valute"]) {
        string code =  item["CharCode"].get<string>();
        double rate = item["Value"].get<double>() / item["Nominal"].get<int>();
        res.push_back(make_pair(code, rate));
    }
    return res;
}


class Database {
    private:
        map<string, double> rates_sum; 
        map<string, double> cache; 
        int iterations;
    public:
        Database() { iterations = 0;}

        void load_rates() {
            ++iterations;

            json json_file = get_exchange_rates();
            auto res = json_to_rates(json_file);

            for (auto pr : res) {
                string code = pr.first;
                double rate = pr.second;

                if (rates_sum.count(code) == 0)
                    rates_sum[code] = 0;
                
                cache[code] = rate;
                rates_sum[code] += rate;
            }
        }

        void print_rates(ofstream &out) {
            out << "Exchange Rates #" << iterations << "\n";
            for (auto pr : cache) {
                string code = pr.first;
                double rate = pr.second;

                out << code << ": " << rate << "\n"; 
            }
        }

        void print_average(ofstream &out) {
            for (auto pr : rates_sum) {
                string code = pr.first;
                double rate = pr.second;

                out << code << ": " << rate / iterations << "\n"; 
            }
        }

};


const string DIR = "D:\\Desktop\\pr\\assets\\";
Database * global_db;


void at_exit() {
    ofstream out (DIR + "avg.txt");
    out << "Average rates\n";
    global_db->print_average(out);
    out.close();
}


// мб надо изменить
int main() {
    Database db = Database();
    global_db = &db;
    atexit(at_exit);

    int i = 0;
    while (++i) {
        string path = DIR + to_string(i) + ".txt";
        freopen(path.c_str(), "w", stdout);
        ofstream out (path);
        db.load_rates();
        db.print_rates(out);
        out.close();
        Sleep(3000);
    }
}