# EntropyIncreaser 与 动态图

## 题目背景

话说 NaCly_Fish 在和  $\mathsf E \color{red}\mathsf{ntropyIncreaser}$ 吃饭时，问过她一个问题：“一个无向图，支持动态加边，求两点间割点数，怎么做？” 

$\mathsf E \color{red} \mathsf{ntropyIncreaser}$ 想了几秒，说：“这不是sb题吗，随便怎么做都行吧。”然后三两句道出了一个算法。

而 NaCly_Fish 还是不会，请你来教教她这题怎么做吧。

## 题目描述

有一个 $n$ 个点的图，初始没有边。  
有 $q$ 个操作，分为 $3$ 种，具体如下：  

- `1 u v` 表示在 $u,v$ 之间连一条无向边  
- `2 u v` 表示求 $u,v$ 间的割边数量   
- `3 u v` 表示求 $u,v$ 间的割点数量   

特别地，对于 $2$、$3$ 操作，若 $u,v$ 不连通，则输出 $-1$    
****
为了防止有歧义，这里给出对两点间割边和割点数量的定义：  
对于所有包含 $u,v$ 的路径的节点集合之交 $S$ ，定义 $S$ 中的元素数量为 $u,v$ 间的割点数。  
对于所有包含 $u,v$ 的路径的边集合之交 $T$ ，定义 $T$ 中的元素数量为 $u,v$ 间的割边数。  
****
**本题强制在线。**  
从第二行开始，每次的输入的 $u,v$ 都需要异或上 $\text{last}$ ，才是实际操作的 $u,v$。  
 $\text{last}$ 为最近一次**答案非 $-1$ 的**询问的答案，定义初始 $\text{last}=0$   
