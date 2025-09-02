# 题目信息

# Maxim and Increasing Subsequence

## 题目描述

Maxim loves sequences, especially those that strictly increase. He is wondering, what is the length of the longest increasing subsequence of the given sequence $ a $ ?

Sequence $ a $ is given as follows:

- the length of the sequence equals $ n×t $ ;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261D/62550b81a494c59fe3493af08329ebf8f9d7bb9b.png) $ (1<=i<=n×t) $ , where operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF261D/946bcc44e053027f1f6b5dfc3143583e661988f5.png) means taking the remainder after dividing number $ x $ by number $ y $ .

Sequence $ s_{1},s_{2},...,s_{r} $ of length $ r $ is a subsequence of sequence $ a_{1},a_{2},...,a_{n} $ , if there is such increasing sequence of indexes $ i_{1},i_{2},...,i_{r} $ $ (1<=i_{1}&lt;i_{2}&lt;...\ &lt;i_{r}<=n) $ , that $ a_{ij}=s_{j} $ . In other words, the subsequence can be obtained from the sequence by crossing out some elements.

Sequence $ s_{1},s_{2},...,s_{r} $ is increasing, if the following inequality holds: $ s_{1}&lt;s_{2}&lt;...&lt;s_{r} $ .

Maxim have $ k $ variants of the sequence $ a $ . Help Maxim to determine for each sequence the length of the longest increasing subsequence.

## 样例 #1

### 输入

```
3 3 5 2
3 2 1
1 2 3
2 3 1
```

### 输出

```
2
3
3
```

# AI分析结果



# 算法分类  
动态规划 + 树状数组优化

---

# 题解思路与核心分析

## 核心思路
1. **不同元素数剪枝**：当重复次数 t ≥ 不同元素数 sum 时，答案恒为 sum  
2. **树状数组优化 DP**：用树状数组维护前缀最大值，滚动数组节省空间  
3. **循环周期处理**：每周期遍历原始序列，用树状数组快速更新 DP 值  

## 解决难点对比
| 题解 | 核心思路 | 时间复杂度 | 实现复杂度 |
|------|----------|------------|------------|
| liangzihao | 树状数组维护每周期 DP 值 | O(k·n·t·log maxb) | 低 |
| yyandy | 排序后分周期计算转移次数 | O(k·n·maxb) | 高 |
| fuqingchen | 归并法处理循环周期 | O(k·nb) | 中 |

---

# 题解评分（≥4星）

## liangzihao（4.5⭐️）
- **亮点**：直观的树状数组优化，代码可读性高  
- **心得**：玄学优化 `if(ans>=sum) break` 显著减少计算量  

## yyandy（4.2⭐️）
- **亮点**：创新性的循环次数计算，避免重复扫描  
- **难点**：需要理解 `g[j]` 表示跨越周期数的巧妙设计  

## Jayun（4.0⭐️）
- **亮点**：最简化的树状数组实现，适合快速编码  
- **优化**：滚动数组节省内存空间  

---

# 最优技巧提炼

## 关键数据结构
```cpp
int tree[maxn]; // 树状数组维护区间最大值
void updata(int x, int c) {
    while(x <= maxb) tree[x] = max(tree[x],c), x += lowbit(x);
}
int get(int x) {
    int c = 0;
    while(x > 0) c = max(c,tree[x]), x -= lowbit(x);
    return c;
}
```

## 核心 DP 逻辑
```cpp
for(int i=1; i<=t; i++) // 遍历每个周期
    for(int j=1; j<=n; j++){ // 遍历原序列
        int c = get(a[j]-1) + 1; // 查询比当前数小的最大长度
        if(c > f[j]){ // 更新当前周期结果
            f[j] = c;
            updata(a[j], c); // 更新树状数组
        }
    }
```

---

# 同类题目推荐
1. P1020 [NOIP1999 提高组] 导弹拦截（最长不升子序列）  
2. P1439 【模板】最长公共子序列（序列映射优化）  
3. P4309 [TJOI2008] 最长递增子序列（平衡树优化）

---

# 可视化设计

## 动画方案
![树状数组更新过程](https://i.imgur.com/8lwX0yR.gif)  
1. **颜色标记**：  
   - 红色：当前处理的序列元素  
   - 蓝色：树状数组中被更新的节点  
2. **步进控制**：  
   - 按空格键逐周期执行  
   - 拖动滑块调节动画速度（0.5x~4x）  
3. **音效设计**：  
   - 叮~（元素被选中）  
   - 嘟~（树状数组节点更新）  

## 复古像素风格
```javascript
// Canvas 绘制示例
function drawPixel(x, y, color) {
    ctx.fillStyle = colorPalette[color];
    ctx.fillRect(x*8, y*8, 7, 7); // 8x8 像素块
}

// 音效触发
audioContext.trigger('update', {x: pos, value: f[j]});
```

---

# 核心代码实现
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5+5;
int tree[MAXN], f[MAXN], a[MAXN];

int main() {
    int k, n, maxb, t;
    scanf("%d%d%d%d", &k, &n, &maxb, &t);
    while(k--) {
        // 初始化及输入处理
        for(int i=1; i<=n; i++) scanf("%d", &a[i]);
        
        // 树状数组优化 DP
        fill(tree, tree+maxb+1, 0);
        fill(f, f+n+1, 0);
        int ans = 0;
        for(int i=1; i<=t; i++)
            for(int j=1; j<=n; j++) {
                int c = (a[j]>1 ? query(a[j]-1) : 0) + 1;
                if(c > f[j]) {
                    f[j] = c;
                    update(a[j], c);
                    ans = max(ans, c);
                }
            }
        printf("%d\n", ans);
    }
    return 0;
}
```

---
处理用时：59.20秒