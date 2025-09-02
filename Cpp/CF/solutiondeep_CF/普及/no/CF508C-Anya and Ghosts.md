# 题目信息

# Anya and Ghosts

## 题目描述

Anya loves to watch horror movies. In the best traditions of horror, she will be visited by $ m $ ghosts tonight. Anya has lots of candles prepared for the visits, each candle can produce light for exactly $ t $ seconds. It takes the girl one second to light one candle. More formally, Anya can spend one second to light one candle, then this candle burns for exactly $ t $ seconds and then goes out and can no longer be used.

For each of the $ m $ ghosts Anya knows the time at which it comes: the $ i $ -th visit will happen $ w_{i} $ seconds after midnight, all $ w_{i} $ 's are distinct. Each visit lasts exactly one second.

What is the minimum number of candles Anya should use so that during each visit, at least $ r $ candles are burning? Anya can start to light a candle at any time that is integer number of seconds from midnight, possibly, at the time before midnight. That means, she can start to light a candle integer number of seconds before midnight or integer number of seconds after a midnight, or in other words in any integer moment of time.

## 说明/提示

Anya can start lighting a candle in the same second with ghost visit. But this candle isn't counted as burning at this visit.

It takes exactly one second to light up a candle and only after that second this candle is considered burning; it means that if Anya starts lighting candle at moment x, candle is buring from second x + 1 to second x + t inclusively.

In the first sample test three candles are enough. For example, Anya can start lighting them at the $ 3 $ -rd, $ 5 $ -th and $ 7 $ -th seconds after the midnight.

In the second sample test one candle is enough. For example, Anya can start lighting it one second before the midnight.

In the third sample test the answer is $ -1 $ , since during each second at most one candle can burn but Anya needs three candles to light up the room at the moment when the ghost comes.

## 样例 #1

### 输入

```
1 8 3
10
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 10 1
5 8
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1 1 3
10
```

### 输出

```
-1
```

# AI分析结果



# Anya and Ghosts

## 题目描述

Anya 喜欢看恐怖电影。按照恐怖的经典设定，今晚将有 $m$ 个鬼魂造访她。Anya 准备了许多蜡烛，每根蜡烛可以燃烧恰好 $t$ 秒。女孩点燃一根蜡烛需要 1 秒钟。更正式地说，Anya 需要花费 1 秒来点燃一根蜡烛，之后这根蜡烛会燃烧恰好 $t$ 秒，然后熄灭且无法再次使用。

对于每个鬼魂，Anya 知道它到来的时间：第 $i$ 次造访发生在午夜后的 $w_i$ 秒，所有 $w_i$ 互不相同。每次造访持续恰好 1 秒。

求 Anya 需要使用的蜡烛的最小数量，使得每个造访期间至少有 $r$ 根蜡烛正在燃烧。Anya 可以在任意整数秒开始点燃蜡烛（包括午夜前的负整数秒）。

## 说明/提示

- 若在鬼魂造访的同一秒开始点燃蜡烛，该蜡烛不计入该次造访的燃烧数量
- 当 $t < r$ 时必然无解，因为每根蜡烛至少需要 $r$ 秒才能维持 $r$ 根同时燃烧

---

**算法分类**：贪心

---

## 题解分析与结论

### 思路对比与核心难点

1. **特殊判断**：所有题解都优先处理 $t < r$ 的无解情况
2. **贪心方向**：
   - 前向贪心（liuzhongrui）：在鬼魂时间点尽可能晚地点燃蜡烛，用滑动窗口维护有效蜡烛
   - 逆向贪心（wxw_zl）：从最后一个鬼魂开始处理，尽可能早地点燃蜡烛以覆盖前面的需求
3. **实现技巧**：
   - 滑动窗口优化查询效率
   - 时间偏移处理负数时间
   - 逆向处理最大化蜡烛覆盖范围

### 优质题解推荐

#### 题解1：wxw_zl（⭐⭐⭐⭐⭐）
**关键亮点**：逆向贪心策略，通过从后往前处理鬼魂时间点，确保每个蜡烛尽可能覆盖更多鬼魂。代码使用时间偏移技巧处理负数时间，统计区间贡献时采用高效遍历。

**核心代码**：
```cpp
fall(i,m,1) {
    int k=max(w[i]-t,0), burning=0;
    fall(j,w[i]-1,k) burning += tim[j];
    rise(j,k,w[i]-1) {  // 贪心在最早可能时间点蜡烛
        if(burning >= r) break;
        if(tim[j]) continue;
        tim[j] = 1;
        burning++;
    }
    if(burning < r) return -1;
}
```

#### 题解2：liuzhongrui（⭐⭐⭐⭐）
**关键亮点**：滑动窗口维护有效蜡烛区间，时间复杂度稳定。通过维护蜡烛的结束时间数组，使用双指针动态维护当前有效蜡烛数量。

**核心代码**：
```cpp
while(st<ed && a[st]<w) st++;  // 滑动窗口过滤过期蜡烛
for(int i=w-r+ed-st; i<w; i++){  // 计算需要补充的蜡烛位置
    a[ed++] = i + t;  // 记录蜡烛结束时间
    ans++;
}
```

---

## 最优思路总结

**逆向贪心策略**：从最后一个鬼魂开始处理，在时间区间 $[w_i-t, w_i)$ 内尽可能早地点燃蜡烛。这能确保每个蜡烛的燃烧时间覆盖最多的后续鬼魂需求。实现时需要注意：
1. 使用时间偏移处理负时间
2. 区间统计时采用逆序遍历优化

---

## 同类题目推荐

1. [CF1005D - Polycarp and Div 3](https://www.luogu.com.cn/problem/CF1005D)（贪心策略）
2. [P1209 [USACO1.3] 修理牛棚 Barn Repair](https://www.luogu.com.cn/problem/P1209)（区间覆盖优化）
3. [P2255 [USACO14JAN] Recording the Moolympics S](https://www.luogu.com.cn/problem/P2255)（时间区间调度）

---
处理用时：117.46秒