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



# 算法分类
**质因数分解与数论**

---

## 综合分析与结论
### 核心思路
1. **质因数分解优化**：预处理小质数（≤1e6）加速分解，剩余大数分情况处理（平方数、质数、合数）
2. **Pollard-Rho算法**：处理无法用小质数分解的大数，结合Miller-Rabin素性测试
3. **次数统计**：维护哈希表统计所有质因子出现次数，寻找最大次数k及对应质因子数量num
4. **结果计算**：最终答案为2^num-1，使用浮点数转字符串优化高精度

### 解决难点
- **大数分解**：通过Pollard-Rho算法实现O(n^1/4)分解
- **平方数检测**：用sqrt取整判断避免遗漏平方因子
- **高精度处理**：2^num可能达600位，通过long double转字符串后末位减1

### 可视化设计
1. **像素化分解动画**：
   - 用不同颜色方块表示质因子（红：小质数，蓝：大质数）
   - 分解时展示质因子"爆破"效果，伴随8-bit音效
2. **统计面板**：
   - 动态柱状图显示质因子次数排名，最大k值高亮
   - 计算2^num时显示二进制位增长动画
3. **自动演示模式**：
   - 模拟AI自动分解质因数，可调速观察关键步骤
   - 错误路径播放短促"失败音效"，成功找到k值播放胜利音效

---

## 题解清单（≥4星）

### 1. skylee（★★★★☆）
- **亮点**：预处理1e6内质数显著加速分解，四类情况分类清晰
- **代码优化**：使用gcd碰撞分解合数，避免全面Pollard-Rho
- **高精度技巧**：ldexpl直接计算2^num，字符串末位减1

### 2. Kreado（★★★★☆）
- **亮点**：完整实现Pollard-Rho+Miller-Rabin模板
- **代码简洁性**：统一质因子统计逻辑，无冗余分类
- **高精度处理**：powl计算2^num，直接操作字符串减1

### 3. MuYC（★★★★☆）
- **教学价值**：详细注释分解过程，适合学习Pollard-Rho
- **高精度实现**：手动实现字符串乘法，避免浮点精度问题
- **优化点**：分离小质数处理，减少Pollard-Rho调用次数

---

## 最优思路与代码实现
### 核心代码（skylee版关键片段）
```cpp
// 预处理小质数分解
for(int j=1;j<=p[0]&&a[i]!=1;j++){
    while(a[i]%p[j]==0){
        a[i]/=p[j];
        cnt[p[j]]++;
    }
}

// 处理大质数情况
if(floor(sqrt(a[i]))==ceil(sqrt(a[i]))){
    cnt[sqrt(a[i])]+=2; //平方数情况
} else if(miller_rabin(a[i])){ 
    cnt[a[i]]++; //单一质数
} else { //合数尝试gcd分解
    for(int j=1;j<=m;j++){
        const int64 d=std::__gcd(a[i],a[j]);
        if(d!=1) cnt[d]++, cnt[a[i]/d]++;
    }
}

// 结果计算
sprintf(ans,"%.Lf",ldexpl(1,ans2)); //浮点转2^num
ans[strlen(ans)-1]--; //末位减1
```

---

## 相似题目推荐
1. **P4718** 【模板】Pollard-Rho算法
2. **P1069** 小明的随机数（质因数分解应用）
3. **P1075** 质因数分解（基础版）

---

## 个人心得摘录
> "处理大数分解时，先筛除小质因子能大幅提升效率。遇到无法分解的合数时，与其他数取gcd往往能找到隐藏因子" —— skylee

> "2^num-1的高精度计算，直接操作字符串末位比写完整高精度减法快10倍" —— Kreado

---

## 复古游戏化动画设计
### 交互要素
1. **像素风格**：使用16色调色板，质因数显示为8x8像素块
2. **音效系统**：
   - 分解成功：短促"哔"声（Web Audio合成方波）
   - 找到最大k值：播放FC游戏通关音效
3. **自动演示AI**：
   ```javascript
   function autoDecompose(){
       highlight(currentNumber);
       playSound('scan');
       if(checkSmallPrimes()){ //优先尝试小质数
           explodeAnimation(currentPrime);
       }else{
           startPollardRho(); //启动随机分解动画
       }
   }
   ```
4. **积分系统**：
   - 快速分解小质数得10分/个
   - 成功分解大质数得50分
   - 错误尝试扣5分

---

通过这种多维度解析与可视化设计，学习者既能掌握质因数分解的核心算法，又能通过互动体验加深对Pollard-Rho等高级数论方法的理解。

---
处理用时：61.97秒