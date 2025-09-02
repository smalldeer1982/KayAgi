# 题目信息

# Gabriel and Caterpillar

## 题目描述

The $ 9 $ -th grade student Gabriel noticed a caterpillar on a tree when walking around in a forest after the classes. The caterpillar was on the height $ h_{1} $ cm from the ground. On the height $ h_{2} $ cm ( $ h_{2}&gt;h_{1} $ ) on the same tree hung an apple and the caterpillar was crawling to the apple.

Gabriel is interested when the caterpillar gets the apple. He noted that the caterpillar goes up by $ a $ cm per hour by day and slips down by $ b $ cm per hour by night.

In how many days Gabriel should return to the forest to see the caterpillar get the apple. You can consider that the day starts at $ 10 $ am and finishes at $ 10 $ pm. Gabriel's classes finish at $ 2 $ pm. You can consider that Gabriel noticed the caterpillar just after the classes at $ 2 $ pm.

Note that the forest is magic so the caterpillar can slip down under the ground and then lift to the apple.

## 说明/提示

In the first example at $ 10 $ pm of the first day the caterpillar gets the height $ 26 $ . At $ 10 $ am of the next day it slips down to the height $ 14 $ . And finally at $ 6 $ pm of the same day the caterpillar gets the apple.

Note that in the last example the caterpillar was slipping down under the ground and getting the apple on the next day.

## 样例 #1

### 输入

```
10 30
2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10 13
1 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
10 19
1 2
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
1 50
5 4
```

### 输出

```
1
```

# AI分析结果



# Gabriel and Caterpillar

## 题目描述

九年级学生Gabriel下课后在森林中散步时，发现树上有一只毛毛虫。毛毛虫位于离地面$h_1$厘米的高度，而同一棵树上$h_2$厘米（$h_2>h_1$）处悬挂着一个苹果，毛毛虫正在向苹果方向爬行。

Gabriel想知道他应该在第几天返回森林才能看到毛毛虫吃到苹果。已知毛毛虫白天（上午10点至晚上10点）每小时爬升$a$厘米，夜晚（晚上10点至次日上午10点）每小时下滑$b$厘米。Gabriel每天下午2点下课，发现毛毛虫的时间是当天下午2点刚下课。

注意：毛毛虫可以滑落到地面之下再重新爬升。

## 输入输出样例

### 样例 #1
输入：
```
10 30
2 1
```
输出：
```
1
```

### 样例 #2
输入：
```
10 13
1 1
```
输出：
```
0
```

## 算法分类
模拟

---

## 题解分析与结论

### 核心思路
1. **初始阶段处理**：第一天下午2点至晚上10点（8小时）的爬升后立即判断能否到达
2. **终止条件判断**：若$a \leq b$且首日无法到达，则永远无法到达（输出-1）
3. **循环模拟**：以天为单位模拟，每天经历12小时爬升和12小时下滑，直到高度≥h2

### 最优题解亮点

#### 题解作者：欢黎明陌（⭐⭐⭐⭐⭐）
**关键亮点**：
- 清晰划分三种情况：立即到达、无法到达、需多日模拟
- 代码注释详细，处理首日8小时与后续循环逻辑分离
- 数学优化：通过`(h2 - h1 - 8a) / (12(a-b))`公式减少循环次数

**核心代码**：
```cpp
h1 += 8 * a;
if (h1 >= h2) { /* 输出0 */ }
h1 -= 12 * b;
while (h1 < h2) {
    h1 += 12 * a;
    if (h1 >= h2) break;
    h1 -= 12 * b;
    ans++;
}
```

#### 题解作者：Micnation_AFO（⭐⭐⭐⭐）
**关键亮点**：
- 三情况分类简洁明确
- 数学公式直接计算天数，避免逐日模拟
- 处理余数的技巧：`(tmp % d != 0) ? ans++ : 0`

**核心代码**：
```cpp
int d = (a - b) * 12;
ans = (h2 - h1 - 8*a) / d;
if ((h2 - h1 - 8*a) % d) ans++;
```

#### 题解作者：PersistentLife（⭐⭐⭐⭐）
**关键亮点**：
- 详细处理时间段的注释说明
- 循环逻辑与边界条件处理清晰
- 包含调试经历的思考过程（如首日时间计算）

**个人心得摘录**：
> "第一天只爬了8小时但掉了12小时，答案初始化为1很容易被忽略"

---

## 拓展与练习
### 类似题型套路
1. **周期性变化模拟**：蜗牛爬井、昼夜交替运动
2. **数学公式优化**：通过推导将循环转为数学计算
3. **边界特判**：初始阶段的特殊时间窗口处理

### 推荐练习题
1. [P1518 牛吃草](https://www.luogu.com.cn/problem/P1518) - 二维坐标系的周期性模拟
2. [P1036 选数](https://www.luogu.com.cn/problem/P1036) - 组合数学与循环终止判断
3. [P2697 宝石串](https://www.luogu.com.cn/problem/P2697) - 前缀和与区间平衡点的寻找

---
处理用时：57.62秒