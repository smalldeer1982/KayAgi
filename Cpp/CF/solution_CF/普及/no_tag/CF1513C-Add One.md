# Add One

## 题目描述

You are given an integer $ n $ . You have to apply $ m $ operations to it.

In a single operation, you must replace every digit $ d $ of the number with the decimal representation of integer $ d + 1 $ . For example, $ 1912 $ becomes $ 21023 $ after applying the operation once.

You have to find the length of $ n $ after applying $ m $ operations. Since the answer can be very large, print it modulo $ 10^9+7 $ .

## 说明/提示

For the first test, $ 1912 $ becomes $ 21023 $ after $ 1 $ operation which is of length $ 5 $ .

For the second test, $ 5 $ becomes $ 21 $ after $ 6 $ operations which is of length $ 2 $ .

For the third test, $ 999 $ becomes $ 101010 $ after $ 1 $ operation which is of length $ 6 $ .

For the fourth test, $ 88 $ becomes $ 1010 $ after $ 2 $ operations which is of length $ 4 $ .

## 样例 #1

### 输入

```
5
1912 1
5 6
999 1
88 2
12 100```

### 输出

```
5
2
6
4
2115```

# 题解

## 作者：gaozitao1 (赞：8)

**题目大意**：一次操作是将这个数的每一位都加一。求将 $n$ 进行 $m$ 次操作后有几位。

这一道题如果暴力枚举，时间复杂度是 $O\left(mt\right)$ ，过不了这一道题。

仔细分析题目可以发现，每一次操作只对当前位数有影响，所以可以一位一位考虑。

可以发现，每一位本来都是一位数，如果变成两位数，那么一定是一个是 $1$，一个是 $0$。

这样，就可以只考虑对 $1$ 和 $0$ 进行操作了。

所以，这有一个递推的性质，可以使用 DP 解决。

用 $d_{i,j}$ 表示当前位置的数是 $i$，经过 $j$ 次操作之后的数的位数。

如果 $i+j<10$，那么操作之后还是一位。

如果 $i+j\ge10$，那么操作之后就变成了两位，一位是 $1$，一位是 $0$，而从 $i$ 到 $10$ 需要 $10-i$ 步，还剩 $i+j-10$ 步。

所以，就有一个 DP 方程：

如果 $i+j<10$ ，那么 $d_{i,j}=1$ 。

如果 $i+j\ge10$ ，那么 $d_{i,j}=d_{0,i+j-10}+d_{1,i+j-10}$。

还有一些细节。

1. 要开 long long。

2. DP 时先枚举 $j$ 再枚举 $i$ 。否则转移时 $d_{0,i+j-10}$ 和 $d_{1,i+j-10}$ 可能没有初始化。

