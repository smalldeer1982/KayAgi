# 题目信息

# Make It Permutation

## 题目描述

You have an integer array $ a $ of length $ n $ . There are two kinds of operations you can make.

- Remove an integer from $ a $ . This operation costs $ c $ .
- Insert an arbitrary positive integer $ x $ to any position of $ a $ (to the front, to the back, or between any two consecutive elements). This operation costs $ d $ .

You want to make the final array a permutation of any positive length. Please output the minimum cost of doing that. Note that you can make the array empty during the operations, but the final array must contain at least one integer.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the array is already a permutation, so there's no need for operations.

In the second test case, we can remove numbers $ 5 $ , $ 6 $ to get the permutation $ [1,2,3] $ in cost $ 2 $ . Note that we can also get a permutation by inserting a number $ 4 $ , but it costs $ 5 $ .

In the third test case, we can just remove all the numbers except for the first number $ 1 $ . It costs $ 8 $ , and the final array is $ [1] $ , which is a permutation of length $ 1 $ .

In the fourth test case, we can remove all the numbers except for $ 2 $ , and insert a number $ 1 $ to the first position. It costs $ 4+10=14 $ , and the final array is $ [1,2] $ , which is a permutation of length $ 2 $ .

## 样例 #1

### 输入

```
8
3 3 3
1 2 3
5 1 5
1 2 3 5 6
5 2 3
1 1 1 3 3
5 1 10
2 4 6 8 10
6 2 8
7 3 5 4 4 8
4 10 1
1 2 6 7
4 3 3
2 5 8 7
2 1000000000 1
1000000000 1```

### 输出

```
0
2
8
14
20
3
12
999999998```

# AI分析结果

### 题目内容重写

#### 题目描述

你有一个长度为 $n$ 的整数数组 $a$。你可以进行以下两种操作：

- 从 $a$ 中删除一个整数，这个操作的代价为 $c$。
- 在 $a$ 的任意位置插入一个任意的正整数 $x$（可以插入到最前面、最后面或任意两个连续元素之间），这个操作的代价为 $d$。

你的目标是将最终的数组变成一个任意正长度的排列。请输出完成这个目标的最小代价。注意，在操作过程中你可以将数组变为空，但最终的数组必须至少包含一个整数。

一个长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的 $n$ 个不同整数组成的数组，顺序可以任意。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 出现了两次），$[1,3,4]$ 也不是排列（因为 $n=3$ 但数组中出现了 $4$）。

#### 说明/提示

在第一个测试用例中，数组已经是一个排列，因此不需要进行操作。

在第二个测试用例中，我们可以删除数字 $5$ 和 $6$，得到排列 $[1,2,3]$，代价为 $2$。注意，我们也可以通过插入数字 $4$ 来得到一个排列，但这样做的代价是 $5$。

在第三个测试用例中，我们可以删除除第一个数字 $1$ 之外的所有数字，代价为 $8$，最终的数组是 $[1]$，这是一个长度为 $1$ 的排列。

在第四个测试用例中，我们可以删除除 $2$ 之外的所有数字，并在最前面插入数字 $1$，代价为 $4+10=14$，最终的数组是 $[1,2]$，这是一个长度为 $2$ 的排列。

#### 样例 #1

##### 输入

```
8
3 3 3
1 2 3
5 1 5
1 2 3 5 6
5 2 3
1 1 1 3 3
5 1 10
2 4 6 8 10
6 2 8
7 3 5 4 4 8
4 10 1
1 2 6 7
4 3 3
2 5 8 7
2 1000000000 1
1000000000 1
```

##### 输出

```
0
2
8
14
20
3
12
999999998
```

### 算法分类

贪心

### 题解分析与结论

#### 综合分析与结论

本题的核心思路是通过贪心策略，枚举可能的排列长度，并计算每种情况下的最小代价。主要步骤如下：

1. **去重与排序**：首先对数组进行去重和排序，确保数组中不包含重复元素，并且元素有序排列。
2. **枚举排列长度**：枚举可能的排列长度，计算将数组转换为该长度排列的代价。代价包括删除多余元素和插入缺失元素的成本。
3. **特判全删留1的情况**：考虑将数组全部删除，然后插入一个1的情况，确保不会遗漏最优解。

#### 所选高星题解

##### 题解1：abensyl (4星)

