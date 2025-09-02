# Interesting Array

## 题目描述

We'll call an array of $ n $ non-negative integers $ a\[1\],a\[2\],...,a\[n\] $ interesting, if it meets $ m $ constraints. The $ i $ -th of the $ m $ constraints consists of three integers $ l_{i} $ , $ r_{i} $ , $ q_{i} $ ( $ 1<=l_{i}<=r_{i}<=n $ ) meaning that value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF482B/c5cfeb39e6b942f975aeab6674c1941b58030e74.png) should be equal to $ q_{i} $ .

Your task is to find any interesting array of $ n $ elements or state that such array doesn't exist.

Expression $ x&y $ means the bitwise AND of numbers $ x $ and $ y $ . In programming languages C++, Java and Python this operation is represented as "&", in Pascal — as "and".

## 样例 #1

### 输入

```
3 1
1 3 3
```

### 输出

```
YES
3 3 3
```

## 样例 #2

### 输入

```
3 2
1 3 3
1 3 2
```

### 输出

```
NO
```

# 题解

## 作者：wanggk (赞：13)

方法：**线段树**。

## 题意

构造一串长度为 $n$ 的数列，满足 $m$ 个条件。

每个条件表示为 $[l,r,x]$，指的是从 $a_l$ 到 $a_r$  这个连续子段中，满足所有的数**按位与**的结果**恰好**是 $x$ 。

问是否有这样的序列。如果有，第一行输出 `YES` ，第二行输出一个满足条件的长度为 $n$ 的数列(**这样的数列可能有多个，输出所有元素和最小的那个**)。如果没有，输出 `NO` 。

## 分析

$\tiny\color{blue}\texttt{比较详(啰)细(嗦)，可以跳过，代码在下面}$

#### Step1： 一眼看出线段树。

毕竟是区间的操作，再加上数据范围的提示。

#### Step2： 节点状态设定

既然题目条件为按位与，所以线段树每个节点的状态，存储的是**对应区间按位与的结果**。

#### Step3：联系一下线段树的操作（线段树建模）

从题中“按位与结果为 $x$ ”入手。

若区间内若干个数的按位与为 $x$ ，则这些数及 $x$ 在**二进制下满足**：

- 性质1：若按位与的结果 $x$ 在二进制下，某一位为 $1$ ，则区间内的这些数该位**均**为 $1$ 。

- 性质2：若按位与的结果 $x$ 在二进制下，某一位为 $0$ ，则区间内的这些数该位**不全**为 $1$ 。

弄清楚这点就好办了：

- **要想某区间内按位与结果为 $x$ ，就让区间内每个数 $a[i]|=x$ ，即区间按位或操作。** （对应性质1），$m$ 个条件，进行 $m$ 次区间按位或修改操作。

- 在所有区间按位或修改操作结束后，**对每个条件查询，判断每个条件中，该区间按位与的结果是否恰好为** $x$ ，如果不满足直接输出无解。（对应性质2）

#### Step4：总结

节点状态：区间**按位与**的结果。

修改操作：$m$ 次修改，将区间每一个数都与 $x$ 进行**按位或**。

查询操作：对每个条件的 $[l,r]$ 区间查询**按位与**，判断是否是预期的 $x$ 值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+10,maxm=4e5+10;

int n,m;
int x,y,z;//（询问/修改）的左边界，右边界，z为修改的值
int sm[maxn],lazy[maxn];
int s[maxm],h[maxm],t[maxm];

void pushdown(int o)
{
    if(!lazy[o]) return;
    lazy[o<<1]|=lazy[o];
    lazy[o<<1|1]|=lazy[o];
    sm[o<<1]|=lazy[o];
    sm[o<<1|1]|=lazy[o];
    lazy[o]=0;
}
void update(int o,int l,int r)
//修改，o为根节点，l和r分别是当前节点的左右边界（和全局变量的x,y意义不同）
{
    if(x<=l&&r<=y){
        lazy[o]|=z;
        sm[o]|=z;
        return;
    }
    pushdown(o);
    int mid=(l+r)>>1;
    if(x<=mid) update(o<<1,l,mid);
    if(y>mid)  update(o<<1|1,mid+1,r);
    sm[o]=(sm[o<<1]&sm[o<<1|1]);
}
int query(int o,int l,int r)
//查询，o为根节点，l和r分别是当前节点的左右边界（和全局变量的x,y意义不同）
{
    if(x<=l&&r<=y) return sm[o];
    pushdown(o);
    int res=(1<<30)-1;
    int mid=(l+r)>>1;
    if(x<=mid) res&=query(o<<1,l,mid);
    if(y>mid) res&=query(o<<1|1,mid+1,r);
    return res;
}

