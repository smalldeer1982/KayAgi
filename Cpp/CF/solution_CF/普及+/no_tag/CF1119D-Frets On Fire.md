# Frets On Fire

## 题目描述

## 题目背景
Miyako 带着尤克里里琴来到跳蚤王国。她与当地的跳蚤居民成为了好朋友，每天为他们演奏美妙的音乐。

作为回报，跳蚤为她做了一个更大的尤克里里琴：它有 $n$ 个弦，每个弦都有从 $0$ 到 $10^{18}$ 的 $10^{18}+1$ 个琴格（用来给琴划分音阶高低）。跳蚤使用数组 $s_1, s_2,......,s_n$ 来描述尤克里里琴的品，也就是说，第 $i$ 个弦上第 $j$ 个琴格的音调是整数 $s_i+j$。

Miyako 即将离开王国，但跳蚤希望 Miyako 能为它们回答最后一些问题。

第 $k$ 个问题是：“在所有弦上，琴格 $l_k$ 与琴格 $r_k$（包括 $l_k$，$r_k$）之间有多少个不同的音调？”

Miyako 即将访问蟋蟀王国，没有时间回答所有问题。请你帮助她完成这项任务！

在形式上，给出一个 $n$ 行 $10^{18}+1$ 列的矩阵，其中第 $i$  行（$1 \leqslant i \leqslant n$）第 $j$ 列（$0 \leqslant j \leqslant 10^{18}$）中的单元格为整数 $s_i+j$。有 $q$ 个询问，对于第 $k$ 个询问，你需要回答矩阵中从第 $l_k$ 列到第 $r_k$ 列（包括 $l_k$，$r_k$）的不同整数的数量。

## 样例 #1

### 输入

```
6
3 1 4 1 5 9
3
7 7
0 2
8 17
```

### 输出

```
5 10 18
```

## 样例 #2

### 输入

```
2
1 500000000000000000
2
1000000000000000000 1000000000000000000
0 1000000000000000000
```

### 输出

```
2 1500000000000000000
```

# 题解

## 作者：StudyingFather (赞：9)

先有一个比较显然的结论：区间平移答案不变。因此一个 $[l_i,r_i]$ 的询问可以平移为 $[0,r_i-l_i]$。

先来看看单独一列的情况：答案显然是 $n$。接下来我们增加一列，答案会增加多少呢？

$$1\ 3\ 4\ 5\ 9 \to 1\ 2\ 3\ 4\ 5\ 6\ 9\ 10$$

答案增加了 $3$，答案的增加归功于两部分：

1. 填补了之前数的空隙（比如 $1\ 3$ 之间的空隙和 $5\ 9$ 之间的空隙）。
2. 尾端添加了新数。

第一部分的贡献可以这样计算：我们先找出最初的所有空隙（定义两个数 $l,r$ 之间的空隙长度为 $r-l-1$），如果增加了 $x$ 列（现在有 $x+1$ 列了），那么所有长度小于等于 $x$ 的空隙都填平了，而长度大于 $x$ 的空隙则长度减少了 $x$。这个数据可以很轻松地通过二分和前缀和来计算。

第二部分比较显然，如果**增加**了 $x$ 列，则第二部分的增量就是 $x$。

```cpp
// Problem : D. Frets On Fire
// Contest : Codeforces Global Round 2
// URL : https://codeforces.com/contest/1119/problem/D
// Author : StudyingFather
// Site : https://studyingfather.com
// Memory Limit : 256 MB
// Time Limit : 1500 ms
// Powered by CP Editor (https://github.com/cpeditor/cp-editor)

#include <iostream>
#include <algorithm>
using namespace std;
long long s[100005],d[100005],sum[100005];
int main()
{
 long long n;
 cin>>n;
 for(int i=1;i<=n;i++)
  cin>>s[i];
 sort(s+1,s+n+1);
 for(int i=1;i<n;i++)
  d[i]=s[i+1]-s[i]-1;
 sort(d+1,d+n);
 for(int i=1;i<n;i++)
  sum[i]=sum[i-1]+d[i];
 int q;
 cin>>q;
 while(q--)
 {
  long long l,r;
  cin>>l>>r;
  r-=l;
  int p=upper_bound(d,d+n,r)-d;
  cout<<n+r+sum[p-1]+(n-p)*r<<endl;
 }
 return 0;
}
```

