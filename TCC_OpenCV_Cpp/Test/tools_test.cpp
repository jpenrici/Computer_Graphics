/*
 * Arquivo para simples visualização das saídas dos métodos
 */
#include "../tools.hpp"
#include <iostream>
#include <unordered_map>

using namespace std;
using namespace tools;

inline void test(int line, int t, string msg)
{
	cout << "\n[ Line: " << line << ", Test: "
		<< t << " , " << msg << "]\n";
}

int main()
{

	int t(1);

	// visualizar vetor - template
	test(__LINE__, t++, "view_vector");
	try {
		view_vector(vector<int>{});
	}
	catch(const exception& e) {
		cout << "test throw ... ok\n";
		cout << e.what() << '\n';
	}

	test(__LINE__, t++, "view_vector_line");
	view_vector_line(vector<char>{'0', '1', 'A', 'a'}, ";");
	cout << '\n';
	view_vector_line(vector<string>{"abc", "def"},",");
	cout << '\n';	
	view_vector_line(vector<float>{10.01, 10.12, 10.23}," :");
	cout << '\n';	

	vector<double> v {1.2, 1.3};
	view_vector(v);
	cout << '\n';

	test(__LINE__, t++, "view_vector_2D");
	vector<int> v_int {1, 2, 3, 4, 5};
	view_vector_2D(vector<vector<int> >{v_int, v_int});

	// minúscula para maiúscula
	test(__LINE__, t++, "to_upper, upper");	
	string str = "abc";
	to_upper(str);
	cout << str;

	str = upper("def");
	cout << str << '\n';

	// split
	test(__LINE__, t++, "split");	
	vector<string> v1;
	split("/1/2/3/4.5", v1, '/');
	view_vector_line(v1, ",");
	cout << '\n';

	v1 = split("/1/2/3/ 4/5/6/7  8/", char(32));
	view_vector(v1);
	cout << '\n';

	// split path
	test(__LINE__, t++, "split_path");
	try {
		split_path("directory/filename.extension", v1);
		view_vector(v1);
	}
	catch(const exception& e) {
		cout << e.what() << '\n';
	}

	// comparação de string
	test(__LINE__, t++, "match_pos");
	cout << boolalpha << match("aa", "AA") << '\n';
	cout << boolalpha << match_pos("12", "01245", 1) << '\n';

	string str1 = "AAA";
	str = upper("aaa");
	cout << str << char(32) << str1 << char(32);
	cout << boolalpha << match(str, str1) << '\n';


	// remover string de string
	test(__LINE__, t++, "remove_pos");	
	str = "0123456789";
	cout << str << '\n';
	remove_pos("456", str, 4);
	cout << str << '\n';
	remove("01237", str);
	cout << str << '\n';

	// obter do arquivo
	test(__LINE__, t++, "get_filename ...");	
	cout << get_filename_extension("dir/filename.png") << '\n';
	cout << get_filename("dir/filename.png") << '\n';
	cout << get_directory("dir/filename.png") << '\n';
	cout << get_name("NAME.png") << '\n';

	// comparar extensão de arquivo
	test(__LINE__, t++, "check_filename_extension");	
	cout << boolalpha 
		<< check_filename_extension("dir/filename.jpeg", "dpp") << '\n'
		<< check_filename_extension("dir/filename.JPG", "jpg") << '\n'
		<< check_filename_extension("dir/filename.dpp", "dpp") << '\n';

	// comparar extensão de arquivo com mapa
	test(__LINE__, t++, "check_filename_extension map");	
	unordered_map<string, string> map_extension = {
			{"PNG", "png"}, {"JPG", "jpg"}, {"JPEG", "jpeg"},
		};		
	cout << boolalpha << check_filename_extension(
			upper("dir/filename.jpeg"), map_extension) << '\n';

	// teste map
	test(__LINE__, t++, "find_key");	
	cout << find_key("JPEG", map_extension) << '\n';

	// salvar vetor em arquivo texto
	test(__LINE__, t++, "save");	
	vector<float> v_float {1, 2, 3, 4, 5, 6, 7};

	try {
		// teste de path em branco ou vazio
		save(v_float, " ");
	}
	catch(const exception& e) {
		cout << "test throw ... ok\n";
		cout << e.what() << '\n';
	}

	try {
		save(v_float, "output_file");
		cout << "save ok" << '\n';
	}
	catch(const exception& e) {
		cout << e.what() << '\n';
	}

	// salvar ou sobrescrever arquivo
	test(__LINE__, t++, "save_new_file");	
	try {
		save_new_file("output_file");
		cout << "save_new_file ok" << '\n';
	}
	catch(const exception& e) {
		cout << e.what() << '\n';
	}

	// incluir texto no arquivo
	test(__LINE__, t++, "write");	
	try {
		write("arquivo teste", "output_file");
		write('\n', "output_file");
		write(double(99999.123), "output_file");
		cout << "write ok" << '\n';
	}
	catch(const exception& e) {
		cerr << e.what() << '\n';
	}
	
	// lendo arquivo gravado e transferir linhas para um vetor
	test(__LINE__, t++, "load");	
	vector<string> v_text;
	try {
		load("output_file", v_text);
		view_vector_line(v_text, "; ");
	}
	catch(const exception& e) {
		cerr << e.what() << '\n';
	}

	// listar arquivos no diretório
	test(__LINE__, t++, "files, directory");	
	cout << '\n';
	try {
		files(v_text, ".");
		view_vector_line(v_text, "\n");
	}
	catch(const exception& e) {
		cerr << e.what() << '\n';
	}

	test(__LINE__, t++, "view_map");
	view_map(map_extension);

	// checar se path existe
	test(__LINE__, t++, "exist_path");
	cout << boolalpha 
		 << exist_path("/home");

	// criar diretórios
	test(__LINE__, t++, "create_directory");
	create_directory("../Workspace");
	create_directory("../Workspace/imgp");
	create_directory("../Workspace/output/other/other");

	// remover extensão
	test(__LINE__, t++, "add_suffix_filename");
	string p = "directory/directory/filename.png";
	cout << p << '\n';
	add_suffix_filename(p, "_new");
	cout << p << '\n';	

	return 0;
}