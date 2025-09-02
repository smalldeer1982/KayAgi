# Ant on the Tree

## 题目描述

Connected undirected graph without cycles is called a tree. Trees is a class of graphs which is interesting not only for people, but for ants too.

An ant stands at the root of some tree. He sees that there are $ n $ vertexes in the tree, and they are connected by $ n-1 $ edges so that there is a path between any pair of vertexes. A leaf is a distinct from root vertex, which is connected with exactly one other vertex.

The ant wants to visit every vertex in the tree and return to the root, passing every edge twice. In addition, he wants to visit the leaves in a specific order. You are to find some possible route of the ant.

## 样例 #1

### 输入

```
3
1 2
2 3
3
```

### 输出

```
1 2 3 2 1 ```

## 样例 #2

### 输入

```
6
1 2
1 3
2 4
4 5
4 6
5 6 3
```

### 输出

```
1 2 4 5 4 6 4 2 1 3 1 ```

## 样例 #3

### 输入

```
6
1 2
1 3
2 4
4 5
4 6
5 3 6
```

### 输出

```
-1
```

# 题解

## 作者：Alex_Wei (赞：11)

> 题目大意：给定一棵 $n$ 个节点的树，$1$ 为根节点。设其有 $k$ 个叶节点，给定一个叶节点的排列 $c_1,c_2,\cdots,c_k$，求路径 $1\to c_1\to c_2\to\cdots\to c_k\to 1$ 是否经过树上每条边 $2$ 次。是则输出路径，否则输出 $-1$。

$n$ 只有 $300$，连最无脑的 $n^3$ 暴力和无脑 $n^2$ 暴力都能过。但既然要追求效率，那就贯彻到底咯（

---

判断是否满足题目的要求可以树上差分，时间复杂度 $O(n\log n)$。

判断后暴力输出路径即可。因为每条边只会经过两次，所以点数是 $O(n)$ 级别的。输出路径时注意边界判断。

总时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair <int,int>
#define fi first
#define se second
#define pb push_back
#define all(x) x.begin(),x.end()
#define sortv(x) sort(all(x))
#define rev(x) reverse(all(x))
#define mem(x,v) memset(x,v,sizeof(x))

char buf[1<<21],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;

#ifdef __WIN64
	#define gc getchar()
#else
	#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
#endif
#define pc(x) (*O++=x)
#define flush() fwrite(obuf,O-obuf,1,stdout)

inline int read(){
	int x=0,sign=0; char s=getchar();
	while(!isdigit(s))sign|=s=='-',s=getchar();
	while(isdigit(s))x=(x<<1)+(x<<3)+(s-'0'),s=getchar();
	return sign?-x:x;
}
void print(int x){
	if(x>9)print(x/10);
	pc(x%10+'0');
}

