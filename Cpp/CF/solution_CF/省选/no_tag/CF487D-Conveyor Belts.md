# Conveyor Belts

## 题目描述

Automatic Bakery of Cyberland (ABC) recently bought an $ n×m $ rectangle table. To serve the diners, ABC placed seats around the table. The size of each seat is equal to a unit square, so there are $ 2(n+m) $ seats in total.

ABC placed conveyor belts on each unit square on the table. There are three types of conveyor belts: "^", "<" and ">". A "^" belt can bring things upwards. "<" can bring leftwards and ">" can bring rightwards.

Let's number the rows with $ 1 $ to $ n $ from top to bottom, the columns with $ 1 $ to $ m $ from left to right. We consider the seats above and below the top of the table are rows $ 0 $ and $ n+1 $ respectively. Also we define seats to the left of the table and to the right of the table to be column $ 0 $ and $ m+1 $ . Due to the conveyor belts direction restriction there are currently no way for a diner sitting in the row $ n+1 $ to be served.

Given the initial table, there will be $ q $ events in order. There are two types of events:

- "A $ x $ $ y $ " means, a piece of bread will appear at row $ x $ and column $ y $ (we will denote such position as $ (x,y) $ ). The bread will follow the conveyor belt, until arriving at a seat of a diner. It is possible that the bread gets stuck in an infinite loop. Your task is to simulate the process, and output the final position of the bread, or determine that there will be an infinite loop.
- "C $ x $ $ y $ $ c $ " means that the type of the conveyor belt at $ (x,y) $ is changed to $ c $ .

Queries are performed separately meaning that even if the bread got stuck in an infinite loop, it won't affect further queries.

## 说明/提示

For the first sample:

If the bread goes from $ (2,1) $ , it will go out of the table at $ (1,3) $ .

After changing the conveyor belt of $ (1,2) $ to "<", when the bread goes from $ (2,1) $ again, it will get stuck at "><", so output is $ (-1,-1) $ .

## 样例 #1

### 输入

```
2 2 3
>>
^^
A 2 1
C 1 2 <
A 2 1```

### 输出

```
1 3
-1 -1
```

## 样例 #2

### 输入

```
4 5 7
><<^<
^<^^>
>>>^>
>^>>^
A 3 1
A 2 2
C 1 4 <
A 3 1
C 1 2 ^
A 3 1
A 2 2```

### 输出

```
0 4
-1 -1
-1 -1
0 2
0 2
```

# 题解

## 作者：yinianxingkong (赞：5)

简洁的题解。

如果不带修怎么做？直接并查集模拟就行。

带修怎么半？操作序列分治树即可（这是我们的红太阳 @jzp1025 的叫法，或许它有个更出名的名字“线段树分治”）。

复杂度 $O(n \log^2 n)$，与板子没有太大区别。

