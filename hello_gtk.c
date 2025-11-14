#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

// Global counter
static int counter = 0;

// Structure to hold widget references
typedef struct {
    GtkEntry *entry_a;
    GtkEntry *entry_b;
    GtkLabel *result_label;
    GtkLabel *counter_label;
    GtkLabel *history_label;
} AppWidgets;

static void update_result(AppWidgets *widgets, const char *operation, double result) {
    char result_text[500];
    const char *entry_a_text = gtk_editable_get_text(GTK_EDITABLE(widgets->entry_a));
    const char *entry_b_text = gtk_editable_get_text(GTK_EDITABLE(widgets->entry_b));
    
    double a = atof(entry_a_text);
    double b = atof(entry_b_text);
    
    snprintf(result_text, sizeof(result_text),
             "Result: %.2f %s %.2f = %.2f",
             a, operation, b, result);
    
    gtk_label_set_text(widgets->result_label, result_text);
    
    // Update history
    const char *current_history = gtk_label_get_text(widgets->history_label);
    char new_history[1000];
    snprintf(new_history, sizeof(new_history), "%s\n%s", current_history, result_text);
    gtk_label_set_text(widgets->history_label, new_history);
}

static void on_add_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;
    const char *entry_a_text = gtk_editable_get_text(GTK_EDITABLE(widgets->entry_a));
    const char *entry_b_text = gtk_editable_get_text(GTK_EDITABLE(widgets->entry_b));
    
    double a = atof(entry_a_text);
    double b = atof(entry_b_text);
    double result = a + b;
    
    update_result(widgets, "+", result);
    counter++;
    char counter_text[50];
    snprintf(counter_text, sizeof(counter_text), "Operations: %d", counter);
    gtk_label_set_text(widgets->counter_label, counter_text);
}

static void on_subtract_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;
    const char *entry_a_text = gtk_editable_get_text(GTK_EDITABLE(widgets->entry_a));
    const char *entry_b_text = gtk_editable_get_text(GTK_EDITABLE(widgets->entry_b));
    
    double a = atof(entry_a_text);
    double b = atof(entry_b_text);
    double result = a - b;
    
    update_result(widgets, "-", result);
    counter++;
    char counter_text[50];
    snprintf(counter_text, sizeof(counter_text), "Operations: %d", counter);
    gtk_label_set_text(widgets->counter_label, counter_text);
}

static void on_multiply_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;
    const char *entry_a_text = gtk_editable_get_text(GTK_EDITABLE(widgets->entry_a));
    const char *entry_b_text = gtk_editable_get_text(GTK_EDITABLE(widgets->entry_b));
    
    double a = atof(entry_a_text);
    double b = atof(entry_b_text);
    double result = a * b;
    
    update_result(widgets, "×", result);
    counter++;
    char counter_text[50];
    snprintf(counter_text, sizeof(counter_text), "Operations: %d", counter);
    gtk_label_set_text(widgets->counter_label, counter_text);
}

static void on_divide_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;
    const char *entry_a_text = gtk_editable_get_text(GTK_EDITABLE(widgets->entry_a));
    const char *entry_b_text = gtk_editable_get_text(GTK_EDITABLE(widgets->entry_b));
    
    double a = atof(entry_a_text);
    double b = atof(entry_b_text);
    
    if (b == 0) {
        gtk_label_set_text(widgets->result_label, "Error: Division by zero!");
        return;
    }
    
    double result = a / b;
    update_result(widgets, "÷", result);
    counter++;
    char counter_text[50];
    snprintf(counter_text, sizeof(counter_text), "Operations: %d", counter);
    gtk_label_set_text(widgets->counter_label, counter_text);
}

static void on_clear_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;
    gtk_editable_set_text(GTK_EDITABLE(widgets->entry_a), "");
    gtk_editable_set_text(GTK_EDITABLE(widgets->entry_b), "");
    gtk_label_set_text(widgets->result_label, "Result will appear here...");
    gtk_label_set_text(widgets->history_label, "History:");
    counter = 0;
    gtk_label_set_text(widgets->counter_label, "Operations: 0");
}

static void on_count_clicked(GtkButton *button, gpointer user_data) {
    AppWidgets *widgets = (AppWidgets *)user_data;
    char count_text[200] = "Counting from 1 to 10: ";
    for (int i = 1; i <= 10; i++) {
        char temp[50];
        snprintf(temp, sizeof(temp), "%d ", i);
        strcat(count_text, temp);
    }
    gtk_label_set_text(widgets->result_label, count_text);
}

