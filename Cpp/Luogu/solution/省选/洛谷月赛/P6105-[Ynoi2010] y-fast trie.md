# [Ynoi2010] y-fast trie

## 题目背景

谔谔我

本题读入量约 6 MB，输出量约 5 MB，请选择适合的输入输出方法

## 题目描述

给定一个常数 $C$，你需要维护一个集合 $S$，支持 $n$ 次操作：

- 操作1：给出 $x$，插入一个元素 $x$，保证之前集合中没有 $x$ 这个元素
- 操作2：给出 $x$，删除一个元素 $x$，保证之前集合中存在 $x$ 这个元素

每次操作结束后，需要输出 $\max\limits_{\substack{ i, j \in S \\ i \ne j }} \bigl( (i+j) \bmod C \bigr)$，即从 $S$ 集合中选出两个不同的元素，其的和 $\bmod~C$ 的最大值，如果 $S$ 集合中不足两个元素，则输出 `EE`。

本题强制在线，每次的 $x$ 需要 $\operatorname{xor}$ 上次答案 ，如果之前没有询问或者输出了 `EE`，则上次答案为 $0$。

## 说明/提示

Idea：zhouwc，Solution：ccz181078&nzhtl1477，Code：ccz181078&nzhtl1477，Data：nzhtl1477

注意：本题采用**捆绑测试**，只有当你通过一个 subtask 中的所有测试点后，你才能拿到这个 subtask 的分数。

对于其中 $1\%$ 的数据，为样例 1。

对于另外 $9\%$ 的数据，集合中元素个数 $\le 1$。

对于另外 $19\%$ 的数据，$n\leq 500$。

对于另外 $19\%$ 的数据，$n\leq 10^4$。

对于另外 $19\%$ 的数据，$1\leq n,C \leq 10^5$。

对于 $100\%$ 的数据，$1\leq n \leq 5\times 10^5$，$1\leq C\leq 1073741823$，$0\leq x\leq 1073741823$。

## 样例 #1

### 输入

```
7 9
1 2
1 3
1 0
1 14
2 14
2 13
1 1
```

### 输出

```
EE
5
8
8
8
5
7
```

# 题解

## 作者：Owen_codeisking (赞：39)

比赛时 T2 忘开 long long 自闭了好长时间，这是赛后写的。

好像这题还蛮套路的？

首先我们先分类讨论（加入集合 $S$ 时已取模）：

1. $C\le i+j<2\times C$，因为 $0\le i,j< C$，所以取个最大值和次大值就行了。

2. $0\le i+j<C$，这样的话每个数 $i$ 会有一个最佳匹配 $j$，使得 $i+j$ 最接近 $C-1$。显然这个匹配是单向的。

若此题离线，那么考虑线段树分治，每次加进去的时候把这个数的最佳匹配找出来，对答案取个 $\max$。时间 $O(n\log^2 n)$。

现在考虑在线。若删除的话，有可能这个数是多个数的最佳匹配，那么一次删除涉及最多 $O(|S|)$ 次重新匹配，显然不可取。

那么我们换个角度考虑，只维护双向匹配的对数，这样每次修改只涉及 $O(1)$ 对，时间就对了。

为什么呢？

一般这种最优化数对的题，都是先弄出个 $O(n^2)$ 的解法，再看看这些对数是否满足什么限制，使得某个数对 $(i,j)$ 一定比 $(j,k)$ 优，这些数对一定很少且一次修改涉及的对数不多，所以我们只需要维护这些数对。

假设 $i$ 的最优匹配是 $j$，$j$ 的最优匹配是 $k$。若 $i<k$，那么只需考虑 $(j,k)$ 这一数对。

这样的数对显然最多 $O(n)$ 个，用 $\text{multiset}$ 维护最优匹配，时间 $O(n\log n)$。

不过你一次修改需要找出这个数的最优匹配，最优匹配的最优匹配，最优匹配的最优匹配的最优匹配，常数比较大，细节有一点。建议画个图把细节理清楚再写。还有，$\text{stl}$ 的边界要格外小心。

