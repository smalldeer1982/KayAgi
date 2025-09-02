# 题目信息

# [AGC003D] Anticube

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc003/tasks/agc003_d

高橋君は誕生日にお母さんから正の整数 $ s_1,...,s_N $ をもらいました。ただし、要素の重複は許されます。 高橋君は、これらの$ N $個の整数のうちのいくつかを丸で囲みます。

高橋君は立方数が嫌いなので、$ s_i,s_j(i\ ≠\ j) $の両方が丸で囲まれているなら、その積$ s_is_j $は立方数とならないようにしたいです。 例えば、$ s_1=1,s_2=1,s_3=2,s_4=4 $のとき、$ s_1 $と$ s_2 $を同時に丸で囲むことはできません。また、$ s_3 $と$ s_4 $を同時に丸で囲むこともできません。

高橋君が丸で囲むことができる整数の個数の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N\ ≦\ 10^5 $
- $ 1\ ≦\ s_i\ ≦\ 10^{10} $
- 入力はすべて整数である。

### Sample Explanation 1

$ 1,2,3,5,6,7 $ を丸で囲むことができます。

## 样例 #1

### 输入

```
8

1

2

3

4

5

6

7

8```

### 输出

```
6```

## 样例 #2

### 输入

```
6

2

4

8

16

32

64```

### 输出

```
3```

## 样例 #3

### 输入

```
10

1

10

100

1000000007

10000000000

1000000009

999999999

999

999

999```

### 输出

```
9```

# AI分析结果



---

## 【算法分类】  
数论（质因数分解、立方数处理） + 哈希映射

---

## 【题解思路与解决难点】  
### **核心思路**  
1. **预处理质数**：筛出至立方根（约2160）的质数，用于分解立方因子。  
2. **去除立方因子**：将每个数分解，去除质数的立方因子，得到简化形式。  
3. **处理剩余质因数**：根据剩余部分分类（质数、平方数等）生成对应的“补数”。  
4. **哈希统计配对**：用哈希表统计每个简化形式及其补数的出现次数，取最大值。  

### **关键难点与解决**  
- **质因数分解优化**：只分解到立方根，剩余部分分类讨论，避免分解大质数。  
- **补数生成逻辑**：通过平方或平方根处理，确保补数不超出数据范围。  
- **哈希去重处理**：每统计一对后清空计数，避免重复计算。  

---

## 【题解评分】  
**CYJian (5星)**  
- 思路清晰，代码高效，用预处理质数优化分解。  
- 分类处理剩余质因数，逻辑严谨。  
- 时间复杂度低（O(n√³s)），适合大数据。  

**K8He (4星)**  
- 明确质因数模3思路，代码结构简洁。  
- 补数生成方法直观，但未优化大质数处理。  

**yijan (4星)**  
- 分层处理质数范围，逻辑清晰。  
- 代码可读性高，但部分边界需注意。  

---

## 【最优思路提炼】  
1. **立方因子剔除**：用预处理质数快速去除立方因子，简化计算。  
2. **补数生成策略**：  
   - 若剩余部分是质数p，补数为p²。  
   - 若剩余是平方数p²，补数为p。  
   - 其他情况直接加入答案（无法配对）。  
3. **哈希统计最大值**：每组配对取数量较多者，避免重复统计。  

---

## 【相似题目推荐】  
1. **洛谷 P2423 - 质因数分解**（分解优化）  
2. **AT ABC284E - Count Simple Paths**（哈希统计配对）  
3. **CF1493D - GCD of an Array**（质因数分解与计数）  

---

## 【算法可视化设计】  
### **动画演示步骤**  
1. **质数筛法**：展示筛出立方根质数的过程，像素块标记质数。  
2. **分解立方因子**：数被拆解为小质数立方块，剩余部分高亮。  
3. **生成补数**：剩余部分根据类型（质数/平方数）生成对应补数，显示补数公式。  
4. **哈希配对**：每对简化形式与补数以不同颜色显示，统计较大值并清空计数。  

### **复古像素风格**  
- **颜色方案**：质数用绿色，立方因子用红色，补数用蓝色。  
- **音效设计**：分解时“切割”音效，配对成功时“得分”音效，背景8位音乐。  
- **自动演示**：按步分解并生成补数，可调节速度或单步执行。  

---

## 【核心代码实现】  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1e5 + 5, CUBE = 2160;
vector<int> primes;
ll s[MAXN];

void sieve() {
    vector<bool> is_prime(CUBE + 1, true);
    for (int i = 2; i <= CUBE; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= CUBE; j += i) 
                is_prime[j] = false;
        }
    }
}

ll remove_cubic(ll x) {
    for (int p : primes) {
        ll cube = 1LL * p * p * p;
        while (x % cube == 0) x /= cube;
    }
    return x;
}

int main() {
    sieve();
    int n; cin >> n;
    map<ll, ll> cnt;

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        s[i] = remove_cubic(s[i]);
        if (s[i] == 1) { ans = 1; continue; }

        ll norm = 1, comp = 1;
        // 处理小质数部分
        for (int p : primes) {
            if (s[i] % p) continue;
            int cnt = 0;
            while (s[i] % p == 0) s[i] /= p, cnt++;
            cnt %= 3;
            if (cnt == 1) norm *= p, comp *= p * p;
            else if (cnt == 2) norm *= p * p, comp *= p;
        }
        // 处理剩余部分
        if (s[i] > 1) {
            ll sq = sqrt(s[i]);
            if (sq * sq == s[i]) comp *= sq, norm *= sq * sq;
            else comp *= s[i] * s[i], norm *= s[i];
        }
        cnt[norm]++;
    }

    for (auto &[k, v] : cnt) {
        if (k == 1) continue;
        ll c = (ll)sqrt(k * comp);
        ans += max(v, cnt[comp]);
        cnt[k] = cnt[comp] = 0;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 【可视化代码片段】  
```javascript
// 示例：Canvas绘制质数筛法
const canvas = document.getElementById('prime-sieve');
const ctx = canvas.getContext('2d');
const SIZE = 20; // 每个质数块大小

function drawPrimes(primes) {
  ctx.fillStyle = '#2ecc71'; // 质数绿色
  primes.forEach(p => {
    const x = (p % 40) * SIZE;
    const y = Math.floor(p / 40) * SIZE;
    ctx.fillRect(x, y, SIZE-1, SIZE-1);
  });
}
// 初始化时调用筛法并绘制
sievePrimes().then(drawPrimes);
```

---
处理用时：93.97秒