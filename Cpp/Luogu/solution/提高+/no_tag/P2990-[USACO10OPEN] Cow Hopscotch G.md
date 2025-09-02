# [USACO10OPEN] Cow Hopscotch G

## 题目描述

奶牛们正在回味童年，玩一个类似跳格子的游戏，在这个游戏里，奶牛们在草地上画了一行 $N$ 个格子，编号为 $1\dots N$。

就像任何一个好游戏一样，这样的跳格子游戏也有奖励！第 $i$ 个格子标有一个数字 $v_i$ 表示这个格子的钱。奶牛们想看看最后谁能得到最多的钱。

规则很简单：

* 每个奶牛从 $0$ 号格子出发。($0$ 号格子在 $1$ 号之前，那里没钱)

* 然后她执行一个可能为空的跳跃序列前往格子 $N$。她每次落地所在的格子距离前一个格子最多 $K$ 个格子（例如，如果 $K=2$，从格子 $1$ 出发，她最多可以跳到格子 $2$ 或 $3$）。

* 在任何时候，她都可以选择回头往 $0$ 号格子跳，直到跳到 $0$ 号格子。

另外，除了以上规则之外（包括 $K$ 限制），回头跳的时候还有两条规则：

* 不可以跳到前进序列中的格子（格子 $0$ 除外）。

* 除了 $0$ 号格子之外，她在回来的时候，停留的格子必须是恰巧过去的时候停留的某个格子的前一格（尽管她可能在返回时做一些更大的跳跃，从而跳过一些潜在的返回格子）。

她赚取的金钱数量等于她跳过的所有格子的金钱价值之和。请找出奶牛能赚到的最大金额。

举例说明，考虑一个有六个格子的路线，其中 $K = 3$。

```
格子编号:       0      1      2      3      4      5      6 
            +---+  +---+  +---+  +---+  +---+  +---+  +---+ 
            |///|--|   |--|   |--|   |--|   |--|   |--|   | 
            +---+  +---+  +---+  +---+  +---+  +---+  +---+ 
值:            -      0      1      2     -3      4      5 
```

Bessie 的一种最优途径为（括号中表示当前格子的金钱收益）： $0[0] \to 1[0]\to 3[2]\to 6[5] \to 5[4] \to 2[1] \to 0[0]$。

如果 Bessie 跳了一个以 $0, 1, 2, 3, 4, \dots$ 开始的序列，那么她将无法返回，因为她无法合法地跳回到一个未被触碰过的格子上。

## 说明/提示

**【数据范围】**


数据保证：$-2 
\times 10 ^9 \le V_i \le 2 \times 10 ^ 9$，$3 \le N \le 2.5 \times 10^5$，$2 \le K \le N$。

## 样例 #1

### 输入

```
6 3 
0 
1 
2 
-3 
4 
5 
```

### 输出

```
12 
```

# 题解

## 作者：mqxmm (赞：5)

# 小兔的话
欢迎大家在评论区留言哦~



# 思路
因为每次来回的路径是不重复的，所以每次来回的路径都可以在第一次的来回走完，就把问题转化成求奶牛走一次来回所能获得的最大价值了  

$n$ 的范围较大，肯定是不能搜索的，不妨来思考一下 $dp$：  
假设现在 **在第 $i$ 个格子** 进行 $dp$ 转移，再假设如果从 **第 $r$ 个格子** 往回跳到 **第 $l$ 个格子** $(l \leq i - 1 < r)$  
- 如果 **不跳到第 $i - 1$ 个格子**，即 $l < i - 1$；既然如此，那么在 $[l + 1, r - 1]$ 中，可以只跳价值为正的格子，这样价值才最大；所以可以用数组存放正价值的前缀和，记为 $s$ **$($ 这种情况会在 $dp_r$ 的时候被转移 $)$**  
- 如果 **跳到第 $i - 1$ 个格子**，即 $l = i - 1$；可以在这种情况进行 $dp$：设 $dp_i$ 表示 **往前(正方向)跳的时候，跳到第 $i$ 个格子；往回跳的时候，跳到第 $i - 1$ 个格子** 的 **最大价值**；可以暴力枚举 $j \  (i - k \leq j \leq i - 2)$，表示从 **第 $j$ 个格子** 跳到 **第 $i$ 个格子** ，由 $dp_j$ 进行状态转移：$dp_i = dp_j + (v_i + v_{ i - 1 }) + (s_{ i - 2 } - s_j)$  
  - $j \neq i - 1$：因为 **第 $i - 1$ 个格子** 是往回跳的格子，不能重复  
  - $v_i + v_{ i - 1 }$：往前跳和往回跳的价值都是需要的  
  - $s_{ i - 2 } - s_j$：$[j + 1, i - 2]$ 的所有正价值和；这些格子是可以提供价值的 $($ 因为 $i - j \leq k$，所以 $[j + 1, i - 2]$ 中的任意一个格子距离 $i, j$ 的距离都不会超过 $k$ $)$  



