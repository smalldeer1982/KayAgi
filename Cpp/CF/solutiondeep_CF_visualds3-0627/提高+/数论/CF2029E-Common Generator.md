# 题目信息

# Common Generator

## 题目描述

对于两个整数 $x$ 和 $y$（$x,y\ge 2$），如果且仅如果可以通过若干次（可能为零次）以下操作将 $x$ 变换为 $y$，则称 $x$ 是 $y$ 的一个**生成器**：

* 选取一个 $x$ 的约数 $d$（$d\ge 2$），然后将 $x$ 增加 $d$。

例如：

* $3$ 是 $8$ 的生成器，因为可以执行如下操作：

  $$
    3 \xrightarrow{d = 3} 6 \xrightarrow{d = 2} 8
  $$
* $4$ 是 $10$ 的生成器，因为可以执行如下操作：

  $$
    4 \xrightarrow{d = 4} 8 \xrightarrow{d = 2} 10
  $$
* $5$ 不是 $6$ 的生成器，因为无法通过上述操作将 $5$ 转换为 $6$。

现在，Kevin 给你一个长度为 $n$ 的数组 $a$，其中包含两两不同的整数（$a_i \ge 2$）。

你需要寻找一个整数 $x\ge 2$，使得对每个 $1\le i\le n$，$x$ 都是 $a_i$ 的生成器；如果不存在这样的整数，则输出 $-1$。

## 说明/提示

* 对于第一个测试用例，取 $x=2$：

  * $2$ 是 $8$ 的生成器，因为可以：

    $$
      2 \xrightarrow{d = 2} 4
      \xrightarrow{d = 4} 8
    $$
  * $2$ 是 $9$ 的生成器，因为可以：

    $$
      2 \xrightarrow{d = 2} 4
      \xrightarrow{d = 2} 6
      \xrightarrow{d = 3} 9
    $$
  * $2$ 是 $10$ 的生成器，因为可以：

    $$
      2 \xrightarrow{d = 2} 4
      \xrightarrow{d = 2} 6
      \xrightarrow{d = 2} 8
      \xrightarrow{d = 2} 10
    $$
* 对于第二个测试用例，可以证明不存在同时生成 $\{2,3,4,5\}$ 的共同生成器。

## 样例 #1

### 输入

```
4
3
8 9 10
4
2 3 4 5
2
147 154
5
3 6 8 25 100000```

### 输出

```
2
-1
7
3```

# AI分析结果



## 唯一算法分类
**数论（质数处理、线性筛）**

---

## 综合分析与结论

### 核心思路与算法要点
1. **质数判定与分类讨论**  
   - 质数只能由自身生成，若数组中出现两个不同质数则无解  
   - 若数组无质数，则 `2` 可生成所有合数  
   - 若数组有唯一质数 `p`，需验证其能否生成其他元素  

2. **生成条件判断**  
   - **偶合数**：需满足 `2p ≤ a_i`  
   - **奇合数**：需满足 `2p ≤ (a_i - 最小质因子)`  
   - 预处理每个数的**最小质因子**（通过线性筛）  

3. **高效预处理**  
   - 使用线性筛法预处理质数与最小质因子  
   - 奇合数的生成条件转化为 `a_i - min_prime_factor` 的验证  

### 可视化设计思路
1. **像素风格筛法演示**  
   - **Canvas网格**：展示数字 2~N 的筛法过程，被标记为质数的方块显示绿色  
   - **高亮当前操作**：如筛选中 `i=6` 时，用红色边框高亮其最小质因子 `2`  
   - **音效触发**：质数发现时播放清脆音效，合数标记时播放低沉音效  

2. **生成条件检查动画**  
   - **分步验证**：对每个 `a_i` 显示质数判断结果，偶/奇合数分别用不同颜色标记  
   - **条件判定**：奇合数展示 `a_i - min_prime_factor` 的减法过程，结果与 `2p` 比较  
   - **失败提示**：若条件不满足，播放短促错误音效并闪烁红色边框  

---

## 题解清单（≥4星）

