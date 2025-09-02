# Ticket Hoarding

## 题目描述

[Maître Gims - Est-ce que tu m'aimes ?](https://youtu.be/6TpyRE_juyA)

ඞ



As the CEO of a startup company, you want to reward each of your $ k $ employees with a ticket to the upcoming concert. The tickets will be on sale for $ n $ days, and by some time travelling, you have predicted that the price per ticket at day $ i $ will be $ a_i $ . However, to prevent ticket hoarding, the concert organizers have implemented the following measures:

- A person may purchase no more than $ m $ tickets per day.
- If a person purchases $ x $ tickets on day $ i $ , all subsequent days (i.e. from day $ i+1 $ onwards) will have their prices per ticket increased by $ x $ .

For example, if $ a = [1, 3, 8, 4, 5] $ and you purchase $ 2 $ tickets on day $ 1 $ , they will cost $ 2 $ in total, and the prices from day $ 2 $ onwards will become $ [5, 10, 6, 7] $ . If you then purchase $ 3 $ more tickets on day $ 2 $ , they will cost in total an additional $ 15 $ , and the prices from day $ 3 $ onwards will become $ [13, 9, 10] $ .

Find the minimum spending to purchase $ k $ tickets.

## 说明/提示

In the first test case, one optimal way to buy $ 3 $ tickets is as follows:

- Buy $ 0 $ tickets on the first day. The prices per ticket for the remaining days are $ [6, 4, 2] $ .
- Buy $ 0 $ tickets on the second day. The prices per ticket for the remaining days are $ [4, 2] $ .
- Buy $ 1 $ ticket on the third day with cost $ 4 $ . The price per ticket for the remaining day is $ [3] $ .
- Buy $ 2 $ tickets on the fourth day with cost $ 6 $ .

In the second test case, there is only one way to buy $ 8 $ tickets:

- Buy $ 2 $ tickets on the first day with cost $ 16 $ . The prices per ticket for the remaining days are $ [8, 6, 4] $ .
- Buy $ 2 $ tickets on the second day with cost $ 16 $ . The prices per ticket for the remaining days are $ [8, 6] $ .
- Buy $ 2 $ tickets on the third day with cost $ 16 $ . The price per ticket for the remaining day is $ [8] $ .
- Buy $ 2 $ tickets on the fourth day with cost $ 16 $ .

## 样例 #1

### 输入

```
4
4 2 3
8 6 4 2
4 2 8
8 6 4 2
5 100 1
10000 1 100 10 1000
6 3 9
5 5 5 5 5 5```

### 输出

```
10
64
1
72```

# 题解

## 作者：littlebug (赞：5)

## Solution

设在 $1\sim n$ 买的票的个数分别为 $b_1\sim b_n$。求 $\displaystyle \sum_{i=1}^n ( b_i \times ( a_i + \sum_{j=1}^{i-1} b_j ) )$ 的最小值。

推柿子：

$$
\displaystyle \begin{aligned}
\sum_{i=1}^n ( b_i \times ( a_i + \sum_{j=1}^{i-1} b_j ) ) & =\sum_{i=1}^n(b_i a_i + b_i \sum_{j=1}^{i-1} b_j ) \\
& =\sum_{i=1}^n a_i b_i + \sum_{i=1}^n b_i \sum_{j=1}^{i-1} b_j \\
& =\sum_{i=1}^n a_i b_i + \sum_{i=1}^n \sum_{j=1}^{i-1} b_i b_j \\
& =\sum_{i=1}^n a_i b_i + \sum_{1 \le j < i \le n} b_i b_j
\end{aligned}
$$

于是，如果对调一对 $(i,j)$，原式变为：

$$\sum_{j=1}^n a_j b_j + \sum_{1 \le i < j \le n} b_j b_i$$

容易看出来，结果是不变的，因此可以将数组 $a$ 排序，贪心一下即可。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define il inline
#define ll long long
using namespace std;
const int MAXN=3e5+5;
ll n,m,k;
ll a[MAXN];
il void solve()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	sort(a+1,a+n+1);
	ll ans=0,add=0;
	for(int i=1;i<=n;++i)
	{
		if(k>=m)
		{
			k-=m;
			ans+=m*(a[i]+add);
			add+=m;
		}
		else
		{
			ans+=k*(a[i]+add);
			cout<<ans<<'\n';
			return;
		}
	}
	cout<<ans<<'\n';
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：Karl_Aldrich (赞：2)

### 题目大意
给出长度为 $n$ 的数列 $a$，其中 $a_i$ 表示在第 $i$ 天购买一张门票需要 $a_i$ 元，假如你买了 $c$ 张门票，那么从第 $i+1$ 天到第 $n$ 天的门票价格全部增加 $c$。
### 思路
考虑贪心。

尝试找到一种方法来解释第 $i$ 天因前几天购买而上涨的价格。

我们知道，在 $i$ 之前购买的每张票都会将每张票 $i$ 的价格提高 $1$；反过来，每次在第 $i$ 天购买机票时，这笔“附加税”都会添加到我们的总费用中。

尝试找到一种方法来优化基础成本和总附加税。观察到“尽可能多地购买便宜门票”的策略对它们都适用。

下面考虑如何实现。

假设我们在第 $1, 2, \ldots, n$ 分别购买了 $b_1, b_2, \ldots, b_n$ 张门票，那么第 $i$ 天门票的价格将为 $a_i + b_1 + b_2 + \ldots + b_{i-1} = a_i + \sum_{j=1}^{i-1} b_j$ 元，由此，可以得出总成本为：$\sum_{i=1}^{n} (a_i + \sum_{j=1}^{i-1} b_j)b_i = \sum_{i=1}^{n} a_ib_i + \sum_{1 \leq j < i \leq n} b_ib_j$ 元。

有意思的一点是，假如我们随便选择两天 $i$ 和 $j$ 并将 $(a_i, b_i)$ 和 $(a_j, b_j)$ 交换，最终计算出来的结果将不会改变，因此我们可以自由的排列 $a$ 而不改变答案。

### 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
#define rep(i,s,e) for(int i=s;i<=e;++i)
#define int long long
//记得开long long
const int INF=0x7f7f7f7f;
int read(){
	int num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=='-'?f=-1:f=1,ch=getchar();
	while(ch>='0'&&ch<='9')num=num*10+ch-'0',ch=getchar();
	return f*num;
}
void write(int num){
	if(num<0){
		putchar('-');
		num*=-1;
	}
	if(num>9)write(num/10);
	putchar(num%10+'0');
}
int T;
int n,m,k;
int a[300010];
int ans,more;//more即为附加税
signed main(){
	T=read();
	while(T--){
		n=read(),m=read(),k=read();
		rep(i,1,n)a[i]=read();
		sort(a+1,a+n+1);
		ans=0,more=0;
		rep(i,1,n){
			int cnt=min(m,k);
			ans+=1ll*cnt*(a[i]+more);
			more+=cnt;
			k-=cnt;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：EastIsRed (赞：1)

## 题目翻译

作为一家初创公司的 $\texttt{CEO}$，你想奖励你的 $k$ 名员工每人一张即将到来的音乐会的门票。门票将会销售 $n$ 天，通过一些时间旅行，你已经预测到第一天的每张票的价格将会是 $100$ 美元。不过，为防止囤积门票，音乐会主办方采取了以下措施:

每人每天可购买不超过 $m$ 张票。
如果一个人在第 $1$ 天购买了 $x$ 张票，那么随后的所有日子(即从第 $2$ 日起)的每张票的价格将增加 $x$。
例如，如果 $a=[1,3,8,4,5]$，你在第一天购买了2张票，它们将花费 $2$，从第二天开始的价格将变成 $[5,10,6,7]$。如果你在第 $2$ 天再购买 $3$ 张票，他们将花费额外的 $15$ 美元，从第 $3$ 天开始的价格将变成 $[13,9,10]$。

求购买 $k$ 张票的最小花费。

## 形式化题意
给定一个长度为 $n$ 的正整数数组 $a$，求一个正整数数组 $b$ 在满足 $\sum_{i=1}^n b_i = k$ 的条件下，使得 $\sum_{i=1}^n b_i(a_i + \sum_{j=1}^{i-1}b_i)$ 尽可能小。

## 题目解析
对上面的式子进行变形。
$$ \begin{align*}
\sum_{i=1}^n b_i(a_i + \sum_{j=1}^{i-1}b_i) &=  \sum_{i=1}^n a_i b_i + \sum_{i=1}^n \sum_{j=1}^{i-1}b_i
\\&= \sum_{i=1}^n a_i b_i + \frac{1}{2}(\sum_{i=1}^n b_i)^2 - \frac{1}{2}\sum_{i=1}^n b_i^2
\\&= \sum_{i=1}^n (a_i-\frac{1}{2}b_i)b_i + \frac{1}{2} k^2
\\&= \frac{1}{2}\sum_{i=1}^n (a_i^2-(b_i-a_i)^2) +\frac{1}{2} k^2
\\&= -\frac{1}{2} \sum_{i=1}^n (b_i-a_i)^2 + \frac{1}{2}\sum_{i=1}^n a_i^2 + \frac{1}{2} k^2
 \end{align*} $$

因而，我们显然能够发现，若使该式值最小，则应使 $\sum_{i=1}^n (b_i-a_i)^2$ 尽可能大，即在 $a_i$ 较小时使 $b_i$ 尽量大，$a_i$ 较大时使 $b_i$ 尽量小。

对数组 $a$ 按升序排序，将 $b$ 的前 $\lfloor \frac{k}{m} \rfloor$ 项置为 $m$，如果 $k \mod m \neq 0$ 时将第 $\lfloor \frac{k}{m} \rfloor + 1$ 项置为 $k \mod m$，其余项置为 $0$，即可满足要求。

时间复杂度 $O(n \log n)$。

## 代码实现
```cpp
#include<cstdio>
#include<algorithm>
int T;
int n,m,k;
int a[300086];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++)
            scanf("%d",a+i);
        std::sort(a+1,a+1+n);
        long long sum=1ll*k*k;
        for(int i=1;i<=n;i++)
            if(k>=m)
            {
                sum-=1ll*(m-a[i])*(m-a[i]);
                k-=m;
            }
            else if(k)
            {
                sum-=1ll*(k-a[i])*(k-a[i]);
                k=0;
            }
            else sum-=1ll*a[i]*a[i];
        for(int i=1;i<=n;i++)
            sum+=1ll*a[i]*a[i];
        printf("%lld\n",sum/2);
    }
    return 0;
}
```

---

## 作者：fsp_luogu (赞：0)

## 思路

通过观察题目给出的样例说明，我们可以得出三点：

- 要将得到的数组**从大到小**排序。
- 从下标 $[n-(k \div m+1)+1]$ 开始向后买票，如果下标是 $[n-(k \div m+1)+1]$（即最开始）买 $ k\bmod m $ 张票，其余都买 $k$ 张票。
- 每次买票的单价 $=$ 原价 $+$ 已买的票数（建个数组记录下来）。

## Code

我的码风有点丑，请多包涵。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
const int N = 3e5+10;
ll t;
ll n,m,k;
ll a[N];
bool cmp(ll a,ll b){
	return a>b;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		for(int i = 1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1,cmp);
		ll start =n-(k/m+1)+1;
		ll ans = 0;
		ll c = 0;
		for(int i = start;i<=n;i++){
			if(i == start){
				ans+=a[i]*(k%m);
				c+=k%m;
			}else{
				ans+=(a[i]+c)*m;
				c+=m;
			}
		}
		cout<<ans<<'\n';
	}	
	return 0;
} 
```

---

## 作者：_Lightning_ (赞：0)

# Ticket Hoarding

## 思路

考虑贪心，从最便宜的门票开始买，注意在这之前先排序。每次先判断，如果将门票全买了还没到我们需要的门票数就直接全买。然后记下后面每张门票多花的钱，如果这次买票之后的总票数能到我们需要的总票数就买我们还需要的门票数。

## AC Code


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=300005;
ll t;
ll n,m,k;
ll a[N]; 
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++) 
			cin>>a[i];
		sort(a+1,a+1+n);//排序 
		ll i=1,s=0,ans=0;
		while(k!=0){
			if(k>=m){
				k-=m;
				ans+=m*(a[i]+s);
				s+=m;
			}
			else{
				ans+=k*(a[i]+s);
				k=0;
			}
			i++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：gaomingyang101011 (赞：0)

## 思路

因为题目要求我们求门票的最小花费，所以我们要从门票价格最小的门票开始买，那就我们就要先将输入的序列排序，然后每次判断将门票全买了还没到我们需要的门票数就全买，然后记录后面每张门票要多花的钱，如果这次买票之后的总票数能到我们需要的门票数就买我们还需要的门票数。

## 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const long long N=3*1e5+1;
long long t;
long long n,m,k;
long long a[N]; 
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+1+n);
		long long i=1,s=0;
		long long ans=0;
		while(k!=0){
			if(k>=m){
				k-=m;
				ans+=m*(a[i]+s);
				s+=m;
			}
			else{
				ans+=k*(a[i]+s);
				k=0;
			}
			i++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