const int N=305;
int n,fa[N][9],dep[N],c[N],l[N],leaf;
vector <int> e[N];
void dfs(int id,int f,int d){
	fa[id][0]=f,dep[id]=d;
	int isl=1;
	for(auto to:e[id])if(to!=f)dfs(to,id,d+1),isl=0;
	leaf+=isl;
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=8;~i;i--)if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=8;~i;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
void check(int id,int f){
	for(auto to:e[id])if(to!=f)check(to,id),c[id]+=c[to];
	if(id>1&&c[id]!=2)puts("-1"),exit(0);
}
void move(int from,int to){
	int rev=0;
	if(dep[from]<dep[to])swap(from,to),rev=1;
	vector <int> p;
	while(from!=to){
		p.pb(rev?from:fa[from][0]);
		from=fa[from][0];
	}
	if(rev)rev(p);
	for(auto it:p)cout<<it<<" ";
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u); 
	}
	dfs(1,0,1);
	for(int i=1;i<9;i++)for(int j=1;j<=n;j++)fa[j][i]=fa[fa[j][i-1]][i-1];
	l[0]=l[leaf+1]=1;
	for(int i=1;i<=leaf+1;i++){
		if(i<=leaf)cin>>l[i],c[l[i]]+=2;
		c[LCA(l[i-1],l[i])]-=2;
	}
	check(1,0);
	cout<<"1 ";
	for(int i=1;i<=leaf+1;i++){
		int d=LCA(l[i-1],l[i]);
		move(l[i-1],d),move(d,l[i]);
	}
    return 0;
}
```

可能有 $O(n)$ 的解法，~~太菜了想不出来。~~

---

## 作者：chenxia25 (赞：8)

>### [洛谷题目页面传送门](https://www.luogu.org/problemnew/show/CF29D) & [CodeForces题目页面传送门](https://www.codeforces.com/contest/29/problem/D)

>题意见洛谷里的翻译。

## 这题有$3$种解法，但只有$1$种是正解~~（这不是废话嘛）~~。
---
### 方法$1$：最近公共祖先LCA（正解）
真的把它当作一棵树来做。使用父亲表示法，记录每个节点的父亲。可是输入中只能告诉你谁和谁连，并没有说谁是谁的父亲，这该怎么办呢？~~其实很简单，只~~需要通过根是$1$这个信息，先把$1$的父亲设成自己，把所有$1$的邻居$i$的父亲都设成$1$，然后再对$i$进行如下操作：把所有$i$的“还没有父亲”的邻居$j$的父亲都设成$i$，然后对$j$进行如下操作：把所有$j$的“还没有父亲”的邻居$k$的父亲都设成$j$，然后对$k$进行如下操作……这样就做出来一棵树。我们还需要一个二维`bool`数组，在$\operatorname{O}\left(n^2\right)$时间内预处理出对于任意一对节点与叶子节点（也就是说第一维是任意节点，第二维是叶子节点）$(x,y)$，$x$是不是$y$的祖先。设叶子节点集合为$l$，然后从$1$走到$l_1$、从$l_1$走到$l_2$、……、从$l_{n-1}$走到$l_n$、从$l_n$走到$1$。对于每一次走，从起点一直向上走，一直走到是终点的祖先为止（相当于走到原起点和终点的最近公共祖先（LCA）），再向下走到终点，把经过的点都压入答案序列。最后如果答案序列的大小不是$2n-1$就输出$-1$，否则输出答案就可以了。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> nei[301]/*邻接表*/,ans/*答案序列*/;
int f[301];//父亲
bool ance[301][301];//[1]是否是[2]的祖先
void mktre(int x){//对x进行如下操作：
    for(int i=0;i<nei[x].size();i++)//将所有x的
        if(!f[nei[x][i]])/*“孤儿”邻居*/f[nei[x][i]]=x/*收养*/,mktre(nei[x][i])/*并对它进行如下操作……*/;
}
void go(int st,int ed){//从st走到ed
    while(!ance[st][ed])st=f[st],ans.push_back(st);//往上走到是ed的祖先为止
    vector<int> rev;
    while(st!=ed)rev.push_back(ed),ed=f[ed];//本应向下走，但用的是父亲表示法，只能向上走
    for(int i=rev.size()-1;i>=0;i--)ans.push_back(rev[i]);//倒过来压入答案序列
}
int main(){
    int n/*节点数*/,i;scanf("%d",&n);
    for(i=1;i<n;i++){
        int x,y;scanf("%d%d",&x,&y);
        nei[x].push_back(y);nei[y].push_back(x);
    }
    f[1]=1;/*1的父亲是自己*/mktre(1);//先对1进行操作
    int x=1,y;ance[1][1]=true;
    ans.push_back(1);//因为1没有机会压入答案序列，只好特殊招待
    while(~scanf("%d",&y)){
        int z=y;while(z!=1)ance[z][y]=true,z=f[z];ance[1][y]=true;//预处理ance
        go(x,y);x=y;//从l[i]走到l[i+1]
    }
    go(x,1);
    if(ans.size()>(n<<1)-1)return !printf("-1");//大小不是2n-1
    for(i=0;i<ans.size();i++)printf("%d ",ans[i]);//输出答案
    return 0;
}
```
这种方法的时间复杂度是$\mathrm{O}\left(n^2\right)$。因为做树的时间是边数，$\mathrm{O}(n)$；走一次的时间是$\mathrm{O}(n)$，走$n$次$\mathrm{O}\left(n^2\right)$。对于$300$的水数据，简直再容易不过了！

