# Variety is Discouraged

## 题目描述

定义任意数组 $b$ 的分数为 $b$ 的长度减去其中不同元素的数量。例如：
- 数组 $[1, 2, 2, 4]$ 的分数为 $1$，因为它长度为 $4$ 且只有 $3$ 个不同元素（$1$、$2$、$4$）。
- 数组 $[1, 1, 1]$ 的分数为 $2$，因为它长度为 $3$ 且只有 $1$ 个不同元素（$1$）。
- 空数组的分数为 $0$。

给定一个数组 $a$。你需要最多一次移除一个非空的连续子数组。

更正式地说，你最多可以执行以下操作一次：
- 选择两个整数 $l$ 和 $r$（$1 \le l \le r \le n$）
- 从 $a$ 中删除连续子数组 $[a_l,\ldots,a_r]$（即将 $a$ 替换为 $[a_1,\ldots,a_{l - 1},a_{r + 1},\ldots,a_n]$）

请输出一个操作，使得操作后 $a$ 的分数最大。若存在多个答案，输出能使操作后数组长度最短的任一解；若仍有多个答案，可输出任一。

## 说明/提示

第一个测试用例有两种选择：
- 不操作：数组 $[1]$ 的分数为 $1-1=0$。
- 删除 $l=1$，$r=1$ 的子数组：删除唯一元素后得到空数组，分数为 $0$。

因此最大可能分数为 $0$。但需要额外最小化数组长度，故必须输出第二种选择 $l=r=1$。注意第一种不操作的方案是错误的，因为它保留的数组长度更长。

第二个测试用例未选择任何子数组，操作后数组仍为 $[1, 1, 1, 1, 1]$。其长度为 $5$ 且有 $1$ 个不同元素，分数为 $5 - 1 = 4$。可以证明这是能最大化分数且长度最短的数组。

第三个测试用例选择删除子数组 $[2, \text{\color{red}{1,\ 3}}, 2]$，操作后数组变为 $[2, 2]$。其长度为 $2$ 且有 $1$ 个不同元素，分数为 $2 - 1 = 1$。可以证明这是能最大化分数且长度最短的数组。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
1
1
5
1 1 1 1 1
4
2 1 3 2```

### 输出

```
1 1
0
2 3```

# 题解

## 作者：Starlit_Night (赞：2)

根据得分计算公式，只有删除只出现 $1$ 次的元素是不会使得分降低的，如果删除了出现 $2$ 次及以上的元素，数组长度减少得比不同元素的个数减少得多，导致得分反而降低。同时题目要求在得分相同的情况下，数组长度最小。因此，我们要删掉连续的只出现一次的元素，并让删除的这一段长度尽可能长。  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<int> a(n);
        map<int,int> mp;
        for(int i=0;i<n;i++){
            cin>>a[i];
            mp[a[i]]++;
        }
        int ansl=0,maxlen=0;
        //只删除唯一出现的元素
        for(int i=0;i<n;i++){
            if(mp[a[i]]==1){
                int len=1;
                while(i+len<n&&mp[a[i+len]]==1){
                    len++;
                }
                if(len>maxlen){
                    maxlen=len;
                    ansl=i+1; //因为题目要求的是1索引
                }
                i=i+len-1; //减1，因为for循环还会加1，让下一次从i+len开始
            }
        }
        if(ansl==0) cout<<0<<"\n";
        else cout<<ansl<<" "<<ansl+maxlen-1<<"\n"; 
    }
	return 0;
}  
```

---

## 作者：thedyingkai (赞：1)

### 思路
删除元素时，如果删除重复的元素，分数减一，删除不重复的元素分数不变，要是分数最大就只能删除不重复的元素，而要使最终长度最小化，删除的长度就要最大，其实就是找出最长的连续只出现一次的元素的子序列。
### AC code
```cpp
#define rep(i,x,n) for(int i=x;i<=n;i++)
void solve(){
    int n,ans1=0,ans2=0;
    cin>>n;
    vector<int> a(n),b(n),c(n);
    rep(i,0,n-1) cin>>a[i],a[i]--,b[a[i]]++;
    rep(i,0,n-1) if(b[a[i]]==1) c[i]++;
    for(int l=0,r=0;l<n;l=r){
        while(r!=n&&c[r]) r++;
        if(ans2-ans1<r-l) ans2=r,ans1=l;
        if(l==r) r++;
    }
    if(ans2) cout<<ans1+1<<" "<<ans2<<endl;
    else cout<<0<<endl;
}
```

---

## 作者：K_yuxiang_rose (赞：0)

