# Rabbit

## 题目背景

“说实话，最喜欢你了；因为长得好看，所以最喜欢你了。

你的性格，我最喜欢了；虽然不太清楚，但是最喜欢了。”

赫尔德最近加入了一个奇怪的社区，那里面流行一种“配对追星”的活动。大家在人群中找到那个最耀眼的人，就作为自己的偶像了。

## 题目描述

赫尔德不知道这样是否好，为了研究这个活动，她想先从这个活动能持续多久开始研究。于是她抽象了这个问题。

给定一棵树，共 $n$ 个点，分别编号为 $1\sim n$。

每次操作，你需要选出三个点 $a,b,c$ 将他们标记，满足：

- $c$ 是 $a$ 到 $b$ 简单路径上编号最大的点；
- $a,b,c$ 两两不同；
- $a,b,c$ 先前都没有被标记过。

问至多能进行多少次操作。

---

**【提示】**

树上 $p$ 到 $q$ 的简单路径是指一个数列 $a_1,\dots,a_k$，满足：

1. $a_1=p$，$a_k=q$；
2. 其中没有重复元素；
3. 对于所有 $1\le i<k$，$a_{i+1}$ 与 $a_i$ 有边相连。

## 说明/提示

**【样例解释】**

对于第一组数据，可以选择 $a=1,b=2,c=3$。

对于第三组数据，可以依次选择 $a=3,b=4,c=7$，$a=1,b=2,c=5$。

---

**【数据范围】**

设 $S$ 为每个测试点所有数据中 $n$ 的和。

对于所有数据：$1\le T\le 3\times 10^4$，$1\le n\le 2\times 10^5$，$S\le 6\times 10^5$。

$$
\begin{array}{c|c|c|c|c|c} \hline
\textbf{子任务编号} & ~~~~~~~n\le ~~~~~~~ & ~~~~~~~S\le ~~~~~~~ & \textbf{特殊性质} & \textbf{子任务依赖} & \textbf{~~~分数~~~} \\ \hline
\textsf{1} & 5 & & & & 3 \\ \hline
\textsf{2} & 20 & 60 & & & 5 \\ \hline
\textsf{3} & & & \textsf{B} & & 12 \\ \hline
\textsf{4} & 333 & 10^3 & \textsf{A} & & 9 \\ \hline
\textsf{5} & 333 & 10^3 & & \textsf{2,4} & 7 \\ \hline
\textsf{6} & 3333 & 10^4 & \textsf{A} & \textsf{4} & 15 \\ \hline
\textsf{7} & 3333 & 10^4 & & \textsf{5,6} & 13 \\ \hline
\textsf{8} & & & \textsf{A} & \textsf{6} & 12 \\ \hline
\textsf{9} & & & & \textsf{1,3,7,8} & 24 \\ \hline
\end{array}
$$

特殊限制 $\textsf{A}$：保证树的形态是一条链，即树上不存在度数大于 2 的点。

特殊限制 $\textsf{B}$：保证树随机生成：对于每个整数 $i\in [2,n]$，均匀随机选择整数 $j\in [1,i-1]$ 并在 $i,j$ 间连边，然后随机打乱点的编号。

## 样例 #1

### 输入

```
3
3
2 3
1 3
4
2 3
3 4
4 1
7
2 5
5 1
2 6
2 3
7 4
3 7
```

### 输出

```
1
1
2
```

# 题解

## 作者：dottle (赞：44)

我们考察整棵树上编号最大的点 $X$。对于经过 $X$ 的所有路径，都应当选取 $X$ 作为最大值。去掉 $X$，将树切成了若干子树，递归进子树内解决原问题。然后对于这些子树，如果有至少两个子树内还有没进三元组的点，就他们和 $X$ 作为一个三元组。

直接做是 $n^2$ 的，我们不妨逆序地考虑。从小到大地加入每个点，每次加入点的时候把和它相邻的、已经加入了的点合并在一起。维护每一个连通块的最大三元组个数和总大小，未匹配点的个数可以根据前两个信息方便地计算。

