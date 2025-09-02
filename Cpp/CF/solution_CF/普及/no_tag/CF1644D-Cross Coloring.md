# Cross Coloring

## 题目描述

There is a sheet of paper that can be represented with a grid of size $ n \times m $ : $ n $ rows and $ m $ columns of cells. All cells are colored in white initially.

 $ q $ operations have been applied to the sheet. The $ i $ -th of them can be described as follows:

- $ x_i $ $ y_i $ — choose one of $ k $ non-white colors and color the entire row $ x_i $ and the entire column $ y_i $ in it. The new color is applied to each cell, regardless of whether the cell was colored before the operation.

The sheet after applying all $ q $ operations is called a coloring. Two colorings are different if there exists at least one cell that is colored in different colors.

How many different colorings are there? Print the number modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
2
1 1 3 2
1 1
1 1
2 2 2 3
2 1
1 1
2 2```

### 输出

```
3
4```

# 题解

## 作者：yydfj (赞：4)

这是本蒟蒻第三十五次写的题解，如有错误点请好心指出！

## 问题简述

给你一个 $n \times m$ 的矩阵，你可以进行 $q$ 次操作，每次操作给定 $(x,y)$，表示从 $k$ 种颜色中选出其中一种覆盖在第 $x$ 行和第 $y$ 列的所有格子上，求最终得到不同的染色结果的数量并取模 $998244353$。

## 解法综述

根据题意发现 $q$ 次操作结束后，某个格子的颜色是由染该格子颜色的最后一次操作决定的，于是我们考虑将原来的操作顺序倒转过来，这样在倒序操作中染某个格子颜色的第一个操作即决定该格子的最终颜色，就不需要再考虑某个格子的颜色被多次操作覆盖的情况，因为在此之后的相同操作都是无效操作。

同时我们还要考虑一种情况，当 $n$ 行全部都被覆盖时，其实相当于 $m$ 列全部都被覆盖了，此后的所有操作都是无效操作，$m$ 列全部都被覆盖的情况同理。

我们记能够成功给某个格子染色的操作总数为 $ss$，那么最终答案为 $k^{ss}$，可以用快速幂解决。

## 代码描述

```cpp
#include<cstdio>
#include<cstring>
typedef long long ll;
const ll mod=998244353;
bool row[200005],col[200005];
ll T,n,m,k,q,xx[200005],yy[200005],crow,ccol,ss;
ll ksm(ll x,ll y)
{
	ll res=1;
	while(y)
	{
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		crow=ccol=ss=0;
		memset(row,0,sizeof(row));
		memset(col,0,sizeof(col));
		scanf("%lld%lld%lld%lld",&n,&m,&k,&q);
		for(int i=1;i<=q;i++) scanf("%lld%lld",&xx[i],&yy[i]);
		for(int i=q;i>=1;i--)
		{
			bool bz=0;
			if(crow<n&&ccol<m&&!row[xx[i]]) row[xx[i]]=1,crow++,bz=1;
			if(crow<n&&ccol<m&&!col[yy[i]]) col[yy[i]]=1,ccol++,bz=1;
			if(bz) ss++;
		}
		printf("%lld\n",ksm(k,ss));
	}
	return 0;
}
```

---

## 作者：FiraCode (赞：3)

### 题解思路：
我们就倒着考虑，那么题目就变成了：
> 每次选一行一列，然后染成一个颜色，后染的色不会覆盖原来染得颜色。

那么当一个颜色会有颜色，当且仅当他是满足没有全覆盖并且行没有完全覆盖或列没有完全覆盖；

那么我们定义两个数组一个表示当前行是否完全覆盖，另一个表示当前列是否完全覆盖。

那么我们就顺着做一遍，在用两个变量分别表示覆盖了多少行和覆盖了多少列。

那么只要行数等于 $n$ 了或者列数等于 $m$ 了就退出或者跳过。

**十年OI一场空，不开longlong见祖宗。**
### AC CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000005, mod = 998244353;
int n, m, k, q;
int x[N], y[N];
int fn[N], fm[N];
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d%d%d", &n, &m, &k, &q);
		for (int i = 1; i <= q; i++)
			scanf("%d%d", &x[i], &y[i]);
		int cn = 0, cm = 0;
		long long res = 1;
		for (int i = q; i >= 1; i--)
		{
			if (cn == n || cm == m)//若全覆盖就跳过，但最好直接跳出
				continue;
			int fl = 1;
			if (!fn[x[i]])//若没有覆盖就覆盖
				cn++, fn[x[i]] = 1, fl = k;
			if (!fm[y[i]])//同理
				cm++, fm[y[i]] = 1, fl = k;
			res = res * fl % mod;//统计答案
		}
		for (int i = q; i >= 1; i--)
			fn[x[i]] = fm[y[i]] = 0;//多组数据清空
		printf("%d\n", res);
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：2)

讲一个题解区没有的思路。

### 题意：

现 $n \times m$ 的矩阵中，所有格子均为白色，现还给出 $k$ 种不同的颜色（非白色）。

需要执行 $q$ 次操作，每次操作给定 $(x,y)$：

在 $k$ 种颜色里任选一种颜色，将第 $x$ 行和第 $y$ 列的所有格子染成这种颜色，这种染色操作将覆盖之前的颜色。

### 思路：

由于颜色会相互覆盖，对于一个格子而言，它的颜色只与最后一次染色有关。

设第 $i$ 行第 $j$ 列的格子被染色的最后时刻是 $a_{i,j}$，若是集合中共有 $t$ 种颜色（不包含白色），则答案应该是 $k^t$，因为这 $t$ 个时刻中，每个时刻的颜色都可以从 $k$ 颜色种中任取。

然而，格子的总个数可能很多，不可能一个个记录每一个格子的情况。

但是因为每次操作都是针对整行/整列的，所以可以我们标记每行每列的状态：

- $a_i$ 表示第 $i$ 行的最晚染色时间。
- $b_i$ 表示第 $j$ 列的最晚染色时间。

则第 $i$ 行第 $j$ 列的元素，其颜色与 $\max(a_i,b_j)$ 时刻的染色有关。

现在我们要求 $\max(a_i,b_j)$ 有多少种不同的取值，我们分两种情况考虑：

- $\max(a_i,b_j)=a_i$，则 $b$ 中存在一个元素，满足 $a_i \ge b_j$，即要 $a_i \ge \min\limits_{j=1}^{m}(b_j)$ 满足。所以枚举 $i$ ，看看需要将哪些 $a_i$ 加入集合中。

- 同理，如果 $\max(a_i,b_j)=b_j$，则 $a$ 中存在一个元素，满足 $b_j \ge a_i$，即要 $b_j \ge \min\limits_{i=1}^{n}(a_i)$ 满足。所以枚举 $j$ ，看看需要将哪些 $b_j$ 加入集合中。

最后，我们将这个集合去重，同时去除集合中大小为 $0$ 的元素（因为白色不能转变为其他 $k$ 种颜色），如果集合的大小为 $t$，那么答案就是 $k^t$。

时间复杂度是：$O(T\times (n+m+q))$。

但是如果 $\sum n+m$ 的值都很大，即都是 $2 \times 10^5$，那么将会超时，所以考虑优化，对于去重，我们可以使用 ``set`` 进行去重。

求 $\min\limits_{j=1}^{m}(b_j),\min\limits_{i=1}^{n}(a_i)$ 的时候，我们使用 ``map`` 容器表示 $a,b$，所以我们可以遍历 $map$ 中的元素求最小值，这样对于没有涂色的地方，我们就不用遍历。

然后写一个快速幂就行了。

这样我们的时间复杂度就优化到了 $O(T \times (q \log q))$

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=998244353;
inline ll read(){ 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,m,k,q,t;
ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1ll)
		  ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1ll;
	}
	return ans;
}
ll Min(map<ll,ll> a){
	ll ans=INT_MAX; 
	for(auto i:a)
	  ans=min(ans,i.second); 
	return ans;
}
int main(){
	T=read();
	while(T--){
		set<ll> s;
		map<ll,ll> a,b; 
		n=read(),m=read(),k=read(),q=read();
		for(int i=1;i<=q;i++){
			ll x=read(),y=read();
			a[x]=b[y]=i;
		}
		t=Min(a);
		if(a.size()!=n)
		  t=0;
		for(auto i:b)
		  if(i.second>=t)
		    s.insert(i.second);
		t=Min(b);
		if(b.size()!=m)
		  t=0;
		for(auto i:a)
		  if(i.second>=t)
		    s.insert(i.second);
		if(s.count(0)) 
		  s.erase(0);
		write(qpow(k,s.size()));
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：KAMIYA_KINA (赞：1)

## Tag

计数。

## Preface

考场上因为这题打错了一个地方然后摆烂了，感觉后面两题本来是可以做的啊……

## Description

给一个 $n\times m$ 的棋盘涂上 $[1, k]$ 的颜色，涂色的规则是，选择一个 $(x,y)$ 坐标，使其 $x$ 行和 $y$ 列全都涂成一个颜色，给定 $q$ 个涂色位置 $(x,y)$，求最后棋盘有多少种情况，对 $998244353$ 取模。

$\texttt{data range:} n,m,k,q \leq 2\times 10^5$.


## Solution

直接做是困难的，不妨反过来思考，我们优先涂最后需要涂色的位置，因为这个位置会把所有其他的颜色覆盖住，如果说从后往前涂，某一个位置其其他位置都被覆盖了，那么这个位子就没有意义，所以不计入贡献。

于是我们记录横坐标和纵坐标哪些位置被涂过，但是注意我们还需要记录横行和纵列有多少个位置被涂过，因为如果说下图这样一种涂色的话，那么也是没有意义的。

```
. . .

