/*
 * Laboratório básico
 *
 * Uso de mapa padrão
 * ORIGINAL, COPY, GRAYSCALE, BINARY, BINARY_INV
 *
 * Workspace LAB1
 *
 * Objetivo: Testar as ferramentas de apoio (tools.hpp , img_tools.hpp)
 * para que o "arquivo.imgp" gerencie tudo que ocorre no processamento
 * da imagem. Processar neste caso, somente uma image.
 */

#include "../image_tools.hpp"
using namespace img_tools;

using namespace std;
using namespace cv;

int main ()
{
	// definições iniciais
	vector<vector<string> > v_map;
	string image = "../Images/images_test/leaf_diseases.jpg";	// original

	// inicializando workspace
	method_name = "lab1_";
	save_imgp(image, "LAB1");

	// aproveitando estado inicial da variável global do image_tools.hpp
	cout << "info -> " << imgp_path << '\n';

	// verificando se imgp_path foi salvo
	if (!tools::exist_path(imgp_path)) {
		cout << "IMGP failure!" << '\n';
		exit(0);
	} 	

	// inserindo texto dica, aproveitando o token ':' (separador)
	string text(
	":\n"
	": Laboratório básico\n"
	": Workspace => LAB1\n");
	tools::write(text, imgp_path);

	/* ler arquivo .imgp gerado
	 * testar imagens pelo OpenCV
	 * testar reunião de dados sobre a imagem processada
	 */
	cout << "Reload .imgp : " << imgp_path << '\n';
	v_map = load_imgp(imgp_path);

	// OPENCV - ORIGINAL
	string path_ori = search_path("ORIGINAL", v_map);
	cout << "Path image: " << path_ori << '\n';

	Mat src_ori;
	src_ori = imread(path_ori, IMREAD_COLOR);

	if(src_ori.empty()) {
        cout << "could not open or find the image!\n";
        error(__LINE__, "ORIGINAL failure");
	}

	imshow("ORIGINAL", src_ori);
	waitKey(8000);	// 8 segundos de espera

	// OPENCV - COPY
	string path_cp = search_path("COPY", v_map);
	cout << "Path image: " << path_cp << '\n';

	imwrite(path_cp, src_ori);	// cópia de segurança

	// OPENCV - GRAYSCALE
	string path_gray = search_path("GRAYSCALE", v_map);
	cout << "Path image: " << path_gray << '\n';

	Mat src_gray(src_ori.size(), CV_8U);
	cvtColor(src_ori, src_gray, CV_BGR2GRAY);

	imshow("GRAYSCALE", src_gray);
	imwrite(path_gray, src_gray);
	waitKey(8000);

	// OPENCV - BINARY
	string path_bin = search_path("BINARY", v_map);
	cout << "Path image: " << path_bin << '\n';

	Mat src_bin(src_gray.size(), src_gray.type());
	threshold(src_gray, src_bin, 100, 255, THRESH_BINARY);

	imshow("BINARY", src_bin);
	imwrite(path_bin, src_bin);
	waitKey(8000);

	// OPENCV - BINARY_INV
	string path_bin_inv = search_path("BINARY_INV", v_map);
	cout << "Path image: " << path_bin_inv << '\n';

	Mat src_bin_inv(src_gray.size(), src_gray.type());
	threshold(src_gray, src_bin_inv, 120, 255, THRESH_BINARY_INV);

	imshow("BINARY_INV", src_bin_inv);
	imwrite(path_bin_inv, src_bin_inv);	
	waitKey(0);

	return 0;
}