# 题目信息

# [ABC315C] Flavors

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc315/tasks/abc315_c

$ N $ カップのアイスクリームがあります。  
 $ i $ カップ目の味は $ F_i $ 、美味しさは $ S_i $ ( $ S_i $ は偶数 ) です。

あなたは、 $ N $ 個のカップの中から $ 2 $ つを選んで食べることにしました。  
 このときの満足度は次のように定義されます。

- 食べたアイスクリームの美味しさを $ s,t $ ( 但し、 $ s\ \ge\ t $ ) とする。
  - $ 2 $ つのカップの味が異なるなら、満足度は $ \displaystyle\ s+t $ である。
  - そうでないなら、満足度は $ \displaystyle\ s\ +\ \frac{t}{2} $ である。
 
満足度として達成可能な最大値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \le\ N\ \le\ 3\ \times\ 10^5 $
- $ 1\ \le\ F_i\ \le\ N $
- $ 2\ \le\ S_i\ \le\ 10^9 $
- $ S_i $ は偶数
 
### Sample Explanation 1

$ 2 $ カップ目と $ 4 $ カップ目のアイスを食べることを考えます。 - $ 2 $ カップ目の味は $ 2 $ 、美味しさは $ 10 $ です。 - $ 4 $ カップ目の味は $ 3 $ 、美味しさは $ 6 $ です。 - 両者の味は異なるので、満足度は $ 10+6=16 $ です。 以上より、満足度 $ 16 $ を達成できます。 満足度を $ 16 $ より大きくすることはできません。

### Sample Explanation 2

$ 1 $ カップ目と $ 4 $ カップ目のアイスを食べることを考えます。 - $ 1 $ カップ目の味は $ 4 $ 、美味しさは $ 10 $ です。 - $ 4 $ カップ目の味は $ 4 $ 、美味しさは $ 12 $ です。 - 両者の味は同じなので、満足度は $ 12+\frac{10}{2}=17 $ です。 以上より、満足度 $ 17 $ を達成できます。 満足度を $ 17 $ より大きくすることはできません。

## 样例 #1

### 输入

```
4

1 4

2 10

2 8

3 6```

### 输出

```
16```

## 样例 #2

### 输入

```
4

4 10

3 2

2 4

4 12```

### 输出

```
17```

# AI分析结果



**唯一算法分类**  
贪心算法

---

**综合分析与结论**  
题目要求选择两个冰淇淋，使得满足度最大。核心思路是贪心算法，分两种情况讨论：  
1. **不同口味**：取两个最大美味度的不同口味冰淇淋之和。  
2. **同口味**：取同一口味中两个最高美味度的组合（最大值 + 次大值的一半）。  

**关键步骤**：  
- 将所有冰淇淋按美味度降序排序。  
- 取最大冰淇淋后，遍历后续元素找到第一个不同口味的冰淇淋，计算总美味度。  
- 若次大值与最大值同口味，需额外计算其组合值。  
- 比较两种情况的最大值，取最大者。  

**可视化设计**：  
- **动画展示**：排序后的数组以颜色区分口味，高亮最大值和候选元素。  
- **步进控制**：单步执行遍历过程，展示不同情况的比较逻辑。  
- **复古像素风**：用8位色块表示冰淇淋，颜色区分口味，动态标记当前操作元素。  

---

**题解清单 (≥4星)**  
1. **Elairin176（5星）**  
   - 思路清晰，分两种情况处理，时间复杂度低（O(n log n)）。  
   - 代码简洁，直接排序后遍历，确保找到最优解。  

2. **Miyamizu_Mitsuha（4星）**  
   - 详细证明贪心正确性，代码逻辑严谨。  
   - 通过遍历次大值后的元素覆盖所有可能情况。  

3. **Failure_Terminator（4星）**  
   - 维护各口味最大值数组，分两类计算最优解。  
   - 时间复杂度O(n)，适用于大数据量。  

---

**最优思路与代码实现**  
**核心思路**：排序后分情况讨论，优先选择不同口味的最优组合。  
```cpp
#include <bits/stdc++.h>
using namespace std;

struct IceCream { int flavor, taste; };

int main() {
    int n; cin >> n;
    vector<IceCream> ices(n);
    for (auto &ice : ices) cin >> ice.flavor >> ice.taste;
    sort(ices.begin(), ices.end(), [](auto &a, auto &b) { return a.taste > b.taste; });

    int max_taste = 0;
    int first_flavor = ices[0].flavor;
    // 情况1：最大和次大不同口味
    for (int i = 1; i < n; i++) {
        if (ices[i].flavor != first_flavor) {
            max_taste = ices[0].taste + ices[i].taste;
            break;
        }
    }
    // 情况2：同口味中次大值
    int same_flavor_max = ices[0].taste;
    for (int i = 1; i < n; i++) {
        if (ices[i].flavor == first_flavor) {
            max_taste = max(max_taste, same_flavor_max + ices[i].taste / 2);
            break;
        }
    }
    cout << max_taste << endl;
}
```

---

**同类型题与算法套路**  
- **通用解法**：排序后分情况讨论，维护极值或前N大元素。  
- **类似题目**：  
  1. [LeetCode 1679. Max Number of K-Sum Pairs](https://leetcode.com/problems/max-number-of-k-sum-pairs/)  
  2. [洛谷 P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)  
  3. [Codeforces 1399C. Boats Competition](https://codeforces.com/problemset/problem/1399/C)  

---

**个人心得摘录**  
- **Elairin176**：无需复杂预处理，排序后直接遍历即可覆盖所有情况。  
- **Miyamizu_Mitsuha**：贪心正确性需严格证明，避免漏解。  

---

**可视化与复古游戏化设计**  
1. **像素化展示**：  
   - 冰淇淋用不同色块表示，颜色对应口味，大小对应美味度。  
   - 最大值用闪烁边框标记，候选元素用箭头指示。  
2. **音效与动画**：  
   - 发现新候选时播放“滴”声，确定最优解时播放胜利音效。  
   - 背景音乐采用8位芯片音乐循环播放。  
3. **交互设计**：  
   - 控制面板支持暂停/继续/单步执行。  
   - 右侧面板实时显示当前最大值和候选值比较结果。  

---

**推荐题目**  
1. [洛谷 P1223 排队接水](https://www.luogu.com.cn/problem/P1223)  
2. [洛谷 P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
3. [ABC251D - At Most 3 (Contestant ver.)](https://atcoder.jp/contests/abc251/tasks/abc251_d)

---
处理用时：160.38秒