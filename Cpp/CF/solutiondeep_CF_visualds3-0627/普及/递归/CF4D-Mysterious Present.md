# 题目信息

# Mysterious Present

## 题目描述

Peter decided to wish happy birthday to his friend from Australia and send him a card. To make his present more mysterious, he decided to make a chain. Chain here is such a sequence of envelopes $ A $ = { $ a_{1},a_{2},...,a_{n} $ }, where the width and the height of the $ i $ -th envelope is strictly higher than the width and the height of the $ (i-1) $ -th envelope respectively. Chain size is the number of envelopes in the chain.

Peter wants to make the chain of the maximum size from the envelopes he has, the chain should be such, that he'll be able to put a card into it. The card fits into the chain if its width and height is lower than the width and the height of the smallest envelope in the chain respectively. It's forbidden to turn the card and the envelopes.

Peter has very many envelopes and very little time, this hard task is entrusted to you.

## 样例 #1

### 输入

```
2 1 1
2 2
2 2
```

### 输出

```
1
1 
```

## 样例 #2

### 输入

```
3 3 3
5 4
12 11
9 8
```

### 输出

```
3
1 3 2 
```

# AI分析结果



### 唯一算法分类
动态规划（二维最长严格递增子序列）

---

### 综合分析与结论
#### 核心思路
题目要求找出严格递增的信封序列，可转化为二维最长严格递增子序列问题。各题解核心思路对比：
1. **记忆化搜索**：递归遍历所有可能路径，通过缓存优化重复计算，本质是自顶向下的动态规划。
2. **O(n²) DP**：先按宽度排序，在高度维度做最长递增子序列，需双重循环检查双维度严格递增。
3. **O(n log n)优化**：排序后维护高度序列，用二分查找优化更新过程，类似一维LIS的优化思路。

#### 解决难点
- **严格递增处理**：需同时满足宽度和高度严格递增，排序后需额外检查未被排序的维度。
- **路径记录**：通过前驱数组（pre/from）记录转移路径，递归或迭代回溯输出。
- **数据过滤**：预处理筛除不满足卡片尺寸的信封。

#### 可视化设计
- **动画方案**：
  1. 信封按宽度排序后以网格排列，高度用柱状图表示。
  2. 动态高亮当前处理信封，红色标记已选中的最长序列。
  3. 维护一个上升高度序列，绿色表示当前有效区间，黄色表示二分查找位置。
- **复古像素风格**：
  - 信封用16x16像素块表示，宽度映射为横向长度，高度为纵向。
  - 背景音乐：8-bit风格循环音轨。
  - 音效：选中信封时播放“滴”声，更新最长序列时播放“升级”音效。

---

### 题解清单（≥4星）
1. **Plozia（★★★★★）**
   - **亮点**：清晰解释二维LIS转换思路，代码结构工整，路径记录简洁。
   - **关键代码**：
     ```cpp
     sort(a + 1, a + cnt + 1, cmp);
     for (int i = 1; i <= cnt; ++i) {
         for (int j = 1; j < i; ++j) {
             if (a[j].w < a[i].w && a[j].h < a[i].h && f[j] + 1 > f[i]) {
                 f[i] = f[j] + 1;
                 las[i] = j;
             }
         }
     }
     ```

2. **_edge_（★★★★☆）**
   - **亮点**：O(n log n)优化实现，排序策略巧妙处理相同宽度，二分维护高度序列。
   - **关键代码**：
     ```cpp
     sort(a + 1, a + 1 + tot, cmp);
     f[++len] = a[1].y; fid[len] = 1;
     for (int i = 2; i <= tot; i++) {
         if (f[len] < a[i].y) {
             f[++len] = a[i].y; f1[i] = fid[len - 1];
         } else {
             int it = lower_bound(f + 1, f + len + 1, a[i].y) - f;
             f[it] = a[i].y; f1[i] = fid[it - 1];
         }
     }
     ```

3. **CaiXY06（★★★★）**
   - **亮点**：代码简洁，预处理与DP结合紧密，适合快速实现。
   - **关键代码**：
     ```cpp
     sort(a + 1, a + n + 1, cmp);
     for (int i = 1; i <= n; ++i) {
         for (int j = 1; j < i; ++j) {
             if (a[j].w < a[i].w && a[j].h < a[i].h && f[j] + 1 > f[i]) {
                 f[i] = f[j] + 1;
                 pre[i] = j;
             }
         }
     }
     ```

---

### 最优思路提炼
1. **排序策略**：按宽度升序排序，同宽时按高度降序，避免相同宽度干扰。
2. **状态转移**：DP[i]表示以i结尾的最长序列长度，转移时检查双维度严格递增。
3. **路径回溯**：通过pre数组记录前驱节点，递归逆序输出。
4. **二分优化**：维护高度数组，通过lower_bound快速查找插入位置。

---

### 类似题目推荐
1. **P2782** 争夺圣杯（二维偏序+LIS变形）
2. **P1439** 最长公共子序列（转化为LIS问题）
3. **CF977F** Consecutive Subsequence（一维序列特殊LIS）

---

### 核心代码实现（Plozia题解）
```cpp
sort(a + 1, a + cnt + 1, cmp);
for (int i = 1; i <= cnt; ++i) {
    f[i] = 1;
    for(int j = 1; j < i; ++j) {
        if (a[j].w < a[i].w && a[j].h < a[i].h && f[j] + 1 > f[i]) {
            f[i] = f[j] + 1;
            las[i] = j;
        }
    }
}
int ans = 0, flag = 0;
for (int i = 1; i <= cnt; ++i) {
    if (f[i] > ans) {
        ans = f[i];
        flag = i;
    }
}
printf("%d\n", ans);
print(flag); // 递归输出路径
```

---

### 可视化代码片段（JS伪代码）
```javascript
// Canvas绘制信封网格
function drawEnvelopes(envelopes) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    envelopes.forEach((env, i) => {
        ctx.fillStyle = env.selected ? '#FF0000' : '#00FF00';
        ctx.fillRect(i * 50, 100 - env.h, 40, env.h);
    });
}

// 自动演示LIS构建
function autoPlay() {
    let i = 0;
    const interval = setInterval(() => {
        if (i >= sortedEnvs.length) clearInterval(interval);
        updateLIS(i);
        drawEnvelopes(sortedEnvs);
        i++;
    }, 1000);
}
```

---
处理用时：100.86秒