# 题目信息

# Turtle and a MEX Problem (Easy Version)

## 题目描述

The two versions are different problems. In this version of the problem, you can choose the same integer twice or more. You can make hacks only if both versions are solved.

One day, Turtle was playing with $ n $ sequences. Let the length of the $ i $ -th sequence be $ l_i $ . Then the $ i $ -th sequence was $ a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i} $ .

Piggy gave Turtle a problem to solve when Turtle was playing. The statement of the problem was:

- There was a non-negative integer $ x $ at first. Turtle would perform an arbitrary number (possibly zero) of operations on the integer.
- In each operation, Turtle could choose an integer $ i $ such that $ 1 \le i \le n $ , and set $ x $ to $ \text{mex}^{\dagger}(x, a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}) $ .
- Turtle was asked to find the answer, which was the maximum value of $ x $ after performing an arbitrary number of operations.

Turtle solved the above problem without difficulty. He defined $ f(k) $ as the answer to the above problem when the initial value of $ x $ was $ k $ .

Then Piggy gave Turtle a non-negative integer $ m $ and asked Turtle to find the value of $ \sum\limits_{i = 0}^m f(i) $ (i.e., the value of $ f(0) + f(1) + \ldots + f(m) $ ). Unfortunately, he couldn't solve this problem. Please help him!

 $ ^{\dagger}\text{mex}(c_1, c_2, \ldots, c_k) $ is defined as the smallest non-negative integer $ x $ which does not occur in the sequence $ c $ . For example, $ \text{mex}(2, 2, 0, 3) $ is $ 1 $ , $ \text{mex}(1, 2) $ is $ 0 $ .

## 说明/提示

In the first test case, when $ x $ is initially $ 2 $ , Turtle can choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}) = \text{mex}(2, 7, 0, 1, 5) = 3 $ . It can be proved that Turtle can't make the value of $ x $ greater than $ 3 $ , so $ f(2) = 3 $ .

It can be seen that $ f(0) = 3 $ , $ f(1) = 3 $ , $ f(2) = 3 $ , $ f(3) = 3 $ , and $ f(4) = 4 $ . So $ f(0) + f(1) + f(2) + f(3) + f(4) = 3 + 3 + 3 + 3 + 4 = 16 $ .

In the second test case, when $ x $ is initially $ 1 $ , Turtle can choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(1, 1, 3, 0, 3, 3) = 2 $ , and choose $ i = 3 $ and set $ x $ to $ \text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}, a_{3, 5}) = \text{mex}(2, 1, 3, 0, 3, 3) = 4 $ . It can be proved that Turtle can't make the value of $ x $ greater than $ 4 $ , so $ f(1) = 4 $ .

It can be seen that $ f(0) = 4 $ , $ f(1) = 4 $ , $ f(2) = 4 $ , $ f(3) = 4 $ , and $ f(4) = 4 $ . So $ f(0) + f(1) + f(2) + f(3) + f(4) = 4 + 4 + 4 + 4 + 4 = 20 $ .

In the fourth test case, it can be seen that $ f(0) = 3 $ and $ f(1) = 3 $ . So $ f(0) + f(1) = 3 + 3 = 6 $ .

## 样例 #1

### 输入

```
6
3 4
2 0 2
3 2 3 3
4 7 0 1 5
3 4
5 0 2 0 4 11
1 1
5 1 3 0 3 3
2 50
2 1 2
2 1 2
1 1
7 1 2 4 1 4 9 5
4 114514
2 2 2
5 7 3 6 0 3
3 0 1 1
5 0 9 2 1 5
5 1919810
1 2
2 324003 0
3 1416324 2 1460728
4 1312631 2 0 1415195
5 1223554 192248 2 1492515 725556```

### 输出

```
16
20
1281
6
6556785365
1842836177961```

# AI分析结果

### 题目内容重写

#### 题目描述

两个版本的问题不同。在这个版本中，你可以多次选择同一个整数。只有当你解决了两个版本的问题时，才能进行hack。

