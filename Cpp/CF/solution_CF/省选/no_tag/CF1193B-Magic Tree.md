# Magic Tree

## 题目描述

我们有一棵魔法树：一棵有 $n$ 个顶点的有根树。顶点编号为 $1$ 到 $n$，顶点 $1$ 是根节点。

魔法树会结出魔法果实。果实只会长在根节点以外的顶点上，每个顶点最多有一个果实。

现在是第 $0$ 天，所有果实都还未成熟。每个果实只会在某一天成熟一天。对于每个果实，给出它生长的顶点 $v_j$、成熟的天数 $d_j$，以及如果在成熟当天采摘可以获得的魔法汁液量 $w_j$。

采摘果实时需要通过砍断树上的某些分支来完成。每天你可以砍断任意多条树枝。被砍下的部分会掉落到地面，你可以收集其中所有当天成熟的果实。所有在掉落时未成熟的果实都会被丢弃，无法获得魔法汁液。

具体来说，每天你可以删除树上的一些边。每次删除后，树会被分成若干连通块。你需要删除所有不包含根节点的连通块，并收获这些连通块中当天成熟的所有果实。

给定树的结构，以及所有 $m$ 个果实的位置、成熟天数和汁液量，计算你最多能从树上收获多少魔法汁液。

## 说明/提示

在样例输入中，一种最优方案如下：

- 第 4 天，砍断顶点 4 和 5 之间的边，收获成熟的果实，获得 1 单位魔法汁液。同一天，砍断顶点 1 和 2 之间的边，收获顶点 3 上成熟的果实，获得 5 单位魔法汁液。
- 第 7 天，不做任何操作。（此时可以收获刚成熟的顶点 4 上的果实，但这样做不是最优的。）
- 第 9 天，砍断顶点 1 和 4 之间的边，丢弃已经不再成熟的顶点 4 上的果实，收获顶点 6 上成熟的果实，获得 3 单位魔法汁液。（或者，也可以砍断顶点 4 和 6 之间的边，效果相同。）

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 4 10
1
2
1
4
4
3 4 5
4 7 2
5 4 1
6 9 3
```

### 输出

```
9
```

# 题解

## 作者：辰星凌 (赞：5)

# **【题解】魔法树 Magic Tree [CEOI2019] [CF1193B] [Loj3166]**

[$\mathcal{My}\ \mathcal{Blog}$](https://www.cnblogs.com/Xing-Ling/p/12931590.html)

传送门：[魔法树 $\text{Magic Tree}$](https://www.luogu.com.cn/problem/CF1193B) [$\text{[CEOI2019]}$](https://ceoi.sk/static/statements/magictree-ENG.pdf) [$\text{[CF1193B]}$](http://codeforces.com/problemset/problem/1193/B) [$\text{[Loj3166]}$](https://loj.ac/problem/3166)

## **【题目描述】**

给出一颗 $n$ 个节点的树（根为 $1$），每个节点 $i$ 会在第 $d_i$ 天时放出量为 $w_i$ 的妹汁。在每一天 $j$ 您可以砍掉树上的任意一些边，若当天与节点 $1$ 不再联通的点的 $d_i$ 恰好等于 $j$，您可以获得这些妹汁。

求总共最多能收获多少妹汁。

## **【分析】**

先考虑暴力 $dp$，设 $f(x,j)$ 表示在时间 $j$ 时以 $x$ 为根的子树可获得的最大妹汁量，则有：

$f(x,j)=\max\{f(x,j-1),g(x,j)\}$，其中 $g(x,j)=w(x)*[j=d(x)]+\sum_{to\in son(x)}f(to,j)$

复杂度 $O(nk)$，可以过 $\text{Subtask 1,4,5}$，有 $34pts$ 。

用个小 $trick$ 优化转移。

注意到 $f$ 实际上是 $g$ 的前缀最大值，给每个点开个 $map$ 记录 $j$ 和 $f(x,j)-f(x,k)$ $(k<j,f(x,k)\neq f(x,j))$（相邻两个不同前缀最大值的差），那坨子树累加直接启发式合并。

每次给 $g(x,d(x))$ 加上 $w(x)$ 后都会使从 $d(x)$ 开始的连续一段发生改变，先 $\text{upperbound}$ 找到 $d(x)$ 位置后面的第一个指针，然后依次往后移动并删去被更新掉的位置，无法继续更新时就停止（利用差分的良好性质）。

## **【Code】**

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<map>
#define LL long long
#define Re register int
#define IT map<int,LL>::iterator
using namespace std;
const int N=1e5+3;
int n,m,x,y,o,T,K,t[N],v[N],head[N];
struct QAQ{int to,next;}a[N];
inline void add(Re x,Re y){a[++o].to=y,a[o].next=head[x],head[x]=o;}
inline void in(Re &x){
    int f=0;x=0;char c=getchar();
    while(c<'0'||c>'9')f|=c=='-',c=getchar();
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
    x=f?-x:x;
}
struct Sakura1{//暴力
    LL ans,dp[N][23];
    inline void dfs(Re x){
        for(Re i=head[x],to;i;i=a[i].next){
            dfs(to=a[i].to);
            for(Re j=0;j<=K;++j)dp[x][j]+=dp[to][j];
        }
        dp[x][t[x]]+=v[x];
        for(Re j=t[x]+1;j<=K;++j)dp[x][j]=max(dp[x][j],dp[x][j-1]);
    }
    inline void sakura(){dfs(1),printf("%lld\n",dp[1][K]);}
}T1;
struct Sakura2{//正解
    int id[N];LL ans;map<int,LL>s[N];
    inline void dfs(Re x){
        id[x]=x;
        for(Re i=head[x],to;i;i=a[i].next){
            dfs(to=a[i].to);
            if(s[id[x]].size()<s[id[to]].size())swap(id[x],id[to]);
            for(IT it=s[id[to]].begin();it!=s[id[to]].end();++it)
                s[id[x]][it->first]+=it->second;
        }
        s[id[x]][t[x]]+=v[x];LL dlt=v[x];IT it=s[id[x]].upper_bound(t[x]),tmp;
        while(it!=s[id[x]].end())
            if(dlt>=it->second)dlt-=it->second,tmp=it++,s[id[x]].erase(tmp);//f(x,d(x))更优，删掉这个点
            else{it->second-=dlt;break;}//这个点更优，结束枚举
    }
    inline void sakura(){
        dfs(1);
        for(IT it=s[id[1]].begin();it!=s[id[1]].end();++it)ans+=it->second;//差分回收
        printf("%lld\n",ans);
    }
}T2;
int main(){
//    freopen("magic.in","r",stdin);
//    freopen("magic.out","w",stdout);
    in(n),in(T),in(K),m=n-1;
    for(Re i=2;i<=n;++i)in(x),add(x,i);
    while(T--)in(x),in(t[x]),in(v[x]);
//    if(K<=20)T1.sakura();else
    T2.sakura();
}
```


