# Hiring Staff

## 题目描述

A new Berland businessman Vitaly is going to open a household appliances' store. All he's got to do now is to hire the staff.

The store will work seven days a week, but not around the clock. Every day at least $ k $ people must work in the store.

Berland has a law that determines the order of working days and non-working days. Namely, each employee must work for exactly $ n $ consecutive days, then rest for exactly $ m $ days, then work for $ n $ more days and rest for $ m $ more, and so on. Vitaly doesn't want to break the law. Fortunately, there is a loophole: the law comes into force on the day when the employee is hired. For example, if an employee is hired on day $ x $ , then he should work on days $ [x,x+1,...,x+n-1] $ , $ [x+m+n,x+m+n+1,...,x+m+2n-1] $ , and so on. Day $ x $ can be chosen arbitrarily by Vitaly.

There is one more thing: the key to the store. Berland law prohibits making copies of keys, so there is only one key. Vitaly is planning to entrust the key to the store employees. At the same time on each day the key must be with an employee who works that day — otherwise on this day no one can get inside the store. During the day the key holder can give the key to another employee, if he also works that day. The key will handed to the first hired employee at his first working day.

Each employee has to be paid salary. Therefore, Vitaly wants to hire as few employees as possible provided that the store can operate normally on each day from $ 1 $ to infinity. In other words, on each day with index from $ 1 $ to infinity, the store must have at least $ k $ working employees, and one of the working employees should have the key to the store.

Help Vitaly and determine the minimum required number of employees, as well as days on which they should be hired.

## 样例 #1

### 输入

```
4 3 2
```

### 输出

```
4
1 1 4 5```

## 样例 #2

### 输入

```
3 3 1
```

### 输出

```
3
1 3 5```

# 题解

## 作者：ShwStone (赞：1)

## 思路分析

可以发现 $n + m$ 天之后必然是循环的。所以考虑前 $n + m$ 天。

首先第一天必然要雇佣 $k$ 个人。然后一天一天往后扫，直到遇到一天不足 $k$ 人。假设这一天只有 $x$ 人。如果 $x=0$，那么先在前一天雇佣一个人拿钥匙，然后再在这一天雇佣 $k-1$ 个人（为了使人数最少，显然雇佣越晚越好）。否则直接在这一天雇佣 $k-x$ 人。

最后要考虑 $n+m+1$ 天能否拿到钥匙。由于循环性，这一天的上班人数已经够了（第一天的 $k$ 个人回来了），但如果从 $m + 1$ 天开始都没有雇佣过员工，会出现没有钥匙的情况。要单独判断，再多雇佣一个人送钥匙。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

// #define FILE_IO
namespace io {...}; // https://shwst.one/2022/07/14/%E6%A8%A1%E6%9D%BF/
using namespace io;

const int maxn = 4e3 + 5;

int n, m, k;

int cnt[maxn];
vector<int> ans;

int main() {
    read(n); read(m); read(k);
    for (int i = 1; i <= n; i++) {
        cnt[i] = k;
    }
    for (int i = 1; i <= k; i++) {
        ans.emplace_back(1);
    }
    for (int i = n + 1; i <= n + m; i++) {
        if (cnt[i] < k) {
            if (cnt[i] == 0) {
                for (int j = 1; j <= n; j++) cnt[i + j - 2]++;
                ans.emplace_back(i - 1);
            }
            while (cnt[i] < k) {
                for (int j = 1; j <= n; j++) cnt[i + j - 1]++;
                ans.emplace_back(i);
            }
        }
    }
    if (!cnt[n + m + 1]) {
        ans.emplace_back(n + m);
    }
    write(ans.size());
    for (int x : ans) {
        write(x, ' ');
    }
    return 0;
}
```


---

## 作者：_xbn (赞：1)

首先考虑 $k=1$ 特殊情况。

由于有员工要来自前一天工作，又要保证雇佣员工最少，所以我们可以让一个员工来自前一天。所以在第 $n$ 天我们要加入 $1$ 个员工。

推广到一般。

我们按照 $k=1$ 的类似方法。由于有员工要来自前一天工作，又要保证雇佣员工最少，所以我们可以让一个员工来自前一天。剩下 $k-1$ 个员工在 $n+1$ 天加入工作。

还有一种特殊情况，当 $n=m$ 时，在第 $n$ 天加入的员工在 $n+m$ 天已经休息了，要保证在 $n+m$ 天有足够的员工，我们可以在 $n+2$ 天加入一个员工。

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 100002;
int n, m, k, p, q, ans, t, l, r, sum, tot, cnt, a[N], b[N], c[N], d[N];
vector<int> v;
inline int rd()
{
	int f = 1, x = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
int main()
{
	n = rd(), m = rd(), k = rd();
	if(k == 1) 
	{
		for (int i = 1; i <= n + m; i = i + n - 1) v.pb(i);
		cout << v.size() << endl;
		for (auto i : v) cout << i << " ";
		return 0;
	}
	for (int i = 1; i <= k; i++) v.pb(1);
	v.pb(n);
	for (int i = 2; i <= k; i++) v.pb(n + 1);
	if(n == m) v.pb(n + 2);
	cout << v.size() << endl;
	for (auto i : v) cout << i << " ";
	return 0;
}
```



---