static void on_activate(GtkApplication *app, gpointer user_data) {
    // Create main window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Enhanced Calculator - GTK");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 600);
    
    // Create main vertical box
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_widget_set_margin_top(main_box, 20);
    gtk_widget_set_margin_bottom(main_box, 20);
    gtk_widget_set_margin_start(main_box, 20);
    gtk_widget_set_margin_end(main_box, 20);
    
    // Create widgets structure
    AppWidgets *widgets = g_malloc(sizeof(AppWidgets));
    
    // Title
    GtkWidget *title_label = gtk_label_new("Enhanced Calculator");
    gtk_widget_add_css_class(title_label, "title-1");
    gtk_box_append(GTK_BOX(main_box), title_label);
    
    // Counter label
    GtkWidget *counter_label = gtk_label_new("Operations: 0");
    widgets->counter_label = GTK_LABEL(counter_label);
    gtk_box_append(GTK_BOX(main_box), counter_label);
    
    // Input section
    GtkWidget *input_frame = gtk_frame_new("Input Numbers");
    GtkWidget *input_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(input_box, 10);
    gtk_widget_set_margin_bottom(input_box, 10);
    gtk_widget_set_margin_start(input_box, 10);
    gtk_widget_set_margin_end(input_box, 10);
    
    // Entry A
    GtkWidget *label_a = gtk_label_new("Number A:");
    gtk_box_append(GTK_BOX(input_box), label_a);
    GtkWidget *entry_a = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_a), "Enter first number");
    widgets->entry_a = GTK_ENTRY(entry_a);
    gtk_box_append(GTK_BOX(input_box), entry_a);
    
    // Entry B
    GtkWidget *label_b = gtk_label_new("Number B:");
    gtk_box_append(GTK_BOX(input_box), label_b);
    GtkWidget *entry_b = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_b), "Enter second number");
    widgets->entry_b = GTK_ENTRY(entry_b);
    gtk_box_append(GTK_BOX(input_box), entry_b);
    
    gtk_frame_set_child(GTK_FRAME(input_frame), input_box);
    gtk_box_append(GTK_BOX(main_box), input_frame);
    
    // Operations section
    GtkWidget *ops_frame = gtk_frame_new("Operations");
    GtkWidget *ops_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(ops_box, 10);
    gtk_widget_set_margin_bottom(ops_box, 10);
    gtk_widget_set_margin_start(ops_box, 10);
    gtk_widget_set_margin_end(ops_box, 10);
    
    // Operation buttons in a grid
    GtkWidget *ops_grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(ops_grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(ops_grid), 10);
    
    GtkWidget *add_btn = gtk_button_new_with_label("Add (+)");
    GtkWidget *sub_btn = gtk_button_new_with_label("Subtract (-)");
    GtkWidget *mul_btn = gtk_button_new_with_label("Multiply (×)");
    GtkWidget *div_btn = gtk_button_new_with_label("Divide (÷)");
    GtkWidget *count_btn = gtk_button_new_with_label("Count 1-10");
    GtkWidget *clear_btn = gtk_button_new_with_label("Clear All");
    
    g_signal_connect(add_btn, "clicked", G_CALLBACK(on_add_clicked), widgets);
    g_signal_connect(sub_btn, "clicked", G_CALLBACK(on_subtract_clicked), widgets);
    g_signal_connect(mul_btn, "clicked", G_CALLBACK(on_multiply_clicked), widgets);
    g_signal_connect(div_btn, "clicked", G_CALLBACK(on_divide_clicked), widgets);
    g_signal_connect(count_btn, "clicked", G_CALLBACK(on_count_clicked), widgets);
    g_signal_connect(clear_btn, "clicked", G_CALLBACK(on_clear_clicked), widgets);
    
    gtk_grid_attach(GTK_GRID(ops_grid), add_btn, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(ops_grid), sub_btn, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(ops_grid), mul_btn, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(ops_grid), div_btn, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(ops_grid), count_btn, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(ops_grid), clear_btn, 1, 2, 1, 1);
    
    gtk_box_append(GTK_BOX(ops_box), ops_grid);
    gtk_frame_set_child(GTK_FRAME(ops_frame), ops_box);
    gtk_box_append(GTK_BOX(main_box), ops_frame);
    
    // Result section
    GtkWidget *result_frame = gtk_frame_new("Result");
    GtkWidget *result_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(result_box, 10);
    gtk_widget_set_margin_bottom(result_box, 10);
    gtk_widget_set_margin_start(result_box, 10);
    gtk_widget_set_margin_end(result_box, 10);
    
    GtkWidget *result_label = gtk_label_new("Result will appear here...");
    gtk_label_set_wrap(GTK_LABEL(result_label), TRUE);
    gtk_label_set_selectable(GTK_LABEL(result_label), TRUE);
    widgets->result_label = GTK_LABEL(result_label);
    gtk_box_append(GTK_BOX(result_box), result_label);
    
    gtk_frame_set_child(GTK_FRAME(result_frame), result_box);
    gtk_box_append(GTK_BOX(main_box), result_frame);
    
    // History section
    GtkWidget *history_frame = gtk_frame_new("History");
    GtkWidget *history_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(history_box, 10);
    gtk_widget_set_margin_bottom(history_box, 10);
    gtk_widget_set_margin_start(history_box, 10);
    gtk_widget_set_margin_end(history_box, 10);
    
    GtkWidget *history_label = gtk_label_new("History:");
    gtk_label_set_wrap(GTK_LABEL(history_label), TRUE);
    gtk_label_set_selectable(GTK_LABEL(history_label), TRUE);
    widgets->history_label = GTK_LABEL(history_label);
    
    // Scrollable history
    GtkWidget *scrolled = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), history_label);
    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled), 100);
    gtk_box_append(GTK_BOX(history_box), scrolled);
    
    gtk_frame_set_child(GTK_FRAME(history_frame), history_box);
    gtk_box_append(GTK_BOX(main_box), history_frame);
    
    // Add main box to window
    gtk_window_set_child(GTK_WINDOW(window), main_box);
    
    // Store widgets pointer in window data
    g_object_set_data(G_OBJECT(window), "widgets", widgets);
    
    // Show window
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    
    app = gtk_application_new("com.example.hellogtk", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return status;
}

