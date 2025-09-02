# [USACO12JAN] Mountain Climbing S

## 题目描述

Farmer John has discovered that his cows produce higher quality milk when they are subject to strenuous exercise.  He therefore decides to send his N cows (1 <= N <= 25,000) to climb up and then back down a nearby mountain!

Cow i takes U(i) time to climb up the mountain and then D(i) time to climb down the mountain.  Being domesticated cows, each cow needs the help of a farmer for each leg of the climb, but due to the poor economy, there are only two farmers available, Farmer John and his cousin Farmer Don.  FJ plans to guide cows for the upward climb, and FD will then guide the cows for the downward climb.  Since every cow needs a guide, and there is only one farmer for each part of the voyage, at most one cow may be climbing upward at any point in time (assisted by FJ), and at most one cow may be climbing down at any point in time (assisted by FD).  A group of cows may temporarily accumulate at the top of the mountain if they climb up and then need to wait for FD's assistance before climbing down.  Cows may climb down in a different order than they climbed up.

Please determine the least possible amount of time for all N cows to make the entire journey.


## 样例 #1

### 输入

```
3
6 4
8 1
2 3```

### 输出

```
17```

# 题解

## 作者：Kirin (赞：17)

被叫去给学弟讲这道题，没想到被学弟Hack了。。。Orz

做法和大家一样：

$$ans=\max\left\{\sum_{k=1}^n{up_k}+down_{\min},\sum_{k=1}^n{down_k}+up_{\min}\right\}$$

但是这个做法是不完全正确的，比如以下数据：

```plain
3
6 4
8 3
2 1
```
正确答案应该是$18$而不是$17$，这个可以手动模拟，会发现之前的做法有问题。

我去查了一下[USACO官方题解](http://usaco.org/current/data/sol\_climb.html "传送门")，下面来简单说一下。


- 首先，贪心的想法和之前的做法是相同的，就是让更多的牛早到山顶；

- 我们把牛分成两类：1. up < down    2. up > down，up=down的归为任意一类是不影响的；

- 之后，考虑到up小的先到山顶不会拖慢后面的牛，我们把第一类都排在第二类前面，而且按up升序排；

- 第二类牛我们按down降序排，这个没上面那个显然，但是原因也很简单，下的慢的先下可以拖住后面的牛下山，减少出现山顶的牛已经下完了，下面的牛还没上完这种浪费的情况；

- 之后是计算时间，其实最初那个方法的贪心策略和上面应该是相同的，但是计算出了问题；

- 那组数据之所以被Hack，就是因为最初的方法认为第一个牛上山后，所有上下山是一起进行的，其实有可能出现不重叠的情况，于是少算了；

- 正确的做法是按之前那个策略排序后，O(n)模拟一下。


代码：

```cpp
#include <cstdio>
#include <algorithm>

using std::sort;
using std::max;

const int MAXN=25005;
int n;
int up_tm[MAXN],dwn_tm[MAXN];

struct Cow{
    int up,dwn;
    static bool cmp_tm(const Cow &a,const Cow &b){
        if(a.up<a.dwn){
            if(b.up<b.dwn) return a.up<b.up;
            else return true;
        }
        else{
            if(b.up<b.dwn) return false;
            else return a.dwn>b.dwn;
        }
    }
}cow[MAXN];

inline int greedy(){
    sort(cow+1,cow+n+1,Cow::cmp_tm);
    for(int i=1;i<=n;++i)
        up_tm[i]=up_tm[i-1]+cow[i].up;
    for(int i=1;i<=n;++i)
        dwn_tm[i]=max(dwn_tm[i-1],up_tm[i])+cow[i].dwn;
    return dwn_tm[n];
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d%d",&cow[i].up,&cow[i].dwn);
    printf("%d",greedy());
    return 0;
}
```

---

## 作者：PP__ (赞：12)

贪心。

首先考虑什么样的奶牛得先上坡。很明显，上坡耗时短的奶牛先上坡。为什么？因为如果耗时长的奶牛先上坡的话，那么后面的奶牛就会被全部拖慢，同时下坡的开始时间也被延后。所以这时我们将上坡耗时短的奶牛排在前面。

其次考虑什么样的奶牛得先下坡。很明显，下坡耗时长的奶牛先下坡。为什么？因为如果耗时短的奶牛先下坡的话，那么越到后面，上坡了在山顶上的奶牛就会被全部拖慢，同时下了坡的奶牛也会因等待而浪费时间。所以这时我们将下坡耗时长的奶牛排在前面。

但是我们还要考虑一个问题：如果上坡慢的奶牛下坡很快，我们怎么办？

所以，我们应该将奶牛归为两类。第一类是上坡时间小于下坡时间的，第二类是上坡时间大于等于下坡时间的。

很明显，我们应该将第一类排在第二类前，按上坡时间升序，这个在我们的第一个讨论中很显然。同理，在第二种情况中，我们应该把下坡时间长的排在前面。因为在第二种情况中，上坡时间大于等于下坡时间，那么我们就必须把下坡时间长的排在前面。这样就能尽量避免下坡已经下完了但下一头牛还没上来这样的情况。

所以最后的计算过程就是：
$$
ans = \max(\sum_{j=1}^nup_j,ans)+down_i
$$
读者自证不难。

最后的代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
struct node
{
	int a,b;
}x[100010];
bool cmp(node a,node b)
{
	if(a.a < a.b)
	{
		if(b.a < b.b)return a.a < b.a;
		return 1;
	}
	else 
	{
		if(b.a < b.b)return 0;
		return a.b > b.b;
	} 
}
int main()
{
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> x[i].a >> x[i].b; 
	}
	sort(x + 1,x + n + 1,cmp);
	int ut = 0,dt = 0,ans = 0;
	for (int i = 1;i <= n;i++)
	{
		ut += x[i].a;
		dt = max(ut,dt) + x[i].b;
	}
	cout << dt << endl;
} 
```

---

## 作者：羽儇 (赞：9)

![](https://cdn.luogu.com.cn/upload/image_hosting/6d6vlvq0.png)

[P2123](https://www.luogu.org/problem/P2123)题面的公式正是本题的核心

让窝来解释一下趴QAQ：

```cpp
如图，C[i]表示当到第i个cow回去后，总共花费的最多时间

