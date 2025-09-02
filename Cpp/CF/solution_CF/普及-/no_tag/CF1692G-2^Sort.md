# 2^Sort

## 题目描述

Given an array $ a $ of length $ n $ and an integer $ k $ , find the number of indices $ 1 \leq i \leq n - k $ such that the subarray $ [a_i, \dots, a_{i+k}] $ with length $ k+1 $ (not with length $ k $ ) has the following property:

- If you multiply the first element by $ 2^0 $ , the second element by $ 2^1 $ , ..., and the ( $ k+1 $ )-st element by $ 2^k $ , then this subarray is sorted in strictly increasing order.

 More formally, count the number of indices $ 1 \leq i \leq n - k $ such that $ $$$2^0 \cdot a_i < 2^1 \cdot a_{i+1} < 2^2 \cdot a_{i+2} < \dots < 2^k \cdot a_{i+k}. $ $$$

## 说明/提示

In the first test case, both subarrays satisfy the condition:

- $ i=1 $ : the subarray $ [a_1,a_2,a_3] = [20,22,19] $ , and $ 1 \cdot 20 < 2 \cdot 22 < 4 \cdot 19 $ .
- $ i=2 $ : the subarray $ [a_2,a_3,a_4] = [22,19,84] $ , and $ 1 \cdot 22 < 2 \cdot 19 < 4 \cdot 84 $ .

 In the second test case, three subarrays satisfy the condition: - $ i=1 $ : the subarray $ [a_1,a_2] = [9,5] $ , and $ 1 \cdot 9 < 2 \cdot 5 $ .
- $ i=2 $ : the subarray $ [a_2,a_3] = [5,3] $ , and $ 1 \cdot 5 < 2 \cdot 3 $ .
- $ i=3 $ : the subarray $ [a_3,a_4] = [3,2] $ , and $ 1 \cdot 3 < 2 \cdot 2 $ .
- $ i=4 $ : the subarray $ [a_4,a_5] = [2,1] $ , but $ 1 \cdot 2 = 2 \cdot 1 $ , so this subarray doesn't satisfy the condition.

## 样例 #1

### 输入

```
6
4 2
20 22 19 84
5 1
9 5 3 2 1
5 2
9 5 3 2 1
7 2
22 12 16 4 3 22 12
7 3
22 12 16 4 3 22 12
9 3
3 9 12 3 9 12 3 9 12```

### 输出

```
2
3
2
3
1
0```

# 题解

## 作者：Hovery (赞：8)

# Problem

