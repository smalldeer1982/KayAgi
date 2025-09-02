# Color the Axis

## 题目描述

在一条数轴上有 $n$ 个点，分别是 $1,2,\ldots,n$。一开始所有的点都被染成黑色。接着我们进行 $m$ 次操作，第 $i$ 次操作将 $[l_i,r_i]$ 这些点染成白色。请输出每个操作执行后剩余黑色点的个数。

## 说明/提示

- 对于 $30\%$ 的数据，有 $1\le n\le2000$，$1\le m\le2000$；
- 对于 $100\%$ 的数据，有 $1\le l_i\le r_i\le n\le 2\times 10^5$，$1\le m\le 2\times10^5$。

## 样例 #1

### 输入

```
10 3
3 3
5 7
2 8```

### 输出

```
9
6
3```

# 题解

## 作者：凌幽 (赞：47)

看了看各位大佬的题解,都是线段树,那我就来一份并查集的题解吧

给一段区间染色,可以看做是合并一段区间,并且使其在统计过程中不会重复统计

固定染色区间的左端点,将整个区间合并(从右向左扫一边染色区间),这样当我们统计区间时用x=find(x)时就相当于跳过该区间,达到了不重复的目的

部分代码

```cpp
int n,m;
int cnt;
int fa[200005];
inline int found(int x){
    return x==fa[x]?x:fa[x]=found(fa[x]);
}
inline int dy(){
    in(n),in(m);
    for(R int i=0;i<=n+1;++i)fa[i]=i;
    while(m--){
        R int a,b;in(a),in(b);
        b=found(b);
        while(a<=b){
            if(a!=b && found(a)==b)break;
            fa[b]=found(fa[b-1]);
            cnt++;
            b=found(b);
        }
        write(n-cnt),putchar('\n');        
    }
    exit(0);
}
```

---

## 作者：木木！ (赞：24)

我是来给并查集大佬补时间复杂度证明的QwQ。

设势能函数$\Phi(s)=\text{s中并查集个数}$，易知在一开始$\Phi(s)=n$。

而每次操作，如果一下子跳不到r的话，会执行合并，将并查集数量-1，势能函数就减少了1。则，该次多余跳+合并不消耗时间。

因此，每次修改的时间复杂度是$\Theta(1)$。

由于一开始$\Phi(s)=n$，所以必须得在程序开始时额外花费$\Theta(n)$的时间提高势能函数。

所以，最终时间复杂度为$\Theta(n+m)$。

附AC代码：

```cpp
#include <cstdio>
using namespace std;

int st[200005];

int getfa(int x)
{
	return x==st[x]?x:st[x]=getfa(st[x]);
}

void unio(int a,int b)
{
	st[getfa(b)] = getfa(a);
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);

	int blkn = n;	
	for(int i=1; i<=n+1; ++i)
	{
		st[i] = i;
	}
	for(int i=1; i<=m; ++i)
	{
		int li,ri;
		scanf("%d%d",&li,&ri);
		
		int t = getfa(li);
		while(t<=ri)
		{
			unio(t+1,t);
			t = getfa(t);
			--blkn;
		}
		
		printf("%d\n",blkn);
	}
}
```

（线段树的题怎么能用线段树做呢）

---

## 作者：zh_dou (赞：8)

## 分析
我们考虑将黑色点看成1，白色点看成0，那么这道题可以转化为：给定一个全1串，要求我们实现：

1. 区间推平

2. 区间查询

...珂朵莉树的模板题，亲测跑得飞快