如果删除了个数大于一的数，那么最终得分会减小，所以不能删除任何个数大于一的数。

题目还要求使数列最小，所以删去的数要最多，既然不能删个数大于一的数，那就只能删只出现过一次的数，题目就转化为了：求数列的最长连续子序列，使得序列里的每一个数都只在整个数列中出现过一次。

开个桶维护每个数的数量，再扫一遍数列找最长连续子序列即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],b[200005];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) b[i]=0;
		for(int i=1;i<=n;i++) cin>>a[i],b[a[i]]++;
		int l=1,r=0,maxl=0,maxr=-1;
		int i=1,flag=0;
		while(i<=n)
		{
			if(b[a[i]]>1)
			{
				if(r-l+1>maxr-maxl+1) maxl=l,maxr=r;
				l=i+1;
				r=i;
			}
			else r++,flag=1;
			i++;
		}
		if(r-l+1>maxr-maxl+1) maxl=l,maxr=r;
		if(!flag) cout<<"0\n";
		else cout<<maxl<<" "<<maxr<<"\n";
	}
    return 0;
}

```

---

## 作者：wandereman (赞：0)

## 思路
当删除出现了大于 1 次的数时，分数减小，所以我们如果想让分数最大，那么我们就要删掉不重复的数字，又要使长度最小，删除的数就要越多，所以我们只需要选出长度最大的连通块并输出。
## AC code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
    ll T;
    cin>>T;
    while(T--){
        ll n;
        cin>>n;
        vector<ll> a(n);
        map<ll,ll> mp;
        for(ll i = 0;i < n;i++) cin>>a[i];mp[a[i]]++;
        ll al = 0,ml = 0;
        for(ll i = 0;i < n;i++){
            if(mp[a[i]] == 1){
                ll len = 1;
                while(i + len < n && mp[a[i + len]] == 1) len++;
                if(len>ml) ml = len;al = i + 1;
                i = i + len - 1;
            }
        }
        if(al == 0) cout<<0<<endl;
        else cout<<al<<" "<<al + ml - 1<<endl; 
    }
	return 0;
}  
```

---

## 作者：NEKO_Daze (赞：0)