# 分析
$dp$ 初始化：$dp_0 = 0$，$dp_1 = v_1$  

$dp$ 处理完了，就需要寻找答案了：  
暴力枚举 $i \  (0 \leq i \leq n)$，对于每个 $i$ 它可以再跳 $k - 1$ 个格子，再直接回到 第 $\mathrm{max(i - 1, 0)}$ 格子，因此需要加上 $[i + 1, i + k - 1]$ 的正价值和 $($ 这种情况在 $dp$ 中是 **没有** 并且 **不能** 被处理的 $)$  

但暴力 $dp$ 肯定是不行的，需要优化  

$dp_i = dp_j + (v_i + v_{ i - 1 }) + (s_{ i - 2 } - s_j)$  
$dp_i = (dp_j - s_j) + (v_i + v_{ i - 1 } + s_{ i - 2 })$  

可以考虑单调队列优化：  
由于需要求 $dp$ 最大值，$v_i + v_{ i - 1 } + s_{ i - 2 }$ 是定值，所以需要保证 $dp_j - s_j$ 为最大值；以 $dp_j - s_j$ 为价值，进行单调队列优化就可以了  



# 代码
```cpp
#include <cstdio>

namespace Rabbit
{
	#define i64 long long
	#define u64 unsigned i64
	
	i64 Max(i64 a, i64 b) { return a > b ? a : b; }
	i64 Min(i64 a, i64 b) { return a < b ? a : b; }
	
	int rint()
	{
		int x = 0, fx = 1; char c = getchar();
		while (c < '0' || c > '9') { fx ^= (c == '-' ? 1 : 0); c = getchar(); }
		while ('0' <= c && c <= '9') { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
		if (!fx) return -x;
		return x;
	}
} using namespace Rabbit;

const int MAX_n = 250000;
const int MAX_v = 2e9;

int n, k, v[MAX_n + 5];
int que[MAX_n + 5], head, tail;
i64 res, s[MAX_n * 2 + 5], dp[MAX_n + 5];

i64 Get_DP(int i, int j) { return dp[j] + v[i] + v[i - 1] + s[i - 2] - s[j]; }
i64 Value(int j) { return dp[j] - s[j]; }
bool Check_Head(int i) { return i - que[head] > k; }
bool Check_Tail(int i) { return Value(i) > Value(que[tail]); }

int main()
{
	n = rint(), k = rint();
	if (k > n) k = n;
	for (int i = 1; i <= n; i++)
	{
		v[i] = rint();
		s[i] = s[i - 1] + (v[i] > 0 ? v[i] : 0);
	}
	for (int i = n + 1; i <= n + k - 1; i++)
		s[i] = s[i - 1];
	dp[0] = 0, dp[1] = v[1];
	res = Max(s[k], dp[1] + s[k] - s[1]);
	que[head = tail = 1] = 0;
	for (int i = 2; i <= n; i++)
	{
		while (tail - head + 1 >= 2 && Check_Head(i)) ++head;
		dp[i] = Get_DP(i, que[head]);
		res = Max(res, dp[i] + s[i + k - 1] - s[i]);
		while (tail - head + 1 >= 1 && Check_Tail(i - 1)) --tail;
		que[++tail] = i - 1;
	}
	printf("%lld\n", res);
	return 0;
}

```


---

## 作者：CaoXian (赞：4)

## P2990 [USACO10OPEN]Cow Hopscotch G 题解

题意很简单，感觉可以使用动态规划求解。

先来看一个最暴力的 `dp`：

令 $dp_{i}$ 表示正着跳到第 `i` 个格子并且返回时跳到第 `i - 1` 个格子能得到的最大价值之和。

$$dp_{i} = v_{i} + v_{i - 1} + \max\limits_{\max(0, i - k) \leq j \leq i - 2}{\left\{dp_{j} + \sum\limits_{l = j + 1}^{i - 2}{\max(v_{l}, 0)}\right\}}$$

(~~感觉打得是不是有点复杂了~~)

应该挺好理解的，其中的 $v_{i} + v_{i - 1}$ 是将往回跳和正着跳踩到的格子的价值，$\sum\limits_{l = j + 1}^{i - 2}{\max(v_{l}, 0)}$ 表示去的时候可以踩的格子没有限制所以尽量把能踩到的权值为正的格子踩了。