窝觉得，举栗纸更通俗易懂点：

C1 = a1 + b1（第一头牛上山时间+下山时间）

则C2 = max(C1 , a1 + a2) + b2

即C2 = max(a1+b1 , a1 + a2) + b2//敲黑板！！！

这时就有惹  b1与a2的比较

如果第一个cow下山的时间大于第二个cow在上山的时间，则以第一个cow下山的时间为基准，再+b2（b2,即第二个cow下山的时间）
如果第二个cow在上山的时间大于第一个cow下山的时间，则以第二个cow上山的时间为基准，再+b2
至于相等时，无所谓哪一个惹QAQ

图上的式子是可以化简的，


```

[戳窝](https://www.luogu.org/problemnew/solution/P2123)



里面的第一篇很详尽惹

然后先去做P2123

再回来做本题

上图的式子最终可化简为

```cpp
if(p1.d!=p2.d)return p1.d<p2.d;
	else if(p1.d<=0)return p1.a<p2.a;
	return p1.b>p2.b;
```



AC代码

```cpp
#include <cstdio>
#include <algorithm>
#define maxn 30100
using namespace std;
struct node 
{
	int a, b,d;
}cow[maxn];
int T,n;
long long C[maxn];
bool cmp(node p1,node p2)
{
	if(p1.d!=p2.d)return p1.d<p2.d;
	else if(p1.d<=0)return p1.a<p2.a;
	return p1.b>p2.b;
}
signed main()
{
		long long suma = 0;
		scanf("%d",&n);
		for(int i = 1 ;i <= n ;i++)
		{
			scanf("%d%d",&cow[i].a,&cow[i].b);
			if(cow[i].a<cow[i].b)cow[i].d = -1;
			else if(cow[i].a>cow[i].b)cow[i].d = 1;
			else cow[i].d = 0;
		}
		sort(cow+1,cow+1+n,cmp);
		for(int i = 1;i<=n;i++)
		{
			suma += cow[i].a;
		    C[i] = max(C[i-1],suma) + cow[i].b;
		}
		printf("%lld\n",C[n]);
	return 0;
}
}
三倍经验题

