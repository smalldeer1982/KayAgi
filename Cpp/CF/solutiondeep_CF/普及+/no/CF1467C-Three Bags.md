# 题目信息

# Three Bags

## 题目描述

You are given three bags. Each bag contains a non-empty multiset of numbers. You can perform a number of operations on these bags. In one operation, you can choose any two non-empty bags, and choose one number from each of the bags. Let's say that you choose number $ a $ from the first bag and number $ b $ from the second bag. Then, you remove $ b $ from the second bag and replace $ a $ with $ a-b $ in the first bag. Note that if there are multiple occurrences of these numbers, then you shall only remove/replace exactly one occurrence.

You have to perform these operations in such a way that you have exactly one number remaining in exactly one of the bags (the other two bags being empty). It can be shown that you can always apply these operations to receive such a configuration in the end. Among all these configurations, find the one which has the maximum number left in the end.

## 说明/提示

In the first example input, let us perform the following operations:

 $ [1, 2], [6, 3, 4, 5], [5] $

 $ [-5, 2], [3, 4, 5], [5] $ (Applying an operation to $ (1, 6) $ )

 $ [-10, 2], [3, 4], [5] $ (Applying an operation to $ (-5, 5) $ )

 $ [2], [3, 4], [15] $ (Applying an operation to $ (5, -10) $ )

 $ [-1], [4], [15] $ (Applying an operation to $ (2, 3) $ )

 $ [-5], [], [15] $ (Applying an operation to $ (-1, 4) $ )

 $ [], [], [20] $ (Applying an operation to $ (15, -5) $ )

You can verify that you cannot achieve a bigger number. Hence, the answer is $ 20 $ .

## 样例 #1

### 输入

```
2 4 1
1 2
6 3 4 5
5```

### 输出

```
20```

## 样例 #2

### 输入

```
3 2 2
7 5 4
2 9
7 1```

### 输出

```
29```

# AI分析结果

### 题目翻译
# 三个袋子

## 题目描述
你有三个袋子。每个袋子里都包含一个非空的多重数集。你可以对这些袋子进行若干次操作。在一次操作中，你可以选择任意两个非空的袋子，并从每个袋子中选择一个数。假设你从第一个袋子中选择了数 $a$，从第二个袋子中选择了数 $b$。然后，你从第二个袋子中移除 $b$，并将第一个袋子中的 $a$ 替换为 $a - b$。请注意，如果这些数有多个出现，那么你应该只移除/替换恰好一个出现。

你必须以这样的方式执行这些操作，使得最后恰好有一个袋子中只剩下一个数（另外两个袋子为空）。可以证明，你总是可以通过执行这些操作得到这样的配置。在所有这些配置中，找出最后剩下的数最大的那个。

## 说明/提示
在第一个示例输入中，让我们执行以下操作：

$ [1, 2], [6, 3, 4, 5], [5] $

$ [-5, 2], [3, 4, 5], [5] $（对 $ (1, 6) $ 执行操作）

$ [-10, 2], [3, 4], [5] $（对 $ (-5, 5) $ 执行操作）

$ [2], [3, 4], [15] $（对 $ (5, -10) $ 执行操作）

$ [-1], [4], [15] $（对 $ (2, 3) $ 执行操作）

$ [-5], [], [15] $（对 $ (-1, 4) $ 执行操作）

$ [], [], [20] $（对 $ (15, -5) $ 执行操作）

你可以验证无法得到更大的数。因此，答案是 $ 20 $。

## 样例 #1
### 输入
```
2 4 1
1 2
6 3 4 5
5
```
### 输出
```
20
```

