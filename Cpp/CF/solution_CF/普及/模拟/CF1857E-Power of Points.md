# Power of Points

## 题目描述

You are given $ n $ points with integer coordinates $ x_1,\dots x_n $ , which lie on a number line.

For some integer $ s $ , we construct segments \[ $ s,x_1 $ \], \[ $ s,x_2 $ \], $ \dots $ , \[ $ s,x_n $ \]. Note that if $ x_i<s $ , then the segment will look like \[ $ x_i,s $ \]. The segment \[ $ a, b $ \] covers all integer points $ a, a+1, a+2, \dots, b $ .

We define the power of a point $ p $ as the number of segments that intersect the point with coordinate $ p $ , denoted as $ f_p $ .

Your task is to compute $ \sum\limits_{p=1}^{10^9}f_p $ for each $ s \in \{x_1,\dots,x_n\} $ , i.e., the sum of $ f_p $ for all integer points from $ 1 $ to $ 10^9 $ .

For example, if the initial coordinates are $ [1,2,5,7,1] $ and we choose $ s=5 $ , then the segments will be: $ [1,5] $ , $ [2,5] $ , $ [5,5] $ , $ [5,7] $ , $ [1,5] $ . And the powers of the points will be: $ f_1=2, f_2=3, f_3=3, f_4=3, f_5=5, f_6=1, f_7=1, f_8=0, \dots, f_{10^9}=0 $ . Their sum is $ 2+3+3+3+5+1+1=18 $ .

## 说明/提示

In the first test case we first choose $ s=x_1=1 $ , then the following segments are formed: $ [1,1] $ , $ [1,4] $ , $ [1,3] $ .

The powers of the points will be as follows: $ f_1=3, f_2=2, f_3=2, f_4=1, f_5=0 \dots $ The sum of powers of the points: $ 3+2+2+1+0+\dots+0=8 $ .

After that we choose $ s=x_2=4 $ . Then there will be such segments: $ [1,4] $ , $ [4,4] $ , $ [3,4] $ , and powers of the points are $ f_1=1, f_2=1, f_3=2, f_4=3 $ .

At the end we take $ s=x_3=3 $ and the segments look like this: $ [1,3] $ , $ [3,4] $ , $ [3,3] $ , the powers of the points are $ f_1=1, f_2=1, f_3=3, f_4=1 $ .

## 样例 #1

### 输入

```
3
3
1 4 3
5
1 2 5 7 1
4
1 10 100 1000```

### 输出

```
8 7 6
16 15 18 24 16
1111 1093 1093 2893```

# 题解

## 作者：ScottSuperb (赞：9)

## 解法分析
显然题目所要求的就是各段长度之和。那么我们将各点排序，先求出最小的点的答案。易得当点 $p_i$ 转移到 $p_{i+1}$ 时，实际上是与 $p_{i+1}$ 左边的每个点都增加了这一段的长度、右边都减少了，因此可递推得出答案。
## 代码
快读快写函数定义已省略。
```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long
typedef pair<int, int> pii;
pii p[200005];
ll res[200005];

int main() {
  int t = read();
  ll ans, n;
  while (t--) {
    n = read(), ans = 0;
    for (int i = 0; i < n; ++i) p[i] = {read(), i};
    sort(p, p + n);
    for (int i = 0; i < n; ++i) ans += p[i].first - p[0].first + 1;
    res[p[0].second] = ans;
    for (int i = 1; i < n; ++i) {
      ans = ans + (i * 2 - n) * (p[i].first - p[i - 1].first);
      res[p[i].second] = ans;
    }
    for (int i = 0; i < n; ++i) write(res[i], ' ');
    pc('\n');
  }
  return 0;
}
```

---

## 作者：2huk (赞：6)

# E. [Power of Points](https://codeforces.com/contest/1857/problem/E)

好题耶！

## Description

数轴上有 $n$ 条线段，第 $i$ 条线段的端点为 $x_i$ 和 $s$。

定义函数 $f(p)$ 表示有多少个线段覆盖了点 $p$。

给定 $x$，对于每个 $s = x_i$，求出 $\sum_{p = 1}^{10^9} f(p)$ 的值。

## Solution

第一步转化很简单，由于题目中的 $f$ 函数是从点的角度考虑的，并不方便计算，因此我们换一个看待问题的角度，即从线段的角度分析。

对于 $\sum_{p = 1}^{10^9} f(p)$ 这个式子，表示对于每个点，有多少个线段覆盖了它，也可以理解成每个线段覆盖的点的总数，也就是线段的总长度。

