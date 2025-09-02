# Balance (Hard version)

## 题目描述

# Balance (Hard version)


这是原题的加强版（就是加上了删除操作啦）。

最初你有一个集合，该集合仅包括一个元素 $0$ 。你需要处理 $q$ 个下述类型的操作：

- `+ x` 向集合中添加一个整数 $x$ 。数据保证集合中原来没有这个整数。
- `- x` 从集合中移除整数 $x$ 。数据保证集合包含这个就要删除的整数。
- `? k` 找出当前是 $k$ 的倍数且不被包含在集合中的最小非负整数 $x$ 。

除 $q$ 外，本题涉及的数据都在 $10^{18}$ 内。

## 说明/提示

**对于第一个样例：**
在第一次和第二次**查询**之后，集合将包含元素 $\{0,1,2\}$ 。是 $1$ 的倍数且不在集合中的最小非负数为 $3$ 。
在第四次**查询**之后，集合将包含元素 $\{0，1，2，4\}$ 。是 $2$ 的倍数且不在集合中的最小非负数是 $6$ 。

**对于第二个样例：**

- 最初，集合只包含元素 $\{0\}$ 。

- 添加整数 $100$ 后，集合包含元素 $\{0，100\}$ 。
- 集合的 $x$ 为 $200$ 。
- 添加整数 $200$ 后，集合包含元素 $\{0，100，200\}$ 。
- 集合的 $x$ 为 $300$ 。
- 移除整数 $100$ 后，该集合包含元素 $\{0，200\}$ 。
- 集合的 $x$ 为 $100$ 。
- 添加整数 $50$ 后，集合包含元素 $\{0，50，200\}$ 。
- 集合的 $x$ 为 $100$ 。
- 移除整数 $50$ 后，该集合包含元素 $\{0，200\}$ 。
- 集合的 $x$ 为 $50$ 。

## 样例 #1

### 输入

```
18
+ 1
+ 2
? 1
+ 4
? 2
+ 6
? 3
+ 7
+ 8
? 1
? 2
+ 5
? 1
+ 1000000000000000000
? 1000000000000000000
- 4
? 1
? 2```

### 输出

```
3
6
3
3
10
3
2000000000000000000
3
4```

## 样例 #2

### 输入

```
10
+ 100
? 100
+ 200
? 100
- 100
? 100
+ 50
? 50
- 50
? 50```

### 输出

```
200
300
100
100
50```

# 题解

## 作者：BigJ2333 (赞：13)

蒟蒻的第一篇题解

~~调了2h+的动态开点线段树被赛后10min写完的set瞎搞做法给吊打了~~


------------


# Description

维护一个集合 $S$ ，有三种操作：插入一个数、删除一个数、查询 $k$ 的倍数中没出现过的最小的数。

# Solution


本来想写动态开点线段树维护，后来发现用 set 瞎搞就能解决。

对于一个修改操作 $x$ ,它有可能影响到哪些询问 $k$ 呢？显然当 $k$ 是 $x$ 的因数时就有可能影响到。所以我们可以维护以下三个集合：

1. 集合 $S$ 就是题目中的集合。

2. 集合 $S1[k]$ 维护对于每个 $k$ ， $k$ 的倍数中“可能”在集合 $S$ 中没出现的数的集合（就是有可能成为答案的集合）。

3. 集合 $S2[k]$ 维护每一个数的因子的集合。这里有一个小技巧，如果我们如果维护每个数的所有因子的话时间肯定会炸，但我们只要维护那些有可能询问到的因子就行了，一边询问一边维护 $S2$ 即可

 

具体地，对于插入操作，直接在 $S$ 中插入即可；

对于删除操作，先在 $S$ 中把这个数 $x$ 删掉，然后再在 $x$ 的所有因子的 $S1$ 中插入 $x$ ；

对于询问 $k$ ， 直接在 $k$ 的 $S1$ 中暴力跳，直到有一个数满足在 $S$ 中没有出现然后输出就行了,顺便在这个过程中维护一下 $S2$

还有一个细节，因为数据范围很大，所以要用 $map$ 代替普通的数组

具体实现看代码吧 （其实还挺短的）

