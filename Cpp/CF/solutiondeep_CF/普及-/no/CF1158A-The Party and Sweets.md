# 题目信息

# The Party and Sweets

## 题目描述

 $ n $ boys and $ m $ girls came to the party. Each boy presented each girl some integer number of sweets (possibly zero). All boys are numbered with integers from $ 1 $ to $ n $ and all girls are numbered with integers from $ 1 $ to $ m $ . For all $ 1 \leq i \leq n $ the minimal number of sweets, which $ i $ -th boy presented to some girl is equal to $ b_i $ and for all $ 1 \leq j \leq m $ the maximal number of sweets, which $ j $ -th girl received from some boy is equal to $ g_j $ .

More formally, let $ a_{i,j} $ be the number of sweets which the $ i $ -th boy give to the $ j $ -th girl. Then $ b_i $ is equal exactly to the minimum among values $ a_{i,1}, a_{i,2}, \ldots, a_{i,m} $ and $ g_j $ is equal exactly to the maximum among values $ b_{1,j}, b_{2,j}, \ldots, b_{n,j} $ .

You are interested in the minimum total number of sweets that boys could present, so you need to minimize the sum of $ a_{i,j} $ for all $ (i,j) $ such that $ 1 \leq i \leq n $ and $ 1 \leq j \leq m $ . You are given the numbers $ b_1, \ldots, b_n $ and $ g_1, \ldots, g_m $ , determine this number.

## 说明/提示

In the first test, the minimal total number of sweets, which boys could have presented is equal to $ 12 $ . This can be possible, for example, if the first boy presented $ 1 $ and $ 4 $ sweets, the second boy presented $ 3 $ and $ 2 $ sweets and the third boy presented $ 1 $ and $ 1 $ sweets for the first and the second girl, respectively. It's easy to see, that all conditions are satisfied and the total number of sweets is equal to $ 12 $ .

In the second test, the boys couldn't have presented sweets in such way, that all statements satisfied.

In the third test, the minimal total number of sweets, which boys could have presented is equal to $ 4 $ . This can be possible, for example, if the first boy presented $ 1 $ , $ 1 $ , $ 2 $ sweets for the first, second, third girl, respectively and the second boy didn't present sweets for each girl. It's easy to see, that all conditions are satisfied and the total number of sweets is equal to $ 4 $ .

## 样例 #1

### 输入

```
3 2
1 2 1
3 4
```

### 输出

```
12```

## 样例 #2

### 输入

```
2 2
0 1
1 0
```

### 输出

```
-1```

## 样例 #3

### 输入

```
2 3
1 0
1 1 2
```

### 输出

```
4```

# AI分析结果

### 题目内容
# 派对与糖果

## 题目描述
有\(n\)个男孩和\(m\)个女孩来到派对。每个男孩给每个女孩一些整数数量的糖果（可能为零）。所有男孩都用从\(1\)到\(n\)的整数编号，所有女孩都用从\(1\)到\(m\)的整数编号。对于所有\(1 \leq i \leq n\)，第\(i\)个男孩给某个女孩的糖果的最小数量等于\(b_i\)；对于所有\(1 \leq j \leq m\)，第\(j\)个女孩从某个男孩那里得到的糖果的最大数量等于\(g_j\)。

更正式地说，设\(a_{i,j}\)是第\(i\)个男孩给第\(j\)个女孩的糖果数量。那么\(b_i\)恰好等于\(a_{i,1}, a_{i,2}, \ldots, a_{i,m}\)中的最小值，\(g_j\)恰好等于\(b_{1,j}, b_{2,j}, \ldots, b_{n,j}\)中的最大值。

你对男孩们可能给出的最小糖果总数感兴趣，所以你需要最小化所有满足\(1 \leq i \leq n\)且\(1 \leq j \leq m\)的\((i,j)\)对应的\(a_{i,j}\)的和。给定数字\(b_1, \ldots, b_n\)和\(g_1, \ldots, g_m\)，确定这个数量。

## 说明/提示
在第一个测试中，男孩们可能给出的最小糖果总数等于\(12\)。例如，如果第一个男孩给\(1\)颗和\(4\)颗糖果，第二个男孩给\(3\)颗和\(2\)颗糖果，第三个男孩分别给第一个和第二个女孩\(1\)颗糖果，就可以实现。很容易看出，所有条件都满足，糖果总数等于\(12\)。

在第二个测试中，男孩们不可能以满足所有条件的方式给出糖果。

在第三个测试中，男孩们可能给出的最小糖果总数等于\(4\)。例如，如果第一个男孩分别给第一个、第二个、第三个女孩\(1\)颗、\(1\)颗、\(2\)颗糖果，第二个男孩不给每个女孩糖果。很容易看出，所有条件都满足，糖果总数等于\(4\)。

## 样例 #1
### 输入
```
3 2
1 2 1
3 4
```
### 输出
```
12```

## 样例 #2
### 输入
```
2 2
0 1
1 0
```
### 输出
```
-1```

## 样例 #3
### 输入
```
2 3
1 0
1 1 2
```
### 输出
```
4```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是通过分类讨论来解决问题。首先对男孩给出糖果的最小值数组\(b\)和女孩收到糖果的最大值数组\(g\)进行排序，然后根据\(b\)数组中的最大值与\(g\)数组中的最小值的关系进行分类：
 - **无解情况**：当\(b\)数组中的最大值大于\(g\)数组中的最小值时，不存在满足条件的分配方式，输出\(-1\)。
 - **相等情况**：当\(b\)数组中的最大值等于\(g\)数组中的最小值时，除了最大值对应的男孩外，其他男孩给每个女孩的糖果数为其各自的最小值，而最大值对应的男孩给每个女孩的糖果数为\(g\)数组中的值，以此计算总糖果数。
 - **大于情况**：当\(b\)数组中的最大值小于\(g\)数组中的最小值时，除了一个男孩给一个女孩\(g\)数组中的最小值，其他男孩给每个女孩的糖果数为其各自的最小值，剩下的\(g\)数组中的值由另一个男孩提供，计算总糖果数。
