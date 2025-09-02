# Furukawa Nagisa's Tree

## 题目背景

有一天冈崎朋也和送给古河渚一棵树作为渚的生日礼物。（因为渚的生日是 12.24 啊~）。这是一棵奇奇怪怪的树，每一个节点都有一个权值 $v_i$。现在渚和朋也想在这棵树上玩一个游戏。


设 $ (s,e) $ 为从节点  $s$ 到节点 $e$ 的路径，我们可以写下路径 $ (s,e) $ 上的节点值序列，并将此序列表示为 $ S(s,e) $。  
可爱的渚这样定义了一个序列的权值： $G(S(s,e)) $。假设这个序列是 $ z_{0},z_{1}...z_{l-1} $，此处 $ l $ 是序列长度，定义 $ G(S(s,e))=z_{0}\times k^{0}+z_{1}\times k^{1} + \cdots + z_{l-1} \times k^{l-1} $。  
如果这条序列满足 $G(S(s, e)) \equiv x \pmod y$，那么这条路径 $ (s,e) $ 属于古河渚，反之属于冈崎朋也。


渚觉得计算谁拥有更多的路径实在是太简单了，所以她想要尝试一些难一点的。渚认为如果路径 $ (p_{1},p_{2}) $ 和 $ (p_{2},p_{3}) $ 属于她，那么$ (p_{1},p_{3}) $ 的路径也会属于她。同理，如果路径 $ (p_{1},p_{2}) $ 和 $ (p_{2},p_{3}) $ 属于朋也，那么路径 $ (p_{1},p_{3}) $ 也属于朋也。但是实际上，渚的这一结论并不是一直都是正确的。渚现在想知道有多少三元组 $ (p_{1},p_{2},p_{3}) $ 满足她的结论，这就是你的任务啦！


翻译者：永远喜欢 Furukawa Nagisa 的 zcysky。

## 题目描述

One day, Okazaki Tomoya has bought a tree for Furukawa Nagisa's birthday. The tree is so strange that every node of the tree has a value. The value of the $ i $ -th node is $ v_{i} $ . Now Furukawa Nagisa and Okazaki Tomoya want to play a game on the tree.

Let $ (s,e) $ be the path from node $ s $ to node $ e $ , we can write down the sequence of the values of nodes on path $ (s,e) $ , and denote this sequence as $ S(s,e) $ . We define the value of the sequence $ G(S(s,e)) $ as follows. Suppose that the sequence is $ z_{0},z_{1}...z_{l-1} $ , where $ l $ is the length of the sequence. We define $ G(S(s,e))=z_{0}×k^{0}+z_{1}×k^{1}+...+z_{l-1}×k^{l-1} $ . If the path $ (s,e) $ satisfies ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF434E/90c086b3cd66d72f064774200cc642323d3ee403.png), then the path $ (s,e) $ belongs to Furukawa Nagisa, otherwise it belongs to Okazaki Tomoya.

Calculating who has more paths is too easy, so they want to play something more difficult. Furukawa Nagisa thinks that if paths $ (p_{1},p_{2}) $ and $ (p_{2},p_{3}) $ belong to her, then path $ (p_{1},p_{3}) $ belongs to her as well. Also, she thinks that if paths $ (p_{1},p_{2}) $ and $ (p_{2},p_{3}) $ belong to Okazaki Tomoya, then path $ (p_{1},p_{3}) $ belongs to Okazaki Tomoya as well. But in fact, this conclusion isn't always right. So now Furukawa Nagisa wants to know how many triplets $ (p_{1},p_{2},p_{3}) $ are correct for the conclusion, and this is your task.

## 样例 #1

### 输入

```
1 2 1 0
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3 5 2 1
4 3 1
1 2
2 3
```

### 输出

```
14
```

## 样例 #3

### 输入

```
8 13 8 12
0 12 7 4 12 0 8 12
1 8
8 4
4 6
6 2
2 3
8 5
2 7
```

### 输出

```
341
```

# 题解

## 作者：Styx (赞：14)

