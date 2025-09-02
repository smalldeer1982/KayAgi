# 题目信息

# MEX and Increments

## 题目描述

Dmitry has an array of $ n $ non-negative integers $ a_1, a_2, \dots, a_n $ .

In one operation, Dmitry can choose any index $ j $ ( $ 1 \le j \le n $ ) and increase the value of the element $ a_j $ by $ 1 $ . He can choose the same index $ j $ multiple times.

For each $ i $ from $ 0 $ to $ n $ , determine whether Dmitry can make the $ \mathrm{MEX} $ of the array equal to exactly $ i $ . If it is possible, then determine the minimum number of operations to do it.

The $ \mathrm{MEX} $ of the array is equal to the minimum non-negative integer that is not in the array. For example, the $ \mathrm{MEX} $ of the array $ [3, 1, 0] $ is equal to $ 2 $ , and the array $ [3, 3, 1, 4] $ is equal to $ 0 $ .

## 说明/提示

In the first set of example inputs, $ n=3 $ :

- to get $ \mathrm{MEX}=0 $ , it is enough to perform one increment: $ a_1 $ ++;
- to get $ \mathrm{MEX}=1 $ , it is enough to perform one increment: $ a_2 $ ++;
- $ \mathrm{MEX}=2 $ for a given array, so there is no need to perform increments;
- it is impossible to get $ \mathrm{MEX}=3 $ by performing increments.

## 样例 #1

### 输入

```
5
3
0 1 3
7
0 1 2 3 4 3 2
4
3 0 0 0
7
4 6 2 3 5 0 5
5
4 0 1 0 4```

### 输出

```
1 1 0 -1 
1 1 2 2 1 0 2 6 
3 0 1 4 3 
1 0 -1 -1 -1 -1 -1 -1 
2 1 0 2 -1 -1```

# AI分析结果

### 题目中文重写
# MEX 和增量

## 题目描述
德米特里有一个包含 $ n $ 个非负整数的数组 $ a_1, a_2, \dots, a_n $。

在一次操作中，德米特里可以选择任意一个索引 $ j $（$ 1 \le j \le n $），并将元素 $ a_j $ 的值加 $ 1 $。他可以多次选择同一个索引 $ j $。

对于从 $ 0 $ 到 $ n $ 的每个 $ i $，判断德米特里是否可以使数组的 $ \mathrm{MEX} $ 恰好等于 $ i $。如果可以，那么求出实现这一目标所需的最少操作次数。

数组的 $ \mathrm{MEX} $ 等于数组中未出现的最小非负整数。例如，数组 $ [3, 1, 0] $ 的 $ \mathrm{MEX} $ 等于 $ 2 $，数组 $ [3, 3, 1, 4] $ 的 $ \mathrm{MEX} $ 等于 $ 0 $。

## 说明/提示
在第一组示例输入中，$ n = 3 $：
- 要使 $ \mathrm{MEX} = 0 $，只需执行一次增量操作：$ a_1 $ 加 $ 1 $；
- 要使 $ \mathrm{MEX} = 1 $，只需执行一次增量操作：$ a_2 $ 加 $ 1 $；
- 给定数组的 $ \mathrm{MEX} = 2 $，因此无需执行增量操作；
- 无法通过执行增量操作使 $ \mathrm{MEX} = 3 $。

## 样例 #1
### 输入
```
5
3
0 1 3
7
0 1 2 3 4 3 2
4
3 0 0 0
7
4 6 2 3 5 0 5
5
4 0 1 0 4
```

