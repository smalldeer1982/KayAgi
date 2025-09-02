# 题目信息

# Sale

## 题目描述

Once Bob got to a sale of old TV sets. There were $ n $ TV sets at that sale. TV set with index $ i $ costs $ a_{i} $ bellars. Some TV sets have a negative price — their owners are ready to pay Bob if he buys their useless apparatus. Bob can «buy» any TV sets he wants. Though he's very strong, Bob can carry at most $ m $ TV sets, and he has no desire to go to the sale for the second time. Please, help Bob find out the maximum sum of money that he can earn.

## 样例 #1

### 输入

```
5 3
-6 0 35 -2 4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4 2
7 0 0 -7
```

### 输出

```
7
```

# AI分析结果



### 题目中文翻译
#### 题目描述
Bob参加了一个旧电视促销活动，共有 $n$ 台电视。第 $i$ 台电视的价格为 $a_i$ 贝尔（可能为负数，表示卖家会倒贴钱）。Bob最多能带走 $m$ 台电视，且只能去一次。求Bob能赚到的最大金额。

#### 样例 #1
##### 输入
```
5 3
-6 0 35 -2 4
```
##### 输出
```
8
```

#### 样例 #2
##### 输入
```
4 2
7 0 0 -7
```
##### 输出
```
7
```

---

### 题解分析与结论
#### 思路总结
所有题解均采用贪心策略：
1. **排序数组**：将电视价格按升序排列。
2. **选择负数**：从前 $m$ 个价格中选择所有负数（价格最低的），累加其绝对值。
3. **边界处理**：遇到非负数时停止选择。

#### 关键难点
1. **贪心选择顺序**：必须优先选择价格最低的（即绝对值最大的负数）。
2. **循环终止条件**：遍历时需及时终止于非负数，避免收益减少。
3. **零值处理**：价格为0的电视不影响收益，但会占用购买次数（不影响正确性）。

---

### 高分题解推荐
#### 1. 作者：xuezhe（4星）
**亮点**：思路最简，直接排序后取前 $m$ 个负数，代码简洁。
**心得**：明确强调“价格为负数时才累加”。
```python
n, m = map(int, input().split())
a = list(map(int, input().split()))
a.sort()
i = 0
s = 0
while i < m and a[i] < 0:
    s -= a[i]
    i += 1
print(s)
```

#### 2. 作者：时律（4星）
**亮点**：代码结构清晰，严格处理负数边界。
**心得**：注释明确“买东西倒贴，良心”。
```cpp
sort(x+1, x+1+a);
for(int i=1; i<=b; i++){
    if(x[i]<0) ans += 0 - x[i];
    else break;
}
```

#### 3. 作者：☆芝麻大饼☆（4星）
**亮点**：代码注释明确，强调“用零减”的陷阱。
**心得**：特别提醒注意负数转正数的计算方式。
```cpp
sort(a, a+n);
for(int i=0; i<m; i++){
    if(a[i]>=0) break;
    sum += 0 - a[i];
}
```

---

### 优化技巧总结
- **直接排序法**：无需取反，直接升序排序后取前 $m$ 个负数更直观。
- **提前终止循环**：遍历时遇到非负数立即跳出，减少无效计算。
- **边界处理统一**：所有实现均正确处理了“负数不足 $m$ 个”的情况。

---

### 同类题目推荐
1. **P1090 [NOIP2004 提高组] 合并果子**（贪心+优先队列）
2. **P1223 排队接水**（贪心排序）
3. **P1803 凌乱的yyy / 线段覆盖**（活动选择类贪心）

---
处理用时：177.41秒