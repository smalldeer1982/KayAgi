# 题目信息

# Our Tanya is Crying Out Loud

## 题目描述

Right now she actually isn't. But she will be, if you don't solve this problem.

You are given integers $ n $ , $ k $ , $ A $ and $ B $ . There is a number $ x $ , which is initially equal to $ n $ . You are allowed to perform two types of operations:

1. Subtract 1 from $ x $ . This operation costs you $ A $ coins.
2. Divide $ x $ by $ k $ . Can be performed only if $ x $ is divisible by $ k $ . This operation costs you $ B $ coins.

 What is the minimum amount of coins you have to pay to make $ x $ equal to $ 1 $ ?

## 说明/提示

In the first testcase, the optimal strategy is as follows:

- Subtract 1 from $ x $ ( $ 9→8 $ ) paying 3 coins.
- Divide $ x $ by 2 ( $ 8→4 $ ) paying 1 coin.
- Divide $ x $ by 2 ( $ 4→2 $ ) paying 1 coin.
- Divide $ x $ by 2 ( $ 2→1 $ ) paying 1 coin.

The total cost is $ 6 $ coins.

In the second test case the optimal strategy is to subtract 1 from $ x $ $ 4 $ times paying $ 8 $ coins in total.

## 样例 #1

### 输入

```
9
2
3
1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
5
2
20
```

### 输出

```
8
```

## 样例 #3

### 输入

```
19
3
4
2
```

### 输出

```
12
```

# AI分析结果

### 题目内容中文重写
# 我们的坦尼娅大声哭泣

## 题目描述

现在她实际上并没有哭。但如果你不解决这个问题，她就会哭。

给定整数 $n$、$k$、$A$ 和 $B$。有一个数 $x$，最初 $x$ 等于 $n$。允许执行两种操作：
1. 将 $x$ 减 1。此操作花费 $A$ 枚硬币。
2. 将 $x$ 除以 $k$。仅当 $x$ 能被 $k$ 整除时可执行此操作。此操作花费 $B$ 枚硬币。

要使 $x$ 等于 1，最少需要支付多少枚硬币？

## 说明/提示
在第一个测试用例中，最优策略如下：
- 从 $x$ 中减 1（$9 \to 8$），花费 3 枚硬币。
- 将 $x$ 除以 2（$8 \to 4$），花费 1 枚硬币。
- 将 $x$ 除以 2（$4 \to 2$），花费 1 枚硬币。
- 将 $x$ 除以 2（$2 \to 1$），花费 1 枚硬币。

总花费为 6 枚硬币。

在第二个测试用例中，最优策略是从 $x$ 中减 1 四次，总共花费 8 枚硬币。

## 样例 #1
### 输入
```
9
2
3
1
```
### 输出
```
6
```

## 样例 #2
### 输入
```
5
5
2
20
```
### 输出
```
8
```

## 样例 #3
### 输入
```
19
3
4
2
```
### 输出
```
12
```

### 综合分析与结论
- **思路对比**：所有题解均采用贪心算法，核心思路是每次比较减法和除法操作的代价，选择代价小的操作。部分题解还考虑了特殊情况，如 $n < k$ 或 $k = 1$ 时的处理。
- **算法要点**：先将 $n$ 减到能被 $k$ 整除，再比较除法（花费 $B$）和多次减法（花费 $(n - n/k) * A$）的代价，选择更优操作。
- **解决难点**：处理数据范围大导致的暴力超时问题，通过贪心策略避免不必要的计算；同时注意特殊情况的处理，如 $n < k$ 只能减法，$k = 1$ 只能一直减。

### 评分情况
| 作者 | 评分 | 理由 |
| ---- | ---- | ---- |
| miraculously | 5 星 | 思路清晰，代码简洁，对特殊情况和贪心策略的处理清晰明了。 |
| thomas_zjl | 4 星 | 详细阐述解题思路，代码实现简洁易懂。 |
| Jerry_heng | 4 星 | 思路清晰，代码简洁，考虑了特殊情况。 |

### 所选题解
- **作者：miraculously（5 星）**
    - **关键亮点**：思路清晰，代码简洁，对特殊情况和贪心策略的处理清晰明了。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a,b,ans;
signed main()
{
    scanf("%lld%lld%lld%lld",&n,&k,&a,&b);
    if(n<k)
        return printf("%lld",(n-1)*a),0;
    while(n!=1)
    {
        ans+=n%k*a;
        n-=n%k;
        if(b<(n-n/k)*a)
        {
            ans+=b;
            n/=k;
        }
        else
        {
            ans+=(n-1)*a;
            return printf("%lld",ans),0;
        }
    }
    printf("%lld",ans);
}
```
    - **核心实现思想**：先判断 $n < k$ 的特殊情况，直接输出减法结果。然后在循环中，先将 $n$ 减到能被 $k$ 整除，再比较除法和减法的代价，选择更优操作。

- **作者：thomas_zjl（4 星）**
    - **关键亮点**：详细阐述解题思路，代码实现简洁易懂。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,k,a,b;
    cin>>n>>k>>a>>b;
    long long ans=0;
    while(n!=1){
        ans+=(n%k)*a;
        n=n-n%k;
        if(b>(n-n/k)*a){
            ans+=(n-1)*a;
            break;
        }
        else{
            n=n/k;
            ans+=b;
        }
    }
    cout<<ans;
    return 0;
}
```
    - **核心实现思想**：在循环中，先将 $n$ 减到能被 $k$ 整除，比较除法和减法代价，若减法优则直接减到 1，否则进行除法操作。

- **作者：Jerry_heng（4 星）**
    - **关键亮点**：思路清晰，代码简洁，考虑了特殊情况。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a,b,ans;
signed main(){
    scanf("%lld%lld%lld%lld",&n,&k,&a,&b);
    if(k==1)printf("%lld",(n-1)*a);
    else if(n==1)printf("0");
    else{
        while(n>1){
            if(n<k){
                ans+=(n-1)*a;
                break;
            }
            int rest=n%k;
            ans+=rest*a;
            n-=rest;
            int nxt=n/k;
            ans+=min(b,(n-nxt)*a);
            n=nxt;
        }
        printf("%lld",ans);
    }
    return 0;
}
```
    - **核心实现思想**：先处理 $k = 1$ 和 $n = 1$ 的特殊情况，然后在循环中，将 $n$ 减到能被 $k$ 整除，选择除法和减法中代价小的操作。

### 最优关键思路或技巧
- **贪心策略**：每次比较减法和除法的代价，选择代价小的操作，避免不必要的计算。
- **特殊情况处理**：对 $n < k$ 和 $k = 1$ 等特殊情况单独处理，简化计算。

### 可拓展之处
同类型题可能涉及更多操作类型或更复杂的代价计算，但核心思路仍是贪心，每次选择最优操作。类似算法套路可用于资源分配、路径选择等问题。

### 推荐题目
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：经典贪心问题，通过排序选择最优顺序。
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：贪心分组问题，合理分组使组数最少。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：贪心解决背包问题，按性价比选择物品。

### 个人心得摘录与总结
- **cym_233**：提到要尽量优化代码细节，能省去的计算一定要省去，否则较大数据点会被卡，还强调要特判 $k = 1$ 的情况。总结：在处理大数据范围问题时，代码优化和特殊情况处理很重要。
- **Aisaka_Taiga**：指出直接按思路写会 TLE，需优化。若当前除以 $k$ 的代价大于直接减到 $n = 1$ 的花费，后续都采用减一策略。总结：贪心问题中可根据操作的单调性进行优化，避免重复计算。 

---
处理用时：41.52秒