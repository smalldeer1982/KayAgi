# Cat Party (Hard Edition)

## 题目描述

This problem is same as the previous one, but has larger constraints.

Shiro's just moved to the new house. She wants to invite all friends of her to the house so they can play monopoly. However, her house is too small, so she can only invite one friend at a time.

For each of the $ n $ days since the day Shiro moved to the new house, there will be exactly one cat coming to the Shiro's house. The cat coming in the $ i $ -th day has a ribbon with color $ u_i $ . Shiro wants to know the largest number $ x $ , such that if we consider the streak of the first $ x $ days, it is possible to remove exactly one day from this streak so that every ribbon color that has appeared among the remaining $ x - 1 $ will have the same number of occurrences.

For example, consider the following sequence of $ u_i $ : $ [2, 2, 1, 1, 5, 4, 4, 5] $ . Then $ x = 7 $ makes a streak, since if we remove the leftmost $ u_i = 5 $ , each ribbon color will appear exactly twice in the prefix of $ x - 1 $ days. Note that $ x = 8 $ doesn't form a streak, since you must remove exactly one day.

Since Shiro is just a cat, she is not very good at counting and needs your help finding the longest streak.

## 说明/提示

In the first example, we can choose the longest streak of $ 13 $ days, since upon removing the last day out of the streak, all of the remaining colors $ 1 $ , $ 2 $ , $ 3 $ , and $ 4 $ will have the same number of occurrences of $ 3 $ . Note that the streak can also be $ 10 $ days (by removing the $ 10 $ -th day from this streak) but we are interested in the longest streak.

In the fourth example, if we take the streak of the first $ 6 $ days, we can remove the third day from this streak then all of the remaining colors $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ and $ 5 $ will occur exactly once.

## 样例 #1

### 输入

```
13
1 1 1 2 2 2 3 3 3 4 4 4 5
```

### 输出

```
13```

## 样例 #2

### 输入

```
5
10 100 20 200 1
```

### 输出

```
5```

## 样例 #3

### 输入

```
1
100000
```

### 输出

```
1```

## 样例 #4

### 输入

```
7
3 2 1 1 4 5 1
```

### 输出

```
6```

## 样例 #5

### 输入

```
6
1 1 1 2 2 2
```

### 输出

```
5```

# 题解

## 作者：OIerWu_829 (赞：6)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1163B2) / [Codeforces 传送门](https://codeforces.com/problemset/problem/1163/B2)

我们用两个哈希表 $cnt$ 和 $fec$，分别存储每种元素出现的次数和每种出现次数（从 $cnt$ 中获取）的数量。然后我们遍历每一个元素，更新 $cnt$ 和 $fec$，并检查当前检查状态是否符合要求：

+ 确保有且仅有两种不同的出现次数：
  + 其中一种出现次数是 $1$（也就意味着可以删除这个元素的一个实例）；
  + 另一种出现次数是 $k$（也就意味着其他颜色都出现了 $k$ 次）。
+ 或者只有一种出现次数 $k$，并且正好 $cnt_k=1$（也就意味着可以删除这个元素的一个实例）。

然后在每次遍历中更新答案最后输出即可。

```cpp
#include <iostream>
#include <map>
using namespace std;

const int N = 1e5 + 5;

int a[N];
map<int, int> cnt, fec;

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		if (cnt[a[i]] > 0)
		{
			fec[cnt[a[i]]]--;
			if (fec[cnt[a[i]]] == 0) fec.erase(cnt[a[i]]);
		}
		cnt[a[i]]++;
		fec[cnt[a[i]]]++;
		if (fec.size() == 1)
		{
			auto it = fec.begin();
			if (it->first == 1 || it->second == 1) ans = i + 1;
		}
		else if (fec.size() == 2)
		{
			auto it1 = fec.begin(), it2 = next(it1);
			if ((it1->first == 1 && it1->second == 1) || 
				(it2->first == 1 && it2->second == 1) || 
				(it1->first == it2->first + 1 && it1->second == 1) || 
				(it2->first == it1->first + 1 && it2->second == 1)) ans = i + 1; 
		}
	}
	cout << ans;
    return 0;
}
```

---

## 作者：Ag2WO4 (赞：5)

考虑以下几种可行的结构：

1. 所有数都一样，此时删除任意一个都不影响（其他数都是零个）。
2. 有一个数只有一个（其他数的个数都一样，无论是一个还是多个），删除它即可。
3. 有一个数比别的数多一个，删除它即可。

