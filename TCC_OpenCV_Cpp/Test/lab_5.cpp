/*
 * Laboratório 5
 *
 * Uso da configuração de mapa customizado
 *
 * Workspace LAB5
 *
 * Construção de "folhas doentes"
 *
 * Objetivo: Receber uma lista de images de folhas sadias, uma lista de imagens
 * de manchas foliares e mesclar as imagens em pontos aleatórios.
 *
 */

#include "../image_tools.hpp"
using namespace img_tools;

#include "../create_leafs_diseases.hpp"
using namespace cld;

using namespace std;
using namespace cv;

// Threshold para folha
#undef THRESH
#undef MAX_VALUE
#define THRESH 38
#define MAX_VALUE 255

// Novo mapa de diretórios
static const std::unordered_map<std::string, std::string> map_lab = {
	{"ORIGINAL"  , "."},
	{"COPY"      , "/original"},
	{"GRAYSCALE" , "/grayscale"},
	{"BINARY"    , "/binary"},
	{"BINARY_INV", "/binary_inv"},
	{"LEAFS_DISEASES", "/leafs_diseases"}	
};

void method_leafs_diseases(const string& spot,
						   vector<vector<string> >& v_map,
						   int num)
{
		cout << "SPOT: " << spot << '\n';

		// Recuperando imagens base
		string path_cp = search_path("COPY", v_map);

		// Observar que o limbo tem que ser branco
		string path_bin = search_path("BINARY_INV", v_map);	

		// LEAFS_DISEASES
		string path_disease = search_path("LEAFS_DISEASES", v_map);
		tools::add_suffix_filename(path_disease, "_" + to_string(num));
		cout << path_disease << '\n';

		build_leaf_disease(path_cp, path_bin, spot, path_disease, 200);
}

int main()
{
	string new_workspace(tools::current_dir() + "/LAB5");
	string new_method_name = "lab5_";
	string new_folder = "../Images/images_test/leaf_disease";
	string new_extension = "jpg";
	string folder_spots = "../Images/images_test/spots";	

	cout << "folder_spots ... ";
	if (!tools::exist_path(folder_spots)) {
		cout << "failure\n";
		return (EXIT_FAILURE);
	} else {
		cout << "ok\n";
	}

	bath(new_workspace, new_method_name, new_folder, new_extension, map_lab);

	vector<string> imgps = list_imgp(new_workspace);
	vector<vector<string> > v_map;

	vector<string> images_spots;
	tools::files(images_spots, folder_spots);
	tools::view_vector_line(images_spots, "\n");
	cout << "\n\n";	

	for (auto imgp: imgps) {

		v_map = load_imgp(imgp);

		int num(0);
		for (auto spot: images_spots) {
			if (!tools::exist_path(spot)) {
				cout << "spot image failure!" << '\n';
				continue;
			}
			// construir folhas doentes
			method_leafs_diseases(spot, v_map, num++);	
		}		
	}

	return 0;
}