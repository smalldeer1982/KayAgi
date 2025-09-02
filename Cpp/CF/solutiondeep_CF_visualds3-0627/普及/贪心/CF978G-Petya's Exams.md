# 题目信息

# Petya's Exams

## 题目描述

Petya studies at university. The current academic year finishes with $ n $ special days. Petya needs to pass $ m $ exams in those special days. The special days in this problem are numbered from $ 1 $ to $ n $ .

There are three values about each exam:

- $ s_i $ — the day, when questions for the $ i $ -th exam will be published,
- $ d_i $ — the day of the $ i $ -th exam ( $ s_i < d_i $ ),
- $ c_i $ — number of days Petya needs to prepare for the $ i $ -th exam. For the $ i $ -th exam Petya should prepare in days between $ s_i $ and $ d_i-1 $ , inclusive.

There are three types of activities for Petya in each day: to spend a day doing nothing (taking a rest), to spend a day passing exactly one exam or to spend a day preparing for exactly one exam. So he can't pass/prepare for multiple exams in a day. He can't mix his activities in a day. If he is preparing for the $ i $ -th exam in day $ j $ , then $ s_i \le j < d_i $ .

It is allowed to have breaks in a preparation to an exam and to alternate preparations for different exams in consecutive days. So preparation for an exam is not required to be done in consecutive days.

Find the schedule for Petya to prepare for all exams and pass them, or report that it is impossible.

## 说明/提示

In the first example Petya can, for example, prepare for exam $ 1 $ in the first day, prepare for exam $ 2 $ in the second day, pass exam $ 1 $ in the third day, relax in the fourth day, and pass exam $ 2 $ in the fifth day. So, he can prepare and pass all exams.

In the second example, there are three days and two exams. So, Petya can prepare in only one day (because in two other days he should pass exams). Then Petya can not prepare and pass all exams.

## 样例 #1

### 输入

```
5 2
1 3 1
1 5 1
```

### 输出

```
1 2 3 0 3 
```

## 样例 #2

### 输入

```
3 2
1 3 1
1 2 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
10 3
4 7 2
1 10 3
8 9 1
```

### 输出

```
2 2 2 1 1 0 4 3 4 4 
```

# AI分析结果



## 综合分析与结论

### 题目核心与难点
题目要求合理安排考试复习时间，核心难点在于**贪心策略的设计**：如何在有限时间内优先保证所有考试有充足复习时间。关键在于证明贪心选择的有效性（先处理早截止的考试）并处理多考试时间窗口重叠的情况。

### 贪心策略要点
1. **按考试时间排序**：优先处理截止时间早的考试（按d_i升序），确保紧迫任务优先安排。
2. **尽早安排复习**：从s_i到d_i-1尽可能填充空闲天，避免后续考试占用其窗口。
3. **冲突处理**：若某考试无法满足复习天数，直接判定无解。

### 题解对比与评分
#### 评分≥4星的题解
| 作者 | 评分 | 核心亮点 |
|------|-----|---------|
| 风中の菜鸡 | ★★★★☆ | 代码简洁，注释明确，正确实现贪心策略 |
| fls233666 | ★★★★☆ | 结构清晰，排序后按序填充，逻辑严谨 |
| kimidonatsu | ★★★★☆ | 详细注释，可读性强，包含完整题解结构 |

### 最优思路提炼
1. **排序策略**：考试按d_i升序排序，确保先处理紧迫任务。
2. **填充分配**：对每个考试，从s_i到d_i-1遍历，优先占用最早可用天。
3. **冲突检测**：若某考试复习天数不足，立即终止程序。

```cpp
// 核心代码示例（fls233666题解）
sort(e+1, e+m+1, cmp); // 按d_i排序
for (int i=1; i<=m; i++) {
    int cnt = 0;
    for (int j=e[i].s; j<e[i].d; j++) {
        if (plan[j] == 0) {
            plan[j] = e[i].id;
            if (++cnt == e[i].c) break;
        }
    }
    if (cnt < e[i].c) return -1;
}
```

### 同类题目与算法套路
- **区间调度问题**：优先选择结束早的任务（如活动选择问题）。
- **资源分配问题**：在限制条件下最大化资源利用率（如P1230智力大冲浪）。
- **任务安排问题**：带截止时间和惩罚的任务调度（如CF/洛谷类似题目）。

### 推荐题目
1. [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)  
2. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)  
3. [CF1132F Clear the String](https://codeforces.com/problemset/problem/1132/F)

### 个人心得摘录
- **「风中の菜鸡」**：贪心策略需严格排序，考试序号需保存以免排序后丢失。
- **「玉环小姐姐」**：多关键字排序确保处理顺序正确，避免遗漏边界情况。

---

## 可视化与算法演示设计

### 动画方案
1. **像素风格展示**：用不同颜色块表示每天状态（复习、考试、休息）。
2. **步进执行**：高亮当前处理的考试和遍历的天数，实时显示复习进度。
3. **冲突提示**：当天数不足时，闪烁红色警告并终止动画。

### 交互设计
- **控制面板**：播放/暂停、步进、重置、速度调节。
- **音效反馈**：成功填充复习天（清脆音效），冲突（低沉音效），考试日（钟声）。

### 复古游戏化设计
- **8位像素UI**：考试图标为书本，复习天数为进度条，背景音乐循环。
- **积分系统**：每安排成功一考试+100分，连续成功触发连击加成。
- **自动演示模式**：AI按最优策略自动填充，展示贪心过程。

---

## 可视化代码片段（Canvas示例）

```javascript
// 初始化Canvas网格
function drawGrid() {
    ctx.fillStyle = "#000000";
    for (let day = 1; day <= n; day++) {
        const x = (day-1) * 32;
        if (plan[day] === m+1) { // 考试日
            ctx.fillStyle = "#FF0000";
            ctx.fillRect(x, 0, 30, 30);
        } else if (plan[day] > 0) { // 复习日
            ctx.fillStyle = "#00FF00";
            ctx.fillRect(x, 0, 30, 30);
        } else { // 休息日
            ctx.fillStyle = "#CCCCCC";
            ctx.fillRect(x, 0, 30, 30);
        }
    }
}
```

---
处理用时：78.78秒