```

喃~


[P2123](https://www.luogu.org/problem/P2123)

[P1248](https://www.luogu.org/problem/P1248)

[P1561](https://www.luogu.org/problem/P1561)

---

## 作者：Unordered_OIer (赞：4)

# P1561 题解
## 题意
$n$ 头牛，上山时间为 $u_i$ ,下山为 $d_i$ 。  
要求每一时刻最多只有一头牛上山，一头牛下山。  
问每头牛都上下山后花费最少时间。

## 解答
这是一道经典的序列约束建模题。序列就是上山和下山，约束就在于**必须先上山才能下山**，我们要使得下山序列尽量短。

很容易能证明**最优的情况上山序列必定是连续的**，但是下山也要尽量保持连续顺序。

于是我们就有了一个目标：让山顶的牛多一些，让下山序列尽量连续。

所以我们要让山上的牛多一点，即让上山快的牛先上来，但是要注意可能下山太快，山上都还没有牛就下山了，会出现等待。

**所以我们可以按照上山时间和下山时间分别考虑**  
（这里记上山时间为 $up$ ，下山时间为 $dn$ ）

1. 当 $up < dn$ ，按 $up$ 升序排序
2. 当 $up ≥ dn$ ，按 $dn$ 降序排序

于是我们记录每头牛的 $upt$ 代表前 $i$ 头牛上山时间和 $dnt$ 前 $i$ 头牛下山时间。

则：
$$dnt_i=max\{dnt_{i-1},upt_i\}+cow_i.dn$$

然后我们就可以快乐的写程序啦~

## 代码军
```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN=25005;
int n;
int up_tm[MAXN],dwn_tm[MAXN];

struct Cow{
    int up,dwn;
    static bool cmp_tm(const Cow &a,const Cow &b){
        if(a.up<a.dwn){
            if(b.up<b.dwn) return a.up<b.up;
            else return true;
        }
        else{
            if(b.up<b.dwn) return false;
            else return a.dwn>b.dwn;
        }
    }
}cow[MAXN];

inline int greedy(){
    sort(cow+1,cow+n+1,Cow::cmp_tm);
    for(int i=1;i<=n;++i)
        up_tm[i]=up_tm[i-1]+cow[i].up;
    for(int i=1;i<=n;++i)
        dwn_tm[i]=max(dwn_tm[i-1],up_tm[i])+cow[i].dwn;
    return dwn_tm[n];
}