对于一条线段，如果 $x_i < s$，那么其长度为 $s - x_i + 1$，反之为 $x_i - s + 1$。因此线段总长为 $\sum_{i = 1}^n (|x_i - s| + 1) = \sum_{i = 1}^n (|x_i - s|) + n$。因此问题来到了如何快速求解 $\sum_{i = 1}^n (|x_i - s|)$ 上。

还是上面的分类。对于 $x_i < s$ 的情况，其总贡献为 $\sum_{i = 1}^{p - 1} (s - x_i) = s \times p - \sum_{i = 1}^{p - 1} x_i$，其中 $p$ 是 $x_i < s$ 的数量。$x_i \ge s$ 同理，其总贡献为 $\sum_{i = p + 1}^n(x_i - s) = \sum_{i = p + 1}^n x_i  - s \times (n - p)$。

由于 $s$ 是某一个 $x_i$，所以上面的 $p$ 实际上就是当前的 $x_i$ 的 $i - 1$。

这时会发现，$\sum$ 中只有 $x_i$ 了，所以只需要在计算前维护前缀和和后缀和即可。

整理一下，答案为：
$$
s \times (i - 1) - pre_{p - 1} + suf_{p + 1} - s \times (n - p)
$$
其实你可以继续化简，但是貌似没什么必要。

## Code

注意一些代码细节，读入的 $x$ 不一定是有序的，但是维护前后缀和时需要升序排序，但是输出时有需要排回原序。所以你需要开一个 `map` 存储原先元素在序列中的位置在排序后的位置是哪。

```cpp
int T, n;
int pre[N], suf[N];
PII x[N];
map<int, int> p;
 
void Solve()
{
	p.clear();
	n = read();
	
	fup (i, 1, n)
		x[i] = {read(), i};
	
	sort(x + 1, x + n + 1);
	pre[0] = suf[n + 1] = 0;
	
	fup (i, 1, n)
		pre[i] = pre[i - 1] + x[i].first,
		p[x[i].second] = i;
	
	fdw (i, n, 1)
		suf[i] = suf[i + 1] + x[i].first;
	
	sort(x + 1, x + n + 1, [&](PII a, PII b)
	{
		return a.se < b.se;
	});
	
	fup (i, 1, n)
	{
		int k = x[i].first * (p[i] - 1) - pre[p[i] - 1] + suf[p[i] + 1] - (n - p[i]) * x[i].first + n;
		printf("%d ", k);
	}
	
	puts("");
	return;
}
```

---

## 作者：chlchl (赞：4)

纪念一下，晚上在关灯的机房 AC 五道题，打到 1 点钟，然后直接开锁铁门，冲回宿舍的经历（doge）。

其实这道题做过莫队的都应该能马上想到思路。

## Solution
题目要求对于每一个 $s=x_i$ 都输出答案，并且数据达到了惊为天人的 $2\times 10^5$，显然并不可能每次都求解答案。

我们只能算出当 $s$ 从 $x_i\rightarrow x_{x+1}$ 时，对答案的影响。

然后那个 $10^9$ 是吓人的，实际上将 $x$ 从小到大排序后，$f(i)\ne 0$ 的地方只会介于 $[x_1,x_n]$，其它地方根本就没有线段。

那么我们来算一下变化量吧。

首先，$n$ 个端点将这条线段 $[x_1,x_n]$ 分成了 $n-1$ 段。

如果不考虑端点，初始状态，第 $i$ 段分别有 $n-1,n-2,n-3,\cdots,1$ 条线段覆盖。

以 $n=5$ 为例，初始时四段分别有 $4,3,2,1$ 条线段。

- $s=x_2$ 时，第 $1$ 段由 $4$ 条变成 $1$ 条。
- $s=x_3$ 时，第 $2$ 段由 $3$ 条变成 $2$ 条。
- $s=x_4$ 时，第 $3$ 段由 $2$ 条变成 $3$ 条。
- $s=x_5$ 时，第 $4$ 段由 $1$ 条变成 $4$ 条。

