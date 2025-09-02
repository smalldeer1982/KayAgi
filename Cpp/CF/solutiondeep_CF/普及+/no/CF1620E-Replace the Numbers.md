# 题目信息

# Replace the Numbers

## 题目描述

You have an array of integers (initially empty).

You have to perform $ q $ queries. Each query is of one of two types:

- " $ 1 $ $ x $ " — add the element $ x $ to the end of the array;
- " $ 2 $ $ x $ $ y $ " — replace all occurrences of $ x $ in the array with $ y $ .

Find the resulting array after performing all the queries.

## 说明/提示

In the first example, the array changes as follows:

 $ [] $ $ \rightarrow $ $ [3] $ $ \rightarrow $ $ [3, 1] $ $ \rightarrow $ $ [3, 2] $ $ \rightarrow $ $ [3, 2, 2] $ $ \rightarrow $ $ [3, 2, 2, 1] $ $ \rightarrow $ $ [3, 2, 2, 1, 2] $ $ \rightarrow $ $ [3, 2, 2, 3, 2] $ .

In the second example, the array changes as follows:

 $ [] $ $ \rightarrow $ $ [1] $ $ \rightarrow $ $ [1, 2] $ $ \rightarrow $ $ [1, 2, 1] $ $ \rightarrow $ $ [1, 2, 1] $ .

In the third example, the array changes as follows:

 $ [] $ $ \rightarrow $ $ [] $ $ \rightarrow $ $ [1] $ $ \rightarrow $ $ [1, 4] $ $ \rightarrow $ $ [1, 4, 2] $ $ \rightarrow $ $ [1, 4, 4] $ $ \rightarrow $ $ [1, 3, 3] $ $ \rightarrow $ $ [1, 3, 3, 2] $ $ \rightarrow $ $ [1, 3, 3, 7] $ .

## 样例 #1

### 输入

```
7
1 3
1 1
2 1 2
1 2
1 1
1 2
2 1 3```

### 输出

```
3 2 2 3 2```

## 样例 #2

### 输入

```
4
1 1
1 2
1 1
2 2 2```

### 输出

```
1 2 1```

## 样例 #3

### 输入

```
8
2 1 4
1 1
1 4
1 2
2 2 4
2 4 3
1 2
2 2 7```

### 输出

```
1 3 3 7```

# AI分析结果

### 题目翻译
## 替换数字

### 题目描述
你有一个整数数组（初始为空）。

你需要执行 $q$ 次查询。每次查询有以下两种类型之一：
- “$1$ $x$” — 将元素 $x$ 添加到数组末尾；
- “$2$ $x$ $y$” — 将数组中所有 $x$ 的出现替换为 $y$。

求出执行所有查询后的结果数组。

### 说明/提示
在第一个示例中，数组变化如下：
$ [] $ $ \rightarrow $ $ [3] $ $ \rightarrow $ $ [3, 1] $ $ \rightarrow $ $ [3, 2] $ $ \rightarrow $ $ [3, 2, 2] $ $ \rightarrow $ $ [3, 2, 2, 1] $ $ \rightarrow $ $ [3, 2, 2, 1, 2] $ $ \rightarrow $ $ [3, 2, 2, 3, 2] $ 。

在第二个示例中，数组变化如下：
$ [] $ $ \rightarrow $ $ [1] $ $ \rightarrow $ $ [1, 2] $ $ \rightarrow $ $ [1, 2, 1] $ $ \rightarrow $ $ [1, 2, 1] $ 。

在第三个示例中，数组变化如下：
$ [] $ $ \rightarrow $ $ [] $ $ \rightarrow $ $ [1] $ $ \rightarrow $ $ [1, 4] $ $ \rightarrow $ $ [1, 4, 2] $ $ \rightarrow $ $ [1, 4, 4] $ $ \rightarrow $ $ [1, 3, 3] $ $ \rightarrow $ $ [1, 3, 3, 2] $ $ \rightarrow $ $ [1, 3, 3, 7] $ 。

### 样例 #1
#### 输入
```
7
1 3
1 1
2 1 2
1 2
1 1
1 2
2 1 3
```
#### 输出
```
3 2 2 3 2
```

### 样例 #2
#### 输入
```
4
1 1
1 2
1 1
2 2 2
```
#### 输出
```
1 2 1
```

