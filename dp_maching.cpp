#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream> 
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <boost/format.hpp>
#include <algorithm>

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
using std::min;

class dp_matching
{
    public:
        dp_matching() :
            file_total_number_(100),
            frame_number_(15),
            init_flag_(1),
            min_search_num_store_(0),
            vec_one_dimensional_{1,1,1,1,1}
        {
            file_number_.emplace_back();
            file_data_capture_.emplace_back();
            template_data_.emplace_back();
            unknown_data_.emplace_back();
            local_distance_.emplace_back();
            cumulative_distance_.emplace_back();
            //word_distance_.emplace_back();
            minimum_word_distance_.emplace_back();
        }

        void file_read(int file_number_tmp, int file_number_unk)
        {
            char *c = getenv("HOME");
            string HOME = c; 
            int f_te_num = 0,f_un_num = 0,a = 0;
            const std::string f_te_path = (boost::format("/Documents/campas_work/dp_matching/city_mcepdata/city%03d/city%03d_%03d.txt") % 11 % 11 % file_number_tmp).str();
            const std::string f_un_path = (boost::format("/Documents/campas_work/dp_matching/city_mcepdata/city%03d/city%03d_%03d.txt") % 12 % 12 % file_number_unk).str();
            ifstream f_te(HOME + f_te_path,std::ios::in);
            ifstream f_un(HOME + f_un_path,std::ios::in);

            string line,field;

            while (getline(f_te, line)) 
            {
                istringstream stream(line);

                while (getline(stream, field, ' ') )
                {
                    template_data_[vec_one_dimensional_.at(0) - 1].push_back(field );
                }

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
            {   
                int cnt = 0;
                for (auto it_unk = unknown_data_.begin(); it_unk != unknown_data_.end(); ++it_unk) 
                {   
                    int tuning_number_outside = 0;
                    double accumulation = 0;
                    for (auto it = (*it_temp).begin(); it != (*it_temp).end(); ++it) 
                    {
                        int tuning_number_inside = 0;
                        for (auto it_t = (*it_unk).begin(); it_t != (*it_unk).end(); ++it_t) 
                        {
                            if(tuning_number_outside == tuning_number_inside)
                            {
                                double it_d = 0,it_t_d = 0;
                                try 
                                {
                                    it_d   = stod(*it);
                                    it_t_d = stod(*it_t);
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
                    if(double_flag) local_distance_[vec_one_dimensional_.at(2) - 1].push_back(accumulation);
                }
                if(double_flag) local_distance_.resize(++vec_one_dimensional_.at(2));
            }
            local_distance_.resize(--vec_one_dimensional_.at(2));
#endif       
        }

        void boundary_condition_calculation()
        {
            for (auto it_t = local_distance_.begin(); it_t != local_distance_.end(); ++it_t) 
            {
                for (auto it = (*it_t).begin(); it != (*it_t).end(); ++it) 
                {
                    cumulative_distance_[vec_one_dimensional_.at(3) - 1].push_back(*it);
                } 
                cumulative_distance_.resize(++vec_one_dimensional_.at(3));
            }
            cumulative_distance_.resize(--vec_one_dimensional_.at(3));

            for(int i(1);i < stoi(template_data_[2][0]);i++)
            {
                cumulative_distance_.at(i).at(0) = cumulative_distance_.at(i - 1).at(0) + local_distance_.at(i).at(0); 
            }

            for(int i(1);i < stoi(unknown_data_[2][0]);i++)
            {
                cumulative_distance_.at(0).at(i) = cumulative_distance_.at(0).at(i - 1) + local_distance_.at(0).at(i);
            }
            
#if 1
            for (int i = 1; i < stoi(template_data_[2][0]); ++i) 
            {
                for (int j = 1; j < stoi(unknown_data_[2][0]); ++j) 
                {
                    double vertical = cumulative_distance_[i][j - 1] + local_distance_[i][j];
					double diagonal = cumulative_distance_[i - 1][j - 1] + (2 * local_distance_[i][j]);
					double side = cumulative_distance_[i - 1][j] + local_distance_[i][j];

                    //cout << vertical << " " << diagonal << " " << side << " ";
                    //cout << vertical << " " << cumulative_distance_[i][j - 1] << " " << local_distance_[i][j] << endl;

                    double min_num = min ({vertical, diagonal , side});

					if (vertical == min_num)
                    {
						cumulative_distance_.at(i).at(j) = vertical;
					}

					if (diagonal == min_num)
                    {
						cumulative_distance_.at(i).at(j) = diagonal;
					}

                    if (side == min_num)
                    {
						cumulative_distance_.at(i).at(j) = side;
					}
                    //cout << cumulative_distance_.at(108).at(108) << endl;
            
                }
            }

            word_distance_.push_back(cumulative_distance_[stoi(template_data_[2][0]) - 1][stoi(unknown_data_[2][0]) - 1] / (stoi(template_data_[2][0]) + stoi(unknown_data_[2][0]) ) );
#endif        
        }

        void min_search()
        {
            int min_file_search = 1,min_file_result = 0;
            double min_search_num = 0;
            for (auto it_t =  word_distance_.begin(); it_t !=  word_distance_.end(); ++it_t) 
            {
                min_search_num =  *it_t;
                if (init_flag_) min_search_num_store_ = min_search_num;
                double min_num = min ({min_search_num_store_,min_search_num});
                min_search_num_store_ = min_num;
                if (min_search_num_store_ == min_search_num) min_file_result = min_file_search;
                ++min_file_search;
                init_flag_ = 0;
            }
            cout << min_file_result << endl;
        }

        void vector_memory_clear()
        {
            file_number_.clear();
            file_data_capture_.clear();
            template_data_.clear();
            unknown_data_.clear();
            local_distance_.clear();
            cumulative_distance_.clear();

            file_number_.emplace_back();
            file_data_capture_.emplace_back();
            template_data_.emplace_back();
            unknown_data_.emplace_back();
            local_distance_.emplace_back();
            cumulative_distance_.emplace_back();
            vec_one_dimensional_ = {1,1,1,1,1};

            min_search_num_store_ = 0;
            init_flag_ = 1;
        }

        void run()
        {
            //int cnta = 0;
            
            //for(int i(1); i<= file_total_number_;i++)
            //{
            //    int cntb = 0;
                for(int j(1);j <= file_total_number_;j++)
                {
                    file_read(18,j);
                    local_distance_calculation();
                    boundary_condition_calculation();
                    vector_memory_clear();
                    min_search();
                    //++cntb;
                }
            //    ++cnta;
            //    cout << cntb<< " " << cnta << endl;
            //}
#if 0
            for (auto it_t = word_distance_.begin(); it_t != word_distance_.end(); ++it_t) 
            {
                for (auto it = (*it_t).begin(); it != (*it_t).end(); ++it) 
                {
                    cout << *it;
                    cout << " ";
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
#if 1
            for (auto it_t =  word_distance_.begin(); it_t !=  word_distance_.end(); ++it_t) 
            {
                cout << *it_t;
                cout << endl;
            }
#endif     
        }

    private:
        int file_total_number_;
        int frame_number_;
        int init_flag_;
        double min_search_num_store_;
        vector<int> vec_one_dimensional_;
        vector<int> file_number_;
        vector<double> file_data_capture_;
        vector<vector<string>> template_data_;
        vector<vector<string>> unknown_data_;
        vector<vector<double>> local_distance_;
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
