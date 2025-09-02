# Eating Queries

## 题目描述

Timur has $ n $ candies. The $ i $ -th candy has a quantity of sugar equal to $ a_i $ . So, by eating the $ i $ -th candy, Timur consumes a quantity of sugar equal to $ a_i $ .

Timur will ask you $ q $ queries regarding his candies. For the $ j $ -th query you have to answer what is the minimum number of candies he needs to eat in order to reach a quantity of sugar greater than or equal to $ x_j $ or print -1 if it's not possible to obtain such a quantity. In other words, you should print the minimum possible $ k $ such that after eating $ k $ candies, Timur consumes a quantity of sugar of at least $ x_j $ or say that no possible $ k $ exists.

Note that he can't eat the same candy twice and queries are independent of each other (Timur can use the same candy in different queries).

## 说明/提示

For the first test case:

For the first query, Timur can eat any candy, and he will reach the desired quantity.

For the second query, Timur can reach a quantity of at least $ 10 $ by eating the $ 7 $ -th and the $ 8 $ -th candies, thus consuming a quantity of sugar equal to $ 14 $ .

For the third query, there is no possible answer.

For the fourth query, Timur can reach a quantity of at least $ 14 $ by eating the $ 7 $ -th and the $ 8 $ -th candies, thus consuming a quantity of sugar equal to $ 14 $ .

For the second test case:

For the only query of the second test case, we can choose the third candy from which Timur receives exactly $ 3 $ sugar. It's also possible to obtain the same answer by choosing the fourth candy.

## 样例 #1

### 输入

```
3
8 7
4 3 3 1 1 4 5 9
1
10
50
14
15
22
30
4 1
1 2 3 4
3
1 2
5
4
6```

### 输出

```
1
2
-1
2
3
4
8
1
1
-1```

# 题解

## 作者：Otue (赞：6)

## 思路
反正他每次可以随便吃糖果，为了让他糖果吃的少且糖分达到要求，那么肯定优先吃糖分最大的糖果。

所以 $a$ 数组从大到小排序，依次的吃，吃到需要达到的糖分要求即可。

但是这样子枚举着吃，会超时，所以选择二分。

具体流程：

先对 $a$ 数组排序，然后假设 $sum$ 数组就是排序后 $a$ 的前缀和，则只需要找到第一个 $sum_i \geq k$ 即可（$k$ 是需要的糖分）。由于 $sum$ 数组单调递增，则可以选择二分。
## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int t, n, q, a[N], sum[N];

bool cmp(int x, int y) {
	return x > y;
}

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> q;
		for (int i = 1; i <= n; i++) cin >> a[i];
		sort(a + 1, a + n + 1, cmp);  //从大到小排序
		for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];   //前缀和
		while (q--) {
			int x;
			cin >> x;
			if (sum[n] < x) puts("-1");   //判断无解
			else cout << lower_bound(sum + 1, sum + n + 1, x) - sum << endl;   //否则二分
		}
		
	}
}
```

---

## 作者：Coros_Trusds (赞：6)

# 题目分析

不如看看对于单个询问，我们怎么解决它：不妨使用贪心思想，我们要想让吃的糖果最少，一定要让吃的糖果尽量大。

所以我们把序列 $a$ 降序排列，这样可以满足一次吃的糖果尽量大，数量也就尽量小。然后维护前缀和 $sum[i]=\sum\limits_{j=1}^ia[j]$。

$sum$ 显然单调递增，于是在 $sum$ 上二分查找第一个大于等于 $x$ 的位置即可。位置即为答案。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1.5e5 + 5;
int a[N],sum[N];
int T,n,m;
inline bool cmp(int x,int y) {
    return x > y;
}
inline void solve() {
    cin >> n >> m;
    for (register int i = 1;i <= n; ++ i) {
        cin >> a[i];
    }
    sort(a + 1,a + n + 1,cmp);
    for (register int i = 1;i <= n; ++ i) sum[i] = sum[i - 1] + a[i];
    while (m --) {
        int x;
        cin >> x;
        int l = 1,r = n,ans = -1;
        while (l <= r) {
            int mid = l + r >> 1;
            if (sum[mid] >= x) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << "\n";
    }
}
int main(void) {
    cin.tie(nullptr),cout.tie(nullptr);
    ios::sync_with_stdio(false);
    cin >> T;
    while (T --) {
        solve();
    }

    return 0;
}
```

