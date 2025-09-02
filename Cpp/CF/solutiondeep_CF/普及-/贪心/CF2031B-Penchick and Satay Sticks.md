# 题目信息

# Penchick and Satay Sticks

## 题目描述

Penchick and his friend Kohane are touring Indonesia, and their next stop is in Surabaya!

In the bustling food stalls of Surabaya, Kohane bought $ n $ satay sticks and arranged them in a line, with the $ i $ -th satay stick having length $ p_i $ . It is given that $ p $ is a permutation $ ^{\text{∗}} $ of length $ n $ .

Penchick wants to sort the satay sticks in increasing order of length, so that $ p_i=i $ for each $ 1\le i\le n $ . For fun, they created a rule: they can only swap neighboring satay sticks whose lengths differ by exactly $ 1 $ . Formally, they can perform the following operation any number of times (including zero):

- Select an index $ i $ ( $ 1\le i\le n-1 $ ) such that $ |p_{i+1}-p_i|=1 $ ;
- Swap $ p_i $ and $ p_{i+1} $ .

Determine whether it is possible to sort the permutation $ p $ , thus the satay sticks, by performing the above operation.

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, we can sort permutation $ p = [2, 1, 3, 4] $ by performing an operation on index $ 1 $ ( $ |p_2 - p_1| = |1 - 2| = 1 $ ), resulting in $ p = [1, 2, 3, 4] $ .

In the second test case, it can be proven that it is impossible to sort permutation $ p = [4, 2, 3, 1] $ by performing the operation. Here is an example of a sequence of operations that can be performed on the permutation:

- Select $ i = 2 $ ( $ |p_3 - p_2| = |3 - 2| = 1 $ ). This results in $ p = [4, 3, 2, 1] $ .
- Select $ i = 1 $ ( $ |p_2 - p_1| = |3 - 4| = 1 $ ). This results in $ p = [3, 4, 2, 1] $ .
- Select $ i = 3 $ ( $ |p_4 - p_3| = |1 - 2| = 1 $ ). This results in $ p = [3, 4, 1, 2] $ .

Unfortunately, permutation $ p $ remains unsorted after performing the operations.

## 样例 #1

### 输入

```
2
4
2 1 3 4
4
4 2 3 1```

### 输出

```
YES
NO```

# AI分析结果



### 题目内容中文翻译
# Penchick 与沙爹串

## 题目描述

Penchick 和好友 Kohane 在印尼旅游，下一站是泗水！

在泗水热闹的夜市中，Kohane 买了 $n$ 根沙爹串并排成一列，第 $i$ 根的长度为 $p_i$。已知 $p$ 是长度为 $n$ 的排列$^{\text{∗}}$。

Penchick 想按长度递增排序沙爹串，使得对所有 $1\le i\le n$ 有 $p_i=i$。他们制定了一个规则：只能交换相邻且长度差恰好为 1 的沙爹串。具体操作如下（可执行任意次，包括零次）：

- 选择索引 $i$（$1\le i\le n-1$），满足 $|p_{i+1}-p_i|=1$；
- 交换 $p_i$ 和 $p_{i+1}$。

判断能否通过这些操作将排列 $p$ 排序。

$^{\text{∗}}$排列指包含 $1$ 到 $n$ 各一次的数组。例如 $[2,3,1,5,4]$ 是排列，但 $[1,2,2]$（重复）和 $[1,3,4]$（$n=3$ 含 4）不是。

---

### 题解分析与结论
#### 关键思路
**核心结论**：当且仅当每个元素 $p_i$ 满足 $|p_i - i| \leq 1$ 时，可通过交换排序。若存在任意元素的位置与目标位置差超过 1，则无法排序。

**正确性证明**：  
元素只能通过与相邻差 1 的元素交换逐步移动。若元素初始位置偏离目标超过 1，则无法跨越中间无法交换的障碍。例如元素 3 初始在位置 1（目标位置 3），必须经过位置 2，但若位置 2 的元素无法与其交换（如差非 1），则无法到达目标。

#### 最优题解评分与亮点
1. **Lyw_and_Segment_Tree（★★★★★）**  
   - 直接验证每个元素是否满足 $|p_i - i| \leq 1$，时间复杂度 $O(n)$，代码简洁高效。
   - 引用官方证明，思路清晰，代码可读性强。

2. **fishing_cat（★★★★★）**  
   - 同样采用位置差验证，代码简洁，逻辑明确。
   - 提到反向思考，启发式分析操作可行性。

3. **Jerrycyx（★★★★☆）**  
   - 模拟交换相邻逆序对，最后检查有序性。
   - 时间复杂度 $O(n)$，代码极简但正确性依赖核心结论。

#### 关键代码片段
**Lyw_and_Segment_Tree 的核心判断逻辑**：
```cpp
bool flag = true;
for (ll i = 1; i <= n; i++) {
    ll x = read();
    if (abs(x - i) > 1) flag = false;
}
cout << (flag ? "YES" : "NO");
```

**Jerrycyx 的模拟交换代码**：
```cpp
for(int i = 2; i <= n; i++)
    if(a[i-1] - a[i] == 1) swap(a[i-1], a[i]);
puts(is_sorted(a+1, a+n+1) ? "YES" : "NO");
```

#### 拓展与心得
- **同类问题**：涉及元素移动受限的排列问题，如需要特定交换条件，可考虑元素可达性分析。
- **调试经验**：注意数组边界（如 Ivan422 因数组开小导致错误），验证猜想时需构造极端测试用例。
- **举一反三**：若交换条件变化（如差为 2 可交换），需重新分析元素移动范围。

---

### 推荐相似题目
1. [P1963 变换序列](https://www.luogu.com.cn/problem/P1963)  
2. [P2894 [USACO08FEB]Hotel G](https://www.luogu.com.cn/problem/P2894)  
3. [P2115 [USACO14MAR]Sabotage G](https://www.luogu.com.cn/problem/P2115)

---
处理用时：91.56秒