---
### 方法$2$：暴搜
不把这张图当作树来看，而当作图。走的时候，从起点~~毫无方向感地~~搜遍全图直到搜到终点为止。走的函数里要再加一个参数，表示走过来的节点，避免再回去，造成死循环。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> nei[301]/*邻接表*/,ans/*答案序列*/;
bool dfs(int st/*起点*/,int ed/*终点*/,int prv/*走过来的，避免死循环*/){//暴搜
	if(st==ed)return true;//到达了，带回这个喜讯
	for(int i=0;i<nei[st].size();i++)//枚举邻居
		if(nei[st][i]!=prv&&dfs(nei[st][i],ed,st)){//如果不是走过来的，那看看能不能搜到终点
			ans.push_back(nei[st][i]);//此时已经搜到了，压入答案序列
			return true;//搜到了，返回
		}
	return false;//没搜到
}
int main(){
	int i,n/*节点数*/;scanf("%d",&n);
	for(i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		nei[x].push_back(y);nei[y].push_back(x);
	}
	int x=1,y;
	while(~scanf("%d",&y))dfs(y,x,0),x=y;//从l[i]开始暴搜l[i+1]，因为dfs中是回溯时压入答案序列的，是反的，所以起点和终点也要反过来，反反得正
	dfs(1,x,0);
	ans.push_back(1);//因为1没有机会压入答案序列，只好特殊招待
	if(ans.size()>(n<<1)-1)return !printf("-1");
	for(i=0;i<ans.size();i++)printf("%d ",ans[i]);
	return 0;
}
```
暴搜中枚举邻居，每个邻居都可能将整个图遍历一遍，$\mathrm{O}\left(n^2\right)$，最多有$n$次暴搜，所以整个时间复杂度是$
\mathrm{O}\left(n^3\right)$。~~这时间复杂度是在欺负出题人的数据范围吗？~~

---
### 方法$3$：Floyd指路
聪明的读者也许~~一定~~没想到，这题还可以用Floyd吧！先用Floyd算出任意两点的最短路（邻居距离为$1$），然后在走的时候，就有方向~~、不盲目、不彷徨、自信~~了，~~很显然，~~走能够缩短与终点的距离的邻居呗！在这里，Floyd起到了指路的作用。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f//设成INT_MAX相加时会爆int
int dis[301][301]/*最短距离*/,n/*节点数*/;
vector<int> ans;//答案序列
void go(int st,int ed){//从st走到ed
	if(st==ed)return;//到达，返回
	for(int i=1;/*一定有能走的点，所以不需要终止条件*/;i++)//枚举每个点
		if(dis[st][i]==1/*是邻居*/&&dis[i][ed]<dis[st][ed]/*能缩短距离*/){//走
			ans.push_back(i);//压入答案序列
			go(i,ed);//走一步
			return;//能走的点只有一个，找到了就算成功了，不再找了
		}
}
int main(){
	int i,j;scanf("%d",&n);
	for(i=1;i<=n;i++)for(j=1;j<=n;j++)dis[i][j]=i==j?0:inf;//初始化dis
	for(i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		dis[x][y]=dis[y][x]=1;//邻居的距离为1
	}
	//Floyd
	for(int k=1;k<=n;k++)for(i=1;i<=n;i++)for(j=1;j<=n;j++)
		dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
//	for(i=1;i<=n;i++){for(j=1;j<=n;j++)printf("dis[%d][%d]=%d\t",i,j,dis[i][j]);puts("");}
	int x=1,y;
	ans.push_back(1);//因为1没有机会压入答案序列，只好特殊招待
	while(~scanf("%d",&y))go(x,y),x=y;//从l[i]走到l[i+1]
	go(x,1);
	if(ans.size()>(n<<1)-1)return !printf("-1");
	for(i=0;i<ans.size();i++)printf("%d ",ans[i]);
	return 0;
}
```
虽然有方向了，但也要为此付出代价——奇慢无比的Floyd。所以时间复杂度还是$\mathrm{O}\left(n^3\right)$。~~题目被虐了，出题人好可怜~~

---

## 作者：这有一只匿 (赞：2)

~~N只有300，看起来就可以乱搞，只要不玩过头了就应该不会炸~~

下面是乱搞做法

先dfs一遍找到每个点的父亲和叶子节点个数。

然后对每个叶子节点，向自己的父亲遍历，开一个数组h[i][j]表示第i节点的子树中是否有j节点，有就为1，否则为0。

接下来再dfs一次，按题目给的叶子节点的顺序遍历，就是走到一个点，看当前要走的叶子节点是否在它的子树内。而当你回溯到一个点时判断你现在要走的叶子节点是否被更新过了，如果更新过了，就再把这个点重新遍历，以防出现虽然现在要去的叶子节点是在这个点的子树内，但因为在找上一个叶子节点时已经遍历过了导致的漏了。

在遍历时记录遍历顺序，如果记录的遍历顺序中的数的个数不等于2*n-1，就输出-1，否则输出遍历顺序。

语文不好，可能没解释清楚，看不懂的欢迎私聊

