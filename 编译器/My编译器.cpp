// ������.cpp : �������̨Ӧ�ó������ڵ㡣
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
//��cpp�ļ�
	ifstream infile;
	ofstream outfile;
	//��ȡ���ļ�
	char filename[99];
	cout << "Enter the name of a file:";
	cin >> filename;
	infile.open(filename);
	//д�����ļ�
	char newfile[] = "new.cpp";
	outfile.open(newfile);
	if (!infile.good())
	{
		cout << "Could not open file " << filename << endl;
		exit(EXIT_FAILURE);
	}

	string line;
	string before, after;
	// ��ȡÿһ��
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
	//ɾ�����ļ��������ļ�����
	remove(filename);
	int c =rename(newfile, filename);
    return 0;
}


//�滻
string def(string before,string after,string line)
{
	for (unsigned int i = 0; i < line.size(); i++)
	{
		//#define����ע�������ַ����ڲ��滻
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

//�ж��ַ����е�һ���Ƿ���궨����ͬ
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

//��ȡ�궨��
string readef(string out,string line,int count)
{
	for (unsigned int index = 0; index < line.size(); index++)
	{
		if (line[index] == '#'&&same("#define", line, index))
		{
			//define���ÿո�ָ� ֱ����Ҫ�ĵ�count���ִ�  
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

