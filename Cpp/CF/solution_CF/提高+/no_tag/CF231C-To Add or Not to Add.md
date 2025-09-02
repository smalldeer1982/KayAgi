# To Add or Not to Add

## 题目描述

A piece of paper contains an array of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Your task is to find a number that occurs the maximum number of times in this array.

However, before looking for such number, you are allowed to perform not more than $ k $ following operations — choose an arbitrary element from the array and add $ 1 $ to it. In other words, you are allowed to increase some array element by $ 1 $ no more than $ k $ times (you are allowed to increase the same element of the array multiple times).

Your task is to find the maximum number of occurrences of some number in the array after performing no more than $ k $ allowed operations. If there are several such numbers, your task is to find the minimum one.

## 说明/提示

In the first sample your task is to increase the second element of the array once and increase the fifth element of the array twice. Thus, we get sequence $ 6,4,4,0,4 $ , where number $ 4 $ occurs $ 3 $ times.

In the second sample you don't need to perform a single operation or increase each element by one. If we do nothing, we get array $ 5,5,5 $ , if we increase each by one, we get $ 6,6,6 $ . In both cases the maximum number of occurrences equals $ 3 $ . So we should do nothing, as number $ 5 $ is less than number $ 6 $ .

In the third sample we should increase the second array element once and the fifth element once. Thus, we get sequence $ 3,2,2,2,2 $ , where number $ 2 $ occurs $ 4 $ times.

## 样例 #1

### 输入

```
5 3
6 3 4 0 2
```

### 输出

```
3 4
```

## 样例 #2

### 输入

```
3 4
5 5 5
```

### 输出

```
3 5
```

## 样例 #3

### 输入

```
5 3
3 1 2 2 1
```

### 输出

```
4 2
```

# 题解

## 作者：Buried_Dream (赞：6)

## Soultion	

首先有一个很明显的贪心。

将一个数加成 $x$，选的数都是比他小的最大的几个数才会最优。

我们用双指针来移动，$r$ 所指的位置表示将数替换成 $a_r$。

对于如何判断当前的 $l$ 合不合法，我们用前缀和来判断即可。

当前移动到 $[l,r]$，区间都变成 $a_r$ 的和为 $(r - l + 1) \times a_r$，

实际上的和为 $qzh_r - qzh_{l-1}$，判断一下两者的差值和 $k$ 的关系就行了。

写完之后比最优解第二快了 $300+ms$，~~虽然最优解第二也是我~~

```cpp
int n, k, a[N], qzh[N];
int maxv, maxnum = 0;

signed main() 
{
	n = read(), k = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) qzh[i] = qzh[i - 1] + a[i];
	int l = 1, r = 1;
	while(l <= r && r <= n) {
		if(a[r] * (r - l + 1) - (qzh[r] - qzh[l - 1]) <= k) {
			if(r - l + 1 > maxnum) maxv = a[r], maxnum = r - l + 1;
			r++;
		}	
		else l++;
	}
	printf("%lld %lld\n", maxnum, maxv);
	return 0;
}
```

---

## 作者：ZMQ_Ink6556 (赞：4)

## CF231C To Add or Not to Add 题解
### 解题思路
明显这道题可以用**贪心**的思路解决。

首先，我们发现，只能加 $k$ 次，那么最优的方法肯定是优先加距离 $a_i$ 近的数。

但是，我们发现这样枚举复杂度为 $O(n^2k)$，显然是会 $\text{TLE}$。所以，我们要对现有的思路进行优化。

我们可以尝试使用**双指针**优化现有的算法，如果这一段所需要的操作 $\le k$，那么将右指针 $r$ 右移，否则将左指针 $l$ 右移。现在成功将复杂度降为了 $O(n^2)$，可是面对 $1\le n\le 10^5$ 的数据范围还是有点不够。

此时只能继续优化。我最终用上了**前缀和**优化，降低查询一段范围内需要操作次数的复杂度，通过**打擂台**记录答案，最终将查询的复杂度降为 $O(n)$。