int main()
{
    memset(sm,0,sizeof(sm));
    memset(lazy,0,sizeof(lazy));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&s[i],&h[i],&t[i]);
        x=s[i],y=h[i],z=t[i];
        update(1,1,n);
    }
    for(int i=1;i<=m;i++){
        x=s[i],y=h[i];
        if(query(1,1,n)!=t[i]){
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    for(int i=1;i<=n;i++){
        x=y=i;
        printf("%d ",query(1,1,n));
    }
    return 0；
}
```


---

## 作者：TKXZ133 (赞：7)

[Interesting Array](https://www.luogu.com.cn/problem/CF482B)

### 题目大意

构造一个序列 $a$，使其满足若干限制条件，每个限制条件是形如 `l r q` 的式子，其意义是：$\&_{i=l}^ra_i=q$。

### 题意分析

看上去是构造题，实际上是数据结构题。

我们不妨先令初始时 $a$ 为一个全 $0$ 序列，再逐一看每个限制条件。

为了满足某一个限制条件 $l,r,p$，$[l,r]$ 区间的数必须符合以下两点：

- $1$，在二进制表示中，$p$ 为 $1$ 的位置均为 $1$。
- $2$，在二进制表示中，$p$ 为 $0$ 的位置区间内至少有一个数该位为 $0$。

我们发现，同时构造出满足两个条件的序列比较麻烦，且不好判断无解，因此，我们可以让一个条件成为构造的依据，另一个条件成为判断的依据。

具体的说，我们只需要构造出满足其中一个条件的序列，再逐一判断每个区间是否满足另一个条件即可。

因此，我们不妨先构造一个满足条件 $1$ 的序列，再逐一对条件 $2$ 进行判断。

那么，现在问题就变成了如果构造一个满足条件 $1$ 的序列和如何对条件 $2$ 进行判断。

这其实很简单，我们只需要用线段树进行区间按位或和区间求按位与就行了。

这是因为为了满足条件 $1$，我们需要让区间的二进制表示包含 $p$，这等价于于区间按位或 $p$，而条件 $2$ 与区间的按位与是 $p$ 二者也等价。

综上，我们只需要维护一颗线段树，支持区间或和区间求与即可。

### 代码

```
#include <bits/stdc++.h>
using namespace std;
const int N=100100;

int n,m,inp[N][3];

struct STn{int l,r,t,sum;};//sum表示区间与的结果，t是懒标记
struct ST{
    STn a[N<<2];
    void or_t(int p,int k){
        a[p].t|=k;a[p].sum|=k;//都或上k
    }
    void push_down(int p){//下放懒标记
        if(a[p].t){
            or_t(p<<1,a[p].t);
            or_t(p<<1|1,a[p].t);
            a[p].t=0;
        }
    }
    void build(int p,int l,int r){//简单建树
        a[p].l=l;a[p].r=r;a[p].t=0;
        if(a[p].l==a[p].r) return ;
        int mid=(a[p].l+a[p].r)>>1;
        build(p<<1,l,mid);
        build(p<<1|1,mid+1,r);
    }
    void or_all(int p,int l,int r,int k){//区间或
        if(l<=a[p].l&&a[p].r<=r){or_t(p,k);return ;}
        push_down(p);int mid=(a[p].l+a[p].r)>>1;
        if(l<=mid) or_all(p<<1,l,r,k);
        if(r>mid) or_all(p<<1|1,l,r,k);
        a[p].sum=a[p<<1].sum&a[p<<1|1].sum;
    }
    int and_all(int p,int l,int r){//区间求与
        if(l<=a[p].l&&a[p].r<=r) return a[p].sum;
        push_down(p);int mid=(a[p].l+a[p].r)>>1;
        if(r<=mid) return and_all(p<<1,l,r);
        if(l>mid) return and_all(p<<1|1,l,r);
        return and_all(p<<1,l,r)&and_all(p<<1|1,l,r);
    }
    void print(int p){//输出序列
        if(a[p].l==a[p].r){cout<<a[p].sum<<' ';return ;}
        push_down(p);int mid=(a[p].l+a[p].r)>>1;
        print(p<<1);print(p<<1|1);
    }
}tree;

int main(){
    scanf("%d%d",&n,&m);
    tree.build(1,1,n);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&inp[i][0],&inp[i][1],&inp[i][2]);
        tree.or_all(1,inp[i][0],inp[i][1],inp[i][2]);
    }
    for(int i=1;i<=m;i++)
        if(tree.and_all(1,inp[i][0],inp[i][1])!=inp[i][2]){cout<<"NO\n";return 0;} 
    cout<<"YES\n";
    tree.print(1);
    return 0;
}
```

---

## 作者：CaiXY06 (赞：4)

看到神犇们都用各种数据结构过了这题，那我就来一篇 **差分** 的题解吧

题目要求构造一个序列，并且需要满足 $m$ 个限制，每个限制都是要 $[l,r]$ 的 **按位与和** 为 $q$。

那么我们可以对于每一位做一个 **差分**。

设当前考虑二进制下的第 $i$ 位 $(0\leq i\leq 30)$。

如果这一位的差分值 $>0$ 就说明这个数的二进制第 $i$ 为 $1$，$a_i=a_i+2^i$。

我们在差分完之后，就满足了需要这一位为 $1$ 的限制，但是并不满足不为 $1$ 的限制，所以我们可以再做一个 **前缀和** 判断 $[l,r]$ 这一段区间的差分值是否都 $>1$ ，如果是就输出无解的情况。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100010],l[100010],r[100010],q[100010],c[100010],s[100010];
bool tag;
inline bool check(int x){
	memset(c,0,sizeof(c));
	for(int i=1;i<=m;i++)
	if(q[i]&x)c[l[i]]++,c[r[i]+1]--;//差分
	for(int i=1;i<=n;i++){
		c[i]+=c[i-1],s[i]=s[i-1]+(!c[i]);//前缀和
		if(c[i])a[i]|=x;
	}
	for(int i=1;i<=m;i++)
	if(!(q[i]&x)&&!(s[r[i]]-s[l[i]-1]))return 1;//判断是否无解
	return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d%d",&l[i],&r[i],&q[i]);
	for(int i=0;i<=30&&!tag;i++)tag=check(1<<i);//枚举每一位
	if(tag)return puts("NO"),0;
	puts("YES");
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
}
```