接下来，考虑可行的数据结构：统计每个数的数量，再统计数量的数量。这里用 Python 3 的字典来实现。然后分析：

1. 若数量多于三种，那显然不可能。
2. 若数量为两种，考虑第二种情况和第三种情况。由于字典只有两项，分别提取，看有没有某一项的值是一，以及这一项是不是一或比另一项多一。
3. 若数量为一种，考虑第一种和第二种情况的特例（每种数都只有一个）。此时，要么项为当前前缀的长度（第一种），要么项为一（第二种）。

通过统计数量和数量的数量的数据结构是可以做到 $O(n)$ 的。
#### 代码
```python
input();b={};c={};x=y=0
for i in map(int,input().split()):
    x+=1
    if i in b:
        c[b[i]]-=1
        if c[b[i]]==0:del c[b[i]]
        b[i]+=1
        if b[i]in c:c[b[i]]+=1
        else:c[b[i]]=1
    else:
        b[i]=1
        if 1 in c:c[1]+=1
        else:c[1]=1
    if len(c)==1:
        if 1 in c:y=x
        elif x in c:y=x
    if len(c)==2:
        if 1 in c:
            if c[1]==1:y=x
        d,e=c.keys()
        if d==e+1 and c[d]==1:y=x
        elif e==d+1 and c[e]==1:y=x
print(y)
```


---

## 作者：OIerZhang (赞：2)

# [CF1163B2 Cat Party (Hard Edition)](https://www.luogu.com.cn/problem/CF1163B2)

## 思路

要想每个数出现的次数相同，只能以下四种结构：

1. 所有数都一样，如 $[6, 6, 6, 6, 6]$。
2. 有一个数只出现一次，剩余的出现次数一样，如 $[1, 1, 4, 4, 5]$。
3. 每个数都只出现一次，如 $[1, 2, 3, 4, 5]$。
4. 有一个数出现 $x + 1$ 次，剩余的出现 $x$ 次，如 $[1, 1, 1, 4, 4]$。

而第二种和第三种等价。

第一种只需求出现次数最大值（`mx`），为 $1$ 即可。

第二种和第三种可以假设其余数出现次数（`mx`）相等，再求出这个出现次数出现的次数（`cc[mx]`），判断两者相乘再加 $1$ 是否刚好为序列长度。

第四种求出剩余数出现次数（`mx - 1`），再求出这个出现次数出现的次数（`cc[mx - 1]`），判断两者相乘再加 `mx` 是否刚好为序列长度。

