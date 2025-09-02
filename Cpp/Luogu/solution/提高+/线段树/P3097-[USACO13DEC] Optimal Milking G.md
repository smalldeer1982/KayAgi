# [USACO13DEC] Optimal Milking G

## 题目描述

Farmer John has recently purchased a new barn containing N milking machines (1 <= N <= 40,000), conveniently numbered 1..N and arranged in a row.

Milking machine i is capable of extracting M(i) units of milk per day (1 <= M(i) <= 100,000).  Unfortunately, the machines were installed so close together that if a machine i is in use on a particular day, its two neighboring machines cannot be used that day (endpoint machines have only one neighbor, of course).  Farmer John is free to select different subsets of machines to operate on different days.

Farmer John is interested in computing the maximum amount of milk he can extract over a series of D days (1 <= D <= 50,000).  At the beginning of each day, he has enough time to perform maintenance on one selected milking machine i, thereby changing its daily milk output M(i) from that day forward. Given a list of these daily modifications, please tell Farmer John how much milk he can produce over D days (note that this number might not fit into a 32-bit integer).

FJ最近买了1个新仓库, 内含N 个挤奶机,1 到N 编号并排成一行。


挤奶机i 每天能产出M(i) 单位的奶。不幸的是, 机器装得太近以至于如果一台机器i 在某天被使用, 那与它相邻的两台机器那一天不能被使用


(当然, 两端点处的机器分别只有一个与之相邻的机器)。


FJ 可自由选择不同的机器在不同的日子工作。


FJ感兴趣于计算在D 天内他能产出奶的最大值。在每天开始时, 他有足够的时间维护一个选中的挤奶机i, 从而改变它从那天起的每日产奶量M(i)。


给出这些每日的修改,请告诉FJ他D 天中能产多少奶。


## 说明/提示

There are 5 machines, with initial milk outputs 1,2,3,4,5.  On day 1, machine 5 is updated to output 2 unit of milk, and so on.


On day one, the optimal amount of milk is 2+4 = 6 (also achievable as 1+3+2).  On day two, the optimal amount is 7+4 = 11.  On day three, the optimal amount is 10+3+2=15.

题意简述：给定n个点排成一排，每个点有一个点权，多次改变某个点的点权并将最大点独立集计入答案，输出最终的答案

感谢@zht467 提供翻译


## 样例 #1

### 输入

```
5 3 
1 
2 
3 
4 
5 
5 2 
2 7 
1 10 
```

### 输出

```
32 
```

# 题解

## 作者：wurzang (赞：11)

来补一个动态 dp 做法。


题意大致就是单点修改求最大独立集

暴力 dp 大概就是

$$
\begin{cases}
f_{i,0}=\max\limits \{ f_{i-1,0},f_{i-1,1}\} \\
f_{i,1}=f_{i-1,0}+a_i
\end{cases}

$$

最后是要求 $\max\{ f_{n,0},f_{n,1} \}$

考虑这个东西怎么转为矩阵形式。

这里我们定义矩阵乘法为

$$
c_{i,j}=\max\limits_{k} \{ a_{i,k}+b_{k,j} \}
$$

这个东西是满足结合律的。

于是上面那个暴力 dp 可以看成是

$$
\begin{bmatrix}f_{i-1,0}\\ f_{i-1,1}\end{bmatrix}
\begin{bmatrix}0 \  \ \ \  \ 0 \\ a_i\ \operatorname{-inf} \end{bmatrix}= \begin{bmatrix} f_{i,0} \\f_{i,1} \end{bmatrix}
$$


然后用线段树维护矩阵乘即可。


