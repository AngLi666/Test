#include "ultis.hpp"


void stl_sleep(int millisecond)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));	
}


int load_bin(void* buf, int buf_size, char* path)
{
	FILE* fp;
	fp = fopen(path, "rb");
	if (fp == NULL) {
		printf("\n#!!!nna_load_buf open file fail :%s ", path);
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
	if (fp == NULL) {
		printf("\n#!!!nna_save_buf open file fail :%s ", path);
		return 0;
	}

	int sz = fwrite(buf, 1, buf_size, fp);
	// printf("\n# %p[%8d]--> %s ", buf, sz, path);
	if (sz < buf_size)
		printf("\n!!! nna_save_buf write file: %s error :%d [%d]", path, sz, buf_size);
    fclose(fp);
	return sz;
}

