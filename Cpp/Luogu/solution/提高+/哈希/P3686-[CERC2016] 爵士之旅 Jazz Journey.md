# [CERC2016] 爵士之旅 Jazz Journey

## 题目描述

Ivan正在为他的爵士乐队计划一场规模盛大的欧洲巡演。在欧洲一共有n个城市，编号依次为1到n。Ivan计划举办d场演出，分别在城市a\_1,a\_2,...,a\_d，并且严格遵循这个顺序，而且不会在同一个城市连续巡演两次（即a\_i!=a\_{i+1}），但在整个过程中，他可能在一个城市巡演多次。最终，他一定会回到开始的城市进行巡演（即a\_1=a\_d）。


Ivan每次总是选择搭乘一趟从a\_i到a\_{i+1}的直达航班。然而，他希望变得聪明一些，尽量节省机票的开支。你也知道，机票的价格取决于供给和需求，比如一张单程票可能会比相同目的地的双程票还要贵。


一共有两种可以购买的机票：


1.从a到b的单程票，每张只能从a飞到b一次，但不能从b飞到a。


2.从a到b的双程票，只需购买一张，就能从a飞到b一次，然后从b飞回a一次，但先从b飞回a是不允许的。当然，你也可以选择从a飞到b之后就再也不返回a。


给定可以购买的机票集合，每种机票都是无限量供应的。请帮助Ivan找到一种最省钱的方案。你可以认为合法方案必然存在。


## 样例 #1

### 输入

```
2 5
1 2 1 2 1
4
1 2 R 6
1 2 O 3
2 1 O 3
1 2 R 5```

### 输出

```
10```

# 题解

## 作者：Ebola (赞：6)


一道非常繁琐的贪心题，需要高超的实现技巧，否则代码会很丑

在这里先%一下Mys_C_K大爷，他的写法实在是太优美了

先根据给定的这些机票，处理出每种类型机票的最小花费，用哈希表保存一下（懒人用unordered_map）

然后对于一种x与y之间的飞行，记A表示x到y的单程最小花费，B表示y到x的单程最小花费，AB表示x到y的来回最小花费，BA表示y到x的来回最小花费

单程最小花费需要考虑往返机票反而更便宜的情况。来回最小花费需要考虑两张单程反而比一张往返便宜的情况

然后如果AB比BA小，就优先选择x到y往返。注意到一个往返机票买了之后是可以任意时刻免费返程的，所以可以做类似括号匹配的事情，将匹配的位置打上删除标记。然后再选择y到x的往返。最后再处理x到y的单程、y到x的单程

如果AB比BA大，那也是一样的，就把优先顺序换一下就好了。注意到这是完全一样的过程，所以如果AB比BA大，我们可以swap(A,B)，swap(AB,BA)，然后将x与y的意义交换一下，代码就不用再多写一遍了

贪心的正确性显然

