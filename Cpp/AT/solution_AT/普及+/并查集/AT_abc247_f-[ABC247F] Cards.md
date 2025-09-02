# [ABC247F] Cards

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc247/tasks/abc247_f

$ 1,\ldots,N $ の番号がついた $ N $ 枚のカードがあり、カード $ i $ の表には $ P_i $ が、裏には $ Q_i $ が書かれています。  
 ここで、$ P=(P_1,\ldots,P_N) $ 及び $ Q=(Q_1,\ldots,Q_N) $ はそれぞれ $ (1,\ 2,\ \dots,\ N) $ の並び替えです。

$ N $ 枚のカードから何枚かを選ぶ方法のうち、次の条件を満たすものは何通りありますか？ $ 998244353 $ で割った余りを求めてください。

条件：$ 1,2,\ldots,N $ のどの数も選んだカードのいずれかに書かれている

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ P_i,Q_i\ \leq\ N $
- $ P,Q $ はそれぞれ $ (1,\ 2,\ \dots,\ N) $ の並び替えである
- 入力に含まれる値は全て整数である

### Sample Explanation 1

例えばカード $ 1,3 $ を選ぶと、$ 1 $ はカード $ 1 $ の表に、$ 2 $ はカード $ 1 $ の裏に、$ 3 $ はカード $ 3 $ の表に書かれているため条件を満たします。 条件を満たすカードの選び方は $ \{1,3\},\{2,3\},\{1,2,3\} $ の $ 3 $ 通りです。

## 样例 #1

### 输入

```
3
1 2 3
2 1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
5
2 3 5 4 1
4 2 1 3 5```

### 输出

```
12```

## 样例 #3

### 输入

```
8
1 2 3 4 5 6 7 8
1 2 3 4 5 6 7 8```

### 输出

```
1```

# 题解

## 作者：Proxima_Centauri (赞：17)