---

## 作者：ljc20020730 (赞：4)

### Hint  
看到题解区都是$O(n log_2^2 n )$的线段树算法，其实本题是有$O(n log_2 n)$写法的并且不用线段树。

### 正文

#### 题意


> 给出若干个要求，$l_i ， r_i ， q_i$表示$a[l_i] \& a[l_i + 1]\& ... \& a[r_i] = q_i$
> 
> 如果存在数组$a$则输出一行$YES$然后输出一种合法的数组. 否则，输出一行$NO$.
> 
> 对于100%的数据 $\leq n\leq 10^5 , q_i \leq 2^{30}$


#### 解析
可以把每个二进制为拉出来，对每一个位分别处理

如果一个区间$l,r$ 区间 $ and $ 值为1，那么 说明这个区间必须全部是$1$

所以我们直接对这个区间赋值为$1$即可。

然后对每个询问做一遍check，判断是否合法，即看看是$0$位置上的$l,r$是不是都是$1$，一旦都是1，那么就前后矛盾，输出$NO$.

上述维护可以使用差分前缀和维护。复杂度是$O(n \ log_2 \ n)$



#### 程序

```cpp
# include<bits/stdc++.h>
# define int long long
using namespace std;
const int N=1e5+10;
int n,Q,c[31][N],ans[31][N];
struct rec{ int l,r,d; }q[N];
void update(int l,int r,int d)
{
	for (int i=30;i>=0;i--)
		if (d&(1ll<<i)) c[i][l]++,c[i][r+1]--;
}
void init()
{
	for (int i=0;i<=30;i++) for (int j=1;j<=n;j++) c[i][j]=c[i][j-1]+c[i][j];
	for (int i=0;i<=30;i++) for (int j=1;j<=n;j++) c[i][j]=(c[i][j]>0);
	memcpy(ans,c,sizeof(c));
	for (int i=0;i<=30;i++) for (int j=1;j<=n;j++) c[i][j]=c[i][j-1]+c[i][j];
}
bool check(int l,int r,int d)
{
	for (int i=30;i>=0;i--)
	 if ((!(d&(1ll<<i)))&&(c[i][r]-c[i][l-1]==r-l+1)) return false;
	return true;
}
signed main()
{
	scanf("%lld%lld",&n,&Q);
	for (int i=1;i<=Q;i++) {
		scanf("%lld%lld%lld",&q[i].l,&q[i].r,&q[i].d);
		update(q[i].l,q[i].r,q[i].d);
	}
	init();
	for (int i=1;i<=Q;i++)
		if (!check(q[i].l,q[i].r,q[i].d)) { puts("NO"); return 0; }
	puts("YES");
	for (int i=1;i<=n;i++) {
		int ret=0;
		for (int j=0;j<=30;j++) if (ans[j][i]) ret+=(1<<j);
		printf("%lld ",ret);
	}
	return 0;
}
```

