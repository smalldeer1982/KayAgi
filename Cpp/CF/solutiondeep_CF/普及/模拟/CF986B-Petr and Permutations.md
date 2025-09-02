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

### 题目翻译
# 彼得与排列

## 题目描述
彼得喜欢出一些关于随机生成数据的问题。这次的问题是关于随机排列的。他决定用以下方式生成一个随机排列：他先取从 $1$ 到 $n$ 的恒等排列，然后 $3n$ 次随机选取两个不同的元素并交换它们。亚历克斯羡慕彼得，试图在所有事情上模仿他。亚历克斯也想出了一个关于随机排列的问题。他生成随机排列的方式和彼得一样，但他交换元素的次数是 $7n + 1$ 次，因为这样更随机，对吧？

你不知怎么得到了其中一个问题的测试数据，现在你想知道这个数据来自哪个问题。

## 说明/提示
请注意，样例不是有效的测试数据（因为 $n$ 有范围限制），仅用于说明输入/输出格式。你的程序仍然需要正确处理这个样例才能通过。

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
这些题解主要围绕判断给定排列是经过 $3n$ 次交换还是 $7n + 1$ 次交换得到的。思路主要分为两类：一是利用逆序对的奇偶性，二是计算将排列还原为有序排列的交换次数的奇偶性。

|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|pufanyi|计算将序列还原为有序序列的交换次数，通过奇偶性判断|贪心策略交换元素，统计交换次数|快速还原序列|5星|
|Mr_Wu|计算序列逆序数，通过奇偶性判断|树状数组计算逆序数|$O(n^2)$ 算法超时，使用树状数组优化|4星|
|duyi|通过量化排列的“有序”程度判断|定义指标 $f(p) = \sum_{i = 1}^{n}[p_i = i]$，根据 $f(p)$ 值判断|衡量排列的“有序”程度|3星|
|大菜鸡fks|计算逆序对数，根据方程解的奇偶性判断|树状数组计算逆序对数|判断方程解的奇偶性|4星|
|xiaoshumiao|计算逆序对数量，通过奇偶性判断|归并排序计算逆序对|$O(n^2)$ 算法超时，使用归并排序优化|4星|
|PDAST|使用 dfs 计算交换次数，通过奇偶性判断|dfs 搜索元素的“源头”，统计交换次数|递归搜索元素的“源头”|3星|
|liuyr1234|计算将序列变为有序序列的交换次数，通过奇偶性判断|模拟交换过程，统计交换次数|判断剩余交换是否为无用交换|3星|
|Aw顿顿|计算逆序对数量，通过奇偶性判断|归并排序计算逆序对|$O(n^2)$ 算法超时，使用归并排序优化|4星|
|201012280925LSY|计算将序列变为自然数列的次数，通过奇偶性判断|模拟交换过程，统计交换次数|判断 $3N - sum$ 是否为偶数|3星|
|zhengzidu|计算序列逆序数，通过奇偶性判断|树状数组计算逆序数|证明交换元素逆序数奇偶性改变|4星|
|2021zjhs005|计算逆序对个数，通过奇偶性判断|树状数组维护逆序对|判断逆序对个数与操作次数的奇偶性|4星|
|Kyl_in_2024|计算交换次数，通过奇偶性判断|最优策略交换元素，统计交换次数|寻找元素位置优化时间复杂度|3星|
|I_will_AKIOI|计算将排列排序的步数，通过奇偶性判断|贪心算法排序，统计步数|证明排序步数奇偶性不变|3星|
|caoshuchen|思路1：计算逆序对个数，通过奇偶性判断；思路2：计算序列变换次数，通过奇偶性判断|思路1：归并排序计算逆序对；思路2：模拟交换过程，统计交换次数|思路1：证明交换元素逆序数奇偶性改变；思路2：证明变换次数奇偶性唯一确定|4星|

### 所选题解
- **pufanyi（5星）**
    - 关键亮点：思路清晰，代码简洁，时间复杂度为 $O(n)$。
    - 核心代码：
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
    - 核心实现思想：通过贪心策略，不断交换元素，将序列还原为有序序列，统计交换次数，最后根据交换次数的奇偶性判断。

- **Mr_Wu（4星）**
    - 关键亮点：使用树状数组计算逆序数，优化时间复杂度为 $O(n\log n)$。
    - 核心代码：
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
    - 核心实现思想：利用树状数组计算序列的逆序数，通过逆序数的奇偶性判断。

- **大菜鸡fks（4星）**
    - 关键亮点：通过方程解的奇偶性判断，思路独特。
    - 核心代码：
```cpp
for (int i=n;i;i--){
    sum+=query(a[i]);
    upd(a[i],1);
}
sum&=1; n&=1;
if (sum==n) puts("Petr"); else puts("Um_nik");
```
    - 核心实现思想：使用树状数组计算逆序对数，根据方程解的奇偶性判断。

### 最优关键思路或技巧
- **奇偶性判断**：利用交换操作对逆序对奇偶性的影响，以及 $3n$ 和 $7n + 1$ 的奇偶性不同，通过判断逆序对个数或还原序列的交换次数的奇偶性来解决问题。
- **数据结构优化**：使用树状数组或归并排序计算逆序对，将时间复杂度从 $O(n^2)$ 优化到 $O(n\log n)$。

### 拓展思路
同类型题可考虑其他排列变换问题，如给定一个排列，判断经过特定次数的某种操作（如旋转、交换等）能否得到另一个排列。类似算法套路可应用于需要判断操作次数奇偶性的问题。

### 推荐题目
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
- [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
- [P1309 瑞士轮](https://www.luogu.com.cn/problem/P1309)

### 个人心得摘录与总结
- **Mr_Wu**：作者提到不会证明交换序列任意两元素逆序数奇偶性必定改变，是手推瞎猜的。这提醒我们在解题时可以先通过尝试和观察找到规律，再去深入证明。
- **duyi**：作者通过尝试发现可以用 $f(p) = \sum_{i = 1}^{n}[p_i = i]$ 量化排列的“有序”程度，并且进一步探究了排列操作后 $p_i = i$ 的位置 $i$ 的数量的期望。这体现了在解题过程中可以不断深入思考，拓展问题。
- **caoshuchen**：作者在证明交换元素逆序对奇偶性改变时，先尝试了一种错误的证明方法，后使用代数方法证明。这告诉我们在证明过程中要严谨，遇到问题及时调整思路。 

---
处理用时：48.03秒