最短代码 $\text{1.13k}$：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,c,sz;
multiset<int> a,b;
multiset<int>::iterator it;
inline int best(int x,int op)
{
	if(x==-1) return -1;
	it=a.upper_bound(c-1-x);
	if(it==a.begin()) return -1;
	it--;
	if(op==1 && *it==x && a.count(x)==1)
		return (it==a.begin())?-1:*--it;
	else
		return *it;
}
inline void insert(int x)
{
	sz++;
	if(sz==1) { a.insert(x); return; }
	int y=best(x,0),z=best(y,1),w=best(z,1);
	if(y!=-1 && z<x)
	{
		if(z!=-1 && y==w) b.erase(b.find(y+z));
		b.insert(x+y);
	}
	a.insert(x);
}
inline void erase(int x)
{
	a.erase(a.find(x)),sz--;
	if(!sz) return;
	int y=best(x,0),z=best(y,1),w=best(z,1);
	if(y!=-1 && z<x)
	{
		if(z!=-1 && y==w) b.insert(y+z);
		b.erase(b.find(x+y));
	}
}
inline int query()
{
	it=--a.end();
	if(a.count(*it)>=2) return *it*2%c;
	else return (*it+*--it)%c;
}
int main()
{
	scanf("%d%d",&n,&c);
	int op,x,lastans=0;
	while(n--)
	{
		scanf("%d%d",&op,&x); x^=lastans;
		if(op==1) insert(x%c);
        else erase(x%c);
		if(sz<2) puts("EE"),lastans=0;
		else printf("%d\n",lastans=max(query(),b.empty()?0:*--b.end()));
	}
	return 0;
}
```

（估计我大括号不换行会更短）

题出得好！难度适中，覆盖知识点广，码量不大，解法比较自然，给出题人点赞！

~~就是没啥 gal 的背景，差评~~

upd: 好像不能每次都过？

---

## 作者：Fading (赞：12)

这道题我和ljc争论了快一个小时，然后我来写了（

考场上我被T1搞睡了一个小时，被T2卡常卡了快一个小时，就没时间写这题的线段树分治了。

------------


我们把加入的数全部$\bmod \ C$

首先答案分成两类，一类$-C$，一类不$-C$，前者直接求最大值+次大值就好了，我们考虑后者。

首先平衡树可以轻松求出一个数$x_1$对应的在这个集合里的$x_2$，满足$x_1+x_2$最接近$C$。

一个想法就是每一个数只维护一个和最大的匹配，接下来就是删除怎么更新了。

我们考虑用平衡树维护匹配，一个数在平衡树里只能出现一次。

考虑插入一个$x_1$，找到那个$x_2$，如果$x_2$原先已经匹配上了$x_3$，就看看$x_1,x_3$哪个大。如果$x_3$小就换匹配。

考虑删除一个$x_1$，就把原先匹配上的$x_4$删去，再和插入一样去更新原先匹配上的$x_4$。

我们把匹配的值存在$\texttt{multiset}$里，把匹配的信息存在$\texttt{unordered\_map}$，每次删除就好了。

你可能会问，不会连锁反应吗？

其实是不会的。此时如果删去了$x_3$，到时候$x_1$或$x_2$删去的时候又会更新回来。



------------

你以为这么简单吗？

最恶心的就是$x\bmod C$可能出现好几次！RE，WA，TLE...

这样你就在插入更新的时候就需要疯狂讨论，疯狂讨论。。。

ljc：要不要你写一下试试？

------------

这是STL的更新部分

```cpp
inline void update(int x){
	wht=get(x);
	if (wht==-1) return;
	if (pr.count(x)&&pr.count(wht)){//本来不需要这么讨论的，但是这题。。。
		opx=pr[x],opw=pr[wht];
		if (wht>opx&&x>opw){
			pr.erase(opw),pr.erase(opx);
			pr[wht]=x;pr[x]=wht; 
			register int caca=x+opx,cacb=wht+opw;
			S.erase(S.find(caca));
			if (caca!=cacb) S.erase(S.find(cacb));
			S.insert(x+wht);
		}
	}else if (pr.count(x)){
		opx=pr[x];
		if (opx<wht){
			pr.erase(opx),pr[wht]=x,pr[x]=wht;
			S.erase(S.find(x+opx)),S.insert(x+wht);
		}
	}else if (pr.count(wht)){
		opw=pr[wht];
		if (opw<x){
			pr.erase(opw),pr[wht]=x,pr[x]=wht;
			S.erase(S.find(wht+opw)),S.insert(x+wht);
		}
	}else{
		pr[wht]=x,pr[x]=wht;
		S.insert(wht+x);
	}
}
```
ljc说，可以不用这么分类讨论，相同数的贡献单独算就好了

这样代码就变得非常小清新，几乎没细节了。

~~真就这么简单~~

```cpp
#include<bits/stdc++.h>
#define mit map<int,int>::iterator
using namespace std;
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
inline int read(){
    register int x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-') f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
map<int,int> mp;
unordered_map<int,int> pr;
multiset<int> S;
set<int> two; 
int wht,opx,opw,n,C,ans,las,opt,x,cnt;
inline int get(int x){
	mit it=mp.lower_bound(C-x);
	if (it==mp.begin()) return -1;
	else{
		if ((*--it).first==x){
			if (it==mp.begin()) return -1;
			it--;
		}
		return (*it).first;
	}
}
inline void update(int x){
	wht=get(x);
	if (wht==-1) return;
	if (pr.count(wht)){
		opw=pr[wht];
		if (opw<x){
			pr.erase(opw),pr[wht]=x,pr[x]=wht;
			S.erase(S.find(wht+opw)),S.insert(x+wht);
		}
	}else{
		pr[wht]=x,pr[x]=wht;
		S.insert(x+wht);
	}
}
inline void add(int x){
	mp[x]++;
	if (mp[x]==1) update(x);
	else if (mp[x]==2){
		if (2*x<C) two.insert(2*x);
	}
}
inline void del(int x){
	mp[x]--;
	if (mp[x]==0){
		mp.erase(x);
		if (pr.count(x)){
			opx=pr[x];
			pr.erase(opx),pr.erase(x);
			S.erase(S.find(opx+x));
			update(opx);
		}
	}else if (mp[x]==1){
		if (2*x<C) two.erase(2*x);
	}
}
inline int query(){
	ans=0;
	mit it=(--mp.end());
	if ((*it).second>1) ans=(*it).first*2;
	else ans=(*it).first+(*--it).first;
	ans=max(ans%C,(!two.empty()?(*--two.end()):0));
	ans=max(ans,(!S.empty()?(*--S.end()):0));
	return ans;
}
signed main(){
	n=read(),C=read();
	while (n--){
        opt=read(),x=read();
		x^=las;
		if (opt==1) add(x%C),cnt++;
		else del(x%C),cnt--; 
		if (cnt>1) las=query(),printf("%d\n",las);
		else puts("EE"),las=0;
	}
    return 0;
}
```


好久没写Ynoi了。

事实证明我STL水平极其垃圾。

居然因为subtask取min的机制最优解了？？

听说有一个更好写更快的写法。

---

## 作者：Terac (赞：6)

[$\texttt{link}$](https://www.luogu.com.cn/problem/P6105)

## 题意

给定常数 $C$，维护一个集合 $S$，$n$ 次操作，支持插入、删除，每次操作后询问 $\max\limits_{i,j\in S\land i\ne j}\{(i+j)\bmod C\}$，强制在线。

数据范围：$1\le n\le 5\times 10^5,1\le C\le 1073741823$

## 题解

以下默认 $|S|,n$ 同级。

首先发现加入一个数的时先对它取模不影响正确性，也便于处理。

然后思考下这个模 $C$ 意义下和的最大值。

发现可以分类讨论：
- 当 $C\le i+j\le 2\times C$ 时，从集合中取最大值和次大值出来即可。
- 当 $0\le i+j < C$ 时，可以想到个暴力，对于每个 $x\in S$，找到 $\max\limits_{y\in S\land x\ne y}((x+y)\bmod C)$，在这些值中取最大值即可。

第一类情况 simple，我们只看第二类。

$y$ 其实就是 $C-1-x$ 的前驱，可以 $O(\log n)$ 求得，而这个匹配是单向的，复杂度 $O(n^2\log n)$。

在这个过程中有许多的匹配是不优的，但我们都考虑了进去，每次插入删除要更新的个数级别是 $O(n)$ 的，考虑维护更少的匹配。

有个结论，若 $x$ 的最优匹配是 $y$，$y$ 的最优匹配是 $z$，那么 $(x+y)\bmod C$ 不如 $(y+z)\bmod C$。

这个结论证明也很显然，存在这种情况说明 $y$ 有更好的选择。这个结论可推出只用维护所有双向的匹配即可，每次插入删除要更新的数就变成 $O(1)$ 的了。

于是每次插入 $x$ 考虑其最优匹配 $y$，看 $x$ 是否能对 $y$ 的匹配产生影响，删除相当于重新插入 $y$，这样的复杂度就是 $O(n\log n)$ 的。

因为插入集合后对 $C$ 取模了，所以可能会有重复，用 STL 的 `multiset` 就好，注意找匹配时可能会找回自己，要判掉。

```cpp
#include <bits/stdc++.h>
#define IT multiset<int>::iterator
using namespace std;
multiset<int> s, pr;
int n, c;
int mat(int x, bool t) {
	if(!~x) return -1;
	IT it = s.upper_bound(c - 1 - x);
	if(it == s.begin()) return -1;
	--it;
	if(t && *it == x && s.count(x) == 1)
		return it == s.begin() ? -1 : *--it;
	return *it;
}
void ins(int x) {
	if(s.empty()) { s.insert(x); return; }
	int y = mat(x, 0), z = mat(y, 1), w = mat(z, 1);
	if(~y && x > z) {
		if(~z && y == w) pr.erase(pr.find(y + z));
		pr.insert(x + y);
	}
	s.insert(x);
}
void del(int x) {
	s.erase(s.find(x));
	if(s.empty()) return;
	int y = mat(x, 0), z = mat(y, 1), w = mat(z, 1);
	if(~y && x > z) {
		if(~z && y == w) pr.insert(y + z);
		pr.erase(pr.find(x + y));
	}
}
int qry() {
	int res;
	IT it = --s.end();
	if(s.count(*it) >= 2) res = *it * 2 % c;
	else res = (*it + *--it) % c;
	if(!pr.empty()) res = max(*--pr.end(), res);
	return res;
}
int main() {
	scanf("%d%d", &n, &c);
	int opt, x, last = 0;
	while(n--) {
		scanf("%d%d", &opt, &x);
		x = (x ^ last) % c;
		if(opt == 1) ins(x);
		else del(x);
		if(s.size() < 2) puts("EE"), last = 0;
		else printf("%d\n", last = qry());
	}
	return 0;
}
```

---

## 作者：Saliеri (赞：3)

好像是一个新思路，所以来写题解。

___

不难想到对于 $i+j<c$ 与 $i+j\ge c$ 分类讨论。

很明显第二类的最大值是平凡的——我们只需要将集合中最大的两个数取出来即可。

考虑第一类贡献，其他题解的想法是维护双向的最优匹配，但是仔细想想会发现一个很有用的结论——

- 对于每一个数，必然在值域上存在**一段区间**，使得在这段区间内的数都与这个数匹配最优。

于是我们的想法就变成了对于每一个数，维护在它这段最优区间内的最大值（如果这段区间内没有数就是 $-\text{inf}$）。然后将每一个数的答案放进可删堆里即可。

现在考虑如何修改，我们发现如果这样想的话，修改也是非常简单的——

- 对于插入，相当于分裂一个已有的区间，并且更新这一个数所在的另一个数的最优区间的答案。这两个操作都可以通过维护平衡树（set / map） 来维护。

- 对于删除，基本同理，只不过变成了合并区间。

因为每一次修改只会执行 $O(1)$ 次平衡树操作，所以总复杂度是 $O(n\log n)$。

___

但是这就完了吗？远远没有。

首先，不要天真的以为插入的数都互不相同， $\text{mod }C$ 之后就可能相同了，所以你需要讨论一个数的出现次数，用 map 记录会好一些。

然后，因为一个数不能与自己匹配，所以求它最优区间内的最大值时要将自己排除掉。

最后，因为这个做法常数是真的很大。所以你需要：

- 尽量通过特判减少你的平衡树操作。

- 通过 set 包含的结构体内部变量的 mutable 修饰符将区间的删除再插入变成直接修改。（重要！） 

最后一次大改前的代码（67pts）：

```cpp
#include <map>
#include <set>
#include <queue>
#include <cstdio>
const int Mxdt = (1<<16);
inline char pc(char ch,bool bj) {
	static char buf[Mxdt],*p1=buf,*p2=buf+Mxdt;
	return ((bj)||(*p1++=ch)&&p1==p2)&&fwrite(p1=buf,1,p1-buf,stdout),0;
}
void print(int x) {
	if(x>9)print(x/10);
	pc(x%10^48,false);
}
inline void printnum(int x,int ch) {
	if(x < 0)pc('-',false),x=-x;
	print(x),pc(ch,false);
}
char gc() {
	static char buf[1<<16],*S,*T;
	if(T==S) {
		T=(S=buf)+fread(buf,1,1<<16,stdin);
		if(T==S) return EOF;
	}
	return *S++;
}
#define getchar gc
inline int re() {
	char C;
	while((C=getchar())>'9'||C<'0');
	int res = C-'0';
	while((C=getchar())>='0'&&C<='9')res = res*10+C-'0';
	return res;
}
const int inf = 1073741824;
inline int max(int a,int b){return a>b?a:b;}
int n,C,ty,v,lstans,tv,Cnt;
struct Heap {
	std :: priority_queue <int> q1,q2;
	void ins(int x) {q1.push(x);}
	void del(int x) {q2.push(x);}
	int top() {while(q1.top() == q2.top())q1.pop(),q2.pop();return q1.top();}
} H;//可删堆
struct Int{
	int l,r;
	mutable int mx;
	Int(int L=0,int R=0,int Mx=0):l(L),r(R),mx(Mx){};
	bool operator <(const Int &b)const{return r<b.r;}
};
std :: set<Int> s1;
std :: map<int,int> s2;
std :: set<Int> :: iterator it;
std :: map<int,int> :: iterator tp;
//值域 [l,r] 内最大的不等于 v 的数。
int Maxlr(const int &l,const int &r,const int &v){
	if(r == C)return -inf;
	tp = s2.upper_bound(r);
	if(tp == s2.begin())return -inf;
	--tp;
	if(tp->first < l)return -inf;
	if(tp->first == v && tp -> second == 1){
		if(tp == s2.begin())return -inf;
		--tp;
	}
	return (tp->first<l?-inf:tp->first);
}
int mapMax(){
	tp = --s2.end();
	if(tp->second >= 2)return 2*tp->first;
	int v = tp->first;
	--tp;return v+tp->first;
}//最大值+次大值。
int main() {
	n = re(),C = re(),s1.insert(Int(0,C,-inf)),H.ins(-inf);
	static const int mod = C;
	while(n--){
		ty = re(),v = (re()^lstans)%mod;
		if(ty == 1){
        //如果出现了两次以上，改动就不有影响。删除同理。
			int V = ++s2[v];++Cnt;
			if(V == 2){
				it = s1.lower_bound(Int(0,v,0));
				if(it -> r != C)
					if(it->mx-(C-it->r-1) < v)
						H.del(it -> mx),H.ins(it->mx=C-it->r-1+v);
			}
			if(V == 1){
				it = s1.lower_bound(Int(0,v,0));
				if(it -> r != C)
					if(it->mx-(C-it->r-1) < v)H.del(it -> mx),H.ins(it->mx=C-it->r-1+v);
                    		//只有第一次插入需要分裂
				it = s1.lower_bound(Int(0,C-v-1,0));
				Int tmp = *it;H.del(tmp.mx),s1.erase(it);
				s1.insert(Int(tmp.l,C-v-1,tv=Maxlr(tmp.l,C-v-1,v)+v)),H.ins(tv);
				if(tmp.mx-(C-tmp.r-1) < C-v)s1.insert(Int(C-v,tmp.r,tv=-inf)),H.ins(tv);
				else s1.insert(Int(C-v,tmp.r,tv=tmp.mx)),H.ins(tv);
			}
		}
		if(ty == 2){
			int V = --s2[v];--Cnt;
			if(V == 1){
				it = s1.lower_bound(Int(0,v,0));
				if(it -> r != C)H.del(it -> mx),H.ins(it->mx=C-it->r-1+Maxlr(it->l,it->r,C-it->r-1));
			}
			if(V == 0){
				s2.erase(s2.find(v));
				it = s1.lower_bound(Int(0,v,0));
				if(it -> r != C)H.del(it -> mx),H.ins(it->mx=C-it->r-1+Maxlr(it->l,it->r,C-it->r-1));
				it = s1.lower_bound(Int(0,C-v-1,0));
				Int tmp = *it,tmp1;
				H.del(tmp.mx),++it,s1.erase(tmp);
				tmp1 = *it,s1.erase(it),H.del(tmp1.mx);
				if(tmp1.mx > 0)s1.insert(Int(tmp.l,tmp1.r,tv=tmp1.mx)),H.ins(tv);
				else s1.insert(Int(tmp.l,tmp1.r,tv=C-tmp1.r-1+Maxlr(tmp.l,tmp1.r,C-tmp1.r-1))),H.ins(tv);
			}
		}
		if(Cnt < 2)pc('E',0),pc('E',0),pc('\n',0),lstans = 0;
		else printnum(lstans=(max(H.top(),mapMax()%mod)),'\n');
	}
	return pc('L',1);
}
```

---

## 作者：WrongAnswer_90 (赞：3)

[更好的阅读体验](https:https://www.cnblogs.com/WrongAnswer90-home/p/17972741)

[P6105 [Ynoi2010] y-fast trie](https://www.luogu.com.cn/problem/P6105)

首先把所有数对 $C$ 取模，分类讨论：

1. $x+y\geq C$

因为只会取模一次，这时显然取最大值和次大值。

2. $x+y<C$

一开始的想法是对于每一个数 $a$ 找到另一个数满足 $a+b<C$ 的最大的 $b$，这样是一棵外向树（环长一定 $=2$），修改如果修改到入度比较大的节点复杂度不对。

接下来是神奇套路：$(a,b)$ 需要被维护当且仅当 $(a,b)$ 互为最优配对。

对于加数，加进去的数 $a$ 寻找一个最优配对 $b$，如果 $b$ 没有被配对直接把 $(a,b)$ 扔进堆里。否则比较 $b$ 的配对 $c$ 和 $a$ 的大小，取较大者和 $b$ 配对，较小者不与任何数配对（一定不会与任何数配对，因为较小数找到的配对数一定是 $b$）。

对于删数，如果 $a$ 没有配对直接删掉，否则把 $(a,b)$ 都删掉，然后插入 $b$。

显然上述操作一定不会遗漏互为最优的配对。

开一个堆维护所有配对，开一个 `set` 维护所有数，复杂度 $\mathcal O(n\log n)$。注意插入的数中可能有 $0$。

```cpp
	struct Node{int v,oth;Node(int V,int Oth){v=V,oth=Oth;};};
	bool operator <(const Node nd1,const Node nd2){return nd1.v<nd2.v||(nd1.v==nd2.v&&nd1.oth<nd2.oth);}
	multiset<Node> st;
	struct Delq
	{
		priority_queue<int> q1,q2;
		inline void ins(int x){q1.e(x);}
		inline void del(int x){q2.e(x);}
		inline void update(){while(q1.size()&&q2.size()&&q1.top()==q2.top())q1.pop(),q2.pop();}
		inline int top(){return update(),q1.size()?q1.top():-inf;}
	}q;
	int n,m;
	inline void ins(int x)
	{
		auto it=st.lower_bound(Node(m-x,-1));int oth=-1;
		if(it!=st.begin())
		{
			--it;Node nd=*it;
			if(nd.oth==-1)st.erase(it),st.insert(Node(oth=nd.v,x)),q.ins(nd.v+x);
			else
			{
				if(nd.oth<x)
				{
					st.erase(it),st.erase(st.find(Node(nd.oth,nd.v)));
					st.insert(Node(nd.oth,-1)),st.insert(Node(nd.v,x));
					q.del(nd.v+nd.oth),q.ins(nd.v+x),oth=nd.v;
				}
			}
		}
		st.insert(Node(x,oth));
	}
	inline void mian()
	{
		read(n,m);int opt,x,ans=0;
		while(n--)
		{
			read(opt,x),x=(x^ans)%m;
			if(opt==1)ins(x);
			else
			{
				auto it=st.lower_bound(Node(x,-1));Node nd=*it;
				if(nd.oth==-1)st.erase(it);
				else q.del(nd.oth+nd.v),st.erase(it),st.erase(st.find(Node(nd.oth,nd.v))),ins(nd.oth);
			}
			ans=q.top();
			if(st.size()>=2)Mmax(ans,((--st.end())->v+(--(--st.end()))->v)%m);
			if(ans<0)puts("EE"),ans=0;else write(ans,'\n');
		}
	}
```

---

## 作者：SymphonyOfEuler (赞：3)

**题意：**

维护一个集合，支持集合中一下两种操作：

- 1. 插入一个元素（集合中以前没有这个元素的情况下）

- 2. 删除一个元素（集合中有这个元素的情况下）

操作完毕后，输出随意两个不同的元素之和的最大值，模 $C$。若集合长度 $< 1$，即，不足两个数字，则输出 `EE`。每次输入需要异或上次的答案。

**思路：**

考虑用线段树分治。$O(nlog^2n)$

可惜题目要求强制在线。所以我们换个方法，用 $multiset$，求解时分两类：

- $i+j$（集合中随意两个元素）必须 $\ge C$，并且 $< 2C$，求出最大值和第二大值之和即可。因 $0 \le i,j < C$，所以上面的解成立。

- $i+j$ 大于等于0，小于 $C$。对于这种情况，维护所谓的 $i$ 最佳匹配的 $j$（让这两个元素的和接近$C$）。

$i$ 的最佳匹配可以用 $multiset$ 维护，删除操作复杂度 $O(length(set))$，如果所有情况都考虑的话太废时间了，所以需要做优化。


维护 $i$ 的最优匹配 $j$ 时，有一个情况，可以将一些配对忽略。

我们想一下，一个数 $a$，最佳匹配为 $b$，而 $b$ 最佳匹配为 $c$，且 $c$ 大于 $a$，显然，我们要求的尽可能大，可以省去掉前面的那两个数，使用 $b,c$ 这两个。

这样复杂度就从 $O(length(set))$ 优化到了 $O(nlogn)$。

**注意事项：**

- 这题中取 $a$ 的最优匹配的最优匹配的时候，容易把变量搞混，加倍注意。

- 记住，如果输出了 `EE`，一定要把上次答案变量设为 $0$，其他情况也要异或上次答案+设上次答案变量为这次答案。

- `本题读入量约 6 MB，输出量约 5 MB，请选择适合的输入输出方法` lxl的凉心提醒，我选择cin加速，你 自 己 看 着 办。

- 有可能会一片RE，查一下你的函数有没有返回值，$multiset$ 顺序是否正确

**代码：**

```
/* by JS */

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

int len, n, c, lans;

multiset<int> mst1, mst2;

struct kafuu_chino {

    static inline int ask1(register int d) {
        if (d == -1) return -1;
        if (mst1.begin() == mst1.upper_bound(c - d - 1)) return -1;
        multiset<int>::iterator mst3;
        mst3 = mst1.upper_bound(c - d - 1);
        --mst3;
        if (*mst3 == d && mst1.count(d) == 1) {
            if (mst3 == mst1.begin()) return -1;
            else return *--mst3;
        } else return *mst3;
    }

    static inline int ask2(register int d) {
        if (d == -1) return -1;
        if (mst1.begin() == mst1.upper_bound(c - d - 1)) return -1;
        multiset<int>::iterator mst3;
        mst3 = mst1.upper_bound(c - d - 1);
        --mst3;
        return *mst3;
    }

    inline void add(register int d) {
        ++len;
        if (len == 1) {
            mst1.insert(d);
            return;
        }
        register int tmp1 = ask2(d), tmp2 = ask1(tmp1), tmp3 = ask1(tmp2);
        mst1.insert(d);
        if (tmp2 < d && tmp1 != -1) {
            if (tmp2 != -1 && tmp1 == tmp3) {
                mst2.erase(mst2.find(tmp1 + tmp2));
            }
            mst2.insert(tmp1 + d);
        }
    }

    inline void del(register int d) {
        --len;
        _Rb_tree_const_iterator<int> pos = mst1.find(d);
        mst1.erase(pos);
        if (len == 0) return;
        register int tmp1 = ask2(d), tmp2 = ask1(tmp1), tmp3 = ask1(tmp2);
        if (tmp2 < d && tmp1 != -1) {
            if (tmp2 != -1 && tmp1 == tmp3) {
                mst2.insert(tmp1 + tmp2);
            }
            mst2.erase(mst2.find(tmp1 + d));
        }
    }
} qwq;

inline void solve() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> c;
    for (register int i = 1; i <= n; ++i) {
        register int op, x;
        cin >> op >> x;
        x ^= lans;
        if (op == 1) {
            x %= c;
            qwq.add(x);
        }
        if (op == 2) {
            x %= c;
            qwq.del(x);
        }
        if (len <= 1) {
            cout << "EE\n";
            lans = 0;
        } else {
            if (mst2.empty()) {
                auto mst3 = --mst1.end();
                register int res;
                if (mst1.count(*mst3) > 1) {
                    res = *mst3 * 2 % c;
                } else {
                    res = (*mst3 + *--mst3) % c;
                }
                cout << max(res, 0) << '\n';
                lans = max(res, 0);
            } else {
                register int query;
                auto mst3 = --mst1.end();
                if (mst1.count(*mst3) > 1) {
                    query = *mst3 * 2 % c;
                } else {
                    query = (*mst3 + *--mst3) % c;
                }
                cout << max(query, *--mst2.end()) << '\n';
                lans = max(query, *--mst2.end());
            }
        }
    }
}

