# 题目信息

# Find The Bone

## 题目描述

Zane the wizard is going to perform a magic show shuffling the cups.

There are $ n $ cups, numbered from $ 1 $ to $ n $ , placed along the $ x $ -axis on a table that has $ m $ holes on it. More precisely, cup $ i $ is on the table at the position $ x=i $ .

The problematic bone is initially at the position $ x=1 $ . Zane will confuse the audience by swapping the cups $ k $ times, the $ i $ -th time of which involves the cups at the positions $ x=u_{i} $ and $ x=v_{i} $ . If the bone happens to be at the position where there is a hole at any time, it will fall into the hole onto the ground and will not be affected by future swapping operations.

Do not forget that Zane is a wizard. When he swaps the cups, he does not move them ordinarily. Instead, he teleports the cups (along with the bone, if it is inside) to the intended positions. Therefore, for example, when he swaps the cup at $ x=4 $ and the one at $ x=6 $ , they will not be at the position $ x=5 $ at any moment during the operation.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF796B/190b731b36b585b1537188535b06ba518cad612c.png)Zane’s puppy, Inzane, is in trouble. Zane is away on his vacation, and Inzane cannot find his beloved bone, as it would be too exhausting to try opening all the cups. Inzane knows that the Codeforces community has successfully helped Zane, so he wants to see if it could help him solve his problem too. Help Inzane determine the final position of the bone.

## 说明/提示

In the first sample, after the operations, the bone becomes at $ x=2 $ , $ x=5 $ , $ x=7 $ , and $ x=1 $ , respectively.

In the second sample, after the first operation, the bone becomes at $ x=2 $ , and falls into the hole onto the ground.

## 样例 #1

### 输入

```
7 3 4
3 4 6
1 2
2 5
5 7
7 1
```

### 输出

```
1```

## 样例 #2

### 输入

```
5 1 2
2
1 2
2 4
```

### 输出

```
2```

# AI分析结果



# Find The Bone

## 题目描述

Zane 巫师要进行一场杯子魔术表演。

桌上有 $n$ 个杯子（编号 1 到 n），沿 x 轴排列。第 i 号杯子位于 x=i 的位置。桌上有 m 个洞，当骨头出现在洞的位置时会立即掉落。

骨头初始在 x=1 处。Zane 会进行 k 次交换操作，第 i 次交换位置 u_i 和 v_i 的杯子（交换是瞬间完成的，不会经过中间位置）。若交换时骨头恰在交换的某个位置，则会跟随杯子移动到另一个位置。一旦骨头掉入洞中，后续交换不再影响它。

请确定最终骨头的位置。

## 样例 #1

### 输入
```
7 3 4
3 4 6
1 2
2 5
5 7
7 1
```

### 输出
```
1
```

## 样例 #2

### 输入
```
5 1 2
2
1 2
2 4
```

### 输出
```
2
```

---

### 算法分类
模拟

---

## 题解综合分析

所有题解均采用模拟思路，核心差异在于状态检查时机和代码优化。关键要点对比：

1. **洞位置标记**：均使用布尔数组或哈希表标记洞位置
2. **位置更新逻辑**：仅在交换位置包含当前骨位时更新
3. **终止条件**：发现骨位处于洞中立即终止后续操作

### 最优思路总结
- **实时状态检查**：在每次交换后立即检查新位置是否为洞（而非仅在下一次交换前）
- **操作短路**：使用 `while(k-- && !fall_into_hole)` 式循环结构
- **初始状态预判**：优先检查初始位置是否含洞

---

## 精选题解（4星）

### 题解作者：Cutler
**星级**：★★★★★  
**亮点**：  
- 循环条件整合状态检查 `while(k-- && !f[cur])`
- 代码简洁度最佳（仅 20 行）
- 使用位标记替代计数器节省空间

**核心代码**：
```cpp
int cur = 1;
while(k--) {
    if(f[cur]) break;      // 先检查当前位置是否在洞中
    scanf("%d%d", &x, &y);
    if(cur == x) cur = y;  // 更新骨位
    else if(cur == y) cur = x;
}
printf("%d\n", cur);
```

---

### 题解作者：happybob
**星级**：★★★★☆  
**亮点**：
- 使用 `while(k-- && !mp[place])` 提前终止无效操作
- 变量命名清晰（`place` 代替 `cur`）
- 无冗余条件判断

**代码片段**：
```cpp
while(k-- && !mp[place]) {
    cin >> x >> y;
    if(place == x) place = y;
    else if(place == y) place = x;
}
```

---

### 题解作者：yxy666
**星级**：★★★★☆  
**亮点**：
- 独立处理初始位置洞检测
- 快读优化大数据输入
- 逻辑分层清晰

**关键实现**：
```cpp
if(vis[1]==1) { printf("1"); return 0; }  // 初始位置特判
for(...) {
    if(sx==x) sx=y;
    else if(sx==y) sx=x;
    if(vis[sx]==1) { ... }               // 交换后立即检查
}
```

---

## 关键技巧提炼

1. **状态驱动流程**：以骨头的实时位置为状态驱动模拟过程
2. **短路优化**：将状态检查整合到循环条件中，避免无效操作
3. **交换对称性**：仅需判断骨位是否等于两个交换位置之一
4. **零移动优化**：不涉及骨位的交换无需任何处理

---

## 同类题目推荐

1. [P1030 乒乓球](https://www.luogu.com.cn/problem/P1030) - 规则模拟
2. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042) - 状态转换模拟
3. [P1563 玩具谜题](https://www.luogu.com.cn/problem/P1563) - 环形位置计算

---

## 心得摘录

> "交换后要立即检查新位置是否在洞里，否则会漏判最后一次移动的结果" —— xiaozeyu  
> "使用快读处理3e5次操作的大输入，否则会TLE" —— Mr_WA的大号  
> "初始位置可能有洞的测试用例需要单独处理" —— cxy000

---
处理用时：67.61秒