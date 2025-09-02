# Bear and Floodlight

## 题目描述

One day a bear lived on the $ Oxy $ axis. He was afraid of the dark, so he couldn't move at night along the plane points that aren't lit. One day the bear wanted to have a night walk from his house at point $ (l,0) $ to his friend's house at point $ (r,0) $ , along the segment of length $ (r-l) $ . Of course, if he wants to make this walk, he needs each point of the segment to be lit. That's why the bear called his friend (and yes, in the middle of the night) asking for a very delicate favor.

The $ Oxy $ axis contains $ n $ floodlights. Floodlight $ i $ is at point $ (x_{i},y_{i}) $ and can light any angle of the plane as large as $ a_{i} $ degree with vertex at point $ (x_{i},y_{i}) $ . The bear asked his friend to turn the floodlights so that he (the bear) could go as far away from his house as possible during the walking along the segment. His kind friend agreed to fulfill his request. And while he is at it, the bear wonders: what is the furthest he can go away from his house? Hep him and find this distance.

Consider that the plane has no obstacles and no other light sources besides the floodlights. The bear's friend cannot turn the floodlights during the bear's walk. Assume that after all the floodlights are turned in the correct direction, the bear goes for a walk and his friend goes to bed.

## 说明/提示

In the first sample, one of the possible solutions is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF385D/70cd74581588ecc939447891194dd426bcc1962c.png)In the second sample, a single solution is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF385D/6d28a59da2dde7e6425608e1f0cdf10b62cece79.png)In the third sample, a single solution is:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF385D/10b4dd48817911ff77f858eb6a9fd18802c09260.png)

## 样例 #1

### 输入

```
2 3 5
3 1 45
5 1 45
```

### 输出

```
2.000000000
```

## 样例 #2

### 输入

```
1 0 1
1 1 30
```

### 输出

```
0.732050808
```

## 样例 #3

### 输入

```
1 0 1
1 1 45
```

### 输出

```
1.000000000
```

## 样例 #4

### 输入

```
1 0 2
0 2 90
```

### 输出

```
2.000000000
```

# 题解

## 作者：洛谷の老豆 (赞：0)

### 题意简述（翻译）

在平面直角坐标系上，沿直线从 $(l,0)$ 走到 $(r,0)$ 。有 $n$ 盏灯，第 $i$ 盏灯位于 $(x_i,y_i)$ ，可以照亮的角度为 $a_i^\circ$ （注意**不是**弧度制）。途中不能经过未照亮的区域，求能走的最远距离。

### 正解

注意到 $n\leq 20$ ，明显是状压DP，设 $f[s]$ 为选择灯状态为 $s$ 时最远可以到达的位置。

为方便计算，纵坐标 $y_i$ 取绝对值，不影响正确性。

考虑加入一盏灯 $A(x_i,y_i)$ ，令角的始边过 $(f[s],0)$ 是最优的，此时终边与 $x$ 轴交点即为最远可以到达的位置。

当 $x_i$ 大于 $f[s]$ 时，画图并分类讨论，运用一些三角函数知识进行计算（详见代码和下图）；不大于时同理，但还要考虑到这盏灯可以照亮 $(f[s],+∞)$ 的情况。

下图中 $B$ 为 $(f[s],+∞)$ ， $C$ 为照亮之后最远可以到达的位置 。

![](https://img-blog.csdnimg.cn/235ee19efd034490a6ca7f095f870be5.png#pic_center)

$x_i>f[s]$ 的第一种情况

![](https://img-blog.csdnimg.cn/9b39c66dd90e4180856ad9519db3dbe1.png#pic_center)

$x_i>f[s]$ 的第二种情况

![](https://img-blog.csdnimg.cn/b8617c5804da4115a684f40921c454d4.png#pic_center)

$x_i\leq f[s]$ 的第一种情况

![在这里插入图片描述](https://img-blog.csdnimg.cn/89cd95d5f4fd4110baf0c79ab1e7c1ad.png#pic_center)

$x_i\leq f[s]$ 的第二种情况

```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define inf 1000000007
#define ldb long double
#define hehe pair<pair<ldb,ldb>,ldb>
#define fir first
#define sec second
#define pi (ldb)(3.14159265358979)
#define N 25
#define M ((1<<20)+5)
using namespace std;
long long read()
{
	long long x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1ll)+(x<<3ll)+ch-48,ch=getchar();
	return x*f;
}
void write(long long x)
{
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int n,m;
ldb f[M],l,r;
hehe a[N];
ldb rad(ldb alpha)
{
	return alpha/(ldb)180*pi;
}
int main()
{
	n=read(),l=read(),r=read();
	for(int i=0;i<n;i++)
	{
		ldb x=read(),y=read(),z=read();
		a[i]={{x,fabs(y)},rad(z)};
	}
	for(int s=0;s<(1<<n);s++)f[s]=l;
	for(int s=0;s<(1<<n);s++)
	{
		for(int i=0;i<n;i++)
		{
			if((s>>i)&1)continue;
			ldb x=(a[i].fir).fir,y=(a[i].fir).sec,alpha=a[i].sec,beta,theta;
			int ss=s|(1<<i);
			if(x>f[s])
			{
				beta=atan((x-f[s])/y);
				if(alpha>beta)
				{
					theta=alpha-beta;
					f[ss]=max(x+y*tan(theta),f[ss]);
					f[ss]=min(f[ss],r);
				}
				else
				{
					theta=beta-alpha;
					f[ss]=max(x-y*tan(theta),f[ss]);
					f[ss]=min(f[ss],r);
				}
			}
			else
			{
				beta=atan((f[s]-x)/y);
				theta=alpha+beta;
				if(theta>rad(90))f[ss]=r;
				else f[ss]=max(x+y*tan(theta),f[ss]);
				f[ss]=min(f[ss],r);
			}
		}
	}
	printf("%.8Lf\n",f[(1<<n)-1]-l);
	return 0;
}

```





---

