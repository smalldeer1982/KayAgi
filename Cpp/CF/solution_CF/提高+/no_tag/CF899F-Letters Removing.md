# Letters Removing

## 题目描述

Petya has a string of length $ n $ consisting of small and large English letters and digits.

He performs $ m $ operations. Each operation is described with two integers $ l $ and $ r $ and a character $ c $ : Petya removes from the string all characters $ c $ on positions between $ l $ and $ r $ , inclusive. It's obvious that the length of the string remains the same or decreases after each operation.

Find how the string will look like after Petya performs all $ m $ operations.

## 说明/提示

In the first example during the first operation both letters 'a' are removed, so the string becomes "bc". During the second operation the letter 'c' (on the second position) is removed, and the string becomes "b".

In the second example during the first operation Petya removes '0' from the second position. After that the string becomes "Az". During the second operations the string doesn't change.

## 样例 #1

### 输入

```
4 2
abac
1 3 a
2 2 c
```

### 输出

```
b
```

## 样例 #2

### 输入

```
3 2
A0z
1 3 0
1 1 z
```

### 输出

```
Az
```

## 样例 #3

### 输入

```
10 4
agtFrgF4aF
2 5 g
4 9 F
1 5 4
1 7 a
```

### 输出

```
tFrg4
```

## 样例 #4

### 输入

```
9 5
aAAaBBccD
1 4 a
5 6 c
2 3 B
4 4 D
2 3 A
```

### 输出

```
AB
```

# 题解

## 作者：scp020 (赞：7)

# CF899F Letters Removing 题解

这好像是个典题。

## 解法

一个很自然的想法。

考虑开 $62$ 颗平衡树，即每一种字符都开一颗平衡树，维护的是每种字符出现的位置，每次操作就把对应的平衡树区间删去即可，是很基础的非旋 treap 操作。

实现就是按值分裂。

```cpp
inline std::pair<fhq_node *,fhq_node *> split(fhq_node *rt,const int k)
{
	std::pair<fhq_node *,fhq_node *> ret;
	if(rt==nullptr) return std::make_pair(nullptr,nullptr);
	if(k<rt->val) ret=split(rt->lc,k),rt->lc=ret.second,rt->pushup(),ret.second=rt;
	else ret=split(rt->rc,k),rt->rc=ret.first,rt->pushup(),ret.first=rt;
	return ret;
}
```

当我搓完平衡树后发现过不了样例，仔细看样例才发现，字符的标号是随着删除操作而变化的。所以我们需要动态的维护每个数的标号，这也是很典的问题。考虑用一个树状数组，初始值都是 $1$，表示所有字符都没有被删除，之后每删除一个字符，我们就在树状数组的对应位置减 $1$，树状数组中第 $k$ 大的数的位置就是删除后的第 $k$ 个字符在原序列中的位置。最朴素的想法就是在树状数组上二分。

当然，有比树状数组上二分复杂度更优的做法，就是树状数组上倍增。

注意到树状数组上的节点 $c_i$ 表示 $\sum \limits _{j=i-\operatorname{lowbit}(i)+1}^i a_j$，所以我们从高位向低位枚举答案的每个二进制位即可。

```cpp
inline int kth(int k)
{
	int sum=0,ret=0;
	for(int i=lgn;i>=0;i--)
	{
		ret+=1<<i;
		if(ret>=n || sum+c[ret]>=k) ret-=1<<i;
		else sum+=c[ret];
	}
	return ret+1;
}
```

时间复杂度：$\mathcal{O}(n \log n)$，即树状数组初始化、平衡树区间删除、树状数组获取第 $k$ 小值、树状数组单点修改的复杂度。

## 代码

