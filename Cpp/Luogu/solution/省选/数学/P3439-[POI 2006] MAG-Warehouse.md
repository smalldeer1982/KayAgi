# [POI 2006] MAG-Warehouse

## 题目描述

The streets of the New Byte City form a rectangular grid - those running east-west are simply called streets, while those running north-south are called avenues. To avoid mistakes, we shall call them h-streets and v-streets, respectively. The v-streets are numbered from $1$ to $500\ 000\ 000$ eastwards. Similarly, the h-streets are numbered from $1$ to $500\ 000\ 000$ northwards. Every v-street crosses every h-street and, conversely, every h-street crosses every v-street. The distance between two consecutive v-streets, as well as between two consecutive h-streets, is exactly one kilometre.

 ![](https://cdn.luogu.com.cn/upload/pic/6964.png) 

There are $k$ shops in the city, each one of them is situated at a crossroads. Byteasar, the merchant, supplies every single one of the $k$ shops, and furthermore he returns to some of them several times a day with fresh supplies. Recently he has decided to have a warehouse built, from which the goods would be delivered. For obvious reasons, it should stand at a crossroads. The lorry loaded with goods can supply only one shop per course - it leaves the warehouse, delivers to the shop and returns to the warehouse. The lorry always picks the shortest path from the warehouse to the shop, and the shortest one back (possibly the same one). The distance between points $(x_i, y_i)$ and $(x_j, y_j)$ equals $\max \{ |x_i - x_j|, |y_i - y_j| \}$.

TaskWrite a programme that:

reads the locations of shops, as well as the numbers of their daily deliveries, from the standard inputdetermines such a warehouse's position that the summary distance of the lorry's daily route is minimal,writes the result to the standard output.

给定一个网格图，其上有一堆坏点(整点，同一位置多个)，求一个整点，使得该整点到所有的坏点的**切比雪夫距离**之和最小。

求这个整点位置。(横纵坐标最大)


## 说明/提示

感谢@oscar 提供SPJ


## 样例 #1

### 输入

```
3
2 2 1
6 2 1
4 6 1```

### 输出

```
4 4```

# 题解

## 作者：_LiWenX_ (赞：2)

来点无脑做法。

首先把切比雪夫距离转化成曼哈顿距离。

具体来说，对于点 $(x_1,y_1)$ 与 $(x_2,y_2)$ 的切比雪夫距离等于点 $(\frac{x_1+y_1}{2},\frac{x_1-y_1}{2})$ 与 $(\frac{x_2+y_2}{2},\frac{x_2-y_2}{2})$ 的曼哈顿距离。

那么现在可以把所有点 $(x_i,y_i)$ 换成 $(x_i+y_i,x_i-y_i)$，问题就变成了找一个点，使得曼哈顿距离最小，注意我这里是没有除以二的，最后要除回去才对。

变成曼哈短距离最大的好处就是把横纵坐标的 $\max$ 换成了加法，这使得我们可以横纵坐标分别考虑。

先做答案的横坐标 $x$，那么纵坐标问题是对称的，我们现在只考虑横坐标咋做，我们要最小化：

$$\sum\limits_{i=1}^n|x_i-x|k_i$$

直接把 $k_i$ 看做是有 $k_i$ 个 $x_i$，那么就是数轴上有若干个点，我们要求一个点使得到所有点的距离之和最小，根据初中数学老师告诉我们的结论，直接取中间的那个点即可，证明还是很简单的，可以考虑若干个绝对值函数加起来，最小值必然在斜率为 $0$ 的点上，那么这个点必然是中点。

于是就做完了。

但是还有一个问题，最后复原答案的时候有一步要除一个 $2$，这样可能会使得和真实的答案相差 $O(1)$ 个位置，直接暴力判断周围距离不超过 $2$ 的点中最优的那一个即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
struct node{
	int x,k;
}a[100005],b[100005];
int x[100005],y[100005],k[100005];
signed main(){
	cin>>n;
	__int128 s=0;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i]>>k[i];
		s+=k[i];
		a[i].x=x[i]+y[i];
		b[i].x=x[i]-y[i];
		a[i].k=b[i].k=k[i];
	}
	sort(a+1,a+1+n,[](node x,node y){
		return x.x<y.x;
	});
	sort(b+1,b+1+n,[](node x,node y){
		return x.x<y.x;
	});
	int pos1=0,pos2=0,t=0;
	for(int i=n;i;i--){
		t+=a[i].k;
		if(t*2>=s){
			pos1=a[i].x;
			break;
		}
	}
	t=0;
	for(int i=n;i;i--){
		t+=b[i].k;
		if(t*2>=s){
			pos2=b[i].x;
			break;
		}
	}
	int X=pos1+pos2;
	int Y=pos1-pos2;
	X>>=1,Y>>=1;
	__int128 minn=1e30;
	int ansx=0,ansy=0;
	for(int i=-2;i<=2;i++){
		for(int j=-2;j<=2;j++){
			if(X+i<1||X+i>5e8||Y+j<1||Y+j>5e8) continue;
			s=0;
			for(int p=1;p<=n;p++){
				s+=max(abs(X+i-x[p]),abs(Y+j-y[p]))*k[p];
			}
			if(s<minn){
				minn=s;
				ansx=X+i;
				ansy=Y+j;
			}
		}
	}
	cout<<ansx<<' '<<ansy<<'\n'; 
}
```

---

## 作者：oscar (赞：2)

【POI补全计划#23 POI2006 MAG】

~~终于有道（我会做的）没人做的题了~~

这题的思路很妙，嘿嘿

一开始看到“切比雪夫距离”我也是一脸懵○，心想着如果是曼哈顿距离我就会做了

嗯...先来讲讲曼哈顿距离的情况怎么做

我们发现曼哈顿距离对于x方向和y方向是独立的，于是转换成一维情况

一维情况就很好解决了（类似中位数，调整法可证）

--------------------分割线----------------------------

那么切比雪夫距离怎么做呢？

我们来把到一个点切比雪夫距离为k的所有点画出来，发现是一个正着放的正方形

再把所有到一个点曼哈顿距离为k的所有点画出来，发现是一个转了45度的正方形


emmmmmmm...

这样就好办了，只需要把坐标系转45度，求新坐标系下的曼哈顿距离版本问题就好了


什么？你问我怎么转45度？

只需要将坐标轴改为x+y和x-y即可（最后不要忘了转回来）


最后有一点细节需要注意

求出来的答案可能不是整点，需要额外验证一下附近的点（x坐标±1，y坐标±1（开区间），共1或4个整点）

（写个SPJ还得用\_\_int128 ......）

贴代码：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100010;
struct pt
{
    int x,y,cnt;
}a[MAXN],b[MAXN],c[MAXN];
int n;
inline bool cmpx(const pt &a,const pt &b)
{
    return a.x<b.x;
}
inline bool cmpy(const pt &a,const pt &b)
{
    return a.y<b.y;
}
inline long long check(int x,int y)
{
    unsigned long long ret=0;
    for(int i=1;i<=n;i++)
    {
        ret+=max(abs(x-c[i].x),abs(y-c[i].y))*(long long)c[i].cnt;
    }
    return ret;
}
int main()
{
    int u,v,w;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        a[i].x=u+v,a[i].y=u-v,a[i].cnt=w;
        b[i].x=u+v,b[i].y=u-v,b[i].cnt=w;
        c[i].x=u,c[i].y=v,c[i].cnt=w;
    }
    sort(a+1,a+n+1,cmpx);
    sort(b+1,b+n+1,cmpy);
    int posx,posy;
    int l=1,r=n;//d:l-r
    while(l<r)
    {
        if(a[l].cnt<a[r].cnt)
        {
            a[r].cnt-=a[l].cnt;
            l++;
        }
        else if(a[l].cnt>a[r].cnt)
        {
            a[l].cnt-=a[r].cnt;
            r--;
        }
        else
        {
            l++;
            r--;
        }
    }
    posx=a[l].x;
    l=1,r=n;
    while(l<r)
    {
        if(b[l].cnt<b[r].cnt)
        {
            b[r].cnt-=b[l].cnt;
            l++;
        }
        else if(b[l].cnt>b[r].cnt)
        {
            b[l].cnt-=b[r].cnt;
            r--;
        }
        else
        {
            l++;
            r--;
        }
    }
    posy=b[l].y;
    int xx=(posx+posy)/2,yy=(posx-posy)/2;
    unsigned long long sum1=check(xx,yy),
                       sum2=check(xx+1,yy),
                       sum3=check(xx,yy+1),
                       sum4=check(xx+1,yy+1),
                       minn=0xffffffffffffffffllu;
    int mins=0;
    if(sum1<minn)mins=1,minn=sum1;
    if(sum2<minn)mins=2,minn=sum2;
    if(sum3<minn)mins=3,minn=sum3;
    if(sum4<minn)mins=4,minn=sum4;
    if(mins==1)printf("%d %d\n",xx,yy);
    if(mins==2)printf("%d %d\n",xx+1,yy);
    if(mins==3)printf("%d %d\n",xx,yy+1);
    if(mins==4)printf("%d %d\n",xx+1,yy+1);
    return 0;
}
```

