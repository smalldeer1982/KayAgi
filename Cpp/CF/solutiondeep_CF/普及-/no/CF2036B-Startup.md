# 题目信息

# Startup

## 题目描述

Arseniy came up with another business plan — to sell soda from a vending machine! For this, he purchased a machine with $ n $ shelves, as well as $ k $ bottles, where the $ i $ -th bottle is characterized by the brand index $ b_i $ and the cost $ c_i $ .

You can place any number of bottles on each shelf, but all bottles on the same shelf must be of the same brand.

Arseniy knows that all the bottles he puts on the shelves of the machine will be sold. Therefore, he asked you to calculate the maximum amount he can earn.

## 说明/提示

In the first test case, Arseniy has $ 3 $ shelves in the vending machine. He can place, for example, two bottles of the brand $ 2 $ on the first shelf and a bottle of the brand $ 1 $ on the second shelf. Then the total cost of the bottles would be $ 6 + 7 + 15 = 28 $ .

In the second test case, he has only one shelf. It is not difficult to show that the optimal option is to place a bottle of the brand $ 1 $ on it. Then the total cost will be $ 15 $ .

In the third test case, he has as many as $ 6 $ shelves, so he can place all available bottles with a total cost of $ 7 + 5 = 12 $ .

## 样例 #1

### 输入

```
4
3 3
2 6
2 7
1 15
1 3
2 6
2 7
1 15
6 2
1 7
2 5
190000 1
1 1000```

### 输出

```
28
15
12
1000```

# AI分析结果

### 题目翻译
#### 创业

#### 题目描述
阿尔谢尼想出了另一个商业计划——从自动售货机中售卖汽水！为此，他购买了一台有 $n$ 个货架的机器，以及 $k$ 瓶汽水，其中第 $i$ 瓶汽水的品牌索引为 $b_i$，价格为 $c_i$。

你可以在每个货架上放置任意数量的瓶子，但同一货架上的所有瓶子必须是同一品牌。

阿尔谢尼知道他放在机器货架上的所有瓶子都会被售出。因此，他请你计算他能赚取的最大金额。

#### 说明/提示
在第一个测试用例中，阿尔谢尼的自动售货机有 $3$ 个货架。例如，他可以在第一个货架上放置两瓶品牌为 $2$ 的汽水，在第二个货架上放置一瓶品牌为 $1$ 的汽水。那么这些瓶子的总价格将是 $6 + 7 + 15 = 28$。

在第二个测试用例中，他只有一个货架。不难证明，最优方案是在上面放置一瓶品牌为 $1$ 的汽水。那么总价格将是 $15$。

在第三个测试用例中，他有多达 $6$ 个货架，所以他可以放置所有可用的瓶子，总价格为 $7 + 5 = 12$。

