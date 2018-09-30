/*
 * Laboratório 4
 *
 * Uso da configuração de mapa customizado
 *
 * Workspace LAB4
 *
 * Objetivo: Segmentar a folha, exalatando as partes (manchas e limbo).
 *
 */

#include "../image_tools.hpp"

using namespace std;
using namespace cv;
using namespace img_tools;

#undef THRESH
#define THRESH 70
#undef MAX_VALUE
#define MAX_VALUE 160

// Novo mapa de diretórios
static const std::unordered_map<std::string, std::string> map_lab = {
	{"ORIGINAL"			, "."},
	{"COPY"      		, "/original"},
	{"GRAYSCALE" 		, "/grayscale"},
	{"BINARY"    		, "/binary"},
	{"BINARY_INV"		, "/binary_inv"},
	{"TEMP"       		, "/temp"},
	{"RESULT"  			, "/result"},
};

void save_image(Mat& src, const string& token, const string& suffix,
	vector<vector<string> >& v_map)
{
	string path = search_path(token, v_map);
	tools::add_suffix_filename(path, suffix);
	imwrite(path, src);
}

void black2white(Mat& src)
{
	for (int y = 0; y < src.rows; ++y) {
		for (int x = 0; x < src.cols; ++x) {
			Vec3b color = src.at<Vec3b>(Point(y,x));
			if (color[0] == 0 && color[1] == 0 && color[2] == 0) {
				color[0] = 255;
				color[1] = 255;
				color[2] = 255;
				src.at<Vec3b>(Point(y,x)) = color;
			}
		}
	}
}

void method_segmentation(vector<vector<string> >& v_map) {

	cout << "segmentation ...\n";

	Mat src_ori, src_bin, temp;
	Mat hsv, mask_hsv, result_leaf, result_spot;

	// Recuperando imagens
	load_image(src_ori, "COPY", v_map, IMREAD_COLOR);
	load_image(src_bin, "BINARY_INV", v_map, IMREAD_GRAYSCALE);

	// Removendo o fundo
	bitwise_and(src_ori, src_ori, temp, src_bin);
	src_ori = temp.clone();

	// RGB para HSV
	cvtColor(src_ori, hsv, COLOR_BGR2HSV);
	save_image(hsv, "TEMP", "_hsv", v_map);

	// Separar a folha das manchas, pelo tom de verde
	inRange(hsv, Scalar(38, 60, 60), Scalar(60, 255, 160), mask_hsv);
	bitwise_and(src_ori, src_ori, result_leaf, mask_hsv);
	black2white(result_leaf);
	save_image(mask_hsv, "TEMP", "_mask_hsv", v_map);	
	save_image(result_leaf, "RESULT", "_leaf", v_map);

	// Separar as manchas	
	threshold(mask_hsv, mask_hsv, 1, 255, THRESH_BINARY_INV);
	bitwise_and(src_ori, src_ori, result_spot, mask_hsv);
	black2white(result_spot);
	save_image(mask_hsv, "TEMP", "_mask_hsv_inv", v_map);	
	save_image(result_spot, "RESULT", "_spot", v_map);
}	

int main()
{
	string new_workspace(tools::current_dir() + "/LAB4");
	string new_method_name = "lab4_";
	string new_folder = "../Images/images_test/leaf_disease";
	string new_extension = "png";

	bath(new_workspace, new_method_name, new_folder, new_extension, map_lab);

	vector<string> imgps = list_imgp(new_workspace);
	vector<vector<string> > v_map;
	for (auto imgp: imgps) {
		v_map = load_imgp(imgp);
		method_segmentation(v_map);
	}

	return 0;
}