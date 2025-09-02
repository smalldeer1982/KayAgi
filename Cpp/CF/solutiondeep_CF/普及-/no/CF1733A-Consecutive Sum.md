# 题目信息

# Consecutive Sum

## 题目描述

You are given an array $ a $ with $ n $ integers. You can perform the following operation at most $ k $ times:

- Choose two indices $ i $ and $ j $ , in which $ i \,\bmod\, k = j \,\bmod\, k $ ( $ 1 \le i < j \le n $ ).
- Swap $ a_i $ and $ a_j $ .

After performing all operations, you have to select $ k $ consecutive elements, and the sum of the $ k $ elements becomes your score. Find the maximum score you can get.

Here $ x \bmod y $ denotes the remainder from dividing $ x $ by $ y $ .

## 说明/提示

In the first test case, we can get a score of $ 11 $ if we select $ a_1, a_2 $ without performing any operations.

In the third test case, we can get a score of $ 15 $ if we first swap $ a_1 $ with $ a_4 $ and then select $ a_3, a_4, a_5 $ .

## 样例 #1

### 输入

```
5
3 2
5 6 0
1 1
7
5 3
7 0 4 0 4
4 2
2 7 3 4
3 3
1000000000 1000000000 999999997```

### 输出

```
11
7
15
10
2999999997```

# AI分析结果

### 题目内容
# 连续和

## 题目描述
给定一个包含 $n$ 个整数的数组 $a$ 。你最多可以执行 $k$ 次以下操作：
- 选择两个索引 $i$ 和 $j$ ，满足 $i \bmod k = j \bmod k$（$1 \le i < j \le n$）。
- 交换 $a_i$ 和 $a_j$ 。
在执行完所有操作后，你必须选择 $k$ 个连续的元素，这 $k$ 个元素的和即为你的分数。求你能得到的最大分数。
这里 $x \bmod y$ 表示 $x$ 除以 $y$ 的余数。

## 说明/提示
在第一个测试用例中，如果我们不执行任何操作，选择 $a_1$, $a_2$ ，可以得到分数 $11$ 。
在第三个测试用例中，如果我们首先交换 $a_1$ 和 $a_4$ ，然后选择 $a_3$, $a_4$, $a_5$ ，可以得到分数 $15$ 。

## 样例 #1
### 输入
```
5
3 2
5 6 0
1 1
7
5 3
7 0 4 0 4
4 2
2 7 3 4
3 3
1000000000 1000000000 999999997
```
### 输出
```
11
7
15
10
2999999997
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解均采用贪心策略，利用操作规则下 “$i \bmod k = j \bmod k$ 时可交换元素” 这一特性，意识到可将模 $k$ 同余位置的最大元素集中到长度为 $k$ 的区间以获取最大和。不同题解在实现细节和代码风格上有差异，如数组初始化方式、输入输出处理等，但核心思路一致。

### 所选的题解
- **作者：QingDeng_Star (4星)**
    - **关键亮点**：思路清晰简洁，代码实现直接，利用数组 `a` 记录模 `k` 同余位置的最大值，初始化数组并通过简单循环处理输入、计算结果。
    - **重点代码**：
```c
#include <bits/stdc++.h>
using namespace std;
long long a[105],b[105];
int main(){
    int t;
    cin>>t;
    while(t--) 
    {
        int n,k;
        cin>>n>>k;
        memset(a,0,sizeof a);
        for(int i=1;i<=n;i++) 
        {
            cin>>b[i];
            a[i%k]=max(a[i%k],b[i]);
        }
        long long ans=0;
        for(int i=0;i<k;i++) 
            ans+=a[i];
        cout<<ans<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：遍历输入数组 `b`，将每个元素与对应模 `k` 位置在数组 `a` 中的值比较取大，最后累加 `a` 数组得到最大分数。
- **作者：0zhouyq (4星)**
    - **关键亮点**：代码简洁规范，使用 `maxn` 数组记录模 `k` 同余位置的最大值，通过 `scanf` 和 `printf` 进行输入输出，在循环处理中完成数据读取、计算和结果输出。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int maxn[101];
signed main(){
    int t;
    scanf("%lld",&t);
    while(t--){
        int n,k;
        scanf("%lld %lld",&n,&k);
        for(int i=0;i<=100;i++) maxn[i]=-0x3f3f3f3f3f3f3f3f;
        for(int i=1;i<=n;i++){
            int x;
            scanf("%lld",&x);
            int p=i%k;
            maxn[p]=max(maxn[p],x);
        }
        int ans=0;
        for(int i=0;i<k;i++){
            ans+=maxn[i];
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```
    - **核心实现思想**：初始化 `maxn` 数组为极小值，遍历输入数据更新 `maxn` 数组中对应模 `k` 位置的最大值，最后累加 `maxn` 数组得到答案。
- **作者：sgl654321 (4星)**
    - **关键亮点**：解题思路阐述详细，代码结构清晰，通过 `b` 数组记录模 `k` 同余位置的最大值，注意多组数据下的数组清零，利用 `memset` 初始化数组。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,k,a[100010],b[100010],ans; 
int main(){
    cin>>t;
    while(t--){
        cin>>n>>k;
        ans=0;
        memset(b,0,sizeof(b));
        for(int i=1;i<=n;i++){
            cin>>a[i];
            b[i%k]=max(b[i%k],a[i]);
        }
        for(int i=0;i<k;i++)
            ans+=b[i];
        cout<<ans<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：每次处理新数据时初始化 `ans` 和 `b` 数组，遍历输入数组 `a` 更新 `b` 数组中模 `k` 同余位置的最大值，累加 `b` 数组得到最大分数。

### 最优关键思路或技巧
利用贪心策略，根据操作规则将模 `k` 同余位置的最大元素集中。在代码实现上，使用数组记录模 `k` 同余位置的最大值，通过一次遍历输入数组更新该数组，最后累加得到结果，这种方法简洁高效。

### 拓展
同类型题常围绕特定操作规则下的数组元素处理与最值求解。类似算法套路是分析操作规则对元素位置和值的影响，基于此采用贪心策略，寻找能使目标最优的元素组合方式。

### 推荐题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：涉及贪心策略，通过分析数据关系找到最优排序方式以解决问题。
- [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需运用贪心思想结合游戏规则，找到最优策略。
- [P2859 [USACO06DEC]Milk Patterns G](https://www.luogu.com.cn/problem/P2859)：在一定规则下对数据进行处理，利用贪心等策略解决问题。 

---
处理用时：48.70秒