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

// Busca de informação por vetor
// apesar de mais lento, atende o propósito do teste
string search_path(const string& format, vector<vector<string> >& v)
{
	// Sem tratamento de erros, por enquanto.
	for (auto path: v){
		// std::cout << path.front() << " " << path.back() << '\n';
		if (path.front() == format) return path.back();
	}
	return "EMPTY";
}

int main ()
{
	/*
	 * Laboratório básico
	 *
	 * Uso da configuração de mapa padrão
	 * ORIGINAL, COPY, GRAYSCALE, BINARY, BINARY_INV
	 *
	 * Workspace LAB1
	 *
	 * Objetivo testar as ferramentas de apoio (tools.hpp , img_tools.hpp)
	 * para que o "arquivo.imgp" gerencie tudo que ocorre no processamento
	 * da imagem.
	 */

	// definições iniciais
	std::vector<std::vector<std::string> > v_map;
	string image = "../Images/images_test/leaf_diseases.jpg";	// original

	// inicializando workspace com a imagem e
	// alterando a variável global method_name
	method_name = "lab1_";
	save_imgp(image, "LAB1");

	// aproveitando estado inicial da variável global do image_tools.hpp
	std::cout << "info -> " << imgp_path << '\n';

	// verificando se imgp_path foi salvo
	if (!tools::exist_path(imgp_path)) {
		std::cout << "IMGP failure!" << '\n';
		exit(0);
	} 	

	// inserindo texto dica, aproveitando o token ':' (separador)
	std::string text(
	":\n"
	": Laboratório básico\n"
	":\n"
	": Uso da configuração de mapa padrão\n"
	": ORIGINAL, COPY, GRAYSCALE, BINARY, BINARY_INV\n"
	":\n"
	": Workspace LAB1\n"
	":\n"
	": Objetivo testar ferramentas de apoio (tools.hpp , img_tools.hpp)\n");

	tools::write(text, imgp_path);

	// ler arquivo .imgp gerado para testar imagens pelo OpenCV
	std::cout << "Load .imgp : " << image << '\n';
	v_map = load_imgp(imgp_path);

	// OPENCV - ORIGINAL
	std::string path_ori = search_path("ORIGINAL", v_map);
	std::cout << "Selected image: " << path_ori << '\n';

	Mat src_ori;
	src_ori = imread(path_ori, IMREAD_COLOR);

	// Se path_ori for EMPTY vai falhar
	if(src_ori.empty()) {
        cout << "could not open or find the image!\n";
        error(__LINE__, "ORIGINAL failure");
	}

	imshow("ORIGINAL", src_ori);

	waitKey(8000);	// 8 segundos de espera

	// OPENCV - COPY
	std::string path_cp = search_path("COPY", v_map);
	std::cout << "Selected image: " << path_cp << '\n';

	imwrite(path_cp, src_ori);	// cópia de segurança

	// OPENCV - GRAYSCALE
	std::string path_gray = search_path("GRAYSCALE", v_map);
	std::cout << "Selected image: " << path_gray << '\n';

	Mat src_gray(src_ori.size(), CV_8U);
	cvtColor(src_ori, src_gray, CV_BGR2GRAY);

	imshow("GRAYSCALE", src_gray);
	imwrite(path_gray, src_gray);

	waitKey(8000);

	// OPENCV - BINARY
	std::string path_bin = search_path("BINARY", v_map);
	std::cout << "Selected image: " << path_bin << '\n';

	Mat src_bin(src_gray.size(), src_gray.type());
	threshold(src_gray, src_bin, 80, 149, THRESH_BINARY);

	imshow("BINARY", src_bin);
	imwrite(path_bin, src_bin);

	waitKey(8000);

	// OPENCV - BINARY_INV
	std::string path_bin_inv = search_path("BINARY_INV", v_map);
	std::cout << "Selected image: " << path_bin_inv << '\n';

	Mat src_bin_inv(src_gray.size(), src_gray.type());
	threshold(src_gray, src_bin_inv, 100, 150, THRESH_BINARY_INV);

	imshow("BINARY_INV", src_bin_inv);
	imwrite(path_bin_inv, src_bin_inv);	

	waitKey(0);

	return 0;
}