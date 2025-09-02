# Dead Ends

## 题目描述

Bertown的生活变得困难了起来。这个城市有太多的道路，而且政府花费了太多来维护这些道路。这里有$n$个节点和$m$条双向道路，且两两节点之间可以通过道路相互到达。现在市长想要关闭一些道路，使最后总共有$n-1$条道路留下，并且所以节点之间仍然联通。另外，市长很关心终点，也就是只有一条道路可以到达的点的数量。终点不能太多也不能太少。在讨论过这个问题之后，市长和他的助手们觉得在应该关闭的道路关闭后，应该总共有恰好$k$个终点。你的任务是求出满足以下三个条件的方案数：

1.有恰好$n-1$条道路保留下来；

2.整张道路图仍然联通；

3.最后有恰好$k$个终点在道路图上。

如果有一条道路在第一种方案中被关闭而在第二种方案中没有被关闭，那么我们认为这两种方案不同。

## 样例 #1

### 输入

```
3 3 2
1 2
2 3
1 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
4 6 2
1 2
2 3
3 4
4 1
1 3
2 4
```

### 输出

```
12
```

## 样例 #3

### 输入

```
4 6 3
1 2
2 3
3 4
4 1
1 3
2 4
```

### 输出

```
4
```

# 题解

## 作者：优少 (赞：10)

### 题意：
　　给一个n(n<=10)个节点的无向图,图里面有m条边，以这m条边构建生成树，求所有生成树中只含有k个度数为1的点的方案数。

### 题解：
　　看见这个数量级就一定会想到状态压缩dp...
  
   那让我们设计一下状态：
   
   **dp[i][j]**  表示生成树的状态为i时，所含的度数为1的点的状态j的方案数。

　　那么就可以进行状态转移了，每次有两种更新方式：
  
   **1：加入一条边(也就是一个新点)到原来度数为1的点，相当于替换了。**
   
   **2：把边加到一个度数不为1的节点上。**
   
### 时间复杂度：
    
   ~~**O（能过）**~~
   
##    废话少说上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxs=(1<<11)+10;
vector<int> mapp[20];
int dp[maxs][maxs],cnt1[maxs];
int n,m,k;
void init(){
	for(int i=1;i<=maxs;i++)
	    for(int k=0;k<+15;k++)
	        if(i&(1<<k))
	           cnt1[i]++;
}
int main(){
	init();
	scanf("%d%d%d",&n,&m,&k);
	int x,y;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y); x--;y--;
		mapp[x].push_back(y);mapp[y].push_back(x);
	}
	for(int i=1;i<=(1<<n)-1;i<<=1) dp[i][i]=1;
	for(int i=1;i<=(1<<n)-1;i++)
		for(int j=i;j;--j&=i)
			if(dp[i][j])
				for(int e=0;e<n;e++)
					if(i&(1<<e))
						for(int r=0;r<mapp[e].size();r++){
							int to=mapp[e][r],now;
							if(~i&(1<<to)){
								if(cnt1[i]==1) now=i|(1<<to);
                                else now=j&~(1<<e)|(1<<to);
                                if(!(now>>to+1)) dp[i|(1<<to)][now]+=dp[i][j];
							}
						}
	long long ans=0;
	for(int i=0;i<=(1<<n)-1;i++) 
	    if(cnt1[i]==k)
	       ans+=dp[(1<<n)-1][i];
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：myee (赞：9)

### Update
* 2022-02-10 修改了柿子中的几处小错误，并增加部分说明。

---
### 前言

校内模拟赛做到这题，我写了一个 $O^* (2^n)$ 的做法，结果发现旁边同学全是状压 dp 的 $O^* (3^n)$ 甚至不知道咋么来的 $O^* (4^n)$ 做法……

那么我是咋做的呢？**容斥 + 矩阵树定理**。

---
### 题意简述

给一个节点个数不超过 $10$ 的简单无向图，问有多少棵生成树（有标号）使得它的叶结点个数为 $k$。

---
### 思路

分类讨论。

特判掉 $n=1,2$ 的情况，这个很好处理。

下面考虑 $n\ge3$ 的情况，此时叶结点个数严格小于 $n$。

---
看到**生成树计数**就想到矩阵树定理。

但是这有一个 $k$ 个叶子的要求，那咋做哩？

考虑**容斥**。

我们假设已经钦定了**某** $\omega\ \ (\omega<n)$ 个叶结点组合 $a_1,a_2,\dots,a_\omega$。

那么**这些叶结点一定和未被钦定的结点相连**，每个被钦定的叶结点有**一定数量的选法**。

对**未被钦定的结点**跑**矩阵树**。

由乘法原理，把这些数**乘起来**，即是对这 $\omega$ 个结点钦定时的方案数 $f_{\{a_\omega\}}$。

我们假设容斥系数是 $S_{\{a_\omega\}}$

考虑每个**真正的叶结点方案** $A$ 在**哪些钦定** $\{a_\omega\}$ 时被枚举到，有：

$$\sum_\omega\sum_{\{a_\omega\}\subseteq A}S_{\{a_\omega\}}=[|A|=k]$$

我们不难想到**对于同样的 $\omega$，其容斥系数相同**，即 $S_\omega$。（可以数学归纳法证明）

那么上式即：

$$\sum_\omega\binom{|A|}{\omega}S_\omega=[|A|=k]$$

这个东西是一个二项式反演的形式，我们可以立即得到：

$$S_\omega=(-1)^{\omega-k}\binom\omega k$$

于是答案即：

$$\sum_{k\le|\{a\}|<n}(-1)^{|\{a\}|-k}\binom{|\{a\}|}kf_{\{a\}}$$

枚举所有这样的 $\{a\}$ 就好了。

总复杂度 $O(n^32^n)$，即 $O^* (2^n)$。