```cpp
#include<bits/stdc++.h>
namespace fast_IO
{
	/**
	 * 快读快写
	*/
};
using namespace fast_IO;
int n,m;
char ans[200010],now;
class BIT
{
	#define N 200010
private:
	int c[N],lgn;
	inline int lowbit(const int &x)
	{
		return x&(-x);
	}
public:
	inline void init()
	{
		lgn=log2(n);
	}
	inline void fix(int pos,int x)
	{
		while(pos<=n) c[pos]+=x,pos+=lowbit(pos);
	}
	inline int kth(int k)
	{
		int sum=0,ret=0;
		for(int i=lgn;i>=0;i--)
		{
			ret+=1<<i;
			if(ret>=n || sum+c[ret]>=k) ret-=1<<i;
			else sum+=c[ret];
		}
		return ret+1;
	}
};
BIT fenwik_tree;
template<typename T>
inline void swap(T &_x,T &_y)
{
	T tmp=_x;
	_x=_y,_y=tmp;
}
struct fhq_node
{
	int val,w,siz;
	fhq_node *lc,*rc;
	inline fhq_node(int val)
	{
		this->val=val,w=rand(),siz=1,lc=rc=nullptr;
	}
	inline void pushup()
	{
		siz=(lc==nullptr?0:lc->siz)+(rc==nullptr?0:rc->siz)+1;
	}
};
class fhq_treap
{
	#define ls l,mid-1
	#define rs mid+1,r
private:
	fhq_node *root;
	std::vector<int> v;
	inline fhq_node *merge(fhq_node *l,fhq_node *r)
	{
		if(l==nullptr && r==nullptr) return nullptr;
		if(l==nullptr) return r;
		if(r==nullptr) return l;
		if(l->w<r->w)
		{
			l->rc=merge(l->rc,r),l->pushup();
			return l;
		}else
		{
			r->lc=merge(l,r->lc),r->pushup();
			return r;
		}
	}
	inline std::pair<fhq_node *,fhq_node *> split(fhq_node *rt,const int k)
	{
		std::pair<fhq_node *,fhq_node *> ret;
		if(rt==nullptr) return std::make_pair(nullptr,nullptr);
		if(k<rt->val) ret=split(rt->lc,k),rt->lc=ret.second,rt->pushup(),ret.second=rt;
		else ret=split(rt->rc,k),rt->rc=ret.first,rt->pushup(),ret.first=rt;
		return ret;
	}
	inline fhq_node *build(int l,int r)
	{
		if(l>r) return nullptr;
		if(l==r) return new fhq_node(v[l-1]);
		int mid=(l+r)/2;
		fhq_node *rt=new fhq_node(v[mid-1]);
		rt->lc=build(ls),rt->rc=build(rs);
		rt->pushup();
		return rt;
	}
	inline void print(fhq_node *rt)
	{
		if(rt==nullptr) return;
		if(rt->lc!=nullptr) print(rt->lc);
		ans[rt->val]=now;
		if(rt->rc!=nullptr) print(rt->rc);
	}
	inline void del(fhq_node *rt)
	{
		if(rt==nullptr) return;
		if(rt->lc!=nullptr) del(rt->lc);
		fenwik_tree.fix(rt->val,-1);
		if(rt->rc!=nullptr) del(rt->rc);
		delete rt;
	}
public:
	inline void push_back(const int x)
	{
		v.push_back(x);
	}
	inline void build()
	{
		root=build(1,(int)v.size());
	}
	inline void del(const int L,const int R)
	{
		std::pair<fhq_node *,fhq_node *> a,b;
		a=split(root,R),b=split(a.first,L-1),del(b.second);
		root=merge(b.first,a.second);
	}
	inline void print()
	{
		print(root);
	}
};
fhq_treap tree[70];
std::unordered_map<char,int> mp;
std::unordered_map<int,char> imp;
char ch;
int main()
{
	srand(time(0));
	for(int i=1;i<=26;i++) mp['a'+i-1]=i,imp[i]='a'+i-1;
	for(int i=27;i<=52;i++) mp['A'+i-27]=i,imp[i]='A'+i-27;
	for(int i=53;i<=62;i++) mp['0'+i-53]=i,imp[i]='0'+i-53;
	in>>n>>m,fenwik_tree.init();
	for(int i=1;i<=n;i++) in>>ch,tree[mp[ch]].push_back(i),fenwik_tree.fix(i,1);
	for(int i=1;i<=62;i++) tree[i].build();
	for(int i=1,x,y;i<=m;i++)
	{
		in>>x>>y>>ch;
		x=fenwik_tree.kth(x),y=fenwik_tree.kth(y);
		tree[mp[ch]].del(x,y);
	}
	for(int i=1;i<=62;i++) now=imp[i],tree[i].print();
	for(int i=1;i<=n;i++) if(ans[i]) out<<ans[i];
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```

---

## 作者：封禁用户 (赞：5)

咦？题解怎么全是线段树？
~~（本蒟蒻太菜了不会线段树）~~

我就来发一个不用线段树的题解。

先开62（10+26+26）个set维护每个字符的位置，再开一个树状数组维护从1到i被删了几个点，删除前可以先通过二分求出给出的位置在原字符串的位置，然后在set中二分出那个区间，每次删除只要在set中erase并且在树状数组那个下标+1即可。

