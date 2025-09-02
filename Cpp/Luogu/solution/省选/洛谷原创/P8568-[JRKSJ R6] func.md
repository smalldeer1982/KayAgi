# [JRKSJ R6] func

## 题目描述

**这是一道 IO 交互题．**

你有一个一次函数 $f(x)=kx+b$（$1\le x \le n-1$）．这个一次函数满足 $k,b$ 均为整数且 $k>0$．

vectorwyx 修改了这个函数，具体而言，他会选择一个整数 $t$（$1\le t \le n-1$），将这个函数在直线 $x=t$ 及右侧的部分向右平移一个单位长度，并把两部分的端点用直线段连接，得到一个分段函数 $g(x)$：

$$
g(x)=\begin{cases}
kx+b&1\le x<t\\
kt+b& t\le x <t+1\\
k(x-1)+b& t+1\le x \le n
\end{cases}
$$

请通过交互的方式得到 $t$ 的值．

### 交互方式

**本题单个测试点中含有多组数据．**

1. 首先从标准输入流读入一个整数 $T$，表示数据组数．
1. 接下来你将进行 $T$ 组数据的交互．对于每组数据，首先从标准输入流读入三个整数 $n,Q,P$．
1. 你可以通过向标准输出流输出 `? l r p`（$1\le l \le r \le n$，$2\le p \le P$）的方式来询问．在单组数据中，你最多只能进行 $Q$ 次 `?` 操作．交互库会根据你的询问依次做出以下判断并向标准输入流发送返回结果：
    - 若你的询问数据范围错误，回答为 $-2$．此时交互库会直接返回 WA．你需要立刻退出你的程序来避免与已经结束程序的交互库交互引起超时．
    - 若 $g(l)=g(r)$，回答为 $-1$．
    - 否则回答为 $(g(l) + g(r))\bmod p$．
1. 你可以通过向标准输出流输出 `! t` 的方式来给出答案．你只能进行一次回答操作，且回答操作必须是你在每组数据中进行的最后一个操作．交互完成后，从标准输入流读入一个零或一的整数 $x$．若 $x=1$ 则代表当前数据回答正确，你需要回到步骤 $2$ 以进行下一组数据的交互．否则 $x=0$，你需要立刻退出自己的程序．

**不要忘记在每次输出后刷新缓冲区，否则你将会 TLE．**

下面是一些语言的刷新缓冲区操作：

- C++：`fflush(stdout)` 或 `cout.flush()`．
- C: `fflush(stdout)`．
- Java: `System.out.flush()`．
- Python: `stdout.flush()`．
- Pascal: `flush(output)`．
- 其他语言：请参考对应语言的帮助文档．


## 说明/提示

### 样例解释

请注意，样例仅用来表示交互的规则，不保证有逻辑性．

#### 样例 #1

$f(x)=3x-2$（$1\le x \le 4$），$t=3$．

$$
g(x)=\begin{cases}
3x-2&1\le x<3\\
7& 3\le x <4\\
3x-5& 4\le x \le 5.
\end{cases}
$$

所以第一次询问的结果 $(g(1) + g(3))\bmod 2 = (1+7)\bmod 2=0$，第二次询问的结果 $(g(4)+g(5))\bmod 2 = (7+ 10)\bmod 2=1$．

### 数据范围与约束

**本题采用捆绑测试．且不存在一个 Subtask 包含其它所有 Subtask 的限制．**

| Subtask | 分值 |    $n$     | $Q=$ |       $P=$        | $g(x)\le$ |    特殊性质     |
| ------- | ---- | ---------- | ---- | ----------------- | --------- | --------------- |
| $1$     | $10$ | $\le 10^9$ | $42$ | $2\times 10^{18}$ | $10^{18}$ | 无              |
| $2$     | $20$ | $\le 10^9$ | $30$ | $2$               | $10^{18}$ | 斜率 $k$ 为奇数 |
| $3$     | $30$ | $\le 10^9$ | $42$ | $50$              | $10^{18}$ | 无              |
| $4$     | $39$ | $\le 10^9$ | $32$ | $50$              | $10^{18}$ | 无              |
|$5$|$1$|$ = 1162261531$| $32$| $50$| $7857125847061472735$|无|

对于 $100\%$ 的数据，保证 $1 \le T \le 10$，$2\le n\le 1162261531$．且满足 $\forall x \in [1,n], 0 \le g(x)\le 7857125847061472735$．

### 提示

由于本题不存在一个 Subtask 包含其它所有 Subtask 的限制．所以数据范围中「对于 $100\%$ 的数据」部分的 $n$ 和 $g(x)$ 的上界没有任何意义．但由于直接写「对于 $100\%$ 的数据，满足 $n \ge 2$，$g(x)\ge 0$」会被某些管理以「你管这叫数据范围」打回，故此题中保留该没有意义的上界．

## 样例 #1

### 输入

```
1
5 999 999

0

1

1```

### 输出

```


? 1 3 2

? 4 5 2

! 3```

# 题解

## 作者：vectorwyx (赞：12)

好题，yzy 神中神 orz。

