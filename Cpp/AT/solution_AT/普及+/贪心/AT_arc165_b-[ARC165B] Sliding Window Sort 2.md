# [ARC165B] Sliding Window Sort 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc165/tasks/arc165_b

$ 1 $ から $ N $ までの整数からなる順列 $ P=(P_1,P_2,\dots,P_N) $ と整数 $ K $ が与えられます。

順列 $ P $ に対して以下のような操作を考えます。

- $ 1\ \leq\ i\ \leq\ N-K+1 $ を満たす整数 $ i $ を $ 1 $ つ選び、 $ P_i,P_{i+1},\dots,P_{i+K-1} $ を昇順に並び替える。すなわち、$ P_i,P_{i+1},\dots,P_{i+K-1} $ を小さい方から順に並べたものを $ (x_1,x_2,\dots,x_K) $ としたとき、各 $ 1\ \leq\ j\ \leq\ K $ に対して $ P_{i+j-1} $ を $ x_j $ で置き換える。
 
$ P $ に対して上記の操作をちょうど $ 1 $ 回行うことで得られる順列のうち、辞書式順序最大のものを求めてください。

  数列の辞書順とは？数列 $ S\ =\ (S_1,S_2,\ldots,S_{|S|}) $ が数列 $ T\ =\ (T_1,T_2,\ldots,T_{|T|}) $ より**辞書順で小さい**とは、下記の 1. と 2. のどちらかが成り立つことを言います。 ここで、$ |S|,\ |T| $ はそれぞれ $ S,\ T $ の長さを表します。

1. $ |S|\ \lt\ |T| $ かつ $ (S_1,S_2,\ldots,S_{|S|})\ =\ (T_1,T_2,\ldots,T_{|S|}) $。
2. ある整数 $ 1\ \leq\ i\ \leq\ \min\lbrace\ |S|,\ |T|\ \rbrace $ が存在して、下記の $ 2 $ つがともに成り立つ。 
  - $ (S_1,S_2,\ldots,S_{i-1})\ =\ (T_1,T_2,\ldots,T_{i-1}) $
  - $ S_i $ が $ T_i $ より（数として）小さい。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ P_i\ \leq\ N $
- $ (P_1,P_2,\dots,P_N) $ は $ 1 $ から $ N $ までの整数からなる順列
- 入力される値はすべて整数
 
### Sample Explanation 1

$ i=1 $ として操作を行うと $ (P_1,P_2,P_3)=(2,1,4) $ であり、これを昇順に並び替えると $ (1,2,4) $ となります。よって操作によって $ P_1,P_2,P_3 $ はそれぞれ $ 1,2,4 $ に置き換えられ、 $ P=(1,2,4,3) $ となります。同様に $ i=2 $ として操作を行うと $ P $ は $ (2,1,3,4) $ となります。 これらのうち辞書式順序で大きいのは $ (2,1,3,4) $ であるため、答えは $ (2,1,3,4) $ となります。

## 样例 #1

### 输入

```
4 3
2 1 4 3```

### 输出

```
2 1 3 4```

## 样例 #2

### 输入

```
5 1
3 1 4 2 5```

### 输出

```
3 1 4 2 5```

## 样例 #3

### 输入

```
20 7
9 4 3 1 11 12 13 15 17 7 2 5 6 20 19 18 8 16 14 10```

### 输出

```
9 4 3 1 11 12 13 15 17 7 2 5 6 8 18 19 20 16 14 10```

# 题解

## 作者：EuphoricStar (赞：4)

悲，赛时代码赛后被 hack 了。

发现对子段排序不会使排列的字典序变大。因此若存在长度 $\ge k$ 的递增子段直接输出原排列。

否则答案与原排列的 $\text{LCP}$ 至少为 $n - k$（可以通过对 $[n - k + 1, n]$ 排序达到）。我们想在不影响前 $n - k$ 个数的顺序的前提下，最小化后面的数。

找出以 $n - k$ 为右端点的最长递增子段，设其为 $[o, n - k]$。则对于 $l \in [o, n - k]$，若 $p_{n - k} < \min\limits_{i = n - k + 1}^{l + k - 1} p_i$，就说明对 $[l, l + k - 1]$ 排序不会影响前 $n - k$ 个数。对于所有这样的 $l$，若 $l_1 < l_2$，则对 $[l_1, l_1 + k - 1]$ 排序一定不劣于对 $[l_2, l_2 + k - 1]$ 排序。因为进入子段的数越少，排序结果不会变劣。

