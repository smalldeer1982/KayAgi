# 题目信息

# Social Circles

## 题目描述

You invited $ n $ guests to dinner! You plan to arrange one or more circles of chairs. Each chair is going to be either occupied by one guest, or be empty. You can make any number of circles.

Your guests happen to be a little bit shy, so the $ i $ -th guest wants to have a least $ l_i $ free chairs to the left of his chair, and at least $ r_i $ free chairs to the right. The "left" and "right" directions are chosen assuming all guests are going to be seated towards the center of the circle. Note that when a guest is the only one in his circle, the $ l_i $ chairs to his left and $ r_i $ chairs to his right may overlap.

What is smallest total number of chairs you have to use?

## 说明/提示

In the second sample the only optimal answer is to use two circles: a circle with $ 5 $ chairs accomodating guests $ 1 $ and $ 2 $ , and another one with $ 10 $ chairs accomodationg guests $ 3 $ and $ 4 $ .

In the third sample, you have only one circle with one person. The guest should have at least five free chairs to his left, and at least six free chairs to his right to the next person, which is in this case the guest herself. So, overall number of chairs should be at least 6+1=7.

## 样例 #1

### 输入

```
3
1 1
1 1
1 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
1 2
2 1
3 5
5 3
```

### 输出

```
15
```

## 样例 #3

### 输入

```
1
5 6
```

### 输出

```
7
```

# AI分析结果

### 题目翻译
# 社交圈子

## 题目描述
你邀请了 $n$ 位客人来吃晚餐！你计划安排一个或多个椅子围成的圈。每把椅子要么被一位客人占用，要么空着。你可以安排任意数量的圈。

你的客人有点害羞，所以第 $i$ 位客人希望他的椅子左边至少有 $l_i$ 把空椅子，右边至少有 $r_i$ 把空椅子。“左边” 和 “右边” 的方向是假设所有客人都面向圆圈中心就座来确定的。注意，当一位客人独自在一个圈中时，他左边的 $l_i$ 把椅子和右边的 $r_i$ 把椅子可能会重叠。

你最少需要使用多少把椅子？

## 说明/提示
在第二个样例中，唯一的最优答案是使用两个圈：一个有 5 把椅子的圈安排客人 1 和 2，另一个有 10 把椅子的圈安排客人 3 和 4。

在第三个样例中，你只有一个圈和一个人。这位客人左边至少需要 5 把空椅子，右边至少需要 6 把空椅子到下一个人（在这种情况下就是客人自己）。所以，椅子的总数至少应该是 6 + 1 = 7。

## 样例 #1
### 输入
```
3
1 1
1 1
1 1
```
### 输出
```
6
```

## 样例 #2
### 输入
```
4
1 2
2 1
3 5
5 3
```
### 输出
```
15
```

## 样例 #3
### 输入
```
1
5 6
```
### 输出
```
7
```

### 综合分析与结论
- **思路对比**：大部分题解思路一致，即通过贪心策略，将 $l$ 和 $r$ 数组分别排序，计算 $\sum\limits_{i=1}^n max(l_i,r_i)$ 并加上 $n$ 得到最少椅子数。彭骐飞的题解先计算 $\sum\limits_{i=1}^n {l_i+r_i+1}$，再减去 $\sum\limits_{i=1}^{n} {min \{ l_i, r_i \}}$ 得到结果。
- **算法要点**：核心是贪心算法，通过排序找到合适的 $l$ 和 $r$ 配对，使公用椅子最多，从而使总椅子数最少。
- **解决难点**：难点在于理解如何安排座位能使公用椅子最多，即如何确定贪心策略。通过分析发现，将 $l$ 和 $r$ 分别排序后对应配对能使 $max(l_i,r_i)$ 最小，进而使总椅子数最少。

### 所选题解
- **作者：Itst（5星）**
    - **关键亮点**：思路清晰简洁，代码可读性高，直接阐述贪心策略并实现。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define MAXN 100010
using namespace std;

int numL[MAXN], numR[MAXN];

int main(){
    int N;
    cin >> N;
    for(int i = 1 ; i <= N ; i++)
        cin >> numL[i] >> numR[i];
    sort(numL + 1, numL + N + 1);
    sort(numR + 1, numR + N + 1);
    long long ans = N;
    for(int i = 1 ; i <= N ; i++)
        ans += max(numL[i], numR[i]);
    cout << ans;
    return 0;
}
```
核心实现思想：先读取输入，将 $l$ 和 $r$ 数组分别排序，初始化答案为 $n$，然后遍历数组，累加 $max(l_i,r_i)$ 到答案中，最后输出答案。

- **作者：king_xbz（4星）**
    - **关键亮点**：详细分析了椅子公用和重复使用的情况，逐步推导得出贪心策略。
    - **核心代码**：
```cpp
signed main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>l[i]>>r[i];
    int bas=n;
    sort(l+1,l+n+1);
    sort(r+1,r+n+1);
    int ans=0;
    for(int i=1;i<=n;i++)
        ans+=max(l[i],r[i]);
    cout<<ans+bas;
    return 0;
}
```
核心实现思想：读取输入，将 $l$ 和 $r$ 数组分别排序，初始化基础椅子数为 $n$，计算 $\sum\limits_{i=1}^n max(l_i,r_i)$ 并加上基础椅子数得到答案。

- **作者：云浅知处（4星）**
    - **关键亮点**：通过具体例子解释贪心策略，使思路更易理解。
    - **核心代码**：
```cpp
#include<cstdio>
#include<algorithm>

#define MAXN 100005
#define int long long

using namespace std;

int l[MAXN],r[MAXN];
int n;

signed main(void){
    
    scanf("%ld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&l[i],&r[i]);
    }
    
    sort(l+1,l+n+1);
    sort(r+1,r+n+1);
    
    int ans=n;
    
    for(int i=1;i<=n;i++){
        ans+=max(l[i],r[i]);
    }
    
    printf("%lld\n",ans);
    
    return 0;
}
```
核心实现思想：读取输入，将 $l$ 和 $r$ 数组分别排序，初始化答案为 $n$，遍历数组累加 $max(l_i,r_i)$ 到答案中，最后输出答案。

### 最优关键思路或技巧
- **贪心策略**：将 $l$ 和 $r$ 数组分别排序，对应配对取 $max(l_i,r_i)$ 累加，可使公用椅子最多，总椅子数最少。
- **排序优化**：通过排序将问题简化，找到合适的配对方式。

### 可拓展之处
同类型题可能会有不同的座位安排规则或约束条件，但核心思路仍是通过贪心策略使某种资源（如本题中的椅子）使用最少。类似算法套路可用于资源分配、区间覆盖等问题。

### 推荐洛谷题目
- P1090 [合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略合并果子，使总代价最小。
- P1223 [排队接水](https://www.luogu.com.cn/problem/P1223)：合理安排排队顺序，使平均等待时间最短。
- P2240 [部分背包问题](https://www.luogu.com.cn/problem/P2240)：使用贪心策略选择物品放入背包，使背包价值最大。

### 个人心得摘录与总结
- **彭骐飞**：先推性质，尝试不同计算方法，通过样例验证后提交，最终通过系统测试。提醒要开 $long long$，认为常规推出该解法不太可能。总结：在解题时可尝试先推性质、用样例验证，同时注意数据范围。 

---
处理用时：44.71秒