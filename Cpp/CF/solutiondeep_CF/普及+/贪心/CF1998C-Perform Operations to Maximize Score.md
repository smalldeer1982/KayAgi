# 题目信息

# Perform Operations to Maximize Score

## 题目描述

I see satyam343. I'm shaking. Please more median problems this time. I love those. Please satyam343 we believe in you.

— satyam343's biggest fan



You are given an array $ a $ of length $ n $ and an integer $ k $ . You are also given a binary array $ b $ of length $ n $ .

You can perform the following operation at most $ k $ times:

- Select an index $ i $ ( $ 1 \leq i \leq n $ ) such that $ b_i = 1 $ . Set $ a_i = a_i + 1 $ (i.e., increase $ a_i $ by $ 1 $ ).

Your score is defined to be $ \max\limits_{i = 1}^{n} \left( a_i + \operatorname{median}(c_i) \right) $ , where $ c_i $ denotes the array of length $ n-1 $ that you get by deleting $ a_i $ from $ a $ . In other words, your score is the maximum value of $ a_i + \operatorname{median}(c_i) $ over all $ i $ from $ 1 $ to $ n $ .

Find the maximum score that you can achieve if you perform the operations optimally.

For an arbitrary array $ p $ , $ \operatorname{median}(p) $ is defined as the $ \left\lfloor \frac{|p|+1}{2} \right\rfloor $ -th smallest element of $ p $ . For example, $ \operatorname{median} \left( [3,2,1,3] \right) = 2 $ and $ \operatorname{median} \left( [6,2,4,5,1] \right) = 4 $ .

## 说明/提示

For the first test case, it is optimal to perform $ 5 $ operations on both elements so $ a = [8,8] $ . So, the maximum score we can achieve is $ \max(8 + \operatorname{median}[8], 8 + \operatorname{median}[8]) = 16 $ , as $ c_1 = [a_2] = [8] $ . It can be proven that you cannot get a better score.

For the second test case, you are not able to perform operations on any elements, so $ a $ remains $ [3,3,3] $ . So, the maximum score we can achieve is $ 3 + \operatorname{median}[3, 3] = 6 $ , as $ c_1 = [a_2, a_3] = [3, 3] $ . It can be proven that you cannot get a better score.

## 样例 #1

### 输入

```
8
2 10
3 3
1 1
3 10
3 3 3
0 0 0
4 4
2 1 5 1
0 1 0 1
5 4
7 5 2 5 4
0 0 1 0 1
5 1
5 15 15 2 11
1 0 0 1 1
5 2
10 11 4 10 15
1 1 0 1 0
4 4
1 1 2 5
1 1 0 0
2 1000000000
1000000000 1000000000
1 1```

### 输出

```
16
6
8
13
21
26
8
3000000000```

# AI分析结果



# Perform Operations to Maximize Score

## 题目描述

给定一个长度为 $n$ 的数组 $a$、一个整数 $k$ 和一个二进制数组 $b$。你可以进行最多 $k$ 次操作：

- 选择一个下标 $i$（$1 \leq i \leq n$）满足 $b_i = 1$，将 $a_i$ 增加 $1$。

你的得分定义为 $\max\limits_{i = 1}^{n} \left( a_i + \operatorname{median}(c_i) \right)$，其中 $c_i$ 表示删除 $a_i$ 后的数组。$\operatorname{median}(p)$ 定义为数组 $p$ 中第 $\left\lfloor \frac{|p|+1}{2} \right\rfloor$ 小的元素。

求通过最优操作能获得的最大得分。

---

## 题解对比与精析

### 最优思路提炼
1. **排序预处理**：将数组升序排序，便于确定中位数的位置。
2. **双策略取最优**：
   - **策略一**：将全部操作次数用于提升某个可操作元素（$b_i=1$），使其成为最大值后贡献得分。
   - **策略二**：通过二分法确定最大可达的中位数，将操作次数用于提升其他元素以支撑该中位数。
3. **关键结论**：当最大元素不可操作时，最优解可能来自提升中位数区域中的元素。

### 高分题解推荐
#### 题解1：BrotherCall（★★★★☆）
**核心亮点**：
- 严格证明两种极端情况的最优性（全0/全1的b数组）
- 提出混合情况的二分判定框架
- 时间复杂度 $O(n\log n \log V)$ 可接受

**关键代码解析**：
```cpp
bool chk(ll tg) { // 检查能否使中位数≥tg
    ll kk = k, cnt = 0;
    vector<pair<ll,ll>> tmp(a);
    for(int i=n-1; i>=0; --i) { // 从大到小处理
        if(tmp[i].first < tg && tmp[i].second) {
            ll need = tg - tmp[i].first;
            if(kk >= need) kk -= need, tmp[i].first = tg;
        }
        if(tmp[i].first >= tg) cnt++;
    }
    sort(tmp.begin(), tmp.end());
    return tmp[n/2 - 1].first >= tg; // 检查中位数位置
}
```

#### 题解2：liugh_（★★★★☆）
**核心亮点**：
- 更简洁的二分实现
- 显式处理最大可操作元素的贡献
- 引入动态中位数位置调整机制

**策略选择代码**：
```cpp
// 策略一：寻找最大可操作元素的贡献
ll res1 = 0;
for(int i=n; i>=1; --i) 
    if(a[i].se) 
        res1 = max(res1, a[i].fi + m + 中位数偏移计算);

// 策略二：二分中位数阈值
ll l=1, r=2e9, ans=0;
while(l <= r) {
    ll mid = (l+r)/2;
    if(check(mid)) l=mid+1, ans=mid;
    else r=mid-1;
}
return max(ans + a[n].fi, res1);
```

---

## 拓展与总结
### 同类型题目推荐
1. [P1168 中位数](https://www.luogu.com.cn/problem/P1168) - 动态维护中位数
2. [P2672 推销员](https://www.luogu.com.cn/problem/P2672) - 贪心选择与贡献计算
3. [P4344 SHOI2015 脑洞治疗仪](https://www.luogu.com.cn/problem/P4344) - 二分答案与操作模拟

### 调试经验摘录
- **排序后索引偏移**：多位题解强调排序后原索引对应关系丢失，需在预处理时绑定原始数据（`pair<值, 可操作标记>`）。
- **二分边界设定**：初始右边界应设为原数组最大值 +k，而非固定值。
- **中位数位置计算**：当n为偶数和奇数时的不同处理需要严格验证。

### 核心思维导图
```
排序预处理 → 分治两种策略
    ↓
策略一：最大化可操作元素
    → 寻找最大可操作的a[i] → a[i]+k + 当前中位数
    ↓
策略二：最大化中位数区域
    → 二分目标中位数 → 贪心填充不足值
    ↓
取两种策略的最大值
```

---
处理用时：54.88秒