此时，包括排序在内，整个程序的复杂度是 $O(n \log n)$，可以 $\text{AC}$。

话说这道题的前缀和也可以换成 ST 表（虽然没有人会去这样做）。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct p
{
	int a , b;
}ans;
long long n , k , a[100005] , b[100005] , l , r;
int main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    for(int i = 1 ; i <= n ; i++)
    {
    	cin >> a[i];
	}
	sort(a + 1 , a + n + 1);
	for(int i = 1 ; i <= n ; i++)
	{
		b[i] = b[i - 1] + a[i];
	}
	l = 1;
	r = 1;
	while(r <= n)
	{
		if(a[r] * (r - l) + a[r] - b[r] + b[l - 1] <= k)
		{
			if(ans.a < r - l + 1)
			{
				ans.a = r - l + 1;
				ans.b = a[r];
			}
			r++;
		}
		else
		{
			l++;
		}
	}
	cout << ans.a << ' ' << ans.b;
    return 0;
}
```

---

## 作者：AKPC (赞：4)

### 思路
首先给 $a$ 数组从小到大排序。显然，如果要把数字改成 $a_i$，显然只能更改 $a_1\sim a_{i-1}$ 的数字。首先暴力枚举这个 $i$，考虑将 $a_j\sim a_i(j\leq i)$ 改为 $a_i$。显然 $j$ 越小，需要更改的次数越大，所以具有**单调性**，考虑**二分答案**。

二分这个 $j$，令 $l=1$，$r=i$，得出 $mid=\dfrac{l+r}{2}$ 之后，考虑这个 $mid$，如果可以就让 $j$ 继续考虑更小的值，$mid\to r$，反之只能考虑更大的 $j$，$mid+1\to l$。最后 $l=r$ 的时候，此时 $l$（或者 $r$，因为它们的值是相等的）就是最优的 $j$ 了。记录 $i-l+1\to tip_i$，即最多可以将 $i-l+1$ 个数改为 $a_i$。

怎么快速判断 $mid$ 是否可取？如果让 $a_{mid}\sim a_i$ 变成 $a_i$，需要的次数就是操作后 $a_{mid}\sim a_i$ 的值减去操作前 $a_{mid}\sim a_i$ 的值。操作后的值显然是 $a_i\times (i-mid+1)$。问题变成了怎么快速计算操作前 $a_{mid}\sim a_i$ 的值，显然就要用到前缀和了。定义 $f_x=\sum_{t=1}^xa_t$，显然 $f_i-f_{mid-1}$ 就是 $\sum_{t=mid}^ia_t$ 的值，即操作前的值。

最后统计每个 $tip_i$ 的最大值即可。注意，如果最大值有多个，那么取最小的 $i$ 作为答案。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x=0;bool f=1;register char c=getchar();
    while (c<48||c>57){if(c=='-') f=0;c=getchar();}
    while (c>=48&&c<=57){x=x*10+(c^48);c=getchar();}
    return f?x:-x;
}
int n=read(),k=read(),a[100001],f[100001],tip[100001],ans;
signed main(){
	for (int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	for (int i=1;i<=n;i++) f[i]=f[i-1]+a[i];
	for (int i=1;i<=n;i++){
		int l=1,r=i;
		while (l<r){
			int mid=(l+r)/2;
			if (a[i]*(i-mid+1)-f[i]+f[mid-1]<=k) r=mid;
			else l=mid+1;
		}
		tip[i]=i-l+1;
		if (tip[i]>tip[ans]) ans=i;
	}
	cout<<tip[ans]<<' '<<a[ans];
	return 0;
}
```


---

## 作者：XL4453 (赞：3)

### 解题思路：

双指针（或者叫尺取法）以及一个显然的贪心，不算难。

首先考虑贪心部分，假设当前需要将最多的值加到 $a_i$，那么一定选择比 $a_i$ 小的且最大的若干个，否则将一个相对小的换成大的一定可以在价值不变得前提下减少需要使用的代价，以便其他的值加到 $a_i$。

