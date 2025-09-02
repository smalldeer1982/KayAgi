# Nauuo and Circle

## 题目描述

给定一圆，上有n个节点（不重合，从1到n编号）。它们按照输入连成一棵树。

求合法树的方案总数，对998244353取模。

一棵树是合法的，当且仅当这棵树中无交叉的边（两边共用一端点除外）。

注意：只要从 **最上面端点(不一定对于每个都是1，见样例1解释3&5)** 顺时针沿圆遍历所有节点得到的序列不同，那么两种方案就是不同的，即使它们本质相同。

## 样例 #1

### 输入

```
4
1 2
1 3
2 4
```

### 输出

```
16```

## 样例 #2

### 输入

```
4
1 2
1 3
1 4
```

### 输出

```
24```

# 题解

## 作者：StudyingFather (赞：6)

设 $f_x$ 为以 $x$ 为根的子树的方案数，$d_x$ 为节点 $x$ 的度数。另外为了方便起见，钦点 $1$ 号点为根。

首先容易发现为了不出现相交的情况，各子树一定对应一个连续的区间。

于是得到如下转移方程：

$$
f_u=(d_v+[u \neq 1])!\prod_{v \in son(u)} f_v
$$

上面这个式子的含义比较显然：对于根节点，其 $d_1$ 棵子树可以任意排列，对于非根节点，除了排列其所有子树之外，它自己的位置也要参与排序。

最终答案为 $n f_1$。

稍微化简一下上面的式子，就会发现答案为每个节点度数阶乘之积再乘 $n$。

```cpp
#include <iostream>
#include <algorithm>
#define MOD 998244353
using namespace std;
int t[200005];
int main()
{
 int n;
 cin>>n;
 long long ans=n;
 for(int i=1;i<n;i++)
 {
  int u,v;
  cin>>u>>v;
  t[u]++,t[v]++;
  ans=ans*t[u]%MOD*t[v]%MOD;
 }
 cout<<ans<<endl;
 return 0;
}
```


---

## 作者：yzhang (赞：4)

### [更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/10994323.html)

### [原题传送门](https://www.luogu.org/problemnew/show/CF1172B)

#### 题意：在圆上有n个节点（珂以构成凸多边形），让你给节点编号，使得将题目给你的边（一棵树）没有交叉

#### 我们钦定1为这个树的根节点。易知任意节点$x$的一颗子树的点应该是圆弧上连续的一段（~~我也不知道我当时怎么就从HNOI2019d1t3多边形yy到这道题了~~），所以就是要将一段序列划分成$siz[x]+1$段，这个节点的贡献就是$A_{siz[x]+1}^{siz[x]+1}$。因为父子之间排序方案数互不干扰，所以最后答案就是所有节点贡献的乘积（根节点要特判，因为在一个环上，不能直接排列数）

#### ~~考场上写的代码比较丑~~

```cpp
#include <bits/stdc++.h>
#define N 200005
#define mod 998244353
#define getchar nc
using namespace std;
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read()
{
    register int x=0,f=1;register char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x*f;
}
inline void write(register int x)
{
    if(!x)putchar('0');if(x<0)x=-x,putchar('-');
    static int sta[20];register int tot=0;
    while(x)sta[tot++]=x%10,x/=10;
    while(tot)putchar(sta[--tot]+48);
}
struct edge{
	int to,next;
}e[N<<1];
int head[N],cnt;
inline void add(register int u,register int v)
{
	e[++cnt]=(edge){v,head[u]};
	head[u]=cnt;
}
int n,siz[N],sizs[N],fa[N],f[N],fac[N];
inline void dfs1(register int x)
{
	siz[x]=1;
	if(x!=1)
		sizs[x]=1;
	for(register int i=head[x];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa[x])
			continue;
		fa[v]=x;
		dfs1(v);
		siz[x]+=siz[v];
		++sizs[x];
	}
}
inline void dfs2(register int x)
{
	f[x]=fac[sizs[x]];
	for(register int i=head[x];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa[x])
			continue;
		dfs2(v);
		f[x]=1ll*f[x]*f[v]%mod;
	}
}
int main()
{
	fac[0]=1;
	for(register int i=1;i<N;++i)
		fac[i]=1ll*i*fac[i-1]%mod;
	n=read();
	for(register int i=1;i<n;++i)
	{
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs1(1);
	dfs2(1);
	write(1ll*f[1]*n%mod);
	return 0;
}
```

---

## 作者：tXX_F (赞：1)

# CF1172B Nauuo and Circle

## 解题思路