#### 样例 #1
##### 输入
```
4
3 3
2 6
2 7
1 15
1 3
2 6
2 7
1 15
6 2
1 7
2 5
190000 1
1 1000
```
##### 输出
```
28
15
12
1000
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，由于每个货架可以放任意数量的同一品牌瓶子，所以要让收益最大，就需要把每个品牌的瓶子总价值计算出来，然后从大到小排序，选取前 $n$ 个品牌的瓶子放在货架上，它们的总价值就是最大收益。

各题解的主要区别在于数据结构的使用和代码实现细节：
- **数组桶的使用**：大部分题解使用数组作为桶来记录每个品牌的总价值，通过品牌索引直接访问和累加价值，简单高效，但需要注意数组的初始化和大小。
- **`map` 的使用**：部分题解使用 `map` 来统计每个品牌的总价值，`map` 可以自动处理品牌索引不连续的情况，但在排序时需要将 `map` 中的值提取到数组或向量中。
- **排序处理**：所有题解都对品牌总价值进行排序，排序方向为从大到小，以便选取前 $n$ 个最大值。

### 所选题解
- **作者：Yxy7952（4星）**
  - **关键亮点**：思路清晰，代码简洁，使用数组桶记录品牌总价值，注释详细，易于理解。
- **作者：zhang_kevin（4星）**
  - **关键亮点**：详细阐述了贪心策略，代码结构清晰，使用 `inline` 函数提高效率。
- **作者：GreenMelon（4星）**
  - **关键亮点**：思路简洁明了，代码实现简单，使用 `lambda` 表达式进行降序排序，代码风格现代。

### 重点代码
#### 作者：Yxy7952
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,n,k;
ll b[200005],c[200005],t[200005];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        ll m=0,sum=0;
        for(int i=0;i<=200005;i++) t[i]=0; //初始化为 0
        for(int i=1;i<=k;i++){
            cin>>b[i]>>c[i];
            t[b[i]]+=c[i];
            m=max(m,b[i]);
        }
        sort(t+1,t+m+1); //这里从小到大排序
        for(int i=m;i>=m-n+1;i--) sum+=t[i];
        //因为从小到大排序，这里从后往前找寻前 n 个物品
        cout<<sum<<"\n";
    }
    return 0;
}
```
**核心实现思想**：使用数组 `t` 作为桶记录每个品牌的总价值，通过 `sort` 函数对总价值数组进行排序，最后从后往前选取前 $n$ 个最大值求和。

#### 作者：zhang_kevin
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001], box[200001];
inline bool cmp(int x, int y){
    return x > y;
}
inline void Solve(){
    memset(box, 0, sizeof(box));
    int n, k;
    cin >> n >> k;
    for(int i = 1, b, c; i <= k; i++){
        cin >> b >> c;
        box[b] += c;
    }
    sort(box+1, box+1+k, cmp);
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        ans += box[i];
    }
    cout << ans << endl;
    return;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        Solve();
    }
    return 0;
}
```
**核心实现思想**：使用数组 `box` 作为桶记录每个品牌的总价值，自定义 `cmp` 函数进行降序排序，然后选取前 $n$ 个最大值求和。

#### 作者：GreenMelon
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[200005];
int main(){
    int t;
    cin>>t;
    while(t--){
        memset(a, 0, sizeof(a));
        int n, k, ans=0;
        cin>>n>>k;
        for(int i=1;i<=k;i++){
            int b, c;
            cin>>b>>c;
            a[b]+=c;
        }
        sort(a+1, a+1+k, [](int x, int y){return x>y;});
        for(int i=1;i<=n;i++){
            ans+=a[i];
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
**核心实现思想**：使用数组 `a` 作为桶记录每个品牌的总价值，使用 `lambda` 表达式进行降序排序，最后选取前 $n$ 个最大值求和。

### 关键思路或技巧
- **贪心策略**：根据题目条件，将同一品牌的瓶子放在一个货架上，计算每个品牌的总价值，然后选取总价值最大的前 $n$ 个品牌，这是解决问题的核心思路。
- **桶的使用**：使用数组或 `map` 作为桶来记录每个品牌的总价值，方便统计和排序。
- **排序优化**：对品牌总价值进行从大到小的排序，以便快速选取前 $n$ 个最大值。

### 拓展思路
同类型题目通常涉及资源分配、选择最优方案等问题，解题关键在于找到合适的贪心策略。常见的类似算法套路包括：
- **区间问题**：如区间选点、区间覆盖等，通过对区间的排序和贪心选择来求解。
- **任务调度问题**：根据任务的优先级、时间限制等条件，选择最优的任务执行顺序。
- **背包问题的变种**：在一定的约束条件下，选择价值最大的物品组合。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略合并果子，使总代价最小。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据每个人的接水时间，安排排队顺序，使平均等待时间最短。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：在背包容量有限的情况下，选择单位价值最高的物品，使背包中物品的总价值最大。

### 个人心得摘录与总结
部分题解提到了多组测试数据时需要注意数组的初始化，避免数据残留影响结果。这是在处理多组测试数据时常见的坑点，需要特别注意。

---
处理用时：48.32秒