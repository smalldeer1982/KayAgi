# Mahmoud and Ehab and yet another xor task

## 题目描述

Ehab has an array $ a $ of $ n $ integers. He likes the [bitwise-xor operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) and he likes to bother Mahmoud so he came up with a problem. He gave Mahmoud $ q $ queries. In each of them, he gave Mahmoud 2 integers $ l $ and $ x $ , and asked him to find the number of subsequences of the first $ l $ elements of the array such that their bitwise-xor sum is $ x $ . Can you help Mahmoud answer the queries?

A subsequence can contain elements that are not neighboring.

## 说明/提示

The bitwise-xor sum of the empty set is 0 and the bitwise-xor sum of a set containing one element is that element itself.

## 样例 #1

### 输入

```
5 5
0 1 2 3 4
4 3
2 0
3 7
5 7
5 8
```

### 输出

```
4
2
0
4
0
```

## 样例 #2

### 输入

```
3 2
1 1 1
3 1
2 0
```

### 输出

```
4
2
```

# 题解

## 作者：傅天宇 (赞：12)

## 前言：
萌新最近刚刚学了线性基，而且这道题昨天卡了一天，就写篇题解巩固下。由于我非常的懒，不想码2遍，所以模板的题解就跟这道题一起发在这里吧。

## 开始正文：
嗯，首先，什么是 **线性基** ？

##### 百度百科：线性基是竞赛中常用来解决子集异或一类题目的算法。

##### OI WiKi：线性基是向量空间的一组基，通常可以解决有关异或的一些题目。

通俗一点，就是由一个集合构造出来的另一个集合。（

### 它有何作用呢？

维护异或和。

### 它有什么性质呢？

- 线性基的元素能相互异或能还原原序列，且它是满足此性质的最小的集合。

- 线性基里没有异或和为 $0$ 的子集。

- 线性基中每个元素的异或方案唯一，也就是说，线性基中不同的异或组合异或出的数都是不一样的。

- 线性基中每个元素的二进制最高位互不相同。

——对 OI WiKi 所说的进行了适当改编。

### 你说了这么多了，那原集合是怎么得到线性基的集合呢？

放个代码，更容易理解~。

```cpp
#define M 25  //根据题意给出的样例范围，此题为25,(然而开大了也没事。
void get_xxj(int x)
{
    for(re i=M;i>=0;i--)
    {
        if(x&1<<i)//M>=30时就要写(x&1ll<<i)了。
        {
            if(xxj[i]) x^=xxj[i];
            else 
            {
                xxj[i]=x;//如果xxj[i]为0，则为x之前被异或后的数字。
                break;
            }
        }
    }
}
```

明显地看到一个个地插入，最终得到线性基的集合。

由此，我们又可以改编一下，写成如下的代码，判断是否可以成功插入。

如果可以，则 干啥；

不可以，则 干啥。

```cpp
#define M 25  
bool check(int x)
{
    for(re i=M;i>=0;i--)
    {
        if(x&1<<i)
        {
            if(xxj[i]) x^=xxj[i];
            else return 0;//成功插入。
        }
    }
    return 1;//这个数已经可以被其他数异或得到，就不用插了。
}
```

### 好的，现在我们来看这道题。

题意：询问前 $cnt$ 个数字中有多少个子集异或起来等于 $x$ 。

先预处理出 $lg$ 数组，按照 $l$ 排序，然后插入，判断 $x$ ，如果可以被线性基的集合求出，设 $tot$ 是此时的线性基的集合内没有用到的数，答案就是 $2^{cnt-tot}$ ，很好理解。

也没啥核心代码，就放整个的吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
//省略50行的火车头。
#define re register int//卡常是个好习惯呢。
#define N 100005
#define M 25//根据题意改M大小，题目是2^20，就写25吧。
const int mod=1e9+7;//mod模数。

inline int read()//快读，卡常是个好习惯呢。
{
    int x=0;
    bool flag=true;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') flag=false;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    if(flag) return x;
    return ~(x-1);
}

int n,q,tot,cnt;//上文说的tot,cnt和题意的n,q。
int a[N],lg[N],ans[N];//初始的子集,log数组,答案数组。

struct node
{
    int l,x,id;
    bool operator < (const node &a) const 
    {
        if(l!=a.l) return l<a.l;
        return x<a.x;
    }
}b[N];//结构体+排序。