---

## 作者：Moyou (赞：3)

> 反悔贪心做法。

## 想法

首先发现，如果我们把区间 $[l, r]$ 移到 $[0, r - l]$，对答案无影响，因为这次操作相当于把被选中的所有数都减去 $r - l$，不同数字的个数依然不变。

接下来，从琴格 $0$ 开始向后拓展区间，让我们看看每个点对答案的贡献会发生什么变化。

以样例为例子：

$$\begin{matrix} \textbf{Fret} & \textbf{0} & \textbf{1} & \textbf{2} & \textbf{3} & \textbf{4} & \textbf{5} & \textbf{6} & \textbf{7} & \ldots \\ s_1: & 3 & 4 & 5 & 6 & 7 & 8 & 9 & 10 & \dots \\ s_2: & 1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 & \dots \\ s_3: & 4 & 5 & 6 & 7 & 8 & 9 & 10 & 11 & \dots \\ s_4: & 1 & 2 & 3 & 4 & 5 & 6 & 7 & 8 & \dots \\ s_5: & 5 & 6 & 7 & 8 & 9 & 10 & 11 & 12 & \dots \\ s_6: & 9 & 10 & 11 & 12 & 13 & 14 & 15 & 16 & \dots \end{matrix}$$

观察可以发现，实际上每个琴弦都有一定的寿命，也就是说，在若干琴格之后，一些琴弦不再对答案产生贡献。

$$\begin{matrix} \textbf{Fret} & \textbf{0} & \textbf{1} & \textbf{2} & \textbf{3} & \textbf{4} & \textbf{5} & \textbf{6} & \textbf{7} & \ldots \\ s_1: & \sqrt{} & \times & \times & \times & \times & \times & \times & \times & \dots \\ s_2: & \sqrt{} & \sqrt{} & \times & \times & \times & \times & \times & \times & \dots \\ s_3: & \sqrt{} & \times & \times & \times & \times & \times & \times & \times & \dots \\ s_4: &\times & \times & \times & \times &\times & \times &\times & \times & \dots \\ s_5: & \sqrt{} & \sqrt{} & \sqrt{} & \sqrt{} & \times & \times & \times & \times & \dots \\ s_6: & \sqrt{} & \sqrt{} & \sqrt{} & \sqrt{} & \sqrt{} & \sqrt{} & \sqrt{} & \sqrt{} & \dots \end{matrix}$$

如图，标记为 $\sqrt{}$ 的是对答案真正有贡献的琴格，标记为 $\times$ 的是对答案实际无贡献的琴格。

接下来进一步发现，这种有无贡献的变化的原因是这个琴格的数字已经与其他琴弦上的琴格重复了，同理，此琴格的下一个琴格也重复了。

设 $lim_i$ 表示第 $i$ 个琴弦最多有多少个琴格产生贡献，不难发现得知 $lim_i = a_j - a_i$，其中 $a_j$ 是比 $a_i$ 大的琴品的最小值，如果一个数是所有琴品的最大值，钦定其 $lim$ 为正无穷。

例如上图中，$lim_5 = a_6 - a_5 = 9 - 5 = 4$，可见图中 $5$ 号琴弦恰有 $4$ 个 $\sqrt{}$，完全没问题。

可以得知，如果一个查询区间 $[l, r]$ 的长度 $r - l + 1$ 比 $lim_i$ 小，那么 $i$ 号琴弦可以对答案产生 $r - l + 1$ 的贡献。

否则，代表 $i$ 号琴弦在区间右端点前就无法产生贡献了，贡献为 $lim_i$。

综上，一次询问 $[l, r]$ 的答案就是：

$$
\sum_{i = 1}^n\min(lim_i, r - l + 1)
$$

如果暴力计算这个可以得到 $O(qn)$ 的算法。

## 思路

顺着上述思路走，加速和式的计算。

具体而言，我们可以先把询问离线，之后按区间长度排序，设 $w_i = r_i - l_i + 1$，从前往后枚举，设当前枚举到第 $k$ 个区间。