乱搞代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define re register int 
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){if(A==B){B=(A=ss)+fread(ss,1,1<<17,stdin);if(A==B)return EOF;}return *A++;}
template <class T>inline void read(T & x){
	re y=1;char c;while(c=gc(),c<48||c>57)if(c=='-')y=-1;x=(c^48);
	while(c=gc(),47<c&&c<58)x=(x<<1)+(x<<3)+(c^48);x*=y;
}
const int MAX=310;
int n,fi[MAX],cnt,ans[MAX*10],top,fa[MAX],h[MAX][MAX],a[MAX],k,t;
struct hehe{
	int nx,nd;
}e[MAX*2];
void add(int a,int b)
{
	e[++cnt]=(hehe){fi[a],b},fi[a]=cnt;
}
void dfs_1(int x,int fat)
{
	int flag=0;
//	if(e[fi[x]].nd==fat)k++;
	for(int v=fi[x];v;v=e[v].nx)
	if(e[v].nd!=fat)
	{
		flag=1;
		fa[e[v].nd]=x;
		dfs_1(e[v].nd,x);
	}
	if(flag==0)k++;
}
void dfs(int x)
{
	if(x==a[t]){t++;return ;}
	for(int v=fi[x];v;v=e[v].nx)
	if(e[v].nd!=fa[x])
	{
		int last=t;
		if(h[e[v].nd][a[t]]==1)
		{ans[++top]=e[v].nd;dfs(e[v].nd);ans[++top]=x;}
		if(last!=t&&h[x][a[t]]==1)
		{
			dfs(x);break;
		}
	}
}
int main()
{
	read(n);
	for(int i=1;i<n;i++)
	{
		int a,b;
		read(a),read(b);
		add(a,b);add(b,a);
	}
	dfs_1(1,1);
	for(int i=1;i<=k;i++)
	{
	read(a[i]);
	int ff=a[i];
	h[a[i]][a[i]]=1;
	while(ff)
	{
		h[fa[ff]][a[i]]=1;
		ff=fa[ff];	
	}
	}
	ans[++top]=1;t=1;
	dfs(1);
	if(top==2*n-1)
	for(int i=1;i<=top;i++)cout<<ans[i]<<" ";
	else cout<<-1;
	return 0;
}














```

---

## 作者：Epi4any (赞：1)

就很莫名其妙，怎么题解区这么多 lca 的，更有甚者说 lca 是这道题最优且唯一的正确解法。我：？？？？？

这道题是一道好题，做法有 $O(n^3)$ 的 floyd，$O(n^2)$ 的 lca。本文介绍一个 $O(n \log n)$ 的贪心解法，具体地，用两遍 dfs 来实现。

这道题，不难发现，就是我们对子树进行重新排序，然后输出这个每个节点子树拍完序后的树的 dfs 序列。换句话说，我们只需要确定到每一个分叉应该先往哪个方向走。

于是不难想到对每个叶子结点进行编号，按序列中的出现顺序从小到大。我们只需要对每个节点按照其叶子节点的子树的编号最小的叶子节点的编号进行排序。

这件事我们进行一次 dfs 解决，样例 2 处理完大致长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/gxrcaf5z.png)

然后就好做了，每一个分叉我们都知道要往什么方向走，于是只需要按照规定顺序遍历一遍并存答案就行。存完答案记得再遍历一遍看叶子节点出现的顺序是否正确，如果错误那么就无解。

最后时间复杂度为 $O(n \log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=1e9+7;
const int maxn=305;
int n,val[maxn];
vector<int> mp[maxn],ans,tar;
bool cmp(int first, int second) {
    return val[first]<val[second];
}
void dfs1(int id, int _fa) {
    for(auto it:mp[id]) {
        if(it!=_fa) {
            dfs1(it,id);
            val[id]=min(val[id],val[it]);
        }
    }
}
void dfs2(int id, int _fa) {
    ans.push_back(id);
    for(auto it:mp[id]) {
        if(it!=_fa) {
            dfs2(it,id);
            ans.push_back(id);
        }
    }
}
int main() {
    cin>>n;
    for(int i=1;i<=n;i++) {
        val[i]=INF;
    }
    for(int i=1;i<n;i++) {
        int u,v;
        cin>>u>>v;
        mp[u].push_back(v);
        mp[v].push_back(u);
    }
    int tmp,id=1;
    while(cin>>tmp) {
        tar.push_back(tmp);
        val[tmp]=id;
        id++;
    }
    dfs1(1,1);
//    for(int i=1;i<=n;i++) {
//        cout<<val[i]<<" ";
//    }
//    cout<<endl;
    for(int i=1;i<=n;i++) {
        sort(mp[i].begin(),mp[i].end(),cmp);
//        for(auto it:mp[i]) {
//            cout<<it<<" ";
//        }
//        cout<<endl;
    }
    dfs2(1,1);
    int pos=0;
    for(auto it:tar) {
        while(ans[pos]!=it) {
            pos++;
            if(pos>=ans.size()) {
                cout<<-1<<endl;
                return 0;
            }
        }
    }
    for(auto it:ans) {
        cout<<it<<" ";
    }
    cout<<endl;
    return 0;
}

```

