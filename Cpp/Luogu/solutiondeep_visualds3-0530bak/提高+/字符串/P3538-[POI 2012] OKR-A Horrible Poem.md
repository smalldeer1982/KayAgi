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



### 唯一算法分类
字符串哈希 + 质因数分解

---

### 综合分析与结论
**核心思路**  
本题需要快速判断区间的最小循环节，核心思路结合两个关键点：  
1. **循环节长度必须是区间长度的因数**  
2. **哈希快速判断子串是否相等**  

**解决难点**  
- 直接枚举所有因数会超时，需用质因数分解优化  
- 预处理每个数的最小质因子，将质因数分解复杂度从 O(√n) 优化到 O(logn)  
- 通过试除质因子的方式，逐步缩小可能的循环节长度  

**可视化设计要点**  
1. **动画流程**  
   - 用像素风格显示字符串区间，高亮当前比较的循环节候选  
   - 分解质因数时，显示质因子气泡逐个弹出  
   - 哈希比较时，用左右箭头高亮比较的两个子串  
   - 成功匹配时播放上升音效，失败时播放下降音效  

2. **复古风格实现**  
   - 使用 8-bit 风格字体，质因数用不同颜色方块表示  
   - Canvas 绘制字符串区间，每次试除时更新候选长度  
   - 背景音乐循环播放《超级马里奥》地下关卡音乐  

---

### 题解清单（4星及以上）

#### 1. RenaMoe（5星）  
- **亮点**  
   - 线性筛预处理最小质因子，质因数分解优化到 O(logn)  
   - 用哈希前缀和巧妙处理循环节判断  
   - 代码结构清晰，注释详细  

#### 2. 忆殇（4.5星）  
- **亮点**  
   - 明确列出循环节判断的三大数学性质  
   - 用`nxt[]`数组记录每个数的最小质因子  
   - 代码中对质因数分解过程有详细注释  

#### 3. Leap_Frog（4星）  
- **亮点**  
   - 代码极度简洁（仅50行）  
   - 用`mx[]`数组代替线性筛，优化内存占用  
   - 哈希基数和模数选择巧妙避免碰撞  

---

### 最优思路与技巧提炼

#### 关键步骤
1. **预处理最小质因子**  
   ```cpp
   for (int i=2; i<=n; i++) {
       if (!vis[i]) pri[++cnt] = i, nxt[i] = i;
       for (int j=1; j<=cnt && i*pri[j]<=n; j++) {
           vis[i*pri[j]] = true;
           nxt[i*pri[j]] = pri[j];
           if (i%pri[j] == 0) break;
       }
   }
   ```
   - 时间复杂度 O(n)，空间 O(n)

2. **质因数分解与试除**  
   ```cpp
   while (len != 1) {
       int p = nxt[len];
       if (check(l, r, ans/p)) ans /= p;
       len /= p;
   }
   ```
   - 逐步试除质因子，确保得到最小解

3. **哈希比较判断循环节**  
   ```cpp
   bool check(int l, int r, int len) {
       return get_hash(l, r-len) == get_hash(l+len, r);
   }
   ```

#### 优化技巧
- **哈希参数选择**：使用双哈希或大质数（如 1e9+7）降低碰撞概率  
- **预处理幂次**：预先计算 base 的幂次，避免重复计算  
- **质因数存储**：分解时直接存储质因子，无需额外排序  

---

### 同类型题与算法套路

#### 类似算法思路
- **循环节问题**：KMP的next数组性质  
- **因数分解优化**：Pollard-Rho算法（大数分解）  
- **区间哈希比较**：二维前缀哈希（矩阵循环节）  

#### 推荐题目
1. **P4391** [BOI2009]Radio Transmission（循环节扩展应用）  
2. **P3435** [POI2006]OKR-Periods of Words（KMP与最长循环节）  
3. **P2375** [NOI2014]动物园（KMP性质与周期计数）  

---

### 个人心得摘录
- **调试教训**  
  > "哈希基数选择过大导致超时，改用较小的基数后通过" —— RenaMoe  
  > "忘记处理 len=1 的特殊情况，WA 了 3 次" —— Leap_Frog  

- **优化经验**  
  > "预处理质因数分解比每次sqrt(n)枚举快 10 倍" —— 忆殇  
  > "用自然溢出哈希省去取模运算，加速明显" —— raincity  

---

### 可视化与算法演示

#### 核心算法动画流程
```javascript
// 伪代码示例
class Animation {
  constructor(str) {
    this.str = str; // 原始字符串
    this.canvas = document.getElementById('canvas');
    this.ctx = this.canvas.getContext('2d');
    this.speed = 500; // 动画速度（ms）
  }

  // 高亮区间 [l, r]
  highlight(l, r, color) {
    this.ctx.fillStyle = color;
    this.ctx.fillRect(l*10, 0, (r-l+1)*10, 50);
  }

  // 分解质因数过程
  async factorize(len) {
    let factors = [];
    while (len > 1) {
      let p = nxt[len];
      factors.push(p);
      len /= p;
    }
    return factors;
  }

  // 主演示流程
  async demo(l, r) {
    let len = r - l + 1;
    let ans = len;
    let factors = await this.factorize(len);
    
    for (let p of factors) {
      this.highlight(l, r, '#FF0000'); // 红色高亮当前区间
      let candidate = ans / p;
      if (checkHash(l, r, candidate)) {
        ans = candidate;
        this.highlight(l, l+candidate-1, '#00FF00'); // 绿色显示有效循环节
      }
      await sleep(this.speed);
    }
  }
}
```

#### 音效设计
- **比较成功**：8-bit 风格 "叮" 声（频率 800Hz）  
- **分解质因数**：电子合成爆破音  
- **最终结果**：马里奥吃到金币音效  

---

### 完整代码参考（RenaMoe 题解核心）
```cpp
#include <cstdio>
#include <cctype>
typedef long long ll;
const int N = 5e5 + 5, MOD = 1e9+7;

int n, m, g[N];
ll hash[N], pow[N];
char s[N];
bool vis[N];

void euler() { /* 线性筛预处理略 */ }

ll calc(int l, int r) {
    return ((hash[r] - hash[l-1]*pow[r-l+1]) % MOD + MOD) % MOD;
}

int main() {
    euler();
    scanf("%s", s+1);
    for (int i=1; i<=n; i++)
        hash[i] = (hash[i-1]*29 + s[i]-'a') % MOD;
    
    while (m--) {
        int l, r, len = r-l+1, ans = len;
        while (len > 1) {
            int p = g[len];
            if (calc(l, r - ans/p) == calc(l + ans/p, r))
                ans /= p;
            len /= p;
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---
处理用时：92.00秒