// 编译器.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "cstring"
#include "string"
#include "iostream"
#include "fstream"
#include "sstream"

using namespace std;
string def(string before, string after, string line);
bool same(string before, string line, int i);
string readef(string out,  string line,int count);

int main()
{
//打开cpp文件
	ifstream infile;
	ofstream outfile;
	//读取旧文件
	char filename[99];
	cout << "Enter the name of a file:";
	cin >> filename;
	infile.open(filename);
	//写入新文件
	char newfile[] = "new.cpp";
	outfile.open(newfile);
	if (!infile.good())
	{
		cout << "Could not open file " << filename << endl;
		exit(EXIT_FAILURE);
	}

	string line;
	string before, after;
	// 读取每一行
	while (getline(infile,line))
	{
		before=readef(before, line,2); 
		after=readef(after, line, 3);
		line = def(before, after, line);
		cout << line<<endl;
		outfile << line<<endl;
		line.clear();
	}
	infile.close();
	outfile.close();
	//删除旧文件，将新文件改名
	remove(filename);
	int c =rename(newfile, filename);
    return 0;
}


//替换
string def(string before,string after,string line)
{
	for (unsigned int i = 0; i < line.size(); i++)
	{
		//#define行与注释行与字符串内不替换
		if (line[i] == '/' || line[i] == '#'||line[i]=='\"')
			break;
		if (line[i] == before[0]&&same(before, line, i))
		{
			line.replace(i,before.size(),after);
			break;
		}

	}
	return line;

}

//判定字符串中的一段是否与宏定义相同
bool same(string before, string line, int i) 
{
	bool isame =false;
	string in=before;
	for (unsigned int index = 0;( index < before.size())&&((i+index)<line.size()); index++)
	{
		in[index] = line[i + index];
	}
	if (before == in)
		isame = true;
	return isame;
}

//读取宏定义
string readef(string out,string line,int count)
{
	for (unsigned int index = 0; index < line.size(); index++)
	{
		if (line[index] == '#'&&same("#define", line, index))
		{
			//define行用空格分隔 直到需要的第count个字串  
			istringstream istr(line);
			int number = 1;
			while (istr >> out)
			{
				if (number++ == count)
					break;
			}
			break;
		}
	}
	return out;
}

