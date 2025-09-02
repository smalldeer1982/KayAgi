# Array Game

## 题目描述

You are given an array $ a $ of $ n $ positive integers. In one operation, you must pick some $ (i, j) $ such that $ 1\leq i < j\leq |a| $ and append $ |a_i - a_j| $ to the end of the $ a $ (i.e. increase $ n $ by $ 1 $ and set $ a_n $ to $ |a_i - a_j| $ ). Your task is to minimize and print the minimum value of $ a $ after performing $ k $ operations.

## 说明/提示

In the first test case, after any $ k=2 $ operations, the minimum value of $ a $ will be $ 1 $ .

In the second test case, an optimal strategy is to first pick $ i=1, j=2 $ and append $ |a_1 - a_2| = 3 $ to the end of $ a $ , creating $ a=[7, 4, 15, 12, 3] $ . Then, pick $ i=3, j=4 $ and append $ |a_3 - a_4| = 3 $ to the end of $ a $ , creating $ a=[7, 4, 15, 12, 3, 3] $ . In the final operation, pick $ i=5, j=6 $ and append $ |a_5 - a_6| = 0 $ to the end of $ a $ . Then the minimum value of $ a $ will be $ 0 $ .

In the third test case, an optimal strategy is to first pick $ i=2, j=3 $ to append $ |a_2 - a_3| = 3 $ to the end of $ a $ . Any second operation will still not make the minimum value of $ a $ be less than $ 3 $ .

## 样例 #1

### 输入

```
4
5 2
3 9 7 15 1
4 3
7 4 15 12
6 2
42 47 50 54 62 79
2 1
500000000000000000 1000000000000000000```

### 输出

```
1
0
3
500000000000000000```

# 题解

## 作者：huangrenheluogu (赞：3)

这道题还是比较有意思的。

首先发现 $k\ge 3$ 的时候答案显然为 $0$。

当 $k\ge3$ 的时候，可以进行两次 $a_1,a_2$ 得到相同的数，这两个相同的数进行操作即可。

- $k=1$

直接 $\mathcal{O}(n^2)$ 暴力算即可，注意本身也可能是。

- $k=2$

将 $a$ 排序，然后取出两个数进行计算差值 $tem$，接着进行二分，计算 $a$ 数组中和 $tem$ 最接近的那个数，更新即可。

