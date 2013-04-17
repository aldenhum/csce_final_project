#include "std_lib_facilities_3.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"
#include "Chrono.h"
//#include <time.h>


struct Calendar_window : Window 	// Lines_window inherits from Window
{
	Calendar_window(Point xy, int w, int h, const string& title); // declare constructor

	private:
		Button prev_button;
		Button next_button;		// declare some buttons – type Button
		Button quit_button;

		void prev();			//what to do when prev_button is pushed
		void next(); 			//what to do when next_button is pushed
		void quit(); 			//what to do when quit_button is pushed

		static void cb_prev(Address, Address window); // callback for the previous month button
		static void cb_next(Address, Address window); // callback for the next month button
		static void cb_quit(Address, Address window); 	// callback for quit_button
}; 

Calendar_window::Calendar_window(Point xy, int w, int h, const string& title)
	:Window(xy,w,h,title),
	prev_button(Point(0,0),  		 70, 20, "Previous Month", cb_prev),
	next_button(Point(75,0), 		 70, 20, "Next Month",	   cb_next),
	quit_button(Point(x_max()-70,0), 70, 20, "QUIT", 	  	   cb_quit))
{
	attach(prev_button);
	attach(next_button);
	attach(quit_button);
}


//The callback functions... Just pass data along to "worker" functions
Calendar_window::cb_quit(Address, Address pw)
{
	reference_to<Calendar_window>(pw).quit();
}

Calendar_window::cb_prev(Address, Address pw)
{
	reference_to<Calendar_window>(pw).prev();
}

Calendar_window::cb_next(Address, Address pw)
{
	reference_to<Calendar_window(pw).next();
}

//Our "worker" functions
void Calendar_window::quit()
{
	hide(); //FLTK's way of deleting the window
}

void Calendar_window::prev()
{
	//TODO:
	/*
	Figure out the month which preceeds the current one...
	Update the display with the previous month's info...
	*/
	redraw();
}

void Calendar_window::next()
{
	//TODO:
	/*
	Figure out which month follows the current one...
	Update the display with the next month's info
	*/
	redraw();
}

struct Calendar_Day 
{
	//This should ACTUALLY just contain info about the days
	//TODO: Add a constructor which (somehow) takes a formatted date string
	//Probably need to have a read from file in here somewhere...
	//TODO: public members here
	//We need to make it so the day knows things such as what day of the week it is, what day of the month it is, and what (if anything) is special about it
	/*Calendar_Day(Point tl, int w, int h, string date_info, string day_of_week, int date)
	{
		//TODO: implement this constructor... we can start by using Rectangle's constructor
	}
	private:
		int month_start_day = 1;*/
};

int main()
{
	try
	{
		Date start;
		int y;
		int m;
		int d;
		cout << "Please enter a date (YYYY MM DD):: ";
		cin >> y >> m >> d;
		cout << endl;
		start = Date(y,(Date::Month)(m),d);
		/*time_t theTime = time(NULL);
struct tm *aTime = localtime(&theTime);

int day = aTime->tm_mday;
int month = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
int year = aTime->tm_year + 1900; // Year is # years since 1900*/
		int width = 700;
		int square_size = 100;
		int old_width;
		Rectangle* my_rect;
		Point* p;
		vector <vector <Point *> > board(8,vector <Point *> (8));
		vector <Point *> pts_row;
		if(H112 != 201206L)
			error("Error: incorrect std_lib_facilities_3.h version ", H112);
		
		Calendar_window my_window(Point(50,50),width,630,"Calendar"); //declare window

		int row = 0;
		for (int yy = 0; yy < 6/*board.size()*/; yy++)
		{
			row = yy; //row number
			for (int x = 0; x < 6/*board[row].size()*/; x++)
			{
				p = new Point(x*100,yy*100+30);
				pts_row.push_back(p); //add board to the row
			}

			board[row] = pts_row; //give the points to the matrix..
			pts_row.clear(); //clear our "temporary" row vector for reuse
		} //move down to the next row in the matrix of board

		//Our matrix now contains points
		//We need to create the squares which will comprise our board

		for (int r = 0; r < board.size(); r++)
		{
			for (int c = 0; c < board[r].size(); c++)
			{
				my_rect = new Rectangle(*(board[r][c]),square_size,square_size);
				my_window.attach((*my_rect));
			}
		}

		/*Line horizontal(Point(100,100),Point(200,100));  // make a horizontal line
		Line vertical(Point(150,50),Point(150,150));     // make a vertical line
		win1.attach(horizontal); //attach horizontal line to window
		win1.attach(vertical); //attach vertical line to window
		vertical.set_color(Color::magenta); */
	  
		//resize handling code (only checks width)
		while(true)
		{
			win1.redraw();
			width = win1.Fl_Widget::w();
			old_width = width;
			cout << old_width << endl;
			do
			{
				Fl::wait(1);	//wait up to 1 second
				width = win1.Fl_Widget::w();
			}
			while(width == old_width);
		}
	  
		return 0;
	}

	catch(exception& e)
	{
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}

	catch (...)
	{
		cerr << "Some exception\n";
		return 2;
	}
}