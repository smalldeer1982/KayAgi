# 题目信息

# Alice's Adventures in Permuting

## 题目描述

Alice mixed up the words transmutation and permutation! She has an array $ a $ specified via three integers $ n $ , $ b $ , $ c $ : the array $ a $ has length $ n $ and is given via $ a_i = b\cdot (i - 1) + c $ for $ 1\le i\le n $ . For example, if $ n=3 $ , $ b=2 $ , and $ c=1 $ , then $ a=[2 \cdot 0 + 1, 2 \cdot 1 + 1, 2 \cdot 2 + 1] = [1, 3, 5] $ .

Now, Alice really enjoys permutations of $ [0, \ldots, n-1] $ $ ^{\text{∗}} $ and would like to transform $ a $ into a permutation. In one operation, Alice replaces the maximum element of $ a $ with the $ \operatorname{MEX} $ $ ^{\text{†}} $ of $ a $ . If there are multiple maximum elements in $ a $ , Alice chooses the leftmost one to replace.

Can you help Alice figure out how many operations she has to do for $ a $ to become a permutation for the first time? If it is impossible, you should report it.

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 0 $ to $ n-1 $ in arbitrary order. Please note, this is slightly different from the usual definition of a permutation. For example, $ [1,2,0,4,3] $ is a permutation, but $ [0,1,1] $ is not a permutation ( $ 1 $ appears twice in the array), and $ [0,2,3] $ is also not a permutation ( $ n=3 $ but there is $ 3 $ in the array).

 $ ^{\text{†}} $ The $ \operatorname{MEX} $ of an array is the smallest non-negative integer that does not belong to the array. For example, the $ \operatorname{MEX} $ of $ [0, 3, 1, 3] $ is $ 2 $ and the $ \operatorname{MEX} $ of $ [5] $ is $ 0 $ .

## 说明/提示

In the first test case, the array is already $ [0, 1, \ldots, 9] $ , so no operations are required.

In the third test case, the starting array is $ [1, 3, 5, \ldots, 199] $ . After the first operation, the $ 199 $ gets transformed into a $ 0 $ . In the second operation, the $ 197 $ gets transformed into a $ 2 $ . If we continue this, it will take exactly $ 50 $ operations to get the array $ [0, 1, 2, 3, \ldots, 99] $ .

In the fourth test case, two operations are needed: $ [1,1,1] \to [0,1,1] \to [0,2,1] $ .

In the fifth test case, the process is $ [0,0,0] \to [1,0,0] \to [2,0,0] \to [1,0,0] \to [2,0,0] $ . This process repeats forever, so the array is never a permutation and the answer is $ -1 $ .

## 样例 #1

### 输入

```
7
10 1 0
1 2 3
100 2 1
3 0 1
3 0 0
1000000000000000000 0 0
1000000000000000000 1000000000000000000 1000000000000000000```

### 输出

```
0
1
50
2
-1
-1
1000000000000000000```

# AI分析结果

### 题目内容重写

#### Alice的排列冒险

#### 题目描述

Alice混淆了“transmutation”和“permutation”这两个词！她有一个数组 $a$，由三个整数 $n$、$b$、$c$ 定义：数组 $a$ 的长度为 $n$，且 $a_i = b \cdot (i - 1) + c$，其中 $1 \le i \le n$。例如，如果 $n=3$，$b=2$，$c=1$，那么 $a = [2 \cdot 0 + 1, 2 \cdot 1 + 1, 2 \cdot 2 + 1] = [1, 3, 5]$。

现在，Alice非常喜欢 $[0, \ldots, n-1]$ 的排列，并希望将 $a$ 转换为一个排列。在一次操作中，Alice将数组 $a$ 中的最大元素替换为 $a$ 的 $\operatorname{MEX}$。如果 $a$ 中有多个最大元素，Alice选择最左边的那个进行替换。

你能帮助Alice计算出她需要进行多少次操作才能使 $a$ 第一次成为一个排列吗？如果不可能，请报告。

$^{\text{∗}}$ 长度为 $n$ 的排列是一个由 $0$ 到 $n-1$ 的 $n$ 个不同整数组成的数组，顺序任意。请注意，这与通常的排列定义略有不同。例如，$[1,2,0,4,3]$ 是一个排列，但 $[0,1,1]$ 不是排列（$1$ 出现了两次），$[0,2,3]$ 也不是排列（$n=3$ 但数组中出现了 $3$）。

$^{\text{†}}$ 数组的 $\operatorname{MEX}$ 是不属于该数组的最小非负整数。例如，$[0, 3, 1, 3]$ 的 $\operatorname{MEX}$ 是 $2$，$[5]$ 的 $\operatorname{MEX}$ 是 $0$。

#### 说明/提示

在第一个测试用例中，数组已经是 $[0, 1, \ldots, 9]$，因此不需要操作。

