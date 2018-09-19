#ifndef IMAGE_VIEW_HPP
#define IMAGE_VIEW_HPP

#include "tools.hpp"

#include <gtkmm.h>
#include <iostream>

class Image_view : public Gtk::Window {

#define IMAGES 3

public:
	Image_view();
	virtual ~Image_view();

protected:
	int image_created;
	const std::string image_default = "../resources/empty.png";

	// eventos
	void on_menu_file_new();
	void on_menu_file_open();
	void on_menu_file_save();
	void on_menu_file_save_as();
	void on_menu_file_quit();
	void on_menu_choices_one();
	void on_menu_choices_two();
	void on_menu_help_about();	
	void on_button_clicked(const int& /*num button*/);
	void on_combobox_image_changed();
	void report(const std::string& /*message*/);
	void report_terminal(const std::string& /*message*/);

	// widgets
	Gtk::Box VBox;
	Gtk::Box HBox;
	Gtk::Box VBox_image[IMAGES];
	Gtk::Image image[IMAGES];    
	Gtk::Button button[IMAGES];
	Gtk::ComboBox combobox_image[IMAGES];  
	Gtk::Statusbar statusbar;

	Glib::RefPtr<Gtk::UIManager> 	menu_refUIManager;
	Glib::RefPtr<Gtk::ActionGroup> 	menu_refActionGroup;
	Glib::RefPtr<Gtk::RadioAction> 	menu_refOptionOne, menu_refOptionTwo;

	class ModelColumns : public Gtk::TreeModel::ColumnRecord {
	public:
		ModelColumns() { add(action); }
		Gtk::TreeModelColumn<Glib::ustring> action;
	};

	bool image_in_use[IMAGES];
	ModelColumns combobox_image_columns[IMAGES];
	Glib::RefPtr<Gtk::ListStore> combobox_image_list[IMAGES];
};

Image_view::Image_view():
image_created(0)
{
	// configuração inicial
	set_title("Image View [Testing]");
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
	HBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
	HBox.set_spacing(6);

	for (unsigned i = 0; i < IMAGES; ++i)
	{
		VBox_image[i].set_orientation(Gtk::ORIENTATION_VERTICAL);
		VBox_image[i].set_spacing(3);
		
		image[i].set(image_default);

		button[i].set_label("Reload file " + std::to_string(i+1));
		button[i].signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
			&Image_view::on_button_clicked), i));

		// combobox_image[i].signal....

		VBox_image[i].pack_start(image[i], true, true);
		VBox_image[i].pack_start(button[i], true, true);
		VBox_image[i].pack_start(combobox_image[i], true, true);

		if (i == image_created){
			image[i].show();
			VBox_image[i].show();
			image_in_use[i] = false;
		}

		HBox.pack_start(VBox_image[i], true, true);
		HBox.show();
	}

	VBox.pack_start(HBox, true, true);

	statusbar.show();
	VBox.pack_start(statusbar, true, true);

	VBox.show();
}

Image_view::~Image_view() {	/* destructor */ }

void Image_view::report(const std::string& message)
{
	Gtk::MessageDialog dialog (*this, message);
	dialog.set_transient_for(*this);
	dialog.run();
}

void Image_view::report_terminal(const std::string& src)
{
	Glib::ustring message(src);
	std::cout << message << std::endl;
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
	if (image_created >= IMAGES) {
		report("limit exceeded!");
		report_terminal("limit exceeded!");
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
	if (image_created >= IMAGES) {
		report("limit exceeded!");
		report_terminal("limit exceeded!");
		return;
	}

	if (image_in_use[image_created]) {
		report("Local ocupado ....\nSubstituir??");
		return;
	}

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
	bool is_image = tools::check_filename_extension(path, "png");

	if (!is_imgp && !is_image) {
			report("Invalid: " + path);
			report_terminal("Invalid: " + path);
			return;
	}

	image_in_use[image_created] = true;

	if (is_imgp) {

		std::vector<std::string> types_image { "A", "B" };

        // criando lista para o comboBox
        combobox_image_list[image_created] = Gtk::ListStore::create
        	(combobox_image_columns[image_created]);
        combobox_image[image_created].set_model(combobox_image_list[image_created]);

        Gtk::TreeModel::Row row;
        for (unsigned i = 0; i < types_image.size(); ++i) {
        	row = *(combobox_image_list[image_created]->append());
        	row[combobox_image_columns[image_created].action] = types_image[i];        
        }
        combobox_image[image_created].pack_start
        	(combobox_image_columns[image_created].action);

		image[image_created].set("../resources/tree-17.png"); // gerar outro caminho
        button[image_created].show();
		combobox_image[image_created].show();
		statusbar.push(path, image_created);
		report_terminal("IMGP OPEN");
	}

	if (is_image) {
		image[image_created].set(path);
		button[image_created].show();
		combobox_image[image_created].hide();
		statusbar.push(path, image_created);
		report_terminal("IMAGE OPEN");
    } 
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
	report("ABOUT");
	report_terminal("ABOUT");
}

void Image_view::on_button_clicked(const int& num_button)
{
	report_terminal("BUTTON " + std::to_string(num_button));
}

void Image_view::on_combobox_image_changed()
{
	report_terminal("COMBO BOX");
}

#endif // IMAGE_VIEW_HPP
