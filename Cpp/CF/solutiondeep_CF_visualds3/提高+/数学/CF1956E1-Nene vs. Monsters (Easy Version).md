# 题目信息

# Nene vs. Monsters (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference between the versions is the constraints on $ a_i $ . You can make hacks only if both versions of the problem are solved.

Nene is fighting with $ n $ monsters, located in a circle. These monsters are numbered from $ 1 $ to $ n $ , and the $ i $ -th ( $ 1 \le i \le n $ ) monster's current energy level is $ a_i $ .

Since the monsters are too strong, Nene decided to fight with them using the Attack Your Neighbour spell. When Nene uses this spell, the following actions happen in the following order one by one:

- The $ 1 $ -st monster attacks the $ 2 $ -nd monster;
- The $ 2 $ -nd monster attacks the $ 3 $ -rd monster;
- $ \ldots $
- The $ (n-1) $ -th monster attacks the $ n $ -th monster;
- The $ n $ -th monster attacks the $ 1 $ -st monster.

When the monster with energy level $ x $ attacks the monster with the energy level $ y $ , the energy level of the defending monster becomes $ \max(0, y-x) $ (the energy level of the attacking monster remains equal to $ x $ ).

Nene is going to use this spell $ 10^{100} $ times and deal with the monsters that will still have a non-zero energy level herself. She wants you to determine which monsters will have a non-zero energy level once she will use the described spell $ 10^{100} $ times.

## 说明/提示

In the first test case, the following actions happen during the first $ 3 $ uses of the spell in this order:

- Nene uses the Attack Your Neighbour spell for the first time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 5-2)=3 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 3-3)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ ;
- Nene uses the Attack Your Neighbour spell for the second time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 3-2)=1 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 0-1)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ ;
- Nene uses the Attack Your Neighbour spell for the third time;
- the $ 1 $ -st monster attacks the $ 2 $ -nd monster, after the attack the energy level of the $ 2 $ -nd monster becomes equal to $ \max(0, 1-2)=0 $ ;
- the $ 2 $ -nd monster attacks the $ 3 $ -rd monster, after the attack the energy level of the $ 3 $ -rd monster becomes equal to $ \max(0, 0-0)=0 $ ;
- the $ 3 $ -rd monster attacks the $ 1 $ -st monster, after the attack the energy level of the $ 1 $ -st monster becomes equal to $ \max(0, 2-0)=2 $ .

After each of the next uses of the spell, energy levels of monsters do not change. Thus, only the $ 1 $ -st monster has a non-zero energy level in the end.

In the second test case, both monsters initially have zero energy level.

## 样例 #1

### 输入

```
5
3
2 5 3
2
0 0
4
1 5 7 2
4
4 2 1 2
13
1 1 4 5 1 4 1 9 1 9 8 1 0```

### 输出

```
1
1 
0

1
1 
2
1 3 
6
1 3 6 8 10 12```

# AI分析结果


### 💡 Kay的C++算法解析：Nene vs. Monsters (Easy Version) 深入学习指南 💡

**引言**  
今天我们一起分析这道有趣的环形怪物对战题。本指南将帮你掌握模拟优化的核心思想，理解有限轮次稳定的巧妙性质，并通过像素动画直观感受算法流程。

---

## 1. 题目解读与核心算法识别
✨ **本题主要考察**：`模拟优化`（利用性质减少操作轮次）  
🗣️ **初步分析**：  
> 这道题如同像素游戏中的怪物车轮战：n个怪物围成一圈，依次攻击下一个怪物（防御方能量变为max(0, y-x)）。由于操作次数高达$10^{100}$，直接模拟不可行。核心技巧是发现**操作在有限轮次后进入稳定状态**（任意三个相邻怪物不会同时非零）。  
> - **题解思路对比**：  
>   - FFTotoro：动态检查"三个连续非零"条件，满足则继续模拟一轮  
>   - ReTF：固定模拟650轮（≈√值域）确保稳定  
> - **可视化设计**：  
>   采用8位像素风格（类似FC游戏），怪物显示为彩色方块，高度代表能量值：  
>   - **关键步骤高亮**：攻击时发射像素箭头，被攻击方高度降低并显示伤害值  
>   - **稳定标记**：三个连续非零时触发警告红光，稳定后存活怪物绿色闪烁  
>   - **音效设计**：攻击时"叮"声，能量归零时"碎裂"声，稳定时胜利音效  

---

## 2. 精选优质题解参考
**题解一（FFTotoro）**  
* **点评**：  
  思路清晰抓住核心性质——通过动态检测三个连续非零（`a[i]&&a[i+1]&&a[i+2]`）决定是否继续模拟。代码规范：  
  - 使用Lambda函数封装条件检查（第18-23行），逻辑紧凑  
  - 特判n=2的边界情况（第10-16行），避免性质失效  
  - 稳定后巧妙收集"前一个为零且自己非零"的怪物（第26行）  
  时间复杂度O(n√V)在值域V=100时高效，可直接用于竞赛。

**题解二（ReTF）**  
* **点评**：  
  提供重要理论支撑：证明√V轮后非零连通块≤2。实践采用固定650轮模拟：  
  - 优势：代码实现更简单（未提供代码但思路明确）  
  - 注意点：固定轮次需合理估算（本题√200≈14.14，取650确保安全）  
  启发我们：当上界可证明时，固定轮次是更稳定的选择。

---