code:

```
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int get(char c)
{
	if(c>='0'&&c<='9')
		return c-'0';
	if(c>='A'&&c<='Z')
		return c-'A'+10;
	return c-'a'+36;
}
set<int>d[62];
int bit[N];
int del[N];
void ins(int x)
{
	for(;x<N;x+=x&-x)
		bit[x]++;
} 
int qq(int x)
{
	int res=0;
	for(;x;x-=x&-x)
		res+=bit[x];
	return res; 
}
int get_pos(int x)
{
	int ll=x,rr=N-1;
	while(ll<rr)
	{
		int mm=(ll+rr)/2;
		if(mm-qq(mm)>=x)
			rr=mm;
		else
			ll=mm+1;
	}
	return ll;
}
char s[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	scanf("%s",s);
	for(int i=0;i<n;i++)
		d[get(s[i])].insert(i+1);
	for(int cs=0;cs<m;cs++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		char c[4];
		scanf("%s",c);
		int id=get(c[0]);
		x=get_pos(x);
		y=get_pos(y);
		auto it=d[id].lower_bound(x);
		auto it2=it;
		while(it2!=d[id].end()&&*it2<=y)
		{
			del[*it2]=1;
			ins(*it2);
			it2++;	
		}
		d[id].erase(it,it2);
	}
	for(int i=1;i<=n;i++)
		if(!del[i])
			putchar(s[i-1]);
	puts("");
	return 0;
}

```

---

## 作者：shinkuu (赞：4)

题解区用树状数组和二分的不少，但全都是两只 $\log$ 的。真的有人会写一个 $\log^2$ 的解法而不直接单 $\log$ 吗。

### 树状数组上二分

你是否有这样的烦恼：有时需要用到线段树上二分，但是又会遇到常数过大的情况。想用树状数组，但是又只会 $\log^2$。这时就可以利用**树状数组上二分**的方法。

众所周知，树状数组每个点 $x$ 权值即为区间 $(x-\operatorname{lowbit}(x),x]$ 这一整段的和，相当于是一段长为 $2^k$ 的区间的和。看到这个，我们就很容易想到一个熟悉的算法：倍增。

我们可以尝试从更大的 $2^k$ 开始尝试，设当前序列上位置为 $p$，$[1,p]$ 和为 $s$，要找的数为 $x$，因为我们是从高位往低位加，所以 $<k$ 的所有位上现在都为 $0$，也就是说，$\operatorname{lowbit}(p+2^k)=2^k$。所以，$tr_{p+2^k}$ 即为 $(p,p+2^k]$ 这一段的和。

与倍增思想一样，若 $s+tr_{p+2^k}<x$，则 $p\leftarrow p+2^k,s\leftarrow s+tr_{p+2^k}$。最后 $x$ 所在位置即为 $p+1$。

回到这道题，还是和常规做法一样，用 set 维护每个字符在哪里出现，并用树状数组维护当前序列 $x$ 位置相当于原数列的哪个位置。

跑得飞快。没卡常最优解第二。

code：

