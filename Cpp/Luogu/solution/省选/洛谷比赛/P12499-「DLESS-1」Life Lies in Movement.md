# 「DLESS-1」Life Lies in Movement

## 题目背景

**在本题题目描述最后，我们提供了一份形式化题意**。

一个小镇马上要举行一场马拉松。

## 题目描述

这个小镇可以看作一个 $n$ 个点，$n-1$ 条边的无向树，每条边有正整数边权，每个点上都有一家住户。记 $\operatorname{dis}(u,v)$ 为 $u$ 到 $v$ 的简单路径的边权和。

主办方将选择一个起点 $u$ 和终点 $v$（需要保证 $u\neq v$），从 $u$ 到 $v$ 的简单路径就是本次比赛的赛道。届时，所有住户都会到赛道上去看比赛，第 $x$ 个点上的住户会到 $u\to v$ 简单路径上满足 $\operatorname{dis}(x,y)$ 最小的 $y$ 去（显然 $y$ 是唯一的），$\operatorname{dis}(y,v)$ 被称作这家住户的“激情值”，记作 $f(x,u,v)$。

设 $g(u,v)$ 表示所有住户的激情的平均值，即 $\frac{1}{n}\sum_{x=1}^nf(x,u,v)$，主办方认为，当 $g(u,v)\ge \frac{1}{2}\operatorname{dis}(u,v)+k$ 时，这场比赛是“成功的”。

现在给出常数 $k$，求有多少有序对 $(u,v)$ 使得比赛是“成功的”。

**形式化题意：**

给定一棵 $n$ 个点的带边权无向树。

设 $\operatorname{dis}(u,v)$ 表示从 $u$ 到 $v$ 的路径长度，$f(x,u,v)$ 表示 $u\to v$ 简单路径上离 $x$ 最近的一个点到 $v$ 的距离，$g(u,v)=\frac{1}{n}\sum_{x=1}^nf(x,u,v)$。

给定一个常数 $k$，求有多少有序对 $(u,v)$ 使得 $g(u,v)\ge \frac{1}{2}\operatorname{dis}(u,v)+k$。

## 说明/提示

#### 【数据范围】

对于所有数据，保证：
- $1\le T\le 10^4$
- $1\le n,\sum n\le 10^6$
- $1\le v,k\le10^6$

**本题采用打包测试**，各测试包描述如下：

| Subtask | $\sum n\le$ | 分值 |
| :----------: | :----------: | :----------: |
| $1$ | $500$ | $5$ |
| $2$ | $2000$ | $15$ |
| $3$ | $5000$ | $20$ |
| $4$ | $10^5$ | $20$ |
| $5$ | $3\times10^5$ | $20$ |
| $6$ | $10^6$ | $20$ |


## 样例 #1

### 输入

```
4
7 3
1 6 3
6 4 1
6 7 4
2 6 2
3 6 1
5 6 2
6 1
2 5 4
2 1 1
2 3 3
2 4 2
6 2 2
10 2
3 2 3
4 9 2
3 10 4
10 4 1
7 6 1
3 5 3
9 8 2
7 10 1
8 1 2
10 1
1 7 2
3 2 3
8 6 4
5 4 2
9 3 2
4 10 3
10 1 4
2 5 3
9 6 2
```

### 输出

```
0
3
2
24```

# 题解

## 作者：Gold14526 (赞：10)

变一下这个式子：

$$\frac{\sum_{x=1}^nf(x,u,v)}{n}\ge \frac{1}{2}\operatorname{dis}(u,v)+k$$

$$2\sum_{x=1}^nf(x,u,v)\ge n\times \operatorname{dis}(u,v)+2nk$$

$$2\sum_{x=1}^nf(x,u,v)-n\times \operatorname{dis}(u,v)\ge 2nk$$

注意到 $f(x,u,v)+f(x,v,u)=\operatorname{dis}(u,v)$。

所以 $\sum_{x=1}^n(f(x,u,v)+f(x,v,u))=n\times \operatorname{dis}(u,v)$。

