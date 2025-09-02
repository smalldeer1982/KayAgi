# Coloring Game

## 题目描述

Alice 和 Bob 使用一个长度为 $n$ 的数列 $a$ 进行游戏。

初始时，任何数列中的数字都没有被染色。首先，Alice 选择 $3$ 个 $a$ 中的元素并将它们染为红色。然后 Bob 将选择一个任意元素并将它染为蓝色（如果这个元素原本是红色的，那么蓝色将覆盖掉红色）。Alice 获胜当且仅当剩余的红色的数字之和严格大于蓝色的数字。

你需要计算 Alice 有多少种选择 $3$ 个元素染色的方案使得无论 Bob 如何操作 Alive 都将获胜。

## 说明/提示

**样例解释**

对于前两组数据，无论 Alice 怎么选择元素，Bob 总有办法选择元素使得 Alice 不能获胜。

对于第三组数据，Alice 可以选择任意的三个元素。如果 Bob 选择对红色的某个元素染色，红色数字的和将为 $14$，蓝色数字的和将为 $7$；如果 Bob 选择对某个未染色的元素染色，红色数字的和将为 $21$，蓝色数字的和将为 $7$。

对于第四组数据，Alice 可以选择 $a_1,a_3,a_4$ 或 $a_2,a_3,a_4$。

## 样例 #1

### 输入

```
6
3
1 2 3
4
1 1 2 4
5
7 7 7 7 7
5
1 1 2 2 4
6
2 3 3 4 5 5
5
1 1 1 1 3```

### 输出

```
0
0
10
2
16
0```

# 题解

## 作者：lilong (赞：6)

设 Alice 取的位置为 $i,j,k$ 且 $i<j<k$，则 Bob 的最优策略有两种：取 $n$ 或 $k$。为了使 Alice 必胜，必须同时满足 $a_i+a_j+a_k>a_n,a_i+a_j>a_k$。枚举 $i,j$，显然满足两个条件的 $k$ 都是一段连续的区间。分别二分算出两个区间的边界，那么区间的交集即为合法的 $k$。时间复杂度 $O(\sum(n^2\log n))$。