---
### Code

```cpp
// 10^8 < 998244353
// 直接在模 998244353 的剩余系下操作
// 钦定叶子，容斥 + 矩阵树即可
// 容斥系数可以二项式反演
// O*(2^n)
// 可以通过

#include <algorithm>
#include <stdio.h>
#include <vector>
typedef long long llt;
typedef unsigned uint;typedef unsigned long long ullt;
typedef bool bol;typedef char chr;typedef void voi;
typedef double dbl;
template<typename T>bol _max(T&a,T b){return(a<b)?a=b,true:false;}
template<typename T>bol _min(T&a,T b){return(b<a)?a=b,true:false;}
template<typename T>T power(T base,T index,T mod){return((index<=1)?(index?base:1):(power(base*base%mod,index>>1,mod)*power(base,index&1,mod)))%mod;}
template<typename T>T lowbit(T n){return n&-n;}
template<typename T>T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T>T lcm(T a,T b){return(a!=0||b!=0)?a/gcd(a,b)*b:(T)0;}
template<typename T>T exgcd(T a,T b,T&x,T&y){if(!b)return y=0,x=1,a;T ans=exgcd(b,a%b,y,x);y-=a/b*x;return ans;}
template<const ullt p=998244353>
class mod_ullt
{
    private:
        ullt v;
        inline ullt chg(ullt w){return(w<p)?w:w-p;}
        inline mod_ullt _chg(ullt w){mod_ullt ans;ans.v=(w<p)?w:w-p;return ans;}
    public:
        mod_ullt():v(0){}
        mod_ullt(ullt v):v(v%p){}
        bol empty(){return!v;}
        inline ullt val(){return v;}
        friend bol operator<(mod_ullt a,mod_ullt b){return a.v<b.v;}
        friend bol operator>(mod_ullt a,mod_ullt b){return a.v>b.v;}
        friend bol operator<=(mod_ullt a,mod_ullt b){return a.v<=b.v;}
        friend bol operator>=(mod_ullt a,mod_ullt b){return a.v>=b.v;}
        friend bol operator==(mod_ullt a,mod_ullt b){return a.v==b.v;}
        friend bol operator!=(mod_ullt a,mod_ullt b){return a.v!=b.v;}
        inline friend mod_ullt operator+(mod_ullt a,mod_ullt b){return a._chg(a.v+b.v);}
        inline friend mod_ullt operator-(mod_ullt a,mod_ullt b){return a._chg(a.v+a.chg(p-b.v));}
        inline friend mod_ullt operator*(mod_ullt a,mod_ullt b){return a.v*b.v;}
        friend mod_ullt operator/(mod_ullt a,mod_ullt b){return b._power(p-2)*a.v;}
        inline mod_ullt operator-(){return _chg(p-v);}
        mod_ullt sqrt()
        {
            if(power(v,(p-1)>>1,p)!=1)return 0;
            mod_ullt b=1;do b++;while(b._power((p-1)>>1)==1);
            ullt t=p-1,s=0,k=1;while(!(t&1))s++,t>>=1;
            mod_ullt x=_power((t+1)>>1),e=_power(t);
            while(k<s)
            {
                if(e._power(1llu<<(s-k-1))!=1)x*=b._power((1llu<<(k-1))*t);
                e=_power(p-2)*x*x,k++;
            }
            return _min(x,-x),x;
        }
        mod_ullt inv(){return _power(p-2);}
        mod_ullt _power(ullt index){mod_ullt ans(1),w(v);while(index){if(index&1)ans*=w;w*=w,index>>=1;}return ans;}
        voi read(){v=0;chr c;do c=getchar();while(c>'9'||c<'0');do v=(c-'0'+v*10)%p,c=getchar();while(c>='0'&&c<='9');v%=p;}
        voi print()
        {
        	static chr C[20];uint tp=0;
        	ullt w=v;do C[tp++]=w%10+'0',w/=10;while(w);
        	while(tp--)putchar(C[tp]);
        }
        voi println(){print(),putchar('\n');}
        mod_ullt operator++(int){mod_ullt ans=*this;return v=chg(v+1),ans;}
    public:
        inline ullt&operator()(){return v;}
        inline mod_ullt&operator+=(mod_ullt b){return*this=_chg(v+b.v);}
        inline mod_ullt&operator-=(mod_ullt b){return*this=_chg(v+chg(p-b.v));}
        inline mod_ullt&operator*=(mod_ullt b){return*this=v*b.v;}
        mod_ullt&operator/=(mod_ullt b){return*this=b._power(p-2)*v;}
        mod_ullt&operator++(){return v=chg(v+1),*this;}
};
const ullt Mod=998244353;
typedef mod_ullt<Mod>modint;
const uint Siz=35;
struct Mat
{
    modint M[Siz][Siz];uint n;
    Mat():n(0){}
    Mat(uint n):n(n){}
    modint*operator[](uint n){return M[n];}
    voi bzr(){resize(0);}
    voi resize(uint s)
    {
        for(uint i=s;i<n;i++)for(uint j=0;j<n;j++)M[i][j]=M[j][i]=0;
        n=s;
    }
    modint det()
    {
        Mat A=*this;
        modint ans(1);
        for(uint i=0;i<n;i++)
        {
            {
                uint j;for(j=i;j<n&&!A[j][i]();j++);
                if(j==n)return 0;
                if(i!=j)
                {
                    ans=-ans;
                    for(uint k=0;k<n;k++)std::swap(A[i][k],A[j][k]);
                }
            }
            modint qaq=A[i][i];
            ans*=qaq;qaq=qaq.inv();
            for(uint j=0;j<n;j++)A[i][j]*=qaq;
            for(uint j=0;j<n;j++)if(A[j][i]()&&i!=j)
            {
                qaq=A[j][i];
                for(uint k=0;k<n;k++)A[j][k]-=A[i][k]*qaq;
            }
        }
        for(uint i=0;i<n;i++)ans*=A[i][i];
        return ans;
    }
};
typedef std::pair<uint,uint>Pair;
std::vector<Pair>E;
Mat M;
modint P[35],Q[35];
modint binom(uint n,uint m){return P[n]*Q[m]*Q[n-m];}
int main()
{
	P[0]=1;for(uint i=1;i<=30;i++)P[i]=P[i-1]*i;
	Q[30]=P[30].inv();for(uint i=30;i;i--)Q[i-1]=Q[i]*i;
	uint n,m,k;
	scanf("%u%u%u",&n,&m,&k);
	if(n==1)puts(k==1?"1":"0");
	else if(n==2)puts(m==1&&k==2?"1":"0");
	else
	{
		if(!k||k>=n)return puts("0"),0;
		uint u,v;while(m--)scanf("%u%u",&u,&v),E.push_back(Pair(u-1,v-1));
		modint ans;
		for(uint i=0;i<(1u<<n)-1;i++)if(__builtin_popcount(i)>=k)
		{
			modint now;
			std::vector<uint>Leaf,Any,Back(n);
			for(uint j=0;j<n;j++)
				if(i>>j&1)Back[j]=Leaf.size(),Leaf.push_back(j);
				else Back[j]=Any.size(),Any.push_back(j);
			std::vector<modint>Time(Leaf.size());
			M.bzr();
			M.resize(Any.size());
			for(auto e:E)
			{
				if((i>>e.first&1)&&!(i>>e.second&1))
					Time[Back[e.first]]++;
				else if(!(i>>e.first&1)&&(i>>e.second&1))
					Time[Back[e.second]]++;
				else if(!(i>>e.first&1)&&!(i>>e.second&1))
				{
					u=Back[e.first],v=Back[e.second];
					M[u][u]+=1,M[v][v]+=1,
					M[u][v]-=1,M[v][u]-=1;
				}
			}
			M.resize(Any.size()-1);
			now=M.det();
			for(auto t:Time)now*=t;
			uint w=__builtin_popcount(i);
			ans+=((w-k)&1)?-binom(w,k)*now:binom(w,k)*now;
		}
		ans.println();
	}
	return 0;
}
```


