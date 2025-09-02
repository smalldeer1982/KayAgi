# 题目信息

# Madoka and The Corruption Scheme

## 题目描述

Madoka decided to entrust the organization of a major computer game tournament "OSU"!

In this tournament, matches are held according to the "Olympic system". In other words, there are $ 2^n $ participants in the tournament, numbered with integers from $ 1 $ to $ 2^n $ . There are $ n $ rounds in total in the tournament. In the $ i $ -th round there are $ 2^{n - i} $ matches between two players (one of whom is right, the other is left), after which the winners go further along the tournament grid, and the losing participants are eliminated from the tournament. Herewith, the relative order in the next round does not change. And the winner of the tournament — is the last remaining participant.

But the smaller the participant's number, the more he will pay Madoka if he wins, so Madoka wants the participant with the lowest number to win. To do this, she can arrange the participants in the first round as she likes, and also determine for each match who will win — the participant on the left or right.

But Madoka knows that tournament sponsors can change the winner in matches no more than $ k $ times. (That is, if the participant on the left won before the change, then the participant on the right will win after the change, and if the participant on the right won, then the participant on the left will win after the change).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1717D/f3b4c42531ac8b0aab0fa40e7e46069a137caf77.png)So, the first image shows the tournament grid that Madoka made, where the red lines denote who should win the match. And the second one shows the tournament grid, after one change in the outcome of the match by sponsors (a match between $ 1 $ and $ 3 $ players).Print the minimum possible number of the winner in the tournament, which Madoka can get regardless of changes in sponsors. But since the answer can be very large, output it modulo $ 10^9 + 7 $ . Note that we need to minimize the answer, and only then take it modulo.

## 说明/提示

In the first example, there is only one match between players $ 1 $ and $ 2 $ , so the sponsors can always make player $ 2 $ wins.

The tournament grid from the second example is shown in the picture in the statement.

## 样例 #1

### 输入

```
1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
2 1```

### 输出

```
3```

## 样例 #3

### 输入

```
3 2```

### 输出

```
7```

# AI分析结果


### 💡 Kay的C++算法解析：Madoka and The Corruption Scheme 深入学习指南 💡

<introduction>
今天我们分析一道有趣的锦标赛问题！Madoka需要设计比赛树，赞助商可修改比赛结果。本指南将帮助你理解如何通过组合数学解决此题，并掌握关键思维技巧。
</introduction>

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`组合数学`

🗣️ **初步分析**：
> 想象锦标赛树是一座像素迷宫（如图），每个分叉点代表比赛。Madoka预设所有比赛向左走（蓝色箭头），赞助商可翻转k次方向（变为红色箭头）。  
> - **核心思想**：每个叶子到根的路径是唯一的二进制序列（左=0，右=1）。赞助商通过翻转使序列中0的数量≤k的叶子都可能获胜  
> - **难点**：证明路径数 = ∑C(n,i)（i=0~k）  
> - **可视化设计**：8位像素迷宫演示路径遍历，翻转时播放"咔哒"音效，高亮当前路径。自动模式像"吃豆人"逐关展示不同翻转次数  

