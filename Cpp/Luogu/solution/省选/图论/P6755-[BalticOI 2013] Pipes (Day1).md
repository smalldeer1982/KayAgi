# [BalticOI 2013] Pipes (Day1)

## 题目描述

给定一个 $N$ 点 $M$ 边的无向图，**保证图连通**。现在每个点都有一定量的水，现在可以在一条边上进行操作：

- 让水流出：给定 $d$，假设长度为 $m$，流的时间为 $s$，那么总共失水速度为 $\dfrac{2dm^3}{s}$，这条边两边的每个点的失水速度为 $\dfrac{dm^3}{s}$。
- 让水流进：给定 $p$，假设长度为 $m$，流的时间为 $s$，那么总共得水速度为 $\dfrac{2pm^3}{s}$，这条边两边的每个点的得水速度为 $\dfrac{pm^3}{s}$。

现在给定这个图，和每个点的水量的变化速度，求每条边的水量的变化速度的构造方案。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le N \le 10^5$，$1 \le M \le 5 \times 10^5$，$-10^9 \le c_i \le 10^9$，如果有解且唯一解，每个答案在 $[-10^9,10^9]$ 的范围内。     
对于其中 $30\%$ 的数据，该图为一棵树。

#### 说明

翻译自 [BalticOI 2013 Day1 C Pipes](https://boi.cses.fi/files/boi2013_day1.pdf)。

## 样例 #1

### 输入

```
4 3
-1
1
-3
1
1 2
1 3
1 4```

### 输出

```
2
-6
2```

## 样例 #2

### 输入

```
4 5
1
2
1
2
1 2
2 3
3 4
4 1
1 3```

### 输出

```
0```

# 题解

## 作者：liuliucy (赞：9)

## 各种情况
首先，我们可以用边权表示出每个点的点权：
$$2a_i=\sum_j e_{i,j}$$
$ e_{i,j} $ 表示一条从 $i$ 到 $j$ 的边的边权。然后，我们便可以列出一个方程组：
$$\left\{\begin{matrix}
 \sum_j e_{1,j}=2a_1\\
 \sum_j e_{2,j}=2a_2\\...
 \\
\sum_j e_{n,j}=2a_n

\end{matrix}\right.$$
有 $n$ 个方程，$m$ 个未知数，~~我们用高斯消元暴力~~我们可以知道当 $m>n$ 时方程组有无数组解，图是联通的，所以只可能 $m=n-1$ 或者 $m=n$ ，当 $m=n-1$，这是一棵树，而 $m=n$ 时则是基环树。

我们分别考虑以下三种情况：

如图所示时：
![](https://cdn.luogu.com.cn/upload/image_hosting/pyzf0adb.png)

这显然是可以直接算的，因为 $a_1$ 点权的两倍就是 $1-2$ 的边权。

当是个环时：
![](https://cdn.luogu.com.cn/upload/image_hosting/h5z967r5.png)

我们可以列出方程组：
$$\left\{\begin{matrix}
 e_{1,2}+e_{1,3}=2a_1\\
 e_{2,3}+e_{1,2}=2a_2\\
e_{1,3}+e_{2,3}=2a_3
\end{matrix}\right.$$
我们将 $1$ 式减去 $2$ 式 加上 $3$ 式便可得到 $2e_{1,3}$ 的值，之后便可得到所有的边权。

而当环上有偶数个点时：
![](https://cdn.luogu.com.cn/upload/image_hosting/dzihvvya.png)

这也有无穷多组解，因为我们将 $e_{1,4}$ 加 $1$ ，$e_{1,2}$ 减 $1$，之后再将 $e_{2,3}$ 加 $1$，$e_{3,4}$ 减 $1$，我们发现这样也是成立的，但是却得到了不同的一组解，所以这样会出现无穷多组解。
## 算法
我们先拓扑排序，先处理掉链的情况，最后只剩下环，最后再处理环即可。
## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
struct xx{
	int x,id,nxt;
}e[1000001];
int head[1000001],cnt;
bool b[1000001];
void add(int x,int y,int id){
	e[++cnt].x=y;
	e[cnt].id=id;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
bool vis[1000001];
bool used[1000001];
int a[1000001],in[10000001];
int ans[10000001];
queue<int>q;
int n,m,aw,ct,f=1;
void dfs1(int x,int fa,int rt){
	if(fa!=-1&&rt==x){
		if(ct%2==0){
			printf("0");
			exit(0);
		}
		return;
	}
	aw+=f*a[x];
	f*=-1;
	ct++;
	for(int i=head[x];i!=-1;i=e[i].nxt){
		int y=e[i].x;
		if(y==fa)continue;
		if(in[y]<2)continue;
		if(b[y])continue;
		b[y]=1;
		dfs1(y,x,rt);
	}
}
void dfs2(int x,int fa,int rt){
	if(fa!=-1&&rt==x)return;
	for(int i=head[x];i!=-1;i=e[i].nxt){
		int y=e[i].x;
		if(y==fa)continue;
		if(in[y]<2)continue;
		if(b[y])continue;
		b[y]=1;
		aw=a[x]-aw;
		ans[e[i].id]=2*aw;
		dfs2(y,x,rt);
		
	}
}
signed main(){
	memset(head,0xff,sizeof(head));
	scanf("%d%d",&n,&m);
	if(m>n){
		putchar('0');
		return 0;
	}
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y,i);
		add(y,x,i);
		in[y]++;in[x]++;
	}
	for(int i=1;i<=n;i++)if(in[i]==1)q.push(i);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		if(used[x])continue;
		used[x]=1;
		for(int i=head[x];i!=-1;i=e[i].nxt){
			int y=e[i].x,id=e[i].id;
			if(vis[id])continue;
			ans[id]=2*a[x];
			a[y]-=a[x];
			vis[id]=1;
			in[y]--;
			if(in[y]==1){
				q.push(y);
			}
		}
	}
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;i++){
		if(b[i])continue;
		if(in[i]>=2){
			dfs1(i,-1,i);
			memset(b,0,sizeof(b));
			aw/=2;
			dfs2(i,-1,i);
		}
	}
	for(int i=1;i<=cnt/2;i++)printf("%d\n",ans[i]);
}
```


---

## 作者：xs_siqi (赞：7)

赛时思路：

首先看到这道题面无用信息太多了。我们把它简化一下。

对于题目中的 $\dfrac{2dm^3}{s}$ 与 $\dfrac{dm^3}{s}$，我们发现这其实是诈骗。所以我们把 $\dfrac{dm^3}{s}$ 消掉完全不影响题意。后面的 $\dfrac{pm^3}{s}$ 同理。

题目变为了：$n$ 个点，$m$ 条边（保证图联通），给定点权，点权是与其相连的边的权值总和的一半（保证每一条边边权为偶数），求一开始边权的方案数是否唯一，如果唯一，输出方案（保证有解）。

首先我们发现一个性质：对于只有一个解的情况，只要确定一条边，其它必然都能被确定。让我们来证明一下这个性质：

这条被确定的边两端必然连着两个点，而这两个点的点权我是知道的。

- 如果对于相连的两个点，点权均等于 $3$，则我对于相连的这两个点，每个点就会有三条边。我此次确定一条边，那么这两个点分别均有两个点没有确定。设我当前确定的边为 $x$，两点中的一点点权为 $p$。那么剩下两边边权之和是 $2p-x$，设对于剩下两边，有一边我权值取 $y$，最后一边的权值就是 $2p-x-y$，而 $y$ 是可以取任意值的，出现多种情况，不符合条件“仅有一个解”，因此这种情况不合法。

- 如果对于相连的两个点，点权有任意一个大于等于 $3$，与上述同理，不过多证明。

- 如果对于相连的两个点，点权有任意一个等于 $2$，剩余一个取任意值，那么对于点权为 $2$ 的边，因为我已知点权和边权，知二求二。我就必然可以确定这个点相连的两另外一条边的边权。具体地，我们不妨称这另外一条边叫边 $r$，若点权为 $p$，已知一条边为 $x$，那么边 $r$ 的权值就是 $2p-x$。在此之后，对于边 $r$ 它连着两个点，所以我们就可以一直按照这个证明循环下去。如果出现两个三条边的点（严谨点应该说是两个有两条边未确定的点，因为后续的时候会有一些点，它虽然度数为 $3$，但是有一两条边已经确定，所以可以确定最后一条边，度数更多同理），那么就是不合法的，违反已知条件，否则合法。

可见原命题正确。

那么接下来我们来思考，什么时候解是唯一的。

什么情况下我们能确定一条边以直接确定所有边呢？显然是树上情况。第一条边如何确定？我们找到一个度数为 $1$ 的点，对于它，它的边权显然就是它的点权乘二。

所以我们对树上情况拓扑即可。但是我没有使用拓扑（因为不会），我直接用队列存度数，每次将度数为 $1$ 的插入队列，然后一直做下去。

但是，存在一些情况是我们要用一条边去间接确定所有边的。例如环上情况。

把环上情况枚举了几次，发现这无法直接构造，很难找到规律。这时我们不能再草草推推了，可能需要更形式化的表达来寻找构造方案。由于图联通，且存在一个环，我们知道这是基环树。

在基环树上，对于其它不形成环的路径，我们可以像在树上一样处理。对于环，我们可以以以下方式处理：

不妨设点权为 $p_i$（已经去除了在环上以外的边（下面有解释）），边权为 $x_i$。

可能我这么说有点抽象，什么叫“除了在环上以外的边”？看下面一张图：

```
4
|
1--2--3
|     |
-------

```

像上面这张图，$1,2,3$ 构成了一个环，$4$ 是一个环外节点。

我们假设 $p_1=2,p_2=2,p_3=3,p_4=1$，我们知道点 $4$ 是一个度数为 $1$ 的点，那么 $1$ 点和 $4$ 点相连的边边权一定是 $2$。

这样，那么 $1$ 与 $2$ 相连的边和 $1$ 与 $3$ 相连的边的边权和就是 $1$。所以变成了 $p_1=1,p_2=2,p_3=3$。我们称这个叫做“除了在环上以外的边后的 $p_i$”，下面就简称“环上 $p_i$ ”了。有了这张图应该很好理解了吧。

对于环上 $p_i$，设点 $d_{i-1}$ 与点 $d_{i+1}$ 与点 $d_i$ 相连，根据题目已知，我们可以列出以下等式。

$$\dfrac{p_i}{2}=e_{d_{i-1},d_i}+e_{d_i,d_{i+1}}$$

当环上点是偶数时，我们将偶数个方程组融合（读者自行消元），剩余的最后两个等式分别是 

$$e_{n-1,n}-e_{n,1}=\sum_{i=2}^{\frac{n-2}{2}}p_{2i}-\sum_{i=1}^{\frac{n}{2}}p_{2i-1}$$

与

$$e_{n-1,n}-e_{n,1}=p_n$$

如果你解出来的跟我不一样也先别急，因为最后的两个方程可以有很多组，你稍微看一下形式是不是差不多就行了。我这里取 $n$ 为最后一组是为了美观。

这两个东西刚好消掉了，然后一条边都求不出来。

对于一个方程，不管你消的过程如何，方程的解是在原方程组就可以决定的。所以不管你如何消元它就是无限多组解的。

由此可见，边数为偶数是无限多组解的。

其实在考场上你也没必要消元，随便枚举一个发现它好像有无限多组解就差不多了。

那么奇数是什么情况呢？

读者请继续自己解决这个问题。解决完可以参考下面的最终方程：

$$e_{n,1}=\sum_{i=2}^{\frac{n}{2}}p_{2i}-\sum_{i=1}^{\frac{n}{2}}p_{2i-1}$$

那么我们就可以确定这一条边了，那么这个环就变成一条链了。链是树的一种，然后套用树上的做法即可。

最后还有一个东西没证明，那就是有多个环的情况（即 $n<m$）。

我们这个时候不需要奇偶性分类了，继续延续使用方程来解决这个问题。我们再把方程列一下，发现它变成了一个 $m$ 个未知数， $n$ 个等式的方程。我们知道，至少未知数的数量与等式的数量相等，才有可能解出唯一解。所以这种情况必然不止一种解，不用解下去了。

我们总结一下：对于树的情况，和存在一个环且环上点为奇数的情况下，有且仅有一组解。

这样我们就把性质找完了。树上如何实现我们已经知道了，接下来想环上如何实现。

我们先把环外面的杂七杂八不是环的东西沿用树的方式处理了，然后对于环，我们随便找个节点为 $1$ 节点，这个节点直接相连的点卫 $n$ 节点，然后反向遍历，在遍历的过程中把点权的 $p$ 值像上述操作一样累加即可。然后断环成链后，延续树的做法即可。

可惜赛时反向遍历有个小细节没处理好，只得了树上的分。

给出一种可行的实现如下：

```cpp
#include<bits/stdc++.h>
#define STOP {printf("0\n");return 0;}
using namespace std;
const int MN=1e6+5;
int h=1,t,n,m,du[MN],p[MN],b[MN],q[MN],ji,CT,k,p1,p2;
int F[MN],T[MN],N[MN],tot;
bool V[MN],V2[MN];
void A(int x,int y){
	T[++tot]=y;
	N[tot]=F[x];
	F[x]=tot;}//前向星
void C(){//树上做法
	while(h<=t){
	int u=q[h],tv=0,p1=0,co=0,CT=0;
	if(h==n)break;//当只剩下最后一个点就不需要遍历了
	h++,V[u]=1;
	for(int i=F[u];i;i=N[i]){
		if(!V[T[i]]){
			tv=T[i],p1=i;//找到了一个度数为 1 的点，把它加到队列里
			du[tv]--,du[u]--;//找到一条边，我们把与它相连的点的度数都减掉 1
			if(du[tv]==1)q[++t]=tv;}}
	if(p1&1)p1++;
	b[p1]=p[u]*2,b[p1-1]=p[u]*2;//这条边就是点权乘上 2。当然双向边都要标记啦
	p[u]-=b[p1]/2,p[tv]-=b[p1]/2;}}//之前遍历过的点当然要删除了
void P(){
	for(int i=2;i<=tot;i+=2)printf("%d\n",b[i]);}//链式前向星输出
void D(int u,int fa,int c){
	V2[u]=1,k++;
	for(int i=F[u];i;i=N[i])
		if(du[T[i]]==2&&T[i]!=fa){//只遍历度数为 2 的点，防止你遍历到环外面去
			if(V2[T[i]])return;
			if(u==p1&&CT==0)ji=i,p2=T[i];//发现这条边连的点是环上的，钦定它为 n 节点
			CT+=p[T[i]]*((c&1)==1?-1:1);//计算 sigma p 的累加
			D(T[i],u,c^1);}}
int main(){
	scanf("%d%d",&n,&m);
	if(m+1!=n&&m!=n)STOP
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int x,y,i=1;i<=m;i++)
		scanf("%d%d",&x,&y),du[x]++,du[y]++,
		A(x,y),A(y,x);
	for(int i=1;i<=n;i++)if(du[i]==1)q[++t]=i;
	C();
	if(h==n)P();
	else if(n==m){
		for(int i=1;i<=n;i++)k+=(!V[i]);//看看环上有几条边
		if(!(k%2))STOP
		for(int i=1;i<=n;i++)
			if(!V[i]){p1=i;D(i,0,0);break;}
		if(ji&1)ji++;
		CT+=p[p1],b[ji]=b[ji-1]=CT;
		p[p1]-=b[ji]/2,p[p2]-=b[ji]/2;//因为环上断掉这条边，对于每个点的贡献就是二分之一了
		du[p1]--,du[p2]--,q[++t]=p1,q[++t]=p2,V[p1]=V[p2]=1;
		C(),P();}
	else STOP//多个环的情况
	return 0;}
```


---

## 作者：Mr_H2T (赞：4)

# P6755 Pipes 题解


upd:修复错误，精简代码，补充注释

---

~~我们模拟赛题~~

---

## 题目大意

题目等价于：

给定一个无自环重边的无向连通图，边权均为偶数，点权等于与其相连的边权之和的一半。 现给定每个点的点权以及边的连接情况，试求解每条边的边权。

## 题目分析

相当于求解一个 $m$ 元含 $n$ 条方程的方程组。

容易想到高斯消元，效率为 $O(n^3)$ ，显然过不了(~~考试时我的写法~~)

由于原图连通，故至少含有 $n-1$ 条边，即 $m>n-1$

- 当 $m>n$ 时，由于至少需要 $m$ 条方程才可能解出唯一解，故必有多解，输出 $0$ 。

- 当 $m<n\Leftrightarrow m=n-1$ 时，原图为一颗树。由于叶子结点只有一条边与之相连，而对于其他节点当其所有子树与之相连的边权以及其自身点权都一直时，其连向父节点的边权也可求出。
	
	则对树进行遍历，从叶子节点开始往上回溯，即可求出所有边权。

- 当 $m=n$ 时，原图为一颗基环树。对于非环部分，可以同树一样求解；对于环上的部分，可以通过线性求解若干条方程解决。

综上，可以在线性复杂度内解决问题，复杂度为（似乎） $O(n+m)$ .

## 处理细节

对于求环上边权的部分，可以通过如下步骤求解：

**假设**环上节点编号分别为 $1,2,\dots,k$.

我们设 $tpv_i$ 表示当前节点不在环上的边权之和，设两条环上边分别为 $x_i$ 与 $x_{i+1}$ （首尾需特判, $x_{k+1}=x_1$ ），该点点权为 $a_i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/thz0bbkq.png)

则有：

$$tpv_i+x_i+x_{i+1}=2a_i$$

$$x_i+x_{i+1}=2a_i-tpv_i$$

将 $2a_i-tpv_i$ 记作 $a'_i$ ,

而能否得到答案，还与环长的奇偶性有关。

当我们计算 

$$a'_1-a'_2+a'_3-\dots=x_1+x_2-x_2-x_3+x_3+x_4\dots$$

时，可能会将所有 $x$ 消完，也可能剩下一个未知量。

- 当环的路径数为偶数时，沿环一次计算结果为 
	$$x_1+x_2-x_2-x_3\dots-x_k-x_1=0$$
  	则我们无法解出环上的边权。
    
- 当环的路径数为奇数时，结果为
	$$x_1+x_2-x_2-x_3\dots-x_{k-1}-x_k+x_k+x_1=2x_1$$
  	则此时可以解出 $x_1$ ，并由此解出 $x_2,x_3,\dots,x_k$ 。

所以，对于环的长度，我们需要进行一定的特判，以此得到正确答案。

## 参考代码

我使用**拓扑排序**的方法对树进行遍历，每次加入度为 $1$ 的点。遍历完后如果还有节点没被访问，说明剩下的均为环，则按照上面步骤处理。

```cpp
#include <bits/stdc++.h>
#define rint register int
#define fu(i, a, b, d, c) for (rint i = a; i <= (b) && c; i += d)
#define fd(i, a, b, d, c) for (rint i = a; i >= (b) && c; i -= d)
using namespace std;
inline int read()
{
    char c = 0, f = 1;
    int num = 0;
    while (c < '0' || c > '9' && c != '-')
        ((c = getchar()) == '-') && (f = -f);
    while (c >= '0' && c <= '9')
        num = (num << 1) + (num << 3) + (c ^ 48), c = getchar();
    return num * f;
}
const int MAXN = 100050, MAXM = 500050;
int n, m;
int head[MAXN], nxt[MAXM], to[MAXM], cnt, id[MAXM];
void add(int u, int v, int i) { nxt[++cnt] = head[u], head[u] = cnt, to[cnt] = v, id[cnt] = i; }
int a[MAXN], d[MAXN], tpv[MAXN], vis[MAXN], vised, ans[MAXM], gonex[MAXN];
queue<int> q;
signed main()
{
    n = read(), m = read();
    if (n < m)
        return printf("0") & 0;
    fu(i, 1, n, 1, 1) a[i] = read();
    fu(i, 1, m, 1, 1)
    {
        int u = read(), v = read();
        add(u, v, i), add(v, u, i);
        //度数加一
        d[u]++, d[v]++;
    }
    fu(i, 1, n, 1, 1) if (d[i] == 1) q.push(i); //度为 1 节点入队
    while (!q.empty())    //树上计算
    {
        int now = q.front();
        q.pop();
        vis[now] = 1, vised++;
        for (int i = head[now]; i; i = nxt[i])
            if (!vis[to[i]])
            {
                //ans 表示答案数组，pv 表示连向子树的边权
                ans[id[i]] = 2 * a[now] - tpv[now]; //计算连向父亲的边权
                tpv[to[i]] += ans[id[i]];
                d[to[i]]--;
                if (d[to[i]] == 1)
                    q.push(to[i]); //新点入队
            }
    }
    if (vised < n) //存在环
    {
        if (!((n - vised) & 1)) //环长为偶数，直接输出 0
            return printf("0") & 0;
        int cur = 0, sum = 0, sym = 1, st = 0, tmp;
        //cur 为当前节点，sum 为点权和， sym为符号(依次交替)，st为起点
        fu(i, 1, n, 1, 1) if (!vis[i])
        {
            st = cur = i;
            a[i] = 2 * a[i] - tpv[i]; //计算 a'
        }
        while (!vis[cur])
        {
            bool tost = 0, flag = 0;//tost = to start 是否能到达起点; flag 记录是否是环尾
            int stg = 0;
            vis[cur] = 1;
            sum += a[cur] * sym;
            sym = -sym;
            for (int i = head[cur]; i; i = nxt[i])
            {
                if (to[i] == st) //这里处理是否是 1.起点连出的 2.环尾连入起点的
                    tost = 1, stg = i;
                if (!vis[to[i]])
                {
                    flag = 1;
                    gonex[cur] = i, cur = to[i];
                    //gonex 表示环上下一步走的边
                    break;
                }
            }
            if (!flag && tost) //是否是环尾
                gonex[cur] = stg;
        }
        ans[id[gonex[cur]]] = sum / 2; //计算 环尾-起点 边权
        tmp = ans[id[gonex[cur]]];     //tmp 记录上一条边，a[cur]-tmp 即为连接cur的另一条边的边权
        cur = st;                      //cur指向起点
        do
        {
            ans[id[gonex[cur]]] = a[cur] - tmp;
            tmp = ans[id[gonex[cur]]]; //更新tmp
            cur = to[gonex[cur]];
        } while (cur != st);
    }
    fu(i, 1, m, 1, 1) printf("%d\n", ans[i]);
}

```


---