int main(){
    freopen("climb.in","r",stdin);
    freopen("climb.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d%d",&cow[i].up,&cow[i].dwn);
    printf("%d",greedy());
    return 0;
}
```
$$\tiny{\color{lightgrey}{官方题解勿喷}}$$
完结撒花~顺便求赞

---

## 作者：JOHNKRAM (赞：4)

算法构造：

1.设置集合F、M、S：先让F中奶牛的爬山，再让M中奶牛的爬山，最后让S中奶牛的爬山。

2.对第i件，若U[i]>D[i]，则归入S；若U[i]=D[i]，则归入M，否则归入F。

3.对F中的元素按U[i]升序排列，S中的按D[i]降序排列。

证明思路：

1.F中的能“拉开”John、Don让同一头奶牛上下山的结束时刻，为后面的奶牛爬山“拉开时间差”，利于节省总时间。S中的刚好相反。因而，F中元素放在最前一定是最优策略之一。

2.F中U[i]小的前置，可以缩短开始时B的空闲时间，但会使F所有奶牛“拉开的时间差”缩短。不过可以证明，后者带来的损失不大于前者获得的优势。对称地，对S也一样。因而步骤3是可行的。

思路很简单，就是实际编写比较麻烦。


---

## 作者：MoonCake2011 (赞：4)

此题是一道贪心的题，用 johnson 不等式会被 hack，所以我用了一个随机算法。

我们充分发扬人类智慧，设计以下随机算法。

我们先用 johnson 不等式以基准排个序，这个应该很接近答案了。

johnson 不等式是用邻项干扰法推一下就推出来了的。

具体可以看我朋友写的 [johnson 不等式详解](https://www.luogu.com.cn/blog/HDZmessi/tan-xin-zhi-johnson-suan-fa-jiang-xie)。

再在时间足够的情况下不断地用 knuth 算法随机打乱序列以来获得更多不同的答案，进行比较。

AC 代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	int a,b;
}a[25010];
void knuth(){//knuth算法 
	for(int i=1;i<=n;i++)
		swap(a[1],a[rand()%n+1]);
}
int count(){
	int sum=0,ans=0;
	for(int i=1;i<=n;i++){
		sum+=a[i].a;
		ans=max(ans,sum)+a[i].b;
	}
	return ans;
}
bool cmp(node x,node y){
	return (min(x.a,y.b)<min(x.b,y.a)) ? 1 : 0;
}
int main() {
	srand(time(0));
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].a>>a[i].b;
	sort(a+1,a+n+1,cmp);
	int cnt=0,ans=2e9;
	while(cnt+2*n<=5e7){//时间足够就继续枚举 
		cnt+=2*n; 
		int p=count();
		ans=min(ans,p);
		knuth();
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：YuYuanPQ (赞：2)

# 洛谷 P1561 题解

## 题目大意

此为简要概括：

奶牛们要上山和下山；

帮助它们上山的有 $1$ 个农夫；

帮助它们下山的有 $1$ 个农夫；

任何时刻只有一头奶牛爬山也只能有一头奶牛下山；

问全部奶牛上山下山最短时间。

## 分析

我们可以把奶牛分成两种：

第一种是：上山快，但下山慢。

第二种是：上山慢，但下山快。

最优做法：

将第一种奶牛放在第二种前面（也就是按照上山的时间，从小到大），这是为了让上山的农夫空闲时间更长（不浪费后面还未上山奶牛时间）。

而第二种奶牛，为了使下山的农夫空闲时间长，应该把下山慢的排前面（不浪费后面已经上到山顶，但是还未下山奶牛的时间）。

以样例为例子：

```
3
6 4
8 1
2 3
```

那么最优顺序是：

第 $2$ 头奶牛先，第 $3$ 头奶牛其次，第 $1$ 头奶牛最后。

细节请看代码。

## 具体做法

见上面的分析。

## 注意事项

### 一

排序时 `cmp` 函数记得打对，不然会挂（按上面的方法排序即可）。

## Code

```cpp
/*
Language : C++
lizhaoyuan_2010
2023.07.21.8:57
*/
#include<bits/stdc++.h>
using namespace std;
int n,a[25010],b[25010],ta[25010],s[25010],my_left,my_right,ans;
struct LZY{
    int minx,wz;//minx--最小 wz--位置
}d[25010];
bool cmp(LZY p,LZY q)
{
    return p.minx<q.minx;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&a[i],&b[i]);
        d[i].wz=i;
        d[i].minx=min(a[i],b[i]);
    }
    sort(d+1,d+1+n,cmp);
    my_right=n+1;
    for(int i=1;i<=n;i++)
    {
        if(a[d[i].wz]==d[i].minx) s[++my_left]=d[i].wz;
        else s[--my_right]=d[i].wz;
    }
    for(int i=1;i<=n;i++)
        ta[i]=ta[i-1]+a[s[i]];
    ans=ans+b[s[1]]+ta[1];
    for(int i=2;i<=n;i++) ans=max(ans,ta[i])+b[s[i]];
    printf("%d\n",ans);
    //for(int i=1;i<=n;i++) printf("%d ",s[i]);
    //printf("\n");
    return 0;
}
```


## 另附

### 一

[题目链接](https://www.luogu.com.cn/problem/P1561)

### 二

如有更好做法，欢迎[私信我](https://www.luogu.com.cn/chat?uid=1029900)。

### 三

[我的提交记录](https://www.luogu.com.cn/record/list?pid=P1561&user=1029900)

### 四

这是我第 $2$ 次写题解，如有错误请各位大佬指出。

---

## 作者：Nuyoah_awa (赞：1)

### 题目大意

有 $n$ 头牛，第 $i$ 头牛上山所用的时间为 $u_i$，下山所用的时间为 $d_i$。

每一时刻最多只有一头牛正在上山，一头牛正在下山。

问最少需要多少时间使得每头牛都过山。

### 题目分析

我们可以将这道题拆成两步想。

1. 还没上山的奶牛需要上山。
2. 已经上山了的奶牛需要下山。

也就是说上山和下山是互不干预的，所以如果山上一直有奶牛等着下山，也就是所下山的奶牛几乎不间断的话，答案肯定是最优的。

于是我们可以想到如下策略：

1. 上山的顺序按照上山时间少的先上。（这样可以使山顶有更多的牛等待或直接下山）
2. 下山顺序按照下山时间长的先下。（这样可以有效地拖慢时间等后面的牛，但是下山的奶牛基本上不会间断所以总的时间是更优的）

但是我们发现这样并不能使下山的奶牛尽可能不间断，如果一头牛的 $u_i > d_i$，就说明上下山的时间会有空当，如果连续多头牛都是这样就有可能间断下山队列。

于是我们可以考虑按照奶牛分类：

1. 第一种奶牛 $u_i \le d_i$，这种奶牛的上山时间小于下山时间，我们按照 $u_i$ 升序排列，既能保证山顶奶牛尽可能多，又不会出现时间空当。
2. 第二种奶牛 $u_i > d_i$，这些奶牛下山时间小于上山时间，我们按照 $d_i$ 降序排列，尽可能拖慢下山速度，为后面奶牛及时到达山顶争取时间。
3. 第一声奶牛排在第二种奶牛前面，因为第一种奶牛能更好的使山顶有更多的奶牛。

按照这样排序后就可以 dp 求解了，我们设 $f_i$ 为第 $i$ 头奶牛过山后的最少时间，转移方程为：

$$f_i = \max(f_{i-1}, \sum_{j=1}^{j\le i} u_i) + d_i$$

对于 $\sum_{j=1}^{j\le i} u_i$，我们可以记一个 $sum$ 然后就可以 $\mathcal O(1)$ 求值了，总时间复杂度是 $\mathcal O(n)$ 的。
### code
```cpp
#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
const int N = 3e4 + 5;
struct node{
	int u, d, opt;
}p[N];
int T, n, f[N], now;
bool cmp(node x, node y)
{
	return (x.opt != y.opt) ? x.opt < y.opt : ((x.opt <= 0) ? x.u < y.u : x.d > y.d);
}
signed main()
{
	scanf("%lld", &n);
	for(int i = 1;i <= n;i++)
	{
		scanf("%lld %lld", &p[i].u, &p[i].d);
		p[i].opt = p[i].u < p[i].d ? -1 : (p[i].u > p[i].d ? 1 : 0);
	}
	sort(p + 1, p + 1 + n, cmp);
	for(int i = 1;i <= n;i++)
	{
		now += p[i].u;
	    f[i] = max(f[i-1], now) + p[i].d;
	}
	printf("%lld", f[n]);
	return 0;
}
```

---

## 作者：qiuqiuqzm (赞：0)

# P1561 题解
**[题目传送门](https://www.luogu.com.cn/problem/P1561)**

## 题目大意
有 $N$ 头奶牛要去爬山，每个奶牛都有上山所需要的时间 $u_i$，和下山所需的时间 $d_i$。每次只能有一只奶牛上山也只能有一只奶牛下山。
要算出所有 $N$ 头牛完成旅程的最短时间。

## 分析
* ~~通过翻看题目标签~~，我们发现这道题是一道贪心题。
* 我们先看上山的情况，每头奶牛上山的顺序肯定要是时间越短的先上才好。因为如果时间长的先上的话，后面就肯定会很慢，到下山的时候，可能会导致要等某一只奶牛上来导致时间过长。
* 而下山的时候，肯定要下山越慢的先下。这同样很好证明。因为如果快的先下的话，可能会导致后面的奶牛还没上来，下去的奶牛已经到底了，就会有空档，时间就肯定不是最优的了。
* 但如果有的奶牛上山快而下山也快，或者上山慢但下山慢呢。我们可以大致将奶牛分成 $2$ 类。一类是上山时间小于下山时间的，还有一种是上山时间大于等于下山时间的。
* 综合上面的情况，我们就可以简单写出代码啦！

## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
	int up,down;
}a[25010]; //记录上山下山时间
long long n,ans=0,sum=0;
bool cmp(node a,node b)
{
	if(a.up<a.down) //上山时间小于下山时间
	{
		if(b.up<b.down) //都是上山时间小于下山时间
			return a.up<b.up; //比较上山时间
		else
			return 1; //否则就先选上山时间小于下山时间的
	}
	else//上山时间大于等于下山时间
	{
		if(b.up>=b.down) //同样的类别
			return a.down>b.down; //先选更长的下山时间
		else
			return 0; //否则先选上山更快的
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].up>>a[i].down;
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		sum+=a[i].up; //上山
		if(ans<sum) //因为要最后一只奶牛爬完后才能结束，那这只奶牛时间肯定是最长的，所以要答案就是时间最长的时候。
			ans=sum; //更久就交换
		ans+=a[i].down;//下山
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：HDZmessi (赞：0)

很有趣的一道贪心和结构体的问题！

如何贪心呢？所谓贪心就是考虑目前最优的规划方法，从而得到最优解。

本蒟蒻最先想到的是 johnson，即排序规律：

$T\min=a _ {1} +b _ {1}+a _ {2}+b _ {2}-\max(\min(a _ {2} , b _ {1}),\min(b _ {2} , a _ {1}))$

很明显一定会被数据 hack，毕竟是紫题，数据一定很严。

那怎么办呢？看了看楼上 ~~dalao~~ 的题解有了一些启发。

第一点，把数据分成 $up>down$ 和 $up<down$ 的两种情况。显然，    
 $up<down$ 的应该放在前面；再进一步分类讨论，$up$ 的时间应该按照升序排列，$down$ 应该按照降序排列，这样下山时间长的奶牛可以包含奶牛上山的时间。

## 所以排序的代码就应该是

```cpp
bool operator < (node x,node y){
	if(x.up>x.down){
		if(y.up>y.down) return x.down>y.down;
		else return 0;
	}
	else{
		if(y.up<y.down) return x.up<y.up;
		else return 1;
	}
}
```


第二件事就是确定了顺序后如何模拟的问题。

最终的 $ans=\max((up _ {1}+up _ {2}+......+up _ {n}),ans)+down _ {n}$

简要的证明一下，如果已经排出两组数据的顺序：

$up _ {1}$   $down _ {1}$

$up _ {2}$    $down _ {2}$

根据以上公式的其中一种情况从而推出最简公式：

$up _ {1}+down _ {1}>up _ {1}+up _ {2}$

  $down _ {1}>up _ {2}$

这种情况下上时间已包含第二头牛上山时间，这时就取更大的那个数

同理可得第二种情况，在此不多赘述。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int up,down;
}a[100005];
int n;
bool operator < (node x,node y){
	if(x.up>x.down){
		if(y.up>y.down) return x.down>y.down;
		else return 0;
	}
	else{
		if(y.up<y.down) return x.up<y.up;
		else return 1;
	}
} 
int ans;
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i].up>>a[i].down;
	}
	sort(a,a+n);
	int ans=0,sum=0;
	for(int i=0;i<n;i++){
		sum+=a[i].up;
		ans=max(ans,sum)+a[i].down;
	}
	cout<<ans;
	return 0;
}
```

