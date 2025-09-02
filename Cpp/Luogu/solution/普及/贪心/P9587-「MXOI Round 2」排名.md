# 「MXOI Round 2」排名

## 题目描述

小 C 有一个长度为 $n$ 的数组 $a$。

小 C 定义，$f(i)$ 为 $a_i$ 的前排名，其中 $f(i)$ 等于数组 $a$ 中大于 $a_i$ 的元素个数加 $1$。

小 C 还定义，$g(i)$ 为 $a_i$ 的后排名，其中 $g(i)$ 等于数组 $a$ 中大于等于 $a_i$ 的元素个数。

每次操作，小 C 需要选择一个不大于 $n$ 的正整数 $t$，并将 $a_t$ 的值增加 $1$。

小 C 想知道，对于每一个 $1 \le i \le n$，想要使 $f(i) \le k \le g(i)$，最少需要进行多少次操作？

可以证明一定存在一种操作方案使得 $f(i) \le k \le g(i)$。

## 说明/提示

#### 【样例解释 #1】

当 $i=1$ 时，小 C 可以选择 $t=1$ 并进行 $3$ 次操作。此时 $f(i)=2$，$g(i)=4$，满足 $f(i) \le k \le g(i)$。可以证明此时小 C 至少需要进行 $3$ 次操作。

当 $i=4$ 时，小 C 可以选择 $t=3$ 进行 $1$ 次操作，再选择 $t=6$ 进行 $1$ 次操作。此时 $f(i)=1$，$g(i)=3$，满足 $f(i) \le k \le g(i)$。可以证明此时小 C 至少需要进行 $2$ 次操作。

#### 【样例 #2】

见附加文件中的 `rank/rank2.in` 与 `rank/rank2.ans`。

该样例满足测试点 $7$ 的限制。

#### 【样例 #3】

见附加文件中的 `rank/rank3.in` 与 `rank/rank3.ans`。

该样例满足测试点 $20$ 的限制。

#### 【数据范围】

对于 $100\%$ 的数据，$1 \le k \le n \le 5 \times 10^5$，$1 \le a_i \le 10^9$。

|测试点编号|$n \le$|$a_i \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1\sim6$|$2000$|$10^9$|A|
|$7\sim10$|$2000$|$10^9$|无|
|$11\sim14$|$5\times10^5$|$10^9$|B|
|$15\sim20$|$5\times10^5$|$10^9$|无|

特殊性质 A：保证对于所有的 $1 \le i \lt n$，都有 $a_i \ge a_{i+1}$。

特殊性质 B：保证 $k=1$。

## 样例 #1

### 输入

```
0 6 3
1 1 4 5 1 4```

### 输出

```
3
3
0
2
3
0```

# 题解

## 作者：卷王 (赞：24)

## 题目大意

