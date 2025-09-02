# [POI 2014] DOO-Around the world

## 题目描述

After trying hard for many years, Byteasar has finally received a pilot license.

To celebrate the fact, he intends to buy himself an airplane and fly around the planet  3-SATurn (as you may have guessed, this is the planet on which Byteotia is located).

Specifically, Byteasar plans to fly along the equator.

Unfortunately, the equator is rather long, necessitating refuels.

  The flight range (on full tank) of each aircraft is known.

There is a number of airports along the equator, and a plane can be refueled when it lands on one.

Since buying an airplane is a big decision, Byteasar asks your help.

He is about to present you with a list of different plane models he is considering.

Naturally, these differ in their flight range.

For each plane model, he would like to know the minimum number of landings  (including the final one) he would have to make in order to complete the journey.

Note that for each airplane model, the journey may start at a different airport.

通过几年的努力，Byteasar最终拿到了飞行员驾驶证。为了庆祝这一事实，他打算买一架飞机并且绕Byteotia星球赤道飞行一圈。但不幸的是赤道非常长所以需要中途加几次油。现在已知赤道上面所有飞机场，所有飞机从飞机场起飞降落也可以加油。因为买飞机是个十分重大的决定，Byteasar决定寻求你的帮助。他将会让你模拟不同的飞行路线。自然这些飞机一次能走的航程是不同的。对于每次模拟，他想要知道最少需要降落多少次（包括最后一次）。需要注意的是起点可以任意选取。


## 说明/提示

通过几年的努力，Byteasar最终拿到了飞行员驾驶证。为了庆祝这一事实，他打算买一架飞机并且绕Byteotia星球赤道飞行一圈。但不幸的是赤道非常长所以需要中途加几次油。现在已知赤道上面所有飞机场，所有飞机从飞机场起飞降落也可以加油。因为买飞机是个十分重大的决定，Byteasar决定寻求你的帮助。他将会让你模拟不同的飞行路线。自然这些飞机一次能走的航程是不同的。对于每次模拟，他想要知道最少需要降落多少次（包括最后一次）。需要注意的是起点可以任意选取。


## 样例 #1

### 输入

```
6 4
2 2 1 3 3 1
3 2 4 11
```

### 输出

```
4
NIE
3
2
```

# 题解

## 作者：RicardoShips (赞：6)

先断环成链复制一遍，再前缀和预处理

显然终点都在$[n+1,2n]$中，把终点当作起点倒推

考虑设走$f[i]$步可以到达的最远的点为$fa[i]$

如果当前所在点为$i$，找到可以到达的最远的点为$j$

那么$f[i]=f[j]+1$，$fa[i]=fa[j]$

如果$i-fa[i]>=n$，那么直接退出输出$f[i]$

因为不存在一个更靠后的位置答案更优，~~证明不会~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2000002;
int m,n,x,s,f[maxn],fa[maxn],sum[maxn];
inline int read () {
    char ch=getchar(); int num=0;
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) num=(num<<3)+(num<<1)+(ch^'0'),ch=getchar();
    return num;
}
int main () {
    n=read(),s=read();
    for(register int i=1;i<=n;++i) {
    	int x=read(); m=max(m,x);
    	fa[i]=i,sum[i]=sum[i-1]+x;
    }
    for(register int i=n+1;i<=(n<<1);++i)
        sum[i]=sum[i-1]+sum[i-n]-sum[i-n-1];
    while(s--) {
    	register int i,j,d=read();
    	if(d<m) puts("NO");
    	else for(i=n+1,j=1;i<=(n<<1);++i) {
    		while(sum[i]-sum[j]>d) ++j;
    		f[i]=f[j]+1,fa[i]=fa[j];
    		if(i-fa[i]>=n) {
    			printf("%d\n",f[i]);
    			break ;
            }
        }
    }
    return 0;
}
```


---

## 作者：foreverlasting (赞：3)

神奇的题。

首先我建议洛谷这边空间也改小一点，不然就没意思了。这一题主要恶心在于空间。

思路其实很简单，环当然破开成两倍，然后预处理出前缀和。然后利用一个类似于并查集的神奇东西记录这个点已经计算到的位置。最后维护一个DP就好了。


code:
```
#include<cstdio>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(res x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
inline int _max(res x,res y){
    return x>y?x:y;
}
inline int _min(res x,res y){
    return x>y?y:x;
}
const int N=2*1e6+1;
int n,T,sum[N],maxx,dp[N],fa[N];
int main(){
	n=read(),T=read();
	for(res i=1;i<=n;i++){
		fa[i]=i;
		res x=read();
		maxx=_max(maxx,x);
		sum[i]=sum[i-1]+x;
	}
	for(res i=n+1;i<=n+n;i++)sum[i]=sum[i-1]+sum[i-n]-sum[i-n-1];
	while(T--){
		res x=read();
		if(x<maxx){puts("NIE");continue;}
		for(res i=n+1,j=1;;i++){
			while(sum[i]-sum[j]>x)j++;
            dp[i]=dp[j]+1;
			fa[i]=fa[j];
            if(i-fa[i]>=n){printf("%d\n",dp[i]);break;}
		}
	}
    return 0;
}
```

---

## 作者：WaReTle (赞：2)

提供另一种线性的做法。这种做法只需要开两个长度为 $n$ 的 ```int``` 数组但是比较慢。

先判掉不合法的情况。然后我们设 $to_i$ 表示 $i$ 沿正方向走能走到的最远的点。这个数组容易用双指针线性求出。接着找到走出步数（即 $i$ 到 $to_i$ 之间的点数）最小的点 $p$。容易证明任何合法的走法一定经过 $p$ 到 $to_p$ 之间的至少一个点。我们以 $p$ 到 $to_p$ 中间每个点为起点分别暴力模拟就可以求出答案。

设 $p$ 到 $to_p$ 之间的点数为 $x$。由于暴力模拟的时候每一步至少跳了 $x$，所以枚举一个点的复杂度是 $O(\dfrac{n}{x})$。一共枚举了 $x$ 个点，所以单次询问的复杂度是 $O(n)$。总复杂度 $O(ns)$。常数不小，实现得不好可能会超时。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int n,q,to[1000005],a[1000005];
int getnum(int l,int r){return l<=r?r-l+1:n+r-l+1;}
int nxt(int i){return i==n?1:i+1;}
int calc(int p)
{
	int cur=p,res=0;
	while(to[cur]>cur)cur=to[cur],++res;
	cur=to[cur],++res;
	if(cur>=p)return res;
	while(1)
	{
		if(to[cur]>=p||to[cur]<cur){++res;break;}
		cur=to[cur],++res;
	}
	return res;
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	int mx=*max_element(a+1,a+n+1);
	while(q--)
	{
		ll k;scanf("%lld",&k);
		if(k<mx){puts("NIE");continue;}
		ll d=0;
		for(int l=1,r=1;l<=n;++l)
		{
			while(d+a[r]<=k)d+=a[r],r=nxt(r);
			to[l]=r,d-=a[l];
		}
		int p=0,mn=n+5,ans=n;
		for(int i=1;i<=n;++i)
			if(getnum(i,to[i])<mn)mn=getnum(i,to[i]),p=i;
		for(int i=p;;i=nxt(i))
		{
			ans=min(ans,calc(i));
			if(i==to[p])break;
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

---