**代码：**
```cpp
#include<cstdio>
#include<iostream>
long long d[10][200001];
//注意开long long
//d[i][j]表示这一位是i，操作j次后的位数
int main()
{
	int i,j,m,n,t;
	long long a;//注意开long long
	for(j=0; j<200001; ++j)
	//从0开始枚举
	//先枚举j防止d[0][i+j-10]和d[1][i+j-10]没有被初始化
	{
		for(i=0; i<10; ++i)
		//从0开始枚举
		{
			if(i+j>9)
				d[i][j]=(d[0][i+j-10]+d[1][i+j-10])%1000000007;
			else
				d[i][j]=1;
		}
	}
	scanf("%d",&t);
	while(t--)
	{
		a=0;
		scanf("%d%d",&n,&m);
		while(n)
		{
			a=(a+d[n%10][m])%1000000007;
			n/=10;
		}
		printf("%lld\n",a);
	}
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：7)

作业里的水题。

------------

一开始打算直接记搜，然后写挂了。、

于是考虑 $10$ 这个特殊数字，其他数由一位变成两位后第一个数就是 $10$。

所以先将 $10$ 修改 $i$ 次后的位数打表出来，询问直接查表就行。

考虑如何打表。

将 $10$ 拆成两位 $1$ 和 $0$，而他俩分别需要修改 $9$ 和 $10$ 次就会变成 $10$。

若用 $f_i$ 表示 $10$ 修改 $i$ 次后的位数，则用 $f_{i-9}+f_{i-10}$ 更新 $f_i$。

记得取模。

------------

记搜改的代码，所以有点奇怪。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=2e5+84,mod=1e9+7;
ll T,m,len,ans,f[maxn];
string s;
bitset<maxn> vis;
inline ll dfs(ll x,ll c){//没改的函数名
    if(x+c<10)
        return 1;
    if(x==10)
        return f[c];
    return dfs(10,c-(10-x));
}
int main(){
    scanf("%lld",&T);
    for(ll i=0;i<9;i++)
        f[i]=2;
    f[9]=3;
    for(ll i=10;i<=2e5;i++)
        f[i]=(f[i-9]+f[i-10])%mod;
    while(T--){
        cin>>s;
        scanf("%lld",&m);
        ans=0;
        len=s.size();
        for(ll i=0;i<len;i++)
            ans=(ans+dfs(s[i]-'0',m))%mod;
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：破壁少年 (赞：4)

# CF1513C Add One 题解
~~这道题是我们集训题，本蒟蒻交了 20 多发，突然发现模少了(悲)~~

题目大意：给你一个数 $n$，一个操作次数 $m$，每次把 $n$ 所有位上的数 $+1$，注意不是一股脑地加，而是一次一次加，也就是新加的一位后续也会加，暴力 $O(m \times t)$，超时。

考虑 dp 预处理，$f_{i,j}$ 表示当前位为 $i$，修改了 $m$ 次的位数，预处理枚举修改 $j$ 次，当前位为 $i$，每次判断 $i+j$ 是否大于 $9$ 也就是是否进位，是的话 $f_{i,j}=f_{1,i+j-10}+f_{0,i+j-10}$，否则 $f_{i,j}=1$，这样复杂度常数级，预处理每次查询即可。

注：千万千万用快读或 cin 优化，本蒟蒻用的快读。

上 AC 代码，码风很丑，望谅解：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define naipaokuikui main
const long long mod=1e9+7;
long long f[15][400010];
inline void read(long long & a)
{
	int s=0,w=1;
	char ch=getchar();
	while (ch<'0'||ch>'9')
	{
		if (ch=='-')
			w=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9')
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	a=s*w;
}
int naipaokuikui(){
	
	for(int j=0;j<=400000;j++){ 
		for(int i=0;i<=9;i++){
			if(i+j<=9){
				f[i][j]=1;
			}
			else {
				f[i][j]=(f[1][i+j-10]%mod+f[0][i+j-10]%mod)%mod;
			}
		}
	}
	long long t;
	read(t);
	while(t--){
		long long ans=0;
		long long n,m;
		read(n);
		read(m);
	 	while(n){
	 		long long cnt=n%10;
	 		ans=((ans%mod)+f[cnt][m]%mod)%mod;
	 		n/=10;
		 }
		printf("%lld\n",ans);
	}
	return 0;
}




```



---

## 作者：Acfboy (赞：2)

> 把一个整数中每一个位都变为其加上一的数字， `9` 变为 `10`, 问变 $m$ 次后数字长度是多少。

可怜的孩子没看清数据范围，看成保证所有的 $m$ 和不超过 $2 \times 10^5$, 以为这是一个简单 dp, $f[i][j]$ 表示 $i$ 次后 $j$ 出现了几次，那么很容易想出转移 $f[i][j] = f[i-1][j-1](i \ge2), f[i][0] = f[i-1][9], f[i][1] = f[i-1][0] + f[i-1][9]$ 最后 $\sum f[m][j]$ 就是答案，然后顺利 T 飞。

不过这样的 DP 还有没有救呢？枚举几个小样例发现每个数都是独立变化的，既然独立变化，那么分开考虑，发现一个数字为 $d$ 的位在 $10-d$ 次后不管怎样都变成 `10` 继续变换了，那么只要能快速处理出 `10` 的变化就可以快速得出所有的变化。

一开始我一直想着有啥数学方法可做，后来一看，直接预处理一遍把所有次数以后的变换处理完不就得了。