然后考虑尺取法，若将当前的 $a_r$ 能取到的最远的左端点设为 $l$，将 $r$ 向右移动后 $l$ 一定不会向左移动，所以直接用一个尺取法来做，总复杂度是 $O(n)$ 的，完全可以通过本题。 

---

此外，如果不用尺取法，而采用枚举需要加到的值然后二分位置也可以，不过那样的复杂度是 $O(nlogn)$ 的，没有尺取法优秀。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,a[100005],sum[100005],ans,k,num;
bool check(long long l,long long r){
	return a[r]*(r-l+1)-sum[r]+sum[l-1]<=k;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(long long i=1;i<=n;i++)scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	long long l=1;
	ans=-1;
	for(long long rr=1;rr<=n;rr++){
		sum[rr]=sum[rr-1]+a[rr];
		while(!check(l,rr))l++;
		if(ans<rr-l+1){
			ans=rr-l+1;
			num=a[rr];
		}
	}
	printf("%lld %lld\n",ans,num);
	return 0;
}
```


---
### 闲话：

标题玩梗：$\text{To add or not to add,that's a question.}$ （加还是不加，这是个问题）

---

## 作者：hongshixiaobai (赞：2)

# CF231C To Add or Not to Add 题解
[传送门](https://www.luogu.com.cn/problem/CF231C)
## 思路
显而易见，

1. 只有比 $n$ 小的数才能修改成 $n$。
2. 把更接近 $n$ 的数修改成 $n$ 的代价更小。
3. 修改成原数组中的数比修改成其他数更优。

考虑双指针。

先排序，然后打一个前缀和，如果不能把左指针 $l$ 到右指针 $r$ 之间的范围都修改为 $a_r$，说明区间太大，左指针 $+1$。否则更新答案，右指针 $+1$。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005],n,k,l,r,pre[100005],ans1,ans2,i;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
	cin>>n>>k;
	for(i = 1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(i = 1;i<=n;i++)
	{
		pre[i] = pre[i-1]+a[i];
	}
	l = r = 1;
	while(l<=r&&r<=n)
	{
		if((r-l+1)*a[r]-pre[r]+pre[l-1]>k)l++;
		else 
		{
			if(r-l+1>ans1)
			{
				ans1 = r-l+1;
				ans2 = a[r];
			}
			r++;
		}
	}
	cout<<ans1<<' '<<ans2;
}
```

---

## 作者：_byta (赞：2)

首先肯定会把数组排序一遍，之后我们考虑相邻两个不同的数之间答案的变化。

我们设前一个为 $x$ 后一个为 $y$，接下来我们考虑众数出现次数的变化，由于数变大了，所以我们要增加一的次数也变大了。

