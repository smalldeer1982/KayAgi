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



---

## 0. 题目翻译

# [ABC305G] 被禁止的子串

## 题目描述

给定由 $M$ 个长度不超过 $6$ 的仅包含字母 $\texttt{a}$ 和 $\texttt{b}$ 的非空字符串组成的集合 $S=\{s_1, s_2, ..., s_M\}$。

求满足以下条件的字符串 $T$ 的个数：

1. 长度为 $N$ 且仅由字母 $\texttt{a}$ 和 $\texttt{b}$ 组成。
2. 对于任意 $s_i \in S$，$T$ 不包含 $s_i$ 作为连续子串。

答案对 $998244353$ 取模。

## 输入格式

第一行包含两个整数 $N$ 和 $M$，随后 $M$ 行每行给出一个字符串 $s_i$。

## 样例 #1

### 输入
```
4 3
aab
bbab
abab
```

### 输出
```
10
```

## 数据范围
$1 \leq N \leq 10^{18}$，$1 \leq M \leq 126$

---

## 1. 唯一算法分类  
**线性DP**

---

## 2. 综合分析与结论

### 核心思路
两种主流解法均基于**状态转移**与**矩阵快速幂**优化：
1. **末尾状态法**：维护最后 $L-1$ 个字符（$L$为最长禁止串长度），每次添加新字符后检查是否形成禁止串
2. **AC自动机法**：将禁止串构建为自动机，状态表示当前匹配位置，通过自动机转移避免进入非法状态

### 关键难点与解决方案
| 方法 | 状态设计 | 转移检查 | 时间复杂度 |
|------|----------|----------|------------|
| 末尾状态 | 最后 $5$ 字符组合 | 暴力检查所有可能子串 | $O(2^{L-1} \cdot M)$ |
| AC自动机 | 自动机节点编号 | 自动机跳转自动规避 | $O(\text{节点数}^3 \log N)$ |

### 可视化设计
1. **像素网格**：用 8x8 像素块表示状态矩阵，高亮当前活跃状态（如绿色表示合法状态，红色表示禁止状态）
2. **音效触发**：
   - 蓝色闪光：矩阵乘法运算
   - 清脆音效：成功转移
   - 低沉音效：触发禁止状态
3. **自动演示**：以贪吃蛇式路径自动遍历状态空间，动态展示矩阵指数运算过程

---

## 3. 题解清单 (≥4星)

### 题解1：AC自动机法（作者：Neil_Qian） ★★★★☆
**亮点**：
- 完整实现AC自动机的构建与转移
- 正确处理失败指针的标记传播
- 矩阵乘法采用结构体封装，代码可读性强

### 题解2：自动机优化版（作者：_•́へ•́╬_） ★★★★
**亮点**：
- 使用双端队列优化自动机构建
- 简洁的状态转移矩阵生成逻辑
- 内存占用控制优秀（节点数估算精准）

---

## 4. 核心代码实现

### AC自动机法关键代码
```cpp
struct matrix { // 矩阵快速幂模板
    ll a[N][N];
    matrix operator*(const matrix &t) {
        matrix res;
        for(int i=0; i<=cnt; i++)
            for(int k=0; k<=cnt; k++) if(a[i][k])
                for(int j=0; j<=cnt; j++)
                    res.a[i][j] = (res.a[i][j] + a[i][k]*t.a[k][j]) % MOD;
        return res;
    }
};

void build_automaton() { // 构建自动机
    queue<int> q;
    for(int c=0; c<2; c++)
        if(ch[0][c]) q.push(ch[0][c]);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int c=0; c<2; c++) {
            if(ch[u][c]) {
                fail[ch[u][c]] = ch[fail[u]][c];
                q.push(ch[u][c]);
            } else {
                ch[u][c] = ch[fail[u]][c];
            }
        }
    }
}
```

---

## 5. 推荐相似题目
1. **P4052 [JSOI2007]文本生成器**  
   （AC自动机+动态规划）
   
2. **P3193 [HNOI2008]GT考试**  
   （KMP+矩阵快速幂优化）

3. **P2446 [HNOI2010]合唱队**  
   （线性DP优化与状态设计）

---

## 6. 可视化伪代码示例
```javascript
// 像素动画核心逻辑
class DPSimulator {
  constructor() {
    this.states = this.buildAutomaton(); // 生成自动机节点
    this.canvas = new PixelCanvas(640, 480); // 8-bit风格画布
    this.playSound('startup'); // 启动音效
  }

  async run() {
    while(n > 0) { // 矩阵快速幂迭代
      if(n & 1) this.highlightState('multiply');
      this.rotateMatrix();
      await this.delay(500); // 步进延迟
      n >>= 1;
    }
    this.showResult();
  }
}
```

---
处理用时：92.00秒