可以发现，上面的 $\sum\limits_{l = j + 1}^{i - 2}{\max(v_{l}, 0)}$ 可以使用前缀和给优化掉。

所以就变成了：

$$dp_{i} = v_{i} + v_{i - 1} + \max\limits_{\max(0, i - k) \leq j \leq i - 2}{\left\{dp_{j} + sum_{i - 2} - sum_{j} \right\}}$$

其中：

$$sum_{i} = \sum\limits_{j = 1}^{i}{\max(v_{j}, 0)}$$

可以把 $\max\limits_{\max(0, i - k) \leq j \leq i - 2}{\left\{dp_{j} + sum_{i - 2} - sum_{j} \right\}}$ 里面的 $sum_{i - 2}$ 提出来，就变成了：

$$dp_{i} = v_{i} + v_{i - 1} + sum_{i - 2} + \max\limits_{\max(0, i - k) \leq j \leq i - 2}{\left\{dp_{j} - sum_{j} \right\}}$$

然后看到 $\max\limits_{\max(0, i - k) \leq j \leq i - 2}{\left\{dp_{j} - sum_{j} \right\}}$，其中 `j` 的取值范围的左右端点是随 `i` 的增加单调递增的，于是可以用一个单调递减的单调队列优化掉。

时间复杂度就是 $\Theta(n)$ 了。

最后的答案就是：

$$\max\left(\max\limits_{1 \leq i \leq n}{\left\{dp_{i} + sum_{\min(i + k - 1, n)} - sum_{i}\right\}}, sum_{k}\right)$$

注意 $dp_{1}$ 的初始值设为 $v_{1}$。

有什么不理解的可以问我 qwq。

Code:

```cpp
#include <bits/stdc++.h>
#define re register
#define il inline
#define getchar gc
#define fu(i, l, r) for(re int i = l; i <= r; ++i)
using namespace std;
typedef long long ll;
il char gc() {static char ibuf[1 << 20], *p1 = ibuf, *p2 = ibuf; return p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 1000010, stdin), p1 == p2) ? -1 : *p1++;}
il void read(re ll& x) {x = 0; re int f = 1; re char ch = getchar(); while(ch < '0' || ch > '9') f *= ((ch == '-') ? -1 : 1), ch = getchar(); while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar(); x *= f;}
ll n, k, ans, front = 1, back, v[250001], sum[250001], dp[250001], q[250001];
int main() {
	read(n), read(k);
	fu(i, 1, n) read(v[i]), sum[i] = sum[i - 1] + max(v[i], 0ll);
	dp[1] = v[1];
	q[++back] = 0;
	fu(i, 2, n) {//dp 和 单调队列优化
		while(q[front] < i - k) ++front;
		if(front <= back) dp[i] = v[i] + v[i - 1] + dp[q[front]] + sum[i - 2] - sum[q[front]];
		while(front <= back && dp[i - 1] - sum[i - 1] >= dp[q[back]] - sum[q[back]]) --back;
		q[++back] = i - 1;
	}
	fu(i, 1, n) ans = max(ans, dp[i] + sum[min(n, i + k - 1)] - sum[i]);
	printf("%lld", max(ans, sum[k]));
	return 0;
}
```

---

## 作者：神犇的蒟蒻 (赞：4)

#新的题解

重新思考了一下，发现了##一个新思路


**dp+单调队列优化**

TAT。。一开始有个条件没细想结果方程推错了TAT。

主要是转移的时候强制留下哪个点作为回去的落脚点的问题= =。。

预处理出presum[i]表示1~i个格子中，正数的前缀和（因为在K的小范围内肯定会贪心地选正数的点跳），val[i]表示第i个格子上的数字。

f[i]表示当前跳到第i个格子，并且留下了一条回去的路的最大总和。

f[i]=max{f[j]+presum[i-1]-presum[j]}+val[i-1]+val[i]，（i-K<=j<i-1）

也就是从j跳到i，并且强制(i-1)不走，留作回去的路（但回来的时候一定会走的。。所以先把val[i-1]加上）。

max{f[i]}并不是最后的答案。。因为对于f[i]，我们留下了(i-1)作回去时的第一个点。。所以还可以走完 [i+1,i-1+K]这些点中的正数点 再跳回(i-1)。。。注意边界

一开始太懒。不想算最后多走一段的情况。。所以不是强制i-1不走，而是强制j+1不走。。。结果贪心地取[j+2,i]中的点时可能使j+2走不到。。

而如果强制j-1不走的话会重复计算。。。所以还是只能强制i-1不走。。。然而这样就会产生走到i后可以多走一段的情况TAT


