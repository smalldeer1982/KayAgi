# Robin Hood in Town

## 题目描述

In Sherwood, we judge a man not by his wealth, but by his merit.



Look around, the rich are getting richer, and the poor are getting poorer. We need to take from the rich and give to the poor. We need Robin Hood!

There are $ n $ people living in the town. Just now, the wealth of the $ i $ -th person was $ a_i $ gold. But guess what? The richest person has found an extra pot of gold!

More formally, find an $ a_j=max(a_1, a_2, \dots, a_n) $ , change $ a_j $ to $ a_j+x $ , where $ x $ is a non-negative integer number of gold found in the pot. If there are multiple maxima, it can be any one of them.

A person is unhappy if their wealth is strictly less than half of the average wealth $ ^{\text{∗}} $ .

If strictly more than half of the total population $ n $ are unhappy, Robin Hood will appear by popular demand.

Determine the minimum value of $ x $ for Robin Hood to appear, or output $ -1 $ if it is impossible.

 $ ^{\text{∗}} $ The average wealth is defined as the total wealth divided by the total population $ n $ , that is, $ \frac{\sum a_i}{n} $ , the result is a real number.

## 说明/提示

In the first test case, it is impossible for a single person to be unhappy.

In the second test case, there is always $ 1 $ happy person (the richest).

In the third test case, no additional gold are required, so the answer is $ 0 $ .

In the fourth test case, after adding $ 15 $ gold, the average wealth becomes $ \frac{25}{4} $ , and half of this average is $ \frac{25}{8} $ , resulting in $ 3 $ people being unhappy.

In the fifth test case, after adding $ 16 $ gold, the average wealth becomes $ \frac{31}{5} $ , resulting in $ 3 $ people being unhappy.

## 样例 #1

### 输入

```
6
1
2
2
2 19
3
1 3 20
4
1 2 3 4
5
1 2 3 4 5
6
1 2 1 1 1 25```

### 输出

```
-1
-1
0
15
16
0```

# 题解

## 作者：Temp113 (赞：3)

## Solution

答案显然满足单调性，考虑二分。可以先将数组排序，对于验证一个 $x$，修改最大值，统计不快乐的人数，恢复，最后判断。

时间复杂度：$\mathcal O(n \log n)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int t, n, a[N], L, R, mid, tmp, s, tot, ans;
double d;
bool check(int aa){
	tmp = a[n];
	a[n] += aa;
	s = 0;
	tot = 0;
	for(int i = 1; i <= n; i++) s += a[i];
	d = ((double) s) / n / 2;
	for(int i = 1; i <= n; i++) if(a[i] < d) tot++;
	a[n] = tmp;
	if(tot > ((double) n) / 2) return 1;
	else return 0;	
}
void solve(){
	L = 0;
	R = 1e18;
	ans = -1;
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	while(L <= R){
		mid = (L + R) >> 1;
		if(check(mid)){
			R = mid - 1;
			ans = mid;
		}else L = mid + 1;
	}
	cout << ans << '\n';
	return ;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie();
	cin >> t;
	for(int kk = 1; kk <= t; kk++) solve(); 
	return 0;
}
```

---

## 作者：alan1118 (赞：2)

## 思路

如果 $n\le 2$ 就直接输出 $-1$，易证。

先排序，$a_{n/2+1}+1$ 就是平均数。

接着用平均数倒推计算当罗宾汉会出现时的钱的总数，最后减去开始时的总和就可以了。

### 注意：

+ 开 long long！
+ 如果最后的结果小于 $0$，就输出 $0$。
+ 因为是多组数据，在判断 $n\le2$ 时，一定记住在这组数据所有输入结束后再输出 $-1$。

下面就是完整代码了：

## Code

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

using LL = long long;

const int N = 2e5 + 5;

LL a[N];

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		LL sum = 0;
		for(int i = 1; i <= n; i++)
		{
			cin >> a[i];
			sum += a[i];
		}
		if(n <= 2)
		{
			cout << -1 << endl;
			continue;
		}
		sort(a+1, a+n+1);
		LL p = a[n/2+1];
		LL m = p * 2 * n + 1;
		cout << max(0LL, m-sum) << endl;
	}
	return 0;
}
```

