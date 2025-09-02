# 题目信息

# Number Reduction

## 题目描述

You are given a positive integer $ x $ .

You can apply the following operation to the number: remove one occurrence of any digit in such a way that the resulting number does not contain any leading zeroes and is still a positive integer. For example, $ 10142 $ can be converted to $ 1142 $ , $ 1042 $ , $ 1012 $ or $ 1014 $ (note that $ 0142 $ is not a valid outcome); $ 10 $ can be converted to $ 1 $ (but not to $ 0 $ since it is not positive).

Your task is to find the minimum positive integer that you can obtain from $ x $ if you can apply the aforementioned operation exactly $ k $ times.

## 样例 #1

### 输入

```
5
10000
4
1337
0
987654321
6
66837494128
5
7808652
3```

### 输出

```
1
1337
321
344128
7052```

# AI分析结果

### 题目内容重写
# 数字缩减

## 题目描述

给定一个正整数 $x$。

你可以对该数字进行以下操作：移除该数字中的任意一个数字，且移除后不能有前导零，且结果仍为正整数。例如，$10142$ 可以转换为 $1142$、$1042$、$1012$ 或 $1014$（注意 $0142$ 不是有效结果）；$10$ 可以转换为 $1$（但不能转换为 $0$，因为它不是正数）。

你的任务是在恰好进行 $k$ 次上述操作后，找到可以得到的最小正整数。

## 样例 #1

### 输入

```
5
10000
4
1337
0
987654321
6
66837494128
5
7808652
3```

### 输出

```
1
1337
321
344128
7052```

### 算法分类
贪心

### 题解分析与结论
本题的核心是通过贪心策略，每次选择移除当前字符串中能使得结果最小的数字，最终得到最小正整数。难点在于如何处理前导零的问题，以及如何高效地找到每次移除的最佳位置。

### 所选题解
1. **作者：灵茶山艾府 (5星)**
   - **关键亮点**：使用单调栈优化了时间复杂度，严格 $\mathcal{O}(n)$，并且通过在前 $k+1$ 个字符中找到最小的非零字符，解决了前导零的问题。
   - **个人心得**：通过单调栈维护字典序最小的子序列，避免了重复遍历，极大提高了效率。

2. **作者：_X_Z_N_ (4星)**
   - **关键亮点**：通过优化遍历起点，将时间复杂度从 $O(nk)$ 优化到 $O(n+k)$，有效避免了重复遍历。
   - **个人心得**：通过记录上一次删除的位置，优化了遍历过程，减少了不必要的比较。

3. **作者：Alex_Wei (4星)**
   - **关键亮点**：通过预处理每个数字的下一次出现位置，快速找到最小数字的位置，优化了删除操作。
   - **个人心得**：通过预处理和贪心策略结合，实现了高效的最小化操作。

### 关键思路与技巧
- **单调栈**：用于维护字典序最小的子序列，避免重复遍历。
- **贪心策略**：每次选择移除当前字符串中能使得结果最小的数字。
- **预处理**：通过预处理每个数字的下一次出现位置，快速找到最小数字的位置。

### 可拓展之处
- 类似问题可以扩展到其他字符串操作，如删除特定字符、替换字符等。
- 可以结合动态规划，处理更复杂的字符串操作问题。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

### 核心代码片段
```cpp
// 灵茶山艾府的单调栈实现
for _, b := range s[j+1:] {
    for len(st) > 1 && k > 0 && b < st[len(st)-1] {
        st = st[:len(st)-1]
        k--
    }
    st = append(st, b)
}
st = st[:len(st)-k]
```

```cpp
// _X_Z_N_的优化遍历实现
for(int i=1;i<=k;i++) {
    int j=0;
    for(j=p;;j++) {
        if(a[j]>a[j+1] && (a[j+1]!='0' || j!=0)) {
            break;
        }
    }
    a.erase(j,1);
    p=j-1;
}
```

```cpp
// Alex_Wei的预处理实现
for (int i = 0; i < s.size(); i++) {
    a[s[i] - '0'].push_back(i);
}
while (k) {
    for (int i = 0; i <= 9; i++) {
        if (a[i].size() > idx[i] && (l > 0 || i != 0)) {
            if (a[i][idx[i]] <= l + k) {
                k = k - (a[i][idx[i]] - l);
                l = a[i][idx[i]] + 1;
                idx[i]++;
                ans += char(i + '0');
                break;
            }
        }
    }
}
```

---
处理用时：30.11秒