[洛谷CF2064B](https://www.luogu.com.cn/problem/CF2064B) || [CodeForces 2064 B](https://codeforces.com/contest/2064/problem/B)

### 简要题意
定义数组 $b$ 的贡献为 $b$ 中元素个数减去 $b$ 中不同元素的数量。空数组贡献为 $0$。

给出一个数组 $a$。拥有**一次**对其操作的机会，删除 $a$ 的一个子段。即选择两个整数 $l$ 和 $r$，其中 $1 \le l \le r \le n$，删除连续的子数组 $[a_l,\ldots,a_r]$。也可以不进行操作。如果有多个答案，则输出贡献最大的**操作**。

请最小化 $a$ 的贡献。如果还是有多个答案，输出其中的任何一个。

### 思路
如果从 $a$ 中删除一个元素，贡献不会增加。因为删除一个元素将导致 $|a|$ 减少 $1$，而 $\mathrm{distinct}(a)$ 最多减少 $1$，所以 $|a|-\mathrm{distinct}(a)$ 永远不会增加。这意味着我们应该尝试删除最长的子数组，这不会降低贡献。实际上，删除在 $a$ 中只出现一次的任何元素都不会降低贡献，删除任何出现一次以上的元素总是会降低贡献。

因此，我们应该尝试找到在 $a$ 中只有 $1$ 出现的元素的最长子数组。这可以通过 $O(n)$ 中的单个循环来计算。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n), freq(n+1), len(n+1);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) freq[a[i]]++;
    len[0] = freq[a[0]] == 1;
    for (int i = 1; i < n; i++)
        if (freq[a[i]] == 1)
            len[i] = len[i - 1] + 1;
    int mx = *max_element(len.begin(), len.end());
    if (mx == 0)
    {
        cout << "0\n";
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (len[i] == mx){
            cout << i - len[i] + 2 << " " << i + 1 << "\n";
            return;
        }
    }
}
int main(){
    int t;
    cin >> t;
    while (t--) solve();
}
```

---

## 作者：yvbf (赞：0)

![](bilibili:BV19cAaeVEme?t=237)

---

## 作者：c_legg (赞：0)

## 题意

给出一个整数 $n\in[1, 2\times10^5]$，和 $n$ 个整数 $a_1,a_2,\dots,a_n$。令 $m(a)$ 为去重后的 $a$，则 $s(a)=\mid a\mid-\mid m(a)\mid$ 即 $n$ 减去数组中不同元素的数量。要求一对整数 $l,r\in[1,n],l\le r$，使得 $\mid a\mid$ 最小且 $s([a_1,a_2,\dots a_{l-1},a_{r+1},\dots,a_n])$ 最大，即把编号从 $l$ 到 $r$ 的数删掉后的数组的 $s$ 最大化。

## 思路

可以发现，如果 $a_i$ 在 $a$ 中出现了不止一次，那就不能删掉 $a_i$。因为这会使得 $s(a)$ 变为 $s(a)-1$。

所以就只能删除在 $a$ 中只出现一次的数，显然，它们要是连续的。

那问题就好办了：用一个 `map` 表示数组中每个数出现次数，再用双指针找到最优的区间即可。

[代码不在这儿](https://codeforces.com/contest/2064/submission/307129505)

---

## 作者：feng_0108 (赞：0)

# Variety is Discouraged题解
## 题目简介
给出一个长度为 $n$ 的数组 $a$ ，从中删除一个子数组使得数组 $a$ 的得分最大。
## 解法说明
题目大意要求我们计算 $\max(len_a - elt_a)$，其中 $len_a$ 为数组长度， $elt_a$ 为数组元素种类，我们可以分以下两种情况进行讨论：
### 情况一： $a_i$ 的个数等于 $1$ 
当 $a_i$ 的个数等于 $1$ 时，删除 $a_i$ 使得原数组 $len_a - 1$ 并且 $elt_a - 1$ ，导致 $len_a - 1 - (elt_a - 1) = len_a - elt_a$ ，这并没改变数组得分大小。
### 情况二： $a_i$ 的个数大于 $1$ 
当 $a_i$ 的个数大于 $1$ ，删除 $a_i$ 使得原数组 $len_a - 1$ ，但是 $elt_a$ 并未发生改变，当前数组得分为 $len_a - 1 - elt_a$ ，小于原数组得分，因此我们不能对个数大于 $1$ 的 $a_i$ 进行删除操作。
### 总结：
我们对个数等于 $1$ 的 $a_i$ 进行删除操作不会对得分产生影响，反而它们的存在占用了个数大于 $1$ 的 $a_i$ 得分，因此要求最大得分的最短长度就是求个数等于 $1$ 的最长子数组.
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

int t, n;

int a[N], dp[N];

void solve()
{
	cin >> n;
	
	unordered_map<int, int> hash;
	for(int i = 1; i <= n; i ++ ) {
		cin >> a[i];
		hash[a[i]] ++;
	}
	
	int tmp = 0, l = 0, r = 0;
	for(int i = 1; i <= n; i ++ )  // 时间复杂度O(N)
	{
		if(hash[a[i]] == 1) {
			dp[i] = dp[i - 1] + 1;
			if(dp[i] > tmp){
				tmp = max(tmp, dp[i]);
				r = i, l = i - tmp + 1;
			}
		}
		else dp[i] = 0;
	}
	
	if(!l && !r) cout << 0 << endl;
	else cout << l << ' ' << r << endl;
}

int main()
{
	cin >> t;
	while(t -- )
		solve();
	return 0;
 } 
```

---

## 作者：hbhz_zcy (赞：0)

题意：给了一个序列 $b$，定义 $score_b$ 为 $b$ 的长度减去 $b$ 中元素（去重后）的个数。要求不操作或进行一次删除连续段的操作，使得 $score_b$ 最大前提下 $b$ 的长度尽量小。  
显而易见，$score_b$ 即为 $b$ 中出现元素的重复数减 $1$ 求和。假设我们随便选一个 $b_i$ 删除，如果 $\exist b_j = b_i(i \neq j)$，则 $score_b$ 减去 $1$，否则不变。所以得出题面中的删除操作如果被执行，一定是对应 $score_b$ 不变的情况，即删除的所有数都没有重复出现过。  
因此，我们利用一个桶记录出现次数，然后从左到右扫一遍 $b$，寻找元素仅记录一次的最长连续段，将其删去即可。特别的，如果没有这样的连续段（或者说长度为 $0$），按题意不进行操作，输出 $0$。  
```cpp
//g++ b.cpp -o b -g -std=c++14 -O0 -Wall
#include<iostream>
#include<cstdio>
using namespace std;
int qd(){
	int rt=0;char c=getchar();
	while(c<'0'||c>'9')  c=getchar();
	while('0'<=c&&c<='9')  rt=(rt<<3)+(rt<<1)+c-48,c=getchar();
	return rt;
}
const int maxn=2e5+10;
int a[maxn],tn[maxn];
int main(){
	freopen("in.txt","r",stdin);
	int T=qd();
	while(T--){
		int N=qd(),ansl=0,ansr=0;for(int i=1;i<=N;i++)  tn[a[i]=qd()]++;
		for(int i=1,l=0;i<=N+1;i++)
			if(i==N+1||tn[a[i]]>1){
				if(i-l>ansr-ansl)  ansl=l,ansr=i;
				l=i;
			}
		if(ansr-ansl<=1)  printf("0\n");
		else printf("%d %d\n",ansl+1,ansr-1);
		for(int i=1;i<=N;i++)  tn[a[i]]=0;
	}
	return 0;
}
```

