# Removing Smallest Multiples

## 题目描述

You are given a set $ S $ , which contains the first $ n $ positive integers: $ 1, 2, \ldots, n $ .

You can perform the following operation on $ S $ any number of times (possibly zero):

- Choose a positive integer $ k $ where $ 1 \le k \le n $ , such that there exists a multiple of $ k $ in $ S $ . Then, delete the smallest multiple of $ k $ from $ S $ . This operation requires a cost of $ k $ .

You are given a set $ T $ , which is a subset of $ S $ . Find the minimum possible total cost of operations such that $ S $ would be transformed into $ T $ . We can show that such a transformation is always possible.

## 说明/提示

In the first test case, we shall not perform any operations as $ S $ is already equal to $ T $ , which is the set $ \{1, 2, 3, 4, 5, 6\} $ .

In the second test case, initially, $ S = \{1, 2, 3, 4, 5, 6, 7\} $ , and $ T = \{1, 2, 4, 7\} $ . We shall perform the following operations:

1. Choose $ k=3 $ , then delete $ 3 $ from $ S $ .
2. Choose $ k=3 $ , then delete $ 6 $ from $ S $ .
3. Choose $ k=5 $ , then delete $ 5 $ from $ S $ .

The total cost is $ 3+3+5 = 11 $ . It can be shown that this is the smallest cost possible.

In the third test case, initially, $ S = \{1, 2, 3, 4\} $ and $ T = \{\} $ (empty set). We shall perform $ 4 $ operations of $ k=1 $ to delete $ 1 $ , $ 2 $ , $ 3 $ , and $ 4 $ .

In the fourth test case, initially, $ S = \{1, 2, 3, 4\} $ and $ T = \{3\} $ . We shall perform two operations with $ k=1 $ to delete $ 1 $ and $ 2 $ , then perform one operation with $ k=2 $ to delete $ 4 $ .

## 样例 #1

### 输入

```
6
6
111111
7
1101001
4
0000
4
0010
8
10010101
15
110011100101100```

### 输出

```
0
11
4
4
17
60```

# 题解

## 作者：FFTotoro (赞：8)

本题需要使用类似埃氏筛的做法。

很显然，一个数如果需要被删除，那么最小的代价 $k$ 就是它不在集合 $T$ 内的**最小质因子**。

知道这一点就很好做了，枚举 $[1,n]$ 中的所有正整数，如果 $T$ 中没有就可以用它消去 $S$ 中需要删除的所有数，并且给已经删掉的数打上标记即可。

这样一直做下去，我们就可以解决问题了。

放代码：

```cpp
#include<iostream>
#include<vector>
using namespace std;
int main(){
    ios::sync_with_stdio(false);
    int t; cin>>t;
    while(t--){
        int n; long long c=0; string s; cin>>n>>s;
        vector<bool> b(n);
        for(int i=1;i<=n;i++){
            if(!(s[i-1]&1)){
                if(!b[i-1])c+=1ll*i;
                for(int j=2;i*j<=n;j++){
                    if(!(s[i*j-1]&1)){
                        if(!b[i*j-1])c+=1ll*i,b[i*j-1]=true;
                    }
                    else break;
                }
            }
        }
        cout<<c<<endl;
    }
    return 0;
}
```

---

## 作者：Dregen_Yor (赞：3)


