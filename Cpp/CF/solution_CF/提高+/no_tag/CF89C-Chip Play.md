# Chip Play

## 题目描述

有一个大小为n×m的矩形场，这个矩形场的某些地方有筹码，皆处于行与列上。
每个筹码上都有一个箭头。因此，场上的每个筹码都指向以下方向之一：上，下，左或右。

玩家可以选择一个筹码并开始行动。

以下是一次动作顺序：

1.所选筹码被标记为当前的筹码。

2.检查当前筹码的箭头指向方向的同一行（或同一列）的筹码。如果至少有一个，则将最近的筹码标记为新的当前筹码。

3.将先前的当前筹码从场中移除。

4.重复此过程。如果未找到新筹码，则将当前筹码从场地中移出，玩家的移动结束。

在移动结束时，玩家会获得分数，分数等于已移除筹码的数量。

要求找到最优的初始筹码安排，确定你在一次行动中可获得的最大分数并确定有几种方案能达成。

## 说明/提示

在第一个样例中，初始筹码在位置（3,3）（3,3），即可获得最大点数。 您可以在下图看到它的方案：
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF89C/564cfdc234dcf38266b456e2e5fec700d68e459e.png)

其它方案将会有更差结果

## 样例 #1

### 输入

```
4 4
DRLD
U.UL
.UUR
RDDL
```

### 输出

```
10 1```

## 样例 #2

### 输入

```
3 5
.D...
RRRLL
.U...
```

### 输出

```
6 2```

# 题解

## 作者：7KByte (赞：0)

首先 $n\times m \le 5000$，可以知道是个 $O(n^2m^2)$ 可过的题。

估计一下，如果我们枚举起点，然后再对整张棋盘模拟一下，可以得到一个复杂度为 $O(n^2m^2)$ 的算法。

关键在于如何快速模拟这个移动和删除的过程。

不难发现移动就是求前驱和后继，使用双向链表可以快速维护删除，查询和恢复操作。

因为我们的恢复操作是在$\rm DFS$回溯的时候进行，所以这样做是正确的。

注意链表不仅要维护每一行，还要维护每一列。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 5005
using namespace std;
int n,m;
char s[N][N];
vector<int>up[N],dn[N],lt[N],rt[N];
//int up[N][N],dn[N][N],lt[N][N],rt[N][N];
void del(int x,int y){
	dn[up[x][y]][y]=dn[x][y];
	up[dn[x][y]][y]=up[x][y];
	rt[x][lt[x][y]]=rt[x][y];
	lt[x][rt[x][y]]=lt[x][y];
}
void ins(int x,int y){
	dn[up[x][y]][y]=x;
	up[dn[x][y]][y]=x;
	rt[x][lt[x][y]]=y;
	lt[x][rt[x][y]]=y;
}
int dfs(int x,int y){
	int ans=1;
	if(s[x][y]=='U'){
		int cur=up[x][y];
		if(cur)del(x,y),ans+=dfs(cur,y),ins(x,y);
	}
	else if(s[x][y]=='D'){
		int cur=dn[x][y];
		if(cur!=n+1)del(x,y),ans+=dfs(cur,y),ins(x,y);
	}
	else if(s[x][y]=='L'){
		int cur=lt[x][y];
		if(cur)del(x,y),ans+=dfs(x,cur),ins(x,y);
	}
	else if(s[x][y]=='R'){
		int cur=rt[x][y];
		if(cur!=m+1)del(x,y),ans+=dfs(x,cur),ins(x,y);
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)scanf("%s",s[i]+1);
	rep(i,0,n+1)up[i].resize(m+3),dn[i].resize(m+3),lt[i].resize(m+3),rt[i].resize(m+3);
	rep(i,1,n){
		int pre=0;
		rep(j,1,m)if(s[i][j]!='.')rt[i][pre]=j,lt[i][j]=pre,pre=j;
		rt[i][pre]=m+1;lt[i][m+1]=pre;
	}
	rep(j,1,m){
		int pre=0;
		rep(i,1,n)if(s[i][j]!='.')dn[pre][j]=i,up[i][j]=pre,pre=i;
		dn[pre][j]=n+1;up[n+1][j]=pre;
	}
	int ans=0,mx=0;
	rep(i,1,n)rep(j,1,m)if(s[i][j]!='.'){
		int cur=dfs(i,j);
		if(cur>mx)mx=cur,ans=1;
		else if(cur==mx)ans++;
	}
	printf("%d %d\n",mx,ans);
	return 0;
}
```

---

