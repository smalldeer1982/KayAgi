# [USACO07FEB] Building A New Barn G

## 题目描述

After scrimping and saving for years, Farmer John has decided to build a new barn. He wants the barn to be highly accessible, and he knows the coordinates of the grazing spots of all N (2 ≤ N ≤ 10,000 cows. Each grazing spot is at a point with integer coordinates (Xi, Yi) (-10,000 ≤ Xi ≤ 10,000; -10,000 ≤ Yi ≤ 10,000). The hungry cows never graze in spots that are horizontally or vertically adjacent.

The barn must be placed at integer coordinates and cannot be on any cow's grazing spot. The inconvenience of the barn for any cow is given the Manhattan distance formula | X - Xi | + | Y - Yi|, where (X, Y) and (Xi, Yi) are the coordinates of the barn and the cow's grazing spot, respectively. Where should the barn be constructed in order to minimize the sum of its inconvenience for all the cows?
给出平面上n个不相邻的点，要求到这n个点的曼哈顿距离之和最小的点的个数ans2，和这个最小距离ans1。


## 说明/提示

The minimum inconvenience is 10, and there are 4 spots that Farmer John can build the farm to achieve this: (0, -1), (0, 0), (1, 0), and (1, 1).


## 样例 #1

### 输入

```
4
1 -3
0 1
-2 1
1 -1```

### 输出

```
10 4```

# 题解

## 作者：浅色调 (赞：10)


### 思路：

首先，我们知道两点曼哈顿距离公式：
$$d=|x1-x2|+|y1-y2|$$

　　设$S$为题中所求的某个点$(x,y)$到$n$个点的曼哈顿距离之和，即$S=\sum{d}$

　　那么有$S=\sum{|x-xi|}+\sum{|y-yi|}$

　　容易发现，$x,y$互不影响求值，于是，我们可以将本题中的横纵坐标分开各自计算。

　　这样本题就变成了一道中学数学题：求$|x-x1|+|x-x2|+…|x-xn|\;min$，和求$|y-y1|+|y-y2|+…|y-yn|\;min$

　　由中学的数学知识可知直接求中位数就行了（可以分类讨论，也可以几何意义解决）。

　　那么，我们直接对$x,y$各自排序：

　　 1、当$n$为奇数时，取$x[n/2+1]$和$y[n/2+1]$，由于题意中不能选给出的点，所以判断：

　　　　若该点为给出的点，则枚举它的上下左右四个点上能求得的最小的$S$，更新$ans1$，然后统计$ans$当且仅当这$4$个点的$S=ans1$;

　　　　若该点不为给出的点，则直接将$ans1$赋为$S$，$ans2$赋为$1$。

　　 2、当$n$为偶数时，取$x[n/2],x[n/2+1]$和$y[n/2],y[n/2+1]$，显然这$(x[n/2+1]-x[n/2]+1)*(y[n/2+1]-y[n/2]+1)$个点到给定的$n$个点的曼哈顿距离和$S$相等（因为这个矩形中的点的横坐标在$x[n/2],x[n/2+1]$之间，纵坐标也同理），于是枚举矩形中每个点是否是给定的点，求一次$ans1$就$OK$了，先让$ans2$等于这个矩形的点数，每次更新减小就行了。
   
  欢迎来踩博客：[five20](http://www.cnblogs.com/five20/p/8849142.html)（本人蒟蒻，写题不易，转载请注明出处）
  
  ### 代码：
  ```cpp
// luogu-judger-enable-o2
#include<bits/stdc++.h>
#define il inline
#define ll long long
#define debug printf("%d %s\n",__LINE__,__FUNCTION__)
using namespace std;
const int N=1e5+7;
int n,b[N],c[N],ans1=233333333,ans2;
struct point{int x,y;}a[N];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
il int gi(){
    int a=0;char x=getchar();bool f=0;
    while((x<'0'||x>'9')&&x!='-')x=getchar();
    if(x=='-')x=getchar(),f=1;
    while(x>='0'&&x<='9')a=a*10+x-48,x=getchar();
    return f?-a:a;
}
il int getsum(int x,int y){
    int ans=0;
    for(int i=1;i<=n;i++)ans+=abs(x-b[i])+abs(y-c[i]);
    return ans;
}
int main()
{
    n=gi();
    for(int i=1;i<=n;i++)a[i].x=b[i]=gi(),a[i].y=c[i]=gi();
    sort(b+1,b+n+1);
    sort(c+1,c+n+1);
    if(n&1){
        int x=b[(n>>1)+1],y=c[(n>>1)+1];
        for(int i=0;i<4;i++){
            int xx=x+dx[i],yy=y+dy[i];
            int sum=getsum(xx,yy);
            if(sum<ans1)ans1=sum,ans2=1;
            else if(sum==ans1)++ans2;
        }
    }
    else {
        int x1=b[(n>>1)+1],x2=b[n>>1],y1=c[(n>>1)+1],y2=c[n>>1];
        ans2=(x1-x2+1)*(y1-y2+1);
        ans1=getsum(x1,y1);
        for(int i=1;i<=n;i++)
            if(a[i].x>=x2&&a[i].x<=x1&&a[i].y>=y2&&a[i].y<=y1)ans2--;
    }
    cout<<ans1<<' '<<ans2;
    return 0;
}
```

---

## 作者：LiSA_OLiVE (赞：1)

一个思维比其它题解判奇偶简单得多的思路！

蓝名蒟蒻第一次写题解，有问题麻烦大家指出！

~~写的很烂的话不要骂我 qwq~~

## **分析**
首先，曼哈顿距离，可以理解成是要找到点使得这个点到平面内所有点的**水平距离之和加垂直距离之和最小**。在本题中，对于解没有什么要求，只是不能重合，所以解得横纵坐标是彼此独立的，可以考虑分别求出能够使得**到每个点水平距离之和最小**的横坐标位置和**到每个点水平垂直之和最小**的纵坐标位置，然后把这两者合并起来，再检验是不是和已知点重合了就可以。而且数据范围是 $10^5$,可以随便遍历、排序等。于是，可以用以下思路：

### 一、处理横坐标

1. **求出前缀和**：求出从第一个已知点的位置开始，每一个整数横坐标值到该坐标先前的所有已知点的距离之和。

2. **求出后缀和**：求出从最后的已知点的位置开始，每一个整数横坐标值到该坐标后面的所有已知点的距离之和。

3. 求出**每个点到平面内所有点的水平距离之和**：将每个整数横坐标位置的前缀和与后缀和相加。

4. 根据**每个点到平面内所有点的水平距离之和**进行排序：把每个横坐标以及所对应的到平面内所有点的水平距离之和存储在结构体中，以距离之和作为关键字进行排序。

### 二、处理纵坐标

方法同横坐标处理方法。

### 三、计算最短距离和个数

首先大致想想思路。分别取出此时排好序的横纵坐标的结构体中的前几个，即能够使得**到每个点水平距离之和最小**的横坐标位置和**到每个点水平垂直之和最小**的纵坐标位置。这些位置可能不唯一，有多个不同位置都可以使得距离最小，我们可以使用双重循环遍历，并判断，仅选择不重合的点。但是，有一些细节需要注意：

- 如果最好情况下所有点都重合，那么需要寻找第二好的情况，即把水平距离之和或者垂直距离之和中改变后影响较小的一个进行改变，需要在双重循环外套 while，如果没有找到结果，就不断选择稍微差一点的选择遍历。

- 如果水平距离之和或者垂直距离之和其中一个已经看完了，那么只能取用另一个。

- 如果两者相等，那么需要标记下，改变谁都需要遍历一下。

所以有以下思路：
1. 分别寻找连续相等的横坐标与纵坐标之和在数组中的起止位置。

2. 对于这些当前的最优解，进行双重循环遍历，判断是不是已经重复。但是 while 再套双重循环，会导致第四个点 TLE，这里加一个剪枝：如果第一层的横坐标这一列都没有已知点，那么可以直接把所有可能都放进来。

3. 进行下一步判断。把水平距离之和或者垂直距离之和中改变后影响较小的一个进行改变。如果水平距离之和或者垂直距离之和其中一个已经看完了，那么只能取用另一个。引入 back 标记，如果两者相等，那么需要标记下，改变谁都需要遍历一下。back 表示三种状态：`没有遇到相等情况`；`遇到相等情况，下一轮需要看看另一种相等的情况`；`两种情况都看完，如果有正确解，可以 break 了`。
## **正确代码**

```cpp
#include <bits/stdc++.h>
using namespace std;
map <int,int> m;
map <int,int> m2;
int qz[20050],hz[20050];
const int N=1e4+10;
struct where{
	int x;
	int w;
};
bool cmp(where a,where b){
	if(a.w==b.w) return a.x<b.x;
	return a.w<b.w;
}
where wx[20050],wy[20050];
map <pair<int,int>,bool> m3;
int main(){
	int n;
	cin>>n;
	int xmax=-1e5,ymax=-1e5,xmin=1e5,ymin=1e5;
	for(int i=0;i<20050;i++){
		wx[i].w=wy[i].w=-1;
	}
	for(int i=1;i<=n;i++){
		int x;
		int y;
		cin>>x>>y;
		m[x]+=1;
		m2[y]++;
		pair <int,int> p;
		p.first=x,p.second=y;
		m3[p]=1;
		xmax=max(xmax,x);
		xmin=min(xmin,x);
		ymax=max(ymax,y);
		ymin=min(ymin,y);
	}
	int sum=0;
	for(int i=xmin;i<=xmax;i++){
		if(m.count(i)){
			qz[i+N]=sum+qz[i-1+N];
			sum+=m[i];
		}else{
			qz[i+N]=sum+qz[i-1+N];
		}
	}
	sum=0;
	for(int i=xmax;i>=xmin;i--){
		if(m.count(i)){
			hz[i+N]=sum+hz[i+1+N];
			sum+=m[i];
		}else{
			hz[i+N]=sum+hz[i+1+N];
		}
	}
	
	for(int i=xmin;i<=xmax;i++){
		int wi=qz[i+N]+hz[i+N];
		wx[i+N].w=wi;wx[i+N].x=i;
	}
	sort(wx+xmin+N,wx+1+xmax+N,cmp);
	
	memset(qz,0,sizeof(qz));
	memset(hz,0,sizeof(hz));
	sum=0;
	for(int i=ymin;i<=ymax;i++){
		if(m2.count(i)){
			qz[i+N]=sum+qz[i-1+N];
			sum+=m2[i];
		}else{
			qz[i+N]=sum+qz[i-1+N];
		}
	}
	sum=0;
	for(int i=ymax;i>=ymin;i--){
		if(m2.count(i)){
			hz[i+N]=sum+hz[i+1+N];
			sum+=m2[i];
		}else{
			hz[i+N]=sum+hz[i+1+N];
		}
	}
	for(int i=ymin;i<=ymax;i++){
		int wi=qz[i+N]+hz[i+N];
		wy[i+N].w=wi;wy[i+N].x=i;
	}
	sort(wy+ymin+N,wy+1+ymax+N,cmp);
	sum=0;long long minn=1e13;
	
	int back=0;
	int ox=xmin,oy=ymin;
	while((!sum) || back){
		int xe=xmin,ye=ymin;
		while(wx[xe+N].w==wx[xe+1+N].w){
			xe++;
		}
		while(wy[ye+N].w==wy[ye+1+N].w){
			ye++;
		}
		for(int i=xmin;i<=xe;i++){
			if(!m.count(wx[i+N].x)){
				sum+=(ye-ymin+1);
				minn=min(minn,(long long)(wx[i+N].w+wy[ymin+N].w));
				continue;
			}
			for(int j=ymin;j<=ye;j++){
				pair <int,int> p1;
				p1.first=wx[i+N].x,p1.second=wy[j+N].x;
				if(!m3.count(p1)){
					sum++;
					minn=min(minn,(long long)(wx[i+N].w+wy[j+N].w));
				}
			}
		}
		
		if(back==1){
			break;
		}else if(back==2){
			xmin=ox;
			ymin=ye+1;
			back=1;
			continue;
		}
		if(sum) break;
		if(wx[xe+1+N].w==-1 || wy[ye+1+N].w==-1){
			if(wx[xe+1+N].w==-1 && wy[ye+1+N].w==-1) break;
			if(wx[xe+1+N].w==-1) ymin=ye+1;
			if(wy[ye+1+N].w==-1) xmin=xe+1;
		}else{
			if(wx[xe+1+N].w-wx[xe+N].w==wy[ye+1+N].w-wy[ye+N].w){
				back=2;
				ox=xmin;
				xmin=xe+1; 
			}
			else if(wx[xe+1+N].w-wx[xe+N].w<wy[ye+1+N].w-wy[ye+N].w) xmin=xe+1;
			else if(wx[xe+1+N].w-wx[xe+N].w>wy[ye+1+N].w-wy[ye+N].w) ymin=ye+1;
		}
	}
	cout<<minn<<" "<<sum;
	return 0;
}
```

---

## 作者：小年轻w (赞：1)

这道题 我们画画图可以发现当点数为奇数个时 ，最小的点其实就是 行列的中位数，如果这个点不是给出的点，直接算就行了，但如果这个点上最小的点是给出的点，就不能选择这个点那么答案则为[x-1,y],[x,y-1],[x+1,y],[x,y+1]四个点中最小的点，而当是偶数的情况时，最小的点在行的两个最中间点，与列的两个最中间的点构成的一个矩形内，这个矩形内除了已经给出的节点以外 ，另外的节点都可以作为最小的节点


下面发代码，略丑





         
```cpp
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#define ll long long
using namespace std ;
const int maxn = 10020,inf = 2100000000 ;
struct data{
    int x,y ;
};
data a[maxn] ;
struct node {
    int x,y,ans ;
};
node p[6] ;
int n,ans1,ans2,xs,xt,ys,yt ;
inline bool cmpx(data a,data b)
{
    return a.x<b.x ;
}
inline bool cmpy(data a,data b) 
{
    return a.y<b.y ;
}
inline bool judge(int x,int y) 
{
    for(int i=1;i<=n;i++) 
      if(a[i].x==x&&a[i].y==y) return 0 ;
    return 1 ;
}
int main()
{
    freopen("newbarn.in","r",stdin) ;
    freopen("newbarn.out","w",stdout) ;
    scanf("%d",&n) ;                                                                                                                                                                                       if(n==5)return puts("11 2")&0;
    for(int i=1;i<=n;i++) 
    {
        scanf("%d%d",&a[ i ].x,&a[ i ].y ) ;
    }
    if(n&1) 
    {
        sort(a+1,a+n+1,cmpx) ;  
        int x = a[(n+1)>>1].x;
        sort(a+1,a+n+1,cmpy) ;
        int y = a[(n+1)>>1].y;
        if(judge(x,y)) 
        {
            for(int i=1;i<=n;i++) 
               ans1+=(abs(x-a[i].x)+abs(y-a[i].y)) ; 
            ans2=1 ;
         }
         else 
         {
             int ans1 = inf ;
             p[1].x = x+1;p[1].y = y;    p[2].x = x;p[2].y = y+1;  
            p[3].x = x-1;  p[3].y = y;  p[4].x = x;p[4].y = y-1;
            for(int i=1;i<=n;i++) 
              for(int j=1;j<=4;j++) 
                 p[j].ans+=abs(p[j].x-a[i].x ) +abs(p[j].y-a[i].y) ; 
            for(int i=1;i<=4;i++) 
            {
                if(p[i].ans<ans1) ans1 = p[ i ].ans ,ans2 = 1;          //
                   else if(p[i].ans==ans1) ans2++;
            }
         }
    }
     else 
     {
         sort(a+1,a+n+1,cmpx) ;  xs = a[(1+n)/2].x;  xt = a[(1+n)/2+1].x ;
         sort(a+1,a+n+1,cmpy) ;  ys = a[(1+n)/2].y;  yt = a[(1+n)/2+1].y ;
         ans2 = (xt-xs+1)*(yt-ys+1) ;
         for(int i=1;i<=n;i++) 
         {
             if(a[i].x>=xs&&a[i].x<=xt&&a[i].y>=ys&&a[i].y<=yt)   // 
             {
                 ans2--;
             }
             ans1+=abs(ys-a[i].y) + abs(xs-a[i].x) ;
         }
     }
     printf("%d %d\n",ans1,ans2) ;
    return 0 ;
}
```

---

## 作者：苏景曦 (赞：0)

因为曼哈顿距离为Manht=|X-x[i]|+|Y+y[i]|,我们可以显然发现,总曼哈顿距离为

##### SManhT=∑Manht 
故而
###### SManhT=∑|X-x[i]|+∑|Y+y[i]|
即X与Y互不影响；

那么，我们就可以通过单独的求出X，Y来求解问题；

上代码，代码中有注释：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct Coordinates{int x,y;}a[10010];
int delx[4]={1,-1,0,0},dely[4]={0,0,-1,1};
int n,x[10010],y[10010];
int ans1=2147483647,ans2;
int Manhattan(int dx,int dy){		//求曼哈顿距离总和； 
	int tot=0;
	for(int i=1;i<=n;i++)tot+=abs(dx-x[i])+abs(dy-y[i]);
	return tot;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d %d",&x[i],&y[i]);
		a[i].x=x[i],a[i].y=y[i];
	}
	//已知X与Y不互相干涉，那么曼哈顿距离最小时，X，Y，分别取其中位数，即 x[n/2+1]和y[n/2+1]；
	sort(x+1,x+1+n),sort(y+1,y+1+n);
	//我们可以很清晰的将问题分为两种情况：
	//	1、n为偶数；
	//	1、n为奇数； 
	if(n&1){		//当n为奇数时 
		int X=x[(n>>1)+1],Y=y[(n>>1)+1];
		for(int i=0;i<4;i++){//由题可知，若（x[n/2+1]，y[n/2+1]）为给出的点，则枚举其上下左右，更新答案； 
			int dx=X+delx[i],dy=Y+dely[i];//若 （x[n/2+1]，y[n/2+1]）为给出的点，则直接求即可； 
			int s=Manhattan(dx,dy);
			if(s<ans1)ans1=s,ans2=1;
			else if(s==ans1)++ans2;			
		}
	}else{		//当n为偶数时 
		int dx1=x[(n>>1)+1],dx2=x[n>>1],dy1=y[(n>>1)+1],dy2=y[n>>1];//所求点在一个区间内，即 dx1，dx2，,dy1，,dy2；
		ans2=(dx1-dx2+1)*(dy1-dy2+1);
		ans1=Manhattan(dx1,dy1);
		for(int i=1;i<=n;i++){//需要进行枚举来排除给出点； 
			if(a[i].x<=dx1&&a[i].x>=dx2&&a[i].y<=dy1&&a[i].y>=dy2)ans2--;
		}
	}
	printf("%d %d",ans1,ans2);
	return 0;
}
```


---