于是找出最小的 $l$，对 $[l, l + k - 1]$ 排序即可。

若预处理以 $n - k + 1$ 为左端点的区间最小值，使用计数排序等排序算法做到 $O(n)$ 排序，时间复杂度就是 $O(n)$。

[code](https://atcoder.jp/contests/arc165/submissions/45712036)

---

## 作者：樱雪喵 (赞：3)

被题目名里的滑动窗口误导了，于是卡 B 40min /fn

## Description

给定长度为 $n$ 的排列 $P$ 和一个整数 $K$。一次操作定义为选择一个长度为 $K$ 的区间，对原排列的这段区间升序排序，其余位置不变。

你要执行操作恰好一次，求能得到的字典序最大的排列。

$1\le K \le N\le 2\times 10^5$。

## Solution 1

题解做法。

观察到由于操作是升序排列，操作之后不会使排列的字典序变得比原来更大。那么如果存在某种操作方式使得这个区间不变，这样做一定是最优的。这种情况等价于找一个长度为 $K$ 的单调递增区间，而这是容易判断的。

考虑不存在上述区间的情况，即无论如何操作都会使排列的字典序变小。我们显然更希望操作后值被改变的第一个位置尽可能靠右。设这个位置的下标为 $x$。

可以发现，当选择区间 $[n-K+1,K]$ 时，$x$ 可以取得下界 $n-K+1$。也就是说，如果一个操作改变了 $n-K+1$ 左侧的位置，这个操作不如最后一个区间优，它一定不是答案。但直接操作最后一个区间并不一定是最优的。如果最后一个区间后面的部分有一些很小的数，把操作区间左移避开它们或许更优。

将操作区间左移至 $[L,R]$，要使答案不变劣，应当保证 $n-K+1$ 前面的部分都不变，即 $[L,n-K]$ 的值单调递增且均小于后面。在满足条件的情况下，显然 $L$ 变小答案不会变劣，因此我们只需找到最小满足条件的 $L$。

对于“全部小于后面”的条件，因为单调递增，只需满足 $P_{n-K}$ 小于后面的最小值，可以得出 $L$ 的上界。而通过“单调递增”的条件可以得出 $L$ 的下界，我们在 $L$ 存在（上界不小于下界）的情况下取最小的 $L$，不存在就取 $n-K+1$ 作为区间左端点进行操作即可。

## Solution 2

这人被题目名误导弄出来的赛时做法，给大家看个乐子。

我们希望第一个被改变的位置尽可能靠后。因此，类似于滑动窗口，从左到右枚举操作区间，用 `set` 维护当前区间排序后的结果。然后我们一位一位把 `set` 里的值和原序列匹配，找到第一个被改变的位置和它被改成的值，更新答案。

这样做时间复杂度不对，但是我们发现：如果 $[L,R]$ 有一段前缀排序后不动，那 $[L+1,R+1]$ 的这段前缀（长度减了 $1$）排序后要么还是这段不动，要么后面来了个很小的数让不动的区间变短了。总之不会让不动的位置更靠后。

所以每次匹配完把不动的前缀跳过去不枚举即可，一共匹配了 $n$ 次，时间复杂度 $O(n\log n)$。

代码是 Solution 2。

```cpp
const int N=2e5+5,inf=1e9;
int n,k;
int a[N],flag[N];
int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++) a[i]=read();
    set<int> s;
    for(int i=1;i<=k;i++) s.insert(a[i]);
    int mx=0,ans=0;
    for(int st=1;st<=n-k+1;st++)
    {
        if(st!=1) s.insert(a[st+k-1]),s.erase(a[st-1]);
        if(flag[st]) continue;
        auto it=s.begin(); int len=0;
        for(int j=st;j<=st+k-1;j++)
        {
            if((*it)!=a[j]) {len=j;break;}
            it++;
        }
        if(!len) mx=inf,ans=st;
        for(int i=st+1;i<=len;i++) flag[i]=1;
        if(len>mx) mx=len,ans=st;
    }
    sort(a+ans,a+ans+k);
    for(int i=1;i<=n;i++) printf("%d ",a[i]);
    printf("\n");
    return 0;
}
```

---

## 作者：fangzichang (赞：3)

场上吃了九发。  

---  

[题目链接](https://www.luogu.com.cn/problem/AT_arc165_b)，简要题意：给一个长度 $n$ 的排列，你需要对其中一个长度为 $k$ 的区间排序，使得排序后的字典序尽量大。输出排序后字典序最大的排列。  

---

数据很水，各种奇怪解法都能过，这里给一种应该是正确的解法。  
考虑在 $[1,n-k+1]$ 范围内枚举所有可能作为排序区间起点的位置，假设排序这个区间会产生什么变化。  
然后容易发现第一个发生变化的位置会变成什么值最为关键。  
设这个区间为 $[l,r]$。  
可以发现，排序后**第一个和原来不同**的位置，和这个位置会变成什么值，一定可以通过如下方法找出：  
1. 求出区间内最长的一段升序前缀 $[l,pos]$。  
2. 特判，若 $pos=r$，则对该区间排序不会产生变化，直接输出原序列并退出。  
3. 求出不在该升序前缀内（或者说在区间 $[pos+1,r]$ 内）的最小值 $val$。  
4. 求出排序后 $val$ 将会插入到升序前缀的位置 $p$，那么 $p$ 即为排序后第一个不同的位置，并且必然会变成 $val$。  

考虑证明这个结论：
1. 假设还存在比 $p$ 更靠前的并且改变了的位置，那么这个位置的值必然小于 $val$，然后由 $val$ 是“不在该升序前缀内的最小值”得出这个值必定在升序前缀内，并且必定在 $p$ 之前，然后容易发现它排序后必定不变。  
2. 假设 $p$ 排序后会变成比 $val$ 更小的值，和上面类似容易证明，不再赘述。  

求升序前缀、求 $p$ 均可以使用二分，求 $val$ 可以用 st 表。  
顺便，场上我突然不会求升序前缀，只能相邻作差之后用 st 表求区间最小值判定，还要套一个二分，脑瘫了。  
然后就这样把所有可能的排序区间抽象成三个值 $\{l,p,val\}$，表示区间左端点、排序后第一个有改变的位置和这个位置会改变成的值。  
考虑选哪个会优。  

可以发现，显然 $p$ 越靠后越优，因为位置 $p$ 变成 $val$ 后由于是排序后，字典序必定会比原来小。  
在此基础上，$p$ 相同时 $val$ 越大越优。显然。  
然后发现 $p$ 和 $val$ 都相同时 $l$ 越小越优。  
这个可能有点难想到，证明一下。  
假设两个可能的排序区间 $[l,r]$ 和 $[l',r'](l'>l)$，排序后区间内第一个改变的位置均为 $p$，且 $p$ 这个位置均变为 $val$，那么可以看作两个区间剩余部分 $(p,r]$ 和 $(p,r']$ 分别排序之后比较字典序大小。  
然后发现 $(p,r]$ 内有的值 $(p,r']$ 内显然都有，那么显然排序后 $(p,r]$ 的字典序必定不小于 $(p,r']$。  
然后就好做了。  
总时间复杂度 $O(n\log n)$，瓶颈在二分求 $p$。  
[提交记录](https://atcoder.jp/contests/arc165/submissions/45682564)，写代码的时候不太清醒，不要在意。  

upd：一车乱搞被加的几组数据卡掉了，但是我没有被卡掉。  

---

## 作者：lzyqwq (赞：2)

**[AT](https://atcoder.jp/contests/arc165/tasks/arc165_b "AT")**

**[洛谷](https://www.luogu.com.cn/problem/AT_arc165_b "洛谷")**

> - 给出长度为 $N$ 的整数排列 $P_1\sim P_N$，**必须**选择一个长度为 $K$ 的区间，将区间内的数**升序**排序。求最后可以得到的**最大**字典序。
>
> - $K\le N\le 2\times 10^5$。

我们发现，进行一次排序后排列的字典序**不增**。若排列中存在长度不低于 $K$ 的上升子序列，则答案为原排列。

否则，我们肯定希望一段最长的前缀字典序不变，然后剩下的部分字典序变小。这么看似乎就是选择 $[N-K+1,N]$ 这个区间排序，保证了最长的前缀 $P_1\sim P_{N-K}$ 不变。

实则不然，选择其它的区间排序也可以使得这段前缀的字典序不变，如这组数据：

```cpp
5 3
5 1 4 3 2
```

我们若选择 $P_3\sim P_5$ 这个区间，则得到排列为 $\{5,1,2,3,4\}$，而若选择 $P_2\sim P_4$ 这个区间，得到的排列为 $\{5,1,3,4,2\}$，更优。

因此还有考虑怎样的左端点 $l\,(1\le l\le N-K)$ 能够满足这个性质。首先 $P_l\sim P_{N-K}$ 必须是一个递增的序列，否则排序会将这个区间变成递增序列，字典序变小。这一步从 $N-K$ 这个位置往左扫即可。

其次，需要满足 $\min\limits_{i=N-K+1}^{l+K-1}>P_{N-K}$，不然 $P_{N-K+1}\sim P_{l+K-1}$ 中的某些数就会被排到 $N-K$ 这个位置及以前，使得 $P_1\sim P_{N-K}$ 这个前缀的字典序变小。这一步维护一下以 $N-K+1$ 为起点的前缀最小值（代码中的 $pre$ 数组）即可。

假设有若干个位置满足这个条件，我们一定选择最左边的那个，可以来看一张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hk0v35qp.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

选择 $l_1$ 或 $l_2$，$P_1\sim P_{N-K}$ 以及 $P_{l_2+K}\sim P_{N}$ 的顺序都不会发生改变，而对于 $P_{N-K+1}\sim P_{l_2+k-1}$，选择 $l_2$ 会将这个区间进行升序排序，这样一来这个区间的字典序一定是所有重排方式中最小的，显然将 $P_{N-K+1}\sim P_{l_1+K-1}$ 排序，不动 $P_{l_1+K}\sim P_{l_2+K-1}$ 也是一种重排方式，选择 $l_1$ 时其它部分字典序不变，$P_{N-K+1}\sim P_{l_2+K-1}$ 的字典序不会更小，因此选择 $l_1$ 更优。

若能找到这样的左端点 $l$，就对 $P_{l}\sim P_{l+K-1}$ 进行排序，否则对 $P_{N-K+1}\sim P_N$ 进行排序。

时间复杂度为 $\mathcal{O}(K\log N+N)$，空间复杂度为 $\mathcal{O}(N)$。

**[评测记录](https://atcoder.jp/contests/arc165/submissions/45732438 "评测记录")**

```cpp
#include <bits/stdc++.h>
using namespace std; const int N = 2e5 + 5; 
int n, k, a[N], maxn, pos = 1, lg[N], ans, pre[N];
template<class T> void read(T &x) {
    x = 0; T f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -1;
    for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - 48; x *= f;
}
template<class T> void write(T x) {
    if (x > 9) write(x / 10); putchar(x % 10 + 48);
}
template<class T> void print(T x, char ed = '\n') {
    if (x < 0) putchar('-'), x = -x; write(x), putchar(ed);
}
signed main() {
    read(n), read(k); for (int i = 1; i <= n; ++i) read(a[i]), lg[i] = __lg(i);
    for (int i = 1, la, len = 0; i <= n; ++i) {
        if (i == 1 || a[i] > la) ++len; else maxn = max(len, maxn), len = 1;
        la = a[i];
    }
    if (maxn >= k) { for (int i = 1; i <= n; ++i) print(a[i], ' '); return 0; }
    for (int i = n - k, la = N; i >= 1; --i) 
        if (a[i] > la) { pos = i + 1; break; } else la = a[i];
    pre[n - k + 1] = a[ans = n - k + 1];
    for (int i = n - k + 2; i <= n; ++i) pre[i] = min(pre[i - 1], a[i]);
    for (int i = pos; i <= n - k; ++i) 
        if (pre[i + k - 1] > a[n - k]) { ans = i; break; }
    sort(a + ans, a + ans + k); for (int i = 1; i <= n; ++i) print(a[i], ' ');
    return 0;
}
```

---

## 作者：stswkl (赞：0)

## 题意
给你一个长为 $N$ 的排列 $P$ 和一个整数 $K$，定义一次操作为把 $P_i,P_{i+1},\dots,P_{i+K-1}$ 从小到大排序一次，要求恰好操作一次后字典序最大的排列。

## 思路
设该操作选中的区间为 $[i,i+k-1]$，则有如下结论：
- 若区间中的数单调递增，则排序后的区间不变，此时答案即为原排列。
- 否则在排序之后排列的字典序必然变小，设 $x$ 为排列第一个与原来不同的位置，显然我们是希望这个 $x$ 越大越好的。假设当前区间的子区间 $[i,j]$ 单调递增，我们可以求出区间 $[j+1,i+k-1]$ 中的最小值，在排序之后这个最小值一定会去到前面，它排序后的位置就是 $x$。于是我们可以用二分在 $[i,j]$ 中查找该值插入后的位置，即求出了 $x$。

二分和线段树维护区间最小的时间复杂度均为 $O(\log N)$，故总的时间复杂度为 $O(N\log N)$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,inf=1e9+5;
class segment_tre
{
    private:
        int minn[N<<2];
        void push_up(int id){minn[id]=min(minn[id<<1],minn[id<<1|1]);}
    public:
        void build(int id,int l,int r,int*a)
        {
            if(l==r)minn[id]=a[l];
            else
            {
                int mid=l+r>>1;
                build(id<<1,l,mid,a);
                build(id<<1|1,mid+1,r,a);
                push_up(id);
            }
        }
        int query(int id,int l,int r,int x,int y)
        {
            if(x<=l&&r<=y)return minn[id];
            int mid=l+r>>1,res=inf;
            if(x<=mid)res=min(res,query(id<<1,l,mid,x,y));
            if(y>mid)res=min(res,query(id<<1|1,mid+1,r,x,y));
            return res;
        }
}tree;
int a[N],id[N],r[N];
int find(int L,int R,int val)
{
    int l=L-1,r=R+1;
    while(l+1<r)
    {
        int mid=l+r>>1;
        if(a[mid]<val)l=mid;
        else r=mid;
    }
    return r;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    tree.build(1,1,n,a);
    int tot=1;
    for(int i=1;i<=n;i++)
    {
        if(a[i-1]>a[i])tot++;
        id[i]=tot;
        r[tot]=i;
    }
    int maxn=0,minx;
    for(int i=1;i+k-1<=n;i++)
    {
        if(r[id[i]]>=i+k-1)
        {
            for(int j=1;j<=n;j++)cout<<a[j]<<' ';
            return 0;
        }
        int ret=find(i,r[id[i]],tree.query(1,1,n,r[id[i]]+1,i+k-1));
        if(ret>maxn)maxn=ret,minx=i;
    }
    sort(a+minx,a+minx+k);
    for(int i=1;i<=n;i++)cout<<a[i]<<' ';
    return 0;
}
```

---

## 作者：Robin_kool (赞：0)

先考虑字典序最大，我们需要使得第一个变化的位置尽量接近 $n$。

发现对于一个区间 $[l,r]$，如果第一个不变的位置为 $x$，则对于任意符合条件的 $[l+len,r+len]$，第一个不变的位置一个大于等于 $x$。原因很简单，后面的区间的一段不变前缀要么被接下来的某个数代替，要么是 $[l,r]$ 变化区间的一个子集（包括空集）。

也就是说，如果正序枚举 $l$，那么不动的前缀可能是最优解当且仅当它第一次被遍历到。

那么只需要对每一段不变的区间打标记即可。发现至多匹配 $n$ 次，存前缀可以用 `set` 之类的东西，复杂度大概是 $O(n \log n)$ 的。

---

## 作者：__Star_Sky (赞：0)

## Description
给定一个长度为 $n$ 的整数序列和一个整数 $k$，你需要进行一次操作，任意选择的一个长度为 $k$ 的区间并将该区间按升序排序。求能够得到的字典序最大的序列。

---
## Solution
首先，由于是按升序排序，得到的新序列的字典序一定不会比原序列大。当且仅当原序列中存在一个长度大于等于 $k$ 的单调递增序列时新序列和原序列的字典序相等，这种情况直接输出原序列即可。

如果不存在这样的单调递增序列，根据贪心策略，显然尽量选靠后的区间进行操作是更优的。这是因为如果选较为靠前的区间 $[l,r]$，那么 `a[l]` 的位置可能被更小的数代替，一定不会比选后面的区间更优。

但是选最靠后的区间 $[n-k+1,n]$ 仍然不一定是最优策略。考虑一个区间 $[l,r]$ 满足 $r\in[n-k+1,r-1]$，且区间 $[l,n-k]$ 是单调递增的，且 $[l,n-k]$ 的最大值小于等于 $[n-k+1,r]$ 的最小值。显然 $[l,n-k]$ 这部分是不会改变的。对于 $[n-k+1,r]$ 这一部分，如果 `a[r+1]` 大于等于这一段的最大值，那么选 $[n-k+1,r]$ 和 $[n-k+1,r+1]$是等价的，不会改变结果。如果`a[r+1]` 小于这一段的最大值，那么排序后 `a[r+1]`应该在的位置被一个更大的数代替了，排序后的序列字典序更大了。因此，只要区间 $[l,n-k]$ 是单调递增的，那么让 $r$ 更接近 $n-k+1$ 一定更优。可以倒序枚举 $l\in[\min(n-2*k+2,1),n-k]$，则$r=l+k-1$。如果不满足 $[l,n-k]$ 单调递增则直接 `break`。若满足$[l,n-k]$ 的最大值小于等于 $[n-k+1,r]$ 的最小值，就更新答案选取的区间。

由于单调递增，$[l,n-k]$ 的最大值实际上就是 `a[n-k]`。而对于 $[n-k+1,r]$ 的最小值，可以用线段树或 ST 表求出。

时间复杂度 $O(n\log n)$。

---
## Code
```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N];
struct trnode{
	int l,r,lc,rc,c;
}tr[N*4];
int trlen;
void build_tree(int l,int r)
{
	int now=++trlen;
	tr[now]={l,r,-1,-1,0};
	if(l==r) tr[now].c=a[l];
	else
	{
		int mid=(l+r)/2;
		tr[now].lc=trlen+1;build_tree(l,mid);
		tr[now].rc=trlen+1;build_tree(mid+1,r);
		tr[now].c=min(tr[tr[now].lc].c,tr[tr[now].rc].c);
	}
}
int get_min(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r) return tr[now].c;
	int lc=tr[now].lc,rc=tr[now].rc,mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid) return get_min(lc,l,r);
	else if(l>=mid+1) return get_min(rc,l,r);
	else return min(get_min(lc,l,mid),get_min(rc,mid+1,r));
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	if(n==k)
	{
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++) printf("%d ",a[i]);
		exit(0);
	}
	int cnt=1;
	for(int i=2;i<=n;i++)
	{
		if(cnt>=k)
		{
			for(int i=1;i<=n;i++) printf("%d ",a[i]);
			exit(0);
		}
		if(a[i]>=a[i-1]) cnt++;
		else cnt=1;
	}
	build_tree(1,n);
	int ans=n-k+1;
	for(int i=n-k;i+k-1>=n-k+1&&i>=1;i--)
	{
		if(a[n-k]<=get_min(1,n-k+1,i+k-1)) ans=i;
		if(a[i-1]>a[i]) break;
	}
	sort(a+ans,a+ans+k);
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：C6H6 (赞：0)

~~怎么一车 ST 表，给一个平衡树做法~~

写一个比较好理解的做法。（应该，但我可能描述的不好。）

这个做法是暴力优化。

先考虑暴力。

对于每个长度为 $k$ 的区间，排个序，一个一个比，比到第一个不同的位置，都记录下来，比较出最大的位置和对应区间的左端点。

很显然这是 $n$ 方的，同时我们维护一个长度为 $k$ 的序列，每次删除一个数并插入一个数，支持查询 $m$ 大的数。~~一看就可以用平衡树来维护。~~（考场发现 set 和 priority_queue 似乎都不支持随机访问。如果你觉的我太弱了不会用 STL 欢迎来 D 我）

但是如果每次都从头开始比较，前面一段可能多次比较，就会 T 飞。如果从之前已经匹配的地方（记为 $p$ ）开始匹配，就能保证时间复杂度并保证正确性。下面是我胡的证明：

如果新加进去的数排完序后的位置在 $p$ 之前，那么 $p$ 这个位置上原来的数一定会被“挤”掉，$p$ 位置上就无法匹配，也就不会再往下匹配，也不会更新答案。

如果新加进去的数排完序后的位置在 $p$ 后， 正确性显然。

因为 $p$ 单调递增，最多只会匹配 $n$ 次，时间复杂度为 $O(n \log n)$。

平衡树有一个简单的替代版本，但是要求离线或值域较小。刚好这题是个排列，于是就能用上这个奇技淫巧。详情见[这里](https://www.luogu.com.cn/blog/388651/about-RBIT)。

代码：

```cpp
/*
他说他是乱打的,
他可不是乱打的啊,
cin, cout, return 0,
训练有素,
后来他说他练过三四年OI,
啊, 看来是 有 Bear 来。
*/
#include <bits/stdc++.h>
using namespace std;
int c[200010], a[200010];
int n, k;
inline void add(int x, int y) {
	for(; x <= n; x += x & -x) c[x] += y;
}
inline int k_th(int k) {
	int p = 0, s = 0;
	for(int i = 18; i >= 0; i--) {
		if(p + (1 << i) > n) continue;
		if(s + c[p + (1 << i)] < k) p += (1 << i), s += c[p];
	}
	return p + 1;
}
int main() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i];

	for(int i = 1; i < k; i++) add(a[i], 1);
	int ansp = 0, p = 0;
	for(int i = k; i <= n; i++){
		add(a[i], 1);//插入
		if(i - k > 0) add(a[i - k], -1);//删除
		bool f = 0;
		
		for(int j = max(p, i - k + 1); j <= i; j++) {
			if(k_th(j - i + k) == a[j]) continue; //维护的序列中取第 j - i + k 大的数和现在的第 j 项比较，相同就跳过
			if(j > p || (j == p && k_th(j - i + k) > a[j])) { 
            //如果排序后更改的位置比之前大或者这个位置上的数字比原来更大
				p = j;//更新更改的位置
				ansp = i - k + 1;//更新区间的左端点
			}
			f = 1;
			break;
		}
		if(!f) { //特判不用变
			for(int i = 1; i <= n; i++) cout << a[i] << " ";
			puts("");
			return 0;
		}
	}
	sort(a + ansp, a + ansp + k);
	for(int i = 1; i <= n; i++) cout << a[i] << " ";
	puts("");


	return 0;
/*
*/
}
/*后记:
无
*/
```




---

## 作者：Flandres (赞：0)

赛时挂了无数发，赛后又被加的数据 hack 了/kk。

因为要求字典序最大，所以升序排序修改一定不优，若序列的升序连续段个数大于 $k$，那么答案直接就是原序列。

若个数小于 $k$，贪心地想，我们要获得字典序最大的序列，一定希望尽可能更改后面的数。设需要更改区间的左端点位置为 $pos$，先直接把当前答案设置为 $n-k+1$，接着看是否能将区间向左移动。如果排序当前区间后，在 $n-k+1$ 之前的数位置不发生改变，那么这种情况才是更优的。也就是说，$pos$ 可以移动到 $l$ 当且仅当 $[l,n-k+1]$ 中的数单调递增，并且 $[l,n-k]$ 的所有元素均小于 $[n-k+1,l+k-1]$ 中的元素。

可以拿 ST 表维护区间最小值。时间复杂度为 $O(n\log n)$。

upd:感谢 AKG_001 大佬指正错误。

code:

```cpp
#include<bits/stdc++.h>
const int N=2e5;
int n,k,a[N+5],f[N+5],mx;
int lg[N+5],st[N+5][20];
inline int query(int l,int r){
    if(l>r)return 0x7f7f7f7f;int k=lg[r-l+1];
    return std::min(st[l][k],st[r-(1<<k)+1][k]);
}
int main(){
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin>>n>>k;
    for(int i=1;i<=n;++i)std::cin>>a[i];
    f[n]=1;for(int i=n-1;i>=1;--i){if(a[i]<a[i+1])f[i]=f[i+1]+1;else f[i]=1;mx=std::max(mx,f[i]);}
    if(mx<k){
        lg[0]=-1;for(int i=1;i<=n;++i)lg[i]=lg[i>>1]+1;
        for(int i=1;i<=n;++i)st[i][0]=a[i];
        for(int j=1;j<=lg[n];++j)
            for(int i=1;i+(1<<j)-1<=n;++i)
                st[i][j]=std::min(st[i][j-1],st[i+(1<<j-1)][j-1]);
        int pos=n-k+1,lim=std::max(n-2*k+2,1);
        for(int i=n-k;i>=lim;--i){
            if(a[i]>a[i+1])break;
            if(a[n-k]<query(n-k+1,i+k-1))pos=i;
        }
        std::sort(a+pos,a+pos+k);
    }
    for(int i=1;i<=n;++i)std::cout<<a[i]<<" ";
    return 0;
}
//10 6 1 2 4 5 10 3 6 7 8 9
```

---

