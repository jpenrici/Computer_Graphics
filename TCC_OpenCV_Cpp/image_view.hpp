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

#define IMGROWS 1
#define IMGCOLS 2

public:
	Image_view();
	virtual ~Image_view();

protected:
	const std::string image_default = "../resources/empty.png";

	int image_created;	
	std::vector<std::vector<std::string> > v_map;

	std::string str_min(const std::string& /*path*/);

	std::vector<std::vector<std::string> >
	load_imgp(const std::string& /*path imgp*/);	

	// eventos
	void on_menu_file_new();
	void on_menu_file_open();
	void on_menu_file_save();
	void on_menu_file_save_as();
	void on_menu_file_quit();
	void on_menu_choices_one();
	void on_menu_choices_two();
	void on_menu_help_about();
	void on_button_clicked(const int& /*num image*/);
	void on_combobox_image_changed(const int& /*num image*/);
	void report(const std::string& /*message*/);
	void report_terminal(const std::string& /*message*/);
	void update_box_image(const int& /*num image*/);

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

	bool image_in_use[IMGROWS * IMGCOLS];
	ModelColumns combobox_image_columns[IMGROWS * IMGCOLS];
	Glib::RefPtr<Gtk::ListStore> combobox_image_list[IMGROWS * IMGCOLS];	
};

Image_view::Image_view():
image_created(0)
{
	// configuração inicial
	set_title("Image View [ Testing ]");
	set_border_width(5);

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

	menu_refActionGroup->add(Gtk::Action::create("FileOpen",
		Gtk::Stock::OPEN),
		sigc::mem_fun(*this, &Image_view::on_menu_file_open));

	// menu_refActionGroup->add(Gtk::Action::create("FileSave",
	// 	Gtk::Stock::SAVE),
	// 	sigc::mem_fun(*this, &Image_view::on_menu_file_save));

	// menu_refActionGroup->add(Gtk::Action::create("FileSaveAs",
	// 	Gtk::Stock::SAVE_AS),
	// 	sigc::mem_fun(*this, &Image_view::on_menu_file_save_as));

	menu_refActionGroup->add(Gtk::Action::create("FileQuit",
		Gtk::Stock::QUIT),
		sigc::mem_fun(*this, &Image_view::on_menu_file_quit));

	// choices menu, radio itens
	// menu_refActionGroup->add(Gtk::Action::create("OptionsMenu",
	// 	Gtk::Stock::EXECUTE));

	// Gtk::RadioAction::Group group_userlevel;
	// menu_refOptionOne = Gtk::RadioAction::create(group_userlevel,
	// 	"OptionOne", "One");
	// menu_refActionGroup->add(menu_refOptionOne,
	// 	sigc::mem_fun(*this, &Image_view::on_menu_choices_one));
	// menu_refOptionTwo = Gtk::RadioAction::create(group_userlevel,
	// 	"OptionTwo", "Two");
	// menu_refActionGroup->add(menu_refOptionTwo,
	// 	sigc::mem_fun(*this, &Image_view::on_menu_choices_two));

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
		"      <menuitem action='FileOpen' />"
		"      <separator/>"			
		// "      <menuitem action='FileSave' />"
		// "      <menuitem action='FileSaveAs' />"
		// "      <separator/>"
		"      <menuitem action='FileQuit'/>"
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

	try
	{
		menu_refUIManager->add_ui_from_string(ui_report);
	}
	catch (const Glib::Error& ex)
	{
		std::cerr << "building menus failed: " << ex.what();
	}

	Gtk::Widget* pMenubar = menu_refUIManager->get_widget("/MenuBar");
	if (pMenubar) VBox.pack_start(*pMenubar, Gtk::PACK_SHRINK);

	// outros widgets
	unsigned pos = 0;
	for (unsigned i = 0; i < IMGROWS; ++i)
	{
		HBox[i].set_orientation(Gtk::ORIENTATION_HORIZONTAL);
		HBox[i].set_spacing(6);

		for (unsigned j = 0; j < IMGCOLS; ++j) {

			report_terminal("image box " + std::to_string(pos)
				+ " initialized ...");

			VBox_image[pos].set_orientation(Gtk::ORIENTATION_VERTICAL);
			VBox_image[pos].set_spacing(3);
			
			image[pos].set(image_default);

			button[pos].set_label("Reload file " + std::to_string(pos + 1));
			button[pos].signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
				&Image_view::on_button_clicked), pos));

			combobox_image[pos].signal_changed().connect
				(sigc::bind(sigc::mem_fun
				(*this, &Image_view::on_combobox_image_changed), pos));

			VBox_image[pos].pack_start(image[pos], true, true);
			VBox_image[pos].pack_start(button[pos], true, true);
			VBox_image[pos].pack_start(combobox_image[pos], true, true);
			VBox_image[pos].pack_start(label_info[pos], true, true);

			if (pos == image_created){
				image[pos].show();
				// button[pos].show();
				// combobox_image[pos].show();
				// label_info[pos].show();
				VBox_image[pos].show();
				image_in_use[pos] = false;
			}
			HBox[i].pack_start(VBox_image[pos], true, true);
			pos++;			
		}

		HBox[i].show();
		VBox.pack_start(HBox[i], true, true);
	}

	VBox.show();
}

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