[雅虎曰：原题传送门](https://www.luogu.com.cn/problem/AT_abc247_f)

~~题意不需要翻译吧。~~

# 分析
我们考虑给对应数字所在的卡片建边。

那么我们会发现，生成的图肯定是若干个连通块，每个连通块都恰好是一个环（或者单独一个点）。而每一条边的两边都至少要取一个点。

所以我们只需要考虑，每一个环有多少种方案，最后根据乘法原理把它们相乘就可以了。

不难发现，环的贡献只与环的大小有关。我们设 $f[i]$ 表示总共有 $i$ 个点的环的方案数。

这个东西看着就像一个 DP 的样子······所以我们尝试一下：经过列举以后发现：$f[1] = 1, f[2] = 3, f[3] = 4, f[4] = 7, f[5] = 11$，不难猜出一个结论：
$$f[i] = f[i - 1] + f[i - 2]$$
这个结论的证明，我是参考了 lfyszy 大佬的方法的：

假设环上总共有 $n$ 个点，其中有三个点：$A$ 点，它两边的 $B$ 点和 $C$ 点，环上剩余的部分用 $O$ 表示。

那么，我们考虑是否选 $A$ 点。
- 选 $A$ 点

那么 $B$ 点和 $C$ 点就可以任取了，所以这个环就变成了一个 $B + O + C$ 的链，这个链不好计算，我们不妨作一条辅助线——连接 $BC$。作完辅助线以后，这个图的答案就是 $f[n - 1]$，但是我们还漏算了一种情况，就是 $B,C$ 两个点都不取的情况。我们把这两个点压成一个点 $P$。我们设不取 $P$ 的答案是 $k$。
- 不选 $A$ 点

那么 $B$ 点和 $C$ 点就都必须选。所以我们可以把两个点还有 $A$ 压成一个点 $P$。此时新图的答案就是 $f[n - 2]$。但是我们多算了一种情况——在新图里不取 $P$ 的情况。这时，我们发现：这种情况的个数恰好就是上文提到的 $k$！

所以答案就非常明显了：
$$f[n] = f[n - 1] + k + f[n - 2] - k = f[n - 1] + f[n - 2]$$
得证万岁！

那么最后还面临着一个小问题——怎么计算连通块里面点的个数。相信大家心里都在默念一个词——**并查集**！

没错，使用并查集算法求解即可。
# AC code
```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[200010], b[200010]; 
long long f[200010];
int fa[200010], siz[200010];
int p[200010];
int n;
const int mod = 998244353; //别忘了取模！
void F()
{
	f[1] = 1, f[2] = 3;
	for (int i = 3; i <= n; i++)
		f[i] = (f[i - 1] + f[i - 2]) % mod;
}//计算f[i]
int find(int x)
{
	while (x != fa[x]) x = fa[x];
	return fa[x];
} 
void merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	if (fx != fy) 
	{
		fa[fx] = fy;
		siz[fy] += siz[fx];
	}
}//并查集基本操作
int main()
{
	cin >> n;
	F();
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		p[a[i]] = i;//标记正面写着a[i]的卡片标号
		siz[i] = 1;
		fa[i] = i;//并查集的初始化
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> b[i];
		//p[b[i]]和i建边
		merge(i, p[b[i]]);
	}
	long long ans = 1; //乘法原理求答案
	for (int i = 1; i <= n; i++)
		if (i == fa[i]) 
		{
			ans *= f[siz[i]];
			ans %= mod;
		}
	cout << ans << endl;
	return 0;
}
```
# 总结与反思
这个题的思维难度其实还是挺高的，值得被评绿题。关键在于想到建边的操作，然后求 $f[i]$ 的过程其实很简单，但是证明不太好想，后面并查集还是挺明显的。

最后提醒一句：

别忘了取模！！！

---

## 作者：Alexandra (赞：9)

## 前言

第一篇绿题题解。

## 题目大意
每张卡片的正面与背面各有一个数，保证正面的数构成的序列，和反面的数构成的序列，分别均为 $1$ 到 $n$ 的排列。  

求出选择任意张卡片能使 $1-n$ 各出现至少一次的方案数。


## 题目分析

首先分析第二组样例：
```
5
2 3 5 4 1
4 2 1 3 5
```

将 $1-n$ 每个数所出现的卡片的序号之间建一条边。例如，$3$ 出现在第 $2$ 张与第 $4$ 张上卡片，那么我们将 $2$ 与 $4$ 之间连一条边。  
那么题目中每个数均要出现至少一次的要求就可以**转换**为每条边的两个端点至少选择一个。  

每张卡片上只有两个数字，故一个点最多只能向外连两条边，所以最终的图应为**若干个环**。  
此样例建图如下：  
![](https://cdn.luogu.com.cn/upload/image_hosting/mo4zbycn.png)  

各个环之间是**不会互相干扰**的，所以只需要分别求出每个环的选择方案数，再依据乘法原理相乘便得出最终的答案。  
此时各个环上的方案数只与环的大小有关，与环上每个点的编号无关，所以我们可以**预处理**出大小为 $s$ 的环的选择方案数 $F_s$。  

手推出：
$$ F_1=1$$
$$ F_2=3$$
$$ F_3=4$$
$$ F_4=7$$
$$ F_5=11$$
大胆猜测通项公式为:
$$F_n=F_{n-1}+F_{n-2}$$
接下来证明一下，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/4yki6ztc.png)  
如果点 $n$ 被选择，那么点 $1$ 与点 $n-1$ 无限制，此时方案数为 $F_{n-1}$。  
如果点 $n$ 不选，那么 $1$ 与 $n-1$ 是必须选的，此时我们可以将 $1$、$n-1$、$n$ 这三个点缩成一个，那么此时方案数就是 $F_{n-2}$。  

所以最终的方案数就是 $F_{n-1}+F_{n-2}$。


## 代码  
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 200100
#define mod 998244353
long long n,m,ans=1,fa[N],b[N],s[N],f[N];
inline long long read()
{
	long long jia=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')flag*=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		jia=(jia<<1)+(jia<<3)+(ch^48);
		ch=getchar();
	}
	return jia*flag;
}
long long Find(long long x)
{
	if(fa[x]==x)return x; 
	return fa[x]=Find(fa[x]);
}
inline void add(long long x,long long y)
{
	long long xx=Find(x),yy=Find(y);
	if(xx!=yy)fa[xx]=yy,s[yy]+=s[xx];
}
int main ()
{
	n=read();
	f[1]=1,f[2]=3;
	for(long long i=1;i<=n;i++)
	{
		fa[i]=i,s[i]=1;
		if(i!=1&&i!=2)f[i]=(f[i-1]+f[i-2])%mod;
		long long wjl=read();
		b[wjl]=i;
	}
	for(long long i=1;i<=n;i++)
	{
		long long wjl=read();
		add(b[wjl],i);//利用并查集求出每个环的大小 
	}
	for(long long i=1;i<=n;i++)
	{
		if(fa[i]==i)ans=f[s[i]]*ans%mod;
	}
	printf("%lld\n",ans%mod);
	return 0;
}
```



---

## 作者：IcyL (赞：3)

# 思路
我们可以非常自然地想到在两个拥有相同数的卡片连边，则两点间必须选一个。

由于每张卡有两个数，度数为二，则连完后必定会形成若干个环。

根据乘法原理，我们需要对于每个环求出方案数后相乘。

我们令 $f_i$ 表示一个大小为 $i$ 的图的方案数，则有：

$$f_i = f_{i - 1} + f_{i - 2}$$

（~~但这当然是找规律出来的~~）

咳咳，接下来我们要证明它。

首先我们有这样一个环：

[![pPZXPbD.png](https://s1.ax1x.com/2023/08/09/pPZXPbD.png)](https://imgse.com/i/pPZXPbD)

（$C$ 是环的剩余部分，并不是一个点）

我们来分类讨论一下：

1.选 $A$ 点：

方案数就是这样一张图的方案数：

[![pPZX9KK.png](https://s1.ax1x.com/2023/08/09/pPZX9KK.png)](https://imgse.com/i/pPZX9KK)

（图一）

但这并不好算，所以我们把它补成一个环：

[![pPZXCDO.png](https://s1.ax1x.com/2023/08/09/pPZXCDO.png)](https://imgse.com/i/pPZXCDO)

但环的方案数似乎并不等于上面的图，是因由于 $A$ 点被选过，则 $B1$、$B2$ 是可以不选的，所以我们要把它加回来。

那可以把 $B1$、$B2$ 压成一点：

[![pPZXcxx.png](https://s1.ax1x.com/2023/08/09/pPZXcxx.png)](https://imgse.com/i/pPZXcxx)

所以我们可以令 $\Delta_1$ 等于图一中 $B$ 不选时方案数。

（为什么不算？往下看）

2.不选 $A$ 点：

方案数就是这样一张图，且 $B1$、$B2$ 必选的方案数：

[![pPZX9KK.png](https://s1.ax1x.com/2023/08/09/pPZX9KK.png)](https://imgse.com/i/pPZX9KK)

由于两点都必选，所以可以压成一点。

[![pPZXcxx.png](https://s1.ax1x.com/2023/08/09/pPZXcxx.png)](https://imgse.com/i/pPZXcxx)

这张图的方案数是 $f_{i - 2}$，可算多了，因为 $B$ 必选。

所以要减掉 $\Delta_2$ 为上图 $B$ 不选时方案。

有没有发现 $\Delta_1 = \Delta_2$?

所以可以得出：
$$f_i = f_{i - 1} + f_{i - 2}$$

实现：

并查集就可以了！详细部分看代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define PII pair<int, int>
#define x first
#define y second
using namespace std;
const int N = 2e5 + 10, mod = 998244353;
int fa[N], cnt[N];
int F[N];
int c[N];
int find(int x)
{
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i ++)
    {
        int co;
        cin >> co;
        c[co] = i;
        fa[i] = i;
    }
    for(int i = 1; i <= n; i ++)
    {
        int x;
        cin >> x;
        fa[find(i)] = find(c[x]);
    }
    for(int i = 1; i <= n; i ++) cnt[find(i)] ++;
    F[1] = 1;
    F[2] = 3;
    for(int i = 3; i < N; i ++) F[i] = (F[i - 1] + F[i - 2]) % mod;
    int ans = 1;
    for(int i = 1; i <= n; i ++) ans = (ans * max(F[cnt[i]], 1LL)) % mod;
    cout << ans << "\n";
    return 0;
}

```