```cpp
#include <cstdio>
#include <cstring>
#define int long long
const int p = 1000000007;
int T, x, m, f[200005][10];
int get(int x) {
    if(x < 0) return 1;
    int an = 0;
    for(int i = 0; i <= 9; i++) an = (an + f[x][i]) % p;
    return an;
}
signed main() {
    scanf("%lld", &T);
    f[0][1] = f[0][0] = 1;
    for(int i = 1; i <= 200000; i++) {
        for(int j = 9; j >= 1; j--) f[i][j] = f[i-1][j-1];
        f[i][0] = 0;
        f[i][0] = (f[i][0] + f[i-1][9]) % p;
        f[i][1] = (f[i][1] + f[i-1][9]) % p;
    }
    while(T--) {
        scanf("%lld%lld", &x, &m);
        int ans = 0;
        while(x) {
            int d = x % 10;
            ans = (ans + get(m - (10-d))) % p;
            x /= 10;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：Mophie (赞：1)

首先很显然每一位上的数都不互相影响。

所以只需要拆位考虑即可。

设 $dp[i][j]$ 表示这位为 $i$ ，跳 $j$ 次时能弄出来的位数。

那么转移方程比较显然，因为每次加，加到 $10$ 就会再多一位，所以可以得到下面的式子：

$$dp[i][j]=dp[0][j+i-10]+dp[1][j+i-10]$$

然后初始化将不可能分位的状态设为 $1$ 即可。

```cpp
//红太阳zhouakngyang txdy!
#include<bits/stdc++.h>
using namespace std;
//#define int long long
inline int read()
{
	int sum=0,nega=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')nega=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')sum=sum*10+ch-'0',ch=getchar();
	return sum*nega;
}
const int mod=1e9+7;
int taxi,n,m;
long long ans,dp[13][200009];
int main()
{
	for(int i=0;i<=9;i++)dp[i][0]=1;
	for(int i=1;i<=200000;i++)
		for(int j=0;j<=9;j++)
			if(i+j>=10)dp[j][i]=(dp[1][i+j-10]+dp[0][i+j-10])%mod;
			else dp[j][i]=1;
	taxi=read();
	for(int ttt=1;ttt<=taxi;ttt++)
	{
		ans=0;
		n=read();m=read();
		while(n!=0)
		{
			ans=ans+dp[n%10][m];ans=ans%mod;
			n=n/10;
		}
		printf("%lld\n",ans);
	}
	return 0;
}


```


---

## 作者：Phoenix114514 (赞：0)

# CF1513C Add One
## 思路
由题目中的 $93$ 会在操作后变成 $104$ 可知，**对于每一位的操作是不会影响下一数位**，于是我们考虑 $10$ 这个数，$0 \sim 9$ 经过若干次操作后都会变成 $10$。于是我们设 $dp_i$ 表示 $10$ 经历过 $i$ 次操作后的位数模 $mod$ 的结果，则：
$$
dp_i=\begin{cases}
2 & i < 9 \\
3 & i = 9\\
dp_{i-9}+dp{i-10} \bmod 10^9+7 & i > 9
\end{cases}
$$

然后对于每一次输入数的每一位，设函数 $cal(x,y)$ 表示 $x$ 经过 $y$ 次操作后的位数，则对于每一次调用，有：
$$
cal(x,y)=\begin{cases}
1 & x+y<10 \\
dp_y & x=10 \\
cal(10,y-10+x) & default 
\end{cases}
$$
最后将答案累加，每一次取模即可。
## Code
```cpp
#include<bits/stdc++.h>
#include<bits/stl_algo.h>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define int long long
#define ull unsigned long long
#define ui unsigned int
const int mod=1e9+7;
const int M=2e5+5;
int t,m,dp[M];
string s;
int cal(int num,int cnt){
    if (num+cnt<10)return 1;
    else if (num==10)return dp[cnt];
    return cal(10,cnt-(10-num));
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>t;
    auto begin_=chrono::high_resolution_clock::now();
    for(int i=0;i<9;i++)dp[i]=2;
    dp[9]=3;
    for(int i=10;i<=2e5;i++)dp[i]=(dp[i-9]+dp[i-10])%mod;
    while(t--){
        cin>>s>>m;
        int ans=0;
        for (int i=0;i<s.size();i++){
            ans+=cal(s[i]-'0',m);
            ans%=mod;
        }
        cout<<ans<<endl;
    }
    auto end_=chrono::high_resolution_clock::now();
    cerr<<chrono::duration_cast<chrono::milliseconds>(end_-begin_).count()<<"ms"<<endl;
    return 0;
}

