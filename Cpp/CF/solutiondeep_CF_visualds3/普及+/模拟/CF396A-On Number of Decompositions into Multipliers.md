# 题目信息

# On Number of Decompositions into Multipliers

## 题目描述

You are given an integer $ m $ as a product of integers $ a_{1},a_{2},...\ a_{n} $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF396A/511aaee908ff3da31c1047aebc73037f3c2d6e3f.png). Your task is to find the number of distinct decompositions of number $ m $ into the product of $ n $ ordered positive integers.

Decomposition into $ n $ products, given in the input, must also be considered in the answer. As the answer can be very large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the second sample, the get a decomposition of number 2, you need any one number out of three to equal 2, and the rest to equal 1.

In the third sample, the possible ways of decomposing into ordered multipliers are \[7,5\], \[5,7\], \[1,35\], \[35,1\].

A decomposition of positive integer $ m $ into $ n $ ordered multipliers is a cortege of positive integers $ b={b_{1},b_{2},...\ b_{n}} $ such that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF396A/b461305f46e6043012038c3479cb445ca537b144.png). Two decompositions $ b $ and $ c $ are considered different, if there exists index $ i $ such that $ b_{i}≠c_{i} $ .

## 样例 #1

### 输入

```
1
15
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 1 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2
5 7
```

### 输出

```
4
```

# AI分析结果

# 💡 Kay的C++算法解析：On Number of Decompositions into Multipliers 深入学习指南 💡

<introduction>
今天我们来一起分析“On Number of Decompositions into Multipliers”这道C++编程题。这道题看起来是关于“分解乘积”的计数问题，但其实核心是**组合数学**和**质因数分解**的结合。本指南会帮你拆解问题本质，理解关键算法，并掌握高效解题的技巧！
</introduction>


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：数学（质因数分解）+ 组合数学（隔板法）

🗣️ **初步分析**：
解决这道题的关键，在于把“乘积分解”的问题**转化为质因数的分配问题**——这就像把一堆“相同的小球”（质因数）放进“不同的盒子”（序列的每个位置）里，每个盒子可以放0个或多个小球。 

### 核心思路拆解：
1. **质因数分解的必要性**：直接计算m会溢出（因为a_i可达1e9，n达500，m会大到无法存储）。但根据**唯一分解定理**，m的质因数分解是唯一的——比如m=15=3×5，那么所有满足条件的b序列的质因数总次数，必须和m的完全一致。
2. **隔板法的应用**：对于每个质因数p，假设它总共有x个（比如m=15的3有1个，5有1个），要分配到n个位置（序列的n个元素），允许某个位置不放p。这相当于“把x个相同的球放进n个不同的盒子，允许空盒”，根据组合数学的**隔板法**，方案数是组合数C(n+x-1, n-1)。
3. **独立事件相乘**：每个质因数的分配是独立的，所以总方案数是所有质因数对应组合数的乘积，最后模1e9+7。

### 可视化设计思路：
我会设计一个**8位像素风的“质因数分配游戏”**：
- 用像素盒子代表序列的n个位置（比如n=3时显示3个彩色方块）；
- 用小像素点代表质因数（比如红色点代表3，蓝色点代表5）；
- 动画展示“如何用隔板把质因数分到盒子里”：比如x=2个红色点，n=3个盒子，需要选2个隔板（n-1=2）把点分成3份，每个盒子里的点数就是该位置的质因数次数；
- 关键操作（比如选隔板、分配质因数）会伴随“叮”的像素音效，分配完成后盒子会闪烁提示。


## 2. 精选优质题解参考

<eval_intro>
我从思路清晰度、代码可读性、算法效率等方面筛选了3份优质题解，一起来看看它们的亮点吧！
</eval_intro>

**题解一（作者：__LiChangChao__）**
* **点评**：这份题解的思路非常清晰，完整覆盖了“质因数分解→组合数计算→结果相乘”的核心流程。亮点在于使用了**Lucas定理**计算组合数——虽然本题中组合数的参数并不大（n≤500，x≤log2(1e9)≈30，所以n+x-1≤530），Lucas定理不是必须的，但它展示了处理**大数组合数**的通用方法。代码中的欧拉筛、快速幂、Lucas模板都很规范，适合学习基础算法的实现。

