# 题目信息

# 【模板】Pollard-Rho

## 题目描述

Miller Rabin 算法是一种高效的质数判断方法。虽然是一种不确定的质数判断法，但是在选择多种底数的情况下，正确率是可以接受的。

Pollard rho 是一个非常玄学的方式，用于在 $O(n^{1/4})$ 的期望时间复杂度内计算合数 $n$ 的某个非平凡因子。事实上算法导论给出的是 $O(\sqrt p)$，$p$ 是 $n$ 的某个最小因子，满足 $p$ 与 $n/p$ 互质。但是这些都是期望，未必符合实际。但事实上 Pollard rho 算法在实际环境中运行的相当不错。

这里我们要写一个程序，对于每个数字检验是否是质数，是质数就输出 `Prime`；如果不是质数，输出它最大的质因子是哪个。

## 说明/提示

2018.8.14 新加数据两组，时限加大到 2s，感谢 @whzzt

2022.12.22 加入新的数据，感谢 @ftt2333 和 Library Checker

by @will7101

## 样例 #1

### 输入

```
6
2
13
134
8897
1234567654321
1000000000000```

### 输出

```
Prime
Prime
67
41
4649
5```

# AI分析结果



# Pollard-Rho 算法题解分析

## 唯一算法分类
**随机化算法**

---

## 综合分析与结论
### 核心思路与算法流程
1. **Miller-Rabin 素性测试**  
   - 基于费马小定理与二次探测定理  
   - 通过固定底数（如2,3,5,7等）实现确定性判断  
   - 时间复杂度：$O(k \log^3 n)$，k为测试轮数  

2. **Pollard-Rho 因数分解**  
   - 伪随机函数：$f(x) = x^2 + c \mod n$ 生成序列  
   - 路径倍增优化：每倍增一轮计算一次 GCD，减少计算次数  
   - Floyd 判环算法：检测循环避免死循环  

### 解决难点与优化
- **大数溢出**：使用 `__int128` 或分块乘法避免中间结果溢出  
- **GCD 累积优化**：积累多个差值后再求 GCD，减少计算量  
- **确定性判素**：针对 $n \leq 2^{64}$ 使用固定底数保证正确性  

### 可视化设计要点
1. **动画流程**  
   - 显示伪随机序列生成过程（如数字在模数下的循环轨迹）  
   - 高亮当前比较的差值 $|x_i - x_j|$ 及 GCD 计算结果  
   - 路径倍增时以不同颜色标注倍增区间  

2. **复古像素风格**  
   - 使用 8-bit 风格数字块表示序列值  
   - 循环检测时播放 "beep" 音效，发现因子时触发 "coin" 音效  
   - 背景音乐采用芯片音乐风格循环播放  

---

## 题解清单 (≥4星)

1. **LinearODE（赞231）**  
   - **亮点**：详细推导生日悖论与路径倍增优化  
   - **代码**：实现倍增间隔127优化，减少GCD调用  
   ```cpp
   inline ll PR(ll x) {
       ll s=0,t=0,c=1ll*rand()%(x-1)+1;
       for(int goal=1;;goal<<=1,s=t,val=1) {
           for(stp=1; stp<=goal; ++stp) {
               t = f(t,c,x);
               val = (lll)val * abs(t-s) % x;
               if(stp%127 == 0) {
                   ll d = gcd(val,x);
                   if(d>1) return d;
               }
           }
           ll d = gcd(val,x);
           if(d>1) return d;
       }
   }
   ```

2. **Piwry（赞40）**  
   - **亮点**：完整处理边界条件（如n=4），使用`mt19937`优化随机  
   - **代码**：路径倍增与GCD累积结合  
   ```cpp
   ll getnext(ll x, ll c, ll n) { 
       return ((__int128)x*x + c) % n; 
   }
   ```

3. **TheLostWeak（赞22）**  
   - **亮点**：引入二进制优化的GCD算法  
   ```cpp
   ll gcd(ll a,ll b) {
       if(!a||!b) return a|b;
       int t=__builtin_ctzll(a|b);
       a>>=__builtin_ctzll(a);
       do {
           b>>=__builtin_ctzll(b);
           if(a>b) swap(a,b);
           b-=a;
       } while(b);
       return a<<t;
   }
   ```

---

## 核心代码实现
### Miller-Rabin 确定性判素
```cpp
bool is_prime(ll n) {
    if(n < 2) return false;
    for(ll p : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if(n == p) return true;
        if(n%p == 0) return false;
        ll d = n-1, s = 0;
        while(d%2 == 0) d/=2, s++;
        if(qpow(p,d,n) != 1) {
            bool ok = true;
            for(int i=0; i<s; i++) {
                if(qpow(p, (1LL<<i)*d, n) == n-1) {
                    ok = false; break;
                }
            }
            if(ok) return false;
        }
    }
    return true;
}
```

### Pollard-Rho 路径倍增优化
```cpp
ll pollard_rho(ll n) {
    if(n == 4) return 2;
    ll c = rand()%(n-1)+1;
    ll x = 0, y = 0, t = 0, product = 1;
    auto f = [&](ll x) { return ((__int128)x*x + c) % n; };
    for(int k=1; ; k<<=1) {
        y = x, product = 1;
        for(int i=1; i<=k; i++) {
            x = f(x);
            product = (__int128)product * abs(x-y) % n;
            if(i%127 == 0) {
                ll d = gcd(product, n);
                if(d > 1) return d;
            }
        }
        ll d = gcd(product, n);
        if(d > 1) return d;
    }
}
```

---

## 相似题目推荐
1. **P1075 [NOIP2012 普及组] 质因数分解**  
   - 基础质因数分解应用  
2. **P1069 [NOIP2009 普及组] 细胞分裂**  
   - 质因数分解与指数处理  
3. **P4178 Tree**  
   - 需要高效质因数分解处理路径统计  

---

## 可视化算法演示
### 伪随机序列生成
![Pollard-Rho路径生成动画](https://cdn.luogu.com.cn/upload/image_hosting/yaihaze5.png)
- **红色点**：当前比较的 $x_i$ 和 $x_j$  
- **绿色箭头**：路径倍增区间  
- **黄色高亮**：触发GCD计算的差值  

### 复古像素风格设计
```javascript
// 示例：Canvas绘制伪随机序列
const canvas = document.getElementById('rhoCanvas');
const ctx = canvas.getContext('2d');
const points = [];

function drawPoint(x, y, color='#00FF00') {
    ctx.fillStyle = color;
    ctx.fillRect(x*10, y*10, 8, 8); // 8x8像素块
}

// 播放音效
function playSound(freq=440, duration=0.1) {
    const osc = new OscillatorNode(ctx, {frequency: freq});
    osc.connect(ctx.destination);
    osc.start();
    osc.stop(ctx.currentTime + duration);
}
```

---

## 总结
Pollard-Rho算法的核心在于巧妙利用伪随机序列的数学性质，结合路径倍增和GCD优化实现高效因数分解。在处理大数问题时，需特别注意溢出和随机参数选择。可视化设计通过动态展示路径生成和关键操作，可加深对算法内在机制的理解。

---
处理用时：83.80秒