---

## 作者：reyik (赞：3)

线段树

乍一看是一个构造题，其实我们发现，如果这段区间这一位的值为1，那么整段区间都要为1，直接区间赋值1就行了，把每一位合起来就是区间$or$ $a[i]$

但是这样就有可能出现0的位置也为1的情况，所以我们对所有的区间都再查询一遍，看看我们构造出来的是不是有0的位置变成1，如果有冲突就输出$NO$

```cpp

#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const int N=100005;
struct node {
  int l,r,k;
}q[N<<2];
int a[N<<2],tag[N<<2],n,m;
bool vis=1;
void pushup(int x) {a[x]=a[x<<1]&a[x<<1|1];}
void pushdown(int x) {
  a[x<<1]|=tag[x];
  a[x<<1|1]|=tag[x];
  tag[x<<1]|=tag[x];
  tag[x<<1|1]|=tag[x];
}
void modify(int x,int l,int r,int L,int R,int y) {
  if(L<=l && r<=R) {
    a[x]|=y,tag[x]|=y;
    return ;
  }
  pushdown(x);
  int mid=(l+r)>>1;
  if(L<=mid) modify(x<<1,l,mid,L,R,y);
  if(R>mid) modify(x<<1|1,mid+1,r,L,R,y);
  pushup(x);
}
int query(int x,int l,int r,int L,int R) {
  if(L<=l && r<=R) return a[x];
  pushdown(x);
  int ret=(1<<30)-1,mid=(l+r)>>1;
  if(L<=mid) ret=ret&query(x<<1,l,mid,L,R);
  if(R>mid) ret=ret&query(x<<1|1,mid+1,r,L,R);
  return ret;
}
int main() {
  scanf("%d%d",&n,&m);
  for (int i=1;i<=m;++i) {
    scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].k);
    if(q[i].l>q[i].r) swap(q[i].l,q[i].r);
    modify(1,1,n,q[i].l,q[i].r,q[i].k);
  }
  for (int i=1;i<=m;++i) {
    if(query(1,1,n,q[i].l,q[i].r)!=q[i].k) vis=0;
  }
  if(!vis) {
    puts("NO");
    return 0;
  }
  puts("YES");
  for (int i=1;i<n;++i) printf("%d ",query(1,1,n,i,i));
  printf("%d\n",query(1,1,n,n,n));
  return 0;
}
```

---

## 作者：Styx (赞：2)

这道题看似是个构造题，其实他就是一道 ~~构造~~ 数据结构题

首先考虑最暴力的情况

对于一个区间，区间与后得到ai，则ai的二进制表示下，如果第i位为一，那么这一个区间中所有数的第i位一定是一。

然后如果第i位为0，那么说明在区间中一定至少有一个数是零，可以查询区间中1的个数是不是等于区间长度，如果是的话就GG了，输出NO

上述的思路可以建30棵区间覆盖线段树，维护每一位。

然后你就光荣的TLE第九个点了，比较喜欢这种暴力思路的大佬可以考虑用差分或者树状数组去继续优化常数，应该是可以A的

像我这种蒟蒻就只能重构代码了。

其实可以压位

我们进行的区间覆盖，其实就是按位或运算，可以直接把三十颗线段树合到一棵，支持区间或修改，每次区间或上ai

