# Reading Books (hard version)

## 题目描述

做此题前，建议先做 [CF1374E1 Reading Books (easy version)](https://www.luogu.com.cn/problem/CF1374E1) 。

Alice 和 Bob 一共有 $n$ 本书要读。第 $i$ 本书有三个属性：阅读时间 $t_i$ ， $a_i$（为 $1$ 表示 Alice 喜欢这本书，为 $0$ 表示 Alice 不喜欢）， $b_i$ （为 $1$ 表示 Bob 喜欢这本书，为 $0$ 表示 Bob 不喜欢）。

他们需要从这些书中选择 $m$ 本，满足
- 这些书中至少有 $k$ 本是 Alice 喜欢的，至少有 $k$ 本是 Bob 喜欢的。
- 阅读的总时间最小（总时间为选中的书的 $t_i$ 的总和）

## 样例 #1

### 输入

```
6 3 1
6 0 0
11 1 0
9 0 1
21 1 1
10 1 0
8 0 1```

### 输出

```
24
6 5 1```

## 样例 #2

### 输入

```
6 3 2
6 0 0
11 1 0
9 0 1
21 1 1
10 1 0
8 0 1```

### 输出

```
39
4 6 5```

# 题解

## 作者：sdxjzsq (赞：4)

### 题目链接  
[https://www.luogu.com.cn/problem/CF1374E2](https://www.luogu.com.cn/problem/CF1374E2)   
[https://codeforces.com/contest/1374/problem/E2](https://codeforces.com/contest/1374/problem/E2)  

### 题目大意  
在 $n$ 本书中选出 $m$ 本，使得至少有 $k$ 本 Alice 喜欢、有 $k$ 本 Bob 喜欢，并且总阅读时间最小。  

### 思路  
在 [CF1374E1](https://www.luogu.com.cn/problem/CF1374E1) 中，我们可以~~很显然地~~看出直接用贪心即可 AC。根据CF比赛E1与E2一脉相承的传统，我们可以认为这题也可以用贪心来做，区别是本题增加了恰好读 $m$ 本的限制，这就导致不能像 E1 那样无脑贪心地选时最少的书来读，但这并不妨碍我们贪心。  

首先对书的性质进行分类：  
- $00:$ Alice 和 Bob 都不喜欢  
- $01:$ Alice 喜欢， Bob 不喜欢  
- $10:$ Alice 不喜欢， Bob 喜欢  
- $11:$ Alice 和 Bob 都喜欢  

因为肯定希望优先阅读花费时间更少的书，因此我们可以使用4个优先队列维护上述4类不同的书。

分好类之后，我们像 E1 那样先在 $11$类 和 $01+10$类 中优先选择阅读时间更少的书，直到满足 Alice 和 Bob 喜欢的书都至少有 $k$ 本这一条件，记录当前 $m$ 的消耗情况。为了之后方便调整，我选择将选出来的书从优先队列中弹出，并加入对应的四个答案优先队列中，但将花费时间最长的书放在堆顶（后面将叙述为什么这么做）。  

满足第一个要求后，便分为以下三种情况：  
1. 如果选出的书数量恰好为 $m$，那么直接输出当前答案即可，因为这已经满足了阅读时间最短。 
2. 如果选出的书数量大于 $m$，那么说明 $01+10$类选择地太多，将 1 本 $01+10$类 换成 $11$类 可以在满足“两人都至少有 $k$ 本喜欢”的情况下减少 1 本书。因此我们不断将 $01+10$类 换为 $11$类 直到数量等于 $m$ 即可。如果发现 $11$类 的书不够用或者答案队列中已经没有 $01+10$ 类 的书，那么可以判定无解。  
3. 如果选出的书数量小于 $m$，那么说明还需要更多的书。在这种情况下我们有两种选择：一是将 $11$类 的书换为 $01+10$类 的书，这样可以在满足要求的情况下增加 1 本选出的数量；二是在四类书中选择用时最短的一本直接加入答案队列中。    
为了保证总阅读时间最小，我们需要从上述两种选择中选出用时较少的一种方案，这里的用时比较难找出：对于第一种选择，对答案的增量为 “ $01+10$类书的最小用时” 减去 “答案序列中 $11$类书的最长用时”；而对于第二种选择，对于答案的增量为 “四类书中的最小用时”。将这两个用时增量都求出选择用时短的那个即可。  

需要注意的是可能有的种类书的数量不够当前操作，需要提前判断优先队列是否为空（似乎用数组会比优先队列好写？）  

~~（我感觉前面整个过程都保证了贪心的正确性，不证自明，证明略）~~    

上述过程中，我们对优先队列最多执行 $O(n)$ 次操作，而优先队列每次插入与弹出操作时间复杂度为 $O(\log n)$，因此总复杂度为 $O(n\log n)$。  
当然，上述操作中的优先队列可以改为数组+预处理排序实现，但预处理复杂度 $O(n\log n)$，和优先队列复杂度相差不大。  

我的方法和官方不同的是，不需要枚举在 $11$类 书中选择多少本，因此~~可能~~导致了常数上的提升（G++17下我的代码171ms，官方题解592ms，本题洛谷上的另外一篇题解280ms）  

### code
``` cpp
#include <cstdio>
#include <queue>
using namespace std;
const int maxn = 2e5 + 7;
int n, m, k, tot, tmp[4], flag = 1;
struct node
{
    int no, t;
    bool operator<(const node &rhs) const { return t > rhs.t; }
};
priority_queue<node> book[4], ans[4];
int switchD(int v)
{
    node x = book[v].top();
    tot += x.t, x.t = -x.t;
    ans[v].push(x), book[v].pop();
    --m;
}
int switchR(int v)
{
    node x = ans[v].top();
    tot += x.t, x.t = -x.t;
    book[v].push(x), ans[v].pop();
    ++m;
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, t, a, b; i <= n; ++i) scanf("%d%d%d", &t, &a, &b), book[a << 1 | b].push({i, t});
    while (k-- && flag)
    {
        for (int i = 1; i < 4; ++i) tmp[i] = !book[i].empty();
        if ((tmp[1] + tmp[2] < 2) && tmp[3])
            switchD(3); // 01或10类书的数量不够
        else if ((!tmp[3]) && tmp[1] && tmp[2])
            switchD(1), switchD(2); // 11类书的数量不够
        else if (tmp[3] + tmp[2] + tmp[1] == 3)
            if (book[1].top().t + book[2].top().t > book[3].top().t)
                switchD(3); // 11类比01+10类用时短
            else
                switchD(1), switchD(2); // 11类比01+10类用时长
        else
            flag = 0; // 无解的情况下将flag置0
    }
    while (m < 0 && flag)
    {
        tmp[1] = !ans[1].empty(), tmp[2] = !ans[2].empty(), tmp[3] = !book[3].empty();
        if (tmp[1] && tmp[2] && tmp[3])
            switchR(1), switchR(2), switchD(3); // 当前答案本数大于m，将01+10类换成11类
        else
            flag = 0;
    }
    while (m > 0 && flag)
    {
        int now = -1, v = 1e9;
        for (int i = 0; i < 4; ++i)
            if ((!book[i].empty()) && v > book[i].top().t) now = i, v = book[i].top().t;
        tmp[1] = !book[1].empty(), tmp[2] = !book[2].empty(), tmp[3] = !ans[3].empty();
        if (tmp[1] && tmp[2] && tmp[3] && v - ans[3].top().t > book[2].top().t + book[1].top().t)
            switchD(1), switchD(2), switchR(3); // 如果当前 11类 换 01+10类 选择用时更短
        else if (now == -1)                     // 找不到可以换或者加入答案队列中的书
            flag = 0;
        else
            switchD(now);
    }
    printf("%d\n", flag ? tot : -1);
    for (int i = 0; i < 4 && flag; ++i)
        while (!ans[i].empty()) printf("%d ", ans[i].top().no), ans[i].pop();
    return 0;
}
```

---

## 作者：Clouder (赞：4)

## 前言

本文亦发表于[笔者博客](https://www.codein.icu/cf1374e2/)

## 前言2

本题为 CF1374E1 的 Hard Version，题意变化不大，解法也是在其基础上调整，因此如果没有做过的话，建议先做 [CF1374E1](https://www.luogu.com.cn/problem/CF1374E1)，或者简单看看 [我的博客](https://www.codein.icu/cfround653/#toc-CF1374E1ReadingBookseasyversion) 中的题解。

## 题意

每本书都有权值，每本书可能被 A 喜欢，可能被 B 喜欢，要求选出的书中，A 与 B 都至少喜欢 $k$ 本，且最少选出 $m$ 本书，求最小权值和。   

相对于 Easy Version，只有一个限定条件的变化：最少选出 $m$ 本书。  

## 解法

依然给书分类：  

0. A 与 B 都不喜欢  
1. B 喜欢  
2. A 喜欢  
3. A 与 B 都喜欢  

考虑强制选定 $m$ 本书对做法产生什么影响。  

设第3种中选出 $i$ 本书，则第1种、第2种中都需要选出 $k - i$ 本书。    

设枚举到 $i$ 时，还需要选出的书本数为 $\text{need}$，更新其值：



1. $i \leq k$ 时，选出了 $i + 2 \times (k - i)$ 本书，即 $k \times 2 - i$ 本书，还需要 $m - k \times 2 + i$ 本书。
2. $i > k$ 时，选出了 $i$ 本书，还需要 $m - i$ 本书。

所需的书在第0种、第1种未被选择部分、第2种未被选择部分选出。  

由于枚举在第3种中选择 $i$ 本书，因此无需考虑在第3种中再次选择。  

考虑选择范围： 

0. 全部可选
1. $[k - i + 1,R]$ 可选
2. $[k - i + 1,R]$ 可选

在该范围内选出 $\text{need}$ 本书，可以维护一个大小为 $\text{need}$ 的set，在加入、弹出元素时更新 $\text{sum}$ 值来维护权值和大小。  

由于枚举 $i$ 单调递增，第1种、第2种中可选范围不断扩大，向set中插入元素进行维护。  

$\text{need}$ 值也会变化，因此可以维护一个可选set以存放可选的元素。   

记选择set为 $\text{choose}$，可选set为 $\text{all}$。  

考虑用 $\text{all}$ 更新 $\text{choose}$ 的过程：  

1. $\operatorname{size}(\text{choose}) > \text{need}$，将其中最大元素转移到 $\text{all}$ 中。
2. $\operatorname{size}(\text{choose}) < \text{need}$，将 $\text{all}$ 中最小元素转移到其中。
3. $\operatorname{size}(\text{choose}) = \text{need}$，比较 $\text{all}$ 中最小元素与 $\text{choose}$ 中最大元素，若 $\text{all}$ 中最小元素更小则进行交换。

由于不能保存取得答案时的状态，则保存取得答案时的 $i$ 值，再次运行到后输出所选书号。  

## 代码

也可以看[官方的代码](https://codeforces.com/blog/entry/79517)。

```cpp
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
template <typename T>
void read(T &r)
{
    static char c; r = 0;
    for (c = getchar(); c > '9' || c < '0'; c = getchar());
    for (; c >= '0' && c <= '9'; r = (r << 1) + (r << 3) + (c ^ 48), c = getchar());
}
const int maxn = 2e5 + 100;
int n, m, k;
struct node
{
    int t, id;
    bool operator<(const node &b) const { return t == b.t ? id < b.id : t < b.t; }
} A[4][maxn];
int num[4];
long long sums[4][maxn];
inline void init()
{
    read(n), read(m), read(k);
    for (int i = 1; i <= n; ++i)
    {
        int t, a, b, p;
        read(t), read(a), read(b), p = a * 2 + b;
        A[p][++num[p]].id = i, A[p][num[p]].t = t;
    }
    for (int i = 0; i < 4; ++i) sort(A[i] + 1, A[i] + 1 + num[i]);
    for (int i = 0; i < 4; ++i)  for (int j = 1; j <= num[i]; ++j) sums[i][j] = sums[i][j - 1] + A[i][j].t;
}
set<node> all, choose;
int sum, need;
inline void updateChoose()
{
    if (need < 0) need = 0;
    set<node>::iterator it;
    while (choose.size() > need) it = --choose.end(), sum -= it->t,all.insert(*it), choose.erase(it);
    while (choose.size() < need && !all.empty()) sum += (it = all.begin())->t,choose.insert(*it), all.erase(it);
    while (!choose.empty() && !all.empty() && (it = --choose.end())->t > all.begin()->t)
    {
        sum -= it->t, sum += all.begin()->t;
        all.insert(*it), choose.erase(it);
        choose.insert(*all.begin()), all.erase(all.begin());
    }
}
inline void updateRange(int i)
{
    if(k - i >= 0)
    {
        need = m - k * 2 + i;
        if(k - i + 1 <= num[1]) all.insert(A[1][k - i + 1]);
        if(k - i + 1 <= num[2]) all.insert(A[2][k - i + 1]);
    }
    else need = m - i;
}
int main()
{
    init();
    int start = 0;
    while (start <= num[3] && (k - start > num[1] || k - start > num[2] || m - start - (k - start) * 2 < 0)) ++start;
    if (start == num[3] + 1) { puts("-1"); return 0; }
    for (int i = 0; i < 3; ++i) for (int j = num[i]; j > (i == 0 ? 0 : k - start); --j) all.insert(A[i][j]);
    long long ans = 1ll << 60;
    int ansp = -1;
    for (int i = start; i <= num[3]; ++i)
    {
        updateRange(i),updateChoose();
        int res = sums[3][i] + sum;
        if (k - i >= 0) res += sums[1][k - i] + sums[2][k - i];
        if (res < ans && ((k - i >= 0) ? (i + 2 * (k - i) + choose.size() == m) : (i + choose.size() == m))) ans = res, ansp = i;
    }
    printf("%lld\n", ans);
    all.clear(), choose.clear();
    for (int i = 0; i < 3; ++i) for (int j = num[i]; j > (i == 0 ? 0 : k - start); --j) all.insert(A[i][j]);
    for (int i = start; i <= num[3]; ++i)
    {
        updateRange(i),updateChoose();
        if (i == ansp)
        {
            for (int j = 1; j <= i; ++j) printf("%d ", A[3][j].id);
            if (k - i > 0) for (int j = 1; j <= k - i; ++j) printf("%d %d ", A[1][j].id, A[2][j].id);
            for (set<node>::iterator it = choose.begin(); it != choose.end(); ++it) printf("%d ", it->id);
            return 0;
        }
    }
    puts("-1");
    return 0;
}
```



---

## 作者：dd_d (赞：1)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/16418812.html)  
思路比较好想但写起来比较阿拉丁，大分讨。
大概是记忆中第一次独立做出 \*2500  
目前是 cf 最优解 rk1
### Sol  
首先把书按时间排序。  
然后我们假定前 $m$ 本书即为答案。考虑一本书一本书换进去。  
现在我们的目标是找到一种合法方案，但不要求时间最优。  
记 $c1$ 表示两者都喜欢的书的数量，$c2$ 为 Alice 喜欢，$c3$ 为 Bob 喜欢，$c4$ 为都不喜欢。  
若当前这本书只有 Alice 喜欢并且 $c1+c2<k,c1+c3>k$ 那么可以把这本书换进去。  
只有 Bob 喜欢同理。  
若当前这本书两者都喜欢，并且 $c1+c2 \ge k,c1+c3<k$ 或 $c1+c2<k,c1+c3 \ge k$，那么可以把这本书换进去。  
是否合法做完了，然后考虑更优的方案。  
若有一种只有一个人喜欢的多了，那么可以考虑用一本两人都不喜欢的书放进去看看是否更优。  
一本两人都喜欢的和一本两人都不喜欢的可以替换一本 Alice 喜欢的和一本 Bob 喜欢的。  
然后大力分讨即可。情况有点多，我 WA 了 $6$ 发。
[link](https://codeforces.com/contest/1374/submission/162004504 "link")

---

## 作者：zhimao (赞：1)

我们把书分成4类 。

- $a_i=b_i=1$ 记为 A
- $a_i=1,b_i=0$ 记为 B
- $a_i=0,b_i=1$ 记为 C
- $a_i=b_i=0$ 记为 D

显然有一个贪心做法是对每类按 $t_i$ 从小到大排序 ，枚举 A 的数量 $x$ ，则 B,C 的数量为 $k-x$ ，然后从剩下所有书中选 $m-k-k+x$ 本 。复杂度 $O(n\log n+m^2)$ 。

我们考虑加一本 A 类书对答案的影响 ，加一本 A 的费用（单调不减），减一本 B 类书的费用（单调不增），减一本 C 类书的费用（单调不增），加一本剩下书中的费用 ，这本书要么是减下来的 B 或 C 类书 ，要么是 原先剩下书中费用最小的（单调不减），因此它对答案贡献会逐渐减小（可能依然不严谨 ，但大致就是这样） ，因此它是个单峰函数 ，可以三分 。

代码
```cpp
#include<bits/stdc++.h>
#define inf 10000000000001
#define int long long
using namespace std;
int n,m,k,ans=inf,p[1000000],m1,m2,m3,m4;
struct arr
{
	int x,y;
}a[200005],b[200005],c[200005],d[200005];
bool cmp(arr x,arr y)
{
	return x.x<y.x;
}
int check(int x)
{
	if(x<0||x>m1) return inf;
	if(k+k-x>m) return inf;
	if(k-x>m2) return inf;
	if(k-x>m3) return inf;
	int p1=1,p2=1,p3=1,p4=1,s=0;
	for(;p1<=x;p1++) s+=a[p1].x;
	for(;p2<=k-x;p2++) s+=b[p2].x;
	for(;p3<=k-x;p3++) s+=c[p3].x;
	while(p1+p2+p3+p4-4<m)
	{
		if(a[p1].x<=b[p2].x&&a[p1].x<=c[p3].x&&a[p1].x<=d[p4].x) s+=a[p1++].x;
		else
		{
			if(b[p2].x<=c[p3].x&&b[p2].x<=d[p4].x) s+=b[p2++].x;
			else
			{
				if(c[p3].x<=d[p4].x) s+=c[p3++].x; else s+=d[p4++].x;
			}
		}
	}
	if(s>=ans) return s;
	ans=s;
	for(int i=1;i<p1;i++) p[i]=a[i].y;
	for(int i=1;i<p2;i++) p[i+p1-1]=b[i].y;
	for(int i=1;i<p3;i++) p[i+p1+p2-2]=c[i].y;
	for(int i=1;i<p4;i++) p[i+p1+p2+p3-3]=d[i].y;
	return s;
}
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		int x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		if(y&z) a[++m1]={x,i};
		else
		{
			if(y) b[++m2]={x,i};
			else
			{
				if(z) c[++m3]={x,i}; else  d[++m4]={x,i};	
			}
		}
	}
	a[++m1]={inf,0};
	b[++m2]={inf,0};
	c[++m3]={inf,0};
	d[++m4]={inf,0};
	sort(a+1,a+m1+1,cmp);
	sort(b+1,b+m2+1,cmp);
	sort(c+1,c+m3+1,cmp);
	sort(d+1,d+m4+1,cmp);
	int l=0,r=m1,mid=(l+r)>>1;
	while(l<=r)
	{
		int t1=check(mid-1),t2=check(mid),t3=check(mid+1);
		if(t1>t2&&t2<t3) break;
		if(t1>t2||(t1==t2&&t1==inf)) l=mid+2; else r=mid-2;
		mid=(l+r)>>1;
	}
	if(ans==inf)
	{
		puts("-1");
		return 0;
	}
	printf("%lld\n",ans);
	for(int i=1;i<=m;i++) printf("%lld ",p[i]);
	return 0;
}
```


---

## 作者：CQ_Bab (赞：0)

# 前言
这个蒟蒻用 E1 的方法做这道题成功一直挂在 $12$ 上而换了一种做法马上就过了，后面发现题解并无此做法就来~~水一篇~~啦。
# 思路
我们发现对于 $1,1$ 的情况如果确定了那么 $0,1$ 和 $1,0$ 的数量就都确定了所以可以考虑枚举 $1,1$ 的数量为 $i$ 所以 $0,1$ 与 $1,0$ 的数量就是 $k-i$ 个，那么我们可以算出总的数量 $i+(k-i)\times 2=2\times k-i$ 以此来算出还需要选的数量然后就直接在剩下的东西中选那么多个最小的即可。现在便得出了一种 $n^2$ 的做法，考虑优化。

我们发现对于 $1,1$ 和 $0,1$ 还有 $1,0$ 的情况一定只会选其最优的 $x$ 个那么随着 $i$ 的增大我们发现最后剩的 $1,1$ 越来越少而 $0,1$ 和 $1,0$ 会越来越多，所以考虑维护一棵权值线段树在每一次操作后最多只会变 $3$ 个数所以只需要在线段树上修改即可，最终也就转化为了求全局前 $k$ 小的问题了，这个不难解决。

注意判一下边界就行了。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int bufsize = 230005;
char buf[bufsize], *f1, *f2;
#define getchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
int n;
const int N=2e5+10;
set<pair<int,int>>q_q,q11,q12;
int k;
set<int>v;
struct node{
	int t,a,b;
}s[N];
int m;
int sum[N],sum1[N],sum2[N];
int a[N],a1[N],a2[N];
struct nodes{
	int l,r;
	int cnt,sum;
}tr[N<<2];
void up(int x) {
	tr[x].cnt=tr[x<<1].cnt+tr[x<<1|1].cnt;
	tr[x].sum=tr[x<<1].sum+tr[x<<1|1].sum;
}
void build(int u,int l,int r) {
	tr[u]={l,r};
	if(l==r) return ;
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
}
void modify(int u,int x,int k) {
	if(tr[u].l==tr[u].r) {
		tr[u].cnt+=k;
		tr[u].sum+=k*tr[u].l;
		return ;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(mid>=x) modify(u<<1,x,k);
	else modify(u<<1|1,x,k);
	up(u);
}
int Ans(int x,int k) {
	if(tr[x].l==tr[x].r) {
		return tr[x].l*k;
	}
	int mid=tr[x].l+tr[x].r>>1,res=0;
	if(tr[x<<1].cnt>=k)  return Ans(x<<1,k);
	return Ans(x<<1|1,k-tr[x<<1].cnt)+tr[x<<1].sum;
}
void solve() {
	in(n),in(m),in(k);
	build(1,0,10000);
	int ff=0;
	rep(i,1,n) {
		int t,a,b;
		in(t),in(a),in(b);
		s[i]={t,a,b};
		if(a&&b) {
			q_q.insert({t,i});
		}else if(a) q11.insert({t,i});
		else if(b) q12.insert({t,i});
		else modify(1,t,1);
	}
	int cnt=false;
	for(auto to:q_q) {
		cnt++;
		sum[cnt]=sum[cnt-1]+to.first;
		a[cnt]=to.first;
	}
	int cc=cnt;
	rep(i,1,cnt) modify(1,a[i],1);
	cnt=false;
	for(auto to:q11) {
		cnt++;
		sum1[cnt]=sum1[cnt-1]+to.first;
		a1[cnt]=to.first;
	}
	int ll=cnt;
	cnt=false;
	for(auto to:q12) {
		cnt++;
		sum2[cnt]=sum2[cnt-1]+to.first;
		a2[cnt]=to.first;
	}
	int l1=cnt;
	int res=INT_MAX,id=false;
	rep(i,k+1,ll) modify(1,a1[i],1);
	rep(i,k+1,l1) modify(1,a2[i],1);
	rep(i,0,min(k,cc)) {
		int dis=false;
		dis=sum[i];
		int kk=k-i;
		if(i!=0) modify(1,a[i],-1);
		if(kk>l1||kk>ll) {
			if(kk<=ll&&kk!=0) modify(1,a1[kk],1);
			if(kk<=l1&&kk!=0) modify(1,a2[kk],1);
			continue;
		}
		if(kk>=1) dis+=sum1[kk];
		if(kk>=1) dis+=sum2[kk];
		if(max(0ll,kk)*2+i>m) {
			if(kk<=ll&&kk!=0) modify(1,a1[kk],1);
			if(kk<=l1&&kk!=0) modify(1,a2[kk],1);
			continue;
		}
		if(m-max(0ll,kk)*2-i>=1) {
			if(tr[1].cnt>=m-max(0ll,kk)*2-i) dis+=Ans(1,m-max(0ll,kk)*2-i);
			else dis=INT_MAX;
		}
		if(kk<=ll&&kk!=0) modify(1,a1[kk],1);
		if(kk<=l1&&kk!=0) modify(1,a2[kk],1);
		if(dis<res) {
			res=dis;
			id=i;
		}
	}
	if(res==INT_MAX) puts("-1");
	else {
		cout<<res<<endl;
		int kk=k-id;
		int yu=m-id;
		auto it=q_q.begin();
		while(id) {
			id--;
			v.insert(it->second);
			it++;
		}
		int k_k=kk;
		yu-=kk*2;
		it=q11.begin();
		while(kk) {
			kk--;
			v.insert(it->second);
			it++;
		}
		kk=k_k;
		it=q12.begin();
		while(kk) {
			kk--;
			v.insert(it->second);
			it++;
		}
		set<pair<int,int>>se;
		rep(i,1,n) {
			if(v.find(i)==v.end()) se.insert({s[i].t,i});
		}
		it=se.begin();
		while(yu) {
			v.insert(it->second);
			it++;
			yu--;
		}
		for(auto to:v) cout<<to<<' ';
	}
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：shuangmu (赞：0)

# CF1374E2  Reading Books(hard version)

[广告](https://www.cnblogs.com/frostwood/p/17684907.html)

这道题是在 [CF1374E1 Reading Books(easy version)](https://www.luogu.com.cn/problem/CF1374E1) 的基础上出的，而且仅仅增加了一个 $m$ 的限制，下面的做法也是基于简单版的思路而想到的。建议先尝试简单版，然后尝试此题。

## 题意简述：

有 $n$ 本书，每本书有一个阅读时间 $t_i$，和属性 $a_i$、$b_i$，代表是否被 Alice 和 Bob 喜欢。要求两人**恰好读 $m$ 本书**，其中必须有至少 $k$ 本被 Alice 喜欢，至少 $k$ 本被 Bob 喜欢，求最小的总阅读时间，并输出读书方案。总阅读时间为这 $m$ 本书的时间和。

## 思路：

### 简单版

先不考虑 $m$。我们可以把书分为四类：被 Alice 喜欢，被 Bob 喜欢，两人都喜欢，两人都不喜欢。我们设这四类分别为 $a$、$b$、$ab$、$none$。显然，两人都不喜欢的书没必要去选，满足了 $k$ 的限制后，也没必要去多选书。因此，问题转换为了要选多少 $ab$ 与 $a$、$b$。每多选一本 $ab$ 就可以少选一本 $a$ 和和一本 $b$，所以我们可以枚举选 $i$ 本 $ab$，那么 $a$ 和 $b$ 的数量就是 $k-i$。我们只需要知道阅读时间前 $i$ 小的 $ab$ 的阅读时间和以及前 $k-i$ 小的 $a$ 和 $b$ 的阅读时间和即可。这三类书的选择相互独立，因此可以分别排序，求前缀和即可。

### 困难版

和简单版唯一的不同在于，简单版可以读任意数量的书，而困难版必须读 $m$ 本。也就是说，如果已经满足了 $k$ 的限制后，读的书数量不够多，必须从未选择的书中再选出几本。

我们来分析一下刚才过程中，未选择的书有哪些。还是设选择 $i$ 本 $ab$，设 $ab$、$a$、$b$、$none$ 四种书的总数为 $totab$、$tota$、$totb$、$totn$。

- $ab$ 中有 $totab - i$ 本未被选择；
- $a$ 中有 $tota - k + i$ 本书未被选择；
- $b$ 中有 $totb - k + i$ 本书未被选择；
- $none$ 中的我们都没有选。

我们设没有选的书的集合为 $S$，那么我们只需要找到 $S$ 中阅读时间前 $m-k*2+i$ 小的书的阅读时间和。这个可以用平衡树做。

我们来理一下这个过程。首先从小到大枚举选 $i$ 本 $ab$，然后维护 $S$ 内的元素，计算答案，如果答案可以更新，则记录一下得到答案时 $i$ 是多少（因为还要输出方案）。

至于输出方案，首先 $ab$、$a$、$b$ 都好处理，从小到大输出即可；对于 $S$ 中我们选择的元素，可以先恢复 $S$ 在得到答案的 $i$ 时的状态，然后把得到答案的那部分输出出来即可。

总时间复杂度 $O(n \log n)$。细节见代码注释。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5+100;

inline int read(){
	int x = 0; char ch = getchar();
	while(ch<'0' || ch>'9') ch = getchar();
	while(ch>='0'&&ch<='9') x = x*10+ch-48, ch = getchar();
	return x;
}

struct xwx {
	ll val;
	int id;int v;
	bool operator < (const xwx &b ) const{
		return val < b.val;
	}
};// 用来存储 a、b、ab、none 中的书
struct qwq{
	int v, id;
	bool operator <(const qwq &b) const{
		if(v == b.v){
			return id < b.id;
		}
		return v < b.v;
	}
	bool operator >(const qwq &b) const{
		if(v == b.v){
			return id > b.id;
		}
		return v >b.v;
	}
};//作为 FHQ 上元素的权值，重载运算符便于删除操作。
xwx a[N], b[N], ab[N], no[N];//A喜欢，B喜欢，都喜欢，都不喜欢。

struct node{
	qwq val;
	ll sum;//sum 记录子树内的权值和。
	int siz;
	int ls, rs;
	int rnd;
};
int root;
mt19937 getrand(time(0));
struct FHQ_Treap{
	node tree[N];
	int idx;
	#define ls(x) tree[x].ls
	#define rs(x) tree[x].rs
	void push_up(int tr){
		tree[tr].sum = tree[ls(tr)].sum+tree[rs(tr)].sum+tree[tr].val.v;
		tree[tr].siz = tree[ls(tr)].siz+tree[rs(tr)].siz+1;
	}
	int New(qwq val){
		tree[++idx] = (node){val, val.v, 1, 0, 0, (int)getrand()};
		return idx;
	}
	void split_by_size(int pos, int &l, int &r, int K){//按大小分裂，也就是取出前 K 小的元素
		if(!pos) return l = r = 0, void();
		int tmp = tree[ls(pos)].siz+1;
		if(K>=tmp){
			l = pos;
			split_by_size(rs(pos), rs(pos), r, K-tmp);
			push_up(l);
		} else{
			r = pos;
			split_by_size(ls(pos), l, ls(pos), K);
			push_up(r);
		}
	}
	void split_by_val(int pos, int &l, int &r, qwq K){//按权值大小分裂，主要用于插入元素。
		if(!pos) return l = r = 0, void();
		if(K>tree[pos].val){
			l = pos;
			split_by_val(rs(pos), rs(pos), r, K);
			push_up(l);
		} else{
			r = pos;
			split_by_val(ls(pos), l, ls(pos), K);
			push_up(r);
		}
	}
	int merge(int l, int r) {
		if((!l) || (!r)) return l | r;
		if(tree[l].rnd < tree[r].rnd){
			rs(l) = merge(rs(l), r);
			push_up(l);
			return l;
		} else{
			ls(r) = merge(l, ls(r));
			push_up(r);
			return r;
		}
	}
	void insert(int val, int id){
		int dl, dr;
		split_by_val(root, dl, dr, (qwq){val, id});
		root = merge(merge(dl, New((qwq){val, id})), dr);
	}
	void del(int val, int id){
		int dl, md, dr;
		split_by_val(root, dl, dr, (qwq){val, id});
		split_by_val(dr, md, dr, (qwq){val, id+1});//将目标节点分裂出来，合并两边。
		root = merge(dl, dr);
	}
	ll query(int K){
		int dl, dr;
		split_by_size(root, dl, dr, K);//分裂出前 K 小的元素。
		ll tmp = tree[dl].sum;
		root = merge(dl,dr);
		return tmp;
	}
	void clear(){
		root = 0;
		idx = 0;
		memset(tree, 0, sizeof(tree));
	}
	void output(int pos){
		if(ls(pos)){
			output(ls(pos));
		}
		printf("%d ", tree[pos].val.id);
		if(rs(pos)){
			output(rs(pos));
		}
	}//遍历子树，输出方案
	void print(int K){
		int dl,dr;
		split_by_size(root, dl, dr, K);
		if(dl) output(dl);
	}
}s;
int ta, tb, tab, tn;
int n, m, K;
int main(){
	n = read(), m = read(), K = read();
	for(int i = 1, ar, br, t; i<=n; ++i){
		t = read(), ar = read(), br = read();
		if(ar && br){
			ab[++tab] = (xwx){t, i, t};
			s.insert(t, i);
		} else if(ar){
			a[++ta] = (xwx){t, i, t};
		} else if(br){
			b[++tb] = (xwx){t, i, t};
		} else{
			no[++tn] = (xwx){t, i, t};
			s.insert(t, i);//没人喜欢的直接插入到 S 里
		}
	}
	sort(a+1, a+ta+1);
	sort(b+1, b+tb+1);
	sort(ab+1, ab+tab+1);
	// sort(no+1, no+tn+1);
	for(int i = 1; i<=ta; ++i){
		a[i].val+=a[i-1].val;
	}
	for(int i = 1; i<=tb; ++i){
		b[i].val+=b[i-1].val;
	}
	for(int i = 1; i<=tab; ++i){
		ab[i].val+=ab[i-1].val;
	}
	// 求前缀和。
	ll ans = 0x3f3f3f3f3f3f3f3f;
	int num = -1;//记录答案在哪里产生
	int tota = ta, totb = tb, totab = tab;
	for(int i = 0; i<=min(K, tab); ++i){
		if(i > 0){
			s.del(ab[i].v, ab[i].id);
		}//枚举到的 ab 必须要选，所以就从 S 中删除。
		if((K-i)>ta || (K-i)>tb || K*2-i > m) continue;

		while(ta > (K-i)){
			s.insert(a[ta].v, a[ta].id);
			--ta;
		}
		while(tb > (K-i)){
			s.insert(b[tb].v, b[tb].id);
			--tb;
		}//将选不上的 a 和 b 都加入 S

		ll tmp = ab[i].val + a[ta].val + b[tb].val + s.query(m-K*2+i);
		if(ans > tmp){
			num = i;
			ans = tmp;
		}
	}
	if(ans == 0x3f3f3f3f3f3f3f3f){
		puts("-1");
		return 0;
	}
	printf("%lld\n", ans);
	s.clear();
	for(int i = num+1; i<=totab; ++i){
		s.insert(ab[i].v, ab[i].id);
	}
	for(int i = (K-num+1); i<=tota; ++i){
		s.insert(a[i].v, a[i].id);
	}
	for(int i = (K-num+1); i<=totb; ++i){
		s.insert(b[i].v, b[i].id);
	}
	for(int i = 1; i<=tn; ++i){
		s.insert(no[i].v, no[i].id);
	}//将 S 恢复到 i = num 时的状态

	for(int i = 1; i<=num; ++i){
		printf("%d ", ab[i].id);
	}
	for(int i = 1; i<=K-num; ++i){
		printf("%d ", a[i].id);
	}
	for(int i = 1; i<=K-num; ++i){
		printf("%d ", b[i].id);
	}//顺序输出 ab、a、b
	s.print(m-K*2+num);//输出 S 中选择的元素。
	return 0;
}
```



---

