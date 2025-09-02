# 题目信息

# Vitaly and Advanced Useless Algorithms

## 题目描述

Vitaly enrolled in the course Advanced Useless Algorithms. The course consists of $ n $ tasks. Vitaly calculated that he has $ a_i $ hours to do the task $ i $ from the day he enrolled in the course. That is, the deadline before the $ i $ -th task is $ a_i $ hours. The array $ a $ is sorted in ascending order, in other words, the job numbers correspond to the order in which the assignments are turned in.

Vitaly does everything conscientiously, so he wants to complete each task by $ 100 $ percent, or more. Initially, his completion rate for each task is $ 0 $ percent.

Vitaly has $ m $ training options, each option can be used not more than once. The $ i $ th option is characterized by three integers: $ e_i, t_i $ and $ p_i $ . If Vitaly uses the $ i $ th option, then after $ t_i $ hours (from the current moment) he will increase the progress of the task $ e_i $ by $ p_i $ percent.

For example, let Vitaly have $ 3 $ of tasks to complete. Let the array $ a $ have the form: $ a = [5, 7, 8] $ . Suppose Vitaly has $ 5 $ of options: $ [e_1=1, t_1=1, p_1=30] $ , $ [e_2=2, t_2=3, p_2=50] $ , $ [e_3=2, t_3=3, p_3=100] $ , $ [e_4=1, t_4=1, p_4=80] $ , $ [e_5=3, t_5=3, p_5=100] $ .

Then, if Vitaly prepares in the following way, he will be able to complete everything in time:

- Vitaly chooses the $ 4 $ -th option. Then in $ 1 $ hour, he will complete the $ 1 $ -st task at $ 80 $ percent. He still has $ 4 $ hours left before the deadline for the $ 1 $ -st task.
- Vitaly chooses the $ 3 $ -rd option. Then in $ 3 $ hours, he will complete the $ 2 $ -nd task in its entirety. He has another $ 1 $ hour left before the deadline for the $ 1 $ -st task and $ 4 $ hours left before the deadline for the $ 3 $ -rd task.
- Vitaly chooses the $ 1 $ -st option. Then after $ 1 $ hour, he will complete the $ 1 $ -st task for $ 110 $ percent, which means that he will complete the $ 1 $ -st task just in time for the deadline.
- Vitaly chooses the $ 5 $ -th option. He will complete the $ 3 $ -rd task for $ 2 $ hours, and after another $ 1 $ hour, Vitaly will complete the $ 3 $ -rd task in its entirety.

Thus, Vitaly has managed to complete the course completely and on time, using the $ 4 $ options.

Help Vitaly — print the options for Vitaly to complete the tasks in the correct order. Please note: each option can be used not more than once. If there are several possible answers, it is allowed to output any of them.

## 样例 #1

### 输入

```
5
3 5
5 7 8
1 1 30
2 3 50
2 3 100
1 1 80
3 3 100
1 5
51
1 36 91
1 8 40
1 42 83
1 3 45
1 13 40
2 9
9 20
2 8 64
2 7 64
1 20 56
2 8 76
2 20 48
1 2 89
1 3 38
2 18 66
1 7 51
3 2
7 18 33
1 5 80
3 4 37
2 5
569452312 703565975
1 928391659 66
1 915310 82
2 87017081 92
1 415310 54
2 567745964 82```

### 输出

```
4
1 4 3 5 
3
2 4 5 
4
6 7 1 2 
-1
4
2 4 3 5```

## 样例 #2

### 输入

```
3
3 9
20 31 40
1 9 64
3 17 100
3 9 59
3 18 57
3 20 49
2 20 82
2 14 95
1 8 75
2 16 67
2 6
20 36
2 2 66
2 20 93
1 3 46
1 10 64
2 8 49
2 18 40
1 1
1000000000
1 1000000000 100```

### 输出

```
-1
4
3 4 1 5 
1
1```

# AI分析结果



0. **题目翻译**  

# Vitaly 与高级无用算法

## 题目描述

Vitaly 报名了名为"高级无用算法"的课程。该课程包含 $n$ 个任务，Vitaly 计算出从报名当天起，完成第 $i$ 个任务有 $a_i$ 小时的时间（即第 $i$ 个任务的截止时间为 $a_i$ 小时）。数组 $a$ 按升序排列，任务编号对应提交顺序。

Vitaly 做事认真，希望每个任务完成度达到 100% 或更高。每个任务的初始进度为 0%。

