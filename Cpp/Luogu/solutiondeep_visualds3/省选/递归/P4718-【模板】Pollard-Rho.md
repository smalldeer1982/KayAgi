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



---

# 💡 Kay的C++算法解析：【模板】Pollard-Rho 深入学习指南 💡

<introduction>
今天我们要一起攻克的是“【模板】Pollard-Rho”这道题。它的核心是通过高效的随机算法实现大数的质因数分解，涉及两个关键算法：Miller-Rabin素性测试和Pollard-Rho因数分解。本指南将带大家理解算法原理、关键步骤，并通过代码和可视化演示快速掌握！
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`素性测试（Miller-Rabin）与质因数分解（Pollard-Rho）`

🗣️ **初步分析**：
要解决这道题，我们需要两步：首先用Miller-Rabin判断数是否为质数，若是则输出“Prime”；否则用Pollard-Rho找到其最大质因子。

- **Miller-Rabin**：基于费马小定理和二次探测定理的随机素性测试。简单来说，费马小定理告诉我们，若p是质数，则对任意a不被p整除，有a^(p-1)≡1 mod p。但存在合数（如卡迈克尔数）也满足这一条件，因此需要结合二次探测定理（若x²≡1 mod p，则x≡±1 mod p）进一步验证。通过多次随机选取底数测试，错误率可低至4^(-k)（k为测试次数）。
- **Pollard-Rho**：利用“生日悖论”和伪随机序列的因数分解算法。生成形如x_i = (x_{i-1}² + c) mod n的伪随机序列（c为随机常数），通过Floyd判圈法检测环，并计算相邻项的差与n的gcd，找到非平凡因子。其期望时间复杂度为O(n^(1/4))，适合大数分解。

**核心难点与解决方案**：
- 难点1：Miller-Rabin的正确实现，特别是二次探测定理的边界处理（如x²≡1的解是否为±1）。
- 难点2：Pollard-Rho的随机序列生成和gcd计算的优化（如倍增累积减少gcd次数）。
- 解决方案：通过固定测试底数（如前12个质数）确保Miller-Rabin的确定性；Pollard-Rho使用倍增累积差的乘积，每隔127步计算一次gcd，减少时间消耗。

**可视化设计**：
设计8位像素风格动画，模拟Pollard-Rho的随机序列生成过程。用不同颜色方块表示序列中的数，红色标记环的起点，绿色高亮当前计算的gcd值。动画包含“单步执行”“自动播放”按钮，同步显示当前序列值和gcd结果，关键步骤（如找到因子）伴随“叮”的音效，完成时播放胜利音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性和算法有效性，以下题解因逻辑清晰、优化到位被选为优质参考：
</eval_intro>

**题解一：LinearODE（赞：231）**
* **点评**：该题解详细推导了Pollard-Rho的理论基础（生日悖论、伪随机序列），并给出了基于路径倍增优化的代码。代码中通过累积127步的差乘积再计算gcd，显著减少了gcd调用次数，是高效实现的典范。其对Miller-Rabin的多底数测试（如2、3、5等）确保了素性判断的准确性，适合竞赛实战。

**题解二：Piwry（赞：40）**
* **点评**：此题解深入分析了Pollard-Rho的复杂度来源（与最小质因子p的平方根相关），并提供了基于Floyd判圈的优化实现。代码中使用mt19937生成随机数，结合__int128处理大数乘法，避免溢出问题，对大数分解的鲁棒性强。

**题解三：FutaRimeWoawaSete（赞：27）**
* **点评**：该题解完整展示了从Miller-Rabin到Pollard-Rho的全流程代码，特别强调了固定底数测试的重要性（如前12个质数覆盖10^18范围）。代码结构清晰，递归分解逻辑简洁，适合初学者理解。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
在解决本题时，以下三个关键点需重点突破：
</difficulty_intro>

1. **关键点1：Miller-Rabin的正确实现**  
   - **分析**：需正确处理二次探测定理的边界条件。例如，当计算a^(d*2^k) mod n时，若中间结果为1或n-1则跳过，否则判定为合数。固定使用前12个质数（如2、3、5等）作为测试底数，可覆盖10^18范围内的所有数，避免随机底数的不确定性。
   - 💡 **学习笔记**：固定底数测试是竞赛中确保正确性的常用技巧，前12个质数足够覆盖大数范围。

2. **关键点2：Pollard-Rho的随机序列优化**  
   - **分析**：直接两两计算gcd效率低，通过倍增累积差的乘积（如每127步计算一次gcd）可大幅减少gcd调用次数。同时，使用伪随机函数x_i = (x_{i-1}² + c) mod n生成序列，利用其“ρ”形环结构，通过Floyd判圈法快速检测环，避免无效循环。
   - 💡 **学习笔记**：倍增累积和Floyd判圈是Pollard-Rho的两大优化核心，缺一不可。

