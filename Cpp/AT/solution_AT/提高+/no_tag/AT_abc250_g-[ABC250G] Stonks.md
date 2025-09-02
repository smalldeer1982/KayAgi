# [ABC250G] Stonks

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc250/tasks/abc250_g

あなたは $ N $ 日にわたって、 X 社の株の取引を行います。

未来予知の能力者であるあなたは、取引のうち $ i $ 日目の X 社の株価が $ 1 $ 株あたり $ P_i $ 円であることを知っています。

あなたは、毎日以下の行動をどれか $ 1 $ つだけ行うことが出来ます。

- X 社の株を $ 1 $ 株、 $ P_i $ 円で買う。
  - このとき、持ち株が $ 1 $ 株増え、所持金が $ P_i $ 円減少する。
- X 社の株を $ 1 $ 株、 $ P_i $ 円で売る。この行動は株を $ 1 $ 株以上保有している時行える。
  - このとき、持ち株が $ 1 $ 株減り、所持金が $ P_i $ 円増加する。
- 何もしない。

あなたの取引開始時の所持金は $ 10^{100} $ 円なので、現金に困ることはありません。

$ N $ 日目の行動を終えた時点で、所持金の増加額としてありうる最大値を求めてください。  
 なお、 $ N $ 日目の行動を終えた時点でまだ X 社の株をいくつか保有していても、それは所持金の計算上 $ 0 $ 円であるものとします。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ P_i\ \le\ 10^9 $

### Sample Explanation 1

以下のように行動することで所持金を $ 16 $ 円増加させることができ、これが最大です。 - $ 1 $ 日目、株を $ 1 $ 株買う。 持ち株は $ 1 $ 株、所持金の増加額は $ -2 $ 円になる。 - $ 2 $ 日目、株を $ 1 $ 株売る。 持ち株は $ 0 $ 株、所持金の増加額は $ 3 $ 円になる。 - $ 3 $ 日目、株を $ 1 $ 株買う。 持ち株は $ 1 $ 株、所持金の増加額は $ -1 $ 円になる。 - $ 4 $ 日目、株を $ 1 $ 株買う。 持ち株は $ 2 $ 株、所持金の増加額は $ -4 $ 円になる。 - $ 5 $ 日目、株を $ 1 $ 株売る。 持ち株は $ 1 $ 株、所持金の増加額は $ 3 $ 円になる。 - $ 6 $ 日目、株を $ 1 $ 株買う。 持ち株は $ 2 $ 株、所持金の増加額は $ 2 $ 円になる。 - $ 7 $ 日目、株を $ 1 $ 株売る。 持ち株は $ 1 $ 株、所持金の増加額は $ 10 $ 円になる。 - $ 8 $ 日目、株を $ 1 $ 株売る。 持ち株は $ 0 $ 株、所持金の増加額は $ 16 $ 円になる。

## 样例 #1

### 输入

```
8
2 5 4 3 7 1 8 6```

### 输出

```
16```

## 样例 #2

### 输入

```
5
10000 1000 100 10 1```

### 输出

```
0```

## 样例 #3

### 输入

```
15
300 1 4000 1 50000 900000000 20 600000 50000 300 50000 80000000 900000000 7000000 900000000```

### 输出

```
2787595378```

# 题解

## 作者：OMG_wc (赞：7)

加深一下对反悔贪心的理解：

每天的价格 $x$ 对答案的贡献是三选一的：正贡献 $+x$，零贡献 $+0$，负贡献 $-x$。   

题意就是在保证最终正贡献和负贡献的总次数相等，且到每个时刻正贡献次数 $\le$ 负贡献次数的前提下，总贡献最大。

以下代码即可解决：

```cpp
int main() {
    int n;
    scanf("%d", &n);
    priority_queue<int, vector<int>, greater<int>> q;
    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        ans += x;
        q.push(x), q.push(x);
        ans -= q.top();
        q.pop();
    }
    printf("%lld\n", ans);
    return 0;
}
```


为什么每个数需要 `push` 两次？

因为一开始假设都是正贡献，每从优先队列里 `pop` 一次降低一个级别（正贡献变成零贡献，零贡献变成负贡献）。这里的级别降低就体现出反悔操作。

用优先队列取最小值的目的，也是为了负贡献尽可能少。