先来考虑 Sub2，也就是已知 $p,k\bmod p,2b\bmod p$ 怎么做。为方便行文以下如无特殊说明提到 $k,b$ 均默认为模 $p$ 意义下。一个自然的思路是二分，每次询问 $g(1)+g(x)$，如果 $[1,x)$ 中没有拐点答案应为 $(x+1)k+2b$，否则为 $xk+2b$。在已知 $k,2b$ 且 $k\not= 0$ 时可以据此判断出拐点所在位置，询问次数为 $\log_2n=30$。

接下来考虑 Sub3，也就是赛时的正解。Sub3 在 $P$ 改为 $50$ 的同时多了 $12$ 次询问，由前文不难想到我们应当用多出来的这 $12$ 次询问确定一个合适的 $p$，满足 $k\bmod p\not= 0$，在确定 $p$ 的同时还需要确定 $k,2b$ 的取值。

先解决第一个问题，对于某个 $p$ 如何判断 $k$ 在模 $p$ 意义下是否为 $0$。首先一次询问就确定不现实，因为这里有 $k,b$ 两个变量。两次的话只需要任选三个数 $x<y<z$ 满足 $y+1<z$ 然后询问 $g(x)+g(y)$ 与 $g(x)+g(z)$，将询问结果作差得到 $a=g(z)-g(y)=(z-y)k$ 或 $(z-y-1)k$，由于 $y+1<z$，$a=0$ 当且仅当 $k=0$。即 $k\bmod p=0\iff g(x)+g(y)=g(x)+g(z)$。

第二个问题是在找到一个合法的 $p$ 后如何求出 $k,2b$。考虑能否利用检验 $k\bmod p\not= 0$ 时得到的 $g(x)+g(y)$ 与 $g(x)+g(z)$ 来解出 $k,2b$。这看上去是一个模意义下的二元一次方程，可惜由于拐点的存在，未知元 $k$ 的系数是不确定的。好在当 $x+1=y,z+1=x$ 时我们能够根据交互库是否返回 `-1` 来排除拐点的影响，即询问 $s=g(x-1)+g(x)$ 与 $t=g(x)+g(x+1)$，如果两者中有任意一个返回了 `-1` 可以直接确定拐点，否则两个方程是确定的：

$$
\begin{cases}
(2x-1)k+2b=s\\
(2x+1)k+2b=t\\
\end{cases}\iff
\begin{cases}
k=\dfrac{t-s}{2}\\
2b=s-\dfrac{(2x-1)(t-s)}{2}
\end{cases}
$$

不妨令 $x=2$，则有：

$$
\begin{cases}
k=\dfrac{t-s}{2}\\
2b=\dfrac{3s-t}{2}
\end{cases}
$$

这里需要用到 $2$ 的逆元，如果 $2|p$ 那么 $k,2b$ 就又不确定了，因此 $p$ 的取值只能为奇数。现在需要从 $[1,50]$ 中选 $12/2=6$ 个奇数出来，满足它们中至少有一个能整除斜率 $k$，显然这 $6$ 个数的 $\operatorname{lcm}$ 越大越容易成功，问题变为选出 $\operatorname{lcm}$ 最大的 $6$ 个奇数。可以写个 dfs 搜，也可以直接手动构造，思路是贪心，从大到小选，每次选一个对当前 $\operatorname{lcm}$ 贡献最大的数丢进集合里，这个贪心在范围大的时候不对，但是范围小的时候能凑合着用。按这个思路选出来的数是 $49,47,45,43,41,37$，其 $\operatorname{lcm}$ 为 $6760214685$，设为 $B$。那么它够不够用呢？由于题目只给了 $g(x)$ 的上界，所以我们还需要分析一下斜率 $k$ 的上界。令 $g(x)$ 的上界为 $A$，则：

$$
\begin{gathered}
0\le k+b\le nk+b\le A\\
-b\le k\le \dfrac{A-b}{n}
\end{gathered}
$$