void Image_view::update_box_image(const int& current_image)
{
	// selecionar novo arquivo
	Gtk::FileChooserDialog dialog("Open File", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);

	dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_ACCEPT);
	dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

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
		report_terminal("cancel clicked");
		return;
	}	

	// validar arquivo
	std::string path = dialog.get_filename();
	bool is_imgp = tools::check_filename_extension(path, "imgp");
	bool is_image = tools::check_filename_extension(path, tools::image_extension);

	if (!is_imgp && !is_image) {
			report("Invalid: " + path);
			return;
	}

	image_in_use[current_image] = true;

	if (is_imgp) {

		// criando lista para o comboBox
		Gtk::TreeModel::Row row;
		combobox_image_list[current_image] = Gtk::ListStore::create
			(combobox_image_columns[current_image]);
		combobox_image[current_image].set_model
			(combobox_image_list[current_image]);

		v_map = load_imgp(path);					
		if (v_map.empty()) {
			report ("File with problems.\nCould not open.");
			return;
		}

		for (size_t i = 0; i < v_map.size(); ++i) {
			report_terminal(v_map[i][0]	+ " => " + v_map[i][1]);
			row = *(combobox_image_list[current_image]->append());
			row[combobox_image_columns[current_image].action] = v_map[i][0];        
			row[combobox_image_columns[current_image].source] = v_map[i][1];        

			if (i == 0) {
				combobox_image[current_image].set_active(row); 
				image[current_image].set(v_map[i][1]);   
			}
		}

		combobox_image[current_image].pack_start
			(combobox_image_columns[current_image].action);
		// combobox_image[current_image].pack_start
		// 	(combobox_image_columns[current_image].source);			

		button[current_image].show();
		combobox_image[current_image].show();
		label_info[current_image].show();

		label_info[current_image].set_text("last read IMGP file ["
			+ std::to_string(current_image + 1) + "]: " + str_min(path));
		report_terminal("IMGP OPEN");
	}

	if (is_image) {
		image[current_image].set(path);
		button[current_image].show();
		combobox_image[current_image].hide();
		label_info[current_image].show();

		label_info[current_image].set_text("last read IMAGE file ["
			+ std::to_string(current_image + 1)	+ "]: " + str_min(path));
		report_terminal("IMAGE OPEN");
	} 	

}

void Image_view::on_menu_file_new()
{
	// checar se existe imagem para o box atual
	if (!image_in_use[image_created]) {
		report_terminal("image " + std::to_string(image_created)
			+ " is free. Open new viewer!\n");
		on_menu_file_open();		
		return;
	}

	// verificar se todos os espaços foram preenchidos
	image_created++;
	if (image_created >= IMGROWS * IMGCOLS) {
		report("limit exceeded!");
		return;
	}

	// exibir novo espaço
	image[image_created].show();
	VBox_image[image_created].show();
	image_in_use[image_created] = false;
	report_terminal("new box displayed!");

	on_menu_file_open();
}

void Image_view::on_menu_file_open()
{
	if (image_created >= IMGROWS * IMGCOLS) {
		report("limit exceeded!");
		return;
	}

	if (image_in_use[image_created]) {
		report("Click to reload image!");
		return;
	}

	update_box_image(image_created);
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

void Image_view::on_menu_choices_one()
{
	if(menu_refOptionOne->get_active())
		report_terminal("Option 1 was selected.");
	else
		report_terminal("Option 1 was deselected.");
}

void Image_view::on_menu_choices_two()
{
	if(menu_refOptionTwo->get_active())
		report_terminal("Option 2 was selected.");
	else
		report_terminal("Option 2 was deselected.");
}

void Image_view::on_menu_help_about()
{
	report("Simple Image Viewer.");
}

void Image_view::on_button_clicked(const int& num_button)
{
	image_in_use[num_button] = false;
	report_terminal("BUTTON " + std::to_string(num_button));
	update_box_image(num_button);
}

void Image_view::on_combobox_image_changed(const int& option)
{
	Gtk::TreeModel::iterator iter = combobox_image[option].get_active();
	if (iter) {
		Gtk::TreeModel::Row row = *iter;
		if (row) {
			Glib::ustring action = row[combobox_image_columns[option].action];
			Glib::ustring source = row[combobox_image_columns[option].source];

			std::cout << action << std::endl;
			std::cout << source << std::endl;

			image[option].set(source);
		}
	} else {
		std::cout << "invalid iter ..." << std::endl;
	}

	report_terminal("COMBO BOX " + std::to_string(option));
}

std::string Image_view::str_min(const std::string& path)
{
	int count(0);
	std::string out("");
	for (size_t i = path.size() - 1; i >= 0; --i) {
		if (path[i] == '/') count++;
		if (count == 4) break;
		out = path[i] + out;
	}
	return out;
}

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
				report_terminal("ignored line ...");
				continue;
			}

			if (word[0][0] == '#') {
				report_terminal("ignored line ...");
				continue;				
			}

			result.push_back(word);
		}
	}
	catch(const std::exception& e) {
		tools::error(__LINE__, "Image_view::load_imgp");
	}
	return result;
}

#endif // IMAGE_VIEW_HPP