于是：

$$2\sum_{x=1}^nf(x,u,v)-\sum_{x=1}^n(f(x,v,u)+f(x,u,v))\ge 2nk$$

$$\sum_{x=1}^n(f(x,u,v)-f(x,v,u))\ge 2nk$$

设 $K=2nk$。

注意到 $f(x,u,v)-f(x,v,u)=\operatorname{dis}(x,v)-\operatorname{dis}(x,u)$。

所以：

$$\sum_{x=1}^n(\operatorname{dis}(x,v)-\operatorname{dis}(x,u))\ge K$$

设 $s_u=\sum_{x=1}^n \operatorname{dis}(x,u)$。

则：

$$s_v-s_u\ge K$$

简单换根算出所有点的 $s$ 之后排序，双指针即可。

时间复杂度 $O(n\log n)$，瓶颈在于排序。

```cpp
#include<bits/stdc++.h>
#define cint const int
#define uint unsigned int
#define cuint const unsigned int
#define ll long long
#define cll const long long
#define ull unsigned long long
#define cull const unsigned long long
#define sh short
#define csh const short
#define ush unsigned short
#define cush const unsigned short
using namespace std;
ll read()
{
	ll num=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		num=(num<<1)+(num<<3)+(ch-'0');
		ch=getchar();
	}
	return num;
}
void print(cll x)
{
	if(x<10)
	{
		putchar(x+'0');
		return;
	}
	print(x/10);
	putchar(x%10+'0');
}
void princh(cll x,const char ch)
{
	print(x);
	putchar(ch);
}
int n;
ll k,K;
int head[1000001];
struct edge{
	int to,nxt,val;
}e[2000000];
int tot;
void add_edge(cint u,cint v,cint val)
{
	e[++tot]=edge{u,head[v],val};
	head[v]=tot;
	e[++tot]=edge{v,head[u],val};
	head[u]=tot;
}
int siz[1000001];
ll a[1000001];
void dfs(cint u,cint father,cll dep)
{
	siz[u]=1;
	a[1]+=dep;
	for(int i=head[u];i;i=e[i].nxt)
	{
		if(e[i].to==father)continue;
		dfs(e[i].to,u,dep+e[i].val);
		siz[u]+=siz[e[i].to];
	}
}
void calc(cint u,cint father)
{
	for(int i=head[u];i;i=e[i].nxt)
	{
		if(e[i].to==father)continue;
		a[e[i].to]=a[u]-1ll*siz[e[i].to]*e[i].val+1ll*(n-siz[e[i].to])*e[i].val;
		calc(e[i].to,u);
	}
}
int l;
ll ans;
void solve()
{
	n=read();
	k=read();
	K=n*k<<1;
	tot=ans=0;
	for(int i=1;i<=n;++i)head[i]=0;
	for(int i=1;i<n;++i)
	{
		cint u=read(),v=read(),val=read();
		add_edge(u,v,val);
	}
	dfs(1,0,0);
	calc(1,0);
	sort(a+1,a+n+1);
	l=0;
	for(int i=1;i<=n;++i)
	{
		while(a[l+1]<=a[i]-K)++l;
		ans+=l;
	}
	princh(ans,'\n');
}
int main()
{
	int T=read();
	while(T--)solve();
	return 0;
}
```

---

## 作者：fish_love_cat (赞：2)

相关定义见题面。求有多少有序对 $(u,v)$ 使得：

$$\frac{1}{n}\sum_{x=1}^nf(x,u,v)\ge \frac{1}{2}\operatorname{dis}(u,v)+k$$

去分母：

$$2\sum_{x=1}^nf(x,u,v)\ge n\operatorname{dis}(u,v)+2nk$$

移项：

$$2\sum_{x=1}^nf(x,u,v)- n\operatorname{dis}(u,v)\ge2nk$$

根据 $f$ 的定义，我们知道：

$$\operatorname{dis}(u,v)=f(x,u,v)+f(x,v,u)$$

