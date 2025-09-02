# 题目信息

# Running Competition

## 题目描述

A running competition is going to be held soon. The stadium where the competition will be held can be represented by several segments on the coordinate plane:

- two horizontal segments: one connecting the points $ (0,         0) $ and $ (x, 0) $ , the other connecting the points $ (0,         y) $ and $ (x, y) $ ;
- $ n + 1 $ vertical segments, numbered from $ 0 $ to $ n $ . The $ i $ -th segment connects the points $ (a_i,         0) $ and $ (a_i, y) $ ; $ 0 = a_0 < a_1 < a_2 <         \dots < a_{n - 1} < a_n = x $ .

For example, here is a picture of the stadium with $ x = 10 $ , $ y = 5 $ , $ n = 3 $ and $ a = [0, 3, 5, 10] $ :

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1398G/81bd381693fb1325b3353cdccb69047f4e9ca225.png)A lap is a route that goes along the segments, starts and finishes at the same point, and never intersects itself (the only two points of a lap that coincide are its starting point and ending point). The length of a lap is a total distance travelled around it. For example, the red route in the picture representing the stadium is a lap of length $ 24 $ .

The competition will be held in $ q $ stages. The $ i $ -th stage has length $ l_i $ , and the organizers want to choose a lap for each stage such that the length of the lap is a divisor of $ l_i $ . The organizers don't want to choose short laps for the stages, so for each stage, they want to find the maximum possible length of a suitable lap.

Help the organizers to calculate the maximum possible lengths of the laps for the stages! In other words, for every $ l_i $ , find the maximum possible integer $ L $ such that $ l_i \bmod L =       0 $ , and there exists a lap of length exactly $ L $ .

If it is impossible to choose such a lap then print $ -1 $ .

## 样例 #1

### 输入

```
3 10 5
0 3 5 10
6
24 30 14 16 18 10```

### 输出

```
24 30 14 16 -1 -1```

# AI分析结果

---
# 💡 Kay的C++算法解析：Running Competition 深入学习指南 💡

<introduction>
今天我们来一起分析“Running Competition”这道C++编程题。本指南将帮助大家理解题目核心、掌握高效解题方法，并通过可视化方案直观感受算法过程。让我们开始吧！
</introduction>

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`数学应用（因数预处理）与高效差值计算（bitset/FFT卷积）`

🗣️ **初步分析**：
解决“Running Competition”的关键在于两步：  
1. **找出所有可能的环形路径长度**：题目中的环形路径本质是矩形，其周长为 \( 2 \times (a_i - a_j + y) \)（\( i > j \)），其中 \( a_i - a_j \) 是横向边长，\( y \) 是纵向边长。  
2. **预处理每个查询的最大因数**：对于每个查询长度 \( l_i \)，需找到最大的 \( L \) 满足 \( L \mid l_i \) 且存在长度为 \( L \) 的环形路径。  

**核心难点**：直接枚举所有 \( i,j \) 对（共 \( O(n^2) \) 种）会超时，需用高效方法计算所有可能的 \( a_i - a_j \)。题解中提供了两种优化思路：  
- **bitset优化**：用位运算快速标记所有可能的差值，时间复杂度 \( O(\frac{n^2}{\omega}) \)（\( \omega \) 是机器字长，如64）。  
- **FFT卷积**：通过多项式卷积计算差值的存在性，时间复杂度 \( O(x \log x) \)，更高效。  

**可视化设计**：我们将设计一个“像素差数生成器”动画，用像素点表示 \( a_i \) 的位置（如横坐标），通过左右移动指针 \( i,j \) 高亮显示 \( a_i - a_j \) 的差值，并用颜色变化标记有效差值。最终生成的周长 \( 2 \times (差值 + y) \) 会以像素条动态展示，预处理因数时用“倍数扩散”动画（如像素波扩散覆盖所有倍数位置）。

---

## 2. 精选优质题解参考

<eval_intro>
经过评估，以下题解在思路清晰性、代码规范性和算法效率上表现优秀（均≥4星），值得重点学习：
</eval_intro>

**题解一：Froggy的Sol2（FFT卷积法）**  
* **点评**：该题解巧妙利用FFT（快速傅里叶变换）解决差值计算问题。思路上，通过生成函数将差值问题转化为多项式卷积，高效找出所有可能的 \( a_i - a_j \)。代码结构工整（如NTT函数封装清晰），变量命名直观（如`poly`表示多项式）。算法上，FFT的时间复杂度仅 \( O(x \log x) \)，远优于暴力枚举，是竞赛中处理此类问题的典型优化方法。实践中，代码边界处理严谨（如限制数组大小），可直接用于竞赛。

