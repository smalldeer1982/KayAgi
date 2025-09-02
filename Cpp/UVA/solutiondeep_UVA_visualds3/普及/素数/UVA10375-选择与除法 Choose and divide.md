# 题目信息

# 选择与除法 Choose and divide

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1316

[PDF](https://uva.onlinejudge.org/external/103/p10375.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10375/f4c82551d4d63248a3265b83e25132b66c043585.png)

## 样例 #1

### 输入

```
10 5 14 9
93 45 84 59
145 95 143 92
995 487 996 488
2000 1000 1999 999
9998 4999 9996 4998```

### 输出

```
0.12587
505606.46055
1.28223
0.48996
2.00000
3.99960```

# AI分析结果



## 算法分类
数论（组合数学与质因数分解）

---

## 题解思路与难点对比

### 核心思路
计算组合数比值时避免大数溢出，常用三种方法：
1. **边乘边除法**：交替乘分子项与除分母项，控制中间值大小。
2. **质因数分解法**：分解所有数至质因数，统计指数后相乘。
3. **对数转换法**：利用对数将乘法转换为加法，避免数值溢出。

### 关键难点与解决
- **边乘边除法**：需合理安排乘除顺序避免中间值溢出或精度丢失。例如，循环中每次优先除以当前分母项。
- **质因数分解法**：需高效分解阶乘的质因数指数。通过预处理质数表，快速统计每个质数在分子分母中的总指数差。
- **对数转换法**：预计算 `log(n!)` 数组，用加减代替乘除，最后通过 `exp` 恢复结果。需注意浮点精度。

---

## 题解评分（≥4星）

1. **ShineEternal（质因数分解）** ★★★★☆  
   - 亮点：精确处理大数，预处理质数表高效，代码结构清晰。
   - 代码：[见原题解] 关键函数 `search` 分解质因数，`pd` 处理阶乘。

2. **地大陈参志（对数转换）** ★★★★☆  
   - 亮点：代码简洁，预处理 `logF` 数组，利用对数避免溢出。
   - 核心代码：
     ```cpp
     long double logc(int n, int m) {
         return logF[n] - logF[m] - logF[n - m];
     }
     printf("%.5f\n", exp(v1 - v2));
     ```

3. **小闸蟹（质因数分解优化）** ★★★★☆  
   - 亮点：试商法分解质因数，优化指数统计逻辑。
   - 核心函数：
     ```cpp
     void AddFactorial(int n, int d) {
         for (int i = 1; i <= n; ++i) AddInteger(i, d);
     }
     ```

---

## 最优思路提炼
**质因数分解法**为最优：
1. **预处理质数表**：埃氏筛或欧拉筛生成质数。
2. **统计指数**：对每个阶乘分解质因数，统计分子分母的指数差。
3. **计算结果**：遍历质数表，累乘 `prime[i]^e[i]`。

**关键代码片段**：
```cpp
// 预处理质数表
vector<int> prime;
void sieve() {
    for (int i = 2; i <= 10000; i++) {
        if (!vis[i]) prime.push_back(i);
        for (int j : prime) { /* 欧拉筛逻辑 */ }
    }
}

// 统计阶乘质因数指数
void count(int x, int d) {
    for (int p : prime) {
        while (x % p == 0) e[p] += d, x /= p;
        if (x == 1) break;
    }
}
```

---

## 类似题目推荐
1. **UVA 369 Combinations**（组合数模运算）
2. **洛谷 P3807 卢卡斯定理**（大组合数取模）
3. **LeetCode 172 阶乘后的零**（质因数分解应用）

---

## 可视化算法设计
### 质因数分解动画
1. **像素风格界面**：  
   - 左侧展示质数表（8-bit 字体），右侧为指数统计条。
   - 每次分解质因数时，对应质数条长度变化（绿色增，红色减）。
2. **步进控制**：  
   - 高亮当前处理的阶乘项（如 `p!`），逐步分解质因数。
3. **音效反馈**：  
   - 分解完成时播放“叮”声，错误操作触发“哔”声。

### 对数转换演示
- **动态折线图**：展示 `logF[n]` 的累积过程，计算时实时绘制 `v1 - v2` 的差值曲线。
- **精度提示**：最终结果用发光特效强调，若误差超过阈值则标记红色。

---

## 个人心得摘录
- **封禁用户**：边乘边除需注意循环顺序，否则中间值可能溢出。
- **SisconHL**：对数法虽简便，但 `long double` 的精度在极端数据下可能不足。
- **233333q**：质因数分解时直接统计 `n/p + n/p² + ...` 更高效。

---

## 完整代码示例（质因数分解法）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX = 10005;
vector<int> primes;
bool vis[MAX];
int e[MAX];

void sieve() {
    for (int i = 2; i < MAX; i++) {
        if (!vis[i]) primes.push_back(i);
        for (int p : primes) {
            if (i*p >= MAX) break;
            vis[i*p] = true;
            if (i % p == 0) break;
        }
    }
}

void update(int n, int d) {
    for (int p : primes) {
        if (p > n) break;
        int cnt = 0, tmp = n;
        while (tmp) cnt += tmp/p, tmp /= p;
        e[p] += cnt * d;
    }
}

int main() {
    sieve();
    int p, q, r, s;
    while (cin >> p >> q >> r >> s) {
        memset(e, 0, sizeof(e));
        update(p, 1);     // C(p,q)分子
        update(q, -1);    // C(p,q)分母
        update(p-q, -1);
        update(r, -1);    // C(r,s)分母
        update(s, 1);     // C(r,s)分子
        update(r-s, 1);
        
        double ans = 1.0;
        for (int p : primes) 
            if (e[p] != 0) ans *= pow(p, e[p]);
        printf("%.5f\n", ans);
    }
    return 0;
}
```

---
处理用时：117.37秒