```cpp
#include<bits/stdc++.h>
#define FR first
#define SE second
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}
inline bool readc()
{
    char c=Get();
    while(c!='O'&&c!='R') c=Get();
    return c=='R';
}
template<class I> inline void upmin(I &x,const I &y){if(y<x) x=y;}

typedef long long LL;
typedef pair<int,int> pii;
const int N=300010;
struct Type
{
    int u,v,ty;
    Type(int _u=0,int _v=0,int _ty=0):u(_u),v(_v),ty(_ty){}
    LL gethash(){return (LL)u*N*2+v*2+ty;}
};

unordered_map<LL,int> h;
map<pii,int> idx;
int n,m,pfm[N],d[N],cnt=0;
vector<int> V[N];
int stk[N];
bool del[N];
LL ans=0;

int val(pii pr,int d)
{
    LL tmp=Type(pr.FR,pr.SE,d).gethash();
    if(!h.count(tmp)) return INT_MAX;
    else return h[tmp];
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=m;i++) pfm[i]=read();
    int tot=read();
    for(int i=1;i<=tot;i++)
    {
        int x=read(),y=read(),z=readc(),w=read();
        if(!h.count(Type(x,y,z).gethash())) h[Type(x,y,z).gethash()]=w;
        else upmin(h[Type(x,y,z).gethash()],w);
    }
    for(int i=1;i<m;i++)
    {
        int x=pfm[i],y=pfm[i+1];
        if(x>y) swap(x,y),d[i]=1;
        if(!idx.count(pii(x,y))) idx[pii(x,y)]=++cnt;
        V[idx[pii(x,y)]].push_back(i);
    }
    for(auto mpr : idx)
    {
        if(!V[mpr.SE].size()) continue;
        pii pr=mpr.FR,ipr=pii(pr.SE,pr.FR);
        LL A=val(pr,0),B=val(ipr,0),AB=val(pr,1),BA=val(ipr,1),dd=0;
        upmin(A,AB);upmin(B,BA);upmin(AB,A+B);upmin(BA,B+A);
        if(AB>BA) swap(A,B),swap(AB,BA),dd=1;
        memset(del,0,sizeof(bool)*V[mpr.SE].size());
        for(int i=0,top=0;i<V[mpr.SE].size();i++)
        {
            if(d[V[mpr.SE][i]]==dd) stk[++top]=i;
            else if(top) del[stk[top]]=del[i]=1,top--,ans+=AB;
        }
        for(int i=0,top=0;i<V[mpr.SE].size();i++)
        {
            if(del[i]) continue;
            if(d[V[mpr.SE][i]]!=dd) stk[++top]=i;
            else if(top) del[stk[top]]=del[i]=1,top--,ans+=BA;
        }
        for(int i=0;i<V[mpr.SE].size();i++)
        {
            if(del[i]) continue;
            if(d[V[mpr.SE][i]]==dd) ans+=A;
            else ans+=B;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：Starlight237 (赞：5)

>  (**2021集训队作业 P3686 【[CERC2016]爵士之旅 Jazz Journey】**)给定一个序列 $a_1,...,a_d$，需要依次按顺序从 $a_i$ 走到 $a_{i+1}$，共走 d-1 次。有 m 种票，分为单程票和往返票，单程票 $(u\rightarrow v)$ 只能从 u 走到 v 恰好一次，往返票 $(u\rightarrow v\rightarrow u)$ 可以从 u 走到 v 恰好一次，在此之后可以选择最多一次机会从 v 回到 u，也可以当成单程票使用，但是不可以先从 v 走到 u。每张票都有价格，且数目无限，求完成这 d-1 次移动的最小费用。

**Lemma 0** 若 $\{a_i,a_{i+1}\}$ 和 $\{a_j,a_{j+1}\}$ 不同，则这两次移动的方案和贡献互不干涉，可以分开讨论。

从而我们可以考虑分别对于每一种 $(u,v)$ 和 $(v,u)$ 求出最小费用。用 $\texttt{'('}$ 表示 $u\rightarrow v$，$\texttt{')'}$ 表示 $v\rightarrow u$，则一个方案可以表示成字符集为 $\{\texttt{'(',')'}\}$ 的字符串。记单程票 $(x\rightarrow y)$ 的票价为 $w(x,y)$，往返票 $(x\rightarrow y\rightarrow x)$ 的票价为 $w'(x,y)$。则有

**Lemma 1** 我们可以假定 $w(u,v)\le w'(u,v)\le w(u,v)+w(v,u),w(v,u)\le w'(v,u)\le w(v,u)+w(u,v)$。  
证明：否则可以用往返票代替单程票，或者两张单程票代替往返票，答案一定不会变劣。

Lemma 1 的意思是，若不满足该不等关系，可以直接把单程票的票价调成往返票的票价，或者把往返票的票价调成两张单程票之和，从而强行满足该不等式，并且这样调整不影响答案。

下面不妨设 $w'(u,v)\le w'(v,u)$，反之同理。

**Lemma 2** 存在一种最优方案，最多使用 $(u\rightarrow v)$ 和 $(v\rightarrow u)$ 的其中一种。  
证明：若同时使用了两种，根据 Lemma 1，我们可以将这两种按照顺序用往返票 $(u\rightarrow v\rightarrow u)$ 或 $(v\rightarrow u\rightarrow v)$ 代替。

**Lemma 3** 最优方案中，两种往返票的使用次数总和为定值。  
证明：最优方案中，使用往返票一定是对于一对 $\texttt{(,)}$ （不管先后顺序），由于 $($ 和 $)$ 的对数是一定的，而由 Lemma 1 知使用往返票比两张单程更优，从而对于每对 $\texttt{(,)}$ 或者 $\texttt{),(}$，我们都使用往返票。这样往返票的使用次数恰好等于括号对数。

由于 $w'(u,v)\le w'(v,u)$，我们尽可能配对 $\texttt{(,)}$，于是问题转化为了求一个括号序列的最大合法匹配子序列。

用栈跑一遍，贪心地进行括号匹配即可。具体实现时和判定括号序列是否合法匹配一样，区别在于如果当前匹配不了（遇到了 $\texttt{')'}$ 但栈为空）,不需要做任何处理，跳过即可。

然后最后一定是剩下了 $\texttt{)))...(((}$ 这样的序列，贪心用 $\texttt{),(}$ 匹配，剩下的 $\texttt{((...}$ 或者 $\texttt{))...}$ 用单程票跑掉即可。

tip 1. 其实我们可以发现并不需要真的用栈，只要维护栈顶指针即可（栈中元素个数），至于栈中存啥无所谓。并不需要开一个栈数组或者 `std::stack` 之类的。

tip 2. 在处理行程和票的时候，可以把 $(u,v)$ 压缩成一个 `unsigned long long`，并且用 `std::unordered_map` 来存储。

```cpp
#define ull unsigned ll
#define vi vector<int>
const int N = 300010;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, d, m, tot, a[N];
struct Edge {
	ll uv, vu, uvu, vuv;
	Edge (ll uv = INF, ll vu = INF, ll uvu = INF, ll vuv = INF) : uv(uv), vu(vu), uvu(uvu), vuv(vuv) {}
};
ull buc[N];
unordered_map<ull, int> id;
unordered_map<ull, Edge> mp;
vector<int>vec[N];
inline int newedge(int u, int v) {
	if (u > v) swap(u, v);
	ull sta = (ull)u << 32 | v;
	auto op = id.emplace(sta, tot + 1);
	return op.second ? buc[++tot] = sta, tot : op.first -> second;
}
inline ll solve(vi&vec, Edge e) {
	ll uv = e.uv, vu = e.vu, uvu = e.uvu, vuv = e.vuv;
	uv = min(uv, uvu), vu = min(vu, vuv), uvu = min(uvu, uv + vu), vuv = min(vuv, vu + uv);
	if (uvu > vuv) {
		for (int &x : vec) x ^= 1;
		swap(uv, vu), swap(uvu, vuv);
	}
	if (uvu == 0x3f3f3f3f3f3f3f3fll) return min(uv, vu) * vec.size();
	int lft = 0, rht = 0, pair_ = 0;
	for (int x : vec)
		!x ? ++lft : lft ? --lft, ++pair_ : ++rht;
	int rest_ = min(lft, rht);
	return uv * (lft - rest_) + vu * (rht - rest_) + uvu * pair_ + vuv * rest_;
}
inline void upd(ll &x, ll y) {x = min(x, y);}
int main() {
	n = rd(), d = rd();
	for (int i = 1; i <= d; ++i) a[i] = rd();
	for (int i = 1; i < d; ++i) {
		int u = a[i], v = a[i + 1];
		vec[newedge(u, v)].push_back(u > v);
	}
	m = rd();
	for (int i = 1; i <= m; ++i) {
		int u = rd(), v = rd(), w;
		char tic = gtc(); w = rd();
		if (tic == 'O')
			upd(u < v ? mp[(ull)u << 32 | v].uv : mp[(ull)v << 32 | u].vu, w);
		if (tic == 'R')
			upd(u < v ? mp[(ull)u << 32 | v].uvu : mp[(ull)v << 32 | u].vuv, w);
	}
	ll ans = 0;
	for (int i = 1; i <= tot; ++i)
		ans += solve(vec[i], mp[buc[i]]);
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Alan_Zhao (赞：1)

**[在我的 cnblogs 中查看](https://www.cnblogs.com/alan-zhao-2007/p/p3686-sol.html)**

## 题解

可以发现，对于巡演的路线 $x\to y$ 和 $a\to b$，若 $\min(x,y)\neq \min(a,b)$ 或 $\max(x,y)\neq \max(a,b)$，则其答案互不影响。不妨设 $x<y$，我们需要对每一种 $(x,y),(y,x)$ 求出最小值。

将巡演路线中 $x\to y$ 记作 $($，$y\to x$ 记作 $)$，则它形成了一个仅由左右括号组成的序列。设 $A$ 为 $x\to y$ 的最优价钱，$B$ 同理；$AB$ 为 $x\to y\to x$ 的最优价钱，$BA$ 同理。则有：$A=\min(\operatorname{cost}(x\to y),AB),AB=\min(A+B,\operatorname{cost}(x\to y\to x))$，$B,BA$ 同理。

不妨设 $AB<BA$，于是，最优策略是：不断地删去括号序列中的 $()$ 子序列（不必连续），然后不断地删去 $)($ 子序列，直到只剩下若干 $($ 或 $)$。

若 $AB>BA$，则只需要将所有左、右括号调换，然后 $A,B$ 调换，$AB,BA$ 调换，再执行上面的策略即可。

注意 $\max(AB,BA)$ 可能会达到 $2\times 10^9$，因此 $\inf$ 要开得大一点。

## 代码

```cpp
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <utility>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
template<typename T> void Read(T &_x){
	_x=0;int _f=1;
	char ch=getchar();
	while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();
	while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();
	_x*=_f;
}
template<typename T,typename... Args> void Read(T &_x,Args& ...others){
	Read(_x);Read(others...);
}
typedef long long ll;
typedef pair<int,int> pii;
const ll Inf=0x3f3f3f3f3fLL;
const int N=3e5+5;
int n,d,m;
map<pii,string> mp;
void Insert(int x,int y){
	if(x<y) mp[{x,y}]+='A';
	else mp[{y,x}]+='B';
}
map<pii,ll> one,two;
void Insert2(map<pii,ll> &fli,int u,int v,int p){
	pii x(u,v);
	if(!fli.count(x)) fli.insert({x,p});
	else fli[x]=min(fli[x],ll(p));
}
ll Find(const map<pii,ll> &fli,int u,int v){
	pii x(u,v);
	if(!fli.count(x)) return Inf;
	return fli.at(x);
}
int rem[N];
ll Calc(const string &s,ll cost,char c){
	ll res=0;
	stack<int> stk;
	for(int i=0;i<int(s.size());++i){
		if(rem[i]) continue;
		if(s[i]==c) stk.push(i);
		else{
			if(stk.empty()) continue;
			res+=cost,rem[stk.top()]=rem[i]=1;
			stk.pop();
		}
	}
	return res;
}
int main(){
	Read(n,d);
	int pre;
	For(i,1,d){
		int x;Read(x);
		if(i>1) Insert(pre,x);
		pre=x;
	}
	Read(m);
	For(i,1,m){
		int u,v,p;char temp[5];
		Read(u,v);scanf("%s",temp);Read(p);
		if(temp[0]=='O') Insert2(one,u,v,p);
		else Insert2(two,u,v,p);
	}
	ll ans=0;
	for(const auto &pr:mp){
		int x=pr.first.first,y=pr.first.second;
		string s=pr.second;
		for(int i=0;i<int(s.size());++i) rem[i]=0;
		ll A=Find(one,x,y),B=Find(one,y,x);
		ll AB=Find(two,x,y),BA=Find(two,y,x);
		A=min(A,AB),B=min(B,BA);
		AB=min(AB,A+B),BA=min(BA,A+B);
		if(BA<AB){
			for(char &c:s){
				if(c=='A') c='B';
				else c='A';
			}
			swap(A,B);swap(AB,BA);
		}
		ans+=Calc(s,AB,'A');
		ans+=Calc(s,BA,'B');
		for(int i=0;i<int(s.size());++i){
			if(rem[i]) continue;
			if(s[i]=='A') ans+=A;
			else ans+=B;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