![](https://cdn.luogu.com.cn/upload/image_hosting/ihvhpe93.png?x-oss-process=image/resize,m_lfit,h_400,w_600)

并且我们发现，变换前后的两个数，和刚好是 $5$。

设第 $i$ 段被 $k_i$ 条线段覆盖。那么当 $x_i\rightarrow x_{i+1}$ 时，$k_i\leftarrow n-k_i$，其它不变。

而初始状态允许我们 $O(n)$ 算出来。

最后是端点的问题。

画图可知，初始状态时，与它前面一段的线段覆盖数是一样的（因为线段是闭区间），所以我们将每一段定成左开右闭区间（即第 $i$ 段为 $(x_i,x_{i+1}]$），然后计算答案。

最后你发现漏了 $x_1$ 没算。显然 $n$ 条线段都覆盖了 $x_1$，所以答案 $+n$。

然后你发现，对于每一次变换，都有且仅有一个点被覆盖 $n$ 次。也就是说，一旦我们在初始状态计算了端点的覆盖数量，后面就不用管了，因为一定不变。

所以我们就得到了 $O(1)$ 计算变化的方法。时间复杂度 $O(n\log n+n)$，注意 $x$ 不一定有序，要排序。

排序时下标的变化，要开 ``long long`` 啥的，自己注意下就好，这些都是小细节。

然后就做完了。代码中的一些下标与上文有所区别，请小心观看。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
 
const int N = 2e5 + 5;
int T, n;
ll d[N], ans[N];
struct pos{
	ll v, id;
	bool operator < (const pos &p) const {
		return v < p.v;
	}
} a[N];
 
 
void solve(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++)
		scanf("%lld", &a[i].v), a[i].id = i;
	sort(a + 1, a + 1 + n);
	ans[a[1].id] = n;
	for(int i=1;i<n;i++)
		d[i] = a[i + 1].v - a[i].v, ans[a[1].id] += (n - i) * d[i];
	for(int i=2;i<=n;i++){//现在要改变的是 d[i - 1] 
		ll now = i - 1;
		ans[a[i].id] = ans[a[i - 1].id] + 1ll * (now - 1ll * (n - i + 1)) * d[i - 1];
	}
	for(int i=1;i<=n;i++)
		printf("%lld ", ans[i]);
	printf("\n");
}
 
int main(){
	cin >> T;
	while(T--)
		solve();
	return 0;
}

```


---

## 作者：I_am_kunzi (赞：3)

# CF1857E 题解

### 题目翻译

数轴上有 $ n $ 个点，位置分别为 $ a_i $，现在求 $ n $ 个结果，第 $ i $ 个结果是 $ \sum_{j = 1} ^ n [a_j , a_i]$，输出这 $ n $ 个结果。

### 题目思路

暴力的方法是每次计算出 $ n $ 段的长度和，复杂度 $ O(n ^ 2)$，显然超时。

我们将数组从大到小排序，并按照与 $ a_i $ 的大小关系将原式分为两部分，分别为 $ \sum_{j = 1} ^ i (a_i - a_j + 1) $ 和 $ \sum_{j = i + 1} ^ n (a_j - a_i + 1)$。第 $ i $ 个结果显然是两式之和。

接下来将式子化简，先提出两个求和函数中的 $ 1$，因为这一项被累加 $ n $ 次，所以式子变为 $ n + \sum_{j = 1} ^ i (a_i - a_j) + \sum_{j = i + 1} ^ n (a_j - a_i)$。

提出每项中的 $ a_i$，式子变为 $ n - \sum_{j = 1} ^ i a_j + i \cdot a_i + \sum_{j = i + 1} ^ n a_j - (n - i) \cdot a_i$。

合并同类项，式子变为 $ n - \sum_{j = 1} ^ i a_j + (2 \times i - n) \cdot a_i + \sum_{j = i + 1} ^ n a_j$。

改变下位置，式子变为 $ n + (2 \times i - n) \cdot a_i - \sum_{j = 1} ^ i a_j + \sum_{j = i + 1} ^ n a_j$。

其中 $ n $ 和 $ (2 \times i - n) \cdot a_i $ 可以 $ O(1) $ 计算，难点在后面两项，这两项不是加法关系，所以很难暴力计算，但是每次 $ i $ 变大时，第一项都会增加 $ a_{i + 1}$，第二项会减少 $ a_{i + 1}$，所以预处理即可实现 $ O(1) $ 计算。

### 题目代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
pair < long long , long long > a[200005]; // 第一项为 a[i]，第二项存编号，因为排序后原来的编号被打乱，只能提前存储
long long ans[200005];
signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		long long fs = 0 , bs = 0; // fs 为第一项值，bs 为第二项值
		int n;
		cin >> n;
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a[i].first; // 输入值
			a[i].second = i; // 预处理编号
			bs += a[i].first; // 累加到 bs 中，因为每次操作前改变 fs 与 bs 的值，所以这里不需特判第一项
		}
		sort(a + 1 , a + n + 1); // pair < first , second > 默认以 first 为第一关键字，second 为第二关键字
		for(int i = 1 ; i <= n ; i++)
		{
			bs -= a[i].first; // 后面删掉一项
			fs += a[i].first; // 前面加上一项
			ans[a[i].second] = n + a[i].first * (2 * i - n) - fs + bs; // 处理每一项的值，下标就应该是 a[i].second
		}
		for(int i = 1 ; i <= n ; i++)
		{
			cout << ans[i] << " \n" [i == n]; // 后面这一项是简写，当 i != n 时应该输出空格，此时 bool 返回 0 ，输出第 0 个下标的值，即 ' '；当 i == n 时应该输出换行，此时 bool 返回 1，输出第 1 个下标的值，即 '\n'
		}
	}
    return 0;
}

```