**题解二：YipChip的FFT解法**  
* **点评**：此题解与Froggy的Sol2思路一致，但实现更简洁（如`covolution`函数封装卷积过程）。代码中使用`NTT`函数直接处理多项式乘法，逻辑清晰。特别地，预处理因数时通过反向遍历更新最大值，避免重复计算，体现了优秀的编程技巧。变量`maxn`明确限制数组大小，防止越界，鲁棒性强。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决此题时，我们常遇到以下核心难点。结合优质题解，我们总结了应对策略：
</difficulty_intro>

1.  **难点1：如何高效计算所有可能的 \( a_i - a_j \)？**  
    * **分析**：直接枚举 \( i,j \) 对的时间复杂度为 \( O(n^2) \)，当 \( n \) 较大（如 \( 10^5 \)）时不可行。优质题解采用两种方法优化：  
      - **bitset**：用位掩码标记 \( a_i \) 的位置，通过位或操作快速得到所有差值（如 `myh |= p >> a[i]`）。  
      - **FFT卷积**：将 \( a_i \) 视为多项式系数，通过卷积计算差值的存在性（如 \( A(x) \times B(x) \) 的系数表示差值出现次数）。  
    * 💡 **学习笔记**：当需要快速计算集合中元素的差值时，bitset或FFT是高效的选择。

2.  **难点2：如何预处理每个 \( l_i \) 的最大因数？**  
    * **分析**：对于每个有效周长 \( L \)，需将其所有倍数 \( kL \) 的最大因数更新为 \( L \)（若 \( L \) 更大）。题解中通过反向遍历（从大到小）或直接标记倍数实现，确保每个 \( l_i \) 最终存储最大的 \( L \)。  
    * 💡 **学习笔记**：预处理因数时，“倍数扩散”法（从 \( L \) 出发标记其所有倍数）是高效的通用技巧。

3.  **难点3：如何处理奇偶性与边界条件？**  
    * **分析**：周长 \( L \) 必为偶数（因 \( 2 \times (\text{差值} + y) \)），因此若 \( l_i \) 为奇数，直接输出-1。此外，需确保 \( a_i - a_j \) 有效（即 \( i > j \)，差值非负）。  
    * 💡 **学习笔记**：题目中隐含的数学性质（如奇偶性）是快速判断无解的关键。

### ✨ 解题技巧总结
- **问题转化**：将几何问题（环形路径）转化为数学问题（差值计算与因数预处理）。  
- **高效工具使用**：bitset适合小范围快速标记，FFT适合大范围差值计算。  
- **预处理优化**：通过“倍数扩散”法预处理因数，避免对每个查询单独枚举因数。  

---

## 4. C++核心代码实现赏析

<code_intro_overall>
我们综合Froggy的FFT解法和YipChip的优化思路，提炼出一个高效且清晰的核心实现。
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：本代码基于FFT卷积法，综合了两种优质题解的思路，兼顾高效与可读性。  
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 998244353;
const int G = 3; // 原根
const int MAXN = 1e6 + 10;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

void ntt(vector<int>& f, bool invert, int n) {
    static vector<int> rev(n);
    for (int i = 0; i < n; ++i) 
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    for (int i = 0; i < n; ++i) 
        if (i < rev[i]) swap(f[i], f[rev[i]]);
    
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = qpow(invert ? qpow(G, MOD-2) : G, (MOD-1)/len);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len/2; ++j) {
                int u = f[i+j], v = 1LL * w * f[i+j+len/2] % MOD;
                f[i+j] = (u + v) % MOD;
                f[i+j+len/2] = (u - v + MOD) % MOD;
                w = 1LL * w * wlen % MOD;
            }
        }
    }
    if (invert) {
        int inv_n = qpow(n);
        for (int i = 0; i < n; ++i) 
            f[i] = 1LL * f[i] * inv_n % MOD;
    }
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n); fb.resize(n);
    ntt(fa, false, n); ntt(fb, false, n);
    for (int i = 0; i < n; ++i) 
        fa[i] = 1LL * fa[i] * fb[i] % MOD;
    ntt(fa, true, n);
    return fa;
}

