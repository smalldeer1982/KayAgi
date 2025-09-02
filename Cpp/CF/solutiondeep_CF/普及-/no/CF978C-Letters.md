# 题目信息

# Letters

## 题目描述

There are $ n $ dormitories in Berland State University, they are numbered with integers from $ 1 $ to $ n $ . Each dormitory consists of rooms, there are $ a_i $ rooms in $ i $ -th dormitory. The rooms in $ i $ -th dormitory are numbered from $ 1 $ to $ a_i $ .

A postman delivers letters. Sometimes there is no specific dormitory and room number in it on an envelope. Instead of it only a room number among all rooms of all $ n $ dormitories is written on an envelope. In this case, assume that all the rooms are numbered from $ 1 $ to $ a_1 + a_2 + \dots + a_n $ and the rooms of the first dormitory go first, the rooms of the second dormitory go after them and so on.

For example, in case $ n=2 $ , $ a_1=3 $ and $ a_2=5 $ an envelope can have any integer from $ 1 $ to $ 8 $ written on it. If the number $ 7 $ is written on an envelope, it means that the letter should be delivered to the room number $ 4 $ of the second dormitory.

For each of $ m $ letters by the room number among all $ n $ dormitories, determine the particular dormitory and the room number in a dormitory where this letter should be delivered.

## 说明/提示

In the first example letters should be delivered in the following order:

- the first letter in room $ 1 $ of the first dormitory
- the second letter in room $ 9 $ of the first dormitory
- the third letter in room $ 2 $ of the second dormitory
- the fourth letter in room $ 13 $ of the second dormitory
- the fifth letter in room $ 1 $ of the third dormitory
- the sixth letter in room $ 12 $ of the third dormitory

## 样例 #1

### 输入

```
3 6
10 15 12
1 9 12 23 26 37
```

### 输出

```
1 1
1 9
2 2
2 13
3 1
3 12
```

## 样例 #2

### 输入

```
2 3
5 10000000000
5 6 9999999999
```

### 输出

```
1 5
2 1
2 9999999994
```

# AI分析结果

### 题目中文重写
# 信件

## 题目描述
在伯兰国立大学有 $n$ 栋宿舍楼，它们的编号从 $1$ 到 $n$。每栋宿舍楼由若干房间组成，第 $i$ 栋宿舍楼有 $a_i$ 个房间。第 $i$ 栋宿舍楼的房间编号从 $1$ 到 $a_i$。

有一位邮递员负责送信。有时信封上不会写明具体的宿舍楼号和房间号，而是只写了所有 $n$ 栋宿舍楼中所有房间的统一编号。在这种情况下，假设所有房间的编号从 $1$ 到 $a_1 + a_2 + \dots + a_n$，并且第一栋宿舍楼的房间排在最前面，第二栋宿舍楼的房间紧随其后，依此类推。

例如，当 $n = 2$，$a_1 = 3$ 且 $a_2 = 5$ 时，信封上可以写从 $1$ 到 $8$ 之间的任何整数。如果信封上写的数字是 $7$，则意味着这封信应该被送到第二栋宿舍楼的第 $4$ 个房间。

对于 $m$ 封信中的每一封，根据所有 $n$ 栋宿舍楼中的房间编号，确定这封信应该被送到哪一栋宿舍楼以及该宿舍楼中的房间号。

## 说明/提示
在第一个样例中，信件应该按照以下顺序投递：
- 第一封信投递到第一栋宿舍楼的第 $1$ 个房间
- 第二封信投递到第一栋宿舍楼的第 $9$ 个房间
- 第三封信投递到第二栋宿舍楼的第 $2$ 个房间
- 第四封信投递到第二栋宿舍楼的第 $13$ 个房间
- 第五封信投递到第三栋宿舍楼的第 $1$ 个房间
- 第六封信投递到第三栋宿舍楼的第 $12$ 个房间

## 样例 #1
### 输入
```
3 6
10 15 12
1 9 12 23 26 37
```
### 输出
```
1 1
1 9
2 2
2 13
3 1
3 12
```

## 样例 #2
### 输入
```
2 3
5 10000000000
5 6 9999999999
```
### 输出
```
1 5
2 1
2 9999999994
```

