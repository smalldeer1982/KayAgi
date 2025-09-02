# [USACO18OPEN] Out of Sorts P

## 题目描述

留意着农场之外的长期职业生涯的可能性，奶牛 Bessie 开始在不同的在线编程网站上学习算法。她最喜欢的两个算法是“冒泡排序”和“快速排序”，但不幸的是，Bessie 轻易地把它们搞混了，最后实现了一个奇怪的混合算法！

如果数组 $A$ 中 $A[0 \ldots i]$ 的最大值不大于 $A[i+1 \ldots N-1]$ 的最小值，我们就称元素 $i$ 和 $i+1$ 之间的位置为一个“分隔点”。Bessie 还记得快速排序包含对数组的重排，产生一个分隔点，然后递归对两侧的 $A[0 \ldots i]$ 和 $A[i+1 \ldots N-1]$ 排序。然而，尽管她正确地记下了数组中所有的分隔点都可以在线性时间内求出，她却忘记了快速排序应该如何重排来快速构造一个分隔点！在这个可能是排序算法历史上最糟糕的失误之下，她做出了一个不幸的决定：使用冒泡排序来完成这个任务。

以下是 Bessie 最初对数组 $A$ 进行排序的实现的概要。她首先写了一个简单的函数，执行冒泡排序的一轮：

```
bubble_sort_pass(A) {
   for i = 0 to length(A)-2
      if A[i] > A[i+1], swap A[i] and A[i+1]
}
```

她的快速排序（相当快）函数的递归代码如下：

```
quickish_sort(A) {
   if length(A) == 1, return
   do { // Main loop
      work_counter = work_counter + length(A)
      bubble_sort_pass(A)
   } while (no partition points exist in A)
   divide A at all partition points; recursively quickish_sort each piece
}
```

Bessie 好奇于她的代码能够运行得多快。简单起见，她计算出主循环的每一轮都消耗线性时间，因此她通过增加一个全局变量 `work_counter` 的值来跟踪整个算法完成的总工作量。

给定一个输入数组，请预测 `quickish_sort` 函数接收这个数组后，变量 `work_counter` 的最终值。

## 说明/提示

在这个例子中，数组初始为 `20 2 3 4 9 8 7`。在一轮冒泡排序之后（增加 $7$ 的工作量），我们得到 `2 | 3 | 4 | 9 8 7 | 20`，其中 `|` 表示一个分隔点。于是问题被分成了递归的子问题，包括对 `2`、`3`、`4`、`20` 排序（每个消耗 $0$ 单元的工作量）和对 `9 8 7` 排序。对于 `9 8 7` 这个子问题，主循环的一轮（$3$ 单元工作量）得到 `8 7 | 9`，在此之后最后一轮处理 `8 7`（$2$ 单元工作量）就有效地完成了排序。

题目来源：Brian Dean

## 样例 #1

### 输入

```
7
20
2
3
4
9
8
7```

### 输出

```
12
```

# 题解

## 作者：Ajsoabk (赞：9)

**这道题的关键是研究分隔点，元素与答案的关系**

#  理解理解
## 定义分隔点i为元素i与i+1之间的一条分割线，简称点i
## 分清楚元素、位置、点的区别
### 问题转化：
1：对于一段已排完序的区间，每两个位置中间都有且仅有一个分隔点，换言之，区间有序的标志就是所有的分隔点都已出现

难道不是显然？
### t[i]定义：
2：对于一个分隔点i，t[i]是它出现的时间

->是最后一个进来该区间的元素的时间

->是最右的**本应在分隔点i左边的元素maxpos**到点i的**距离**（最远的进来了，不就都进来了）
                    
若没有这样的点则为1（出现时间最少是1）

这里的“本应在...（位置）”指的是最终位置，发现这个对3有启发，觉得表述不清的的下面有解释
### 答案转化
3：将答案ans的增加过程看成两个分隔点之间所有位置对ans产生1的贡献，一个位置会不断对答案产生贡献**直到其左右两边都产生了分隔点**（重要性质）

#### 故由2，3可推出位置i对ans的贡献为max(t[i],t[i-1]),i：1~n，即位置i两边更晚出现的分隔点出现的时间

