# Coins

## 题目描述

银国的人们使用硬币。他们有面值分别为 $A_1, A_2, A_3, \dots, A_n$ 的硬币。有一天，托尼打开了他的储蓄罐，发现里面有一些硬币。他决定去附近的商店购买一块非常漂亮的手表。他想要支付准确的价格（不找零），而他知道手表的价格不会超过 $m$ 。但他不知道手表的确切价格。

你需要编写一个程序，读取 $n$、$m$、$A_1, A_2, A_3, \dots, A_n$ 以及对应的数量 $C_1, C_2, C_3, \dots, C_n$ （表示托尼拥有的每种面值的硬币数量），然后计算托尼可以用这些硬币支付的价格数量（从 1 到 $m$ 的所有价格）。

## 样例 #1

### 输入

```
3 10
1 2 4 2 1 1
2 5
1 4 2 1
0 0```

### 输出

```
8
4```

# 题解

## 作者：wandereman (赞：5)

[快速传送](https://www.luogu.com.cn/problem/P10973)
[更好食用](https://www.luogu.com.cn/article/7pt8kill)
## 题意
一道普通的背包题（多重背包）。
## 思路
先给出一个 01 背包的动态规划式。
```cpp
dp[j] = max (dp[j],dp[j - w[i]] + v[i]);
```
随后只需简单操作，便可得出以下动态规划式。
```cpp
for(int j=m; j>=c[i]*a[i]; j--){
	if(dp[j-c[i]*a[i]]){
		dp[j]=1;
	}
}	
```
## 重头戏 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[105],c[105];
bool dp[100005];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while(cin>>n>>m){
		if(!n&&!m)break;
		for(int i=1; i<=n;i++)cin>>a[i];
		for(int i=1; i<=n; i++)cin>>c[i];
		memset(dp,0,sizeof dp);
		dp[0]=1;
		for(int i=1; i<=n; i++){
			for(int j=1; j<=c[i]; j*=2){
				int s=min(j,c[i]);
				c[i]-=s;
				for(int k=m; k>=s*a[i]; k--)
					if(dp[k-s*a[i]])dp[k]=1;}
			if(c[i]){
				for(int j=m; j>=c[i]*a[i]; j--){
					if(dp[j-c[i]*a[i]]){
						dp[j]=1;
					}
				}	
			}	
		}
		int ans=0;
		for(int i=1; i<=m; i++){
			ans+=dp[i];
		}	
		cout<<ans<<'\n';
	}
	return 0;
}
```
## 尾声
这只是一道模板题，但是却是基础，拒绝抄题解。

---

## 作者：OIer_ACMer (赞：4)

# 题目解析：

首先，~~为啥这道题只有一个点？~~

好，回归正题，我们首先可以知道这道题是一道多重背包动态规划，于是，我们直接通过板子敲一个多重背包，第一层枚举第几个物品，第二层枚举物品数量多少，最后一层枚举背包容量，最终，若 $dp_i$ 的值不为 $0$，则进行计算，代码如下（我还指望着三层循环能过）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int a[1000009], c[1000009];
int dp[1000009];
int main()
{
    while (1)
    {
        cin >> n >> m;
        if (n == 0 && m == 0)
        {
            return 0;
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> c[i];
        }
        for (int i = 1; i <= m; i++)
        {
            dp[i] = 0;
        }
        dp[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= c[i]; j++)
            {
                for (int k = m; k >= a[i]; k--)
                {
                    if (dp[k - a[i]])
                    {
                        dp[k] = 1;
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= m; i++)
        {
            if (dp[i])
            {
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

不是意外地超时了，这时，我们根据方程式中 $dp_k$ 要存在的要求是 $dp_{k - a[i]}$ 以及 $dp_{k - j *a_i}$ 之类的减去新增钱数的状态存在才能符合条件，很明显，这就是动态规划的**整体考虑思想**。

那么，我们可以根据这一点用数组 $g_j$ 存储 $j$ 状态下有多少种状态，每次在计算时，我们先在 $g$ 数组中找 $g_{j - a_i}$ 的代价是否比 $c_i$ 小，也就是此时能否进行转移，减去一维的枚举，优化了时间复杂度。

# 正解代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int a[1000009], c[1000009];
int dp[1000009], g[1000009];
int main()
{
    while (1)
    {
        cin >> n >> m;
        if (n == 0 && m == 0)
        {
            return 0;
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> c[i];
        }
        for (int i = 1; i <= m; i++)
        {
            dp[i] = 0;
        }
        dp[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            // for (int j = 1; j <= c[i]; j++)
            // {
            //     for (int k = m; k >= a[i]; k--)
            //     {
            //         if (dp[k - a[i]])
            //         {
            //             dp[k] = 1;
            //         }
            //     }
            // }
            for (int j = 0; j <= m; j++)
            {
                g[j] = 0;
            }
            for (int j = a[i]; j <= m; j++)
            {
                if (!dp[j] && dp[j - a[i]] && g[j - a[i]] < c[i])
                {
                    dp[j] = 1;
                    // g[j]++;
                    g[j] = g[j - a[i]] + 1;
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= m; i++)
        {
            if (dp[i])
            {
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Vitamin_B (赞：4)

更新：第一种暴力方法已经被我自己 Hack 了。
# 前言
什么？多重背包模板竟然是绿题？
# 思路
这题是一道多重背包的模板题。

不难想到可以把这 $c_i$ 个同品种的商品拆开，当成 $c_i$ 个每种只有 $1$ 个的不同品种的商品做 01 背包，这样便是第一种解法了，~~已经可以 AC 了~~。

---

但上面那种方法只适用于小数据，大数据就会 T 飞。众所周知，例如 `1 2 4 8 16` 的数列就可以凑出 $1\sim31$ 的所有数。所以，我们只要把每种商品先按 $2^0\times a_i,2^1\times a_i,2^2\times a_i,\dots$ 的方法拆成一些商品，直到 $c_i$ 不够用了再把剩下的那一点东西变成一个大小为 $[c_i-(2^0+2^1+2^2+\dots)]\times a_i$ 的商品。然后就是 01 背包啦。

# 小窍门
使用 bitset 代替你的 bool 数组，不仅码量可以减少，还能为你的代码提速，有机会抢到最优解哦！

下面介绍这题中 bitset 的用法：
1. 定义。`bitset<114514>dp` 就等价于 `bool dp[114514]`。
2. `dp<<114` 表示数组中的每一位统一向左偏移 $114$ 位，低位自动补 $0$，高位溢出部分自动省略。
3. `dp|dpp` 表示对每一位进行或操作，前提条件 $dp$ 和 $dpp$ 的大小相等。
4. 在这题中，若想进行一次大小为 $a$ 的硬币转移，可以直接使用 `dp|=dp<<a`。
5. `dp.reset` 表示将 $dp$ 的每一位重置为 $0$。

# 代码
# 方法 1 的代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, m, a[105], c, s;
bitset <100005> dp;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	while (cin >> n >> m, n | m) {
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		s = 0, dp.reset (), dp[0] = 1;
		for (int i = 0; i < n; ++ i) {
			cin >> c;
			while (c --)
				dp |= dp << a[i];
		}
		for (int i = 1; i <= m; ++ i)
			if (dp[i])
				++ s;
		cout << s << '\n';
	}
	I AK IOI
}
```

# 方法 2 的代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, m, a[105], c, s;
bitset <100005> dp;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	while (cin >> n >> m, n | m) {
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		s = 0, dp.reset (), dp[0] = 1;
		for (int i = 0; i < n; ++ i) {
			cin >> c;
			for (int j = 0; c > (1 << j); ++ j)
				dp |= dp << (a[i] << j), c -= 1 << j;
			dp |= dp << (a[i] * c);
		}
		for (int i = 1; i <= m; ++ i)
			if (dp[i])
				++ s;
		cout << s << '\n';
	}
	I AK IOI
}
```

---

## 作者：return_third (赞：1)

也是用小号写了一篇题解。

# 思路

明显的多重背包。先二进制拆分。令 $dp_i$ 为是否能达到 $i$ 的重量，初始值 $dp_0$ 设为 `true`，然后跑一遍 01 背包板。第一层循环枚举第 $i$ 件物品，第二层循环枚举可取的重量 $j$，状态转移方程就是 $dp_j=dp_j \lor dp_{j-a_i}$。最后统计即可。

# 代码实现

给出代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+5;
int n,m;
int a[105];
int cnt,v[N];
bool dp[N];
void solve()
{
    cnt=0;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        int c,p=1;
        scanf("%d",&c);
        while(c>=p)
        {
            cnt++;
            v[cnt]=a[i]*p;
            c-=p;
            p<<=1;
        }
        if(c>0)
        {
            cnt++;
            v[cnt]=a[i]*c;
        }
    }
    memset(dp,false,sizeof(dp));
    dp[0]=true;
    for(int i=1;i<=cnt;i++)
        for(int j=m;j>=v[i];j--)
            dp[j]=dp[j]||dp[j-v[i]];
    int ans=0;
    for(int i=1;i<=m;i++)
        if(dp[i])
            ans++;
    printf("%d\n",ans);
}
int main()
{
	while(~scanf("%d%d",&n,&m)&&n&&m)
        solve();
    return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/220828625)

---

## 作者：MafuyuQWQ (赞：1)

## 题意

> 给定 $ n $ 种硬币，每个硬币能用若干次，价值不等，选出若干个相加，问 $ 1 \sim m $ 之间能被
拼成的面值有几个。

## Solution

不难看出这道题考察的是多重背包，可以用二进制拆分转化为 01 背包。（不懂可以看[这个](https://blog.csdn.net/hnjzsyjyj/article/details/109363826)）  

然而普通的二进制优化多重背包会 TLE，所以考虑如何优化。

一般是用数据结构优化的，不难想到用单调队列优化。

可以增设一个辅助数组 $ g $，设 $ g_{i,j} $ 表示 $ j $ 到 $ j - s_i \times v_i $ 这 $ s_i + 1 $ 个数中是否有 $ f $ 的值为 $ 1 $ 即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, m;
int f[N], g[N];
int v[N], s[N];

int main()
{
    while (cin >> n >> m, n || m)//多组数据
    {
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; i ++ ) cin >> v[i];
        for (int i = 1; i <= n; i ++ ) cin >> s[i];

        f[0] = 1;//初始化
        for (int i = 1; i <= n; i ++ )
        {
            memset(g, 0, sizeof g);
            for (int j = v[i]; j <= m; j ++ )
                if (!f[j] && f[j - v[i]] && g[j - v[i]] < s[i])//判断条件
                {
                    g[j] = g[j - v[i]] + 1;
                    f[j] = 1;//DP
                }
        }
        int ans = 0;
        for (int i = 1; i <= m; i ++ ) ans += f[i];//答案统计

        cout << ans << '\n';
    }

    return 0;
}
```

