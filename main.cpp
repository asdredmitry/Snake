#include <iostream>
#include <iostream>
#include <list>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <utility>
#include <time.h>
const std :: string path = "/home/dmitry/GitHub/Snake/";
const int len = 4;
const int width = 3;
int from4(int x)
{
    return x - x%(2*len);
}
using namespace cv;

int main()
{
    int Score(0);
    int counter = 0;
    bool eatApple = true;
    Point apple;
    cvNamedWindow("Snake");
    Mat image = imread(path + "fon.jpg");
    std :: list <Point> snake;
    snake.push_back(Point(100,100));
    for(int i = 1; i < 30; i++)
        snake.push_back(Point(100 - i*len,100));
    Point direction(len,0);
    Point oldDirection(len,0);
     Mat tmpImage = image.clone();
     srand(time(0));
     Scalar appleColor = Scalar(rand()%255,rand()%255,144);
    while(true)
    {
        tmpImage = image.clone();
        std :: list <Point> :: iterator it = snake.begin();
        if(!eatApple)
            circle(tmpImage,apple,len + 4,appleColor,CV_FILLED);
        while(it != (--snake.end()))
        {
            if(it == snake.begin())
                line( tmpImage, (*it),*(++it), Scalar( 0, 0, 220 ),  10, 8 );
            else
                line( tmpImage, (*it),*(++it), Scalar( 110, 220, 0 ),  10, 8 );
        }
        char c = waitKey(40);
        if(eatApple)
        {
            apple = Point(from4(rand()%image.cols),from4(rand()%image.rows));
            eatApple = false;
        }
        imshow("Snake",tmpImage);
        oldDirection = direction;
        if(c == 'w')
            direction = Point(0,-len);
        else if(c == 's')
            direction = Point(0,len);
        else if(c == 'a')
            direction = Point(-len,0);
        else if(c == 'd')
            direction = Point(len,0);
        if(oldDirection == -direction)
            direction = oldDirection;
        snake.push_front(*(snake.begin()) + direction);
        if((*snake.begin()).x > image.cols || (*snake.begin()).x < 0 || (*snake.begin()).y > image.rows || ((*snake.begin()).y < 0))
        {
            std :: cout << " YOU LOSE" << std :: endl;
            std :: cout << " FINAL SCORE " << Score << std :: endl;
            exit(0);
        }
        it = snake.begin();
        it ++;
        while(it != (snake.end()))
        {
            if(*it == *(snake.begin()))
            {
                std :: cout << " YOU LOSE" << std :: endl;
                std :: cout << " FINAL SCORE " << Score << std :: endl;
                exit(0);
            }
            it++;
        }
        if(norm(*(snake.begin()) - apple) < 8)
        {
            Score++;
            counter = 3;
            appleColor = Scalar(rand()%255,rand()%255,144);
            std :: cout << " YOUR SCORE IS " << Score << std :: endl;
            eatApple = true;
        }
        else if(counter != 0)
            counter --;
        else
            snake.pop_back();
    }
    waitKey();
    image.release();
    return 0;
}