语文不好，就不注释了。


---

## 作者：哈士奇憨憨 (赞：0)

## 题意
给定 $N$ 只奶牛上山和下山需要的时间，可以按照任意顺序上山和下山，但同时只有一只奶牛在上山，只有一只奶牛在下山，求所有奶牛上下山花费的最少时间。
## 思路
首先，虽然奶牛可以按照任意的顺序上下山，但是不难发现，下山的顺序是没必要调整的，如果同时有多只奶牛在山顶，她们按照任意顺序下山，都不影响答案，所以我们只需要考虑奶牛行动的顺序即可。

令当前最后一只奶牛上山的时间为 $x$，下山时间为 $y$，加上下一只上下山时间分别为 $u$ 和 $d$ 的奶牛，更新时间的方式为：
1. $x$ 加上 $u$。
2. $y$ 和 $x$ 取较小值。
3. $y$ 加上 $d$。

初始时 $x$ 和 $y$ 均为 $0$，最后的答案就是 $y$。
通过更新的方式可知，我们应该尽量避免 $y$ 被 $x$ 更新，由此可以贪心的安排顺序：

1. $u<d$ 的奶牛应该比 $u\ge d$ 的奶牛先走。
2. 在所有 $u<d$ 的奶牛中， 小的奶牛应该先走，此时第一只奶牛上山的时间也最短。
3. 在所有 $u\ge d$ 的奶牛中， 大的奶牛应该先走，此时最后一只奶牛下山的时间也最短。
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
using Pii = pair<int, int>;
const int kMaxN = 25001;
Pii a[kMaxN];
int n, x, y;
int C(Pii p) {                                           // 计算排序时的值
  return p.first < p.second ? p.first : 1e9 - p.second;  // 先比较两个值的大小关系，再比较对应值
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  sort(a + 1, a + 1 + n, [](Pii i, Pii j) { return C(i) < C(j); });
  x = y = 0;  // 初始化时间
  for (auto p : a) {
    x += p.first;   // 累加上山时间
    y = max(x, y);  // 更新下山时间
    y += p.second;  // 累加下山时间
  }
  cout << y;
  return 0;
}
```

---

## 作者：破忆 (赞：0)

### 【题目大意】
n头奶牛需要上山下山，需要花时间

一次只能有一头奶牛上山，也只能由一头奶牛下山

求所有奶牛完成锻炼的最短时间

------------

### 【分析】

观察数据，显然这是贪心

一般推导贪心方法很困难

不妨用生活经验感性分析

首先必须要知道先完成上山的牛先开始下山，可以减少等待时间

有两种牛可以很快确定方案

第一种是上山快的牛，把它放在前面，这样能减少其它牛等待上山的时间

第二种是下山快的牛，把它放在后面，这样能减少已经完成的牛等待所有牛完成的时间

这样就得到了一种贪心方式：根据上山下山时间中较小值排序，让牛尽可能分配到节省时间的组，上山较快的排前面，下山较快的排后面。

这里的比较都是先对每头牛自身上下山的比较，再对所有牛进行比较

------------
### 【算法】
贪心

------------

### 【代码】
```cpp
#include<bits/stdc++.h>
#define maxn 25005
using namespace std;
int n,fst,lst,id[maxn],p[maxn];
struct why{
	int u,d,c;
	bool operator <(why b)const{return c<b.c||(c==b.c&&u<b.u);}
}a[maxn];
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
bool cmp(int x,int y){return a[x].c<a[y].c;}
int main(){
 	freopen("P1561.in","r",stdin);
 	freopen("P1561.out","w",stdout);
	n=read();
	int L=0,R=n+1;
	for(int i=1;i<=n;i++)  a[i].u=read(),a[i].d=read(),a[i].c=min(a[i].u,a[i].d),id[i]=i;
	sort(id+1,id+1+n,cmp);
	for(int i=1;i<=n;i++){
		if(a[id[i]].c==a[id[i]].u) p[++L]=id[i];
		else p[--R]=id[i];
	}
	for(int i=1;i<=n;i++){
		fst+=a[p[i]].u;
		lst=max(lst,fst)+a[p[i]].d;
	}
	printf("%d\n",lst);
	return 0;
}
```



---

