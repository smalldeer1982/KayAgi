# 题目信息

# Strange Definition

## 题目描述

Let us call two integers $ x $ and $ y $ adjacent if $ \frac{lcm(x, y)}{gcd(x, y)} $ is a perfect square. For example, $ 3 $ and $ 12 $ are adjacent, but $ 6 $ and $ 9 $ are not.

Here $ gcd(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ , and $ lcm(x, y) $ denotes the [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) of integers $ x $ and $ y $ .

You are given an array $ a $ of length $ n $ . Each second the following happens: each element $ a_i $ of the array is replaced by the product of all elements of the array (including itself), that are adjacent to the current value.

Let $ d_i $ be the number of adjacent elements to $ a_i $ (including $ a_i $ itself). The beauty of the array is defined as $ \max_{1 \le i \le n} d_i $ .

You are given $ q $ queries: each query is described by an integer $ w $ , and you have to output the beauty of the array after $ w $ seconds.

## 说明/提示

In the first test case, the initial array contains elements $ [6, 8, 4, 2] $ . Element $ a_4=2 $ in this array is adjacent to $ a_4=2 $ (since $ \frac{lcm(2, 2)}{gcd(2, 2)}=\frac{2}{2}=1=1^2 $ ) and $ a_2=8 $ (since $ \frac{lcm(8,2)}{gcd(8, 2)}=\frac{8}{2}=4=2^2 $ ). Hence, $ d_4=2 $ , and this is the maximal possible value $ d_i $ in this array.

In the second test case, the initial array contains elements $ [12, 3, 20, 5, 80, 1] $ . The elements adjacent to $ 12 $ are $ \{12, 3\} $ , the elements adjacent to $ 3 $ are $ \{12, 3\} $ , the elements adjacent to $ 20 $ are $ \{20, 5, 80\} $ , the elements adjacent to $ 5 $ are $ \{20, 5, 80\} $ , the elements adjacent to $ 80 $ are $ \{20, 5, 80\} $ , the elements adjacent to $ 1 $ are $ \{1\} $ . After one second, the array is transformed into $ [36, 36, 8000, 8000, 8000, 1] $ .

## 样例 #1

### 输入

```
2
4
6 8 4 2
1
0
6
12 3 20 5 80 1
1
1```

### 输出

```
2
3```

# AI分析结果

### 题目翻译
## 奇怪的定义

### 题目描述
如果 $\frac{lcm(x, y)}{gcd(x, y)}$ 是一个完全平方数，我们就称两个整数 $x$ 和 $y$ 相邻。例如，$3$ 和 $12$ 相邻，但 $6$ 和 $9$ 不相邻。

这里 $gcd(x, y)$ 表示整数 $x$ 和 $y$ 的[最大公约数 (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor)，$lcm(x, y)$ 表示整数 $x$ 和 $y$ 的[最小公倍数 (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple)。

给定一个长度为 $n$ 的数组 $a$。每秒都会发生以下情况：数组中的每个元素 $a_i$ 都会被数组中所有与当前值相邻的元素（包括它本身）的乘积所替换。

设 $d_i$ 为与 $a_i$ 相邻的元素的数量（包括 $a_i$ 本身）。数组的美观度定义为 $\max_{1 \le i \le n} d_i$。

给定 $q$ 个查询：每个查询由一个整数 $w$ 描述，你需要输出 $w$ 秒后数组的美观度。

### 说明/提示
在第一个测试用例中，初始数组包含元素 $[6, 8, 4, 2]$。此数组中的元素 $a_4 = 2$ 与 $a_4 = 2$ 相邻（因为 $\frac{lcm(2, 2)}{gcd(2, 2)}=\frac{2}{2}=1=1^2$），也与 $a_2 = 8$ 相邻（因为 $\frac{lcm(8, 2)}{gcd(8, 2)}=\frac{8}{2}=4=2^2$）。因此，$d_4 = 2$，这是该数组中 $d_i$ 的最大可能值。

在第二个测试用例中，初始数组包含元素 $[12, 3, 20, 5, 80, 1]$。与 $12$ 相邻的元素是 $\{12, 3\}$，与 $3$ 相邻的元素是 $\{12, 3\}$，与 $20$ 相邻的元素是 $\{20, 5, 80\}$，与 $5$ 相邻的元素是 $\{20, 5, 80\}$，与 $80$ 相邻的元素是 $\{20, 5, 80\}$，与 $1$ 相邻的元素是 $\{1\}$。一秒后，数组变为 $[36, 36, 8000, 8000, 8000, 1]$。

### 样例 #1
#### 输入
```
2
4
6 8 4 2
1
0
6
12 3 20 5 80 1
1
1
```
#### 输出
```
2
3
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先根据数论知识判断两个数是否相邻，再分析数组元素在每秒变换后的规律，最后根据询问的秒数输出对应答案。

- **思路对比**：各题解均通过质因数分解判断相邻关系，但在处理元素变换时，有的按奇偶分组讨论，有的引入“核”的概念，有的将质因数指数对 2 取余转化为 01 串处理。
- **算法要点**：普遍采用质因数分解，用哈希表（如 `map`、`unordered_map`）统计相邻元素个数。部分题解还预处理质数，优化质因数分解过程。
- **解决难点**：主要解决了判断相邻关系和处理元素变换的问题，通过分析发现元素变换存在规律，即最多变化一次，后续答案不变，从而将问题简化为 $w = 0$ 和 $w > 0$ 两种情况。

### 高评分题解
- **作者：fanfansann (赞：14)，4星**
    - **关键亮点**：思路详细，从数论知识逐步推导，结合分类讨论清晰地分析了元素变换的各种情况，代码实现简单易懂。
    - **个人心得**：作者提到做题时在演草纸上画思维导图分类讨论，不到 10 分钟就理清思路，写题解时为详细呈现思考过程所以内容较多。
- **作者：灵茶山艾府 (赞：7)，4星**
    - **关键亮点**：引入“核”的概念，简洁地描述了相邻关系的判断方法，对元素变换的分析清晰明了，代码结构清晰。
- **作者：Fairicle (赞：3)，4星**
    - **关键亮点**：通过质因数指数对 2 取余转化为 01 串的方式判断相邻关系，对元素变换的证明逻辑严谨，代码实现简洁。

### 重点代码
#### fanfansann 的代码
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;
const int N = 3e5 + 7, mod = 1e9 + 7;
typedef long long ll;
unordered_map<int, int> Hash;
void get_factor(int x)
{
    for(int i = 2; ; ++ i) {
        int even = i * i;
        while(x % even == 0 && x >= even) x /= even;
        if(x < even) break;
    }
    Hash[x] ++ ;
}
int n, m, t, q;
int main()
{
    scanf("%d", &t);
    while(t -- ) {
        Hash.clear();
        scanf("%d", &n);
        for(int i = 1; i <= n; ++ i) {
            int a;
            scanf("%d", &a);
            get_factor(a);
        }
        int ans1 = 0, ans2 = 0;
        for(auto it = Hash.begin(); it != Hash.end(); ++ it) {
            ans1 = max(ans1, it -> second);
            if(it -> second % 2 == 0 || it -> first == 1)
                ans2 += it->second;
        }
        ans2 = max(ans2, ans1);
        scanf("%d", &q);
        for(int i = 1; i <= q; ++ i) {
            ll w;
            scanf("%lld", &w);
            if(w == 0)
                printf("%d\n", ans1);
            else printf("%d\n", ans2);
        }
    }
    return 0;
}
```
**核心实现思想**：`get_factor` 函数对输入的数进行质因数分解，将其所有质因子的次方压成 0 或 1，用 `Hash` 表统计相同结果的个数。通过遍历 `Hash` 表，分别计算 $w = 0$ 和 $w > 0$ 时的答案。

#### 灵茶山艾府的代码
```go
package main

import (
    "bufio"
    . "fmt"
    "os"
)

func main() {
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()

    const mx int = 1e6
    lpf := [mx + 1]int{1: 1}
    for i := 2; i <= mx; i++ {
        if lpf[i] == 0 {
            for j := i; j <= mx; j += i {
                if lpf[j] == 0 {
                    lpf[j] = i
                }
            }
        }
    }
    core := func(x int) int {
        c := 1
        for x > 1 {
            p := lpf[x]
            e := 1
            for x /= p; lpf[x] == p; x /= p {
                e ^= 1
            }
            if e > 0 {
                c *= p
            }
        }
        return c
    }

    var T, n, v, q int
    var w int64
    for Fscan(in, &T); T > 0; T-- {
        cnt := map[int]int{}
        for Fscan(in, &n); n > 0; n-- {
            Fscan(in, &v)
            cnt[core(v)]++
        }
        maxC, c1 := 0, cnt[1]
        for v, c := range cnt {
            maxC = max(maxC, c)
            if v > 1 && c&1 == 0 {
                c1 += c
            }
        }
        for Fscan(in, &q); q > 0; q-- {
            if Fscan(in, &w); w == 0 {
                Fprintln(out, maxC)
            } else {
                Fprintln(out, max(maxC, c1))
            }
        }
    }
}

func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}
```
**核心实现思想**：先预处理最小质因数数组 `lpf`，`core` 函数计算数的“核”。用 `cnt` 表统计相同“核”的个数，通过遍历 `cnt` 表计算 $w = 0$ 和 $w > 0$ 时的答案。

#### Fairicle 的代码
```cpp
#include"bits/stdc++.h"
using namespace std;
#define N 300010
#define ri register int
#define ll long long
inline ll rd(){
    ll x=0,flg=1;
    char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-') flg=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+(ch^48);ch=getchar();}
    return x*flg;
}
int t,n,a[N],q,tmp,cnt,fir,sec,pre;
ll w;
int main(){
    t=rd();
    while(t--){
        n=rd();
        for(ri i=1;i<=n;++i){
            a[i]=rd();tmp=a[i];
            for(ri j=2;j*j<=tmp;++j){
                if(tmp%j==0){
                    cnt=0;
                    while(tmp%j==0) tmp/=j,a[i]/=j,cnt++;
                    if(cnt&1) a[i]*=j;
                }
            }
        }
        
        fir=0,sec=0,pre=0;
        sort(a+1,a+1+n);a[n+1]=0;
        for(ri i=1;i<=n;++i){
            if(a[i]!=a[i+1]) {fir=max(fir,i-pre);if(a[i]==1) sec+=i-pre;else if(((i-pre)&1)^1) sec+=i-pre;pre=i;} 
        }
        q=rd();sec=max(sec,fir);
        while(q--) {w=rd();if(w) printf("%d\n",sec);else printf("%d\n",fir);} 
    }
    return 0;
}
```
**核心实现思想**：对数组中的每个数进行质因数分解，将质因数指数对 2 取余。排序后统计相同结果的个数，分别计算 $w = 0$ 和 $w > 0$ 时的答案。

### 关键思路或技巧
- **质因数分解**：将数分解为质因数的乘积，通过质因数的指数判断相邻关系。
- **哈希表统计**：用哈希表统计相同质因数分解结果的个数，方便计算答案。
- **规律分析**：通过分析元素变换的规律，将问题简化为 $w = 0$ 和 $w > 0$ 两种情况。

### 拓展思路
同类型题可能会改变相邻关系的定义，或对数组元素的变换规则进行调整，但核心思路仍可围绕数论知识和规律分析展开。类似算法套路包括利用质因数分解解决数论问题，通过分析操作规律简化问题。

### 推荐题目
- [P1072  Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)：涉及最大公约数和最小公倍数的计算，与本题数论知识相关。
- [P1463  [POI2002][HAOI2007]反素数](https://www.luogu.com.cn/problem/P1463)：需要对质因数分解和数的性质有深入理解。
- [P2152 [SDOI2009]SuperGCD](https://www.luogu.com.cn/problem/P2152)：考察高精度和最大公约数的计算。

---
处理用时：88.17秒