[代码为目前最优解。](https://codeforces.com/contest/487/submission/272647245)

---

## 作者：_Eriri_ (赞：3)

怎么说，还是太水了。

这题和弹飞绵羊比较类似，带修用不了倍增，所以用分块或者 LCT 来加速，这里提供 LCT 的做法。

其实很简单，总共 $nm$ 个点，每个点向它所指的方向连边，我们假设不会有走死循环的边，即没有环边，则显然会形成树结构，这个时候一个点走到的终点就是它所属树的根。

重点在于环边的处理，这边肯定是不能连的，只能把它存起来，直到某一次修改后它不是环边，再把它指出去。想一下不连边的后果是什么，无非就是走到它就停了，这个时候终点没法在边界外，输出-1就行。

具体实现：
假如将点 $(x,y)$ 的权值改变，来看它的影响

1. 所有指向它的边不用做任何修改，就算修改后这些边和新边成环，不连 $(x,y)$ 指的边就行，不会对答案造成影响。

2. 断开它原先指的边(没有就不断)，然后看新指的边是不是环边，是就不连，不是才连。

3. 设修改前 $(x,y)$ 指向 $(x',y')$，在第2步时，这两个点之间的边已经断开。如果 $(x',y')$ 预存了指回 $(x,y)$ 的环边，再次尝试指出它，所以这时候原先不连的环边就起了作用。

查询的话，先看根在不在边界上，再看能不能走出去就行了，比较简单。

总时间复杂度 $O(nm+q\log nm)$ 不依赖 $m$ 很小的条件，这就是高级数据结构。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int M=15;

int n,m,q;
char a[N][M];
int bj[N][M];
 
#define d(x,y) (m*(x-1)+y)
int fa[N*M],ch[N*M][2];
#define get(u) (u==ch[fa[u]][1])
#define isRoot(u) (u!=ch[fa[u]][0] && u!=ch[fa[u]][1])

void rotate(int x){
	int y=fa[x],z=fa[y],k=get(x);
	if(!isRoot(y))ch[z][get(y)]=x;
	fa[x]=z,fa[y]=x;
	fa[ch[x][k^1]]=y,ch[y][k]=ch[x][k^1];
	ch[x][k^1]=y;
}
void splay(int x){
	for(int f=fa[x];!isRoot(x);rotate(x),f=fa[x])
		if(!isRoot(f))rotate(get(x)==get(f)?f:x);
}
void Access(int x){
	int p=0;
	for(;x;p=x,x=fa[x]){
		splay(x);
		ch[x][1]=p; 
	}
}
void Link(int x,int y){
	splay(x);
	fa[x]=y;
}
void Cut(int x,int y){
	Access(x);
	splay(y);
	ch[y][1]=fa[ch[y][1]]=0;
}
int FindRoot(int x){
	Access(x);
	splay(x);
	while(ch[x][0])x=ch[x][0];
	splay(x);
	return x;
}
int Conn(int x,int y){
	return FindRoot(x)==FindRoot(y);
}
void TryToLink(int i,int j){
	bj[i][j]=0;
	if(a[i][j]=='^'&&i>1){
		Link(d(i,j),d(i-1,j)),bj[i][j]=d(i-1,j);
	}
	if(a[i][j]=='<'&&j>1){
		if(!Conn(d(i,j),d(i,j-1)))Link(d(i,j),d(i,j-1)),bj[i][j]=d(i,j-1);
		else bj[i][j]=-1;
	}
	if(a[i][j]=='>'&&j<m){
		if(!Conn(d(i,j),d(i,j+1)))Link(d(i,j),d(i,j+1)),bj[i][j]=d(i,j+1);
		else bj[i][j]=-1;
	}		
}

void Leap(int p){	 
	int to=FindRoot(p);	

	int x=(to+m-1)/m,y=(to%m==0?m:to%m);
	
	 
	if(to%m==0&&a[x][y]=='>'){
		cout<<x<<' '<<y+1<<'\n';
		return ;
	} 
	if((to%m==1 || (m==1&&y==1))&&a[x][y]=='<'){
		cout<<x<<' '<<y-1<<'\n';
		return ;
	} 	
	if(to<=m&&a[x][y]=='^'){
		cout<<x-1<<' '<<y<<'\n';
		return ;
	} 
	cout<<-1<<' '<<-1<<'\n';
}


int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>m>>q;	
	for(int i=1;i<=n;i++){
		string s;cin>>s;s=" "+s;
		for(int j=1;j<=m;j++){
			a[i][j]=s[j];
			TryToLink(i,j);
		}
	}
	for(int i=1;i<=q;i++){
		char op,val;int x,y;
		cin>>op>>x>>y;
		if(op=='A')Leap(d(x,y));
		else {
			cin>>val;
			int last=0;
			if(bj[x][y]>=1){
				Cut(d(x,y),bj[x][y]);
				last=bj[x][y];
			}
			
			a[x][y]=val;
			TryToLink(x,y);
			
			if(last>=1){
				int lx=(last+m-1)/m,ly=(last%m==0?m:last%m);
				if(bj[lx][ly]==-1)TryToLink(lx,ly);				
			}
		}
	}
	
	return 0;
}
```
和我说的会有一点不一样，但是里面的细节还是要读者揣摩，若有不懂可以向我提问。

---

## 作者：IkunTeddy (赞：3)

# 前言

怎么没人写 LCT 啊，只有我来写一篇了。

# 题目分析

每个点的的路线显然是唯一的，换句话说下一步是唯一的，那么如果把下一步当做父亲，那么构成一个森林。

但是无限循环的情况例外，但是我们把所有无限循环的点的父亲指向一个虚点，就解决了这个问题。

最后的答案就是这个点所属树的根节点。

修改就是修改一个点的父亲，动态森林，我们直接考虑 LCT 维护。

无限循环的情况有且只有 ```><``` 才会无限循环，所以特判一下就行。

# Code


```cpp
//饺子皮是圆皮
#include<bits/stdc++.h>
using namespace std;
//
const int maxn=1e5+10;
int n,m,q;
char s[maxn][15];
int fa[maxn*15],idx[maxn][15];
int id(int x,int y){return idx[x][y];}
void out(int id){
	int x=(id-1)/(m+2),y=id-x*(m+2)-1;
	if(x==n+1&&y==m+1){
		cout<<-1<<' '<<-1<<'\n';
		return ;
	}
	cout<<x<<' '<<y<<'\n';
}
//
struct node{
	int fa,son[2];
	node(){fa=son[0]=son[1]=0;}
}tree[maxn*15];
int isroot(int v){return v!=tree[tree[v].fa].son[0]&&v!=tree[tree[v].fa].son[1];}
int get(int v){return v==tree[tree[v].fa].son[1];}
void rotate(int v){
	int f=tree[v].fa,g=tree[f].fa,chk=get(v);
	if(!isroot(f))tree[g].son[get(f)]=v;
	tree[v].fa=g;
	tree[f].son[chk]=tree[v].son[chk^1];
	if(tree[v].son[chk^1])tree[tree[v].son[chk^1]].fa=f;
	tree[v].son[chk^1]=f;
	tree[f].fa=v;
}
void splay(int v){
	while(!isroot(v)){
		int f=tree[v].fa;
		if(!isroot(f))rotate(get(f)==get(v)?f:v);
		rotate(v);
	}
}
void access(int v){
	int p=0;
	while(v){
		splay(v);
		tree[v].son[1]=p;
		p=v,v=tree[v].fa;
	}
}	
int findroot(int v){
	access(v);
	splay(v);
	while(tree[v].son[0])v=tree[v].son[0];
	splay(v);
	return v;
}
void link(int x,int y){
	tree[x].fa=y;
}
void cut(int x){
	access(x);
	splay(x);
	int y=tree[x].son[0];
	tree[x].son[0]=tree[y].fa=0;
}
void update(int x,int y){
	cut(x);
	fa[x]=y;
	link(x,fa[x]);
}
int main(){
	cin>>n>>m>>q;
	for(int i=0;i<=n+1;i++){
		for(int j=0;j<=m+1;j++){
			idx[i][j]=i*(m+2)+j+1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]=='<'){
				if(s[i][j-1]!='>')fa[id(i,j)]=id(i,j-1);
				else fa[id(i,j)]=id(n+1,m+1);
			}
			if(s[i][j]=='>'){
				if(s[i][j+1]!='<')fa[id(i,j)]=id(i,j+1);
				else fa[id(i,j)]=id(n+1,m+1);
			}
			if(s[i][j]=='^')fa[id(i,j)]=id(i-1,j);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			link(id(i,j),fa[id(i,j)]);
		}
	}
	while(q--){
		char op,k;
		int x,y;
		cin>>op>>x>>y;
		if(op=='A'){
			out(findroot(id(x,y)));
		}else{
			if(s[x][y]=='<'){
				if(s[x][y-1]=='>'){
					update(id(x,y-1),id(x,y));
				}
			}
			if(s[x][y]=='>'){
				if(s[x][y+1]=='<'){
					update(id(x,y+1),id(x,y));
				}
			}
			cin>>k;
			s[x][y]=k;
			if(s[x][y]=='<'){
				if(s[x][y-1]!='>'){
					update(id(x,y),id(x,y-1));
				}
				else{
					update(id(x,y),id(n+1,m+1));
					update(id(x,y-1),id(n+1,m+1));
				}
			}
			if(s[x][y]=='>'){
				if(s[x][y+1]!='<'){
					update(id(x,y),id(x,y+1));
				}
				else{
					update(id(x,y),id(n+1,m+1));
					update(id(x,y+1),id(n+1,m+1));
				}
			}
			if(s[x][y]=='^'){
				update(id(x,y),id(x-1,y));
			}
		}
	}
	
	return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：2)

