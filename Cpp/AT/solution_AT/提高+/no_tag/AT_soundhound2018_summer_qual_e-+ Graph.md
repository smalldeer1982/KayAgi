# + Graph

## 题目描述

[problemUrl]: https://atcoder.jp/contests/soundhound2018-summer-qual/tasks/soundhound2018_summer_qual_e

kenkooooさんは $ n $ 頂点 $ m $ 辺の単純連結グラフを拾いました。 グラフの頂点には $ 1 $ から $ n $ の番号が付けられていて、 $ i $ 番目の辺は頂点 $ u_i $ と $ v_i $ をつないでいます。 また、$ i $ 番目の辺には整数 $ s_i $ が定められています。

kenkooooさんは次の条件を満たすようにそれぞれの頂点に *正の整数* を書き込もうとしています。

- どの辺 $ i $ についても、頂点 $ u_i $ と $ v_i $ に書かれた正の整数の和は $ s_i $ に等しい

条件を満たすような正の整数の書き方が何通りあるか求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ n\ \leq\ 10^5 $
- $ 1\ \leq\ m\ \leq\ 10^5 $
- $ 1\ \leq\ u_i\ <\ v_i\ \leq\ n $
- $ 2\ \leq\ s_i\ \leq\ 10^9 $
- $ i\neq\ j $ のとき $ u_i\ \neq\ u_j $ または $ v_i\ \neq\ v_j $
- グラフは連結
- 入力はすべて整数

### Sample Explanation 1

頂点 $ 1,2,3 $ にそれぞれ $ 1,2,3 $ を書くと条件を満たします。 これ以外に条件を満たすような整数の書き方は無いため、答えは $ 1 $ です。

### Sample Explanation 2

頂点 $ 1,2,3,4 $ に書く数をそれぞれ $ a,b,c,d $ で表すことにすると、条件を満たす $ (a,b,c,d) $の組は以下の $ 3 $ つです。 - $ (a,b,c,d)=(1,5,2,3) $ - $ (a,b,c,d)=(2,4,3,2) $ - $ (a,b,c,d)=(3,3,4,1) $

## 样例 #1

### 输入

```
3 3
1 2 3
2 3 5
1 3 4```

### 输出

```
1```

## 样例 #2

### 输入

```
4 3
1 2 6
2 3 7
3 4 5```

### 输出

```
3```

## 样例 #3

### 输入

```
8 7
1 2 1000000000
2 3 2
3 4 1000000000
4 5 2
5 6 1000000000
6 7 2
7 8 1000000000```

### 输出

```
0```

# 题解

## 作者：_edge_ (赞：4)

### 题意

给定一张无向简单连通图，要求给点赋值上正整数使得所有的边 $(u_i,v_i,s_i)$ 满足 $a_{u_i}+a_{v_i}=s_i$，求方案数。

### 思路

这题乍一看没啥思路，但是实际来思考的时候，我们先思考一个子问题。

不妨直接设 $m=n-1$，这样这张图就是一棵树，在树的情况下，我们随便选一个点为根，先假设为 $1$。

那么我们确定了 $1$ 节点的值之后就可以确定它的儿子，确定了他的儿子之后就可以确定更下面的节点，这样一次一次确定下去整棵树都会被确定。

好的，现在我们已经有初步想法了，就是确定一个点的值之后确定其他的。

我们不妨直接设 $x$ 为 $a_1$，那么对于和它连边的节点就是 $a_x=s_i-x$，对于与 $x$ 连边的点就是 $a_y=s_j-(a_x) =s_j-s_i+x$，这样会列出一系列关于 $x$ 的等式。

然后我们利用题目条件，就是对于 $a_i$ 必然需要满足 $a_i>0$，那么对于形如 $a_i=y-x$ 的等式就是 $y-x>0$ 那么就是 $x<y$，对于 $a_i=y+x$ 的等式就是 $y+x>0$，就是 $x>-y$。

然后我们确定了这个 $x$ 的上下界，很容易计算答案，两个减一减就可以了。

然后我们再来思考添加另外的边会产生什么贡献，由于对于所有的点我们均用 $-x+y$ 或者 $x+y$ 的式子表示出来了，那么如果是 $-x+y$ 和 $x+y$ 之间有条边，那么需要确定它们两个的和是不是正确的。

然后对于 $x+y$ 和 $x+y$ 有边的话直接解方程确定整棵树的唯一数值。

