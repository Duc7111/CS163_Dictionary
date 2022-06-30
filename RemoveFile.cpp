#include "RemoveFile.h"


bool DeleteFile(string &dir) //dir : address of an binary file
{
	int ret = remove(dir.c_str());
	if (ret == 0) return false;
	else return true;
	return ret;
}
