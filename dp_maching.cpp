#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream> 
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <boost/format.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::istringstream;
using std::stod;
using std::stoi;
using std::pow;

class dp_matching
{
    public:
        dp_matching() :
            file_total_number_(100),
            frame_number_(15),
            vec_one_dimensional_{1,1,1}
        {
            file_number_.emplace_back();
            file_data_capture_.emplace_back();
            template_data_.emplace_back();
            unknown_data_.emplace_back();
            local_distance_.emplace_back();
            cumulative_distance_.emplace_back();
            word_distance_.emplace_back();
            minimum_word_distance_.emplace_back();
        }

        void file_read()
        {
            char *c = getenv("HOME");
            string HOME = c; 
            int f_te_num = 0,f_un_num = 0,a = 0;
            cin >> f_te_num >> f_un_num;
            const std::string f_te_path = (boost::format("/Documents/campas_work/dp_matching/city_mcepdata/city%03d/city%03d_%03d.txt") % f_te_num % f_te_num % f_te_num).str();
            const std::string f_un_path = (boost::format("/Documents/campas_work/dp_matching/city_mcepdata/city%03d/city%03d_%03d.txt") % f_un_num % f_un_num % f_te_num).str();
            ifstream f_te(HOME + f_te_path,std::ios::in);
            ifstream f_un(HOME + f_un_path,std::ios::in);

            string line,field;

            while (getline(f_te, line)) 
            {
                istringstream stream(line);
#if 0 
                cout << line << endl;
#endif
                while (getline(stream, field, ' ') )
                {
#if 0 
                    cout << field;
#endif
                    template_data_[vec_one_dimensional_.at(0) - 1].push_back(field );
                }
#if 0                
                cout << endl;
#endif
                template_data_.resize(++vec_one_dimensional_.at(0) );
            }
            template_data_.resize(--vec_one_dimensional_.at(0) );
#if 1
            while (getline(f_un, line)) 
            {
                istringstream stream(line);
                while (getline(stream, field) )
                {
                    unknown_data_[vec_one_dimensional_.at(1) - 1].push_back(field );
                }

                unknown_data_.resize(++vec_one_dimensional_.at(1) );
            }
            unknown_data_.resize(--vec_one_dimensional_.at(1) );
#endif
        }

        void local_distance_calculation()
        {
#if 1
            int double_flag = 0;
            
            for (auto it_temp = template_data_.begin(); it_temp != template_data_.end(); ++it_temp) 
            {   int cnt = 0;
                for (auto it_unk = unknown_data_.begin(); it_unk != unknown_data_.end(); ++it_unk) 
                {   
                    int tuning_number_outside = 0;
                    int accumulation = 0;
                    for (auto it = (*it_temp).begin(); it != (*it_temp).end(); ++it) 
                    {
                        int tuning_number_inside = 0;
                        for (auto it_t = (*it_unk).begin(); it_t != (*it_unk).end(); ++it_t) 
                        {
                            if(tuning_number_outside == tuning_number_inside)
                            {
                                int it_d = 0,it_t_d = 0;
                                try 
                                {
                                    it_d   = stoi(*it);
                                    it_t_d = stoi(*it_t);
                                    accumulation += pow(it_d - it_t_d,2);
                                    if(it_d < 10 && it_t_d < 10) double_flag = 1;
                                    else double_flag = 0;
                                    ++tuning_number_inside;
                                } 
                                catch (const std::invalid_argument& e) 
                                {
                                    double_flag = 0;
                                }
                            }
                            break;
                        }
                        ++tuning_number_outside;
                    } 
                    if(double_flag)
                    {
                        local_distance_[vec_one_dimensional_.at(2) - 1].push_back(accumulation);
                        ++cnt;
                        cout << cnt << endl;
                    }
                }
                if(double_flag) local_distance_.resize(++vec_one_dimensional_.at(2));
            }
            local_distance_.resize(--vec_one_dimensional_.at(2));
#endif       
        }

        void run()
        {
            file_read();
            local_distance_calculation();
#if 0
            for (auto it_t = local_distance_.begin(); it_t != local_distance_.end(); ++it_t) 
            {
                for (auto it = (*it_t).begin(); it != (*it_t).end(); ++it) 
                {
                    cout << *it;
                } 

                cout << endl;
            }
#endif     
#if 0
            int ct = 0;
            for (auto it_t = local_distance_.begin(); it_t != local_distance_.end(); ++it_t) 
            {
                
                for (auto it = (*it_t).begin(); it != (*it_t).end(); ++it) 
                {

                } 
                ++ct;
                cout << ct << endl;
            }
#endif     
        }

    private:
        int file_total_number_;
        int frame_number_;
        vector<int> vec_one_dimensional_;
        vector<int> file_number_;
        vector<double> file_data_capture_;
        vector<vector<string>> template_data_;
        vector<vector<string>> unknown_data_;
        vector<vector<int>> local_distance_;
        vector<vector<double>> cumulative_distance_;
        vector<double> word_distance_;
        vector<double> minimum_word_distance_;
};

int main()
{
    dp_matching dp;
    dp.run();

    return 0;
}