代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls p<<1
#define rs p<<1|1
const int N=40000+5;
// f[i][0]=max(f[i-1][0],f[i-1][1])
// f[i][1]=f[i-1][0]+a[i]
// |  0 0      |  
// |  a_i -inf |
struct mat{
	int a[2][2];
	mat(){
		memset(a,-0x3f,sizeof(a));
	}
	mat operator *(const mat &b) const{
		mat res;
		for(int i=0;i<2;++i)
			for(int j=0;j<2;++j)
				for(int k=0;k<2;++k)
					res.a[i][j]=max(res.a[i][j],a[i][k]+b.a[k][j]);
		return res;
	}
}tr[N<<2];
int a[N];
void pushup(int p){
	tr[p]=tr[rs]*tr[ls];
}
void build(int p,int l,int r){
	if(l==r){
		tr[p].a[0][0]=0;
		tr[p].a[0][1]=0;
		tr[p].a[1][0]=a[l];
		tr[p].a[1][1]=-0x3f3f3f3f;
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(p);
}
void upt(int p,int l,int r,int pos,int v){
	if(l==r){
		tr[p].a[0][0]=0;
		tr[p].a[0][1]=0;
		tr[p].a[1][0]=v;
		tr[p].a[1][1]=-0x3f3f3f3f;
		return;		
	}
	int mid=(l+r)>>1;
	if(pos<=mid) upt(ls,l,mid,pos,v);
	else upt(rs,mid+1,r,pos,v);
	pushup(p);
}
int main(){
	long long ans=0;
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	int pos,v;
	build(1,1,n);
	mat res,tmp;
	res.a[0][0]=0;res.a[0][1]=0;
	while(q--){
		cin>>pos>>v;
		upt(1,1,n,pos,v);
		tmp=res*tr[1];
		ans+=max(tmp.a[0][0],tmp.a[0][1]);
		//cout<<max(tmp.a[0][0],tmp.a[0][1])<<endl;
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：LlLlCc (赞：9)

看大家都是写的线段树，这里提供一种分块做法

------------

先将序列分成$\sqrt n$块，然后对每一个块内进行$DP$，处理这个块的左右两端分别取或不去的最大值，然后把每个块看出一个点，再跑一遍，这样一次预处理的复杂度是$O(N)$。

修改的话，因为我们是对每一块内进行分别$DP$，所以每个块内互不影响，我们只需要对修改的那个点所在的块重新$DP$一遍就行

复杂度为$O(n \sqrt n)$，水过去没问题，不过不开O2最大点要跑$500ms$，如果会线段树做法建议还是打线段树，分块比较还是比较暴力

## code
```
#include<bits/stdc++.h>
#define maxn 40005
#define ll long long
using namespace std;
int n,N,Q,x,y,id[maxn],a[maxn],tot[205],A[205][205],Id[maxn];
ll f[205][2],F[205][2][2],G[205][2],Ans,Cnt;
bool vis[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline ll Solve(){
	for (int i=1;i<=id[n];i++){
		if (vis[i]) continue;
		for (int j=1;j<=tot[i];j++) f[j][0]=max(f[j-1][0],f[j-1][1]),f[j][1]=f[j-1][0]+A[i][j];
		F[i][1][1]=f[tot[i]][1],F[i][1][0]=f[tot[i]][0];
		f[1][0]=f[1][1]=0;
		for (int j=2;j<=tot[i];j++) f[j][0]=max(f[j-1][0],f[j-1][1]),f[j][1]=f[j-1][0]+A[i][j];
	    F[i][0][1]=f[tot[i]][1],F[i][0][0]=f[tot[i]][0];
	    vis[i]=1;
	}
	G[1][0]=max(F[1][0][0],F[1][1][0]),G[1][1]=max(F[1][0][1],F[1][1][1]);
	for (int i=2;i<=id[n];i++) G[i][0]=max(G[i-1][0]+max(F[i][0][0],F[i][1][0]),G[i-1][1]+F[i][0][0]),G[i][1]=max(G[i-1][0]+max(F[i][0][1],F[i][1][1]),G[i-1][1]+F[i][0][1]);
	return max(G[id[n]][0],G[id[n]][1]);
}
int main(){
	n=read(),Q=read();N=sqrt(n);
	for (int i=1;i<=n;i++) a[i]=read(),id[i]=(i-1)/N+1;
	for (int i=1;i<=n;i++) A[id[i]][++tot[id[i]]]=a[i],Id[i]=tot[id[i]];
    Cnt=Solve();
	while (Q--) x=read(),y=read(),A[id[x]][Id[x]]=y,vis[id[x]]=0,Ans+=Solve();
	printf("%lld",Ans);
	return 0;
}
```


---

## 作者：zcysky (赞：9)

这个范围肯定不是让你跑最大点独立集的，这很显然。

那么我们考虑下可能的情况

无非是两个端点选或者不选的组合

于是就可以用线段树维护了。

```cpp
#include<bits/stdc++.h>
#define N 50010
#define lson (o<<1)
#define rson (o<<1|1)
using namespace std;
typedef long long ll;
int f[N<<2][4],n,m;
ll ans=0;
inline int read(){
    int f=1,x=0;char ch;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    return f*x;
}
inline int max(int a,int b,int c){return max(max(a,b),c);}
inline int max(int a,int b,int c,int d){return max(max(a,b),max(c,d));}
inline void pushup(int o){
    for(int i=0;i<4;i++)
        f[o][i]=max(f[lson][i&2]+f[rson][2+(i&1)],f[lson][(i&2)+0]+f[rson][i&1],f[lson][(i&2)+1]+f[rson][i&1]);
}
void build(int o,int l,int r){
    if(l==r){f[o][3]=read();return;}
    int mid=(l+r)>>1;
    build(lson,l,mid);build(rson,mid+1,r);
    pushup(o);
}
void change(int o,int l,int r,int q,int v){
    if(l==r){f[o][3]=v;return;}
    int mid=(l+r)>>1;
    if(q<=mid)change(lson,l,mid,q,v);
    else change(rson,mid+1,r,q,v);
    pushup(o);
}
int main(){
    n=read();m=read();
    build(1,1,n);
    while(m--){
        int x=read(),y=read();
        change(1,1,n,x,y);
        ans+=max(f[1][0],f[1][1],f[1][2],f[1][3]);
    }
    cout<<ans<<endl;
}
```

---

## 作者：Zhengsiwei (赞：8)

$\;\;\;\;\;\;$这是[题目链接](https://www.luogu.com.cn/problem/P3097)。  
$\;\;\;\;\;\;$好，都读完题了。我们发现：
- 多次的单点修改  
- 区间查询（每次都是从头到尾）    

$ $所以这个应当是线段树或树状数组。（没学过这两种算法的请自行百度搜索。）  
$ $但树状数组胜任不了这次的任务。更新会很麻烦。只好用了线段树。  
$ $在这里，我将分别讨论几个重要部分的写法。


------------

### 结构体
$\;\;\;\;\;\;$这里说的是线段树的“节点”。描述左右端点的变量自然少不了。剩下的应是描述数据的变量。这里有一个小技巧，一些线段树的题都可以用到：先考虑左右端点。现在无非就是下面几种情况：
- 不取左端点也不取右端点；
- 不取左端点而取右端点；
- 取左端点而不取右端点；
- 左右端点都取。  
分别把这四种情况下的此节点范围内的答案存储，分别记为：
- C_00
- C_01
- C_10
- C_11  
可以给代码了。  
```cpp
struct Node{
    int l,r;
    long long C_00,C_01,C_10,C_11;
}Tree[160000];
```


------------

### pushup() 函数
$\;\;\;\;\;\;$你会问我 pushdown() 函数哪里去了，是吗？事实上，pushdown() 函数是为了 lazytag 诞生的。没有 lazytag，也就没有 pushdown() 函数。  
$\;\;\;\;\;\;$好了，回归正题。我们拿 C_00 举例子。它一定等于左子树的什么加右子树的什么。经过尝试发现，除了 C_00 不等于左子树的 C_01 加右子树的 C_10 以外，其他都合法。我们把其他情况取个最小值。其他变量(C_01、C_10、C_11)依此类推。代码：
```cpp
inline int max(int x,int y,int z,char id1,char id2){return (x>y? x:y)>z? (x>y? x:y):z;}
inline int max(int x,int y,int z,int w){return ((x>y? x:y)>z? (x>y? x:y):z)>w? ((x>y? x:y)>z?  (x>y? x:y):z):w;}
void pushup(int now){
    Tree[now].C_00=max(Tree[lson].C_00+Tree[rson].C_10,Tree[lson].C_01+Tree[rson].C_00,Tree[lson].C_00+Tree[rson].C_00,'0','0');
    Tree[now].C_01=max(Tree[lson].C_00+Tree[rson].C_01,Tree[lson].C_01+Tree[rson].C_01,Tree[lson].C_00+Tree[rson].C_11,'0','0');
    Tree[now].C_10=max(Tree[lson].C_10+Tree[rson].C_10,Tree[lson].C_10+Tree[rson].C_00,Tree[lson].C_11+Tree[rson].C_00,'0','0');
    Tree[now].C_11=max(Tree[lson].C_11+Tree[rson].C_01,Tree[lson].C_10+Tree[rson].C_01,Tree[lson].C_10+Tree[rson].C_11,'0','0');
}
```


------------

$\;\;\;\;\;\;$剩下的就是模板了。AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define lson (now<<1) 
#define rson ((now<<1)|1)
#define PAUSE printf("------------------------------------------------\nProcess exited with return value 0\n");system("PAUSE")
inline int max(int x,int y,int z,char id,char uid){return (x>y? x:y)>z? (x>y? x:y):z;}
inline int max(int x,int y,int z,int w){return ((x>y? x:y)>z? (x>y? x:y):z)>w? ((x>y? x:y)>z? (x>y? x:y):z):w;}
inline int read(){
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
struct Node{
    int l,r;
    long long C_00,C_01,C_10,C_11;
}Tree[160000];
void pushup(int now){
    Tree[now].C_00=max(Tree[lson].C_00+Tree[rson].C_10,Tree[lson].C_01+Tree[rson].C_00,Tree[lson].C_00+Tree[rson].C_00,'0','0');
    Tree[now].C_01=max(Tree[lson].C_00+Tree[rson].C_01,Tree[lson].C_01+Tree[rson].C_01,Tree[lson].C_00+Tree[rson].C_11,'0','0');
    Tree[now].C_10=max(Tree[lson].C_10+Tree[rson].C_10,Tree[lson].C_10+Tree[rson].C_00,Tree[lson].C_11+Tree[rson].C_00,'0','0');
    Tree[now].C_11=max(Tree[lson].C_11+Tree[rson].C_01,Tree[lson].C_10+Tree[rson].C_01,Tree[lson].C_10+Tree[rson].C_11,'0','0');
}
void init(int now,int l,int r){
    Tree[now].l=l;Tree[now].r=r;
    if(l==r){
        Tree[now].C_11=read();
        return;
    }
    init(lson,l,(l+r)>>1);
    init(rson,((l+r)>>1)+1,r);
    pushup(now);
}
void upgrade(int now,int target){
    if(Tree[now].l==Tree[now].r){
        Tree[now].C_11=read();
        return;
    }
    if(target>((Tree[now].l+Tree[now].r)>>1)) upgrade(rson,target);
    else upgrade(lson,target);
    pushup(now);
}
int main(){
    int n,d;
    long long ans=0;
    n=read();d=read();
    init(1,1,n);
    for(int i=1;i<=d;i++){
        upgrade(1,read());
        ans+=max(Tree[1].C_11,Tree[1].C_10,Tree[1].C_01,Tree[1].C_00);
    }
    cout<<ans;
//    PAUSE;
    return 0;
}
```
**谢谢大家！**

---

## 作者：破忆 (赞：5)

## 【题意】
给定n个点排成一排，每个点有一个点权，多次改变某个点的点权并将最大点独立集计入答案，输出最终的答案
## 【分析】
考虑用线段树维护每次操作之后的结果

问题在于维护和传递区间信息

合并子区间信息时，只有端点会限制传递方式

令$f[0/1][0/1]$表示某个子区间内，两端点分别取/不取的最大收益

子区间就几种可取的情况，分类讨论并维护即可
```cpp

t[k].f[0][0]=max(t[ls].f[0][0]+max(t[rs].f[0][0],t[rs].f[1][0]),t[ls].f[0][1]+t[rs].f[0][0]);
t[k].f[0][1]=max(t[ls].f[0][0]+max(t[rs].f[0][1],t[rs].f[1][1]),t[ls].f[0][1]+t[rs].f[0][1]);
t[k].f[1][0]=max(t[ls].f[1][0]+max(t[rs].f[0][0],t[rs].f[1][0]),t[ls].f[1][1]+t[rs].f[0][0]);
t[k].f[1][1]=max(t[ls].f[1][0]+max(t[rs].f[0][1],t[rs].f[1][1]),t[ls].f[1][1]+t[rs].f[0][1]);
```
初始或修改时，叶子节点的$f[1][1]$值就是点权

别忘了开$long long$
## 【算法】
线段树
## 【代码】
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int maxn=4e4+5,maxt=maxn<<2;
int n,m;
struct segment_tree{
	LL f[2][2];
}t[maxt];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
#define ls (k<<1)
#define rs (k<<1|1)
#define mid (l+r>>1)
void pushup(int k){
	t[k].f[0][0]=max(t[ls].f[0][0]+max(t[rs].f[0][0],t[rs].f[1][0]),t[ls].f[0][1]+t[rs].f[0][0]);
	t[k].f[0][1]=max(t[ls].f[0][0]+max(t[rs].f[0][1],t[rs].f[1][1]),t[ls].f[0][1]+t[rs].f[0][1]);
	t[k].f[1][0]=max(t[ls].f[1][0]+max(t[rs].f[0][0],t[rs].f[1][0]),t[ls].f[1][1]+t[rs].f[0][0]);
	t[k].f[1][1]=max(t[ls].f[1][0]+max(t[rs].f[0][1],t[rs].f[1][1]),t[ls].f[1][1]+t[rs].f[0][1]);
}
void build(int k,int l,int r){
	if(l==r){
		t[k].f[1][1]=read();
		return;
	}
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(k);
}
void update(int k,int l,int r,int x,int v){
	if(l==r){
		t[k].f[1][1]=v;
		return;
	}
	if(x<=mid) update(ls,l,mid,x,v);
	else update(rs,mid+1,r,x,v);
	pushup(k);
}
LL ans;
int main(){
	freopen("P3097.in","r",stdin);
	freopen("P3097.out","w",stdout);
	n=read(),m=read();
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int x=read(),v=read();
		update(1,1,n,x,v);
		ans+=max(max(t[1].f[0][0],t[1].f[0][1]),max(t[1].f[1][0],t[1].f[1][1]));
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：大菜鸡fks (赞：2)

我貌似读题读错了，以为修改的方案是自己定的。。。

这题发现数列的答案可以分治。然后考虑线段树合并答案。很显然的只需要考虑端点选或不选的情况。

看起来很一眼的题目我貌似没秒掉。还是太菜了。。。。

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=40005;
int n,m,q;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
struct node{
	int f[2][2],ans;
}a[maxn<<2];
inline void pushup(int k){
	a[k].f[0][0]=max(a[k<<1].f[0][1]+a[k<<1|1].f[0][0],a[k<<1].f[0][0]+a[k<<1|1].f[1][0]);
	a[k].f[0][1]=max(a[k<<1].f[0][1]+a[k<<1|1].f[0][1],a[k<<1].f[0][0]+a[k<<1|1].f[1][1]);
	a[k].f[1][0]=max(a[k<<1].f[1][0]+a[k<<1|1].f[1][0],a[k<<1].f[1][1]+a[k<<1|1].f[0][0]);
	a[k].f[1][1]=max(a[k<<1].f[1][1]+a[k<<1|1].f[0][1],a[k<<1].f[1][0]+a[k<<1|1].f[1][1]);
	a[k].ans=max(a[k].f[0][0],a[k].f[1][1]);
	a[k].ans=max(a[k].ans,max(a[k].f[0][1],a[k].f[1][0]));
}
void build(int k,int l,int r){
	if (l==r){
		a[k].f[1][1]=a[k].ans=read();
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid); build(k<<1|1,mid+1,r);
	pushup(k);
}
void update(int k,int l,int r,int x,int v){
	if (l==r){
		a[k].f[1][1]=a[k].ans=v;
		return;
	}
	int mid=(l+r)>>1;
	if (mid>=x) update(k<<1,l,mid,x,v);
		else update(k<<1|1,mid+1,r,x,v);
	pushup(k);	
}
int sum;
signed main(){
	n=read(); q=read();
	build(1,1,n);
	for (int i=1;i<=q;i++){
		int x=read(),y=read();
		update(1,1,n,x,y);
		sum+=a[1].ans;
	}
	writeln(sum);
	return 0;
}
```

---

## 作者：zx2003 (赞：2)

```cpp
uses math;
type
 tree=record
  l,r:int64;
  su:array[0..1,0..1] of int64;
 end;
var
 n,m,od,ev,x,y,ans:int64;
 a:array[0..40000] of int64;
 t:array[1..130000] of tree;
 i:longint;
procedure merge(i:longint);
begin
 t[i].su[1,1]:=max(t[i shl 1].su[1,0]+t[i shl 1 or 1].su[1,1],
  t[i shl 1].su[1,1]+t[i shl 1 or 1].su[0,1]);
 t[i].su[1,0]:=max(t[i shl 1].su[1,0]+t[i shl 1 or 1].su[1,0]
  ,t[i shl 1].su[1,1]+t[i shl 1 or 1].su[0,0]);
 t[i].su[0,1]:=max(t[i shl 1].su[0,1]+t[i shl 1 or 1].su[1,1],
  t[i shl 1].su[0,0]+t[i shl 1 or 1].su[1,1]);
 t[i].su[0,0]:=max(t[i shl 1].su[0,0]+t[i shl 1 or 1].su[1,0],
```
t[i shl 1].su[0,1]+t[i shl 1 or 1].su[0,0])
```cpp
end;
procedure build(i,l,r:longint);
var
 m:longint;
begin
 t[i].l:=l;
 t[i].r:=r;
 if l=r then
 begin
  t[i].su[1,1]:=a[l];
```
exit
```cpp
 end;
 m:=(l+r) shr 1;
 build(i shl 1,l,m);
 build(i shl 1 or 1,m+1,r);
 merge(i)
end;
procedure change(i:longint);
var
 m:longint;
begin
 if (t[i].l=x)and(t[i].r=x) then
 begin
  t[i].su[1,1]:=y;
```
exit

```cpp
 end;
 m:=(t[i].l+t[i].r) shr 1;
 if m>=x then change(i shl 1)
  else change(i shl 1 or 1);
 merge(i)
end;
begin
 readln(n,m);
 for i:=1 to n do readln(a[i]);
 build(1,1,n);
 for i:=1 to m do
 begin
  readln(x,y);
  change(1);
  inc(ans,t[1].su[1,1])
 end;
 writeln(ans)
end.
```
开一个线段树，每个点记录四个信息：
区间左端点不选，右端点也不选的最大值

区间左端点选择，右端点不选的最大值

区间左端点不选，右端点选择的最大值

区间左端点选择，右端点也选择的最大值

然后合并时讨论一下就行了


---

## 作者：NelsonBoss (赞：1)



#### 欢迎访问 [My Space](https://www.luogu.org/space/show?uid=143742)，以及 [My Blog](https://www.luogu.org/blog/bosswnx/#)，更好的阅读体验请 [Check Me！](https://www.luogu.org/blog/bosswnx/solution-uva710)
------------

## 【标签】

线段树，单点修改，区间DP。

------
## 【分析】

通过**线段树**来进行**区间DP**，维护最大点集。

#### 基本想法：

化简题目：将 $n$ 个点排成一排，每一个点都有一个点权，从中选出相互不能临近的最大点集。

#### 改进：

由于需要维护区间信息，考虑通过线段树来进行区间DP。

每个线段树的节点内都有一个$F$数组：

1. $F[1][0]$ 表示区间左端点取，右端点不取的最大点集的和。
2. $F[0][1]$ 表示区间左端点不取，右端点取的最大点集的和。
3. $F[1][1]$ 表示区间左端点取，右端点也取的最大点集的和。
4. $F[0][0]$ 表示区间左端点、右端点都不取的最大点集的和。

因为两个相邻的点不能同时取，所以更新最大值的时候要进行分类讨论，**左子节点**的右端点 与 **右子节点**的左端点不能同时取。

举例，当前树节点的 $F[1][0]$ 可以由：

1. **左**子节点的 $F[1][0]$ $+$ **右**子节点的 $F[1][0]$；  
2. **左**子节点的 $F[1][0]$ $+$ **右**子节点的 $F[0][0]$；
3. **左**子节点的 $F[1][1]$ $+$ **右**子节点的 $F[0][0]$；

三种情况取最大值 $(Max)$ 更新来，其他情况同理，在更新时讨论即可。

注：在建树时叶子节点的值为$F[1][1] = S[l]$。

每组数据读入后进行线段树单点修改，$Ans$ 增加线段树根节点 $(T[1])$ 的所有情况中的最大值即可。

------

## 【代码】

### [C++]
```cpp
#include <bits/stdc++.h>
#define wld(a) while(a(isdigit(c=getchar())))
#define xpp x=(x<<1)+(x<<3)+(c^48)
#define LL long long
#define R k<<1|1
#define L k<<1
using namespace std;
const int MAXN = 40000+5;
struct T{LL F[2][2];int l, r;}T[MAXN*4];

int S[MAXN], n, d, p, v;
long long Ans;

inline int Rd(){char c;wld(!);int x=c^48;wld()xpp;return x;}
inline void Update(int &k){  //更新数据
	T[k].F[1][0] = max(max(T[L].F[1][0]+T[R].F[1][0], T[L].F[1][1]+T[R].F[0][0]), T[L].F[1][0]+T[R].F[0][0]);
	T[k].F[0][1] = max(max(T[L].F[0][1]+T[R].F[0][1], T[L].F[0][0]+T[R].F[1][1]), T[L].F[0][0]+T[R].F[0][1]);
	T[k].F[0][0] = max(max(T[L].F[0][1]+T[R].F[0][0], T[L].F[0][0]+T[R].F[1][0]), T[L].F[0][0]+T[R].F[0][0]);
	T[k].F[1][1] = max(max(T[L].F[1][0]+T[R].F[1][1], T[L].F[1][1]+T[R].F[0][1]), T[L].F[1][0]+T[R].F[0][1]);
}
void Build(int k, int l, int r){  //建树
	T[k].l = l, T[k].r = r;
	if(l==r){T[k].F[1][1] = S[l];return;}
	int mid = (l+r)>>1;
	Build(L, l, mid);
	Build(R, mid+1, r);
	Update(k);
}
void Revise(int k){  //单点修改
	if(T[k].l==T[k].r){T[k].F[1][1]=v;return;}
	int Tmid = (T[k].l+T[k].r)>>1;
	if(p<=Tmid) Revise(L);
	else Revise(R);
	Update(k);
}
int main(){
	n=Rd(), d=Rd();
	for(int i=1; i<=n; i++) S[i]=Rd();
	Build(1, 1, n);
	while(d--){
		p=Rd(), v=Rd();
		Revise(1);
		Ans += max(max(T[1].F[1][1], T[1].F[0][0]), max(T[1].F[1][0], T[1].F[0][1]));
	}
	printf("%lld", Ans);
	return 0;
}
```
------
## 【补充】

分类讨论时要细心一点，要记得是先修改再统计。

---

# Over

---

## 作者：傅思维666 (赞：0)


## 题解：

思路：单点修改+求最大点权独立集。

考虑用区间树维护。但是一时半会没明白要维护什么。~~（维护了个寂寞）~~

后来发现，但凡不是裸的线段树，都可以先考虑分类讨论+向上pushup区间合并。

我们完全可以维护区间端点有没有被选的情况，然后在pushup函数中分类转移即可。

C语言代码：

```cpp
#include<stdio.h>
#define max(a,b) (a)>(b)?(a):(b)
#define lson pos<<1
#define rson pos<<1|1
#define int long long
int n,m,q,ans;
char *p1,*p2,buf[100000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read()
{
    int x=0,f=1;
    char ch=nc();
    while(ch<48||ch>57)
    {
        if(ch=='-')
            f=-1;
        ch=nc();
    }
    while(ch>=48&&ch<=57)
        x=x*10+ch-48,ch=nc();
   	return x*f;
}
struct node
{
	int f[2][2],ans;
}tree[40005<<2];
void pushup(int pos)
{
	tree[pos].f[0][0]=max(tree[rson].f[0][1]+tree[lson].f[0][0],tree[rson].f[0][0]+tree[lson].f[1][0]);
	tree[pos].f[0][1]=max(tree[rson].f[0][1]+tree[lson].f[0][1],tree[rson].f[0][0]+tree[lson].f[1][1]);
	tree[pos].f[1][0]=max(tree[rson].f[1][0]+tree[lson].f[1][0],tree[rson].f[1][1]+tree[lson].f[0][0]);
	tree[pos].f[1][1]=max(tree[rson].f[1][1]+tree[lson].f[0][1],tree[rson].f[1][0]+tree[lson].f[1][1]);
	tree[pos].ans=max(tree[pos].f[0][0],tree[pos].f[1][1]);
	tree[pos].ans=max(tree[pos].ans,max(tree[pos].f[0][1],tree[pos].f[1][0]));
}
void build(int pos,int l,int r)
{
	if (l==r)
    {
		tree[pos].f[1][1]=tree[pos].ans=read();
		return;
	}
	int mid=(l+r)>>1;
	build(rson,l,mid); 
    build(lson,mid+1,r);
	pushup(pos);
}
void update(int pos,int l,int r,int x,int v)
{
	if (l==r)
    {
		tree[pos].f[1][1]=tree[pos].ans=v;
		return;
	}
	int mid=(l+r)>>1;
	if (mid>=x) 
        update(rson,l,mid,x,v);
	else 
        update(lson,mid+1,r,x,v);
	pushup(pos);	
}
signed main()
{
	n=read();q=read();
	build(1,1,n);
	for(int i=1;i<=q;i++)
    {
		int x=read(),y=read();
		update(1,1,n,x,y);
		ans+=tree[1].ans;
	}
	printf("%lld",ans);
	return 0;
}
```


---

