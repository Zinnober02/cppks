#include "utils.h"

std::filesystem::path utils::getDirPath(int index1, int index2, int fId, int id) {
	std::string item1 = selection[index1];
	std::string item2 = selection[index2];
	path current_dir = current_path() / "files";
	path dir_path =
		id ? current_dir / item1 / item2 / std::to_string(id) : current_dir / item1 / item2;
	if (!exists(dir_path)) {
		create_directories(dir_path);
		std::cout << "成功创建目录" << std::endl;
	}
	return dir_path;
}