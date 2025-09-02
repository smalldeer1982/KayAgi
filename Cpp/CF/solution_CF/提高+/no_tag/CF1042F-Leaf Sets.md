# Leaf Sets

## 题目描述

给定一棵包含 $n$ 个顶点的无向树。

如果某个顶点恰好与一个顶点相邻，则称其为叶子节点。

两个顶点之间的距离定义为它们之间最短路径上的边数。

我们称一组叶子节点为“美丽集合”，如果该集合中任意两叶子节点之间的最大距离不超过 $k$。

你需要将所有叶子节点划分为若干个互不相交的美丽集合。请问最少需要多少个美丽集合？

## 说明/提示

以下是第一个样例的图示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1042F/5a707ac956bf7a0b2ca96d67d4d3ef782292e2c3.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
9 3
1 2
1 3
2 4
2 5
3 6
6 7
6 8
3 9
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 3
1 2
2 3
3 4
4 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
6 1
1 2
1 3
1 4
1 5
1 6
```

### 输出

```
5
```

# 题解

## 作者：Sino_E (赞：6)


[blog](https://acxblog.site/archives/sol-cf-1042f.html)

考虑从下向上维护。

假设维护上来子树叶子节点的目前为止分成了$k$个集合，并且每个集合的最深深度为$k_i$，我们考虑如何合并这$k$个集合。

我们可以证明，假设有$k_1< k_2< ... < k_n$，则我们找到最大的$i$使$k_i+k_{i+1}>K$，那么$k_1$到$k_i$都可以合并在一起，并且这么合并一定最优。

若存在$1,2,4$能合并，则一定有$1,2,3$能合并，那么无论怎么合并，最后剩下来的一定会包含$3,4$（由$1,2,3$或$1,2,4$合并而来）。

若存在$1,2,4,6$能合并，则一定有$1,2,3,4,6$能合并，所以所有的其它情况都可转化成上面的情况。

所以如此合并得到的结果最终是相同的。

此时上可并堆就可以做到$O(n\log n)$的复杂度了。

---------------------

进一步分析。若$k_i+k_{i+1}>K$，那么在向上维护的过程中，$k_{i+1}$一定不会再与其它集合进行合并。

又因为所有比$k_i$小的都已经合并，所以我们只需要得到$k_i$即可，而令$k_{i+1}$到$k_n$直接单独成为集合。

于是只需用一个变量维护$k_i$的值即可，这样的复杂度为$O(n)$。

注意所有$k_i>K$的情况。

## Code
```cpp
// Code by ajcxsu
// Problem: leaf sets

#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10, M=2e6+10;
int h[N], to[M], nexp[M], d[N], p=1;
inline void ins(int a, int b) {
    nexp[p]=h[a], h[a]=p, to[p]=b, p++; d[a]++;
}

template<typename T> inline void gn(T &x) {
    char ch=getchar(); x=0;
    while(ch<'0' || ch>'9') ch=getchar();
    while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
}


int k, ans;
int dfs(int x, int fa) {
    if(d[x]==1) return 1;
    int na=0;
    for(int u=h[x];u;u=nexp[u])
        if(to[u]!=fa) {
            int d=dfs(to[u], x);
            if(d+na>k) ans++, na=min(na, d);
            else if(d>na) na=d;
        }
    return na?na+1:0;
}

