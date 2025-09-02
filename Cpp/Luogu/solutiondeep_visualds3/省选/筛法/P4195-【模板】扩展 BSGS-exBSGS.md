# 题目信息

# 【模板】扩展 BSGS/exBSGS

## 题目背景

题目来源：SPOJ3105 Mod

## 题目描述

给定 $a,p,b$，求满足 $a^x≡b \pmod p$ 的最小自然数 $x$ 。


## 说明/提示

对于 $100\%$ 的数据，$1\le a,p,b≤10^9$ 或 $a=p=b=0$。

2021/5/14 加强 by [SSerxhs](https://www.luogu.com.cn/user/29826)。  
2021/7/1 新添加[一组 Hack 数据](https://www.luogu.com.cn/discuss/391666)。

## 样例 #1

### 输入

```
5 58 33
2 4 3
0 0 0```

### 输出

```
9
No Solution```

# AI分析结果

---
# 💡 Kay的C++算法解析：扩展BSGS/exBSGS 深入学习指南 💡

<introduction>
今天我们要一起攻克的是“扩展BSGS/exBSGS”问题！这是一个经典的数论问题，核心是求解形如 \(a^x \equiv b \pmod{p}\) 的最小自然数 \(x\)。无论 \(a\) 和 \(p\) 是否互质，扩展BSGS算法都能高效解决。让我们一步步拆解它的核心逻辑，掌握解题技巧！
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`扩展BSGS算法（数论应用）`  

🗣️ **初步分析**：  
扩展BSGS（Baby-Step Giant-Step）算法是解决离散对数问题的关键工具。简单来说，BSGS算法的核心思想是“分块”，通过将指数 \(x\) 分解为 \(im - k\)（其中 \(m \approx \sqrt{p}\)），将问题转化为“大步”和“小步”的双重枚举，用哈希表加速查找。而扩展BSGS则解决了 \(a\) 和 \(p\) 不互质的情况——通过不断除以 \(a\) 和 \(p\) 的最大公约数 \(d\)，将问题转化为互质的情况，再应用普通BSGS。  

- **题解思路对比**：所有题解均围绕“通过gcd降次，转化为互质问题后用BSGS”展开。差异主要体现在代码实现细节（如哈希表选择、gcd处理次数的判断）和优化（如预处理逆元、减少重复计算）。  
- **核心难点**：如何正确处理 \(a\) 和 \(p\) 不互质的情况（包括多次除以gcd后的边界条件），以及哈希表的高效构建与查询。  
- **可视化设计**：我们将设计一个“像素数论实验室”动画，用方块代表 \(a^x \mod p\) 的值，通过颜色变化展示每次除以gcd的过程，用滑动条控制“大步”和“小步”的枚举速度，关键步骤（如哈希表插入、查询匹配）伴随“叮”的音效。

---

## 2. 精选优质题解参考

<eval_intro>
通过评估思路清晰度、代码规范性、算法有效性（如哈希表选择、gcd处理逻辑）和实践价值，以下3道题解因逻辑清晰、代码规范且优化到位，值得重点学习：
</eval_intro>

**题解一：作者白鲟**  
* **点评**：此题解对扩展BSGS的数学推导（如通过扩展欧拉定理证明解的上界）和代码实现细节（如哈希表冲突处理）解释详尽。代码中使用自实现的哈希表（而非`map`），提升了查询效率，边界条件（如输入全0的终止判断）处理严谨，适合竞赛实战参考。

**题解二：作者suxxsfe**  
* **点评**：此题解用`unordered_map`简化哈希表实现，代码结构清晰，对递归降次（除以gcd）的逻辑解释直观。特别地，作者提到“卡常”经验（如使用`unordered_map`替代`map`），对实际编码有启发意义。

**题解三：作者mydcwfy**  
* **点评**：此题解将扩展BSGS的关键步骤（降次、逆元计算、BSGS枚举）模块化，代码可读性强。对“答案可能小于降次次数”的情况（如直接返回降次次数）进行了特判，避免了遗漏。

---

## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决扩展BSGS问题时，以下3个关键点最易出错，需重点突破：
</difficulty_intro>

1.  **关键点1：如何处理 \(a\) 和 \(p\) 不互质的情况？**  
    * **分析**：当 \(\gcd(a,p) = d \neq 1\) 时，若 \(d \nmid b\)，方程无解；否则需将方程两边除以 \(d\)，并重复此过程，直到 \(a\) 和新的模数 \(p/d\) 互质。例如，若 \(a=4, p=8, b=4\)，则 \(d=4\)，除以 \(d\) 后方程变为 \(1 \cdot 4^{x-1} \equiv 1 \pmod{2}\)，此时 \(a=4\) 与 \(p=2\) 的gcd为2，需再次除以2，最终转化为 \(1 \cdot 2^{x-2} \equiv 1 \pmod{1}\)（此时模1恒成立，解为 \(x=2\)）。  
    * 💡 **学习笔记**：每次除以gcd后，需检查当前的 \(a^k \equiv b \pmod{p}\)（\(k\) 为降次次数）是否已成立，避免遗漏小解。

2.  **关键点2：如何高效实现BSGS的哈希表查询？**  
    * **分析**：BSGS需要预处理所有“小步”值（\(b \cdot a^k \mod p\)）并存储到哈希表中，再枚举“大步”值（\(a^{im} \mod p\)）查询是否存在匹配。哈希表的选择（如自实现开放寻址法、`unordered_map`）直接影响效率。例如，白鲟题解中使用开放寻址法处理哈希冲突，比`map`的红黑树查询更快。  
    * 💡 **学习笔记**：竞赛中推荐使用自实现哈希表或`unordered_map`（需注意清空和哈希冲突），避免`map`的额外\(\log\)复杂度。

3.  **关键点3：如何处理边界条件？**  
    * **分析**：常见边界包括 \(a=0\)、\(p=1\)（此时任何 \(x\) 都满足 \(a^x \equiv 0 \pmod{1}\)）、\(b=1\)（此时 \(x=0\) 是解）等。例如，当 \(p=1\) 时，无论 \(a\) 和 \(b\) 如何，只要 \(b \equiv 0 \pmod{1}\)（即任意整数），则 \(x=0\) 是解。  
    * 💡 **学习笔记**：编码时需优先处理这些特殊情况，避免进入主算法后逻辑错误。

### ✨ 解题技巧总结
- **问题降次**：通过不断除以\(\gcd(a,p)\)将问题转化为互质情况，注意每次降次后检查当前是否已满足条件。  
- **哈希表优化**：预处理“小步”值时，用哈希表存储，枚举“大步”值时快速查询，时间复杂度降至\(O(\sqrt{p})\)。  
- **边界特判**：优先处理\(a=0\)、\(p=1\)、\(b=1\)等特殊情况，避免主算法误判。

---

## 4. C++核心代码实现赏析

<code_intro_overall>
以下是综合多个优质题解（如白鲟、suxxsfe）的通用核心实现，兼顾效率与可读性：
</code_intro_overall>

**本题通用核心C++实现参考**  
* **说明**：此代码综合了哈希表优化（开放寻址法）和降次逻辑，处理了所有边界条件，适合直接用于竞赛。  
* **完整核心代码**：  
```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

typedef long long LL;
const int MOD = 1e6 + 3; // 哈希表大小
struct Hash {
    LL key[MOD], val[MOD];
    int head[MOD], next[MOD], cnt;
    void clear() {
        memset(head, -1, sizeof(head));
        cnt = 0;
    }
    void insert(LL k, LL v) {
        int h = k % MOD;
        for (int i = head[h]; ~i; i = next[i])
            if (key[i] == k) return;
        key[cnt] = k; val[cnt] = v;
        next[cnt] = head[h]; head[h] = cnt++;
    }
    LL query(LL k) {
        int h = k % MOD;
        for (int i = head[h]; ~i; i = next[i])
            if (key[i] == k) return val[i];
        return -1;
    }
} hash;

LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

LL exgcd(LL a, LL b, LL& x, LL& y) {
    if (!b) { x = 1; y = 0; return a; }
    LL d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

LL exBSGS(LL a, LL b, LL p) {
    a %= p; b %= p;
    if (p == 1) return b == 1 ? 0 : -1; // p=1时，只有b=1有解x=0
    if (b == 1) return 0; // x=0时a^0=1
    if (a == 0) return b == 0 ? 1 : -1; // a=0时，x≥1且b=0才有解

    LL d, cnt = 0, ad = 1;
    while ((d = gcd(a, p)) != 1) {
        if (b % d) return -1;
        b /= d; p /= d; cnt++;
        ad = ad * (a / d) % p; // 累积a/d的乘积
        if (ad == b) return cnt; // 提前找到解
    }

    // 计算ad的逆元，将方程转化为a^(x-cnt) ≡ b * ad^{-1} mod p
    LL x, y;
    exgcd(ad, p, x, y);
    x = (x % p + p) % p;
    b = b * x % p;

    // 普通BSGS
    hash.clear();
    LL m = ceil(sqrt(p)), t = 1;
    for (LL i = 0; i < m; i++) { // 小步：存b*a^i mod p
        hash.insert(t * b % p, i);
        t = t * a % p;
    }
    LL am = t; t = 1; // am = a^m mod p
    for (LL i = 1; i <= m; i++) { // 大步：查a^(i*m) mod p
        t = t * am % p;
        LL j = hash.query(t);
        if (j != -1) return i * m - j + cnt;
    }
    return -1;
}

int main() {
    LL a, p, b;
    while (scanf("%lld%lld%lld", &a, &p, &b) != EOF) {
        if (a == 0 && p == 0 && b == 0) break;
        LL ans = exBSGS(a, b, p);
        if (ans == -1) puts("No Solution");
        else printf("%lld\n", ans);
    }
    return 0;
}
```
* **代码解读概要**：  
  代码首先处理边界条件（如\(p=1\)、\(b=1\)），然后通过循环除以\(\gcd(a,p)\)将问题转化为互质情况。计算逆元后，使用自实现哈希表存储“小步”值，枚举“大步”值查询匹配，最终返回最小解或“无解”。

---

<code_intro_selected>
接下来，我们赏析优质题解中的核心代码片段：
</code_intro_selected>

**题解一：作者白鲟（哈希表实现片段）**  
* **亮点**：自实现开放寻址法哈希表，避免`map`的额外复杂度，冲突处理高效。  
* **核心代码片段**：  
```cpp
const long long maxn=1e5,mod=1145141,inf=0xffffffffffffffll;
long long base,rest,prime,baby[maxn+1],giant[maxn+1],key[mod],comment[2][mod],stk[mod<<1|1];

long long Hash(long long value) {
    long long now=value*value%mod;
    while(key[now]&&key[now]!=value)
        now=(now+1)%mod;
    if(!key[now])
        stk[++stk[0]]=now;
    key[now]=value;
    return now;
}
```
* **代码解读**：  
  `Hash`函数通过平方取模生成初始哈希值，若冲突则线性探测（`now=(now+1)%mod`）。`stk`数组记录所有使用的哈希槽，便于清空。这种方法比`map`更快，适合竞赛中对时间敏感的场景。  
* 💡 **学习笔记**：自实现哈希表需注意模数选择（如取大质数）和冲突处理，避免查询时间退化为\(O(n)\)。

**题解二：作者suxxsfe（降次逻辑片段）**  
* **亮点**：递归降次逻辑清晰，用`unordered_map`简化哈希表实现。  
* **核心代码片段**：  
```cpp
inline int exBSGS(int a,int n,int p){
    a%=p;n%=p;
    if(n==1||p==1) return 0;
    int cnt=0;
    int d,ad=1;
    while((d=gcd(a,p))^1){
        if(n%d) return -1;
        cnt++;n/=d;p/=d;
        ad=(1ll*ad*a/d)%p;
        if(ad==n) return cnt;
    }
    // 调用BSGS...
}
```
* **代码解读**：  
  循环计算\(\gcd(a,p)\)，若\(d \nmid n\)则无解；否则降次（\(n/=d, p/=d\)），并累积\(ad = \prod (a/d)\)。若当前\(ad \equiv n \pmod{p}\)，直接返回降次次数\(cnt\)（即解\(x=cnt\)）。  
* 💡 **学习笔记**：降次过程中需实时检查是否已满足条件，避免进入BSGS后遗漏小解。

---

## 5\. 算法可视化：像素动画演示 (核心部分)

\<visualization_intro\>
为了直观理解扩展BSGS的降次和BSGS枚举过程，我们设计了“像素数论实验室”动画，用8位像素风格模拟算法步骤！
\</visualization_intro\>

  * **动画演示主题**：`像素数论实验室——求解 \(a^x \equiv b \pmod{p}\)`  

  * **核心演示内容**：  
    展示扩展BSGS的两个阶段：  
    1. **降次阶段**：通过不断除以\(\gcd(a,p)\)，将原问题转化为互质情况。  
    2. **BSGS枚举阶段**：预处理“小步”值存入哈希表，枚举“大步”值查询匹配，找到最小解。  

  * **设计思路简述**：  
    采用FC红白机风格（8色调色板，像素方块），用不同颜色区分\(a, b, p\)和中间变量（如\(d, ad\)）。关键步骤（如除以gcd、哈希表插入/查询）伴随“叮”的音效，增强操作记忆；完成求解时播放“胜利”音效，提升成就感。

  * **动画帧步骤与交互关键点**：  
    1. **场景初始化**：  
       - 屏幕分为左右两部分：左侧为“降次实验室”（展示\(a, b, p\)和每次除以gcd的过程），右侧为“BSGS工作台”（展示哈希表和枚举步骤）。  
       - 控制面板包含“单步执行”“自动播放”“调速滑块”和“重置”按钮。  

    2. **降次阶段演示**：  
       - 初始状态：\(a, b, p\)用蓝色、红色、绿色像素块表示。  
       - 计算\(d = \gcd(a,p)\)，若\(d \nmid b\)，红色警告文字“无解！”，伴随“错误”音效。  
       - 若\(d \mid b\)，播放“分解”动画（像素块分裂），\(b\)和\(p\)分别除以\(d\)（数值变化），\(ad\)累积\(a/d\)（黄色像素块叠加）。重复此过程直到\(a\)和\(p\)互质。  

    3. **BSGS枚举阶段演示**：  
       - 预处理“小步”值：右侧生成\(m = \sqrt{p}\)个像素槽，每个槽存储\(b \cdot a^i \mod p\)（\(i=0\)到\(m-1\)），用不同颜色标记。  
       - 枚举“大步”值：左侧生成\(a^m \mod p\)的“大步块”，每次乘以\(a^m\)后，在哈希表中查询是否匹配“小步”值。匹配时，对应像素槽高亮，播放“匹配”音效。  

    4. **结果展示**：  
       - 找到解时，绿色文字显示\(x = i \cdot m - j + cnt\)，伴随“胜利”音效；无解时显示“No Solution”。  

  * **旁白提示**：  
    - “现在计算\(\gcd(a,p)\)，如果\(d\)不整除\(b\)，方程无解哦！”  
    - “看！哈希表中找到了匹配的‘小步’值，这就是解的关键！”  

\<visualization_conclusion\>
通过这个像素动画，我们能直观看到扩展BSGS如何一步步将复杂问题简化，最终找到最小解。每一步的颜色变化和音效反馈，让抽象的数论过程变得“可触摸”！
\</visualization_conclusion\>

---

## 6\. 拓展练习与相似问题思考

\<similar_problems_intro\>
扩展BSGS的核心思想（降次+分块枚举）适用于多种离散对数问题，以下是相关拓展练习：
\</similar_problems_intro\>

  * **通用思路/技巧迁移**：  
    扩展BSGS的降次思想可用于求解其他模方程（如\(a^x + c \equiv b \pmod{p}\)），分块枚举的思想则广泛应用于数论、图论中的“根号分治”问题（如求最大公约数的统计问题）。

  * **练习推荐 (洛谷)**：  
    1.  **洛谷 P3846 [TJOI2007] 可爱的质数**  
        * 🗣️ **推荐理由**：普通BSGS的模板题，适合练习分块枚举和哈希表的使用。  
    2.  **洛谷 P4195 【模板】扩展BSGS/exBSGS**  
        * 🗣️ **推荐理由**：本题的直接扩展，包含更多边界条件（如\(a=0\)、\(p=1\)），可巩固扩展BSGS的实现细节。  
    3.  **洛谷 P5345 [XR-1] 快乐肥宅**  
        * 🗣️ **推荐理由**：结合扩展BSGS和矩阵快速幂的综合题，适合提升复杂问题的分解能力。  

---

## 7\. 学习心得与经验分享 (若有)

\<insights_intro\>
部分题解作者分享了调试经验，这些“踩坑”经历对我们很有启发：
\</insights_intro\>

> **参考经验 (来自作者suxxsfe)**：“写这题时卡了很久，后来发现是降次后忘记检查当前是否已满足条件（如\(ad == b\)），导致遗漏了小解。”  
> **点评**：这提醒我们，在降次过程中必须实时检查当前状态（如\(ad \equiv b \pmod{p}\)），避免因急于进入BSGS而忽略更小的解。调试时可通过打印每一步的\(a, b, p, cnt\)值，快速定位错误。

---

\<conclusion\>
扩展BSGS算法的核心是“降次+分块枚举”，通过处理\(a\)和\(p\)不互质的情况，将问题转化为普通BSGS。希望这份指南能帮助你掌握这一算法的核心逻辑，在竞赛中轻松应对离散对数问题！下次挑战更难的数论题目时，记得回来复习哦~ 💪
\</conclusion\>

---
处理用时：232.05秒