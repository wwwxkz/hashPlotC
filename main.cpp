#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

// [X] Class plotter
// [X] Class menu
// [ ] plotter::function
// [ ] plotter::horizontal_bar labels
// [ ] plotter::pizza labels

class Plotter {
  public:
    void display(int width, char border, char position, vector<string> frame) {
      // Top border
      cout << string(width, border);
      // Cout frame content
      for (int line = 0; line < frame.size(); line++) {
        // Calc blank spots removing content from display width
        int blank = width - frame[line].length();
        // Align content R, L, C using blank
        switch (position) {
        case 'r':
          cout << endl << string(blank, ' ') + frame[line];
          break;
        case 'l':
          cout << endl << frame[line] + string(blank, ' ');
          break;
        case 'c':
          cout << endl
               << string(blank / 2, ' ') + frame[line] + string(blank / 2, ' ');
          break;
        }
      }
      // Bottom border
      cout << endl;
      cout << string(width, border);
    }

    vector<string> horizontal_bar(vector<tuple<int, string>> columns) {
      vector<string> frame;
      // Get each column
      for (int column = 0; column < columns.size(); column++) {
        int last_line = 0;
        // Get column '#' value
        int column_value = get<0>(columns[column]);
        // Loop in frame adding '#' until frame.size() is reached
        for (int line = 0; line < frame.size(); line++) {
          // When column value is completely added, break, even if frame.size() is not reached
          if(line >= column_value) {
            break;
          }
          frame[line] += "#";
          last_line++;
        }
        // If frame.size() reached but not all column values add push_back until it completes
        while (last_line < column_value) {
          frame.push_back("#");
          last_line++;
        }
      }
      // Reverse frame as bar starts from bottom to top and not the oposite
      vector<string> frame_reversed;
      int frame_size = frame.size();
      for (int line = 0; line < frame_size; line++) {
        frame_reversed.push_back(frame[frame_size - line - 1]);
      }
      return frame_reversed;
    }

    vector<string> vertical_bar(vector<tuple<int, string>> columns, char align_by_label) {
      vector<string> frame;
      // Align label text using blank spaces as padding
      // Find largest label and follow adding blank spaces to subsequent labels
      int largest_label = 0;
      if (align_by_label == *"y") {
          for (int column = 0; column < columns.size(); column++) {
            if (get<1>(columns[column]).length() > largest_label) {
              largest_label = get<1>(columns[column]).length();
            }
          }
      }
      for (int column = 0; column < columns.size(); column++) {
        frame.push_back(get<1>(columns[column]) + string(largest_label - get<1>(columns[column]).length(), ' ') + ": " + string(get<0>(columns[column]), '#'));
      } 
      return frame;
    }

    vector<string> pizza(vector<tuple<int, string>> slices, float radius) {
      vector<string> frame = {""};
      float l;
      // Terminal font/pixel size
      float k = 2;
      // Width
      for (int i = -radius; i <= radius; i++) {
        // Height
        for (int c = -radius; c <= radius; c++) {
          l = ((i * k) / radius) * ((i * k) / radius) + (c / radius) * (c / radius);
          // Make it size-equal as terminal/console height is not width-height equivalent
          if (l > 0.95 && l < 1.08) {
            frame[frame.size()-1] += "*";
          } else {
            frame[frame.size()-1] += " ";
          }
        }
        frame.push_back("");
      }
      return frame;
    }
};

