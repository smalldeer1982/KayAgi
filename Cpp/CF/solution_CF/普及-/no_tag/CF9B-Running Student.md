# Running Student

## 题目描述

一位可怜的学生再次遭遇不幸——他要考试迟到了。

【他所在的地区可以看成一个平面直角坐标系，】他跑到了位于(0,0)处的公交车站，上了一辆小巴。这辆小巴沿x轴向x轴正方向行驶。

这个学生知道这样一些事：

这辆小巴将停靠n个站点，其中第i个站点位于(xi,0)处。

每一个站点的坐标都不相同。

这辆小巴将以速度vb匀速行驶。

小巴停站的时间很短，可以忽略不计。

乘客只能在站点上下车。

乘客最晚必须在终点站下车。

考试地点在(xu,yu)处。

他可以用vs的速度匀速从一个车站跑向考试地点。

在平面直角坐标系内，两点间的距离可以用![](https://cdn.luogu.org/upload/vjudge_pic/CF9B/22fd88ba9a7f84161b680cf39a97d9a06bc287ba.png)表示

他不能在上车站下车。
这个可怜的学生想用尽可能短的时间到达考试地点。请你帮他选择一个可以达到他的目的的下车地点。如果有多个满足的下车地点，请输出离考试地点最近的一个。

## 说明/提示

保证2<=n<=100,1<=vb,vs<=1000,0<=xi<=10^5,0<=|xu|,|yu|<=10^5

其他

就像你所知道的一样，学生通常是匆匆忙忙的，但小巴通常不是。所以如果你发现学生的速度比小巴快，不要吃惊。

## 样例 #1

### 输入

```
4 5 2
0 2 4 6
4 1
```

### 输出

```
3```

## 样例 #2

### 输入

```
2 1 1
0 100000
100000 100000
```

### 输出

```
2```

# 题解

## 作者：panjoel (赞：5)

这题只需要暴力枚举每一个站台下车，再由学生步行到学校算最小值。

**但是注意（此题有陷阱）：**

1. 看题，他跑到了位于(0,0)处的公交车站，**上了一辆小巴**。且他不能在**上车站下车**。所以他不能直接从（0,0）点下车。应该越过起点搜索。

1. 题目说：如果有多个满足的下车地点，请输出**离考试地点最近**的一个。因此要把距离储存起来比较大小，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/5zhivqzn.png)

### AC代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;

long long n,vb,vs,x,y,a[100010],ans;
double minn_1=9e9,minn_2=9e9;//增加精度

int main(){
	cin>>n>>vb>>vs;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>x>>y;

	for(int i=2;i<=n;i++){//从2开始，必须乘坐小巴
		double k=(double)a[i]/vb;//公式
		double v=(double)sqrt((x-a[i])*(x-a[i])+y*y)/vs;//公式
		if(k+v<=minn_1&&v<minn_2){//注意等于号
			minn_1=k+v;
			minn_2=v;
			ans=i;
		}
	}

	cout<<ans;

	return 0;
}
```


---

## 作者：sinsop90 (赞：2)

这道题是一道暴力枚举题,需要做的就是枚举每一个车站和考试地点的距离。

所以我们只需要枚举每一个车站与考场的距离,就可以求出最近的车站了。

要注意的事,由于我们记录距离和其他数值的数都是$int$类型的数

所以我们在计算直线距离的时候还要加上$(double)$来强制转换类型

代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,kl=0;
int vb,vs,mps[100005],x,y;
double ans,minx = 2147483647;
void sqrtm(int op){
	ans=(double)mps[op]/(double)vb+(double)sqrt(((double)x-(double)mps[op])*((double)x-(double)mps[op])+(double)y*y)/(double)vs;
	if (ans<minx || (ans==minx && abs(mps[op]-x)<abs(mps[kl]-x))){
		minx = ans;//记录最小值
		kl = op;//记录第几个车站
	}
}
int main(){
	cin>>n>>vb>>vs;
	for(int i=1;i<=n;i++){
		cin>>mps[i];
	}
	cin>>x>>y;
	for(int i=2;i<=n;i++){
		sqrtm(i);
	}
	cout<<kl<<endl;
}
```


---

## 作者：TRZ_2007 (赞：0)