时间复杂度 $O(n\alpha (n))$，其中 $\alpha(n)$ 是并查集复杂度。

```
#include<bits/stdc++.h>
const int N=1000050;
using namespace std;

int n,res;
int fa[N],rest[N];
int gf(int k){return k==fa[k]?k:fa[k]=gf(fa[k]);}
vector<int> e[N];

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)fa[i]=i,rest[i]=1,e[i].clear(),res=0;
	for(int i=1;i<n;i++){
		int x,y;cin>>x>>y;
		e[max(x,y)].push_back(min(x,y));
	}
	for(int k=1;k<=n;k++){
		int c=0;
		for(auto to:e[k]){
			c+=!!rest[gf(to)];
			rest[k]+=rest[gf(to)];
			fa[gf(to)]=k;
		}
		if(c>=2)rest[k]-=3,res++;
	} 
	cout<<res<<endl;
}

main(){
	ios::sync_with_stdio(false);
	int _T=1;cin>>_T;
	while(_T--)solve();
}
```

---

## 作者：Hisaishi_Kanade (赞：8)

为了感激多头的[回复](https://www.luogu.com.cn/discuss/499463)，我特意来这里膜拜。然后~~发现这题似乎并不难~~发觉这道题解法很巧妙，思维难度不低，代码极其简单。

题意很清楚，就是至多能找到多少个符合条件三元组 $\{a,b,c\}$：

1. $c$ 是 $a\to b$ 的简单路径上编号最大的点。
2. $a,b,c$ 是不同的三个节点。
3. $a,b,c$ 仅能被使用一次。

- - - 

接下来记录我的思考历程。

**编号最大**一词给了我启发，这也就是说明，这棵树编号为 $n$ 的节点要么就是 $\{a,b,c\}$ 中的 $c$，要么就干脆不用。

接下来我就思考：什么时候不用，什么时候用呢？

我们不妨假设一棵树中编号最大的节点就是根，输入时把编号小的当成编号大节点的儿子。

维护一个数组 ${size_i}$，表示以 $i$ 为根的树匹配完三元组后所剩的节点数。很显然有对于节点 $j$，$\sum[size_k>0]\ge 2$ 时就可以有一个三元组的 $c$ 为 $j$（$k$ 为 $j$ 儿子）。

再次因为输入时的特殊处理，惊奇的发现任意三元组 $\{a,b,c\}$ 中，$a,b$ 分别位于 $c$ 的两颗不同子树上！

但这样复杂度不可靠，所以使用并查集辅助维护 $size$，复杂度蜕变为 $O(n)$ 带点并查集常数，问题不大。

至此，题目结果水落石出。

- - -

我语文很差，如果没听懂借助代码理解。
```cpp
#include <vector>
#include <stdio.h>
std::vector<int> edge[200005];
int f[200005],sze[200005];
inline int find(int x){
    while(x!=f[x])
        x=f[x]=f[f[x]];
    return x;
}
//这种写法复杂度正确的，并且通常比递归版优秀。
int main(){
	int t,n,i,u,v,son,ans;
	scanf("%d",&t);while(t--){
	    ans=0;
	    scanf("%d",&n);
	    for(i=1;i<=n;++i)
	        f[i]=i;
	    for(i=1;i<=n;++i)
	        sze[i]=1;//先假定每个点“自成一家”
	    for(i=1;i<=n;++i)
	        edge[i].clear();//多测不清空，抱灵两行泪/ll
	    for(i=1;i<n;++i){
	        scanf("%d %d",&u,&v);
	        if(u>v)
	            edge[u].emplace_back(v);
	        else
	            edge[v].emplace_back(u);//这四行就是后面那么多行的基础。
	    }
	    std::vector<int>::iterator it;
	    for(i=1;i<=n;++i){
	        son=0;
	        for(it=edge[i].begin();it<edge[i].end();++it){//遍历所有子树
	            if(sze[find(*it)])
	                ++son;
	            sze[i]+=sze[find(*it)];//更新size
	            f[find(*it)]=i;//认祖宗
	        }
	        if(son>1){
	            sze[i]-=3;
	            ++ans;
	        }//如果子树中空闲节点个数足够，就能造出一个三元组。
	    }
	    printf("%d\n",ans);
	}
}
```

---

## 作者：hcywoi (赞：3)

[题目点这里](https://www.luogu.com.cn/problem/P8552)

题意：选出最多的“三元组 $a, b, c$”使得每个 $a, b, c$ 都不重复，并且 $c$ 是 $a \to b$ 的简单路径中的最大点。

设以下图为这棵树：

![](https://cdn.luogu.com.cn/upload/image_hosting/uyjoqh0g.png)

那么这个根节点必定是两个与他直接相连的子树中的**没有**匹配的点配对或者不配对。

~~说实话这句话有点绕。~~

在以上面的图解释一下:
![](https://cdn.luogu.com.cn/upload/image_hosting/9ntgi78m.png)

其中蓝色圈出部分表示已经变成了一组。

1. 这棵树的根就不需要与其他点进行成组，因为和别的点成组必须要拆掉一对，因为只有一颗子树满足有剩余的点，并且剩余的点不变，所以没有这个必要；
2. 两棵子树都满足有至少一个点是没有配对的，$a_{1 \sim 3}$ 与 $b$ 的路径中就经过最大点，可以给答案加 $1$。

综上所述，我们可以维护每一棵子树的剩余没匹配的数量，然后从小到大枚举每一个点，在枚举所有的邻边，如果这棵子树的剩余没匹配的数量 $\ge 1$，就把可以匹配的子树的数量加 $1$。

如果可以匹配的子树数量 $\ge 2$，则把合并完后的子树的剩余没匹配的数量减 $3$，因为要把根节点也减去，再把答案加  $1$。

以上操作可以用并查集来维护。

### $\text{Ac Code}$

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <cmath>
#include <sstream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#define x first
#define y second

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;

const int N = 200010, M = 200010, MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

int n;
int p[N], sz[N];
int h[N], e[N], ne[N], idx;

void add(int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int find(int x)
{
	if (p[x] != x) p[x] = find(p[x]);
	return p[x];
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T -- )
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i ++ )
		{
			h[i] = -1;
			p[i] = i, sz[i] = 1;
		}
		idx = 0;
		for (int i = 0; i < n - 1; i ++ )
		{
			int a, b;
			scanf("%d%d", &a, &b);
			add(max(a, b), min(a, b)); // 这里是编号大的与编号小的点连边
		}

		int res = 0;
		for (int i = 1; i <= n; i ++ )
		{
			int cnt = 0;
			for (int j = h[i]; ~j; j = ne[j]) // 枚举邻边
			{
				int k = e[j];
				int px = find(i), py = find(k);
				if (sz[py] >= 1) cnt ++ ;
				p[px] = py, sz[py] += sz[px]; // 合并
			}
			if (cnt >= 2) res ++, sz[find(i)] -= 3; // 说明i可以配对
		}
		printf("%d\n", res);
	}

	return 0;
}
```

---

## 作者：I_AM_CIMOTA (赞：2)

我们发现如果直接对原树考虑是不方便的，于是就可以进行一种类似于 kruskal 重构树的转化：

我们需要重构出一棵树，使得两个点的 LCA 是它们在原树上路径中最大的那个点。具体地，我们先把每个点看作一棵独立的新树，然后我们从小到大枚举每一个点。对于枚举到的点 $u$ ，在原树上找到所有与它有边相连的点，如果 $u$ 与 $v$ 在原树有连边，并且 $u>v$ ，那么我们就可以让 $u$ 成为 $v$ 当前所在新树的根的父亲（使用并查集可以快速找到 $v$ 所在新树的根）。照这样我们就可以把所有的点重新构建出一棵树，这棵重构树就满足上文提到的性质。

重构树构建完了，下面我们就可以把问题变为：一次可以找一对没有祖先关系的两个点，把它们及它们的 LCA 一起标记，问最多的标记次数。

考虑贪心，不难发现如果先标记 LCA 更深的点对一定是不劣的。证明如下：

显然，如果我们要让被标记的点尽量多，那么也就是让没有被标记的点最少，因此我们需要最小化“没用”的点的个数。假设 $u_1$ 是 $u_2$ 的祖先。以 $u_2$ 作为 LCA，最多可以标记两个在 $u_2$ 子树内的节点以及 $u_2$ 本身，而先选 $u_1$ 作为 LCA 只能标记 $u_2$ 子树内的一个点，还使 $u_2$ 少了一个可选项（这可能导致 $u_2$ 没法选两个后代做标记，从而让“没用”的点增多），所以先让 $u_2$ 作为 LCA 去配对是更好的决策。

于是我们只需要记 $f_i$ 表示 $i$ 子树内按照上面的贪心策略尽量多地标记完 $i$ 子树内的点后标记的点对数，记 $r_i$ 表示照上面的贪心策略尽量多地标记完 $i$ 子树内的点后子树内还没有被标记的点的个数。

在决策 $u$ 的匹配时，先考虑 $u$ 的儿子的匹配，然后得到所有儿子 $v$ 的 $r_v$ 。现在知道了所有儿子的 $r_v$ 就可以很简单地判断 $u$ 是否存在两个没标记的属于不同儿子子树的后代，如果存在就让 $u$ 和它们配对。

于是，如果找到了符合条件的两个后代，那么有：
$$
f_u=\sum_{v\in son_u}f_v+1
$$
$$
r_u=\sum_{v\in son_u}r_v-2
$$
否则：
$$
f_u=\sum_{v\in son_u}f_v
$$
$$
r_u=\sum_{v\in son_u}r_v+1
$$
最终的答案显然就是 $f_n$ 了（因为 $n$ 号节点一定是重构树的根）。

参考代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int T,n,fa[N],f[N],rest[N];
vector<int>e[N],g[N];

int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

void dfs(int u){
    int cnt=0;
    for(int v:g[u]){
        dfs(v);
        if(rest[v]>0)cnt++;
        f[u]+=f[v],rest[u]+=rest[v];
    }
    if(cnt>=2)f[u]++,rest[u]-=2;
    else rest[u]++;
}

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        for(int i=1;i<=n;i++)fa[i]=i;
        for(int i=1;i<=n;i++){
            for(int j:e[i]){
                if(j<i){
                    int fj=find(j);
                    fa[fj]=i,g[i].push_back(fj);
                }
            }
        }
        dfs(n);
        printf("%d\n",f[n]);
        for(int i=1;i<=n;i++)f[i]=rest[i]=0,e[i].clear(),g[i].clear();
    }
    return 0;
}
```

---

## 作者：luxiaomao (赞：1)

## [P8852](https://www.luogu.com.cn/problem/P8552) 思维题

好玩的题，~~虽然是参考题解过的~~。

### Problem

给出一棵 $n$ 个点的树，要求最多能找出多少对互不相同的 $a,b,c$，使得 $c$ 的编号是 $a$ 到 $b$ 间简单路径上最大的。

### Solution

考虑用类似重构树的方式换个角度来看树，连边的时候不用双向边，而是让编号大的点作为父亲，向编号小的点连边。

然后我们就发现，在这样的一棵树中，根节点可以作为 $c$，而我们可以从两棵不同的子树中分别找出 $a$ 和 $b$。（如果在同一子树中，$c$ 就不在 $a$ 和 $b$ 之间的简单路径上了）

我们按照从小到大的顺序枚举点，计算如果它作为 $c$ 能否产生一个新的三元组，然后维护一棵子树的“未被标记的节点”的数量，这里使用复杂度很优的并查集。

具体实现请看代码。

### Code

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;

int T,n;

struct edge
{
	int v,nex;
}e[N];
int tot,head[N];
void add(int u,int v)
{
	e[++tot].v = v,e[tot].nex = head[u],head[u] = tot;
}
int fa[N],sz[N],ok[N],ans;
int find(int u)
{
	return u == fa[u]?u:fa[u] = find(fa[u]);
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		tot = ans = 0;
		scanf("%d",&n);
		for(int i = 1;i <= n;i++)
			head[i] = 0,fa[i] = i,sz[i] = ok[i] = 1;
		for(int i = 1;i < n;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			add(max(u,v),min(u,v));
		}
		for(int u = 1;u <= n;u++)
		{
			int cnt = 0;
			for(int i = head[u];i;i = e[i].nex)
			{
				int v = e[i].v;
				v = find(v);
				sz[u] += sz[v];
				ok[u] += ok[v];
				if(ok[v])cnt++;
				fa[v] = u;
			}
			if(cnt >= 2)ok[u] -= 3,ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：1)

## 思路

考虑一个编号为 $i$ 的点什么时候可能成为 $c$。我们可以把这个点作为根，这个问题就被转化为它的所有子树中，是否存在两个点 $a,b$，使得 $a,b$ 不在同一个子树中且 $a\to b$ 上所有点编号小于 $i$。为了解决这一问题，我们在连边时可以由编号大的向编号小的连边，这样点 $i$ 的两个不同的子树中，任取两点一定都能满足条件。接下来问题就变为能否取到了。

如果从编号大的开始考虑，不太好做。所以从编号小的开始考虑。只要它拥有两个及以上还有空闲节点的子树，那么就一定能取到一个三元组，空闲节点就是子树中还没被标记的节点数。同时，以它本身为根的子树空闲节点数要减三。这个过程可以用并查集维护。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct edge{
	int to,nxt;
}e[N];
int T,n,head[N],fa[N],size[N],cnt,ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int find(int x){
	return x==fa[x]?x:fa[x]=find(fa[x]);
}
int main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++)head[i]=0;
		cnt=0;ans=0;
		for(int i=1;i<n;i++){
			int u,v;u=read();v=read();add(max(u,v),min(u,v));
		}
		for(int i=1;i<=n;i++)fa[i]=i,size[i]=1;
		for(int u=1;u<=n;u++){
			int cc=0;
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(find(v)!=find(u)){
					size[find(u)]+=size[find(v)];
					if(size[find(v)]>=1)cc++;
					fa[find(v)]=find(u);
				}
			}
			if(cc>=2){
				ans++;size[u]-=3;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：jockbutt (赞：1)

月赛时想了各种奇怪的打牌，可惜都假了，于是去问了问大佬 [duuuang](https://www.luogu.com.cn/user/552)，董王瞬间把这道题给切了。

## Solution 

对于 $a,b,c$ 这三个数，满足 $ c > a $ 且 $ c > b $，对于 $ c $ 为根的时候，其他节点只需要在不同子树上就行了，具体位置影响不大，而当它不为根时，父亲节点的影响不好处理，而换根不好列出转移方程，非常麻烦。

考虑建一棵树，每个节点的儿子的编号都小于自己，建树时可以用并查集从小到大合并。当枚举到某条边时遇到了比自己祖先大的数字，就连边并合并，最后以 $ n $ 为根节点，就建好了这棵树。

接着，我们可以贪心地选取两个子树上的不同点，如果对于某个点，剩余两个子树，答案就加一，并且将这个子树的 $ size $ 减去三，可以证明，这样的选取方案是最优的。时间复杂度大概是 $O(k \times n)$，$ k $ 是并查集常数。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define INF 1145141919
const int BUFFER=1<<20;
char RB[BUFFER],*RP=RB,*RT=RB;
#define getchar() RP==RT?(RT=RB+fread(RB,1,BUFFER,stdin),RP=RB,*RP++):*RP++
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')	{if(ch=='-')f=-1;ch=getchar();}
	while('0'<=ch&&ch<='9')	{x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n;
const int maxn=2e5+10;
vector <int> G[maxn],e[maxn];
int ans,par[maxn];
int find(int x)	{return x==par[x]?x:par[x]=find(par[x]);}
int sz[maxn];
void dfs(int u)
{
	sz[u]=1;
	int x=0;
	for(int v : e[u])
	{
		dfs(v);
		sz[u]+=sz[v];
		x+=(sz[v]>0);
	}
	if(x>=2)	sz[u]-=3,ans++;
}
inline void solve()
{
	n=read();
	for(int i=1;i<=n;++i)	G[i].clear(),e[i].clear(),par[i]=i;
	for(int i=1,u,v;i<n;++i)
	{
		u=read(),v=read();
		G[u].push_back(v),G[v].push_back(u);
	}
	for(int i=1;i<=n;++i)
	{
		for(int v : G[i])
		{
			int x=find(v);
			if(i>x)	e[i].push_back(x),par[x]=i;
		}
	}
	ans=0;
	dfs(n);
	printf("%d\n",ans);
}
signed main(){
	int T=read();
	while(T--)	solve();
	return 0;
}

/*
1
10
8 6
6 3
3 4
4 7
7 2
2 1
1 10
10 9
9 5

*/
```


---

## 作者：Jordan_Pan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8552)

看到题目，第一反应就是从小到大或者从大到小（废话）。

注意到，路径上有最大的节点的两个点的位置，必须在去掉它之后不连通，即以它为根的不同子树内，于是考虑递归求解：每次找到最大的节点，分别处理割开它之后得到的的几个树，向上合并答案。具体地，如果各子树中有至少两个子树有还没标记过的节点，即可用上这个最大的节点。

我们其实做了这样的事情：  
找最大节点；  
把和它相连的边割掉；  
求解分成的子树的答案；  
算出整棵树的答案。  
两个字：递归，具体实现看代码。

发现割开不好维护，考虑反着操作，即合并。从小到大枚举节点，每次把它和比它小的节点合并。这个东西用并查集即可在常数复杂度内查询根和位于根子树答案、合并。

可能文字讲得不是很清楚，上代码。

~~~cpp
#include<vector>
#include<algorithm>
using namespace std;
const int _=2e5+5;
int n,fa[_],siz[_],ans[_];
vector<int>g[_];
int Fnd(int x){return fa[x]==x?x:fa[x]=Fnd(fa[x]);}
void solve(){
	rd(n);
	for(int u=1;u<=n;u++)
		g[u].clear(),fa[u]=u,siz[u]=1,ans[u]=0;//初始化 
	for(int i=1;i<n;i++){
		int u,v;rd(u),rd(v);
		if(u<v)swap(u,v);
		g[u].push_back(v);//从大向小连边 
	}
	for(int u=1;u<=n;u++){
		int cnt=0;//有还没被标记过的节点的子连通块的数量 
		for(int v:g[u]){
			int x=Fnd(v);
			fa[x]=u;siz[u]+=siz[x];ans[u]+=ans[x];
			if(3*ans[x]<siz[x])cnt++;//注意我们只需要数量 
			//由于从小到大枚举，这里的 u 是最大的 
		}
		if(cnt>=2)ans[u]++;
	}
	printf("%d\n",ans[Fnd(1)]);//最后并成了一整块，找根，输出答案 
}
int main(){
	int T;rd(T);
	while(T--)solve();
	return 0;
}
~~~

十分简短。

---

## 作者：OtoriEmu (赞：0)

考虑构建一棵重构树，满足 $u \to v$ 的路径上最大的点为 $u,v$ 的最近公共祖先。这个构造可以考虑从小到大加点，用并查集维护。

然后现在得到一棵树，每次可以在一个结点以及其子数内的两个结点打上标记。注意到一个结点的不同子树，在这个结点的祖先看来没有区别，因此直接保存下子树内可用的结点数量，如果在一个结点上能匹配则匹配，剩下的上传即可。

[完整实现](https://www.luogu.com.cn/paste/f8b2y01b)。

```cpp
struct unionFindSet{
	int fa[200005];
	void makeSet(int up){for(int i=0;i<=up;++i)	fa[i]=i;}
	int findSet(int x){return x==fa[x]?x:fa[x]=findSet(fa[x]);}
}ufs;
int n;
vector<int> T[200005],G[200005];
int ans;
int dfs(int u)
{
	int sum=1,tr=0;
	for(auto v:G[u])
	{
		int c=dfs(v);
		if(c==0)	continue;
		++tr,sum+=c;
	}
	if(tr>=2 && sum>=3)	++ans,sum-=3;
	return sum;
}
void Solve()
{
	n=read();
	for(int i=1;i<n;++i)
	{
		int u=read(),v=read();
		T[max(u,v)].push_back(min(u,v));
	}
	ufs.makeSet(n);
	for(int i=1;i<=n;++i)
	{
		int u=i;
		for(auto j:T[u])
		{
			int v=ufs.findSet(j);
			G[u].push_back(v);
			ufs.fa[v]=u;
		}
	}
	ans=0;
	dfs(n);
	write(ans),puts("");
	for(int i=1;i<=n;++i)	G[i].clear(),T[i].clear();
}
```

---

## 作者：吴思诚 (赞：0)

# P8552 Rabbit 题解
[题目传送门](https://www.luogu.com.cn/problem/P8552)
## 思路
考虑编号最大的点一定会成为一个 $c$，所以先考虑编号最大的点 $x$，但要怎么选 $a,b$ 呢？可以考虑先删除这个点，裂成很多棵子树，先处理出它的子树，再看子树中有剩下节点的子树个数是否 $\ge 2$（注意这里不是剩余节点个数，因为这个三元组必须包含 $x$）。而这样做的时间复杂度为 $O(n^2)$，可以考虑倒过来做，先把编号小的点处理好，再用并查集慢慢往上连边。而若可以拆除下面的匹配来完成和 $x$ 的匹配是没必要的，因为我们只关心最大匹配数，这样做对答案没有影响。时间复杂度可以做到 $O(n\alpha(n))$，其中 $\alpha(n)$ 是并查集的时间复杂度。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200001;
int T,n,res,f[N],rest[N];
vector<int>g[N];
int find(int x){
	return x==f[x]?x:f[x]=find(f[x]);
}
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)f[i]=i,rest[i]=1,g[i].clear();res=0;
	for(int i=1;i<n;++i){
		int x,y;
		scanf("%d%d",&x,&y);
		g[max(x,y)].push_back(min(x,y));//这种建边的方式是方便加点时代替加边
	}
	for(int k=1;k<=n;++k){
		int c=0;//记录有剩余点没有使用的子树数量
		for(auto v:g[k]){
			c+=!!rest[find(v)];//两次取反等价于rest[find(v)]>0
			rest[k]+=rest[find(v)];//计算总剩余数
			f[find(v)]=k;//连接
		}
		if(c>1)rest[k]-=3,++res;//建立三元组
	}
	printf("%d\n",res);
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：yzy1 (赞：0)

喜 提 最 劣 解 ．

官方题解看不懂．提供一个更加无脑的解法．

考虑分治．每次选择当前子树结点编号最大值作为根，将根从原树中删除，原树划分为若干子树．递归处理各子树．合并时考虑贪心，若至少两个子树中存在没匹配的结点，则将这两个结点和当前结点组成三元组．

最差情况出现在一条编号单调递减的链，上述做法由于每次递归时都需要暴力查询当前子树的编号最大值．时间复杂度为 $O(n^2)$．考虑用数据结构优化上述分治．由于递归时树根在不断变换，每次查询当前子树的最大值不是很好维护．考虑改为每次把不在当前子树内的点推平为 $-\infty$，然后全局查询最大值，单层递归结束时撤销修改．

首先顷定 $1$ 为根，预处理所有点的 DFS 序 $\operatorname{dfn}(i)$ 和每个点子树的大小 $\operatorname{sz}(i)$．

递归时，设当且结点为 $u$，将要处理的儿子 $t$，进行以下讨论：

- 若 $v$ 在以 $1$ 为根情况下是 $u$ 的儿子，则将区间 $[1,\operatorname{dfn}(v)-1]$ 和 $[\operatorname{dfn}(v)+\operatorname{sz}(v),n]$ 推平．
- 若 $v$ 在以 $1$ 为根情况下是 $u$ 的父亲，则将区间 $[\operatorname{dfn}(u),\operatorname{dfn}(u)+\operatorname{sz}(u)-1]$ 推平．

接着查询全局最大值，得到的值就是就是原树删除 $u$ 结点后，$v$ 结点所在的子树中结点编号的最大值．

考虑如何维护上述操作．显然可以直接使用可持久化线段树，但是还存在一种更为简单的方式．注意到每次推平时只会推成 $-\infty$，考虑实现一种标记永久化的线段树，线段树结点维护区间最大值和一个初始为零的计数器 $\mathit{cnt}$．每次区间推平时，将对应的 $O(\log n)$ 个线段树区间对应的结点上的 $\mathit{cnt}$ 自增 $1$．撤销时将对应区间对应的结点上的 $\mathit{cnt}$ 自减 $1$．Push up 时，若左（或右）半区间的 $\mathit{cnt}$ 不为零，则将左（或右）半区间视为最大值为 $-\infty$．由于我们采用了标记永久化，无需 push down．

考虑到这是 A 题，题解有必要包含代码参考．

```cpp
vector<int> e[N];
int n, ans, dfn[N], tim, nfd[N], dep[N], sz[N];
bool ban[N];
vector<pair<int, int>> q;

struct Seg {
  struct T {
    int mx, cnt;
  } d[N << 2];

  inline void Up(int u) {
    if (d[u << 1].cnt && d[u << 1 | 1].cnt)
      d[u].mx = -1e9;
    else if (d[u << 1].cnt)
      d[u].mx = d[u << 1 | 1].mx;
    else if (d[u << 1 | 1].cnt)
      d[u].mx = d[u << 1].mx;
    else
      d[u].mx = max(d[u << 1].mx, d[u << 1 | 1].mx);
  }

  inline void Add(int L, int R, int x, int u, int l, int r) {
    if (L <= l && r <= R) return d[u].cnt += x, void();
    int mid = (l + r) >> 1;
    if (L <= mid) Add(L, R, x, u << 1, l, mid);
    if (mid + 1 <= R) Add(L, R, x, u << 1 | 1, mid + 1, r);
    Up(u);
  }

  inline void Build(int u, int l, int r) {
    d[u].cnt = d[u].mx = 0;
    if (l == r) return d[u].mx = nfd[l], void();
    int mid = (l + r) >> 1;
    Build(u << 1, l, mid);
    Build(u << 1 | 1, mid + 1, r);
    Up(u);
  }
} seg;

inline void Dfs1(int f, int fa) {
  nfd[dfn[f] = ++tim] = f;
  dep[f] = dep[fa] + 1;
  sz[f] = 1;
  each (t, e[f]) {
    if (t == fa) continue;
    Dfs1(t, f);
    sz[f] += sz[t];
  }
}

inline void Fil(int l, int r) { q.push_back({l, r}), seg.Add(l, r, 1, 1, 1, n); }
inline void RB() { seg.Add(q.back().first, q.back().second, -1, 1, 1, n), q.pop_back(); }

inline int F(int f) {
  ban[f] = 1;
  int cnt = 1, dif = 0;
  each (t, e[f]) {
    if (ban[t]) continue;
    int rb = 0;
    if (dep[t] == dep[f] + 1) {
      if (dfn[t] != 1) ++rb, Fil(1, dfn[t] - 1);
      if (dfn[t] + sz[t] != n + 1) ++rb, Fil(dfn[t] + sz[t], n);
    } else
      ++rb, Fil(dfn[f], dfn[f] + sz[f] - 1);
    int ne = seg.d[1].mx;
    ++rb, Fil(dfn[ne], dfn[ne]);
    int tmp = F(ne);
    if (tmp) cnt += tmp, ++dif;
    while (rb--) RB();
  }
  if (dif >= 2) cnt -= 3, ++ans;
  return cnt;
}

inline void Work() {
  q.clear();
  tim = ans = 0;
  cin >> n;
  re (i, n - 1) {
    int f, t;
    cin >> f >> t;
    e[f].push_back(t), e[t].push_back(f);
  }
  Dfs1(1, 0);
  seg.Build(1, 1, n);
  int x = seg.d[1].mx;
  Fil(dfn[x], dfn[x]);
  F(x);
  cout << ans << '\n';
  re (i, n) e[i].clear(), ban[i] = 0;
}
```


---

