# Array

## 题目描述

给一个长度为n的数列，其中每一个数都是正整数，第一个数的标号为1，求一个区间[l,r]，使得这个区间里一共含有k个不同的数，并且要使这个区间里的所有数之和尽可能的小。

## 样例 #1

### 输入

```
4 2
1 2 2 3
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
8 3
1 1 2 2 3 3 4 5
```

### 输出

```
2 5
```

## 样例 #3

### 输入

```
7 4
4 7 7 4 7 4 7
```

### 输出

```
-1 -1
```

# 题解

## 作者：vanueber (赞：3)

建议评橙。

[CF原题传送门](https://codeforces.com/problemset/problem/224/B)

# 题目大意

在长度为 $n$ 的序列中选出区间 $ \left [ l,r \right ]$ 使其中有 $k$ 个不同的数并使其和尽可能小。

# 题目解析

首先考虑暴力，但是 $\Theta (n^{2})$ 的算法显然会超时，我们对它进行优化。

首先枚举 $l$，开一个 $cnt$ 数组统计 $a_{i}$ 的出现次数，同时记录区间中不同的数的个数。因为 $a_{i}$ 都是正整数，所以第一次找到的答案必定是最小的。最终输出答案即可，具体实现见代码。

# 代码

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n,k;
int a[100005],pre[100005];
int cnt[100005],tot;

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int j=1;
	for(int i=1;i<=n;i++)
	{
		cnt[a[i]]++;//统计出现次数 
		if(cnt[a[i]]==1) ++tot;//不同的数的个数 
		while(tot>k||cnt[a[j]]>=2)
		{
			cnt[a[j]]--;
			tot-=(cnt[a[j]]==0);
			j++;
		}
		if(tot==k)//满足条件 
		{
			cout<<j<<" "<<i<<endl;
			return 0;
		}
	}
	cout<<"-1 -1"<<endl;
	return 0;
}
```

[AC记录](https://codeforces.com/problemset/submission/224/218662251)

---

## 作者：linan04195 (赞：1)

## 思路
可以选用**尺取法**，慢指针 $l$ ，快指针 $r$ 。

先让 $r$ 不断往前走，直到区间内数的种类达到 $k$ 。

再让 $l$ 向前走，直到区间内数的种类小于 $k$ 。

判断区间和是不是**最小的**。

接下来就是如何解决区间内数的和以及数量：

在上述过程中，用两个变量 $sum$ 和 $num$ 分别存储 $[l,r]$ 区间内的数的总和以及数的种类，判断是否**最优**，不断更新答案即可

---
本蒟蒻自认为讲的很清楚了，那就不放代码了。

---

## 作者：Rosmarinus (赞：1)

## 题意简述

给定一个长度为 $n$ 的序列与一个正整数 $t$，要求你在序列中选出一串子序列，使这串子序列中恰好有 $t$ 种不同的数且使这串子序列的数字之和最小，输出这个子序列的头和尾下标。

## 思路分析

采用类似于尺取法的思路。

定义一个数组 $z$ 表示当前选定的子串中每种数字出现的次数，$cnt$ 表示当前选定的子序列中恰有几种数字。设当前选定的子串为 $[l, r]$。

重复以下过程：

1. 增加 $r$ 直到选定子串中恰好有 $t$ 种不同的数字；
2. 比较当前子串的数字和是否为更优值，有则更新；
3. 增加 $l$ 直到选定子串中不再有 $t$ 种不同的数字，在增加过程中重复过程 $2$。

就好了。

具体看代码：

```cpp
#include<iostream>
#define int long long
using namespace std;

int a[1100000], sum[1100000], z[1100000], ans = (long long)(1e18);

