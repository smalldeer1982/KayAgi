# 题目信息

# [POI 2012] ODL-Distance

## 题目描述

**译自 POI 2012 Stage 1. 「[Distance](https://szkopul.edu.pl/problemset/problem/Phel_x2Ny30OUh7z1RhCtzEG/site/?key=statement)」**

定义一次「操作」为将一个正整数除以或乘以一个质数。定义函数 $d(a,b)$ 表示将 $a$ 进行若干次“操作”变成 $b$ 所需要的最小操作次数。例如，$d(69,42)=3$.

$d$ 显然是一个距离函数，满足以下性质：
* $d(a,a) = 0$
* $d(a,b) = d(b,a)$
* $d(a,b) + d(b,c) \ge d(a,c)$

给定 $n$ 个正整数 $a_1, a_2, \ldots, a_n$，对每个 $a_i (1 \le i \le n)$，求 $j$ 使得 $j \neq i$ 且 $d(a_i,a_j)$ 最小。如果有多个满足条件的 $j$，应输出最小的那个。

## 说明/提示

对于 $30\%$ 的数据有 $n \le 1000$.

对于所有数据有 $2 \le n \le 10^5,1 \le a_i \le 10^6$.

翻译来自于 [LibreOJ](https://loj.ac/p/2690)。

## 样例 #1

### 输入

```
6
1
2
3
4
5
6```

### 输出

```
2
1
1
2
1
2```

# AI分析结果



## 数学分类选择  
**数论**

---

## 题解思路、算法要点与解决难点  
### 核心公式推导  
定义 $\Omega(x)$ 为 $x$ 的质因数指数和（如 $12=2^2×3^1$，$\Omega(12)=3$）。  
对于 $a_i$ 和 $a_j$，其距离公式为：  
$$d(a_i,a_j) = \Omega(a_i) + \Omega(a_j) - 2\Omega(\gcd(a_i,a_j))$$  
**推导思路**：  
- $\gcd(a_i,a_j)$ 的质因子为两者的公共部分，无需操作  
- $a_i$ 和 $a_j$ 的非公共质因子需要通过乘/除操作消除  

### 算法实现要点  
1. **预处理 $\Omega(x)$**  
   通过线性筛法（类似欧拉筛）预处理所有数的 $\Omega(x)$，时间复杂度 $O(n)$。  
   ```cpp  
   for(int i=2; i<=maxx; ++i) {  
       if(!cnt[i]) prime[++tot] = i, cnt[i] = 1;  
       for(int j=1; prime[j]*i <= maxx; ++j) {  
           cnt[i*prime[j]] = cnt[i] + 1;  
           if(i%prime[j] == 0) break;  
       }  
   }  
   ```  
2. **枚举 $\gcd$ 的优化**  
   对于每个数 $a_i$，枚举其所有因数 $d$（即可能的 $\gcd$），维护每个 $d$ 对应的最小 $\Omega(a_j)$ 及其下标。  
   - **维护最小值与次小值**：避免 $i=j$ 的情况  
   ```cpp  
   void update(int d, int x) {  
       if(cnt[a[x]] < cnt[a[min1[d]]]) {  
           min2[d] = min1[d]; min1[d] = x;  
       } else if(cnt[a[x]] < cnt[a[min2[d]]]) {  
           min2[d] = x;  
       }  
   }  
   ```  
3. **查询最优解**  
   对于每个 $a_i$，遍历其所有因数 $d$，计算 $d$ 对应的最优 $j$，并记录全局最小值。  
   ```cpp  
   void query(int i, int d) {  
       int j = (min1[d] == i) ? min2[d] : min1[d];  
       int val = cnt[a[i]] + cnt[a[j]] - 2*cnt[d];  
       if(val < min_val || (val == min_val && j < ans)) {  
           min_val = val; ans = j;  
       }  
   }  
   ```  

### 解决难点  
- **避免重复选择自身**：通过维护次小值  
- **高效枚举所有可能的 $\gcd$**：利用因数分解而非直接枚举所有数  
- **复杂度优化**：调和级数枚举倍数，总复杂度 $O(n\sqrt{m})$  

---

## 题解评分（≥4星）  
1. **傅思维666（5星）**  
   - 思路清晰，详细解释了次小值的必要性  
   - 代码结构清晰，维护最小/次小值的逻辑明确  
   - 预处理与查询分离，可读性强  
2. **lhm_（4.5星）**  
   - 双维护最小值与次小值  
   - 代码略紧凑但核心逻辑正确  
3. **ThinkofBlank（4星）**  
   - 完整注释与推导，适合新手  
   - 代码中详细处理了因数的对称性  

---

## 最优思路或技巧提炼  
1. **枚举 $\gcd$ 而非直接枚举数对**：将问题从 $O(n^2)$ 降至 $O(n\sqrt{m})$  
2. **预处理 $\Omega(x)$**：线性筛法高效计算质因数指数和  
3. **维护最小与次小值**：解决 $i=j$ 的特殊情况  
4. **因数分解优化**：仅需遍历 $\sqrt{a_i}$ 次即可覆盖所有因数  

---

## 同类型题与通用套路  
- **通用数论模型**：  
  $$f(a,b) = g(a) + g(b) - 2g(\gcd(a,b))$$  
  类似问题可通过枚举 $\gcd$ 并维护极值解决  
- **同类题目**：  
  1. [洛谷 P1029 最大公约数与最小公倍数问题](https://www.luogu.com.cn/problem/P1029)  
  2. [洛谷 P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)  
  3. [CF 1350C. Orac and LCM](https://codeforces.com/problemset/problem/1350/C)  

---

## 可视化与算法演示（核心数学过程）  
### 动画设计方案  
1. **像素风格界面**：  
   - **背景**：16色调色板，深蓝底色模拟复古终端  
   - **当前操作数**：黄色像素块高亮显示 $a_i$  
   - **因数枚举**：绿色方块标记当前因数 $d$，红色方块标记对称因数 $a_i/d$  
2. **关键步骤演示**：  
   - **步骤1**：分解 $a_i=12$ → 因数 $1,2,3,4,6,12$  
   - **步骤2**：对每个因数 $d$，显示其维护的最小值下标 $min1[d]$ 和 $min2[d]$  
   - **步骤3**：计算 $d=3$ 时的贡献值 $\Omega(12)+\Omega(6)-2×\Omega(3)=3+2-2×1=3$  
3. **音效与交互**：  
   - **分解因数**：8-bit 短音效（类似《超级马里奥》金币音）  
   - **更新最小值**：高音调“滴”声  
   - **错误选择**：低音“嗡”声  

### 关键代码片段（Canvas 绘制）  
```javascript  
function drawStep(d, a_i, min_j) {  
    ctx.fillStyle = "#FFFF00"; // 黄色标记当前数  
    ctx.fillRect(x, y, 16, 16);  
    ctx.fillStyle = "#00FF00"; // 绿色标记因数  
    factors.forEach(f => {  
        drawFactor(f);  
        let j = getMinJ(f);  
        drawLink(a_i, j); // 绘制连线到最小值下标  
    });  
}  
```  

---

## 个人心得摘录  
> “维护次小值时，必须严格判断 `x != min1[d]`，否则会错误覆盖最小值。调试时通过构造全相同数的测试用例发现此问题。”（摘自傅思维666题解）  

---

## 代码实现（核心片段）  
```cpp  
// 预处理最小/次小值  
for(int i=1; i<=n; ++i) {  
    for(int j=1; j*j<=a[i]; ++j) {  
        if(a[i]%j != 0) continue;  
        update(j, i);  
        if(j != a[i]/j) update(a[i]/j, i);  
    }  
}  
// 查询答案  
for(int i=1; i<=n; ++i) {  
    int min_val = INF, ans = -1;  
    for(int j=1; j*j<=a[i]; ++j) {  
        if(a[i]%j != 0) continue;  
        query(i, j);  
        query(i, a[i]/j);  
    }  
    printf("%d\n", ans);  
}  
```

---
处理用时：89.96秒