# Multiple Testcases

## 题目描述

给予$n$个整数$m_{1,2,...,n}$，现在要将它们放进若干容器，要求：

- 在每个容器$p_j$中，对于每个数$i$（$1 \le i \le k$），大于等于$i$的数不能超过$c_i$个。

求最小所需容器数以及安排方式，保证：

- $1 \le n \le 2 \cdot 10^5$
- $1 \le k \le 2 \cdot 10^5$
- $1 \le m_i \le k$
- $n \ge c_1 \ge c_2 \ge ...\ge c_k \ge 1$

## 样例 #1

### 输入

```
4 3
1 2 2 3
4 1 1```

### 输出

```
3
1 2
2 1 3
1 2```

## 样例 #2

### 输入

```
6 10
5 8 1 10 8 7
6 6 4 4 3 2 2 2 1 1```

### 输出

```
2
3 8 5 7
3 10 8 1```

## 样例 #3

### 输入

```
5 1
1 1 1 1 1
5```

### 输出

```
1
5 1 1 1 1 1```

## 样例 #4

### 输入

```
5 1
1 1 1 1 1
1```

### 输出

```
5
1 1
1 1
1 1
1 1
1 1```

# 题解

## 作者：chen_03 (赞：8)

我的做法似乎和正解不太一样，于是来水一发题解。

我们运用贪心的思想，即依次对于每个数组，选择最合适的一组数据，把它放进去，若没有数据可选就添加一组数据。

我们发现，最“有影响力”的数组必定是最大的数组，因为较大的数组被放入某组数据时，它会影响较小的数组的数量限制，而较小的数组不会影响较大的数组的数量限制。于是我们选择数组的顺序是从大到小，这用一次排序即可实现。

我们对于现有的这些数据，记录它目前拥有的数组的数量，记为 $\text{sum}_j$。设当前数组的大小为 $t$，即 $t=a_i$，则我们选择放入的数据中，应满足 $c_t>$ 这个数据拥有的大于等于 $t$ 的数组数量，这样才能放得下。由于我们从大到小放入数组，这个数据拥有的大于等于 $t$ 的数组数量就是 $\text{sum}_j$。

于是我们每次贪心地选择满足 $c_t>\text{sum}_j$ 且 $\text{sum}_j$ 最大的一组数据，把当前的数组放进去，若没有这样的数据，就添加一组数据。为什么选择 $\text{sum}_j$ 最大的一组数据呢，因为这样可以使 $\text{sum}$ 数组满足单调性，也使数组尽量被平分。