但是之前判断是否GG的地方就要魔改了，不要慌，会改的更加简单，因为我们进行完所有的或操作之后，已经得到了那个我们需要的ans数组，只需要检查这个数组对于每个区间li-ri的区间与是否等于ai就可以了，还是蛮神奇的，好吧，其实是我太菜了┓( ´∀` )┏

代码如下：
```cpp
#include<ctime>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define lson root<<1
#define rson root<<1|1
using namespace std;

struct oper
{
	int l,r,a;
} op[100010];

struct node
{
	int l,r,lazy,sum;
} tr[400010];

inline void push_up(int root)
{
	tr[root].sum=tr[lson].sum&tr[rson].sum;
}

inline void push_down(int root)
{
	tr[lson].sum|=tr[root].lazy;
	tr[lson].lazy|=tr[root].lazy;
	tr[rson].sum|=tr[root].lazy;
	tr[rson].lazy|=tr[root].lazy;
	tr[root].lazy=0;
}

inline void build(int root,int l,int r)
{
	if(l==r)
	{
		tr[root].l=l;
		tr[root].r=r;
		return ;
	}
	tr[root].l=l;
	tr[root].r=r;
	register int mid=(l+r)>>1;
	build(lson,l,mid);
	build(rson,mid+1,r);
}

inline void update(int root,int l,int r,int val)
{
	if(tr[root].l==l&&tr[root].r==r)
	{
		tr[root].sum|=val;
		tr[root].lazy|=val;
		return ;
	}
	if(tr[root].lazy)
	{
		push_down(root);
	}
	register int mid=(tr[root].l+tr[root].r)>>1;
	if(mid<l)
	{
		update(rson,l,r,val);
	}
	else
	{
		if(mid>=r)
		{
			update(lson,l,r,val);
		}
		else
		{
			update(lson,l,mid,val);
			update(rson,mid+1,r,val);
		}
	}
	push_up(root);
}

inline int query(int root,int l,int r)
{
	if(tr[root].l==l&&tr[root].r==r)
	{
		return tr[root].sum;
	}
	if(tr[root].lazy)
	{
		push_down(root);
	}
	register int mid=(tr[root].l+tr[root].r)>>1;
	if(mid<l)
	{
		return query(rson,l,r);
	}
	else
	{
		if(mid>=r)
		{
			return query(lson,l,r);
		}
		else
		{
			return query(lson,l,mid)&query(rson,mid+1,r);
		}
	}
}

int main()
{
	int n,m,flag=0;
	scanf("%d%d",&n,&m);
	build(1,1,n);
	for(int i=1; i<=m; i++)
	{
		scanf("%d%d%d",&op[i].l,&op[i].r,&op[i].a);
		update(1,op[i].l,op[i].r,op[i].a);
	}
	for(int i=1; i<=m; i++)
	{
		if(query(1,op[i].l,op[i].r)!=op[i].a)
		{
			flag=1;
		}
	}
	if(flag)
	{
		puts("NO");
	}
	else
	{
		puts("YES");
		for(int i=1; i<=n; i++)
		{
			printf("%d ",query(1,i,i));
		}
	}
}
```

---

## 作者：Saber_Master (赞：1)

[CF482B Interesting Array](https://www.luogu.com.cn/problem/CF482B)

注意观察按位与运算的特性，$ a\& b != c $不成立意味着二进制中$ a,b $的公共部分为$ c $的真子集或者存在其它部分.我们可以利用线段树执行区间或运算将第一种可能去除，接下来再次扫描区间按位与值是否符合要求，最后输出即可.

线段树具体操作详见代码.另外注意$pushdown$.

$O(n\log n)$
```cpp
const ll N=1e5+5;

ll ans[N];

namespace seg{
	ll dat[N<<2], lazy[N<<2];
	
	inline void pushup(ll p, ll val){
		dat[p]|=val; lazy[p]|=val;
	}
	
	inline void pushdown(ll p, ll l, ll r){
		if (l==r || !lazy[p]) return;
		pushup(p<<1, lazy[p]); pushup(p<<1|1, lazy[p]);
		return (void)(lazy[p]=0);
	}
	
	inline void update(ll p, ll l, ll r, ll u, ll v, ll val){
		pushdown(p, l, r);
		if (u<=l && r<=v) return pushup(p, val);
		ll mid=l+r>>1;
		if (u<=mid) update(p<<1, l, mid, u, v, val);
		if (v>mid) update(p<<1|1, mid+1, r, u, v, val);
		dat[p]=(dat[p<<1]&dat[p<<1|1]);
	}
	
	inline ll query(ll p, ll l, ll r, ll u, ll v){
		pushdown(p, l, r);
		if (u<=l && r<=v) return dat[p];
		ll mid=l+r>>1, res=(1ll<<30)-1;
		if (u<=mid) res&=query(p<<1, l, mid, u, v);
		if (v>mid) res&=query(p<<1|1, mid+1, r, u, v);
		return res;
	}
	
	inline void calc_ans(ll p, ll l, ll r){
		pushdown(p, l, r);
		if (l==r) return (void) (ans[l]=dat[p]);
		ll mid=l+r>>1;
		calc_ans(p<<1, l, mid); calc_ans(p<<1|1, mid+1, r);
	}
}

ll n, m;
ll quel[N], quer[N], num[N];
int main(){
	read(n); read(m);
	for (R ll i=1; i<=m; i++){
		read(quel[i]); read(quer[i]); read(num[i]);
		seg::update(1, 1, n, quel[i], quer[i], num[i]);
	}
	for (R ll i=1; i<=m; i++){
		if (seg::query(1, 1, n, quel[i], quer[i])!=num[i]) return puts("NO"), 0;
	}
	seg::calc_ans(1, 1, n);
	puts("YES");
	for (R ll i=1; i<=n; i++) writesp(ans[i]); putchar('\n');
}
```


---

## 作者：MyukiyoMekya (赞：1)

我们贪心的把这些限制填充上去，就是对每一个 $[l_i,r_i]$ 都 or 上一个 $q_i$

这样我们就可以保证现在的序列一定包含这些限制，而且一定为最优，因为没有添加任何“多余”的东西

然后我们再把每条限制都对这个最优的序列扫一遍，如果出现了 $[l_i,r_i]$ 的 and 和不等于 $q_i$ ，那就可以输出 NO 了，因为这已经是最优的序列了，如果把那些不符合的 1 删掉的话一定会使序列不符合其他的一些限制。

扫完发现没有问题的话就直接输出即可

时间复杂度 $O(m\log n)$

```cpp
// This code writed by chtholly_micromaker(MicroMaker)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define reg register
using namespace std;
const int MaxN=100050;
struct Quetion
{
	int l,r,x;
}Q[MaxN];
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
#define lson (u<<1)
#define rson (u<<1|1)
int val[MaxN<<2],lazy[MaxN<<2];
inline void pushup(int u)
{
	val[u]=val[lson]&val[rson];
	return;
}
inline void pushdown(int u,int l,int r)
{
	if(lazy[u])
	{
		lazy[lson]|=lazy[u];
		lazy[rson]|=lazy[u];
		val[lson]|=lazy[u];
		val[rson]|=lazy[u];
		lazy[u]=0;
	}
	return;
}
inline void modify(int u,int l,int r,int ql,int qr,int k)
{
	if(ql<=l&&r<=qr)
	{
		lazy[u]|=k;
		val[u]|=k;
		return;
	}
	pushdown(u,l,r);
	reg int mid=(l+r)>>1;
	if(ql<=mid)
		modify(lson,l,mid,ql,qr,k);
	if(mid<qr)
		modify(rson,mid+1,r,ql,qr,k);
	pushup(u);
	return;
}
inline int query(int u,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr)
		return val[u];
	pushdown(u,l,r);
	reg int mid=(l+r)>>1,ans=(1<<31)-1;
	if(ql<=mid)
		ans&=query(lson,l,mid,ql,qr);
	if(mid<qr)
		ans&=query(rson,mid+1,r,ql,qr);
	return ans;
}
signed main(void)
{
	int n,m;
	reg int l,r,x;
	cin>>n>>m;
	for(int i=1;i<=m;++i)
	{
		read(l);read(r);read(x);
		Q[i]=(Quetion){l,r,x};
		modify(1,1,n,l,r,x);
	}
	for(int i=1;i<=m;++i)
	{
		l=Q[i].l;r=Q[i].r;x=Q[i].x;
		if(query(1,1,n,l,r)!=x)
		{
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	for(int i=1;i<=n;++i)
		printf("%d ",query(1,1,n,i,i));
	puts("");
	return 0;
}
```



---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF482B](https://www.luogu.com.cn/problem/CF482B)

* **【解题思路】**

首先，对于某一个询问，我们可以确定，$a_i(l\leq i\leq r)\operatorname{and}q=q$，所以每一次我们只要把 $a_i(l\leq i\leq r)$ 全部位或上 $q$，这样就可以保证 $a_i(l\leq i\leq r)\operatorname{and}q=q$。可以使用线段树。

但是，为什么会有不合法的情况？看样例二可知，可能存在有询问冲突的情况。可以证明，如果按照上述方法构造出来的数组不合法，那么没有任何数组合法。所以，我们再用构造好的线段树查询区间位与，检查结果是否符合。

* **【实现细节】**

本题保证了修改一定在询问之前，所以线段树的实现会有些不一样。具体来讲，我们修改时直接打 tag 且不下推，全部修改完后统一把 tag 下推算出叶子节点的值，从而构建整个线段树。

~~感觉现在我就没写过一个正常的线段树~~

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

struct query
{
	int range_l,range_r,val;
};

array<int,400000> segment_tree,lazy_tag;
array<query,100000> queries;

int& l_son(int root)
{
	return segment_tree[root<<1];
}
int& r_son(int root)
{
	return segment_tree[root<<1|1];
}
void push_down(int root)
{
	lazy_tag[root<<1]|=lazy_tag[root],lazy_tag[root<<1|1]|=lazy_tag[root],lazy_tag[root]=0;
}
void update(int root,int range_l,int range_r,const int targ_l,const int targ_r,const int val)
{
	if(range_l>=targ_l&&range_r<=targ_r)
		return (void)(lazy_tag[root]|=val);
	int mid=range_l+range_r>>1;
	if(targ_l<=mid)
		update(root<<1,range_l,mid,targ_l,targ_r,val);
	if(targ_r>mid)
		update(root<<1|1,mid+1,range_r,targ_l,targ_r,val);
}
void clear_tag(int root,int range_l,int range_r)
{
	if(range_l==range_r)
		return (void)(segment_tree[root]=lazy_tag[root]);
	push_down(root);
	int mid=range_l+range_r>>1;
	clear_tag(root<<1,range_l,mid);
	clear_tag(root<<1|1,mid+1,range_r);
	segment_tree[root]=l_son(root)&r_son(root);
}
int and_query(int root,int range_l,int range_r,const int targ_l,const int targ_r)
{
	if(range_l>=targ_l&&range_r<=targ_r)
		return segment_tree[root];
	int mid=range_l+range_r>>1,result=2147483647;
	if(targ_l<=mid)
		result&=and_query(root<<1,range_l,mid,targ_l,targ_r);
	if(targ_r>mid)
		result&=and_query(root<<1|1,mid+1,range_r,targ_l,targ_r);
	return result;
}
void output(int root,int range_l,int range_r)
{
	if(range_l==range_r)
		return (void)(cout<<segment_tree[root]<<' ');
	int mid=range_l+range_r>>1;
	output(root<<1,range_l,mid);
	output(root<<1|1,mid+1,range_r);
}

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int cnt,cntquery;
	cin>>cnt>>cntquery;
	for(int i=0;i<cntquery;i++)
		cin>>queries[i].range_l>>queries[i].range_r>>queries[i].val,update(1,1,cnt,queries[i].range_l,queries[i].range_r,queries[i].val);
	clear_tag(1,1,cnt);
	for(int i=0;i<cntquery;i++)
		if(and_query(1,1,cnt,queries[i].range_l,queries[i].range_r)!=queries[i].val)
			return cout<<"NO",0;
	cout<<"YES\n";
	output(1,1,cnt);
	return 0;
}
```

---

## 作者：rui_er (赞：0)

构造一个数列使得区间与和满足一些限制。

考虑到两个数的与的一个二进制位为 $1$，当且仅当这一位在两个数中都为 $1$。推广可得，$a_l\sim a_r$ 与起来一位为 $1$，这些数的对应为必须都为 $1$。根据题目的限制把这些位标为 $1$。

那么其他的没有标为 $1$ 的位呢？直接赋值为 $0$ 即可。因为这里不是必须为 $1$，标为 $0$ 显然没有任何问题；但是如果标为 $1$ 可能会导致一些限制中本应为 $0$ 的位变成 $1$。

当然，像样例二中的一样，此时还是可能导致一些限制中本应为 $0$ 的位变成 $1$，还需要重新判一下所有的限制。综上，我们需要一个数据结构，支持区间或一个数、求区间与和，可以使用线段树维护。

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 1e5+5; 

int n, m;
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
struct Require {
	int l, r, q;
}req[N];
struct Node {
	int tag, w;
};
struct SegTree {
	Node t[N<<2];
	#define lc(u) (u<<1)
	#define rc(u) (u<<1|1)
	void pushup(int u) {
		t[u].w = t[lc(u)].w & t[rc(u)].w;
	}
	void pushdown(int u) {
		if(!t[u].tag) return;
		t[lc(u)].tag |= t[u].tag;
		t[rc(u)].tag |= t[u].tag;
		t[lc(u)].w |= t[u].tag;
		t[rc(u)].w |= t[u].tag;
		t[u].tag = 0;
	}
	void modify(int u, int l, int r, int ql, int qr, int k) {
		if(ql <= l && r <= qr) {
			t[u].tag |= k;
			t[u].w |= k;
			return;
		}
		pushdown(u);
		int mid = (l + r) >> 1;
		if(ql <= mid) modify(lc(u), l, mid, ql, qr, k);
		if(qr > mid) modify(rc(u), mid+1, r, ql, qr, k);
		pushup(u);
	}
	int query(int u, int l, int r, int ql, int qr) {
		if(ql <= l && r <= qr) return t[u].w;
		pushdown(u);
		int mid = (l + r) >> 1, ans = (1LL << 31) - 1;
		if(ql <= mid) ans &= query(lc(u), l, mid, ql, qr);
		if(qr > mid) ans &= query(rc(u), mid+1, r, ql, qr);
		pushup(u);
		return ans;
	}
	void print(int u, int l, int r) {
		if(l == r) {
			printf("%d ", t[u].w);
			return;
		}
		pushdown(u);
		int mid = (l + r) >> 1;
		print(lc(u), l, mid);
		print(rc(u), mid+1, r);
	}
	#undef lc
	#undef rc
}sgt;

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, m) {
		scanf("%d%d%d", &req[i].l, &req[i].r, &req[i].q);
		per(j, 30, 0) if((req[i].q >> j) & 1) sgt.modify(1, 1, n, req[i].l, req[i].r, 1<<j);
	}
	rep(i, 1, m) {
		int qwq = sgt.query(1, 1, n, req[i].l, req[i].r);
		if(qwq != req[i].q) return puts("NO")&0;
	}
	puts("YES");
	sgt.print(1, 1, n);
    return 0;
}
```

---

## 作者：critnos (赞：0)

一遍过的 CF 紫题。。真的水

看到这种位运算第一个想法就是拆位，然后对互不影响的每一位讨论。

然后就变成了 $01$ 序列，每次给出一个条件：区间都是 $1$/至少有一个 $0$。

想到这里就很显然了。对于区间都是 $1$ 的限制条件，直接区间推平，剩下不是 $1$ 的肯定贪心的染为 $0$。然后再逐个验证区间至少有一个 $0$ 的询问，若这个区间都是 $1$ 则无解，这个建前缀和。

这个区间推平做完之后看了下题解，发现都是线段树？不解，这个是经典老套路了吧，用并查集处理，不知道的可以去做一下 P2391。

这个做法朴素实现是时间 $O(n \log w \alpha(n)$，空间 $O(n)$ 的，用 uoj 上看到的处理这类问题的特殊的并查集可以把时间优化到 $O(n\log w)$。

---

## 作者：Cylete (赞：0)

数据范围：

$1 \le n, m \le 10^5, 0 \le q_i < 2^{30}$

乍一看貌似是一个构造题

细看我们发现对于一条限制$[l,r,q]$

**这段区间的每一个数对应的二进制都要包含$q$**

那我们对于每一条限制都加上去，最后再一起判断是不是都符合条件即可

复杂度$O(nlog_2n)$

```cpp
#define int long long
#define mid ((l+r)>>1)
#define lson (o<<1)
#define rson (o<<1|1)
#define R register

