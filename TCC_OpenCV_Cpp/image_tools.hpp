/*
 * Métodos para facilitar a gerência das imagens
 */
#ifndef IMAGE_TOOLS_HPP
#define IMAGE_TOOLS_HPP

#include "tools.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

namespace img_tools {

	#define THRESH 180
	#define MAX_VALUE 255
	
	// Padrão
	static const std::string WORKSPACE = tools::current_dir() + "/Workspace";
	static const std::string WORKSPACE_IMGP = "/imgp";
	static const std::string WORKSPACE_OUT = "/output";
	static const std::string METHOD = "M0_";

	// utilizar '#' como no shell para desabilitar item ao carregar '.imgp' 
	static const std::unordered_map<std::string, std::string> map_default = {
		{"ORIGINAL"  , "."},
		{"COPY"      , "/original"},
		{"GRAYSCALE" , "/grayscale"},
		{"BINARY"    , "/binary"},
		{"BINARY_INV", "/binary_inv"}
	};	

	static const std::unordered_map<std::string, std::string> map_extension = {
		{"PNG", "png"}, {"JPG", "jpg"}, {"JPEG", "jpeg"},
	};

	// Variáveis globais
	std::vector<std::string> info;
	std::string directory, filename, extension, name;
	std::string workspace(WORKSPACE);
	std::string method_name(METHOD);
	std::string imgp_path, path_temp;
	std::unordered_map<std::string, std::string> map_user = map_default;

	// Métodos iniciais
	void error(int line, const std::string& msg)
	{
		throw std::domain_error("[Line: " + std::to_string(line) + "]: " + msg);
	}

	void validate (const std::string& file_image)
	{
		if (!tools::check_extension(tools::upper(extension), map_extension))
			error(__LINE__, "img_tools::validate, invalid file_image.\n");		
	}

	void info_path(const std::string& file_image)
	{
		try {
			tools::split_path(file_image, info);
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::info_path\n");
		}
		
		directory = info[0];
		filename  = info[1];
		extension = info[2];
		name      = info[3];
	}	

	bool exist_workspace(const std::string& new_workspace)
	{
		if (!tools::exist_path(new_workspace)) {
			// std::cout << new_workspace << " don't exist!\n";
			return false;
		}
		return true;
	}

	void create_workspace(const std::string& new_workspace, 
		const std::unordered_map<std::string, std::string>& map_work)
	{
		try {
			if (new_workspace.empty()) {
				std::cout << "string new_workspace empty!\n";
				return;
			}

			if (map_work.empty()) {
				std::cout << "map empty!\n";
			}

			if (exist_workspace(new_workspace)) {
				std::cout << new_workspace << " exist. don't created!\n";
				return;
			}

			tools::create_directory(new_workspace);
			tools::create_directory(new_workspace + WORKSPACE_IMGP);
			tools::create_directory(new_workspace + WORKSPACE_OUT);

			for (auto it : map_work) {
				if (it.first == "ORIGINAL") continue;
				tools::create_directory(new_workspace + WORKSPACE_OUT
					+ std::string(it.second));
			}

			std::cout << new_workspace << " ... ok\n";
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::create_workspace");
		}
	}

	void create_workspace()
	{
		create_workspace(workspace, map_default);
	}

	void create_workspace(const std::string& new_workspace)
	{
		create_workspace(new_workspace, map_default);
	}

	void save_imgp(const std::string& file_image,
		const std::string& new_workspace,
		const std::unordered_map<std::string, std::string>&	map_work)
	{
		try {
			if (new_workspace.empty()) {
				std::cout << "string new_workspace empty!\n";
				return;
			}

			if (map_work.empty()) {
				std::cout << "map empty!\n";
				return;
			}

			if (!exist_workspace(new_workspace))
				create_workspace(new_workspace, map_work);
			// else {
			// 	std::cout << "Check directories and workspace"
			// 		<< " before changing the map.\n";
			// }		

			info_path(file_image);
			validate(file_image);			
 
			imgp_path = new_workspace + WORKSPACE_IMGP + "/"
						+ method_name + name + ".imgp";
			std::cout << "save .imgp: " << imgp_path;
			tools::save_new_file(imgp_path);
			tools::write("#IMGP:" + imgp_path + "\n", imgp_path);

			for (auto it: map_work) {
				if (it.first == "ORIGINAL") {
					path_temp = "ORIGINAL:" + file_image + "\n";
				}
				else {
					path_temp = std::string(it.first) + ":"
						+ new_workspace + WORKSPACE_OUT
						+ std::string(it.second) + "/"
						+ method_name + filename + "\n";
				}
				tools::write(path_temp, imgp_path);
			}
			tools::write("#WORKSPACE:" + new_workspace + "\n", imgp_path);

			std::cout << " ... ok" << '\n';
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::create_imgp");
		}		
	}

	void save_imgp(const std::string& file_image,
				   const std::string& new_workspace)
	{
		save_imgp(file_image, new_workspace, map_default);
	}

	void save_imgp(const std::string& file_image)
	{
		save_imgp(file_image, workspace, map_default);
	}