---

## 作者：__XU__ (赞：2)

## AT\_abc247\_f 题解

### 思路

将所有卡牌的正反面建一条边（可以用并查集来实现），所以当我们需要取任意一点时，卡牌所连带的面都会被选。所以我们定义 $f$ 存方案数。

### 做法

情况一：当你不选这条边时，因为需要满足题目要求（得的数至少包含 $1 \sim n$ 至少一次）。后面还会选到这个未选的数。（也可以成为与他相邻的两条边必选）。此时的 $f_i=f_{i-2}$。

情况二：当你选当前这条边时，所以与他相邻的边就不必选（也可以选）。所以此时的 $f_i=f_{i-1}$。

最后，$f_i = f_{i-1} + f_{i-2}$。

### 分享另一种推导方法

$f_1=1,f_2=3, f_3 = 4, f_4 = 7 \dots$

所以，$f_i = f_{i-1} + f_{i-2}$。

### AC CODE

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,EN=998244353;
int n;
int f[N];
int p[N],h[N],sum[N];
map<int,int> a;
map<int,int> b;//a正 b反
long long ans=1; 
int get(int x){
	if(x!=p[x]){
		p[x]=get(p[x]);
	}
	return p[x];
}
void l(){//杂碎 
	f[1]=1,f[2]=3;//分情况 
	for(int i=1;i<=n;i++){
		if(i>=3){
			f[i]=(f[i-1]+f[i-2])%EN;
		}
		p[i]=i;
		sum[i]=1;
	}
} 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	l();
	for(int i=1;i<=n;i++){
		cin>>a[i];
		h[a[i]]=i;//统计正面卡牌 
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		int xx=get(h[b[i]]),zz=get(i);
		if(xx!=zz){
//			cout<<sum[xx]<<' '<<sum[zz]<<'\n';
			p[xx]=zz;
			sum[zz]+=sum[xx];
//			cout<<sum[xx]<<' '<<sum[zz]<<'\n';
		}
	}
	for(int i=1;i<=n;i++){
		if(p[i]==i){
//			cout<<"HHH";
//			cout<<f[i]<<' ';
			ans*=f[sum[i]];
			ans%=EN;
		}
	} 
	cout<<ans;
	return 0;
} 
```

谢谢观看。

---

## 作者：zsyzsy_2012 (赞：2)

一道有一些难度的并查集套动态规划。

很容易想到每次把正、反面的两个数值连边，并用并查集合并，最后得出若干个已经算好元素个数的集合，元素个数之和为 $n$。

接下来的重点是如何求一个元素个数为 $n0$ 的集合的答案。容易得到，它里面连的边一定构成一个圆环。所以我们考虑 DP，用 $dp _ {i}$ 表示元素个数为 $i$ 的集合的答案。

有了状态，我们再来考虑转移。方便起见，我们称拿走有 $i$ 和 $i-1$ 的卡片为选 $i$ 。如果选 $i$，必须带上 $i-1$，当前种数应加上 $dp _ {i-2}$。如果不选 $i$，种数应加上 $dp _ {i}$。所以我们得到递推式：$dp _ {i} = dp _ {i - 1} + dp _ {i - 2}$。初始值：$dp _ {0}=2$，$dp _ {1}=1$。当前答案：$dp _ {n0}$。最终的答案就是每个连通块算出来的那个值相乘，最后别忘了取模。

下面是我的代码。

```
#include <bits/stdc++.h>
using namespace std;
const int N=200005,P=998244353;
int n,x[N],y,ans=1,fa[N],cnt[N],dp[N];
int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
void merge(int x,int y){
	int x0=getfa(x),y0=getfa(y);
	fa[x0]=y0;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&x[i]),fa[i]=i;
	for(int i=1;i<=n;i++){
		scanf("%d",&y);
		merge(x[i],y);
	}
	for(int i=1;i<=n;i++)cnt[getfa(fa[i])]++;
	for(int i=1;i<=n;i++){
		if(!cnt[i])continue;
		dp[0]=2,dp[1]=1;
		for(int j=2;j<=cnt[i];j++)dp[j]=(dp[j-1]+dp[j-2])%P;
		ans=1LL*ans*dp[cnt[i]]%P;
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：_Flame_ (赞：1)

### $\text{solution}$

套路题。

套路的把有相同颜色的卡片连边，会形成一些互不影响连通块。

对于每一个连通块计数，首先发现一张卡片最多向外连两条边所以每个块一定是单点或者环，题目转化为在一个环上选点，使得每一条边两边的点都至少有一个被选。

对于每一个点分讨，可以发现对于一个点，若这个点选，则两边的点任选，若不选，则两边的点必选。选的情况相当于把环变成一个点数少一的环，不选的情况对应一个点数减少二的环。

所以得到转移 $dp_{i}=dp_{i-1}+dp_{i-2}$ 其中 $dp_1=1$，$dp_2=3$。

并查集维护连通块大小即可。

---

## 作者：zhr2021 (赞：1)

# [AT_abc247_f [ABC247F] Cards](https://www.luogu.com.cn/problem/AT_abc247_f) 题解
## solution
与本题多数题解一样，先建图，发现图必然由一些简单环组成，且一个环中如何选卡片（即选边）不影响其他环。说明了环之间的方案数符合乘法原理。

此时，环内的方案计算成为本题重点。直接选边不好选，考虑删边，因为删边的限制很明确：**删的任意两条边不能接在同一点上（即不相邻）。**

设环边数为 $n$，要删 $k$ 条边。先断环为链，在链上选 $k$ 个元素不相邻的方案为 ${n-k+1} \choose {k}$。又发现这样计算会出现同时选择首尾两条边，首尾相接时就不合法了。减去首尾同时删去的方案，相当于强制选择首尾，只剩 $k-2$ 个元素和 $n-4$ 个位置可自由选择，方案为 ${(n-4)-(k-2)+1}\choose {k-2}$。

因此每个环的方案数 $f_n$ 为：
$$ f_n= \sum_{k=0}^{\lfloor \frac{n}{2} \rfloor} {{n-k+1}\choose {k}}-{{n-k-1}\choose{k-2}}$$
总方案数为：
$$ans=\prod f_{siz}$$
时间复杂度 $O(n)$。
## code

```cpp
#include<bits/stdc++.h>
#define L long long
using namespace std;
const L N=2e5+10,mod=998244353;
L n,a[N],b[N],f[N],siz[N],ans=1;
L froot(L x){while(f[x]!=x)x=f[x]=f[f[x]];return x;}
L fac[N],inv[N];
L qpow(L x,L d){
	L r=1;
	while(d){
		if(d&1) r=r*x%mod;
		x=x*x%mod;
		d>>=1;
	}
	return r;
}
L C(L n,L m){
	if(n<0||m<0||n<m) return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main(){
	fac[0]=1;
	for(L i=1;i<N;i++) fac[i]=fac[i-1]*i%mod;
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(L i=N-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	scanf("%lld",&n);
	for(L i=1;i<=n;i++){
		f[i]=i,siz[i]=1;
		scanf("%lld",&a[i]);
	}
	for(L i=1;i<=n;i++){
		scanf("%lld",&b[i]);
		L fa=froot(a[i]),fb=froot(b[i]);
		if(fa!=fb){
			f[fa]=fb;
			siz[fb]+=siz[fa];
		}
	}
	for(L i=1;i<=n;i++){
		if(f[i]==i){
			L k=siz[i],cnt=0;
			for(L j=0;j*2<=k;j++){
				cnt=(cnt+C(k-j+1,j)-C(k-j-1,j-2)+mod)%mod;
			}
			ans=ans*cnt%mod;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Shunpower (赞：1)

## 思路

正如其他所有题解说的那样，我们拿到这道题可以非常自然地想到每一张卡片的正反面连无向边。这样做，因为正反面数一定都是排列，所以每个点的度数一定都是 $2$，所以一定可以连出来一堆简单环和自环。

我们不妨去掉自环，因为自环意味着一张卡正反都是一个数，那么不选这张卡我们一定会损失掉这个数，所以一定要选这张卡，所以去掉这个自环不影响我们计数方案数。

去掉自环之后，我们的问题变成计数选择一些无向边的方案数，使得这些边两端的节点的点集是所有点。因为都是简单环，所以每个点都在且仅在一个环上，所以我们可以对每个环分开考虑，每个环都需要计数选出一些无向边使得包含整个环上的所有点的方案数，把每个环的方案数乘起来就是总答案。

接下来考虑如何计数一个环上选择边的方案使得边两端的点的点集是环上所有点。

我发现不了方案数是斐波拉契数列还不会 dp，怎么办？！不妨假设环长为 $k$，很明显在环上 $k$ 既是环点数又是环边数。

不妨我们钦定环上一个点，把它拆成两个点，一个作为环起点，一个作为环终点，这两个点之间不连边。这个环就变成了链。问题就转变为：计数在链上选一些边，使得每一个点两边都至少有一条被选的边，并且不能同时不选 $1$ 和 $k$ 的方案数。
 
枚举这条链上有 $i$ 条边不选，很明显需要满足 $2(k-i)\geqslant k$。

断掉这 $i$ 条不选的边之后，整个链被分成了 $i+1$ 个部分，我们要求这 $i+1$ 个部分中不能有单点。现在我们不妨改成选择哪些边被断掉，也就是说，要在 $k$ 个位置中选中 $i$ 个，使得任意两个都不相邻，并且不能同时选 $1$ 和 $k$。

如果你认真阅读了《组合数学》第二章的内容，你会发现这差不多就是习题的第 $39$ 题。你可以通过将相邻两个位置的下标做差**再减一**的方式得到 $i+1$ 个变量（包括用第一个位置与 $0$，$n$ 与最后一个位置），然后要求这 $i+1$ 个变量的和为 $k-i$，并且每一个都需要 $>0$。更加形象地，体现在链上就是两个相邻的被断边之间有多少个未断边。很明显利用隔板法可以知道这样做的方案数是 $k-i-1\choose{i}$。

但是你可以发现这个方案有点问题，就是因为要求了最左边和最右边的变量都要 $>0$，所以我们根本选不上 $1$ 或者 $k$。考虑钦定必然有一条边是 $1$，于是不能选 $2$ 或 $k$，可以发现非常优美地，我们相当于是要在 $2\sim k$ 中做一样的问题（不允许选 $2$ 也不允许选 $k$），于是方案数就是 ${k-1-(i-1)-1\choose{i-1}}={k-i-1\choose{i-1}}$，这里用 $k-1$ 是因为我们已经钦定掉一条边了。

钦定 $k$ 的时候是同理的。

于是我们可以得到断掉 $i$ 条边，使得剩余边的两端构成的点集是所有点的方案数为 $2{k-i-1\choose{i-1}}+{k-i-1\choose{i}}$。

于是先用并查集分离环，然后就可以得到环长，对于每个环枚举断边数量，总共就只需要枚举 $O(n)$ 次（环长和），而每次计算方案数是 $O(\log P)$ 的，于是总时间复杂度为 $O(n\log P)$。

## 代码

下面是核心部分的代码：

```
fr1(i,1,n){
	bol[finder(i)]++;
}
fr1(i,1,n){
	if(bol[i]>1){
		ans=0;
		int x=bol[i];
		fr1(j,0,x){
			if(2*(x-j)<x){
				break;
			}
			ans+=(2ll*C(x-j-1,j-1)%M+C(x-j-1,j))%M;
			ans%=M;
		}
		mulans*=ans;
		mulans%=M;
	}
}
```

这里用的 `C(n,m)` 表示计算 $n\choose m$。

[AC 记录](https://www.luogu.com.cn/record/119827129)

---

## 作者：CQ_Bab (赞：1)

# 前言
某同学在补题开始后竟用 $0$ 罚时过前三道题，而考试时却一道题也切不出来，可还是吊打我。
# 思路
我们可以发现，在正面包含 $i$ 和反面包含 $i$ 的两张卡片中必须选一张，那么我们就可以对于包含 $i$ 的两张卡片连边，然后我们就能得到一些环，因为对于每一张卡片的出度都为 $2$ 然后我们就可以用一个排列组合来计算方案数。我们先来举个例子，当环内大下为 $1$ 时共 $1$ 中取法，当大下为 $2$ 时共 $3$ 种取法，当大小为 $3$ 时共 $4$ 种取法，当大小为 $4$ 时共 $7$ 种取法。乍一看没什么规律，再仔细一看，这不就是一个变种的斐波那契数列吗？然后，我们就可以先预处理出来即可，这里统计环的大下可以用并查集完成。
# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a);
		a=a*a;
		b>>=1;
	}
	return res;
}
void read(int &x) {
	x=false;
	ri f=1;
	char c=getchar();
	while(c>'9'||c<'0') {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c-'0'<=9&&c>='0') {
		x=x*10+c-'0';
		c=getchar();
	}
	x*=f;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int n;
pair<int,int>a[200100];
const int mod=998244353;
int f[200100];
int fa[200100],siz[200100];
int find(int x) {
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
fire main() {
	f[1]=1;
	f[2]=3;
	rep(i,3,200000) f[i]=(f[i-1]+f[i-2])%mod; //预处理
	cin>>n;
	rep(i,1,n) {
		int x;
		cin>>x;
		a[x].first=i;
	}
	rep(i,1,n) {
		int b;
		cin>>b;
		a[b].second=i;
	}
	rep(i,1,n) {
		fa[i]=i;//初始化
		siz[i]=1;
	}
	rep(i,1,n) {
		int tx=find(a[i].first),ty=find(a[i].second); //合并
		if(tx==ty) continue;
		siz[tx]+=siz[ty];
		siz[ty]=0;
		fa[ty]=tx;
	}
	int res=1;
	rep(i,1,n) {
		if(fa[i]==i) {
			res=(res*f[siz[find(i)]])%mod; //排列组合
//			cout<<i<<endl;
		}
	}
	print(res);
	return false;
}

```

---

## 作者：under_the_time (赞：0)

## 题意

> 有 $n$ 个卡片，第 $i$ 张卡片正面为 $p_i$ 背面为 $q_i$（$p,q$ 两个数组均为 $1\sim n$ 的排列），求：选择若干张卡片使得 $1\sim n$ 在选择的卡片正面和背面中至少出现一次的方案数。
>
> $n\le 2\times 10^5$。

## 解法

考虑一个等价转换：对于**数字** $i$，我们将它所在的两张（或者一张，此时为自环）卡连一条边。对于建出的图，边代表数字，点代表卡牌，$1,2,\cdots,n$ 至少出现一次转化为**每个端点至少被一条边覆盖**。由于每个点连出去两条边（正反各一个数字），最终的图一定由若干个不相交的环组成，环与环之间独立，只需计算每个环的答案然后乘起来即可。注意到环的答案只与环的大小有关，设大小为 $m$ 的环答案为 $f(m)$，手模一下：
$$
f(1)=1,f(2)=3,f(3)=4,f(4)=7,\cdots \Rightarrow f(m)=f(m-1)+f(m-2)
$$
环的大小用并查集维护即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5, P = 998244353;
int n, p[maxn];
namespace DSU {
    int fa[maxn], siz[maxn];
    int find(int u) { return fa[u] == u ? u : fa[u] = find(fa[u]); }
    void Union(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return ;
        siz[u] += siz[v], fa[v] = u;
    }
    void init1() { for (int i = 1; i <= n; i ++) fa[i] = i, siz[i] = 1; }
} using namespace DSU;
namespace Fab {
    int f[maxn];
    void init2() {
        f[1] = 1, f[2] = 3;
        for (int i = 3; i <= n; i ++) f[i] = (1ll * f[i - 1] + 1ll * f[i - 2]) % P;
    }
} using namespace Fab;
int main() {
    scanf("%d", &n); init1(), init2();
    for (int i = 1, x; i <= n; i ++)
        scanf("%d", &x), p[x] = i;
    for (int i = 1, x; i <= n; i ++)
        scanf("%d", &x), Union(p[x], i);
    int ans = 1;
    for (int i = 1; i <= n; i ++) 
        if (fa[i] == i) ans = (1ll * ans * f[siz[i]]) % P;
    return printf("%d", ans), 0;
}
```

---

## 作者：彭俊皓123 (赞：0)

# AT_abc247_f 题解

不得不说样例还是构造得蛮巧妙的，

恰好构造出了答案为点数加一的组合，推式子错了直接爆 WA。

## 题意

给定 $n$ 张卡牌，每张卡牌都有正反两面，均写着 $[1,n]$ 范围内的一个数字。

找出选牌组合的数量，使得选的牌中的正反面的数中 $[1,n]$ 均有至少一张。

**tips：正面和反面的数都能算入记数的贡献，而不是每个牌只能贡献一次。**

~~因为没理解这个差点没想出来。~~~~

## 分析

既然每张牌都有正反两个面，不难想到将其转化为边。

因此问题转化为找出所有能覆盖所有点的边的组合的数量。

建完图之后发现这 $n$ 个点形成了若干个类基环树的连通块。

>>由于可能正反两面数值相等而导致形成自环，不能直接说是基环树。

然而 **不在环上的点所连的边是必选的**，于是不纳入我们的考虑范围。

### 我们只考虑处理环上的点：

由于不在一个连通块内的边的选择是互不干扰的，

设长度为 $x$ 的环的可行方案数为 $f(x)$。

由乘法原理可知，$ans=\prod \limits_{x}f(x)$。

于是考虑如何处理出 $f(x)$。

然后，在~~手搓模拟~~严谨分析之后，我们得到了两组数据：$f(2)=3,f(3)=4$。

是不是以为 $f(x)=x+1$ 就是真正的结果了？

### 然而，当我们继续模拟 $x=4$ 的情况：

设边分别为 $A,B,C,D$，为了保证所有点都被选到，至少要选两条边。

#### 1.选择两条边时：

显然是互不相连的两条边，即 $A,C$ 或 $B,D$ 共两种情况。

#### 2.选择三条边时：

只有一条边不会被选择，因此显然有四种情况。

#### 3.选择四条边时：

全选时只有一种情况。

于是我们得到了 $f(4)=7$ 而不是 $5$，这显然与我们之前的推论不符。

### 于是可以再试试 $x=5$ 的情况：

设边分别为 $A,B,C,D,E$，为了保证所有点都被选到，至少要选三条边。

#### 1.选择三条边时：

答案有 $A,B,D$ 或 $A,C,E$ 或 $A,C,D$ 或 $B,C,E$ 或 $B,D,E$ 共五种情况组成。

#### 2.选择四条边时：

由于只有一条边不选，可以发现有五种情况。

#### 3.选择五条边时：

全选时只有一种情况。

于是我们得到了 $f(5)=11$。

到这里规律应该很明显了，显然有：

$$
f(x)=
\begin{cases}

3,x=2\\
4,x=3\\
f(x-1)+f(x-2),x>3

\end{cases}
$$

于是就求出了 $f(x)$ 的数值，这道题就基本上结束了。

剩下的就是将点通过并查集之类的操作分为几个连通块，

然后按照拓扑排序将不在环上的点删去，

接着直接按照公式求解即可。

**如果你是通过在环上深搜得出的结果，请注意你是否在返回时漏了一条边。**

**记得 $f(x)$ 也是需要取模的！！！**

## 证明

对于 $n$ 个点，将其看为 $n$ 个只包含一个点的连通块。

先只考虑某一条边，如果这条边不选，则转化为 $n-2$ 个连通块的情况，

否则就转化为 $n-1$ 个连通块的情况。

于是只要得到了 $f(1)=1,f(2)=3$，便可递推解出 $f(x)$ 了。

## 代码
```cpp
#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;
const int MAXN=400005,modd=998244353;
int a,b,c,dft=0;
int num[MAXN],dfn[MAXN],fa[MAXN],in[MAXN];
int que[MAXN],bj[MAXN],dp[MAXN][2];
ll sum[MAXN];
vector<int> edge[MAXN];
inline int read()
{
    char x=getchar();int t=0;
    while(!isdigit(x))x=getchar();
    while(isdigit(x))t=(t<<3)+(t<<1)+(x^48),x=getchar();
    return t;
}
int getfa(int x)
{
    if(x==fa[x])return x;
    return fa[x]=getfa(fa[x]);
}
void dfs(int x)
{
    for(auto now:edge[x])
    {
        if(getfa(now)!=getfa(x))
            fa[now]=x,dfs(now);
    }
}
void topo()
{
    int head=1,tail=0;
    for(int i=1;i<=a;++i)
        if(in[i]==1)que[++tail]=i;
    while(head<=tail)
    {
        int x=que[head++];
        for(auto now:edge[x])
        {
            in[now]--;
            if(!in[now])que[++tail]=now;
        }
    }
}
int row(int x)
{
    bj[x]=1;
    for(auto now:edge[x])
    {
        if(in[now]&&!bj[now])return row(now)+1;
    }
    return 1;
}
int main()
{
    sum[0]=1,sum[1]=3,sum[2]=4;
    a=read();
    for(int i=1;i<=a;++i)num[i]=read(),fa[i]=i;
    for(int i=1;i<=a;++i)num[i+a]=read();
    for(int i=3;i<=a;++i)(sum[i]=sum[i-1]+sum[i-2])%=modd;
    for(int i=1;i<=a;++i)
    {
        edge[num[i]].push_back(num[i+a]);
        edge[num[i+a]].push_back(num[i]);
        in[num[i]]++,in[num[i+a]]++;
    }
    ll ans=1,res;
    for(int i=1;i<=a;++i)if(fa[i]==i)dfs(i);
    topo();
    for(int i=1;i<=a;++i)
    {
        if(in[i]&&!bj[i])
        {
            ll now=row(i);
            ans*=sum[now-1];
            ans%=modd;
        }
    }
    cout<<ans;
}


```

---

## 作者：WaterSun (赞：0)

# 思路

对于包含数 $x$ 的卡牌，两张之中必定要选择一张，由此想到 2-SAT 的思想。

我们将所有带有 $x$ 的卡牌两两连边，每一条边连接的点都表示两点必须选择一个。

不难发现，我们这样会得出若干个环。（因为对于每一张卡牌的出边为 $2$，一定会形成环）

在每一个环中的选择情况，不会影响答案，所以考虑分析每一个环所能做的贡献，然后用分布乘法原理得出答案。

定义 $dp_i$ 表示一个大小为 $i$ 的环的贡献。

不难得出 $dp_1 = 1,dp_2 = 3$。对于 $i \geq 3$ 的时候，需要分类讨论一下：

1. 如果 $1$ 不选，贡献等同于一个大小为 $i - 2$ 的环，贡献为 $dp_{i - 2}$。

2. 如果 $1$ 选，贡献等同于一个大小为 $i - 1$ 的环，贡献为 $dp_{i - 1}$。

所以，对于一个大小为 $i$ 的环，贡献为 $dp_{i - 1} + dp_{i - 2}$。（正好是一个斐波那契数列）

因此，答案是（其中 $sz_i$ 表示第 $i$ 个环的大小）：

$$
\prod_{i = 1}dp_{sz_i}
$$

求环的大小直接用并查集即可。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10,mod = 998244353;
int n,ans = 1;
int f[N],dp[N],sz[N],id[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 1) + (r << 3) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int find(int x){
	if (f[x] != x) return f[x] = find(f[x]);
	return f[x];
}

inline void merge(int a,int b){
	int x = find(a);
	int y = find(b);
	if (x != y){
		f[x] = y;
	 	sz[y] += sz[x];
	}
}

signed main(){
	n = read();
	dp[1] = 1;
	dp[2] = 3;
	for (re int i = 1;i <= n;i++){
		f[i] = i;
		sz[i] = 1;
		if (i >= 3) dp[i] = (dp[i - 1] + dp[i - 2]) % mod;
	}
	for (re int i = 1;i <= n;i++){
		int x;
		x = read();
		id[x] = i;
	}
	for (re int i = 1;i <= n;i++){
		int x;
		x = read();
		merge(i,id[x]);
	}
	for (re int i = 1;i <= n;i++){
		if (f[i] == i) ans = ans * dp[sz[i]] % mod;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：0)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16146088.html)

题意：

给你 $n$ 张卡片，每一张的正面写着 $p_i$，背面写着 $q_i$。现在要选一些卡片出来，使得 $1\sim n$ 中所有数都在选择的卡片中至少出现一次。问有多少种选法。 

$p$ 和 $q$ 都是 $1\sim n$ 的排列。

-----
明显的，可以将这个题转化为一个图论题。设数字 $m$ 在 $p,q$ 中出现的下标分别为 $i,j$，则在 $i,j$ 间连一条边。给这些点染色，使得每条边连接的两个节点中至少有一个点被染色了。

那显然每个节点的度数都是 $2$。同样显然的构造出的图一定由若干个环组成。所以可以将每个环分开计算。

对于一个环，有两种计算方法。
1. DP。因为我不会写，这里从略。
2. 找规律。明显当环上点的个数为 $1,2,3,4,5,\ldots$ 时解的个数分别为 $1,3,4,7,11,\ldots$ 。
于是我们就想到了[这个](https://oeis.org/A000032)。算一下即可。最后把每个环乘起来。

[代码](https://paste.ubuntu.com/p/2XHPNc5vs4/)
 

---

## 作者：Tsawke (赞：0)

# [ABC247F Cards](https://www.luogu.com.cn/problem/AT_abc247_f) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=ABC247F)

## 题面

给定 $ n $ 张卡片，每张卡片正反面各有一个数，给定每张卡片正面和反面的数，保证正面的数构成的序列，和反面的数构成的，分别均为 $ 1 $ 到 $ n $ 的排列，可以选择任意张卡片并获得其正反面的数，要求最终所有获得的数至少包含 $ 1 $ 到 $ n $ 每个数至少一次。求有多少种取法，对 $ 998244353 $ 取模。

## Solution

考虑卡片之间的联系，显然若一个数在同一张卡牌的正反面那么这张卡牌必须选择，否则无法凑齐一个排列，反之这个数一定会在两张卡牌中出现，且这两张卡牌一定至少有一张被选择，否则依然无法凑齐一个排列，这个很好理解。

于是我们考虑一些对于这种题的一般的套路，可以尝试建图，对于本题不难想到，我们将一张卡牌作为一个点，将这个点向卡牌上存在的数的另一次出现所在的卡牌连一条边。抽象地说，对于一个数所在的两张（或一张）卡牌位置 $ pos_{i, 0} $ 和 $ pos_{i, 1} $，其中一定有一个刚好为 $ i $，我们就是要从 $ i $ 向不等于 $ i $ 的那个 $ pos_i $ 连一条边，这里便不难想到从 $ i $ 向 $ pos_{i, 0} \oplus pos_{i, 1} \oplus i $ 连边即可。

不难想到这样会形成多个环，每一个环代表着其中几张卡牌，同时这些卡牌上的数在环内一定每个数都出现了两遍，如排列 $ \{ 1, 2, 3 \} $ 和排列 $ \{ 2, 1, 3 \} $，显然 $ i = 1 $ 时向数字 $ 1 $ 所在的另一张卡牌 $ 2 $ 和数字 $ 2 $ 所在的另一张卡牌 $ 2 $ 连边（不拿发现很有可能存在重边与自环，所以需要注意判重并忽略），对于 $ i = 2 $ 同理，最终一定会形成 $ 1 \rightarrow 2 \rightarrow 1 $ 和 $ 3 \rightarrow 3 $ 两个环，第一个环可以求出带有 $ 1, 2 $ 数字的卡牌的让 $ 1, 2 $ 都至少存在一次的卡牌选择方案数，第二个环则为 $ 3 $ 的方案数，将两者乘起来即为最终答案。并且环上每个边相连的两个点，或者说两张卡牌，至少要被选择一张，因为一条边连结的两个卡牌一定存在着相同的数，为了保证构成排列至少需要选择一个。

同时发现不同环的方案数，只跟环的长度有关，于是我们考虑令 $ dp(i) $ 表示 $ i $ 个数构成的环，则有边界 $ dp(1) = 1 $ 和 $ dp(2) = 3 $，和转移 $ dp(i) = dp(i - 1) + dp(i - 2) $，大概就是我们考虑向原环中插入第 $ i $ 个数，如果选择第 $ i $ 个数，那么任意的前 $ i - 1 $ 个数的合法方案都可以接上新的这个数，反之如果不选第 $ i $ 个，那么第 $ i $ 个的两侧都应该是选择的，这个时候我们直观地可以想到，固定其左右的两个然后由 $ dp(i - 3) $ 转移而来，但是这个是有遗漏的。观察发现对于 $ i $ 不选择的，是存在类似 $ \cdots \rightarrow 0 \rightarrow 1 \rightarrow i(0) \rightarrow 1 \rightarrow 0 \rightarrow \cdots $，也就是在固定三个之后左右各自接一个不选的，这个东西显然是不在 $ dp(i - 3) $ 里的，因为两个都不选接在一起形成环是不合法的，考虑如何正确地转移：我们可以考虑在 $ dp(i - 2) $ 的方案中找到任意一个选择的点，然后在其旁边接上 $ i $ 和另一个固定的选择的点，这样也是合法的且不重不漏，最终就是 $ dp(i) = dp(i - 1) + dp(i - 2) $。

于是考虑并查集维护好每个环的大小，$ \prod dp(siz_i) $ 即为最终的答案。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

#define MOD 998244353

template< typename T = int >
inline T read(void);

int N;
int P[210000], Q[210000];
int cnt[210000];
int pos[210000][2];
int f[210000];
bool vis[210000];
int ans(1);

class UnionFind{
private:
public:
    int fa[210000];
    int siz[210000];
    UnionFind(void){for(int i = 1; i <= 201000; ++i)fa[i] = i, siz[i] = 1;}
    int Find(int x){return x == fa[x] ? x : fa[x] = Find(fa[x]);}
    void Union(int origin, int son){
        if(Find(origin) == Find(son))return;
        siz[Find(origin)] += siz[Find(son)], fa[Find(son)] = Find(origin);
    }
}uf;

int main(){
    N = read();
    f[1] = 1, f[2] = 3;
    for(int i = 3; i <= N; ++i)f[i] = (ll)(f[i - 1] + f[i - 2]) % MOD;
    for(int i = 1; i <= N; ++i)P[i] = read(), pos[P[i]][cnt[P[i]]++] = i;
    for(int i = 1; i <= N; ++i)Q[i] = read(), pos[Q[i]][cnt[Q[i]]++] = i;
    for(int i = 1; i <= N; ++i)
        uf.Union(i, pos[P[i]][0] ^ pos[P[i]][1] ^ i),
        uf.Union(i, pos[Q[i]][0] ^ pos[Q[i]][1] ^ i);
    for(int i = 1; i <= N; ++i)if(uf.Find(i) == i)ans = (ll)ans * f[uf.siz[uf.Find(i)]] % MOD;
    printf("%d\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_10_25 初稿

---