int main() {
    solve();
    return 0;
}

```



**最后：** ~~谔谔我~~


---

## 作者：_Diu_ (赞：2)

给出一个和其他题解不同的会被卡空间的做法。

我们同样先把询问转成 $i+j\ge C$ 和 $i+j<C$ 两个部分。对于 $i+j\ge C$ 的，我们找全局最大次大即可。

对于 $i+j<C$ 的，我们考虑对于每个 $i$，找到满足 $i+j<C$ 的最大的 $j$，然后对所有 $i$ 统计答案。

考虑把信息放在值域上，每个数 $i$ 在位置 $i$ 插入作为一类点，在位置 $C-i$ 插入作为二类点。这样做的好处是什么呢？这样对于每个一类点 $i$，其满足 $i+j<C$ 的最大的 $j$ 既是最小的比它大的二类点。这样我们可以用值域线段树维护。复杂度为 $O(n\log V)$，缺点是需要动态开点，空间也是 $O(n\log V)$。

但是有个问题，题目要求 $i\not=j$，这可以通过维护最大次大解决。具体来说，线段树上每个节点维护最大次大的第一类点和最小次小的第二类点即可。

```cpp
struct node{
	int x,y;
	node(int xx=-1,int yy=-1){x=xx,y=yy;}
};
node operator+(node a,node b){
	if(b.x!=-1){
		if(a.x==-1)a.x=b.x;
		else if(a.y==-1)a.y=b.x;
	}
	if(b.y!=-1){
		if(a.x==-1)a.x=b.y;
		else if(a.y==-1)a.y=b.y;
	}
	return a;
}
int operator*(node a,node b){
	if(a.x==-1||b.x==-1)return 0;
	if(a.x!=b.x)return a.x+b.x;
	else if(a.y!=-1&&b.y!=-1)return max(a.x+b.y,a.y+b.x);
	else if(a.y!=-1)return a.y+b.x;
	else if(b.y!=-1)return a.x+b.y;
	return 0;
}
```

但是本题空间限制 128M，无法通过。我尝试了底层分块，具体而言，对于区间 $\le B$ 的情况直接暴力处理，每一位每一类点信息只有 $3$，因此用三进制数储存压缩空间，但是还是无法通过本题。

接下来我们还有两个方案。一个是我们采用动态开点线段树的虚树写法即可把空间做到线性。也就是如果一个点只有一个儿子，那么它没必要存在。感兴趣的同学可以实现一下。

另一个是我们发现其实我们只需要一个支持单点修和 `pushup`，我们可以把线段树换成随便一个平衡树即可做到空间线性。

实测 fhq 被卡到趋势，但是 splay 抖一抖能过。splay 的常数其实并不大，并且这题相当于没有查询，splay 表现得会更加优秀。感谢 bdzzj 帮忙卡常。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,C;
int tot,rt;
int c1[N],c2[N],mx[N],val[N],L[N],R[N],fa[N];
struct node{
	int x,y;
	node(int xx=-1,int yy=-1){x=xx,y=yy;}
};
node lm[N],rm[N];
inline node operator+(node a,node b){
	if(b.x!=-1){
		if(a.x==-1)a.x=b.x;
		else if(a.y==-1)a.y=b.x;
	}
	if(b.y!=-1&&a.y==-1)a.y=b.y;
	return a;
}
inline int operator*(node a,node b){
	if(a.x==-1||b.x==-1)return 0;
	if(a.x!=b.x)return a.x+b.x;
	else if(a.y!=-1&&b.y!=-1)return max(a.x+b.y,a.y+b.x);
	else if(a.y!=-1)return a.y+b.x;
	else if(b.y!=-1)return a.x+b.y;
	return 0;
}
int cntt=0;
inline void up(int x){
	cntt++;
	rm[x].x=c1[x]>0?val[x]:-1;
	rm[x].y=c1[x]>1?val[x]:-1;
	lm[x].x=c2[x]>0?C-val[x]:-1;
	lm[x].y=c2[x]>1?C-val[x]:-1;
	mx[x]=0;
	if(L[x]){
		mx[x]=max(max(mx[x],mx[L[x]]),rm[L[x]]*lm[x]);
		rm[x]=rm[x]+rm[L[x]];
		lm[x]=lm[L[x]]+lm[x];
	}
	if(R[x]){
		mx[x]=max(max(mx[x],mx[R[x]]),rm[x]*lm[R[x]]);
		lm[x]=lm[x]+lm[R[x]];
		rm[x]=rm[R[x]]+rm[x];
	}
	return;
}
inline void pushup(int x){
	up(x);
	return; 
}
inline void rotate(int x){
	int f=fa[x];
	if(x==L[f]){
		L[f]=R[x];
		R[x]=f;
		if(f==rt) rt=x;
		else{
			if(fa[f]){
				if(f==L[fa[f]]) L[fa[f]]=x;
				else R[fa[f]]=x;
			}
		}
		fa[x]=fa[f];
		if(L[f]) fa[L[f]]=f;
		fa[f]=x;
		pushup(f);
		pushup(x);
//		if(fa[x]) pushup(fa[x]);
	}else{
		R[f]=L[x];
		L[x]=f;
		if(f==rt) rt=x;
		else{
			if(fa[f]){
				if(f==L[fa[f]]) L[fa[f]]=x;
				else R[fa[f]]=x;
			}
		}
		fa[x]=fa[f];
		if(R[f]) fa[R[f]]=f;
		fa[f]=x;
		pushup(f);
		pushup(x);
//		if(fa[x]) pushup(fa[x]);
	}
	return;
}
inline void splay(int x){
	while(fa[x]){
		int f=fa[x];
		if(fa[f]){
			if((L[fa[f]]==f)==(L[f]==x)) rotate(f);
			else rotate(x);
		}
		rotate(x);
	}
	return;
}
void inserts(int &rt,int f,int x,int tp,int v){
	if(!rt){
		rt=++tot;
		val[rt]=x;
		fa[rt]=f;
		if(tp==1) c1[rt]+=v;
		else c2[rt]+=v;
		pushup(rt);
		splay(rt);
		return;
	}
	if(x==val[rt]){
		if(tp==1) c1[rt]+=v;
		else c2[rt]+=v;
		pushup(rt);
		splay(rt);
		return;
	}
	if(x>val[rt]) inserts(R[rt],rt,x,tp,v);
	else inserts(L[rt],rt,x,tp,v);
	return;
}
inline void upd(int tp,int x,int v){
	inserts(rt,0,x,tp,v);
	return;
}
namespace IO{
	const int sz=1<<20;
	char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
	inline char gc(){
		return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
	}
	template<class T> inline void gi(T& x){
		int f=1;
		x=0; char c=gc();
		for(;c<'0'||c>'9';c=gc()) if(c=='-') f*=-1;
		for(;c>='0'&&c<='9';c=gc())
			x=x*10+(c-'0');
		x*=f;
		return;
	}
	inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
	inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
	template<class T> inline void pi(T x,char c='\n'){
		if(x==0) pc('0'); int t=0;
		if(x<0) pc('-'),x*=-1;
		for(;x;x/=10) p[++t]=x%10+'0';
		for(;t;--t) pc(p[t]); pc(c);
		return;
	}
	struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
struct my_set{
	int size;
	priority_queue<int> q,qd;
	inline void insert(int x){
		q.push(x);
		size++;
		return;
	}
	inline void erase(int x){
		qd.push(x);
		size--;
		return;
	}
	inline void clears(){
		while(!qd.empty()&&q.top()==qd.top()){
			q.pop();
			qd.pop();
		}
		return;
	}
	inline int top(){
		clears();
		return q.top();
	}
	inline void pop(){
		clears();
		q.pop();
		size--;
		return;
	}
}s;
signed main(){
//	freopen("tr.in","r",stdin);
//	freopen("tr.out","w",stdout);
// 	n=5e5,C=1073741823;
	gi(n),gi(C);
	for(int ans=0,op,x;n--;){
// 		op=1,x=rand()<<14|rand();
		gi(op),gi(x),x^=ans;
		x%=C;
		if(op==1){
			s.insert(x);
			upd(1,x,1);
			upd(2,C-x,1);
		}else{
			s.erase(x);
			upd(1,x,-1);
			upd(2,C-x,-1);
		}
		if(s.size<=1){
			pc('E'),pc('E'),pc('\n'),ans=0;
		}else{
			int x=s.top();s.pop();int y=s.top();
			s.insert(x);
			ans=max((x+y)%C,mx[rt]);
			pi(ans);
		}
	}
//	cerr<<cntt<<endl;
}
/*
4 114514
1 6673
1 15745
1 2589
2 15745
*/
```

