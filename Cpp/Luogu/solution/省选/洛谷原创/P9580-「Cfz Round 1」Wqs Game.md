# 「Cfz Round 1」Wqs Game

## 题目背景

『博』和『奕』喜欢博弈，尤其喜欢 wqs 带权博弈。

## 题目描述

wqs 带权博弈在一个数列 $\{a_i\}$ 上进行，对应有一个 $01$ 串 $\{b_i\}$。

1. 若 $b_i=0$，则 $a_i$ 这个数字是属于『博』的；
2. 若 $b_i=1$，则 $a_i$ 这个数字是属于『奕』的。

游戏规则是，每次给定一个区间 $[l,r]$，从 $a_l$ 到 $a_r$，拥有这个数的人**依次**决定选该数或者不选，两个人都会采用**最优策略**。

因为『博』很强大，她会让着『奕』，于是博弈的规则是，如果最后两个人选的数**按位异或和不为零**，则『奕』获胜，否则『博』获胜。

注意每个人**能看到**对方的选数情况，可以选**多个**数（只要这个数是自己的），最后计算两个人选数的总**异或**和。

对于任意区间 $[l,r]$，若『奕』获胜，则 $w(l,r)=1$，否则 $w(l,r)=0$。

每次查询 $\sum\limits_{l=L}^R\sum\limits_{r=l}^Rw(l,r)$ 的值，对 $2^{32}$ 取模。

由于输入输出量过大，对于 $tp\ne 0$ 的测试点，选手需要自行生成数列 $a_i$ 和询问区间 $[L,R]$，并用特殊方式输出答案。

注意正解**不依赖**特殊的输入输出方式。

## 说明/提示

#### 【样例解释 #1】

只有 $w(1,1)=w(1,2)=1$。

对于区间 $[1,3]$，如果『奕』选第一个数，则『博』选后两个数，否则『博』不选，于是『博』获胜。

注意是从左往右依次选取，『博』在选后两个数之前能够知道『奕』是否选了第一个数。

#### 【样例解释 #2】

只有 $w(1,1)=w(1,2)=w(1,3)=w(1,4)=w(2,3)=w(2,4)=w(3,3)=w(3,4)=1$。

#### 【样例解释 #3】

由于本样例 $tp\ne 0$，所以你需要使用特殊方式输入输出。

#### 【数据范围】

对于所有数据，$1\le n\le5\times10^5,1\le q\le 1.5\times10^6,0<a_i<2^{60},1\le L\le R\le n,0\le tp<2^{64}$。

| 子任务编号 | 分值 |    $n\le$     |     $q\le$      |  $tp$  |  $a_i<$  | 特殊性质 |
| :--------: | :--: | :-----------: | :-------------: | :----: | :------: | :------: |
|    $1$     | $6$  |     $20$      |      $100$      |  $=0$  | $2^{60}$ |    有    |
|    $2$     | $7$  |     $100$     |     $10^3$      |  $=0$  | $2^{10}$ |    有    |
|    $3$     | $8$  |     $700$     |     $10^3$      |  $=0$  | $2^{10}$ |    无    |
|    $4$     | $9$  |    $3000$     |     $10^5$      |  $=0$  | $2^{60}$ |    无    |
|    $5$     | $14$ | $3\times10^4$ |     $10^5$      |  $=0$  | $2^{20}$ |    无    |
|    $6$     | $17$ | $2\times10^5$ | $1.5\times10^6$ | $\ge1$ | $2^{60}$ |    有    |
|    $7$     | $19$ | $5\times10^5$ | $1.5\times10^6$ | $\ge1$ | $2^{60}$ |    有    |
|    $8$     | $20$ | $5\times10^5$ | $1.5\times10^6$ | $\ge1$ | $2^{60}$ |    无    |

特殊性质：序列 $b_i$ 中最多有 $10$ 个 $0$。

#### 【备注】

数据生成方式：

