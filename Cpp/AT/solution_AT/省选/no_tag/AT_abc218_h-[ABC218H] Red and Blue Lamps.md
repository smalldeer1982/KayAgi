# [ABC218H] Red and Blue Lamps

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc218/tasks/abc218_h

$ 1 $ から $ N $ の番号がついた $ N $ 個のランプが一列に並べられています。あなたはこのうち $ R $ 個を赤く、$ N-R $ 個を青く光らせようとしています。

各 $ i=1,\ldots,N-1 $ について、ランプ $ i $ とランプ $ i+1 $ が異なる色で光っているとき、あなたは $ A_i $ の報酬を得ます。

ランプの色を適切に定めたときに得られる報酬の合計の最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ R\ \leq\ N-1 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

ランプ $ 3,5 $ を赤く、ランプ $ 1,2,4,6 $ を青くすることで、$ A_2+A_3+A_4+A_5=11 $ の報酬を得ます。 これ以上の報酬を得ることはできないため、答えは $ 11 $ です。

### Sample Explanation 2

ランプ $ 1,2,3,4,5,7 $ を赤く、ランプ $ 6 $ を青くすることで、$ A_5+A_6=10 $ の報酬を得ます。

## 样例 #1

### 输入

```
6 2
3 1 4 1 5```

### 输出

```
11```

## 样例 #2

### 输入

```
7 6
2 7 1 8 2 8```

### 输出

```
10```

## 样例 #3

### 输入

```
11 7
12345 678 90123 45678901 234567 89012 3456 78901 23456 7890```

### 输出

```
46207983```

# 题解

## 作者：EastPorridge (赞：5)

离 2023 NOI 春季测试 还有 $4$ 天，随机拷打 ABC 锻炼手感。

感觉一下 $O(nk)$ 的 dp，$f_{0/1,i,j}$ 表示选或不选第 $i$ 个灯，前 $i$ 个灯，有 $j$ 个是红色时的最大价值。

寄了，无法上数据结构优化转移，所以它必须带点性质，

恰好选 $R$ 个，给我一种 wqs 二分的感觉，函数 $g(x)$ 表示选 $x$ 个红色点的最大价值，$g(x)-g(x-1) \le g(x+1)-g(x)$，在 $x \le \lfloor \frac{n}{2} \rfloor$ 时成立，大于的时候反过来，人话说就是这个函数是上凸的。

套路抛弃选 $R$ 个的限制，变成任意选的时候最大价值，二分斜率切这个凸包，转移的时候额外加上权值，最后减去 $R \times \text{mid}$，内层是个很典的 $O(n)$ dp，做完了。

我看官方题解给的是写成区间 dp 的形式，通过凸性做分治，也挺好的。

### Code.