---

## 作者：CYZZ (赞：3)

# [Eating Queries](https://www.luogu.com.cn/problem/CF1676E)
此题可以加深对二分和前缀和的理解。
# 思路分析
首先我们需要明白一件事（贪心）：对于吃任意的 $k$ 个糖果，肯定选择糖分最大的 $k$ 个糖，才能使总和最大。

所以，我们可以先给 $a$ 数组排个序，此时的 $a$ 数组满足**单调不减**。

第一个想法是：遍历 $a$ 数组并累加，发现和大于 $x$ 就退出，最后输出 -1。
```cpp
for(int i=1;i<=q;i++)
{
	scanf("%d",&x);
	int tot=0,cnt=0;
	bool flag=0;
	for(cnt=1;cnt<=n;cnt++)
	{
		tot+=a[cnt];
		if(tot>=x)
		{
			flag=1;
			break;
		}
	}
	printf("%d\n",flag?cnt:-1);
}
```
但是，这样明显无法支持 $q$ 个询问。所以考虑前缀和优化。维护前缀和数组使 $sum_i=\sum\limits_{j=1}^ia_j$。因为 $sum$ 数组满足单调性，所以二分查找第一个大于等于 $x$ 的元素位置即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,q,a[150005],sum[150005],x;
bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&q);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			sum[i]=0;
		}
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++)
		{
			sum[i]=a[i]+sum[i-1];
		}
		for(int i=1;i<=q;i++)
		{
			scanf("%d",&x);
			printf("%d\n",sum[n]>=x?lower_bound(sum+1,sum+n+1,x)-sum:-1);
		}
	}
	return 0;
}
```
 希望本篇题解可以帮到大家！！！

---

## 作者：Engulf (赞：2)

下列的 $a$ 代表糖堆，$x_j$ 代表第 $j$ 个询问。

考虑贪心，为了使吃的糖堆数尽可能少，肯定要优先吃糖多的堆，所以将 $a$ 降序排序。

预处理出前缀和 $s$，找出第一个 $\ge x_j$ 的即可。

```cpp
// author: TMJYH09
// create time: 2022/05/10 23:13:04
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

int a[150005];
int s[150005];

void solve(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1,greater<int>());
    for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
    while(q--){
        int x;cin>>x;
        int ans=lower_bound(s+1,s+n+1,x)-s;
        cout<<(ans==n+1?-1:ans)<<endl;
    }
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int _;cin>>_;while(_--)solve();
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：2)

# 题意
有 $n$ 个数，第 $i$ 个数是 $a_i$，$q$ 次询问，

每次询问最少选出几个数，使得它们的和不小于 $x$。
# 思路
很明显，应该先选较大的数，可以保证数的个数最小。

但直接模拟复杂度是 $O(nq)$，不太行。

假设 $a_i$ 已经降序排序，则选出的数应该是 $a$ 的一个前缀。

不妨预处理初 $s_k=\sum\limits_{i=1}^ka_i$，则问题就变成了求 $\min\limits_{s_k≥x}k$。

