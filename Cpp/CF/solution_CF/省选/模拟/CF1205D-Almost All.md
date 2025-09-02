# Almost All

## 题目描述

给定一棵有 $n$ 个节点的树。你需要在树的每条边上写上非负整数，使得满足以下条件：

对于任意两个节点 $i$ 和 $j$，考虑它们之间的路径，并计算该路径上所有边的数字之和。将所有得到的和写在黑板上。要求从 $1$ 到 $\lfloor \frac{2n^2}{9} \rfloor$ 的每一个整数都至少出现在黑板上一次。

保证一定存在一种满足条件的方案。

## 说明/提示

在第一个样例中，节点 $1$ 和 $2$ 之间的距离为 $2$，节点 $2$ 和 $3$ 之间的距离为 $1$，节点 $1$ 和 $3$ 之间的距离为 $3$。

在第三个样例中，黑板上会写下从 $1$ 到 $9$（包含 $9$）的数字，而只需要从 $1$ 到 $5$ 即可通过测试。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 3
2 1
```

### 输出

```
3 2 1
1 2 2
```

## 样例 #2

### 输入

```
4
2 4
2 3
2 1
```

### 输出

```
4 2 1
3 2 2
1 2 3
```

## 样例 #3

### 输入

```
5
1 2
1 3
1 4
2 5
```

### 输出

```
2 1 1
5 2 1
3 1 3
4 1 6
```

# 题解

## 作者：lottle1212__ (赞：7)

# [Almost All](https://www.luogu.com.cn/problem/CF1205D)

首先吐槽一嘴，这个数据范围很奇怪，这题是可以做到 $O(n)$ 的，可是 $n\leq 1000$。这什么神操作？

先不管数据范围以及题目的要求。拿到这题，首先按照题意随意构造几个。如果是一条长度为 $n$ 的链，若边权全为 $1$ 则可以构造出 $[0, n-1]$。瞄一眼所求，发现是一个二次的式子，于是想到把这条链看作左右两段，想办法让它们乘起来，我们可以类似进制的操作。先按照前面所述的方法，设左边构造出 $[0, a]$，右边构造出 $[0, b]$，此时，将右边的边权全部乘上 $a+1$，则右边变成了 $0, a+1, 2(a+1), \dots, b(a+1)$，再加上左边 $[0, a]$，则可以构造出 $[0, ab+a+b]$ 的数。当然如果分成更多段，当 $n$ 大的时候可以做得更好，不过在此题没有必要。

再回过头看看题目要求，把 $\left\lfloor\frac{2n^2}{9}\right\rfloor$ 中的 $\frac{2n^2}{9}$ 看成 $\frac{n}{3}\times\frac{2n}{3}$，则在一条链的情况，只需要把链分成长度比为 $\frac{1}{2}$ 的两段，当然比离 $1$ 越近越好，就可以达到题目要求。那么，对于一般情况，只需要把整棵树拆成两棵分别用链的方法解决。

而对于单独一棵的贡献，若要从链的方法迁移，则能产生贡献的就是树上的节点到树根的链。比如操作子树 $u$ 时，对于两棵子树 $v1, v2$，设子树 $v1$ 可以做出 $[0, a]$，子树 $v2$ 可以做出 $[0, b]$。设边 $(u, v1)$ 的边权为 $w$（这是因为 $v1$ 以前的子树已经表示出了 $[0, w-1]$），则子树 $v1$ 实际表示出了 $[w, w+a]$。那么给子树 $v2$ 的值都加上 $w+a+1$，即将 $(u, v2)$ 的边权设为 $w+a+1$，就可以最大化表示出的数的数量了。可以发现，一棵子树 $u$ 能产生的贡献为 $size_u-1$，这个使用归纳法可证。则像做链的方法一样把子树 $u$ 分成两部分即可。

为了方便划分这两部分，可以先求出树的重心，此时将重心作为根，则每棵子树的大小都不超过 $\left\lfloor\frac{n}{2}\right\rfloor$，把子树按大小降序排，按顺序取子树，当取的总大小不小于 $\left\lfloor\frac{n}{3}\right\rfloor$ 为止，则一定能分成大小差不超过 $\left\lfloor\frac{n}{3}\right\rfloor$ 的两部分。

代码[在此](https://codeforces.com/problemset/submission/1205/304932928)。

---

## 作者：λᴉʍ (赞：6)


神仙题

首先选一个点作树根，只考虑经过根的路径

那么先考虑一个问题，在一个大小为$n$的子树中，让每个点到根的路径长度凑出$a,2a,\ldots,(n-1)a$

这个很好构造。先找出所有儿子，分别为$son_1,\ldots,son_m$，子树大小为$siz_1,\ldots,siz_m$。根到第$i$个儿子的边权是$(1+\sum_{j<i}siz_j)a$，然后对每个儿子递归下去做。

现在假设选了一个根节点$rt$，将儿子分为两组$A,B$，分别做上面的算法，其中$A$权值是$1,2,\ldots,siz_A$，$B$权值是$siz_A+1,2(siz_A+1),\ldots,siz_B(siz_A+1)$

那么从$A$到根节点到$B$的路径可以凑出来$1$到$(siz_A+1)(siz_B+1)-1$中所有数

考虑怎么将儿子分组，$(siz_A+1)(siz_B+1)-1$可以到达$\lfloor\frac{2n^2}{9}\rfloor$

显然两边尽量接近才能让结果更优

如果$siz_A,siz_B$都不小于$\lceil\frac{n-1}{3}\rceil$，那么最极端的情况就是$siz_A=\frac{n-1}{3}$，结果$\ge (\frac{n+2}{3})(\frac{2n+1}{3})-1=\frac{2n^2+5n-7}{9}$

需要的是$\frac{2n^2}{9}$。结果在$n>1$时正确，$n=1$无需考虑。

那么需要选一个根和划分让$siz_A,siz_B\geq \lceil\frac{n-1}{3}\rceil$

如果子树数量$\ge 4$，一定有两个子树大小之和$\le \frac n2$可以不断合并。

如果子树数量$\ge 3$，合并最小的两个子树，剩下那个大小一定$\geq\frac{n-1}{3}$，那么另一个大小也会$\leq 2\frac{n-1}{3}$。

子树数量为$1$只可能是$n=2$，无需考虑

合并完之后子树数量只可能为$2$，这时如果有一个子树大小$\ge \frac{2}{3}(n-1)$就不合法。

选重心做根，最大的子树大小小于等于$\frac{n}{2}$，就合法了。

https://codeforces.com/contest/1205/submission/59208736



---

## 作者：Alex_Wei (赞：4)

[CF1205D Almost All](https://www.luogu.com.cn/problem/CF1205D)

多个子树之间产生贡献不方便处理。注意到 $\dfrac 2 9$ 可以拆成 $\dfrac 1 3\times \dfrac 2 3$，且 $\dfrac 1 3 + \dfrac 2 3 = 1$，这启发我们将原树以某个点为中心分成两棵子树 $T_1, T_2$，设重合点为 $r$，则我们容易通过标边权使得 $T_1$ 每个点到 $r$ 的距离为 $0\sim |T_1| - 1$，$T_2$ 每个点到 $r$ 的距离为 $(0\sim |T_2| - 1) |T_1|$，做到使得距离 $1\sim |T_1||T_2| - 1$ 均出现。

将 $r$ 从 $|T_1|$ 和 $|T_2|$ 中去掉，则 $|T_1| + |T_2| = n - 1$。$|T_1|$ 和 $|T_2|$ 只需均不小于 $\dfrac {n - 1} 3$ 即可符合题目要求。

像这种子树大小相关的问题，可以从最有性质的重心入手。因为重心没有大小大于 $\dfrac n 2$ 的子树，所以若存在大小不小于 $\dfrac {n - 1} 3$ 的子树，则直接将其划分至 $T_1$，否则不断选子树直到大小不小于 $\dfrac {n - 1} 3$，则因所有子树大小均小于 $\dfrac {n - 1} 3$，所以最终 $|T_1| \leq \dfrac {2n - 3} 3$，故 $|T_2| \geq \dfrac {n - 1} 3$。[代码](https://codeforces.com/contest/1205/submission/182301441)。

---

## 作者：whiteqwq (赞：3)

[CF1205D Almost All](https://www.luogu.com.cn/problem/CF1205D) 解题报告：

[更好的阅读体验](https://www.cnblogs.com/xiaoziyao/p/15679743.html)

## 题意

给定一颗 $n$ 个点的树，构造树的边权使得对于 $x\in[1,\lfloor\frac{2n^2}{9}\rfloor]$ 都存在一条路径使得路径边权和为 $x$。

$1\leqslant n\leqslant 1000$。

## 分析

nb 题。

首先容易构造出一种基本操作：对于一颗 $n$ 个点的树，根到每个点的路径长度取遍 $1,2,3,\cdots,n-1$，只需要跑出 dfn 序然后边权等于相邻点 dfn 序之差即可。

考虑选择一个根，将儿子分成两个部分 A 和 B（大小分别为 $p,q$），A 部分使用上面的方法做出 $1,2,\cdots,p$ 的路径长度，B 部分做出 $1,2,\cdots,q$ 的路径长度，然后将所有边权乘 $(p+1)$，容易发现这样可以拼凑出 $(p+1)(q+1)-1$ 的所有长度。

那么我们要选择出一组比较均衡的 $p,q$ 满足 $(p+1)(q+1)-1\geqslant \lfloor\frac{2n^2}{9}\rfloor$。

考虑怎么让 $p,q$ 均衡：

首先选择重心为根，那么所有子树大小小于等于 $\lfloor\frac{n}{2}\rfloor$。

我们只需要将子树按照大小排序，选择一段前缀使得其恰好大于等于 $\lfloor\frac{n}{3}\rfloor$ 即可，容易发现这些子树的大小之和不超过 $2\lfloor\frac{n}{3}\rfloor$。

计算可得上述构造符合条件，于是直接做即可，时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=1005;
int n,p,ids,dfns;
int sz[maxn],val[maxn],id[maxn],ok[maxn],fa[maxn],dfn[maxn];
vector<int>v[maxn];
void dfs(int x,int last,int f){
	sz[x]=1;
	for(int i=0;i<v[x].size();i++)
		if(v[x][i]!=last)
			dfs(v[x][i],x,f),sz[x]+=sz[v[x][i]],val[x]=max(val[x],sz[v[x][i]]);
	val[x]=max(val[x],n-sz[x]);
	if(f==0&&(p==0||val[p]>val[x]))
		p=x;
}
inline int cmp(int a,int b){
	return sz[a]<sz[b];
}
void get(int x,int last,int val){
	fa[x]=last,dfn[x]=(++dfns)*val;
	for(int i=0;i<v[x].size();i++)
		if(v[x][i]!=last)
			get(v[x][i],x,val);
}
int main(){
	scanf("%d",&n); 
	for(int i=1,x,y;i<n;i++)
		scanf("%d%d",&x,&y),v[x].push_back(y),v[y].push_back(x);
	dfs(1,0,0),dfs(p,0,1);
	for(int i=0;i<v[p].size();i++)
		id[++ids]=v[p][i];
	sort(id+1,id+1+ids,cmp);
	int sum=0,k;
	for(int i=1;i<=ids;i++){
		ok[id[i]]=1,sum+=sz[id[i]],get(id[i],p,1);
		if(sum>=n/3){
			k=i;
			break;
		}
	}
	dfns=0;
	for(int i=k+1;i<=ids;i++)
		get(id[i],p,sum+1);
	for(int i=1;i<=n;i++)
		if(i!=p)
			printf("%d %d %d\n",i,fa[i],dfn[i]-dfn[fa[i]]);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

首先先考虑要求 $1\sim n-1$ 都出现在黑板上的构造。

显然可以将整个树 dfs 一遍，设每个数的 dfn 序为 $d_i$（从 $0$ 开始），只需要令每个位置到根的距离都为 $d_i$ 即可。这是容易做到的。

考虑这个做法的局限性在于端点只有一个。考虑取出一个中间点，左边到该点的距离为 $1\sim x$，右边到该点的距离为 $(x+1)\times 1\sim(x+1)\times y$，即可拼接出 $1\sim (x+1)(y+1)-1$ 的所有长度。也就是说，我们希望找到一种取中间点与钦定每个点属于左边还是右边的方案数，使得 $(x+1)(y+1)-1\geq\lfloor\frac{2n^2}{9}\rfloor$。

结论：重心至少有一个儿子的子集使得大小和在 $\frac{(n-1)}{3}\sim\frac{2(n-1)}{3}$ 之间。

证明：反证，假设不存在，设距离 $\frac{(n-1)}{3}$ 最近且小于 $\frac{(n-1)}{3}$ 的儿子的子集大小和为 $x$，那么显然重心不存在大小为 $1\sim \frac{(n-1)}{3}-x$ 额外子树，不存在大小为 $\frac{(n-1)}{3}-x\sim \frac{2(n-1)}{3}-x$ 额外子树，也不存在 $\frac{(n-1)}{3}\sim\frac{2(n-1)}{3}$ 额外子树，同时由重心性质也不存在 $\frac{(n-1)}{2}\sim (n-1)$ 额外子树，也就是说重心不存在任何其他额外子树，而重心的子树大小和为 $n-1$，显然大于 $\lfloor\frac{(n-1)}{3}\rfloor$（当然 $n=1$ 时根本不需要构造），于是假设不成立，原命题成立。

然后背包求一下方案即可。总复杂度 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> vc[1005];
int siz[1005],n,minv,rt;
void dfs(int now,int fa){
	siz[now]=1;
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
		siz[now]+=siz[v];
	}
}
int dp[1005],frm[1005],tag[1005],mul;
void findrt(int now,int fa){
	int maxv=0;
	for(auto v:vc[now]){
		if(v==fa) continue;
		findrt(v,now);
		maxv=max(maxv,siz[v]);
	}
	maxv=max(maxv,n-siz[now]);
	if(maxv<minv){
		minv=maxv,rt=now;
	}
}
void print(int now,int fa,int ntag){
	if(now==rt){
		int tmp=1;
		for(auto v:vc[now]){
			if(tag[v]==ntag){
				cout<<now<<" "<<v<<" "<<tmp*mul<<"\n";
				print(v,now,ntag);
				tmp+=siz[v];
			}
		}
		mul=tmp;
	}
	else{
		int tmp=1;
		for(auto v:vc[now]){
			if(v==fa) continue;
			cout<<now<<" "<<v<<" "<<tmp*mul<<"\n";
			print(v,now,ntag);
			tmp+=siz[v];
		}
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	dfs(1,0);
	minv=1e9;
	findrt(1,0);
	dfs(rt,0);
	memset(frm,-1,sizeof(frm));
	dp[0]=1;
	for(int i=0;i<vc[rt].size();i++){
		int v=vc[rt][i];
		for(int j=n-1;j>=siz[v];j--){
			if(dp[j-siz[v]]&&!dp[j]){
				dp[j]=1;
				frm[j]=i;
			}
		}
	}
	int st=0;
	for(int i=n/3;;i++){
		if(dp[i]){
			st=i;
			break;
		}
	}
	while(st){
		tag[vc[rt][frm[st]]]=1;
		st-=siz[vc[rt][frm[st]]];
	}
	mul=1;
	print(rt,0,1);
	print(rt,0,0);
	return 0;
}
```

