# 题目信息

# Anton and Fairy Tale

## 题目描述

Anton likes to listen to fairy tales, especially when Danik, Anton's best friend, tells them. Right now Danik tells Anton a fairy tale:

"Once upon a time, there lived an emperor. He was very rich and had much grain. One day he ordered to build a huge barn to put there all his grain. Best builders were building that barn for three days and three nights. But they overlooked and there remained a little hole in the barn, from which every day sparrows came through. Here flew a sparrow, took a grain and flew away..."

More formally, the following takes place in the fairy tale. At the beginning of the first day the barn with the capacity of $ n $ grains was full. Then, every day (starting with the first day) the following happens:

- $ m $ grains are brought to the barn. If $ m $ grains doesn't fit to the barn, the barn becomes full and the grains that doesn't fit are brought back (in this problem we can assume that the grains that doesn't fit to the barn are not taken into account).
- Sparrows come and eat grain. In the $ i $ -th day $ i $ sparrows come, that is on the first day one sparrow come, on the second day two sparrows come and so on. Every sparrow eats one grain. If the barn is empty, a sparrow eats nothing.

Anton is tired of listening how Danik describes every sparrow that eats grain from the barn. Anton doesn't know when the fairy tale ends, so he asked you to determine, by the end of which day the barn will become empty for the first time. Help Anton and write a program that will determine the number of that day!

## 说明/提示

In the first sample the capacity of the barn is five grains and two grains are brought every day. The following happens:

- At the beginning of the first day grain is brought to the barn. It's full, so nothing happens.
- At the end of the first day one sparrow comes and eats one grain, so $ 5-1=4 $ grains remain.
- At the beginning of the second day two grains are brought. The barn becomes full and one grain doesn't fit to it.
- At the end of the second day two sparrows come. $ 5-2=3 $ grains remain.
- At the beginning of the third day two grains are brought. The barn becomes full again.
- At the end of the third day three sparrows come and eat grain. $ 5-3=2 $ grains remain.
- At the beginning of the fourth day grain is brought again. $ 2+2=4 $ grains remain.
- At the end of the fourth day four sparrows come and eat grain. $ 4-4=0 $ grains remain. The barn is empty.

So the answer is $ 4 $ , because by the end of the fourth day the barn becomes empty.

## 样例 #1

### 输入

```
5 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8 1
```

### 输出

```
5
```

# AI分析结果



# 中文题目重写

# Anton 的童话故事

## 题目描述

Anton 喜欢听童话故事，尤其是他的好友 Danik 讲述的故事。现在 Danik 正在给 Anton 讲一个故事：

"从前有个富有的皇帝，他建了一个容量为 $n$ 粒谷物的谷仓。每天会发生以下事件（从第一天开始）：

1. 向谷仓添加 $m$ 粒谷物（若超过容量则只保留填满谷仓的部分）
2. 第 $i$ 天会有 $i$ 只麻雀来吃谷物，每只吃一粒（谷仓空时则无谷物可吃）"

请帮助 Anton 确定谷仓首次变空的具体天数。

## 说明/提示

样例1中，谷仓容量5粒，每日补充2粒。第四天结束时谷仓变空，过程详见题目描述。

## 样例 #1

### 输入
```
5 2
```

### 输出
```
4
```

## 样例 #2

### 输入
```
8 1
```

### 输出
```
5
```

**算法分类**：数学、二分

---

# 题解分析与结论

## 题解对比分析

**共同思路**：
1. 分情况处理：当初始谷物量 $n \leq m$ 时，答案就是 $n$ 天
2. 当 $n > m$ 时，前 $m$ 天谷仓始终保持满仓，之后转化为等差数列求和问题

**关键公式**：
前 $m$ 天后剩余谷物量为 $n' = n - m$，需要找到最小的 $x$ 满足：
$$ \frac{x(x+1)}{2} \geq n' $$
最终答案即为 $m + x$

**解法差异**：
- **二分法**（npqenqpve）：在 $[1, 10^{10}]$ 区间二分查找满足条件的最小 $x$，时间复杂度 $O(\log n)$
- **数学近似**（lichenfan等）：通过平方根估算初始值，再微调得到正确解，时间复杂度 $O(1)$

## 精选题解（≥4星）

### 题解1（npqenqpve） ★★★★★
**亮点**：
- 严谨的二分查找实现
- 清晰的分类讨论逻辑
- 处理大数时的稳定性

**核心代码**：
```cpp
int l=1, r=1e10;
while(l<=r) {
    int mid = (l+r)>>1;
    if(mid*(mid+1) >= 2*(n-m)) {
        r = mid-1;
    } else {
        l = mid+1;
    }
}
cout << ans + l;
```

### 题解3（lichenfan） ★★★★☆
**亮点**：
- 巧妙的平方根近似优化
- 简洁的代码实现
- 直观的数学推导

**核心代码**：
```cpp
n = (n-m)*2;
ans = sqrt(n);
while(ans*(ans+1) >= n) ans--;
cout << ans + m + 1;
```

## 关键技巧总结

1. **分阶段处理**：将问题分解为补满阶段（前 $m$ 天）和消耗阶段（后续天数）
2. **等差数列求和**：利用 $\frac{x(x+1)}{2}$ 公式快速计算累计消耗量
3. **二分边界处理**：确定满足不等式的最小整数解
4. **平方根优化**：通过 $x \approx \sqrt{2n}$ 快速定位解区间

## 同类题目推荐

1. **P1085 麦森数**（数学、二分）
2. **P1469 找筷子**（数学推导、异或特性）
3. **P1029 最大公约数和最小公倍数问题**（数论、因数分解）

---
处理用时：95.53秒