Vitaly 有 $m$ 个训练选项，每个选项最多使用一次。第 $i$ 个选项由三个整数描述：$e_i$（任务编号）、$t_i$（耗时）和 $p_i$（进度增加百分比）。使用该选项后，经过 $t_i$ 小时，任务 $e_i$ 的进度将增加 $p_i$%。

请帮助 Vitaly 找到能在截止时间前完成所有任务的选项使用顺序，若存在多个解输出任意一个，无解输出 -1。

---

1. **唯一算法分类**  
0-1背包

---

2. **综合分析与结论**  
### 核心思路
- **分组背包模型**：将每个任务的训练选项分组，独立处理每个任务的 0-1 背包问题
- **逆向容量设计**：以百分比为背包容量（范围 0~199），时间为价值，求达到 100% 的最小时间
- **路径回溯**：使用辅助数组记录状态转移路径，最终反向推导出选择的训练选项

### 关键状态转移
对每个任务 $e$ 的选项集合，转移方程为：  
$$ dp[j][k] = \min(dp[j+1][k],\ dp[j+1][k-p] + t) $$  
其中 $j$ 表示选项索引，$k$ 表示当前进度百分比，$p$ 和 $t$ 为选项的百分比增量与耗时

### 可视化设计要点
- **像素风格 DP 矩阵**：用 16x16 像素块表示状态，红色表示未达阈值，绿色表示可行解
- **音效触发机制**：
  - "叮"声：状态被更新时
  - "噔"声：达成 100% 进度时
  - 8-bit 背景音乐循环播放
- **自动演示模式**：按任务顺序逐步展开背包过程，每个选项选择时高亮对应行与百分比列

---

3. **题解清单 (≥4星)**  
1. **落海沉（5星）**
   - ✅ 创新性使用分组背包处理多任务
   - ✅ 路径回溯实现简洁高效
   - ✅ 时间复杂度严格控制在 $O(m \times 200)$

2. **qianqing（4星）**
   - ✅ 清晰的状态转移方程注释
   - ✅ 使用滚动数组优化空间
   - ⚠️ 变量命名可读性待提升

3. **OIer_ACMer（4星）**
   - ✅ 完整处理 200% 冗余容量的边界情况
   - ✅ 采用哈希优化路径存储
   - ⚠️ 初始化逻辑存在潜在 BUG

---

4. **最优思路与代码实现**  
### 核心代码片段（落海沉题解）
```cpp
// 分组处理每个任务的背包
for(int i=1; i<=n; i++) {
    // 获取当前任务的所有选项
    int lft = 1, rgt = 分组结束位置;
    
    // 倒序处理选项（经典 0-1 背包写法）
    for(int j=rgt; j>=lft; j--) {
        for(int k=200; k>=e[j].val; k--) {
            dp[j][k] = min(dp[j+1][k-e[j].val] + e[j].ti, dp[j][k]);
        }
    }
    
    // 找出最优解（100%~200%）
    int min_time = *min_element(dp[lft]+100, dp[lft]+200);
    
    // 路径回溯
    while(w > 0) {
        if(当前选项被选中) 记录选项编号;
    }
}
```

---

5. **同类型题目推荐**  
1. [P1060] 开心的金明 - 基础 0-1 背包
2. [P1776] 宝物筛选 - 多重背包进阶
3. [P1941] 飞扬的小鸟 - 背包模型变形

---

6. **调试心得摘录**  
- **路径记录陷阱**：多个选项可能产生相同耗时，需严格比较转移来源
- **初始化惨案**：未将 dp[0][0] 初始化为 0 导致全盘错误
- **时间累加玄学**：每个任务剩余时间需要累加到下个任务的可用时间中

---

7. **像素化 DP 可视化示例**  
```javascript
// 使用 Canvas 绘制背包状态（伪代码）
function drawDP() {
  ctx.fillStyle = '#2D2D2D'; // 复古深灰背景
  ctx.fillRect(0, 0, canvas.width, canvas.height);

  for(let p=0; p<=200; p+=5) { // 每5%一个像素块
    const color = dp[p] <= limit ? '#7CFC00' : '#FF4500';
    ctx.fillStyle = color;
    ctx.fillRect(p*4 % 320, Math.floor(p/80)*4, 3, 3);
  }
  
  // 播放音效
  if(updated) playSound('blip.wav');
  if(reached100) playSound('success.wav');
}
```

---
处理用时：66.59秒