---

## 作者：jess1ca1o0g3 (赞：2)

我们的目标就是找到一个 $x$，使得 $a_i$ **严格小于** $\frac{(\sum a_i)+x}{2n}$ 的个数大于 $n\over 2$。可以考虑二分答案。预处理一个 $\sum a_i$，每次加上 $m$，则可以在线性时间下检验出。当然，在 $n\leq 2$ 时必定无解，因为无论如何加，满足条件的个数不可能大于 $n\over 2$。复杂度 $\mathcal{O(n\log n)}$。不过需要注意的是答案可能会非常大（非常坑），且下界为 $0$。[代码](https://paste.ubuntu.com/p/KNFbjwyY8q/)。

---

## 作者：Karieciation (赞：2)

## 题目大意分析

$n$ 个人，每个人有 $a_i$ 个金币，求一个 $\min{x}$，设所有人金币总和为 $sum$，$k_i$ 为第 $i$ 贫穷的人， $k_{\lfloor n\div2\rfloor+1}<\dfrac{sum+x}{2n}(x,\forall k_i,sum,n\in\mathbb Z )$ 。

由题意得，当 $n\le2$ 时，一定无解，特判输出 `-1`。

当 $n>2$ 时，一定有解，解上面不等式得：$x>k_{\lfloor n\div2\rfloor+1}\cdot n\cdot2-sum(x,\forall k_i,sum,n\in\mathbb Z )$。

$$\therefore x=\begin{cases}
  k_{\lfloor n\div2\rfloor+1}\cdot n\cdot2-sum+1 & (k_{\lfloor n\div2\rfloor+1}\cdot n\cdot2\ge sum) \\
  0 & (k_{\lfloor n\div2\rfloor+1}\cdot n\cdot2<sum)
\end{cases}$$

将数组 $a$ 从小到大排序，即可得到数组 $k$。

此题完~。

$Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5,INF=0x3f3f3f3f;
int n,a[N];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		ll sum=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",a+i);
			sum=sum+a[i];
		}
		if(n<3)
		{
			puts("-1");continue;
		}
		sort(a+1,a+1+n);
		ll v=(ll)a[n+2>>1]*n<<1;
		if(sum>v)
			puts("0");
		else
			printf("%lld\n",v-sum+1);
	}
	return 0;
}
```

---

## 作者：naroto2022 (赞：2)

# CF2014C 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF2014C)

### 题意

城镇里有 $n$ 个人。现在，第 $i$ 个人的财富是 $a_i$ 金币。找出 $a_j=\max(a_1,a_2,\cdots,a_n)$，将 $a_j$ 改为 $a_j+x$，其中 $x$ 是从罐子里找到的非负整数金币。如果有多个最大值，取其中任意一个即可。

如果一个人的财富严格低于平均财富的一半，他们就会感到不幸福。

如果超过一半的人口感到不幸福，罗宾汉就会应大家的要求出现。

请确定为了让罗宾汉出现的最小 $x$ 值，或者输出 $-1$ 如果这不可能。

### 思路

依题求即可。

首先 $n$ 为 $1,2$ 的时候显然无解。

接着想到给 $a$ 排序，并算出 $a$ 的和 $cnt$，算出第 $\frac{n}{2}+1$ 个数，以这个数为平均数，求出有超过一半的人口感到不幸福时钱的总数，减去 $cnt$ 即可。

具体见代码。

### 代码


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int MN=2e5+5;
ll n,a[MN],num,cnt;
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
void solve(){
    n=read();cnt=0;
    for(int i=1; i<=n; i++) a[i]=read(),cnt+=a[i];
    if(n==1||n==2){
        write(-1);putchar('\n');
        return;
    }
    sort(a+1,a+1+n);
    num=a[(n>>1)+1];
    num=num*2*n+1;
    write(max(0ll,num-cnt));putchar('\n');
}
int main(){
    // freopen("1.in","r",stdin);
    ll T=read();while(T--) solve();
	return 0;
}
```

---