signed main()
{
    int n, t, l = 1, r = 0, cnt = 0, ansl = -1, ansr = -1;
    scanf("%lld %lld", &n, &t);
    for(int i = 1; i <= n; i ++)
    {
        cin >> a[i];
        sum[i] = a[i] + sum[i - 1];
    }
    while(r <= n)
    {
        while(cnt != t && r <= n)
        {
            r ++;
            if(!z[a[r]]) cnt ++;
            z[a[r]] ++;
        }
        if(r > n) break;
        if(sum[r] - sum[l - 1] < ans)
        {
            ans = sum[r] - sum[l - 1];
            ansl = l, ansr = r;
        }
        if(cnt == t && l <= r)
        {
            if(z[a[l]] == 1) cnt --;
            z[a[l]] --;
            l ++;
        }
    }
    cout << ansl << " " << ansr << endl;
    return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

## 题意简述

有一个长度为 $n$ 的序列 $a$，你需要选出一个区间 $[l, r]$，使得该区间数字的种类恰好为 $k$，并且最小化区间的和。

## 开始解题！

这个题是一个比较板子的双指针题。首先我们考虑当 $r$ 确定时，$l$ 应该如何选择？

首先，当 $[l, r]$ 中数字种类大于 $k$ 的时候，我们反复让 $l \leftarrow l + 1$，即缩小区间，直到实在不能缩小（即 $l = r$ 时）我们结束区间的缩小。

之后，若缩小之后 $[l, r]$ 中数字种类数为 $k$，则我们考虑能否再进行一轮缩小，使得 $[l, r]$ 更优。显然，在 $[l, r]$ 中数字种类数为 $k$ 并且 $l \le r$ 时是一定可以缩小的，但是，若 $a_l$ 这个数字的个数在 $[l, r]$ 中只剩 1 了，那么再进行缩小显然会让数字种类减少，于是遇到此情况时我们停止本轮的缩减，并且更新答案。这里注意为了快速更新答案我们还需要一个前缀和，前缀和是什么应该不用多说吧。

然后我们讨论的都是 $r$ 固定的情况，那么事实上我们取 $r = 1, 2, 3 \dots , n$ 即可，对于每个 $r$ 都进行计算与更新，便可完成本题。

最后判断如果答案的 $l$ 或答案的 $r$ 为 0 说明根本没更新，应输出 `-1 -1`，否则输出对应的答案。

做完了。

code:

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl "\n"
using namespace std;
ll n, k, a[100005], s[100005], cnt[100005], tot = 0;
ll sum = LLONG_MAX, L, R;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i]; s[i] = s[i - 1] + a[i];
    }
    ll l = 1, r = 1;
    for (r = 1; r <= n; r++) {
        cnt[a[r]] ++;
        if (cnt[a[r]] == 1) tot ++;
        while (tot > k && l <= r) {
            cnt[a[l]] --; 
            if (cnt[a[l]] == 0) tot --;
            l ++;
        }
        while (tot == k && l <= r) {
            if (cnt[a[l]] == 1) break;
            cnt[a[l]] --;
            if (cnt[a[l]] == 0) tot --;
            l ++;
        }
        if (tot == k && s[r] - s[l - 1] <= sum) {
            sum = s[r] - s[l - 1], L = l, R = r;
        }
    }
    if (L == 0 || R == 0) {
        cout << "-1 -1" << endl;
    } else {
        cout << L << " " << R << endl;
    }
}
```

[AC record](https://codeforces.com/contest/224/submission/281481473)

---

## 作者：2b2b2bbb (赞：0)

# 思路
~~与逛画展差不多的双指针问题。~~                   
首先我们可以定义两个指针 $l,r$ 然后这道题要求我们求出数的个数是否为 $k$ 个那么我们再定义一个桶。          
然后我们就让右指针一直往右移知道数的个数刚好达到了 $k$ 个那么就停止下来。               
然后我们就可以用前缀和找出这段区间内的数的和判断是否比当前得到的答案更小就替换。                
然后我们就要左指针往后移动，这个操作要一直到数的个数小于了 $k$ 为止然后再一直循环右指针知道右指针大于了 $n$。               
最后输出我们最后统计的答案即可。  
# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int a[100005];
int sum[100005];
int vis[100005];
int lt = -1,rt = -1;	
signed main(){
	cin >> n >> k;
	for(int i = 1 ; i <= n ; i ++){
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	int ans = 0,minn = 1e18,l = 1,r = 0;
	while(r < n){
		while(r < n && ans < k){
			r ++;
			vis[a[r]] ++;
			if(vis[a[r]] == 1){
				ans ++;
			}
		}
		while(l <= r && ans == k){
			if(sum[r] - sum[l - 1] < minn){
				lt = l,rt = r;
				minn = sum[r] - sum[l - 1];
			}
			vis[a[l]] --;
			if(vis[a[l]] == 0){
				ans --;
			}
			l ++;
		}
	}
	cout << lt << " " << rt;
	return 0;
}
```

---

## 作者：meimu75 (赞：0)

