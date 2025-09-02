# Vanya and Field

## 题目描述

> 滑稽树上滑稽果
>
> 滑稽树下你和我

> 滑稽树前做游戏
>
> 滑稽多又多

一天，Vanya 来到了一片滑稽树林中，准备采摘滑稽果。滑稽树林可看作一个 $n \times n$ 的正方形，其中 $m$ 个点上有滑稽果，某些点没有。（注意一个点上可能有多个滑稽果）

Vanya 会沿向量 $(\mathit{dx},\mathit{dy})$ 方向移动。也就是说，如果 Vanya 在 $(x,y)$ 处，她将移动到 $((x + \mathit{dx})\bmod n,(y + \mathit{dy})\bmod n)$ 处。每到一个点，她会拿走该点所有滑稽果。（$\mathit{dx},\mathit{dy}$ 为定值（输入中给出），且 $\gcd(n,\mathit{dx})=\gcd(n,\mathit{dy})=1$）

由于滑稽树林太巨了，当 Vanya 走到一个她走到过的点时，她就会停止走动。

现在 Vanya 想知道她怎么走才能拿到最多的滑稽果。

## 说明/提示

对于所有测试数据，$1 \le n \le 10^6$，$1 \le m \le 10^5$，$1 \le dx,dy \le n$，$0 \le x_i,y_i \le n-1$。

Translated By InterestingLSY.

## 样例 #1

### 输入

```
5 5 2 3
0 0
1 2
1 3
2 4
3 1
```

### 输出

```
1 3
```

## 样例 #2

### 输入

```
2 3 1 1
0 0
0 1
1 1
```

### 输出

```
0 0
```

# 题解

## 作者：Prean (赞：4)

屑题。

考虑对于每一个 $ (x,y) $，将其与 $ ((x+dx) \mod n,(y+dy) \mod n) $ 连边。

答案就是连通块中权值最大的那个。

考虑对于 $ (x_1,y_1) $ 和 $ (x_2,y_2) $ 两个点在同一个连通块中的条件。

条件就是同余方程 $ x_1+x * dx \equiv x_2 \bmod n  $ 和 $ y_1+y * dy \equiv y_2 \bmod n $ 的解是同一个。

考虑化简：
$$ x \equiv \frac {x_2-x_1} {dx} \mod n $$
$$ x \equiv \frac {y_2-y_1} {dy} \mod n $$
也就是：
$$ \frac {x_2-x_1} {dx} \mod n \equiv \frac {y_2-y_1} {dy} \mod n $$
$$ \frac {y_1} {dy} -\frac {x_1} {dx} \equiv \frac {y_2} {dy} - \frac {x_2} {dx} \bmod n $$
因为值域只有 $ O(n) $，开个桶统计一下数量就好了。

因为 $ \gcd(n,dx)=\gcd(n,dy)=1 $，所以 $ dx $ 和 $ dy $ 的逆元可以使用 exgcd 计算。
```cpp
#include<cstdio>
typedef unsigned uint;
const uint M=1e6;
uint n,m,id,dx,dy,x[M],y[M],sum[M];
void exgcd(const uint&a,const uint&b,uint&x,uint&y){
    if(!b)return void((x=1,y=0));exgcd(b,a%b,y,x);y-=a/b*x;
}
inline uint Del(const uint&a,const uint&b){
	return b>a?a-b+n:a-b;
}
signed main(){
	register uint i,T,X,Y;
	scanf("%u%u%u%u",&n,&m,&dx,&dy);
	exgcd(dx,n,X,Y);dx=(X+n)%n;
	exgcd(dy,n,X,Y);dy=(X+n)%n;
	for(i=1;i<=m;++i){
		scanf("%u%u",&X,&Y);
		T=Del(1ull*X*dx%n,1ull*Y*dy%n);
		if(!sum[T])x[T]=X,y[T]=Y;
		if(++sum[T]>sum[id])id=T;
	}
	printf("%u %u",x[id],y[id]);
}
```

---

## 作者：wsyhb (赞：2)