---

## 作者：Zelotz (赞：0)

令 $ c $ 为树的重心。以 $ c $ 为根节点，令 $ s_1, s_2, \dots, s_k $ 成为其子节点的子树大小。由重心的性质， $ s_i \le \frac{n}{2}$ 。我们可以将子节点的子树分成两组，使得每组的大小至少为 $ \lceil \frac{n-1}{3} \rceil $ 。

证明：若至少有 $ 4 $ 棵子树，则其中一定存在两棵的顶点总数不超过 $ \frac{n}{2} $ 个，然后将它们合并。当剩下 $ 3 $ 棵子树时，我们令 $a, b, c$ 为 $3$ 棵子树的大小，有 $a\le b\le c, a+b+c=n-1$， 将两棵较小的子树 $a,b$ 合并为一组，不难发现 $a+b=n-c-1 \ge n-1-\frac{n}{2} \ge \lceil \frac{n-1}{3} \rceil$，$c\ge \lceil \frac{n-1}{3} \rceil$。

（实际上，我们将 $s$ 排序后，选取一段前缀直到 $sum\ge \lceil \frac{n-1}{3} \rceil$ 即可。）

令第一组有 $A$ 个顶点，第二组有 $ B$ 个顶点。们将数字放在 $A$ 中以及 $ c $ 和 $A$ 之间的边上，使 $ c $ 到第一组顶点的距离为 $ 1, 2, \dots, A $ 。类似地，我们使从 $ c $ 到第二组顶点的距离等于 $ (A + 1), 2 (A + 1), \dots, B (A + 1) $ 。显然从 $ 1 $ 到 $ (A + 1) (B + 1) -1 $ 的每个数字都可以作为第一组中某个顶点与第二组中某个顶点之间的距离。接下来只需证明 $ (A + 1) (B + 1) -1 \ge \frac {2n ^ 2} {9} $ 。