代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define ll long long
using namespace std;
const int maxn=250233;
ll f[maxn],presum[maxn],ans,dl[maxn];
int val[maxn],dlpos[maxn];
int i,j,n,m,K,l,r;
int ra,fh;char rx;
inline int read(){
    rx=getchar();ra=0;fh=1;
    while((rx<'0'||rx>'9')&&rx!='-')rx=getchar();
    if(rx=='-')fh=-1,rx=getchar();
    while(rx>='0'&&rx<='9')ra*=10,ra+=rx-48,rx=getchar();return ra*fh;
}
int main(){
    n=read();K=read();n++;
    for(i=2;i<=n;i++)val[i]=read(),presum[i]=presum[i-1]+(ll)(val[i]>0?val[i]:0);//,printf("              %d %lld\n",val[i],presum[i]);
    f[0]=f[1]=0;
    l=1;r=0;
    ll tmp;
    for(i=2,j=0;i<=n;i++,j++){
        tmp=f[j]-presum[j];
        while(l<=r&&dl[r]<=tmp)r--;dl[++r]=tmp;dlpos[r]=j;
        while(l<r&&dlpos[l]<i-K)l++;
//      for(int k=l;k<=r;k++)printf("   %lld %d",dl[k],dlpos[k]);printf("\n");
        f[i]=dl[l]+presum[i-2]+val[i-1]+val[i];
//      printf("%d   %lld\n",i,f[i]);
    }
    ans=f[1]+presum[min(1+K,n)];
    for(i=2;i<=n;i++){
        f[i]+=(i+K-1<=n)?(presum[i+K-1]-presum[i]):(presum[n]-presum[i]);
        if(f[i]>ans)ans=f[i];
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

# 思路

英文看着头大，实际上就是在坐标轴上跳，每次最多跳 $k$ 步，还要跳回来时踩得点必须时跳过去时经过过的点的前一个，求这样跳过去跳回圆点能获得的最大值。

而很容易想到，因为回来时的路径选择是依赖过去的路径，我们可以 DP 过去的路径，同时为回来的路径预留位置，所以我们的 DP 方程 $f[i]$ 表示过去是跳到 $i$ 位置此时能获得的最大价值，转移就是从 $f[i-k]-f[i-2]$ 中取 $\max$（就是选最优决策点），再加上选的最有决策点到当前位置$i$中区间正数的和（因为 k 距离以内可以随便跳，我们贪心选择这段区间价值大于 0 的跳就行了），最后加上 $a[i]$ 和 $a[i-1]$ 就行了。

因为要找的实际上就是在 k 范围内的最大 $f[j]- pre[j]$，很容易想到用单调队列来优化。然后问题就解决了，主要是各种细节。

首先要保证队列中能更新 $i$ 的决策点都是在 $i-k$ 到 $i-2$ 之间的，所以随着 $i$ 的加入顺势加入当前新的决策点 $j$ 就可以了。

优先队列一般都是先删掉列的尾，加入当前的新值，再删过期的头，最后更新要求得的 dp 方程。删尾时要保证队列内不为空，删头时除过期的还要满足题目要求的限定条件，比如队列内必须至少存在几个因素。

这道题最后统计答案时不能忘了，一步跳过去和一部跳回来也可能时一个答案，要先定 $ans$ 初值。

---

## 作者：fanke (赞：1)

### 题目

#### [题目传送门](https://www.luogu.com.cn/problem/P2990)

大意：在坐标轴上跳，每次最多跳 $k$ 步，还要跳回来，而跳回来时踩的点必须是跳过去时经过过的点的前一个，求这样跳过去跳回原点能获得的最大价值。



------------


### 思路 


~~往回跳是一个麻烦的事情。~~

因为回来时的路径选择是依赖过去的路径，所以我们可以动规过去的路径，同时为回来的路径预留位。

综上所述，我们用 $f[i]$ 表示过去时跳到 $i$ 位置此时的最大价值。

转移就是从 $f[i - k] - f[i - 2]$ 中选最优决策点再加上选的最有决策点到当前位置$i$中区间正数的和值，最后加上 $a[i]$ 和 $a[i-1]$ 就行了。

因为要找的实际上就是在 $k$ 范围内的最大 $f[j] - pre[j]$，很容易想到用单调队列来优化。然后问题就解决了，主要是各种细节：

要保证队列中能更新 $i$ 的点都是在 $i-k$ 到 $i - 2$ 之间的，随着 $i$ 的加入当前新的点 $j$ 就可以了。



#### 最后统计答案时不能忘了，一步跳过去和一步跳回来也可能是一个答案，要先定 $ans$ 初值。



------------


### 代码（部分）

```cpp
for(int i = 2,j = 0; i <= n; i ++,j ++) 
{
	//队列中位置必须小于等于 i - 2 才能更新 i 所以定义j来表示 
        long long tmp = f[j] - pre[j];
        while(t - h > 0 && tmp >= f[q[t]] - pre[q[t]])    
			t --;
        q[++ t] = j;
        while(i - q[h+1] > k && t - h > 1)    
			h ++; 
        f[i] = f[q[h + 1]] - pre[q[h + 1]] + a[i] + a[i-1] + pre[i-2];
}
```


---

## 作者：CuriousCat (赞：1)

我就说一下我一直纠结的地方吧qwq

首先通过观察我们知道可以倒着考虑整个过程，先走回去的路，再走去的路，然后就有

f [ i ] = max(i-k<=j<i-1){f[j]+positive\_sum[j+1,i-1]+value[i]+value[i+1]}

其实这个方程很好优化，单调队列搞搞就行了。

但是考虑这一组数据。

```cpp
7 5
-1000
1
1
-1000
1
-1000
1
```
如果我把最右边的点定义成return点，中间的5号点就可以看成是return点之间的去点，所以是对的。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 
const int N = 3e5; 
const ll INF = 2e12; 
struct C { 
    ll x, y; 
    C(ll _x = 0ll,ll _y = 0ll) { x = _x; y = _y; }
} a[N], *h = a, *t = a; 
int n, k; ll p[N], f[N], ans, v[N];
int main(int argc, char *argv[]) {
    freopen("dat.in","r",stdin);
    freopen("my.out","w",stdout);
    int i;
    scanf("%d%d", &n, &k); 
    for (i = 1;i <= n;++i) scanf("%lld", &v[i]); 
    *t++ = C (-1ll, 0ll); 
    for (i = 1;i <= n;++i) p[i] = p[i - 1] + max(v[i], 0ll); 
    for (i = 1;i <= n;++i) {
        while (h != t && i - h->x > k) ++h;
        f[i] = h->y + v[i] + p[i - 1] - p[h->x + 1]; 
        ans = max(ans, f[i] + max(v[i + 1], 0ll)); 
        f[i] += v[i + 1]; 
        printf("f[%d]=%d\n",i,f[i]);
        while (h != t && f[i - 1] > t[-1].y + p[i] - p[t[-1].x + 1]) --t; 
        *t++ = C (i - 1, f[i - 1]);
    }
    printf("%lld\n", ans); 
    return 0; 
}
```

---

## 作者：ni_ju_ge (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P2990)

## 思路
首先可以将几次来回视作一次大的来回，这样不会影响答案也更加便于设置状态。

设 $dp_i$ 为跳到 $i$ 且跳回时跳到 $i-1$ 的答案，那么容易得到

$$dp_i=v_i+v_{i-1}+\max_{i-k\le j\le i-2} (dp_j+\sum_{p=j+1}^{i-2} \max(v_p,0))$$

使用前缀和优化，记 $s_i=\sum_{j=1}^i \max(v_j,0)$，则原式变为

$$dp_i=v_i+v_{i-1}+\max_{i-k\le j\le i-2} (dp_j+s_{i-2}-s_j)$$

也就是

$$dp_i=v_i+v_{i-1}+s_{i-2}+\max_{i-k\le j\le i-2} (dp_j-s_j)$$

发现 $j$ 被限制在 $i-k$ 到 $i-2$ 的范围内且要求 $dp_j-s_j$ 的最大值，可以使用单调队列优化。时间复杂度 $O(n)$。

实现时要注意边界情况，最后要加上 $s_{i+k-1}-s_i$。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2.5e5+5;
ll dp[N],ans;
ll s[N];
ll n,k,v[N];
int q[N],h,t;
int main() {
	cin>>n>>k;
	for(int i=1;i<=n;i++) {
		cin>>v[i];
		s[i]=s[i-1]+max(v[i],0ll);
	}
	dp[1]=v[1];
	h=0,t=1;
	for(int i=2;i<=n;i++) {
		while(h<=t&&q[h]<i-k) h++;
		dp[i]=v[i]+v[i-1]+dp[q[h]]+s[i-2]-s[q[h]];
		while(h<=t&&dp[i-1]-s[i-1]>=dp[q[t]]-s[q[t]]) t--;
		q[++t]=i-1;
	}
	ans=s[k];
	for(int i=1;i<=n;i++) ans=max(ans,dp[i]+s[min(n,i+k-1)]-s[i]);
	cout<<ans;
}
```

---

