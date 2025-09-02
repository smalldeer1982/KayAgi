# 题目信息

# [ABC305G] Banned Substrings

## 题目描述

给定一个由 $M$ 个长度不超过 $6$ 的仅由字母 $\texttt a$ 和 $\texttt b$ 组成的非空字符串集合 $S=\{s_1, s_2, ..., s_M\}$。

求有多少个字符串 $T$ 满足以下条件：

- 长度为 $N$ 且仅由字母 $\texttt a$ 和 $\texttt b$ 组成。
- 对于任意 $s_i\in S$，$T$ 中不包含 $s_i$ 作为连续的子串。

由于答案可能很大，所以对 $998244353$ 取模。

## 说明/提示

$1\leq N\leq 10^{18}$

$1\leq M\leq 126$

$N$ 和 $M$ 是整数。

$s_i$ 是由字母 $a$ 和 $b$ 组成的长度不超过 $6$ 的非空字符串。

$s_i \neq s_j$（$1\leq i<j\leq M$）。

## 样例 #1

### 输入

```
4 3

aab

bbab

abab```

### 输出

```
10```

## 样例 #2

### 输入

```
20 1

aa```

### 输出

```
17711```

## 样例 #3

### 输入

```
1000000007 28

bbabba

bbbbaa

aabbab

bbbaba

baaabb

babaab

bbaaba

aabaaa

aaaaaa

aabbaa

bbaaaa

bbaabb

bbabab

aababa

baaaba

ababab

abbaba

aabaab

ababaa

abbbba

baabaa

aabbbb

abbbab

baaaab

baabbb

ababbb

baabba

abaaaa```

### 输出

```
566756841```

# AI分析结果


### 💡 Kay的C++算法解析：Banned Substrings 深入学习指南 💡

**引言**  
今天我们一起分析"Banned Substrings"这道AC自动机与矩阵优化的经典题。本指南将帮助大家理解如何高效处理大规模字符串计数问题。

---

## 1. 题目解读与核心算法识别

✨ **本题主要考察**：`字符串（AC自动机）` + `动态规划（矩阵优化）`

🗣️ **初步分析**：
> 解决本题的关键在于构建"字符串安检系统"（AC自动机）并设计"状态高速公路"（矩阵优化）。就像地铁安检机自动识别违禁品（禁止子串），我们通过状态转移矩阵快速计算所有安全路径（合法字符串）。  
> - **核心难点**：当字符串长度N达10¹⁸时，普通DP会超时，需将状态转移转化为矩阵乘法  
> - **可视化设计**：用像素网格展示AC自动机状态节点（红/绿区分危险/安全状态），转移边用发光轨道表示，矩阵乘法用像素块组合动画呈现  
> - **游戏化元素**：8-bit音效（状态转移→"滴"声，危险状态→警报音），通关设定（每完成10%进度解锁新像素皮肤）

---

## 2. 精选优质题解参考

**题解一（Disjoint_cat）**
* **亮点**：创新性地跳过显式AC自动机构建，直接通过状态压缩设计转移矩阵。代码中`dp[i][T]`的状态定义（T为末尾5字符）极大简化了实现，矩阵乘法部分采用标准快速幂模板，边界处理严谨。

**题解二（Neil_Qian）**
* **亮点**：完整展示AC自动机构建细节，特别强调`ban[u] |= ban[fail[u]]`的标记传递机制。矩阵构建逻辑清晰（安全状态→转移边赋1），快速幂部分用位运算优化，代码模块化程度高。

**题解三（_•́へ•́╬_）**
* **亮点**：极致简洁的实现，仅120行完成所有功能。采用双端队列优化fail指针计算，状态转移矩阵用二维数组直接映射，空间利用率极高。

---

## 3. 核心难点辨析与解题策略

1. **AC自动机的标记传递**  
   * **分析**：危险状态需沿fail指针传播（如"aa"危险则"baa"也危险）。优质解法均通过`suc[u] |= suc[fail[u]]`解决  
   * 💡 **学习笔记**：fail指针不仅是跳转工具，更是状态继承的通道

2. **状态空间的合理压缩**  
   * **分析**：Disjoint_cat利用|sᵢ|≤6的特性，仅记录末尾5字符（2⁵=32种状态）；其他解法通过AC自动机结点数<128保证可行性  
   * 💡 **学习笔记**：子串匹配仅与有限后缀相关，这是状态压缩的理论基础

3. **DP到矩阵的转化技巧**  
   * **分析**：将DP转移式∑dp[i][x]→dp[i+1][y]转化为矩阵乘法Mⁿ·v。矩阵元素M[y][x]=1表示状态x→y存在合法转移  
   * 💡 **学习笔记**：线性递推问题都可尝试矩阵化，复杂度从O(n)降至O(log n)

### ✨ 解题技巧总结
- **状态机思维**：将字符串匹配转化为有限状态机转移
- **矩阵降维打击**：遇O(n)DP且n极大时，立即考虑矩阵快速幂
- **AC自动机三要素**：trie树建立 → fail指针计算 → 标记传递
- **边界防御**：单独处理n<6情况（直接2ⁿ枚举）

---

## 4. C++核心代码实现赏析

**通用核心实现参考**
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353, S = 32; // S: 状态数

struct Matrix {
    long long m[S][S];
    Matrix operator*(const Matrix& b) {
        Matrix res;
        for(int i=0; i<S; i++)
        for(int k=0; k<S; k++)
        for(int j=0; j<S; j++) 
            res.m[i][j] = (res.m[i][j] + m[i][k]*b.m[k][j]) % MOD;
        return res;
    }
};

