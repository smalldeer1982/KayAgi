# Almost All Divisors

## 题目描述

We guessed some integer number $ x $ . You are given a list of almost all its divisors. Almost all means that there are all divisors except $ 1 $ and $ x $  in the list.

Your task is to find the minimum possible integer $ x $ that can be the guessed number, or say that the input data is contradictory and it is impossible to find such number.

You have to answer $ t $ independent queries.

## 样例 #1

### 输入

```
2
8
8 2 12 6 4 24 16 3
1
2
```

### 输出

```
48
4
```

# 题解

## 作者：vеctorwyx (赞：4)

### 来一发代码相对简短且相对好理解的做法

方法：

条件 1. 排序并依次相乘结果回相等，都等于$x$（最小乘最大，次小乘次大），即$ a_1 * a_n =a_2*a_{n-1}=......=x$;

条件 2.  根据条件一求出$x$后，再求出$x$的因数个数，因数个数应等于$n-2$（易忽略，考点）；

求$x$因数个数的方法：枚举i=1~  $\sqrt{n}$ （去掉1和n）,如果n%i=0则ans+=2，
如果i=$\sqrt{n}$则ans++，最后比较ans是否等于n+2；（好像还有质因数分解的方法更快~~但我不会~~）

代码如下：

```
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define int long long//十年OI一场空，不开long long见祖宗
using namespace std;
long long t,n,a[5010];
bool flag;
signed main()
{
	cin>>t;
	while(t--)
	{
		flag=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		sort(a+1,a+1+n);//排序
		long long x=a[1]*a[n];//求x
		for(int i=2;i<=n/2+1;i++)//条件千万是i<=n/2+1！！！ 我改了半小时才发现。。。
		{
			if(a[i]*a[n-i+1]!=x)//无法组成x；
			{
				flag=1;
				break;
			}
		}
		if(flag)
		{
			cout<<-1<<endl;
			continue;
		}
		int ans=0;//记录x的因数个数
		for(int i=1;i*i<=x;i++)
		{
			if(i*i==x)
			ans++;
			else if(x%i==0)
			ans+=2;
		}
		if(ans-2!=n)//因数个数有误则输出-1
		{
			cout<<-1<<endl;
			continue;
		}
		else
		cout<<x<<endl;
	}
}
```


---

## 作者：piuke (赞：2)

~~辣鸡数学题……~~  
毒瘤猜结论题……

设这个数为$X$，如果这一串数是这个数的所有因子，那么把这串数从大到小排序后，就肯定满足这个关系式：
$$X=d_i*d_{n-i+1}$$

至于原因，因为$X$整除$d_i$，所以$X\div d_i$也在数组$d$中，若$d_i$从小到大排序，那么$X\div d_i$也就相当于从大到小排序了。

所以，排完序后，将$X$赋为$d_1*d_n$，然后对$X$这样检测一波……

~~好了这是个水题……~~

因为$t$组数据，每组数句中需要输入，一次对数组的排序（好像冒泡都能过），对生成的$X$进行一次检测，所以时间复杂度是$\Theta(t(n\log n+2*n))$，如果用冒泡的话，就是$\Theta(t(n^2+2*n))$。  
~~反正都能过就对了~~

附上~~罪恶的~~代码

```cpp
long long T, n, a[301];
long long ans;
map<int, bool> ap;
inline bool check(long long x) {
    for (int i = 2; i <= sqrt(x); i++)
        if (x % i == 0 && (!ap[i] || !ap[x / i]))
            return 0;
    return 1;
}
int main() {
    read(T);
    while (T--) {
        ap.clear();
        read(n);
        long long pr = 1e17, minnum = 1e17, maxnum = -1e17;
        for (int i = 1; i <= n; i++)
            read(a[i]), ap[a[i]] = 1;
        sort(a + 1, a + n + 1);
        ans = a[1] * a[n];
        if(!check(ans)) ans = -1;
        for(int i = 2; i < n; i++)
            if(a[i] * a[n - i + 1] != a[i - 1] * a[n - i + 2])
                ans = -1;
        write(ans, '\n');
    }
}
```

