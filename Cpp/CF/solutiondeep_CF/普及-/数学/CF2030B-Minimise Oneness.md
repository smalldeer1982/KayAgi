# 题目信息

# Minimise Oneness

## 题目描述

For an arbitrary binary string $ t $ $ ^{\text{∗}} $ , let $ f(t) $ be the number of non-empty subsequences $ ^{\text{†}} $ of $ t $ that contain only $ \mathtt{0} $ , and let $ g(t) $ be the number of non-empty subsequences of $ t $ that contain at least one $ \mathtt{1} $ .

Note that for $ f(t) $ and for $ g(t) $ , each subsequence is counted as many times as it appears in $ t $ . E.g., $ f(\mathtt{000}) = 7, g(\mathtt{100}) = 4 $ .

We define the oneness of the binary string $ t $ to be $ |f(t)-g(t)| $ , where for an arbitrary integer $ z $ , $ |z| $ represents the absolute value of $ z $ .

You are given a positive integer $ n $ . Find a binary string $ s $ of length $ n $ such that its oneness is as small as possible. If there are multiple strings, you can print any of them.

 $ ^{\text{∗}} $ A binary string is a string that only consists of characters $ \texttt{0} $ and $ \texttt{1} $ .

 $ ^{\text{†}} $ A sequence $ a $ is a subsequence of a sequence $ b $ if $ a $ can be obtained from $ b $ by the deletion of several (possibly, zero or all) elements. For example, subsequences of $ \mathtt{1011101} $ are $ \mathtt{0} $ , $ \mathtt{1} $ , $ \mathtt{11111} $ , $ \mathtt{0111} $ , but not $ \mathtt{000} $ nor $ \mathtt{11100} $ .

## 说明/提示

In the first test case, for the example output, $ f(t)=1 $ because there is one subsequence that contains only $ \mathtt{0} $ ( $ \mathtt{0} $ ), and $ g(t)=0 $ because there are no subsequences that contain at least one $ 1 $ . The oneness is $ |1-0|=1 $ . The output $ \mathtt{1} $ is correct as well because its oneness is $ |0-1|=1 $ .

For the example output of the second test case, $ f(t)=1 $ because there is one non-empty subsequence that contains only $ \mathtt{0} $ , and $ g(t)=2 $ because there are two non-empty subsequences that contain at least one $ \mathtt{1} $ ( $ \mathtt{01} $ and $ \mathtt{1} $ ). The oneness is thus $ |1-2|=1 $ . It can be shown that $ 1 $ is the minimum possible value of its oneness over all possible binary strings of size $ 2 $ .

## 样例 #1

### 输入

```
3
1
2
3```

### 输出

```
0
01
010```

# AI分析结果

【题目内容中文重写】
# 最小化单一性

## 题目描述

对于任意一个二进制字符串 $ t $ $ ^{\text{∗}} $ ，定义 $ f(t) $ 为 $ t $ 中仅包含 $ \mathtt{0} $ 的非空子序列 $ ^{\text{†}} $ 的数量，定义 $ g(t) $ 为 $ t $ 中至少包含一个 $ \mathtt{1} $ 的非空子序列的数量。

注意，对于 $ f(t) $ 和 $ g(t) $ ，每个子序列在 $ t $ 中出现多少次就计算多少次。例如，$ f(\mathtt{000}) = 7, g(\mathtt{100}) = 4 $ 。

我们定义二进制字符串 $ t $ 的单一性为 $ |f(t)-g(t)| $ ，其中对于任意整数 $ z $ ，$ |z| $ 表示 $ z $ 的绝对值。

给定一个正整数 $ n $ ，找到一个长度为 $ n $ 的二进制字符串 $ s $ ，使得其单一性尽可能小。如果有多个字符串，可以输出其中任意一个。

 $ ^{\text{∗}} $ 二进制字符串是指仅由字符 $ \texttt{0} $ 和 $ \texttt{1} $ 组成的字符串。

 $ ^{\text{†}} $ 序列 $ a $ 是序列 $ b $ 的子序列，如果 $ a $ 可以通过删除 $ b $ 中的若干个（可能为零或全部）元素得到。例如，$ \mathtt{1011101} $ 的子序列包括 $ \mathtt{0} $ ，$ \mathtt{1} $ ，$ \mathtt{11111} $ ，$ \mathtt{0111} $ ，但不包括 $ \mathtt{000} $ 和 $ \mathtt{11100} $ 。