[传送门](https://codeforces.com/contest/487/problem/D)

第一篇分块题解在讲啥啊...

#### 分析：

放现在最多 2300* 了......但是本身是很棒的题。

- 没有向下走

- 只有 $10$ 列

第一点启发我们按行进行转移。就是说我们可以设 $next(i,j)$ 表示从 $(i,j)$ 出发，会从 $(i,next(i,j))$ 这个格子向上走。$next$ 里要特判走出去，或者在这一行死循环的情况。

发现此时修改操作只会影响一行的 $next$，可以 $O(m)$ 解决，近似常数。然而 $n$ 很大，而一次查询最多要跳 $n$ 行，太慢。

优化跳跃过程，主流的有倍增和分块（或者根号分治一类的算法）。这里带修，所以首先考虑分块。事实上很容易联想到 CF13E Holes（你可能做过它的双倍经验 弹飞绵羊）。

这里的分块，就是指我们把 $\sqrt{n}$ 行合为一块，$next(i,j)$ 的定义改为走到的最后一个在 $(i,j)$ 的节点位置。同样需要特殊记录走出去和死循环的情况。发现可以在 $O(m\sqrt n)$ 的时间内完成对一块里 $next$ 的修改，同时单词询问的跳跃次数也缩为了 $O(\sqrt{n})$。然后修改操作次数 $\le 10^4$，所以总复杂度可以视为 $O(n\sqrt{n})$。





稍微讲一下如何实现在块长复杂度内计算块内 $next$ 的值。直接暴力枚举每一个点。$vis(i,j)=0$ 表示该点从未被访问，$vis(i,j)=1$ 表示该点的 $next$ 已经计算出，$vis(i,j)=2$ 
表示该点的 $next$ 正在计算。

不难发现如果下一个点（走出去了特判）的 $vis$ 为 $0$ 就继续递归算下去，然后继承 $next$，为 $1$ 就直接继承 $next$，为 $2$ 就说明死循环，直接退出。不难发现总复杂度就是 $O(size)$（块长）。

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e5+10,MAXM=12,MAXK=350;
int n,m,q,x,y,lim;
int num[MAXN],st[MAXN],ed[MAXN],tot;
int vis[MAXN][MAXM];
ppi nxt[MAXN][MAXM];
char s[MAXN][MAXM],op,ch;
void dfs(int r,int c){
	vis[r][c]=2;
	int rr=r,cc=c;
	if(s[r][c]=='<')cc--;
	else if(s[r][c]=='>')cc++;
	else rr--;
	if(num[rr]!=num[r] || cc<1 || cc>m){
		nxt[r][c]=mp(1,mp(r,c));
		vis[r][c]=1;
		return;
	}
	if(vis[rr][cc]==0){
		dfs(rr,cc);
		nxt[r][c]=nxt[rr][cc];
		vis[r][c]=1;
		return;
	}
	if(vis[rr][cc]==1){
		nxt[r][c]=nxt[rr][cc];
		vis[r][c]=1;
		return;
	}
	nxt[r][c]=mp(2,mp(r,c));
	vis[r][c]=1;
	return;
}
void pre(){
	rep(i,1,n){num[i]=(i-1)/lim+1;}
	rep(i,1,n){
		if(num[i-1]!=num[i])st[num[i]]=i;
		if(num[i+1]!=num[i])ed[num[i]]=i;
	}
	tot=num[n];
	rep(i,1,tot){
		rep(r,st[i],ed[i]){
			rep(c,1,m){
				if(!vis[r][c]){
					dfs(r,c);
				}
			}
		}
	}
}
void update(){
	s[x][y]=ch;
	int d=num[x];
	rep(r,st[d],ed[d]){
		rep(c,1,m){
			vis[r][c]=0;
		}
	}
	rep(r,st[d],ed[d]){
		rep(c,1,m){
			if(!vis[r][c]){
				dfs(r,c);
			}
		}
	}
}
void query(){
	int r=x,c=y;
	while(1){
		if(nxt[r][c].fr==2){
			r=c=-1;break;
		}
		int rr=nxt[r][c].se.fr,cc=nxt[r][c].se.se;
		r=rr,c=cc;
		if(s[r][c]=='<')cc--;
		else if(s[r][c]=='>')cc++;
		else rr--;
		r=rr;c=cc;
		if(rr<1 || cc<1 || cc>m)break;
	}
	printf("%d %d\n",r,c);
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	lim=sqrt(n)+1;
	rep(i,1,n)rep(j,1,m)scanf(" %c",&s[i][j]);
	pre();
	rep(i,1,q){
		scanf(" %c%d%d",&op,&x,&y);
		if(op=='C'){
			scanf(" %c",&ch);
			update();
		}else{
			query();
		}
	}
	return 0;
}

```

---

## 作者：世末OIer (赞：2)

这里是Cf上最慢的一个AC的程序。

2995ms/3000ms

---

这题就是分块。

设一个块就是hpk*m的一个矩阵(hpk你自己定)

to[i][j] 是个pair，表示再这个块的第i行j列这个位置能到达的在这个块里的位置。由于下标是从0开始的，所以{-1,-1}就要存成{-2,-2} （最后要+1）

由于改变一次会使得整个快都改变，所以这个块要很小。多小呢？玄学.多试试就可以了。

```cpp
#pragma GCC optimize("Ofast,inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC diagnostic error "-std=c++11"
#define mp make_pair
#include<bits/stdc++.h>
using namespace std;
const int hpk=102;

struct kuai{  //就是块
	int h;
	string c[hpk+10];
	pair<int,int> to[hpk+10][11];
};
 
string cc[100005];
kuai kk[int(100005/hpk)+10];
int n,m,q,sz;
int use[hpk+10][11];
kuai nwk;
int col;
 
pair<int,int> dfs(int x,int y){      //进行处理每一个位置能到达的位置
	if(x<0 or x==nwk.h or y<0 or y==m) return {x,y};
	if(use[x][y]==col) return {-2,-2};
	use[x][y]=col;
	if(nwk.c[x][y]=='^') nwk.to[x][y]=dfs(x-1,y);
	else if(nwk.c[x][y]=='<') nwk.to[x][y]=dfs(x,y-1);
	else nwk.to[x][y]=dfs(x,y+1);
	return nwk.to[x][y];
}
 
inline kuai go(kuai x){   //改变和预处理
	nwk=x;
	int tl=col;
	for(int i=0;i<x.h;++i) for(int j=0;j<m;++j) if(use[i][j]<=tl) ++col,dfs(i,j);
	return nwk;
}
 
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int i,j;
	cin>>n>>m>>q;
	for(i=0;i<n;++i) cin>>cc[i];
	for(i=0;i<n;++i) kk[i/hpk].c[i%hpk]=cc[i],++kk[i/hpk].h;
	sz=(n+hpk-1)/hpk;
	for(i=0;i<sz;++i) kk[i]=go(kk[i]);
	while(q--){
		char type,cg;
		cin>>type;
		if(type=='A'){
			int x,y;
			cin>>x>>y;
			--x,--y;
			int k=x/hpk;
			pair<int,int> ans=mp(x%hpk,y);
			while(1){   //往前寻找答案
				ans=kk[k].to[ans.first][ans.second];
				if(ans==mp(-2,-2)) break;
				if(ans.second==-1 or ans.second==m or not k) break;
				--k;
				ans.first=hpk-1;
			}
			if(ans==mp(-2,-2)) cout<<"-1 -1\n";
			else cout<<k*hpk+ans.first+1<<' '<<ans.second+1<<endl;
		}else{  //更改
			int x,y;
			cin>>x>>y>>cg;
			--x,--y;
			int t=x/hpk;
			kk[t].c[x%hpk][y]=cg;
			kk[t]=go(kk[t]);
		}
	}
}
```

---

## 作者：lgswdn_SA (赞：1)

补充一种 $O((n+q)m+(Cm+q)\log n)$ 的简单线段树做法。

考虑对于线段树上每个区间 $[l,r]$，处理出数组 $v$，其中 $v_j$ 表示如果从 $(l,j)$ 出发，那么最终会跑到什么地方。

容易发现这是可以简单合并与修改的。合并只需要对于每个 $j$，看右半区间的 $v_j$ 是否能跑到左半区间即可。

做一次修改需要暴力更新该行的 $v$，然后再放到线段树上，单次复杂度 $O(m\log n)$。问询只需要找到 $[1,x]$ 能拆成的线段树区间，然后从右往左做即可，单次复杂度 $O(m+\log n)$。

https://codeforces.com/contest/487/submission/231889491

---

## 作者：Msents (赞：0)

先考虑暴力做，这里有两种暴力：

1. 设 $f_{i,j}$ 表示从 $(x,y)$ 出发最终能到哪，每次修改更新复杂度为 $O(nm)$，查询答案 $O(1)$。

2. 直接暴力跳，查询答案最坏 $O(nm)$，修改 $O(1)$。

注意到 $m$ 很小，结合两个暴力的思想，既不需要一下跳到底，也不需要一整块更新，于是分块。

现设 $f_{i,j}$ 表示离开该位置所属的块后的位置或者是不是陷入死循环，修改时就只需要改一块，查询时跳就行了。

设块长 $B$，于是查询复杂度 $O(\frac n B)$，修改复杂度 $O(mB)$，设 $B$ 为 $\sqrt \frac n m$ 时最优。

很快就做完了，很慢就跑完了，跑了 1.67s，全谷最慢，码：

```
#include<bits/stdc++.h>
using namespace std;
const int MaxN=100000,MaxM=10;
int n,m,q,block;
char mat[MaxN+1][MaxM+1];
int f[2][MaxN+1][MaxM+1];
bool vst[MaxN+1][MaxM+1];
int BlockID(int x){return(x-1)/block+1;}
void UpdateBlock(int id){
	for(int i=(id-1)*block+1;i<=min(n,id*block);i++)
		for(int j=1;j<=m;j++)
			vst[i][j]=false,f[0][i][j]=-1,f[1][i][j]=-1;
	for(int i=(id-1)*block+1;i<=min(n,id*block);i++){
		for(int j=1;j<=m;j++){
			if(vst[i][j])continue;
			vector<pair<int,int> >fe;
			int x=i,y=j;
			while(!(vst[x][y]||x>min(n,id*block)||x<(id-1)*block+1||y<1||y>m)){
				fe.emplace_back(x,y);
				vst[x][y]=true;
				if(mat[x][y]=='^')
					x--;
				else if(mat[x][y]=='<')
					y--;
				else
					y++;
			}
			int ax,ay;
			if(x>min(n,id*block)||x<(id-1)*block+1||y<1||y>m)ax=x,ay=y;
			else ax=f[0][x][y],ay=f[1][x][y];
			for(auto&pi:fe){
				int px=pi.first,py=pi.second;
				f[0][px][py]=ax,f[1][px][py]=ay;
			}
		}
	}
}
void Solve(){
	cin>>n>>m>>q;
	block=max(1,int(sqrt(n/m)));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>mat[i][j];
	for(int i=1;i<=(n+block-1)/block;i++)UpdateBlock(i);
	for(int i=1;i<=q;i++){
		char op,c;
		int x,y;
		cin>>op;
		if(op=='A'){
			cin>>x>>y;
			while(!(x>n||x<1||y<1||y>m)){
				int nx=f[0][x][y],ny=f[1][x][y];
				x=nx,y=ny;
			}
			cout<<x<<' '<<y<<'\n';
		}else{
			cin>>x>>y>>c;
			mat[x][y]=c;
			UpdateBlock(BlockID(x));
		}
	}
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
//	int T;
//	cin>>T;
//	while(T--)
		Solve();
	return 0;
}

