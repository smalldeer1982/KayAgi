# Minimizing Difference

## 题目描述

You are given a sequence $ a_1, a_2, \dots, a_n $ consisting of $ n $ integers.

You may perform the following operation on this sequence: choose any element and either increase or decrease it by one.

Calculate the minimum possible difference between the maximum element and the minimum element in the sequence, if you can perform the aforementioned operation no more than $ k $ times.

## 说明/提示

In the first example you can increase the first element twice and decrease the third element twice, so the sequence becomes $ [3, 3, 5, 5] $ , and the difference between maximum and minimum is $ 2 $ . You still can perform one operation after that, but it's useless since you can't make the answer less than $ 2 $ .

In the second example all elements are already equal, so you may get $ 0 $ as the answer even without applying any operations.

## 样例 #1

### 输入

```
4 5
3 1 7 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 10
100 100 100
```

### 输出

```
0
```

## 样例 #3

### 输入

```
10 9
4 5 5 7 5 4 5 2 4 3
```

### 输出

```
1
```

# 题解

## 作者：AutumnKite (赞：9)

[题目传送门](http://codeforces.com/contest/1244/problem/E)

## 题意

给定一个长度为 $n$ 的序列 $a$，一次操作可以将序列中的某个数 $+1$ 或 $-1$。

定义一个序列的差值为序列的最大值减去最小值得到的数。

求进行至多 $k$ 次操作后序列差值的最小值。

$n\le 10^5,a_i\le 10^9,k\le 10^{14}$

## 题解

显然可以二分答案 $x$，然后就是求使得差值 $\le x$ 需要进行至少多少次操作。

将 $a_i$ 排序，假设最后的序列中的数在 $[p,p+x]$ 中，记序列中最后一个 $< p$ 的数为 $a_l$，第一个 $>p+x$ 的数为 $a_r$，那么需要进行的操作数量是 $p\times l-\sum_{i=1}^{l}a_i+\sum_{i=r}^{n}a_i-(p+x)\times (n-r+1)$。根据这个式子我们可以发现 $p$ 和 $p+x$ 这两个数中一定有一个数是存在于原序列中的，否则可以进行调整使得操作次数更少。于是我们枚举所有情况进行判断即可。

时间复杂度 $O(n\log \max a_i)$。

## 代码

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
long long read(){
	register long long x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
int n;
long long k, a[N], sum[N];
bool check(int x){
	for (register int i = 1, j = 1; i <= n; ++i){
		while (j <= n && a[j] - a[i] <= x) ++j;
		if (a[i] * (i - 1) - sum[i - 1] + sum[n] - sum[j - 1] - (a[i] + x) * (n - j + 1) <= k) return 1;
	}
	for (register int i = 1, j = 1; i <= n; ++i){
		while (a[i] - a[j] > x) ++j;
		if ((a[i] - x) * (j - 1) - sum[j - 1] + sum[n] - sum[i] - a[i] * (n - i) <= k) return 1;
	}
	return 0;
}
int main(){
	n = read(), k = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	std :: sort(a + 1, a + 1 + n);
	for (register int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
	int l = 0, r = a[n] - a[1], md, ans = 0;
	while (l <= r) if (check(md = (l + r) >> 1)) r = md - 1, ans = md; else l = md + 1;
	printf("%d\n", ans);
}
```

---

## 作者：lrj124 (赞：6)

打的时候又是个 zz，，WA4

这个题直接维护左右两个指针，每次答案若要 -1 必须将所有最大值减一或所有最小值加一。搞花费小的就行了。。

代码较丑、、
```cpp
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
using ll = long long;
ll ans,n,k,l,r,a[100001];
int main(){
	cin >> n >> k;
	for (ll i = 1;i <= n;i++) cin >> a[i];
	sort(a+1,a+n+1); ans = a[n]-a[1];
	for (ll l = 1,r = n,x;l < r && k;ans -= x) k -= l < n-r+1 ? (x = min(a[l+1]-a[l],k/l))*l++ : (x = min(a[r]-a[r-1],k/(n-r+1)))*(n-r--)+x;
	cout << ans;
	return 0;
}
```

---

## 作者：lamboo (赞：4)

### 题意简述：

给定一个长度为$n$的序列$a$和$k$次操作，每次操作可以使其中的一个数$+1$或$-1$。

问最后$a_{max}-a_{min}$的最小值是多少。

数据范围：$2\leq n\leq 10^5$，$1\leq k\leq 10^{14}$，$1\leq a_i\leq 10^9$。

### **solution**:

先排序。

由于只有最大值和最小值会对答案造成影响，所以我们要尽量将最大值减小，最小值增大。

比较最大值和最小值的个数，取个数较小的进行调整（个数较少的调整一个所花费的步数少）。

**注意long long​**

### code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll a[100010];
inline ll read() {
    ll x=0;
    char ch=getchar();
    while (!isdigit(ch)) ch=getchar();
    while (isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return x;
}
int main() {
    long long n=read(),k=read();
    for (int i=1;i<=n;i++) a[i]=read();
    sort(a+1,a+n+1);
    int l=1,r=n;
    //l表示前l个数均已调整为最小值
    for (int i=1;i<=n;i++) 
        if (a[i]==a[l]) l=i; else break;
    for (int i=n;i>=1;i--)
        if (a[i]==a[r]) r=i; else break;
    long long ans=0;
    while (l<r) {
        if (l<n-r+1) {
            if (k>=l*(a[l+1]-a[l])) {                 //能够将全部最小值更新成下一个值
                k-=l*(a[l+1]-a[l]);
                ++l;
                for (int i=l;i<=n;i++)
                    if (a[i]==a[l]) l=i; else break;  //更新最小值的个数
            } else {
                ans=k/l;break;
            }
        } else {
            if (k>=(n-r+1)*(a[r]-a[r-1])) {           //能够将全部最大值更新成下一个值
                k-=(n-r+1)*(a[r]-a[r-1]);
                --r;
                for (int i=r;i>=1;i--)
                    if (a[i]==a[r]) r=i; else break;  //更新最大值的个数
            } else {
                ans=k/(n-r+1);break;
            }
        }
    }
    if (l>=r) printf("0\n");
    else cout<<a[r]-a[l]-ans<<endl;
    return 0;
}
```



---

## 作者：xz001 (赞：3)

- 发现答案具有单调性，因此我们可以二分答案。
- 由初中数学得知：
  - $n$ 个点，若 $n$ 为奇数，则最中间的点与其他点的距离和最小；若 $n$ 为偶数，则最中间的两个点之间的位置与其他点的距离和最小。
- 因此 ```check``` 函数可以这么写，不断枚举最大值和最小值，看看其之间的差是否大于二分的 ```mid```，若小于则最小代价加上**两点之间的差减去 mid**，去除最大值和最小值，否则退出。
- 代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, k, a[1000005];
int check (int mid) {
	int l = 1, r = n, sum = 0;
	while (l < r) {
		if (a[r] - a[l] <= mid) break; //若两点之间的距离已经小于 mid 了，就直接退出
		sum += a[r] - a[l] - mid;  //加上代价
		++ l, -- r;  //去除最大值和最小值
	}
	return sum;
}
signed main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; ++ i) scanf("%lld", a + i);
	sort(a + 1, a + n + 1);  //别忘了排序
	int l = 0, r = 1e18, ans;
	while (l <= r) {   //伟大的二分答案
		int mid = (l + r) >> 1;
		if (check(mid) <= k) {  //若最大值和最小值小于等于 mid 的最小代价小于等于 k
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	printf("%lld", ans);
	return 0;
} 
```

---

## 作者：123zbk (赞：2)

符合单调性，直接二分答案 $mid$。

将数组排序后，计算每一次的 $a_r-a_l$ 的差和 $mid$ 的大小。如果 $a_r-a_l\le mid$ 直接返回判断次数，否则这一次需要操作 $a_r-a_l-mid$ 次。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
int n,k,ans,a[maxn];
bool check(int mid)
{
    int l=1,r=n,cnt=0;
    while(l<r)
    {
        if(a[r]-a[l]<=mid)
        {
            return cnt<=k;
        }
        cnt+=a[r]-a[l]-mid;
        l++;
        r--;
    }
    return cnt<=k;
}
signed main()
{
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
    }
    sort(a+1,a+n+1);
    int l=0,r=1e9;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid))
        {
            ans=mid;
            r=mid-1;
        }
        else
        {
            l=mid+1;
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Genius_Star (赞：2)

### 思路：

**update：ABC330 F 题跟是此题的严格加强版。**

明显答案符合单调性，所以考虑二分答案。

现在想想怎么写 ``check``。

先将原序列排序。

设当前判断的答案为 $x$，分两种情况考虑：

- 枚举一个 $i$，假定其为 $\min$，那么可以通过二分或者单调栈找出一个小于等于 $a_i + x$ 的下一个数，设位置为$p$，假定其为 $\max$；那么需要将 $a_{p+1 \sim n}$ 减到等于 $a_i +x$，这样是操作最少的；同样需要将 $a_{1 \sim i-1}$ 加到 $a_i$；（设最小操作次数为 $S1$）

- 枚举一个 $i$，假定其为 $\max$，那么可以通过二分或者单调栈找出一个小于等于 $a_i - x$ 的下一个数，设位置为$p$，假定其为 $\min$；那么需要将 $a_{i+1 \sim n}$ 减到等于 $a_i$，这样是操作最少的；同样需要将 $a_{1 \sim p-1}$ 加到 $a_i - x$；（设最小操作次数为 $S2$）

则只要 $\min(S1,S2) \le k$，则符合。

对于上面的实现操作可以根据前缀和进行优化。

时间复杂度为：$O( N \log W \log N)$。

**如果再加一点预处理，可以优化到 $O(N \log W)$，不过这题能过，就懒得加了。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=200200,INF=1e17;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,k;
ll a[N],A[N],F1[N],F11[N],as1[N],as2[N];
bool check(ll x){
	ll S1=INF,S2=INF;
	for(int i=1;i<=n;i++){
		ll t=a[i]+x;
		ll p=F1[i],q=upper_bound(a+1,a+n+1,t)-a;
		S1=min(S1,(as1[q]-(n-q+1)*t)+(p*a[i]-as2[p]));
	}
	for(int i=1;i<=n;i++){
		ll t=A[i]-x;
		ll p=F11[i],q=n-(lower_bound(a+1,a+n+1,t)-(a+1))+1;
//		printf("%lld %lld\n",p,q);
		S2=min(S2,((q<=i||q>n)?0:((n-q+1)*t-as2[n-q+1]))+(as1[n-p+1]-p*A[i]));		
	}
	return (min(S1,S2)<=k);
}
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	  A[i]=a[n-i+1];
	F1[1]=F11[1]=0;
	for(int i=2;i<=n;i++){
		if(a[i]==a[i-1])
		  F1[i]=F1[i-1];
		else
		  F1[i]=i-1;
		if(A[i]==A[i-1])
		  F11[i]=F11[i-1];
		else
		  F11[i]=i-1;	
	}
	for(int i=n;i>=1;i--)
	  as1[i]=as1[i+1]+a[i];
	for(int i=1;i<=n;i++)
	  as2[i]=as2[i-1]+a[i];
	check(2ll);
	ll l=0,r=1e9;
	while(l<r-1){
		ll mid=(l+r)>>1;
		if(check(mid)) 
		  r=mid;
		else 
		  l=mid;
	}
	if(check(l)) 
	  write(l);
	else
	  write(r);
	return 0;
}
```


---

## 作者：dbxxx (赞：2)

[欢迎在我的博客中查看本文，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/cf1244e.html)

首先容易想到把 $a$ 升序排列。

想让 $\max - \min$ 最小，一定是选择降低 $\max$，提高 $\min$。

先考虑一个问题：单纯最大化 $\min$。

想一下，提高 $\min$ 其实是这样一个过程：一直加 $a_1$，直到 $a_1 = a_2$，然后一直同步加 $a_1, a_2$，直到 $a_1=a_2=a_3$，再一直同步加 $a_1,a_2,a_3$……直到最后 $k$ 被用尽。易证不这么加就是浪费操作。

假设我们刚刚同步把 $a_1 \sim a_{i - 1}$ 加到和 $a_i$ 齐平，现在我们要把 $a_1 \sim a_i$ 加到和 $a_{i +1}$ 齐平。

如果代价足够用，我们就考虑把 $a_1 \sim a_i$ 花费 $i(a_i - a_{i-1})$ 的代价一直加到 $a_{i + 1}$，然后 $i \gets i + 1$；

如果代价不够用了，就考虑把 $a_1 \sim a_i$ 一直加到代价耗尽，答案就是此时能加到的位置。

单纯降低 $\max$ 是同理的。现在我们综合考虑。

如果我们刚刚把 $a_1$ 加到和 $a_2$ 齐平，这时有两条路走：

- $a_1, a_2$ 一直加到和 $a_3$ 齐平；
- $a_n$ 一直减到和 $a_{n-1}$ 齐平。

那么我们一定选择第二条路。因为第一条路每花费 $2$ 的代价才能提高 $1$ 的 $\min$，但第二条路每花费 $1$ 的代价就能降低 $1$ 的 $\max$。第二条路走完（齐平了）如果还有操作剩余，再走第一条路。

因此最优解一定是重复执行以下三步得到，初始时 $l = 1$：

- 尝试把 $a$ 开头长度为 $l$ 的前缀加到和后面那个数齐平，并把 $a$ 结尾长度为 $l$ 的后缀减到和前面那个数齐平；
- 如果齐平成功，$l \gets l +1$；
- 如果齐平不成功，说明步数要不够了。尽可能让剩下的步数给前缀的 $l$ 个数 $+1$，后缀的 $l$ 个数 $-1$，可以让 $\max$ 和 $\min$ 再靠近【剩下的步数除以 $l$，下取整】个单位。此时得到最终答案。

考虑前缀和后缀的汇合点。这里我们让上述算法在处理 $l= \lfloor \dfrac{n - 1}{2} \rfloor$ 后终止。那么在 $n$ 为奇数时刚刚好，$n$ 为偶数时还有中间两个点没齐平，手动尝试齐平一下即可。

时间复杂度 $\mathcal{O}(n \log n)$。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2022-10-18 09:56:47 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2022-10-18 10:45:39
 */
#include <bits/stdc++.h>
#define int long long
inline int read() {
    int x = 0;
    bool flag = true;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            flag = false;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    if(flag)
        return x;
    return ~(x - 1);
}

const int maxn = (int)1e5 + 5;
int a[maxn];

inline int min(int a, int b) {
    return a < b ? a : b;
}

signed main() {
    int n = read(), k = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    
    std :: sort(a + 1, a + 1 + n);
    int ans = a[n] - a[1];

    for (int l = 1, r = n; l <= ((n - 1) >> 1); ++l, --r) {
        int t = (a[l + 1] - a[l] + a[r] - a[r - 1]) * l;
        if (k < t) {
            printf("%lld\n", ans - k / l);
            return 0;
        } else {
            ans = a[r - 1] - a[l + 1];
            // 可以写成 ans -= t / l;
            k -= t;
        }
    }

    if ((n & 1) == 0) {
        int l = (n >> 1);
        ans -= min(a[l + 1] - a[l], k / l);
    }

    printf("%lld\n", ans);
    return 0;
}
```

如果觉得本篇题解写得好，请不要忘记点赞，谢谢！

---

## 作者：Katsura_Hinagiku (赞：2)

题意简述：给定一个数列，k次操作。每一次操作你可以将数列中的一个数加一或减一，问进行小于等于k次操作后数列中最大值减去最小值最小为多少

可以用贪心的思路求解。先将数列排序。要使数列中的最小值增大一，则需要将数列中的每一个最小值都加一；要使数列中的最大值减小一，则需要将数列中的每一个最大值都减一。每次操作时，先得出数列中最小值和最大值分别有几个，再选定本次操作增大最小值还是减小最大值。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n;
ll k;
ll a[100005];
int main()
{
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;++i)
	{
		scanf("%lld",&a[i]);
	}
	sort(a+1,a+n+1);
	ll sum=0;
	if(n%2)
	{
		for(int i=1;i<=n;++i)
		{
			sum+=abs(a[n/2+1]-a[i]);
		}
	}
	else
	{
		for(int i=1;i<=n;++i)
		{
			sum+=abs(a[n/2]-a[i]);
		}
	}
	if(k>=sum)
	{
		printf("0\n");
		return 0;
	}//可以将数列中每个数变成一样，则输出0
	ll bg=a[1],ed=a[n];
	int pre=1,nxt=n;
	while(pre<=nxt)
	{
		while(pre<nxt&&a[pre]==a[pre+1])++pre;
		while(pre<nxt&&a[nxt-1]==a[nxt])--nxt;//统计出当前数列中最小值和最大值分别有几个
		if(pre==nxt)break;
		if(pre<(n-nxt+1))//如果最小值的个数少，则增大最小值
		{
			ll val1=(ll)pre*(a[pre+1]-a[pre]);
			if(k<val1)
			{
				bg+=k/(ll)pre;
				break;
			}
			else
			{
				k-=val1;
				bg=a[pre+1];
				++pre;
			}
		}
		else//反之减小最大值
		{
			ll val2=(ll)(n-nxt+1)*(a[nxt]-a[nxt-1]);
			if(k<val2)
			{
				ed-=k/(ll)(n-nxt+1);
				break;
			}
			else
			{
				k-=val2;
				ed=a[nxt-1];
				--nxt;
			}
		}
	}
	printf("%lld\n",ed-bg);
	return 0;
}
```

---

## 作者：TruchyR (赞：1)

## Part 1 思路
~~从[强化版](https://www.luogu.com.cn/problem/AT_abc330_g)跑过来的题解。~~  
显然二分答案，下文假设二分的答案为 $m$，且数组已经从小到大排好序。  
- 第一个问题：如果我们知道了最终序列的最小值是 $l$，最大值是 $l+m$，怎么求需要几次操作可以得到序列？  
  - 在区间内的数字不需要操作。
  - 可以二分得到在这个区间左侧/右侧的数字，假设下标分别是 $x,y$。  
  - 答案即为 $\sum_{i=1}^{x}(l-a_i)+\sum_{i=y}^{n}(a_i-l-m)$。  
   化简可得 $\sum_{i=y}^{n}a_i-(n-y+1)(l+m)+xl-\sum_{i=1}^{x} a_i$。
  - 前缀和预处理可以做到 $O(\log{n})$。
- 第二个问题：我们如何确定 $l$ 在哪里呢？  
  - 一个结论：在至少一组最优解中，$l$ 和 $l+m$ 中至少有一个出现在 $a$ 中。  
  - 考虑反证，假设没有一组最优解满足上面的条件。  
  如果 $l$ 和 $l+m$ 组成区间左侧有 $p$ 个，右侧有 $q$ 个数在序列中：
    - 当 $p\leq q$ 时：  
    可以把区间向右移动，直到区间其中一端在 $a$ 中来达成一组最优解，与假设矛盾。
    - 当 $p\geq q$ 时：  
    可以把区间向左移动，直到区间其中一端在 $a$ 中来达成一组最优解，与假设矛盾。
    - 故假设不成立。
  - 所以我们只需要在每次判定中枚举 $2n$ 个端点即可。
- 总时间复杂度 $O(n\log^2{n})$，可以通过本题。

## Part 2 代码
```cpp
#include<bits/stdc++.h>
#define CKE if(CHECK)
#define FRE if(FIL)
#define int long long
#define MX 200005
#define INF 10000000000000000ll
using namespace std;
const int CHECK=0,FIL=0;int read();
int n,k,mid,w,s,d[MX],z[MX];
bool les(int X){return X<s;}
bool gre(int X){return X>s+mid;}
int ef(int P[],bool (*F)(int),int op){
	int l=0,r=n+1;
	if(op)
		while(l<r){
			int mid=(l+r)>>1;
			if(F(P[mid])) r=mid;
			else l=mid+1;
		}
	else
		while(l<r){
			int mid=(l+r+1)>>1;
			if(F(P[mid])) l=mid;
			else r=mid-1;
		}
	return r;
}
int ck(){
	int K=INF;
	for(int i=1;i<=n;i++){
		s=d[i];	  	 w=ef(d,gre,1);//这个点是左端点时
		K=min(K,z[n]-z[w-1]-(s+mid)*(n-w+1)  +  d[i]*i-z[i]);
		s=d[i]-mid;  w=ef(d,les,0);//这个点是右端点事时
		K=min(K,z[n]-z[i]-d[i]*(n-i)         +  s*w-z[w]);
	}
	return K<=k;
}
int solve(){
	sort(d+1,d+1+n);//排序
	for(int i=1;i<=n;i++) z[i]=z[i-1]+d[i];//前缀和
	int l=0,r=INF;//二分答案
	while(l<r){
		mid=(l+r)>>1ll;
		if(ck()) r=mid;
		else l=mid+1;
	}return l;
}
signed main(){
	//读入输出
	FRE freopen(".in","r",stdin);
	FRE freopen(".out","w",stdout);
	n=read();k=read();
	for(int i=1;i<=n;i++){d[i]=read();}
	printf("%lld",solve());
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
```


---

## 作者：OldDriverTree (赞：1)

本文讲解二分套三分做法。

[加强版：ABC330F](https://www.luogu.com.cn/problem/AT_abc330_f)。

# Solution

考虑先二分 $\max-\min$ 的最小值 $x$。

可以发现，$x$ 确定后 $\min$ 的值对应的最小移动步数是一个单峰函数，三分即可。

时间复杂度 $O(n\log^2 V)$。
# Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5;
int n,m,a[N];

int f(int l,int x)
{
	int sum=0;
	for (int i=0;i<n;i++) {
		if (a[i]<x) sum+=x-a[i];
		if (a[i]>x+l) sum+=a[i]-x-l;
	}
	return sum;
}
bool check(int x)
{
	int l=1,r=1e9,ans=LONG_LONG_MAX;
	while (l+2<r) {
		int mid1=(l+l+r)/3,mid2=(l+r+r)/3;
		f(x,mid1)>f(x,mid2)?l=mid1:r=mid2;
	}
	while (l<=r)
	ans=min(ans,f(x,l++) );
	return ans<=m;
}
main()
{
	scanf("%lld%lld",&n,&m);
	for (int i=0;i<n;i++) scanf("%lld",a+i);
	int l=0,r=1e9;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (check(mid) ) r=mid-1;
		else l=mid+1;
	}
	printf("%lld",l);
	return 0;
}
````

---

## 作者：CWzwz (赞：1)

[CF1244E Minimizing Difference](https://www.luogu.com.cn/problem/CF1244E) 题解

[Codeforces](https://codeforces.com/problemset/problem/1244/E)

------------

## 闲话

吐槽一下，[ABC330F](https://www.luogu.com.cn/problem/AT_abc330_f) 比此题严格更强，但是它评了绿，这题评了蓝。（个人感觉大概都是绿。）

------------

## 题解

给你一个序列 $a_i$，一次操作将一个数的值增加 $\pm1$，进行至多 $k$ 次操作后，求最小 $\max\{a_i\} - \min\{a_i\}$。

把序列抽象成一个数轴，其上 $n$ 个点，第 $i$ 个点的坐标是 $a_i$，一次操作将一个点左移或右移 $1$ 单位，至多 $k$ 次操作后，用一条线段盖住所有点，求线段最小长度。

### 结论

- **为了使线段的位置最优（操作次数少），它必然有一端在一个点上。**

### 证明

**能感性理解的话可跳过**

注意：以下“包含”、“盖住”指**严格**包含（在端点上不算包含）。

比如：

![](https://cdn.luogu.com.cn/upload/image_hosting/wl0cm2it.png)

将黑色线段左移，其端点刚好碰到一个点时，停下，记为红线。右移，同样碰到点就停下，记为蓝线。**（也就是说，它快要盖住或离开一个点时，停止移动。）**

这个结论就是，黑色线段 不优于红线 或 不优于蓝线。

因为像我们这样移动黑线，并不会改变任何点的**被包含状态**（线段不会**新**覆盖任何点，也不会离开任何点）。

左移线段 $x$ 单位（$x$ 可为负，即右移），会使右边没被盖住的点代价增加 $x$，左边没被盖住的点代价减少 $x$。

那么，如果左边点多，向左移（红线）；右边点多，向右移（蓝线）。这样，红蓝线里必然有一个不劣于黑色。证毕。

这样，没有端点在点上的线段（黑线），都不优于端点在点上的线段（红/蓝线）。那么这些黑线就不用考虑了。

### 做法

容易想到，短的线段可以覆盖，长的必然也可以。问题单调，考虑二分线段长。

如何 `check(x)`？

由上面的结论，线段一定有一端在点上。那就可以 $O(n)$ 枚举线段位置，每个点两种情况：线段的左/右端点在它这里。

考虑快速统计一个位置的代价。前缀和维护坐标和即可 $O(\log n)$。

复杂度 $O(n \log n \cdot \log V)$，$V$ 是坐标值域。

[Submission](https://codeforces.com/contest/1244/submission/236137191)

------------

### 题外话：[ABC330F](https://www.luogu.com.cn/problem/AT_abc330_f) 题解

这个东西转成二维了啊，但是其实它的 $x$ 和 $y$ 是分开的，因为是曼哈顿距离。所以 $x$ 和 $y$ 分别排序，共用 $k$ 的贡献即可。

复杂度还是 $O(n \log n\cdot\log V)$，$V$ 为坐标值域。

[Submission](https://atcoder.jp/contests/abc330/submissions/48244101)

---

## 作者：Pelom (赞：1)

# 题意

给出$n$个数，每次操作可以选择一个数$+1$或$-1$，求$k$次操作后最小极差

**数据范围：**$2 \le n \le 10^5,1 \le k \le 10^{14}$

# 题解

为了减小极差，每次肯定是选择最大值$-1$或最小值$+1$，所以先排个序

为了快速转移，可以将$a[i]$变为$a[i+1]$（对于前半部分）或将$a[i]$变为$a[i-1]$（对于后半部分）；而当$k$值不足以进行一次转移时，还可以给之前已经处理过的数（相等且最大/最小）整体改变

为了避免选择改变最大值还是最小值，将其放到一起处理；注意偶数项的中间两项需要特殊处理，避免算重

**代码：**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int N=1e5+10;
int n,k;
int a[N];
int ans;
signed main(){
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    ans=a[n]-a[1];
    for(int i=1;i<(n+1)/2;i++){
        int t=min(a[i+1]-a[i]+a[n-i+1]-a[n-i],k/i);
        ans-=t;
        k-=t*i;
    }
    if(n%2==0){
        int t=min(a[n/2+1]-a[n/2],k/(n/2));
        ans-=t;
        k-=t*(n/2);
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Llf0703 (赞：1)

[更好的阅读体验](https://llf0703.com/p/cf-1244.html#eminimizingdifference)

## 题意

给出 $n(\le 10^5)$ 个数，可以进行 $k$ 次操作，每次可以把一个数 $+1$ 或 $-1$ 。求操作后 最大数和最小数差值 的最小值。

## 题解

可以发现最优的操作就是把两端的最值不断往中间靠近。而最值的点可能有多个，假设有 $x$ 个，那么每消耗 $x$ 才能使答案 $-1$ ，所以每次都选择个数较少的一端进行操作。

需要离散化得到各个数值的个数。因为我比较懒所以操作的过程就写的优先队列。

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pii pair<ll,ll>
#define pip pair<ll,pii>
#define ll long long

using namespace std;

inline ll read()
{
    char ch=getchar(); ll f=1,x=0;
    while (ch<'0' || ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    return f*x;
}

const ll N=100005;
struct node {
    ll s,cnt;
} s[100005];
ll n,m,k,ans=1e9,a[100005];
priority_queue <pip,vector<pip>,greater<pip> > q;

signed main()
{
    n=read(); k=read();
    for (ll i=1;i<=n;i++) a[i]=read();
    sort(a+1,a+n+1);
    for (ll i=1;i<=n;i++) //离散化
    {
        if (a[i]!=a[i-1]) s[++m].s=a[i],s[m].cnt=1;
        else s[m].cnt++;
    }
    if (m==1) return 0&puts("0"); //只有一个值
    q.push(mp(s[1].cnt,mp(1,0))); //左端
    q.push(mp(s[m].cnt,mp(m,1))); //右端
    for (ll l=1,r=m;!q.empty();q.pop())
    {
        ll x=q.top().second.first,y=q.top().first;
        bool p=q.top().second.second; //在哪一端
        ll delta=p ? s[x].s-s[x-1].s : s[x+1].s-s[x].s; //差值
        if (delta*y<=k) //如果能直接靠近到下一个数值
        {
            k-=delta*y;
            if (p) //在右端
            {
                r--;
                q.push(mp(y+s[r].cnt,mp(r,1)));
            }
            else
            {
                l++;
                q.push(mp(y+s[l].cnt,mp(l,0)));
            }
            if (l==r) { ans=0; break; }
        }
        else //否则能靠近多少算多少
        {
            ll maxd=k/y; //最多能靠近的值
            ans=s[r].s-s[l].s-maxd;
            break;
        }
    }
    return !printf("%lld",ans);
}
```

---

## 作者：xukuan (赞：1)

这场比赛唯一的中档题

显然是贪心。

先将数列排序。

要使数列中的最小值+1，则需要将数列中的每一个最小值都+1；要使数列中的最大值-1，则需要将数列中的每一个最大值都-1。——mangoyang在XJOI上的讲评（不是这题）

现在我们来分类讨论:

- 如果剩下的操作次数足够：比较左右两边的差的较小值（就是$a_{l+1}-a_l$和$a_r-a_{r-1}$），选择较小的操作

- 如果剩下的操作次数不够，选择两边数字较少的（就是$l$和$n-r+1$）操作

总共四种情况，代码有点烦，要耐心

另外如果次数稳够就直接输出0

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=100010;
ll n,k,sum,a[N];

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

int main(){
	n=read(); k=read();
	for(ll i=1; i<=n; i++) a[i]=read();
	sort(a+1,a+1+n);
	for(ll i=1; i<=n; i++) sum+=abs(a[(n+1)/2]-a[i]);
	if(k>=sum) return printf("0")&0;
	ll l=1,r=n,lval=a[1],rval=a[n];
	while(l<=r){
		while(l<r&&a[l]==a[l+1]) l++;
		while(r>l&&a[r]==a[r-1]) r--;
		if(l==r) break;
		if(l<n-r+1){
			ll eps=l*(a[l+1]-a[l]);
			if(k<eps){
				lval+=k/l;
				break;
			}
			else{
				k-=eps;
				l++;
				lval=a[l];
			}
		}
		else{
			ll eps=(n-r+1)*(a[r]-a[r-1]);
			if(k<eps){
				rval-=k/(n-r+1);
				break;
			}
			else{
				k-=eps;
				r--;
				rval=a[r];
			}
		}
	}
	cout<<rval-lval<<endl;
	return 0;
}
```

---

## 作者：Vitamin_B (赞：0)

看着一串二分题解，我还是来补一发贪心的吧~
# 思路
每次要使 $Max-Min$ 变小 $1$ 时，必须要把 $=Max$ 的数整体 $-1$ 或把 $=Min$ 的数整体 $+1$，所以很显然可以选较少的数操作。

所以，我们可以利用 map 存下每种数的个数。因为当 $Max$ 的个数改变时，仅可能它和次大数相同，所以我们只要每次一次性操作到次大值就行啦。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <char, int> pci;
int n, a[100005], l, r;
ll k;
map <int, int> mp;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> k;
	for (int i = 0; i < n; ++ i)
		cin >> a[i], ++ mp[a[i]];
	sort (a, a + n), n = unique (a, a + n) - a; //排序&去重
	r = n - 1;
	while (r > l)
		if (mp[a[l]] < mp[a[r]]) //操作 Min 更划算
			if (k >= (ll) (a[l + 1] - a[l]) * mp[a[l]])  //足够操作到次小值
				k -= (ll) (a[l + 1] - a[l]) * mp[a[l]], mp[a[l + 1]] += mp[a[l]], ++ l; //记得加上个数
			else {
				a[l] += k / mp[a[l]]; //最多可以再操作 k / mp[a[l]] 次
				cout << a[r] - a[l];
				return 0;
			} else if (k >= (ll) (a[r] - a[r - 1]) * mp[a[r]]) //足够操作到次大值
			k -= (ll) (a[r] - a[r - 1]) * mp[a[r]], mp[a[r - 1]] += mp[a[r]], -- r; //记得加上个数
		else {
			a[r] -= k / mp[a[r]]; //最多可以再操作 k / mp[a[r]] 次
			cout << a[r] - a[l];
			return 0;
		}
	cout << 0; //l = r 都用不完了，肯定0
	return 0;
}
```

---

## 作者：WhisperingWillow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1244E)

简单题。

想让最大值减去最小值最小，我们可以二分答案 $x$。

当 $\max_{i=1}^na_i-\min_{i=1}^na_i\le x$ 时，我们不用进行任何操作。

否则我们可以将它们进行 $\max_{i=1}^na_i-\min_{i=1}^na_i-x$ 次操作，使 $\max_{i=1}^na_i-\min_{i=1}^na_i= x$。


```

int a[N],k; 

inline bool check(int x){
	int l=1,r=n,cnt=0;
	while(l<r){
		if(a[r]-a[l]<=x) return cnt<=k;
		cnt+=a[r]-a[l]-x;
		++l,--r; 
	}
	return cnt<=k;
}

void solve(){
	n=read(),k=read();
	f(i,1,n) a[i]=read();
	sort(a+1,a+n+1);
	
	int mid,l=0,r=1e18,ans=0;
	while(l<=r) {
		mid=(l+r)>>1;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1; 
	}
	writed(ans);
	 return;
}

```

---

## 作者：Lydia1010__ (赞：0)

## 本题思路：
这道题需要用到的算法有二分和排序，还算是一道比较简单的蓝题吧。

看到题目，要求最大值减最小值的值最小，那么就可以用二分去枚举差值是多少，计算出答案即可。

考虑判断当前值是否合法，我们就可以先给数值排一个序，如果当前的这个数与从后往前当前这一位相差大于当前答案数，那么就可以用当前两个数的相差数减去当前答案数作为更改量，因为我们排了序，给当前这两位均匀的加减到相差为当前的答案后不会对后面的值产生影响，所以合法。如果相差已经比答案数小了，就可以直接判断更改量是否大于 $m$，大于就不行，小于等于就合法。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100005];
int n,m;
int check(int k){
	int sum=0;
	for(int i=1;i<=n/2;i++){
		int j=n-i+1;
		if(sum>m) return 0;
		if(a[j]-a[i]<=k){
			if(sum<=m) return 1;
			return 0;
		}
		sum+=(a[j]-a[i])-k;
	}
	if(sum<=m) return 1;return 0;
}
signed main(){
	int ma=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n); 
	int l=0,ans=0,r=a[n]-a[1];
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

我们考虑二分最终的答案。

接下来就是如何检查最大值减最小值大于等于 $mid$ 的时候操作步数是多少。

先把数列排序。显然我们希望把大的数变小，小的数变大。且我们只关心一个数要变多少。

我们把这个数列中的数两两考虑。即 $\{a_{1},a_{n}\},\{a_2,a_{n-1}\}\cdots$ 这样子组合。如果一组数 $\{a_i,a_j\}$差大于 $mid$ 则花费 $a_j-a_i-mid$ 的代价把差变成 $mid$，否则不操作。

这个做法的正确性就来自排序。感性理解下，我们假设有一对合法的数 $\{x,y\},x\le y$ 且差值等于 $mid$，那么对于所有 $a_i\le x\le y \le a_j$，它们可以通过变成 $\{x,y\}$ 完成操作。对于 $x<a_i\le a_j<y$，则无需操作。**因为排序和上面的分组方式，不会出现其它情况。**

那么按照上面的思路实现就可以了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,x[100005];
bool check(int mid){
	int sum=0;
	for(int l=1,r=n;l<r;l++,r--){
		if(x[r]-x[l]<=mid) break;
		sum+=x[r]-x[l]-mid;
	}
	return sum<=k;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>x[i];
	sort(x+1,x+n+1);
	int l=0,r=1e9,ans=r;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
}
```

---