一组数据的复杂度至多为 $\mathcal{O}(n^2\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2005, inf = 9e18;
int T, n, a[N], k, ans, tem, l, r, mid;
signed main(){
	scanf("%lld", &T);
	while(T--){
		scanf("%lld%lld", &n, &k);
		for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		if(k >= 3){
			printf("0\n");
			continue ;
		}
		if(k == 1){
			ans = inf;
			for(int i = 1; i <= n; i++){
				ans = min(ans, a[i]);
				for(int j = i + 1; j <= n; j++){
					ans = min(ans, abs(a[i] - a[j]));
				}
			}
		}
		if(k == 2){
			ans = inf;
			sort(a + 1, a + n + 1);
			for(int i = 1; i <= n; i++){
				ans = min(ans, a[i]);
				for(int j = i + 1; j <= n; j++){
					tem = a[j] - a[i];
					ans = min(ans, tem);
					l = 1, r = n;
					while(l <= r){
						mid = l + r >> 1;
						ans = min(ans, abs(tem - a[mid]));
						if(a[mid] >= tem) r = mid - 1;
						else l = mid + 1;
					}
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

[评测链接](https://codeforces.com/contest/1904/submission/236976534)

---

## 作者：MicroSun (赞：3)

分类讨论+双指针好题。

## 题目大意

- 给你一个数组 $a$ 和操作数 $k$，你必须进行 $k$ 次操作。

- 每次操作，选取一对 $(i,j)$，并将 $|a_i-a_j|$ 加入数组。

- 你要用这些操作使 $a$ 的最小值最小，输出这个最小值。

- $\sum n \le 2 \cdot 10^3$

## 思路

分类讨论。

当 $k=1$ 时，将数组进行排序，答案明显为 $\min \limits_{i=1}^{n-1} a_{i+1}-a_i$。

当 $k=2$ 时，一样先将数组排序。暴力枚举每一对 $(i,j)$ 并计算出 $|a_i-a_j|$（第一次操作），后用双指针或二分确定第二次操作的最小值即可。

实现时，记得统计原数组的最小值并与所求得的值进行比较。

当 $k=3$ 时，可以将任意一对 $(i,j)$ 进行两次操作并将其结果再进行一次操作，一定可以得到最小值 $0$。输出即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline ll read(){
    ll x=0;bool w=0;char ch=getchar();
    while((ch<'0'||ch>'9')&&(ch^45)&&(ch^-1)) ch=getchar();
    (!(ch^45)&&(w=1,(ch=getchar())));
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return w&&(x=-x),x;
}
inline void write(ll x,char l='\n'){
    if(!x){putchar('0');putchar(l);return;}
    int cnt=0;
    static char ch[55];
    ((x<0)&&(putchar('-'),(x=-x)));
    while(x) ch[++cnt]=x%10+48,x/=10;
    while(putchar(ch[cnt]),--cnt);
    putchar(l);
}
using pii=pair<int,int>;
#define pb push_back
void solve(){
	int n=read(),k=read();
	vector<ll> ve(n+1);
	ll minn=LLONG_MAX;
	for(int i=1;i<=n;i++) minn=min(minn,ve[i]=read());
	if(k>=3){write(0);return;}
	sort(begin(ve)+1,end(ve));
	for(int i=1;i<n;i++) minn=min(minn,ve[i+1]-ve[i]);
	if(k==1){write(minn);return;}
	for(int i=1;i<n;i++){
		ll m=0;//双指针，用一个指针确定 |ai-aj| 的位置
		for(int j=i+1;j<=n;j++){
			ll p=ve[j]-ve[i];
			while(m<n&&ve[m]<p) m++;
			m--;
			if(!m) minn=min(minn,abs(p-ve[1]));//特判
			else minn=min(minn,min(abs(p-ve[m]),abs(p-ve[m+1])));
		}
	}
	write(minn);
}
int main(){
	int t=1;
	t=read();
	while(t--) solve();
}
```

---

## 作者：Zinc_acetate (赞：1)

~~[更好的阅读体验](https://www.luogu.com.cn/blog/ZincAcetate/solution-cf1904c)~~

### 题目传送门

[codeforces](https://codeforces.com/problemset/problem/1904/C)

[洛谷](https://www.luogu.com.cn/problem/CF1904C)

### 题目大意

给你一个由 $n$ 个正整数组成的数组 $a$。在一次操作中，选取 $(i, j)$，将 $|a_i - a_j|$ 加到 $a$ 的末尾。你的任务是在执行 $k$ 操作后，最小化最后数组 $a$ 的最小值。

### 思路

分三种情况：

- $k \geq 3$ 时，我们可以取两次相同的 $|a_i - a_j|$，这样数组中就会出现两个相同的数，第三次操作取这两个相同的数即可，可以保证最小值为 $0$；

- $k=1$ 时，我们暴力枚举每组 $|a_i - a_j|$，然后直接取数组 $a$ 和枚举出的每组 $|a_i - a_j|$ 的最小值；

- $k=2$ 时，我们考虑先暴力枚举出每组 $|a_i - a_j|$，并对原数组 $a$ 排序，对于每个得到的 $|a_i - a_j|$，在排好序的原数组 $a$ 中二分找到与这个值最接近的数，和它取差值，最后答案就是原数组 $a$、暴力枚举出每个 $|a_i - a_j|$、二分找到的数取的差值，这三组数中的最小值。

最坏情况时间复杂度 $O(n^{2}\log{n})$，可以接受。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
void solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	if (k >= 3)
	{
		cout << 0 << endl;
		return;
	}
	int minn = LLONG_MAX;
	for (int i = 0; i < n; i++)
	{
		minn = min(minn, a[i]);
	}
	vector<int> b;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			int c = abs(a[i] - a[j]);
			b.push_back(c);
			minn = min(minn, c);
		}
	}
	if (k == 1)
	{
		cout << minn << endl;
		return;
	}
	sort(a.begin(), a.end());
	for (auto i : b)
	{
		int l = 0, r = n - 1, mid, d = 0;
		while (l <= r)
		{
			mid = (l + r) >> 1;
			if (a[mid] <= i)
			{
				l = mid + 1;
				d = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
		minn = min(minn, abs(a[d] - i));
		if (d != n - 1)
			minn = min(minn, abs(a[d + 1] - i));
	}
	cout << minn << endl;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
}
```

---

## 作者：kczw (赞：1)

# 题意
共 $t$ 组数据，每组给定一个长为 $n$ 的序列 $a$，你可以操作 $k$ 次。

每次操作选择序列的任意两个位置不同的数，将它们的差的绝对值添加进序列里。

求 $k$ 此操作后，序列里最小的数是多少。
# 思路
首先可以知道，设有 $a_i$ 和 $a_j$，它们的差为 $a_i-a_j$，我们添加两次，就会至少有两个一样的元素在 $a$ 中，最后择这两个数相减得到最小可能的答案 $0$。

所以我们知道 $3\le k$ 时，直接可以输出 $0$，接下来考虑其他情况，即 $k=1$ 或 $k=2$。

关于这个我们可以暴力地求出所有 $k=1$ 所能得出的数，其次我们可以二分查找距离每个数最近的数，最后统计最小的值就是 $k=2$ 所能达到的最小值了。
# 实现
```cpp
#include<iostream>
#include<algorithm>
#define int long long
#define abs(x) x<0?-x:x
using namespace std;
int t,n,k,res1,res2,a[2005];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		sort(a,a+n+1);
		if(k>=3){
			printf("0\n");
			continue;
		}res1=a[1];res2=1e18;
		for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			res1=min(res1,a[j]-a[i]);
			int id=lower_bound(a+1,a+n+1,a[j]-a[i])-a;
			res2=min(res2,min(abs(a[id]-a[j]+a[i]),abs(a[j]-a[i]-a[id-1])));
		}if(k==1)printf("%lld\n",res1);
		else printf("%lld\n",res2);
	}
	return 0;
}
```

---

## 作者：Infinite_Loop (赞：0)

# CF1904C
## 题意
给定一个长度为 $n$ 的数组 $a$，你可以进行 $k$ 次操作，每次操作可以将 $a$ 数组中任意两个数的差放入 $a$ 数组中，问最后的最小值最小是多少。
## 思路
很明显，本题是一道找规律的题目。分类讨论 $k$ 的值：

- 当 $k=1$ 时，只能进行一次操作，可以先求出 $a$ 数组中最小的数，再两两求差，最后输出两者中的最小值即可。时间复杂度为 $\mathcal{O}(n^2)$。

- 当 $k=2$ 时，一开始和 $k=1$ 的方案一样，只需要在求完每两个数的差后，进行二分查找即可。时间复杂度为 $\mathcal{O}(n^2 \log n)$。

- 当 $k\ge 3$ 时，可以将任意两个数求差两次放入数组 $a$，在把这两个差再次求差，很明显答案为 $0$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e3+10;
ll t,n,k,a[N],ans;
int main(){
	cin>>t;
	while(t--){
		ans=2e18;
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>a[i];
		if(k==1){
			sort(a+1,a+1+n);
			for(int i=1;i<=n;i++){
				ans=min(ans,a[i]);
				for(int j=i+1;j<=n;j++)
				ans=min(ans,a[j]-a[i]);
			}
			cout<<ans<<endl;
		}else if(k==2){
			sort(a+1,a+1+n);
			for(int i=1;i<=n;i++){
				ans=min(ans,a[i]);
				for(int j=i+1;j<=n;j++){
					ans=min(ans,a[j]-a[i]);
					ll l=1,r=n;
					while(l<=r){
						ll mid=l+r>>1;
						ans=min(ans,abs(a[j]-a[i]-a[mid]));
						if(a[j]-a[i]<=a[mid])r=mid-1;
						else l=mid+1;
					}
				}
			}
			cout<<ans<<endl;
		}else{
			cout<<0<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

不太好想。（~~我看了题解才会~~）

1. 当 $k>2$ 时，可以选两次相同的 $i$ 和 $j$。再将生成的数做差。

1. 当 $k=1$ 时，直接 $Θ(n^2)$ 枚举。

1. 当 $k=2$ 时，先枚举第一次的 $i$ 和 $j$，再用 `lower_bound()` 实现查找第二次选择的数。时间复杂度 $Θ(n^2\log_2{n})$。

注意：当 $k=2$ 时，仍要考虑 $k=1$ 时的情况。当 $k=1$ 或 $k=2$ 时，考虑不操作的最小值。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k,a[2010];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&k);
		int ans=2e18;
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]),ans=min(ans,a[i]);
		sort(a+1,a+n+1);
		if(k>2){
			puts("0");
			continue;
		}
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				ans=min(ans,a[j]-a[i]);
		if(k==2){
			for(int i=1;i<=n;i++)
				for(int j=i+1;j<=n;j++){
					int s=a[j]-a[i];
					int pos=lower_bound(a+1,a+n+1,s)-a;
					if(pos>1)ans=min(ans,abs(a[pos-1]-s));
					if(pos<=n)ans=min(ans,abs(a[pos]-s));
				}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：TLEWA (赞：0)

## 解题思路

考虑分类讨论。

当 $k \ge 3$ 时，我们使用如下构造方法：

从序列中任选一对 $a_i,a_j$，其中 $a_i$ 较大。先将 $a_i,a_j$ 进行一次运算后得 $a_i - a_j$，然后再将 $a_i - a_j$ 与 $a_i$ 运算，得 $\left| a_i-(a_i-a_j) \right| = a_j$，于是我们得到了两个相等的值，进行一次 $a_j-a_j$ 后即得 $0$，由于原序列中的数均为正整数且操作取绝对值，$0$ 就是所能构造出的最小值，于是对于 $k \ge 3$ 的情况，我们输出 $0$ 即可，时间复杂度 $O(1)$。

当 $k=1$ 时，我们先将数组排序，对排序后的相邻值作差后取最小值即可，时间复杂度为 $O(n)$。

当 $k=2$ 时，我们枚举第一步操作的所有可能，这个数量显然是 $n^2$ 级别的，然后我们通过二分找到第一个小于第一次操作新值的数和第一个大于等于新值的数，分别作差后取最小值输出，时间复杂度为 $O(n^2 \log n)$，可以使用双指针的实现方法将复杂度进一步优化到 $O(n^2)$。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N=2005,INF=(1e18)+5;

int T;

int n,k;
int arr[N];

signed main() {
	cin >> T;
	while(T--) {
		cin >> n >> k;
		for(int i=1;i<=n;++i)
			cin >> arr[i];
		sort(arr+1,arr+1+n);
		if(k>=3) {cout << 0 << endl;continue;}
		int num,p,minn=arr[1];
		for(int i=2;i<=n;++i) minn=min(minn,arr[i]-arr[i-1]);
		if(k==2) {
			for(int i=1;i<=n;++i) {
				for(int j=i+1;j<=n;++j) {
					num=arr[j]-arr[i];
					p=lower_bound(arr+1,arr+1+n,num)-arr;
					if(p<=n) minn=min(minn,arr[p]-num);
					if(p>1) minn=min(minn,num-arr[p-1]); 
				}
			}
		}
		cout << minn << endl;
	}
	return 0;
}

```


---

## 作者：IYSY2009I (赞：0)

当 $k \ge 3$ 是，我们可以先同样的方法构造出两个数，第三次操作就可以得到 $0$，所以只需要考虑 $k \le 2$ 的情况即可。

如果一次操作也不执行，最小值就是这个数列中的最小值。

如果执行一次操作，直接枚举 $i,j$ 就可以。

如果执行两次操作，先将 $a$ 数组排序，然后对于枚举的每个 $|a_i-a_j|$，二分查找出与它的差最小的数。

答案就是上面这些取 $\min$。

代码：

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long read() //这里省略一个快读
long long a[2005];
void solve(){
	int n=read(),k=read();
	long long ans=1e18;
	for(int i=1;i<=n;i++){
		a[i]=read();
		ans=min(ans,a[i]);
	}
	if(!k){ //k=0 的情况
		printf("%lld\n",ans);
		return;
	}
	if(k>2){ //k>2 的情况
		printf("0\n");
		return;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++){
			long long num=abs(a[i]-a[j]);
			ans=min(ans,num); //k>0 的情况
			if(k>1){ //k>1 的情况
				int id=upper_bound(a+1,a+n+1,num)-a;
				if(id<=n) ans=min(ans,a[id]-num); //二分比它大的数中最小的和比它小的数中最大的
				if(id>1) ans=min(ans,num-a[id-1]);
			}
		}
	printf("%lld\n",ans);
	return;
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		solve();
	return 0;
}
```


---

## 作者：Hyh_111 (赞：0)

## 思路

分类讨论 $k$ 的情况：

- $k \ge 3$，则答案为 $0$。因为只要选取同一组 $(i,j)$ 两次，就会产生同样的两个数，在操作一次就可以产生 $0$。

- $k = 1$，此时只需要找到差最小的两个元素并作差取绝对值就行了。

- $k = 2$，注意到所有 $n^2$ 之和小于等于 $10^6$，于是先排序，然后枚举第一步操作，最后二分找答案即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T;
int n,k;
int a[2005];

signed main()
{
    cin >> T;
    while (T--)
    {
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        if (k >= 3)
        {
            puts("0");
            continue;
        }//k=3的情况
        sort(a + 1,a + n + 1);
        int minn = a[1];
        for (int i = 1; i < n; i++) minn = min(minn,a[i + 1] - a[i]);//先处理初始的最小值
        if (k == 1)
        {
            printf("%lld\n",minn);
            continue;
        }//k=1的情况
        for (int i = 1; i <= n; i++) for (int j = 1; j < i; j++)
        {
            int val = a[i] - a[j];
            int pos = lower_bound(a + 1,a + n + 1,val) - a;
            if (pos <= n) minn = min(minn,a[pos] - val);//比val大或相等的第一个值
            if (pos > 1) minn = min(minn,val - a[pos - 1]);//比val小的第一个值
        }
        printf("%lld\n",minn);
    }
	return 0;
}
```

---

## 作者：fcy20180201 (赞：0)

## 思路
首先发现，若 $k\ge 3$，则前 $k-1$ 操作每次把前 $N$ 个中的同两个作差，最后一次操作把这些差随便选两个相减就能得到 $0$。

若 $k=1$，只要把数组排序后对相邻两项的差取 $\min$。（别忘了第一项也可能成为最小值）。

若 $k=2$，一定是先将两项作差，再把差和一项作差。因此可以先将数组排序，再枚举第一次作差的两项，算出差后再在数组中二分，找到**最小的大于等于差的**和**最大的小于等于差的**，再算出第二次的差取 $\min$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int t,n,m;
ll a[2005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		ll ans=2e18;
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		sort(a+1,a+n+1);//排序
		if(m==1){
			for(int i=1;i<=n;i++)ans=min(ans,abs(a[i]-a[i-1]));
			//相邻两项作差
			printf("%lld\n",ans);
		}
		if(m==2){
			for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++){//枚举第一次作差的两项
				ll x=abs(a[i]-a[j]);
				int s=lower_bound(a+1,a+n+1,x)-a;//二分
				ans=min({ans,abs(a[s]-x),abs(a[s-1]-x)});
			}
			printf("%lld\n",ans);
		}
		if(m>2)puts("0");
	}
	return 0;
}

```

---

## 作者：_smart_stupid_ (赞：0)

# [题目](https://www.luogu.com.cn/problem/CF1904C)

## 思路：

分情况讨论，分成三种情况，$k \ge 3$，$k = 1$ 和 $k = 2$。

首先，讨论 $k \ge 3$ 的情况，我们可以做这种操作：

- 选两个数 $a$，$b$。
- 往数组里添加两次 $a - b$。
- 往数组里添加上一步添加的 $a - b$ 和 $a - b$ 的差，显然为 $0$。

无论再怎么添加，最小值都为 $0$。

所以这种情况直接输出 $0$。

然后，讨论 $k = 1$ 和 $k = 2$ 的情况。

先把数组排序，答案初始化为数组的第一项。

在再数组里找到相邻两个数，如果他们的差的绝对值小于答案，就更新答案。

#### 如果 $k = 1$：

答案就是上述步骤更新后的答案。

#### 如果 $k = 2$：

我们在数组中找到两个数，求差，然后找到数组中与它最接近的数，做差，更新答案，然后输出答案。

## AC Code:
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;
int t;
int n, k;

int main() {
	scanf("%d", &t);
	while (t --) {
		scanf("%d%d", &n, &k);
		vector<long long> a(n);
		for (int i = 0; i < n; i ++) {
			cin >> a[i];
		}
		if (k >= 3) {
			printf("0\n");
		} else {
			sort (begin(a), end(a));
			long long ans = a[0];
			for (int i = 0; i < n - 1; i ++) {
				ans = min(ans, a[i + 1] - a[i]);
			}
			if (k == 1) {
				printf("%lld\n", ans);
			} else {
				for (int i = 0; i < n; i ++) {
					for (int j = 0; j < i; j ++) {
						long long v = a[i] - a[j];
						int tmp = lower_bound(begin(a), end(a), v) - begin(a);
						if (tmp < n) ans = min(ans, a[tmp] - v);
						if (tmp > 0) ans = min(ans, v - a[tmp - 1]);
					}
				}
				printf("%lld\n", ans);
			}
		}
	}
	
	return 0;
}
```

---

