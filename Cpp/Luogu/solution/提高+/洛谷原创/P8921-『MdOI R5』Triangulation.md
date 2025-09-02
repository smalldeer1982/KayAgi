# 『MdOI R5』Triangulation

## 题目描述

有一个正 $n$ 边形，顶点按顺时针方向从 $1$ 到 $n$ 依次标号。给定这个多边形的 $n-3$ 条**互不相同**的对角线，满足它们**互相之间只可能在顶点处相交**。这样我们得到了一张 $n$ 个点，$2n-3$ 条边的无向图。

凸多边形的对角线指的是连接两个**不相同**且**不在多边形上相邻**的顶点的一条线段。

实际上，这个无向图可以是任意一个凸 $n$ 边形的三角剖分图。

你需要构造这个无向图的一棵生成树，使得每个点的度数都是**奇数**，或报告无解。

## 说明/提示

对于 $100\%$ 的数据，$3\le n\le 3\times 10^5$。

$\operatorname{Subtask} 1(9\%)$：$n\le 10$。

$\operatorname{Subtask} 2(1\%)$：$n$ 为奇数。

$\operatorname{Subtask} 3(10\%)$：$u=1$。

$\operatorname{Subtask} 4(30\%)$：$n\le 100$。

$\operatorname{Subtask} 5(30\%)$：$n\le 5\times 10^3$。

$\operatorname{Subtask} 6(20\%)$：无特殊限制。

## 样例 #1

### 输入

```
5
1 3
1 4```

### 输出

```
-1```

## 样例 #2

### 输入

```
8
6 8
5 8
2 4
2 5
1 5```

### 输出

```
3 2
2 4
7 8
6 8
2 1
1 5
8 1```

# 题解

## 作者：yummy (赞：13)

# D 验题人 sol

这里提供一种代码更短的 $O(n)$ 做法。

**Update：被当做官方解法拿去讲了，实际上本质相同。**

**Update：修正一个 typo，添加 Python 程序。**

## 背景

实际上这场比赛的备赛周期非常长。这道题在 8 月就出出来了，当时我就睡觉的时候把这题口胡了，第二天和 JV 讲了，他表示这做法好想好写，觉得这题要被橄榄。但是后来咕咕咕了。再接着到了 12 月。

然后我就退役了。但是一想到这题可能是我在役期间唯一独立完成的 div2D（而且和出题人做法完全不同），我逼自己完成了这个实现，不能让这个奇妙想法就此埋没。

JV 很喜欢三角剖分啊。上次那个 You are the Miserable 也是三角剖分的性质。

## 做法

当 $n$ 为奇数时显然不存在答案。思考偶数怎么做。

当 $n=2$ 时答案是唯一确定的，接下来思考如果每次增加两个点，我们应该怎么加边，才能维护生成树的性质。

如果我们在原来基础上连续添加一对相邻三角形（左图，增加 $0,2$ 两点），那么可以添加 $(0,4),(2,4)$ 两条边；如果在相邻两条边上各加入一个三角形（右图，增加 $1,2$ 两点），那么可以添加 $(0,1),(0,2)$ 两条边。

