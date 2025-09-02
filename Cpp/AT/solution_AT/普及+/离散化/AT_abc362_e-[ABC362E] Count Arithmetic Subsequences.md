# [ABC362E] Count Arithmetic Subsequences

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc362/tasks/abc362_e

長さ $ N $ の数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられます。各 $ k=1,2,\dots,N $ について、$ A $ の長さ $ k $ の（連続するとは限らない）部分列であって等差数列であるようなものの個数を $ 998244353 $ で割ったあまりを求めてください。ただし、$ 2 $ つの部分列が列として同じでも、取り出す位置が異なるならば区別するものとします。

部分列とは数列 $ A $ の部分列とは、$ A $ の要素を $ 0 $ 個以上選んで削除し、残った要素を元の順序を保って並べた数列のことを指します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 80 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数

### Sample Explanation 1

\- 長さ $ 1 $ の部分列は全部で $ 5 $ 個あり、これらはすべて長さ $ 1 $ の等差数列です。 - 長さ $ 2 $ の部分列は全部で $ 10 $ 個あり、これらはすべて長さ $ 2 $ の等差数列です。 - 長さ $ 3 $ の部分列であって等差数列であるものは、$ (A_1,A_2,A_3),(A_1,A_2,A_5),(A_1,A_4,A_5) $ の $ 3 $ つです。 - 長さ $ 4 $ 以上の部分列であって等差数列であるものは存在しません。

## 样例 #1

### 输入

```
5
1 2 3 2 3```

### 输出

```
5 10 3 0 0```

## 样例 #2

### 输入

```
4
1 2 3 4```

### 输出

```
4 6 2 1```

## 样例 #3

### 输入

```
1
100```

### 输出

```
1```

# 题解

## 作者：_determination_ (赞：9)

一道比较版的计数 dp。

设 $f_{i,j,k}$ 表示长度为 $i$，最后两项分别是 $a_j$ 和 $a_k$ 的方案数。显然我们可以枚举倒数第三项来进行转移。复杂度 $O(n^4)$。

```cpp
#include<bits/stdc++.h>
#define int long long
//#define endl '\n'
using namespace std;
const int mod=998244353,inf=0x3f3f3f3f3f3f3f3f;
int n;
int a[110];
int f[110][110][110];//f[i][j][k]->长度=i,后两个数是j,k
int ans[110];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
    if(n==1)return cout << 1,0;
    for ( int i = 1 ; i <= n ; i++ )cin >> a[i];
    cout << n << " " << n*(n-1)/2 << " ";
    for ( int i = 1 ; i <= n ; i++ )
    {
        for ( int j = i+1 ; j <= n ; j++ )
        {
            f[2][i][j]=1;
        }
    }
    for ( int i = 3 ; i <= n ; i++ )
    {
        for ( int j = i-1 ; j <= n ; j++ )
        {
            for ( int k = j+1 ; k <= n ; k++ )
            {
                //f[i][j][k]->f[i-1][?][j]
                for ( int l = i-2 ; l < j ; l++ )
                {
                    if(a[j]-a[l]==a[k]-a[j])
                        f[i][j][k]=(f[i][j][k]+f[i-1][l][j])%mod;
                }
                ans[i]+=f[i][j][k];
            }
        }
    }
    for ( int i = 3 ; i <= n ; i++ )cout << ans[i]%mod << " ";
	return 0;
}
```

---

## 作者：MightZero (赞：6)

一道很有意思的 `DP` 题。

首先根据观察发现 $N$ 的范围很小，可以快速列出一个状态：$dp_{i,len,d}$ 表示以 $i$ 结尾，长度为 $len$，公差为 $d$ 的方案数。

然而 $d$ 的值可能会很大，所以考虑预处理所有可能的公差，排序后每次查询时二分查找即可（相当于把公差离散化）。

