# 题目信息

# Jumping Through Segments

## 题目描述

Polycarp is designing a level for a game. The level consists of $ n $ segments on the number line, where the $ i $ -th segment starts at the point with coordinate $ l_i $ and ends at the point with coordinate $ r_i $ .

The player starts the level at the point with coordinate $ 0 $ . In one move, they can move to any point that is within a distance of no more than $ k $ . After their $ i $ -th move, the player must land within the $ i $ -th segment, that is, at a coordinate $ x $ such that $ l_i \le x \le r_i $ . This means:

- After the first move, they must be inside the first segment (from $ l_1 $ to $ r_1 $ );
- After the second move, they must be inside the second segment (from $ l_2 $ to $ r_2 $ );
- ...
- After the $ n $ -th move, they must be inside the $ n $ -th segment (from $ l_n $ to $ r_n $ ).

The level is considered completed if the player reaches the $ n $ -th segment, following the rules described above. After some thought, Polycarp realized that it is impossible to complete the level with some values of $ k $ .

Polycarp does not want the level to be too easy, so he asks you to determine the minimum integer $ k $ with which it is possible to complete the level.

## 说明/提示

In the third example, the player can make the following moves:

- Move from point $ 0 $ to point $ 5 $ ( $ 3 \le 5 \le 8 $ );
- Move from point $ 5 $ to point $ 10 $ ( $ 10 \le 10 \le 18 $ );
- Move from point $ 10 $ to point $ 7 $ ( $ 6 \le 7 \le 11 $ ).

Note that for the last move, the player could have chosen not to move and still complete the level.

## 样例 #1

### 输入

```
4
5
1 5
3 4
5 6
8 10
0 1
3
0 2
0 1
0 3
3
3 8
10 18
6 11
4
10 20
0 5
15 17
2 2```

### 输出

```
7
0
5
13```

# AI分析结果



---

## 算法分类  
**二分**

---

## 题解思路与算法要点  

### 核心思路  
1. **二分答案**：通过二分法寻找最小的可行跳跃距离 `k`。  
2. **区间维护**：每次跳跃后，维护当前可能的坐标区间 `[left, right]`，通过扩展该区间并与当前线段取交集，验证 `k` 的可行性。  
3. **交集判断**：若扩展后的区间与当前线段无交集，则当前 `k` 不合法；否则更新区间为交集后的范围，继续处理后续线段。  

### 解决难点  
- **动态区间更新**：每次跳跃后的区间扩展需要与当前线段范围取交集，维护可能的位置范围。  
- **二分边界处理**：合理设置初始左右边界（如 `left=0`, `right=1e9`），并在二分过程中正确处理区间收缩条件。  

---

## 题解评分 (≥4星)  

1. **abensyl (5星)**  
   - **亮点**：代码简洁高效，使用对称的 `max` 和 `min` 维护区间，逻辑清晰。  
   - **优化点**：合理处理初始边界，避免冗余计算。  

2. **WAis_WonderfulAnswer (4星)**  
   - **亮点**：变量命名规范，代码可读性强，明确维护 `[ll, rr]` 区间。  
   - **优化点**：二分循环条件可优化为更直观的形式。  

3. **kczw (4星)**  
   - **亮点**：代码简洁，使用宏优化 `max` 和 `min`，适合竞赛场景。  
   - **优化点**：缺少详细注释，但逻辑紧凑。  

---

## 最优思路提炼  

1. **二分框架**：  
   ```cpp  
   int lef = 0, rig = 1e9;  
   while (lef <= rig) {  
       int mid = (lef + rig) >> 1;  
       if (check(mid)) rig = mid - 1;  
       else lef = mid + 1;  
   }  
   ```  
   - **关键点**：通过二分法快速缩小 `k` 的范围。  

2. **区间维护逻辑**：  
   ```cpp  
   int posl = 0, posr = 0;  
   for (int i = 1; i <= n; ++i) {  
       posl -= k, posr += k;  // 扩展区间  
       if (posl > r[i] || posr < l[i]) return false;  // 无交集  
       posl = max(posl, l[i]);  
       posr = min(posr, r[i]);  // 取交集  
   }  
   ```  
   - **关键点**：每次跳跃后动态更新可行区间，确保始终落在当前线段内。  

---

## 同类型题与算法套路  

1. **二分答案模板题**：如「跳石头」「供暖器」等，均需在有序答案空间中验证可行性。  
2. **动态区间维护**：类似「滑动窗口」「合并区间」问题，需实时维护有效区间。  

---

## 推荐题目  

1. **P2678 跳石头**  
   - **核心**：二分最小跳跃距离，验证移除石头数是否合法。  

2. **P3743 kotori的设备**  
   - **核心**：二分时间，验证设备能否持续运行。  

3. **P1182 数列分段 Section II**  
   - **核心**：二分最大段和，验证分段数是否满足要求。  

---

## 个人心得摘录  

- **调试经验**：初始区间未正确维护导致错误，需注意每次跳跃后的区间更新顺序。  
- **顿悟点**：区间的交集操作保证了后续跳跃的合法性，避免无效分支。  

---

## 可视化与算法演示  

### 动画方案  
1. **区间扩展与收缩**：  
   - 初始区间 `[0, 0]`，每次跳跃后扩展为 `[left-k, right+k]`，高亮当前线段 `[l_i, r_i]` 并显示交集结果。  
   - **颜色标记**：  
     - 绿色：当前可行区间。  
     - 红色：无交集（`k` 不合法）。  
     - 黄色：扩展后的区间与线段相交。  

2. **二分过程可视化**：  
   - **Canvas 网格**：横轴表示 `k` 的取值范围，纵轴表示二分步骤。  
   - **像素风格**：每次 `mid` 更新时，显示当前 `left`、`mid`、`right` 的位置，使用 8-bit 音效提示状态变化。  

3. **交互设计**：  
   - **步进控制**：用户可手动点击调整二分步骤，观察区间变化。  
   - **自动模式**：AI 自动执行二分，音效提示合法/非法状态。  

### 复古游戏化设计  
- **音效**：  
  - `mid` 更新：短促“哔”声。  
  - 合法 `k`：上扬音调。  
  - 非法 `k`：低沉音效。  
- **积分系统**：每正确收缩区间获得 10 分，连续正确触发连击奖励。  

---

## 核心代码实现  

```cpp  
bool check(int k) {  
    int posl = 0, posr = 0;  
    for (int i = 1; i <= n; ++i) {  
        posl -= k;  
        posr += k;  
        if (posl > r[i] || posr < l[i]) return false;  
        posl = max(posl, l[i]);  
        posr = min(posr, r[i]);  
    }  
    return true;  
}  
```  

完整代码见原题解。  

---

**可视化演示链接**：[示例实现](https://example.com/demo)（需自行实现交互逻辑）

---
处理用时：83.34秒