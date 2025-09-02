# 题目信息

# Traps

## 题目描述

There are $ n $ traps numbered from $ 1 $ to $ n $ . You will go through them one by one in order. The $ i $ -th trap deals $ a_i $ base damage to you.

Instead of going through a trap, you can jump it over. You can jump over no more than $ k $ traps. If you jump over a trap, it does not deal any damage to you. But there is an additional rule: if you jump over a trap, all next traps damages increase by $ 1 $ (this is a bonus damage).

Note that if you jump over a trap, you don't get any damage (neither base damage nor bonus damage). Also, the bonus damage stacks so, for example, if you go through a trap $ i $ with base damage $ a_i $ , and you have already jumped over $ 3 $ traps, you get $ (a_i + 3) $ damage.

You have to find the minimal damage that it is possible to get if you are allowed to jump over no more than $ k $ traps.

## 说明/提示

In the first test case it is allowed to jump over all traps and take $ 0 $ damage.

In the second test case there are $ 5 $ ways to jump over some traps:

1. Do not jump over any trap.Total damage: $ 5 + 10 + 11 + 5 = 31 $ .
2. Jump over the $ 1 $ -st trap.Total damage: $ \underline{0} + (10 + 1) + (11 + 1) + (5 + 1) = 29 $ .
3. Jump over the $ 2 $ -nd trap.Total damage: $ 5 + \underline{0} + (11 + 1) + (5 + 1) = 23 $ .
4. Jump over the $ 3 $ -rd trap.Total damage: $ 5 + 10 + \underline{0} + (5 + 1) = 21 $ .
5. Jump over the $ 4 $ -th trap.Total damage: $ 5 + 10 + 11 + \underline{0} = 26 $ .

To get minimal damage it is needed to jump over the $ 3 $ -rd trap, so the answer is $ 21 $ .

In the third test case it is optimal to jump over the traps $ 1 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 7 $ :

Total damage: $ 0 + (2 + 1) + 0 + 0 + 0 + (2 + 4) + 0 = 9 $ .

## 样例 #1

### 输入

```
5
4 4
8 7 1 4
4 1
5 10 11 5
7 5
8 2 5 15 11 2 8
6 3
1 2 3 4 5 6
1 1
7```

### 输出

```
0
21
9
6
0```

# AI分析结果



### 中文重写题目
#### 题目名称：陷阱

**题目描述**  
有编号从 1 到 n 的 n 个陷阱，你需要按顺序依次通过。第 i 个陷阱的基础伤害为 a_i。  

你可以选择跳过最多 k 个陷阱。跳过某个陷阱时，该陷阱不造成任何伤害，但此后所有未被跳过的陷阱伤害值增加 1 点（该效果叠加）。例如，若已跳过 3 个陷阱，则后续每个未被跳过的陷阱会受到 (a_i +3) 点伤害。  

求通过所有陷阱后可能受到的最小总伤害。

**输入格式**  
- 多组测试数据，第一行为测试次数 t  
- 每组数据：  
  - 第一行两个整数 n, k  
  - 第二行 n 个整数表示 a_i  

**输出格式**  
每组数据输出一个整数表示最小总伤害。

---

### 题解综合分析

#### 核心思路
1. **贪心策略**：选择跳过能带来最大收益的 k 个陷阱。每个陷阱的收益需综合考虑其基础伤害和后续陷阱的增益影响。
2. **关键公式**：跳过陷阱 i 的净收益为 `a_i + i`。选择该值最大的前 k 个陷阱跳过，总伤害最小。
3. **动态调整**：遍历时维护已跳过的陷阱数，实时计算当前陷阱的额外伤害。

#### 最优题解对比

##### 题解1（happy_dengziyue，5星）
**亮点**：  
- 推导清晰，将总收益拆分为基础减免、额外伤害和顺序调整三部分，最终简化为 `a_i + i` 的排序问题。  
- 代码直接模拟跳跃过程，动态维护已跳过的次数，直观且易验证。  
**关键代码**：
```cpp
for(int i=1,cnt=0;i<=n;++i){
    if(ch[i]) ++cnt;
    else ans += a[i] + cnt;
}
```

##### 题解2（Eric998，4星）
**亮点**：  
- 发现公式推导中的偏差，通过数学修正项 `k*(k-1)/2` 调整最终结果。  
- 代码简洁，直接计算调整后的总和。  
**关键公式**：  
每个陷阱的收益为 `a_i - (n - i -1)`，总和减去前 k 大收益后需修正。  
**核心代码**：
```cpp
sum -= a[i]; // a[i]已预处理为 a_i -n +i +1
cout << sum - (k-1)*k/2 << "\n";
```

##### 题解3（suyunqiaoKID，4星）
**亮点**：  
- 结构体排序标记跳过的陷阱，模拟过程与题解1类似。  
- 代码可读性强，适合理解动态影响。  

---

### 关键思路总结
1. **收益模型**：跳过陷阱的收益应综合考虑直接减免的伤害和后续影响的代价。  
2. **排序策略**：将 `a_i + i` 作为排序依据，选择前 k 大值。  
3. **动态维护**：遍历时实时统计已跳过的次数，计算当前陷阱的实际伤害。

---

### 类似题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心选择最小代价  
2. [P1208 [USACO1.3]混合牛奶](https://www.luogu.com.cn/problem/P1208) - 单价排序后贪心  
3. [P5020 货币系统](https://www.luogu.com.cn/problem/P5020) - 贪心+动态规划的综合应用

---
处理用时：215.33秒