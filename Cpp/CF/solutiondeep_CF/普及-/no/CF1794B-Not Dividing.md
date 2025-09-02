# 题目信息

# Not Dividing

## 题目描述

You are given an array of $ n $ positive integers $ a_1, a_2, \ldots, a_n $ . In one operation, you can choose any number of the array and add $ 1 $ to it.

Make at most $ 2n $ operations so that the array satisfies the following property: $ a_{i+1} $ is not divisible by $ a_i $ , for each $ i = 1, 2, \ldots, n-1 $ .

You do not need to minimize the number of operations.

## 说明/提示

In the first test case, the array $ [4, 5, 6, 7] $ can be achieved by applying $ 2 $ operations to the first element, $ 1 $ operation to the second element, $ 3 $ operations to the third element, and $ 1 $ operation to the last element. The total number of operations performed is $ 7 $ , which is less than the allowed $ 8 $ operations in this case.

In the second test case, the array $ [3, 2, 3] $ can be achieved by applying two operations to the first element. Another possible resulting array could be $ [2, 3, 5] $ , because the total number of operations does not need to be minimum.

In the third test case, not applying any operations results in an array that satisfies the statement's property. Observe that it is not mandatory to make operations.

## 样例 #1

### 输入

```
3
4
2 4 3 6
3
1 2 3
2
4 2```

### 输出

```
4 5 6 7
3 2 3
4 2```

# AI分析结果

### 题目内容
# 不可整除

## 题目描述
给定一个包含 $n$ 个正整数的数组 $a_1, a_2, \ldots, a_n$ 。在一次操作中，你可以选择数组中的任意数字并给它加 $1$ 。

进行至多 $2n$ 次操作，使得数组满足以下性质：对于每个 $i = 1, 2, \ldots, n - 1$，$a_{i + 1}$ 不能被 $a_i$ 整除。

你无需最小化操作次数。

## 说明/提示
在第一个测试用例中，数组 $[4, 5, 6, 7]$ 可以通过对第一个元素进行 $2$ 次操作，对第二个元素进行 $1$ 次操作，对第三个元素进行 $3$ 次操作，对最后一个元素进行 $1$ 次操作得到。执行的操作总数为 $7$ ，在这种情况下小于允许的 $8$ 次操作。

在第二个测试用例中，数组 $[3, 2, 3]$ 可以通过对第一个元素进行两次操作得到。另一个可能的结果数组可以是 $[2, 3, 5]$ ，因为不需要操作次数最少。

在第三个测试用例中，不进行任何操作得到的数组就满足题目的性质。请注意，不强制要求进行操作。

## 样例 #1
### 输入
```
3
4
2 4 3 6
3
1 2 3
2
4 2
```
### 输出
```
4 5 6 7
3 2 3
4 2
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是通过遍历数组，检查相邻元素之间的整除关系，并通过给元素加1的操作来破坏这种整除关系，同时处理 $a_i = 1$ 这种特殊情况。所有题解都能正确解决问题，但在代码的简洁性、可读性等方面存在差异。

### 所选的题解
- **作者：SunnyYuan (赞：6)  星级：5星 关键亮点：思路清晰简洁，代码结构紧凑，先处理第一个元素防止其为1，然后遍历数组，简洁地处理了整除和 $a_i = 1$ 的情况**
```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    if (a[0] == 1) a[0]++;
    for (int i = 1; i < a.size(); i++) {
        if (a[i] == 1) a[i]++;
        if (a[i] % a[i - 1] == 0) {
            a[i]++;
        }
    }
    for (auto& x : a) cout << x << ' ';
    cout << '\n';
}
```
- **作者：Xy_top (赞：4)  星级：4星 关键亮点：代码简短，逻辑清晰，直接遍历数组，针对整除和 $a_i = 1$ 的情况进行处理，并且在处理 $a_i = 1$ 时考虑到了 $a_{i - 1}$ 的情况**
```cpp
int main () {
    cin >>t;
    while (t --) {
        cin >>n;
        for (int i = 1; i <= n; i ++) cin >> a[i];
        for (int i = 1; i < n; i ++) {
            if (a[i + 1] % a[i] == 0) {
                if (a[i] == 1) {
                    if (a[i - 1] == 2) a[i] += 2;
                    else ++ a[i];
                    i --;
                }
                else ++ a[i + 1];
            }
        }
        for (int i = 1; i <= n; i ++) cout << a[i] << " ";
        cout << "\n";
    }
    return 0;
}
```

### 最优关键思路或技巧
1. **核心模拟思路**：从前往后遍历数组，检查相邻元素的整除关系，通过给后一个元素加1来破坏整除关系。
2. **特殊情况处理**：当 $a_i = 1$ 时，因为任何数都能被1整除，所以要将 $a_i$ 变为2（若 $a_{i - 1} \neq 2$），若 $a_{i - 1} = 2$ 则变为3，以保证新的 $a_i$ 不会与前后元素产生整除矛盾。

### 拓展
此类题目属于数组元素关系调整的模拟题，类似套路是对数组元素间特定关系（如倍数、差值等）进行调整，通过遍历数组并根据条件进行操作来满足题目要求。

### 洛谷相似题目
1. [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)
2. [P1161 开灯](https://www.luogu.com.cn/problem/P1161)
3. [P1244 青蛙过河](https://www.luogu.com.cn/problem/P1244) 

---
处理用时：32.96秒