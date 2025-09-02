# 题目信息

# Peanuts

## 题目描述

Having the magical beanstalk, Jack has been gathering a lot of peanuts lately. Eventually, he has obtained $ n $ pockets of peanuts, conveniently numbered $ 1 $ to $ n $ from left to right. The $ i $ -th pocket has $ a_i $ peanuts.

Jack and his childhood friend Alice decide to play a game around the peanuts. First, Alice divides the pockets into some boxes; each box will have a non-zero number of consecutive pockets, and each pocket will, obviously, belong to exactly one box. At the same time, Alice does not change the order of the boxes, that is, the boxes are numbered in ascending order of the indices of the pockets in them.

After that, Alice and Jack will take turns alternately, with Alice going first.

At each turn, the current player will remove a positive number of peanuts from exactly one pocket which belongs to the leftmost non-empty box (i.e., the leftmost box containing at least one non-empty pocket). In other words, if we number the boxes from left to right, then each player can only pick peanuts from the pocket in the $ j $ -th box ( $ j \ge 2 $ ) only if the $ (j - 1) $ -th box has no peanuts left. The player who cannot make a valid move loses.

Alice is sure she will win since she has the advantage of dividing the pockets into boxes herself. Thus, she wanted to know how many ways there are for her to divide the peanuts into boxes at the start of the game so that she will win, assuming both players play optimally. Can you help her with the calculation?

As the result can be very large, output it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, the only way for Alice to win is to divide the pockets into two boxes as follows: $ ([1, 2], [3]) $ (the first box contains the first two pockets and the second box contains the third pocket). Alice wins by taking both peanuts from the second pocket, leaving Jack with $ ([1], [3]) $ . Jack is forced to take the only peanut left in the first box, which allows Alice to take the remaining ones in the second box.

In the second test case, the winning divisions for Alice are $ ([1], [2, 3, 1]) $ , $ ([1, 2, 3, 1]) $ , $ ([1, 2], [3], [1]) $ , and $ ([1, 2], [3, 1]) $ .

In the third test case, Alice always wins no matter how she divides the pockets into boxes.

In the fourth test case, Alice always loses no matter how she divides the pockets into boxes.

## 样例 #1

### 输入

```
5
3
1 2 3
4
1 2 3 1
5
1 1 1 1 1
2
1 1
10
1 2 3 4 5 6 7 8 9 10```

### 输出

```
1
4
16
0
205```

# AI分析结果



0. **题目翻译**  
---

# 花生

## 题目描述

拥有魔法豆茎的杰克最近收集了大量花生。最终他获得了 $n$ 袋花生，按从左到右顺序编号为 $1$ 到 $n$。第 $i$ 袋装有 $a_i$ 颗花生。

杰克和他的童年玩伴爱丽丝决定用花生玩一个游戏。首先，爱丽丝将袋子分成若干个盒子；每个盒子必须包含连续的非空袋子，且每个袋子只能属于一个盒子。分盒完成后，爱丽丝和杰克将轮流进行操作，爱丽丝先手。

每轮操作中，当前玩家必须从最左侧非空盒子（即包含至少一个非空袋子的最左侧盒子）的某个袋子里取出正整数颗花生。换句话说，若将盒子从左到右编号，玩家只能在第 $j$ 个盒子（$j \ge 2$）操作的前提是第 $(j-1)$ 个盒子已无花生。无法进行有效操作的玩家判负。

爱丽丝确信自己可以通过合理分盒赢得游戏。因此她想知道初始分盒方案中能确保她获胜的总数，结果对 $998\,244\,353$ 取模。

---

1. **唯一算法分类**  
**线性DP**

---

2. **综合分析与结论**  

### 核心思路
题目本质是博弈论与动态规划的结合，需要处理两种博弈规则：
1. **Nim游戏**：异或和不为零时先手必胜
2. **反Nim游戏**：存在非1元素时规则同Nim，全1时胜负与奇偶性相关

### 动态规划设计
- **状态定义**：  
  $f[i][0/1]$ 表示前 $i$ 个袋子划分后，最后一段是**Nim/反Nim游戏**时爱丽丝必胜的方案数
- **转移方程**：  
  从 $j$ 处划分时：
  ```math
  f[i][0] = \sum (f[j][1] \text{当[j+1,i]为Nim必胜} + f[j][0] \text{当[j+1,i]为Nim必败})
  f[i][1] = \sum (f[j][0] \text{当[j+1,i]为反Nim必胜} + f[j][1] \text{当[j+1,i]为反Nim必败})
  ```

### 优化关键
1. **异或前缀和**：使用 $s_i = a_1 \oplus ... \oplus a_i$ 快速判断区间异或
2. **哈希桶优化**：用哈希表记录特定异或值对应的方案数，将转移复杂度降为 $O(1)$
3. **全1段处理**：维护连续1的区间，通过奇偶性分桶统计

---

3. **题解清单 (≥4星)**

| 题解作者 | 星级 | 核心亮点 |
|---------|-----|---------|
| 2020HZ06 | ★★★★☆ | 双哈希桶设计，清晰处理正常/反常博弈转移 |
| DaiRuiChen007 | ★★★★ | 逆向状态转移，代码结构简洁 |
| lfxxx | ★★★★ | 极简状态定义，特殊处理全1段 |

---

4. **代码核心实现**

```cpp
// 2020HZ06 题解核心片段
for(int i=1;i<=n;i++){
    // 处理正常Nim转移
    f[i][0] = (g - buc[a[i]][1] + buc[a[i]][0]) % mod;
    
    // 处理全1段中断后的反Nim转移
    if(c[i]>1){
        while(pos<i) 更新双指针位置并更新反Nim桶
    }
    
    // 更新反Nim转移的奇偶性贡献
    f[i][1] = (G - Buc[a[i]][1] + Buc[a[i]][0] + 奇偶贡献) % mod;
    
    // 更新哈希桶
    buc[a[i]][0] += f[i][0];
    buc[a[i]][1] += f[i][1];
}
```

---

5. **可视化设计**

### 像素化DP矩阵
- **8色调色板**：  
  红色表示Nim转移，蓝色表示反Nim转移，绿色表示异或值为0的位置
- **Canvas网格**：每个单元格显示状态值，边框颜色表示当前操作段
- **音效触发**：  
  - 清脆"滴"声：正常状态转移
  - 低沉"嘟"声：全1段处理
  - 金币音效：找到可行解

### 自动演示模式
```javascript
function autoPlay() {
    let step = 0;
    const timer = setInterval(() => {
        if(step >= n) clearInterval(timer);
        highlightCell(step, 0); // 高亮当前处理位置
        updateBucketDisplay();  // 显示哈希桶变化
        step++;
    }, 500);
}
```

---

6. **同类型题目推荐**
1. P2575 高手过招（博弈论+状态压缩）
2. P2964 [USACO09NOV]硬币游戏（前缀和优化DP）
3. P2148 [SDOI2009] E&D（SG函数应用）

---
处理用时：57.81秒