![](https://cdn.luogu.com.cn/upload/image_hosting/7g8dhyul.png)

---

## 2. 精选优质题解参考

**题解一（Hedgehog_210508）**
* **点评**：思路直观清晰，将比赛树倒置为从根到叶的路径，图示化展示"右转次数≤k"的核心思想。代码简洁规范（递推阶乘+逆元求组合数），边界处理严谨（k≥n时特判）。亮点是问题转化能力，实践参考价值高。

**题解二（whhsteven）**
* **点评**：从二进制属性值视角精确定义修改次数=路径中0的数量，逻辑推导严谨。虽未提供完整代码，但公式∑C(n,i)直指核心，启发性强。

**题解三（DaiRuiChen007）**
* **点评**：代码实现最优美，预处理阶乘+逆元递推（inv[i]=inv[i+1]*(i+1)），O(n)高效求解。变量命名规范（fact/inv），边界处理完整，竞赛实用性强。

---

## 3. 核心难点辨析与解题策略

1.  **问题转化难点**  
    * **分析**：如何将比赛修改转化为组合问题？优质题解将路径视为二进制序列（长度=n），赞助商修改次数=序列中0的数量  
    * 💡 **学习笔记**：复杂过程可抽象为二进制序列统计  

2.  **组合求和证明**  
    * **分析**：为什么路径数=∑C(n,i)？需理解：i次翻转对应选i条边，C(n,i)是选择方案数。所有i=0~k的方案互斥且完备  
    * 💡 **学习笔记**：组合数求和对应分类计数原理  

3.  **特判处理**  
    * **分析**：k≥n时所有叶子都可能获胜（路径数=2ⁿ），需优先处理避免超时  
    * 💡 **学习笔记**：边界条件往往隐含优化机会  

### ✨ 解题技巧总结
- **模型转化**：将树形结构转为二进制序列（路径表示）  
- **组合预处理**：阶乘+逆元递推求C(n,i)（模质数）  
- **分类累加**：∑_{i=0}^{min(k,n)} C(n,i) 是核心公式  
- **特判优化**：k≥n时直接返回2ⁿ  

---

## 4. C++核心代码实现赏析

**本题通用核心C++实现参考**
* **说明**：综合优质题解，使用递推逆元优化组合数计算
* **完整核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9+7;
const int MAXN = 1e5+5;

ll qpow(ll a, ll b) { // 快速幂
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ll n, k; cin >> n >> k;
    // 特判k≥n
    if (k >= n) {
        cout << qpow(2, n);
        return 0;
    }
    // 预处理组合数
    vector<ll> fact(n+1), inv(n+1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) 
        fact[i] = fact[i-1] * i % MOD;
    inv[n] = qpow(fact[n], MOD-2);
    for (int i = n-1; i >= 0; i--) 
        inv[i] = inv[i+1] * (i+1) % MOD;  // 逆元递推

    ll ans = 0;
    for (int i = 0; i <= k; i++) {
        ll C = fact[n] * inv[i] % MOD * inv[n-i] % MOD; // C(n,i)
        ans = (ans + C) % MOD;
    }
    cout << ans;
}
```
* **代码解读概要**：  
  1. 特判k≥n时直接输出2ⁿ（快速幂实现）  
  2. 递推计算阶乘数组fact和逆元数组inv  
  3. 累加组合数C(n,0)到C(n,k)  

---

**题解一（Hedgehog）核心片段赏析**
* **亮点**：费马小定理求逆元，代码简洁
* **核心代码片段**：
```cpp
ll c(ll a,ll b) {
    return fact[a] * inv(fact[b]) % MOD * inv(fact[a-b]) % MOD;
}
```
* **代码解读**：  
  > 组合数公式C(a,b)=a!/(b!(a-b)!)，通过fact数组存储阶乘，对分母用费马小定理求逆元（inv(x)=xᴹᴼᴰ⁻²）  
  > 注意：需先预计算阶乘，多次调用快速幂可能稍慢  

**题解三（DaiRuiChen）逆元递推赏析**
* **亮点**：O(n)时间预处理逆元
* **核心代码片段**：
```cpp
inv[n] = qpow(fact[n], MOD-2);
for(int i = n-1; i >= 0; i--)
    inv[i] = inv[i+1] * (i+1) % MOD;  // 关键递推
```
* **代码解读**：  
  > 利用公式：inv(i!) = inv((i+1)!) * (i+1)  
  > 从后往前递推，避免对每个阶乘单独求逆元，效率提升显著  

---

## 5. 算法可视化：像素动画演示

* **主题**：8位机风格"锦标赛迷宫"  
* **设计思路**：用FC游戏《吃豆人》地图风格呈现二叉树，路径翻转即吃豆人改道  

### 动画帧步骤：
1. **场景初始化**  
   - 像素化二叉树（16色），预设全左路径（蓝箭头）  
   - 控制面板：开始/暂停、单步、速度滑块、k值调节  

2. **自动演示模式**  
   ```mermaid
   graph LR
   A[根节点] -->|i=0| B[全左路径]
   A -->|i=1| C[第1条边翻转]
   A -->|i=2| D[第2条边翻转]
   ```
   - 步进式遍历i=0~k：当前路径高亮黄色，显示组合数C(n,i)  
   - 翻转边时：箭头变红 + "咔哒"音效 + 路径闪烁  

3. **游戏化元素**  
   - 每完成一个i值视为通关，显示"Lv.i Clear!" + 像素烟花  
   - 实时计分板：当前∑C(n,i)值  
   - 背景音乐：8-bit轻快循环BGM  

4. **信息同步**  
   - 右侧显示当前C(n,i)计算公式  
   - 底部日志："当k={k}时，有{ans}条路径"  

---

## 6. 拓展练习与相似问题思考

* **组合数应用场景**：  
  1. 二项式定理展开  
  2. 网格路径计数（只能向右/向下）  
  3. 子集选择问题（选i个元素）  

* **洛谷推荐**：  
  1. **P2638 安全系统**  
     🗣️ 巩固组合数求和模型  
  2. **P2822 组合数问题**  
     🗣️ 学习组合数前缀和预处理  
  3. **P3414 SAC#1 - 组合数**  
     🗣️ 二项式定理灵活应用  

---

## 7. 学习心得与经验分享
> **参考经验**：  
> _"我在处理k≥n时忘记特判，导致n=100000时超时" —— DaiRuiChen007调试经历_  
>  
> **点评**：  
> 边界特判是竞赛编码关键技巧，遇到n/k较大时优先考虑特殊边界，可节省大量计算资源！

---

<conclusion>
通过本次分析，我们掌握了组合数学在比赛问题中的巧妙应用。记住核心口诀："路径翻转即组合，累加求和解难题"。下次遇到类似问题，不妨先尝试二进制转化！✨
</conclusion>

---
处理用时：166.67秒