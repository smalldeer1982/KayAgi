# 题目信息

# Make Equal

## 题目描述

There are $ n $ containers of water lined up, numbered from left to right from $ 1 $ to $ n $ . Each container can hold any amount of water; initially, the $ i $ -th container contains $ a_i $ units of water. The sum of $ a_i $ is divisible by $ n $ .

You can apply the following operation any (possibly zero) number of times: pour any amount of water from the $ i $ -th container to the $ j $ -th container, where $ i $ must be less than $ j $ (i.e. $ i<j $ ). Any index can be chosen as $ i $ or $ j $ any number of times.

Determine whether it is possible to make the amount of water in all containers the same using this operation.

## 说明/提示

In the third test case of the example ( $ a=[4, 5, 2, 1, 3] $ ), you can proceed as follows:

- pour $ 1 $ unit of water from the first vessel to the fourth, then $ a=[3, 5, 2, 2, 3] $ ;
- pour $ 1 $ unit of water from the second vessel to the third, then $ a=[3, 4, 3, 2, 3] $ ;
- pour $ 1 $ unit of water from the second vessel to the fourth, then $ a=[3, 3, 3, 3, 3] $ .

## 样例 #1

### 输入

```
6
1
43
2
1 3
5
4 5 2 1 3
3
1 2 3
7
4 5 5 0 6 4 4
7
6 5 5 1 3 4 4```

### 输出

```
YES
NO
YES
NO
NO
YES```

# AI分析结果



---

**算法分类**  
贪心算法

---

### **题解思路与算法要点**

1. **核心逻辑**  
   所有容器最终水量必须等于总和除以 `n`（记为 `avg`）。由于只能将水从前往后倒，关键在于确保每个位置之前积累的多余水量足以覆盖后续不足的部分。

2. **关键变量与遍历方式**  
   - **维护累计变量 `diff`**：表示当前可向后传递的多余水量。  
   - **从前向后遍历**：每个位置 `i` 的差值为 `a[i] - avg`，累加到 `diff`。若 `diff < 0`，说明前方积累不足以补足当前需求，直接判否。

3. **难点与对比**  
   - **难点**：理解 `diff` 的累计意义，即每个位置的多余或不足必须由前面已处理的部分完全覆盖。  
   - **对比**：部分题解从后向前遍历，维护后方所需总水量 (`now`)，确保当前容器多余水量可覆盖后方需求。两种方法本质等价，但前向遍历更简洁。

---

### **题解评分 ≥4星**

1. **RyanLi (5星)**  
   - **亮点**：代码极简，维护 `diff` 变量，仅需一次遍历，时空复杂度最优。  
   - **代码片段**：  
     ```cpp
     for (int i = 1; i <= n; ++i) {
         diff += a[i] - aver;
         if (diff < 0) flag = true;
     }
     ```

2. **Eason_cyx (4星)**  
   - **亮点**：显式处理差值数组 `d[]`，通过 `psts` 变量模拟水量流动，逻辑清晰但稍显冗余。  
   - **代码片段**：  
     ```cpp
     if (d[i] < 0) {
         if (psts < abs(d[i])) { flag = false; break; }
         psts -= abs(d[i]);
     }
     ```

3. **__O_v_O__ (4星)**  
   - **亮点**：反向遍历维护后方需求 (`now`)，验证当前容器是否满足后方总需求，思路独特。  
   - **代码片段**：  
     ```cpp
     afor(j, n, 1, BTS) {  // 反向遍历
         if (a[j] > sum) now -= (a[j] - sum);
         else now += (sum - a[j]);
     }
     ```

---

### **最优思路提炼**

- **核心技巧**：使用单变量累计前方多余水量，确保每一步非负。  
- **代码优化**：无需预处理或额外数组，直接遍历一次即可。  
- **思维关键**：贪心策略下，局部最优（及时补足需求）保证全局可行。

---

### **同类题目推荐**

1. **P1115 最大子段和**  
   - 思路：维护前缀和的局部最优，类似贪心逻辑。  
2. **P1090 合并果子**  
   - 思路：贪心选择最小代价合并，优先队列维护状态。  
3. **P1223 排队接水**  
   - 思路：排序优化局部等待时间，贪心策略应用。

---

### **可视化与动画设计**

1. **动画方案**  
   - **数据结构**：横向排列的容器，颜色标记当前水量（绿=达标，红=过多，蓝=不足）。  
   - **核心步骤**：  
     - 高亮当前处理容器，显示 `a[i]-avg` 的差值。  
     - 动态更新顶部 `diff` 变量，颜色渐变（绿→红表示正负）。  
     - 若 `diff < 0`，播放警示音效并暂停。  

2. **复古像素风格**  
   - **绘制**：8-bit 容器像素块，顶部状态栏显示 `diff` 数值。  
   - **音效**：  
     - 正常操作：短促“滴”声。  
     - 错误触发：低音“哔”声。  
   - **交互**：支持步进/暂停，速度调节滑块。  

3. **自动演示模式**  
   - **AI 逻辑**：按固定速度遍历容器，动态显示 `diff` 变化。  
   - **关卡设计**：分阶段展示不同测试用例，积分奖励正确判断。

---

### **个人心得摘录**

- **RyanLi 的调试经验**：初始误判 `diff` 的更新顺序，通过小样例验证修正。  
- **__O_v_O__ 的逆向思维**：从后向前分析需求，避免正向累计的直觉陷阱。  
- **Shadow_T 的变量命名**：`spare` 直观体现“备用水量”，提升代码可读性。

---

**代码实现（RyanLi 版本）**  
完整代码见题解列表，核心逻辑如下：  
```cpp
for (int i = 1; i <= n; ++i) {
    diff += a[i] - aver;  // 累计多余或不足
    if (diff < 0) {        // 前方积累不足以补足
        cout << "NO\n";
        return;
    }
}
cout << "YES\n";
```

---
处理用时：163.33秒