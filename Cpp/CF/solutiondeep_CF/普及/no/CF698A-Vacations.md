# 题目信息

# Vacations

## 题目描述

Vasya has $ n $ days of vacations! So he decided to improve his IT skills and do sport. Vasya knows the following information about each of this $ n $ days: whether that gym opened and whether a contest was carried out in the Internet on that day. For the $ i $ -th day there are four options:

1. on this day the gym is closed and the contest is not carried out;
2. on this day the gym is closed and the contest is carried out;
3. on this day the gym is open and the contest is not carried out;
4. on this day the gym is open and the contest is carried out.

On each of days Vasya can either have a rest or write the contest (if it is carried out on this day), or do sport (if the gym is open on this day).

Find the minimum number of days on which Vasya will have a rest (it means, he will not do sport and write the contest at the same time). The only limitation that Vasya has — he does not want to do the same activity on two consecutive days: it means, he will not do sport on two consecutive days, and write the contest on two consecutive days.

## 说明/提示

In the first test Vasya can write the contest on the day number 1 and do sport on the day number 3. Thus, he will have a rest for only 2 days.

In the second test Vasya should write contests on days number 1, 3, 5 and 7, in other days do sport. Thus, he will not have a rest for a single day.

In the third test Vasya can do sport either on a day number 1 or number 2. He can not do sport in two days, because it will be contrary to the his limitation. Thus, he will have a rest for only one day.

## 样例 #1

### 输入

```
4
1 3 2 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
1 3 3 2 1 2 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2
2 2
```

### 输出

```
1
```

# AI分析结果



# Vacations

## 题目描述

Vasya 有 $n$ 天假期！他决定提升 IT 技能和锻炼身体。Vasya 知道这 $n$ 天中每天的两个状态：健身房是否开放、是否有在线比赛。对于第 $i$ 天有四种可能：

1. 健身房关闭且无比赛  
2. 健身房关闭但有比赛  
3. 健身房开放但无比赛  
4. 健身房开放且有比赛  

每天 Vasya 可以选择休息、参加比赛（若当天有）或健身（若健身房开放）。求他休息的最少天数，约束条件是不能连续两天进行相同活动。

## 说明/提示

样例1：选择第1天比赛，第3天健身，休息2天  
样例2：交替安排活动实现0休息  
样例3：两天只能安排一次健身，休息1天  

**算法分类**  
动态规划

---

## 题解分析与结论

### 综合题解对比
所有题解均采用动态规划，主要差异在状态定义和转移方程：
- **状态维度**：主流使用三维状态（休息/比赛/健身）
- **转移逻辑**：根据当天活动可能性，从前一日非冲突状态转移
- **逆向思维**：tZERO 题解通过计算最大活动天数间接求最小休息天数

### 高星题解推荐

#### 1. SqrtSecond（五星）
**核心思路**  
- 状态定义：`dp[i][j]` 表示第i天进行j类活动（0休息/1比赛/2健身）时的最小休息天数  
- 转移方程：  
  ```cpp
  dp[i][0] = min(前一日所有状态) + 1  // 当天必须休息
  dp[i][1] = min(前一日非比赛状态)   // 仅当有比赛时更新
  dp[i][2] = min(前一日非健身状态)   // 仅当健身房开放时更新
  ```
**代码亮点**  
```cpp
memset(dp,127,sizeof(dp)); // 初始化为极大值
dp[0][0] = dp[0][1] = dp[0][2] = 0; // 边界条件
for(int i=1; i<=n; i++){
    dp[i][0] = min({dp[i-1][0], dp[i-1][1], dp[i-1][2]}) +1;
    if(a[i]&1) dp[i][1] = min(dp[i-1][0], dp[i-1][2]); 
    if(a[i]&2) dp[i][2] = min(dp[i-1][0], dp[i-1][1]);
}
```
**评分理由**：状态定义清晰，转移方程简洁高效，代码可读性极佳。

#### 2. ZXXS（四星）
**核心思路**  
与 SqrtSecond 方案类似，但增加详细注释和初始化说明，适合新手理解。  
**关键代码**：  
```cpp
if(a[i]==1||a[i]==3) dp[i][1] = ... // 显式条件判断
```
**评分理由**：详尽的代码注释，对边界条件和转移逻辑进行详细说明。

#### 3. happybob（四星）
**代码亮点**  
使用位运算判断活动可行性：
```cpp
if (a[i]&1) ...  // 比赛位检查
if (a[i]&2) ...  // 健身位检查
```
**评分理由**：代码简洁，使用位运算提升可读性。

---

## 最优思路总结
**关键技巧**  
1. **状态压缩**：用三位二进制数表示每日活动可能性（比赛=1，健身=2）  
2. **滚动更新**：只需维护前一日的状态即可计算当日  
3. **贪心思维**：在可选活动时优先选择与前日不同的活动  

**类似题目推荐**  
1. [P1359 租用游艇](https://www.luogu.com.cn/problem/P1359)  
2. [P1216 数字三角形](https://www.luogu.com.cn/problem/P1216)  
3. [P1434 滑雪](https://www.luogu.com.cn/problem/P1434)  

**调试经验**  
- 注意初始状态设置为0而非无穷大  
- 当活动可选时，需同时考虑"选择活动"和"主动休息"两种可能性  
- 测试用例要覆盖连续相同活动不可行的场景

---
处理用时：71.08秒