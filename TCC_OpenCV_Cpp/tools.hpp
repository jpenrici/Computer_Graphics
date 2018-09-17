/*
 * Métodos Comuns
 */
#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <locale>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>

namespace tools {

	/*
	* Mensagem de erro
	*/
	void error(int line, const std::string& msg)
	{
		throw std::domain_error("[Line: " + std::to_string(line) + "]: " + msg);
	}

	/*
	 * Manipulação de Vetor
	 */
	template<typename T>
	void view_vector_line(const std::vector<T>& v, const std::string& separator)
	{
		if (v.empty())
			error(__LINE__, "tools::view_vector_line, vector empty.\n");

		for(size_t i = 0; i < v.size() - 1; ++i){
			std::cout << v[i] << separator;
		}
		std::cout << v[v.size() - 1];
	}

	template<typename T>
	void view_vector(const std::vector<T>& v)
	{
		view_vector_line(v,";");
	}

	template<typename T>
	void view_vector_2D (const std::vector<std::vector<T> >& v)
	{
		for (size_t i = 0; i < v.size(); ++i){
			view_vector(v[i]);
			std::cout << '\n';
		}
	}	

	/*
	 * Manipulação de MAPs
	 */
	std::string find_key(const std::string& key,
		const std::unordered_map<std::string,std::string>& map)
	{
		std::string str("");
		if (map.empty())
			error(__LINE__, "tools::find_key, map empty.\n");
		if (key.empty())
			error(__LINE__, "tools::find_key, key empty.\n");

		std::unordered_map<std::string,std::string>
		::const_iterator it = map.find(key);

		if (it == map.end()) return "";
		return it->second;
	}

	template<typename T_first,typename T_second>
	void view_map(const std::unordered_map<T_first,T_second>& map)
	{
		if (map.empty())
			error(__LINE__, "tools::view_map, map empty.\n");

		for (auto it: map){
			std::cout << it.first << " " << it.second << '\n';
		}
	}

	/*
	 *	Manipulação de STRING
	 */
	void to_upper(std::string& str)
	{
		if (str.empty())
			error(__LINE__, "tools::to_upper, string empty.\n");

		std::locale loc;
		for (std::string::size_type i = 0; i < str.length(); ++i)
			str[i] = std::toupper(str[i], loc);
	}

	std::string upper(const std::string& str)
	{
		if (str.empty())
			error(__LINE__, "tools::upper, string empty.\n");

		std::string str_upper(str);
		to_upper(str_upper);

		return str_upper;
	}

	void to_lower(std::string& str)
	{
		if (str.empty())
			error(__LINE__, "tools::to_lower, string empty.\n");

		std::locale loc;
		for (std::string::size_type i = 0; i < str.length(); ++i)
			str[i] = std::tolower(str[i], loc);
	}

	std::string lower(const std::string& str)
	{
		if (str.empty())
			error(__LINE__, "tools::lower, string empty.\n");

		std::string str_lower(str);
		to_lower(str_lower);

		return str_lower;
	}	

	void split(const std::string& str, std::vector<std::string>& tokens,
		const char& delimiter)
	{
		if (str.empty())
			error(__LINE__, "tools::split, string empty.\n");

		tokens.clear();
		std::stringstream ss(str);
		std::string item;
		
		while(getline(ss, item, delimiter)) {
			tokens.push_back(item);
		}
	}

	std::vector<std::string> split(const std::string& str, const char& delimiter)
	{
		if (str.empty())
			error(__LINE__, "tools::split, string empty.\n");

		std::vector<std::string> tokens;
		std::stringstream ss(str);
		std::string item;
		
		while(getline(ss, item, delimiter)) {
			tokens.push_back(item);
		}		

		return tokens;
	}

	bool match_pos(const std::string& key, const std::string& str, unsigned pos)
	{
		if ((pos + key.length()) > str.length()) return false;
		if (pos < 0 || pos > str.length()) return false;

		if (str.compare(pos, key.length(), key) == 0)
			return true;

	 	return false;
	}