**题解二（作者：Transparent）**
* **点评**：这是一份**效率极高**的题解！亮点有两个：① 预处理阶乘和阶乘的逆元（用费马小定理+倒推法），避免了每次计算组合数时重复计算；② 分解质因数时用埃氏筛预处理质数，加快了分解速度。代码中的`getfac`函数（预处理阶乘和逆元）非常巧妙——逆元通过`invfac[i] = invfac[i+1]*(i+1)%Mod`倒推，比每次用快速幂求逆元快得多！

**题解三（作者：orz_z）**
* **点评**：这份题解的代码风格非常简洁，用`#define int long long`避免了类型溢出的问题（比如组合数计算时的乘法溢出）。分解质因数的逻辑和题解二一致，但代码更紧凑。适合学习“如何用简洁的代码实现复杂逻辑”。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
这道题的难点不在代码本身，而在**问题的转化**和**组合数学的应用**。我提炼了3个核心关键点，帮你突破瓶颈：
</difficulty_intro>

1. **关键点1：为什么要分解质因数？**
    * **分析**：直接计算m会溢出（比如n=500，每个a_i=1e9，m=1e4500，根本无法存储）。但质因数分解是唯一的——所有满足条件的b序列的质因数总次数，必须和原序列a的质因数总次数完全一致。比如原序列a是[1,1,2]（m=2），质因数2有1个，那么b序列的质因数2的总次数也必须是1，其他质因数次数为0。
    * 💡 **学习笔记**：遇到“乘积计数”问题，优先考虑质因数分解，把问题转化为“质因数的分配”！

2. **关键点2：隔板法的应用场景？**
    * **分析**：隔板法适用于“将相同的物品分到不同的盒子，允许空盒”的场景。公式是C(n+x-1, n-1)——其中x是物品数，n是盒子数。比如x=1（质因数2有1个），n=3（序列长度3），方案数是C(3+1-1,3-1)=C(3,2)=3，对应样例2的输出。
    * 💡 **学习笔记**：记住隔板法的两个核心条件——物品相同、盒子不同，允许空盒！

3. **关键点3：组合数如何高效计算？**
    * **分析**：因为结果要模1e9+7（质数），所以可以用**费马小定理**求逆元：若p是质数，则a的逆元是a^(p-2) mod p。为了避免重复计算，我们可以**预处理阶乘和阶乘的逆元**——阶乘fac[i] = i! mod Mod，逆元invfac[i] = (i!)^{-1} mod Mod。这样组合数C(a,b) = fac[a] * invfac[b] * invfac[a-b] mod Mod，计算速度极快！
    * 💡 **学习笔记**：预处理阶乘和逆元是计算组合数的“常规操作”，一定要掌握！

### ✨ 解题技巧总结
- **问题转化**：把“乘积分解”转化为“质因数分配”，避免处理大数；
- **预处理优化**：预处理质数、阶乘、逆元，加快计算速度；
- **模运算注意**：所有乘法都要取模，避免溢出；逆元计算用费马小定理更高效。


## 4. C++核心代码实现赏析

<code_intro_overall>
先看一份**综合优质题解思路的通用核心代码**，它结合了预处理阶乘逆元的高效性和清晰的逻辑：
</code_intro_overall>

**本题通用核心C++实现参考**
* **说明**：本代码综合了题解二和题解三的思路，预处理阶乘和逆元以提高效率，适合大多数情况。
* **完整核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_PRIME = 4e5;  // 预处理质数到4e5（足够分解1e9的数）
const int MAX_FAC = 5e3 + 10;  // 最大组合数参数：n+x-1 ≤500+30=530
const long long MOD = 1e9 + 7;

bool is_prime[MAX_PRIME + 1];
vector<int> primes;
map<int, int> prime_cnt;  // 存储每个质因数的总次数
long long fac[MAX_FAC], invfac[MAX_FAC];