### 输出
```
1 1 0 -1 
1 1 2 2 1 0 2 6 
3 0 1 4 3 
1 0 -1 -1 -1 -1 -1 -1 
2 1 0 2 -1 -1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是围绕让数组的 MEX 值等于 $i$ 展开，要满足 $0$ 到 $i - 1$ 均在数组中出现且 $i$ 不在数组中出现这两个条件。为了满足第一个条件，利用栈来维护可操作的数，优先选择最大但不超过 $i - 1$ 且之前未使用过的数进行操作，以保证操作次数最少，这体现了贪心的思想。同时，利用“若某个 $i$ 无法满足条件，则 $i + 1$ 到 $n$ 都无法满足条件”这一性质来提前终止后续计算。

### 所选题解
- **Otomachi_Una_（5星）**
    - **关键亮点**：思路清晰，代码简洁易懂，详细阐述了利用栈维护可操作数的过程，且注释明确。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
#define ll long long
const int MAXN=2e5+5;
int t,n;
int a[MAXN],cnt[MAXN];
int st[MAXN],tail=0;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            cnt[a[i]]++;
        }
        cout<<cnt[0]<<" ";
        ll ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=cnt[i-1];j++)
                st[++tail]=i-1;
            if(tail==0){
                for(int j=1;j<=n-i+1;j++)
                    cout<<"-1 ";
                break;
            }
            else{
                ans+=(i-1-st[tail--]);
                cout<<ans+cnt[i]<<" ";
            }
        }
        for(int i=1;i<=n;i++)
            cnt[a[i]]=0;
        cout<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：先统计每个数的出现次数，对于 $i = 0$，答案就是 $0$ 的出现次数。从 $i = 1$ 开始，将值为 $i - 1$ 的元素加入栈中，若栈为空则后续答案都为 $-1$，否则取出栈首元素，计算将其操作到 $i - 1$ 的代价，再加上 $i$ 的出现次数作为当前答案。

- **Ericby666（4星）**
    - **关键亮点**：思路明确，使用标准库的栈结构，代码规范，对满足两个条件的操作解释清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,x,cnt[200005],ans;
stack<int>q;//使用栈维护
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        memset(cnt,0,sizeof cnt);
        ans=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>x;
            cnt[x]++;
        }
        cout<<cnt[0]<<' ';
        for(int i=1;i<=n;i++){
            for(int j=1;j<=cnt[i-1];j++)q.push(i-1);
            if(q.empty()){
                for(int j=1;j<=n-i+1;j++)cout<<"-1 ";//后面全无法满足要求
                break;
            }
            else{
                ans+=(i-1)-q.top();//转换的代价
                q.pop();
                cout<<ans+cnt[i]<<' ';//最终答案
            }
        }
        cout<<'\n';
    }
    return 0;
}
```
    - **核心实现思想**：与 Otomachi_Una_ 的思路类似，只是使用了标准库的栈。先统计每个数的出现次数，对于 $i = 0$ 输出 $0$ 的出现次数，从 $i = 1$ 开始，将值为 $i - 1$ 的元素压入栈，若栈为空则后续输出 $-1$，否则计算操作代价并输出答案。

### 最优关键思路或技巧
- **贪心策略**：每次选择最大但不超过 $i - 1$ 且之前未使用过的数进行操作，保证操作次数最少。
- **栈的使用**：用栈来维护可操作的数，方便取出和管理。
- **性质利用**：利用“若某个 $i$ 无法满足条件，则 $i + 1$ 到 $n$ 都无法满足条件”的性质提前终止计算，提高效率。

### 拓展思路
同类型题目可能会改变操作规则，如每次操作可以选择一个区间的数加 $1$，或者改变 MEX 的定义，如改为数组中未出现的最小正整数等。类似算法套路可以应用在需要满足一定条件并求最小操作次数的问题中，通过贪心策略和合适的数据结构来优化求解过程。

### 推荐洛谷题目
1. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)：考察贪心算法在区间问题中的应用。
2. [P2240 【深基12.例1】部分背包问题](https://www.luogu.com.cn/problem/P2240)：经典的贪心问题，与本题的贪心思想有相似之处。
3. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：通过合理分组来达到最优解，体现了贪心的思想。

### 个人心得
部分题解提到要开 `long long`，否则第 4 个点会 WA，这提示我们在处理可能出现较大数值的题目时，要注意数据类型的选择，避免因数据溢出导致错误。 

---
处理用时：52.64秒