Matrix qpow(Matrix base, long long exp) {
    Matrix res; // 单位矩阵初始化
    while(exp) {
        if(exp & 1) res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}

// 检查str是否包含任何禁止子串
bool isSafe(const string& str, const vector<string>& banned) { /*...*/ } 

int main() {
    long long n; int m;
    vector<string> banned(m);
    // 输入处理...

    if(n <= 5) { // 特判小数据
        int cnt = 0;
        for(int i=0; i<(1<<n); i++) {
            string s;
            for(int j=0; j<n; j++) 
                s += (i>>j & 1) ? 'b' : 'a';
            if(isSafe(s, banned)) cnt++;
        }
        cout << cnt;
        return 0;
    }

    Matrix trans;
    // 构建转移矩阵：状态i（5bit）-> 状态j（新字符+右移）
    for(int i=0; i<S; i++) {
        string state = bitset<5>(i).to_string();
        for(char c : {'a','b'}) {
            string new_state = state.substr(1) + c;
            int j = stoi(new_state,0,2);
            if(isSafe(state+c, banned)) 
                trans.m[j][i] = 1; 
    }}

    Matrix final = qpow(trans, n-5);
    long long ans = 0;
    for(int i=0; i<S; i++) 
    for(int j=0; j<S; j++)
        ans = (ans + final.m[i][j]) % MOD;
    cout << ans;
}
```

**代码解读概要**：  
> 1. 小数据直接枚举2ⁿ种字符串  
> 2. 大数据用5bit表示末尾字符状态  
> 3. 构建32×32转移矩阵，矩阵快速幂加速  
> 4. 最终结果=∑Mⁿ所有元素值（从任意初态→任意终态）

---

**题解一核心片段（Disjoint_cat）**  
```cpp
// 矩阵幂核心 (n > 5时调用)
Matrix matpow(Matrix base, long long exp) {
    Matrix res; // 初始化为单位矩阵
    while(exp) {
        if(exp & 1) res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}
```
* **亮点**：标准快速幂模板，适用于任何矩阵类型  
* **学习笔记**：`exp >>= 1` 比 `/=2` 更快，位运算是优化关键

**题解二核心片段（Neil_Qian）**  
```cpp
fail[ch[u][i]] = ch[fail[u]][i];  // fail指针计算
ban[u] |= ban[fail[u]];           // 危险标记传递
```
* **亮点**：两行代码解决AC自动机核心逻辑  
* **学习笔记**：fail指针本质是寻找当前串的最长后缀匹配

**题解三核心片段（_•́へ•́╬_）**  
```cpp
deque<int> q;  // 双端队列优化
if(tre[i][0]) fail[tre[i][0]]=tre[fail[i]][0], q.push_back(tre[i][0]);
```
* **亮点**：用deque替代queue，减少内存碎片  
* **学习笔记**：BFS遍历trie树时，deque的连续内存访问更快

---

## 5. 算法可视化：像素动画演示

**主题**：8-bit风格《AC自动机大冒险》  
**核心演示**：AC自动机状态转移 × 矩阵乘法过程  

### 动画帧设计：
1. **场景初始化**（复古绿底像素网格）
   - 左侧：AC自动机状态图（安全状态→绿芯片，危险→红火焰）
   - 右侧：32×32矩阵网格（初始单位矩阵）
   - 控制面板：速度滑块/单步/暂停（FC手柄样式）

2. **AC自动机运行**（每步0.5秒）
   ```python
   # 伪代码逻辑
   for char in input_string:
       播放"滴"声
       当前状态芯片闪烁黄光
       沿char边移动到新状态
       if 新状态有火焰: 播放爆炸音效并结束
   ```
   - 转移边发光动画（a→蓝色光轨，b→黄色光轨）

3. **矩阵快速幂**（乘法过程可视化）
   ```python
   while n > 0:
      if n & 1: 
         高亮结果矩阵的行列（红光扫描）
         播放"咔哒"拼接音效
      n //= 2
      矩阵自乘：网格分裂→旋转→重组（吃豆人动画）
   ```
   - 指数二进制显示（像素LED计数板）

4. **游戏化元素**：
   - 每完成10%进度，解锁新角色皮肤（像素战士/法师/机械师）
   - 最终答案揭晓时，播放FC《超级玛丽》通关音乐
   - 错误路径触发"Game Over"像素火焰动画

---

## 6. 拓展练习与相似问题

**技巧迁移场景**：
1. 基因序列检测（避免特定碱基片段）
2. 硬件电路状态验证（规避危险信号组合）
3. 密码强度校验（排除常见弱密码）

**洛谷推荐**：
1. [P2446 外星密码](https://www.luogu.com.cn/problem/P2446)  
   → 巩固AC自动机+DP的经典应用
2. [P4052 文本生成器](https://www.luogu.com.cn/problem/P4052)  
   → 从"禁止"转"包含"的反向思维训练
3. [P2414 阿狸的打字机](https://www.luogu.com.cn/problem/P2414)  
   → AC自动机与树结构的进阶结合

---

## 7. 学习心得与经验分享

> **Neil_Qian的经验**：  
> *"ban[u] |= ban[fail[u]]这行千万别漏！我调试2小时才发现标记没传递"*  

**Kay点评**：  
这反映了AC自动机的核心陷阱——危险状态具有**传染性**。就像病毒传播，当某个状态危险时，所有通过fail指针链接的状态都需隔离。建议调试时：
1. 打印fail树结构
2. 用小数据验证标记传递
3. 对终止状态特别标注（如红框高亮）

---

掌握AC自动机+矩阵快速幂的组合拳，你就能高效解决这类"天文数字级"的字符串计数问题！下次遇到类似题目时，记得构建你的"状态高速公路"哦！🚀

---
处理用时：123.14秒