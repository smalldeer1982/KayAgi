# Look Back

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ . You need to make it non-decreasing with the minimum number of operations. In one operation, you do the following:

- Choose an index $ 1 \leq i \leq n $ ,
- Set $ a_i = a_i \cdot 2 $ .

An array $ b_1, b_2, \ldots, b_n $ is non-decreasing if $ b_i \leq b_{i+1} $ for all $ 1 \leq i < n $ .

## 说明/提示

No operations are needed in the first test case.

In the second test case, we need to choose $ i = 2 $ , after which the array will be $ [2, 2] $ .

In the third test case, we can apply the following operations:

- Choose $ i = 3 $ , after which the array will be $ [3, 2, 2] $ ,
- Choose $ i = 3 $ , after which the array will be $ [3, 2, 4] $ ,
- Choose $ i = 2 $ , after which the array will be $ [3, 4, 4] $ .

## 样例 #1

### 输入

```
9
1
1
2
2 1
3
3 2 1
4
7 1 5 3
5
11 2 15 7 10
6
1 8 2 16 8 16
2
624323799 708290323
12
2 1 1 3 3 11 12 22 45 777 777 1500
12
12 11 10 9 8 7 6 5 4 3 2 1```

### 输出

```
0
1
3
6
10
3
0
2
66```

# 题解

## 作者：One_JuRuo (赞：14)

## 思路

首先，对于 $a_i$ 他必须得不小于最后的 $a_{i-1}$，所以每个数乘的次数都是固定的。

如果暴力去乘 $2$ 直到不小于为止，将会超时，所以考虑使用其他的方法进行优化。

因为前后两个数可以同时乘以 $2$，相对比值不会变化，所以我们可以考虑对于最开始的 $a_{i-1},a_i$ 直接计算需要多少次才能使 $a_i$ 不小于 $a_{i-1}$，也就是两者需要乘以 $2$ 的差值，那么这个差值加上 $a_{i-1}$ 需要乘以 $2$ 的次数，就是 $a_i$ 需要的次数，只要把每两个数之间的差值都算出来，也就是次数的差分，再求一遍前缀和，就可以得到每个数需要的次数，再求一遍前缀和就是次数的总和。

