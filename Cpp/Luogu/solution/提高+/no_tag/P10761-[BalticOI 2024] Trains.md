# [BalticOI 2024] Trains

## 题目背景

翻译自 [BalticOI 2024 Day1 T3](https://boi2024.lmio.lt/tasks/d1-trains-statement.pdf)。

## 题目描述

你已经抵达维尔纽斯，并希望参观立陶宛的不同城市。立陶宛的城市位于一条直线上，并按顺序从 $1$ 到 $N$ 编号。维尔纽斯是 $1$ 号城市。每个城市都有一个火车站，并且有一条从该站出发的单轨列车运营路线。你只能在该路线起点的城市上车，但可以在其任何一站下车。从第 $i$ 个城市开始的列车每行驶 $d_i$ 个城市就会停靠一站，并且其路线包含 $x_i$ 个停靠站（不包括起始城市）。如果 $d_i = 0$，则从第 $i$ 个城市出发的列车目前处于停运状态，因此你不能乘坐它们。

更具体地说，如果你在第 $i$ 个城市上车，你可以在任何编号为 $i + t \cdot d_i$ 的城市下车，其中 $1 \leq t \leq x_i$。请注意，由于你只希望参观立陶宛的城市，因此即使列车在其路线上有更多的停靠站，你也不会超过第 $N$ 个城市下车。

你打算使用列车前往参观一些城市。在规划你的旅行时，你开始思考从维尔纽斯出发的旅程有多少种不同的选择。如果两次旅行在不同的城市序列中停靠，则它们被视为不同。输出答案对 $10^9 + 7$ 取模的值。

## 说明/提示

对于样例，存在如下七种路线：

- $1$
- $1 \rightarrow  2$
- $1 \rightarrow  2 \rightarrow  4$
- $1 \rightarrow  3$
- $1 \rightarrow 3 \rightarrow 4$
- $1 \rightarrow 3 \rightarrow 5$
- $1 \rightarrow 4$

| 子任务编号 | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $n \leq 15$ | $8$ |
| $2$ | $n \leq 10^4$ | $13$ |
| $3$ | $d_i = 1$ | $16$ |
| $4$ | $x_i = 10^9$ | $34$ |
| $5$ | 无特殊性质 | $29$ |

对于所有数据，保证 $1 \leq N \leq 10^5$，$0 \leq d_i,x_i \leq 10^9$。

## 样例 #1

### 输入

```
5
1 3
2 1
1 3
0 10
3 5```

### 输出

```
7```

# 题解

## 作者：xiaoliebao1115 (赞：10)

大佬写的题解都太抽象了，这一篇题解献给每一个蒟蒻们。
## 朴素动态规划
从左到右进行动态规划即可，就是 $dp_i=\sum dp_j$，这里的 $j$ 都有一条从 $j$ 出发的火车路径经停 $i$，特别的 $dp_1=1$。

文中的 $dp_i$ 就表示的是从维尔纽斯开始到 $i$ 结束的方案数总和，这个应该都能理解。最后 $ans=\sum dp_i$。
## 根号分治
### 情况 $1$
先令 $b=\sqrt{n}$，很容易发现对于 $d>b$ 的情况来讲最多只有 $b$ 个位置可以从当前位置转移，总复杂度 $O(n\sqrt{n})$。
### 情况 $2$
考虑 $d\le b$ 的情况，注意到这里的 $d$ 的种类数最多不会超过 $\sqrt{n}$ 个。所以我们开一个数组 $f_{i,j}$ 表示最后经过一个 $d=j$ 的路线到达 $i$ 的总方案数，注意，这个数组只记录 $j\le b$ 的情况。

我们可以得到一些转移方程：$f_{i+j,j}=f_{i+j,j}+f_{i,j}$，这个表示把这条 $d=j$ 的铁路线继续往下一个站点开。

$dp_i=dp_i+f_{i,j}$，这里的 $dp_i$ 已经保存了 $d\le b$ 的所有答案，加上剩余部分即可。

$f_{i+d,d}=f_{i+d,d}+dp_i$，这个表示一条从 $i$ 开始的铁路线，$i+d$ 就是第一个停下来的地方，通过向这个地方转移，可以让 $i+d$ 根据前面的式子向后面停下来的位置转移。

但是考虑到从一个地方开始的火车经停站数量有限，所以有 $f_{i+d\times(x+1),d}=f_{i+d\times(x+1),d}-dp_i$，因为从 $x+1$ 往后就不能再停车了，正确性是显然的，相当于把 $f_{i+d,d}=f_{i+d,d}+dp_i$ 这个式子中增加的 $dp_i$ 给减掉，有点类似于差分的思路。

这边的每次转移都是 $O(1)$，并且 $f_{i,j}$ 大小是 $n\sqrt{n}$ 的，所以整个程序总时间复杂度 $O(n\sqrt{n})$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int nn=1e5+5,B=317,mod=1e9+7;
int n,f[nn][B],dp[nn],ans;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	int b=sqrt(n);
	dp[1]=1;
	for(int i=1;i<=n;i++){
		int d,x;
		cin>>d>>x;
		for(int j=1;j<=b;j++){
			if(i+j<=n) f[i+j][j]=(f[i+j][j]+f[i][j])%mod;
			dp[i]=(dp[i]+f[i][j])%mod;
		}
		ans=(ans+dp[i])%mod;
		if(d==0) continue;
		if(d>b){
			for(int j=i+d,k=1;j<=n&&k<=x;j+=d,k++)
			dp[j]=(dp[i]+dp[j])%mod;
		}
		else{
			if(i+d<=n) f[i+d][d]=(f[i+d][d]+dp[i])%mod;
			if(i+d*(x+1)<=n) f[i+d*(x+1)][d]=(f[i+d*(x+1)][d]-dp[i]+mod)%mod;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```
这里需要注意的是在 $d=0$ 或者是超出范围的时候要特判一下，记得赋初值。

---

## 作者：woshishabi11451444 (赞：3)

首先考虑设计状态：$dp_i$ 表示从 $1$ 走到 $i$ 的方案数，但是转移还是超时的。

考虑对 $d_i$ 的值域进行考虑：

当 $d_i > \sqrt N$ 时，点 $i$ 只会转移至多出 $\sqrt N$ 个点。

否则，因为 $d_i$ 的值域较小，那么点 $i$ 的转移本质是在对一个区间内对 $d_i$ 取模的值等同于 $d_i$ 取模 $i$ 的值的点，那么点 $i$ 会转移到这些点，那么用数组记录一下当取模 $d_i = j$ 时能转移到该点的贡献，但是暴力维护时间复杂度会超时，但观察到总共变化的位置数量是 $2 \times N$ 个，每次只需维护变化的点就行了。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int K = 320;
const int inf = 316;
const int N = 1e5 + 2;
const int mod = 1e9 + 7;

struct Node{
  int d, r, num;
};

int n, d[N], x[N], dp[N], s[K][K];
vector<Node> g[N];

int read(){
  int f = 1, x = 0;
  char ch = getchar_unlocked();
  for(; ch < '0' || ch > '9'; ch = getchar_unlocked()){
    if(ch == '-') f = -1;
  }
  for(; ch >= '0' && ch <= '9'; ch = getchar_unlocked()){
    x = (x << 3) + (x << 1) + ch - '0';
  }
  return x * f;
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  n = read();
  dp[1] = 1;
  for(int i = 1; i <= n; i++){
    d[i] = read(), x[i] = read();
    for(Node v : g[i]){
      s[v.d][v.r] += v.num;
      while(s[v.d][v.r] >= mod) s[v.d][v.r] -= mod;
    }
    for(int j = 1; j <= inf; j++){
      dp[i] += s[j][i % j];
      while(dp[i] >= mod) dp[i] -= mod;
    }
    if(!d[i]) continue;
    if(d[i] > n) continue;
    if(d[i] >= inf){
      for(int j = 1; j <= x[i]; j++){
        long long now = i + 1ll * j * d[i];
        if(now > n) break;
        dp[now] += dp[i];
        while(dp[now] >= mod) dp[now] -= mod;
      }
    }
    else{
      g[i + 1].push_back({d[i], i % d[i], dp[i]});
      g[min(i + 1ll * x[i] * d[i] + 1, 1ll * n + 1)].push_back({d[i], i % d[i], mod - dp[i]});
    }
  }
  int ans = 0;
  for(int i = 1; i <= n; i++){
    ans += dp[i];
    while(ans >= mod) ans -= mod;
  }
  cout << ans;
  return 0;
}
```

---

## 作者：TMLY114514 (赞：2)

# 题解：P10761 [BalticOI 2024] Trains
看到题后能设出状态 $f_i$ 表示到达第 $i$ 个城市的方案数。

由题目条件可知，对于能被当前点 $i$ 做贡献的点 $j$，在满足 $k\le x_i$ 的前提下，一定有 $j=i+k\times d_i$，
容易得出一个朴素的转移：
$$f_{i+k\times d_i}=f_{i+k\times d_i}+f_i$$
发现这个转移方程在 $d_i>\sqrt{n}$ 时复杂度是对的，需要考虑 $d_i\le \sqrt{n}$ 时的做法。

再次观察 $j=i+k\times d_i$ 这个式子，发现其等价于 $j\equiv i\space(\bmod\space d_i)$。

设 $cnt_{j,k}$ 表示满足 $d_i=j$ 且 $i\equiv k\space(\bmod\space d_i)$ 的 $f_i$ 的和。在求 $f_p$ 时枚举 $j$，$f_p=f_p+cnt_{j,p\bmod j}$。

虽然数组是二维的，但只有 $n$ 个点。可以用 unordered_map 维护这个数组，在第 $i+x_i\times d_i+1$ 个城市减去 $i$ 的贡献即可。对于每个城市以 $\sqrt{n}$ 做为界限使用两种做法，总复杂度 $O(n\sqrt{n})$。

由于 unordered_map 常数比较大，实际上取 $n^{0.4}$ 作为界限才能通过，也有可能是我的代码太垃圾了。

## 代码

```cpp
const int mod=1e9+7;
#define N 100010
int n,d[N],x[N],f[N],bl,ans;
unordered_map<int,int>cnt[N];
#define pait pair<int,int>
vector<pait>tag[N];
inline void add(int &x,const int y){
	x+=y;
	if(x>=mod)x-=mod;
}
int main(){
	read(n);
	bl=pow(n,0.4);
	for(int i=1;i<=n;++i)read(d[i],x[i]);
	f[1]=1;
	for(int i=1;i<=n;++i){
		for(auto[x,y]:tag[i])cnt[x][y%x]=(cnt[x][y%x]-f[y]+mod)%mod;
		for(int j=1;j<=bl;++j)
			if(cnt[j].count(i%j))
				add(f[i],cnt[j][i%j]);
		add(ans,f[i]);
		if(!d[i])continue;
		if(d[i]>bl){
			for(int k=1;k<=x[i]&&i+k*d[i]<=n;++k)
				add(f[i+k*d[i]],f[i]);
		}else{
			ll r=1ll*x[i]*d[i]+i+1;
			add(cnt[d[i]][i%d[i]],f[i]);
			if(r>n)continue;
			tag[r].push_back({d[i],i});
		}
	}
	write(ans);
```

---

## 作者：Exp10re (赞：2)

典 Trick。

类似的 Trick 可以参考 [P5309 [Ynoi2011] 初始化](https://www.luogu.com.cn/problem/P5309)。

## 解题思路

考虑朴素动态规划。

记 $f_i$ 表示到达 $i$ 的不同路线个数，则有如下转移：

$$f_{i+t\cdot d_i}\leftarrow f_{i+t\cdot d_i}+f_i,t\leq x_i,i+t\cdot d_i\leq n$$

时间复杂度 $O(n^2)$，考虑优化。

不难发现，当 $d_i\gt \sqrt n$ 时有效转移的次数是 $O(\sqrt n)$ 规模的，而当 $d_i\leq \sqrt n$ 时不同的 $d_i$ 只有 $\sqrt n$ 个，这启发我们使用根号分治。

记 $g_{i,j}$ 表示所有 $d=j$ 的操作对 $f_i$ 产生的影响。

考虑对于 $d_i\gt \sqrt n$ 的操作都暴力修改 $f_i$，对于 $d_i\leq \sqrt n$ 的操作通过维护 $g$ 来间接影响 $f_i$，则到达 $i$ 的不同路线个数的实际值为 $f_i+\sum_{j=1}^{\sqrt n} g_{i,j}$。

接下来考虑如何维护 $g$。不难发现，我们维护 $f_i$ 时的顺序是 $i$ 从小到大维护，使用前缀和差分维护 $g_i$ 即可。

具体可以参考代码。我一般不挂代码，但是这一题的代码实在太短了。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXP=400,MAXB=400,MAXN=101000,Moder_=1e9+7;
long long n,rec[MAXN][MAXP],ans[MAXN],Delta,Ans;
int main()
{
	long long i,j,ta,tb;
	scanf("%lld",&n);
	Delta=sqrt(n)+1;
	ans[1]=1;
	for(i=1;i<=n;i++)
	{
		scanf("%lld%lld",&ta,&tb);
		for(j=1;j<=Delta;j++)
		{
			if(i-j>=0)
			{
				rec[i][j]=(rec[i][j]+rec[i-j][j])%Moder_;
			}
			ans[i]=(ans[i]+rec[i][j])%Moder_;
		}
		Ans=(Ans+ans[i])%Moder_;
		if(ta==0)
		{
			continue;
		}
		if(ta<=Delta)
		{
			if(i+ta<=n)
			{
				rec[i+ta][ta]=(rec[i+ta][ta]+ans[i])%Moder_;
			}
			if(i+(tb+1)*ta<=n)
			{
				rec[i+(tb+1)*ta][ta]=(rec[i+(tb+1)*ta][ta]-ans[i]+Moder_)%Moder_;
			}
		}
		else
		{
			for(j=1;i+j*ta<=n&&j<=tb;j++)
			{
				ans[i+j*ta]=(ans[i+j*ta]+ans[i])%Moder_;
			}
		}
	}
	printf("%lld",Ans);
	return 0;
}
```

---

## 作者：北文 (赞：2)

这是一道建图题，很显然，如果能把这个图建出来，那么只需要一个简单的拓扑排序即可解决。  
问题是，边数好像有点多。   
考虑根号分治和前缀优化建图。  
首先取 $B=\sqrt n$，  
套路地分类讨论：  
$d>B$ 直接暴力建，边不会超过 $B$。  
$d \le B$ 考虑前缀优化建图，给小于 $B$ 的每个数每个起始位置，搞一条链，类似如此：  


![](https://cdn.luogu.com.cn/upload/image_hosting/ru4o86fp.png)  
然后想区间连边直接连向对应的虚点即可。还有一个问题需要解决，他是向区间连边，后面的边怎么删掉？  
考虑到该拓扑排序只是加减法，直接给后面的贡献扣掉即可。  
在实现的时候不要真的把图建出来，在建图的过程中直接 dp 转移即可。  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+6, B=355, P=1e9+7;
bool Be;
int n, d, x, cnt, de[N*B], f[N*B];
bool Ed;
int id(int b, int x) {
	return b*n+x;
}
void ma(int &x, int y) {
	x+=y;
	x>=P?x-=P:0;
}
int main() {
	scanf("%d", &n); int b=316;
	f[1]=1; long long ans=0;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=b; j++) {
			ma(f[i], f[id(j, i)]);
			if(i+j<=n)
				ma(f[id(j, i+j)], f[id(j, i)]);
		}
		scanf("%d %d", &d, &x);
		ans=(ans+P+f[i])%P;
		if(d==0) continue ;
		if(d>b) {
			for(int j=i+d, k=1; j<=n&&k<=x; j+=d, k++) {ma(f[j], f[i]);}
		}
		else {
			if(i+d<=n) {
				ma(f[id(d, i+d)], f[i]);
			}
			if(i+1ll*d*(x+1)<=n) {
				//这里是把贡献扣掉 
				ma(f[id(d, i+d*(x+1))], P-f[i]);
			}
		}
	}
	printf("%lld\n", (ans%P+P)%P);
	return 0;
} 
```

---

## 作者：Hell0_W0rld (赞：1)

首先我们有一个简单 dp：$f_i$ 表示从 $i$ 号站开始的乘车方案的个数。

简单写出如下转移方程：$f_i=\sum\limits_{k=1}^{x_i} f_{i+k\times d_i}$，其中默认 $\forall i>n,f_i=0$。

注意到这个乘积的形式类似于 [Homework](https://www.luogu.com.cn/problem/P9809)，考虑根号分治。

当 $d_i<B$ 时，用已经累加好的后缀和进行处理。复杂度 $O(1)$。

当 $d_i\geq B$ 时，暴力直接枚举倍数，复杂度 $O(\min{\lfloor \frac{n-i}{d_i}\rfloor,x_i})$。

总复杂度 $O(nB+n\times \frac{n}{B})$，当 $B=\sqrt{n}$ 时复杂度 $O(n\sqrt{n})$。

```cpp
#include<bits/stdc++.h>
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define ll long long
#define ull unsigned long long
#define rep(i,l,r) for(ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(ll i=(r);i>=(l);--i)
#define all(x) x.begin(),x.end()
#define Set(x,y) memset(x,y,sizeof(x))
#define Cpy(x,y) memcpy(x,y,sizeof(x))
#define cll const long long
using namespace std;
template<class T>
void death(T s){cout<<s<<endl;exit(0);}
template<cll MOD> class modint{
	private:
	public:
		ll x;
		modint()=default;
		modint(ll _x){x=(_x%MOD+MOD)%MOD;}
		friend istream& operator>>(istream& in, modint& a){in>>a.x; a.x%=MOD; return in;}
		friend ostream& operator<<(ostream& out, modint a){return out<<a.x;}
		friend modint operator+(modint a,modint b){return a.x+b.x>=MOD?a.x+b.x-MOD:a.x+b.x;}
		friend modint operator-(modint a,modint b){return a.x-b.x>=0?a.x-b.x:a.x-b.x+MOD;}
		friend modint operator*(modint a,modint b){ll x=a.x,y=b.x;return x*y%MOD;}
		friend modint operator/(modint a,modint b){return a*(~b);}
		friend modint operator^(modint a,ll p){modint ans=1;for(;p;p>>=1){if(p&1)ans*=a;a=a*a;}return ans;}
		friend modint operator~(modint a){return a^(MOD-2);}
		friend modint operator-(modint a){return a.x==0?0:MOD-a.x;}
		friend modint& operator+=(modint&a,modint b){return a=a+b;}
		friend modint& operator-=(modint&a,modint b){return a=a-b;}
		friend modint& operator*=(modint&a,modint b){return a=a*b;}
		friend modint& operator/=(modint&a,modint b){return a=a/b;}
		friend modint& operator++(modint&a) {return a+=1;}
		friend modint operator++(modint&a,int){modint x=a;a+=1;return x;}
		friend modint& operator--(modint&a) {return a-=1;}
		friend modint operator--(modint&a,int){modint x=a;a-=1;return x;}
		friend bool operator==(modint a, modint b){return a.x==b.x;}
		friend bool operator!=(modint a, modint b){return a.x!=b.x;}
};
using mint=modint<1000000007>;
cll N=100009;
mint sum[N][400],f[N];
ll n,d[N],x[N];
int main(){
	cin>>n;
	rep(i,1,n)cin>>d[i]>>x[i];
	ll L=sqrt(n);
	Rep(i,1,n){
		if(d[i]<=L){
			ll L=i+d[i],R=i+d[i]*(x[i]+1);
			if(L<=n&&R>n)f[i]=1+sum[L][d[i]];
			else if(L<=n)f[i]=1+sum[L][d[i]]-sum[R][d[i]];
			else f[i]=1;
		}
		else{
			f[i]=1;
			for(ll j=1;j<=x[i]&&i+d[i]*j<=n;j++)f[i]+=f[i+d[i]*j]; 
		}
		rep(x,1,L){
			sum[i][x]=f[i];
			if(x+i>n)continue;
			sum[i][x]+=sum[i+x][x];
		}
	}
	cout<<f[1]<<endl;
	return 0;
}
```

---

## 作者：船酱魔王 (赞：1)

## 题意回顾

总共 $ n $ 个位置，第 $ i $ 个位置可以直接到达第 $ i+td_i $ 个位置，注意需要满足 $ 1 \le t \le x_i $ 且 $ i+td_i \le n $。

你从 $ 1 $ 出发到任何位置结束，有多少种本质不同的旅行方案？

数据规模：$ n \le 10^5 $。

## 分析

显然有 $ dp_i=\sum dp_{i+td_i}+1 $，条件为 $ i+td_i \le n $ 且 $ 1 \le t \le x_i $。

单次暴力转移复杂度是 $ O(\frac{n}{d_i}) $ 的，考虑 $ d_i \le 100 $ 时如何做。

我们发现我们要求的内容可以看作所有模 $ d_i $ 与 $ i $ 同余的位置上的数构成的子序列的一个区间和，可以用前缀和优化，复杂度为 $ O(d_in) $。

设阈值为 $ S $，则复杂度为 $ O(\frac{n}{S} \times n+nS) $，$ S $ 趋近于 $ \sqrt{n} $ 时复杂度可近似为 $ O(n^{1.5}) $，本代码实现取 $ S=100 $。

注意 $ x_i $ 或 $ d_i $ 为 $ 0 $ 的特判，注意 $ i+x_id_i $ 可能超出数组范围需要避免 RE。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int N = 1e5 + 5;
const int S = 100;
const int mod = 1e9 + 7;
int sum[S + 5][N];
int dp[N];
int n;
int d[N], x[N];
signed main() {
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++) scanf("%lld%lld", &d[i], &x[i]);
    for(int i = n; i >= 1; i--) {
        dp[i] = 1;
        if(!d[i] || !x[i]) {}
        else if(d[i] > S) {
            for(int j = i + d[i]; j <= n && j <= i + x[i] * d[i]; j += d[i]) dp[i] = (dp[i] + dp[j]) % mod;
        } else {
            int mit = min((n - i) / d[i] + 1, x[i] + 1);
            int rd = i + mit * d[i];
            int ld = i + d[i];
            if(ld > n) {}
            else if(rd > n) dp[i] = (dp[i] + sum[d[i]][ld]) % mod;
            else dp[i] = ((dp[i] + sum[d[i]][ld] - sum[d[i]][rd]) % mod + mod) % mod;
        }
        for(int j = 1; j <= S; j++) {
            sum[j][i] = dp[i];
            if(i + j <= n) sum[j][i] = (sum[j][i] + sum[j][i + j]) % mod;
        }
    }
    printf("%lld\n", dp[1]);
    return 0;
}
```

---

## 作者：Helloworldwuyuze (赞：0)

# P10761 [BalticOI 2024] Trains

## Des

有 $n$ 辆火车，第 $i$ 辆从 $i$ 开出，每 $d_i$ 站停一次，共停 $x_i$ 站。也就是停在 $x+kd_i,k\in [1, x_i]$。问：
$$
\sum_{i=1}^n f(1, i)
$$
其中 $f(u,v)$ 表示从 $u$ 到 $v$ 有多少种走法。

## Sol

我们设 $f_i$ 表示从 $1$ 到 $i$ 的路径数量，那么显然有：
$$
f_{i}\rightarrow f_{i+kd_i},k\in[1,x_i]
$$
这个题隔一段加一个的操作显然并不好直接用数据结构维护，但显然的，我们都会 $d_i\ge \sqrt n$ 的做法。直接暴力向后跳加上就行了。但是 $d\le \sqrt n$ 怎么办。

考虑到一个一个实现是不可能的，这是因为操作次数到达了 $O(n^2)$ 量级，于是我们就一定需要打一个标记。思考隔一段加一的操作本质是什么，实际上他可以写成形式化的：对于满足 $\begin{cases}x = i+kd_i\\ x\in(i, i+x_id_i]\end{cases}$ 都进行加操作。再转换一下呢？发现它是：
$$
\begin{cases}x\equiv i\pmod{ d_i} \\ x\in(i, i+x_id_i]\end{cases}
$$
这是不是就清晰很多了，我们直接设 $g_{i,j}$ 表示模 $i$ 余 $j$ 的点所需要加的权值，然后在修改的时候我们在 $g_{d_i,x_i\bmod d_i}$ 的地方加上 $f_i$，然后在每次循环到 $i$ 的时候直接让：
$$
f_i\leftarrow f_i + \sum_{j=1}^{\sqrt n} g_{j,i\bmod j}
$$
即可。

这样的时间复杂度正好 $O(n\sqrt n)$。

至于怎么消除右端点后面的影响，直接每个位置开一个 `vector` 记录要删除那些贡献即可。

```
#define endl '\n'

using namespace std;

#define int long long
const int INF = 0x3f3f3f3f;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;
const int N = 1e5 + 10;
const int B = 300;
const int MOD = 1e9 + 7;
inline int max(int x,int y){ return x<y ? y:x; }
inline int min(int x,int y){ return x<y ? x:y; }

int n, d[N], x[N], f[N];
int sum[B+10][B+10];
vector<int> del[N];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)	cin>>d[i]>>x[i];
	f[1] = 1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=B;++j)	f[i] = (f[i] + sum[j][i%j]) %MOD;
		for(int x : del[i])	sum[d[x]][x%d[x]] = (sum[d[x]][x%d[x]] - f[x] +MOD) %MOD;
		if(d[i] == 0)	continue;
		if(d[i] >= B || x[i] <= B){
			for(int j=1;j<=x[i]&&i+d[i]*j<=n;++j)
				f[i+d[i]*j] = (f[i+d[i]*j] + f[i]) %MOD;
		}else{
			sum[d[i]][i%d[i]] = (sum[d[i]][i%d[i]] + f[i]) %MOD;
			if(i + d[i]*x[i] <= n)	del[i+d[i]*x[i]].pb(i);
		}
	}
	int ans = 0;
	for(int i=1;i<=n;++i)	ans = (ans + f[i]) %MOD;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：harmis_yz (赞：0)

题解摘自[做题记录](https://www.luogu.com.cn/article/u60fmw50)。

## 分析

考虑 DP。定义状态函数 $f_{i}$ 表示到 $i$ 的方案数。则有：$f_i=\sum\limits_{j=1}^{i-1} f_j[(i-j)\bmod b_j=0]$。

对于这种无脑跳 $d_i$ 步的题面，不难想到根号分治。使用刷表的方式更新状态函数。对于 $d_i\ge B$ 的点，因为能过转移的点最多有 $\frac{n}{B}$ 个点，所以暴力转移就行了。对于 $d_i<B$ 的点，可以给它打个标记，$tag_{i,j}$ 表示 $b_x=i$ 且 $x\bmod b_x =j$ 的所有 $f_x$ 的和。因为当 $i$ 与 $j$ 的差同余 $b_j$ 时都能转移。所以这样是可行的。由于 $b_i<B$，所以模数也不超过 $B$。每次转移的时候暴力枚举 $b_x$ 就行了。单次转移的复杂度是 $O(B)$ 的。所以总的复杂度 $O(nB+\frac{n^2}{B})$。$B$ 取 $\sqrt{n}$ 最优。

对于 $x$ 的限制，搞一个差分就行了。

## 代码

```cpp
il void solve(){
	n=rd,B=sqrt(n);
	for(re int i=1;i<=n;++i) d[i]=rd,x[i]=rd;
	f[1]=1;
	for(re int i=1;i<=n;++i){
		for(auto x:v[i]) tag[x.x][x.y]=(tag[x.x][x.y]-x.z+p)%p;
		for(re int j=1;j<B;++j) f[i]=(f[i]+tag[j][i%j])%p;
		ans=(ans+f[i])%p;	
		if(!d[i]) continue;
		if(d[i]>=B){
			for(re int j=i+d[i],w=1;j<=n&&w<=x[i];j+=d[i],++w) f[j]=(f[j]+f[i])%p;
			continue;
		}	
		tag[d[i]][i%d[i]]=(tag[d[i]][i%d[i]]+f[i])%p;
		v[min(n+1,i+x[i]*d[i]+1)].push_back({d[i],i%d[i],f[i]});
	}
	printf("%lld\n",ans);
    return ;
}
```

---

## 作者：Nuyoah_awa (赞：0)

### 题目大意

从 $1$ 号节点出发，在 $i$ 号节点可以走到城市 $i + t \times d_i$。问共有多少条路线。

### 题目分析

#### subtask 1-2

根据题意模拟即可，及从一号节点出发遍历，加上记忆化后时间复杂度为 $\mathcal O(n ^ 2)$。

#### subtask 3

考虑到 $d_i = 1$，所以从 $i$ 号节点出发能到 $i+1 \sim i+t$。及记忆化数组上的一段数之和，差分即可。

#### subtask 4

不太理解，感觉除了正解不是很可做。

#### subtask 5-正解

我们根据 subtask3 的思路来考虑，不妨将其拓展为 $d_i$ 很小，则我们只需要做 $d_i$ 个差分即可。

于是很好想到对于 $d$ 较大，subtask1-2 的思路较优，对于 $d$ 较小，subtask3 的思路较优，于是考虑根号分治，及以 $\sqrt{n}$ 为界分别对大小不同的 $d$ 求解。

时间复杂度 $\mathcal O(n \sqrt{n})$。

### code
```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

const int N = 1e5 + 5, S = 400, MOD = 1e9 + 7;
int n, d[N], x[N], s[N], f[N][S];

signed main()
{
    scanf("%lld", &n);
    for(int i = 1;i <= n;i++)
        scanf("%lld %lld", &d[i], &x[i]);
    for(int i = 1;i <= n;i++)
    {
        s[i] = 1, f[i][0] = 0;
        for(int j = 1;j * j <= n;j++)
            f[i][j] = 1;
    }
    for(int i = n;i >= 1;i--)
    {
        if(d[i] * d[i] > n)
        {
            int now = i + d[i];
            for(int j = 1;j <= x[i] && now <= n;now += d[i], j++)
                (s[i] += s[now]) %= MOD;
        }
        else
        {
            if(i + d[i] <= n)
                (s[i] += f[i+d[i]][d[i]]) %= MOD;
            if(x[i] <= n && i + (x[i] + 1) * d[i] <= n)
                s[i] = (s[i] - f[i+(x[i]+1)*d[i]][d[i]] + MOD) % MOD;
        }
        if(d[i] == 0)   s[i] = 1;
        //printf("%lld ", s[i]);
        for(int j = 1;j * j <= n;j++)
        {
            if(i + j <= n)
                f[i][j] = (f[i+j][j] + s[i]) % MOD;
            else
                f[i][j] = s[i];
            //printf("%lld ", f[i][j]);
        }
        //puts("");
    }
    printf("%lld\n", s[1]);
    return 0;
}
```

---