# Code

```cpp
#define int long long

int q;
set <int> S;//题目中的集合s
map <int,set<int> >disapr,factor;
//disapr维护对每个k,k的倍数中"可能"没出现过的数
//factor维护每个x的因数，一边修改一边维护，只记录有用的就行
signed main(){
	cin>>q;
	while(q--){
		char opt;int x;
		cin>>opt>>x;
		if(opt=='+') S.insert(x);
		else if(opt=='-'){
			S.erase(x);
			set <int> ::iterator it=factor[x].begin();
			while(it!=factor[x].end()) disapr[*it].insert(x),it++;
		}else{
			disapr[x].insert(x);
			int u=*disapr[x].begin();
			factor[u].insert(x);
			while(S.count(u)){
				disapr[x].erase(u);
				if(disapr[x].empty()) disapr[x].insert(u+x);
				u=*disapr[x].begin(),factor[u].insert(x);
			}
			cout<<*disapr[x].begin()<<endl;
		}
	}
	return 0;
}
```
暴力跳的复杂度本蒟蒻也不会算，可能是倒数之和均摊一下就变成 $O(qlogX)$ 了？反正能过

---

## 作者：Bring (赞：3)

##### [For better experience please click here.](https://www.cnblogs.com/BrianPeng/p/16827008.html)

First CF round at Cambridge. Solved A,B,D1 in the round. Dropped from purple to blue...

Still a long way to go...

# Solution: CF Round #830 (Div. 2) D1&D2 Balance

## Easy Version

### Brute-force

Evidently the most brute-force way is to create a set to collect the $x$ added. Then for all query with $k,$ check $k,2k,3k,\cdots$ till the first multiple of $k$ that is not contained in the set. Output it.

Obviously it is doomed to TLE, especially when you are queried by the same $k$ multiple times with very large $k\text{-mex}$.

### Becoming Elegant

We try to optimize the brute-force by reducing the time cost if queried by the same $k.$ As there is no remove, if you are queried by $k$ and you find the $k\text{-mex},$ it is obvious that the next time if you are queried by the same $k,$ the answer must be greater than or equal to the previous one.

Therefore, we can memorize all the "previous answers." If $k$ that has a memorized answer is queried, we start checking the set from its previous answer instead of from $1\cdot k.$

Wait, do we avoid TLE just by this "subtle" optimization?

#### Calculation of time complexity (not rigorous):

For queries with the same $k,$ every multiples of $k$ in the set is checked at most once. So the time complexity is the same as if every query is moved to the end of the operations, and every $k$ is queried at most once.

Then, the worst case happens (intuitively) when the first $q/2$ operations fill the set with numbers between $1$ and $q/2,$ and the next $q/2$ operations query for $k=1,2,\cdots,q/2.$ In this case, the number of times checking the set is $O(\sum_{k=1}^{q/2} \frac{q}{2k})=O(q\log q)$ by harmonic series. As every check of the set takes $O(\log q)$ of time, the overall time complexity is $O(q\log^2 q).$

##### Code (795 ms / 12600 KB)

We use a map to memorize the previous answers. The function $\mathtt{srch(x,fs)}$ takes $\mathtt x$ as queried $k$ and $\mathtt{fs}$ its starting number.

```cpp
//This program is written by Brian Peng.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Rd(a) (a=rd())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
int rd(){
	int x;char c(getchar());bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	c^'-'?(k=1,x=c&15):k=x=0;
	while(isdigit(Gc(c)))x=x*10+(c&15);
	return k?x:-x;
}
void wr(int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(int i(a);i<(b);++i)
#define Frn1(i,a,b) for(int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
int q,x;
char opt;
set<int>s;
map<int,int>ans; //Memorization
int srch(int x,int fs);
signed main(){
	Rd(q);
	while(q--){
		cin>>opt,Rd(x);
		if(opt=='+')s.insert(x);
		else{
			if(ans.find(x)!=ans.end())ans[x]=srch(x,ans[x]);
			else ans[x]=srch(x,x);
			wr(ans[x]),Pe;
		}
	}
	exit(0);
}
int srch(int x,int fs){
	while(s.find(fs)!=s.end())fs+=x;
	return fs;
}
```