---

## 作者：Flash_Man (赞：2)

[link](https://www.luogu.com.cn/problem/CF1193B)

[双倍经验](https://www.luogu.com.cn/problem/P6847)

$f(u,i)$ 表示 $u$ 节点在 $i$ 天之前收割的最大收益。
$$
f(u,i)=\max\begin{cases}\sum f(v,i)\\w_i+\sum f(v,d_u)&,\text{if}\ i\ge d_u \end{cases}
$$
考虑到转移方程是求和和后缀加，所以用 map 维护断点即可。第一行转移方程相当于 map 按秩合并，第二行转移方程相当于在 map 里加一个差分标记。

细节：由于两行转移方程要取 $\max$，所以用第二行更新时要把后面的一些差分标记覆盖掉，具体实现见代码。

```cpp
#include <cstdio>
#include <map>
#include <algorithm>
#define int long long
const int maxn = 1e5 + 3;
int n, m, k, fa[maxn], a[maxn], d[maxn], w[maxn];
std::map<int, int> f[maxn];
int rt[maxn], ans = 0;
void merge(int &x, int y) {
	if (f[x].size() < f[y].size()) std::swap(x, y);
	for (auto p : f[y]) f[x][p.first] += p.second;
}
signed main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	for (int i = 2; i <= n; i++) scanf("%lld", &fa[i]);
	for (int i = 1, v; i <= m; i++) scanf("%lld", &v), scanf("%lld%lld", &d[v], &w[v]);
	for (int i = 1; i <= n; i++) rt[i] = i;
	for (int i = n; i >= 1; i--) {
		f[rt[i]][d[i]] += w[i];
		auto it = f[rt[i]].find(d[i]);
		for (it++; it != f[rt[i]].end(); ) {
			if (it->second > w[i]) { it->second -= w[i]; break; }
			w[i] -= it->second;
			auto tmp = it++;
			f[rt[i]].erase(tmp);
		}
		merge(rt[fa[i]], rt[i]);
	}
	for (auto p : f[rt[1]]) ans += p.second;
	printf("%lld\n", ans);
	return 0;
}
```

---

