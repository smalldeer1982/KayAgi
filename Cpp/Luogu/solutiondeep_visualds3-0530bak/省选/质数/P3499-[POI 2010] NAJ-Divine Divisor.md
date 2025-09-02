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



### 唯一算法分类
**质因数分解（Pollard-Rho算法与Miller-Rabin素性测试）**

---

### 综合分析与结论
#### 核心算法流程
1. **质因数分解**  
   - 预处理小质数（≤1e6），分解所有数的小质因子  
   - 剩余数分为四类：1、平方数、质数、无法直接分解的合数  
   - 使用 Miller-Rabin 判断质数，Pollard-Rho 分解合数  
   - 对无法分解的合数，通过两两求 GCD 进一步分解  
2. **统计与计算**  
   - 统计所有质因子的出现次数，最大值即答案 k  
   - 统计达到 k 的质因子数量 cnt，最终答案为 2^cnt - 1  
   - 高精度优化：用浮点数计算 2^cnt 后转字符串手动减一  

#### 解决难点
- **大数分解**：Pollard-Rho 算法应对 1e18 范围数据  
- **效率优化**：预处理小质数减少 Pollard-Rho 调用次数  
- **特殊情况处理**：平方数、复合数的分解策略  
- **高精度处理**：避免直接实现大数运算，利用浮点特性优化  

#### 可视化设计思路
- **像素动画**：在 Canvas 网格中展示每个数的分解过程  
  - 初始状态：所有数显示为灰色方块  
  - 分解过程：被分解的数闪烁，分解出的质因子以不同颜色弹出  
  - 统计面板：右侧实时更新质因子频次排行榜（按出现次数排序）  
- **音效交互**：  
  - 发现新质因子：播放 8-bit "升级" 音效  
  - 触发 GCD 分解：播放短促 "点击" 音效  
  - 计算完成：播放经典 FC 过关音乐  
- **自动演示模式**：  
  - 按步骤分解所有数，单步间隔可调（0.5s~3s）  
  - 支持暂停观察当前质因子分布  

---

### 题解评分（≥4星）
1. **skylee（5星）**  
   - 亮点：完整覆盖四类剩余数处理，代码逻辑清晰  
   - 优化：通过两两 GCD 解决未分解合数，避免遗漏质因子  

2. **Kreado（4.5星）**  
   - 亮点：直接调用 Pollard-Rho 分解，代码简洁  
   - 不足：未显式处理平方数等特殊情况  

3. **MuYC（4星）**  
   - 亮点：详细注释与高精度实现，适合教学  
   - 特色：独立统计未分解数，保证计数准确性  

---

### 关键代码实现（skylee 题解核心）
```cpp
// 处理剩余数的四种情况
for(register int i=1;i<=m;i++) {
    if(a[i]==1||b[i]) continue;
    if(floor(sqrt(a[i]))==ceil(sqrt(a[i]))) { // 平方数判断
        cnt[sqrt(a[i])]+=2;
        continue;
    }
    if(miller_rabin(a[i])) { // 质数判断
        cnt[a[i]]++;
        continue;
    }
    // 合数通过 GCD 分解
    for(register int j=1;j<=m;j++) {
        const int64 d=std::__gcd(a[i],a[j]);
        if(d==1) continue;
        cnt[d]++; cnt[a[i]/d]++; // 分解成功
        break;
    }
}
```

---

### 同类型题与算法套路
1. **质因数分解模板题**  
   - 洛谷 P4718【模板】Pollard-Rho算法  
   - 核心：完全依赖 Pollard-Rho 分解大数  

2. **最大公约数应用**  
   - 洛谷 P1075 质因数分解  
   - 关键：n 为两质数乘积时的特殊性质  

3. **高精度与数论结合**  
   - 洛谷 P1604 B进制星球  
   - 共性：需处理大数运算与进制转换  

---

### 推荐练习题
1. **P4718** - Pollard-Rho 模板题  
2. **P1068** - 数论+排序应用  
3. **P2424** - 约数和定理实践  

---

### 个人心得摘录
> "Pollard-Rho 的随机性需要合理设置参数，尤其是复合数分解时，通过倍增优化可显著减少无效计算。实际调试中发现，预处理小质数后剩余数的分解成功率达 99% 以上。" —— skylee

---

### 复古像素化演示方案
**HTML/JS 核心伪代码**  
```javascript
class FactorAnimation {
  constructor(nums) {
    this.canvas = document.getElementById("grid"); // 600x400 像素画布
    this.nums = nums.map(n => new PixelNumber(n)); // 数字像素化
    this.factors = new Map(); // 质因子统计
  }

  async autoRun() {
    for(let num of this.nums) {
      num.highlight(); // 当前数黄色闪烁
      await this.decompose(num);
      num.markDone();  // 标记为绿色
    }
    this.showResult(); // 显示结果面板
  }

  async decompose(num) {
    // 分解过程动画...
  }
}
```
**交互设计**  
- 方向键控制动画速度（←减速，→加速）  
- 空格键暂停/继续  
- ESC 键重置演示  

---

**可视化总结**  
通过像素动画直观展现大数分解的 "分而治之" 思想，结合游戏化元素降低算法理解门槛，适合初学者建立数论问题的空间思维模型。

---
处理用时：84.20秒