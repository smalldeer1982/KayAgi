# Game in Tree (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, $ \mathbf{u = v} $ . You can make hacks only if both versions of the problem are solved.

Alice and Bob are playing a fun game on a tree. This game is played on a tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . Recall that a tree with $ n $ vertices is an undirected connected graph with $ n - 1 $ edges.

Alice and Bob take turns, with Alice going first. Each player starts at some vertex.

On their turn, a player must move from the current vertex to a neighboring vertex that has not yet been visited by anyone. The first player who cannot make a move loses.

You are given two vertices $ u $ and $ v $ . Represent the simple path from vertex $ u $ to $ v $ as an array $ p_1, p_2, p_3, \ldots, p_m $ , where $ p_1 = u $ , $ p_m = v $ , and there is an edge between $ p_i $ and $ p_{i + 1} $ for all $ i $ ( $ 1 \le i < m $ ).

You need to determine the winner of the game if Alice starts at vertex $ 1 $ and Bob starts at vertex $ p_j $ for each $ j $ (where $ 1 \le j \le m $ ).

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2013F1/e1cf544a0db6c078ce895e1ac7918ee5810cf6b5.png) Tree from the first and second examples.In the first test case, the path will be ( $ 2,2 $ ). Bob starts at vertex $ 2 $ , Alice will not be able to move anywhere on her first turn and will lose.

In the second test case, the path will be ( $ 3,3 $ ). Bob starts at vertex $ 3 $ , Alice will move to vertex $ 2 $ , and Bob will have no remaining vertices to visit and will lose.

## 样例 #1

### 输入

```
3
3
1 2
2 3
2 2
3
1 2
2 3
3 3
6
1 2
1 3
2 4
2 5
1 6
4 4```

### 输出

```
Bob
Alice
Alice```

# 题解

## 作者：DerrickLo (赞：0)

我们考虑每个人的决策。

记 $1$ 到 $x$ 的路径上的点构成的序列为 $b_1\sim b_m$，那么假设现在 Alice 在 $l$，Bob 在 $r$，那么对于 Alice 来说，如果她要从此不再走 $1$ 到 $x$ 这条路径，那么就必须满足往其他地方走能走的最大步数要大于 Bob 在 $[l+1,r]$ 处往其他地方走的最大步数，对于 Bob 也是类似。我们发现后面那个东西是一个区间最大值，所以可以预处理出每个点如果不走 $b_1\sim b_m$ 这些点所能走到的最远点，然后直接使用 st 表维护区间最大值即可。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h> 
using namespace std;
int t,n,a,b,u,v,st1[200005][25],st2[200005][25],fa[200005],c[200005],vis[200005],f[200005];
vector<int>ve[200005];
void dfs(int u,int f){
	fa[u]=f;
	for(int v:ve[u]){
		if(v==fa[u])continue;
		dfs(v,u);
	}
}
void dfs1(int u){
	f[u]=1;
	for(int v:ve[u]){
		if(v==fa[u])continue;
		dfs1(v);
	}
	for(int v:ve[u]){
		if(v==fa[u]||vis[v])continue;
		f[u]=max(f[u],f[v]+1);
	}
}
int query1(int l,int r){
	int k=__lg(r-l+1);
	return max(st1[l][k],st1[r-(1<<k)+1][k]);
}
int query2(int l,int r){
	int k=__lg(r-l+1);
	return max(st2[l][k],st2[r-(1<<k)+1][k]);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)ve[i].clear(),vis[i]=f[i]=0;
		for(int i=1;i<n;i++)cin>>u>>v,ve[u].emplace_back(v),ve[v].emplace_back(u);
		cin>>a>>b;
		dfs(1,0);
		int now=a,cnt=0;
		while(now)vis[now]=1,c[++cnt]=now,now=fa[now];
		dfs1(1);
		for(int i=1;i<=cnt;i++)st1[i][0]=i-1+f[c[i]]-1,st2[i][0]=cnt-i+f[c[i]]-1;
		for(int i=1;i<=20;i++)for(int j=1;j+(1<<i)-1<=cnt;j++){
			st1[j][i]=max(st1[j][i-1],st1[j+(1<<i-1)][i-1]);
			st2[j][i]=max(st2[j][i-1],st2[j+(1<<i-1)][i-1]);
		}
		int l=1,r=cnt,noww=0,flag=0;
		while(l<r){
			if(noww==0){
				int cnt1=f[c[r]]-1;
				int cnt2=query1(l,r-1)-(l-1);
				if(cnt1>cnt2){
					cout<<"Alice\n";flag=1;
					break;
				}
				r--;
			}
			else{
				int cnt1=f[c[l]]-1;
				int cnt2=query2(l+1,r)-(cnt-r);
				if(cnt1>cnt2){
					cout<<"Bob\n";flag=1;
					break;
				}
				l++;
			}
			noww^=1;
		}
		if(!flag)cout<<(noww?"Bob\n":"Alice\n");
	}
}
```

---

