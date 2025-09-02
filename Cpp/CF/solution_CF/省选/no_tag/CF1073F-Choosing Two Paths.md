# Choosing Two Paths

## 题目描述

给定一棵包含 $n$ 个顶点的无向无权树。

无向树是一个连通的无向图，包含 $n-1$ 条边。

你的任务是从这棵树中选择两对顶点（所有被选中的顶点都必须互不相同），即 $(x_1, y_1)$ 和 $(x_2, y_2)$，使得 $x_1$ 和 $y_1$ 都不在从 $x_2$ 到 $y_2$ 的简单路径上，反之亦然（即 $x_2$ 和 $y_2$ 也都不在从 $x_1$ 到 $y_1$ 的简单路径上）。

保证对于给定的树一定可以选择出满足条件的两对顶点。

在所有可能的选择方案中，你需要选择一组，使得从 $x_1$ 到 $y_1$ 的路径与从 $x_2$ 到 $y_2$ 的路径的公共顶点数最大。在所有公共顶点数最大的方案中，再选择一组使得这两条路径的总长度最大。

保证对于给定的树，存在至少有两个公共顶点的答案。

路径的长度是指路径上的边数。

简单路径是指每个顶点最多只经过一次的路径。

## 说明/提示

第一个样例对应的图如下：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1073F/240c81d8c0649c71ee92437821440e7761310fb9.png)

两条路径的交集为 $2$（顶点 $1$ 和 $4$），总长度为 $4+3=7$。

第二个样例对应的图如下：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1073F/6c389544ddcc0274094aa4810ea900c37e29670a.png)

两条路径的交集为 $2$（顶点 $3$ 和 $4$），总长度为 $5+3=8$。

第三个样例对应的图如下：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1073F/607ccb06ab07d0cf6650c7e34cf624c5db33512a.png)

两条路径的交集为 $3$（顶点 $2$、$7$ 和 $8$），总长度为 $5+5=10$。

第四个样例对应的图如下：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1073F/a19a0cf4ee91bef5fa339fd3d828a321e8d550f5.png)