[传送门](https://www.luogu.com.cn/problem/P9587)

题目已经很简短了，不好概括。

## 大体思路

先讲一下 $20$ 分的做法，从部分分做起可以更深的理解题意。

看题目中的特殊性质 B，既然 $k=1$ 那么 $f(i)$ 就必须为 $1$，而 $g(i)$ 又必须大于 $0$，所以当前的数就必须和最大数平齐，所以对于每一个 $i$，答案就是 $maxx-a_i$，其中 $maxx$ 为数列最大值。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int c,n,k,maxx = 0;
int a[500007];

int main(){
	c = read(), n = read(), k = read();
	for(int i = 1; i <= n; i++) a[i] = read(), maxx = max(maxx, a[i]);
	if(k == 1) {
		for(int i = 1; i <= n; i++)
			printf("%d\n", maxx - a[i]);
		return 0;
	}
	
	return 0;
}
```
得完这档部分分，相信大家对于 $f(i)$ 和 $g(i)$ 都有了更深的理解。

------------
那么我们考虑 $100$ 分做法。

我在做这题的时候有一种下意识，当我发现题目怎么暴力也暴力不出来的时候，就想到分情况讨论，找规律。

首先，我们得先给数组排个序。

于是有如下几种情况：

* $a_i < a_k$。我们要让 $f(i)$ 尽量小，也就是得让 $a_i$ 变的更大，发现 $a_i=a_k$ 的时候正好满足条件，所以答案为 $a_k-a_i$。

* $a_i > a_k$。由于数组已经排过序了，那么就贪心地选择后面的 $k-i$ 个数，将它们变成 $a_i$，那么总代价为 $\sum\limits_{j=i+1}^{k} a_i-a_j$。

* $a_i = a_k$。显然答案为 $0$。

其中第二个式子可以直接用前缀和优化。

由于要排序，时间复杂度为 $O(n \log n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int _,n,k,maxx=0;
struct node {
	int x, num;
} a[500007];
ll sum[500007], ans[500007];
inline bool cmp(node i, node j) { return i.x > j.x; }
int main(){
	_ = read(), n = read(), k = read();
	for(int i = 1; i <= n; i++) a[i].x = read(), a[i].num = i;
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i].x;
	for(int i = 1; i <= n; i++) {
		if(a[i].x == a[k].x) continue;
		if(a[i].x < a[k].x) ans[a[i].num] = a[k].x - a[i].x;
		else ans[a[i].num] = (k - i) * 1ll * a[i].x - (sum[k] - sum[i]);
	}
	for(int i = 1; i <= n; i++)
		printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：Coffee_zzz (赞：12)

### Task 1~6

在前面放一个省流。

> 当 $a_i=a_k$ 时答案为 $0$；
>
> 当 $a_i \gt a_k$ 时答案为 $a_i-a_k$；
>
> 当 $a_i \lt a_k$ 时答案为 $\sum\limits^k_{j=i+1} a_i-a_j$。

接下来说思考过程和证明。

显然地，$i=k$ 时一定有 $f(i) \le k \le g(i)$，所以 $i=k$ 时答案为 $0$。

仍然显然地，当 $a_i=a_k$ 时一定有 $f(i)=f(k)$ 且 $g(i)=g(k)$，所以当 $a_i=a_k$ 时答案也为 $0$。

接下来我们考虑 $a_i \gt a_k$ 时的答案。

此时，由于 $a_i \gt a_k$，根据 $f$ 和 $g$ 的定义，一定有 $f(i) \gt g(k) \ge k$，即 $k \lt f(i)$。$f(i)$ 太大，我们要通过操作减小 $f(i)$ 的值。

我们知道，要操作的话一定是对 $a_i$ 进行操作，因为只有这样才能使 $f(i)$ 尽可能小，对其他数进行操作只会使 $f(i)$ 越来越大。

操作到多少合适呢？当 $a_i=a_k$ 时一定有 $f(i)=f(k)$ 且 $g(i)=g(k)$，满足条件，而 $a_i \gt a_k$ 时又有 $f(i) \gt g(k) \ge k$，不满足条件，所以操作到 $a_i=a_k$ 最优，一共需要操作 $a_i-a_k$ 次。单次计算复杂度 $O(1)$。

我们再来考虑 $a_i \lt a_k$ 时的答案。

此时，由于 $a_i \lt a_k$，根据 $f$ 和 $g$ 的定义，一定有 $g(i) \lt f(k) \le k$，即 $k \gt g(i)$。$g(i)$ 太小，但是每次操作只能使 $g(i)$ 越来越小，那我们只能对其他数进行操作，使 $g(i)$ 的值越来越大。

那我们让第 $k$ 大的数等于 $a_i$，此时一定有 $f(i)=f(k)$ 且 $g(i)=g(k)$，满足条件，而第 $k$ 大的数小于 $a_i$ 时又有 $g(i) \lt f(k) \le k$，不满足条件，所以让第 $k$ 大的数等于 $a_i$ 最优。

我们要让操作数尽可能少，那我们就贪心地选择下标为 $i+1$ 到 $k$ 的数进行操作，让他们都等于 $a_i$，此时满足第 $k$ 大的数等于 $a_i$ 且最优，总操作次数为 $\sum\limits^k_{j=i+1} a_i-a_j$。暴力计算这个式子的复杂度为 $O(k)$。

这样做的最劣时间复杂度为 $O(n^2)$，可以通过。

这一大段话看起来很复杂，但其实想起来还是很简单的，甚至直接猜都可以。

### Task 7~10

你会发现数组 $a$ 的顺序除了在输出答案的时候都没有影响，那开一个结构体，存 $a_i$ 的值和其下标，然后按照 $a_i$ 从大到小排序，套上面的做法即可，输出的时候按下标输出，时间复杂度 $O(n^2)$。

### Task 11~14

你会发现 $k=1$ 时排完序后不会出现 $a_i \lt a_k$ 的情况，那么直接套 Task 9~12 的做法即可，时间复杂度 $O(n \log n)$。

### Task 15~20

考虑化简式子。

$$
\sum\limits^k_{j=i+1} a_i-a_j = (k-i)\times a_i- \sum\limits^k_{j=i+1} a_j
$$

你会发现这个东西直接上前缀和就行，时间复杂度 $O(n \log n)$。

当然这个东西也可以 dp 做。

定义 dp 数组 $dp_{i}$ 表示对于排序后的数组 $a$，使 $a_{i+1} \sim a_k$ 都变为 $a_i$ 所至少需要进行的操作数。

根据 dp 数组的定义可以得到转移方程为：

$$
dp_i=dp_{i+1}+(k-i)\times (a_i-a_{i+1})
$$

转移顺序为从 $k-1$ 到 $1$。

由于 $k=i$ 时答案为 $0$，可以得到初始状态为 $dp_k=0$。

最后记得开 `long long`。

### Code

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e5+5;
struct Nod{
	int a,id;
}nod[N];
ll ans[N],f[N];
bool cmp(Nod x,Nod y){
	return x.a<y.a;
}
int main(){
	ios::sync_with_stdio(0);
	int c,n,k;
	cin>>c>>n>>k;
	for(int i=1;i<=n;i++) cin>>nod[i].a,nod[i].id=i;
	sort(nod+1,nod+n+1,cmp);
	reverse(nod+1,nod+n+1);
	for(int i=k;i<=n;i++) ans[nod[i].id]=nod[k].a-nod[i].a;
	for(int i=k-1;i>=1;i--) f[i]=f[i+1]+1ll*(k-i)*(nod[i].a-nod[i+1].a),ans[nod[i].id]=f[i];
	for(int i=1;i<=n;i++) cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：XiaoQuQu (赞：7)

容易发现 $a$ 的顺序对答案无影响，所以我们先将 $a$ 从大到小排序。

考虑 $f,g$ 在排序后有什么更加显然的意义，容易发现，对于任意 $i\in[1,n]$，令 $p$ 为最小的使得 $a_p=a_i$ 的数，$q$ 为最大的使得 $a_p=a_i$ 的数，$f(i)$ 其实就是 $p$，$g(i)$ 其实就是 $q$：

$$
\underbrace{\overbrace{a_1,a_2,a_3,\cdots ,a_p}^{f(i)},a_{p+1},\cdots,a_{i},\cdots,a_{q-1},a_{q}}_{g(i)},\cdots,a_n.
$$

所以我们对于任意 $i\in[1,n]$，有如下结论：

1. 当 $i>k$ 的时候，由于 $f(i)\ge k$，我们需要 $a_i-a_k$ 次将他变为 $a_k$。
2. 当 $i=k$ 的时候，答案为 $0$。
3. 当 $i<k$ 的时候，我们需要令 $g(i)\ge k$，也就是需要将 $p\in (i,k]$ 的所有数 $a_p$ 变为 $a_i$，答案也就为 $\sum\limits_{p=i+1}^k a_p-a_i$。

考虑情况 (3) 的式子如何优化，显然可以把 $a_i$ 提到求和外边，变成 $\sum\limits_{p=i+1}^k a_p - (k-i)\times a_i$，发现这个式子可以用前缀和优化，然后就优化一下，最终时间复杂度 $O(n \log n)$。

```cpp
const int MAXN = 5e5 + 5;
int c, n, k, ans[MAXN], s[MAXN];
struct _node {
	int v, i;
	bool operator < (const _node b) const {
		return v > b.v;
	}
} a[MAXN];

void work() {
	cin >> c >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> a[i].v, a[i].i = i;
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i].v;
	for (int i = 1; i < k; ++i) ans[a[i].i] = (k - i) * a[i].v - (s[k] - s[i]);
	for (int i = k; i <= n; ++i) ans[a[i].i] = a[k].v - a[i].v;
	for (int i = 1; i <= n; ++i) cout << ans[i] << endl;
}
```


---

## 作者：Fireworks_Rise (赞：5)

# 题意

比较容易理解，题目给出数列 $a_i$。

对于 $a$ 数组中的任意一个数 $v$，有：

$f_i$ 为 $1+\textstyle \sum_{i=1}^{n} ai > v $

$g_i$ 为 $\textstyle \sum_{i=1}^{n} ai \ge v$

再给出 $k$ ，对于每个 $S \in a_i$，可以对其进行 $+1$ 操作，最后使得 $f_i \le k \le g_i$ 的最小操作次数。

# 思路 & 流程

观察题目，可以发现每个询问是单独的，说明数组的顺序并不影响最后答案的正确性，所以采用离线的模式处理。

先对 $a$ 数组的值从小到大排序，使数列有序。

此时对于每个 $f_i$ 的值都是其后面的数的数目（包括自己）,即 $f_i=n-i+1$。

分析一下，若 $f_i > k$，则不符合数列的要求，然而只能对数 $+1$，可以想到，如果对除本身之外的数操作， $f_i$ 只会越来越大，所以，只考虑对自身进行操作的。

一点点贪心，要使 $f_i$ 符合要求的前提下操作次数最小，只需 $f_i=k$ 即可，所以 $f_i$ 改变后 $a_i$ 的位置应该是在 $i+(k-f)$，此部分的最小操作次数为 $a_{i+(k-k)}-a_i$。

用二分维护一下修改后的 $a_i$ 在数列中的位置。

易知，这时的 $g_i$ 应该为 $n-r+1$；

若 $g_i <k$，需要使大于等于 $a_i$ 的数增多，最优的情况必定是将 $S \in a_i$ 的数变为 $a_i$，预处理时维护数列的前缀和，则此时的操作次数应该为 $w*(k-g+1)-(qz_r-qz_{r-(k-g)-1})$。

由于是离线操作，最后应把两次操作次数相加存入 $ans_i$ 即可。

# Code

本思想坑点较多，贴上蒟蒻的代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int c,n,k,s[N];
struct Node {
	int id,x;
	int ans;
}a[N];
int ans[N];
bool cmp(Node x,Node y) {
	return x.x<y.x;
}
signed main() {
	scanf("%lld%lld%lld",&c,&n,&k);
	for(int i=1;i<=n;i++) {
		scanf("%lld",&a[i].x);
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
		s[i]=s[i-1]+a[i].x;
	for(int i=1;i<=n;i++) {
		if(a[i].x==a[i-1].x) 
			ans[a[i].id]=ans[a[i-1].id];
		else {
			int f=n-i+1,p=0,w=a[i].x;
			if(f>k) p=a[i+f-k].x-a[i].x,w=a[i+f-k].x;
			int l=0,r=n+1;
			while(l+1<r) {
				int mid=(l+r)>>1;
				if(a[mid].x<w) l=mid;
				else r=mid;
			}
			if(r>i+f-k&&f>k) r--;
			int g=n-r+1; 
			if(g<k) {
				int tmp=r-(k-g);
				p+=w*(k-g+1)-(s[r]-s[tmp-1]);
				if(tmp<=i&&r!=i) {
					p=p-(w-a[i].x);
					p=p+(w-a[tmp-1].x);
				}
			}
			ans[a[i].id]=p;
		}
	}
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：4)

上来果断先排个序。

如果排完序的新位置 $i\ge k$，也就是说 $a_i\le a_k$，只用把 $a_i$ 变为 $a_k$ 就完事了。

否则，需要把 $a_i\sim a_k$ 的值全部变为 $a_i$。这里我们用前缀和维护。

对于相同的 $a_i$，它们的答案必定相同。所以我们相同的值只用做一遍就好了。

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
int c,n,k,s[500010],ans[500010];
struct node{int x,id;}a[500010];
bool cmp(const node &x,const node &y){
    return x.x>y.x;
}
signed main()
{
    cin>>c>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].x;
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);
    //for(int i=1;i<=n;i++)cout<<a[i].x<<endl;
    for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i].x;
    for(int i=1;i<=n;i++)
        if(a[i].x!=a[i-1].x)
        {
            int now;
            if(i>=k)now=a[k].x-a[i].x;
            else now=a[i].x*(k-i+1)-(s[k]-s[i-1]);
            for(int j=i;a[j].x==a[i].x;j++)ans[a[j].id]=now;
        }
    for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
    return 0;
}
```