```cpp
#include<bits/stdc++.h>
#define ll long long
int read()
{
	int x=0; bool f=0; char ch=getchar();
	while(ch < '0' || ch > '9') f|=(ch == '-'),ch=getchar();
	while(ch >= '0' && ch <= '9') x=x*10+(ch^48),ch=getchar();
	return f ? -x : x;
}
using namespace std;
const int N=2e5+10;
int a[N],n,k,cnt[2][N]; ll f[2][N];
bool check(ll mid)
{
	f[1][1]=mid; cnt[1][1]=1;
	for(int i=2;i<=n;i++)
	{
		(f[0][i-1] < f[1][i-1] + a[i]) ? (f[0][i]=f[1][i-1]+a[i],cnt[0][i]=cnt[1][i-1]) : (f[0][i]=f[0][i-1],cnt[0][i]=cnt[0][i-1]);
		(f[0][i-1] + a[i] < f[1][i-1]) ? (f[1][i]=mid+f[1][i-1],cnt[1][i]=cnt[1][i-1]+1) : (f[1][i]=mid+f[0][i-1]+a[i],cnt[1][i]=cnt[0][i-1]+1);
	}
	return (f[1][n] > f[0][n]) ? (cnt[1][n] <= k) : (cnt[0][n] <= k);
}
int main()
{
	n=read(); k=read(); for(int i=2;i<=n;i++) a[i]=read();
	ll l=-2e9,r=2e9,res=0;
	while(l <= r)
	{
		ll mid = (l + r) >> 1ll;
		if(check(mid)) l=mid+1,res=max(f[1][n],f[0][n])-k*mid;
		else r=mid-1;
	}
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：Phobia (赞：5)

首先有这样两个性质：

- 假设初始灯的颜色都相同和变色方案相同，将 $R$ 盏蓝灯变成红色和将 $N - R$ 盏红灯变成蓝色的结果都是一样的。

- 最优方案变色的灯一定是不连续的。

于是原题就可以转化为将 $R \left( R \le \frac{N}{2} \right)$ 盏灯变色，将第 $i$ 盏灯变色可以获得 $A_{i - 1} + A_i$ 的收益，其中变色的灯**不连续**，求最大收益。

可以使用反悔贪心或 WQS 二分解决，这里使用反悔贪心。

~~~cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 200005;

int n, r;

int a[maxn], pre[maxn], nxt[maxn];

long long val[maxn], ans;

bool vis[maxn];

priority_queue<pair<long long, int> > hep;

int main()
{
    scanf("%d%d", &n, &r);
    r = min(r, n - r);
    for (int i = 1; i < n; ++i)
        scanf("%d", a + i);
    for (int i = 1; i <= n; ++i)
    {
        pre[i] = i - 1, nxt[i] = i + 1;
        hep.push(make_pair(val[i] = a[i - 1] + a[i], i));
    }
    for (int i = 1; i <= r; ++i)
    {
        while (vis[hep.top().second])
            hep.pop();
        int u = hep.top().second, l = pre[u], r = nxt[u];
        hep.pop();
        ans += val[u];
        vis[l] = vis[r] = true;
        nxt[pre[u] = pre[l]] = pre[nxt[u] = nxt[r]] = u;
        val[u] = val[l] + val[r] - val[u];
        hep.push(make_pair(val[u], u));
    }
    printf("%lld\n", ans);
    return 0;
}
~~~

---

## 作者：tder (赞：1)

You can view the [English version](https://www.luogu.com/article/vterim6t/) of this solution.

有显然结论，选 $R$ 个等价于选 $N-R$ 个，这是由于红 / 蓝没有本质区别。这使得我们可以保证 $R\le\frac N2$。

此时，有贪心结论，红格不连续。可用调整法证明，例如，若染色为 $\{\tt B,R,R,B,B\}$，此时收益为 $A_1+A_3$。而若调整为 $\{\tt B,R,B,R,B\}$，此时收益为 $A_1+A_2+A_3+A_4$，显著更优。

因此，问题转化为，选出 $R$ 个不连续的位置，选第 $i$ 个位置的贡献为 $A_i+A_{i-1}$，求最大贡献。即反悔贪心经典问题 [P1484 种树](/problem/P1484)。

复杂度 $\mathcal{O}(N\log N)$。

---

## 作者：wgyhm (赞：1)

## Description

https://www.luogu.com.cn/problem/AT_abc218_h

## Solution

做法是找规律。

首先观察到颜色交换一下对答案并没有影响，所以不妨钦定 $2R\le n$。

然后再观察到除了 $2R=n$ 的情况，红颜色的两边都为蓝色。考虑两个红颜色连续，一定可以调整成上述情况且一定不会更劣。

再观察产生贡献的位置，有 $2R$ 个，且被划分为许多段，每段都是偶数。然后直接两组两组贪心即可。拿链表维护一下，有点像反悔贪心。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long 
#define ull unsigned long long
#define maxn 200005
#define put() putchar('\n')
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
using namespace std;
Tp void read(T &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
#define fi first
#define se second
#define mk make_pair
const int mod=1e9+7;
ll power(ll x,int y=mod-2,int p=mod) {
	ll sum=1;x%=p;
	while (y) {
		if (y&1) sum=sum*x%p;
		x=x*x%p;y>>=1;
	}
	return sum;
}
int n,m;
int ans,a[maxn];
int nex[maxn],pre[maxn],vis[maxn];
priority_queue<pair<int,pair<int,int> > >q;
void del(int x) {
	pre[nex[x]]=pre[x];
	nex[pre[x]]=nex[x];
	vis[x]=1;
}
void add(int x) {
	if (x&&x<n&&nex[x]&&nex[x]<n) {
		q.push(mk(a[x]+a[nex[x]],mk(x,nex[x])));
	}
}
signed main(void){
	int i;
	read(n);read(m);
	m=min(m,n-m);
	for (i=1;i<n;i++) read(a[i]);
	if (2*m==n) {
		for (i=1;i<n;i++) ans+=a[i];
		printf("%lld\n",ans);
		return 0;
	}
	for (i=1;i<n;i++) nex[i]=i+1,pre[i]=i-1;
	for (i=1;i<n-1;i++) q.push(mk(a[i]+a[i+1],mk(i,i+1)));
	while (!q.empty()) {
		auto tmp=q.top();q.pop();
		if (vis[tmp.se.fi]||vis[tmp.se.se]) continue;
		ans+=tmp.fi;if (--m==0) break;
		int x=tmp.se.fi,y=tmp.se.se;
		del(x),del(y);
		add(pre[x]),add(nex[y]);
	}
	printf("%lld\n",ans);
	return 0;
}
//i=begin && g++ $i.cpp -o $i -std=c++14 && ./$i
```



---