[点这里](https://www.luogu.com.cn/problem/CF1692G)

# Sol

对于这样一个不等式 $2 ^ 0 \cdot a_i < 2 ^ 1 \cdot a_{i + 1}$ ，可以转化为 $a_i < 2 \cdot a_{i + 1}$ 。

那么题目就变成了给你一个长度为 $n$ 的序列，问：有多少段长度为 $k$ 的区间满足对于任意一个位置 $i (1\le i <n)$ ， $a_i<2\cdot a_{i + 1}$ 。

上面就是一个最长平台问题，我们可以预处理出每一段符合这种条件的区间，对于一个长度为 $len$ 的这种区间，我们可以进行分类讨论。

> $1.\ len \ge k$ ， 对于这种情况，不难想到，它对答案的贡献为 $len - k + 1$ 。

> $2.\ len <k$ ，对于这种情况，它对答案不会产生贡献。

# Code

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define int long long
#define lowbit(x) (x & (-x))
using namespace std;

int n, k, t, now, ans, a[200010];

signed main()
{
	cin >> t;
	while (t--)
	{
		cin >> n >> k;
		for (int i = 1;i <= n;i++)
		cin >> a[i];
		now = 1;
		ans = 0;
		for (int i = 2;i <= n;i++)
		if (a[i] * 2 <= a[i - 1])
		{
			if (i - now >= k)
			{
				ans += i - now - k;
			}
			now = i;
		}//求出符合条件的每一段。
		if (n - now + 1 >= k && a[n] * 2 > a[n - 1])
		ans += n - now + 1 - k;//对于最后一段，不要忘记去统计答案。
		cout << ans << endl;
	}
}
```

---

## 作者：Otue (赞：3)

自我感觉这 G 题比 E 题简单多了。

## 思路
原不等式满足这么一个关系：$a_i<a_{i+1} \times 2$

于是可以把问题转化为：

$a_1<a_2 \times 2$，$a_2<a_3\times 2$，$a_3<a_4\times 2$ $,......,\ $ $a_{n-1}<a_n \times 2$ 

这些不等式中连续选择 $k$ 个都满足 有多少种情况。

---

这不就完了吗？

每一个不等式我们都可以提前计算出它成不成立，成立的标记成 $1$，不成立成 $0$，那么就连续选择 $k$ 个 $1$ 不就对了吗？ 

总共 $n-1$ 个不等式，把他的成立情况转化成一个长度为 $n-1$ 的 `bool` 数组，只需要求出这个数组有多少个连续为 $1$ 的方案数。

可以 $O(n)$ 的时间计算出。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int t, n, x, a[N], b[N];


int main() {
	cin >> t;
	while (t--) {
		memset(b, 0, sizeof b);
		cin >> n >> x;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i < n; i++) {
			if (a[i] >= a[i + 1] * 2) {
				b[i] = 1;   //b[i]=1表示不等式不成立，和上述思路反了一下
			}
		} 
		b[n] = 1;
		int res = 0, ans = 0;
		for (int i = 1; i <= n; i++) {
			if (b[i] == 0) res++; //统计当前的连续长度
			if (b[i] == 1) {
				if (res >= x) ans += res - x + 1;
				res = 0;
			}
		}
		cout << ans << endl;
	}
}
```

---

## 作者：Withers (赞：2)

[题目传送门](https://codeforces.com/contest/1692/problem/G)
# 题目大意
给出 $n,k$ 和数列 $a[]$，找出有多少个序列满足 $ 2^0 \cdot a_i < 2^1 \cdot a_{i+1} < 2^2 \cdot a_{i+2} < \dots < 2^k \cdot a_{i+k}$ 
# 思路
很水的一道题，我们每次可以直接找出 $2\cdot a_i<a_{i+1}$ 的最长长度，设一段满足要求的最大长度为 $ans$ 则它对答案的贡献为 $\max(0,ans-k)$，然后直接模拟即可

# 代码

```cpp
cin>>n>>k;
for(int i=1;i<=n;i++) cin>>a[i];
int ans=1,tot=0;
for(int i=1;i<n;i++)
{
	if(a[i]<2*a[i+1]) ans++;
	else tot+=max(ans-k,0),ans=1;
}
tot+=max(ans-k,0);
cout<<tot<<endl;
```


---

## 作者：tzyt (赞：1)

题目链接[（CF](https://codeforces.com/problemset/problem/1692/G)，[洛谷）](https://www.luogu.com.cn/problem/CF1692G) | 强烈推荐[博客](https://ttzytt.com/2022/06/CF1692G/)中观看。

打的第一场 CF div.4

这个题就是那种想到点了就很很简单，没想到的话就……寄了的题（~~我就属于是寄了~~）。

# 1. 题意：
给你一个长度为 $n \ (\sum n < 2\cdot 10^5)$ 的数组 $a$，问你在这个数组中，有多少个长度为 $k + 1 \ (1\le k < n)$ 的区间，符合以下的条件：

$$
2^0 \cdot a_i < 2^1 \cdot a_{i + 1} < 2^2 \cdot a_{i + 2} < \dotsi < 2^k \cdot a_{i + k}
$$

注：$i$ 为这个区间开始的位置
# 2. 思路
暴力还是很好搞的，就把数组中每个可能的区间都算一遍就行了，但是看到 $\sum n < 2\cdot 10^5$ 这个条件就知道要寄了。

所以我们需要一种能在 $O(1)$ 的时间内判断区间是否符合条件的方法。（你要能搞出来 $O(\log n)$ 的也不是不可以）

可以发现，采用暴力的方法是因为每次这个区间的起始位都会变，所以数组的每一项前面要乘的数都不确定的。但如果我们能找到一种跟区间起始位置不相关的判断条件，这个问题就解决了。

---
**接下来，重点来了**

再仔细观察题目中给的条件，可以发现如果想要符合条件，数组中的前一项必须小于后一项的两倍，也就是：

$$
    a_i < 2 \cdot a_{i + 1}
$$

这个性质是**和区间的位置，以及长度不相关的**，只要两个相邻的数符合这个条件，那么它可以出现在任何长度，位置的区间中。

不过，这只是区间中的两个数，如果我们想要让一整个区间都合法，那么我们就需要让整个区间内，任意的 $a_i$ 都小于 $2\cdot a_{i+ 1}$。

也就是说，只要长度为 $k$ 的区间内，有 $k - 1$ 个符合 $a_i < 2 \cdot a_{i + 1}$ 的数对，那这个区间就是符合条件的。

统计区间内的合法数量……并且需要在 $O(1)$ 的时间内查询到结果，那这不就是前缀和吗？

于是我们很自然的就想到了判断完每个数对是否合法后，开一个前缀和数组 `valid_sum[i]` 来统计，到 $i$ 为止，有多少个符合条件的数对。

最后再搞个循环统计一下符合条件的区间就好了。

# 3. 代码：
代码还是比较简单的，这题的 $a_i < 2 \cdot a_{i + 1}$ 这个点还是比较难想。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n, k;
        scanf("%d%d", &n, &k);
        //注意他给你的是 k，但是这个区间实际的长度是 k + 1
        int a[n + 1];
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
        }
        bool valid[n + 1];
        memset(valid, 0, sizeof(valid));
        int valid_sum[n + 1];
        memset(valid_sum, 0, sizeof(valid_sum));

        for(int i = 1; i < n; i++){
            if(a[i] < 2 * a[i + 1]){
                valid[i] = true;
                //判断和记录 a[i] 和 a[i + 1] 这个树对是否合法。
            }
            valid_sum[i] = valid_sum[i - 1] + valid[i];
            //前缀和
        }
        int ans = 0;
        for(int i = 1; i <= n - k; i++){
            if(valid_sum[i + k - 1] - valid_sum[i - 1] == k){
                //实际长度是 k + 1，所以 k + 1 再 - 1 = k
                ans++;
            }
        }

        printf("%d\n", ans);
    }
}
```

最后，希望这篇题解对你有帮助，如果有问题可以通过评论区或者私信联系我。

---

## 作者：duchengjun (赞：0)

# 题意

给你一个 $n$ 和一个长度为 $n$ 的数组 $a$，问你在这个数组中有多少个长度为 $k$ 的区间，使得每一个在这个区间中的数都满足它小于它的下一个数乘 2。

# 分析

原题给的是：

$$2^0 \cdot a_i < 2^1 \cdot a_{i+1} < 2^2 \cdot a_{i+2} < \dots < 2^k \cdot a_{i+k}. $$

我们选 $i$ 这个数，若要满足上方的公式，则这个数一定满足（$p$ 满足在 $[0,k-1]$ 区间中）：

$$2^p \cdot a_i<2^{p+1}\cdot a_{i+1}$$

则：

$$a_i<2\cdot a_{i+1}$$

我们就可以预处理出基本符合上述情况的所有 $i$：

```cpp
for(int i=1;i<n;i++)
	if(a[i]<2*a[i+1])
		ok[i]=true;
