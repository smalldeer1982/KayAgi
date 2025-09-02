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



## 唯一算法分类
Pollard-Rho 算法（大数质因数分解算法）

---

## 综合分析与结论

### 题解核心思路与难点解析
1. **算法核心流程**
   - **Miller-Rabin 素性测试**：通过固定基底（如 [2,3,5,7,11,13,17,19,23,29,31,37]）实现确定性判断，处理 2^64 范围内的质数判定
   - **Pollard-Rho 分解逻辑**：
     - 伪随机函数生成序列：$f(x)=(x^2+c)\ mod\ n$
     - Floyd 判圈法检测循环（龟兔赛跑策略）
     - 倍增优化（每 127 次累积差值求 GCD）
   - **递归分解因子**：对分解出的因子递归应用 Pollard-Rho，记录最大质因子

2. **关键难点与解决方案**
   - **大数运算溢出**：使用 `__int128` 处理乘法取模
   - **随机性优化**：通过伪随机序列生成和多次重试避免死循环
   - **效率瓶颈**：倍增优化减少 GCD 计算次数，位运算加速 GCD

### 可视化设计思路
![Pollard-Rho 算法流程动画示意图](https://oi-wiki.org/math/number-theory/images/pollard-rho1.png)
- **动画方案**：
  1. **伪随机序列生成**：展示 $x_i=(x_{i-1}^2+c)\ mod\ n$ 的生成过程，红色高亮当前计算节点
  2. **Floyd 判圈**：用龟兔指针（蓝/绿色）展示快慢指针移动，相遇时触发环检测
  3. **GCD 计算**：黄色闪烁标注差值累积过程，命中因子时全屏闪烁
- **复古像素风格**：
  - **调色板**：8-bit 风格（黑背景+霓虹色高亮）
  - **音效**：伪随机数生成时播放 8-bit 电子音效，命中因子时播放《超级马里奥》金币音效
  - **Canvas 网格**：将数值映射为像素块，指针移动时产生拖尾光效

---

## 题解清单（≥4星）

1. **LinearODE（★★★★☆）**
   - **亮点**：完整推导生日悖论与二次探测，倍增优化代码清晰
   - **代码段**：
     ```cpp
     inline ll PR(ll x){
         ll s=0,t=0,c=rand()%(x-1)+1;
         for(int lim=1;;lim<<=1,s=t){
             ll val=1;
             for(int stp=1;stp<=lim;stp++){
                 t = (mul(t,t,x)+c) % x;
                 val = mul(val, abs(t-s), x);
                 if(stp%127==0)
                     if(ll d=gcd(val,x); d>1) return d;
             }
             if(ll d=gcd(val,x); d>1) return d;
         }
     }
     ```

2. **warzone（★★★★★）**
   - **亮点**：确定性 Miller-Rabin 实现，时间复杂度分析透彻
   - **优化点**：固定前 12 个质数基底，代码可移植性强

3. **Piwry（★★★★☆）**
   - **亮点**：位运算加速 GCD，Floyd 判圈与倍增混合优化
   - **调试心得**：特别处理 n=4 的边界情况，避免死循环

---

## 最优技巧提炼

### 核心技巧
1. **倍增优化**：每 127 次累积差值求 GCD，减少模运算次数
   ```cpp
   if(stp%127==0)
       if(ll d=gcd(val,x); d>1) return d;
   ```
2. **位运算 GCD**：通过 `__builtin_ctzll` 快速计算二进制末尾零
   ```cpp
   ll gcd(ll a,ll b){
       if(!a||!b) return a|b;
       int shift=__builtin_ctzll(a|b);
       a >>= __builtin_ctzll(a);
       do{
           b >>= __builtin_ctzll(b);
           if(a>b) swap(a,b);
           b-=a;
       }while(b);
       return a<<shift;
   }
   ```
3. **确定性 Miller-Rabin**：固定基底覆盖 2^64 范围
   ```cpp
   const int primes[]={2,3,5,7,11,13,17,19,23,29,31,37};
   ```

### 同类型题套路
- **大数分解**：均需 Miller-Rabin + Pollard-Rho 组合
- **质数特性验证**：结合费马小定理与二次探测
- **快速 GCD**：适用于需要高频计算公约数的场景

---

## 推荐相似题目
1. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075) - 基础质因数分解应用
2. [P4139 扩展欧拉定理](https://www.luogu.com.cn/problem/P4139) - 大数取模与数论定理
3. [P5431 乘法逆元](https://www.luogu.com.cn/problem/P5431) - 快速幂与模运算优化

---

## 可视化代码片段（JS Canvas）

```javascript
// 伪随机序列生成动画
class PollardRhoViz {
    constructor(canvas, n) {
        this.ctx = canvas.getContext('2d');
        this.n = n;
        this.nodes = new Map(); // 保存节点位置
        this.trail = [];        // 指针移动轨迹
    }

    drawNode(x, color) {
        const pos = (x * 300 / this.n) % 300; // 映射到 Canvas 坐标
        this.ctx.fillStyle = color;
        this.ctx.fillRect(pos, pos, 10, 10);  // 绘制方块
        this.trail.push({x:pos, y:pos, alpha:1});
    }

    animate() {
        this.ctx.clearRect(0,0,300,300);
        // 绘制轨迹拖尾
        this.trail.forEach(p => {
            this.ctx.fillStyle = `rgba(0,255,0,${p.alpha})`;
            this.ctx.fillRect(p.x, p.y, 10, 10);
            p.alpha -= 0.1;
        });
        this.trail = this.trail.filter(p => p.alpha > 0);
        
        // 更新伪随机数生成
        const c = 1, x = (prevX * prevX + c) % n;
        this.drawNode(x, '#FF0000'); // 红色表示当前节点
        requestAnimationFrame(() => this.animate());
    }
}
```

---

## 个人调试心得摘录
> **@Piwry**  
> 调试时发现 `x=4` 会导致死循环，必须特殊处理  
> **@FutaRimeWoawaSete**  
> 使用 `__int128` 处理乘法后性能提升 30%，但需注意编译器兼容性  
> **@TheLostWeak**  
> 倍增参数 127 是试错得出，128 会显著增加无效 GCD 计算

---
处理用时：93.86秒