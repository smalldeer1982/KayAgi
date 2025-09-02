# 题目信息

# 「NnOI R2-T3」Horizon Blue

## 题目描述

小 C 喜欢在画板上画画。他进行了 $ n $ 次操作，每次操作有如下三种可能：

- ```1 k b``` 代表小 C 绘制了一条解析式为 $ y=kx+b $ 的直线。
- ```2 k b``` 代表小 C 询问你直线 $ y=kx+b $ 与多少条被绘制的直线有**恰好**一个公共点。
- ```3 k b``` 代表小 C 擦除所有与直线 $ y=kx+b $ 有**至少**一个公共点的直线。

**注意：两条重合的直线有无数个交点。**

**注意：询问时重合的直线应分别计算。**

## 说明/提示

**【样例 1 解释】**

第 1 次操作，绘制直线 $ y=x $。

第 2 次操作，绘制直线 $ y=-x $。

第 3 次操作，可以发现直线 $ y=2x+1 $ 与前两条线相交。

第 4 次操作，擦掉所有 $ y=x+3 $ 相交的线，直线 $ y=-x $ 被擦掉。

第 5 次操作，$ y=2x+1 $ 显然与 $ y=x $ 相交。

第 6 次操作，$ y=x+1 $ 与 $ y=x $ 斜率相等，是平行线，不相交。

**【数据范围】**

对于 $ 100\% $ 的数据，$ 1 \le n \le 10^5 $，$ 1 \le |k| \le 10^5 $，$ 0 \le |b| \le 10^5 $。

**提示：本题开启捆绑测试。**

$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c}
\textbf{Subtask} & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1& n \le 5000 & 27 \r
\textsf2& \vert k\vert,\vert b\vert \le 50 & 21 \r
\textsf3& 无第\ 3\ 类操作 & 13 \r
\textsf4& 第\ i\ 次操作满足\ k=i & 14 \r
\textsf5& 无特殊限制 & 25 \r
\end{array}
$$

在赛后新添加的 hack 测试点将放入 subtask 6。

### 题目来源

| 项目 | 人员 |
|:-:|:-:|
| idea | 船酱魔王 |
| data | 船酱魔王 |
| check | EstasTonne |
| solution | 船酱魔王 |

## 样例 #1

### 输入

```
6
1 1 0
1 -1 0
2 2 1
3 1 3
2 2 1
2 1 1```

### 输出

```
2
1
0```

## 样例 #2

### 输入

```
10
1 1 0
1 1 0
2 1 1
2 1 0
2 2 5
3 1 0
2 2 5
1 2 3
1 3 4
2 3 5```

### 输出

```
0
0
2
0
1```

# AI分析结果

### 综合分析与结论
这些题解主要围绕如何高效实现题目中的三种操作展开。核心思路基于直线相交的数学性质：两直线斜率 \( k \) 不同则恰有一个交点；斜率 \( k \) 不同或斜率 \( k \) 与截距 \( b \) 都相同则至少有一个交点。

算法要点在于选择合适的数据结构来维护直线信息，如使用 `map`、`multiset`、`set` 等 STL 容器。解决难点主要体现在操作三的实现上，即如何高效删除满足条件的直线，部分题解通过延迟删除、避免频繁清空数据结构等方式优化。

整体来看，多数题解思路清晰，但在代码可读性和优化程度上有所差异。

### 所选的题解
- **作者：NaN_HQJ2007_NaN (5星)**
    - **关键亮点**：思路清晰简洁，利用 `set` 存储不同的 \( k \)，每个 \( k \) 对应一个 `multiset` 存储 \( b \)，操作实现高效直观，复杂度分析准确。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,nn=1e5;