因为 $a_i$ 是正数，所以 $s$ 具有单调性，上面的问题可以二分求出。
# 代码
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int T, n, q, a[150050];
bool cmp(int x, int y) {return x > y;}
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &q);
        for(int i = 1;i <= n;++i) scanf("%d", &a[i]);
        sort(a + 1, a + n + 1, cmp);
        for(int i = 2;i <= n;++i) a[i] += a[i - 1];
        for(int i = 0, x, s;i < q;++i)
        {
            scanf("%d", &x);
            s = lower_bound(a + 1, a + n + 1, x) - a;
            printf("%d\n", s > n ? -1 : s);
        }
    }
    return 0;
}
```


---

## 作者：Anonymous__user (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1676E)。

**题目大意**：有 $t$ 组数据，每组数据中有 $n$ 颗糖，吃第 $i$ 颗糖可以得到 $a_i$ 的糖分。

有 $q$ 次询问，每次询问最少吃多少颗糖可以得到不小于 $x$ 的糖分，无解输出 `-1`。
在每次询问中，不能多次吃同一颗糖；每次询问互相独立，即不同询问可以吃同一颗糖。

**思路**：这是一道贪心和二分题。我们先把糖分排序，定义一个 $sum$ 数组，$sum_i$ 表示吃掉 $i$ 个糖果最多需要的糖分。如果 $sum_n$ 小于询问中的糖分 $x$ ，就代表无解，输出 `-1` 。然后二分一下，找出最少需要吃的糖果个数就是答案。

**代码**：
```c
#include<bits/stdc++.h>
using namespace std;
long long t,n,q,a[150010],x,ans,sum[150010],l,r,zh;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>q;
		sum[0]=0;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
			sum[i]=sum[i-1]+a[n-i+1];
		for(int i=1;i<=q;i++){
			cin>>x;
			if(x>sum[n])cout<<-1<<endl;
			l=1;r=n;
			while(l<=r){
				if(l==r)break;
				zh=(l+r)>>1;
				if(sum[zh]>=x)
					r=zh;
				else l=zh+1;
			}
			if(x<=sum[n])cout<<l<<endl;
			ans=0;
		}
	}
	return 0;
}
```


---

## 作者：happy_zero (赞：0)

这是一道贪心+二分+前缀和的题目。
### 贪心
因为题目中要求的只是是吃的糖的数量最少，我们知道每次吃的糖糖分越多越好，所以我们每次就贪心选择未吃过的、糖分最大的糖果。于是我们可以在输入后对所有糖果从大到小进行排序，每次按顺序吃直至糖的总糖分大于等于 $x$。
### 二分
知道了吃糖的顺序，那一共要吃多少颗糖？观察数据范围，对于每次输入 $x$，从头到尾扫一遍肯定是会超时的，我们就要考虑如何优化。我们知道，每个糖果的糖分都是大于等于 1 的，所以按顺序吃糖的获得的糖分总数会随着吃糖的数量不断增加，具有单调性，于是我们自然而然地想到了二分。
### 前缀和
我们在二分的过程中如何判断某一值行不行？这里我们就要用到前缀和了。我们在给糖排序后维护前缀和 $s_i$ 等于前 $i$ 个糖果的糖分总和，二分时直接 $O(1)$ 判断即可。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
int a[150005];
int s[150005];
bool cmp(int x,int y){
    return x>y;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        cin>>n>>q;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        sort(a+1,a+1+n,cmp);
        for(int i=1;i<=n;i++){
            s[i]=a[i]+s[i-1];
        }
        while(q--){
            int x,ans=-1;
            cin>>x;
            int l=0,r=n;
            while(l<=r){
                int mid=(l+r)/2;
                if(s[mid]>=x){ans=mid;r=mid-1;}
                else l=mid+1;
            }
            cout<<ans<<endl;
        }
    }
    
    
    return 0;
}
```



---

## 作者：ryf_loser (赞：0)

这是一道二分题。

此题的简单题意是：每次询问最少选出多少个数，使得它们的和不小于 $x$。

#### 大体思路是：

他必须优先吃糖分最大的糖果，所以 a 数组从大到小排序，按顺序吃的吃，才能使糖分达到要求，此时要用到前缀和的思路，$s_{i}$ 为前缀和数组，则只需要找到第一个 $\max (s_{i},k)$ 即可。

此时我们可以枚举，但肯定超时。

但我们可以二分，这样时间复杂度从 $O(n)$ 降低到 $O(n\log{n})$ 。

此时就可以 AC 了。

