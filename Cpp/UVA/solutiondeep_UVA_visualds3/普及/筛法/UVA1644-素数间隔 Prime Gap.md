# 题目信息

# 素数间隔 Prime Gap

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4519

[PDF](https://uva.onlinejudge.org/external/16/p1644.pdf)

# AI分析结果



## 算法分类
筛法（欧拉筛） + 二分查找

---

## 题解思路与核心难点

### 核心逻辑
1. **预处理阶段**：使用欧拉筛法生成 1~1299709 范围内所有素数
2. **查询阶段**：
   - 若 n 是素数 → 输出 0
   - 否则在预处理的素数数组中找到包围 n 的最小素数对 → 输出差值

### 关键难点对比
| 实现方式           | 时间复杂度       | 核心优势                     | 缺点                     |
|--------------------|------------------|------------------------------|--------------------------|
| 线性查找相邻素数   | O(N) 每次查询    | 实现简单                     | 无法应对大规模查询       |
| 二分查找           | O(logN) 每次查询 | 查询效率指数级提升           | 需要有序数组预处理       |
| 质数间隔预计算     | O(1) 每次查询    | 终极优化方案                 | 需要额外存储空间         |
| 逐个判断素数       | O(√n) 每次判断   | 省内存                      | 无法处理大范围查询       |

---

## 精选题解 (≥4星)

### 1. 珅肐题解（⭐⭐⭐⭐⭐）
- **核心亮点**：使用 `lower_bound` 二分查找
- **代码亮点**：
  ```cpp
  int o=lower_bound(prime+1,prime+cnt+1,n)-prime;
  printf("%d\n",prime[o]-prime[o-1]);
  ```
- **优化点**：将查询复杂度从 O(n) 优化到 O(logn)

### 2. xixike题解（⭐⭐⭐⭐）
- **核心亮点**：完整实现线性筛+二分模板
- **数据结构**：
  ```cpp
  int p[100010],mindiv[1300000]; // 双数组存储
  ```

### 3. 封禁用户题解（⭐⭐⭐⭐）
- **核心贡献**：详细解释欧拉筛原理
- **重要注释**：
  ```cpp
  if(!(i%prime[j])) break; // 避免重复标记的关键
  ```

---

## 最优实现代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX = 1299710;
vector<int> primes;
bool is_composite[MAX];

void sieve() {
    fill(is_composite, is_composite+MAX, false);
    for(int i=2; i<MAX; ++i) {
        if(!is_composite[i]) primes.push_back(i);
        for(int p : primes) {
            if(i*p >= MAX) break;
            is_composite[i*p] = true;
            if(i%p == 0) break;
        }
    }
}

int query(int n) {
    if(!is_composite[n]) return 0;
    auto it = upper_bound(primes.begin(), primes.end(), n);
    return *it - *(it-1);
}
```

---

## 同类型拓展
1. **区间素数统计**：预处理前缀和数组快速回答区间素数数量
2. **质因数分解**：利用筛法存储最小质因数加速分解
3. **回文素数**：结合筛法与回文数判断

---

## 洛谷推荐题目
1. [P3383 线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P1217 回文质数](https://www.luogu.com.cn/problem/P1217)
3. [P3912 素数统计](https://www.luogu.com.cn/problem/P3912)

---

## 算法可视化设计

### 欧拉筛动画方案
```javascript
// 伪代码示例
class SieveAnimation {
  constructor(canvas) {
    this.numbers = Array(50).fill().map((_,i) => i+2) // 演示用较小范围
    this.current = 2
    this.primes = []
  }

  step() {
    if(this.current > Math.sqrt(50)) return
    
    // 高亮当前数
    if(!this.marked[this.current]) {
      this.primes.push(this.current)
      // 标记倍数（红色闪烁）
      for(let k=this.current; k<=50; k+=this.current) {
        this.markNumber(k, 'red') 
      }
    }
    
    // 移动到下一个数
    this.current++
  }
}
```

### 可视化特性
1. **颜色编码**：
   - 绿色：当前处理的素数
   - 红色：正在标记的合数
   - 蓝色：已确认的素数
2. **交互控制**：
   - 速度滑块：调节动画执行速度（1x-10x）
   - 单步执行按钮：手动控制算法进度
3. **音效反馈**：
   - 发现新素数时播放 "ping" 音效
   - 标记合数时播放 "tick" 音效

---

## 调试心得摘录
> "卡了N次才发现输入处理有问题...原来UVa的输入需要先读一次再进循环，血泪教训！" —— 封禁用户

> "线性筛中的 `if(i%prime[j]==0) break` 是灵魂所在，理解这点才能真正掌握筛法" —— MoXiaodu

---

## 举一反三
当遇到以下特征时考虑筛法：
1. 需要处理 **密集素数查询**
2. 数据范围在 **1e6 级别**
3. 需要 **快速质因数分解**
4. 涉及 **数论函数计算**（如欧拉函数）

通过预处理将时间复杂度从每次 O(√n) 优化到 O(1) 或 O(logn)，是这类问题的核心解决思路。

---
处理用时：81.11秒