#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

int IsValid(int x,int y,Mat v)
{
  if(x<0||y<0||x>=v.rows||y>=v.cols)
    return 0;
  else
    return 1;
}

int main()
{
	Mat a=imread("a.png",1);
    Mat b(a.rows,a.cols,CV_8UC3,Scalar(0,0,0));
    for(int i=0;i<a.rows;i++)
    {
    	for(int j=0;j<a.cols;j++)
    	{
    		if(a.at<Vec3b>(i,j)[1]>=150 && a.at<Vec3b>(i,j)[2]<=50 && a.at<Vec3b>(i,j)[0]<=50)
    		{
    			
    			b.at<Vec3b>(i,j)[1]=255;
    		}

    		if(a.at<Vec3b>(i,j)[2]==255 && a.at<Vec3b>(i,j)[1]==0 && a.at<Vec3b>(i,j)[0]==0)
    			b.at<Vec3b>(i,j)[2]=255;

    	}
    	
    }
    int c=0,g=0,f=0,xr,yr,xg,yg,cxr,cyr,cxg,cyg,maxr,maxg;
    for (int i = 0; i <a.rows; ++i)
    { c=0;g=0;
    	for (int j = 0; j <a.cols; ++j)
    	{
    		if(b.at<Vec3b>(i,j)[2]==255 && c==0)
    			{
    				xr=i;yr=j;
    			}
    		if (b.at<Vec3b>(i,j)[2]>=225)
    			{
    				c++;//printf("%d\n",c );
    			}	
    		if(b.at<Vec3b>(i,j)[1]==255 && g==0)
    			{
    				xg=i;yg=j;
    			}

    		if (b.at<Vec3b>(i,j)[1]==255)
    		{
    			g++;
    		}
    	}

    	if (f==0)
    	{
    		maxr=c;
    		cyr=yr*c/2;
    		cxr=xr;
    		//printf("%d\n",cyr );
    		maxg=g;
    		cyg=yg*g/2;
    		cxg=xg;
    		f=1;
    	}
    	else
    	{
    		if(maxr<c)
    		{
    			maxr=c;
    		cyr=yr+c/2;
    		cxr=xr;
    		//printf("%d %d %d\n",cyr,c,yr );
    		}
    		if(maxg<g)
    		{//printf("%d %d %d\n",cyr,c,yr );
    			maxg=g;
    		cyg=yg+g/2;
    		cxg=xg;
    		}
    	}

    }
    b.at<Vec3b>(cxr,cyr)[0]=255;
    b.at<Vec3b>(cxg,cyg)[0]=255;

    printf("%d %d %drr\n",cxr,cyr,a.cols);
    printf("%d %d %dgg\n",cxg,cyg,a.rows);

    Mat w=a.clone();int v=0,min=sqrt(pow(cxg-cxr,2)+pow(cyr-cyg,2)),mx=cxg,my=cyg;
    //int i=cxg,j=cyg;
    int L=0,B=0;
    float sint=sqrt(pow(cxg-cxr,2)/pow(min,2));
    float cost=sqrt(pow(cyg-cyr,2)/pow(min,2));
    printf("%f %f\n",sint,cost );
    printf("enter the length of bot:");
    scanf("%d",&L);
    printf("enter the breath of bot:");
    scanf("%d",&B);
    L=L/2;B=B/2;
    for(int i=0;i<a.rows;i++)
    {
        for(int j=0;j<a.cols;j++)
        {
            if((a.at<Vec3b>(i,j)[0]==255 && a.at<Vec3b>(i,j)[1]==255 && a.at<Vec3b>(i,j)[2]==255))
                                    {
            for(int k=i-L;k<i+L+1;k++)
                 {
                for(int l=j-B;l<j+B+1;l++)
                    {
                        if(IsValid(k,l,a))
                            {//printf("%d %d\n",k,l);
                                w.at<Vec3b>(k,l)[0]=255;
                                 w.at<Vec3b>(k,l)[1]=255;
                                  w.at<Vec3b>(k,l)[2]=255;
                            }
                    }
                }
            }
        }
    }
//imshow("path",w);
  //  waitKey(0);
    Mat z=a.clone();
    Mat h=a.clone();
    int i=cxg,j=cyg,u=0,i1=0,j1=0;
    while((i!=cxr || j!=cyr) )
    {
    	for(int k=i-1;k<i+2;k++)
  {
    for(int l=j-1;l<j+2;l++)
    {
      if(IsValid(k,l,a))
      {//printf("%d %d\n",k,l);
        if(!(w.at<Vec3b>(k,l)[0]>=250 && w.at<Vec3b>(k,l)[1]>=250 && w.at<Vec3b>(k,l)[2]>=250))
        {//printf("kk\n");
        	v=sqrt(pow(k-cxr,2)+pow(l-cyr,2));
        	if(v<min )//&& a.at<Vec3b>(k+L+1,l+B+1)!=255 && )
        	{
               /* if(IsValid(k+L+1,l+B+1,a) && IsValid(k+L+1,l-B-1,a) && IsValid(k-L-1,l+B+1,a) && IsValid(k-L-1,l-B-1,a) )
                {
                    if(!(a.at<Vec3b>(k+L+1,l+B+1)[0]>=250 && a.at<Vec3b>(k+L+1,l+B+1)[1]>=250 && a.at<Vec3b>(k+L+1,l+B+1)[2]>=250) && !( a.at<Vec3b>(k+L+1,l-B-1)[0]>=250 &&  a.at<Vec3b>(k+L+1,l-B-1)[1]>=250 &&  a.at<Vec3b>(k+L+1,l-B-1)[2]>=250) && !(a.at<Vec3b>(k-L-1,l+B+1)[0]>=250 && a.at<Vec3b>(k-L-1,l+B+1)[1]>=250 && a.at<Vec3b>(k-L-1,l+B+1)[2]>=250) && !(a.at<Vec3b>(k-L-1,l-B-1)[0]>=250 && a.at<Vec3b>(k-L-1,l-B-1)[1]>=250 && a.at<Vec3b>(k-L-1,l-B-1)[2]>=250))
                    {*/


        		          min=v;
        		          mx=k;
        		          my=l;

                          
                    //}
                //}
        	}
        	else if(v==min && z.at<Vec3b>(k,l)[0]!=252)
        	{//printf("%d %d %d\n",i,j,min );
        		/*if(IsValid(k+L+1,l+B+1,a) && IsValid(k+L+1,l-B-1,a) && IsValid(k-L-1,l+B+1,a) && IsValid(k-L-1,l-B-1,a) )
                {
                   // if(!(a.at<Vec3b>(k+L+1,l+B+1)==255) && !(a.at<Vec3b>(k+L+1,l-B-1)==255) && !(a.at<Vec3b>(k-L-1,l+B+1)==255) && !(a.at<Vec3b>(k-L-1,l-B-1)==255))
                    //{
                     if(!(a.at<Vec3b>(k+L+1,l+B+1)[0]>=250 && a.at<Vec3b>(k+L+1,l+B+1)[1]>=250 && a.at<Vec3b>(k+L+1,l+B+1)[2]>=250) && !( a.at<Vec3b>(k+L+1,l-B-1)[0]>=250 &&  a.at<Vec3b>(k+L+1,l-B-1)[1]>=250 &&  a.at<Vec3b>(k+L+1,l-B-1)[2]>=250) && !(a.at<Vec3b>(k-L-1,l+B+1)[0]>=250 && a.at<Vec3b>(k-L-1,l+B+1)[1]>=250 && a.at<Vec3b>(k-L-1,l+B+1)[2]>=250) && !(a.at<Vec3b>(k-L-1,l-B-1)[0]>=250 && a.at<Vec3b>(k-L-1,l-B-1)[1]>=250 && a.at<Vec3b>(k-L-1,l-B-1)[2]>=250))
                    {*/


                          
                          mx=k;
                          my=l;
                    //}
                //}

        	}
        	
        }
      }
    }
  }
  i1=i;j1=j;
  i=mx;j=my;//printf("kk\n");
  z.at<Vec3b>(i,j)[0]=252;
  z.at<Vec3b>(i,j)[1]=0;
  z.at<Vec3b>(i,j)[2]=0;

//if(u==0)
//{
   // sint=sqrt(pow(i-i1,2)/pow(2,2));
    //cost=sqrt(pow(j-cyr,2)/pow(min,2));
    sint=sqrt(pow(i-i1,2)/(pow(i-i1,2)+pow(j-j1,2)));
    cost=sqrt(pow(j-j1,2)/(pow(i-i1,2)+pow(j-j1,2)));
//printf("%f %f\n",sint,cost );
                          for(int p=i-L;p<i+L;p++)
                 {
                for(int q=j-B;q<j+B;q++)
                    {  // printf("%d %d %d %d\n",i,j,p,q );
                        if(IsValid(sqrt(pow(q*sint+p*cost,2)),sqrt(pow(q*cost-p*sint,2)),a))
                            {//printf("%d %d\n",k,l);
                                h.at<Vec3b>(sqrt(pow(q*sint+p*cost,2)),sqrt(pow(q*cost-p*sint,2)))[0]=200;
                                h.at<Vec3b>(sqrt(pow(q*sint+p*cost,2)),sqrt(pow(q*cost-p*sint,2)))[1]=100;
                                h.at<Vec3b>(sqrt(pow(q*sint+p*cost,2)),sqrt(pow(q*cost-p*sint,2)))[2]=55;
                               // printf("%d %d %d %d\n",i,j,(int)(p*(1)),(int)(q*(1)));
                            }
                    }
                }//u=1;
 //} //printf("%d %d %d\n",i,j,min );
  imshow("pathr",h);
   waitKey(25);
   for(int p=i-L;p<i+L;p++)
                 {
                for(int q=j-B;q<j+B;q++)
                    {  // printf("%d %d %d %d\n",i,j,p,q );
                        if(IsValid(p,q,a))
                            {//printf("%d %d\n",k,l);
                                h.at<Vec3b>((int)(p*(1)),(int)(q*(1)))[0]=a.at<Vec3b>(p*(1),q*(1))[0];
                                h.at<Vec3b>(p*(1),q*(1))[1]=a.at<Vec3b>(p*(1),q*(1))[1];
                                h.at<Vec3b>(p*(1),q*(1))[2]=a.at<Vec3b>(p*(1),q*(1))[2];
                                printf("%d %d %d %d\n",i,j,(int)(p*(1)),(int)(q*(1)));
                            }
                    }
                }//u=1;
 //} //printf("%d %d %d\n",i,j,min );
  //imshow("pathr",h);
   //waitKey(1);
  //if(i==365)
  	//i++;j++;
 //if(a.at<Vec3b>(mx,my)[2]==255 && a.at<Vec3b>(mx,my)[1]<=50 && a.at<Vec3b>(mx,my)[0]<=50)
  //	break;
    }
    //printf("%d %d %d\n",i,j,min );

    imshow("original",a);
   // imshow("image1",b);
    imshow("path",z);
    imshow("pathr",h);
    waitKey(0);
	return 0;
}