multiset<int>st[N];
set<int>s;
vector<int>t;
int n;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n;
    int tot=0;
    for(int i=1;i<=n;++i){
        int op,k,b;cin>>op>>k>>b;
        if(op==1)st[k+nn].insert(b),s.insert(k+nn),++tot;
        else if(op==2)cout<<tot-st[k+nn].size()<<endl;
        else{
            set<int>::iterator it;t.clear();
            for(it=s.begin();it!=s.end();++it){
                int w=(*it);if(w==k+nn)continue;
                tot-=st[w].size();st[w].clear();t.push_back(w);
            }
            for(int i=0;i<t.size();++i)s.erase(t[i]);
            tot-=st[k+nn].count(b);st[k+nn].erase(b);
        }
    }
    return 0;
}
```
    - **核心实现思想**：操作1插入直线时，更新 `set` 和 `multiset` 并增加直线总数；操作2输出直线总数减去同斜率直线数量；操作3遍历 `set` 清空不同斜率直线，再删除重合直线并更新总数。

- **作者：DengDuck (4星)**
    - **关键亮点**：对操作分析透彻，使用 `map` 统计斜率为 \( k \) 的线段数量，用 `map` 数组维护不同斜率下 \( b \) 的出现次数，通过集合 \( d \) 巧妙处理操作三的删除，代码简洁明了。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=1e5;
map<LL,LL>ma[N*2+5];
map<LL,LL>m;
set<LL>d;
LL n,op,k,b,cnt;
int main()
{
    cin>>n;
    for(int i=-N;i<=N;i++)d.insert(i);
    while(n--)
    {
        cin>>op>>k>>b;
        if(!d.count(k))
        {
            ma[k+N].clear();
            d.insert(k);
        }
        if(op==1)
        {
            m[k]++;
            ma[k+N][b]++;
            cnt++;
        }
        else if(op==2)
        {
            cout<<cnt-m[k]<<endl;
        }
        else 
        {
            LL t=m[k];
            m.clear();
            d.clear();
            m[k]=t-ma[k+N][b];
            ma[k+N][b]=0;
            cnt=m[k];
            d.insert(k);
        }
    }
}
```
    - **核心实现思想**：操作1插入直线时更新两个 `map` 和直线总数；操作2输出直线总数减去同斜率直线数；操作3清空相关 `map` 和集合，重新设置斜率为 \( k \) 的直线数量及相关信息。

- **作者：_wsq_ (4星)**
    - **关键亮点**：将操作转化为对有序数对的操作，使用 `map` 套 `multiset` 的数据结构，清晰实现各操作，代码逻辑清晰，对操作的处理直接明了。
    - **重点代码**：
```cpp
#include <iostream>
#include <set>
#include <map>
using namespace std;
int main(){
    int n,size=0;
    map<int,multiset<int> > m;
    cin>>n;
    for(int i=1;i<=n;i++){
        int op,k,b;
        cin>>op>>k>>b;
        if(op==1){
            if(m.count(k)){
                m[k].insert(b);
            }
            else{
                multiset<int> s;
                s.insert(b);
                m[k]=s;
            }
            size++;
        }
        else{
            if(op==2){
                if(m.count(k)){
                    cout<<size-m[k].size()<<endl;
                }
                else{
                    cout<<size<<endl;
                }
            }
            else{
                for(map<int,multiset<int> >::iterator it=m.begin();it!=m.end();){
                    if(it->first==k){
                        size-=it->second.size();
                        it->second.erase(b);
                        size+=it->second.size();
                        it++;
                    }
                    else{
                        size-=it->second.size();
                        m.erase(it++);
                    }
                }
            }
        }
    }
    return 0;
}
```
    - **核心实现思想**：操作1插入直线时，根据 \( k \) 是否存在决定在 `multiset` 插入或新建 `multiset` 并插入 \( b \)，更新直线总数；操作2根据 \( k \) 是否存在输出直线总数减去同斜率直线数量；操作3遍历 `map`，对同斜率直线处理重合情况，对不同斜率直线直接删除并更新总数。

### 最优关键思路或技巧
- **数据结构选择**：使用 `map` 或 `set` 存储不同斜率 \( k \)，用 `multiset` 或 `map` 存储每个斜率对应的截距 \( b \)，方便统计和删除操作。如 `map<int, multiset<int>>` 结构，外层 `map` 以斜率 \( k \) 为键，内层 `multiset` 存储截距 \( b \)，能高效实现对直线信息的维护。
- **操作优化**：对于操作三的删除，部分题解通过避免频繁清空数据结构，采用延迟删除或标记删除等方式优化。如记录每个斜率是否需要清空，在实际使用时再进行处理，减少不必要的操作。

### 可拓展之处
此类题目属于模拟与数据结构结合的题型，类似套路可应用于需要动态维护集合元素关系，并进行插入、查询、删除操作的场景。例如在几何图形关系判断、事件调度等问题中，通过合适的数据结构选择和操作优化来解决问题。

### 相似知识点洛谷题目
- **P3370 【模板】字符串哈希**：涉及字符串处理和哈希表的应用，与本题类似在于需选择合适数据结构存储和查询信息。
- **P2376 [USACO09OCT]津贴Allowance**：通过合理的数据结构和算法优化实现动态维护和查询，与本题在操作实现和优化思路上有相似处。
- **P1447 [NOI2010] 能量采集**：结合数学知识和数据结构，与本题类似在于利用数据结构维护信息以解决问题。

### 个人心得摘录与总结
- **作者：NASFsky**：考场解题过程中，从最初错误理解题意只考虑斜率判断交点，到发现重合直线的特殊情况，增加对 \( k,b \) 相同直线个数的维护，体现了仔细读题和修正思路的重要性。之后针对 `map` 时间复杂度高的问题，通过替换数据结构和增加特殊判断优化代码，反映出对数据结构性能的理解和优化能力的提升。 

---
处理用时：83.73秒