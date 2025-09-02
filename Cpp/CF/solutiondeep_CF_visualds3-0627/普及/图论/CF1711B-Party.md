# 题目信息

# Party

## 题目描述

A club plans to hold a party and will invite some of its $ n $ members. The $ n $ members are identified by the numbers $ 1, 2, \dots, n $ . If member $ i $ is not invited, the party will gain an unhappiness value of $ a_i $ .

There are $ m $ pairs of friends among the $ n $ members. As per tradition, if both people from a friend pair are invited, they will share a cake at the party. The total number of cakes eaten will be equal to the number of pairs of friends such that both members have been invited.

However, the club's oven can only cook two cakes at a time. So, the club demands that the total number of cakes eaten is an even number.

What is the minimum possible total unhappiness value of the party, respecting the constraint that the total number of cakes eaten is even?

## 说明/提示

In the first test case, all members can be invited. So the unhappiness value is $ 0 $ .

In the second test case, the following options are possible:

- invite $ 1 $ and $ 2 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 3 $ );
- invite $ 2 $ and $ 3 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 2 $ );
- invite only $ 1 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 4 $ );
- invite only $ 2 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 5 $ );
- invite only $ 3 $ ( $ 0 $ cakes eaten, unhappiness value equal to $ 3 $ );
- invite nobody ( $ 0 $ cakes eaten, unhappiness value equal to $ 6 $ ).

 The minimum unhappiness value is achieved by inviting $ 2 $ and $ 3 $ .In the third test case, inviting members $ 3,4,5 $ generates a valid party with the minimum possible unhappiness value.

## 样例 #1

### 输入

```
4
1 0
1
3 1
2 1 3
1 3
5 5
1 2 3 4 5
1 2
1 3
1 4
1 5
2 3
5 5
1 1 1 1 1
1 2
2 3
3 4
4 5
5 1```

### 输出

```
0
2
3
2```

# AI分析结果



---

## 唯一算法分类  
**图论中的奇偶分析**

---

## 综合分析与结论  
题目核心在于处理图的边数奇偶性。当原始边数 \( m \) 为奇数时，必须通过删除点使得剩余边数为偶数。关键思路为：  
1. **删除奇数度数的点**：该操作会减少奇数次边数（度数本身为奇数的点连接的边数为奇数，删除后边数减少奇数次，奇-奇=偶）。  
2. **删除一条边上的两个点**：若两点的度数之和为偶数（即两奇或两偶），删除后边数减少奇数次（度数之和减去公共边数）。  

**难点**在于快速枚举这两种情况的最小代价。通过预处理度数并遍历点/边，时间复杂度为 \( O(n + m) \)。  

**可视化设计思路**：  
- **颜色标记**：奇度数点用红色，偶度数点用绿色，边用灰色线条。  
- **动态操作**：点击点或边时，显示删除后的边数变化和代价。  
- **复古风格**：像素化节点和边，删除时播放 8-bit 音效，背景音乐循环播放。  
- **自动演示**：依次删除所有候选点/边，展示最优解的搜索过程。

---

## 题解清单 (≥4星)  
1. **Hovery (⭐️⭐️⭐️⭐️⭐️)**  
   - 思路清晰，代码简洁，直接枚举奇点与边两端点。  
   - 关键亮点：快速判断边两端度数之和是否为偶数，避免复杂计算。  
2. **IGJHL (⭐️⭐️⭐️⭐️)**  
   - 详细分类讨论，补充了删除两个点的六种情况分析。  
   - 代码规范，注释明确，适合新手理解。  
3. **Bai_Kking (⭐️⭐️⭐️⭐️)**  
   - 代码实现简洁，核心逻辑与上述解法一致，但未处理冗余情况。  

---

## 最优思路或技巧提炼  
1. **奇偶转换**：删除奇度数点或相邻偶度数点对，将总边数奇偶性翻转。  
2. **贪心策略**：直接遍历所有可能的最优候选（奇点、边两端点），取最小值。  
3. **度数预处理**：通过计算度数快速判断候选点类型，避免重复遍历边。  

**代码片段**（Hovery 的关键逻辑）：  
```cpp
if (m % 2 == 0) cout << "0\n"; // 情况1：边数已为偶数
else {
    int ans = INF;
    // 枚举奇点
    for (int i = 1; i <= n; i++) 
        if (deg[i] % 2) ans = min(ans, a[i]);
    // 枚举边两端点
    for (int i = 1; i <= m; i++) 
        if ((deg[u[i]] + deg[v[i]]) % 2 == 0)
            ans = min(ans, a[u[i]] + a[v[i]]);
    cout << ans << endl;
}
```

---

## 同类型题或类似算法套路  
1. **图的奇偶性调整**：如判断欧拉路径是否存在（度数奇偶性）。  
2. **贪心选择**：在满足条件的前提下选择局部最优解。  
3. **边与点的关联分析**：通过度数快速关联点与边的性质。  

**推荐题目**：  
1. [洛谷 P1330 封锁阳光大学](https://www.luogu.com.cn/problem/P1330)  
2. [洛谷 P1341 无序字母对](https://www.luogu.com.cn/problem/P1341)  
3. [CF 1176E Cover it!](https://codeforces.com/problemset/problem/1176/E)  

---

## 个人心得摘录  
- **zhicheng**：在反例中发现删除相邻偶点更优，强调需验证所有可能性。  
- **Shimotsuki**：将问题转化为子图边数奇偶性，简化分析过程。  

---

## 可视化与算法演示  
**实现方案**：  
1. **Canvas 绘制**：  
   - 节点为圆形，奇度数红色，偶度数绿色；边为灰色线段。  
   - 删除节点时，播放“碎裂”音效，相关边变虚线。  
2. **交互逻辑**：  
   - 点击节点/边显示删除代价和剩余边数。  
   - 自动模式：按候选顺序遍历，高亮当前最优解。  
3. **复古风格**：  
   - 8-bit 背景音乐（循环播放）。  
   - 音效：删除成功（上扬音调），无解（低沉音效）。  

**核心代码（伪代码）**：  
```javascript
// 初始化图
drawGraph(nodes, edges);
// 自动演示最优解
function autoDemo() {
    let candidates = [...奇点, ...边两端点];
    for (let c of candidates) {
        highlight(c);
        calculateCost(c);
        playSound('beep');
    }
    showFinalAnswer();
}
```

---
处理用时：91.42秒