![](https://cdn.luogu.com.cn/upload/image_hosting/tv6k2kyh.png)

接下来需要证明所有 $n$ 为偶数的三角剖分都可以用这两种方法得到。

如果我们以每个三角形为结点，相邻三角形间连边，那么每个点度数不超过 $3$，是一棵二叉树。

如果我们要给树 $T$ 构造答案，那么：

- 如果 $T$ 的两个孩子都有偶数个三角形，则分别让两个孩子自给自足即可，根等待父亲连边。
- 如果 $T$ 两个孩子都有奇数个三角形，则我们用上面右图的方法连接两个孩子。
- 如果 $T$ 两个孩子一奇一偶，则根应该和奇数子树的根使用左图方法连接。

这样整棵树 $T$ 都能被构造一个合法的答案。

## 实现

对偶图，听上去好办，实操起来细节很多。

---

第一个问题是如何给 $n$ 个长度和 $O(n)$，值域为 $n$ 的数列排序。

我们可以采用计数排序，但是如果 $n$ 个数列一起排序只要扫描一次计数器，时间复杂度 $O(n)$。

但是本题因为排序是为了求环上的前驱后继，所以对序列 $u$，大于 $u$ 的放前面，小于 $u$ 的放后面。

同时为了方便查找我们可以放 $n$ 个哈希表，记录每个点在 `vector` 中的下标。

---

第二个问题是如何区分三角形的三条边。

这个建议大家边在草稿纸上画图边写，位置关系要和草稿纸严格对应。

我草稿纸上的图 $1\sim n$ 是逆时针排列的，因此我规定 `dfs(u,v,w)` 中，$u,v,w$ 也是逆时针排列，并且 $(u,v)$ 是当前三角形和父亲之间的界限。这种记法给我带来了很多方便。

写的时候还是脑抽很多次了的。比如说，两次 DFS（一次求子树大小，一次染色）不会带来任何 coding 的方便，徒增常数，直到我 AC 了这道题我才意识到。参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
vector<int> g[300005],ng[300005];
unordered_map<int,int> loc[300005];
#define lc g[u][loc[w][u]+1]
#define rc g[v][loc[w][v]-1]
int tree(int u,int v,int w)//返回值为子树大小
{
	int lsz=0,rsz=0;
	if(not(w==u-1 or w==n and u==1))lsz=tree(u,w,lc);
	if(not(w==v+1 or w==1 and v==n))rsz=tree(w,v,rc);
	if((lsz+rsz)%2)//如果子树大小为偶数
		if(lsz%2==1)
			printf("%d %d\n%d %d\n",u,w,u,lc);
		else
			printf("%d %d\n%d %d\n",v,w,v,rc);
	else if(lsz%2==1)//如果两个奇数那么将两个孩子连起来
		printf("%d %d\n%d %d\n",w,lc,w,rc);
	return lsz+rsz+1;
}
int main()
{
	scanf("%d",&n);
	if(n%2){puts("-1");return 0;} 
	int u,v;
	for(int i=1;i<=n-3;i++)
	{
		scanf("%d%d",&u,&v);
		ng[u].push_back(v);
		ng[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
	{
		ng[i].push_back(i%n+1);
		ng[i%n+1].push_back(i);
	}
	for(int i=1;i<=n;i++)//问题 1：计数排序，i 枚举值
		for(int j:ng[i])
		{
			if(j>i)continue;//j<i 的边在前
			loc[i][j]=g[j].size();
			g[j].push_back(i);
		}
	for(int i=1;i<=n;i++)
		for(int j:ng[i])
		{
			if(j<i)continue;//j>i 的边在后
			loc[i][j]=g[j].size();
			g[j].push_back(i);
		}
	printf("1 2\n");//一开始将 1,2 加入答案
	tree(1,2,g[1][1]);//可以保证这个三角形一定是贴边的，构成二叉树
	return 0;
}
```

Python 3 解法（虽然常数比较大，无法通过 Subtasks 3 and 6）：
```python
n=int(input())
import sys
sys.setrecursionlimit(300005)
if n%2:
	print(-1)
	sys.exit(0)
ng,g=[[] for i in range(n+5)],[[] for i in range(n+5)]
loc=[{} for i in range(n+5)]
def tree(u,v,w):
	lsz,rsz=0,0
	if not(w==u-1 or w==n and u==1):
		lc=g[u][loc[w][u]+1]
		lsz=tree(u,w,lc)
	if not(w==v+1 or w==1 and v==n):
		rc=g[v][loc[w][v]-1]
		rsz=tree(w,v,rc)
	if (lsz+rsz)%2:
		if lsz%2:
			print("%d %d\n%d %d"%(u,w,u,lc))
		else:
			print("%d %d\n%d %d"%(v,w,v,rc))
	elif lsz%2==1:
		print("%d %d\n%d %d"%(w,lc,w,rc))
	return lsz+rsz+1
for i in range(n-3):
	u,v=map(int,input().split())
	ng[u].append(v)
	ng[v].append(u)
for i in range(1,n+1):
	ng[i].append(i%n+1)
	ng[i%n+1].append(i)
for i in range(1,n+1):
	for j in ng[i]:
		if j<i:
			loc[i][j]=len(g[j])
			g[j].append(i)
for i in range(1,n+1):
	for j in ng[i]:
		if j>i:
			loc[i][j]=len(g[j])
			g[j].append(i)
print(1,2)
tree(1,2,g[1][1])
```

---

## 作者：lndjy (赞：3)

- 手玩样例可以发现，尝试从最边上的三角形构造是个不错的选择。
- 做过类似的套路的话，考虑每次删除一个三角形进行构造。
- 每个点度数的奇数如何处理？给同一个点一次连两条边是不影响该点奇偶性的。可以考虑，每次给一个点连两条边，最后把这个点向外连一条边保证图连通，然后就“抛弃”这个点。这样这个点的度数就可以写成 $2n+1$ 的形式。
- 如果你推到这里，尝试构造，你会发现，每次删除一个三角形不能满足第三条的要求。
- 那么就每次删相邻两个。
- 相邻的两个三角形，最多包含 5 个点。
- 钦定五个点按照逆时针排序，第一个和第五个点和剩下的图形连通，也就是说删去的两个三角形的顶点不能是这两个。

分类讨论：

1.如这个图右边的图，最左边和最右边的点和中间的点有边，那么删除剩下的两个点，并将两个点和中间点连边。也就是只存在图中的 034 三个点。

![](https://cdn.luogu.com.cn/upload/image_hosting/tv6k2kyh.png)

2.如果右边的图的 03 04 边改为了 40 41，那么删除的就是 02 两个点，02 向 4 连边。

3.如果右边的图的 03 04 边改为了 12 14，那么删除的就是 02 两个点，02 向 1 连边。

4.如果右边的图的 03 04 边改为了 21 23，那么删除的就是 01 两个点，01 向 2 连边。

讲的比较抽象，建议用草稿纸自己模拟一下这四种情况。

细节的话就是可以用循环链表维护最外侧边的顺序关系。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<map>
#include<cstdlib>
#include<algorithm>
using namespace std;
int inline read()
{
	int ans=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*f;
}
const int N=3e5+5;
int n;
map<int,int> mp[N]; 
int ansx[N],ansy[N],tot,pre[N],nxt[N];
void del(int x)
{
	pre[nxt[x]]=pre[x];
	nxt[pre[x]]=nxt[x];
}
void add(int x,int y)
{
	ansx[++tot]=x;
	ansy[tot]=y;
}
void dfs(int now,int res)
{
	if(res==4)
	{
		int A=now,B=nxt[now],C=nxt[B],D=nxt[C];
		if(mp[A][B]&&mp[A][C]&&mp[A][D]) add(A,B),add(A,C),add(A,D);
		else if(mp[B][A]&&mp[B][C]&&mp[B][D]) add(B,A),add(B,C),add(B,D);
		else if(mp[C][A]&&mp[C][B]&&mp[C][D]) add(C,A),add(C,B),add(C,D);
		else add(D,A),add(D,B),add(D,C);
		return;
	}
	for(int i=now;;i=nxt[i])
	{
		int A=nxt[i],B=nxt[A],C=nxt[B],D=nxt[C],flg=0;
		if(mp[i][B]&&mp[B][D]) del(A),del(C),dfs(pre[i],res-2),add(B,A),add(B,C),flg=1;
		if(mp[i][B]&&mp[i][C]) del(A),del(B),dfs(pre[i],res-2),add(i,A),add(i,B),flg=1;
		if(mp[D][A]&&mp[D][B]) del(B),del(C),dfs(pre[i],res-2),add(D,C),add(D,B),flg=1;
		if(mp[i][C]&&mp[A][C]) del(A),del(B),dfs(pre[i],res-2),add(C,A),add(C,B),flg=1;
		if(flg) break;
	}
}
signed main()
{
	n=read();
	if(n&1)
	{
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=n-3;i++)
	{
		int x=read(),y=read();
		mp[x][y]=mp[y][x]=1;
	}
	for(int i=1;i<n;i++)
	mp[i][i+1]=1,pre[i+1]=i;mp[n][1]=1;pre[1]=n;
	for(int i=2;i<=n;i++)
	mp[i][i-1]=1,nxt[i-1]=i;mp[1][n]=1;nxt[n]=1;
	dfs(1,n);
	for(int i=1;i<=tot;i++)
	cout<<ansx[i]<<" "<<ansy[i]<<endl;
	return 0;
 } 
```


---

## 作者：TianyiLemon (赞：1)

首先 $n$ 为奇数显然无解。

接下来考虑 $n$ 为偶数怎么构造，考虑递归。

就是说我们每次找到一个二度点，删掉相邻的两个三角形，把原问题转化成一个形态相同的子问题。分两种情况讨论：

情况 $1$：（删掉点 $B,C$，选择边 $AB,AC$）
![](https://cdn.luogu.com.cn/upload/image_hosting/pldh3hlr.png)

情况 $2$：（删掉点 $B,E$，选择边 $BC,EC$）
![](https://cdn.luogu.com.cn/upload/image_hosting/6g09tsii.png)

最后删得只剩一条边，那么这条边就一定要选。

在删三角形的时候，我们要首先考虑满足情况 $1$ 的三角形，如果没有再考虑情况 $2$。我们用循环链表模拟删点，暴力枚举每个二度点，判断是否能删除，即可做到 $O(n^2)$，实现得好就能拿到 $80$ 分。

如何优化？发现我们每次从头开始找合法的点太浪费时间了，只需从上一次删掉点的相邻点开始找即可。

时空复杂度 $O(n)$，代码实现非常简洁。

```cpp
#include<bits/stdc++.h>
#define N 300009
#define rep(i,x,y) for(int i=(x);i<=(y);++i)
using namespace std;
int n,deg[N],l[N],r[N];
void dele(int x){
	r[l[x]]=r[x];l[r[x]]=l[x];
	--deg[l[x]];--deg[r[x]];
}
int main(){
	cin>>n;
	if(n&1){puts("-1");return 0;}
	rep(i,1,n-1)++deg[i],++deg[i+1];
	++deg[n],++deg[1];
	rep(i,1,n)l[i]=i-1,r[i]=i+1;
	l[1]=n,r[n]=1;
	rep(i,1,n-3){
		int u,v;scanf("%d %d",&u,&v);
		++deg[u],++deg[v];
	}
	int u=1;
	rep(i,1,(n-2)/2){
		for(;;u=r[u])if(deg[u]==2){
			if(deg[l[u]]==3){
				printf("%d %d\n",l[u],r[u]);
				printf("%d %d\n",u,r[u]);
				dele(u);dele(l[u]);
				u=r[u];
				break;
			}else if(deg[r[u]]==3){
				printf("%d %d\n",l[u],r[u]);
				printf("%d %d\n",u,l[u]);
				dele(u);dele(r[u]);
				u=l[u];
				break;
			}else if(deg[l[l[u]]]==2){
				printf("%d %d\n",u,l[u]);
				printf("%d %d\n",l[u],l[l[u]]);
				dele(u);dele(l[l[u]]);
				u=l[u];
				break;
			}else if(deg[r[r[u]]]==2){
				printf("%d %d\n",u,r[u]);
				printf("%d %d\n",r[u],r[r[u]]);
				dele(u);dele(r[r[u]]);
				u=r[u];
				break;
			}
		}
	}
	printf("%d %d\n",u,l[u]);
	return 0;
}
```

---

