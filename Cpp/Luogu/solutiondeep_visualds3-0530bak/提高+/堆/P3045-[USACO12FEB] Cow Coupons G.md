# 题目信息

# [USACO12FEB] Cow Coupons G

## 题目背景

Subtask 0 为原数据，Subtask 1,2 为 hack 数据。

## 题目描述

Farmer John needs new cows! There are N cows for sale (1 <= N <= 50,000), and FJ has to spend no more than his budget of M units of money (1 <= M <= 10^14).  Cow i costs P\_i money (1 <= P\_i <= 10^9), but FJ has K coupons (1 <= K <= N), and when he uses a coupon on cow i, the cow costs C\_i instead (1 <= C\_i <= P\_i). FJ can only use one coupon per cow, of course.

What is the maximum number of cows FJ can afford? 

FJ 准备买一些新奶牛。市场上有 $N$ 头奶牛，第 $i$ 头奶牛价格为 $P_i$。FJ 有 $K$ 张优惠券，使用优惠券购买第 $i$ 头奶牛时价格会降为 $C_i$，当然每头奶牛只能使用一次优惠券。FJ 想知道花不超过 $M$ 的钱最多可以买多少奶牛？

- $1 \le K \le N \le 5 \times 10^4$
- $1 \le C_i \le P_i \le 10^9$
- $1 \le M \le 10^{14}$

## 说明/提示

FJ has 4 cows, 1 coupon, and a budget of 7.


FJ uses the coupon on cow 3 and buys cows 1, 2, and 3, for a total cost of 3 + 2 + 1 = 6.


## 样例 #1

### 输入

```
4 1 7 
3 2 
2 2 
8 1 
4 3 
```

### 输出

```
3 
```

# AI分析结果



# 算法分类  
反悔贪心

---

## 题解分析与结论

### 核心算法流程
1. **初始贪心**：选 K 个优惠价最小的牛使用优惠券
2. **维护差价堆**：记录已用优惠券的差价（原价-优惠价）
3. **动态选择**：对后续牛比较两种选择：
   - 直接原价购买（`p[i]`）
   - 替换差价最小的优惠券（`c[i] + min_delta`）
4. **优先队列管理**：三个优先队列分别管理原价、优惠价、差价

### 解决难点
- **优惠券复用**：通过维护差价堆实现优惠券的动态调整
- **时间复杂度**：O(N log N) 的贪心决策，使用优先队列快速获取极值
- **状态同步**：用标记数组处理已购买的牛，避免重复选择

---

## 题解评分（≥4星）

### 人间温柔（★★★★☆）
- 亮点：代码简洁，优先队列维护清晰
- 关键代码：
```cpp
priority_queue<int,vector<int>,greater<int>> delta; // 差价堆
while(...){
    // 比较原价购买与替换优惠券的代价
    if(delta.top() > p_val - c_val){
        m -= p_val; // 原价购买
    } else {
        m -= c_val + delta.top(); // 替换优惠券
        delta.pop();
        delta.push(p_i - c_i); // 更新差价堆
    }
}
```

### Cuxhin（★★★★☆）
- 亮点：分阶段推导，详细解释反悔条件
- 关键思路：
```cpp
// 初始化差价堆为 K 个 0（虚拟优惠券）
for(int i=1;i<=k;i++) delta.push(0);

// 动态选择最优购买方式
if(p_current < c_current + delta.top()){
    buy_by_original_price();
} else {
    refund_min_delta_coupon();
    use_coupon_for_current();
}
```

### _ZSR_（★★★★☆）
- 亮点：代码结构清晰，维护三个优先队列
- 关键片段：
```cpp
priority_queue<pii> q1,q2,q3; // 原价、优惠价、差价堆
while(...){
    // 比较两种选择的最小代价
    if(原价更优) 直接购买;
    else 替换差价最小的优惠券;
}
```

---

## 最优思路提炼

### 核心技巧
1. **差价反悔机制**：用优先队列维护已用优惠券的差价（`p_j - c_j`），每次替换时选择最小差值的优惠券进行反悔
2. **双队列筛选**：同时维护原价队列和优惠价队列，保证每次取到当前最优选择
3. **虚拟优惠券**：初始化时在差价堆填充 K 个 0，统一处理未使用完优惠券的情况

### 数学推导
当替换优惠券时需满足：
```
c_i + (p_j - c_j) < p_i
=> p_j - c_j < p_i - c_i
```
即优先替换差价更小的优惠券使用记录

---

## 同类题目推荐
1. P2949 [USACO09OPEN]Work Scheduling G（反悔贪心）
2. P4053 [JSOI2007]建筑抢修（截止时间+贪心反悔）
3. P1090 [NOIP2004 提高组] 合并果子（基础优先队列）

---

## 可视化设计

### 动画方案
![反悔贪心动画演示](https://fastly.jsdelivr.net/gh/doocs/leetcode@main/solution/2800-2899/2813.Maximum%20Elegance%20of%20a%20K-Length%20Subsequence/images/demo.gif)
（示例图：动态展示优惠券替换过程）

### 交互要素
1. **颜色标记**：
   - 红色：当前候选牛
   - 绿色：已用优惠券的牛
   - 黄色：差价堆中的可替换优惠券
2. **步进控制**：
   - 暂停/继续按钮控制动画
   - 拖动条调节执行速度（0.5x~3x）
3. **音效反馈**：
   - 选择原价购买时播放硬币音效
   - 替换优惠券时播放"咔嗒"声
   - 超额时播放警示音

### 像素风格实现
```javascript
// Canvas 绘制示例（8-bit风格）
function drawCow(ctx, x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x*16, y*16, 14, 14); // 16x16像素块
}

// 音效触发
function playSound(type) {
    const audio = new Audio();
    audio.src = type === 'buy' ? 'coin.wav' : 'click.wav';
    audio.play();
}
```

---

## 代码实现

### 人间温柔题解核心代码
```cpp
priority_queue<int, vector<int>, greater<int>> delta; // 差价小根堆

for(int i=1; i<=k; i++) delta.push(0); // 初始化虚拟优惠券

while(...) {
    // 取出当前最小原价和优惠价
    auto [p_val, p_id] = P.top();
    auto [c_val, c_id] = C.top();
    
    if(delta.top() > p_val - c_val) {
        // 原价购买逻辑
        P.pop();
        buy_with_original_price(p_val);
    } else {
        // 替换优惠券逻辑
        delta.pop();
        delta.push(p[c_id] - c[c_id]); // 更新差价堆
        buy_with_coupon(c_val);
    }
}
```

---

## 心得摘录
> "反悔贪心的精髓在于『常思己过』—— 当发现更优解时，要有勇气推翻之前的局部最优决策" —— 人间温柔

> "调试时发现，未正确维护已购买标记会导致队列中残留无效元素，这是 90% WA 的原因" —— Cuxhin

---

## 总结
本题通过差价反悔机制实现动态贪心，核心在于维护可替换的优惠券集合。使用优先队列快速获取极值，结合双队列筛选策略，在 O(N log N) 时间复杂度内完成最优决策。同类问题中涉及截止时间、资源调度的题目均可借鉴此思路。

---
处理用时：89.06秒