# 题目大意：

现有 $n$ 个数，需要连续的选出一些数，这些数要含有 $m$ 个不同的数，并在满足要求的情况下让这些数的和最小，求任意一个满足答案且和最小的答案区间。

不就尺取法嘛。前置题目[逛画展](https://www.luogu.com.cn/problem/P1638)。

甚至就是一个选数的板子。

由于要看选了多少个不同的数，所以需要一个桶来记录每个数选了多少个。

# 尺取法（选择区间）：

对于同一个左端点，而且我们要求区间最长或最短，右端点的选择又有单调性（也就是说一个临界值左边的右端点都不行，右边的都行。但是一般要求**只有** $m$ 个，因此我们就是要找第一个可行的。），就说明一个左端点只对应一个右端点。另外如果单调递增的左端点对应的右端点也是单调不减的，就可以用尺取法（双指针中的快慢指针）做。

核心首先会不停地移动右端点使得区间可以计入答案，然后在区间满足要求的情况下不停地移动左端点。前面的部分不停地循环，直到右端点出界。（这就是为什么单调不减的左端点必须对应单调不减的右端点，因为这样才能保证右端点只需要往右边移动。）

## 上伪代码。
>在右指针小于 $n$ 的情况下 `while` 循环。
>>在右指针小于 $n$ 且选的不同的数的数量小于 $m$ 的情况下 `while` 循环。
>>>右指针右移。
>>>
>>>右指针现在指向的数字桶对应的数量加一。\
>>>统计选的数量。\
>>>统计和。
>>
>>在和比之前更小的情况下更新答案。
>>
>>在左端点没有在右端点右边并且选择的数的数量不小于 $m$ 的时候 `while` 循环。
>>>左指针现在指向的数字桶对应的数量减一。\
>>>更新左指针导致的选数数量变化。\
>>>更新和。
>>>
>>>左指针右移

注意，虽然你可以在右指针右边的数字选过的情况下右移右节点，不会不满足要求，但这样会导致和变大，所以贪心的考虑肯定不会右移。

# Code:
```cpp
int l = 1,r = 0,minn = 1e18,sum = 0,tot = 0,ansl = -1,ansr = -1;
while(r < n)
{
    while(r < n && tot < m)
    {
        r++;
        cnt[a[r]]++;
        if(cnt[a[r]] == 1)tot++;
        sum += a[r];
    }
    while(l <= r && tot == m)
    {
        if(tot == m)
        {
            if(sum < minn)
            {
              minn = sum;
              ansl = l;
              ansr = r;
            }
        }
        cnt[a[l]]--;
        if(cnt[a[l]] == 0)tot--;
        sum -= a[l];
        l++;
    }
}
``````

坑点：因为是求和，所以 ${(n\times a_i)}_{\max}$ 能达到 $10^{10}$ ，所以要开 `long long`。

拒绝抄题解，从我做起。（如果你要复制，我相信你会很开心的打基本框架输入输出啥的。）

---

## 作者：_yang_yi_bo_ (赞：0)

尺取板子。

每次维护快指针 $r$ 与慢指针 $l$。

用一个桶来统计每个数出现出现的次数，并用两个变量分别维护当前出现了多少种数与所有数的和。

可以将两个答案的初始值设为 $-1$，方便计算。

记得开 `long long`。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int ans=2e18+5,sum,cnt,ll=-1,rr=-1;
int num[100005];
int n,k;
int a[100005];
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}int l=1,r=0;
	while(r<n){
		while(r<n&&cnt<k){
			r++;
			sum+=a[r];
			num[a[r]]++;
			if(num[a[r]]==1){
				cnt++;
			}
		}while(cnt==k){
			if(sum<ans){
				ans=sum;
				ll=l;
				rr=r;
			}
			sum-=a[l];
			num[a[l]]--;
			if(num[a[l]]==0){
				cnt--;
			}l++;
		}
	}cout<<ll<<" "<<rr;
	return 0;
}
```

在某机构内 OJ 已经 AC。

---

## 作者：sccc_ (赞：0)

## 题目大意  
给出一个长度为 $n$ 的序列，选出一段区间 $[l,r]$，使这段区间内有 $k$ 个不同的数，并且使区间内的和最小。  

## 思路  
考虑尺取法。  

假设我们现在选出的区间是 $[l,r]$，定义一个桶 $vis$ 来统计当前数出现的个数，且定义一个变量 $tot$ 代表当前这段区间内有多少种数。  

我们需要重复以下步骤：  
1. 让 $r$ 指针一直向前走，直到区间内数的总数到达了 $k$。
2. 让 $l$ 指针一直向前走，直到这段区间数的种类小于 $k$，并在此过程中一直判断操作 $3$。  
3. 判断这段区间是否为最优解，即区间内和最小。

## 代码  
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
int n, k;
int a[100005];
int sum[100005];
int vis[100005];
int lt = -1, rt = -1;	

signed main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i ++)
	{
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	int l = 1, r = 0;
	int tot = 0, minn = 2e18;
	while (r < n)
	{
		while (r < n and tot < k)
		{
			r ++;
			vis[a[r]] ++;
			if (vis[a[r]] == 1)
				tot ++;
		}
		while (l <= r and tot == k)
		{
			if (sum[r] - sum[l - 1] < minn)
			{
				lt = l, rt = r;
				minn = sum[r] - sum[l - 1];
			}
			vis[a[l]] --;
			if (vis[a[l]] == 0)
				tot --;
			l ++;
		}
	}
	cout << lt << ' ' << rt;
	return 0;
}

