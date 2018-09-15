/*
 * Laboratório 5
 *
 * Uso da configuração de mapa customizado
 *
 * Workspace LAB5_LeafsDiseases
 *
 * Construção de "folhas doentes"
 *
 * Objetivo receber uma lista de images de folhas sadias, uma lista de imagens
 * de manchas foliares e mesclar as imagens em pontos aleatórios.
 *
 */

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

#include "../image_tools.hpp"
#include "../create_leafs_diseases.hpp"

#include <iostream>
#include <unordered_map>

using namespace std;
using namespace cv;
using namespace cld;
using namespace img_tools;

// Threshold para folha
#define MIN_VALUE 38
#define MAX_VALUE 255

// Mapa de diretórios
static const std::unordered_map<std::string, std::string> map_lab = {
	{"ORIGINAL"  , "."},
	{"COPY"      , "/original"},
	{"GRAYSCALE" , "/grayscale"},
	{"BINARY"    , "/binary"},
	{"LEAFS_DISEASES", "/leafs_diseases"}
};

Mat src_ori, src_gray, src_bin, src_spot;
vector<vector<string> > v_map;

string search_path(const string& format, vector<vector<string> >& v)
{
	for (auto path: v) {
		if (path.front() == format) return path.back();
	}
	return "EMPTY";
}

void create_imgp_base(const string& workspace, const vector<string>& images,
	const string& ext)
{
	for (auto image: images) {
		if (!tools::check_filename_extension(image, ext)) continue;
		cout << "image: " << image << '\n';
		save_imgp(image, workspace, map_lab);
	}
}

void method_basic()
{
		// OPENCV - ORIGINAL
		string path_ori = search_path("ORIGINAL", v_map);
		cout << "OPENCV ORIGINAL: " << path_ori << '\n';

		src_ori = imread(path_ori, IMREAD_COLOR);
		if(src_ori.empty()) {
	        cout << "could not open or find the image!\n";
	        error(__LINE__, "ORIGINAL failure");
		}

		// OPENCV - COPY
		string path_cp = search_path("COPY", v_map);
		cout << "OPENCV COPY: " << path_cp << '\n';

		imwrite(path_cp, src_ori);	

		// OPENCV - GRAYSCALE
		string path_gray = search_path("GRAYSCALE", v_map);
		cout << "OPENCV GRAYSCALE: " << path_gray << '\n';

		cvtColor(src_ori, src_gray, CV_BGR2GRAY);
		imwrite(path_gray, src_gray);
}

void method_threshold()
{
		// OPENCV - BINARY
		string path_bin = search_path("BINARY", v_map);
		// tools::add_suffix_filename(path_bin, "_" + to_string(MIN_VALUE)
		// 	+ "-" + to_string(MAX_VALUE));
		cout << "OPENCV BINARY: " << path_bin << '\n';

		threshold(src_gray, src_bin, MIN_VALUE, MAX_VALUE, THRESH_BINARY);
		imwrite(path_bin, src_bin);
}

void method_leafs_diseases(const string& spot, const int& count)
{
		cout << "SPOT: " << spot << '\n';

		// OPENCV - COPY
		string path_cp = search_path("COPY", v_map);
		cout << "OPENCV COPY: " << path_cp << '\n';

		// OPENCV - BINARY
		string path_bin = search_path("BINARY", v_map);
		cout << "OPENCV BINARY: " << path_bin << '\n';

		// LEAFS_DISEASES
		string path_disease = search_path("LEAFS_DISEASES", v_map);
		cout << "Output LEAFS_DISEASES: " << path_disease << '\n';
		tools::add_suffix_filename(path_disease, "_" + to_string(count));

		string path_temp = "../Test/";
		build_leaf_disease(path_temp + path_cp, path_temp + path_bin, 
			spot, path_temp + path_disease, 100);
}

void method_main(const vector<string>& images_leafs,
	const vector<string>& images_spots)
{
	for (auto image: images_leafs) {
		
		if (!tools::exist_path(image)) {
			cout << "IMGP failure!" << '\n';
			continue;
		}		

		cout << '\n';
		cout << "reload .imgp : " << image << '\n';
		v_map = load_imgp(image);

		// Sequência de Métodos
		method_basic();
		method_threshold();

		int count(0);
		for (auto spot: images_spots) {

			if (!tools::exist_path(spot)) {
				cout << "IMGP failure!" << '\n';
				continue;
			}

			method_leafs_diseases(spot, count++);	// construir folhas doentes
		}
	}
}	

void image_processing(const string& new_workspace, const string& folder_leafs, 
	const string& folder_spots, const string& ext)
{
	// passo 1 - checar se diretórios de imagens existem
	cout << "folder_leafs ... ";
	if (!tools::exist_path(folder_leafs)) {
		cout << "failure\n";
		exit(0);
	} else {
		cout << "ok\n";
	}

	cout << "folder_spots ... ";
	if (!tools::exist_path(folder_spots)) {
		cout << "failure\n";
		exit(0);
	} else {
		cout << "ok\n";
	}

	// passo 2 - criar workspace com MAP customizado
	method_name = tools::lower(new_workspace) + "_";
	create_workspace(new_workspace, map_lab);
	cout << '\n';

	// passo 3 - listar arquivos de imagens alvo
	vector<string> images_leafs;
	tools::files(images_leafs, folder_leafs);

	cout << "images_leafs ...\n";
	tools::view_vector_line(images_leafs, "\n");
	cout << '\n';

	vector<string> images_spots;
	tools::files(images_spots, folder_spots);

	cout << "images_spots ...\n";
	tools::view_vector_line(images_spots, "\n");
	cout << '\n';

	// passo 4 - gerar os arquivos de gerencia
	create_imgp_base(new_workspace, images_leafs, ext);
	cout << '\n';

	// passo 5 - processar para cada .imgp as imagens
	tools::files(images_leafs, new_workspace + "/imgp");
	method_main(images_leafs, images_spots);
}

int main()
{
	image_processing("LAB5_LeafsDiseases", "../Images/images_test/leafs",
	"../Images/images_test/spots", "jpg");

	return 0;
}