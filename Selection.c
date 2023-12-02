#include <gtk/gtk.h>

void on_item_hovered(GtkWidget *widget, gpointer data);
void on_item_clicked(GtkWidget *widget, gpointer data);
void on_window_resize(GtkWidget *widget, GdkRectangle *allocation, gpointer data);

// Explications pour chaque sujet
const char *explications[] = {
    "Un arbre binaire est une structure de données dans laquelle chaque nœud a au maximum deux enfants, appelés enfant gauche et enfant droit. Cette structure est largement utilisée dans des applications telles que les arbres de recherche, les tas, et dans l'implémentation de divers algorithmes de tri.",
    "Un tas binaire est un arbre binaire complet (chaque niveau, sauf peut-être le dernier, est complètement rempli et tous les nœuds sont aussi à gauche que possible) avec une propriété supplémentaire appelée propriété de tas. Dans un tas max, chaque nœud parent est supérieur ou égal à ses enfants et dans un tas min, il est inférieur ou égal. Les tas binaires sont utilisés dans l'implémentation d'algorithmes de tri et de files de priorité.",
    "Le tri par tas (Heap Sort) est un algorithme de tri efficace basé sur la structure de données de tas binaire. L'idée est de construire d'abord un tas à partir de l'ensemble de données, puis de supprimer successivement le plus grand élément (dans un tas max) et de le placer à la fin de la séquence triée. Ce processus est répété jusqu'à ce que tous les éléments soient triés.",
    "Une file de priorité est une structure de données abstraite similaire à une file d'attente ordinaire, mais chaque élément a une « priorité » associée. Les éléments avec une priorité plus élevée sont servis avant ceux avec une priorité plus basse. Les files de priorité sont souvent implémentées à l'aide de tas binaires pour permettre une insertion et une suppression efficaces.",
    "La méthode de compression de Huffman est une technique de compression de données sans perte. Elle utilise un algorithme de codage basé sur la fréquence d'apparition de chaque élément (comme des caractères dans un fichier texte). Les éléments les plus fréquents reçoivent les codes les plus courts et ceux qui sont moins fréquents reçoivent des codes plus longs, ce qui réduit la taille totale des données."
};



int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Création de la fenêtre principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Selection");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    gtk_window_set_resizable(GTK_WINDOW(window), TRUE); 
    gtk_window_set_deletable(GTK_WINDOW(window), TRUE);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Configuration de l'apparence
    GtkSettings *settings = gtk_settings_get_default();
    g_object_set(settings, "gtk-application-prefer-dark-theme", TRUE, NULL);

    // CSS Provider pour le style
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider,
        "#left_vbox { background-color: #151515; }"
        "#explication_title { font-size: 20px; font-weight: bold; }"
        "#titre_label { font-size: 30px; font-weight: bold;}", 
        -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Création des conteneurs
    GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_name(left_vbox, "left_vbox");
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    GtkWidget *titre_label = gtk_label_new("ARBRE");
    gtk_widget_set_name(titre_label, "titre_label");
    gtk_box_pack_start(GTK_BOX(left_vbox), titre_label, FALSE, FALSE, 0);


    // Création et configuration du label pour le titre du texte explicatif
    GtkWidget *explication_title_label = gtk_label_new("EXPLICATION");
    gtk_widget_set_name(explication_title_label, "explication_title");
    gtk_box_pack_start(GTK_BOX(right_vbox), explication_title_label, FALSE, FALSE, 0);

    // Création et configuration du label pour le sous-titre
    GtkWidget *sous_titre_label = gtk_label_new("");
    gtk_widget_set_name(sous_titre_label, "sous_titre_label");
    gtk_box_pack_start(GTK_BOX(right_vbox), sous_titre_label, FALSE, FALSE, 0);

    // Configuration du label pour les explications
    GtkWidget *explication_label = gtk_label_new("Explication du code ici");
    gtk_widget_set_name(explication_label, "explication_label");
    gtk_label_set_line_wrap(GTK_LABEL(explication_label), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(explication_label), GTK_WRAP_WORD);
    gtk_label_set_justify(GTK_LABEL(explication_label), GTK_JUSTIFY_LEFT);

    gtk_paned_pack1(GTK_PANED(paned), left_vbox, TRUE, FALSE);
    gtk_paned_pack2(GTK_PANED(paned), right_vbox, TRUE, FALSE);

    gtk_box_pack_start(GTK_BOX(right_vbox), explication_label, TRUE, TRUE, 0);

    // Boutons pour les différents sujets
    const char *items[] = {
     "TP1: Arbres Binaires",
     "TP2: Tas Binaires",
     "TP3: Tri par Tas",
     "TP4: Files de priorité",
     "PROJET: Methode de compression de Huffman"
    };
    for (int i = 0; i < 5; i++) {
        GtkWidget *item = gtk_button_new_with_label(items[i]);
        g_signal_connect(item, "enter", G_CALLBACK(on_item_hovered), explication_label);
        g_signal_connect(item, "clicked", G_CALLBACK(on_item_clicked), NULL);
        gtk_box_pack_start(GTK_BOX(left_vbox), item, FALSE, FALSE, 0);
    }

    g_signal_connect(window, "size-allocate", G_CALLBACK(on_window_resize), paned);

    gtk_container_add(GTK_CONTAINER(window), paned);
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

void on_item_hovered(GtkWidget *widget, gpointer data) {
    const char *label = gtk_button_get_label(GTK_BUTTON(widget));
    const char *explication = NULL;
    const char *sous_titre = NULL;

    if (strcmp(label, "TP1: Arbres Binaires") == 0) {
        explication = explications[0];
        sous_titre = "Arbres Binaires";
    } else if (strcmp(label, "TP2: Tas Binaires") == 0) {
        explication = explications[1];
         sous_titre = "Tas Binaires";
    } else if (strcmp(label, "TP3: Tri par Tas") == 0) {
        explication = explications[2];
        sous_titre = "Tri par Tas";
    } else if (strcmp(label, "TP4: Files de priorité") == 0) {
        explication = explications[3];
        sous_titre = "Files de priorité";
    } else if (strcmp(label, "PROJET: Methode de compression de Huffman") == 0) {
        explication = explications[4];
        sous_titre = "PROJET: Methode de compression de Huffman";
    }

    if (explication != NULL) {
        gtk_label_set_text(GTK_LABEL(data), explication);
    }
}

void on_item_clicked(GtkWidget *widget, gpointer data) {
    const char *label = gtk_button_get_label(GTK_BUTTON(widget));
    GtkWidget *new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(new_window), label);
    gtk_widget_show_all(new_window);
}

void on_window_resize(GtkWidget *widget, GdkRectangle *allocation, gpointer data) {
    GtkWidget *paned = GTK_WIDGET(data);
    gint width = allocation->width;
    gtk_paned_set_position(GTK_PANED(paned), width * 0.4); // 40% de la largeur totale
}
