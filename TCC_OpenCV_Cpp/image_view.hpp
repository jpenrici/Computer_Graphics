#ifndef IMAGE_VIEW_HPP
#define IMAGE_VIEW_HPP

#include <gtkmm.h>
#include <iostream>

class ImageView : public Gtk::Window {
public:
	ImageView();
	virtual ~ImageView();

protected:
	const std::string& path_image_default = "./resources/empty.png";

    void on_menu_file_open();
    void on_menu_file_save();
    void on_menu_file_save_as();
    void on_menu_file_quit();
	void on_menu_choices_one();
	void on_menu_choices_two();
    void on_menu_help_about();	
    void on_button_1_clicked();
    void on_combobox_image_changed();	

    Gtk::Box VBox, HBox_1, HBox_2;
    Gtk::Image image_1, image_2;    
    Gtk::Button button_1;
    Gtk::ComboBox combobox_image;   
    Gtk::Statusbar statusbar;

    Glib::RefPtr<Gtk::UIManager> menu_refUIManager;
	Glib::RefPtr<Gtk::ActionGroup> menu_refActionGroup;
	Glib::RefPtr<Gtk::RadioAction> menu_refOptionOne, menu_refOptionTwo;

    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() { add(action); }
        Gtk::TreeModelColumn<Glib::ustring> action;
    };

    bool flag_combobox_image;
    ModelColumns combobox_image_columns;
    Glib::RefPtr<Gtk::ListStore> combobox_image_list;
};

ImageView::ImageView():
	button_1("Run", true),
	flag_combobox_image(false)
{
	// configuração inicial da janela
	set_title("Image View");
	set_border_width(5);
	set_default_size(500, 500);

	// adiciona box principal
	add(VBox);
	VBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
	VBox.set_spacing(6);

	// criar menus 
	menu_refActionGroup = Gtk::ActionGroup::create();

	// file menu
	menu_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));
	menu_refActionGroup->add(Gtk::Action::create("FileOpen",
		Gtk::Stock::OPEN),
		sigc::mem_fun(*this, &ImageView::on_menu_file_open));
	menu_refActionGroup->add(Gtk::Action::create("FileSave",
		Gtk::Stock::SAVE),
		sigc::mem_fun(*this, &ImageView::on_menu_file_save));
	menu_refActionGroup->add(Gtk::Action::create("FileSaveAs",
		Gtk::Stock::SAVE_AS),
		sigc::mem_fun(*this, &ImageView::on_menu_file_save_as));
	menu_refActionGroup->add(Gtk::Action::create("FileQuit",
		Gtk::Stock::QUIT),
		sigc::mem_fun(*this, &ImageView::on_menu_file_quit));

	// choices menu, radio items
	menu_refActionGroup->add(Gtk::Action::create("OptionsMenu", "Options"));
	Gtk::RadioAction::Group group_userlevel;
	menu_refOptionOne = Gtk::RadioAction::create(group_userlevel,
		"OptionOne", "One");
	menu_refActionGroup->add(menu_refOptionOne,
			sigc::mem_fun(*this, &ImageView::on_menu_choices_one));
	menu_refOptionTwo = Gtk::RadioAction::create(group_userlevel,
		"OptionTwo", "Two");
	menu_refActionGroup->add(menu_refOptionTwo,
			sigc::mem_fun(*this, &ImageView::on_menu_choices_two));

	// help menu:
	menu_refActionGroup->add(Gtk::Action::create("HelpMenu", "Help"));
	menu_refActionGroup->add(Gtk::Action::create("HelpAbout",
		Gtk::Stock::ABOUT),
		sigc::mem_fun(*this, &ImageView::on_menu_help_about));

	menu_refUIManager = Gtk::UIManager::create();
	menu_refUIManager->insert_action_group(menu_refActionGroup);
	add_accel_group(menu_refUIManager->get_accel_group());

	// layout do menubar
	Glib::ustring ui_info =
			"<ui>"
			"  <menubar name='MenuBar'>"
			"    <menu action='FileMenu'>"
			"      <menuitem action='FileOpen' />"
			"      <separator/>"			
			"      <menuitem action='FileSave' />"
			"      <menuitem action='FileSaveAs' />"
			"      <separator/>"
			"      <menuitem action='FileQuit'/>"
			"    </menu>"
			"    <menu action='OptionsMenu'>"
			"      <menuitem action='OptionOne'/>"
			"      <menuitem action='OptionTwo'/>"
			"    </menu>"
			"    <menu action='HelpMenu'>"
			"      <menuitem action='HelpAbout'/>"
			"    </menu>"
			"  </menubar>"
			"</ui>";

	try
	{
		menu_refUIManager->add_ui_from_string(ui_info);
	}
	catch (const Glib::Error& ex)
	{
		std::cerr << "building menus failed: " << ex.what();
	}

	Gtk::Widget* pMenubar = menu_refUIManager->get_widget("/MenuBar");
	if (pMenubar) VBox.pack_start(*pMenubar, Gtk::PACK_SHRINK);

	// outros widget
	image_1.set(path_image_default);
	image_2.set(path_image_default);

	HBox_1.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
	HBox_1.set_spacing(6);
	HBox_1.pack_start(image_1, true, true);
	HBox_1.pack_start(image_2, true, true);

	button_1.signal_clicked().connect(sigc::mem_fun(*this,
		&ImageView::on_button_1_clicked));

	HBox_2.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
	HBox_2.set_spacing(6);
	HBox_2.pack_start(button_1, true, true);
	HBox_2.pack_start(combobox_image, true, true);

	VBox.pack_start(HBox_1, true, true);
	VBox.pack_start(HBox_2, true, true);
	VBox.pack_start(statusbar, true, true);

	show_all_children();
}

