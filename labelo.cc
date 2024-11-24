//
// Created by zeatoen on 11/21/24.
//

#include "labelo.h"


Labelo::Labelo():
    m_box(Gtk::Orientation::HORIZONTAL,10),
    m_label("hello everyone this is vey biiiiiiig.. \nlabello"),

{


  Glib::RefPtr<Gdk::Pixbuf>imbuf = Gdk::Pixbuf::create_from_file("hell.jpg");


    m_image.set_image(imbuf);
    m_box.append(m_image);
    m_box.append(m_label);

    set_child(m_box);


  }