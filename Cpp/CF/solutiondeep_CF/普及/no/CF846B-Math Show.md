# 题目信息

# Math Show

## 题目描述

Polycarp takes part in a math show. He is given $ n $ tasks, each consists of $ k $ subtasks, numbered $ 1 $ through $ k $ . It takes him $ t_{j} $ minutes to solve the $ j $ -th subtask of any task. Thus, time required to solve a subtask depends only on its index, but not on the task itself. Polycarp can solve subtasks in any order.

By solving subtask of arbitrary problem he earns one point. Thus, the number of points for task is equal to the number of solved subtasks in it. Moreover, if Polycarp completely solves the task (solves all $ k $ of its subtasks), he recieves one extra point. Thus, total number of points he recieves for the complete solution of the task is $ k+1 $ .

Polycarp has $ M $ minutes of time. What is the maximum number of points he can earn?

## 说明/提示

In the first example Polycarp can complete the first task and spend $ 1+2+3+4=10 $ minutes. He also has the time to solve one subtask of the second task in one minute.

In the second example Polycarp can solve the first subtask of all five tasks and spend $ 5·1=5 $ minutes. Also he can solve the second subtasks of two tasks and spend $ 2·2=4 $ minutes. Thus, he earns $ 5+2=7 $ points in total.

## 样例 #1

### 输入

```
3 4 11
1 2 3 4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5 5 10
1 2 4 8 16
```

### 输出

```
7
```

# AI分析结果



# 中文题目重写

## 题目描述

Polycarp 参加了一个数学节目。他需要解决 $n$ 个任务，每个任务包含 $k$ 个子任务。解决任意任务中第 $j$ 个子任务需要 $t_j$ 分钟。每个子任务得 1 分，若完整解决一个任务（完成所有 $k$ 个子任务）可额外获得 1 分。Polycarp 有 $M$ 分钟时间，求他能获得的最大分数。

## 输入格式

第一行包含三个整数 $n$, $k$, $M$  
第二行包含 $k$ 个整数 $t_1, t_2, ..., t_k$

## 输出格式

输出最大得分

## 样例

### 样例输入 1
3 4 11  
1 2 3 4

### 样例输出 1
6

### 样例输入 2
5 5 10  
1 2 4 8 16

### 样例输出 2
7

---

**算法分类**：贪心

---

### 题解综合分析

各题解核心思路均为：
1. 枚举完成完整任务的数量 $i$
2. 计算剩余时间用于处理未完成任务的最优子任务组合
3. 对子任务时间排序后贪心选取

**关键优化点**：
- 通过数学计算代替逐次累加（如 Walrus 题解）
- 及时终止无效循环（所有题解均实现）

---

### 精选题解

#### 1. 作者：Walrus（5星）
**亮点**：
- 时间复杂度优化至 $O(nk)$
- 数学计算剩余时间可完成的子任务数
- 代码结构简洁清晰

**核心代码**：
```cpp
for(int T = 0; T <= n; T++) {
    int sum = m - T * cnt; // 剩余时间
    if(sum < 0) break;
    
    int now = (k+1)*T; // 基础得分
    for(int j=1; j<=k; j++){ // 遍历每个子任务类型
        int max_num = (n-T); // 可处理的任务数
        if(sum >= t[j]*max_num){
            now += max_num;
            sum -= t[j]*max_num;
        }else{
            now += sum / t[j];
            break; // 时间不足时及时退出
        }
    }
    ans = max(ans, now);
}
```

#### 2. 作者：naroto2022（4星）
**亮点**：
- 双重循环实现直观易懂
- 完整处理所有子任务类型

**个人心得**：
> "注意完成完整任务后要及时计算剩余时间，这是本题的关键步骤"

---

### 最优技巧总结

**贪心策略**：
1. 优先处理耗时少的子任务
2. 对于每个可能的完整任务数 $i$，数学计算剩余时间的最大利用率

**实现技巧**：
- 预处理子任务时间排序
- 使用整除运算快速计算可完成次数

---

### 拓展练习
1. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)（贪心选择策略）
2. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)（价值密度排序）
3. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)（双指针贪心）

---
处理用时：87.79秒