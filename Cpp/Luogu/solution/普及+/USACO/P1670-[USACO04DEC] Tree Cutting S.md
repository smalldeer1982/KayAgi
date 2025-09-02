# [USACO04DEC] Tree Cutting S

## 题目描述

约翰意识到贝茜建设网络花费了他巨额的经费，就把她解雇了。贝茜很愤怒，打算狠狠报复。她打算破坏刚建成的约翰的网络。约翰的网络是树形的，连接着 $N$ 个牛棚。她打算切断某一个牛棚的电源，使和这个牛棚相连的所有电缆全部中断。之后，就会存在若干子网络。为保证破坏够大，每一个子网的牛棚数不得超过总牛棚数的一半，那哪些牛棚值得破坏呢？

## 说明/提示

$1\le N\le 10^4$。

## 样例 #1

### 输入

```
10
1 2
2 3
3 4
4 5
6 7
7 8
8 9
9 10
3 8```

### 输出

```
3
8
```

# 题解

## 作者：MoonCake2011 (赞：7)

# 前置知识：[树的重心](https://blog.csdn.net/qiancm/article/details/118856915)

此题呢是可以 $n$ 次 `dfs`，以 $\text O(n^2)$ 的时间复杂度求解的。

但，这只是常规做法。

众所周知，树的重心可以以一次 `dfs` 以玄妙的方式求解**以一个节点为根的最大子树大小**。

这不是这道题需要去比较的吗？

