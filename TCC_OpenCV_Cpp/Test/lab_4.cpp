/*
 * Laboratório 4
 *
 * Uso da configuração de mapa customizado
 *
 * Workspace LAB4
 *
 * Teste com foto real e com fundos retirados no GIMP.
 * Objetivo detectar a cor verde.
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

#define MIN_VALUE 160
#define MAX_VALUE 180

static const std::unordered_map<std::string, std::string> map_lab4 = {
	{"ORIGINAL"  , "."},
	{"COPY"      , "/original"},
	{"GRAYSCALE" , "/grayscale"},
	{"BINARY"    , "/binary"},
	{"GREEN"     , "/green"},
};

Mat src_ori, src_gray, src_bin, src_hsv, src_green;
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
		save_imgp(image, workspace, map_lab4);
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

		// OPENCV - BINARY
		string path_bin = search_path("BINARY", v_map);
		tools::add_suffix_filename(path_bin, "_" + to_string(MIN_VALUE)
			+ "-" + to_string(MAX_VALUE));
		cout << "OPENCV BINARY: " << path_bin << '\n';

		threshold(src_gray, src_bin, MIN_VALUE, MAX_VALUE, THRESH_BINARY);
		imwrite(path_bin, src_bin);
}

void method_hsv() {

	// OPENCV - HSV
	string path_green = search_path("GREEN", v_map);
	cout << "OPENCV HSV:" << path_green << '\n';

	cvtColor(src_ori, src_hsv, CV_BGR2HSV);

	string path_hsv = path_green;
	tools::add_suffix_filename(path_hsv, "_hsv");
	imwrite(path_hsv, src_hsv);

	inRange(src_hsv, Scalar(38, 0, 0), Scalar(70, 255, 255), src_green);
	tools::add_suffix_filename(path_green, "_green");
	imwrite(path_green, src_green);
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
	create_workspace(new_workspace, map_lab4);

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
	image_processing("LAB4", "../Images/images_test/Anthurium", "jpg");

	return 0;
}