## 3. 核心难点辨析与解题策略
1. **难点1：如何确定模拟终止条件？**  
   * **分析**：  
     两种策略各有千秋：动态检查精确但需循环判断；固定轮次简单但依赖值域估算。优质题解均抓住核心——**稳定时无三个连续非零**。
   * 💡 **学习笔记**：大规模模拟要先分析收敛性。

2. **难点2：稳定状态的特征处理**  
   * **分析**：  
     稳定后非零怪物形成孤点或相邻两点：  
     - 孤点（`[0, X, 0]`）：必然存活  
     - 相邻点（`[0, X, Y, 0]`）：首怪物存活（攻击方），次怪物归零（被攻击方）
   * 💡 **学习笔记**：环形结构注意模运算索引（如`(i+n-1)%n`）。

3. **难点3：边界情况n=2的特殊处理**  
   * **分析**：  
     两怪物互相攻击会振荡直至一方归零（如`[2,3]→[2,1]→[1,1]→[1,0]`）。必须单独处理。
   * 💡 **学习笔记**：算法性质失效时需特判。

### ✨ 解题技巧总结
- **技巧1：收敛性优先** - 大规模操作先证明/发现收敛条件  
- **技巧2：环形索引技巧** - 用`(i+1)%n`处理环形遍历  
- **技巧3：边界全覆盖** - 小规模数据（如n=2）单独验证  

---

## 4. C++核心代码实现赏析
**通用核心实现参考**  
* **说明**：综合两个题解优点，FFTotoro的完整实现+ReTF的收敛思想  
* **完整核心代码**：
  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
      int n; cin >> n;
      vector<int> a(n), res;
      for(auto &x : a) cin >> x;

      // 特判n=2
      if(n == 2) {
        while(a[0] && a[1]) {
          a[1] = max(0, a[1] - a[0]);
          a[0] = max(0, a[0] - a[1]);
        }
        if(a[0]) cout << "1\n1\n";
        else if(a[1]) cout << "1\n2\n";
        else cout << "0\n";
        continue;
      }

      // 动态检查三个连续非零
      while([&]{
        for(int i=0; i<n; i++)
          if(a[i] && a[(i+1)%n] && a[(i+2)%n]) 
            return true;
        return false;
      }()) 
      { // 模拟一轮攻击
        for(int i=0; i<n; i++) 
          a[(i+1)%n] = max(0, a[(i+1)%n] - a[i]);
      }

      // 收集结果：前一个为零且自己非零
      for(int i=0; i<n; i++) 
        if(a[i] && !a[(i+n-1)%n]) 
          res.push_back(i+1); // 注意编号+1

      cout << res.size() << '\n';
      for(int x : res) cout << x << ' ';
      cout << '\n';
    }
    return 0;
  }
  ```
* **代码解读概要**：  
  > 1. 特判n=2：互相攻击直至一方归零  
  > 2. 主循环：当存在三个连续非零时，模拟一轮环形攻击  
  > 3. 结果收集：满足`a[i]!=0`且`a[i-1]==0`的怪物存活  

---

## 5. 算法可视化：像素动画演示
**主题**：像素怪物大作战（复古RPG风格）  
**核心演示**：模拟攻击直至稳定状态，突出三个连续非零的检测与破除  

### 动画设计（FC红白机风格）
1. **场景初始化**  
   - 怪物显示为彩色像素方块（高度=能量值），环形排列  
   <center>
   | 位置 | 1 | 2 | 3 |  
   |------|---|---|---|
   | 能量 | ▮▮ | ▮▮▮▮▮ | ▮▮▮ |
   </center>

2. **攻击过程演示**  
   - **单步攻击**：攻击方闪烁红光→发射像素箭头→被攻击方高度降低（显示`-X`数值）  
   ```python
   # 伪代码：第i个怪物攻击动画
   highlight(monster[i], color=RED)  // 攻击方高亮
   draw_arrow(i → (i+1)%n)           // 绘制攻击箭头
   update_health((i+1)%n, -damage)   // 更新血条并显示伤害值
   ```

3. **稳定条件检测**  
   - 每轮结束扫描：发现三个连续非零时（如位置1-2-3），触发警告红光  
   - 破除动画：该区域快速闪烁三次后继续攻击

4. **游戏化控制面板**  
   ```html
   [开始] [暂停] [步进] [自动播放▼] 速度：█▁▁▁▁▁▁▁▁▁
   ```

5. **胜利结算**  
   - 稳定后：存活怪物绿色闪烁+播放胜利音效  
   - 统计界面：显示存活怪物编号列表  

---

## 6. 拓展练习与相似问题
1. **洛谷 P1996** 约瑟夫问题  
   → **推荐理由**：环形结构模拟的经典题，练习索引循环技巧  
2. **洛谷 P1028** 数的计算  
   → **推荐理由**：收敛性质分析（操作次数有限时状态稳定）  
3. **洛谷 P1030** 求先序排列  
   → **推荐理由**：理解稳定状态在树形结构的应用  

---

## 7. 学习心得与经验分享
> 本次题解未包含作者个人心得，但Kay提醒大家：  
> **调试技巧**：当模拟过程复杂时，可打印每轮后怪物状态，观察何时收敛。

---

**结语**  
通过环形怪物对战，我们掌握了模拟优化的核心思想——利用收敛性质减少操作！记住：面对大规模操作题，先分析"何时稳定"，再处理最终状态。下次挑战见！🚀

---
处理用时：149.01秒