为了方便计算，定义两个可以动态维护的变量 $cnt, sum$，分别表示有多少个数满足 $lim_i > w_k$，以及 $\sum_{lim_i < w_k}lim_i$，这样答案就为 $cnt\cdot w_k + sum$。

贪心地，我们先假设 $\forall lim_i > \max_{j = 1}^nw_j$，并且将 $lim_i$ 推入小根堆中。

在第 $k$ 个区间时，更新 $cnt$ 和 $sum$，流程如下。

1. $cnt\gets cnt - 1$，反悔之前令 $lim_i > w_k$ 的决策。
2. $sum\gets sum + top$，$top$ 为栈顶元素，加上当前决策带来的收益。
3. 弹出栈顶
4. 重复 $1\sim 3$，直到堆空或 $top > w_k$。

完成了 $cnt$ 和 $sum$ 的维护，再用上面的公式计算当前区间的答案就好了。

注意由于是离线之后的，所以要记录询问的编号，方便输出。

时间复杂度：$O(n\log n + q\log n)$

## AC 代码

```cpp
#include <iostream>
#include <queue>
#include <algorithm>
#define int long long
using namespace std;

const int N = 2e5 + 10;

int n;
int a[N];
int lim[N];
struct qwq
{
    int l, r, w, id;
    bool operator<(const qwq &W) const
    {
        return w < W.w;
    }
} p[N];
int ans[N];
int sum = 0, cnt;
priority_queue<int, vector<int>, greater<int>> heap;

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    lim[n] = 2e18 + 1; // 切记别开小了，不然会爆
    for (int i = n - 1; i >= 1; i--)
        lim[i] = a[i + 1] - a[i]; // 计算 lim
    int m;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> p[i].l >> p[i].r;
        p[i].w = p[i].r - p[i].l + 1;
        p[i].id = i;
    }
    cnt = n; // 初始设置
    for (int i = 1; i <= n; i++)
        heap.push(lim[i]); // 推入小根堆
    sort(p + 1, p + m + 1); // 按 w 从小到大排序
    for (int i = 1; i <= m; i++)
    {
        while (heap.size() && heap.top() < p[i].w)
        {
            cnt--; // 反悔
            sum += heap.top();
            heap.pop();
        }
        ans[p[i].id] = cnt * p[i].w + sum; // 计算贡献
    }
    for (int i = 1; i <= m; i++)
        cout << ans[i] << ' ';
    cout << '\n';

    return 0;
}
```

---

## 作者：Zechariah (赞：3)

