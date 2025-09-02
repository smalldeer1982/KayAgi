# Sets and Union

## 题目描述

You have $ n $ sets of integers $ S_{1}, S_{2}, \ldots, S_{n} $ . We call a set $ S $ attainable, if it is possible to choose some (possibly, none) of the sets $ S_{1}, S_{2}, \ldots, S_{n} $ so that $ S $ is equal to their union $ ^{\dagger} $ . If you choose none of $ S_{1}, S_{2}, \ldots, S_{n} $ , their union is an empty set.

Find the maximum number of elements in an attainable $ S $ such that $ S \neq S_{1} \cup S_{2} \cup \ldots \cup S_{n} $ .

 $ ^{\dagger} $ The union of sets $ A_1, A_2, \ldots, A_k $ is defined as the set of elements present in at least one of these sets. It is denoted by $ A_1 \cup A_2 \cup \ldots \cup A_k $ . For example, $ \{2, 4, 6\} \cup \{2, 3\} \cup \{3, 6, 7\} = \{2, 3, 4, 6, 7\} $ .

## 说明/提示

In the first test case, $ S = S_{1} \cup S_{3} = \{1, 2, 3, 4\} $ is the largest attainable set not equal to $ S_1 \cup S_2 \cup S_3 = \{1, 2, 3, 4, 5\} $ .

In the second test case, we can pick $ S = S_{2} \cup S_{3} \cup S_{4} = \{2, 3, 4, 5, 6\} $ .

In the third test case, we can pick $ S = S_{2} \cup S_{5} = S_{2} \cup S_{3} \cup S_{5} = \{3, 5, 6, 8, 9, 10\} $ .

In the fourth test case, the only attainable set is $ S = \varnothing $ .

## 样例 #1

### 输入

```
4
3
3 1 2 3
2 4 5
2 3 4
4
4 1 2 3 4
3 2 5 6
3 3 5 6
3 4 5 6
5
1 1
3 3 6 10
1 9
2 1 3
3 5 8 9
1
2 4 28```

### 输出

```
4
5
6
0```

# 题解

## 作者：Nuclear_Fish_cyq (赞：11)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF1882B)

