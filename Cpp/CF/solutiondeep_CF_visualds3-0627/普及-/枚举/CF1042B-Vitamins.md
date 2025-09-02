# 题目信息

# Vitamins

## 题目描述

Berland shop sells $ n $ kinds of juices. Each juice has its price $ c_i $ . Each juice includes some set of vitamins in it. There are three types of vitamins: vitamin "A", vitamin "B" and vitamin "C". Each juice can contain one, two or all three types of vitamins in it.

Petya knows that he needs all three types of vitamins to stay healthy. What is the minimum total price of juices that Petya has to buy to obtain all three vitamins? Petya obtains some vitamin if he buys at least one juice containing it and drinks it.

## 说明/提示

In the first example Petya buys the first, the second and the fourth juice. He spends $ 5 + 6 + 4 = 15 $ and obtains all three vitamins. He can also buy just the third juice and obtain three vitamins, but its cost is $ 16 $ , which isn't optimal.

In the second example Petya can't obtain all three vitamins, as no juice contains vitamin "C".

## 样例 #1

### 输入

```
4
5 C
6 B
16 BAC
4 A
```

### 输出

```
15
```

## 样例 #2

### 输入

```
2
10 AB
15 BA
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5
10 A
9 BC
11 CA
4 A
5 B
```

### 输出

```
13
```

## 样例 #4

### 输入

```
6
100 A
355 BCA
150 BC
160 AC
180 B
190 CA
```

### 输出

```
250
```

## 样例 #5

### 输入

```
2
5 BA
11 CB
```

### 输出

```
16
```

# AI分析结果



## 算法分类
状态压缩动态规划

---

## 题解思路与核心分析
### 核心逻辑
将维生素组合（A/B/C）压缩为二进制状态（001/010/100），目标状态为111。采用动态规划思想，维护每个状态的最小花费，通过遍历果汁列表不断更新状态。

### 解决难点
- **状态表示**：用3位二进制表示维生素组合，解决了多维状态存储问题
- **转移方程**：`f[新状态] = min(f[新状态], f[旧状态] + 当前价格)`
- **边界处理**：初始化空状态为0，其他状态初始化为极大值

### 算法对比
| 方法          | 时间复杂度 | 扩展性       | 实现难度 |
|---------------|------------|--------------|----------|
| 状压DP        | O(n)       | 强（k种维生素） | 中       |
| 暴力枚举组合  | O(1)       | 仅限3种维生素 | 低       |
| 三维状态DP    | O(n)       | 弱（仅3维）    | 高       |

---

## 高分题解推荐（≥4星）
1. **ZigZagKmp（5星）**
   - 亮点：状态压缩设计精妙，代码简洁高效，可扩展性强
   - 核心代码：
     ```cpp
     for(int i=1;i<=n;++i){
         for(int j=7;j>=0;--j){
             f[j|pv[i]] = min(f[j|pv[i]], f[j]+w[i]);
         }
     }
     ```

2. **SIXIANG32（4星）**
   - 亮点：详细的状态压缩教学，适合初学者理解
   - 关键说明："按位或实现维生素集合的并集操作"

3. **览遍千秋（4星）**
   - 亮点：直观的暴力组合思路，易理解小规模场景
   - 注意点：需手动枚举所有可能的组合方式

---

## 最优技巧提炼
1. **状态压缩**：将多维状态编码为整数，如 `ABC=7(111)`，`AB=3(011)`
2. **位运算合并**：使用 `|` 运算合并维生素集合
3. **滚动更新**：逆序遍历状态避免重复计算

---

## 相似题目推荐
1. P1433 吃奶酪（状压DP经典）
2. P1171 售货员的难题（状态压缩应用）
3. P2704 炮兵阵地（复杂状压DP）

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, f[8]; 
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    
    cin >> n;
    for(int i=0; i<n; ++i){
        int cost; string s;
        cin >> cost >> s;
        
        int mask = 0;
        for(char c : s){
            if(c == 'A') mask |= 1;
            if(c == 'B') mask |= 2;
            if(c == 'C') mask |= 4;
        }
        
        for(int j=7; j>=0; --j)
            f[j|mask] = min(f[j|mask], f[j]+cost);
    }
    
    cout << (f[7] > 1e9 ? -1 : f[7]);
}
```

---

## 可视化设计
**动画方案**：
1. **状态网格**：8x1网格展示0-7的二进制状态
2. **果汁流动**：新果汁从右侧滑入，显示其维生素组合
3. **状态更新**：被更新的状态闪烁黄光，数值变化显示价格
4. **路径追踪**：用箭头显示状态转移关系

**复古特效**：
- **像素风格**：16色模式，每个状态用3个像素块表示维生素
- **音效设计**：
  - 状态更新：8-bit "哔"声
  - 达成目标：经典马里奥过关音效
- **自动演示**：AI自动选择最优路径，展示状压过程

---

## 举一反三
当遇到类似"覆盖所有要素的最优解"问题时：
1. 识别要素数量，确定状态压缩可行性
2. 设计位运算合并规则
3. 采用逆序更新避免状态污染

**思维口诀**：  
"要素组合想状压，位运算来合并它  
逆序更新保正确，状态转移min最佳"

---
处理用时：87.52秒