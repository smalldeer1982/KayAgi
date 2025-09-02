# [ABC050C] Lining Up

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc050/tasks/arc066_a

$ 1～N $ までの番号がついた、$ N $ 人の人がいます。 彼らは昨日、ある順番で左右一列に並んでいましたが、今日になってその並び方が分からなくなってしまいました。 しかし、彼らは全員、「自分の左に並んでいた人数と自分の右に並んでいた人数の差の絶対値」を覚えています。 彼らの報告によると、人 $ i $ の、「自分の左に並んでいた人数と自分の右に並んでいた人数の差の絶対値」は $ A_i $ です。

彼らの報告を元に、元の並び方が何通りあり得るかを求めてください。 ただし、答えは非常に大きくなることがあるので、$ 10^9+7 $ で割った余りを出力してください。 また、彼らの報告が間違っており、ありうる並び方がないこともありえます。 その際は $ 0 $ を出力してください。

## 说明/提示

### 制約

- $ 1≦N≦10^5 $
- $ 0≦A_i≦N-1 $

### Sample Explanation 1

ありうる並び方は、人の番号で書くと、 - $ 2,1,4,5,3 $ - $ 2,5,4,1,3 $ - $ 3,1,4,5,2 $ - $ 3,5,4,1,2 $ の $ 4 $ 通りです。

### Sample Explanation 2

どのような並び方でも、報告と矛盾するので、$ 0 $ が答えになります。

## 样例 #1

### 输入

```
5
2 4 4 0 2```

### 输出

```
4```

## 样例 #2

### 输入

```
7
6 4 0 2 4 0 2```

### 输出

```
0```

## 样例 #3

### 输入

```
8
7 5 1 1 7 3 5 3```

### 输出

```
16```

# 题解

## 作者：Iktsuarpok (赞：4)

题意其实可以转化成这样，有一段无序序列，需要你去排序后判断是否满足一定的递增规律——
## 不懂？

我们可以这样想，每个人的位置是不确定的，但他们有一个相对位置，举个例子：

# 1 1    _**1**_    1 1 1 1 1 1 1 1

看到那个歪了的‘1’吗（你一定看到了对吧），由题意我们可以知道此处的Ai=|2-8|=6

那这个呢：

# 1 1 1 1 1 1 1 1  _1_  1 1

此处的Ai=|8-2|=6



因为给出了每个点的Ai，我们可以知道——


# 1 1  _1_  1 1 1 1 1  _1_  1 1

在排列的时候这两个Ai相等的点是可以互换的，总方案时应该为2^（n/2）。如果n为奇数，即有个人在最中间，它的Ai就为0，所以它没有可以互换的位置，n/2刚好把它舍掉了。

我们再看组样例：

		       5

		       2 4 4 0 2
               
答案为4，正好就是2^（n/2）个。但是为什么下一组样例会输出0呢？因为它不一定给的就是正确的Ai，然后需要你去判断。判断很简单，细心点你会发现，越中间的人的Ai就越小，直到最中间，只有可能是0或1，再往外推一点点，你就会发现： 

## 0 2 2 4 4 8 8……


## 1 1 3 3 5 5 7 7……

没错，就是开头所说的递增序列！我们只要给输入的Ai排个序，在一一与正确序列比较就行了

弱弱地献上蒟蒻的代码：
```cpp
#include<stdio.h>
#include<algorithm>
using namespace std;
const int mod=1e9+7;
int num[100005],a[100005];
void init(int x)
{
	if(x%2==0)
		for(int i=1;i<=x;i+=2) 
		{
			a[i]=i;
			a[i+1]=a[i];
		}
	else
		for(int i=2;i<=x;i+=2)
		{
			a[i]=i;
			a[i+1]=a[i];
		}
		
}
int main()
{
	int n,k=1;
	scanf("%d",&n);
	init(n);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	sort(num+1,num+1+n);
	for(int i=1;i<=n;i++)
		if(a[i]!=num[i])
		{
			printf("0");
			return 0; 
		}
			
	long long ans=1;
	n/=2;
	while(n--)
		ans=ans*2%mod;
	printf("%lld",ans);
	return 0;
}
```







---

## 作者：Buried_Dream (赞：1)

## Solution

如果 $n$ 为奇数，则必有一个人的左右两边数量想等，如果没有 $1$ 则无解。