```

---

## 作者：zesqwq (赞：0)

# CF487D Conveyor Belts 题解

[题目传送门](https://www.luogu.com.cn/problem/CF487D)

我的思路和他人不太一样，但时间复杂度不变，都可以做到 $O(q\sqrt{nm})$。

##  题解部分

我们优化一个不断跳 $\text{next}$ 的过程时一般会有两种方法。如 $\text{LCA}$ 问题，其一就是倍增，其二就是存下每个点过 $\sqrt n$ 轮之后跳到了哪里（也就是分块的思想）。

然后我们发现倍对于这道题增很难支持修改，但是第二种就可以。于是我们就定一个值 $B$，然后求每个点过 $B$ 轮会跳到哪里。然后对于查询操作，就可以一次跳 $B$ 格，如果过了 $\lceil \frac{nm}{B} \rceil$ 轮后还是没有跳出，就可以判定死循环。对于修改操作，先处理修改点在 $B$ 轮中分别会跳到哪里，然后再反向跑一次 $\text{BFS}$ 来求出哪些点在 $B$ 轮中经过了修改点，就可以更改所有要更改的信息了。然后分析一波时间复杂度：修改单次是 $O(Bm)$ 的，查询单次是 $O(\frac{nm} B)$ 的，虽然查询和修改不同阶，但鉴常数原因， $B$ 还是取约为 $\sqrt{nm}$ 的一个值较好，但是最优应该是 $\sqrt{nm^2}$。

具体来说，代码如下：

$\text{Code:}$

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
const int N = 1e5 + 10, M = 12;
int n, m, q, s;
pair<int, int> que[N * M];
int l, r;
char g[N][M];
pair<int, int> to[N][M];
pair<int, int> dis[N];
int dist[N][M], dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
vector<pair<int, int> > vec;
inline bool check(pair<int, int> p) { return p.first >= 1 && p.first <= n && p.second >= 1 && p.second <= m; }
inline pair<int, int> nxt(pair<int, int> p) {
    if (g[p.first][p.second] == '^') return {p.first - 1, p.second};
    if (g[p.first][p.second] == '>') return {p.first, p.second + 1};
    if (g[p.first][p.second] == '<') return {p.first, p.second - 1};
    return {114514, 1919810};
}
void bfs(pair<int, int> p, int type) {
    vec.push_back(p), dist[p.first][p.second] = 0;
    l = 1, que[r = 1] = p;
    pair<int, int> u, v;
    while (l <= r) {
        u = que[l++];
        to[u.first][u.second] = dis[s - dist[u.first][u.second]];
        if (dist[u.first][u.second] < s)
            for (int i = 0; i < 4; i++) {
                v = {u.first + dx[i], u.second + dy[i]};
                if (!check(v) || dist[v.first][v.second] || nxt(v) != u) continue;
                dist[v.first][v.second] = dist[u.first][u.second] + 1, vec.push_back(v), que[++r] = v;
            }
    }
    if (type)
        for (int i = 0; i < vec.size(); i++) dist[vec[i].first][vec[i].second] = 0;
    vec.clear();
}
inline void update(pair<int, int> p, int type) {
    dis[0] = p;
    for (int i = 1; i <= s; i++) {
        dis[i] = nxt(dis[i - 1]);
        if (!check(dis[i])) dis[i] = dis[i - 1];
    }
    bfs(p, type);
}
inline void query(pair<int, int> p) {
    int step = 0;
    while (step <= n * m && check(nxt(p))) p = to[p.first][p.second], step += s;
    if (!check(nxt(p)))
        p = nxt(p), printf("%d %d\n", p.first, p.second);
    else
        puts("-1 -1");
}
inline void print(pair<int, int> p) { printf("%d %d\n", p.first, p.second); }
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> q, s = sqrt(n * m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> g[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!dist[i][j]) update({i, j}, 0);
    memset(dist, 0, sizeof(dist));
    char op, z;
    int x, y;
    for (int i = 1; i <= q; i++) {
        cin >> op >> x >> y;
        if (op == 'A')
            query({x, y});
        else
            cin >> z, g[x][y] = z, update({x, y}, 1);
    }
    return 0;
}
```