不过需要注意的是，一个数差分后的次数可以是负数，代表这个数比前面一个数可以少乘以几次 $2$，同时前缀和不能是负数，因为你不能除以 $2$，所以需要与 $0$ 取个 $\max$。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,a,la,ans,c1,c2,sum;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&la),ans=sum=0;
		for(int i=1;i<n;++i)
		{
			scanf("%lld",&a),c1=0,c2=0;
			int l=la,r=a;
			while(l<r) l<<=1,++c1;//少乘几个2
			while(l>r) r<<=1,++c2;//多乘几个2
        /*c2-c1就是综合需要多乘几个2*/
			sum+=c2-c1,sum=max(0ll,sum),ans+=sum,la=a;
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：yydfj (赞：6)

这是本蒟蒻第四十三次写的题解，如有错误点请好心指出！

## 问题简述

给你一个长度为 $n$ 的序列 $a_i$，记使 $a_i$ 的值变为 $a_i \times 2$ 为一次操作，问最少要花多少次操作，使得该序列非严格递增。

## 解法综述

序列是否非严格递增要看对于每个 $a_i$，是否总是有 $a_{i-1} \le a_i$，那么就会很自然地想到当不符合上述条件时，就需要给 $a_i$ 一直乘 $2$，直到它大于等于 $a_{i-1}$ 为止，可以证明这样操作是最优的。

考虑一次性乘多次 $2$ 来符合条件，发现在乘的时候会发现乘出来的数太大而导致爆精度，可以将每个数转化为二进制并存储，记录它们在二进制中位权为 $1$ 的数位，如果要乘 $x$ 次 $2$，只需将每个数位加上 $x$ 即可。

若 $a_i$ 的最高数位 $x$ 小于 $a_{i-1}$ 的最高数位 $y$，则可以先将 $a_i$ 的所有数位加上 $y-x$，即乘 $y-x$ 次 $2$，然后比较 $a_i$ 与 $a_{i-1}$ 的大小，如果 $a_i$ 还是小，则再将 $a_i$ 的所有数位加上 $1$，这样就完成了一次性乘多次 $2$ 的操作。

## 代码描述

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,a[100005];
vector<ll> vt[100005];//这里用vector实现二进制存储
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		ll ans=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			vt[i].clear();
			for(int j=(1<<29),k=29;j>=1;j/=2,k--)
			if(a[i]>=j) a[i]-=j,vt[i].push_back(k);//记录每个a[i]在二进制中位权为1的数位
		}
		for(int i=2;i<=n;i++)
		{
			int len=vt[i-1].size(),len1=vt[i].size(),pp=vt[i-1][0]-vt[i][0];
			pp=max(0,pp);//乘max(0,pp)次2
			for(int j=0;j<len1;j++) vt[i][j]+=pp;
			bool bz=0;
			for(int j=0;j<len&&j<len1;j++)//比较a[i]与a[i-1]的大小
			{
				if(vt[i][j]==vt[i-1][j]) continue;
				if(vt[i][j]>vt[i-1][j])
				{
					ans+=pp;
					bz=1;
					break;
				}
				else//如果a[i]还是小
				{
					for(int j=0;j<len1;j++) vt[i][j]++;
					ans+=pp+1;
					bz=1;
					break;
				}
			}
			if(!bz)
			{
				if(len1>=len) ans+=pp;
				else//如果a[i]还是小
				{
					for(int j=0;j<len1;j++) vt[i][j]++;
					ans+=pp+1;
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：N_Position (赞：4)

# CF1883E
## 题目翻译
共 $t$ 组数据，对于每组数据，给一个正整数 $n$ 和一个长度为 $n$ 的数列。

每一次操作，你可以选择将一个数，使得这个数变为原来的两倍。

问，最少需要几次操作才能使得整个数列单调不降，即 $\forall i \in\left[1,n-1\right],a_i \leq a_{i+1}$。

## 题目分析
考虑暴力。

即遍历整个数列，将每一个数一直翻倍，知道大于等于前一个数为止，时间复杂度为 $O(\sum n\log_2(\sum n))$。时间复杂度可以通过本题，但是这样会炸 `unsigned long long`，所以此做法不可取。

考虑将一个数分为两部分，原数据和翻倍的次数 $t_i$，因此，第 $i$ 个数实际为 $a_i \times 2^{t_i}$。

这样，每个数便不会超过 `long long` 范围，可以通过本题。

考虑 $t_i$ 的转移，显然分为两种情况：

当 $a_i \geq a_{i-1}$ 时，$t_i = \max(0,t_{i-1}-\lfloor\log_2(a_i\div a_{i-1})\rfloor)$；

当 $a_i \lt a_{i-1}$ 时，$t_i = \max(0,t_{i-1}+\lceil\log_2(a_i\div a_{i-1})\rceil)$。

注意取整的上下。

## 代码实现

时间复杂度为 $O(\sum n)$。

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
const int N = 1e5+5;
typedef long long ll;
ll a[N];
ll t[N];
int main(){
	ll q;
	scanf("%lld",&q);
	while(q--){
		ll n;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}
		for(int i=2;i<=n;i++){
			if(a[i] >= a[i-1]){
				t[i] = max(0ll,(ll)(t[i-1] - floor(log2((double)a[i]/a[i-1]))));
			}
			if(a[i] < a[i-1]){
				t[i] = max(0ll,(ll)(t[i-1] + ceil(log2((double)a[i-1]/a[i]))));
			}
		}
		ll ans = 0;
		for(int i=1;i<=n;i++){
			ans += t[i];
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：_hxh (赞：2)

这种题一开始就能想到暴力的做法，对于所有的 $i (1 \le  i < n)$，一直将 $a_{i + 1}$ 乘 $2$ 直到 $a_i \le a_{i + 1}$。~~但这是普及/提高-的题目~~，想想这样都不可能过，所以我们要进行优化。

***

注意到如果 $a_i$ 和 $a_{i + 1} (1 \le  i < n)$ 同时乘上 $2^x (x \ge 1)$ 的话，比值是不会变的，所以我们可以遍历所有的数对 $(a_i,a_{i + 1})$，计算 $x$ 的值。这里并不需要累加之前的 $x$，只要最后求前缀和就可以了。

------------

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a,b,ans,cnt,sum,leftt,rightt;
signed main()
{
	cin >> t;
	while (t--)
	{
		sum = 0;
		ans = 0;
		cin >> n >> a;
		for (int i = 2;i <= n;i++)
		{
			cnt = 0;
			cin >> b;
			leftt = a;
			rightt = b;
			a = b;
			while (leftt < rightt)//当 a[i] 小于 a[i+1] 时 
			{
				leftt *= 2;
				cnt--;
			}
			while (leftt > rightt)//当 a[i] 大于 a[i+1] 时
			{
				rightt *= 2;
				cnt++;
			}
			sum += cnt;//cnt 为最终的乘的 2 的数量（即文中的 x） 
			if (sum < 0)//然鹅并不能除以 2，底线是不乘 2 
				sum = 0;
			ans += sum;
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：LiJoQiao (赞：2)

[原题链接](https://codeforces.com/contest/1883/problem/E) [洛谷题面](https://www.luogu.com.cn/problem/CF1883E) [提交记录](https://www.luogu.com.cn/record/132026363)  
### 题目大意  
给定长度为 $n$ 的序列 $a$，你可以进行以下操作。  
>选取一个 $i$ 满足 $1\le i\le n$，使 $a_i$ 变为原来的 $2$ 倍。  

求最少需要几次操作使得 $a$ 为一个不下降的序列。  
### 题目分析  
我们可以依次求出区间 $\left[1,i\right]$（$i\in \left[2,n\right]$）满足该条件需要的操作。  
这样 $\left[1,i-1\right]$ 中的数不需要再修改（没有后效性）。  

对 $a_i$ 进行分类讨论。注意以下的数都是未经修改的。  
设对 $a_i$ 的操作为 $cz_i$。

1. $a_i<a_{i-1}$  
>此时只需要求得 $a_i\ge a_{i-1}$ 需要的最少操作，然后加上 $cz_{i-1}$ 即为 $cz_i$。  

2. $a_i\ge a_{i-1}$   
>求 $(a_i\div 2^{j})\ge a_{i-1}$ 的 $j$ 的最大值，$cz_{i-1}-j$ 与 $0$ 的较大值（因为不能反向修改）即为 $cz_i$。

边求边加和，即可得到答案。  

注意要开 `long long `。  

代码如下。  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10;
typedef long long ll;
int n,a[MAXN];
int cz[MAXN];
ll ans;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t){
		--t;
		cin>>n;
		ans=0;
		for(int i=1;i<=n;++i){
			cin>>a[i];
		}
		for(int i=2;i<=n;++i){
			int ai=a[i];
			cz[i]=0;
			while((ai>>1)>=a[i-1]){
				ai>>=1;
				--cz[i];
			}
			while(ai<a[i-1]){
				ai<<=1;
				++cz[i];
			}
			cz[i]=max(0,cz[i-1]+cz[i]);
			ans+=cz[i];
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：linjinkun (赞：1)

提供一个目前所有题解都没有讲到的做法（现在开始我来说明我做这道题的全过程）。

拿到题，一看，简单！！

写了份代码，一交，嗯？没过？

超时了，怎么会呢？算了吧，直接优化！！

看我直接使用 $\log$ 函数加上开 ```long long```！！不是吧！怎么会 Wrong answer on test 4？

额……仔细一般分析，好像会爆 ```long long```！没办法了，只能用 ```__int128``` 了，结果……怎么还是 Wrong answer on test 5！（虽然比上次好）

服了服了，哎对！！可以用 ```long double```！！额……怎么会 Wrong answer on test 7 呢，看来得用高精度了，但是这种高精度怎么写的出来嘛，服了，看来得看题解了……

正当我准备查看题解的时候，突然，我灵光一闪，既然每个数只会被改一次，而且都是乘上 $2^x$，这里 $x$ 是指未知数，那么只需要标记每个数它乘上的 $2^x$ 的 $x$ 值是多少不就行了吗？于是，直接开写！！

代码（附注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
struct node
{
	int x;
	int y;//这个是标记
}a[N];
signed main()
{
	int _;
	scanf("%d",&_);
	while(_--)
	{
		int n;
		scanf("%d",&n);
		for(int i = 1;i<=n;i++)
		{
			scanf("%d",&a[i].x);
			a[i].y = 0;//初始化标记
		}
		long long sum = 0;
		for(int i = 2;i<=n;i++)
		{
			if(log2(a[i].x)<log2(a[i-1].x)+a[i-1].y)//比较大小，如果需要乘
			{
				int s = a[i-1].y+ceil(log2(a[i-1].x*1.0/a[i].x));//计算需要乘的x
				sum+=s;//代价加上x
				a[i].y = s;//标记这个数乘上了 2^x
			}
		}
		printf("%lld\n",sum);
	}
	return 0;
}
```

---

## 作者：smartdevil (赞：0)

[题目传送门。](https://www.luogu.com.cn/problem/CF1883E)

我首先想的是暴力，将 $a_{i-1}$ 乘 $2$ 直到 $a_i \le a_{i+1}$ ~~然后就成功的寄了。~~

设 $dp_i$ 为位置最小的调整情况，没有后效性。

当 $a_i \ge a_ {i-1}$ 时 $dp_i = \max (dp_ {i-1} - \log_2(\frac{a_i}{2}) , 0)$。

当 $a_i < a_ {i-1}$ 时 $dp_i = \max (dp_ {i-1} + \log_2(\frac{a_i}{2}) , 0)$。

求每个位置次数，根据上一个求大幅度增加速度。

---

## 作者：joker_opof_qaq (赞：0)

题目翻译很清晰，不在加以赘述。

## 思路 && 解法

本来想的肯定是去直接暴力，发现空间炸了，要写高精度，那么时间可能就会炸而且没人想写高精度，换一种 $dp$ 思路吧。

设 $dp_i$ 表示当前位置最小的调整情况，因为后面的不会影响前面的，所以 $dp$ 就是一个很好的思路。

- 当 $a_i \geq a_{i-1}$ 时 $dp_i=max(dp_{i-1} - \log_2(\frac {a_i}{a_{i-1}} ),0)$

- 当 $a_i < a_{i-1}$ 时 $dp_i=max(dp_{i-1} + \log_2(\frac {a_i}{a_{i-1}} ),0)$

就是直接去快速求每个位置次数，根据上一个求可以大幅度增加速度。

式子都给你了，代码就不给了。

---

## 作者：ZLCT (赞：0)

# CF1883E Look Back
## 题意
给定长度为 $n$ 的序列 $a$ ，每次可以选择一个数 $a_i\times 2$。求最小次数使 $a$ 成为一个不下降序列。
## original idea
我们可以很自然地想到可以从前往后枚举每一位并计算出需要改成多少。\
那……这个题不就做完了吗？\
观察一下数据你会发现 $n\le 10^5,a_i\le 10^9$ ，如果要暴力乘的话即使用高精度也会面临 $3\times 10^4$ 位的巨大计算。复杂度 $3\times 10^9$ 是无法接受的。
## modified solution
我们既然无法把大数表示出来，那我们把它缩小不就可以了？\
于是我们就想到对它们取对数，原来 $\times 2$ 的操作就变成了 $+1$。（具体原因见对数运算法则）\
但是理论可行，实际做的时候你会发现~~毒瘤~~ c++ 会出现严重的精度问题。\
于是这种思路看起来已经不可行了。
## BUT！
## correct solution
我们考虑对数做法的过程，其实就是不断 $+1$ 直到不比前面小为止。那么把它转化为差分思想不就是差分数组非负吗？\
于是我们就可以直接考虑差分数组，如果 $a_i\le a_{i+1}$ 那么他们 $\log2$ 的差值可以当成一个缓冲变量 $d_i$，只要 $a_i\times 2$ 的次数小于 $d_i$，$a_{i+1}$ 就不需要操作。反之代表 $a_{i+1}$ 要比 $a_i$ 多操作 $d_i$ 次。\
具体细节可以见代码。
### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const double eps=1e-9;
int n,a[112345],c[112345];
int make_c(int x,int y){
    int res=0;
    while(x<y){
        res--;x<<=1;
    }
    while(x>y){
        res++;y<<=1;
    }
    return res;
}
void solve(){
    cin>>n;
    int ans=0;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=2;i<=n;++i){
        c[i]=make_c(a[i-1],a[i]);
    }
    for(int i=2;i<=n;++i){
        c[i]+=c[i-1];
        c[i]=max(0ll,c[i]);
    }
    for(int i=2;i<=n;++i){
        ans+=c[i];
    }
    cout<<ans<<'\n';
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```
## a special code by KrK
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> ii;

const int Maxn = 100005;

int T;
int n;
ii a[Maxn];

bool lessEq(const ii &a, const ii &b)
{
    int mn = min(a.second, b.second);
    ll A = ll(a.first) << ll(a.second - mn);
    ll B = ll(b.first) << ll(b.second - mn);
    return A <= B;
}

int main()
{
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i].first);
            a[i].second = 0;
        }
        ll res = 0ll;
        for (int i = 1; i < n; i++) {
            a[i].second = max(a[i - 1].second - 30, 0);
            while (!lessEq(a[i - 1], a[i]))
                a[i].second++;
            res += a[i].second;
        }
        printf("%I64d\n", res);
    }
    return 0;
}
```
这份代码真的能学习到很多很多东西。\
乍看之下 KrK 的代码和我们正常的没什么差别，但是仔细一看才发现他的精妙之处。\
他 `a[i].second = max(a[i - 1].second - 30, 0);` 这句话太美妙了，这其实是一个分块。因为输入的数最多就是 $10^9$，于是假如在输入以内，只需要暴力跳即可。\
而如果在输入限制以外，则一定是跳上来的，每次最多只会比上一个多跳 $1$ 次，所以之后的判断是 $O(1)$ 的。\
这看似是一个没什么用的小分块，但是蕴含的是他对这种题目性质敏锐的洞察力，这是十分宝贵的，并且只能通过做题的累积得到。

---

## 作者：FireRain (赞：0)

# 思路

因为对于所有的数直接暴力乘会炸，考虑统计对于每一个数的操作数量。

定义 $s_i$ 表示将前 $i$ 个数变合法，第 $i$ 个数需要的操作次数。

分类讨论一下 $a_{i - 1}$ 和 $a_i$ 的关系：

1. 如果 $a_{i - 1} \leq a_i$，说明在 $a_{i - 1}$ 不操作的情况下，可以让 $a_{i - 1}$ 操作 $\lfloor \log_{2}a_i - a_{i - 1} \rfloor$ 次。所以 $s_i = \max(0,s_{i - 1} - \lfloor \log_{2}a_i - a_{i - 1} \rfloor)$

2. 如果 $a_{i - 1} > a_i$，说明在 $a_{i - 1}$ 不操作的情况下，必须让 $a_i$ 操作 $\lceil \log_{2}a_{i - 1} - a_i \rceil$ 次。所以 $s_i = s_{i - 1} + \lceil \log_{2}a_{i - 1} - a_i \rceil$。

显然最终答案为 $\sum_{i = 1}^{n}{s_i}$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 1e5 + 10;
int T,n,ans;
int arr[N],s[N];

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

inline void solve(){
	int ans = 0;
	n = read();
	for (re int i = 1;i <= n;i++){
		s[i] = 0;
		arr[i] = read();
	}
	for (re int i = 2;i <= n;i++){
		if (arr[i - 1] < arr[i]) s[i] = max(0ll,s[i - 1] - (int)(floor(log2(1.0 * arr[i] / arr[i - 1]))));
		else s[i] = s[i - 1] + ceil(log2(1.0 * arr[i - 1] / arr[i]));
		ans += s[i];
	}
	printf("%lld\n",ans);
}

signed main(){
	T = read();
	while (T--) solve();
	return 0;
}
```

---