值得一提的是，确定完成的之后可能还有边未被添加，需要重新判断整棵树是否合法。

时间复杂度 $O(n)$。

其实这类问题并不罕见，我们有时候可以通过一个值来确定另外的值。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e5+5;
struct _node_edge{
	int to_,next_,disv_;
}edge[INF<<1];
int tot,head[INF],m,op[INF],dd[INF],vis[INF],n,xx[INF],yy[INF],zz[INF],ans[INF];
// op[i] 表示 x 正负 1/0，dd[i] 表示 0 次项系数 
void add_edge(int x,int y,int z) {
	edge[++tot]=(_node_edge){y,head[x],z};
	head[x]=tot;return ;
}
void DFS(int x,int fa) {
	vis[x]=1;
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_,d=edge[i].disv_;
		if (v==fa) continue;
		if (vis[v]) continue;
//		cout<<x<<" "<<v<<" "<<dd[x]<<" "<<dd[v]<<" "<<" keklkker\n";
		op[v]=op[x]^1;
		dd[v]=d-dd[x];
		DFS(v,x);
	}
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=m;i++) {
		int x=0,y=0,z=0;
		cin>>x>>y>>z;
		xx[i]=x;yy[i]=y;zz[i]=z;
		add_edge(x,y,z);
		add_edge(y,x,z);
	}
	op[1]=1;dd[1]=0;
	DFS(1,-1);
	
	for (int i=1;i<n;i++) {
		int x=xx[i],y=yy[i],z=zz[i];
		if (op[x]==(op[y]^1)) {
			if (dd[x]+dd[y]!=z) {cout<<"0\n";return 0;}
			continue;
		}
		int ss=dd[x]+dd[y];
		z-=ss;
		if (z%2) {cout<<"0\n";return 0;}
		if (op[x]==0) op[x]=-1;
		int kk=z/op[x]/2;
		ans[1]=kk;
		if (kk<=0) {cout<<"0\n";return 0;}
		for (int j=2;j<=n;j++) {
			if (op[j]==0) op[j]=-1;
			int Y=dd[j]+op[j]*ans[1];
			if (Y<=0) {cout<<"0\n";return 0;}
			ans[j]=Y;
		}
		for (int j=1;j<=m;j++) {
			int x=xx[j],y=yy[j],z=zz[j];
			if (ans[x]+ans[y]!=z) {cout<<"0\n";return 0;}
		}
		cout<<"1\n";
		return 0;
	}
	int L=0,R=1e18; 
	for (int i=1;i<=n;i++) {
		if (op[i]==0) op[i]=-1;
		if (op[i]==1) L=max(L,-dd[i]);
		else R=min(R,dd[i]);
	}
	cout<<max(0ll,R-L-1)<<"\n";
	return 0;
}
```


---

## 作者：shinkuu (赞：0)

给你一张 $n$ 个点 $m$ 条边的无向连通图，每条边 $(u_i,v_i)$ 有边权 $w_i$。现在你要给每个点赋一个点权 $d_j$，要求 $\forall i,d_{u_i}+d_{v_i}=w_i$。求方案数。

图的性质一般是不够好的，考虑拎一棵生成树出来做。

容易发现在树上，任意确定一个节点的值，其他节点的值就是唯一的。现在问题就变成了没加入的边为若干限制，求情况数。

那么现在就要研究没加入的边有什么限制。容易发现，对于一条边 $(u,v,w)$，$A$ 是 $u$ 到 $v$ 路径上的点的点权，则相当于得到了一个 $k$ 元一次方程组：

$$\begin{cases}A_1+A_2=w_1\\A_2+A_3=w_2\\\cdots\\A_{k-1}+A_k=w_{k-1}\\A_k+A_1=w_k\end{cases}$$

然后分讨：

- 当 $n$ 为奇数时，可以解出这个方程组，然后验证是否可行。若可行，答案为 $1$，否则为 $0$。

- 当 $n$ 为偶数时，无法解出，但是给出了 $w_1-w_2+w_3-w_4+\cdots-w_{k-1}+w_k=w$ 的限制。检查一下。

上述操作可以用倍增 lca 维护。

如果此时还没处理出答案，则直接按树的情况做即可。具体地说，可以发现每次让一个奇数深度的点权值 $-1$，则所有奇数深度的点权值 $-1$，偶数深度的点权值 $+1$。反之亦然。

先将 $1$ 号点赋一个值，分别求出当前树上奇数深度和偶数深度点权最小值，再分讨一下即可。具体大家可以自己思考，也可以参考代码。

code：

```cpp
int n,m;
ll mn[2],ans[N];
int dep[N],fa[N][23];
ll g[N][23],h[N][23];
bool vis[N],pd[N];
int tot,head[N];
struct node{
	int to,nxt,cw;
}e[N<<1];
struct Node{
	int x,y,z,flag;
};
inline void add(int u,int v,int w){
	e[++tot]={v,head[u],w};
	head[u]=tot;
}
void dfs(int u,int f,int w){
	fa[u][0]=f;
	g[u][0]=h[u][0]=w;
	fa[u][1]=fa[f][0];
	g[u][1]=g[u][0]-g[f][0],h[u][1]=h[u][0];
	for(int i=2;i<=18;i++){
		fa[u][i]=fa[fa[u][i-1]][i-1];
		g[u][i]=g[u][i-1]+g[fa[u][i-1]][i-1];
		h[u][i]=h[u][i-1]+h[fa[u][i-1]][i-1];
	}
	dep[u]=dep[f]+1;
	vis[u]=true;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v]){
			continue;
		}
		pd[(i+1)/2]=true;
		dfs(v,u,e[i].cw);
	}
}
Node get_lca(int u,int v){
	bool ff=false;
	if(dep[u]<dep[v]){
		swap(u,v);
		ff=true;
	}
	int a=0,b=0,c=0,d=0,flag1=1,flag2=1;
	for(int i=18;i>=0;i--){
		if(dep[fa[u][i]]>=dep[v]){
			a+=g[u][i];
			b+=h[u][i];
			u=fa[u][i];
			if(!i){
				flag1*=-1;
			}
		}
	}
	if(u==v){
		return {u,a,b,ff};
	}
	for(int i=18;i>=0;i--){
		if(fa[u][i]!=fa[v][i]){
			a+=flag1*g[u][i],c+=g[v][i];
			b+=flag1*h[u][i],d+=h[v][i];
			u=fa[u][i],v=fa[v][i];
			if(!i){
				flag1*=-1;
				flag2*=-1;
			}
		}
	}
	a+=flag1*g[u][0],c+=flag2*g[v][0];
	b+=flag1*h[u][0],d+=flag2*h[v][0];
	flag1*=-1,flag2*=-1;
	if(flag1!=flag2){
		a+=c,b+=d;
	}else{
		a-=c,b-=d;
	}
	return {fa[u][0],a,b,ff};
}
void check(int u){
	vis[u]=true;
	if(ans[u]<=0){
		puts("0");
		exit(0);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v]){
			if(ans[u]+ans[v]!=e[i].cw){
				puts("0");
				exit(0);
			}
			continue;
		}
		ans[v]=e[i].cw-ans[u];
		check(v);
	}
}
void get_val(int u,int dep){
	mn[dep%2]=min(mn[dep%2],ans[u]);
	vis[u]=true;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[v]||!pd[(i+1)/2]){
			continue;
		}
		ans[v]=e[i].cw-ans[u];
		get_val(v,dep+1);
	}
}
void solve(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<=m;i++){
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0,0);
	for(int i=1;i<=tot;i+=2){
		if(pd[(i+1)/2]){
			continue;
		}
		int u=e[i+1].to,v=e[i].to;
		Node w=get_lca(u,v);
		if(w.flag){
			swap(u,v);
		}
		if((dep[u]+dep[v]-2*dep[w.x]+1)%2==1){
			if((w.y+e[i].cw)%2==1){
				puts("0");
				return;
			}
			ans[u]=(w.y+e[i].cw)/2;
			mems(vis,false);
			check(u);
			puts("1");
			return;
		}else{
			if(w.y!=e[i].cw){
				puts("0");
				return;
			}
		}
	}
	mems(vis,false);
	mn[0]=mn[1]=inf;
	get_val(1,1);
	if(mn[0]+mn[1]-2<0){
		puts("0");
	}else{
		printf("%lld\n",mn[0]+mn[1]-1);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)solve();
}
```

ps：![](https://cdn.luogu.com.cn/upload/image_hosting/3v59u5fu.png)

这屎山能一遍过我是没想到的。

---

