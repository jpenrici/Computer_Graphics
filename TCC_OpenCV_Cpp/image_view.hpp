/*
 * Interface gráfica para visualização das imagens gerenciados pelo .imgp
 *
 */
#ifndef IMAGE_VIEW_HPP
#define IMAGE_VIEW_HPP

#include "tools.hpp"

#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <unordered_map>

class Image_view : public Gtk::Window {

#define IMGROWS 2
#define IMGCOLS 2
#define SHORT_PATH 1	

public:
	Image_view();
	virtual ~Image_view();

protected:
	const std::string image_default;

	int image_created;
	bool image_lock[IMGROWS * IMGCOLS];
	bool swap_released[IMGROWS * IMGCOLS];
	std::vector<std::vector<std::string> > v_map;

	// métodos comuns
	std::string short_path(const std::string& /*path*/);

	std::vector<std::vector<std::string> >
	load_imgp(const std::string& /*path imgp*/);	

	// eventos
	void on_menu_file_new();
	void on_menu_file_save();
	void on_menu_file_save_as();
	void on_menu_file_quit();
	void on_menu_option_one();
	void on_menu_option_two();
	void on_menu_help_about();
	void on_button_clicked(const int& /*num image*/);
	void on_hide_button_image();
	void on_combobox_changed(const int& /*num image*/);
	void update_image(const int& /*num image*/);	
	void report(const std::string& /*message*/);
	void report_terminal(const std::string& /*message*/);

	// widgets
	Gtk::Box 		VBox;
	Gtk::Box 		HBox[IMGROWS];
	Gtk::Box 		VBox_image[IMGROWS * IMGCOLS];
	Gtk::Image 		image[IMGROWS * IMGCOLS];    
	Gtk::Button 	button[IMGROWS * IMGCOLS];
	Gtk::ComboBox 	combobox_image[IMGROWS * IMGCOLS];
	Gtk::Label 		label_info[IMGROWS * IMGCOLS];

	Glib::RefPtr<Gtk::UIManager> 	menu_refUIManager;
	Glib::RefPtr<Gtk::ActionGroup> 	menu_refActionGroup;
	Glib::RefPtr<Gtk::RadioAction> 	menu_refOptionOne, menu_refOptionTwo;
	Glib::RefPtr<Gtk::ToggleAction>  menu_refCheckOne;

	class ModelColumns : public Gtk::TreeModel::ColumnRecord {
	public:
		ModelColumns()
		{
			add(action);
			add(source);
		}
		Gtk::TreeModelColumn<Glib::ustring> action;
		Gtk::TreeModelColumn<Glib::ustring> source;
	};

	ModelColumns combobox_image_columns[IMGROWS * IMGCOLS];
	Glib::RefPtr<Gtk::ListStore> combobox_image_list[IMGROWS * IMGCOLS];	
};

