#include "tools.hpp"
#include <iostream>
#include <unordered_map>

int main()
{
	// visualizar vetor - template
	try {
		tools::view_vector(std::vector<int>{});
	}
	catch(const std::exception& e) {
		std::cout << "test throw ... ok\n";
		std::cout << e.what() << '\n';
	}

	tools::view_vector_line(std::vector<char>{'0', '1', 'A', 'a'}, ";");
	std::cout << '\n';
	tools::view_vector_line(std::vector<std::string>{"abc", "def"},",");
	std::cout << '\n';	
	tools::view_vector_line(std::vector<float>{10.01, 10.12, 10.23}," :");
	std::cout << '\n';	

	std::vector<double> v {1.2, 1.3};
	tools::view_vector(v);
	std::cout << '\n';

	// minúscula para maiúscula
	std::string str = "abc";
	tools::to_upper(str);
	std::cout << str;

	str = tools::upper("def");
	std::cout << str << '\n';

	// split
	std::vector<std::string> v1;
	tools::split("/1/2/3/4.5", v1, '/');
	tools::view_vector_line(v1, ",");
	std::cout << '\n';

	v1 = tools::split("/1/2/3/ 4/5/6/7  8/", char(32));
	tools::view_vector(v1);
	std::cout << '\n';

	// split path
	try {
		tools::split_path("directory/filename.extension", v1);
	}
	catch(const std::exception& e) {
		std::cout << e.what() << '\n';
	}

	// comparação de string
	std::cout << std::boolalpha << tools::match("aa", "AA") << '\n';
	std::cout << std::boolalpha << tools::match_pos("12", "01245", 1) << '\n';

	std::string str1 = "AAA";
	str = tools::upper("aaa");
	std::cout << str << char(32) << str1 << char(32);
	std::cout << std::boolalpha << tools::match(str, str1) << '\n';


	// remover string de string
	str = "0123456789";
	std::cout << str << '\n';
	tools::remove_pos("456", str, 4);
	std::cout << str << '\n';
	tools::remove("01237", str);
	std::cout << str << '\n';

	// obter do arquivo
	std::cout << tools::get_filename_extension("dir/filename.png") << '\n';
	std::cout << tools::get_filename("dir/filename.png") << '\n';
	std::cout << tools::get_directory("dir/filename.png") << '\n';
	std::cout << tools::get_name("NAME.png") << '\n';

	// comparar extensão de arquivo
	std::cout << std::boolalpha 
		<< tools::check_filename_extension("dir/filename.jpeg", "dpp") << '\n'
		<< tools::check_filename_extension("dir/filename.JPG", "jpg") << '\n'
		<< tools::check_filename_extension("dir/filename.dpp", "dpp") << '\n';

	// comparar extensão de arquivo com mapa
	std::unordered_map<std::string, std::string> map_extension = {
			{"PNG", "png"}, {"JPG", "jpg"}, {"JPEG", "jpeg"},
		};		
	std::cout << std::boolalpha << tools::check_filename_extension(
			tools::upper("dir/filename.jpeg"), map_extension) << '\n';

	// teste map
	std::cout << tools::find_key("JPEG", map_extension) << '\n';

	// salvar vetor em arquivo texto
	std::vector<float> v_float {1, 2, 3, 4, 5, 6, 7};

	try {
		// teste de path em branco ou vazio
		tools::save(v_float, " ");
	}
	catch(const std::exception& e) {
		std::cout << "test throw ... ok\n";
		std::cout << e.what() << '\n';
	}

	try {
		tools::save(v_float, "outfile_float");
		std::cout << "ok" << '\n';
	}
	catch(const std::exception& e) {
		std::cout << e.what() << '\n';
	}

	// salvar ou sobrescrever arquivo
	try {
		tools::save_new_file("outfile_float");
		std::cout << "save_new_file ok" << '\n';
	}
	catch(const std::exception& e) {
		std::cout << e.what() << '\n';
	}

	// incluir texto no arquivo
	try {
		tools::write(double(100.123), "outfile_float");
		tools::write('\n', "outfile_float");
		tools::write(double(99999.123), "outfile_float");
		std::cout << "ok" << '\n';
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	
	// lendo arquivo gravado e transferir linhas para um vetor
	std::vector<std::string> v_text;
	try {
		tools::load("outfile_float", v_text);
		tools::view_vector_line(v_text, "; ");
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	// listar arquivos no diretório
	std::cout << '\n';
	try {
		tools::files(v_text, ".");
		tools::view_vector_line(v_text, "\n");
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}

	return 0;
}