这是小号 @A_Legendary_Coder 赛时交的代码。

---

## 作者：菲斯斯夫斯基 (赞：3)

## P9587 排名 题解

首先我们可以用 `upper_bound` 和 `lower_bound` 预处理出每一个 $f_i$ 和 $g_i$。

然后可以得出一个结论：至少有 $1$ 个数满足 $f_i\le k\le g_i$。

显然，从大到小排序后，第 $k$ 个数一定满足，不妨设此数的值为 $mi$。

因为 $f_i\le g_i$，所以可以分成 $3$ 类进行讨论：

1. $f_i\le k\le g_i$。答案为 $0$。

2. $k<f_i\le g_i$。说明有 $\ge k$ 个数比 $a_i$ 大，所以会选择增大 $a_i$。接下来考虑 $a_i$ 要增大到多少。不难发现，当 $a_i=mi$ 时；可以满足条件，但当 $a_i<mi$ 时，$f_i$ 仍大于 $k$。故此时的答案为 $mi-a_i$。

3. $f_i\le g_i<k$。说明 $a_i$ 太大，所以选择增大其他的数。不难想到，更优的策略当然是将**最大的小于** $a_i$ **的** $k-g_i$ **个数**，更改为 $a_i$。用前缀和优化，可以求出答案。

时间复杂度：$O(n\log n)$。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int c,n,k,mi=1e9;
int f[N],g[N],a[N],b[N],s[N];
signed main()
{
	scanf("%lld%lld%lld",&c,&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),b[i]=a[i];
	sort(b+1,b+1+n);
	mi=b[n-k+1];//从大到小排序后，第 k 个数
	for(int i=1;i<=n;i++)
	{
		s[i]=s[i-1]+b[i];
		f[i]=n-(upper_bound(b+1,b+1+n,a[i])-b)+2;
		g[i]=n-(lower_bound(b+1,b+1+n,a[i])-b)+1;//依次求出前缀和,f、g 数组
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i]<=k&&k<=g[i])printf("0\n");//符合，答案为 0
		else if(f[i]>k)printf("%lld\n",mi-a[i]);//第二种情况
		else
		{
			int p=lower_bound(b+1,b+1+n,a[i])-b-1;//第一个小于 ai 的数的位置
			int t=k-g[i];//增加 t 个数
			printf("%lld\n",a[i]*t-(s[p]-s[p-t]));//求出需要增加的值，即为答案
		}
	}
	return 0;
}


