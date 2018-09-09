/*
 * Methods For Recording Images
 */
#ifndef IMAGE_TOOLS_HPP
#define IMAGE_TOOLS_HPP

#include "tools.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>

namespace img_tools {
	
	static const std::string WORKSPACE = "Workspace/";
	static const std::string WORKSPACE_IMGP = "Workspace/imgp/";
	static const std::string METHOD = "M0_";

	static const std::unordered_map<std::string, std::string> map_extension = {
		{"PNG", "png"}, {"JPG", "jpg"}, {"JPEG", "jpeg"},
	};

	static const std::unordered_map<std::string, std::string> map_default = {
		{"ORIGINAL"  , "output/original/"},
		{"GRAYSCALE" , "output/grayscale/gray-"},
		{"BINARY"    , "output/binary/bin-"},
		{"BINARY_INV", "output/binary/bininv-"}
	};	

	std::unordered_map<std::string, std::string> map_imgp;

	std::vector<std::string> info;
	std::string directory, filename, extension, name;
	std::string workspace(WORKSPACE), workspace_imgp(WORKSPACE_IMGP);
	std::string method_name(METHOD);
	std::string imgp_path, path_temp;

	void error(int line, const std::string& msg)
	{
		throw std::domain_error("[Line: " + std::to_string(line) + "]: " + msg);
	}	

	void view_map_load()
	{
		std::cout << "Map currently loaded:\n";
		try {
			tools::view_map(map_imgp);
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::view_map_load");
		}
	}

	void status_map()
	{
		view_map_load();
		std::cout << "\nIMGP: " << imgp_path
			<< "\nfilename: " << filename
			<< "\nname: " << name << '\n';
	}

	std::string get_path_map(const std::string& key)
	{
		return tools::find_key(key, map_imgp);
	}	

	void validate (const std::string& file_image)
	{
		if (!tools::check_extension(tools::upper(extension), map_extension))
			error(__LINE__, "img_tools::validate, invalid file_image in.\n");		
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
		filename = info[1];
		extension = info[2];
		name = info[3];		
	}

	void initialize_imgp_default(const std::string& file_image)
	{
		try {
			info_path(file_image);	
			validate(file_image);			
			map_imgp.clear();

			imgp_path = workspace_imgp + method_name + name + ".imgp";
			std::cout << "initialize .imgp: " << imgp_path << "\n";
			tools::save_new_file(imgp_path);

			for (auto it: map_default) {
				path_temp = std::string(it.first) + ":" + workspace + 
					std::string(it.second) + filename + '\n';
				map_imgp.insert(std::make_pair<std::string, std::string>
					(std::string(it.first),workspace +
					std::string(it.second) + filename));
				tools::write(path_temp, imgp_path);
			}
			std::cout << "img_tools::initialize_imgp_default ... ok" << '\n';
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::initialize_imgp_default");
		}		
	}

	void create_imgp(const std::string& file_image)
	{
		try {

			if (map_imgp.empty()) {
				std::cout << "map currently empty!\n";
				return;
			}		
				
			info_path(file_image);	
			validate(file_image);			

			imgp_path = workspace_imgp + method_name + name + ".imgp";
			std::cout << "create .imgp: " << imgp_path << "\n";
			tools::save_new_file(imgp_path);

			for (auto it: map_imgp) {
				path_temp = std::string(it.first) + ":" + workspace + 
					std::string(it.second) + filename + '\n';
				map_imgp.insert(std::make_pair<std::string, std::string>
					(std::string(it.first),workspace +
					std::string(it.second) + filename));
				tools::write(path_temp, imgp_path);
			}
			std::cout << "img_tools::create_imgp ... ok" << '\n';
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::create_imgp");
		}		
	}	

	void update_imgp(const std::string& file_imgp)
	{
		try {

			if (!tools::check_filename_extension(file_imgp, "imgp"))
				error(__LINE__, 
					"img_tools::update_imgp, invalid file_image in.\n");

			if (map_imgp.empty()) {
				std::cout << "map currently empty!\n";
				return;
			}

			std::string file_temp =  tools::get_filename(file_imgp);
			imgp_path = file_imgp;
			tools::save_new_file(imgp_path);

			for (auto it: map_imgp) {
				path_temp = std::string(it.first) + ":"
					+ std::string(it.second) + '\n';
				tools::write(path_temp, imgp_path);
			}
			std::cout << "img_tools::update ... ok" << '\n';
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::update_imgp");
		}
	}

	void recover_imgp(const std::string& file_imgp)
	{
		std::vector<std::string> lines, word;
		try {
			tools::load(file_imgp, lines);
			map_imgp.clear();
			std::string file_temp("");
			for (std::string line : lines) {
				tools::split(line, word, ':');
				map_imgp.insert(std::make_pair<std::string, std::string>(
					std::string(word[0]), std::string(word[1])));
				if (word[0] == "ORIGINAL") file_temp = word[1];
			}
			imgp_path = file_imgp;
			info_path(file_temp);
		}
		catch(const std::exception& e) {
			error(__LINE__, "img_tools::recover_imgp");
		}
	}
};

#endif // IMAGE_TOOLS_HPP