然后我们就可以愉快的 [AC](https://codeforces.com/problemset/submission/1163/300788481) 啦！

## 代码

```cpp
#include <iostream>
#define int long long
using namespace std;

int a[100005], cnt[100005], cc[100005];

signed main()
{
    int n, mx = -2e9, ans = -1;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
    {
        cc[cnt[a[i]]]--;
        cnt[a[i]]++;
        cc[cnt[a[i]]]++;
        mx = max(mx, cnt[a[i]]);
        if (mx == 1)
            ans = i;
        else if (cc[mx] * mx == i - 1)
            ans = i;
        else if ((mx - 1) * cc[mx - 1] == i - mx)
            ans = i;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1163B2)

## 思路

我们可以将可选的前缀分为以下情况：
1. 每种数都只有 $1$ 个。
2. 有一种数只有 $1$ 个，其他数出现的数量一样。
3. 有一种数比其他数多出现 $1$ 次，其他数出现的的次数一样。

而且以上三种情况可以分别转化为以下三种：
1. 出现数量最多的数出现了 $1$ 次。
2. 出现数量最多的数每种数的数量与出现数量最多的数有多少种的乘积为 $k - 1$（剩下的那个是只出现了一次的那个数）。
3. 出现数量第二多的数每种数的数量与出现数量第二多的数有多少种的乘积加上出现数量最多的数每种数的数量为 $k$。

我们可以发现转化后的三种情况的非常数值只有：出现数量最多的数每种数的数量、出现数量最多的数有多少种、出现数量第二多的数每种数的数量、出现数量第二多的数有多少种、$k$。

## 具体过程

每输入一个数就进行以下操作：
* 分别判定断 $a_{i}$ 在 $[1, i - 1]$ 中出现的数量 $cnt_{a_{i}}$ 是否等于最大出现数量 $mx$ 或第二大出现数量 $mx2$，如果是则将其对应的种数 $cntmx$ 或 $cntmx2$ 减 $1$。
* 将 $cnt_{a_{i}}$ 加 $1$（统计上第 $i$ 个数 $a_{i}$）。
* 分别判断 $a_{i}$ 在 $[1, i]$ 中出现的数量 $cnt_{a_{i}}$ 是否等于最大出现数量 $mx$ 或第二大出现数量 $mx2$，如果是则将其对应的种数 $cntmx$ 或 $cntmx2$ 加 $1$。
* 判断 $cnt_{a_{i}}$ 是否要替换 $mx$ 或 $mx2$，如果是则替换并更新 $cntmx$ 与 $cntmx2$。
* 判断是否可以让 $k = i$，以下三种情况时可以：
  1. $mx = 1$。
  2. $mx \cdot cntmx + 1 = i$。
  3. $mx2 \cdot cntmx2 + mx = i$。

输出最大的 $k$。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (int i = ed; i >= st; --i)
#define fir first
#define sec second

//#define debug

typedef long long ll;
typedef double db;
typedef pair<ll, ll> pll;

const int maxn = 1e5 + 10;
const int maxval = 1e5 + 10;

int n;
int a[maxn];

int mx, cntmx, mx2, cntmx2, ans;
int cnt[maxval], cntcnt[maxn];

int main () {
	scanf("%i", &n);
	FOR (1, n, i) {
		scanf("%i", &a[i]);
		
		if (cnt[a[i]] == mx) {
			--cntmx;
		}else if (cnt[a[i]] == mx2) {
			--cntmx2;
		}
		cnt[a[i]]++;
		if (cnt[a[i]] == mx) {
			++cntmx;
		}else if (cnt[a[i]] == mx2) {
			++cntmx2;
		}
		if (cnt[a[i]] > mx) {
			mx2 = mx;
			cntmx2 = cntmx;
			mx = cnt[a[i]];
			cntmx = 1;
		}else if (cnt[a[i]] < mx && cnt[a[i]] > mx2) {
			mx2 = cnt[a[i]];
			cntmx2 = 1;
		}
		if (mx == 1/*每种数只有一个*/ || cntmx*mx == i - 1/*一个种只有一个*/ || cntmx2*mx2 + mx == i/*一种多一个*/) {
			ans = i;
		}
	}
	
	printf("%i", ans);
}
```

---

## 作者：czh___ (赞：0)

题意：

先给个 $n$，然后给 $n$ 个数组成的数组，要求输出一个 $k$，满足前 $k$ 个数去掉一个数之后剩下每种数的数量相同。输出 $k$ 的最大值。

分析：

读入的时候记录前 $n$ 个数字每一个数字出现的次数加上该出现次数的出现的次数。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int a[N],b[N],n,ans=1,t;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>t;
        b[++a[t]]++;
        if((a[t]*b[a[t]]==i)&&(i!=n))
            ans=i+1;
        if(a[t]*b[a[t]]==i-1)
            ans=i;
    }
    cout<<ans;
    return 0;
}
```

拜拜！

---

## 作者：_little_Cabbage_ (赞：0)

# CF1163B2 Cat Party (Hard Edition)题解
~~[博客观看食用更佳](https://www.luogu.com.cn/blog/958804/solution-cf1163b2)~~

此题与 [CF1163B1](https://www.luogu.com.cn/problem/CF1163B1) 一模一样，我的做法在这题也不会超时。

根据题意，我们可以知道在子序列 $[1,x]$ 中，要满足**其中任一元素后每个数出现的次数相同**这个条件，有如下三种情况：
- 所有元素出现次数都为 $1$，如序列 $[1,2,3,4,5]$。
- 除了一个出现次数为 $1$ 的元素，其他元素的出现次数都相等，如序列 $[1,2,2,3,3,4,4,5,5]$。
- 除了一个出现次数比其他数的出现次数多 $1$ 的元素，其他元素的出现次数都相等，如序列 $[1,1,2,2,3,3,4,4,4,5,5]$。

为什么呢？

让我们来分析一下：
- 对于第一种情况，以序列 $[1,2,3,4,5]$ 为例，删除其中任何一个数以后都能满足**其中任一元素后每个数出现的次数相同**。
- 对于第二种情况，以序列 $[1,2,2,3,3,4,4,5,5]$ 为例，删除 $1$ 以后就能满足**其中任一元素后每个数出现的次数相同**。
- 对于第三种情况，以序列 $[1,1,2,2,3,3,4,4,4,5,5]$ 为例，删除任意一个 $4$ 以后就能满足**其中任一元素后每个数出现的次数相同**。

这样就很容易写出 AC 代码了。

AC 代码：
```cpp
#include<bits/stdc++.h>
#define caozuo ret[cnt[u[i]]]--;cnt[u[i]]++;ret[cnt[u[i]]]++;
using namespace std;
int cnt[100010],ret[100010],u[100010];
int main()
{
	int n;
	scanf("%d",&n);
	int ans=0;
	int mx=INT_MIN;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&u[i]);
		caozuo
		mx=max(mx,cnt[u[i]]);
		if(mx==1)
		{
			ans=i;
			continue;
		}
		if(ret[mx]*mx==i-1)
		{
			ans=i;
			continue;
		}
		if((ret[(mx-1)]+1)*(mx-1)==i-1)
		{
			ans=i;
			continue;
		}
	}
	printf("%d",ans);
}
```
[AC 记录](https://www.luogu.com.cn/record/135890517)

---

## 作者：luuia (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1163B2)

~~这个题和 CF1163B1 基本差不多，本蒟蒻自己测了一下最坏情况也没有任何超时的问题。~~

### 题意
给定一个长度为 $n$ 的序列，从这个序列的第一项开始，长度为 $x$ 的子序列满足去掉其中任一元素后每个数出现的次数相同，求 $x$ 的最大值。

### 分析

序列的子序列 $[1,x]$ 中，去掉其中任一元素后每个数出现的次数相同，很显然分为 $3$ 种情况：

- 每一种元素均出现了 $1$ 次。

- 元素中有一种元素出现了 $1$ 次，其余出现的次数相同。

- 元素中有其他元素出现次数相等，一种元素比其他元素次数多 $1$ 次。

下面对这三种情况进行分析：

#### 每一种元素均出现了 $1$ 次

从 $1$ 遍历到 $n$，每次输入统计子序列 $[1,i]$ 每种元素出现的次数，然后统计所有颜色次数的最大值，如果为 $1$，就符合题意，更新答案为当前序列的长度。

#### 元素中有一种元素出现了 $1$ 次，其余出现的次数相同

统计每一种颜色出现的次数，再统计其中的最小值，如果为 $1$ 且其他相等那么符合题意，更新答案为当前序列的长度。

#### 元素中有其他元素出现次数相等，一种元素比其他元素次数多 $1$ 次

统计每一种颜色出现的次数，再统计其中的最大值，如果其他相等，而且最大值比其他的大 $1$，那么符合题意，更新答案为当前序列的长度。

那么，我们可以写出本题的 AC 代码。

### 代码
下面是 AC 代码：[AC 代码](https://www.luogu.com.cn/paste/wfvgjutb)
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n,maxinum = -10,x = 0,a[100010],b[100010],u[100010],i;
    cin >> n;
    for(i = 1;i <= n;i++)                                                            
	{
		cin >> u[i];
	} 
    for(i = 1;i <= n;i++)
    {
        int p = b[u[i]];
        a[p] -= 1;
        b[u[i]] += 1;
        p += 1;
        a[p] += 1;
        maxinum = max(b[u[i]],maxinum);
        if (((maxinum == 1) || (a[maxinum] * maxinum == i - 1)) || (((maxinum - 1) * (a[maxinum - 1] + 1)) == i - 1)) x = i;
    }
    cout << x << endl;
    return 0;
}

```




---

## 作者：FwbAway (赞：0)

先判断他们原始序列，把他们存进一个数组里，然后判断这个数组里的最多出现的次数是多少次，然后把多的剪掉，存进 $sum$ 里面，少的把他全部去掉，也存进 $sum$ 里面，因为总共 $n$ 个数，又去掉了 $sum$ 个，所以还剩的就是 $n-sum$ 了。

注意：

- 这里面有个坑，如果去掉数之后里面的数还剩 $0$ 个（也就是 $n-sum=0$），就不能去掉那个数，输出 $n$ 才对。

- 如果一开始发现这里面的所有数都是不同的，也就是均值有可能是小数，就要提前判断，直接输出 $n$，结束就行了。

- 如果遇到全是相同的数字，可以直接输出 $n$ 了，因为相同的数字是一个也不用去的。

---