. . .

* * *

```

其中 `*` 代表已经被涂过，可以发现不论我们选择剩下的哪一个位置涂入都不会影响棋盘的状态，所以我们需要特判这个地方。（我考场上就是这里写错了然后就摆烂了）

## Code

```cpp
const int N = 2e5 + 10;
const int mod = 998244353;

int n, m, k, q, cntx, cnty;
int X[N], Y[N];
bool visx[N], visy[N];

inline void work() {
  cin >> n >> m >> k >> q;
  ll ans = 1;
  for(int i = 1; i <= q; i++) 
    cin >> X[i] >> Y[i];
  for(int i = q; i; i--) {
    bool flag = false;
    flag |= (visx[X[i]] && visy[Y[i]]);
    flag |= (visx[X[i]] && cntx == n);
    flag |= (visy[Y[i]] && cnty == m);
    if(!visx[X[i]]) visx[X[i]] = true, cntx++;
    if(!visy[Y[i]]) visy[Y[i]] = true, cnty++;
    if(!flag) ans = ans * k % mod;
  }
  for(int i = q; i; i--) 
    visx[X[i]] = false, visy[Y[i]] = false;
  cntx = 0, cnty = 0;
  cout << ans << '\n';
  return ;
}

inline void solve() {
  cin.sync_with_stdio(false);
  int t;
  cin >> t;
  while(t--) 
    work();
  return ;
}
```

---

## 作者：fujiayu (赞：0)

# CF1644D Cross Coloring
## 题意:
在一个 $n$ 行 $m$ 列的网格里执行 $q$ 次操作，每次操作在 $k$ 种颜色中 **(没有初始颜色)** 选择一种给第 $x_i$ 行和第 $y_i$ 列染色且覆盖原有颜色，问最终染色方案数
## 做法:
因为后染的色会覆盖先染的色，所以最后染的色一定不会被覆盖，不需要处理被覆盖的情况,所以我们从后向前枚举每次操作，如果当前列和当前行都已经被染色，那么**这次操作会被后面的操作覆盖**，对结果**没有影响，不需要统计**，否则共有 $k$ 种染色方法，将答案 $\times k$。
### 特判:
当网格全部被覆盖，即 $n$ 行或 $m$ 列全部被覆盖时，前面的操作对最终结果都没有影响,直接跳出即可。

时间复杂度 $O(TQ)$

记得开 `long long` ！
## 代码:
```cpp
#include<iostream>
#define int long long
using namespace std;