	bool match(const std::string& key, const std::string& str)
	{
		return match_pos(key, str, 0);
	}	

	void remove_pos(const std::string& key, std::string& str, unsigned pos) 
	{
		if ((pos + key.length()) >= str.length())
			error(__LINE__,
				"tools::remove, (pos + key.length) >= string.length.\n");

		if (pos < 0 || pos > str.length())
			error(__LINE__, "tools::remove, pos > string.length.\n");

		if (str.compare(pos, key.length(), key) == 0)
			str.erase(pos, key.length());
		else
			std::cout << "key not found in this position\n";
	}		

	void remove(const std::string& key, std::string& str) 
	{
		remove_pos(key, str, 0);
	}

	/*
	 *	STRING -> PATH, DIRECTORY, FILENAME
	 */
	void split_path(const std::string& path, std::vector<std::string>& tokens)
	{
		if (path.empty())
			error(__LINE__, "tools::split_path, path empty.\n");

		std::vector<std::string> v_temp;
		split(path, v_temp, char(47));
		std::string filename(v_temp.back());

		size_t len =  path.size() - filename.size();
		if (len <= 0)
			error(__LINE__, "tools::split_path, path < filename.\n");

		std::string directory = path.std::string::substr(0, len);
		split(filename, v_temp, char(46));
		std::string filename_extension = v_temp.back();

		len = filename.size() - filename_extension.size();
		if (len <= 0)
			error(__LINE__, "tools::split_path, filename < extension.\n");
			
		std::string name = filename.std::string::substr(0, len - 1);

		tokens = {directory, filename, filename_extension, name};
		
		// std::cout << "{directory, filename, filename_extension, name}:\n{ ";
		// view_vector_line(tokens, "; ");
		// std::cout << " }\n";
	}

	std::string get_directory(const std::string& path)
	{
		std::vector<std::string> tokens;
		split_path(path, tokens);

		return tokens.front();
	}

	std::string get_name(const std::string& filename)
	{
		std::vector<std::string> tokens;
		split(filename, tokens, char(46));

		return tokens.front();
	}	

	std::string get_filename(const std::string& path)
	{
		std::vector<std::string> tokens;
		split_path(path, tokens);

		return tokens[1];
	}

	std::string get_filename_extension(const std::string& path)
	{
		std::vector<std::string> tokens;
		split_path(path, tokens);

		return tokens[2];
	}

	bool check_filename_extension(const std::string& path,
		const std::string& extension)
	{
		if (extension.compare(get_filename_extension(path)) == 0) return true;

		return false;
	}

	bool check_filename_extension(const std::string& path, 
		const std::unordered_map<std::string, std::string>& map_extension)
	{
		if (map_extension.empty()) return false;
		if (path.empty()) return false;

		std::unordered_map<std::string, std::string>
		::const_iterator it = map_extension.find(get_filename_extension(path));

		if (it == map_extension.end()) return false;

		return true;
	}

	bool check_extension(const std::string& extension, 
		const std::unordered_map<std::string, std::string>& map_extension)
	{
		if (map_extension.empty()) return false;
		if (extension.empty()) return false;

		std::unordered_map<std::string, std::string>
		::const_iterator it = map_extension.find(extension);

		if (it == map_extension.end()) return false;

		return true;
	}

	void add_suffix_filename(std::string& src, std::string new_src)
	{
		std::string src_temp("");
		while(src.back() != '.') {
			src_temp = src.back() + src_temp;
			src.pop_back();
		}
		src.pop_back();
		src.append(new_src);
		src.push_back('.');
		src.append(src_temp);
	}

	/*
	 *	Manipulação de arquivos
	 */
	std::string current_dir() {
		char buffer[FILENAME_MAX];
		getcwd(buffer, FILENAME_MAX);
		return std::string(buffer);
	}