令 $b'=-b$，由 $-b\le \dfrac{A-b}{n}$ 得 $nb'\le A+b'\iff b'\le\dfrac{A}{n-1}$。那么 $k\le\dfrac{A+b'}{n}\le \dfrac{A+\frac{A}{n-1}}{n}=\dfrac{A}{n-1}$。对于 Sub5，将 $n=1162261531,A=7857125847061472735$ 代入得 $A\le6760204690<B=6760214685$，刚刚好。对于 Sub3,4，将 $n=10^9,A=10^{18}$ 代入显然也是符合要求的。但是有个小问题是 Sub3,4 中的 $n$ 有可能比 $10^9$ 小，它带来的影响是抬高了 $k$ 的上界，此时可能会用到多于 $6$ 个奇数，多一个奇数会使所需询问次数多 $2$，这意味着 $k$ 的上界 $\dfrac{A}{n-1}\ge B\iff n\le \left\lfloor\dfrac{A}{B}\right\rfloor+1=147924297$，也就说如果想要把上界抬高到 $6$ 个奇数无法搞定 $n$ 至少要降至 $147924297< \dfrac{10^9}{4}$，即二分次数至少会减 $2$，因此即使 $n<10^9$ 也不会出事。多两个奇数或更多也是类似的分析。至此我们解决了赛时的限制。

赛后毒瘤 yzy 把次数卡到了 $32$ 次。原本的做法由两部分组成：第一部分是根据事先定好的模数集合用 $12$ 次询问确定合适的模数 $p$，这过程中除了 $k,2b$ 的取值外不会获得任何有效信息，不过这已经很强了，因为它实际上给出了修改前的函数具体长啥样。第二部分是根据已知信息确定拐点位置，我们需要把这部分的次数卡到 $20$。回想最开始在 Sub2 中提到的二分做法，每次询问 $g(1)+g(x)$，然后把它与修改前 $g(1)+g(x)$ 应该是什么做对比，以此推出拐点对于 $x$ 的影响，进而得到拐点与 $x$ 的相对位置。这里固定的 $1$ 看起来很奇怪，因为 $1$ 始终不会受到拐点影响，那么感觉上讲根据 $g(1)+g(x)$ 能得到的信息不如询问 $g(x)+g(y)$。由于拐点会偏移一段后缀，因此 $g(x)+g(y)$ 的偏移量有三种可能：$0,k,2k$，分别对应拐点位于 $[y,r),[x,y),[l,x)$，其中 $[l,r)$ 为当前拐点所在的位置范围。所以把二分改为三等分当前区间，次数由 $\log_2 n$ 变为 $\log_3n$，刚好能通过 Sub5！

对于 Sub4 会遇到与之前同样的问题，也就是若 $n$ 减小导致 $k$ 的上界抬高对询问次数的影响。仍然套用前文的分析，然而 $147924297>\dfrac{10^9}{9}$，看起来有点寄，毕竟在上界抬高到 $6760214685$ 时 $\log_3 n$ 只减小了 $1$，而确定模数时用的询问次数增加了 $2$。幸运的是 $\lfloor\log_3{10^9}\rfloor=18$，换句话说它有 $2$ 次的冗余量，因此不会炸。而之后模数集合的大小不会增加太多，**粗略地估计**一下，大小每增加 $1$ 其 $\operatorname{lcm} B$ 就会翻至少 $20$ 倍。$n\le \left\lfloor\dfrac{A}{B}\right\rfloor+1$，所以 $n$ 的上界也会减少 $20$ 倍，对应 $\log_3 n$ 会减小 $2$，能够抵消模数集合大小增加 $1$ 对询问次数的影响。

实现时还有个细节是如何尽量三等分区间 $[l,r)$，设三等分点分别为 $x<y$，则 $x-l=y-x=r-y$，解得 $x=\dfrac{2l+r}{3},y=\dfrac{l+2r}{3}$。

代码如下（码 $\LaTeX$ 不易，能不能点个赞再走啊 awa）：

```
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define emp emplace
#define re return
//#define int ll 
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){int ch=getchar(),x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

namespace func{
int k=100,b=11111,t=7;
ll F(int x){
    if(t<x) return k*(x-1ll)+b;
    return (ll)k*x+b;
}
//using func::F;
int cnt;

inline int ask(int l,int r,int p){
    printf("? %d %d %d\n",l,r,p);
    cnt++;
    cout.flush();
    return read();
    //printf("%d\n",(F(l)+F(r))%p);
    //if(F(l)==F(r)) return -1;
    //return (F(l)+F(r))%p;
}

void answer(int x){
    printf("! %d\n",x);
    cout.flush();
    if(!read()) exit(0);
    //if(t!=func::t) exit(0);
//    cout<<"cnt="<<cnt<<'\n';    
}
}
using func::answer;
using func::ask;

const int P[]={49,47,45,43,41,37,31,29,25,23};
const int ni[]={25,24,23,22,21,19,16,15,13,12};
int n;

void solve(){
    int L=1,R=read(),q=read(),pp=read();
    if(pp==2){
        int l=1,r=R,mid;
        while(l<=r){
            //printf("[%d,%d]\n",l,r);
            if(r-l<=1){
                answer(l);
                return;
            }
            mid=l+((r-l)>>1);
            //printf("mid=%d\n",mid);
            int x=ask(1,mid,2);
            if(x==-1){
                answer(1);
                return;
            }
            if((mid&1)^(x&1)) l=mid;
            else r=mid;
        }
        re;
    }
    int p=0,k=0,b=0;
    fo(i,0,9){
        p=P[i];
        int x=ask(1,2,p),y=ask(2,3,p);
        if(x==-1){answer(1); re;}
        if(y==-1){answer(2); re;}
        if(x==y) continue;
        k=(y-x+p)*ni[i]%p;
        b=(x-3*k+3*p)%p;
        break;
    }
    while(R-L>1){//对开区间 [l,R) 三等分 
        int x=(2ll*L+R)/3,y=(L+2ll*R)/3;
        //printf("[%d,%d] %d,%d\n",L,R,x,y);
        int w=ask(x,y,p);
        if(w==-1){answer(x);re;}
        int a0=(k*(x-2ll+y)+b)%p,a1=(k*(x-1ll+y)+b)%p,a2=(k*(x+0ll+y)+b)%p;
        if(w==a0) R=x;
        if(w==a1) L=x,R=y;
        if(w==a2) L=y;
    }
    answer(L);
}

signed main(){
    int T=read();
    while(T--) solve();
    return 0;
}
```

---

## 作者：Eafoo (赞：5)

一道非常有意思的交互题。

# 一句话题意

给定函数 ：
$$
f(x) = 
\begin{cases}
kx + b & 1 \le x \le t \\
k(x - 1) + b & t < x \le n
\end{cases}
$$

每次你可以给出一个询问 $Ask(l, r, p)$，若 $f(l) = f(r)$ 则返回 $-1$，否则返回 $(f(l) + f(r)) \mod p$

# 挖掘性质

首先这个函数肯定长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/7qft0sn1.png)