---

## 作者：wuyouawa (赞：0)

### 题目大意


定义任意数组 $b$ 的得分为数组的长度减去数组中不同元素的个数。例如：

- 数组 $[1, 2, 2, 4]$ 的得分是 $1$，因为它的长度是 $4$，其中有 $3$ 个不同的元素（$1$、$2$、$4$）。
- 数组 $[1, 1, 1]$ 的得分是 $2$，因为它的长度是 $3$，其中有 $1$ 个不同的元素（$1$）。
- 空数组的得分是 $0$。

现在给定一个数组 $a$。你需要从 $a$ 中删除某个非空的连续子数组，最多一次。

更正式地，你可以执行以下操作，至多一次：


- 选择两个整数 $l$ 和 $r$，其中 $1 \leq l \leq r \leq n$，
- 删除连续子数组 $[a_l, \dots, a_r]$，并将数组变为 $[a_1, \dots, a_{l-1}, a_{r+1}, \dots, a_n]$。

输出一种操作，使得删除后的数组的得分最大；如果有多个答案，输出最终长度最小的数组。如果仍然有多个答案，您可以输出任意一个。

### 思路

首先，我们可以知道，为了让数组的得分最大，数组中不同元素的个数应尽量少，那么每次删只出现一次的数永远是最优的。

然后就好做了。直接删最长连续的只出现 $1$ 次的元素即可。这个可以先下标计数，再每次用下标计数的结果看每一个元素是不是只出现 $1$ 次，是的话更新最长的连续的 $1$ 的数组等于上一个加 $1$，因为在上一个的基础上又多了一个。

最后判断最大值为 $0$ 的情况，此时输出 $0$，如果不为 $0$，则再扫一遍最长的连续的 $1$ 的数组，把最大值找出，并算出开头和结尾即可。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x[200005],a[200005],l[200005],ma; 
int main(){
	cin>>t;
	while(t--)//多测
	{
		cin>>n;
		for(int i=1;i<=200000;i++)
		{
			a[i]=0;
			l[i]=0;//清零
		}
        for(int i=1;i<=n;i++)  cin>>x[i],a[x[i]]++;//下标计数
        l[1]=a[x[1]]==1;
        ma=0;
        for(int i=2;i<=n;i++)
        {
    	    if(a[x[i]]==1)  l[i]=l[i-1]+1;//每次更新答案
    	}
    	for(int i=1;i<=n;i++)
    	{
    		ma=max(ma,l[i]);//找最大值
    	}
        if(ma==0)
	    {
            cout<<ma<<endl;
            continue;
        }//特判
        else
        {
        	for(int i=1;i<=n;i++)
	        {
                if(l[i]==ma)
		        {
                   cout<<i-l[i]+1<<" "<<i<<endl;//找到了，算开头结尾
                   break;
                }
            }
        }
	}
    return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

由题知删除出现次数大于 $1$ 的数一定不优。将这些数删掉，选出长度最大的连通块输出即可。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 2e5 + 10;
int n, a[N], l, r, buc[N];
void init_global()
{
}
void init_local()
{
	scanf("%d", &n);
	memset(buc + 1, 0, n << 2);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", a + i);
		buc[a[i]]++;
	}
}
void run()
{
	l = 0;
	r = -1;
	for (int i = 1, j; i <= n; i++)
	{
		j = i;
		while (j <= n and buc[a[j]] == 1)
			j++;
		j--;
		if (j - i > r - l)
			l = i, r = j;
		if (i <= j)
			i = j;
		// fprintf(stderr, "%d\n", i);
	}
	if (!l)
		puts("0");
	else
		printf("%d %d\n", l, r);
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	int T = 1;
	scanf("%d", &T);
	init_global();
	while (T--)
	{
		init_local();
		run();
	}
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