由题意可知，如果我们选择一个节点作为根节点，那么每个子树都必须位于圆上的连续弧中。所以我们可以用 DP 来解决这个问题。

设 $f_u$ 是绘制子树 $u$ 的方案数，先为每个子树选择一个位置，再是 $u$ 本身，最后绘制子树，形式化的表示为：

$$
f_u=(|son(u)|+[u\ne root])!\prod\limits_{v\in son(u)}f_v
$$

但我们不需要确定根的位置，只假设根在圆上的某一点上，最后旋转圆，就可以得到答案为：$nf_{root}$ .

最后，我们可以发现，我们不需要真正写 DP，因为答案就是 $n$ 乘以每个节点度阶乘的乘积即:

$$
Answer=n\prod\limits_{i = 1}^ndegree[i]!
$$

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
char buf[1048576], *p1, *p2;
template<typename T>inline void Super_Quick_Read(T &x) {
	bool f = 1;
	x = 0;
	char ch = (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? 0 : *p1++);
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = !f;
		ch = (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? 0 : *p1++);
	}
	while (ch >= '0' && ch <= '9')x = (x << 1) + (x << 3) + (ch ^ 48), ch = (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? 0 : *p1++);
	x = (f ? x : -x);
	return;
}
template<typename T>inline void Quick_Write(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) Quick_Write(x / 10);
	putchar(x % 10 + '0');
	return;
}
int n;
long long D[200005], Answer = 1;
signed main() {
	Super_Quick_Read(n);
	for (register int i = 1; i <= n; ++i) D[i] = 1;
	for (register int i = 1, u, v; i < n; ++i)Super_Quick_Read(u), Super_Quick_Read(v), Answer = Answer * D[u] % 998244353 * D[v] % 998244353, ++D[u], ++D[v];
	Quick_Write(Answer * n % 998244353);
	return 0;
}
```

---

## 作者：Suzt_ilymtics (赞：1)

代码写起来和 SF 的是差不多的，不过理解的角度略有不同。

首先，因为它在一个环上，我们可以固定任何方案中的任何一个点作为环的起点，所以最后方案数要 $\times n$。

然后我们考虑依次去加边。

考虑加一条边 $(u,v)$，记 $du_i$ 表示 $i$ 这个点的度数。

考虑 $u$ 这个点连出去的 $v$ 放在哪。

就比如下面这张图，当前已经连了三条边，$v$ 可以放的区域有 $4$ 个，所以方案数就 $\times 4$。

然后再从 $v$ 的角度考虑也是如此，所以还要乘一个 $(du_v + 1)$ 。

![](https://cdn.luogu.com.cn/upload/image_hosting/6el5ot6q.png)

最后放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define orz cout<<"tyy YYDS!!!\n"

using namespace std;
const int MAXN = 2e5+5;
const int mod = 998244353;

int n, ans = 1;
int du[MAXN];

signed main()
{
    n = read();
    for(int i = 1; i <= n; ++i) du[i] = 1;
    for(int i = 1, u, v; i < n; ++i) {
        u = read(), v = read();
        ans = ans * du[u] % mod * du[v] % mod;
        du[u] ++, du[v] ++;
    }
    printf("%lld\n", ans * n % mod);
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题解：CF1172B Nauuo and Circle

### 题意简述

给定一圆，上有 $n$ 个不重合的节点，从 $1$ 到 $n$ 编号。按照输入连成一棵树。求没有边相交的树的方案总数。

### 解题思路

任意节点 $x$ 的一颗子树的点应该是圆弧上连续的一段。设一个节点的度（所连接的边数）为 $deg_i$，则问题转化为将一段序列划分成 $deg_i + 1$ 段。此时每个节点的贡献即为 $A_{deg_i}^{deg_i}$ 因为**父子之间排序方案数互不干扰**，所以最后答案就是所有节点贡献的乘积。

答案为：

$$n \times \prod_{i=1}^{n}deg_i$$

**阶乘**可以 $O(n)$ **预处理** $O(1)$ 查询。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
const long long mod = 998244353ll;
long long n , degree[200005] , jiecheng[200005] , ans = 1;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1 ; i < n ; i++)
	{
		int u , v;
		cin >> u >> v;
		degree[u]++;
		degree[v]++;
	}
	jiecheng[0] = 1;
	for(long long i = 1 ; i <= n ; i++)
	{
		jiecheng[i] = jiecheng[i - 1] * i % mod; 
	}
	for(int i = 1 ; i <= n ; i++)
	{
		ans = ans * jiecheng[degree[i]] % mod;
	}
	cout << ans * n % mod;
	return 0;
}
```

---

