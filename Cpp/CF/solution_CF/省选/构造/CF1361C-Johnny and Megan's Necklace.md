# Johnny and Megan's Necklace

## 题目描述

Johnny's younger sister Megan had a birthday recently. Her brother has bought her a box signed as "Your beautiful necklace — do it yourself!". It contains many necklace parts and some magic glue.

The necklace part is a chain connecting two pearls. Color of each pearl can be defined by a non-negative integer. The magic glue allows Megan to merge two pearls (possibly from the same necklace part) into one. The beauty of a connection of pearls in colors $ u $ and $ v $ is defined as follows: let $ 2^k $ be the greatest power of two dividing $ u \oplus v $ — [exclusive or](https://en.wikipedia.org/wiki/Exclusive_or#Computer_science) of $ u $ and $ v $ . Then the beauty equals $ k $ . If $ u = v $ , you may assume that beauty is equal to $ 20 $ .

Each pearl can be combined with another at most once. Merging two parts of a necklace connects them. Using the glue multiple times, Megan can finally build the necklace, which is a cycle made from connected necklace parts (so every pearl in the necklace is combined with precisely one other pearl in it). The beauty of such a necklace is the minimum beauty of a single connection in it. The girl wants to use all available necklace parts to build exactly one necklace consisting of all of them with the largest possible beauty. Help her!

## 说明/提示

In the first example the following pairs of pearls are combined: $ (7, 9) $ , $ (10, 5) $ , $ (6, 1) $ , $ (2, 3) $ and $ (4, 8) $ . The beauties of connections equal correspondingly: $ 3 $ , $ 3 $ , $ 3 $ , $ 20 $ , $ 20 $ .

The following drawing shows this construction.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1361C/6125420b0e694cf370b4926dc6818a057d7952f1.png)

## 样例 #1

### 输入

```
5
13 11
11 1
3 5
17 1
9 27```

### 输出

```
3
8 7 9 10 5 6 1 2 3 4```

## 样例 #2

### 输入

```
5
13 11
11 1
3 5
17 1
7 29```

### 输出

```
2
8 7 10 9 5 6 4 3 2 1```

## 样例 #3

### 输入

```
1
1 1```

### 输出

```
20
2 1```

# 题解

## 作者：Alex_Wei (赞：18)