Image_view::Image_view():
image_created(-1),
image_default("../resources/empty.png")
{
	set_border_width(5);	
	set_title("Visualizador de Imagens");

	// box principal
	add(VBox);
	VBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
	VBox.set_spacing(6);

	// menubar
	menu_refActionGroup = Gtk::ActionGroup::create();

	// file menu
	menu_refActionGroup->add(Gtk::Action::create("FileMenu",
		Gtk::Stock::FILE));

	menu_refActionGroup->add(Gtk::Action::create("FileNew",
		Gtk::Stock::NEW),
		sigc::mem_fun(*this, &Image_view::on_menu_file_new));

	// menu_refActionGroup->add(Gtk::Action::create("FileSave",
	// 	Gtk::Stock::SAVE),
	// 	sigc::mem_fun(*this, &Image_view::on_menu_file_save));

	// menu_refActionGroup->add(Gtk::Action::create("FileSaveAs",
	// 	Gtk::Stock::SAVE_AS),
	// 	sigc::mem_fun(*this, &Image_view::on_menu_file_save_as));

	menu_refActionGroup->add(Gtk::Action::create("FileQuit",
		Gtk::Stock::QUIT),
		sigc::mem_fun(*this, &Image_view::on_menu_file_quit));

	// edit
	menu_refActionGroup->add(Gtk::Action::create("EditMenu",
		Gtk::Stock::EDIT));

	menu_refCheckOne = Gtk::ToggleAction::create("HideButton",
		"Ocultar botão");
	menu_refActionGroup->add(menu_refCheckOne,
		sigc::mem_fun(*this, &Image_view::on_hide_button_image));
	menu_refCheckOne->set_active(true);

	// choices menu, radio itens
	// menu_refActionGroup->add(Gtk::Action::create("OptionsMenu",
	// 	Gtk::Stock::PROPERTIES));

	// Gtk::RadioAction::Group group_userlevel;
	// menu_refOptionOne = Gtk::RadioAction::create(group_userlevel,
	// 	"OptionOne", "One");
	// menu_refActionGroup->add(menu_refOptionOne,
	// 	sigc::mem_fun(*this, &Image_view::on_menu_option_one));
	// menu_refOptionTwo = Gtk::RadioAction::create(group_userlevel,
	// 	"OptionTwo", "Two");
	// menu_refActionGroup->add(menu_refOptionTwo,
	// 	sigc::mem_fun(*this, &Image_view::on_menu_option_two));

	// help menu
	menu_refActionGroup->add(Gtk::Action::create("HelpMenu",
		Gtk::Stock::HELP));

	menu_refActionGroup->add(Gtk::Action::create("HelpAbout",
		Gtk::Stock::ABOUT),
		sigc::mem_fun(*this, &Image_view::on_menu_help_about));

	menu_refUIManager = Gtk::UIManager::create();
	menu_refUIManager->insert_action_group(menu_refActionGroup);
	add_accel_group(menu_refUIManager->get_accel_group());

	// layout menubar
	Glib::ustring ui_report
	{
		"<ui>"
		"  <menubar name='MenuBar'>"
		"    <menu action='FileMenu'>"
		"      <menuitem action='FileNew' />"
		"      <separator/>"			
		// "      <menuitem action='FileSave' />"
		// "      <menuitem action='FileSaveAs' />"
		// "      <separator/>"
		"      <menuitem action='FileQuit'/>"
		"    </menu>"
		"    <menu action='EditMenu'>"
		"      <menuitem action='HideButton'/>"
		"    </menu>"		
		// "    <menu action='OptionsMenu'>"
		// "      <menuitem action='OptionOne'/>"
		// "      <menuitem action='OptionTwo'/>"
		// "    </menu>"
		"    <menu action='HelpMenu'>"
		"      <menuitem action='HelpAbout'/>"
		"    </menu>"
		"  </menubar>"
		"</ui>"
	};

	try {
		menu_refUIManager->add_ui_from_string(ui_report);
	} catch (const Glib::Error& ex)	{
		std::cerr << "Building menus failed: " << ex.what();
	}

	Gtk::Widget* pMenubar = menu_refUIManager->get_widget("/MenuBar");
	if (pMenubar) VBox.pack_start(*pMenubar, Gtk::PACK_SHRINK);

	// box image
	unsigned pos = 0;
	for (unsigned i = 0; i < IMGROWS; ++i)
	{
		HBox[i].set_orientation(Gtk::ORIENTATION_HORIZONTAL);
		HBox[i].set_spacing(4);

		for (unsigned j = 0; j < IMGCOLS; ++j) {

			report_terminal("Image box " + std::to_string(pos + 1)
				+ " initialized and unlocked ...");

			VBox_image[pos].set_orientation(Gtk::ORIENTATION_VERTICAL);
			VBox_image[pos].set_spacing(2);
			
			image_lock[pos] = false;
			swap_released[pos] = false;
			image[pos].set(image_default);
			if (pos == 0) image[pos].show();

			button[pos].set_label("Abrir Nova Imagem");
			button[pos].signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
				&Image_view::on_button_clicked), pos));

			combobox_image[pos].signal_changed().connect
				(sigc::bind(sigc::mem_fun
				(*this, &Image_view::on_combobox_changed), pos));

			VBox_image[pos].pack_start(image[pos], true, true);
			VBox_image[pos].pack_start(label_info[pos], true, true);
			VBox_image[pos].pack_start(button[pos], true, true);
			VBox_image[pos].pack_start(combobox_image[pos], true, true);					

			VBox_image[pos].show();
			HBox[i].pack_start(VBox_image[pos], true, true);
			pos++;			
		}

		HBox[i].show();
		VBox.pack_start(HBox[i], true, true);
	}

	VBox.show();
} // constructor

