# [PA 2024] Alchemik Bajtazar

## 题目背景

PA 2024 2B

## 题目描述

**题目译自 [PA 2024](https://sio2.mimuw.edu.pl/c/pa-2024-1/dashboard/) Runda 2 [Alchemik Bajtazar](https://sio2.mimuw.edu.pl/c/pa-2024-1/p/alc/)**

Byteasar 是一位著名的炼金术士，为了解决材料的嬗变问题，他暂时放下了制造贤者石的尝试。具体来说，Byteasar 想把一种分子转化成另一种。Byteasar 所拥有的分子由 $n$ 个 bytonium 原子组成（在 Byteotia，bytonium 是最常用的化学元素之一，主要用于生产食品和隐形眼镜），这些原子从 $1$ 到 $n$ 编号。某些原子对之间可能存在键，但每对原子之间最多只有一个键。这些分子形成了一个连贯的整体——从每个原子出发，通过一个或多个键就可以到达其他任何原子。

Byteasar 描述了他希望得到的 $n$ 个原子的分子中的键——对于每一对原子，他都知道是否希望它们最终由键连接。目标分子满足同样的条件——它形成一个连贯的整体，每对原子最多由一个键连接。不幸的是，Byteasar 的分子可能与目标分子不同。为了解决这个问题，他可以使用自己的炼金术能力。他可以随时进行两种可能的操作之一：

- Byteasar 可以选择没有键连接的两个不同原子 $a$ 和 $b$，并在它们之间形成键。由于 bytonium 的高度不稳定性，只有当前存在与 $a$ 和 $b$ 都成键的原子 $c$（不同于 $a$ 和 $b$），他才可以这样做。
- Byteasar 可以选择通过键连接的两个不同原子 $a$ 和 $b$，并移除连接它们的键。出于类似的原因，只有当前存在与 $a$ 和 $b$ 都成键的原子 $c$（不同于 $a$ 和 $b$），他才可以这样做。

Byteasar 不想在转化上花费太多时间。请编写一个程序，帮助他将自己的分子转化为目标分子，并在最多 $200\, 000$ 次操作中完成。

注意：原子两两不同，可以区分。

## 说明/提示

请注意，Byteasar 无法立即连接第一个原子与第四个原子，因为当时没有原子与它们两个相连。通过在第一个和第三个原子之间建立临时键，Byteasar 就使该原子成为了第三个原子。

## 样例 #1

### 输入

```
4
3
1 2
3 4
3 2
4
1 4
1 2
2 3
3 4
```

### 输出

```
3
+ 1 3
+ 1 4
- 3 1
```

# 题解

## 作者：yuanruiqi (赞：0)

考虑先连接辅助键 $(1,2),(1,3),\dots,(1,n)$，连接顺序可以按照原图上 dfs 遍历的顺序。先加入并删除与 $1$ 不相连的键。最后考虑删除与 $1$ 相连的辅助键，可以按照新图上的 dfs 倒序。

---

## 作者：六楼溜刘 (赞：0)

### 题意

- 构造题。
- 有一张 $n$ 个点 $m_s$ 条边的连通图 $G_1$，你要进行一些操作把它变成另一张 $n$ 个点 $m_d$ 条边的连通图 $G_2$。
- 有两个操作，加边和删边。能在两个点 $a,b$ 之间加边/删边当且仅当存在一个结点 $c$ 同时与两者直接相连。
- 你要用不超过 $2\times 10^5$ 次操作完成这个任务。
- $1\le n \le 3\times 10^4,n-1\le m_s,m_d\le 5\times 10^4$

### 题解

现在有很多人喜欢出这种题，出道图论题但是出成构造，防止错误复杂度卡常卡过去。但是这道题比较简单，而且还是比较偏构造。

注意到操作数是 $O(n)$（或者说 $O(m)$，这道题 $n,m$ 数据规模差不多）级别的，这大大的限制了可用的算法，考虑有什么图上的 $O(n)$ 算法。

容易想到 dfs/bfs，可以按照由浅到深的顺序把所有点连在同一个点上，这样任意两个点之间都能有这个点作为中间点。然后把端点不为这个点的边该加的加上该删的删掉，最后由深到浅来删掉这个点上多连的边。

注意删边的时候应在 $G_2$ 上遍历。

复杂度 $O(n)$（指操作数和实际上的时间复杂度）。

### code

```cpp
//代码写的很屎，不要参考

using namespace std;
using pii=pair<int,int>;
#define fi first
#define se second
#define mkp make_pair
#define gc getchar()
inline int read(){
    int x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const int N=30005,inf=0x3f3f3f3f;
int n,m1,m2,vis[N];
set<pii> s1,s2;
vector<int> e[N];
struct Node{
	bool op;
	int x,y;
};
vector<Node> ans;
void dfs(int x){
	if(x!=1&&!s1.count(mkp(1,x))){
		ans.push_back(Node{1,1,x});
	}
	vis[x]=1;
	for(auto i:e[x]){
		if(!vis[i]){
			dfs(i);
		}
	}
}
void dfs2(int x){
	vis[x]=0;
	for(auto i:e[x]){
		if(vis[i]){
			dfs2(i);
		}
	}
	if(x!=1&&!s2.count(mkp(1,x))){
		ans.push_back(Node{0,1,x});
	}
}
signed main(){
	n=read();
	m1=read();
	forup(i,1,m1){
		int u=read(),v=read();
		if(u>v) swap(u,v);
		s1.insert(mkp(u,v));
		e[u].push_back(v);
		e[v].push_back(u);
	}
	m2=read();
	forup(i,1,m2){
		int u=read(),v=read();
		if(u>v) swap(u,v);
		s2.insert(mkp(u,v));
	}
	dfs(1);
	for(auto i:s2){
		if(i.fi==1) continue;
		if(!s1.count(i)){
			ans.push_back(Node{1,i.fi,i.se});
		}
	}
	for(auto i:s1){
		if(i.fi==1) continue;
		if(!s2.count(i)){
			ans.push_back(Node{0,i.fi,i.se});
		}
	}
	forup(i,1,n) e[i].clear();
	for(auto i:s2){
		e[i.fi].push_back(i.se);
		e[i.se].push_back(i.fi);
	}
	dfs2(1);
	printf("%d\n",(int)ans.size());
	for(auto i:ans){
		printf(i.op?"+ %d %d\n":"- %d %d\n",i.x,i.y);
	}
}
```

---