> [题面传送门](https://www.luogu.com.cn/problem/CF1361C)。

> 题意简述：$n$ 对珍珠由 $n$ 条所连起来，共 $2n$ 颗。现在你可以在任意两个未被线连起来的珍珠之间连一条线，共可连 $n$ 条，使得这 $2n$ 颗珍珠形成一个环。设一条线所连的两颗珍珠权值为 $u,v$，则该线的权值为最大的整数 $k$ 满足 $2^k|u \oplus v$。如果 $u=v$，则 $k=20$。求所有**新连的线**的权值最小值的最大值并给出方案，即 $2n$ 颗珍珠所形成的的环。

---

因为答案取值数很少，所以我们可以从小到大贪心。

如何判断答案是否能为 $i$：

因为所有新连的线 $(u,v)$ 都要满足 $2^i|u\oplus v$，所以 $u,v$ 在二进制下的后 $i$ 位必须相等。这就启发我们对于每个原有的线 $(u,v)$，在新图 $G_i$ 中添加一条边 $(u\bmod2^i,v\bmod2^i)$，这样一来，**如果答案能为 $i$，则无向图 $G_i$ 必有欧拉回路。**

根据判断一个图是否有欧拉回路的充要条件，$G_i$ 的每个顶点的度数都必须是偶数，且只能有 $1$ 个连通块。每次判断的时间复杂度是 $O(n)$。

找到答案后找欧拉回路即可，其方法在此不再赘述。

时间复杂度 $O(20n)$，可以通过。

容易发现答案满足单调性，所以可以用二分法将时间复杂度优化至 $O(n\log_2 20)$。

代码使用的是枚举法。为更好的阅读体验，代码中的板子已省略。

```cpp
const int N=(1<<20)+5;

struct edge {int u,v,to,d;}vv[N];
int c,hd[N],nxt[N];
void add(int u,edge t){nxt[++c]=hd[u],hd[u]=c,vv[c]=t;}

int n,a[N],b[N],v[N];
vector <int> ans;

void cir(int id){
	for(int i=hd[id];i;i=hd[id]){
		hd[id]=nxt[i]; edge it=vv[i];
		if(!v[it.d])v[it.d]=1,cir(it.to),ans.pb(it.v),ans.pb(it.u);
	}
}

void end(int k){
	int bs=(1<<k)-1; mem(v,0);
	for(int i=1;i<=n;i++){
		int c=a[i]&bs,d=b[i]&bs;
		add(c,(edge){i*2-1,i*2,d,i}),add(d,(edge){i*2,i*2-1,c,i});
	} cir(a[1]&bs);
	cout<<k<<endl; for(int it:ans)cout<<it<<" ";
	exit(0);
}

vector <int> e[N];

void dfs(int id){v[id]=1; for(int it:e[id])if(!v[it])dfs(it);}
int block(int k){int c=0; for(int i=0;i<1<<k;i++)if(e[i].size()&&!v[i]){c++,dfs(i);} return c;}

int main(){
	n=read(); for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	for(int i=1,bs=1;i<=20;i++,bs=(bs<<1)+1,mem(v,0)){
		for(int j=0;j<1<<i;j++)e[j].clear();
		for(int j=1;j<=n;j++){int c=a[j]&bs,d=b[j]&bs; e[c].pb(d),e[d].pb(c);}
		int od=0; for(int j=0;j<(1<<i);j++)od|=e[j].size()&1;
		if(od||block(i)!=1)end(i-1);
	} end(20);
	return 0;
}
```

---

## 作者：duyi (赞：8)

## CF1361C Johnny and Megan's Necklace

因为答案只可能是$0\dots 20$，考虑**从大到小**枚举答案，判断是否可行。

设当前要判断的答案为$i$。那么，所有我们连接的两个数$u,v$，必须满足$u\operatorname{and}(2^i-1)=v\operatorname{and}(2^i-1)$，也就是二进制下后$i$位相同，否则异或后的$\text{lowbit}$肯定小于$2^i$，不符合要判断的条件。考虑把满足条件的点两两连边，这样边数高达$O(n^2)$。一个经典的优化套路是，对每个$j\in[0,2^i)$建一个**虚点**。然后从每个$u$向$u\operatorname{and}(2^i-1)$连无向边。

然后判断这张图是否是欧拉图（也就是是否存在一条**回路**，经过图上每条**边**恰好一次）即可。

时间复杂度$O((n+a)\log a)$。

参考代码：

```cpp
//problem:CF1361C
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int MAXN=5e5;
const int MAXS=1<<20;
int n,a[MAXN+5],b[MAXN+5],deg[MAXS+5];

struct EDGE{int nxt,to;}edge[MAXN*4+5];
int head[MAXN+MAXS+10],tot;
inline void add_edge(int u,int v){edge[++tot].nxt=head[u],edge[tot].to=v,head[u]=tot;}

int sta[MAXN*4+5],top;
bool vis[MAXN*4+5];
void dfs(int u){
	for(int& i=head[u];i;i=edge[i].nxt){
		if(!vis[i]){
			vis[i]=vis[i^1]=1;
			int v=edge[i].to;
			dfs(v);
			sta[++top]=v;
		}
	}
}

int main() {
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i]>>b[i];
	}
	for(int i=20;i>=1;--i){
		int S=(1<<i)-1;
		for(int j=0;j<=S;++j)deg[j]=0;
		for(int j=1;j<=n;++j){
			deg[a[j]&S]++;
			deg[b[j]&S]++;
		}
		bool fail=false;
		for(int j=0;j<=S;++j)if(deg[j]&1){fail=true;break;}
		if(fail)continue;
		for(int i=1;i<=tot;++i)vis[i]=0;
		tot=1;
		for(int j=1;j<=S+n+1;++j)head[j]=0;
		for(int j=1;j<=n;++j){
			add_edge(j,(a[j]&S)+n+1);add_edge((a[j]&S)+n+1,j);
			add_edge(j,(b[j]&S)+n+1);add_edge((b[j]&S)+n+1,j);
		}
		top=0;
		dfs(1);
		int cnt=0;
		for(int j=1;j<=top;++j)cnt+=(sta[j]<=n);
		if(cnt!=n)continue;
		cout<<i<<endl;
		for(int j=1;j<=top;++j){
			if(sta[j]<=n){
				assert(j<top && sta[j+1]>n);
				int s=(sta[j+1]-(n+1));
				int id=sta[j];
				assert((a[id]&S)==s || (b[id]&S)==s);
				if((a[id]&S)==s){
					cout<<id*2<<" "<<id*2-1<<" ";
				}
				else{
					cout<<id*2-1<<" "<<id*2<<" ";
				}
			}
		}
		cout<<endl;
		return 0;
	}
	cout<<0<<endl;
	for(int i=1;i<=n*2;++i)cout<<i<<" ";cout<<endl;
	return 0;
}
```



---

## 作者：chenxia25 (赞：3)

> ### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/CF1361C) & [CF题目页面传送门](https://codeforces.com/contest/1361/problem/C)

> 给定$n$个珠子无序对，第$i$个珠子对的权值为$(a_i,b_i)$，每对的两个珠子已经连了起来。要求再连$n$条线，使$2n$个珠子连成简单环，其中对于每个珠子对，连接它的两条线分别与两个珠子相连。每条再连的线的权值为使得$2^x$能被它所连的两个珠子的权值的异或和整除的最大自然数$x$。你需要最大化再连的$n$条线的最小权值，并给出此时的连接方案。

> $n\in\left[1,5\times10^5\right],a_i,b_i\in\left[0,2^{20}\right)$。

首先注意到，答案最多只有$21$种（$0\sim 20$），我们可以从大到小贪心地枚举答案，转最优化为判定。

考虑对于$v\in[0,20]$，如何判定答案是否$\geq v$。注意到，要求所有再连的边的最小权值$\geq v$，就是所有再连的边的权值都要$\geq v$。设连的两个珠子权值分别为$x,y$，那么即$2^v\mid x\oplus y$，即$x\bmod 2^v=y\bmod 2^v$。不难想到，可以将每个珠子的权值当作$(a/b)_i\bmod 2^v$，这样有解当且仅当可以使得每条再连的线的两端权值相等。

这样就不难想到图论了。考虑在每个珠子对之间连边，这样最终肯定要每条边都走一遍，并回到自己，不难想到欧拉回路。那么如何体现“再连的线的两端权值相等”这个条件呢？我们把每个珠子映射到它的权值再建图即可，这样每两条相邻走过的边的交点，表示这两个珠子对连接的地方的左右两端的权值是这个同一个数。

这样，判一下，如果有欧拉回路，DFS的时候就逆序记录经过的边们连接的珠子对，最后将这个大小为$2n$的答案序列`reverse`即可。

时间复杂度$\mathrm O((n+v)\log v)$，其中$v$是值域大小，$\log$是枚举答案。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
const int N=500000,A_I=1<<20;
int n;
int a[N+1],b[N+1];
vector<pair<int,pair<int,int> > > nei[A_I];
vector<int> reg[A_I];
vector<bool> ban[A_I];
int now[A_I];//当前弧 
vector<int> pa;
void dfs(int x=a[1]){//跑欧拉回路 
//	cout<<x<<" ";
	for(int &i=now[x];i<nei[x].size();i++)if(!ban[x][i]){
		int y=nei[x][i].X,y1=nei[x][i].Y.X,y2=nei[x][i].Y.Y;
		ban[x][i]=ban[y][reg[x][i]]=true;
		dfs(y);
		pa.pb(y2);pa.pb(y1);//逆序压入 
	}
}
void sol(int x){
	for(int i=1;i<=n;i++)a[i]%=1<<x,b[i]%=1<<x;
	for(int i=0;i<1<<x;i++)nei[i].clear(),reg[i].clear(),ban[i].clear();
	for(int i=1;i<=n;i++){//建图 
		if(a[i]==b[i]){
			nei[a[i]].pb(mp(a[i],mp(2*i-1,2*i)));nei[a[i]].pb(mp(a[i],mp(2*i,2*i-1)));
			reg[a[i]].pb(nei[a[i]].size()-1);reg[a[i]].pb(nei[a[i]].size()-2);
		}
		else{
			nei[a[i]].pb(mp(b[i],mp(2*i-1,2*i)));nei[b[i]].pb(mp(a[i],mp(2*i,2*i-1)));
			reg[a[i]].pb(nei[b[i]].size()-1);reg[b[i]].pb(nei[a[i]].size()-1);
		}
		ban[a[i]].pb(false);ban[b[i]].pb(false);
	}
	for(int i=0;i<1<<x;i++)if(nei[i].size()%2)return;//判欧拉回路 
	memset(now,0,sizeof(now));pa.clear();
	dfs(); 
//	puts("");
	if(pa.size()!=2*n)return;//图要连通 
	cout<<x<<"\n";
	for(int i=2*n-1;~i;i--)printf("%d ",pa[i]);//倒序 
	exit(0);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d%d",a+i,b+i);
	for(int i=20;;i--)sol(i);//从大到小枚举答案 
	return 0;
}
```

---

## 作者：陈刀仔 (赞：2)

弱化条件：削去不需要考虑的部分，放松题目限制，尽量找简单的方法做。

**看到是最小边权的最大值，为什么没有想到将最优化问题转换为存在性问题？？？？？**

我们显然在图上考虑这个问题，我们要在图上添加 $n$ 条边，缝合成一个环。

答案很少，只有 $20$ 以内，我们考虑枚举最小边权。

假设此时枚举到的答案是 $k$ ，那么一条边可以连接当且仅当其连接的两点权值大于等于 $k$ ，**大于等于可以向存在性变换，这里就是存在长度等于 $k$ 的公共后缀。**

权值除掉公共后缀以外的部分都不用管，这提示我们仅保留每一个点权值后 $k$ 位的部分。

**连边相当于拼接两个珠子对。**拼接区别于合并是因为它有顺序。

那么此时发现两对珠子能够拼接起来当且仅当拼接端的权值是相等的，**我们把相等的点缩成一个点**，一个合法的珠子对相当于一条原有边接上一个点，在加上另一条原有边。

**环即是点的回路，又是边的回路。当我们不一定要化边为点，因为欧拉回路就是解决这样一个问题。**现在我们相当于是找一条欧拉回路。

**然后千万要记得，欧拉回路需要当前弧优化！！！！！**



---

## 作者：shinkuu (赞：1)

首先看到要求最小值最大，考虑二分。但是发现答案值域为 $[0,20]$，直接从大到小枚举答案判断是否可行。

判断一个答案 $k$ 可行，即要求所有边权值 $\geq k$。容易发现，这只和点权的后 $k$ 位有关。将点权后 $k$ 位 $c_i$ 提取出来，则一条边 $(u,v)$ 可以被连上的条件为 $c_u=c_v$。

此时，我们要解决的问题就是，从一个点 $s$ 开始，是否有一种方案使得，走到 $u$ 时，如果有一条原有的边 $(u,v)$ 没走过则走这条边，否则走到一个点 $x$ 满足 $c_x=c_u$，最后回到 $s$。

直接在原来的边上跑是困难的，边数达到了 $O(n^2)$。考虑将每个点权建一个点，原图有边 $(u,v)$ 则在这张图中添加边 $(c_u,c_v)$。此时要求就变成了从一个点 $s$，遍历图的每一条边，最后回到 $s$。这是一个欧拉回路问题。使用 Hierholzer 算法解决。

具体实现方法就是不断 dfs，并当一个点出栈，即回溯时将其加入一个序列中，最后得到的序列就是欧拉回路的倒序。

实现细节不少。首先注意 dfs 时要加当前弧优化，否则复杂度会退化到 $O(n^2)$。还要特判 $ans=0$ 的情况。尤其注意常数优化：少用 memset，少记录无用信息，等等。

code：

```cpp
const int N=2e6+7,M=-1,inf=0x3f3f3f3f,mod=0;
int n,m,idx,c[N],d[N],deg[N],fa[N],siz[N],cur[N];
int tot,head[N];
bool vis[N];
struct node{
	int to,nxt,cw;
}e[N<<1];
vector<int> g,h[N];
map<pii,int> id;
il void add(int u,int v){
	e[++tot]={v,head[u]};
	head[u]=tot;
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
il void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)
		return;
	siz[y]+=siz[x];
	fa[x]=y;
}
void dfs(int u){
	for(int &i=cur[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(vis[(i+1)/2])
			continue;
		vis[(i+1)/2]=true;
		dfs(v);
	}
	g.eb(u);
}
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n){
		c[i*2-1]=read(),c[i*2]=read();
	}
	drep(k,20,1){
		rep(i,1,n*2){
			deg[d[i]]=head[d[i]]=0;
			vis[d[i]]=false;
			d[i]=c[i]&((1<<k)-1);
			fa[d[i]]=d[i];
		}
		tot=0;
		rep(i,1,n){
			int u=d[i*2-1],v=d[i*2];
			add(u,v),add(v,u);
			deg[u]++,deg[v]++;
		}
		rep(i,1,n){
			merge(d[i*2-1],d[i*2]);
		}
		int cnt=0,sum=0;
		rep(i,1,n*2){
			if(vis[d[i]])
				continue;
			int j=d[i];
			vis[j]=true;
			if(deg[j]&1)
				cnt++;
			sum+=fa[j]==j;
		}
		if(sum>1||cnt)
			continue;
		printf("%d\n",k);
		rep(i,1,n){
			int u=d[i*2-1],v=d[i*2];
			if(!id[Mp(u,v)])
				id[Mp(u,v)]=++idx;
			if(!id[Mp(v,u)])
				id[Mp(v,u)]=++idx;
			h[id[Mp(u,v)]].eb(i*2-1);
			h[id[Mp(v,u)]].eb(i*2);
		}
		rep(i,1,n*2){
			cur[d[i]]=head[d[i]];
			vis[d[i]]=false;
		}
		dfs(d[1]);
		reverse(g.begin(),g.end());
		mems(vis,false);
		for(int j=0;j<(int)g.size()-1;j++){
			int x=id[Mp(g[j],g[j+1])];
			int i=h[x].back();
			h[x].pop_back();
			while(vis[(i+1)/2]){
				i=h[x].back();
				h[x].pop_back();
			}
			vis[(i+1)/2]=true;
			if(i&1)
				printf("%d %d ",i,i+1);
			else 
				printf("%d %d ",i,i-1);
		}
		return;
	}
	puts("0");
	rep(i,1,n*2){
		printf("%d ",i);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1361C)