---

## 作者：RainsAFO (赞：2)



按照传统先取模，然后分类讨论：

$1.$ $C  \leq(i + j) \leq 2 \times C$，取最大值 + 次大值就好了。

$2.$ $0 \leq (i + j) \leq C - 1$，那么答案在每个 $i$ 最优的 $j$ 取到。

考虑第二种情况。

一个比较 simple 的想法是维护每个 $i$ 的最优匹配 $j$（注意到这是单向的），用 $\text{multiset}$ 维护，但这样删除会被卡到 $O(|S|)$。

对上述做法进行优化，减小可能成为答案的集合。

本题关键在于，如果你要加入/删除一个数 $x1$，其最优匹配为 $x2$ ，需要用这两个数排除掉不优的决策。

这些决策一定至于 $x1,x2$ 相关，设 $x2$ 的最优匹配为 $x3$，若 $x1 > x3$，则 $(x2 , x3)$ 是无用的。

可以证明，保留的匹配个数是 $O(n)$ 级的。

也许会有这样的一个问题，如果删除产生了连锁反应怎么办？

注意到可能的决策集合变化大小始终不超过 $1$ ，而数集是不可重的，也就是说决策集合的元素用到的时候一定对应着数集的变化。

用两个 $\text{multiset}$ 分别维护数集与决策集合，实现有一些细节（注意 $\text{multiset}$ 的 count函数复杂度是错的）。

