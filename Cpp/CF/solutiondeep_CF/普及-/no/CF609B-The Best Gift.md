# 题目信息

# The Best Gift

## 题目描述

Emily's birthday is next week and Jack has decided to buy a present for her. He knows she loves books so he goes to the local bookshop, where there are $ n $ books on sale from one of $ m $ genres.

In the bookshop, Jack decides to buy two books of different genres.

Based on the genre of books on sale in the shop, find the number of options available to Jack for choosing two books of different genres for Emily. Options are considered different if they differ in at least one book.

The books are given by indices of their genres. The genres are numbered from $ 1 $ to $ m $ .

## 说明/提示

The answer to the first test sample equals 5 as Sasha can choose:

1. the first and second books,
2. the first and third books,
3. the first and fourth books,
4. the second and third books,
5. the third and fourth books.

## 样例 #1

### 输入

```
4 3
2 1 3 1
```

### 输出

```
5
```

## 样例 #2

### 输入

```
7 4
4 2 3 1 2 4 3
```

### 输出

```
18
```

# AI分析结果

### 题目内容（中文重写）
# 最佳礼物

## 题目描述
艾米丽的生日下周就到了，杰克决定给她买一份礼物。他知道她喜欢书，于是就去了当地的书店，那里有 $n$ 本来自 $m$ 种不同类型的书在售。

在书店里，杰克决定买两本不同类型的书。

根据书店里在售书籍的类型，找出杰克为艾米丽选择两本不同类型书籍的可选方案数量。如果两种方案至少有一本书不同，则认为它们是不同的方案。

书籍通过其类型的索引给出。类型编号从 $1$ 到 $m$。

## 说明/提示
第一个测试样例的答案等于 5，因为杰克可以选择：
1. 第一本书和第二本书；
2. 第一本书和第三本书；
3. 第一本书和第四本书；
4. 第二本书和第三本书；
5. 第三本书和第四本书。

## 样例 #1
### 输入
```
4 3
2 1 3 1
```
### 输出
```
5
```

## 样例 #2
### 输入
```
7 4
4 2 3 1 2 4 3
```
### 输出
```
18
```

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路都是先统计每种类型书的数量，再通过不同方式计算两本不同类型书的组合数。主要区别在于计算组合数的方法不同。
- **暴力枚举法**：直接枚举所有类型对，计算组合数累加，但时间复杂度较高。
- **降序枚举法**：从后往前枚举，通过动态更新未计算的书的数量来计算组合数。
- **总方案减去不可行方案法**：先计算从所有书中选两本的总方案数，再减去选到两本相同类型书的方案数。

### 所选的题解
- **作者：asasas (赞：4)，4星**
    - **关键亮点**：思路清晰，代码简洁易懂，使用桶来统计每种类型书的数量，然后通过双重循环枚举所有类型对计算组合数。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[10005],n,m;
int main(){
    long long ans=0;
    cin >> n >> m;
    int q;
    for (int i=1;i<=n;i++){
        cin >> q;
        a[q]++;
    }
    for (int i=1;i<=m;i++){
        for (int j=i+1;j<=m;j++){
            ans=ans+a[i]*a[j];
        }
    } 
    cout << ans;
}
```
- **作者：Miraik (赞：4)，4星**
    - **关键亮点**：采用降序枚举的方式，通过动态更新未计算的书的数量来计算组合数，减少了计算量。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
int n,m,f[15],ans;
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++)f[read()]++;
    for(int i=m;i>=2;i--)
        n-=f[i],ans+=f[i]*n;
    printf("%d\n",ans);
    return 0;
}
```
- **作者：AzureMist (赞：0)，4星**
    - **关键亮点**：思路独特，先计算从所有书中选两本的总方案数，再减去选到两本相同类型书的方案数，简化了计算过程。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,mfs[11],ans;
int main()
{
    cin>>n>>m;
    ll a[n];
    for(ll i=0;i<=n-1;i++)
    {
        cin>>a[i];
        mfs[a[i]]++;
    }
    ans=n*(n-1)/2;
    for(ll i=1;i<=10;i++)
        if(mfs[i]>=2)
            ans=ans-mfs[i]*(mfs[i]-1)/2;
    cout<<ans;
    return 0;
}
```

### 最优关键思路或技巧
- **桶的运用**：使用桶来统计每种类型书的数量，方便后续计算组合数。
- **组合数学思想**：利用组合数的计算方法，通过不同方式计算两本不同类型书的组合数。

### 可拓展之处
同类型题目可能会增加更多的限制条件，如每种类型书有不同的价格，要求在一定预算内选择两本不同类型的书等。类似算法套路可以应用于其他组合计数问题，如从多个集合中选择元素的组合数计算。

### 推荐洛谷题目
- [P1037 产生数](https://www.luogu.com.cn/problem/P1037)
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)

### 个人心得摘录与总结
- **damage**：提到原题保证答案不超过 $2\times10^9$，所以没必要开 `long long`，但有开 `long long` 的想法是好的。总结：在做题时要仔细阅读题目条件，合理选择数据类型，避免不必要的空间浪费。

---
处理用时：31.29秒