设 $D(X)$ 表示公差 $X$ 的离散化后位置，对于每个 $i (1\le i\le n)$，枚举 $j (1\le j < i)$，将 $dp_{j,len-1,D(a_i-a_j)}$ 累加到 $dp_{i,len,D(a_i-a_j)}$ 即可。

最终累加答案，$ans_{len}=\sum_{i=1}^n\sum_d{dp_{i,len,d}}$。

时间复杂度 $O(n^3\log n)$。

理论上来说用 `unordered_map` 或其他手段离散化可以达到 $O(n^3)$ 的复杂度。

空间复杂度可以通过滚动去除长度这一维，达到 $O(n^3)$。（然而本人太懒了没写）


Code：
```cpp
#include<bits/stdc++.h>
#define loop(x,l,r) for(ll (x) = (l);(x)<=(r);++(x))
#define rloop(x,l,r) for(ll (x) = (r);(x)>=(l);--(x))
#define elif else if
using namespace std;
using ll = __int128_t;
vector<ll> d;
#define N 85
const ll MOD=998244353;
ll dp[N][N][N*N];
ll a[N],ans[N],n;

inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
    return x*f;
}
inline void write(ll x)
{
    if(x<0){putchar('-');x=-x;}
    if(x%10==x){putchar(x+'0');return;}
    write(x/10);putchar(x%10+'0');
}
signed main()
{
    n=read();
    loop(i,1,n) a[i]=read();
    loop(i,1,n)loop(j,1,i-1)d.push_back(a[i]-a[j]);
    sort(d.begin(),d.end());
    d.erase(unique(d.begin(),d.end()),d.end());
    loop(i,1,n)loop(nd,0,(ll)d.size()-1)dp[i][1][nd]=1;
    loop(i,1,n)loop(len,2,i)loop(j,1,i-1)
    {
        ll dpos=lower_bound(d.begin(),d.end(),a[i]-a[j])-d.begin();
        (dp[i][len][dpos]+=dp[j][len-1][dpos])%=MOD;
    }
    loop(i,1,n)loop(len,1,i)loop(nd,0,(ll)d.size()-1)
        (ans[len]+=dp[i][len][nd])%=MOD;
    ans[1]=n;
    loop(i,1,n){write(ans[i]%MOD);putchar(' ');}
    return 0;
}
```

