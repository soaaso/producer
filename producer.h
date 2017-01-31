#include<iostream>
#include<fstream>
#include<string>

class Param
{
	private:
		float buffSize;
		std::string compressionType;
		std::string targetReadFile;
		std::string targetWriteFile;
	public:
		Param();
		~Param();
		void setBuff(float size);
		void setCompression(std::string type);
		void setTargetRead(std::string file);
		void setTargetWrite(std::string file);
		float getBuff();
		std::string getCompression();
		std::string getTargetRead();
		std::string getTargetWrite();
};

bool checkFile(std::string);
void usage();
Param readConfig(char* str);
void tail(std::string readFile, float buffSize);
