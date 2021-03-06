#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <menu.h>
#include <string>

char* text  = NULL;
/*
  OpenFile reads a text file and returns an int
  to check for errors
*/
static int Read(char *filename)
{
  FILE *file = NULL;
  file = fopen(filename, "rb");
  if (file == NULL)
    {
      return 1;
    }
  //obtain file size:
  fseek(file, 0, SEEK_END);
  long  mag  = ftell(file);
  fseek(file, 0, SEEK_SET);

  text = (char*) malloc(mag + 1);

  
  mag = fread(text, 1, mag, file);
  if (mag == 0)
    {
      return 2;
    }
  
  return 0;

}

/*
  Display prints the text to a tui
*/
static void Display()
{
  printw(text);
}
  
int main(int argc, char* argv[1]) {

  initscr();                 // start curses mode
  scrollok(stdscr, TRUE); 
  idlok(stdscr, TRUE); 
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLUE);
  bkgd(COLOR_PAIR(1));
   refresh();                 // print it on to the real screen
 
   
  char str[256] = "";
  if(argc == 2)
    {
      strcpy(str, argv[1]);
    }

  while(true)
    {
      if (strcmp(str, "") == 0)
	{
	  printw("Please enter the file you wish to open: ");
	  getstr(str);
	}
    
      int errorCheck = Read(str);
      if (errorCheck == 0)
	{
	  Display();
	  break;
	}
      else if (errorCheck == 1)
	{
	  printw("Error");
	  printw("\n");
	  strcpy(str, "");
	}
      else if (errorCheck == 2)
	{
	  printw("Error ");
	  printw("\n");
	  break;
	}
    }  
  getch();
  endwin();                  // end curses mode
  return EXIT_SUCCESS;
} //main
  