int xxj[M+5];//线性基的子集。

void get_xxj(int x)
{
    for(re i=M;i>=0;i--)
    {
        if(x&1<<i)
        {
            if(xxj[i]) x^=xxj[i];
            else 
            {
                xxj[i]=x;
                tot++;
                break;
            }
        }
    }
}//上文说的，插入线性基子集。

bool check(int x)
{
    for(re i=M;i>=0;i--)
    {
        if(x&1<<i)
        {
            if(xxj[i]) x^=xxj[i];
            else return 0;
        }
    }
    return 1;
}//上文已说。

int main()
{
    n=read();
    q=read();
    for(re i=1;i<=n;i++) a[i]=read();
    for(re i=1;i<=q;i++)
    {
        b[i].l=read();b[i].x=read();
        b[i].id=i;
    }//读入,卡常是个好习惯呢。
    lg[0]=1;
    for(re i=1;i<=n;i++) lg[i]=(lg[i-1]<<1)%mod; //预处理lg数组。 
    sort(b+1,b+1+q);//排序。
    for(re i=1;i<=q;i++)
    {
        while(cnt<b[i].l) get_xxj(a[++cnt]);
        if(check(b[i].x)) ans[b[i].id]=lg[cnt-tot];
    }
```
前文已说：

如果可以被线性基的集合求出，$tot$ 是此时的线性基的集合内没有用到的数，答案就是 $2^{cnt-tot}$ ，很好理解。
```cpp
    for(re i=1;i<=q;i++) cout<<ans[i]<<endl; //输出答案。
    return 0;//完结撒花。
}
```

顺便再安利一下[我的博客](https://www.luogu.com.cn/blog/ljfty666666666666/) $ \ \ $![](https://cdn.luogu.com.cn/upload/image_hosting/0vmj19yo.png)

---

## 作者：UperFicial (赞：9)

没想到吧，我到现在才学会线性基。

[题目传送门](https://www.luogu.com.cn/problem/CF959F)。

同步发表于我的 [$\text{cnblogs}$](https://www.cnblogs.com/UperFicial/p/16690617.html)。

先把询问离线下来，按照 $l$ 升序把元素插入进线性基，并维护线性基内元素个数 $t$。

若 $x$ 不能被线性基内的元素表示出来，那么答案显然为 $0$。

否则，考虑到线性基的唯一性，$x$ 只能被一组元素表示，所以只需要考虑不在线性基内的元素有多少个，这些数都可以将这一组中的某一个元素替换掉。

线性基内元素一共有 $t$ 个，一共有 $l$ 个数，不在线性基内的数有 $(l-t)$ 个，每一个数有两种选择，替换或者不替换，所以答案是 $2^{l-t}$。阶乘预处理即可。

**PS：** 笔者在翻看题解时注意到一个非常有趣的现象。在最早的题解[这篇](https://www.luogu.com.cn/blog/user7035/solution-cf959f)，作者将 $t$ 的意义错写成不在线性基的元素个数，之后两篇题解都写的是这个含义，有点震撼了属于是/流汗黄豆（

[代码](https://codeforc.es/contest/959/submission/172028702)。

---

## 作者：ShieHere (赞：4)

# 前言

因为看到现有的题解全是离线做法，所以蒟蒻想来补一篇在线的。（虽然离线的好写一些）

此外，本片题解默认大家都会线性基，因此不会再对线性基作额外介绍。

此外，本篇题解的所有代码基于这样的设置：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e5+5,MAXJ=21;
const ll MOD=1e9+7;
```

因此若遇上了不认识的东西，多半是这里出来的。


# 正文

