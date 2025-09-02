# Peaceful Rooks

## 题目描述

You are given a $ n \times n $ chessboard. Rows and columns of the board are numbered from $ 1 $ to $ n $ . Cell $ (x, y) $ lies on the intersection of column number $ x $ and row number $ y $ .

Rook is a chess piece, that can in one turn move any number of cells vertically or horizontally. There are $ m $ rooks ( $ m < n $ ) placed on the chessboard in such a way that no pair of rooks attack each other. I.e. there are no pair of rooks that share a row or a column.

In one turn you can move one of the rooks any number of cells vertically or horizontally. Additionally, it shouldn't be attacked by any other rook after movement. What is the minimum number of moves required to place all the rooks on the main diagonal?

The main diagonal of the chessboard is all the cells $ (i, i) $ , where $ 1 \le i \le n $ .

## 说明/提示

Possible moves for the first three test cases:

1. $ (2, 3) \to (2, 2) $
2. $ (2, 1) \to (2, 3) $ , $ (1, 2) \to (1, 1) $ , $ (2, 3) \to (2, 2) $
3. $ (2, 3) \to (2, 4) $ , $ (2, 4) \to (4, 4) $ , $ (3, 1) \to (3, 3) $ , $ (1, 2) \to (1, 1) $

## 样例 #1

### 输入

```
4
3 1
2 3
3 2
2 1
1 2
5 3
2 3
3 1
1 2
5 4
4 5
5 1
2 2
3 3```

### 输出

```
1
3
4
2```

# 题解

## 作者：MC小萌新 (赞：10)

## 题目大意
在 $ n*n $ 的象棋棋盘中，有 $ m $ 个车，每个车坐标为 $ (x_i,y_i) $，求出把每个车都移动到棋盘的主对角线（主对角线上点的坐标特点：横纵坐标相等）需要的最短次数 $ ans $。

## 题目分析
在象棋中，我们知道车走直线，所以想让 $ ans $ 最小，就要把车移到对应行或列的对角线上。那么在没有冲突且没有车原来就在对角线上的情况下，只需要移动 $ m $ 步就可以达到要求。

但是，任意两个车都不能在同一行或者同一列上，所以在本题中，当我们要把一个车移到对角线上时，就要先判断一下目标点所对应的列有没有车，如果有，则需先把那个车移走，然后再把待移动的车移到对角线上去。

那么，如何判断冲突呢？在这里，我们可以通过建图的方式来解决。我们把每个车的横纵坐标之间连边，如果有环，则说明会有冲突，$ ans $ 就要 $ +1 $。有几个环，就有几个冲突，最后的 $ ans $ 就要加上环的数量。

计算环则可以通过并查集来实现。在加边时，如果目标的两个点已经在同一连通块，则加边后一定会形成一个环。所以只需要每次加边时记录一下就可了。

还有一点，如果有点本来就在对角线上，则无需移动，$ ans $ 也要随之 $ -1 $。

总结一下，$ ans $  $ = $  $ m $  $ + $ 环数 $ - $ 对角线上点数。
## 代码实现
多组数据，每次不要忘记初始化。
```cpp
#include <iostream>
using namespace std;
int n,m,t,x,y,fa[100010],ans;
int find(int x){
	if(x==fa[x])
		return x;
	return fa[x]=find(fa[x]);
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		ans=m;
		for(int i=1;i<=n;++i)
			fa[i]=i;
		for(int i=1;i<=m;++i){
			cin>>x>>y;
			if(x==y){
				--ans;
				continue;
			}
			if(find(x)==find(y))
				++ans;
			else
				fa[x]=y;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```



---

## 作者：滑稽的小宫 (赞：3)

## 题意简述
- 给定一个n*n的棋盘，然后有m个车分布在一些位置
- 移动一个车的时候不能移动到会被其他车吃掉的位置
- 目标是用最少的移动步数把m个车放在对角线上
## solving
这道题看起来有点难度，我们不妨先模拟一下样例

