# 题目信息

# Even-Odd Increments

## 题目描述

You are given $ n $ of integers $ a_1, a_2, \ldots, a_n $ . Process $ q $ queries of two types:

- query of the form "0 $ x_j $ ": add the value $ x_j $ to all even elements of the array $ a $ ,
- query of the form "1 $ x_j $ ": add the value $ x_j $ to all odd elements of the array $ a $ .

Note that when processing the query, we look specifically at the odd/even value of $ a_i $ , not its index.

After processing each query, print the sum of the elements of the array $ a $ .

Please note that the answer for some test cases won't fit into 32-bit integer type, so you should use at least 64-bit integer type in your programming language (like long long for C++).

## 说明/提示

In the first test case, the array $ a = [2] $ after the first query.

In the third test case, the array $ a $ is modified as follows: $ [1, 3, 2, 4, 10, 48] $ $ \rightarrow $ $ [7, 9, 2, 4, 10, 48] $ $ \rightarrow $ $ [7, 9, 7, 9, 15, 53] $ $ \rightarrow $ $ [7, 9, 7, 9, 15, 53] $ $ \rightarrow $ $ [10, 12, 10, 12, 18, 56] $ $ \rightarrow $ $ [22, 24, 22, 24, 30, 68] $ $ \rightarrow $ $ [23, 25, 23, 25, 31, 69] $ .

## 样例 #1

### 输入

```
4
1 1
1
1 1
3 3
1 2 4
0 2
1 3
0 5
6 7
1 3 2 4 10 48
1 6
0 5
0 4
0 5
1 3
0 12
0 1
6 7
1000000000 1000000000 1000000000 11 15 17
0 17
1 10000
1 51
0 92
0 53
1 16
0 1```

### 输出

```
2
11
14
29
80
100
100
100
118
190
196
3000000094
3000060094
3000060400
3000060952
3000061270
3000061366
3000061366```

# AI分析结果

### 题目中文重写
# 奇偶增量

## 题目描述
给定 $n$ 个整数 $a_1, a_2, \ldots, a_n$。处理 $q$ 个两种类型的查询：
- 类型为 “0 $x_j$” 的查询：将值 $x_j$ 加到数组 $a$ 中所有偶数元素上。
- 类型为 “1 $x_j$” 的查询：将值 $x_j$ 加到数组 $a$ 中所有奇数元素上。

请注意，在处理查询时，我们特别关注的是 $a_i$ 的奇偶值，而不是其索引。

在处理完每个查询后，打印数组 $a$ 中元素的总和。

请注意，某些测试用例的答案可能无法用 32 位整数类型表示，因此在你的编程语言中应至少使用 64 位整数类型（如 C++ 中的 `long long`）。

## 说明/提示
在第一个测试用例中，经过第一次查询后，数组 $a = [2]$。

在第三个测试用例中，数组 $a$ 按如下方式修改：$ [1, 3, 2, 4, 10, 48] \rightarrow [7, 9, 2, 4, 10, 48] \rightarrow [7, 9, 7, 9, 15, 53] \rightarrow [7, 9, 7, 9, 15, 53] \rightarrow [10, 12, 10, 12, 18, 56] \rightarrow [22, 24, 22, 24, 30, 68] \rightarrow [23, 25, 23, 25, 31, 69] $。

## 样例 #1
### 输入
```
4
1 1
1
1 1
3 3
1 2 4
0 2
1 3
0 5
6 7
1 3 2 4 10 48
1 6
0 5
0 4
0 5
1 3
0 12
0 1
6 7
1000000000 1000000000 1000000000 11 15 17
0 17
1 10000
1 51
0 92
0 53
1 16
0 1
```

### 输出
```
2
11
14
29
80
100
100
100
118
190
196
3000000094
3000060094
3000060400
3000060952
3000061270
3000061366
3000061366
```

### 题解综合分析与结论
- **思路对比**：所有题解思路基本一致，都是先统计数组中奇数和偶数的个数以及数组的初始总和，然后根据查询类型和加数的奇偶性更新总和与奇偶个数。
- **算法要点**：
    - 统计初始的奇数个数、偶数个数和数组总和。
    - 根据查询类型（0 或 1），将总和加上对应奇偶个数乘以加数。
    - 若加数为奇数，更新奇偶个数。
- **解决难点**：关键在于处理加数为奇数时奇偶性的变化，这会导致奇数和偶数的个数发生改变。

