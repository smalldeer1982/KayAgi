# 题目信息

# Encryption (easy)

## 题目描述

Rebel spy Heidi has just obtained the plans for the Death Star from the Empire and, now on her way to safety, she is trying to break the encryption of the plans (of course they are encrypted – the Empire may be evil, but it is not stupid!). The encryption has several levels of security, and here is how the first one looks.

Heidi is presented with a screen that shows her a sequence of integers $ A $ and a positive integer $ p $ . She knows that the encryption code is a single number $ S $ , which is defined as follows:

Define the score of $ X $ to be the sum of the elements of $ X $ modulo $ p $ .

Heidi is given a sequence $ A $ that consists of $ N $ integers, and also given an integer $ p $ . She needs to split $ A $ into $ 2 $ parts such that:

- Each part contains at least $ 1 $ element of $ A $ , and each part consists of contiguous elements of $ A $ .
- The two parts do not overlap.
- The total sum $ S $ of the scores of those two parts is maximized. This is the encryption code.

Output the sum $ S $ , which is the encryption code.

## 说明/提示

In the first example, the score is maximized if the input sequence is split into two parts as $ (3,4) $ , $ (7,2) $ . It gives the total score of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/39bbc2e047bed6ad62ef40401430a139534974d3.png).

In the second example, the score is maximized if the first part consists of the first three elements, and the second part consists of the rest. Then, the score is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958C1/d991bcec92c9c10d8e1b00b096112e99ba9e2d35.png).

## 样例 #1

### 输入

```
4 10
3 4 7 2
```

### 输出

```
16
```

## 样例 #2

### 输入

```
10 12
16 3 24 13 9 8 7 5 12 12
```

### 输出

```
13
```

# AI分析结果



## 算法分类
前缀和

---

## 综合分析与结论
### 核心思路与难点
题目要求将数组拆分为两个非空连续区间，使得两区间和模 p 的总和最大。所有题解均采用前缀和优化，关键难点在于正确处理分割点范围。  
- **正确分割点**：枚举时必须确保后半部分非空，即分割点只能到 n-1。部分题解因循环范围错误导致结果偏差。
- **模运算性质**：利用前缀和模 p 与总和模 p 的关系，避免暴力计算。
- **数据类型**：需使用 long long 防止溢出。

### 最优思路提炼
1. **预处理前缀和数组**，快速计算任意区间和。
2. **枚举分割点 i（1 ≤ i < n）**，计算 `(sum[1..i] % p) + (sum[i+1..n] % p)`。
3. **直接使用前缀和差值**，无需额外维护后缀和数组。

### 可视化设计
- **动画方案**：以像素风格显示数组元素，动态高亮当前分割点 i，左右两部分用不同颜色区分。每次分割后显示两部分模值及当前最大值。
- **音效与交互**：当发现更大值时播放上扬音效，错误分割（如 i = n）时触发警示音。支持步进控制观察模值计算细节。
- **复古效果**：采用 8-bit 风格网格展示数组，前缀和数组以滚动数字形式更新。

---

## 题解评分（≥4星）
1. **chlchl（5星）**  
   思路清晰，正确处理分割点范围，代码可读性高，关键注释明确。

2. **Noby_Glds（4星）**  
   代码简洁高效，预处理 a[i] % p 优化计算，但注释较少。

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e5 + 5;
ll s[N];

int main() {
    int n, p;
    cin >> n >> p;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    ll ans = 0;
    for (int i = 1; i < n; ++i) { // 关键：i < n
        ans = max(ans, (s[i] % p) + ((s[n] - s[i]) % p));
    }
    cout << ans;
    return 0;
}
```

---

## 相似题目推荐
1. **P1115 最大子段和** - 前缀和经典应用  
2. **P2671 [NOIP2015 普及组] 求和** - 分段处理与模运算  
3. **P2967 [USACO09DEC] Video Game Troubles G** - 分割数组求极值

---

## 个人心得摘录
- **分割点陷阱**：chlchl 强调分割点不能取到 n，此边界条件易错且影响最终结果。
- **模运算优化**：Noby_Glds 的代码通过预取模降低计算量，避免 long long 溢出。

---

## 可视化算法演示（复古像素版）
```html
<!DOCTYPE html>
<html>
<body>
<canvas id="game" width="640" height="480"></canvas>
<script>
const canvas = document.getElementById('game');
const ctx = canvas.getContext('2d');
let data = { n:4, p:10, a:[3,4,7,2], maxS:0, currentI:0 };

function drawPixel(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x*32, y*32, 32, 32);
}

function animate() {
    // 绘制数组元素
    for(let i=0; i<data.n; i++) {
        drawPixel(i, 0, i < data.currentI ? '#FF0000' : '#00FF00');
        ctx.fillText(data.a[i], i*32+8, 32);
    }
    // 更新逻辑
    if(data.currentI < data.n-1) {
        let s1 = data.a.slice(0, data.currentI+1).reduce((a,b)=>a+b,0) % data.p;
        let s2 = data.a.slice(data.currentI+1).reduce((a,b)=>a+b,0) % data.p;
        data.maxS = Math.max(data.maxS, s1 + s2);
        data.currentI++;
    }
    requestAnimationFrame(animate);
}
animate();
</script>
</body>
</html>
```

---
处理用时：172.43秒