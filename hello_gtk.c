#include <gtk/gtk.h>

// Wrapper function to set visibility to FALSE
static gboolean hide_button_after_fade_out(GtkWidget *button)
{
    gtk_widget_set_visible(button, FALSE);
    return G_SOURCE_REMOVE; // Stop the timeout after hiding the button
}

static void on_button_clicked(GtkWidget *button, gpointer data)
{/
    // Add a CSS class to trigger the fade-out animation
    gtk_widget_set_name(button, "fade-out");

    // Use a timeout to hide the button after the animation duration (1 second here)
    g_timeout_add(1000, (GSourceFunc)hide_button_after_fade_out, button); 
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *box;
    GtkCssProvider *css_provider;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Set up the box layout with GTK_ORIENTATION_VERTICAL, so buttons are arranged in a column
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // 5px spacing between buttons
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(window), box);

    // Create and load CSS styles for the fade-out animation
    css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(css_provider,
        "#fade-out { "
        "    opacity: 0; "
        "    transition: opacity 1s ease; " // Fade-out duration of 1 second
        "}");

    // Apply the CSS to the default screen
    gtk_style_context_add_provider_for_display(gdk_display_get_default(),
        GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Create buttons and connect the click signal
    for (size_t i = 0; i < 30; i++)
    {
        char tmplabel[8];
        sprintf(tmplabel, "but %zu", i);
        
        GtkWidget *tmpbutton = gtk_button_new_with_label(tmplabel);
        g_signal_connect(tmpbutton, "clicked", G_CALLBACK(on_button_clicked), NULL);
        
        gtk_box_append(GTK_BOX(box), tmpbutton);
    }

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
