# Bichromization

## 题目描述

[problemUrl]: https://atcoder.jp/contests/keyence2020/tasks/keyence2020_e

$ N $ 頂点 $ M $ 辺の連結な無向グラフがあります。 このグラフの辺 $ i $ ($ 1\ \leq\ i\ \leq\ M $) は頂点 $ U_i $ と頂点 $ V_i $ を双方向に結んでいます。 また、$ N $ 個の整数 $ D_1,\ D_2,\ ...,\ D_N $ が与えられます。

このグラフの各頂点に白または黒の色を割り当て、さらに 各辺に $ 1 $ 以上 $ 10^9 $ 以下の整数の重みを割り当てる方法であって、以下の条件を満たすものが存在するかどうか判定してください。 さらに、存在する場合、そのような割り当てをひとつ求めてください。

- 白および黒が割り当てられた頂点がそれぞれ少なくとも $ 1 $ 個以上存在する。
- 各頂点 $ v $ ($ 1\ \leq\ v\ \leq\ N $) に対して以下の条件が成り立つ。
  - 頂点 $ v $ からグラフの辺を通って頂点 $ v $ と異なる色が割り当てられた頂点に移動する際にかかる最小のコストはちょうど $ D_v $ である。

なお、グラフ上の移動にかかるコストとは、 移動の際に通る辺の重みの和のことです。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100,000 $
- $ 1\ \leq\ M\ \leq\ 200,000 $
- $ 1\ \leq\ D_i\ \leq\ 10^9 $
- $ 1\ \leq\ U_i,\ V_i\ \leq\ N $
- 与えられるグラフは連結であり、自己ループや多重辺を持たない。
- 入力値はすべて整数である。

### Sample Explanation 1

出力例のように色と重みを割り当てた場合、たとえば頂点 $ 5 $ からグラフの辺を通って頂点 $ 5 $ と異なる色が割り当てられた頂点に最小のコストで移動するには、 頂点 $ 5 $ $ \to $ 頂点 $ 4 $ $ \to $ 頂点 $ 2 $ と移動すればよく、この移動のコストは $ 7 $ となるので、条件を満たします。 他の頂点についても条件を満たすことが確かめられます。

## 样例 #1

### 输入

```
5 5
3 4 3 5 7
1 2
1 3
3 2
4 2
4 5```

### 输出

```
BWWBB
4
3
1
5
2```

## 样例 #2

### 输入

```
5 7
1 2 3 4 5
1 2
1 3
1 4
2 3
2 5
3 5
4 5```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 6
1 1 1 1
1 2
1 3
1 4
2 3
2 4
3 4```

### 输出

```
BBBW
1
1
1
2
1
1```

# 题解

## 作者：Natori (赞：1)

个人感觉这道构造题比较有意思。

# 分析

既然是构造题，就先考虑构造方案。

题目中提到**最短路**，分析这个关键词，发现对于原图，一定存在一个**最短路森林**，因此能用这个最短路森林来满足题目中所给的限制，不在最短路森林中的边可以将边权直接设为题中的边权上限 $10^9$，也就是 $+ \infty$。

考虑用父亲表示法存储这个最短路森林。

那么对于原图中的一条边 $(u,v)$：

- 如果 $D[u]=D[v]$，并且有一个点尚未被染色，那么我们就让这两个点的颜色互不相同，并让这条边的边权等于 $D[u]$。

- 否则，如果 $D[u]>D[v]$，并让 $v$ 做 $u$ 的父亲，并让 $u$、$v$ 同色，边权设为 $D[u]-D[v]$。当然，若 $D[u]<D[v]$，直接交换 $u$、$v$ 即可。

当然点的颜色可以用 $1$ 和 $-1$ 来表示```白```和```黑```，这个不必赘述。

不难发现如果最后所有的点都有颜色，那么这一定是一组合法的方案，否则一定不存在合法方案。

# 代码

## 变量解释

- $n$、$m$、$D$ 题中变量

- $p_i$ 用于排序后顺序处理的数组，见代码

- $fa_i$ 点 $i$ 在最短路森林中的父亲（最短路森林使用父亲表示法）

- $color_i$ 原图中点 $i$ 被染上的颜色，只有 $1$、$-1$ 两个值

- $edgeid_i$ 用于存储边与点的关联，具体见代码

- $w_i$ 边 $i$ 的边权

## code

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){
	int f=1,x=0;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=x*10+c-'0';
		c=getchar();
	}
	return f*x;
}
inline void write(int x){
	if(x<0)x=-x,putchar('-');
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
inline void swap(int &x,int &y){
	x^=y^=x^=y;
}
const int N=1e5+10,M=2e5+10;
int n,m,D[N];
int p[N],fa[N],color[N];
int edge_id[N],w[M];
bool cmp(int x,int y){
	return D[x]<D[y];
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		p[i]=i;
		D[i]=read();
	}
	sort(p+1,p+1+n,cmp);
	for(int i=1,u,v;i<=m;i++){
		u=read(),v=read();
		if(D[u]==D[v]){
			if(!color[u]&&!color[v])
				color[u]=1;
			if(!color[u])
				color[u]=-color[v];
			if(!color[v])
				color[v]=-color[u];
			if(color[u]==-color[v])
				w[i]=D[u];
		}
		else{
			if(D[u]<D[v])
				swap(u,v);
			fa[u]=v;
			edge_id[u]=i;
		}
	}
	for(int i=1,x;i<=n;i++){
		x=p[i];
		if(!color[x]){
			if(!fa[x]){
				printf("-1");
				return 0;
			}
			color[x]=color[fa[x]];
			w[edge_id[x]]=D[x]-D[fa[x]];
		}
	}
	for(int i=1;i<=n;i++)
		putchar(color[i]==1?'B':'W');
	for(int i=1;i<=m;i++)
		putchar('\n'),write(w[i]?w[i]:1e9);
	return 0;
}
```