[CF 原题传送门](https://codeforces.com/problemset/problem/1882/B)

[提交记录](https://www.luogu.com.cn/record/126940174)

## 题目大意

有 $n$ 个集合，第 $i$ 个集合有 $k_i$ 个元素，要求选出一些集合，使得：

- 被选出的集合的并集与所有集合的并集（全集）不同。

- 被选出的集合的并集的元素数尽可能大。

## 做法

看到 $n\le50$ 和 $ 1 \le s_{i, 1} < s_{i, 2} < \ldots < s_{i, k_{i}} \le 50 $，好像能暴力。

首先，被选出的集合的并集肯定被包含于全集。

那么，我们要求被选出的集合的并集与全集不同，那么肯定是存在一个元素 $q$，使得 $q$ 不属于被选出的集合的并集，但 $q$ 属于全集。那么，我们可以反过来枚举这个 $q$，只选不包含 $q$ 的集合，然后计算选出的集合的并集的元素个数，取最大值。注意，这道题是多组测试点，最好是在开始跑每一个测试点前都先清空数据。

上代码。码风可能比较奇怪，请不要太在意。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int t, n, siz[50], ans, cnt;
bool a[50][51], flag[51], app[51];//a[i][j]表示第i个集合里是否有j 
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	for(int kk = 0; kk < t; kk++){
		ans = 0;
		for(int i = 0; i < 50; i++){
			for(int j = 0; j <= 50; j++){
				a[i][j] = false;
				app[j] = false;
			}
		}
		cin >> n;
		for(int i = 0; i < n; i++){
			cin >> siz[i];
			for(int j = 0; j < siz[i]; j++){
				int k;
				cin >> k;
				a[i][k] = true;
				app[k] = true;
			}
		}
		for(int i = 0; i <= 50; i++){
			if(!app[i]){
				continue;
			}
			cnt = 0;
			for(int j = 0; j <= 50; j++){
				flag[j] = false;
			}
			for(int j = 0; j < n; j++){
				if(!a[j][i]){
					for(int k = 0; k <= 50; k++){
						if(!flag[k] && a[j][k]){
							cnt++;
							flag[k] = true;
						}
					}
				}
			}
			ans = max(ans, cnt);
		}
		cout << ans << endl;
	}
	return 0;
}

```


---

## 作者：MhxMa (赞：2)

### 概述
题目给定了一些集合，要求找到一个可达的集合$ S $，使得$ S $的元素个数最大，并且$ S $不能等于$ S_{1} \cup S_{2} \cup \ldots \cup S_{n} $。

### 分析

$ S_{1} \cup S_{2} \cup \ldots \cup S_{n}$ 表示集合 $S_{1} $、$ S_{2} $、$\ldots$、$ S_{n}$ 的并集，即所有集合中的元素的集合。
根据题目要求，我们需要找到一个可达集合$S$ （可达集合：从给定的一些集合中，选择一些集合的元素，使得这些元素的并集等于可达集合），使得 $S$ 的元素个数最大，并且 $S$ 不能等于 $S_{1} \cup S_{2} \cup \ldots \cup S_{n}$。
我们可以使用一个集合 $se$ 来存储所有集合中的元素，然后遍历 $se$ 中的每个元素，将其从集合 $se$ 和其他集合中删除，计算删除后的 $se$ 的大小，并更新最大值。最后输出最大值即可。

本题可以通过使用集合和映射来简化代码，并且通过遍历集合的方式来求解最大可达集合的元素个数，以下是代码。

```cpp
#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<set<int>> sets(n);
        set<int> se;
        map<int, int> ma;
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            for (int j = 0; j < k; j++) {
                int b;
                cin >> b;
                sets[i].insert(b);
                ma[b]++;
                se.insert(b);
            }
        }
        int maxi = 0;
        for (int val : se) {
            set<int> tset = se;
            map<int, int> tmap = ma;
            for (int i = 0; i < n; i++) {
                if (sets[i].count(val) > 0) {
                    for (int num : sets[i]) {
                        tmap[num]--;
                        if (tmap[num] == 0) {
                            tset.erase(num);
                        }
                    }
                }
            }
            maxi = max(maxi, (int)tset.size());
        }
        cout << maxi << endl;
    }
    return 0;
}
```

---

## 作者：wrkwrkwrk (赞：1)

为了使得选出的集合的并集不是所有集合的并集，我们只要让其中至少一个数不在里面即可。枚举 $S$ 中的每一个数，每次求出不包含这个元素的集合个数，这些数的最大值就是答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace _wrk{;
set<int>p[100];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		set<int>s;
		for(int i=1;i<=60;i++){
			p[i].clear();
		}
		for(int i=1;i<=n;i++){
			int k;
			cin>>k;
			while(k--){
				int a;
				cin>>a;
				s.insert(a);
				p[i].insert(a);
			}
		}
		int ans=0;
		for(auto x:s){
			set<int>pp;
			for(int i=1;i<=n;i++){
				if(p[i].find(x)==p[i].end()){
					for(auto y:p[i]){
						pp.insert(y); 
					}
				}
			}
			ans=max<int>(ans,pp.size());
		}
		cout<<ans<<endl;
	}
	return 0;
}
}
signed main(){
	   return _wrk::main();
}

```

---

## 作者：phigy (赞：1)

我们需要一个方法去强制防止让选的集合包含所有元素，那么就只需要禁止一个元素就行了，所以我们对每个元素都禁止一次，然后求没有这个元素的集合的并集的元素个数，然后答案即为这个的最大值。

