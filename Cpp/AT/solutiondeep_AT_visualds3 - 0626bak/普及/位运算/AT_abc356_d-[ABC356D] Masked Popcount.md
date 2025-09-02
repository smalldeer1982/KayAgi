# 题目信息

# [ABC356D] Masked Popcount

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc356/tasks/abc356_d

整数 $ N,M $ が与えられるので、 $ \displaystyle\ \sum_{k=0}^{N} $ $ \rm{popcount} $$ (k\ \mathbin{\&amp;}\ M) $ を $ 998244353 $ で割った余りを求めてください。

ただし、 $ \mathbin{\&amp;} $ はビット単位 $ \rm{AND} $ 演算を表します。

 ビット単位 $ \rm{AND} $ 演算とは？ 非負整数 $ a $ と非負整数 $ b $ とのビット単位 $ \rm{AND} $ 演算の結果 $ x\ =\ a\ \mathbin{\&amp;}\ b $ は次のように定義されます。  
- $ x $ は全ての非負整数 $ k $ について以下の条件を満たすただ $ 1 $ つの非負整数である。
- $ a $ を $ 2 $ 進法で書き下した際の $ 2^k $ の位と $ b $ を $ 2 $ 進法で書き下した際の $ 2^k $ の位が共に $ 1 $ なら、 $ x $ を $ 2 $ 進法で書き下した際の $ 2^k $ の位は $ 1 $ である。
- そうでないとき、 $ x $ を $ 2 $ 進法で書き下した際の $ 2^k $ の位は $ 0 $ である。
 
 
 例えば $ 3=11_{(2)},\ 5=101_{(2)} $ なので、 $ 3\ \mathbin{\&amp;}\ 5\ =\ 1 $ となります。  $ \rm{popcount} $ とは？ $ \rm{popcount} $$ (x) $ は、 $ x $ を $ 2 $ 進法で書き下した際に登場する $ 1 $ の個数を表します。  
 例えば $ 13=1101_{(2)} $ なので、 $ \rm{popcount} $$ (13)\ =\ 3 $ となります。

## 说明/提示

### 制約

- $ N $ は $ 0 $ 以上 $ 2^{60} $ 未満の整数
- $ M $ は $ 0 $ 以上 $ 2^{60} $ 未満の整数
 
### Sample Explanation 1

\- $ \rm{popcount} $$ (0\mathbin{\&amp;}3)\ =\ 0 $ - $ \rm{popcount} $$ (1\mathbin{\&amp;}3)\ =\ 1 $ - $ \rm{popcount} $$ (2\mathbin{\&amp;}3)\ =\ 1 $ - $ \rm{popcount} $$ (3\mathbin{\&amp;}3)\ =\ 2 $ - $ \rm{popcount} $$ (4\mathbin{\&amp;}3)\ =\ 0 $ であり、これらの和は $ 4 $ です。

### Sample Explanation 2

$ N=0 $ である場合や $ M=0 $ である場合もあります。

### Sample Explanation 3

$ 998244353 $ で割った余りを求めることに注意してください。

## 样例 #1

### 输入

```
4 3```

### 输出

```
4```

## 样例 #2

### 输入

```
0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
1152921504606846975 1152921504606846975```

### 输出

```
499791890```

# AI分析结果



**唯一算法分类**  
位运算与数位分析

---

**综合分析与结论**  
题目要求计算从0到N的每个数与M按位与后的二进制中1的个数之和。由于N可达2^60，需按位拆分计算贡献。

**核心思路**：  
1. **按位贡献分析**：对于M的每个二进制位i，若该位为1，则统计0~N中有多少数的第i位为1。  
2. **周期性规律**：第i位的值为1的规律为每2^(i+1)个数形成周期，其中前2^i个为0，后2^i个为1。  
3. **公式推导**：  
   - 完整周期数：(N+1) // (2^(i+1))  
   - 每个周期贡献：2^i  
   - 余数部分：若余数超过2^i，则贡献余数 - 2^i  