Image_view::~Image_view() {	/* destructor */ }

void Image_view::report_terminal(const std::string& src)
{
	Glib::ustring message(src);
	std::cout << message << std::endl;
}

void Image_view::report(const std::string& message)
{
	report_terminal(message);
	Gtk::MessageDialog dialog (*this, message);
	dialog.set_transient_for(*this);
	dialog.run();
}

void Image_view::update_image(const int& current_image)
{
	if (image_lock[current_image]) {
		report("Local bloqueado para troca de imagem!");
		return;
	}

	// selecionar arquivo
	report_terminal("Update Image [" + std::to_string(current_image + 1)+ "]");
	report_terminal("Load new image ...");

	Gtk::FileChooserDialog dialog("Abrir Arquivo", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);

	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_ACCEPT);
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

	// filtro de arquivos
	auto filter_image = Gtk::FileFilter::create();
	filter_image->add_pixbuf_formats();
	filter_image->set_name("Images");
	dialog.add_filter(filter_image);

	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Imgp");
	filter_text->add_mime_type("text/plain");
	dialog.add_filter(filter_text);	

	const int response = dialog.run();
	dialog.hide();

	if (response != Gtk::RESPONSE_ACCEPT) {
		report_terminal("Cancel clicked ...");
		return;
	}	

	// validar arquivo
	std::string path = dialog.get_filename();
	bool is_imgp = tools::check_filename_extension(path, "imgp");
	bool is_image = tools::check_filename_extension(path, tools::image_extension);

	if (!is_imgp && !is_image) {
			report("Extensão inválida: " + path);
			return;
	}

	// arquivo .imgp: disponibilizar combobox 
	if (is_imgp) {
		report_terminal("Load imgp file ...");

		Gtk::TreeModel::Row row;
		combobox_image_list[current_image] = Gtk::ListStore::create
			(combobox_image_columns[current_image]);
		combobox_image[current_image].set_model
			(combobox_image_list[current_image]);

		v_map = load_imgp(path);	// ler arquivo tipo texto					
		if (v_map.empty()) {
			report("Erro ao abrir arquivo.");
			return;
		}

		for (size_t i = 0; i < v_map.size(); ++i) {
			// report_terminal(v_map[i][0]	+ " => " + v_map[i][1]);
			row = *(combobox_image_list[current_image]->append());
			row[combobox_image_columns[current_image].action] = v_map[i][0];        
			row[combobox_image_columns[current_image].source] = v_map[i][1];        

			if (i == 0)
				combobox_image[current_image].set_active(row);
		}

		combobox_image[current_image].pack_start
			(combobox_image_columns[current_image].action);
		// combobox_image[current_image].pack_start
		// 	(combobox_image_columns[current_image].source);			

		button[current_image].hide();	// não permitir atualização
		combobox_image[current_image].show();

		label_info[current_image].hide();		
		// label_info[current_image].set_text(short_path(path));
		report_terminal("IMGP [" + std::to_string(current_image + 1) + "]");
	}

	if (is_image) {
		report_terminal("Load image file ...");

		image[current_image].set(path);

		if (menu_refCheckOne->get_active())
			button[current_image].hide();
		else
			button[current_image].show();

		swap_released[current_image] = true;
		combobox_image[current_image].hide();

		label_info[current_image].show();
		label_info[current_image].set_text(short_path(path));
		report_terminal("IMAGE [" + std::to_string(current_image + 1) + "]");
	}

	image[current_image].show();
	image_lock[current_image] = true;	// desbloquear somente pelo "Reload"
	report_terminal("Image box [" + std::to_string(current_image + 1)
	  + "]: lock!");
}