```

---

## 作者：SJZ2010 (赞：3)

### 做题思路

这题看上去很麻烦，然而只需要几个简单的结论：

1. 很显然：
	对于每一个 $1 \le i \le n$，$f(i) \le g(i)$。

2. 如果 $f(i) > k$，需要增加 $a_i$，因为增加别的数只会让 $f(i)$ 继续增加或不变。

3. 如果 $g(i) < k$，需要将排序后的 $a$ 数组（设它为 $b$）$a_i$ 所在位置前的 $k-g(i)$ 个数增加到 $a_i$。增加 $ >a_i$ 的数不会改变 $g(i)$ 的大小，为了使增加次数最少，要将与 $a_i$ 差距最小的 $k-g(i)$ 个数增加到 $a_i$。

4. 由 1. 可得，上述两种情况要么全不出现，要么只出现一种。

### 实现方法

1. 将一个与原来 $a$ 数组相同的 $b$ 数组从小到大排序。

1. 求 $g(i)$ 和 $f(i)$ 直接二分求。

2. 先预处理出 $b$ 数组中满足 $f(i) \le k \le g(i)$ 的区间 $[l,r]$（一下沿用此称呼）。

3. 对于每个 $a_i$，由做题思路中的 2、3 进行分类，并计算答案，第 2 种情况需要将 $a_i$ 增加到 $b_l$，第 3 种情况可以用前缀和加快计算，2、3 种情况全不满足则输出 $0$。

这样时间复杂度是 $O(n \log n)$ 的，可以通过此题。

### 注意点

1. 要开 `long long`！

### 代码实现

```cpp
#include <cstdio>
#include <algorithm>