我们要做的，就是求出中间那一段平台的左端点

既然它给的这个函数很像一次函数，那么我们考虑解出它的斜率，

显然有：

$$
\begin{aligned}
 & Ask(1, 3, p) - Ask(1, 2, p) \\
=\,\,\,& (f(1) + f(3) - f(1) - f(2)) \mod p \\
=\,\,\,& (f(3) - f(2)) \mod p \\
=\,\,\,& k \mod p
\end{aligned}
$$

但是如果 $p$ 能够整除 $k$，那么解出的斜率为 $0$，没有任何作用，所以我们考虑重复选取多个 $p$ 求斜率，直到解出的斜率不为 $0$ 为止。

那么我们要试的 $p$ 应该是什么呢？

考虑如果一个斜率能够被所有试选数整除，那它一定是所有试选数的倍数。

由于我们能构造出的最小的这样的斜率便是试选数的 lcm，因此，我们首先要保证所有试选数的 lcm 大于理论的斜率最大值。

其次，由于求解需要花费一定的次数，而我们检验一个试选数需要花费两次询问，所以我们还要把握好试选数的个数。

至于具体选哪些试选数，我们留到后面再说。

# 解出答案

假定我们已经成功求出了一个模意义下的斜率，那么现在我们的任务是找到 $t$

首先考虑 Subtask 2，既然斜率一定为奇数，那么就一定有 ：

$$
Ask(1, x, 2) = 
\begin{cases}
(x - 1) \mod 2 & 1 \le x \le t \\
x \mod 2 & t < x \le n
\end{cases}
$$

我们直接根据此性质二分 $x$，便可以轻松解决 Subtask 2

考虑在任意情况下二分。

设 $g(x) = 2 \cdot f(x) \mod p$，那么显然有 $g(x) = (Ask(x, x + 1) - k) \mod p$

考虑在刚刚找模数的过程中，我们已经顺便可以求出 $g(1)$ 了，那么我们又有：

$$g(x) = (g(1) + 2 \cdot (x - 1) \cdot k) \mod p$$

所以：

$$
2 \cdot Ask(1, x, p) = 
\begin{cases}
(g(1) + g(x)) \mod p & 1 \le x \le t \\
(g(1) + g(x) - 2 \cdot k) \mod p & t < x \le n
\end{cases}
$$

通过二分 $x$，我们便可以求得答案了，但是这样会超次数。

于是我们考虑三分，每次考虑一个区间 $[l, r]$，设 $lmid = l + \lfloor \frac{(r - l)}{3} \rfloor$，$rmid = r - \lfloor \frac{(r - l)}{3} \rfloor$

有：

$$
Ask(lmid, rmid, p) \cdot 2 = 
\begin{cases}
(g(lmid) + g(rmid)) \mod p & 1 \le lmid \le rmid \le t \\
(g(lmid) + g(rmid) - 2 \cdot k) \mod p & lmid \le t < rmid \\
(g(lmid) + g(rmid) - 4 \cdot k) \mod p & t < lmid \le rmid \\
\end{cases}
$$

于是我们就可以三分了。

由于每次区间长度缩小到原来的 $\frac{1}{3}$，所以对于给定的 $n$，三分次数为 $\lfloor \log_3 n \rfloor + 1$，我们取 $n = 3 ^ {19} = 1162261467$，此时三分次数为 20 次。由于 $0 \le f(x) \le 7857125847061472735$，所以取 $b = -k$，解得此时理论斜率最大值为 $6760205057$

我们还剩 12 次机会来选模数，那么试选数的数量最多为 6。

注意到我们有乘二的操作，所以我们的试选数不能是二的倍数，否则当 $2k = p$ 时会直接崩掉。

所以我们通过 DFS 找出一组 lcm 最大的数：

``` cpp
int l = 30, r = 50;
ll a[7], b[7], ans = 0;
void DFS(int k, int now) {
    if (k == 7) {
        ll res = 1;
        fop(i, 1, 6) res = res / __gcd(res, a[i]) * a[i];
        if (res > ans) { fop(i, 1, 6) b[i] = a[i]; ans = res; }
        return;
    }
    fop(i, now + 1, r) if (i & 1) a[k] = i, DFS(k + 1, i);
}
int main() {
    DFS(1, l);
    fop(i, 1, 6) printf("%lld ", b[i]);
    printf(": %lld\n", ans);
}
```

