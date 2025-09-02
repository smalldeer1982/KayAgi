# Inna and Babies

## 题目描述

在一个无限平面上，有 $n$ 个 A 类数对和 $m$ 个 B 类数对。每个数对是一条会随时间而增长的线段。在时间为 $t$ 时，A 类数对 $(x,y)$ 是一条以点 $(x-t, y+t)$ 和 $(x+t, y-t)$ 为端点的线段，B 类数对 $(x,y)$ 是一个以点 $(x+t,y+t)$ 和 $(x-t,y-t)$ 为端点的线段。初始时刻 $t \gets 0$ 时，所有数对都是平面上的点。

你的目标是找到第一个当 $t$ 为整数的时刻，平面上至少有一个面积不为 $0$ 的矩形，矩形的每条边上的每个点都应该至少被一条线段覆盖。一条边可以被多条线段覆盖。**线段包含它们的两个端点。**

给定 $n$ 个 A 类数对和 $m$ 个 B 类数对，
输出最小的满足条件的 $t$。

## 说明/提示

$|x_i,y_i| \le 10^6$。

Translated by liuli688

## 样例 #1

### 输入

```
2 2
2 2
5 5
3 7
5 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 2
2 2
3 2
6 2
4 2
5 2
```

### 输出

```
1
```

# 题解

## 作者：Twig_K (赞：4)

便于处理，我们把每个点 $(x,y)$ 都绕原点旋转 45 度得到 $(\sqrt{2}x-\sqrt{2}y,\sqrt{2}x+\sqrt{2}y)$。

则对于 A 类线段，两端点为 $(\sqrt{2}(x-y-2t),\sqrt{2}(x+y))$ 和 $(\sqrt{2}(x-y+2t),\sqrt{2}(x+y))$，发现 $\sqrt{2}$ 并不影响判断相交，于是直接扔了。

最终 A 类线段端点为 $(x-y-2t,x+y)$ 和 $(x-y+2t,x+y)$，B 类线段端点为 $(x-y,x+y-2t)$ 和 $（x-y,x+y+2t)$。A 类线段水平延伸，B 类线段竖直延伸。

----------------------

先考虑无解的情况。如果找不到两条纵坐标不同（不在同一高度）的水平线，或者找不到两条横坐标不同的竖直线，那么一定无解（无论如何也找不到矩形的边）。否则，只要给足够的时间，一定会产生我们想要的交点。

再考虑有解的情况。如果 $T_0$ 时间能构成矩形，那么任意 $t \geq T_0$ 的时刻都可以构成矩形。可以二分答案 $T$。

关于二分 check 函数，根据要检验的 $T$，得出每个 A 类点和 B 类点延伸成的线段，并**将相交的线段合并成一条**（否则会 WA on test 3）。

我们枚举两条**不在同一直线**（即纵坐标不同）的水平线段，作为矩形的上下边。这个时候我们只需要枚举所有竖直线段，看看是否有两条**不在同一直线**的竖直线段与矩形的上下两边都相交即可。


```cpp
#include<bits/stdc++.h>
#define For(i,il,ir) for(register int i=(il);i<=(ir);++i)
#define mid (L+R>>1)
#define mk make_pair
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
template<typename T>
inline void read(T& x){
	bool f=0;x=0;char ch=getchar();
	while(ch<'0'||ch>'9'){ if(ch=='-') f=1; ch=getchar(); }
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	if(f) x=-x;
}
template<typename T,typename... Args>
void read(T& first,Args&... args){ read(first),read(args...); }
namespace O_O{
	int n,m;
	pll a[2005],b[2005];
	struct node{
		ll d,l,r;// d：基准（即水平线的纵坐标，竖直线的横坐标） 
	}ta[2005],tb[2005];//ta 是合并后的 a[]，tb 是合并后的 b[] 
	bool check(ll t)
	{
		int totn=0,totm=0;
		For(i,1,n)  
			if(i^1&&a[i].y==ta[totn].d&&a[i].x-2ll*t<=ta[totn].r) ta[totn].r=a[i].x+2ll*t;//如果在同一高度（纵坐标相同）且相交，合并入前一条线段 
			else ta[++totn]=(node){a[i].y,a[i].x-2ll*t,a[i].x+2ll*t};//否则，新建一条线段，记录基准（水平线的高度）、左端点、右端点 
		For(i,1,m)	
			if(i^1&&b[i].x==tb[totm].d&&b[i].y-2ll*t<=tb[totm].r) tb[totm].r=b[i].y+2ll*t;//如果横坐标相同且相交，合并入前一条线段 
			else tb[++totm]=(node){b[i].x,b[i].y-2ll*t,b[i].y+2ll*t};//否则，新建一条线段，记录基准（横坐标的值）、左端点、右端点 
			
		For(i,1,totn) For(j,i+1,totn)//枚举上下两条水平线 
		{
			int tmp=-1;//tmp 是满足条件的竖直线段的编号 
			ll p=max(ta[i].l,ta[j].l),q=min(ta[i].r,ta[j].r);//两条水平线左右端点取交集，就是矩形最大范围的左右边界 
			ll down=ta[i].d,up=ta[j].d;//矩形的上下边界就是两条水平线的高度 
			if(p>=q||down>=up) continue;//矩形不能退化成线段或点 
			For(k,1,totm)// tb[k].d （横坐标）必须被包含进左右边界，线段端点必须包含上下边界
				if(tb[k].d>=p&&tb[k].d<=q&&tb[k].l<=down&&tb[k].r>=up)
					if(tmp==-1) tmp=k;//找到了第一条竖直线段 
					else if(tb[k].d^tb[tmp].d) return 1;//找到了第二条竖直线段，且不与第一条共线 
		}
		return 0;
	}
	bool cmpa(pll xx,pll yy){ return xx.y==yy.y?xx.x<yy.x:xx.y<yy.y; }
	signed my_main()
	{
		read(n,m);
		bool flag1=0,flag2=0;ll xx,yy;
		// a[] 是水平线，b[] 是竖直线 
		For(i,1,n) read(xx,yy),a[i]=mk(xx-yy,xx+yy),flag1|=(i^1&&a[i].y^a[i-1].y);
		For(i,1,m) read(xx,yy),b[i]=mk(xx-yy,xx+yy),flag2|=(i^1&&b[i].x^b[i-1].x);
		if(!flag1||!flag2){ printf("Poor Sereja!\n"); return 0; }
		sort(a+1,a+1+n,cmpa),sort(b+1,b+1+m);// a[] 按纵坐标（a[i].y）排序，b 按横坐标排序（排序是为了后面的合并线段） 
		
		ll L=1,R=0x3f3f3f3f3f3f3f3f,ans=-1;
		while(L<=R) if(!check(mid)) L=mid+1; else ans=mid,R=mid-1;
		printf("%lld\n",ans);
		return 0;
	}
}
signed main(){ return O_O::my_main(); }
```

---