const int N = 5e5+5;

long long c, n, k;
long long a[N], b[N], sum[N];

inline long long g(long long p){//计算两个函数
	long long q = std::lower_bound(b+1, b+n+1, p)-b;
	return n-q+1;
}
inline long long f(long long p){
	long long q = std::upper_bound(b+1, b+n+1, p)-b;
	return n-q+2;
}

int main(){
	scanf("%lld %lld %lld", &c, &n, &k);
	for(int i(1); i<=n; i++)
		scanf("%lld", &a[i]), b[i] = a[i];
	std::sort(b+1, b+n+1);//排序
	for(int i(1); i<=n; i++)
		sum[i] = sum[i-1]+b[i];//计算前缀和
	int s_f = 1, s_g = n;
	for(; s_f<=n; s_f++)//计算不用修改的区间范围
		if(f(b[s_f]) <= k)
			break;
	for(; s_g>=1; s_g--)
		if(g(b[s_g]) >= k)
			break;
	for(int i(1); i<=n; i++){
		if(a[i] >= b[s_f] && a[i] <= b[s_g]){//2、3 都不满足
			printf("0\n");
			continue;
		}
		if(a[i] < b[s_f]){//第 2 种
			printf("%lld\n", b[s_f]-a[i]);
		}else if(a[i] > b[s_g]){// 第 3 种
			long long now = k-g(a[i]);
			long long idx = std::lower_bound(b+1, b+n+1, a[i])-b;//计算 a[i] 在 b 数组中的位置
			long long Sum = sum[idx-1]-sum[idx-now-1];
			Sum = now*a[i]-Sum;//计算需要多少次操作
			printf("%lld\n", Sum);
		}
	}
	return 0;
}
```

---

## 作者：Milthm (赞：2)

## P9587 题解

~~怎么感觉我跟正解做的不是很一样。~~

### 前置知识

- 数学

### 题目解法

首先发现一件事，$g(i)$ 一定是大于等于 $f(i)$ 的，因为这个数至少有 $1$ 个。

然后根据这个，我们分情况来讨论。

假设我们每次遍历到一个值 $a_i$，先求出这个地方的 $f(i)$ 和 $g(i)$，然后看一下属于什么情况。

- 如果 $f(i)\le k \le g(i)$，说明已经满足条件，输出 $0$。

- 如果 $g(i)\le k$，说明当前的 $a_i$ 太大了，但是此时把 $a_i$ 往上调是没用的，这样只会使 $g(i)$ 越来越小。所以设 $q=k-g(i)$，应该找到序列中比 $a_i$ 小的数中，前 $q$ 大的，把它们全都变成 $a_i$。若序列中比 $a_i$ 小的数中，前 $q$ 大的数的和为 $x$，则答案为 $qa_i-x$。

- 如果 $f(i)\ge k$，说明当前的 $a_i$ 太小了，但此时改其它的数只会使 $f(i)$ 更大，所以只能改 $a_i$ 本身。容易发现把 $a_i$ 改到序列中第 $k$ 大值就可以满足条件。设第 $k$ 大值为 $p$，答案即为 $p-a_i$。

然后发现这个操作是 $O(n^2)$ 的，会超时。但是没关系，容易发现这一堆最大值最小值的可以用二分，这个“序列中比 $a_i$ 小的数中，前 $q$ 大的数的和”可以用前缀和来维护，然后本题就做完了。

### AC 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
int c,n,k,a[5000005],b[5000005],ff[5000005]; 
int read(){
    int f=1,x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
signed main(){
	cin>>c>>n>>k;
	for(int i=1;i<=n;++i)a[i]=read(),b[i]=a[i];
	sort(b+1,b+n+1);
	int qwq=b[n-k+1];//第 k 大值
	for(int i=1;i<=n;++i)ff[i]=ff[i-1]+b[i]; 
	for(int i=1;i<=n;++i){
		int f=n-(upper_bound(b+1,b+n+1,a[i])-b)+2,g=n-(lower_bound(b+1,b+n+1,a[i])-b)+1;//f(i) 和 g(i)
		if(f<=k&&k<=g)puts("0");
		else if(g<k){
			int ovo=lower_bound(b+1,b+n+1,a[i])-b;//a_i 在序列中的位置
			printf("%lld\n",(k-g)*a[i]-(ff[ovo-1]-ff[ovo-1-(k-g)]));
		}
		else{
			printf("%lld\n",qwq-a[i]);
		}
	}
	return 0;
}
```


