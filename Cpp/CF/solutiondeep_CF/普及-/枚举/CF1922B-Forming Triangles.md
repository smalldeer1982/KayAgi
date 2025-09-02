# 题目信息

# Forming Triangles

## 题目描述

You have $ n $ sticks, numbered from $ 1 $ to $ n $ . The length of the $ i $ -th stick is $ 2^{a_i} $ .

You want to choose exactly $ 3 $ sticks out of the given $ n $ sticks, and form a non-degenerate triangle out of them, using the sticks as the sides of the triangle. A triangle is called non-degenerate if its area is strictly greater than $ 0 $ .

You have to calculate the number of ways to choose exactly $ 3 $ sticks so that a triangle can be formed out of them. Note that the order of choosing sticks does not matter (for example, choosing the $ 1 $ -st, $ 2 $ -nd and $ 4 $ -th stick is the same as choosing the $ 2 $ -nd, $ 4 $ -th and $ 1 $ -st stick).

## 说明/提示

In the first test case of the example, any three sticks out of the given $ 7 $ can be chosen.

In the second test case of the example, you can choose the $ 1 $ -st, $ 2 $ -nd and $ 4 $ -th stick, or the $ 1 $ -st, $ 3 $ -rd and $ 4 $ -th stick.

In the third test case of the example, you cannot form a triangle out of the given sticks with lengths $ 2 $ , $ 4 $ and $ 8 $ .

## 样例 #1

### 输入

```
4
7
1 1 1 1 1 1 1
4
3 2 1 3
3
1 2 3
1
1```

### 输出

```
35
2
0
0```

# AI分析结果

### 题目内容中文重写
## 组成三角形

### 题目描述
你有 $n$ 根木棒，编号从 $1$ 到 $n$。第 $i$ 根木棒的长度为 $2^{a_i}$。

你想从给定的 $n$ 根木棒中恰好选择 $3$ 根，并使用这些木棒作为三角形的边，组成一个非退化三角形。如果一个三角形的面积严格大于 $0$，则称其为非退化三角形。

你需要计算恰好选择 $3$ 根木棒以组成三角形的方案数。请注意，选择木棒的顺序无关紧要（例如，选择第 $1$ 根、第 $2$ 根和第 $4$ 根木棒与选择第 $2$ 根、第 $4$ 根和第 $1$ 根木棒是相同的）。

### 说明/提示
在样例的第一个测试用例中，可以从给定的 $7$ 根木棒中任选 $3$ 根。

在样例的第二个测试用例中，你可以选择第 $1$ 根、第 $2$ 根和第 $4$ 根木棒，或者选择第 $1$ 根、第 $3$ 根和第 $4$ 根木棒。

在样例的第三个测试用例中，你不能用长度为 $2$、$4$ 和 $8$ 的给定木棒组成三角形。

### 样例 #1
#### 输入
```
4
7
1 1 1 1 1 1 1
4
3 2 1 3
3
1 2 3
1
1
```
#### 输出
```
35
2
0
0
```

### 综合分析与结论
这些题解的核心思路都是先根据三角形的边长关系（两边之和大于第三边）以及木棒长度为 $2$ 的幂次这一特点，推导出能构成三角形的组合只有两种情况：三根长度相同和两根长度相同且另一根较短。然后通过分类讨论，利用组合数公式计算方案数。

#### 算法要点
- **统计出现次数**：使用数组（桶）或 `map` 统计每个 $a_i$ 出现的次数。
- **分类计算**：分别计算三根长度相同和两根长度相同且另一根较短的组合数，最后求和。
- **前缀和优化**：部分题解使用前缀和数组快速计算比当前长度小的木棒数量。

#### 解决难点
- **推导组合情况**：通过数学推导得出能构成三角形的组合情况。
- **避免重复计算**：在计算组合数时，要注意选择的顺序无关紧要，避免重复计数。

### 所选题解
- **作者：wanglexi（5星）**
    - **关键亮点**：思路清晰，详细推导了能构成三角形的条件，对两种组合情况的分析和代码实现都很清晰，还给出了避免超时的优化提示。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,n,a[300005];
