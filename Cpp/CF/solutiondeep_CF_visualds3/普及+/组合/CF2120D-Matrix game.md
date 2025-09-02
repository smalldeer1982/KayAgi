# 题目信息

# Matrix game

## 题目描述

Aryan and Harshith play a game. They both start with three integers $ a $ , $ b $ , and $ k $ . Aryan then gives Harshith two integers $ n $ and $ m $ . Harshith then gives Aryan a matrix $ X $ with $ n $ rows and $ m $ columns, such that each of the elements of $ X $ is between $ 1 $ and $ k $ (inclusive). After that, Aryan wins if he can find a submatrix $ ^{\text{∗}} $ $ Y $ of $ X $ with $ a $ rows and $ b $ columns such that all elements of $ Y $ are equal.

For example, when $ a=2, b=2, k=6, n=3 $ and $ m=3 $ , if Harshith gives Aryan the matrix below, it is a win for Aryan as it has a submatrix of size $ 2\times 2 $ with all elements equal to $ 1 $ as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2120D/ff9ee31dfc04aa73a7daca458dede1d4462758ef.png) Example of a matrix where Aryan wins Aryan gives you the values of $ a $ , $ b $ , and $ k $ . He asks you to find the lexicographically minimum tuple $ (n,m) $ that he should give to Harshith such that Aryan always wins. Help Aryan win the game. Assume that Harshith plays optimally. The values of $ n $ and $ m $ can be large, so output them modulo $ 10^9+7 $ . A tuple $ (n_1, m_1) $ is said to be lexicographically smaller than $ (n_2, m_2) $ if either $ n_1<n_2 $ or $ n_1=n_2 $ and $ m_1<m_2 $ .

 $ ^{\text{∗}} $ A submatrix of a matrix is obtained by removing some rows and/or columns from the original matrix.

## 说明/提示

For the first test case, every $ n\times m $ matrix contains a $ 1\times 1 $ submatrix with all elements equal. $ (1,1) $ is the lexicographically minimum tuple among all of them.

For the second test case, it can be verified that whatever $ 3\times 7 $ matrix Harshith gives to Aryan, Aryan can always win by finding a $ 2\times 2 $ submatrix with all elements equal. $ (3,7) $ is also the lexicographically minimum tuple among all possible tuples where Aryan always wins.

## 样例 #1

### 输入

```
3
1 1 5
2 2 2
90000 80000 70000```

### 输出

```
1 1
3 7
299929959 603196135```

# AI分析结果


### 💡 Kay的C++算法解析：Matrix Game 深入学习指南 💡

#### 1. 题目解读与核心算法识别
✨ **本题主要考察**：组合数学与鸽巢原理  
🗣️ **初步分析**：  
> 解决本题的关键在于巧妙运用**鸽巢原理**（又称抽屉原理）。想象你有k种颜色的球，要保证至少有一种颜色出现a次，至少需要准备`k*(a-1)+1`个球。在本题中：
> - **行数n**：每列需要至少一种数字出现a次 → `n = k*(a-1)+1`
> - **列数m**：考虑所有可能的列配置方案（共`k·C(n,a)`种），需保证至少一种方案重复b次 → `m = k·C(n,a)·(b-1)+1`
> 
> **可视化设计思路**：采用8位像素风格展示矩阵填充过程：
> 1. 用不同颜色像素块表示数字（1~k）
> 2. 高亮每列中首次达到a个相同数字的位置（闪烁+音效）
> 3. 当出现b列相同模式时，触发胜利动画（金色边框+胜利音效）
> 4. 控制面板支持调速/单步观察鸽巢原理的执行

---

#### 2. 精选优质题解参考
**题解一（作者：yitinboge_fan）**  
* **亮点**：  
  - 严谨应用鸽巢原理推导n/m公式  
  - 组合数计算优化：循环连乘配合逆元（避免溢出）  
  - 边界处理：`(n-i+1+p)%p`确保负数修正  
  - 代码规范：变量命名清晰（a,b,k,n,m）

**题解二（作者：_O_v_O_）**  
* **亮点**：  
  - 相同数学推导但独立实现  
  - 模块化设计：分离`inv()`和`calc()`函数  
  - 注意：组合数计算中`(n-i+1+mod)`可优化为`(n-i+1)%mod`  