---

## 作者：lzytag (赞：9)

本篇题解是直接状压 dp 题解，内容不含容斥和矩阵树定理。

其他的题解里大多有写到防止算冲，却没有任何一篇题解讲明白如何防止，为什么这样做可以做到不算重。于是我这篇题解就来补充一下证明。

首先我们来设计状态，我们从只有节点 $1$ 开始 $f_{S1,S2}$ 表示集合 $S1$ 已经与节点 $1$ 联通，其中 $S2$ 集合是度数为一的节点，每次都选一条边 $(u,v)$，$u$ 在 $S1$ 中，$v$ 不在 $S1$ 中，然后将 $v$ 加入 $S1$，$S2$，若 $u$ 在 $S2$ 中则从 $S2$ 中删去 $u$，进行状压 dp 。

但这样有一个问题，这样有可能会算重，例如样例一中选择 $(1,2)(1,3)$ 会被加入两次。

如何才能防止算重呢？我们发现状压 dp 表示的其实是一个在生成树中不断加边的过程，也就是说，如果能做到让生成树能且仅能通过一种加边顺序形成，就能算出答案。

解决方法是：当新加入一个叶子节点是，判断它是否为所有当前叶子节点中序号最大的节点，若是则进行转移，否则不进行转移。

证明：对于一棵生成树，必须先把节点 $1$ 到节点 $2$ 的路径上的边依次加入，再把节点 $1$ 到节点 $3$ 的路径上未被加入的边依次加入，以此类推直到节点 $1$ 到节点 $n$ 路径上所有边已被加入。这种加边方式显然是会被计算到的，但是如果不这样加边，比如在加入节点 $1$ 到节点 $v$ 的过程中加入了其他的边，则当 $v$ 被加入时，必然有一个比它编号大的节点，是不会被重复计算的。

