#include "opencv2/photo.hpp"		// computational photography
#include "opencv2/imgproc.hpp"		// image processing
#include "opencv2/imgcodecs.hpp"	// image I/O
#include "opencv2/highgui.hpp"		// high level GUI and Media
#include "opencv2/core.hpp"			// core functionality

#include "../image_tools.hpp"

#include <iostream>
#include <unordered_map>

using namespace std;
using namespace cv;
using namespace img_tools;

#define THMIN 70
#define THMAX 220
#define STEP 15

/*
 * Laboratório 3
 *
 * Uso da configuração de mapa padrão
 * ORIGINAL, COPY, GRAYSCALE, BINARY, BINARY_INV
 *
 * Workspace LAB3
 *
 * Fazer binarização com limites variáveis
 *
 */
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
		save_imgp(image, workspace);
	}
}

void method_threshold(Mat& src_gray, vector<vector<string> >& v_map) {

	for (int i = THMIN; i < THMAX; i += STEP) {

		// OPENCV - BINARY
		string path_bin = search_path("BINARY", v_map);
		tools::add_suffix_filename(path_bin, "_" + to_string(i));
		cout << "OPENCV BINARY: " << path_bin << '\n';

		Mat src_bin(src_gray.size(), src_gray.type());
		threshold(src_gray, src_bin, i, THMAX - i, THRESH_BINARY);

		imwrite(path_bin, src_bin);

		// OPENCV - BINARY_INV
		string path_bin_inv = search_path("BINARY_INV", v_map);
		tools::add_suffix_filename(path_bin_inv, "_inv_" + to_string(i));
		cout << "OPENCV BINARY_INV: " << path_bin_inv << '\n';

		Mat src_bin_inv(src_gray.size(), src_gray.type());
		threshold(src_gray, src_bin_inv, i, THMAX - i, THRESH_BINARY_INV);

		imwrite(path_bin_inv, src_bin_inv);
	}
}	

void method_basic(const vector<string>& images) {

	vector<vector<string> > v_map;
	for (auto image: images) {
		
		if (!tools::exist_path(image)) {
			cout << "IMGP failure!" << '\n';
			continue;
		}		

		cout << '\n';
		cout << "reload .imgp : " << image << '\n';
		v_map = load_imgp(image);

		// OPENCV - ORIGINAL
		string path_ori = search_path("ORIGINAL", v_map);
		cout << "OPENCV ORIGINAL: " << path_ori << '\n';

		Mat src_ori;
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

		Mat src_gray(src_ori.size(), CV_8U);
		cvtColor(src_ori, src_gray, CV_BGR2GRAY);
		imwrite(path_gray, src_gray);

		// Método Threshold variado	
		method_threshold(src_gray, v_map);

	}
}	

void image_processing_basic(const string& new_workspace, const string& folder, 
	const string& ext)
{
	// passo 1 - checar se diretório de imagens existe
	if (!tools::exist_path(folder)) {
		cout << "folder failure\n";
		exit(0);
	}	

	// passo 2 - criar workspace
	method_name = tools::lower(new_workspace) + "_";
	create_workspace(new_workspace);

	// passo 3 - listar arquivos de imagens alvo
	vector<string> images;
	tools::files(images, folder);

	// passo 4 - gerar os arquivos de gerencia
	create_imgp_base(new_workspace, images, ext);
	cout << '\n';

	// passo 5 - processar para cada .imgp as imagens
	tools::files(images, new_workspace + "/imgp");
	method_basic(images);	
}

int main()
{
	image_processing_basic("LAB3", "../Images/images_test", "png");

	return 0;
}