由于 $\text{sum}$ 数组满足单调性，所以我们可以用类似[导弹拦截](https://www.luogu.com.cn/problem/P1020)的方法，二分一下，找到满足条件的那组数据，把它放进去，若没有这样的数据就添加一组数据。

题目要求输出方案，所以对于每组数据我们开一个 `vector`，每次把当前的数组大小放进这组数据的 `vector` 就行了。

时间复杂度 $\Theta(n\log n+k)$，其中 $k$ 是读入 $c$ 数组的复杂度。

这个做法明显比正解劣，也比较口胡，但至少没有 FST（

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int n,k,a[200005],c[200005],sum[200005],cnt,l,r,mid; //cnt 即为当前的数据数量
vector<int> v[200005];
inline bool cmp(const int &x,const int &y){
	return x>y;
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
		scanf("%d",a+i);
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=k;++i)
		scanf("%d",c+i);
	for(int i=1;i<=n;++i){
		int t=a[i];
		l=1;r=cnt+1; //注意 r=cnt+1，因为我们要考虑没有可选数据的情况
		while(l<r){
			mid=(l+r)>>1;
			if(c[t]>sum[mid])r=mid; //如果满足条件
			else l=mid+1;
		}
		if(l>cnt){ //如果没有可选的数据，就添加一组数据
			++cnt;
			sum[cnt]=1; //记得要更新 sum 数组，下同
			v[cnt].push_back(t); //放入这组数据的 vector，下同
			continue;
		}
		++sum[l]; //如果有满足条件的数据，就把当前的数组放进去
		v[l].push_back(t);
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;++i){
		printf("%d",v[i].size());
		for(int j=0;j<v[i].size();++j)
			printf(" %d",v[i][j]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Limit (赞：5)

# 题目大意

给出一个序列,和一些限制,需要将这个序列分到最少的组中使得每个组中大于 $i$ 的数小于等于 $c_i$ 个.

# 分析

先计算最小的组数考虑计算 $sum_i=\sum_{i=j}^{n}(a_j\geq i)$,计算过程类似一个后缀和,那么就可以直接计算出大于等于 $i$ 的数至少要放在几组中,然后取max就好了.

然后考虑怎么去放,很显然是按顺序去放(从小到大排序后依次轮流放入)最优,可以保证一定满足,具体证明可以理解一下计算公式.

排序如果用桶排可以做到 $\mathcal{O}(n+k)$,但是我比较懒,就直接用了 sort.

## 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=2e5+5;
int n,k;
int arr[MAXN];
int c[MAXN];
int sum[MAXN];
int main()
{
	scanf("%d%d",&n,&k);
	REP(i,1,n)
	{
		scanf("%d",&arr[i]);
		sum[arr[i]]++;//统计出现次数
	}
	DOW(i,k-1,1)//后缀和
	{
		sum[i]+=sum[i+1];
	}
	int answer=0;
	sort(arr+1,arr+1+n);
	REP(i,1,k)
	{
		scanf("%d",&c[i]);
	}
	REP(i,1,k)
	{
		answer=max(answer,sum[i]/c[i]+(bool)(sum[i]%c[i]));//计算最小组数
	}
	printf("%d\n",answer);
	REP(i,1,answer)
	{
		int now=i,p=0;
		while(now<=n)//考虑是按组数循环,先计算出个数再输出
		{
			++p;
			now+=answer;
		}
		printf("%d ",p);
		now=i;
		while(now<=n)
		{
			printf("%d ",arr[now]);
			now+=answer;
		}
		printf("\n");
	}
	return 0;
}
```



---

## 作者：朝夕 (赞：2)

### 题目大意

这题题意蛮复杂的，我在赛场上读了半天，现在用比较简洁的方式说明一下。

给你n，k。

然后给你n个数字$m_i$，$m_i\le k$。要求你将这n个数字进行分组。

再给你k个限制$c_i,n\ge c_1\ge c_2……\ge c_n\ge 1$。

$c_i$代表每个分组内$\ge i$的数字最多可有几个。

譬如$c_1=2$，则每个分组内大于等于1的数字的数量不能超过2.

若给的数字有2,3,4,5,6。

则一个可行的分组为[2,3],[4,5],[6]。

最后求可行的分组方法中，组数最小的。

要求输出最小组数与你分组的办法。

### 解题思路

由于要求最小分组数，所以用贪心的思路来看，数字要尽量平分。

譬如$c_2=3$，大于等于2的数字有7个，则我们尽量平分，最小分组数为(7/3)向上取整，即3组，以[3,3,1]的方式分配。

所以只需要先做一遍计数排序，再倒着做一遍前缀和，就可以求出最小分组数。

至于分组的方法，当然是平分，我们可以通过去mod（最小分组数）的方法来将一个个数字平分。

最后的时间复杂度应该是$O(n+k)$。
### 参考代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int m[200005];
int c[200005];
int vis[200005];
int la[200005];
vector<int>pu[200005];
int main()
{
    ios::sync_with_stdio(false);
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>m[i];
    for(int i=1;i<=k;i++) cin>>c[i];
    for(int i=1;i<=n;i++)
    {
        vis[m[i]]++;//计数排序
    }
    int ans=0;
    for(int i=k;i>=1;i--)//倒着前缀和
    {
        la[i]=la[i+1]+vis[i];//前缀和
        int temp=la[i]/c[i];//当前限制下的最小分组数
        if(la[i]%c[i]!=0) temp++;//要向上取整
        ans=max(ans,temp);//求出最小分组数
    }
    sort(m+1,m+n+1);//排序一下，好处理
    cout<<ans<<endl;
    int nl=1,nr=1;
    for(int j=1;j<=k;j++)//分配等于j的数字
    {
        while(m[nr]>=j&&m[nr]<j+1) nr++;//求出等于j的数字在m数组内的范围
        nr--;
        for(int i=nl;i<=nr;i++)
        {
            pu[(i-1)%ans+1].push_back(m[i]);
        }//以取模的方法分配
        nl=nr+1;
        nr++;
    }
    for(int i=1;i<=ans;i++)
    {
        cout<<pu[i].size()<<" ";
        for(int j=0;j<pu[i].size();j++)
        {
            if(j!=0) cout<<" ";
            cout<<pu[i][j];
        }
        cout<<endl;
    }//输出答案
    return 0;
}
```


---

## 作者：skyskyCCC (赞：1)

## 前言。
很好的一道贪心题。

题意简述：给定 $n$ 个不大于 $k$ 的数，请把这些数尽量分成较小的组，同时每组大于等于 $i$ 的数不超过 $c_i$ 个。
## 分析。
分成较小的组？显然我们有一个明显的方向：贪心。那么我们就分析是否能贪心。我们考虑这个数据的个数与分组个数之间的关系。我们观察到，对于这 $n$ 个数中最大的数 $a_i$，如果数组中一共有 $m_i$ 个 $a_i$ 则显然这个数组中大于等于 $a_i$ 的数的总数量就是 $m_i$ 个。那么我们分成组的个数就是 $\left\lceil\frac{m_i}{c_i}\right\rceil$ 个。我们发现存在特例。

扩展到另一个情况：在 $n$ 个数中的数为 $a_{i-1}$，那么大于等于这个数的数的数量就是 $m_i+m_{i-1}$ 个。令 $i-1=k$ 则同理我们可以分成 $\left\lceil\frac{\left(m_i+m_k\right)}{c_k}\right\rceil$ 组。但是这样存在一个问题，就是我们前面分的组的数量和后面分的组的数量不一定是相等的。那么，如果想要满足每个条件，肯定要取最大的组数。因为我们如果选取的小的组数，可能像上面的两种不同的分组情况一样，会出现交集。

比较每个数的大小，我们可以先用桶进行计数，然后倒着跑一遍后缀和，向上取整即可。那么我们现在就确定的组数，考虑分配每个数即可。我们显然经过前面的计算，已经得到了最小的合法的组数，所以我们只要按顺序把各个数均摊到组里就行了。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int n,k,m[200005],c[200005];
int t[200005],ans;
int tot,cot;
int main(){
	cin>>n>>k;
    for (int i=1;i<=n;i++){
    	cin>>m[i];
    	t[m[i]]++;
	}
    for (int i=k;i;i--){
    	t[i]+=t[i+1];
	}
    for (int i=1;i<=k;i++){
    	cin>>c[i];
	}
    for (int i=1;i<=k;i++){
	    ans=max(ans,t[i]/c[i]+(bool)(t[i]%c[i]));
	}
    cout<<ans<<"\n";
    sort(m+1,m+n+1);
    for (int i=1;i<=ans;i++){
        tot=0;
        cot=i;
        while(cot<=n){
        	tot++;
        	cot+=ans;
		}
        cout<<tot<<" ";
        cot=i;
        while(cot<=n){
        	cout<<m[cot]<<" ";
        	cot+=ans;
		}
        cout<<"\n";
    }
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Echo_Long (赞：1)

### [Multiple Testcases](https://www.luogu.com.cn/problem/CF1342D)

题面没看懂。

大意是让你不重不漏地平均分配一个数组 $a$ 到 $m$ 个容器中，使得对于每一个容器，每一个数 $i\in[1,k]$，都满足 $\ge i$ 的 $a$ 数量 $\le c_i$。

首先对于 $a$ 进行桶的标记，并从 $k$ 到 $1$ 做一个后缀和，算出每一个 $i\in[1,k]$ 的最小分配数，取最大值输出。

对于方案的输出，一定是将 $a$ 数组从小到大，均分到每一个容器中，这样才能保证我们满足条件的分配数尽量少。

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inl inline
#define eb emplace_back
#define getchar() cin.get()
#define pii pair<int,int>
#define fi first
#define se second
#define int long long
const int N = 2e5 + 5;

int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}

int n , k , sum[N] , a[N] , ans , c[N];

signed main ()
{
    ios::sync_with_stdio(false);
    cin.tie(0) , cout.tie(0);
    n = read() , k = read();
    for ( int i = 1 ; i <= n ; i ++ ) a[i] = read() , sum[a[i]] ++;
    for ( int i = k ; i ; i -- ) sum[i] += sum[i+1];
    for ( int i = 1 ; i <= k ; i ++ ) c[i] = read();
    for ( int i = 1 ; i <= k ; i ++ ) ans = max ( ans , sum[i] / c[i] + !! ( sum[i] % c[i] ) );
    cout << ans << endl;
    sort ( a + 1 , a + n + 1 );
    for ( int i = 1 ; i <= ans ; i ++ )
    {
        int stp = i , cnt = 0;
        while ( stp <= n ) ++ cnt , stp += ans;
        cout << cnt << ' ';
        stp = i;
        while ( stp <= n ) cout << a[stp] << ' ' ,  stp += ans;;
        cout << endl;
    }
    return 0;
}

```



---

## 作者：Silvestorm (赞：0)

### 题目大意

[题目链接](https://www.luogu.com.cn/problem/CF1342D)。

给出 $n$ 个数，要求放进若干给容器里。在每个容器中，对于所有数 $i(1\le i\le k)$，大于等于 $i$ 的数不能超过 $c_i$ 个。

要求输出容器数量最小的方案。

$1\le n\le 2\times 10^5$，$1\le m_i\le k\le 2\times 10^5$，$n\ge c_1\ge c_2\ge...\ge c_k\ge 1$。

### 题目类型

贪心，二分。

### 解题思路

往一个容器里添加一个数，要考虑容器里每个不比它大的数是否依旧合法，依旧大于它的数是否超出限制，后者容易处理，而前者比较难。若是按照降序往容器里添加元素，每次添加的数的大小总是容器里最小的，那么只要考虑容器元素的数量是否超出限制即可。

对于所有可添加的容器，总是选择编号最小的去添加，这样就可以通过二分查找可添加的容器。

时间复杂度为 $O(n\log{n})$。

### code


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, m, k = 1, tem, num[200100], arr[200100], vis[200100];
ll ans = 0;
vector<ll> v[200100];
void solve()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> num[i];
	sort(num + 1, num + 1 + n);
	for (int i = 1; i <= k; i++)
		cin >> arr[i];
	ll l = 0, r = 0;
	for (int i = n; i > 0; i--)//逆序遍历
	{
		l = 0, r = ans;
		while (l < r)//二分查找
		{
			ll mid = (l + r) >> 1;
			if (v[mid].size() >= arr[num[i]])
				l = mid + 1;
			else
				r = mid;
		}
		ll x = l;
		while (v[x].size() >= arr[num[i]])
			x++;
		ans = max(ans, x);
		v[x].push_back(num[i]);
	}
	cout << ans + 1 << "\n";
	for (int i = 0; i <= n; i++)
	{
		if (v[i].size() == 0)
			break;
		cout << v[i].size();
		for (auto j : v[i])
			cout << " " << j;
		cout << '\n';
	}
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
```

---