两条路径的交集为 $5$（顶点 $1$、$2$、$3$、$4$ 和 $5$），总长度为 $6+6=12$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
1 4
1 5
1 6
2 3
2 4
4 7
```

### 输出

```
3 6
7 5
```

## 样例 #2

### 输入

```
9
9 3
3 5
1 2
4 3
4 7
1 7
4 6
3 8
```

### 输出

```
2 9
6 8
```

## 样例 #3

### 输入

```
10
6 8
10 3
3 7
5 8
1 7
7 2
2 9
2 8
1 4
```

### 输出

```
10 6
4 5
```

## 样例 #4

### 输入

```
11
1 2
2 3
3 4
1 5
1 6
6 7
5 8
5 9
4 10
4 11
```

### 输出

```
9 11
8 10
```

# 题解

## 作者：mrsrz (赞：8)

如果是一条链最长，则求的就是树的直径。

现在要求两条链的公共部分最长。

我们知道，两条链的公共部分一定也是一条链，且这条链的两个端点，一定至少有三个分叉（两条链的端点在这个节点处分开）。

也就是说，我们要找两个端点$u,v$，使得它们都至少有两个儿子节点（不包括两条链之间的路径上的那个节点）。

这个东西，也可以像求直径一样两遍dfs。

然后还要使得总长度尽可能长。

那我们就在$u$和$v$的子树中，找离根最远和次远的点即可。

为了保证求出的两个端点的子树中，“离根最远和次远的点到根距离之和”是最长的，所以在dfs的时候若两个点距离根同样远，则根据它们“离根最远和次远的点到根距离之和”的大小来判断即可。

时间复杂度$O(n)$。

## Code：
```cpp
#include<cstdio>
#include<cstring>
#define N 233333
int n,head[N],cnt=0,dep[N],mx,_1,_2,tot,li[N];
struct edge{
	int to,nxt;
}e[N<<1];
void dfs(int now){
	int son=0;
	int mx2=0;
	for(int i=head[now];i;i=e[i].nxt)
	if(!dep[e[i].to]){
		dep[e[i].to]=dep[now]+1;
		dfs(e[i].to);
		if(dep[li[e[i].to]]>dep[li[now]])mx2=li[now],li[now]=li[e[i].to];else
		if(dep[li[e[i].to]]>dep[mx2])mx2=li[e[i].to];
		++son;
	}
	if(son==0)li[now]=now;
	if(son>1&&(dep[now]>dep[mx]||dep[now]==dep[mx]&&dep[li[now]]+dep[mx2]>tot)){
		mx=now;
		tot=dep[li[now]]+dep[mx2];
	}
}
void get(int now){
	int son=0;
	for(int i=head[now];i;i=e[i].nxt)
	if(dep[e[i].to]>dep[now]){
		++son;
		get(e[i].to);
	}
	if(!son){
		if(dep[_1]<dep[now]){
			_2=_1;_1=now;
		}else
		if(dep[_2]<dep[now])_2=now;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		e[++cnt]=(edge){v,head[u]};
		head[u]=cnt;
		e[++cnt]=(edge){u,head[v]};
		head[v]=cnt;
	}
	tot=0;
	dfs(dep[1]=1);
	int u=mx;
	_1=_2=0;
	get(u);
	int u1=_1,u2=_2;
	memset(dep,0,sizeof dep);
	dep[u]=1;mx=tot=0;
	dfs(u);
	int v=mx;
	_1=_2=0;
	get(v);
	printf("%d %d\n%d %d\n",u1,_1,u2,_2);
	return 0;
}
```

---

## 作者：Memory_of_winter (赞：4)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/9929795.html)

**题目大意：**有一棵树，从中选取$2$条链，其中任何一条链的端点不能被另一条链包含，求这两条链，使这两条链的公共的点的部分最长，若相同，使得总长度最长。

**题解：**树形$DP$，因为端点互不包含，所以公共的部分的端点一定有两个及以上的儿子，然后可以把这样的点先全部求出来。求新树的直径就可以满足第一个要求（洛谷题意有锅，没有写在相同情况下要求总长度最长，导致我最后重构代码）。

那如何使得相同情况下总长度最长呢？可以再维护一个以$i$为根的子树内以$i$为一个端点的最长链和次长链，$DP$时以新树的深度为第一关键字，以最长链和次长链长度总和为第二关键字就可以了。




**C++ Code：**

```cpp
#include <cstdio>
#define maxn 200010
inline int max(int a, int b) {return a > b ? a : b;}

int head[maxn], cnt;
struct Edge {
	int to, nxt;
} e[maxn << 1];
inline void add(int a, int b) {
	e[++cnt] = (Edge) {b, head[a]}; head[a] = cnt;
}
bool choose[maxn];
int ind[maxn];
int n, root;

struct node {//M为链的长度，P为该链的端点
	int P, M;
	inline node() {}
	inline node(int __P, int __M) {M = __M, P = __P;}
	inline node operator + (const int &rhs) const {return node(P, M + rhs);}
	inline friend operator < (const node &lhs, const node &rhs) {return lhs.M < rhs.M;}
} V[maxn][2];//0为最长的链，1为次长链
void dfs(int u, int fa = 0) {//求出那些点可以属于公共部分
	if (ind[u] > 1) choose[u] = true;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v != fa) {
			dfs(v, u);
			if (ind[u] == 2 && !choose[v]) choose[u] = false;
		}
	}
}

int f[maxn], F[maxn];
node dfs1(int u, int fa = 0) {//求端点
	V[u][0] = node(u, 0); V[u][1] = node(0, 0);
	f[F[u] = u] = choose[u];
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v != fa) {
			node tmp = dfs1(v, u) + 1;
			if (f[v] + choose[u] > f[u]) {
				f[u] = f[v] + choose[u];
				F[u] = F[v];
			} else if (f[v] + choose[u] == f[u]) {
				if (choose[v] && V[F[u]][1].M + V[F[u]][0].M <= V[F[v]][1].M + V[F[v]][0].M) {
					F[u] = F[v];
				}
			}
			if (V[u][0] < tmp) {
				V[u][1] = V[u][0];
				V[u][0] = tmp;
			} else if (V[u][1] < tmp) V[u][1] = tmp;
		}
	}
	return V[u][0];
}

