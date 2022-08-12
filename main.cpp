#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;

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

void example_text() {
  int display_w = 40;
  vector<string> text = {"teste", "teste2"};
  display(display_w, *"-", 'r', text);
}

void example_horizontal_bar() {
  int display_w = 40;
  vector<tuple<int, string>> bar = {
    make_tuple(4, "texto"),
    make_tuple(2, "testing")
  };
  vector<string> h = horizontal_bar(bar);
  display(display_w, *"-", 'l', h);
}

void example_vertical_bar() {
  int display_w = 40;
  vector<tuple<int, string>> bar = {
    make_tuple(4, "texto"),
    make_tuple(2, "testing")
  };
  vector<string> h = vertical_bar(bar, 1);
  display(display_w, *"-", 'l', h);
}

int main() {
  example_text();
  cout << endl;
  example_horizontal_bar();
  cout << endl;
  example_vertical_bar();
}