```cpp
using ul=unsigned long long;
using ui=unsigned int;
ui Ans,ans;
ul Sd,Cnt;
ul Rd(){Sd^=Sd<<19,Sd^=Sd>>12,Sd^=Sd<<29;return Sd^=++Cnt;}
void GetA(ul &a){a=Rd()%((1ull<<60)-2)+1;}
void GetLR(int &l,int &r){
    l=Rd()%n+1,r=Rd()%n+1;
    if(l>r)swap(l,r);
}
int main(){
    //read n,q,tp,b[i]
    if(tp){
        Sd=tp,Cnt=0;
        for(int i=1;i<=n;++i)GetA(a[i]);
        for(int qi=1;qi<=q;++qi){
            GetLR(l,r);
            //sol
            Ans^=ans*qi;
        }
        printf("%u\n",Ans);
	}
}
```

## 样例 #1

### 输入

```
3 2 0
100
3 1 2
1 3
2 3```

### 输出

```
2
0```

## 样例 #2

### 输入

```
5 2 0
10100
2 7 6 3 5
1 5
2 4```

### 输出

```
8
4```

## 样例 #3

### 输入

```
20 100 8551679995685981130
11001000000000000000```

### 输出

```
1673```

# 题解

## 作者：EnofTaiPeople (赞：18)

首先，我们需要明确胜负判断规则，防止把博和奕搞反，而关键句就是“博让奕，故为零博获胜”。

如果只考虑一次博弈，最初的异或和为零。每当遇到一个奕的数字，如果他选了，那么博必须想办法把这个数字抵消掉，即在后面寻找一个自己的数字集合，将它们取反（即选变不选，不选变选，最开始每个数字都不选）。

如果对于每一个奕的数字，博都能在后面找到抵消方案的话，博就获胜，如果存在一个找不到抵消方案，就是奕获胜。

奕获胜的方法就是，其它的数字都不选，只考虑这个数字选不选。而走到这里时，如果奕选或不选博在后面都有方法应对的话，将这两种方法异或能得出凑出该数的方案，与“找不到抵消方案”矛盾。

找子集异或起来等于给定数字就是异或线性基模板，于是我们能够成功解决一次博弈的胜负了，这样时间复杂度为 $O(n^2w)$，可以得到 $21$ 分。（$w=60$ 为二进制位数，下同）

然后你发现如果 $b_r=1$，那么 $[l,r]$ 一定是奕获胜（走到最后，为零就选，否则不选），于是子任务 $6$ 可以通过，子任务 $7$ 也可能通过，期望得分 $38\sim57$ 分。

要想得到更高的分，需要从单调性入手，本题的单调性在于固定右端点，左端点一定是前一段奕获胜，后一段博获胜，因为越往左越能找到一个“凑不出的”奕的数字，考虑求出 $L_r=\min\limits_{w(l,r)=0}l$，不存在则 $L_r=r+1$。

还有对于一个奕的数字，一定是前一段凑不出，后一段凑得出，这个就太明显了。

可以对于每一个奕的数字都二分找到最后一个凑不出的地方，用线段树或 ST 表套线性基维护。如果对于 $l$ 来说，最后一个凑不出的地方为 $r$，就有 $\forall x\in[l,r],L_x\ge l+1$，这里是一个区间最值操作，怎么做都可以。

求出 $L_x$ 之后，我们只需要扫右端点，每次对区间 $[1,L_r-1]$ 增加 $1$，然后 $[l,r]$ 的区间和就是答案，这里因为操作简单只需要使用树状数组，瓶颈在于线段树或 ST 表套线性基，为 $O(nw^2\log n+q\log n)$，不过特殊性质可以只维护 $b_i=0$ 的，忽略不计，能通过子任务 $1\sim 7$，期望得分 $80$ 分。

上面都不是难点，我们需要优化求 $L_x$ 的过程。

从右往左扫，扫到 $l$ 时，如果 $b_l=1,(l,r]$ 凑不出 $a_l$ 那么直接令 $L_r=l+1$，$r$ 就没有用了，因为对于后面的 $l$，由于我们无法凑出 $b_l$，因此 $\forall l'\in[1,l],w(l',r)=1$。

可以动态维护一个线性基栈，依次是 $(l,r_1],(r_1,r_2],\dots$，如果 $b_l=0$，就直接将区间 $(l-1,l]$ 压栈，否则看 $(l,r_1]$ 能否凑出 $a_l$，能就不管，不能就 $L_{r_1}\leftarrow l+1$，并将 $(l,r_1]$ 并到 $(r_1,r_2]$，继续判断。

