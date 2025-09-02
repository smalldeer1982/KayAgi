# [GCJ Farewell Round #2] Spacious Sets

## 题目描述

**Ada** 和 **John** 是最好的朋友。由于他们感到无聊，**Ada** 让 **John** 为她解决一个谜题。

一个集合 $S$ 被称为 **宽松的**，如果其中任意两个不同元素的绝对差至少为 $\mathbf{K}$，即对于所有 $x, y \in S$ 且 $x \neq y$，都有 $|x - y| \geq \mathbf{K}$。

**Ada** 有一个包含 $\mathbf{N}$ 个不同整数的列表 $\mathbf{A}$ 和一个整数 $\mathbf{K}$。对于每个 $\mathbf{A}_i$，她要求 **John** 找出由 $\mathbf{A}$ 中元素构成的最大尺寸的集合 $S_i$，使得 $S_i$ 包含 $\mathbf{A}_i$ 并且是宽松的。

注意：集合 $S_i$ 不需要由列表中连续的元素构成。

## 说明/提示

**样例解释**

在样例 #1 中，一个宽松集合不能同时包含 1 和 2，也不能同时包含 2 和 3。这意味着 $S_2 = \{2\}$，而使用 $S_1 = S_3 = \{1, 3\}$ 可以使它们的尺寸最大化。

在样例 #2 中，可能的尺寸最大集合为：

* $S_1 = S_2 = S_3 = S_4 = \{2, 7, 11, 19\}$，
* $S_5 = \{11, 19, 5\}$，
* $S_6 = \{7, 11, 19, 3\}$。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。
- 对所有 $i$，$-10^9 \leq \mathbf{A}_i \leq 10^9$。
- 对所有 $i \neq j$，$\mathbf{A}_i \neq \mathbf{A}_j$。

**测试集 1（4 分，可见判定）**
- $1 \leq \mathbf{N} \leq 10$。
- $1 \leq \mathbf{K} \leq 100$。

**测试集 2（10 分，可见判定）**
- $1 \leq \mathbf{K} \leq 10^9$。

对于最多 15 个测试用例：
- $1 \leq \mathbf{N} \leq 10^5$。

对于其余测试用例：
- $1 \leq \mathbf{N} \leq 10^3$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
3 2
1 2 3
6 4
2 7 11 19 5 3```

### 输出

```
Case #1: 2 1 2
Case #2: 4 4 4 4 3 4```

# 题解

## 作者：4041nofoundGeoge (赞：0)

## 题目大意

给定一个序列 $A$，要求选择 $i$ 之前的任意元素，组成一个最长宽松子序列，一个集合的宽松被描述为：对于宽松子序列**任意**元素，若 $i,j∈S,i\not=j$ 且 $|A_i-A_j|≥K$ 我们称为宽松。令你输出 $1\le i\le N$ 中每一个 $i$ 对应最长宽松子序列。

## 思路

首先宽松子序列要求是任意元素，所以我们不妨把元素排序，构成新的数组 $sora_{x,y}$，其中 $x$ 记录原数组 $A_y$ 的值。

设 $left_i$ 为从数组开始到 $sora_{A_{i-1},i-1}$ 的最长宽松子序列长度；$right_i$ 为从 $sora_{A_{i+1},i+1}$ 到数组末尾的最长宽松子序列长度。为了最优解，我们考虑二分，找到最优的左边界 $pos$，并转移：$left_i=left_{pos}+1$。右边界同理，得到 $right_i=right_{pos'}+1$。

最后对于每一个下标 $i$，都有 $Ans_i=left_i+right_i-1$，之所以 $-1$ 是因为 $A_i$ 会被重复计算。

时间复杂度 $O(n\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct N{
    int id,num;
}sora[100005];
bool cmp(N a,N b){
    return a.num<b.num;
}
int a[100005];
int leftt[100005],rightt[100005],res[100005];//left是c++函数！
int main(){
    int t;
    cin>>t;
    int q=t;
    while(t--){
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++)sora[i].id=i,sora[i].num=a[i];
        sort(sora+1,sora+n+1,cmp);
        for(int i=1;i<=n;i++){
            int pos=-1;
            int cur=sora[i].num;
            int l=1,r=i-1;
            while(l<=r){
                int mid=(l+r)/2;
                if(cur-sora[mid].num>=k){
                    pos=mid;
                    l=mid+1;
                }
                else r=mid-1;
            }
            if(pos==-1)leftt[i]=1;
            else leftt[i]=leftt[pos]+1;
        }
        for(int i=n;i>=1;i--){
            int pos=-1;
            int cur=sora[i].num;
            int l=i+1,r=n;
            while(l<=r){
                int mid=(l+r)/2;
                if(sora[mid].num-cur>=k){
                    pos=mid;
                    r=mid-1;
                }
                else l=mid+1;
            }
            if(pos==-1)rightt[i]=1;
            else rightt[i]=rightt[pos]+1;
        }
        for(int i=1;i<=n;i++){
            res[sora[i].id]=leftt[i]+rightt[i]-1;
        }
        cout<<"Case #"<<q-t<<":";
        for(int i=1;i<=n;i++){
            cout<<" "<<res[i];
        }
        cout<<"\n";
    }
    return 0;
}
```

---

