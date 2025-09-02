# 壊れた機器 (Broken Device)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2017/tasks/joisc2017_e



# 题解

## 作者：novax (赞：9)

非常有趣的通信题。

再次叙述题意：你需要实现两个函数 ``void Anna(int N,long long X,int K,int P[])`` 和 ``long long Bruno(int N,int A[])``，实现以下功能：``Anna`` 将得到一个长为 $n=150$ 的空白序列和一个不大于 $10^{18}$ 的数字 $x$，这个函数需要为每一位赋予一个 $0$ 或 $1$ 的值来保存 $x$，其中序列中有 $k$ 个位置是损坏的：无论设置为 $0$ 还是 $1$，这些位置的值都恒为 $0$，$p$ 数组保存着这些位置的下标；``Bruno`` 将得到 ``Anna`` 操作后的序列，这个函数需要依靠这个序列来还原 ``Anna`` 得到的数字 $x$。

#### 思路

直接二进制存储肯定是不可行的，因为损坏的位置不能保存任何信息。

序列长度是 $150$，而需要保存的信息有 $60$ 位。考虑以两位为单位保存信息。将序列分成 $75$ 段，对于每一段，如果两个格子中有一个损坏了，就将这两个格子都设置为 $0$，不保存任何信息；否则使用两个二进制位的 $01/10/11$ 分别表示一个三进制位 $0/1/2$，使用三进制来存储 $x$。计算一下，$x_{\max}=3^{\frac{150}{2}-40}=3^{35}\approx 5\times 10^{16}$，所能保存的最大值小于本题要求，但这个做法可以在本题获得 $85$ 分的好成绩。

以上做法每个损坏位最多都会使一个正常位不保存任何信息，这些位置被浪费了。

考虑更高效的存储方式。以三位为单位保存信息，将序列分成 $50$ 份。这样对于每一段，只要损坏的位数小于两个，就都还能保存一些信息。对于损坏了两位或三位的段，我们还是直接全部设置为 $0$，只使用损坏了一位和全部完好的段存储信息。

共有 $50$ 段，那么最坏情况会有 $20$ 个不保存任何信息的段或有 $40$ 个损坏了一位的段。如果损坏了一位的段可以保存一位二进制信息而没有损坏的段可以保存两位二进制信息，那么在任何情况下这个序列都可以保存 $60$ 位二进制信息，恰能将 $x$ 存下。

考虑构造这样一种方案。

若三位中有至少两位损坏，则将三位全部设置为 $0$，表示这三位不记录任何信息。

然后将 $001/010/011/100/101/110/111$ 分别赋予保存的内容：

$$011/100 \rightarrow 1$$

$011/100$ 用来表示一位二进制 $1$，当前段有一个损坏时，使用这两种总能表示出来，存储了一位信息。

$$001 \rightarrow 00$$

$$110 \rightarrow 01$$

$$101 \rightarrow 10$$

$$111 \rightarrow 11$$

以上四种情况分别对应 $00/01/10/11$，当前段没有损坏时，可以存储两位二进制信息。

$$010 \rightarrow 0$$

$010$ 用来表示一位二进制 $0$。这样有一个问题：能保存信息的三位二进制数只有 $7$ 种，需要的对应关系却有 $8$ 种。当前段的中间点损坏时就不能表示了。

那么考虑复用前面的对应关系 $001 \rightarrow 00$ 和 $101 \rightarrow 10$。若当前段的中间点损坏了，那就让当前段也保存两位信息，恰好前面构造的方案中存下 $00$ 和 $10$ 的方案中间位都是 $0$，因此可以在这一段同时保存上一位的信息。

这样我们就达成了前面的目标，可以获得 $100$ 分的成绩。

#### 本题通信相关

本题在 AtCoder 的评测和计分方式异乎传统题。只要成功完成通信即可获得 $0$ 分的 AC。洛谷爬回的提交记录只会显示是否 AC 而不会显示分数。