代入原式：

$$2\sum_{x=1}^nf(x,u,v)- n(f(x,u,v)+f(x,v,u))\ge2nk$$

上式等价于：

$$2\sum_{x=1}^nf(x,u,v)- \sum_{x=1}^nf(x,u,v)-\sum_{x=1}^nf(x,v,u)\ge2nk$$

把一些项消掉：

$$\sum_{x=1}^nf(x,u,v)-\sum_{x=1}^nf(x,v,u)\ge2nk$$

合并：

$$\sum_{x=1}^n(f(x,u,v)-f(x,v,u))\ge2nk$$

由于是一棵树，$x$ 离路径最近的点的距离其实与 $f(x,u,v)-f(x,v,u)$ 无关，所以可以直接将其等价为 $\text{dis}(x,v)-\text{dis}(x,u)$。  
将其代入原式得到：

$$\sum_{x=1}^n(\text{dis}(x,v)-\text{dis}(x,u))\ge2nk$$

拆开：

$$\sum_{x=1}^n\text{dis}(x,v)-\sum_{x=1}^n\text{dis}(x,u)\ge2nk$$

那么我们只需要对于每一个点 $u$ 求解 $\sum_{x=1}^n\text{dis}(x,u)$，然后出来跑个双指针计数就行了。

换根 dp 是好做的，代码不放了。

---

## 作者：Delete_error (赞：1)

听说这比赛好题多就来补了，然后写这篇记录一下。

