# Hill Climbing

## 题目描述

This problem has nothing to do with Little Chris. It is about hill climbers instead (and Chris definitely isn't one).

There are $ n $ hills arranged on a line, each in the form of a vertical line segment with one endpoint on the ground. The hills are numbered with numbers from 1 to $ n $ from left to right. The $ i $ -th hill stands at position $ x_{i} $ with its top at height $ y_{i} $ . For every two hills $ a $ and $ b $ , if the top of hill $ a $ can be seen from the top of hill $ b $ , their tops are connected by a rope. Formally, the tops of two hills are connected if the segment connecting their top points does not intersect or touch any of the other hill segments. Using these ropes, the hill climbers can move from hill to hill.

There are $ m $ teams of climbers, each composed of exactly two members. The first and the second climbers of the $ i $ -th team are located at the top of the $ a_{i} $ -th and $ b_{i} $ -th hills, respectively. They want to meet together at the top of some hill. Now, each of two climbers move according to the following process:

1. if a climber is at the top of the hill where the other climber is already located or will come eventually, the former climber stays at this hill;
2. otherwise, the climber picks a hill to the right of his current hill that is reachable by a rope and is the rightmost possible, climbs this hill and continues the process (the climber can also climb a hill whose top is lower than the top of his current hill).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF406D/18474a63aa39fe0525ef153aa056faf1ff26cb33.png)For each team of climbers, determine the number of the meeting hill for this pair!

## 样例 #1

### 输入

```
6
1 4
2 1
3 2
4 3
6 4
7 4
3
3 1
5 6
2 3
```

### 输出

```
5 6 3 
```

# 题解

## 作者：LEE114514 (赞：0)

## 题意

题目已经说得很清楚了，但是有一点要注意的是三点共线第三个点会被第二个点遮挡。

## 思路

首先，有一些绳子（以下绳子均指向后连接的）是没用的。比如 $5,1,2,3,4$ 这个例子中，$5$ 向其他每座山都有一根绳子，但是只有向 $4$ 的绳子是有意义的，因为其它山都可以通过绳子直接或间接走到 $4$。

对于每一座山，我们只保留有用的一根绳子，除了最后一座山没有绳子。那么，这个东西形成一个树形结构，把绳子看成向父节点连边。

我们思考一下保留的条件，发现就是下一个在凸包上的点。

