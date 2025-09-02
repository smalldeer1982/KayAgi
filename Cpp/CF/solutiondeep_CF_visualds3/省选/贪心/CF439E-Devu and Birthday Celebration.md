# 题目信息

# Devu and Birthday Celebration

## 题目描述

Today is Devu's birthday. For celebrating the occasion, he bought $ n $ sweets from the nearby market. He has invited his $ f $ friends. He would like to distribute the sweets among them. As he is a nice guy and the occasion is great, he doesn't want any friend to be sad, so he would ensure to give at least one sweet to each friend.

He wants to celebrate it in a unique style, so he would like to ensure following condition for the distribution of sweets. Assume that he has distributed $ n $ sweets to his friends such that $ i^{th} $ friend is given $ a_{i} $ sweets. He wants to make sure that there should not be any positive integer $ x&gt;1 $ , which divides every $ a_{i} $ .

Please find the number of ways he can distribute sweets to his friends in the required way. Note that the order of distribution is important, for example \[1, 2\] and \[2, 1\] are distinct distributions. As the answer could be very large, output answer modulo $ 1000000007 $ $ (10^{9}+7) $ .

To make the problem more interesting, you are given $ q $ queries. Each query contains an $ n $ , $ f $ pair. For each query please output the required number of ways modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

For first query: $ n=6,f=2 $ . Possible partitions are \[1, 5\] and \[5, 1\].

For second query: $ n=7,f=2 $ . Possible partitions are \[1, 6\] and \[2, 5\] and \[3, 4\] and \[4, 3\] and \[5, 3\] and \[6, 1\]. So in total there are 6 possible ways of partitioning.

## 样例 #1

### 输入

```
5
6 2
7 2
6 3
6 4
7 4
```

### 输出

```
2
6
9
10
20
```

# AI分析结果


### 💡 Kay的C++算法解析：Devu and Birthday Celebration 深入学习指南 💡

#### 1. 题目解读与核心算法识别  
✨ **本题主要考察**：`数学容斥/莫比乌斯反演` + `组合数学`  

🗣️ **初步分析**：  
> 这道题像在玩「像素地牢分糖果」游戏：Devu要把$n$块糖果分给$f$个朋友（每人至少1块），但要求所有朋友分到的糖果数不能有共同度量单位（即gcd=1）。核心思路是：  
> - **容斥原理**：想象一个"反诅咒系统"——先计算所有分法（包括gcd>1的"诅咒分法"），再通过魔法符文（容斥系数）解除诅咒。  
> - **组合数学**：用"糖果隔板法"计算分法数——$n$块糖果间放$f-1$个隔板（$\binom{n-1}{f-1}$种分法）。  
>  
> **关键难点**：直接计算gcd=1困难，需枚举公约数$d$，用莫比乌斯函数$\mu(d)$作容斥系数：  
> $$ANS = \sum_{d|n} \mu(d) \cdot \binom{\frac{n}{d}-1}{f-1}$$  
>  
> **可视化设计**：  
> - **像素动画**：8-bit风格展示糖果分割过程。当枚举$d$时，屏幕左侧显示$d$的像素标签（如$d=2$时显示🔵），右侧用隔板动画演示$\frac{n}{d}$块糖果的分法。  
> - **交互特效**：正贡献（$\mu(d)=1$）时播放"叮🎵"音效+绿色高亮；负贡献（$\mu(d)=-1$）时播放"砰💥"音效+红色闪烁。  

---

#### 2. 精选优质题解参考  
**题解一（EDqwq）**  
* **点评**：  
  思路直击要害——用莫比乌斯反演将gcd=1转化为求和式，隔板法应用清晰。代码中预处理阶乘、逆元和$\mu$函数，查询时$O(\sqrt{n})$枚举约数，效率极高。亮点在于$\mu$函数与组合数的完美结合，边界处理严谨（如$C(n,m)$中$n<m$返回0），竞赛实战价值高。  

**题解二（MCAdam）**  
* **点评**：  
  公式推导详尽，从求和式逐步展开到莫比乌斯反演，教学性强。代码模块化优秀：`init()`预处理、`C()`组合数、`main()`逻辑分层清晰。特别值得学习的是用`vector`存储质数，空间利用高效，且复杂度$O(n+q\sqrt{n})$完全达标。  

**题解三（szh_AK_all）**  
* **点评**：  
  独创性质因子乘积容斥法，通过六重循环预处理容斥系数（$t[i]$）。优势在于避免$\mu$函数，改用质因子奇偶性判断符号。虽然预处理稍复杂，但查询时直接调用$t[i]$，体现了"空间换时间"的优化思想。  

---

#### 3. 核心难点辨析与解题策略  
1. **难点1：如何将gcd=1转化为可计算形式？**  
   * **分析**：正难则反！通过容斥原理或莫比乌斯反演，将条件转化为枚举公约数$d$的加权和。关键突破：$\sum_{d|n}\mu(d)=[n=1]$。  
   * 💡 **学习笔记**：莫比乌斯函数$\mu$是容斥的"魔法符文"，专治gcd约束。  

2. **难点2：如何高效计算组合数？**  
   * **分析**：预处理阶乘$fac[i]$及逆元$inv[i]$！利用$C(n,m)=fac[n]\cdot inv[m]\cdot inv[n-m]$实现$O(1)$查询。模运算下需用费马小定理求逆元。  
   * 💡 **学习笔记**：阶乘预处理是组合问题的"万能钥匙"，逆元是模世界的"倒数镜"。  