int main() {
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n+1);
    for (int i = 0; i <= n; ++i) cin >> a[i];

    // 构造生成函数A(x)和反转后的B(x)
    vector<int> A(x+1, 0), B(x+1, 0);
    for (int ai : a) A[ai] = 1;
    B = A; reverse(B.begin(), B.end());

    // 卷积计算差值的存在性
    vector<int> C = multiply(A, B);

    // 预处理所有可能的周长L=2*(d+y)，d=a_i -a_j
    vector<int> ans(MAXN, 0);
    for (int d = 1; d <= x; ++d) {
        if (C[d + x] > 0) { // 差值d存在
            int L = 2 * (d + y);
            if (L >= MAXN) continue;
            for (int k = L; k < MAXN; k += L) 
                ans[k] = max(ans[k], L);
        }
    }

    int q; cin >> q;
    while (q--) {
        int l; cin >> l;
        if (l % 2 != 0 || ans[l] == 0) cout << "-1 ";
        else cout << ans[l] << " ";
    }
    return 0;
}
```
* **代码解读概要**：  
  代码首先读取输入并构造生成函数 \( A(x) \)（标记 \( a_i \) 的位置），反转 \( A(x) \) 得到 \( B(x) \)。通过FFT卷积计算 \( A(x) \times B(x) \)，结果 \( C \) 的系数表示差值 \( a_i - a_j \) 的存在性。接着预处理所有可能的周长 \( L \)，并更新每个 \( L \) 的倍数的最大因数。最后处理查询，输出结果。

---
<code_intro_selected>
接下来，我们分析优质题解的核心代码片段，学习其中的巧妙思路。
</code_intro_selected>

**题解一：Froggy的Sol2（FFT卷积法）**  
* **亮点**：通过多项式卷积高效计算差值，代码中NTT函数封装清晰，预处理因数时直接标记倍数。  
* **核心代码片段**：
```cpp
poly Mul(poly A, poly B) {
    int n = A.size() + B.size() - 1;
    int lim = NTT_init(n);
    NTT(A, 1, lim), NTT(B, 1, lim);
    for (int i = 0; i < lim; ++i) 
        P[i] = 1LL * A[i] * B[i] % mod;
    NTT(P, 0, lim);
    P.resize(n);
    return P;
}
```
* **代码解读**：  
  `Mul`函数实现了多项式乘法。首先计算卷积所需的最小长度`lim`，对两个多项式`A`和`B`进行NTT变换（转换到频域），逐点相乘后逆NTT变换回时域，得到卷积结果。这一步是关键，通过FFT快速计算所有可能的差值 \( a_i - a_j \)。  
* 💡 **学习笔记**：多项式卷积是处理集合差值问题的“数学魔法”，将 \( O(n^2) \) 问题转化为 \( O(x \log x) \)。

**题解二：YipChip的FFT解法**  
* **亮点**：代码简洁，预处理因数时反向更新最大值，避免重复计算。  
* **核心代码片段**：
```cpp
for (int i = y << 1; i <= maxn; i += 2) {
    if (!cnt[i]) continue;
    for (int j = i; j <= maxn; j += i) 
        if (cnt[j] < cnt[i]) cnt[j] = cnt[i];
}
```
* **代码解读**：  
  这段代码预处理每个可能的周长 \( L \)（偶数），并将其所有倍数 \( j \) 的`cnt[j]`更新为最大的 \( L \)。通过从 \( L \) 出发标记其倍数，确保每个 \( j \) 最终存储最大的合法 \( L \)。  
* 💡 **学习笔记**：预处理因数时，“倍数扩散”法能高效覆盖所有可能的查询。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

<visualization_intro>
为了直观理解如何生成差值和预处理因数，我们设计“像素差数生成器”动画，结合8位像素风格与游戏化元素。
</visualization_intro>

  * **动画演示主题**：`像素探险家的差值之旅`  
  * **核心演示内容**：展示 \( a_i \) 的位置、差值 \( a_i - a_j \) 的生成、周长 \( L \) 的计算，以及预处理因数的“倍数扩散”过程。  

  * **设计思路简述**：  
    采用8位像素风（如FC游戏画面），用不同颜色的像素块表示 \( a_i \)（如绿色方块）。通过左右移动指针 \( i,j \)（像素箭头）高亮显示差值 \( a_i - a_j \)（红色线段长度），并生成对应的周长 \( L \)（蓝色像素条）。预处理因数时，用“像素波”从 \( L \) 位置扩散，覆盖所有倍数位置（黄色标记），增强对“因数关系”的直观理解。

  * **动画帧步骤与交互关键点**：  
    1. **场景初始化**：  
       - 屏幕下方显示横坐标（0到x），绿色像素块标记 \( a_i \) 的位置（如 \( a=[0,3,5,10] \) 时，0、3、5、10处有绿块）。  
       - 控制面板：开始/暂停、单步、重置按钮；速度滑块（调节动画快慢）。  
       - 8位背景音乐（如《超级马里奥》风格）轻响。  

    2. **差值生成**：  
       - 左指针（红色箭头）指向 \( j \)，右指针（蓝色箭头）指向 \( i \)（\( i > j \)）。  
       - 两指针间的水平线段高亮（红色），显示差值 \( a_i - a_j \)（如 \( a_2=5, a_1=3 \) 时，差值为2）。  
       - 伴随“叮”音效（像素风格），差值数值（2）显示在屏幕上方。  

    3. **周长计算**：  
       - 纵向边长 \( y \) 用垂直绿色线段表示（如 \( y=5 \) 时，从 \( (a_j,0) \) 到 \( (a_j,5) \)）。  
       - 周长 \( L=2*(2+5)=14 \) 以蓝色像素条从屏幕底部升起，数值（14）闪烁显示，伴随“唰”音效。  

    4. **预处理因数**：  
       - 蓝色像素条（L=14）触发“倍数扩散”动画：从14开始，每隔14个单位（如28、42…）出现黄色标记，标记处数值更新为14（若当前值更小）。  
       - 扩散时播放“波”音效，标记完成后播放“滴答”声。  

    5. **查询处理**：  
       - 输入查询 \( l_i=24 \)，屏幕上方显示24的像素数字。  
       - 黄色标记中最大的L（24）高亮，播放“胜利”音效，结果24显示为绿色；若查询无解（如l=10），显示红色-1，播放“错误”音效。  

  * **旁白提示**：  
    - “看！左指针和右指针之间的距离就是差值 \( a_i - a_j \) 哦～”  
    - “周长是差值加上y，再乘以2，像不像给矩形围了一圈绳子？”  
    - “黄色波扩散到的位置都是当前周长的倍数，这样查询时就能直接找到最大的L啦！”  

<visualization_conclusion>
通过这个动画，我们能直观看到差值如何生成、周长如何计算，以及预处理因数的过程。像素风格和游戏化元素让学习更有趣！
</visualization_conclusion>

---

## 6\. 拓展练习与相似问题思考

<similar_problems_intro>
本题的核心思路（差值计算+因数预处理）可迁移到多种场景，例如：
</similar_problems_intro>

  * **通用思路/技巧迁移**：  
    - 计算集合中元素的差值（如两数之和、子数组和等）。  
    - 预处理倍数关系（如求最大公约数、最小公倍数的应用）。  
    - FFT在字符串匹配、多项式乘法中的其他应用。  

  * **练习推荐 (洛谷)**：  
    1.  **洛谷 P3321** - 寻宝  
        * 🗣️ **推荐理由**：涉及差值计算与路径长度问题，可巩固差值分析能力。  
    2.  **洛谷 P3803** - 多项式乘法（FFT）  
        * 🗣️ **推荐理由**：直接练习FFT的实现与应用，理解其数学原理。  
    3.  **洛谷 P1463** - [POI2002][HAOI2007]反素数  
        * 🗣️ **推荐理由**：涉及因数预处理与最大值查询，与本题预处理思路类似。  

---

## 7\. 学习心得与经验分享 (若有)

<insights_intro>
Froggy在题解中提到：“Sol1的bitset方法虽然理论时间复杂度较高，但实际通过了测试，不过最慢点跑了1825ms；而Sol2的FFT方法更高效，最慢点仅300ms。” 这给了我们重要启发：
</insights_intro>

> **参考经验 (来自 Froggy)**：“选择高效的算法（如FFT）能显著降低运行时间，特别是在数据量大时。即使暴力方法能通过，也要尝试优化，提升代码的鲁棒性。”  
> **点评**：Froggy的经验提醒我们，竞赛中需根据数据范围选择最优算法。FFT等高级算法虽实现复杂，但能处理更大规模的数据。平时多学习这些算法，关键时刻能派上大用场！

---

<conclusion>
本次关于“Running Competition”的分析就到这里。希望大家掌握了差值计算与因数预处理的技巧，理解了FFT的高效应用。编程的魅力在于不断优化与探索，下次我们再一起挑战新的题目！💪
</conclusion>

---
处理用时：146.92秒