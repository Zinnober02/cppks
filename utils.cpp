#include "utils.h"

std::filesystem::path utils::getDirPath(int index1, int index2, int id) {
	std::string item1 = selection[index1];
	path dir_path;
	path current_dir = current_path() / "files";
	if (index2 == -1)
		dir_path = current_dir / item1;
	else {
		std::string item2 = selection[index2];
		dir_path = id ? current_dir / item1 / item2 / std::to_string(id) : current_dir / item1 / item2;
	}
	if (!exists(dir_path)) {
		create_directories(dir_path);
		std::cout << "成功创建目录" << std::endl;
	}
	//std::cout << dir_path << std::endl;
	return dir_path;
}

void rgbSet(int wr, int wg, int wb, int br, int bg, int bb) {						//设置RGB
	printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm", wr, wg, wb, br, bg, bb);
	//\033[38   表示前景，\033[48   表示背景，三个%d表示混合的数
}