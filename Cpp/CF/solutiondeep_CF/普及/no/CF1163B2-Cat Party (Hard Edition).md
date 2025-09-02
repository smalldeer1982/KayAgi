# 题目信息

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

# AI分析结果

### 题目重写
#### Cat Party (Hard Edition)

**题目描述**

这个问题与之前的问题相同，但约束条件更大。

Shiro刚刚搬到了新房子。她想要邀请所有的朋友来家里玩大富翁。然而，她的房子太小了，所以她一次只能邀请一个朋友。

在Shiro搬到新房子后的$n$天里，每天都会有一只猫来到Shiro的家。第$i$天来的猫的丝带颜色为$u_i$。Shiro想知道最大的数字$x$，使得如果我们考虑前$x$天的连续天数，可以从中删除恰好一天，使得剩下的$x - 1$天中，每种丝带颜色的出现次数都相同。

例如，考虑以下$u_i$序列：$[2, 2, 1, 1, 5, 4, 4, 5]$。那么$x = 7$是一个有效的连续天数，因为如果我们删除最左边的$u_i = 5$，剩下的前$x - 1$天中，每种丝带颜色都恰好出现了两次。注意，$x = 8$不是一个有效的连续天数，因为必须删除恰好一天。

由于Shiro只是一只猫，她不擅长计数，需要你的帮助来找到最长的连续天数。

**说明/提示**

在第一个例子中，我们可以选择最长的连续天数为$13$天，因为删除这个连续天数中的最后一天后，剩下的颜色$1$、$2$、$3$和$4$都出现了$3$次。注意，连续天数也可以是$10$天（通过删除这个连续天数中的第$10$天），但我们感兴趣的是最长的连续天数。

在第四个例子中，如果我们取前$6$天的连续天数，可以删除这个连续天数中的第三天，然后剩下的颜色$1$、$2$、$3$、$4$和$5$都恰好出现了一次。

**样例 #1**

**输入**

```
13
1 1 1 2 2 2 3 3 3 4 4 4 5
```

**输出**

```
13
```

**样例 #2**

**输入**

```
5
10 100 20 200 1
```

**输出**

```
5
```

**样例 #3**

**输入**

```
1
100000
```

**输出**

```
1
```

**样例 #4**

**输入**

```
7
3 2 1 1 4 5 1
```

**输出**

```
6
```

**样例 #5**

**输入**

```
6
1 1 1 2 2 2
```

**输出**

```
5
```

### 算法分类
**模拟**

### 题解分析与结论

本题的核心在于通过模拟和统计来找到满足条件的最长连续天数。各题解的思路大致相同，主要通过维护两个哈希表（或类似结构）来记录每种颜色的出现次数以及每种出现次数的数量，然后在遍历过程中不断更新这些统计信息，并检查是否满足题目要求。

### 评分较高的题解

#### 题解1：作者：OIerWu_829 (赞：6)
**星级：5星**
**关键亮点：**
- 使用两个哈希表`cnt`和`fec`分别记录每种颜色的出现次数和每种出现次数的数量。
- 通过遍历数组，动态更新哈希表，并在每次更新后检查是否满足条件。
- 代码简洁，逻辑清晰，易于理解。

**核心代码：**
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

#### 题解2：作者：OIerZhang (赞：2)
**星级：4星**
**关键亮点：**
- 通过维护最大出现次数`mx`和出现次数的数量`cc`来检查是否满足条件。
- 代码结构清晰，逻辑严谨，易于理解。

**核心代码：**
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

#### 题解3：作者：Peter20122012 (赞：0)
**星级：4星**
**关键亮点：**
- 通过维护最大出现次数`mx`和第二大出现次数`mx2`及其对应的数量`cntmx`和`cntmx2`来检查是否满足条件。
- 代码逻辑清晰，结构合理，易于理解。

**核心代码：**
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

### 最优关键思路或技巧
- **哈希表的使用**：通过维护两个哈希表来记录每种颜色的出现次数和每种出现次数的数量，可以高效地检查是否满足题目要求。
- **动态更新与检查**：在遍历数组的过程中，动态更新哈希表，并在每次更新后检查是否满足条件，确保算法的实时性和准确性。

### 可拓展之处
- **类似问题**：类似的问题可以通过维护多个哈希表或数组来统计不同维度的信息，从而高效地解决问题。
- **算法优化**：可以通过进一步优化哈希表的更新和检查过程，减少不必要的计算，提高算法的效率。

### 推荐题目
1. [P1163 找硬币](https://www.luogu.com.cn/problem/P1163)
2. [P1164 小A的糖果](https://www.luogu.com.cn/problem/P1164)
3. [P1165 小A的糖果2](https://www.luogu.com.cn/problem/P1165)

---
处理用时：65.87秒