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

### 题目中文重写
# 我们的坦尼娅大声哭泣

## 题目描述

现在她实际上并没有哭。但如果你不解决这个问题，她就会哭。

给你整数 $n$、$k$、$A$ 和 $B$。有一个数 $x$，它最初等于 $n$。你可以执行两种操作：

1. 将 $x$ 减 1。此操作花费你 $A$ 枚硬币。
2. 将 $x$ 除以 $k$。仅当 $x$ 能被 $k$ 整除时才能执行此操作。此操作花费你 $B$ 枚硬币。

你要支付的使 $x$ 等于 1 的最小硬币数是多少？

## 说明/提示

在第一个测试用例中，最优策略如下：

- 从 $x$ 中减 1（$9→8$），花费 3 枚硬币。
- 将 $x$ 除以 2（$8→4$），花费 1 枚硬币。
- 将 $x$ 除以 2（$4→2$），花费 1 枚硬币。
- 将 $x$ 除以 2（$2→1$），花费 1 枚硬币。

总花费是 6 枚硬币。

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
- **思路对比**：各题解思路基本一致，均采用贪心算法，核心是比较减法和除法操作的代价，优先选择代价小的操作。部分题解考虑了特殊情况，如 $n < k$ 或 $k = 1$ 时的处理。
- **算法要点**：先将 $n$ 减到能被 $k$ 整除，再比较除法（花费 $B$）和将 $n$ 减到 $n/k$ 的减法（花费 $(n - n/k) * A$）的代价，选择代价小的操作，重复此过程直到 $n = 1$。
- **解决难点**：主要难点在于判断何时使用除法更优，以及如何处理特殊情况（如 $n < k$ 或 $k = 1$）。部分题解还提到了优化，避免超时。

### 评分较高的题解
- **作者：miraculously（4星）**
    - **关键亮点**：思路清晰，代码简洁，对特殊情况和核心逻辑的处理明确。
    - **个人心得**：无
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
核心思想：先处理 $n < k$ 的特殊情况，然后在循环中，先将 $n$ 减到能被 $k$ 整除，再比较除法和减法的代价，选择代价小的操作。

- **作者：thomas_zjl（4星）**
    - **关键亮点**：思路阐述详细，代码结构清晰，对操作步骤的解释明确。
    - **个人心得**：无
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
核心思想：同样先将 $n$ 减到能被 $k$ 整除，再比较除法和减法的代价，若减法代价小则直接将 $n$ 减到 1，否则进行除法操作。

- **作者：Aisaka_Taiga（4星）**
    - **关键亮点**：对贪心思路的分类讨论清晰，解释了优化的原因，避免超时。
    - **个人心得**：无
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a,b,ans;
signed main()
{
    cin>>n>>k>>a>>b;
    if(n<k)
    {
        cout<<(n-1)*a<<endl;
        return 0;
    }
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
            cout<<ans<<endl;
            return 0;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
核心思想：先处理 $n < k$ 的情况，然后在循环中，将 $n$ 减到能被 $k$ 整除，比较代价后选择操作，若除法不优则直接将 $n$ 减到 1。

### 最优关键思路或技巧
- **贪心策略**：每次比较减法和除法操作的代价，优先选择代价小的操作。
- **特殊情况处理**：对 $n < k$ 和 $k = 1$ 的情况进行特判，避免不必要的计算。
- **优化判断**：若某次除法操作的代价大于减法操作，后续都采用减法操作，避免超时。

### 可拓展之处
同类型题或类似算法套路：
- 其他涉及多种操作选择，需要通过比较代价来确定最优策略的贪心问题。
- 状态转移类问题，可结合动态规划思想，对贪心策略进行验证或拓展。

### 洛谷相似题目推荐
- P1223 排队接水：根据每个人的接水时间进行排序，贪心选择接水顺序，使总等待时间最短。
- P1094 纪念品分组：将物品按价格排序，采用贪心策略进行分组，使分组数最少。
- P1803 凌乱的yyy / 线段覆盖：对线段按结束时间排序，贪心选择不重叠的线段，使覆盖线段数最多。

### 个人心得摘录与总结
- **cym_233**：提到要尽量优化代码细节，省去不必要的计算，否则较大的测试点会超时，还强调要特判 $k = 1$ 的情况。总结：在贪心算法题中，要注意代码优化和特殊情况处理，避免超时和错误。
- **Aisaka_Taiga**：指出若当前除以 $k$ 的代价大于直接减到 $n = 1$ 的花费，后面无论如何都是减一的策略更优，可直接减到 1 输出花费，避免 TLE。总结：在贪心算法中，可通过分析操作的代价变化规律进行优化，避免重复计算。 

---
处理用时：42.28秒