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



# 分析与解答

## 1. 算法分类
**数论**

## 2. 题解核心思路与难点对比

### 数学方法与关键公式
- **核心公式**：设质因数分解后各质数次数为 $cnt_i$，则答案 $k = \max(cnt_i)$，满足条件的 $d$ 数量为 $2^{num} - 1$（$num$ 为最大次数质数的个数）
- **推导关键**：任何 $d$ 必须是这些质数的子集乘积，子集非空

### 解决难点
- **大数分解**：需处理 $10^{18}$ 规模的质因数分解
- **高效分解**：通过筛小质数（≤1e6）预处理降低复杂度
- **剩余数分类**：
  - 完全平方数：$\sqrt{a_i}$ 是否整数
  - 质数：Miller-Rabin 检测
  - 两不同质数积：与其他数求 GCD 分解

### 可视化设计思路
- **分步动画**：展示分解过程（小质数→平方数→质数→剩余数），用不同颜色标记分解阶段
- **像素风格**：质因数用色块表示，分解时色块分裂成小质数块并统计次数
- **音效触发**：质数检测通过时播放确认音效，分解失败时警示音

## 3. 题解评分（≥4星）

### skylee（★★★★☆）
- **亮点**：分层处理（小质数→平方数→质数→剩余数），浮点数处理高精度
- **代码**：引入 `cnt2` 处理无法分解的剩余数，避免遗漏

### Kreado（★★★★☆）
- **亮点**：标准 Pollard-Rho 模板，代码简洁
- **代码片段**：
```cpp
inline void solve(ll X){
    if(X<2) return ;
    if(Prime(X)){S[X]++;return ;} // 直接统计质数
    ll Y=X; while((Y=PR(X,Rand(X)))==X);
    solve(X/Y); solve(Y);
}
```

### MuYC（★★★★☆）
- **亮点**：详细注释与高精度乘法实现，适合教学
- **技巧**：先筛小质数优化分解效率，避免 Pollard-Rho 处理小因子

## 4. 最优思路提炼
- **分解优化**：先筛小质数（≤1e6），剩余数分类处理
- **平方数特判**：`sqrt(a_i)` 判断是否为平方数
- **高精度技巧**：浮点数计算 $2^{cnt}$ 转字符串后减一
- **关键代码**（浮点数转字符串减一）：
```cpp
sprintf(ans,"%.Lf",powl(2.0L,cnt));
ans[strlen(ans)-1]--; // 直接操作字符串末位
```

## 5. 同类题目与套路
- **通用套路**：
  1. 质因数分解是数论核心，常用 Pollard-Rho + Miller-Rabin
  2. 最大公约数分解法处理复合数
- **类似题目**：
  - P4718 【模板】Pollard-Rho
  - P1069 细胞分裂（质因数次数统计）
  - P2043 质因数分解（高精度统计）

## 6. 个人心得摘录
- **调试教训**：剩余数需多次与其他数求 GCD，否则漏分解（skylee）
- **顿悟点**：无法分解的剩余数若与其他数互质，不影响全局统计（kczno1）

## 7. 可视化方案设计

### 像素风格动画（Canvas 实现）
- **颜色标记**：
  - 红色：待分解的数
  - 绿色：已分解的小质数
  - 蓝色：大质数
- **分解动效**：
  1. 初始显示所有输入的 $a_i$ 方块
  2. 小质数筛阶段：红色块分裂成绿色小方块（质数）
  3. 剩余数处理：红色块爆炸成蓝色块（大质数）或黄色块（复合数）
- **音效**：
  - `分解成功`：8-bit 上升音阶
  - `找到最大k`：经典马里奥通关音效

### 自动演示逻辑
```javascript
function autoSolve() {
    decomposeSmallPrimes(); // 小质数分解动画
    checkSquares();         // 平方数检测动画
    millerRabinTest();      // 质数检测粒子效果
    handleRemaining();      // 剩余数GCD分解
    calculateResults();     // 统计结果并高亮
}
```

## 8. 核心代码片段
### 质数检测与分解（MuYC 题解）
```cpp
bool Miller_Rabin(ll x) {
    if(x < 2) return false;
    for(int i=1; i<=10; ++i) {
        ll a = rand()%(x-1)+1;
        if(quick_pow(a, x-1, x) != 1) return false;
    }
    return true;
}

void Pollard(ll x) {
    if(x == 1) return;
    if(Miller_Rabin(x)) { factors[x]++; return; }
    ll p = x;
    while(p >= x) p = PR_Algorithm(x); // Pollard-Rho 核心
    Pollard(p); Pollard(x/p);
}
```

### 高精度处理（Leasier 题解）
```cpp
void print_ans(int cnt) {
    long double pow_val = powl(2.0L, cnt);
    sprintf(buf, "%.0Lf", pow_val); // 直接转字符串
    buf[strlen(buf)-1]--; // 末位减一无需借位
    printf("%s", buf);
}
```

---
处理用时：75.09秒