发现这组数为 49, 47, 45, 43, 41, 37，并且它们的 lcm 为 $6760214685$，大于理论斜率最大值，符合题意。

另外，如果将 $n$ 缩小来增加三分次数，我们可以用类似的方法证明只要顺着质数表往下选，次数依然在合法范围内。

只要有一个优秀的三分实现（我一开始因为三分写得丑被卡次数了），再注意各种细节，这道题就解决了。

# 参考代码

``` cpp
#include <bits/stdc++.h>
#define ff fflush(stdout)
#define fop(x, l, r) for (register int x = l; x <= r; ++x)
#define pof(x, r, l) for (register int x = r; x >= l; --x)
using namespace std;
typedef long long ll;
#define int ll // 呃呃
int read() {
    int x = 0; char c; bool f = 0;
    while (!isdigit(c = getchar())) if (c == '-') f = 1;
    do x = (x << 1) + (x << 3) + (c ^ 48); while (isdigit(c = getchar()));
    return f ? -x : x;
}

int tes[] = { 0, 49, 47, 45, 43, 41, 37, 31, 29, 23, 19, 17, 13, 7, 5 }; // 试选数

#ifdef DEBUG
// 本地调试
int K = 209566655235, b = -209566655206, t = 262157;
int tot = 0;
__int128_t f(int x) { if (x <= t) return (__int128_t)K * x + b; else return (__int128_t)K * (x - 1) + b; }
int Ask(int l, int r, int p) { ++tot; if (f(l) == f(r)) return -1; return (f(l) + f(r)) % p; }
void Guess(int p) { printf("tot = %lld, p = %lld\n", tot, p); if (p == t) puts("OK"); else puts("WRONG"); }
#else
// oj
int tot = 0;
int Ask(int l, int r, int p) { printf("\n? %lld %lld %lld\n", l, r, p); ff; int x = read(); assert(x != -2); return x; }
void Guess(int p) { printf("\n! %lld\n", p); ff; assert(read()); }
#endif

int k, p, g1;
int g(int x) { return (g1 + (x - 1) * k % p * 2 % p) % p; } // = 2f(x)

void Work2(int n) { // 特判 Subtask 2
    int l = 1, r = n, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int res = Ask(1, mid, 2);
        if (res == -1) { ans = 1; break; }
        if (res != (mid % 2)) l = mid + 1, ans = mid;
        else r = mid - 1;
    }
    Guess(ans);
}
void Solve() { 
    int n = read(), q = read(), P = read();
    if (P == 2) return Work2(n); // 特判 Subtask 2
    int x = 0;
    int lim = ceil(log(n) / log(3)) + 1; // 最大三分次数
    k = 0;
    fop(i, 1, min(q - lim, 14ll)) {
        p = tes[i];
        if ((x = Ask(1, 2, p)) == -1) return Guess(1); // 注意特判
        k = ((Ask(1, 3, p) - x) % p + p) % p;
        if (k) break;
    }
    if (!k) return Guess(2); // 找不到合适模数就是 t = 2 了
    int l = 1, r = n;
    g1 = (x - k + p) % p;
    while (l < r) { // 三分
        int len = r - l + 1;
        if (len == 2) return (Ask(l, r, p) == -1) ? Guess(l) : Guess(r);
        if (len == 3) {
            if (Ask(l, l + 1, p) == -1) Guess(l);
            else if (Ask(l + 1, l + 2, p) == -1) Guess(l + 1);
            else Guess(l + 2);
            return;
        }
        int lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
        if (max({ lmid - l, rmid - lmid + 1, r - rmid + 1 }) - min({ lmid - l, rmid - lmid + 1, r - rmid + 1 }) >= 2) ++lmid;
        int res = Ask(lmid, rmid, p);
        if (res == -1) return Guess(lmid); // 注意特判
        int x = res * 2 % p, y = (g(lmid) + g(rmid)) % p;
        if (x == y) l = rmid;
        else if ((x + k + k) % p == y) l = lmid, r = rmid;
        else r = lmid - 1;
    }
}

signed main() { int T = read(); while (T--) tot = 0, Solve(); }
```

---

## 作者：星星与辰 (赞：2)

## 题意

~~虽然题面已经写得很清楚了~~。