证明：$f(A)=(A+1)(B+1)-1=(A+1)(n-A)-1=-A^2+(n-1)A+n-1$ 是一个关于 $A$ 的开口向下的二次函数，在定义域内最小值在 $\frac{n-1}{3}$ 取得，此时 $f(A)=(\frac{n + 2 }{3}) (\frac{2n + 1}{3}) - 1 = \frac{2n ^ 2 + 5n + 3}{9} - 1 \ge \frac{2n ^ 2}{9}$。

```
const int N = 1e6 + 5;
int n, rt, sz[N];
vector <int> E[N];
void init(int x, int fa) {
    sz[x] = 1; int mx = 0;
    for (int v : E[x]) {
        if (v == fa) continue;
        init(v, x);
        sz[x] += sz[v];
        mx = max(mx, sz[v]);
    }
    mx = max(mx, n - sz[x]);
    if (mx * 2 <= n) rt = x;
}
int dfn[N], lst, tot, val;
void dfs(int x, int fa) {
    sz[x] = 1; 
    for (int v : E[x]) {
        if (v == fa) continue;
        dfs(v, x);
        sz[x] += sz[v];
    }
}
vector <tuple <int, int, int> > ans;
void dfs2(int x, int fa) {
    dfn[x] = ++tot;
    ans.push_back({fa, x, (dfn[x] - dfn[fa]) * val});
    for (int v : E[x]) {
        if (v == fa) continue;
        dfs2(v, x);
    }
}
signed main() {
    cin >> n; if (n == 1) return 0;
    R(i, 1, n - 1) {
        int u, v; cin >> u >> v;
        E[u].push_back(v), E[v].push_back(u);
    }
    init(1, 0); dfs(rt, 0);
    sort(E[rt].begin(), E[rt].end(), [&](int x, int y) {return sz[x] < sz[y];});
    int sum = 0; int lim = ceil((n - 1) * 1.0 / 3); int pos;
    for (int i = 0; i < E[rt].size(); ++i) {
        int v = E[rt][i];
        sum += sz[v];
        if (sum >= lim) {pos = i; break;}
    }
    val = 1;
    for (int i = 0; i <= pos; ++i) dfs2(E[rt][i], rt); val = sum + 1; tot = 0;
    for (int i = pos + 1; i < E[rt].size(); ++i) dfs2(E[rt][i], rt);
    for (auto t : ans) cout << get<0>(t) << ' ' << get<1>(t) << ' ' << get<2>(t) << '\n';
    return 0;
}
```