---

## 作者：Hughpig (赞：2)

引理：一定有 $f(i)\le g(i)$。

把 $f(i)$ 看作两部分组成：比 $a_i$ 大的数和 $a_i$ 自己。

把 $g(i)$ 看成三部分组成：比 $a_i$ 大的数，和 $a_i$ 一样大的其他数（可能为 $0$ 个）和 $a_i$ 自己。

可以看到 $g(i)$ 包含 $f(i)$ 的每个部分。

我们考虑怎么计算 $f(i)$ 和 $g(i)$。

把 $a$ 复制一份，记作 $a'$。

对于 $f(i)$，我们把 $a'$ 排序，然后二分找出大于 $a_i$ 的数的个数，$+1$ 即可。可以用自带的 `lower_bound` 函数找出小于等于 $a_i$ 的数的个数，设答案为 $k$，则 $n-k+1$ 就是 $f(i)$。

对于 $g(i)$ 可以类似的用 `upper_bound` 找出小于 $a_i$ 的数的个数，记答案为 $k$，则 $g(i)=n-k$。注意这里不用 $+1$。

代码：

```cpp
int f(int i){
	int qwq=a[i];
	return n-(upper_bound(a_+1,a_+n+1,qwq)-a_-1)+1;
}

int g(int i){
	int qwq=a[i];
	return n-(lower_bound(a_+1,a_+n+1,qwq)-a_-1);
}
```

