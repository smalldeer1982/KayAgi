# 题目信息

# [USACO23DEC] Bovine Acrobatics S

## 题目描述

Farmer John 决定让他的奶牛表演杂技！首先，FJ 为他的奶牛称重，发现她们有 $N$（$1\le N\le 2\times 10^5$）个不同的体重。具体来说，对于全部的 $i\in [1,N]$，有 $a_i$ 只奶牛的体重为 $w_i$ 单位（$1\le a_i\le 10^9, 1\le w_i\le 10^9$）。

他最出名的节目需要奶牛叠成**平衡的奶牛塔**。一座**奶牛塔**是一些奶牛，每只奶牛站在下一只奶牛身上。一座奶牛塔是**平衡的**，当且仅当每一只被踩着的奶牛，都比**直接**踩在它身上的那只奶牛重至少 $K$（$1\le K\le 10^9$）单位。每只奶牛都可以成为奶牛塔的一部分。

如果 FJ 想要创造最多 $M$（$1 \le M \le 10^9$）座奶牛塔，最多有多少只奶牛可以成为奶牛塔的一部分？

## 说明/提示

### 样例解释 1

FJ 可以用体重为 $5,7,9$ 的奶牛创造四座平衡的奶牛塔，再用体重为 $5,7$ 的奶牛创造另一座。

### 样例解释 2

FJ 可以用体重为 $5,9$ 的奶牛创造四座平衡的奶牛塔，再用体重为 $7$ 的一只奶牛创造另一座。或者，他可以用体重为 $5,9$ 的奶牛创造四座平衡的奶牛塔，再用体重为 $5$ 的一只奶牛创造另一座。

### 测试点性质

- 测试点 $3-5$ 满足 $M \le 5000$ 且奶牛的总数不超过 $5000$。
- 测试点 $6-11$ 满足奶牛的总数不超过 $2\cdot 10^5$。
- 测试点 $12-17$ 没有额外限制。


## 样例 #1

### 输入

```
3 5 2
9 4
7 6
5 5```

### 输出

```
14```

## 样例 #2

### 输入

```
3 5 3
5 5
7 6
9 4```

### 输出

```
9```

# AI分析结果

• 综合分析与结论：这些题解都基于贪心策略，核心思路是按奶牛体重排序后，从某种顺序（如从小到大或从大到小）遍历奶牛，尽量将奶牛放入满足重量差条件的塔中。算法要点在于如何高效维护可放置奶牛的塔的信息，难点是处理大规模数据时避免时间和空间复杂度过高。各题解采用了不同的数据结构和优化方法，如双指针、小根堆、单调队列、离散化等。

所选的题解：
  - **作者：Little_x_starTYJ (5星)**
    - **关键亮点**：思路清晰，先明确贪心策略，即最重奶牛放底层，按重量排序后依次放置奶牛。通过双指针维护可放置奶牛的塔数，代码简洁高效。
    - **重点代码**：
```c
#include <stdio.h>
#include <algorithm>
struct node {
    int a, b;
} c[200010];
bool cmp(node a, node b) {
    return a.b < b.b;
}
int ans[200010], id = 1;
long long res;
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &c[i].b, &c[i].a);
    std::sort(c + 1, c + 1 + n, cmp);
    for (int i = 1; i <= n; i++) {
        while (id < i && c[i].b - c[id].b >= k)
            m += ans[id++];
        ans[i] = m < c[i].a? m : c[i].a;
        m -= ans[i], res += ans[i];
    }
    printf("%lld", res);
    return 0;
}
```
    - **核心实现思想**：先对奶牛按体重排序，遍历奶牛时，用双指针 `id` 维护可放置奶牛的塔数，更新 `m`。计算当前奶牛可放入塔的数量 `ans[i]`，更新答案 `res` 和可放置塔数 `m`。

  - **作者：_qingshu_ (4星)**
    - **关键亮点**：证明了贪心策略的正确性，即无论奶牛正着放还是倒着放不影响答案，且每头牛只要有位置就一定会放。同样采用双指针优化，思路表述清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
struct _qingshu_{
    int a,w;
}c[5200010];
bool cmp(_qingshu_ x,_qingshu_ y){
    return x.w<y.w;
}
int tot=1,qa[5200010];
long long ans;
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        cin>>c[i].w>>c[i].a;
    }
    stable_sort(c+1,c+n+1,cmp);
    for(int i=1;i<=n;i++){
        while(tot<=i-1&&c[i].w-c[tot].w>=k){
            m+=qa[tot++];
        }
        qa[i]=min(m,c[i].a);
        m-=qa[i];
        ans+=qa[i];
    }
    cout<<ans;
}
```
    - **核心实现思想**：与上一题解类似，对奶牛按体重排序后，用双指针 `tot` 维护可放置奶牛的塔数，更新 `m`，计算当前奶牛放入塔的数量 `qa[i]`，更新答案 `ans` 和可放置塔数 `m`。

  - **作者：kczw (4星)**
    - **关键亮点**：详细阐述了贪心思路，包括从大到小或从小到大放置奶牛的等价性，以及对数据范围优化的思考。通过一个变量存储可放置当前奶牛的堆数量，并记录每种牛放置个数来更新可放置位置。
    - **重点代码**：
```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int ans,n,m,k,t,num[200005];
pair<int,int> a[200005];
signed main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i].first,&a[i].second);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        while(t<=i-1&&a[i].first-a[t].first>=k)m+=num[t++];
        num[i]=min(a[i].second,m);
        m-=num[i];
        ans+=num[i];
    }printf("%lld",ans);
    return 0;
}
```
    - **核心实现思想**：对奶牛按体重排序后，用双指针 `t` 维护可放置奶牛的堆数量 `m`，计算当前奶牛放入堆的数量 `num[i]`，更新答案 `ans` 和可放置堆数 `m`。

最优关键思路或技巧：采用贪心策略，按奶牛体重排序，通过双指针维护可放置奶牛的塔（堆）数量，高效解决问题。同时，部分题解利用数据结构如小根堆、单调队列等进一步优化，或通过离散化处理数据范围大的问题。

可拓展之处：此类题目属于贪心策略结合数据结构优化的问题，类似套路可用于解决资源分配、任务调度等场景的题目，关键在于找到合理的贪心策略和合适的数据结构优化方法。

推荐洛谷题目：
  - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
  - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
  - [P1937 [USACO10MAR]Barn Allocation G](https://www.luogu.com.cn/problem/P1937)

个人心得：无。 

---
处理用时：54.27秒