// 埃氏筛预处理质数
void sieve() {
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= MAX_PRIME; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * 2; j <= MAX_PRIME; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

// 分解质因数：将x分解，统计到prime_cnt中
void factorize(int x) {
    for (int p : primes) {
        if (p * p > x) break;
        while (x % p == 0) {
            prime_cnt[p]++;
            x /= p;
        }
    }
    if (x != 1) {  // 剩余的x是质数
        prime_cnt[x]++;
    }
}

// 快速幂：计算a^b mod MOD
long long quick_pow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 预处理阶乘和阶乘逆元
void precompute_fac() {
    fac[0] = 1;
    for (int i = 1; i < MAX_FAC; ++i) {
        fac[i] = fac[i-1] * i % MOD;
    }
    invfac[MAX_FAC - 1] = quick_pow(fac[MAX_FAC - 1], MOD - 2);
    for (int i = MAX_FAC - 2; i >= 0; --i) {
        invfac[i] = invfac[i+1] * (i+1) % MOD;
    }
}

// 计算组合数C(a, b)
long long comb(int a, int b) {
    if (b < 0 || b > a) return 0;
    return fac[a] * invfac[b] % MOD * invfac[a - b] % MOD;
}

int main() {
    sieve();
    precompute_fac();
    
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        factorize(x);
    }
    
    long long ans = 1;
    for (auto& [p, cnt] : prime_cnt) {
        // 每个质因数的方案数是C(n + cnt - 1, n-1)
        ans = ans * comb(n + cnt - 1, n - 1) % MOD;
    }
    cout << ans << endl;
    return 0;
}
```
* **代码解读概要**：
  1. **预处理阶段**：用埃氏筛预处理质数（用于分解质因数），预处理阶乘和逆元（用于快速计算组合数）；
  2. **输入处理**：读取n和每个a_i，分解每个a_i的质因数，统计所有质因数的总次数；
  3. **计算结果**：对每个质因数，计算对应的组合数，相乘得到总方案数，模1e9+7输出。


<code_intro_selected>
接下来剖析优质题解中的**核心片段**，看看它们的巧妙之处：
</code_intro_selected>

**题解二（作者：Transparent）：预处理阶乘和逆元**
* **亮点**：用**倒推法**预处理逆元，比每次用快速幂快得多！
* **核心代码片段**：
```cpp
inline void getfac() {
    fac[0] = 1;
    for (register int i=1; i<=40000; i++) {
        fac[i] = fac[i-1] * (long long)i % Mod;
    }
    invfac[40000] = Pow(fac[40000], Mod-2); // 费马小定理求最大逆元
    for (register int i=39999; i>=0; i--) {
        invfac[i] = invfac[i+1] * (i+1) % Mod; // 倒推小逆元
    }
}
```
* **代码解读**：
  - 首先计算阶乘`fac[i]`：`fac[i] = i! mod Mod`；
  - 然后用费马小定理计算最大的逆元`invfac[40000]`（即40000!的逆元）；
  - 最后倒推 smaller 的逆元：因为`(i+1)! = (i+1)*i!`，所以`1/(i!) = (i+1)*1/( (i+1)! )`，对应代码中的`invfac[i] = invfac[i+1]*(i+1)%Mod`。
* 💡 **学习笔记**：倒推逆元是高效计算阶乘逆元的关键，一定要记住这个技巧！

**题解三（作者：orz_z）：避免类型溢出**
* **亮点**：用`#define int long long`统一类型，避免乘法溢出。
* **核心代码片段**：
```cpp
#define int long long

inline int Pow(int x, int y) {
    int res = 1;
    while(y) {
        if(y & 1) res = res * x % Mod;
        x = x * x % Mod;
        y >>= 1;
    }
    return res;
}
```
* **代码解读**：`long long`类型可以存储更大的数，避免了`int`类型乘法时的溢出问题（比如`1e5 * 1e5`会超过int的范围）。
* 💡 **学习笔记**：处理大数时，优先用`long long`类型，避免溢出bug！


## 5. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了让你更直观地理解“质因数分配”的过程，我设计了一个**8位像素风的动画游戏**——《质因数分配小能手》！
</visualization_intro>