前 $\frac{n}{2}$ 和后 $\frac{n}{2}$ 是对称的，

如果 $n$ 为奇数，则 $2, 4, 6, 8...$ 各出现了 $2$ 遍。

如果 $n$ 为偶数，则 $1, 3, 5, 7...$ 各出现了 $2$ 遍。
 
相等的位置可以交换，所以如果有解的话答案就是 $2^{\frac{n}{2}}$。

一个小优化就是判断有两遍的时候开俩个 `bitset`，查询的时候看看这俩个是否都有就可以了，加了这个优化就最优解了。

```cpp

bitset <10000001> vis1, vis2;
int f, a[N];

signed main() 
{
	int n = read();
	for(int i = 1; i <= n; i++) a[i] = read(), f |= (!a[i]);
	if(n & 1) {
		if(!f) return puts("0"), 0;
		for(int i = 1; i <= n; i++) {
			if(!vis1[a[i]]) vis1[a[i]] = 1;
			else vis2[a[i]] = 1;
		}
		for(int i = 2; i <= n; i += 2) {
			if(!vis1[i] || !vis2[i]) return puts("0"), 0;
		}
		printf("%lld\n", ksm(2, n / 2));
	}
	else {
		for(int i = 1; i <= n; i++) {
			if(!vis1[a[i]]) vis1[a[i]] = 1;
			else vis2[a[i]] = 1;
		}
		for(int i = 1; i <= n - 1; i += 2) {
			if(!vis1[i] || !vis2[i]) return puts("0"), 0;
		}
		printf("%lld\n", ksm(2, n / 2));
	}
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：0)

大家好，本蒟蒻又来写题解啦~

[这里是题目](https://www.luogu.com.cn/problem/AT2271)

这道题思路很简单，但是有一些细节需要注意。

不难想到，对于给出答案相同的人，只能有两个。一个站在左边，一个站在右边，是两个对称的位置。

为什么呢？因为左边的人数加上右边的人数一定是 $N-1$，而两个数知道它们的和，也知道差的绝对值，那两个数也就只有两种可能了。有可能左边的人比右边的人多，也有可能左边的人比右边的人少。

但是有个例外，就是给出的答案是 $0$。这说明左边人数和右边人数相等。那么这种情况下，人就一定站在中间位置，只有一种可能。

讲到这里，有些细心的同学会问了，如果 $N$ 是偶数，不就没有中间位置了吗？没错，$0$ 是不可能出现了。还有没有其他答案也不可能出现了呢？我们来列一个式子。假设左边人数为 $l$，右边人数为 $r$。

我们知道 $l+r=N-1$。说明 $l+r$ 与 $N$ 的奇偶性不同。则我们可以推出 $\operatorname{abs}(l-r)$ 与 $N$ 的奇偶性也不同，**则给出的答案 $A_i$ 与 $N$ 的奇偶性不同。**

因为题目里没保证这一点，所以这一点我们是需要判断的。

剩下的部分就可以找出当前这个人能站的位置方案有多少种，直接用加乘原理，把方案数一个个乘出来就可以了。以下是 AC 代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int mod=1e9+7;
int b[100010];//类似桶的思想。记录这个数出现了多少次。
int main()
{
    int n,mul=1;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int a;
        cin>>a;
        if(a%2==n%2)//特判奇偶性相同。
        {
            cout<<0<<endl;
            return 0;
        }
        b[a]++;
        if(a>0)mul=mul*(max(0,2-b[a]+1))%mod;
        else mul=mul*(max(0,1-b[a]+1))%mod;//特判 0。记得取模。
    }
    cout<<mul<<endl;
    return 0;
}
```

好了，本期题解就到这里，求 dalao 们点个赞吧~

~~本蒟蒻被特判和取模坑了很多次。。。~~

---

## 作者：bloodstalk (赞：0)

## 题目大意
有 $n$ 个人拍成一列，每个人左边的人数减去右边的人数的绝对值已经固定，问有几种排列情况（如果报告错误，输出 $0$）。

## 思路
### 找规律

  举一个例子，当 $n=5$ 的时候，从左到右他们的 $A_{i}$ 就分别为 $4$ $2$ $0$ $2$ $4$ ; 当 $n=6$ 的时候，从左到右他们的 $A_{i}$ 就分别为 $5$ $3$ $1$ $1$ $3$ $5$。由此我们发现，$A_{i}$的大小是左右对称的，那么导致有多种排列的原因就是绝对值：一个数可以出现在左半边，也可以出现在右半边。于是我们得到结论:
  $$
  A = 2^{\lfloor \frac{n}{2}\rfloor}
  $$