int main() {
	scanf("%d", &n);
	for (int i = 1, a, b; i < n; i++) {
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
		ind[a]++, ind[b]++;
		if (ind[a] >= 3) root = a;
		if (ind[b] >= 3) root = b;
	}
	dfs(root);
	int x, a, b, c, d;
	dfs1(root);
	x = F[root], a = V[F[root]][0].P, c = V[F[root]][1].P;
	dfs1(x);
	b = V[F[x]][0].P, d = V[F[x]][1].P;
	printf("%d %d\n%d %d\n", a, b, c, d);
	return 0;
}

```



---

## 作者：tommymio (赞：2)

有点意思又偏向套路的结论题。

我们发现，最终答案一定是类似于一条路径 $\mathrm{Path(u\to v)}$ 上延伸出两条路径 $\mathrm{Path(x'\to x),Path(y'\to y)}$ 这种形式，其中 $x',y'$ 都在路径 $u\to v$ 上。而我们要先让 $\mathrm{dis(x',y')}$ 最大（即相交部分最大），其次令路径 $\mathrm{Path(u\to v),Path(x'\to x),Path(y'\to y)}$ 的长度之和最大。

可以发现 $\mathrm{Path(u\to v)}$ 这条路径，可以使用类似直径的两次 $\text{dfs}$ 求出。而一旦这条路径确定，另外两条路径的 $x',y'$ 是确定的，对应求出 $x',y'$ 子树中的叶子节点 $x,y$ 即可。答案的链对就为 $\mathrm{Path(u\to v),Path(x\to y)}$。

但是如果 $u\to v$ 不满足一些条件，会导致对应求出的 $x,y$ 形成的交集不是最大的，或者路径长度总和不是最大的（~~我在这个地方反复 $\text{Wrong Answer on test 72/57/45}$~~，不得不说 $\text{Codeforces}$ 的数据还是挺强的

为了解决这个问题，我们在两遍 $\text{dfs}$ 的时候，按照优先级更新值即可。先考虑相交部分最大，其次考虑路径长度之和最大。由于需要求路径长度之和，我们需要预处理出 $x$ 子树内最大距离和次大距离，这是一个套路就不细表了。

那么，我们就可以在 $O(n)$ 的时间复杂度内解决这个问题。代码写的有点凌乱随便看看就好（我才不会告诉你是我故意的呢~

```cpp
#include<cstdio>
int pos=0,val=0,val2=0,cnt=0,mx,mn,rex,rey;
int du[200005],h[200005],to[400005],ver[400005];
int dis[200005],tag[200005],pre[200005],s[200005],leaf[200005],sec[200005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void swap(int &x,int &y) {int tmp=y;y=x;x=tmp;}
inline void add(int x,int y) {to[++cnt]=y;ver[cnt]=h[x];h[x]=cnt;}
inline void dfs2(int x) { 
	du[x]=0;
	if(dis[mx]-dis[mn]>val) pos=x,val=dis[mx]-dis[mn],val2=dis[leaf[mn]]+dis[leaf[mx]]+dis[x]; else if(val==dis[mx]-dis[mn]&&dis[leaf[mn]]+dis[leaf[mx]]+dis[x]>val2) pos=x,val2=dis[leaf[mn]]+dis[leaf[mx]]+dis[x];
	for(register int i=h[x],y;i;i=ver[i]) {if(pre[x]==(y=to[i])) continue; ++du[x];}
	for(register int i=h[x],y;i;i=ver[i]) {
		if(pre[x]==(y=to[i])) continue; 
		pre[y]=x; dis[y]=dis[x]+1; int premx=mx,premn=mn; 
		int flag=0; if(leaf[y]==leaf[x]) {flag=1;swap(leaf[x],sec[x]);} 
		if(du[x]>1) {
			if(dis[x]>dis[mx]) mx=x;
			else if(dis[x]==dis[mx]&&dis[leaf[x]]>dis[leaf[mx]]) mx=x;
			if(dis[x]<dis[mn]) mn=x;
			else if(dis[x]==dis[mn]&&dis[leaf[x]]>dis[leaf[mn]]) mn=x; 
		} 
		dfs2(y); mx=premx; mn=premn;
		if(flag) swap(leaf[x],sec[x]);
	}
}
inline void dfs3(int x) {
	leaf[x]=x; 
	for(register int i=h[x],y;i;i=ver[i]) {
		if(pre[x]==(y=to[i])||tag[y]) continue; pre[y]=x; dfs3(y); 
		if(dis[leaf[x]]<dis[leaf[y]]) {sec[x]=leaf[x];leaf[x]=leaf[y];}
		else if(dis[sec[x]]<dis[leaf[y]]) {sec[x]=leaf[y];}
	}
}
int main() {
	int n=read(),top=0,st,ed; dis[0]=mx=0; dis[n+1]=mn=n+1;
	for(register int i=1;i<n;++i) {int x=read(),y=read();add(x,y);add(y,x);}
	dis[1]=pos=val=0; dfs2(1); st=pos; pre[st]=-1; dis[st]=pos=val=0; dfs3(st); mx=0,mn=n+1; dfs2(st); ed=pos;
	int cur=ed,rex,rey; while(cur!=-1) {s[++top]=cur; tag[cur]=1; cur=pre[cur];} mx=0,mn=n+1;
	for(register int i=top-1;i>=2;--i) {
		int x=s[i];
		for(register int k=h[x],y;k;k=ver[k]) if(!tag[y=to[k]]) mx=(dis[x]>dis[mx]? x:mx),mn=(dis[x]<dis[mn]? x:mn); 
	}
	dfs3(mn); rex=leaf[mn]; dfs3(mx); rey=leaf[mx];
	printf("%d %d\n%d %d\n",st,ed,rex,rey);
	return 0;
}
```

---

## 作者：No21 (赞：1)

### 解题思路

~~当机房大佬把这道题推给我时，我：“这能评紫？这不是一眼切？”然而蒟蒻调了三个半小时才通过本题。~~

题目的思路很清晰，想到解法也不难。

首先补充一句翻译落下的，本题保证所有数据，至少存在公共部分长度为 $2$ 的两条链，因此无需考虑菊花图，链等情况。

然后我们回到题目，我们考虑当两条链有公共部分时，那么这个公共部分只有两种情况，一种是点，一种是链，由于题目有保证而且要求公共部分最长，因此我们要找的两条链的公共部分一定是一条链，那么接下来的目标就是要让这条链最长。**为了方便表达，后面我们称某两条链公共部分为公共链**。树上的最长链？直径？没错，求最长的公共链和求直径方法类似，但是要加一些限制。

我们考虑如何限制，对于四个端点均不同的两条链来说，无论它们的公共链有多长，最后都要分开成两叉，因此对于每一条公共链来说，**它的两个端点至少有三个出度**，我们只要在跑 dfs 时判断点的出度就能轻松找到最长公共链（方法类似找树的直径，即跑两边 dfs，如果不会找树的直径建议先去学习一下）。

接着，我们考虑一种情况，如果我们找到了两条同样长的公共链，那么我们应该取哪条呢？这很显然，题目中要求我们最终找到的**两条链的链长的和最大**，因此我们应该取**以两个端点为根，子树内过根的最长链的链长与次长链长的和最大的最长公共链**（感性理解，稍微画画图就能明白什么意思）

注意细节，本题细节还是很多的，如果没看懂可以尝试看看代码，虽然蒟蒻的代码写的不好看，但是蒟蒻已经觉得注释很详细了 qwq。

```
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
    const int N=2e5+21;
    int n,U,V,ans1,ans2,len,last,q1,q2;
    vector <int> e[N];
    int l1[N][2],l2[N][2];//二维数组第一维存链长，第二维存端点（是题目要求的链的端点，不是最长公共链的端点）
    void dfs1(int x,int fa)
    {
        if(e[x].size()==1&&e[x].front()==fa)
        {
            l1[x][0]=1;
            l1[x][1]=x;
            return ;
        }//如果是叶子就赋值
        for(auto i:e[x])
        {
            if(i!=fa)
            {
                dfs1(i,x);
                if(e[x].size()==2)
                {
                    l1[x][0]=l1[i][0]+1;
                    l1[x][1]=l1[i][1];
                }//如果是一条链是没有次长链的，因此只更新 l1
                if(e[x].size()>=3)
                {
                    if(l1[i][0]+1>l1[x][0])
                    {
                        l2[x][0]=l1[x][0];
                        l2[x][1]=l1[x][1];
                        l1[x][0]=l1[i][0]+1;
                        l1[x][1]=l1[i][1];
                    }
                    else if(l1[i][0]+1>l2[x][0])
                    {
                        l2[x][0]=l1[i][0]+1;
                        l2[x][1]=l1[i][1];
                    }
                }//尝试更新 l1 和 l2
            }
        }
    }
    void dfs2(int x,int fa,int c)
    {
        if(e[x].size()>=3)
        {
            if(c>len)
            {
                last=x;
                len=c;
            }公共链更长直接替换
            else if(c==len)
            {
                if(l1[x][0]+l2[x][0]>l1[last][0]+l2[last][0])
                    last=x;
            }公共链等长判断子树内的链长
        }
        for(auto i:e[x])
        {
            if(i!=fa)
                dfs2(i,x,c+1);
        }
    }
    int mian()
    {
        cin>>n;
        for(int i=1;i<n;i++)
        {
            cin>>U>>V;
            e[U].push_back(V);
            e[V].push_back(U);
        }
        dfs1(1,0);//以 1 为根更新子树链长
        dfs2(1,0,1);//先找一个端点
        ans1=last;
        q1=l1[ans1][1];
        q2=l2[ans1][1];
        last=0;
        len=0;
        memset(l1,0,sizeof(l1));
        memset(l2,0,sizeof(l2));
        dfs1(ans1,0);//以找到的端点为根更新子树链长
        dfs2(ans1,0,1);//再找另一个端点
        ans2=last;
        cout<<q1<<' '<<l1[ans2][1]<<'\n'<<q2<<' '<<l2[ans2][1]<<'\n';
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

## 作者：RedLycoris (赞：1)

模拟赛考了这题，花了2h刚了个弱智的点分治做法。

假设当前我们分治到的重心是 $x$，那么我们此时钦定重合部分一定要经过点  $x$。

这时候就会有两种情况：

1. $x$ 不是一个端点。

那么我们可以对 $x$ 的所有儿子排序，以 $dep$ 为第一关键字（该有根子树中最深的有两个及以上儿子的节点的深度），以 $sum$ 为第二关键字（该有根子树中满足第一关键字下最大的深度的节点的两个距离该节点距离最大的两个点的距离之和，说人话就是两个分叉的长度）进行排序。

排序后，由于可能存在多个直径，我们需要找到所有经过点 $x$ 的直径的答案。但是，我们按照上述规则排完序后，直接比较前两大的即可。

证明：

+ 如果有多个儿子的深度最大，那么该方法肯定只在他们之间选。而且，根据第二关键字，我们选前两个就足以凑到在公共部分最长的情况下总长度最长的 方案了。

+ 如果只有一个儿子深度最大，那么按照第二关键字还是能把所有深度第二大的儿子按照分叉从大到小排序，仍然可以选择前两大的配对。

2. $x$ 是一个直径的端点。

这种情况可能在一个蒲公英一样的图上出现（一个菊花接了一条链和一个小分叉）。

那么 $x$ 的所有儿子中有两个及以上叶子的节点只有一个（伸出去的那条链），我们不得不看 $x$ 的所有其他直接儿子作为分叉。就是记录每个儿子的 $lt$ 表示其最深的叶子到它的距离，和 $id$ 表示 $lt$ 对应的叶子的编号。

然后套一个点分治模板就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mxn=2e5+5;
vector<int>g[mxn];
int ban[mxn];
int root=-1,ma=mxn,totn;
int sz[mxn],n;
inline void findroot(int x,int fa=0){
	sz[x]=1;int cm=0;
	for(int y:g[x])if(y!=fa and !ban[y]){
		findroot(y,x);
		sz[x]+=sz[y];
		cm=max(cm,sz[y]);
	}
	cm=max(cm,totn-sz[x]);
	if(cm<ma){
		ma=cm;
		root=x;
	}
}
vector<int>v,o;
int deg[mxn],dt[mxn],lt[mxn],fa[mxn],id[mxn],dep[mxn],sm[mxn],par[mxn];
pair<int,int>ch[mxn];
inline void dfs(int x,int fa=0){
	par[x]=fa,v.push_back(x),deg[x]=0,lt[x]=0,id[x]=x,sz[x]=1,dep[x]=-mxn;
	for(int y:g[x])if(!ban[y] and y!=fa){
		dfs(y,x),++deg[x];sz[x]+=sz[y];
		if(lt[x]<lt[y]+1){
			lt[x]=lt[y]+1;
			id[x]=id[y];
		}
	}
}
inline void dfs2(int x,int fa=0){
	vector<pair<int,int> >cv;cv.clear();
	sm[x]=-mxn;ch[x]={-mxn,-mxn};dep[x]=-mxn;
	for(int y:g[x])if(!ban[y] and y!=fa){
		dfs2(y,x);
		if(dep[y]+1>dep[x] and sm[y]>=0){
			sm[x]=sm[y],ch[x]=ch[y];dep[x]=dep[y]+1;
		}else if(dep[y]+1==dep[x] and sm[y]>=0){
			if(sm[y]>sm[x]){
				sm[x]=sm[y];
				ch[x]=ch[y];
			}
		}
		cv.push_back({lt[y],id[y]});
		sort(cv.rbegin(),cv.rend());
		if(cv.size()>3)cv.pop_back();			
	}
	if(sm[x]<0 and cv.size()>1){
		if(cv[0].first+cv[1].first>sm[x]){
			sm[x]=cv[0].first+cv[1].first;
			ch[x]={cv[0].second,cv[1].second};
			dep[x]=0;
		}
	}
}
#define x1 x114514
#define y1 y114514
#define x2 x1919810
#define y2 y1919810
int cml,sml,x1,y1,x2,y2,bp[mxn];
vector<int>ee;bool fd;
int cnt=0;
inline void go(int x){
	v.clear(),dfs(x);
	if(v.size()<=5){
		for(int i:v)ban[i]=1;
		return;
	}
	dfs2(x);
	vector<pair<int,pair<int,pair<int,int> > > >cv;cv.clear();
	for(int y:g[x])if(!ban[y] and sm[y]>=0 and dep[y]>=0)cv.push_back({dep[y]+1,{sm[y],ch[y]}});
	if(cv.size()>1){
		sort(cv.rbegin(),cv.rend());
		if(cml<cv[0].first+cv[1].first or (cml==cv[0].first+cv[1].first and sml<cv[0].second.first+cv[1].second.first)){
			cml=cv[0].first+cv[1].first;
			sml=cv[0].second.first+cv[1].second.first;
			x1=cv[0].second.second.first,x2=cv[0].second.second.second;
			y1=cv[1].second.second.first,y2=cv[1].second.second.second;
		}
	}else if(cv.size()==1){
		vector<pair<int,int> >wr;wr.clear();
		for(int y:g[x])if(!ban[y] and dep[y]<0)wr.push_back({lt[y],id[y]});
		sort(wr.rbegin(),wr.rend());
		if(wr.size()>1){
			int tc=cv[0].first,ts=cv[0].second.first+wr[0].first+wr[1].first;
			if(tc>cml or (tc==cml and ts>sml)){
				cml=tc,sml=ts;
				x1=wr[0].second,x2=wr[1].second;
				y1=cv[0].second.second.first,y2=cv[0].second.second.second;
			}
		}
	}
	ban[x]=1;
	for(int y:g[x]){
		if(ban[y])continue;
		totn=sz[y];ma=mxn;
		findroot(y);
		go(root);
	}
}
int main(){
//	freopen("reveal.in","r",stdin);
//	freopen("reveal.out","w",stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;for(int i=1,u,v;i<n;++i)cin>>u>>v,g[u].push_back(v),g[v].push_back(u);
	totn=n;findroot(1,0);
	go(root);
	cout<<x1<<' '<<y1<<'\n'<<x2<<' '<<y2<<'\n';
	return 0;
}
```

---