这道题直接暴力查询整个 $[1,n]$ 即可，
但[某些题](https://www.luogu.org/problem/CF915E)会卡这种做法。

考虑每一次区间推平，产生的影响只有这次推平的 $[l,r]$ 

故只需要在推平前扫描 $[l,r]$ ，减去对应区间的贡献即可

## 代码
$\mathcal{Code:}$
```cpp
#include<set>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 100010
//#define int long long
#define debug cout<<__LINE__<<" "<<__FUNCTION__<<"\n"
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x;
}
struct Node{
	signed l,r;
	mutable int val;
	Node(int L,int R=-1,int V=0):l(L),r(R),val(V){}
	friend bool operator <(const Node &a,const Node &b){
		return a.l<b.l;
	}
};
int n,m,sum;
set<Node> s;
#define IT set<Node>::iterator
inline IT Split(signed pos){
	IT it=s.lower_bound(Node(pos));
	if(it!=s.end()&&it->l==pos) return it;
	it--;
	int l=it->l,r=it->r,val=it->val;
	s.erase(it);
	s.insert(Node(l,pos-1,val));
	return s.insert(Node(pos,r,val)).first;
}
inline void Assign(signed l,signed r,int val){
	IT it2=Split(r+1),it1=Split(l);
	for(IT it=it1;it!=it2;++it)//如果是黑色点的区间就减去黑点的贡献
		sum-=it->val*(it->r-it->l+1);
	s.erase(it1,it2);
	s.insert(Node(l,r,val));
}
signed main(){
// 	freopen(".in","r",stdin);
// 	freopen(".out","w",stdout);
	sum=n=read();m=read();//初始全部是黑色点
    s.insert(Node(1,n+1,1));
    for(int i=1,opt,l,r,l1,r1,res;i<=m;i++){
        l=read();r=read();
        Assign(l,r,0);//区间推平
        printf("%d\n",sum);
    }
//	fclose(stdin);
//	fclose(stdout);
    return 0;
}

```

---

## 作者：冰糖鸽子 (赞：8)

啧，不知道为什么题解里没有这种 $300\text{B}$ 的做法呢

----

线段树？你真的愿意用线段树来维护这个看上去就很 naive 的操作？

本人的做法和并查集挺类似的，但省去了一些。

考虑维护每个点是不是白色，若是白色，记录这个点往后能到达的较远的连续一段白色的终点。（注意，是较远的，因为操作的时候会有很多点无法方便的维护）

操作时，从 $l$ 到 $r$ 遍历，若 $f_i$ 不为 $0$ （是白色），则 $i$ 变为 $f_i$ ，**同时，$f_i$ 与 $r$ 取 $\max$**。反之则赋 $f_i$ 为 $r$ ，并让 $n$ 减 $1$（因为后面不会用到 $n$ ，所以 $n$ 可以顺便当答案）。

最后输出 $n$ 即可。

最后吐槽一下，如果不加上面粗体标注的优化，很轻易就可以卡到 $n^2$ ，但数据过水导致过了，还跑得贼快。相比之下优化之后基本上时间没有变/kk

正常的 $368\text{B}$ 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,f[200005],k,l,r;
int main()
{
	cin>>n>>m;
	for(int j=1;j<=m;j++)
	{
		cin>>l>>r;
		for(int i=l;i<=r;i++)
    	{
    		if(f[i])
    		{
    			k=f[i];
    			f[i]=max(f[i],r);
    			i=k;
    		}
    		else
    		{
    			f[i]=r;
    			n--;
    		}
    	}
		cout<<n<<endl;
	}
	return 0;
}
```

只压了一点点的 $211\text{B}$ 代码：

```cpp
#include<iostream>
using namespace std;int n,m,f[200005],k,l,r;int main(){cin>>n>>m;for(int j=1;j<=m;j++){cin>>l>>r;for(int i=l;i<=r;i++){if(f[i]){k=f[i];f[i]=max(f[i],r);i=k;}else{f[i]=r;n--;}}cout<<n<<endl;}}
```

---

## 作者：流逝丶 (赞：6)

提供一个比较简单的线段树写法

不用build，ask还有down

一整棵树维护白点的数量，每次change找到精准的区间然后一整个区间都是白点

如果再change的时候发现要访问的区间已经全部覆盖，就可以直接返回，无需再改

输出答案的话，$tr[1]$是区间白点总数，所以答案就是$n-tr[1]$


```cpp
#include<iostream>
#include<cstdio>
#define lson k<<1,l,mid
#define rson k<<1|1,mid+1,r
#define ls k<<1
#define rs k<<1|1
#define mid ((l+r)>>1)
using namespace std;
const int maxn=200005;
int n,m;
int tr[maxn<<2];
inline void update(int k){
	tr[k]=tr[ls]+tr[rs];
}
void change(int k,int l,int r,int x,int y){
	if(tr[k]==r-l+1)return ;
	if(l==x&&y==r){
		tr[k]=r-l+1;
		return ;
	}
	if(y<=mid)change(lson,x,y);
	else if(x>mid)change(rson,x,y);
	else change(lson,x,mid),change(rson,mid+1,y);
	update(k);
}
int main(){
	scanf("%d%d",&n,&m);
	int x,y;
	while(m--){
		scanf("%d%d",&x,&y);
		change(1,1,n,x,y);
		printf("%d\n",n-tr[1]);
	}
	return 0;
}
```


---

## 作者：Aleph1022 (赞：6)

各位大佬都写了线段树啊。  
还有一个神犇写了并查集！

鄙人也是第一反应线段树，但是最近 FHQ Treap 写多了，于是忍不住……  
其实平衡树打标记也和其他数据结构差不多的说  
而且空间占用比线段树要小。

代码：
```cpp
#include <cstdio>
#include <cstdlib>
#define ls(p) tree[p].lson
#define rs(p) tree[p].rson
using namespace std;
const int N = 2e5;
int n,m;
struct node
{
	int val,rnd,sz;
	int set,sum;
	int lson,rson;
} tree[N + 10];
inline int new_node(int v)
{
	static int tot = 0;
	tree[++tot].val = v;
	tree[tot].sum = v;
	tree[tot].rnd = rand();
	tree[tot].set = -1;
	tree[tot].sz = 1;
	return tot;
}
inline void up(int p)
{
	tree[p].sz = tree[ls(p)].sz + 1 + tree[rs(p)].sz;
	tree[p].sum = tree[ls(p)].sum + tree[p].val + tree[rs(p)].sum;
}
inline void down(int p)
{
	if(tree[p].set != -1)
	{
		if(ls(p))
			tree[ls(p)].val = tree[p].set,tree[ls(p)].sum = tree[p].set * tree[ls(p)].sz,tree[ls(p)].set = tree[p].set;
		if(rs(p))
			tree[rs(p)].val = tree[p].set,tree[rs(p)].sum = tree[p].set * tree[rs(p)].sz,tree[rs(p)].set = tree[p].set;
		tree[p].set = -1;
	}
}
void split(int p,int k,int &x,int &y)
{
	if(!p)
	{
		x = y = 0;
		return ;
	}
	down(p);
	if(tree[ls(p)].sz < k)
		x = p,split(rs(p),k - tree[ls(p)].sz - 1,rs(p),y);
	else
		y = p,split(ls(p),k,x,ls(p));
}
int merge(int x,int y)
{
	if(!x || !y)
		return x | y;
	down(x),down(y);
	if(tree[x].rnd < tree[y].rnd)
	{
		rs(x) = merge(rs(x),y);
		up(x);
		return x;
	}
	else
	{
		ls(y) = merge(x,ls(y));
		up(y);
		return y;
	}
}
int p,x,y,z;
int main()
{
	srand(19260817);
	scanf("%d%d",&n,&m);
	for(register int i = 1;i <= n;++i)
		p = merge(p,new_node(1));
	int l,r;
	while(m--)
	{
		scanf("%d%d",&l,&r);
		split(p,r,x,z);
		split(x,l - 1,x,y);
		tree[y].val = 0,tree[y].set = 0,tree[y].sum = 0;
		p = merge(merge(x,y),z);
		printf("%d\n",tree[p].sum);
	}
}
```

---

## 作者：NIMNIM (赞：5)

### 很标准的线段树模板

但是我打的是分块

分块很暴力啊，像某位dalao说的，
~~你看n方的暴力什么不能维护~~

言归正传，看看我的分块代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define re register int
#define il inline
bool col[200005];
int sum[500]={};
int n,m,len,num,ans;

int main ( )
{
//	freopen("axis.in","r",stdin);
//	freopen("axis.out","w",stdout);
	int l,r;
	scanf("%d%d",&n,&m);
	ans=n;
	num=len=sqrt(n);
	if(n%num) ++num;
	for(re i=1;i<=m;++i)
	{
		scanf("%d%d",&l,&r);
		int pl=(l-1)/len+1,pr=(r-1)/len+1;
		if(pl==pr)
		{
			if(sum[pl]!=len)
				for(re j=l;j<=r;++j)
					if(!col[j])
					{
						col[j]=true;
						++sum[pl];
						--ans;
					}
		}
		else
		{
			for(re j=pl+1;j<=pr-1;++j)
			{
				ans-=len-sum[j];
				sum[j]=len;
			}
			if(sum[pl]!=len)
				for(re j=l;j<=pl*len;++j)
					if(!col[j])
					{
						col[j]=true;
						++sum[pl];
						--ans;
					}
			if(sum[pr]!=len)
				for(re j=(pr-1)*len+1;j<=r;++j)
					if(!col[j])
					{
						col[j]=true;
						++sum[pr];
						--ans;
					}
		}
		printf("%d\n",ans);
	}
}
```

1.sum数组用于维护一段区间已经变成白色的点

2.col就是每个点是否已经染色

3.pl，pr 是当前左右端点所属的区间

再推荐一道题：


[P4145 上帝造题的七分钟2 / 花神游历各国](https://www.luogu.org/problem/P4145)

---

## 作者：寒冰大大 (赞：4)

看了一下题解，显然在做无用功啊，而且麻烦了许多，但是这道题真心不难，显然是一个区间修改的题目，然后查询的题目

我的线段树只需要记录一个量：区间和

看了一下其他题解的pushdown函数，发现真心写的很麻烦

这里有一个很巧妙的解法：

### 如果这个区域被染成了白棋，那么直接把这个区间总和清零就好了

### 然后向下传值，只需要把他的儿子节点sum清零就好了

## 那就直接上代码吧

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<algorithm> 

#define lson i*2,l,mid
#define rson i*2+1,mid+1,r  //宏定义 
#define I_copy_the_answer return 0;
using namespace std;

int n,m;
struct tree{
	int l,r,sum;
}t[1000860];  //线段树最大可能达到四倍空间，因此数组开四倍以上 

void build_tree(int i,int l,int r)
{
	t[i].l=l;  //这东西没什么用，但是查错的时候挺方便的 
	t[i].r=r;
	if(l==r)
	{
		t[i].sum=1;  //每一个黑色棋子 
		return ;
	}
	int mid=(l+r)/2;
	build_tree(lson);
	build_tree(rson);
	t[i].sum=t[i*2].sum+t[i*2+1].sum; //这个不多睡了吧 
	return ;
}

int pushdown(int i)   //简短的pushdown 
{
	if(!t[i].sum)  //！即取反 0取反即1 
	t[i*2].sum=0,t[i*2+1].sum=0;  
}

void change_tree(int i,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)
	{
		t[i].sum=0;
		return ;
	}
	pushdown(i);  
	int mid=(l+r)/2;
	if(a<=mid) change_tree(lson,a,b);
	if(b>mid) change_tree(rson,a,b);
	t[i].sum=t[i*2].sum+t[i*2+1].sum;  
	return ;
}

int ask_color_tree(int i,int l,int r,int a,int b)  //这个函数其实可以不写，输出t[1].sum即可，但是为了演示一下写了出来
{
	if(l>=a&&r<=b)
	{
		return t[i].sum;
	}
	pushdown(i);  
	int mid=(l+r)/2;
	int ans=0;
	if(a<=mid) ans+=ask_color_tree(lson,a,b);
	if(b>mid) ans+=ask_color_tree(rson,a,b);
	return ans;
}

int main()
{
	int i,j;
	scanf("%d %d",&n,&m);
	build_tree(1,1,n);
	for(i=1;i<=m;i++)
	{
		int t1,t2;
		scanf("%d %d",&t1,&t2);
		change_tree(1,1,n,t1,t2);
		printf("%d\n",ask_color_tree(1,1,n,1,n));  //可以不要，直接输出t[1].sum
	}
	I_copy_the_answer //你就别抄这个代码了吧 
}
```


---

## 作者：sjie (赞：4)

-  直接裸线段树，把黑棋看做1，把白旗看做0，操作前先把1~n个数都赋值1

-  操作时把区间内的所有数用线段树乘0就好

-  每次操作完查询一次1到n的所有数的和就好了

-  不过还是先建议大家先去做线段树2的模板

-  代码如下

```cpp
#include<iostream>
#include<cstring>
#include<queue>
#include <cstdio>
#include<cmath>
#include <algorithm>
#define ll long long
using namespace std;
ll n,m,p;
struct P{
      ll l,r,h,c,f;
}t[800009];
ll a[200009];
void sgin(ll);
void bulid(ll,ll,ll);
ll sum(ll,ll,ll);
void inc(ll,ll,ll,ll);
void cf(ll,ll,ll,ll);
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    a[i]=1;
    bulid(1,n,1);
    int o,x,y,k;
    for(int i=1;i<=m;i++){
            cin>>x>>y;
            cf(x,y,1,0);
            cout<<sum(1,n,1)<<endl;
                 }     
    return 0;
}
void bulid(ll x,ll y,ll l){
     t[l].l=x;
     t[l].r=y;
     t[l].c=1;
     t[l].f=0;
     if(x==y){
          t[l].h=a[x];
          return;
          }  
     int m=(x+y)/2;
     bulid(x,m,l*2);
     bulid(m+1,y,l*2+1);
     t[l].h=t[l*2].h+t[l*2+1].h;
}
void sgin(ll x){
     if(t[x].c==1&&t[x].f==0)return;
     if(t[x].l==t[x].r){t[x].c=1;t[x].f=0;return;}
     t[x*2].h=(t[x*2].h*t[x].c+t[x].f*(t[x*2].r-t[x*2].l+1));
     t[x*2+1].h=(t[x*2+1].h*t[x].c+t[x].f*(t[x*2+1].r-t[x*2+1].l+1));
     t[x*2].c=t[x*2].c*t[x].c;
     t[x*2+1].c=t[x*2+1].c*t[x].c;
     t[x*2].f=(t[x*2].f*t[x].c+t[x].f);
     t[x*2+1].f=(t[x*2+1].f*t[x].c+t[x].f);
     t[x].c=1;t[x].f=0;
}
/*void inc(ll x,ll y,ll l,ll h){
     sgin(l);
     if(x<=t[l].l&&t[l].r<=y){
          t[l].h=(t[l].h+h*(t[l].r-t[l].l+1));
          t[l].f=h;
          return;
          }
     int m=(t[l].l+t[l].r)/2;
     if(x<=m)inc(x,y,l*2,h);
     if(y>m)inc(x,y,l*2+1,h);
     t[l].h=t[l*2].h+t[l*2+1].h;
```
}处理加法操作，跟本题无关\*/
void cf(ll x,ll y,ll l,ll h){//乘0； 变成白旗的过程;

```cpp
     sgin(l);
     if(x<=t[l].l&&t[l].r<=y){
                t[l].h=t[l].h*h;
                t[l].c=h;
                return;
                }
     int m=(t[l].l+t[l].r)/2;
     if(x<=m)cf(x,y,l*2,h);
     if(y>m)cf(x,y,l*2+1,h);
     t[l].h=(t[l*2].h+t[l*2+1].h);
}                                              
ll sum(ll x,ll y,ll l){//统计1 到 n的和（因为白旗为0，黑棋为1，所以和就是黑棋的个数） 
    sgin(l);
    if(x<=t[l].l&&t[l].r<=y){
        return t[l].h;
        }
    int m=(t[l].l+t[l].r)/2;
    ll ans=0;
    if(x<=m)ans+=sum(x,y,l*2);
    if(y>m)ans+=sum(x,y,l*2+1);
    return ans;
}
```

---

## 作者：litjohn (赞：3)

unsigned long long 类型做一次操作的时间消耗与 bool 类型是同样的，所以可以通过压位用一个 unsigned long long 代替64个 bool 减小常数。能使时间减小到原来的 1/64，实测能通过本题。

在下面的代码实现中，我采用了 `bitset<64>` 代替unsignedlonglong 类型，因为它方便使用且内部的实现也进行了64位压位。但是 `bitset` 不支持直接修改指定区间，所以还是得分成若干小块。 

代码中的 `foo` 函数是用来计算给定下标 `pos` 所处的  `bitset` 和在该 `bitset` 中的下标。
```cpp
#include <bits/stdc++.h>

using namespace std;
int n, m;
array<bitset<64>, 10001> a;

inline pair<int, int> foo(int pos) {
    return {pos >> 6, pos & 0x3f};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i <= foo(n).first; ++i) {
        a[i].set();
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        l--, r--;//这里要转换成0-indexed与之前适配。
        auto x = foo(l), y = foo(r);
        if (x.first != y.first) {
            for (int j = x.second; j < 64; ++j) {
                a[x.first].reset(j);
            }
            for (int j = x.first + 1; j < y.first; ++j) {
                a[j].reset();
            }
            for (int j = y.second; j >= 0; --j) {
                a[y.first].reset(j);
            }
        } else {//如果在一块bitset中
            for (int j = x.second; j <= y.second; ++j) {
                a[x.first].reset(j);
            }
        }
        int ans = 0;
        for (int j = 0; j < foo(n).first; ++j) {
            ans += a[j].count();
        }
        for (int j = 0; j < foo(n).second; ++j) {
            if (a[foo(n).first][j]) {
                ans++;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：清远学会 (赞：3)

# 遇事不决先分块
### 我用分块水这道题 
这道题很裸，但用线段树来做就有点大材小用了，分块可以说是短小精悍，并且可以维护很多数据，真是居家陆行必备的良器啊
### 不懂分块 [点我领取例题](https://loj.ac/problems/search?keyword=%E5%88%86%E5%9D%97)
希望你在分块路上越走越远~
代码如下：
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#define N 300500
using namespace std;

inline int read() {
	int x = 0,f = 1; char s = getchar();
	while(s < '0' || s > '9') {if(s == '-') f = -1;s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
	return x * f;
}

int n,m;
int a[N];
int L[N],R[N],tag[N];
int sum[N],lz[N];

inline void Change(int l,int r) {
	if(tag[l] == tag[r]) {
		for(int i = l;i <= r;i ++)
			if(a[i]) a[i] = 0,sum[tag[i]] --;
		return ;
	}
	for(int i = l;i <= R[tag[l]];i ++) 
		if(a[i]) a[i] = 0,sum[tag[l]] --;
	for(int i = tag[l] + 1;i < tag[r];i ++) lz[i] = 1;
	for(int i = L[tag[r]];i <= r;i ++) 
		if(a[i]) a[i] = 0,sum[tag[r]] --;
}

inline int Qurry() {
	int res = 0;
	for(int i = 1;i <= tag[n];i ++)
		if(!lz[i] && sum[i] > 0) 
			res += sum[i];
	return res; 
}

int main() {
	n = read(),m = read();
	int len = sqrt(n);
	for(int i = 1;i <= n;i ++) 
		tag[i] = (i - 1) / len + 1,a[i] = 1;
	for(int i = 1;i <= tag[n];i ++) 
		L[i] = R[i - 1] + 1,R[i] = min(n,L[i] + len - 1); 
	for(int i = 1;i <= tag[n];i ++) 
		sum[i] = R[i] - L[i] + 1;
	for(int i = 1;i <= m;i ++) {
		int l = read(),r = read();
		Change(l,r);
		printf("%d\n",Qurry());
	}
	return 0;
}
```
## 谢谢

---

## 作者：peterwuyihong (赞：2)

好久没发题解了今天来一发
### 分块大法好！
把序列分成$k$块，则一共能分成$ \frac{n}{k} $块，对于一个$ change(l,r) $操作，只需要把 $ l-r $ 包含的块标记$ tag $，则有$ tag $的块计算时只需要算这个块的长度即可；算完块就朴素算边角。
#### 那么这样复杂度是多少？
每一块的操作加上块总数的操作，即$ O(m(k+\frac{n}{k})) $,用均值不等式得到
### $ O(m(k+\frac{n}{k})) ≥ O(2m\sqrt{n})=O(m\sqrt{n}) $
### 在$ k=\sqrt{n} $取到
完美！那么就是代码时光！
```cpp
#include<bits/stdc++.h>
#define maxn 200010
#define rg register
using namespace std;
template<class T>int read(T &__x){__x=0;short __f=1;char __ch=getchar();while(__ch<'0'||__ch>'9'){if(__ch=='-')__f=-1;__ch=getchar();}while(__ch>='0'&&__ch<='9'){__x=(__x<<1)+(__x<<3)+(__ch^48);__ch=getchar();}__x*=__f;return __x;}
int n,m;
int t;
int sum[maxn];
int L[maxn],R[maxn],POS[maxn];
bool tag[maxn];
bool a[maxn];
inline void change(int l,int r){
	int p=POS[l],q=POS[r];
	if(p==q){
		for(rg int i=l;i<=r;i++){
			if(a[i]!=1){
				a[i]=1;
				sum[p]++;
			}
		}
		return;
	}
	for(rg int i=p+1;i<=q-1;i++)tag[i]=1;
	for(rg int i=l;i<=R[p];i++){
		if(a[i]!=1){
			a[i]=1;
			sum[p]++;
		}
	}
	for(rg int i=L[q];i<=r;i++){
		if(a[i]!=1){
			a[i]=1;
			sum[q]++;
		}
	}
}
inline int ask(int l,int r){
	int p=POS[l],q=POS[r];
	int ans=0;
	if(p==q){
		if(tag[p])ans+=r-l+1;
		else for(rg int i=l;i<=r;i++)ans+=a[i];
		return ans;
	}
	for(rg int i=p+1;i<=q-1;i++)
	if(tag[i])ans+=R[i]-L[i]+1;
	else ans+=sum[i];
	if(tag[p])ans+=R[p]-l+1;
	else for(rg int i=l;i<=R[p];i++)ans+=a[i];
	if(tag[q])ans+=r-L[q]+1;
	else for(rg int i=L[q];i<=r;i++)ans+=a[i];
	return ans;
}
int x,y;
int main(){
//	freopen("testdata.in","r",stdin);
	read(n),read(m);
	t=sqrt(n);
	for(rg int i=1;i<=n/t;i++){
		L[i]=(i-1)*sqrt(n)+1;
		R[i]=i*sqrt(n);
	}
	if(R[t]<n)t++,L[t]=R[t-1]+1,R[t]=n;
	for(rg int i=1;i<=t;i++)
		for(rg int j=L[i];j<=R[i];j++)
		POS[j]=i;
	while(m--){
		read(x),read(y);
		change(x,y);
	//	cout<<x<<' '<<y<<endl;
	//	for(int i=1;i<=n;i++)cout<<a[i]<<' ';puts("");
	//	for(int i=1;i<=t;i++)cout<<sum[i]<<' ';puts("");
	//	for(int i=1;i<=t;i++)cout<<tag[i]<<' ';puts("");
		printf("%d\n",n-ask(1,n));
	}
}

```
#### 得得得得得得得得得得得得
其实分块速度不快，我用了$ Register+Inline+Fastread $才过，但是用途很广泛，几乎所有$ n^2 $的序列操作都能做，常数还很小。我写这篇主要是为了~~装B~~练习一下我的分块，拓展读者的芝士。
### 但我还有一个小小的问题希望管理大大和读者巨佬解答
一个我疑惑至今的问题

#### 为什么我这么分块会$ Wa $？
```cpp
t=sqrt(n);
for(int i=1;i<=t;i++){
	L[i]=R[i-1]+1;
	R[i]=L[i]+t-1;
}
```

#### 但是这样就$ A $了？？
```cpp
t=sqrt(n);
for(rg int i=1;i<=t;i++){
	L[i]=(i-1)*sqrt(n)+1;
	R[i]=i*sqrt(n);
}
```
我仔细一推式子感觉也没有问题，甚至写了对拍
![](https://cdn.luogu.com.cn/upload/image_hosting/2msqms4p.png)
#### $Excuse \  me $??

---

## 作者：江屿 (赞：2)

反正就是线段树了，不过看楼下两篇写的好麻烦。

思路和楼下一样，就是先把1到n都初始化为1，黑棋默认为1，白棋则是0。

每次把一个区间的黑棋都改成白棋，那么只要询问到的区间在目标区间内，就把这个区间的个数直接设为0。

直接输出线段树的根节点，也就是tree[1]就行啦。

当然因为是区间修改所以要用懒标记啦，lazylazylazy。

因为把题目中的200000看成了100000而开小了空间，激情RE40分......

代码：

```cpp
#include<cstdio>
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
int tree[840000],lazy[840000],num,n,m,a,b;
void pushup(int rt){
    tree[rt]=tree[rt<<1]+tree[rt<<1|1];
}
void pushdown(int rt){
    if(lazy[rt]==1){
        if(!lazy[rt<<1])
            tree[rt<<1]=0;
        lazy[rt<<1]=1;
        if(!lazy[rt<<1|1])
            tree[rt<<1|1]=0;
        lazy[rt<<1|1]=1;
        lazy[rt]=0;
    }
}
void build(int l,int r,int rt){
    if(l==r){
        tree[rt]=1;
        return;
    }
    int m=(l+r)>>1;
    build(lson);
    build(rson);
    pushup(rt);
}
void update(int l,int r,int rt,int L,int R){
    if(L<=l&&r<=R){
        if(!lazy[rt])
            tree[rt]=0;
        lazy[rt]=1;
        return;
    }
    pushdown(rt);
    int m=(l+r)>>1;
    if(L<=m)
        update(lson,L,R);
    if(m<R)
        update(rson,L,R);
    pushup(rt);
}
int main(){
    scanf("%d%d",&n,&m);
    build(1,n,1);
    for(int i=1;i<=m;++i){
        scanf("%d%d",&a,&b);
        update(1,n,1,a,b);
        printf("%d\n",tree[1]);
    }
    return 0;
}
```

---

## 作者：Doubeecat (赞：1)

## 题目链接：

[Color the Axis_NOI导刊2011提高（05）](<https://www.luogu.org/problem/P1840>)

## 题目描述：

在一条数轴上有$N$个点，分别是$1 \rightarrow N$。一开始所有的点都被染成黑色。接着我们进行$M$次操作，第$i$次操作将$[L_i,R_i]$这些点染成白色。请输出每个操作执行后剩余黑色点的个数。

## 解题思路：

这个题的思路很简单，把黑色的部分当成1，白色的部分当成0来处理，使用支持区间修改，区间查询的数据结构维护一下即可。  

如果你和我一样是写线段树的，那么更简单了，在下传lazytag的时候只需要将其的左右节点清零即可。

另外在区间查询时由于每次都是查整段的，所以只需要输出`tree[1].num`即可

## 代码：

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
const int N = 200010;
const int M = 500010<<1;
inline int read() {
	int x = 0,f = 1;char v = getchar();
	while (!isdigit(v)) {if (v =='-') f = -1;v = getchar();}
	while (isdigit(v)) {x = x * 10 + v - 48;v = getchar();}
	return x * f;
}

struct node {
	int l,r,num,tag;
}tree[N<<2];

inline void build(int p,int l,int r) {
	tree[p].l = l;tree[p].r = r;
	if (l == r) {
		tree[p].num = 1;
		return ;
	}
	int mid = (l + r) >> 1;
	build (p << 1,l,mid);
	build (p << 1 | 1,mid + 1,r);
	tree[p].num = tree[p<<1].num + tree[p << 1 | 1].num;
	return;
}	

inline void spread(int p) {
	if (!tree[p].num) {
		tree[p<<1].num = tree[p<<1|1].num = 0;
	}
}

inline void change (int p,int x,int y) {
	if (tree[p].l >= x && tree[p].r <= y) {
		tree[p].num = 0;
		return ; 
	}
	spread(p);
	int mid = (tree[p].l + tree[p].r) >> 1;
	if (mid >= x) change(p<<1,x,y);
	if (mid < y) change(p<<1|1,x,y);
	tree[p].num = tree[p<<1].num + tree[p<<1|1].num;
	return ;
}

int main() {
	int n = read(),m = read();
	build (1,1,n);
	for (int i = 1;i <= m;++i) {
		int x = read(),y = read();
		change(1,x,y);
		printf("%d\n",tree[1].num);
	}
	return 0;
}
```


---

## 作者：lemir3 (赞：1)

#P1840 Color the Axis_NOI导刊2011提高（05）

[*题面*](https://www.luogu.org/problemnew/show/P1840)

##题意分析

说句大实话,这题比线段树的板子都好写.

同志们可以把这个数轴视为一个长度为$n$,每一个点的值都为$1$的数列,每次操作就是将一个区间内的数全部变为0,查询整个数列的值.

具体内容直接看代码吧.

##代码:

```cpp

#include "cstdio"
#include "iostream"
#include "cstring"
#include "cstring"
#include "queue"
#include "set"
#include "map"
#include "vector"
#include "iomanip"

#define ll long long
#define lson id<<1
#define rson (id<<1)+1
#define debug(x) printf("debug:%lld\n",x)

using namespace std;

ll n,m;

struct SegmentTree//做一个封装
{
	struct node
	{
		ll l,r,sum;
		bool DeleteMark=false;
	}t[800010];

	inline void BuiltTree(ll id,ll l,ll r)
	{
		ll mid=(l+r)>>1;
		t[id].l=l;
		t[id].r=r;
		if(l==r)
		{
			t[id].sum=1;
			return;
		}
		BuiltTree(lson,l,mid);
		BuiltTree(rson,mid+1,r);
		PushUp(id);
	}

	inline void delete_(ll id,ll l,ll r,ll x,ll y)
	{
		ll mid=(l+r)>>1;
		if(x<=l&&y>=r)
		{
			t[id].sum=0;//如果要查询区间包含了当前区间,就把这个区间的值全部变为1
			t[id].DeleteMark=true;//记录删除标记,将它在树上的所有儿子结点的值也全部变为1
			return;
		}
		PushDown(id);//下传标记
		if(x<=mid)
		{
			delete_(lson,l,mid,x,y);
		}
		if(y>mid)
		{
			delete_(rson,mid+1,r,x,y);
		}
		PushUp(id);
	}

	inline void PushDown(ll id)
	{
		if(t[id].DeleteMark)
		{
			t[lson].DeleteMark=true;//获得标记
			t[rson].DeleteMark=true;
			t[lson].sum=0;//清空
			t[rson].sum=0;
			t[id].DeleteMark=false;
		}
	}

	inline ll query()
	{
		return t[1].sum;
	}

	inline void PushUp(ll id)
	{
		t[id].sum=t[lson].sum+t[rson].sum;
	}

}tree;

signed main(void)
{
	scanf("%lld%lld",&n,&m);
//	n=10;m=3;
	tree.BuiltTree(1,1,n);
	for(ll _=1;_<=m;_++)
	{
		ll l,r;
		scanf("%lld%lld",&l,&r);
		tree.delete_(1,1,n,l,r);
		printf("%lld\n",tree.query());
	}
return 0;
}

```

---

## 作者：清风我已逝 (赞：1)


直接暴力模拟，30，TLE

线段树强做 AC 

我的懒标记下传与别人的不同

一个节点的权值就代表这个区间的白点数

最后直接输出总点数-白点数，即为黑点数

也可以白的为1，黑的为0，此时权值表示的就是黑点数

最后直接输出整个区间的权值就好了
***
	意义不同，标记下放也就不同

***
```cpp
#include<bits/stdc++.h>

using namespace std;

int n,m,ans,sum,tp;
struct node{
	int l,r,w,f;
}e[200000*4+5];

void pushup(int k){
	e[k].w=e[k*2].w+e[k*2+1].w;
}

void build(int k,int l,int r){
	e[k].l=l;e[k].r=r;
	if(l==r){e[k].w=0;return;}
	int mid=(l+r)/2;
	build(k*2,l,mid);build(k*2+1,mid+1,r);
	pushup(k);
}

void pushdown(int k){
	e[k].f=0;e[k*2].f=1;e[k*2+1].f=1;
	e[k*2].w=e[k*2].r-e[k*2].l+1;
	e[k*2+1].w=e[k*2+1].r-e[k*2+1].l+1;
}

void change_interval(int k,int l,int r){
	int ll=e[k].l,rr=e[k].r,mid=(ll+rr)/2;
	if(ll>=l&&rr<=r){
		e[k].w=rr-ll+1;
		e[k].f=1;return;
	}if(e[k].f) pushdown(k);
	if(l<=mid) change_interval(k*2,l,r);
	if(r>mid) change_interval(k*2+1,l,r);
	pushup(k);
}

int main()
{
	cin>>n>>m;
	build(1,1,n);
//	cout<<e[1].w;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		change_interval(1,x,y);
		printf("%d\n",n-e[1].w);
	}return 0;
}
```

---

## 作者：DarkEyeR (赞：1)

一道裸的线段树，白的为1，黑的为0设置即可。

因为每次查询都为总共的，所以只需要返回根即可

```cpp
#include <iostream>
#define MAX 200010
using namespace std;
int sum[MAX<<2],add[MAX<<2],arr[MAX];
int n,m;
void pushup(int rt){
    sum[rt] = sum[rt<<1]+sum[rt<<1|1];
}

void pushdown(int rt){
    if(add[rt]){
        add[rt<<1] = 1;
        add[rt<<1|1] = 1;
        sum[rt<<1] = 0;
        sum[rt<<1|1] = 0;
        add[rt] = 0;
    }
}

void build(int l,int r,int rt){
    if(l == r){
        sum[rt] = arr[l];
        return;
    }
    int m = (l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    pushup(rt);
}

void update(int L,int R,int l,int r,int rt){
    if(L <= l && r <= R){
        sum[rt] = 0;
        add[rt] = 1;
        return;
    }
    int m = (l+r) >> 1;
    pushdown(rt);
    if(L <= m) update(L,R,l,m,rt<<1);
    if(R > m) update(L,R,m+1,r,rt<<1|1);
    pushup(rt);
}

int main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        arr[i] = 1;
    }
    build(1,n,1);
    while(m--){
        int a,b;
        cin >> a >> b;
        update(a,b,1,n,1);
        cout << sum[1] << endl;
    }
    return 0;
}
```

---

## 作者：__stdcall (赞：1)

啊，很裸的线段树，set操作的模板题，当然也可以用add操作来做

直接上代码了








```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
using namespace std;
int n,m;
struct IO {
    static const int BUFSZ = 500000;
    char buf[BUFSZ];
    int idx;
    IO(){ idx = BUFSZ; }
    void readfile() {
        fread( buf , 1 , BUFSZ , stdin );
    }
    char getch() {
        if( idx == BUFSZ ) {
            readfile(); idx = 0;
        }
        return buf[idx++];
    }
    int getnum() {
        int num = 0;
        char ch;
        while( isspace(ch=getch()) );
        do {
            num *= 10;
            num += ch-'0';
        }while( isdigit(ch=getch()) );
        return num;
    }
};
IO io;
struct SGT {
    int setv[800010];
    int sumv[800010];
    int left,right;
    void build(){ buildtree(1,1,n); }
    void buildtree( int o , int L , int R ) {
        if( L == R ) {
            setv[o] = sumv[o] = 1;
            return;
        }
        int M = L+(R-L)/2;
        int lc = o<<1; int rc = lc|1;
        buildtree(lc,L,M);
        buildtree(rc,M+1,R);
        setv[o] = -1; // -1表示没有设置setv的值
        sumv[o] = sumv[lc] + sumv[rc];
    }
    void set0( int L , int R ) {
        left=L; right=R;
        settree(1,1,n);
    }
    void settree( int o , int L , int R ) {
        if( setv[o] == 0 ) return;
        if( L >= left && R <= right ) {
            setv[o] = sumv[o] = 0;
            return;
        }
        int M = L+(R-L)/2;
        int lc = o<<1; int rc = lc|1;
        if( left <= M ) settree(lc,L,M);
        if( right > M ) settree(rc,M+1,R);
        sumv[o] = sumv[lc] + sumv[rc];
    }
    int query() {
        return sumv[1];
    }
};
SGT sgt;
int main() {
    freopen( "axis.in" , "r" , stdin );
    freopen( "axis.out" , "w" , stdout );
    n = io.getnum(); m = io.getnum();
    sgt.build();
    for( int i = 0 ; i < m ; ++i ) {
        int l = io.getnum();
        int r = io.getnum();
        sgt.set0(l,r);
        printf( "%d\n" , sgt.query() );
    }
    return 0;
}

```

---