---

## 作者：Wf_yjqd (赞：1)

还是很简单。

------------

考虑按数轴上的位置排序。

$\sum f_p=\sum\limits_{i=1}^n\left|x_i-s\right|+n$

考虑转化掉绝对值，分左右两种情况讨论。

维护位置的前缀和 $qzh_i$ 和后缀和 $hzh_i$。

若当前 $s$ 为 $x_i$，化简得 $\sum f_p=(s+1)\times(n-1)-qzh_{i-1}+hzh_{i+1}$。

最后按原顺序输出每一位置的答案即可。

------------

没开 long long 一发罚时。。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=2e5+84;
struct Point{
    ll ad,id,ans;
    friend bool operator<(Point xy,Point zb){
        return xy.ad<zb.ad;
    }
}p[maxn];
ll T,n,qzh[maxn],hzh[maxn];
inline bool cmp(Point xy,Point zb){
    return xy.id<zb.id;
}
int main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        for(ll i=1;i<=n;i++){
            scanf("%lld",&p[i].ad);
            p[i].id=i;
        }
        sort(p+1,p+n+1);
        for(ll i=1;i<=n;i++)
            qzh[i]=qzh[i-1]+p[i].ad;
        hzh[n+1]=0;
        for(ll i=n;i>=1;i--)
            hzh[i]=hzh[i+1]+p[i].ad;
        for(ll i=1;i<=n;i++)
            p[i].ans=p[i].ad*(i-1)-qzh[i-1]-1+hzh[i+1]-p[i].ad*(n-i)+n+1;
        sort(p+1,p+n+1,cmp);
        for(ll i=1;i<=n;i++)
            printf("%lld ",p[i].ans);
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：W_s_W (赞：1)

### 更新
- 2023.8.8 补了个空格。

感谢提出问题！

---

### 思路
首先将 $a$ 数列排序。  
显然 $p<a_1$ 或 $p>a_n$ 的时候，点 $p$ 不在任何线段上。  

推一下式子。  
我们记 $s=a_i$ 时的答案为 $sum_i$。  
首先算出当 $s=a_1$ 时的答案：
$$(a_1-a_1+1)+(a_2-a_1+1)+\dots+(a_n-a_1+1)$$
$$=n+(a_1-a_1)+(a_2-a_1)+\dots+(a_n-a_1)$$  

当 $s=a_2$ 时，$s$ 向右移动了 $a_2-a_1$ 个单位。  

- 对于所有的 $a_j (j<2)$，从 $a_j$ 到 $s$ 的线段覆盖的点增加了 $a_2-a_1$ 个。那么一共增加了 $(a_2-a_1)\times (2-1)$ 个点。
- 对于所有的 $a_j (j\ge i)$，从 $a_j$ 到 $s$ 的线段覆盖的点减少了了 $a_2-a_1$ 个。那么一共减少了了 $(a_2-a_1)\times (n-2+1)$ 个点。


所以当 $s=a_i$ 时，答案为:
$$sum_{i-1}+(a_i-a_{i-1})\times (i-1)-(a_i-a_{i-1})\times (n-i+1)$$
$$=sum_{i-1}+(a_i-a_1)\times (i\times2-n-2)$$

根据式子递推即可。

**注意要开 `long long`。**

---
### 代码和[提交记录](https://codeforces.com/contest/1857/submission/217701537)
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x;
	int id;
}a[200003];
int t,n;
long long sum;
long long ans[200003];
bool cmp(node x,node y){
	return x.x<y.x;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		sum=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i].x);
			a[i].id=i;
		}
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++){
			sum+=a[i].x-a[1].x+1;
		}
		ans[a[1].id]=sum;
		for(int i=2;i<=n;i++){
			sum+=((i<<1)-2-n)*(long long)(a[i].x-a[i-1].x);
			ans[a[i].id]=sum;
		}
		for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：LCat90 (赞：1)

转换一下题意，设当前点为 $i$，就是求 $n+\sum_{j=1}^n |a_i-a_j|$。

先从小到大排个序，然后如果 $j<i$，则直接拆开绝对值，这些 $j$ 的贡献为：$ (i-1)\times a_i-\sum_{j=1}^{i-1} a_j $。