class Menu { 
  public:
    Menu() {
      char border = *" "; 
      char position = *" ";
      int display_width;
      Plotter plotter;
      cout << "Type 'h' for help";
      while (1) {
        char option;
        cout << endl << "@-->> ";
        cin >> option;
        if (option == *"e") {
          this->examples(plotter);
        }
        if (option == *"h") {
          this->help();
        }
        if (option == *"c") {
          cout << "\033[H\033[J";
        }
        if (option == *"t" || option == *"b" || option == *"v" || option == *"p" || option == *"f") {
          cout << "Table width (40): ";
          cin >> display_width;
          cout << "Border char (-, #, @): ";
          cin >> border;
          while (position != *"r" && position != *"l" && position != *"c") {
            cout << "Position (l, r, c): ";
            cin >> position;
          }
        }
        if (option == *"t") {
          vector<string> frame;
          char end = *" ";
          while (end != *"y") {
            string text;
            cout << "Text to append: ";
            cin >> text;
            frame.push_back(text);
            cout << "End (y, n): ";
            cin >> end;
          }
          plotter.display(display_width, border, position, frame);
        }
        if (option == *"b") {
          vector<tuple<int, string>> bar;
          char end = *" ";
          while (end != *"y") {
            int value;
            string label;
            cout << "Bar value: ";
            cin >> value;
            cout << "Label text: ";
            cin >> label;
            bar.push_back(make_tuple(value, label));
            cout << "End (y, n): ";
            cin >> end;
          }
          vector<string> frame = plotter.horizontal_bar(bar);
          plotter.display(display_width, border, position, frame);
        }
        if (option == *"p") {
          vector<tuple<int, string>> pizza;
          int radius;
          cout << "Pizza radius (5, 10, 15): ";
          cin >> radius;
          char end = *" ";
          while (end != *"y") {
            int value;
            string label;
            cout << "Slice value: ";
            cin >> value;
            cout << "Slice text: ";
            cin >> label;
            pizza.push_back(make_tuple(value, label));
            cout << "End (y, n): ";
            cin >> end;
          }
          vector<string> frame = plotter.pizza(pizza, radius);
          plotter.display(display_width, border, position, frame);
        }
        if (option == *"v") {
          vector<tuple<int, string>> bar;
          char align_by_label = *" ";
          while (align_by_label != *"y" && align_by_label != *"n") {
            cout << "Align by label (y, n): ";
            cin >> align_by_label;
          }
          char end = *" ";
          while (end != *"y") {
            int value;
            string label;
            cout << "Bar value: ";
            cin >> value;
            cout << "Label text: ";
            cin >> label;
            bar.push_back(make_tuple(value, label));
            cout << "End (y, n): ";
            cin >> end;
          }
          vector<string> frame = plotter.vertical_bar(bar, align_by_label);
          plotter.display(display_width, border, position, frame);
        }
        if (option == *"q") {
          exit(0);
        }
      }
    }

  void help() {
    cout << "Examples       : e" << endl;
    cout << "Help           : h" << endl;
    cout << "Clear          : c" << endl;
    cout << "Text           : t" << endl;
    cout << "Horizontal Bar : b" << endl;
    cout << "Pizza Bar      : p" << endl;
    cout << "Vertical Bar   : v" << endl;
    cout << "Function       : f" << endl;
    cout << "Quit           : q" << endl;
  }

  void examples(Plotter plotter) {
    example_text(plotter);
    cout << endl;
    example_horizontal_bar(plotter);
    cout << endl;
    example_vertical_bar(plotter);
    cout << endl;
    example_pizza(plotter);
  }

  void example_text(Plotter plotter) {
    int display_width = 40;
    vector<string> text = {
      "Firs text", 
      "Second text"
    };
    plotter.display(display_width, *"-", 'r', text);
  }

  void example_horizontal_bar(Plotter plotter) {
    int display_width = 40;
    vector<tuple<int, string>> bar = {
      make_tuple(4, "Testing bar label"),
      make_tuple(2, "Another label")
    };
    vector<string> frame = plotter.horizontal_bar(bar);
    plotter.display(display_width, *"-", 'l', frame);
  }

  void example_vertical_bar(Plotter plotter) {
    int display_width = 40;
    vector<tuple<int, string>> bar = {
      make_tuple(4, "Vertical bar label"),
      make_tuple(2, "My label")
    };
    vector<string> frame = plotter.vertical_bar(bar, *"y");
    plotter.display(display_width, *"-", 'l', frame);
  }

  void example_pizza(Plotter plotter) {
    int display_width = 40;
    vector<tuple<int, string>> p = {
      make_tuple(4, "Pizza label test"),
      make_tuple(2, "Testing pizza quality")
    };
    vector<string> frame = plotter.pizza(p, 10);
    plotter.display(display_width, *"-", 'c', frame);
  }
};

int main() {
  Menu menu;
}