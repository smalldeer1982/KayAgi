# 幻梦 | Dream with Dynamic

## 题目背景

“那以后见到她，会不会笑出来啊？”

“哈，一时半会见不到她的。”

小时候说要一起去看尘寰间的人间烟火，有人欣然接受，长大了说遗忘过去，那人也没有反驳。

其实吧，她们彼此明白，小时候在意的不是什么人间烟火，而是一起。

黑夜里，没有早晨的绯红，也褪去了天边的白光，留下的是她心头的散不去的灰暗。没有星光璀璨，没有满天繁星，她不在乎。她在乎的是那个人心中闪烁的星辰大海。

----

察觉所谓规则秘密，不过取悦于创世神明，早已知晓光明同黑暗般腥风血雨



## 题目描述

有一个长度为 $n$ 的序列，开始时第 $i$ 位为 $a_i$。你需要完成 $q$ 次操作：

- `A l r x`，对于所有的 $l\le i\le r$，令 $a_i\gets a_i+x$。
- `P l r`，对于所有的 $l\le i\le r$，令 $a_i\gets\operatorname{popcount}(a_i)$。
- `J p`，查询 $a_p$ 的值。

注：$\operatorname{popcount}(x)$ 为 $x$ 的二进制表示中 $1$ 的个数。

## 说明/提示

**【样例解释】**

- 开始时，$a = [1, 2, 3, 4, 5]$。
- 对询问 `J 2`，应回答 $a_2 = 2$。
- 操作 `A 2 4 3` 后，$a = [1, 5, 6, 7, 5]$。
- 对询问 `J 4`，应回答 $a_4 = 7$。
- 操作 `P 1 4` 后，$a = [1, 2, 2, 3, 5]$。
- 对询问 `J 3`，应回答 $a_3 = 2$。

---

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | 特殊限制 | 分值 |
| :----------: | :----------: | :----------: |
| 1 |$n,q\le 2000$| 3 |
| 2 |没有 `P` 操作| 7 |
| 3 |没有 `A` 操作| 15 |
| 4 |数据随机生成| 15 |
| 5 |无特殊限制| 60 |

对于全部数据，保证 $1\leq n\leq 3\times 10^5$，$1 \le q \le 10^6$，$1 \le l \le r \le n$，$1 \le p \le n$，$1\le a_i, x\le 10^9$。

子任务 4 的随机方式：

- 取 $n=3\times 10^5$，$q=10^6$；
- $a_i$ 从 $[1,10^9]$ 均匀随机选取；
- 对于每一个操作：
	- 从 3 种操作中均匀随机选取一个；
   - 如果是 `A` 操作，均匀随机从 $[1,n]$ 中选取 2 个整数，将较小的作为区间左端点，较大的作为区间右端点，再从 $[1,10^9]$ 中选取一个整数作为参数 `x`；
   - 如果是 `P` 操作，均匀随机从 $[1,n]$ 中选取 2 个整数，将较小的作为区间左端点，较大的作为区间右端点；
   - 如果是 `J` 操作，均匀随机从 $[1,n]$ 中选取一个整数作为参数 `p`。

---

**【提示】**

本题最大 I/O 量达到 30 MiB，请注意 I/O 效率。

## 样例 #1

### 输入

```
5 5
1 2 3 4 5
J 2
A 2 4 3
J 4
P 1 4
J 3
```

### 输出

```
2
7
2
```

# 题解

## 作者：ღꦿ࿐ (赞：24)

看到这个题的题解都很简略，所以我写详细点。

首先这个 $\operatorname{popcount}$ 函数的势能性质是不好分析的，因为 $a\geq p$ 时  $\operatorname{popcount}(a)$ 不一定大于 $\operatorname{popcount}(b)$， 所以只能考虑 $\operatorname{popcount}$ 的值域为 $O(\log V)$ 的性质，

线段树维护，将操作分为若干线段，接下来如果某个段在某个时刻被求过一次 $\operatorname{popcount}$，后面无论再怎么整段地加，它的值都可以表示成 $\operatorname{popcount}( \dots) + b$ 的形式，所以我们考虑在线段树上维护标记：

$f(\operatorname{popcount}(x+a))+b$，其中 $f(x)$ 是一个 值域和定义域均为 $O(\log V)$ 的函数，这样做的原因如下：

我们把操作序列形象地描述出来，加法是 $\texttt a$，区间做 $\operatorname{popcount}$ 是 $\texttt p$，那么操作序列例如
$$\texttt{apapppaaapaaa}$$

我们把加法合并成一次再按照 $p$ 分段：

