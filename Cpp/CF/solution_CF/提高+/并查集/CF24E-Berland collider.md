# Berland collider

## 题目描述

在 $x$ 轴上有 $n$ 个点，每个点向左或向右发射子弹，给定每个点的坐标 $x_i$ 和所发射子弹的飞行速度 $v_i$，问所有相向而行的的子弹中最短的相遇时间。

## 样例 #1

### 输入

```
3
-5 9
0 1
5 -1
```

### 输出

```
1.00000000000000000000
```

## 样例 #2

### 输入

```
6
1 3
2 3
3 3
4 -3
5 -1
6 -100
```

### 输出

```
0.02912621359223301065
```

# 题解

## 作者：Siyuan (赞：6)

## 本题思路：
1. 判断所有物体是否运动方向均一致，注意题目中的“**以坐标递增顺序列出**”，具体$\ O(n)$的判断方法见代码。
2. 很显然，此题正解是二分答案，下界为$\ 0$，上界为$\ 1e9$。循环的条件为`fabs(r-l)>1e-10`（答案误差在$\ 1e-9$）。
3. 每次二分得到一个**时间**，维护向右移动的物体的最大最终坐标$\ rr$。如果遇到向左运动的物体，那么计算它的最终坐标$\ ll$。如果$\ rr>ll$，说明有两者会相遇，更新答案上界。否则意味着此时的时间不满足条件，更新答案下界。

--------

### 代码如下：

$PS$：感谢 @浪浪更健康0106 的思路和代码参考

```
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAXN=5*1e5+10;
int n,x[MAXN],v[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&x[i],&v[i]);
	bool flg=0;
	for(int i=1;i<=n;i++)
		if(v[i]>0)
		{
			for(int j=i+1;j<=n;j++)
				if(v[j]<0){flg=1;break;}
			break;
		}
	if(!flg)  return puts("-1"),0;
    
	double l=0,r=1e9;
	while(fabs(r-l)>1e-10)
	{
		double mid=(l+r)/2;
		double ll=0,rr=-1e30;
		bool flg=0;
		for(int i=1;i<=n;i++)
		{
			if(v[i]>0)  rr=max(rr,x[i]+v[i]*mid);
			else{
				//这样写是错的 -> ll=min(ll,x[i]+v[i]*mid);
                //因为这样可能会使结果变小，每次判断的应该是当前物体的最终坐标。
				ll=x[i]+v[i]*mid;
				if(rr>ll)
				{
					r=mid;
					flg=1;
					break;
				}
			}
		}
		if(!flg)  l=mid;
	}
	printf("%.20lf",r);
	return 0;
}
```

---

## 作者：_lxy_ (赞：1)

### 分析