---

## 作者：有趣的问题 (赞：1)

翻了一下题解区，似乎没有跟我一样的做法？这里提供一种不用 LCA，复杂度同样为 $O(n\log n)$ 的做法。

### 解题思路

因为我们对叶子节点的遍历顺序有一定要求，我们考虑要走到叶子节点一定会走到他的所有祖先。

于是我们可以 DFS 一遍整棵树，给每个节点一个优先级。叶子节点的优先级就是遍历到他的顺序，其他节点的优先级则是它子树内所有叶节点优先级的最小值。特别地，对于没有规定遍历顺序的叶子结点，我们可以直接把它的优先级设为 $n$。

然后我们再 DFS 一遍，这次 DFS 的顺序就是我们要的答案。DFS 的过程中遵循两个原则：

1. 一旦遍历到某个节点，就要把该节点的子树遍历完。

2. 每次按优先级的顺序遍历一个节点的儿子。

在 DFS 的同时，我们记录一下当前经过叶节点的序是否与题目要求相符，不相符则说明无解。

### 丑陋的代码

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,cnt,lst[305],xu[305],tmp,now=1,wt[305];
struct edge{
	int f,t,lst;
	edge(int f=0,int t=0,int lst=0):
		f(f),t(t),lst(lst){};
}e[605];
void add(int u,int v){
	e[++cnt]=edge(u,v,lst[u]);lst[u]=cnt;
	e[++cnt]=edge(v,u,lst[v]);lst[v]=cnt;
}
int dfs(int u,int f){
	int ret=n+1;
	if(xu[u])ret=xu[u];
	for(int i=lst[u];i;i=e[i].lst){
		int v=e[i].t;
		if(v==f)continue;
		ret=min(ret,dfs(v,u));
	}
	wt[u]=ret;
	return ret;
}
vector<int> ans;
struct node{
	int id;
	bool operator<(node b)const{
		return wt[id]<wt[b.id];
	}
};
bool dfs2(int u,int f){
	ans.push_back(u);
	if(xu[u]&&xu[u]!=now)return 0;
	if(xu[u])now++;
	vector<node> son;
	for(int i=lst[u];i;i=e[i].lst){
		int v=e[i].t;
		if(v==f)continue;
		son.push_back((node){v});
	}
	sort(son.begin(),son.end());
	bool ret=1;
	for(int i=0;i<son.size();i++){
		ret&=dfs2(son[i].id,u);
		ans.push_back(u);
	}
	return ret;
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
	}
	int now;
	while(cin>>now){
		xu[now]=++tmp;
	}
	dfs(1,0);
	if(!dfs2(1,0))puts("-1");
	else{
		for(int i=0;i<ans.size();i++)cout<<ans[i]<<' ';
	}
	return 0;
}