---

## 作者：__DayLight__ (赞：1)

## 前言

写得挺好的[多重背包](https://blog.csdn.net/windfriendc/article/details/123892024)。

## 思路

如上，多重背包但二进制优化。

可以将 $m$ 理解为背包容量，$n$ 理解为物品数量，$A_i$ 理解为物品价值，$C_i$ 理解为物品数量，很清晰地就能明白。

状态：$dp_i$ 表示能否支付价格 $i$。

对于第 $i$ 件物品，用 $j$ 枚举前 $i-1$ 件物品能支付的价格，再用 $k$ 枚举 $a_i$ 的数量，则价格 $j+k \times a_i$ 能被支付。

```cpp

		dp[0]=1;//0 元用 0 个硬币支付
		for(int i=1; i<=n; i++)
            for(int j=m; j>=0; j--)
                if(dp[j])//价格 j 能被支付
                    for(int k=1; k<=c[i]&&j+k*a[i]<=m; k++)
                        dp[j+k*a[i]]=1;//记为能被支付
        
```
但很明显会 [TLE](https://www.luogu.com.cn/record/174591083)。

所以我们考虑二进制优化。

简单解释一下（同样取自上面推荐的文章）：

第 $i$ 种物品我们有 $10$ 个。

那么我们用二进制怎么表示这个 $10$ 呢，$10=1+2+4+3$。

为什么这么表示？而不是 $8 + 2$？ 

因为如果是 $8+2$ 件的话，我们如果仅仅想拿 $5$ 件，就无法表示了。
```cpp
		dp[0]=1;
		for(int i=1; i<=n; i++)//同样枚举
		{
			for(int j=1; j<=c[i]; j*=2)//用二进制数表示物品数量
			{
				int s=min(j,c[i]);//注意不要取多了
				c[i]-=s;
				for(int k=m; k>=s*a[i]; k--)
					if(dp[k-s*a[i]])dp[k]=1;
			}
			if(c[i])//只是二进制可能会剩下，把剩下的看成一个整体
				for(int j=m; j>=c[i]*a[i]; j--)
					if(dp[j-c[i]*a[i]])dp[j]=1;
		}
```
这样就能 [AC](https://www.luogu.com.cn/record/174591250) 了。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[105],c[105];
bool dp[100005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	while(cin>>n>>m)
	{
		if(!n&&!m)break;
		for(int i=1; i<=n; i++)
			cin>>a[i];
		for(int i=1; i<=n; i++)
			cin>>c[i];
		memset(dp,0,sizeof dp);//注意初始化 
		dp[0]=1;
		for(int i=1; i<=n; i++)
		{
			for(int j=1; j<=c[i]; j*=2)
			{
				int s=min(j,c[i]);
				c[i]-=s;
				for(int k=m; k>=s*a[i]; k--)
					if(dp[k-s*a[i]])dp[k]=1;
			}
			if(c[i])
				for(int j=m; j>=c[i]*a[i]; j--)
					if(dp[j-c[i]*a[i]])dp[j]=1;
		}
		int ans=0;
		for(int i=1; i<=m; i++)
			ans+=dp[i];
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：_luogu_huowenshuo_ (赞：0)

## 思路

经典的背包问题。

先用二进制优化遍历一下，然后双重循环处理 01 背包（`dp[j]|=dp[j-w[i]];`），最后输出有多少 `dp[i]==1`。

## 警示后人
1. 多测要清空。
2. 别忘了 $0$ 元也可以支付。

## 代码

$m$ 为背包容量，$n$ 为物品数量，$a_i$ 为物品价值，$c_i$ 为物品数量。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[11414],c[11414],cnt,ans,w[114514],v[114514],n,m;
bool dp[114514];
int main()
{
    while(cin>>n>>m)
    {
        if(m==0&&m==0)return 0;
        ans=cnt=0;
    	memset(dp,0,sizeof dp);
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<=n;i++)
            cin>>c[i];
        for(int i=1;i<=n;i++)
        {
            int k=1;
            while(k<=c[i])
            {
                w[++cnt]=a[i]*k;
                c[i]-=k;
                k*=2;
            }
            if(c[i])
            {
                w[++cnt]=a[i]*c[i];
            }
        }
        dp[0]=1;
        for(int i=1;i<=cnt;i++)
            for(int j=m;j>=w[i];j--)
                dp[j]|=dp[j-w[i]];
        for(int i=1;i<=m;i++)
            if(dp[i]==1)
                ans++;
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

