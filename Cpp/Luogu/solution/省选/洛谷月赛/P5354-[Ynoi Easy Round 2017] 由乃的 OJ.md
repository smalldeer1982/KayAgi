# [Ynoi Easy Round 2017] 由乃的 OJ

## 题目背景

![](https://cdn.luogu.com.cn/upload/pic/58221.png)

## 题目描述

由乃正在做她的OJ。现在她在处理OJ上的用户排名问题。

OJ 上注册了 $n$ 个用户，编号为 $1\sim n$，一开始他们按照编号排名。由乃会按照心情对这些用户做以下四种操作，修改用户的排名和编号：然而由乃心情非常不好，因为 Deus 天天问她题。。。
 
因为 Deus 天天问由乃 OI 题，所以由乃去学习了一下 OI，由于由乃智商挺高，所以 OI 学的特别熟练。

她在 RBOI2016 中以第一名的成绩进入省队，参加了 NOI2016 获得了金牌保送。

Deus：这个题怎么做呀？  
yuno：这个不是 NOI2014 的水题吗。。。  
Deus：那如果出到树上，多组链询问，带修改呢？  
yuno：诶。。。？？？  
Deus：这题叫做睡觉困难综合征哟~  

虽然由乃 OI 很好，但是她基本上不会 DS，线段树都只会口胡，比如她 NOI2016 的分数就是 $100+100+100+0+100+100$。。。NOIP2017 的分数是 $100+0+100+100+0+100$。

所以她还是只能找你帮她做了。。。

给你一个有 $n$ 个点的树，每个点的包括一个位运算 $opt$ 和一个权值 $x$，位运算有`&`，`|`，`^` 三种，分别用 $1,2,3$ 表示。

每次询问包含三个整数 $x,y,z$，初始选定一个数 $v$。然后 $v$ 依次经过从 $x$ 到 $y$ 的所有节点，每经过一个点 $i$，$v$ 就变成 $v\ opt_i\ x_i$，所以他想问你，最后到 $y$ 时，希望得到的值尽可能大，求最大值。给定的初始值 $v$ 必须是在 $[0,z]$ 之间。

每次修改包含三个整数 $x,y,z$，意思是把 $x$ 点的操作修改为 $y$，数值改为 $z$。

## 说明/提示

Idea：f321dd，Solution：f321dd&nzhtl1477，Code：nzhtl1477，Data：nzhtl1477

对于 $30\%$ 的数据，$n,m\leq 1$。

对于另外 $20\%$ 的数据，$k\leq 5$。

对于另外 $20\%$ 的数据，位运算只会出现一种。

对于 $100\%$ 的数据，$0\leq n,m \leq 10^5$，$0\leq k\leq 64$。


## 样例 #1

### 输入

```
5 5 3
1 7
2 6
3 7
3 6
3 1
1 2
2 3
3 4
1 5
1 1 4 7
1 1 3 5
2 1 1 3
2 3 3 3
1 1 3 2```

### 输出

```
7
1
5```

## 样例 #2

### 输入

```
2 2 2
2 2
2 2
1 2
2 2 2 2
1 2 2 2```

### 输出

```
3```

# 题解

## 作者：noip (赞：46)

首先发现每一位不会互相影响，可以把每一位分开考虑，然后用树链剖分或者LCT维护这个树

修改直接修改，询问的时候算出来每一位填0，1经过这条链的变换之后得到的值

考虑贪心，从高往低，如果这一位填0可以得到1，那么填0一定是最优的

否则如果可以填1，就把这一位填为1

复杂度是nklog^2n或者nklogn，只能通过50%的数据

发现可以并行计算这k位，复杂度降为nlog^2n的树链剖分或者nlogn的LCT，可以通过100%的数据

这个题没有卡常，合并信息不是O( 1 )的算法没有通过是很正常的吧。。。

还有树链剖分没法做到logn，每条链建线段树也是log^2n的，还不能搞子树，似乎常数也一般。。。

最优复杂度是log^2n，不过期望下大概是lognloglogn的感觉

这个题的最优复杂度为O( n + q( logn + k ) )，至少目前来说是这样的

![](https://cdn.luogu.com.cn/upload/pic/4163.png)


---

## 作者：Orion545 (赞：34)

# 广告

[蒟蒻のblog](https://www.cnblogs.com/dedicatus545/p/9404081.html)

# 思路

### 原题目

我们先看这道题的原题目[NOI2014起床困难综合症](https://www.luogu.org/problemnew/show/P2114)

的确就是上树的带修改版本

那么我们先来解决这个原版的序列上单次询问

二进制的这些操作，我们把操作数和符号一起（比如xor 7,and 31）挪动的话，答案是会改变的，不同符号之间不满足交换律和结合律

那么我们就无法把这些操作的顺序随意变换为比较好算的方式了

考虑二进制位运算的过程，发现这三种运算的过程中，不同的二进制位之间不会有互相影响

因此我们考虑把每个二进制位拆出来处理

对于每一个二进制位，我们记录两个值a0,a1，分别表示这一位上是0或1的情况下，走过所有运算之后得到的是0还是1

然后，我们从高的二进制位往低的走，贪心地在高位可以达成1且不会超过m的限制的情况下，令高位为1

这道题就做完了（的确作为NOI题来说简单了一些，果然签到题啊）

那么当本题上树+修改之后了，怎么办呢？

### 树剖+线段树

一个显而易见的想法就是用树剖+线段树这种可以轻松维护链上信息的数据结构来修改+询问

那么，我们对于每一个二进制位，维护区间中从左到右跑和从右到左跑得到的是0还是1，询问的时候把链拆开到线段树上，不同的链之间可以直接01对应合并

再和上面一样贪心就好了......吗？

这样的复杂度是多少呢？是$O(nklog^2n)$的，虽然那个$log^2$常数很小，但是这个玩意儿满打满算也是个$O(nklogn)$的，本题数据范围下肯定过不了

### 优化

这怎么解决？

我们发现上述复杂度中，最有希望优化掉的就是那个$k$，因为其他的都是树剖的固有复杂度了

怎么优化掉$k$呢？我们考虑再把这些二进制位压回同一个 long long 里面

但是这样就有一个问题，那就是在线段树上，我们不知道怎么合并了

原来每一个二进制位拆开的时候，两个线段树节点之间的合并就是0出来的对应0进去的，1出来的对应1进去的，但是压位起来以后，难道我们要枚举$2^k$种状态分别对应转移吗？

非也

### 线段树节点的合并

**二进制位运算是每一位独立的**

我们现在要再一次让这个结论发挥作用：我们可以用位运算来解决这些独立的、但是被压到一起了的二进制位

假设当前要合并的线段树节点是$l$和$r$，$f_0[l]$的第$i$位代表这一位进去是0时出来的值，$f_1[l]$同理

那么显然，对于新的合并后节点$u$而言，如果$f_0[u]$的第$i$位（后文中用$f_0[u][i]$表示）是1，那么有以下两种情况：

情况一：$f_0[l][i]==1$且$f_1[r][i]==1$

情况二：$f_0[l][i]==0$且$f_0[r][i]==1$

可以得到表达式：$f_0[u][i]=(f_0[l][i]\;bitand\;f_1[r][i])\;bitor\;(!f_0[l][i]\;bitand\;f_0[r][i])$

那么把这个式子放到整个$f_0[u]$的角度上，就是$f_0[u]=((f_0[l]\;bitand\;f_1[r])\;bitor\;((bitnot\;f_0[l])\;bitand\;f_1[r]))$

其中$bitand,bitor,bitnot$分别是按位与，或，取反

对于$f_1[u]$，也是同样的道理，$f_1[u]=((f_1[l]\;bitand\;f_1[r])\;bitor\;((bitnot\;f_1[l])\;bitand\;f_0[r]))$

（注意还有反过来跑的要处理）

### 问题解决

这样之后，我们可以对于修改进行单点修改，然后树链剖分+区间询问，得到每一位的输入01对应输出01。树剖中的序列合并也可以用上述方法合并起来

最后我们做一次原题中的贪心即可

### 坑点

要用unsigned long long

需要维护4个值，不要写混了

树剖得到两个序列：x->lca和y->lca，但是注意其中一个要把跑的顺序反过来

# Code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#include<cmath>
#define ll unsigned long long
using namespace std;
inline ll read(){
	ll re=0,flag=1;char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-') flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') re=(re<<1)+(re<<3)+ch-'0',ch=getchar();
	return re*flag;
}
const ll LIM=0-1;
int n,Q,K,first[200010],dep[200010],son[200010],siz[200010],top[200010],pos[200010],back[200010];
int op[200010],cnte,cntn,fa[200010];ll val[200010];
struct data{
	ll f0,f1,inv0,inv1;
    //f0:从左到右，0进
    //f1:从左到右，1进
    //inv0:从右到左，0进
    //inv1:从右到左，1进
	data(){f0=f1=inv0=inv1=0;}
}a[800010];
struct edge{
	int to,next;
}e[200010];
inline void add(int u,int v){
	e[++cnte]=(edge){v,first[u]};first[u]=cnte;
	e[++cnte]=(edge){u,first[v]};first[v]=cnte;
}
void dfs1(int u,int f){
	int i,v;dep[u]=dep[f]+1;siz[u]=1;son[u]=0;fa[u]=f;
	for(i=first[u];~i;i=e[i].next){
		v=e[i].to;if(v==f) continue;
		dfs1(v,u);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int t){
	int i,v;top[u]=t;pos[u]=++cntn;back[cntn]=u;
	if(son[u]) dfs2(son[u],t);
	for(i=first[u];~i;i=e[i].next){
		v=e[i].to;if(pos[v]) continue;
		dfs2(v,v);
	}
}
ll calc(ll num,int x){
	if(op[x]==1) return num&val[x];
	if(op[x]==2) return num|val[x];
	if(op[x]==3) return num^val[x];
}
data update(data l,data r){
	data re;//核心合并过程，参考上方题解
	re.f0=((l.f0&r.f1)|((~l.f0)&r.f0));
	re.f1=((l.f1&r.f1)|((~l.f1)&r.f0));
	re.inv0=((r.inv0&l.inv1)|((~r.inv0)&l.inv0));
	re.inv1=((r.inv1&l.inv1)|((~r.inv1)&l.inv0));
	return re;
}
void build(int l,int r,int num){
	if(l==r){
		a[num].f0=a[num].inv0=calc(0,back[l]);
		a[num].f1=a[num].inv1=calc(LIM,back[l]);
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,num<<1);build(mid+1,r,(num<<1)+1);
	a[num]=update(a[num<<1],a[(num<<1)+1]);
}
void change(int l,int r,int num,int pos){
	if(l==r){
		a[num].f0=a[num].inv0=calc(0,back[l]);
		a[num].f1=a[num].inv1=calc(LIM,back[l]);
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=pos) change(l,mid,num<<1,pos);
	else change(mid+1,r,(num<<1)+1,pos);
	a[num]=update(a[num<<1],a[(num<<1)+1]);
}
data query(int l,int r,int ql,int qr,int num){
	if(l==ql&&r==qr) return a[num];
	int mid=(l+r)>>1;data re;
	if(mid>=qr) re=query(l,mid,ql,qr,num<<1);
	else{
		if(mid<ql) re=query(mid+1,r,ql,qr,(num<<1)+1);
		else re=update(query(l,mid,ql,mid,num<<1),query(mid+1,r,mid+1,qr,(num<<1)+1));//询问时也是同样的合并
	}
	return re;
}
data ans1[100010],ans2[100010];int cnt1,cnt2;
data solve(int x,int y){
	cnt1=cnt2=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>=dep[top[y]]){
			ans1[++cnt1]=query(1,n,pos[top[x]],pos[x],1);
			x=fa[top[x]];
		}
		else{
			ans2[++cnt2]=query(1,n,pos[top[y]],pos[y],1);
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y]) ans1[++cnt1]=query(1,n,pos[y],pos[x],1);
	else ans2[++cnt2]=query(1,n,pos[x],pos[y],1);
	data re;int i;
	for(i=1;i<=cnt1;i++) swap(ans1[i].f0,ans1[i].inv0),swap(ans1[i].f1,ans1[i].inv1);//反过来
	if(cnt1){
		re=ans1[1];
		for(i=2;i<=cnt1;i++) re=update(re,ans1[i]);
		if(cnt2) re=update(re,ans2[cnt2]);
	}
	else re=ans2[cnt2];
	for(i=cnt2-1;i>=1;i--) re=update(re,ans2[i]);
	return re;
}
int main(){
	memset(first,-1,sizeof(first));
	n=read();Q=read();K=read();int i,t1,t2,opt;ll t3,ans,tmp0,tmp1;
	for(i=1;i<=n;i++) op[i]=read(),val[i]=read();
	for(i=1;i<n;i++){
		t1=read();t2=read();
		add(t1,t2);
	}
	dfs1(1,0);dfs2(1,1);
	build(1,n,1);
	while(Q--){
		opt=read();t1=read();t2=read();t3=read();
		if(opt==2){
			op[t1]=t2;val[t1]=t3;
			change(1,n,1,pos[t1]);
		}
		else{
			data re=solve(t1,t2);ans=0;
			for(i=63;i>=0;i--){//贪心
				tmp0=(re.f0>>i)&1ull;
				tmp1=(re.f1>>i)&1ull;
				if(tmp0>=tmp1||(1ull<<i)>t3) ans|=(tmp0?(1ull<<i):0);
				else ans|=(tmp1?(1ull<<i):0),t3-=(1ull<<i);
			}
			printf("%llu\n",ans);
		}
	}
}
```

---

## 作者：Macesuted (赞：14)

[在我的个人博客中阅读以获得更佳阅读体验](https://www.macesuted.cn/article/lg5354/)

---

[题面](https://www.luogu.com.cn/problem/P5354)

## 题意

给定一棵 $n$ 个点的树，每个节点上均有一个二进制运算符（`&`、`|` 或 `^`）和一个在 $[0,~2^k-1]$ 之间的数值。

接下来给定 $m$ 个操作，每个操作分为两类：

1. 修改某个结点上的运算符与数值。
2. 给定 $x,~y,~z$，你可以先任意指定一个值 $val \in [0,~z]$，然后在树上沿 $x$ 与 $y$ 之间的简单路径从 $x$ 向 $y$ 移动，每次到达一个结点后将 $val$ 变为 $val~op[i]~a[i]$，$op[i]$ 为该节点上运算符，$a[i]$ 为该节点上数值。最大化到达 $y$ 结点时的 $val$ 值并输出。

$n,~m \le 10^5,~0 \le k \le 64$

## 分析

由于询问时询问的是树上两点间路径的信息，不难想到通过树链剖分将每条路径转化为 $\log n$ 个区间。

由于每个结点上的运算符均为二进制位运算符，运算过程中不同二进制位之间互不影响。我们可以考虑对于每一个二进制位分开来考虑其运算结果，即对于每一个二进制位都求出其为 $0/1$ 时经过路径后的结果，最后通过类似数位 DP 的计算方法即可求出 $[0,~z]$ 区间内的初值可产生的最大运算结果。

而由于询问时两点间的路径是有向的，从 $x \to lca$ 的路径是向上的，从 $lca \to y$ 的路径是向下的。将树上移动的顺序对应到区间上移动的顺序，不难发现 $x \to lca$ 的路径对应的区间都是从右向左经过的，$lca \to y$ 的路径对应的区间都是从左向右经过的。因此我们需要对于每一个区间都求出每一个二进制位初始为 $0/1$ 时从左向右或是从右向左经过该区间之后的值。

考虑如何维护，建立一棵线段树，每个线段树结点都记录 $l0[i],~l1[i],~r0[i],~r1[i]$ 分别表示：

1. 二进制第 $i$ 位为 $0$ 时从左向右经过该区间后该位的值。
2. 二进制第 $i$ 位为 $1$ 时从左向右经过该区间后该位的值。
3. 二进制第 $i$ 位为 $0$ 时从右向左经过该区间后该位的值。
4. 二进制第 $i$ 位为 $1$ 时从右向左经过该区间后该位的值。

每次合并两个结点 $a,~b$ 的信息时令：

1. `ans.l0[i] = a.l0[i] && b.l1[i] || !a.l0[i] && b.l0[i]`
2. `ans.l1[i] = a.l1[i] && b.l1[i] || !a.l1[i] && b.l0[i]`
3. `ans.r0[i] = b.r0[i] && a.r1[i] || !b.r0[i] && a.r0[i]`
4. `ans.r1[i] = b.r1[i] && a.r1[i] || !b.r1[i] && a.r0[i]`

即枚举某一位在经过第一个区间后的值，将其以初值代入第二个区间得到结果。

此时对于每一个询问我们将路径拆为 $\log n$ 个区间，每个区间对应 $\log n$ 个线段树结点，每次合并结点需要花费 $O(k)$ 的时间，因此此时的总时间复杂度为 $O(m \times k \times \log ^2n)$，无法通过本题。

## 优化

我们仔细分析上面的时间复杂度，发现两个 $\log n$ 在该算法中都难以去除，因此我们考虑优化掉 $O(k)$ 的时间复杂度。容易发现 $O(k)$ 的时间复杂度来自线段数结点合并。

仔细观察我们发现对于 $k$ 位分别进行逻辑运算是非常浪费的，我们考虑将四个大小为 $k$ 的数组压为四个大小为 $2^k$ 的数字，将逻辑运算转变为二进制位运算即可。对应的四个转移变为：

1. `ans.l0 = (a.l0 & b.l1[i]) | (~a.l0[i] & b.l0[i])`
2. `ans.l1 = (a.l1 & b.l1[i]) | (~a.l1[i] & b.l0[i])`
3. `ans.r0 = (b.r0 & a.r1[i]) | (~b.r0[i] & a.r0[i])`
4. `ans.r1 = (b.r1 & a.r1[i]) | (~b.r1[i] & a.r0[i])`

因此合并结点信息的复杂度优化到 $O(1)$，总复杂度达到 $O(m \times \log ^2n)$，足以通过此题。

## 代码

[View on GitHub](https://github.com/Macesuted/Code/blob/main/Luogu/5354.cpp)

---

## 作者：MatrixCascade (赞：12)

此题为[[NOI2014]起床困难综合症](https://www.luogu.com.cn/problem/P2114)扩展到树上带修改。

我们首先考虑弱化版这个题怎么做。先求出二进制全 0 和全 1 经过门后的状态，然后从高位到低位去贪心。如果可以用 0 换 1 必换，如果可以用 1 换 1 就尽可能换（每次换完把 m 减掉这一位的贡献，如果不够就不换。）然后这个题就解决了。

然后看到树上操作，并且带修改，就可以想到用 LCT 维护。我一开始的想法是先拆位，然后每一位用一颗 LCT 维护，每一次合并是 $O(k)$ 的，总复杂度$O(knlogn)$，差不多 $1e8$ 左右，还要考虑常数，非常不稳。

于是就考虑 $O(1)$ 合并左右子树的信息。每个节点存中序遍历和反中序遍历得到的二进制全 0 和全 1 经过门后的状态。ans0 代表初始全为 0 的答案，ans1 代表初始全为 1 的答案。

考虑合并 2 个区间 a 和 b 。设合并出来的区间叫 c。  
则 c.ans0 的第 k 位为 1 的条件是：a.ans0 的 第 k 位为 0，并且 b.ans0 的第 k 位为 1；或者是 a.ans0 的第 k 位为 1 而且 b.ans1 的第 k 位为 1。

然后把所有位合起来考虑，就有这样的式子:  
```
z.ans0 = (~x.ans0 & y.ans0) | (x.ans0 & y.ans1);
z.ans1 = (~x.ans1 & y.ans0) | (x.ans1 & y.ans1);
```

然后每次询问就把 x 和 y split 出来，跑弱化版的那个算法就可以了。

一些细节：

- 翻转操作的时候要将中序遍历和反中序遍历得到的答案交换一下。

- 如果你 `define int unsigned long long` 了，按位贪心枚举位数的时候不能直接`for(int kk = 63; kk >= 0; --kk)` 需要在统计完后特判 kk=0 的情况去 break（因为 0ull-1 不等于 -1，所以就会死循环）

- 位移要 1ull ，这不用多说了吧。

如果你此题 TLE 了，基本上就是你复杂度错了，亲测此题不卡常（（

~~关于 LCT 就不用多说了吧，不会就先学一下或用树剖做~~

```
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int maxn = 1e6 + 10;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}
struct node
{
    int ans0, ans1;
} val[maxn], head[maxn], tail[maxn];
int fa[maxn], ch[maxn][2], sta[maxn], rev[maxn];
node merge(node x, node y)
{
    node z;
    z.ans0 = (~x.ans0 & y.ans0) | (x.ans0 & y.ans1);
    z.ans1 = (~x.ans1 & y.ans0) | (x.ans1 & y.ans1);
    return z;
}
bool notroot(int x)
{
    return ch[fa[x]][0] == x || ch[fa[x]][1] == x;
}
void pushup(int x)
{
    head[x] = tail[x] = val[x];
    if (ch[x][0])
    {
        head[x] = merge(head[ch[x][0]], head[x]);
        tail[x] = merge(tail[x], tail[ch[x][0]]);
    }
    if (ch[x][1])
    {
        head[x] = merge(head[x], head[ch[x][1]]);
        tail[x] = merge(tail[ch[x][1]], tail[x]);
    }
    return;
}

void turn(int x)
{
    swap(head[x], tail[x]);
    swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;
}
void pushdown(int x)
{
    if (rev[x])
    {
        if (ch[x][0])
            turn(ch[x][0]);
        if (ch[x][1])
            turn(ch[x][1]);
        rev[x] = 0;
    }
    return;
}
void rotate(int x)
{
    int y = fa[x], z = fa[y];
    int k1 = (ch[y][1] == x);
    int v = ch[x][!k1];
    if (notroot(y))
    {
        ch[z][ch[z][1] == y] = x;
    }
    ch[x][!k1] = y;
    ch[y][k1] = v;
    if (v)
    {
        fa[v] = y;
    }
    fa[y] = x;
    fa[x] = z;
    pushup(y);
    pushup(x);
}
void splay(int x)
{
    int top = 0;
    int y = x, z;
    sta[++top] = y;
    while (notroot(y))
        sta[++top] = y = fa[y];
    while (top)
        pushdown(sta[top--]);
    while (notroot(x))
    {
        y = fa[x], z = fa[y];
        if (notroot(y))
        {
            rotate((ch[y][0] == x) ^ (ch[z][0] == y) ? x : y);
        }
        rotate(x);
    }
    pushup(x);
    return;
}
void access(int x)
{
    for (int y = 0; x; x = fa[y = x])
    {
        splay(x);
        ch[x][1] = y;
        pushup(x);
    }
}
void makeroot(int x)
{
    access(x);
    splay(x);
    turn(x);
}
void split(int x, int y)
{
    makeroot(x);
    access(y);
    splay(y);
}
void link(int x, int y)
{
    makeroot(x);
    fa[x] = y;
}
signed main()
{
    int mn = 0;
    int mx = ~mn;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i)
    {
        int x, y;
        cin >> x >> y;
        if (x == 1)
            val[i] = (node){mn, y};
        if (x == 2)
            val[i] = (node){y, mx};
        if (x == 3)
            val[i] = (node){y, ~y};
    }
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        link(x, y);
    }
    for (int i = 1; i <= m; ++i)
    {
        int opt, x, y, z;
        cin >> opt >> x >> y >> z;
        //opt = read(), x = read(), y = read(), z = read();
        if (opt == 1)
        {
            split(x, y);
            node nw = head[y];
            int ans = 0;
            for (long long kk = 63; kk >= 0; --kk)
            {
                if (nw.ans0 & (1ull << kk))
                {
                    ans += (1ull << kk);
                }
                else if (nw.ans1 & (1ull << kk) && z >= (1ull << kk))
                {
                    ans += (1ull << kk);
                    z -= (1ull << kk);
                }
            }
            cout << ans << endl;
        }
        if (opt == 2)
        {
            if (y == 1)
                val[x] = (node){mn, z};
            if (y == 2)
                val[x] = (node){z, mx};
            if (y == 3)
                val[x] = (node){z, ~z};
            splay(x);
        }
    }
}
```


---

## 作者：bztMinamoto (赞：8)

打个广告：[blog](https://www.cnblogs.com/bztMinamoto/p/9430957.html)

人生第一道由乃……

做这题之前应该先去把这一题给切掉->[这里](https://www.luogu.org/problemnew/show/P2114)

我的题解->[这里](https://www.cnblogs.com/bztMinamoto/p/9429072.html)

大体思路就是先吧全0和全1的都跑答案，然后按位贪心

我一开始想到的是每一次split，然后直接一个一个跑

后来发现时间复杂度肯定爆炸……

跑来看看题解……发现楼下的大佬们都太强了根本看不懂他们在说什么……特别是那个公式为什么都不解释一下直接“不难看出”“简单推导”“容易求得”……

先考虑一下LCT维护什么

定义$f0$为全0走过一条路径之后的答案，$f1$表示全1走过一条路径之后的答案

LCT需要维护的是splay中以x为根的子树里，从前往后遍历（即中序遍历）的$f0$和$f1$以及从后往前（即与前面完全相反的顺序）的$f0$和$f1$

比如有一棵splay，x是其中一个点，它在splay中有两个儿子，左儿子y和右儿子z，那么从前往后遍历就是路径y->x->z，从后往前就是路径z->x->y

然后思考，如果已经有了两个区间，该如何合并他们

假如说我们有两段计算出答案的区间，分别对应f0,f1和g0,g1。我们设合并后的答案是h0,h1，那么有如下式子：

h0=(~f0&g0)+(f0&g1)

h1=(~f1&g0)+(f1&g1)

为啥？

全0走到最后的话，先考虑两种情况

全0走到中间等于1的那几位，走后一半的答案等同于全1走后一半的这几位的答案

全0走到中间等于0的那几位，走后一半的答案等同于全0走后一半的这几位的答案

只需要把这两个答案加起来即可

（ps：这里默认f为前一半的答案，g为后一半的答案）

全1走到最后同理

然后就是几个细节

1.pushdown的时候因为有翻转标记，从前往后走和从后往前走的答案也要交换

2.按位贪心用1做位运算的时候，记得把1设成unsigned long long（简单来说就是设一个ull变量让它等于1）（我就是因为一开始直接用1做位运算结果死都调不出来……）
```
//minamoto
#include<iostream>
#include<cstdio>
#define ll unsigned long long
using std::swap;
using std::cout;
using std::endl;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline ll read(){
    #define num ch-'0'
    char ch;bool flag=0;ll res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
char obuf[1<<24],*o=obuf;
void print(ll x){
    if(x>9) print(x/10);
    *o++=x%10+48;
}
const int N=100005;
struct node{
    ll f0,f1;
    inline node operator +(const node &b)const
    {
        node a;
        a.f0=(~f0&b.f0)|(f0&b.f1);
        a.f1=(~f1&b.f0)|(f1&b.f1);
        return a;
    }
}f[N],l[N],r[N];
int fa[N],ch[N][2],s[N],rev[N],top,tot;
int ver[N<<1],head[N],Next[N<<1];
inline void add(int u,int v){
    ver[++tot]=v,Next[tot]=head[u],head[u]=tot;
    ver[++tot]=u,Next[tot]=head[v],head[v]=tot;
}
inline bool isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
#define ls ch[x][0]
#define rs ch[x][1]
inline void pushup(int x){
    l[x]=r[x]=f[x];
    if(ls) l[x]=l[ls]+l[x],r[x]=r[x]+r[ls];
    if(rs) l[x]=l[x]+l[rs],r[x]=r[rs]+r[x];
}
inline void pushr(int x){
    swap(ls,rs),swap(l[x],r[x]),rev[x]^=1;
}
inline void pushdown(int x){
    if(rev[x]&&x){
        pushr(ls),pushr(rs),rev[x]=0;
    }
}
void rotate(int x){
    int y=fa[x],z=fa[y],d=ch[y][1]==x;
    if(!isroot(y)) ch[z][ch[z][1]==y]=x;
    fa[x]=z,fa[y]=x,fa[ch[x][d^1]]=y,ch[y][d]=ch[x][d^1],ch[x][d^1]=y,pushup(y);
}
void splay(int x){
    s[top=1]=x;for(int i=x;!isroot(i);i=fa[i]) s[++top]=fa[i];
    while(top) pushdown(s[top--]);
    for(int y=fa[x],z=fa[y];!isroot(x);y=fa[x],z=fa[y]){
        if(!isroot(y))
        ((ch[y][1]==x)^(ch[z][1]==y))?rotate(x):rotate(y);
        rotate(x);
    }
    pushup(x);
}
void access(int x){
    for(int y=0;x;x=fa[y=x]){
        splay(x),rs=y,pushup(x);
    }
}
void makeroot(int x){
    access(x),splay(x),pushr(x);
}
void split(int x,int y){
    makeroot(x),access(y),splay(y);
}
void dfs(int u){
    for(int i=head[u];i;i=Next[i]){
        int v=ver[i];
        if(v==fa[u]) continue;
        fa[v]=u,dfs(v);
    }
    pushup(u);
}
int main(){
    //freopen("testdata.in","r",stdin);
    int n=read(),m=read(),k=read();
    for(int i=1;i<=n;++i){
        int x=read();ll y=read();
        switch(x){
            case 1:f[i]=(node){0,y};break;
            case 2:f[i]=(node){y,~0};break;
            case 3:f[i]=(node){y,~y};break;
        }
    }
    for(int i=1;i<n;++i){
        int u=read(),v=read();add(u,v);
    }
    dfs(1);
    while(m--){
        int opt=read(),x=read(),y=read();ll z=read();
        if(opt&1){
            split(x,y);ll ans=0,e=1;
            for(int i=k-1;i>=0;--i){
                if(l[y].f0&(e<<i)) ans|=e<<i;
                else if((l[y].f1&(e<<i))&&z>=(e<<i)) ans|=e<<i,z^=e<<i;
            }
            print(ans),*o++='\n';
        }
        else{
            switch(y){
                case 1:f[x]=(node){0,z};break;
                case 2:f[x]=(node){z,~0};break;
                case 3:f[x]=(node){z,~z};break;
            }
            splay(x);
        }
    }
    fwrite(obuf,o-obuf,1,stdout);
    return 0;
}
```

---

## 作者：Deep_Kevin (赞：7)

#  **正题**

      一看到这题就心碎emm，好好睡觉不行吗。。。

      关键看完这道题，你就要想到，用树链剖分+线段树来维护，因为在这方面线段树是最灵活而且是最万能的。我们就要想，怎么去进行线段树合并。

      首先，您不可能建2^64个线段树。然后第i个线段树维护i经过这个线段树的某个区间所留下来的值。

      这样的时间复杂的虽然比起暴力来好像快很多，但是细想还是不行。

      想着拆位优化。

      比如说当前的z是00101001.

      那么我们就可以取00000000~00101001.

      位运算就是每一位之间的操作都不影响，所以我们可以把它们拆成一位一位进去跑。

      如果第一位（最高位）放入一个0，跑出来的结果是0.

      放入一个1，跑出来的结果是1.

      那么我们肯定会优先选择有价值的，因为我们是从高位往底位做，所以就算后面的1全部取，也没有当前取1大，所以当前优先取大。

      那么我们对于每一个位置建立一棵线段树，然后进行维护。跑一遍合并之后发现我们的时间复杂度为

      m logn logn 64*2

     所以是接近1亿的。

     那么我们都说了，不同两位之间不会影响，何尝不把它们同时做，用unsigned long long 来存储呢?

     那么我们之前是对于每一位放0和放1跑，现在我们不如放000000...和111111...来跑。

    所以线段树中的每一个节点都只需要存两个值，一个是000000...放进该区间跑出来的权值，另一个是111111...放进该区间跑出来的权值。

     然后我们就发现，在向上维护的过程中遇到了麻烦。

     比如说00000000放入左子树跑出来的答案是01001011.

     但是右子树的节点只存储了两个值00000000放进去跑和11111111放进去跑。

     那么我们怎么向上维护呢？

     我们需要做的是不是将左子树中的1，改成这一位为1时放入右子树后的得出来的值。

     那么得出来的一个unsigned long long 我们把它设为ans

     ans中为1的条件是什么?

     左子树的答案中为1的那位，在右子树把1放进去时也为1.

     左子树的答案中为0的那位，在右子树把0放进去时也为1

     所以思考一下位运算，就可以作出O（1）的向上维护
```cpp
    ans[now][0]=(ans[rs[now]][1]&ans[ls[now]][0])|(ans[rs[now]][0]&(~ans[ls[now]][0]));
    ans[now][1]=(ans[rs[now]][1]&ans[ls[now]][1])|(ans[rs[now]][0]&(~ans[ls[now]][1]));
```

      然后依据这个来更新就可以了，这部分是关键哦~

     另外还要说的，因为位运算的操作不能颠倒，所以必须从x往y做。

     所以我们做的顺序可能是(7->1) (8->11)

     顺序就会有正和倒的区分，所以要建两棵线段树。

     最后把得出来的两个值（分别是把000...放进去和把111...放进去的权值）

     做一遍贪心（上面），就可以知道最大的v。

    
```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;

int ls[1000010],rs[1000010];//0为从左往右放，1为从右往左放 
unsigned long long ans[1000010][2][2];
int root;
int n,m,k;
unsigned long long t[100010];
int op[200010];
struct edge{
    int y,next;
}u[200010];
int first[200010];
int tot[200010],son[200010],top[200010],image[200010],fa[200010],dep[200010];
int len=0;
int v,opt;
unsigned long long tt;
unsigned long long piece=0-1;

void ins(int x,int y){
    len++;
    u[len].y=y;u[len].next=first[x];first[x]=len;
}

void dfs_1(int x){
    tot[x]=1;
    for(int i=first[x];i!=0;i=u[i].next){
        int y=u[i].y;
        if(y!=fa[x]){
            fa[y]=x;
            dep[y]=dep[x]+1;
            dfs_1(y);
            if(tot[y]>tot[son[x]]) son[x]=y;
            tot[x]+=tot[y];
        }
    }
}

void dfs_2(int x,int tp){
    top[x]=tp;image[x]=++len;
    if(son[x]!=0) dfs_2(son[x],tp);
    for(int i=first[x];i!=0;i=u[i].next){
        int y=u[i].y;
        if(y!=fa[x] && y!=son[x]) dfs_2(y,y);
    }
}

void update(int&now,int x,int y){
    if(now==0) now=++len;
    int mid=(x+y)/2;
    if(x==y){
        if(opt==1){
            ans[now][0][0]=ans[now][0][1]=(0&tt);
            ans[now][1][0]=ans[now][1][1]=(piece&tt);
        }
        else if(opt==2){
            ans[now][0][0]=ans[now][0][1]=(0|tt);
            ans[now][1][0]=ans[now][1][1]=(piece|tt);
        }
        else if(opt==3){
            ans[now][0][0]=ans[now][0][1]=(0^tt);
            ans[now][1][0]=ans[now][1][1]=(piece^tt);
        }
        return ;
    }
    if(v<=mid) update(ls[now],x,mid);
    else update(rs[now],mid+1,y);
    ans[now][0][0]=(ans[rs[now]][1][0]&ans[ls[now]][0][0])|(ans[rs[now]][0][0]&(~ans[ls[now]][0][0]));
    ans[now][1][0]=(ans[rs[now]][1][0]&ans[ls[now]][1][0])|(ans[rs[now]][0][0]&(~ans[ls[now]][1][0]));
    ans[now][0][1]=(ans[ls[now]][1][1]&ans[rs[now]][0][1])|(ans[ls[now]][0][1]&(~ans[rs[now]][0][1]));
    ans[now][1][1]=(ans[ls[now]][1][1]&ans[rs[now]][1][1])|(ans[ls[now]][0][1]&(~ans[rs[now]][1][1]));
}

unsigned long long get_change(int now,int l,int r,int x,int y,bool w,bool wh){
    if(l==x && r==y) return ans[now][w][wh];
    int mid=(x+y)/2;
    if(r<=mid) return get_change(ls[now],l,r,x,mid,w,wh);
    else if(mid<l) return get_change(rs[now],l,r,mid+1,y,w,wh);
    else{
    	unsigned long long temp;
        if(wh==false){
        	temp=get_change(ls[now],l,mid,x,mid,w,wh);
        	temp=(get_change(rs[now],mid+1,r,mid+1,y,true,wh)&temp)|(get_change(rs[now],mid+1,r,mid+1,y,false,wh)&(~temp));
        }
        else {
        	temp=get_change(rs[now],mid+1,r,mid+1,y,w,wh);
        	temp=(get_change(ls[now],l,mid,x,mid,true,wh)&temp)|(get_change(ls[now],l,mid,x,mid,false,wh)&(~temp));
        }
        return temp;
    }
}

int l[2][30],r[2][30];
int tota[2],total;

unsigned long long solve(){
    int x,y;
    unsigned long long z;
    scanf("%d %d %llu",&x,&y,&z);
    int tx=top[x],ty=top[y];
    bool tf=true;
    tota[0]=tota[1]=0;
    while(tx!=ty){
        if(dep[tx]>dep[ty]){
            swap(x,y);
            swap(tx,ty);
            tf^=true;
        }
        l[tf][++tota[tf]]=image[ty];
        r[tf][tota[tf]]=image[y];
        y=fa[ty];ty=top[y];
    }
    if(dep[x]>dep[y]){
        swap(x,y);
        tf^=true;
    }
    l[tf][++tota[tf]]=image[x];
    r[tf][tota[tf]]=image[y];
    unsigned long long op1=0,op2=0-1;
    for(int i=1;i<=tota[0];i++){
        op1=(get_change(root,l[0][i],r[0][i],1,n,true,true)&op1)|(get_change(root,l[0][i],r[0][i],1,n,false,true)&(~op1));
    	op2=(get_change(root,l[0][i],r[0][i],1,n,true,true)&op2)|(get_change(root,l[0][i],r[0][i],1,n,false,true)&(~op2));
    }
    for(int i=tota[1];i>=1;i--){
        op1=(get_change(root,l[1][i],r[1][i],1,n,true,false)&op1)|(get_change(root,l[1][i],r[1][i],1,n,false,false)&(~op1));
    	op2=(get_change(root,l[1][i],r[1][i],1,n,true,false)&op2)|(get_change(root,l[1][i],r[1][i],1,n,false,false)&(~op2));
    }
    unsigned long long temp=((unsigned long long)1<<63);
    unsigned long long vv=0;
    for(int i=63;i>=0;i--){
        if(op1&temp) vv+=temp;
        else if((op2&temp) && temp<=z){
            vv+=temp;
            z-=temp;
        }
    	temp>>=1;
    }
    return vv;
}

void change(){
    int x,y;
    unsigned long long z;
    scanf("%d %d %llu",&x,&y,&z);
    v=image[x];opt=y;
    tt=z;
    update(root,1,n);
}

int main(){
    scanf("%d %d %d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        scanf("%d %llu",&op[i],&t[i]);
    for(int i=1;i<=n-1;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        ins(x,y);
        ins(y,x);
    }
    dep[1]=1;dfs_1(1);
    len=0;dfs_2(1,1);
    len=0;
    for(int i=1;i<=n;i++){
        v=image[i];opt=op[i];
        tt=t[i];
        update(root,1,n);
    }
    int type;
    while(m--){
        scanf("%d",&type);
        if(type==1) printf("%llu\n",solve());
        else change();
    }
}
```

---

## 作者：FutaRimeWoawaSete (赞：3)

一道还行的题目吧，感觉 trick 比较简单。          

这道题其实就是[起床困难综合征](https://www.luogu.com.cn/problem/P2114)的加强版，其实没做过也没关系大概描述一下：假如要暴力跑链，我们从高位到低位考虑，枚举每一位是 0 还是 1 去跑，如果 0 跑出来就是 1 或者当前已经不能选 1 那么我们就填 0 否则填 1 ，这样贪心地做很明显可以保证答案的正确性。          

接着我们就考虑怎么把这个问题给进行拓展，我们不难发现我们如果拿到了 64 位里每一位填 0 和 1 是个什么情况我们就可以进行 $O(qk)$ 的判断，所以我们不妨考虑怎么维护这个东西。          

我最开始的时候是想做个树分块，毕竟这东西我觉得有点不会维护，不过 $O(n \sqrt n \log_n)$ 直接劝退好吗？于是考虑线段树，我们不妨树剖一下，然后我们对每一个区间记录一下一个全是 1 的数和全是 0 的数通过的情况，这个情况很明显可以压缩成一个数，接下来解决了合并的问题这道题就很简单了！            

首先如果你直接合的话这个时间复杂度不难证明是一个 $O(n\log_n^3)$ 的想法，所以我们只能考虑 $O(1)$ 合并，这里可能不是很好想，虽然你可以很简单滴猜到肯定是一堆位运算结合在一起，但是直接凑这个式子貌似不太好想，所以我们换一个角度。               

- 我们一个位一个位地考虑，它肯定在位运算下是相互独立的，所以我们单独对每个位考虑。         

- 先考虑让 1 从左到右。过如果当前左边让 1 过是 1 并且右边从 1 过是 1 的话答案就是 1 ； 如果当前左边让 1 过是 0 并且右边从 0 过是 1 的话答案也是 1 。其余情况 1 过答案都是 0 ，让 0 从左到右过的情况类似，从右到左的情况反过来就可以了。         
          
为了方便理解放一下从左到右让 1 过的伪代码：         

```res.ly = ((x.ly & y.ly) | ((~x.ly) & y.lx));//x,y是左右区间的情况，ly表示从左到右1过的情况，lx表示从左到右0过的情况 ```


接着我们维护一下一段区间从前到后和从后到前 1 过 和 0 过的情况，就可以做到 $O(n\log_n^2)$ 了 。         

感觉很平淡的一道 $Ynoi$ ，唯一亮点可能就是这个 $O(1)$ 转移。     

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define ll unsigned long long
const int Len = 2e5 + 5;
inline ll read() {
    char ch = getchar();
    ll x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
ll Maxn = 0 - 1,Minn,a[Len],val[Len]; 
int n,m,k,son[Len],siz[Len],dep[Len],fa[Len],id[Len],top[Len],opt[Len],head[Len],cnt,tot,aopt[Len];
struct Node
{
	ll lx,ly;
	ll rx,ry;
	Node(ll xx = 0 , ll yy = 0,ll xxx = 0,ll yyy = 0){lx = xx , ly = yy , rx = xxx , ry = yyy;}
}Forever_Pursuit , Used[Len][3] , ans[Len << 2];
int Cnt[5];
struct node
{
	int next,to;
}edge[Len << 2];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
void dfs1(int x,int f)
{
	fa[x] = f;
	dep[x] = dep[f] + 1;
	siz[x] = 1;
	int maxson = -1;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		dfs1(to , x);
		siz[x] += siz[to];
		if(siz[to] > maxson) maxson = siz[to] , son[x] = to;
	}
}
void dfs2(int x,int topf)
{
	top[x] = topf;
	id[x] = ++ tot;
	val[tot] = a[x];
	opt[tot] = aopt[x];
	if(!son[x]) return;
	dfs2(son[x] , topf);
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == fa[x] || to == son[x]) continue;
		dfs2(to , to);	
	} 
}
ll Calc(ll x,ll y,int z)
{
	if(z == 1) return x & y;
	if(z == 2) return x | y;
	if(z == 3) return x ^ y;
}
int ls(int x){return x << 1;}
int rs(int x){return x << 1 | 1;}
Node Caalc(Node x,Node y)
{
	Node res;
	res.lx = ((x.lx & y.ly) | ((~x.lx) & y.lx));
	res.ly = ((x.ly & y.ly) | ((~x.ly) & y.lx));//x,y是左右区间的情况，ly表示从左到右1过的情况，lx表示从左到右0过的情况 
	res.rx = ((y.rx & x.ry) | ((~y.rx) & x.rx));
	res.ry = ((y.ry & x.ry) | ((~y.ry) & x.rx));
	return res;
}
void build(int p,int l,int r)
{
	ans[p].lx = ans[p].rx = ans[p].ly = ans[p].ry = 0;
	if(l == r)
	{
		ans[p].lx = ans[p].rx = Calc(Minn , val[l] , opt[l]);
		ans[p].ly = ans[p].ry = Calc(Maxn , val[l] , opt[l]);
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	ans[p] = Caalc(ans[ls(p)] , ans[rs(p)]);
}
void update(int p,int l,int r,int idx,int Opt,ll num)
{
	if(l == r)
	{
		val[l] = num , opt[l] = Opt;
		ans[p].lx = ans[p].rx = Calc(Minn , val[l] , opt[l]);
		ans[p].ly = ans[p].ry = Calc(Maxn , val[l] , opt[l]);
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) update(ls(p) , l , mid , idx , Opt , num);
	else update(rs(p) , mid + 1 , r , idx , Opt , num);
	ans[p] = Caalc(ans[ls(p)] , ans[rs(p)]);
}
Node query(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) return ans[p];
	int mid = (l + r) >> 1;
	if(nr <= mid) return query(ls(p) , l , mid , nl , nr);
	if(nl >= mid + 1) return query(rs(p) , mid + 1 , r , nl , nr);
	return Caalc(query(ls(p) , l , mid , nl , nr) , query(rs(p) , mid + 1 , r , nl , nr));
}
void Updpoint(int x,int y,ll z){update(1 , 1 , n , id[x] , y , z);}
void Qrange(int x,int y)
{
	Forever_Pursuit.lx = Forever_Pursuit.ly = Forever_Pursuit.rx = Forever_Pursuit.ry = 0;
	Cnt[1] = Cnt[2] = 0;
	while(top[x] != top[y])
	{
		if(dep[top[x]] >= dep[top[y]]) 
		{
			Used[++ Cnt[1]][1] = query(1 , 1 , n , id[top[x]] , id[x]);
			x = fa[top[x]];
		}
		else
		{
			Used[++ Cnt[2]][2] = query(1 , 1 , n , id[top[y]] , id[y]);
			y = fa[top[y]];
		}
	}
	if(dep[x] > dep[y]) Used[++ Cnt[1]][1] = query(1 , 1 , n , id[y] , id[x]);
	else Used[++ Cnt[2]][2] = query(1 , 1 , n , id[x] , id[y]);
	for(int i = 1 ; i <= Cnt[1] ; i ++) swap(Used[i][1].lx , Used[i][1].rx) , swap(Used[i][1].ly , Used[i][1].ry);
	if(Cnt[1])
	{
		Forever_Pursuit = Used[1][1];
		for(int i = 2 ; i <= Cnt[1] ; i ++) Forever_Pursuit = Caalc(Forever_Pursuit , Used[i][1]);
		if(Cnt[2]) Forever_Pursuit = Caalc(Forever_Pursuit , Used[Cnt[2]][2]);
	}
	else Forever_Pursuit = Used[Cnt[2]][2];
	for(int i = Cnt[2] - 1 ; i >= 1 ; i --) Forever_Pursuit = Caalc(Forever_Pursuit , Used[i][2]);
}
signed main()
{
	n = read() , m = read() , k = read();
	for(int i = 1 ; i <= n ; i ++) aopt[i] = read() , a[i] = read();
	for(int i = 1 ; i < n ; i ++) 
	{
		int x,y;x = read() , y = read();
		add(x , y) , add(y , x);
	}
	dfs1(1 , 0);
	dfs2(1 , 1);
	build(1 , 1 , n);
	for(int i = 1 ; i <= m ; i ++)
	{
		ll OPT , x , y , z;
		OPT = read() , x = read() , y = read() , z = read();
		if(OPT == 1) 
		{
			Qrange(x , y);
			ll res = 0 , val = 0;
			for(int bit = 63 ; bit >= 0 ; bit --)
			{
				int res0 = (Forever_Pursuit.lx >> bit) & 1llu;
				int res1 = (Forever_Pursuit.ly >> bit) & 1llu;
				if(val + (1llu << bit) <= z && res0 < res1) val += (1llu << bit) , res += (1llu << bit);
				else res += (1LL * res0 << bit);
			}
			printf("%llu\n",res);
		}
		else Updpoint(x , y , z);
	}
	return 0;
}
```

---

## 作者：FlashHu (赞：3)

膜拜神犇出题人管理员！！膜拜yler和ZSY！！

没错yler连续教我这个蒟蒻写起床困难综合症和睡觉困难综合症%%%Orz，所以按位贪心的思路可以继承下来

这里最好还是写树剖吧，不过我根本不会，于是只好来个LCT，用unsigned long long维护链上双向的按位操作。具体方法yler已经讲得很好啦

注意因为信息的维护是有方向性的，所以pushdown要写规范。。。。。。
```cpp
#include<cstdio>
#define RG register
#define R RG int
#define I inline void
#define TP template<typename T>
#define lc c[x][0]
#define rc c[x][1]
#define G ch=getchar()
#define upd switch(y){\
	case 1:v[x]=(B){_0,z};break;\
	case 2:v[x]=(B){z,_I};break;\
	case 3:v[x]=(B){z,~z};\
}
typedef unsigned long long L;
const L _0=0ull,_1=1ull,_I=~_0;
const int N=100009;
struct B{
	L f0,f1;
	I merge(RG B x,RG B y){
		f0=(~x.f0&y.f0)|(x.f0&y.f1);
		f1=(~x.f1&y.f0)|(x.f1&y.f1);
	}
}v[N],b[N],e[N];
bool r[N];
int f[N],c[N][2];
TP I swap(RG T&x,RG T&y){
	RG T z=x;x=y;y=z;
}
TP I in(RG T&x){
	RG char G;
	while(ch<'-')G;
	x=ch&15;G;
	while(ch>'-')x*=10,x+=ch&15,G;
}
inline bool nroot(R x){
	return c[f[x]][0]==x||c[f[x]][1]==x;
}
I up(R x){//之前试着写数组发现WA了，原因是本来需要继续运算的信息又被覆盖掉，用结构体弄一下就好了
	b[x]=e[x]=v[x];
	if(lc)b[x].merge(b[lc],b[x]),e[x].merge(e[x],e[lc]);
	if(rc)b[x].merge(b[x],b[rc]),e[x].merge(e[rc],e[x]);
}
I rev(R x){
	swap(b[x],e[x]);swap(lc,rc);r[x]^=1;
}
I down(R x){
	if(r[x])rev(lc),rev(rc),r[x]=0;
}
I all(R x){
	if(nroot(x))all(f[x]);down(x);
}
I rot(R x){
	R y=f[x],z=f[y],k=c[y][1]==x,w=c[x][!k];
	if(nroot(y))c[z][c[z][1]==y]=x;c[x][!k]=y;c[y][k]=w;
	up(f[w]=y);f[y]=x;f[x]=z;
}
I splay(R x){
	all(x);R y;
	while(nroot(x)){
		if(nroot(y=f[x]))
			rot((c[f[y]][0]==y)^(c[y][0]==x)?x:y);
		rot(x);
	}
	up(x);
}
I access(R x){
	for(R y=0;x;y=x,x=f[x])
		splay(x),rc=y,up(x);
}
I mroot(R x){
	access(x);splay(x);rev(x);
}
int main(){
	R n,m,k,q,x,y;
	RG L i,z,g0,g1,w,ans;
	in(n);in(m);in(k);--k;
	for(x=1;x<=n;++x){
		in(y);in(z);upd;up(x);
	}
	for(i=1;i<n;++i){
		in(x);in(y);
		mroot(x);f[x]=y;
	}
	while(m--){
		in(q);in(x);in(y);in(z);
		if(q&1){
			mroot(x);access(y);splay(y);
			g0=b[y].f0;g1=b[y].f1;w=ans=_0;
			for(i=_1<<k;i;i>>=1)//和起床困难综合症一样贪心下去
				if(g0&i)ans|=i;
				else if((g1&i)&&(w|i)<=z)ans|=i,w|=i;
			printf("%llu\n",ans);
		}
		else{upd;splay(x);}
	}
	return 0;
}
```

---

## 作者：Cyhlnj (赞：3)

这道题是**NOI起床困难综合症**改编而来的

思路是一样的

这道题我们考虑用LCT维护，每个节点维护两个值

一个为中序遍历这棵子树的ans0，ans1（分别表示0和INF(二进制下全为1)跑的答案）

另一个为中序遍历的反向遍历这棵子树的ans0，ans1

还要记得保存这个点的初始操作


考虑合并，若知道的左边的f0，f1，右边的g0，g1，合并后的h0，h1  有

    h0 = (~f0 & g0) | (f0 & g1)

    h1 = (~f1 & g0) | (f1 & g1)

含义就是走完前面，是0的继续走0，不是的走1


注意LCT中Splay区间翻转时交换左右


最后按高位贪心跑一遍


---

```cpp
# include <bits/stdc++.h>
# define RG register
# define IL inline
# define Fill(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ul;
const int _(1e5 + 10);