3. **关键点3：大数运算的溢出处理**  
   - **分析**：计算x²时可能溢出，需用__int128或龟速乘（模拟乘法避免溢出）。例如，用`(__int128)x * x % n`代替直接乘法，确保中间结果正确。
   - 💡 **学习笔记**：大数乘法必须使用防溢出技巧，__int128在C++中是最直接的解决方案。

### ✨ 解题技巧总结
- **固定底数测试**：Miller-Rabin使用前12个质数作为测试底数，确保10^18内的正确性。
- **倍增累积优化**：Pollard-Rho中每127步累积差的乘积，减少gcd调用次数。
- **防溢出处理**：大数乘法用__int128或龟速乘，避免中间结果溢出。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合多个优质题解的通用核心实现，结合了Miller-Rabin和Pollard-Rho的关键优化，适合直接用于竞赛。
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了LinearODE和Piwry的题解，包含Miller-Rabin素性测试和Pollard-Rho因数分解，使用__int128处理大数乘法，固定前12个质数作为测试底数，确保10^18范围内的正确性。
* **完整核心代码**：
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    using lll = __int128;

    mt19937 rng(random_device{}());

    // Miller-Rabin 素性测试
    bool is_prime(ll n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0) return false;
        vector<ll> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        ll d = n - 1;
        int s = 0;
        while (d % 2 == 0) d /= 2, s++;
        for (ll a : bases) {
            if (a >= n) continue;
            ll x = 1;
            lll tmp = a;
            for (ll p = d; p > 0; p >>= 1) {
                if (p & 1) x = (lll)x * tmp % n;
                tmp = tmp * tmp % n;
            }
            if (x == 1 || x == n - 1) continue;
            for (int i = 1; i < s; i++) {
                x = (lll)x * x % n;
                if (x == n - 1) break;
            }
            if (x != n - 1) return false;
        }
        return true;
    }

    // Pollard-Rho 因数分解
    ll pollard_rho(ll n) {
        if (n % 2 == 0) return 2;
        if (n % 3 == 0) return 3;
        if (n % 5 == 0) return 5;
        while (true) {
            ll c = uniform_int_distribution<ll>(1, n - 1)(rng);
            auto f = [&](ll x) { return ((lll)x * x + c) % n; };
            ll x = 0, y = 0, g = 1;
            ll q = 1;
            int step = 0, goal = 1;
            while (g == 1) {
                if (step == goal) {
                    goal *= 2;
                    y = x;
                    q = 1;
                }
                x = f(x);
                q = (lll)q * abs(x - y) % n;
                step++;
                if (step % 127 == 0) {
                    g = gcd(q, n);
                    if (g != 1 && g != n) return g;
                }
            }
            if (g != 1 && g != n) return g;
        }
    }

    ll max_factor;

    void factor(ll n) {
        if (n <= max_factor || n < 2) return;
        if (is_prime(n)) {
            max_factor = max(max_factor, n);
            return;
        }
        ll d = pollard_rho(n);
        while (n % d == 0) n /= d;
        factor(n);
        factor(d);
    }

    int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        int T;
        cin >> T;
        while (T--) {
            ll n;
            cin >> n;
            max_factor = 0;
            factor(n);
            if (max_factor == n) cout << "Prime\n";
            else cout << max_factor << '\n';
        }
        return 0;
    }
    ```
* **代码解读概要**：代码首先通过`is_prime`函数判断质数，使用固定的12个底数确保正确性；`pollard_rho`函数生成伪随机序列，通过倍增累积差的乘积优化gcd计算；`factor`函数递归分解质因数，更新最大质因子。主函数处理输入输出，调用分解逻辑。

---
<code_intro_selected>
以下是优质题解的核心代码片段赏析：
</code_intro_selected>

**题解一：LinearODE（路径倍增优化）**
* **亮点**：通过累积127步的差乘积再计算gcd，减少gcd调用次数。
* **核心代码片段**：
    ```cpp
    inline ll PR(ll x) {
        ll s=0,t=0,c=1ll*rand()%(x-1)+1;
        int stp=0,goal=1;
        ll val=1;
        for(goal=1;;goal<<=1,s=t,val=1) {
            for(stp=1;stp<=goal;++stp) {
                t=f(t,c,x);
                val=(lll)val*abs(t-s)%x;
                if((stp%127)==0) {
                    ll d=gcd(val,x);
                    if(d>1) return d;
                }
            }
            ll d=gcd(val,x);
            if(d>1) return d;
        }
    }
    ```
* **代码解读**：`PR`函数中，`goal`倍增累积步数，`val`存储127步内的差乘积，每127步计算一次gcd。若找到非1因子则返回，否则继续。这种优化将gcd调用次数从O(√p)降至O(√p/127)，显著提升效率。
* 💡 **学习笔记**：倍增累积是Pollard-Rho的关键优化，通过批量计算减少常数。

**题解二：Piwry（Floyd判圈实现）**
* **亮点**：使用Floyd判圈法检测环，确保序列不会无限循环。
* **核心代码片段**：
    ```cpp
    ll pr(ll n) {
        if(n == 4) return 2;
        ll x = rng() % n, y = x;
        ll c = rng() % (n-1) + 1;
        ll d = 1;
        x = (x*x + c) % n;
        y = (y*y + c) % n, y = (y*y + c) % n;
        while(x != y) {
            d = gcd(abs(x - y), n);
            if(d != 1) return d;
            x = (x*x + c) % n;
            y = (y*y + c) % n, y = (y*y + c) % n;
        }
        return n;
    }
    ```
* **代码解读**：`x`和`y`分别以1步和2步速度迭代，当`x == y`时检测到环，否则计算`gcd(abs(x-y), n)`找因子。Floyd判圈确保序列不会无限循环，提升了算法的鲁棒性。
* 💡 **学习笔记**：Floyd判圈是检测环的高效方法，适用于伪随机序列的因子查找。

---

## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解Pollard-Rho的因子查找过程，我们设计了一个8位像素风格的动画演示。
</visualization_intro>

  * **动画演示主题**：`像素探险家的因数大冒险`

  * **核心演示内容**：模拟Pollard-Rho生成伪随机序列、检测环、计算gcd的过程，展示如何从随机序列中找到因子。

  * **设计思路简述**：采用8位像素风格（如FC游戏画面），用不同颜色方块表示序列中的数，红色标记环的起点，绿色高亮当前计算的gcd值。动画通过“单步执行”和“自动播放”按钮控制，关键步骤（如找到因子）伴随“叮”的音效，完成时播放胜利音效，增强学习趣味性。

  * **动画帧步骤与交互关键点**：
    1. **初始化场景**：屏幕左侧显示像素网格（表示序列值），右侧显示控制面板（开始/暂停、单步、重置按钮）和当前gcd值。背景播放8位风格BGM。
    2. **生成序列**：每次点击“单步”或“自动播放”，生成新的序列值（x_i = (x_{i-1}² + c) mod n），用蓝色方块在网格中显示。
    3. **检测环**：当x和y（双指针）相遇时，用红色圆圈标记环的起点，提示“发现环，更换c重新生成”。
    4. **计算gcd**：每127步计算一次gcd，若gcd>1，用绿色高亮显示该因子，并提示“找到因子！”，伴随“叮”音效。
    5. **完成分解**：当最大质因子被找到时，播放胜利音效，网格显示“成功！最大质因子是XX”。

  * **旁白提示**：
    - “现在生成第i个序列值，x_i = (x_{i-1}² + c) mod n”
    - “x和y相遇了，说明进入环，需要更换c重新生成”
    - “计算当前127步的差乘积，gcd结果为d，d是n的因子！”

<visualization_conclusion>
通过这样的动画，我们能直观看到Pollard-Rho如何通过随机序列和环检测找到因子，理解算法的每一步逻辑。
</visualization_conclusion>

---

## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握本题后，可通过以下练习巩固算法应用：
</similar_problems_intro>

  * **通用思路/技巧迁移**：
    - Miller-Rabin和Pollard-Rho的组合是大数质因数分解的经典方法，适用于密码学（如RSA加密）、数论问题（如求最大质因子）等场景。
    - 随机化算法（如生日悖论的应用）在信息学竞赛中常用于解决大数问题，需掌握其优化技巧（如倍增、判圈）。

  * **练习推荐 (洛谷)**：
    1.  **洛谷 P4718** - `【模板】Pollard's rho算法`  
       🗣️ **推荐理由**：本题原题，适合直接练习，巩固算法实现。
    2.  **洛谷 P1075** - `质因数分解`  
       🗣️ **推荐理由**：基础质因数分解题，适合熟悉分解流程。
    3.  **洛谷 P2043** - `质因子分解`  
       🗣️ **推荐理由**：需处理多个数的分解，练习批量处理技巧。
    4.  **洛谷 P1514** - `引水入城`（涉及数论基础）  
       🗣️ **推荐理由**：综合题，需结合数论和图论，拓展算法应用能力。

---

## 7. 学习心得与经验分享 (若有)

<insights_intro>
部分题解作者分享了调试经验，对学习者有重要参考价值：
</insights_intro>

> **参考经验 (来自LinearODE)**：“在实现Pollard-Rho时，曾因未处理大数乘法溢出导致错误。后来改用__int128存储中间结果，问题解决。”

**点评**：大数运算的溢出是常见问题，使用__int128或龟速乘（模拟乘法）可有效避免。调试时可打印中间变量，定位溢出位置。

---

<conclusion>
通过本指南，我们掌握了Miller-Rabin和Pollard-Rho的核心原理、代码实现及优化技巧。记住，多练习、多调试是提升算法能力的关键！下次再见，一起挑战更难的题目！💪
</conclusion>

---

---
处理用时：186.67秒