	template<typename T>
	void save(const std::vector<T>& v, const std::string& path)
	{
		const char terminator = '\n';

		if (v.empty())
			error(__LINE__, "tools::save, vector empty.\n");

		std::string path_temp = path;
		while(path_temp[0] == char(32)) path_temp.erase(path_temp.begin());

		if (path_temp.empty())
			error(__LINE__, "tools::save, path empty.\n");

		try {

			std::ofstream file_out(path_temp, std::ios::out);

			for (auto s : v ) {
				file_out << s << terminator;
			}

			file_out.close();
		}
		catch(const std::exception& e) {
			error(__LINE__, "tools::save, path failure.\n");
		}
	}

	void save_new_file(const std::string& path)
	{
		std::string path_temp = path;
		while(path_temp[0] == char(32)) path_temp.erase(path_temp.begin());

		if (path_temp.empty())
			error(__LINE__, "tools::save, path empty.\n");

		try {
			std::ofstream file_out(path_temp, std::ios::out);
			file_out.close();
		}
		catch(const std::exception& e) {
			error(__LINE__, "tools::save_new_file, path failure.\n");
		}
	}	

	template<typename T>
	void write(const T& value,	const std::string& path)
	{
		std::string path_temp = path;
		while(path_temp[0] == char(32)) path_temp.erase(path_temp.begin());

		if (path_temp.empty())
			error(__LINE__, "tools::write, path empty.\n");

		try {
			std::ofstream file_out(path, std::ios::app);
			file_out << value;
			file_out.close();		
		}
		catch(const std::exception& e) {
			error(__LINE__, "tools::write, path failure.\n");
		}
	}

	void load(const std::string& path, std::vector<std::string>& v_txt)
	{
		v_txt.clear();
		std::string line;

		std::string path_temp = path;
		while(path_temp[0] == char(32)) path_temp.erase(path_temp.begin());

		if (path_temp.empty())
			error(__LINE__, "tools::load, path empty.\n");		

		try {

			std::ifstream filein(path_temp, std::ios::in);

			while(getline(filein, line)) {
			    v_txt.push_back(line);
			}

			filein.close();			
		}
		catch(const std::exception& e) {
			error(__LINE__, "tools::load, path failure.\n");
		}
	}

	void files(std::vector<std::string>& list, const std::string& folder)
	{
		try {
			list.clear();
			const char* path = const_cast<char*>(folder.c_str());

			DIR* dir;
			struct dirent* entry;
			char entry_path[PATH_MAX + 1];
			size_t path_len = strlen(path);

			if (path == NULL) path = ".";

			strncpy (entry_path, path, sizeof(entry_path));
			if (entry_path[path_len - 1] != '/') {
				entry_path[path_len] = '/';
				entry_path[path_len + 1] = '\0';
				++path_len;
			}

			struct stat info;
			dir = opendir(path);

			while ((entry = readdir(dir)) != NULL) {
				strncpy(entry_path + path_len, entry->d_name,
					sizeof (entry_path) - path_len);
				lstat (entry_path, &info);
				if (S_ISREG(info.st_mode)) {
					list.push_back(std::string(entry_path));		
				}
			}
			closedir(dir);
		}
		catch(const std::exception& e) {
			error(__LINE__, "tools::files\n");
		}
	}

	bool exist_path(const std::string& path) {
		struct stat info;
		return (stat(path.c_str(), &info) == 0);
	}

	void create_directory(const std::string& folder)
	{
		try {
			if (exist_path(folder)) {
				std::cout << folder << " exist\n";
				return;
			}
			
			std::cout << "tools::create_directory, mkdir " << folder;
			if (mkdir(folder.c_str(), S_IRWXU | S_IRWXG |
				S_IROTH | S_IXOTH) == 0)
				std::cout << " ok\n";
			else
				std::cout << " failure" << '\n';
		}
		catch(const std::exception& e) {
			error(__LINE__, "tools::create_directory");
		}
	}
} // namespace tools

#endif // TOOLS_HPP