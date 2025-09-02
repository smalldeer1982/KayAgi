# 夜店 (Night Market)

## 题目描述

从 $N$ 个夜市中选择其中几个夜市进行游玩，给定：

$A_i$：在夜市 $i$ 玩的乐趣值；

$B_i$：在夜市 $i$ 游玩的时长。

要求：

- 必须按顺序游玩；

- 在夜市游玩的时间是 $0$~$T$；

- 游玩时间不得与时间点 $S$ 重叠；

- 使游玩乐趣值之和 $M$ 尽可能大。

## 说明/提示

**样例解释**

$0$ 时游玩夜市 $1$；

$9$ 时游玩夜市 $2$；

$14$ 时游玩夜市 $4$；
 
$M=8+2+6=16$
 

$10 \%$ 的数据满足：$N \le 20$

$20 \%$ 的数据满足：$S = 0$

全部的数据满足：

$1 \le N, T, B_i \le 3000$

$0 \le S \le T$

$0 \le A_i \le 10^5$

保证输入数据能够制定至少一种游玩方案。

**Source**

[JOI 2011/2012 本選 問題3](https://www.ioi-jp.org/joi/2011/2012-ho-prob_and_sol/2012-ho.pdf#page=7)

**Translate**

By [zerc](https://www.luogu.com.cn/user/581312)

# 题解

## 作者：PR_CYJ (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/AT_joi2012ho3)
# 思路
这道题我们先从最简单的 DP 开始。先不考虑特殊要求，那这道题就是一个很基础的 01 背包。很容易就可以写出转移方程：
$$dp_j=\max(dp_j,dp_{j-b_i}+a_i)$$

接下来考虑特殊要求。因为不能有游玩时间与时间点 $S$ 重合，所以我们只需要让 $j-b_i\ge S$ 或 $j\le S$，所以考虑分成两段进行 DP，此处不需要用两个数组，一个就可以解决。

最后由于游玩时间是 $0\sim T$，所以不能直接输出 $dp_T$，而是要遍历一遍 $dp$ 数组，求出最大值后再输出。
# 代码
- 切勿抄袭！！！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,s,ans=0;
	cin>>n>>m>>s;
	int w[n+10]={},v[n+10]={},dp[m+10]={};
	for(int i=1;i<=n;i++)
		cin>>v[i]>>w[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=s+w[i];j--)
			dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
		for(int j=s;j>=w[i];j--)
			dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
	}
	for(int i=0;i<=m;i++)
		ans=max(ans,dp[i]);
	cout<<ans<<endl;
}
```

---

## 作者：zerc (赞：3)

一个非常裸的背包问题，设 $f_{i,j}$ 表示游玩第 $i$ 个夜市，时间为 $j$ 的最大的兴趣值，不考虑限制条件的话就是：

$$
f_{i,j}=\max(f_{i-1,j}, f_{i-1,j-b_{i}} + a_{i})
$$

考虑限制条件，因为游玩是按顺序的，所以我们考虑分成 $S$ 前与 $S$ 后两部分考虑，后半部分可以倒推一个 $g_{i,j}$，与 $f$ 类似，我们可以得到：

$$
g_{i,j}=\max(g_{i+1,j}, g_{i+1,j-b_{i}} + a_{i})
$$

最后的答案就是：

$$
ans=\max(f_{i-1,s} + g_{i,t-s})
$$

时间复杂度 $O(NT)$。


```cpp
int main() {
    scanf("%d %d %d", &n, &t, &s);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= t; j++) {
            f[i][j]= f[i-1][j];
            if (j - b[i] >= 0) {
                f[i][j] = max(f[i][j], f[i-1][j-b[i]] + a[i]);
            }
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j <= t; j++) {
            g[i][j] = g[i+1][j];
            if (j - b[i] >= 0) {
                g[i][j] = max(g[i][j], g[i+1][j-b[i]] + a[i]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        ans = max(ans, f[i-1][s] + g[i][t-s]);
    }
    printf("%d\n",ans);
}
```

然后你就会喜提最劣解（（（

---

讲一种常数更小的做法：

其实不用那么麻烦，如果满足 $j \le S$ 或 $j - b \ge S$ 就直接更新 $f_j$ 是一样的，所以：

$$
f_{j}=\max(f_{j},f_{j-b}+a)
$$

注意 $j$ 要倒序枚举，防止在前面更新过的状态影响后面的转移。

时间复杂度 $O(NT-\sum B_{i})$。

```cpp
int main() {
    scanf("%d %d %d", &n, &t, &s);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &a, &b);
        for (int j = t; j >= b; j--) {
            if (j <= s || j - b >= s) {
                f[j] = max(f[j], f[j-b] + a);
            }
            ans = max(ans, f[j]);
        }
    }
    printf("%d\n", ans);
}
```

---

## 作者：大眼仔Happy (赞：1)

# 输出答案一定要换行！！！

[题目传送门](https://www.luogu.com.cn/problem/AT_joi2012ho3)

~~来水题解的。~~

用 exlg 跳到的蓝题，一开始没有什么思路。再想想，这不就是一个背包吗？（所以真的是蓝题吗）

考虑没有限制的背包，习惯了滚动的我们可能一写就是这样的：

$$
f_{j}=\max(f_{j},f_{j-b_i}+a_i)
$$

但是这里我们先回到二维的版本。

$$
f_{i,j}=\max(f_{i-1,j},f_{i-1,j-b_i}+a_i)
$$

但是现在加上了一个限制，不能在 $s$ 时刻去夜店，大概就是长这样的：

![](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAKQAAAAuCAYAAACmnrL/AAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAADsMAAA7DAcdvqGQAAAMOSURBVHhe7Zu7jtpAFIatVVahCyVarSIUpaCJREnJo/AIlLwBJY+AlJehpKQLJdtElJQT/45HXDSLx/bMnIP5P+lItqHwGX8cz43MEKIICklUQSGJKigkUYWIkMfj0YzHY5NlWRE4xjVCRISEgNvttjwzxfF0OqWUREZIVMVbICVEJc+NGiHBcDgsj8izokpIQpKbgX5iv98vz0gK7CDyEQaPSYU8nU5mMplcDWhIfOwgEoFiYGc3bGjquycVcrVamfl8Xp6RVFR1kao+T0nSOxkMBuZwOJRnJBVVwqFqanmdJxVS0y/xmfBpdy3TblEMWa/XxRQOGqJpYKKchAHt6YPv92IS/A4g0mw2M/v9vrxyRkPCkvx9/5k8/rz9MN9eXpyf2fj1+rWI719enZ/HChdXhmS/P+IGqp/resKQ5LOHEBM7wr5H8VwSFwtvIWMiXSGfUciqNrfzwhRSgDb5odLg/i+jbj9Xm5CQETmggt77XgwoZE6b/ELcuyYhMfC8fJ1TSAEo5P/VMoh4OfDEtV6vVxynQlxI21eRhEK6V8sWi4VZLpflWRrEhfQZ7cWmTX4hVjOkhUQlxPzw5WrZZrMp9hekRlzIEBWmLW3za7uaIS2kqzqORiOz2+3Ks3RQyJwQ+dlK2QQJIe2UDgLHt3sJpJ4LhcwJlV9TKSWErIJCChIyvyZ9Sgp5hkLmhM6vbp+SQp6hkDkx8quTlzYhJeYfLRQyh0JeI7mDn0LmUMhrJHfwewsZLfIH57yeOO6BjQboE+JV5ssjCylZJLyEjImGCukDXmF4lflQdzkUD0FT4Jm4rqcKFxTyBrzCsLyG3TAuICGqKPKBjNLLoW3Q+EwopAPsgsFuGNzzbWiVEPdbF+SjDQrZEZq0b6eFrPqFUsi41G1fdEnq9H9TEcwSJHdvGY1CxqVO+6IP/Nk/Q6UJZgn6VZASDeMKjb/GLoE29qXOd1PDstURfCWrO1WVGgrZEXyEhIz2X4ZaoZAdoUrIR5ARUMiOcK//jsDnjzCJTyGJKigkUQWFJIow5h+GIElY8hb9bAAAAABJRU5ErkJggg==)

这样画看起来就很显然了，先对前面做一个背包 $f$，然后再对后面做一个背包 $g$。由于要按顺序，所以统计答案的时候枚举边界，背包 $f$ 中只能选择前面的，背包 $g$ 中只能选后面的，这时候状态中 $i$ 的作用就有了，而不能像模板题一样可以被滚掉。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3005;
int inline read()
{
	int num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int n,t,s,a[N],b[N],f[N][N],g[N][N],ans;
int main(){
	n=read();t=read();s=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=t;j++)
		{
			f[i][j]=f[i-1][j];
			if(j>=b[i])f[i][j]=max(f[i][j],f[i-1][j-b[i]]+a[i]);
		}
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=0;j<=t;j++)
		{
			g[i][j]=g[i+1][j];
			if(j>=b[i])g[i][j]=max(g[i][j],g[i+1][j-b[i]]+a[i]);
		}
	}
	for(int i=1;i<=n;i++)ans=max(ans,f[i-1][s]+g[i][t-s]);
	printf("%d\n",ans);
	return 0;
}
```


---