那么报告错误的话，就说明每个 $A_{i}$ 出现的次数不是两次（$0$ 出现一次），我们给一个桶，进行判断即可。

## 代码实现

```
#include<bits/stdc++.h>
const int N=1e5+5;
const int MOD=1e9+7;
using namespace std;

int n;
int a[N];
int tong[N];
int ans=1;

int main()
{
	/*freopen("queue.in","r",stdin);
	freopen("queue.out","w",stdout);*/
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),tong[a[i]]++;/*看看出现次数是否是两次*/
	bool flag=1;/*flag来验证是否正确*/
	if(n%2!=0)/*当n为奇数的时候才需要特判0，n为偶数的时候就不需要了*/
	{
		if(tong[0]==1)
		{
			for(int i=2;i<=n-1;i+=2)/*n为奇数的时候每个Ai为偶数，n为偶数的时候相反*/
				if(tong[i]!=2) /*不对就把flag设为0*/
				{
					flag=0;
					break;
				}
		}
		else flag=0;
	}
	else
	{
		for(int i=1;i<=n-1;i+=2)
			if(tong[i]!=2) 
				{
					flag=0;
					break;
				}
	}/*同理*/
	if(flag)/*验证是否正确*/
	{
		for(int i=1;i<=n/2;i++)
			ans=((ans%MOD)*2)%MOD;/*按照规律乘上2就可以了，这里数据较小，可以不用快速幂*/
		printf("%d",ans%MOD);
	}
	else printf("0");
	return 0;
} 
```


---

## 作者：Aisaka_Taiga (赞：0)

看了一下题解里 dalao 们的代码感觉好长，所以来发一篇短一点的。

## 基本思路

分析题目可以看出，当两个人给出的值一样（特殊 0 除外）时，他俩的位置是可以互换的，所以在之前的排列数的基础上乘二就好了，而当有一个人报的值有 1 个或 3 个时，就证明谎报了，输出 0。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int n,a[100010],ans=1,vis[100010],cnt=0;//a存放每一个人给出的值，vis标记每一个数出现的次数，cnt存放成对的数量，ans存答案 
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);//输入每一个人给出的值 
	for(int i=1;i<=n;i++)
	    vis[a[i]]++;//用桶排序原理来测出次数 
	for(int i=1;i<=n;i++)//从第一个开始 
	{
		if(vis[i]==2)//如果成对就乘二次数加一 
		cnt++; 
		if(vis[i]%2==1)//判断是否有人谎报 
		{
			cout<<"0"<<endl;//输出0 
			return 0;
		}
	}
	for(int i=1;i<=cnt;i++)
	ans=ans*2%mod;//计算排列方式总数 
	cout<<ans<<endl;//输出答案 
	return 0;//好习惯 
}
```


---

## 作者：cjZYZtcl (赞：0)

## ~~水题~~
如果有解，我们可以发现，从原排列正中间分开，左边和右边的人的 $a_i$ 是对称的。

所以如果有解，那么设 $k=\left\lfloor\tfrac{n}{2}\right\rfloor$，排列种数一定是 $2^k$ 。

而无解有以下几种情况：
- 总人数为奇数，而 $a_i$ 的最小值的数量不为1
- 总人数为偶数，而 $a_i$ 的最小值的数量不为2
- $a_i$ 中非最小值的数的数量不为2
- 原排列中相邻的两个 $a_i$ 的差的绝对值不为2

判断一下无解然后用快速幂计算就可以啦。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MOD 1000000007
int a[100005], b[100005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
int qpow(int x, int y){
	int z = 1;
	while(y){
		if(y % 2){
			z = z * x % MOD;
		}
		x = x * x % MOD;
		y = y / 2;
	}
	return z;
}
signed main(){
	int n = read(), m = 0;
	for(int i = 1; i <= n; i++){
		int x = read();
		if(!b[x]){
			a[++m] = x;
		}
		b[x]++;
	}
	sort(a + 1, a + m + 1);
	if(b[a[1]] != (n + 1) % 2 + 1){
		write(0);
		return 0;
	}
	for(int i = 2; i <= m; i++){
		if(b[a[i]] != 2){
			write(0);
			return 0;
		}
		if(a[i] - a[i - 1] != 2){
			write(0);
			return 0;
		}
	}
	write(qpow(2, n / 2));
}
```


