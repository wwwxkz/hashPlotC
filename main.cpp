#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

void display(int width, char border, char direction, vector<string> frame) {
  // Top border
  cout << string(width, border);
  // Cout frame content
  for (int line = 0; line < frame.size(); line++) {
    // Calc blank spots removing content from display width
    int blank = width - frame[line].length();
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

  for (int column = 0; column < columns.size(); column++) {
    for (int row = 0; row < get<0>(columns[column]); row++) {
      frame.push_back("#");
    }
  } 

  return frame;
}

vector<string> vertical_bar(vector<tuple<int, string>> columns) {
  vector<string> frame;
  for (int column = 0; column < columns.size(); column++) {
    frame.push_back(get<1>(columns[column]) + ": " + string(get<0>(columns[column]), '#'));
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
  display(display_w, *"-", 'c', h);
}

void example_vertical_bar() {
  int display_w = 40;
  vector<tuple<int, string>> bar = {
    make_tuple(4, "texto"),
    make_tuple(2, "testing")
  };
  vector<string> h = vertical_bar(bar);
  display(display_w, *"-", 'l', h);
}

int main() {
  example_text();
  cout << endl;
  example_horizontal_bar();
  cout << endl;
  example_vertical_bar();
}