在这之前先叨叨一句：我是因为这题是绿题才进来的QAQ   
![](https://cdn.luogu.com.cn/upload/pic/30696.png)  
本来以为是到难得水的E题，结果推了一波结论发现事情并不简单……  
我的天，点分治是绿题qwq？？？果然洛谷大佬辈出啊qwq


先简述一下题意：  
给出一棵树，树上各点都有点权。  
定义$S(s,t)$ 为树上$s\rightarrow t$的简单路径的序列。   
设$s$位置的点**点权**为$z_0$，他到$t$的路径上的下一个点点权为$z_1$，以此类推……再设一下这条路径的长度为$l$。  
然后定义$G(S(s,t))={z_0}*k^{0}+{z_1}*k^{1}+{z_2}*k^{2}+...+{z_{l-1}}*k^{l-1}$。  
如果一条路径满足$G(S(s,t))\equiv x(mod y)$ 那么这条边就是好边，反之如果不满足，这就是条坏边。    
定义好三元组$(x,y,z)$为$(x,y),(y,z),(x,z)$**都是**好边或坏边的三元组。   
求这棵树上有多少对好三元组？（三元组中的点可以重复）  
保证y是质数

这题非常的绕……  
所以，首先我们先不考虑好边坏边怎么在时限内求，先把怎么判断三元组弄清楚  
思考一下，很显然针对三元组来说，只会有这八种情况(0是坏边,1是好边)    
![](https://cdn.luogu.com.cn/upload/pic/30701.png)  
首先先考虑直接判断好三元组，你会发现，我们必须要知道三条边的信息才能判断，反正我比较菜这个东西我是想不到$O(nlogn)$的做法，所以要在思考一下别的方法，我们再看坏三元组的特征  
坏三元组和好三元组的区别显然是有点连着一条好边和一条坏边，如下图红的点 
![](https://cdn.luogu.com.cn/upload/pic/30706.png)  

那么统计一下，假设好的入边为$in_1$，坏的为$in_0$，同样，假设好的出边为$out_1$，坏的为$out_0$，在一番数数之后，我们得出图中各类点连得边的数量为
>in0 out1 2  
in1 out0 2  
in1 in0 4  
out1 out0 4  

因为有两个点，所以每个点的贡献为1/2   
即一个点会产生$in_0*in_1*2+out0*out1*2+in0*out1+in1*out0$个坏三元组  
因为一个坏三元组里有两个这样的点，所以答案要除二  
这样我们就把坏三元组的个数弄到了一个点上，这里的复杂度降到了$O(n)$
显然根据容斥的思想减掉坏三元组就是好三元组的数量

好的，接着开始接过之前的话题——怎么在时限内求出一个点的$in_1$、$in_0$、$out_1$、$out_0$  
因为三元组中的点可以重复，所以每个点都有$n$条出边，$n$条入边。  
所以$in_0=n-in_1,out_0=n-out_1$   
至于$in_1$、$out_1$  
这个是可以用点分治搞得  
好的先进入数论环节  
首先在点分的时候推两个距离，$vu=(prevu*k+a[now])$表示从下到上的距离1,$vd=(prevd+a[now]*k^{deep})$表示从上到下的距离2   
![](https://cdn.luogu.com.cn/upload/pic/30708.png)   
那么显然当一条边是好边的时候存在：  
$vu+vd*k^{len[vu]} \equiv x(mod y)$  
感觉$len[vu]$这个东西比较尴尬，我们移下项  
$vd \equiv (x-vu)/k^{len[vu]} (mod y)$   
其中右项就可以边dfs边处理了，相当于减一下再乘个逆元，逆元表可以和幂次表一起打，反正y一定是质数的话一趟费马小定理就可以了。
那么只要存在$vd \equiv (x-vu)/k^{len[vu]} (mod y)$ 就可以组成一条好边  
我们可以把所有得到的vd和右边这个值全部sort一下，然后尺取求一下相等的对数，反正就基本能点分出来$in_1$、$out_1$了……

之后就按上面的方法计算答案了，总三元组个数为$n^3$,答案就是$n^3-ans/2$  

代码如下：
```cpp
#include<map>
#include<set>
#include<queue>
#include<cmath>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

long long cnt,vis[100010],fa[100010],sz[100010],in0[100010],in1[100010],out0[100010],out1[100010],tm[100010],inv[100010],a[100010],x,y,k,n,ans;
vector<int> g[100010];

struct point
{
	long long val,id;
} tmp1[100010],tmp2[100010];

int cmp(point a,point b)
{
	return a.val<b.val;
}

long long kasumi(long long a,long long b)
{
	long long ans=1;
	while(b)
	{
		if(b&1)
		{
			ans=ans*a%y;
		}
		a=a*a%y;
		b>>=1;
	}
	return ans;
}

int get_sz(int now,int f)
{
	sz[now]=1;
	fa[now]=f;
	for(int i=0; i<g[now].size(); i++)
	{
		if(g[now][i]==f||vis[g[now][i]]) continue;
		get_sz(g[now][i],now);
		sz[now]+=sz[g[now][i]];
	}
}

int get_zx(int now,int f)
{
	if(sz[now]==1) return now;
	int maxson=-1,son;
	for(int i=0; i<g[now].size(); i++)
	{
		if(g[now][i]==f||vis[g[now][i]]) continue;
		if(maxson<sz[g[now][i]])
		{
			maxson=sz[g[now][i]];
			son=g[now][i];
		}
	}
	int zx=get_zx(son,now);
	while(sz[zx]<2*(sz[now]-sz[zx])) zx=fa[zx];
	return zx;
}

int get_val(int now,int f,int dep,long long vu,long long vd)
{
	vu=(vu*k+a[now])%y;
	if(dep) vd=(vd+a[now]*tm[dep-1])%y;
	tmp1[++cnt].id=now;
	tmp1[cnt].val=(x-vu+y)*inv[dep+1]%y;
	tmp2[cnt].id=now;
	tmp2[cnt].val=vd;
	for(int i=0; i<g[now].size(); i++)
	{
		if(g[now][i]==f||vis[g[now][i]]) continue;
		get_val(g[now][i],now,dep+1,vu,vd);
	}
}

int calc(int now,int kd,int dep,long long vu,long long vd)
{
	int posa,posb,tot;
	cnt=0;
	vu=(vu*k+a[now])%y;
	if(dep) vd=(vd+a[now]*tm[dep-1])%y;
	tmp1[++cnt].id=now;
	tmp1[cnt].val=(x-vu+y)*inv[dep+1]%y;
	tmp2[cnt].id=now;
	tmp2[cnt].val=vd;
	for(int i=0; i<g[now].size(); i++)
	{
		if(!vis[g[now][i]])
		{
			get_val(g[now][i],now,dep+1,vu,vd);
		}
	}
	sort(tmp1+1,tmp1+cnt+1,cmp);
	sort(tmp2+1,tmp2+cnt+1,cmp);
	tot=0;
	for(posa=posb=1; posa<=cnt; posa++)
	{
		while(posb<=cnt&&tmp2[posb].val<=tmp1[posa].val)
		{
			if(posb==1||tmp2[posb].val!=tmp2[posb-1].val) tot=0;
			tot++;
			posb++;
		}
		if(posb!=1&&tmp2[posb-1].val==tmp1[posa].val) out1[tmp1[posa].id]+=tot*kd;
	}
	tot=0;
	for(posa=posb=1; posb<=cnt; posb++)
	{
		while(posa<=cnt&&tmp1[posa].val<=tmp2[posb].val)
		{
			if(posa==1||tmp1[posa].val!=tmp1[posa-1].val) tot=0;
			tot++;
			posa++;
		}
		if(posa!=1&&tmp1[posa-1].val==tmp2[posb].val) in1[tmp2[posb].id]+=tot*kd;
	}
}

int solve(int now)
{
	vis[now]=1;
	calc(now,1,0,0,0);
	for(int i=0; i<g[now].size(); i++)
	{
		if(vis[g[now][i]]) continue;
		calc(g[now][i],-1,1,a[now],0);
	}
	for(int i=0 ;i<g[now].size(); i++)
	{
		if(vis[g[now][i]]) continue;
		get_sz(g[now][i],0);
		int zx=get_zx(g[now][i],0);
		solve(zx);
	}
}

int main()
{
	scanf("%lld%lld%lld%lld",&n,&y,&k,&x);
	for(int i=1; i<=n; i++)
	{
		scanf("%lld",&a[i]);
	}
	tm[0]=1;
	inv[0]=1;
	long long invk=kasumi(k,y-2);
	for(int i=1; i<=n; i++)
	{
		tm[i]=tm[i-1]*k%y;
		inv[i]=inv[i-1]*invk%y;
	}
	int from,to;
	for(int i=1; i<n; i++)
	{
		scanf("%d%d",&from,&to);
		g[from].push_back(to);
		g[to].push_back(from);
	}
	get_sz(1,0);
	int zx=get_zx(1,0);
	solve(zx);
	for(int i=1; i<=n; i++)
	{
		in0[i]=n-in1[i];
		out0[i]=n-out1[i];
		ans+=2*in0[i]*in1[i]+2*out0[i]*out1[i]+in1[i]*out0[i]+in0[i]*out1[i];
	}
	printf("%lld\n",1ll*n*n*n-ans/2);
}
```


---

## 作者：LiuIR (赞：2)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/CF434E)

对于定义 $S(i,j)$ 从点 $i$ 到点 $j$ 的路径上的点形成的序列，若序列 $S(i,j)$ 的长度为 $l$，序列上的点的权值为 $a_1\cdots a_l$，那么 $S(i,j)$ 的权值为
$$
G(S(i,j))=a_1\times k^0+a_2\times k^1+a_{l-1}\times k^{l-2}+a_{l}\times k^{l-1}
$$

若 $G(S(i,j))\equiv x\pmod y$，则该路径为好，否则为坏。现在统计三元组 $(i,j,k)$ 满足路径 $(i,j)$，路径 $(i,k)$，路径 $(j,k)$，都为好或都为坏的数量。

### 题目分析

我们可以建立一个有 $n^2$ 条边的有向图，若路径 $S(i,j)$ 属于，则从 $i$ 向 $j$ 连一条边权为 $0$ 的边，否则连一条边权为 $1$ 的边。那么我们只需计算边权都相同的有向三角形个数。

但直接计算较为困难，属于可以计算边权不同的有向三角形个数 $p$。设 $in0_i,in1_i,out0_i,out1_i$ 分别表示连向 $i$ 的边中 $0/1$ 的数量和 $i$ 连出去的边中 $0/1$ 的数量。那么
$$
p=\sum\limits_{i=1}^n2\times in0_i\times in1_i+in0_i\times out1_i+in1_i\times out0_i+2\times out0_i\times out1_i
$$
因为每一个三角形会被计算两次，所以最终答案为 $n^3-\dfrac{p}2$。

又因为
$$
in1_i=n-in0_i
$$
$$
out1_i=n-out0_i
$$
所以只需计算 $in0_i,out0_i$。于是可以设计一个 $O(n^2)$ 的暴力做法。根据套路，我们考虑使用点分治优化。

对于一个点分中心 $rt$，我们要计算经过 $rt$ 的路径 $S(u,v)$。对于每一个点 $u$，我们计算从 $u$ 到 $rt$ 和 $rt$ 到 $u$ 的路径长度和权值。令 $F(S(u,v))$ 表示从 $u$ 到 $v$ 的路径上不算 $u$ 的权值，$L(u,v)$ 表示从 $u$ 到 $v$ 的路径长度，那么一条经过 $rt$ 的路径 $S(u,v)$ 的权值为
$$
G(S(u,v))=G(S(u,rt))+F(S(rt,v))\times k^{L(u,rt)}
$$
又因为 $G(S(u,v))\equiv x\pmod y$，所以
$$
F(S(rt,v))\equiv\dfrac{x-S(u,rt)}{k^{L(u,rt)}}\pmod y
$$
所以可以将所有的 $F(s(rt,v))$ 加入数组后二分查找。

时间复杂度 $O(n\log^2n)$，可以通过本题。

### 细节处理

~~亿~~点点的小细节：

1. 有可能 $u$ 和 $v$ 都在同一个子树内，那么 $S(u,v)$ 就不经过 $rt$，所以要把这种情况减去。
2. 最后答案会爆 int，要用 long long 存。
3. 点分治找重心前要先更新 $size$ 和整棵树的大小。

```c++
#include <cstdio>
#include <cstring>
#include <algorithm>
 
using std::sort;
 
const int N = 1e5 + 5;
 
struct Node{
	int id, len;
	long long val;
}a[N], b[N], aa[N], bb[N];
class Graph{
	public:
		int cnt, head[N], next[N << 1], to[N << 1];
		void Add(int, int);
};
 
int tot, tot1, sum[N], size[N];
long long n, nn, k, x, y, in[N], out[N], pow_[N], inv[N], val[N];
bool bj[N];
Graph g;
 
bool operator < (Node, Node);
void Input();
void Output();
void Prepare();
void Work(int);
long long Pow(long long, int);
void Getsize(int, int);
void Solve(int, int, Node*, Node*);
void Getroot(int, int, int&);
void Getdis(int, int, int, long long, long long);
 
signed main()
{
	Input();
	Prepare();
	Work(1);
	Output();
	return 0;
}
 
void Graph::Add(int u, int v)
{
	next[++cnt] = head[u];
	to[cnt] = v;
	head[u] = cnt;
}
bool operator < (Node x_, Node y_){return x_.val < y_.val;}
void Input()
{
	scanf("%lld%lld%lld%lld", &n, &y, &k, &x);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &val[i])/*, val[i] %= y*/;
	for (int i = 1, u, v; i < n; i++)
	{
		scanf("%d%d", &u, &v);
		g.Add(u, v); g.Add(v, u);
	}
	nn = n;
}
void Output()
{
	n = nn;
	long long ans = 0, ans1 = n * n * n;
	for (int i = 1; i <= n; i++)
		ans += 2 * in[i] * (n - in[i]) + 2 * out[i] * (n - out[i]) + in[i] * (n - out[i]) + (n - in[i]) * out[i];
	printf("%lld", ans1 - ans / 2);
}
void Prepare()
{
	pow_[0] = inv[0] = 1;
	for (int i = 1; i <= n; i++)
		pow_[i] = pow_[i - 1] * k % y;
	inv[n] = Pow(pow_[n], y - 2);
	for (int i = n; i > 1; i--)
		inv[i - 1] = inv[i] * k % y;
}
void Work(int root)
{
	Getsize(root, 0);
	n = size[root];
	Getroot(root, 0, root);
	tot = 0;
	a[++tot] = Node{root, 1, val[root]};
	b[tot] = Node{root, 1, 0};
	for (int i = g.head[root]; i; i = g.next[i])
	{
		tot1 = 0;
		int v = g.to[i];
		if (bj[v])
			continue;
		Getdis(v, root, 0, val[root], 0);
		Solve(-1, tot1, aa, bb);
	}
	Solve(1, tot, a, b);
	bj[root] = true;
	for (int i = g.head[root]; i; i = g.next[i])
	{
		int v = g.to[i];
		if (bj[v])
			continue;
		Work(v);
	}
}
long long Pow(long long x_, int y_)
{
	long long res = 1;
	for(; y_; x_ = x_ * x_ % y, y_ >>= 1)if (y_ & 1)
		res = res * x_ % y;
	return res;
}
void Getsize(int u, int fa)
{
	size[u] = 1;
	for (int i = g.head[u]; i; i = g.next[i])
	{
		int v = g.to[i];
		if (v == fa || bj[v])
			continue;
		Getsize(v, u);
		size[u] += size[v];
	}
}
void Getroot(int u, int fa, int& root)
{
	bool flag = true;
	for (int i = g.head[u]; i; i = g.next[i])
	{
		int v = g.to[i];
		if (v == fa || bj[v])
			continue;
		Getroot(v, u, root);
		if (size[v] > n / 2)
			flag = false;
	}
	if (n - size[u] > n / 2)
		flag = false;
	if (flag)
		root = u;
}
void Solve(int f, int n, Node* a, Node* b)
{
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
	{
		long long value = (x - a[i].val + y) * inv[a[i].len] % y;
		int l = 1, r = n, s = n + 1, t = 0;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			if (b[mid].val > value)
				r = mid - 1;
			else if (b[mid].val < value)
				l = mid + 1;
			else
				s = mid, r = mid - 1;
		}
		if (s == n + 1)
			continue;
		l = 1; r = n;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			if (b[mid].val > value)
				r = mid - 1;
			else if (b[mid].val < value)
				l = mid + 1;
			else
				t = mid, l = mid + 1;
		}
		if (s > t)
			continue;
		out[a[i].id] += f * (t - s + 1);
		sum[s]++; sum[t + 1]--;
	}
	for (int i = 1; i <= n; i++)
	{
		sum[i] += sum[i - 1];
		in[b[i].id] += f * sum[i];
	}
	for (int i = 0; i <= n + 1; i++)
		sum[i] = 0;
}
void Getdis(int u, int fa, int deep, long long val1, long long val2)
{
	val1 = (val1 * k + val[u]) % y;
	val2 = (val2 + val[u] * pow_[deep]) % y;
	a[++tot] = Node{u, deep + 2, val1};
	b[tot] = Node{u, deep + 2, val2};
	aa[++tot1] = Node{u, deep + 2, val1};
	bb[tot1] = Node{u, deep + 2, val2};
	for (int i = g.head[u]; i; i = g.next[i])
	{
		int v = g.to[i];
		if (v == fa || bj[v])
			continue;
		Getdis(v, u, deep + 1, val1, val2);
	}
}
```

---

## 作者：tzc_wk (赞：2)

[Codeforces 题面传送门](https://codeforces.ml/contest/434/problem/E) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF434E)

~~场号 hopping，刚好是我的学号（指 round 的编号）~~

注：下文中分别用 $X,Y,K$ 代替题目中的 $x,y,k$

注意到这东西长得有点像三元环，因此考虑往三元环方面考虑。我们重新建立一张图，对于两点 $x,y$，如果 $x\to y$ 路径对应的权值为 $X$（即 $x\to y$ 这条路径属于 Furukawa Nagisa），那么我们就在 $x\to y$ 之间连一条权值为 $1$ 的边，否则我们在 $x\to y$ 之间连一条权值为 $0$ 的边，那么我们要求的即为有多少个三元组 $(x,y,z)$，满足 $x\to y,y\to z,x\to z$ 之间全是权值为 $1$ 的边，或者全是权值为 $0$ 的边。我们考虑借鉴竞赛图三元环计数的一个小 trick：从反面考虑。具体来说我们考虑不合法的情况长什么样，不难发现，对于每种不合法的情况都**恰好有两个点，满足与它相连的两条边恰好一条权值为 $0$，一条权值为 $1$**。我们记这样的点为这个三元组的“代表点”。我们考虑对每个点分别统计有多少个三元组，满足其在该三元组中作为一个代表点出现，那么一个不合法的三元组会恰好被计算两次，因此将这个数目除以 $2$ 就是不合法的三元组个数。

那么怎么计算每个点在多少个三元组中作为代表点呢？注意到对于一个点 $x$ 而言，与其相连的点可以被分为四类：$y\to x$，权值为 $0/1$，$x\to y$，权值为 $0/1$。因此考虑将与 $x$ 相连的两条边，一条权值为 $0$，一条权值为 $1$ 的情况分为以下四类：

- $y\to x$​，权值为 $0$​，$z\to x$​，权值为 $1$​
- $y\to x$，权值为 $0$，$x\to z$，权值为 $1$
- $x\to y$，权值为 $0$，$z\to x$，权值为 $1$
- $x\to y$，权值为 $0$，$x\to z$，权值为 $1$

不难发现对于第一种和第四种情况，$y,z$ 之间的边既可以是 $y\to z$，也可以是 $z\to x$，因此贡献应该乘 $2$，而对于第二种和第三种情况，$y,z$ 之间边的指向唯一。故如果我们已经求出 $c1_x$ 表示有多少个 $y$ 满足 $y\to x$ 的边权值为 $1$，$c2_x$ 表示有多少个 $y$ 满足 $x\to y$ 的边的权值为 $1$，那么一个点 $x$ 的贡献即可写作：
$$
2c1_x·(n-c1_x)+2c2_x·(n-c2_x)+c1_x·(n-c2_x)+c2_x·(n-c1_x)
$$
接下来考虑怎样求出 $c1_x,c2_x$​，注意到这里涉及树上路径统计，因此考虑点分治，于是问题可以转化为如何求出经过当前分治中心 $x$​ 的路径的贡献。对于 $x$​ 所在的连通块中的点 $y$​，我们考虑一遍 DFS 找出 $x\to y$​ 路径上所有点 $x=p_1,p_2,p_3,\cdots,p_k=y$​，那么我们考虑设 $s_y=\sum\limits_{i=2}^ka_{p_i}·K^{k-i},t_y=\sum\limits_{i=1}^ka_{p_i}·K^{i-1}$​，那么对于一条 $u\to v$​ 的路径，其权值可以写作 $s_u+t_v·K^{dep_u}$​。我们考虑从左到右遍历所有子树，那么 $c1_v$​ 会加上满足 $s_u+t_v·K^{dep_u}\equiv X\pmod{Y}$​ 的 $u$​ 的个数，这个可以开一个桶 $b1$​，然后每加入一个点 $u$​ 时，就在 $(X-s_u)·K^{-dep_u}$​ 位置加 $1$​，然后通过调用 $b1_{t_v}$​ 即可求出符合要求的 $u$ 的个数。$c2_v$ 的贡献也同理，一个点 $u$ 会对 $c2_v$ 产生贡献当且仅当 $s_v+t_u·K^{dep_v}\equiv X\pmod{Y}$，化简可得 $t_u\equiv(X-s_v)·K^{-dep_u}\pmod{Y}$，同样开个桶 $b2$ 维护一下即可。

时间复杂度 $n\log^2n$

```cpp
const int MAXN=1e5;
const int INF=0x3f3f3f3f;
int n,X,Y,k,a[MAXN+5];
int hd[MAXN+5],to[MAXN*2+5],nxt[MAXN*2+5],ec=0;
int qpow(int x,int e){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%Y) if(e&1) ret=1ll*ret*x%Y;
	return ret;
}
int pw[MAXN+5],ipw[MAXN+5];
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int siz[MAXN+5],cent=0,mx[MAXN+5];bool vis[MAXN+5];
void findcent(int x,int f,int tot){
	siz[x]=1;mx[x]=0;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f||vis[y]) continue;
		findcent(y,x,tot);siz[x]+=siz[y];
		chkmax(mx[x],siz[y]);
	} chkmax(mx[x],tot-siz[x]);
	if(mx[x]<mx[cent]) cent=x;
}
int dep[MAXN+5],f1[MAXN+5],f2[MAXN+5];
void getdep(int x,int f){
//	printf("%d %d %d %d\n",x,dep[x],f1[x],f2[x]);
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f||vis[y]) continue;
		dep[y]=dep[x]+1;f1[y]=(1ll*f1[x]*k+a[y])%Y;
		f2[y]=(f2[x]+1ll*a[y]*pw[dep[y]])%Y;
		getdep(y,x);
	}
}
vector<int> pt;
int res1[MAXN+5],res2[MAXN+5];
void getpts(int x,int f){
	pt.pb(x);
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f||vis[y]) continue;
		getpts(y,x);
	}
}
void divcent(int x){
//	printf("divcent %d\n",x);
	vis[x]=1;f1[x]=0;f2[x]=a[x];dep[x]=0;
	map<int,int> cnt1,cnt2;
	#define insert1(x) cnt1[1ll*(X-f1[x]+Y)*ipw[dep[x]]%Y]++
	#define insert2(x) cnt2[f2[x]]++
	#define calc(x) (res1[x]+=cnt1[f2[x]],res2[x]+=cnt2[1ll*(X-f1[x]+Y)*ipw[dep[x]]%Y])
	insert1(x);insert2(x);stack<int> stk;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(vis[y]) continue;
		f1[y]=a[y];f2[y]=(1ll*a[y]*k+a[x])%Y;
		dep[y]=1;getdep(y,x);
	}
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(vis[y]) continue;
//		printf("y=%d\n",y);
		pt.clear();getpts(y,x);stk.push(y);
		for(int z:pt) calc(z);
		for(int z:pt) insert1(z),insert2(z);
	} cnt1.clear();cnt2.clear();
	while(!stk.empty()){
		int y=stk.top();stk.pop();
//		printf("y=%d\n",y);
		pt.clear();getpts(y,x);
		for(int z:pt) calc(z);
		for(int z:pt) insert1(z),insert2(z);
	} calc(x);
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(vis[y]) continue;
		cent=0;findcent(y,x,siz[y]);divcent(cent);
	}
}
int main(){
	scanf("%d%d%d%d",&n,&Y,&k,&X);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),adde(u,v),adde(v,u);
	pw[0]=ipw[0]=1;pw[1]=k;ipw[1]=qpow(k,Y-2);
	for(int i=2;i<=n;i++){
		pw[i]=1ll*pw[i-1]*pw[1]%Y;
		ipw[i]=1ll*ipw[i-1]*ipw[1]%Y;
	} mx[0]=INF;findcent(1,0,n);divcent(cent);
	for(int i=1;i<=n;i++) if(a[i]==X) res1[i]++,res2[i]++;
//	for(int i=1;i<=n;i++) printf("%d %d\n",res1[i],res2[i]);
	ll res=0;
	for(int i=1;i<=n;i++){
		int rst1=n-res1[i],rst2=n-res2[i];
		res+=2ll*rst1*res1[i];res+=1ll*rst1*res2[i];
		res+=1ll*rst2*res1[i];res+=2ll*rst2*res2[i];
	} printf("%lld\n",1ll*n*n*n-(res>>1));
	return 0;
}
```



---

## 作者：WeLikeStudying (赞：1)

- emmm，我不是有意要摆烂的，我只是想不到。

**[题意](https://www.luogu.com.cn/problem/CF434E)**
- 对于 $u$ 到 $v$ 树上路径所成字符串的一种哈希函数 $H(u,v)$，您需要研究这个函数 $G(u,v)=[H(u,v)=x]$ 。
- 为了加大难度，您需要在一棵树上统计类似于三元环的东西：$G(u,v)=G(v,w)=G(u,w)$ 的个数。

**分析**
- 我们拥有 $O(n^3)$ 的[暴力](https://www.luogu.com.cn/paste/gyxtt92j)，但是这不值得夸耀！
- 经过我们的仔细思考，我们发现三个量就像石榴籽一样紧紧抱在一起！我们希望尝试将其分开！
- 我们现在可以快速的算出所有 $G(u,v)$ 的和，也可以快速算出 $G(u,v)=G(v,w)$ 的方案数，因为我们可以利用差分在 $v$ 上将他枚举到，但是，丝毫看不出这个和 $G(u,w)$ 有什么关系，如果我们必须要枚举三元环，我们也就必须陷入 $\text{TLE}$。
- 它这个三元害人不浅呐！仔细思考一下我们会发现，我们的树上路径在一个点交会！但是那个点似乎没有什么性质！如果我们一开始来思考的话，我们或许可以枚举所有端点，或许能够得到一个类似于 $O(n^2)$ 的做法。
- 但是，三元害人不浅！不弄开它，信息学的伟大事业是不能取得发展和进步的！
- 然后我忽然发现反着想以后：我们那个算出 $G(u,v)=G(v,w)$ 的方案数的东西，在三元环的三个位置分别处理两种方向信息加起来之后，结果恰好是除了 $G(u,v)=G(v,w)=G(u,w)$ 情况的两倍！因为情况恰好是完全对称的！
![](https://cdn.luogu.com.cn/upload/image_hosting/bby3c48r.png)
- 因此，我们可以直接上点分治了，这题有点坑人：[代码](https://www.luogu.com.cn/paste/dhvr68cb)。

---

## 作者：Saka_Noa (赞：1)

定义 $t(p_1 \to p_2) = z_{0}\times k^{0}+z_{1}\times k^{1} + \cdots + z_{l-1} \times k^{l-1}$，$f(r) = [r = x]$  
则答案为 
$$\sum_{p_1 \in n}\sum_{p_2 \in n} \sum_{p_3 \in n} [f(t(p_1\to p_2))=f(t(p_2 \to p_3))=f(t(p_1 \to p_3))]$$  
计 $R(p_1,p_2) = f(t(p_1\to p_2))$，考虑等价变形  
$$\sum_{p_1 \in n}\sum_{p_2 \in n} \sum_{p_3 \in n} R(p_1, p_2)R(p_2,p_3)R(p_1,p_3)+(1-R(p_1, p_2))(1-R(p_2,p_3))(1-R(p_1,p_3))$$  
将右边的柿子拆开：  
$$1-R(p_1,p_2)-R(p_1,p_3)-R(p_2,p_3)+R(p_1,p_2)R(p_1,p_3)+R(p_1,p_2)R(p_2,p_3)+R(p_1,p_3)R(p_2,p_3)$$  
记 $a_u =\sum_{v \in n} R(u,v)$，$b_u=\sum_{v \in n} R(v,u)$  
上面的和式可以化为：
$$n^3-\frac{3n}{2}\sum (a_i+b_i)+\sum (a_i^2+b_i^2+a_i \times b_i)$$  
实质上 $\sum a_i = \sum b_i$。  
处理 $a_u$ 和 $b_u$ 可以使用点分治。  
具体来说：对于一个分治中心 $u$，处理出 $t(u,v)$，$t(v,u)$，记为 $c_u,d_v$。有 $c_u +d_u \times k^{len_{c_u}+1}=x$。我们把 $d_i$ 和 $\frac{x-c_i}{k^{len_{c_i}+1}}$ 分别丢进哈希表里，每次枚举 $c_i$ 和 $d_i$，$O(1)$ 查询。  
使用 ```unordered_map``` 建议使用 ```while``` $+$ ```erase``` 清空，使用 ```clear``` 貌似会被卡？  
建议预处理出逆元和 $k$ 的 $i$ 次方，不然复杂度是假的。
```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
#define mp make_pair
typedef long long ll; 
const int N = 1e6 + 500;
int read() {
    int x = 0;char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return x;
}
struct edge{int next,to;}e[N << 1];
int n, sum, rt, y, k, r, nnv, ccv;
int cnt, head[N], maxp[N], si[N], val[N], vis[N];
ll fk[N], ink[N];
ll a[N], b[N], dl[N]; 
pair<int, int> dd[N];
pair<ll, pair<int, int> > cc[N]; 
unordered_map<ll, ll> Q, W; 
void add(int f, int t) {e[++cnt] = edge{head[f], t}, head[f] = cnt;} 
void get_core(int u, int f) {
    maxp[u] = 0;
    si[u] = 1;
    for(int i = head[u];i;i = e[i].next) {
        int v = e[i].to;
        if(v == f || vis[v]) continue;
        get_core(v, u);
        si[u] += si[v];
        maxp[u] = max(maxp[u], si[v]);
    }
    maxp[u] = max(maxp[u], sum - si[u]);
    if(!rt || maxp[u] < maxp[rt]) rt = u; 
}
ll km(ll a, ll b){
    ll ans = 1, bs = a;
    while(b) {if(b & 1) ans = (ans * bs) % y;bs = (bs * bs) % y;b >>= 1;} 
    return ans;
}
void get_dis(int u, int f, ll len, int dep, bool jd = false) {
    len = (len * k  + val[u]) % y;
    cc[++ccv] = mp(len, mp(dep, u)); // cc : v -> u
    dl[u] = (dl[f] + fk[dep + 1] * val[u] ) % y; // dd : u -> v
    dd[++nnv] = mp(dl[u], u); 
    for(int i = head[u];i; i = e[i].next) {
        int v = e[i].to;
        if(v == f || vis[v]) continue;
        get_dis(v ,u, len, dep + 1, jd);
    }
}
int qr(int vl, int kt) {
    int c = r - vl;
    return (c * ink[kt] % y + y) % y;
}
void tadd(int opt) {
    for (int dk = 1; dk <= nnv; dk++) W[dd[dk].first] += opt;
    for (int dk = 1; dk <= ccv; dk++) Q[qr(cc[dk].first, cc[dk].second.first + 1)] += opt;
}
void calc(int u) {
    while(!Q.empty()) Q.erase(Q.begin());
    while(!W.empty()) W.erase(W.begin());
    dl[u] = val[u];
    Q[r]++, W[val[u]]++;
    ccv = nnv = 0;
    for(int i = head[u];i ;i = e[i].next) {
        int v = e[i].to;
        if(vis[v]) continue;
        get_dis(v, u, 0, 0);
    }
    tadd(1);
    a[u] += W[r];
    b[u] += Q[val[u]];
    for(int i = head[u];i;i = e[i].next) {
        int v = e[i].to;
        if(vis[v]) continue;
        ccv = nnv = 0;
        get_dis(v, u, 0, 0);
        tadd(-1);
        for(int dk = 1;dk <= ccv;dk++) 
            a[cc[dk].second.second] += W[qr(cc[dk].first, cc[dk].second.first + 1)];
        for(int dk = 1;dk <= nnv;dk++) b[dd[dk].second] += Q[dd[dk].first];
        tadd(1);
    }
}
void solve(int u) {
    vis[u] = 1;
    calc(u);
    for(int i = head[u];i;i = e[i].next) {
        int v = e[i].to;
        if(vis[v]) continue;
        sum = si[v], rt = 0;
        get_core(v, u);
        solve(rt);
    }
}
int main(){
    scanf("%d %d %d %d", &n, &y, &k, &r); r %= y;
    for(int i = 1;i <= n;i++) val[i] = read();
    for(int i = 1;i < n;i++) {
        int u, v;
        u = read(), v = read();
        add(u, v), add(v, u);
    } fk[0] = 1;
    for(int i = 1;i <= n;i++) fk[i] = (fk[i - 1] * k) % y;
    for(int i = 1;i <= n;i++) ink[i] = km(fk[i], y - 2);
    sum = n;
    get_core(1, 0);
    solve(rt);
    ll ans = (ll)n * n * n;
    for(int i = 1;i <= n;i++) ans -= 3 * n * a[i];
    for(int i = 1;i <= n;i++) 
        ans += (ll)a[i] * a[i] + (ll)b[i] * b[i] + (ll)a[i] * b[i];    
    printf("%lld", ans);
    return 0;
}
```

---