---

#### 3. 核心难点辨析与解题策略
1. **难点：维度分解思维**  
   * **分析**：将二维问题拆解为行/列两个一维鸽巢问题。先固定行方向（n），再处理列方向（m）。  
   * 💡 **学习笔记**：高维问题常可降维击破！

2. **难点：组合数模运算**  
   * **分析**：当n>10^5时需用逆元替代除法。质数模下用费马小定理：`inv(x)=x^(mod-2)`  
   * 💡 **学习笔记**：`1e9+7`模数下，除a! ≡ 乘a!的逆元

3. **难点：字典序最小化**  
   * **分析**：优先最小化n（因n权重>m），再计算对应m。证明n取`k*(a-1)+1`时m最小。  
   * 💡 **学习笔记**：字典序问题常需多阶段贪心

✨ **解题技巧总结**  
- **鸽巢扩展**：从经典单维抽屉扩展到多维配置  
- **模运算安全**：负数转正 `(x%mod + mod)%mod`  
- **组合数优化**：O(a)复杂度计算`C(n,a)`（a≤10^5）  

---

#### 4. C++核心代码实现赏析
**通用核心实现**  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll p = 1e9+7;

ll fastpow(ll a, ll b) {
    ll r = 1;
    while (b) {
        if (b & 1) r = r * a % p;
        a = a * a % p; b >>= 1;
    }
    return r;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int a, b, k; 
        scanf("%d%d%d", &a, &b, &k);
        // 行数n计算
        ll n = (a-1LL) * k + 1; 
        n %= p;
        
        // 组合数C(n,a)计算
        ll comb = 1;
        for (int i = 1; i <= a; i++) {
            comb = comb * fastpow(i, p-2) % p; // 分母i!的逆元
            comb = comb * ((n - i + 1 + p) % p) % p; // 分子连乘
        }
        
        // 列数m计算
        ll m = (comb * k % p) * (b-1) % p + 1; 
        printf("%lld %lld\n", n, m % p);
    }
}
```
**代码解读概要**：  
1. 快速幂求逆元替代除法（模质数核心技巧）  
2. 组合数通过`分子连乘*分母逆元`计算  
3. 安全取模：每次运算后`%p`，负数`+p`转正  

---

#### 5. 算法可视化：像素动画演示
**主题**：8-bit风格《鸽巢矩阵大冒险》  
**核心流程**：  
```plaintext
1. 初始化：
   - 屏幕左侧：k色像素块（数字池）
   - 右侧：n×m网格（初始灰色）

2. 行方向填充（鸽巢原理演示）：
   - 列填充动画：像素块从左侧飞入网格
   - 当某列出现a个同色块时：
       ① 触发闪烁（该列高亮黄框）
       ② 播放“叮！”音效
       ③ 记录该列模式（底部显示模式ID）

3. 列方向检测（胜利条件）：
   - 当某模式重复b次时：
       ① 网格中b列闪金边
       ② 播放胜利音效（8-bit和弦）
       ③ 显示"WIN!"像素艺术字

4. 交互控制：
   - 调速滑块：控制填充速度
   - 单步模式：空格键逐步观察
   - 模式追踪面板：实时显示各模式出现次数
```

---

#### 6. 拓展练习与相似问题
**通用技巧迁移**：鸽巢原理适用于：  
1. 重复元素检测（如：数组中找重复）  
2. 子数组/子矩阵约束问题  
3. 哈希冲突概率计算  

**洛谷推荐**：  
1. [P1495 抽屉原理](https://www.luogu.com.cn/problem/P1495)  
   → 鸽巢基础训练  
2. [P1634 生日礼物](https://www.luogu.com.cn/problem/P1634)  
   → 高维抽屉原理应用  
3. [P1978 集合](https://www.luogu.com.cn/problem/P1978)  
   → 组合数+鸽巢进阶  

---

本次解析旨在帮助大家掌握**组合数学的降维思维**和**模运算实践技巧**。记住：复杂问题往往由简单原理层层构建！下次见~ 🚀

---
处理用时：123.73秒