const int N = 1e5 + 10;

int n, m, flag;
int tree[N << 2], lazy[N << 2];

struct node
{
	int x, y, z;
}e[N];

inline void pushup(int o)
{
	tree[o] = tree[lson] & tree[rson];
}

inline void pushdown(int o)
{
	if(!lazy[o]) return;
	tree[lson] |= lazy[o];
	tree[rson] |= lazy[o];
	lazy[lson] |= lazy[o];
	lazy[rson] |= lazy[o];
	lazy[o] = 0;
}

inline void add(int o, int l, int r, int ql, int qr, int val)
{
	if(ql <= l && r <= qr)
	{
		tree[o] |= val;
		lazy[o] |= val;
		return;
	}
	pushdown(o);
	if(ql <= mid) add(lson, l, mid, ql, qr, val);
	if(qr > mid) add(rson, mid + 1, r, ql, qr, val);
	pushup(o);
}

inline int ask(int o, int l, int r, int ql, int qr)
{
	if(ql <= l && r <= qr) return tree[o];
	pushdown(o);
	int res = (1 << 30) - 1;
	if(ql <= mid) res &= ask(lson, l, mid, ql, qr);
	if(qr > mid) res &= ask(rson, mid + 1, r, ql, qr);
	pushup(o);
	return res;
}

inline void traval(int o, int l, int r)
{
	if(l == r)
	{
		writesn(tree[o]);
		return;
	}
	pushdown(o);
	traval(lson, l, mid);
	traval(rson, mid + 1, r);
}

signed main()
{
	into();
	read(n); read(m);
	for(R int i = 1; i <= m; i++)
	{
		read(e[i].x); read(e[i].y); read(e[i].z);
		add(1, 1, n, e[i].x, e[i].y, e[i].z);
	}
	for(R int i = 1; i <= m; i++)
		if(ask(1, 1, n, e[i].x, e[i].y) != e[i].z) flag = 1;
	if(flag) puts("NO");
	else
	{
		puts("YES");
		traval(1, 1, n);
	}
	return 0;
}
```

---

