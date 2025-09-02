# The Ultimate Wine Tasting Event

## 题目描述

Gabriella 的品酒会因其卓越品质闻名世界，并登上了知名葡萄酒杂志的头条。如今，她受邀为 EUC 2025 组织一场活动！

本次她挑选了 $2n$ 瓶葡萄酒，其中恰好 $n$ 瓶白葡萄酒和 $n$ 瓶红葡萄酒。她将这些酒瓶按预定顺序排成一行，用一个长度为 $2n$ 的字符串 $s$ 描述排列：对于 $1 \le i \le 2n$，从左数第 $i$ 瓶为白葡萄酒时 $s_i = \texttt{W}$，红葡萄酒时 $s_i = \texttt{R}$。

为增加趣味性（参赛者将参与其中），Gabriella 设计了以下葡萄酒主题问题：

考虑将这 $2n$ 瓶酒划分为两个不相交的子集，每个子集包含 $n$ 瓶。然后，对于每个 $1 \le i \le n$，交换第一个子集（从左数）的第 $i$ 瓶与第二个子集（同样从左数）的第 $i$ 瓶。能否选择这样的子集，使得操作完成后前 $n$ 个位置全为白葡萄酒？


## 说明/提示

第一个测试用例中，可选择位置 $1, 2, 3, 7$ 的瓶子（分别为：白、红、红、红）作为第一个子集，位置 $4, 5, 6, 8$ 的瓶子（分别为：白、白、白、红）作为第二个子集。交换 $(1, 4)$、$(2, 5)$、$(3, 6)$ 和 $(7, 8)$ 后，前 $4$ 个位置全为白葡萄酒。

第二个测试用例中，唯一的划分方式是将第一个瓶子作为第一个子集，第二个瓶子作为第二个子集。交换后排列为 $\texttt{RW}$，因此无解。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
4
WRRWWWRR
1
WR
20
WWWWRRWRRRRRWRRWRWRRWRRWWWWWWWRWWRWWRRRR```

### 输出

```
YES
NO
YES```

# 题解

## 作者：xyvsvg (赞：0)

这个题还是挺多细节的。显然我们尽量要换尽可能靠前的，但同时也需要尽可能“浪费”更多在前 $n$ 个位置的 W。

注意到 $n$ 很小，因此不妨直接枚举第二个集合的第一个元素的位置，然后贪心的换，检查是否存在一种合法方案即可。

复杂度为 $O(n^2)$：


```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    s=' '+s;
    for(int d=1;d<=n;++d)
    {
        vector<bool>vis(n*2+10);
        int j=d;
        for(int i=1;i<=n;++i)
        {
            if(vis[i])
                continue;
            if(s[i]=='R')
                j=max(j,n);
            vis[i]=1;
            for(++j;(s[j]=='R'||vis[j])&&j<=2*n;++j);
            if(j>2*n)
                goto ed1;
            vis[j]=1;
        }
        for(int i=n+1;i<=n*2;++i)
        {
            if(vis[i])
                continue;
            for(++j;vis[j]&&j<=2*n;++j);
            if(j>2*n)
                goto ed1;
            vis[j]=1;
        }
        cout<<"YES"<<endl;
        return;
        ed1:;
    }
    cout<<"NO"<<endl;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
        solve();
    return 0;
}

```

---