### 各题解评分
| 作者 | 评分 | 理由 |
| ---- | ---- | ---- |
| 深度产业观察 | 4星 | 思路清晰，代码简洁易懂，注释较少但不影响理解。 |
| _Haoomff_ | 4星 | 思路详细，有前置知识说明，代码规范，有输入输出优化。 |
| ice_fish01 | 3星 | 思路分析详细，但代码中部分注释可更简洁，整体结构稍显冗余。 |
| _JF_ | 3星 | 思路明确，代码简洁，但注释较少。 |
| Marshall001 | 3星 | 思路清晰，代码简洁，但解释相对简略。 |
| Larryyu | 3星 | 有自定义输入函数，代码稍复杂，注释较少。 |
| xiezheyuan | 3星 | 思路巧妙，但代码注释较少。 |
| 隐仞Mrsu | 3星 | 思路正确，代码结构清晰，但注释较少。 |
| Allanljx | 3星 | 思路清晰，代码简洁，但注释较少。 |
| XiaoQuQu | 3星 | 思路正确，代码有一定结构，但注释较少。 |

### 所选题解
- **深度产业观察（4星）**
    - **关键亮点**：思路清晰，代码简洁直接，能快速实现功能。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,q,a,b,s[1000000],js,os,cnt;
int main(){
    cin>>t;
    for(int g=1;g<=t;g++){
        cin>>n>>q;
        for(int i=1;i<=n;i++){
            cin>>s[i];
            if(s[i]%2==0)
                os++;
            else
                js++;
            cnt+=s[i];
        }
        for(int i=1;i<=q;i++){
            cin>>a>>b;
            if(a==0){
                cnt+=os*b;
                if(b%2!=0){
                    js+=os;
                    os=0;
                }
            }
            else{
                cnt+=js*b;
                if(b%2!=0){
                    os+=js;
                    js=0;
                }
            }
            cout<<cnt<<endl;
        }
        cnt=0;
        js=os=0;
        for(int i=1;i<=n;i++)
            s[i]=0;
    }
    return 0;
} 
```
- **_Haoomff_（4星）**
    - **关键亮点**：思路详细，有前置知识说明，代码规范，使用输入输出优化。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstring>
#define ll long long
using namespace std;
ll t,n,q,a[100005];
ll js;//奇数个数 
ll os;//偶数个数 
ll ans;//数组和 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    for(;t--;){
        js=os=ans=0;//初始化 
        cin>>n>>q;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            if(a[i]%2==0)++os;
            else ++js;
            ans+=a[i];//求出整个数组的和 
        }
        for(int i=1;i<=q;++i){
            int x,y;
            cin>>x>>y;
            if(x==0){
                ans+=os*y;
                if(y%2==1){//奇数+偶数=奇数，所以偶数全部变为奇数
                    js+=os;
                    os=0;
                }
            }
            else if(x==1){
                ans+=js*y;
                if(y%2==1){//奇数+奇数=偶数，所以奇数全部变为偶数 
                    os+=js;
                    js=0;
                } 
            }
            cout<<ans<<"\n";
        }
    }
    return 0;
}
```

### 最优关键思路与技巧
- 避免暴力遍历，通过统计奇数和偶数的个数来快速计算总和的变化，时间复杂度从 $O(nq)$ 优化到 $O(q)$。
- 利用奇偶性的运算规则（奇数 + 奇数 = 偶数，奇数 + 偶数 = 奇数，偶数 + 偶数 = 偶数），在加数为奇数时快速更新奇偶个数。

### 拓展思路
同类型题可能会改变操作规则，如对不同余数类别的数进行操作，或者改变查询类型。类似算法套路是通过预处理和记录关键信息（如本题的奇偶个数），避免重复计算，从而优化时间复杂度。

### 推荐洛谷题目
1. [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：涉及奇偶性判断和简单的状态改变。
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：需要对区间进行操作，可类比本题的操作思想。
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：需要对数据进行处理和统计，与本题统计奇偶个数类似。

### 个人心得摘录与总结
- ice_fish01：一开始想用遍历的方法做，但发现数据范围太大，遍历会超时，从而醒悟需要换思路。总结：做题时要先看数据范围，避免使用会超时的算法。
- 隐仞Mrsu：写题时把操作对象错看成奇数序号的元素和偶数序号的元素。总结：读题要仔细，明确题目要求。 

---
处理用时：50.67秒