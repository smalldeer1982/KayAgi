# Intercepted Inputs

## 题目描述

### 题目翻译


为了帮助您准备即将到来的 Codeforces 竞赛，茜特菈莉设置了一个网格问题，并试图通过您的输入流为您提供一个 $n$ 乘 $m$ 的网格。具体来说，您的输入流应包含以下内容：

- 第一行包含 $n$ 和 $m$ 两个整数。- 网格的尺寸。
- 接下来的 $n$ 行分别包含 $m$ 个整数--网格值。

然而，有人截获了你的输入流，将所有给定的整数洗牌后放在一行！现在，一行中有 $k$ 个整数，而你却不知道每个整数原本属于哪一行。你决定自己确定 $n$ 和 $m$ 的值，而不是让茜特菈莉 重新发送输入。

输出茜特菈莉i 可能提供的 $n$ 和 $m$ 的任何可能值

## 样例 #1

### 输入

```
5
3
1 1 2
11
3 3 4 5 6 7 8 9 9 10 11
8
8 4 8 3 8 2 8 1
6
2 1 4 5 3 3
8
1 2 6 3 8 5 5 3```

### 输出

```
1 1
3 3
2 3
4 1
1 6```

# 题解

## 作者：Sakura_Emilia (赞：3)

# Solution

对于每组数据读入的 $k$ 个数，由于有两个数是决定网格的宽度和高度，因此矩形区域的面积一定是 $k-2$。因此只需要检查这 $k$ 个数中，有没有两个数的乘积，恰好为 $k-2$。使用 `map<int, int>` 打个桶即可。

这里特别需要注意矩形区域为正方形的情况，因此在读入 $k$ 个数时，一定要先检查此时是否可以构造，再来记录。`mp[k]++;` 更新要放置在 `mp[(n - 2) / k] > 0` 判断的后面。

# Code

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
using namespace std;

int T, n, k, ans1, ans2;
map<int, int> mp;

