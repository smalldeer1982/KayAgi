# 迷い猫 (Stray Cat)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2020/tasks/joisc2020_i

配布ファイルは [こちら](https://www.ioi-jp.org/camp/2020/2020-sp-tasks/index.html) ．

C++ を使用する場合，`stray.h` を include し，すべての関数を 1 つのファイル内で実装してください．AtCoder の仕様上グローバル変数の共有が可能ですが，自粛してください．

このジャッジは C++ 以外に対応していません．

# 题解

## 作者：DaiRuiChen007 (赞：2)

# JOISC2020I 题解

[Problem Link](https://qoj.ac/problem/3560)

**题目大意**

> 通信题：
>
> - `Anthony.cpp`：给定一张 $n$ 个点 $m$ 条边的无向图，给每条边一个 $[0,A)$ 之间的标记。
> - `Catherine.cpp`：每次可以知道当前节点所有出边的标记（不包括来时的边），选定一个标记，随机走一条这个标记的边，或者原路返回。
>
> 要求对于任意一个起点 $u$，`Catherine.cpp` 总能在 $dis(0,u)+b$ 次移动内到达 $0$。
>
> 数据范围：$n,m\le 20000$，$a=3,b=0$ 或 $a=2,b=6,m=n-1$。

**思路分析**

先考虑 $a=3,b=0$ 的情况：

假如原图是一棵树，那么很好解决，对于每层的边，我们依次染 $0,1,2$，那么 `Catherine.cpp` 每次就会得到 $(0,1),(1,2),(2,0)$，很好判断哪条向上哪条向下。

假如原图不是树，那么考虑建出 BFS 树，对于相邻两层之间的边按 $0,1,2$ 顺次染，同层的边和下行边染同种颜色，这样就能保证每次都走上行边。

然后考虑 $a=2,b=6,m=n-1$ 的情况：

考虑朴素做法，对于每层的边交替染 $0,1$，我们把儿子到父亲的边称为上行边，父亲到儿子的边称为下行边。

容易发现起点不在链上的时候，一定能分出第一步的上下，而后面的上下也随之确定了：

- 假如只有一个标记出现了 $1$ 次，那么显然这条边就是上行边。
- 假如两个标记都只出现了 $1$ 次，那么和上一次移动不同的标记是上行边。

因此我们只要保证，每个点上行边和下行边颜色不同，那么我们一旦走出了一步正确的移动，那么就可以直接找到一条最短路。

因此我们只要解决第一步在链上的情况。

考虑把链上的边染成一个特殊的串，使得我们往一个方向走若干步后就能发现我们的运动方向到底是正还是反。

注意到 $b=6$，因此我们至多可以向某个方向走 $3$ 步，算上两端的一共是五条边，因为我们只要要求任意位置开始正着读五位始终与反着读五位不相同，可以构造出 $(001101)^\infty$ 满足条件。

如果链顶是 $0$ 就从第一位开始，否则从第三位开始不断填链，如果是非链节点就 $0,1$ 交替填。

注意特判没走够三步就到链外的情况。

时间复杂度 $\mathcal O(n+m)$。

**代码呈现**

`Anthony.cpp`：

```cpp
#include<bits/stdc++.h>
#include "Anthony.h"
using namespace std;
namespace {
const int MAXN=2e4+5;
namespace Task0 {
int dep[MAXN];
vector <int> G[MAXN];
inline vector<int> main(int n,int m,vector<int>&u,vector<int>&v) {
	for(int i=0;i<m;++i) G[u[i]].push_back(v[i]),G[v[i]].push_back(u[i]);
	queue <int> Q; Q.push(0),dep[0]=1;
	while(Q.size()) {
		int x=Q.front(); Q.pop();
		for(int y:G[x]) if(!dep[y]) dep[y]=dep[x]+1,Q.push(y);
	}
	vector <int> w(m);
	for(int i=0;i<m;++i) w[i]=min(dep[u[i]],dep[v[i]])%3;
	return w;
}
}
namespace Task1 {
vector <int> w;
struct Edge { int v,id; };
vector <Edge> G[MAXN];
const int arr[]={0,0,1,1,0,1};
inline void dfs(int u,int fa,int len,int col) {
	if(fa==-1) {
		for(auto e:G[u]) w[e.id]=0,dfs(e.v,u,G[u].size()==1,1);
	} else if(G[u].size()==2) {
		if(len==0&&col==1) len=2;
		for(auto e:G[u]) if(e.v^fa) w[e.id]=arr[len%6],dfs(e.v,u,len+1,w[e.id]^1);
	} else {
		for(auto e:G[u]) if(e.v^fa) w[e.id]=col,dfs(e.v,u,0,col^1);
	}
}
inline vector<int> main(int n,int m,vector<int>&u,vector<int>&v) {
	for(int i=0;i<m;++i) G[u[i]].push_back({v[i],i}),G[v[i]].push_back({u[i],i});
	w.resize(m),dfs(0,-1,0,0);
	return w;
}
}
}
vector<int> Mark(int N,int M,int A,int B,vector<int> U,vector<int> V) {
	if(A>=3) return Task0::main(N,M,U,V);
	else return Task1::main(N,M,U,V);
}
```

`Catherine.cpp`：

```cpp
#include<bits/stdc++.h>
#include "Catherine.h"
using namespace std;
namespace {
bool task;
namespace Task0 {
inline int Move(vector<int>&g) {
	int cnt=0,s=0;
	for(int i:{0,1,2}) if(g[i]) ++cnt,s+=i;
	assert(cnt);
	if(cnt==1) return s;
	else return (4-s)%3; //f(0,1)=0, f(1,2)=1, f(2,0)=2
}
}
namespace Task1 {
const vector<int> mod[6]={{0,0,1,1,0},{0,1,1,0,1},{1,1,0,1,0},
						  {1,0,1,0,0},{0,1,0,0,1},{1,0,0,1,1}};
int lst=-1,chk=0;
vector <int> pat;
inline int solve(vector<int>&g) {
	if(lst==-1) { //first move
		if(g[0]+g[1]==2) { //chain
			if(g[0]==2) return pat={0,0},0;
			if(g[1]==2) return pat={1,1},1;
			return pat={0,1},1;
		} else { //tree
			chk=1;
			if(!g[0]||!g[1]) return g[0]?0:1;
			return (g[0]==1)?0:1;
		}
	}
	if(!g[0]&&!g[1]) return chk=1,-1; //leaf
	if(!chk) {
		if(g[0]+g[1]>1) { //tree
			++g[lst],chk=1;
			if(g[0]==1&&lst!=0) return 0;
			if(g[1]==1&&lst!=1) return 1;
			return -1;
		}
		pat.push_back(g[0]?0:1); //chain
		if(pat.size()==5) {
			chk=1;
			for(int x:{0,1,2,3,4,5}) if(pat==mod[x]) return -1; //reverse
			return pat.back();
		} else return pat.back();
	} else {
		if(!g[0]||!g[1]) return g[0]?0:1; //chain
		if(g[0]==1&&g[1]==1) return lst^1; //3-deg
		return g[0]==1?0:1; //other
	}
}
inline int Move(vector<int>&g) { return lst=solve(g); }
}
}
void Init(int A,int B) { task=(A==2); }
int Move(vector<int> y) { return task?Task1::Move(y):Task0::Move(y); }
```





---