将时间二分，对于每一个二分得到的时间，从左至右搜每一个子弹，如果是从左往右飞的，就计算出它在这个时刻的坐标，取所有现坐标的最大值；如果是从右往左飞的，就看目前有没有从左往右飞的子弹此前能和它相遇，也就是比较它的现坐标是否小于从左往右飞子弹的现坐标最大值。如果能相遇，就更新答案，否则继续二分。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=5e5+7;
inline void qread(){}template<class T1,class ...T2>
inline void qread(T1 &a,T2&... b)
{
	register T1 x=0;register bool f=false;char ch=getchar();
	while(ch<'0') f|=(ch=='-'),ch=getchar();
	while(ch>='0') x=(x*10)+(ch^48),ch=getchar();
	x=(f?-x:x);a=x;qread(b...);
}
template<class T>inline T qmax(const T &x,const T &y){return x>y?x:y;}
template<class T>inline T qmin(const T &x,const T &y){return x<y?x:y;}
long long n;
struct node
{
	long double x,v;
	node(){;}
	node(long double _x,long double _v):x(_x),v(_v){}
	bool operator < (const node &o)const{return x<o.x;}
}a[MAXN];
bool check(long double mid)
{
	long double mx=-1e30;
	for(int i=0;i<n;i++)
	{
		if(a[i].v>0) mx=qmax(mx,a[i].x+a[i].v*mid);
		else
		{
			long double t=(a[i].x+a[i].v*mid);
			if(t<mx) return true;
		}
	}
	return false;
}
long double ans;
signed main()
{
	qread(n);int i,j;
	for(i=0;i<n;i++) qread(a[i].x,a[i].v);
	long double l=0,r=1e9+7;
	while(r-l>=1e-10)
	{
		long double mid=(l+r)/2;
		if(check(mid)) ans=r=mid;
		else l=mid;
	}
	if(r==1e9+7) ans=-1;
	printf("%.10Lf\n",ans);
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

首先，要判断是否有相向而行且可能相遇的子弹，这个直接找出最左边的向右的子弹和最右边的向左的子弹的位置判断就行了。

考虑二分答案，二分出一个时间然后转化为可行性问题，即对于这一个时间判断出是否有区间相交。

区间相交可以使用 $O(n)$ 的判断方法，从左向右扫描所有的区间，维护最右边的向右飞的子弹，没当遇到一个向左的子弹，判断这两个位置是否有交集，有则可以预见，反之不行。

----
### 代码：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
long long n,x[500005],v[500005];
bool check(long double tim){
	long double rt=0,fi=0;
	for(int i=1;i<=n;i++){
		if(v[i]>0){
			if(fi==0)rt=(long double)x[i]+(long double)v[i]*tim;
			rt=max(rt,(long double)x[i]+(long double)v[i]*tim),fi=1;
		}else
		if(rt>=(long double)x[i]+(long double)v[i]*tim&&fi)return 1;
	}
	return 0;
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	scanf("%lld%lld",&x[i],&v[i]);
	long double l=0,r=1e9+5,ans,mid;
	while(r-l>=1e-10){
		mid=(l+r)/2;
		if(check(mid))r=mid,ans=mid;
		else l=mid;
	}
	if(r==1e9+5){
		printf("-1\n");
		return 0;
	}
	printf("%.20Lf",ans);
	return 0;
}
```


---

## 作者：Graphcity (赞：0)

## 思路

这道题求的就是这个式子的最小值：（ $x_1,v_1$ 为向右，$x_2,v_2$ 为向左 ）

$$\frac{x_2-x_1}{v_1-v_2}$$

等等...这个式子是不是有点像分数规划？

考虑二分时间。假设

$$\frac{x_2-x_1}{v_1-v_2}\le \text{mid}$$

那么就有

$$
\begin{matrix}
(x_2-x_1)\le \text{mid} \cdot (v_1-v_2) \\
x_2+ \text{mid} \cdot v_2 \le x_1 + \text{mid} \cdot v_1
\end{matrix}
$$

在之前将所有的子弹按照坐标从小到大排序，再按照这个关系二分判断即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=int(5e5);

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,typ[Maxn+5];
struct Node{int a,b;} k[Maxn+5];
inline int cmp(Node x,Node y) {return x.a<y.a;}

inline int Check(double mid)
{
    double res=-1e20; // 注意这里的值要十分小
    for(register int i=1;i<=n;++i)
    {
        if(typ[i]) res=max(res,k[i].a+mid*k[i].b);
        else if(k[i].a+mid*k[i].b<=res) return 1;
    }
    return 0;
}

int main()
{
    n=read();
    for(register int i=1;i<=n;++i)
        k[i].a=read(),k[i].b=read(),typ[i]=(k[i].b>0);
    double l=0.0,r=1e10;
    for(register int i=1;i<=100;++i) // 防止死循环
    {
        double mid=(l+r)/2;
        if(Check(mid)) r=mid;
        else l=mid;
    }
    if(r==1e10) printf("-1");
    else printf("%.12lf",l);
    return 0;
}
```

---