有一天，Turtle在玩$n$个序列。设第$i$个序列的长度为$l_i$，则第$i$个序列为$a_{i,1}, a_{i,2}, \ldots, a_{i,l_i}$。

当Turtle在玩的时候，Piggy给了他一个问题来解决。问题的描述如下：

- 最初有一个非负整数$x$。Turtle可以对$x$进行任意次（可能为零次）操作。
- 在每次操作中，Turtle可以选择一个整数$i$，其中$1 \le i \le n$，并将$x$设置为$\text{mex}^{\dagger}(x, a_{i,1}, a_{i,2}, \ldots, a_{i,l_i})$。
- Turtle被要求找到答案，即在执行任意次操作后$x$的最大值。

Turtle轻松地解决了上述问题。他定义了$f(k)$为当$x$的初始值为$k$时上述问题的答案。

然后Piggy给了Turtle一个非负整数$m$，并要求Turtle找到$\sum\limits_{i = 0}^m f(i)$的值（即$f(0) + f(1) + \ldots + f(m)$的值）。不幸的是，他无法解决这个问题。请帮助他！

$^{\dagger}\text{mex}(c_1, c_2, \ldots, c_k)$被定义为序列$c$中未出现的最小非负整数$x$。例如，$\text{mex}(2, 2, 0, 3)$是$1$，$\text{mex}(1, 2)$是$0$。

#### 说明/提示

在第一个测试用例中，当$x$最初为$2$时，Turtle可以选择$i = 3$并将$x$设置为$\text{mex}(x, a_{3,1}, a_{3,2}, a_{3,3}, a_{3,4}) = \text{mex}(2, 7, 0, 1, 5) = 3$。可以证明，Turtle无法使$x$的值大于$3$，因此$f(2) = 3$。

可以看到，$f(0) = 3$，$f(1) = 3$，$f(2) = 3$，$f(3) = 3$，$f(4) = 4$。因此，$f(0) + f(1) + f(2) + f(3) + f(4) = 3 + 3 + 3 + 3 + 4 = 16$。

在第二个测试用例中，当$x$最初为$1$时，Turtle可以选择$i = 3$并将$x$设置为$\text{mex}(x, a_{3,1}, a_{3,2}, a_{3,3}, a_{3,4}, a_{3,5}) = \text{mex}(1, 1, 3, 0, 3, 3) = 2$，然后再次选择$i = 3$并将$x$设置为$\text{mex}(x, a_{3,1}, a_{3,2}, a_{3,3}, a_{3,4}, a_{3,5}) = \text{mex}(2, 1, 3, 0, 3, 3) = 4$。可以证明，Turtle无法使$x$的值大于$4$，因此$f(1) = 4$。

可以看到，$f(0) = 4$，$f(1) = 4$，$f(2) = 4$，$f(3) = 4$，$f(4) = 4$。因此，$f(0) + f(1) + f(2) + f(3) + f(4) = 4 + 4 + 4 + 4 + 4 = 20$。

在第四个测试用例中，可以看到$f(0) = 3$，$f(1) = 3$。因此，$f(0) + f(1) = 3 + 3 = 6$。

### 题解分析与结论

#### 题解1：Exp10re
- **星级**：4
- **关键亮点**：通过分析每个序列的次小未出现非负整数$v_i$，得出$f(x)$的下界，并利用等差数列求和公式计算$\sum_{i=0}^m f(i)$。
- **核心思想**：对于每个序列，计算其$\text{mex}$和次小$\text{mex}$，取所有序列中最大的次小$\text{mex}$作为$f(x)$的下界。对于小于等于该下界的$x$，$f(x)$等于该下界；对于大于该下界的$x$，$f(x)$等于$x$本身。
- **代码实现**：使用`set`来计算$\text{mex}$，时间复杂度为$O(\sum l_i)$。