## Code

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m,u,v,x[maxn],sta[maxn],tp,fa[20][maxn],dep[maxn];
long long y[maxn];
int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=19;~i;--i) if(dep[fa[i][x]]>=dep[y]) x=fa[i][x];
	if(x==y) return x;
	for(int i=19;~i;--i) if(fa[i][x]!=fa[i][y]) x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d%lld",x+i,y+i);
	for(int i=n;i>=1;--i){
		while(tp>=2&&(y[sta[tp]]-y[i])*(x[sta[tp-1]]-x[sta[tp]])<(y[sta[tp-1]]-y[sta[tp]])*(x[sta[tp]]-x[i])) --tp;
		dep[i]=dep[sta[tp]]+1;
		fa[0][i]=sta[tp];
		sta[++tp]=i;
	}
	for(int i=1;i<19;++i) for(int j=1;j<=n;++j) fa[i][j]=fa[i-1][fa[i-1][j]];
	scanf("%d",&m);
	while(m--) scanf("%d%d",&u,&v),printf("%d ",LCA(u,v));
}
```

---

## 作者：Hoks (赞：0)

## 前言
duel 发生意外后来提款的时候跳到的题，感觉挺水的。

感觉如果写过斜优的话这题还是很好写的。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
首先不难发现对于一座山 $i$，他到达的山是唯一固定的。

接着询问又是问从山 $x,y$ 出发第一次在哪座山相遇。

走的过程又是让左边的人先走。

结合这些性质，感觉像什么东西？

不就是求 LCA 吗？

对于山 $i$，他到达的山就是 $f_i$，这样组成了一个以 $n$ 为根的树。

左边先走就是深度深的先跳嘛，所以题意的从山 $x,y$ 出发第一次相遇即为点 $x,y$ 在树上的 LCA 编号。

这个东西直接用树剖可以轻松解决，接着来考虑怎么建树。

相当于对于点 $i$ 找到第一个上凸点。

对于这种问题，考虑使用单调数据结构维护。

但是我们并不能找到单调性，只知道随着 $i$ 的递增，$f_i$ 也递增，原因是左边的山峰被**删除**了。

考虑把这个过程逆转过来，从右边开始扫，就变成了一个山峰只增不减的问题。

用单调队列类似于斜率优化维护一个上凸包即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,INF=0x3f3f3f3f3f3f3f3f;
struct node{int x,y;}a[N];
int n,m,tot,st[N];vector<int>e[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline int slope(int x,int y,int z)
{
    node s={a[x].x-a[y].x,a[x].y-a[y].y};
    node t={a[y].x-a[z].x,a[y].y-a[z].y};
    return s.x*t.y-s.y*t.x;
}
namespace tree_decomposition
{
    int fa[N],son[N],si[N],dep[N],top[N];
    inline void dfs1(int u,int ff)
    {
        fa[u]=ff,si[u]=1,dep[u]=dep[ff]+1;
        for(auto v:e[u])
        {
            if(v==ff) continue;
            dfs1(v,u);si[u]+=si[v];
            if(si[son[u]]<si[v]) son[u]=v;
        }
    }
    inline void dfs2(int u,int topf)
    {
        top[u]=topf;
        if(son[u]) dfs2(son[u],topf);
        for(auto v:e[u])
        {
            if(v==fa[u]||v==son[u]) continue;
            dfs2(v,v);
        }
    }
    inline int LCA(int x,int y)
    {
        while(top[x]!=top[y])
        {
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]<dep[y]?x:y;
    }
}
using namespace tree_decomposition;
signed main()
{
    n=read();for(int i=1;i<=n;i++) a[i].x=read(),a[i].y=read();
    st[++tot]=n;m=read();
    for(int i=n-1;i>=1;i--)
    {
        while(tot>=2&&slope(st[tot-1],st[tot],i)<0) tot--;
        e[st[tot]].emplace_back(i);st[++tot]=i;
    }dfs1(n,0);dfs2(n,n);
    for(int i=1,x,y;i<=m;i++) x=read(),y=read(),print(LCA(x,y)),put(' ');
    genshin:;flush();return 0;
}

```

---

## 作者：truly_handsome (赞：0)

题意：有 $n$ 座山，第 $i$ 座的山的山顶位置为 $(x_i,y_i)$。对于每两座山 $a$ 和山 $b$，如果从山 $a$ 的山顶可以看到山 $b$ 的山顶，则它们的山顶由一根绳子连接。

现在有 $m$ 个登山队，每队有两个攀登者，每个攀登者都可以经过绳子到达**最右边**的山顶，问每个登山队两人相见的山的编号。

很明显，每次必须到达最右边而且还能不被其他山阻挡的意思就是说路径是一些上凸包，又因为每座山最多只能到达一座山，所以这还是一颗树，那问题就转化为问一颗树上两个节点的 $LCA$。

```cpp
# include <bits/stdc++.h>
# define pb push_back
# define int long long
using namespace std;

int n, top = 0, st[100005], dep[100005], f[100005][25];

struct P{
	int x, y;
} arr[100005];

P operator - (P a, P b){return (P){a.x-b.x, a.y-b.y};}

int cc(P a, P b){return a.x*b.y - a.y*b.x;}

int LCA(int u, int v){
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 20;i >= 0;i--) if (dep[f[u][i]] >= dep[v]) u = f[u][i];
	if (u == v) return u;
	for (int i = 20;i >= 0;i--) if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
	return f[u][0];
}

signed main(){
	scanf("%lld", &n);
	for (int i = 1;i <= n;i++) scanf("%lld%lld", &arr[i].x, &arr[i].y);
	st[++top] = n; f[n][0] = n;
	for (int i = n-1;i >= 1;i--){
		while (top >= 2 && cc(arr[st[top]] - arr[i], arr[st[top-1]] - arr[st[top]]) > 0) top--;
		f[i][0] = st[top]; dep[i] = dep[st[top]] + 1; st[++top] = i;
	}
	for (int i = 1;i <= 20;i++) for (int j = 1;j <= n;j++) f[j][i] = f[f[j][i-1]][i-1];
	int q; scanf("%lld", &q);
	while (q--){
		int u, v; scanf("%lld%lld", &u, &v);
		printf("%lld\n", LCA(u, v));
	}
	return 0;
}

```

---