---

## 作者：_ANIG_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1205D)

直接构造不太容易，从特殊情况入手。

首先考虑菊花图的情况。

此时，问题转化为构造出尽量少的数，使得 $1$ 到 $m$ 的每个数都能由这些数的某一个或某两个相加得到。

这个问题就比较好解决，可以构造：

$$\{\sqrt m,2\sqrt m,\dots,m,1,2,3,\dots,\sqrt m-1\}$$

数的数量是 $\sqrt m$ 数量级。

然后考虑链的情况。

相当于构造出尽量短的序列，使得 $1$ 到 $m$ 的每个数都能由一个区间相加得到。

菊花图的情况提示我们可以接着利用根号构造。

于是我们可以前一半全是 $\sqrt m$，后一半全是 $1$，这样每个数都能由一个过中点的区间的和表示。

考虑扩展到一般情况。

上述情况启发我们分别构造 $1$ 到 $\sqrt m$ 和 $\sqrt m$ 的所有倍数，并且这两条路径的端点相交。

假设我们已经确定了它们的交点。

以交点为根，相当于找到两个位于根的不同儿子的子树内的点，深度恰好分别为给定的两个值。

要想凑出 $1$ 到 $m$ 的所有数，可以考虑把根的所有儿子分为两个集合，使得每个集合对应的子树的所有点的深度能包含 $1$ 到 $\sqrt m$ 的所有数。