以下是代码实现，参考了 Owen_codeisking 的代码。

```cpp
#include <set>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

inline int read() {
	register char c = getchar();
	register int x = 0, f = 1;
	while(c < '0' || c > '9') {
		if (c == '-')
			f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

using namespace std;

int n , C;

multiset <int> s1 , s2;

// s1 : num , s2 : pair

multiset <int> ::iterator it;

inline int get_pair(int x , int o) {
	if(x == -1)
		return -1;
	it = s1.upper_bound(C - x - 1);
	if(it == s1.begin())
		return -1;
	--it;
	if(o == 1 && *it == x && s1.count(x) == 1) {
		if(it == s1.begin())
			return -1;
		return *--it;
	} else
		return *it;
}

int cnt = 0;

inline void insert(int x1) {
	cnt++;
	if(cnt == 1) {
		s1.insert(x1);
		return;
	}
	int x2 = get_pair(x1 , 0);
	int x3 = get_pair(x2 , 1);
	int x4 = get_pair(x3 , 1);
	if(x2 != -1 && x1 > x3) {
		if(x3 != -1 && x2 == x4)
			s2.erase(s2.find(x2 + x3));
		s2.insert(x1 + x2);
	}
	s1.insert(x1);
}

inline void erase(int x1) {
	cnt--;
	s1.erase(s1.find(x1));
	if(!cnt)
		return;int x2 = get_pair(x1 , 0);
	int x3 = get_pair(x2 , 1);
	int x4 = get_pair(x3 , 1);
	if(x2 != -1 && x1 > x3) {
		if(x3 != -1 && x2 == x4)
			s2.insert(x2 + x3);
		s2.erase(s2.find(x1 + x2));
	}
}

inline int query(){
	it = --s1.end();
	int num = *it;
	s1.erase(it);
	if(s1.find(num) != s1.end()){
		s1.insert(num);
		return num * 2 % C;
	}
//	if(s1.count(*it) >= 2)
//		return *it * 2 % C;
	else{
		s1.insert(num);
		it = --s1.end();
		return (*it + *--it) % C;
	}
}

int main() {
	n = read() , C = read();
	int lstans = 0;
	while(n--) {
		int opt = read() , x = (read() ^ lstans) % C;
		if(opt == 1)
			insert(x);
		else
			erase(x);
		if(cnt < 2){
			puts("EE");
			lstans = 0;
		}
		else{
			lstans = max(query() , s2.empty() ? 0 : *--s2.end());
			printf("%d\n" , lstans);
		}
	}
	return 0;
}
```