```



---

## 作者：Drind (赞：0)

感觉大家都用的是很高端的做法，这里提供一种空间复杂度和时间复杂度都是 $O(\frac{n^2}{w})$ 的做法。


首先我们每个点开一个 bitset 来存他以及他的子树里有多少种点，用一次深度优先搜索可以预处理这个问题。然后我们每次贪心地往下走到那个有这次我们要找的点的位置即可。

实现见代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;

struct node{
	int to,nxt;
}edge[N*2]; int head[N],cnt;
void add(int u,int v){
	edge[++cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
void adde(int u,int v){
	add(u,v); add(v,u);
}

queue<int>q;
int dir[N],p;
int tot;

bitset<310>tmp[310];

void dfs1(int u,int fa){
	tmp[u][u]=1;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to; if(v==fa) continue;
		dfs1(v,u); tmp[u]|=tmp[v];//和预处理子树大小类似
	}
	if(tmp[u].count()==1) tot++;
}

int root;

void dfs2(int u,int fa,int rep){
	q.push(u);
	if(dir[p]==u){//如果找到了就往下找第下一个
		p++; 
	}
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to; if(v==fa) continue;
		if(tmp[v][dir[p]]==1) dfs2(v,u,rep);//往有下一个的地方走去
		if(rep!=p){
			rep=p; dfs2(u,fa,rep); return;//注意如果我们找到一个了之后，再找下一个点可能是在我们这个子树里已经遍历过的节点里的，所以需要重启一次循环。
		}
	}
}

inline void fake_main(){
	int n; cin>>n;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		adde(u,v);
	} 
	dfs1(1,0);
	for(int i=1;i<=tot;i++) cin>>dir[i]; p=1;
	dfs2(1,0,p);
	if(p>tot&&q.size()==2*n-1){//注意这么做可能会把一些应该返回-1的情况找出解，所以需要特判，这个特判可以扔到dfs当做剪枝跑的快一点，但是这道题n<=300没有必要了
		while(!q.empty()){
			cout<<q.front()<<" "; q.pop();
		} 
	}else cout<<"-1\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：封禁用户 (赞：0)

翻译自己去看[原文翻译](https://www.luogu.com.cn/problem/CF29D)，我认为没有必要在此画蛇添足。

思路就是先从根节点一路找到第一个叶子节点，然后往上找，找到能与第二个叶子节点重合的地方，接着继续往下，重复这个操作直到结束。

大概是这个样子的？~~我实在找不到比图片表达更为清晰的方式了。~~

下面是样例 $2$ 的解释。

![](https://cdn.luogu.com.cn/upload/image_hosting/k1mzv4un.png)

最后判断是否每条边都走过了 $2$ 次，如果为否就输出 $-1$，否则输出答案。

于是这就是我们的思路。总体往上面找是 $O(n)$，往下也是 $O(n)$，最多有 $n$ 个叶子，于是最坏时间复杂度就是 $O(n ^ 2)$，可以通过本题。

听说这题 LCA 才是正解，但是因为作者菜的可怜，最好也只能想出 $O(n ^ 2)$ 的解法，至于 $O(n ^ 3)$ 的暴搜？我觉得对于一道蓝题不太合适，不过也不是不行。

这题代码比较难写，一定要注意，**一不小心你就会写出臃肿的代码，就像我一样**。

我的代码里对于答案的输出，前面乱搞了一下（fix 函数），不知道具体该怎么改，猜测是在 go 函数里出锅了。

以下是本人的 AC 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> g[500];
vector<int> t[500];
int deg[500] = {0};

bool find(vector<int> &path, int fa, int u, int tar) {
	if (u == tar) return true;
	for (int i = 0; i < g[u].size(); i++) 
		if (fa != g[u][i]) {
			path.push_back(i);
			if (find(path, u, g[u][i], tar)) return true;
			path.pop_back();
		}
	return false;
}

void go(vector<int> &ans, vector<int> &p1, vector<int> &p2) {
	int u = 1, _u;
	int i = 0, j;
	while (i < min(p1.size(), p2.size()) && p1[i] == p2[i]) {
		u = g[u][p1[i]];
		i++;
	}
	vector<int> v;
	for (j = i, _u = u; j < p1.size(); j++) {
		v.push_back(_u);
		t[_u][p1[j]]++;
		_u = g[_u][p1[j]];
	}
	for (int i = v.size() - 1; i >= 0; i--) ans.push_back(v[i]);
	v.clear();
	for (j = i, _u = u; j < p2.size(); j++) {
		v.push_back(_u);
		t[_u][p2[j]]++;
		_u = g[_u][p2[j]];
	}
	v.push_back(_u);
	for (int i = 0; i < v.size(); i++) ans.push_back(v[i]);
}

void tryno(int fa, int u) {
	for (int i = 0; i < g[u].size(); i++)
		if (fa != g[u][i]) {
			if (t[u][i] != 2) {
				cout << -1 << endl;
				exit(0);
			}
			tryno(u, g[u][i]);
		}
}

void fix(vector<int> &v) {
	vector<int> vv = {v[0]};
	for (int i = 1; i < v.size(); i++)
		if (v[i - 1] != v[i])
			vv.push_back(v[i]);
	v = vv;
}

int main() {
	int n;
	cin >> n;
	deg[1] = 1;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
		deg[u]++;
		deg[v]++;
	}
	int k = count(deg + 1, deg + 1 + n, 1);
	vector<vector<int> > p(k + 2, vector<int>());
	for (int i = 1; i <= k; i++) {
		int temp;
		cin >> temp;
		find(p[i], 0, 1, temp);
	}
	vector<int> ans;
	for (int i = 1; i <= n; i++)
		t[i] = vector<int>(g[i].size(), 0);
	for (int i = 1; i <= k + 1; i++)
		go(ans, p[i - 1], p[i]);
	tryno(0, 1);
	fix(ans);
	for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
	cout << endl;
	return 0;
}
```

