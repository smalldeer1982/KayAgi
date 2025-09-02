#include <iostream>
#include <cmath>
using namespace std;
int a[100010][3];//用于存放价格和销量的数组
int main()
{
    int i=1,j=1,k,expect,down,max,temp,cha,xl,num,s,price,p;
    cin>>expect;//读入预期价
    while(cin>>a[i][1]>>a[i][2]&&a[i][1]!=-1&&a[i] [2]!=-1)//如果输入的两个数不是-1，-1
    {
	    i++;//循环变量i++
	    if(i>2&&a[i-1][1]-a[i-2][1]>1)//如果两个价格之间差大于一
	    {
		    i--;//回到上一个读入的销量
		    cha=(a[i-1][2]-a[i][2])/(a[i][1]-a[i-1][1]);//求出每次销量减少多少：销量差/价格差
		    temp=a[i][1];//记录下价格
		    for(j=a[i-1][1]+1;j<=temp;j++)//按价格递增顺序依次写入
		    {
		    	a[i][1]=j;//写入价格
		    	a[i][2]=a[i-1][2]-cha;//按销量差写入销量
		    	i++;
		    }
	    }
    }
    cin>>down;//输入超过最大价格之后每次销量降低多少
    i--;//因为上面的while循环最后有i++所以用i--抵消……
    xl=a[i][2];//记录目前的销量
    while(xl>0)
    {
	    if(xl-down<0)break;//如销量小于零则退出
	    else//否则
	    {
	    	xl-=down;//销量每次减掉down
	    	i++;//循环变量++
	    	a[i][1]=a[i-1][1]+1;//每次价格+1
	    	a[i][2]=xl;//销量就是xl
	    }
    }
    for(j=1;j<=10000;j++)//该遍历了，因为收税相当于补贴*-1所以记录一下符号即可
    {
	    max=-99999;//用于存储最大的总利润
	    for(k=1;k<=i;k++)//每次扫一遍每一种价格
	    {
		    num=(a[k][1]-a[1][1]+j)*a[k][2];//套公式算出总利润
		    if(num>=max)//如果总利润比目前最大的大
		    {
		        max=num;//更新max
			    price=a[k][1];//记录下价格
			    p=1;//记录下符号
		    }
	    }
	    if(price==expect){cout<<j*p;return 0;}//如果价格就是政府预期价则打印出来，因为本身就是从小到大遍历所以不用求绝对值最小的
	    max=-99999;//后面是收税，原理同上
	    for(k=1;k<=i;k++)
	    {
		    num=(a[k][1]-a[1][1]-j)*a[k][2];
		    if(num>=max)
		    {
		       max=num;
			    price=a[k][1];	
			    p=-1;
		    }
	    }
	    if(price==expect){cout<<j*p;return 0;}
    }
    //前面有了return 0;这儿就不用了。
}