ll cnt[300005],s[300005],ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        ans=0;
        for(int i=0;i<=n;i++)cnt[i]=s[i]=0;
        for(int i=1;i<=n;i++)cin>>a[i],cnt[a[i]]++;
        for(int i=0;i<=n;i++)ans+=cnt[i]*(cnt[i]-1)*(cnt[i]-2)/6,s[i]=(i==0?0:s[i-1])+cnt[i];
        for(int i=1;i<=n;i++)ans+=cnt[i]*(cnt[i]-1)/2*s[i-1];
        cout<<ans<<"\n";
    }
    return 0;
}
```
核心实现思想：使用 `cnt` 数组统计每个 $a_i$ 出现的次数，`s` 数组作为前缀和数组。先计算三根长度相同的组合数，再计算两根长度相同且另一根较短的组合数，最后将两者相加得到答案。

- **作者：Jerry_heng（4星）**
    - **关键亮点**：思路简洁明了，代码实现简洁，直接给出了两种情况的计算方式和代码。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x,sum[300010],ans,s;
signed main(){
    scanf("%lld",&t);
    while(t--){
        scanf("%lld",&n);
        ans=0,s=0;
        memset(sum,0,sizeof sum);
        for(int i=1;i<=n;i++){
            scanf("%lld",&x);
            sum[x]++;
        }
        for(int i=0;i<=n;i++){
            if(sum[i]>1)ans+=sum[i]*(sum[i]-1)/2*s;
            if(sum[i]>2)ans+=sum[i]*(sum[i]-1)*(sum[i]-2)/6;
            s+=sum[i];
        }
        printf("%lld\n",ans);
    }
    return 0;
} 
```
核心实现思想：使用 `sum` 数组统计每个 $a_i$ 出现的次数，在遍历数组时，同时计算两种组合情况的方案数并累加到 `ans` 中。

- **作者：indream（4星）**
    - **关键亮点**：思路清晰，给出了详细的公式推导，代码注释明确，还给出了注意事项。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define MAXN 300005
using namespace std;
typedef long long ll;
ll n,t,tmp,sum,ans;
int cnt[MAXN];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>t;
    while(t--){
        sum=0;ans=0;
        cin>>n;
        for(int i=0;i<=n;++i)
            cnt[i]=0;
        for(int i=0;i<n;++i){
            cin>>tmp;
            ++cnt[tmp];
        }
        for(int i=0;i<=n;++i){
            ll t=cnt[i];
            ans+=t*(t-1)/2*sum;
            ans+=t*(t-1)*(t-2)/6;
            sum+=cnt[i];
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```
核心实现思想：使用 `cnt` 数组统计每个 $a_i$ 出现的次数，通过遍历数组，根据公式计算两种组合情况的方案数并累加到 `ans` 中。

### 最优关键思路或技巧
- **数学推导**：通过数学推导得出能构成三角形的组合情况，将问题简化。
- **分类讨论**：将满足条件的组合分为两种情况分别计算，降低计算复杂度。
- **前缀和优化**：使用前缀和数组快速计算比当前长度小的木棒数量，提高计算效率。

### 可拓展之处
同类型题可能会改变木棒长度的计算方式或三角形的构成条件，但解题思路仍然可以是先分析满足条件的组合情况，再进行分类计算。类似算法套路可以应用于其他组合计数问题，如从多个元素中选择满足特定条件的组合。

### 推荐洛谷题目
- [P1104 生日](https://www.luogu.com.cn/problem/P1104)：考察排序和计数。
- [P1097 统计数字](https://www.luogu.com.cn/problem/P1097)：考察统计元素出现次数。
- [P1271 选举学生会](https://www.luogu.com.cn/problem/P1271)：考察排序和计数。

### 个人心得摘录与总结
- **wanglexi**：指出在处理多组数据时，使用 `memset` 会导致超时，应改用循环赋值，避免了时间复杂度的增加。
- **indream**：提到不用特判 $n<3$ 的情况，否则在 $T\ne1$ 时会出错，但不清楚具体原因，提醒了在编程时要注意边界条件的处理。 

---
处理用时：39.15秒