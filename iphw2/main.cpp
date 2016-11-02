#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include<opencv2/legacy/legacy.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include<vector>
#include<cv.h>

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Mat img = imread("/Users/sovietreborn/Desktop/lena_color.jpg"),imggray;
    if(img.empty())
    {
        fprintf(stderr, "Can not load image \n");
        return -1;
    }
    Mat resultlap;
    resultlap.create(img.size(),img.type());
        imggray.create(img.size(),img.type());
    //double time_ = static_cast<double>(cv::getTickCount());
   // cvtColor(img,imggray,CV_RGB2GRAY);
    //imggray=img;
        for(int j= 1; j<img.rows-1; ++j)
        
    {
        
        const uchar *previous = img.ptr<const uchar>(j-1);
        
        const uchar *current = img.ptr<const uchar>(j);
        
        const uchar *next = img.ptr<const uchar>(j+1);
        
        uchar *output = resultlap.ptr<uchar>(j);
        
        for(int k= 1; k<img.cols-1; k++)
            
            {
                int i=3*k;
                output[i] = cv::saturate_cast<uchar>(4*current[i]-previous[i]-next[i]-current[i-3]-current[i+3]);
                i=3*k-1;
                output[i] = cv::saturate_cast<uchar>(4*current[i]-previous[i]-next[i]-current[i-3]-current[i+3]);
                i=3*k-2;
                output[i] = cv::saturate_cast<uchar>(4*current[i]-previous[i]-next[i]-current[i-3]-current[i+3]);
            }
    }

    imwrite("/Users/sovietreborn/Desktop/good3.jpg", resultlap);
    Mat resultsobel;
    resultsobel.create(img.size(),img.type());
    for(int j= 1; j<img.rows-1; ++j)
        
    {
        
        const uchar *previous = img.ptr<const uchar>(j-1);
        
        const uchar *current = img.ptr<const uchar>(j);
        
        const uchar *next = img.ptr<const uchar>(j+1);
        
        uchar *output = resultsobel.ptr<uchar>(j);
        
        for(int k= 1; k<img.cols-1; k++)
            
        {
            int i=3*k;
            output[i] =atan2((2*current[i+3]+previous[i+3]+next[i+3]-2*current[i-3]-previous[i-3]-next[i-3]), (-2*previous[i]-previous[i+3]-previous[i-3]+2*next[i]+next[i+3]+next[i-3]));
            i=3*k-1;
            output[i] =atan2((2*current[i+3]+previous[i+3]+next[i+3]-2*current[i-3]-previous[i-3]-next[i-3]), (-2*previous[i]-previous[i+3]-previous[i-3]+2*next[i]+next[i+3]+next[i-3]));
            i=3*k-2;
            output[i] =atan2((2*current[i+3]+previous[i+3]+next[i+3]-2*current[i-3]-previous[i-3]-next[i-3]), (-2*previous[i]-previous[i+3]-previous[i-3]+2*next[i]+next[i+3]+next[i-3]));
            //printf("%f\n",output[i]);
        }
    }

    imwrite("/Users/sovietreborn/Desktop/good4.jpg", resultsobel);
    Mat resultsmooth;
    resultsmooth.create(img.size(),img.type());
    for(int j= 1; j<img.rows-1; ++j)
        
    {
        
        const uchar *previous = resultsobel.ptr<const uchar>(j-1);
        
        const uchar *current = resultsobel.ptr<const uchar>(j);
        
        const uchar *next = resultsobel.ptr<const uchar>(j+1);
        
        uchar *output = resultsmooth.ptr<uchar>(j);
        
        for(int k= 1; k<img.cols-1; k++)
            
        {
            int i=3*k;
            output[i] =(current[i-3]+current[i]+current[i+3]+previous[i]+previous[i-3]+previous[i+3]+next[i]+next[i+3]+next[i-3])/9;
            i=3*k-1;
            output[i] =(current[i-3]+current[i]+current[i+3]+previous[i]+previous[i-3]+previous[i+3]+next[i]+next[i+3]+next[i-3])/9;
            i=3*k-2;
            output[i] =(current[i-3]+current[i]+current[i+3]+previous[i]+previous[i-3]+previous[i+3]+next[i]+next[i+3]+next[i-3])/9;
            //printf("%f\n",output[i]);
        }
    }
    Mat resultnormal;
    resultnormal.create(img.size(),img.type());
    normalize(resultsmooth, resultnormal,1.0,0.0,NORM_MINMAX);
    Mat result;
    result.create(img.size(),img.type());
    Mat resultmul;
    resultmul.create(img.size(),img.type());
    multiply(resultlap, resultnormal, resultmul);
    imwrite("/Users/sovietreborn/Desktop/goodmulti.jpg", resultmul);
    //resultgau.create(img.size(),img.type());
    //GaussianBlur(resultmul, resultgau, Size(3,3),1);
    //imwrite("/Users/sovietreborn/Desktop/goodmulti.jpg", resultgau);
   // normalize(resultmul, resultnormal,1.0,0.0,NORM_MINMAX);
   // imwrite("/Users/sovietreborn/Desktop/goodmulti.jpg", resultnormal);

    add(resultmul,img,result);
    //cout<<"M="<<endl<<result<<endl;
    imwrite("/Users/sovietreborn/Desktop/goodgood.jpg", result);
    return 0;
}
