# 题目信息

# Medians

## 题目描述

You are given an array $ a = [1, 2, \ldots, n] $ , where $ n $ is odd, and an integer $ k $ .

Your task is to choose an odd positive integer $ m $ and to split $ a $ into $ m $ subarrays $ ^{\dagger} $ $ b_1, b_2, \ldots, b_m $ such that:

- Each element of the array $ a $ belongs to exactly one subarray.
- For all $ 1 \le i \le m $ , $ |b_i| $ is odd, i.e., the length of each subarray is odd.
- $ \operatorname{median}([\operatorname{median}(b_1), \operatorname{median}(b_2), \ldots, \operatorname{median}(b_m)]) = k $ , i.e., the median $ ^{\ddagger} $ of the array of medians of all subarrays must equal $ k $ . $ \operatorname{median}(c) $ denotes the median of the array $ c $ .

 $ ^{\dagger} $ A subarray of the array $ a $ of length $ n $ is the array $ [a_l, a_{l + 1}, \ldots, a_r] $ for some integers $ 1 \le l \le r \le n $ .

 $ ^{\ddagger} $ A median of the array of odd length is the middle element after the array is sorted in non-decreasing order. For example: $ \operatorname{median}([1,2,5,4,3]) = 3 $ , $ \operatorname{median}([3,2,1]) = 2 $ , $ \operatorname{median}([2,1,2,1,2,2,2]) = 2 $ .

## 说明/提示

In the first test case, the given partition has $ m = 1 $ and $ b_1 = [1] $ . It is obvious that $ \operatorname{median}([\operatorname{median}([1])]) = \operatorname{median}([1]) = 1 $ .

In the second test case, the given partition has $ m = 3 $ and:

- $ b_1 = [1] $
- $ b_2 = [2] $
- $ b_3 = [3] $

Therefore, $ \operatorname{median}([\operatorname{median}([1]), \operatorname{median}([2]), \operatorname{median}([3])]) = \operatorname{median}([1, 2, 3]) = 2 $ .

In the third test case, there is no valid partition for $ k = 3 $ .

In the fourth test case, the given partition has $ m = 5 $ and:

- $ b_1 = [1, 2, 3] $
- $ b_2 = [4, 5, 6] $
- $ b_3 = [7, 8, 9] $
- $ b_4 = [10, 11, 12] $
- $ b_5 = [13, 14, 15] $

Therefore, $ \operatorname{median}([\operatorname{median}([1, 2, 3]), \operatorname{median}([4, 5, 6]), \operatorname{median}([7, 8, 9]), \operatorname{median}([10, 11, 12]), \operatorname{median}([13, 14, 15])]) = \operatorname{median}([2, 5, 8, 11, 14]) = 8 $ .

## 样例 #1

### 输入

```
4
1 1
3 2
3 3
15 8```

### 输出

```
1
1
3
1 2 3
-1
5
1 4 7 10 13```

# AI分析结果

### 题目中文重写
# 中位数

## 题目描述
给定一个数组 $a = [1, 2, \ldots, n]$，其中 $n$ 为奇数，以及一个整数 $k$。

你的任务是选择一个正奇数 $m$，并将数组 $a$ 划分为 $m$ 个子数组 $b_1, b_2, \ldots, b_m$，满足以下条件：
- 数组 $a$ 中的每个元素恰好属于一个子数组。
- 对于所有 $1 \le i \le m$，$|b_i|$ 为奇数，即每个子数组的长度为奇数。
- $\operatorname{median}([\operatorname{median}(b_1), \operatorname{median}(b_2), \ldots, \operatorname{median}(b_m)]) = k$，即所有子数组中位数组成的数组的中位数必须等于 $k$。$\operatorname{median}(c)$ 表示数组 $c$ 的中位数。

### 说明
- 数组 $a$ 长度为 $n$ 的子数组是指对于某些整数 $1 \le l \le r \le n$，由 $[a_l, a_{l + 1}, \ldots, a_r]$ 组成的数组。
- 奇数长度数组的中位数是将数组按非递减顺序排序后的中间元素。例如：$\operatorname{median}([1,2,5,4,3]) = 3$，$\operatorname{median}([3,2,1]) = 2$，$\operatorname{median}([2,1,2,1,2,2,2]) = 2$。

