# 题目信息

# Elimination of a Ring

## 题目描述

Define a cyclic sequence of size $ n $ as an array $ s $ of length $ n $ , in which $ s_n $ is adjacent to $ s_1 $ .

Muxii has a ring represented by a cyclic sequence $ a $ of size $ n $ .

However, the ring itself hates equal adjacent elements. So if two adjacent elements in the sequence are equal at any time, one of them will be erased immediately. The sequence doesn't contain equal adjacent elements initially.

Muxii can perform the following operation until the sequence becomes empty:

- Choose an element in $ a $ and erase it.

For example, if ring is $ [1, 2, 4, 2, 3, 2] $ , and Muxii erases element $ 4 $ , then ring would erase one of the elements equal to $ 2 $ , and the ring will become $ [1, 2, 3, 2] $ .

Muxii wants to find the maximum number of operations he could perform.

Note that in a ring of size $ 1 $ , its only element isn't considered adjacent to itself (so it's not immediately erased).

## 说明/提示

In the first test case, you can erase the second element first, then erase the remaining elements one by one in any order. In total, you can perform the operation $ 4 $ times. Note that if you erase the first element first, then the sequence will be turned into $ [2,3,2] $ and then immediately become $ [2,3] $ .

In the second test case, you can erase the first element first, then the sequence becomes $ [2,1] $ . Then you can erase all remaining elements one by one in any order.

## 样例 #1

### 输入

```
3
4
1 2 3 2
4
1 2 1 2
1
1```

### 输出

```
4
3
1```

# AI分析结果

### 题目内容
# 环的消除

## 题目描述
定义一个长度为 $n$ 的循环序列为一个长度为 $n$ 的数组 $s$，其中 $s_n$ 与 $s_1$ 相邻。

Muxii 有一个由长度为 $n$ 的循环序列 $a$ 表示的环。

然而，这个环本身不喜欢相邻元素相等。所以在任何时候，如果序列中两个相邻元素相等，其中一个将立即被删除。序列初始时不包含相邻相等的元素。

Muxii 可以执行以下操作，直到序列为空：
- 从 $a$ 中选择一个元素并删除它。

例如，如果环为 $[1, 2, 4, 2, 3, 2]$，Muxii 删除元素 $4$，那么环会删除其中一个等于 $2$ 的元素，环将变为 $[1, 2, 3, 2]$。

Muxii 想找到他可以执行的最大操作次数。

注意，在长度为 $1$ 的环中，其唯一的元素不被认为与自身相邻（所以不会立即被删除）。

## 说明/提示
在第一个测试用例中，你可以先删除第二个元素，然后按任意顺序逐个删除剩余元素。总共，你可以执行操作 $4$ 次。注意，如果你先删除第一个元素，那么序列将变为 $[2,3,2]$，然后立即变为 $[2,3]$。

在第二个测试用例中，你可以先删除第一个元素，然后序列变为 $[2,1]$。然后你可以按任意顺序逐个删除剩余元素。

## 样例 #1
### 输入
```
3
4
1 2 3 2
4
1 2 1 2
1
1
```
### 输出
```
4
3
1
```

### 算法分类
数学

### 综合分析与结论
这几道题解的核心思路都是通过分析环中元素种类数量来确定最大操作次数。当环中元素种类大于2种时，总能通过合理选择删除元素，使得每次删除操作后不会引发相邻元素相等而自动删除的情况，从而操作次数为 $n$ 次；当环中元素种类为2种时，序列呈 $abab\cdots$ 形式，操作次数为 $\frac{n}{2}+1$ 次；当环中元素种类为1种且 $n = 1$ 时，操作次数为1次。不同题解在实现细节上略有差异，如统计元素种类的方式不同等。

### 所选的题解
- **作者：linyihdfj (5星)**
    - **关键亮点**：思路清晰，简洁明了地阐述了不同元素种类情况下的操作次数计算方式，代码实现简洁高效。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int a[N],n;
bool vis[N];
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1; i<=n; i++) scanf("%d",&a[i]);
        int cnt = 0;
        for(int i=1; i<=n; i++) if(!vis[a[i]]) cnt++,vis[a[i]] = true;
        if(cnt > 2) printf("%d\n",n);
        else printf("%d\n",n == 1? 1 : (n - 2) / 2 + 2);
        for(int i=1; i<=n; i++) vis[a[i]] = false;
    }
    return 0;
}
```
    - **核心实现思想**：通过 `vis` 数组标记已经出现过的元素，统计不同元素的个数 `cnt`。根据 `cnt` 的值判断环中元素种类情况，从而输出对应的最大操作次数。

- **作者：abensyl (4星)**
    - **关键亮点**：采用排序和 `unique` 函数统计不同元素个数，代码简洁，逻辑清晰。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
const int N = 205;
int a[N];
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        sort(a + 1, a + n + 1);
        int len = unique(a + 1, a + n + 1) - a - 1;
        if (len == 1) //只有一种元素
            cout << 1;
        else if (len == 2) //有两种元素
            cout << min(n, (n >> 1) + 1);
        else //多于两种元素
            cout << n;
        cout << '\n';
    }
    return 0;
}
```
    - **核心实现思想**：先对数组排序，再用 `unique` 函数去重，通过计算去重后的数组长度 `len` 判断元素种类数量，进而得出最大操作次数。

- **作者：KingPowers (4星)**
    - **关键亮点**：通过位运算判断环长度奇偶性，并且通过循环判断环是否为两种元素交替出现，逻辑较为严谨。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define fx first
#define fy second
#define mkp make_pair
#define umap unordered_map
using namespace std;
const int N=2e5+5;
const int inf=1e18;
int read(){
    int ans=0,flag=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') flag=-1;
    for(;isdigit(ch);ch=getchar()) ans=ans*10+(ch^48);
    return ans*flag;
}
int T,n,m,a[N],b[N];
signed main(){
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++) a[i]=read();
        if(n&1||n==2) printf("%lld\n",n);
        else{
            bool flag=1;
            for(int i=3;i<n;i++) if(a[i]!=a[i-2]) flag=0;
            for(int i=4;i<=n;i++) if(a[i]!=a[i-2]) flag=0; 
            if(flag) printf("%lld\n",1+(n/2));
            else printf("%lld\n",n);
        }
    }
    return 0;
}
```
    - **核心实现思想**：先通过 `n&1` 判断环长度奇偶性，对于偶数长度的环，通过两次循环判断是否为两种元素交替出现，从而确定最大操作次数。

### 最优关键思路或技巧
通过分析环中元素种类数量来确定最大操作次数，利用数组标记、排序去重、循环判断等方式统计元素种类。这种根据数据特征分类讨论的思维方式是解决本题的关键。

### 可拓展之处
此类题目可拓展到更复杂的循环序列操作问题，类似算法套路是先分析序列特征，如元素种类、分布规律等，再根据不同情况分类讨论得出结果。

### 洛谷相似题目推荐
- [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)
- [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)

### 个人心得摘录与总结
- **作者：linyihdfj**：一开始想了两个贪心都错了，说明本题贪心策略较难直接想到，需要深入分析题目条件。
- **作者：abensyl**：这题又吃一罚时，表明本题虽看似简单，但容易因细节考虑不周而犯错。 

---
处理用时：53.41秒