在第三个测试用例中，起始数组是 $[1, 3, 5, \ldots, 199]$。第一次操作后，$199$ 被替换为 $0$。第二次操作后，$197$ 被替换为 $2$。如果继续这样操作，最终需要恰好 $50$ 次操作才能将数组变为 $[0, 1, 2, 3, \ldots, 99]$。

在第四个测试用例中，需要两次操作：$[1,1,1] \to [0,1,1] \to [0,2,1]$。

在第五个测试用例中，过程是 $[0,0,0] \to [1,0,0] \to [2,0,0] \to [1,0,0] \to [2,0,0]$。这个过程会无限重复，因此数组永远不会成为一个排列，答案为 $-1$。

#### 样例 #1

##### 输入

```
7
10 1 0
1 2 3
100 2 1
3 0 1
3 0 0
1000000000000000000 0 0
1000000000000000000 1000000000000000000 1000000000000000000
```

##### 输出

```
0
1
50
2
-1
-1
1000000000000000000
```

### 题解分析与结论

#### 综合分析

本题的核心在于通过分类讨论来确定将数组 $a$ 转换为排列所需的最少操作次数。题解主要围绕以下几种情况进行讨论：

1. **$b > 0$**：此时数组 $a$ 是一个等差数列，可以通过数学公式计算出需要操作的次数。
2. **$b = 0$**：此时数组 $a$ 中的所有元素都等于 $c$，需要根据 $c$ 与 $n$ 的关系来判断是否有解。
3. **$c \ge n$**：此时数组 $a$ 中的所有元素都大于等于 $n$，需要进行 $n$ 次操作。

各题解的主要思路相似，但在具体实现和细节处理上有所不同。部分题解在分类讨论时更为细致，能够更好地处理边界情况。

#### 所选高分题解

1. **作者：chenxi2009（4星）**
   - **关键亮点**：分类讨论清晰，代码简洁，处理了 $b=0$ 时的多种情况，特别是 $c$ 与 $n$ 的关系。
   - **代码片段**：
     ```cpp
     if(b){
         printf("%lld\n",n - max(0ll,(n - c + b - 1) / b)); //向上取整 
     }
     else{
         printf("%lld\n",c >= n - 2 ? n - bool(c <= n - 1) : -1);//归纳了一下 b=0 的情况 
     }
     ```

2. **作者：Lee_OIer（4星）**
   - **关键亮点**：分类讨论详细，特别是对 $b=0$ 时的无解情况进行了清晰的说明，代码可读性高。
   - **代码片段**：
     ```cpp
     if (c >= n) cout << n << '\n';
     else {
         if (b) cout << n - (n - c - 1) / b - 1 << '\n';
         else {
             if (n - c >= 3) cout << -1 << '\n';
             else cout << n - 1 << '\n';
         }
     }
     ```

3. **作者：wuyouawa（4星）**
   - **关键亮点**：分类讨论全面，特别是对 $b=0$ 时的不同情况进行了详细分析，代码实现简洁。
   - **代码片段**：
     ```cpp
     if(c>=n)  cout<<n;
     else {
         if(b==0) {
             if(n-3>=c)  cout<<-1;
             else  cout<<n-1;
         }
         else {
             cout<<n-(n-c-1)/b-1;
         }
     }
     ```

#### 最优关键思路

1. **分类讨论**：根据 $b$ 和 $c$ 的不同取值，将问题分为几种情况分别处理，特别是 $b=0$ 时的无解情况。
2. **数学公式**：对于 $b>0$ 的情况，通过数学公式计算出需要操作的次数，避免了复杂的循环和判断。
3. **边界处理**：在处理 $b=0$ 时，特别注意 $c$ 与 $n$ 的关系，确保无解情况的正确判断。

#### 可拓展之处

- **类似问题**：类似的分类讨论和数学公式应用可以用于解决其他涉及等差数列或固定值数组的问题。
- **算法优化**：通过数学公式直接计算结果，避免了不必要的循环和操作，提高了算法的效率。

#### 推荐题目

1. **洛谷 P1008 三连击**：考察分类讨论和数学公式应用。
2. **洛谷 P1012 拼数**：涉及数组元素的排列和数学计算。
3. **洛谷 P1028 数的计算**：考察数学公式和递归思维。

#### 个人心得摘录

- **调试经历**：在处理 $b=0$ 时，最初忽略了 $c$ 与 $n$ 的关系，导致部分测试用例无法通过。通过仔细分析样例，最终找到了正确的处理方法。
- **踩坑教训**：在计算 $b>0$ 时的操作次数时，最初没有考虑到向上取整的问题，导致结果不准确。通过引入 `max` 函数解决了这一问题。
- **顿悟感想**：通过分类讨论和数学公式的结合，能够高效地解决看似复杂的问题，体现了数学在算法中的重要性。

---
处理用时：63.72秒