## 题解

由于 $\gcd(n,dx)=\gcd(n,dy)=1$，所以恰好在 $n$ 步以后回到起点。

若从 $(x,y)$ 向 $((x+dx) \bmod n,(y+dy) \bmod n)$ 连边，则得到了 $n$ 个互不相交的大小为 $n$ 的环，且环上每个点的横坐标和纵坐标分别互不相同。

任务变为：给定 $m$ 个关键点，求这 $n$ 个环中哪一个环包含最多的关键点（若有多个取任意一个），输出这个环上的任意一个点。

考虑**用环上横坐标为 $0$ 的点的纵坐标对环进行编号**，例如：包含点 $(0,m)$ 的环的编号为 $m$。

那么对于一个关键点 $(a,b)$，我们只需求出它所在环的编号即可。

设从横坐标为 $0$ 的点走 $k$ 步可以到达 $(a,b)$，则 $k \cdot dx \equiv a \pmod n$。

移项得 $k \equiv a \cdot (dx)^{-1} \pmod n$，于是这个点所在环的编号为 $(y-k \cdot dy) \bmod n=(y-a \cdot (dx)^{-1} \cdot dy) \bmod n$。

使用**扩展欧几里得算法**求逆元，并使用大小为 $n$ 的桶计数即可解决本题。

时间复杂度 $O(n+m\log{n})$。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
int x,y;
int exgcd(int a,int b)
{
	if(!b)
	{
		x=1,y=0;
		return a;
	}
	int d=exgcd(b,a%b);
	int p=y,q=x-a/b*y;
	x=p,y=q;
	return d;
}
inline int inverse(int v,int mod)
{
	int d=exgcd(v,mod);
	assert(d==1);
	return x+(x<0?mod:0);
}
const int max_n=1e6+5;
int cnt[max_n];
int main()
{
	int n,m,dx,dy;
	scanf("%d%d%d%d",&n,&m,&dx,&dy);
	int inv=inverse(dx,n);
	while(m--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int k=1ll*(n-x)*inv%n;
		++cnt[(y+1ll*k*dy)%n];
	}
	int ans_id=-1,ans_cnt=0;
	for(int i=0;i<n;++i)
	{
		if(cnt[i]>ans_cnt)
		{
			ans_cnt=cnt[i];
			ans_id=i;
		}
	}
	printf("%d %d\n",0,ans_id);
	return 0;
}
```

---

## 作者：foreverlasting (赞：0)

[同步发表在我的博客里哦](https://foreverlasting1202.github.io/)

瞎搞法。

感觉这种思维题我就完全不会了，看来我还是太弱了。

首先要看到$gcd(n,dx)=gcd(n,dy)=1$这个重要的条件。

然后借用网上的一篇题解：

 _就是从某一行和某一列的交点出发，要重新回到这个交点，就要经过$n$步而且这$n$步覆盖了每一行每一列。每个循环必须每个$x$走一次以及每个$y$走一次，$n$个格子属于一组循环里面的，总共有$n\ast n$个格子，所以有$n$组循环。一组循环内的格子是等价的。同一行内的$n$个格子均来自不同的$n$组。_ 
 
于是我们预处理$a[i]$表示$x$坐标移动$i$，$y$坐标的移动量 $(mod n)$

然后考虑起点为$(0,p)$，划分集合，输出最大集合就可以了。

code:
```cpp
//2019.2.24 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=1e6+10;
const int M=1e5+10;
namespace MAIN{
	int n,m,dx,dy;
	int a[N],sum[N],mx,ans;
	inline void MAIN(){
		n=read(),m=read(),dx=read(),dy=read();
		for(res j=0,x=0,y=0;j<n;j++)a[x]=y,x=(x+dx)%n,y=(y+dy)%n;
		for(res i=1;i<=m;i++){
			res x=read(),y=read(),k=(y-a[x]+n)%n;
			sum[k]++;
			if(sum[k]>mx)mx=sum[k],ans=k;
		}
		printf("0 %d\n",ans);
	}
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

