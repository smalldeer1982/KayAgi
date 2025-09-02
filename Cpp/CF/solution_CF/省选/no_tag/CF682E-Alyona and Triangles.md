# Alyona and Triangles

## 题目描述

给定 n 个点，坐标都是整数， n 个点中任取 3 个点构成的三角形的面积都不超过 S 。

要求构造出一个三角形覆盖这 n 个点，并且面积不超过 4S 。该三角形的顶点可以不是这 n 个给定点。

## 样例 #1

### 输入

```
4 1
0 0
1 0
0 1
1 1
```

### 输出

```
-1 0
2 0
0 2```

# 题解

## 作者：xzggzh1 (赞：5)

这个题除了 @辰星凌 的做法，还有更加简单的做法。

首先，稍微有点几何基础的人都知道，只要找到最大的三角形，再让这个三角形向三遍各扩展一倍，就找不到不被大三角形包含的点。


然后就是如何找到最大的三角形。

其实有一种比较简洁的方法：先任意取三个点，然后每次遍历所有点，如果这个点把三个点之中的一个点换掉可以使得三角形扩大，那就保留换的操作。

注意到 $n\leq5000$ ,在对算法略加分析，发现时间其实很充裕。跑得最慢的点不到50ms。

下面是核心代码:

```cpp
int  ar(int a,int b,int c){return abs((x[b]-x[a])*(y[c]-y[a])-(y[b]-y[a])*(x[c]-x[a]));}
void finds()
{
    a=1;b=2;c=3;
    int flag=0;
    while(1)
    {
        flag=0;
        for(int i=1;i<=n;i++)
        {
            if(ar(i,b,c)>ar(a,b,c))a=i,flag=1;
            if(ar(a,i,c)>ar(a,b,c))b=i,flag=1;
            if(ar(a,b,i)>ar(a,b,c))c=i,flag=1;
        }
        if(flag == 0)break;
    }
}
```


---

## 作者：辰星凌 (赞：2)

# **【题解】Alyona and Triangles [CF682E]**

