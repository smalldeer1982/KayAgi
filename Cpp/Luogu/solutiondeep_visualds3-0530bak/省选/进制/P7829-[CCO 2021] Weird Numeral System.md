# 题目信息

# [CCO 2021] Weird Numeral System

## 题目描述

Alice 正在思考一个关于 $k$ 进制整数的问题。

普通的 $k$ 进制可以将整数 $n$ 表示为 $d_{m - 1} d_{m - 2} \cdots d_0$，且满足：

1. $0 \leq d_i < k$；
2. $n = \displaystyle\sum_{i = 0}^{m - 1} d_i k^i$。

然而，普通的 $k$ 进制整数对于 Alice 来说太简单了，Alice 更喜欢奇怪的 $k$ 进制整数。它与普通 $k$ 进制整数的差别仅仅在于将 $0 \leq d_i < k$ 换成了 $d_i \in a$，其中 $a$ 为一个长为 $D$ 的数列。

现在有一组固定的 $a_1, a_2, \cdots, a_D$，Alice 想要将 $q$ 个十进制整数 $n_1, n_2, \cdots, n_q$ 全部转化为奇怪的 $k$ 进制整数，这种问题显然更适合写程序来解决。

## 说明/提示

**本题由 @[Leasier](https://www.luogu.com.cn/user/201007) 提供 SPJ。**
#### 数据范围
对于 $100\%$ 的数据，$2 \leq k \leq 10^6$，$1 \leq q \leq 5$，$1 \leq D \leq 801$，$1 \leq M \leq 400$，$-M \leq a_i \leq M$，$-10^{18} \leq n_i \leq 10^{18}$。
#### 题目来源
[CCO2021](https://cemc.math.uwaterloo.ca/contests/computing/2021/index.html) D1T2

## 样例 #1

### 输入

```
3 3 3 1
-1 0 1
15
8
-5```

### 输出

```
1 -1 -1 0
1 0 -1
-1 1 1```

## 样例 #2

### 输入

```
10 1 3 2
0 2 -2
17```

### 输出

```
IMPOSSIBLE```

# AI分析结果



**算法分类选择**  
动态规划 / BFS

---

**综合分析与结论**  
本题要求将十进制数转换为特殊的k进制数，每位必须选自给定集合。核心难点在于高效验证存在性并构造解。

**核心算法流程**：  
1. **预处理**：对每个数字d∈a，计算其mod k的余数，建立余数到d的映射表。  
2. **BFS搜索**：从初始余数n出发，每一步根据当前余数r的模k值，选择所有可能的d，生成新余数m=(r-d)/k。若m=0则找到解。  
3. **路径记录**：记录每一步选择的d，逆序输出即为高位到低位的解。

**可视化设计**：  
- **动画方案**：用网格展示余数变化，当前余数高亮显示，候选d以不同颜色标记。  
- **步进控制**：允许单步执行，观察余数如何被k除并选择d。  
- **像素风格**：用8位风格显示余数队列，选中节点时播放音效。

---

**题解清单 (4星以上)**  
1. **BFS+余数剪枝（5星）**  
   - 利用BFS确保最短路径，预处理余数映射加速搜索。  
   - 通过余数去重避免无限循环，时间复杂度为O(q·log_k|n|)。

---

**最优思路提炼**  
- **模运算分组**：将集合a按mod k分组，快速筛选有效数字。  
- **逆向构建**：从低位到高位逐步消减余数，保证解的构造可行性。  
- **余数剪枝**：记录已处理的余数，避免重复搜索。

---

**代码实现**  
```python
from collections import deque, defaultdict

def solve():
    import sys
    input = sys.stdin.read().split()
    ptr = 0
    k = int(input[ptr]); ptr +=1
    q = int(input[ptr]); ptr +=1
    D = int(input[ptr]); ptr +=1
    M = int(input[ptr]); ptr +=1
    a = list(map(int, input[ptr:ptr+D]))
    ptr += D
    mod_map = defaultdict(list)
    for d in a:
        mod = (d % k + k) % k
        mod_map[mod].append(d)
    for _ in range(q):
        n = int(input[ptr]); ptr +=1
        visited = set()
        queue = deque([(n, [])])
        visited.add(n)
        found = False
        res = []
        while queue:
            r, path = queue.popleft()
            if r == 0:
                res = path[::-1]
                found = True
                break
            r_mod = (r % k + k) % k
            if r_mod not in mod_map:
                continue
            for d in mod_map[r_mod]:
                m = (r - d) // k
                if m not in visited:
                    visited.add(m)
                    new_path = path + [d]
                    queue.append((m, new_path))
                    if m == 0:
                        res = new_path[::-1]
                        found = True
                        queue.clear()  # 退出循环
                        break
        if found:
            print(' '.join(map(str, res)))
        else:
            print("IMPOSSIBLE")

if __name__ == "__main__":
    solve()
```

---

**同类型题推荐**  
1. [P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)（大数处理与递推）  
2. [P1096 Hanoi双塔问题](https://www.luogu.com.cn/problem/P1096)（高精度与进制转换）  
3. [P1017 负进制转换](https://www.luogu.com.cn/problem/P1017)（负基数下的进制构造）  

---

**个人心得**  
- **负数取模**：需手动调整余数为正，确保分组正确。  
- **路径顺序**：BFS生成的是低位到高位，需逆序输出。  

---

**可视化与游戏化设计**  
- **Canvas展示**：余数队列以像素块流动，选中路径时播放8位音效。  
- **自动演示**：AI自动选择最短路径，过关时触发胜利音效。  
- **关卡积分**：按解的长度计分，鼓励找到最短路径。

---
处理用时：349.69秒