### 样例 #3
#### 输入
```
8
2 1 4
1 1
1 4
1 2
2 2 4
2 4 3
1 2
2 2 7
```
#### 输出
```
1 3 3 7
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心都是模拟题目中的两种操作，但采用了不同的数据结构和方法来优化操作效率。难点在于操作 `2` 中替换所有 $x$ 为 $y$ 的操作，如果直接暴力替换会导致时间复杂度较高。不同题解通过不同思路解决该问题：
- **离线处理思路**：利用离线询问的性质，从后往前处理操作，通过数组记录数字的最终变化，避免了每次操作都遍历数组。
- **数据结构优化思路**：使用 `set`、链表、并查集等数据结构，快速定位和合并相同值的元素，减少操作时间复杂度。

### 所选题解
- **作者：sszcdjr（5星）**
    - **关键亮点**：思路清晰，利用离线询问的性质，从后往前处理操作，通过一个数组 `bel` 记录数字的最终变化，时间和空间复杂度均为 $O(q)$，代码简洁易懂。
- **作者：cmaths（4星）**
    - **关键亮点**：采用 `set` 数据结构，在值域上建立 `set` 来快速查询给定数值的所有下标，并使用启发式合并保证复杂度，时间复杂度为 $O(n\log n)$。
- **作者：cff_0102（4星）**
    - **关键亮点**：同样是逆序操作的思路，通过数组 `b` 记录数字的最终变化，逻辑清晰，代码实现简单。

### 重点代码
#### sszcdjr 的代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int bel[500005];
int a[500005];
int opt[500005],x[500005],y[500005];
signed main(){
    int q;
    cin>>q;
    for(int i=1;i<=500000;i++){
        bel[i]=i;
    }
    for(int i=1;i<=q;i++){
        cin>>opt[i];
        if(opt[i]==1){
            cin>>x[i];
        }
        else{
            cin>>x[i]>>y[i];
        }
    }
    int k=0;
    for(int i=q;i>=1;i--){
        if(opt[i]==1){
            k++;
            a[k]=bel[x[i]];
        }
        else{
            bel[x[i]]=bel[y[i]];
        }
    }
    for(int i=k;i>=1;i--){
        cout<<a[i]<<" ";
    }
    return 0;
}
```
**核心思想**：从后往前处理操作，`bel` 数组记录每个数字最终变成的数字，遇到操作 `1` 直接将 `bel[x]` 加入结果数组，遇到操作 `2` 将 `bel[x]` 改成 `bel[y]`。

#### cmaths 的代码
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

const int N = 500000, A = 500000;
set <int> s[A + 5];
int a[N + 5];

int cnt = 0;
void solve()
{
    int op;
    scanf("%d", &op);
    if(op == 1)
    {
        int x;
        scanf("%d", &x);
        cnt++;
        s[x].insert(cnt);
    }
    else
    {
        int x, y;
        scanf("%d %d", &x, &y);
        if(x == y)
        {
            return;
        }
        if(s[x].size() > s[y].size())
        {
            swap(s[x], s[y]);
        }
        s[y].insert(s[x].begin(), s[x].end());
        s[x].clear();
    }
}

void out()
{
    for(int i = 1; i <= A; i++)
    {
        while(s[i].size())
        {
            int x = *s[i].begin();
            s[i].erase(s[i].begin());
            a[x] = i;
        }
    }
    for(int i = 1; i <= cnt; i++)
    {
        printf("%d ", a[i]);
    }
}

int main()
{
    int qq;
    scanf("%d", &qq);
    while(qq--)
    {
        solve();
    }
    out();
    return 0;
}
```
**核心思想**：在值域上建立 `set`，操作 `1` 在对应 `set` 中添加下标，操作 `2` 合并两个 `set`，使用启发式合并保证复杂度，最后根据 `set` 中的下标赋值得到结果数组。

#### cff_0102 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[500005],x[500005],y[500005];// 记录操作 
int s[500005],b[500005];
int main(){
    ios::sync_with_stdio(false);
    int q;cin>>q;// 操作次数
    for(int i=0;i<q;i++){
        cin>>c[i]>>x[i];
        if(c[i]==2)cin>>y[i];
    }// 输入并存储操作
    int l=0;// 表示最终数组的长度 
    for(int i=0;i<500005;i++)b[i]=i;// 预处理 b 数组，表示没有操作时数字 i 最终还是数字 i 
    for(int i=q-1;i>=0;i--){// 逆序处理 
        if(c[i]==1){
            // a 数组中插入了 x[i]，所以在 s 数组中插入 b[x[i]] 
            s[l++]=b[x[i]];
        }else{
            // 将 b[x] 赋值为 b[y]，原因见上面解析
            b[x[i]]=b[y[i]];
        }
    }
    for(int i=l-1;i>=0;i--){
        cout<<s[i]<<" ";// 逆序输出最终的答案 
    }
    return 0;
}
```
**核心思想**：逆序处理操作，`b` 数组记录数字的最终变化，遇到操作 `1` 将 `b[x]` 加入结果数组，遇到操作 `2` 将 `b[x]` 赋值为 `b[y]`。

### 最优关键思路或技巧
- **离线处理**：利用离线询问的性质，从后往前处理操作，避免了每次操作都遍历数组，降低了时间复杂度。
- **数据结构优化**：使用 `set`、链表、并查集等数据结构，快速定位和合并相同值的元素，提高操作效率。

### 拓展思路
同类型题目可能会有更多复杂的操作或条件，但核心思路仍然是模拟操作过程，并通过合适的数据结构和算法优化来提高效率。类似的算法套路包括离线处理、利用数据结构优化查找和合并操作等。

### 推荐题目
- [P1160 队列安排](https://www.luogu.com.cn/problem/P1160)
- [P1551 亲戚](https://www.luogu.com.cn/problem/P1551)
- [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)

### 个人心得摘录与总结
- **sszcdjr**：给出了一系列代码检查的注意事项，提醒要注意整数溢出、循环边界、精度、特殊情况、初始化等问题，在编写代码时要保持代码简洁，遇到问题可以逐步排查。 

---
处理用时：63.42秒