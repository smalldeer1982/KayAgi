# 题目信息

# Make Almost Equal With Mod

## 题目描述

[xi - Solar Storm](https://soundcloud.com/yugenero/xi-solar-storm)

⠀



You are given an array $ a_1, a_2, \dots, a_n $ of distinct positive integers. You have to do the following operation exactly once:

- choose a positive integer $ k $ ;
- for each $ i $ from $ 1 $ to $ n $ , replace $ a_i $ with $ a_i \text{ mod } k^\dagger $ .

Find a value of $ k $ such that $ 1 \leq k \leq 10^{18} $ and the array $ a_1, a_2, \dots, a_n $ contains exactly $ 2 $ distinct values at the end of the operation. It can be shown that, under the constraints of the problem, at least one such $ k $ always exists. If there are multiple solutions, you can print any of them.

 $ ^\dagger $ $ a \text{ mod } b $ denotes the remainder after dividing $ a $ by $ b $ . For example:

- $ 7 \text{ mod } 3=1 $ since $ 7 = 3 \cdot 2 + 1 $
- $ 15 \text{ mod } 4=3 $ since $ 15 = 4 \cdot 3 + 3 $
- $ 21 \text{ mod } 1=0 $ since $ 21 = 21 \cdot 1 + 0 $

## 说明/提示

In the first test case, you can choose $ k = 7 $ . The array becomes $ [8 \text{ mod } 7, 15 \text{ mod } 7, 22 \text{ mod } 7, 30 \text{ mod } 7] = [1, 1, 1, 2] $ , which contains exactly $ 2 $ distinct values ( $ \{1, 2\} $ ).

In the second test case, you can choose $ k = 30 $ . The array becomes $ [0, 0, 8, 0, 8] $ , which contains exactly $ 2 $ distinct values ( $ \{0, 8\} $ ). Note that choosing $ k = 10 $ would also be a valid solution.

In the last test case, you can choose $ k = 10^{18} $ . The array becomes $ [2, 1] $ , which contains exactly $ 2 $ distinct values ( $ \{1, 2\} $ ). Note that choosing $ k = 10^{18} + 1 $ would not be valid, because $ 1 \leq k \leq 10^{18} $ must be true.

## 样例 #1

### 输入

```
5
4
8 15 22 30
5
60 90 98 120 308
6
328 769 541 986 215 734
5
1000 2000 7000 11000 16000
2
2 1```

### 输出

```
7
30
3
5000
1000000000000000000```

# AI分析结果

### 题目内容翻译
## 题目描述
[xi - Solar Storm](https://soundcloud.com/yugenero/xi-solar-storm)

你会得到一个由不同正整数组成的数组 $ a_1, a_2, \dots, a_n $。你必须恰好执行一次以下操作：
- 选择一个正整数 $ k $；
- 对于从 $ 1 $ 到 $ n $ 的每个 $ i $，将 $ a_i $ 替换为 $ a_i \text{ mod } k^\dagger $。

找到一个满足 $ 1 \leq k \leq 10^{18} $ 的 $ k $ 值，使得操作结束后数组 $ a_1, a_2, \dots, a_n $ 恰好包含 $ 2 $ 个不同的值。可以证明，在题目的约束条件下，至少总有一个这样的 $ k $ 存在。如果有多个解，你可以输出其中任意一个。

$ ^\dagger $ $ a \text{ mod } b $ 表示 $ a $ 除以 $ b $ 后的余数。例如：
- $ 7 \text{ mod } 3 = 1 $，因为 $ 7 = 3 \cdot 2 + 1 $
- $ 15 \text{ mod } 4 = 3 $，因为 $ 15 = 4 \cdot 3 + 3 $
- $ 21 \text{ mod } 1 = 0 $，因为 $ 21 = 21 \cdot 1 + 0 $

## 说明/提示
在第一个测试用例中，你可以选择 $ k = 7 $。数组变为 $ [8 \text{ mod } 7, 15 \text{ mod } 7, 22 \text{ mod } 7, 30 \text{ mod } 7] = [1, 1, 1, 2] $，它恰好包含 $ 2 $ 个不同的值（$ \{1, 2\} $）。

在第二个测试用例中，你可以选择 $ k = 30 $。数组变为 $ [0, 0, 8, 0, 8] $，它恰好包含 $ 2 $ 个不同的值（$ \{0, 8\} $）。注意，选择 $ k = 10 $ 也是一个有效的解。

在最后一个测试用例中，你可以选择 $ k = 10^{18} $。数组变为 $ [2, 1] $，它恰好包含 $ 2 $ 个不同的值（$ \{1, 2\} $）。注意，选择 $ k = 10^{18} + 1 $ 是无效的，因为必须满足 $ 1 \leq k \leq 10^{18} $。

## 样例 #1
### 输入
```
5
4
8 15 22 30
5
60 90 98 120 308
6
328 769 541 986 215 734
5
1000 2000 7000 11000 16000
2
2 1
```

### 输出
```
7
30
3
5000
1000000000000000000
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是通过枚举合适的 $k$ 值，使得数组中所有元素对 $k$ 取模后恰好有两个不同的值。大部分题解采用从 $2$ 开始，每次将 $k$ 翻倍的方式进行枚举，利用了如果 $a\bmod b = c$，则 $a\bmod 2b$ 一定等于 $c$ 或 $b + c$ 这一数学性质，保证了最终一定能找到符合条件的 $k$。部分题解还从二进制的角度进行了分析，因为不同的数在二进制下至少有一位不同，所以枚举二进制位也能找到答案。另外，有题解通过计算相邻元素差值的最大公约数来找到 $k$。

### 所选题解
- Stars_visitor_tyw（4星）
    - 关键亮点：思路清晰，通过不断将 $k$ 乘以 $2$ 进行枚举，利用 `check` 函数判断是否满足条件，代码简洁易懂。
- UncleSam_Died（4星）
    - 关键亮点：从二进制的角度进行证明，逻辑严谨，利用 `set` 容器去重，方便判断取模结果的个数。
- Lu_xZ（4星）
    - 关键亮点：提供了两种方法，二进制拆分和数学方法，分别从不同角度解决问题，且对数学方法进行了详细的证明。

### 重点代码及核心实现思想
#### Stars_visitor_tyw
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105;
int n,a[N];
bool check(int k, int tmp)
{
    for(int i=2;i<=n;i++)
    {
        if(a[i]%k!=tmp)
        {
            return 1;
        }
    }
    return 0;
}
void work()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=2;;i*=2)
    {
        if(check(i,a[1]%i))
        {
            cout<<i<<"\n";
            return ;
        }
    }
}
signed main()
{
    int t;
    cin>>t;
    while(t--)
    {
        work();
    }
    return 0; 
}
```
核心实现思想：从 $2$ 开始枚举 $k$，每次将 $k$ 乘以 $2$，对于每个 $k$，检查数组中所有元素对 $k$ 取模的结果是否只有一个值，如果不是，则说明找到了符合条件的 $k$。

#### UncleSam_Died
```cpp
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<algorithm>
#define ll long long
#define N 105
#include<set>
int n,m;ll a[N],b[N],delta[N];
std::set<ll> s;
inline void work(){
    scanf("%d",&n);
    for(register int i=1;i<=n;++i)
        scanf("%lld",&a[i]);
    ll Mode=2;
    while(true){s.clear();
        for(register int i=1;i<=n;++i){
            s.insert(a[i]%Mode);
        }if(s.size()==2){
            printf("%lld\n",Mode);
            return;
        }Mode=Mode*2;
    }
}
signed main(){
    int T;scanf("%d",&T);
    while(T--) work();
}
```
核心实现思想：从 $2$ 开始枚举 $k$，每次将 $k$ 乘以 $2$，对于每个 $k$，将数组中所有元素对 $k$ 取模的结果插入到 `set` 容器中，利用 `set` 的去重功能，判断取模结果的个数是否为 $2$，如果是，则输出 $k$。

#### Lu_xZ
```cpp
// 法一：二进制拆分
void solve() {
    int n;
    cin>> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    auto check = [&](ll p) -> bool {
        set<ll> se;
        for(int i = 0; i < n; ++ i) se.insert(a[i] % p); 
        return se.size() == 2;
    };
    for(int i = 1; ; ++ i) {
        if(check(1ll << i)) {
            cout << (1ll << i) <<'\n';
            return;
        }
    }
}

// 法二：数学
void solve() {
    int n;
    cin >> n;
    ll ans = 0;
    vector<ll> a(n);
    for(int i = 0; i < n; ++ i) {
        cin >> a[i];
        if(i) ans = gcd(ans, abs(a[i] - a[i - 1]));
    }
    cout << ans * 2 << '\n';
}
```
核心实现思想：
- 法一：从 $2^1$ 开始枚举，对于每个 $2^i$，将数组中所有元素对 $2^i$ 取模的结果插入到 `set` 容器中，判断取模结果的个数是否为 $2$，如果是，则输出 $2^i$。
- 法二：计算相邻元素差值的最大公约数 $x$，则 $2x$ 即为所求的 $k$。

### 最优关键思路或技巧
- 采用从 $2$ 开始，每次将 $k$ 翻倍的枚举方式，利用数学性质减少枚举次数。
- 利用 `set` 容器的去重功能，方便判断取模结果的个数。
- 从二进制的角度分析问题，不同的数在二进制下至少有一位不同，通过枚举二进制位找到答案。

### 拓展思路
同类型题目可能会改变条件，例如要求取模结果有 $3$ 个不同的值，或者数组元素有其他限制。类似的算法套路可以是根据题目条件找到一个合适的枚举起点和枚举方式，利用数学性质或数据结构优化枚举过程。

### 推荐题目
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
- [P1414 又是毕业季II](https://www.luogu.com.cn/problem/P1414)
- [P2152 [SDOI2009]SuperGCD](https://www.luogu.com.cn/problem/P2152)

### 个人心得
题解中未包含个人心得。

---
处理用时：57.60秒