```cpp
#include <iostream>

#define int long long

using namespace std;

int T;
int n;
int a[1005][1005];
int b[10005];
int sum[10005];

signed main()
{
    int i,j,k;
    cin>>T;
    while(T--)
    {
        cin>>n;
        for(i=1;i<=50;i++)
        {
            sum[i]=0;
        }
        for(i=1;i<=n;i++)
        {
            b[i]=0;
            for(j=1;j<=50;j++)
            {
                a[i][j]=0;
            }
        }
        int ans=0;
        for(i=1;i<=n;i++)
        {
            cin>>b[i];
            for(j=1;j<=b[i];j++)
            {
                int x;
                cin>>x;
                a[i][x]=1;
                sum[x]++;
            }
        }
        for(i=1;i<=50;i++)
        {
            if(sum[i])ans++;
        }
        int maxx=0;
        for(i=1;i<=50;i++)
        {
            int res=0;
            for(j=1;j<=n;j++)
            {
                if(a[j][i]==1)
                {
                    for(k=1;k<=50;k++)
                    {
                        sum[k]-=a[j][k];
                    }
                }
            }
            for(j=1;j<=50;j++)
            {
                if(sum[j])res++;
            }
            for(j=1;j<=n;j++)
            {
                if(a[j][i]==1)
                {
                    for(k=1;k<=50;k++)
                    {
                        sum[k]+=a[j][k];
                    }
                }
            }
            if(res!=ans)maxx=max(res,maxx);
        }
        cout<<maxx<<endl;
    }
    return 0;
}

```


---

## 作者：qusia_MC (赞：0)

数据范围这么小。。

## 题意
~~这翻译不知道是哪个大聪明写得，看不懂一点，还让我线上网查~~就是说有 $n$ 个集合，每个集合有 $m_i$ 个数，集合中的元素为 $v_i$，求你从中删除任意多的集合后，他们的并集元素数量的最大值。并且并集不能等于全集。

## 思路

