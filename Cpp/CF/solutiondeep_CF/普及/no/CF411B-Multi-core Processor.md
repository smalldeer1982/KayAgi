# 题目信息

# Multi-core Processor

## 题目描述

The research center Q has developed a new multi-core processor. The processor consists of $ n $ cores and has $ k $ cells of cache memory. Consider the work of this processor.

At each cycle each core of the processor gets one instruction: either do nothing, or the number of the memory cell (the core will write an information to the cell). After receiving the command, the core executes it immediately. Sometimes it happens that at one cycle, multiple cores try to write the information into a single cell. Unfortunately, the developers did not foresee the possibility of resolving conflicts between cores, so in this case there is a deadlock: all these cores and the corresponding memory cell are locked forever. Each of the locked cores ignores all further commands, and no core in the future will be able to record an information into the locked cell. If any of the cores tries to write an information into some locked cell, it is immediately locked.

The development team wants to explore the deadlock situation. Therefore, they need a program that will simulate the processor for a given set of instructions for each core within $ m $ cycles . You're lucky, this interesting work is entrusted to you. According to the instructions, during the $ m $ cycles define for each core the number of the cycle, during which it will become locked. It is believed that initially all cores and all memory cells are not locked.

## 样例 #1

### 输入

```
4 3 5
1 0 0
1 0 2
2 3 1
3 2 0
```

### 输出

```
1
1
3
0
```

## 样例 #2

### 输入

```
3 2 2
1 2
1 2
2 2
```

### 输出

```
1
1
0
```

## 样例 #3

### 输入

```
1 1 1
0
```

### 输出

```
0
```

# AI分析结果



# 多核处理器

## 题目描述

研究机构 Q 开发了一款新型多核处理器。该处理器包含 $n$ 个核心和 $k$ 个缓存单元。处理器的工作流程如下：

每个周期中，每个核心会接收一条指令：要么无操作，要么指定要写入的缓存单元编号（核心将向该单元写入信息）。核心收到指令后立即执行。若同一周期内有多个核心尝试写入同一缓存单元，则发生死锁：这些核心及对应缓存单元将永久锁定。被锁定的核心会忽略后续所有指令，被锁定的缓存单元无法再被写入。若未被锁定的核心尝试写入已锁定的缓存单元，该核心将立即被锁定。

现需要模拟处理器在 $m$ 个周期内的运行情况，确定每个核心被锁定的周期编号（若未被锁定则记为 0）。

## 样例 #1

### 输入

```
4 3 5
1 0 0
1 0 2
2 3 1
3 2 0
```

### 输出

```
1
1
3
0
```

## 样例 #2

### 输入

```
3 2 2
1 2
1 2
2 2
```

### 输出

```
1
1
0
```

## 样例 #3

### 输入

```
1 1 1
0
```

### 输出

```
0
```

---

### 算法分类
模拟

---

## 题解综合分析

所有题解均采用**分步模拟**策略，核心思路为：
1. 按时间步处理每个周期
2. 每个周期分两阶段处理：
   - 阶段一：处理向已锁定单元发送指令的情况
   - 阶段二：统计当前周期冲突并处理新锁定
3. 使用两个数组分别记录处理器和缓存单元的锁定状态

### 精选题解

#### 题解1：Cure_Wing（4星）
**亮点**：  
- 使用`c1[]`记录处理器锁定时间，`c2[]`记录缓存单元锁定时间  
- 分两次遍历：首次处理已锁定单元情况，二次处理冲突  
- 代码结构清晰，变量命名规范  

**核心代码**：
```cpp
for(int i=1;i<=m;++i){
    memset(vis,0,sizeof(vis));
    // 第一阶段：检查已锁定单元
    for(int j=1;j<=n;++j){
        if(c1[j]||!a[j][i]) continue;
        if(c2[a[j][i]]) c1[j]=i; 
        else ++vis[a[j][i]];
    }
    // 第二阶段：处理新冲突
    for(int j=1;j<=n;++j){
        if(c1[j]) continue;
        if(vis[a[j][i]]>1) 
            c1[j]=c2[a[j][i]]=i;
    }
}
```

#### 题解2：maomao233（4星）
**亮点**：  
- 使用`f[]`标记锁定单元，`ans[]`记录结果  
- 先统计冲突数量再处理，逻辑层次分明  
- 代码简洁，逻辑紧凑  

**核心代码**：
```cpp
for(int i=1;i<=m;i++){
    memset(cnt,0,sizeof(cnt));
    // 统计当前周期访问情况
    for(int j=1;j<=n;j++)
        if(!ans[j]) cnt[a[j][i]]++;
    // 处理多核冲突
    for(int j=1;j<=k;j++)
        if(cnt[j]>=2){
            f[j]=1;
            for(int l=1;l<=n;l++)
                if(!ans[l] && a[l][i]==j)
                    ans[l]=i;
        }
    // 处理访问锁定单元
    for(int j=1;j<=n;j++)
        if(!ans[j] && f[a[j][i]])
            ans[j]=i;
}
```

---

### 关键思路总结
1. **分阶段处理**：先处理已锁定单元的影响，再统计新冲突，避免状态更新干扰判断  
2. **状态记录**：使用独立数组分别维护处理器和缓存单元的锁定状态  
3. **时间步遍历**：按周期逐个处理，保持时间维度上的顺序性  

---

### 拓展建议
类似问题可考虑：
1. 状态更新顺序对结果的影响（如先处理已锁定单元）
2. 多条件判断的优先级设计
3. 高效状态标记方法（如位运算优化）

---

### 推荐练习题
1. [P1063 能量项链](https://www.luogu.com.cn/problem/P1063) - 环形结构模拟  
2. [P1540 机器翻译](https://www.luogu.com.cn/problem/P1540) - 队列模拟缓存替换  
3. [P1152 欢乐的跳](https://www.luogu.com.cn/problem/P1152) - 数组状态标记技巧

---
处理用时：61.30秒