```

---

## 作者：TainityAnle (赞：0)

第一点注意：当 $9$ 变为 $10$ 的时候是直接多出来一位，而不是进一位，这里翻译没有注意到这一点，但原题面中体现了。

既然如此，我们可以把每一位都拆分开，即把每一位都当成一个独立的数，最后计算每一位的答案总和即可。

对于每一位考虑的话，就只有 $0\sim9$ 这 $10$ 种情况，只需要对这 $10$ 个数变换所有次数预处理下来即可。

容易发现，如果初始数字 $x$ 加上变换次数 $k$ 小于 $10$ 则不会进位。进位后，由 $9$ 变成 $10$，需要加上 $1$ 变换 $k-10$ 次和 $0$ 变换 $k-10$ 次的答案和。

这样的话就像一个动态规划问题了，设 $f_{i,j}$ 表示 $i$ 变换 $j$ 次后的位数，则状态转移方程为：

$$
f_{i,j} = \begin{cases} 1 & i+j\le9\\ f_{0,i+j-10}+f_{1,i+j-10} & i+j\ge10 \end{cases}
$$

$i\in[0,9]$，$j\in[0,2\times10^5]$，枚举即可。

[AC Code](https://codeforces.com/problemset/submission/1513/297375800)

---

## 作者：wmrqwq (赞：0)

duel 到的。

# 题目链接

[CF1513C Add One (luogu)](https://www.luogu.com.cn/problem/CF1513C)

[CF1513C Add One (codeforces)](https://codeforces.com/problemset/problem/1513/C)

# 解题思路

我们发现，初始数列中的每个数字变为 $10$ 必定只需要**至多** $10$ 次，于是我们可以直接预处理出 $10$ 这个数字经过 $i$ 次变化后能形成多少位的数字即可。

状态为 $dp_{i,j}$ 表示 $10$ 这个数字经过 $i$ 次操作后所得到的数字中含有多少个值为 $j$ 的数字。

转移显然。

按照这样的思路预处理即可。

# 参考代码

```cpp
/*
Tips:

你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);init();
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll t;
ll n,m;
string s;
ll mod=1e9+7;
ll dp[200010][10],sum[200010],ans;
void _clear(){}
void solve()
{
	_clear();
	cin>>s>>m;
	s=' '+s;
	forl(i,1,(ll)s.size()-1)
	{
		if('9'+1-s[i]<=m)
			ans+=sum[m-('9'+1-s[i])];
		else
			ans++;
		ans%=mod;
	}
	cout<<ans<<endl;
	ans=0;
}
void init()
{
	dp[0][0]=1,dp[0][1]=1;
	sum[0]=2;
	forl(i,1,2e5+5)
	{
		forl(j,0,8)
			dp[i][j+1]+=dp[i-1][j],dp[i][j+1]%=mod;
		dp[i][0]+=dp[i-1][9];
		dp[i][1]+=dp[i-1][9];
		dp[i][0]%=mod;
		dp[i][1]%=mod;
		forl(j,0,9)
			sum[i]+=dp[i][j],sum[i]%=mod;
	}
}
int main()
{
	IOS;
	t=1;
 	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：mouseboy (赞：0)

#### 一道递推

由于对于一个数 $x$ ,可得 $x+10-x=10$ ~~（废话）~~ 于是问题就变成了 $0+m$ 次,然后 $x+m$ 就变成 $0+x+m$ ~~（还是废话）~~ 于是可以写一个递推。

首先对于函数 $f(m)$ 可分为 $m\le 9$ 和 $m>9$ ,然后可得出递推式结果为 $1$ 或 $f(m-9)+f(m-10)$ ，所以我们可以直接求出结果再分解数位求值。

最后贴上代码
```cpp
#include <iostream>
using namespace std;

const int Maxn = 2e5 + 11, mod = 1e9 + 7;
int a[Maxn], n, m, t, cnt;//因为每次都%了，可不开long long
int main() {
  ios::sync_with_stdio(false);//必须优化（卡读入）
  cin.tie(0);
  for (int i = 0; i < Maxn; i++) {
    a[i] = i < 10 ? 1 : (a[i - 9] + a[i - 10]) % mod;//递归求值
  }
  for (cin >> t; t; t--) {
    cnt = 0;
    for (cin >> n >> m; n; n /= 10) {
      cnt = (cnt + a[n % 10 + m]) % mod;//分解数位计算
    }
    cout << cnt << '\n';
  }
  return 0;//华丽的结束
}
```

---