既然范围贼小所以直接开一个桶枚举含有这个数的集合数，然后依次枚举 $1\sim 50$ 的所有数，然后依次扫每个集合，如果存在就把这个数定义成存在（需另开数组），扫完一个集合之后如果有数是存在的就含有这个数的集合数 $-1$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
void Main()//一组数据
{
	int n, sum_u[51], sum_u2[51], ans = -999;
	memset (sum_u, 0, sizeof(sum_u));
//先清空
//这个东西统计的是每个数字含有它的集合数。
	cin >> n;
	vector <int> v[114];

	for (int i = 1; i <= n; i ++)
	{
		int t, if_sz[51];//是不是存在
		memset(if_sz, 0, sizeof(if_sz));//清空
		cin >> t;
		for (int j = 1; j <= t; j ++)
		{
			int l;
			cin >> l;
			v[i].push_back(l);//集合push进去
			if_sz[l] = 1;//存在
		}
		for (int k = 1; k <= 50; k ++) sum_u[k] += if_sz[k];//累加
	}
	for (int i = 1; i <= 50; i ++)//枚举要删除的数
	{
		if (sum_u[i] == 0) continue;
//是0，删掉的是空气，wyy。
		for (int j = 1; j <= 50; j ++) sum_u2[j] = sum_u[j];//复制
		for (int k = 1; k <= n; k ++)
		{
		    bool flag = 0;
			for (auto j : v[k])
		    {
		    	if (j == i) flag = 1;//存在这个数
		    }
		    if (flag)
	    	{
	    		int if_sz[51];
	    		memset(if_sz, 0, sizeof(if_sz));
	    		for (auto j : v[k])
	    		{
					if_sz[j] = 1;
				}
				for (int j = 1; j <= 50; j ++)
				{
					sum_u2[j] -= if_sz[j];//集合数-1
				}
	    	}
		}
		int cnt = 0;
		for (int j = 1; j <= 50; j ++)
		{
			if (sum_u2[j] >= 1) cnt ++;//如果有存在的集合，则答案元素个数+1
		}
		ans = max (ans, cnt);//取最大值
	}
	cout << ans << "\n";
}
int main()
{
	int T;
	cin >> T;
	while (T --) Main();
//T组数据
	return 0;
//完结撒花
}
```

---

## 作者：lfxxx (赞：0)

既然要不等于全集，等于说一定有一个元素没有被选择。

当满足了存在一个元素没有被选择的条件后，剩下的一定要尽可能多选。

所以对于枚举的每一个不选择的元素 $x$ 将所欲不包含它的集合并起来就是本次的答案。

所有答案取最大值即可，结合 bitset 压位后可以轻松通过。

```cpp
#include<bits/stdc++.h>
//#define int long long
//#define lowbit(x) (x&-(x))
using namespace std;
const int maxn = 60;
bitset<maxn> S[maxn],U;
void work(){
	int n;
	cin>>n;
	U.reset();
	for(int i=1;i<=n;i++){
		S[i].reset();
	}
	for(int i=1;i<=n;i++){
		int k;
		cin>>k;
		for(int j=1;j<=k;j++){
			int x;
			cin>>x;
			S[i][x]=true;
		}
		U|=S[i];
	}
	int ans=0;
	for(int i=1;i<=55;i++){//在不含元素 i 的情况下的答案 
		if(U[i]==0) continue;
		bitset<maxn> now;
		for(int j=1;j<=n;j++){
			if(S[j][i]==0) now|=S[j];
		}
		ans=max(ans,(int)now.count());
	}
	cout<<ans<<'\n';
}
int t;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--) work();

	return 0;
}
/*
1
3
3 1 2 3
2 4 5
2 3 4
*/
```


---

## 作者：shenwentao (赞：0)

## 题目大意:

给出 $n$ 个集合，第 $i$ 个集合为 $S_i$，然后,我们会把这 $n$ 个集合给他并起来，做成一个大集合 $S$。
我们需要从大集合 $S$ 当中，去找出一个集合 $T$，集合 $T$ 是由其他集合 $S_i$ 所组成的，并且使得集合 $T$ 不等于集合 $S$。

## 题目目的:

要求你找出这个集合 $T$，并且要求他尽可能地大，也就是里面元素尽可能的多，并且要求输出这个集合的大小 $h$。

### 举个例子:

$n=3$

$k_1=3$，$s_1= \{ 1,2,3 \} $

$k_2=2$，$s_2= \{ 4,5 \} $

$k_3=2$，$s_3= \{ 3,4 \} $ 

#### 他们的大并集 $S$ 我们可以得出是:

$S= \{ 1,2,3 \} ∪ \{ 4,5 \} ∪ \{ 3,4 \} = \{ 1,2,3,4,5 \} $

#### 然后我们现在要去里面去求出最大的并集 $T$ ，并且使 $T$ 不等价于 $S$

$T = s_1 ∪ s_2 = \{ 1,2,3 \} ∪ \{ 4,5 \} = \{ 1,2,3,4,5 \}$ 

不可以，因为此时 $T$ 的取值等价于 $S$，也就是 $T$ 的元素和 $S$ 的元素一致。

$T = s_1 ∪ s_3 = \{ 1,2,3,4 \} $

此时的T可以作为我们的答案，大小为 $4$ 。

$T = s_2 ∪ s_3 = \{ 3,4,5 \} $ 

此时T也可以作为我们的答案，大小为 $3$ 。

## 思路

1. 我们可以这样想，既然我们要从 $S$ 当中去找出一个和 $S$ 集合不同的 $T$ 集合，并且这个 $T$ 集合必须是使用组成 $S$ 集合的一个个 $S_i$ 集合并成，那么我们就可以直接使用 $S$ 大集合去删除一个个 $S_i$ 集合去求得答案。（但是有一个问题，我们删除集合的时候，我们有时候并不一定删除一个集合就可以得到 $T$ 了，也许所有的 $S_i$ 都相等呢？）

2. 数据范围很小，我们一共只有50个集合，每个集合最多只有50个数字，也就是 $1 \sim 50$，那么，我们是不是可以枚举每一个数字是否在大集合当中出现过，并且枚举这个数字不存在大集合当中的集合是否可以作为我们的 $T$。

## 代码示范

```cpp 
//思路二：制作集合S，然后去枚举出现过的数字，去剔除其中一个数字所在的集合，查看这个集合剔除之后生成的集合T是否可以作为最终答案，枚举所有符合这个条件的集合T，然后选出最大的一个。
#include<bits/stdc++.h>
using namespace std;
bool vis[55];//标记某个数字出现过
bool mp[55][55];//标记这个数字在哪一个集合当中出现过
int t,n; 
bool f[55];
int main()
{
	cin>>t;
	while(t--)
	{
		memset(vis,0,sizeof vis);
		memset(mp,0,sizeof mp);
		cin>>n;
		for(int i=0;i<n;i++)
		{
			int k;
			cin>>k;
			for(int j=0;j<k;j++)
			{
				int x;
				cin>>x;
				vis[x]=mp[i][x]=true;
			}
		}
		int answer=0 ;
		for(int i=1;i<=50;i++)
		{
			if(vis[i])
			{
				//如果数字出现过，那么反过来去枚举没有这个数字的集合的并集大小
				memset(f,0,sizeof f);//标记每个数字元素是否被并过。 
				int res=0 ;
				for(int j=0;j<n;j++)
				{
					//选择集合 
					if(!mp[j][i])
					{
						//如果数字i没在这个集合出现过那么就把这个集合并起来 
						for(int z=1;z<=50;z++)
						{
							if(mp[j][z] && !f[z])
							{
								res++;
								f[z]=true;
							}
						}
					}
				} 
				answer=max(answer,res);
			}
			
		}
		cout<<answer<<endl;
	}
	return 0;
}
```

---

## 作者：Womind (赞：0)

如果正面暴力枚举是不是真子集要去到 $2^n$，显然不行对于真子集，她的定义是至少比全集少一个元素，那比全集少一个元素就一定是真子集！ 

这样不会漏掉最优解，枚举每一个不选的元素，从没有这个元素的集合中求并集，找出最大的并集。时间复杂度 $O(n^2)$。 

发现集合中的元素 $\le50$，可以用二进制压缩使空间复杂度压为 $O(n)$，比较的时间复杂度 $O(1)$。
 
总时间复杂度 $O(n^2)$，空间复杂度压为 $O(n)$。

talk is cheap, show you my coooooooooooooode!
``` 
/*
    Name:
    Copyright:
    Author:
    Date: 2023/10/8 16:58:19
    Description:
*/