存在一个函数：
$$ g(x)=\left\{
\begin{array}{rcl}
kx + b       &      & {1 \leq x \lt t}\\
kt + b     &      & {t \leq x < t + 1}\\
k(x - 1) + b     &      & {t + 1 \leq x \leq n}\\
\end{array} \right. $$
我们并不知道其中的 $k,b,t$ 是什么，每一次我们可以进行不超过 $Q$（每个测试点均不同）次询问，每一次可以给交互库三个数 $l,r,p$，交互库将会返回 $x = l,r$ 时，函数 $g(x)$ 的值的和对 $p$ 取模的结果。

## 思路
看数据范围是肯定要对数据点进行分治的，毕竟第二个范围明显是要特判的，而且这个数据点有一个非常有启发意义的性质，斜率 $k$ 为奇数。设函数 $f = kx + b $，则可知函数 $g$ 是由函数 $f$ 在某一个位置右移产生的，假如 $x\gt t$，在被右移的部分，其对应的函数值实际上是函数 $f$ 上对应的 $f(x - 1)$ 的值，而在这个性质下，满足这样一个显然的式子：
$$f(x) \not \equiv f(x - 1) \pmod 2$$
还可以由此推知一下两条显然的式子：

$$f(x) \equiv f(x + 2) \pmod 2$$
$$f(x) + f(y) \equiv x + y \pmod 2
$$


若我们知道本来 $f(l) + f(r)$ 对应的奇偶性，如果发现 $g(l) + g(r)$ 的奇偶性不同时，只有一种情况， $r$ 在被右移的函数部分，并且 $l$ 不在，因为两者同时改变奇偶性时，整体和的奇偶性不变，而 $l$ 如果在被右移的部分，则 $r$ 必须在，那么只可能是 $r$ 在 $l$ 不在，仔细思考后，发现实际上我们可以通过询问得到 $l,r$ 是否位于 $t$ 的同侧，那么如果我们直直接确定 $l\leq t$ 时，比如说钦定 $l$ 为 $1$，为奇数，则由上面的式子可知，若 $r$ 对应的奇偶性与返回值不同，则可知 $r\leq t$ 否则 $r \gt t$，发现这个可以用二分做，总次数 $O(\log n)$。

那么第二个捆绑测试就可以搞定了，但是其他数据点又不保证存在这样的性质不能用钦定模数为 $2$ 来做，而我们的目标却是满分！不过回顾一下刚刚捆绑测试2的做法，发现事实上真正重要的性质是 $f(x) \not\equiv f(x - 1) \pmod p$，因为当这个条件符合时，我们可以迅速判断当前的 $r$ 在 $t$ 的哪个方位，显然地，满足这个条件的前提是 $p \nmid k$。

然后仔细一看发现这个 $Q$ 的限制除了最后一个点外都并不是很紧，我们掐指一算，除了二分找答案的必要的 $30$ 次操作外，竟还剩下 $12$ 次操作！也就是说是可以尝试枚举这个 $p$ 的，现在考虑怎样确定一个 $k\mod p\neq 0$ ，用一次询问肯定不行，毕竟你并不知道 $b$ 模 $p$ 为多少，至少存在两个未知数！那么两次操作怎么做，那很简单，假如我两次询问的分别是 $l1,r1,l2,r2$ 均在 $t$ 的左侧，其对应的返回值为 $v1,v2$ 那么可以像求一次函数一样求出来：
$$k = (v1 - v2)\div(l1+r1-l2-r2) \pmod p$$
$$b = v2 - (l2+r2)\times k \pmod p$$
我们可以令 $l1 = 1 ,r1 = 2 , l2 = 2 , r2 = 3$ 来降低它们属于 $t$ 右侧的概率，但是总归还是有可能在 $t$ 右侧的，那么只可能是因为 $t = 1$ 或者 $t = 2$ 不过因为 $1 + 1 = 2 , 2 + 1 = 3$ ~~好像废话~~，这两种情况会分别在两次询问中返回 $-1$ 这时候也可以立马得到 $t$ 的位置，更不同枚举 $p$ 了。

但是如果一直没找到这样的 $p$ 怎么办，放心每一个 $p$ 花费两次询问，可以枚举 $6$ 个 $p$，若没有符合条件的 $p$ 则 $k$ 至少得为这 $6$ 个 $p$ 的最小公倍数，只需要找到 $6$ 个本身在合法范围内且其最小公倍数大于等于 $k$ 的极限范围的即可，这里给出合法的一组 ${49, 47, 45, 43, 41, 37}$。于是除了最后一个测试点就都搞定了。

但是我们的目标还是满分！

仔细观察一下最后一个数据点的数据范围，算了一下用 $g(x)$ 的限制算了 $k$ 的最大值： $78571258470614727357857125847061472735 / 1162261531 = 6760204685$，这个数字正好是我给的 $6$ 个数组的最小公倍数。那 $n$ 的范围是什么意思？用计算机一试发现$3^{19}=1162261467$，与其极其相似！所以就猜到了，啊不，是知道了要用三分。

怎么三分呢？注意到我们当前的询问一直在做一件很蠢的事，那就是钦定 $l = 1$，如果我们能将 $l$ 利用起来呢？怎么利用？我们发现有一个这样的性质：
$$ (g(l) + g(r)) =\left\{
\begin{array}{rcl}
(f(l) + f(r))       &      & {1\leq l \lt r \lt t}\\
(f(l) + f(r - 1)    &      & {l \lt t \leq r < t + 1}\\
(f(l - 1) + f(r - 1))      &      & {t + 1 \leq l \lt r \leq n}\\
\end{array} \pmod p\right. $$

而这三种情况在 $p \gt 2$ 时对应的值均不相等，也就是说可以尝试用 $l$ 把当前区间再切一刀，来实现三分的过程，于是这样就做完了。
注意第二个测试点由于 $p \leq 2$ 一定不能与其他点用同样的做法，要单独拎出来做。

[Code](https://www.luogu.com.cn/paste/qw6ubybl)

## 一些小优化
发现我们前面询问的 $6$ 个 $p$ 浪费的询问实际上很无用，我们可以用随机优化一下，但是更好的是直接在询问时同时确定 $t$ 是否小于等于 $12$，可以缩小三分的区间，不过效果微乎其微。

---

## 作者：oOoOoOOOooOO (赞：1)

## 思路
把 $subtask$ 分成两类来解决  。

* $k$ 为奇数且 $P=2$。  


$$ 
    query(1, x, 2) = 
    \begin{cases}
    ((x + 1) \times k + 2\times b) \bmod 2 = (x + 1) \bmod 2 & x \in [1,t] \\
    (x \times k + 2\times b) \bmod 2 = x \bmod 2 & x \in [t + 1, n]
    \end{cases}
$$  
$n \le 10^9, q = 30$ 直接二分就可以。

* $k$ 无特殊性质，且 $P \leq 50$。  
**假设存在 $M$，使得 $2 \times k \bmod M \neq 0$。**  
$$t \in [l, r], midl < midr,midl \ge l,midr \le r$$

$$ 
    query(midl, midr, M) = 
    \begin{cases}
    (k \times (midl + midr) + 2\times b)\bmod M  &  t \in [midr, r] \\
    (k \times (midl + midr - 1)+ 2\times b)\bmod M & t \in [midl, midr] \\
    (k \times (midl + midr - 2)+ 2\times b)\bmod M & t \in [l, midl - 1] \\
    \end{cases}
$$ 
如果已知 $k \bmod M$ 以及 $2\times b \bmod M$，那我们就可以用三分去解决这个问题。  

下面分析一下如何找到这个 $M$

当 $t < n - 1$，且 $query(1, n, M) \neq query(1, n - 1, M)$ 时，通过作差可以知道 $k \bmod M \neq 0$，如果 $M \mod 2 \neq 0$，则可以知道 $2\times k \bmod M \neq 0$。  
所以现在问题变成找到一组集合，使得至少存在一个数，使得这个数满足 $M$ 的条件，并且集合尽量小，集合满足任意两个数互质，爆搜求得集合。
$$S = \left\{ 49,47,45,43,41,37,31,29,23,19,17,13 \right\} $$
**从大到小选取，当选中的数乘积大于 $k$ 时，选中的数里至少存在一个合法的 $M$**。  

每次测试一个选中的数需要询问两次，剩下的次数则是三分 $n$。  
当 $k$ 恰好小于 $\prod_{i=0}^{x} S[i]$ 时，所需总次数为 $2 \times (x + 1) + \lceil \log_{3}{(2 \times n - 1)} \rceil$  
因为 $ 0 \le g(n) = k \times (n - 1) + b $，显然当 $b = -k$ 时，$k$ 取得最大值 $ \lfloor \frac{g(n)}{n - 2} \rfloor $，根据上面计算次数的方式以及对应的集合 $S$，可以知道最大询问次数不会超过 $32$ （暴力验证）  

如果 $t = n - 1$
>从大到小选取，当选中的数乘积大于 $k$ 时，选中的数里至少存在一个合法的 $M$。

**上述条件会不满足**，即对于选中的任何数 $x$，都有 $query(1, n, x) = query(1, n - 1, x)$。  
这种情况下我们只需要在枚举完集合后还没找到合适的 $M$ 就可以确定 $t = n - 1$。


**实现的时候注意亿点细节当 $query(l, r, mod) = -1$ 时，$t = l$。**

代码
```cpp
#include <bits/stdc++.h>
#include <type_traits>
#define pb push_back
#define mp make_pair
#define bg begin
#define ed end
#define all(x) (x).bg(),(x).ed()
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 xl;

typedef pair<int,int> pii;
typedef pair<int,pii> piii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef vector<pll> vll;
typedef vector<ll> vl;

template<typename Ta, typename Tb>
std::ostream & operator << (std::ostream & o, const std::pair<Ta, Tb> &p)
{
    o << p.first << " " << p.second;
    return o;
}

std::ostream & operator << (std::ostream & o, xl v)
{
    if(v < 0)o << '-', v *= -1;
    if(v >= 10)o << v / 10;
    o << (int)(v % 10);
    return o;
}

template<typename T>
struct is_string : public std::false_type { };

template <>
struct is_string<std::string> : public std::true_type {};

template<typename T, template<class, class...> typename C, class... Args>
typename std::enable_if<!is_string<C<T, Args...>>::value, std::ostream&>::type
        operator << (std::ostream & o, const C<T, Args...> &obj)
{
    for(const auto & x : obj)
    {
        o << x << ",";
    }
    return o;
}

#ifdef local
#include "mydebug.h"
#define de(...) pretty_dbg(cerr,__LINE__,__func__,##__VA_ARGS__);
#else
#define de(...) void(0);
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 2e6 + 8;
const int M = 2e5 + 8;
int T = 1;

const int inf = 0x3f3f3f3f;
const ll INF = 1ll<<61;
const int mod = 998244353;
ll li = 1760204685ll;

vl coprime = {49,47,45,43,41,37,31,29,23,19,17,13};
ll mx = 1;
int num = 0;
vl fp;

void dfs(ll s, vl f, ll tp)
{
    if(s == 1) return ;
    if(tp >= li)
    {
        num = f.size();
        mx = tp;
        fp = f;
        return;
    }
    if(f.size() + 1 >= num)
    {
        return;
    }
    bool can = true;
    if(s % 2 == 0)can = false;
    for(auto v : f)
    {
        if(__gcd(s, v) != 1)
        {
            can = false;
        }
    }
    if(can)
    {
        auto fg = f;
        fg.pb(s);
        dfs(s - 1, fg, tp * s);
    }
    dfs(s - 1, f, tp);
}

ll k = 182708505ll, b = -182703198;
int t = 14348907;
ll fakeg(ll x)
{
    if(x < t) return k * x + b;
    else if(x >= t + 1) return k * (x - 1) + b;
    else return k * t + b;
}

int gl = 0;
int n;

ll ask(ll l, ll r, ll p)
{
    ++gl;
    cout << "? " << l << " " << r << " " << p << endl;
#ifdef local
    if(fakeg(l) != fakeg(r))
    {
        return (fakeg(l) + fakeg(r)) % p;
    }
    else
        return -1;
#endif // local
    ll v;
    cin >> v;
    if(v == -2) exit(0);
    return v;
}

void answer(int x)
{
    cout << "! " << x << endl;
    if(T)
    {
        int k;
        cin >> k;
        if(k == 0)exit(0);
    }
}

void solve()
{

//    cout << mx << " " << k << endl;
    gl = 0;
    int q;
    ll p;
    cin >> n >> q >> p;
    if(p == 2)
    {
        ll l = 1, r = n;
        while(l + 1 < r)
        {
            int mid = (r + l) >> 1;
            int v = ask(1, mid, 2);
            if(v == -1)
            {
                answer(1);
                return;
            }
            if(v == (1 + mid) % 2)
            {
                l = mid;
            }
            else
            {
                r = mid;
            }
        }
        answer(l);
    }
    else if(n == 2)
    {
        if(ask(1, 2, 2) == -1)
        {
            answer(1);
        }
        else
        {
            answer(2);
        }
    }
    else
    {
//        num = 100;
//        li = 7857125847061472735ll / (n - 2);
//        dfs(50, {}, 1);
//        coprime = fp;

//        cout << coprime << endl;
        vector<vl> can;
        ll mo = -1;
        ll mok = -1;
        ll mo2b = -1;
        for(auto v : coprime)
        {
            int v1 = ask(1, n, v);
            int v2 = ask(1, n - 1, v);
            if((v1 - v2 + v) % v  != 0)
            {
                mo = v;
                mok = (v1 - v2 + v)  % v;
                mo2b = (v1 - mok * n % v + v) % v;
                can.pb({mo, mok, mo2b});
            }
            if(can.size()) break;
        }
        if(can.size() == 0)
        {
            answer(n - 1);
            return;
        }
        ll l = 1, r = n;
        ll llen = r - l + 2;
        while(l < r)
        {
            llen = r - l + 1;
            if(r - l == 1)
            {
                if(ask(l, r, 2) == -1)
                {
                    answer(l);
                }
                else
                {
                    answer(r);
                }
                return;
            }
            else if(r - l == 2)
            {
                if(ask(l, l + 1, 2) == -1)
                {
                    answer(l);
                }
                else if(ask(l + 1, l + 2, 2) == -1)
                {
                    answer(l + 1);
                }
                else
                {
                    answer(l + 2);
                }
                return;
            }
            ll midl = l + (r - l) / 3;
            ll midr = r - (r - l) / 3;
            vl f = {midl - l, midr - midl + 1, r - midr + 1};
            if(*max_element(all(f)) - *min_element(all(f)) >= 2)
            {
                midl++;
            }

            for(auto s : can)
            {
                ll v1 = ((midl + midr) * s[1] + s[2]) % s[0];
                ll v2 = ((midl + midr - 1 + s[0]) % s[0] * s[1] + s[2]) % s[0];
                ll v3 = ((midl + midr - 2 + s[0]) % s[0] * s[1] + s[2]) % s[0];
                if(set<ll>({v1, v2, v3}).size() == 3)
                {
                    ll v = ask(midl, midr, s[0]);
                    if(v == -1)
                    {
                        answer(midl);
                        return;
                    }
                    if(v == v1)
                    {
                        l = midr;
                    }
                    else if(v == v2)
                    {
                        l = midl, r = midr;
                    }
                    else if(v == v3)
                    {
                        r = midl - 1;
                    }
                    else
                    {
                        assert(false);
                    }
                    break;
                }

            }

        }
        answer(l);
    }
}

int main()
{
#ifdef local
    freopen("in.txt", "r", stdin);
#endif // local
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#define mulcase

#ifdef mulcase
    cin >> T;
#endif // mulcase
    while(T--)
    {
        solve();
    }

    return 0;
}
```

---