看到涉及某个区间的线性基，我首先想到的是这道题：[Ivan and Burgers](https://www.luogu.com.cn/problem/CF1100F)。

事实上，在本题中，我们也可以对于每一个下标 $i$，建一个从 $a_{1}$ 到 $a_{i}$ 的线性基，由于原序列最多有 $1\times10^{5}$ 个数，而每个数的二进制最高位都不超过 $20$ 位（$a_{i}<2^{20}$），因此并不会爆空间。

构造方式和“Ivan” 一题大同小异，甚至更加简单：

```cpp
struct XXJ{//一个线性基的结构体类型
    ll c[MAXJ];
    ll bnum(ll x){//获取一个数的二进制最高位
        ll r=0;
        while(x)x>>=1,r++;
        return r;
    }
    ll knum(ll x,ll k){return (x>>(k-1))&1;}//获取一个数的二进制第 k 位
    void ins(XXJ TOOL,ll x){//插入元素
        *this=TOOL;//继承之前已经构造好了的线性基（如果没有这一步，那么构造线性基的时间复杂度是不可接受的）
        while(x){
            ll num=bnum(x);
            if(c[num])x^=c[num];
            else return c[num]=x,void();
        }
    }
    ll size(){//获取该线性基中的元素个数
        ll r=0;
        for(int i=0;i<MAXJ;i++)r+=(c[i]!=0);
        return r;
    }
    ll check(ll x){//检查 x 能否被该线性基表示
        ll r=0;
        while(x){
            ll num=bnum(x);
            if(c[num])x^=c[num],r++;
            else return -1;//不能表示，返回 -1
        }
        return x?r:size();
        //如果可以表示，就返回表示 x 所需要的元素个数
        //要记得对 x==0 的情况特判
    }
}xxj[MAXN];//令 xxj[i] 表示从 a[1] 到 a[i] 的线性基
```

拥有了这样的结构体后，构造所有的线性基就很容易了：

```cpp
for(int i=1;i<=n;i++){
    scanf("%lld",&a[i]);
    xxj[i].ins(xxj[i-1],a[i]);
}
```

接下来是最关键的处理询问了。和大部分题解不同，本片题解提供的是在线的处理方法。

具体地，对于每一次询问，我们需要得到从 $a_{1}$ 到 $a_{l}$ 的线性基表示出 $x$ 所需要的元素个数。设这个数为 $num$。

其他离线做法都很明确地指出：每一次询问的答案都为 $2^{l-t}$，$t$ 为当前线性基中的元素个数。

于是想到：离线做法中的“当前线性基中的元素个数”，不就是表示出 $x$ 所需要的元素个数吗？

很巧，我们的 $num$ 刚好就是这个数，因此对于每一个询问，我们只需要讨论：

1. $a_{1}$ 到 $a_{l}$ 的线性基无法表示出 $x$，此时应输出 $0$。

2. $x$ 为 $0$，此时应该取 $num$ 为 $a_{1}$ 到 $a_{l}$ 的线性基中的元素个数。

3. 其他情况，通通输出 $2^{l-num}$。

接下来对上述情况作出解释：

当 $a_{1}$ 到 $a_{l}$ 的线性基无法表示出 $x$ 时，当然不存在任何一个子序列能表示出 $x$，因此输出 $0$。

当 $x$ 为 $0$ 时，由于线性基外任何一个数都可以被线性基内的元素表示，也就自然可以异或成 $0$，而线性基内的数是无法表示出 $0$ 的，因此我们只需要选择线性基外的每个数选或不选，因此方案数为 $2^{l-size}$，$size$ 为线性基内的元素个数，因此取 $num$ 为线性基中的元素个数。

其他情况，就和其他的题解一样了。

接下来给出代码，代码中有自认为详细的注释。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e5+5,MAXJ=21;
const ll MOD=1e9+7;
ll fastpow(ll base,ll k){//快速幂
    ll r=1;
    while(k){
        if(k&1)r=r*base%MOD;
        base=base*base%MOD;
        k>>=1;
    }
    return r;
}
struct XXJ{//一个线性基的结构体类型
    ll c[MAXJ];
    ll bnum(ll x){//获取一个数的二进制最高位
        ll r=0;
        while(x)x>>=1,r++;
        return r;
    }
    ll knum(ll x,ll k){return (x>>(k-1))&1;}//获取一个数的二进制第 k 位
    void ins(XXJ TOOL,ll x){//插入元素
        *this=TOOL;//继承之前已经构造好了的线性基（如果没有这一步，那么构造线性基的时间复杂度是不可接受的）
        while(x){
            ll num=bnum(x);
            if(c[num])x^=c[num];
            else return c[num]=x,void();
        }
    }
    ll size(){//获取该线性基中的元素个数
        ll r=0;
        for(int i=0;i<MAXJ;i++)r+=(c[i]!=0);
        return r;
    }
    ll check(ll x){//检查 x 能否被该线性基表示
        ll r=0;
        while(x){
            ll num=bnum(x);
            if(c[num])x^=c[num],r++;
            else return -1;//不能表示，返回 -1
        }
        return x?r:size();
        //如果可以表示，就返回表示 x 所需要的元素个数
        //要记得对 x==0 的情况特判
    }
}xxj[MAXN];//令 xxj[i] 表示从 a[1] 到 a[i] 的线性基
ll n,q,a[MAXN],li,xi;
int main(){
    scanf("%lld%lld",&n,&q);
    for(int i=1;i<=n;i++){//构造所有的线性基
        scanf("%lld",&a[i]);
        xxj[i].ins(xxj[i-1],a[i]);
    }
    while(q--){
        scanf("%lld%lld",&li,&xi);
        ll num=xxj[li].check(xi);//获取 xxj[li] 表示出 xi 所需要的元素个数
        ll ans=fastpow(2,li-num);//对于 2 的幂次运算，记得使用快速幂或预处理
        if(num==-1)ans=0;//若无法表示出 x，则答案为 0
        printf("%lld\n",ans);
    }
    return 0;
}
```

# 尾言

这是我的第一篇题解，因此经验略有不足，若有哪里表述不清或表述错误可以在评论区提出。

此外，本片题解仅为该题的在线做法补充，不代表更好的做法，在条件允许的情况下，请优先选择容易写的写法。

最后，祝大家看的开心！

---

## 作者：5k_sync_closer (赞：2)

离线下来按 $l$ 扫描线，问题变为维护一个集合，支持插入元素，查询异或和为 $x$ 的子集个数。考虑线性基维护。

对每个未成功插入线性基的数 $k$，都能在线性基中选出若干数与 $k$ 异或和为 $0$，记选出的这个异或和为 $0$ 的子集为 $T_k$。

对一次询问 $x$，若能在线性基中选出异或和为 $x$ 的子集 $S$，则 $S$ 任意异或上若干个 $T_k$ 异或和仍为 $x$，

由此可知，这样得到的异或和为 $x$ 的子集个数为 $2^{|\{k\}|}$。

若在线性基中不能选出异或和为 $x$ 的子集，答案显然为 $0$。

```cpp
#include <cstdio>
#include <vector>
using namespace std;
vector<pair<int, int>> v[100050];
bool f;
int n, m, z = 1, a[100050], q[100050], p[40];
bool P(int x)
{
    for (int i = 30; i >= 0; --i)
        if (x >> i & 1)
        {
            if (!p[i])
                return 0;
            else
                x ^= p[i];
        }
    return 1;
}
signed main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    for (int i = 0, l, x; i < m; ++i)
        scanf("%d%d", &l, &x), v[l].push_back({x, i});
    for (int i = 1, x; i <= n; ++i)
    {
        f = 0;
        x = a[i];
        for (int j = 30; j >= 0; --j)
            if (x >> j & 1)
            {
                if (!p[j])
                {
                    f = 1;
                    p[j] = x;
                    break;
                }
                else
                    x ^= p[j];
            }
        if (!f)
            z = (z << 1) % 1000000007;
        for (auto j : v[i])
            if (P(j.first))
                q[j.second] = z;
    }
    for (int i = 0; i < m; ++i)
        printf("%d\n", q[i]);
    return 0;
}
```


---

## 作者：Great_Influence (赞：2)

题意：

询问前$l$个数字中有多少个子集$xor$起来等于$x$。

因为是$xor$，所以考虑线性基。先离线操作，按$l$排序，依次将数字插入线性基。然后此时如果$x$能够被拼凑出，则答案为$2^{l-cnt}$其中$cnt$为线性基此时中线性无关数字个数(因为线性有关的数字可选可不选)。如果不可被拼凑则答案为0。时间复杂度$O(nlog_2n)$。

代码：

```cpp
#include<bits/stdc++.h>
#include<cctype>
#define For(i,a,b) for(i=(a),i##end=(b);i<=i##end;++i)
#define Forward(i,a,b) for(i=(a),i##end=(b);i>=i##end;--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define Chkmax(a,b) a=a>b?a:b
#define Chkmin(a,b) a=a<b?a:b
using namespace std;
template<typename T>inline void read(T &x){
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&k^'-')k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}
void file(void){
    #ifndef ONLINE_JUDGE
    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
    #endif
}