int main() {
    int n, u, v, x;
    gn(n), gn(k);
    for(int i=0;i<n-1;i++) gn(u), gn(v), ins(u, v), ins(v, u);
    for(int i=1;i<=n;i++) if(d[i]>1) x=dfs(i, 0), printf("%d\n", ans+bool(x)), exit(0);
    printf("%d\n", ans+1);
    return 0;
}
```




---

## 作者：Dispwnl (赞：3)

#### 题目大意
给定一棵树，把树的叶子分成多个集合，要求每个集合的叶子距离不超过$k$，问最少可以划分成几个集合

#### 题解
感觉思路挺神仙的……

贪心的思想，按深度处理每个点，记录每个点的子树里的叶子节点到ta的距离，排个序后把相邻的相加不大于$k$的划成一个集合，即从$1$开始的一段区间，其他的各自搞个集合，然后返回大集合里的最长边，ta上面的节点处理这棵子树时就以这条边为代替了

为什么这样划分保证最优呢？假设有三条边$a,b,c(a<b<c)$，且$a+b\leq k,a+c\leq k,b+c>k$，如果$a$和$c$放一个集合里，那这个集合就不能放$b$了，同时这个集合能加进去的长度为$k-c$，如果放$b$，这个集合能加进去的长度为$k-b$，明显是优于放$c$的

那么为什么是返回大集合里的最长边呢？如果返回其他单元素的集合，ta们肯定大于大集合里的最长边，其他子树与ta匹配的限制会变大，所以可能会划分成更多的集合，不是更优的处理

#### 代码
```
# include<bits/stdc++.h>
using namespace std;
const int MAX=1e6+1;
struct p{
	int x,y;
}c[MAX<<1];
int n,k,num,ans;
int du[MAX],h[MAX];
void add(int x,int y)
{
	c[++num]=(p){h[x],y},h[x]=num;
	c[++num]=(p){h[y],x},h[y]=num;
}
int dfs(int x,int f=0)
{
	if(du[x]==1) return 0;
	vector<int> ve;
	for(int i=h[x];i;i=c[i].x)
	  if(c[i].y!=f) ve.push_back(dfs(c[i].y,x)+1);
	sort(ve.begin(),ve.end());
	int L=ve.size()-1;
	for(;L>=1;--L)
	  {
	  	if(ve[L]+ve[L-1]<=k) break;
	  	++ans;
	  }
	return ve[L];
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1,x,y;i<n;++i)
	  scanf("%d%d",&x,&y),add(x,y),++du[x],++du[y];
	int rt=1;
	for(int i=1;i<=n;++i)
	  if(du[i]>1) {rt=i;break;}
	dfs(rt);
	return printf("%d",ans+1),0;
}
```

---

## 作者：tommymio (赞：1)

看到这个模型，再看看数据范围，贪心没错了。

树形贪心通常考虑当前子树的情况，自底而上合并答案，这题也是如此。

设当前 $x$ 的子树内有 $m(x)$ 个划分出的叶子集合 $S_i$，集合 $S_i$ 中节点的最大深度是 $p_i$。

如果将这 $m(x)$ 个集合按 $p_i$ 从小到大排序，即 $k_1\leq k_2\leq k_3\leq k_4..\leq k_{m(x)}$，选择最小的 $k_i+k_{i+1}>k$，将 $k_1,k_2,..,k_i$ 所代表的集合合并，记合并后的集合为 $S'$。这样做一定是最优的，不存在其他方案比这个方案更优，这是非常容易证明的。并且，将 $S'$ 向上合并其他子树内的叶子集合也是最优的，因为 $S'$ 是 $x$ 子树内最大深度最小的集合，如果 $S'$ 无法合并，子树 $x$ 内的其他集合一定也无法合并。按上述策略不断递归向上合并就可以了，采用优秀一点的实现，时间复杂度可以达到 $O(n)$。

具体实现的话，我们记录一个子树内当前的 $k_i$ 的 $\min$，并注意特判当前子树内不存在符合条件的 $k_i$ 的情况。 

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
int cnt=0,ans=0,n,k;
int h[1000005],to[2000005],ver[2000005];
int dep[1000005],du[1000005];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline void add(int x,int y) {++du[x];to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline void add_d(int x,int y) {add(x,y);add(y,x);} 
inline int max(const int &x,const int &y) {return x>y? x:y;}
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline int dfs(int x,int fa) {
    if(du[x]==1) return du[x];
    int res=0;
    for(register int i=h[x],y,t;i;i=ver[i]) {
        if((y=to[i])==fa) continue; t=dfs(y,x);
        if(t+res>k) {++ans;res=min(res,t);}
        else if(res<t) res=t;
    }
    return res? res+1:0;
}
int main() {
    n=read();k=read();
    for(register int i=1;i<n;++i) add_d(read(),read());
    int rt=1; for(register int i=2;i<=n;++i) if(du[i]>1) {rt=i;break;}
    dep[rt]=1; int x=dfs(rt,-1); printf("%d\n",ans+(x>0));
    return 0;
}
```



---

## 作者：Priestess_SLG (赞：0)

比较巧妙的树上贪心。考虑在树上做 DFS，若当前结点为叶子结点则不做任何处理，否则，考虑一个非叶子结点 $u$，假设其所有儿子结点 $v_1,v_2,\ldots,v_k$ 全部 DFS 处理过了，那么假设从当前结点到她们的儿子结点的距离分别为 $d_1,d_2,\ldots,d_k$。则将 $d$ 数组升序排序，必然存在一个位置 $p$，使得 $1\sim p$ 中所有子树合并为一个集合，而 $p+1\sim k$ 中所有子树单独成为一个集合并不做任何合并操作。其中 $p$ 是最大的，满足 $1\sim p$ 内子树合并之后仍然满足条件的值，可以一遍扫描求出答案。容易证明这样贪心是正确的。时间复杂度为 $O(n\log n)$。

代码：

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000010;
vector<int> adj[N];
int deg[N], res, n, k;
int dfs(int u, int fa) {
    if (deg[u] == 1) return 0;
    vector<int> now;
    for (int &v : adj[u])
        if (v != fa) now.emplace_back(dfs(v, u) + 1);
    sort(now.begin(), now.end());
    while (now.size() >= 2) {
        if (now.back() + now[now.size() - 2] <= k) break;
        now.pop_back(), ++res;
    }
    return now.back();
}
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].emplace_back(y);
        adj[y].emplace_back(x);
        ++deg[x], ++deg[y];
    }
    for (int i = 1; i <= n; ++i)
        if (adj[i].size() > 1) {
            dfs(i, 0);
            cout << res + 1 << '\n';
            return 0;
        }
    cout << "1\n";
    return 0;
}
```

---

