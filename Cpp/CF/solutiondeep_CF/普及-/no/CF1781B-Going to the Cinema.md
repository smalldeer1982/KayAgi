# 题目信息

# Going to the Cinema

## 题目描述

A company of $ n $ people is planning a visit to the cinema. Every person can either go to the cinema or not. That depends on how many other people will go. Specifically, every person $ i $ said: "I want to go to the cinema if and only if at least $ a_i $ other people will go, not counting myself". That means that person $ i $ will become sad if:

- they go to the cinema, and strictly less than $ a_i $ other people go; or
- they don't go to the cinema, and at least $ a_i $ other people go.

In how many ways can a set of people going to the cinema be chosen so that nobody becomes sad?

## 说明/提示

In the first test case, both people want to go to the cinema if and only if the other person goes. There are two valid options: either both people go, or neither of them goes. However, if just one of them goes, both will be sad.

In the second test case, everyone has to go to the cinema. In any other case, someone will be sad.

In the third test case, there are three valid options: person number $ 2 $ goes to the cinema; or persons with indices $ 2, 3, 4, 7 $ go; or all eight people go.

## 样例 #1

### 输入

```
4
2
1 1
7
0 1 2 3 4 5 6
8
6 0 3 3 6 7 2 7
5
3 0 0 3 3```

### 输出

```
2
1
3
2```

# AI分析结果

### 题目内容
# 去看电影

## 题目描述
有一家公司共 $n$ 人计划去看电影。每个人要么去看电影，要么不去，这取决于有多少其他人会去。具体来说，每个人 $i$ 表示：“当且仅当至少有 $a_i$ 个其他人（不包括我自己）去看电影时，我才会去看电影”。这意味着如果出现以下情况，第 $i$ 个人会难过：
- 他们去看电影了，但去的其他人严格少于 $a_i$ 个；或者
- 他们没去看电影，但去的其他人至少有 $a_i$ 个。

问有多少种选择去看电影的人员组合方式，能保证没有人会难过？

## 说明/提示
在第一个测试用例中，两个人都表示当且仅当另一个人去时，自己才会去。有两种有效的选择：要么两人都去，要么两人都不去。然而，如果只有一个人去，两人都会难过。

在第二个测试用例中，每个人都必须去看电影。在任何其他情况下，都会有人难过。

在第三个测试用例中，有三种有效的选择：2号人去看电影；或者2、3、4、7号人去；或者八个人都去。

## 样例 #1
### 输入
```
4
2
1 1
7
0 1 2 3 4 5 6
8
6 0 3 3 6 7 2 7
5
3 0 0 3 3
```
### 输出
```
2
1
3
2
```

### 算法分类
枚举 + 前缀和

### 综合分析与结论
这些题解的核心思路都是基于对题目中人物去看电影条件关系的分析。大家都发现了要求相同的人会一起行动，以及要求低的人会跟随要求高的人行动这两个关键特性。不同题解在实现方式上有所差异，有的通过前缀和优化计数，有的通过排序简化判断过程。

### 所选的题解
- **作者：roger_yrj（5星）**
  - **关键亮点**：思路清晰，详细分析了题目特性，利用前缀和数组优化计数过程，代码简洁高效，时间复杂度为 $O(n)$。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,a[N],b[N],sum[N],ans; 
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        ans=0;
        for(int i=0;i<=n;i++)b[i]=sum[i]=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            b[a[i]]++;
        }
        sum[0]=b[0];
        for(int i=1;i<=n;i++)sum[i]=sum[i-1]+b[i];
        for(int i=0;i<=n;i++)if(sum[i]==i&&b[i]==0)ans++;
        printf("%d\n",ans);
    }
}
```
  - **核心实现思想**：首先统计每个要求值 $a_i$ 出现的次数存于数组 $b$，再计算前缀和数组 $sum$。然后枚举人数 $i$，判断当去的人数为 $i$ 时是否合法，合法条件为 $sum[i] == i$ 且 $b[i] == 0$，满足则方案数加一。

- **作者：Nuyoah_awa（4星）**
  - **关键亮点**：从暴力解法出发，逐步优化到前缀和优化，再到利用排序优化，展示了优化过程，代码可读性较好。
  - **核心代码（最终优化版）**：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
int T, n, a[N], ans;
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i = 1;i <= n;i++)
            scanf("%d", &a[i]);
        a[n+1] = N;
        sort(a + 1, a + 1 + n);
        ans = 0;
        a[1]? ans++ : 1;
        for(int i = 1;i <= n;i++)
            (a[i]!= a[i+1] && i < a[i+1] && i > a[i])? ans++ : 1 ;
        printf("%d\n", ans);
    }
    return 0;
}
```
  - **核心实现思想**：先对数组 $a$ 排序，然后通过遍历数组，当 $a[i] \neq a[i + 1]$ 且 $i < a[i + 1]$ 且 $i > a[i]$ 时，说明找到了一种新的合法方案，方案数加一。同时特判 $a[1] \neq 0$ 时，无人去的情况也算一种方案。

- **作者：wangxinyi2010（4星）**
  - **关键亮点**：通过排序和构建反向数组 $b$ 来快速找到小于某个值的 $a_i$ 的个数，思路独特。
  - **核心代码**：
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int t,n,a[200005],b[200005];
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(int j=0;j<n;j++) cin>>a[j];
        sort(a,a+n);
        for(int j=0;j<n;j++) b[a[j]]=j+1;
        int now=0,ans=0;
        for(int j=0;j<=n;j++){
            if(b[j]!=0) now=b[j];
            else if(j==now) ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
  - **核心实现思想**：对 $a$ 数组排序后，构建数组 $b$ 记录 $a_i$ 对应的最大下标。遍历 $0$ 到 $n$，若 $b[j] \neq 0$ 则更新 $now$，若 $j == now$ 说明当前人数 $j$ 对应的方案合法，方案数加一。

### 最优关键思路或技巧
1. **利用前缀和优化计数**：通过统计每个要求值的人数，并计算前缀和，能快速得到满足某个条件的总人数，从而优化枚举过程中的判断效率。
2. **排序简化判断**：对要求数组进行排序后，可以利用相邻元素的关系简化合法方案的判断逻辑，减少不必要的计算。

### 同类型题或类似算法套路拓展
此类题目通常涉及到根据一些相互关联的条件来确定方案数。类似套路包括先分析条件之间的逻辑关系，找到可以优化的点，如利用数据结构（如前缀和数组）来加速计算，或者通过排序等操作简化判断过程。

### 洛谷相似题目推荐
1. [P1131 海战](https://www.luogu.com.cn/problem/P1131)：通过分析矩阵中元素之间的关系，利用类似的枚举和计数思路来解决问题。
2. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)：在给定规则下，通过类似的对每个位置进行条件判断和状态记录来完成遍历和计数。
3. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)：同样是根据一些条件对方案进行判断和选择，可通过排序和前缀和等方法优化。 

---
处理用时：46.25秒