**难点与解决方案**：  
- **大数处理**：使用`long long`类型避免溢出。  
- **正确取模**：每一步加法后立即取模，避免结果溢出。  
- **位遍历**：通过右移操作遍历M的每一位。  

**可视化设计思路**：  
- **像素风格展示**：用不同颜色块表示二进制位的0/1周期性分布，动态分块显示完整周期和余数部分。  
- **高亮当前位**：在动画中高亮当前处理的二进制位，显示周期划分和贡献计算过程。  
- **音效与自动演示**：每处理完一位播放音效，自动按位演示计算流程，最终显示累加结果。  

---

**题解清单 (≥4星)**  
1. **LuukLuuk (5星)**  
   - 清晰推导位贡献公式，代码简洁高效。  
   - 关键点：正确处理余数部分与取模操作。  
2. **刘梓轩2010 (4星)**  
   - 结合官方题解思路，详细分析周期性规律。  
   - 代码结构清晰，注释明确。  
3. **Liyunze123 (4星)**  
   - 直接按位拆分贡献，代码简洁，函数封装合理。  

---

**最优代码实现**  
```cpp
#include <cstdio>
using namespace std;
#define int long long

const int mod = 998244353;

signed main() {
    int n, m, ans = 0;
    scanf("%lld%lld", &n, &m);
    
    for (int i = 0; i <= 60; ++i) { // 遍历M的每一位
        if ((m >> i) & 1) {         // 该位为1时计算贡献
            int j = 1LL << i;       // 当前位对应的值2^i
            int cycle = 2 * j;      // 完整周期长度2^(i+1)
            
            // 完整周期贡献
            int full = ((n + 1) / cycle) * j % mod;
            ans = (ans + full) % mod;
            
            // 余数部分贡献
            int rem = (n + 1) % cycle;
            if (rem > j) 
                ans = (ans + rem - j) % mod;
        }
    }
    printf("%lld", ans);
    return 0;
}
```

---

**相似题目推荐**  
1. [P4317 花神的数论题](https://www.luogu.com.cn/problem/P4317)  
   - 求二进制中1的个数之积，需类似位分析。  
2. [P4127 [AHOI2009]同类分布](https://www.luogu.com.cn/problem/P4127)  
   - 数位DP与位运算结合。  
3. [P2602 [ZJOI2010]数字计数](https://www.luogu.com.cn/problem/P2602)  
   - 统计数字在指定位数中的出现次数。  

---

**可视化算法演示**  
```html
<div id="bit-visual"></div>
<script>
// 参数初始化
const N = 4, M = 3; // 样例输入
let currentBit = 0;
const mod = 998244353;
let total = 0;

function drawBit(bit) {
    const container = document.getElementById('bit-visual');
    container.innerHTML = `<h3>Processing Bit ${bit}</h3>`;
    
    // 计算周期和余数
    const j = 1 << bit;
    const cycle = 2 * j;
    const fullCycles = Math.floor((N + 1) / cycle);
    const remainder = (N + 1) % cycle;
    
    // 动态生成周期块
    for (let i = 0; i < fullCycles; i++) {
        const div = document.createElement('div');
        div.style = `display:inline-block; width:${j * 20}px; height:30px; 
                     background:${i % 2 ? '#FF6B6B' : '#4ECDC4'}`;
        container.appendChild(div);
    }
    // 绘制余数部分
    if (remainder > 0) {
        const remDiv = document.createElement('div');
        remDiv.style = `display:inline-block; width:${remainder * 20}px; height:30px;
                        background:${remainder > j ? '#FF6B6B' : '#4ECDC4'}`;
        container.appendChild(remDiv);
    }
}

// 自动步进演示
setInterval(() => {
    if (currentBit > 3) return; // 仅演示低4位
    if ((M >> currentBit) & 1) {
        drawBit(currentBit);
        total += calculateContribution(currentBit);
        total %= mod;
    }
    currentBit++;
}, 2000);
</script>
```

---
处理用时：72.88秒