---

## 作者：xieyikai2333 (赞：0)

# 一道有意思的 LCA ~~水~~题

- **[洛谷题目页面传送门](https://www.luogu.com.cn/problem/CF29D) & [CodeForces题目页面传送门](https://codeforces.com/contest/29/problem/D)**

---

- 先建立一个 $from$ 数组，记录各点的父亲；
- 搜索整棵树：记录各节点的深度存放在 $d$ 数组中，记录每条边走过的次数存放在 $vis$ 数组中；
- 对于遍历顺序从先到后连续的两叶节点 $x$ ， $y$ ，蚂蚁先走到 $x$ ，再走至 $x$ ， $y$ 的 LCA ，再走至 $y$ ；
- 再枚举每一条边，若有一条边走过的次数不是两次，则输出 $-1$ ，否则输出答案。

---

### 如何求两个节点 $x$ , $y$ 的 LCA ：
1. 让深度更大的节点 $x$ 向上走，直到 $x$ 与 $y$ 深度相等；
2. 如果 $x$ 与 $y$ 不相等，那么 $x$ 与 $y$ 一同向上走；
3. **当 $x$ 与 $y$ 相等时**，当前它们的位置就是原先两个节点的 LCA 。
___

#### AC代码:
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> nodes[305],ans;
int from[305],leaf[305],d[305],vis[305][305],cnt;
void work(int u,int depth)
{
	int i,v;
	d[u]=depth;
	if(nodes[u].size()==1&&u!=1)
	{
		cnt++;
		return;
	}
	for(i=0;i<nodes[u].size();i++)
	{
		v=nodes[u][i];
		if(v==from[u])continue;
		from[v]=u;
		work(v,depth+1);
	}
	return;
}
int lca(int u,int v)
{
	if(d[u]>d[v])swap(u,v);
	int delta=d[v]-d[u];
	while(delta--)v=from[v];
	while(u!=v)u=from[u],v=from[v];
	return u;
}
void go1(int goal,int u)
{
	if(u==goal)return;
	vis[u][from[u]]++;
	go1(goal,from[u]);
	ans.push_back(u);
	return;
}
void go2(int u,int goal)
{
	if(u==goal)return;
	vis[u][from[u]]++;
	ans.push_back(from[u]);
	go2(from[u],goal);
	return;
}
int main()
{
	int n,i,j,u,v;
	scanf("%d",&n);
	for(i=1;i<n;i++)
	{
		scanf("%d %d",&u,&v);
		nodes[u].push_back(v);
		nodes[v].push_back(u);
	}
	work(1,1);
	for(i=1;i<=cnt;i++)scanf("%d",&leaf[i]);
	ans.push_back(1);
	go1(1,leaf[1]);
	for(i=2;i<=cnt;i++)
	{
		go2(leaf[i-1],lca(leaf[i-1],leaf[i]));
		go1(lca(leaf[i-1],leaf[i]),leaf[i]);
	}
	go2(leaf[cnt],1);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if((from[i]==j||from[j]==i)&&vis[i][j]+vis[j][i]!=2)
			{
				printf("-1");
				return 0;
			}
		}
	}
	for(i=0;i<ans.size();i++)printf("%d ",ans[i]);
	return 0;
}
```
---

附上[AC记录](https://www.luogu.com.cn/record/52743964)

---

## 作者：unordered_yao (赞：0)

## 思路
1. 我们要按照题目询问顺序输出路径，那么怎样才能找到正确的路径，这是个难点。
2. 我们可以通过 floyd 来找这个路径。如果当前点到目标点的距离大于下一个点到目标点的距离，我们可以通过这个点继续寻找下一点，递归的终点即可。
3. 怎样判非法询问呢？如果有 $n$ 个点，因为所有遍历到的最后一个点只会遍历一次，题目要求每条边要遍历两次，从而得到规律，所以答案中存的路径经过的点的个数大于 $2\times n - 1$ 那么就是非法情况。
4. 注意，递归到最后一个点时，别忘了再从最后一个询问的点递归返回根节点！
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int dist[330][330];
int ans[330*330],idx;
void deal(int x,int y){
    if(x==y) return;
    for(int i=1;;i++){
        if(dist[x][i]==1&&dist[i][y]<dist[x][y]){
            ans[idx++] = i;
            deal(i,y);
            return;
        }
    }
}
int main(){
    read(n);
    memset(dist,0x3f,sizeof dist);
    for(int i=1;i<=n;i++) dist[i][i]=0;
    for(int i=0;i<n-1;i++){
        int a,b;
        read(a,b);
        dist[a][b]=dist[b][a]=1;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(dist[i][j] > dist[i][k]+dist[k][j])
                    dist[i][j] = dist[i][k]+dist[k][j];
    
    int x=1,y;
    ans[idx++]=1;
    while(cin >> y) deal(x,y),x=y;
    deal(x,1);
    if(idx>2*n-1) write(-1),exit(0);
    for(int i=0;i<idx;i++) write(ans[i]);
    return 0;
}
```