```cpp
int n,m,pw[23];
char ans[N],s[N];
set<int> st[307];
#define lowbit(x) (x&(-x))
int tr[N];
inline void update(int x,int y){
	while(x<=n){
		tr[x]+=y;
		x+=lowbit(x);
	}
}
inline int query(int x){
	int ret=0,cnt=0;
	drep(i,18,0){
		if(ret+pw[i]<=n&&cnt+tr[ret+pw[i]]<x)
			cnt+=tr[ret+=pw[i]];
	}
	return ret+1;
}
void Yorushika(){
	scanf("%d%d%s",&n,&m,s+1);
	rep(i,1,n){
		st[s[i]].insert(i);
		update(i,1);
	}
	pw[0]=1;
	rep(i,1,20){
		pw[i]=pw[i-1]*2;
	}
	rep(i,1,m){
		int l,r;
		char op[7];
		scanf("%d%d%s",&l,&r,op);
		l=query(l),r=query(r);
		auto x=st[op[0]].lower_bound(l),y=st[op[0]].upper_bound(r);
		for(auto j=x;j!=y;j++){
			update(*j,-1);
		}
		if(x!=y)
			st[op[0]].erase(x,y);
	}
	rep(i,1,300){
		for(int j:st[i]){
			ans[j]=i;
		}
	}
	rep(i,1,n){
		if(ans[i])
			printf("%c",ans[i]);
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：__Floze3__ (赞：1)

## 思路简述

看到数据范围是 $2 \times 10 ^ 5$，考虑分块。

我们对每个块开一个桶，存储每种字符在这个块内的出现次数，同时维护每个块实际对应的字符串长。同时我们用一个 bool 数组维护每个位置有没有被删除。但我们判断一个字符是否被删除，需要判断这个位置有没有在 bool 数组内被记录删除，以及这个块内有没有这个字符出现，因为我们会对一个块内的字符做集体删除。因此，对于一次修改，我们可以遍历每个块，单独处理 $l$ 所在的块，$r$ 所在的块，同时直接通过桶来维护这两个块之间的块。注意要特判 $l$、$r$ 在同一块内的情况。时间复杂度为 $O(m\sqrt{n})$。

## 完整代码

[提交记录](https://codeforces.com/contest/899/submission/264698631)

---

## 作者：FZzzz (赞：1)

这题作为黑题是简单了点，思考过程还是很妙的，写篇题解纪念一下。

首先我们发现，这题只有删除操作。

那其实我们的重点完全不在如何维护删除，因为每个点最多被删一次，我们完全可以暴力单点删除，不需要多余的技巧去维护，只要单点删除复杂度是对的，均摊下来复杂度就是对的。

那么我们就把重心放在如何找出该被删的数。

有一个很暴力的想法是直接去存每一个字符的所有出现位置，那我们用 `set` 维护，就可以做到均摊一个 $\log$。

但是这题的下标是会有变化的，我们需要根据给出的下标找出原序列下标。我们可以把所有未被删除的点塞进一个平衡树里，然后就只需要支持第 $k$ 大查询即可。这题权值线段树比任何一种平衡树都好写很多，所以我使用权值线段树。

这样这题就做完了，总时间复杂度 $O(n\log n)$

代码：
```cpp
#include<set>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=2e5+5;
int n,m;
char s[maxn];
set<int> ss[70];
inline int hash(char c){
	if(islower(c)) return c-'a';
	else if(isupper(c)) return 26+c-'A';
	else return 52+c-'0';
}