然后对于每个 $a_i$ 分类讨论：

如果 $f(i)\le k \le g(i)$，那么不用操作就行，输出 $0$。

如果 $f(i)>k$，那么需要减少大于 $k$ 的数的个数，反向思考，即增加 $a_i$。

如果 $g(i)<k$，那么需要增加大于等于 $k$ 的数的个数，即增加比 $a_i$ 小的数。

为了操作次数最小，因此选比 $a_i$ 小的数中最大的 $k-g(i)$ 个，增加到 $a_i$。

我们求出后缀和，这样可以 $O(1)$ 求出比 $a_i$ 小的前 $k-g(i)$ 数的和，记作 $m$。

将它们全部加到 $a_i$ 后，总和为 $a_i\times (k-g(i))$。因此操作次数为 $a_i\times (k-g(i))-m$。

考虑到每个数可能要操作 $a_i-1$ 次，总共最大可能操作是 $(a_i-1)^2$ 次，需要用 `long long` 类型。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll c,n,k,a[500007],a_[500007],b[500007];
int f(int i){
	int qwq=a[i];
	return n-(upper_bound(a_+1,a_+n+1,qwq)-a_-1)+1;
}

int g(int i){
	int qwq=a[i];
	return n-(lower_bound(a_+1,a_+n+1,qwq)-a_-1);
}

ll work(int i){
	ll qwq=f(i),awa=g(i);
	//cout<<qwq<<' '<<awa<<'\n';
	if(qwq<=k&&awa>=k){
		//debug;
		return 0;
	}
	else if(qwq>k){//增大 a[i] 
		int p=n-k+1;
		//cout<<p<<' ';
		//debug;
		return a_[p]-a[i];
	}
	else{//g(i)<k 增大k-awa 个小于a[i]的其他数 
		int p=n-awa+1;
		return (k-awa)*a_[p]-(b[p-(k-awa)]-b[p]);
	}
}

