#include "producer.h"

Param::Param()
{
	buffSize = 128;
	compressionType = "gzip";
	targetReadFile = "/tmp/producer_read.log";
	targetWriteFile = "/tmp/producer_write.log";
}

Param::~Param(){}

void Param::setBuff(float size)
{
	if(size > 0){
		buffSize = size;
	} else {
		buffSize = 1024;
	}
}

void Param::setCompression(std::string type)
{
	std::string types[3] =
	{
		"gzip",
		"snappy",
		"lz4"
	};
	for(int i = 0; i<sizeof(types); i++) {
		if(type == types[i]) {
			compressionType = type;
		}
	}
	if(compressionType == ""){
		compressionType = "gzip";
	}
}

void Param::setTargetRead(std::string file)
{
	if(sizeof(file) == 0) {
		targetReadFile = "/tmp/hoge_read.log";
	}
	targetReadFile = file;
}

void Param::setTargetWrite(std::string file)
{
	if(sizeof(file) == 0) {
		targetWriteFile = "/tmp/hoge_write.log";
	}
	targetWriteFile = file;
}


float Param::getBuff()
{
	return buffSize;
}

std::string Param::getCompression()
{
	return compressionType;
}

std::string Param::getTargetRead()
{
	return targetReadFile;
}

std::string Param::getTargetWrite()
{
	return targetWriteFile;
}

Param readConfig(std::string confPath)
{
	Param params;
	std::ifstream ifs(confPath);
	if(ifs.fail()) {
		std::cout << "failed read config : " << confPath << std::endl;
		exit(1);
	}
	std::string str;
	//int n = 0;
	std::string key = "";
	while (std::getline(ifs, str)) {
		if(key == "") {  // 1回目はkeyに登録, 2回目は値として入れる
			key = str;
		} else {
			if(key == "BUFFSIZE"){
				// test metrics
				params.setBuff(1024);
			} else if (key == "COMPRESSION_TYPE") {
				params.setCompression(str);
			} else if (key == "TARGET_READ_FILE") {
				params.setTargetRead(str);
			} else if (key == "TARGET_WRITE_FILE") {
				params.setTargetWrite(str);
			} else {
				std::cout << "failed key" << std::endl;
			}
			key = "";
		}
	}
	return params;
}

// TODO defined file check
bool checkFile(std::string file_name)
{
	return true;
}

void tail(std::string readFile, float buffSize)
{
	std::ifstream ifs(readFile);
	std::string line;
	while(ifs && getline(ifs,line)) { // 最初のifsは開けたかどうかを判定するため
		// 長すぎるログは除外
		if(line.length() > buffSize) {
			continue;
		}
		std::cout << line << std::endl;
	}
}
/*
   for watch

   writeLog
 */

void usage()
{
	std::cout << "Usage\n./producer.cpp <conf file path>\n";
	exit(1);
}

int main(int argc, char* argv[])
{
	std::string str;
	bool debug = false;
	if(argc < 2) {
		std::cout << "failed arg. no such file name\n";
		usage();
	}
	// TODO debug option
	//if(argc == 3 || argv[2] == "debug") {
	//	debug = true;
	//}
	//debug = true;
	str = argv[1];
	Param params = readConfig(str);
	if(debug) {
		std::cout << "buff size  " << params.getBuff() << std::endl;
		std::cout << "compression type " << params.getCompression() << std::endl;
		std::cout << "target read file " << params.getTargetRead() << std::endl;
		std::cout << "target write file " << params.getTargetWrite() << std::endl;
	}
	tail(params.getTargetRead(), params.getBuff());
	return 0;
}
