/*
 * Laboratório 4
 *
 * Uso da configuração de mapa customizado
 *
 * Workspace LAB4
 *
 * Teste com foto real e com fundos retirados no GIMP.
 * Objetivo detectar as manchas nas folhas.
 *
 */

#include "opencv2/photo.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"	

#include "../image_tools.hpp"

#include <iostream>
#include <unordered_map>

using namespace std;
using namespace cv;
using namespace img_tools;

#define MIN_VALUE 180
#define MAX_VALUE 255

static const std::unordered_map<std::string, std::string> map_lab = {
	{"ORIGINAL"  , "."},
	{"COPY"      , "/original"},
	{"GRAYSCALE" , "/grayscale"},
	{"BINARY_INV", "/binary_inv"},
	{"SPOT"      , "/spot"},
};

Mat src_ori, src_gray, src_bin_inv, src_hsv, src_spot;
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

void method_basic() {

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

void method_threshold() {

		// OPENCV - BINARY_INV
		string path_bin_inv = search_path("BINARY_INV", v_map);
		tools::add_suffix_filename(path_bin_inv, "_" + to_string(MIN_VALUE)
			+ "-" + to_string(MAX_VALUE));
		cout << "OPENCV BINARY_INV: " << path_bin_inv << '\n';

		threshold(src_gray, src_bin_inv, MIN_VALUE, MAX_VALUE, THRESH_BINARY_INV);
		imwrite(path_bin_inv, src_bin_inv);
}

void method_hsv() {

	// OPENCV - HSV
	string path_spot = search_path("SPOT", v_map);
	cout << "OPENCV HSV:" << path_spot << '\n';

	cvtColor(src_ori, src_hsv, CV_BGR2HSV);

	string path_hsv = path_spot;
	tools::add_suffix_filename(path_hsv, "_hsv");
	imwrite(path_hsv, src_hsv);

	Mat src_temp;
	inRange(src_hsv, Scalar(20, 10, 10), Scalar(90, 255, 255), src_temp);
	bitwise_not(src_temp, src_spot, src_bin_inv);

	tools::add_suffix_filename(path_spot, "_spot");
	imwrite(path_spot, src_spot);
}

void method_main(const vector<string>& images) {

	for (auto image: images) {
		
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
		method_hsv();
	}
}	

void image_processing(const string& new_workspace, const string& folder, 
	const string& ext)
{
	// passo 1 - checar se diretório de imagens existe
	if (!tools::exist_path(folder)) {
		cout << "folder failure\n";
		exit(0);
	}	

	// passo 2 - criar workspace com MAP customizado
	method_name = tools::lower(new_workspace) + "_";
	create_workspace(new_workspace, map_lab);

	// passo 3 - listar arquivos de imagens alvo
	vector<string> images;
	tools::files(images, folder);

	// passo 4 - gerar os arquivos de gerencia
	create_imgp_base(new_workspace, images, ext);
	cout << '\n';

	// passo 5 - processar para cada .imgp as imagens
	tools::files(images, new_workspace + "/imgp");
	method_main(images);	
}

int main()
{
	image_processing("LAB4", "../Images/images_test", "jpg");

	return 0;
}