#include<bits/stdc++.h>
using namespace std;
int t, n, siz[51], a[52];
long long s[51];
//__builtin_popcount 只能 int!!  有 popcountll !! 
int main(){
	cin >> t;
	while(t--) {
		cin >> n;
		memset(s, 0, sizeof(s));
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= n; i++) {
			scanf("%d", &siz[i]);
			for (int j = 1; j <= siz[i]; j++) {
				int x; scanf("%d", &x);
				s[i] |= (1ll << x);
				a[x] = 1;
			}
		}
		int ans = 0;
		for (int i = 1; i <= 50; i++) {
			if (a[i]) {
				long long tmp = 0;
				for (int j = 1; j <= n; j++) {
					if ((1ll << i) & s[j]) continue;
					tmp |= s[j];
				}
				ans = max(ans,  __builtin_popcountll(tmp));
			}
		}
		cout << ans << "\n";
	}
}
```


---

## 作者：Leeb (赞：0)

### 题意简述

存在 $n$ 个集合 $S_i$，设 $S=S_1 \cup S_2 \cup S_3 \cup \dots \cup S_n$，要求从这 $n$ 个集合中选出 $k$ 个集合，记这 $k$ 个集合的并集为 $S'$，使得 $S' \subsetneqq S$ 。求 $k$ 的最大值。

### 解题思路

**核心：** 正难则反。

- 由于数据范围非常小，只有 $50$，所以直接考虑暴力。
  
- 从正面来想，发现选取 $k$ 个集合并求它们的并集并不好实现，于是考虑反面操作。
  
- 直接枚举要排去哪个元素，找到所有不包含这个元素的集合，求它们的并集，记录并集的元素个数 $res$。求所有 $res$ 的最大值即可。
  

#### 代码参考

- 看到楼上的巨佬们大多都是利用数据结构来实现的，再此提供一种不需要数据结构的实现方式。
  

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
#include <bits/stdc++.h>
// #include <cstdio>
// #include <cstring>
// #include <algorithm>
#define N 55
#define inf 0x3f3f3f3f
#define elif else if
#define ll long long
#define ub upper_bound
#define lb lower_bound
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int n, res, ans; bool f[N], vis[N], is[N][N]; 
// f用于求选取的集合的并集，vis用于求所有集合的并集，is[i][j]表示第i个集合是否包含元素j。
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline int max(int a, int b) {
    return a > b ? a : b;
}
int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = in();
    while (t--) {
        n = in(); ans = 0;
        mem(f, 0), mem(vis, 0), mem(is, 0); //多组数据，记得清空数组。
        for (int i = 1; i <= n; ++i) {
            int len = in();
            for (int j = 1; j <= len; ++j) {
                int x = in();
                vis[x] = is[i][x] = 1; // 记录所有集合中出现的元素和每个集合中出现的元素
            }
        }
        for (int x = 0; x <= 50; ++x) { // 枚举要排除的那个数
            if (vis[x]) { //如果出现
                res = 0, mem(f, 0);
                for (int i = 1; i <= n; ++i) 
                    if (is[i][x]) continue;
                    else //如果集合i中不包含x，则进行统计
                        for (int j = 0; j <= 50; ++j)
                            if (!f[j] && is[i][j]) ++res, f[j] = 1;
                ans = max(res, ans); //取res的最大值
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

蒟蒻的第一篇题解，望管理大大通过qwq

---

## 作者：BugGod (赞：0)

## 题目大意
给定 $n$ 个整数集合，第 $i$ 个集合有 $k_i$ 个元素 $a_1,a_2,\cdots ,a_{k_i}$。

你可以取出其中的一些集合并求出他们的并集（可以是空集）使得此集合不等于全集（即所有 $n$ 个集合的并集），询问得到的并集最多能有多少元素。

## $\texttt{Solution}$
题目中说要使选出的集合不等于全集，那么我们就尽量从全集中取出一个元素。我们可以枚举要取出的元素，然后计算得到并集元素数量的最大值。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,vis[60][60],ans,k,x;
vector<int>s[60];
set<int>m;
typedef set<int>::iterator ite;
int main()
{
	cin>>t;
	while(t--)
	{
		memset(vis,0,sizeof(vis));
		m.clear();
		for(int i=0;i<60;i++)s[i].clear();
		ans=-2e9;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>k;
			for(int j=1;j<=k;j++)
			{
				cin>>x;
				vis[i][x]=1;//记录x是否在i集合中
				m.insert(x);//全集
				s[i].push_back(x);
			}
		}
		for(ite it=m.begin();it!=m.end();it++)//枚举元素
		{
			x=*it;
			set<int>mm;
			for(int i=1;i<=n;i++)
			{
				if(vis[i][x]==0)
				{
					for(int j=0;j<s[i].size();j++)mm.insert(s[i][j]);//被选出的集合
				}
			}
			ans=max(ans,(int)mm.size());
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：FireRain (赞：0)

# 思路

我们可以直接强制让某个数 $x$ 不出现，那么我们可以在读入的时候用一个 `vector` 存包含 $x$ 的集合的编号。

那么，我们就让这些集合都不合起来。

时间复杂度 $\Theta(n^2\log n)$。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 55,inf = 1e9 + 10;
int T,n;
bool num[N][N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

int main(){
	T = read();
	while (T--){
		memset(num,false,sizeof(num));
		vector<int> v[N];
		set<int> s;
		n = read();
		for (re int i = 1;i <= n;i++){
			int len;
			len = read();
			while (len--){
				int x;
				x = read();
				s.insert(x);
				v[i].push_back(x);
				num[x][i] = true;
			}
		}
		int ans = -inf;
		for (auto it = s.begin();it != s.end();it++){
			set<int> st;
			int x = (*it);
			for (re int i = 1;i <= n;i++){
				if (!num[x][i]){
					for (auto p:v[i]) st.insert(p);
				}
			}
			ans = max(ans,(int)(st.size()));
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