本题要求所有点的值都恰好被设置一次，即使是损坏的格子也必须设置一个值。

#### 代码

```
#include "Broken_device_lib.h"
void Anna(int N,long long X,int K,int P[])
{
	int i,j,w,b[3],ax;
	long long now=X;
	for(i=0;i<N/3;i++)
	{
		w=0;b[0]=b[1]=b[2]=0;
		for(j=0;j<K;j++)
		{
			if(P[j]==3*i) b[0]=1,w++;
			else if(P[j]==3*i+1) b[1]=1,w++;
			else if(P[j]==3*i+2) b[2]=1,w++;
		}
		if(w>=2)
		{
			Set(3*i,0),Set(3*i+1,0),Set(3*i+2,0);
			continue;
		}
		if(w==1)
		{
			ax=now%2;
			if(ax==0)
			{
				if(b[1]!=1)
				{
					Set(3*i+1,1),Set(3*i,0),Set(3*i+2,0);
					now>>=1;
				}
				else
				{
					ax=now%4;
					if(ax==0) Set(3*i+2,1),Set(3*i,0),Set(3*i+1,0);
					else if(ax==2) Set(3*i,1),Set(3*i+2,1),Set(3*i+1,0);
					now>>=2;
				}
			}
			else if(ax==1)
			{
				if(b[0]!=1) Set(3*i,1),Set(3*i+1,0),Set(3*i+2,0);
				else Set(3*i+1,1),Set(3*i+2,1),Set(3*i,0);
				now>>=1;
			}
		}
		if(w==0)
		{
			ax=now%4;
			if(ax==0) Set(3*i+2,1),Set(3*i,0),Set(3*i+1,0);
			else if(ax==1) Set(3*i,1),Set(3*i+1,1),Set(3*i+2,0);
			else if(ax==2) Set(3*i,1),Set(3*i+2,1),Set(3*i+1,0);
			else if(ax==3) Set(3*i,1),Set(3*i+1,1),Set(3*i+2,1);
			now>>=2;
		}
	}
}
long long Bruno(int N,int A[])
{
	int i,j,w,b[3],ax;
	long long ret=0;
	for(i=N/3-1;i>=0;i--)
	{
		ax=(A[i*3+2]<<2)+(A[i*3+1]<<1)+A[i*3];
		if(ax==0) continue;
		else if(ax==1) ret<<=1,ret|=1;
		else if(ax==2) ret<<=1;
		else if(ax==3) ret<<=2,ret|=1;
		else if(ax==4) ret<<=2;
		else if(ax==5) ret<<=2,ret|=2;
		else if(ax==6) ret<<=1,ret|=1;
		else if(ax==7) ret<<=2,ret|=3;
	}
	return ret;
}
```


---

## 作者：10circle (赞：7)

审题解的时候看见有个这题题解，瞄了一眼，看到一个『以两位为单位保存信息』，于是就感觉很会了！是好题。

首先，考虑将长度 $150$ 的序列每两位分一段，每一段若有一个位坏掉就都是 $0$（称之为坏段），否则以三进制存储信息。这样的话，最多能有 $40$ 个坏段，则只能表示出 $3^{35}$ 级别的数，显然无法通过。

考虑随机化：让 Anna 和 Bruno 都使用同一个随机排列来遍历数组。我采用的是标准库里的 `mt19937`，如果种子一样，生成的序列也一样。也可以直接打表出一个随机排列。

这样可以使一些坏段拥有两个坏位，就减少了坏段的数量。~~期望懒的算了~~，但是这样就可以获得 $90$ 分，通过 $L \le 38$ 的测试点。

考虑将坏段利用起来：如果一个坏段有一个好位，并且将这个好位置为 $1$ 时，它和 $X$ 当前三进制最低位的表示恰好相同，那么就可以利用上这个坏段表示三进制的一位。