### 1. 作者：_lmh_（⭐️⭐️⭐️⭐️⭐️）
- **亮点**：完整数学证明 + 高效线性筛实现  
- **核心贡献**：  
  - 引理 1-4 严格证明生成条件  
  - 预处理 `rem[]` 存储奇偶合数的关键阈值  
  ```cpp
  // 预处理奇合数的 rem[a_i]
  if (o%2 == 0) rem[o] = o/2;
  else rem[o] = prime[j] * (i-1)/2;
  ```

### 2. 作者：ny_jerry2（⭐️⭐️⭐️⭐️）
- **亮点**：代码简洁 + 埃式筛法实现  
- **关键技巧**：  
  - 利用 `mark[]` 数组标记最小质因子  
  - 直接通过奇偶性判断生成条件  
  ```cpp
  if(a[i]&1) check a[i]-d[a[i]] >= 2p
  else check a[i] >= 2p
  ```

### 3. 作者：tai_chi（⭐️⭐️⭐️⭐️）
- **亮点**：模块化设计 + 清晰的分类逻辑  
- **实现特点**：  
  - 单独 `init()` 函数处理筛法  
  - 主函数逻辑分层明确（质数计数→条件验证）  
  ```cpp
  for(int i=1;i<=n;i++) 
    if(!vis[a[i]]) cnt++, p=a[i];
  ```

---

## 核心代码实现

### 线性筛预处理最小质因子
```cpp
const int N = 4e5 + 7;
int prime[N], nP, rem[N];
bool ok[N];

void initPrime() {
    ok[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!ok[i]) prime[++nP] = i;
        for (int j = 1; j <= nP && i * prime[j] < N; ++j) {
            int o = i * prime[j];
            ok[o] = 1;
            rem[o] = (o % 2 == 0) ? o / 2 : prime[j] * (i - 1);
            if (i % prime[j] == 0) break;
        }
    }
}
```

### 主逻辑判断
```cpp
int main() {
    initPrime();
    int T, n, x;
    cin >> T;
    while (T--) {
        cin >> n;
        x = 0;
        vector<int> a(n);
        for (auto &num : a) {
            cin >> num;
            if (!ok[num]) { // 质数检测
                if (x == 0 || x == num) x = num;
                else x = -1;
            }
        }
        if (x == -1) { cout << -1 << endl; continue; }
        if (x == 0) { cout << 2 << endl; continue; }
        // 验证生成条件
        for (auto num : a) {
            if (num != x && rem[num] < x) {
                x = -1; break;
            }
        }
        cout << x << endl;
    }
}
```

---

## 同类型题目推荐
1. **CF1366D** - 分解数为两个互质数之和  
2. **P3383** - 线性筛素数模板题  
3. **CF1294D** - 数论构造与模运算  

---

## 个人心得摘录
> "打表发现质数只能由自身生成时，才意识到多个质数必定无解。这一观察大幅简化了问题。" —— I_will_AKIOI  
> "奇合数的生成条件 `a_i - min_prime` 是关键，调试时发现必须严格大于等于 `2p`" —— Exp10re  

---

## 可视化与算法演示（伪代码）

```javascript
// Canvas 初始化
const canvas = document.getElementById('sieve-canvas');
const ctx = canvas.getContext('2d');
const CELL_SIZE = 20;

function drawNumber(num, color) {
    const x = (num % 10) * CELL_SIZE;
    const y = Math.floor(num / 10) * CELL_SIZE;
    ctx.fillStyle = color;
    ctx.fillRect(x, y, CELL_SIZE, CELL_SIZE);
}

// 线性筛动画演示
async function animateSieve() {
    for (let i = 2; i < N; i++) {
        if (!ok[i]) { // 质数
            drawNumber(i, '#90EE90');
            playSound('prime'); // 清脆音效
            await delay(100);
        }
        for (let p of primes) {
            if (i * p >= N) break;
            drawNumber(i*p, '#FFB6C1'); // 合数标记
            playSound('composite'); // 低沉音效
            await delay(50);
        }
    }
}
```

---
处理用时：92.93秒