可以发现，让第一个儿子边权为 $1$，然后让这个子树凑出 $1-siz$ 的所有数，再让第二个儿子边权为 $siz+1$，以此类推，我们就能得到 $1$ 到 $\sum siz$ 的所有数。

由于题目中 $m=\frac{2n^2}9$，所以 $\sqrt m=\frac{\sqrt 2n}3$。

也就是我们找一个点，把这个点删掉后整棵树分成若干个连通块。

把这些连通块分成 $2$ 个集合，使得每个集合的连通块大小之和不小于 $\frac{\sqrt 2n}3$。

但是这样是不一定有解的。

可以发现，阈值不一定要取到 $\sqrt m$。

分成的两个集合只需要大小相乘不小于 $m$ 即可。

题目给的分数也提示我们可以拆分成 $\frac 13n\times \frac 23 n$。

也就是让两个集合大小之和都在 $[\frac13n,\frac23n]$ 之间。

对于这种问题，不难猜测可以取重心。

取重心可以使得每个子树大小不超过 $\frac n2$。

不妨贪心直接取。

一个一个子树加入，直到大于 $\frac13 n$。

如果加入最后一个子树后集合大小之和不超过 $\frac23 n$，则已经合法。

否则不取最后一个子树，取剩余的所有子树，这样调整过后的大小恰好在 $[\frac 13n,\frac 23n]$ 之间。