---

## 作者：happybob (赞：1)

以为 $C$ 不是常数想了半天想不出来。

正解应该很容易思考。先将插入的所有数对 $C$ 取模。一个容易的思考方向是如果固定了 $i$，$j$ 会怎么选。显然分类讨论，若 $i+j < C$，即 $j<C-i$ 时，$(i+j)\bmod C=i+j$，故 $j$ 应该选小于 $C-i$ 的最大值。若 $i+j \geq C$，$j$ 必然会取模 $C$ 意义下的最大值。所以对于结果的两个数 $(i,j)$，要么 $i,j$ 分别是集合内的最大和次大值，要么 $i+j \leq C$。

最大值和次大值是可以用 `set` 简单维护的。问题现在是 $i+j \leq C$ 的部分。观察最优解的性质。发现对于 $i$ 来讲，最优的必然是 $j$，同时对于 $j$ 来说最优的必然是 $i$，也就是说这个是双向的关系。考虑动态维护双向关系集合。加入一个数直接在 `set` 上做二分就能找到其对应的最优的数，判断是否为双向关系即可。删除同理。同时维护一个 `multiset` 表示所有双向关系的答案。总复杂度 $O(n \log n)$，应该可以无压力通过。

代码：


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <array>
#include <map>
#include <set>
using namespace std;

using ll = long long;

const int N = 5e5 + 5;

int n;
ll c, lst;
set<ll> st;
map<ll, int> cnt;
map<ll, int> mtc;
multiset<ll> ans;

inline ll qry(ll x)
{
	// x+y<c => y<c-x
	if (!st.size()) return -1ll;
	auto it = st.lower_bound(c - x);
	if (it == st.begin()) return -1ll;
	--it;
	if (*it == x)
	{
		if (it == st.begin()) return -1ll;
		--it;
	}
	return *it;
}

void ins(ll x)
{
	x %= c;
	if (cnt[x])
	{
		if (++cnt[x] == 2) ans.insert((x + x) % c);
		return;
	}
	cnt[x] = 1;
	ll y = qry(x);
	st.insert(x);
	if (y != -1 && qry(y) == x)
	{
		if (mtc.count(y))
		{
			ans.erase(ans.find((y + mtc[y]) % c));
			mtc.erase(mtc[y]);
		}
		mtc[x] = y, mtc[y] = x;
		ans.insert((x + y) % c);
	}
}

inline ll getmatch(ll x)
{
	ll y = qry(x);
	if (y == -1) return -1ll;
	if (qry(y) == x) return y;
	return -1ll;
}

void del(ll x)
{
	x %= c;
	if (cnt[x] >= 2)
	{
		if (--cnt[x] == 1) ans.erase(ans.find((x + x) % c));
		return;
	}
	cnt[x] = 0;
	if (mtc.count(x))
	{
		ans.erase(ans.find((x + mtc[x]) % c));
		ll y = mtc[x];
		if (mtc[y] != x) exit(-1);
		st.erase(x);
		ll g = getmatch(y);
		if (g != -1)
		{
			if (mtc.count(g))
			{
				ans.erase(ans.find((g + mtc[g]) % c));
				mtc.erase(g);
			}
			mtc[y] = g, mtc[g] = y;
			ans.insert((y + g) % c);
		}
		else if (g == -1) mtc.erase(y);
		mtc.erase(x);
	}
	else
	{
		st.erase(x);
	}
}

void query()
{
	ll res = -1ll;
	if (st.size() >= 2) res = (*(--st.end()) + *(--(--st.end()))) % c;
	if (ans.size()) res = max(res, *ans.rbegin());
	//cout << "Size: " << ans.size() << "\n";
	if (res == -1ll)
	{
		cout << "EE\n";
		lst = 0ll;
	}
	else
	{
		cout << (lst = res) << "\n";
	}
}

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> c;
	while (n--)
	{
		int op;
		ll x;
		cin >> op >> x;
		x ^= lst;
		//cout << "real: " << x << "\n";
		if (op == 1)
		{
			ins(x);
		}
		else del(x);
		query();
	}
	return 0;
}
```

---

## 作者：violin_wyl (赞：1)

# [Ynoi2010] y-fast trie

## 思路

考虑在插入所有元素的时候对 $C$ 取模。

那么可以分类讨论了：

- $0\leq x+y<C$
- $x+y\geq C$

考虑第二种情况等价于取集合中前两大的数，可以简单维护。

考虑第一种情况，对于一个数 $x$ 令 $f(x)$ 为小于 $C-1-x$ 的最大的数，那么就可以套路维护 $n$ 个元素对 $(x,f(x))$。那么在插入 $x$ 的时候可以平衡树找到 $f(x)$，问题变为小于某值的最大值。

而有些数的 $f(y)=x$，而这样的 $y$ 最劣情况下复杂度是 $\mathcal O(n)$ 的，这时候如果对集合中的每个数暴力重构 $f$​ 时间就错了。

我们设 $nxt_x$ 为 $x$ 的后继，考虑什么数可以让 $x$ 作为自己的 $f$，那么这些数必定小于等于 $C-1-x$，而如果这个数小到一定程度，那么就可以让 $nxt_x$ 作为自己的 $f$ 了，所以以 $x$ 为 $f$ 的数在数轴上应该在区间 $(C-1-nxt_x, C-1,x]$ 之间，那么这个操作等价于平衡树上的区间覆盖，可以单 $log$ 维护。

考虑删除操作，我们可以套路线段树分治把删除操作变为撤销操作，离线 $\mathcal O(n\log^2 n)$，~~那么这道题就做完了~~。

考虑强制在线，我们观察删除一个数 $x$ 的时候，哪些数 $f(y)=x$。设 $pre_x$ 为 $x$ 的前驱，那么本来以 $x$ 作为 $f$ 的数在区间 $(C-1-nxt_x, C-1,x]$ 中，但现在需要删除 $x$ ，而这些数又不能让 $nxt_x$ 作为自己的 $f$ ，所以需要让 $pre_x$  对区间 $(C-1-nxt_x,C-1-pre_x]$ 作一次区间覆盖。

#### 细节：

- $x$ 互不相同，但是 $x\bmod C$ 可能有重复的，因此需要开 `multiset`。
- $x$ 不能作为自己的 $f(x)$，但是如果 $x$ 有两个及以上则可以。这部分的解决方法是在插入的时候先更新 $f$ 再插入 $x$，删除的时候令 $pre_x,nxt_x=x$ 即可。

复杂度是 $\mathcal O(n\log n)$ 的，能不能 1s 过看使用的平衡树的常数，毕竟笔者由于 $5e5$ 的数据范围和~~本人优秀的写法~~ $fhq\_treap$ 的巨大常数，因此不得不让 lxl 把洛谷上的时限开到了 2s ~~还好有后台能改时限~~。

## code

```c++
#include <bits/stdc++.h>
#define mk make_pair
#define pb push_back
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
using namespace std;
const int N = 5e5 + 10;
const int INF = 0x3f3f3f3f;
typedef pair <int, int> pii;
char buf[1 << 23],*p1 = buf, *p2 = buf, obuf[1 << 23], *O = obuf;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
	int x = 0; char ch = getchar ();
	while (ch < '0' || ch > '9') { ch = getchar (); }
	while (ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = getchar ();
	return x;
}

void print(int x) {
    if(x > 9) print(x / 10);
    *O++ =x % 10 +'0';
}

