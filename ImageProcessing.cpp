#include "highgui.h"
#include "cv.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>

#include <atlstr.h>
#include <atlimage.h>

using namespace std;

IplImage* image = 0;
IplImage* src = 0;
int X, Y;
bool FlagClicked = false;
int ROI = 10;

void MousePress(int event, int x, int y, int flags, void* param)
{
	IplImage* img = (IplImage*)param;

	switch (event) {

		case CV_EVENT_MOUSEMOVE :
			break;

		case CV_EVENT_LBUTTONDOWN :
			X = x, Y = y;
			FlagClicked = true;
			printf("%d x %d\n", x, y);
			break;

		case CV_EVENT_LBUTTONUP :
			break;

	}

}

int main(int argc, char** argv)
{
	vector<int> myVector;
	int idx = 0;

	IplImage* img = cvLoadImage("H://1H-39//0.png");

	cvNamedWindow("DisplayPicture", CV_WINDOW_AUTOSIZE);
	cvShowImage("DisplayPicture", img);

	cvSetMouseCallback("DisplayPicture", MousePress, (void*)img);

	while (!FlagClicked)
	{
		cvWaitKey(500);
	}

	cvReleaseImage(&img);
	cvDestroyWindow("DisplayPicture");

	ofstream fout("ppg.txt");

	while (true)
	{
		wchar_t name[64], num[8];
		_itow(idx, num, 10);
		wcscpy(name, L"H://1H-39//");
		wcscat(name, num);
		wcscat(name, L".png");

		ATL::CImage img1;
		img1.Load(name);
		if (img1.IsNull())
			break;

		double value = 0;
		for (int y = Y - ROI; y < Y + ROI; y++)
		for (int x = X - ROI; x < X + ROI; x++)
			value += GetGValue(img1.GetPixel(x,y));
		value /= (double)(2 * ROI + 1)*(2 * ROI + 1);


		myVector.push_back(value);

		fout << value << endl;
		idx++;

		cout << idx - 1 << endl;

	}
	fout.close();


	ifstream file("C://Users//nicki_000//Documents//3//pointsString_80.txt");
	ofstream cardio("cardio.txt");
	ofstream syncro("synchro.txt");
	ofstream max_index("max_index.txt");

	ofstream temp("temp.txt");

	vector <int> c1, c2,noimp_c,noimp_index_vec, cardio_vec;
	bool flag_start = false;
	int impulse_count = 0,
		noimpulse_count = 0,
		im_num = 0,
		noimp_index = 0,
		diff = 0,
		sum_cardio = 0,
		noimp,
		cardio_counter = 0,
		sum_counter = 0;
	double cardio_aver;
	vector <int> counters, sum_counters, max_cardio_index;

	if (file.is_open())
	{
		int counter = 0;
		while (!file.eof())
		{
			char value[32];
			file >> value;
			file >> value;
			file >> value;
			int ch1;
			sscanf(value, "%X", &ch1);

			file >> value;
			file >> value;
			file >> value;
			file >> value;
			file >> value;
			file >> value;

			file >> value;

			int ch2;

			sscanf(value, "%X", &ch2);

			file >> value;
			file >> value;
			file >> value;

			if (ch2 != 0)
				ch2 = 1;

				if ( ch2 == 0)
					impulse_count++;

				if (impulse_count != 0)
					cardio_counter++;
				if (counter !=0)
				if (c2[counter - 1] == 0 && ch2 == 1)
				{
					sum_cardio += ch1;
					sum_counter++;
					sum_counters.push_back(sum_counter);
				}


				temp << ch1 << endl;

				if (ch2 !=0 && impulse_count == 5 && c2[counter-1]==1)
				{
					counters.push_back(counter);
					noimpulse_count++;

					if (ch2 == 0)
					{


						noimp_c.push_back(noimpulse_count);
					}
						im_num++;
						noimp = noimpulse_count;
						impulse_count = 0;
						noimpulse_count = 0;
				}

				if (counter != 0)
				if (c2[counter - 1] == 1 && ch2 == 0  )
				{
					cardio_vec.push_back(sum_cardio);
					sum_cardio = 0;
					if (cardio_vec.size() != 0)
						cardio << cardio_vec[cardio_vec.size() - 1] << endl;
				}

			if (!flag_start)
			{
				if (ch2 != 0)
					continue;
				else
					flag_start = true;
			}

			c1.push_back(ch1);
			c2.push_back(ch2);

			counter++;

			syncro << ch2 << endl;

		}

    }
	syncro.close();
	cardio.close();
	file.close();
	max_index.close();
	temp.close();

}