inline void solve() {
    cin >> n;
    mp.clear();
    for(int i = 1; i <= n; i++) {
        cin >> k;
        if((n - 2) % k == 0) {
            if(mp[(n - 2) / k] > 0)
                ans1 = k, ans2 = (n - 2) / k;
            mp[k]++;
        }
    }

    cout << ans1 << " " << ans2 << endl;
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
```

---

## 作者：DoubleQLzn (赞：1)

一道简单题，建议评红/橙 ~~vp 时弱智操作导致交了好多发~~。

### Description

原来一个矩阵的数以及长宽 $n$ 和 $m$ 被打乱到一个数列中，求原来的 $n$ 与 $m$。

原题体面较为难懂，建议阅读原题题面 : https://codeforces.com/contest/2037/problem/B。

### Solution

首先考虑什么情况下两个数合法。由于本身已经占了 $2$ 个数，所以实际上，设第一个数为 $x$，第二个数为 $y$，则矩阵其他数数量为 $xy$，所以当 $x$ 与 $y$ 合法时，$xy+2=n$。

问题转化为有多少个双元组 $(a_i,a_j)$ 满足 $a_i\times a_j+2=n$。我们可以想到开一个桶，对于 $a_i$，判断符合要求的 $a_j$ 是否存在即可。

### Code

请勿抄袭。

```cpp
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
int a[200005],f[200005];
int t,n;
void solve()
{
  memset(f,0,sizeof f);
		cin >> n;
		for (int i = 1;i <= n;i++)
		{
			cin >> a[i];
			f[a[i]]++;
		}
		n = n - 2;
		int ans1,ans2;
		for (int i = 1;i <= n + 2;i++)
		{
			if (n % a[i] == 0 && ((a[i] != n / a[i] && f[n / a[i]]) || (a[i] == n / a[i] && f[a[i]] > 1)))
			{
				ans1 = a[i],ans2 = n / a[i];
				break;
			}
		}
		cout << ans1 << ' ' << ans2 << endl;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：WRT_Partisan (赞：1)

# 题解：CF2037B Intercepted Inputs

[题目链接](https://www.luogu.com.cn/problem/CF2037B)

## 题目大意

输入一行 $k$ 个数据，其中包括 $n$ 和 $m$ 以及 $n\times m$ 个数字，需要我们找出 $n$ 和 $m$。如果有多组满足条件的 $n$ 和 $m$，只输出一组即可。

## 解题思路

因为数据中有两个是 $n$ 和 $m$，所以矩阵的数据个数为 $k-2$，即 $n\times m=k-2$。我们将可以整除 $k-2$ 的所有数据加入到 map 中，再对 map 中的每个 $a_i$ 判断 $(k-2)/a_i$ 是否在 map 中。

## 代码

```cpp
/*
 * @FilePath: \c++\CF2037B.cpp
 * @Author: WRT_Partisan
 * @Date: 2024-11-23 20:22:44
 */
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef unsigned long long ull;
int t, k, a, ans1, ans2;
map<int, int> mp;
signed main()
{
    scanf("%lld", &t);
    while (t--)
    {
        mp.clear();
        scanf("%lld", &k);
        for (int i = 1; i <= k; i++)
        {
            scanf("%lld", &a);
            if ((k - 2) % a == 0)
                mp[a]++;
        }
        for (auto i : mp)
            if ((i.first != (k - 2) / i.first && mp.count((k - 2) / i.first)) || (i.first == (k - 2) / i.first && i.second >= 2))
                ans1 = i.first, ans2 = (k - 2) / i.first;
        printf("%lld %lld\n", ans1, ans2);
    }
    return 0;
}
```

---

## 作者：Jason_Ming (赞：0)

### 思路

题意很简单，从一个长度为 $k$ 的序列中选出两个数 $n$ 和 $m$，使得剩下的 $k-2$ 个数可以放进大小为 $n\times m$ 的矩阵中。

对于序列中的每个数 $a_i$，当 $a_i$ 作为 $n$ 的时候，$m$ 的大小就应该是 $(k-2)\div a_i$。前提条件是 $a_i\mid (k-2)$。

我们可以枚举 $a_i$，并判断符合条件的 $m$ 是否存在于序列当中。有人用 ```map``` 来记录每个数出现的次数，但是考虑到 $a_i$ 最大不超过 $2 \cdot 10^5$，完全可以直接使用数组以优化时间复杂度。

需要注意的是，当 $a_i=(k-2)\div a_i$ 的时候，需要判断 $(k-2)\div a_i$ 是否出现了至少两次，而不是是否出现过。

时间复杂度 $O(k)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int t,k;
int a[200005],f[200005];

int main()
{
	cin>>t;
	while(t--)
	{
		memset(f,0,sizeof(f));//多测要清空
		cin>>k;
		for(int i=1;i<=k;i++)
		{
			cin>>a[i];
			f[a[i]]++;
		}
		for(int i=1;i<=k;i++)
		{
			if((k-2)%a[i]==0&&f[(k-2)/a[i]])
			{
				if((k-2)/a[i]!=a[i]&&f[(k-2)/a[i]])
				{
					cout<<a[i]<<" "<<(k-2)/a[i]<<endl;
					break;
				}
				if((k-2)/a[i]==a[i]&&f[a[i]]>=2)
				{
					cout<<a[i]<<" "<<(k-2)/a[i]<<endl;
					break;
				}
			}
		}
	}
}
```

**拒绝抄袭，从我做起。**

---

## 作者：_dbq_ (赞：0)

## 前言
[题目传送门](https://www.luogu.com.cn/problem/CF2037B)

## 思路
考虑暴力枚举 $n$ 和 $m$，使用桶数组记录每个数字的出现个数，判断在输入中是否包含 $n$ 和 $m$。

我们输入 $k$ 个数，其中包含 $n$、$m$ 和 $n \times m$ 个数，可得 $n \times m=k-2$。

具体内容见代码

## 代码

```cpp
/* 2024-11-22-22:50 by _dbq_ */
#include<iostream>
#include<string.h>
#define cint const int 
using namespace std;
cint N=2e5+10;
int a[N],tot[N];//a记录数据，tot是桶数组

inline int read(){//快读优化
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve()
{
    int k=read();
    for(int i=1;i<=k;i++){
        a[i]=read();
        tot[a[i]]++;//桶数组标记
    }
    int n=k;
    k-=2;//把n、m删去
    for(int i=1;i<=n;i++)//枚举每一个a[i]
        if(k%a[i]==0//判断k/a[i]是否是个整数
        &&(a[i]*a[i]!=k&&tot[k/a[i]]//如果k/a[i]与a[i]不等，我们需要一个k/a[i]和一个a[i] 
        ||a[i]*a[i]==k&&tot[a[i]]>=2)){//否则，我们需要两个a[i]
            cout<<a[i]<<" "<<k/a[i]<<'\n';//输出
            return ;//打断
        }
}
int main()
{
    #ifdef dbq
    freopen("CF2037B.in","r",stdin);
    freopen("CF2037B.out","w",stdout);
    #endif
    int T=read();//多组数据
    while(T--){
        solve();
        memset(tot,0,sizeof(tot));//记住清空桶数组
    }
    return 0;
}
```

---

## 作者：wuyouawa (赞：0)

### 题目大意

给你一个整数 $k$ 和一个 $k$ 个数组成的数组，要求从里面找到两个数 $n$ 和 $m$，使得这个数组除了 $n$ 和 $m$ 以外还有 $n \times m$ 个数。

### 思路

由于 $n$ 和 $m$ 一共 $2$ 个数，再加上 $n \times m$ 个数是 $k$ 个数，说明：

$$n \times m+2=k$$

移项得 $n \times m=k-2$。

那么只需要枚举 $k-2$ 的因数，看有**哪一对**因数是在数组中出现过的即可。

枚举因数可以用 sqrt 优化，当然都一样。

记得用 scanf，数据比较大。

### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,k,a,y[200005];
int main(){
	scanf("%d",&t);
	while(t--)
	{
		 scanf("%d",&k);
		 for(int i=1;i<=200000;i++)  y[i]=0;//重置 
		 for(int i=1;i<=k;i++)  scanf("%d",&a),y[a]++;//计数 
		 for(int i=1;i<=sqrt(k-2);i++)//暴力找n
		 {
		 	 if((k-2)%i==0&&y[i]>0&&y[(k-2)/i]>0)//注意积要是n的倍数 
		 	 {
		 	 	printf("%d %d\n",i,(k-2)/i);//积除以n就是m 
		 	 	break;//只用一个解
		 	 }
		 }
	}
	return 0;
} 
```

---

## 作者：linjinkun (赞：0)

简单题。

首先输入的数据中肯定有两个数是 $n$ 和 $m$，所以我们要先将数量减 $2$，得出原输入的网格中有多少个数，所以问题就转化为从 $k$ 个数中随便选两个数，使得这两个数的乘积是 $k-2$，于是就好做了，我们开一个桶来记录每种数出现次数，设这个桶是 $num$，遍历我们要选的第一个数 $a_i$，求 $num_{(k-2) \div a_i}$ 是否大于 $0$，也就是这第二个数在输入中是否存在，如果存在就直接输出 $a_i$ 和 $(k-2) \div a_i$，因为这就是一组合法的 $n$ 和 $m$。

注意事项：

- 多测不清空，爆零两行泪。
- 我们每遍历一个 $a_i$ 时，都需要使 $num_{a_i}$ 减 $1$，因为代表我们已经用了这个数，查询完之后在加回来。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int num[N];
int a[N];
signed main()
{
	int _;
	scanf("%d",&_);
	while(_--)
	{
		memset(num,0,sizeof(num));//记得清空
		int n;
		scanf("%d",&n);//这里的n就是题目的k
		for(int i = 1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			num[a[i]]++;//统计
		}
		for(int i = 1;i<=n;i++)
		{
			if((n-2)%a[i] == 0)//首先得满足a_i是n的因数
			{
				num[a[i]]--;//这里得减少
				if(num[(n-2)/a[i]])//判断第二个数能否取出
				{
					printf("%d %d\n",a[i],(n-2)/a[i]);
					break;//题目只需要输出一组，打印完一组后，就退出
				}
				num[a[i]]++;//查询完后在加回来
			}
		}
	}
	return 0;
}
```
[AC 证据。](https://codeforces.com/contest/2037/submission/292331471)

---

## 作者：huanglihuan (赞：0)

#### 题意
有一个 $n\times m$ 的矩阵，其中的所有数均被打乱（包括 $n,m$），找到 $n,m$。
#### 思路
发现矩阵中有 $k-2$ 个数，因此枚举 $k-2$ 的因数，看看乘积是否为 $k-2$，可以开一个桶来存，单组时间复杂度 $O(\sqrt k)$。
#### 代码

```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 998244353
#define MOD 1000000007
using namespace std;
const int N = 2e6 + 5,maxn = 3e3 + 5;
inline int read ()
{
	int x = 0;
	bool f = 1;
	char c = getchar ();
	while (c < '0' || c > '9') f = (c == '-' ? !f : f),c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return (f ? x : -x);
}
inline void write (int x)
{
	if (x < 0) putchar ('-'),x = -x;
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
	return ;
}
signed main ()
{
	int T;
	cin >> T;
	while (T --)
	{
		int k;
		cin >> k;
		int bucket [N] = {0};
		for (int i = 1;i <= k;i ++)
		{
			int x;
			cin >> x;
			bucket [x] ++;
		}
		k -= 2;
		for (int i = 1;i <= sqrt (k);i ++)
		{
			if (k % i == 0)
			{
				if (bucket [i] > 0 && bucket [k / i] > 0)
				{
					cout << i << ' ' << k / i << endl;
					break;
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：_xguagua_Firefly_ (赞：0)

~~原题好评~~

### 分析

输入每个数的时候开个数组记录出现的次数，然后将 $k$ 减去 $2$，现在 $k$ 就是 $n \times m$ 矩阵的元素的个数。然后遍历数组，设当前元素为 $i$，将数组中 $i$ 的个数减去 $1$，如果 $i \mid k$，则判断 $\frac{k}{i}$ 个数是否为 $0$，若不为 $0$，则这是一组符合的解。

### Code

[AC 记录](https://codeforces.com/contest/2037/submission/292147445)

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int t;
int k,a;
map<int,int> apr;
signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> t;
    while(t--)
    {
        apr.clear();
        cin >> k;
        for(int i = 1;i <= k;i++)
        {
            cin >> a;
            apr[a] += 1;
        }
        k -= 2;
        for(auto it:apr)
        {
            if(k % it.first == 0)
            {
                it.second--;
                if(apr[k / it.first])
                {
                    cout << it.first << " " << (k / it.first) << "\n";
                    break;
                }
                it.second++;
            }
        }
    }
}
```

---

