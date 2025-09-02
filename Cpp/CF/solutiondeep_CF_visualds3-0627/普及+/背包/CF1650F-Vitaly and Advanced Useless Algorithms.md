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



**唯一算法分类**  
动态规划（背包问题）

---

**综合分析与结论**  
题目核心是多个独立任务的最优选择问题。每个任务需通过 01 背包模型计算最小时间，同时记录路径，要点如下：

1. **算法流程**  
   - **按任务分组**：将选项按任务分组，每个任务独立处理  
   - **背包建模**：对每个任务，以百分比为容量（0~200），时间为价值，构建 01 背包  
   - **路径回溯**：通过记录转移路径，回溯每个任务选择的选项  
   - **时间校验**：累计各任务耗时，验证是否超过对应截止时间  

2. **可视化设计**  
   - **背包填充动画**：以网格展示百分比和时间，动态更新 `dp[j] = min(dp[j], dp[j-p]+t)`  
   - **高亮机制**：  
     - 红色标记当前处理的选项  
     - 绿色标记被更新的背包状态  
   - **路径回溯演示**：从 100% 状态反向追踪，用黄色线条连接被选中的选项  

3. **复古游戏化设计**  
   - **像素风格 UI**：用 8-bit 字体显示背包状态，选项以不同颜色方块表示  
   - **音效反馈**：  
     - `滴`：选项被选中  
     - `叮~`：完成一个任务  
     - `哔--`：超时失败  
   - **自动演示模式**：AI 按任务顺序依次填充背包，显示实时耗时进度条  

---

**题解清单 (≥4星)**  
1. **落海沉（5星）**  
   - **亮点**：使用滚动数组优化空间，路径记录简洁  
   - **关键代码**：  
     ```cpp
     for(int j=rgt; j>=lft; j--){  // 逆序处理选项
         for(int k=200; k; k--){   // 滚动更新背包
             if(k>=e[j].val) dp[j][k] = min(dp[j+1][k-e[j].val]+e[j].ti, dp[j][k]);
         }
     }
     ```

2. **qianqing（4星）**  
   - **亮点**：分离任务处理逻辑，代码结构清晰  
   - **路径追踪**：通过临时数组 `q[v]` 动态维护路径  

3. **E1_de5truct0r（4星）**  
   - **亮点**：哈希优化路径记录空间，处理大数据更稳定  
   - **独特技巧**：  
     ```cpp
     for(int j=200;j>=p;j--){  // 百分比容量上限
         if(dp[j-p]+t < dp[j]) 
             q[j] = q[j-p], q[j].push_back(id); // 路径继承
     }
     ```

---

**最优思路提炼**  
1. **状态压缩**：用百分比（0~200）代替时间作为背包容量  
2. **分层处理**：每个任务独立计算，避免全局状态爆炸  
3. **贪心验证**：按截止时间升序处理任务，累计时间校验  

---

**同类型题推荐**  
1. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)（01 背包基础）  
2. [P1941 飞扬的小鸟](https://www.luogu.com.cn/problem/P1941)（多维背包+路径记录）  
3. [P1156 垃圾陷阱](https://www.luogu.com.cn/problem/P1156)（时间限制型背包）  

---

**个人心得摘录**  
> “卡在路径记录上，发现必须用二维数组存储前驱状态。后来改用 vector 动态维护路径，代码量暴增但终于 AC” —— littlebug  
> “初始化 dp[0]=0 后忘记其他状态置 INF，WA 了 3 次才找到这个低级错误” —— AzurIce  

---

**可视化代码片段（JS 核心逻辑）**  
```javascript
// 背包填充动画
function animateDP(taskId, options) {
  let dp = new Array(201).fill(Infinity);
  dp[0] = 0;
  let path = Array.from({length:201}, ()=>[]);
  
  options.forEach((opt, idx) => {
    highlightOption(opt.id); // 高亮当前选项
    
    for(let j=200; j>=opt.p; j--){ 
      if(dp[j - opt.p] + opt.t < dp[j]) {
        dp[j] = dp[j - opt.p] + opt.t;
        path[j] = [...path[j - opt.p], opt.id]; // 记录路径
        flashCell(j); // 闪烁更新的状态格
      }
    }
  });
  
  return path.slice(100).find(p => dp[p] <= deadline);
}
```

---

**复古像素风格 CSS 示例**  
```css
/* 8-bit 风格背包网格 */
.dp-grid {
  display: grid;
  grid-template-columns: repeat(20, 32px);
  background: #2d2d2d;
  border: 2px solid #8b8b8b;
}

.cell {
  width: 32px;
  height: 32px;
  font: 14px 'Press Start 2P';
  color: #e0e0e0;
  border: 1px solid #4a4a4a;
}

.highlight {
  background: #00ff00 !important;
  animation: blink 0.5s infinite;
}
```

---
处理用时：65.02秒