## Hard Version

Now the "remove" operation is added, and we can no longer memorize the previous answers simply.

Maybe we can use something more powerful, which is able to record "removed" $x$'s?

The most useful tool to record and query the existence of numbers in a given range is

##### Segment Tree

For every queried $k,$ instead of memorizing the previous $k\text{-mex}$, we build a segment tree of $k$ recording the **checked and not removed** multiples of $k.$ In the following text, we let $\text{St}_k$ denote the "SegTree of $k$", and use $x\in \text{St}_k$ to denote that $x$ is recorded in the SegTree of $k.$

For a query with $k$, if $\text{St}_k$ is not set up yet (i.e. $\text{St}_k$ is empty), we go through the multiples of $k$ in the set, which are $k,2k,3k,\cdots$ till the first multiple of $k$ (say $nk$) that is not in the set. Then, the SegTree of $k$ is built with the entries from $1$ to $n-1$ set as $1,$ meaning that $k,2k,\cdots,(n-1)k\in\text{St}_k.$ **(As we only insert multiples of $k$ into $\text{St}_k,$ we let the $i$ th entry of $\text{St}_k$ represent the number $ik$ to make the tree more compact.)**

Thus, **if a number is recorded in a SegTree, it is in the set**.

Then, for removal of $x$, we need to remove $x$ from not only the set, but also from every SegTree that records it. To achieve this, we create a list of $x$ (say $\text{Tk}_x$) that consists of all the $k$'s such that $x\in\text{St}_k.$ In other words, if a certain $x$ is recorded in the SegTree of $k$, we add $k$ into the list $\text{Tk}_x$ so that when $x$ is removed from the set, we remove $x$ from all SegTrees recording it by going through every $k$ in $\text{Tk}_x$ and setting the $x/k$ th entry in $\text{St}_k$ to be $0.$ We clear $\text{Tk}_x$ at the end of the process as $x$ is no longer recorded in any SegTree.

Now, if a $k$ is queried a second time, we **find the least entry in $\text{St}_k$ that is $0.$** (This is why we need to use a SegTree instead of an array, as we may **check whether a sub-interval is set all $1$ by checking if the sum of the interval is equal to its length.**) Say this entry is the $n$ th. If $nk$ is not in the set, we output $nk$ as $k\text{-mex}.$ Otherwise, if $nk$ is in the set, we update the $n$ th entry in $\text{St}_k$ to be $1,$ add $k$ into the list $\text{Tk}_{nk},$ and repeat the process of seeking the least entry in $\text{St}_k$ that is $0.$

### Code Implementation

As the range of $k$ and $x$ in the input is very large, I use `#define int long long` ~~(a wicked trick)~~ for convenience and `signed` is used in place of `int` if such a large range is not needed.

#### Lazy Created Segment Tree

We may see that most of the entries in a SegTree are $0,$ and most of the $k$'s even do not have a SegTree if they are never queried. Thus, we need Lazy Created SegTree to reduce time and memory complexity.

The following is the structure of a node in a lazy created SegTree:

```cpp
struct SgT{signed ls,rs,v;}t[10000000];
```

Here, $\mathtt {ls,rs}$ represent the ids of left/right-son respectively, and $\mathtt v$ represents the sum of the interval the node represents. (The interval is not stored in the nodes explicitly, but they will be clear in functions.)

##### How lazy creation is achieved

1. We use a counter $\mathtt{tn}$ (initial value $0$) to record the highest id of the SegTree nodes. Then whenever a new node is created, we add $1$ to $\mathtt{tn}$ and use it as the id of the new node.

2. Particularly, the **node with id $0$** represents an interval with entries all $0,$ and at the beginning every SegTree has only node $0.$ If a son of a node is $0,$ it means that its half-interval is filled with $0.$

3. We use a map `map<int,signed>rt` to store the root of $\text{St}_k$ (`rt[k]`). For every SegTree, we set its root interval be $[1,q]$ as any number greater than or equal $(q+1)k$ can never be $k\text{-mex}.$ (Why?)

4. We also use a map `map<int,list<int>>tk` to store the lists $\text{Tk}_x$ (`tk[x]`).