### 算法分类
前缀和

### 综合分析与结论
这些题解的核心思路都是先预处理出前缀和数组，用于记录每栋宿舍楼最后一个房间的编号。对于每个询问的房间编号，不同题解采用了不同的方法来确定其所在的宿舍楼和房间号。部分题解利用了询问序列递增的特性，通过模拟的方式一层一层往上找；部分题解则使用二分查找来快速定位。

### 所选题解
- **Silence_water（5星）**
    - **关键亮点**：思路清晰，详细说明了利用询问序列递增的特性进行模拟的方法，代码注释清晰，易于理解。
    - **个人心得**：指出翻译中丢掉了询问序列房间编号递增的关键信息。
- **StudyingFather（4星）**
    - **关键亮点**：代码简洁，按照题意直接进行计算，逻辑清晰。
- **封禁用户（4星）**
    - **关键亮点**：明确指出使用二分和前缀和的算法，思路和代码都很清晰。

### 重点代码
#### Silence_water 的核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=2e5+5;
int n,m,fl=1;
ll a[M],b[M],p[M];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        p[i]=p[i-1]+a[i];// 前缀和。p[i]即第i层的最后一个房间的编号
    }
    for(int i=1;i<=m;i++)
    {
        ll x;scanf("%lld",&x);
        ll ch=x-p[fl-1];// 还差这么多编号
        while(ch>a[fl])ch-=a[fl],fl++;// 模拟
        printf("%d %lld\n",fl,ch);
    }
    return 0;
}
```
**核心实现思想**：先预处理前缀和数组 `p`，对于每个询问的房间编号 `x`，计算其与当前楼层之前所有房间数的差值 `ch`，若 `ch` 大于当前楼层的房间数，则进入下一层，直到找到对应的楼层和房间号。

#### StudyingFather 的核心代码
```cpp
#include <iostream>
using namespace std;
long long n,m,a[200005],b[200005],c[200005];
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        c[i]=c[i-1]+a[i];
    }
    int f=1;
    for(int i=1;i<=m;i++)
    {
        cin>>b[i];
        long long k=b[i]-c[f-1];
        while(k>a[f])//这里计算宿舍号和房间号
            k-=a[f++];
        cout<<f<<' '<<k<<endl;
    }
    return 0;
}
```
**核心实现思想**：同样先预处理前缀和数组 `c`，对于每个询问的房间编号 `b[i]`，计算其与当前楼层之前所有房间数的差值 `k`，若 `k` 大于当前楼层的房间数，则进入下一层，直到找到对应的楼层和房间号。

#### 封禁用户的核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200020],b,sum[200020];
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i ++)
    {
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    while(m--)
    {
        cin>>b;
        int f=lower_bound(sum+1,sum+1+n, b)-sum;
        long long k=b-sum[f-1];
        cout<<f<<" "<<k<<endl;
    }
    return 0;
}
```
**核心实现思想**：预处理前缀和数组 `sum`，对于每个询问的房间编号 `b`，使用 `lower_bound` 函数二分查找第一个大于等于 `b` 的前缀和位置 `f`，该位置即为宿舍楼号，房间号为 `b - sum[f - 1]`。

### 关键思路或技巧
- 预处理前缀和数组，方便快速计算每栋宿舍楼最后一个房间的编号。
- 利用询问序列递增的特性，采用模拟或二分查找的方法来确定房间所在的宿舍楼和房间号。

### 拓展思路
同类型题目通常会涉及区间查询、范围判断等问题，都可以考虑使用前缀和来优化计算。类似的算法套路还有差分，用于处理区间修改问题。

### 推荐题目
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
- [P3406 海底高铁](https://www.luogu.com.cn/problem/P3406)
- [P2367 语文成绩](https://www.luogu.com.cn/problem/P2367)

### 个人心得总结
- Silence_water 指出翻译中可能会遗漏关键信息，做题时需要仔细查看英文原文。
- Shadow_T 提到不开 `long long` 可能会导致错误，在处理数据范围较大的题目时需要注意数据类型。

---
处理用时：51.30秒