int n, C, seed = 114514;
int root;
multiset <int> s;
set <int> :: iterator it, mx1;
inline int Rand() { return (seed = (seed << 21) + (seed >> 3)); }
inline int Max(int x, int y) { return (x > y) ? x : y; }
int node;
int x, y, z, Pre, Nxt;
struct node {
	int ls, rs;
	int key, siz, val;
	int cov, tag, mv, mx;
} t[N];
inline void pushup (int x)
{
	t[x].siz = t[t[x].ls].siz + t[t[x].rs].siz + 1;
	t[x].mv = Max (Max (t[t[x].ls].mv, t[t[x].rs].mv), t[x].val); // mv 是区间最大值
	t[x].mx = Max (Max (t[t[x].ls].mx, t[t[x].rs].mx), t[x].val + t[x].cov); // mx 是区间最大的 pair 值
}
#define Cov(now,v) 	t[now].tag = t[now].cov = (v), t[now].mx = (v) + t[now].mv;
inline void pushdown (int x)
{
	if (~t[x].tag)
	{
		if (t[x].ls) Cov (t[x].ls, t[x].tag);
		if (t[x].rs) Cov (t[x].rs, t[x].tag);
		t[x].tag = -1;
	}
}
inline int merge (int x, int y)
{
	if (!x || !y) return x + y;
	pushdown(x), pushdown(y);
	if (t[x].key < t[y].key) { t[x].rs = merge (t[x].rs, y); pushup (x); return x; }
	else { t[y].ls = merge (x, t[y].ls); pushup (y); return y; }
}
inline void split (int now, int k, int &x, int &y)
{
	if (!now) { x = y = 0; return ; }
	pushdown (now);
	if (t[now].val <= k) x = now, split (t[now].rs, k, t[x].rs, y);
	else y = now, split (t[now].ls, k, x, t[y].ls);
	pushup (now);
}
inline int new_node (register int v, register int v1)
{
	t[++node].siz = 1;
	t[node].key = Rand ();
	t[node].val = t[node].mv = v;
	t[node].tag = -1; t[node].cov = v1;
	t[node].mx = v + v1;
	return node;
}
inline void cover (register int l, register int r, register int c)
{
	split (root, l - 1, x, y);
	split (y, r, y, z);
	if(y) Cov(y, c);
	root = merge (merge (x, y), z);
}
inline void update (register int v)
{
	it = s.upb (C - 1 - v); it--;
	if (*it == v) it--;
	cover (v, v, *it);
}
inline void insert (int v, int v1)
{
	Nxt = *s.upb (v);
	if (Nxt != INF) cover (C - Nxt, C - 1 - v, v);
	else cover (0, C - 1 - v, v);  // 更新对应的 f
	split (root, v, x, y);
	root = merge (merge (x, new_node (v, v1)), y); // 插入 pair(x,f(x))
}
void del (register int v)
{
	split (root, v, x, z);
	split (x, v - 1, x, y);
	y = merge (t[y].ls, t[y].rs);
	root = merge (merge (x, y), z);
	it = s.lob (v); it--;
	Pre = *it, Nxt = *s.upb (Pre);
	if (~Pre) // 有前驱
	{
		if (Nxt != INF) cover (C - Nxt, C - 1 - Pre, Pre);
		else cover (0, C - 1 - Pre, Pre);
		update (Pre);  // 删除 x 有可能影响 f(pre)
	}
	else if (Nxt != INF) cover (C - Nxt, C - 1, -INF); // 没有前驱，那么这部分的数将没有 f
	if (Nxt != INF) update (Nxt); // 删除 x 有可能影响 f(nxt)
}
signed main ()
{
	n = read (), C = read (); s.insert(-INF); s.insert (INF);
	int lst = 0, op, x, tmp;
	root = new_node (-1, 0);
	while (n--)
	{ 
		op = read (), x = read () ^ lst;
		x -= x / C * C;
		if (op == 1)
		{
			it = s.upb (C - 1 - x); it--;
			s.insert (x);
			insert (x, *it);
		}
		else
		{
			s.erase (s.find(x));
			del (x);
		}
		if (s.size () <= 3) *O++='E',*O++='E',*O++='\n', lst = 0;
		else 
		{
			mx1 = s.end(); --mx1;
			tmp = *--mx1; tmp += *--mx1;
			if (tmp >= C) tmp -= C;
			print(lst = Max (t[root].mx, tmp));
			*O++='\n';
		}
	}
	fwrite(obuf,O-obuf,1,stdout); // 卡常快写，这部分可以直接掠过
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

自己做的时候漏了条重要性质……                   

首先我们知道，我们把 $x$ 都模上 $C$ 后得到的答案没有变化，由于只有两个数，所以两数之和肯定都在 $0 \sim 2 \times C - 2$ 之间，那么我们分类讨论一下：        

1. 两数之和大于等于 $C$ 。显然对于这种情况我们取集合里最大的两个数，随便维护；              

2. 两数之和小于 $C$ 。对于这种情况我们维护每个数在当前集合内的一个最优匹配，在这里定义一个数 $x$ 的最优匹配是集合中在 $[0 , C - x - 1]$ 中最大的数，最后我们的答案肯定是所有的数的最优匹配得到的结果取最大值。                 

我们将重点放在第二种情况上面，显然直接维护所有数的最优匹配是很不现实的，考虑缩小答案范围。                   

我们尝试运用一些题目特有的性质解决这个问题：            

1. 答案一定是一个这样形式的匹配贡献的值：$(a,b)$ 并且 $a$ 的最优匹配是 $b$ ，且 $b$ 的最优匹配是 $a$ 。                 

这里很好证明，我们运用反证法。如果答案不是一个这样的匹配贡献出来的值，那么 $(a , b)$ 中至少有一个数的最优匹配不是另一个数，所以找到这个数凑成的匹配得到的值一定比当前情况下的值更优，矛盾，结论得证。               

很多题解也没写到这步，也是我忽略的一条重要性质。（                        

有了这条性质后后面的东西就简简单单了。                   

2. 如果一个数 $x$ 的最优匹配是 $y$ ，$y$ 的最优匹配是 $z$ ，并且 $x < z$ 那我们就可以在考虑答案时只 $(y , z)$ 这个匹配。                      

这个比较显然，毕竟现在的两数之和都小于 $C$ ，$x + y < y + z$ 所以肯定只考虑 $(y , z)$ 这个匹配就好了。                

由于这个性质对所有在满足两数之和小于 $C$ 的匹配都适用，那么肯定也对性质 $1$ 的特殊匹配也适用，所以我们考虑维护所有的性质 $1$ 中提到的特殊匹配，很显然这些匹配的数量级始终控制在 $O(\frac{n}{2})$ 左右，比起最开始的 $O(n ^ 2)$ 不知 NB 了多少。

而且我们发现这么一挖掘，我们在插入和删除时只用考虑再增加减少各一个匹配就好了，所有操作的时间复杂度也得到保证，这道题就做完了。                  

总的时间复杂度为 $O(n \log n)$ ，但是由于寻找每个点的最优匹配常数比较大就有点卡了。


本来啊这东西写个平衡树啥的都好……虽然有点难码但是毕竟细节少，可是 Ynoi 还是得卡常，于是用 multiset 就细节多的一批还难调……建议实在调不动的朋友们看一下第一篇题解的实现。                


---

## 作者：miaow (赞：1)

这题思路挺简单的，就是代码写着有点麻烦 ~~也可能是我太菜了~~

### 题解

首先很明显的，读进来的数字先$mod C$再操作对答案没有影响，这时候两个数相加是$<2C$的

然后分类讨论，一类是相加$≥C$的，这类就是直接取集合内最大的两个数相加即可（即使和比$C$小也无所谓）

对于和$<C$的，先把集合$S$内数字排成有序的（可以用$set$），然后每一个数字$x$维护与其相加最接近$C$的数字$y$，称为$y$是$x$的最佳匹配

具体来讲，对于每一个数字$y$用平衡树维护一个集合$S_{y}$，集合内存放最佳匹配是$y$的所有$x$，并设$S$中比$x$小的最大数字为$z$。在加入一个新的$x$时，将$x$放入$S_{y}$中，并将$S_{z}$中与$x$的和小于$C$的部分从$S_{z}$中取出放入$S_{x}$中。删除一个$x$时把$x$从$S_{y}$中删去，并将$S_{x}$并入$S_{z}$中。由于$S_{x}$中最大值必定比$S_{z}$中最小值要小，所以可以快速进行这些操作。再使用一个$set$储存每一个$y$与$S_{y}$中最大值的和，在每个$S_{y}$进行操作时动态维护这个$set$，这个$set$中的最大值即为和$<C$情况下的答案

有一个小细节就是数字不能重复取用，所以当$x$只加入了一次且其最佳匹配是其自身时，需要把$x$加入$S_{z}$中而不是$S_{x}$，当再次加入$x$时再把其取回来，其他相关的操作也要特判这种情况

每一次操作都操作了常数次的$set$和平衡树，总的复杂度是$O(nlogn)$的，空间复杂度是线性。

~~我用了两个set还用了一个splay为什么我的代码跑的这么快，完全没遇到过卡常~~

### 代码

很多地方可以写成函数来减少码量的，但是我懒得改了（于是就有了这个又臭又长的代码

~~理解思路就好代码不重要（雾~~

```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#include<set>
using namespace std;
const int N=5e5+5,M=1e5,INF=1073741824;
inline int read()
{
	int sum=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')
	{
		sum=sum*10+c-'0';
		c=getchar();
	}
	return sum;
}
inline void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
}

int n,m,c;
struct meow
{
	int sz;
	mutable int cs,root;
	inline bool operator < (const meow& qwe) const
	{
		return sz>qwe.sz;
	}
	meow(int sz=-INF,int cs=0,int root=0):sz(sz),cs(cs),root(root){}
};
set<meow> a;
#define smi set<meow>::iterator
set<meow> ans;

struct miaow
{
	int son[2],fa,sz;
	miaow(int ls=0,int rs=0,int fa=0,int sz=0):fa(fa),sz(sz)
	{
		son[0]=ls,son[1]=rs;
	}
}t[N];
int cou=1;
#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define son(x,k) t[x].son[k]
#define fa(x) t[x].fa
#define sz(x) t[x].sz
inline int fx(int x)
{
	if(!fa(x))return -1;
	return rs(fa(x))==x;
}
inline void rt(int x)
{
	if(!fa(x))return;
	int y=fa(x),k=fx(x);
	if(fa(y))
	{
		son(fa(y),fx(y))=x;
	}
	fa(x)=fa(y);
	fa(y)=x;
	if(son(x,k^1))
	{
		fa(son(x,k^1))=y;
	}
	son(y,k)=son(x,k^1);
	son(x,k^1)=y;
}
inline void splay(int x,int md=0)
{
	int y=fa(x);
	while(y&&y!=md)
	{
		int z=fa(y);
		if(!z||z==md)
		{
			rt(x);
			return;
		}
		if(fx(y)==fx(x))rt(y);
		else rt(x);
		rt(x);
		y=fa(x);
	}
}

inline int findl(int x,int y)
{
	int o=x,fo=0;
	if(!o)return fo;
	while(1)
	{
		if(y==sz(o))
		{
			fo=o;
			break;
		}
		if(y>sz(o))
		{
			fo=o;
			if(!rs(o))break;
			o=rs(o);
		}
		else
		{
			if(!ls(o))break;
			o=ls(o);
		}
	}
	return fo;
}
inline int find(int x,int y)
{
	int o=x;
	if(!o)return o;
	while(1)
	{
		if(y==sz(o))break;
		else if(y>sz(o))
		{
			if(!rs(o))break;
			o=rs(o);
		}
		else
		{
			if(!ls(o))break;
			o=ls(o);
		}
	}
	return o;
}

inline void ansadd(int x)
{
	meow qwe=meow(x,1,0);
	smi o=ans.find(qwe);
	if(o==ans.end())
	{
		ans.insert(qwe);
	}
	else
	{
		o->cs+=1;
	}
}
inline void ansdel(int x)
{
	meow qwe=meow(x,1,0);
	smi o=ans.find(qwe);
	o->cs-=1;
	if(!o->cs)
	{
		ans.erase(o);
	}
}

inline void ins(smi o,int x)
{
	int zxc=find(o->root,x);
	if(!zxc)
	{
		t[cou]=miaow(0,0,0,x);
		o->root=cou;
		ansadd(o->sz+sz(cou));
		++cou;
	}
	else
	{
		t[cou]=miaow(0,0,zxc,x);
		if(sz(zxc)<x)rs(zxc)=cou;
		else ls(zxc)=cou;
		splay(cou);
		if(!rs(cou))
		{
			while(rs(zxc))zxc=rs(zxc);
			ansdel(o->sz+sz(zxc));
			ansadd(o->sz+sz(cou));
		}
		o->root=cou;
		++cou;
	}
}
inline void era(smi o,int x)
{
	int zxc=find(o->root,x);
	splay(zxc);
	if(!ls(zxc))
	{
		if(!rs(zxc))
		{
			o->root=0;
			ansdel(o->sz+sz(zxc));
		}
		else
		{
			int qwe=rs(zxc);
			while(ls(qwe))qwe=ls(qwe);
			splay(qwe);
			splay(zxc,qwe);
			fa(zxc)=0;
			ls(qwe)=0;
			o->root=qwe;
		}
	}
	else
	{
		if(!rs(zxc))
		{
			int qwe=ls(zxc);
			while(rs(qwe))qwe=rs(qwe);
			splay(qwe);
			splay(zxc,qwe);
			fa(zxc)=0;
			rs(qwe)=0;
			o->root=qwe;
			ansdel(o->sz+sz(zxc));
			ansadd(o->sz+sz(qwe));
		}
		else
		{
			int qwe=ls(zxc),asd=rs(zxc);
			while(rs(qwe))qwe=rs(qwe);
			while(ls(asd))asd=ls(asd);
			splay(qwe);
			splay(asd,qwe);
			fa(zxc)=0;
			ls(asd)=0;
			o->root=qwe;
		}
	}
}

inline void add(int x)
{
	meow qwe=meow(x,0,0);
	smi o=a.find(qwe),o2;
	if(o==a.end())
	{
		qwe.cs=1;
		o=a.insert(qwe).first;
		o2=o++;
		int asd=findl(o->root,c-x-1);
		if(asd)
		{
			splay(asd);
			if(!rs(asd))
			{
				o->root=0;
				ansdel(o->sz+sz(asd));
				o2->root=asd;
				ansadd(o2->sz+sz(asd));
			}
			else
			{
				int zxc=rs(asd);
				while(ls(zxc))zxc=ls(zxc);
				splay(zxc);
				splay(asd,zxc);
				fa(asd)=0,ls(zxc)=0;
				o->root=zxc;
				o2->root=asd;
				ansadd(o2->sz+sz(asd));
			}
		}
		if(o->cs==1)
		{
			smi o3=a.lower_bound(meow(c-o->sz-1,0,0));
			if(o3==o2)
			{
				smi o4=o;
				++o4;
				era(o4,o->sz);
				ins(o3,o->sz);
			}
		}
		
		
		smi o3=a.lower_bound(meow(c-x-1,0,0));
		if(o3==o2)++o3;
		ins(o3,x);
	}
	else if(o->cs==1)
	{
		o->cs+=1;
		smi o3=a.lower_bound(meow(c-x-1,0,0));
		if(o3==o)
		{
			++o3;
			era(o3,x);
			ins(o,x);
		}
	}
	else
	{
		o->cs+=1;
	}
}
inline void del(int x)
{
	meow qwe=meow(x,0,0);
	smi o=a.find(qwe),o2;
	if(o->cs>=3)
	{
		o->cs-=1;
	}
	else if(o->cs==2)
	{
		o->cs-=1;
		smi o3=a.lower_bound(meow(c-x-1,0,0));
		if(o3==o)
		{
			++o3;
			era(o,x);
			ins(o3,x);
		}
	}
	else
	{
		o2=o++;
		if(o2->root)
		{
			if(o->root)
			{
				int asd=o->root,zxc=o2->root;
				while(ls(asd))asd=ls(asd);
				while(rs(zxc))zxc=rs(zxc);
				splay(asd);
				splay(zxc);
				ls(asd)=zxc;
				fa(zxc)=asd;
				o2->root=0;
				o->root=asd;
				ansdel(o2->sz+sz(zxc));
			}
			else
			{
				int asd=o2->root;
				while(rs(asd))asd=rs(asd);
				splay(asd);
				o->root=asd;
				o2->root=0;
				ansdel(o2->sz+sz(asd));
				ansadd(o->sz+sz(asd));
			}
			smi o3=a.lower_bound(meow(c-o->sz-1,0,0));
			if(o3==o2&&o->cs==1)
			{
				int ss=o->sz;
				era(o,ss);
				++o;
				ins(o,ss);
			}
		}
		smi o3=a.lower_bound(meow(c-x-1,0,0));
		if(o3==o2)++o3;
		era(o3,x);
		a.erase(o2);
	}
}
inline void solve()
{
	n=read(),c=read();
	int lastans=0,cou=0;
	a.insert(meow());
	for(int i=1;i<=n;++i)
	{
		int x=read(),y=(read()^lastans)%c;
		if(x==1)
		{
			add(y);
			cou+=1;
		}
		else
		{
			del(y);
			cou-=1;
		}
		if(cou<2)
		{
			puts("EE");
			lastans=0;
		}
		else
		{
			int imax,imax2;
			smi qwe=ans.begin();
			imax=qwe->sz;
			qwe=a.begin();
			if(qwe->cs>=2)imax2=qwe->sz*2;
			else
			{
				imax2=qwe->sz;
				++qwe;
				imax2+=qwe->sz;
			}
			lastans=max(imax,imax2%c);
			write(lastans),putchar('\n');
		}
	}
}
int main()
{
	solve();
}
```


---