[$\mathcal{My}\ \mathcal{Blog}$](https://www.cnblogs.com/Xing-Ling/p/12646815.html)

传送门：[$\text{Alyona and Triangles}$](https://www.luogu.com.cn/problem/CF682E) [$\text{[CF682E]}$](http://codeforces.com/problemset/problem/682/E)

## **【题目描述】**

二维平面上给定 $n$ 个点， 满足从中任取 $3$ 个点所构成的三角形的面积都不超过 $\text{S}$ 。

要求构造一个三角形覆盖这 $n$ 个点，并且面积不超过 $\text{4S}$ 。三角形顶点可以取二维平面上的任意整数坐标。

## **【分析】**

[【学习笔记】计算几何全家桶](https://www.luogu.com.cn/blog/ChenXingLing/post-xue-xi-bi-ji-ji-suan-ji-he-quan-jia-tong)

计算几何水题（~~毒瘤程度不及 SCOI 的万分之一~~）。

经过一番手推+盲猜，发现一个性质：先求出在这 $n$ 个点中任取三个点所能构成的最大三角形，然后将其扩大成原来的四倍即为答案（分别以三条边作为对角线画四边形所并成的大三角）。

如样例，红色部分为求出的最大三角，对其进行扩展得到答案（蓝色大三角）：

![](https://cdn.luogu.com.cn/upload/image_hosting/1akwha1t.png)

易证所有点都一定会被包含在大三角中（如果在外面还有其他点，那么红三角就一定不是最大的，前后矛盾）。

于是问题转换为：用给定点构造一个最大三角形。

可知最大三角的顶点都在凸包上，直接暴力枚举一条边，用类似旋转卡壳的方法求出距离该直线最远的点，然后取最大的一个即可。

## **【Code】**

```cpp
#include<algorithm>
#include<cstdio>
#include<cmath>
#define LD double
#define LL long long
#define Vector Point
#define Re register int
using namespace std;
const int N=5e3+3;
int n;LL S;
const LD eps=1e-8;
inline int dcmp(LD a){return a<-eps?-1:(a>eps?1:0);}//处理精度
struct Point{
    LD x,y;Point(LD X=0,LD Y=0){x=X,y=Y;}
    inline void in(){scanf("%lf%lf",&x,&y);}
    inline void print(){printf("%.lf %.lf\n",x,y);}
}A,B,C,P[N],cp[N];
inline LD Cro(Vector a,Vector b){return a.x*b.y-a.y*b.x;}//【叉积】
inline Vector operator+(Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
inline Vector operator-(Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
inline bool cmp(Point a,Point b){return a.x!=b.x?a.x<b.x:a.y<b.y;}//按坐标排序
inline int ConvexHull(Point *P,Re n,Point *cp){//【Graham扫描法】求凸包
    sort(P+1,P+n+1,cmp);
    Re t=0;
    for(Re i=1;i<=n;++i){//下凸包
        while(t>1&&dcmp(Cro(cp[t]-cp[t-1],P[i]-cp[t-1]))<=0)--t;
        cp[++t]=P[i];
    }
    Re St=t;
    for(Re i=n-1;i>=1;--i){//上凸包
        while(t>St&&dcmp(Cro(cp[t]-cp[t-1],P[i]-cp[t-1]))<=0)--t;
        cp[++t]=P[i];
    }
    return --t;//要减一
}
int main(){
//    freopen("123.txt","r",stdin);
    scanf("%d%lld",&n,&S);
    for(Re i=1;i<=n;++i)P[i].in();
    Re cnt=ConvexHull(P,n,cp);
    LD Max=0;
    for(Re i=1;i<=cnt;++i)//枚举三角形一条边cp[i]cp[j]
        for(Re j=i+1,k=j<cnt?j+1:1;j<=cnt&&k!=i;++j){
            while(dcmp(Cro(cp[j]-cp[i],cp[k]-cp[i])-Cro(cp[j]-cp[i],cp[k+1]-cp[i]))<0)k=k<cnt?k+1:1;
            if(k!=i&&k!=j){
                LD tmp=Cro(cp[j]-cp[i],cp[k]-cp[i]);//计算三角形面积
                if(tmp>Max)Max=tmp,A=cp[i],B=cp[j],C=cp[k];
            }
        }
    (A-C+B).print(),(B-A+C).print(),(C-B+A).print();
}
```


---

## 作者：Erotate (赞：1)

### Solutions

其实题目里的 $S$ 没什么用。

我们只需要找到这 $n$ 个点所能构成的面积最大的三角形，然后把它的边长变成原来的两倍，扩大后的三角形就是我们要找的三角形。

证明：

如果还有一个点不能被找的三角形覆盖，那么以这个点为其中一个顶点所构成的三角形面积会比以原先选的三个点为顶点的三角形面积要大，所以原先选的三个点构成的三角形面积就不是最大的，矛盾，即所有点都能被覆盖。

对于如何把边长扩大两倍，只需要将原三角形沿着三边分别对称过去即可。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=5e3+5;
struct node{
	int x,y;
}pos[N];
int n,S,a=1,b=2,c=3;
int gt(int fir,int sec,int thi){
	return abs((pos[sec].x-pos[fir].x)*(pos[thi].y-pos[fir].y)-(pos[sec].y-pos[fir].y)*(pos[thi].x-pos[fir].x));
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>S;
	for(int i=1;i<=n;++i) cin>>pos[i].x>>pos[i].y;
	while(1){
		bool flag=0;
		for(int i=1;i<=n;++i){
			if(gt(i,b,c)>gt(a,b,c)){
				a=i;
				flag=1;
			}
			if(gt(a,i,c)>gt(a,b,c)){
				b=i;
				flag=1;
			}
			if(gt(a,b,i)>gt(a,b,c)){
				c=i;
				flag=1;
			}
		}
		if(!flag) break;
	}
	cout<<pos[b].x+pos[c].x-pos[a].x<<" "<<pos[b].y+pos[c].y-pos[a].y<<endl<<pos[a].x+pos[c].x-pos[b].x<<" "<<pos[a].y+pos[c].y-pos[b].y<<endl<<pos[a].x+pos[b].x-pos[c].x<<" "<<pos[a].y+pos[b].y-pos[c].y<<endl;
	return 0;
}
```


---

## 作者：ethan0328 (赞：1)

## 思路

首先，观察到三角形面积不超过 $4S$，于是考虑到先求出一个面积不超过 $S$ 的三角形，再把它扩大 $4$ 倍，也就是把它的每个顶点向对边做对称。

然后就很容易想求出最大三角形，然后把它扩大 $4$ 倍。

这时你发现 $S$ 屁用没有，因为 $n$ 个点中任取 $3$ 个点构成的三角形的面积都不超过 $S$。

考虑如何求最大三角形，考虑先乱选三个点 $A,B,C$ 作为最大三角形顶点。

每加入一个点 $D$，比较 $\Delta ABC,\Delta ABD,\Delta ADC,\Delta DBC$ 的面积大小，并更新 $A,B,C$ 为最大的三角形的三个顶点。

最后，别忘开 `long long`，~~我就是因为这个调了半天~~。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+10;
struct point
{
	int x,y;
};
int n;
point ar[N];
double ss(point a,point b,point c)
{
	return abs((double)(b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x));
}
signed main()
{
	int t1;
	point a1,a2,a3,a4,a,Qb,c;
	cin>>n>>t1;
	for(int i=1;i<=n;i++)
	{
		cin>>ar[i].x>>ar[i].y;
	}
	a1=ar[1];a2=ar[2];a3=ar[3];
	while(true)
	{
		bool flg=0;
		for(int i=1;i<=n;i++)
		{
			a4=ar[i];
			if(ss(a1,a2,a3)<ss(a1,a2,a4))
			{
				a3=a4;
				flg=1;
			}
			if(ss(a1,a2,a3)<ss(a1,a4,a3))
			{
				a2=a4;
				flg=1;
			}
			if(ss(a1,a2,a3)<ss(a4,a2,a3))
			{
				a1=a4;
				flg=1;
			}
		}
		if(!flg)
		{
			break;
		}
	}
	cout<<a3.x+a2.x-a1.x<<" "<<a3.y+a2.y-a1.y<<"\n";
	cout<<a1.x+a3.x-a2.x<<" "<<a1.y+a3.y-a2.y<<"\n";
	cout<<a1.x+a2.x-a3.x<<" "<<a1.y+a2.y-a3.y;
}
```


---

## 作者：az__eg (赞：0)

提供一种比较无脑且好写的方法。

求出最大的三角形，然后倍长中线。

求三角形提供一种不一样的做法：首先先求凸包，然后考虑枚举凸包上两个点，然后三分即可，因为凸包有凸性，所以是单峰函数。时间复杂度 $O(n^2 \log n)$。能过。

然后证明以下构造方法的正确性：

![](https://cdn.luogu.com.cn/upload/image_hosting/11xns8d3.png)

假设 $\triangle ABC$ 是我们找到面积最大的三角形，我们先倍长中线，$S_{\triangle AEC}=S_{\triangle ABC}=S_{\triangle BCD}$，我们发现如果有点在 $BE$ 或 $EC$ 外，设其为点 $G$，那么 $S_{\triangle GAC} > S_{\triangle ABC}$，不符合我们指定的条件，所以证明了这个方案一定是对的。

代码：[https://codeforces.com/contest/682/submission/206602235](https://codeforces.com/contest/682/submission/206602235) 。

---