const int MAXN=1e5+7;

static int n,Q;

static struct quer
{
	int pos,num,id;
	friend bool operator<(quer a,quer b)
	{return a.pos<b.pos;}
}q[MAXN];

static int a[MAXN];

inline void init()
{
	read(n);read(Q);
	Rep(i,1,n)read(a[i]);
	Rep(i,1,Q)read(q[i].pos),read(q[i].num),q[i].id=i;
	sort(q+1,q+Q+1);
}

const int mod=1e9+7;
static int pow2[MAXN];

namespace liner_base
{
	int ba[22]={0},cnt=0;
	inline void insert(int x)
	{
		Repe(i,20,0)if((x>>i)&1)
		{
			if(!ba[i]){ba[i]=x;++cnt;return;}
			x^=ba[i];
		}
	}
	inline bool could(int x)
	{
		Repe(i,20,0)if((x>>i)&1)
		{
			if(!ba[i])return false;
			x^=ba[i];
		}
		return true;
	}
}
using namespace liner_base;
static int ans[MAXN];
inline void solve()
{
	pow2[0]=1;
	Rep(i,1,n)pow2[i]=(pow2[i-1]<<1)%mod;
	static int pos=0;
	Rep(i,1,Q)
	{
		while(pos<q[i].pos)insert(a[++pos]);
		if(could(q[i].num))ans[q[i].id]=pow2[pos-cnt];
	}
	Rep(i,1,Q)printf("%d\n",ans[i]);
}
int main(void){
    file();
    init();
    solve();
    return 0;
}