~~期望还是懒的算了~~，但是这样就可以通过。因为是随机的顺序，所以 $K$ 一定时任何数据对它都是一样的，所以能反映出它正确率是很高的。

在代码实现中，三进制的表示为 $0 \to 10$、$1 \to 11$、$2 \to 01$。

[代码](https://qoj.ac/submission/100008)。

---

## 作者：xiezheyuan (赞：2)

2025 年的第一篇题解！介绍一个今天好题分享中的一个更加优秀的做法。

## 简要题意

这是一道通信题。

你需要实现两个函数：

- `void Anna(int N,long long X,int K,int P[])` 表示有一个长度为 $N$ 的 $01$ 序列 $a$ 和一个整数 $X$，你需要用序列 $a$ 记录 $X$，但是其中 $K$ 个位置 $P_0,P_1,\cdots,P_{K-1}$ 是损坏的，这些位置恒为 $0$。你可以调用 `void Set(int pos, int val)` 来设定 $a_{\mathrm{pos}}$ 为 $\mathrm{val}$。
- `long long Bruno(int N,int A[])` 给定一个长度为 $N$ 的序列 $A$，表示 `Anna` 函数中记录的序列 $a$，你需要返回记录对象 $X$ 的值。注意损坏的位置不会给出。

$N=150,1\leq X\leq 10^{18},1\leq K\leq 40$。一次测试会将你的 `Anna` 函数和 `Bruno` 函数调用 $Q=10^3$ 次，因此请注意时间复杂度。

## 思路

第一次做通信题。

常规的做法有很多，其中一种的大致思路是将相邻的两位看成一组，如果一组中某位被损坏了，就让这两个位置都设定为 $0$，否则有 $11,10,01$ 三种情况，可以看成一个三进制数表示。另外全都设定为 $0$ 很浪费，如果只有一位损坏，可以考虑利用剩下的一位试图编码 $10,01$。

这样的做法在精心设计的数据下可能会炸，考虑随机化。我们随机生成一个排列来替代原本的 $a$ 的下标即可。由于随机数种子固定，生成的随机数也是固定的，所以可以在两个函数中均使用相同的种子。

这样子可以通过 $N=150$，但是如果我们要求 $N=120$ 呢？

考虑异或线性基的性质，我们给每个位置随机生成一个权值 $w_i$。然后将没有破坏的位置插入到线性基中。这样 $X$ 有极大概率在这一组基的张成空间内（后文会计大致估计这个概率），那么可以找到一组线性组合。

具体实现的话将极大线性无关组的值是如何由权值构造的记录下来（用一个 `vector`）即可。注意这个 `vector` 可能会有多次重复，只保留奇数次重复。

注意到这组线性组合一定可以写成若干个没有破坏的位置的权值的异或和，于是可以将这些位置全部修改为 $1$，其余的位置全部修改为 $0$。

至于 `Bruno` 函数，我们可以使用相同的随机数种子，生成相同的权值，将 $a$ 为 $1$ 的位置的权值异或起来即可。


现在我们来对这个做法的正确率进行估计。

记 $X$ 的二进制表示最多有 $d$ 位，则一组秩为 $z$ 的基，可以将 $X$ 线性表出的概率是：

$$
P(z,d)=\frac{2^d-2^z}{2^d}
$$

证明是平凡的，因为秩为 $z$ 的基，根据基的线性无关性，可以表示 $2^z$ 个数，而至多 $d$ 位二进制数，有 $2^d$ 个。

考虑随机生成权值，相当于每次维护一个数 $z$ 表示当前基的大小，初始时 $z=0$，每次有 $P(z,d)=\frac{2^d-2^z}{2^d}$ 的概率（本题 $d=60$）可以令 $z\leftarrow z+1$，求 $n-k$ 次操作后 $z$ 的期望。

这个期望求解比较困难，改为求到达 $z=d$ 的期望次数，即：

$$
\sum_{i=0}^{d-1}\frac{2^d}{2^d-2^i}=\sum_{i=0}^{d-1}\frac{1}{1-2^{i-d}}\approx \sum_{i=0}^{d-1}1+2^{i-d}=d+2^{-d}\sum_{i=0}^{d-1}2^{i}=O(d)
$$

而我们可以进行 $n-k$ 次操作，这是绰绰有余的。

## 代码

[UOJ Submission](https://uoj.ac/submission/728588)。

```cpp
#include <bits/stdc++.h>
#include "Broken_device_lib.h"
using namespace std;

using i64 = long long;
void Set(int pos, int bit);

i64 basis[65];
vector<int> ids[65];

void deal(vector<int>& vct){
    map<int,int> mp;
    for(int i : vct) mp[i]++;
    vct.clear();
    for(auto [i, v] : mp){
        if(v & 1) vct.emplace_back(i);
    }
}

void insert(i64 x, int id){
    vector<int> vct; vct.emplace_back(id);
    for(int i=62;~i;i--){
        if(!(x & (1ll << i))) continue;
        if(!basis[i]){
            basis[i] = x, ids[i] = vct;
            deal(ids[i]);
            return;
        }
        x ^= basis[i];
        for(int j : ids[i]) vct.emplace_back(j);
    }
}

auto query(i64 x){
    vector<int> vct;
    for(int i=62;~i;i--){
        if(!(x & (1ll << i))) continue;
        x ^= basis[i];
        for(int j : ids[i]) vct.emplace_back(j);
    }
    deal(vct);
    map<int,bool> mp;
    for(int i : vct)  mp[i] = true;
    return mp;
}

void Anna(int n, i64 x, int k, int p[]){
    mt19937 rnd(20090328); // 据说用自己的生日作为随机数种子，会有好运！
    uniform_int_distribution<i64> dist(2, i64(1e18));
    map<int,bool> broken;
    for(int i=0;i<k;i++) broken[p[i] + 1] = true;
    for(int i=1;i<=n;i++){
        i64 v = dist(rnd);
        if(!broken[i]) insert(v, i);
    }
    auto res = query(x);
    for(int i=1;i<=n;i++){
        if(res[i]) Set(i - 1, 1);
        else Set(i - 1, 0);
    }
    for(int i=60;~i;i--) basis[i] = 0, ids[i].clear();
}

i64 Bruno(int n, int a[]){
    mt19937 rnd(20090328);
    uniform_int_distribution<i64> dist(2, i64(1e18));
    i64 ans = 0;
    for(int i=0;i<n;i++){
        i64 v = dist(rnd);
        if(a[i]) ans ^= v;
    }
    return ans;
}

// Written by xiezheyuan
```

---

## 作者：DaiRuiChen007 (赞：1)

# JOISC2017E 题解



## 题目大意

> 通信题：
>
> `Encoder.cpp`：输入一个非负整数 $x$，输出到一个 01 串 $S$ 中并传递给 `Decive.cpp`，已知 $S$ 中第 $p_1,p_2,\dots,p_k$ 位会在传递给 `Device.cpp` 之前被赋值成  $0$。
>
> `Device.cpp`：输入被修改后的 01 串 $S$，求出 $x$ 的值。
>
> 数据范围：$x\le 10^{18},|S|=150,k\le 40$。



## 思路分析

考虑以相邻两位保存信息，只要 $i,i+1$ 有一个位被破坏那么设为 $00$，剩下的 $\{01,10,11\}$ 分别对应三进制下的数码 $\{0,1,2\}$，以 $3$ 进制的方式传递 $x$。

最坏情况下，我们剩下 $35$ 组数码表示 $x$，表出数的最大值为 $3^{35}\approx 5\times 10^{16}$，考虑进一步优化：

首先可以通过随机化一个 $1\sim|S|$ 的排列来得到相邻两位的分组，此时每组数码可用的概率 $p$ 约为 $\binom{|S|-2}{k}\div\binom{|S|}{k}\approx 0.536$，最终传递上界的期望为 $3^{75p}\approx 1.57\times 10^{19}$，在随机化效果不好时依然有概率无法通过本题。

考虑一个优化：在只有第 $i$ 位被破坏时，依然可以表示 $01$，同理只有第 $i+1$ 被破坏时依然可以表示 $10$，因此这两种情况也能被利用，此时 $p=\binom{|S|-2}{k}\div\binom{|S|}{k}+\frac 23\binom{|S|-2}{k-1}\div\binom{|S|}k\approx 0.6677$，标出上界的期望被进一步优化到 $7.82\times 10^{23}$，足够通过本题。



## 代码呈现

```cpp
#include<bits/stdc++.h>
#include "Broken_device_lib.h"
#define ll long long
using namespace std;
void Anna(int N,ll X,int k,int P[]) {
	mt19937 RndEng(19260827);
	vector <int> idx(N),mark(N,0);
	for(int i=0;i<k;++i) mark[P[i]]=1;
	iota(idx.begin(),idx.end(),0);
	shuffle(idx.begin(),idx.end(),RndEng);
	for(int i=0;i<N;i+=2) {
		int u=idx[i],v=idx[i+1];
		if(mark[u]&&mark[v]) {
			Set(u,0),Set(v,0);
		} else if(mark[u]) {
			if(X%3==0) X/=3,Set(u,0),Set(v,1);
			else Set(u,0),Set(v,0);
		} else if(mark[v]) {
			if(X%3==1) X/=3,Set(u,1),Set(v,0);
			else Set(u,0),Set(v,0);
		} else {
			int d=X%3; X/=3;
			if(d==0) Set(u,0),Set(v,1);
			if(d==1) Set(u,1),Set(v,0);
			if(d==2) Set(u,1),Set(v,1);
		}
	}
}
ll Bruno(int N,int A[]) {
	mt19937 RndEng(19260827);
	vector <int> idx(N);
	iota(idx.begin(),idx.end(),0);
	shuffle(idx.begin(),idx.end(),RndEng);
	ll X=0;
	for(int i=N-2;i>=0;i-=2) {
		int u=A[idx[i]],v=A[idx[i+1]];
		if(!u&&!v) continue;
		else if(!u) X=X*3+0;
		else if(!v) X=X*3+1;
		else X=X*3+2;
	}
	return X;
}
```





---

## 作者：lfxxx (赞：0)

介绍两种做法。

## 基于三进制拆分的做法

考虑对原数三进制拆分，然后我们使用三个 bit 来表示一个三进制位，每三个 bit，假若至多只有一个损坏则考虑如下方案编码：$(001,110) \to 0,(010,101) \to 1,(100,011) \to 2$，则无论这位要填什么或者哪一个 bit 损坏都可以成功传输，假若存在两个 bit 损坏那么按照上面的方案依然有 $\frac{1}{3}$ 的概率可以传输，假若三个 bit 全部损坏或者两个 bit 损坏且没法传输，就令这三个 bit 为 $000$，然后考虑对三进制拆分的每一位和下标序列全部进行随机置换，这个方法最坏情况也能传递 $30$ 个三进制位，因此随机化后即可通过。

[代码](https://atcoder.jp/contests/joisc2017/submissions/61307736)

## 基于线性基的做法

你发现一个很不牛的事情是，传递信息的过程中，我们在乎信息之间的顺序，也就是你在乎这个信息对应了哪一位。

考虑消去这个顺序，我们对序列的每个位置赋上一个约定好的权值 $p_i$，一些位置顺坏后，剩下的 $110$ 的位置很大概率能选出一个线性无关的子集，于是考虑利用剩下的 $110$ 个位置构造一个线性基来表示 $X$，由于只用了没有顺坏的位置来表示，直接将这些位置传过去即可。这个做法中每个位置上代表的信息和其与其他信息的相对顺序无关，只与其位置下标有关，因此大大提高了抗干扰能力（一个位置被干扰不会导致其他位置上出问题）。

[代码](https://atcoder.jp/contests/joisc2017/submissions/61310312)

---

## 作者：cyc001 (赞：0)

# 8pts 做法

$X$ 存两遍，或起来即可。

# 约 50pts 

一个可能的做法是，我们发现 $X$ 存两遍做法比较有道理，如果我们可以规避掉不合法的情况就更好了。

维护一个尾指针 $pos$，对于第 $i$ 位考虑一个可能的放置策略:

1. 如果 $X$ 的第 $i$ 位是 $0$，将 $pos$ 和 $pos+1$ 设为 $0$。
2. 否则如果 $pos$ 位可用，就将 $pos$ 位设为 $1$。
3. 否则如果 $pos+1$ 位可用，将 $pos+1$ 位设为 $1$。
4. 否则方案不合法。

然后发现这个方案至多会用到 $120$ 位，考虑剩下的 $30$ 位，我们考虑按随机数生成操作序列，这些位存合法的种子在 $8 \sim 10$ 位左右，多存几遍，解码的时候先或起来求出种子，再解密。

理论上每个种子正确的概率是 $0.01$ 左右，但会被多测炸死 /kk。

### Code (53pts)

```cpp
#include"Broken_device_lib.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

using random_engine=mt19937_64;
using randint=uniform_int_distribution<int>;
static constexpr auto _seed='MikeMirzayanov';

void Anna(int N,long long X,int K,int P[]){
    random_engine eng(_seed);
    set<int> cfpos;
    vector<int> fpos;
    randint ri(0,N-1);
    while(cfpos.size()<30){
        const auto w=ri(eng);
        if(!cfpos.contains(w)) cfpos.emplace(w),fpos.emplace_back(w);
    }
    vector chkP(N,true);
    cir(i,0,K) chkP[P[i]]=false;
    vector<int> vaild;
    cir(i,0,N) if(!cfpos.contains(i)) vaild.emplace_back(i);
    auto ans=0;
    cir(__seed,0,128) if([&]{
        auto cv=vaild;
        random_engine ueng(__seed);
        ranges::shuffle(cv,ueng);
        auto pos=0;
        if(__seed<127){
            cir(i,0,60){
                const auto x=(X>>i)&1;
                if(!x) pos+=2;
                else if(chkP[cv[pos]]) ++pos;
                else if(!chkP[cv[pos+1]]) return false;
                else pos+=2;
            }
        }
        pos=0;
        cir(i,0,60){
            const auto x=(X>>i)&1;
            if(!x) Set(cv[pos++],false),Set(cv[pos++],false);
            else if(chkP[cv[pos]]) Set(cv[pos++],true);
            else Set(cv[pos++],true),Set(cv[pos++],true);
        }
        while(pos<120) Set(cv[pos++],false);
        return true;
    }()){
        ans=__seed;
        break;
    }
    cir(i,0,30){
        const auto b=i%10;
        const auto bi=(ans>>b)&1;
        Set(fpos[i],bi);
    }
}

long long Bruno(int N,int A[]){
    random_engine eng(_seed);
    set<int> cfpos;
    vector<int> fpos;
    randint ri(0,N-1);
    while(cfpos.size()<30){
        const auto w=ri(eng);
        if(!cfpos.contains(w)) cfpos.emplace(w),fpos.emplace_back(w);
    }
    auto __seed=0;
    cir(i,0,30){
        __seed|=(A[fpos[i]]<<(i%10));
    }
    auto ans=0ll;
    vector<int> vaild;
    cir(i,0,N) if(!cfpos.contains(i)) vaild.emplace_back(i);
    random_engine ueng(__seed);
    ranges::shuffle(vaild,ueng);
    auto pos=0;
    cir(i,0,60){
        if(A[vaild[pos]]){
            ans|=(1ll<<i);++pos;
            continue;
        }
        ++pos;
        ans|=((long long)(A[vaild[pos]])<<i);
        ++pos;
    }
    return ans;
}

```

另外一种可能的优化是把定种子换成 `chenlinxuan0226` @陈霖瑄0226 可以获得 61pts。

另外 `clx0226` 和 `陈霖瑄0226` 都是 61pts，比 `MikeMirzayanov` 高，更比 `ZengDingjun_EggArmy` 高出了 20pts。

# 约 70pts

考虑上面的做法一个比较大的问题是种子的存储有问题，我们考虑在更少的位数中存下这个数，然后把种子存 $4$ 遍。

不难发现 $1$ 的位数越多越能节约位数，考虑让 $1$ 尽量多，这样我们可以考虑反转，然后拿 $4$ 位出来存是否反转，这样可以获得 60pts 左右。

### Code (75pts，by juruoA，有删改)

```cpp
#include"Broken_device_lib.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long li;
typedef long double lf; 

inline li read(){
	long long ans = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){
		f = (ch == '-') ? -1 : 1;
		ch = getchar();
	}
	while(ch <= '9' && ch >= '0'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans * f;
} 

li Get(li s, li i){return s >> i & 1;}

#define SEED 569490

void Anna(int N,long long X,int K,int P[]){
    li vis[160];
    li p[160], p2[160];
    std::mt19937 rng2(SEED);
	li FL = 0, cnt0 = 0, cnt1 = 0;
	for(li i = 0; i <= 59; i++){
		if(Get(X, i)) cnt1++;
		else cnt0++;
	}
	if(cnt1 > cnt0) FL = 1;
	if(FL){
		for(li i = 0; i <= 59; i++){
			li temp = Get(X, i);
			X -= (1ll << i) * temp;
			X += (1ll << i) * (!temp);
		}
	}
    memset(vis, 0, sizeof vis);
    for(li i = 0; i < K; i++) vis[P[i]] = 1;
    li S;
	li len = 120;
	for(li i = 0; i < 150; i++) p[i] = i;
	shuffle(p, p + 150, rng2);
    for(li seed = 1; 1; seed++){
        li fl = 1;
        std::mt19937 rng1(seed);
		for(li i = 0; i < len; i++) p2[i] = p[i];
		shuffle(p2, p2 + len, rng1);
        for(li i = 0; i <= 59; i++){
			li r1 = p2[i * 2], r2 = p2[i * 2 + 1];
            if(Get(X, i) == 1 && (vis[r1] == 1 && vis[r2] == 1)){
                fl = 0;
				break;
            }
        }
        if(fl){
            S = seed;
            break;
        }
    }
    std::mt19937 rng1(S);
	for(li i = 0; i < len; i++) p2[i] = p[i];
	shuffle(p2, p2 + len, rng1);
    for(li i = 0; i <= 59; i++){
		li r1 = p2[i * 2], r2 = p2[i * 2 + 1];
		Set(r1, Get(X, i)), Set(r2, Get(X, i));
    }
	li cnt = 0, i;
	for(i = 120; i + 4 < 145; i += 4, cnt++){
		Set(p[i], Get(S, cnt));
		Set(p[i + 1], Get(S, cnt));
		Set(p[i + 2], Get(S, cnt));
		Set(p[i + 3], Get(S, cnt));
	}
	for(; i < 145; i++){
		Set(p[i], 0);
	}
	for(; i < 150; i++){
		Set(p[i], FL);
	}
}



long long Bruno( int N, int A[] ){
    li ans = 0;
    li p[160], p2[160];
    std::mt19937 rng2(SEED);
	li len = 120;
	for(li i = 0; i < 150; i++) p[i] = i;
	shuffle(p, p + 150, rng2);
    li S = 0, cnt = 0;
    li fl = 0;
    fl = (A[p[147]]) | (A[p[148]]) | (A[p[149]]) | (A[p[146]]) | (A[p[145]]);
    for(li i = 120; i + 4 < 146; i += 4, cnt++){
        S |= (A[p[i]] * (1ll << cnt));
        S |= (A[p[i + 1]] * (1ll << cnt));
        S |= (A[p[i + 2]] * (1ll << cnt));
        S |= (A[p[i + 3]] * (1ll << cnt));
    }
    std::mt19937 rng1(S);
	for(li i = 0; i < len; i++) p2[i] = p[i];
	shuffle(p2, p2 + len, rng1);
    for(li i = 0; i <= 59; i++){
		li r1 = p2[i * 2], r2 = p2[i * 2 + 1];
        ans |= (A[r1] * (1ll << i));
        ans |= (A[r2] * (1ll << i));
    }
    if(fl){
		for(li i = 0; i <= 59; i++){
			li temp = ((ans >> i) & 1);
			ans -= (1ll << i) * temp;
			ans += (1ll << i) * (!temp);
		}
    }
    return ans;
}

```

# 100pts

~~多试几个种子大家加油。~~

考虑传种子错误率太高啦，这样显然无法冲击更高分了。

这个时候 [IGM 251Sec](https://codeforces.com/profile/251Sec) 提出了一些见解，他说他会做 $3^{35}$，具体就是考虑相邻两位如果有至少一位坏掉了就不用设为 $0$，否则设为一个非零数就可以存 $0,1,2$。

有一个剪枝就是如果一个位本来就是 $0$ 那么它坏掉了也不影响，所以可以不管这种情况。

剩下的可以使用定种子随机打乱避免被干掉。

### Code (100pts)

```cpp
#include"Broken_device_lib.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

using random_engine=mt19937_64;
using randint=uniform_int_distribution<int>;
static constexpr auto _seed='MikeMirzayanov';

void Anna(int N,long long X,int K,int P[]){
    random_engine eng(_seed);
    vector<int> a(N);
    iota(a.begin(),a.end(),0);
    ranges::shuffle(a,eng);
    vector<int> ternary;
    while(X) ternary.emplace_back(X%3),X/=3;
    ranges::reverse(ternary);
    auto pos=0;
    set<int> invaild(P,P+K);
    for(auto&i:ternary){
        if(!i){            // Type '01'
            while(pos+2<N&&invaild.contains(a[pos+1])){
                Set(a[pos++],false);
                Set(a[pos++],false);
            }
            Set(a[pos++],false);
            Set(a[pos++],true);
        }else if(i==1){    // Type '10'
            while(pos+2<N&&invaild.contains(a[pos])){
                Set(a[pos++],false);
                Set(a[pos++],false);
            }
            Set(a[pos++],true);
            Set(a[pos++],false);
        }else{             // Type '11'
            while(pos+2<N&&(invaild.contains(a[pos])||invaild.contains(a[pos+1]))){
                Set(a[pos++],false);
                Set(a[pos++],false);
            }
            Set(a[pos++],true);
            Set(a[pos++],true);
        }
        if(pos+2>N-1) break;
    }
    for(;pos<N;++pos) Set(a[pos],false);
}

long long Bruno(int N,int A[]){
    random_engine eng(_seed);
    vector<int> a(N);
    iota(a.begin(),a.end(),0);
    ranges::shuffle(a,eng);
    auto ans=0ll;
    for(auto pos=0;pos<N;pos+=2){
        if(A[a[pos]]||A[a[pos+1]]){
            (ans*=3)+=(map{
                pair(pair(0,1),0),
                pair(pair(1,0),1),
                pair(pair(1,1),2)
            })[{A[a[pos]],A[a[pos+1]]}];
        }
    }
    return ans;
}
```

---