---

## 作者：John_Smith (赞：0)

通过这篇 [常用距离算法详解](https://www.luogu.com.cn/blog/xuxing/Distance-Algorithm)，我们可以将 **切比雪夫距离** 转换为 **曼哈顿距离**。

为了防止掉精度，我们需要将原坐标系中的点 $(x,y)$ 转化为 $(x+y,x-y)$ 而不是 $(\frac{x+y}{2} , \frac{x-y}{2})$。

然后可以将两个维度分开来算。此处以 $x$ 为例

假设我们选出的坐标为 $x$。

我们假设把每个坐标拆成 $t_i$ 个点。

将所有 $x_i$ 排序。

我们要使 $\sum_{i=1}^{n} | x-x_i |$ 最小。

根据初一的知识，我们可以得出 $x=x_{\lfloor \frac n2 \rfloor}$。

当然，根据数据范围，拆点行不通，所以可以先求出 $t$ 的前缀和再二分查找。

根据上述过程，我们可以得出在曼哈顿距离的坐标下的答案 $(x_{ans},y_{ans})$。

但是注意到我们在之前的处理中并没有除以二，所以的出来的可能不是整点。

此处运用了 oscar 大佬的方法，直接暴力判断点就好了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
#define int long long
#define rep(i,a,b) for(register int i=a;i<=b;++i)
#define Rep(i,a,b) for(register int i=a;i>=b;--i)
inline int read()
{
    bool f=0;int x=0;char ch;
    do{ch=getchar();f|=(ch=='-');}while(!isdigit(ch));
    do{x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}while(isdigit(ch));
    return f?-x:x;
}
inline void write(int x)
{
    if(x<0)x=-x,putchar('-');
    if(x>9)write(x/10);putchar(x%10+'0');
}
inline void writesp(int x)
{
	write(x);putchar(' ');
}
inline void writeln(int x)
{
	write(x);puts("");
}
struct node1
{
	int x;
	int t;
	bool operator <(const node1 &b)const
	{
		return x<b.x;
	}
}x[maxn];
struct node2
{
	int y;
	int t;
	bool operator <(const node2 &b)const
	{
		return y<b.y;
	}
}y[maxn];
int qx[maxn],qy[maxn],qz[maxn];
int n;
int sumx[maxn],sumy[maxn];
int check(int xx,int yy)
{
	int ans=0;
	rep(i,1,n)
	{
		ans+=max(abs(xx-qx[i]),abs(yy-qy[i]))*qz[i];
	}
	return ans;
}
signed main()
{
	n=read();
	rep(i,1,n)
	{
		int a=read(),b=read();
		x[i].x=a+b;y[i].y=a-b;
		qz[i]=x[i].t=y[i].t=read();
		qx[i]=a;qy[i]=b;
	}
	sort(x+1,x+1+n);
	sort(y+1,y+1+n);
	rep(i,1,n)sumx[i]=sumx[i-1]+x[i].t;
	rep(i,1,n)sumy[i]=sumy[i-1]+y[i].t;
	int tempx=sumx[n],tempy=sumy[n];
	rep(i,1,n)sumx[i]<<=1;
	rep(i,1,n)sumy[i]<<=1;
	int posx=lower_bound(sumx+1,sumx+1+n,tempx)-sumx;
	int posy=lower_bound(sumy+1,sumy+1+n,tempy)-sumy;
	int sx=x[posx].x,sy=y[posy].y;
	int nx=((sx+sy)/2),ny=((sx-sy)/2);
	int ans1=check(nx,ny),ans2=check(nx+1,ny),ans3=check(nx,ny+1),ans4=check(nx+1,ny+1);
	if(ans4<=ans3&&ans4<=ans2&&ans4<=ans1)     printf("%d %d\n",nx+1,ny+1);
	else if(ans3<=ans4&&ans3<=ans2&&ans3<=ans1)printf("%d %d\n",nx,ny+1);
	else if(ans2<=ans4&&ans2<=ans3&&ans2<=ans1)printf("%d %d\n",nx+1,ny);
	else if(ans1<=ans2&&ans1<=ans3&&ans1<=ans4)printf("%d %d\n",nx,ny);
	return 0;
}
```

---