inline char readchar(){
	char c=getchar();
	while(isspace(c)) c=getchar();
	return c;
}
struct node{
	int l,r;
	node* ch[2];
	int sum;
	void pushup(){
		sum=ch[0]->sum+ch[1]->sum;
	}
	node(int l,int r):l(l),r(r){
		if(l<r){
			int mid=l+(r-l)/2;
			ch[0]=new node(l,mid);
			ch[1]=new node(mid+1,r);
			pushup();
		}
		else{
			sum=1;
			ch[0]=ch[1]=0;
		}
	}
	void remove(int x){
		if(l==r) sum=0;
		else{
			if(x<=ch[0]->r) ch[0]->remove(x);
			else ch[1]->remove(x);
			pushup();
		}
	}
	int kth(int k){
		if(l==r) return r;
		else{
			if(k<=ch[0]->sum) return ch[0]->kth(k);
			else return ch[1]->kth(k-ch[0]->sum);
		}
	}
	void out(){
		if(l==r){
			if(sum==1) printf("%c",s[r]);
		}
		else{
			ch[0]->out();
			ch[1]->out();
		}
	}
}*rt;
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    m=readint();
    scanf("%s",s+1);
    for(int i=1;i<=n;i++) ss[hash(s[i])].insert(i);
    rt=new node(1,n);
    while(m--){
    	int l,r,c;
    	l=rt->kth(readint());
    	r=rt->kth(readint());
    	c=hash(readchar());
    	set<int>::iterator itl=ss[c].lower_bound(l),itr=ss[c].upper_bound(r);
    	for(set<int>::iterator i=itl;i!=itr;i++) rt->remove(*i);
		ss[c].erase(itl,itr);
	}
	rt->out();
	printf("\n");
    return 0;
}
```


---

## 作者：lnwhl (赞：0)

## $\text{Description}$
长度为 $n$ 的串，$m$ 次操作，删除一段区间内的所有为 $c$ 的字符，输出删除完毕后的字符串。注意这个区间是指进行完之前的删除操作之后的字符串上的区间。
## $\text{Solution}$
发现只有删除一种操作，我们其实只需要找到每次删除哪些字符即可。

考虑对每一种字符开一个 `set`，总共开 $10+26+26=62$ 个 `set`，然后每次删除对应 `set` 中区间内的元素即可。

但是怎么知道每个元素在进行了之前的删除操作后的位置呢？考虑使用树状数组维护。初始对于每一个位置都 $+1$，删除就将对应位置 $-1$。那么怎么确定给定区间在原序列上对应的区间呢？可以在[树状数组上倍增](https://www.cnblogs.com/lnwhl/p/17091331.html)。

这样这道题就做完了，最后遍历一下每个 `set` 找到没有被删除的元素输出即可。

总的复杂度应该是 $\mathcal O(n\log n)$，当然如果您不会树状数组上倍增求第 $k$ 小元素的话，也可以在树状数组上进行二分，复杂度是 $\mathcal O(n\log^2n)$ 的，同样可以通过。也可以看看我写的[这篇博客](https://www.cnblogs.com/lnwhl/p/17091331.html)。
## $\text{Code}$
```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define il inline
using namespace std;
const int N=2e5+5;
int n,m,b[N];
set<int>st[65];
map<int,char>mp;
il int cg(char ch)//将字符转成下标 
{
	if(ch>='a'&&ch<='z')return ch-'a';
	if(ch>='A'&&ch<='Z')return ch-'A'+26;
	return ch-'0'+52;
}
il char dec(int x)//将下标转成字符 
{
	if(x<=25)return 'a'+x;
	if(x<=51)return 'A'+x-26;
	return '0'+x-52;
}
il int lb(int x){return x&-x;}
il void add(int x,int y){while(x<=n)b[x]+=y,x+=lb(x);}
il int query(int x){int res=0;while(x)res+=b[x],x-=lb(x);return res;}
il int get_pos(int k)//bit上倍增 
{
	int l=0,tot=0,x,y;
	for(int i=20;i>=0;--i)
	{
		x=l+(1<<i);
		if(x>n)continue;
		y=tot+b[x];
		if(y<k)l=x,tot=y;
	}
	return l+1;
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		char ch;cin>>ch;add(i,1);
		st[cg(ch)].insert(i);
	}
	while(m--)
	{
		int l,r,c;char ch;cin>>l>>r>>ch;
		l=get_pos(l),r=get_pos(r);c=cg(ch);
		for(auto it=st[c].lower_bound(l);it!=st[c].end();)
		{
			if(*it>r||st[c].empty())break;
			add(*it,-1);it=st[c].erase(it);
			/*更新树状数组，迭代器++*/ 
		}
	}
	for(int i=0;i<=61;++i)//遍历62个set找到没被删除的元素 
		for(auto it=st[i].begin();it!=st[i].end();++it)
			mp[*it]=dec(i);
	for(auto it=mp.begin();it!=mp.end();++it)cout<<it->second;
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

之前学校做过这道题，今天突然看到了，来写一篇题解。

# 题目大意

长度为 $n$ 的串，$m$ 次操作，删除一段区间内的所有为 $c$ 的字符，输出删除完毕后的字符串。

# 题目分析

因为只有小写字母、大写字母和数字，所以可以开 $62$ 棵 `set` 来维护每个字母的位置，然后如果删除后没有合并操作的话，直接标记一下就可以了。

但是这道题删除后会合并，那么也就代表下标可能会变化。

因此，我们可以用树状数组来维护 $1\sim i$ 删除的字符个数。删除前先二分求出询问给出的区间左右端点在原字符串中的位置 $posl,posr$，假设要删除的字符为 $ch$，然后再在 $ch$ 的 `set` 中二分找到大于等于 $posl$ 的下标，再暴力遍历 `set` 删除即可。

# 代码