[AC Record](https://atcoder.jp/contests/abc362/submissions/55555260)

---

## 作者：Po7ed (赞：2)

[\[ABC362E\] Count Arithmetic Subsequences](https://www.luogu.com.cn/problem/AT_abc362_e)

看到其他题解写的都是 dp，所以交一个数学优化爆搜的题解。

### 题意

给出一个长度为 $n$ 的序列 $a$，对于 $1\le l\le n$ 求长度为 $l$ 的等差子序列数量 $ans_l$。

以下用 $d$ 表示公差，$l$ 表示子序列长度。

### 爆搜

注意到 $n\le 80$ 的数据范围，非常诡异，考虑爆搜。我们充分发扬人类智慧，可以发现随机数据下答案是比较小的，也就是说等差子序列并不多。

于是可以写出如下爆搜代码：

```cpp
#include <iostream>
#include <map>
// #include <random>

using std::cin;
typedef long long ll;
constexpr int N=100;
ll a[N];
int n;

ll ans[N]; // ans[i] 表示长度为 i 的等差子序列个数
// i 表示当前搜到 a[i]，l 记录长度，d 代表公差
inline void dfs(int i,int l,ll d)
{
	ans[l]++; // 累加答案
	for(int j=i+1;j<=n;j++)if(a[j]-a[i]==d)
	{ // 搜后继
		dfs(j,l+1,d);
	}
}


std::map<std::pair<int,ll>,bool> vis; // 防止重复搜
int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	// std::mt19937 rnd(114514);
	// for(int i=1;i<=80;i++)printf("%d ",rnd()%114);
	// return 0;
	// 赛时用来造随机数据测试
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
	{ // 枚举头两个数
		for(int j=i+1;j<=n;j++)if(!vis[{i,a[j]-a[i]}])
		{ // 只搜没搜过的
			vis[{i,a[j]-a[i]}]=true;
			dfs(i,1,a[j]-a[i]);
		}
	}
	ans[1]=n; // 保险起见
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
	return 0;
}
```

[结果 T 了两个手造数据](https://atcoder.jp/contests/abc362/submissions/55561925)。

### 优化


考虑如果我们是出题人，该怎么卡。可以发现如果 $\forall 1\le i\le n,\,a_i=1$（即数据全为 $1$），任意子序列都是 $d=0$ 的等差序列，此时长度为 $l$ 的答案为 $\dbinom{n}{l}$，答案之和为 $2^n$，直接爆炸。

考虑让爆搜避开它不擅长的领域，只搜 $d\ne 0$ 的等差子序列。$d=0$ 的情况用数学优化。具体的，设 $cnt_x$ 表示 $a$ 中 $x$ 的出现次数，则 $d=0$ 时

$$
ans_l\gets ans_l+\sum_{\mathclap{x,\exists j,a_j=x}}\,\dbinom{cnt_x}{l}
$$

注意 $d=0$ 的情况对 $ans_l$ 有贡献，但贡献不是直接等于 $ans_l$，因为还有其他情况。

### 代码

```cpp
#include <iostream>
#include <map>
// #include <random>

using std::cin;
typedef long long ll;
constexpr int N=100,mod=998244353;
ll a[N];
int n;

ll ans[N];
void dfs(int i,int l,ll d) // 爆搜
{
	ans[l]++;
	for(int j=i+1;j<=n;j++)if(a[j]-a[i]==d)
	{
		dfs(j,l+1,d);
	}
}

ll qpow(ll x,ll y) // 快速幂，用来求逆元
{
	ll res=1;
	while(y)
	{
		if(y&1)res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
ll fac[N]; // 阶乘
ll C(int n,int m) // 组合数
{
	return fac[n]*qpow(fac[m],mod-2)%mod*qpow(fac[n-m],mod-2)%mod;
}

std::map<ll,bool> vis;
std::map<ll,int> cnt;
int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	// std::mt19937 rnd(114514);
	// for(int i=1;i<=80;i++)printf("%d ",i);
	// return 0;
	cin>>n;
	fac[0]=1;
	for(int i=1;i<=n;i++)cin>>a[i],fac[i]=fac[i-1]*i%mod,cnt[a[i]]++;
	for(int i=1;i<=n;i++)
	{ // 枚举头两个数
		for(int j=i+1;j<=n;j++)if(!vis[a[j]-a[i]]&&(a[i]-a[j])) // 必须满足 d=a[i]-a[j]!=0
		{
			vis[a[j]-a[i]]=true;
			dfs(i,1,a[j]-a[i]);
		}
		vis.clear(); // 判重方法和上面略有不同（其实等价）
	}
	for(auto x:cnt) // 对于每个数，这里 x.first 为值，x.second 为出现次数
	{
		for(int l=1;l<=x.second;l++)
		{
			ans[l]=(ans[l]+C(x.second,l))%mod; // 加上 d=0 的贡献
		}
	}
	ans[1]=n; // 保险起见
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc362/submissions/55570447)。目前排在洛谷最优解第 $4$，前面 $3$ 位好像也是类似方法。

---

## 作者：aCssen (赞：1)

### Solution
对于一个等差数列，我们只要知道它的第一项，第二项，就能推出第 $n$ 项的值：设第一项为 $w_1$，第二项为 $w_2$，那么第 $n$ 项的值就是 $w_1+(n-1) \times (w_2-w_1)$，就是首项加上 $(n-1)$ 倍的公差。

那么这个时候就可以 dp 了，可以把前两项是哪个位置直接塞到 dp 状态里，但这样细节就有点多。注意这里是要存位置，如果是值显然是存不下的。一种更简洁的办法是枚举前两项的位置，进行朴素的二维 dp，把贡献累加到答案里即可。

假设这两个位置为 $p_1,p_2(p_1<p_2)$。设 $f_{i,j}$ 表示前 $i$ 个数，选了 $j$ 个的方案数。那么易得 $f_{i,j}=f_{i-1,j}+f_{i-1,j-1}[a_i=a_{p_1}+(a_{p_2}-a_{p_1}) \times (j-1)]$。

注意一下这里的初值是 $f_{p_2,2}=1$，其它均为 $0$。计算时只计算大于 $p_2$ 处的 dp 值。

然后对于每个 $i$，将 $k=i$ 的答案加上 $f_{n,i}$ 即可。

这里我们是默认的这个等差数列有至少两个元素，对于 $k=1$ 的情况，显然答案为 $n$。

时间复杂度 $\mathcal{O}(n^4)$。

### Code
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
typedef long long ll;
namespace FastIO{
	template<typename T=int> T read(){
		T x=0;int f=1;char c=getchar();
		while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
		while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
		return x*f;
	}
	template<typename T> void write(T x){
		if(x<0){putchar('-');x=-x;}
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	template<typename T> void Write(T x,char c='\n'){write(x);putchar(c);}
}
using namespace FastIO;
const int MOD=998244353;
int f[85][85],a[85],ans[85];
int main(){
	int n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int p1=1;p1<=n;p1++){
		for(int p2=p1+1;p2<=n;p2++){
			memset(f,0,sizeof(f));
			f[p2][2]=1;
			int d=a[p2]-a[p1];
			for(int i=p2+1;i<=n;i++){
				for(int j=0;j<=i;j++){
					f[i][j]=f[i-1][j];
					if(a[i]==1ll*d*(j-1)+a[p1]) f[i][j]=(f[i][j]+f[i-1][j-1])%MOD;
				}
			}
			for(int i=1;i<=n;i++)
				ans[i]=(ans[i]+f[n][i])%MOD;
		}
	}
	Write(n,' ');
	for(int i=2;i<=n;i++)
		Write(ans[i],' ');
	return 0;
}
```

---

## 作者：xiaofu15191 (赞：0)

由于 $n \le 80$，考虑高复杂度乱打 DP。

首先可以设出 DP 状态为 $f_{i,j,k}$ 表示当前等差数列长度为 $i$，末项为 $A_j$，公差为 $k$ 时的方案数。$k$ 需要离散化，我这里使用了 `map`。

然后就可以转移了。枚举数列长度 $i$，末项在原数组中的编号 $j$ 和前一项的编号 $k$。公差可由 $A_j-A_k$ 得出。转移方程显然。记得模 $998244353$。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
map<long long,long long>mp;
long long n,a[100],f[85][85][85*85],ans[100],cnt;
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++) scanf("%lld",&a[i]);
	ans[1]=n;
	for(long long i=1;i<=n;i++)
		for(long long j=i+1;j<=n;j++)
		{
			if(!mp.count(a[j]-a[i])) mp[a[j]-a[i]]=++cnt;
			f[2][j][mp[a[j]-a[i]]]++;
		}
	for(long long j=1;j<=n;j++)
		for(long long k=1;k<=cnt;k++)
			ans[2]+=f[2][j][k];
	for(long long i=3;i<=n;i++)
	{
		for(long long j=i;j<=n;j++)
			for(long long k=i-1;k<j;k++)
			{
				long long tmp=mp[a[j]-a[k]];
				f[i][j][tmp]=(f[i][j][tmp]+f[i-1][k][tmp])%998244353;
			}
		for(long long j=i;j<=n;j++)
			for(long long k=1;k<=cnt;k++)
				ans[i]=(ans[i]+f[i][j][k])%998244353;
	}
	for(long long i=1;i<=n;i++) printf("%lld ",ans[i]);
}
```

---

