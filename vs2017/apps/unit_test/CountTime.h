// CountTime.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <map>
#include <fstream>
#include <time.h>
#include <string>
#include <stdio.h>
namespace TimeProfile
{
	class TimeCount
	{
	public:
		TimeCount(std::string name)
		{
			m_name = name;
			m_t_start = clock();
		}

		long stop(std::ofstream& f)
		{
			m_t_finished = clock();
			f << m_name.c_str() << "过程耗时: " << (m_t_finished - m_t_start) << "ms";
			f << std::endl;
			return (m_t_finished - m_t_start);
		}
	private:
		std::string m_name;
		clock_t m_t_start;
		clock_t m_t_finished;
	};

	class TimeCountInstance
	{
	public:
		static TimeCountInstance* Instance()
		{
			return &s_instance;
		}

		void createTimeCount(std::string name)
		{
			TimeCount* t = new TimeCount(name);
			m_map.insert(make_pair(name,t));

		}
		void recordTimeCount(std::string name)
		{
			std::map<std::string,TimeCount*>::iterator it = m_map.find(name);
			if (it != m_map.end())
			{
				total_time += it->second->stop(ofs);
				m_map.erase(it);
			}
		}

		void saveProfile()
		{
			ofs << "过程总耗时: " << total_time << "ms";
			ofs << std::endl;
			ofs.close();
		}
	private:
		TimeCountInstance()
		{
			char* file_name = new char[128];
			int count = 1;
			sprintf_s(file_name,128,"profile_time.txt");
			while (isFileExists(file_name))
			{
				sprintf_s(file_name,128,"profile_time%d%s",count,".txt");
				count ++;
			}
			ofs.open(file_name,std::ios::out);
		}
		bool isFileExists(const char* filename)
		{
			std::ifstream f(filename);
			return f.good();
		}
		static TimeCountInstance s_instance;

		std::map<std::string,TimeCount*> m_map;

		std::ofstream ofs;
		long total_time;

	};
}