ps：如果您不知道异或是什么意思，可以看这里：[xor](https://www.baidu.com/link?url=bhG_De1gZYsqrIq7dkhgGj8vP87xSSyoIwk0-5p1fyKmf58cznvq0oYJg0XGoyKNpuGk7EsvjUnyvgJ19_ZA3PhoMJ3hIufHZ5GXh1OaIoS&wd=&eqid=ab26bc160004324d000000035d1ed64e)

## 说明/提示

~~题目背景为真实事件~~

### 样例说明：  
实际操作为：  
```cpp
5 10
1 1 2
1 2 3
2 1 3
3 2 3
1 1 3
1 3 4
2 1 5
1 4 5
1 5 3
3 1 4
```

【数据范围】
  
对于 $20\%$ 的数据，$1\le n,q \le 2000$ ；   
对于另外 $30\%$ 的数据，所有 $2$、$3$ 操作均在 $1$ 操作之后；    
对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le q \le 3\times 10^5$。
    
对于 $1$ 操作，保证 $u\neq  v$。  

By：NaCly_Fish

****

欢迎加入 EI队长粉丝裙，群号：$747262201$   

## 样例 #1

### 输入

```
5 10
1 1 2
1 2 3
2 1 3
3 0 1
1 3 1
1 1 6
2 3 7
1 6 7
1 7 1
3 3 6```

### 输出

```
2
2
-1
3```

# 题解

## 作者：yurzhang (赞：13)

更好的阅读体验 -> [推销博客](https://nikaidou-shinku.github.io/【题解】-Luogu5489-EntropyIncreaser与动态图/)

---

# 前言

这个题其实没有多难，静下来慢慢写还是十分可做的，不失为一道 $\text{LCT}$ 练手好题。

---

# 正文

首先看到 $1$ 操作连边，第一反应应该就是 $\text{Link/Cut Tree}$ 了，然而怎么维护割边割点数量呢？我们分开讨论。

## 割边

考虑对于一个环，环上所有边一定不会是割边；而对于一条链，链上所有边一定是割边。

我们可以直接维护每条边是不是割边，初始时所有边都是割边，当某次加边操作产生了环，则环上所有边都不会成为割边了。

具体来讲，边转点后所有边权值均为 $1$ ，当某次 $\text{Link}$ 的两结点已经连通，则将两结点间的链上的边全部赋值为 $0$ ，同时维护和即可。

## 割点

割点不像割边那样好处理了。

考虑静态的情况，静态割点有一个比较套路的方法是用**圆方树**，我们可以尝试动态地维护一棵圆方树：每次连边产生环就将环上所有点连到一个方点上来。

考虑这样做的复杂度：

假设环的长度是 $L$ ，每次会用 $O(L\log n)$ 的复杂度删去一个长为 $O(L)$ 的环，均摊复杂度为 $O(n\log n)$ 。

---

# 最后

于是使用两棵 $\text{LCT}$ 分别维护割边和割点即可。

参考代码：

```cpp
#include <cstdio>

#define N 200010
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]

inline void swap(int&a,int&b) {
	int tmp(a); a=b,b=tmp;
}

namespace Summer {
	int ch[N][2],fa[N],rev[N],val[N],sumv[N],mark[N];
	inline void reverse(int x) {
		if(x) {
			swap(lc(x),rc(x));
			rev[x]^=1;
		}
	}
	inline void NaCly_Fish_Orz(int x) {
		if(x) {
			val[x]=sumv[x]=0;
			mark[x]=1;
		}
	}
	inline void up(int x) {
		sumv[x]=sumv[lc(x)]+sumv[rc(x)]+val[x];
	}
	inline void down(int x) {
		if(rev[x]) {
			reverse(lc(x));
			reverse(rc(x));
			rev[x]=0;
		}
		if(mark[x]) {
			NaCly_Fish_Orz(lc(x));
			NaCly_Fish_Orz(rc(x));
			mark[x]=0;
		}
	}
	inline int nrt(int x) {
		return x==lc(fa[x])||x==rc(fa[x]);
	}
	void psa(int x) {
		if(nrt(x)) psa(fa[x]);
		down(x);
	}
	inline void rotate(int x) {
		int y(fa[x]),z(fa[y]),k(x==rc(y));
		ch[y][k]=ch[x][k^1],ch[x][k^1]=y;
		if(nrt(y)) ch[z][y==rc(z)]=x;
		if(ch[y][k]) fa[ch[y][k]]=y;
		fa[y]=x,fa[x]=z,up(y);
	}
	inline void splay(int x) {
		int y,z;
		for(psa(x);nrt(x);rotate(x)) {
			y=fa[x],z=fa[y];
			if(nrt(y)) rotate(x==rc(y)^y==rc(z)?x:y);
		} up(x);
	}
	inline void access(int x) {
		for(int y=0;x;x=fa[y=x]) {
			splay(x); rc(x)=y; up(x);
		}
	}
	inline void mrt(int x) {
		access(x); splay(x); reverse(x);
	}
	inline void link(int x,int y) {
		mrt(x); fa[x]=y;
	}
	inline void cut(int x,int y) {
		mrt(x); access(y); splay(y);
		fa[x]=lc(y)=0; up(y);
	}
}

namespace Pockets {
	int ch[N][2],fa[N],rev[N],val[N],sumv[N],st[N],num;
	inline void reverse(int x) {
		if(x) {
			swap(lc(x),rc(x));
			rev[x]^=1;
		}
	}
	inline void up(int x) {
		sumv[x]=sumv[lc(x)]+sumv[rc(x)]+val[x];
	}
	inline void down(int x) {
		if(rev[x]) {
			reverse(lc(x));
			reverse(rc(x));
			rev[x]=0;
		}
	}
	inline int nrt(int x) {
		return x==lc(fa[x])||x==rc(fa[x]);
	}
	void psa(int x) {
		if(nrt(x)) psa(fa[x]);
		down(x);
	}
	inline void rotate(int x) {
		int y(fa[x]),z(fa[y]),k(x==rc(y));
		ch[y][k]=ch[x][k^1],ch[x][k^1]=y;
		if(nrt(y)) ch[z][y==rc(z)]=x;
		if(ch[y][k]) fa[ch[y][k]]=y;
		fa[y]=x,fa[x]=z,up(y);
	}
	inline void splay(int x) {
		int y,z;
		for(psa(x);nrt(x);rotate(x)) {
			y=fa[x],z=fa[y];
			if(nrt(y)) rotate(x==rc(y)^y==rc(z)?x:y);
		} up(x);
	}
	inline void access(int x) {
		for(int y=0;x;x=fa[y=x]) {
			splay(x); rc(x)=y; up(x);
		}
	}
	inline void mrt(int x) {
		access(x); splay(x); reverse(x);
	}
	inline void link(int x,int y) {
		mrt(x); fa[x]=y;
	}
	inline void cut(int x,int y) {
		mrt(x); access(y); splay(y);
		fa[x]=lc(y)=0; up(y);
	}
	void print(int now) {
		if(now) {
			down(now);
			print(lc(now));
			st[++num]=now;
			print(rc(now));
		}
	}
}

int n,q,opt,u,v,last,tot,ans,SummerPockets;

int fa[N];
inline int find(int x) {
	return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline void getEdge(int u,int v) {
	int x=find(u),y=find(v);
	if(x!=y) {
		ans=-1;
		return;
	}
	Summer::mrt(u);
	Summer::access(v);
	Summer::splay(v);
	ans=Summer::sumv[v];
}

inline void getPoint(int u,int v) {
	int x=find(u),y=find(v);
	if(x!=y) {
		ans=-1;
		return;
	}
	Pockets::mrt(u);
	Pockets::access(v);
	Pockets::splay(v);
	ans=Pockets::sumv[v];
}

inline void link(int u,int v) {
	int x=find(u),y=find(v);
	if(x==y) {
		Summer::mrt(u);
		Summer::access(v);
		Summer::splay(v);
		Summer::NaCly_Fish_Orz(v);
		
		getPoint(u,v);
		if(ans>2) {
			++SummerPockets;
			Pockets::mrt(u);
			Pockets::access(v);
			Pockets::splay(v);
			Pockets::num=0;
			Pockets::print(v);
			for(int i=1;i<Pockets::num;++i)
				Pockets::cut(Pockets::st[i],Pockets::st[i+1]);
			for(int i=1;i<=Pockets::num;++i)
				Pockets::link(Pockets::st[i],SummerPockets);
		}
	} else {
		++tot; fa[y]=x;
		Summer::val[tot]=1;
		Summer::link(u,tot);
		Summer::link(tot,v);
		
		Pockets::link(u,v);
	}
}

int main() {
	scanf("%d%d",&n,&q);
	tot=SummerPockets=n;
	for(int i=1;i<=n;++i)
		fa[i]=i,Pockets::val[i]=1;
	while(q--) {
		scanf("%d%d%d",&opt,&u,&v);
		u^=last,v^=last;
		switch(opt) {
			case 1: {
				link(u,v);
				break;
			}
			case 2: {
				getEdge(u,v);
				if(ans!=-1) last=ans;
				printf("%d\n",ans);
				break;
			}
			default: {
				getPoint(u,v);
				if(ans!=-1) last=ans;
				printf("%d\n",ans);
				break;
			}
		}
	}
	return 0;
}
```



---

## 作者：KiDDOwithTopTree (赞：6)

题目在这：[传送门](https://www.luogu.com.cn/problem/P5489)。

这是一道很不错的 LCT 题目。

一看到动态加边就知道是 LCT 了。

此题可以分为两部分：

1. 动态求桥。
2. 动态求割点。

动态求桥的话有一道[模板题](https://www.luogu.com.cn/problem/P2542)，而动态求割点也有一道[模板题](https://www.luogu.com.cn/problem/P5622)。你可以选择先 A 那两题，也可以 A 了这题后再 A 其他那两题。

#### 如何动态求桥

因为在一个点双的边一定不是桥，所以连边时如果原先联通的话就进行暴力 dfs 缩成一个点。看似很暴力，但实际上却是均摊 $O(1)$ 的（每一个点最多被缩一次）。

查询路径上的桥时，我们就直接输出 LCT 中这条路径的点数 -1 即可。因为 LCT 上的一个点代表一个点双，所以 LCT 中路径的点数 -1 即为连接这些点双的边数，即为桥的数量。

暴力 dfs 的代码:
```cpp
void dfs(int pos,int fa){//暴力dfs
	if(!pos)//如果pos为空就退出
		return ;
	f[pos]=fa;//f为并查集，f[pos]表示pos所在的双联通分量的编号
	dfs(spl[pos].son[0],fa);
	dfs(spl[pos].son[1],fa);
	spl[pos].son[0]=spl[pos].son[1]=0;//断儿子
	pushup(pos);//更新（毕竟儿子都没了嘛）
}
```

因为我们只更新了 $f$ 数组，所以在 access 操作时跳 $fa$ 时需要更新。

access 代码：
```cpp
void access(int pos){
	int son=0;
	while(pos){
		splaying(pos);
		spl[pos].son[1]=son;
		pushup(pos);
		son=pos;
		pos=spl[pos].fa=find(spl[pos].fa);//记得更新
	}
}
```

#### 如何动态求割点

弄割点有一个很好的东西：**圆方树**。

不太懂思想的可以去[洛谷日报](https://www.luogu.com.cn/blog/PinkRabbit/Introduction-to-Round-Square-Tree)看看。

因为连接点双的分隔点是割点，所以在这个圆方树中，$x$ 到 $y$ 的路径上的圆点个数即为 $x$ 到 $y$ 路径上的割点个数。

那么连边时如果原先联通的话就进行暴力 dfs，把这一个点双上的点都与一个方点进行连边。这个 dfs 的过程也是均摊 $O(1)$ 的。

暴力 dfs 的代码：
```cpp
void dfs(int pos,int fa){//暴力dfs
	spl[pos].fa=fa;//断掉原来的边，连向一个方点
	if(spl[pos].son[0])
		dfs(spl[pos].son[0],fa);
	if(spl[pos].son[1])
		dfs(spl[pos].son[1],fa);
	spl[pos].son[0]=spl[pos].son[1]=0;//断儿子
	pushup(pos);//更新（毕竟儿子都没了嘛）
}
```

pushup 函数可以写成这样：
```cpp
inline void pushup(int pos){
	int lson=spl[pos].son[0],rson=spl[pos].son[1];
	spl[pos].sum=spl[lson].sum+spl[rson].sum+(pos<=n);//如果pos的编号小于等于n，即为圆点，那么sum数就要+1
}
```

#### 如何AC此题

思想已经全部讲完，就剩下综合起来了。

我们可以发现：因为求桥的 dfs 会把点双缩成一个点，而求割点的 dfs 则要保留点双的其他点，所以我们不能使用同一个 LCT 来维护这两个东西，而是要开两个不同的 LCT 进行分别维护。~~因为我的强迫症~~，我开了一个结构体进行封装起来。

因为这两个 LCT 还是有一部分不一样的。那就是 access 操作了。求桥的 access 中有并查集找 $fa$ 的步骤，而求割点的没有。分成两个操作吗？太繁琐了。我们可以把两个 access 合为一体吗？可以。怎么办呢？因为 $f$ 数组最开始都是自己，而求割点的代码又没有进行更改它，所以我们可以直接用求桥的那个 access 函数。

其他的可以看看代码：
```cpp
#include<iostream>
using namespace std;
const int N=1e6+10;//因为是圆方树，所以要注意空间开2倍。我就直接开到1e6了
int n,m;
struct link_cut_tree{
	struct splay{
		int fa,son[2];
		int size;//点双个数
		int sum;//圆点个数
		int rev;
	};
	splay spl[N];
	int f[N];
	link_cut_tree(){//初始化
		for(int i=0;i<N;i++)
			f[i]=i;
	}
	inline int find(int x){
		return f[x]==x?x:f[x]=find(f[x]);
	}
	inline bool check_root(int pos){
		return spl[spl[pos].fa].son[0]!=pos&&spl[spl[pos].fa].son[1]!=pos;
	}
	inline int relation(int pos,int fa){
		return spl[fa].son[1]==pos;
	}
	inline void connect(int pos,int fa,int son){
		spl[pos].fa=fa;
		spl[fa].son[son]=pos;
	}
	inline void pushup(int pos){
		int lson=spl[pos].son[0],rson=spl[pos].son[1];
		spl[pos].size=spl[lson].size+spl[rson].size+1;
		spl[pos].sum=spl[lson].sum+spl[rson].sum+(pos<=n);
	}
	inline void pushdown(int pos){
		if(!spl[pos].rev)
			return ;
		swap(spl[pos].son[0],spl[pos].son[1]);
		spl[spl[pos].son[0]].rev^=1;
		spl[spl[pos].son[1]].rev^=1;
		spl[pos].rev=0;
	}
	inline void pushall(int pos){
		if(!check_root(pos))
			pushall(spl[pos].fa);
		pushdown(pos);
	}
	void rotate(int pos){
		int fa=spl[pos].fa,gf=spl[fa].fa;
		int t1=relation(pos,fa),t2=relation(fa,gf);
		connect(spl[pos].son[t1^1],fa,t1);
		connect(fa,pos,t1^1);
		spl[pos].fa=gf;
		if(spl[gf].son[t2]==fa)
			spl[gf].son[t2]=pos;
		pushup(fa);
		pushup(pos);
	}
	void splaying(int pos){
		pushall(pos);
		while(!check_root(pos)){
			int fa=spl[pos].fa,gf=spl[fa].fa;
			if(!check_root(fa))
				relation(pos,fa)^relation(fa,gf)?rotate(pos):rotate(fa);
			rotate(pos);
		}
	}
	void access(int pos){
		int son=0;
		while(pos){
			splaying(pos);
			spl[pos].son[1]=son;
			pushup(pos);
			son=pos;
			pos=spl[pos].fa=find(spl[pos].fa);//记得要find
		}
	}
	void make_root(int pos){
		access(pos);
		splaying(pos);
		spl[pos].rev^=1;
	}
	int find_root(int pos){
		access(pos);
		splaying(pos);
		pushdown(pos);
		while(spl[pos].son[0]){
			pos=spl[pos].son[0];
			pushdown(pos);
		}
		splaying(pos);
		return pos;
	}
	void link(int x,int y){
		make_root(x);
		spl[x].fa=y;
	}
	void split(int x,int y){
		make_root(x);
		access(y);
		splaying(y);
	}
	bool check(int x,int y){
		return find_root(x)==find_root(y);//注意要用find_root
	}
};
link_cut_tree lct[2];
//lct[0]为求桥的lct，lct[1]为求割点的lct。注意要分清
void dfs1(int pos,int fa){
	if(!pos)//要一进来就判断pos是否为0。如果不想的可以在main函数里特判一下
		return ;
	lct[0].f[pos]=fa;
	dfs1(lct[0].spl[pos].son[0],fa);
	dfs1(lct[0].spl[pos].son[1],fa);
	lct[0].spl[pos].son[0]=lct[0].spl[pos].son[1]=0;
	lct[0].pushup(pos);
}
void dfs2(int pos,int fa){
	lct[1].spl[pos].fa=fa;
	if(lct[1].spl[pos].son[0])
		dfs2(lct[1].spl[pos].son[0],fa);
	if(lct[1].spl[pos].son[1])
		dfs2(lct[1].spl[pos].son[1],fa);
	lct[1].spl[pos].son[0]=lct[1].spl[pos].son[1]=0;
	lct[1].pushup(pos);
}
int main(){
	cin>>n>>m;
	int t=0;
	int fx,fy;
	int opt,x,y;
	int lastans=0;
	for(int i=1;i<=m;i++){
		cin>>opt>>x>>y;
		x^=lastans;
		y^=lastans;
		fx=lct[0].find(x);
		fy=lct[0].find(y);
		//找到x和y缩点后成为的点。否则会出错
		switch(opt){
			case 1:
				if(lct[0].check(fx,fy)){//联通
					lct[0].split(fx,fy);
					lct[1].split(x,y);
					//在各自的lct中分裂出路径
					t++;
					dfs1(lct[0].spl[fy].son[0],fy);//把点双缩成fy一个点
					dfs2(y,n+t);//连向一个方点
				}
				else{//直接连边。注意两个lct都要进行连边
					lct[0].link(fx,fy);
					lct[1].link(x,y);
				}
				break;
			case 2:
				if(lct[0].check(fx,fy)){
					lct[0].split(fx,fy);
					lastans=lct[0].spl[fy].size-1;
					cout<<lastans<<'\n';
				}
				else
					cout<<"-1\n";
				break;
			case 3:
				if(lct[1].check(x,y)){
					lct[1].split(x,y);
					lastans=lct[1].spl[y].sum;
					cout<<lastans<<'\n';
				}
				else
					cout<<"-1\n";
				break;
		}
	}
}
```

---

## 作者：hsfzLZH1 (赞：5)

upd 20221122：原来的代码有一处小锅（在 LCT 中访问了被缩掉的点），现在修好了

##

%%% NaCly_Fish

考虑用 LCT 维护操作 $1,2$，可以将每个 **边-双连通分量** 缩成一个点。

加边时，如果一条边连接的 $u,v$ 两点不连通，在动态树上连接 $u,v$ 即可；如果已经连通，则 $u,v$ 之间的路径上的所有点都应该在一个边-双连通分量当中，需要缩成一个点。我们先 `Split(u,v)`，在辅助树上，问题转化为将一个子树缩成一个点。

每个点归属的缩点之后的点可以用并查集维护、缩点时暴力遍历子树，将其与缩点后的结点合并。由于暴力遍历的子树中最后只会剩下一个结点，所以总的时间复杂度是 $O(n\log n)$ 的。

查询两点间的割边数量，由于此时所有边-双连通分量都被缩成了一个点，还在辅助树上的边一定是割边。此时的答案即为缩点后 LCT 上两点间路径上的边数（$=$ 点数 $-1$）。

考虑加入 $3$ 操作。此时要求的是将每个 **点-双连通分量** 缩成一个点。但是一个点可能归属于多个 **极大** 点-双连通分量中，不能直接缩点维护。

利用 **圆方树** 的思想。假设原来的 $n$ 个点都是 **圆点** ，用一个 **方点** 代表一个点-双连通分量，则当连边时 $u,v$ 已经连通，则 $u,v$ 路径上的点归属于一个点-双连通分量，可以暴力遍历辅助树上的子树（可能包含圆点和方点），断开原有的连接，并将子树上的所有点连接到新的一个方点。

查询两点间的割点数量，只要求路径上的圆点的数量即可。因为在一个点-双连通分量内部，不存在割点，可能的割点只会是在路径上的两个，所以这样求得的答案是正确的。

至于时间复杂度，可以感性理解（在同一个点双内部的点的距离都 $\le 2$），或者用势能分析法证明是 $O(n\log n)$ 的。空间复杂度 $O(n)$。

#### 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=100010;
int n,q,op,u,v,lstans,f[maxn];
struct LCT3
{
    int cur,ch[maxn*4][2],fa[maxn*4],tag[maxn*4],siz[maxn*4],val[maxn*4],sum[maxn*4];
    int getch(int x){return ch[fa[x]][1]==x;}
    int isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
    void maintain(int x)
    {
        siz[x]=siz[ch[x][0]]+1+siz[ch[x][1]];
        sum[x]=sum[ch[x][0]]+val[x]+sum[ch[x][1]];
    }
    void rotate(int x)
    {
        int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
        fa[x]=z;if(!isroot(y))ch[z][chy]=x;
        ch[y][chx]=ch[x][chx^1];fa[ch[x][chx^1]]=y;
        ch[x][chx^1]=y;fa[y]=x;
        maintain(y);maintain(x);
    }
    void pushdown(int x)
    {
        if(!tag[x])return;
        if(ch[x][0])tag[ch[x][0]]^=1,swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
        if(ch[x][1])tag[ch[x][1]]^=1,swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
        tag[x]=0;
    }
    void update(int x)
    {
        if(!isroot(x))update(fa[x]);
        pushdown(x);
    }
    void splay(int x)
    {
        update(x);
        for(int f=fa[x];f=fa[x],!isroot(x);rotate(x))
        if(!isroot(f))rotate(getch(x)==getch(f)?f:x);
    }
    void access(int x)
    {
        for(int f=0;x;f=x,x=fa[x])splay(x),ch[x][1]=f,maintain(x);
    }
    void makeroot(int x)
    {
        access(x);splay(x);
        tag[x]^=1;swap(ch[x][0],ch[x][1]);
    }
    int find(int x)
    {
        access(x);splay(x);
        while(ch[x][0])x=ch[x][0];
        splay(x);
        return x;
    }
    void build(int x,int f)
    {
        if(!x)return;
        fa[x]=f;
        build(ch[x][0],f);build(ch[x][1],f);
        ch[x][0]=ch[x][1]=0;
        maintain(x);
    }
    void link(int x,int y)
    {
        makeroot(x);access(y);splay(y);
        fa[x]=y;
    }
}st3;
int findp(int x){return f[x]?f[x]=findp(f[x]):x;}
void merge(int x,int y){x=findp(x);y=findp(y);if(x!=y)f[x]=y;}
struct LCT
{
    int cur,ch[maxn][2],fa[maxn],tag[maxn],siz[maxn],val[maxn],sum[maxn];
    int getch(int x){return ch[fa[x]][1]==x;}
    int isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
    void maintain(int x)
    {
        siz[x]=siz[ch[x][0]]+1+siz[ch[x][1]];
        sum[x]=sum[ch[x][0]]+val[x]+sum[ch[x][1]];
    }
    void rotate(int x)
    {
        int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
        fa[x]=z;if(!isroot(y))ch[z][chy]=x;
        ch[y][chx]=ch[x][chx^1];fa[ch[x][chx^1]]=y;
        ch[x][chx^1]=y;fa[y]=x;
        maintain(y);maintain(x);
    }
    void pushdown(int x)
    {
        if(!tag[x])return;
        if(ch[x][0])tag[ch[x][0]]^=1,swap(ch[ch[x][0]][0],ch[ch[x][0]][1]);
        if(ch[x][1])tag[ch[x][1]]^=1,swap(ch[ch[x][1]][0],ch[ch[x][1]][1]);
        tag[x]=0;
    }
    void update(int x)
    {
        if(!isroot(x))update(fa[x]);
        pushdown(x);
    }
    void splay(int x)
    {
        update(x);
        for(int f=fa[x];f=fa[x],!isroot(x);rotate(x))
        if(!isroot(f))rotate(getch(x)==getch(f)?f:x);
    }
    void access(int x)
    {
        for(int f=0;x;f=x,x=fa[x])splay(x),ch[x][1]=f,fa[x]=findp(fa[x]),maintain(x);
    }
    void makeroot(int x)
    {
        access(x);splay(x);
        tag[x]^=1;swap(ch[x][0],ch[x][1]);
    }
    int find(int x)
    {
        access(x);splay(x);
        while(ch[x][0])x=ch[x][0];
        splay(x);
        return x;
    }
    void build(int x)
    {
        if(!x)return;
        if(ch[x][0])build(ch[x][0]),merge(ch[x][0],x);
        if(ch[x][1])build(ch[x][1]),merge(ch[x][1],x);
    }
    void link(int x,int y)
    {
        makeroot(x);access(y);splay(y);
        fa[x]=y;
    }
}st2;
int main()
{
    scanf("%d%d",&n,&q);st3.cur=n;
    for(int i=1;i<=n;i++)st3.val[i]=1,st3.maintain(i),st2.maintain(i);
    while(q--)
    {
        scanf("%d%d%d",&op,&u,&v);
        u^=lstans;v^=lstans;
        if(op==1)
        {
        	int uu=findp(u),vv=findp(v);
            if(st2.find(uu)!=st2.find(vv))st2.link(uu,vv),st3.link(u,v);
            else
            {
                st3.makeroot(u);st3.access(v);st3.splay(v);
                if(st3.sum[v]>2)st3.cur++,st3.build(v,st3.cur);
                u=findp(u);v=findp(v);
                st2.makeroot(u);st2.access(v);st2.splay(v);
                st2.build(v);st2.maintain(v);
            }
        }
        if(op==2)
        {
            u=findp(u);v=findp(v);
            if(st2.find(u)!=st2.find(v)){printf("-1\n");continue;}
            st2.makeroot(u);st2.access(v);st2.splay(v);
            printf("%d\n",lstans=st2.siz[v]-1);
        }
        if(op==3)
        {
            if(st3.find(u)!=st3.find(v)){printf("-1\n");continue;}
            st3.makeroot(u);st3.access(v);st3.splay(v);
            printf("%d\n",lstans=st3.sum[v]);
        }
    }
    return 0;
}
```

---

## 作者：Hoks (赞：4)

## 前言
LCT 题单里的，刚好我的[总结文章](https://www.luogu.com.cn/blog/Hok/cute-tree-decomposition)里把这题当做了练习题，就写篇题解吧。

这道题是真的折磨玩意，个人调题情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/pz0ftqga.png)

4:22后面我没调了，最后是21:30继续开始调的。
## 题意分析
题目的意思就是要实现动态割边/动态割点。

这两玩意都是有板子题的，分别是[P2542 [AHOI2005] 航线规划](https://www.luogu.com.cn/problem/P2542)和[P5622 [DBOI2019] 巫女的职责](https://www.luogu.com.cn/problem/P5622)。

前者为割边，后者为割点。

但是为了题解的完整性，还是讲下如何实现动态割边割点吧。

对于割边而言：

考虑先缩个点，把每个点双缩成一个点。

那么查询的时候就是链长度 $-1$（为什么是这样请读者自行推敲一二）。

然后是对于割点：

首先我们考虑下之前静态求割点是怎么做的。

考虑建一颗圆方树，然后在圆方树上维护即可。

那怎么动态呢？

其实很简单，我们只需要在连边前，判断这两个点是否连通，如果已经连通了，那连上这条边就会产生一个环，也就是点双，给路径上的边全部断开然后直接建圆方树即可。

这个复杂度是正确的。

下面给个略证：

> 因为只有加边操作，所以任意一个点最多只会被合并一次（因为合并完后就成一个点了）
> 
> 那这样的话复杂度就是 $O(n)$，再加上 LCT 本身单点修改复杂度为 $\log n$，所以均摊后还是 $\log n$。
> 
> 证毕。

然后就变成圆方树上查询树链信息了。

至此，这题的解决方法已经有了，接着就是实现了。

因为割边和割点都会改变树的形态，所以我们要造两颗 LCT，这也就是最折磨的地方了。

给点个人写挂的感受与建议：能不公用的东西就别公用，一公用函数整个炸光！

代码很丑，整合了下前面说的两道模板题。
## 代码
```cpp
#include <bits/stdc++.h>
#define ls son[x][0]
#define rs son[x][1]
#define int long long
using namespace std;
const int N=200010;
int n,q,lst,ans;
int h[N];
inline int find(int x){return x==h[x]?x:h[x]=find(h[x]);}
namespace LCT1
{
	int tot,f[N],s[N],son[N][2],st[N],w[N];bool r[N],tg[N];
	inline bool ntrt(int x){return son[f[x]][1]==x||son[f[x]][0]==x;}
	inline void pushup(int x){s[x]=s[ls]+s[rs]+w[x];}
	inline void pushtag(int u){s[u]=w[u]=0;tg[u]=1;}
	inline void pushson(int x){swap(ls,rs),r[x]^=1;}
	inline void pushdown(int x)
	{
		if(tg[x])
		{
	        if(ls) pushtag(ls);
	        if(rs) pushtag(rs);
	        tg[x]=0;
	    }
		if(r[x])
		{
			if(ls) pushson(ls);
			if(rs) pushson(rs);
			r[x]=0;
		}
	}
	inline void rotate(int x)
	{
		int y=f[x],z=f[y],k=(son[y][1]==x),w=son[x][!k];
		if(ntrt(y)) son[z][son[z][1]==y]=x;son[x][!k]=y;son[y][k]=w;
		if(w) f[w]=y;f[y]=x;f[x]=z;
		pushup(y);
	}
	inline void Splay(int x)
	{
		int y=x,tot=0,z;st[++tot]=y;
		while(ntrt(y)) st[++tot]=y=f[y];
		while(tot) pushdown(st[tot--]);
		while(ntrt(x))
		{
			y=f[x];z=f[y];
			if(ntrt(y)) rotate((son[y][0]==x)^(son[z][0]==y)?x:y);
			rotate(x);
		}
		pushup(x);
	}
	inline void access(int x){for(int y=0;x;x=f[y=x]) Splay(x),rs=y,pushup(x);}
	inline void makert(int x){access(x);Splay(x);pushson(x);}
	inline int findrt(int x)
	{
		access(x);Splay(x);
		while(ls) pushdown(x),x=ls;
		Splay(x);return x;
	}
	inline int split(int x,int y){makert(x);access(y);Splay(y);return s[y];}
	inline void cut(int x,int y){makert(x);access(y);Splay(y);f[x]=son[y][0]=0,pushup(y);}
	inline void link(int x,int y){makert(x);f[x]=y;}
	inline void lk(int u,int v)
	{
		int x=find(u),y=find(v);
		if(x==y) makert(u),access(v),Splay(v),pushtag(v);
		else tot++,w[tot]=1,link(u,tot),link(tot,v);
	}
	inline int qr(int x,int y){return find(x)==find(y)?split(x,y):-1ll;}
}
namespace LCT2
{
	int tot,top;
	int f[N],s[N],son[N][2],st[N],stk[N],w[N];bool r[N];
	inline bool ntrt(int x){return son[f[x]][1]==x||son[f[x]][0]==x;}
	inline void pushup(int x){s[x]=s[ls]+s[rs]+w[x];}
	inline void pushson(int x){swap(ls,rs),r[x]^=1;}
	inline void pushdown(int x)
	{
		if(r[x])
		{
			if(ls) pushson(ls);
			if(rs) pushson(rs);
			r[x]=0;
		}
	}
	inline void rotate(int x)
	{
		int y=f[x],z=f[y],k=(son[y][1]==x),w=son[x][!k];
		if(ntrt(y)) son[z][son[z][1]==y]=x;son[x][!k]=y;son[y][k]=w;
		if(w) f[w]=y;f[y]=x;f[x]=z;
		pushup(y);
	}
	inline void Splay(int x)
	{
		int y=x,tot=0,z;st[++tot]=y;
		while(ntrt(y)) st[++tot]=y=f[y];
		while(tot) pushdown(st[tot--]);
		while(ntrt(x))
		{
			y=f[x];z=f[y];
			if(ntrt(y)) rotate((son[y][0]==x)^(son[z][0]==y)?x:y);
			rotate(x);
		}
		pushup(x);
	}
	inline void access(int x){for(int y=0;x;x=f[y=x]) Splay(x),rs=y,pushup(x);}
	inline void makert(int x){access(x);Splay(x);pushson(x);}
	inline int findrt(int x)
	{
		access(x);Splay(x);
		while(ls) pushdown(x),x=ls;
		Splay(x);return x;
	}
	inline int split(int x,int y){makert(x);access(y);Splay(y);return s[y];}
	inline void link(int x,int y){makert(x);f[x]=y;}
	inline void cut(int x,int y){makert(x);access(y);Splay(y);f[x]=son[y][0]=0,pushup(y);}
	void dfs(int x){if(x) pushdown(x),dfs(ls),stk[++top]=x,dfs(rs);}
	inline void lk(int x,int y)
	{
		if(find(x)==find(y))
		{
            split(x,y);if(s[y]<=2) return;
            top=0;dfs(y);tot++;
            for(int i=1;i<top;i++) cut(stk[i],stk[i+1]);
			for(int i=1;i<=top;i++) link(stk[i],tot);
        }
		else link(x,y),h[find(y)]=find(x);
	}
	inline int qr(int x,int y){return find(x)==find(y)?split(x,y):-1ll;}
}
static char buf[1000000],*paa=buf,*pd=buf;
//#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void){
    int x(0),t(1);char fc(getchar());
    while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
    while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
    return x*t;
}
inline void print(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) print(x/10);
	putchar(x%10+'0');
}
inline int zh(int x){return x^lst;}
signed main()
{
	LCT1::tot=LCT2::tot=n=read(),q=read();
	for(int i=1;i<=n;i++) h[i]=i,LCT2::w[i]=1;
	for(int i=1,op,x,y;i<=q;i++)
	{
		op=read(),x=zh(read()),y=zh(read());
		if(op==1) LCT1::lk(x,y),LCT2::lk(x,y);
		if(op==2)
		{
			ans=LCT1::qr(x,y);print(ans),puts("");
			if(ans!=-1) lst=ans;
		}
		if(op==3)
		{
			ans=LCT2::qr(x,y);print(ans),puts("");
			if(ans!=-1) lst=ans;
		}
	}
	return 0;
}
```


---

## 作者：OIer_ACMer (赞：2)

~~这题咋这么难？~~

------------
注意：本人由于实力有限，部分思路参考[大佬博客](https://blog.csdn.net/zsyzClb/article/details/113934267?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522169260102116800213044521%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=169260102116800213044521&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-113934267-null-null.142^v93^insert_down28v1&utm_term=P5489%20EntropyIncreaser%20%E4%B8%8E%20%E5%8A%A8%E6%80%81%E5%9B%BE&spm=1018.2226.3001.4187)。

------------
## 大致思路：
本题要求我们实现**连接两点之间的无向边以及求两个点之间的割点与桥的数量**（我甚至连割点与割桥的代码都不是很熟练）。

既然标签上写着 LCT，那么就用我才学的 LCT 来实现吧。

首先，我们先来输入一开始的图的各个点以及各个边的信息（但是个空图，后面才是重要的）。同时，我们还要初始化一下 LCT 树上每个点以及边的边权，边权一开始全是 $1$，点权全是 $0$，不用动。接着，我们输入各个操作，紧接着就是 LCT 输大展拳脚的环节了！

对于割边，先是要以点代边，根据前面预处理的结果，边权为 $1$，点权为 $0$。**我们发现在一个环上的边全部都不是割边**（因为你**无论割了那条边也会成一条链**，也可以**互相到达**），所以如果添加的边的两个端点已经联通，我们就把路径上的全部点权值设置为 $0$。

对于割点，我们**动态维护圆方树**（不知道圆方树是啥的可以参看[圆方树简介](https://oi-wiki.org/graph/block-forest/)），如果加一条边就会形成和环，**那么就把环完全断掉**，把环上的每一个点（方点和圆点）**全部连在一个新的方点上**。可以发现**原来环上的任意两个点之间的距离都是** $2$，所以能够保证时间复杂度。查询就输出圆点个数就可以了。

最终，我们在不断进行操作将 LCT 模板函数进行调用（至于函数怎么写我就不讲了，因为太模板了）得到最终结果，并判断是否能够找到换或者链，如果 $\operatorname{findroot}$ 函数返回值与 $x$ 不相符（因为没有走回来 $x$ 点，我是用 LCT 树递上的下传实现的，最终要向上返回结果，同时**在途中更新** LCT **树上各个节点的子问题答案**），就说明没有可以割的点或者边，否则直接输出答案。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int mxn = 4e5 + 10;
int tot1, tot2, num, sta[mxn], n, q, lastans;
struct LCT
{
    int d[mxn], fa[mxn], dat[mxn], ch[mxn][2];
    bool rv[mxn], circle[mxn];
#define lc ch[x][0]
#define rc ch[x][1]
#define ls(x) ch[x][0]
#define rs(x) ch[x][1] // 懒人操作
    bool check(int x)
    {
        return ls(fa[x]) == x || rs(fa[x]) == x;
    }
    void crv(int x)
    {
        if (!x)
        {
            return;
        }
        swap(lc, rc);
        rv[x] ^= 1;
    }
    void clear(int x)
    {
        if (!x)
        {
            return;
        }
        d[x] = dat[x] = 0;
        circle[x] = 1;
    }
    void pushdown(int x)
    {
        if (rv[x])
        {
            crv(lc), crv(rc), rv[x] = 0;
        }
        if (circle[x])
        {
            clear(lc), clear(rc), circle[x] = 0;
        }
    }
    void update(int x)
    {
        dat[x] = dat[lc] + dat[rc] + d[x];
    }
    void rotate(int x)
    {
        int y = fa[x], z = fa[y], w = rs(y) == x;
        if (check(y))
        {
            ch[z][rs(z) == y] = x;
        }
        fa[x] = z;
        fa[ch[y][w] = ch[x][1 - w]] = y;
        ch[x][1 - w] = y, fa[y] = x;
        update(y);
    }
    void splay(int p)
    {
        int x = p, tp = 0;
        sta[++tp] = x;
        while (check(x))
        {
            sta[++tp] = x = fa[x];
        }
        while (tp)
        {
            pushdown(sta[tp--]);
        }
        x = p;
        while (check(x))
        {
            int y = fa[x], z = fa[y];
            if (check(y))
            {
                (rs(z) == y) ^ (rs(y) == x) ? rotate(x) : rotate(y);
            }
            rotate(x);
        }
        update(x);
    }
    void access(int x)
    {
        for (int y = 0; x; x = fa[y = x])
        {
            splay(x), rs(x) = y, update(x);
        }
    }
    void makeroot(int x)
    {
        access(x), splay(x), crv(x);
    }
    int findroot(int x)
    {
        while (lc)
        {
            pushdown(x), x = lc;
        }
        return x;
    }
    void dfs(int x)
    {
        sta[++num] = x;
        if (lc)
        {
            dfs(lc);
            fa[lc] = 0, lc = 0;
        }
        if (rc)
        {
            dfs(rc);
            fa[rc] = 0, rc = 0;
        }
    }
    void solve(int x, int y)
    {
        makeroot(x), access(y), splay(y);
        if (findroot(y) != x)
        {
            cout << -1 << endl;
        }
        else
        {
            lastans = (dat[ls(y)] + d[y]);
            cout << lastans << endl; // 机智压行
        }
    }
} t1, t2; // 第一次玩用结构体存储一大堆函数~~
int main()
{
    n = read();
    q = read();
    tot1 = tot2 = n;
    for (int i = 1; i <= q; i++)
    {
        t1.d[n + i] = t1.dat[n + i] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        t2.d[i] = t2.dat[i] = 1;
    }
    while (q--)
    {
        int op, x, y;
        op = read();
        x = read();
        y = read();
        x ^= lastans;
        y ^= lastans;
        if (op == 1)
        {
            t1.makeroot(x);
            t1.access(y);
            t1.splay(y);
            if (t1.findroot(y) != x)
            {
                t1.fa[x] = ++tot1;
                t1.fa[tot1] = y;
            }
            else
            {
                t1.clear(t1.ch[y][0]);
                t1.update(y);
            }
            t2.makeroot(x);
            t2.access(y);
            t2.splay(y);
            if (t2.findroot(y) != x)
            {
                t2.fa[x] = ++tot2;
                t2.fa[tot2] = y;
            }
            else
            {
                num = 0;
                t2.dfs(y);
                tot2++;
                for (int i = 1; i <= num; i++)
                {
                    t2.fa[sta[i]] = tot2;
                }
            }
        }
        else if (op == 2)
        {
            t1.solve(x, y);
        }
        else
        {
            t2.solve(x, y);
        }
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122074511)

---

## 作者：huta0 (赞：1)

注意到有加边操作，所以用 LCT 来做。

割边很好处理，每次加边看看这条边两端点是否在树上已经连通了，如果连通，那么在这条边两端点的链上所有边都不会是割边了，否则直接加边即可。

割点有点不怎么好处理，考虑圆方树，每次加边看看这条边两端点是否连通了，若是那么连到方点上，否则直接加边，具体操作可以看看代码。
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<unordered_map>
#include<map>
#include<cmath>
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define drep(a,b,c) for(int a=b;a>=c;a--)
#define a_all a.begin(),a.end()
using namespace std;
typedef long long ll;
int n,m,op,a,b,lst;
const int N = 3e5+10;
namespace hikari {
      struct node {
            int p,v,sum,tag,add;
            int s[2];
      } tr[2*N];
      #define fa(x) tr[x].p
      #define lc(x) tr[x].s[0]
      #define rc(x) tr[x].s[1]
      #define ntrt(x) lc(fa(x))==x||rc(fa(x))==x
      void pk(int x) { tr[x].v=0; tr[x].sum=0; tr[x].add=1; }
      void pushup(int x) { tr[x].sum=tr[lc(x)].sum+tr[rc(x)].sum+tr[x].v; }
      void pushdown(int x) {
            if(tr[x].add) {
                  pk(lc(x));
                  pk(rc(x));
                  tr[x].add=0;
            }
            if(tr[x].tag) {
                  swap(lc(x),rc(x));
                  tr[lc(x)].tag^=1;
                  tr[rc(x)].tag^=1;
                  tr[x].tag=0;
            }
      }
      void pushall(int x) {
            if(ntrt(x)) pushall(fa(x));
            pushdown(x);
      }
      void rotate(int x) {
             int y=fa(x),z=fa(y);
             int k= rc(y)==x;
             if(ntrt(y))
                   tr[z].s[rc(z)==y]=x;
             fa(x)=z;
             tr[y].s[k]=tr[x].s[k^1];
             fa(tr[x].s[k^1])=y;
             tr[x].s[k^1]=y;
             fa(y)=x;
             pushup(y); pushup(x);
      }
      void splay(int x) { 
             pushall(x);
             while(ntrt(x)) {
                   int y=fa(x),z=fa(y);
                   if(ntrt(y)) rotate(rc(z)==y^rc(y)==x?x:y);
                   rotate(x);
             }
      }
      void access(int x) {
             int y=0;
             while(x) {
                    splay(x);
                    rc(x)=y;
                    pushup(x);
                    y=x; x=fa(x);
             }
      }
      void mkrt(int x) {
             access(x);
             splay(x);
             tr[x].tag^=1;
      }
      inline int fdrt(int x) {
             access(x);
             splay(x);
             while(lc(x)) pushdown(x),x=lc(x);
             splay(x);
             return x;
      }
      void split(int x,int y) {
             mkrt(x);
             access(y);
             splay(y);
      }
      void link(int x,int y) { 
             mkrt(x);
             if(fdrt(y)!=x) fa(x)=y;
      }
      void cut(int x,int y) {
             mkrt(x);
             if(fdrt(y)==x&&fa(y)==x&&!lc(y))
                  rc(x)=fa(y)=0,pushup(x);
      }
};
namespace tairitsu {
      struct node {
            int p,v=1,sum,tag;
            int s[2];
      } tr[2*N];
      #define fa(x) tr[x].p
      #define lc(x) tr[x].s[0]
      #define rc(x) tr[x].s[1]
      #define ntrt(x) lc(fa(x))==x||rc(fa(x))==x
      void pushup(int x) { tr[x].sum=tr[lc(x)].sum+tr[rc(x)].sum+tr[x].v; }
      void pushdown(int x) {
            if(tr[x].tag) {
                  swap(lc(x),rc(x));
                  tr[lc(x)].tag^=1;
                  tr[rc(x)].tag^=1;
                  tr[x].tag=0;
            }
      }
      void pushall(int x) {
            if(ntrt(x)) pushall(fa(x));
            pushdown(x);
      }
      void rotate(int x) {
             int y=fa(x),z=fa(y);
             int k= rc(y)==x;
             if(ntrt(y))
                   tr[z].s[rc(z)==y]=x;
             fa(x)=z;
             tr[y].s[k]=tr[x].s[k^1];
             fa(tr[x].s[k^1])=y;
             tr[x].s[k^1]=y;
             fa(y)=x;
             pushup(y); pushup(x);
      }
      void splay(int x) { 
             pushall(x);
             while(ntrt(x)) {
                   int y=fa(x),z=fa(y);
                   if(ntrt(y)) rotate(rc(z)==y^rc(y)==x?x:y);
                   rotate(x);
             }
      }
      void access(int x) {
             int y=0;
             while(x) {
                    splay(x);
                    rc(x)=y;
                    pushup(x);
                    y=x; x=fa(x);
             }
      }
      void mkrt(int x) {
             access(x);
             splay(x);
             tr[x].tag^=1;
      }
      inline int fdrt(int x) {
             access(x);
             splay(x);
             while(lc(x)) pushdown(x),x=lc(x);
             splay(x);
             return x;
      }
      void split(int x,int y) {
             mkrt(x);
             access(y);
             splay(y);
      }
      void link(int x,int y) { 
             mkrt(x);
             if(fdrt(y)!=x) fa(x)=y;
      }
      void cut(int x,int y) {
             mkrt(x);
             if(fdrt(y)==x&&fa(y)==x&&!lc(y))
                  rc(x)=fa(y)=0,pushup(x);
      }
      int num[2*N],top=0,pct=0;
      void dfs(int x) {
            if(!x) return;
            pushdown(x);
            dfs(lc(x));
            num[++top]=x;
            dfs(rc(x));
      }
      inline void init() {
            tr[pct].v=0;
            rep(i,1,top-1) cut(num[i],num[i+1]);
            rep(i,1,top) link(num[i],pct);
      }
};
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int fat[N];
inline int find(int x) { return fat[x]==x?x:fat[x]=find(fat[x]); }
inline void merge(int x,int y) { if(find(x)!=find(y)) fat[find(x)]=find(y); }
inline int cot(int x,int y) { return find(x)==find(y); }
signed main() {
      n=read(); m=read();
      tairitsu::pct=n;
      rep(i,1,n) fat[i]=i;
      rep(i,1,m) {
           op=read(); a=read(); b=read();
           a^=lst,b^=lst;
           if(op==1) {
                if(cot(a,b)) {
                    hikari::split(a,b),hikari::pk(b);
                    tairitsu::split(a,b);
                    if(tairitsu::tr[b].sum<=2) continue;
                    tairitsu::top=0;
                    tairitsu::dfs(b);
                    ++tairitsu::pct;
                    tairitsu::init();
                }
                else hikari::tr[i+n].v=1,hikari::link(a,i+n),hikari::link(i+n,b),tairitsu::link(a,b),merge(a,b);
           } else if(op==2) {
                if(!cot(a,b)) printf("-1\n");
                else {
                     hikari::split(a,b);
                     printf("%d\n",hikari::tr[b].sum);
                     lst=hikari::tr[b].sum;
                }
           } else if(op==3) {
                if(!cot(a,b)) cout<<-1<<endl;
                else {
                     tairitsu::split(a,b);
                     printf("%d\n",tairitsu::tr[b].sum);
                     lst=tairitsu::tr[b].sum;
                }
           }
      }
      
      return 0;
}
```

---

## 作者：pitiless0514 (赞：1)

## 题目大意
$n$ 个点的图，初始没有边，执行 $3$ 种操作。

动态加边，动态查询两点间割边与割点的数量。

操作一共 $q$ 次。

$\text{Data Range:} 1 \le n \le 10^5, 1\le q\le 3 \times 10^5$

---------
作为 $\text{LCT}$ 的维护图结构的练手题是不错的。

分别考虑如何求割边割点。

先考虑割边怎么做。

考虑一棵树的割边就是树上的边数量，当形成了一个环的时候，这个环内的全部边将都不是割边。

因为动态加边，自然想到 $\text{LCT}$ 维护，考虑因为维护的是边，肯定要新加点，初始将可能被加入的点全部值设为 $1$，然后查询就是查询两点间的权值和。

加边时如果两点没有联通直接加就好了。

如果已经连通，代表成环了，于是要去掉这路径上边的贡献，等价于将两点间边值全部变为 $0$。

这东西直接提出路径之后打标记就好了。

考虑割点怎么做。

求割点常用的做法是圆方树。

那考虑动态维护一个圆方树。

其实和上面差不多，如果加边的时候成环了，那就直接暴力遍历每个环，然后删环，建一个方点，这些换上点都是圆点直接连向这个方点，方点权值设为 $1$。

那么询问仍然是一个问两点间权值和的问题。

做完了，总复杂度为 $n \log n$，代码挺好写的。

```cpp
// 德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱
// 德丽莎的可爱在于德丽莎很可爱，德丽莎为什么很可爱呢，这是因为德丽莎很可爱！
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6;
int n, q, las, tot;
vector<int> ver;
class LCT {
  public :
  struct node {
    int val, tag, fa, ltag;
    int ch[2];
    int siz;//割边数量
    int sum;//割点数量
  }t[N];
  public :
  #define ls(k) t[k].ch[0]
  #define rs(k) t[k].ch[1]
  public :
  void pushup(int k) {
    t[k].siz = t[ls(k)].siz + t[rs(k)].siz + t[k].val;
    t[k].sum = t[ls(k)].sum + t[rs(k)].sum + t[k].val;
  }
  public :
  bool chk(int x) {
    return ( rs(t[x].fa) != x ) && ( ls(t[x].fa) != x );
  }
  public :
  void pushdown(int x) {
    if( t[x].tag ) {
      swap( ls(x), rs(x) );
      t[x].tag = 0;
      t[ls(x)].tag ^= 1;  t[rs(x)].tag ^= 1;
    }
    if( t[x].ltag ) {
      t[x].ltag = 0;
      t[ls(x)].ltag = t[rs(x)].ltag = 1;
      t[ls(x)].siz = t[rs(x)].siz = 0;
      t[ls(x)].val = t[rs(x)].val = 0;
    }
  }
  public :
  void rotate(int x) {
    int f = t[x].fa, ff = t[f].fa;
    int z = (rs(f) == x), ch = t[x].ch[z ^ 1];
    t[x].fa = ff; 
    if( !chk(f) ) t[ff].ch[rs(ff) == f] = x;
    t[f].fa = x;  t[x].ch[z ^ 1] = f;
    t[ch].fa = f;  t[f].ch[z] = ch;
    pushup(f), pushup(x);
  }
  public :
  int st[N], tp;
  public :
  void splay(int x) {
    int u = x;  st[++tp] = x;
    while(!chk(u)) st[++tp] = (u = t[u].fa);
    while(tp) pushdown(st[tp--]);
    while(!chk(x)) {
      int f = t[x].fa, ff = t[f].fa;
      if(!chk(f)) {
        ( ( rs(ff) == f ) ^ ( rs(f) == x ) ) ? rotate(x) : rotate(f);
      }
      rotate(x);
    }
  }
  public :
  void access(int x) {
    for(int y = 0; x; y = x, x = t[x].fa) {
      splay(x);  rs(x) = y;  pushup(x);
    }
  }
  public :
  void makeroot(int x) {
    access(x);  splay(x);  t[x].tag ^= 1;
  }
  public :
  void spilt(int x,int y) {
    makeroot(x);  access(y);  splay(y);
  }
  public :
  int findrt(int x) {
    access(x);  splay(x);  pushdown(x);
    while ( ls(x) ) pushdown( x = ls(x) );
    return x;
  }
  public :
  void link(int x,int y) {
    makeroot(x);
    if(findrt(y) != x) t[x].fa = y;
  }
  public :
  bool cut(int x,int y) {
    if(findrt(x) != findrt(y)) return 0;
    spilt(x, y);
    if(t[x].fa != y || t[x].ch[1]) return 0;
    t[x].fa = t[y].ch[0] = 0;
    pushup(x);
    return 1;
  }
  void dfs(int x, vector<int>& ver) {
    pushdown(x);
    if(t[x].ch[0]) dfs(t[x].ch[0], ver);
    ver.push_back(x);
    if(t[x].ch[1]) dfs(t[x].ch[1], ver);
  }
  void getroad(int x,int y, vector<int>& ver) {
    ver.clear();
    spilt(x, y);
    dfs(y, ver);
  }
};
LCT A, B;
signed main () {
  ios :: sync_with_stdio( 0 );
  cin.tie( 0 ), cout.tie( 0 );
  cin >> n >> q;
  for(int i = n + 1; i <= n + q; i++) A.t[i].val = 1;
  for(int i = 1; i <= n; i++) B.t[i].val = 1;
  tot = n;
  int num = n;
  for(int i = 1; i <= q; i++) {
    int op, u, v, w;  cin >> op >> u >> v;
    u ^= las;  v ^= las;
    //cout << u << " " << v << "\n";
    int qx = A.findrt(u);
    int qy = A.findrt(v);
    if(op == 1) {
      if(qx == qy) {
        //割边
        A.spilt(u, v);
        A.t[v].siz = 0;  A.t[v].val = 0;
        A.t[v].ltag = 1;
        //割点
        B.getroad(u, v, ver);
        for(int i = 1; i < ver.size(); i++) B.cut(ver[i], ver[i - 1]);
        ++num;
        for(int i = 0; i < ver.size(); i++) B.link(ver[i], n + num);
      }  else  {
        tot++;
        A.link(u, tot);  A.link(tot, v);
        B.link(u, v);
      }
    }  else if(op == 2) {
      if(qx != qy) {  cout << "-1\n";  continue;  }
      A.spilt(u, v);
      las = A.t[v].siz;
      cout << A.t[v].siz << "\n";
    }  else if(op == 3) {
      if(qx != qy) {  cout << "-1\n";  continue;  }
      B.spilt(u, v);
      las = B.t[v].sum;
      cout << B.t[v].sum << "\n";
    }
  }
  return 0;
}
```

---

## 作者：Starstream (赞：0)

### 题意

动态加边，维护两点 $x, y$ 间割点和桥的数量。强制在线。

### 思路

不难想到 LCT。

动态求割点的板子题是 [P5622 [DBOI2019] 巫女的职责](https://www.luogu.com.cn/problem/P5622)。

求割点部分放个本人的题解 [链接](https://www.luogu.com.cn/blog/860817/solution-p5622)，不多赘述了。

动态求桥的板子题是 [P2542 [AHOI2005] 航线规划](https://www.luogu.com.cn/problem/P2542)。

显然，树上所有边都是桥；每次加边时，若出现环，则环上所有边都不是桥。

具体地，初始我们将所有边权赋值为 $1$，如果出现环那么将这个环上所有边权变为 $0$，查询操作即转化为求路径和。

于是开两棵 LCT 分别维护割点和桥即可。

### 代码

```cpp
#include <iostream>

using namespace std;

const int N = 300010;

int n, m, la;
struct Splay_Node
{
    int s[2], p, v;
    int sum, rev, cov;
};

struct Link_Cut_Tree
{
    Splay_Node tr[N];
    int stk[N], idx, cnt;
    inline void pushrev(int x) {swap(tr[x].s[0], tr[x].s[1]), tr[x].rev ^= 1;}
    inline void pushcov(int x) {tr[x].v = tr[x].sum = 0, tr[x].cov = 1;}
    inline void pushup(int x) {tr[x].sum = tr[tr[x].s[0]].sum + tr[x].v + tr[tr[x].s[1]].sum;}
    inline bool is_root(int x) {return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x;}
    inline void pushdown(int x)
    {
        if (tr[x].rev) pushrev(tr[x].s[0]), pushrev(tr[x].s[1]), tr[x].rev ^= 1;
        if (tr[x].cov) pushcov(tr[x].s[0]), pushcov(tr[x].s[1]), tr[x].cov = 0;
    }

    inline void rotate(int x)
    {
        int y = tr[x].p, z = tr[y].p;
        int k = tr[y].s[1] == x;
        if (!is_root(y)) tr[z].s[tr[z].s[1] == y] = x;
        tr[x].p = z;
        tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
        tr[x].s[k ^ 1] = y, tr[y].p = x;
        pushup(y), pushup(x);
    }

    inline void splay(int x)
    {
        int top = 0, r = x;
        stk[ ++ top] = r;
        while (!is_root(r)) stk[ ++ top] = tr[r].p, r = tr[r].p;
        while (top) pushdown(stk[top -- ]);
        while (!is_root(x))
        {
            int y = tr[x].p, z = tr[y].p;
            if (!is_root(y))
                if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
                else rotate(y);
            rotate(x);
        }
    }

    void flatten(int u)
    {
        pushdown(u);
        if (tr[u].s[0]) flatten(tr[u].s[0]);
        stk[ ++ idx] = u;
        if (tr[u].s[1]) flatten(tr[u].s[1]);
    }

    inline int access(int x)
    {
        int z = x, y;
        for (y = 0; x; y = x, x = tr[x].p)
            splay(x), tr[x].s[1] = y, pushup(x);
        splay(z);
        return y;
    }

    inline void make_root(int x) {access(x), pushrev(x);}
    inline int find_root(int x)
    {
        access(x);
        while (tr[x].s[0]) pushdown(x), x = tr[x].s[0];
        splay(x);
        return x;
    }

    inline bool judge(int x, int y) {make_root(x); return find_root(y) == x;}
    inline void split(int x, int y) {make_root(x); access(y);}
    inline bool link(int x, int y)
    {
        if (judge(x, y)) return false;
        else tr[x].p = y;
        return true;
    }
}cut, brg;

inline void add_brg(int x, int y)
{
    if (brg.judge(x, y)) brg.split(x, y), brg.pushcov(y);
    else brg.link(x, ++ brg.cnt), brg.link(y, brg.cnt);
}

inline void add_cut(int x, int y)
{
    if (cut.link(x, y)) return;
    cut.split(x, y);
    cut.idx = 0, cut.cnt ++ ;
    cut.flatten(y);
    while (cut.idx)
    {
        int u = cut.stk[cut.idx -- ];
        cut.tr[u].p = cut.cnt, cut.tr[u].s[0] = cut.tr[u].s[1] = 0;
        cut.pushup(u);
    }
}

int main()
{
    int op, x, y;
    scanf("%d%d", &n, &m), cut.cnt = brg.cnt = n;
    for (int i = 1; i <= n; i ++ ) cut.tr[i].v = 1;
    for (int i = 1; i <= m; i ++ ) brg.tr[i + n].v = 1;
        
    while (m -- )
    {
        scanf("%d%d%d", &op, &x, &y);
        x ^= la, y ^= la;
        if (op == 1) add_cut(x, y), add_brg(x, y);
        else if (op == 2)
        {
            if (!brg.judge(x, y)) puts("-1");
            else brg.split(x, y), printf("%d\n", (la = brg.tr[y].sum));
        }
        else
        {
            if (!cut.judge(x, y)) puts("-1");
            else cut.split(x, y), printf("%d\n", (la = cut.tr[y].sum));
        }
    }
    return 0;
}
```

---

## 作者：SrsgPrince_ (赞：0)

# Luogu P5489 EntropyIncreaser 与 动态图 Solution

题面传送门：[Luogu P5489 EntropyIncreaser 与 动态图](https://www.luogu.com.cn/problem/P5489)。

推荐在我的 [博客](https://www.luogu.com.cn/blog/fy123333/LuoguP5489Solution) 中查看。

## 题目分析 Hint

题目如下：

有一个 $n$ 个点的图，初始没有边。

有 $q$ 个操作，分为 $3$ 种：
1. `1 u v` 表示在 $u, v$ 之间连一条无向边
2. `2 u v` 表示求 $u, v$ 之间的割边数量
3. `3 u v` 表示求 $u, v$ 之间的割点数量

对于操作 $2, 3$，如果边不连通，那么输出 $-1$。

强制在线，每次的输入的 $u, v$ 都需要异或上 $last$。

操作 $1$ 中的动态加边说明这题是 LCT，动态加边比较基础，考虑的是用 LCT 动态维护割边和割点。

## 思路 Solution

首先是维护割边。首先能想到，环没有割边，链上每条边都是割边，那么维护割边的时候，当加边时产生了环，那么这条环上的所有边都不是割边。做法是联结一条边之后，如果不连通，则把两边权值设为 $1$，如果已经联通，那么两节点之间的链以及新加的这条边的权值设为 $0$，维护权值和。

接下来是割点。先转为静态的割点来讲，正常来说，我们会先考虑到圆方树。根据这个思路，我们可以动态维护圆方树。原本的所有点都是圆点，如果像上文一样，连接边是发现这两个节点已经联通，那么断开这个环上的连接并把这个子树上的点连接到一个方点上。维护和的时候直接求圆点的数量，因为对于每一个方点，都不存在割点，保证了正确性。

这两个操作我放在了两棵 LCT 里。时间复杂度每一个操作均摊下来都是 $O(n \log n)$。

下面放上通过代码：

```cpp
int n, q, opt, u, v, last, tot, res, cnt, fa[maxn];
struct LinkCutTree { // 这个棵 LCT 用来维护割边
    int chd[maxn][2], fa[maxn], revtag[maxn], val[maxn], sum[maxn], mrk[maxn];
    inline bool nRoot(int x) {
        return chd[fa[x]][0] == x || chd[fa[x]][1] == x;
    }
    inline void reverse(int x) {
        if (x) {
            swap(chd[x][0], chd[x][1]);
            revtag[x] ^= 1;
        }
    }
    inline void pushTag(int x) {
        if (x) {
            val[x] = sum[x] = 0;
            mrk[x] = 1;
        }
    }
    inline void pushUp(int x) {
        sum[x] = sum[chd[x][0]] + sum[chd[x][1]] + val[x];
    }
    inline void pushDown(int x) {
        if (revtag[x]) {
            reverse(chd[x][0]);
            reverse(chd[x][1]);
            revtag[x] = 0;
        }
        if (mrk[x]) {
            pushTag(chd[x][0]);
            pushTag(chd[x][1]);
            mrk[x] = 0;
        }
    }
    inline void pushAll(int x) {
        if (nRoot(x))
            pushAll(fa[x]);
        pushDown(x);
    }
    inline void rotate(int x) {
        int y = fa[x], z = fa[y], k = x == chd[y][1];
        chd[y][k] = chd[x][!k];
        chd[x][!k] = y;
        if (nRoot(y))
            chd[z][y == chd[z][1]] = x;
        if (chd[y][k])
            fa[chd[y][k]] = y;
        fa[y] = x;
        fa[x] = z;
        pushUp(y);
    }
    inline void splay(int x) {
        int y, z;
        for (pushAll(x); nRoot(x); rotate(x)) {
            y = fa[x], z = fa[y];
            if (nRoot(y))
                rotate((chd[y][1] == x) ^ (chd[z][1] == y) ? x : y);
        }
        pushUp(x);
    }
    inline void access(int x) {
        for (int y = 0; x; x = fa[y = x]) {
            splay(x);
            chd[x][1] = y;
            pushUp(x);
        }
    }
    inline void makeRoot(int x) {
        access(x);
        splay(x);
        reverse(x);
    }
    inline void link(int x, int y) {
        makeRoot(x);
        fa[x] = y;
    }
    inline void cut(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        fa[x] = chd[y][0] = 0;
        pushUp(y);
    }
} lct;
struct LinkCutTree2 { // 这棵 LCT 用来维护割点
    int chd[maxn][2], fa[maxn], revtag[maxn], val[maxn], sum[maxn], mrk[maxn], stk[maxn], num;
    inline bool nRoot(int x) {
        return chd[fa[x]][0] == x || chd[fa[x]][1] == x;
    }
    inline void reverse(int x) {
        if (x) {
            swap(chd[x][0], chd[x][1]);
            revtag[x] ^= 1;
        }
    }
    inline void pushTag(int x) {
        if (x) {
            val[x] = sum[x] = 0;
            mrk[x] = 1;
        }
    }
    inline void pushUp(int x) {
        sum[x] = sum[chd[x][0]] + sum[chd[x][1]] + val[x];
    }
    inline void pushDown(int x) {
        if (revtag[x]) {
            reverse(chd[x][0]);
            reverse(chd[x][1]);
            revtag[x] = 0;
        }
        if (mrk[x]) {
            pushTag(chd[x][0]);
            pushTag(chd[x][1]);
            mrk[x] = 0;
        }
    }
    inline void pushAll(int x) {
        if (nRoot(x))
            pushAll(fa[x]);
        pushDown(x);
    }
    inline void rotate(int x) {
        int y = fa[x], z = fa[y], k = x == chd[y][1];
        chd[y][k] = chd[x][!k];
        chd[x][!k] = y;
        if (nRoot(y))
            chd[z][y == chd[z][1]] = x;
        if (chd[y][k])
            fa[chd[y][k]] = y;
        fa[y] = x;
        fa[x] = z;
        pushUp(y);
    }
    inline void splay(int x) {
        int y, z;
        for (pushAll(x); nRoot(x); rotate(x)) {
            y = fa[x], z = fa[y];
            if (nRoot(y))
                rotate((chd[y][1] == x) ^ (chd[z][1] == y) ? x : y);
        }
        pushUp(x);
    }
    inline void access(int x) {
        for (int y = 0; x; x = fa[y = x]) {
            splay(x);
            chd[x][1] = y;
            pushUp(x);
        }
    }
    inline void makeRoot(int x) {
        access(x);
        splay(x);
        reverse(x);
    }
    inline void link(int x, int y) {
        makeRoot(x);
        fa[x] = y;
    }
    inline void cut(int x, int y) {
        makeRoot(x);
        access(y);
        splay(y);
        fa[x] = chd[y][0] = 0;
        pushUp(y);
    }
    inline void cpy(int now) {
        if (now) {
            pushDown(now);
            cpy(chd[now][0]);
            stk[++num] = now;
            cpy(chd[now][1]);
        }
    }
} lct2;
inline int find(int x) { // 并查集维护缩点之后的点
    return (x == fa[x]) ? x : fa[x] = find(fa[x]);
}
inline void getEdge(int u, int v) {
    int x = find(u), y = find(v);
    if (x != y) {
        res = -1;
        return;
    }
    lct.makeRoot(u);
    lct.access(v);
    lct.splay(v);
    res = lct.sum[v];
}
inline void getPoint(int u, int v) {
    int x = find(u), y = find(v);
    if (x != y) {
        res = -1;
        return;
    }
    lct2.makeRoot(u);
    lct2.access(v);
    lct2.splay(v);
    res = lct2.sum[v];
}
inline void link(int u, int v) {
    int x = find(u), y = find(v);
    if (x == y) {
        lct.makeRoot(u);
        lct.access(v);
        lct.splay(v);
        lct.pushTag(v);
        getPoint(u, v);
        if (res > 2) {
            ++cnt;
            lct2.makeRoot(u);
            lct2.access(v);
            lct2.splay(v);
            lct2.num = 0;
            lct2.cpy(v);
            for (int i = 1; i < lct2.num; ++i)
                lct2.cut(lct2.stk[i], lct2.stk[i+1]);
            for (int i = 1; i <= lct2.num; ++i)
                lct2.link(lct2.stk[i], cnt);
        }
    } else {
        ++tot;
        fa[y] = x;
        lct.val[tot] = 1;
        lct.link(u, tot);
        lct.link(tot, v);
        lct2.link(u, v);
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> q;
    tot = cnt = n;
    for (int i = 1; i <= n; ++i)
        fa[i] = i, lct2.val[i] = 1;
    while (q--) {
        cin >> opt >> u >> v;
        u ^= last, v ^= last;
        if (opt == 1)
            link(u, v);
        else if (opt == 2) {
            getEdge(u, v);
            if (res != -1) 
                last = res;
            cout << res << "\n";
        }
        else if (opt == 3) {
            getPoint(u, v);
            if (res != -1) 
                last = res;
            cout << res << "\n";
        }
    }
    return 0;
}
```

截止写完题解的时间 2023-07-10 10:18，仍然是最优解（我也没卡常啊）。


---

## 作者：hlsnqdmz (赞：0)

一道练习 LCT 很不错的题（当然难度不小），也是用 LCT 维护割边割点的模板题，当然单独维护[割边](https://www.luogu.com.cn/problem/P2542)和[割点](https://www.luogu.com.cn/problem/P5622)也有自己的模板题。

看到操作，第一个就是基础的连边，这也是我们选择 LCT 的原因，这里略过。

## 维护割边
我们知道，一个环所有边都不是割边，一条链所有边都是割边，所以我们连边时判断两点是否连通，连通就不连边直接推平，否则连边。这里我最开始忘了 LCT 维护边权的方式是新建一个节点令其点权为 1 来表示边权，还在纳闷怎么维护（还是我太**蒻**了），其他操作都是 LCT 板子。

## 维护割点
这个可能不太好想，但是好写，也是连边时检测两点是否连通，如果不连通就直接连边，否则 `split()` 让 $y$ 成为树根，然后 `dfs` 把 $y\to x$ 路径上所有点都与一个新建节点相连，这个节点的点权设为 0，具体操作就是让路径上的点的父亲设为方点，下传标记以后 `dfs` 左右儿子，然后清空左右儿子，最后别忘了 `push_up()` 这样我们就动态建立圆方树，然后查询就直接查就可以了。

代码重度卡常（其实火车头被我删了），马蜂丑陋，如果观感不好请见谅（不过在我这里居然是[人蒻常数小吗](https://www.luogu.com.cn/record/list?pid=P5489&orderBy=1&status=&page=1)）：

```
//Just Sayori
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long
#define rnt register int
#define gr getchar_unlocked
#define pr putchar_unlocked
#define N 500005
#define M 1000000007
using namespace std;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = gr();
    while (ch < '0' || ch > '9')
        ch == '-' ? f = -1, ch = gr() : ch = gr();
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + (ch ^ 48), ch = gr();
    return x * f;
}

inline void write(ll x)
{
    static int sta[39], top = 0;
    if (x < 0)
        pr('-'), x = -x;
    do
        sta[++top] = x % 10, x /= 10;
    while (x);
    while (top)
        pr(sta[top--] ^ 48);
}
#define fa(x) s[x].fa
#define lc(x) s[x].ch[0]
#define rc(x) s[x].ch[1]
#define is_root(x) (lc(fa(x))==x||rc(fa(x))==x)

int n, m, u, v, bcc, tot;
ll last;

struct giedian//维护割点
{
    struct tree
    {
        int ch[2];
        int fa, tag;
        ll w, sum;
    } s[N << 1];
    inline void push_up(int u)
    {
        s[u].sum = s[lc(u)].sum + s[rc(u)].sum + s[u].w;
    }

    inline void push_down(int u)
    {
        if (s[u].tag)
        {
            swap(lc(u), rc(u));
            s[lc(u)].tag ^= 1;
            s[rc(u)].tag ^= 1;
            s[u].tag = 0;
        }
    }

    void push_all(int u)
    {
        if (is_root(u))
            push_all(fa(u));
        push_down(u);
    }

    inline void rotate(int x)
    {
        int y = fa(x), z = fa(y);
        bool k1 = rc(y) == x, k2 = rc(z) == y;
        if (is_root(y))
            s[z].ch[k2] = x;
        fa(x) = z;
        s[y].ch[k1] = s[x].ch[k1 ^ 1];
        fa(s[x].ch[k1 ^ 1]) = y;
        s[x].ch[k1 ^ 1] = y;
        fa(y) = x;
        push_up(y), push_up(x);
    }

    void splay(int x)
    {
        push_all(x);
        while (is_root(x))
        {
            int y = fa(x), z = fa(y);
            if (is_root(y))
                (rc(y) == x)^(rc(z) == y) ? rotate(x) : rotate(y);
            rotate(x);
        }
    }

    void access(int x)
    {
        for (rnt y = 0; x; y = x, x = fa(x))
        {
            splay(x);
            rc(x) = y;
            push_up(x);
        }
    }

    void make_root(int u)
    {
        access(u);
        splay(u);
        s[u].tag ^= 1;
    }

    int find_root(int u)
    {
        access(u);
        splay(u);
        while (lc(u))
            push_down(u), u = lc(u);
        splay(u);
        return u;
    }

    void split(int u, int v)
    {
        make_root(u);
        access(v);
        splay(v);
    }

    void dfs(int u, int f)//dfs 连接方点
    {
        if (!u)
            return;
        fa(u) = f;
        push_down(u);
        dfs(lc(u), f);
        dfs(rc(u), f);
        lc(u) = rc(u) = 0;
        push_up(u);
    }

    void link(int u, int v)
    {
        make_root(u);
        if (find_root(v) != u)
            fa(u) = v;
        else
            bcc++, split(u, v), dfs(v, bcc);//新建方点，连接
    }
} s;

struct giebian//维护割边
{
    struct tree
    {
        int ch[2];
        int fa, tag, tag2;
        ll w, sum;
    } s[N << 1];
    inline void push_up(int u)
    {
        s[u].sum = s[lc(u)].sum + s[rc(u)].sum + s[u].w;
    }

    inline void push_down(int u)
    {
        if (s[u].tag)
        {
            swap(lc(u), rc(u));
            s[lc(u)].tag ^= 1;
            s[rc(u)].tag ^= 1;
            s[u].tag = 0;
        }
        if (s[u].tag2)//区间推平
        {
            s[lc(u)].tag2 = s[rc(u)].tag2 = 1;
            s[lc(u)].w = s[lc(u)].sum = 0;
            s[rc(u)].w = s[rc(u)].sum = 0;
            s[u].tag2 = 0;
        }
    }

    void push_all(int u)
    {
        if (is_root(u))
            push_all(fa(u));
        push_down(u);
    }

    inline void rotate(int x)
    {
        int y = fa(x), z = fa(y);
        bool k1 = rc(y) == x, k2 = rc(z) == y;
        if (is_root(y))
            s[z].ch[k2] = x;
        fa(x) = z;
        s[y].ch[k1] = s[x].ch[k1 ^ 1];
        fa(s[x].ch[k1 ^ 1]) = y;
        s[x].ch[k1 ^ 1] = y;
        fa(y) = x;
        push_up(y), push_up(x);
    }

    void splay(int x)
    {
        push_all(x);
        while (is_root(x))
        {
            int y = fa(x), z = fa(y);
            if (is_root(y))
                (rc(y) == x)^(rc(z) == y) ? rotate(x) : rotate(y);
            rotate(x);
        }
    }

    void access(int x)
    {
        for (rnt y = 0; x; y = x, x = fa(x))
        {
            splay(x);
            rc(x) = y;
            push_up(x);
        }
    }

    void make_root(int u)
    {
        access(u);
        splay(u);
        s[u].tag ^= 1;
    }

    int find_root(int u)
    {
        access(u);
        splay(u);
        while (lc(u))
            push_down(u), u = lc(u);
        splay(u);
        return u;
    }

    void split(int u, int v)
    {
        make_root(u);
        access(v);
        splay(v);
    }

    void link(int u, int v)
    {
        make_root(u);
        if (find_root(v) != u)
            fa(u) = ++tot, fa(tot) = v, s[tot].w = s[tot].sum = 1;//新建点权表示边权节点，别忘了设置点权
        else
            split(u, v), s[v].w = s[v].sum = 0, s[v].tag2 = 1;//区间推平
    }
} k;

int main()
{
    tot = bcc = n = read(), m = read();
    for (rnt i = 1; i <= n; i++)
        s.s[i].w = s.s[i].sum = 1;
    for (rnt i = 1; i <= m; i++)
        switch (read())
        {
            case 1:
                u = read()^last, v = read()^last;
                s.link(u, v);
                k.link(u, v);
                break;
            case 2:
                u = read()^last, v = read()^last;
                if (k.find_root(u) == k.find_root(v))
                {
                    k.split(u, v);
                    last = k.s[v].sum;
                    write(last), pr(10);
                }
                else
                    printf("-1\n");
                break;
            case 3:
                u = read()^last, v = read()^last;
                if (s.find_root(u) == s.find_root(v))
                {
                    s.split(u, v);
                    last = s.s[v].sum;
                    write(last), pr(10);
                }
                else
                    printf("-1\n");
                break;
        }
    return 0;
}
```

### 感谢您的观看！

---