故ans是每个位置i的max(t[i],t[i-1])的和

# 小小的解释
## 最右的**本应在分隔点i左边的元素maxpos**到点i的**距离**
![](https://cdn.luogu.com.cn/upload/pic/37601.png )

maxpos可用结构体在排序前将位置pos记录，排序后位置i及位置i之前pos的最大值即为maxpos

## 为何有些题解是max(t[i],t[i+1])
因为他们是从0~n-1
max(t[0],t[1])...max(t[n-1],t[n])不就是这里的
max(t[1],t[0])...max(t[n],t[n-1])



---

## 作者：hs_black (赞：7)


## [P4372 Out of Sorts P](https://www.luogu.org/problem/P4372)
### 博客内食用效果更佳[冒泡排序深入理解](https://www.luogu.org/blog/hs-black/mao-pao-pai-xu-shen-ru-li-xie)

### 这道题用到了一个套路, 就是"横向变纵向"

求每一次冒泡排序的长度, 不如求每一个点被冒泡排序了几次

定义分割点为i与i+1的分割线,不妨假设它就在i上吧

再次定义序列排好序的标准

### 我们称一个序列是有序的当且仅当所有点(除了n)都是分割点

那么接下来我们要求分割点的出现时间t数组

### 为什么求:

对于每个点它不用在进行冒泡排序了当且仅当两边都已成为分割点, 也就是两边出现时间的最大值

依据t数组,我们可以求出每个点被排了几次

### 怎么求(敲重点):

首先离散化

对于一个点x来说, 所有小于它的数却在它后面的, 每一次都会向前走一次

那么它出现的时间就是离它最远的小于它的点冒泡到它前面的时间

即那个点到它的距离, 具体见代码

所以单调队列或指针都可以维护

代码:

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int N = 100500;
int d[N], n;
int read(void) {
	int x = 0;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)){
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	return x;
}
struct node{
	int val, pos;
	bool operator < (const node &i) const{
		if (val == i.val) return pos < i.pos;
		return val < i.val;
	}
}p[N];
bool cmp(node i,node j) {
	return i.pos < j.pos;
}
int t[N], k;
int main() {
//	freopen("hs.in","r",stdin);
	n = read();
	for (int i = 1;i <= n; i++) p[i] = (node){read(),i};
	sort(p + 1,p + n + 1);
	for (int i = 1;i <= n; i++) p[i].val = i;
	sort(p + 1,p + n + 1, cmp);
	long long ans = 0;
	k = n;
	for (int i = n;i >= 1; i--) {
		while (p[k].val > i) k--;
		t[i] = max(p[k].pos - i, 1);
	}
	for (int i = 0;i < n; i++) ans += max(t[i], t[i+1]);
	printf ("%lld\n", ans);
	return 0;
}
/*
6
2 5 6 3 1 4

*/
```


---

## 作者：XuYueming (赞：3)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P4372)。

其他题解十分生硬地给出了 `t[]` 的定义，本题解按照解题思路，层层递进，自然得出题目解法。

前往[我的博客](https://www.cnblogs.com/XuYueming/p/18705237)获得更好的阅读体验。

## 题意简述

以下是冒泡排序的一轮：

```cpp
void bubble_sort(int val[], int l, int r) {
    for (int i = l; i < r; ++i)
        if (val[i] > val[i + 1])
            swap(val[i], val[i + 1]);
}
```

定义 $(p, p+1)$ 是 $\{a_n\}$ 的一个「分割点」当 $\max\limits_{i=1}^{p}a_i\leq\min\limits_{i=p+1}^na_i$。

以下是一个基于分治和冒泡排序的排序算法：

```cpp
void qsort(int val[], int l, int r){
	if (l == r) return;
	do {
		bubble_sort(val, l, r);
		work_cnt += r - l + 1;
	} while (!check(val, l, r));
	// check(val, l, r) 返回 val[l~r] 中是否存在「分割点」
	divide_and_qsort_each_piece(val, l, r);
	// 将 val[l~r] 按照「分割点」分割成若干子问题，并递归调用 qsort
}
```

给你长度为 $n$ 的序列 $\{a_n\}$，求运行 `qsort(a, 1, n)` 后，全局变量 `work_cnt` 的值。

$n \leq 10^5$。

## 题目分析

显然我们需要分析冒泡排序的性质。

一轮冒泡排序后，肯定会产生一个「分割点」。这是由于一轮冒泡排序后，序列中的最大值被冒泡到了最右侧，所以产生了一个「分割点」。所以那个 `do...while` 实际没有用处。

然后发现整个序列在排序过程中比较鬼畜，难以发现性质。于是考虑转变计数视角，求每一个元素被 `bubble_sort` 了多少次，答案就是每个元素答案之和。

对于一个元素，只要它没有到达最终位置，它会一直被 `bubble_sort`，这在时间轴上体现为一段前缀，我们只要求出在什么时候这个元素不会被 `bubble_sort` 即可。发现，每个元素唯一的递归出口 `l == r` 的实际含义为，该元素左右两侧都出现了「分割点」，于是问题似乎可以被进一步规约到每一个「分割点」出现的时刻。

一个「分割点」出现，当该在它左侧的元素都在它左侧，该在它右侧的元素都在它右侧了。这么想是因为我们冒泡排序的经典思考方式，关注于每一个元素的移动。我们有一个经典结论：

**经典结论：**

对于一个元素，倘若它想要向左移动，它在一轮冒泡中会恰向左移动一个位置。

**证明：**

考虑在一轮冒泡中，它会且只会和其左侧的最大值 `swap`，然后向左移动一个位置。

所以我们考虑在某一个「分割点」右侧的元素，什么时候到这个「分割点」左侧。所需的冒泡轮数，根据我们的结论，就是它到「分割点」的距离。那么对于所有在它右侧且想要跑到它左侧的元素，求出位置最靠右的元素的位置，即可求出这个「分割点」出现的时间。

接下来随便求了。给出一种可能的实现方式：设 $b_i$ 表示排序后的序列 $a'$ 的第 $i$ 个元素 $a'_i$ 为原序列 $a_{b_i}$，再设 $\operatorname{mxR}_i$ 表示 $1\sim i$ 中，目标位置最右在哪里。那么 $t_i=\operatorname{mxR}_i-i$ 就是「分割点」$(i, i+1)$ 出现的时刻。倘若其值小于 $1$，说明该「分割点」一开始便存在，对 $1$ 取 $\max$ 即可。答案根据我们的分析为 $\sum\limits_{i=1}^n\max\{t_{i-1},t_i\}$，其中 $t_0=1$。$b_i$ 排序以下即可，很好求，不难发现 $\operatorname{mxR}_i$ 即为 $b_i$ 的前缀最大值。

时间复杂度 $\mathcal{O}(n\log n)$，瓶颈在于一开始的排序。

## 代码

实际实现起来很短。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 100010;

int n, a[N], b[N], t[N];
long long ans;

signed main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        b[i] = i;
    }
    sort(b + 1, b + n + 1, [] (int x, int y) -> bool {
        if (a[x] == a[y]) return x < y;  // notice this detail
        return a[x] < a[y];
    });
    t[0] = 1;
    for (int i = 1; i <= n; ++i) {
        b[i] = max(b[i], b[i - 1]);  // mxR[i]
        t[i] = b[i] - i;
        if (t[i] <= 0) t[i] = 1;
    }
    for (int i = 1; i <= n; ++i)
        ans += max(t[i], t[i - 1]);
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：OIer_ACMer (赞：3)

~~牛之进化~~。

------------
注：本题笔者用的方法比较简单，因此不会过多阐述证明和原理，望周知！

------------
## 大致思路：
首先，我们很容易就想到冒泡排序这一~~毒瘤~~暴力算法。但，为了得满分，我们先来观察一下题目细节，发现 $\operatorname{workcounter}$ 函数每次加的是当前的长度，也就是说当前每个元素会对答案产生加 $1$ 的贡献。一个元素会一直产生贡献直到它两边都有分隔点。如果我们**求出了每个分隔点出现的时间**，那么每个点的贡献就是两边分割点出现时间的较大值。

考虑怎么算 $i$ 和 $i+1$ 间出现分隔点的时间：出现分隔点当且仅当前前 $i$ 小的数全部在分隔点之前。一轮冒泡过后前 $i$ 个数中**最靠右的数一定会向左移一位**，所以出现的时间就是 $r - i$。具体实现的话，我们可以先把所有元素排序（先按大小，**再按原序列中的位置，因为冒泡排序是稳定排序**，用 $\operatorname{cmp}$ 函数实现），从左往右求出现时间，同时用第 $i$ 小的元素的初始位置维护当前最靠右的位置。最后用上文提到的方法求出答案就好了。

然而，我们还要注意一件事：当 $n=1$ 的时候要特殊处理，因为**根本不会进入循环**，会漏掉；而且如果一个位置两边一开始就有分隔点，**它也会产生 $1$ 的贡献**，因为这相当于是个 do 和 while 循环。复杂度瓶颈在于排序，总复杂度为 $O(N \log{N})$。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
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
struct node
{
    int x, id;
} a[100010];
bool cmp(node x, node y)
{
    if (x.x == y.x)
    {
        return x.id < y.id;
    }
    else
    {
        return x.x < y.x;
    }
}
int t[100010];
int main()
{
    int n;
    n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i].x = read();
        a[i].id = i;
    }
    if (n == 1)
    {
        cout << 0;
        return 0;
    }
    sort(a + 1, a + n + 1, cmp);
    int maxx = 0;
    for (int i = 1; i < n; i++)
    {
        maxx = max(maxx, a[i].id);
        t[i] = maxx - i;
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int tmp = 0;
        if (i >= 1)
        {
            tmp = max(tmp, t[i - 1]);
        }
        if (i < n)
        {
            tmp = max(tmp, t[i]);
        }
        if (tmp == 0)
        {
            tmp = 1;
        }
        ans += tmp;
    }
    cout << ans << endl;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122988971)

---

## 作者：ljc20020730 (赞：2)

我们不妨宏观考虑这个排序的问题，在对于A进行子冒泡排序的时候，可以发现，比第i个元素小的元素且在i右边的元素是以1贡献/次向i移动的。

所以第i个元素和第i+1元素之间的隔板产生的区间长度就是$ (maxpos-i+1-1)=maxpos-i $,其中$ maxpos $指的是排序以后比$a_i$元素更小的，但排在$a_i$元素的右边，且距离$a_i$最远的数$a_j$的下标(位置)$j$。

对于i被计算1次当他的前面隔板不是连续的，或者 后面隔板不是连续的满足其一即可，所以若把i存在于的这个隔板不连续的区间排成有序，那么仅对于元素i它被算的次数（产生的贡献）是$max(t_{i-1},t_i)$

说明一下： 如果i前后隔板都不连续的话i被产生$max(t_{i-1},t_i)$后便不产生贡献了，如果前面或后面隔板不连续显然。

有了上面的说明，这个题目的算法呼之欲出，

 1. 遍历原数组，当前位置为i，求出$ t_i $，查找最后一个比$a_i$小的数出现的位置为j，令$ t_i = j - i $

 2. 求出 $ans = \sum\limits_{i=1} ^ {n} \max \{ t_{i-1}, t_i \}$ 并输出。

 显然按照上面模拟是$ O(n^2) $算法。

 我们可以这样做，先把$a_i$每个元素记录它的值$val$和下标$i$，排序。

 那么求一个前缀$ maxpos=max{a[i].id , maxpos }$，显然遍历到i位置的时候，前面都是比$ a[i] $ 的值，然后前面最大的$ id $号码就是$ maxpos $。

 那么时间复杂度就降到$ O(nlog_2n) $
 
 ```
 # include <bits/stdc++.h>