### update:
2025/6/16修改了下标的笔误。
### 题目：
[Link](https://www.luogu.com.cn/problem/P12499)，我觉得形式化题意挺详细了。

### 式子推导：
方便理解起见，我们设对于每组 $f(x,u,v)$ 其中满足处于 $u→v$ 路径上且离 $x$ 最近的点为 $y$，则有 $f(x,u,v)= dis(y,v)$。

原式：
$$
\frac{1}{n}\sum_{x = 1}^{n}f(x,u,v)\ge\frac{1}{2} dis(u,v) + k
$$
通分：
$$
2\times \sum_{x = 1}^{n}f(x,u,v)\ge n\times dis(u,v) + 2\times n\times k
$$
将变量移至一侧：
$$
2\times \sum_{x = 1}^{n}f(x,u,v) -n\times dis(u,v)\ge   2\times n\times k
$$
由于在无向树上，则有：
$$
\text {对于}x \in [1,n] \text {，都有}dis(u,v)=dis(y,u)+dis(y,v)=f(x,u,v)+f(x,v,u)
$$
代入进式子：
$$
2\times \sum_{x = 1}^{n}f(x,u,v) -n\times (f(x,u,v)+f(x,v,u))\ge   2\times n\times k
$$
等价为：
$$
2\times \sum_{x = 1}^{n}f(x,u,v) -\sum_{x = 1}^{n} (f(x,u,v)+f(x,v,u))\ge   2\times n\times k
$$
继续化简：
$$
\sum_{x = 1}^{n}(f(x,u,v) -f(x,v,u))\ge   2\times n\times k
$$
化简到这一步已经差不多了，但因为 $f$ 并不好求，所以我们将前面的式子再次代入：
$$
\sum_{x = 1}^{n}(dis(y,v)-dis(y,u))\ge   2\times n\times k
$$
由于在无向树上，可以用 $x$ 将 $y$ 代掉:
$$
\sum_{x = 1}^{n}((dis(x,v)-dis(x,y))-(dis(x,u)-dis(x,y)))\ge   2\times n\times k
$$
化简:
$$
\sum_{x = 1}^{n}(dis(x,v)-dis(x,u))\ge   2\times n\times k
$$
分开：
$$
\sum_{x = 1}^{n}dis(x,v)-\sum_{x = 1}^{n}dis(x,u)\ge   2\times n\times k
$$
设 $Q(u)=\sum_{x = 1}^{n}dis(x,u)$

则最终式子为:
$$
Q(v)-Q(u)\ge 2\times n\times k
$$
到这里就很好求了，对于每个 $u$ 求一下 $Q(u)$，换根就可以处理。然后 $Q(u)$ 排序之后，每次固定右端点后的这个式子的答案具有单调性，双指针指 $v$ 和 $u$ 就做完了。换根和双指针 $O(n)$，但排序 $O(n\log n)$，总的时间复杂度是 $O(n\log n)$。
### Code:
代码比较简单，但是我写了所以放了。

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int MAXN=1e6+5;
ll t,n,k;
ll s[MAXN],f[MAXN],dis[MAXN];
struct Edge{
	int v,w;
};
vector<Edge> e[MAXN];
void dfs(int u,int fa){
	for(int i=0;i<e[u].size();i++){
		ll v=e[u][i].v,w=e[u][i].w;
		if(v!=fa){
			dis[v]=dis[u]+w;
			dfs(v,u);
			s[u]+=s[v];
		}
	}
}
void solve(int u,int fa){
	for(int i=0;i<e[u].size();i++){
		ll v=e[u][i].v,w=e[u][i].w;
		if(v!=fa){
			f[v]=f[u]+(n-2*s[v])*w;
			solve(v,u);
		}
	}
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++) e[i].clear();
		for(int i=1;i<=n-1;i++){
			ll u,v,w;
			cin>>u>>v>>w;
			s[u]=s[v]=1;
			f[u]=f[v]=0;
			dis[u]=dis[v]=0;
			e[u].push_back(Edge{v,w});
			e[v].push_back(Edge{u,w});
		}
		dfs(1,-1);
		for(int i=1;i<=n;i++) f[1]+=dis[i];
		solve(1,-1);
		sort(f+1,f+n+1);
		//cout<<f[1]<<"\n";
		ll l=1,ans=0;
		for(int r=1;r<=n;r++){
			while(f[r]-f[l]>=2*n*k) l++;
			ans+=l-1;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：SafariMo (赞：1)

真真 Adhoc 题。

考虑移项为 $2\sum_{x=1}^n f(x ,u, v) - n\operatorname{dis}(u , v) \ge 2nk$。

注意到 $f(x , u , v) + f(x ,  v ,u) = \operatorname{dis}(u ,v)$，$f(x , u , v) - f(x , v , u) = \operatorname{dis}(x ,v) - \operatorname{dis}(x , u)$。

因此变为 $\sum_{x=1}^n \operatorname{dis}(v , x) - \operatorname{dis}(u , x)\ge 2nk$。

换根 dp 求出 $a_x = \sum_{x=1}^n \operatorname{dis}(u , x) $ 后相当于求 $a_i - a_j \ge x$ 的个数，排序后双指针或二分即可。

[link](https://www.luogu.com.cn/record/216865010)

---

## 作者：Rain_chr (赞：0)

:::epigraph[——蒋校长(jkx)]
我不明白为什么这么多人都觉得这题是 ad-hoc
:::

提供一个非常好写，不用换根的做法。

开题，一眼一个点分治 $O(n\log^2 n)$ 做法，极其难写不说，$n=10^6$ 没有任何通过的可能，于是来考虑推一下式子。

先将不等式两边同乘 $2n$ 得到 $2\sum_{i=1}^n f(i,u,v) \ge n\times dis(u,v)+2nk$

钦定以 $1$ 为根，设 $w_x$ 为 $(x,fa)$ 这条边的边权，我们先来用 $w_x$ 表示一下 $\sum_{i=1}^n f(i,u,v)$：

$$
\begin{aligned}
\sum_{i=1}^n f(i,u,v)
&=
\sum_{i\in path[u,\operatorname{lca(u,v)})} w_i \times siz_i+
\sum_{i\in path(\operatorname{lca(u,v)},v]} w_i \times (n-siz_i)
\end{aligned}
$$

注意路径用的是一边开的区间，表示这两段路径都是不含 $\operatorname{lca(u,v)}$ 的，我们相当于是对于每一条路径上的边都计算了他的贡献，这是比较套路的**拆贡献**。

同时不难发现 $dist(u,v)=\sum_{i\in path[u,v]} w_i$，代入原式可得：

$$
2\sum_{i=1}^n f(i,u,v) \ge n\times dis(u,v)+2nk \\
2\sum_{i\in path[u,\operatorname{lca(u,v)})} w_i \times siz_i+
2\sum_{i\in path(\operatorname{lca(u,v)},v]} w_i \times (n-siz_i) \ge n \sum_{i\in path[u,v]} w_i+2nk \\
\sum_{i\in path[u,\operatorname{lca(u,v)})} w_i \times (2siz_i-n)+
\sum_{i\in path(\operatorname{lca(u,v)},v]} w_i \times (n-2siz_i) \ge 2nk \\
$$

这个时候我们就觉得有点意思了，上升段和下降段符号是完全相反的。

设 $f_i=\sum_{j\in path[i,1)} w_j\times (2siz_j-n)$，其实我们上面的式子等价于：

$$
f_u-f_v \ge 2nk
$$

因为 $path[\operatorname{lca(u,v)},1]$ 这一段上边全的贡献全部正负抵消掉了。

于是直接求出 $f$，然后排序计算答案即可，瓶颈完全在于排序。

---

## 作者：_ayaka_ (赞：0)

诈骗。

### 思路

转换三次式子即可。

首先入手会发现 $g(u,v)$ 以及 $\frac{1}{2} \operatorname{dis}(u,v)$这个东西很恶心，遂把式子整体乘一个 $2\times n$。转换出来是这样的：

$$2\times \sum_{x=1}^n f(x,u,v) \ge n\times \operatorname{dis}(u,v) + 2nk$$

然后考虑到 $n\times \operatorname{dis}(u,v)=\sum_{x=1}^n f(x,u,v)+f(x,v,u)$，则式子再变为：

$$\sum_{x=1}^n f(x,u,v) \ge \sum_{x=1}^n f(x,v,u) + 2nk$$

移项后得：

$$\sum_{x=1}^n f(x,u,v)-f(x,v,u) \ge  2nk$$

最后发现 $f(x,u,v)-f(x,v,u)=\operatorname{dis}(x,v)-\operatorname{dis}(x,u)$，得出最终式子：

$$\sum_{x=1}^n \operatorname{dis}(x,v)-\operatorname{dis}(x,u) \ge  2nk$$

设 $\sum_{x=1}^n\operatorname{dis}(x,u) = d_u$，换根求出所有的 $d_u$ 后双指针即可。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T, n, k, x, y, z, d[2000005], son[2000005], h[2000005], ans;
vector<pair<int, int>> e[2000005];
int dfs(int u, int fa) {
	int res = 0;
	for (auto i : e[u]) {
		int v = i.first, w = i.second;
		if (v == fa) continue;
		res += dfs(v, u) + w;
		son[u] += son[v];
		h[v] = w;
	}
	return res;
}
void dp(int u, int fa) {
	d[u] = d[fa] - h[u] * son[u] + h[u] * (son[1] - son[u]);
	for (auto i : e[u]) {
		int v = i.first;
		if (v == fa) continue;
		dp(v, u);
	}
	return ;
}
signed main() {
	cin >> T;
	while (T--) {
		ans = 0;
		cin >> n >> k;
		for (int i = 1; i <= n; i++) e[i].clear(), d[i] = h[i] = 0, son[i] = 1;
		k = 2 * n * k;
		for (int i = 1; i < n; i++) {
			cin >> x >> y >> z;
			e[x].push_back({y, z});
			e[y].push_back({x, z});
		}
		d[0] = dfs(1, 0);
		dp(1, 0);
		sort(d + 1, d + n + 1);
		d[n + 1] = 0x3f3f3f3f3f3f;
		for (int i = 1, j = 1; i <= n; i++) {
			while (j <= n && d[j] - d[i] < k) j++;
			ans += n - j + 1;
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