## 样例 #2
### 输入
```
3 2 2
7 5 4
2 9
7 1
```
### 输出
```
29
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过分析操作的性质，找出能使最后剩下的数最大的策略。主要策略有两种情况：一是两个在不同集合中的数贡献为负，其余为正；二是一个集合中的元素贡献为负，其余为正。各题解的不同在于实现细节和对策略的解释方式。

### 所选题解
- **PersistentLife（5星）**
    - **关键亮点**：思路清晰，直接指出答案的两种情况并给出具体操作方法，代码简洁易懂，通过计算不同情况的结果取最大值得到最终答案。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n1,n2,n3,m1,m2,m3,s1,s2,s3;
int a[300005],b[300005],c[300005];
signed main()
{
    cin>>n1>>n2>>n3;
    m1=m2=m3=0x3f3f3f3f;
    
    for(int i=1;i<=n1;i++) scanf("%lld",&a[i]),m1=min(m1,a[i]),s1+=a[i];
    for(int i=1;i<=n2;i++) scanf("%lld",&b[i]),m2=min(m2,b[i]),s2+=b[i];
    for(int i=1;i<=n3;i++) scanf("%lld",&c[i]),m3=min(m3,c[i]),s3+=c[i];
    int ans=0;
    ans=max(ans,s2+s3-s1);
    ans=max(ans,s1+s3-s2);
    ans=max(ans,s1+s2-s3);
    ans=max(ans,s1+s2+s3-2*min(m1+m2,min(m1+m3,m2+m3)));
    cout<<ans;
    return 0;
}
```
    - **核心实现思想**：先读取每个袋子中的数，计算每个袋子中数的和以及最小值。然后分别计算一个集合为负其余为正的三种情况，再计算两个不同集合中最小数为负其余为正的情况，最后取这些情况的最大值作为答案。

- **duyi（4星）**
    - **关键亮点**：从操作的性质出发，将操作转化为树形结构，清晰地阐述了两种构造树的方法，并且给出了时间复杂度分析。
    - **核心代码**：
```cpp
const int MAXN = 3e5;
const ll LL_INF = 1e18;

int n[3];
ll a[3][MAXN + 5], sum[3], sumall, mn[3];

int main() {
    cin >> n[0] >> n[1] >> n[2];
    for (int t = 0; t < 3; ++t) {
        mn[t] = LL_INF;
        for (int i = 1; i <= n[t]; ++i) {
            cin >> a[t][i];
            sum[t] += a[t][i];
            ckmin(mn[t], a[t][i]);
        }
        sumall += sum[t];
    }
    ll ans = 0;
    // 策略1:
    for (int t = 0; t < 3; ++t) {
        ckmax(ans, sumall - sum[t] * 2); // 这一层全部作为根的儿子 
    }
    // 策略2:
    for (int t = 0; t < 3; ++t) { // 根节点 
        ll cur_ans = sumall;
        for (int tt = 0; tt < 3; ++tt) {
            if (tt == t)
                continue;
            cur_ans -= mn[tt] * 2;
        }
        ckmax(ans, cur_ans);
    }
    cout << ans << endl;
    return 0;
}
```
    - **核心实现思想**：先读取每个袋子中的数，计算每个袋子中数的和以及最小值。然后分别实现两种构造树的策略，第一种策略是枚举一个集合，让该集合的元素全部作为根的儿子，计算此时的答案；第二种策略是枚举根节点，在另外两个集合中各选一个最小的元素作为根的儿子，计算此时的答案，最后取最大值作为最终答案。

### 最优关键思路或技巧
- **贪心策略**：通过分析操作的性质，找出使最后剩下的数最大的两种贪心策略，即一个集合为负其余为正和两个不同集合中最小数为负其余为正。
- **树形结构转化**：将操作过程转化为树形结构，通过树的奇偶层来确定每个数的正负贡献，有助于理解和分析问题。

### 可拓展之处
同类型题可能会有更多的袋子或更复杂的操作规则，但核心思路仍然是通过分析操作的性质，找出贪心策略。类似算法套路可以应用于其他需要通过一系列操作得到最优结果的问题，如博弈问题、资源分配问题等。

### 推荐题目
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录与总结
- **lndjy**：通过观察样例找规律，发现策略是把一个数堆成负数，然后把它加给一个正数，从而得到可能的最优情况。总结：在面对复杂问题时，观察样例找规律是一种有效的解题方法。
- **_JF_**：大力分讨贪心，感觉做起来挺难受的。总结：贪心问题可能需要进行分类讨论，过程可能比较繁琐，需要耐心和细心。

---
处理用时：57.37秒