#### 题解2：Defy_HeavenS
- **星级**：4
- **关键亮点**：通过固定一个序列并多次操作，得出$f(x)$的最大值，并利用等差数列求和公式计算$\sum_{i=0}^m f(i)$。
- **核心思想**：选择一个序列，通过多次操作使得$x$达到该序列的次小$\text{mex}$。取所有序列中最大的次小$\text{mex}$作为$f(x)$的最大值。对于小于等于该最大值的$x$，$f(x)$等于该最大值；对于大于该最大值的$x$，$f(x)$等于$x$本身。
- **代码实现**：使用`set`来计算$\text{mex}$，时间复杂度为$O(\sum l_i)$。

#### 题解3：_O_v_O_
- **星级**：3
- **关键亮点**：通过$\text{popcount}$操作得出$f(x)$的最大值，并利用等差数列求和公式计算$\sum_{i=0}^m f(i)$。
- **核心思想**：通过$\text{popcount}$操作得出每个序列的次小$\text{mex}$，取所有序列中最大的次小$\text{mex}$作为$f(x)$的最大值。对于小于等于该最大值的$x$，$f(x)$等于该最大值；对于大于该最大值的$x$，$f(x)$等于$x$本身。
- **代码实现**：时间复杂度为$O(\sum l_i)$，但$\text{popcount}$操作的实际应用较为复杂。

### 最优关键思路或技巧

1. **次小$\text{mex}$的计算**：通过计算每个序列的$\text{mex}$和次小$\text{mex}$，确定$f(x)$的下界或最大值。
2. **等差数列求和**：对于小于等于某个值的$x$，$f(x)$等于该值；对于大于该值的$x$，$f(x)$等于$x$本身，利用等差数列求和公式快速计算$\sum_{i=0}^m f(i)$。
3. **$\text{mex}$的高效计算**：使用`set`来高效计算$\text{mex}$，确保时间复杂度为$O(\sum l_i)$。

### 可拓展之处

- **类似问题**：可以扩展到多个序列的$\text{mex}$操作问题，或者扩展到更复杂的操作序列。
- **优化思路**：可以考虑使用更高效的数据结构（如线段树）来计算$\text{mex}$，以进一步优化时间复杂度。

### 推荐题目

1. [CF2003D2](https://www.luogu.com.cn/problem/CF2003D2) - 类似$\text{mex}$操作的问题。
2. [P3919](https://www.luogu.com.cn/problem/P3919) - 线段树与$\text{mex}$的结合问题。
3. [P4556](https://www.luogu.com.cn/problem/P4556) - 动态规划与$\text{mex}$的结合问题。

### 个人心得摘录

- **Exp10re**：通过分析次小$\text{mex}$，得出了$f(x)$的下界，并利用等差数列求和公式快速计算$\sum_{i=0}^m f(i)$。
- **Defy_HeavenS**：通过固定一个序列并多次操作，得出了$f(x)$的最大值，并利用等差数列求和公式快速计算$\sum_{i=0}^m f(i)$。

### 核心代码片段

```cpp
// 题解2的核心代码片段
int n, m, ans;
vector<LL> a[N];
void solve() {
    cin >> n >> m;
    for (LL i = 1, len; i <= n; i++) {
        cin >> len;
        for (LL j = 1, val; j <= len; j++) {
            cin >> val;
            a[i].pb(val);
        }
    }
    ans = -1;
    for (LL i = 1; i <= n; i++) {
        int n = a[i].size();
        set<LL> s; s.clear();    // set求mex
        vector<int> cnt(n + 5, 0);
        for (int i = 0; i <= n + 2; i++) s.insert(i);
        for (auto val : a[i]) {
            if (val > n + 2) val = n + 2;
            if (!cnt[val]) {
                s.erase(s.find(val));
            }
            cnt[val]++;
        }
        int val = *s.begin();
        if (!cnt[val]) {
            s.erase(s.find(val));    // 加入mex，求第二个mex
        }
        cnt[val]++;
        ans = max(ans, *s.begin());    // 更新答案
    }
    LL len = min(ans + 1, m + 1);    // i <= ma的数量
    LL sec = max((m + ans + 1) * (m - ans) / 2, 0ll);    // i > ma
    cout << ans * len + sec << "\n";
    for (int i = 1; i <= n; i++) a[i].clear();
}
```

---
处理用时：67.57秒