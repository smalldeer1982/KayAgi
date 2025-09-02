# Lucky Queries

## 题目描述

## 问题描述

给你 $n$ 个数，每个数是 $4$ 或者 $7$ ，给你 $m$ 个任务完成。

`switch l r` 把 $[l,r]$ 位置的 $4$ 换成 $7$ , $7$ 换成 $4$。

`count` 计算 $n$ 个数的最长不下降子序列的长度。

 $N$ 个数的不下降子序列是这 $n$ 个数移除掉 $0$ 个或者若干个位置的数，并且满足从第 $2$ 个数开始每一个数不小于前一个数的大小。

## 样例 #1

### 输入

```
2 3
47
count
switch 1 2
count
```

### 输出

```
2
1
```

## 样例 #2

### 输入

```
3 5
747
count
switch 1 1
count
switch 1 3
count
```

### 输出

```
2
3
2
```

# 题解

## 作者：TKXZ133 (赞：7)

[Lucky Queries](https://www.luogu.com.cn/problem/CF145E)

### 题目大意

给出一个只由 $4$ 和 $7$ 组成的序列，要求完成区间 $4,7$ 翻转和求全序列最长不下降子序列操作。

### 思路分析

我们发现，我们要求的答案其实只与 $4,7$ 的大小关系有关，因此，我们不妨令 $4\to0,7\to1$，将原序列转化为一个 $01$ 序列。

对于一个 $01$ 序列中的最长不下降子序列，它一定是由前面的若干个 $0$（可以是 $0$ 个）和后面的若干的 $1$ 组成的，其划分端点可能在左区间也可能在右区间。

![](https://i.328888.xyz/2023/02/04/NBmMA.png)

经过观察，我们发现可以通过维护区间内 $0$ 和 $1$ 的个数来辅助更新最长不下降子序列的长度。

具体的说，我们设 $\text{sum}_0$ 为区间内 $0$ 的个数，$\text{sum}_1$ 为区间内 $1$ 的个数，$\text{len}_1$ 为区间内最长不下降子序列的长度，那么我们可以按照以下的方法来更新区间：

```
a[p].sum0=a[p<<1].sum0+a[p<<1|1].sum0
a[p].sum1=a[p<<1].sum1+a[p<<1|1].sum1
a[p].len1=max(a[p<<1].len1+a[p<<1|1].sum1,a[p<<1].sum0+a[p<<1|1].len1)

```

上面的 $\text{max}$ 是对 $0,1$ 的划分段点进行讨论得出的。

但是区间 $01$ 翻转操作怎么办呢？

我们发现，在翻转后，原来的最长不下降子序列的长度变成了最长不上升子序列的长度，$\text{sum}_0$ 和 $\text{sum}_1$ 发生了互换。

于是，我们可以再维护区间最长不上升子序列的长度 $\text{len}_0$，这样翻转时只需要交换即可。

维护最长不上升子序列的长度也类似：
```
a[p].len0=max(a[p<<1].len0+a[p<<1|1].sum0,a[p<<1].sum1+a[p<<1|1].len0)
```

### 代码

```
#include <bits/stdc++.h>
using namespace std;
const int N=1001000;

int inp[N],n,m,in1,in2;
char ch[N];

struct STn{int l,r,sum0,sum1,len0,len1,t;};
void merge(STn &res,STn a,STn b){//按照上述方法更新
    res.sum0=a.sum0+b.sum0;
    res.sum1=a.sum1+b.sum1;
    res.len1=max(a.len1+b.sum1,a.sum0+b.len1);
    res.len0=max(a.len0+b.sum0,a.sum1+b.len0);
}
struct ST{
    STn a[N<<2];
    void change_t(int p){a[p].t^=1;swap(a[p].sum0,a[p].sum1);swap(a[p].len0,a[p].len1);}//交换，更新标记
    void push_down(int p){if(a[p].t){change_t(p<<1);change_t(p<<1|1);a[p].t=0;}}
    void build(int p,int l,int r){
        a[p].l=l;a[p].r=r;a[p].t=0;
        if(a[p].l==a[p].r){
            if(inp[a[p].l]) a[p].sum1=1;//赋初值
            else a[p].sum0=1;
            a[p].len0=a[p].len1=1;
            return ;
        }
        int mid=(a[p].l+a[p].r)>>1;
        build(p<<1,l,mid);
        build(p<<1|1,mid+1,r);
        merge(a[p],a[p<<1],a[p<<1|1]);
    }
    void change(int p,int l,int r){//区间翻转
        if(l<=a[p].l&&a[p].r<=r){change_t(p);return ;}
        push_down(p);int mid=(a[p].l+a[p].r)>>1;
        if(l<=mid) change(p<<1,l,r);
        if(r>mid) change(p<<1|1,l,r);
        merge(a[p],a[p<<1],a[p<<1|1]);
    }
}tree;

int main(){
    scanf("%d%d",&n,&m);
    scanf("%s",ch+1);
    for(int i=1;i<=n;i++)
        inp[i]=(ch[i]=='7')?1:0;//转化为01序列
    tree.build(1,1,n);
    while(m--){
        scanf("%s",ch+1);
        if(ch[1]=='c') cout<<tree.a[1].len1<<'\n';
        if(ch[1]=='s'){scanf("%d%d",&in1,&in2);tree.change(1,in1,in2);}
    }
    return 0;
}
```

---

## 作者：Warriors_Cat (赞：3)

线段树入门题。

### $Solution:$

考虑维护线段树的 $4$ 个值：$4$ 的个数、$7$ 的个数，最长不下降子序列长度，最长不上升子序列长度。

先说说合并，前两个显然，至于后两个就先拿最长不下降子序列长度举例子。

由于这里只有 $4$ 和 $7$，所以最长不下降子序列只会是先有一段 $4$ 后有一段 $7$。所以只可能是左边的最长不下降子序列和右边的 $7$ 合并或者是左边的 $4$ 和右边的最长不下降子序列合并。

搞定完合并，这道题就基本做完了。

一个区间翻转就把前两个交换，后两个交换，然后打一个翻转标记就行了。

至于 `build`, `change` 那些线段树基本操作就是个板子。

于是这题没了……

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int N = 1000010;
char opt[10], s[N];
int n, m, x, y;
struct node{
	int f, s, up, down; bool tag;
	node(int a = 0, int b = 0, int c = 0, int d = 0, bool e = 0){
		f = a; s = b; up = c; down = d; tag = e;
	}//f -> four, s -> seven
}d[N << 2];
inline void pushup(int p){
	int ls = p << 1, rs = p << 1 | 1;
	d[p].f = d[ls].f + d[rs].f; d[p].s = d[ls].s + d[rs].s;
	d[p].up = max(d[ls].up + d[rs].s, d[ls].f + d[rs].up);
	d[p].down = max(d[ls].down + d[rs].f, d[ls].s + d[rs].down);
}
inline void upd(int p){ swap(d[p].f, d[p].s); swap(d[p].up, d[p].down); d[p].tag ^= 1; }
inline void pushdown(int p){
	if(d[p].tag){
		upd(p << 1); upd(p << 1 | 1); d[p].tag = 0;
	}
}
inline void build(int p, int l, int r){
	if(l == r){
		d[p] = (s[l] == '4' ? node(1, 0, 1, 1) : node(0, 1, 1, 1));
		return;
	} dingyi;
	build(ls, l, mid); build(rs, mid + 1, r); pushup(p);
}
inline void change(int p, int l, int r, int x, int y){
	if(x <= l && r <= y){ upd(p); return; } dingyi; pushdown(p);
	if(x <= mid) change(ls, l, mid, x, y);
	if(y > mid) change(rs, mid + 1, r, x, y);
	pushup(p);
}
int main(){
	n = read(); m = read(); scanf("%s", s + 1);
	build(1, 1, n);
	for(int i = 1; i <= m; ++i){
		scanf("%s", opt); 
		if(opt[0] == 'c') printf("%d\n", d[1].up);
		else{
			x = read(); y = read();
			change(1, 1, n, x, y);
		}
	}
	return 0;
}

```

---

## 作者：tmp_get_zip_diff (赞：2)

给定一个序列，每一个数是 $4$ 或者 $7$ ，每次两种操作，翻转一个区间的 $4,7$ 或者询问这个序列的最长不降子序列长度。

分析：经典的线段树维护的题目。

考虑维护区间内 $4$ 的个数 ，$7$ 的个数以及最长不下降子序列长度和最长不上升子序列长度。

于是区间翻转就很好处理了，直接把四个值两两交换即可。

代码：
```
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;bool f=false;char ch=getchar();
	while(!isdigit(ch)){f|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template<typename T>
inline void write(T x){
	if(x<0) x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
const int N=1e6+5,N1=1e4+5,M=1e7+5;
#define PII pair<int,int>
#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define ll long long
int n,m,a[N],tag[N<<2];
int valx[N<<2],valy[N<<2],num4[N<<2],num7[N<<2];//valx：最长不下降，valy：最长不上升 
inline void Pushup(int x){
	num4[x]=num4[x<<1]+num4[x<<1|1];
	num7[x]=num7[x<<1]+num7[x<<1|1];
	valx[x]=max(valx[x<<1]+num7[x<<1|1],num4[x<<1]+valx[x<<1|1]);
	valy[x]=max(valy[x<<1]+num4[x<<1|1],num7[x<<1]+valy[x<<1|1]);
	return ;
}
void Build(int x,int l,int r){
	if(l==r) return num4[x]=(a[l]==4),num7[x]=!num4[x],valx[x]=valy[x]=1,void();
	int mid=l+r>>1;
	Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
	Pushup(x);return ;
}
inline void Pushtag(int x){
	swap(num4[x],num7[x]),swap(valx[x],valy[x]),tag[x]^=1;
	return ;
}
void PushDown(int x){
	if(tag[x]) Pushtag(x<<1),Pushtag(x<<1|1);
	tag[x]=0;
	return ;
}
void Modify(int x,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return Pushtag(x),void();
	PushDown(x);int mid=l+r>>1;
	if(ql<=mid) Modify(x<<1,l,mid,ql,qr);
	if(qr>mid) Modify(x<<1|1,mid+1,r,ql,qr);
	Pushup(x);
	return ;
}
signed main(){
	read(n),read(m);
	for(register int i=1;i<=n;i++) scanf("%1d",&a[i]);
	Build(1,1,n);
	while(m--){
		int l,r;char op[5];
		scanf("%s",op);
		if(op[0]=='c'){
			write(valx[1]);putchar('\n');
			continue;
		}
		read(l),read(r);
		Modify(1,1,n,l,r);
	}
	return 0;
}
```
注释较少，希望看懂，感谢各位管理员，求过

---

## 作者：Celtic (赞：1)

线段树。

在树中我们维护四个东西：最长不下降子序列的长度，最长不上升子序列的长度，$4$的个数和$7$的个数。

线段树最重要的是$push\,up$，也就是合并。

显然$4$的个数和$7$的个数就直接加一下，没什么好说的。

因为数列中不是$4$就是$7$，所以这个最长不下降子序列一定有一个$4$和$7$的分界点。

如果这个分界点在左儿子里，那么父节点的最长不下降子序列的长度就是左儿子的最长不下降子序列长度加上右儿子的$7$的个数。

如果这个分界点在右儿子里，那么父节点的最长不下降子序列的长度就是左儿子的$4$的个数加上右儿子的最长不下降子序列长度。

最长不上升子序列的长度同理。

这部分的代码

```cpp
struct node
{
	ll l,r,mid,vals,valx,num4,num7;//vals是最长不上升子序列长度，valx是最长不下降子序列长度
	bool tag;//lazy标记
}seg[N<<2];
inline void pushup(re ll pos)
{
	seg[pos].vals=max(seg[pos<<1].vals+seg[pos<<1|1].num7,seg[pos<<1].num4+seg[pos<<1|1].vals);
	seg[pos].valx=max(seg[pos<<1].valx+seg[pos<<1|1].num4,seg[pos<<1].num7+seg[pos<<1|1].valx);
	seg[pos].num4=seg[pos<<1].num4+seg[pos<<1|1].num4;
	seg[pos].num7=seg[pos<<1].num7+seg[pos<<1|1].num7;
	return;
}
```
建树就没什么可说的了，和正常的线段树建树一样，最长不上升子序列长度和最长不下降子序列的长度都赋为$1$。

```cpp
inline void build(re ll pos,re ll l,re ll r)
{
	seg[pos].l=l;
	seg[pos].r=r;
	seg[pos].mid=l+r>>1;
	if(l==r)
	{
		seg[pos].vals=seg[pos].valx=1;
		seg[pos].num4=(a[l]==4);
		seg[pos].num7=(a[l]==7);
	}
	else
	{
		build(pos<<1,l,seg[pos].mid);
		build(pos<<1|1,seg[pos].mid+1,r);
		pushup(pos);	
	}
	return;
}
```

修改操作就直接把最长不上升子序列的长度和最长不下降子序列的长度交换，$4$的数量和$7$的数量交换。

标记下传

```cpp
inline void add(re ll pos)
{
	seg[pos].tag^=1;
	swap(seg[pos].num4,seg[pos].num7);
	swap(seg[pos].valx,seg[pos].vals);
	return;
}
inline void pushdown(re ll pos)
{
	if(!seg[pos].tag)
		return;
	add(pos<<1);
	add(pos<<1|1);
	seg[pos].tag^=1;
	return;
}
```

区间修改

```cpp
inline void upgrade(re ll pos,re ll l,re ll r)
{
	if(seg[pos].l>=l&&seg[pos].r<=r)
		return add(pos);
	else if(seg[pos].l>r||seg[pos].r<l)
		return;
	pushdown(pos);
	upgrade(pos<<1,l,r);
	upgrade(pos<<1|1,l,r);
	pushup(pos);
	return;
}
```
每次询问的结果就是`seg[1].vals`。

注意这个毒瘤的没有空格的输入就好了，main函数不在这里给出。

$\color{red}\texttt{  P.S. 楼主写题解不容易，请勿ctrl+c*ctrl+V，尊重楼主的劳动成果}$



---

## 作者：panyf (赞：1)

线段树。

首先，这种题建议用一个结构体来存储节点，会比较清晰：
```cpp
struct T{
	bool t;
	int sa,sb,ta,tb;
}t[N<<2];
```
其中 $t$ 是翻转标记， $sa$ 和 $sb$ 分别为区间最长不下降子序列的长度和最长不上升子序列的长度， $ta$ 和 $tb$ 分别为 $4$ 和 $7$ 的数量。

接下来直接套线段树板子。

$4$ 和 $7$ 的交换：
```cpp
inline void rev(T&k){
	k.t^=1,swap(k.sa,k.sb),swap(k.ta,k.tb);//打上翻转标记，然后只需分别交换sa,sb和ta,tb
}
```
最重要的区间合并。考虑由于只有 $4$ 和 $7$ 两个数，因此最长不下降子序列一定存在一个分界点，使得其左侧全为 $4$ ，右侧全为 $7$ 。当分界点在区间左半部分时，长度即为左半部分的答案加上右半部分 $7$ 的个数。右半部分同理。区间的答案即为两种情况的最大值。最长不上升子序列同理。代码：
```cpp
inline void up(T&k,T a,T b){
	k.ta=a.ta+b.ta,k.tb=a.tb+b.tb;//4和7的个数直接加就可以
	k.sa=max(a.sa+b.tb,a.ta+b.sa);
	k.sb=max(a.sb+b.ta,a.tb+b.sb);
}
```
建树：
```cpp
void build(int k,int l,int r){
	if(l==r){
		t[k].sa=t[k].sb=1;//只有一个节点的区间，最长不下降及不上升子序列长度一定为1
		if(s[l]=='4')t[k].ta=1;//4的个数为1
		else t[k].tb=1;//7的个数为1
		return;
	}
	int m=l+r>>1,a=k<<1,b=a|1;
	build(a,l,m),build(b,m+1,r),up(t[k],t[a],t[b]);
}
```
修改：
```cpp
void upd(int k,int l,int r){//修改区间[u,v]
	if(u<=l&&r<=v)return rev(t[k]);//该区间全部被修改区间包含，直接翻转
	int m=l+r>>1,a=k<<1,b=a|1;
	if(t[k].t)t[k].t=0,rev(t[a]),rev(t[b]);//下传标记
	if(u<=m)upd(a,l,m);
	if(m<v)upd(b,m+1,r);
	up(t[k],t[a],t[b]);//合并
}
```
完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
struct T{
	bool t;
	int sa,sb,ta,tb;
}t[N<<2];
char s[N],o[9];
int u,v;
inline void rev(T&k){
	k.t^=1,swap(k.sa,k.sb),swap(k.ta,k.tb);
}
inline void up(T&k,T a,T b){
	k.ta=a.ta+b.ta,k.tb=a.tb+b.tb;
	k.sa=max(a.sa+b.tb,a.ta+b.sa);
	k.sb=max(a.sb+b.ta,a.tb+b.sb);
}
void build(int k,int l,int r){
	if(l==r){
		t[k].sa=t[k].sb=1;
		if(s[l]=='4')t[k].ta=1;
		else t[k].tb=1;
		return;
	}
	int m=l+r>>1,a=k<<1,b=a|1;
	build(a,l,m),build(b,m+1,r),up(t[k],t[a],t[b]);
}
void upd(int k,int l,int r){
	if(u<=l&&r<=v)return rev(t[k]);
	int m=l+r>>1,a=k<<1,b=a|1;
	if(t[k].t)t[k].t=0,rev(t[a]),rev(t[b]);
	if(u<=m)upd(a,l,m);
	if(m<v)upd(b,m+1,r);
	up(t[k],t[a],t[b]);
}
int main(){
	int n,m;
	scanf("%d%d%s",&n,&m,s+1),build(1,1,n);//建树
	while(m--){
		scanf("%s",o);
		if(o[0]=='s')scanf("%d%d",&u,&v),upd(1,1,n);//修改
		else printf("%d\n",t[1].sa);//查询
	}
	return 0;
}
```
思考题：将原题“最长不下降子序列”改为“最长不下降子段”，怎么做？其实方法几乎一样，但代码量更大，需要维护更多信息。

---

## 作者：ZBH_123 (赞：0)

## 一道线段树的模板题
### 1.分析题意
通过题目我们可以得知，这道题就是线段树“区间修改，区间查询”的操作。只不过，这道题的区间查询操作不再是常见的区间求和和 RMQ，而是变成了求最长不下降子序列的长度。
### 2.大体思路
通过题目的描述，我们可以想到，在线段树的每个结点上维护区间内最长不下降子序列的长度，就可以查询出题目要求的答案。接下来就会遇到一个问题：如何把两个子结点合并成一个结点呢？把两个子区间的最长不下降子序列的长度合并成这个区间的最长不下降子序列的长度，有两种情况需要讨论。由于本题中的序列只有两种数字：$4$ 和 $7$。所以，我们还需要记录两个信息，分别是这个区间内 $4$ 的个数 $sum1$ 和这个区间内 $7$ 的个数 $sum2$。在区间合并时，合并成的大区间的最长不下降子序列的长度 $len1$，就可以是左区间的 $sum1$ 加右区间的 $len1$，也可以是左区间的 $len1$ 加右区间的 $sum2$。那么，区间查询的问题就这样被我们解决了。

接下来是区间修改的操作。首先，由于区间内的 $4$ 要变成 $7$，$7$ 要变成 $4$，所以，我们需要交换 $sum1$ 和 $sum2$ 的值。那么，$len1$ 该如何改变呢？我们可以发现，当发生修改操作时，原本的最长不下降子序列就会变成最长不上升子序列，而原本的最长不上升子序列就会变成最长不下降子序列。也就是说，我们还得维护区间的最长不上升子序列的长度 $len2$。对于 $len2$ 的合并操作，我们可以借鉴一下 $len1$ 的合并操作，从而得到一下公式（$i$ 为合并后的区间，$j$ 和 $k$ 为待合并的区间）：
$$len2_{i}=\max(sum2_{j}+len2_{k},len2_{j}+sum1_{k})$$
### 3.代码实现
对于区间修改的操作，我们需要一个懒惰标记，否则每次都要到叶结点再返回，这样时间复杂度会很高。懒惰标记里记录该序列是否改变过。由于在本题中，对同一个区间进行两次操作，就相当于没有修改，这时，我们就能想到一种运算：异或。由于 $1 \operatorname{xor} 1=0$，$0 \operatorname{xor} 1=1$，所以每一次区间修改时就把区间上的懒惰标记异或上 $1$，每次遇到懒惰标记为 $1$ 的区间就把懒惰标记下传，把两个子区间的懒惰标记分别异或上 $1$，并对子区间的各个数值进行修改，就可以解决这个问题了。

#### AC Code:
```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int n,q,x,y,a[1000001];
string s,t;
struct node{
	int l,r,sum1,sum2,len1,len2,lazy;
}bt[4000001];
void pushup(int x){//合并区间
	bt[x].sum1=bt[x*2].sum1+bt[x*2+1].sum1;
	bt[x].sum2=bt[x*2].sum2+bt[x*2+1].sum2;
	bt[x].len1=max(bt[x*2].sum1+bt[x*2+1].len1,bt[x*2].len1+bt[x*2+1].sum2);//合并最长不下降子序列的长度
	bt[x].len2=max(bt[x*2].sum2+bt[x*2+1].len2,bt[x*2].len2+bt[x*2+1].sum1);//合并最长不上升子序列的长度
}
void pushdown(int x){//下传懒惰标记
	if(bt[x].lazy){
		bt[x*2].lazy^=1,bt[x*2+1].lazy^=1;
		swap(bt[x*2].sum1,bt[x*2].sum2);
		swap(bt[x*2+1].sum1,bt[x*2+1].sum2);
		swap(bt[x*2].len1,bt[x*2].len2);
		swap(bt[x*2+1].len1,bt[x*2+1].len2);
		bt[x].lazy=0;//清空懒惰标记
	}
}
void build(int x,int l,int r){//建树
	bt[x].l=l,bt[x].r=r;
	if(l==r){
		bt[x].len1=bt[x].len2=1;
		if(a[l]==4)
			bt[x].sum1=1;
		else
			bt[x].sum2=1;
		return;
	}
	int mid=l+r>>1;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	pushup(x);
}
void rev(int x,int l,int r){//区间修改
	if(bt[x].l>=l&&bt[x].r<=r){
		swap(bt[x].sum1,bt[x].sum2);
		swap(bt[x].len1,bt[x].len2);
		bt[x].lazy^=1;//修改懒惰标记
		return;
	}
	pushdown(x);
	int mid=bt[x].l+bt[x].r>>1;
	if(r<=mid)
		rev(x*2,l,r);
	else if(l>mid)
		rev(x*2+1,l,r);
	else{
		rev(x*2,l,mid);
		rev(x*2+1,mid+1,r);
	}
	pushup(x);
}
node find(int x,int l,int r){//区间查询，可省略
	if(bt[x].l>=l&&bt[x].r<=r)
		return bt[x];
	pushdown(x);
	int mid=bt[x].l+bt[x].r>>1;
	if(r<=mid)
		return find(x*2,l,r);
	else if(l>mid)
		return find(x*2+1,l,r);
	else{
		node a=find(x*2,l,mid),b=find(x*2+1,mid+1,r);
		return (node){a.l,b.r,a.sum1+b.sum1,a.sum2+b.sum2,max(a.sum1+b.len1,a.len1+b.sum2),max(a.sum2+b.len2,a.len2+b.sum1)};
	}
}
int main(){
	scanf("%d%d",&n,&q);
	cin>>s;
	for(int i=0;i<n;i++)
		a[i+1]=s[i]-'0';
	build(1,1,n);
	for(int i=1;i<=q;i++){
		cin>>t;
		if(t=="count")
			printf("%d\n",find(1,1,n).len1);//可以直接输出bt[1].len1，因为1号结点存储的是1到n的最长不下降子序列的长度
		else{
			scanf("%d%d",&x,&y);
			rev(1,x,y);
		}
	}
	return 0;
}
```

---

## 作者：Acee (赞：0)

线段树水题。

看询问，维护一下 $4$ 的个数与 $7$ 的个数。
然后可以发现最长不下降子序列一定先是若干个 $4$，然后是若干个 $7$。

由于有区间反转，再维护一下不上升子序列，然后交换就行了。

于是 `pushup` 就应该这样写:

```cpp
SegmentTree merge(SegmentTree ls, SegmentTree rs) {
	SegmentTree ans;
	ans.cql = ls.cql + rs.cql;
	ans.jrx = ls.jrx + rs.jrx;
	ans.tk = max(ls.tk + rs.cql, ls.jrx + rs.tk);
	ans.lql = max(ls.lql + rs.jrx, ls.cql + rs.lql);
	return ans;
}
```


代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Main {
	const int N = 1e6 + 5;
	int n, m;
	int s[N];
	int Root;
	int TreeCnt;
	struct SegmentTree {
		int cql, jrx;//cql:xia, jrx:shang
		int tk, lql;//tk:shang, lql:xia
		mutable int hyz, yhy;//hyz:shang(lson), yhy:xia(rson)
		bool love;
	} t[N << 2];
	// void newnode(int &p) {
	// 	if (!p) p = ++TreeCnt;
	// }
	SegmentTree merge(SegmentTree ls, SegmentTree rs) {
		SegmentTree ans;
		ans.cql = ls.cql + rs.cql;
		ans.jrx = ls.jrx + rs.jrx;
		ans.tk = max(ls.tk + rs.cql, ls.jrx + rs.tk);
		ans.lql = max(ls.lql + rs.jrx, ls.cql + rs.lql);
		return ans;
	}
	void pushup(int p) {
	//	cout << p << ' ' << p << 1 << ' ' << p << 1 | 1 << '\n';
		t[p] = merge(t[p << 1], t[p << 1 | 1]);
		// cout << p << '\n';
		// printf("%d %d\n%d %d\n", t[Root].cql, t[Root].jrx, t[Root].lql, t[Root].tk);

	}
	void makelove(int p) {
		// cout << p << '\n';
		t[p].love ^= 1;
		swap(t[p].cql, t[p].jrx);
		swap(t[p].tk, t[p].lql);
		// printf("%d %d\n%d %d\n", t[Root].cql, t[Root].jrx, t[Root].lql, t[Root].tk);

	}
	void pushdown(int p) {
		if (t[p].love) {
			// cout << p << '\n';
			// newnode(p << 1);
			// newnode(p << 1 | 1);
			makelove(p << 1);
			makelove(p << 1 | 1);
			t[p].love = 0;
		}
	}
	void build(int p, int l, int r) {
		if (l == r) {
			t[p].cql = (s[l] == 4);
			t[p].jrx = (s[l] == 7);
			t[p].tk = t[p].lql = 1;
			// cout << l << ' ' << p << '\n';
			return;
		}
		int mid = (l + r) >> 1;
		// p << 1 = p << 1;
		// p << 1 | 1 = p << 1 | 1;
		// cout << p << ' ' << p << 1 << ' ' << p << 1 | 1 << '\n';
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		pushup(p);
	}
	void change(int p, int l, int r, int x, int y) {
		// newnode(p);
		// cout << "CQL = " << p << '\n';
		// cout << p << 1 << ' ' << p << 1 | 1 << '\n';
		if (x <= l && r <= y) {
			// cout << l << ' ' << r << '\n';
			makelove(p);
			return;
		}
		pushdown(p);
		int mid = (l + r) >> 1;
		if (x <= mid) change(p << 1, l, mid, x, y);
		if (y > mid) change(p << 1 | 1, mid + 1, r, x, y);
		pushup(p);
	}
	SegmentTree ask(int p, int l, int r, int x, int y) {
		// newnode(p);
		if (x <= l && r <= y) {
			return t[p];
		}
		pushdown(p);
		pushup(p);
		int mid = (l + r) >> 1;
		if (y <= mid) return ask(p << 1, l, mid, x, y);
		if (x > mid) return ask(p << 1 | 1, mid + 1, r, x, y);
		return merge(ask(p << 1, l, mid, x, y), ask(p << 1 | 1, mid + 1, r, x, y));
	}
	int main() {
		// ios :: sync_with_stdio(false);
		// cin.tie(0), cout.tie(0);
		scanf ("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%1d", &s[i]);
		}
		Root = ++TreeCnt;
		build(Root, 1, n);
		char op[12];
		for (int ti = 1, l, r; ti <= m; ++ti) {
			scanf ("%s", op);
			if (op[0] == 'c') {
				printf("%d\n", t[Root].lql);
			}
			else {
				scanf ("%d%d", &l, &r);
				change(Root, 1, n, l, r);
			}
			// for (int i = 1; i <= 5; ++i) {
			// 	printf ("%d %d\n", t[i].hyz, t[i].yhy);
			// 	printf("%d %d\n%d %d\n", t[i].cql, t[i].jrx, t[i].lql, t[i].tk);
			// }
		}
		return 0;
	}
}
int main() {
	Main :: main();
	return 0;
}
```

---

## 作者：流水行船CCD (赞：0)

# 思路

不错的线段树版子

很明显，这题因为操作是区间取反，区间查询，考虑线段树。

因为数列中有且仅有数字 $4$，$7$，因此最长不下降子序列有且仅有以下三种形态。

$$444444444...444444444$$

$$777777777...777777777$$

$$444444444...777777777$$

因此我们维护以上三种序列的最长长度，最后取最大值就是整个数列的最长不下降子序列。

那取反操作该怎么维护，注意到在取反操作后序列中原本 $a_i \le a_j$ 的关系会变成 $a_j \le a_i$，即原本的最长不下降子序列会变成取反后的最长不上升子序列，这样，我们只需要同时去维护当前区间的最长不下降子序列和最长不上升子序列，在取反操作时交换它们的值就可以了。

例子：

`4747477`

不下降：`44477  len=5`

不上升：`7777  len=4`

`switch 1 7`

`7474744`

不下降：`4444  len=4`

不上升：`77444  len=5`


# AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e6+7;
int split,marge;
struct lyt{
	int l,r;
	int tag,val;
	int len4[2],len7[2],len47[2];
	int ans;
}st[N];
int arr[N],n,m;
void pushup(int u){
	st[u].len4[0]=st[2*u].len4[0]+st[2*u+1].len4[0];
	st[u].len7[0]=st[2*u].len7[0]+st[2*u+1].len7[0];
	st[u].len47[0]=max(st[2*u].len47[0]+st[2*u+1].len7[0],st[2*u].len4[0]+st[2*u+1].len47[0]);
	st[u].len47[0]=max(st[u].len47[0],st[2*u].len4[0]+st[2*u+1].len7[0]);
	st[u].ans=max(st[u].len47[0],max(st[u].len4[0],st[u].len7[0]));
	st[u].len4[1]=st[2*u].len4[1]+st[2*u+1].len4[1];
	st[u].len7[1]=st[2*u].len7[1]+st[2*u+1].len7[1];
	st[u].len47[1]=max(st[2*u].len47[1]+st[2*u+1].len7[1],st[2*u].len4[1]+st[2*u+1].len47[1]);
	st[u].len47[1]=max(st[u].len47[1],st[2*u].len4[1]+st[2*u+1].len7[1]);
	return;
}//7777774
void pushdown(int u){
	if(st[u].tag){
		swap(st[2*u].len4[0],st[2*u].len4[1]);
		swap(st[2*u].len7[0],st[2*u].len7[1]);
		swap(st[2*u].len47[0],st[2*u].len47[1]);
		st[2*u].ans=max(st[2*u].len47[0],max(st[2*u].len4[0],st[2*u].len7[0]));
		swap(st[2*u+1].len4[0],st[2*u+1].len4[1]);
		swap(st[2*u+1].len7[0],st[2*u+1].len7[1]);
		swap(st[2*u+1].len47[0],st[2*u+1].len47[1]);
		st[2*u+1].ans=max(st[2*u+1].len47[0],max(st[2*u+1].len4[0],st[2*u+1].len7[0]));
		st[2*u].tag^=1;st[2*u+1].tag^=1;
		st[u].tag=0;
	}
	return;
}
void build(int u,int l,int r){
	st[u].l=l;st[u].r=r;st[u].tag=0;
	//cout<<u<<' '<<l<<' '<<r<<endl;
	if(l==r){
		st[u].val=arr[l];
		st[u].len4[0]=(arr[l]==4);
		st[u].len7[0]=(arr[l]==7);
		st[u].len47[0]=0;
		st[u].ans=1;
		st[u].len4[1]=(arr[l]==7);
		st[u].len7[1]=(arr[l]==4);
		st[u].len47[1]=0;
		return;
	}
	int mid=(l+r)>>1;
	build((u<<1),l,mid);
	build(((u<<1)+1),mid+1,r); 
	pushup(u);
	return;
}
void updata(int u,int l,int r){
	//cout<<u<<' '<<l<<' '<<r<<endl;
	if(l>=split&&r<=marge){
		st[u].tag^=1;
		swap(st[u].len4[0],st[u].len4[1]);
		swap(st[u].len7[0],st[u].len7[1]);
		swap(st[u].len47[0],st[u].len47[1]);
		st[u].ans=max(st[u].len47[0],max(st[u].len4[0],st[u].len7[0]));
		//pushup(u);
		return;
	}
	pushdown(u);
	int mid=(l+r)>>1;
	if(mid>=split){
		updata((u<<1),l,mid);
	}
	if(mid+1<=marge){
		updata(((u<<1)+1),mid+1,r); 
	}
	pushup(u);
	return;
}
signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%1d",&arr[i]);
	}
	build(1,1,n);
	for(int i=1;i<=m;i++){
		char ch[114];
		scanf("%s",ch);
		if(ch[0]=='s'){
			scanf("%d%d",&split,&marge);
			updata(1,1,n);
		}else{
			printf("%d\n",st[1].ans);
		}
//		for(int i=0;i<=1;i++){
//			cout<<st[1].len4[i]<<' '<<st[1].len7[i]<<' '<<st[1].len47[i]<<endl;
//		}
//		cout<<st[1].ans<<endl;
	}
	return 0;
}//YEEE

```

---

## 作者：IkunTeddy (赞：0)

# 题目大意
给出一个由 $4$ 和 $7$ 组成的序列，有翻转子序列和查询最长不下降子序列的长度这两种操作。
# 做法分析
这种区间修改和区间查询的题目一看就能想到是线段树，用线段树维护一个最长不下降子序列的长度就行，那这个翻转又该怎么解决呢。

经过一番研究后会发现，一个序列翻转过来后最长不下降子序列的长度就是翻转前序列的最长不上升子序列的长度，那现在就简单了，同时维护他们两个就行了。
# Code
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define ls 2*v
#define rs 2*v+1
using namespace std;
const int maxn=1000000+10;
int a[maxn];
struct node{
	int l,r;
	int sum[2];
	int len[2];
	int lazy;
}tree[4*maxn];
void pushup(int v){
	tree[v].sum[1]=tree[ls].sum[1]+tree[rs].sum[1];
	tree[v].sum[0]=tree[ls].sum[0]+tree[rs].sum[0];
	tree[v].len[1]=max(tree[ls].len[1]+tree[rs].sum[1],tree[ls].sum[0]+tree[rs].len[1]);
	tree[v].len[0]=max(tree[ls].len[0]+tree[rs].sum[0],tree[ls].sum[1]+tree[rs].len[0]);
}
void pushdown(int v){
	if(tree[v].lazy){
		tree[ls].lazy^=1;
		swap(tree[ls].sum[0],tree[ls].sum[1]);
		swap(tree[ls].len[0],tree[ls].len[1]);
		
		tree[rs].lazy^=1;
		swap(tree[rs].sum[0],tree[rs].sum[1]);
		swap(tree[rs].len[0],tree[rs].len[1]);
		
		tree[v].lazy=0;
	}
}
void build(int l,int r,int v){
	tree[v].l=l;
	tree[v].r=r;
	tree[v].lazy=0;
	if(l==r){
		if(a[l]==1) tree[v].sum[1]=1;
		else tree[v].sum[0]=1;
		tree[v].len[1]=1;
		tree[v].len[0]=1;
		return ;
	}
	int mid=(l+r)/2;
	build(l,mid,ls);
	build(mid+1,r,rs);
	pushup(v);
}
void update(int x,int y,int v){
	int l=tree[v].l;
	int r=tree[v].r;
	if(l==x&&r==y){
		tree[v].lazy^=1;
		swap(tree[v].sum[0],tree[v].sum[1]);
		swap(tree[v].len[0],tree[v].len[1]);
		return ;
	}
	pushdown(v);
	int mid=(l+r)/2;
	if(y<=mid) update(x,y,ls);
	else if(x>mid) update(x,y,rs);
	else{
		update(x,mid,ls);
		update(mid+1,y,rs);
	}
	pushup(v);
	
}
int main(){
	int n,m;
	cin>>n>>m;
	getchar(); //这里需读一个回车字符不然会出问题 
	for(int i=1;i<=n;i++){
		char c;
		scanf("%c",&c);
		if(c=='4'){
			a[i]=0;
		}else{
			a[i]=1;
		}
	}
	build(1,n,1);
	for(int i=1;i<=m;i++){
		string s;
		cin>>s;
		if(s[0]=='s'){
			int x,y;
			scanf("%d%d",&x,&y);
			update(x,y,1);
		}else{
			cout<<tree[1].len[1]<<endl;
		}
	}

	return 0;
}


```


---

## 作者：Astatinear (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF145E)

### 思路

**线段树。**

看到这个题的数据范围，以及这样的区间修改和区间查询的操作，不难想到使用线段树来求解。

我们可以对于线段树上的每一个区间，维护 $4$ 个值，分别是：该区间 $4$ 出现的次数，该区间 $7$ 出现的次数，该区间的最长不下降子序列的长度，该区间的最长不上升子序列的长度。

显然，再建树时，对于求 $4,7$ 在区间上出现的次数这个比较简单，这里不做阐述，主要来看一下不下降和不上升子序列的长度该怎么求。

对于不下降子序列来说，一共有两种情况：

+ 当前区间左孩子的最长不下降子序列长度 $+$ 当前区间右孩子的数字 $7$ 的个数。

+ 当前区间左孩子的 $4$ 的个数 $+$ 当前区间右孩子的最长不下降子序列长度。

所以，我们只需要将两个值取最大值即可。

对于不上升子序列来说，也是一样。

然后，我们来看反转操作。

如果要将一个区间的数进行翻转的话，对于 $4$ 和 $7$ 出现的次数，我们只需要将这两个值进行交换，而对于不上升和不下降子序列来说，也是将两个值交换即可。但由于是区间翻转，所以需要使用懒惰标记。

最后查询时，我们只需要输出第一个区间的最长不下降子序列长度即可。

最后一个小提示：由于输入数据很大，千万不要使用 $cin$ 不然会 T 到飞起！

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct segmentree
{
	int l,r;
	int num4,num7;//4 的个数，7的个数
	int val1,val2;//不下降和不上升
	int lazytag;//懒惰标记
}tree[4000005];
int n,m;
char a[1000005];
void build(int p,int l,int r)//建树操作。
{
	tree[p].l=l,tree[p].r=r;
	if(l==r)
	{
		if(a[l]=='4') tree[p].num4++;
		else tree[p].num7++;
		tree[p].val1=tree[p].val2=1;
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	tree[p].num4=tree[p*2].num4+tree[p*2+1].num4;//思路中有阐述，这里不做过多介绍。
	tree[p].num7=tree[p*2].num7+tree[p*2+1].num7;
	tree[p].val1=max(tree[p*2].val1+tree[p*2+1].num7,tree[p*2].num4+tree[p*2+1].val1);
	tree[p].val2=max(tree[p*2].val2+tree[p*2+1].num4,tree[p*2].num7+tree[p*2+1].val2);
}
void pushdown(int p)//标记下传操作
{
	if(tree[p].lazytag)
	{
		int l=p*2,r=p*2+1,tag=tree[p].lazytag;
		tree[p].lazytag=0;
		swap(tree[l].num4,tree[l].num7);
		swap(tree[r].num4,tree[r].num7);
		swap(tree[l].val1,tree[l].val2);
		swap(tree[r].val1,tree[r].val2);
		tree[l].lazytag^=tag;
		tree[r].lazytag^=tag;
	}
}
void change(int p,int l,int r)//翻转操作。
{
	if(tree[p].r<l||tree[p].l>r)
	return;
	if(tree[p].l>=l&&tree[p].r<=r)
	{
		tree[p].lazytag^=1;
		swap(tree[p].val1,tree[p].val2);
		swap(tree[p].num4,tree[p].num7);
		return;
	}
	pushdown(p);
	change(p*2,l,r);
	change(p*2+1,l,r);
	tree[p].num4=tree[p*2].num4+tree[p*2+1].num4;
	tree[p].num7=tree[p*2].num7+tree[p*2+1].num7;
	tree[p].val1=max(tree[p*2].val1+tree[p*2+1].num7,tree[p*2].num4+tree[p*2+1].val1);
	tree[p].val2=max(tree[p*2].val2+tree[p*2+1].num4,tree[p*2].num7+tree[p*2+1].val2);
}
int main()
{
	scanf("%d%d\n",&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%c",&a[i]);
	}
	build(1,1,n);
	while(m--)
	{
		char s[10];
		scanf("%s",s);
		if(s[0]=='c')
		{
			printf("%d\n",tree[1].val1);
		}
		else
		{
			int l,r;
			cin>>l>>r;
			change(1,l,r);
		}
	}
	return 0;
}
```

---

## 作者：crn1 (赞：0)

由区间修改和数据范围想到线段树。

考虑如何维护节点信息。每个节点保存三个值：$4$ 的个数，$7$ 的个数，以及最长不下降子序列的长度。

最长不下降子序列分为两种情况
1. 选择左节点中的全部 $4$ 和右节点的最长不下降子序列。
2. 选择左节点的最长不下降子序列和右节点中的全部 $7$。

接着考虑如何进行修改操作，因为个数 $n$ 最大达 $10^6$，且有最多 $3\times 10^5$ 个询问，需使用懒惰标记保证复杂度为 $\mathcal{O(m\log n)}$。

假设不使用懒惰标记，对于每个节点，只需交换 $4$ 的个数和 $7$ 的个数，再重新计算最长不下降子序列长度即可。接着加上懒惰标记，仍然交换 $4$ 和 $7$ 的个数，但是最长不下降子序列的长度不能和之前一样直接计算了。虽然不能直接计算最长不下降子序列的长度，但是最长不下降子序列的长度等于将其更改后的最长不上升子序列。

举个例子
```
原序列 : 4 4 7 4 7
最长不降子序列 : 4 4 4 7
```
将其更改后为
```
更改后的序列 : 7 7 4 7 4
最长不升子序列 : 7 7 7 4
```

于是我们可以同时维护最长不降子序列和最长不升子序列，最长不升子序列计算方式与最长不降子序列计算方式大同小异，进行 $switch$ 操作时交换即可。

代码
```cpp
#include <algorithm>
#include <cstdio>
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

const int N = 1000005;
char t[N]; bool a[N];

struct sgt {
	int l, r, lz;
	int a, b, res, res_; // res 是最长不降子序列，res_ 是最长不升子序列
} tr[N << 2];

void push(int p) {
	if (tr[p].lz) {
		std::swap(tr[ls(p)].a, tr[ls(p)].b); // 交换 4 和 7 的个数
		std::swap(tr[ls(p)].res, tr[ls(p)].res_); // 交换最长不降子序列和最长不升子序列的长度
		tr[ls(p)].lz ^= 1; // 下传标记
		std::swap(tr[rs(p)].a, tr[rs(p)].b);
		std::swap(tr[rs(p)].res, tr[rs(p)].res_);
		tr[rs(p)].lz ^= 1;
		tr[p].lz = 0;
	}
}

void build(int l, int r, int p) {
	tr[p].l = l, tr[p].r = r;
	if (l == r) {
		tr[p].a = a[l] == 0;
		tr[p].b = a[l] == 1;
		tr[p].res = tr[p].res_ = 1;
		return;
	}
	int mid = l + r >> 1;
	build(l, mid, ls(p));
	build(mid + 1, r, rs(p));
	tr[p].a = tr[ls(p)].a + tr[rs(p)].a; // 计算 4 的个数
	tr[p].b = tr[ls(p)].b + tr[rs(p)].b; // 计算 7 的个数
	tr[p].res = std::max(tr[ls(p)].a + tr[rs(p)].res, tr[ls(p)].res + tr[rs(p)].b); // 计算最长不降子序列的长度
	tr[p].res_ = std::max(tr[ls(p)].res_ + tr[rs(p)].a, tr[ls(p)].b + tr[rs(p)].res_); // 计算最长不升子序列的长度
}

void modify(int l, int r, int p) {
	if (l <= tr[p].l && tr[p].r <= r) {
		tr[p].lz ^= 1;
		std::swap(tr[p].a, tr[p].b);
		std::swap(tr[p].res, tr[p].res_);
		return;
	}
	push(p);
	int mid = tr[p].l + tr[p].r >> 1;
	if (l <= mid) modify(l, r, ls(p));
	if (r > mid) modify(l, r, rs(p));
	tr[p].a = tr[ls(p)].a + tr[rs(p)].a;
	tr[p].b = tr[ls(p)].b + tr[rs(p)].b;
	tr[p].res = std::max(tr[ls(p)].a + tr[rs(p)].res, tr[ls(p)].res + tr[rs(p)].b);
	tr[p].res_ = std::max(tr[ls(p)].res_ + tr[rs(p)].a, tr[ls(p)].b + tr[rs(p)].res_);
}

int main(void) {
	int n, m; scanf("%d %d", &n, &m);
	scanf("%s", t + 1);
	for (int i = 1; i <= n; i++)
		a[i] = t[i] == '4' ? 0 : 1;
	build(1, n, 1);
	for (int i = 1; i <= m; i++) {
		char op[10];
		scanf("%s", op + 1);
		if (op[1] == 'c') printf("%d\n", tr[1].res);
		else {
			int l, r; scanf("%d %d", &l, &r);
			modify(l, r, 1);
		}
	}
	return 0;
} 
```

---

## 作者：Steven_Meng (赞：0)

一看数据范围就知道是线段树

不过怎样区间翻转是一个问题

这里的思想非常巧妙

**记录最长不上升子序列的长度**

在区间翻转的时候,交换最长不上升子序列的长度和最长不下降子序列的长度即可.

还有合并区间时需要用到一点dp的思想

代码有点丑神犇勿喷

code:

```cpp
#include <iostream>
#include <cstdio>
#define MAXN 1000005
#define ll int
using namespace std;
struct node{
    int sheng,jiang,seven,four;
    bool lazy;
}tree[MAXN*4];
int max(int a,int b){
    return a>b?a:b;
}
int n,m;
void swap(int &a,int &b){
    int t=a;
    a=b;
    b=t;
}
char str[MAXN];
void push_up(int i){
    tree[i].seven=tree[i<<1].seven+tree[i<<1|1].seven;
    tree[i].four=tree[i<<1].four+tree[i<<1|1].four;
    int max1=max(tree[i<<1].sheng+tree[i<<1|1].seven,tree[i<<1].four+tree[i<<1|1].sheng);
    tree[i].sheng=max(max1,tree[i<<1].four+tree[i<<1|1].seven);
    //可能前面不下降,后面全7
    //可能前面全4,后面不下降
    //可能前面全4,后面全7
    int max2=max(tree[i<<1].jiang+tree[i<<1|1].four,tree[i<<1].seven+tree[i<<1|1].jiang);
    tree[i].jiang=max(max2,tree[i<<1].seven+tree[i<<1|1].four);
    //同理
}
void buildtree(int l,int r,int i){
    if (l==r){
        tree[i].sheng=1;
        tree[i].jiang=1;
        tree[i].seven=(str[l]=='7');
        tree[i].four=!tree[i].seven;
        return ;
    }
    int mid=(l+r)>>1;
    buildtree(l,mid,i<<1);
    buildtree(mid+1,r,i<<1|1);
    push_up(i);
}
void rev(int i){
    tree[i].lazy=!tree[i].lazy;
    swap(tree[i].four,tree[i].seven);
    swap(tree[i].jiang,tree[i].sheng);
    //区间翻转需要swap一下
}
void update(int l,int r,int L,int R,int i){
    if (r<L||l>R){
        return ;
    }
    if (r<=R&&l>=L){
        rev(i);
        return ;
    }
    if (tree[i].lazy){
        tree[i].lazy=false;
        rev(i<<1);
        rev(i<<1|1);
    }
	int mid=(l+r)>>1;
	if (mid>=r){
		update(l,mid,L,R,i<<1);
	}
    else if (l>mid){
    	update(mid+1,r,L,R,i<<1|1);
	}
	else {
		update(l,mid,L,R,i<<1);
		update(mid+1,r,L,R,i<<1|1);
	}
    push_up(i);
}
int main(){
    scanf("%d%d%s",&n,&m,str+1);
    buildtree(1,n,1);
    int ans;
    for (int t=0;t<m;t++){
        char ch[100];
        scanf("%s",ch);
        if (ch[0]=='c'){
            printf("%d\n",tree[1].sheng);
        }
        else {
            int l,r;
            scanf("%d%d",&l,&r);
            update(1,n,l,r,1);
        }
    }
}
```

---

