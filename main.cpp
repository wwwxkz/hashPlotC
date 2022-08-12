#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

// [ ] Class plotter
// [ ] Class menu
// [ ] plotter::function
// [ ] plotter::horizontal_bar labels
// [ ] plotter::pizza labels

void display(int width, char border, char direction, vector<string> frame) {
  // Top border
  cout << string(width, border);
  // Cout frame content
  for (int line = 0; line < frame.size(); line++) {
    // Calc blank spots removing content from display width
    int blank = width - frame[line].length();
    // Align content R, L, C using blank
    switch (direction) {
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

vector<string> vertical_bar(vector<tuple<int, string>> columns, int align_by_label) {
  vector<string> frame;
  // Align label text using blank spaces as padding
  // Find largest label and follow adding blank spaces to subsequent labels
  int largest_label = 0;
  if (align_by_label == 1) {
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
  vector<string> frame;
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
        cout << "*";
      } else {
        cout << " ";
      }
    }
    cout << "\n";
  }
  return frame;
}

void example_text() {
  int display_w = 40;
  vector<string> text = {
    "Firs text", 
    "Second text"
  };
  display(display_w, *"-", 'r', text);
}

void example_horizontal_bar() {
  int display_w = 40;
  vector<tuple<int, string>> bar = {
    make_tuple(4, "Testing bar label"),
    make_tuple(2, "Another label")
  };
  vector<string> frame = horizontal_bar(bar);
  display(display_w, *"-", 'l', frame);
}

void example_vertical_bar() {
  int display_w = 40;
  vector<tuple<int, string>> bar = {
    make_tuple(4, "Vertical bar label"),
    make_tuple(2, "My label")
  };
  vector<string> frame = vertical_bar(bar, 1);
  display(display_w, *"-", 'l', frame);
}

void example_pizza() {
  int display_w = 40;
  vector<tuple<int, string>> p = {
    make_tuple(4, "Pizza label test"),
    make_tuple(2, "Testing pizza quality")
  };
  vector<string> frame = pizza(p, 10);
  display(display_w, *"-", 'c', frame);
}

int main() {
  example_text();
  cout << endl;
  example_horizontal_bar();
  cout << endl;
  example_vertical_bar();
  cout << endl;
  example_pizza();
}