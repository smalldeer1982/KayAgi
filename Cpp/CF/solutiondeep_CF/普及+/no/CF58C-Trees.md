# 题目信息

# Trees

## 题目描述

On Bertown's main street $ n $ trees are growing, the tree number $ i $ has the height of $ a_{i} $ meters ( $ 1<=i<=n $ ). By the arrival of the President of Berland these trees were decided to be changed so that their heights formed a beautiful sequence. This means that the heights of trees on ends (the $ 1 $ st one and the $ n $ -th one) should be equal to each other, the heights of the $ 2 $ -nd and the $ (n-1) $ -th tree must also be equal to each other, at that the height of the $ 2 $ -nd tree should be larger than the height of the first tree by $ 1 $ , and so on. In other words, the heights of the trees, standing at equal distance from the edge (of one end of the sequence) must be equal to each other, and with the increasing of the distance from the edge by $ 1 $ the tree height must also increase by $ 1 $ . For example, the sequences "2 3 4 5 5 4 3 2" and "1 2 3 2 1" are beautiful, and '1 3 3 1" and "1 2 3 1" are not.

Changing the height of a tree is a very expensive operation, using advanced technologies invented by Berland scientists. In one operation you can choose any tree and change its height to any number, either increase or decrease. Note that even after the change the height should remain a positive integer, i. e, it can't be less than or equal to zero. Identify the smallest number of changes of the trees' height needed for the sequence of their heights to become beautiful.

## 样例 #1

### 输入

```
3
2 2 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
1 2 2 1
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# Trees

## 题目描述
在伯顿镇的主街上种着$n$棵树，第$i$棵树的高度为$a_{i}$米（$1\leq i\leq n$）。为迎接伯兰德国总统的到访，这些树的高度被决定进行调整，使其高度形成一个优美的序列。这意味着两端的树（第$1$棵和第$n$棵）高度应相等，第$2$棵和第$(n - 1)$棵树的高度也应相等，且第$2$棵树的高度应比第$1$棵树高$1$，依此类推。换句话说，与边缘（序列一端）距离相等的树的高度应该相等，并且随着与边缘距离增加$1$，树的高度也应增加$1$。例如，序列“$2 3 4 5 5 4 3 2$”和“$1 2 3 2 1$”是优美的，而“$1 3 3 1$”和“$1 2 3 1$”则不是。

改变一棵树的高度是一项非常昂贵的操作，需要使用伯兰德国科学家发明的先进技术。在一次操作中，你可以选择任意一棵树，并将其高度改变为任意正整数（即不能小于或等于零）。确定使树高序列变得优美所需的最少高度改变次数。

## 样例 #1
### 输入
```
3
2 2 2
```
### 输出
```
1
```

## 样例 #2
### 输入
```
4
1 2 2 1
```
### 输出
```
0
```

### 算法分类
数学

### 题解综合分析与结论
所有题解核心思路一致，均采用逆向思维，将求最少修改次数转化为求最多不修改次数。要点在于利用优美序列特性，即每一位数字与对应编号（或简单序列对应位）差值相等，通过桶记录各差值出现次数，找出出现次数最多的差值，其对应数量即为最多不修改数，用总数$n$减去该数量得最少修改次数。解决难点关键在于发现并运用这一差值相等规律。

### 所选的题解
- **作者：Tune_ (赞：18) - 5星**
    - **关键亮点**：思路清晰，直接点明逆向思维，通过具体例子展示数列与数位编号关系，简洁易懂。代码简洁明了，逻辑清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,n,t[100005],s=0; 
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        a-=min(i,n-i+1);
        if(a>=0)
        {
            t[a]++;
            s=max(s,t[a]);
        }
    }
    cout<<n-s;
    return 0;
}
```
    - **核心实现思想**：读入树高，计算每个数与对应编号差值，若差值非负则用桶记录其出现次数，更新最大出现次数，最后用总数$n$减去最大出现次数得最少修改数。
- **作者：_HCl_ (赞：5) - 4星**
    - **关键亮点**：详细阐述题意、思路及实现步骤，引入“简单序列”概念辅助理解，逻辑严谨。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[1000001],b[100001],c[100001];
int cnt,maxn;
int main()
{
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n;++i)
    {
        if(a[i]-min(i,n-i+1)<0)continue;
        c[a[i]-min(i,n-i+1)]++;
        if(c[a[i]-min(i,n-i+1)]>maxn)
        {
            maxn=c[a[i]-min(i,n-i+1)];
        }
    }
    cout<<n-maxn;
}
```
    - **核心实现思想**：读入树高，构造简单序列，计算差值，用桶记录差值出现次数，更新最大出现次数，输出总数$n$与最大出现次数差值。
- **作者：墨舞灵纯 (赞：5) - 4星**
    - **关键亮点**：简洁阐述逆向思维解题思路，代码简洁高效。
    - **核心代码**：
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=1000005;
int a[N],n,x,ans; 
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&x);
        x-=min(i,n-i+1);
        if(x>=0)
        {
            ++a[x];
            ans=max(ans,a[x]);
        }
    }
    printf("%d",n-ans);
    return 0;
}
```
    - **核心实现思想**：读入树高，计算与对应编号差值，非负则用桶记录并更新最大出现次数，最后输出最少修改数。

### 最优关键思路或技巧
逆向思维，将求最少修改次数转化为求最多不修改次数。利用优美序列数字与对应编号差值相等规律，通过桶记录差值出现次数求解。

### 拓展
同类型题常围绕特定序列性质，通过逆向思维或寻找规律解决。类似算法套路如分析序列特征，建立数学关系，用数据结构（如桶）辅助统计计算。

### 相似知识点洛谷题目
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)
- [P1134 阶乘问题](https://www.luogu.com.cn/problem/P1134)
- [P1147 连续自然数和](https://www.luogu.com.cn/problem/P1147)

### 个人心得摘录与总结
多位作者提到逆向思维重要性，如linyinuo2008指出正向找最少修改数规律难，逆向求最多不修改数更易发现规律。部分作者强调模拟数据辅助理解，如zythonc分享被一组数据卡住调试经历，表明模拟对理解题目与算法重要性。 

---
处理用时：68.12秒