代码中的模板参见[这里](https://www.luogu.org/paste/ustzpmnv)

---

## 作者：Frozencode (赞：1)

不难看出，我们只要把d数组升序排序，设置两个指针，一个从前往后扫一个从后往前扫就可以验证存不存在这个数，但是问题来了，怎么验证所给因数恰好就是除了$1$和它本身之外的所有因数呢？不难想到$O(\sqrt{n})$的枚举，把所有因数和所给的数一一比较就行了。一个值得注意的地方是这里的$n$达到了$10^{12}$所以循环变量要开个$long long$。~~不然会T到飞起,别问我怎么知道的~~

上代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=5010;
const ll INF=2147483647;
ll t,n,a[maxn],l,r,tem,flag;
vector<ll>e;
bool check()
{
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=e[i-1])return false;
	}
	return true;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		flag=0;
		e.clear();
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);
		l=1;
		r=n;
		for(int i=1;i<=n;i++)
		{
			if(l>r)break;
			if(i==1)
			{
				tem=a[l]*a[r];
			}
			else
			{
				if(a[l]*a[r]!=tem)
				{
					flag=1;
					break;
				}
			}
			l++;
			r--;
		}
		if(!flag)
		{
			for(ll i=2;i*i<=tem;i++)
			{
				if(tem%i==0)
				{
					e.push_back(i);
					if(i*i!=tem)e.push_back(tem/i);
				}
			}
			sort(e.begin(),e.end());
			if(check())cout<<tem<<endl;
			else
			{
				cout<<"-1"<<endl;
			}
		}
		else
		{
			cout<<"-1"<<endl;
		}
	}
	return 0;
}
```


---

## 作者：Wander_E (赞：0)

由于因数是成对出现的，所以对于一个自然数 $x$ 他的因数如果按照升序排列它的因数得到序列 $k$ 那么 $k$ 中的每个数必然满足 $k_i\times k_{n-i+1}=x$。

于是就可以将数组 $a$ 排序并检测它是否满足上述性质。

本题的一个坑点在于对于 $x=a_i\times a_{n-i+1}$，$x$ 的因数可能**没有完全**被 $a$ 包含。所以再求得 $x$ 后还需再找一遍 $x$ 的因数，与 $a$ 中的每一项进行对比。

附上 AC 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
const int N = 1e6 + 5;
const int INF = 0x3f3f3f3f;
int n;
int a[N];
int T;

signed main()
{
	cin >> T;
	while(T--)
	{
		int cnt = 0;
		bool flag = 0;
		cin >> n;
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		sort(a + 1, a + n + 1);
		int ans = a[1] * a[n];
		for(int i = 2, j; i <= n / 2 + 1; i++)
		{
			if(a[i] * a[n - i + 1] != ans)
			{
				flag = 1;
				break;
			}
		}
		if(flag)
		{
			cout << -1 << endl;
			continue;
		}
		for(int i = 1; i <= sqrt(ans); i++)
		{
			if(ans % i == 0)
			{
				if(i == sqrt(ans)) cnt++;
				else cnt += 2; 
			}
		}
		if(cnt != n + 2)
		{
			cout << -1 << endl;
			continue;
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：两年打铁 (赞：0)

## 题目大意
有t组数据

每组数据有一个n以及n个数，让你进行猜数，使得这个这n个数是你猜的数除1和本身以外的所有因子。

如果能猜到，输出最小的，否则输出-1.



------------


因为因数包含了除本身和1以外的所有因子，而且因子只有两种情况
$$a_i*a_j=x$$
$$a_i*a_i=x$$
那么我们排个序，记录这些共同的积是否相同，不相同就输出-1.

这只是第一步

我们还要验证除1和本身的因子个数就等于n。
由唯一分解定理可知
$$x=p_1^{k1}*p_2^{k2}*...*p_m^{km}$$
因子个数即为
$$(k1+1)*(k2+1)*...*(km+1)$$
然后就是如果有一个大于1e6的因子，最多也只有一个，判掉就行了。
总复杂度

$O(t(nlog_2(n)+log(product)))$ 


```cpp
#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define int long long 
using namespace std;

inline void read(int &x)
{
	x=0;char ch=getchar();int pd=1;
	while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x*=pd;
}
inline void write(const int &x)
{
	char ggg[10001];int s=0;int tmp=x;
	if(tmp==0){putchar('0');return;}
	if(tmp<0){tmp=-tmp;putchar('-');}
	while(tmp>0){ggg[s++]=tmp%10+'0';tmp/=10;}
	while(s>0){putchar(ggg[--s]);}
}

int n,a[1001];
int p[1000010];
bool vis[1000010];
int d,ans;
int cnt;
void init()
{
	for(register int i=2;i<=1000000;++i)
	{
		if(!vis[i])
		{
			p[++cnt]=i;
		}
		for(register int j=1;j<=cnt&&i*p[j]<=1000000;++j)
		{
			vis[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
}
signed main()
{
	init();
	int T;
	read(T);
	while(T--)
	{
		read(n);
		for(register int i=1;i<=n;++i)
		{
			read(a[i]);
		}
		sort(a+1,a+n+1);
		int i=1,j=n;
		int ji=a[i]*a[j];
		while(i<=j)
		{
			if(a[i]*a[j]!=ji)
			{
				puts("-1");
				goto nt;
			}
			++i,--j;
		}
		d=ji;
		ans=1;
		for(register int i=1;i<=cnt&&p[i]<=ji;++i)
		{
			if(d%p[i]==0)
			{
				int k=0;
				while(d%p[i]==0)
				{
					k++;
					d/=p[i];
				}
				ans*=(k+1);
			}
		}
		if(d>1)ans*=2;
		if(ans-2==n)
		{
			write(ji);
			puts("");
		}
		else 
		{
			puts("-1");
		}
		nt:;
	}
}


---

