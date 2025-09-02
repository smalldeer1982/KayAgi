# 「DBOI」Round 1 人生如树

## 题目背景

> _永远这么酷 永远永远这么酷_\
_像个冒险家一样 不断探着山顶的路_\
——《Hustle》

张均好望着窗外，朱芝心走过来坐在他旁边，折了一架纸飞机飞出去。他对张均好说，要带着对未来的期待，往前走，别回头。

正如 [命运](https://www.luogu.com.cn/problem/P6773) 所述，每个人的人生都是一棵树。它总在无限的随机与缘分中伸展，有的枝丫茂盛了，有些却也不可避免地枯萎。

## 题目描述

朱芝心用魔法得到了张均好的人生树。

这是一棵 $n$ 个节点的树，节点 $i$ 上有权值 $w_i$。

朱芝心想要观测 $m$ 次张均好的人生：

设**当前**张均好人生树上的节点数量为 $s$。

1. 输入四个整数 $u_1,v_1,u_2,v_2$。令 $u_1\to v_1$ 的简单路径上**顺次组成**的数组为 $a$，$u_2\to v_2$ 的简单路径上**顺次组成**的数组为 $b$。朱芝心认为张均好这两段人生的相似度是 $LRP(a,b)$，希望你求出它。保证 $1\leq u_1,v_1,u_2,v_2 \leq s$。

2. 输入两个整数 $u,w'$。朱芝心观测到了张均好的另外一种可能，因此你需要新建一个点权为 $w'$ 的节点，编号为 $s+1$，建立一条 $(s+1,u)$ 的无向边，其中 $u\leq s$。显然，此后 $s\leftarrow s+1$。

对于两个数组 $a,b$，设它们的相似度 $LRP(a,b)$ 表示最大的 $i$ 满足 $i\leq \min\{|a|, |b|\}$ 且**对于所有** $1\leq j\leq i$，都有 $b_j=a_j+j$。其中 $|a|$ 表示数组 $a$ 的长度。特殊地，若不存在这样的 $i$，则 $LRP(a,b) = 0$。


## 说明/提示

### 样例解释

对于样例一，第一个操作结束后，$w_{10}=10$，树如图所示：

![](https://s1.ax1x.com/2023/04/26/p9MV9pV.png)

- 对于第二个操作，第一条路径为 $3\to 2\to 4\to 5$，故 $a=\{2, 3, 4, 6\}$，第二条路径为 $8\to 7\to 9\to 10$，故 $b=\{3, 5, 7, 10\}$，由于 $3=2+1$，$5=3+2$，$7=4+3$，$10=6+4$，所以答案为 $4$；
- 对于第三个操作，$a=\{2, 3, 4, 5\}$，$b=\{3, 5, 7, 10\}$，由于 $3=2+1$，$5=3+2$，$7=4+3$，$10\ne 5+4$，所以答案为 $3$。

对于样例二，初始的树如图所示：

![](https://s1.ax1x.com/2023/04/26/p9MVZkR.png)


| Subtask | $n \le$ | $m \le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| Subtask 1 | $5000$ | $5000$ | 无 | $10$ |
| Subtask 2 | $10^5$ | $5\times{10}^4$ | A & B | $30$ |
| Subtask 3 | $10^5$ | $5\times{10}^4$ | B | $30$ |
| Subtask 4 | $10^5$ | $5 \times {10}^4$ | 无 | $20$ | 
| Subtask 5 | $10^5$ | $10^5$ | 无 | $10$ |

特殊性质 A：$v_i=u_i+1$。

特殊性质 B：保证无操作 2。

对于 $100\%$ 的数据，$1\leq n,m\leq 10^5$，$1\leq w_i,w'\leq 10^6$，$1\leq u_i,v_i\leq n$。  


## 样例 #1

### 输入

```
9 3 0
7 3 2 4 6 5 5 3 7
1 2
2 3
2 4
4 5
4 6
1 7
7 8
7 9
2 9 10
1 3 5 8 10
1 3 6 8 10```

### 输出

```
4
3```

## 样例 #2

### 输入

```
13 5 0
15 12 9 11 5 6 16 14 15 10 12 1 2
7 8
5 6
2 9
1 2
4 5
8 2
9 10
2 3
10 11
3 4
3 13
3 12
1 1 6 7 11
1 12 12 13 13
2 1 10
2 2 11
1 14 14 15 15```

### 输出

```
6
1
1```

# 题解

## 作者：Hoks (赞：4)

## 前言
双倍经验：[Misha and LCP on Tree](https://www.luogu.com.cn/problem/CF504E)，但是要和我同个做法才能过。

这篇题解使用的是树剖做法，时间复杂度为 $O(n+m\log n)$。

该题解思路鸣谢 lzyqwq，感谢他点醒了我成功拿下最优解。

同时这题是我树剖 part $2$ 中的一道练习题，详情文章可见：[『从入门到入土』树链剖分学习笔记](https://www.luogu.com.cn/blog/Hok/cute-tree-decomposition)。
## 思路分析
题意：
- 给定一颗树，每个点有点权。

- 操作一：查询 $u\rightarrow v$ 的路径上依次的点权减去 $x\rightarrow y$ 的路径上依次的点权形成的 $1,2,3,\dots,n$ 这种等差数列的最大长度。

- 操作二：新加 $n+1$，与 $u$ 连边，点权为 $x$。 

显然的是可以直接一眼秒：

考虑先第一步转化，查询时加点不方便，因为新加的点不会对前面的查询有影响，所以离线下询问先给点加上就行了。

接着考虑处理查询，如果被限死在序列中的话复杂度就会难免带上一个序列长度 $len$。

所以考虑一种能把序列转化为一个值的东西：Hash！

Hash 之后直接处理也是难绷的复杂度，所以我们考虑二分答案。

这样的话我们只需要考虑如何快速求出 $u$ 向上/下 $k$ 步的 Hash 值就行了。

考虑使用倍增，处理出 $2^j$ 步向上/下的 Hash 值。

接着查询的时候二分答案使用倍增算出 Hash 值比一下是否相同 check 即可。

------------

这样我们就完成了倍增做法，欸那这题和树剖有什么关系啊？

想完了倍增做法后，我果断打开了题解发现没有一个重剖做法，所以我考虑重剖如何做。

最初，受到了出题人题解中说可以用**长剖树上 $k$ 级祖先**的方法来处理 Hash 值的启发，考虑用重剖实现**树上 $k$ 级祖先**，来代替掉倍增求 Hash 的过程。

仔细一分析，这个复杂度好像不是很优，是 $O(n\log^3n)$。

------------

接下去神犇 lzyqwq 给了我点启发，他看了一眼后说，不就是 CF226E 吗？

受此启发，我们考虑利用重剖的特性。

比起倍增把路径分为了 $2^j$ 长度的链，重剖的特性就是把路径划分为了一条条重链。

那我们考虑直接把 $u$ 开始往上跳的那条重链拿出来，再把 $x$ 开始往上跳的重链也拿出来。

那我们就能把这两段重链直接相消。

如果不匹配呢？

那直接上大力二分即可。

具体写的时候推荐把每条链的转折点 $topf$ 记录进一个 vector 中。

原因是**可能两段重链长度不同，所以只能消掉其中的一段，另一段要从已经被消掉的头开始继续往上匹配**。

也就是我们用 vector 的话，假设原本没被消光的这个点为 $x$，上段重链的链顶为 $topf$，那我们这次消完了后就是去掉这个 $topf$，再压入这个 $x$ 就做完了。

因为害怕 Hash 被卡，所以在此推荐两个大模数：$1004535809,167772161$。（来源：mrsrz 的代码。）

这两个模数的强度很高，所以我用单 Hash 轻松通过了此题并且拿下最优解。

时间复杂度：$O(n+m\log n)$ 常数最劣情况下约为 $3$，均摊一下的话常数还是很小的。
## 代码
代码有些冗长，见谅。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
const int N=200010,mod=167772161,INF=0x3f3f3f3f3f3f3f3f;
const int p=13331;
struct edge
{int v,nxt;}e[N<<1];
struct node
{int u,v,x,y;}q[N];
int n,m,tot,cnt;
int s[N],op[N],h1[N],h2[N],h3[N];
int top[N],id[N],dfn[N],head[N];
int fa[N],dep[N],si[N],son[N];
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
int read()
{
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
void print(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
void add(int u,int v){e[++tot].v=v,e[tot].nxt=head[u],head[u]=tot;}
void dfs1(int u,int ff)
{
	fa[u]=ff;dep[u]=dep[ff]+1,si[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==ff) continue;
		dfs1(v,u),si[u]+=si[v];
		if(si[v]>si[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int topf)
{
	top[u]=topf,dfn[u]=++cnt,id[cnt]=u;
	if(son[u]) dfs2(son[u],topf);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
vector<pair<int,int> > get(int x,int y)
{
	vector<pair<int,int> >l,r;
	while(top[x]!=top[y])
		if(dep[top[x]]<dep[top[y]]) r.pb(mp(top[y],y)),y=fa[top[y]];
		else l.pb(mp(x,top[x])),x=fa[top[x]];
	int lca=dep[x]<dep[y]?x:y;l.pb(mp(x,lca));
	if(y!=lca) r.pb(mp(son[lca],y));
	while(r.size()) l.pb(r.back()),r.pop_back();
	return l;
}
int h(bool opt,int x,int k)
{
	if(opt) return (h2[x-k+1]-h2[x+1]*op[k]%mod+mod)%mod;
	return (h1[x+k-1]-h1[x-1]*op[k]%mod+mod)%mod;
}
int gt(int l,int r){return (h3[r]-h3[l-1]*op[r-l+1]%mod+mod)%mod;}
signed main()
{
	n=read();m=read();read();for(int i=1;i<=n;i++) s[i]=read();op[0]=1;
	for(int i=1,u,v;i<n;i++) u=read(),v=read(),add(u,v),add(v,u);
	for(int i=1,opt,x,y;i<=m;i++)
	{
		opt=read();
		if(opt==2) x=read(),add(x,++n),add(n,x),s[n]=read();
		else q[i].u=read(),q[i].v=read(),q[i].x=read(),q[i].y=read();
	}
	dfs1(1,0),dfs2(1,1);
	for(int i=1;i<=n;i++) 
		h1[i]=(h1[i-1]*p+s[id[i]])%mod,h2[n+1-i]=(h2[n+2-i]*p+s[id[n+1-i]])%mod,
		op[i]=op[i-1]*p%mod,h3[i]=(h3[i-1]*p+i)%mod;
	for(int i=1,a,b,c,d,ans,s,t;i<=m;i++)
	{
		if(!q[i].u) continue;
		a=q[i].u,b=q[i].v,c=q[i].x,d=q[i].y;s=t=ans=0;
		vector<pair<int,int> > f=get(a,b),g=get(c,d);
		while(s<(int)f.size()&&t<(int)g.size())
		{
			int d11=dfn[f[s].fi],d12=dfn[f[s].se],d21=dfn[g[t].fi],d22=dfn[g[t].se];
			bool opf=d11>d12,opt=d21>d22;
			int lf=(opf?d11-d12:d12-d11)+1,lt=(opt?d21-d22:d22-d21)+1,len=min(lf,lt);
			int hf=h(opf,d11,len),hg=h(opt,d21,len),hsh=gt(ans+1,ans+len);
			if((hf+hsh)%mod==hg)
			{
				if(len==lf) s++;
				else f[s].fi=id[d11+(opf?-1:1)*len];
				if (len==lt) t++;
				else g[t].fi=id[d21+(opt?-1:1)*len];
				ans+=len;
			}
			else
			{
				int l=1,r=len;
				while(l<r)
				{
					hf=h(opf,d11,mid),hg=h(opt,d21,mid),hsh=gt(ans+1,ans+mid);
					if((hf+hsh)%mod==hg) l=mid+1;
					else r=mid;
				}
				ans+=l-1;break;
			}
		}
		print(ans);puts("");
	}
	return 0;
}
```


---

## 作者：wxzzzz (赞：4)

### 思路

二分答案，哈希判断是否合法。

需要快速判断对于一个二分的长度 $mid$，是否满足 $\operatorname{hash}(\{a_i+i\})=\operatorname{hash}(\{b_i\})$ 是否成立。

可以维护几个东西：

- $f_{i,j}$ 表示 $i$ 的 $2^j$ 倍祖先，倍增 LCA 板子。

- $hs_{i,j}$ 表示 $i$ 到 $f_{i,j}$ 路径的哈希值（从下往上），有：

$$hs_{i,j}=hs_{i,j-1}\times P^{2^{j-1}}+hs_{f_{i,j-1},j-1}$$


- $rs_i$ 表示从跟到节点 $i$ 路径的哈希值（从上往下），有：

$$rs_i=rs_{f_{i,0}}\times P+w_i$$

- $adds_i$ 表示 $|a|=i$ 时 $\operatorname{hash}(\{a_j+j\})-\operatorname{hash}(\{a_j\})$，有：

$$adds_{i-1}+P^{i-1}\times i$$

然后 $\operatorname{hash}(\{a_i+i\})$ 就可转化为 $\operatorname{hash}(\{a_i\})+adds_{mid}$，可以快速计算。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, t, sub, idx, w[500005], d[500005], v[500005], h[500005], ne[500005], f[500005][25];
unsigned long long p[500005], rs[500005], adds[500005], hs[500005][25];
queue<int> q;
void add(int x, int y) {
    v[++idx] = y, ne[idx] = h[x], h[x] = idx;
}
void bfs() {
    q.push(1), d[1] = 1;
    hs[1][0] = rs[1] = w[1];

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        d[x] = d[f[x][0]] + 1;
        rs[x] = rs[f[x][0]] * 131 + w[x];

        for (int i = 1; i <= t; i++) {
            f[x][i] = f[f[x][i - 1]][i - 1];
            hs[x][i] = hs[x][i - 1] * p[1 << i - 1] + hs[f[x][i - 1]][i - 1];
        }

        for (int i = h[x]; ~i; i = ne[i]) {
            int y = v[i];

            if (y != f[x][0])
                f[y][0] = x, q.push(y);
        }
    }
}
int LCA(int x, int y) {
    if (d[x] > d[y])
        swap(x, y);

    for (int i = t; i >= 0; i--)
        if (d[f[y][i]] >= d[x])
            y = f[y][i];

    if (x == y)
        return x;

    for (int i = t; i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];

    return f[x][0];
}
int getup(int x, int k) {
    int to = d[x] - k;

    for (int i = t; i >= 0; i--)
        if (d[f[x][i]] >= to)
            x = f[x][i];

    return x;
}
unsigned long long uphash(int x, int k) {
    unsigned long long ret = 0, to = d[x] - k;

    for (int i = t; i >= 0; i--) {
        if (d[f[x][i]] >= to) {
            ret = ret * p[1 << i] + hs[x][i];
            x = f[x][i];
        }
    }

    return ret;
}
unsigned long long roadhash(int x, int y) {
    return rs[x] - rs[f[y][0]] * p[d[x] - d[f[y][0]]];
}
unsigned long long gethash(int x, int y, int lca, int len) {
    unsigned long long ret, dep = d[x] - d[lca] + 1;

    if (len <= dep)
        return roadhash(x, getup(x, len - 1));

    len -= dep;
    ret = roadhash(x, lca);
    y = getup(y, d[y] - d[lca] - len);
    ret = ret + p[dep] * uphash(y, len);
    return ret;
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m >> sub;
    t = log(n) / log(2), p[0] = 1;

    for (int i = 1; i <= n; i++)
        cin >> w[i], hs[i][0] = w[i];

    for (int i = 1; i <= n + m; i++)
        p[i] = p[i - 1] * 131, adds[i] = adds[i - 1] + p[i - 1] * i;

    for (int i = 1, x, y; i < n; i++) {
        cin >> x >> y;
        add(x, y), add(y, x);
    }

    bfs();

    while (m--) {
        int op;
        cin >> op;

        if (op == 1) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            int lca1 = LCA(x1, y1), lca2 = LCA(x2, y2);
            int l = 1, r = min(d[x1] + d[y1] - d[lca1] - d[f[lca1][0]], d[x2] + d[y2] - d[lca2] - d[f[lca2][0]]), mid,
                ans = 0;

            while (l <= r) {
                mid = l + r >> 1;

                if ((unsigned long long)(gethash(x1, y1, lca1, mid) + adds[mid]) == gethash(x2, y2, lca2, mid))
                    ans = mid, l = mid + 1;
                else
                    r = mid - 1;
            }

            cout << ans << '\n';
        } else {
            int x, wn;
            cin >> x >> wn;
            n++, t = log(n) / log(2);
            add(x, n), f[n][0] = x;
            d[n] = d[x] + 1;
            hs[n][0] = w[n] = wn;
            rs[n] = rs[x] * 131 + w[n];

            for (int i = 1; i <= t; i++) {
                f[n][i] = f[f[n][i - 1]][i - 1];
                hs[n][i] = hs[n][i - 1] * p[1 << i - 1] + hs[f[n][i - 1]][i - 1];
            }
        }
    }

    return 0;
}
```

---

## 作者：StayAlone (赞：4)

出题人题解。

板题典题诈骗题。

### Subtask 1

你甚至不需要知道如何快速求 LCA。对于操作 1，存下来数组 $a,b$，从左往右扫到第一个不合法的位置即可；对于操作 2，直接连边。时间复杂度 $\mathcal O(nm)$。

### Subtask 2

这个性质保证图是一条链，且作为良心出题人，其编号就是顺次的 $1\sim n$。因此这个问题被转换为了在序列上。

容易注意到，$LRP$ 有单调性，可以二分答案。考虑哈希维护序列。

定义哈希数组 $h_i=h_{i-1}\times p + w_i$。其中 $p$ 是一个值域加 $n+m$ 以上的数。你可以理解为把数组压成一个 $p$ 进制数 $h_n$，由于 $w_i\leq 10^6$，再加上轮转前缀的常数一定在 $n+m$ 以内，所以这样可以保证取模前不会出现哈希值的冲突。

设 $h_a,h_b$ 分别是 $a$ 的哈希数组和 $b$ 的哈希数组。

若当前二分的长度为 $x$，我们需要判断 $[u_1,u_1+x-1]$ 和 $[u_2,u_2+x-1]$ 是否满足最长轮转前缀的限制。

当前长度合法，当且仅当 $h_{a_x}+\sum_{i=1}^x i\times p^{x-i}=h_{b_{x}}$。

例如：  
$$
\begin{aligned}
&a=\{1, 1, 4, 5, 1, 4\}\\
&b=\{(1+1),(1+2),(4+3),(5+4),(1+5),(4+6)\}
\end{aligned}
$$

显然 $h_{b_x} -h_{a_x}=1\times p^5+2\times p^4 + 3\times p^3 + 4\times p^2 + 5\times p^1 +6\times p^0$。

发现这个偏移量可以通过两次前缀和预处理，即：

设 $sum_i\leftarrow p^i$。

累 $sum$ 的前缀和，$sum_i\leftarrow sum_{i-1}+p^i$，此时 $sum_i=\sum_{k=0}^i p^k$。

再累 $sum$ 的前缀和，$sum_i\leftarrow sum_{i-1}+sum_i$，此时 $sum_i=\sum_{k=0}^i (k+1)\times p^{i-k}=\sum_{k=1}^{i+1} k\times p^{i+1-k}$。那么 $sum_{x-1}=\sum_{i=1}^{x} i\times p^{x-i}$。

注意在链上的询问中，$v>u$ 有可能出现，所以还需要倒着处理一个哈希数组出来。

总结一下思路：预处理前缀和及哈希数组，二分答案，对于每个长度哈希判断。时间复杂度 $\mathcal O(m\log n)$。

### Subtask 3

与 Subtask 2 不同的是，我们需要在树上快速获得哈希值。

首先要预处理倍增数组 $f_{i,j}$ 表示节点 $i$ 的 $2^j$ 级祖先。二分出长度后，可以使用这个数组跳到该路径上距离左端 $x$ 的点。然后你可能会写树剖，时间复杂度 $\mathcal O(m\log^3 n)$，空间复杂度 $\mathcal O(n)$，可以通过。

~~但是这很蠢。~~ 静态同样可以预处理出倍增的哈希数组。需要两个：一个是从 $i$ 开始往上 $2^j$ 个点的哈希值，一个是 $i$ 开始往上第 $2^j$ 个点到它的哈希值（也就是一个从深向浅，一个由浅至深）。两者都可以合并，因此在跳的过程中合并哈希值即可。时间复杂度 $\mathcal O(m\log^2 (n+m))$，空间复杂度 $\mathcal O((n+m)\log (n+m))$。

### Subtask 4、Subtask 5

~~有一个从开始到现在都没用到的显然性质，大家应该都看出来了。~~

显然可以先读入所有操作，先进行所有操作 2，再处理操作 1 不影响答案。

如果你写了树剖，应该可以通过吧（

--------------

赛后发现更简单的写法，常数、空间减小，而且配合长链剖分查询树上 $k$ 级祖先即可做到 $\mathcal O((n+m)\log(n+m))$。

只需要用类似树上前缀和的方法预处理 $1\sim x$ 的哈希值和 $x\sim 1$ 的前缀和即可。

下面的代码第一份是赛前的 std，第二份是赛后的，没写长链剖分。

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (int i = l; i <= int(r); ++i)
#define rep2(i, l, r) for (int i = l; i >= int(r); --i)
#define cop(i, l, r, a, b) rep1(i, l, r) a[i] = b[i]
#define rep(i, x) for (int i = pnt[x]; i; i = nxt[i])
#define rer(i, l, r, a) rep1(i, l, r) read(a[i])
#define ptc putchar
#define il inline
#define eb emplace_back
#define ef emplace_front
#define mp make_pair
#define fst first
#define snd second
#define sqr(x) ((x) * (x))
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define YES ptc('Y'), ptc('E'), ptc('S'), ptc('\n')
#define Yes ptc('Y'), ptc('e'), ptc('s'), ptc('\n')
#define NO ptc('N'), ptc('O'), ptc('\n')
#define No ptc('N'), ptc('o'), ptc('\n')
#define rout return 0
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
// typedef __int128 bll;
// typedef unsigned __int128 ubll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = 2e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
const int LOGN = log2(MAXN) + 1;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
namespace stupid_lrc {
	template <typename T> il bool read(T &x) {
		x = 0; bool f = false; char ch;
		while (!isdigit(ch = getchar())) {
			f ^= !(ch ^ '-');
			if (ch == EOF) return false;
		}
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = getchar();
		if (f) x = ~x + 1; return true;
	}
	il int read() {int x; read(x); return x;}

	template <typename T> il bool read(pair <T, T> &x) {return read(x.fst) && read(x.snd);}

	template <typename T, typename ...L>
	il bool read(T &x, L &...y) {return read(x) && read(y...);}

	template <typename T> il T lowbit(const T &x) {return x & -x;}
}
using namespace stupid_lrc;
const int mod = 114514003, base = 432842357;
int n, m, idx, d[MAXN], lg[MAXN], f[MAXN][LOGN + 5], w[MAXN]; vector <int> lnk[MAXN];
ll has[2][MAXN][LOGN + 5], pw[MAXN], sum[MAXN];

il void add(const int &x, const int &y) {
	lnk[x].eb(y); lnk[y].eb(x);
}

struct query {
	int u1, v1, u2, v2;
}; vector <query> pr;

il void dfs(int x, int p) {
	f[x][0] = p; d[x] = d[p] + 1;
	has[0][x][0] = has[1][x][0] = w[x];
	for (auto v : lnk[x]) if (v ^ p) dfs(v, x);
}

il int lca(int u, int v) {
	if (d[u] < d[v]) swap(u, v);
	rep2(i, lg[n], 0) if (d[u] - d[v] >= 1 << i) u = f[u][i];
	if (u == v) return u;
	rep2(i, lg[n], 0) if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
	return f[u][0];
}

int u, v, u2, v2, tp1, tp2;

il ull getval(int u, int v, int dis, int top) {
	ull ans = 0;
	rep2(i, lg[n], 0) if (d[u] - (1 << i) >= 0 && dis >= (1 << i) && d[f[u][i]] + 1 >= d[top]) {
		(ans = ans * pw[1 << i] % mod + has[0][u][i]) %= mod;
		u = f[u][i], dis -= 1 << i;
	}
	if (dis) {
		rep2(i, lg[n], 0) if (d[v] - d[top] - dis >= (1 << i)) v = f[v][i];
		vector <pll> uni;
		rep2(i, lg[n], 0) if (d[v] - (1 << i) >= 0 && d[f[v][i]] >= d[top]) {
			uni.emplace_back(has[1][v][i], 1 << i);
			v = f[v][i];
		} reverse(uni.begin(), uni.end());
		for (auto p : uni) (ans = ans * pw[p.snd] % mod + p.fst) %= mod;
	} return ans;
}

il bool check(int x) {
	if ((getval(u, v, x, tp1) + sum[x - 1]) % mod != getval(u2, v2, x, tp2)) return false;
	return true;
}

int main() {
	read(n, m, idx); rer(i, 1, n, w);
	rep1(i, 2, n) add(read(), read());
	while (m--) {
		int op, u, v, u2, v2;
		read(op, u, v);
		if (op == 1) read(u2, v2), pr.eb(query{u, v, u2, v2});
		else ++n, add(n, u), w[n] = v;
	}
	rep1(i, 2, n) lg[i] = lg[i >> 1] + 1;
	sum[0] = pw[0] = 1;
	rep1(j, 1, n) sum[j] = pw[j] = pw[j - 1] * base % mod;
	
	rep1(j, 1, n) (sum[j] += sum[j - 1]) %= mod;
	rep1(j, 1, n) (sum[j] += sum[j - 1]) %= mod;
	dfs(1, 0);
	
	rep1(j, 1, lg[n]) rep1(i, 1, n) {
		f[i][j] = f[f[i][j - 1]][j - 1];
		(has[0][i][j] = has[0][f[i][j - 1]][j - 1] + has[0][i][j - 1] * pw[1 << j - 1] % mod) %= mod;
		(has[1][i][j] = has[1][f[i][j - 1]][j - 1] * pw[1 << j - 1] % mod + has[1][i][j - 1]) %= mod;
	}
	for (auto p : pr) {
		u = p.u1, v = p.v1, u2 = p.u2, v2 = p.v2;
		tie(tp1, tp2) = mp(lca(u, v), lca(u2, v2));
		int l = 0, r = min(d[u] - d[tp1] + d[v] - d[tp1] + 1, d[u2] - d[tp2] + d[v2] - d[tp2] + 1);
		while (l ^ r) {
			int mid = l + r + 1 >> 1;
			if (check(mid)) l = mid;
			else r = mid - 1;
		} printf("%d\n", l);
	}
	rout;
}
```

```cpp
#include <bits/stdc++.h>
#define rep1(i, l, r) for (int i = l; i <= int(r); ++i)
#define rep2(i, l, r) for (int i = l; i >= int(r); --i)
#define cop(i, l, r, a, b) rep1(i, l, r) a[i] = b[i]
#define rep(i, x) for (int i = pnt[x]; i; i = nxt[i])
#define rer(i, l, r, a) rep1(i, l, r) read(a[i])
#define ptc putchar
#define il inline
#define eb emplace_back
#define ef emplace_front
#define mp make_pair
#define fst first
#define snd second
#define sqr(x) ((x) * (x))
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define YES ptc('Y'), ptc('E'), ptc('S'), ptc('\n')
#define Yes ptc('Y'), ptc('e'), ptc('s'), ptc('\n')
#define NO ptc('N'), ptc('O'), ptc('\n')
#define No ptc('N'), ptc('o'), ptc('\n')
#define rout return 0
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
// typedef __int128 bll;
// typedef unsigned __int128 ubll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = 2e5 + 10, inf = ~0U >> 2, INF = ~0U >> 1;
const int LOGN = log2(MAXN) + 1;
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
namespace stupid_lrc {
	template <typename T> il bool read(T &x) {
		x = 0; bool f = false; char ch;
		while (!isdigit(ch = getchar())) {
			f ^= !(ch ^ '-');
			if (ch == EOF) return false;
		}
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = getchar();
		if (f) x = ~x + 1; return true;
	}
	il int read() {int x; read(x); return x;}

	template <typename T> il bool read(pair <T, T> &x) {return read(x.fst) && read(x.snd);}

	template <typename T, typename ...L>
	il bool read(T &x, L &...y) {return read(x) && read(y...);}

	template <typename T> il T lowbit(const T &x) {return x & -x;}
}
using namespace stupid_lrc;
const int mod = 114514003, base = 432842357;
int n, m, idx, d[MAXN], lg[MAXN], f[MAXN][LOGN + 5], w[MAXN];
ll has[2][MAXN], pw[MAXN], invp[MAXN], sum[MAXN]; vector <int> lnk[MAXN];

il void add(const int &x, const int &y) {
	lnk[x].eb(y); lnk[y].eb(x);
}

struct query {
	int u1, v1, u2, v2;
}; vector <query> pr;

il void dfs(int x, int p) {
	f[x][0] = p; d[x] = d[p] + 1;
	has[0][x] = (has[0][p] * base + w[x]) % mod;
	has[1][x] = (has[1][p] + w[x] * pw[d[p]]) % mod;
	for (auto v : lnk[x]) if (v ^ p) dfs(v, x);
}

il int lca(int u, int v) {
	if (d[u] < d[v]) swap(u, v);
	rep2(i, lg[n], 0) if (d[u] - d[v] >= 1 << i) u = f[u][i];
	if (u == v) return u;
	rep2(i, lg[n], 0) if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
	return f[u][0];
}

int u, v, u2, v2, tp1, tp2;

il ull getval(int u, int v, int dis, int top) {
	ll ans; int p = u;
	rep2(i, lg[n], 0) if (d[u] - (1 << i) >= 0 && dis >= (1 << i) && d[f[u][i]] + 1 >= d[top]) {
		u = f[u][i], dis -= 1 << i;
	} ans = (has[1][p] - has[1][u]) * invp[d[u]] % mod;
	if (dis) {
		rep2(i, lg[n], 0) if (d[v] - d[top] - dis >= (1 << i)) v = f[v][i];
		int q = v;
		rep2(i, lg[n], 0) if (d[v] - (1 << i) >= 0 && d[f[v][i]] >= d[top]) v = f[v][i];
		(ans = ans * pw[dis] + has[0][q] - has[0][v] * pw[dis]) %= mod;
	} return (ans + mod) % mod;
}

il bool check(int x) {
	if ((getval(u, v, x, tp1) + sum[x - 1]) % mod != getval(u2, v2, x, tp2)) return false;
	return true;
}

il int qpow(int a, int b) {
	ll ans = 1, base = a;
	while (b) {
		if (b & 1) (ans *= base) %= mod;
		(base *= base) %= mod; b >>= 1;
	} return ans;
}

int main() {
	read(n, m, idx); rer(i, 1, n, w);
	rep1(i, 2, n) add(read(), read());
	while (m--) {
		int op, u, v, u2, v2;
		read(op, u, v);
		if (op == 1) read(u2, v2), pr.eb(query{u, v, u2, v2});
		else ++n, add(n, u), w[n] = v;
	}
	rep1(i, 2, n) lg[i] = lg[i >> 1] + 1;
	sum[0] = pw[0] = invp[0] = 1;
	rep1(j, 1, n) sum[j] = pw[j] = pw[j - 1] * base % mod, invp[j] = qpow(pw[j], mod - 2);
	
	rep1(j, 1, n) (sum[j] += sum[j - 1]) %= mod;
	rep1(j, 1, n) (sum[j] += sum[j - 1]) %= mod;
	dfs(1, 0);
	
	rep1(j, 1, lg[n]) rep1(i, 1, n) f[i][j] = f[f[i][j - 1]][j - 1];
	for (auto p : pr) {
		u = p.u1, v = p.v1, u2 = p.u2, v2 = p.v2;
		tie(tp1, tp2) = mp(lca(u, v), lca(u2, v2));
		int l = 0, r = min(d[u] - d[tp1] + d[v] - d[tp1] + 1, d[u2] - d[tp2] + d[v2] - d[tp2] + 1);
		while (l ^ r) {
			int mid = l + r + 1 >> 1;
			if (check(mid)) l = mid;
			else r = mid - 1;
		} printf("%d\n", l);
	}
	rout;
}
```

---

## 作者：bluewindde (赞：3)

发现求 $LRP(a,b)$ 时，存在 $a_j$ 和 $j$ 两个没有直接关系的变量，所以应该不能用数据结构一步得答案。

可以想到哈希。

先考虑 $a_j$。

预处理从根节点到每一个节点的哈希值 $hs_i$，树上倍增处理树上任何一段深度由大到小的序列的哈希值和 LCA。

考虑查询从 $u$ 到 $v$ 的一段序列的哈希值，设 $u,v$ 的 LCA 为 $p$，这个序列的哈希值为从 $u$ 到 $p$ 的哈希值：$hash(u,p)=hs_u-hs_{fa_p}\times base^{dep_u-dep_{fa_p}}$，加上从 $p$ 到 $v$ 的哈希值（用倍增求，代码如下）。

```cpp
static inline ull hsh(int x, int k) { // x 往上的长度为 k 的路径的哈希
    ull ret = 0;
    for (int i = 20; i >= 0; --i)
        if ((k >> i) & 1) {
            int len = dep[x] - dep[st[x][i]];
            ret = ret * power[len] + wst[x][i];
            x = st[x][i];
        }
    return ret;
}
```

再考虑第二个变量 $j$，直接预处理（代码如下），因为哈希的本质是一个 $base$ 进制的数对 $mod$ 取模的值，所以可以直接与 $a_j$ 的哈希值相加得到该序列总体的哈希值。

```cpp
for (int i = 1; i <= n; ++i) {
    jer[i] = jer[i - 1] + power[i - 1] * i;
}
```

显然 $LRP(a,b)$ 有单调性，可以二分答案。并且，新添加的点不会对答案造成影响，可以离线询问，便于预处理。

代码

```cpp
#include <iostream>
#include <tuple>
#include <vector>

#define ull unsigned long long

using namespace std;

const int base = 131;

int n, m, idx;
vector<int> vec[200005];
vector<tuple<int, int, int, int>> question;
int a[200005];
int w[200005];
int f[200005];
int dep[200005];
int st[200005][25];  // 倍增 LCA
ull wst[200005][25]; // 哈希
ull hs[200005];
ull power[200005]; // 预处理 base 的幂
ull jer[200005];   // 预处理 j 的幂

static inline void dfs(int u, int fa) {
    st[u][0] = fa;
    wst[u][0] = w[u];
    hs[u] = hs[fa] * base + w[u];
    f[u] = fa;
    dep[u] = dep[fa] + 1;
    for (int i = 1; i <= 20; ++i) {
        st[u][i] = st[st[u][i - 1]][i - 1];
        wst[u][i] = wst[u][i - 1] * power[dep[st[u][i - 1]] - dep[st[st[u][i - 1]][i - 1]]] + wst[st[u][i - 1]][i - 1];
    }
    for (auto v : vec[u]) {
        if (v == fa) {
            continue;
        }
        dfs(v, u);
    }
}
static inline int LCA(int u, int v) { // 最近公共祖先
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    for (int i = 20; i >= 0; --i) {
        if (dep[st[u][i]] >= dep[v]) {
            u = st[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = 20; i >= 0; --i) {
        if (st[u][i] != st[v][i]) {
            u = st[u][i];
            v = st[v][i];
        }
    }
    return st[u][0];
}
static inline int jump(int x, int k) { // 跳到 x 的 k 级祖先
                                       // 这和 轻重路径 的求法如出一辙
    for (int i = 20; i >= 0; --i) {
        if ((k >> i) & 1) {
            x = st[x][i];
        }
    }
    return x;
}
static inline ull hsh(int x, int k) { // x 往上的长度为 k 的路径的哈希
    ull ret = 0;
    for (int i = 20; i >= 0; --i)
        if ((k >> i) & 1) {
            int len = dep[x] - dep[st[x][i]];
            ret = ret * power[len] + wst[x][i];
            x = st[x][i];
        }
    return ret;
}
static inline ull Hash(int x, int y) {
    return hs[x] - hs[f[y]] * power[dep[x] - dep[f[y]]];
}
static inline ull get(int x, int y, int lca, int len) {
    int fl = dep[x] - dep[lca] + 1;
    if (len <= fl) {
        y = jump(x, len - 1);
        return Hash(x, y);
    }
    len -= (dep[x] - dep[lca] + 1);
    ull ans = Hash(x, lca);
    y = jump(y, dep[y] - dep[lca] - len);
    ans = ans + power[dep[x] - dep[lca] + 1] * hsh(y, len);
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> idx;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    while (m--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int u1, v1, u2, v2;
            cin >> u1 >> v1 >> u2 >> v2;
            question.push_back(make_tuple(u1, v1, u2, v2)); // 询问离线
                                                            // 方便预处理
        } else {
            int u, x;
            cin >> u >> x;
            ++n;
            vec[u].push_back(n);
            w[n] = x;
        }
    }
    power[0] = 1;
    for (int i = 1; i <= n; ++i) {
        power[i] = power[i - 1] * base;
        jer[i] = jer[i - 1] + power[i - 1] * i;
    }
    dfs(1, 0);
    for (auto [u1, v1, u2, v2] : question) {
        int lca1 = LCA(u1, v1);
        int lca2 = LCA(u2, v2);
        int dis1 = dep[u1] + dep[v1] - dep[lca1] - dep[f[lca1]];
        int dis2 = dep[u2] + dep[v2] - dep[lca2] - dep[f[lca2]];
        int l = 1;
        int r = min(dis1, dis2);
        int ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if ((get(u1, v1, lca1, mid) + jer[mid]) == (get(u2, v2, lca2, mid))) {
                l = mid + 1;
                ans = mid;
            } else {
                r = mid - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

自然溢出哈希可过，应该没有我这种用 $10^{11}+3$ 作模数的见祖宗人吧。


---

## 作者：Fzrcy (赞：2)

明显的，我们可以将操作离线下来，先考虑操作二，再考虑操作一。

- 对于操作二，直接连边即可。
- 对于操作一，我们发现答案具有可二分性，考虑二分答案 $mid$，那么 $mid\le LEP(a,b)$ 当且仅当 $b_i=a_i+i(1\le i\le mid)$。这个东西一脸不可直接维护的样子，考虑维护序列的哈希值。那么原式等价于 $Hash(\{b_1,b_2,\dots,b_{mid}\})=Hash(\{a_1,a_2,\dots,a_{mid}\})+Hash(\{1,2,\dots,mid\})$（$Hash(x)$ 表示序列 $x$ 的哈希值）。其中 $Hash(\{1,2,\dots,mid\})$ 可以预处理，树上任意一条序列的哈希值可以用树上倍增维护。

具体的，用 $st_{x,i}$ 表示序列 $w_x,w_{fa_x},\dots,w_y$ 的哈希值（$y$ 为 $x$ 的 $2^{i}-1$ 级祖先），$val_x$ 表示序列 $w_1,\dots,w_{fa_x},w_x$ 的哈希值，这样就可以在 $O(\log n)$ 的复杂度内计算任意一条树上序列的哈希值。

总时间复杂度为 $O(n\log n+m\log^2n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ull=unsigned long long;
const int N=3e5+1;
int h[N],nt[N<<1],to[N<<1],cnt;
ull pw[N],val[N],Base,ST[N][21],I[N];
int dep[N],st[N][21],W[N],Fa[N];
void add(int u,int v){nt[++cnt]=h[u],h[u]=cnt,to[cnt]=v;}
void dfs(int u, int fa){
    Fa[u]=fa;
    dep[u]=dep[fa]+1;
    st[u][0]=fa;
    ST[u][0]=W[u];
    val[u]=val[fa]*Base+1ull*W[u];
    for(int i=1; i<21; i++){
        st[u][i]=st[st[u][i-1]][i-1];
        int x=dep[st[u][i-1]]-dep[st[st[u][i-1]][i-1]];
        ST[u][i]=ST[u][i-1]*pw[x]+ST[st[u][i-1]][i-1];
    }
    for(int i=h[u],v; i; i=nt[i]){
        if((v=to[i])==fa)continue;
        dfs(v,u);
    }
}
int Lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int i=20; i>=0; i--)
        if(dep[st[x][i]]>=dep[y])x=st[x][i];
    if(x==y)return x;
    for(int i=20; i>=0; i--)
        if(st[x][i]!=st[y][i])
        x=st[x][i],y=st[y][i];
    return st[x][0];
}
int Jump(int x,int Length){
    for(int i=20; i>=0; i--)
        if((Length>>i)&1)x=st[x][i];
    return x;
}
ull jump(int x,int Length){
    ull ans=0;
    for(int i=20; i>=0; i--)
    if((Length>>i)&1){
        int len=dep[x]-dep[st[x][i]];
        ans=ans*pw[len]+ST[x][i];
        x=st[x][i];
    }
    return ans;
}
int Dist(int x,int y,int g){return dep[x]+dep[y]-dep[g]-dep[Fa[g]];}
ull Hash(int x,int y){
    return val[x]-val[Fa[y]]*pw[dep[x]-dep[Fa[y]]];
}
ull get(int x,int y,int g,int len){
    int fl=dep[x]-dep[g]+1;
    if(len<=fl){
        y=Jump(x,len-1);
        return Hash(x,y);
    }
    len-=(dep[x]-dep[g]+1);
    ull ans=Hash(x,g);
    y=Jump(y,dep[y]-dep[g]-len);
    ans=ans+pw[dep[x]-dep[g]+1]*jump(y,len);
    return ans;
}
bool check(int x,int y,int g1,int p,int q,int g2,int len){
    return get(x,y,g1,len)+I[len]==get(p,q,g2,len);
}
int Q[N][4],Qc,n,m;
int main(){
#ifdef LOCAL
    freopen("text.in","r",stdin);
    freopen("text.out","w",stdout);
#endif // LOCAL
    int Idx;
    cin>>n>>m>>Idx;
    for(int i=1; i<=n; i++)cin>>W[i];
    for(int i=1,x,y; i<n; i++)
        cin>>x>>y,add(x,y),add(y,x);
    while(m--){
        int op;
        cin>>op;
        if(op==2){
            n++;
            int x,y;
            cin>>x>>y;
            W[n]=y,add(n,x),add(x,n);
        }
        else{
            Qc++;
            cin>>Q[Qc][0]>>Q[Qc][1]>>Q[Qc][2]>>Q[Qc][3];
        }
    }
    pw[0]=1;
    Base=1145143;
    for(int i=1; i<=n; i++)
        pw[i]=pw[i-1]*Base,I[i]=I[i-1]+1ull*pw[i-1]*i;
    dfs(1,0);
    for(int Now=1; Now<=Qc; Now++){
        int x=Q[Now][0],y=Q[Now][1];
        int p=Q[Now][2],q=Q[Now][3];
        int l=1,ans=0,g1=Lca(x,y),g2=Lca(p,q);
//        printf("Lca1: %d Lca2: %d\n",g1,g2);
        int r=min(Dist(x,y,g1),Dist(p,q,g2));
//        printf("Max Length: %d\n",r);
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(x,y,g1,p,q,g2,mid))l=mid+1,ans=mid;
            else r=mid-1;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：zhangxy__hp (赞：0)

新加的点不会影响之前的询问，所以直接离线，先把所有点都建好。

将问题转化为：用 $b$ 数组减去 $a$ 数组，得到的形如 $1,2,3,\dots$ 的等差序列的最大长度。

考虑将两个序列哈希，预处理出等差数列的哈希值，二分长度即可。而在树上维护路径数组的哈希值，可以用倍增解决。

时间复杂度 $O(m\log^2n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
#define ull unsigned ll
#define pb push_back
using namespace std;
namespace asbt{
namespace cplx{bool begin;}
const int maxn=2e5+5;
const ull bas1=13331;
const ll bas2=13327,mod2=1e9+7;
int n,m,q,T,_2[22];
int a[maxn],dep[maxn];
int anc[maxn][22];
vector<int> e[maxn];
struct wnti{
	int u1,v1,u2,v2;
}wt[maxn];
ull tar1[maxn],pw1[maxn];
ull up1[maxn][22],dw1[maxn][22];
ll tar2[maxn],pw2[maxn];
ll up2[maxn][22],dw2[maxn][22];
il void dfs(int u,int fa){
	anc[u][0]=fa,dep[u]=dep[fa]+1;
	up1[u][0]=dw1[u][0]=a[u]*pw1[1];
	up2[u][0]=dw2[u][0]=a[u]*pw2[1]%mod2;
	for(int i=1;i<=20;i++){
		anc[u][i]=anc[anc[u][i-1]][i-1];
		up1[u][i]=up1[u][i-1]+up1[anc[u][i-1]][i-1]*pw1[_2[i-1]];
		dw1[u][i]=dw1[u][i-1]*pw1[_2[i-1]]+dw1[anc[u][i-1]][i-1];
		up2[u][i]=(up2[u][i-1]+up2[anc[u][i-1]][i-1]*pw2[_2[i-1]])%mod2;
		dw2[u][i]=(dw2[u][i-1]*pw2[_2[i-1]]+dw2[anc[u][i-1]][i-1])%mod2;
	}
	for(int v:e[u]){
		if(v==fa){
			continue;
		}
		dfs(v,u);
	}
}
il int lca(int u,int v){
	if(dep[u]<dep[v]){
		swap(u,v);
	}
	int ddep=dep[u]-dep[v],tmp=0;
	while(ddep){
		if(ddep&1){
			u=anc[u][tmp];
		}
		ddep>>=1,tmp++;
	}
	if(u==v){
		return u;
	}
	for(int i=20;~i;i--){
		if(anc[u][i]!=anc[v][i]){
			u=anc[u][i],v=anc[v][i];
		}
	}
	return anc[u][0];
}
il int ganc(int u,int k){
	int tmp=0;
	while(k){
		if(k&1){
			u=anc[u][tmp];
		}
		k>>=1,tmp++;
	}
	return u;
}
il ull gha1(int u,int v,int rt,int len){
//	cout<<u<<" "<<v<<"\n";
	if(len<=dep[u]-dep[rt]+1){
		int tmp=0,cur=0;
		ull res=0;
		while(len){
			if(len&1){
				res+=up1[u][tmp]*pw1[cur];
				cur+=_2[tmp],u=anc[u][tmp];
			}
			len>>=1,tmp++;
		}
//		cout<<res<<"\n";
		return res;
	}
	int ddep=dep[u]-dep[rt]+1;
	int tmp=0,cur=0;
	ull res=0;
	len-=ddep;
	int tdep=ddep;
	while(ddep){
		if(ddep&1){
			res+=up1[u][tmp]*pw1[cur];
			cur+=_2[tmp],u=anc[u][tmp];
		}
		ddep>>=1,tmp++;
	}
	v=ganc(v,dep[v]-dep[rt]-len);
//	cout<<v<<" "<<res<<"\n";
	tmp=cur=0;
	int tlen=len;
	while(len){
		if(len&1){
			res+=dw1[v][tmp]*pw1[tdep+tlen-cur-_2[tmp]];
			cur+=_2[tmp],v=anc[v][tmp];
		}
		len>>=1,tmp++;
	}
//	cout<<res<<"\n";
	return res;
}
il ll gha2(int u,int v,int rt,int len){
	if(len<=dep[u]-dep[rt]+1){
		int tmp=0,cur=0;
		ll res=0;
		while(len){
			if(len&1){
				(res+=up2[u][tmp]*pw2[cur])%=mod2;
				cur+=_2[tmp],u=anc[u][tmp];
			}
			len>>=1,tmp++;
		}
		return res;
	}
	int ddep=dep[u]-dep[rt]+1;
	int tmp=0,cur=0;
	ll res=0;
	len-=ddep;
	int tdep=ddep;
	while(ddep){
		if(ddep&1){
			(res+=up2[u][tmp]*pw2[cur])%=mod2;
			cur+=_2[tmp],u=anc[u][tmp];
		}
		ddep>>=1,tmp++;
	}
	v=ganc(v,dep[v]-dep[rt]-len);
	tmp=cur=0;
	int tlen=len;
	while(len){
		if(len&1){
			(res+=dw2[v][tmp]*pw2[tdep+tlen-cur-_2[tmp]])%=mod2;
			cur+=_2[tmp],v=anc[v][tmp];
		}
		len>>=1,tmp++;
	}
	return res;
}
namespace cplx{
	bool end;
	il double usdmem(){return (&begin-&end)/1048576.0;}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m>>T;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		e[u].pb(v),e[v].pb(u);
	}
	while(m--){
		int opt;
		cin>>opt;
		if(opt==1){
			int u1,v1,u2,v2;
			cin>>u1>>v1>>u2>>v2;
			wt[++q]=(wnti){u1,v1,u2,v2};
		}
		else{
			int u,w;
			cin>>u>>w;
			a[++n]=w;
			e[u].pb(n),e[n].pb(u);
		}
	}
	pw1[0]=pw2[0]=1;
	for(int i=1;i<=n;i++){
		pw1[i]=pw1[i-1]*bas1;
		pw2[i]=pw2[i-1]*bas2%mod2;
		tar1[i]=tar1[i-1]+i*pw1[i];
		tar2[i]=(tar2[i-1]+i*pw2[i])%mod2;
	}
	_2[0]=1;
	for(int i=1;i<=20;i++){
		_2[i]=_2[i-1]<<1;
	}
	dfs(1,0);
//	for(int u=1;u<=n;u++){
//		for(int i=0;i<=2;i++){
//			cout<<anc[u][i]<<" ";
//		}
//		puts("");
//	}
	for(int i=1,u1,v1,u2,v2,rt1,rt2,l,r;i<=q;i++){
		u1=wt[i].u1,v1=wt[i].v1;
		u2=wt[i].u2,v2=wt[i].v2;
		rt1=lca(u1,v1),rt2=lca(u2,v2);
		l=0;
		r=min(dep[u1]+dep[v1]-2*dep[rt1],dep[u2]+dep[v2]-2*dep[rt2])+1;
//		cout<<l<<" "<<r<<"\n";
		while(l<r){
			int mid=(l+r+1)>>1;
//			cout<<l<<" "<<r<<" "<<mid<<"\n";
			if(gha1(u2,v2,rt2,mid)-gha1(u1,v1,rt1,mid)==tar1[mid]&&(gha2(u2,v2,rt2,mid)-gha2(u1,v1,rt1,mid)+mod2)%mod2==tar2[mid]){
				l=mid;
			}
			else{
				r=mid-1;
			}
		}
		cout<<l<<"\n";
	}
	return 0;
}
}
int main(){return asbt::main();}
```

---

