# 题目信息

# 「SWTR-6」GCDs & LCMs

## 题目描述

小 A 有一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$。

他想从这些数中选出一些数 $b_1,b_2,\cdots,b_k$ 满足：对于所有 $i\ (1\leq i\leq k)$，$b_i$ 要么是序列 $b$ 中的最大值，要么存在一个位置 $j$ 使得 $b_j>b_i$ 且 $b_i+b_j+\gcd(b_i,b_j)=\mathrm{lcm}(b_i,b_j)$。

- 如果你不知道 $\gcd$ 和 $\mathrm{lcm}$ 是什么，可以点击最底部的「帮助/提示」部分的链接。

小 A 想让选出的数之和尽量大。请求出这个最大值。

## 说明/提示

**「样例 1 说明」**

可以选择 $b=\{2,3\}$，因为 $2+3+\gcd(2,3)=\mathrm{lcm}(2,3)$。

**「数据范围与约定」**

**本题采用捆绑测试。**

- Subtask 1（5 points）：$n\leq2$；
- Subtask 2（20 points）：$n\leq 17$；
- Subtask 3（15 points）：$a_i\leq 2\times 10^3$；
- Subtask 4（15 points）：$n\leq 2\times 10^3$；
- Subtask 5（10 points）：$n\leq 5\times 10^4$；
- Subtask 6（10 points）：$a_i\leq 10^7$；
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^5$，$1\leq a_i\leq 10^9$。

**「帮助/提示」**