**题解 [CF9B 【Running Student】](https://www.luogu.com.cn/problem/CF9B)**

# Solution  
对于每一个点，我们枚举是否下车，计算各种距离取最小值即可，时间复杂度 $\mathcal{O(n)}$。  
画一个图：  

![](https://cdn.luogu.com.cn/upload/image_hosting/gzph7csm.png)

通过图可以看出，应该在二号站点下车。  

**几个坑点**  
- 1:他不能在起点下车，所以枚举时应该从2（即图中站点1）开始枚举。  
- 2：如果有多个满足的下车地点，请输出离考试地点最近的一个。所以我们需要存下离站点最近的点进行比对。  


# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 109;

double dis[N],x[N],u,v,ans,ansd;
int n,v1,v2,cnt;

int main() {
	scanf("%d %d %d",&n,&v1,&v2);
	for(int i = 1;i <= n;i++) {
		scanf("%lf",x + i);
	}
	scanf("%lf %lf",&u,&v);
	for(int i = 1;i <= n;i++) {
		dis[i] = sqrt((u - x[i]) * (u - x[i]) + v * v);
	}
	ans = 1e9 + 10; ansd = 1e9 + 10;
	for(int i = 2;i <= n;i++) {
		if(ans >= dis[i] / v2 + x[i] / v1 && ansd > dis[i]) {
			ans = dis[i] / v2 + x[i] / v1;
			ansd = dis[i];
			cnt = i;
		}
	}
	printf("%d\n",cnt);
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 前言

这道题目略微有那么一点复杂，但是只要看懂了题面大概就没问题了。

### 分析

题目的意思就是说，我现在要去一个考场，坐标 $(ex,ey)$ ，那么现在有一辆公交车，它可以在坐标 $(x_i,0)$ 的地方下车，那么问你如果乘公交车，最优的话在哪里下车。

PS：不能在第 $1$ 个车站下车。

题目明白了，接下来要明白一个坐标公式。

$\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}$

这样就可以求出直线距离，然后再控制一下精度就可以了！

接下来呢？

上代码：

### 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
//头文件不多说。
using namespace std;
const int INF=105;
int n,vb,vs,data[INF],ex,ey;
//n 表示有几个车站，vb 表示公交车速度，vs 表示人的速度，data 表示第 i 个车站的 x 坐标，ex 和 ey 表示考场的距离。
signed main()
{
        scanf("%d %d %d",&n,&vb,&vs);。
        for (int i=1; i<=n; i++) scanf("%d",&data[i]);
        scanf("%d %d",&ex,&ey);//读入
        double time_min=2147483647;
        int ans=0;
        //time_min 表示最少的时间，一开始赋值最大值，ans 表示答案。
        for (int i=2; i<=n; i++) {
                double d=(double) data[i]/vb+(double) sqrt(((double)ex-data[i])*((double)ex-data[i])+(double)ey*ey)/(double) vs;
                //套用公式来计算时间，路程/速度=时间。
                if (d<(double) time_min) {
                        time_min=d;
                        ans=i;
                        //如果找到了小的那么就换掉。
                }
        }
        printf("%d\n",ans);//输出。
        return 0;
}
```

然后这题目就解决了？

提交上去。。。WA？？

然而我们发现有一个限制条件：

**如果有多个满足的下车地点，请输出离考试地点最近的一个。**

那么。。。公交车的速度可能和人的速度一样，然而就中了这个陷阱。

所以我们需要改一改 if 判断。

```cpp
if (d<time_min || (d==time_min && abs(data[i]-ex)<abs(data[ans]-ex))) //如果和它一样的时间，判断哪个车站距离考试地点近。
```

### 写在后面的话

如果我这篇题解有错误，那么非常感谢指出我错误的 dalao 。

**谢谢观赏！**

---

## 作者：亚索s (赞：0)

自己A这个题还是花了一些力气，原因还是在于思维上的不足，首先容易想到连续的点可以当作一个区间来处理，

然后幼稚认为跨过一个区间必须从上一个区间后面跨来，结果wa了。



后来发现可以一次性跨过多个区间。

---------------------

最后得出本题解法：



### 首先将点排序，两点之间距离太短不够起跳的两点放在一个区间，这样问题转化为跨过若干个区间。



### 如果能跨过某一个区间，那么一定有办法停在ri+1，就是区间右端点+1的位置，而且这样不会比最优解差。



转化出的区间一个一个顺次跨，这样也不会比最优解差。

---------------------
```
#include<bits/stdc++.h>
using namespace std;
int n,a,b,x[105],ex,ey;
double sum(int st)
{
	return st*1.0/a+sqrt((ex*1.0-st)*(ex*1.0-st)+ey*1.0*ey)*1.0/b;
}
int slove()
{
	int ans=2;
	double time=sum(x[2]);
	for(int i=3;i<=n;++i)
	{
		double tp=sum(x[i]);
		if(tp<time||tp==time&&abs(ex-x[i])<abs(ex-x[ans]))
		{
			time=tp;ans=i;
		}
	}
	return ans;
}
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&x[i]);
	}
	scanf("%d%d",&ex,&ey);
	int ans=slove();
	printf("%d\n",ans);
	return 0;
}
```

---

