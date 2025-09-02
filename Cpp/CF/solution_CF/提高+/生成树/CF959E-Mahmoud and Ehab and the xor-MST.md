# Mahmoud and Ehab and the xor-MST

## 题目描述

Ehab is interested in the bitwise-xor operation and the special graphs. Mahmoud gave him a problem that combines both. He has a complete graph consisting of $ n $ vertices numbered from $ 0 $ to $ n-1 $ . For all $ 0<=u<v<n $ , vertex $ u $ and vertex $ v $ are connected with an undirected edge that has weight ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/31294aedffbec70e119efb89ca1f6d2afecc694a.png) (where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/bc47da33894a98df53134f30108d8405a90ea418.png) is the [bitwise-xor operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)). Can you find the weight of the minimum spanning tree of that graph?

You can read about complete graphs in [https://en.wikipedia.org/wiki/Complete\_graph](https://en.wikipedia.org/wiki/Complete_graph)

You can read about the minimum spanning tree in [https://en.wikipedia.org/wiki/Minimum\_spanning\_tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree)

The weight of the minimum spanning tree is the sum of the weights on the edges included in it.

## 说明/提示

In the first sample: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF959E/da1dd366c44de9a7fa58c6a7748f6a57cd6a4b83.png) The weight of the minimum spanning tree is 1+2+1=4.

## 样例 #1

### 输入

```
4
```

### 输出

```
4```

# 题解

## 作者：do_while_true (赞：8)

直接考虑模拟 Kruskal．

假设有 $k$ 个二进制位。

- 首先加入权为 $1$ 的边，那么二进制下前 $(k-1)$ 位相同的在一个连通块里。
- 加入权为 $2$ 的边，二进制下前 $(k-2)$ 位相同的连通。
- 加入权为 $3$ 的边，由于 $x\operatorname{xor}y=3$ 一定满足前 $(k-2)$ 位相同，所以并不会产生连通块的合并。
- ......

则可以发现加入权为 $2^{t-1}$ 的边时，会使二进制下前 $(k-t)$ 位相同的合并在一起。加入的边数即为之前合并出来的连通块数除以 $2$ 上取整。

然后权值大于 $2^{t-1}$ 且小于 $2^t$ 的边都没有用了，因为两个点之间有这样一条边一定满足前 $(k-t)$ 位相同。

令 $i=2^t$，则答案为：

$$
\sum i\times \left\lfloor\frac{\left\lceil\frac{n}{i}\right\rceil}{2}\right\rfloor
$$

```cpp
#include<iostream>
long long n,ans;
signed main(){
	std::cin >> n;
	for(long long i=1;i<=n;i*=2)
		ans+=i*((n+i-1)/i/2);
	std::cout << ans << '\n';
	return 0;
}
```

---

## 作者：Arghariza (赞：4)

根据 `Prim` 的原理，新加入一个点 $x$，我们可以挑一条与其连着的权值最小的边，对答案贡献 $\min \limits_{k=1}^{x-1}\{x⊕k\}$。

- 若 $x=2^y$，由于此时 $2^y$ 那位永远为 $1$，显然有 $\min \limits_{k=1}^{x-1}\{x⊕k\}=x$，取 $k=0$ 即可。
- 否则 $x$ 为 $1000...01(00..)$ 的形式，设最低位 $1$ 在 $2^p$ 处，则 $\min \limits_{k=1}^{x-1}\{x⊕k\}\ge 0$，由于取等需要 $x=k$，不符条件，所以 $\min \limits_{k=1}^{x-1}\{x⊕k\}=2^p$。

综合一下，于是我们惊奇地发现贡献就是 $lowbit(x)$。

所以 $f_n=f(n-1)+lowbit(n-1)=\sum\limits_{i=1}^{n-1}lowbit(i)$，归纳可证。

至此我们有了 $O(n)$ 做法，可惜不足以通过此题。

继续发掘 $lowbit$ 的性质，设 $v=lowbit(x)$，则有 $2^v\mid x$，并且 $2^{v+1}\nmid x$。

于是我们可以单独计算每个 $v$ 对答案的贡献，由小学数论知识，不难算出为 $\left(\left\lfloor\dfrac{n-1}{2^v}\right\rfloor-\left\lfloor\dfrac{n-1}{2^{v+1}}\right\rfloor\right)2^v$。

答案即为 $\large\sum\limits_{v=0}^{\log (n-1)}\left(\left\lfloor\dfrac{n-1}{2^v}\right\rfloor-\left\lfloor\dfrac{n-1}{2^{v+1}}\right\rfloor\right)2^v$，复杂度 $O(\log n)$。

[AC 记录](https://codeforces.com/contest/959/submission/173052407)

---

## 作者：芦苇林 (赞：3)

好像没有数学证明诶，我来补一篇叭QwQ

[原题链接](https://codeforces.com/problemset/problem/959/E) 

[宣传博客](https://www.cnblogs.com/violetholmes/p/14363972.html)

## 题解

为避免构造时出现环，令父结点编号小于子节点。可以发现，对于整数$x$，满足$y<x$且$y^\wedge x$最小的$y$为$x-lowbit(x)$，此时边$(y,x)$的权值为$lowbit(x)$。如此构造，$ans=\sum\limits_{i=1}^{n-1}lowbit(i)$（$lowbit(1)=1$而$lowbit(n)\ge 1$，因此$sum$区间为$[1,n-1]$而非$[2,n]$）。如果暴力求和时间复杂度为$O(n)$，而我们需要使时间复杂度在$logn$以内，仍需进一步推导。

设整数$x,y$满足$ x=lowbit(y),1 ≤ y ≤ n $。因为$lowbit$一定为$2$的整数次幂，所以当且仅当$x$为$2$的整数次幂时$y$的个数$ > 0$。可以发现，当$y=y+2x$时，$lowbit(y)$是不变的（因为进行运算的为$lowbit$左侧的数位）。因此对于每个$x$，$y$的值为一个等差数列：首项为$x$，公差为$2x$。例如$x = 4$时$y$组成的数列为$\{4,12,20, 28,...\}$。所以每一个二进制位对答案的贡献便是对应序列$\le n$的元素个数$\times i$，也就是$(\lfloor \frac{n-i}{2i}\rfloor+1)\cdot i$（首项为$i$所以元素个数为$\frac{n-i}{2i}$向下取整$+$首项）。这样我们只需枚举$\le n$的$2$的整数次幂，时间复杂度$O(logn)$。

## AC代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    int n,ans=0;
    scanf("%lld",&n); n--;
    for(int i=1;i<=n;i<<=1) ans+=((n-i)/(i*2)+1)*i;
    printf("%lld",ans);
}
```


---

## 作者：jch123 (赞：3)

## 解题思路

看到 $n$ 的范围，显然不能直接建图。考虑模拟 Kruskal 过程，假设在二进制下有 $k$ 位。

- 加入边权为 $1$ 的边，边权为 $1$ 代表 $i$ 和 $j$ 的前 $k-1$ 位相同。
- 加入边权为 $2$ 的边，一定满足 $i$ 和 $j$ 的前 $k-2$ 位相同。
- 加入边权为 $3$ 的边，一定满足 $i$ 和 $j$ 的前 $k-2$ 位相同。
- 加入边权为 $4$ 的边，一定满足 $i$ 和 $j$ 的前 $k-3$ 位相同。
- ……

发现加入边权为 $2^h$ 的边时，会让二进制下前 $k-h+1$ 连通，然后发现大于 $2^h$ 小于 $2^{h+1}$ 的边就没用了，因为所有前 $k-h+1$ 位相同的已经连通了。

然后考虑答案，枚举 $i=2^h$ 然后答案为 $\sum i\times \left\lfloor\frac{\left\lceil\frac{n}{i}\right\rceil}{2}\right\rfloor$。

$\left\lceil\frac{n}{i}\right\rceil$ 是因为看这一位每隔多少出现一次，除以 $2$ 是因为只能是 $0$ 到 $1$ 不能从 $1$ 到 $0$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	ll n,ans=0;
	cin>>n;
	for(ll i=1;i<=n;i*=2ll)
	{
		ll x=ceil((double)n/i);
		ans+=i*(x/2);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：minecraft_herobrine (赞：2)

读完题发现输入仅有一个整数，~~根据我多年的经验~~可以看出有可能要打~~亿~~个表找规律，在纸上画了画发现，假如我们把输入的 $n$ $(n\ge2)$ 和对应的答案做一下对比，我们得到了

|类型\\空行|  |  |  |  |  |  |  |  |  |  |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | 
|**点数（输入）**|2|3|4|5|6|7|8|9|10|11|
|**答案值**|1|3|4|8|9|11|12|20|21|23|
|**较上一个增量**|1|2|1|4|1|2|1|8|1|2|

注意增量那行的数据，相信很多人在初学树状数组的时候都见过这样一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/h0z5jcob.png)

蛤？增量怎么和这个lowbit值分布的一毛一样？

![](https://cdn.luogu.com.cn/upload/image_hosting/vu9761sl.png)

ok我们现在呢已经发现了结论，本着精益求精的态度让我们来证明一波（半感性理解）

用递推的方法

当 $n=1$ 时，一条边也没得选，最小生成树就是这个点，边权总和显然为 $0$ 。

当 $n=2$ 时，由于只有两个结点，所以最小生成树的权值和显然为 $1$（就一条边还咋选）

当 $n\ge 3$ 时，结点 $0$ 至 $n-2$ 已经是最小生成树，设结点 $n-1$ 是新来的结点，则它有 $n-1$ 种选择。

![](https://cdn.luogu.com.cn/upload/image_hosting/xg6d4ubi.png)

红色的边是可选的新边

若选择了结点t，则新建边对应的边权就是 $n \oplus t$ ，那怎么让这个值更小呢？显然我们可以选择 $t=(n-1)-lowbit(n-1)$ 因为这保证了异或时只有最低的那位是1，其它位都变成了0。一定可以保证它是最小的。

接下来的过程就以此类推了，证毕

----
$add*(n/2)$
结论的正确性是证明了，可一般对于这个 $lowbit$ 数列，大多数情况都是按树状数组的方法“向上求和”，但这里是要算前缀和。利用树状数组的概念，同层之间节点的编号的$lowbit$值相等。并且通过观察不难得到，角标为奇数的点的$lowbit$值一定是1。设变量$add$表示当前层的$lowbit$值，则$res$每次应当累加一个$add*\lfloor n/2\rfloor$，随后$add\times 2$，$n=\lfloor n/2\rfloor $

最后一段具体可以看一下代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	ll n,m,res=0,add=1;
	scanf("%lld",&n);
	n--;
	while(n>0)
	{
		m=n/2;
		res+=(n-m)*add;
		n=m;add*=2;
	}
	printf("%lld",res);
	return 0;
}

```

---

## 作者：jijidawang (赞：2)

~~从 0 编号真难受啊~~

考虑归纳 .

令 $n-1$ 个节点的答案为 $f(n)$，则加一个节点 $n-1$ 就和前面所有点连一条边 .

根据 Prim 原理，只需要挑一条最小的和 $n-1$ 连着的边然后加进 MST 里就好了 .

现在的问题是最小边的边权是多少，显然就是
$$\min_{0\le x<n-1}\{x\oplus(n-1)\}=\operatorname{lowbit}(n-1)$$

于是 $f(n)=f(n-1)+\operatorname{lowbit}(n-1)$ .

简单处理一下边界就可以得到通项公式：
$$f(n)=\sum_{i=1}^{n-1}\operatorname{lowbit}(i)$$
按位考虑，钦定一个 $\operatorname{lowbit}(i)$ 然后更高位随便选，这样就是 $O(\log n)$ 的了 .

核心代码，仅供参考
```cpp
ll x, ans;
int main()
{
	scanf("%lld", &x); --x;
	for (int i=0; x>>i; i++) ans += ((x >> i) - (x >> (i+1))) * (1ll << i);
	printf("%lld\n", ans); 
	return 0;
}
```

---

## 作者：aRenBigFather (赞：2)

# 没有人发找规律的题解,我发一发
~~(对于数学不好的我只能找规律...)~~

### 首先是一发暴力Kruskal生成树代码
-------
```cpp
#include <bits/stdc++.h>
using namespace std;
struct edge{
    int u,v,len;
};
vector<edge> G;
int fa[500];
void initFa(){
    for(int i=0;i<500;i++) fa[i] = i;
}
int get(int x){
    if(fa[x] == x) return x;
    return fa[x] = get(fa[x]);
}
void merge(int x,int y){
    x = get(x),y=get(y);
    if(x != y) fa[y] = x;
}
void addedge(int u,int v,int w){
    G.push_back((edge){u,v,w});
}
inline bool cmp(const edge &a,const edge &b){return a.len < b.len;}
int Krus(){
    int ans = 0;
    initFa();
    sort(G.begin(),G.end(),cmp);
    for(int i=0;i<G.size();i++){
        int fu = get(G[i].u),fv = get(G[i].v);
        if(fu != fv){
            ans += G[i].len;
            merge(G[i].u,G[i].v);
        }
    }
    return ans;
}
int main(){
    for(int n=2;n<=17;n++){
        //int n = 3;
        G.clear();
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                addedge(i,j,i^j);
            }
        }
        cout << "> n = " << n << ",ans = " << Krus() << endl;
    }
    return 0;
}
```
--------

在这个暴力代码中,我尝试跑了n=2~17的情况,得到的数据如下

> n = 2, ans = 1

> n = 3, ans = 3

> n = 4, ans = 4

> n = 5, ans = 8

> n = 6, ans = 9

> n = 7, ans = 11

> n = 8, ans = 12

> n = 9, ans = 20

> n = 10, ans = 21

> n = 11, ans = 23

> n = 12, ans = 24

> n = 13, ans = 28

> n = 14, ans = 29

> n = 15, ans = 31

> n = 16, ans = 32

> n = 17, ans = 48

对原序列观察似乎看不出什么规律

但是如果对答案序列进行差分,就可以看出一点端倪了

### 原序列

#### 1 3 4 8 9 11 12 20 21 23 24 28 29 31 32 48

### 差分过后序列

#### 1 2 1 4 1 2 1 8 1 2 1 4 1 2 1 16

我这样划分一样就很明显了

#### 1 2 / 1 4 / 1 2 1 8 / 1 2 1 4 1 2 1 16

### 对于前 2^1 = 2 个数,最后一个数是 2^1 

### 对于前 2^2 = 4 个数,最后一个数是 2^2,而且4前面那个1可以看作把前2^1个数去除最后一个数复制过来的

### 对于前 2^3 = 8 个数,最后一个数是 2^3,而且8前面的{1,2,1}可以看作把前2^2个数去除最后一个数复制过来的

### 以此类推......
-----------
## 所以我们不妨设dp[i] 为前 2^i 个数的和

### 那么前几项可以打表:

$$dp[0] = 1$$
$$dp[1] = 3$$
$$dp[2] = 8$$

### 然后根据刚才找到的规律,得到dp递推式子

$$dp[i] = dp[i-1] + dp[i-1] - 2^{i-1} + 2^i;$$

### 然后对输入的n进行二进制分解就行了
------------
## AC代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxbit = 40;
typedef long long ll;
ll dp[maxbit];
ll n;
int main(){
    cin >> n;
    n--;
    dp[0] = 1;
    dp[1] = 3;
    dp[2] = 8;
    for(int i=3;i<maxbit;i++){
        dp[i] = dp[i-1] + (dp[i-1] - (1ll << (i-1))) + (1ll << i);
    }
    ll ans = 0;
    for(int i=0;i<maxbit;i++)
        if(n & (1ll << i))
            ans += dp[i];
    cout << ans;
    return 0;
}
```

---

## 作者：zhaotiensn (赞：2)

我的解法和楼上的大佬是一样的，虽然我觉得这个结论是比较显然的，不过还是~~口胡~~证明一下比较好

因为所有节点之间的边等于节点编号的异或，所以权为$2^k$次的边连接的两个数二进制上只有第$k-1$位不同。

我们然后想普通的最小生成树题是怎么做的。

最小生成树算法比较常用的有$prim$和$kruskal$。

其中$kruskal$是将所有边中最小的一条一条加入。

我们先来考虑加入权为$2^k$的边:

对于每一个$x$，一定都可以分解成$a_0*2^0+a_1*2^1+…+a_k*2^k+…+a_n*2^n$。

对于它的权为$2^k$的边连接的一定是$a_0*2^0+a_1*2^1+…+(a_k\quad xor\quad1)*2^k+…+a_n*2^n$。

因为权值小于$2^k$的边都已近加入过了，所以$a_k*2^k+…+a_n*2^n$与$a_0*2^0+a_1*2^1+…+a_k*2^k+…+a_n*2^n$一定是有边连接的。

所以这条边是可以被$a_k*2^k+…+a_n*2^n$与$(a_k\quad xor\quad 1)*2^k+…+a_n*2^n$所代替的。

所以每$2^{k+1}$个点需要加入一条$2^k$的边。

然后我们再来考虑权值不是$2^k$的边：

假设一条边权值为$x$，我们可以把它表示成$b_0*2^0+b_1*2^1+…+b_k*2^k+…+b_n*2^n$。

它连接的是$a_0*2^0+a_1*2^1+…+a_n*2^n$和$(a_0\quad xor\quad b_0)*2^0+(a_1\quad xor\quad b_1)*2^1+…+(a_n\quad xor \quad b_n)*2^n$

设$k$最大的不为0的$a_i$为$a_k$，那么所有小于$2^k$的边都被加入过了。然后理由同上，这条边一定是没有用的。

然后我们只要将所有$2^k$的边加起来就好了。

代码：
```
#include <iostream>
#include <cstdio>

#define ll long long

using namespace std;

ll n,ans;

int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    ll now=1;
    while(n!=1){
        ans+=(n/2)*now;
        n=n/2+n%2;
        now*=2;
    }
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：cirnovsky (赞：1)

##  题意简述

翻译挺简洁的.

## 题解

先从递推的层面考虑.

我们定义 $F(n)$ 表示结点数为 $n$ 的答案，也就是最小生成树的边权和.

首先边界条件为 $F(0)=0,F(1)=1$.

然后我们考虑如何从 $F(n-1)$ 推到 $F(n)$.

每当我们新加入一个结点 $n-1$（题目结点编号从 0 开始），它的点权为其本身，也就是 $n-1$，那么此时我们就要从之前的 $n-1$ 个结点中选出一个点与 $n-1$ 相连构成当前的最小生成树.

因为边 $(u,v)$ 的边权 $w(u,v)=u\ \mathrm{xor}\ v$ 且图为完全图，所以我们每加入一个新结点 $n-1$ 时，所有我们之前的 $0\cdots n-2$ 号结点都可以被选择.

那么问题转化为：对于一个数 $n-1$，我们需要选出一个整数 $x\in[0,n-1)$ 使得 $(n-1)\ \mathrm{xor}\ x$ 最小.

考虑异或运算的定义：每一位相同为零，不同为一.

那么我们选出的 $x$，需要满足二进制意义下每一位和 $n-1$ 尽量相同，并且从右到左（也就是二进位从低到高）的第一个不同的位置尽量低.

那么结论就摆在眼前了，我们选择的这个 $x$ 为 $(n-1)-\mathrm{lowbit}(n-1)$.

为什么？想想 $\mathrm{lowbit(x)}$ 操作的定义：二进制下 $x$ 最低的 1 和后面的 0 组成的二进制数.

这样结论的正确性就显然了.

我们 $F(n)$ 的递推公式为 $F(n)=F(n-1)+(n\ \mathrm{xor}\ (n\ \mathrm{xor}\ \mathrm{lowbit}(n)))$.

那么暴力递推的代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[100005];
signed main()
{
    long long n;
    scanf("%lld",&n);
    f[0]=0;
    f[1]=1;
    for(long long i=2;i<n;++i)   f[i]=f[i-1]+(i^(i^(i&-i)));
    printf("%lld\n",f[n-1]);
    return 0;
}
```

仔细观察一下递推式，$n\ \mathrm{xor}\ (n\ \mathrm{xor}\ \mathrm{lowbit}(n))$ 不就是 $\mathrm{lowbit}(n)$ 嘛！

那么为题转化为求 $\mathrm{lowbit}$ 前缀和.

通过打一个 $\mathrm{lowbit}$ 表的方法，我们发现 $\mathrm{lowbit}$ 的值十分有规律，就像这种形式：

$$
\texttt{1 2 1 4 1 2 1 8 1 2 1 4 1 2 1 16 1 2 1 4 1 2 1 8 1 2 1 4 1 2 1 32}\cdots
$$

其实这种规律要证明也很方便，只要根据二进制数末尾的情况即可得知.

虽然这个规律没啥用，但是启发了我们按位统计贡献的方法在 $\Theta(1)$ 空间 $\Theta(\log_{2}n)$ 的时间内计算出了 $\mathrm{lowbit}$ 前缀和.

具体方法请参考代码.

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
signed main()
{
    LL n;
    scanf("%lld",&n);
    LL ans=0,app=1,low=n;
    while(low>1)  ans+=app*(low>>1),low-=(low>>1),app<<=1;
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：eEfiuys (赞：0)

令 $\text{MST}_x$ 表示 $0$ 到 $x-1$ 的最小生成树。

$\text{MST}_x$ 可以看作给 $\text{MST}_{x-1}$ 和 $x-1$ 连一条最短的边。

按位贪心，显然要把高位消掉，因为所有 $<x-1$ 的点都存在，所以 $\text{lowbit}_x$ 以上的位都能消掉，而因为不存在 $\ge x-1$ 的点，所以 $\text{lowbit}_x$ 无法消掉，因此 $\text{MST}_{x-1}$ 转移到 $\text{MST}_{x}$ 的代价为 $\text{lowbit}_x$。

则 $\text{MST}_n = \sum^{n-1}_{i=1} \text{lowbit}_i$。

考虑每一位作为 $\text{lowbit}$ 的贡献，蒟蒻不会推式子，所以数位 dp。

$dp_{i,lim}$ 表示第 $i$ 位作为 $\text{lowbit}$ 时的贡献，$tp_{i,lim}$ 表示从最高位到第 $i$ 位填完之后数的个数，状态中的 $lim$ 就是是否达到上限。

转移见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int inf=0x3f3f3f3f3f3f3f3f;
const int mod=998244353;
const int N=5;
int n;
int dp[45][2],tp[45][2];
void solve(){
	cin>>n,n--;
	tp[41][1]=1;
	for(int i=40;~i;i--)
		for(int lim=0;lim<=1;lim++){
			if(!tp[i+1][lim])continue;
			for(int p=0;p<=(lim?((n>>i)&1):1);p++){
				int _lim=(lim&&(p==((n>>i)&1)));
				tp[i][_lim]+=tp[i+1][lim];
				if(p)dp[i][_lim]+=(1ll<<i)*tp[i+1][lim];
			}
		}
	// for(int i=40;~i;i--)
	// 	for(int lim=0;lim<=1;lim++)
	// 		if(tp[i][lim])cout<<i<<' '<<lim<<' '<<tp[i][lim]<<' '<<dp[i][lim]<<endl;
	int ans=0;
	for(int i=40;~i;i--)
		for(int lim=0;lim<=1;lim++)
			ans+=dp[i][lim];
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	// freopen("data.in","r",stdin);
	// freopen("data.out","w",stdout);
	int aqx=1;
	while(aqx--)solve();
	return 0;
}
```



---

## 作者：ncwzdlsd (赞：0)

题意很简单，对于一个图，边 $(i,j)$ 的边权为 $i\oplus j$，求该图的最小生成树。

考虑最小边权如何求。思考一下异或的定义，因为相同为 $0$，不同为 $1$，于是乎我们让低位尽量相同，且第一个不同的位置尽量低，再想想 $\text{lowbit}$ 运算的定义，显然，对于从 $x$ 出发的所有点，它的最小边权为 $\text{lowbit}(x)$，且这条边的构造是 $(x,x-\text{lowbit}(x))$。

于是乎我们就可以得到最终统计答案的式子：$\sum\limits_{i=1}^{n-1}\text{lowbit}(i)$，但是显然遇到 $10^{12}$ 这样级别的数据时间复杂度会炸掉，于是乎我们考虑如何优化这个时间复杂度为 $O(n)$ 的求解过程。对于 $\text{lowbit}$ 运算的结果显然是 $2$ 的整数次幂，于是乎我们考虑利用这一点按位考虑，枚举小于等于 $n$ 的所有 $2$ 的整数次幂即可。统计答案的式子为：

$$
\sum\limits_{i=1}^{n-1}\lceil \dfrac{n-i}{2\cdot i}\rceil\times i
$$

，其中 $i$ 为不断循环得到的 $2$ 的次幂。

时间复杂度为 $O(\log n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
	int n;cin>>n;n-=1;
	int ans=0;
	for(int i=1;i<=n;i<<=1) ans+=((n-i)/(i*2)+1)*i;
	cout<<ans;
	return 0;
} 
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1900}$
---
### 解题思路：

设 $f_i$ 表示有 $0$ 到 $i-1$ 共 $i$ 个点时的最小的代价。

从简单的问题入手，考虑 $n=2^i$ 的情况。在这种情况下，假设已知 $2^{i-1}$ 的情况的结果为 $ans$，那么 $2^i$ 的结果一定是 $2\times ans+2^{i-1}$。

这是因为链接 $2^{i-1}$ 到 $2^{i}-1$ 这一段的最小代价和链接 $0$ 到 $2^{i-1}-1$ 的代相等，证明直接分离出二进制下的最高位，而 $2^{i-1}$ 到 $2^{i}-1$ 这一段的最高位全都抵消了。然后链接两段的最小代价是 $2^{i-1}$，这也是很显然的。

而如果想要考虑在两段内链接多个点，可以通过简单的交换得出最高位（按照当前存在的最高位，其余补零）不等的两段内有且仅有一条边。

----
然后拓展到更一般的形式，设 $i$ 的最高位为 $k$，那么将 $i$ 分成 $2^k$ 和 $i-2^k$ 递归处理就行了。证明方式和上面类似，就不再赘述了。

形式化地讲：$f_{i}=f_{u}+f_{i-u}+u$ 其中 $u=2^k$ 并满足 $u<i$ 且 $2u>=i$。


---
### 代码：
```
#include<cstdio>
#include<map>
using namespace std;
#define int long long
int n;
map <int,int> f;
int calc(int x){
	int now=1;
	while(2*now<x){
		now*=2;
	}
	return now;
}
int dfs(int n){
	if(f[n])return f[n];
	if(n==1)return 0;
	int u=calc(n);
	return f[n]=u+dfs(n-u)+dfs(u);
}
signed main(){
	scanf("%lld",&n);
	dfs(n);
	printf("%lld",f[n]);
	return 0;
}
```


---

## 作者：白鲟 (赞：0)

## 题目描述
对于完全图的每条边 $(i,j)$，其边权为 $i \oplus j$，求最小生成树。

## 题目分析
考虑 Kruskal 算法的过程为每次选择两端点未连通的边权最小边。将边的贡献下放给端点，转化为希望每个点的贡献为与它连接的最小边。根据边权式子，与 $x$ 相连的最小边为 $\operatorname{lowbit}(x)$，于是可能的最优解为 $\sum_{i=1}^{n-1}\operatorname{lowbit}(i)$。

是否能够取到呢？答案是肯定的。只需要使每条边 $(x,x-\operatorname{lowbit}(x))$ 被选择即可。

于是问题转化为求 $\sum_{i=1}^{n-1}\operatorname{lowbit}(i)$。考虑 $2^k$ 的贡献次数为 $\left\lfloor\dfrac{n-1}{2^k}\right\rfloor-\left\lfloor\dfrac{n-1}{2^{k+1}}\right\rfloor$，$\operatorname{O}(\log n)$ 计算每个 $2^k$ 贡献即可。

## 代码
```cpp
#include<cstdio>
using namespace std;
const int maxlog=50;
long long x,ans;
int main()
{
	scanf("%lld",&x);
	--x;
	for(int i=0;i<maxlog;++i)
		ans+=((x>>i)-(x>>(i+1)))*(1ll<<i);
	printf("%lld",ans); 
	return 0;
}
```

---

## 作者：VenusM1nT (赞：0)

使用 Kruskal 暴力打表，作差发现为
```
1 2 1 4 1 2 1 8 1 2 1 4 1 2 1 16 ...
```
观察到第 $i$ 项 $a_i$ 的值为
$$\max_{2^x|\ i}\{x\}$$
后面就不知道怎么做了。  
不过观察原始数据可以简单地找出递推式。
```
1 2 3 4 5 6  7  8  9  10 11 12 13 14 15 16 17 18 19 20
1 3 4 8 9 11 12 20 21 23 24 28 29 31 32 48 49 51 52 56 ...
```
分奇偶观察，发现有如下式子
$$a_{i\times 2}=a_i\times 2+i$$
$$a_{i\times 2+1}=a_i\times 2+i+1$$
随便递归一下就出来了。
```cpp
#include<bits/stdc++.h>
#define reg register
#define inl inline
#define int long long
using namespace std;
int n;
map <int,int> m;
int Solve(reg int x)
{
	if(x==1) return 1;
	if(x==2) return 3;
	if(m[x]) return m[x];
	reg int res=(!(x&1)?(2*Solve(x>>1)+(x>>1)):(2*Solve(x>>1)+(x>>1)+1));
	return m[x]=res;
}
signed main()
{
	scanf("%lld",&n);
	n--;
	printf("%lld\n",Solve(n));
	return 0;
}
```

---

## 作者：pomelo_nene (赞：0)

定义 $\operatorname{lowbit}(x)$ 为 $x$ 的二进制表达式中最低位的 $1$ 所对应的值，$f(x)$ 表示 $n=x$ 时的答案。

设 $T(n)$ 为有 $n$ 个点 $0 \sim n-1$，如题目所言构建一个完全图，所构成的 $\operatorname{MST}$。

结论：当 $n \geq 2$ 时，$T(n)$ 由 $T(n-1)$ 加上一条边 $n \to n - \operatorname{lowbit}(n)$ 构成。即答案 $f(n)= \sum_{i=1}^{n-1} \operatorname{lowbit}(i)$。

感性理解，我们对于任意一棵 $n-1$ 个点的生成树，加入一个点之后，我们需要在前 $n-1$ 个点中选一个点连向新加入的点。在保证 $T(n-1)$ 最优的情况下，保证新加入的边最优，一定使 $T(n)$ 更优。考虑什么是新加入的边。我们发现 $n-1$ 大于所有之前的点，所以不会存在一个连向的边 $x$，使得 $x \geq n-1$，因而我们能够满足的最小的权值就只有 $\operatorname{lowbit}(n-1)$。

考虑这个 $f(n)$ 怎么算。若一个数 $x$ 的 $\operatorname{lowbit}(x)=2^k$，那么这个 $2^k|x$，算的就是 $n-1$ 里面有多少个数能够整除 $2^k$，这个是很简单的，同时我们还要减去 $\operatorname{lowbit}(x)=2^{k-1,k-2,\cdots 1}$ 的答案。这个可以直接用递归实现，应该很好处理。

```cpp
#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
LL lowbitSum(LL x)
{
	if(x==0)	return 0;
	return ((x+1)>>1)+(lowbitSum(x>>1)<<1);
}
int main(){
	LL x;
	scanf("%lld",&x);
	--x;
	printf("%lld",lowbitSum(x));
	return 0;
}
```

---

## 作者：大菜鸡fks (赞：0)

我们分块地考虑问题。

分[0..1] [0..10] [0..100] 等（二进制下）。

可以发现[10..11][100..111] 之间连边的方案数与最高位无关。（最后只要把100000与0连保证方案性就可以进行方案的叠加了）
设f[i]为[0..1000000(i个0)]的连边方案数

f[i]=sum[i-1]+(1<<i);

sum[i]为f[i]的前缀和。 这个转移方程可以感性的理解为

由[0..111111]的方案数转移到[0..1000000]的方案数。只是多了一个0-1000000的边而已。

为什么这样是最优的。。。感性的理解（我不会证）

```cpp
#include<cstdio>
using namespace std;
typedef long long ll;
ll n,p[70],ans,sum[70];
int main(){
	scanf("%I64d",&n);
	p[0]=1; sum[0]=1;
	for (int i=1;i<=60;i++) {
		p[i]=sum[i-1];
		p[i]+=1ll<<i;
		sum[i]=sum[i-1]+p[i];
	}
	n--;
	for (int i=0;i<=60;i++){
		if (n&(1ll<<i)){
			ans+=p[i];
		}
	}
	printf("%I64d\n",ans);
	return 0;
} 
```



---

## 作者：OIer_ACMer (赞：0)

这道题十分的~~水~~有意义。


------------
本来，我是不小心发现了这道水题，不想做。但是，看到了蓝色的标识，我又觉得这是个上分的好机会，于是就~~水~~过了这道题，并~~水~~写了这篇题解。


------------
## 大致思路1：
这道题主要考察**按位异或**的知识，只要知道异或的性质，那么就很简单了。我们知道：如果**两个操作数的数值差距较小**，那么它们的**二进制表示中可能有很多相同的比特位**，导致**异或结果较小**。我们先定义一个数组 $ans$ 记录最小生成树的异或结果，然后我们可以枚举一下：我们尽量让点权相差较小的连边，所以 $0$ 和 $1$，$0$ 和 $2$（注意：除了差要小，**还要考虑到进位发生的大规模变换**，所以主要看的是二进制位的差距，例如 $4$ 的二进制是 $0010$，$6$ 的二进制是 $0110$，两者可以连边，但凡是出现例如 $7$ 的情况，二进制为 $0111$，则差距太大，有两位不同，没有前面的差距小，就不能连边），同理，$4$ 连 $5$，$4$ 连 $6$，$6$ 连 $7$ 等（剩下的请读者自行枚举）。


------------
## 代码1：

```c++

#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, ans;
signed main()
{
    n = read();
    n--;//由于是生成树，所以边数要是n - 1
    while (n)
    {
        long long sum = 1, num = 1, a = 1, b = 1; 
        while (num <= n)
        {
            b = a;
            a = sum + num * 2;
            sum = a + sum;
            num <<= 1;
        }
        num >>= 1;
        // cout << "num=" << num << endl;
        ans += b;
        n -= num;
    }
    cout << ans;
    return 0;
}

```
[AC记录](https://www.luogu.com.cn/record/120750317)


------------
## 大致思路2：
还有一种方法，记得我们之前学过**树状数组**吧，我们通过寻找**最后一个** $1$ 来确定数字或数组在树上的**哪个地方或范围**，所以，在这道题中，答案是 $\sum\limits _ {i = 1} ^ n \operatorname{lowbit}(i)$，因为在做异或运算时主要考虑的是最后一位，所以我们可以通过与最后一位异或来获得答案。

具体证明如下：

由于 $n$ 的大小会很大，所以我们要**按位推**，并计算贡献。

令 $\operatorname{lowbit}(i) = x$ 的个数为 $f(x)$。

则 $ans = \sum\limits _ {i = 1} ^ {2 ^ i \le n} f(2 ^ i) \times 2 ^ i$。

所以每组的给答案的贡献是 $\frac{n - 2 ^ i}{2 ^ {n + 1}} + 1$。

最终，通项公式就是 $\sum \limits _ {i = 1} ^ n \operatorname{lowbit}(i)$（手推一下就可以了）。


------------
## 代码2：

```c++

#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, ans;
signed main()
{
    n = read();
    n--; //由于是生成树，所以边数要是n - 1
    // while (n)
    // {
    //     long long sum = 1, num = 1, a = 1, b = 1;
    //     while (num <= n)
    //     {
    //         b = a;
    //         a = sum + num * 2;
    //         sum = a + sum;
    //         num <<= 1;
    //     }
    //     num >>= 1;
    //     // cout << "num=" << num << endl;
    //     ans += b;
    //     n -= num;
    // }
    for (int i = 1; i <= n; i <<= 1)
    {
        ans += ((n - i) / (i << 1) + 1) * i;
    }
    cout << ans;
    return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/120753913)

---

