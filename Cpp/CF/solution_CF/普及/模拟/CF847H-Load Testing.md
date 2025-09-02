# Load Testing

## 题目描述

Polycarp plans to conduct a load testing of its new project Fakebook. He already agreed with his friends that at certain points in time they will send requests to Fakebook. The load testing will last $ n $ minutes and in the $ i $ -th minute friends will send $ a_{i} $ requests.

Polycarp plans to test Fakebook under a special kind of load. In case the information about Fakebook gets into the mass media, Polycarp hopes for a monotone increase of the load, followed by a monotone decrease of the interest to the service. Polycarp wants to test this form of load.

Your task is to determine how many requests Polycarp must add so that before some moment the load on the server strictly increases and after that moment strictly decreases. Both the increasing part and the decreasing part can be empty (i. e. absent). The decrease should immediately follow the increase. In particular, the load with two equal neigbouring values is unacceptable.

For example, if the load is described with one of the arrays \[1, 2, 8, 4, 3\], \[1, 3, 5\] or \[10\], then such load satisfies Polycarp (in each of the cases there is an increasing part, immediately followed with a decreasing part). If the load is described with one of the arrays \[1, 2, 2, 1\], \[2, 1, 2\] or \[10, 10\], then such load does not satisfy Polycarp.

Help Polycarp to make the minimum number of additional requests, so that the resulting load satisfies Polycarp. He can make any number of additional requests at any minute from $ 1 $ to $ n $ .

## 说明/提示

In the first example Polycarp must make two additional requests in the third minute and four additional requests in the fourth minute. So the resulting load will look like: \[1, 4, 5, 6, 5\]. In total, Polycarp will make $ 6 $ additional requests.

In the second example it is enough to make one additional request in the third minute, so the answer is $ 1 $ .

In the third example the load already satisfies all conditions described in the statement, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
5
1 4 3 2 5
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
1 2 2 2 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7
10 20 40 50 70 90 30
```

### 输出

```
0
```

# 题解

## 作者：OIerJiang_1017 (赞：1)

## [CF847H题目传送门](https://www.luogu.com.cn/problem/CF847H)

### 题目大意

给定一个序列，你可以对序列中的任意元素进行若干次操作，每次操作一个一个元素 $+1$，你的任务是确定最少进行多少次操作能将序列变成一段严格递增之后又严格递减。整个序列严格递增或严格递减是允许的。

### 解决方法

明显的**前缀和**，不用会**超时**。

分别从左到右再从右到左枚举将给定数列分别变成**单调递增数列**和**单调递减数列**的次数，并顺便计算**前缀和**。

```cpp
for(int i = 2; i <= n; i++)
//计算单调递增次数与前缀和
{
      b[i] = max(b[i - 1] + 1, a[i]);
      c[i] = c[i - 1] - a[i] + b[i];
}
for(int i = n - 1; i >= 1; i--)
//计算单调递减次数与前缀和
{
    d[i] = max(d[i + 1] + 1, a[i]);
    e[i] = e[i + 1] - a[i] + d[i];
}
```
最终用如下公式计算结果即可：`sum = max(b[i], d[i]) + c[i] + e[i + 1] - b[i];`

### 注意事项

$1 \leq a_i \leq 10^9$，需要开 `long long`。

### 代码展示

```cpp
#include <bits/stdc++.h>
#define ll long long
//十年OI一场空,不开long long见祖宗
using namespace std;

const int N = 1e5 + 10;
ll n, a[N], b[N], c[N];
//b[],c[],d[],e[]计算将数列变成
//单调递增或递减次数和前缀和
ll d[N], e[N], ans = 2e9, sum;