ImageView::~ImageView(){}

void ImageView::on_menu_file_open()
{
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

	// switch (response) {
	// 	case Gtk::RESPONSE_ACCEPT:
	// 		image_1.set(dialog.get_filename());
	// 		// image_2.set(dialog.get_filename());
	// 		break;
	// 	default:
	// 		break;
	// }

	std::cout << dialog.get_filename() << std::endl;

    std::vector<std::string> types_image { "A", "B" };
    std::cout << "OPEN\n";

    if (!flag_combobox_image) {
        flag_combobox_image = true;	// carregar lista somente para uma imagem

        // criando lista para o comboBox
        combobox_image_list = Gtk::ListStore::create(combobox_image_columns);
        combobox_image.set_model(combobox_image_list);

        Gtk::TreeModel::Row row;
        for (unsigned i = 0; i < types_image.size(); ++i) {
            row = *(combobox_image_list->append());
            row[combobox_image_columns.action] = types_image[i];        
        }
        combobox_image.pack_start(combobox_image_columns.action);

    } else {
        std::cout << "lista aberta!\n";
    }  
}

void ImageView::on_menu_file_save()
{
    std::cout << "SAVE\n";
}

void ImageView::on_menu_file_save_as()
{
    std::cout << "SAVE AS\n";
}

void ImageView::on_menu_file_quit(){
	hide();
}

void ImageView::on_menu_choices_one(){
	Glib::ustring message;
	if(menu_refOptionOne->get_active())
		message = "Option 1 was selected.";
	else
		message = "Option 1 was deselected.";

	std::cout << message << std::endl;
}

void ImageView::on_menu_choices_two(){
	Glib::ustring message;
	if(menu_refOptionTwo->get_active())
		message = "Option 2 was selected.";
	else
		message = "Option 2 was deselected.";

	std::cout << message << std::endl;
}

void ImageView::on_menu_help_about()
{
    std::cout << "ABOUT\n";
    Gtk::MessageDialog dialog(*this, "This is an INFO MessageDialog");
    dialog.set_transient_for(*this);
    dialog.run();
}

void ImageView::on_button_1_clicked()
{
	std::cout << "BUTTON\n";
}

void ImageView::on_combobox_image_changed()
{
    std::cout << "COMBO BOX\n";
}


#endif // IMAGE_VIEW_HPP