```

---

## 作者：run_away (赞：1)

## 题意

给定 $n$ 个整数 $a_i$ 和 $q$ 次形如 $l\ x$ 的提问，每次提问输出 $a_1\sim a_l$ 中有多少个子序列满足异或和为 $x$。

## 分析

很明显的线性基，因为数组开 $20n$ 不会炸，所以可以直接建立 $n$ 个线性基，记录 $a_1\sim a_i$ 的线性基。

但是注意时间，因为下一位的线性基可以直接继承上一位的，所以在求解线性基时可加入 `*this=lst`，其中 $lst$ 表示上一位的线性基，把时间复杂度降到 $O(n)$。

询问复杂度为 $O(q\log n)$，总时间复杂度为 $O(q\log n)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll mod=1e9+7,maxn=1e5+5,maxj=25;
struct basis{
    ll p[maxj];
    inline ll highbit(ll x){ll res=0;while(x)++res,x>>=1;return res;}
    inline void ins(basis lst,ll x){*this=lst;while(x){ll dis=highbit(x);if(p[dis])x^=p[dis];else return p[dis]=x,void();}}
    inline ll size(){ll res=0;for(ll i=1;i<=maxj;++i)res+=p[i]!=0;return res;}
    inline ll sum(ll x){ll res=0;while(x){ll dis=highbit(x);if(p[dis])x^=p[dis],++res;else return -1;}return x?res:size();}
}base[maxn];//线性基模板
ll n,q,a[maxn];
inline ll qpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res=res*a%mod;
        a=a*a%mod,b>>=1;
    }
    return res;
}
signed main(){
    n=read(),q=read();
    for(ll i=1;i<=n;++i)a[i]=read(),base[i].ins(base[i-1],a[i]);
    while(q--){
        ll l=read(),x=read();
        ll res=base[l].sum(x);
        printf("%lld\n",res==-1?0:qpow(2,l-res));
    }
    return 0;
}
```

---

## 作者：splendore (赞：1)

### 题意
给定一个序列 $\{a_n\}$ 和 $q$ 个询问，

对于每个询问 $l,x$ 回答在 $\{a_n\}$ 中前 $l$ 个数有多少个子集的异或和为 $x$。

### 思路
先把询问离线，再按 $l$ 升序排序，可以在 $O(\log N)$ 的时间内实现插入一个数到线性基里。

如果我们目前处理到第 $i$ 个询问， 那么我们需要将 $a_{l_{i-1}+1}$ 至 $a_{l_i}$ 插入到线性基里，再判断 $x_i$ 能否被已有的线性基表出，若能，答案就为 $2^{x_i-cnt}$ ，其中 $cnt$ 是线性基已有的元素个数。

代码如下：

