# 题目信息

# AND Sorting

## 题目描述

You are given a permutation $ p $ of integers from $ 0 $ to $ n-1 $ (each of them occurs exactly once). Initially, the permutation is not sorted (that is, $ p_i>p_{i+1} $ for at least one $ 1 \le i \le n - 1 $ ).

The permutation is called $ X $ -sortable for some non-negative integer $ X $ if it is possible to sort the permutation by performing the operation below some finite number of times:

- Choose two indices $ i $ and $ j $ $ (1 \le i \lt j \le n) $ such that $ p_i \& p_j = X $ .
- Swap $ p_i $ and $ p_j $ .

Here $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

Find the maximum value of $ X $ such that $ p $ is $ X $ -sortable. It can be shown that there always exists some value of $ X $ such that $ p $ is $ X $ -sortable.

## 说明/提示

In the first test case, the only $ X $ for which the permutation is $ X $ -sortable are $ X = 0 $ and $ X = 2 $ , maximum of which is $ 2 $ .

Sorting using $ X = 0 $ :

- Swap $ p_1 $ and $ p_4 $ , $ p = [2, 1, 3, 0] $ .
- Swap $ p_3 $ and $ p_4 $ , $ p = [2, 1, 0, 3] $ .
- Swap $ p_1 $ and $ p_3 $ , $ p = [0, 1, 2, 3] $ .

Sorting using $ X = 2 $ :

- Swap $ p_3 $ and $ p_4 $ , $ p = [0, 1, 2, 3] $ .

In the second test case, we must swap $ p_1 $ and $ p_2 $ which is possible only with $ X = 0 $ .

## 样例 #1

### 输入

```
4
4
0 1 3 2
2
1 0
7
0 1 2 3 5 6 4
5
0 3 2 1 4```

### 输出

```
2
0
4
1```

# AI分析结果

### 题目中文重写
## AND排序

### 题目描述
给定一个从 0 到 n - 1 的排列 p（每个数恰好出现一次）。初始时，该排列是无序的（即至少存在一个 1 ≤ i ≤ n - 1 使得 p[i] > p[i + 1]）。

对于某个非负整数 X，如果可以通过执行以下操作有限次来对排列进行排序，则称该排列是 X 可排序的：
- 选择两个索引 i 和 j（1 ≤ i < j ≤ n），使得 p[i] & p[j] = X。
- 交换 p[i] 和 p[j]。

这里 & 表示[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)。

找出最大的 X 值，使得排列 p 是 X 可排序的。可以证明，总是存在某个 X 值使得排列 p 是 X 可排序的。

### 说明/提示
在第一个测试用例中，排列是 X 可排序的 X 值只有 X = 0 和 X = 2，其中最大值是 2。

使用 X = 0 进行排序：
- 交换 p[1] 和 p[4]，p = [2, 1, 3, 0]。
- 交换 p[3] 和 p[4]，p = [2, 1, 0, 3]。
- 交换 p[1] 和 p[3]，p = [0, 1, 2, 3]。

使用 X = 2 进行排序：
- 交换 p[3] 和 p[4]，p = [0, 1, 2, 3]。

在第二个测试用例中，我们必须交换 p[1] 和 p[2]，这只有在 X = 0 时才可能。

### 样例 #1
#### 输入
```
4
4
0 1 3 2
2
1 0
7
0 1 2 3 5 6 4
5
0 3 2 1 4
```

#### 输出
```
2
0
4
1
```

### 题解综合分析与结论
- **思路总结**：各题解核心思路一致，均认为要使排列有序，需将不在正确位置（即 p[i]!= i）的数进行交换，最大的 X 是这些不在正确位置的数按位与的结果。
- **算法要点**：遍历排列，找出不在正确位置的数，将它们按位与得到最终结果。部分题解使用数组或 vector 存储这些数，部分题解直接在遍历过程中进行按位与操作。
- **解决难点**：主要难点在于理解为什么将不在正确位置的数按位与就能得到最大的 X。这是因为要交换两个数 p[i] 和 p[j]，必须满足 p[i] & p[j] = X，而所有需要交换的数都要满足这个条件，所以最大的 X 就是这些数按位与的结果。

### 所选题解
- **作者：yitian_（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细解释了如何通过遍历排列找到最大的 X。
    - **核心代码**：
```c
#include<bits/stdc++.h>
using namespace std;

int p[200010];

int main() 
{
    int t,n;
    cin >> t;
    while(t--)
    {
        cin >> n;
        int ans=-1;
        for(int i=0;i<n;i++)
        {
            cin >> p[i];
            if(p[i]!=i)
            {
                if(ans==-1)
                {
                    ans=p[i];
                }
                else
                {
                    ans&=p[i];
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```
    - **核心实现思想**：使用 ans 存储最终结果，初始化为 -1。遍历排列，若当前元素不在正确位置，若 ans 未赋值则将该元素赋值给 ans，否则将 ans 与该元素按位与。

- **作者：EternalHeart1314（4星）**
    - **关键亮点**：结合样例解释思路，代码简洁易读。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N(2e5 + 7);
int t, n, x, tot, a[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> t;
    while(t --) {
        cin >> n;
        tot = 0;
        for(int i(0); i < n; ++ i) {
            cin >> x;
            if(x!= i) {
                a[tot ++] = x;
            }
        }
        for(int i(1); i < tot; ++ i) {
            a[0] &= a[i];
        }
        cout << a[0] << '\n';
    }
    return 0;
}
```
    - **核心实现思想**：使用数组 a 存储不在正确位置的数，遍历排列将这些数存入数组，然后将数组中所有数按位与到 a[0] 上，最后输出 a[0]。

- **作者：hdkghc（4星）**
    - **关键亮点**：详细解释了按位与的性质，为思路提供了理论支持。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t;

int _main()
{
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int ans = -1;
        for(int i = 0; i < n - 1; i++)
        {
            int x;
            cin >> x;
            if(x!= i)
            {
                ans &= x;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```
    - **核心实现思想**：使用 ans 存储最终结果，初始化为 -1。遍历排列，若当前元素不在正确位置，将 ans 与该元素按位与。

### 最优关键思路或技巧
- **思维方式**：通过分析排列排序的过程，发现要使排列有序，所有不在正确位置的数都需要参与交换，而交换的条件是按位与等于 X，从而得出最大的 X 是这些数按位与的结果。
- **代码实现技巧**：使用 -1 作为初始值，因为 -1 按位与任何数都等于该数本身，方便进行按位与操作。

### 可拓展之处
同类型题或类似算法套路：
- 涉及排列和位运算的题目，如通过位运算判断排列是否满足某种条件。
- 利用位运算的性质解决排序或交换问题。

### 推荐洛谷题目
- [P1100 高低位交换](https://www.luogu.com.cn/problem/P1100)
- [P1828 香甜的黄油](https://www.luogu.com.cn/problem/P1828)
- [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)

### 个人心得摘录与总结
- **听取MLE声一片**：提到这道题让自己直接送了 -83，说明做题时可能遇到了逻辑问题，后来修改后才解决。这提醒我们做题时要仔细思考逻辑，避免出现错误。
- **eb0ycn**：一开始以为是排序题，后来发现题目特殊条件可以免去排序步骤。这告诉我们做题时要仔细审题，充分利用题目条件，避免做不必要的操作。

---
处理用时：40.18秒