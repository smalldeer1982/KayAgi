# Game on Tree (Medium)

## 题目描述

这是该问题的中等难度版本。本版本的区别在于 $t=1$，并且我们操作的是树结构。

Ron 和 Hermione 在一棵有 $n$ 个节点的树上玩游戏，所有节点初始均为未激活状态。游戏包含 $t$ 轮，每一轮开始时有一颗石子放在某个节点上，该节点被视为已激活。每一步操作可以选择石子所在节点的一个未激活的相邻节点，并将石子移动到该节点（从而激活该节点）。Ron 先手，之后两人轮流操作，直到无法进行有效操作为止。无法操作的一方输掉本轮。如果双方都采取最优策略，问每一轮谁会获胜？

注意，所有轮次都在同一棵树上进行，只是起始节点不同。此外，每轮结束后，所有已激活的节点都会重新变为未激活状态。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 1
1 2
1 3
3 4
3 5
1```

### 输出

```
Ron```

# 题解

## 作者：Vct14 (赞：2)

我们把起始节点当作树根。那么每一次移动都只能是父节点移动到子节点。考虑每个节点的必胜态。叶子节点显然必败。对于任意一个非叶子节点：
- 如果它的儿子全部是必胜节点，则它是必败节点；
- 否则，它是必胜节点。

用一个变量 $f_u=0/1$ 表示 $u$ 节点的是否必败，即若 $u$ 必胜则为 $0$，$u$ 节点必败则为 $1$。则有 $f_u=\prod\limits_{v\in son(u)}(1-f_v)$。递归求解即可。时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+2;
vector<int> G[N];

int dfs(int x,int fa){
	int ans=1;
	for(int i : G[x]){
		if(i==fa) continue;
		ans*=(1-dfs(i,x));
	}
	return ans;
}

int main(){
	int n,t;cin>>n>>t;
	for(int i=1; i<=n-1; i++){
		int u,v;cin>>u>>v;
		G[u].push_back(v);G[v].push_back(u);
	}
	int x;cin>>x;
	puts(dfs(x,0)?"Hermione":"Ron");
	return 0;
}
```

---

## 作者：shicj (赞：1)

# CF1970C2 Game on Tree (Medium) 题解

## 0x00 题目大意

给出一棵树，在一个点上放一个棋子，两人轮流移动棋子到相邻位置，不可重复经过某个点，两人决策最优，问谁获胜。

## 0x01 初步分析

看一下样例，画个图分析一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/0io4uryf.png)

然后看一下可以怎样移动：

![](https://cdn.luogu.com.cn/upload/image_hosting/zfpmlecn.png)

发现每一条路径都去往叶子节点，显而易见，每个叶子节点的状态是确定的：

![](https://cdn.luogu.com.cn/upload/image_hosting/m74g6b5a.png)

这个状态可以很快求出，接下来研究如何向上转移。

## 0x02 深入分析

由于叶子节点状态已知，所以考虑自底向上分析。

在这里，每一个节点上由谁选择（移到下一个点）很重要，我们用绿色字体标出每个节点上由谁选择：

![](https://cdn.luogu.com.cn/upload/image_hosting/rzxr6l98.png)

可以看出，由谁选择取决于节点的深度。

易得，在最优决策中，总是要选择可以使得自己获胜的点，如果没有，则在这一点上出发对方获胜，否则自己获胜。

于是可以自底向上标出每一个点上的获胜者：

![](https://cdn.luogu.com.cn/upload/image_hosting/o61pt5b6.png)

这时看一看起始节点上谁获胜就行了。

# 0x03 具体实现

在代码中，可以如图中用字符表示状态（这样直观但代码量大），但更推荐用布尔值来实现，这样可以把判断获胜者的运算转化为深度模 $2$ 和逻辑运算，具体的写法可以自己琢磨。

求获胜者的步骤可以直接写在搜索的回溯部分，这样便于实现。

# 0x04 正确代码

建议略过这部分，自己思考。

[link](https://codeforces.com/problemset/submission/1970/272718480)

---