```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100005,B=21,mod=1000000007;
struct node{int x,y,id;inline bool operator<(node &b){return x!=b.x?x<b.x:y<b.y;}}q[N];
int a[N],d[N],ans[N],p[B+5];
bool zero;int cnt;
void ins(int x){
	for(int i=B;~i;--i)
		if(x>>i&1){
			if(!p[i])return p[i]=x,++cnt,void();
			else x^=p[i];
		}
	zero=1;
}
bool check(int x){
	for(int i=B;~i;--i)
		if(x>>i&1){
			if(!p[i])return 0;
			else x^=p[i];
		}
	return 1;
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	d[0]=1;
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		d[i]=(d[i-1]<<1)%mod;
	}
	for(int i=1,x,y;i<=m;++i)
		scanf("%d%d",&x,&y),q[i]={x,y,i};
	sort(q+1,q+1+m);
	for(int i=1;i<=m;++i){
		if(q[i-1].x<q[i].x)
			for(int j=q[i-1].x+1;j<=q[i].x;++j)ins(a[j]);
		if(check(q[i].y))ans[q[i].id]=d[q[i].x-cnt];
	}
	for(int i=1;i<=m;++i)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Hagasei (赞：1)

线性基板题。

首先看到求前缀怎么怎么样，第一反应就是离线然后按 $l$ 排序。

看问题：求有多少子序列异或和为 $x$。子集加异或就是赤裸裸的线性基了。

首先，如果前面的数都凑不出来 $x$，就显然是 $0$ 了。

否则，既然线性基里的数只能唯一凑出 $x$，而线性基外则可以和里面任意替换，所以答案就是 $2^t$，其中 $t$ 是线性基外元素数量。

代码实现应该很简单，就不写注释了。

（tips: `__lg()` 是个好东西）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int p[64],d[64],zero;
const int MS=20;
inline void insert(int x){
	while(x&&p[__lg(x)]) x^=p[__lg(x)];
	if(x) p[__lg(x)]=x;
	else ++zero;
}
int a[100005];
struct ppp{
	int l,x,id;
}q[100005];
int ans[100005];
int pw[100005];
signed main(){
	int n,m;
	cin>>n>>m;
	pw[0]=1;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		pw[i]=pw[i-1]*2%1000000007;
	}
	for(int i=1;i<=m;++i){
		cin>>q[i].l>>q[i].x;
		q[i].id=i;
	}
	stable_sort(q+1,q+m+1,[](ppp x,ppp y){return x.l<y.l;});
	int top=0;
	for(int i=1;i<=m;++i){
		while(top<q[i].l){
			++top;
			insert(a[top]);
		}
		int x=q[i].x;
		while(x&&p[__lg(x)]){
			x^=p[__lg(x)];
		}
		if(x) ans[q[i].id]=0;
		else ans[q[i].id]=pw[zero];
		
	}
	for(int i=1;i<=m;++i) cout<<ans[i]<<endl;
}
```

---

## 作者：那个男人 (赞：1)

这道题看到2^20的数据应该考虑用线性基来做~~（今天上午刚学）~~

先把询问一次性读入然后离线做，按照q从小到大排序，楼下的大佬也提到了这一点。
答案就是2的1-L数的总个数减去异或得到x所需数个数次方，即2^pos-cnt。

代码如下~~（自认为代码风格更适合像我一样的蒟蒻们）~~
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define res register int
using namespace std;
const int N=1e5+7;
const int mod=1e9+7;
inline int rd(){
	char ch;int f=0;
	ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){f=f*10+(ch-'0');ch=getchar();}
	return f;
}
struct hs{
	int x,y,n; 
	bool operator <(const hs &tmp)const{
		if(x!=tmp.x)return x<tmp.x;
		else return y<tmp.y;
	}
}b[N];
int n,q,p[24],a[N],ans[N],cnt=0;
inline void ins(int x){
	for(res i=21;i>=0;i--){
		if(x&(1<<i)){
			if(!p[i]){
				p[i]=x;cnt++;return;
			}
			else x^=p[i];
		}
	}
}
inline bool check(int x){
	for(res i=21;i>=0;i--){
		if(x&(1<<i)){
			if(!p[i])return false;
			else x^=p[i];
		}
	}
	return true;
}
int lg2[N];
int main(){
	n=rd();q=rd();
	for(res i=1;i<=n;i++)a[i]=rd();
	for(res i=1;i<=q;i++){
		b[i].x=rd();b[i].y=rd();b[i].n=i;
	}
	lg2[0]=1;
	for(res i=1;i<=n;i++)lg2[i]=(lg2[i-1]<<1)%mod;
	sort(b+1,b+q+1);
	int pos=0;
	for(res i=1;i<=q;i++){
		while(pos<b[i].x)ins(a[++pos]);
		if(check(b[i].y)){ans[b[i].n]=lg2[pos-cnt];}
	}
	for(res i=1;i<=q;i++){
		printf("%d\n",ans[i]);
	}
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF959F)