代入原题意，就是假设每天刚开始都假设是卖（总能在之前找到一个买点，最坏就是当天买，当天卖，等价于不操作），在将来某时刻第一次 `pop` 出来降低一个级别变成不操作，再 `pop` 一次就变成买。

用一个数据 `1 5 9 7` 体会一下就懂了:

- 第一天，是不买不卖（初始是卖，`pop` 一次变成不操作）

- 第二天，$1$ 被 `pop`，变成了 $5$ 卖，$1$ 买。 

- 第三天，$5$ 被 `pop`，所以变成第二天不操作，$9$ 卖 $1$ 买。

- 第四天，还是 $5$ 被 `pop`，第二天的操作变成了买，那么新增一个交易 $7$ 卖 $5$ 买。

这样总贡献就是 $9-1+7-5=10$。









---

## 作者：Clare613 (赞：4)

## 题外话
不是，这道题可以评蓝？
## 思路
这是一道反悔贪心，我们可以发现，一天有三种状态：
- 买**一张**股票。
- 卖**一张**股票。
- 啥也不干。

于是就分成了三级，层层递进的关系。我们每张股票向队列里放两次。第一次是代表会卖这张股票，后面会再减去一张股票，当然也有可能就是这张彩票。在往后走就是买了这张股票，但因为一天只能卖买**一张**股票，所以只能放两次，最后输出就可以了。
## code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int,vector<int>,greater<int> >q;
signed main(){
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		ans+=x;
		q.push(x);
		q.push(x);
		ans-=q.top();
		q.pop();
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Tsawke (赞：4)

# [[ABC250G] Stonks](https://www.luogu.com.cn/problem/AT_abc250_g) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC250G)

## 题面

给定序列 $ P_n $ 表示 $ n $ 天里的股价，每天可以**买入或卖出一股**，本金无限，求最多能**赚**多少钱。

## Solution

明显反悔贪心。

不失一般性，令 $ a \lt b \lt c $，则若某天存在如下决策，即买 $ a $ 卖 $ b $，那么赚的钱为 $ b - a $，而显然对于 $ a $ 来说，若买 $ a $ 卖 $ c $，那么贡献为 $ c - a \gt b - a $，差为 $ c - b $，则不难想到当买 $ a $ 卖 $ b $ 的时候再将 $ b $ 插入，此时如果存在 $ c $ 取了插入的 $ b $，其实际意义即为撤销买 $ a $ 卖 $ b $ 并改为买 $ a $ 卖 $ c $，但此时 $ b $ 天就无操作了，所以我们此时需要再额外插入一个 $ b $，表示后面若需要可以执行一次买 $ b $ 卖 $ d $ 的操作。不难想到可以用小根堆维护，假设堆顶元素为 $ top $，当前元素为 $ x $，若 $ x - top > 0 $ 那么贡献为 $ x - top $，反之将 $ x $ 压入小根堆即可。

双倍经验 [CF865D Buy Low Sell High](https://www.luogu.com.cn/problem/CF865D)。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N;
int P[210000];
ll ans(0);
priority_queue < pair < int, int >, vector < pair < int, int > >, greater < pair < int, int > > > cur;

int main(){
    N = read();
    for(int i = 1; i <= N; ++i){
        P[i] = read();
        if(!cur.empty() && P[i] > cur.top().first){
            int val, idx; tie(val, idx) = cur.top(); cur.pop();
            ans += P[i] - val, cur.push({P[i], P[i]});
            if(idx)cur.push({idx, 0});
        }else cur.push({P[i], 0});
    }printf("%lld\n", ans);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_12_20 初稿

---

## 作者：max666dong123 (赞：4)

## 题意
你有 $10^{100}$ 元，可以看做无限元。第 $i$ 天可以买入一股价格为 $P_i$ 的股票，也可以以 $P_i$ 的价格卖出一股。当然也可以什么都不做。求出可以赚的**最大值**。

## 思路
用反悔贪心来做，怎么后悔呢？我们可以发现：

令 $Cbuy$ 为全局最优的买入当天价格，$Csell$ 为全局最优卖出当天的价格我们可以发现：
$$Csell-Cbuy=Csell-P_i+P_i-Cbuy \ (i\in z^{+}\text{且}1 \le i \le n)$$ 
所以每次要压入两次 $P_i$。 

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
struct node{
	int v;
	bool operator <(const node &b)const {
		return v>b.v;
	}
};
priority_queue<node>q;//小根堆
signed main(){
	IOS;
	int n;
	cin>>n;
	node x;
	int ans=0;
	for(int i=1;i<=n;i++){
		cin>>x.v;
		if(q.size()&&q.top().v<x.v){
			ans=ans+x.v-q.top().v;//计算赚了多少钱
			q.pop();
			q.push(x);
		}
		q.push(x);//压两次
	} 
	cout<<ans<<endl;
	return 0;
}


```

---

## 作者：Richard_Whr (赞：4)

看大家都是反悔贪心，感觉这东西非常玄乎，来一发 $\texttt{slope trick}$ 题解。

###  前言：

本题堪称 $\texttt{slope trick}$ 的一种特殊建模模板，非常适合入手 $\texttt{slope trick}$。

### 正文：

首先对于最优化问题，想到 dp，

设 $f_{i,j}$ 表示 $i$ 天后，手里有 $j$ 个股票，可以赚得得最大利润。

转移有三种：买，卖，啥也不干。

形式化的有 

$$f_{i,j}=max\{f_{i-1,j-1}-w_i,f_{i-1,j+1}+w_i,f_{i-1,j}\}$$

发现这个 $i$ 只是一个天数维，我们将 dp 数组看成 关于 $j$ 的函数，即 $f_i(x)$

$\texttt{slope trick}$ 对函数有凸性要求，因为这样才能通过维护有序斜率而降低复杂度。

对于本题凸性的解释，我从理性上不会证明。但感性的分析就是，手里拿的股票一定是选最便宜天的股票买，手里有的越多，拿的较不便宜的股票就越多，因此斜率掉得越快。

大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/g8s5vlsx.png)

这个转移很有特点，$f_i(x)$ 为我们想要的，他从 $f_{i-1}(x)$ 转移而来。

具体这个操作几何意义为：平移向量 $(-1,w_i)$， $(1,-w_i)$ 后，分别与 $f_{i-1}(x)$ 对应取 $max$。

平移的最大特点就是斜率几乎没有变化。

考虑通过维护斜率快速实现这个转移。


#### 建模 & 维护：

由于斜率有序（全部取为正数后单调上升），因此我们设我们数据结构中第 $i$ 小的值 $k_i$ 表示在 $i-1$ 到 $i$ 这一段单位长度内，斜率为 $k_i$。

假设我们已经可以维护我们的斜率，我们看看这个平移操作应该如何通过斜率变化维护。

- #### 1. 左上平移并和原来取 Max ：

对于左上平移，我们发现凡是函数斜率 $<$ 移动斜率 $w_i$ 的部分，都会被新来的覆盖，而大于的部分不会改变，

也就是说，斜率 $< w_i$ 的部分排名集体左移，而 $\ge$ 的部分排名不变。

中间的一个是两段边界之间，由于左边平移产生的新斜率 $w_i$。

注意到如果最小的斜率都 $\ge w_i$ 也就是平移斜率的时候，是不会进行左上平移操作的。

反之最小的斜率将被踢出当前斜率集合。

- #### 2. 右下平移并和原函数取 Min：

和左上差不多，凡是函数斜率 $>$ 移动斜率 $w_i$ 的部分，都会被右下平移覆盖。小于的部分不会改变。

这样一来中间的分界点处同样会因为平移产生一个 $w_i$ 的斜率。

注意到如果最大的斜率都 $<w_i$ 的话也要进行右下平移，因为他会使得函数的定义域扩展，也就是增加了一个右下角的函数值，而这一段的斜率为 $w_i$。

大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/qxgs35by.png)

注意他还是凸的，因为我们只取整点。



------------


**总结一下所需操作：**

我们需要找到最小斜率，动态插入斜率。

发现这个东西一个**优先队列**就可以搞定了。

**但是如何计算答案呢？**

一般这种情况下我们都是找到函数特殊点的值，然后通过我们维护的函数斜率集合倒推回去。

我们想求左下角的值，但发现右下角的函数值很好求，他是每次右下平移产生的新节点，函数值即为 $f_n(n)=-\sum w_i$

此时我们已经维护好了 $f_n(x)$ 的每个单位斜率变化情况，我们依次加上斜率，就可以获得左上角的值。

为什么直接加斜率就行呢，因为他是单位长度内纵坐标的变化量。

上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
int w[N];
int n;
priority_queue<int,vector<int>,greater<int>> heap;

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	 
	cin>>n;
	int res=0;
	for(int i=1;i<=n;i++)
	{
		cin>>w[i];
		res-=w[i];
		if(heap.size()&&heap.top()<w[i])
		{
			heap.pop();
			heap.push(w[i]);
		} 
		heap.push(w[i]);
	}
	
	while(heap.size()) res+=heap.top(),heap.pop();
	
	cout<<res<<"\n";
	
	return 0;
}
```

---

## 作者：shinkuu (赞：3)

本题的第二篇题解做法比较巧妙，但是讲的不够清楚。在此做一些补充说明。

设原本买 $a$ 元卖 $b$ 元，现在变成卖 $c$ 元。对答案的贡献就是 $c-a$。但同时，它又可以表示成 $(c-b)+(b-a)$，也就是买 $a$ 卖 $b$，再买 $b$ 卖 $c$。所以每一次找到最小的 $a$，计算贡献后，再将 $b$ 压进堆里算。

但是那篇题解讲的不足的地方是，这并不是要进堆两次的原因。真正的原因是，当这个 $b$ 被换成 $c$ 之后，$b$ 也可以变成买的，和另一个卖的 $d$ 匹配。正如第一篇题解说的那样。

这个时候可能会有一个疑问：多进一个不会算多/重吗？事实上，它对答案的贡献不取决于选哪一个，只取决于选几个。而如果选了 $2$ 个，其中就必定有一个是由卖变买的了。

代码看楼上大佬的，就不放了。~~毕竟和贺的没什么区别。~~

---

## 作者：Symbolize (赞：3)

# $\tt{Solution}$
考虑反悔贪心，首先对于一天的价格有三种不同的情况，买入，卖出与不管，也就是说每天对于一个价格，要么为正的贡献，要么为负的贡献，要么无贡献，那我么就可以思考一个问题，设最优的买入当天的价格为 $a$，最优的，卖出当天的价格为 $b$，因为 $b-a=b-p_i+p_i-a$，所以我们可以使用小根堆，每次放入一个 $p_i$，如果说目前的堆顶比当前值小，则在答案累加后将堆顶弹出，并再次加入一个 $p_i$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
#define debug() puts("----------")
const int N=1e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
const double pi=acos(-1);
using namespace std;
typedef complex<int> ci;
typedef complex<double> cd;
int n,ans;
priority_queue<int,vector<int>,greater<int> > q;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
signed main()
{
//	#ifndef ONLINE_JUDGE
//		freopen(".in","r",stdin);
//		freopen(".out","w",stdout);
//	#endif
	n=read();
	rep1(i,1,n)
	{
		int x=read();
		if(!q.empty()&&q.top()<x) 
		{
			ans+=x-q.top();
			q.pop();
			q.push(x);
		}
		q.push(x);
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：Hilaria (赞：2)

### 题意

你现在要炒股，然后你的初始资金有很多（不用担心没钱）。

现在你知道每天这个股票的价值 $p_i$，每天你要么买进一股，要么卖出一股，或者不操作，**不能进行多个操作**。

如果第 $n$ 天结束后你还有剩余的股票，则这些股票全部没用了。

问你最多能获利多少钱？

### 思路

这个题说让我们求最大获利，那这种题一般是 dp 或者贪心。

但是这个题 dp 好像不太行（反正我没想出来），那么我们就考虑贪心。

然后因为你一个 $p_i$ 对于后面的 $p_{i+1}$ 到 $p_n$ 来说是没有影响的，所以我们可以考虑按天来贪心。

假设我们现在算到了第 $i$ 天，那前面的 $1$ 到 $i-1$ 天的状态只有三种，要么买了一股，要么卖了一股，要么是可选的（就是没有操作）。

那你现在第 $i$ 天时，最优的的操作就是从前面买下的股里面找一个最小的（假设为 $p_{\min}$），然后把以今天的价格卖出去，那么贡献就是 $p_i-p_{\min}$（当然如果 $p_{\min}>p_i$ 就不这么做）。

但是怎么做是错误的。

我们随便搞个例子就能卡掉这个思路。

```
3
2 4 100
```

我们会发现，如果我按上面辣个思路做，那在第 2 天时就会把价值 1 的股卖了，贡献为 2，但是其实如果在第 3 天卖贡献会更大。

所以我们要学会反悔！

因为在第 $a$ 天买下一股，第 $c$ 天卖出一股。

其实就相当于在第 $a$ 天买下一股，第 $b$ 天卖出一股，再在第 $b$ 天买下一股，最后在第 $c$ 天卖出这只股。

所以我们可以优化一下上面的思路，我们不仅要从前面买下的股里找，我们还要从「前面状态为卖出」的里面找一个最小值（最小值可以用个优先队列维护一下）。

就是说，假设我们现在在第 $i$ 天，我们从前面「状态为买下」的股和前面「状态为卖出」的里面找出一个最小值为 $p_{\min}$。

现在就有两种情况：

1.$p_i\leq p_{\min}$，那么我们就直接把 $p_i$ **看作**买下的，放入优先队列中（如何最后还有剩余，就当作没有买过，因为我们只计算贡献，所以不会出错）。

2.$p_i>p_{\min}$，那么我们把 $p_i-p_{\min}$ 的贡献加进答案，然后放两个 $p_i$ 进优先队列。因为如果下次在 $p_j$ 找到最小值为 $p_i$ 时，就是贡献加了 $p_j-p_i$，相当于贡献加了 $p_j-p_{\min}$，那么其实在这种情况下，$p_i$ 其实是没有被操作的，所以优先队列中会还有一个 $p_i$。所以才要在一开始加入两个 $p_i$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll ans;
priority_queue<int,vector<int>,greater<int> > q;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int a;
		cin>>a;
		if(q.size()&&q.top()<a)
		{
			ans+=a-q.top();
			q.pop();
			q.push(a);
		}
		q.push(a);
	}
	cout<<ans;

	return 0;
}
```


---

## 作者：Ups_and_downs (赞：2)


# [ABC250G] Stonks

~~**弱弱py党第一次写题解**~~

已经知道了一只股票从第 1天到第 $n$ 天的价格，每天只能从买，卖，不交易这三种操作中选一种，问到最后一天的最大收益。

方法：
	可以利用最小堆来解决问题：每天都在堆中插入两次这一天的股票价格 $P_i$，分别代表在这一天买入或者卖出股票。然后取出堆中的最小值 $P_m$，表示在 $P_m$ 这一天买入了股票，又以 $P_i$ 的价格卖出。这样贪心是正确的，因为如果发现我们既需要在这一天买入股票，有需要在这一天卖出股票，两个操作就互相抵销了，相当于在这一天选择不交易。

**我们知道 python 有个~~好~~东西叫 heapq**

AC代码附上

**------------------------------------------------**
```python
import heapq
def solve():
    n = int(input())
    nums = list(map(int, input().split()))
    res = 0
    pq = []
    for i in range(n):
        heapq.heappush(pq, nums[i])
        heapq.heappush(pq, nums[i])
        res += nums[i] - heapq.heappop(pq)
    print(res)
solve()
```


---

## 作者：_shine_ (赞：1)

### 1.题目大意
现在你有 $10^{100}$ 元（约等于无限），每天你可以进行三种操作中的一种：

1. 买进一股
1. 卖出一股
1. 不进行任何一种操作

如若在第 $n$ 天还有剩余的股票即视为作废。现在问你最多能赚多少钱。
### 2.思路
考虑使用反悔贪心的思想，假设买了 $a$，则在 $b$ 和 $c$ 之间显然选择大的那个，即为 $max_{b,c}-a$，但是这个式子其实也可以表示为 $\left(b-a\right)+\left(c-b\right)$，显然使用小根堆来存储即可，但是，需要注意的是，这个其实是不完善的，可以发现，在第一个式子中，其实可以直接变成 $c-a$，所以在压入堆中时，每天的价值 $a_i$ 其实都应该压入堆中，使得 $a_i$ 能与后面的相匹配。
#### [AC记录](https://atcoder.jp/contests/abc250/submissions/41286220)
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10; 
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
    while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;ch=getchar();
	}
    while(ch>='0'&&ch<='9'){
    	s=s*10+ch-'0';
		ch=getchar();
	}
    return s*w;
}
inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)write(x/10);
    putchar(x % 10 + '0');
}
priority_queue<int,vector<int>,greater<int> >q;
int n,a[maxn],ans;
signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
	}
	q.push(a[1]);
	for(int i=2;i<=n;++i){
		if(q.top()<a[i]){
			int cnt=(a[i]-q.top());
			ans+=cnt;
			q.pop();
			q.push(a[i]);
		}
		q.push(a[i]);
	}
	write(ans);
	return 0;
}
```


---

