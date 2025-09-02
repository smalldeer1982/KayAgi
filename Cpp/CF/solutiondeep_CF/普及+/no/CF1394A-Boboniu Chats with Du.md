# 题目信息

# Boboniu Chats with Du

## 题目描述

Have you ever used the chat application QQ? Well, in a chat group of QQ, administrators can muzzle a user for days.

In Boboniu's chat group, there's a person called Du Yi who likes to make fun of Boboniu every day.

Du will chat in the group for $ n $ days. On the $ i $ -th day:

- If Du can speak, he'll make fun of Boboniu with fun factor $ a_i $ . But after that, he may be muzzled depending on Boboniu's mood.
- Otherwise, Du won't do anything.

Boboniu's mood is a constant $ m $ . On the $ i $ -th day:

- If Du can speak and $ a_i>m $ , then Boboniu will be angry and muzzle him for $ d $ days, which means that Du won't be able to speak on the $ i+1, i+2, \cdots, \min(i+d,n) $ -th days.
- Otherwise, Boboniu won't do anything.

The total fun factor is the sum of the fun factors on the days when Du can speak.

Du asked you to find the maximum total fun factor among all possible permutations of $ a $ .

## 说明/提示

In the first example, you can set $ a'=[15, 5, 8, 10, 23] $ . Then Du's chatting record will be:

1. Make fun of Boboniu with fun factor $ 15 $ .
2. Be muzzled.
3. Be muzzled.
4. Make fun of Boboniu with fun factor $ 10 $ .
5. Make fun of Boboniu with fun factor $ 23 $ .

Thus the total fun factor is $ 48 $ .

## 样例 #1

### 输入

```
5 2 11
8 10 15 23 5```

### 输出

```
48```

## 样例 #2

### 输入

```
20 2 16
20 5 8 2 18 16 2 16 16 1 5 16 2 13 6 16 4 17 21 7```

### 输出

```
195```

# AI分析结果

### 题目翻译
# Boboniu与Du聊天

## 题目描述
你使用过聊天应用QQ吗？在QQ的一个聊天群里，管理员可以禁言用户若干天。

在Boboniu的聊天群里，有一个叫Du Yi的人，他每天都喜欢取笑Boboniu。

Du将在群里聊 $n$ 天。在第 $i$ 天：
- 如果Du可以发言，他会以欢乐因子 $a_i$ 取笑Boboniu。之后，他可能会根据Boboniu的心情被禁言。
- 否则，Du不会做任何事。

Boboniu的心情是一个常量 $m$。在第 $i$ 天：
- 如果Du可以发言且 $a_i > m$，那么Boboniu会生气并禁言他 $d$ 天，这意味着Du在第 $i + 1, i + 2, \cdots, \min(i + d, n)$ 天将无法发言。
- 否则，Boboniu不会做任何事。

总欢乐因子是Du可以发言的那些天的欢乐因子之和。

Du请你找出所有可能的 $a$ 的排列中最大的总欢乐因子。

## 说明/提示
在第一个样例中，你可以将 $a'$ 设为 $[15, 5, 8, 10, 23]$。那么Du的聊天记录将是：
1. 以欢乐因子 $15$ 取笑Boboniu。
2. 被禁言。
3. 被禁言。
4. 以欢乐因子 $10$ 取笑Boboniu。
5. 以欢乐因子 $23$ 取笑Boboniu。

因此总欢乐因子是 $48$。

## 样例 #1
### 输入
```
5 2 11
8 10 15 23 5
```
### 输出
```
48
```

## 样例 #2
### 输入
```
20 2 16
20 5 8 2 18 16 2 16 16 1 5 16 2 13 6 16 4 17 21 7
```
### 输出
```
195
```

### 算法分类
贪心

### 综合分析与结论
这些题解主要围绕贪心算法解决问题。思路核心是将数据按与 $m$ 的大小关系分成两组，大于 $m$ 的数会导致禁言，小于等于 $m$ 的数不会。大部分题解通过枚举大于 $m$ 的数的个数，利用贪心原则优先选择较大的数来计算最大总欢乐因子。各题解的区别在于具体实现方式和细节处理。

### 所选题解
- **作者：KellyFrog (赞：7)，4星**
  - **关键亮点**：思路清晰，代码简洁，通过简单的贪心和枚举实现，先分组排序，再枚举大于 $m$ 的数的个数，计算剩余天数可选择的小于等于 $m$ 的数的和，更新最大总欢乐因子。
- **作者：绝顶我为峰 (赞：4)，4星**
  - **关键亮点**：采用动态规划倒推的方式，考虑不禁言和禁言两种选择，通过 $dp$ 数组记录状态，虽然代码稍复杂，但逻辑严谨。
- **作者：Dzhao (赞：2)，4星**
  - **关键亮点**：贪心思路明确，通过排序和枚举，计算不同情况下的总欢乐因子，取最大值。

### 重点代码
#### KellyFrog的代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

const int MAXN = 1e5 + 5;

int big[MAXN], small[MAXN], sum[MAXN];
int p1 = 1, p2 = 1;
int n, m, k, x;