代码就比较好写了。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll f[1<<10][1<<10],ans;
int n,m,d;
bool g[11][11];
int main()
{
    scanf("%d%d%d",&n,&m,&d);
    for(int i = 1,u,v;i <= m;i++)
    {
        scanf("%d%d",&u,&v);
        g[u][v] = g[v][u] = 1;
    }
    for(int i = 2;i <= n;i++)
        if(g[1][i]) f[1<<(i-1)|1][1<<(i-1)|1] = 1;
    for(int i = 0;i < (1<<n);i++)
    {
        for(int j = i;j;j = (j-1)&i)
        {
            if(!f[i][j]) continue;
            int c1 = 0,c2 = 0;
            for(int k = 1;k <= n;k++)
            {
                bool p1 = i&(1<<(k-1)),p2 = j&(1<<(k-1));
                if(p2) c1++;
                else if(p1) c2++;
                else continue;
                for(int l = 1;l <= n;l++)
                {
                    bool p = i&(1<<(l-1));
                    if(p||!g[l][k]) continue;
                    int to;
                    if(p2) to = j^(1<<(l-1))^(1<<(k-1));
                    else to = j^(1<<(l-1));
                    if((to>>(l-1))==1) f[i|(1<<(l-1))][to] += f[i][j];
                }
            }
            if(c1 == d && c2 == n-d) ans += f[i][j];
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：_jimmywang_ (赞：5)

~~(纪念在模拟赛里场切的一道 2500)~~

与其他状压的做法一样，但是这篇题解主要讲述另一种**去重**的方法。

我们发现会重复的主要原因是同一棵树会被转移到多次。

比如下面这棵树：

![](https://cdn.luogu.com.cn/upload/image_hosting/ybw9hlsn.png)

它应该被 $dp[(111111)_2][(111001)_2]$ 算到一次（下文二进制均简写）。

但是实际上如果我们暴力转移，这棵树会被 $dp[111110][111000]$（加入叶子 1）、$dp[110111][110001]$（加入叶子 4）、$dp[101111][101001]$（加入叶子 5）、$dp[011111][011001]$（加入叶子 6）转移到。一共 4 次。

于是我们可以发现，这棵树有几个叶子，就会被重复转移到几次。

所以在计算时将 $dp[i][j]$ 除以 $popcount(j)$ 就行了。

---

## 作者：liuzhangfeiabc (赞：5)

来一个复杂度更优秀的做法。

首先，（可能不是）众所周知的是，给定任意无向图，求其生成树个数，可以用矩阵树定理来实现。

（什么你不会矩阵树定理？出门右转百度一下）

但是这个题还有一个叶子数限制怎么办呢？

不妨考虑枚举哪些点一定成为叶子，然后从图中删去这些点，对于剩下的点跑一次生成树计数。

然后对于每个叶子节点，它可以从连向非叶子节点的出边中任选一条挂上去。

但是仅仅这样还不够，因为我们只是强制让一部分点成为叶子，但另一部分点却并没有保证让它们不是叶子。

换句话说，对于一个集合s的点，我们能求出fs表示最后的叶子节点集合包含s的方案数。

那怎么得到恰好为s的方案数（不妨记作gs）呢？注意到如果把f和g看做n维、每一维大小为2的数组，那么f就是g的高维后缀和，因此做一次高维差分就可以了。（其实这也是and运算下的ifwt过程）

复杂度O(2^n×n^3)，理论上说跑n=17不成问题。

(注：由于本人太懒，直接粘了个模意义下的高斯消元，不过答案显然不会超过1e8因此也无所谓啦)

```cpp
#include<cstdio>
#include<algorithm>
#define li long long
#define gc getchar()
#define pc putchar
inline li read(){
	li x = 0,y = 0,c = gc;
	while(!isdigit(c)) y = c,c = gc;
	while(isdigit(c)) x = x * 10 + (c ^ '0'),c = gc;
	return y == '-' ? -x : x;
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	if(x >= 10) print(x / 10);
	pc(x % 10 + '0');
}
int n,m,p,ed[20][20],wei[150010],mx,dy[20];
li jz[20][20],as[150010];
const int mo = 1000000007;
inline li ksm(li q,li w){
	li as = 1;
	while(w){
		if(w & 1) as = as * q % mo;
		q = q * q % mo;
		w >>= 1;
	}
	return as;
} 
inline li wk(int cnt){
	register int i,j,k;
	li as = 1,tmp;
	for(i = 1;i <= cnt;++i){
		if(!jz[i][i]){
			int fg = 0;
			for(j = i + 1;j <= cnt;++j) if(jz[j][i]){
				fg = j;break;
			}
			if(!fg) return 0;
			for(j = i;j <= cnt;++j) std::swap(jz[i][j],jz[fg][j]);
		}
		(as *= jz[i][i]) %= mo;
		tmp = ksm(jz[i][i],mo - 2);
		for(j = i;j <= cnt;++j) (jz[i][j] *= tmp) %= mo;
		for(j = i + 1;j <= cnt;++j){
			for(k = cnt;k >= i;--k) (jz[j][k] += mo - (jz[i][k] * jz[j][i]) % mo) %= mo;
		}
	}
	return as;
}
int main(){
	int i,j,k,l,u,v;
	n = read();m = read();p = read();
	for(i = 1;i <= m;++i){
		u = read();v = read();ed[u][v] = ed[v][u] = 1;
	}
	mx = 1 << n;
	for(i = 0;i < mx;++i){
		wei[i] = wei[i >> 1] + (i & 1);
		for(j = 1;j <= n;++j) for(k = 1;k <= n;++k) jz[j][k] = 0;
		int cnt = 0;
		for(j = 1;j <= n;++j) if(!(i & (1 << j - 1))) dy[++cnt] = j;
		for(j = 1;j < cnt;++j) for(k = j + 1;k <= cnt;++k) if(ed[dy[j]][dy[k]]) jz[j][k] = jz[k][j] = mo - 1,++jz[j][j],++jz[k][k];
		as[i] = wk(cnt - 1);
		for(j = 1;j <= n;++j) if(i & (1 << j - 1)){
			int tmp = 0;
			for(k = 1;k <= n;++k) if(ed[j][k] && !(i & (1 << k - 1))) ++tmp;
			as[i] *= tmp;
		}
	}
	for(i = 1;i < mx;i <<= 1) for(j = 0;j < mx;j += (i << 1)) for(k = j;k < j + i;++k) as[k] -= as[k + i];
	li ans = 0;
	for(i = 0;i < mx;++i) if(wei[i] == p) ans += as[i];
	print(ans);  
	return 0;
}
```

---

## 作者：Strelitzia (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF53E)

---

不错一题，就是有些坑点。

看数据范围，可以判断出是状压 $\text{dp}$。

定义 $dp_{i,j}$，$i$ 是已经连了的边，$j$ 是满足度为一的。

但是，你直接打状压，你会快乐开心的发现，你过不了样例。

一开始的 $dp$：

```cpp
for (int s = 0 ; s < cnt ; ++ s) if (Count(s) >= 2) {
	for (int t = 0 ; t < cnt ; ++ t) if (Count(s) >= 2 && (s & t) == t && dp[s][t]) {
		for (int j = 0 ; j < n ; ++ j) if (s & (1 << j)) {
			for (int k = 0 ; k < n ; ++ k) if (!(s & (1 << k)) && g[j][k] && j != k) {
				int now = (t & (1 << j)) ? t ^ (1 << j) ^ (1 << k) : t ^ (1 << k);
				dp[s | (1 << k)][now] += dp[s][t];
			}
		}
	}
}
```

她比答案大了许多……

这是为什么啊？？？

这是因为重复计算。

例如样例一：

```in
3 3 2
1 2
2 3
1 3
```

你先连 $\text{1,2}$ 再连 $1,3$，叶子节点是 $1,2$

你先连 $\text{1,3}$ 再连 $1,2$，叶子节点也是 $1,2$

然而，$\operatorname {dp}$ 的状态是一样的，就会重复了。

所以我们人为控制顺序，使得不会重复计算。

```cpp
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
	x = 0;T f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if (x < 0) putchar('-'),x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<typename T>T Min(T x,T y) {return x < y ? x : y;}
template<typename T>T Max(T x,T y) {return x > y ? x : y;}
template<typename T>T Abs(T x) {return x < 0 ? -x : x;}

int n,m,k,g[11][11];
int dp[1 << 10][1 << 10];

int Count(int x) {
	x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x & 0x0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f);
	x = (x & 0x00ff00ff) + ((x >> 8) & 0x00ff00ff);
	x = (x & 0x0000ffff) + ((x >> 16) & 0x0000ffff);
	return x;
}

void Print(int x) {
	for (int i = n - 1 ; ~i ; -- i) {
		print((x >> i) & 1);
	}
	puts("");
}

int main() {
	read(n);read(m);read(k);
	int x,y;
	for (int i = 1 ; i <= m ; ++ i) {
		read(x);read(y);
		x --,y --;
		g[x][y] = g[y][x] = 1;
	}
	for (int i = 0 ; i < n ; ++ i)
		for (int j = 0 ; j < n ; ++ j)
			if (g[i][j]) dp[(1 << i) | (1 << j)][(1 << i) | (1 << j)] = 1;
	int cnt = 1 << n;
	for (int s = 0 ; s < cnt ; ++ s) if (Count(s) >= 2) {
		for (int t = 0 ; t < cnt ; ++ t) if (Count(s) >= 2 && (s & t) == t && dp[s][t]) {
			for (int j = 0 ; j < n ; ++ j) if (s & (1 << j)) {
				for (int k = 0 ; k < n ; ++ k) if (!(s & (1 << k)) && g[j][k] && j != k) {
					int now = (t & (1 << j)) ? t ^ (1 << j) ^ (1 << k) : t ^ (1 << k);
					if (!((now >> k) ^ 1)) dp[s | (1 << k)][now] += dp[s][t];		//控制不重复计算
				}
			}
		}
	}
	int ans = 0;
	for (int i = 0 ; i < cnt ; ++ i) {
		if (Count(i) == k) ans += dp[cnt - 1][i];
	}
	print(ans);
	return 0;
}
```

---

## 作者：ZillionX (赞：2)

# Description

给定一张 $n$ 个节点和 $m$ 个边的无向连通图，求有 $k$ 个叶子结点的生成树个数。

$n,k \le 10, m \le \dbinom{n}{2}$，时限 5s。

# Solution

没有刻意卡常竟然一发跑到了[最优解](https://www.luogu.com.cn/record/list?pid=CF53E&orderBy=1&status=&page=1)……

------------

生成树计数问题显然考虑 Matrix Tree 定理，但是题目中加以了对叶子个数的限制，没有办法很好地应用结论。

不妨钦定一些点成为叶子，然后对剩下的点跑一遍 Matrix Tree，算出其生成树个数，然后再把钦定的点连上去，方案数乘起来即可。

这样计数显然会有重复，因为未钦定的点也有可能成为叶子。

假设我们现在已经得到了钦定集合 $S$ 成为叶子的方案数 $f_S$，考虑怎样得到恰好叶子集合是 $S$ 的方案数 $g_S$。不难发现，有

$$f_S=\sum_{T\&S=S} g_T$$

这是 FWT 的形式，对 $f_S$ 跑一遍 and 的 IFWT 即可。

至此我们在 $\mathcal O(n^32^n)$ 的时间复杂度下解决了本题，比枚举子集的 $\mathcal O(n^23^n)$ 状压 DP 不知道高到哪里去了。

# Code

```cpp
typedef long long LL;

const int N=15,S=(1<<10)+5;
const LL mod=998244353;

int n,m,q,c[S];
bitset<N> g[N];
LL f[N][N],u[S],Ans;
vector<int> v;

LL Gas(int n,LL f[N][N]) {
	LL x=1;
	for (int i=2;i<=n;i++)
		for (int j=i+1;j<=n;j++) {
			while (f[i][i]) {
				LL v=f[j][i]/f[i][i];
				for (int k=i;k<=n;k++) f[j][k]=(f[j][k]-f[i][k]*v%mod+mod)%mod;
				swap(f[i],f[j]),x=-x;
			}
			swap(f[i],f[j]),x=-x;
		}
	for (int i=2;i<=n;i++) x=x*f[i][i]%mod;
	return (x+mod)%mod;
}

int main() {
	scanf("%d%d%d",&n,&m,&q);
	if (n<=2) {
		printf("0");
		return 0;
	}
	
	for (int i=1;i<=m;i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		g[u][v]=1,g[v][u]=1;
	}
	for (int i=0;i<(1<<n);i++) c[i]=c[i>>1]+(i&1);
	for (int i=0;i<(1<<n);i++) {
		v.clear();
		for (int j=1;j<=n;j++)
			if (!(i&(1<<(j-1))))
				v.push_back(j);
		memset(f,0,sizeof(f));
		for (int j=0;j<v.size();j++)
			for (int k=j+1;k<v.size();k++)
				if (g[v[j]][v[k]])
					f[j+1][j+1]++,f[k+1][k+1]++,
					f[j+1][k+1]=f[k+1][j+1]=mod-1;
		u[i]=Gas(v.size(),f);
		for (int j=1;j<=n;j++)
			if (i&(1<<(j-1))) {
				int cnt=0;
				for (int k=1;k<=n;k++)
					if (g[j][k] && !(i&(1<<(k-1))))
						cnt++;
				u[i]*=cnt;
			}
	}
	
	for (int i=2,j=1;i<=(1<<n);i<<=1,j<<=1)
		for (int k=0;k<(1<<n);k+=i)
			for (int l=0;l<j;l++)
				u[k+l]-=u[j+k+l];
	
	for (int i=0;i<(1<<n);i++)
		if (c[i]==q) Ans+=u[i];
	
	printf("%lld",Ans);
	
	return 0;
}
```


---

## 作者：RockyYue (赞：1)

# 解题思路

感谢兔队审核~

数据规模 $n\le10$ 的 dp 题，显然为状压 dp。

定义 $dp[i][j]$ 表示目前生成树状态为 $i$ 时，其中度数为 $1$ 的点的状态为 $j$ 时的方案数。

对于加边，可以从连到度数为 $1$ 的点和其它点的情况中取最大值，状态转移方程见代码。


# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1 << 10;
int s[N], head[15], cnt;
long long dp[N][N];
struct edge {
	int v, nxt;
} e[205];
inline void add(int u, int v) {
    e[++cnt] = {v, head[u]};
    head[u] = cnt;
}
int main() {
    ios :: sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;
    while (m--) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    int S = (1 << n) - 1;
    for (int i = 1; i <= S; ++i) {
        for (int j = 1; j <= n; ++j) {
			if (i & (1 << j - 1)) {
				++s[i];
			}
        }
    }
	for (int i = 1; i <= n; ++i) {
		dp[1 << i - 1][1 << i - 1] = 1;
    }
	for (int i = 1; i <= S; ++i) {
		for (int j = i; j; --j &= i) {
			if (!dp[i][j]) {
				continue;
			}
			for (int p = 1; p <= n; ++p) {
				if (i & (1 << p - 1)) {
					for (int l = head[p]; l; l = e[l].nxt) {
						int v = e[l].v, t;
						if (i & (1 << v - 1)) {
                            continue;
                        }
                        t = s[i] == 1 ? (i | (1 << v - 1)) : (j & ~(1 << p - 1) | (1 << v - 1));
						if (!(t >> v)) {
                            dp[i | (1 << v - 1)][t] += dp[i][j];
                        }
					}
				}
			}
		}
    }
    long long res = 0;
	for (int i = 1; i <= S; ++i) {
		res += (s[i] == k) * dp[S][i];
	}
    cout << res << '\n';
    return 0;
}
```


Good Good 贺题，Day Day Up！！

---

## 作者：傅思维666 (赞：1)


## 题解：

[博客食用口味更佳](https://www.cnblogs.com/fusiwei/p/11851987.html)

~~2019.11.13CSP-S模拟赛满分场~~

#### 写在前面

众所周知，~~NOIP~~CSP-S模拟赛是一种奇妙的赛事，千万不要被它的名字迷惑。它属于一种类型和性质未知的比赛。在这种奇妙的比赛里，200行的树链剖分非模板题可以被出题人当作$D1\,\,T1$的水题来使用。$T3$如果不用黑题，那么这场比赛就会被成群的大佬吐槽过水。为了扩宽选手们的眼界，这种赛事~~大量~~适当地添加了些许超过联赛范围的知识点。具体可能为后缀自动机，NTT算法，LCT等等......

总之，蒟蒻被一顿惨虐，在一个月的煎熬和瑟瑟发抖后，蒟蒻终于迎来了在考场上切掉的为数不多的几道题...

#### 题解：

看这个数据范围，应该能想到状压DP，但是这个状态的设置比较伤脑筋。我们做状态压缩的时候很少见到过这种题目。但是根据动态规划的一般思路，我们可以确定动态规划状态的设置是基于问题边界的基础上的。于是我们仔细分析这道题的问题边界。假如我们要枚举的话，首先要枚举当前图所有的生成树，其次要枚举度为1的节点。那么就设置两维数组，第一维度存树的状态，第二维度存叶子节点的状态。

那么转移的时候会有两种更新的方式：第一种：把某个点加到一个叶子节点上，这个时候这个新节点就成为了叶子节点，叶子节点的数目是没有变化的。只是被替换了而已。第二种：把某个点加到非叶子节点上。这个时候新节点变成叶子节点，叶子节点的总数增加了1.

代码：

```cpp
#include<cstdio>
#include<vector>
#define int long long
using namespace std;
const int maxs=(1<<11)+10;
vector<int> map[20];
int dp[maxs][maxs],cnt[maxs];
//dp[i][j]表示生成树状态为i，度数为1的点状态为j的方案数
int n,m,k,ans;
signed main()
{
    for(int i=1;i<=maxs;i++)
        for(int j=0;j<15;j++)
            if(i&(1<<j))
               cnt[i]++;
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%lld%lld",&x,&y); 
        x--;y--;
        map[x].push_back(y);
        map[y].push_back(x);
    }
    for(int i=1;i<(1<<n);i<<=1) 
        dp[i][i]=1;
    for(int i=1;i<(1<<n);i++)
        for(int j=i;j;j--,j&=i)
            if(dp[i][j])
                for(int k=0;k<n;k++)
                    if(i&(1<<k))
                        for(int l=0;l<map[k].size();l++)
                        {
                            int to=map[k][l];
                            int now;
                            if(~i&(1<<to))
                            {
                                if(cnt[i]==1) 
                                    now=i|(1<<to);
                                else
                                    now=j&~(1<<k)|(1<<to);
                                if(!(now>>to+1)) 
                                    dp[i|(1<<to)][now]+=dp[i][j];
                            }
                        }
    for(int i=0;i<(1<<n);i++) 
        if(cnt[i]==k)
           ans+=dp[(1<<n)-1][i];
    printf("%lld",ans);
    return 0;
}
```



---

## 作者：kkkk0369 (赞：1)

题意在评论区有，这里就不赘述了。

这题妙啊，但我也不是太懂，看别人的方法学习了一波。

首先必定考虑DP，其次观察数据大小考虑状压DP，再看到答案求方案数考虑容斥。

DP数组$f[i][j]$表示当前已经考虑到$i$个点，$j$个点为死胡同，答案即为

$ans=\sum f[(1<<n)-1][i]$

由于图很小，使用邻接矩阵$g[i][j]$存图。

关于方程就判定生成是否合法即可（所以跟容斥有毛关系）。

代码如下：

```cpp
#include<cstdio>
using namespace std;
int n,m,k,x,y;
int g[20][20];//存图
int f[1050][1050];//考虑了i个点，j个点为死胡同
long long ans;
int cal(int x)
{
	int cnt=0;
	while(x) cnt++,x-=x&(-x);
	return cnt;
}//求二进制下“1”的个数 
int q(int x) { return (1<<x); }
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);x--;y--;int u=(1<<x)|(1<<y);
		g[x][y]=g[y][x]=1;f[u][u]=1;
	}
	for(int i=0;i<q(n);i++)
	for(int j=0;j<q(n);j++)
	if ((i&j)==j&&f[i][j])//j为i的子集且其有边
	for(int k=0;k<n;k++)
	for(int w=0;w<n;w++)
	if (g[k][w]&&(i&q(k))&&(~i&q(w))&&(!(((j&(~q(k)))|q(w))>>(w+1))))
	//判定合法条件有三： 
	//1.此边存在
	//2.此边未被入选但与图连通（可能成为死胡同）
	//3.((j&(~q(k)))|q(w))表示选择的边里是否包含这条边，右移判定其是否被选 
	f[i|q(w)][(j&(~q(k)))|(q(w))]+=f[i][j];//边(k,w)已经被考虑，将f[i][j]的答案转移 
	for(int i=0;i<q(n);i++)//答案为f[q(n)-1][i]
	if (cal(i)==k) ans+=f[q(n)-1][i];//当且仅当i满足cal(i)==k
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：xuantianhao (赞：0)

# [Dead Ends](https://www.luogu.com.cn/problem/CF53E)

$n\le10$，~~我还是第一次见到这么小的状压~~

我们设 $f[S][s]$ 表示：将集合 $S$ 内的点连成一棵树，且集合 $s$ 里的节点是叶子节点的方案数。

则有 

$$f[S\cup\{j\}][\{s\setminus i\}\cup\{j\}]+=f[S][s],i\in S,j\notin S,\exists(i,j)$$

但是，一棵树可能会被不同的顺序构造出来。因此有 $f[S][s]$ 应该除以 $|s|$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=11;
int n,m,P,lim,res,x,y;
int f[1<<N][1<<N],g[N][N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>n>>m>>P;
	lim=(1<<n);
    for(int i=1;i<=m;i++){
		cin>>x>>y;
		x--;y--;g[x][y]=g[y][x]=1;
		f[(1<<x)|(1<<y)][(1<<x)|(1<<y)]=2;
	}
    for(int p=1;p<lim;p++){
		for(int q=p;q;q=(q-1)&p){
		    f[p][q]/=__builtin_popcount(q);
		    for(int i=0;i<n;i++){
		        if(!(p&(1<<i))) continue;
		        int t=q&((lim-1)^(1<<i));
		        for(int j=0;j<n;j++){
		            if(p&(1<<j)||!g[i][j]) continue;
		            f[p|(1<<j)][t|(1<<j)]+=f[p][q];
		        }
		    }       
		}
	}
    for(int i=0;i<lim;i++)if(__builtin_popcount(i)==P) res+=f[lim-1][i];
    cout<<res;
    return 0;
}
```


---

## 作者：StayAlone (赞：0)

## 题意

给出一个简单无向图，求叶子节点数量为 $k$ 的生成树数量。叶子节点被定义为度数为 $1$ 的点。

## 思路

考虑状压。设 $s$ 是一个三进制数。$0$ 表示暂未选择，$1$ 表示叶子节点，$2$ 表示非叶子节点，则 $f_s$ 表示这种情况下的生成树数量。转移时枚举一个已经选择的点 $u$，连向一个暂未选择的点 $v$。此时 $u$ 必定成为非叶子节点，$v$ 必定是叶子节点。

发现会算重，进一步发现，答案会被算叶子节点的数量次。因此算完 $f_s$ 之后，除去其叶子节点数量就是真正的答案。

时间复杂度 $\mathcal O(n^2\cdot 3^n)$。

[AC record](https://www.luogu.com.cn/record/127132924)

```cpp
int n, m, k, d[15][15], pw[15]; ll f[MAXN], ans;

il int get(int x, int k) {
	return x / pw[k] % 3;
}

il int count(int x) {
	int cnt = 0;
	while (x) {
		cnt += x % 3 == 1;
		x /= 3;
	} return cnt;
}

il int popcount(int x) {
	int cnt = 0;
	while (x) cnt += x % 3 != 0, x /= 3;
	return cnt;
}

int main() {
	read(n, m, k); pw[0] = 1;
	rep1(i, 1, n) pw[i] = pw[i - 1] * 3;
	rep1(i, 1, m) {
		int u, v; read(u, v);
		--u; --v;
		d[u][v] = d[v][u] = 1;
		f[pw[u] + pw[v]] = 2;
	}
	const int P = pw[n] - 1;
	rep1(i, 1, P) if (f[i]) {
		int w = f[i] / count(i);
		rep1(u, 0, n - 1) if (int t = get(i, u)) {
			int s = i - pw[u] * t + pw[u] * 2;
			rep1(v, 0, n - 1) if (d[u][v] && !get(i, v)) f[s + pw[v]] += w;
		}
	}
	rep1(i, 0, P) if (popcount(i) == n && count(i) == k) ans += f[i];
	printf("%lld", ans / k);
	rout;
}
```

---

## 作者：lsj2009 (赞：0)

容易想到得是一个状压 $\text{dp}$，即考虑枚举当前生成树的节点集合，然后考虑往里面加点。具体地，在本题中，定义 $f_{S,T}$ 表示为当前选择节点集合为 $S$，叶子结点集合为 $T$，然后考虑转移方程。

显然的，第一眼想到下面得转移方程：

$$
\begin{cases}
& f_{S+\{v\},T-\{u\}+\{v\}}=\sum\limits_{u\in S\bigwedge u\in T\bigwedge (u,v)\in E} f_{S,T}\\
& f_{S+\{v\},T+\{v\}}=\sum\limits_{u\in S\bigwedge u\notin T\bigwedge (u,v)\in E} f_{S,T}
\end{cases}
$$

这里使用刷表法更易理解。

首先先写一条显然成立的引理：

> 对于任意合法的总结点集合 $S$ 和叶子节点集合 $T$ 满足 $T\subseteq S$。

- 证明：你如果都不在这棵树内，你怎么成为这棵树的叶子节点？

根据上面那条引理，可以得到的是如果 $u\in S$ 且 $u\in T$ 当且仅当 $deg_u=1$；如果 $u\in S$ 且 $u\notin T$ 当且仅当 $deg_u>1$。

然后我们依此取讨论上面两条转移方程：

1. 如果此时 $u\in S$ 且 $u\in T$，则 $deg_u=1$，再将 $u$ 向外连一条 $v$ 的边，则 $deg_u\gets deg_u+1\Rightarrow deg_u=2$，那么此时 $u\in S$ 但是 $u\notin T$，就要把 $u$ 从叶子集合删除；而 $deg_v\gets deg_v+1\Rightarrow deg_v=1$，则要将 $v$ 加入总节点集合和叶子节点集合。

2. 而如果此时 $u\in S$ 且 $u\notin T$，则 $deg_u>1$，再将 $u$ 向外连一条 $v$ 的边，则 $deg_u\gets deg_u+1$，那么此时 $u\in S$ 但是 $u\notin T$，但是 $u$ 本身就不在叶子节点集合当中，所以也不用“将 $u$ 从叶子节点删除”，所谓“光脚的不怕穿鞋的”，$u$ 直接将 $v$ 拉入 $S,T$ 集合。

然后对于初始状态有：

$$
f_{S,T}=
\begin{cases}
& 1 \quad\quad S=T=\{u\}+\{v\}\bigwedge (u,v)\in E\\
& 0 \quad\quad \text{otherwise}
\end{cases}
$$

这里是通过边直接进行初始化的，模拟赛时似乎有同学通过点来初始化，但是相对较为复杂。

仔细考虑，发现这种情况的统计其实时会有重复的：例如对于 $S=\{1,2,3\},T=\{1,3\}$ 且最初给定的图 $G=(V,E),V=\{1,2,3\},E=\{(1,2),(2,3)\}$ 这种情况，由 $S_1=\{1,2\}$ 和 $S_2=\{2,3\}$ 均可以转移过来，那么我们得到 $f_{S,T}=2$，其实 $f_{S,T}=1$，为什么？因为由于叶子节点的加入顺序不同，导致方案数重复，所以我们应当令 $f_{S,T}\gets \frac{f_{S,T}}{|T|}$。

那么最终答案则是 $\sum\limits_{|T|=k} f_{\{u|u\in V\},T}$。

---

## 作者：Aleph1022 (赞：0)

考虑枚举一个点集 $S$，表示钦定 $V\setminus S$ 的点为叶子，计算出方案数，那么答案就是对其执行 IFMT 的结果。

要计算这个，可知只需算出 $S$ 的导出子图的生成树个数，然后为每个 $V\setminus S$ 中的点选择一条连向 $S$ 中的边即可。  
后者只需 $O(n 2^n)$，现在我们来说明前者可以做到 $O(n^2 2^n)$。

考虑枚举 $k=1,\dots,n$，依次计算所有 $S \subseteq \{1,\dots,k\}$ 的答案。  
考虑每次加入一个点 $k+1$，对于 $S \subseteq \{1,\dots,k\}$，我们考虑如何在其中加入 $k+1$。  
自然只需枚举断开 $k+1$ 后会构成哪些连通块，不难发现这就是一个集合幂级数的 exp 操作。

核心代码（执行完后 $f_S$ 为 $S$ 导出子图的生成树个数，$e_u$ 为邻接矩阵，$\exp$ 表示将 $f_{2^k,\dots,2^{k+1}-1}$ 原地 $\exp$）：
```cpp
f[0] = 1;
for (int k = 0; k < lg; ++k) {
  for (int i = 0; i < (1 << k); ++i) f[i + (1 << k)] = (ll)f[i] * popcnt(e[k] & i) % mod;
  Set::exp(f + (1 << k), f + (1 << k), k);
}
```

时间复杂度由 $T(n) = T(n-1) + O(n^2 2^n)$ 得到，为 $O(n^2 2^n)$。  
从而这也叫做**逐点牛顿迭代法**。

---