int T;
int a[200010], b[200010];
bool x[200010], y[200010];

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

int maxx(int x, int y)
{
	return x > y ? x : y;
}

signed main()
{
	T = read();
	while(T--)
	{
		int n=read(), m=read(), k=read(), q=read();
		int xf=0, yf=0, ans=1, c=maxx(n, m);
		for(int i=1; i<=c; i++)
		{
			x[i] = y[i] = false;
		}
		for(int i=1; i<=q; i++)
		{
			a[i] = read();
			b[i] = read();
		}
		for(int i=q; i>=1; i--)
		{
			if(xf == n || yf == m)
			{
				break;
			}
			bool flag = false;
			if(x[a[i]] == false)
			{
				x[a[i]] = true;
				flag = true;
				xf ++;
			}
			if(y[b[i]] == false)
			{
				y[b[i]] = true;
				flag = true;
				yf ++;
			}
			if(flag)
			{
				ans *= k;
				ans %= 998244353;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Troubadour (赞：0)

### 题意

给你一个 $n\times m$ 的网格,每次给定 $(x_i,y_i)$，将 $x_i$ 这一行和 $y_i$ 这一列全部涂上某种颜色，求最后可能得到的不同的染色结果。

### 分析

看这个数据范围，首先排除直接按题意模拟。

我们考虑，如果正着做的话，将会被卡住，因为首先我们不容易求每种颜色的贡献，其次不同的染色方案可能会导致相同的结果，要么算重，要么算漏。

所以我们尝试换一个角度去分析：对于每一个格子，后来的染色一定会覆盖先来的，所以我们可以从后往前遍历操作，每次找出染色时会染哪些空格子。假如这次操作所在的行列都被染过了，这次操作也就没有任何意义了，直接跳过去。

我们可以发现，每一次有效的染色操作，它都有 $k$ 种不同的可能，当染不同颜色的时候最后得到的结果一定是不同的，统计答案的时候，就乘上一个 $k$。

具体实现的时候，我们可以开两个数组记录当前行或列有没有被选择，若没被选择的话，就标记这一行或列并统计答案。

注意一点,假如若干次操作之后，每一行都被覆盖到了，但是前面的操作并没有使得所有列都被打上标记，很显然棋盘已经被涂满了，也就不能再接着操作，直接结束遍历。

感觉这题思维难度要比 E 高一点。

### Code:

```cpp
#include<bits/stdc++.h>
#define int long long
namespace GGMZ
{
	const int N = 2e5 + 5;
	const int mod = 998244353;
	bool vis1[N], vis2[N];
	int n, m, k, q, a, b;
	int x[N], y[N];
	int ans;
	void work()
	{
		ans = 1;
		a = b = 0;
		std::cin >> n >> m >> k >> q;
		for (int i = q;i >= 1;i--)
		{
			std::cin >> x[i] >> y[i];
		}
		for (int i = 1;i <= q;i++)
		{
			if (a == n || b == m)break;
			if (vis1[x[i]] == 0 || vis2[y[i]] == 0)
			{
				ans = ans * k%mod;
				if (vis1[x[i]] == 0)a++;
				if (vis2[y[i]] == 0)b++;
				vis1[x[i]] = vis2[y[i]] = 1;
			}
		}
		std::cout << ans << '\n';
		memset(vis1, 0, sizeof(bool)*(n + 5));
		memset(vis2, 0, sizeof(bool)*(m + 5));
	}
}
#undef int 
int main()
{
	int t;
	std::cin >> t;
	while (t--)GGMZ::work();
	return 0;
}
```

---

## 作者：清烛 (赞：0)

题意：$n\times m$ 的格子一开始全为白色，$q$ 次操作，每次操作选择 $(r, c)$，然后将第 $r$ 行全部和第 $c$ 列全部格子涂成 $[1, k]$ 中的任意颜色。问最后有多少种可能的局面。$T\le 10^4$，$1\le n,m,k,q\le 2\times 10^5$，$\sum q\le 2\times 10^5$。

遇到涂色问题不妨倒序考虑，我们会发现，一次涂色操作会对答案产生贡献，当且仅当它影响的行或列至少有一方没被覆盖完。那么我们用 `std::set` 分别维护一下被占用了的行和列，若当前操作的 $r$ 或 $c$ 没有被占用，那么就加入 `set` 并且让答案乘上 $k$。有一个小优化即记录一下占用的行和列的个数，若占用了 $n$ 行或占用了 $m$ 列则直接终止循环。

```cpp
const int maxn = 2e5 + 5;
int n, m, k, q;
int qx[maxn], qy[maxn];

int main() {
    int T; read(T);
    while (T--) {
        read(n, m, k, q);
        FOR(i, 1, q) read(qx[i], qy[i]);
        int visr = 0, visc = 0;
        set<int> remr, remc;
        modint ans = 1;
        DEC(i, q, 1) {
            if (visr == n || visc == m) break;
            int flg = 0;
            if (!remr.count(qx[i]))
                ++visr, remr.insert(qx[i]), flg = 1;
            if (!remc.count(qy[i]))
                ++visc, remc.insert(qy[i]), flg = 1;
            if (flg) ans *= k;
        }
        print(ans);
    }
    return output(), 0;
}
```

另外，部分代码使用的是 $O(nT)$ 的预处理来维护被占用的行/列，但是由于没有 $\sum n$ 的限制，这样的代码可能过了 Pretests 后由于评测波动被 hack（如果常数偏大）。这启示我们**注意观察题目限制条件，并且平时尽可能写常数小的代码**。

---

