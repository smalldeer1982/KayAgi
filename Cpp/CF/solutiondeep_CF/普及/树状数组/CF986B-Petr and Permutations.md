# 题目信息

# Petr and Permutations

## 题目描述

Petr likes to come up with problems about randomly generated data. This time problem is about random permutation. He decided to generate a random permutation this way: he takes identity permutation of numbers from $ 1 $ to $ n $ and then $ 3n $ times takes a random pair of different elements and swaps them. Alex envies Petr and tries to imitate him in all kind of things. Alex has also come up with a problem about random permutation. He generates a random permutation just like Petr but swaps elements $ 7n+1 $ times instead of $ 3n $ times. Because it is more random, OK?!

You somehow get a test from one of these problems and now you want to know from which one.

## 说明/提示

Please note that the sample is not a valid test (because of limitations for $ n $ ) and is given only to illustrate input/output format. Your program still has to print correct answer to this test to get AC.

Due to randomness of input hacks in this problem are forbidden.

## 样例 #1

### 输入

```
5
2 4 5 1 3
```

### 输出

```
Petr
```

# AI分析结果

### 题目中文重写
# 彼得与排列

## 题目描述
彼得喜欢出一些关于随机生成数据的问题。这次的问题是关于随机排列的。他决定用以下方式生成一个随机排列：他取从 $1$ 到 $n$ 的恒等排列，然后 $3n$ 次随机选取两个不同的元素并交换它们。亚历克斯羡慕彼得，试图在各种事情上模仿他。亚历克斯也想出了一个关于随机排列的问题。他生成随机排列的方式和彼得一样，但他交换元素 $7n + 1$ 次，而不是 $3n$ 次。因为这样更随机，对吧？

你不知怎么得到了这些问题中的一个测试用例，现在你想知道它来自哪个问题。

## 说明/提示
请注意，样例不是一个有效的测试用例（由于 $n$ 的限制），仅用于说明输入/输出格式。你的程序仍然需要对这个样例给出正确的答案才能通过。

由于输入的随机性，本题禁止 Hack。

## 样例 #1
### 输入
```
5
2 4 5 1 3
```
### 输出
```
Petr
```

### 综合分析与结论
这些题解主要围绕判断给定排列是经过 $3n$ 次交换还是 $7n + 1$ 次交换得到的。核心在于利用交换操作对排列某些性质（如逆序数奇偶性、还原到初始排列的交换次数奇偶性）的影响，结合 $3n$ 和 $7n + 1$ 奇偶性不同来判断。
- **思路对比**：
    - 逆序数法：多数题解利用交换两元素会改变逆序数奇偶性，通过计算给定排列逆序数奇偶性与 $3n$ 或 $7n + 1$ 对比。
    - 还原法：通过贪心策略将排列还原到初始排列，根据还原交换次数奇偶性判断。
    - 乱搞法：通过定义一个量化“有序”程度的指标 $f(p)$ 进行判断。
- **算法要点对比**：
    - 逆序数计算：使用树状数组（$O(n\log n)$）、归并排序（$O(n\log n)$）或简单模拟（$O(n^2)$ 但本题不可行）。
    - 排列还原：不断交换元素使 $a_i = i$，复杂度 $O(n)$。
- **难点对比**：
    - 逆序数法：证明交换两元素逆序数奇偶性改变，以及高效计算逆序数。
    - 还原法：证明还原次数奇偶性与原交换次数奇偶性相同。
    - 乱搞法：找到合适的量化指标并确定判断阈值。

### 所选题解
- **pufanyi 的题解（5星）**
    - **关键亮点**：思路清晰，采用贪心策略将排列还原到初始排列，复杂度 $O(n)$，代码简洁易懂。
    - **核心代码**：
```cpp
for(int i = 1; i <= n; ++i)
{
    while(aa[i]!= i)
    {
        swap(aa[aa[i]], aa[i]);
        ans++;
    }
}
if((n & 1) == (ans & 1)) // 判断奇偶性相同
    puts("Petr");
else
    puts("Um_nik");
```
核心思想是不断交换元素使 $a_i = i$，统计交换次数，根据交换次数奇偶性与 $n$ 奇偶性对比判断。
- **Mr_Wu 的题解（4星）**
    - **关键亮点**：详细阐述逆序数概念和计算方法，使用树状数组计算逆序数，复杂度 $O(n\log n)$，思路严谨。
    - **核心代码**：
```cpp
for (i = 1; i <= n; i++)
{
    ans = (ans + query(n) - query(a[i] - 1)) % 2; 
    insert(a[i], 1);
}
ans %= 2;
if ((ans - 3 * n) % 2 == 0) printf("Petr"); //奇偶性判断
else printf("Um_nik");
```
核心思想是利用树状数组计算逆序数，根据逆序数奇偶性与 $3n$ 奇偶性对比判断。
- **caoshuchen 的题解（4星）**
    - **关键亮点**：提供两种思路，分别是逆序数法和排列还原法，对逆序数奇偶性改变证明详细，代码实现清晰。
    - **思路1核心代码**：
```c++
int slv(int l, int r) {
    if (l + 1 >= r)
        return 0;
    int mid = (l + r) / 2;
    int ans = (slv(l, mid) + slv(mid, r)) % 2;
    for (int i = l, j = mid; i < mid; i++) {
        while (j < r && a[j] < a[i]) j++;
        ans = (ans + j - mid) % 2;
    }
    // 合并操作
    return ans % 2;
}
```
核心思想是用归并排序计算逆序数，根据逆序数奇偶性与 $n$ 奇偶性对比判断。
    - **思路2核心代码**：
```c++
for (int i = 1; i <= n; i++) {
    if (t[i]!= i) {
        int ai = a[i];
        k++, swap(a[i], a[t[i]]), swap(t[i], t[ai]);
    }
}
if (k % 2 == n % 2)
    cout << "Petr" << endl;
else
    cout << "Um_nik" << endl;
```
核心思想是通过数组记录元素位置，将排列还原到初始排列，根据还原交换次数奇偶性与 $n$ 奇偶性对比判断。

### 最优关键思路或技巧
- **利用奇偶性**：抓住 $3n$ 和 $7n + 1$ 奇偶性不同，通过排列的逆序数奇偶性或还原到初始排列的交换次数奇偶性判断。
- **数据结构优化**：使用树状数组或归并排序计算逆序数，将复杂度从 $O(n^2)$ 优化到 $O(n\log n)$。
- **贪心策略**：采用贪心策略将排列还原到初始排列，复杂度 $O(n)$。

### 可拓展之处
同类型题可能会改变交换次数的规则或排列的初始状态，解题关键仍可围绕排列的某些不变性质（如逆序数、循环节等）的奇偶性。类似算法套路可用于判断排列是否可通过特定次数的操作得到，或计算将排列变换到目标状态的最少操作次数。

### 推荐题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：考察逆序数的计算。
- [P1309 瑞士轮](https://www.luogu.com.cn/problem/P1309)：涉及排序和数据结构的应用。
- [P1226 快速幂取余运算](https://www.luogu.com.cn/problem/P1226)：可拓展对奇偶性和模运算的理解。

### 个人心得摘录与总结
- **Mr_Wu**：提到交换序列任意两元素逆序数奇偶性改变的引理是手推瞎猜的，说明在解题中可以先通过尝试和猜想得到结论，再进行严格证明。
- **caoshuchen**：在证明交换两元素逆序数奇偶性改变时，发现最初证明有错误，后用代数方法证明，提醒在证明过程中要严谨，考虑各种情况。 

---
处理用时：42.44秒