---

## 作者：XL4453 (赞：0)


### 解题思路：

LCA 简单题。

首先遍历一遍处理出父子节点关系，然后预处理倍增，准备做倍增 LCA。

然后每一次从一个叶子结点移动到 LCA，再从 LCA 移动到下一个叶子结点，这里可以直接往上跳，最后翻转一下。同时记录走过的序列。一旦序列长度超过了 $2n-1$，那么一定无解（注意这里在中途判断比较方便，否则数组要开好大，还有可能 RE）。

到最后判断一下总长度是不是 $2n-1$ 的，如果是，那么一定可行，反之一定不可行。

---

其实这是一个结论，但其他题解好像都没有给出证明，这里提一下（其实是显然的）。

直接证明需要分可行和不可行的充分性和必要性，很烦，考虑证明 $2n-1$ 是可能走过的最少的一种点的数目，这样直接就能得出结论。

考虑模拟遍历的过程，当任意一个非根节点被遍历的时候，其被加入搜索栈是这个点连向根节点的边会被经过一次，然后回溯的时候也会经过一次，也就是说这个节点一旦被经过就一定有这个节点的父亲边被经过至少两次。

由于题目中说每一个叶子结点都会被经过，所以一定有每一个节点被经过至少一次，所以至少有 $2n-2$ 条边被经过，所以一定有 $2n-1$ 个点（每两个输出点之间经过了一条边），这样就证明完了。

---

注意 next 是保留字。

---
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,head[1005],next_[1005],num[1005],tot,k;
int fa[1005][30],ord[1005],deep[1005],cnt,ans[3005];
void swap(int &a,int &b){a^=b;b^=a;a^=b;}
void add(int x,int y){
	next_[++tot]=head[x];head[x]=tot;num[tot]=y;
}
void dfs(int now,int fath,int dep){
	int cnt=0;
	fa[now][0]=fath;
	deep[now]=dep;
	for(int i=head[now];i;i=next_[i])
	if(num[i]!=fath)
	dfs(num[i],now,dep+1),cnt++;
	if(cnt==0)k++;
}
int LCA(int a,int b){
	if(deep[a]<deep[b])swap(a,b);
	for(int i=20;i>=0;i--)
	if(deep[fa[a][i]]>deep[b])
	a=fa[a][i];
	if(deep[a]>deep[b])a=fa[a][0];
	if(a==b)return a;
	for(int i=20;i>=0;i--)
	if(fa[a][i]!=fa[b][i]){
		a=fa[a][i];
		b=fa[b][i];
	}
	return fa[a][0];
}
void Swap(int f,int t){
	for(int i=f;i<=(f+t+1)/2-1;i++)
	swap(ans[i],ans[t+f-i]);
}
void go_(int now,int pos){
	int lca=LCA(now,pos);
	while(now!=lca){
		now=fa[now][0];
		ans[++cnt]=now;
	}
	int CNT=cnt;
	if(cnt>2*n-1){
		printf("-1\n");
		exit(0);
	}
	while(pos!=lca){
		ans[++cnt]=pos;
		pos=fa[pos][0];
	}
	Swap(CNT+1,cnt);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,1,1);
	
	for(int i=1;i<=20;i++)
	for(int j=1;j<=n;j++)
	fa[j][i]=fa[fa[j][i-1]][i-1];	
	
	for(int i=1;i<=k;i++)
	scanf("%d",&ord[i]);
	
	ans[cnt=1]=1;
	ord[0]=1;
	for(int i=1;i<=k;i++)
	go_(ord[i-1],ord[i]);
	go_(ord[k],1);
	
	if(cnt!=2*n-1){
		printf("-1\n");
		return 0;
	}
	for(int i=1;i<=cnt;i++)
	printf("%d ",ans[i]);
	return 0;
}
```


---