	std::vector<std::vector<std::string> > load_imgp(const std::string& file_imgp)
	{
		if (!tools::check_filename_extension(file_imgp, "imgp"))
			std::cout << "it is not .imgp" << '\n';

		std::vector<std::string> lines, word;
		std::vector<std::vector<std::string> > result {{"EMPTY"}};
		try {
			tools::load(file_imgp, lines);
			result.clear();
			for (std::string line : lines) {
				tools::split(line, word, ':');
				
				if (word.size() != 2) {
					std::cout << "ignored line ...\n";
					continue;
				}

				// ignorar textos extras
				if (word[0][0] == '#') {
					std::cout << "ignored line ...\n";
					continue;				
				}

				result.push_back(word);
			}
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::load_imgp");
		}
		return result;
	}

	std::vector<std::string> list_imgp(const std::string& new_workspace)
	{
		std::vector<std::string> result {"EMPTY"};
		std::cout << "List: " << new_workspace << WORKSPACE_IMGP << " ... ";
		if (!tools::exist_path(new_workspace + WORKSPACE_IMGP)) {
			std::cout << " failure\n";
			return result;
		} else {
			std::cout << "ok\n";
			tools::files(result, new_workspace + WORKSPACE_IMGP);
		}
		return result;	
	}

	std::string search_path(const std::string& format,
					   		std::vector<std::vector<std::string> >& v_map)
	{
		for (auto path: v_map) {
			if (path.front() == format) {
				std::cout << "=> " << path.front() << ": "
					<< path.back() << '\n';
				return path.back();
			}
		}
		return "EMPTY";
	}

	void create_imgp_base(const std::string& new_workspace,
						  const std::vector<std::string>& images,
						  const std::string& new_ext)
	{
		for (auto image: images) {
			if (!tools::check_filename_extension(image, new_ext)) continue;
			std::cout << "image: " << image << '\n';
			save_imgp(image, new_workspace, map_user);
		}
	}

	/*****************************   OPENCV   *********************************/
	void load_image(cv::Mat& src,
					const std::string& format,
					std::vector<std::vector<std::string> >& v_map,
					const int image_type)
	{
		std::string path = search_path(format, v_map);
		src = cv::imread(path, image_type);
		if(src.empty()) {
			std::cout << "could not open or find the image " << format << "!\n";
		}	
	}

	void method_basic(std::vector<std::vector<std::string> >& v_map)
	{
		// OPENCV - ORIGINAL
		cv::Mat src_ori;
		load_image(src_ori, "ORIGINAL", v_map, cv::IMREAD_COLOR);

		// OPENCV - COPY
		cv::imwrite(search_path("COPY", v_map), src_ori);	

		// OPENCV - GRAYSCALE
		cv::Mat src_gray(src_ori.size(), CV_8U);
		cv::cvtColor(src_ori, src_gray, CV_BGR2GRAY);
		cv::imwrite(search_path("GRAYSCALE", v_map), src_gray);

		// OPENCV - BINARY
		cv::Mat src_bin(src_gray.size(), src_gray.type());
		cv::threshold(src_gray, src_bin, THRESH, MAX_VALUE, cv::THRESH_BINARY);
		cv::imwrite(search_path("BINARY", v_map), src_bin);

		// OPENCV - BINARY_INV
		cv::Mat src_bin_inv(src_gray.size(), src_gray.type());
		cv::threshold(src_gray, src_bin_inv, THRESH, MAX_VALUE, cv::THRESH_BINARY_INV);
		cv::imwrite(search_path("BINARY_INV", v_map), src_bin_inv);
	}

	void method_main(const std::vector<std::string>& images)
	{
		for (auto imgp: images) {
			
			if (!tools::exist_path(imgp)) {
				std::cout << "IMGP failure!" << '\n';
				continue;
			}

			std::cout << "\nreload .imgp : " << imgp << '\n';
			std::vector<std::vector<std::string> > v_map = load_imgp(imgp);

			method_basic(v_map);
		}
	}

	// Processamento de imagens em lote
	int bath(const std::string& new_workspace,
			 const std::string& new_method_name,
			 const std::string& new_folder,
			 const std::string& new_ext,
			 const std::unordered_map<std::string, std::string>& new_map)
	{
		// passo 1 - checar se diretório de imagens existe
		std::cout << "check " << new_folder << " ... ";
		if (!tools::exist_path(new_folder)) {
			std::cout << "failure\n";
			return (EXIT_FAILURE);
		} else {
			std::cout << "ok\n";
		}

		// passo 2 - criar workspace com MAP customizado
		if (!new_method_name.empty()) method_name = new_method_name;
		if (!new_map.empty()) map_user = new_map;
		create_workspace(new_workspace, map_user);

		// passo 3 - listar arquivos de imagens alvo
		std::vector<std::string> images;
		tools::files(images, new_folder);

		// passo 4 - gerar os arquivos de gerência
		create_imgp_base(new_workspace, images, new_ext);

		// passo 5 - processar para cada .imgp as imagens
		tools::files(images, new_workspace + "/imgp");
		method_main(images);

		return (EXIT_SUCCESS);	
	}

	int bath(const std::string& new_workspace,
			 const std::string& new_method_name,
			 const std::string& new_folder,
			 const std::string& new_ext)
	{
		return bath(new_workspace, new_method_name, new_folder,
			new_ext, map_default);
	}

} // namespace img_tools

#endif // IMAGE_TOOLS_HPP