总复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1005;
int n,siz[N],zd[N],mk[N],zx,bk[N],k,fa[N];
vector<int>p[N];
void dfs(int x){
	mk[x]=1;siz[x]=1;
	for(auto c:p[x]){
		if(mk[c])continue;
		dfs(c);
		siz[x]+=siz[c];
		zd[x]=max(zd[x],siz[c]);
	}
	zd[x]=max(zd[x],n-siz[x]);
	if(zd[x]<zd[zx]||!zx)zx=x;
	mk[x]=0;
}
void solve(int x){
	mk[x]=1;siz[x]=1;
	for(auto c:p[x]){
		if(mk[c])continue;
		solve(c);
		fa[c]=x;
		siz[x]+=siz[c];
	}
	mk[x]=0;
}
void solve1(int x,int l,int r){
	cout<<x<<" "<<fa[x]<<" "<<l<<"\n";
	r-=l;
	l=1;
	for(auto c:p[x]){
		if(c==fa[x])continue;
		solve1(c,l,l+siz[c]-1);
		l+=siz[c];
	}
}
void solve2(int x,int l,int r){
	cout<<x<<" "<<fa[x]<<" "<<l*k<<"\n";
	r-=l;
	l=1;
	for(auto c:p[x]){
		if(c==fa[x])continue;
		solve2(c,l,l+siz[c]-1);
		l+=siz[c];
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		p[x].push_back(y);
		p[y].push_back(x);
	}
	dfs(1);
	solve(zx);
	int m=n/3;
	for(int i=0;i<p[zx].size();i++){
		int c=p[zx][i];
		if(k+siz[c]>m){
			if(k+siz[c]>2*m){
				for(int j=i+1;j<p[zx].size();j++)bk[p[zx][j]]=1,k+=siz[p[zx][j]];
				break;
			}
			bk[c]=1;
			k+=siz[c];
			break;
		}
		bk[c]=1;
		k+=siz[c];
	}
	int nw=1,nt=1;
	for(auto c:p[zx]){
		if(bk[c]){
			solve1(c,nw,nw+siz[c]-1);
			nw+=siz[c];
		}else{
			solve2(c,nt,nt+siz[c]-1);
			nt+=siz[c];
		}
	}
}
```

---

