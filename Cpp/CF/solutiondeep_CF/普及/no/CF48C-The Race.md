# 题目信息

# The Race

## 题目描述

Every year a race takes place on the motorway between cities A and B. This year Vanya decided to take part in the race and drive his own car that has been around and bears its own noble name — The Huff-puffer.

So, Vasya leaves city A on the Huff-puffer, besides, at the very beginning he fills the petrol tank with $ α $ liters of petrol ( $ α>=10 $ is Vanya's favorite number, it is not necessarily integer). Petrol stations are located on the motorway at an interval of $ 100 $ kilometers, i.e. the first station is located $ 100 $ kilometers away from the city A, the second one is $ 200 $ kilometers away from the city A, the third one is $ 300 $ kilometers away from the city A and so on. The Huff-puffer spends $ 10 $ liters of petrol every $ 100 $ kilometers.

Vanya checks the petrol tank every time he passes by a petrol station. If the petrol left in the tank is not enough to get to the next station, Vanya fills the tank with $ α $ liters of petrol. Otherwise, he doesn't stop at the station and drives on.

For example, if $ α=43.21 $ , then the car will be fuelled up for the first time at the station number $ 4 $ , when there'll be $ 3.21 $ petrol liters left. After the fuelling up the car will have $ 46.42 $ liters. Then Vanya stops at the station number $ 8 $ and ends up with $ 6.42+43.21=49.63 $ liters. The next stop is at the station number $ 12 $ , $ 9.63+43.21=52.84 $ . The next stop is at the station number $ 17 $ and so on.

You won't believe this but the Huff-puffer has been leading in the race! Perhaps it is due to unexpected snow. Perhaps it is due to video cameras that have been installed along the motorway which register speed limit breaking. Perhaps it is due to the fact that Vanya threatened to junk the Huff-puffer unless the car wins. Whatever the reason is, the Huff-puffer is leading, and jealous people together with other contestants wrack their brains trying to think of a way to stop that outrage.

One way to do this is to mine the next petrol station where Vanya will stop. Your task is to calculate at which station this will happen and warn Vanya. You don't know the $ α $ number, however, you are given the succession of the numbers of the stations where Vanya has stopped. Find the number of the station where the next stop will be.

## 说明/提示

In the second example the answer is not unique. For example, if $ α=10 $ , we'll have such a sequence as $ 1 $ , $ 2 $ , $ 3 $ , and if $ α=14 $ , the sequence will be $ 1 $ , $ 2 $ , $ 4 $ .

## 样例 #1

### 输入

```
3
1 2 4
```

### 输出

```
unique
5
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
not unique
```

# AI分析结果



# The Race

## 题目描述

每年在A城与B城之间的高速公路上都会举办一场赛车比赛。今年Vanya决定驾驶他的爱车"Huff-puffer"参赛。

Vanya从A城出发时，会在油箱中注入α升汽油（α≥10，不一定是整数）。加油站以每100公里一个的间隔分布在公路上：第一个加油站在A城100公里处，第二个在200公里处，依此类推。Huff-puffer每100公里消耗10升汽油。

每当Vanya经过加油站时，如果剩余油量不足以到达下一个加油站，他就会加注α升汽油。已知Vanya前n次加油的加油站编号序列，请确定下一次加油的加油站编号，并判断答案是否唯一。

## 输入格式
第一行包含整数n  
第二行包含n个整数表示已加油的加油站编号

## 输出格式
若答案唯一，输出"unique"和下一站编号  
否则输出"not unique"

## 样例输入1
```
3
1 2 4
```

## 样例输出1
```
unique
5
```

## 样例输入2
```
2
1 2
```

## 样例输出2
```
not unique
```

---

**算法分类**：数学

---

## 题解综合分析

### 核心思路
通过维护α的可行区间范围[min_val, max_val]：
1. 每个加油站i的编号a_i满足：i*α - a_i*10 ∈ [0,10) 
2. 转化为 α ∈ [a_i/i, (a_i+1)/i) 的约束
3. 对所有约束取交集得到最终α的范围
4. 计算 (n+1)*α 的整数部分即为下一站编号

### 难点对比
1. 区间边界的处理：当max_val恰好为整数时需要减1（右开区间）
2. 浮点数精度处理：使用double类型存储范围
3. 多约束叠加：每个加油站都会产生新的约束条件

---

## 精选题解

### 题解1：Creroity（4星）
**关键亮点**：  
- 使用动态范围收缩法维护α的上下界
- 处理边界条件的清晰逻辑
- 代码简洁高效（时间复杂度O(n)）

**核心代码**：
```cpp
double Minx = a, Maxx = a+1;
for(int i=2;i<=n;i++){
    cin>>a;
    Minx = max(Minx, a*1.0/i);
    Maxx = min(Maxx, (a+1)*1.0/i);
}
Minx *= n+1, Maxx *= n+1;
if(Maxx == floor(Maxx)) Max--;
```

### 题解2：PR_CYJ（4星）
**关键亮点**：  
- 将α放大10倍处理，避免浮点运算误差
- 详细的数学推导注释
- 直观的变量命名（minnn/maxxx）

**核心代码**：
```cpp
double minnn=0, maxxx=1e9;
for(int i=1;i<=n;i++) {
    cin>>t;
    minnn = max(minnn,t*10.0/i);
    maxxx = min(maxxx,(t*10.0+10)/i);
}
if (maxx == maxxx*(n+1)) maxx--;
```

### 题解3：灰鹤在此（4星）
**关键亮点**：  
- 清晰的数学公式推导
- 详尽的样例分析
- 完整的边界条件处理

**核心代码**：
```cpp
minn = max(minn,a/i);
maxn = min(maxn,(a+1)/i);
...
if(maxn == floor(maxn)) ax--;
```

---

## 关键技巧总结
1. **区间收缩法**：将每个约束转化为区间，不断取交集缩小范围
2. **边界处理三原则**：
   - 左闭右开区间：[a, b) → floor处理
   - 整数特判：当右边界为整数时需退1
   - 浮点运算：统一使用double类型避免精度丢失
3. **数学建模**：将实际问题转化为线性不等式组求解

---

## 拓展训练
1. **同类型题目**：  
   - CF847E（Packmen）：区间约束与路径规划
   - CF492C（Vanya and Exams）：区间范围维护
   - P1083 [NOIP2012 提高组] 借教室：差分约束系统

2. **调试技巧**：  
   - 使用极限值测试（如α=10的边界情况）
   - 打印中间区间范围辅助调试
   - 验证样例2的多解情况

---

## 心得摘录
"交了7遍总算过了……边界条件真的坑" —— Creroity  
**启示**：浮点运算的边界处理需要特殊验证，特别是整数边界的开闭区间区分

"注意当maxx等于floor(maxx)时的特殊处理" —— 灰鹤在此  
**经验**：区间右端的开区间性质需要始终牢记，这是保证算法正确性的关键

---
处理用时：71.31秒