int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>c>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i],a_[i]=a[i];
    sort(a_+1,a_+n+1);
    for(int i=n;i;i--)b[i]=b[i+1]+a_[i];
    for(int i=1;i<=n;i++){
    	cout<<work(i)<<'\n';
	}
	return 0;
}
```

---

## 作者：sbno333 (赞：2)

这道题我们分类讨论。

不难证明，$f(i)\le g(i)$，因此我们分为三类。

* $f(i)\le k\le g(i)$
* $k\le f(i)\le g(i)$
* $f(i)\le g(i)\le k$

不难发现，对于第一种情况，一定是在排序后与第 $k$ 大的数相同的数。

对于第二种情况，排序后一定在第 $k$ 大的数后面，因此我们可以只增加第 $i$ 个数，使得其与第 $k$ 大数一样大，操作次数为第 $k$ 大数的值减去第 $i$ 个数，不难发现，我们可以将第一类和第二类一起写。

对于第三类，我们需要从大往小将所有小于第 $i$ 大的数，增加至第 $i$ 个数的大小，一直到第 $k$ 个数也被变为相应大小，考虑前缀和，假设要增加的数都是 $0$，增加的值为第 $i$ 个数乘要增加的数的数量（本来等于该数也可以考虑进来），这是假设的操作次数，减去这些数的和，就是答案。

由于多次使用第 $k$ 大，因此我们要排序。

```cpp
#include<bits/stdc++.h>
using namespace std;
int i;
struct st{
    long long num,s,e;//大小，编号，答案
}sd[1000009];
bool cmp(st a1,st a2){
    return a1.num>a2.num;
}
bool pmc(st a1,st a2){
    return a1.s<a2.s;
}
long long qz[1000009],T,n,k;
int main(){
    cin>>T>>n>>k;
    for(i=1;i<=n;i++){
        cin>>sd[i].num;
        sd[i].s=i;//方便排序
    }
    sort(sd+1,sd+1+n,cmp);//按大小排序
    for(i=k;i>=1;i--){
        qz[i]=qz[i+1]+sd[i].num;//到第k个数的和
    }
    for(i=1;i<k;i++){
        sd[i].e=(k-i)*sd[i].num-qz[i+1];//对于第三类
    }
    sd[k].e=0;
    for(i=k+1;i<=n;i++){//对于第二类，第一类合并进去
        sd[i].e=sd[k].num-sd[i].num;
    }
    sort(sd+1,sd+1+n,pmc);//变为原序列
    for(i=1;i<=n;i++){
        cout<<sd[i].e<<endl;//输出答案
    }
}
```

---

## 作者：Haoyue_06432 (赞：0)

首先整理数据，将数据重复的删去并记录重复几次。

先算出最小的 $f(i)$ 和 $g(i)$ 的编号位置，记为 $minf$ 和 $ming$。

再算出每个 $f(i)$ 与 $g(i)$，通过观察规律得出：

当 $k \le f(i)$ 时需要操作自身，使 $a_i = a_{minf}$。

当 $g(i) \le k$ 时需要操作后面比他小的数，使 $a_{i} = a_{i+1,ming}$，可以运用前缀和算出。

![](https://cdn.luogu.com.cn/upload/image_hosting/yc4sk0f9.png?x-oss-process=image/resize,m_lfit,h_180,w_360)

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll c,n,k,a[500005],f[500005],g[500005],b,x[500005],y[500005],minf,ming,s[500005],num[500005],d[500005];
map<ll,ll> ans;
bool cmp(ll a,ll b){return a>b;}
int main()
{
//	freopen("rank5.in","r",stdin);
//	freopen("rank5.out","w",stdout);
	scanf("%lld%lld%lld",&c,&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&x[i]);
		y[i]=x[i];
	}
	sort(x+1,x+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		if(a[b]!=x[i])a[++b]=x[i];
		d[b]++;		
	}
	for(int i=1;i<=b;i++)
	{
		f[i]=g[i-1]+1;
		g[i]=g[i-1]+d[i];
		if(f[i]>k&&f[i-1]<=k)minf=i-1;
		if(g[i]>=k&&g[i-1]<k)ming=i;
	}
	for(int i=b;i>1;i--)
	{
		num[i]=num[i+1]+d[i];
		s[i]=s[i+1]+num[i]*(a[i-1]-a[i]);
	}
	num[1]=num[2]+d[1];
	for(int i=1;i<=b;i++)
	{
		if(f[i]>k)ans[a[i]]=a[minf]-a[i];
		if(g[i]<k)ans[a[i]]=s[i+1]-s[ming+1]-(num[1]-k)*(a[i]-a[ming]);
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[y[i]]);
	return 0;
}
```

---

## 作者：Not_defined (赞：0)

本题思路：由于本题需要计算 $f_{i}$ 和 $g_{i}$，所以我们可以考虑直接从小到大排序，用一个结构体存一下这个数原来的位置，方便最后输出，后面就是模拟的过程。当 $f_{i}=k$ 或 $g_{i}=k$ 很显然是不用做任何操作的。当 $g_{i}<k$ 时，那么我们预先处理前缀和，将比当前的数小的 $k-g_{i}$个数改为 $g_{i}$。当 $f_{i}>k$ 时，那么我们将这个数压入队列中，直到找到一个最小的比它大的一个数，且这个数的 $f_{i}=k$ 或 $g_{i}=k$，将队列中的数取出，并令它们操作后等于当前这个数，因此操作次数就是两者之差。
### code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
struct node
{
	int pos,sum;
}a[N];
int c,n,k,tot[N],ans[N];
bool cmp(node s1,node s2)
{
	return s1.sum<s2.sum;
}
int query(int l,int r)
{
	return tot[r]-tot[l-1];
}
queue<int>q;
signed main()
{
	cin>>c>>n>>k;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].sum);
		a[i].pos=i;
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++)tot[i]=tot[i-1]+a[i].sum;
	for(int i=1;i<=n;i++)
	{
		int cnt1=i,cnt2=i;
	    while(a[cnt1].sum==a[i].sum)cnt1++;
	    while(a[cnt2].sum==a[i].sum)cnt2--;
		int g=n-cnt2;
		int f=n-cnt1+1+1;
		if(g==k||f==k)
		{
			ans[a[i].pos]=0;
			while(q.size())
			{
				int t=q.front();
				ans[a[t].pos]=a[i].sum-a[t].sum;
				q.pop();
			}
		}
		else
		{
			if(g<k)ans[a[i].pos]=(k-g)*a[i].sum-query(cnt2-k+g+1,cnt2);
			if(f>k)q.push(i);
		}
		//cout<<ans[a[i].pos]<<endl;
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<endl;
	return 0;
}
```


---