代码如下

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int t,n,q,a[150001],s[150001],x;
bool cmp(int x,int y){return x>y;}
int main(){
	scanf ("%d",&t);
	while (t--){
		scanf ("%d%d",&n,&q);
		for (int i=1;i<=n;i++)scanf ("%d",&a[i]);
		sort(a+1,a+1+n,cmp);
		for (int i=1;i<=n;i++)s[i]=s[i-1]+a[i];//前缀和。
		while (q--){
			scanf ("%d",&x);
			if (s[n]<x)printf ("-1\n");//如果最大都无法满足要求，则无解。
			else printf ("%d\n",lower_bound(s+1,s+1+n,x)-s);//标准二分。
		}
	}
    return 0;
}
```


---

## 作者：Huhu12346 (赞：0)

这题很明显的二分。

对于第一个查询，Timur 可以吃任何糖果，他将达到所需的数量。

对于第二个查询，Timur 可以通过吃掉第 $77$ 和第 $88$ 颗糖果达到至少 $1010$ 的数量，因此消耗的糖量等于 $1414$。

对于第三个查询，没有可能的答案。

对于第四个查询，Timur 可以通过食用第 $77$ 和第 $88$ 颗糖果达到至少 $1414$ 的数量，因此消耗的糖量等于 $1414$。

对于第二个测试用例：

对于第二个测试用例的唯一查询，我们可以选择 Timur 恰好收到 $33$ 颗糖的第三个糖果。选择第四个糖果也可以得到相同的答案。

### 下面奉上我的代码：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,l,r,a[1000000],b[1000000];
bool cmp(int x, int y) 
{
	return x > y;
}
int main() 
{
	cin >> n;
	for (int i=0;i<n;i++) 
	{
		cin>>l>>r;
		for(int j=0;j<l;j++) 
		{
			cin>>a[j];
		}
		sort(a,a+l,cmp);
		for(int j=0;j<l;j++) 
		{
			if (j==0) 
			{
				b[j]=a[j];
			}
			else 
			{
				b[j]=b[j-1]+a[j];
			}
		}
		int k;
		for(int j=0;j<r;j++)
		 {
			cin>>k;
			if(k>b[l-1]) 
			{
				cout<<-1<<endl;
				continue;
			}
			int x=0,y=l-1;
			while(x<y)
			{
				int mid=x+y>>1;
				if (b[mid]>=k) 
				{
					y=mid;
				}
				else 
				{
					x=mid+1;
				}
			}
			if(k<=b[x]) 
			{
				cout<<x+1<<endl;
			}
			else 
			{
				cout<<-1<<endl;
			}
		}
	}
}
```


---

## 作者：Escapism (赞：0)

练习贪心、前缀和与二分的好题。