signed main() {
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) {
        cin >> x;
        if(x <= k) {
            small[p1++] = x;
        } else {
            big[p2++] = x;
        }
    }
    sort(small + 1, small + 1 + p1, greater<int>());
    sort(big + 1, big + 1 + p2, greater<int>());
    for(int i = 1; i <= p1; i++) {
        sum[i] = sum[i - 1] + small[i];
    }
    int ans = sum[p1], cur = 0;
    for(int i = 1; i <= p2; i++) {
        cur += big[i];
        int days = (i - 1) * (m + 1) + 1;
        if(days > n) {
            break;
        }
        int left = min(n - days, p1);
        ans = max(ans, sum[left] + cur);
    }
    cout << ans << endl;
}
```
**核心实现思想**：先将数据按与 $m$ 的大小关系分组，分别排序。计算小于等于 $m$ 的数的前缀和，枚举大于 $m$ 的数的个数，计算其占用天数，剩余天数选择小于等于 $m$ 的数，更新最大总欢乐因子。

#### 绝顶我为峰的代码
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#define int long long
using namespace std;
int n,m,d,a[100001],dp[100001][3],sum,cnt1,cnt2;
vector<int> q1,q2;
signed main()
{
    cnt1=cnt2=-1;
    scanf("%lld%lld%lld",&n,&d,&m);
    for(register int i=1;i<=n;++i)
    {
        dp[i][0]=-1;
        scanf("%lld",&a[i]);
        if(a[i]>m)
        {
            q1.push_back(a[i]);
            ++cnt1;
        }
        else
        {
            q2.push_back(a[i]);
            sum+=a[i];
            ++cnt2;
        }
    }
    if(q1.empty())
    {
        printf("%lld\n",sum);
        return 0;
    }
    sort(q1.begin(),q1.end());
    sort(q2.begin(),q2.end());
    dp[n][0]=q1[cnt1];
    dp[n][1]=cnt1-1;
    dp[n][2]=cnt2;
    for(register int i=n-1;i>=1;--i)
    {
        if(dp[i+1][2]>=0)
        {
            dp[i][0]=dp[i+1][0]+q2[dp[i+1][2]];
            dp[i][1]=dp[i+1][1];
            dp[i][2]=dp[i+1][2]-1;
        }
        if(i+d<n&&dp[i+d+1][1]>=0)
            if(dp[i+d+1][0]+q1[dp[i+d+1][1]]>dp[i][0])
            {
                dp[i][0]=dp[i+d+1][0]+q1[dp[i+d+1][1]];
                dp[i][1]=dp[i+d+1][1]-1;
                dp[i][2]=dp[i+d+1][2];
            }
        if(dp[i][0]==-1)
        {
            dp[i][0]=dp[i+1][0];
            dp[i][1]=dp[i+1][1];
            dp[i][2]=dp[i+1][2];
        }
    }
    int ans=0;
    for(register int i=1;i<=n;++i)
        ans=max(ans,dp[i][0]);
    printf("%lld\n",ans);
    return 0;
}
```
**核心实现思想**：将数据分组排序，从后往前进行动态规划。考虑不禁言和禁言两种情况，更新 $dp$ 数组，最后取最大值。

#### Dzhao的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void rd(T &x)
{
    x=0;bool f=0;char c=getchar();
    while(!isdigit(c)) {if(c=='-') f=1;c=getchar();}
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x; 
}
typedef long long ll;
const int N=1e5+5;
int n,d,pos=-1;
ll ans,a[N],m,p[N],res;

int main()
{
    rd(n),rd(d),rd(m);
    for(int i=1;i<=n;i++) rd(a[i]); 
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) 
        if(a[i]>m)
        {
            pos=i-1;
            break;
        }
    if(pos==-1) pos=n;
    for(int i=1;i<=n;i++) p[i]=p[i-1]+a[i];
    for(int x=0;x<=pos;x++)
    {
        res=0;
        int k=(n-x)/(d+1);
        int y=n-x-(d+1)*k;
        if(k+(y>0)>n-pos) continue; 
        res=p[n]-p[n-k-(y>0)]+p[pos]-p[pos-x];
        ans=max(res,ans);
    }
    printf("%lld\n",ans);
    return 0;
}
```
**核心实现思想**：排序后找到最后一个小于等于 $m$ 的数的位置，枚举小于等于 $m$ 的数的个数，计算剩余可选择的大于 $m$ 的数的个数，计算总欢乐因子，取最大值。

### 关键思路或技巧
- **分组思想**：将数据按与 $m$ 的大小关系分成两组，分别处理。
- **贪心策略**：优先选择较大的数，以获得最大总欢乐因子。
- **枚举优化**：通过枚举大于 $m$ 的数的个数，减少不必要的计算。

### 拓展思路
同类型题或类似算法套路通常涉及在一定规则下求最优解，可使用贪心算法解决。例如在资源分配、任务调度等问题中，根据不同的规则和限制条件，通过合理的分组和贪心策略来求解。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)

### 个人心得
- **引领天下**：作为边界条件的 $f_n$ 同样需要被统计，否则可能会导致错误。在实现动态规划时，要特别注意边界条件的处理。 

---
处理用时：69.19秒