# [JOI 2016 Final] 断层 / Geologic Fault

## 题目描述

**译者水平有限，跪求各位大佬提供更好的译文**

**本题译自 [JOI 2016 Final](https://www.ioi-jp.org/joi/2015/2016-ho/index.html) T5「[断層](https://www.ioi-jp.org/joi/2015/2016-ho/2016-ho.pdf)」**

很久很久以前，一个叫做 IOI 的先进文明蓬勃发展。时过境迁，现代考古学家 JOI 博士决定挖掘 IOI 文明遗址。

IOI 文明沿着笔直的河流发展。方便起见，IOI 文明遗址可以看作平面直角坐标系的 $x$ 轴，而 $y$ 轴表示海拔。IOI 文明地面平坦，也就是说，直线 $y=0$ 代表地面，而 $y>0$ 代表地面上空，$y<0$ 代表地下。另外，由于流水堆积，IOI 文明的地面一直在缓慢升高。IOI 文明灭亡前 $a$ 年 $(a\geqslant 0)$ 时，直线 $y=-a$ 才是地平面。  
IOI 文明灭亡后，它脚下的地层发生了 $Q$ 次运动。第 $i$ 次运动 $(1\leqslant i\leqslant Q)$ 可用位置 $X_i$，方向 $D_i$ 和变化量 $L_i$ 描述。$D_i = 1$ 或 $2$。具体来说，

* $D_i=1$：断层视为一条过 $(X_i, 0)$，斜率为 $1$ 的直线。断层上方的地层斜向上移动，横坐标增加 $L_i$，纵坐标增加 $L_i$。也就是说，直线上方的所有点 $(x,y)$ 移动到 $(x+L_i, y+L_i)$。
* $D_i=2$：断层视为一条过 $(X_i, 0)$，斜率为 $-1$ 的直线。断层上方的地层斜向上移动，横坐标减少 $L_i$，纵坐标增加 $L_i$。也就是说，直线上方的所有点 $(x,y)$ 移动到 $(x-L_i, y+L_i)$。

每次地壳运动后，$y>0$ 的地层都会因风化作用而消失。

试求：对于每一个 $i(1\leqslant i\leqslant N)$，**点 $(i-1,0)$ 和 点$(i,0)$ 之间的地层**是在 IOI 文明灭亡前哪一年的地层。 

> 在 $y$ 轴上，断层都是经过整点的，$y$ 轴上的相邻整点间没有断层。这样讲能明白吧……


## 说明/提示

#### 样例解释 1
![](https://cdn.luogu.com.cn/upload/image_hosting/uxq94hp7.png)

#### 数据范围与提示
对于所有数据，$1\leqslant N, Q\leqslant 2\times 10^5, -10^9\leqslant X_i\leqslant 10^9, D_i=1$ 或 $2, 1\leqslant L_i\leqslant 10^9(1\leqslant i\leqslant Q)$。

|Subtask #|$N,Q$|其他限制|分值|
|-|-|-|-|
|1|$N,Q\leqslant 100$|$-100\leqslant X_i\leqslant 100, L_i=1(1\leqslant i\leqslant Q)$|18|
|2|$N,Q\leqslant 3000$|无|16|
|3|$N,Q\leqslant 2\times10^5$|无|66|

## 样例 #1

### 输入

```
10 2
12 1 3
2 2 2```

### 输出

```
3
3
5
5
5
5
5
5
2
2```

## 样例 #2

### 输入

```
10 6
14 1 1
17 1 1
-6 2 1
3 2 1
4 1 1
0 2 1```

### 输出

```
5
5
4
5
5
5
5
5
4
4```

## 样例 #3

### 输入

```
15 10
28 1 7
-24 2 1
1 1 1
8 1 1
6 2 1
20 1 3
12 2 2
-10 1 3
7 2 1
5 1 2```

### 输出

```
15
14
14
14
14
12
12
12
12
12
12
12
15
15
12```

# 题解

## 作者：zifanwang (赞：12)

~~提高 T1 难度~~ 远古 JOI 题。这东西能评黑？？？

- [题目链接](https://www.luogu.com.cn/problem/P5103)

## 干什么

有两个长度为 $n$ 个序列 $(x_1,x_2,\dots,x_n),(y_1,y_2,\dots,y_n)$，初始化 $x_i=y_i=i$。有 $q$ 次操作，每次给你三个数 $X,D,L$，若 $D=1$ 将所有满足 $x_i\le X$ 的 $i$ 的 $y_i$ 减 $2L$，若 $D=2$ 则将所有满足 $y_i> X$ 的 $i$ 的 $x_i$ 加 $2L$，求出最终的 $x,y$ 序列。

## 怎么做

发现 $x,y$ 两个序列任意时刻都是单调递增的，两种操作分别是前缀减和后缀加，二分出修改的区间然后树状数组维护即可，时间复杂度 $O(q\log^2 n)$。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 200003
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
struct node{
	ll x,d,l;
}a[mxn];
int n,q;
struct tree{
	ll c[mxn];
	void add(int x,int y){for(;x<=n;x+=x&-x)c[x]+=y;}
	ll ask(int x){
		ll s=0;
		for(;x;x-=x&-x)s+=c[x];
		return s;
	}
}c1,c2;
signed main(){
	scanf("%d%d",&n,&q);
	rep(i,1,q)scanf("%lld%lld%lld",&a[i].x,&a[i].d,&a[i].l),a[i].l<<=1;
	rep(i,1,n)c1.add(i,1),c2.add(i,1);
	drep(j,q,1){
		if(a[j].d==1){
			int l=1,r=n;
			while(l<r){
				int mid=(l+r+1)>>1;
				if(c1.ask(mid)<=a[j].x)l=mid;
				else r=mid-1;
			}
			if(c1.ask(l)<=a[j].x)c2.add(1,-a[j].l),c2.add(l+1,a[j].l);
		}else{
			int l=1,r=n;
			while(l<r){
				int mid=(l+r)>>1;
				if(c2.ask(mid)>a[j].x)r=mid;
				else l=mid+1;
			}
			if(c2.ask(l)>a[j].x)c1.add(l,a[j].l);
		}
	}
	rep(i,1,n)printf("%lld\n",(c1.ask(i)-c2.ask(i))>>1);
	return 0;
}
```

---

## 作者：Fading (赞：10)

一道十分有趣的烧脑题。

不仅考验了线段树的理解程度，还考验了很多很多的...细节？

### 我只想到了第一步：离线。

列出最后的状态

```
0------------
1------------
2------------
3------------
```

然后倒着做一遍，上升变成下降。

最后求出所有$0$被平移到了第几层就好了。

这其实就是挖掘出最初的$0$点是从哪一层平移上来的。 

这样我们就成功的把**风化**这个毒瘤条件给搞掉了。 

因此我们只需要维护所有0的横纵坐标。（注意我们规定原坐标系纵坐标正方向向上） 

### 第二步：翻转坐标。

把一个点$(x,y)$翻转坐标成为$(x',y')$

$$x'=x-y,y'=x+y$$

这样坐标系就变成了这样
```
          0    
        0 _ 1
      0 _ 1 _
    0 _ 1 _ 2
  0 _ 1 _ 2 _ 
0 _ 1 _ 2 _ 3 

```

我们发现所有操作都简单多了，

$1$操作就是左边一整块向下平移，$2$操作就是上面一整块向右平移！

比如说我们随便移动一下，

借用一下$*Miracle*$巨佬的图就是

![](https://cdn.luogu.com.cn/upload/pic/60276.png
)

那么我们如何维护所有$0$点的横纵坐标变化呢？正解已经呼之欲出了。

### 第三步：线段树。

先把两个点之间的层转化成靠右的层。

用两棵线段树维护$0$点的$x,y$坐标 

$1$操作，把$y$线段树中所有$x$坐标$\leq X_i$ 的$y$坐标减去$2L$

$2$操作，把$x$线段树中所有$y$坐标$>X_i$ 的$x$坐标加上$2L$

很显然$0$点的$x,y$坐标满足二分性：对于$i<j,x_i<x_j,y_i<y_j$

所以可以直接二分，或者线段树上二分。

前者是两个$\log$的，需要$O2$。

后者是一个$\log$的。

有人可能觉得**很奇怪**，为什么不是找第$X_i$个$0$点平移呢？


------------

可能你感觉这个问题很蠢，但是我在独立思考的时候就被这个问题困扰了，~~也许是我太菜了吧...~~

第一：$X_i$很大。

第二：可以考虑用$-1,-2...$来填充原来对角线上的位置。这样就好理解很多了。$0$点到其他位置上去了，我们不可以直接平移。


------------


关于线段树上怎么二分:比如说求第一个$x$坐标$\leq X_i$的点。 

我们维护区间最小值。

对于线段树上一个节点，如果右儿子最小值$\leq X_i$，直接去右儿子里找
（根据刚才讲述的二分性质，右儿子一定比左儿子更优）

否则答案一定在左儿子里面。

那么求第一个$>X_i$的点怎么办呢？再维护一个区间最大值？？？这样常数会翻倍！ 

其实大大不必。由于二分单调性，我们可以用这样的方法：

对于一个节点，如果右儿子最小值$>X_i$，那么显然右儿子最小值是在$(\text{mid}+1)($右儿子编号最小的点的编号$)$处取到的

然后我们继续往左儿子去找是否存在更小的点，和当前答案取一个$\min$就好了。 

否则答案一定在右儿子处，继续递归即可。

#### 有一个小细节：如果找不到这个点的话就不需要执行本次操作了。 



### 最后一步：

我们知道了所有0点在翻转坐标系中的横纵坐标$z',y'$，通过解方程可以知道我们最后真实纵坐标
$$y=\frac{(y'-x')}2$$
但是很坑的是我们求的是答案层数！
所以答案

$$=\frac {(x'-y')}2\ \ !!!$$ 

代码很简单，我只写+调了$30$ min。只要思路清晰了这道题不算难写。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 998244353
using namespace std;
#ifdef Fading
#define gc getchar
#endif
#ifndef Fading
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
#endif
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
//x为0 y为1
ll seg[2][1000001],tag[2][1000001];//最小值和加法标记。
inline void pushup(int c,int rt){
    seg[c][rt]=min(seg[c][rt<<1],seg[c][rt<<1|1]);
}
#define mid ((lb+rb)>>1)
void build(int rt,int lb,int rb){
    if (lb==rb) return (void)(seg[0][rt]=seg[1][rt]=lb);
    build(rt<<1,lb,mid);build(rt<<1|1,mid+1,rb);
    pushup(0,rt);pushup(1,rt);
}
inline void pushdown(int c,int rt,int lb,int rb){
    if (!tag[c][rt]) return;
    int ls=rt<<1,rs=rt<<1|1;
    seg[c][ls]+=tag[c][rt];seg[c][rs]+=tag[c][rt];
    tag[c][ls]+=tag[c][rt];tag[c][rs]+=tag[c][rt];
    tag[c][rt]=0;
}
void update(int c,int rt,int lb,int rb,int l,int r,ll x){
    if (lb>r||rb<l) return;
    if (lb>=l&&rb<=r) return (void)(seg[c][rt]+=x,tag[c][rt]+=x);
    pushdown(c,rt,lb,rb);update(c,rt<<1,lb,mid,l,r,x);
    update(c,rt<<1|1,mid+1,rb,l,r,x);pushup(c,rt);
}
void Findx(int rt,int lb,int rb,int x,int &ans){
    if (lb==rb) return (void)(ans=(seg[0][rt]<=x?max(ans,lb):ans));
    pushdown(0,rt,lb,rb);
    if (seg[0][rt<<1|1]<=x) Findx(rt<<1|1,mid+1,rb,x,ans);
    else Findx(rt<<1,lb,mid,x,ans);
}
void Findy(int rt,int lb,int rb,int x,int &ans){
    if (lb==rb) return (void)(ans=(seg[1][rt]>x?min(ans,lb):ans));
    pushdown(1,rt,lb,rb);
    if (seg[1][rt<<1|1]>x) ans=min(ans,mid+1),Findy(rt<<1,lb,mid,x,ans);
    else Findy(rt<<1|1,mid+1,rb,x,ans);
}
ll ans[2][1000001];
void done(int rt,int lb,int rb){//获取最终答案信息 
    if (lb==rb) return (void)(ans[0][lb]=seg[0][rt],ans[1][lb]=seg[1][rt]);
    pushdown(1,rt,lb,rb);pushdown(0,rt,lb,rb);done(rt<<1,lb,mid);done(rt<<1|1,mid+1,rb);
}
int n,Q;
ll que[1000001][3];
signed main(){
    n=read();Q=read();
    build(1,1,n);
    for (int i=1;i<=Q;i++) que[i][0]=read(),que[i][1]=read(),que[i][2]=read();
    for (int i=Q;i;i--){
    	ll opt=que[i][1],X=que[i][0],L=que[i][2];
    	if (opt==1){
            int pos=-999999999;Findx(1,1,n,X,pos);
            if (pos!=-999999999) update(1,1,1,n,1,pos,-2*L);
        }else{
            int pos=999999999;Findy(1,1,n,X,pos);
            if (pos!=999999999) update(0,1,1,n,pos,n,2*L);
        }
    }
    done(1,1,n);
    for (int i=1;i<=n;i++){
        printf("%lld\n",(ans[0][i]-ans[1][i])/2);
    }
    return 0;
}

```

---

## 作者：totorato (赞：7)

# 断层

*(这是一种$O(n\log n)$的树状数组做法)*

我们可以将时间倒流，追溯现在的地表最初的深度。

时间倒流之后，当板块发生运动，地表将会下沉。我们追踪地表第$i$段板块的位置$\vec P(x_i,y_i)$，不难发现，$y$单调递减，而所有板块的$x$均满足$x_i< x_{i+1}$。

另外，我们还可以发现，对于所有$i$，均有$x_i+y_i<x_{i+1}+y_{i+1}$，以及$x_i-y_i<x_{i+1}-y_{i+1}$。

因为，板块的运动将直接导致$\vec P$的一段前缀$x$减小，或者一段后缀$x$增加。

这样，我们就可以用某一种数据结构按$x$坐标升序维护所有板块的位置。每次，我们将一段前缀$\vec P$同时加上$(-l,-l)$，或者将一段后缀$\vec P$同时加上$(+l,-l)$。至于这个前后缀的分界线在哪里，我们可能需要二分找到最后一段被板块运动影响到的$P$。

如果采用树状数组+二分，时间复杂度为$O(n+q\log^2n)$。

如果采用平衡树，时间复杂度为$O(n+q\log n)$，常数巨大。

如果采用树状数组+树状数组上二分，时间复杂度为$O(n+q\log n)$。

那么怎么在树状数组上二分呢？我们维护所有$\vec P$的$x$和$y$的差分序列，那么我们需要找的将会是$\max\{i|x_i+y_i\leq t\}$以及$\max\{i|x_i-y_i\leq t\}$。一开始，我们设$i=0$，从高位到低位尝试$i$能否将这一位变成$1$。最终找到的就是答案$i$。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define MX 262145
#define mov(x) (1<<(x))
#define lb(x) ((x)&(-(x)))

using namespace std;

typedef long long ll;

template <typename T> void read(T& x)
{
	x = 0; char c = getchar(); bool f = 0;
	while(!isdigit(c) && c!='-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(isdigit(c)) x = x*10+c-'0', c = getchar();
	if(f) x = -x;
}

struct FEN
{
	ll x[MX], y[MX];
	
	int find13(ll d)
	{
		int p = 0;
		for(int i=17; i>=0; i--)
		{
			ll s = x[p+mov(i)] - y[p+mov(i)];
			if(s <= d) p += mov(i), d -= s;
		}
		return p;
	}
	
	int find24(ll d)
	{
		int p = 0;
		for(int i=17; i>=0; i--)
		{
			ll s = x[p+mov(i)] + y[p+mov(i)];
			if(s <= d) p += mov(i), d -= s;
		}
		return p+1;
	}
	
	void add(int p, ll dx, ll dy)
	{
		for(int i=p; i<MX; i+=lb(i)) x[i] += dx, y[i] += dy;
	}
} F;

int xi[MX], di[MX], li[MX];
ll sy[MX];

int main()
{
	int n, q;
	read(n); read(q);
	for(int i=1; i<=n; i++) F.add(i, 1, 0);
	for(int i=1; i<=q; i++) read(xi[i]), read(di[i]), read(li[i]);
	for(int i=q; i>=1; i--)
	{
		if(di[i] == 1)
		{
			int p = F.find13(xi[i]);
			if(p) F.add(1, -li[i], -li[i]), F.add(p+1, +li[i], +li[i]);
		}
		else
		{
			int p = F.find24(xi[i]);
			if(p <= n) F.add(p, +li[i], -li[i]);
		}
	}
	for(int i=1; i<=n; i++)
	{
		sy[i] = sy[i-lb(i)]+F.y[i];
		printf("%lld\n", -sy[i]);
	}
	return 0;
}
```



---

## 作者：Msents (赞：5)

这里介绍一种使用无旋 Treap，不需要修改坐标系就行的方法。

和其它题解的思路一样，这里需要离线处理，从后到前遍历每次地层运动，将向上运动视为向下运动。

这样就相当于去找最后的每块地面是最开始的第几层地层，重要的是，这能搞掉风化这个毒瘤条件。

我们将每块最后的地面视作在平面直角坐标系上的在 $X$ 轴上，即 $y=0$ 的点。

然后能发现每次地层运动就是将在一条斜率为 $1$ 或 $-1$ 的直线的上面的点向左下和右下移动。

因为只有线上方的点才会移动，这样如果每个点之间连线，就会只有斜坡和平地的形状出现。（有点抽象但我也只能这样描述了，可以结合其它题解理解）

也就是说每次断层移动就只会移动一段编号连续的点。（如果出现向内凹的陡崖就不行了）

于是乎直接按斜率切割平衡树修改，然后再合并就行了。

最后答案就是每个点的深度

~~压了只有 90 行。~~

代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MaxN=200000;
mt19937 rander(chrono::steady_clock::now().time_since_epoch().count());
struct Node{
	int x,y,lx,ly;
	int heap;
	int lc,rc;
}tree[MaxN+1];
void PushDown(int u){
	if(tree[u].lx){
		tree[tree[u].lc].x+=tree[u].lx,tree[tree[u].rc].x+=tree[u].lx;
		tree[tree[u].lc].lx+=tree[u].lx,tree[tree[u].rc].lx+=tree[u].lx;
		tree[u].lx=0;
	}
	if(tree[u].ly){
		tree[tree[u].lc].y+=tree[u].ly,tree[tree[u].rc].y+=tree[u].ly;
		tree[tree[u].lc].ly+=tree[u].ly,tree[tree[u].rc].ly+=tree[u].ly;
		tree[u].ly=0;
	}
}
pair<int,int>Split(int u,int x,int k){
	if(!u)return make_pair(0,0);
	PushDown(u);
	if(tree[u].x+k*tree[u].y<=x){
		auto pi=Split(tree[u].rc,x,k);
		tree[u].rc=pi.first;
		return make_pair(u,pi.second);
	}else{
		auto pi=Split(tree[u].lc,x,k);
		tree[u].lc=pi.second;
		return make_pair(pi.first,u);
	}
}
int Merge(int u,int v){
	if(!u||!v)return u+v;
	if(tree[u].heap<tree[v].heap){
		PushDown(u);
		tree[u].rc=Merge(tree[u].rc,v);
		return u;
	}else{
		PushDown(v);
		tree[v].lc=Merge(u,tree[v].lc);
		return v;
	}
}
int n,q;
struct Move{int x,d,l;}a[MaxN+1];
void PDfs(int u){
	if(!u)return;
	PushDown(u);
	PDfs(tree[u].lc);
	PDfs(tree[u].rc);
}
void Solve(){
	cin>>n>>q;
	int root=0;
	for(int u=1;u<=n;u++){
		tree[u].x=u,tree[u].y=0,tree[u].lx=0,tree[u].ly=0;
		tree[u].heap=rander();
		tree[u].lc=0,tree[u].rc=0;
		root=Merge(root,u);
	}
	for(int i=1;i<=q;i++)cin>>a[i].x>>a[i].d>>a[i].l;
	for(int i=q;i>=1;i--){
		if(a[i].d==1){
			auto pi=Split(root,a[i].x,1);
			tree[pi.first].lx-=a[i].l,tree[pi.first].ly+=a[i].l;
			tree[pi.first].x-=a[i].l,tree[pi.first].y+=a[i].l;
			root=Merge(pi.first,pi.second);
		}else{
			auto pi=Split(root,a[i].x,-1);
			tree[pi.second].lx+=a[i].l,tree[pi.second].ly+=a[i].l;
			tree[pi.second].x+=a[i].l,tree[pi.second].y+=a[i].l;
			root=Merge(pi.first,pi.second);
		}
	}
	PDfs(root);//记得下放所有懒标记
	for(int i=1;i<=n;i++)cout<<tree[i].y<<'\n';
}
#undef int
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	Solve();
	return 0;
}

```

---

## 作者：mrclr (赞：4)


这题关键在于逆向思维，就是考虑最后的$n$的个点刚开始在哪儿，这样就减少了很多需要维护的东西。
这就让我想到很久以前的一道NOIP题，铺地毯。那是我第一次接触逆向思维，觉得十分的巧妙，原本要写的很麻烦或者干脆写不出来的题，反着想，竟然几行就完事了。

不扯别的了，还是说一下这题怎么想吧……

把操作离线，然后倒着操作，上移变成了下移。但是每一次移动两维的坐标都会改变，十分的难受。于是我们把坐标轴旋转45度，就十分美滋滋了：以顺时针举例，如果斜率为1，在新的坐标系中只有纵坐标发生了改变；斜率为-1，只有横坐标发生了改变。而且改变的这些点一定是一个前缀或者后缀。于是更新可用线段树实现。

不过更为重要的是，对于查询的$n$个点，无论逆向怎么操作，这些点的横、纵坐标的相对大小都不会变，大的只会更大，小的只会更小。

有了这个性质，我们就可以二分找要改的前缀（后缀）的边界了。判断的时候就是线段树单点查询。

到这里这题基本就完事了，需要注意的是，区间修改时应该加（减）的是$2l$，因为在原本的坐标系中移动的距离是$\sqrt{2} l$，而新坐标系的距离又是原来的$\sqrt{2}$倍，所以应该是$\sqrt{2} * \sqrt{2}l$。

线段树有点慢，需要开O2才能过，改成树状数组就快很多了。
```c++
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<stack>
#include<queue>
#include<vector>
using namespace std;
#define space putchar(' ')
#define enter puts("")
#define Mem(a, x) memset(a, x, sizeof(x))
#define In inline
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
const int maxn = 4e5 + 5;
const int N = 262144;
In ll read()
{
	ll ans = 0;
	char ch = getchar(), las = ' ';
	while(!isdigit(ch)) las = ch, ch = getchar();
	while(isdigit(ch)) ans = (ans << 1) + (ans << 3) + ch - '0', ch = getchar();
	if(las == '-') ans = -ans;
	return ans;
}
In void write(ll x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}

int n, Q;
struct Que
{
	int d; ll x, l;
}q[maxn];

struct Tree
{
	int l[maxn << 2], r[maxn << 2];
	ll lzy[maxn << 2];
	In void build(int L, int R, int now, int flg)
	{
		l[now] = L; r[now] = R;
		if(L == R) {lzy[now] = L * flg; return;}
		int mid = (L + R) >> 1;
		build(L, mid, now << 1, flg);
		build(mid + 1, R, now << 1 | 1, flg);
	}
	In void pushdown(int now)
	{
		if(lzy[now])
		{
			lzy[now << 1] += lzy[now]; lzy[now << 1 | 1] += lzy[now];
			lzy[now] = 0;
		}
	}
	In void update(int L, int R, int now, int d)
	{
		if(l[now] == L && r[now] == R) 
		{
			lzy[now] += d;
			return;
		}
		pushdown(now);
		int mid = (l[now] + r[now]) >> 1;
		if(R <= mid) update(L, R, now << 1, d);
		else if(L > mid) update(L, R, now << 1 | 1, d);
		else update(L, mid, now << 1, d), update(mid + 1, R, now << 1 | 1, d);
	}
	In ll query(int now, int id)
	{
		if(l[now] == r[now]) return lzy[now];
		pushdown(now);
		int mid = (l[now] + r[now]) >> 1;
		if(id <= mid) return query(now << 1, id);
		else return query(now << 1 | 1, id);
	}
}t1, t2;

int main()
{
	n = read(), Q = read();
	for(int i = Q; i; --i) q[i].x = read(), q[i].d = read(), q[i].l = read();
	t1.build(0, N - 1, 1, 1), t2.build(0, N - 1, 1, -1);
	for(int i = 1; i <= Q; ++i)
	{
		if(q[i].d == 1)
		{
			int L = 0, R = N - 1;
			while(L < R)
			{
				int mid = ((L + R) >> 1) + 1;
				if(t2.query(1, mid) < -q[i].x) R = mid - 1;
				else L = mid;
			}
			t1.update(0, L, 1, -q[i].l * 2);
		}
		else
		{
			int L = 0, R = N - 1;
			while(L < R)
			{
				int mid = ((L + R) >> 1) + 1;
				if(t1.query(1, mid) > q[i].x) R = mid - 1;
				else L = mid;
			}
			if(L + 1 > N - 1) --L;
			t2.update(L + 1, N - 1, 1, -q[i].l * 2);
		}
	}
	for(int i = 1; i <= n; ++i) write(-(t2.query(1, i) + t1.query(1, i)) / 2), enter;
	return 0;
}
```

---

## 作者：小小小朋友 (赞：2)

## 题意

题目说的比较复杂，可以理解为一个地层对应一个点（它的右端点），然后再根据题面理解。注意所求的答案实际上就是地层的原层数。

## 做法

题面如此复杂，我们考虑离线后倒过来处理。这样子实际上要维护的只有一条线的变化，也就是所有 $y=0$ 上的点的原本位置。

然而两种操作还是很不清晰，我们对坐标系做一个变化，把 $A(x,y)$ 变为 $A'(x-y,x+y)$，也可以理解为做一个 $45$ 度的旋转。

这样来看，两种操作就变得非常清晰，它们是这样的：

对于 $A(x,y)\rightarrow A'(m=x-y,n=x+y)$ 满足 $y-x\geq X_i\rightarrow m\leq X_i$，$A(x+L_i,y+L_i)\rightarrow A'(m,n+2L_i)$。

对于 $A(x,y)\rightarrow A'(m=x-y,n=x+y)$ 满足 $x+y> X_i\rightarrow n> X_i$，$A(x+L_i,y+L_i)\rightarrow A'(m+2L_i,n)$。

倒过来做分别是这样的：

把所有横坐标（变换后）小于等于询问中的 $X_i$ 的点的纵坐标减去 $2L$。

把所有纵坐标（变换后）大于询问中的 $X_i$ 的点的横坐标加上 $2L$。

可以看出，这样操作后，原本点的顺序关系不会变化，即 $i<j$ 时 $X_i<X_j$，$Y_i<Y_j$。

于是我们可以想到二分。这道题数据比较一般，我们直接用两棵线段树分别维护每个点的变换后的横纵坐标，按照给出的操作进行修改，并直接在线段树上暴力二分，然后再把答案转换回来。在 O2 加持下可通过此题。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
const int N=2e5,inf=1e16;
using namespace std;
int seg[2][8*N+5],tag[2][8*N+5],n;
int quer[3][N+5];
void build(int id,int l,int r){
    if(l==r) {
        seg[0][id]=seg[1][id]=l;//第0层的点变换后坐标为(i,i)
        return ;
    }
    int mid=(l+r)>>1;
    build(id*2,l,mid);
    build(id*2+1,mid+1,r);
}
void push_down(int tp,int id){
    seg[tp][id*2]+=tag[tp][id];
    seg[tp][id*2+1]+=tag[tp][id];
    tag[tp][id*2]+=tag[tp][id];
    tag[tp][id*2+1]+=tag[tp][id];
    tag[tp][id]=0;
}
void update(int typ,int id,int x,int y,int l,int r,int L){
    if(l>r) return;
    if(r==n+1) r=n;
    if(l<=x&&y<=r){
        seg[typ][id]+=L;
        if(x!=y)tag[typ][id]+=L;
        return ;
    }
    int mid=(x+y)>>1;
    if(l<=mid) update(typ,id*2,x,mid,l,r,L);
    if(r>mid) update(typ,id*2+1,mid+1,y,l,r,L);
}
int ask(int typ,int id,int x,int y,int l){//线段树板子
    if(x==y) 
        return seg[typ][id];
    int mid=(x+y)>>1;
    push_down(typ,id);
    if(l<=mid) return ask(typ,id*2,x,mid,l);
    else return ask(typ,id*2+1,mid+1,y,l);
}
int searc(int typ,int x){//暴力二分出第一个大于 x 的位置
    int l=1,r=n+1;//注意边界条件
    while(l<r){
        int mid=(l+r)>>1;
        if(ask(typ,1,1,n,mid)>x) r=mid;
        else l=mid+1;
    }
    return l;
}
signed main(){
    ios::sync_with_stdio(0);
    int q;cin>>n>>q;
    build(1,1,n);
    for(int i=1;i<=q;i++) cin>>quer[0][i]>>quer[1][i]>>quer[2][i];
    for(int i=q;i>=1;i--){
        int typ=quer[1][i]-1,x=quer[0][i],L=quer[2][i];
        if(typ==0){
            int pos=searc(0,x);
            update(1,1,1,n,1,pos-1,-2*L);
        }
        else {
            int pos=searc(1,x);
            update(0,1,1,n,pos,n,2*L);
        }
    }
    for(int i=1;i<=n;i++){
        cout<<(ask(0,1,1,n,i)-ask(1,1,1,n,i))/2<<endl;//将变换后坐标变换回去 解方程组可得此式
    }
    return 0;
}
```

不理解可主页询问，我会尽快解答。

---

## 作者：Demoe (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P5103)

~~喜提最劣解~~

## 题意

- 在平面上给定两平移操作，求最后 $n$ 个点原始位置。

~~题目略长 自行阅读~~

## $\text{Sol}$

先考虑**旋转坐标系**，我们逆时针旋转 $\dfrac{\pi}{4}$ 后，两平移操作就只剩下坐标一个维度的变换了。（为了方便建议再放大 $\sqrt 2$ 倍，这样每次计算就都是整数了）

然后我们考虑**反向**操作，把最后求的点反向操作回去。

然后是本题最重要的一个性质。

我们可以发现，在反向操作时，我们**所有点横纵坐标的相对大小都没有变**。（已旋转坐标系）

为什么呢？

初始时，所有点横纵坐标都单调递增。

我们发现 $L_i$ 恒正，那么我们两个操作就变成了**左边一段区间下移**和**上面一段区间右移**。

而这也正好保证了初始的**单调性**。

那么每一次操作都是**区间修改**，可以用线段树或树状数组解决。

然后我写的是二分端点+线段树，复杂度 $O(n\log^2 n)$。

其中单次修改是 $O(\log n)$ 的，单次寻找端点是 $O(\log^2 n)$ 的。

其中有些细节：

- 由于坐标系放大了 $\sqrt 2$ 倍，那么每次操作长度应当是 $2L_i$。

- 答案是最后的 $\dfrac{x-y}{2}$，因为题目中是 $y=-a$。

### $\text{Code}$

```cpp
// wish to get better qwq

#include<bits/stdc++.h>
#define re register ll
#define pb push_back
#define xl (x<<1)
#define xr (x<<1|1)
#define mid ((l+r)>>1)

using namespace std;
typedef long long ll;

template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}

// ---------- IO ---------- //

const ll N=2e5+5;
ll n,m;

struct operations{ll d;ll x,l;}q[N];

struct Segment_Tree{
	ll a[N<<2];
	inline void build(ll l,ll r,ll x){
		if(l==r){a[x]=l;return ;}
		build(l,mid,xl);build(mid+1,r,xr);
	}
	inline void modify(ll L,ll R,ll l,ll r,ll k,ll x){
		if(L>r||R<l) return ;
		if(L<=l&&r<=R){a[x]+=k;return ;}
		modify(L,R,l,mid,k,xl);modify(L,R,mid+1,r,k,xr);
	}
	inline void spread(ll x){
		if(a[x]){
			a[xl]+=a[x];a[xr]+=a[x];
			a[x]=0;
		}
	}
	inline ll qaq(ll l,ll r,ll k,ll x){
		if(l==r) return a[x];
		spread(x);
		if(mid>=k) return qaq(l,mid,k,xl);
		else return qaq(mid+1,r,k,xr);
	}
}sx,sy;
// sx 表示旋转后 x 轴的线段树 sy y 轴 

// ---------- Segment Tree ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);rd(m);sx.build(1,n,1);sy.build(1,n,1);
	//for(re i=1;i<=n;i++) wr(sx.qaq(1,n,i,1)),putchar(' '),wr(sy.qaq(1,n,i,1)),puts("");
	for(re i=m;i>0;i--) rd(q[i].x),rd(q[i].d),rd(q[i].l);
	for(re i=1;i<=m;i++){
		ll l=1,r=n,awa=0;
		if(q[i].d==1){
			while(l<=r){
				if(sx.qaq(1,n,mid,1)<=q[i].x) awa=mid,l=mid+1;
				else r=mid-1;
			}
			if(awa) sy.modify(1,awa,1,n,-2*q[i].l,1);
		}
		else{
			while(l<=r){
				if(sy.qaq(1,n,mid,1)>q[i].x) awa=mid,r=mid-1;
				else l=mid+1;
	//			cout<<awa<<endl;
			}
			if(awa) sx.modify(awa,n,1,n,2*q[i].l,1);
		}
	//	cout<<awa<<endl;
	//	for(re i=1;i<=n;i++) wr(sx.qaq(1,n,i,1)),putchar(' '),wr(sy.qaq(1,n,i,1)),puts("");
	//	puts("-----");
	}
	for(re i=1;i<=n;i++) wr((sx.qaq(1,n,i,1)-sy.qaq(1,n,i,1))/2),puts("");
	return 0;
}

// ---------- Main ---------- //

```

---

## 作者：flyfreemrn (赞：0)

## [[JOI 2016 Final] 断层](https://www.luogu.com.cn/problem/P5103)

### 离线

看到这道题，第一步想到对操作离线，我们先考虑最后的情况，然后从后往前进行每一步操作，把向上变成向下，最后看第 0 层的土都去哪了。

~~然后我就想到这一步。~~

### 处理斜线

这道题的一大难点就是操作给定的是斜线，所以我们很难用正常的数据结构去维护。

一个天才的想法：将斜线转成直线，那么怎么转呢？我们直接旋转坐标系！

我们点 $(x, y)$ 在新坐标系中的坐标为 $(x - y, x + y)$，这样我们就将一坨斜线转化成了直线。

具体来说，考虑一次操作的影响，假如我们要对一个斜率为负的斜线修改，相当于找出所有 $y > b - x$ 的点，移项得 $x + y > b$ 在新坐标系中就等于 $y' > b$。

我们就可以将操作转变成：
1. 将所有 $y > b$ 的点横坐标 $ + 2L$。
2. 将所有 $x < b$ 的点纵坐标 $ - 2L$。
而我们发现一开始深度为 0 的点 $x$ 和 $y$ 坐标都是有单调性的，而上述两种修改都不会改变点之间 $x,y$ 的相对大小，因此我们的两个坐标始终是单调的。

因此，我们可以考虑用两颗线段树分别维护横坐标和纵坐标，在其中一棵上边二分，之后区间修改。

最后，我们再把坐标转回原坐标系即可。

---

## 作者：Aurora_Borealis_ (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P5103)

首先发现斜着平移比较难处理，所以考虑将平面逆时针旋转 $45^\circ$。

接着发现风化也不好处理，但是风化的一定不会作为答案，所以我们可以离线，然后倒着处理操作，上升变为下降。

![](https://cdn.luogu.com.cn/upload/image_hosting/qm4ccssg.png)

我们发现每个初始 $0$ 点最后的坐标就是它正着做时初始的坐标，且每次操作都只会将连续一段点的 $x,y$ 坐标修改。

我们可以开两棵线段树，一棵维护 $x$ 坐标，一棵维护 $y$ 坐标。

容易发现，操作规律：

对于操作一，将维护 $y$ 坐标的线段树中所有 $x$ 坐标小于 $x_i$ 的 $y$ 坐标减去 $2 \cdot d_i$。

对于操作二，将维护 $x$ 坐标的线段树中所有 $y$ 坐标大于 $x_i$ 的 $x$ 坐标增加 $2 \cdot d_i$。

至于为什么乘二，是因为旋转后中间有空隙。

但是我们发现这个修改位置无法直接确定，于是我们可以在线段树上二分修改的位置。当修改 $y$ 坐标时，我们在 $x$ 线段树上二分小于 $x_i$ 的最大的 $x$，当修改 $x$ 坐标时，在 $y$ 线段树上二分大于 $x_i$ 的最小的 $y$。

至于为什么能二分：

显然相邻的两个 $0$ 的 相对位置是不变的，所以小于一个值的坐标一定在一个区间内。

二分到位置后修改，注意到有可能搜不到这个点，此时不修改就行了。

---

## 作者：MuelsyseU (赞：0)

实现可以做到非常简单，但是思维难度却很高的好题。

考虑形式化每个操作，即对于坐标系中每个点的横纵坐标同时 $+1$ 或 $-1$，最后询问满足 $y=0$ 的前 $n$ 个点原先的纵坐标。

容易发现我们不可能维护坐标系中所有的点；我们实际上只关心最终坐标为 $(i,0)$ 的点。因此可以得到题解中重要的逆向思想，考虑仅对这些点应用操作，通过最后的纵坐标取相反数来得到答案。

另一个思想是，显然 $x,y$ 同时发生改变不容易进行维护。但是由于这些点的改变都是沿与坐标轴夹角为 $45 \degree$ 的直线进行，因此考虑对该坐标轴进行旋转。

不妨设 $x'=x-y,y'=x+y$，则容易发现这时两个操作都只修改 $x'_i,y'_i$ 中的一个。由于操作的特点，会发现由于单调性，实际上任何时候我们修改的点在 $x$ 坐标上均是后缀且不断增大，在 $y$ 坐标上均是前缀且不断减小。而原本 $x',y'$ 显然皆为单调递增。

因此，每个修改 $d=1$ 实际上意味着对坐标序列某个前缀执行一个 $x$ 的区间减，$d=2$ 同理。

考虑维护差分数组，则这是一个树状数组可解决的问题。

那么现在的问题是，二分找到该前缀的长度，也就是坐标（差分数组的前缀和）小于或大于 $X_i$ 的一段区间。很显然由于这是一个前缀，而树状数组恰好维护了一段前缀的长度为 $2^k$ 的后缀的和，可以直接选择倍增查找，总复杂度 $O(n\log n)$。

具体来说，从大到小考虑 $\lfloor\log n\rfloor$ 到 $0$ 的每个数，用二进制分解思想拼凑为一段前缀，查看该前缀的答案与 $X_i$ 的相对大小关系，以此判断区间端点编号的这一位是否为 $1$。

```cpp
#include <bits/stdc++.h>
#define maxn 400005
using namespace std;

typedef long long ll;
int n, m, lg, pw[25];
ll cx[maxn], cy[maxn];
int x[maxn], d[maxn], l[maxn];
inline ll ask(ll c[], int x) {
    ll s = 0;
    for (; x; x -= x & (-x)) s += c[x];
    return s;
}
inline void add(ll c[], int x, int y) {
    for (; x <= n; x += x & (-x)) c[x] += y;
}
// 查询前缀和小于等于 k 的最后一个位置
inline int find(ll c[], int k) {
    // t 为位置编号，s 为前 t 位的和
    ll t = 0, s = 0;
    for (int i = lg; i >= 0; --i)
        if (t + pw[i] <= n && s + c[t + pw[i]] <= k) t += pw[i], s += c[t];
    return t;
}
signed main() {
    scanf("%d%d", &n, &m), lg = log2(n);
    for (int i = 0; i <= lg; ++i) pw[i] = (1 << i);
    for (int i = 1; i <= n; ++i) add(cx, i, 1), add(cy, i, 1);
    for (int i = 1; i <= m; ++i) scanf("%d%d%d", x + i, d + i, l + i);
    for (int i = m; i >= 1; --i) {
        if (d[i] == 1)
            add(cy, 1, -2 * l[i]), add(cy, find(cx, x[i]) + 1, 2 * l[i]);
        else
            add(cx, find(cy, x[i]) + 1, 2 * l[i]);
    }
    for (int i = 1; i <= n; i++) {
        // 实际上是 ((x - y) - (x + y)) / 2 = -y
        printf("%lld\n", (ask(cx, i) - ask(cy, i)) >> 1);
    }
    return 0;
}
```

---

## 作者：Tari (赞：0)

#### 线段树，开$O2\space3700ms$左右,不开$O2\space5300ms$左右

主要是自己的二分快一些，好像总复杂度是$O(nlogn)$级的？

原来的地面上升，可以倒着操作（时光倒流），转化为地面沉降，最后的答案就是每个点的深度。

下面的1，2操作均定义为向下沉降（与原题意的变换相反）；

首先这个题目只会操作**前缀和后缀**，并且只会把前缀中的数（纵坐标）变小（2操作），后缀中的数（横坐标）变大（1操作），所以**具有单调性**，可以进行二分。（括号中含义的解释见下）

先把整个坐标系旋转$45$度（逆时针为例），操作1即纵坐标$y>=xi$的点都会往右走$2*l$，横坐标$+2*l$，纵坐标不变，由于有单调性，只会操作后缀；操作2即横坐标$x<=xi$的点都会往下走$2*l$，纵坐标$-2*l$，横坐标不变，由于有单调性，只会操作前缀。

所以二分一下实际坐标就好了。。注意最后计算深度是$(x-y)/2$

我的这种二分需要维护一个$mx$区间最大值,二分时看一眼左右子树的$mx$,然后决定向哪一棵子树递归。

```cpp
#include<cstdio>
#include<iostream>
#define ls (tr<<1)
#define rs (tr<<1|1)
#define ll long long
#define R register ll
const int N=200010,Inf=0x3f3f3f3f;
using namespace std;
char B[1<<15],*S=B,*T=B,ch;
#define getchar() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?EOF:*S++)
inline int g() {
	R ret=0,fix=1; register char ch; while(!isdigit(ch=getchar())) fix=ch=='-'?-1:fix;
	do ret=ret*10+(ch^48); while(isdigit(ch=getchar())); return ret*fix;
}
int n,m;
struct node {int x,d,l;}q[N];
ll MX[2][N<<2],TG[2][N<<2];
#define mx MX[c]
#define tg TG[c]
inline void build(int c,int tr,int l,int r) {
	if(l==r) {mx[tr]=l; return ;} R md=l+r>>1;
	build(c,ls,l,md),build(c,rs,md+1,r); mx[tr]=max(mx[ls],mx[rs]);
}
inline void spread(int c,int tr) { if(!tg[tr]) return ;
	tg[ls]+=tg[tr],tg[rs]+=tg[tr],mx[ls]+=tg[tr],mx[rs]+=tg[tr]; tg[tr]=0;
} ll pos;
inline void fx(int tr,int l,int r,int k) {
	if(l==r) {if(MX[0][tr]<=k) pos=max(pos,(ll)l); return ;} spread(0,tr); R md=l+r>>1;
	if(MX[0][ls]<=k) pos=max(pos,md),fx(rs,md+1,r,k); else fx(ls,l,md,k);
}
inline void fy(int tr,int l,int r,int k) {
	if(l==r) {if(MX[1][tr]>k) pos=min(pos,(ll)l); return ;} spread(1,tr); R md=l+r>>1;
	if(MX[1][ls]<=k) fy(rs,md+1,r,k); else fy(ls,l,md,k);
}
inline void add(int c,int tr,int l,int r,int LL,int RR,int d) {
	if(LL<=l&&r<=RR) {mx[tr]+=d,tg[tr]+=d; return ;} spread(c,tr); R md=l+r>>1;
	if(LL<=md) add(c,ls,l,md,LL,RR,d); if(RR>md) add(c,rs,md+1,r,LL,RR,d); mx[tr]=max(mx[ls],mx[rs]);
} ll p[2][N];
inline void calc(int c,int tr,int l,int r) {
	if(l==r) {p[c][l]=mx[tr]; return ;} spread(c,tr); 
	R md=l+r>>1; calc(c,ls,l,md),calc(c,rs,md+1,r);
}
signed main() {
	n=g(),m=g(); for(R i=1;i<=m;++i) q[i].x=g(),q[i].d=g(),q[i].l=g();
	build(0,1,1,n),build(1,1,1,n); for(R i=m;i>=1;--i) { 
		if(q[i].d==1) {
			pos=0; fx(1,1,n,q[i].x);
			if(pos) add(1,1,1,n,1,pos,-2*q[i].l);
		} else {
			pos=Inf; fy(1,1,n,q[i].x);
			if(pos!=Inf) add(0,1,1,n,pos,n,2*q[i].l);
		} //cerr<<pos<<endl;
	} calc(0,1,1,n),calc(1,1,1,n);
	for(R i=1,ans;i<=n;++i) ans=(p[0][i]-p[1][i])/2,printf("%lld\n",ans);
}
```


---