```cpp
#include<iostream>
#include<cstdio>
#define N 5010
using namespace std;
int n,a[N];
long long ans;
void solve(){
    ans=0;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n-1;j++){
            int l=j+1,r=n,mid,ans1=n,ans2=j+1;
            if(a[i]+a[j]<=a[j+1])continue;
            while(l<=r){
                mid=(l+r)/2;
                if(a[i]+a[j]+a[mid]>a[n])ans1=mid,r=mid-1;
                else l=mid+1;
            }
            l=j+1,r=n;
            while(l<=r){
                mid=(l+r)/2;
                if(a[i]+a[j]>a[mid])ans2=mid,l=mid+1;
                else r=mid-1;
            }
            if(ans2>=ans1) ans+=ans2-ans1+1;
        }
    }
    cout<<ans<<'\n';
}
int main(){
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：Revitalize (赞：3)

蒟蒻太菜了，这种唐题都被卡了 $4$ 发罚时，是不是应该退役……    

>题意：    
>在一个正整数序列中选择 $3$ 个数涂红，再选 $1$ 个数涂蓝，蓝色可以覆盖红色，问有多少个三元组，满足：将它们涂成红色后，无论哪一个数涂蓝，都有红色数的和严格大于蓝色数。  

$n$ 范围很小，这启示我们使用 $O(n^2)$ 解法。  

其实题面的描述已经很通俗易懂了。  
首先，序列的顺序不影响最终的答案，那么可以将序列由大到小排序。  
再定义：$C(x,l,r)$ 为排序后下标 $[l,r]$ 范围内有多少个二元组的和严格大于 $x$。  
然后我们可以想到分讨：（注意，下文中“最大值”若无特殊说明，则指整个序列的最大值）    
**【Case 1】**  
如果最大值的数量 $k$ 大于等于 $3$ ，选 $3$ 个最大值涂红，此时显然无论把哪个数涂蓝，都不可能更大。  
一共就是 $\binom{k}{3}$ 种选法。  
**【Case 2】**  
如果最大值的数量 $k$ 大于等于 $2$ ，且序列存在非最大值，选 $2$ 个最大值涂红，再选任意一个非最大值涂红，此时显然无论把哪个数涂蓝，都不可能更大。  
一共就是 $\binom{k}{2}(n-k)$ 种选法。  
**【Case 3】**  
如果序列存在非最大值，选 $1$ 个最大值涂红，再选 $2$ 个非最大值涂红，此时涂蓝一个最大值对于蓝色来说是最优的，所以我们需要使那两个非最大值的和严格大于最大值。  
一共就是 $k\times C(m,k+1,n)$ 种选法，其中 $m$ 是最大值。  
**【Case 4】**    
如果序列存在非最大值，选 $3$ 个非最大值 $x,y,z$ 涂红，此时涂蓝一个最大值，或者是涂蓝 $\max(x,y,z)$ 对于蓝色来说都可能是最优的，所以我们需要使那三个非最大值的和严格大于最大值，同时较小的两个数的和严格大于三个数中最大的那个。    
枚举三个数中的最大数，一共就是 $\displaystyle\sum_{i=k+1}^{n-2} C(\max(m-a_i,a_i),i+1,n)$ 种选法，其中 $m$ 是最大值。  

现在我们来考虑 $C(x,l,r)$ 的计算，由于 $a$ 已经从大到小排序，所以可以双指针 $O(n)$ 维护，做法很显然，两个指针 $i,j$ 分别维护二元组的两个值的下标，始终保证 $i<j$，然后 $i$ 每往后移动一位，$j$ 就根据目前的 $a_i$ 往前移动，直到 $a_i+a_j$ 恰好刚刚大于 $x$，此时答案加上 $j-i$ 即可，代表着 $a_i+a_{[i+1,j]}$ 都大于 $x$。  

所以总体就是 $O(n^2)$。  

```cpp
#include <bits/stdc++.h>
#define sor(i, l, r) for (int i = l; i <= r; i++)
#define int unsigned long long
using namespace std;
namespace Revitalize
{
    const int N = 5e5;
    int T, n, a[N];
    int solve(int x, int l, int r)
    {
        int res = 0, j = r;
        for (int i = l; i <= r; i++)
        {
            if (j <= i)
                break;
            while ((a[i] + a[j] <= x) && (j > i + 1))
                j--;
            if (a[i] + a[j] > x)
                res += j - i;
        }
        return res;
    }
    inline void work()
    {
        cin >> T;
        while (T--)
        {
            cin >> n;
            sor(i, 1, n) cin >> a[i];
            sort(a + 1, a + n + 1, greater<int>());
            int b = n + 1;
            sor(i, 1, n)
            {
                if (a[i] != a[1])
                {
                    b = i;
                    break;
                }
            }
            int ans = 0;
            if (b - 1 >= 3)
                ans += (b - 1) * (b - 2) * (b - 3) / 6;
            if (b - 1 >= 2 && b != n + 1)
                ans += (b - 1) * (b - 2) * (n - b + 1) / 2;
            if (b != n + 1)
                ans += solve(a[1], b, n) * (b - 1);
            for (int i = b; i <= n - 2; i++)
            {
                ans += solve(max(a[1] - a[i],a[i]), i + 1, n);
            }
            cout << ans << "\n";
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    return Revitalize::work(), 0;
}
```

---

## 作者：MaxBlazeResFire (赞：2)

题解怎么都带 $\rm log$。

全局最大值为 $a_n=M$。由题意，若红方选数 $(x,y,z)$ 合法，应有 $a_x+a_y>a_z$ 且 $a_x+a_y+a_z>M$。

枚举 $z$。我们发现若给定 $y<z$，能成立的 $x$ 是一个对于 $y$ 的后缀。做一个双向的双指针即可，当 $x$ 指针与 $y$ 指针相遇时跳出。

复杂度 $O(n^2)$。

```
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define MAXN 5005
int n,a[MAXN];

inline void solve(){
	scanf("%d",&n);
	for( int i = 1 ; i <= n ; i ++ ) scanf("%d",&a[i]);
	ll Ans = 0;
	for( int M = 3 ; M <= n ; M ++ ){
		int l = 1,r = M - 1;
		while( 1 ){
			while( l < r && ( a[l] + a[r] <= a[M] || a[l] + a[r] + a[M] <= a[n] ) ) l ++;
			Ans += r - l;
			if( l == r ) break;
			r --;
		}
	}
	printf("%lld\n",Ans);
}

signed main(){
	int testcase; scanf("%d",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：Meng_Xiangyu (赞：2)

一定要慢慢的、有耐心的认真读！

当我们拿到一个题，要先看数据范围，而这个题的数据范围直接告诉我们要暴力了。因此，暴力枚举 Alice 将要选择的三个数中的较小的两个数，我们设其分别为 $x,y$。

第三个数呢？我们先设第三个数为 $z$。首先，由题意可知 Bob 可以选 Alice 已经选了的数，所以就要保证 $z<x+y$，否则 Bob 选 $z$ 的话 Alice 就输了。

之后，还要保证 $x+y+z$ 小于 $a$ 的最大值，否则 Bob 选 $a$ 中的最大值 Alice 也会输。我们设 $a$ 中的最大值为 $b$，由上面的推理得

$$x+y+z>b$$

移项得

$$z>b-x-y$$

再结合上面 $z<x+y$，得

$$b-x-y<z<x+y$$

之后，数据范围又告诉我们 $a$ 单调不降，所以我们很快就想到：对于 $z$ 的求解，可以用两次二分来解它的范围。

所以最后的思路便是：先暴力枚举较小的两数 $x,y$，然后两次二分查找 $a$ 中满足 $b-x-y<z<x+y$ 的解的数量，最后累加起来即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define fir first
#define sec second
#define fst ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
const int N=1e6+5,INF=0x3f3f3f3f3f3f3f3f;
int ans=0;

int n;
int a[N];

void code(){
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			int l=j+1,r=n,res=j;
			while(l<=r){
				int mid=l+r>>1;
				if(a[mid]<a[i]+a[j]){
					res=mid;
					l=mid+1;
				}else{
					r=mid-1;
				}
			}
			l=j+1,r=n;int res2=n;
			while(l<=r){
				int mid=l+r>>1;
				if(a[mid]>a[n]-a[i]-a[j]){
					res2=mid;
					r=mid-1;
				}else{
					l=mid+1;
				}
			}
			ans+=max(0ll,res-res2+1);
		}
	}
	cout << ans << endl;
	ans=0;
}

signed main(){
	fst
	int t;
	cin >> t;
	while(t--){
		code();
	}
	return 0;
}
```

---

## 作者：liluhexuan (赞：2)

~~很明显，二分和双指针对于我都太难了，所以我决定提供一种树状数组解法。~~

我们考虑到枚举 $i,j$，然后寻找第三个点。

很明显，Bob 为了尽量取得高分，要么取全局最大值，要么取 Alice 选的最大值。两种分别可以为 Bob 提供 $a_n$ 和 $2 \times a_i$ 的收益（因为在第二种情况下，Alice 少了 $a_i$，Bob 多了 $a_i$，故 Bob 可以得到这么多收益）。Bob 肯定会选大的。所以我们设立一个 $b_i$ ，表示选这个点可以为 Alice 提供多少的负收益（即 Bob 得到分数减去 Alice 得到的分数）。至于什么时候能选这个点，自然就是 $b_i$ 给 Alice 带来的负收益小于 $a_i$ 和 $a_j$ 为其所带来的正收益即可。也就是要找到 $b_k<a_i+a_j$（$k \ge j$）。然后我们就可以用树状数组了。

别忘了求 $b_i$ 时加上选第三个点是给爱丽丝带来的收益！

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
const int N=5005,M=4e5+10;
int d[M],m; //树状数组模板
int lowbit(int x){
	return x&-x;
}
void add(int x,int k){
	while(x<=m){
		d[x]+=k;
		x+=lowbit(x);
	}
}
int query(int x){
	int sum=0;
	while(x){
		sum+=d[x];
		x-=lowbit(x);
	}
	return sum;
}
int a[N];
void slove(){
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	m=a[n]*2,add(a[n],1);
	for(int j=n-1;j>=1;j--){
		for(int i=1;i<j;i++)
			ans+=query(a[i]+a[j]-1);
		add(max(a[n]-a[j],a[j]),1); //代码里 max(a[n]-a[j],a[j]) 就是 b_i
	}
	cout<<ans<<endl;
	for(int j=n;j>=1;j--)
		add(max(a[n]-a[j],a[j]),-1); //省时间的清空
}
signed main(){
	int T;
	cin>>T;
	while(T--) slove(); 
	return 0;
}
```

时间复杂度 $\mathcal O(n^2\log n)$。

~~无耻地~~求过。

---

## 作者：ycx20120224 (赞：1)

## 思路
首先，假设你是 Bob，在 Alice 从数列中选了三个数（设它们分别是 $a_i$,$a_j$ 和 $a_k$，且 $i<j<k$）染成红色之后，你会如何操作？显然为了尽可能使你的分数比 Alice 大，你应当将 $a_n$ 或 $a_k$ 染成蓝色。  
所以，如果要让 Alice 必赢，应当满足以下两个条件：
$$
a_i+a_j>a_k
$$
$$
a_i+a_j+a_k>a_n
$$
这样我们可以得到一个暴力代码，每次枚举 $i$,$j$,$k$。但这种做法显然会超时，考虑优化。  
注意到 $k$ 可取的范围一定是一个区间，左边界 $L$ 被 $a_i+a_j+a_k>a_n$ 确定，右边界 $R$ 被 $a_i+a_j>a_k$ 确定，找到左右界点，将答案加上 $R-L+1$ 即可。因为数列 $a$ 满足单调不减，使用二分查找界点。  
## 贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T;
int main(){
	cin>>T;
	while(T--)
	{
		long long n,ans = 0,a[5005]={0};
		cin>>n;
    	for(int i = 1; i <= n; i++)cin>>a[i];
		for(int i = 1; i <= n; i++)
		{
			for(int j = i + 1; j <= n; j++)
			{
				long long l=j+1,r=n,mid,L=0,R=0;//L和R代表区间界点 
				while(l<=r)//二分查找区间右界点
				{
					mid=(l+r)/2;
					if(a[i]+a[j]>a[mid])
					{
						l=mid+1;
						R=mid;
					}
					else r=mid-1;
				}
				l=j+1,r=R;
				while(l<=r)//二分查找区间左界点
				{
					mid=(l+r)/2;
					if(a[i]+a[j]+a[mid]>a[n])
					{
						r=mid-1;
						L=mid;
					}
					else l=mid+1;
				}
				if(R!=0 && L!=0)
					ans=ans+(R-L+1);
			}
		}
		cout<<ans<<'\n';
	}
    return 0;
}
```

---

## 作者：Mason123456 (赞：1)

题解区简单易懂的 $O(n^2)$ 写法。阅读题解时请最好深刻理解题意。

***

首先，选择的 $3$ 个整数（设它为 $c_1, c_2, c_3$），必须满足**三角不等式**（即令：$c_1 \le c_2 \le c_3$，有 $c_1 + c_2 > c_3$）。

其次，令 $mx = \max(\{a_1, a_2, \dots , a_n\})$，$c_1 + c_2 + c_3 > mx$​。

***

假如枚举 $c_1, c_2$，令 $c_1 \le c_2$，考虑 $c_3$ 的范围（根据**三角不等式**）：$c_3 + c_1 > c_2 \Rightarrow c_3 > c_2 - c_1$ 并且 $c_1 + c_2 > c_3 \Rightarrow c_3 < c_1 + c_2$。

所以 $c_3 \in (c_2 - c_1, c_2 + c_1)$​。

因为 $c_1 + c_2 + c_3 > mx$，所以 $c_3 > mx - (c_1 + c_2)$。

所以 $c_3 \in (\max(c_2 - c_1, mx - c_1 - c_2), c_1 + c_2)$。

补充说明：$x \in (a, b)$ 表示 $a < x < b$。

***

因为 $c_3 \in (\max(c_2 - c_1, mx - c_1 - c_2), c_1 + c_2)$，所以 $c_3$ 的取值个数可以用**前缀和预处理**。

用前缀和预处理之后，可能出现 $c_1, c_2$ 在区间内的情况，所以需要减去一些贡献。

前缀和处理：预处理出每个数字 $i$ 出现的次数 $val_i$，然后 $s_i$ 表示 $\le i$ 的数字出现的次数。

最后，$ans$ 是每个 $c_3$ 的「可以的取值个数」的「总和」除以 $3$。

***

细节：区间右端点 $c_1 + c_2$ 可能越界。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 1e5 + 5;

int val[N];// val[i] 表示有多少为值 i 的数
long long s[N];// s[i] 表示有多少 <= i 的数

long long get(int l, int r, int c1, int c2){// 处理前缀和
    if(l > r)   return 0;
    r = min(r, N - 1);
    return s[r] - s[l - 1] - (l <= c1 && c1 <= r) - (l <= c2 && c2 <= r);
    // 前面是前缀和，后面是要减去如果 c1 或者 c2 在区间 [l, r] 中间，那么就不能重复用 c1 或者 c2 了。
    // 容易证明，减去 c1, c2 的贡献之后，原式 >= 0。
}

void sol(){
    memset(val, 0, sizeof val); // 10^3 * 10^5 根本不慌
    int n;  cin>>n;
    vector<int> a(n + 1);
    for(int i = 1;i <= n;i++)   cin>>a[i], val[a[i]]++;
    for(int i = 1;i < N;i++)    s[i] = s[i-1] + val[i];
    long long ans = 0;
    for(int i = 1;i <= n;i++){
        for(int j = i + 1;j <= n;j++){
            ans += get(max(a[j] - a[i], a[n] - a[i] - a[j]) + 1, a[i] + a[j] - 1, a[i], a[j]);
            // 这里的 c1 == a[i]，c2 == a[j]，因为前缀和是处理闭区间的，所以手动 +1, -1。
            // 后面两个变量传入 c1, c2，如果 c1, c2 在区间内的话，区间数量要减一点。
        }
    }
    cout<<ans / 3<<'\n';// 减去重复贡献。
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;  cin>>t;
    while(t--)  sol();
    return 0;
}
```

---

## 作者：_xdd_ (赞：0)

似乎是题解区里没有的解法喵。

---

### 题意简述：

一个数列，长度为 $N$，小 A 任选三个数字染成红色，随后小 B 选一个数字把他染成蓝色（可以覆盖在红色上）。若红色数字之和严格大于蓝色数字则小 A 胜，求无论小 B 怎么操作，小 A 都能胜利的染色方案的数量。

### 解法

模拟 + 贪心 + 后缀和。

设我们选的三个数字**从小到大**分别为 $k,x,y$，数列最大值为 $m$，需要满足 $x+k>y$ 且 $x+y+k>m$。

显然，$k$ 的取值范围为 $k> \max(m-x-y,y-x)$，也可写作 $k\ge \max(m-x-y+1,y-x+1)$

然后，$k$ 的取值范围会有一部分与 $x,y$ 选过的范围重合，减去即可，显然，$x,y$ 选过的数字数量为 $N-\min(x,y)+1$。

记得特判当 $x=m$ 或 $y=m$ 的情况，将其变为 $0$ 即可。

要查询 $k$ 的取值数量，可以开一个桶记录数列里数字的数量，然后做一个后缀和，可以做到 $\mathcal{O}(1)$ 的查询。

所以具体实现为：

- 预处理：清空数组（多测记得清空），输入数据，桶 + 后缀和。
- 双重循环 $x,y$，特判，计算答案
- 输出。

### code

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define r0 return 0
#define inf (0x7fffffff)
#define maxn ( 100000 +5)
#define int long long
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
int t,n,a[maxn],vis[maxn];
signed main(){
    cin >> t;
    while(t--){
        memset(vis,0,sizeof(vis));
        cin >> n;
        for(int i=1;i<=n;i++){
            cin >> a[i];
            vis[a[i]]++;
        }
        int num=a[n];
        for(int i=num;i>=0;i--){
            vis[i]+=vis[i+1];
        }
        int ans=0;
        for(int i=n;i>1;i--){
            for(int j=i-1;j>=1;j--){
                int x=a[i],y=a[j];
                if(x==num)x=0;
                else if(y==num)y=0;
                int k=max(num-x-y+1,x-y+1),sum=n-min(i,j)+1;
                ans+=max(0LL,vis[max(k,0LL)]-sum);
            }
        }
        cout << max(ans,0LL) << endl;
    }
}
```

---

## 作者：limingyuan333 (赞：0)

### 前言：
啊，这道题居然题解都是二分之类的做法，但这不是一眼双指针吗？让我来提供一个 $O(n^2)$ 的做法吧。

### 题意转化：
可以转化为 对于选择的 三个位置 $i$，$j$，$k$ ，需要满足以下两点要求：

- 需要保证 $a_i+a_j>a_k（i \neq j,j \neq k）$
- 当满足 $k \neq n$ 时需要满足 $a_i+a_j+a_k>a_n$

有了这两点要求我们就可以做了。具体的，可以用一个指针表示 $k$ 可以被计入答案的最右端点，另一个表示 $k$ 可以计入答案的最左端点，由于序列排序后是单调不降的，所以可以用双指针移动来维护，具体看代码吧！


```cpp
#include<bits/stdc++.h>
#define rint register int 
#define int long long
using namespace std;
const int MAXN=5e3+10;
int n,a[MAXN];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL),cout.tie(NULL);
	int T;cin>>T;
	while(T--){
		cin>>n;
		for(rint i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+1+n);int ans=0;
		for(rint i=1;i<=n;i++){
			int R1=i+1,R2=n;//R1是可以到达的最右端点，R2则是最左端点 
			for(rint j=i+1;j<n;j++){
				while(a[R1+1]<a[i]+a[j]&&R1+1<=n)  R1++;//可以移动就尽量移 
				while(a[R2-1]>a[n]-a[i]-a[j]&&R2-1>=j) R2--; //同理 
				if(R1==n) ans+=R1-j;//R1==n时没有限制，因为已经找不到更大的数了 
				else ans+=max(0ll,(R1-max(j,R2-1))); //计算区间贡献 
			}
		}cout<<ans<<'\n';//记得开long long 
	}
	return 0;
}
```

---

## 作者：_qhbd_ (赞：0)

# 题意
有一个长 $n$ 的整数序列 $a$，开始所有数字都没有颜色，小 $A$ 先选择三个数涂上红色，小 $B$ 再选择一个数涂上蓝色（蓝色可覆盖小 $A$ 涂上的红色），问小 $A$ 最后有多少种方案使得无论小 $B$ 如何操作，红色的数总和总是严格大于蓝色的数。

$t\le10^3$ 组多测，$\sum n\le 5\times10^3,a_i\le10^6$，$a$ 序列单调递增。
# 思路
我们总结一下题目：

给定一个大小 $n$ 的序列 $a$，小 $A$ 先选择 $a_{i_1},a_{i_2},a_{i_3}(i_1<i_2<i_3)$，小 $B$ 再选择一个数 $a_j$。如果 $j=i_x(x\in[1,3])$，则视为小 $A$ 失去了所选的 $a_{i_x}$。问有多少种方案满足小 $B$ 取任何数都使得小 $A$ 得数字总和严格大于 $a_j$。

不妨翻转一下序列 $a$，使其单调递减。同时我们令值 $m$ 等于小 $A$ 数总和减去小 $B$ 所选数的值，那么若 $m>0$，则该方案成立。因为无论小 $B$ 如何操作都要确保 $m>0$，所以我们不必考虑小 $B$ 所有操作的情况，直接考虑其最优解即可。

考虑小 $A$ 取三个数 $a_{i_1},a_{i_2},a_{i_3}$：

- 如果小 $B$ 选择 $a_{i_x}(x\in[1,3])$，因为 $a$ 单调递减， 小 $B$ 最优选择 $a_{i_1}$，也就是三个数种最大的一个。最后 $m=a_{i_2}+a_{i_3}-a_{i_1}$。
- 如果小 $B$ 选择 $a_{i_x}(x\in[1,3])$ 外的其他数，同上道理，最优选择 $a_1$。最后 $m=a_{i_2}+a_{i_3}+a_{i_1}-a_1$。

小 $B$ 最优解下 $m=\min(a_{i_2}+a_{i_3}-a_{i_1},a_{i_2}+a_{i_3}+a_{i_1}-a_1)=a_{i_2}+a_{i_3}+\min(-a_{i_1},a_{i_1}-a_1)$。

不难观察到，我们可以把 $m$ 分 $a_{i_2}+a_{i_3},\min(-a_{i_1},a_1-a_{i_1})$ 两部分处理，遍历序列对于每一个 $a_{i_1}$，求出所有满足 $m>0$ 的 $a_{i_2},a_{i_3}$。考虑到 $\sum n\le 5\times10^3$，暴力地套三层循环肯定有问题，我们考虑遍历 $a_{i_1},a_{i_2}$，对于 $a_{i_3}$ 二分求解。

因为如果 $i_1=1$ 第二种情况本应该为 $m=a_{i_2}+a_{i-3}-a_{i_1}$，明显与分析不符，但是因为这是特例，特判即可。

注意到最多有 $C_n^3>2\times10^9$ 种方案。

时间复杂度 $O(n^2\log n)$。
# 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e3+5;
int n,a[N];
long long ans;
inline bool cmp(int x,int y){return x>y;}
inline void solve(){
	scanf("%d",&n);
	for(int i=n;i>=1;i--)scanf("%d",&a[i]);
	if(n==3){
		if(a[1]>=a[2]+a[3])puts("0");
		else puts("1");
		return;
	}
	if(a[1]>=a[2]+a[3]+a[4])return puts("0"),void();
	ans=0;
	for(int i=1;i<n-1;i++){
		int x=min(-a[i],a[i]-a[1]);
		if(i==1)x=-a[i];
		for(int j=i+1;j<n;j++){
			int l=j,r=n;
			while(l<r){
				int mid=l+r+1>>1;
				if(x+a[j]+a[mid]>0)l=mid;
				else r=mid-1;
			}
			ans+=l-j;
		}
	}
	printf("%lld\n",ans);
	return;
}
int main(){
	int t;scanf("%d",&t);
	while(t--)solve();
	return 0;
}
```