```
3 1

2 3
```
只有一个车的话，只要把他移动到对角线上即可

```
3 2

2 1
1 2
```
考虑一下怎样移动最优，由于车的数量少于列的数量，我们可以试试用第三行当做缓冲行，先把第一列的车移到第三行，然后把第二列的车移到第二行，再把第三行的车移到第一行

我们可以发现在操作过程中并没有移动每个车的列号，可以想到如果左右移动改变了列，那么相当于多走了一步，似乎并不能更优（当然可能会出现移动列可以直接到对角线上的情况，不过我们先这么猜想，后面再回来证明）

有了这个猜想以后就好做很多，可以用一条边从它当前的行指向它需要去的行（即从它当前的行号位置指向它的列号的那个位置）

![](https://cdn.luogu.com.cn/upload/image_hosting/7qcpw1hi.png)

对于上面那个图，就构成了一个环，那么我们不能把1节点放到2位置去，因为2正占着2号位置，而2也不能移动，因此需要把1或2移到3位置，然后就只剩另一个节点了，这时候直接把那个节点归位，然后把移出去的节点放回来即可

于是我们有一个猜想：
- 对于形成环的情况，需要先断开一个节点，把这个节点移动到一个没有节点的列上（一定有，因为m<n），然后剩下的就是一条链
- 对于一条链，直接从链的头开始，移动到自己需要去的节点位置（由于那个位置被断开了或者为空，因此可以直接移动过去），然后指向链的头原来的位置的节点移动到链的头的原来的位置，依次处理下去就可以把整条链归位

对于一条链的情况，需要的移动步数就是链的长度。而对于一个环，需要的移动步数就是环的大小+1，这个+1是指某一个节点先要移到缓冲列上的这一步，剩下就是一样了

### 举例模拟：

```
5 4

2 3
3 1
1 2
4 5
```
按照刚才的方式，建立一个有向图:

![](https://cdn.luogu.com.cn/upload/image_hosting/f4t8x1bi.png)

这样相当于3要移到1位置，1要移到2位置，2要移到3位置，4要移到5位置（相当于就是从行向列发出了一条有向边）

那么这个时候3,1,2构成了一个环，如果我想把3移到1位置，就得把2移到3位置，就得把1移到2位置，就得把3移到1位置……永远都不能移动出来

因此可以按照刚才猜想的规律，随便取出一个节点放到5的位置去，例如拿出3，这样1,2就形成了一条链，2放到3原来的位置，1再放到2原来的位置就归位了，这时候1原来的位置自然也让出来了，让3移回去即可，总步数是节点数+1=4

然后对于4的情况，5因为是空的，因此这个链实际上只有4这一个节点，只需要把4移动过去即可，因此步数为1

所以总步数为5

### 证明

可行性：显然

最优性：

对于有向图中的一条链，需要移动的步数就是链的长度，因此每个需要移动的节点都只会移动一次，不会有比这个更优秀的方案了。

对于环来说，用我们的方法步数是环的长度+1，破坏这个环是必须的，因为我们不能通过一个环的整体移动得到归位。破坏这个环的最短步数就是1步，然后这个环里面每个节点按我们的方法都只会移动一次，因此对于这个破坏后的环来说最优步数就是环中节点个数，而破坏一个环最优步数是1，因此总共的最优步数仍然是环中节点个数+1

因此我们证明了这个方法的可行性与最优性

### 实现

可以使用tarjan算法查找环，相当于把这个图分成许多个强连通分量，那么对于节点个数大于1的强连通分量，相当于就是一个环，这时候就把答案加上节点个数+1，对于其他等于1的强连通分量，对答案的贡献就只有1了。

$Talk\ is\ cheap,\ show\ you\ the\ code:$
```cpp
#include<iostream>
#include<cstdio>
#define N 100010
int t,n,m,s,k,hd[N],nxt[N],to[N],st[N],top,low[N],dfn[N],inst[N],vis[N],ans;
void newedge(int u,int v){
	nxt[++k]=hd[u];
	to[k]=v;
	hd[u]=k;
	return;
}void dfs(int x){
	dfn[x]=low[x]=++s;
	st[top++]=x;
	inst[x]=1;
	for(int i=hd[x];i;i=nxt[i]){
		int nex=to[i];
		if(!vis[nex])continue;//vis记录了有车的节点，有的节点上面没有车就不要走
		if(!dfn[nex]){
			dfs(nex);
			low[x]=std::min(low[x],low[nex]);
		}else if(inst[nex])low[x]=std::min(low[x],dfn[nex]);
	}if(low[x]==dfn[x]){
		int cnt=0;
		do{
			cnt++;
			inst[st[top-1]]=0;
		}while(st[--top]!=x);
		if(cnt<=1)ans+=1;//节点个数小于1，说明在链上，只能贡献1
		else ans+=cnt+1;//是一个环，贡献节点个数+1
	}return;
}
int main(){
	scanf("%d",&t);
	start:
	if(t--==0)return 0;
	scanf("%d%d",&n,&m);
	top=s=k=ans=0;
	for(int i=1;i<=n;i++)vis[i]=hd[i]=nxt[i]=to[i]=st[i]=low[i]=dfn[i]=inst[i]=0;
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x==y)continue;//已经满足要求，不要加入图中
		newedge(x,y);//从当前行号向列号建一条边，相当于目标是把行号变成列号
		vis[x]=1;//把这个节点标记成有车的节点
	}for(int i=1;i<=n;i++){
		if(vis[i]&&!dfn[i]){//tarjan求强连通分量
			dfs(i);
		}
	}printf("%d\n",ans);
	goto start;
}
```


---

## 作者：SunsetVoice (赞：1)

首先感谢翻译，让我白白浪费了 $30$ 分钟。

建议撤下，或加入“移动过程中棋子无法互相攻击”。

首先显然若没有“不互相攻击”的条件，则棋子能在一步以内进入主对角线（即改变横坐标或正坐标）。 

题目中说“不能互相攻击”，则移动过程中不能和其他棋子处于同一行、列。

使用并查集求最近公共祖先（是否相同），则可以避免。

注意若一开始棋子位于对角线格（$x=y$），则该棋子不需要移动。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[20001] = {0};
//fanyinmsl
int find(int pos){
	if(f[pos]==pos)return pos;
	else return f[pos] = find(f[pos]);
}
int main(){
	int n,m,T;
	cin>>T;
	while(T--){
		cin>>n>>m;
		int x,y;
		int ans = 0;
		for(int i = 1;i<=n;i++)f[i] = i;
		for(int i = 1;i<=m;i++){
			cin>>x>>y;
			if(x!=y){
				if(find(y)==find(x))ans+=2;
				else f[y] = x,ans++;
			}
  			cout<<x<<y<<endl;
		}
		cout<<ans<<endl;
	} 
	return 0;
} 
```


---

## 作者：王逸辰 (赞：0)

# CF1411C Peaceful Rooks 题解
## 题意理解
建议加入移动过程中棋子无法互相攻击这一条件。
## 思路
并查集板子。

很容易从棋子不能互相攻击，推导这枚棋子在移动的时候不能与其他棋子在同一行或同一列，最后就推出这枚棋子每次移动时都要用并查集求最近公共祖先。

代码很好写，详细见代码注释。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int a[N];
int f(int x){
	if(x==a[x])
		return x;
	return a[x]=f(a[x]);
}
int main(){
	int T,n,m,x,y,ans=0;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&m);
		ans=m;
		for(int i=1; i<=n; i++)
			a[i]=i;
		while(m--){
			scanf("%d %d",&x,&y);
			if(x==y)//处于对角线无需挪动
				ans--;
			else if(f(x)==f(y))//满足条件
				ans++;
			else//不满足
				a[x]=y;
		}
		printf("%d\n",ans);
	}
	return 0;
}
``````

---