这里线性基合并是均摊 $O(nw)$ 的，因为每一个数字只会在每一位插入失败一次。

总时间复杂度 $O(nw+(n+q)\log n)$，空间 $O(nw)$。

不强制在线的原因是可持久化空间花费太大，以至于无法体现时间优势。

因为时空限制都是两倍，所以场上也有人写线段树通过，不卡同复杂度的解法。

可以使用前缀线性基做到一样的复杂度，不需要线性基合并。

---

## 作者：eastcloud (赞：3)

[更好的阅读体验](https://www.cnblogs.com/eastcloud/p/17660423.html)

挺好的博弈论题，这是一个跟官方题解不太一样的做法。

遇到这种组合游戏可以先考虑逆推胜负，把握一下规律，我们先从一个区间的胜负判断开始入手。

考察区间中最后一个数字的从属关系，如果它属于弈，因为 $a_i>0$，如果前面传来的数字非空，则弈不用选择也可以获胜，否则只要选择当前的数即可。

如果它属于博，那么这个数得刚好为 0 或者等于 $a_i$，博才有办法获胜，以此推广到最后有多个数属于博的情况：只有前面传来的数能被这些数异或表示（在它们的张成空间中），博才能获胜。

而这个规律推广到更前面的连续段也是适用的，即对于数列的任意一个前缀中属于弈的数的张成空间，都是对应后缀属于博的数的张成空间的子集时，博才能获胜。

找到了规律，我们接着来设计算法进行统计，一个维护这种“区间中的子区间”数量的常用方法是对一个端点进行扫描线，维护 $S$ 数组表示以对应位置为开头或结尾，且以当前扫描到的这个数为另一个端点时，合法的区间数。

由于刚才我们是从右往左推理，我们也动态从右往左扫描，对于一个以弈拥有的数为右端点的区间贡献肯定为 $r-l+1$，而另一种区间如果在扫描中遇到了一个节点，且它不在当前这个张成空间中，后面无论再怎么扫也一定无解，前面一定有解，也就是说这种胜负具有一定单调性。

这启发我们先预处理出每个弈拥有的点在右端点到哪才能被右边属于博的数异或表示出，记为 $rpos_i$ 可以倒着扫描整个序列，贪心维护一个线性基，每次加数时淘汰时间比较老的节点，当加到 $a_{i+1}$ 时就可以处理 $a_i$ 的信息，对它用到的节点的时间戳取最大即可。

回到刚才的扫描线，由于“当前没有机会的右端点集合”只要一开始把所有都加进去就是只增不减，每次扫描到一个属于弈的数就把 $i$ 到 $rpos_i$ 中的所有数标记为合法，可以使用并查集或者 set 维护，之后开个树状数组维护答案，这里数点的方式有很多种，这里不再赘述。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<set>
#include<vector> 
#define N 500005
#define M 1500006
#define ll long long
using namespace std;
typedef unsigned long long ul;
typedef unsigned int ui;
ui ans;
ui Ans;
ul Sd,Cnt;
ul cnt,n,q,tp,a[N];
ul Rd(){Sd^=Sd<<19,Sd^=Sd>>12,Sd^=Sd<<29;return Sd^=++Cnt;}
char s[N];
void GetA(ul &a){a=Rd()%((1ll<<60)-2)+1;}
void GetLR(ul &l,ul &r){
    l=Rd()%n+1,r=Rd()%n+1;
    if(l>r)swap(l,r);
}
ll read(){
	ll x=0;char ch=getchar();
	while(ch<'0' || ch>'9')ch=getchar();
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x;
}
//-----------------------------------------------
struct que{
	ul l,r;
}Q[M];
void init(){
	n=read();q=read();tp=read();
	char ch=getchar();
	while(ch<'0' || ch>'1')ch=getchar();
	while(ch>='0' && ch<='1'){s[++cnt]=ch;ch=getchar();}
    if(tp){
        Sd=tp,Cnt=0;
        for(ll i=1;i<=n;++i)GetA(a[i]);
        for(ll qi=1;qi<=q;++qi){GetLR(Q[qi].l,Q[qi].r);}
	}
	else{
		for(ll i=1;i<=n;i++)a[i]=read();
		for(ll i=1;i<=q;i++){Q[i].l=read();Q[i].r=read();}
	}
}
ll rpos[N];
vector<que> P[N];
ll bas[65],ti[65];
void insert(ll x,ll t){
	for(ll i=61;i>=0;i--){
		if(x&(1ll<<i)){
			if(!bas[i]){bas[i]=x;ti[i]=t;return;}
			else if(t<ti[i]){swap(x,bas[i]);swap(t,ti[i]);x^=bas[i];}
			else x^=bas[i];
		}
	}
}
ll jud(ll x){
	ll ans=0;
	for(ll i=61;i>=0;i--){
		if(x&(1ll<<i)){
			x^=bas[i];ans=max(ans,ti[i]);
		}
	}
	if(x) return n+1;
	else return ans;
}
int ask_b(ll x,ll t){
	ll ans=0;
	for(ll i=61;i>=0;i--){
		if(x&(1ll<<i) && t<=ti[i]){
			x^=bas[i];ans=max(ans,ti[i]);
		}
		else if(x&(1ll<<i))return false;
	}
}
set<ll> S;
ll F[N],G[N];
ll lowbit(ll x){
	return x&(-x);
}
void add(ll x,ll val,ll *K){
	while(x<=n){
		K[x]+=val;
		x+=lowbit(x);
	}
}
ll ask(ll x,ll *K){
	ll ans=0;
	while(x){
		ans+=K[x];
		x-=lowbit(x);
	}
	return ans;
}
ui an[N];
int main(){
	init();ll pos=1;
	rpos[n]=n+1;
	for(ll i=n;i>=1;i--){
		if(s[i]=='0')insert(a[i],i);
		else rpos[i]=jud(a[i]);
	}
	for(ll i=1;i<=n;i++)if(s[i]=='0'){S.insert(i);add(i,i,F);add(i,1,G);}
	for(ll i=1;i<=q;i++)P[Q[i].l].push_back((que){i,Q[i].r});
	for(ll i=n;i>=1;i--){
		if(s[i]=='1'){
			set<ll>::iterator itt=S.lower_bound(i);
			set<ll>::iterator it=itt;
			for(;itt!=S.end() && *itt<rpos[i];itt++){
				add(*itt,-*itt,F);add(*itt,-1,G);
				add(*itt,*itt-i,F);
			}
			S.erase(it,itt);
		}
		for(ll j=0;j<P[i].size();j++){
			ll r=P[i][j].r;
			ans=0;ans=ask(r,F)-ask(i-1,F)-(ask(r,G)-ask(i-1,G))*(i-1);
			ans=(ll)(r-i+2)*(r-i+1)/2-ans;
			if(!tp)an[P[i][j].l]=(ans%(1ll<<32));
			ans%=(1ll<<32);
			ans=(ans*P[i][j].l)%(1ll<<32);
			ui tmp=ans;
			Ans^=tmp;
		}
	}
	if(tp)cout<<Ans;
	else for(ll i=1;i<=q;i++)cout<<an[i]<<endl;
}
```


---

## 作者：MaxBlazeResFire (赞：2)

以下记 $0$ 表示 “博”，$1$ 表示 “奕”。

现给出一个结论：设 $P$ 为 $[l,r]$ 中 $1$ 可以选择的数的位置的集合，$T[l,r]$ 表示 $[l,r]$ 内所有 $0$ 可以选择的数的线性基。那么 $1$ **获胜的充要条件是 $\exists i\in P,a_i$ 不能被 $T[i+1,r]$ 表出。** 必要性显然。充分性的证明可以考虑如果 $P$ 内的元素全部都能表出，那 $0$ 可以通过 **“每当 $1$ 选择一个 $x$，就将后方拼出恰好 $x$ 的数的选择情况取反”** 的策略保证得到胜利。特别地，若 $i=r$，那 $i$ 自然也无法被表出。

考察答案单调性。设固定右端点 $r$，则 $w(l,r)=0$ 的 $l$ 必然占据一段后缀。记 $L_i$ 表示最小的 $l$ 使得 $w(l,i)=0$。于是可以想到二分求 $L_i$，这个东西线段树套线性基合并，复杂度为 $O(n\log n\log^2V)$。

当然这个东西无法通过，考虑维护 $L$ 相同的等价连续无交段的线性基。只考虑所有 $0$ 位置的 $L_i$（所有 $1$ 位置的 $L_i$ 可以在之后统一赋值为 $i+1$）。我们维护一个区间线性基的栈结构，然后从右向左扫描线。设目前到位置 $p$，如果遇到一个 $0$ 就压入 $[p,p,\{a_p\}]$，如果遇到一个 $1$，就从左到右看栈顶的线性基，每次尝试组合出 $a_p$，如果组合不出就出栈并将这个连续段并到后面的连续段，然后继续判断；找到 **极大的连续不可表出 $a_p$ 的连续段 $[L,R]$** 之后把这一段的 $[L,R]$ 在线段树上做一个区间对 $p+1$ 取 $\rm max$，之后重复这个过程就可以了。由于线性基的大小不可能超过原集合的大小，又由于两个线性基合并的复杂度是 $\log V\times$ 某个线性基元素个数的，于是这里整体均摊 $O(n\log V)$。

然后就是处理询问。考虑对右端点扫描线，我们发现，假设目前扫到 $x$，对于所有的 $l\leq L_x-1$ 的区间都产生了 $1$ 的贡献。然后处理右端点在 $r$ 处的所有询问 $[L,R]$，它的答案就是 $[L,R]$ 的贡献和，用线段树维护区间加区间和就行。

但是线段树常数过大（当然可能是我的常数过大），我们考虑压成树状数组。由于每一次相当于前缀 $+1$，于是将一个询问 $[L,R]$ 拆成前缀和之后，考虑 $[1,R]$ 的和就是 $R$ 乘上大于 $R$ 的修改次数再加上 $[1,R]$ 内所有修改的位置之和，这个东西常数很小，一下就飞过去了。

整体复杂度 $O(n\log V)$。写的时候尤其注意这个输入输出方式。

[点我看参考代码。](https://www.luogu.com.cn/paste/lm6f9lhc)

---

## 作者：Rain_chr (赞：1)

前言：在一个单 $\log$ 都需要卡常的题目中，你该如何用双 $\log$ 通过？

首先博弈题需要推导必胜性质，我们发现如果一个区间是博胜利，那么对于任意弈选的数字，博都要能通过其后面可以选择的数字异或起来把弈选的数字给抵消掉。形式化的说，博能够获胜当且仅当 **对于区间中每个弈可以选择的数字，都要能被它开始的后缀中博可以选择的数字通过异或得到。** 这启发着我们需要使用线性基判断，直接做就是 $O(n^2\log V)$ 的复杂度，可以拿到 30 分。

稍微观察一下可以发现，对于弈可以选择的数字，让博不能够表示出这个数字的右端点是从他开始的一段区间。如果我们能求出最小的 $R_x$ 表示 $a_i$ 能被 $[i,R_x]$ 中博可以选择的数字抵消，那么对于一个右端点 $r$，弈必胜的区间左端点是一段前缀，具体的说 $l\le \max\{R_x|x\le r <R_x\}$ 的 $[l,r]$，弈都能获胜。这样的原因也很简单，$x$ 不能被 $[x,r]$ 中博可以选择的数字表示。

所以对于合法区间的维护是很容易的，你可以在扫描 $r$ 的过程中用一个可删堆动态维护 $\max\{R_x|x\le r <R_x \}$，然后用线段树维护答案。

现在唯一的问题是如何求出 $R_x$，也就是最小的 $R_x$ 使得$a_i$ 能被 $[i,R_x]$ 中博可以选择的数字抵消。我们可以二分这个 $R_x$，然后在后缀线性基中查询是否能够被表示。这样虽然时间复杂度是 $O(n\log n\log V+q\log n)$ 的，但是常数很小跑不满，最后也没怎么卡常就过了。

展示最劣解：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,q;
namespace rd
{
    using ul=unsigned long long;
    using ui=unsigned int;
    ui Ans,ans;
    ul Sd,Cnt;
    ul Rd(){Sd^=Sd<<19,Sd^=Sd>>12,Sd^=Sd<<29;return Sd^=++Cnt;}
    inline void GetA(ll &a){a=Rd()%((1ull<<60)-2)+1;}
    inline void GetLR(int &l,int &r){
        l=Rd()%n+1,r=Rd()%n+1;
        if(l>r)swap(l,r);
    }
}
const int N=5e5+10;
ll a[N];
char b[N];
struct node
{
    ll c[60];
    int t[60];
    inline void insert(ll x,int id)
    {
        for(register int i=59;i>=0;i--)
        {
            if(x>>i&1^1) continue;
            if(!c[i])
            {
                c[i]=x,t[i]=id;
                return ;
            }
            else if(t[i]>id) swap(c[i],x),swap(t[i],id);
            x^=c[i];
        }
    }
    inline bool check(ll x,int r)
    {
        for(register int i=59;i>=0;i--)
        {
            if(x>>i&1^1) continue;
            if(!c[i]||t[i]>r) return 0;
            x^=c[i];
        }
        return 1;
    }
    inline void clear(){memset(c,0,sizeof(c));}
}T;
ll ans[3*N];
vector<pair<int,int> > ask[N];
vector<int> del[N];
struct PQ
{
    priority_queue<int> p,q;
    inline void push(int x){p.push(x);}
    inline void pop(int x){q.push(x);}
    inline int top()
    {
        while(p.size()&&q.size()&&p.top()==q.top()) p.pop(),q.pop();
        return p.top();
    }
    inline bool empty()
    {
        while(p.size()&&q.size()&&p.top()==q.top()) p.pop(),q.pop();
        return p.empty();
    }
}p;
struct Segment
{
    ll t[N<<2],tag[N<<2];
    inline void pushdown(int x,int l,int r)
    {
        if(!tag[x]) return ;
        int mid=(l+r)>>1;
        tag[x<<1]+=tag[x],tag[x<<1|1]+=tag[x];
        t[x<<1]+=tag[x]*(mid-l+1),t[x<<1|1]+=tag[x]*(r-mid);
        tag[x]=0;
    }
    void upd(int x,int l,int r,int L,int R,int v)
    {
        if(L<=l&&r<=R) t[x]+=1ll*v*(r-l+1),tag[x]+=v;
        else
        {
            pushdown(x,l,r);
            int mid=(l+r)>>1;
            if(L<=mid) upd(x<<1,l,mid,L,R,v);
            if(mid+1<=R) upd(x<<1|1,mid+1,r,L,R,v);
            t[x]=t[x<<1]+t[x<<1|1];
        }
    }
    ll query(int x,int l,int r,int L,int R)
    {
        if(L<=l&&r<=R) return t[x];
        else
        {
            pushdown(x,l,r);
            int mid=(l+r)>>1;
            ll k=0;
            if(L<=mid) k+=query(x<<1,l,mid,L,R);
            if(mid+1<=R) k+=query(x<<1|1,mid+1,r,L,R);
            return k;
        }
    }
}S;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    cin>>n>>q>>rd::Sd;
    for(register int i=1;i<=n;i++) cin>>b[i];
    for(register int i=1;i<=n;i++)   
    {
        if(rd::Sd) rd::GetA(a[i]);
        else cin>>a[i];
    }
    for(register int i=1;i<=q;i++)
    {
        int l,r;
        if(rd::Sd) rd::GetLR(l,r);
        else 
        {
            cin>>l>>r;
            if(l>r) swap(l,r);
        }
        ask[r].push_back(make_pair(l,i));
    }
    for(register int i=n;i;i--)
    {
        if(b[i]=='1') 
        {
            int l=i+1,r=n,ans=n+1;
            while(l<=r)
            {
                int mid=(l+r)>>1;
                if(T.check(a[i],mid)) ans=mid,r=mid-1;
                else l=mid+1;
            }
            del[ans].push_back(i);
        }
        else T.insert(a[i],i); 
    }
    for(register int i=1;i<=n;i++)
    {
        if(b[i]=='1') p.push(i);
        for(register int j:del[i]) p.pop(j);
        if(!p.empty()) S.upd(1,1,n,1,p.top(),1);
        for(pair<int,int> j:ask[i]) ans[j.second]=S.query(1,1,n,j.first,i);
    }
    if(rd::Sd)
    {
        unsigned sum=0;
        for(register int i=1;i<=q;i++) sum^=1ll*i*ans[i];
        cout<<sum;
    }
    else 
        for(register int i=1;i<=q;i++) cout<<ans[i]<<'\n';
	return 0;
}

```

---

## 作者：翼德天尊 (赞：1)

场上不会的喵喵提。以下称 博 为 A，奕 为 B。

有关博弈的转化是，对于一个区间 $[l,r]$ 内所有 B 点 $i$ 的 $a_i$，都可以被 $[i+1,r]$ 内 A 点的 $a_i$ 异或表示出来。

此时已经可以对每个区间暴力线性基做了，时间复杂度 $O(n^2w+qn)$。

考虑优化，首先对于所有 $b_r=1$ 的区间 $[l,r]$，一定可以对答案造成贡献。

分析性质我们发现，当右端点固定时，关于左端点一定是前一段不合法后一段合法，分界点在从右向左第一个不能被表示的 B 点，不妨设右端点 $x$ 向左第一个不合法点为 $p_x$；同理对于每一个 B 点，向后也一定是先有一段不合法，再有一段合法。

所以如果我们能快速找到每一个 B 点 $i$ 向后最后一个不能将其表示出的位置 $j$，那么对于 $x\in [i+1,j]$，$p_x=\max(p_x,i)$；而只要能求出所有 $p_i$，我们就可以在询问的时候从左向右扫询问右端点 $r$，移动后将 $[l,p_i] +1$，再查询询问即可。

前者可以考虑，从右向左维护线性基，并对于线性基内的每个位置维护一个时间戳，插入时保持在序列中较靠前的元素保留在时间戳内，B 点在线性基内查的时候将查到的每个线性基元素的时间戳取 max，向前一个位置即为最后一个不能将其表示的位置。求出这个之后从前向后对每个 B 点对应区间作线段覆盖即可。

最终时间复杂度 $O(nw+(n+q)\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ul=unsigned long long;
using ui=unsigned int;
const int N=5e5+5;
const int V=60;
const int Q=1500005;
int n,q;
ul tp;
ul a[N];
ui ans[Q];
char b[N];
struct Query{
    int l,id;
    Query (int l=0,int id=0)
        :l(l),id(id){}
};
vector<Query> qu[N];
struct XXJ{
    ul c[V];
    int ti[V];
    void add(ul x,int id){
        for (int i=V-1;i>=0;i--){
            if (!((x>>i)&1)) continue;
            if (!c[i]){
                c[i]=x,ti[i]=id;
                return;
            }else if (ti[i]>id) swap(c[i],x),swap(ti[i],id);
            x^=c[i];
        }
    } 
    int query(ul x){
        int maxn=0;
        for (int i=V-1;i>=0;i--){
            if (!((x>>i)&1)) continue;
            if (!c[i]) return -1;
            x^=c[i],maxn=max(maxn,ti[i]);
        }
        return maxn;
    }
}X;
struct SegTree{
    int maxn[N<<2],lz[N<<2];
    void pushdown(int i){
        if (lz[i]){
            maxn[i<<1]=max(maxn[i<<1],lz[i]),lz[i<<1]=max(lz[i<<1],lz[i]);
            maxn[i<<1|1]=max(maxn[i<<1|1],lz[i]),lz[i<<1|1]=max(lz[i<<1|1],lz[i]);
            lz[i]=0;
        }
    }
    void pushup(int i){
        maxn[i]=max(maxn[i<<1],maxn[i<<1|1]);
    }
    void modify(int i,int l,int r,int ql,int qr,int k){
        if (ql<=l&&r<=qr){
            maxn[i]=max(k,maxn[i]),lz[i]=max(k,lz[i]);
            return;
        }
        pushdown(i);
        int mid=l+r>>1;
        if (ql<=mid) modify(i<<1,l,mid,ql,qr,k);
        if (mid<qr) modify(i<<1|1,mid+1,r,ql,qr,k);
        pushup(i);
    }
    int query(int i,int l,int r,int pos){
        if (l==r) return maxn[i];
        int mid=l+r>>1;
        pushdown(i);
        if (pos<=mid) return query(i<<1,l,mid,pos);
        return query(i<<1|1,mid+1,r,pos);
    }
}T1;
struct SegTree2{
    ui sum[N<<2],lz[N<<2];
    int len[N<<2];
    void build(int i,int l,int r){
        len[i]=r-l+1;
        if (l==r) return;
        int mid=l+r>>1;
        build(i<<1,l,mid);
        build(i<<1|1,mid+1,r);
    }
    void pushdown(int i){
        if (lz[i]){
            lz[i<<1]+=lz[i],lz[i<<1|1]+=lz[i];
            sum[i<<1]+=lz[i]*len[i<<1],sum[i<<1|1]+=lz[i]*len[i<<1|1];
            lz[i]=0;
        }
    }
    void pushup(int i){
        sum[i]=sum[i<<1]+sum[i<<1|1];
    }
    void add(int i,int l,int r,int ql,int qr,ui k){
        if (ql<=l&&r<=qr){
            sum[i]+=k*len[i],lz[i]+=k;
            return;
        }
        pushdown(i);
        int mid=l+r>>1;
        if (ql<=mid) add(i<<1,l,mid,ql,qr,k);
        if (mid<qr) add(i<<1|1,mid+1,r,ql,qr,k);
        pushup(i);
    }
    ui query(int i,int l,int r,int ql,int qr){
        if (ql<=l&&r<=qr) return sum[i];
        pushdown(i);
        int mid=l+r>>1;
        if (qr<=mid) return query(i<<1,l,mid,ql,qr);
        if (mid<ql) return query(i<<1|1,mid+1,r,ql,qr);
        return query(i<<1,l,mid,ql,qr)+query(i<<1|1,mid+1,r,ql,qr);
    }
}T2;
ll read(){
    ll w=0,f=1;
    char ch=getchar();
    while (ch>'9'||ch<'0') {
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9') {
        w=(w<<3)+(w<<1)+(ch^48);
        ch=getchar();
    }
    return w*f;
}

ul Sd,Cnt;
ul Rd(){Sd^=Sd<<19,Sd^=Sd>>12,Sd^=Sd<<29;return Sd^=++Cnt;}
void GetA(ul &a){a=Rd()%((1ull<<60)-2)+1;}
void GetLR(int &l,int &r){
    l=Rd()%n+1,r=Rd()%n+1;
    if (l>r) swap(l,r);
}
void init(){
    n=read(),q=read(),tp=read();
    scanf("%s",b+1);
    if (tp==0){
        for (int i=1;i<=n;i++) a[i]=read();
        for (int i=1;i<=q;i++){
            int l=read(),r=read();
            qu[r].push_back(Query(l,i));
        }
    }else{
        Sd=tp,Cnt=0;
        for (int i=1;i<=n;i++) GetA(a[i]);//,cout<<a[i]<<" ";puts("");
        for (int i=1;i<=q;i++){
            int l,r;
            GetLR(l,r);
            // cout<<l<<" "<<r<<"\n";
            qu[r].push_back(Query(l,i));
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
	init();
    for (int i=n;i>=1;i--){
        if (b[i]=='0') X.add(a[i],i);
        else{
            int now=X.query(a[i]);
            if (now==-1) T1.modify(1,1,n,i+1,n,i);
            else if (now>i+1) T1.modify(1,1,n,i+1,now-1,i);
        }
    }
    T2.build(1,1,n);
    for (int i=1;i<=n;i++){
        // cout<<"\\-=-------------"<<i<<"------------\n";
        if (b[i]=='1') T2.add(1,1,n,1,i,1);//,cout<<1<<" "<<i<<"\n";
        else{
            int now=T1.query(1,1,n,i);
            if (now) T2.add(1,1,n,1,now,1);//,cout<<1<<" "<<now<<"\n";
        }
        int len=qu[i].size();
        for (int j=0;j<len;j++)
            ans[qu[i][j].id]=T2.query(1,1,n,qu[i][j].l,i);
    }
    if (!tp) for (int i=1;i<=q;i++) cout<<ans[i]<<'\n';
    else{
        ui anss=0;
        for (int i=1;i<=q;i++) anss^=ans[i]*i;
        cout<<anss<<"\n";
    }
    return 0;
}
```

---