[题目传送门](https://www.luogu.com.cn/problem/CF1676E)

# 题意

翻译很清晰，只是没有提到题目的输入是**多组数据**。

# 思路

为了使得能够吃最少的糖获得最多的糖分，那么就必须要选择糖分最大的糖来吃。那么这就是一个贪心，我们先从大到小对每颗糖的糖分拍一次序。

显然 $n$ 的范围是可以 ``sort`` 的，所以我们可以直接用 ``sort``。

然后考虑询问。首先想到的当然是对于每次询问都求一次和。但是由于 $a_i$ 很小但是 $x_j$ 却非常大。如果是极限数据那么单次询问都要做二十万次的求和，然后乘上 $q$ 的极限数据，``TLE`` 不可避免。

所以朴素的暴力显然不行，我们必须要优化。

首先因为糖的糖分是排好序的，而且不会影响到糖分，还是按顺序吃的。所以在吃若干颗糖的时候，糖分是一定的。那么我们可以做一次前缀和，$S_k$ 表示吃 $k$ 颗糖的糖分总和。

如果只用前缀和优化效果并不明显，因为要判 $-1$ 始终还是要判断 $n$ 次。

实际上我们前缀和的目的还有一个：创造二分的条件。

二分最重要的条件就是单调性，而糖必然是吃的越多糖分越多，那么显然具有单调性。不知道二分是什么的同学可以看[这里](https://oiwiki.org/basic/binary/)。

将程序加上二分和前缀和之后就不会超时了。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 * 1.5 + 5;
long long a[MAXN],s[MAXN];

bool cmp(long long a, long long b) {
	return a > b;
}

int main() {
	int t;
	cin >> t;
	for (int j = 1;j <= t;j++){
		int n, ask;
		cin >> n >> ask;
		long long sum = 0;
		for (int i =1 ; i <= n; i++) {
			cin >> a[i];
			sum += a[i];
			s[i] = s[i - 1] + a[i];
		}
		sort(a + 1, a + n + 1, cmp);
		for (int i = 1 ; i <= ask; i++) {
			int tmp;
			cin >> tmp;
			if (tmp > sum) { //小优化，如果询问大于糖分总和，输出-1。
				cout << -1 << endl;
				continue;
			}  
			else if (tmp == sum) {
				cout << n << endl;
				continue;
			}
			int l = 1, r = n, mid;
			while(l < r) { //二分
				mid = (l + r) / 2;
				if (s[mid] >= tmp) r = mid;
				else l = mid + 1;
			}
			cout << l << endl;
		}
		for (int i = 1;i <= n;i++) a[i] = s[i] = 0;//清零，但其实可有可无
	} 
}
```


---

## 作者：Mijacs (赞：0)

### 思路

首先，每次要求知道最少要吃多少颗糖才能满足要求，显然可以每次吃尽可能多的糖。那么这个部分可以先从大到小排序，然后前缀维护即可。那么具体该吃多少颗糖，可以用二分实现，因为显然具有单调性：吃的糖越多可以得到更多的分，只会单调不减。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,q,s[150005],v[150005];
// T 为数据组数，n、q 见题意。
// s 为前缀数组，v 为存储每一颗糖的分数的数组。 
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>q;
		for(int i=0;i<n;i++)
		{
			cin>>v[i];
		}
		sort(v,v+n,greater<int>()); // 输入，并从大到小排序。 
		for(int i=0;i<n;i++)
		{
			s[i]=v[i]+s[i-1]; // 处理前缀。 
		}
		while(q--)
		{
			int x;
			cin>>x;
			if(x>s[n-1]) cout<<-1<<'\n'; // 判断是否无解。 
			else cout<<(lower_bound(s,s+n,x)-s)+1<<'\n';
			// lower_bound 可以返回大于等于 x 的第一个数的地址。
			// 后面的 “-s”可以让其从返回地址变成返回下标。
			// 因为我的下标是从 0 开始，所以要 “+1”。 
		}
	}
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

## 思路

首先明确一个贪心原则：先从糖分多的糖吃起，这样一定可以保证在吃相同的糖的数量时贡献最大，就能吃最少的糖获得最多的贡献。

我们可以通过对 $a$ 降序排序，再预处理前缀和得到前 $1∼n$ 天吃糖果的糖分总和。对于每一个询问，使用 $O(n)$ 的时间复杂度遍历整个前缀和数组显然不行，我们考虑优化：二分可以在 $O(\log n)$ 的时间里找到第一个大于等于糖分 $x$ 的前缀和项，求得下标，就是吃糖的天数。
 
## 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[150005],sum[150005];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,q;
        cin>>n>>q;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1,greater<int>());//降序排列
        for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];//前缀和
        while(q--){
            int x;
            cin>>x;
            if(x>sum[n]) cout<<-1<<'\n';
            //如果比所有糖果甜度的和还大，就无法达成
            else cout<<lower_bound(sum+1,sum+n+1,x)-sum<<'\n';//下标
        }
    }
}
```

---

## 作者：LYqwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1676E)

# 题目大意

有 $n$ 颗糖，吃掉第 $i$ 颗糖可以获得 $a_i$ 点糖分。

有 $q$ 次询问，每次询问最少吃多少颗糖可以得到不小于 $x$ 的糖分，无解输出 $-1$。

# 思路

既然问最少吃多少颗糖，那糖分大的自然优先级要大。

于是就可以把 $a$ 数组降序排列。

询问时还需要知道 $a$ 数组前 $k$ 个糖的糖分之和，我们可以在询问之前对 $a$ 数组进行一次前缀和，也就是将原来的 $a_i$ 变成 $\sum\limits^{i}_{j=1}a_j$。这样转化很简单，只需要 $\mathcal{O}(n)$ 循环一遍，每次使得 $a_i$ 加上 $a_{i-1}$，注意 $a_{i-1}$ 是之前处理过的。

可以发现经过处理后的 $a$ 数组满足单调性，所以在查询时可以直接二分找到第一个 $\ge x$ 的数，取这个数的下标即可。这里可以直接用 `lower_bound`。

当得到的下标高于 $n$ 时，说明无解，输出 $-1$。

# 代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int N=15e4+5;
int t,n,q,x,ans;
int a[N];

int main(){
    cin >> t;
    while(t--){
        cin >> n >> q;
        for(int i=1; i<=n; i++) cin >> a[i];
        // 逆序排序
        sort(a+1,a+n+1,[](int x,int y)->bool{return x>y;});
        for(int i=1; i<=n; i++) a[i]+=a[i-1]; // 前缀和
        while(q--){
            cin >> x;
            ans=lower_bound(a+1,a+n+1,x)-a;
            if(ans<=n) cout << ans << endl;
            else puts("-1");
        }
    }
    return 0;
}
```



---

## 作者：落花月朦胧 (赞：0)

# 题意

给出 $n$ 个数， 每个数都有一个权值 $a_i$。

让你选择尽可能少的数，使这些数的和大于等于 $x$。 这种询问是多次且独立的。

# 解

发现要求个数少，权值大，于是想到贪心，可以从小到大排序。

本题的一个关键是对时间复杂度的规划。

排完序之后，我们要实现的是 2 个点
+ 获得一个区间和
+ 找到一个位置，让这个区间和大于等于 $x$

根据我们学习的算法，可以轻松的想到第一个实现的点要使用前缀和来进行优化，而第二个要实现的点则需呀用二分查找来进行优化，加上这两个优化之后，本题就可以轻松 $\texttt{AC}$ 了。

二分你可以手写，也可以用 STL 中的 `lower_bound`。

```cpp
#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
constexpr int inf = INT_MAX;
constexpr i64 lnf = LONG_LONG_MAX;

int a[1000000];
void solve() {
	int n, q;
	cin >> n >> q;

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	sort(a + 1, a + n + 1, greater<int>());
	
	for (int i = 1; i <= n; i++) {
		a[i] += a[i - 1];
	}

	while (q--) {
		int x; cin >> x;

		int ans = lower_bound(a + 1, a + n + 1, x) - a;
		if (ans > n) {
			ans = -1;
		}
		cout << ans << '\n';
	}
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) {
		solve();
	}

	return 0;
}
```

---

## 作者：WilliamFranklin (赞：0)

这道题比 $D$ 题还水，但也是有很多坑。

### 主要思路

贪心策略，每次都选最大的，肯定用的是最少的次数。

那么我们先将 $a$ 数组从大到小排序，用 $ans$ 从 $a_1$ 开始加，看一看加到第几个数之后大于 $x_j$。当然，为了更快，我们可以判断一下：只要 $x_j$ 大于 $a$ 数列的总和，就输出 $-1$，因为所有的 $a_i$ 加起来都小于它，那么怎么样都不可能大于等于它。当然，所有 $a_i$ 的和如果等于 $x_j$ 的话，就直接输出 $n$ 即可。

好啦，贴代码。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[150005], x[150005];
bool cmp(long long a, long long b) {
	return a > b;
}
int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, q;
		cin >> n >> q;
		long long he = 0;
		for (int i =1 ; i <= n; i++) {
			cin >> a[i];
			he += a[i];
		}
		sort(a + 1, a + n + 1, cmp);
		for (int i =1 ; i <= q; i++) {
			cin >> x[i];
			if (x[i] > he) {
				cout << -1 << endl;
				continue;
			}  else if (x[i] == he) {
				cout << n << endl;
				continue;
			}
			long long ans = 0, ans1 = 0;
			while (ans < x[i]) {
				ans += a[++ans1];
			}
			cout << ans1 << endl;
		}
	} 
}
```

恭喜你，在 $CF$ 和洛谷上都 $\color{lightgreen}AC$ 了前 $8$ 个测试点。

![](https://cdn.luogu.com.cn/upload/image_hosting/t8cw4qgb.png?x-oss-process=image/resize,m_lfit,h_1000,w_1000)

好啦，为了解决 $\color{purple}TLE$，我们不得不再次寻找更优的解法。

我们是不是可以用前缀和思想，在将 $a$ 数组排好序后，用 $qian_i$ 记录 $a$ 数组前 $i$ 个的和，因为 $a_i$ 不可能是负的，所以 $qian$ 数组中，一定是从小到大的。那么我们下一步做的，就是在 $qian$ 数组中找到第一个大于等于 $x_j$ 的数是第几个。因为 $qian$ 数组中是按从小到大排列的，所以，我们就可以用二分查找来寻找。

好啦，上代码。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[150005], x[150005], qian[150005];
bool cmp(long long a, long long b) {
	return a > b;
}
int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, q;
		cin >> n >> q;
		long long he = 0;
		for (int i =1 ; i <= n; i++) {
			cin >> a[i];
			he += a[i];
		}
		sort(a + 1, a + n + 1, cmp);
		for (int i = 1; i <= n; i++) {
			qian[i] = qian[i - 1] + a[i];
		} 
		for (int i =1 ; i <= q; i++) {
			cin >> x[i];
			if (x[i] > he) {
				cout << -1 << endl;
				continue;
			}  else if (x[i] == he) {
				cout << n << endl;
				continue;
			}
			int l = 1, r = n, mid;
			while(l < r) {
				mid = (l + r) >> 1;
				if (qian[mid] >= x[i]) {
					r = mid;
				} else {
					l = mid + 1;
				}
			}
			cout << l << endl;
		}
	} 
}
```

可能会有一些不足，请大家指出，谢谢！

---

## 作者：ttq012 (赞：0)

**Solution**

简单题。

贪心地将数组从大到小排序，然后记录数组的前缀和，二分枚举至少需要多少个数才可以满足这些数的和 $\ge$ 当前的数，求和用记录的前缀和即可。

时间复杂度 $\mathcal O(T\cdot (n + \log \sum a_i))$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;

const int N = (int) 1e6 + 10;
int a[N], s[N];

signed main() {
    int T;
    cin >> T;
    while (T --) {
        int n, Q;
        cin >> n >> Q;
        for (int i = 1; i <= n; i ++)
            cin >> a[i];
        sort (a + 1, a + n + 1, greater <int> ());
        for (int i = 1; i <= n; i ++)
            s[i] = s[i - 1] + a[i];
        while (Q --) {
            int x;
            cin >> x;
            int l = 1, r = n, best = -1;
            while (l <= r) {
                int mid = l + r >> 1;
                if (s[mid] >= x) {
                    best = mid;
                    r = mid - 1;
                } else 
                    l = mid + 1;
            }
            cout << best << '\n';
        }
    }
    return 0;
}

```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