void Image_view::on_menu_file_new()
{
	image_created++;
	if (image_created >= IMGROWS * IMGCOLS) {
		report("Limite de imagens excedido!");
		return;
	}

	report_terminal("Create new image box ...");
	update_image(image_created);
}

void Image_view::on_menu_file_save()
{
	report_terminal("SAVE");
}

void Image_view::on_menu_file_save_as()
{
	report_terminal("SAVE AS");
}

void Image_view::on_menu_file_quit()
{
	report_terminal("WINDOW HIDE");
	hide();
}

void Image_view::on_hide_button_image()
{
	if (menu_refCheckOne->get_active()) {
		for (unsigned i = 0; i < IMGROWS * IMGCOLS; ++i) {
			if (swap_released[i])
				button[i].hide();
		}		
		report_terminal("Hide buttons.");
	} else {
		for (unsigned i = 0; i < IMGROWS * IMGCOLS; ++i) {
			if (swap_released[i])
				button[i].show();
		}		
		report_terminal("Show buttons.");
	}
}

void Image_view::on_menu_option_one()
{
	if (menu_refOptionOne->get_active())
		report_terminal("Option 1 was selected.");
	else
		report_terminal("Option 1 was deselected.");
}

void Image_view::on_menu_option_two()
{
	if (menu_refOptionTwo->get_active())
		report_terminal("Option 2 was selected.");
	else
		report_terminal("Option 2 was deselected.");
}

void Image_view::on_menu_help_about()
{
	report("Interface gráfica para\nvisualização simples de imagens.");
}

void Image_view::on_button_clicked(const int& num_button)
{
	report_terminal("Image [" + std::to_string(num_button) + "] unlocked.");
	image_lock[num_button] = false;
	update_image(num_button);
}

void Image_view::on_combobox_changed(const int& option)
{
	Gtk::TreeModel::iterator iter = combobox_image[option].get_active();
	Gtk::TreeModel::Row row = *iter;
	Glib::ustring source = image_default;

	if (!iter) return;

	if (row) {
		source = row[combobox_image_columns[option].source];
	}

	if (!tools::exist_path(source)) {
		report("Erro ao abrir arquivo!");
		return;
	}

	image[option].set(source);
	report_terminal("Image [" + std::to_string(option + 1) + "] changed!");
	report_terminal(source);
}

// reduzir tamanho da mensagem do 'path'
std::string Image_view::short_path(const std::string& path)
{
	int count(0);
	std::string out("");
	for (size_t i = path.size() - 1; i >= 0; --i) {
		if (path[i] == '/') count++;
		if (count == SHORT_PATH) break;
		out = path[i] + out;
	}
	return out;
}

// ler arquivo específico de extensão .imgp
std::vector<std::vector<std::string> >
Image_view::load_imgp (const std::string& file_imgp)
{
	std::vector<std::string> lines, word;
	std::vector<std::vector<std::string> > result {{"EMPTY"}};
	try {
		tools::load(file_imgp, lines);
		result.clear();
		for (std::string line : lines) {
			tools::split(line, word, ':');
			
			if (word.size() != 2) {
				// report_terminal("ignored line ...");
				continue;
			}

			if (word[0][0] == '#') {
				// report_terminal("ignored line ...");
				continue;				
			}

			result.push_back(word);
		}
	}
	catch(const std::exception& e) {
		report_terminal("Error Image_view::load_imgp");
		tools::error(__LINE__, "Image_view::load_imgp");
	}
	return result;
}

#endif // IMAGE_VIEW_HPP