由于要求的是一些连续区间的并，我们考虑怎么统计“新加入”的数的个数  
麻烦的是重复部分，不妨将s排序去重，然后发现，如果$s_i$与$s_{i-1}$的距离小于$r_i-l_i$，那么“新加入”的个数其实就是这个距离，所以我们做一下前缀和，每个询问二分一个位置，后面增加的个数就是询问区间的大小
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
typedef unsigned int uint;
const int N = 5e5 + 5, mod = 1e9 + 7, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
    inl ll read() {
        rg char c;
        rg ll x = 0;
        rg bool flag = false;
        while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
        if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
        while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if (flag)return -x; return x;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
ll s[N], d[N];
ll sum[N];

int main(void) {
    rg int n = fast_IO::read();
    for (rg int i = 1; i <= n; ++i)s[i] = fast_IO::read();
    sort(s + 1, s + n + 1);
    n = unique(s + 1, s + n + 1) - s - 1;
    for (rg int i = 1; i < n; ++i)d[i] = s[i + 1] - s[i];
    sort (d + 1, d + n);
    for (rg int i = 1; i < n; ++i)sum[i] = sum[i - 1] + d[i];
    rg int q = fast_IO::read();
    while (q--) {
        rg ll l = fast_IO::read(), r = fast_IO::read();
        rg ll cha = r - l;
        rg int x = lower_bound(d + 1, d + n, cha + 1) - d;
        rg ll ans = sum[x - 1];
        fast_IO::write(ans + (n - x + 1) * (cha + 1)); putchar(' ');
    }
    return 0;
}
```


---

## 作者：New_hope (赞：2)

有一些思维含量的题。

我们慢慢来，想想 $O(nq)$ 怎么做。

我们可能会想到把每一行的区间合并起来，求并区间的长度，这个过程我们需要记录 $l$ 和 $r$。但在纸上稍微手摸几个样例会发现对于 $[l,r]$ 和 $[l',r']$，当 $r' - l' = r - l$ 时答案是不变的（或者直接发现），那也就说明我们应该关心的不是每个区间的绝对位置。

那么在 $r - l$ 确定时，什么会影响答案？便是区间的**相对位置**。与上一段落的思想一致，我们仍要统计区间的并。先对区间的相对位置排序后，考虑用贡献计算，减去两两区间的交，于是你会得到以下式子。

记 $L = r - l + 1$，答案即为：

$$
w = nL - \sum_{i=1}^n\max\{(L - (a_i - a_{i-1})),0\}
$$

直接做仍然是 $O(nq)$ 的。把式子分为 $(a_i - a_{i-1}) < L$ 和 $\ge L$ 两部分，想到这里就知道该用二分 + 前缀和优化了。

参考代码：


```cpp
#include <bits/stdc++.h>
#define _ 100005
using namespace std;
using ll = long long;

int n, q;
ll a[_], d[_], sum[_], ans[_];

int main()
{
  cin >> n;
  for (int i = 1; i <= n; i ++) {
    cin >> a[i];
  }
  
  sort (a + 1, a + 1 + n);
  n = unique(a + 1, a + 1 + n) - (a + 1);

  for (int i = 2; i <= n; i ++) {
    d[i] = a[i] - a[i - 1];
  }
  sort (d + 2, d + 1 + n);
  for (int i = 2; i <= n; i ++) {
    sum[i] = sum[i - 1] + d[i];
  }

  cin >> q;
  for (int i = 1; i <= q; i ++) {
    int k; ll l, r, len; 
    cin >> l >> r;
    len = r - l + 1;
    k = upper_bound(d + 1, d + 1 + n, len) - d; k --;
    ans[i] = (n - k + 1) * len + sum[k];
  }

  for (int i = 1; i <= q; i ++) {
    cout << ans[i] << " ";
  }

  return 0;
}
/*
g++ H1.cpp -o H1.exe -O2 -Wall -std=c++11
*/
```

蒟蒻的第一篇题解，有不对处请指出！

---

## 作者：huayt (赞：2)

提供一种**权值线段树**的做法。

## 分析
有 $n$ 个弦，那么一个询问 $x,y$，很明显最多会有 $n\times(y-x+1)$ 个不同的音调。我的思路是减掉重复出现的音调得出答案。

举个例子（在区间 $x,y$ 中，弦已按**最初音调**（即原 $s$ 数组）排序）：

$
\begin{matrix}
s_1=1&2&3&4\\
s_2=3&4&5&6\\
s_3=4&5&6&7
\end{matrix}
$

易得这个区间中答案为 $7$，从 $s_1$ 开始发现 $3,4$ 重复（因为后面还会出现），$s_2$ 中 $4,5,6$ 重复，对答案有贡献只有 $s_1$ 的 $1,2$，$s_2$ 的 $3$ 和 $s_3$ 的 $4,5,6,7$。

发现只需要算后一个弦中与自己重复的个数即为 $(y-x+1)-(s_{i+1}-s_i)$，此时只有在 $s_{i+1}-s_i\le y-x$ 时才需要统计（不然结果小于等于零），所以把**差值**插入权值线段树，查询区间 $1,y-x$ 的信息，时间复杂度 $O(q\log n)$（记得离散化）。

## 代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;
typedef unsigned long long LL;
const int N=1e5+5;
LL f[N];
int fcnt;

int lower_find(LL x){
	int l=1,r=fcnt,res=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(f[mid]<=x) res=mid,l=mid+1;
		else r=mid-1;
	}
	return res;
}
struct Segment_Tree{
	int L[N<<2],R[N<<2],ct[N<<2],rt,top;
	LL sum[N<<2];
	
	void Insert(int &p,int l,int r,int x){
		if(!p) p=++top;
		if(l==r){
			ct[p]++;
			sum[p]+=f[x];
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) Insert(L[p],l,mid,x);
		else Insert(R[p],mid+1,r,x);
		ct[p]=ct[L[p]]+ct[R[p]];
		sum[p]=sum[L[p]]+sum[R[p]];
		return;
	}
	
	int query_cnt(int &p,int l,int r,int x,int y){
		if(r<x||l>y||!p) return 0;
		if(x<=l&&r<=y) return ct[p];
		int mid=(l+r)>>1;
		return query_cnt(L[p],l,mid,x,y)+query_cnt(R[p],mid+1,r,x,y);
	}
	
	LL query_sum(int &p,int l,int r,int x,int y){
		if(r<x||l>y||!p) return 0ll;
		if(x<=l&&r<=y) return sum[p];
		int mid=(l+r)>>1;
		return query_sum(L[p],l,mid,x,y)+query_sum(R[p],mid+1,r,x,y);
	}
}ST;

LL s[N],ans[N];
int n,q;

int main(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		scanf("%llu",&s[i]);
	sort(s+1,s+n+1);
	int cnt=unique(s+1,s+n+1)-s-1;
	for(i=1;i<cnt;i++)
		f[i]=s[i+1]-s[i];
	sort(f+1,f+cnt);
	fcnt=unique(f+1,f+cnt)-f-1;
	for(i=1;i<cnt;i++)
		ST.Insert(ST.rt,1,fcnt,lower_find(s[i+1]-s[i]));
	scanf("%d",&q);
	for(k=1;k<=q;k++){
		LL x,y,sum;
		scanf("%llu%llu",&x,&y);
		sum=(y-x+1)*cnt;
		sum-=(y-x+1)*ST.query_cnt(ST.rt,1,fcnt,1,lower_find(y-x))*1ll;
		sum+=ST.query_sum(ST.rt,1,fcnt,1,lower_find(y-x));
		ans[k]=sum;
	}
	for(i=1;i<=q;i++)
		printf("%llu ",ans[i]);
	printf("\n");
	return 0;
}
```


---

## 作者：decoqwq (赞：2)

真心一道简单题...省选也过分了

考虑到第$i$行到第$j$行的出现数字个数就等于第$1$行到第$j-i+1$行的出现数字个数，所以只需要考虑一开始的数即可

然后考虑的这个玩意不太好维护，我们换个思路

比如第一根弦上的数字$1\ 3\ 4\ 5\ 9$，会发现比较好维护的是$1-9$九个数减去**没有出现过的**数字$2\ 6\ 7\ 8$

那只要考虑两两数之间作差即可

比如对应上一个例子，我们弄$3$行，会发现是这样的
$\begin{matrix}1\ 3\ 4\ 5\ 9\\2\ 4\ 5\ 6\ 10\\ 3\ 5\ 6\ 7\ 11\end{matrix}$

看得出来，在相邻的差小于$4$的数中，空隙都被填满了

所以只需要先预处理两两间差值的前缀和，然后查询时二分最小的大与询问区间长度的差值即可
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[100010],maxdel,del;
int d[100010],sum[100010];
main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
    }
    sort(a+1,a+n+1);
    del=a[n]-a[1];
    for(int i=2;i<=n;i++)
    {
        maxdel=max(maxdel,a[i]-a[i-1]);
        d[i]=a[i]-a[i-1]-1;
    } 
    sort(d+2,d+n+1);
    for(int i=2;i<=n;i++)
    {
        sum[i]=sum[i-1]+d[i];
    }
    int q;
    cin>>q;
    for(int i=1;i<=q;i++)
    {
        int l,r;
        scanf("%lld%lld",&l,&r);
        int ans=a[n]+r-l-a[1]+1;
        if(maxdel<(r-l+1))
        {
            printf("%lld\n",ans);
        }
        else
        {
            int qaq=lower_bound(d+2,d+n+1,(r-l+1))-d;
            ans-=(sum[n]-sum[qaq-1]-(r-l)*(n-qaq+1));
            printf("%lld\n",ans);
        }
    }
}
```


---

## 作者：01Dragon (赞：1)

### 思路
本题需要用到二分和前缀和。

我们可以首先把第 $l$ 列到第 $r$ 列的矩阵转移成第 $0$ 行到第 $r-l$ 行的矩阵，这样显然答案不变。

在只有 $1$ 列时，显然只有 $n$ 个不同的数。随着列数的增加，答案也在增加。答案的增加可以分为两种情况：

1. 新的数是原来的数之间没有的数，填补了之前的缝隙。
2. 最大的数增加。

第一种情况可以这样计算增加的数：首先开一个数组记录每两个数之间的差，再根据排完序的差进行前缀和，存进 $he$ 数组里。由于每个缝隙的大小不同，所以缝隙可能被填满，也可能没有。当增加的列数大于缝隙长度时就能填满，否则则不能。这是我们就要进行二分，找到第一个能填满的缝隙，将下标记录在变量 $x$ 里，再 $x \gets x-1$,那这个缝隙之前的新增数之和就是 $he_x$，之后的新增数之和就是 $(n-x+1) \times (r-l)$。

第二种情况很简单，新增的数量就是新增的列数，也就是 $r-l$。

所以最终答案就是 $n+r-l+he_x+(n-x+1) \times (r-l)$。

提醒：别忘了排序！注意数据范围！
### 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
long long n,s[100005],q,l,r,cha[100005],he[100005]; 
int erfen(long long x)//二分 
{
	int ll=1,rr=n;
	while(ll<rr)
	{
		int mid=(ll+rr)/2;
		if(cha[mid]<x)
		{
			ll=mid+1;
		}
		else
		{
			rr=mid;
		}
	}
	return ll;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	sort(s+1,s+n+1);
	for(int i=1;i<n;i++)
	{
		cha[i]=s[i+1]-s[i]-1;//求差 
	}
	sort(cha+1,cha+n);
	for(int i=1;i<n;i++)
	{
		he[i]=he[i-1]+cha[i];//前缀和 
	}
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		cin>>l>>r;
		int shu=erfen(r-l);
		shu--;
		cout<<n+r-l+he[shu]+(n-shu-1)*(r-l)<<' ';
	} 
	return 0;
}
```