# define int long long
using namespace std;
const int N=1e5+10;
struct rec{ int val,id; }a[N];
int n,t[N];
bool cmp(rec a,rec b)
{
    if (a.val!=b.val) return a.val<b.val;
    else return a.id<b.id;
}
signed main()
{
    scanf("%lld",&n);
    for (int i=1;i<=n;i++)
     scanf("%lld",&a[i].val),a[i].id=i;
    sort(a+1,a+1+n,cmp);
    int maxpos=0;
    for (int i=1;i<=n;i++) {
        maxpos=max(maxpos,a[i].id);
        t[i]=max(1ll,maxpos-i);
    } 
    int ans=0;
    for (int i=1;i<=n;i++)
     ans+=max(t[i],t[i-1]);
    cout<<ans; 
    return 0;
}
 ```

---

## 作者：miaokehao (赞：1)

每次排序，i之后的比i小的数都会以1位的速度向i靠近，所以在i出现分割点的时间就是i之后的最后一个元素到i的距离；  
而每一次，位置i前面一个格子的长度会被算一次，i后面一个格子长度会被算一次。所以i被计算的次数就是max(t[i],t[i+1])
```
#include <bits/stdc++.h>
#define ll long long
#define res register ll
#define N 100005
using namespace std;
ll n,maxpos,t[N],ans;
inline ll read() {
    ll X=0,w=0;
    char ch=0;
    while(!isdigit(ch)) {
        w|=ch=='-';
        ch=getchar();
    }
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
struct papa{
	ll id,num;
	inline bool operator<(const papa&b) const{
		return (num==b.num&&id<b.id)||num<b.num;
	}
}a[N];
signed main(){
	n=read();
	for(res i=1;i<=n;i++)
	  a[i].num=read(),a[i].id=i;
	sort(a+1,a+n+1);
	for(res i=1;i<=n;i++){
	    maxpos=max(maxpos,a[i].id);
		t[i]=max(1LL,maxpos-i);
	}
	for(res i=1;i<=n;i++)
	  ans+=max(t[i],t[i-1]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：legenc6y (赞：0)

最后犯蠢了，所以看了 hs_black 老师的题解。

这种新式排序问题的核心在于找排序方法的性质。

首先离散化一下，参考 [Ynoi 2016] 掉进兔子洞。

一开始并没有什么思路，简单地画一画，在进行若干尝试后，只能得到一些错误的结论，而且都和题目的形式没有什么关系。

进行一些别的尝试，我们去关注怎样的 $x,x+1$ 之间会有分割点。要注意到，在 $x,x+1$ 这个分割点出现之前就有的分割点并不影响我们关注的 $x,x+1$，于是 **成为分割点的条件是相对独立的**。

那么看一看 $x$ 之后的这个分割点。它要求 $[1,x]$ 内的元素都在下标 $[1, x]$ 的范围内，于是对于下标 $>x$ 的，值域为 $[1, x]$ 的元素，它前面一定有比它大的，根据冒泡排序的过程，可以发现它们的下标每次减 $1$。于是 $x$ 之后出现分割点的时间 $tim_x$ 就是 $\max(1, mxp-x)$，其中 $mxp$ 是值域在 $[1, x]$ 内的元素的最大下标。这里和 $1$ 取 $\max$ 是因为我们不认为一开始就存在这个分割点。这是为了方便后面的计算。

然后考虑计算。我犯蠢的一个点是，上来就认为 $\mathrm{len}(A)$ 这个东西肯定没法转化，所以只能直接算。于是可以类似 NOIP 积木大赛 那个题的暴力做法，每次分治下去计算。比较蠢。

事实上这个贡献的形式可以转化为每个点被计算的次数。对于点 $x$，显然 $\max(tim_{x-1}, tim_x)$ 次后两边都是分割线，停止递归。于是 $x$ 的贡献就是这个。

时间复杂度 $\mathcal O(n\log n)$，瓶颈在一开始的排序离散化·。

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fir first
#define sec second

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int maxn = 1e5 + 5;
int n, a[maxn], tim[maxn], ord[maxn], mxp;

void chkmax(int& x, int y) { if (y > x) x = y; return ; }

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	std::iota(ord + 1, ord + 1 + n, 1);
	std::sort(ord + 1, ord + 1 + n, [&](const int& lhs, const int& rhs) {
		return a[lhs] < a[rhs] || (a[lhs] == a[rhs] && lhs < rhs);
	});
	for (int i = 1; i <= n; ++i)
		a[ord[i]] = i;
	i64 ans = 0;
	for (int i = 1; i <= n; ++i) {
		chkmax(mxp, ord[i]); chkmax(tim[i] = mxp - i, 1);
		ans += std::max(tim[i], tim[i - 1]);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

