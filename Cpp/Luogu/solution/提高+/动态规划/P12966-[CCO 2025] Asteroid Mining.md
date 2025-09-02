# [CCO 2025] Asteroid Mining

## 题目描述

现在是 2017 年，**Ryan** 是一名小行星矿工。他以开采小行星并在 **CCO**（天体货运前哨站）出售矿物为生。

在最近的一次采矿探险中，他开采了 $N$ 块矿物，其中第 $i$ 块矿物的价值为 $v_i$，质量为 $m_i$。**Ryan** 计划用他的火箭将一组矿物运送到 **CCO**，但他只剩下足够进行一次飞行的燃料。他计算出火箭能够安全携带的最大总质量为 $M$。由于 **Ryan** 的采矿技术，这些矿物具有一个特殊性质：对于任意两块矿物，其中一块的质量可以被另一块的质量整除。

帮助 **Ryan** 在火箭的限制下找到他能运送到 **CCO** 的最大总价值。

## 说明/提示

**样例解释**

**Ryan** 可以携带除第二块和第五块之外的所有矿物，以获得总价值 $1 + 200 + 9 + 100 = 310$。注意，这些矿物的总质量为 $1 + 6 + 2 + 1 = 10$。可以证明这是最优解。

以下表格展示了 25 分的分布情况：

| 分值 | $N$ 的范围 | $M$ 的范围 | 额外约束 |
| :---: | :---: | :---: | :---: |
| 2 分 | $N = 2$ | $1 \leq M \leq 10^4$ | 无 |
| 2 分 | $1 \leq N \leq 20$ | $1 \leq M \leq 10^4$ | 无 |
| 4 分 | $1 \leq N \leq 1000$ | $1 \leq M \leq 10^4$ | 无 |
| 6 分 | $1 \leq N \leq 1000$ | $1 \leq M \leq 10^8$ | 无 |
| 2 分 | $1 \leq N \leq 500000$ | $1 \leq M \leq 10^8$ | 所有 $m_i$ 相等。 |
| 3 分 | $1 \leq N \leq 500000$ | $1 \leq M \leq 10^8$ | 最多 2 种不同的 $m_i$。 |
| 6 分 | $1 \leq N \leq 500000$ | $1 \leq M \leq 10^{12}$ | 无 |

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6 10 
1 1
5 2
200 6
9 2
6 2
100 1```

### 输出

```
310```

# 题解

## 作者：_Ch1F4N_ (赞：1)

好题我懂得欣赏。

首先给所有物品按照重量排序，显然只有 $\log V$ 种不同的重量。

然后考虑最轻的物品，假设重量为 $w$，显然可以 $m \gets \frac{m}{w}$ 然后给所有物品重量除一个 $w$。

这个时候先把目前重量为 $1$ 的物品排序，然后设这个时候次轻的物品重量为 $w_1$。

我们考察最后的方案中，重量为 $1$ 的物品所占的背包重量，一定可以等效地看作 $m \bmod w_1 + k \times w_1$，这是因为其余的物品重量都是 $w_1$ 的倍数，所以其余的物品所占重量一定形如 $l \times w_1$，故有此结论。

那么我们考虑将重量为 $1$ 的物品先选前 $m \bmod w_1$ 大直接加入答案，然后将剩下的排序后每 $w_1$ 个合并为 $1$ 个重量为 $w_1$ 的物品（最后一组可能不够 $w_1$ 个但是视作重量为 $w_1$ 是没有影响的），此时 $w_1$ 变为最轻的重量，重复上述过程即可。

一共 $\log V$ 层，瓶颈在每层的排序，注意到每往后一层物品数量至少减半，故一个物品对每层的大小贡献是 $O(\sum_{i=0}^{\log V} \frac{1}{2^i}) = O(1)$ 的，总时间复杂度 $O(n \log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
const int maxn = 5e5+114;
pair<int,int> a[maxn];
int ans;
vector<int> dp;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i].second;
        cin>>a[i].first;
    }
    sort(a+1,a+n+1);
    m/=a[1].first;
    int now=a[1].first;
    for(int i=1;i<=n;i++){
        if(a[i].first==now){
            dp.push_back(a[i].second);
        }else{
            sort(dp.begin(),dp.end());
            int M=m%(a[i].first/a[i-1].first);
            while(M>0&&dp.size()>0) ans+=dp.back(),dp.pop_back(),M--;
            m/=(a[i].first/a[i-1].first);
            int c=a[i].first/a[i-1].first;
            vector<int> f;
            while(dp.size()>0){
                int s=0;
                for(int j=1;j<=c&&dp.size()>0;j++) s+=dp.back(),dp.pop_back();
                f.push_back(s);
            }
            swap(f,dp);
            dp.push_back(a[i].second);
            now=a[i].first;
        }
    }
    sort(dp.begin(),dp.end());
    while(m>0&&dp.size()>0) ans+=dp.back(),m--,dp.pop_back();
    cout<<ans<<"\n";
    return 0;
}
```

---

