# Game on Tree (Easy)

## 题目描述

这是该问题的简单版本。本版本的区别在于 $t=1$，并且我们在一个类似数组的树上进行操作。

Ron 和 Hermione 正在一棵有 $n$ 个节点的树上玩游戏，所有节点初始均为未激活状态。这棵树很特殊，因为它恰好有两个叶子节点，因此可以看作是一条链（数组）。游戏共进行 $t$ 轮，每一轮开始时，恰好有一个节点上放有一块石头，该节点被视为已激活。每一步操作可以选择石头所在节点的一个未激活的相邻节点，并将石头移动到该节点上（从而激活该节点）。Ron 先手，之后两人轮流操作，直到无法进行有效操作为止。无法行动的一方输掉本轮游戏。如果双方都采取最优策略，问每一轮游戏谁会获胜？

注意，所有轮次都在同一棵树上进行，仅初始放置石头的节点不同。此外，每轮结束后，所有已激活的节点都会重新变为未激活状态。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 1
2 3
3 1
3```

### 输出

```
Ron```

## 样例 #2

### 输入

```
5 1
1 2
2 3
3 4
4 5
5```

### 输出

```
Hermione```

# 题解

## 作者：OIer_Hhy (赞：1)

这道题我用的是 DFS。

首先，用一个邻接表表示这棵树。

接着直接搜索。用一个 `flag` 表示当前选手能否移动。当一方无路可走时，另一方就赢了。

显然，若罗恩有任意一种胜利的方法，赫敏必输。

所以我们可以用一个变量记录罗恩能否胜利，找到一种罗恩胜利的方法就退出 DFS 搜索。

代码如下：
```cpp
#include<bits/stdc++.h>
#define HERMIONE 0
#define RON 1
using namespace std;
int n,t,a[200010];
vector<int> g[200010];
bool vis[200100];
int x,y;
string ans="Hermione"; 
void dfs(int x,bool now){
	if(ans=="Ron") return ;
	int flag=1;
	for(int i=0;i<g[x].size();i++){
		if(!vis[g[x][i]]){
			flag=0;
			vis[g[x][i]]=1;
			if(now==RON) dfs(g[x][i],HERMIONE);
			else dfs(g[x][i],RON);
			vis[g[x][i]]=0;
		}
	}
	if(flag){
		if(now==HERMIONE)
			ans="Ron";
		return ;
	}
}
signed main(){
	cin>>n>>t;
	for(int i=1;i<n;i++){
		cin>>x>>y;	
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i=1;i<=t;i++) cin>>a[i];
	for(int i=1;i<=t;i++){
		memset(vis,0,sizeof vis);
		ans="Hermione";
		vis[a[i]]=1;
		dfs(a[i],RON);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

