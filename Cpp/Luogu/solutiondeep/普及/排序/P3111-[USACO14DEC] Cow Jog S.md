# 题目信息

# [USACO14DEC] Cow Jog S

## 题目描述

 

The cows are out exercising their hooves again!  There are N cows

jogging on an infinitely-long single-lane track (1 <= N <= 100,000).

Each cow starts at a distinct position on the track, and some cows jog

at different speeds.


 

With only one lane in the track, cows cannot pass each other.  When a

faster cow catches up to another cow, she has to slow down to avoid

running into the other cow, becoming part of the same running group.

 

The cows will run for T minutes (1 <= T <= 1,000,000,000).  Please

help Farmer John determine how many groups will be left at this time.

Two cows should be considered part of the same group if they are at


the same position at the end of T minutes. 

有N (1 <= N <= 100,000)头奶牛在一个单人的超长跑道上慢跑，每头牛的起点位置都不同。由于是单人跑道，所有他们之间不能相互超越。当一头速度快的奶牛追上另外一头奶牛的时候，他必须降速成同等速度。我们把这些跑走同一个位置而且同等速度的牛看成一个小组。


请计算T (1 <= T <= 1,000,000,000)时间后，奶牛们将分为多少小组。



## 样例 #1

### 输入

```
5 3 
0 1 
1 2 
2 3 
3 2 
6 1 

 

```

### 输出

```
 

3 

 
```

# AI分析结果

### 综合分析与结论
这些题解大多围绕计算奶牛在 T 分钟后的分组数量展开，核心在于判断奶牛之间是否会追及并合并为一组。主要思路有两种：一是计算每头牛最终位置，从后往前比对；二是通过速度和位置关系判断是否追及。部分题解使用了单调队列优化。

### 所选题解
- **作者：NewErA（5 星）**
    - **关键亮点**：思路清晰，代码简洁，注释明确提醒使用 long long 处理大数据，可读性高。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,t,last[100005];
struct cow
{
    long long spe,pos;
}a[100005];
int main()
{
    cin >> n >> t;
    for(int i=1;i<=n;i++)
    {
        cin >> a[i].pos >> a[i].spe;
        last[i]=a[i].pos+a[i].spe*t;
    }
    int res=1;
    for(int i=n-1;i>=1;i--)
    {
        if(last[i]>=last[i+1])
        {
            last[i]=last[i+1];
        }
        else
        {
            res++;
        }
    }
    cout<< res;
}
```
    - **核心实现思想**：先计算每头牛的最终位置，再从后往前遍历，若前一头牛最终位置能到达后一头牛，则将其位置设为后一头牛的位置；否则分组数加一。

- **作者：Tarsal（4 星）**
    - **关键亮点**：思路与上一题解类似，代码规范，注释清晰，适合初学者。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, t, ans = 1, last[100010];
struct node
{
    long long s, p;
}a[100010];

int main()
{
    scanf("%lld%lld", &n, &t);
    for(int i = 1; i <= n; ++ i)
    {
        scanf("%lld%lld", &a[i].p, &a[i].s);
        last[i] = a[i].p + a[i].s * t;
    }
    for(int i = n - 1; i >= 1; -- i)
    {
        if(last[i] >= last[i + 1])
            last[i] = last[i + 1];
        else
            ++ ans;
    }
    printf("%lld", ans);
    return 0;
}
```
    - **核心实现思想**：同 NewErA 的题解，先记录最终位置，再从后往前判断是否追及，更新分组数。

- **作者：Thomasguo666（4 星）**
    - **关键亮点**：给出了判断追及的数学公式推导，代码简洁，同时提供了 Python 和 C++ 两种语言的实现。
    - **核心代码（C++）**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll p[100005],v[100005];
int main()
{
    ll n,t,ans=1;
    cin>>n>>t;
    for (ll i=1;i<=n;i++) cin>>p[i]>>v[i],p[i]+=v[i]*t;
    for (ll i=n-1;i>0;i--) ans+=(p[i]<p[i+1]?1:(p[i]=p[i+1])*0);
    cout<<ans<<endl;
    return 0;
}
```
    - **核心实现思想**：先计算每头牛最终位置，反向遍历，若前一头牛最终位置小于后一头牛，则分组数加一；否则更新前一头牛位置。

### 最优关键思路或技巧
- 计算每头牛的最终位置，从后往前遍历判断是否追及，是解决本题的关键思路，能有效避免复杂的模拟过程。
- 注意使用 long long 处理大数据，防止溢出。

### 可拓展之处
同类型题可能会增加跑道数量、改变追及规则等。类似算法套路可用于处理交通流、排队等问题，核心是判断元素之间的追及和合并关系。

### 推荐洛谷题目
- P1031 均分纸牌
- P1223 排队接水
- P1047 校门外的树

### 个人心得摘录与总结
- **OIer991215**：提到数据水，用 $n^2$ 复杂度算法过了十万数据，但意识到存在 hack 数据会导致 TLE，提醒要注意算法复杂度。 

---
处理用时：33.77秒