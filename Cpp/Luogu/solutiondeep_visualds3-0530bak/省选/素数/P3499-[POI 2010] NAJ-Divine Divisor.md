# 题目信息

# [POI 2010] NAJ-Divine Divisor

## 题目描述

An integer ![](http://main.edu.pl/images/OI17/naj-en-tex.1.png) is given.

We say that an integer ![](http://main.edu.pl/images/OI17/naj-en-tex.2.png) is a divisor of ![](http://main.edu.pl/images/OI17/naj-en-tex.3.png) with multiplicity ![](http://main.edu.pl/images/OI17/naj-en-tex.4.png)    (![](http://main.edu.pl/images/OI17/naj-en-tex.5.png) is integer) if ![](http://main.edu.pl/images/OI17/naj-en-tex.6.png) and ![](http://main.edu.pl/images/OI17/naj-en-tex.7.png) does not divide ![](http://main.edu.pl/images/OI17/naj-en-tex.8.png).

For example, the number ![](http://main.edu.pl/images/OI17/naj-en-tex.9.png) has the following divisors:

2 with multiplicity 4, 3 with multiplicity 1, 4 with multiplicity 2, 6 with multiplicity 1, and so on.

We say that a number ![](http://main.edu.pl/images/OI17/naj-en-tex.10.png) is a  divine divisor of the number ![](http://main.edu.pl/images/OI17/naj-en-tex.11.png)    if ![](http://main.edu.pl/images/OI17/naj-en-tex.12.png) is a divisor of ![](http://main.edu.pl/images/OI17/naj-en-tex.13.png) with multiplicity ![](http://main.edu.pl/images/OI17/naj-en-tex.14.png) and ![](http://main.edu.pl/images/OI17/naj-en-tex.15.png) has no divisors    with multiplicities greater than ![](http://main.edu.pl/images/OI17/naj-en-tex.16.png).

For example, the sole divine divisor of 48 is 2 (with multiplicity 4),    and the divine divisors of 6 are: 2, 3 and 6 (each with multiplicity 1).

Your task is to determine the multiplicity of divine divisors of ![](http://main.edu.pl/images/OI17/naj-en-tex.17.png)    and the number of its divine divisors.

给定一个正整数 $m$ 以及长度为 $m$ 的正整数序列  $a$ ,同时给出  $n = \prod_{i=1}^{m}{a_i}$。你需要找出一个最大的 $k$ 使得存在一个 $d$ , $d > 1$ 并且 $d^k | n$。求这个最大的 $k$ 以及在 $k$ 最大的情况下有多少个 $d$ 满足条件。

## 说明/提示

$1\le m\le 600$，且$\forall 1\le i\le m$，有$1\le a_i\le 10^{18}$


## 样例 #1

### 输入

```
3
4 3 4```

### 输出

```
4
1```

# AI分析结果



## 算法分类
**Pollard-Rho 算法与质因数分解**

---

## 综合分析与结论
### 核心算法流程
1. **质因数分解**  
   - 使用筛法预处理小质数（≤1e6），分解所有可被小质数整除的因子  
   - 剩余大数通过 Miller-Rabin 素性测试判断是否为质数，或用 Pollard-Rho 分解  
   - 特殊处理平方数和两质数乘积（通过 GCD 或平方根检测）

2. **统计与求解**  
   - 统计所有质因数出现次数，记录最大值 `k`  
   - 计算最大值出现次数 `cnt`，答案 `ans = 2^cnt - 1`（高精度优化）

### 可视化设计要点
- **像素动画**：质因数分解时，显示当前处理的数分解成像素块，不同颜色区分质数/合数  
- **步进控制**：单步展示 Pollard-Rho 的随机游走过程，高亮当前尝试的伪随机函数值  
- **音效提示**：  
  - 分解成功：播放 8-bit 短促音效  
  - 最大 `k` 出现：上扬音调提示关键结果  
- **统计面板**：右侧实时显示质因数出现次数，最大 `k` 自动置顶闪烁  

---

## 题解清单（≥4星）
### 1. skylee（★★★★☆）
- **亮点**：  
  - 分情况处理剩余数（平方数/质数/合数）  
  - 高精度优化用浮点转字符串减一  
  - 代码结构清晰，结合筛法与分解策略  
- **代码片段**：  
  ```cpp
  // 处理平方数和质数检测
  if(floor(sqrt(a[i])) == ceil(sqrt(a[i]))) { ... }
  if(miller_rabin(a[i])) { ... }
  ```

### 2. Kreado（★★★★☆）
- **亮点**：  
  - 直接使用 Pollard-Rho 分解所有数  
  - 代码简洁，高精度处理与 skylee 类似  
- **代码片段**：  
  ```cpp
  inline void solve(ll X){
    if(X<2) return;
    if(Prime(X)){S[X]++;return;}
    ll Y=X; while((Y=PR(X,Rand(X)))==X);
    solve(X/Y); solve(Y);
  }
  ```

### 3. kczno1（★★★★☆）
- **亮点**：  
  - 复杂情况分类（大质数/平方数/合数）  
  - 手动实现高精度乘法，兼容性更强  
- **关键逻辑**：  
  ```cpp
  // 两两求 GCD 分解合数
  for (j=i+1;j<=top;++j) {
    ll g=gcd(a,st[j]);
    if (g>1) { ... }
  }
  ```

---

## 核心代码实现
### Pollard-Rho 分解核心
```cpp
ll Pollard_Rho(ll n) {
    if(n == 4) return 2;
    ll c = rand()%(n-1)+1, x = 0, y = 0, d = 1;
    for(int lim=1; ;lim<<=1) {
        ll s = 1, x = y;
        for(int i=1; i<=lim; i++){
            y = f(y, c, n);
            s = mul(s, abs(y-x), n);
            if(i%127 == 0 && (d = gcd(s, n)) > 1) 
                return d;
        }
        if((d = gcd(s, n)) > 1) return d;
    }
}
```

### 高精度优化（浮点转字符串）
```cpp
sprintf(ans, "%.0Lf", powl(2.0L, cnt)); // 浮点计算2^cnt
ans[strlen(ans)-1]--; // 末尾减1避免退位
```

---

## 相似题目推荐
1. [P4718]【模板】Pollard-Rho算法  
2. [P1066] 2^k进制数（大数处理与高精度）  
3. [P2485] 计算器（幂次分解与离散对数）  

---

## 可视化方案（伪代码）
```javascript
// Canvas绘制质因数分解动画
function drawFactorization(n) {
    let x = 0, y = 0, d = 1;
    const c = rand();
    // 伪随机游走动画
    setInterval(() => {
        x = f(x, c, n);
        y = f(f(y, c, n), c, n);
        drawPoint(x, y, 'red'); // 当前试探点
        if(gcd(abs(x-y), n) > 1) {
            playSound('success.wav'); // 分解成功音效
            highlightFactor(n, d);
        }
    }, 100);
}
```

---

## 个人心得摘录
> "Pollard-Rho 的随机性让分解效率大幅提升，但需注意多次尝试避免遗漏质因子。高精部分用浮点转字符串减一是巧妙的工程优化，避免手写高精的繁琐。" —— skylee  
> "分解时先筛小质数能显著减少 Pollard-Rho 的调用次数，这是平衡时间复杂度的关键。" —— kczno1

---
处理用时：72.76秒