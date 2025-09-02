# 题目信息

# [POI 2012] OKR-A Horrible Poem

## 题目描述

Bytie boy has to learn a fragment of a certain poem by heart.  The poem, following the best lines of modern art, is a long string    consisting of lowercase English alphabet letters only.  Obviously, it sounds horrible, but that is the least of Bytie's worries.

First and foremost, he completely forgot which fragment is he supposed to learn.  And they all look quite difficult to memorize...

There is hope, however: some parts of the poem exhibit certain regularity.  In particular, every now and then a fragment, say ![](http://main.edu.pl/images/OI19/okr-en-tex.1.png),    is but a multiple repetition of another fragment, say ![](http://main.edu.pl/images/OI19/okr-en-tex.2.png) (in other words, ![](http://main.edu.pl/images/OI19/okr-en-tex.3.png), i.e., ![](http://main.edu.pl/images/OI19/okr-en-tex.4.png), where ![](http://main.edu.pl/images/OI19/okr-en-tex.5.png) is    an integer).  In such case we say that ![](http://main.edu.pl/images/OI19/okr-en-tex.6.png) is a full period of ![](http://main.edu.pl/images/OI19/okr-en-tex.7.png) (in particular, every string is its own full period).

If a given fragment has a short full period, Bytie's task will be easy.  The question remains... which fragment was that?

Make a gift for Bytie - write a program that will read the whole poem as well as a list of fragments that Bytie suspects might be the    one he is supposed to memorize, and for each of them determines its shortest full period.

## 样例 #1

### 输入

```
8
aaabcabc
3
1 3
3 8
4 8```

### 输出

```
1
3
5```

# AI分析结果



# 算法分类  
**哈希 + 质因数分解**

---

## 题解思路与核心难点

### 核心算法流程
1. **哈希预处理**  
   - 计算字符串的前缀哈希值，用于快速比较子串  
   - 公式：`hash[r] - hash[l-1] * pow[r-l+1]`（模运算处理负数）

2. **质因数分解优化**  
   - 线性筛预处理每个数的最小质因子，实现 O(log n) 分解质因数  
   - 分解区间长度 len 的质因数，从大到小试除检查循环节

3. **循环节验证**  
   - 若长度为 d 的循环节存在，则满足：  
     `hash(l, r-d) == hash(l+d, r)`  
   - 通过不断去除质因数，逐步缩小可能的循环节长度

### 解决难点
- **质因数分解效率**：通过线性筛预处理最小质因子，将分解复杂度从 O(√n) 降为 O(log n)  
- **哈希碰撞规避**：双哈希或大模数自然溢出（题解中多用单哈希，实践中建议双哈希）  
- **边界条件处理**：如长度为1的循环节特判、质因数去重等

---

## 题解评分（≥4星）

### 1. RenaMoe（★★★★★）
- **亮点**  
  - 线性筛预处理最小质因子，分解高效  
  - 哈希计算与比较逻辑清晰  
  - 代码可读性强，含详细注释  
```cpp
// 线性筛预处理最小质因子
void euler() {
    for (ll i = 2; i <= n; ++i) {
        if (!vis[i]) pri.push_back(i), g[i] = i;
        for (int j = 0; j < pri.size() && pri[j] * i <= n; ++j) {
            vis[pri[j]*i] = true, g[pri[j]*i] = pri[j];
            if (i % pri[j] == 0) break;
        }
    }
}
```

### 2. Leap_Frog（★★★★☆）
- **亮点**  
  - 代码极简，仅100行实现核心逻辑  
  - 哈希自然溢出节省模运算时间  
  - 质因数分解与检查合并优化  
```cpp
// 质因数分解与检查合并
while (len ^ 1) {
    if (check(l, r - ans/g[len], l + ans/g[len], r))
        ans /= g[len];
    len /= g[len];
}
```

### 3. BeyondStars（★★★★）
- **亮点**  
  - 数学性质推导完整（循环节倍数性质）  
  - 分解质因数过程可视化注释  
  - 包含调试经历与优化思路（如进制选择）  
```cpp
// 质因数分解后枚举判断
for (int j=1; j<=tt; j++) {
    int t = len/ys[j];
    if (check(l, r-t, l+t, r)) len = t;
}
```

---

## 最优思路提炼

### 关键技巧
1. **质因数分解加速**  
   - 线性筛预处理每个数的最小质因子，分解时逐步除以最小质因子  
   - 时间复杂度从 O(√n) 优化至 O(log n)

2. **哈希窗口滑动验证**  
   - 循环节长度 d 需满足：`hash(l, r-d) == hash(l+d, r)`  
   - 通过哈希差公式快速比较子串

3. **逐步缩小循环节**  
   - 初始假设循环节为区间全长  
   - 按质因数从大到小试除，优先尝试更小的循环节

---

## 同类题目推荐
1. **P4391 [BOI2009]Radio Transmission**  
   - 循环节性质在无线传输中的应用  
2. **P3435 [POI2006]OKR-Periods of Words**  
   - 字符串前缀的最大周期问题  
3. **P5410 【模板】扩展 KMP（Z 函数）**  
   - 字符串循环节与 Z 数组的关联

---

## 可视化设计（核心算法演示）

### 动画方案
1. **质因数分解过程**  
   - **像素风格网格**：显示数字的质因数分解步骤，质因数用不同颜色高亮  
   - **音效**：分解成功时播放“滴”声，失败时短促“哔”声

2. **哈希比较演示**  
   - **滑动窗口**：用两个颜色块表示比较的子串 `[l, r-d]` 和 `[l+d, r]`  
   - **哈希值显示**：在 Canvas 上方实时计算并显示两个子串的哈希值

3. **自动演示模式**  
   - **AI 控制**：自动选择质因数并验证，速度可调（1x/2x/5x）  
   - **步进控制**：允许暂停后单步观察哈希比较细节

### 复古效果实现
```javascript
// Canvas 绘制示例（伪代码）
function drawPixel(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x*10, y*10, 8, 8); // 8x8 像素块
}

// 质因数分解动画
function factorize(n) {
    let factors = [];
    while (n > 1) {
        let p = minPrime[n];
        factors.push(p);
        drawPixel(factors.length-1, 0, getColor(p));
        n /= p;
        playSound('beep'); // 触发音效
    }
}
```

---

## 个人心得摘录
> "哈希碰撞是玄学问题，本题用自然溢出反而比模大素数更稳" —— BeyondStars  
> "线性筛的预处理让质因数分解从 TLE 变成 AC，优化效果惊人" —— RenaMoe  
> "不要忘记特判长度为1的循环节，能节省大量无效计算" —— Leap_Frog

---

## 核心代码实现
```cpp
// 预处理哈希与质因数
void init() {
    euler(); // 线性筛预处理最小质因子
    pow[0] = 1;
    for (int i=1; i<=n; i++) {
        hash[i] = hash[i-1] * base + s[i];
        pow[i] = pow[i-1] * base;
    }
}

// 处理单个查询
int solve(int l, int r) {
    int len = r - l + 1, ans = len;
    while (len > 1) {
        int p = minPrime[len];
        if (check(l, r - ans/p, l + ans/p, r))
            ans /= p;
        len /= p;
    }
    return ans;
}
```

---

通过结合哈希快速比较与质因数分解优化，该算法在 O(n + q log n) 时间复杂度下高效解决问题，是此类循环节问题的经典解法。

---
处理用时：89.69秒