Note: apart from the SegTree, the use of **$\mathtt{map}$** for roots and lists are also **Lazy Creation.**


For convenience, we use $\mathtt u$ as the id of the node we are dealing with in a function, and we use `#define` to simplify the id of its two sons:

```cpp
#define Ls (t[u].ls)
#define Rs (t[u].rs)
```

How let's look at how these operations are implemented.

#### Query: Lazy Creation, Updating, and Query in one function

Suppose we are dealing with the SegTree $\text{St}_k.$ The qry function $\mathtt{qry(u,k,l,r)}$ returns the least $n$ in the interval $[l,r]$ such that $nk$ is not in the set. If the interval is all filled with $1,$ return $0$ as the default value.

```cpp
int qry(signed&u,int k,int l,int r){
	if(!u)u=++tn;
	//Lazy Creation happen's here. !!!IMPORTANT: Pass u by Reference!!!
	if(t[u].v==r-l+1)return 0;
	//If the sum is equal to length, then every entry is 1.
	if(l==r){
		//Check if l*k is in the set.
		if(st.find(l*k)!=st.end()){
			t[u].v=1,tk[l*k].push_back(k);
			//l*k is in the set. Update the SegTree and add k into the list tk[l*k].
			return 0;
		}
		else return l;
		//l*k is not in the set, return l (meaning the current k-mex is l*k).
	}
	int md((l+r)/2),ql(qry(Ls,k,l,md));
	//Query the left half-interval first
	if(ql){
		//Found the k-mex, update the SegTree and return.
		t[u].v=t[Ls].v+t[Rs].v;
		return ql;
	}
	//Left half-interval filled with 1. Query the right-interval.
	int qr(qry(Rs,k,md+1,r));
	t[u].v=t[Ls].v+t[Rs].v;
	return qr;
}
```


#### Removal

The modification function $\mathtt{mdf(u,l,r,x)}$ set the **$\mathtt x$ th entry** (Note that the $\mathtt x$ th entry represents the number $\mathtt xk$ recorded in $\text{St}_k$) to be $0$ in the SegTree with root $\mathtt u.$ For the SegTree $\text{St}_k,$ if we want to remove the number $x,$ we implement `mdf(rt[k],1,q,x/k)`.

```cpp
// When implementing, always set l=1 and r=q.
void mdf(signed u,int l,int r,int x){
	while(1){
		//Descending from the root to the leaf.
		--t[u].v;
		if(l==r)return;
		int md((l+r)/2);
		x<=md?(r=md,u=Ls):(l=md+1,u=Rs);
		//Direction chosen by x.
	}
}
```

#### Time complexity Calculation (Not rigorous)

As every checking of set ($O(\log q)$) is accompanied by a SegTree search ($O(\log q)$ as the SegTree interval is $[1,q]$) and possibly a SegTree modification (also $O(\log q)$) for a "remove" later, the time complexity is the same as the easy version: $O(q\log^2 q).$

##### Code (1200 ms / 162500 KB)