IL ul Read(){
    char c = '%'; ul x = 0, z = 1;
    for(; c > '9' || c < '0'; c = getchar()) if(c == '-') z = -1;
    for(; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0';
    return x * z;
}

int n, m, fa[_], ch[2][_], rev[_], S[_];
struct Value{  ul f0, f1;  } G, val[_], lr[_], rl[_];

IL Value Merge(RG Value X, RG Value Y){
    G.f0 = (~X.f0 & Y.f0) | (X.f0 & Y.f1);
    G.f1 = (~X.f1 & Y.f0) | (X.f1 & Y.f1);
    return G;
}

IL bool Son(RG int x){  return ch[1][fa[x]] == x;  }

IL bool Isroot(RG int x){  return ch[0][fa[x]] != x && ch[1][fa[x]] != x;  }

IL void Update(RG int x){
    lr[x] = rl[x] = val[x];
    if(ch[0][x]) lr[x] = Merge(lr[ch[0][x]], lr[x]), rl[x] = Merge(rl[x], rl[ch[0][x]]);
    if(ch[1][x]) lr[x] = Merge(lr[x], lr[ch[1][x]]), rl[x] = Merge(rl[ch[1][x]], rl[x]);
}

IL void Reverse(RG int x){  swap(lr[x], rl[x]); swap(ch[0][x], ch[1][x]); rev[x] ^= 1;  }

IL void Pushdown(RG int x){  if(!rev[x]) return; Reverse(ch[0][x]); Reverse(ch[1][x]); rev[x] = 0;  }

IL void Rotate(RG int x){
    RG int y = fa[x], z = fa[y], c = Son(x);
    if(!Isroot(y)) ch[Son(y)][z] = x; fa[x] = z;
    ch[c][y] = ch[!c][x]; fa[ch[c][y]] = y;
    ch[!c][x] = y; fa[y] = x;
    Update(y);
}

IL void Splay(RG int x){
    S[++S[0]] = x;
    for(RG int y = x; !Isroot(y); y = fa[y]) S[++S[0]] = fa[y];
    while(S[0]) Pushdown(S[S[0]--]);
    for(RG int y = fa[x]; !Isroot(x); Rotate(x), y = fa[x])
        if(!Isroot(y)) Son(x) ^ Son(y) ? Rotate(x) : Rotate(y);
    Update(x);
}

IL void Access(RG int x){  for(RG int y = 0; x; y = x, x = fa[x]) Splay(x), ch[1][x] = y, Update(x);  }

IL void Makeroot(RG int x){  Access(x); Splay(x); Reverse(x);  }

IL void Split(RG int x, RG int y){  Makeroot(x); Access(y); Splay(y);  }

IL void Link(RG int x, RG int y){  Makeroot(x); fa[x] = y;  }

IL ul Query(RG int x, RG int y, RG ul z){
    RG ul ans = 0, t = 1; Split(x, y);
    for(RG int k = 63; k >= 0; k--)
        if(lr[y].f0 & (t << k)) ans += (t << k);
        else if(lr[y].f1 & (t << k) && z >= (t << k)) z -= (t << k), ans += (t << k);
    return ans;
}

int main(RG int argc, RG char *argv[]){
    n = Read(); m = Read(); Read(); RG ul e = 0;
    for(RG int i = 1; i <= n; i++){
        RG int x = Read(); RG ul y = Read();
        if(x == 1) val[i] = (Value){e, y};
        if(x == 2) val[i] = (Value){y, ~e};
        if(x == 3) val[i] = (Value){y, ~y};
    }
    for(RG int i = 1, x, y; i < n; i++) x = Read(), y = Read(), Link(x, y);
    while(m--){
        RG ul op = Read(), i = Read(), x = Read(), y = Read();
        if(op == 1) printf("%llu\n", Query(i, x, y));
        else{
            if(x == 1) val[i] = (Value){e, y};
            if(x == 2) val[i] = (Value){y, ~e};
            if(x == 3) val[i] = (Value){y, ~y};
            Splay(i);
        }
    }
    return 0;
}

```


---

## 作者：CyanSineSin (赞：2)

题目里讲得非常清楚，就是把 睡觉困难综合征 搬到树上了。

那我们先回想一下 睡觉困难综合征 是怎么做的：

首先我们设了两个值，一个在二进制下全是 $1$ （下文中为 $mx$ ），一个全是 $0$ （下文中为 $mn$ ）。

然后我们直接对序列中每一个操作用这两个值进行模拟。

因为二进制运算每个位独立，所以我们可以得到一开始的时候每个位选  $0$ 或 $1$ 时最后能够得到 $0$ 还是 $1$ 。

然后我们就贪心进行选取 $0/1$ 就好了。

先考虑一个序列如何动态维护这个问题。

我们可以开一棵线段树，维护区间内一开始是 $mx$ 和 $mn$ ，一直把这个区间模拟完之后的结果。

那么问题来了，如何合并两个区间的答案呢？

我们先按位分析：现在知道这位选 $1$ 和 $0$ 分别在两边会得到什么结果，那我们先模拟这位选什么，用在左边的结果再拿到右边去看放进去会得到什么结果。这样就可以得到整个区间这位选 $1$ 或 $0$ 的结果了。

那么我们一共枚举最多 $64$ 位， $64$ 的常数瞬间爆炸，所以肯定不能按位枚举。

想一想如果优化这个过程。

我们可以先得到左边全选 $1$ 或 $0$ 时会得到的结果上哪些位是 $1$ ，哪些位是 $0$ 。然后去右边区间看下这些是 $1$ 的位上哪些又会变成  $0$ 或 $1$ ，是 $0$ 的位上哪些又是 $1$ 或 $0$ 。

首先设 $tmp1$ 表示经过左边之后是 $1$ 的位置， $tmp0$ 表示经过左边之后是 $0$ 的位置。

那么 `tmp1=now,tmp0=~now;`（ $now$ 表示当前左边全选 $0$ 或 $1$ 的结果）

然后得到答案 `ans=(tmp1&right1)|(tmp0&right0)`。（ $right0/1$ 表示右边全选 $0/1$ 的结果）

就相当于把左边结果的 $0$ 和 $1$ 分别处理，把是$0$或$1$的位上的右边的结果直接搬过来。

因为这一位经过左边后变成了 $0/1$，所以这一位经过右边之后就应该是右边一开始这位选 $0/1$ 的结果。

这样我们就做到了 $\operatorname{O}(1)$ 合并两个区间的结果。

最后再用树链剖分把这个过程搬到树上就好了。

这道题的两个端点的顺序是有影响的。所以要在树剖里分类讨论，还要维护区间倒着来的结果。

~~细节很多WA了很久，不愧是Ynoi~~

代码：
```
#include<cstdio>
#include<vector>
using namespace std;
vector<unsigned long long> e[100010];
struct node
{
	unsigned long long one,zero;
}nodes[400010],exnodes[400010],emp,ret,exret;//nodes是正着来，exnodes是反着来 
const unsigned long long cone=1;//1常量，免得1<<i爆掉 
unsigned long long mx,mn;//全为1和全为0的量 
unsigned long long n,m,k,opx[100010],op[100010],u,v,opt,opa,opb,opc;
unsigned long long siz[100010],son[100010],dep[100010],fa[100010],hb[100010],dfn[100010],ton[100010],cnt;
bool flag,exflag;
void dfs1(unsigned long long x,unsigned long long las)
{
	fa[x]=las;
	dep[x]=dep[las]+cone;
	siz[x]=cone;
	for(unsigned long long i=0;i<e[x].size();++i)
	{
		unsigned long long y=e[x][i];
		if(y^las)
		{
			dfs1(y,x);
			siz[x]+=siz[y];
			if(siz[son[x]]<siz[y])	son[x]=y;
		}
	}
}
void dfs2(unsigned long long x,unsigned long long las,bool heavy)
{
	dfn[x]=++cnt;
	ton[cnt]=x;
	if(heavy)	hb[x]=hb[las];
	else	hb[x]=x;
	if(son[x])	dfs2(son[x],x,1);
	for(unsigned long long i=0;i<e[x].size();++i)
	{
		unsigned long long y=e[x][i];
		if((y^las)&&(y^son[x]))	dfs2(y,x,0);
	}
}
node merge(node one,node ano)
{
	node res=emp;
	unsigned long long tmp1=one.one;
	unsigned long long tmp0=~tmp1;
	res.one=(tmp1&ano.one)|(tmp0&ano.zero);
	tmp1=one.zero;
	tmp0=~tmp1;
	res.zero=(tmp1&ano.one)|(tmp0&ano.zero);//全选0/1分别维护 
	return res;
}
void build(unsigned long long l,unsigned long long r,unsigned long long x)
{
	if(l^r)
	{
		unsigned long long mid=(l+r)>>cone;
		build(l,mid,x<<cone);
		build(mid+cone,r,x<<cone|cone);
		nodes[x]=merge(nodes[x<<cone],nodes[x<<cone|cone]);
		exnodes[x]=merge(exnodes[x<<cone|cone],exnodes[x<<cone]);//反着来的肯定也要反着合并 
	}
	else
	{
		nodes[x]=exnodes[x]=emp;
		if(op[ton[l]]==cone)//初值直接模拟就好 
		{
			nodes[x].one&=opx[ton[l]];
			exnodes[x].one&=opx[ton[l]];
			nodes[x].zero&=opx[ton[l]];
			exnodes[x].zero&=opx[ton[l]];
		}
		else if(op[ton[l]]==2)
		{
			nodes[x].one|=opx[ton[l]];
			exnodes[x].one|=opx[ton[l]];
			nodes[x].zero|=opx[ton[l]];
			exnodes[x].zero|=opx[ton[l]];
		}
		else
		{
			nodes[x].one^=opx[ton[l]];
			exnodes[x].one^=opx[ton[l]];
			nodes[x].zero^=opx[ton[l]];
			exnodes[x].zero^=opx[ton[l]];
		}
	}
}
void update(unsigned long long l,unsigned long long r,unsigned long long x,unsigned long long pos,unsigned long long oper,unsigned long long val)
{
	if(l^r)
	{
		unsigned long long mid=(l+r)>>cone;
		if(pos<=mid)	update(l,mid,x<<cone,pos,oper,val);
		else	update(mid+cone,r,x<<cone|cone,pos,oper,val);
		nodes[x]=merge(nodes[x<<cone],nodes[x<<cone|cone]);
		exnodes[x]=merge(exnodes[x<<cone|cone],exnodes[x<<cone]);
	}
	else
	{
		op[ton[l]]=oper;
		opx[ton[l]]=val;
		nodes[x]=exnodes[x]=emp;
		if(op[ton[l]]==cone)
		{
			nodes[x].one&=opx[ton[l]];
			exnodes[x].one&=opx[ton[l]];
			nodes[x].zero&=opx[ton[l]];
			exnodes[x].zero&=opx[ton[l]];
		}
		else if(op[ton[l]]==2)
		{
			nodes[x].one|=opx[ton[l]];
			exnodes[x].one|=opx[ton[l]];
			nodes[x].zero|=opx[ton[l]];
			exnodes[x].zero|=opx[ton[l]];
		}
		else
		{
			nodes[x].one^=opx[ton[l]];
			exnodes[x].one^=opx[ton[l]];
			nodes[x].zero^=opx[ton[l]];
			exnodes[x].zero^=opx[ton[l]];
		}
	}
}
void find(unsigned long long l,unsigned long long r,unsigned long long x,unsigned long long fr,unsigned long long ba)//y用的find 
{
	if(l>ba||r<fr)	return;
	if(l>=fr&&r<=ba)
	{
		if(!flag)
		{
			ret=nodes[x];
			flag=cone;
		}
		else	ret=merge(nodes[x],ret);//LCA到y中是dfs序从小到大，y的dfs序大，所以要放到后面，并和正序的结果合并
	}
	else
	{
		unsigned long long mid=(l+r)>>cone;
		find(mid+cone,r,x<<cone|cone,fr,ba);//y放到后面 
		find(l,mid,x<<cone,fr,ba);
	}
}
void exfind(unsigned long long l,unsigned long long r,unsigned long long x,unsigned long long fr,unsigned long long ba)//x用的exfind 
{
	if(l>ba||r<fr)	return;
	if(l>=fr&&r<=ba)
	{
		if(!exflag)
		{
			exret=exnodes[x];
			exflag=cone;
		}
		else	exret=merge(exret,exnodes[x]);//x到LCA中是dfs序从大到小，x的dfs序大，所以要放到后面，并和倒序的结果合并
	}
	else
	{
		unsigned long long mid=(l+r)>>cone;
		exfind(mid+cone,r,x<<cone|cone,fr,ba);//x放到后面 
		exfind(l,mid,x<<cone,fr,ba);
	}
}
node LCA(unsigned long long x,unsigned long long y)
{
	unsigned long long fx=hb[x],fy=hb[y];
	flag=exflag=0;//如果之前没有值，就直接把值赋给ret/exret 
	ret=exret=emp;
	while(fx^fy)
	{
		if(dep[fx]>dep[fy])//分类讨论 
		{
			exfind(cone,n,cone,dfn[fx],dfn[x]);//x这边是从x到LCA往上，但x的dfs序更大 
			x=fa[fx];
			fx=hb[x];
		}
		else
		{
			find(cone,n,cone,dfn[fy],dfn[y]);//y这边是从LCA到y往下，但y的dfs序更大
			y=fa[fy];
			fy=hb[y];
		}
	}
	if(dep[x]<dep[y])	find(cone,n,cone,dfn[x],dfn[y]);
	else	exfind(cone,n,cone,dfn[y],dfn[x]);
	return merge(exret,ret);//x这边在前面 
}
unsigned long long solve(node how,unsigned long long lim)//贪心选取 
{
	unsigned long long res=0,used=0;
	for(unsigned long long i=k-1;i>=0;--i)
	{
		if(how.zero&(cone<<i))	res+=(cone<<i);
		else if((how.one&(cone<<i))&&used+(cone<<i)<=lim)
		{
			res+=(cone<<i);
			used+=(cone<<i);
		}
		if(i==0)	break;
	}
	return res;
}
int main()
{
	scanf("%llu %llu %llu",&n,&m,&k);
	mx=-cone;
	mn=0;
	emp.one=mx;
	emp.zero=mn;
	for(unsigned long long i=cone;i<=n;++i)	scanf("%llu %llu",&op[i],&opx[i]);
	for(unsigned long long i=cone;i<n;++i)
	{
		scanf("%llu %llu",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	} 
	dfs1(cone,cone);
	dfs2(cone,cone,0);
	build(cone,n,cone);
	for(unsigned long long i=cone;i<=m;++i)
	{
		scanf("%llu %llu %llu %llu",&opt,&opa,&opb,&opc);
		if(opt==2)	update(cone,n,cone,dfn[opa],opb,opc);
		else	printf("%llu\n",k?solve(LCA(opa,opb),opc):0);
	}
	return 0;
}
```

---

## 作者：1saunoya (赞：2)

这题就一个合并过程需要说吧。。

考虑最 $naive$ 的做法。

维护 $64$ 线段树，表示相对 $bit$ 。

初始这位为$1$应该变成多少用 $s_{p,1}$表示。

初始这位为$0$应该变成多少用 $s_{p,0}$表示。

这个想法是 $\log^2 / \log^3$的，显然过不去。

考虑一起维护。

$s_{ls,0}=1 \& s_{rs,1}=1$ 就是 $s_{p,0}=1$。

$s_{ls,1}=0 \& s_{rs,0}=1$ 就是 $s_{p,1}=1$。

所以变得非常简单了，由于上树，要考虑正反问题所以就变得非常长（

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
using namespace std;
using u=unsigned long long;
int n,m,k;
const int N=1e5+1;
vector<int>adj[N];
int sz[N];
int fa[N];
int son[N];
int d[N];
void dfs(int u,int p){
	d[u]=d[p]+1;
	sz[u]=1;
	fa[u]=p;
	for(auto v:adj[u])
		if(v^p){
			dfs(v,u);
			sz[u]+=sz[v];
			if(sz[v]>sz[son[u]])son[u]=v;
		}
}
int dfn[N],idx=0;
int top[N];
int rev[N];
void dfs2(int u,int t){
	dfn[u]=++idx;
	rev[idx]=u;
	top[u]=t;
	if(son[u])dfs2(son[u],t);
	for(auto v:adj[u])
		if(!top[v])dfs2(v,v);
}
int op[N];
u val[N];
u calc(u x,int pos){
	if(op[pos]==1)
		return x&val[pos];
	if(op[pos]==2)
		return x|val[pos];
	if(op[pos]==3)
		return x^val[pos];
}
struct data{
	u s,g;
	u revs,revg;
}tr[N<<2];
data merge(const data&x,const data&y){
	u s0=x.s;u g0=x.g;
	u s1=y.s;u g1=y.g;
	data res;
	res.s=(~s0&s1)|(s0&g1);
	res.g=(~g0&s1)|(g0&g1);
	s0=x.revs;
	s1=y.revs;
	g0=x.revg;
	g1=y.revg;
	swap(s0,s1);
	swap(g0,g1);
	res.revs=(~s0&s1)|(s0&g1);
	res.revg=(~g0&s1)|(g0&g1);
	return res;
}
void up(int p){tr[p]=merge(tr[p<<1],tr[p<<1|1]);}
void build(int l,int r,int p){
	if(l==r){
		tr[p].s=tr[p].revs=calc(0,rev[l]);
		tr[p].g=tr[p].revg=calc(-1,rev[l]);
		return;
	}
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	up(p);
}
void upd(int l,int r,int p,int x){
	if(l==r){
		tr[p].s=tr[p].revs=calc(0,rev[l]);
		tr[p].g=tr[p].revg=calc(-1,rev[l]);
		return;
	}
	int mid=l+r>>1;
	if(x<=mid)upd(l,mid,p<<1,x);
	else upd(mid+1,r,p<<1|1,x);
	up(p);
}
data query(int ql,int qr,int l,int r,int p){
	if(ql<=l&&r<=qr)return tr[p];
	int mid=l+r>>1;
	if(qr<=mid)return query(ql,qr,l,mid,p<<1);
	else if(ql>mid)return query(ql,qr,mid+1,r,p<<1|1);
	else return merge(query(ql,qr,l,mid,p<<1),query(ql,qr,mid+1,r,p<<1|1));
}
data query(int x,int y){
	vector<data>p[2];
	while(top[x]!=top[y]){
		if(d[top[x]]>=d[top[y]]){
			p[0].push_back(query(dfn[top[x]],dfn[x],1,n,1));
			x=fa[top[x]];
		}else{
			p[1].push_back(query(dfn[top[y]],dfn[y],1,n,1));
			y=fa[top[y]];
		}
	}
	if(d[x]>=d[y])p[0].push_back(query(dfn[y],dfn[x],1,n,1));
	else p[1].push_back(query(dfn[x],dfn[y],1,n,1));
	data res;
	bool flag=0;
	for(auto&i:p[0])swap(i.s,i.revs),swap(i.g,i.revg);
	for(auto i:p[0]){
		if(!flag)res=i,flag=1;
		else res=merge(res,i);
	}
	reverse(p[1].begin(),p[1].end());
	for(auto i:p[1]){
		if(!flag)res=i,flag=1;
		else res=merge(res,i);
	}
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>n>>m>>k;
	rep(i,1,n){
		int x;
		u y;
		cin>>x>>y;
		op[i]=x;
		val[i]=y;
	}
	rep(i,2,n){
		int x,y;
		cin>>x>>y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs(1,0);
	dfs2(1,1);
	build(1,n,1);
	while(m--){
		int o,x,y;
		u z;
		cin>>o>>x>>y>>z;
		if(o==2){
			op[x]=y;
			val[x]=z;
			upd(1,n,1,dfn[x]);
		}else{
			data res=query(x,y);
			u ans=0;
			per(i,k-1,0){
				if(res.s>>i&1)ans|=1ull<<i;
				else if(res.g>>i&1&&(1ull<<i)<=z){ans|=1ull<<i;z-=1ull<<i;}
			}
			cout<<ans<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：租酥雨 (赞：2)

题面描述[https://www.luogu.org/problemnew/show/3613](https://www.luogu.org/problemnew/show/3613)

原题NOI2014起床困难综合症[https://www.luogu.org/problemnew/show/2114](https://www.luogu.org/problemnew/show/2114)做完原题就可以尝试解决这道题目了


题意：一棵n个节点的树，每个节点上有一个位运算操作符(与、或、异或)和一个数字，走过一个点的时候当前值就会和这个数字做相应运算。现在给定x,y,z，要求在[0,z]中选区一个初值使从x点走到y点的最终结果最大。支持动态修改点上的操作符与数字。


~~我太菜了完全不知道树链剖分去维护什么只知道LCT一顿乱搞。。。~~

咳咳，首先原题[起床困难综合症]得要切掉，然后你就知道这题的大致做法了了：记录初始以全0和全1走完后得到的答案，然后按位贪心即可（选高位一定比选低位优，就算低位全都可以选，因为这是二进制呀）。

为了方便起见，下文中所有的“答案”指以全0全1走完后得到的两个值，以0为下标表示是以全0开始的，1为下标表示是以全1开始的。


####LCT维护啥？


LCT维护的东西是：在以这个点为根的splay中（我没有说这个点就是splay的根，是指以这个点为根的子树），从前往后经过每一个点的答案以及从后往前走经过每一个点的答案。

比如说，有一个叫做1号节点的点，在以她为根的splay中还有点2,3，其中2是她的左儿子，3是她的右儿子，那么在1号点上维护的东西就应该是：依次经过2-1-3的最终结果，以及依次经过3-1-2的最终结果。


####那么两个结果怎么合并呢？


假如说我们有两段带合并的已经计算出答案的区间，分别对应f0,f1和g0,g1。我们设合并后的答案是h0,h1，那么有如下式子：

h0=(~f0&g0)+(f0&g1)

h1=(~f1&g0)+(f1&g1)

原因很简单，请自己YY~


####需要注意的点：

以往的LCT维护的都是子树信息（废话，这题不也是），但同时也是无序的。这题维护的子树信息和左右子树的循序是有关系的，所以原来的翻转操作就需要略为修改。具体详见代码。


####code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define ll unsigned long long
const int N = 100005;
struct data
{
    ll f0,f1;
    data operator + (const data &b) const
        {
            data ans;
            ans.f0=(~f0&b.f0)|(f0&b.f1);
            ans.f1=(~f1&b.f0)|(f1&b.f1);
            return ans;
        }
}f[N],lo[N],ro[N];
int n,m,fa[N],ls[N],rs[N],rev[N],Stack[N],top;
ll gi()
{
    ll x=0,w=1;char ch=getchar();
    while ((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if (ch=='-') w=0,ch=getchar();
    while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return w?x:-x;
}
bool isroot(int x){return ls[fa[x]]!=x&&rs[fa[x]]!=x;}
void reverse(int x){swap(ls[x],rs[x]);swap(lo[x],ro[x]);rev[x]^=1;}
void pushdown(int x){if (rev[x]) reverse(ls[x]),reverse(rs[x]),rev[x]=0;}
void pushup(int x)
{
    lo[x]=ro[x]=f[x];
    if (ls[x]) lo[x]=lo[ls[x]]+lo[x],ro[x]=ro[x]+ro[ls[x]];
    if (rs[x]) lo[x]=lo[x]+lo[rs[x]],ro[x]=ro[rs[x]]+ro[x];
}
void R_rotate(int x)
{
    int y=fa[x],z=fa[y];
    ls[y]=rs[x];
    if (rs[x]) fa[rs[x]]=y;
    fa[x]=z;
    if (!isroot(y)) if (y==ls[z]) ls[z]=x;else rs[z]=x;
    rs[x]=y;fa[y]=x;
    pushup(y);
}
void L_rotate(int x)
{
    int y=fa[x],z=fa[y];
    rs[y]=ls[x];
    if (ls[x]) fa[ls[x]]=y;
    fa[x]=z;
    if (!isroot(y)) if (y==ls[z]) ls[z]=x;else rs[z]=x;
    ls[x]=y;fa[y]=x;
    pushup(y);
}
void splay(int x)
{
    Stack[top=1]=x;
    for (int i=x;!isroot(i);i=fa[i])
        Stack[++top]=fa[i];
    while (top) pushdown(Stack[top--]);
    while (!isroot(x))
    {
        int y=fa[x],z=fa[y];
        if (isroot(y))
            if (x==ls[y]) R_rotate(x);
            else L_rotate(x);
        else
            if (y==ls[z])
                if (x==ls[y]) R_rotate(y),R_rotate(x);
                else L_rotate(x),R_rotate(x);
            else
                if (x==ls[y]) R_rotate(x),L_rotate(x);
                else L_rotate(y),L_rotate(x);
    }
    pushup(x);
}
void access(int x){for (int y=0;x;y=x,x=fa[x]) splay(x),rs[x]=y,pushup(x);}
void makeroot(int x){access(x);splay(x);reverse(x);}
void split(int x,int y){makeroot(x);access(y);splay(y);}
void link(int x,int y){makeroot(x);fa[x]=y;}
int main()
{
    n=gi();m=gi();gi();
    for (int i=1;i<=n;i++)
    {
        int x=gi();ll y=gi();
        if (x==1) f[i]=(data){0,y};
        if (x==2) f[i]=(data){y,~0};
        if (x==3) f[i]=(data){y,~y};
    }
    for (int i=1;i<n;i++)
    {
        int x=gi(),y=gi();
        link(x,y);
    }
    while (m--)
    {
        int opt=gi(),x=gi(),y=gi();ll z=gi();
        if (opt==1)
        {
            split(x,y);ll e=1,ans=0;
            for (int k=63;k>=0;k--)
                if (lo[y].f0&(e<<k))
                    ans+=e<<k;
                else if (lo[y].f1&(e<<k)&&z>=(e<<k))
                    z-=e<<k,ans+=e<<k;
            printf("%llu\n",ans);
        }
        if (opt==2)
        {
            makeroot(x);
            if (y==1) f[x]=(data){0,z};
            if (y==2) f[x]=(data){z,~0};
            if (y==3) f[x]=(data){z,~z};
            pushup(x);
        }
    }
    return 0;
}

```

---

## 作者：Yansuan_HCl (赞：1)

没有子树和，事全局平衡二叉树很好的练习题。

首先可以维护一个函数 $f_{a,o,x}(n)=((n\ \text{and}\ a)\ \text{or}\ o)\ \text{xor}\ x$。可以知道这是支持复合的。所以其具有结合律，上线段树维护。

$O(n\log^2 n)$ 的做法比较 naive，这是因为树剖与线段树没有以正确的姿势结合起来。

为了摊平线段树的 $\log$，可以预处理每个点的轻子树大小 $sz(u)-sz(\text{hson}(u))$。对每条重链建立线段树。线段树处理区间 $[l,r]$ 时，选取 $\text{mid}$ 为 $[l,r]$ 中轻子树大小前缀和的带权中点。

这样，树剖每跳一次，在线段树上的深度也相应减小。每次跳轻边，当次查询在线段树上的深度一定已经跳到了 $O(1)$。其实，等价于把全局平衡二叉树的二叉树换成 WBLT. 因此复杂度为 $O(n \log n)$。优势是 Leafy 且比较好写。

代码（丑见谅）：

```cpp
#include <bits/stdc++.h>
#define ms(x, v) memset(x, v, sizeof(x))
#define il __attribute__((always_inline)) static
#define U(i,l,r) for(int i(l),END##i(r);i<=END##i;++i)
#define D(i,r,l) for(int i(r),END##i(l);i>=END##i;--i)
using namespace std;

typedef unsigned long long ll;
template <class T> using BS = basic_string<T>;

template <class T> void rd(T& s) {
	int c = getchar(); T f = 1; s = 0;
	while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
	while (isdigit(c)) { s = s * 10 + (c ^ 48); c = getchar(); }
	s *= f;
}
template <class T, class... Y> void rd(T& x, Y&... y) { rd(x), rd(y...); }
#define meow(...) fprintf(stderr, __VA_ARGS__)

const int N = 100005;
const ll INF = 0xFFFFFFFFFFFFFFFF;

int n, Q, K;

BS<int> g[N];
int dep[N], fa[N], siz[N], hson[N];
void df1(int u, int f) {
	dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1;
	for (int v : g[u]) if (v != f) {
		df1(v, u);
		siz[u] += siz[v];
		if (siz[v] > siz[hson[u]])
			hson[u] = v;
	}
}
int top[N], lz[N], len[N], dfn[N];
void df2(int u, int f, int t) {
	static int pt; dfn[u] = ++pt; top[u] = t; len[u] = 1;
	if (hson[u]) df2(hson[u], u, t), len[u] = len[hson[u]] + 1;
	lz[dfn[u]] = siz[u] - siz[hson[u]];
	for (int v : g[u]) if (v != f && v != hson[u])
		df2(v, u, v);
}

struct T {
	ll a, o, x;
	T() : a(INF), o(0), x(0) {}
	T(int op, ll v) : a(INF), o(0), x(0) {
		if (op == 1) a = v;
		else if (op == 2) o = v;
		else x = v;
	}
} in[N];
T operator + (T l, T r) {
	l.a &= r.a; l.o &= r.a; l.x &= r.a;
	l.o |= r.o; l.x &= ~r.o;
	l.x ^= r.x;
	return l;
}

struct ST {
	struct Node {
		int ls, rs, mid;
		T up, dn;
	}; vector<Node> tr;
	int L, R;
	
	int build(int l, int r) {
		assert(l <= r);
		int p = tr.size(), ls, rs, mid; T up, dn; tr.push_back(Node());
		if (l == r) { tr[p].up = tr[p].dn = in[l]; return p; }
		
		int w = 0, h = 0; U (i, l, r) w += lz[i];
		for (int i = l; h += lz[i], i <= r; ++i)
			if (h * 2 >= w) {
				mid = i;
				break;
			}
		if (mid == r) --mid;
		assert(mid >= l && mid < r);
		ls = build(l, mid); rs = build(mid + 1, r);
		
		up = tr[rs].up + tr[ls].up;
		dn = tr[ls].dn + tr[rs].dn;
		tr[p] = {ls, rs, mid, up, dn};
		return p;
	}
	void modify(int x, T &v, int p, int l, int r) {
		auto &[ls, rs, mid, up, dn] = tr[p];
		if (l == r) { up = dn = v; return; }
		
		if (x <= mid) modify(x, v, ls, l, mid);
		else modify(x, v, rs, mid + 1, r);
		
		up = tr[rs].up + tr[ls].up;
		dn = tr[ls].dn + tr[rs].dn;
	} void modify(int x, T &v) { modify(x, v, 0, L, R); }
	
	T v;
	void qU(int b, int e, int p, int l, int r) {
		auto &[ls, rs, mid, up, dn] = tr[p];
		if (b <= l && e >= r) { v = v + up; return; }
		
		if (e > mid) qU(b, e, rs, mid + 1, r);
		if (b <= mid) qU(b, e, ls, l, mid);
	} T qU(int b, int e) { v = T(); qU(b, e, 0, L, R); return v; }
	
	void qD(int b, int e, int p, int l, int r) {
		auto &[ls, rs, mid, up, dn] = tr[p];
		if (b <= l && e >= r) { v = v + dn; return; }
		
		if (b <= mid) qD(b, e, ls, l, mid);
		if (e > mid) qD(b, e, rs, mid + 1, r);
	} T qD(int b, int e) { v = T(); qD(b, e, 0, L, R); return v; }
} tr[N];

T query(int u, int v) {
	T a, b, r;
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) {
			a = a + tr[top[u]].qU(dfn[top[u]], dfn[u]);
			u = fa[top[u]];
		} else {
			b = tr[top[v]].qD(dfn[top[v]], dfn[v]) + b;
			v = fa[top[v]];
		}
	}
	if (dep[u] < dep[v])
		r = tr[top[u]].qD(dfn[u], dfn[v]);
	else
		r = tr[top[u]].qU(dfn[v], dfn[u]);
	return a + r + b;
}
ll greedy(T &t, ll m) {
	ll v = 0, w = 0;
	D (i, K - 1, 0) {
#define B(s) (((s) >> (i)) & 1)
		ll d = (B(t.a) | B(t.o)) ^ B(t.x),
			e = B(t.o) ^ B(t.x);
		if (e) {
			w |= 1ull << i;
		} else if (d && (v | (1ull << i)) <= m) {
			w |= 1ull << i; v |= 1ull << i;
		}
	}
	return w;
}
int main() {
	rd(n, Q, K);
	int io[N]; ll iv[N]; U (i, 1, n) rd(io[i], iv[i]);
	U (i, 2, n) { int u, v; rd(u, v); g[u] += v; g[v] += u; }
	df1(1, 1);
	df2(1, 1, 1);
	U (i, 1, n) in[dfn[i]] = T(io[i], iv[i]);
	
	U (i, 1, n) if (i == top[i]) {
		tr[i].L = dfn[i], tr[i].R = dfn[i] + len[i] - 1;
		tr[i].tr.reserve((tr[i].R - tr[i].L) * 2 + 5);
		tr[i].build(tr[i].L, tr[i].R);
	}
	
	while (Q--) {
		ll op, x, y, z; rd(op, x, y, z);
		if (op == 1) {
			T t = query(x, y);
			ll ans = greedy(t, z);
			printf("%llu\n", ans);
		} else {
			T v(y, z);
			tr[top[x]].modify(dfn[x], v);
		}
	}
}
```

~~在本题中由于[常数较大](https://www.luogu.com.cn/record/103851897)跑不过[树剖](https://www.luogu.com.cn/record/103850937)。并且因为过大的常数，这种方法不能通过 DDP 加强版。~~

---

## 作者：Sshenyyyu (赞：1)

这题可用树链剖分或LCT做(然而我太弱了不会LCT)

对于每一组询问，我们可以将二进制分离，分部计算，按起床困难综合症的贪心思路来就行了，然而这样做时间复杂度O(nklog^2n)，再看时间就1s，肯定超时

树链剖分肯定是无法避免的，我们可以试着把k消去

我们先对位运算进行分析，可以发现如果某一位要&0或|1，那么这一位肯定固定下来了，而如果是&1或|0，则相当于没操作过，所以对于初始值，某一位上没有经过&0或|1操作，这一位才受初始值影响。

那么，对于每一连串操作，我们把它压缩成等效的&与|上一个数，设我&x,如果x某一位上为0，表示无论什么数经过这一串操作这一位都要变成0，反之则是不确定，|
的数某一位为1， 表示无论什么数经过这一串操作这一位都要变成1，反之则是不确定

这样，我们就可以通过位运算，快速求出x~y上等效的&与|然后再考虑不确定的位置上为0还是1，时间O(nk+nlong^2n)

压缩时线段树的过程pushup并不好写，这里讲一下

假设我们已经求出了左子树应为&x1，|y1，右子树为&x2，|y2，右子树上的异或和为n

由于|1的位上如果^1就会转化为&0,&0也同理，所以&x1，|y1只经过异或操作后会变为

x1'=(x1|n)&(~(y1&n))
y1'=(y1&(~n))|((~x1)&n)

为什么呢，我们以某一位为例(以下等号表示等效，而不是相等)

```
&0^0=&0
&0^1=&1
&1^0=&1
&1^1=&1
```

它等效于x1|n

```
|0^0=&1
|0^1=&1
|1^0=&1
|1^1=&0
```

它等效于~(y1|n)

或运算也可以这样表示，这样pushup就写好了，最后把等效运算摆在一块时统计的原理也是这样

还有对于链上操作，可能有时要求编号从大到小的等效运算，所以正反都要存一下(顺序一定要考虑好，我在这上面挂了n次)

```cpp
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;
const int N=100005;
int n,m,mk,u,v,ch[N],i,c,tot[2];
int head[N],Next[N*2],adj[N*2],k,dfn[N],siz[N],fa[N],son[N],p[N],top[N],dep[N];
ull treeand[2][N*5],treeor[2][N*5],treexor[N*5],ulmx,num[N],w;
ull staand[2][N],staor[2][N],ansxor,ansand,ansor,ans,x,staxor[2][N],s[N];
void Push(int u,int v)
{
    Next[++k]=head[u];
    head[u]=k;
    adj[k]=v;
}
void dfs(int i,int f)
{
    int j;
    fa[i]=f;
    siz[i]=1;
    for(j=head[i];j!=0;j=Next[j])
        if(adj[j]!=f)
        {
            dep[adj[j]]=dep[i]+1;
            dfs(adj[j],i);
            siz[i]+=siz[adj[j]];
            if(siz[son[i]]<siz[adj[j]])
                son[i]=adj[j];
        }
}
void dfs2(int i,int t)
{
    int j;
    top[i]=t;
    dfn[i]=++k;
    if(son[i]!=0)
        dfs2(son[i],t);
    for(j=head[i];j!=0;j=Next[j])
        if(adj[j]!=fa[i]&&adj[j]!=son[i])
            dfs2(adj[j],adj[j]);
}
void pushup(int i)
{
    treeand[0][i]=treeand[0][i*2+1]&(((treeand[0][i*2]|treexor[i*2+1])&(~(treeor[0][i*2]&treexor[i*2+1])))|treeor[0][i*2+1]);
    treeor[0][i]=treeor[0][i*2+1]|(((treeor[0][i*2]&(~treexor[i*2+1]))|((~treeand[0][i*2])&treexor[i*2+1]))&treeand[0][i*2+1]);
    treeand[1][i]=treeand[1][i*2]&(((treeand[1][i*2+1]|treexor[i*2])&(~(treeor[1][i*2+1]&treexor[i*2])))|treeor[1][i*2]);
    treeor[1][i]=treeor[1][i*2]|(((treeor[1][i*2+1]&(~treexor[i*2]))|((~treeand[1][i*2+1])&treexor[i*2]))&treeand[1][i*2]);
    treexor[i]=treexor[i*2]^treexor[i*2+1];
}
void Pushand(int i,int l,int r,int x,ull y)
{
    if(l==r)
    {
        treeand[0][i]=treeand[1][i]=y;
        return;
    }
    int mid=(l+r)/2;
    if(mid>=x)
        Pushand(i*2,l,mid,x,y);
    else
        Pushand(i*2+1,mid+1,r,x,y);
    pushup(i);
}
void Pushor(int i,int l,int r,int x,ull y)
{
    if(l==r)
    {
        treeor[0][i]=treeor[1][i]=y;
        return;
    }
    int mid=(l+r)/2;
    if(mid>=x)
        Pushor(i*2,l,mid,x,y);
    else
        Pushor(i*2+1,mid+1,r,x,y);
    pushup(i);
}
void Pushxor(int i,int l,int r,int x,ull y)
{
    if(l==r)
    {
        treexor[i]=y;
        return;
    }
    int mid=(l+r)/2;
    if(mid>=x)
        Pushxor(i*2,l,mid,x,y);
    else
        Pushxor(i*2+1,mid+1,r,x,y);
    pushup(i);
}
void Queryandor(int i,int l,int r,int ll,int rr,int f)
{
    if(l>=ll&&r<=rr)
    {
        staand[f][++tot[f]]=treeand[f][i];
        staor[f][tot[f]]=treeor[f][i];
        staxor[f][tot[f]]=treexor[i];
        ansxor^=treexor[i];
        return;
    }
    int mid=(l+r)/2;
	if(mid<rr)
		Queryandor(i*2+1,mid+1,r,ll,rr,f);
	if(mid>=ll)
		Queryandor(i*2,l,mid,ll,rr,f);
}
void Query(int u,int v)
{
    int f=1;
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]])
        {
            u^=v^=u^=v;
            f^=1;
        }
        Queryandor(1,1,n,dfn[top[u]],dfn[u],f);
        u=top[u];
        u=fa[u];
    }
    if(dep[u]<dep[v])
    {
        u^=v^=u^=v;
        f^=1;
    }
    Queryandor(1,1,n,dfn[v],dfn[u],f);
}
int main(){
    scanf("%d %d %d",&n,&m,&mk);
    ulmx--;
    for(i=1;i<=n;i++)
		scanf("%d %llu",&ch[i],&num[i]);
    for(i=1;i<n;i++)
    {
        scanf("%d %d",&u,&v);
        Push(u,v);
        Push(v,u);
    }
    k=0;
    dfs(1,0);
    dfs2(1,1);
    for(i=1;i<=n;i++)
        Pushand(1,1,n,i,ulmx);
    for(i=1;i<=n;i++)
    {
        if(ch[i]==1)
            Pushand(1,1,n,dfn[i],num[i]);
        if(ch[i]==2)
            Pushor(1,1,n,dfn[i],num[i]);
        if(ch[i]==3)
            Pushxor(1,1,n,dfn[i],num[i]);
    }
    while(m--)
    {
        scanf("%d %d %d %llu",&c,&u,&v,&w);
        if(c==2)
        {
            if(ch[u]==1)
                Pushand(1,1,n,dfn[u],ulmx);
            if(ch[u]==2)
                Pushor(1,1,n,dfn[u],0);
            if(ch[u]==3)
                Pushxor(1,1,n,dfn[u],0);
            ch[u]=v;
            if(ch[u]==1)
                Pushand(1,1,n,dfn[u],w);
            if(ch[u]==2)
                Pushor(1,1,n,dfn[u],w);
            if(ch[u]==3)
                Pushxor(1,1,n,dfn[u],w);
        }
        else
        {
            tot[0]=tot[1]=0;
            ansxor=0;
            Query(u,v);
            ansand=ulmx;
            ansor=0;
            s[tot[1]+tot[0]+1]=0;
            for(i=1;i<=tot[0];i++)
				s[tot[1]+tot[0]-i+1]=s[tot[1]+tot[0]-i+2]^staxor[0][i];
            for(i=tot[1];i>=1;i--)
				s[i]=s[i+1]^staxor[1][i];
            for(i=1;i<=tot[1];i++)
            {
                ansand|=(staor[1][i]&(~s[i+1]))|((~staand[1][i])&s[i+1]);
                ansor&=(staand[1][i]|s[i+1])&(~(staor[1][i]&s[i+1]));
                ansor|=(staor[1][i]&(~s[i+1]))|((~staand[1][i])&s[i+1]);
                ansand&=(staand[1][i]|s[i+1])&(~(staor[1][i]&s[i+1]));
            }
            for(i=tot[0];i>=1;i--)
            {
                ansand|=(staor[0][i]&(~s[tot[0]+tot[1]-i+2]))|((~staand[0][i])&s[tot[0]+tot[1]-i+2]);
                ansor&=(staand[0][i]|s[tot[0]+tot[1]-i+2])&(~(staor[0][i]&s[tot[0]+tot[1]-i+2]));
                ansor|=(staor[0][i]&(~s[tot[0]+tot[1]-i+2]))|((~staand[0][i])&s[tot[0]+tot[1]-i+2]);
                ansand&=(staand[0][i]|s[tot[0]+tot[1]-i+2])&(~(staor[0][i]&s[tot[0]+tot[1]-i+2]));
            }
            x=0;
            ans=0;
            for(i=mk-1;i>=0;i--)
                if(((ansand>>i)&1)==0||((ansor>>i)&1)==1)
                    ans|=(((ansand>>i)&1)&((ansor>>i)&1))<<i;
                else
                    if(((ansxor>>i)&1)==1)
                        ans|=1ull<<i;
                    else
                        if((x|(1ull<<i))<=w)
                        {
                            x|=1ull<<i;
                            ans|=1ull<<i;
                        }
            printf("%llu\n",ans);
        }
    }
}

```
PS:其他dalao的代码怎么这么短，好像就我写得最长了...

---

## 作者：SrsgPrince_ (赞：0)

# Luogu P5354 [Ynoi2017] 由乃的 OJ Solution

这题有弱化版：[P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)。

题面传送门：[P5354 [Ynoi2017] 由乃的 OJ](https://www.luogu.com.cn/problem/P5354)。

推荐在我的 [博客](https://www.luogu.com.cn/blog/fy123333/LuoguP5354Solution) 中查看。

## 题目分析 Hint

题目：给一棵有 $n$ 个点的树，每一个点包裹一个位运算 $opt$ 和一个权值 $x$，位运算有 `&`，`|`，`^` 三种，分别用 $1,2,3$ 表示。

每次询问包含三个整数 $x,y,z$，初始选定一个数 $v$。然后 $v$ 依次经过从 $x$ 到 $y$ 的所有节点，每经过一个点 $i$，v 就变成了 $v opt_i x_i$，所以她想问你，最后到 $y$ 时，希望得到的值尽可能大，并求最大值。给定的初始值 $v$ 必须在 $[0,z]$ 之间。

对于修改操作，每次三个整数 $x,y,z$，表示把 $x$ 点的操作改为 $y$，数值改为 $z$。

数据范围：$0 \leq n,m \leq 1 \times 10^5$，操作的值小于 $2^{64}$。

这道题是上述题目的带修，如果没有这个带修，那么就是跑出来所有都是 $0$ 和 $1$ 的答案，然后高位到地位贪心解决，那现在解决树上带修，因为这个询问操作是从 $x$ 到 $y$ 的一条链上的，所以我们可以用轻松维护链信息的数据结构来修改，那就可以用线段树+树剖，或者是 LCT。那么我们首先会想到把这条 $x-y$ 拆位出来，然后按照弱化版的想法，贪心解决。但是这里合并的复杂度 $O(k)$ 的，如果是树剖总复杂度 $O(kn\log^2n)$，LCT $O(kn\log n)$，带上常数很难过。

所以我们要降低合并信息的复杂度，那么我们可以考虑维护中序遍历初始为 $0$ 和反中序遍历初始为 $1$ 的值，我们要让值尽可能的大，那么让总结果的每一位尽可能是 $1$，那么需要两种情况：第一种是一个区间初始为 $0$ 的值的第 $k$ 为 $0$，并且另一个区间初始为 $0$ 的值为 $1$；第二种是第一个区间初始为 $0$ 的第 $k$ 为的值是 $1$，并且另一个区间初始位 $1$ 的值为 $1$。那么有如下式子。

```cpp
// merge
TreeNode ret;
ret.res1=(~lft.res1&rgt.res1)|(lft.res1&rgt.res2);
ret.res2=(~lft.res2&rgt.res1)|(lft.res2&rgt.res2);
```

这里的 $res1$ 指的是初始为 $0$，$res2$ 是指初始为 $1$。那么就把合并信息复杂度降到了 $O(1)$。注意这道题 $k$ 在 $64$，需要开 unsigned long long。

下面给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const unsigned long long maxn=1e6+10;
unsigned long long n,m,k,mn,mx;
unsigned long long fa[maxn],chd[2][maxn],stk[maxn],top,rev[maxn];
struct TreeNode{
    unsigned long long res1,res2;
}val[maxn],head[maxn],tail[maxn];
// 省略上文提到的 merge 操作
inline bool nRoot(register unsigned long long x){
    return chd[0][fa[x]]==x||chd[1][fa[x]]==x;
}
inline void pushUp(register unsigned long long x){
    head[x]=tail[x]=val[x];
    if(chd[0][x]){
        head[x]=merge(head[chd[0][x]],head[x]);
        tail[x]=merge(tail[x],tail[chd[0][x]]);
    }
    if(chd[1][x]){
        head[x]=merge(head[x],head[chd[1][x]]);
        tail[x]=merge(tail[chd[1][x]],tail[x]);
    }
}
inline void reverse(register unsigned long long x){
    swap(head[x],tail[x]);
    swap(chd[0][x],chd[1][x]);
    rev[x]^=1;
}
inline void pushDown(register unsigned long long x){
    if(rev[x]){
        if(chd[0][x])
            reverse(chd[0][x]);
        if(chd[1][x])
            reverse(chd[1][x]);
        rev[x]=0;
    }
}
inline void rotate(register unsigned long long x){
    register unsigned long long y=fa[x],z=fa[y],k=(chd[1][y]==x),w=chd[!k][x];
    if(nRoot(y))
        chd[chd[1][z]==y][z]=x;
    chd[!k][x]=y;
    chd[k][y]=w;
    if(w)
        fa[w]=y;
    fa[y]=x;
    fa[x]=z;
    pushUp(y);
    pushUp(x);
}
inline void pushTag(register unsigned long long x){
    register unsigned long long y=x;
    top=0;
    stk[++top]=y;
    while(nRoot(y))
        stk[++top]=y=fa[y];
    while(top)
        pushDown(stk[top--]);
}
inline void splay(register unsigned long long x){
    pushTag(x);
    while(nRoot(x)){
        register unsigned long long y=fa[x];
        if(nRoot(y))
            rotate((chd[0][y]==x^chd[0][fa[y]]==y)?x:y);
        rotate(x);
    }
    pushUp(x);
}
inline void access(register unsigned long long x){
    for(register unsigned long long y=0;x;x=fa[y=x]){
        splay(x);
        chd[1][x]=y;
        pushUp(x);
    }
}
inline void makeRoot(register unsigned long long x){
    access(x);
    splay(x);
    reverse(x);
}
inline void split(register unsigned long long x,register unsigned long long y){
    makeRoot(x);
    access(y);
    splay(y);
}
inline void link(register unsigned long long x,register unsigned long long y){
    makeRoot(x);
    fa[x]=y;
}
signed main(){
    mn=0;
    mx=~mn;
    quickRead<unsigned long long,unsigned long long,unsigned long long>(n,m,k);
    for(register unsigned long long i=1,u,v;i<=n;++i){
        quickRead<unsigned long long,unsigned long long>(u,v);
        if(u==1)
            val[i]=(TreeNode){mn,v};
        if(u==2)
            val[i]=(TreeNode){v,mx};
        if(u==3)
            val[i]=(TreeNode){v,~v};
    }
    for(register unsigned long long i=1,u,v;i<n;++i){
        quickRead<unsigned long long,unsigned long long>(u,v);
        link(u,v);
    }
    for(register unsigned long long i=1,opt,lft,rgt,w;i<=m;++i){
        quickRead<unsigned long long,unsigned long long,unsigned long long,unsigned long long>(opt,lft,rgt,w);
        if(opt==1){
            split(lft,rgt);
            register TreeNode tmp=head[rgt];
            register unsigned long long res=0;
            for(register long long j=0x3f;j>=0;--j){
                if(tmp.res1&(1ull<<j))
                    res+=(1ull<<j);
                else if(tmp.res2&(1ull<<j)&&w>=(1ull<<j)){
                    res+=(1ull<<j);
                    w-=(1ull<<j);
                }
            }
            quickWrite(res,'\n');
        }
        if(opt==2){
            if(rgt==1)
                val[lft]=(TreeNode){mn,w};
            if(rgt==2)
                val[lft]=(TreeNode){w,mx};
            if(rgt==3)
                val[lft]=(TreeNode){w,~w};
            splay(lft);
        }
    }
    return 0;
}
```


---

## 作者：pokefunc (赞：0)

# P5354 [Ynoi2017]由乃的OJ

## Preface

自己的由乃题一血，写篇题解纪念一下。

## Description

给定一颗 $n$ 个结点的树，每个结点都有一个权值 $a_i$ 和一个位运算符 $\mathrm{op}_i$。

有 $m$ 次操作，包含以下两种：

- 给定 $x$，修改 $a_x$ 与 $\mathrm{op}_x$；
- 给定 $x,y,z$，求 $v\in [0..z]$ 使得 $v$ 沿点 $x$ 到点 $y$ 的路径移动，移动到点 $i$ 就会进行操作 $v \ \mathrm{op}_i \ a_i \to v$，在完成所有操作之后 $v$ 最大，求出这个最大值。

$n,m \le 10^5,\mathrm{op} \in \{\mathrm{and,or,xor}\}$，任意时刻 $a_i,z < 2^k$，$k \le 64$。

## Sol

思路不是那么好想的树剖+线段树。

直接考虑用树剖转换为区间问题。

由于本题中的运算都是位运算，因此每一位是独立的，这一点就可以考虑使用线段树维护某个区间内每一位在 $v$ 的对应位取 $0/1$ 时这一位的最终运算结果。

举个例子：假设区间为 $(1,\mathrm{and}),(3,\mathrm {xor}),(2,\mathrm{or})$，数值转写为二进制后为 $01,11,10$，那么 $v$ 从左往右低到高第 $i$ 位的取值为 $j$ 时的运算结果如下：

|       | $j=0$ | $j=1$ |
| ----- | ----- | ----- |
| $i=1$ | $1$   | $0$   |
| $i=2$ | $1$   | $1$   |

这个信息是可以 $O(k)$ 合并的，只要把把左边的值代入到右边进行求值即可。

由于从左往右的答案和从右往左的答案不一定一样，并且树剖中线段树维护的区间是在链上从上到下编号的，故在链合并的时候需要两个方向的信息（$u$ 到 $\mathrm{LCA}(u,v)$ 为向上，$\mathrm{LCA(u,v)}$ 到 $v$ 为向下），因此两个方向的信息都要维护。

我们回到原问题考虑如何计算答案。

我们采用贪心策略，从 $z$ 范围内的最高位开始贪。考虑到 $2^x > \sum_{i=1}^{x-1}2^i$，因此如果在第 $x$ 位上存在一种取值使得在进行了操作之后结果的这一位上能取到 $1$ 并且符合值域要求，那么我们就一定能要这一位贪下来，在答案上加上 $2^x$。

~~到此问题就解决了。时间复杂度 $O(mk\log^2 n)$。~~

然后您看到这道题250ms的时限和 $k=64$ 陷入了沉思。

这复杂度显然跑不过好吧。想办法优化。

方法也很简单：我们充分利用位运算性质，把上述的信息压进 `unsigned long long`，就把 $k$ 成功优化掉了。

最终时间复杂度 $O(m \log^2 n)$。

细节详见代码。

## Tips

- 链合并的细节非常多，详见代码。

## Code

```cpp
#include<cstdio>
#include<algorithm>
const int M=1e5+5;
typedef unsigned long long ull;
inline int read(){int x(0),op(0);char ch=getchar();while(ch<'0'||ch>'9')op|=(ch==45),ch=getchar();while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();return op?-x:x;}
inline int ssread(){int x;scanf("%d",&x);return x;}
inline ull uread(){ull x;scanf("%llu",&x);return x;}
#ifndef ONLINE_JUDGE
#define read ssread
#endif
int n,m,K;
struct edge{
	int v,nxt;
}e[M<<1];
int etot,h[M];
int fa[M],dep[M],top[M],dfn[M],siz[M],son[M],rev[M],DFN;
ull a[M];
int OP[M];
void dfs1(int u,int f){//树剖第一次dfs
	fa[u]=f;dep[u]=dep[f]+1;siz[u]=1;
	for(int i=h[u],v;v=e[i].v,i;i=e[i].nxt)if(v!=f){
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int tp){//树剖第二次dfs
	dfn[u]=++DFN;rev[DFN]=u;top[u]=tp;
	if(!son[u])return;
	dfs2(son[u],tp);
	for(int i=h[u],v;v=e[i].v,i;i=e[i].nxt)if(v!=son[u]&&v!=fa[u])dfs2(v,v);
}
struct node{//用于记录区间信息的结构体
	ull lef0,lef1,rig0,rig1;
	/*
	lef0：从左开始走，取0得到的值
	lef1：从左开始走，取1得到的值
	rig0：从右开始走，取0得到的值
	rig1：从右开始走，取1得到的值
	*/
	node(ull x=0,ull y=-1,ull z=0,ull w=-1){lef0=x,lef1=y,rig0=z,rig1=w;}
};
node merge(node x,node y){
	return (node){
		//这里的逻辑是：枚举靠前区间的值，以此计算靠后区间的值
		(~x.lef0&y.lef0)|(x.lef0&y.lef1),
		(x.lef1&y.lef1)|(~x.lef1&y.lef0),
		(~y.rig0&x.rig0)|(y.rig0&x.rig1),
		(y.rig1&x.rig1)|(~y.rig1&x.rig0)
	};
}
namespace segtree{//线段树
	#define ls (p<<1)
	#define rs ((p<<1)|1)
	#define mid ((s+t)>>1)
	node T[M<<2];
	void pushup(int p){
		T[p]=merge(T[ls],T[rs]);
	}
	void setp(int p,ull x,int op){//设置某个点的状态
		if(op==1)T[p].lef0=T[p].rig0=0,T[p].lef1=T[p].rig1=x;
		else if(op==2)T[p].lef0=T[p].rig0=x,T[p].lef1=T[p].rig1=-1;
		else T[p].lef0=T[p].rig0=x,T[p].lef1=T[p].rig1=~x;
	}
	void build(int p=1,int s=1,int t=n){
		if(s==t){
			setp(p,a[rev[s]],OP[rev[s]]);
			return;
		}
		build(ls,s,mid);build(rs,mid+1,t);
		pushup(p);
	}
	void modify(int pos,ull x,int op,int p=1,int s=1,int t=n){
		if(s==t){
			setp(p,x,op);
			return;
		}
		if(pos<=mid)modify(pos,x,op,ls,s,mid);
		else modify(pos,x,op,rs,mid+1,t);
		pushup(p);
	}
	node query(int l,int r,int p=1,int s=1,int t=n){
		if(l<=s&&t<=r)return T[p];
		if(l<=mid){
			if(r>mid)return merge(query(l,r,ls,s,mid),query(l,r,rs,mid+1,t));
			else return query(l,r,ls,s,mid);
		}
		else return query(l,r,rs,mid+1,t);
	//一定要注意区间的合并问题！
	}
}
void mdf(int pos,ull x,int op){
	segtree::modify(dfn[pos],x,op);
}
ull qry(int u,int v,ull w){//核心部分：链的合并
	node lc,rc;
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			lc=merge(segtree::query(dfn[top[u]],dfn[u]),lc);
			//细节1：树剖是从下到上跳的，故新的链是不断地并在前面得到的链的前端
			u=fa[top[u]];
		}
		else{
			rc=merge(segtree::query(dfn[top[v]],dfn[v]),rc);
			v=fa[top[v]];
		}
	}
	bool flg=1;
	if(dep[u]<dep[v])std::swap(u,v),std::swap(lc,rc),flg=0;
	std::swap(rc.lef0,rc.rig0),std::swap(rc.lef1,rc.rig1);
	//细节2：为了链的方向的统一方便合成最终链，需要把靠上（默认为v）的链左右颠倒
	node ans=merge(rc,merge(segtree::query(dfn[v],dfn[u]),lc));
	if(flg)std::swap(ans.lef0,ans.rig0),std::swap(ans.lef1,ans.rig1);
	//细节3：此时的链左端是v右端是u，故需要将答案链左右颠倒；但是如果u,v已经交换了就不用颠倒
	ull res=0;
	for(int i=K-1;~i;--i){
		ull l0=ans.lef0>>i&1,l1=ans.lef1>>i&1;
		if(l0)res|=1ull<<i;//可以那就尽量白嫖
		else if(l1&&(1ull<<i)<=w)res|=1ull<<i,w-=1ull<<i;//前文提到的贪心结论：能拿高位一定要拿
	}
	return res;
}
void adde(int u,int v){
	e[++etot]=(edge){v,h[u]};
	h[u]=etot;
}
signed main(){
	n=read();m=read();K=read();
	for(int i=1;i<=n;++i)OP[i]=read(),a[i]=uread();
	for(int i=1;i<n;++i){
		int u=read(),v=read();
		adde(u,v);adde(v,u);
	}
	dfs1(1,1);
	dfs2(1,1);
	segtree::build();
	while(m--){
		int op=read(),u=read(),v=read();
		ull w=uread();
		if(op==1)printf("%llu\n",qry(u,v,w));
		else mdf(u,w,v);
	}
	return 0;
}
```



---

## 作者：Jμdge (赞：0)

怎么说...或许是 LCT 常数问题，或许是洛谷四负优化问题，总之跑得比较慢...

# noteskey

这道题关键只在如果合并两端区间，至于维护无论是 树剖加线段树 或是 LCT 都是 ojbk 的

## build

我们先处理两个信息，一个是所有位上为 0 的数经过当前点会变成什么 (x0) ，以及所有位上为 1 的数经过当前点会变成什么(x1)

然后我们考虑现在处理出了两个区间的更变信息，然后我们要把两段信息合并，那么我们设前面一段为 $(f0,f1)$ ，后一段为 $(g0,g1)$ ，那么我们接下来要求出 $(h0,h1)$

我们首先考虑 h0 ，那么有：全为 0 的数经过 f0 之后有些位上变成了 0 ，然后经过 g0 ，即 ~$f0\&g0$， 全为 0 的数经过 f0 之后有些位上变成了 1 ，然后经过 g1 ，即 $f0\&g1$

所以， $h0=$~$f0\&g0+f0\&g1$ 

同理， $h1=$~$f1\&g0+f1\&g1$


## update

考虑更新，那么我们把当然点信息修改并 splay ，沿路修改节点信息

## query

考虑查询时贪心的从高位到低位计算最大贡献，鉴于有 最大值 的限制，我们每次加上一个贡献之前要比较该贡献是否小于当前限制，小于则累加贡献，并将限制减去该贡献

# code 

自带大常数的 LCT ，请放心食用
  
```
//by Judge
#include<cstdio>
#include<cstring>
#include<iostream>
#define Rg register
#define fp(i,a,b) for(Rg int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(Rg int i=(a),I=(b)-1;i>I;--i)
#define go(G,u) for(Rg int i=G.head[u],v=G.e[i].to;i;v=G.e[i=G.e[i].nxt].to)
#define ll unsigned long long
using namespace std;
const int inf=1e9+7;
const int M=1e5+3;
typedef int arr[M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline ll read(){ ll x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} char sr[1<<21],z[20];int CCF=-1,Z;
inline void Ot(){fwrite(sr,1,CCF+1,stdout),CCF=-1;}
inline void print(ll x,char chr='\n'){
    if(CCF>1<<20)Ot(); while(z[++Z]=x%10+48,x/=10);
    while(sr[++CCF]=z[Z],--Z);sr[++CCF]=chr;
} int n,m,k;
struct node{ ll f0,f1;
	inline node operator +(const node& b)const{
		return (node){(~f0&b.f0)|(f0&b.f1),(~f1&b.f0)|(f1&b.f1)};
	}
}f[M],l[M],r[M];
namespace LCT{ arr fa,s,rev; int ch[M][2],top,tot;
	inline bool isroot(int x){
		return ch[fa[x]][0]^x&&ch[fa[x]][1]^x;
	}
	#define ls ch[x][0]
	#define rs ch[x][1]
	inline void pushup(int x){ l[x]=r[x]=f[x];
		if(ls) l[x]=l[ls]+l[x],r[x]=r[x]+r[ls];
		if(rs) l[x]=l[x]+l[rs],r[x]=r[rs]+r[x];
	}
	inline void pushr(int x){
		swap(ls,rs),swap(l[x],r[x]),rev[x]^=1;
	}
	inline void pushdown(int x){
		if(rev[x]&&x) pushr(ls),pushr(rs),rev[x]=0;
	}
	inline void rotate(int x){
		int y=fa[x],z=fa[y],d=ch[y][1]==x;
		if(!isroot(y)) ch[z][ch[z][1]==y]=x;
		fa[x]=z,fa[y]=x,fa[ch[x][d^1]]=y;
		ch[y][d]=ch[x][d^1],ch[x][d^1]=y,pushup(y);
	}
	inline void splay(int x){
		s[top=1]=x; for(Rg int i=x;!isroot(i);i=fa[i]) s[++top]=fa[i];
		while(top) pushdown(s[top--]);
		for(int y=fa[x],z=fa[y];!isroot(x);rotate(x),y=fa[x],z=fa[y])
			if(!isroot(y)) rotate((ch[y][1]==x)^(ch[z][1]==y)?x:y);
		pushup(x);
	}
	inline void access(int x){
		for(Rg int y=0;x;x=fa[y=x])
			splay(x),rs=y,pushup(x);
	}
	inline void makeroot(int x){
		access(x),splay(x),pushr(x);
	}
	inline void split(int x,int y){
		makeroot(x),access(y),splay(y);
	}
} using namespace LCT;
struct Gr{ int pat,head[M];
	struct Edge{ int to,nxt; }e[M<<1];
	inline void add(int u,int v){
		e[++pat]={v,head[u]},head[u]=pat;
		e[++pat]={u,head[v]},head[v]=pat;
	}
}G;
void dfs(int u){
	go(G,u) if(v^fa[u])
		fa[v]=u,dfs(v); pushup(u);
}
int main(){ int op,x,y;
	n=read(),m=read(),k=read();
	fp(i,1,n){ int x=read(); ll y=read();
		switch(x){
			case 1: f[i]=(node){0,y}; break;
			case 2: f[i]=(node){y,~0}; break;
			case 3: f[i]=(node){y,~y}; break;
		}
	}
	fp(i,2,n) x=read(),y=read(),G.add(x,y);
	for(dfs(1);m;--m){
		op=read(),x=read(),y=read(); ll z=read();
		if(op&1){ split(x,y); ll ans=0,e=1;
			fd(i,k-1,0) if(l[y].f0&(e<<i)) ans|=e<<i;
				else if(l[y].f1&(e<<i)&&z>=(e<<i)) ans|=e<<i,z^=e<<i;
			print(ans);
		} else{
			switch(y){
				case 1: f[x]=(node){0,z}; break;
				case 2: f[x]=(node){z,~0}; break;
				case 3: f[x]=(node){z,~z}; break;
			} splay(x);
		}
	} return Ot(),0;
}
```



---

## 作者：Great_Influence (赞：0)

这道题可以用LCT维护，当然也能够用全局平衡二叉树维护了。

做法和LCT差不多，需要判断一些东西。

时间复杂度$O(n\log n)$，比目前所有LCT都快，但是被ZKW的$log^2n$大佬脚踩。

代码:
```cpp
#include<bits/stdc++.h>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define rep(i,a,b) for(register int i=(a);i<(b);++i)
#define pb push_back
#define mx(a,b) (a>b?a:b)
#define mn(a,b) (a<b?a:b)
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;
using namespace std;

namespace IO
{
    const uint32 Buffsize=1<<15,Output=1<<23;
    static char Ch[Buffsize],*S=Ch,*T=Ch;
    inline char getc()
    {
        return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
    }
    static char Out[Output],*nowps=Out;
    
    inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

    template<typename T>inline void read(T&x)
    {
        x=0;static char ch;T f=1;
        for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
        for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
        x*=f;
    }

    template<typename T>inline void write(T x,char ch='\n')
    {
        if(!x)*nowps++='0';
        if(x<0)*nowps++='-',x=-x;
        static uint32 sta[111],tp;
        for(tp=0;x;x/=10)sta[++tp]=x%10;
        for(;tp;*nowps++=sta[tp--]^48);
        *nowps++=ch;
    }
}
using namespace IO;

void file(void)
{
    FILE*DSD=freopen("water.in","r",stdin);
    FILE*CSC=freopen("water.out","w",stdout);
}

const int MAXN=1e5+7;

static int n,m,k;

static struct edge
{
    int v,nxt;
}p[MAXN<<1];

static int head[MAXN],e;

inline void add(int u,int v)
{p[++e]=(edge){v,head[u]},head[u]=e;}

static int X[MAXN];

static uint64 Y[MAXN];

static uint64 mx;

inline void init()
{
    read(n),read(m),read(k);
    mx=k==64?ULLONG_MAX:(1llu<<k)-1;
    
    Rep(i,1,n)read(X[i]),read(Y[i]);
    static int u,v;
    Rep(i,1,n-1)read(u),read(v),add(u,v),add(v,u);
}

namespace GBST
{
    static uint64 L[MAXN][2],R[MAXN][2];

    static int fa[MAXN],son[MAXN],sz[MAXN],ls[MAXN],rs[MAXN],dep[MAXN];

    void dfs(int u)
    {
        sz[u]=1,dep[u]=dep[fa[u]]+1;
        for(register int i=head[u];i;i=p[i].nxt)
        {
            int v=p[i].v;
            if(v^fa[u])
            {
                fa[v]=u,dfs(v),sz[u]+=sz[v];
                if(sz[v]>sz[son[u]])son[u]=v;
            }
        }
    }

    static int sta[MAXN],tp,ssz[MAXN],bel[MAXN];

    inline uint64 op(uint64 a,uint64 b,int c)
    {
        if(c==1)return a&b;
        if(c==2)return a|b;
        return a^b;
    }

    inline void pushup(int u)
    {
        register uint64 
            l0=ls[u]?op(L[ls[u]][0],Y[u],X[u]):op(0,Y[u],X[u]),
            l1=ls[u]?op(L[ls[u]][1],Y[u],X[u]):op(mx,Y[u],X[u]),
            r0=rs[u]?op(R[rs[u]][0],Y[u],X[u]):op(0,Y[u],X[u]),
            r1=rs[u]?op(R[rs[u]][1],Y[u],X[u]):op(mx,Y[u],X[u]);
        if(ls[u])
        {
            R[u][0]=(~r0&R[ls[u]][0])|(r0&R[ls[u]][1]);
            R[u][1]=(~r1&R[ls[u]][0])|(r1&R[ls[u]][1]);
        }else R[u][0]=r0,R[u][1]=r1;
        if(rs[u])
        {
            L[u][0]=(~l0&L[rs[u]][0])|(l0&L[rs[u]][1]);
            L[u][1]=(~l1&L[rs[u]][0])|(l1&L[rs[u]][1]);
        }else L[u][0]=l0,L[u][1]=l1;
    }

    inline int build_tree(int l,int r)
    {
        if(l>r)return 0;
        int tot=0;Rep(i,l,r)tot+=ssz[sta[i]];
        for(register int i=l,cnt=ssz[sta[i]];i<=r;++i,cnt+=ssz[sta[i]])
            if(cnt<<1>=tot)
            {
                ls[sta[i]]=build_tree(l,i-1);
                rs[sta[i]]=build_tree(i+1,r);
                fa[ls[sta[i]]]=fa[rs[sta[i]]]=sta[i];
                pushup(sta[i]);
                return sta[i];
            }
    }

    bitset<MAXN>isr;

    int build(int u,int fr)
    {
        bel[u]=++e;
        for(int t=u;t;fr=t,t=son[t])
        {
            bel[t]=bel[u];
            for(register int i=head[t];i;i=p[i].nxt)
            {
                int v=p[i].v;
                if(v^son[t]&&v^fr)fa[build(v,t)]=t;
            }
        }
        tp=0;
        for(int t=u;t;t=son[t])sta[++tp]=t,ssz[t]=sz[t]-sz[son[t]];
        int rt=build_tree(1,tp);
        isr.set(rt);
        return rt;
    }

    static int vis[MAXN];

    inline uint64 quer(int x,int y,uint64 z)
    {
        register uint64 ans=0llu,l0=0llu,l1=mx,r0=0llu,r1=mx,zer,on,n0,n1,lasx,lasy;
        e=0;
        register int t,lca;
        for(t=x;t;t=fa[t])vis[t]=++e;
        for(t=y;t;t=fa[t])if(vis[t]){lca=t;break;}
        for(t=x;t;t=fa[t])vis[t]=0;
        for(t=0;bel[x]^bel[lca];t=x,x=fa[x])if(ls[x]&&t^ls[x])
        {
            zer=op(l0,Y[x],X[x]),on=op(l1,Y[x],X[x]);
            n0=(~zer&R[ls[x]][0])|(zer&R[ls[x]][1]);
            n1=(~on&R[ls[x]][0])|(on&R[ls[x]][1]);
            l0=n0,l1=n1;
        }else if(!ls[x]||t^ls[x])
        {
            l0=op(l0,Y[x],X[x]),l1=op(l1,Y[x],X[x]);
        }
        lasx=t;

        for(t=0;bel[y]^bel[lca];t=y,y=fa[y])if(ls[y]&&t^ls[y])
        {
            zer=op(L[ls[y]][0],Y[y],X[y]),on=op(L[ls[y]][1],Y[y],X[y]);
            n0=(~zer&r0)|(zer&r1);
            n1=(~on&r0)|(on&r1);
            r0=n0,r1=n1;
        }else if(!ls[y]||t^ls[y])
        {
            zer=op(0llu,Y[y],X[y]),on=op(mx,Y[y],X[y]);
            n0=(~zer&r0)|(zer&r1);
            n1=(~on&r0)|(on&r1);
            r0=n0,r1=n1;
        }
        lasy=t;
        if(dep[x]<=dep[y])
        {
            for(t=lasx;x^lca;t=x,x=fa[x])if(rs[x]&&t^rs[x])
            {
                zer=op(l0,Y[x],X[x]),on=op(l1,Y[x],X[x]);
                n0=(~zer&L[rs[x]][0])|(zer&L[rs[x]][1]);
                n1=(~on&L[rs[x]][0])|(on&L[rs[x]][1]);
                l0=n0,l1=n1;
            }else if(!rs[x]||t^rs[x])
                l0=op(l0,Y[x],X[x]),l1=op(l1,Y[x],X[x]);
        
            for(t=lasy;y^lca;t=y,y=fa[y])if(ls[y]&&t^ls[y])
            {
                zer=op(L[ls[y]][0],Y[y],X[y]),on=op(L[ls[y]][1],Y[y],X[y]);
                n0=(~zer&r0)|(zer&r1);
                n1=(~on&r0)|(on&r1);
                r0=n0,r1=n1;
            }else if(!ls[y]||t^ls[y])
            {
                zer=op(0llu,Y[y],X[y]),on=op(mx,Y[y],X[y]);
                n0=(~zer&r0)|(zer&r1);
                n1=(~on&r0)|(on&r1);
                r0=n0,r1=n1;
            }
        }
        else
        {
            for(t=lasx;x^lca;t=x,x=fa[x])if(ls[x]&&t^ls[x])
            {
                zer=op(l0,Y[x],X[x]),on=op(l1,Y[x],X[x]);
                n0=(~zer&R[ls[x]][0])|(zer&R[ls[x]][1]);
                n1=(~on&R[ls[x]][0])|(on&R[ls[x]][1]);
                l0=n0,l1=n1;
            }else if(!ls[x]||t^ls[x])
                l0=op(l0,Y[x],X[x]),l1=op(l1,Y[x],X[x]);
        
            for(t=lasy;y^lca;t=y,y=fa[y])if(rs[y]&&t^rs[y])
            {
                zer=op(R[rs[y]][0],Y[y],X[y]),on=op(R[rs[y]][1],Y[y],X[y]);
                n0=(~zer&r0)|(zer&r1);
                n1=(~on&r0)|(on&r1);
                r0=n0,r1=n1;
            }else if(!rs[y]||t^rs[y])
            {
                zer=op(0llu,Y[y],X[y]),on=op(mx,Y[y],X[y]);
                n0=(~zer&r0)|(zer&r1);
                n1=(~on&r0)|(on&r1);
                r0=n0,r1=n1;
            }
        }
        l0=op(l0,Y[lca],X[lca]),l1=op(l1,Y[lca],X[lca]);
        n0=(~l0&r0)|(l0&r1);
        n1=(~l1&r0)|(l1&r1);
        register uint64 now=0llu;
        Repe(i,k-1,0)
        {
            if(z-now>=1llu<<i&&((n1>>i&1)>(n0>>i&1)))now|=1llu<<i,ans|=1llu<<i;
            else ans|=n0&(1llu<<i);
        }
        return ans;
    }

    inline void modify(int x,int y,ll z)
    {
        X[x]=y,Y[x]=z,pushup(x);
        while(x&&!isr.test(x))pushup(fa[x]),x=fa[x];
    }
}
using namespace GBST;

static int rt;

inline void solve()
{
    dfs(1),e=0;
    fa[rt=build(1,0)]=0,isr.set(rt);
    static int opt,x,y;
    static uint64 z;
    Rep(i,1,m)
    {
        read(opt),read(x),read(y),read(z);
        if(opt==1)write(quer(x,y,z));
        else modify(x,y,z);
    }
    flush();
}

int main()
{
    init();
    solve();
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

显然用LCT维护一下经过一条链之后每一位原来是1会变成什么原来是0会变成什么即可

这样的话LCT复杂度是n log n * k的，链剖是n log^2 n * k的，都过不了

考虑把这个k给去掉，我们直接开两个unsigned long long，v0和v1，v0的每一位代表这一位原来是0的话经过这条链会变成什么，v1的每一位代表这一位原来是1的话经过这条链会变成什么

那么考虑信息的合并，假如你现在知道了v0[x],v1[x],v0[y],v1[y]，先经过x后经过y，那么合并之后新的v0=(v0[x]&v1[y])|(~v0[x]&v0[y])，v1=(v1[x]&v1[y])|(~v1[x]&v0[y])

比较好理解吧……就是比如v0，原来的0变成1那些位就会变成v1[y]中对应的位，变成0的那些位会变成v0[y]中对应的位，那么与一下，然后合起来就好了

链剖和LCT我都写了，结果LCT TLE了，链剖3s过了
不会LCT，膜拜一下会的大佬。
```
#include<iostream>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<cstdlib>
#include<cstdio>
#include<map>
#include<bitset>
#include<set>
#include<stack>
#include<vector>
#include<queue>
using namespace std;
#define MAXN 100010
#define MAXM 1010
#define ull unsigned long long
#define eps 1e-8
#define MOD 1000000007
#define INF 1000000000
char xB[1<<15],*xS=xB,*xTT=xB;
#define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
#define isd(c) (c>='0'&&c<='9')
ull read(){
	char xchh;
	ull xaa;
    while(xchh=getc(),!isd(xchh));(xaa=xchh-'0');
    while(xchh=getc(),isd(xchh))xaa=xaa*10+xchh-'0';return xaa;
}
struct vec{
	int to;
	int fro;
};
struct data{
	ull v0;
	ull v1;
	data(){
		
	}
	data(int o,ull x){
		if(o==1){
			v0=0&x;
			v1=(~0)&x;
		}
		if(o==2){
			v0=0|x;
			v1=(~0)|x;
		}
		if(o==3){
			v0=0^x;
			v1=(~0)^x;
		}
	}
	friend data operator +(data x,data y){
		data z;
		z.v0=(x.v0&y.v1)|((~x.v0)&y.v0);
		z.v1=(x.v1&y.v1)|((~x.v1)&y.v0);
		return z;
	}
};
vec mp[MAXN*2];
int tai[MAXN],cnt;
int dfn[MAXN],fa[MAXN],son[MAXN],siz[MAXN],dep[MAXN],ndf[MAXN],tp[MAXN],tim;
int op[MAXN];
ull a[MAXN];
data vl[MAXN<<2],vr[MAXN<<2];
int n,m,k;
inline void be(int x,int y){
	mp[++cnt].to=y;
	mp[cnt].fro=tai[x];
	tai[x]=cnt;
}
inline void bde(int x,int y){
	be(x,y);
	be(y,x);
}
inline void ud(int x){
	vl[x]=vl[x<<1]+vl[x<<1|1];
	vr[x]=vr[x<<1|1]+vr[x<<1];
}
void dfs(int x){
	int i,y;
	siz[x]=1;
	dep[x]=dep[fa[x]]+1;
	for(i=tai[x];i;i=mp[i].fro){
		y=mp[i].to;
		if(!siz[y]){
			fa[y]=x;
			dfs(y);
			siz[x]+=siz[y];
			if(siz[y]>siz[son[x]]){
				son[x]=y;
			}
		}
	}
}
void dfs2(int x,int z){
	int i,y;
	ndf[dfn[x]=++tim]=x;
	tp[x]=z;
	if(son[x]){
		dfs2(son[x],z);
		for(i=tai[x];i;i=mp[i].fro){
			y=mp[i].to;
			if(!dfn[y]){
				dfs2(y,y);
			}
		}
	}
}
void build(int x,int y,int z){
	if(y==z){
		vl[x]=vr[x]=data(op[ndf[y]],a[ndf[y]]);
		return ;
	}
	int mid=y+z>>1;
	build(x<<1,y,mid);
	build(x<<1|1,mid+1,z);
	ud(x);
}
void change(int x,int y,int z,int p){
	if(y==z){
		vl[x]=vr[x]=data(op[ndf[y]],a[ndf[y]]);
		return ;
	}
	int mid=y+z>>1;
	if(p<=mid){
		change(x<<1,y,mid,p);
	}else{
		change(x<<1|1,mid+1,z,p);
	}
	ud(x);
}
data askl(int x,int y,int z,int l,int r){
	if(y==l&&z==r){
		return vl[x];
	}
	int mid=y+z>>1;
	if(r<=mid){
		return askl(x<<1,y,mid,l,r);
	}else if(l>mid){
		return askl(x<<1|1,mid+1,z,l,r);
	}else{
		return askl(x<<1,y,mid,l,mid)+askl(x<<1|1,mid+1,z,mid+1,r);
	}
}
data askr(int x,int y,int z,int l,int r){
	if(y==l&&z==r){
		return vr[x];
	}
	int mid=y+z>>1;
	if(r<=mid){
		return askr(x<<1,y,mid,l,r);
	}else if(l>mid){
		return askr(x<<1|1,mid+1,z,l,r);
	}else{
		return askr(x<<1|1,mid+1,z,mid+1,r)+askr(x<<1,y,mid,l,mid);
	}
}
data toask(int x,int y){
	data vx(3,0),vy(3,0);
	while(tp[x]!=tp[y]){
		if(dep[tp[x]]>=dep[tp[y]]){
			vx=vx+askr(1,1,n,dfn[tp[x]],dfn[x]);
			x=fa[tp[x]];
		}else{
			vy=askl(1,1,n,dfn[tp[y]],dfn[y])+vy;
			y=fa[tp[y]];
		}
	}
	if(dep[x]>dep[y]){
		return vx+askr(1,1,n,dfn[y],dfn[x])+vy;
	}else{
		return vx+askl(1,1,n,dfn[x],dfn[y])+vy;
	}
}
int main(){
	int i,o,x,y;
	ull z;
	n=read();
	m=read();
	k=read();
	for(i=1;i<=n;i++){
		op[i]=read();
		a[i]=read();
	}
	for(i=1;i<n;i++){
		x=read();
		y=read();
		bde(x,y);
	}
	dfs(1);
	dfs2(1,1);
	build(1,1,n);
	while(m--){
		o=read();
		x=read();
		y=read();
		z=read();
		if(o==2){
			op[x]=y;
			a[x]=z;
			change(1,1,n,dfn[x]);
		}
		if(o==1){
			data t=toask(x,y);
			ull ans=0,now=0;
			for(i=k-1;~i;i--){
				if(t.v0&(1ull<<i)){
					ans+=1ull<<i;
				}else if((t.v1&(1ull<<i))&&now+(1ull<<i)<=z){
					ans+=1ull<<i;
					now+=1ull<<i;
				}
			}
			printf("%llu\n",ans);
		}
	}
	return 0;
}
 

```


---

## 作者：tswdfop233 (赞：0)

http://blog.csdn.net/tswdfop/article/details/77753725


---