---

## 作者：fanfansann (赞：0)

**Lining Up**（[AtCoder 2271](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/2271)） 

有 $n$ 个人站一行，对于第 $i$ 个人，给出第 $i$ 个人站在其两端的人数的差值 `a[i]`，问一共有多少种可能的站法。若不存在这样的排列方法，输出 `0 `。

**Solution**

由于我们仅有的信息是 $n$ 的值，和 $a_i$ 所以我们考虑对 $n$ 进行讨论。

对 $n$ 进行奇偶讨论：

- 当 $n$ 为奇数时：中间的人的左右的人的个数一定相同，因此 $a_i$ 为 $0$ 且只有 $1$ 个，从其向两边延伸，每延伸 $1$ 个人，差的人数 $a_i+2$ ，因此在奇数情况下，只有 $0,2,4,6,8...$ 。也就是，除 $0$ 有 $1$ 个外，其余均为 $2$ 个人。

- 当 $n$ 为偶数时：一定没有两边差值  $a_i$  为 $0$ 的情况，其两边的差最小为 $1$，从其两边延伸，每延伸 $1$ 个人，差的人数 $a_i+2$ ，因此在偶数的情况下，只有 $1,3,5,7...$，均为 $2$ 个。

综上所述，除了奇数情况时差值  $a_i$ 为 $0$ 的在中间外，其余的每个位置有两个人可选（就是 $a_i$ 相同的两个人位置可以交换），因此根据乘法原理，答案为 $2^{\frac{n}{2}}$ 。

至于无解的情况，根据上述分析，我们可以开一个桶，记录每个数的个数，如果不满足上面分析的 奇数情况的 $0,2,4,6,8...$ 除 $0$ 有 $1$ 个外，其余均为 $2$ 个人，或者偶数情况的 $1,3,5,7...$，且均为 $2$ 个即为无解输出 `0`。

**Code**

```cpp
typedef long long ll;
typedef int itn;
const int N = 500007, M = 5000007, INF = 0x3f3f3f3f, mod = 1e9 + 7;
const ll LINF = 4e18 +7;
int n, m;
ll a[N];
int vis[N];
int qpow(int a, int b);
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
        vis[a[i]] ++ ;
    }
    bool flag = true;
    if(n & 1) {
        if(vis[0] == 0) 
            flag = false;
        for(int i = 2; i <= n; i += 2) //奇数一定是 2,4,6,8... 且一定都是两个才对称
            if(vis[i] != 2) {
                flag = false;
                break;
            }
    }
    else {
        for(int i = 1; i <= n - 1; i += 2) //偶数一定是 1,3,5,7... 且一定都是两个才对称
            if(vis[i] != 2) {
                flag = 0;
                break;
            }
    }
    ll res = qpow(2, n / 2);
    if(flag) 
        printf("%lld\n", res);
    else puts("0");
    return 0;
}
```



---

## 作者：きりと (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT2271)

### 题目大意

有$n$个人排成一列，现给出排在每个人左右两边的人数差的绝对值$a[i]$，问有多少种排队情况。

### 解题思路

利用数形结合的思想，建立数轴，$n$个人即为数轴上的$n$个点，考虑$a[i]$的正负性，不难得出：从中间点开始，必有人两两关于中间点对称，它们的$a[i]$相等。

进一步得出：数组$a$中的$a[i]$必然两两相等，除非$a[i]=0$若有不符合的情况，直接输出$0$。

最终可能的情况数也就是$2^r$($r$为数组$a$中两两相等的数的对数)，因为没有一对就有两种情况，利用乘法原理求解即可

### 代码实现

核心算法：开个桶，直接算

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int num[100010];
const int mod=1e9+7;
signed main()
{
	int n,a,maxn=-1;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		num[a]++;
		maxn=max(a,maxn);
	}
	if(num[0]>1)
	{
		cout<<0<<endl;;
		return 0;
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(num[i]&&num[i]!=2)
		{
			cout<<0<<endl;
			return 0;
		}
		if(num[i])
		{
			ans++;
		}
	}
	int s=1;
	while(ans--)
	{
		s*=2;
		s%=mod;
	}
	cout<<(s+mod)%mod<<endl;
	return 0;
}
```


---