```cpp
//This program is written by Brian Peng.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Rd(a) (a=rd())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
int rd(){
	int x;char c(getchar());bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	c^'-'?(k=1,x=c&15):k=x=0;
	while(isdigit(Gc(c)))x=x*10+(c&15);
	return k?x:-x;
}
void wr(int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(int i(a);i<(b);++i)
#define Frn1(i,a,b) for(int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
#define Ls (t[u].ls)
#define Rs (t[u].rs)
int q,x,tn;
char opt;
map<int,signed>rt;
map<int,list<int>>tk;
set<int>st;
struct SgT{signed ls,rs,v;}t[10000000];
int qry(signed&u,int k,int l,int r);
void mdf(signed u,int l,int r,int x);
signed main(){
	Rd(q);
	Frn1(i,1,q){
		cin>>opt,Rd(x);
		if(opt=='+')st.insert(x);
		else if(opt=='-'){
			st.erase(x);
			//Remove x from the set, and go through the list tk[x] if exists.
			if(tk.find(x)!=tk.end()){
				for(int k:tk[x])mdf(rt[k],1,q,x/k);
				tk.erase(x);
				//Remove the list tk[x].
			}
		}else{
			signed tmp(rt[x]?rt[x]:(rt[x]=++tn));
			//As Pass by Reference cannot be used with map,
			//we do lazy creation manually
			wr(qry(tmp,x,1,q)*x),Pe;
		}
	}
	exit(0);
}
int qry(signed&u,int k,int l,int r){
	if(!u)u=++tn;
	if(t[u].v==r-l+1)return 0;
	if(l==r){
		if(st.find(l*k)!=st.end()){
			t[u].v=1,tk[l*k].push_back(k);
			return 0;
		}
		else return l;
	}
	int md((l+r)/2),ql(qry(Ls,k,l,md));
	if(ql){
		t[u].v=t[Ls].v+t[Rs].v;
		return ql;
	}
	int qr(qry(Rs,k,md+1,r));
	t[u].v=t[Ls].v+t[Rs].v;
	return qr;
}
void mdf(signed u,int l,int r,int x){
	while(1){
		--t[u].v;
		if(l==r)return;
		int md((l+r)/2);
		x<=md?(r=md,u=Ls):(l=md+1,u=Rs);
	}
}
```

### Conclusion

Why is Lazy Created SegTree effective in the hard version problem? An intuitive explanation:

In the easy version of the problem, there is no remove, so the non-decresing nature of $k\text{-mex}$ with time for a fixed $k$ leads us to the idea of storing answers, so that we can "move up" from the previous answer in a later query of the same $k$.

In the hard problem, the non-decresing nature of $k\text{-mex}$ is destroyed by the remove operation, and we can no longer record previous answer only. Recording the "checked numbers" in a SegTree, on the other hand, provides us with an efficient way to "move back" to a removed $x,$ and "jump up" if the removed $x$ is inserted into the set again.

Last but not least, the idea of Lazy Creation speeds our code up by creating the data structure only when they are to be used. This idea is extremely useful when **the data range** ($1\leqslant x,k\leqslant 10^{18}$) **is a lot larger than the number of operations** ($1\leqslant q\leqslant 2\cdot 10^5$).

#### Thanks for reading! See you next round!


---

## 作者：Sampson_YW (赞：1)

没搞懂时间复杂度证明。。说一个复杂度比较劣但是复杂度好证明的做法。（复杂度为根号级别）