$$\texttt{ ap| ap | ap | ap | ap | a}$$  

就变成了若干次 $\operatorname{popcount}(x+b)$ 的复合，这就是一个值域 $O(\log V)$ 的函数，从第二次开始定义域也变成了 $O(\log V)$，于是我们直接维护第一步函数的样子，暴力维护第二步开始以及后面函数的复合，单独计算最后的加法就可以做到了。

纯加法需要单独记录，它的值域不同。复合时也需要特判。


时间复杂度 $O(q\log n\log V)$ ，可以跑进 4s，做一些卡常性质的处理（如对于区间长度小于 $3\log V$ 的区间，再次下传标记是不优秀的，不如暴力）即可跑进 2s，目前最优解第二。


---

## 作者：jijidawang (赞：16)

刚才被人喷   
![](https://cdn.luogu.com.cn/upload/image_hosting/j6dxakbn.png)   
所以写详细一些。

令值域为 $V$，考虑一个数经过一次 popcount 操作后值域只剩 $\log V$，于是可以考虑把相邻两次 popcount 之间的操作缩起来 .


也就是线段树标记上维护一个 $\log V$ 长的置换 $f$，以及参数 $A,B,p$，表示原来的 $x$ 变成了
$$x'=\begin{cases}x+B&p=0\\f(\operatorname{popcount}(x+A))+B&p=1\end{cases}$$
考虑询问的形式是单点查询于是就只需要标记可以复合运算（也就是只需要下传） .

区间加直接改 $B$，区间 popcount 只需遍历置换 $f$ 求出值并更新即可，需要把   $B$ 的贡献给 $A$ .

于是总时间复杂度为 $\Theta((n+q)\log n\log nV)$ .

Bonus：区间求和同时间复杂度做法？

---

## 作者：yyyyxh (赞：15)

数据结构好题呢。

区间 $x\leftarrow f(x)$ 很不好做，然而这道题的突破口在于 $f(x)=\text{popcount}(x)$ 它值域仅有 $O(\log V)$。

当只有 `P` 操作时，我们可以维护一系列的值域很小的连续段，类似 ODT 一样合并连续段，把连续段个数当成势能，每次操作最多增加两个连续段，每次花费 $O(\log V)$ 的代价势能就会 $-1$，总复杂度 $O((n+q)\log V\alpha(n))$。

具体怎么合并连续段呢？发现在做过一次 $\text{popcount}$ 后再做 $\text{popcount}$ 相当于值域复合上一个长度为 $O(\log V)$ 的置换，并查集维护。

当拥有 `A` 操作时事情变得复杂起来，因为你每次要对一个连续段的区间打 tag，不知道可不可以用一颗平衡树去维护连续段，感觉这样太复杂就没顺着这个思路想下去。

既然常规做法做不了就去想块块，依然考虑给值域很小的块块打上标记维护置换，这次我们发现如果给块块打加法标记变得很快了，代价是维护置换的部分多了一个根号，平衡下复杂度大概可以做到 $O(q\sqrt{n\log V})$，显然跑不过所以没去实现。

发现我们上述做法并没有怎么依赖分块的性质，而主要是在“打加法标记”和“维护值域小的连续段”之间进行平衡，也就是说我们可以换用线段树。本质是我们原来维护极大的“值域很小的段”，现在强行把它劈成线段树/分块的形态方便我们打加法标记。

具体地来说，我们这次给线段树的一些节点打上“终止标记”，代表这个节点是一个“值域很小的连续段”。每次找出若干个需要被合并的连续段，暴力对里面的每一个值计算 $\text{popcount}$，运用标记永久化的思想把计算出来的长为 $O(\log V)$ 的置换记在这个点，然后把所有需要合并的连续段线段树上的 LCA 标记为新的终止节点。

记终止节点的个数是势能。区间修改时，终止节点被 `pushdown` 会标记两个新的终止节点，所以势能总量是 $O(q\log n)$ 级别的。每次花费 $O(\log V)$ 的代价合并一个终止节点，所以两种修改均摊都是 $O(\log n\log V)$ 的。单点查询标记永久化了所以是 $O(\log n)$ 的。

```cpp
#include <cstdio>
#define lc (p<<1)
#define rc (p<<1|1)
using namespace std;
//read()
typedef long long ll;
const int N=300003,Lg=50;
int n,q;
int a[N];
int per[N<<2][Lg];
ll tg[N<<2];
bool ex[N<<2];
void build(int p=1,int l=1,int r=n){
	for(int i=0;i<Lg;++i) per[p][i]=i;
	if(l==r){ex[p]=1;tg[p]=a[l];return;}
	ex[p]=0;tg[p]=0;
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
}
void proc(int p){
	for(int i=0;i<Lg;++i)
		per[p][i]=__builtin_popcountll(per[p][i]+tg[p]);
	tg[p]=0;
}
void pushdown(int p){
	if(ex[p]){
		for(int i=0;i<Lg;++i){
			per[lc][i]=per[p][per[lc][i]];
			per[rc][i]=per[p][per[rc][i]];
		}
		for(int i=0;i<Lg;++i) per[p][i]=i;
		ex[lc]=ex[rc]=1;ex[p]=0;
	}
	if(tg[p]){tg[lc]+=tg[p];tg[rc]+=tg[p];tg[p]=0;}
}
void upd(int p,int l,int r){
	if(ex[p]) return proc(p);
	pushdown(p);
	int mid=(l+r)>>1;
	upd(lc,l,mid);upd(rc,mid+1,r);
}
void update(int ll,int rr,int p=1,int l=1,int r=n){
	if(ll<=l&&r<=rr){upd(p,l,r);ex[p]=1;return;}
	pushdown(p);
	int mid=(l+r)>>1;
	if(ll<=mid) update(ll,rr,lc,l,mid);
	if(rr>mid) update(ll,rr,rc,mid+1,r);
}
void modify(int ll,int rr,int v,int p=1,int l=1,int r=n){
	if(ll<=l&&r<=rr){tg[p]+=v;return;}
	pushdown(p);
	int mid=(l+r)>>1;
	if(ll<=mid) modify(ll,rr,v,lc,l,mid);
	if(rr>mid) modify(ll,rr,v,rc,mid+1,r);
}
ll query(int x,int p=1,int l=1,int r=n){
	if(l==r) return per[p][0]+tg[p];
	int mid=(l+r)>>1;
	if(ex[p]){
		if(x<=mid) return per[p][query(x,lc,l,mid)]+tg[p];
		else return per[p][query(x,rc,mid+1,r)]+tg[p];
	}
	else{
		if(x<=mid) return query(x,lc,l,mid)+tg[p];
		else return query(x,rc,mid+1,r)+tg[p];
	}
}
int main(){
	n=read();q=read();
	for(int i=1;i<=n;++i) a[i]=read();
	build();
	for(int i=1;i<=q;++i){
		char cc;
		do cc=getchar();while(cc<'A'||cc>'Z');
		if(cc=='A'){
			int l=read(),r=read(),v=read();
			modify(l,r,v);
		}
		if(cc=='P'){
			int l=read(),r=read();
			update(l,r);
		}
		if(cc=='J') printf("%lld\n",query(read()));
	}
	return 0;
}
```


---

## 作者：JohnVictor (赞：12)

由于只用支持单点查询，我们维护的信息只用支持信息对信息可结合，信息对操作封闭。

考虑如下信息：$x\to f(\text{popcount}(x+a))+b$ 或者 $x\to x+b$，其中 $f$ 为定义域和值域都是不超过 $64$ 的正整数的函数。显然两种操作均为如下形式，因此只用再证明信息对信息可结合。

$x+b$ 形式的信息结合到正常信息上，只用将 $b$ 值加上相应的 $b$ 值；一般的信息结合到正常信息上，只用将 $f$ 变为 $g(\text{popcount}(f(x)+b))$ 即可，其中 $g$ 是结合上去的那个信息对应的 $f$。

```cpp
struct data{
	bool flg;//x->p(popcount(x+A))+B x->x+B
	ll a,b;
	short p[64]; 
	ll eval(ll x){
		if(flg)return p[bpc(x+a)]+b;
		else return x+b;
	}
}tag[N<<2];
void merge(data &x,data y){
	if(!y.flg)x.b+=y.b;
	else if(x.flg){
		vector<int>q(64);
		rep(i,0,63)q[i]=y.p[__builtin_popcountll(x.p[i]+x.b+y.a)];
		rep(i,0,63)x.p[i]=q[i];
		x.b=y.b;
	}
	else{
		y.a+=x.b;
		x=y;
	}
}
void clear(data &x){
	x.flg=0;x.a=x.b=0;
	rep(i,0,63)x.p[i]=0;
}

```

[完整代码](https://www.luogu.com.cn/paste/0ns9pnvq)。

---

## 作者：_Ch1F4N_ (赞：7)

提供一种需要卡常的分块写法。

首先看到 $\operatorname{popcount}$ 操作，便可以自然而然的想到在值域上做文章。

首先因为 $\operatorname{popcount} \leq \log x$。

所以可以想到对于一个序列来说，进行一次 $\operatorname{popcount}$ 操作后**至多有** $\log V$ 个不同的数字。

并且在对这个区间进行**全局**操作时不同数的数量**不增**。

因此考虑分块。

块内最开始用 $tag$ 记录加法操作。

对于块内如果有整块 $\operatorname{popcount}$ 操作则转换成记录每个值都变成了什么。

由于所有值不大于 $\log V$，所以量级是 $\log V$ 的。

类似于阈值分治的思想，不同类型的数据不同处理。

这样做复杂度是 $O(q \sqrt n \log V)$。

会超时。

不过还能改进。

这样做在保持分块的情况下~~不会写线段树的标记~~只能改进 $\operatorname{popcount}$。

但是我们可以用自带的函数。

这样写：

```cpp
inline int popcount(int n){
    return __builtin_popcountll(n);
}
```

然后考虑一些优化：

1. 记录块内最大值，若为 $1$ 则跳过 $\operatorname{popcount}$ 操作。

2. 每次 $\operatorname{popcount}$ 操作后去重降低后续操作复杂度。

3. 加法操作全部堆到 $tag$ 里，使得加法操作复杂度稳定在 $O(\sqrt n)$。 

如此再加上一定卡常就可以过了。

不过这样为什么可以过呢？

因为这个函数内部用自带的表以及二分实现，虽然都是 $\log$ 量级，但是二分理论上很难跑满。

所以复杂度还是 $O(q \sqrt n \log V)$，但是常数极小。

以下是比较丑的代码，各位大佬轻喷。

```cpp
#include<bits/stdc++.h>
#define int long long
#define max(x,y) (x>y?x:y)
using namespace std;
const int maxn = 3e5+1000;
const int maxw = 1000;
int B;
int a[maxn];
int sum;//块的数量
inline int popcount(int n){
    return __builtin_popcountll(n);
}
class block{
    public:
    int l,r;//块的起止位置
    int flag;//是否已经被 popcount 过
    pair<int,int> chifan[maxw];
    int tot;
    //popcount 后块内不同元素数量至多 50 个，所以暴力记录查询
    int tag;//加法标记
    void init();//初始化
    void maintain();//散块重构
    void change();//popcount 后转换记录方式
    void add(int x);
    void Pop();
}b[maxw];
inline void block::init(){
    flag=0;
    tot=0;
    tag=0;
}
void block::maintain(){
    if(flag==0){
        for(int i=l;i<=r;++i) a[i]=a[i]+tag;
        tag=0;
    }
    else{
        map<int,int> lwx;
        for(int i=1;i<=tot;i++) lwx[chifan[i].first]=chifan[i].second+tag;
        for(int i=l;i<=r;++i)
        {
            a[i]=lwx[a[i]];
        }
    }
    for(int i=1;i<=tot;++i) chifan[i].first=chifan[i].second=0;
    flag=tot=tag=0;
}
void block::change(){
    for(int i=l;i<=r;++i) a[i]=popcount(a[i]+tag);
    tag=0;
    flag=1;
    map<int,int> use;
    for(int i=l;i<=r;++i){
        int op=0;
        if(use[a[i]]==0)
            chifan[++tot]=make_pair(a[i],a[i]),use[a[i]]=1;
    }
}
inline void block::add(int x){
    tag+=x;
}
void block::Pop(){
    if(flag==0) change();
    else{
        int Maxval=0;
        for(int i=1;i<=tot;i++) Maxval=max(Maxval,chifan[i].second+tag);
        if(Maxval==1) return ;
        for(int i=1;i<=tot;++i)
            chifan[i].second=popcount(chifan[i].second+tag);
        int f=0;
        for(int i=2;i<=tot;i++)
            if(chifan[i].first!=chifan[i-1].first) f=1;
        if(f==0)
        {
            for(int i=2;i<=tot;i++) chifan[i].first=chifan[i].second=0;
            tot=1;
        }
    }
    tag=0;
}
void changeA(int l,int r,int x){
    int bl=l/B+1;
    if(l-l/B*B==0) bl--;
    int br=r/B+1;
    if(r-r/B*B==0) br--;
    for(int i=bl+1;i<br;++i)
        b[i].add(x);

    if(bl!=br){
        b[bl].maintain();
        b[br].maintain();
        for(int i=l;i<=b[bl].r;++i) a[i]+=x;
        for(int i=b[br].l;i<=r;++i) a[i]+=x;
    }
    else{
        b[bl].maintain();
        for(int i=l;i<=r;i++) a[i]+=x;
    }
}
void changeB(int l,int r){
    int bl=l/B+1;
    if(l-l/B*B==0) bl--;
    int br=r/B+1;
    if(r-r/B*B==0) br--;
    for(int i=bl+1;i<br;++i)
        b[i].Pop();
    
    if(bl!=br){
        b[bl].maintain();
        b[br].maintain();
        for(int i=l;i<=b[bl].r;++i) a[i]=popcount(a[i]);
        for(int i=b[br].l;i<=r;++i) a[i]=popcount(a[i]);
    }
    else{
        b[bl].maintain();
        for(int i=l;i<=r;++i) a[i]=popcount(a[i]);
    }
}
int question(int x){
    int pos=x/B+1;
    if(x-x/B*B==0) pos--;
    if(b[pos].flag==0) return a[x]+b[pos].tag;
    else{
        for(int j=1;j<=b[pos].tot;++j)
            if(a[x]==b[pos].chifan[j].first) return b[pos].chifan[j].second+b[pos].tag;
    }
}
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}

int n,q;
signed main(){
    n=read();
    q=read();
    B=sqrt(n);
    for(int i=1;i<=n;i++){
        a[i]=read();
    }
    for(int i=1;i<=n;i=i+B){
        b[++sum].l=i;
        b[sum].r=min(n,i+B-1);
        b[sum].init();
    }
    for(int i=1;i<=q;i++){
        char op;
        op=getchar();
        while(op<'A'||op>'Z')
        op=getchar();
        if(op=='A'){
            int l,r,x;
           l=read();
           r=read();
           x=read();
            changeA(l,r,x);
        }
        else if(op=='P'){
            int l,r;
            l=read();
            r=read();
            changeB(l,r);
        }
        else{
            int x;
            x=read();
            write(question(x));
            putchar('\n');
        }
    }
    return 0;
}
```

---

## 作者：dAniel_lele (赞：6)

注意到一个区间要么没有 `P` 操作，要么只会有至多 $\log V$ 种数。

考虑线段树，对于每个节点维护 $add$ 表示增加量的懒标记，$tp$ 表示是否有过 `P` 操作，$b_{i=0\sim \log V}$ 表示 $\operatorname{popcount}(x+add)=i$ 时，这个节点的第一个 `P` 以后的懒标记会将 $x$ 变为哪个数。

懒标记下传时需要优先判断两边的 $tp$ 是 $0$ 还是 $1$。具体细节~~留给读者自行推倒~~可以见代码。

总复杂度 $O(n\log n\log V)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int a[1000005];
struct node{
	int tp,add,b[51];
};
node addx(node t,int x){//A 操作，将一个区间加上 x
	if(t.tp==0){
		t.add+=x;
		return t;
	}
	for(int i=0;i<=50;i++) t.b[i]+=x;
	return t;
}
node addy(node t){//P 操作，将一个区间变为 popcount
	if(t.tp==0){
		t.tp=1;
		for(int i=0;i<=50;i++) t.b[i]=i;
		return t;
	}
	for(int i=0;i<=50;i++) t.b[i]=__builtin_popcountll(t.b[i]);
	return t;
}
node merge(node x,node y){//pushdown 时将两个 node 合并
	if(y.tp==0){
		return addx(x,y.add);
	}
	if(x.tp==0){
		y.add+=x.add;
		return y;
	}
	for(int i=0;i<=50;i++) x.b[i]=y.b[__builtin_popcountll(x.b[i]+y.add)];
	return x;
}
struct sgt{
	node f[1200005];
	void pushdown(int i){
		f[i*2]=merge(f[i*2],f[i]);
		f[i*2+1]=merge(f[i*2+1],f[i]);
		f[i].add=f[i].tp=0;
	}
	void change1(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			f[i]=addx(f[i],cg);
			return ;
		}
		pushdown(i);
		if(ql<=mid) change1(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change1(i*2+1,mid+1,r,ql,qr,cg);
	}
	void change2(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr){
			f[i]=addy(f[i]);
			return ;
		}
		pushdown(i);
		if(ql<=mid) change2(i*2,l,mid,ql,qr);
		if(qr>mid) change2(i*2+1,mid+1,r,ql,qr);
	}
	node qry(int i,int l,int r,int pos){
		if(l==r) return f[i];
		pushdown(i);
		if(pos<=mid) return qry(i*2,l,mid,pos);
		return qry(i*2+1,mid+1,r,pos);
	}
}tree;
signed main(){
	int n,q; cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	while(q--){
		char c; cin>>c;
		if(c=='J'){
			int p; cin>>p;
			node tmp=tree.qry(1,1,n,p);
			if(tmp.tp==0) cout<<a[p]+tmp.add<<"\n";
			else cout<<tmp.b[__builtin_popcountll(a[p]+tmp.add)]<<"\n";
		}
		else if(c=='A'){
			int l,r,x; cin>>l>>r>>x;
			tree.change1(1,1,n,l,r,x);
		}
		else{
			int l,r; cin>>l>>r;
			tree.change2(1,1,n,l,r);
		}
	}
	return 0;
}
```

---

## 作者：Usada_Pekora (赞：6)

以下用 $\mathrm{popc}$ 代替 $\mathrm{popcount}$。

先考虑全局加全局 $\mathrm{popc}$ 怎么做。

维护一个 `tag` 表示目前全局加了多少，于是加法变成了 $O(1)$ 的。

$\mathrm{popc}$ 直接暴力做就好了，只有第一次是 $O(n)$ 的，做完第一次 $\mathrm{popc}$ 以后至多有 $\log V$ 个不同的数，维护一个 $\log V$ 长的映射，后面的 $\mathrm{popc}$ 直接在这个映射上修改就好了。

查询取决于你用什么东西去维护这个映射，可以做到 $O(1),O(\log\log V), O(\log V)$ ，这不重要，不作展开。

然后你发现这个东西就可以搬到一些数据结构上维护了，当然线段树上怎么维护我也不会，所以我要写分块。

整块的维护我们按上面的做法维护就好了，关键是散块，对散块的加操作会破坏掉整个映射（可能有 $a_i=a_j$，但是你需要对 $a_j$ 加上一个数），维护映射的 $\mathrm{popc}$ 操作会破坏掉加法的 `tag`。

于是你要对这个散块把该传的标记都传下去，然后维护一个新的映射，这个过程是 $O(B+\log V)$ 的，$B$ 是块长。

然后就可以分析复杂度了。

加法是 $O(q(B+\log V+\frac{n}{B}))$。

对于 $\mathrm{popc}$ 考虑分析势能，变颜色的复杂度是 $O(B+\log V)$（第一次 $\mathrm{popc}$ 或者散块重构），然后最多变 $O(q)$ 次，所以是 $O(q(B+\log V))$，直接 $\mathrm{popc}$ 的复杂度是 $O(q\frac{n}{B}\log V)$。

查询不是瓶颈，反正不高于 $O(q\log V)$。

同时还解决了区间求和。

理论上 $B=\sqrt{n\log V}$ 是最优的，此时复杂度 $O(q\sqrt{n\log V})$，当然性能瓶颈在于重构，所以小一点总是好的。


```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const int N = 3e5 + 5, S = 389, B = 777, LG = 51;
int n, m, bel[N], st[B], ed[B], siz[B], tmp[LG];
bool pope[B];
ll a[N], tag[B], buk[LG];
pll ys[B][LG];
inline void rebuild(int bid) {
	if (!pope[bid]) {
		for (int i = st[bid]; i <= ed[bid]; i++)
			a[i] += tag[bid];
	} else {
		for (int i = 1; i <= siz[bid]; i++)
			buk[ys[bid][i].fi] = ys[bid][i].se + tag[bid];
		for (int i = st[bid]; i <= ed[bid]; i++)
			a[i] = buk[a[i]];
	}
	pope[bid] = false;
	tag[bid] = 0;
}
inline void mod_add(int l, int r, ll k) {
	int p = bel[l], q = bel[r];
	if (p == q) {
		rebuild(p);
		for (int i = l; i <= r; i++)
			a[i] += k;
	} else {
		rebuild(p);
		for (int i = l; i <= ed[p]; i++)
			a[i] += k;
		for (int i = p + 1; i < q; i++)
			tag[i] += k;
		rebuild(q);
		for (int i = st[q]; i <= r; i++)
			a[i] += k;
	}
}
inline void mod_pop(int l, int r) {
	int p = bel[l], q = bel[r];
	if (p == q) {
		rebuild(p);
		for (int i = l; i <= r; i++)
			a[i] = __builtin_popcountll(a[i]);
	} else {
		rebuild(p);
		for (int i = l; i <= ed[p]; i++)
			a[i] = __builtin_popcountll(a[i]);
		for (int i = p + 1; i < q; i++) {
			if (!pope[i]) {
				memset(tmp, -1, sizeof tmp), siz[i] = 0;
				for (int j = st[i]; j <= ed[i]; j++) {
					a[j] = __builtin_popcountll(a[j] + tag[i]);
					tmp[a[j]] = a[j];
				}
				for (int j = 0; j < LG; j++)
					if (~tmp[j])
						ys[i][++siz[i]] = pll(tmp[j], tmp[j]);
			} else {
				for (int j = 1; j <= siz[i]; j++)
					ys[i][j].se = __builtin_popcountll(ys[i][j].se + tag[i]);
			}
			pope[i] = true;
			tag[i] = 0;
		}
		rebuild(q);
		for (int i = st[q]; i <= r; i++)
			a[i] = __builtin_popcountll(a[i]);
	}
}
inline ll query(int x) {
	int p = bel[x];
	if (!pope[p])
		return a[x] + tag[p];
	return lower_bound(ys[p] + 1, ys[p] + siz[p] + 1, pll(a[x], 0))->se + tag[p];
}
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
//	freopen("test.in", "r", stdin);
//	freopen("dsjaikjf.out", "w", stdout);
	cin >> n >> m;
//	if (n > 2000) {
//		return 0;
//	}
//	ofstream fout("fdsa.out");
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	const int sq = sqrt(n / 2);
	for (int i = 1; i <= n; i++)
		bel[i] = (i - 1) / sq + 1;
	for (int i = 1; i <= bel[n]; i++)
		st[i] = ed[i - 1] + 1, ed[i] = st[i] + sq - 1;
	ed[bel[n]] = n;
	while (m--) {
		char op;
		int l, r;
		ll k;
		cin >> op;
		if (op == 'A') {
			cin >> l >> r >> k;
			mod_add(l, r, k);
		} else if (op == 'P') {
			cin >> l >> r;
			mod_pop(l, r);
		} else {
			cin >> l;
			cout << query(l) << '\n';
		}
//		fout << op << ": ";
//		for (int i = 1; i <= n; i++)
//			fout << query(i) << ' ';
//		fout << endl;
	}
	return 0;
}
```

---

## 作者：MeteorFlower (赞：6)

大家好，我是根号数据结构爱好者。所以我用分块 A 了此题。

观察本题操作，发现区间加和单点查询都是可以简单地用分块来维护的。但是区间 popcnt 是个很新颖的东西。（也许是我题做得太少了吧。）赛时我以为是个什么神秘的 Trie 树然后一直想不出来。赛后听说 LHQing 用分块过了本题然后就滚去问他了。感谢 LHQing 大帝的耐心指导。

容易发现 $\text{popcnt}(x)<64$。由此我们可以得到一种做法——当某个块被整块 popcnt 后，将其去重只会剩下 $64$ 种以下的元素。把这些去重后的元素存起来，之后再对该块进行整块操作的时候，只需要对这几个元素进行修改即可。更详细地说，将第一次被整块 popcnt 后该块中每一个元素的值（下文称为代表值）与继续执行其它整块操作后的值（下文称为实际值）组成一组映射。修改时直接暴力枚举，查询时直接查询映射即可。

来分析一下复杂度。不考虑散块修改。当一个块被第一次整块 popcnt 前，整块加是单块 $O(1)$ 的。第一次被 popcnt 时单块复杂度是 $O\left(\sqrt n\right)$ 的，但这种情况只会发生 $O\left(\sqrt n\right)$ 次。之后执行的所有整块操作都是单块 $O\left(\log V\right)$ 的。因此总复杂度是 $O\left(m\sqrt n\log V\right)$ 。

然而散块修改会破坏映射的一一对应关系。换句话说，散块修改会使两个相同的代表值所对应的实际值不同。所以我们不得不用此块的映射更新自身所有元素，然后将映射清空再执行修改。之后如果要将这个块再整块 popcnt 的话就不得不 $O\left(\sqrt n\right)$ 地重构映射。这样时间复杂度不就不对了吗？

实际上我们可以用类似势能分析的方法来证明散块修改不会过大影响总复杂度。设每块初始时势能为 $1$，散块修改会使该块的势能 $+1$，整块 popcnt（重构映射）会使该块的势能 $-1$。容易发现，每次修改会使中间的所有整块势能 $-1$，只有两旁 $O(1)$ 个散块的势能会 $+1$。因此最大总势能就控制在 $O(m)$ 的级别。所以重构映射的总复杂度是 $O\left(m\sqrt n\right)$。

综上所述，总时间复杂度是 $O\left(m\sqrt n\log V\right)$（忽略低次项），空间复杂度是 $O\left(n+\sqrt n\log V\right)$。

PS：可以通过逐块处理来卡 cache。这样能使存映射的两个数组大小均为 64，可以卡进 cache。应该会使速度显著提升。（但是我没写不逐块处理的代码不知道具体提升了多少。）


---

## 作者：honglan0301 (赞：2)

## 题意简述
你需要对 $n$ 个数的数列进行 $q$ 次操作，其中操作分为以下三种。  
1. 区间加 $k$。
2. 区间变为 $\text{popcount}$，即二进制表示中 $1$ 的个数。
3. 单点求值。

## 题目分析

看起来不太能一只 $\log$, 所以考虑分块。区间加是简单的，不做讨论，区间 $\text{popcount}$ 虽然不太好直接做，但它有个很好的性质是一次 $\text{popcount}$ 操作会使得值域 $V$ 变为 $\log V$。于是我们考虑在整块的第一次 $\text{popcount}$ 时暴力操作，之后就只需对块内的至多 $\log$ 种数维护其变为的值，这是容易的。

分析时间复杂度，设 $n,q$ 同级，块长为 $m$, 单次 $\text{popcount}$ 为 $\log\log V$。则散块加为 $nm$, 散块 $\text{popcount}$ 为 $nm\log\log V$, 整块区间加为 ${n^2}\over m$, 整块 $\text{popcount}$ 为 ${n^2\log V\log\log V}\over m$。故理论块长 $m=\sqrt {n\log V}$ 时取得最优时间复杂度 $O(n\sqrt{n\log V}\log\log V)$, 但是区间内数的数量很难跑满（且前几个子任务各有不同限制），所以块长直接取 $\sqrt n$ 更优，可以较快地通过本题（这能跑到最优解第二是我没想到的）。

## 代码

记得加快读，有一些小优化可看代码。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define popcount(x) __builtin_popcountll(x)
const int B=555;

int n,q,cntk,u,v,w,zt[51],K[300001]; unsigned long long a[300001];
char s;

struct kuai
{
    int l,r,fgt,to[51],num[51],cntt; unsigned long long addt;
    void maintain()
    {
        if(!fgt) for(int i=l;i<=r;i++) a[i]+=addt;
        else for(int i=l;i<=r;i++) a[i]=to[num[a[i]]]+addt;
        addt=fgt=cntt=0;
    }
    void cz_add(unsigned long long k) {addt+=k;}
    void cz_popc()
    {
        if(!fgt)
        {
            memset(zt,0,sizeof(zt));
            for(int i=l;i<=r;i++) {a[i]=popcount(a[i]+addt); zt[a[i]]=1;}
            for(int i=1;i<=50;i++) if(zt[i]) {to[++cntt]=i; num[i]=cntt;}
        }
        else for(int i=1;i<=cntt;i++) to[i]=popcount(to[i]+addt);
        addt=0; fgt=1;
    }
}b[555];

void change_add(int x,int y,int k)
{
    int kl=K[x],kr=K[y];
    if(kl==kr) {b[kl].maintain(); for(int i=x;i<=y;i++) a[i]+=k;}
    else
    {
        for(int i=kl+1;i<=kr-1;i++) b[i].cz_add(k);
        b[kl].maintain(); b[kr].maintain();
        for(int i=x;i<=b[kl].r;i++) a[i]+=k;
        for(int i=b[kr].l;i<=y;i++) a[i]+=k;
    }
}
void change_popc(int x,int y)
{
    int kl=K[x],kr=K[y];
    if(kl==kr) {b[kl].maintain(); for(int i=x;i<=y;i++) a[i]=popcount(a[i]);}
    else
    {
        for(int i=kl+1;i<=kr-1;i++) b[i].cz_popc();
        b[kl].maintain(); b[kr].maintain();
        for(int i=x;i<=b[kl].r;i++) a[i]=popcount(a[i]);
        for(int i=b[kr].l;i<=y;i++) a[i]=popcount(a[i]);
    }
}
unsigned long long ask(int x)
{
    int kx=K[x];
    if(!b[kx].fgt) return a[x]+b[kx].addt;
    else return b[kx].to[b[kx].num[a[x]]]+b[kx].addt;
}

signed main()
{
    cin>>n>>q; for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) K[i]=(i-1)/B+1;
    for(int i=1;(i-1)*B+1<=n;i++) {b[i].l=(i-1)*B+1; b[i].r=min(n,i*B);}
    for(int i=1;i<=q;i++)
    {
        cin>>s;
        if(s=='A') {cin>>u>>v>>w; change_add(u,v,w);}
        else if(s=='P') {cin>>u>>v; change_popc(u,v);}
        else {cin>>u; cout<<ask(u)<<endl;}
    }
}
```


---