$\gcd$ 表示[最大公约数](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308?fr=aladdin)，$\mathrm{lcm}$ 表示[最小公倍数](https://baike.baidu.com/item/%E6%9C%80%E5%B0%8F%E5%85%AC%E5%80%8D%E6%95%B0/6192375?fr=aladdin)。

**「来源」**

[【LGR-075】洛谷 8 月月赛 II Div.2 & SWTR-06 & EZEC Round 3](https://www.luogu.com.cn/contest/33190)。

idea & solution & data by [Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
4
4 3 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
10
6 7 18 4 17 10 9 1 3 8```

### 输出

```
19```

## 样例 #3

### 输入

```
3
123456789 234567890 123456789```

### 输出

```
246913578```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是先推导 $b_i + b_j + \gcd(b_i, b_j) = \text{lcm}(b_i, b_j)$ 这个式子，得出满足条件的 $b_i$ 和 $b_j$ 存在 $b_j=\frac{3}{2}b_i$ 的关系，然后在此基础上通过不同方法找出满足条件的子序列并计算其最大和。

算法要点包括数学推导、枚举、二分查找、map 映射、动态规划、图论（建图、拓扑排序、并查集）等。

难点在于式子的推导以及如何高效地找出满足条件的子序列并计算最大和。不同题解针对不同数据范围给出了不同的做法，从暴力枚举到优化后的 $O(n\log n)$ 复杂度算法。

### 所选题解
- **作者：Alex_Wei (赞：56)，5星**
    - **关键亮点**：思路清晰，详细分析了各个子任务的做法，对核心结论进行了严格证明，代码简洁易懂。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N=3e5+5;

map <int,int> mp;
int n,a[N]; ll ans;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],mp[a[i]]++;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        ll tmp=a[i],cnt=0;
        while(mp[tmp]){
            cnt+=tmp*mp[tmp],mp[tmp]=0;
            if(tmp%2==0)tmp=tmp/2*3;
            else break;
        }
        ans=max(ans,cnt);
    } cout<<ans<<endl;
    return 0;
}
```
    - **核心实现思想**：先将数组元素存入 map 记录出现次数，然后排序。枚举每个元素作为起始元素，不断找其 $\frac{3}{2}$ 倍的元素，累加和并标记已访问，更新最大和。
- **作者：Konnyaku_LXZ (赞：6)，4星**
    - **关键亮点**：对式子推导详细，代码结构清晰，通过二分查找优化查找过程。
    - **核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cmath>
#include<stack>
using namespace std;

const int MAXN=5e5+50;
typedef long long LL;

LL N,a[MAXN],x[MAXN],t[MAXN],f[MAXN],cnt=0,Ans=0;

void Init(){
    scanf("%lld",&N);
    for(int i=1;i<=N;++i) scanf("%lld",&a[i]);
    sort(a+1,a+1+N);//先排序 
    for(int i=1;i<=N;++i){//保存元素值和出现次数 
        if(a[i]==a[i-1]) ++t[cnt];
        else x[++cnt]=a[i],t[cnt]=1;
    }
    for(int i=1;i<=cnt;++i) f[i]=x[i]*t[i],Ans=max(Ans,f[i]);//计算f数组的初始值并更新最大值 
}

void Solve(){
    for(int i=2;i<=cnt;++i){
        if(x[i]%3!=0) continue;//如果不能整除三的话直接跳过 
        LL val=x[i]/3*2;
        LL pos=lower_bound(x+1,x+i,val)-x;//二分 
        if(pos>=i||pos<1||val!=x[pos]) continue;
        f[i]+=f[pos];//更新f值 
        Ans=max(Ans,f[i]);//取最大值 
    }
}

void Print(){
    cout<<Ans<<endl;
}

int main()
{
    Init();
    Solve();
    Print(); 
    return 0;
}
```
    - **核心实现思想**：先排序去重，记录元素值和出现次数。初始化 $f$ 数组为元素值乘以出现次数。然后遍历元素，二分查找其 $\frac{2}{3}$ 倍的元素，若存在则更新 $f$ 值，最后取 $f$ 数组最大值。
- **作者：InformationEntropy (赞：2)，4星**
    - **关键亮点**：推导过程详细，提供了 map 和二分两种实现方式，并对比了复杂度。
    - **核心代码（二分）**：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define max(a, b) (a>b)?a:b;
using namespace std;
typedef long long ll;
inline void read(int &x)
{
    x=0;
    int f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-')
        {
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x*=f;
}
int a[1000001];
struct node{
    int x, times;
}s[1000001];//用结构体存储每个数出现的次数，每次查询一个数复杂度为O(log2cnt)
int cnt;
int find(int n)//手写二分
{
    int l=1, r=cnt;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(s[mid].x==n) return mid;
        else if(s[mid].x<n) l=mid+1;
        else r=mid-1;
    }
    return -1;//如果不在输入序列中则返回-1
}
int main()
{
    int n;
    read(n);
    for(int i=1; i<=n; i++)
    {
        read(a[i]);
    }
    sort(a+1, a+n+1);
    for(int i=1; i<=n; i++)
    {
        if(a[i]!=a[i-1])
        {
            s[++cnt].x=a[i];
            s[cnt].times=1;
        }else{
            s[cnt].times++;
        }
    }//排序初始化每个数出现的次数。
    ll ans=0;
    for(int i=1; i<=n; i++)
    {
        ll t=a[i];
        ll sum=0;
        int sub=find(t);//找到当前数在结构体数组中的下标
        while(s[sub].times)
        {
            sum+=t*s[sub].times;
            s[sub].times=0;
            if(t%2==0)
            {
                t=t/2*3;
                sub=find(t);
                if(sub==-1) break;
            }else break;
        }
        ans=max(ans, sum);
        //与map差不多，不再赘述。
    }
    cout << ans;
    return 0;
}
```
    - **核心实现思想**：用结构体数组存储元素值和出现次数，手写二分查找元素。枚举每个元素，不断找其 $\frac{3}{2}$ 倍的元素，累加和并标记已访问，更新最大和。

### 最优关键思路或技巧
- **数学推导**：通过设 $\gcd(b_i, b_j)=d$，将 $b_i = pd$，$b_j = qd$ 代入式子推导得出 $p,q$ 的关系，进而得到 $b_i$ 和 $b_j$ 的关系，这是解决本题的关键。
- **数据结构优化**：使用 map 或二分查找来判断元素是否存在，将查找复杂度从 $O(n)$ 降低到 $O(\log n)$。
- **剪枝优化**：在枚举过程中，遇到奇数或元素不存在时及时停止，避免不必要的计算。

### 可拓展之处
同类型题可能会涉及更复杂的数学式子推导，或者在满足某种条件的子序列选择上有更多限制。类似算法套路包括先对条件式子进行数学推导，找出元素之间的关系，然后利用数据结构（如 map、二分查找）和算法（如动态规划、图论）来解决问题。

### 推荐题目
- P1048 采药：考察动态规划基础，与本题中动态规划的思想有一定相似性。
- P1216 数字三角形：经典的动态规划题目，有助于理解状态转移方程的构建。
- P1616 疯狂的采药：完全背包问题，进一步加深对动态规划的理解和应用。

### 个人心得摘录与总结
- **作者：lndjy**：当遇到复杂条件不会推导时，可以通过打表找规律，如本题中通过输出选中的数发现选择的数都为上一个数的三分之二，从而确定结论。
- **作者：CuberStan**：比赛时先拿部分分，如本题先通过爆搜拿到 25 分。在遇到复杂度高的问题时，思考如何降低复杂度，如本题通过推导式子找出元素关系，用二分查找代替二重循环建图，将复杂度从 $O(n^2)$ 降低到 $O(n\log n)$。 

---
处理用时：73.61秒