[更好的阅读体验](http://dregen-yor.123ds.tk/index.php/2022/10/16/cf1734c/)。

[题目传送门。](https://www.luogu.com.cn/problem/CF1734C)

# 题意

给定一个集合 $S$，这个集合中包括 $1 \sim n$ 这 $n$ 个正整数，你可以进行若干次操作将这个集合 $S$ 变成指定的集合 $T$，每次操作可以选定一个正整数 $k$ 并将集合 $S$ 中最小的 $k$ 的倍数删去，每次操作的代价为 $k$，求将集合 $S$ 变为 $T$ 的最小代价。

# 思路

这题的思路是个典型的筛法，类似于**埃式筛**，枚举每个 $k$，如果 $k$ 可以删去他的最小倍数，就让 $k$ 一直操作，知道不能操作为止，同时统计已经删去的元素的个数，注意要把已经删去的数打上标记，防止重复计算。

我们从 $1$ 开始遍历，这样根据贪心的思想，得到的答案一定是最优的。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,ans,sum;
bool v[1000010];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		sum=ans=0;
		memset(v,0,sizeof(v));
		string T;
		cin>>T;
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j+=i){
				if(T[j-1]=='1'){
					if(!v[j]){
						sum++;
					}
					v[j]=1;
					break;
				}
				else{
					if(!v[j]){
						sum++;
						ans+=i;
					}
					v[j]=1;
				}
				if(sum==n){
					break;
				}
			}
		}
		printf("%lld\n",ans);
	}	
	return 0;
}
```




---

## 作者：Cczzyy20150005 (赞：3)

## 题目描述
有一个 $n$ 个元素的集合 $S$，每次选取一个正整数 $k$，删除 $S$ 中 $k$ 的最小倍数，这样一次操作价值为 $k$。

求花最小代价，最终使 $S$ 变为 $T$，$T$ 是 $S$ 的一个子集。
## 思路
这是一道**贪心** (有点像埃氏筛)。

首先，可以知道，每次选的 $k$ 一定是最后不在 $T$ 里的。  
每次用最小的 $k$ 去删数字，花的代价最小。  

于是就可以枚举 $k$，判断 $k$ 最后在不在 $T$ 里。  
如果不在，就可以每次加 $k$ 向后删，直到删到这个数为 $T$ 的元素为止。  
复杂度: $O(n$ $\log$ $n)$。

**细节**：
- 删过的元素不用再删了，所以用一个数组保存某数有没有被删。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int a[2000001];
bool vis[2000001];
void solve(){
	int n;
	int ans=0;
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%1lld",&a[i]),vis[i]=1;
	for(int i=1;i<=n;i++){//枚举
		if(a[i]==0){
			int now=i;
			while(a[now]!=1&&now<=n){//现在这个now不在T里
				if(vis[now]==1)ans+=i;//不能重复算
				vis[now]=0;
				now+=i;
			}
		}
	}
	printf("%lld\n",ans);
}
signed main(){
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：litachloveyou (赞：3)

这个题的思路有点类似于质数筛法里面的埃氏筛。

首先，对于每一个要被删除的数，肯定是用它的最小倍数去删除它花费最少。

所以，我们从第一位也就是从 $1$ 开始遍历，当遇到一个要删除的数时，用它去删除它的倍数这样肯定是最优的。

需要注意的是，每一次删除的**是当前倍数的最小值**。所以当我们枚举倍数遇到不用删的数时就要停止了，并且枚举时还要对已经删掉的数打上标记，防止重复计算。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
char s[N];
int num[N];
void solve()
{
	int n;
	scanf("%d\n%s", &n, s+1);
	fill(num + 1, num + n + 1, 0);
	ll ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (s[i] == '0')
		{
			if (!num[i])ans += i, num[i] = 1;
			for (int j = i + i; j <= n; j += i)
			{
				if (s[j] == '0')
				{
					if(!num[j])ans += i;
					num[j] = 1;
				}
				else
					break;
			}
		}
	}
	printf("%lld\n", ans);
}
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```


---

## 作者：Ferm_Tawn (赞：2)