## 作者：cxoi1711 (赞：1)

## 题目传送门：[Robin Hood in Town](https://www.luogu.com.cn/problem/CF2014C)
## 思路：
这道题很简单，如果 $N≤2$ 就输出 $-1$，否则先排序，排好序之后找到数组中正中间的一个数，它就是平均数，最后，我们用这个平均数去倒推就行了。

本题千万不要忘了开 long long！
## AC Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std; 
ll a[200010],t,n,sum,p,m;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		sum=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			sum+=a[i];
		}
		if(n<=2){
			cout<<"-1\n";continue;
		}
		sort(a+1,a+1+n);
		p=a[n/2+1];
		m=p*2*n+1;
		ll ck=0;
		cout<<max(ck,m-sum)<<endl;
	}
}
``````

---

## 作者：boluo2014 (赞：1)

这道题目还挺简单的。

### 思路

第一，如果 $n \le 2$，那么一定不可能，这个很容易证明。

否则，继续看：平均数，那可以用 sort 排序啊！那么直接取 $a_{\lfloor \frac{n}{2}\rfloor+1}$ 就是平均值。

然后根据平均值倒退，过程是先 $\times 2$，然后 $\times n$。这个值减去所有数的和，便是答案吗？不是。如果小于 $0$，就不对了，那么小于 $0$ 的情况下应该取 $0$。

### 代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
signed main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        int n,i;
        cin>>n;
        for(i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        if(n==1||n==2)
        {
            cout<<"-1"<<endl;
            continue;
        }
        else
        {
            sort(a+1,a+1+n);
            int s=(a[n/2+1])*n*2+1;
            for(i=1;i<=n;i++)
            {
                s-=a[i];
            }
            if(s<0)
            {
                s=0;
            }
            cout<<s<<endl;
        }
    }
    return 0;
}
```
希望大家能理解。

---

## 作者：wawatime1 (赞：1)

### 思路
1. $n = 1$ 和 $n = 2$ 时显然无解。
2. 先求出 $a$ 数组的和，用 $s$ 表示。
3. 看到平均数想到排序，排完序后，$a$ 数组中的第 $\displaystyle \frac{n}{2} + 1$ 项就为平均数。
4. 以这个平均数，求出有超过一半的人口感到不幸福时钱的总数，减去 $s$ 即可。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, a[200005], m, s, t;
signed main () {
	cin >> t;
	while (t--) {
		cin >> n;
		sum = 0;
		for (int i = 1; i <= n; i ++) {
			cin >> a[i];
			s += a[i];
		}
		if (n == 1 || n == 2) {
			cout << -1 << endl;
			return;
		}
		sort (a + 1, a + 1 + n);
		m = a[(n / 2) + 1];
		m = m * 2 * n + 1;
		cout << max (0, m - s) << endl;
	}
	return 0;
}
```

---

## 作者：WRT_Partisan (赞：1)

# 题解：CF2014C Robin Hood in Town

