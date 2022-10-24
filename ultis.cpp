#include "ultis.hpp"
#include <fstream>
#include <iostream>
using namespace std;



int load_bin(void* buf, int buf_size, char* path)
{
	ifstream file(path, ios::out | ios::binary);
	if (!file) {
		cout << "\nopen file error" << endl;
		return 0;
	}
	
	if (! file.read((char*)buf, buf_size))
	{
		cout << "\nread file data error" << endl;
	}
	file.close();

	return buf_size;

}

int save_bin(void* buf, int buf_size, char* path)
{
	ofstream file(path, ios::in | ios::binary);

	if (! file.write((char*)buf, buf_size))
	{
		cout << "\nwrite data error" << endl;
	}

	file.close();

	return buf_size;
}


/*

int load_bin(void* buf, int buf_size, char* path)
{
	FILE* fp;
	fp = fopen(path, "rb");
	if (fp == NULL) {
		printf("\n#!!!nna_load_buf open file fail :%s \n", path);
		return 0;
	}

	int sz = fread(buf, 1, buf_size, fp);
	// printf("\n# %p[%8d]<-- %s ", buf, sz, path);
    fclose(fp);
	return sz;
}


int save_bin(void* buf, int buf_size, char* path)
{
	FILE* fp;
	fp = fopen(path, "wb");
	//fopen_s(&fp, path, "rb");
	if (fp == NULL) {
		printf("\n#!!!nna_save_buf open file fail :%s \n", path);
		return 0;
	}

	int sz = fwrite(buf, 1, buf_size, fp);
	// printf("\n# %p[%8d]--> %s ", buf, sz, path);
	if (sz < buf_size)
		printf("\n!!! nna_save_buf write file: %s error :%d [%d]\n", path, sz, buf_size);
    fclose(fp);
	return sz;
}
*/



void stl_sleep(int millisecond)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));
}