添加了对变量的解释，希望能对大家有帮助$\text{qwq}$

---

## 作者：谁是鸽王 (赞：0)

## 【题解】Bichromization(构造)

[咕咕咕](https://www.luogu.com.cn/problem/AT5751)

删边操作直接令其=1e9就好了，图的构造肯定先想想直接构造成树怎么做，我们直接令需要满足$D_i$的条件的那些最短路就=一条边。那么直接弄出一颗WB相间的森林即可，并且令父边=$D_i$。

但是每棵树的根节点没有父边啊！仔细思考发现，找到一个连接两个相等的$D$的并令其中一个为根即可。这样一条父边满足了两个$D_i$的条件的限制。

充分性是显然的，下证必要性

能够如上构造方案的充要条件是存在一条两端D相等的边。

这其实是两个条件，点和边。

先证最小的那条需要满足条件的路径的两端的D相同，不然一定有一个无法满足D的条件。设这条路径长度为len。

再证这条路径经过的点数=2，这也是显然的，因为如果>2，中间的一个点是无法满足条件的，因为这条路径两端是一W一B，一定有一个使得他的最短路<len，那么他永远无法满足条件。

具体实现直接bfs就好了。

```cpp
//@winlere
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;  typedef long long ll;
inline int qr(){
	int ret=0,f=0,c=getchar();
	while(!isdigit(c)) f|=c==45,c=getchar();
	while( isdigit(c)) ret=ret*10+c-48,c=getchar();
	return f?-ret:ret;
}
const int maxn=1e5+5;
const int inf=1e9;
struct E{
	int to,nx;
}e[maxn<<2];
int head[maxn],ans[maxn<<1],usd[maxn],n,m,cnt,D[maxn];
char col[maxn];
void add(int fr, int to){
	static int cnt=1;
	e[++cnt]=(E){to,head[fr]}; head[fr]=cnt;
	e[++cnt]=(E){fr,head[to]}; head[to]=cnt;
}
queue< int > q;

int main(){
	n=qr(); m=qr();
	for(int t=1;t<=n;++t)D[t]=qr();
	for(int t=1,a,b;t<=m;++t){
		a=qr(),b=qr(),add(a,b);
		if(D[a]==D[b]&&!col[a]&&!col[b]) q.push(a),q.push(b),col[a]='W',col[b]='B',ans[t]=D[a];
	}
	while(q.size()){
		int now=q.front(); q.pop();
		for(int t=head[now];t;t=e[t].nx)
			if(!col[e[t].to]&&D[e[t].to]>=D[now])
				col[e[t].to]="WB"[col[now]=='W'],ans[t>>1]=D[e[t].to],q.push(e[t].to);
	}
	for(int t=1;t<=n;++t)
		if(col[t]==0)
			return puts("-1"),0;
	puts(col+1);
	for(int t=1;t<=m;++t)
		printf("%d\n",ans[t]?ans[t]:inf);
	return 0;
}

```



---

