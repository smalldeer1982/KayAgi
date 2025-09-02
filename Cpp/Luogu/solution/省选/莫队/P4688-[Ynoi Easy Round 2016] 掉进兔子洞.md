# [Ynoi Easy Round 2016] 掉进兔子洞

## 题目背景

5.632

我（或者是在读这篇文字的你）不属于这个世界

这是世界的界限

6.41

世界的意义必定存在于世界之外

世界中的一切事物如其所存在般而存在，如其所发生般而发生

世界之中不存在价值

——《逻辑哲学论》

我们的情人，不过是随便借个名字，用幻想吹出来的肥皂泡

把信拿去吧，你可以使假戏成真

我本来是无病呻吟，漫无目的的吐露爱情---现在这些漂泊不定的鸟儿有地方栖息了，你可以从信里看出来

拿去吧---由于不是出自真心，话就说得格外动听，拿去吧，就这么办吧...

![](https://cdn.luogu.com.cn/upload/pic/21091.png)

果然……好女人要有的是，烟、楼顶……还有轻飘飘的衣服呀……

某一天，水上由岐看见天上掉下了个布制玩偶

为了被天空接受而投掷出的她的布偶，不知在天空飞舞了多少次，已经遍体鳞伤

“被天空接受”——那是为了寻找不知何时开始在这个城市流传的“回归天空之路”的行为

![](https://cdn.luogu.com.cn/upload/pic/21102.png)

为了被天空接受而被扔出去的木偶，在空中飞舞并最终坠落

那是为了将其本身即为世界的少女送予天空的少女的行为

![](https://cdn.luogu.com.cn/upload/pic/21093.png)

横跨银河，被称作Vega与Altair，或是织女星与牛郎星的两颗星星，再加上北十字星之顶的天鹅座构成了夏之大三角

它被称作譬如三位一体的神圣的图形

只有神圣的图形在天空闪耀之时，世界才与天空相遇

![](https://cdn.luogu.com.cn/upload/pic/21094.png)

我想试一试，第一次，也是最后一次的恶作剧

![](https://cdn.luogu.com.cn/upload/pic/21095.png)

那是...什么？

什么事也没有哦，只是，间宫君他自己主动跳下去了而已哦~

怎么回事？

什么事也没有哦，只是，间宫君他自己主动跳下去了而已哦~

但是我看到了，是那个杀死了大家吗？

什么事也没有哦，只是，间宫君他自己主动跳下去了而已哦~

不，那个东西，什么都没有做，只是...

什么事也没有哦，只是，间宫君他自己主动跳下去了而已哦~

只是...怎么回事...

什么事也没有哦，只是，间宫君他自己主动跳下去了而已哦~

我确实听到了头盖骨破碎的声音

但是那个，并非是外面的世界

而是总自己的里面传来的

![](https://cdn.luogu.com.cn/upload/pic/21096.png)

水上同学...我偶尔会思考这种事情...

世界的极限到底在哪里呢...

世界的...世界的尽头的更尽头...

要是能有那种地方...

要是假如我能够站在那个地方的话...我还是能跟平时一样看着那个尽头的风景吗？我有这种想法....

我理所当然的想着这种事...然后决定似乎是有些奇怪啊

因为那里是世界的尽头哦

是世界的极限哦

如果我能够看到那个的话...世界的极限...是否就等同于我的极限呢？

因为，从那里看到的世界...我所看见的...不就是我的世界吗？

世界的极限...就会变成我的极限吧~

世界就是我看到的摸到的，并且感受到的东西

那样的话，世界到底是什么呢

世界和我到底有什么不同呢...我有这种想法

有吗？

世界和我的差别

是一样的

但是，或许其他人也有相同的感觉...

就连你，或许也认为世界就是你自己吧

并且，我觉得那个大概是正确的...

虽然我不太清楚...大概是你也站在世界的尽头，跟我一样在看着它吧

所以，你也和世界一样

但是啊，那样果然很奇怪啊...

如果世界就是我的话...为什么我会看不到你看到的世界呢？

明明我的世界里有你存在...却看不到你看到的世界

我从来没有看到过你看到的世界

那个，简直就像是两者不会交集的平行宇宙一样...

即使有现象暗示着那个东西存在...却是绝对的无法触碰...

我...看不到你所在的世界...

但是...

那个也是真的是真的吗？

我真的没有看到过你的世界吗...

既然所有的人都平等的拥有她们自己的世界的话

那么为什么世界会变成一个呢？

为什么那么多的世界会存在于这里呢？

世界变成一个的理由

...我偶尔会思考这种事情

所以...我才能够喜欢上你



## 题目描述

您正在打 galgame，然后突然发现您今天太颓了，于是想写个数据结构题练练手：

一个长为 $n$ 的序列 $a$。

有 $m$ 个询问，每次询问三个区间，把三个区间中同时出现的数一个一个删掉，问最后三个区间剩下的数的个数和，询问独立。

注意这里删掉指的是一个一个删，不是把等于这个值的数直接删完，比如三个区间是  $[1,2,2,3,3,3,3]$，$[1,2,2,3,3,3,3]$ 与 $[1,1,2,3,3]$，就一起扔掉了 $1$ 个 $1$，$1$ 个 $2$，$2$ 个 $3$。

## 说明/提示

Idea：nzhtl1477，Solution：nzhtl1477，Code：nzhtl1477，Data：nzhtl1477

$1\leq n , m \leq 10^5$，$1 \leq a_i\leq 10^9$，$1\leq l_1,r_1,l_2,r_2,l_3,r_3\leq n$，$l_1\leq r_1$，$l_2\leq r_2$，$l_3\leq r_3$。

## 样例 #1

### 输入

```
5 2
1 2 2 3 3
1 2 2 3 3 4
1 5 1 5 1 5```

### 输出

```
3
0```

# 题解

## 作者：shadowice1984 (赞：67)

不得不说bitset套莫队还是相当套路的……

不过这道题放到ynoi里就显得相当亲民了……(45行的ynoi题啊!)
_________________________________

首先这道题的询问看样子基本没法用数据结构维护……

因为你相当于说要维护不同区间权值数组的最小值，这个东西使用数据结构显然是没法做的

那么智商不够压位来凑，我们可以考虑使用bitset乱搞一波

那么我们可以很快的发现一个询问$(l_{1},r_{1},l_{2},r_{2},l_{3},r_{3})$的答案是

$$(r_{1}-l_{1}+1)+(r_{2}-l_{2}+1)+(r_{3}-l_{3}+1)-3×size$$

其中$size$表示这3个区间里面出现了多少个公共的颜色

问题来了，如果我们使用一个bitset来标记这个区间里出现过什么颜色的话，我们最多知道这个3个区间出现了**多少种公共的颜色**，而不是出现了**多少个公共的颜色**

此时情况开始变得辣手起来……

仔细分析一下我们会发现,问题的瓶颈在于，我们的目标是求公共颜色个数，相当于每种颜色的出现次数取一个min，可是bitset却只是支持集合取交集

但是我们又发现一个性质是所有颜色的出现次数之和=区间长度

所以我们发现我们可以以这样的方式存储一个区间

首先我们在给数字离散化的时候做下手脚

我们令这个数字离散化之后的值=这个序列里小于等于这个值的数字个数

(实现起来很简单，用map求出每种值的出现次数做一遍前缀和就行)

接下来我们要用一个bitset存储一个区间了

假设我们现在向这个区间里加一个颜色p

一般的做法是令bitset的p这一位为1

但是我们现在不这样了，假如说这个区间里p这个值已经出现$cnt_{p}$次了

我们就令bitset里面$(p-cnt_{p})$这一位为1

因为这个数字离散化之后的值是所有小于等于这个值的数字个数

换句话说离散化之后，相邻两个值p1,p2的值的差，刚好是p1的出现次数

这意味着我们这样存储颜色也不会出现将一个颜色存到另外一个颜色地方去

那么此时我们发现这样存储元素有一个好处是

我们现在能算两个区间或者多个区间之间有多少个公共的颜色了

只要把这几个区间取一下交集然后看交集的size就行了

为什么此时取交集就可以起到取min的效果呢……？

因为我们插入颜色的方式决定了假如某个颜色p在区间内出现了$cnt_{p}$次的话

那么bitset里面第$p$到第$p-cnt_{p}+1$位是连续的一段1，也就存储下了$cnt_{p}$的信息

而取交集的时候，对于一个颜色p，交集里从第p位向前连续1的长度恰好就是每一个集合$cnt_{p}$中的min(不懂的话自己画个图还是相当好理解的)

 _如果你熟悉后缀数组的话会发现这种存储方式和后缀数组里的计数排序的行为非常向(都是做一遍前缀和然后倒着排布元素)_ 

所以我们就成功使用取交集完成了取min的操作了

好了那么我们的算法就大致定型了:通过某种奇技淫巧求出这个区间的bitset，然后三个bitset取一下交即可

然后你发现一件事情是这样的bitset似乎并没有办法通过线段树这种常用的处理区间问题的工具来求出来

这个时候我们就可以考虑请出莫队这种泛用更强的区间处理算法了

那么我们发现我们求这个区间的bitset还是很资瓷快速插入和删除的

因此我们可以使用莫队算法以$O(N\sqrt{N})$的复杂度求出每一个区间的bitset

然后你需要做的就是把这个bitset和对应的询问的bitset&一下就可以了

最后的问题是我们开不起1e5个长度为1e5的bitset

~~很简单把询问拆成3组，每组莫队一次就行了~~

上代码~

```C
#include<cstdio>
#include<algorithm>
#include<map>
#include<bitset>
using namespace std;const int N=1e5+10;const int M=34010;typedef long long ll;
int a[N];int n;int m;map <int,int> mp;bitset <N> ans[M];int nans[M];bitset <N> nb;
struct qry{int l;int r;int t;}q[3*M];int tp;int tot=1;int cnt[N];
inline bool cmp1(const qry& a,const qry& b){return a.l<b.l;}
inline bool cmp2(const qry& a,const qry& b){return a.r<b.r;}
inline void ins(int p){nb[p-cnt[p]]=1;cnt[p]++;}
inline void del(int p){cnt[p]--;nb[p-cnt[p]]=0;}
inline void solve()
{
    if(tot>=m)return;
    for(int i=1;i<=M-10&&tot<=m;i++,tot++)
    {
        ++tp;scanf("%d%d",&q[tp].l,&q[tp].r);q[tp].t=i;nans[i]+=q[tp].r-q[tp].l+1;
        ++tp;scanf("%d%d",&q[tp].l,&q[tp].r);q[tp].t=i;nans[i]+=q[tp].r-q[tp].l+1;
        ++tp;scanf("%d%d",&q[tp].l,&q[tp].r);q[tp].t=i;nans[i]+=q[tp].r-q[tp].l+1;
    }for(int i=1;i<=tp/3;i++)ans[i].set();sort(q+1,q+tp+1,cmp1);int nl=0;int nr=0;
    for(int i=1;i<=tp;i+=320){int r=min(tp,i+319);sort(q+i,q+r+1,cmp2);}
    for(int i=1;i<=tp;i++)
    {
        if(nr<q[i].l)
        {
            for(int j=nl;j<=nr;j++)del(a[j]);nl=q[i].l;nr=q[i].r;
            for(int j=nl;j<=nr;j++)ins(a[j]);
        }
        else 
        {
            while(nl<q[i].l)del(a[nl]),nl++;while(nl>q[i].l)nl--,ins(a[nl]);
            while(nr<q[i].r)nr++,ins(a[nr]);while(nr>q[i].r)del(a[nr]),nr--;
        }ans[q[i].t]&=nb;
    }for(int i=nl;i<=nr;i++)del(a[i]);
    for(int i=1;i<=tp/3;i++)printf("%lld\n",nans[i]-ans[i].count()*3);
    for(int i=1;i<=tp/3;i++)nans[i]=0;tp=0;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)mp[a[i]]++;map <int,int> :: iterator it,it1;
    for(it=mp.begin(),it1=it,++it1;it1!=mp.end();++it,++it1)it1->second+=it->second;
    for(int i=n;i>=1;i--)a[i]=mp[a[i]];
    solve();solve();solve();return 0;
}
```

---

## 作者：rui_er (赞：51)

题意已经足够清楚了，我们直接说思路：

---

前置知识：

- 分块、莫队
- 离散化
- 一些奇奇怪怪的技巧

根据题意三段区间的数的总和为 $\sum_{i=1}^3(r_i-l_i+1)-3\times k$，其中 $k$ 为三段区间内共有的数的个数。问题转化为求这个 $k$ 的值。

容易想到，我们使用莫队维护查询的区间内每个数的个数。对于一次询问，我们将其拆成传统莫队的三个询问：$(l_1,r_1),(l_2,r_2),(l_3,r_3)$，分别进行处理。我们要得到 $k$，需要得到这三个询问中有哪些数、分别几个，然后取它们的交集即可。

那么问题来了，这个交集（或三次询问）怎么求呢？注意一个数可能重复出现多次。我们考虑先将初始 $a$ 数组进行**离散化**，只记录 $a$ 数组每一个值对应排序好的数组的**编号**即可。这样，若干个相同的数便会留出若干个空着的编号，它们代表同一个值。然后使用这个离散化的对应关系用 bitset 存即可。

完结撒花！

等等，Ynoi 可不是这么简单就过去的。看一眼数据范围，$1\le n,m\le 10^5$。bitset 存不下！（笑容逐渐凝固）

没关系，我们可以把输入的查询**分为若干组**，每组 $2\times 10^4$ 个数（当然更大也可以，不炸空间就没事），对于每一组分别进行处理即可。

**小细节：莫队必须先进队再出队！** 我因为一开始顺序搞混一直 RE，被卡了 1.5h！

真·完结撒花！

---

主要代码：

```cpp
const ll N = 1e5+5, M = 2e4, K = M+5, SIZE = 320;
ll n, m, a[N], b[N], s[N];
ll vis[N], len[N];
bitset<N> cnts[K], u;
#define whichBlock(x) (\
	(x-1)/SIZE+1\
)
struct Node {
	ll l, r, id;
	friend bool operator < (const Node &a, const Node &b) {
		ll x = whichBlock(a.l), y = whichBlock(b.l);
		if(x == y) return a.r < b.r;
		return x < y;
	}
}q[N];

void discretization() {
	for(ll i=1;i<=n;i++) {
		scanf("%lld", &a[i]);
		b[i] = a[i];
	}
	sort(b+1, b+1+n);
	for(ll i=1;i<=n;i++) a[i] = ll(lower_bound(b+1, b+1+n, a[i]) - b);
}
void modify(ll x, ll y) {
	ll z = a[x];
	if(y == -1) u[z+(--s[z])] = 0;
	else u[z+(s[z]++)] = 1;
}
void solve(ll op) {
	assert(op > 0);
	ll tot = 0;
	memset(s, 0, sizeof(s));
	for(ll i=1;i<=op;i++) {
		vis[i] = len[i] = 0;
		for(ll j=1;j<=3;j++) {
			q[++tot].id = i;
			scanf("%lld%lld", &q[tot].l, &q[tot].r);
			len[i] += q[tot].r - q[tot].l + 1;
		}
	}
	sort(q+1, q+1+tot);
	ll l = 1, r = 0;
	u.reset();
	for(ll i=1;i<=tot;i++) {
		while(l > q[i].l) modify(--l, 1);
		while(r < q[i].r) modify(++r, 1);
		while(l < q[i].l) modify(l++, -1);
		while(r > q[i].r) modify(r--, -1);
		if(vis[q[i].id]) cnts[q[i].id] &= u;
		else cnts[q[i].id] = u;
		vis[q[i].id] = 1;
	}
	for(ll i=1;i<=op;i++) printf("%lld\n", len[i]-3*(ll)cnts[i].count());
}
```

---

## 作者：Ryo_Yamada (赞：25)

这是我的第一道 Ynoi，~~同时也一发卡到了最优解~~，发篇题解纪念一下 qwq。看上去不开 $O2$ 也是能过的，~~良心 lxl 好评。~~

本题需要的知识点：

- 分块，莫队
- `bitset` 优化
- 离散化
- 其它的奇技淫巧

首先明确这题要求的，三个区间内不同时出现的数的个数。列出柿子就是 $(r_1 - l_1 + 1) + (r_2 - l_2 + 1) + (r_3 - l_3 + 1) - rep$，其中 $rep$ 是三个区间内同时出现的数的个数。

首先 $1 \le a_i \le 10^9$，显然离散化。同时注意，本题离散化时不能去重，即不需要 `unique`，直接使用 `lower_bound` 即可。

随后对每个询问求删除的数，对于这种对多个区间内元素个数的维护我们不难想到莫队，如莫队板子题 [小 Z 的袜子](https://www.luogu.com.cn/problem/P1494) 就是这种题型。

老套路，将长度为 $n$ 的序列拆成 $\sqrt n$ 块，把所有询问的区间以 $l$ 为第一关键字，$r$ 为第二关键字排序。

此时考虑如何求出上文的 $rep$。对每个询问开一个长度为 $n$ 的 `bitset`，每一位是否为 $1$ 即表示这一位是否被删除。再维护另一个 `bitset` $Bst$，每一位是否为 $1$ 表示这一区间是否有这个数。则最后要删除的数就是三个区间的 $Bst$ 取交集。

最后要注意，

- 此题 $1 \le n, m \le 10^5$，开不下这么大的 `bitset`，需要分几次求答案。

- 区间移动位置时，要先加再减。如果先减，则可能会让 $cnt$ 变成负数再变成正数，会导致 `bitset` 无效访问内存，从而导致 RE。

于是这题就结束了，$\text{Code}$：

```cpp
#include <iostream>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <cmath>
#include <algorithm>
#define il inline
#define rg register

//namespace IO {
//    const int SIZE = (1 << 20) + 1;
//    char ibuf[SIZE], *iS, *iT, obuf[SIZE],*oS = obuf, *oT = obuf + SIZE - 1;
//    char _st[55];
//    int _qr = 0;
//    inline char gc() {
//        return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++);
//    }
//    inline void qread() {}
//    template<class T1, class ...T2>
//    inline void qread(T1 &IEE, T2&... ls) {
//        register T1 __ = 0, ___ = 1;
//        register char ch;
//        while(!isdigit(ch = gc())) ___ = (ch == '-') ? -___ : ___;
//        do {
//            __ = (__ << 1) + (__ << 3) + (ch ^ 48);
//        }while(isdigit(ch = gc()));
//        __ *= ___;
//        IEE = __;
//        qread(ls...);
//        return ;
//    }
//    inline void flush() {
//        fwrite(obuf, 1, oS - obuf, stdout);
//        oS = obuf;
//        return ;
//    }
//    inline void putc_(char _x) {
//        *oS++ = _x;
//        if(oS == oT) flush();
//    }
//    inline void qwrite() {}
//    template<class T1, class ...T2>
//    inline void qwrite(T1 IEE, T2... ls) {
//        if(!IEE) putc_('0');
//        if(IEE < 0) putc_('-'), IEE = -IEE;
//        while(IEE) _st[++_qr] = IEE % 10 + '0', IEE /= 10;
//        while(_qr) putc_(_st[_qr--]);
//        qwrite(ls...);
//        return ;
//    }
//    struct Flusher_{~Flusher_(){flush();}}io_flusher;
//}
//
//using namespace IO;
//此部分是快读，为防止抄袭注释掉了。
//注 : 此快读板子是@SPFA(uid=177999) 给我的，为防止他被说是 ctj 特来此声明一下。
using namespace std;

const int N = 1e5 + 5;
const int M = 25005;

bitset<N> bst[M], Bst;//bitset 开 25000，分四次求出答案。
bool vis[M];
int n, m, tot, blocksize;
int a[N], b[N], blocknum[N];
int ans[N], cnt[N];

struct Node {
	int id, l, r;
	bool operator < (const Node &oth) const {
		return blocknum[l] == blocknum[oth.l] ? r < oth.r : blocknum[l] < blocknum[oth.l];
	}
} Que[N << 2];

il void Add(int id) {
	int x = a[id];
	++cnt[x];
	Bst[x + cnt[x] - 1] = 1; 	
}

il void Del(int id) {
	int x = a[id];
	--cnt[x];
	Bst[x + cnt[x]] = 0;
}

il void Solve(int k) {
	tot = 0;
	memset(vis, false, sizeof vis);
	memset(ans, 0, sizeof ans);
	memset(cnt, 0, sizeof cnt);
    //因为是分次求出答案，不要忘记每次初始化。
	for(rg int i = 1; i <= k; i++) {
		for(int j = 1; j <= 3; j++) {
			Que[++tot].id = i;
			qread(Que[tot].l, Que[tot].r);
			ans[i] += Que[tot].r - Que[tot].l + 1;
		}
	}
	sort(Que + 1, Que + tot + 1);
	Bst.reset();
	int l = 1, r = 0;
	for(rg int i = 1; i <= tot; i++) {
		while(l > Que[i].l) Add(--l);
		while(r < Que[i].r) Add(++r);
		while(l < Que[i].l) Del(l++);
		while(r > Que[i].r) Del(r--);
  		//区间移动位置先加再减。
		if(!vis[Que[i].id]) bst[Que[i].id] = Bst, vis[Que[i].id] = true;//此区间未访问过，直接赋值
		else bst[Que[i].id] &= Bst;//访问过，取交集
	}
	for(rg int i = 1; i <= k; i++) ans[i] -= bst[i].count() * 3;
	for(rg int i = 1; i <= k; i++) printf("%d\n", ans[i]);
}

int main() {
	qread(n, m);
	blocksize = sqrt(n);
	for(rg int i = 1; i <= n; i++) {
		qread(a[i]);
		b[i] = a[i];
		blocknum[i] = (i - 1) / blocksize + 1;
	}
	sort(b + 1, b + n + 1);
	for(rg int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;//离散化，不需要去重
	int T = M - 5;
	while(m) {
		if(m < T) {
			Solve(m);
			break;
		}
		else Solve(T), m -= T;
	}//分次求出答案
	return 0;
}
```

upd：注明了快读板子的来源。

---

## 作者：quest_2 (赞：17)

推一手蒟蒻的 $\color{LimeGreen}{\texttt {博客}}$ 

------------


总体做法已经被楼上的神仙们说得差不多啦，这篇文章旨在尽可能说得$\large{\texttt细}\normalsize{\texttt细}{\texttt 细}\small{\texttt 细}$细一点。避免像笔者一样~~Coding 五分钟，Debug 两小时~~的情况QwQ。

$\Large{\texttt 思}\Large{\texttt 路}$：莫队（不带修）+ $bitset$ 优化。可以称得上板子吧，可惜一眼还没看出来，还是题做的少/kk。

$\Large{\texttt 首}\Large{\texttt 先}$ ，讲一下为什么**离散化**是需要的。权值值域较大，将耗费大量 $bitset$ 的空间。离散化后 $bitset$ 只需开 $10^5$ 的空间，较为优秀。

$\Large{\texttt 其}\Large{\texttt 次} $，如果您是头一回接触 $bitset$ 对莫队的优化，这里有几个在代码里会用上的操作需要先跟您叙清：

- `bitset<MAX> now` 开一个大小为 $MAX$ 的 $bitset$ ，名为 $now$ 。本题中， $bitset$ 的第 $i$ 位则代表离散化后，值为 $i$ 的这个元素 **在/不在(1/0)** 这个区间内。

- `now.set(pos) ` 将 $now$ 的第 $pos$ 位设为 $1$ 。本题中用来表示离散化后，值为 $pos$ 的这个元素 **包含于** 要查询的区间。 

- `now.reset(pos)` 将 $now$ 的第 $pos$ 位设为 $0$ 。相对的，本题中用来表示离散化后，值为 $pos$ 的这个元素 **不包含于** 要查询的区间。 

- `sum[i] &= now` $sum[i]$ 也是一个 $bitset$ 。我们可以将两个 $bitset$ 直接 **与** 上，来实现求 **元素交集** 的作用。
	-  _如果您不理解为什么可以实现，我们可以考虑：如果一个离散后的元素，在三个区间都有出现，则它在三个区间所对应的 $bitset$ 中的位置**都为 $1$** ， **“与”** 运算后，三组都为 $1$ 的位置**结果依然为 $1$**，这些位置就对应着三个区间的交集。_ 
    
- `sum[i].count()` 用于求 $bitset$ 中 $1$ 的个数。这里用来统计求交集后**元素的个数**，原因与前面类似，不再赘述。

$\Large{\texttt 然}\Large{\texttt 后}$，需要指出这题使用莫队+ $bitset$ 的意义，有一言：

> 莫队可以维护常规数据结构难以维护的区间信息

这里的要维护的区间信息是什么，是**一个元素是否在区间中出现**。

这很难不让人联想到莫队板题《小B的询问》。

再者，也很难想到一种别的数据结构能够高效解决这类问题。

又有一言：

> bitset 常用于常规数据结构难以维护的的判定、统计问题

必然，这道题便是一款极为鬼畜的统计问题，**区间元素交集**，这令人不得不趋向 $bitset$ 求帮助。幸好， $bitset$ 求"与"可以解决这个问题。

（这里说句闲话，为什么逻辑运算符 **“与”**  $\land$ 和集合运算符 **“交”** $\cap$ 有些形似，实则不是巧合， $\cap$ 的定义便是：在集合A **且** 在集合B的元素。）

$\Large{\texttt 最}\Large{\texttt 后}$，略加整理一下可能会把您卡着的点，如下：

1. 本题稍带卡空间，建议将询问**分成三块**处理，以实现只开 $\dfrac{1}{3}$ 大小的 $bitset$ 而不牺牲时间复杂度。（这种卡空间思想类似于循环展开的卡时间思想？）。笔者采用了**常数大小的块**，而这一常数经检验为 $33350$ ，再往上就 $MLE$ 了QwQ 。当然，这是因人的写法而异的，不必死板。（~~用模拟退火调常数指日可待~~）

1. 做莫队时需要注意左右指针的移动顺序，否则可能会造成负值 $bitset$ 而 $RE$ 。具体地说，`l--,r++,l++,r--` 或 `l--,r++,r--,l++` 是最吼哒。因为他们都是**先扩张**了区间，**再收缩**。有效避免了一上来就收缩，结果一直找不到询问左右界的情况。

1. 因为本题是一个一个删去相同数的，所以不同位置上的元素，即使他们权值相同，**本质上是不同的**。故离散化时就**别想着去重**了，解决办法很多，比如少写一条 $\operatorname{unique}$ 哇，计算出现次数 $cnt$ 时有意更改权值保证其不重哇。笔者选择的是后者。

1. 和普通莫队记录最终答案的数组一样，参与 “与” 运算的 $bitset$ 的标号也不应是他排序后的序号，而应是这个询问**输入时记录的 $id$** 。即 `sum[q[i].id] &= now` 。

1. 既然我们是开常数大小的块，循环时须**格外注意上界**，谨防访问到空询问导致算法退化成暴力AwA。

1. 如果您被卡常了，可以试试莫队的**奇偶性排序**优化，百度即可，在此不多说了。

由于笔者码风诡异且实现与其他大佬基本无异，这里就放一个 $\mathtt{OI\ Wiki}$ 的[例题参考代码链接](https://oi-wiki.org/misc/mo-algo-with-bitset/)叭，顺着这条链是能翻到的。（~~逃~~

---

## 作者：foreverlasting (赞：9)

[题面](https://www.lydsy.com/JudgeOnline/problem.php?id=4939)

第一次做大毒瘤题，果然恶心......

首先看懂题意后相信诸位奆佬马上就能想到bitset维护并集，再用莫队去维护答案的方法（太明显了吧）。然后当我开开心心敲到一半时，就发现一个神奇的事情：我靠空间好像会炸！赶紧匆匆忙忙看了一波数据，的确开不下。那么怎么办？这时就会有一个神奇的办法叫做 分成多次询问，这样子的话空间就会足够了。然后只要注意下多次询问的次数，调整次数就能在时间上过去了。

下面是code：
```
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define res register int
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read() {
    res s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(res x) {
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const int N=1e5+10,NN=27000;
int n,m,len,part[N],ans[N];
bitset<N> F[NN+10],temp;
int A[N],B[N],L1[N],L2[N],L3[N],R1[N],R2[N],R3[N],cnt[N],l,r,tot;
bool flag[NN+10];
struct mdzz {
    int L,R,id;
    mdzz() {}
    mdzz(res L,res R,res id):L(L),R(R),id(id) {}
} Q[N];
inline bool cmp(mdzz x,mdzz y) {
    return part[x.L]==part[y.L]?x.R<y.R:part[x.L]<part[y.L];
}
inline void init() {
    memset(cnt,0,sizeof(cnt));
    memset(flag,0,sizeof(flag));
    temp.reset();
    l=1,r=0,tot=0;
}
inline void add(res x) {
    temp[x+cnt[x]]=1,cnt[x]++;
}
inline void rem(res x) {
    temp[x+cnt[x]-1]=0,cnt[x]--;
}
inline void solve(res lx,res rx) {
    init();
    for(res i=lx; i<=rx; i++) {
        Q[++tot]=mdzz(L1[i],R1[i],i),ans[i]+=R1[i]-L1[i]+1;
        Q[++tot]=mdzz(L2[i],R2[i],i),ans[i]+=R2[i]-L2[i]+1;
        Q[++tot]=mdzz(L3[i],R3[i],i),ans[i]+=R3[i]-L3[i]+1;
    }
    //for(res i=1;i<=tot;i++)printf("%d %d %d\n",Q[i].L,Q[i].R,Q[i].id);
    sort(Q+1,Q+tot+1,cmp);
    //for(res i=1;i<=tot;i++)printf("%d %d %d\n",Q[i].L,Q[i].R,Q[i].id);
    for(res i=1; i<=tot; i++) {
        while(r<Q[i].R)add(A[++r]);
        while(l>Q[i].L)add(A[--l]);
        while(r>Q[i].R)rem(A[r--]);
        while(l<Q[i].L)rem(A[l++]);
        if(!flag[Q[i].id-lx+1]) flag[Q[i].id-lx+1]=1,F[Q[i].id-lx+1]=temp;
        else F[Q[i].id-lx+1]&=temp;
    }
    for(res i=lx; i<=rx; i++)ans[i]-=F[i-lx+1].count()*3;
}
int main() {
    n=read(),m=read();
    len=sqrt(n);
    for(res i=1; i<=n; i++)A[i]=B[i]=read(),part[i]=(i-1)/len+1;
    sort(B+1,B+n+1);
    for(res i=1; i<=n; i++)A[i]=lower_bound(B+1,B+1+n,A[i])-B;
    for(res i=1; i<=m; i++)L1[i]=read(),R1[i]=read(),L2[i]=read(),R2[i]=read(),L3[i]=read(),R3[i]=read();
    //for(res i=1;i<=n;i++)printf("%d %d\n",A[i],B[i]);
    for(res i=1; i<=m; i+=NN)solve(i,min(m,i+NN-1));
    for(res i=1; i<=m; i++)write(ans[i]),puts("");
    return 0;
}
```

---

## 作者：Michael_Bryant (赞：6)

写Ynoi题解有瘾系列QAQ   
先推一发我的博客  
[传送门](https://lfd2002.com) 
这题绝壁神题  
这个题上来我们可以看看问的是什么  
$\sum _ {i=1}^{3} (r_i-l_i+1) - 3 * \sum _ {j=1} ^ {Max}min(cnt_1[j],cnt_2[j],cnt_3[j])$  
然后发现前面那部分非常好办  
考虑后面那部分  
看到$a_i$的范围我先想到了把这个数列离散化一下  
然后我考虑到的是用一个操作把出现的最少次数搞出来  
如果这要是一个$0-1$串的话这不就是一个与操作么  
所以说我用bitset来维护这个事情  
求一段区间内各数字出现的次数是莫队算法的经典问题。  
对于本题，我们把一个询问的三个区间拆开解决，最后再合并起来。  
每次合并都是O(n)的复杂度，不优秀，这里我们使用bitset优化,记录cnt。注意到数字可能重复出现，而bitset只能记录0和1，因此在离散化前不能有去重操作。  
例如对样例数据：1 2 2 3 3 ，离散化后应为：1 2 2 4 4，在bitset中用第2位表示出现的第1个2，第3位表示第二个2，以此类推。   
但这样会MLE，于是我们强行把询问分组，每25000个为一组，分批求解，解决了空间不足的问题。  
但是这样的话如果常数大点可能会TLE <del>我常数小不关我事</del>这样怎么办呢 我们可以考虑手写一个bitset嘛对不对  
<del>我是不会写 幸好我常数小</del>  
代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100100
#define T 25000
inline int read()
{
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
    return s*w;
}
struct Query
{
    int l,r,id,pos;
}Q[N];
int l1[N],l2[N],l3[N],r1[N],r2[N],r3[N],n,m;
int bel[N],cnt[N],tcnt,vis[T+10],ans[N],block,a[N],b[N];
bitset<N>f[T+10],tmp;
inline bool cmp1(const Query qwq,const Query qaq)
{
    if(qwq.pos<qaq.pos) return true;
    else if(qwq.pos==qaq.pos&&qwq.r<qaq.r) return true;
    else return false;
}
inline bool cmp2(const Query qwq,const Query qaq)
{
    if(qwq.id<qaq.id) return true;
    else return false;
}
inline void modify(int x,int y)
{
    x=a[x];
    if(y<0) tmp[x+cnt[x]-1]=0;
    if(y>0) tmp[x+cnt[x]]=1;
    cnt[x]+=y;
}
inline void solve(int x,int y)
{
    memset(cnt,0,sizeof cnt);tcnt=0;
    tmp.reset();int l=1,r=0;
    memset(vis,0,sizeof vis);
    for(int i=x;i<=y;i++)
    {
        Q[++tcnt]=(Query){l1[i],r1[i],i,bel[l1[i]]};
        ans[i]+=r1[i]-l1[i]+1;
        Q[++tcnt]=(Query){l2[i],r2[i],i,bel[l2[i]]};
        ans[i]+=r2[i]-l2[i]+1;
        Q[++tcnt]=(Query){l3[i],r3[i],i,bel[l3[i]]};
        ans[i]+=r3[i]-l3[i]+1;
    }
    sort(Q+1,Q+tcnt+1,cmp1);
    for(int i=1;i<=tcnt;i++)
    {
        while(r<Q[i].r) r++,modify(r,1);
        while(l>Q[i].l) l--,modify(l,1);
        while(r>Q[i].r) modify(r,-1),r--;
        while(l<Q[i].l) modify(l,-1),l++;
        if(!vis[Q[i].id-x+1]) vis[Q[i].id-x+1]=1,f[Q[i].id-x+1]=tmp;
        else f[Q[i].id-x+1]&=tmp;
    }
    for(int i=x;i<=y;i++)
        ans[i]-=f[i-x+1].count()*3;
}
int main()
{
    n=read(),m=read();block=sqrt(n);
    for(int i=1;i<=n;i++)
    {
        a[i]=read();b[i]=a[i];
        bel[i]=(i-1)/block+1;
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    for(int i=1;i<=m;i++)
    {
        l1[i]=read(),r1[i]=read();
        l2[i]=read();r2[i]=read();
        l3[i]=read();r3[i]=read();
    }
    for(int i=1;i<=m;i+=T) solve(i,min(m,i+T-1));
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}

```

---

## 作者：Schwarzkopf_Henkal (赞：5)

感觉这题给我的一个很大的启示就是带权的 bitset 怎么写。

正常的 bitset 如果某个值出现多次只会占用一个位置（或者说只会使一个位置重复地变成 $1$），但是我们希望出现多次的值能够占用多个位置。这样做的意义在于取并集时能够获知重复的个数而不是重复的种类数，同时在对 bitset 取 count 的时候多个重复数能够重复产生贡献。当然，每个点的权值必须要有一个足够小，或者均摊足够小的上限，不然很容易会爆空间。

具体来说，就是我们要记每个数实际出现了多少次，然后每个数有一个索引表示这个数开始第一个属于这个数的位置，然后后面一些位置都是属于这个数的，每次更新 索引+数量 的位置。不过因为这个，它的实际应用可能只有莫队了吧？

当然，~~因为是 Ynoi~~ 这题要是数据范围小一点可能就放过了暴力，所以即使满足上面的条件，均摊足够小，还是被卡了空间。那么用一个不太常见的方法，把询问分组就可以了，由于 lxl 非常良心（确信），没吸氧也过了这题。

回到这道题本身，是多个区间的可离线询问，数据范围只有 $10^5$，很容易看出是莫队，同一个询问里面有多个互相独立的子询问，这个非常好搞，就额外地设置一个答案数组然后把子询问拆开来就好了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,val[100005],Alpha[100005],S,rt,cnt[100005],neko[100005];
bitset<100005>ans[10005],cur,mk;
int Schwarzkopf_Henkal=1e4;
struct node{
    int l,r,id;
    friend bool operator<(node a,node b){
        if(a.l/S!=b.l/S)
            return a.l<b.l;
        return a.r<b.r;
    }
}t[300005];
int main(){
    scanf("%d%d",&n,&m);
    S=ceil(n/sqrt(m));
    for(int i=1;i<=n;i++){
        scanf("%d",&val[i]);
        Alpha[i]=val[i];
    }
    sort(Alpha+1,Alpha+n+1);
    // cout<<'\n';
    for(int i=1;i<=n;i++){
        val[i]=lower_bound(Alpha+1,Alpha+n+1,val[i])-Alpha;
        // cout<<val[i]<<" ";
    }
    while(m>0){
        mk.reset();
        cur.reset();
        memset(neko,0,sizeof(neko));
        memset(cnt,0,sizeof(cnt));
        rt=0;
        for(int i=1;i<=min(m,Schwarzkopf_Henkal);i++){
            for(int j=1,l,r;j<=3;j++){
                scanf("%d%d",&l,&r);
                t[++rt]=(node){l,r,i};
                neko[i]+=r-l+1;
            }
        }
        sort(t+1,t+rt+1);
        for(int i=1,l=1,r=0;i<=rt;i++){
            while(l>t[i].l){
                l--;
                cur[val[l]+cnt[val[l]]]=1;
                cnt[val[l]]++;
            }
            while(r<t[i].r){
                r++;
                cur[val[r]+cnt[val[r]]]=1;
                cnt[val[r]]++;
            }
            while(l<t[i].l){
                cnt[val[l]]--;
                cur[val[l]+cnt[val[l]]]=0;
                l++;
            }
            while(r>t[i].r){
                cnt[val[r]]--;
                cur[val[r]+cnt[val[r]]]=0;
                r--;
            }
            if(mk[t[i].id])
                ans[t[i].id]&=cur;
            else ans[t[i].id]=cur;
            mk[t[i].id]=1;
        }
        for(int i=1;i<=min(m,Schwarzkopf_Henkal);i++)
            printf("%d\n",neko[i]-3*ans[i].count());
        m-=Schwarzkopf_Henkal;
    }
}
```

---

## 作者：Spasmodic (赞：4)

upd on 7/29：发现题解说的很有问题，改一下

---

这算是Ynoi题里面比较清新的一题了，居然不卡常，我交上去一遍过（大雾

前置芝士：莫队，bitset

首先如果你做过[这道题](https://www.luogu.com.cn/problem/P1494)的话那么你肯定会想到莫队，维护区间

但是直接去维护好像很困难。。。

注意到其实答案就是总数减去三个区间的交集的大小再乘个三，原因是删数的时候其实就是把交集里面的数全部删掉了。

于是考虑用bitset来维护下交集，那么总复杂度大概是$O(n^2/w+n\sqrt n)$，空间是$O(n^2/w)$的

但是你会发现这道题毒瘤到开始卡你空间。。。

于是你去翻翻题解，然后题解告诉你这就是正解，你只要再把询问分成若干组，每组去按照上面的做法做一遍就可以了

然后手算下空间最多允许多少就可以过掉了

代码就不放了

---

## 作者：cirnovsky (赞：2)

## 题意简述

Ynoi的题貌似题面都很简洁……（除了惯例的一大堆Gal或Anime的图片+对话以外）

## 题解

读完题，我们可以发现每轮询问的答案是这个东西:

$$
\sum_{i=1}^{3}(r_{i}-l_{i}+1)-P\times 3
$$

其中，$P$ 表示三个区间里面的公共颜色数量。

前面那个 $\sum$ 里面的东西很好维护，我们主要来讲后面一部分的维护方法。

首先初始序列的 $a_{i}$ 是一定要离散化一遍的。

那么我们如何表示出出现的最少次数呢？

如果这是一个二进制串的话，我们可以发现这就是一个 $\operatorname{bit\_and}$ 的操作。

对于每个询问，我们可以把三个区间分开处理再合并。直接维护复杂度过高，用 bitset 优化。由于这是个二进制序列，所以离散化的时候不能去重，否则答案就会偏大。

直接操作容易 MLE，这里介绍一个小trick。我们可以把询问分批处理，这样就行了。

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <bitset>
#include <cmath>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N = 1e5 + 5;
const int F = 23333 + 5;
int n, m, block, origin[N], appear[N];
int cnt[N], ans[N], vis[25005];
int l1[N], l2[N], l3[N];
int r1[N], r2[N], r3[N];
bitset < N > S[F];
vector < int > disc;
struct AskSet {
	int l, r;
	int id, p;
} Q[N];

int GetID(int x) {
	return lower_bound(disc.begin(), disc.end(), x) - disc.begin() + 1;
}

bool SortWith(const AskSet& x, const AskSet& y) {
	return (x.p < y.p) || (x.p == y.p && x.r < y.r);
}

void MakeCont(int pos, int flags, bitset < N >& bit) {
	pos = origin[pos];
	if (flags > 0) bit[pos + cnt[pos]] = 1;
	else bit[pos + cnt[pos] - 1] = 0;
	cnt[pos] += flags;
}

void Contribute(int fr, int ba) {
	memset(cnt, 0, sizeof cnt);
	memset(vis, 0, sizeof vis);
	bitset < N > bit; bit.reset();
	int l = 1, r = 0, subs = 0;
	for (int i = fr; i <= ba; ++i) {
		Q[++subs] = {l1[i], r1[i], i, appear[l1[i]]};
		Q[++subs] = {l2[i], r2[i], i, appear[l2[i]]};
		Q[++subs] = {l3[i], r3[i], i, appear[l3[i]]};
		ans[i] += (r3[i] - l3[i]) + (r2[i] - l2[i]) + (r1[i] - l1[i]) + 3;
	}
	sort(Q + 1, Q + 1 + subs, SortWith);
	for (int i = 1; i <= subs; ++i) {
		while (r < Q[i].r) MakeCont(++r, 1, bit);
		while (l > Q[i].l) MakeCont(--l, 1, bit);
		while (r > Q[i].r) MakeCont(r--, -1, bit);
		while (l < Q[i].l) MakeCont(l++, -1, bit);
		if (!vis[Q[i].id - fr + 1]) {
			vis[Q[i].id - fr + 1] = 1;
			S[Q[i].id - fr + 1] = bit;
		} else {
			S[Q[i].id - fr + 1] &= bit;
		}
	}
	for (int i = fr; i <= ba; ++i)
		ans[i] -= S[i - fr + 1].count() * 3;
}

signed main() {
	scanf("%d %d", &n, &m);
	block = sqrt(n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &origin[i]);
		appear[i] = (i - 1) / block + 1;
		disc.push_back(origin[i]);
	}
	sort(disc.begin(), disc.end());
	for (int i = 1; i <= n; ++i)
		origin[i] = GetID(origin[i]);
	for (int i = 1; i <= m; ++i) {
		scanf("%d %d", &l1[i], &r1[i]);
		scanf("%d %d", &l2[i], &r2[i]);
		scanf("%d %d", &l3[i], &r3[i]);
	}
	for (int i = 1; i <= m; i += 23333) Contribute(i, min(m, i + 23332));
	for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}
```

---

## 作者：Sol1 (赞：2)

带上八聚氧能直接过的肯定都是 lxl 的良（凉）心题（确信

$10^5$？

可以离线？

~~还是 lxl 的题？~~

所以肯定是莫队啦qwq。

但是我们很快发现一个问题：值域上暴力匹配数组，即使在离散化之后依然是 $O(N)$ 的，这样总复杂度就是 $O(N^2)$ 的，不能接受。

发现离可接受的复杂度并不远，所以考虑 bitset 卡掉 $64$ 倍常数。

但是现在有另外一个问题：bitset 只能维护 $0$ 和 $1$，但是这个题可以多次出现一个数。

这里考虑更换离散化的方法。

因为要支持的是出现次数取 min，而此题不带修，出现次数最大值是固定的，所以将一个数离散化之后的值设定为小于等于它的数的数量。

比如 $\{1,2,2,3,3,10,11,11\}$ 离散化后应为 $\{1,2,2,4,4,6,7,7\}$。

那么这个问题就解决了：在维护的时候，假如值 $x$ 在整个数组中出现过 $c$ 次，在 bitset 维护的区间内出现了 $c_0$ 次，那么此时 $[x,x+c_0-1]$ 中是 $1$，$[x+c_0,x+c-1]$ 中都是 $0$。这样就可以直接 and 了。

现在还有最后一个问题：这里有 $10^5$ 个询问，但是 $10^5$ 个 $10^5$ 的 bitset 开不下怎么办？

考虑强行分组，我这里拆了4组，这样就将空间压缩到了 $2.5 \times 10^4 \times 10^5$bit。实测大概 300M 左右，不是很卡。

最后贴一个代码吧qwq

```cpp
#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <queue>
#include <bitset>
#include <algorithm>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

const int N = 100005, S = 317, DIV = 25000;
struct query {
	int l, r, i;
};
int n, a[N], m, pos[N], cnt[N], tot[N];
query qry[N * 3];
priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > que;
bitset <N> ans[DIV + 5], cur;

inline bool cmp(const query& a, const query& b) {
	return (pos[a.l] ^ pos[b.l] ? pos[a.l] < pos[b.l] : (pos[a.l] & 1 ? a.r < b.r : a.r > b.r));
}

inline void Read() {
	n = qread(); m = qread();
	for (register int i = 1;i <= n;i++) a[i] = qread(), pos[i] = (i - 1) / S + 1;
}

inline void Prefix() {
	for (register int i = 1;i <= n;i++) que.push(make_pair(a[i], i));
	register int rk = 1;
	while (!que.empty()) {
		register int val = que.top().first, trk = rk;
		while (!que.empty() && que.top().first == val) {
			a[que.top().second] = trk;
			rk++;
			que.pop();
		}
	}
}

inline void Add(int pos) {
	cnt[a[pos]]++;
	cur.set(a[pos] + cnt[a[pos]] - 1);
}

inline void Del(int pos) {
	cur.reset(a[pos] + cnt[a[pos]] - 1);
	cnt[a[pos]]--;
}

inline void Solve() {
	for (register int i = 1;i <= DIV && i <= m;i++) {
		qry[3 * i - 2].l = qread(); qry[3 * i - 2].r = qread(); qry[3 * i - 2].i = i;
		qry[3 * i - 1].l = qread(); qry[3 * i - 1].r = qread(); qry[3 * i - 1].i = i;
		qry[3 * i].l = qread(); qry[3 * i].r = qread(); qry[3 * i].i = i;
		ans[i].set();
		tot[i] = qry[3 * i - 2].r - qry[3 * i - 2].l + 1
			   + qry[3 * i - 1].r - qry[3 * i - 1].l + 1
			   + qry[3 * i].r - qry[3 * i].l + 1;
	}
	sort(qry + 1, qry + Min(DIV * 3, 3 * m) + 1, cmp);
	register int l = 1, r = 0;
	memset(cnt, 0, sizeof(cnt));
	cur.reset();
	for (register int i = 1;i <= Min(DIV * 3, 3 * m);i++) {
		while (l > qry[i].l) Add(--l);
		while (r < qry[i].r) Add(++r);
		while (r > qry[i].r) Del(r--);
		while (l < qry[i].l) Del(l++);
		ans[qry[i].i] &= cur;
	}
	for (register int i = 1;i <= Min(DIV, m);i++) printf("%d\n", tot[i] - ans[i].count() * 3);
	m -= DIV;
}

int main() {
	Read();
	Prefix();
	while (m >= 0) Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：tzc_wk (赞：1)

> 题意：给出一个长度为 $n$ 的数组 $a$。有 $m$ 次询问，每次给出三段区间 $[l_1,r_1]$，$[l_2,r_2]$，$[l_3,r_3]$，把这三段区间中同时出现的数一个一个删掉，问最后三个区间剩下的数的个数和，**询问独立**。

> $1 \leq n \leq 10^5$，$1 \leq a_i \leq 10^9$

第一道 Ynoi，写个题解纪念一下。

看到这道题三个区间，并且个数和也是需要主席树一类的数据结构才能维护，就知道这道题数据结构不好维护。

但是 $10^5$ 的数据范围 $n \sqrt n$ 是绰绰有余的，就可以想到莫队。再一看到区间取并集可以想到 bitset。

我们可以将一个询问拆成三个询问，用莫队分别维护这三个区间对应的数的集合，然后取并集。那么最终一个询问的答案 $=$ 这三段区间的长度和 $-\ 3\ \times $ 并集的大小。

还有一个问题。区间中的数可能有重复的。这里有一个技巧，离散化的时候不去重，就可以了。

注意点：莫队需要先入后出，不然可能会出问题。

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n=read(),m=read(),a[100005],key[100005];
const int BLK_SZ=320;
int blk,bel[100005],L[100005],R[100005];
struct query{
	int ind,l,r;
	friend bool operator <(query a,query b){
		if(bel[a.l]!=bel[b.l])
			return bel[a.l]<bel[b.l];
		else if(bel[a.l]&1)
			return a.r<b.r;
		else
			return a.r>b.r;
	}
} q[100005];
int qs=0,ans[100005];
bitset<100005> d[21005],cur;
int cnt[100005];
inline void ins(int x){
	cur[x+cnt[x]]=1;
	cnt[x]++;
}
inline void del(int x){
	cnt[x]--;
	cur[x+cnt[x]]=0;
}
inline void solve(int M){
	fill0(cnt); 
	qs=0;fill0(ans);
	fz(i,1,M){
		q[++qs].l=read();q[qs].r=read();q[qs].ind=i;ans[i]+=q[qs].r-q[qs].l+1;
		q[++qs].l=read();q[qs].r=read();q[qs].ind=i;ans[i]+=q[qs].r-q[qs].l+1;
		q[++qs].l=read();q[qs].r=read();q[qs].ind=i;ans[i]+=q[qs].r-q[qs].l+1;
	}
	sort(q+1,q+qs+1);
	cur.reset();
	fz(i,1,M){
		d[i].set();
	}
	int l=1,r=0;
	fz(i,1,qs){
		while(l>q[i].l)	ins(a[--l]);
		while(r<q[i].r)	ins(a[++r]);
		while(l<q[i].l)	del(a[l++]);
		while(r>q[i].r)	del(a[r--]);
		d[q[i].ind]&=cur;
//		fz(i,1,n)	cout<<cur[i]<<endl;
	}
	fz(i,1,M){
		cout<<ans[i]-3*(d[i].count())<<endl;
	}
}
signed main(){
	fz(i,1,n)	a[i]=read(),key[i]=a[i];
	sort(key+1,key+n+1);
	fz(i,1,n)	a[i]=lower_bound(key+1,key+n,a[i])-key;
	blk=(n-1)/BLK_SZ+1;
	fz(i,1,blk){
		L[i]=(i-1)*BLK_SZ+1;
		R[i]=min(i*BLK_SZ,n);
		fz(j,L[i],R[i])	bel[j]=i;
	}
	int T=m/5;
	solve(T);solve(T);solve(T);solve(T);solve(m-(T<<2));
	return 0;
}
```

~~后排膜拜 lxl~~

---