---

## 作者：Adolfo_North (赞：0)

大水题。

首先，若区间内只有一根弦，不会对答案有贡献。

我们思考如何对答案产生贡献。我们知道，对于每一个 $s_i$，都会产生一段 $s_i+r-l$ 的连续序列，在对 $s$ 数组排序后，若每个 $s_i+r-l \ge s_{i+1}$ 则答案为 $s_n+r-(s_1+l)+1$。

若够不到下一位呢？我们在 $s_n+r-(s_1+l)+1$，上减去够不到的位数即可。

过程的实现：我们先对 $s$ 数组排序，将 $s_{i+1}-s_i \ge 2$ 的 $s_{i+1}-s_i$ 压入 $c$ 数组中，对 $c$ 排序，并且求其前缀和数组 $sum$。设 $c$ 数组长度为 $m$。

对于询问 $l,r$，若 $r-l$ 大于 $c_m$，二分查找 $c$ 数组中第一个大于 $r-l$ 的数，$c_x$。够不到的位数即为 `sum[m]-sum[x-1]-ch*(m-x+1)`。用 $s_n+r-(s_1+l)+1$ 减去即可。反之，输出 $s_n+r-(s_1+l)+1$ 即可。

代码（讲的很详细了不放注释了）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+7;
int a[N],sum[N],c[N];
int n,m;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=2;i<=n;i++) {
		if(a[i]-a[i-1]>1) c[++m]=a[i]-a[i-1]-1;
	}
	sort(c+1,c+1+m);
	for(int i=1;i<=m;i++) sum[i]=sum[i-1]+c[i];
	int qu;
	cin>>qu;
	while(qu--){
		int l,r;
		cin>>l>>r;
		int ch=r-l,ans=a[n]+r-a[1]-l+1;
		if(ch<c[m]) {
			int w=upper_bound(c+1,c+1+m,ch)-c;
//			cout<<w<<'\n';
			int su=sum[m]-sum[w-1]-ch*(m-w+1);
			ans-=su;
		}
		cout<<ans<<' ';
	}
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1119D)
## 思路
@_edge_ 最喜欢的诈骗题。

我们可以显然的发现答案只和区间的长度有关，所以实际上我们要算的是 $r-l+1$ 长度的区间答案。

接下来思考什么情况下会产生重复计算。

显然就是 $a_i-a_{i-1}$ 这个差值可以被区间长度覆盖的时候。

然后，答案就出来了，我们把总的长度减去重复贡献的就好了。
## 代码
[AC 记录](https://codeforces.com/contest/1119/submission/172098243)

---

