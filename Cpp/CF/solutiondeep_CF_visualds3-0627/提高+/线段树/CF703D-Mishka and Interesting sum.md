# 题目信息

# Mishka and Interesting sum

## 题目描述

Little Mishka enjoys programming. Since her birthday has just passed, her friends decided to present her with array of non-negative integers $ a_{1},a_{2},...,a_{n} $ of $ n $ elements!

Mishka loved the array and she instantly decided to determine its beauty value, but she is too little and can't process large arrays. Right because of that she invited you to visit her and asked you to process $ m $ queries.

Each query is processed in the following way:

1. Two integers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) are specified — bounds of query segment.
2. Integers, presented in array segment $ [l,r] $ (in sequence of integers $ a_{l},a_{l+1},...,a_{r} $ ) even number of times, are written down.
3. XOR-sum of written down integers is calculated, and this value is the answer for a query. Formally, if integers written down in point 2 are $ x_{1},x_{2},...,x_{k} $ , then Mishka wants to know the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7210428d91e1c7505cfe57a2df3abdc28a7ac76c.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/4298d47c0191af3c0a3103f431751061bc7e2362.png) — operator of exclusive bitwise OR.

Since only the little bears know the definition of array beauty, all you are to do is to answer each of queries presented.

## 说明/提示

In the second sample:

There is no integers in the segment of the first query, presented even number of times in the segment — the answer is $ 0 $ .

In the second query there is only integer $ 3 $ is presented even number of times — the answer is $ 3 $ .

In the third query only integer $ 1 $ is written down — the answer is $ 1 $ .

In the fourth query all array elements are considered. Only $ 1 $ and $ 2 $ are presented there even number of times. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/1f43581f72fc5ce3c0b862a8034cb76a29952125.png).

In the fifth query $ 1 $ and $ 3 $ are written down. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7a7518e2f6c019be104f1f3114e7d17043192b15.png).

## 样例 #1

### 输入

```
3
3 7 8
1
1 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
7
1 2 1 3 3 2 3
5
4 7
4 5
1 3
1 7
1 5
```

### 输出

```
0
3
1
3
2
```

# AI分析结果



# 算法分类
离线处理 + 树状数组（异或前缀和优化）

# 题解思路与解决难点

## 核心思路推导
利用异或的消去性质：
1. 出现偶数次的数异或和为0，奇数次的数异或和为自身
2. 偶数次异或和 = 区间总异或和 ^ 不同数异或和

## 关键实现步骤
1. **离散化**处理大范围数值
2. 预处理每个数前驱出现位置`pre[]`
3. 离线查询按右端点排序
4. **树状数组维护动态异或和**：插入新元素时消除前驱影响
5. 最终答案 = 树状数组查询结果 ^ 异或前缀和

## 解决难点对比
| 方法         | 时间复杂度  | 关键优化点                     | 适用场景         |
|--------------|------------|------------------------------|----------------|
| 树状数组离线   | O(nlogn)   | 利用异或可逆性维护动态集合       | 大规模数据       |
| 莫队算法      | O(n√n)     | 奇偶排序+块长优化               | 中等规模数据     |
| 线段树离线    | O(nlogn)   | 区间异或标记的传播               | 动态数据更新场景 |

# 题解评分（≥4星）

## 顾z（⭐⭐⭐⭐⭐）
- 亮点：最早提出异或性质转换公式，树状数组实现简洁高效
- 核心代码：
```cpp
while(now<=r) {
    if(pre[now]) add(pre[now],b[a[now]]);
    add(now,b[a[now]]);
    now++;
}
```

## 灰鹤在此（⭐⭐⭐⭐）
- 亮点：线段树实现清晰，离散化处理完整
- 关键步骤：`update()`时通过异或消除前驱影响

## Little09（⭐⭐⭐⭐）
- 亮点：类HH的项链解法，map维护前驱位置
- 独特技巧：使用`map`替代离散化数组处理数值映射

# 最优思路提炼
**异或消去法**：
1. 维护两个异或和：
   - `sum[]`：普通异或前缀和
   - `tree[]`：动态更新的不同数异或和
2. **动态更新策略**：当处理到位置i时：
   ```python
   if 该数之前出现过(pre[i]):
       在树状数组pre[i]位置异或该数（消除旧位置影响）
   在树状数组i位置异或该数（记录新位置）
   ```

# 同类型题拓展
1. [P1972 HH的项链](https://www.luogu.com.cn/problem/P1972)（区间不同元素计数）
2. [CF1000F](https://codeforces.com/problemset/problem/1000/F)（区间任一出现次数为1的数）
3. [SP3267 DQUERY](https://www.luogu.com.cn/problem/SP3267)（区间不同元素数）

# 可视化算法演示

## 动画设计
![树状数组更新过程](https://i.postimg.cc/8z3ZJj8H/xor-trie.gif)
1. **颜色标记**：
   - 红色方块：当前处理的右端点
   - 蓝色连线：`pre[i]`与前驱位置的关联
   - 绿色高亮：树状数组更新的节点
2. **操作流程**：
   - 步进处理右端点，展示`pre[i]`消除和当前插入
   - 显示异或前缀和与树状数组查询的叠加过程

## 复古像素风格实现
```javascript
// Canvas绘制关键帧
function drawFrame(ctx, step) {
    // 绘制树状数组结构
    drawBIT(ctx, step); 
    // 高亮当前处理的数
    ctx.fillStyle = '#FF5555';
    ctx.fillRect(currentX, currentY, 16, 16); 
    // 播放8-bit音效
    playSound('blip', step%2 ? 440 : 523.25);
}

// 自动演示模式
autoPlay(() => {
    moveRightPointer();
    updateBITAnimation();
}, {fps: 2, loop: false});
```

# 核心代码实现
```cpp
// 离散化与预处理
for(int i=1;i<=n;i++) {
    a[i] = lower_bound(b+1,b+tot+1,a[i])-b;
    pre[i] = last[a[i]];
    last[a[i]] = i;
}

// 树状数组更新
void update(int x, int val) {
    while(x <= n) {
        tree[x] ^= val;
        x += lowbit(x);
    }
}

// 查询处理
while(now <= q[i].r) {
    if(pre[now]) update(pre[now], b[a[now]]);
    update(now, b[a[now]]);
    now++;
}
ans = query(r) ^ query(l-1) ^ sum[r] ^ sum[l-1];
```

# 个人心得摘录
> "卡常时发现奇偶排序能让缓存命中率提升30%，块长取n/√m比传统√n快2倍" —— RuntimeErr  
> "异或的消去性质就像魔法，把看似复杂的统计问题转化为简洁的位运算" —— 顾z  
> "离散化时直接保留原数值映射，避免多次查表影响性能" —— Little09

---
处理用时：74.70秒