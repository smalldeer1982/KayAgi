# 题目信息

# Make Equal Again

## 题目描述

You have an array $ a $ of $ n $ integers.

You can no more than once apply the following operation: select three integers $ i $ , $ j $ , $ x $ ( $ 1 \le i \le j \le n $ ) and assign all elements of the array with indexes from $ i $ to $ j $ the value $ x $ . The price of this operation depends on the selected indices and is equal to $ (j - i + 1) $ burles.

For example, the array is equal to $ [1, 2, 3, 4, 5, 1] $ . If we choose $ i = 2, j = 4, x = 8 $ , then after applying this operation, the array will be equal to $ [1, 8, 8, 8, 5, 1] $ .

What is the least amount of burles you need to spend to make all the elements of the array equal?

## 样例 #1

### 输入

```
8
6
1 2 3 4 5 1
7
1 1 1 1 1 1 1
8
8 8 8 1 2 8 8 8
1
1
2
1 2
3
1 2 3
7
4 3 2 7 1 1 3
9
9 9 2 9 2 5 5 5 3```

### 输出

```
4
0
2
0
1
2
6
7```

# AI分析结果

### 题目内容翻译
## 再次使元素相等

### 题目描述
你有一个包含 $n$ 个整数的数组 $a$。

你最多可以进行一次以下操作：选择三个整数 $i$、$j$、$x$（$1 \le i \le j \le n$），并将数组中从索引 $i$ 到 $j$ 的所有元素赋值为 $x$。此操作的代价取决于所选的索引，等于 $(j - i + 1)$ 伯尔（burles，一种货币单位）。

例如，数组为 $[1, 2, 3, 4, 5, 1]$。如果我们选择 $i = 2$，$j = 4$，$x = 8$，那么应用此操作后，数组将变为 $[1, 8, 8, 8, 5, 1]$。

你需要花费的最少伯尔数是多少，才能使数组的所有元素相等？

### 样例 #1
#### 输入
```
8
6
1 2 3 4 5 1
7
1 1 1 1 1 1 1
8
8 8 8 1 2 8 8 8
1
1
2
1 2
3
1 2 3
7
4 3 2 7 1 1 3
9
9 9 2 9 2 5 5 5 3
```

#### 输出
```
4
0
2
0
1
2
6
7
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是先找出数组中从左到右和从右到左的最长连续相同元素的长度，然后根据数组首尾元素是否相等分情况讨论来计算最小操作代价。
- **思路对比**：大部分题解思路一致，都是通过统计左右连续相同元素的长度，再根据首尾元素是否相等确定最终答案。如 `vectorxyz` 题解分三种情况讨论，`RyanLi` 题解根据最终元素一定是 $a_1$ 或 $a_n$ 来维护连续出现个数。
- **算法要点**：主要是遍历数组统计连续相同元素的长度，然后根据条件计算操作代价。
- **解决难点**：关键在于正确处理数组首尾元素相等和不相等的不同情况，以及边界条件的处理，如数组元素全部相同的情况。

### 评分较高的题解
- **vectorxyz（4星）**
    - **关键亮点**：思路清晰，代码简洁，分情况讨论明确。
    - **个人心得**：赛事一开始把题目看成区间动规了。
- **RyanLi（4星）**
    - **关键亮点**：给出了题目传送门和更佳阅读体验的博客链接，思路简洁明了。

### 关键思路或技巧
- 先统计数组中从左到右和从右到左的最长连续相同元素的长度。
- 根据数组首尾元素是否相等分情况计算最小操作代价：若相等，操作中间不同的部分；若不相等，选择保留较长的连续相同部分，操作剩余部分。

### 拓展思路
同类型题或类似算法套路：这类模拟题通常需要根据题目给定的操作规则，通过遍历和条件判断来计算结果。可以关注一些涉及区间操作、数组元素修改的模拟题，例如一些需要对数组进行多次操作，然后求最优结果的题目。

### 推荐洛谷题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 重点代码
#### vectorxyz 题解核心代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int a[N];

signed main()
{
    int T;
    cin >> T;
    while(T -- ){
        int n, ans = LONG_LONG_MAX;
        cin >> n;
        for(int i = 1;i <= n;i ++) cin >> a[i];
    
        int l = 1,r = n;
        
        while(l + 1 <= n && a[l + 1] == a[l]) l ++;
        while(r - 1 >= 1 && a[r - 1] == a[r]) r --;
        
        if(a[1] == a[n]) {
            ans =  min(ans, max(r - l - 1,(long long)0));
        }
        ans = min(min(n - l, r - 1), ans);
        
        cout << max((long long)0, ans) << endl;
    }
    return 0;
}
```
**核心实现思想**：先输入数组，然后分别从左到右和从右到左找到最长连续相同元素的边界 $l$ 和 $r$。根据数组首尾元素是否相等分情况计算最小操作代价，最后输出结果。

#### RyanLi 题解核心代码
```cpp
#include <iostream>
using namespace std;

const int N = 2e5 + 10;
int t, n, a[N], l, r;

int main() {
    scanf("%d", &t);
    while (t--) {
        l = r = 1;
        scanf("%d%d", &n, &a[1]);
        for (int i = 2; i <= n; ++i) {
            scanf("%d", &a[i]);
            if (a[i] == a[i - 1] && l == i - 1) l = i;  // 更新左端点
            if (a[i] != a[i - 1]) r = i;  // 更新右端点
        } if (a[1] == a[n]) printf("%d\n", max(r - l - 1, 0));
        else printf("%d\n", min(n - l, r - 1));
    } return 0;
}
```
**核心实现思想**：输入多组数据，对于每组数据，在输入数组的过程中更新左端点 $l$ 和右端点 $r$，根据数组首尾元素是否相等输出最小操作代价。

---
处理用时：39.97秒