## 说明/提示
- 在第一个测试用例中，给定的划分 $m = 1$，$b_1 = [1]$。显然，$\operatorname{median}([\operatorname{median}([1])]) = \operatorname{median}([1]) = 1$。
- 在第二个测试用例中，给定的划分 $m = 3$，且：
  - $b_1 = [1]$
  - $b_2 = [2]$
  - $b_3 = [3]$
  因此，$\operatorname{median}([\operatorname{median}([1]), \operatorname{median}([2]), \operatorname{median}([3])]) = \operatorname{median}([1, 2, 3]) = 2$。
- 在第三个测试用例中，对于 $k = 3$ 没有有效的划分。
- 在第四个测试用例中，给定的划分 $m = 5$，且：
  - $b_1 = [1, 2, 3]$
  - $b_2 = [4, 5, 6]$
  - $b_3 = [7, 8, 9]$
  - $b_4 = [10, 11, 12]$
  - $b_5 = [13, 14, 15]$
  因此，$\operatorname{median}([\operatorname{median}([1, 2, 3]), \operatorname{median}([4, 5, 6]), \operatorname{median}([7, 8, 9]), \operatorname{median}([10, 11, 12]), \operatorname{median}([13, 14, 15])]) = \operatorname{median}([2, 5, 8, 11, 14]) = 8$。

## 样例 #1
### 输入
```
4
1 1
3 2
3 3
15 8
```
### 输出
```
1
1
3
1 2 3
-1
5
1 4 7 10 13
```

### 综合分析与结论
这些题解均围绕数组划分问题展开，核心思路是将元素 $k$ 单独作为一段，再根据 $k$ 前后元素数量的奇偶性进行分类讨论，从而完成数组的划分。各题解的算法要点在于合理处理不同情况下的划分方式，以满足子数组长度为奇数且子数组中位数的中位数为 $k$ 的条件。主要难点在于对特殊情况（如 $k = 1$ 或 $k = n$）的判断以及奇偶性的处理。

### 所选题解
- **Drifty（5星）**
    - **关键亮点**：思路清晰，分类讨论全面，代码简洁易懂，对各种情况的处理逻辑明确。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int T; cin >> T;
    for (int n, k; T --; ) {
        cin >> n >> k;
        if (n == 1 && k == 1) {
            cout << 1 << '\n' << 1 << '\n';
            continue;
        }
        if (k == n || k == 1) {
            cout << -1 << '\n';
            continue;
        }
        if (n - k & 1) {
            cout << 3 << '\n';
            cout << 1 << ' ' << k << ' ' << k + 1 << '\n';
        }
        else {
            cout << 5 << '\n';
            cout << 1 << ' ' << 2 << ' ' << k << ' ' << k + 1 << ' ' << k + 2 << '\n';
        }
    }
    return 0;
}
```
核心实现思想：先处理特殊情况 $n = 1$ 且 $k = 1$ 以及 $k = 1$ 或 $k = n$，然后根据 $n - k$ 的奇偶性进行不同的划分输出。

- **chen_z（4星）**
    - **关键亮点**：思路清晰，对划分的逻辑解释详细，代码结构良好。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        if(k==1&&n==1){
            cout<<"1\n1\n";
            continue;
        }
        if(k==1||k==n){
            cout<<"-1\n";
            continue;
        }
        if((k-1)%2==0){
            cout<<"5\n";
            if(k<=2||k>=n-1){
                cout<<"-1\n";
                continue;
            }
            cout<<1<<" "<<k-1<<" "<<k<<" "<<k+1<<" "<<k+2<<'\n';
        }
        else{
            cout<<"3\n";
            cout<<1<<" "<<k<<" "<<k+1<<'\n';
        }
    }
    return 0;
}
```
核心实现思想：同样先处理特殊情况，再根据 $k - 1$ 的奇偶性进行划分，同时对不合法的划分情况进行判断。

### 最优关键思路或技巧
将元素 $k$ 单独作为一段，利用 $k$ 前后元素数量的奇偶性进行分类讨论，简化了问题的处理过程。

### 可拓展之处
同类型题目可能会改变数组的初始状态或增加其他限制条件，如数组元素不再是连续的 $1$ 到 $n$，或者对子数组的长度有更复杂的要求。解题时仍可采用分类讨论的思维方式，结合具体条件进行分析。

### 洛谷推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：考察对问题的分类讨论和边界处理。
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)：需要对元素进行合理的排序和分类处理。
3. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：涉及区间的划分和处理，与本题的数组划分思路有一定相似性。

### 个人心得
无。

---
处理用时：35.41秒