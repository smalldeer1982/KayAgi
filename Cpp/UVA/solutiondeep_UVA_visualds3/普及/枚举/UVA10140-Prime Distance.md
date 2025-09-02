# 题目信息

# Prime Distance

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1081

[PDF](https://uva.onlinejudge.org/external/101/p10140.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/7fac8d7bdf18ec6e0fd2914c1623eee77be89ef3.png)

## 样例 #1

### 输入

```
2 17
14 17```

### 输出

```
2,3 are closest, 7,11 are most distant.
There are no adjacent primes.```

# AI分析结果



---

## 算法分类
**区间筛法**

---

## 题解思路与算法分析
### 核心思路
题目要求在区间 [L, R] 中找到相邻质数的最小和最大距离。核心解决思路是通过预处理小质数（≤√R）来标记大区间中的合数，最终未被标记的即为质数。

### 算法要点对比
| 题解方法               | 核心实现                                                                 | 时间复杂度               | 优化点                                                                 |
|------------------------|--------------------------------------------------------------------------|--------------------------|-----------------------------------------------------------------------|
| 埃氏筛预处理+区间筛法 | 预处理 2~√R 的质数，遍历每个质数 p 标记 [L, R] 中 p 的倍数                | O(√R log R + (R-L) log R) | 偏移数组优化（用 vis[x-L] 代替直接存储 x）                              |
| 线性筛预处理+区间筛法 | 线性筛预处理 2~√R 的质数，标记逻辑与埃氏筛相同                             | 同埃氏筛                  | 线性筛减少重复标记                                                   |
| Miller-Rabin 直接检测 | 对每个数单独用 Miller-Rabin 检测质数，标记合数的倍数                        | O((R-L) k log³n)         | 无需预处理，适合区间极小时                                            |

### 解决难点
1. **大区间处理**：R 可达 2³¹，但 R-L ≤ 1e6，需用偏移数组将 [L, R] 映射到 [0, R-L]
2. **起始点计算**：对每个质数 p，起始点应取 max(⌈L/p⌉, 2) * p
3. **特殊值处理**：L=1 时需单独处理第一个元素

---

## 题解评分（≥4星）
#### 1. Siyuan（5★）
- **亮点**：线性筛预处理，偏移数组实现简洁，边界处理完整
- **核心代码**：
  ```cpp
  for(int i=1;i<=tot;++i) {
      for(long long j=l/p[i];j*p[i]<=r;++j) {
          long long x = p[i]*j;
          if(j>1 && x>=l) vis[x-l] = 0;
      }
  }
  ```

#### 2. 冒泡ioa（4.5★）
- **亮点**：详细数学推导，处理溢出问题的技巧（`if(p[i]*j-l<0)continue`）
- **心得摘录**：  
  > "poj上必须加溢出判断，否则会因为负数索引导致WA"

#### 3. AcRapper（4★）
- **亮点**：用线性筛预处理时的特殊处理逻辑清晰
- **关键优化**：`j 从 max(l/prime[j], 2)` 避免标记质数本身

---

## 最优技巧提炼
1. **偏移映射法**：用 `vis[x-L]` 代替直接存储 x，解决大区间内存问题
2. **两阶段筛法**：先筛小质数，再用小质数筛大区间
3. **快速起始计算**：`start = max( (L+p-1)/p * p, 2*p )`
4. **相邻质数遍历**：将筛后的质数存入数组，遍历相邻元素差值

---

## 同类型题目推荐
1. [P1835 素数密度](https://www.luogu.com.cn/problem/P1835)（区间筛法模板题）
2. [P1217 回文质数](https://www.luogu.com.cn/problem/P1217)（质数+回文数联合判断）
3. [UVA10311 质数间隔](https://www.luogu.com.cn/problem/UVA10311)（动态区间质数判断）

---

## 算法可视化设计
### 核心流程演示
```javascript
// 伪代码示例：Canvas 绘制筛法过程
function drawSieveAnimation() {
  let p = primes[currentStep]; // 当前处理的质数
  for(let j = start; j*p <= R; j++) {
    highlightGrid(j*p - L, "orange"); // 高亮当前标记的网格
    markAsComposite(j*p - L);          // 标记为合数
    playSound("mark_sound.wav");       // 播放标记音效
  }
  highlightCurrentPrime(p);            // 高亮当前质数
}
```

### 复古风格设计
1. **像素网格**：将 [L, R] 映射为 16x16 像素格子，质数显示为绿色，合数为红色
2. **音效设计**：
   - 质数发现：8-bit 上升音效（0x1A 波形）
   - 合数标记：短促爆破音（0x02 噪声）
3. **自动演示模式**：按质数从小到大自动播放标记过程，支持暂停/单步

---

## 核心代码片段
```cpp
// 偏移筛法核心代码（Siyuan 题解）
void sieve(long long L, long long R) {
    memset(vis, true, sizeof(vis));
    if(L == 1) vis[0] = false; // 处理 L=1 的特殊情况
    
    for(int i=1; i<=tot_primes; ++i) {
        long long p = primes[i];
        long long start = max((L+p-1)/p, 2LL) * p; // 计算起始点
        
        for(long long j=start; j<=R; j+=p) {
            vis[j - L] = false; // 偏移标记
        }
    }
    
    // 收集质数并计算差值
    vector<long long> primes_in_range;
    for(long long x=L; x<=R; ++x) {
        if(vis[x-L]) primes_in_range.push_back(x);
    }
}
```

---

## 总结
通过区间筛法高效解决大范围质数距离问题，其核心在于利用小质数预处理与偏移映射技巧。相较于直接检测法，筛法在时间复杂度上具有明显优势，特别适合 R-L 较大的场景。可视化时可重点展示质数如何通过「波浪式标记」逐步筛选，配合复古音效增强理解。

---
处理用时：86.03秒