```

---

## 作者：So_noSlack (赞：0)

## 题目简述

给长度为 $n$ 的数列 $\{a_i\}$，求出一个区间 $[l, r]$，使得这个区间里一共含有 $k$ 个不同的数，并且要使这个区间里的所有数之和尽可能的小。

数据范围：$1 \le n,k,a_i \le 10^5$。

## 思路

观察到 $a_i \le 10^5$ 且是求区间内不同的数，考虑双指针和桶计数。

我们可以初始化 $l = r = 1$，然后一步步移动 $r$。

移动过程中记录 $a_i$ 的个数与当前 $[l, r]$ 中不同的个数，当不同个数大于 $k$ 或者 $a_l$ 的个数大于 $1$，我们可以移动 $l$，使得答案最优。

当第一次不同个数等于 $k$ 时，此时的 $[l, r]$ 即为最优答案之一。

无解即为直到双指针 $l = r = n$ 都没找到一个答案，输出 `-1 -1` 即可。

代码如下：


```cpp
#include<iostream>
using namespace std;
#define MAXN 100005

long long n, k, a[MAXN], pre[MAXN], mp[MAXN], p;

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    long long l = 1;
    for (int r = 1; r <= n; r ++) {
        mp[a[r]] ++;
        if(mp[a[r]] == 1) p ++;
        while (p > k || mp[a[l]] >= 2) 
            mp[a[l]] --, p -= (mp[a[l ++]] == 0);
        if(p == k) {
            cout << l << " " << r << "\n";
            return 0;
        }
    }
    cout << "-1 -1\n";
    return 0;
}

```

---

## 作者：DengDuck (赞：0)

一个比较简单的题，当右端点固定时，我们希望区间和最小，显然应该希望左端点尽可能靠右。

这个最靠右的左端点和右端点的关系是显然的：显然，当右端点向右移，最靠右的左端点要么不动，要么向右移，因为右端点右移只可能丰富颜色数量。

因此我们利用双指针的方法来维护这个最靠右的左端点，右端点移动时更新它。

再拿每次求出的最优答案尝试更新全局答案即可。

时间复杂度为 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e5+5;
LL n,k,a[N],sum[N],ansl,ansr,ans,cnt[N],tot;
int main()
{
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		sum[i]=sum[i-1]+a[i];
	}
	ans=1e18;
	LL t=1;
	for(int i=1;i<=n;i++)
	{
		cnt[a[i]]++;
		if(cnt[a[i]]==1)tot++;
		while(tot>k&&t<=i)
		{
			cnt[a[t]]--;
			if(cnt[a[t]]==0)tot--;
			t++;
		}
		while(tot==k&&t<=i)
		{
			if(cnt[a[t]]==1)break;
			cnt[a[t]]--;
			if(cnt[a[t]]==0)tot--;
			t++;
		}	
		if(tot>=k)
		{
			if(sum[i]-sum[t-1]<=ans)
			{
				ansl=t,ansr=i;
				ans=sum[i]-sum[t-1];
			}
		}
	}
	if(ansl==0||ansr==0)
		puts("-1 -1");
	else printf("%lld %lld",ansl,ansr);
}
```

---