3. **难点3：如何降低查询复杂度？**  
   * **分析**：$O(n)$枚举约数不可取！通过$\sqrt{n}$对称枚举：若$d$是约数，则$n/d$也是约数。将复杂度压至$O(\sqrt{n})$。  
   * 💡 **学习笔记**：约数枚举要成对抓捕，避免重复计算。  

✨ **解题技巧总结**：  
- **技巧1：容斥的两种面孔**——质因子容斥（$t[i]$法）或莫比乌斯反演（$\mu(d)$法）  
- **技巧2：组合数三板斧**——预处理阶乘、线性求逆元、边界判$n<m$  
- **技巧3：约数枚举对称术**——用$d \leq \sqrt{n}$触发$d$与$n/d$双计算  

---

#### 4. C++核心代码实现赏析  
**本题通用核心C++实现参考**  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7;

int fac[N], inv[N], mu[N];
vector<int> primes;
bool isprime[N];

void init() {
    // 预处理阶乘和逆元
    fac[0] = 1;
    for (int i = 1; i < N; i++) 
        fac[i] = 1LL * fac[i-1] * i % mod;
    inv[N-1] = [](int a,int p=mod-2){int r=1;while(p){if(p&1)r=1LL*r*a%mod;a=1LL*a*a%mod;p>>=1;}return r;}(fac[N-1]);
    for (int i = N-2; i >= 0; i--)
        inv[i] = 1LL * inv[i+1] * (i+1) % mod;
    
    // 预处理莫比乌斯函数
    for (int i = 1; i < N; i++) mu[i] = 1;
    memset(isprime, true, sizeof isprime);
    isprime[0] = isprime[1] = false;
    for (int i = 2; i < N; i++) {
        if (isprime[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if (i * p >= N) break;
            isprime[i * p] = false;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            } else {
                mu[i * p] = -mu[i];
            }
        }
    }
}

int C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return 1LL * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int main() {
    init();
    int q; cin >> q;
    while (q--) {
        int n, f; cin >> n >> f;
        int ans = 0;
        for (int d = 1; d * d <= n; d++) {
            if (n % d) continue;
            // 对称枚举约数d和n/d
            if (n/d >= f) 
                ans = (ans + mu[d] * C(n/d - 1, f - 1)) % mod;
            if (d != n/d && d >= f) 
                ans = (ans + mu[n/d] * C(d - 1, f - 1)) % mod;
        }
        cout << (ans % mod + mod) % mod << endl;
    }
}
```

**代码解读概要**：  
1. `init()`预加工三件套：阶乘$fac$、逆元$inv$、莫比乌斯函数$\mu$  
2. $C(n,m)$中严判边界：$n<m$时返回0  
3. 主查询中$\sqrt{n}$枚举约数，利用$\mu(d)$加权组合数  

---

#### 5. 算法可视化：像素动画演示  
![](https://via.placeholder.com/600x200/000000/FFFFFF?text=8-bit+Pixel+Animation+Placeholder)  
* **动画主题**："Devu的容斥大冒险"（复古RPG风格）  
* **核心机制**：  
  - **场景**：左侧糖果堆（$n$个🍬），右侧朋友队列（$f$个👦）  
  - **Step 1**：枚举$d$时，$d$显示为像素标签（如🔵=2）  
  - **Step 2**：计算$\frac{n}{d}$时，糖果自动分组（$n=6,d=2$ → 3组🍬🍬🍬）  
  - **Step 3**：插板过程可视化——光标在糖果间隙移动，按空格放置隔板  
  - **容斥特效**：  
    - $\mu(d)=1$ → 绿色✅ + "叮✨"声  
    - $\mu(d)=-1$ → 红色❌ + "轰💥"声  
* **控制面板**：  
  ```markdown
  [▶] 自动播放  [≫] 单步  [↻] 重置
  速度：▁▃▅▆▇ (滑块调节)
  ```
* **音效设计**：  
  - 背景音乐：8-bit风格循环BGM  
  - 关键操作：隔板放置声(咔嗒)、容斥生效声(叮/轰)  
  - 胜利通关：当最终$ANS>0$时播放经典FC过关音乐  

---

#### 6. 拓展练习与相似问题思考  
1. **同类问题迁移**：  
   - 带下界约束的整数划分（如P1246 编码问题）  
   - 多维容斥（如P1450 硬币购物）  
   - 结合质因数分解的计数（如P1064 金明的预算方案）  

2. **洛谷推荐**：  
   - **P2306 被yyh虐的mzc**  
     🗣️ *推荐理由*：强化容斥原理应用，需处理背包约束  
   - **P2512 分糖果**  
     🗣️ *推荐理由*：环形分配问题，练习边界思维  
   - **P1450 硬币购物**  
     🗣️ *推荐理由*：四维容斥经典，掌握"全集-非法"套路  

---

#### 7. 学习心得与经验分享  
> **来自题解作者的调试经验**：  
> *"组合数边界陷阱是血泪教训！一定要加`if(n<m) return 0`，否则n=0,m=1时阶乘逆元计算会炸..."*  
>  
> **Kay的总结**：数学代码需三重防御：  
> 1️⃣ 输入验证：`if(n<f)`提前返回0  
> 2️⃣ 组合数边界：`C(n,m)`中严判`n>=m>0`  
> 3️⃣ 负数的模：`(ans%mod+mod)%mod`确保非负  

---  
**结语**：通过分糖果理解容斥，就像用像素游戏学习数学——复杂概念瞬间生动！记住：$\mu$函数是解除诅咒的符文，组合数是分割糖果的圣剑。下次挑战见！🎮🚀

---
处理用时：204.15秒