**关键亮点**：
- 代码简洁，思路清晰。
- 通过去重和排序后，枚举每个可能的排列长度，计算最小代价。
- 特别处理了全删留1的情况，确保不会遗漏最优解。

**核心代码**：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
#define int long long
const int N = 200005;
int a[N];
signed main() {
  int TT;
  cin >> TT;
  while (TT--) {
    int n, c, d;
    cin >> n >> c >> d;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int res = d * 1 + c * n;
    sort(a + 1, a + n + 1);
    int len = unique(a + 1, a + n + 1) - a - 1;
    for (int i = 1; i <= len; ++i) res = min(res, c * (n - i) + d * (a[i] - i));
    cout << res << '\n';
  }
  return 0;
}
```

##### 题解2：sto_5k_orz (4星)

**关键亮点**：
- 思路清晰，代码简洁。
- 通过去重和排序后，枚举每个可能的排列长度，计算最小代价。
- 特别处理了全删留1的情况，确保不会遗漏最优解。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define CI const int
#define gc getchar
#define Mt(a, b) memset(a, b, sizeof a)
#define pc putchar
#define W while
#define I inline
#define pb push_back
#define int long long
namespace SlowIO{
	I int read() {
		int x = 0, f = 1; char ch = gc();
		W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
		W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
		return x * f;
	}
	I void Read(int &x) {x = read();}
	I void Read(int &x, int &y) {Read(x), Read(y);}
} using namespace SlowIO;
const int N = 100010; int a[N], b[N], n;
signed main() {
	int t, c, d; Read(t);
	W(t--) {
		Read(n, c); Read(d);
		for(int i = 1; i <= n; i++) Read(a[i]), b[i] = a[i]; int mi = n * c + d; // 特判全删留 1 的情况
		sort(b + 1, b + 1 + n); int m = unique(b + 1, b + 1 + n) - b - 1;
		for(int i = 1; i <= m; i++) {
//			cout << i << ' ' << b[i] << endl;
			mi = min(mi, (n - i) * c + (b[i] - i) * d);
		}
		cout << mi << endl;
	}
	return 0;
}
```

##### 题解3：inc1ude_c (4星)

**关键亮点**：
- 思路清晰，代码简洁。
- 通过去重和排序后，枚举每个可能的排列长度，计算最小代价。
- 特别处理了全删留1的情况，确保不会遗漏最优解。

**核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;

ll T;
ll n, c, d;
ll a[200010];
vector<vector<ll> > book;
ll ans;

void init(){
    book.clear();
    ans = 0x3f3f3f3f;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        init();
        cin >> n >> c >> d;
        for(ll i = 1; i <= n; i++){
            cin >> a[i];
        }
        sort(a + 1, a + n + 1);
        vector<ll> ve;
        ll now = a[1];
        ve.push_back(now);
        for(int i = 2; i <= n; i++){
            if(a[i] != now){
                book.push_back(ve);
                ve.clear();
                now = a[i];
            }
            ve.push_back(a[i]);
        }
        book.push_back(ve);
        ve.clear();
        ll cnt1 = 0; // 重复
        ll cnt2 = 0; // 到现在为止有多少个数
        ans = d + c * n;
        for(int i = 0; i < book.size(); i++){
            cnt1 += book[i].size() - 1;
            cnt2 += book[i].size();
            ans = min(ans, cnt1 * c + (book[i][0] - i - 1) * d + (n - cnt2) * c);
        }
        cout << ans << endl;
    }
    return 0;
}
```

### 最优关键思路或技巧

1. **去重与排序**：首先对数组进行去重和排序，确保数组中不包含重复元素，并且元素有序排列。
2. **枚举排列长度**：枚举可能的排列长度，计算将数组转换为该长度排列的代价。代价包括删除多余元素和插入缺失元素的成本。
3. **特判全删留1的情况**：考虑将数组全部删除，然后插入一个1的情况，确保不会遗漏最优解。

### 可拓展之处

类似的问题可以通过贪心策略和枚举法来解决，尤其是在涉及最小代价或最优解的问题中。例如，可以考虑在数组中插入或删除元素，使得数组满足某种特定条件（如单调性、特定排列等）。

### 推荐题目

1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得

在调试过程中，特别需要注意边界情况，例如数组为空或只有一个元素的情况。此外，枚举排列长度时，确保不会遗漏全删留1的情况，这是本题的一个关键点。

---
处理用时：59.31秒