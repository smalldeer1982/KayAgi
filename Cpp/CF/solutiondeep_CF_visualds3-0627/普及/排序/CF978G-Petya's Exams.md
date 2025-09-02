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



---

## 唯一算法分类
**贪心算法**

---

## 综合分析与结论

### 核心思路与算法流程
题目核心是**贪心策略**：按考试时间（d_i）排序，优先处理考试时间早的考试。每个考试在其公布时间（s_i）到考试前一天（d_i-1）的区间内，尽可能早地安排复习天数。若无法满足复习天数则无解。核心步骤如下：
1. **预处理考试日**：将考试日标记为特殊值（如 m+1）。
2. **按考试时间排序**：确保优先处理更紧迫的考试。
3. **贪心填充复习天数**：从 s_i 开始遍历至 d_i-1，优先占用未被安排的天数。
4. **冲突检测**：若某考试无法分配足够复习天数，直接输出 -1。

### 解决难点
- **时间窗口限制**：每场考试的复习只能在特定区间内进行，需合理分配避免冲突。
- **贪心策略证明**：若优先安排早考试失败，则其他顺序也无法满足，反证法可证其正确性。

### 可视化设计
1. **网格布局**：用 Canvas 绘制 n 天的网格，每天显示不同状态（考试红、复习蓝、休息绿）。
2. **高亮当前操作**：处理某考试时，高亮其 s_i 到 d_i 区间；填充复习天时，闪烁目标单元格。
3. **音效反馈**：复习成功时播放清脆音效，失败时低沉音效，考试日触发特殊音效。
4. **复古像素风**：使用 8-bit 风格颜色，网格边界用深色像素线，动画步进速度可调。
5. **自动演示模式**：按天逐步执行算法，用户可暂停/加速，观察填充逻辑。

---

## 题解清单（评分≥4星）

### 1. 风中の菜鸡（⭐️⭐️⭐️⭐️）
- **亮点**：代码简洁，预处理考试日巧妙，变量命名直观。
- **核心逻辑**：按 d_i 排序后暴力填充空闲天，逻辑清晰易实现。
- **代码片段**：
  ```cpp
  for(int i=1;i<=m;i++){
      num=0;
      for(int j=exam[i].promulgate;j<exam[i].start;j++){
          if(num==exam[i].review) break;
          if(jh[j]==-1) jh[j]=exam[i].place, num++;
      }
      if(num<exam[i].review){ cout<<"-1"; return 0; }
  }
  ```

### 2. fls233666（⭐️⭐️⭐️⭐️⭐️）
- **亮点**：结构体命名规范，排序逻辑明确，代码可读性极佳。
- **核心逻辑**：预处理考试日后直接填充，循环内及时 break 优化效率。
- **代码片段**：
  ```cpp
  sort(e+1,e+1+m,cmp);
  for(rgt i=1;i<=m;i++){
      for(rgt j=e[i].si;j<e[i].di;j++){
          if(!plan[j]) plan[j]=e[i].id, e[i].ci--;
          if(!e[i].ci) break;
      }
      if(e[i].ci){ printf("-1"); return 0; }
  }
  ```

### 3. kimidonatsu（⭐️⭐️⭐️⭐️）
- **亮点**：详细注释与题解分析，适合教学，变量命名专业。
- **核心逻辑**：使用稳定排序，处理可能的边界情况，代码稳健。
- **代码片段**：
  ```cpp
  stable_sort(exams + 1, exams + m + 1, cmp);
  for(re int i=1;i<=m;i++){
      for(re int j=exams[i].s; j<exams[i].d; j++){
          if(!ans[j]) ans[j]=exams[i].id, exams[i].c--;
          if(!exams[i].c) break;
      }
      if(exams[i].c){ printf("-1\n"); exit(0); }
  }
  ```

---

## 最优思路与技巧提炼
1. **贪心排序**：按考试时间（d_i）升序排序，确保早考试优先占用时间资源。
2. **时间窗口填充**：从 s_i 到 d_i-1 顺序填充，最大化利用早期空闲天。
3. **冲突即时检测**：在填充过程中直接判断是否满足条件，提前终止无解情况。
4. **状态预处理**：预先标记考试日，避免后续逻辑冲突。

---

## 类似题目推荐
1. **P1230 智力大冲浪**（贪心 + 时间窗口分配）
2. **P1090 合并果子**（贪心 + 优先队列）
3. **P5019 铺设道路**（贪心模拟区间覆盖）

---

## 个人心得摘录
- **玉环小姐姐**提到冒泡排序实现多关键字排序，虽效率低但易理解，适合小数据量。
- **codeLJH114514**尝试用 `set` 动态维护最近考试，虽增加复杂度但提供不同视角。

---

## 可视化与算法演示（核心代码逻辑）

### 关键变量与操作
- **高亮区间**：当前处理的考试 s_i 到 d_i 用黄色边框标记。
- **填充动画**：遍历天时，空闲天变为蓝色并显示考试编号，已占天跳过。
- **冲突提示**：复习天数不足时，整个区间闪烁红色并播放失败音效。

### 代码片段（伪代码）
```javascript
// 初始化 Canvas 和音效
const canvas = initCanvas();
const sound = { fill: loadSound('blip.wav'), error: loadSound('error.wav') };

// 主循环
for (let exam of sortedExams) {
    highlightInterval(exam.s, exam.d); // 高亮当前考试区间
    let daysNeeded = exam.c;
    for (let day = exam.s; day < exam.d; day++) {
        if (grid[day] === EMPTY) {
            grid[day] = exam.id; // 填充复习天
            drawDay(day, COLOR_BLUE, exam.id);
            sound.fill.play();
            daysNeeded--;
            if (daysNeeded === 0) break;
        }
    }
    if (daysNeeded > 0) {
        flashInterval(exam.s, exam.d, COLOR_RED); // 闪烁红色
        sound.error.play();
        showMessage('-1');
        return;
    }
}
```

### 复古风格设计
- **调色板**：使用 8-bit 风格（#FF0000红、#0000FF蓝、#00FF00绿、#FFFF00黄）。
- **网格绘制**：每个天用 32x32 像素块，边框 2px，数字用 8px 像素字体。
- **音效**：使用 Chipbit 音效库生成 8-bit 音效，填充时短促“哔”声，错误时长“嗡”声。

---
处理用时：92.87秒