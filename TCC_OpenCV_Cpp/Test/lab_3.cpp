/*
 * Laboratório 3
 *
 * Workspace LAB3
 *
 * Objetivo: Fazer binarização com limites variáveis.
 *
 */

#include "../image_tools.hpp"
using namespace img_tools;

using namespace std;
using namespace cv;

#define FROM_THRESH 70
#define TO_THRESH 150
#define STEP 2

void method_threshold_loop(Mat& src_binary, Mat& src_gray, const string path,
	int threshold_type)
{
	for (int i = FROM_THRESH; i < TO_THRESH; i += STEP) {
		string path_temp = path;
		threshold(src_gray, src_binary, i, MAX_VALUE, threshold_type);
		tools::add_suffix_filename(path_temp, "_" + to_string(i)	+ "-"
									+ to_string(MAX_VALUE));
		cout << "=> " << path_temp << "\n";
		imwrite(path_temp, src_binary);
	}
}

void method_threshold(vector<vector<string> >& v_map)
{
	// Recuperando imagem base
	Mat src_gray;
	load_image(src_gray, "GRAYSCALE", v_map, IMREAD_GRAYSCALE);

	// OPENCV - THRESHOLD variável
	Mat src_bin(src_gray.size(), src_gray.type());
	Mat src_bin_inv(src_gray.size(), src_gray.type());

	cout << "THRESHOLD:\n";
	method_threshold_loop(src_bin, src_gray,
						  search_path("BINARY", v_map),
						  THRESH_BINARY);
	method_threshold_loop(src_bin_inv, src_gray,
						  search_path("BINARY_INV", v_map),
						  THRESH_BINARY_INV);
}	

int main()
{
	string new_workspace(tools::current_dir() + "/LAB3");
	string new_method_name = "lab3_";
	string new_folder = "../Images/images_test/leaf_disease";
	string new_extension = "jpg";	

	bath(new_workspace, new_method_name, new_folder, new_extension);

	vector<string> imgps = list_imgp(new_workspace);
	vector<vector<string> > v_map;
	for (auto imgp: imgps) {
		v_map = load_imgp(imgp);
		method_threshold(v_map);
	}

	return 0;
}