```

然后这个问题就可以转换为求有多少个长度为 $k$ 的区间中 $ok_i$ 是 $true$。

# CODE

```cpp
// Problem:G. 2^Sort
// From:C (A.CDT,B.LG,C.CF,D.ZCX,E.AT)
// URL:https://codeforces.com/contest/1692/problem/G
// Time:2022/6/15 22:39
// Author:A (A.dcj666,B.清华学子dcj,C.杜承俊)

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2*1e5+10;
int T;
int n,k;
int a[N];
bool ok[N];
void solve(){
	memset(ok,false,sizeof(ok));
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<n;i++)
		if(a[i]<2*a[i+1])
			ok[i]=true;
	int ans=0,cnt=0;
	for(int i=1;i<=k;i++)
		ans+=ok[i];
	if(ans==k)
		cnt++;
	for(int i=k+1;i<n;i++){
		ans+=ok[i],ans-=ok[i-k];
		if(ans==k)
			cnt++;
	} 
	//滑动窗口 
	cout<<cnt<<endl;
}
signed main(void){
	std::ios::sync_with_stdio(false);
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

先自创几个名词。

1. 优美的子序列。如果子序列中，对于每组相邻的两个数字，前一个数字小于后一个数字的两倍，那么这就是优美的子序列。

2. 完美的子序列。如果某个优美的子序列的长度达到了 $k+1$，那么这就是完美的子序列。

可以看出，题目想要求的就是完美的子序列的数量。

那么，我们可以维护一个 $last$ 变量，初始值为 $1$，代表从第 $last$ 个数开始到现在的数，是一个优美的子序列。

然后，从第 $2$ 个数开始遍历数组。如果发现第 $i-1$ 个数大于等于第 $i$ 个数的两倍，则将 $last$ 设为 $i$，因为此时优美的子序列中断了。

如果当前优美的子序列的长度达到了 $k+1$，则增加答案计数。

注意开 `long long`。

### 二、代码

```cpp
#include<cstdio>
using namespace std;
int t;
int n,k;
long long a[200005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
		}
		int last=1;
		int ans=0;
		for(int i=2;i<=n;i++)
		{
			if(a[i-1]>=a[i]*2)
			{
				last=i;
			}
			if(i-last>=k)
			{
				ans++;
				last=last+1;//其实这一句没必要。
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

```


---

## 作者：hanzhang666 (赞：0)

# 分析
这道题的式子乍一看很复杂，但化简后很简单。

$2^m\times a_{i}<2^{m+1}\times a_{i+1}$.

化简得 :

$a_i<2\times a_{i+1}$.

我们发现一个长度为 $l(l\geqslant k)$ 的合法数列，对答案的的贡献为 $l-k+1$。枚举所有合法数列，统计答案即可。

**注意：直接枚举有可能会漏掉最后一个合法数列，所以要枚举到  $n+1$。**
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int a[200005];
bool flag[200005];//flag[i]表示a[i-1]<a[i]*2，特别地，flag[1]=0 
signed main(){
	int T=read();
	while(T--){
		int n=read(),k=read();
		flag[n+1]=0;
		for(int z=1;z<=n;z++){
			a[z]=read();
			if(a[z]*2>a[z-1]&&z!=1) flag[z]=1;
			else flag[z]=0;
		}
		int cnt=0,ans=0;
		for(int z=1;z<=n+1;z++){
			if(flag[z]){
				cnt++;
			}
			else{
				if(cnt>=k)
				ans+=cnt-k+1;
				cnt=0;
			}
		}
		cout<<ans<<endl;
	}
}
```


---

## 作者：Shunpower (赞：0)

## 思路

首先容易发现实际上 $a_2\times1$ 和 $a_3\times2$ 的大小关系与 $a_2\times2$ 和 $a_3\times4$ 的大小关系毫无区别，于是我们考虑从左向右给每个 $a_i$ 乘上一个 $2^i$，看看有多少个长度为 $k+1$ 的区间单调递增就行了。

然而我们发现会乘爆，于是我们发现，当 $a_{i+1}\geqslant a_i\times2$，则这两个数都不可能在同一个区间里面。我们不妨以这样的两个数对原来的序列进行切割，然后我们对切割出的序列统计答案即可。

对于每个切割出的序列，若它的长度为 $s$，如果 $s\geqslant k+1$，则它对答案的贡献为 $s-k$。

## 代码

```
//Author:Zealous_YH
//Hai Bian & Xiao Bao
#include <bits/stdc++.h>
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ll long long
#define inf INT_MAX
#define uinf INT_MIN
#define vr vector
#define pii pair<int,int>
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
#define ld long double
#define il inline
using namespace std;
const int N=2e5+10;
int edgecnt=1;
int maxn=uinf,minn=inf;
int tnt,tot;
int T;
int n,k;
int a[N];
vr <pii> p;
int las;
int ans;
void slove(){//ByC loves Griffin!
	cin>>n>>k;
	ans=0;
	las=1;
	p.clear();
	fr1(i,1,n){
		cin>>a[i];
		if(a[i]<=a[i-1]/2){
			p.pb(mp(las,i-1));
			las=i;
		}
	}
	p.pb(mp(las,n));
	fv(i,p){
//		cout<<p[i].fi<<" "<<p[i].se<<endl;
		if(p[i].se-p[i].fi>=k){
			ans+=p[i].se-p[i].fi+1-k;
		}
	}
	cout<<ans<<endl;
}
int main(){
	cin>>T;
	while(T--){
		slove();
	}
	ET;
}
//Teens-in-Times
//HJL 2004.06.15
//Everything For Ji.
//Everything For Lin.
//Everything For You.


```

[AC 记录](https://www.luogu.com.cn/record/78161282)

---

