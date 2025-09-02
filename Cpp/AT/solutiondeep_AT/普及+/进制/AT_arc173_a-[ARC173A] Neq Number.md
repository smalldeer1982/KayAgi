# 题目信息

# [ARC173A] Neq Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc173/tasks/arc173_a

正整数 $ X $ が以下の条件を満たすとき、$ X $ は **“Neq Number”** であるといいます。

- $ X $ を十進法表記した際、どの隣接する $ 2 $ 文字も相異なる
 
例えば $ 1,173,9090 $ は “Neq Number” です。一方、 $ 22,6335 $ は “Neq Number” ではありません。

正整数 $ K $ が与えられます。小さいほうから $ K $ 番目の “Neq Number” を求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 100 $
- $ 1\ \leq\ K\ \leq\ 10^{12} $
- 入力される値はすべて整数
 
### Sample Explanation 1

$ 1 $ つめのテストケースについて、 “Neq Number” を小さいものから $ 25 $ 個あげていくと - $ 1 $ から $ 9 $ までの整数の $ 9 $ 個 - $ 10 $ から $ 19 $ までの整数のうち、 $ 11 $ を除いた $ 9 $ 個 - $ 20 $ から $ 27 $ までの整数のうち、 $ 22 $ を除いた $ 7 $ 個 となります。よって、小さいほうから $ 25 $ 番目の “Neq Number” は $ 27 $ となります。

## 样例 #1

### 输入

```
3

25

148

998244353```

### 输出

```
27

173

2506230721```

# AI分析结果

### 题目内容重写
#### [ARC173A] Neq Number

**题目描述**

正整数 $X$ 如果满足以下条件，则称为 **“Neq Number”**：

- 当 $X$ 用十进制表示时，任何相邻的两个数字都不相同。

例如，$1$、$173$、$9090$ 是 “Neq Number”，而 $22$、$6335$ 不是。

给定正整数 $K$，请找出从小到大的第 $K$ 个 “Neq Number”。

**输入格式**

输入包含 $T$ 个测试用例，每个测试用例给出一个整数 $K$。

**输出格式**

对于每个测试用例，输出第 $K$ 个 “Neq Number”。

**样例输入**
```
3
25
148
998244353
```

**样例输出**
```
27
173
2506230721
```

**提示**

- $1 \leq T \leq 100$
- $1 \leq K \leq 10^{12}$
- 输入的所有值均为整数

### 题解分析与结论

#### 综合分析
本题的核心是找到第 $K$ 个满足相邻数字不相同的正整数。由于 $K$ 的范围很大（$1 \leq K \leq 10^{12}$），直接枚举显然不可行。因此，大多数题解采用了**二分查找**结合**数位 DP**或**进制转换**的思路来高效求解。

#### 关键思路与技巧
1. **二分查找**：通过二分查找确定第 $K$ 个 Neq Number 的候选值，结合数位 DP 或进制转换来快速计算小于等于某个值的 Neq Number 的数量。
2. **数位 DP**：利用动态规划的思想，预处理出不同位数下满足条件的数字数量，结合二分查找快速定位第 $K$ 个 Neq Number。
3. **进制转换**：将问题转化为 9 进制问题，因为每一位有 9 种选择（第一位不能为 0，后续不能与前一位相同），从而直接通过进制转换得到答案。

#### 最优思路
最优的思路是**进制转换**，因为它避免了复杂的数位 DP 预处理，直接通过 9 进制的思想快速构造答案，时间复杂度为 $O(T \log_{10} K)$，效率较高。

### 精选题解

#### 题解1：无名之雾（5星）
**关键亮点**：
- 通过 9 进制转换直接构造答案，避免了复杂的数位 DP 预处理。
- 代码简洁，思路清晰，时间复杂度低。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int T;
    cin>>T;
    while(T--){
        int k;
        cin>>k;
        int wei=0,cheng=1,last=0;
        while(k>=cheng) k-=cheng,wei++,cheng*=9;
        while(wei){
            cheng/=9,wei--;
            cout<<k/cheng+(k/cheng>=last);
            last=k/cheng+(k/cheng>=last);
            k-=k/cheng*cheng;
        }
        cout<<endl;
    }
    return 0;
}
```

#### 题解2：TankYu（4星）
**关键亮点**：
- 通过数位 DP 预处理，结合二分查找快速定位答案。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int num[20], every[20], pre[20];
signed main(){
    int t; cin >> t;
    num[1] = 9; num[2] = 81;
    for (int i = 3; i <= 17; i++) num[i] = num[i - 1] * 8 + num[i - 2] * 9;
    for (int i = 1; i <= 17; i++) pre[i] = pre[i - 1] + num[i];
    for (int i = 1; i <= 17; i++) every[i] = num[i] / 9;
    while (t--){
        LL k; cin >> k;
        if (k <= 9) { cout << k << '\n'; continue; }
        int now = 17; LL ans = 0;
        while (k){
            ans *= 10;
            if (ans == 0){
                if (pre[now - 1] <= k){
                    if (now != 1){
                        LL tmp = (k - pre[now - 1] + every[now] - 1) / every[now];
                        ans += tmp; k -= tmp * every[now];
                    } else { ans += k - 1; break; }
                }
            } else {
                if (pre[now - 1] <= k){
                    if (now != 1){
                        LL tmp = (k - pre[now - 1] + every[now] - 1) / every[now];
                        if (tmp >= ans / 10 % 10) ans += tmp - 1;
                        else ans += tmp;
                        k -= (tmp + 1) * every[now];
                    } else {
                        if (k > ans / 10 % 10) ans += k;
                        else ans += k - 1;
                        break;
                    }
                }
            }
            now--;
            if (now == 0) break;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

#### 题解3：XYQ_102（4星）
**关键亮点**：
- 通过 9 进制转换直接构造答案，代码简洁，思路清晰。
- 时间复杂度低，适合大规模数据。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int T; cin >> T;
    while(T--){
        int k; cin >> k;
        int len = 1;
        while(pow(9, len) < k) k -= pow(9, len++);
        int pre = 0;
        for(int i = 1; i <= len; i++){
            for(int j = 0; j <= 9; j++){
                if(j == pre) continue;
                if(pow(9, len - i) >= k){
                    putchar('0' + j); pre = j; break;
                } else k -= pow(9, len - i);
            }
        }
        putchar('\n');
    }
    return 0;
}
```

### 扩展思路与推荐题目
#### 扩展思路
- **类似问题**：可以将 Neq Number 的条件扩展到其他进制，或者增加更多的限制条件（如数字必须递增或递减）。
- **优化技巧**：对于大规模数据，预处理和二分查找是常见的优化手段，可以显著减少时间复杂度。

#### 推荐题目
1. [P2657 windy 数](https://www.luogu.com.cn/problem/P2657)
2. [P2602 数字计数](https://www.luogu.com.cn/problem/P2602)
3. [P4127 同类分布](https://www.luogu.com.cn/problem/P4127)

---
处理用时：56.91秒