我们把**以一个节点为根的最大子树大小**存在一个数组里面，再以一个循环比较输出就行了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int head[10010],to[20010],nxt[20010],tot;
void add(int u,int v){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
int dp[10010],siz[10010];
void dfs(int x,int fa){
	siz[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		if(to[i]==fa) continue;
		dfs(to[i],x);
		siz[x]+=siz[to[i]];
		dp[x]=max(dp[x],siz[to[i]]);
	}
	dp[x]=max(dp[x],n-siz[x]);
}
int main() {
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs(1,0);
	int mid=n>>1,cnt=0;
	for(int i=1;i<=n;i++)
		if(dp[i]<=mid)
			cnt++,cout<<i<<"\n";
	if(!cnt) cout<<"NONE";
	return 0;
} 
```

---

## 作者：2021changqing52 (赞：6)

### 思路
我们可以做一遍 DFS 来找出每个节点的儿子，然后算出以每个节点为根的子树的大小，再枚举牛棚检查是否可以。
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d[10005];
vector<int>e[10005],son[10005];
void dfs(int u,int fa){//DFS
	d[u]=1;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(v==fa)continue;
		dfs(v,u);
		son[u].push_back(v);
		d[u]+=d[v];
	}
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,-1);
	int w=1;
	for(int i=1;i<=n;i++){
		bool f=1;//检查
		for(int j=0;j<son[i].size();j++){
			int u=son[i][j];
			if(d[u]>n/2){
				f=0;
				break;
			}
		}
		if(d[i]>=n/2&&f)cout<<i<<endl,w=0;
	}
	if(w)puts("NONE");
	return 0;
}
```


---

## 作者：Miku_QwQ (赞：4)

### 这是蒟蒻的第一篇题解，有错误请指出。

[题目传送门](https://www.luogu.com.cn/problem/P1670)

# 本题芝士：[树的重心](https://oi-wiki.org/graph/tree-centroid/)

## 题意简述：
给定一棵 $N$ 个节点的 __无根树__ 。现在要找到所有的节点，使得删除这个节点之后，剩余的所有连通块中 __最大__ 连通块的大小 $S \leq \frac{N}{2}$。

## 解题思路
观察题意，发现删去的节点性质与树的 __重心__ 一模一样。所以本题即为求解树的重心。

### $O(n^{2})$ 做法

枚举每个点，找到以它的邻接点为根的子树进行 dfs，最后进行一个判断就可以了。

代码蒟蒻就不贴了。~~虽然吸个氧好像是能过的，但这并不是蒟蒻想要介绍的正解。~~

### $O(n)$ 做法

我们发现，对于一棵 __有根树__ ，删去一个节点 $a$ 后所有的连通块有以下两种：

- $a$ 的所有子树

- $a$ 的父节点往上构成的连通块

其中 $a$ 的子树的大小可以一边 dfs 预处理求出，而 $a$ 的父节点往上构成的连通块的大小可以反向思考。

我们发现：向上连通块的大小即为总的节点个数减去以 $a$ 为根的子树节点数。

所以，对于无根树的处理，方法来了：

先任意指定一个节点作为 __无根树的根__ ，一遍 dfs 把这棵无根树处理成有根树。

接下来进行第二次 dfs，处理出以每个节点为根的子树大小。

最后枚举每个点，进行判断即可。注意特判无解情况，输出 ```NONE```。

## 代码实现

题目中并没有说电缆的两端一定是按父子关系给出的，所以蒟蒻就按无根树来处理了。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
vector<int> G[10010],Tree[10010];//G：无根树 Tree：有根树
int s[10010];//大小
bool vis[10010];//构建无根树的标记
void dfs(int u){//构建无根树
	vis[u]=true;
	for(int i=0;i<G[u].size();i++){
		if(!vis[G[u][i]]){
			Tree[u].push_back(G[u][i]);
			dfs(G[u][i]);
		}
	}
}
void DFS(int u){//预处理子树大小
	s[u]=1;
	for(int i=0;i<Tree[u].size();i++){
		DFS(Tree[u][i]);
		s[u]+=s[Tree[u][i]];
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1);
	DFS(1);
	bool flag=false;
	for(int i=1;i<=n;i++){
		int maxn=0;
		for(int j=0;j<Tree[i].size();j++){//找下方连通块
			maxn=max(maxn,s[Tree[i][j]]);
		}
		maxn=max(maxn,n-s[i]);//找上方连通块
		if(maxn*2<=n){
			printf("%d\n",i);
			flag=true;//标记
		}
	}
	if(flag==false){//特判
		printf("NONE");
	}
	return 0;
}
```

然后：

![](https://www.luogu.com.cn/images/congratulation.png)

---

## 作者：xxxxxzy (赞：1)

#### P1670的题解

树的重心的模板题。

首先，树的重心的定义：删除后使产生的最大部分最小的点。

而题目目标就是要求出删除所有点后的最大子树。

暴力一个点一个点枚举是 $O(n^{2})$ 的时间复杂度，不多赘述，下面介绍 $O(n)$ 的算法：

删除一个点后，剩余的部分必然分为两类：

- 一类是它的所有以子节点为根的子树

- 另一类是去掉以它为根的子树的树

对于第一类情况，只需要递归枚举即可；

对于第二类情况，只需要处理完第一类情况后，用总结点减去当前子树的节点总和就是剩余的大小。

所以所有点都只用遍历一遍，也就是 $O(n)$ 的时间复杂度。

回到问题，对于每一个点，记录删除该点之后的最大联通块的顶点数，再在最后一一判断就行了。

#### 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
bool v[10005];
int size[10005],n,d[10005];
vector<int> ed[10005];
void dfs(int x){
	v[x]=size[x]=1;
	int maxn=0;
	for(int i=0;i<ed[x].size();i++){
		int y=ed[x][i];
		if(v[y]) continue;
		dfs(y);
		size[x]+=size[y];
		maxn=max(maxn,size[y]); 
	}
	maxn=max(maxn,n-size[x]);
	d[x]=maxn;
}
int main(){
	cin>>n;
	for(int i=0;i<n-1;i++){
		int x,y;
		cin>>x>>y;
		ed[x].push_back(y),ed[y].push_back(x);
	}
	dfs(1);
	bool flag=0;
	for(int i=1;i<=n;i++){
		if(d[i]<=n/2){
			flag=1;
			cout<<i<<endl;
		}
	}
	if(!flag) cout<<"NONE"; 
}
```



---

## 作者：Huangjy88 (赞：1)

# P1670题解
一道树的重心的题目。我们可以以每个节点为根做 dfs，求出最大子树大小，时间复杂度为 $O(n ^ {2})$，能过此题。考虑更优秀的做法，可以用类似找树的重心的思路，一遍 dfs 求出以每个节点为根的最大子树，最后进行判断最大子树大小是否小于等于 $ \frac{n}{2} $ 即可，时间复杂度为 $O(n)$。不会重心的建议先做[这道题](https://www.luogu.com.cn/problem/P1395)。

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
int n;
vector<int> v[N];
int sz[N],mss[N];
int ans;
void dfs(int x,int fa){//dfs
    sz[x]=1;
    for(int i=0;i<v[x].size();i++){
	int y=v[x][i];
	if(y==fa) continue;
	dfs(y,x);
	sz[x]+=sz[y];
	mss[x]=max(mss[x],sz[y]);//子节点
    }
    mss[x]=max(mss[x],n-sz[x]);//父节点
}
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
	int x,y;cin>>x>>y;
	v[x].push_back(y);
	v[y].push_back(x);//存图
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
	if(mss[i]<=n>>1) cout<<i<<endl;//判断
    }
    return 0;
}
```

---

