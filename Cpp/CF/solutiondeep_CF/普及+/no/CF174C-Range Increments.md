# 题目信息

# Range Increments

## 题目描述

Polycarpus is an amateur programmer. Now he is analyzing a friend's program. He has already found there the function rangeIncrement(l, r), that adds 1 to each element of some array $ a $ for all indexes in the segment $ [l,r] $ . In other words, this function does the following:

`<br></br>function rangeIncrement(l, r)<br></br>    for i := l .. r do<br></br>        a[i] = a[i] + 1<br></br>`Polycarpus knows the state of the array $ a $ after a series of function calls. He wants to determine the minimum number of function calls that lead to such state. In addition, he wants to find what function calls are needed in this case. It is guaranteed that the required number of calls does not exceed $ 10^{5} $ .

Before calls of function rangeIncrement(l, r) all array elements equal zero.

## 说明/提示

The first sample requires a call for the entire array, and four additional calls:

- one for the segment \[2,2\] (i.e. the second element of the array),
- three for the segment \[5,5\] (i.e. the fifth element of the array).

## 样例 #1

### 输入

```
6
1 2 1 1 4 1
```

### 输出

```
5
2 2
5 5
5 5
5 5
1 6
```

## 样例 #2

### 输入

```
5
1 0 1 0 1
```

### 输出

```
3
1 1
3 3
5 5
```

# AI分析结果

### 题目内容
# 区间增量

## 题目描述
Polycarpus是一位业余程序员。现在他正在分析一个朋友的程序。他已经在程序中发现了函数rangeIncrement(l, r)，该函数会对数组 $ a $ 中索引在区间 $ [l,r] $ 内的每个元素加1。换句话说，这个函数执行以下操作：
`<br></br>function rangeIncrement(l, r)<br></br>    for i := l.. r do<br></br>        a[i] = a[i] + 1<br></br>`
Polycarpus知道经过一系列函数调用后数组 $ a $ 的状态。他想确定导致这种状态的最少函数调用次数。此外，他还想找出在这种情况下需要进行哪些函数调用。保证所需的调用次数不超过 $ 10^{5} $ 。
在调用函数rangeIncrement(l, r)之前，数组的所有元素都为零。

## 说明/提示
第一个样例需要对整个数组进行一次调用，以及另外四次调用：
- 一次针对区间 \[2,2\]（即数组的第二个元素），
- 三次针对区间 \[5,5\]（即数组的第五个元素）。

## 样例 #1
### 输入
```
6
1 2 1 1 4 1
```
### 输出
```
5
2 2
5 5
5 5
5 5
1 6
```

## 样例 #2
### 输入
```
5
1 0 1 0 1
```
### 输出
```
3
1 1
3 3
5 5
```

### 算法分类
贪心

### 题解综合分析与结论
两位作者的思路本质相同，都是将原问题转化为从给定数组通过区间减一操作使其变为全零数组，从而寻找最少操作次数及具体操作区间。
 - **__stick的题解**：提出使用单调栈实现贪心策略，通过扫描数组，依据当前元素与上一个元素大小关系决定入栈或出栈操作，将栈顶元素与当前元素组成区间进行减一操作。此方法在实现上利用数据结构辅助，逻辑较为清晰。
 - **AstaSunch_的题解**：直接给出贪心策略，即若 $a_i>a_{i-1},\text{sum}\gets \text{sum}+(a_i - a_{i-1})$，通过模拟操作过程来实现。相比之下，思路较为直接，但在实现细节上不如使用单调栈清晰。

### 所选的题解
 - **__stick的题解**：★★★★ 关键亮点在于利用单调栈实现贪心策略，使得区间减一操作的实现过程逻辑清晰。
 - **AstaSunch_的题解**：★★★ 关键亮点是直接给出简洁的贪心策略公式，但整体实现思路不如使用单调栈清晰。

### 重点代码（__stick题解核心代码，以C++ 为例）
```cpp
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    stack<int> stk;
    vector<pair<int, int>> ans;
    for (int i = 1; i <= n; i++) {
        if (a[i] > a[i - 1]) {
            for (int j = 0; j < a[i] - a[i - 1]; j++) stk.push(i);
        } else {
            while (!stk.empty() && a[stk.top()] > a[i]) {
                ans.push_back({stk.top(), i});
                stk.pop();
            }
        }
    }
    while (!stk.empty()) {
        ans.push_back({stk.top(), n});
        stk.pop();
    }
    cout << ans.size() << endl;
    for (auto p : ans) cout << p.first << " " << p.second << endl;
    return 0;
}
```
核心实现思想：遍历数组，当当前元素大于前一个元素时，将当前元素入栈，差值有多少就入栈多少次；当当前元素小于前一个元素时，将栈顶元素与当前元素组成区间并出栈，直到栈顶元素小于等于当前元素。最后处理完数组后，若栈中还有元素，将栈顶元素与数组末尾组成区间。

### 最优关键思路或技巧
利用单调栈实现贪心策略，通过栈来记录需要操作的区间端点，使得在遍历数组过程中能够高效地确定每次区间减一操作的范围，简化了操作次数及操作区间的确定过程。

### 可拓展之处
此类题目属于贪心策略在区间操作上的应用，类似题目常围绕如何通过最少的区间操作次数达到目标数组状态。常见套路是分析数组元素间的关系，确定贪心策略，可能会结合不同的数据结构来优化实现。

### 洛谷相似题目推荐
 - [P5019 铺设道路](https://www.luogu.com.cn/problem/P5019)
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)

---
处理用时：48.04秒