[题目链接](https://www.luogu.com.cn/problem/CF2014C)

## 题目大意

找到一个使小于 $\dfrac{(\sum a_i)+x}{2n}$ 的 $a_i$ 的个数大于 $\dfrac{n}{2}$ 的最小 $x$ 值。

## 解题思路

首先特判：当 $n=1$ 或 $n=2$ 时无解。

将 $a$ 排序，则当 $a_{\lfloor n/2 \rfloor+1} \times n \times 2<\sum a_i$ 时，已经满足条件，$x=0$ 即可。

否则 $x=a_{\lfloor n/2 \rfloor+1} \times n \times 2-\sum a_i+1$。

## 代码

```cpp
/*
 * @FilePath: \c++\CF2014C.cpp
 * @Author: WRT_Partisan
 * @Date: 2024-11-16 20:35:55
 */
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef unsigned long long ull;
int t, n, a[200005], all;
signed main()
{
    scanf("%lld", &t);
    while (t--)
    {
        all = 0;
        scanf("%lld", &n);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &a[i]), all += a[i];
        sort(a + 1, a + n + 1);
        if (n <= 2)
            printf("-1\n");
        else if (a[n / 2 + 1] * n * 2 - all < 0)
            printf("0\n");
        else
            printf("%lld\n", a[n / 2 + 1] * n * 2 - all + 1);
    }
    return 0;
}
```

---

## 作者：INT_MAX66zz (赞：1)

注：此题解所有 $n ÷ 2$ 全部向下取整。

当 $n = 1$ 时，显然无解

当 $n = 2$ 时，此时至少有一个人不小于平均值，无解。

对于其他情况，我们发现，当第 $n÷2$ 小的数满足小于平均值，但第 $n÷2+1$ 小的数不满足就行了。

设第 $n÷2+1$ 小的数为 $a$ ,不难发现，当 $a$ 变为 $a ×2×n+1$ 时，即可满足上述情况。

[code](https://www.luogu.com.cn/paste/7fqrgtbz)

---

## 作者：Super_Cube (赞：1)

# Solution

答案具有单调性且时间允许，考虑二分。

首先对 $a$ 从小到大排序。判断二分出的 $x$ 是否合法为先使 $a_n\gets a_n+x$（因为 $a_n$ 一定为 $a$ 中最大值），记 $s=\sum a_i$，若 $\sum[a_i<\frac{s}{2n}]>\frac{n}{2}$ 则说明 $x$ 合法，右边界左调，否则左边界右调。别忘了回溯：$a_n\gets a_n-x$。

# Code

```cpp
#include<bits/stdc++.h>
long long a[200005];
int T,n;
long long s,l,r,ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		s=0;
		for(int i=1;i<=n;++i)
			scanf("%lld",&a[i]),s+=a[i];
		std::stable_sort(a+1,a+n+1);
		l=0;r=1e18;ans=-1;
		while(l<=r){
			long long mid=l+r>>1;
			a[n]+=mid;
			if(std::lower_bound(a+1,a+n+1,(s+mid)/2.0/n)-a-1>(n>>1))ans=mid,r=mid-1;
			else l=mid+1;
			a[n]-=mid;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

按题目翻译所述求解即可：


$1.$    $n$ 为 $1,2$ 的时候显然无解。

$2.$ 给数组 $a$ 排序，并算出数组 $a$ 的和。在这里，令变量 $sum = a _ 1 + a _ 2 + \ldots + a _ n$。

$3.$ 计算平均数 $\frac{n}{2} + 1$，以这个数为平均数，求出有超过一半的人口感到不幸福时钱的总数，减去变量 $sum$ 即可。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
const ll MAXN = 2e5 + 10;
ll n, a[MAXN], num, sum, T;
void read () {
    cin >> n;
	sum = 0;
    for (ll i = 1; i <= n; i ++) {
		cin >> a[i];
		sum += a[i];
	}
    if (n == 1 || n == 2) {
        cout << -1 << endl;
        return;
    }
    sort (a + 1, a + 1 + n);
    num = a[(n / 2) + 1];
    num = num * 2 * n + 1;
    cout << max (0ll, num - sum) << endl;
}
int main () {
    cin >> T;
    while (T --) read ();
	return 0;
}
```

---

## 作者：_colin1112_ (赞：0)

## 思路

考虑二分答案，二分对象是新发现的黄金 $x$。

对于二分出来的 $x$，每次计算不快乐的人数，如果 **严格大于** 总人口 $n$ 的一半，说明当前的 $x$ 是可行的，需要再次缩小范围继续枚举；否则，则扩大范围，将 $x$ 增大。

最后二分出来的最小的 $x$ 就为答案。

注意：$0$ 也是可行的答案，以及 $n \leq 2$ 时显然不可行，要输出 $-1$。

## Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E = 1e6 + 5;
ll t, n;
ll a[E];
inline bool check(ll x)
{
    ll max1 = -1e18, id = 0, sum = 0;
    for (int i = 1; i <= n; i++)
        if (max1 > a[i])
            max1 = a[i], id = i, sum += a[i];
        else
            sum += a[i];
    a[id] += x, sum += x;
    double avg = sum * 1.0 / n;
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        if (a[i] < avg / 2.0)
            ans++;
    // cout << avg << endl;
    a[id] -= x;
    return ans > n / 2;
}
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        if (n <= 2)
        {
            cout << -1 << endl;
            continue;
        }
        ll l = 0, r = 1e18, ans = -1;
        while (l <= r)
        {
            ll mid = l + r >> 1;
            if (check(mid))
                r = mid - 1, ans = mid;
            else
                l = mid + 1;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：lhz123bc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2014C)

首先我们需要知道，$n \le 2$ 时是无解的，应输出 ```-1```。

对于其他的情况，我们可以选择对输入数组 $shu$ 进行排序，并算出 $\sum_{i=1}^n{a_i}$ 的值 $sum$，我们以第 $\frac{n}{2}+1$ 个数作为平均值，求出有超过一半的人口感到不幸福时钱的总数，即 $shu[\frac{n}{2}+1] \times 2 \times n+1$，减去 $sum$ 即可。

[AC Code](https://www.luogu.com.cn/paste/wjcxx12q)

---

## 作者：chatoudp (赞：0)

显然 $n\le2$ 时一定无解。

其他情况，可以找出序列中第 $\frac{n}{2}+1$ 个数，此时他感到不幸福就满足了要求。它乘 $2\times n$，再加 $1$ 为最少需要总和是多少，减去原先的总和即为答案。

AC Time：

```cpp
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define itn int
#define Please int
#define AC main(){
#define pritnf printf
using namespace std;
typedef long long ll;
int n,a[1000005],T;
ll sum;
Please AC//'_' T_T ^_^
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		sum=0;
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum+=a[i];
		sort(a+1,a+n+1);
		if(n<=2) printf("-1\n");
		else{
			ll psum=a[n/2+1]*2LL*n;
			printf("%lld\n",max(0LL,psum+1-sum));
		}
	}
	I AK IOI
}

```

---

## 作者：cly312 (赞：0)

分享一种二分答案做法。

先特判 $n=1$，$n=2$，开始就有超过一半的人不高兴的情况。

然后二分 $x$，计算新的和，新的平均值，如果有超过一半的人不高兴，就更新答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		vector<long long>a(n);
		long long S=0;
		long long a_max=0;
		for(int i=0;i<n;++i){
			cin>>a[i];
			S+=a[i];
			a_max=max(a_max,a[i]);
		}
		if(n==1||n==2){
			cout<<-1<<endl;
			continue;
		}
		long long unhappy_count=0;
		double half_avg=1.0*S/(2*n);
		for(int i=0;i<n;++i){
			if(a[i]<half_avg){
				unhappy_count++;
			}
		}
		if(unhappy_count>n/2){
			cout<<0<<endl;
			continue;
		}
		long long left=0;
		long long right=1e18;
		long long result=-1;
		while(left<=right){
			long long mid=(left+right)/2;
			long long new_S=S+mid;
			double new_half_avg=1.0*new_S/(2*n);
			long long new_unhappy_count=0;
			for(int i=0;i<n;++i){
				if(a[i]<new_half_avg){
					new_unhappy_count++;
				}
			}
			if(new_unhappy_count>n/2){
				result=mid;
				right=mid-1;
			}else{
				left=mid+1;
			}
		}
		if(result==-1){
			cout<<-1<<endl;
		}else{
			cout<<result<<endl;
		}
	}

	return 0;
}

```

---

## 作者：cxoi1501 (赞：0)

## 题目传送门：[Robin Hood in Town](https://www.luogu.com.cn/problem/CF2014C)
## 思路：
这道题很简单，如果 $N≤2$ 就输出 $-1$，否则先排序，排好序之后找到数组中正中间的一个数，它就是平均数，最后，我们用这个平均数去倒推就行了。

本题千万不要忘了开 long long！
## AC Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std; 
ll a[200010],t,n,sum,p,m;
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        sum=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            sum+=a[i];
        }
        if(n<=2){
            cout<<"-1\n";continue;
        }
        sort(a+1,a+1+n);
        p=a[n/2+1];
        m=p*2*n+1;
        ll ck=0;
        cout<<max(ck,m-sum)<<endl;
    }
}
``````

---

