/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "gconf_callbacks.h"
#include "gconf_interface.h"
#include "gconf_support.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget *
create_main_wnd (void)
{
  GtkWidget *main_wnd;
  GtkWidget *vbox1;
  GtkWidget *menubar1;
  GtkWidget *file1;
  GtkWidget *file1_menu;
  GtkWidget *load1;
  GtkWidget *image27;
  GtkWidget *save1;
  GtkWidget *image28;
  GtkWidget *separator1;
  GtkWidget *quit1;
  GtkWidget *image30;
  GtkWidget *options1;
  GtkWidget *options1_menu;
  GtkWidget *show_name1;
  GtkWidget *show_range1;
  GtkWidget *show_data1;
  GtkWidget *separator2;
  GtkWidget *show_all_options1;
  GtkWidget *show_debug_info1;
  GtkWidget *help1;
  GtkWidget *help1_menu;
  GtkWidget *introduction1;
  GtkWidget *image31;
  GtkWidget *about1;
  GtkWidget *image32;
  GtkWidget *license1;
  GtkWidget *image33;
  GtkWidget *handlebox1;
  GtkWidget *toolbar1;
  GtkIconSize tmp_toolbar_icon_size;
  GtkWidget *toolitem1;
  GtkWidget *button1;
  GtkWidget *alignment11;
  GtkWidget *hbox11;
  GtkWidget *image44;
  GtkWidget *label11;
  GtkWidget *toolitem2;
  GtkWidget *vseparator1;
  GtkWidget *toolitem3;
  GtkWidget *button2;
  GtkWidget *alignment2;
  GtkWidget *hbox2;
  GtkWidget *image35;
  GtkWidget *label2;
  GtkWidget *toolitem4;
  GtkWidget *button3;
  GtkWidget *alignment4;
  GtkWidget *hbox4;
  GtkWidget *image37;
  GtkWidget *label4;
  GtkWidget *toolitem5;
  GtkWidget *vseparator2;
  GtkWidget *toolitem6;
  GtkWidget *button4;
  GtkWidget *alignment6;
  GtkWidget *hbox6;
  GtkWidget *image39;
  GtkWidget *label6;
  GtkWidget *toolitem7;
  GtkWidget *button5;
  GtkWidget *alignment7;
  GtkWidget *hbox7;
  GtkWidget *image40;
  GtkWidget *label7;
  GtkWidget *toolitem8;
  GtkWidget *button6;
  GtkWidget *alignment8;
  GtkWidget *hbox8;
  GtkWidget *image41;
  GtkWidget *label8;
  GtkWidget *toolitem9;
  GtkWidget *vseparator3;
  GtkWidget *toolitem10;
  GtkWidget *button7;
  GtkWidget *alignment9;
  GtkWidget *hbox9;
  GtkWidget *image42;
  GtkWidget *label9;
  GtkWidget *toolitem11;
  GtkWidget *button8;
  GtkWidget *alignment10;
  GtkWidget *hbox10;
  GtkWidget *image43;
  GtkWidget *label10;
  GtkWidget *hpaned1;
  GtkWidget *scrolledwindow1;
  GtkWidget *treeview1;
  GtkWidget *vpaned1;
  GtkWidget *scrolledwindow2;
  GtkWidget *treeview2;
  GtkWidget *scrolledwindow3;
  GtkWidget *textview3;
  GtkAccelGroup *accel_group;
  GtkTooltips *tooltips;

  tooltips = gtk_tooltips_new ();

  accel_group = gtk_accel_group_new ();

  main_wnd = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (main_wnd), _("Gtk GNUnet Configurator"));
  gtk_window_set_default_size (GTK_WINDOW (main_wnd), 640, 480);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (main_wnd), vbox1);

  menubar1 = gtk_menu_bar_new ();
  gtk_widget_show (menubar1);
  gtk_box_pack_start (GTK_BOX (vbox1), menubar1, FALSE, FALSE, 0);

  file1 = gtk_menu_item_new_with_mnemonic (_("_File"));
  gtk_widget_show (file1);
  gtk_container_add (GTK_CONTAINER (menubar1), file1);

  file1_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (file1), file1_menu);

  load1 = gtk_image_menu_item_new_with_mnemonic (_("_Load"));
  gtk_widget_show (load1);
  gtk_container_add (GTK_CONTAINER (file1_menu), load1);
  gtk_tooltips_set_tip (tooltips, load1, _("Load a config file"), NULL);
  gtk_widget_add_accelerator (load1, "activate", accel_group,
			      GDK_L, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  image27 = gtk_image_new_from_stock ("gtk-open", GTK_ICON_SIZE_MENU);
  gtk_widget_show (image27);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (load1), image27);

  save1 = gtk_image_menu_item_new_with_mnemonic (_("_Save"));
  gtk_widget_show (save1);
  gtk_container_add (GTK_CONTAINER (file1_menu), save1);
  gtk_tooltips_set_tip (tooltips, save1, _("Save the config in .config"),
			NULL);
  gtk_widget_add_accelerator (save1, "activate", accel_group, GDK_S,
			      GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  image28 = gtk_image_new_from_stock ("gtk-save", GTK_ICON_SIZE_MENU);
  gtk_widget_show (image28);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (save1), image28);

  separator1 = gtk_menu_item_new ();
  gtk_widget_show (separator1);
  gtk_container_add (GTK_CONTAINER (file1_menu), separator1);
  gtk_widget_set_sensitive (separator1, FALSE);

  quit1 = gtk_image_menu_item_new_with_mnemonic (_("_Quit"));
  gtk_widget_show (quit1);
  gtk_container_add (GTK_CONTAINER (file1_menu), quit1);
  gtk_widget_add_accelerator (quit1, "activate", accel_group,
			      GDK_Q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  image30 = gtk_image_new_from_stock ("gtk-quit", GTK_ICON_SIZE_MENU);
  gtk_widget_show (image30);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (quit1), image30);

  options1 = gtk_menu_item_new_with_mnemonic (_("_Options"));
  gtk_widget_show (options1);
  gtk_container_add (GTK_CONTAINER (menubar1), options1);

  options1_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (options1), options1_menu);

  show_name1 = gtk_check_menu_item_new_with_mnemonic (_("Show _name"));
  gtk_widget_show (show_name1);
  gtk_container_add (GTK_CONTAINER (options1_menu), show_name1);
  gtk_tooltips_set_tip (tooltips, show_name1, _("Show name"), NULL);

  show_range1 = gtk_check_menu_item_new_with_mnemonic (_("Show _range"));
  gtk_widget_show (show_range1);
  gtk_container_add (GTK_CONTAINER (options1_menu), show_range1);
  gtk_tooltips_set_tip (tooltips, show_range1, _("Show range (Y/M/N)"), NULL);

  show_data1 = gtk_check_menu_item_new_with_mnemonic (_("Show _data"));
  gtk_widget_show (show_data1);
  gtk_container_add (GTK_CONTAINER (options1_menu), show_data1);
  gtk_tooltips_set_tip (tooltips, show_data1, _("Show value of the option"),
			NULL);

  separator2 = gtk_menu_item_new ();
  gtk_widget_show (separator2);
  gtk_container_add (GTK_CONTAINER (options1_menu), separator2);
  gtk_widget_set_sensitive (separator2, FALSE);

  show_all_options1 =
    gtk_check_menu_item_new_with_mnemonic (_("Show all _options"));
  gtk_widget_show (show_all_options1);
  gtk_container_add (GTK_CONTAINER (options1_menu), show_all_options1);
  gtk_tooltips_set_tip (tooltips, show_all_options1, _("Show all options"),
			NULL);

  show_debug_info1 =
    gtk_check_menu_item_new_with_mnemonic (_("Show _debug info"));
  gtk_widget_show (show_debug_info1);
  gtk_container_add (GTK_CONTAINER (options1_menu), show_debug_info1);
  gtk_tooltips_set_tip (tooltips, show_debug_info1, _("Show masked options"),
			NULL);

  help1 = gtk_menu_item_new_with_mnemonic (_("_Help"));
  gtk_widget_show (help1);
  gtk_container_add (GTK_CONTAINER (menubar1), help1);

  help1_menu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (help1), help1_menu);

  introduction1 = gtk_image_menu_item_new_with_mnemonic (_("_Introduction"));
  gtk_widget_show (introduction1);
  gtk_container_add (GTK_CONTAINER (help1_menu), introduction1);
  gtk_widget_add_accelerator (introduction1, "activate", accel_group,
			      GDK_I, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  image31 =
    gtk_image_new_from_stock ("gtk-dialog-question", GTK_ICON_SIZE_MENU);
  gtk_widget_show (image31);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (introduction1),
				 image31);

  about1 = gtk_image_menu_item_new_with_mnemonic (_("_About"));
  gtk_widget_show (about1);
  gtk_container_add (GTK_CONTAINER (help1_menu), about1);
  gtk_widget_add_accelerator (about1, "activate", accel_group,
			      GDK_A, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

  image32 = gtk_image_new_from_stock ("gtk-properties", GTK_ICON_SIZE_MENU);
  gtk_widget_show (image32);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (about1), image32);

  license1 = gtk_image_menu_item_new_with_mnemonic (_("_License"));
  gtk_widget_show (license1);
  gtk_container_add (GTK_CONTAINER (help1_menu), license1);

  image33 = gtk_image_new_from_stock ("gtk-justify-fill", GTK_ICON_SIZE_MENU);
  gtk_widget_show (image33);
  gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (license1), image33);

  handlebox1 = gtk_handle_box_new ();
  gtk_widget_show (handlebox1);
  gtk_box_pack_start (GTK_BOX (vbox1), handlebox1, FALSE, FALSE, 0);

  toolbar1 = gtk_toolbar_new ();
  gtk_widget_show (toolbar1);
  gtk_container_add (GTK_CONTAINER (handlebox1), toolbar1);
  gtk_toolbar_set_style (GTK_TOOLBAR (toolbar1), GTK_TOOLBAR_BOTH);
  tmp_toolbar_icon_size = gtk_toolbar_get_icon_size (GTK_TOOLBAR (toolbar1));

  toolitem1 = (GtkWidget *) gtk_tool_item_new ();
  gtk_widget_show (toolitem1);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem1);

  button1 = gtk_button_new ();
  gtk_widget_show (button1);
  gtk_container_add (GTK_CONTAINER (toolitem1), button1);
  GTK_WIDGET_UNSET_FLAGS (button1, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button1,
			_("Goes up of one level (single view)"), NULL);

  alignment11 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment11);
  gtk_container_add (GTK_CONTAINER (button1), alignment11);

  hbox11 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox11);
  gtk_container_add (GTK_CONTAINER (alignment11), hbox11);

  image44 = gtk_image_new_from_stock ("gtk-go-up", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image44);
  gtk_box_pack_start (GTK_BOX (hbox11), image44, FALSE, FALSE, 0);

  label11 = gtk_label_new_with_mnemonic (_("Up"));
  gtk_widget_show (label11);
  gtk_box_pack_start (GTK_BOX (hbox11), label11, FALSE, FALSE, 0);

  toolitem2 = (GtkWidget *) gtk_tool_item_new ();
  gtk_widget_show (toolitem2);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem2);

  vseparator1 = gtk_vseparator_new ();
  gtk_widget_show (vseparator1);
  gtk_container_add (GTK_CONTAINER (toolitem2), vseparator1);

  toolitem3 = (GtkWidget *) gtk_tool_item_new ();
  gtk_widget_show (toolitem3);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem3);

  button2 = gtk_button_new ();
  gtk_widget_show (button2);
  gtk_container_add (GTK_CONTAINER (toolitem3), button2);
  GTK_WIDGET_UNSET_FLAGS (button2, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button2, _("Load a config file"), NULL);

  alignment2 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment2);
  gtk_container_add (GTK_CONTAINER (button2), alignment2);

  hbox2 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox2);
  gtk_container_add (GTK_CONTAINER (alignment2), hbox2);

  image35 = gtk_image_new_from_stock ("gtk-open", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image35);
  gtk_box_pack_start (GTK_BOX (hbox2), image35, FALSE, FALSE, 0);

  label2 = gtk_label_new_with_mnemonic (_("Load"));
  gtk_widget_show (label2);
  gtk_box_pack_start (GTK_BOX (hbox2), label2, FALSE, FALSE, 0);

  toolitem4 = (GtkWidget *) gtk_tool_item_new ();
  gtk_widget_show (toolitem4);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem4);

  button3 = gtk_button_new ();
  gtk_widget_show (button3);
  gtk_container_add (GTK_CONTAINER (toolitem4), button3);
  GTK_WIDGET_UNSET_FLAGS (button3, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button3, _("Save a config file"), NULL);

  alignment4 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment4);
  gtk_container_add (GTK_CONTAINER (button3), alignment4);

  hbox4 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox4);
  gtk_container_add (GTK_CONTAINER (alignment4), hbox4);

  image37 = gtk_image_new_from_stock ("gtk-save", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image37);
  gtk_box_pack_start (GTK_BOX (hbox4), image37, FALSE, FALSE, 0);

  label4 = gtk_label_new_with_mnemonic (_("Save"));
  gtk_widget_show (label4);
  gtk_box_pack_start (GTK_BOX (hbox4), label4, FALSE, FALSE, 0);

  toolitem5 = (GtkWidget *) gtk_tool_item_new ();
  gtk_widget_show (toolitem5);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem5);

  vseparator2 = gtk_vseparator_new ();
  gtk_widget_show (vseparator2);
  gtk_container_add (GTK_CONTAINER (toolitem5), vseparator2);

  toolitem6 = (GtkWidget *) gtk_tool_item_new ();
  gtk_widget_show (toolitem6);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem6);

  button4 = gtk_button_new ();
  gtk_widget_show (button4);
  gtk_container_add (GTK_CONTAINER (toolitem6), button4);
  GTK_WIDGET_UNSET_FLAGS (button4, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button4, _("Single view"), NULL);

  alignment6 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment6);
  gtk_container_add (GTK_CONTAINER (button4), alignment6);

  hbox6 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox6);
  gtk_container_add (GTK_CONTAINER (alignment6), hbox6);

  image39 =
    gtk_image_new_from_stock ("gtk-justify-fill", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image39);
  gtk_box_pack_start (GTK_BOX (hbox6), image39, FALSE, FALSE, 0);

  label6 = gtk_label_new_with_mnemonic (_("Single"));
  gtk_widget_show (label6);
  gtk_box_pack_start (GTK_BOX (hbox6), label6, FALSE, FALSE, 0);

  toolitem7 = (GtkWidget *) gtk_tool_item_new ();
  gtk_widget_show (toolitem7);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem7);

  button5 = gtk_button_new ();
  gtk_widget_show (button5);
  gtk_container_add (GTK_CONTAINER (toolitem7), button5);
  GTK_WIDGET_UNSET_FLAGS (button5, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button5, _("Split view"), NULL);

  alignment7 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment7);
  gtk_container_add (GTK_CONTAINER (button5), alignment7);

  hbox7 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox7);
  gtk_container_add (GTK_CONTAINER (alignment7), hbox7);

  image40 =
    gtk_image_new_from_stock ("gtk-justify-fill", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image40);
  gtk_box_pack_start (GTK_BOX (hbox7), image40, FALSE, FALSE, 0);

  label7 = gtk_label_new_with_mnemonic (_("Split"));
  gtk_widget_show (label7);
  gtk_box_pack_start (GTK_BOX (hbox7), label7, FALSE, FALSE, 0);

  toolitem8 = (GtkWidget *) gtk_tool_item_new ();
  gtk_widget_show (toolitem8);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem8);

  button6 = gtk_button_new ();
  gtk_widget_show (button6);
  gtk_container_add (GTK_CONTAINER (toolitem8), button6);
  GTK_WIDGET_UNSET_FLAGS (button6, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button6, _("Full view"), NULL);

  alignment8 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment8);
  gtk_container_add (GTK_CONTAINER (button6), alignment8);

  hbox8 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox8);
  gtk_container_add (GTK_CONTAINER (alignment8), hbox8);

  image41 =
    gtk_image_new_from_stock ("gtk-justify-fill", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image41);
  gtk_box_pack_start (GTK_BOX (hbox8), image41, FALSE, FALSE, 0);

  label8 = gtk_label_new_with_mnemonic (_("Full"));
  gtk_widget_show (label8);
  gtk_box_pack_start (GTK_BOX (hbox8), label8, FALSE, FALSE, 0);

  toolitem9 = (GtkWidget *) gtk_tool_item_new ();
  gtk_widget_show (toolitem9);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem9);

  vseparator3 = gtk_vseparator_new ();
  gtk_widget_show (vseparator3);
  gtk_container_add (GTK_CONTAINER (toolitem9), vseparator3);

  toolitem10 = (GtkWidget *) gtk_tool_item_new ();
  gtk_widget_show (toolitem10);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem10);

  button7 = gtk_button_new ();
  gtk_widget_show (button7);
  gtk_container_add (GTK_CONTAINER (toolitem10), button7);
  GTK_WIDGET_UNSET_FLAGS (button7, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button7,
			_("Collapse the whole tree in the right frame"),
			NULL);

  alignment9 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment9);
  gtk_container_add (GTK_CONTAINER (button7), alignment9);

  hbox9 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox9);
  gtk_container_add (GTK_CONTAINER (alignment9), hbox9);

  image42 = gtk_image_new_from_stock ("gtk-remove", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image42);
  gtk_box_pack_start (GTK_BOX (hbox9), image42, FALSE, FALSE, 0);

  label9 = gtk_label_new_with_mnemonic (_("Collapse"));
  gtk_widget_show (label9);
  gtk_box_pack_start (GTK_BOX (hbox9), label9, FALSE, FALSE, 0);

  toolitem11 = (GtkWidget *) gtk_tool_item_new ();
  gtk_widget_show (toolitem11);
  gtk_container_add (GTK_CONTAINER (toolbar1), toolitem11);

  button8 = gtk_button_new ();
  gtk_widget_show (button8);
  gtk_container_add (GTK_CONTAINER (toolitem11), button8);
  GTK_WIDGET_UNSET_FLAGS (button8, GTK_CAN_FOCUS);
  gtk_tooltips_set_tip (tooltips, button8,
			_("Expand the whole tree in the right frame"), NULL);

  alignment10 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment10);
  gtk_container_add (GTK_CONTAINER (button8), alignment10);

  hbox10 = gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox10);
  gtk_container_add (GTK_CONTAINER (alignment10), hbox10);

  image43 = gtk_image_new_from_stock ("gtk-add", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image43);
  gtk_box_pack_start (GTK_BOX (hbox10), image43, FALSE, FALSE, 0);

  label10 = gtk_label_new_with_mnemonic (_("Expand"));
  gtk_widget_show (label10);
  gtk_box_pack_start (GTK_BOX (hbox10), label10, FALSE, FALSE, 0);

  hpaned1 = gtk_hpaned_new ();
  gtk_widget_show (hpaned1);
  gtk_box_pack_start (GTK_BOX (vbox1), hpaned1, TRUE, TRUE, 0);
  gtk_widget_set_size_request (hpaned1, 1, -1);
  gtk_paned_set_position (GTK_PANED (hpaned1), 0);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow1);
  gtk_paned_pack1 (GTK_PANED (hpaned1), scrolledwindow1, FALSE, TRUE);
  GTK_WIDGET_UNSET_FLAGS (scrolledwindow1, GTK_CAN_FOCUS);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow1),
				       GTK_SHADOW_IN);

  treeview1 = gtk_tree_view_new ();
  gtk_widget_show (treeview1);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), treeview1);

  vpaned1 = gtk_vpaned_new ();
  gtk_widget_show (vpaned1);
  gtk_paned_pack2 (GTK_PANED (hpaned1), vpaned1, TRUE, TRUE);
  gtk_paned_set_position (GTK_PANED (vpaned1), 0);

  scrolledwindow2 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow2);
  gtk_paned_pack1 (GTK_PANED (vpaned1), scrolledwindow2, FALSE, TRUE);
  GTK_WIDGET_UNSET_FLAGS (scrolledwindow2, GTK_CAN_FOCUS);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow2),
				       GTK_SHADOW_IN);

  treeview2 = gtk_tree_view_new ();
  gtk_widget_show (treeview2);
  gtk_container_add (GTK_CONTAINER (scrolledwindow2), treeview2);

  scrolledwindow3 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow3);
  gtk_paned_pack2 (GTK_PANED (vpaned1), scrolledwindow3, TRUE, TRUE);
  GTK_WIDGET_UNSET_FLAGS (scrolledwindow3, GTK_CAN_FOCUS);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow3),
				  GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow3),
				       GTK_SHADOW_IN);

  textview3 = gtk_text_view_new ();
  gtk_widget_show (textview3);
  gtk_container_add (GTK_CONTAINER (scrolledwindow3), textview3);
  gtk_text_view_set_editable (GTK_TEXT_VIEW (textview3), FALSE);
  gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (textview3), GTK_WRAP_WORD);
  gtk_text_buffer_set_text (gtk_text_view_get_buffer
			    (GTK_TEXT_VIEW (textview3)),
			    _
			    ("Sorry, no help available for this option yet."),
			    -1);

  g_signal_connect_swapped ((gpointer) main_wnd, "destroy",
			    G_CALLBACK (on_window1_destroy),
			    GTK_OBJECT (main_wnd));
  g_signal_connect_swapped ((gpointer) main_wnd, "size_request",
			    G_CALLBACK (on_window1_size_request),
			    GTK_OBJECT (vpaned1));
  g_signal_connect_swapped ((gpointer) main_wnd, "delete_event",
			    G_CALLBACK (on_window1_delete_event),
			    GTK_OBJECT (main_wnd));
  g_signal_connect ((gpointer) load1, "activate",
		    G_CALLBACK (on_load1_activate), NULL);
  g_signal_connect ((gpointer) save1, "activate",
		    G_CALLBACK (on_save1_activate), NULL);
  g_signal_connect ((gpointer) quit1, "activate",
		    G_CALLBACK (on_quit1_activate), NULL);
  g_signal_connect ((gpointer) show_name1, "activate",
		    G_CALLBACK (on_show_name1_activate), NULL);
  g_signal_connect ((gpointer) show_range1, "activate",
		    G_CALLBACK (on_show_range1_activate), NULL);
  g_signal_connect ((gpointer) show_data1, "activate",
		    G_CALLBACK (on_show_data1_activate), NULL);
  g_signal_connect ((gpointer) show_all_options1, "activate",
		    G_CALLBACK (on_show_all_options1_activate), NULL);
  g_signal_connect ((gpointer) show_debug_info1, "activate",
		    G_CALLBACK (on_show_debug_info1_activate), NULL);
  g_signal_connect ((gpointer) introduction1, "activate",
		    G_CALLBACK (on_introduction1_activate), NULL);
  g_signal_connect ((gpointer) about1, "activate",
		    G_CALLBACK (on_about1_activate), NULL);
  g_signal_connect ((gpointer) license1, "activate",
		    G_CALLBACK (on_license1_activate), NULL);
  g_signal_connect ((gpointer) button1, "pressed",
		    G_CALLBACK (on_back_pressed), NULL);
  g_signal_connect ((gpointer) button2, "pressed",
		    G_CALLBACK (on_load_pressed), NULL);
  g_signal_connect ((gpointer) button3, "pressed",
		    G_CALLBACK (on_save_pressed), NULL);
  g_signal_connect ((gpointer) button4, "clicked",
		    G_CALLBACK (on_single_clicked), NULL);
  g_signal_connect ((gpointer) button5, "clicked",
		    G_CALLBACK (on_split_clicked), NULL);
  g_signal_connect ((gpointer) button6, "clicked",
		    G_CALLBACK (on_full_clicked), NULL);
  g_signal_connect ((gpointer) button7, "pressed",
		    G_CALLBACK (on_collapse_pressed), NULL);
  g_signal_connect ((gpointer) button8, "pressed",
		    G_CALLBACK (on_expand_pressed), NULL);
  g_signal_connect ((gpointer) treeview1, "cursor_changed",
		    G_CALLBACK (on_treeview2_cursor_changed), NULL);
  g_signal_connect ((gpointer) treeview1, "button_press_event",
		    G_CALLBACK (on_treeview1_button_press_event), NULL);
  g_signal_connect ((gpointer) treeview1, "key_press_event",
		    G_CALLBACK (on_treeview2_key_press_event), NULL);
  g_signal_connect ((gpointer) treeview2, "cursor_changed",
		    G_CALLBACK (on_treeview2_cursor_changed), NULL);
  g_signal_connect ((gpointer) treeview2, "button_press_event",
		    G_CALLBACK (on_treeview2_button_press_event), NULL);
  g_signal_connect ((gpointer) treeview2, "key_press_event",
		    G_CALLBACK (on_treeview2_key_press_event), NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (main_wnd, main_wnd, "main_wnd");
  GLADE_HOOKUP_OBJECT (main_wnd, vbox1, "vbox1");
  GLADE_HOOKUP_OBJECT (main_wnd, menubar1, "menubar1");
  GLADE_HOOKUP_OBJECT (main_wnd, file1, "file1");
  GLADE_HOOKUP_OBJECT (main_wnd, file1_menu, "file1_menu");
  GLADE_HOOKUP_OBJECT (main_wnd, load1, "load1");
  GLADE_HOOKUP_OBJECT (main_wnd, image27, "image27");
  GLADE_HOOKUP_OBJECT (main_wnd, save1, "save1");
  GLADE_HOOKUP_OBJECT (main_wnd, image28, "image28");
  GLADE_HOOKUP_OBJECT (main_wnd, separator1, "separator1");
  GLADE_HOOKUP_OBJECT (main_wnd, quit1, "quit1");
  GLADE_HOOKUP_OBJECT (main_wnd, image30, "image30");
  GLADE_HOOKUP_OBJECT (main_wnd, options1, "options1");
  GLADE_HOOKUP_OBJECT (main_wnd, options1_menu, "options1_menu");
  GLADE_HOOKUP_OBJECT (main_wnd, show_name1, "show_name1");
  GLADE_HOOKUP_OBJECT (main_wnd, show_range1, "show_range1");
  GLADE_HOOKUP_OBJECT (main_wnd, show_data1, "show_data1");
  GLADE_HOOKUP_OBJECT (main_wnd, separator2, "separator2");
  GLADE_HOOKUP_OBJECT (main_wnd, show_all_options1, "show_all_options1");
  GLADE_HOOKUP_OBJECT (main_wnd, show_debug_info1, "show_debug_info1");
  GLADE_HOOKUP_OBJECT (main_wnd, help1, "help1");
  GLADE_HOOKUP_OBJECT (main_wnd, help1_menu, "help1_menu");
  GLADE_HOOKUP_OBJECT (main_wnd, introduction1, "introduction1");
  GLADE_HOOKUP_OBJECT (main_wnd, image31, "image31");
  GLADE_HOOKUP_OBJECT (main_wnd, about1, "about1");
  GLADE_HOOKUP_OBJECT (main_wnd, image32, "image32");
  GLADE_HOOKUP_OBJECT (main_wnd, license1, "license1");
  GLADE_HOOKUP_OBJECT (main_wnd, image33, "image33");
  GLADE_HOOKUP_OBJECT (main_wnd, handlebox1, "handlebox1");
  GLADE_HOOKUP_OBJECT (main_wnd, toolbar1, "toolbar1");
  GLADE_HOOKUP_OBJECT (main_wnd, toolitem1, "toolitem1");
  GLADE_HOOKUP_OBJECT (main_wnd, button1, "button1");
  GLADE_HOOKUP_OBJECT (main_wnd, alignment11, "alignment11");
  GLADE_HOOKUP_OBJECT (main_wnd, hbox11, "hbox11");
  GLADE_HOOKUP_OBJECT (main_wnd, image44, "image44");
  GLADE_HOOKUP_OBJECT (main_wnd, label11, "label11");
  GLADE_HOOKUP_OBJECT (main_wnd, toolitem2, "toolitem2");
  GLADE_HOOKUP_OBJECT (main_wnd, vseparator1, "vseparator1");
  GLADE_HOOKUP_OBJECT (main_wnd, toolitem3, "toolitem3");
  GLADE_HOOKUP_OBJECT (main_wnd, button2, "button2");
  GLADE_HOOKUP_OBJECT (main_wnd, alignment2, "alignment2");
  GLADE_HOOKUP_OBJECT (main_wnd, hbox2, "hbox2");
  GLADE_HOOKUP_OBJECT (main_wnd, image35, "image35");
  GLADE_HOOKUP_OBJECT (main_wnd, label2, "label2");
  GLADE_HOOKUP_OBJECT (main_wnd, toolitem4, "toolitem4");
  GLADE_HOOKUP_OBJECT (main_wnd, button3, "button3");
  GLADE_HOOKUP_OBJECT (main_wnd, alignment4, "alignment4");
  GLADE_HOOKUP_OBJECT (main_wnd, hbox4, "hbox4");
  GLADE_HOOKUP_OBJECT (main_wnd, image37, "image37");
  GLADE_HOOKUP_OBJECT (main_wnd, label4, "label4");
  GLADE_HOOKUP_OBJECT (main_wnd, toolitem5, "toolitem5");
  GLADE_HOOKUP_OBJECT (main_wnd, vseparator2, "vseparator2");
  GLADE_HOOKUP_OBJECT (main_wnd, toolitem6, "toolitem6");
  GLADE_HOOKUP_OBJECT (main_wnd, button4, "button4");
  GLADE_HOOKUP_OBJECT (main_wnd, alignment6, "alignment6");
  GLADE_HOOKUP_OBJECT (main_wnd, hbox6, "hbox6");
  GLADE_HOOKUP_OBJECT (main_wnd, image39, "image39");
  GLADE_HOOKUP_OBJECT (main_wnd, label6, "label6");
  GLADE_HOOKUP_OBJECT (main_wnd, toolitem7, "toolitem7");
  GLADE_HOOKUP_OBJECT (main_wnd, button5, "button5");
  GLADE_HOOKUP_OBJECT (main_wnd, alignment7, "alignment7");
  GLADE_HOOKUP_OBJECT (main_wnd, hbox7, "hbox7");
  GLADE_HOOKUP_OBJECT (main_wnd, image40, "image40");
  GLADE_HOOKUP_OBJECT (main_wnd, label7, "label7");
  GLADE_HOOKUP_OBJECT (main_wnd, toolitem8, "toolitem8");
  GLADE_HOOKUP_OBJECT (main_wnd, button6, "button6");
  GLADE_HOOKUP_OBJECT (main_wnd, alignment8, "alignment8");
  GLADE_HOOKUP_OBJECT (main_wnd, hbox8, "hbox8");
  GLADE_HOOKUP_OBJECT (main_wnd, image41, "image41");
  GLADE_HOOKUP_OBJECT (main_wnd, label8, "label8");
  GLADE_HOOKUP_OBJECT (main_wnd, toolitem9, "toolitem9");
  GLADE_HOOKUP_OBJECT (main_wnd, vseparator3, "vseparator3");
  GLADE_HOOKUP_OBJECT (main_wnd, toolitem10, "toolitem10");
  GLADE_HOOKUP_OBJECT (main_wnd, button7, "button7");
  GLADE_HOOKUP_OBJECT (main_wnd, alignment9, "alignment9");
  GLADE_HOOKUP_OBJECT (main_wnd, hbox9, "hbox9");
  GLADE_HOOKUP_OBJECT (main_wnd, image42, "image42");
  GLADE_HOOKUP_OBJECT (main_wnd, label9, "label9");
  GLADE_HOOKUP_OBJECT (main_wnd, toolitem11, "toolitem11");
  GLADE_HOOKUP_OBJECT (main_wnd, button8, "button8");
  GLADE_HOOKUP_OBJECT (main_wnd, alignment10, "alignment10");
  GLADE_HOOKUP_OBJECT (main_wnd, hbox10, "hbox10");
  GLADE_HOOKUP_OBJECT (main_wnd, image43, "image43");
  GLADE_HOOKUP_OBJECT (main_wnd, label10, "label10");
  GLADE_HOOKUP_OBJECT (main_wnd, hpaned1, "hpaned1");
  GLADE_HOOKUP_OBJECT (main_wnd, scrolledwindow1, "scrolledwindow1");
  GLADE_HOOKUP_OBJECT (main_wnd, treeview1, "treeview1");
  GLADE_HOOKUP_OBJECT (main_wnd, vpaned1, "vpaned1");
  GLADE_HOOKUP_OBJECT (main_wnd, scrolledwindow2, "scrolledwindow2");
  GLADE_HOOKUP_OBJECT (main_wnd, treeview2, "treeview2");
  GLADE_HOOKUP_OBJECT (main_wnd, scrolledwindow3, "scrolledwindow3");
  GLADE_HOOKUP_OBJECT (main_wnd, textview3, "textview3");
  GLADE_HOOKUP_OBJECT_NO_REF (main_wnd, tooltips, "tooltips");

  gtk_widget_grab_focus (treeview2);
  gtk_window_add_accel_group (GTK_WINDOW (main_wnd), accel_group);

  return main_wnd;
}
