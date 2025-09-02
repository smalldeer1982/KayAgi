# 题目信息

# Present

## 题目描述

Little beaver is a beginner programmer, so informatics is his favorite subject. Soon his informatics teacher is going to have a birthday and the beaver has decided to prepare a present for her. He planted $ n $ flowers in a row on his windowsill and started waiting for them to grow. However, after some time the beaver noticed that the flowers stopped growing. The beaver thinks it is bad manners to present little flowers. So he decided to come up with some solutions.

There are $ m $ days left to the birthday. The height of the $ i $ -th flower (assume that the flowers in the row are numbered from $ 1 $ to $ n $ from left to right) is equal to $ a_{i} $ at the moment. At each of the remaining $ m $ days the beaver can take a special watering and water $ w $ contiguous flowers (he can do that only once at a day). At that each watered flower grows by one height unit on that day. The beaver wants the height of the smallest flower be as large as possible in the end. What maximum height of the smallest flower can he get?

## 说明/提示

In the first sample beaver can water the last 3 flowers at the first day. On the next day he may not to water flowers at all. In the end he will get the following heights: \[2, 2, 2, 3, 2, 2\]. The smallest flower has height equal to 2. It's impossible to get height 3 in this test.

## 样例 #1

### 输入

```
6 2 3
2 2 2 2 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 5 1
5 8
```

### 输出

```
9
```

# AI分析结果



# Present

## 题目描述

小海狸是一名编程新手，信息学是他最喜欢的科目。不久后他的信息学老师即将过生日，小海狸决定准备一份礼物。他在窗台上种了一排 $n$ 朵花，并等待它们生长。然而一段时间后，他发现花停止生长了。小海狸认为送小花是不礼貌的，于是决定采取措施。

距离生日还有 $m$ 天。当前第 $i$ 朵花（按从左到右编号为 $1$ 到 $n$）的高度为 $a_i$。在剩余的每天中，小海狸可以使用一次特殊浇水，浇灌连续 $w$ 朵花（每天只能进行一次）。被浇水的花当天高度增加 1 单位。小海狸希望最终所有花的最小高度尽可能大。求最终最小高度的最大值。

## 样例 #1

### 输入
```
6 2 3
2 2 2 2 1 1
```

### 输出
```
2
```

---

### 综合分析与结论

本题属于经典的最大化最小值问题，核心解法为二分答案结合差分数组优化。所有题解中评分较高的解法均采用以下关键思路：

1. **二分答案框架**：确定可能的最小高度范围，通过二分查找验证可行性
2. **差分数组优化**：将区间浇水操作转换为差分数组的端点修改，将每次验证复杂度降为 $O(n)$
3. **贪心策略**：从左到右处理花的高度缺口，确保每个位置的浇水操作尽可能影响后续区域

---

### 精选题解分析

#### 题解作者：YuRuiH_（★★★★★）
**关键亮点**：
- 使用差分数组实现 $O(n)$ 复杂度的验证函数
- 代码简洁高效，利用前缀和动态维护累计浇水量
- 边界处理清晰，通过 `i-w` 索引控制差分影响范围

**核心代码解析**：
```cpp
bool can(int s){
    int a=0, b=m; // a维护当前累计浇水量，b剩余天数
    for(int i=1;i<=n;i++){
        if(i>=w) a -= need[i-w]; // 移除超出窗口的浇水影响
        need[i] = max(0, s - a - f[i]); // 计算当前位置需要补足的天数
        a += need[i]; // 累加到前缀和
        b -= need[i]; // 扣除总天数
        if(b<0) return false;
    }
    return true;
}
```
通过维护滑动窗口内的浇水影响，避免了显式的区间操作，巧妙利用 `need` 数组记录每个位置的浇水需求。

---

#### 题解作者：Karry5307（★★★★☆）
**核心贡献**：
- 提出双差分数组策略，分别处理原始高度和浇水操作
- 使用二次差分验证最终高度，确保所有位置达标
- 代码结构清晰，变量命名具有可读性

**关键实现**：
```cpp
bool check(int k) {
    memset(bit, 0, sizeof(bit));
    for(int i=1; i<=n; i++) {
        ll c = a[i] + bit[i-1] - bit[max(i-w, 0)];
        bit[i] = bit[i-1];
        if(c < k) {
            bit[i] += k - c;
            if(bit[i] > m) return false;
        }
    }
    return true;
}
```
通过维护 `bit` 数组记录浇水操作的累计影响，以空间换时间的方式简化计算。

---

### 关键思路总结

1. **二分答案框架**：
   - 下界：初始最小高度
   - 上界：初始最小高度 + 总操作天数
   - 每次验证中间值是否可通过 $m$ 次操作实现

2. **差分数组优化技巧**：
   - 将区间 $[L, R]$ 的加法操作转换为差分数组的 $b[L] += x, b[R+1] -= x$
   - 通过前缀和计算每个位置的实际高度
   - 滑动窗口维护当前浇水操作的持续影响范围

3. **贪心策略**：
   - 从左到右处理每个位置的高度缺口
   - 确保每次浇水尽可能覆盖后续需要处理的位置
   - 及时判断总操作天数是否超出限制

---

### 易错点与扩展

**常见错误**：
- 未正确处理浇水窗口超出右侧边界的情况
- 差分数组初始化错误导致残留数据影响下次验证
- 二分边界设置不合理（应设为 `min(a_i) + m`）

**扩展题型**：
1. 动态窗口大小的浇水操作（如 P2895 [USACO08FEB] Meteor Shower S）
2. 多维区间操作问题（如 P2216 [HAOI2007] 理想的正方形）
3. 带权重的最小值最大化（如 P4344 [SHOI2015] 脑洞治疗仪）

---

### 推荐练习题目
1. P2678 [NOIP2015 提高组] 跳石头（二分答案经典题）
2. P1083 [NOIP2012 提高组] 借教室（差分数组应用）
3. P2895 [USACO08FEB] Meteor Shower S（动态窗口处理）

---
处理用时：52.16秒