int main()
{
    scanf("%lld", &n);//建议scanf,更快
    for(int i = 1; i <= n; i++)
    	scanf("%lld", &a[i]);
    b[1] = a[1];
    for(int i = 2; i <= n; i++)
	//计算将数列变成单调递增次数与前缀和
	{
        b[i] = max(b[i - 1] + 1, a[i]);
        c[i] = c[i - 1] - a[i] + b[i];
    }
    d[n] = a[n];
    for(int i = n - 1; i >= 1; i--)
    //计算将数列变成单调递减次数与前缀和
	{
        d[i] = max(d[i + 1] + 1, a[i]);
        e[i] = e[i + 1] - a[i] + d[i];
    }
    ans = min(e[1], c[n]);
    for(int i = 2; i < n; i++)
	{
        sum = max(b[i], d[i]) + c[i] + e[i + 1] - b[i]; 
        if(sum < ans) ans = sum;//计算答案并取最小值 
    }
    printf("%lld\n", ans);//建议printf,更快
    return 0;
}
```

---

## 作者：MENG_QI (赞：1)

## 前言
蒟蒻的第一篇题解，望各位大佬点评！
## 题意
给定一个数组，问，对多少个位置进行操作后，能将序列变成一段递增之后严格递减的序列。且 $ n≤10^ 6$。
## 思路 
经过 $N$ 分钟的看题，运用**前缀后缀**（假设每个点**为最高点**）。枚举每一个点，计以这个点位最高点的花费。可以预处理出一段前缀成为递增的最小花费。也可以预处理出一段后缀成为递减的最小花费。
## 核心
```cpp
for(int i=1;i<=n;i++)cin >> a[i];//输入
    q[1]=a[1];
    for(int i = 2;i <= n;i++){
        q[i] = max(a[i],q[i-1]+1);
        r[i] = r[i-1]+q[i]-a[i];
    }
    e[n]=a[n];
    for(int i = n - 1;i >= 1;i--){
        e[i] = max(a[i],e[i+1]+1);
        f[i] = f[i+1]+e[i]-a[i];//不多解释
    }
    ll minn=min(f[1],r[n]);//定义小值
    ll ss;
    for(int i=2;i<n;i++){
        ss=r[i]+f[i+1]+max(q[i],e[i])-q[i];
        if(ss<minn)
            minn=ss;
    }