# 前置知识

[线性基](https://oi-wiki.org/math/linear-algebra/basis/) 

# 解法

将操作离线下来，并按 $\{ l \}$ 升序排序，接着顺序插入线性基并处理询问。

对于未成功插入线性基的元素 $k$ 一定能被线性基内选出若干元素得到。故在 $x$ 能被表出的情况下，设 $1 \sim l$ 中成功插入线性基的元素个数为 $siz$，对于剩下 $l-siz$ 个元素选出若干个总方案数为 $2^{l-siz}$，这 $2^{l-siz}$ 种方案都存在一种在线性基中选出若干个元素使得异或起来等于 $x$。

故 $2^{l-siz}$ 即为所求。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
const ll p=1000000007;
struct node
{
    ll l,x,id;
}q[100010];
ll a[100010],d[30],ans[100010];
bool cmp(node a,node b)
{
    return a.l<b.l;
}
ll insert(ll x)
{
    for(ll i=20;i>=0;i--)
    {
        if((x>>i)&1)
        {
            if(d[i]==0)
            {
                d[i]=x;
                return 1;
            }
            x^=d[i];
        }
    }
    return 0;
}
bool check(ll x)
{
    for(ll i=20;i>=0;i--)
    {
        if((x>>i)&1)
        {
            if(d[i]==0)
            {
                return 0;
            }
            x^=d[i];
        }
    }
    return 1;
}
ll qpow(ll a,ll b,ll p)
{
    ll ans=1;
    while(b)
    {
        if(b&1)
        {
            ans=ans*a%p;
        }
        b>>=1;
        a=a*a%p;
    }
    return ans;
}
int main()
{
    ll n,m,siz=0,i,j;
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(i=1;i<=m;i++)
    {
        cin>>q[i].l>>q[i].x;
        q[i].id=i;
    }
    sort(q+1,q+1+m,cmp);
    for(i=1,j=1;i<=m;i++)
    {
        while(j<=q[i].l)
        {
            siz+=insert(a[j]);
            j++;
        }
        ans[q[i].id]=(check(q[i].x))*qpow(2,q[i].l-siz,p);
    }
    for(i=1;i<=m;i++)
    {
        cout<<ans[i]<<endl;
    }
    return 0;
}
```

---

## 作者：永不复行 (赞：0)

线性基，排序节约时间
注意运算符重载时
（别像我之前一样wa了：

表演wa法
```c
return (l<tmp.l)?l<tmp.l:x<tmp.x;
```
）
```c
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007; 
int n,q;
struct nw
{
	int l,x,ad;
	bool operator <(const nw &tmp)const
	{
		if(l!=tmp.l)return l<tmp.l;
		else return x<tmp.x;
	}
}ques[100010];
int pos,used,f[25];
void update(int x)
{
	for(int i=21;i>=0;i--)
	{
		if(x&(1<<i))
		{
			if(!f[i])
			{
				f[i]=x;
				used++;
				return;
			}
			else x^=f[i];
		}
	}
}
bool check(int x)
{
	for(int i=21;i>=0;i--)
		if(x&(1<<i))
		{
			if(!f[i])return false;
			else x^=f[i];
		}
	return true;
}
int m[100010],a[100010],ans[100010];
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&ques[i].l,&ques[i].x);
		ques[i].ad=i;
	}
	m[0]=1;
	for(int i=1;i<=n;i++)
	m[i]=(m[i-1]<<1)%mod;
	sort(ques+1,ques+q+1);
	pos=used=0;	
	for(int i=1;i<=q;i++)
	{
		while(pos<ques[i].l)update(a[++pos]);
		if(check(ques[i].x))ans[ques[i].ad]=m[pos-used];
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
}
```

---