### 动画设计细节
- **风格与场景**：仿照FC红白机的像素风格，背景是浅蓝色的“分配实验室”，中间有n个彩色的像素盒子（代表序列的n个位置），右上角是“质因数池”（显示当前要分配的质因数和数量）。
- **核心演示流程**：
  1. **初始化**：显示输入的n和质因数统计结果（比如n=3，质因数2有1个）；
  2. **质因数分配**：
     - 质因数池中的红色像素点（代表2）会“跳”到盒子上方；
     - 用黄色的“隔板”在像素点之间移动，展示“选n-1个隔板”的过程（比如n=3，选2个隔板）；
     - 每次选隔板后，盒子里的像素点数量会更新（比如选在第1和第2个点之间，盒子1有1个，盒子2和3有0个）；
  3. **音效与反馈**：
     - 选隔板时播放“叮”的像素音效；
     - 分配完成后，盒子会闪烁绿色，并显示当前质因数的方案数；
     - 所有质因数分配完成后，播放“胜利”音效，显示总方案数。
- **交互设计**：
  - 控制面板有“单步执行”（逐帧看分配过程）、“自动播放”（快速演示）、“重置”按钮；
  - 速度滑块可以调节自动播放的速度（从“慢”到“快”）。

### 为什么这样设计？
- 像素风格让你想起小时候玩的游戏，降低学习的“距离感”；
- 可视化质因数和隔板的移动，帮你直接“看到”组合数的计算逻辑；
- 音效和反馈增加了“游戏感”，让学习更有趣！


## 6. 拓展练习与相似问题思考

<similar_problems_intro>
掌握了“质因数分解+隔板法”的思路后，你可以尝试以下相似问题，巩固所学：
</similar_problems_intro>

### 通用思路迁移
这种“将问题转化为质因数分配”的思路，还可以解决：
1. **求n个数的乘积的因数个数**：每个质因数的次数加1相乘；
2. **求n个数的乘积的所有因数的和**：每个质因数的(1 + p + p² + ... + p^k)相乘；
3. **求有多少个有序序列，其乘积为某个数m**：和本题完全一致！

### 洛谷练习推荐
1. **洛谷 P1025 数的划分**  
   🗣️ **推荐理由**：这是隔板法的基础题，让你练习“将相同的数分成不同的部分”，直接对应本题的核心逻辑。
2. **洛谷 P1287 盒子与球**  
   🗣️ **推荐理由**：本题是“不同的球放进不同的盒子”，但可以通过排列组合转化为类似的问题，帮你拓展组合数学的应用。
3. **洛谷 P2392 kkksc03考前临时抱佛脚**  
   🗣️ **推荐理由**：本题需要用组合数计算“分配时间”的方案数，是组合数学的实际应用，帮你巩固预处理阶乘和逆元的技巧。


## 7. 学习心得与经验分享 (若有)

<insights_intro>
题解中提到的**两个关键经验**，值得你记住：
</insights_intro>

> **经验1（来自题解二）**：“分解质因数时，要注意最后剩下的数是否为质数——比如x=7，分解到i=2时，i*i=4≤7，但7%2≠0，所以最后要把7加入质因数统计。”  
> **点评**：这是分解质因数时最容易漏掉的点！如果不特判剩余的x，会导致质因数次数统计错误，比如样例3中的7和5会被漏掉，结果就错了。

> **经验2（来自题解三）**：“用long long类型避免溢出——比如组合数计算时，fac[i] = fac[i-1] * i，如果i是1e5，int类型会溢出。”  
> **点评**：溢出是C++中最常见的bug之一，处理大数时一定要用足够大的类型（比如long long）！


<conclusion>
本次分析就到这里啦！这道题的核心是**将复杂的乘积问题转化为简单的质因数分配问题**，再用组合数学的隔板法解决。记住：**问题转化是算法的灵魂**——遇到不会的题，先想“能不能把问题变成我熟悉的模型？” 下次我们再一起探索更多有趣的算法题！💪
</conclusion>

---
处理用时：119.42秒