```
## 完整代码
```cpp
#include<bits/stdc++.h>
#define ll lowenzhengng long 
#define N 1000001
using namespace std;
ll a[N] ,  q[N] , r[N] , e[N] , f[N];
int n;
int main(){
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    q[1]=a[1];
    for(int i = 2;i <= n;i++){
        q[i] = max(a[i],q[i-1]+1);
        r[i] = r[i-1]+q[i]-a[i];
    }
    e[n]=a[n];
    for(int i = n - 1;i >= 1;i--){
        e[i] = max(a[i],e[i+1]+1);
        f[i] = f[i+1]+e[i]-a[i];
    }
    ll minn=min(f[1],r[n]);
    ll ss;
    for(int i=2;i<n;i++){
        ss=r[i]+f[i+1]+max(q[i],e[i])-q[i];
        if(ss<minn)
            minn=ss;
    }
    cout << minn;
    return 0;
} 
```
### 最后
这毕竟是本**蒟蒻**的第一篇题解，望大家喜欢。

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF847H)
## 题意
给定 $n$，表示一个数组的长度，要把这个数列变成严格递增再严格递减（类似一个山峰，允许单调递增或递减），每次可将这个数组的任意元素 $+1$，求最少需要多少次。
## 思路
这题应该使用**前缀和**，不能直接枚举，否则会超时。

先从左到右用前缀和记录这个点作为递增的时候的最高点所需的次数。
```cpp
for(int i=2;i<=n;i++)
{
    q[i]=max(a[i],q[i-1]+1);
    r[i]=r[i-1]+q[i]-a[i];
}
``````
先从右到左用后缀和记录这个点作为递增的时候的最高点所需的次数。
```cpp
for(int i=n-1;i>=1;i--)
{
    e[i]=max(a[i],e[i+1]+1);
    f[i]=f[i+1]+e[i]-a[i];
 }
``````
### 重点
输出结果为一下。
```cpp
r[i]+f[i+1]+max(q[i],e[i])-q[i];
``````
## code
```cpp
#include<bits/stdc++.h>//万能头
#define ll long long //十年OI一场空，不开long long见祖宗
using namespace std;
const int maxn=1000010;
ll a[maxn],q[maxn],r[maxn],e[maxn],f[maxn],s,n;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    q[1]=a[1];
    for(int i=2;i<=n;i++)//从左到右前缀和
	{
        q[i]=max(a[i],q[i-1]+1);
        r[i]=r[i-1]+q[i]-a[i];
    }
    e[n]=a[n];
    for(int i=n-1;i>=1;i--)//从右到左后缀和
	{
        e[i]=max(a[i],e[i+1]+1);
        f[i]=f[i+1]+e[i]-a[i];
    }
    ll minn=min(f[1],r[n]);
    for(int i=2;i<n;i++)//结果
	{
        s=r[i]+f[i+1]+max(q[i],e[i])-q[i];
        if(s<minn)//最小值
            minn=s;
    }
    cout<<minn<<endl;
    return 0;//完结撒花
}
``````

---

## 作者：_Passerby_ (赞：0)

更好的阅读体验：[cnblogs](https://www.cnblogs.com/Eliauk-FP/p/18529164)。**注意，博客园里面包含了CF847这一套题大部分题的题解！**

【题目大意】

给一个数组 $a$，问多少次对单个位置 $+1$ 操作后，能将序列变成前一段严格递增，后一段严格递减（即单峰序列）。

【解题思路】

考虑维护两个数组 $p_i$ 与 $q_i$，分别表示前 $i$ 个数为严格递增或第 $i$ 个数到第 $n$ 个数为严格递减时位置 $i$ 的最小值。

考虑计算这两个数组。对于前 $i$ 个数，考虑正序递推。由于它们是严格递增，所以 $p_i$ 最小为 $p_{i - 1} + 1$。但是只有 $+1$ 操作，所以如果 $p_{i - 1} + 1 < a_i$，那么就有 $p_i = a_i$。所以有递推式

$$
p_i = \max{(p_{i - 1} + 1, a_i)}
$$

同理，$q$ 倒序递推即可。有递推式

$$
q_i = \max{(q_{i + 1} + 1, a_i)}
$$

考虑枚举最高点 $i$（即山峰），对于 $i$ 前面的数可以前缀和计算需要几次 $+1$，对于 $i$ 后面的数后缀和计算，对于 $i$ 这个数，取到的值为 $\max{(p_i, q_i)}$，因为 $i$ 既属于前面的严格递增序列，也属于后面的严格递减序列。这样直接做就做完了。

形式化的：

记 $sa$、$sb$ 分别为 $a$ 的前缀和和后缀和数组，则有

$$
sa_i = sa_{i - 1} + a_i
$$

$$
sb_i = sb_{i + 1} + a_i
$$

记 $sp$、$sq$ 分别为 $p$ 的前缀和数组和 $q$ 的后缀和数组，则有

$$
sp_i = sp_{i - 1} + p_i
$$

$$
sq_i = sq_{i + 1} + q_i
$$

对于最高点 $i$，有答案为

$$
ans_i = (sp_{i - 1} - sa_{i - 1}) + (sq_{i + 1} - sb_{i + 1}) + (\max{(p_i, q_i)} - a_i);
$$

注意需要特判整个序列严格单增或者严格单减的情况，有答案为

$$
Ans = \min{(sp_n - sa_n, sq_1 - sb_1, \min_{2\leq i < n}{ans_i})}
$$

即

$$
Ans = \min{(sp_n - sa_n, sq_1 - sb_1, \min_{2\leq i < n}{(sp_{i - 1} - sa_{i - 1} + sq_{i + 1} - sb_{i + 1} + \max{(p_i, q_i)} - a_i)})}
$$

这样就做完了。

---

## 作者：xzggzh1 (赞：0)

题意：

给一个数组，问多少次对单个位置 $+1$ 操作后，能将序列变成一段严格递增的之后严格递减。

$n\leq 10^6$ 。

----

枚举每一个点，计算以这个点为转折点的修改花费。

可以预处理出一段前缀成为单调递增的最小花费。

同理可以预处理出一段后缀成为单调递减的最小花费。

---

核心代码：

```cpp

#define int long long
int n,a[101111],mf[101111],mg[101111],f[101111],g[101111],ans;
signed main(){
    scanf("%lld",&n);
    for (int i=1;i<=n;i++)scanf("%lld",&a[i]);
    mf[0]=f[0]=0;
    for (int i=1;i<=n;i++){
        mf[i]=max(mf[i-1]+1,a[i]);
        f[i]=f[i-1]+mf[i]-a[i];
    }
    mg[n+1]=g[n+1]=0;
    for (int i=n;i>0;i--){
        mg[i]=max(mg[i+1]+1,a[i]);
        g[i]=g[i+1]+mg[i]-a[i];
    }
    ans=min(f[n],g[1]);
    for (int i=1;i<n;i++)ans=min(ans,f[i]+g[i+1]+(mf[i]==mg[i+1]?1:0));
    printf("%lld\n",ans);
}

```

---