简单 $2500$。

## 思路

首先看到最小值最大，直接二分，显然是满足单调性的。

但是直接枚举也可以，因为 $\log a \le 20$。

然后考虑如何 $\rm check$。

首先我们把每个数都写成二进制的形式，不难发现从低往高数第 $mid$ 位及以后的位都是没用的。两个数能贴在一起当且仅当它们 $mid$ 位之前都相等。

也就是说，设 $a_i$ 为 $i$ 的权值，我们可以让 $a_i$ 对 $2^{mid}$ 取模，取模后相等的两个数可以贴在一起。

这样我们已经可以打出 $\mathcal O(n^2)$ 的暴力了，我们把 $(2i-1,2i)$ 设为一个二元组，绑在一起考虑，因为它们最开始就贴在一起，然后向能放在旁边的二元组连边。不难发现如果能跑出欧拉回路就有解。

考虑优化连边的过程，我们对每种权值建一个虚点，每次向这个虚点连边即可。

时间复杂度 $\mathcal O(n \log \log a)$。

## 代码

[提交记录](https://codeforces.com/problemset/submission/1361/212039139)

---

## 作者：tzc_wk (赞：1)

[Codeforces 题目传送门](https://codeforces.com/contest/1361/problem/C) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1361C)

~~u1s1 感觉这个题作为 D1C 还是蛮合适的……~~

首先不难发现答案不超过 $20$，所以可以直接暴力枚举答案并 `check` 答案是否合法，当然二分也是没问题的，转最优性问题为判定性问题。

考虑怎样判断一个答案 $k$ 是否合法，由于所有相连的线 $u,v$ 都有 $2^k\mid a_u\oplus a_v$，那么 $a_u\bmod 2^k=a_v\bmod 2^k$ 一定成立。因此我们可以将每个点的权值看作 $a_i\bmod 2^k$，我们要找出一个串珠子的方法使得每条线的两端权值相等。

我们考虑将此题转化为一个图论问题，对于已经连上线的两点 $a_i,b_i$，连一条 $a_i\bmod 2^k$ 与 $b_i\bmod 2^k$ 的无向边。不难想到欧拉回路。当我们经过 $a_i\bmod 2^k$ 与 $b_i\bmod 2^k$ 的边的时候相当于将珠子 $2i+1,2i+2$ 与刚才串好的线连在了一起。那么如何体现”每条新连的线两端权值相等“呢？不难发现，假设我们先访问了 $a_i\bmod 2^k\to b_i\bmod 2^k$，紧接着访问了 $a_j\bmod 2^k\to b_i\bmod 2^k$，那么必须有 $b_i\bmod 2^k=a_j\bmod 2^k$，这就天然地规定了它们的权值必须相等。因此只需检验建出来的图中是否存在欧拉回路即可。根据”每个点度数都是偶数，并且图须为连通图“即可检验。

找到最大的 $k$ 后还是按照上述方式建图并跑一遍欧拉回路即可找出方案。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=5e5;
const int MAXMSK=1<<20;
int n,a[MAXN+5],b[MAXN+5];
vector<int> nei[MAXMSK+5];
bool vis[MAXMSK+5];
void dfs(int x){
	if(vis[x]) return;vis[x]=1;
	for(int i=0;i<nei[x].size();i++) dfs(nei[x][i]);
}
int hd[MAXMSK+5],to[MAXN*2+5],nxt[MAXN*2+5],idu[MAXN*2+5],idv[MAXN*2+5],ec=1;
bool used[MAXN*2+5];
vector<int> ret;
void adde(int u,int v,int x,int y){
	to[++ec]=v;idu[ec]=x;idv[ec]=y;nxt[ec]=hd[u];hd[u]=ec;
}
void cir(int x){
	for(int &e=hd[x];e;e=nxt[e]) if(!used[e>>1]){
		used[e>>1]=1;int u=idu[e],v=idv[e];
		cir(to[e]);ret.pb(v);ret.pb(u);
	}
}
void end(int x){
	int lim=(1<<x)-1;
	for(int i=1;i<=n;i++){
		adde(a[i]&lim,b[i]&lim,i*2-1,i*2);
		adde(b[i]&lim,a[i]&lim,i*2,i*2-1);
	} cir(a[1]&lim);
	printf("%d\n",x);
	for(int u:ret) printf("%d ",u);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	for(int i=20;i;i--){
		int lim=(1<<i)-1;
		for(int j=0;j<=lim;j++) nei[j].clear(),vis[j]=0;
		for(int j=1;j<=n;j++){
			nei[a[j]&lim].pb(b[j]&lim);
			nei[b[j]&lim].pb(a[j]&lim);
		} bool flg=1,hav=0;
		for(int j=0;j<=lim;j++) if(nei[j].size()&1){flg=0;break;}
		for(int j=0;j<=lim;j++) if(nei[j].size()>=1&&!vis[j]){
			if(hav){flg=0;break;}hav=1;dfs(j);
		}
		if(flg){end(i);return 0;}
	} end(0);
	return 0;
}
```



---

## 作者：subcrip (赞：0)

看题解区清一色是欧拉回路，这里提供一个朴素的并查集做法。

考虑二分答案，假设当前答案是 $x$，那么所有低 $x$ 位相同的节点之间可以连边。所以开个桶存放每种低 $x$ 位的那些节点。

如果有一个桶里的节点个数是奇数，那必然不可能。否则，所有桶里都有偶数个点，我们可以把它们每两个凑一对连边，这样连完之后，加上原本的 $2i$ 和 $2i+1$ 的边，一定形成了若干个环。

接下来考虑如何把这若干个环合成一个环。显然，如果我们从两个环上各取一条边，并且满足这两条边的一共 $4$ 个节点低 $x$ 位都相同，那么可以把这两条边“拧”一下。形式化地说，假如有两条边 $x_1\leftrightarrow y_1$ 和 $x_2\leftrightarrow y_2$，则我们把这两条边改成 $x_1\leftrightarrow y_2$ 和 $x_2\leftrightarrow y_1$。这样就把两个环合成了一个。

所以用并查集维护连通块，对于每个桶里的每个点对，我们检查这个点对是否是否与桶里的上一个点对连通，如果不连通就把这两条边拧一下。最后，如果只剩一条环，就说明可行。并且，如果我们用一个数组记录一下每个点沿着新连的边到达的另外一个点，则同时也就求出了方案。

时间复杂度 $O(n\log\log U)$，$U$ 是值域。

Code:

```cpp
void solve() {
    constexpr int N = 1 << 20;

    read(int, n);
    vector<int> a(2 * n);
    for (int i = 0; i < n; ++i) {
        cin >> a[2 * i] >> a[2 * i + 1];
    }

    vector<vector<int>> bk(N);

    auto work = [&] (int x) -> optional<vector<int>> {
        bk.assign(N, {});
        quick_union qu(2 * n);
        for (int i = 0; i < n; ++i) {
            qu.merge(2 * i, 2 * i + 1);
        }
        for (int i = 0; i < 2 * n; ++i) {
            bk[((1 << x) - 1) & a[i]].emplace_back(i);
        }
        vector<int> ret(2 * n);
        for (int i = 0; i < N; ++i) {
            int m = bk[i].size();
            if (m % 2 == 1) {
                return nullopt;
            }
            for (int j = 0; j < m; j += 2) {
                qu.merge(bk[i][j], bk[i][j + 1]);
                ret[bk[i][j]] = bk[i][j + 1];
                ret[bk[i][j + 1]] = bk[i][j];
            }
        }
        for (int i = 0; i < N; ++i) {
            int m = bk[i].size();
            if (m <= 2) continue;
            int l = bk[i][0], r = bk[i][1];
            for (int j = 2; j < m; j += 2) {
                if (not qu.connected(l, bk[i][j])) {
                    ret[l] = bk[i][j];
                    ret[bk[i][j]] = l;
                    ret[r] = bk[i][j + 1];
                    ret[bk[i][j + 1]] = r;
                    qu.merge(l, bk[i][j]);
                    r = bk[i][j];
                }
            }
        }
        if (qu.query_size(0) == 2 * n) {
            return ret;
        } else {
            return nullopt;
        }
    };

    int l = 0, r = 20;
    while (l < r) {
        int mid = l + r + 1 >> 1;
        if (work(mid) != nullopt) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    cout << l << '\n';
    auto res = *work(l);
    int curr = 0;
    for (int i = 0; i < n; ++i) {
        cout << curr + 1 << ' ' << ((1 ^ curr) + 1) << ' ';
        curr = res[1 ^ curr];
    }
    cout << endl;
}
```

---