## 说明/提示

在第一个测试用例中，对于示例输出，$ f(t)=1 $ 因为只有一个仅包含 $ \mathtt{0} $ 的子序列（ $ \mathtt{0} $ ），而 $ g(t)=0 $ 因为没有包含至少一个 $ 1 $ 的子序列。单一性为 $ |1-0|=1 $ 。输出 $ \mathtt{1} $ 也是正确的，因为其单一性为 $ |0-1|=1 $ 。

对于第二个测试用例的示例输出，$ f(t)=1 $ 因为只有一个仅包含 $ \mathtt{0} $ 的非空子序列，而 $ g(t)=2 $ 因为有两个包含至少一个 $ \mathtt{1} $ 的非空子序列（ $ \mathtt{01} $ 和 $ \mathtt{1} $ ）。因此，单一性为 $ |1-2|=1 $ 。可以证明，对于所有长度为 $ 2 $ 的二进制字符串，$ 1 $ 是其单一性的最小值。

## 样例 #1

### 输入

```
3
1
2
3```

### 输出

```
0
01
010```

【题解分析与结论】

这些题解的核心思路都是通过构造一个包含 $1$ 个 $1$ 和 $n-1$ 个 $0$ 的字符串，使得 $f(s)$ 和 $g(s)$ 的差值最小。具体来说，$f(s)$ 表示仅包含 $0$ 的子序列数量，$g(s)$ 表示至少包含一个 $1$ 的子序列数量。通过数学推导，可以得出当字符串中 $0$ 的数量为 $n-1$ 时，$|f(s)-g(s)|$ 的值为 $1$，这是最小的可能值。

【评分较高的题解】

1. **作者：末然Ender (赞：3)**
   - **星级：4**
   - **关键亮点**：通过数学推导得出 $|f(s)-g(s)|$ 的表达式，并明确指出了当 $x+1=n$ 时，差值最小。代码简洁明了，直接输出 $1$ 和 $n-1$ 个 $0$。
   - **代码核心**：
     ```cpp
     putchar('1');
     for(int i=1;i<n;i++)putchar('0');
     ```

2. **作者：zsfzhjf (赞：1)**
   - **星级：4**
   - **关键亮点**：通过观察发现 $f \le g$ 的情况，并提出了构造一个 $1$ 和 $n-1$ 个 $0$ 的字符串的解决方案。代码实现简单，直接输出 $n-1$ 个 $0$ 和 $1$。
   - **代码核心**：
     ```cpp
     for(int i=1;i<n;i++) printf("0");
     printf("1");
     ```

3. **作者：wuyouawa (赞：0)**
   - **星级：4**
   - **关键亮点**：详细解释了为什么 $f(s)$ 和 $g(s)$ 的差值最小为 $1$，并给出了构造字符串的直观解释。代码实现简洁，直接输出 $1$ 和 $n-1$ 个 $0$。
   - **代码核心**：
     ```cpp
     cout << 1;
     for (int i = 1; i < n; i++) {
         cout << 0;
     }
     ```

【最优关键思路或技巧】

通过数学推导，得出 $|f(s)-g(s)|$ 的表达式 $|2^{x+1}-2^n-1|$，并发现当 $x+1=n$ 时，差值最小为 $1$。因此，构造一个包含 $1$ 个 $1$ 和 $n-1$ 个 $0$ 的字符串是最优解。

【可拓展之处】

类似的问题可以通过数学推导和构造法来解决，尤其是在涉及子序列计数和差值最小化的问题中。可以通过类似的思路来解决其他涉及子序列计数的题目。

【推荐题目】
1. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
2. [P1351 联合权值](https://www.luogu.com.cn/problem/P1351)
3. [P1967 货车运输](https://www.luogu.com.cn/problem/P1967)

---
处理用时：46.82秒