```cpp
//2022/2/20
//2022/3/6
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#include <set>
#define enter() putchar(10)
#define debug(c,que) cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) cout << arr[i] << w;
#define speed_up() cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
const int mod = 1e9 + 7;
inline int MOD(int x) {
	while (x < 0) x += mod;
	while (x >= mod) x -= mod;
	return x;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;
using namespace std;

const int ma = 2e5 + 5,MA = 63;
char str[ma];
bool del[ma];
set<int>st[MA];
int n,m;
inline int getid(char ch) {
	if (ch >= '0' && ch <= '9') return (int)(ch - '0');
	if (ch >= 'a' && ch <= 'z') return (int)(ch - 'a') + 10;
	return (int)(ch - 'A') + 10 + 26;
}
struct BIT {
	int tr[ma];
	#define lowbit(x) (x & -x)
	inline void update(int x,int k) {
		for (;x < ma;x += lowbit(x)) {
			tr[x] += k;
		}
	}
	inline int query(int x) {
		int res = 0;
		for (;x;x -= lowbit(x)) {
			res += tr[x];
		}
		return res;
	}
	#undef lowbit
} bit;
inline int binary(int now) {
	int l = now,r = ma - 1;
	while (l < r) {
		int mid = l + r >> 1;
		if (mid - bit.query(mid) < now) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}
	return l;
}
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	scanf("%d%d",&n,&m);
	scanf("%s",str + 1);
	for (register int i = 1;i <= n; ++ i) {
		st[getid(str[i])].insert(i);
	}
	while (m --) {
		int l,r;
		scanf("%d%d",&l,&r);
		char ch[5];
		scanf("%s",ch + 1);
		int posl = binary(l),posr = binary(r),pos = getid(ch[1]);
		set<int>::iterator it = st[pos].lower_bound(posl),t = it;
		for (;t != st[pos].end() && *t <= posr; ++ t) {
			del[*t] = true;
			bit.update(*t,1);
		}
		st[pos].erase(it,t);
	}
	for (register int i = 1;i <= n; ++ i) {
		if (!del[i]) {
			printf("%c",str[i]);
		}
	}
	
	return 0;
}
```

---

## 作者：Adove (赞：0)

我们维护一个字符位置的平衡树森林，还有一个权值线段树

每次修改的时候$l,r$可以用权值线段树找到对应在原序列的位置

删除的时候在平衡树和线段树上同时删就行

我的平衡树写的fhq treap

由于fhq treap删出来的仍然是一棵树，可以直接dfs，常数比调用set的迭代器小了不少

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1<<18;
const int MAXM=256;

int n,m,cnt;
char ch[MAXN];
int sum[MAXN<<1],ik[MAXN];
int root[MAXM];
int siz[MAXN],val[MAXN],rev[MAXN],sn[2][MAXN];

int cret(int v)
{
	siz[++cnt]=1;
	val[cnt]=v;
	rev[cnt]=rand();
	return cnt;
}

void pushup(int x){siz[x]=siz[sn[0][x]]+siz[sn[1][x]]+1;}

int un(int x,int y)
{
	if(!x||!y) return x|y;
	if(rev[x]<rev[y]){
		sn[1][x]=un(sn[1][x],y);
		pushup(x);
		return x;
	}sn[0][y]=un(x,sn[0][y]);
	pushup(y);
	return y;
}

void dro(int k,int v,int &x,int &y)
{
	if(!k){x=y=0;return;}
	if(val[k]<=v) x=k,dro(sn[1][k],v,sn[1][k],y);
	else y=k,dro(sn[0][k],v,x,sn[0][k]);
	pushup(k);
	return;
}

void ins(int id,int v)
{
	int x,y;
	dro(root[id],v,x,y);
	root[id]=un(un(x,cret(v)),y);
	return;
}

void build(int k,int l,int r)
{
	if(l==r){ins((int)ch[l],l);sum[k]=1;ik[l]=k;return;}
	int i=k<<1,mid=l+r>>1;
	build(i,l,mid),build(i|1,mid+1,r);
	sum[k]=sum[i]+sum[i|1];
	return;
}

int find(int k,int l,int r,int v)
{
	while(1){
		if(l==r) return l;
		int i=k<<1,mid=l+r>>1;
		if(sum[i]>=v) k=i,r=mid;
		else v-=sum[i],k=i|1,l=mid+1;
	}
}

void dfsdel(int x)
{
	if(sn[0][x]) dfsdel(sn[0][x]);
	if(sn[1][x]) dfsdel(sn[1][x]);
	for(int i=ik[val[x]];i;i>>=1) --sum[i];
	return;
}

void cdel(int id,int l,int r)
{
	int x,y,z;
	dro(root[id],l-1,x,y);
	dro(y,r,y,z);
	root[id]=un(x,z);
	if(y) dfsdel(y);
	return;
}

void dfs(int k,int l,int r)
{
	if(l==r&&sum[k]){putchar(ch[l]);return;}
	int i=k<<1,mid=l+r>>1;
	if(sum[i]) dfs(i,l,mid);
	if(sum[i|1]) dfs(i|1,mid+1,r);
	return;
}

int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",ch+1);
	build(1,1,n);
	while(m--){
		int l,r;char c;
		scanf("%d%d\n%c",&l,&r,&c);
		l=find(1,1,n,l);r=find(1,1,n,r);
		cdel((int)c,l,r);
	}dfs(1,1,n);puts("");
	return 0;
}
```

---

