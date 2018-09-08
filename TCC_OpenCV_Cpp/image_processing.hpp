#ifndef IMAGE_PROCESSING_HPP
#define IMAGE_PROCESSING_HPP

#include "tools.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>

// #include <opencv2/imgcodecs.hpp>
// #include <opencv2/highgui.hpp>
// #include <opencv2/imgproc.hpp>

namespace image_processing {
	
	enum Format {ORIGINAL, GRAYSCALE, BINARY, BINARY_INV, MASK, FINAL, ALL};

	static const std::string IMGP = "Workspace/imgp/";

	std::unordered_map<std::string, std::string> map_imgp = {
		{"ORIGINAL"  , "Workspace/output/original/"},
		{"GRAYSCALE" , "Workspace/output/grayscale/gray-"},
		{"BINARY"    , "Workspace/output/binary/bin-"},
		{"BINARY_INV", "Workspace/output/binary/bininv-"},
		{"MASK"      , "Workspace/output/maks/mask-"},
		{"FINAL"     , "Workspace/output/final-"},
	};

	std::unordered_map<std::string, std::string> map_extension = {
		{"PNG", "png"}, {"JPG", "jpg"}, {"JPEG", "jpeg"},
	};

	std::unordered_map<std::string, std::string> map_load;
	std::vector<std::string> info;
	std::string directory, filename, extension, name;
	std::string imgp_path, path_temp;

	// Mat source[ALL];

	void view_map_load()
	{
		std::cout << "Map currently loaded:" << '\n';
		for (auto it: image_processing::map_load){
			std::cout << it.first << " " << it.second << '\n';
		}
	}

	void create_imgp(const std::string& file_image, 
		std::string method_name = "default-")
	{
		try {

			// retirar informações do path
			tools::split_path(file_image, info);
			directory = info[0];
			filename = info[1];
			extension = info[2];
			name = info[3];

			// validar o tipo de arquivo de imagem
			if (!tools::check_extension(tools::upper(extension), map_extension))
				throw std::domain_error("error:image_processing::create_imgp,"
					" invalid file_image in.\n");

			// checar se já existe um registro imgp

			// reunir os dados e inicializar no arquivo gestor 
			imgp_path = IMGP + method_name + name + ".imgp";
			tools::save_new_file(imgp_path);
			// tools::write("IGMP:" + imgp_path + '\n', imgp_path);

			// escrever os caminhos de cada tipo de imagem e atualizar map atual
			for (auto it: map_imgp) {
				path_temp = std::string(it.first) + ":" + std::string(it.second)
					+ filename + '\n';
				map_load.insert(std::make_pair<std::string, std::string>(
					std::string(it.first), std::string(it.second) + filename));
				tools::write(path_temp, imgp_path);
			}
		}
		catch(const std::exception& e) {
			std::cout << e.what() << '\n';
		}

		std::cout << "image_processing::create_imgp ... ok" << '\n';
	}

	void recover_imgp(const std::string& file_imgp)
	{
		// try {
			
		// }
		// catch(const std::exception& e) {
		// 	std::cout << e.what() << '\n';
		// }

	}

	void method_basic(const std::string file_imgp)
	{
		// checar se algum imgp está em uso

		// OpenCV

		// Escala de Cinza

		// Binarizar
	}
};

#endif // IMAGE_PROCESSING_HPP