反之如果 $j>i$，则反过来：$ \sum_{j=i+1}^{n}-(n-i)\times a_i$。

区间和用前缀和求。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
int t, n, ot[N], pre[N]; 
struct node {
	int x, id;
} a[N];
bool cmp(node a, node b) { return a.x < b.x; } 
signed main() {
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 1;i <= n; ++i) scanf("%lld", &a[i].x), a[i].id = i;
		sort(a + 1, a + n + 1, cmp);
		for(int i = 1;i <= n; ++i) pre[i] = pre[i - 1] + a[i].x;
		for(int i = 1;i <= n; ++i) {
			int x = n;
			x += (a[i].x * (i - 1)) - pre[i - 1];
			x += (pre[n] - pre[i]) - (a[i].x) * (n - i);
			ot[a[i].id] = x;
		} 
		for(int i = 1;i <= n; ++i) printf("%lld ", ot[i]); 
		puts("");
	}
	return 0;
}

```

---

## 作者：NBest (赞：0)

## 思路
我们发现每个点的答案其实是它与之前的点的答案加上与后面的点的答案加上与自己的答案。而与前面和与后面的前后缀答案都是可以通过递推的方式得到的，我们令 $pre_i$ 表示 $i$ 点的前缀答案，$sub_i$ 表示 $i$ 点的后缀答案，$x_i$ 表示 $i$ 点的坐标，那么有：
$$pre_i=pre_{i-1}-(x_i-x_{i-1})\times(n-i+1)-1\\ sub_i=sub_{i+1}-(x_{i+1}-x_i)\times i-1$$

代码有点丑，见谅。
## $Code$
```cpp
struct node{
    ll v,id,ans1,ans2;
    inline bool operator <(const node &w)const{
        return v<w.v;
    }
}a[200005];
ll ans[200005];
ll T,n;
int main(){
    for(T=read();T--;){
        n=read();
        for(ll i=1;i<=n;i++){
            a[i].v=read();
            a[i].id=i;
            a[i].ans1=a[i].ans2=0;
        }
        sort(a+1,a+1+n);
        for(ll i=2;i<=n;i++){
            a[1].ans1+=a[i].v-a[1].v+1;
        }
        for(ll i=1;i<n;i++){
            a[n].ans2+=a[n].v-a[i].v+1;
        }
        for(ll i=2;i<n;i++){
            a[i].ans1+=a[i-1].ans1-1ll*(a[i].v-a[i-1].v)*(n-i+1)-1;
        }
        for(ll i=n-1;i>=2;--i){
            a[i].ans2+=a[i+1].ans2-1ll*(a[i+1].v-a[i].v)*i-1;
        }
        for(ll i=1;i<=n;i++)ans[a[i].id]=a[i].ans1+a[i].ans2;
        for(ll i=1;i<=n;i++){
            printf("%lld ",ans[i]+1);
        }
        puts("");
    }
}
```

---

## 作者：aeiouaoeiu (赞：0)

对于一个 $s$，线段 $[s,x_i]$ 的贡献显然是被该线段覆盖的点的数量，即 $|x_i-s|+1$。

考虑先将 $x$ 按升序排序，那么对于 $x_i$，我们要求的就是 $(\sum^{i-1}_{k=1}{x_i-x_k+1})+(\sum^n_{k=i+1}{x_k-x_i+1})+1$（最后的 $1$ 其实是 $x_i-x_i+1$）。

我们把式子中的 $x_i$ 和 $1$ 拎出来，变为 $(i-1-n+i)x_i-\sum^{i-1}_{k=1}{x_k}+\sum^n_{k=i+1}{x_k}+n$，求和用前缀和计算即可。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
//typedef __int128 dll;
typedef long double db;
const int maxn=200007,dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
const ll inf=1300000007ll,p=1000000007,hsp=993244853,hsb=1145141;
const ll ee=1000000000000000007ll;
ll n,ans[maxn],sum[maxn];
pair<ll,ll> pir[maxn];
int main(void){
	//freopen("fileinput.in","r",stdin);
	//freopen("fileoutput.out","w",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll T=1;
	cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n;
		for(int i=1;i<=n;i++){cin>>pir[i].first; pir[i].second=i;}
		sort(pir+1,pir+1+n);
		for(int i=1;i<=n;i++) sum[i]=sum[i-1]+pir[i].first;
		for(int i=1;i<=n;i++) ans[pir[i].second]=pir[i].first*(2*i-1-n)-sum[i-1]+sum[n]-sum[i]+n;
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