首先，对于所有糖果，将其糖量从大到小排序。这样可以确保吃的糖的数量达到最小。

然后，计算前缀和。

然后，使用二分算法，求出最少吃多少糖。显然，答案是符合单调性的。

### 二、代码

```cpp
#include<cstdio>
#include<algorithm> 
using namespace std;
#define int long long
int t;
int n,q;
int a[150005],pre[150005];
int x;
bool cmp(int a,int b)
{
	return a>b;
}
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&q);
		for(int i=1;i<=n;i++)//输入
		{
			scanf("%lld",&a[i]);
		}
		sort(a+1,a+1+n,cmp);//排序
		for(int i=1;i<=n;i++)//计算前缀和
		{
			pre[i]=pre[i-1]+a[i];
		}
		while(q--)
		{
			scanf("%lld",&x);
			int l=1,r=n;//标准的二分
			int ans=-1;
			while(l<=r)
			{
				int middle=(l+r)>>1;
				if(pre[middle]>=x)//吃了middle颗糖后可以达到糖量要求
				{
					ans=middle;
					r=middle-1;
				}
				else//不可以达到要求
				{
					l=middle+1;
				}
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}

```


---

## 作者：include_BM (赞：0)

将所有 $a_i$ 按照从大到小排序，显然从大的开始吃所需的个数最少。

对 $a_i$ 求前缀和 $s_i$，问题变为求 $s_i$ 中第一个 $\ge x$ 的数的下标。

由于 $s_i$ 单调增，故可以使用二分解决。

```cpp
sort(a+1,a+n+1,greater<int>());
for(int i=1;i<=n;++i) s[i]=s[i-1]+a[i];
for(int x;q;--q){
    scanf("%d",&x);
    if(x>s[n]) printf("-1\n"); //比总和还大就不可能达到。
    else printf("%d\n",lower_bound(s+1,s+n+1,x)-s);
}
```

`lower_bound(l,r,x)` 函数会返回地址 $[l,r)$ 范围内第一个大于等于 $x$ 的数的地址，减去数组首地址即为数组中的下标。

---