---

## 作者：sSkYy (赞：0)

# [CF2112C Coloring Game](https://www.luogu.com.cn/problem/CF2112C)

## 题意

Alice 和 Bob 正在玩一个游戏，使用一个大小为 $n$（$1 \leq n \leq 5000$）的整数数组 $a$。

$a$ 数组中的元素已从小到大排序。

初始时，数组中的所有元素都是无色的。

首先，Alice 选择 $3$ 个元素并将它们染成红色。

然后 Bob 选择任意**一个**元素并将其染成蓝色（如果它已经是红色，则覆盖）。

如果红色元素的和**严格大于**蓝色元素的值，Alice 获胜。

你的任务是计算 Alice 选择 $3$ 个元素的方式数，使得无论 Bob 如何操作，Alice 都能获胜。

## 题解

假设 Alice 已经选了三个元素 $(a_i,a_j,a_k)$，满足 $i<j<k$。

假设 Bob 选了 $a_x$，显然 $a_x$ 只会是 $a_n$ 或者 $a_k$，所以有：
$$
s.t.
\left\{
\begin{array}{}
a_i+a_j+a_k>a_n\\
a_i+a_j>a_k
\end{array}
\right.
$$

转换一下，有 $a_n-a_i-a_j+1\leq a_k\leq a_i+a_j$，由于 $n$ 最大只有 $5000$，可以 $O(n^2)$ 的枚举 $a_i$ 和 $a_j$，再用树状数组维护出 $a_k$，做到 $O(n^2 \log V)$。

具体的，由于需要满足 $i<j<k$，所以我们要倒序枚举 $a_j$，同时维护 $a_k$，再枚举 $a_i$，最后统计合法的 $a_k$ 数量。

注意每个测试点结束后要清空树状数组，而且不能暴力清空，得写一个 $\text{del}$ 函数。

记得开 `long long`。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
const int M=1e5+5;
int n;
int a[N];

//树状数组
int t[M];
void upd(int x){ for(;x<M;x+=x&(-x)) t[x]++; }
void del(int x){ for(;x<M;x+=x&(-x)) t[x]--; }
int ask(int x){
    if(x<=0) return 0;
    int res=0;
    for(;x;x-=x&(-x)) res+=t[x];
    return res;
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int an=a[n];
    long long ans=0;
    for(int j=n-1;j>=2;j--){//枚举 a_j
        upd(a[j+1]);//维护 a_k
        for(int i=j-1;i>=1;i--)//枚举 a_i
            ans+=(long long)max(0,ask(min(an,a[i]+a[j]-1))-ask(an-a[i]-a[j]));//计算合法的 a_k 数量
    }
    cout<<ans<<"\n";
    for(int i=3;i<=n;i++) del(a[i]);//清空树状数组
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：chatoudp (赞：0)

Bob 在 Alice 选完后有 $2$ 种选法，一种是把 Alice 选的最大的变成蓝色，另一种是把剩下没被 Alice 选的最大的染成蓝色。

所以 Alice 要严格大于 Bob 需要满足（设 Alice 选了的三个数为 $x,y,z$ 且 $x\le y\le z$）： $x+y>z$ 且 $x+y+z>a_n$。

我们可以先固定 $z$，然后就发现 $x+y$ 需要大于 $\max(z,a_n-z)$，于是就转换成了求 $a$ 数组的前缀有多少种选择 $2$ 个数使得其和大于某个数的方法数的问题。

我们再枚举 $y$ 然后用二分即可。

AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T,a[5005],n;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		long long ans=0;
		for(int i=1;i<=n;i++){
			int qwq=max(a[i],a[n]-a[i]);
			for(int j=2;j<i;j++) ans+=j-(upper_bound(a+1,a+j,qwq-a[j])-a); 
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