这时有可能当上一个数作为众数时向左能扩展的最远的数在这个数作为众数时就不能扩展到了（有点绕，建议多读几遍），我们可以从上一个数向左能扩展到的最远的位置开始向后扫直到加一的次数在 $k$ 以内即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, a[N], b[N], c[N], w = -1;
inline int read()
{
    register int x = 0, f = 1;
	char ch = getchar();
    while(!isdigit(ch))
	{
		if(ch == '-') f=-1;
		ch = getchar();
	}
    while(isdigit(ch))
	{
		x=(x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
    return x * f;
}
signed main()
{
    n = read(); k = read();
    for(int i = 1; i <=n ; i++)
	{
	    a[i] = read();
	}
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i++)
    {
        while( r + p * (a[i] - a[i - 1]) > k)
        {
            r = r - (a[i - 1] - a[i - p]);
            p--;
        }
        r += p * (a[i] - a[i - 1]);
        p++;
        if(p > w)
        {
            w = p;
			ans = a[i];
		}
    }
    cout << w << " " << ans;
}


```



---

## 作者：Graphcity (赞：1)

## 思路

首先可以将 $a$ 数组降序排序。可以发现，排完序之后，如果想要让 $a_i$ 出现的次数最多，只能够让 $a_{i+1}\sim a_n$ 的数进行 +1 操作，不妨 **二分答案**。对于每个 $i\ (1\le i \le n)$，二分在操作数 $\le k$ 的情况下，最多可以让多少个数统一为 $a_i$ 。

二分的单调性在于：让 $a_i\sim a_{i+j}$ 统一的次数，一定比让 $a_i\sim a_{i+j+k}\ (i,j,k\ge 1)$ 统一的次数相同或者更低。

设 $sum_i=\sum_{k=1}^ia_k$，那么让 $a_x\sim a_{y}\ (1\le x\le y \le n)$ 统一的次数就为 $a_x\times (y-x+1)-(sum_y-sum_{x-1})$。

最后比较出最小值，输出即可。注意：

- 一定要开 `long long`
- 二分时注意 `mid=(l+r+1)/2`
- 注意在统一次数相同时，选择统一数的最小值作为答案

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Maxn=1e5;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,k,a[Maxn+5],sum[Maxn+5];
int cnt[Maxn+5],ans;
inline int cmp(int x,int y){return x>y;}

signed main()
{
    n=read(),k=read();
    for(int i=1;i<=n;++i) a[i]=read();
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;++i)
    {
        int l=i,r=n;
        while(l<r)
        {
            int mid=(l+r+1)/2;
            if(a[i]*(mid-i+1)-(sum[mid]-sum[i-1])<=k)
                l=mid;
            else r=mid-1;
        }
        cnt[i]=l-i+1;
        if(cnt[i]>=cnt[ans]) ans=i;
    }
    printf("%lld %lld",cnt[ans],a[ans]);
    return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路：
暴力显然是不行的，考虑优化。

使用双指针进行优化。主要思想是如果目前选中的区间 $[l,r]$ 所需要的操作次数小于等于 $k$，那么区间可以扩大，先更新一下答案，再执行 $r \gets r + 1$。如果大于 $k$，说明这个区间不行，缩小范围，执行 $l \gets l + 1$。

问题来了：如何判断这个区间行不行？当然是这个区间所要加到的最终值乘上区间元素个数（$r-l+1$）减去区间所有元素的和。因为如果有多个满足条件的数字，输出值最小的一个，所以这个区间所要加到的最终值设为区间最大值即可。不能暴力，所以区间所有元素的和用前缀和优化即可。因为要用前缀和优化，所以要先排序。

那么如何求区间最大值呢？由于数组不会改变，那么这不就是一个 RMQ 问题吗？RMQ 问题可以直接用 ST 表解决。（当时竟然忘了数组已经排完序了，所以无脑用了 ST 表，萌新不要被误导，实际上 $a_r$ 就是最大值）

最后，不开 long long 见祖宗！
### 代码（无脑 ST 表）：
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define reg register

const int LOGN = 21,MAXN = 1e5 + 1;
// sparse-table
ll f[MAXN][LOGN+1],ln[MAXN+1],s;
// main
ll n,k,a[MAXN],sum[MAXN];

int ans1,ans2;

inline void init()//初始化
{
    reg int i,j;
    //init:ans
    ans1 = INT_MIN;
    ans2 = INT_MAX;
    //init:sparse-table（即 ST 表初始化，懒得打汉字）
    ln[1] = 0;
	ln[2] = 1;
 	for(i = 3;i <= n;++i)
   	ln[i] = ln[i>>1] + 1;
    for(j = 1;j <= ln[n];++j)
 		for(i = 1;i <= n - (1 << j) + 1;++i)
     		f[i][j] = max(f[i][j-1], f[i+(1<<(j-1))][j-1]);
}

ll rmq(int x,int y)//区间最大值
{
   reg ll s = ln[y-x+1];
   return max(f[x][s], f[y-(1<<s)+1][s]);
}

signed main()
{
    reg int i,j;
    //input
    scanf("%lld%lld",&n,&k);
    for(i = 1;i <= n;++i)
        scanf("%lld",&a[i]);
    //sort
    sort(a+1,a+n+1);
    //前缀和
    for(i = 1;i <= n;++i)
    {
        f[i][0] = a[i];
        sum[i] = sum[i-1] + a[i];
    }
    init();
    //main
  	for(i = 1,j = 1;j <= i && i <= n;)
    {
        if(rmq(j,i) * (i-j+1) - sum[i] + sum[j-1] <= k)//判断条件，可以
        {
            if(ans1 < i-j+1)//更新答案
                ans1 = i-j+1,ans2 = rmq(j,i);
			++i;
        }
        else//不可以
            ++j;
    }
    printf("%d %d",ans1,ans2);
  	return 0;
}
```
### 代码（正解）：
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define reg register

const int MAXN = 1e5 + 1;
ll n,k,a[MAXN],sum[MAXN];

int ans1,ans2;

signed main()
{
    reg int i,j,ret;
    scanf("%lld%lld",&n,&k);
    for(i = 1;i <= n;++i)
        scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    for(i = 1;i <= n;++i)
        sum[i] = sum[i-1] + a[i];
    ans1 = INT_MIN;
    ans2 = INT_MAX;
  	for(i = 1,j = 1;j <= i && i <= n;)
    {
        if(a[i] * (i-j+1) - sum[i] + sum[j-1] <= k)
        {
            if(ans1 < i-j+1)
                ans1 = i-j+1,ans2 = a[i];
			++i;
        }
        else
            ++j;
    }
    printf("%d %d",ans1,ans2);
  	return 0;
}
```
因结构与上面代码相似，不再加注释。

---

## 作者：QWQ_123 (赞：0)

考虑贪心。

就是假设我们钦定在变成数字 $x$ 并且操作次数 $\le k$ 的数的个数最大时多少。

由于只能 $+1$，所以考虑 $\le x$ 的数字，那么我们一定是按照从大到小的顺序排序，然后正着选，因为每个数字所需要的操作次数依次递增。

然后考虑那些数字可能是最优解，那么我们发现，最优解一定可以在某个 $a_i$ 中取到，因为假设最优解最大值为 $t$，而选的这些数字做大为 $p$ 且 $p \not = t$（否则如果 $p=t$，那么就是 $a_i$ 中的数了），那么我们发现将所有数字都只增加到 $p$，那么总个数不变，并且所需操作次数更少，故最后的数字一定在 $a_i$ 中取到。

然后考虑将 $a$ 从小到大排序，然后对于当前的 $i$，计算最多能加入多少个数字。

可以二分，假设当前二分到 $M$，那么 $[M,i]$ 这段区间的贡献就是 $(i-M+1)a_i - \sum^{i}_{j=M} a_j$，然后用前缀和维护即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, k;
int a[100010];
ll s[100010];

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);

	sort(a + 1, a + 1 + n);

	for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + 1ll * a[i];
	int ans = 0, cc = 0;

	for (int i = 1; i <= n; ++i) {
		int l = 1, r = i;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (1ll * (i - mid + 1ll) * a[i] - s[i] + s[mid - 1] <= k) r = mid;
			else l = mid + 1;
		}

		if (1ll * (i - l + 1ll) * a[i] - s[i] + s[l - 1] <= k) {
			if (i - l + 1 > cc) {
				cc = i - l + 1;
				ans = a[i];
			}
		}
	}

	printf("%d %d\n", cc, ans);

	return 0;
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF231C)

------------
# 思路：
进行从小到大排序，这样可以使最接近的几个数都聚在一起，然后用 ```(i-j+1)*a[i]-sum;sum-=a[j++]```，这样可以以 $i - j + 1$ 为重复次数，算出重复最多的数，然后以为是从小到大排列的，又可以找出最小数。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int n,k,a[N],s;
pair<int,int> ans;
signed main(){
    cin>>n>>k;
    for(int i=0;i<n;i++){
		cin>>a[i];
	}
    sort(a,a+n);
    ans.first=ans.second=0;
    for(int i=0,j=0;i<n;i++){
        s+=a[i];
        while((i-j+1LL)*a[i]-s>k){
			s-=a[j++];
		}
        if(ans.second<i-j+1LL){
			ans=make_pair(a[i],i-j+1LL);
		}
    }
    cout<<ans.second<<" "<<ans.first<<endl;
    return 0;
}
```
完结撒花~

---

## 作者：jiangchen1234 (赞：0)

### 分析
首先想到的是双指针，敲完后想到了前缀和优化。

首先我们先枚举最大值区间，将 $l$ 设为左端点，$r$ 即是右端点也是最大值。

当区间 $[r,l] + k$ 的和小于 $a{_r} * r - l + 1$。

说明不成立 $l + 1$。

如果大于或等于成立。

更新最大值并 $r + 1$ 。
### 附上代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k,a[100005],sum[100005];//a用来存数，sum用来存前缀和
long long maxx,ans = 0;
long long read() {//一点也不快的快读
	long long s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
	return s * w;
}
int main() {
	n = read(), k = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
	int l = 1, r = 1;
	while(l <= r && r <= n) {//r表示出现次数最多的那个数，l表示左区间
		if(a[r] * (r - l + 1) - (sum[r] - sum[l - 1]) <= k) {
			if(r - l + 1 > ans) maxx = a[r], ans = r - l + 1;
			r++;
		} else l++;
	}
	printf("%lld %lld\n",ans,maxx);
	return 0;
}
```


---

## 作者：enyyyyyyy (赞：0)

这是蓝题？一个很明显的贪心，把每个的高度画出来为一个图，右边比他大，左边比他小；所以双指针大法！！
只需枚举右边界，判断当前的 $l$ 合不合法，我们用前缀和来判断即可。当前的 $k\le len\times x$。
```cpp
#include <bits/stdc++.h>
using namespace std;
inline long long read() {//快读
    long long s = 0,w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-')w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
    return s * w;
}
inline void print(long long x)//快写
{
    if(x < 0)
    {
        putchar('-');
        x = -x;
    }
    if(x>=10) print(x/10);
    putchar(x%10+'0');
    return;
}
long long n,k,a[1000005],tot,ans,r,ans2;
int main(){
    //读入 
    n=read(),k=read();
    for(int i=1;i<=n;i++)a[i]=read();
    sort(1+a,1+a+n); //排序 
    //区间dp + 双指针 
    for(int i=1;i<=n;i++)
    {
        while(tot*(a[i]-a[i-1])>k-r) 
        {
            r-=a[i-1]-a[i-tot],--tot;
        }
        r+=tot*(a[i]-a[i-1]),++tot;
        if(tot>ans) ans=tot,ans2=a[i];
    }
    print(ans),cout<<" ",print(ans2);
    return 0;
}
```


---

## 作者：墨舞灵纯 (赞：0)

==========这题做的人真的太少，既然翻译了一下就顺手写个题解吧。===========

这种题之后读入肯定先排个序。我们设 $ai$为出现次数最多的数，由于只能$+1$，那么我们就要看看比它小的数最多可以加多少个。由于越靠近$ai$加的越少越划算，所以我们很自然地把最前面的$aj$舍弃。这就是一种贪心的思想。

$Code$：

```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000005;
int a[N],n,b[N],c[N],maxn,len,lst,k,id;
long long ans;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i) 
		scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	int j=1;
	for(int i=1;i<=n;++i)
	{
		ans+=a[i];
		while(1ll*(i-j+1)*a[i]-ans>k) ans-=a[j++];
		if(i-j+1>maxn) maxn=i-j+1,id=a[i];
        //计算所需的+1次数并且去掉最前面的
	}
	printf("%d %d",maxn,id);
	return 0;
}

```

---