如果没有删除操作（Easy version），那么复杂度证明直接看[这个讨论](https://www.luogu.com.cn/discuss/518337)感性理解一下大概就懂了。

Easy version 的做法为：暴力做法是从 $0$ 开始枚举倍数。对于查询的数 $k$，记下最后一次查询 $k$ 的答案，下次查询 $k$ 直接从最后一次的答案继续枚举倍数。

那么有删除操作咋办呢，考虑根号重构。对于删除操作，开个数组记录当前删除了哪些数，查询的时候额外扫描这个数组里的所有数。

在加入一个数的时候，如果数组中有这个数就把它删掉。在删除一个数的时候，将这个数加入到数组中。如果当前数组大小 $\ge B$，那么就把所有记忆化过的答案清空，并将这个数组清空。

容易发现数组清空最多 $\frac{q}{B}$ 次，那么复杂度就是 Easy version 跑 $\frac{q}{B}$ 次的复杂度 + 查询时暴力扫数组的复杂度，用 uset 和 umap 就是 $O\left(\frac{q}{B}q\log q+qB\right)$。

注意有卡 umap 和 uset 的数据，所以要随机哈希函数。[code](https://codeforces.com/contest/1732/submission/236047060)

---

## 作者：Priestess_SLG (赞：0)

建议先阅读 [$\textbf{Easy Ver.}$](https://www.luogu.com.cn/article/no1m1rc4) 题解。

前情提要：我不会做这题。所以我用了一个奇奇怪怪的时间复杂度极劣的做法通过了这个题。如果要学习正解建议跳过这篇题解。如果用这个做法的话这题最多蓝（

在简单版本中，没有删除操作，因此对于同一个 $k$ 的答案是单调的，可以直接暴力维护；但是在困难版本中，删除操作导致某一些 $k$ 的值可能会突然反弹回去。而如果暴力枚举所有因数然后把值清空，又有可能陷入删除 - 添加 - 删除 - 添加 - …… 的困境，导致时间复杂度很劣。

那么应该如何避免这种情况呢？简单粗暴的算法肯定不可行了，因此考虑一些奇奇怪怪的做法：设立一个阈值 $P$，对于加入操作还是直接加入一个 `set` 中，删除操作则记录当前所有被删除的元素。查询操作仍然是先暴力跳，然后枚举所有被删除的元素 check 是否用这个元素会合法且让当前答案更优。**为了保证时间复杂度，若某一次操作后删除元素集合的元素数量 $>P$，则直接暴力重构当前集合。**

继续用 `map/set` 系列平衡树相关 STL 时间复杂度多个 $\log$，因此考虑用 `umap/uset` 加 splitmix64 hash，时间复杂度为 $O(qP+\frac qPq\log q)$，根号平衡即 $qP=\frac qPq\log q$，解得 $P=\sqrt{q\log q}$ 时等号成立，此时根号平衡。因此总时间复杂度为 $O(q\sqrt{q\log q}+\frac{q^2\log q}{\sqrt{q\log q}})$，可以通过。

顺便提一下做这题的时候我踩过的坑：

+ 如果你 wa on test $16$，那么请检查如果你缓存了删除信息，但是又在没有 flush 暴力重构删除信息之前插入了元素，那么此时需要特殊处理，将该元素从缓存的信息中删除（撤销）。
+ 如果你 tle on test $60$，那么你要么是被卡常了，要么是因为你把缓存的删除信息用 `set` 存储了。事实证明因为缓存信息量很少所以用 `vector` 存储该信息要远远快于 `set` 存储，差距大约在 $5\sim 6$ 倍左右。
+ 事实证明如果你块长真的取了 $\sqrt{q\log q}$ 会 tle on test $60$，大概是跑 $4\sim 5$ 秒的样子。把块长取 $\sqrt q$ 只会更慢（$25$ 秒左右）。如果把块长取为 $\lfloor 2.5\times\sqrt{q\log q}\rfloor$ test $60$ 会跑 $2$ 秒不到，但是会 tle on test $67$。
+ 如果你块长取 $\lfloor\frac\pi2\sqrt{q\log q}\rfloor$ 那么 test $60,67$ 经过极限卡常都能过，但是会 tle on test $82$，差不多是 $3.2\sim 3.5$ 秒的时间过不去。
+ 只差一点了，能不能再接再厉？启动指令集！`vector` 就算开了 `Ofast` 也跑不过普通的数组，用数组替换，现在是 $3.1$ 秒，真的就只有那么一步了！
+ 众所周知有个东西叫 `fread` 快读，对应的我们还可以发现有一个东西叫 `fwrite` 快写。把这个应用于我们的程序。然后我们还知道 CF 中 `C++17,20,23` 的速度应该是 $20<17<23$ 的，所以用 `C++20` 提交代码，可以获得 $3.05$ 秒的好成绩！
+ 真的就过不去了吗？众所周知还有个东西叫平板电视库，调用该库中的 `gp_hash_table` 要远远快于 `unordered_map`，于是把所有 `umap` 都改成 `gp_hash_table`，这样 test $60$ 只会跑 $1.3$ 秒，test $67$ 只会跑 $0.15$ 秒。但是这样会被专门卡 `gp_hash_table` 的 test $90$ 给卡到 $11$ 秒（值得一提的是，test $69$ 也跑不过去）。
+ 发现如果没有修改操作，然后询问的值已经被询问过了，那么可以直接调用上一次的询问。然后把 buffer 调大一点，可以获得 $3015$ 毫秒的好成绩。
+ 真的没法再优化了啊！考虑继续试块长，最终发现若 $P=\lfloor 1.56\times \sqrt{q\log_2q}\rfloor$，则可以以 $2.95$ 秒的成绩惊险通过。（实际上是 $2952$ 毫秒）。

最后放一下代码，使用了可爱 aimat 姐姐的一些板子。[代码](https://codeforces.com/contest/1732/submission/307029685)。

---