各题解的算法要点和解决难点基本一致，主要区别在于代码实现的细节和表述方式。

### 所选的题解
 - **作者：cute_overmind（5星）**
    - **关键亮点**：思路清晰，代码简洁明了，对每种情况的处理逻辑清晰，变量命名规范。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5; 
int n, m, b[N], g[N], ans;
signed main() 
{
    cin >> n >> m;
    for (int i = 1;i <= n;i++) cin >> b[i];
    for (int i = 1;i <= m;i++) cin >> g[i];
    sort(b + 1, b + n + 1);
    sort(g + 1, g + m + 1);
    if (b[n] > g[1]){
        cout << -1 << endl;
        return 0;
    }
    if (b[n] == g[1]){
        for (int i = 1;i < n;i++) ans += b[i] * m; 
        for (int i = 1;i <= m;i++) ans += g[i];
    } 
    else{
        for (int i = 1;i < n;i++) ans += b[i] * m;
        ans = ans - b[n - 1] + g[1] + b[n];
        for (int i = 2;i <= m;i++) ans += g[i];
    }
    cout << ans << '\n';
    return 0;
}
```
核心实现思想：先读入数据并排序，然后根据\(b[n]\)与\(g[1]\)的关系分情况计算最小糖果总数。
 - **作者：Storm_Lightning（5星）**
    - **关键亮点**：算法分析简洁准确，代码风格良好，逻辑清晰，注释详细。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
long long n,m;
long long b[100086];
long long g[100086];
int main()
{
    scanf("%lld%lld",&n,&m);
    for(long long i=0;i<n;i++) 
    {
        scanf("%lld",&b[i]);
    }
    for(long long i=0;i<m;i++) 
    {
        scanf("%lld",&g[i]);
    }
    sort(b,b+n);
    sort(g,g+m);
    if(b[n-1]>g[0]) 
    {
        printf("-1\n");
    }
    else
    {
        long long sum=0;
        if(b[n-1]==g[0])
        {
            for(long long i=0;i<n-1;i++)
            {
                sum+=b[i]*m;
            }
            for(long long i=0;i<m;i++) 
            {
                sum+=g[i];
            }
        }
        else
        {
            for(long long i=0;i<n-1;i++) 
            {
                sum+=b[i]*m;
            }
            sum=sum-b[n-2]+g[0]+b[n-1];
            for(long long i=1;i<m;i++) 
            {
                sum+=g[i];
            }
        }
        printf("%lld\n",sum);
    }
    return 0;
}
```
核心实现思想：与上一题解类似，读入数据排序后，依据\(b[n - 1]\)与\(g[0]\)的关系分情况计算最小糖果总数。
 - **作者：king_xuan（5星）**
    - **关键亮点**：前言部分点明题目重点，思路阐述清晰，代码规范且有注释提醒注意事项。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
#define int long long//建议大家都写上,毕竟"十年OI一场空,不开long long见祖宗" 
int n,m;
int b[100010],g[100010];
signed main(){//记得将int换成signed
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    for(int i=1;i<=m;i++){
        cin>>g[i];
    }
    sort(b,b+n);
    sort(g,g+m);
    if(b[n-1]>g[0]){
        cout<<-1<<endl;
    }else{
        int ans=0;
        if(b[n-1]==g[0]){
            for(int i=0;i<n-1;i++){
                ans+=b[i]*m;
            }
            for(int i=0;i<m;i++){
                ans+=g[i];
            }
        }else{
            for(int i=0;i<n-1;i++){
                ans+=b[i]*m;
            }
            ans=ans-b[n-2]+g[0]+b[n-1];
            for(int i=1;i<m;i++){
                ans+=g[i];
            }
        }
        cout<<ans;
    }
    return 0;//养成好习惯 
}
```
核心实现思想：同样是读入数据并排序，根据\(b[n - 1]\)与\(g[0]\)的大小关系分情况计算最小糖果总数。

### 最优关键思路或技巧
 - **排序与分类讨论**：通过对男孩给出糖果最小值数组和女孩收到糖果最大值数组排序，清晰地根据两个数组特定位置元素（最大值与最小值）的关系进行分类讨论，简化问题求解过程。
 - **贪心策略**：在每种情况下，都以贪心的方式分配糖果，使得总糖果数最小，例如在满足条件下，让男孩尽量以最小的糖果数满足女孩的最大糖果数要求。

### 拓展思路
此类题目属于基于条件约束的最值问题，类似套路是先分析条件之间的逻辑关系，通过排序等方式简化条件判断，再利用贪心思想进行求解。同类型题可能会改变约束条件或者数据规模，例如增加更多限制条件，或者将数据范围扩大到高精度计算。

### 洛谷相似题目推荐
 - [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过对数据排序后利用贪心策略解决分组问题。
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：根据接水时间排序，利用贪心思想计算总等待时间。
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过对数据进行特定排序后贪心求解最大奖励。

### 个人心得摘录与总结
部分题解提到要注意数据范围，建议开`long long`类型防止数据溢出，这是在处理数值计算问题时需要时刻关注的点，避免因数据类型导致的错误。 

---
处理用时：96.09秒