---

## 作者：jzh817 (赞：0)

~~初学分块，想找到水题练练，没想到碰上了个NOI+，坑了我一整天~~

虽说正解是分块，但我用dp仍然水了过去，速度还挺快，389ms

令dp[i][j]表示第i行第j列的菜送到的位置，对于3种箭头直接转移即可（简单到爆），然后在用倍增就能控制插入的复杂度。

具体写法详见代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read(){
	ll a=0,b=getchar(),c=1;
	while(!isdigit(b))c=b=='-'?-1:1,b=getchar();
	while(isdigit(b))a=a*10+b-'0',b=getchar();
	return a*c;
}
pair<int,int> dp[100005][16];
char s[100005][15],t[5];
int n,m,q,Z=256,x,y;
void gao(int r1,int r2);
int main(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=n;i+=Z)
		gao(i,min(n,i+Z-1));
	while(q--){
		scanf("%s%d%d",&t,&x,&y);
		if(t[0]=='A'){
			int r=x,c=y;
			while(r>=1 and c>=1 and c<=m){
				int nr=dp[r][c].first,nc=dp[r][c].second;
				if(nr==r and(nc>=1 and nc<=m)){
					r=nr,c=nc;
					break;
				}
				r=nr,c=nc;
			}
			if(r>=1 and(c>=1 and c<=m))
				r=c=-1;
			printf("%d %d\n",r,c);
		}
		else{
			getchar(),s[x][y]=getchar();
			gao(min((x/Z)*Z+1,n),min(n,(x/Z)*Z+Z));
		}
	}
	return 0;
}
void gao(int r1,int r2){
	for(int i=r1;i<=r2;i++){
		for(int j=1;j<=m;j++)
			dp[i][j]=make_pair(i,j);
		for(int j=1;j<=m;j++)
			if(s[i][j]=='^')
				dp[i][j]=(i==r1)?make_pair(r1-1,j):dp[i-1][j];
		for(int j=1;j<=m;j++)
			if(s[i][j]=='<')
				dp[i][j]=(j==1)?make_pair(i,0):dp[i][j-1];
		for(int j=m;j>=1;j--)
			if(s[i][j]=='>')
				dp[i][j]=(j==m)?make_pair(i,m+1):dp[i][j+1];
	}
}
```


---