题目传送门：[CF1734C](https://www.luogu.com.cn/problem/CF1734C)

看题目可知用 $Θ(n)$ 或 $Θ(n \log n)$ 的算法来做。

方便起见，我们把 $s$ 数组的值存在 $a$ 数组里。

一波操作：

- 从大到小枚举 $k$，再枚举 $k$ 的倍数：

  - 若这个数不需要被删除，而目前 $k$ 的倍数是这个数，故退出循环。
  
  - 否则将这个数的转换费用设为 $k$，可以保证费用在更新时会变小。
  
- 最后再把所有需要被删除的数的最小费用累加起来即可。

总复杂度为 $n(1 + \dfrac{1}{2} + \dfrac{1}{3} + \cdots + \dfrac{1}{n}) = Θ(n \log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t , n;
long long ans;
int a[1000005] , cost[1000005];
string s;
int main(){
	cin >> t;
	while(t--){
		ans = 0;
		cin >> n;
		cin >> s;
		for(int i = 0 ; i < n ; i++) a[i + 1] = (s[i] == '1');
		for(int i = n ; i >= 1 ; i--){
			for(int j = i ; j <= n ; j += i){
				if(a[j]) break;
				cost[j] = i;
			}
		}
		for(int i = 1 ; i <= n ; i++){
			if(!a[i]) ans += cost[i];
		}
		cout << ans << endl;
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

思路：贪心，有点类似于质数筛里面的埃氏筛。首先，枚举每个 $k$，肯定是 $k$ 的最小倍数去删除它花费最少。如果 $k$ 可以删除它的最小倍数，就让它一直去操作，直到不能操作为止。再同时统计已经删去的元素的个数，为防止重复计算，我们要把已经删去的数打上标记。于是我们利用贪心思想从第一位也就是从 $1$ 开始遍历，当遇到一个要删除的数时，用它去删除它的倍数这样肯定是最优的。

---

## 作者：Allanljx (赞：1)

## 题意
给定一个集合 $S$，其中包含 $1\sim n$ 这 $n$ 个数，再给定一个集合 $T$。你可以进行多次操作来将 $S$ 变成 $T$，一次操作可以选择一个正整数 $k$ 并将最小的满足是 $k$ 的倍数并且在集合 $S$ 中的元素删除，删除的代价为 $k$。问将 $S$ 变为 $T$ 的最小代价。
## 思路
拿一个 vector 记录第 $i$ 个数可以被哪些数删除（初始第 $i$ 个数只能用 $i$ 删除），然后从小到大枚举不在集合 $T$ 中的数，每个数 $x$ 都可以用 vector 中最小的数来删除，当 $x$ 被删除后原本能用于删除 $x$ 的每个数 $y$ 都可以被用于删除 $x+y$，不难发现每个 $y$ 最多被枚举 $\dfrac{n}{y}$ 次，所以总的时间复杂度大约是 $\Theta(n\log_2{n})$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,ans;
string s;
vector<int>c[1000005];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) c[i].clear();
		for(int i=1;i<=n;i++)
		{
			c[i].push_back(i);
		}
		cin>>s;
		ans=0;
		for(int i=1;i<=s.size();i++)
		{
			if(s[i-1]=='0')
			{
				int minn=1e9;
				for(int j=0;j<c[i].size();j++)
				{
					int x=c[i][j];
					if(i+x<=n) c[i+x].push_back(x);
					minn=min(minn,x);
				}
				ans+=minn;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：dengruijie2 (赞：0)

本题需要使用类似埃氏筛的做法。

很显然，一个数如果需要被删除，那么最小的代价 $k$ 就是它不在集合 $T$ 内的最小质因子。

知道这一点就很好做了，枚举 $[1,n]$ 中的所有正整数，如果 TT 中没有就可以用它消去 $S$ 中需要删除的所有数，并且给已经删掉的数打上标记即可。

这样一直做下去，我们就可以解决问题了。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int T;
string t;
bool f[1000005];

signed main(){
	cin >> T;
	while(T--){
		int n, sum = 0;
		cin >> n >> t;
		memset(f, 0, sizeof(f));
		t = " " + t;
		for (int i = 1; i <= n; i++){
			if (t[i] == '1') continue;
			for (int j = i; j <= n; j += i){
				if (f[j] == 0 && t[j] == '0'){
					sum += i;
					f[j] = 1;
				}
				else if (t[j] == '1') break;
			}
		}
		cout << sum << '\n';
	}
	return 0;
}


```

---

## 作者：wei2013 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1734C)

## 思路：
一道用了**埃氏筛**思想的贪心。

首先，每次删掉的 $k$ 一定不在结果字符串里面，而只要每次删的最小，所需的代价也就最小。
然后就可以枚举 $k$，判断 $k$ 最后在不在结果字符串里。如果不在，就可以每次加 $k$ 向后删，每次都删掉 $k$ 的倍数，直到删到这个数为结果字符串的元素为止，为防止重复计算，需打上标记，进行判断，这样就能做到一定最优，这也就是**埃氏筛**思想。

时间复杂度 $\mathcal{O(n\log n)}$，足以通过题目了。
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
bool flag[2000005];
int main(){
    int t;
	cin>>t;
    while(t--){
        int n;
		long long ans=0;
		string s;
		cin>>n>>s;
		memset(flag,1,sizeof(flag));
        for(int i=1;i<=n;i++){
			if(s[i-1]=='0'){
				for(int j=i;j<=n && s[j-1]!='1';j+=i){
					if(flag[j]){
						ans+=i;
					}
					flag[j]=0;
				}
			}
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：CodingOIer (赞：0)

## CF1734C Removing Smallest Multiples

### 思路分析

一道贪心题，利用了[埃氏筛](https://oi-wiki.org/math/number-theory/sieve/)的思想。

对于一个筛法求质数的 C++ 代码实现：

```cpp
void init()
{
    vis[1] = true;
    for (int i = 2; i <= 1e5; i++)
    {
        if (vis[i])
        {
            continue;
        }
        for (int j = 2; i * j <= 1e5; j++)
        {
            vis[i * j] = true;
        }
    }
    return;
}
```

其中的 $vis_i = 1$ 时，表示这个数是合数，反之。

主要思想就是利用之前的质数来筛掉之前的合数，本题亦然。

本题的思路是用较小 $k$ 筛掉较大的 $p_i$

```cpp
#include <cstdio>
constexpr int MaxN = 1e6 + 5;
int t;
int n;
int sum[MaxN];
char s[MaxN];
bool vis[MaxN];
long long answer;
void solve()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i++)
    {
        vis[i] = s[i] == '1';
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; i * j <= n; j++)
        {
            if (vis[i * j])
            {
                break;
            }
            sum[i * j] = i;
        }
    }
    answer = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            answer += sum[i];
        }
    }
    printf("%lld\n", answer);
}
int main()
{
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

一测样例，你会发现**好像**对了，然后就是快乐的……WA！（你猜为什么现在还在思路分析）

显而易见的 Hack 数据：

CF1734.in
```
1
4
0010
```

CF1734.out
```
7
```

CF1734.ans
```
4
```

因为在 $1, 2, 4$，$1, 2$ 会先被筛掉，但 $4$ 就只能用 $4$ 覆盖了。

所以我们要倒着枚举。

### 代码实现

```cpp
#include <cstdio>
constexpr int MaxN = 1e6 + 5;
int t;
int n;
int sum[MaxN];
char s[MaxN];
bool vis[MaxN];
long long answer;
void solve()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i++)
    {
        vis[i] = s[i] == '1';
    }
    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; i * j <= n; j++)
        {
            if (vis[i * j])
            {
                break;
            }
            sum[i * j] = i;
        }
    }
    answer = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            answer += sum[i];
        }
    }
    printf("%lld\n", answer);
}
int main()
{
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：lzdqwq (赞：0)

明显埃氏筛，枚举 $k$ 就是它不在 $T$ 内的最小质因子。如果不在，就可以每次加 $k$ 向后删，直到为 $T$ 为止。

至此，我们在 $O(n \log n)$ 的时间复杂度内过掉了本题。

代码可以去看 CF 上的提交。

---

## 作者：cryozwq (赞：0)

不难想到一个数让它在尽可能小的因数时被删，并且一个数被删了不会影响后面的数被删，因为对于每个 $k$ 能删的是一段 $k$ 的倍数的前缀。

所以可以枚举 $k$，能删则删，复杂度是调和级数，$O(n \log n)$。注意开 long long。

代码见 CF 提交。

---

