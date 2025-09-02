# Journey

## 题目描述

Monocarp 决定去进行一次漫长的徒步旅行。

他计划，第一天走 $a$ 公里，第二天走 $b$ 公里，第三天走 $c$ 公里，到第四天再像第一天那样走 $a$ 公里，第五天如同第二天走 $b$ 公里，第六天则重复第三天走 $c$ 公里，如此循环下去。

当他走过的总路程达到至少 $n$ 公里时，就完成了整个旅程。你的任务是找出 Monocarp 在哪一天达到了这个目标。

## 说明/提示

在第一个例子中，Monocarp 在前四天总共走了 $1 + 5 + 3 + 1 = 10$ 公里。到了第五天，他又走了 $5$ 公里，总数达到 $15$ 公里。因为 $n = 12$，所以 Monocarp 在第五天实现了目标，完成了旅程。

在第二个例子中，Monocarp 第一天就走了 $6$ 公里。而由于 $n = 6$，他实际上一天就完成了旅程。

在第三个例子中，Monocarp 在六天内的总行程为 $3 + 4 + 1 + 3 + 4 + 1 = 16$ 公里。因为 $n = 16$，所以他在第六天达成旅程目标。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
12 1 5 3
6 6 7 4
16 3 4 1
1000000000 1 1 1```

### 输出

```
5
1
6
1000000000```

# 题解

## 作者：OIerWu_829 (赞：3)

[洛谷传送门](https://www.luogu.com.cn/problem/CF2051B) / [Codeforces 传送门](https://codeforces.com/contest/2051/problem/B)

我们首先用 $d$ 算出 Monocarp 每 $3$ 天也就是每一个周期所走的总距离 $a+b+c$；然后用 $e$ 计算目标距离 $n$ 所需的完整周期数，这里用 $(n+d-1)\div d$ 来算，相当于向上取整；然后用 $f$ 算出在 $e$ 个完整周期内 Monocarp 可以走的总距离 $d\times e$。

如果 $f>n$，说明在 $e$ 个周期中 Monocarp 已经超过了目标距离，因此需要减去完整周期数 $e$，以及相应地减去一个周期的距离 $d$，以便我们找到实际的距离 $f$。因为每个周期有 $3$ 天，所以答案的初始值是 $d\times 3$，然后我们处理剩余的天数，如果 $f<n$，则需要进一步判断 Monocarp 还需要多少天，具体步骤如下：

+ 如果加上第一天的 $a$ 之后就能达到目标 $n$，则增加 $1$ 天；
+ 如果加上第一天的 $a$ 和第二天的 $b$ 之后就能达到目标 $n$，则增加 $2$ 天；
+ 否则，增加 $3$ 天。

最后输出答案。

```cpp
#include <iostream>
using namespace std;

typedef long long LL;

int main()
{
	LL T;
	cin >> T;
	while (T--)
	{
		LL n, a, b, c;
		cin >> n >> a >> b >> c;
		LL d = a + b + c, e = (n + cd - 1) / d, f = e * d;
		if (f > n) e--, f -= d;
		LL ans = e * 3LL;
		if (f < n)
		{
			if (f + a >= n) ans++;
			else if (f + a + b >= n) ans += 2;
			else ans += 3;
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：JimmyQ (赞：2)

# CF2051B Journey
## 思路
先计算 $a,b,c$  都一定会走的次数，也就是 $n/(a+b+c)$，记结果 $num$，为然后再一个一个枚举：

- 剩下的 $n=0$：答案为 $num\cdot3$
- 剩下的 $n\le a$：答案为 $num\cdot3+1$
- 剩下的 $a\lt n\le a+b$：答案为 $num\cdot3+2$
- 剩下的 $a+b\lt n$：答案为 $num\cdot3+3$
## AC 代码
```
#include<bits/stdc++.h>
using namespace std;
long long t,n,a,b,c;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>a>>b>>c;
		long long num=n/(a+b+c);
		n-=num*(a+b+c);
		if(n==0) cout<<num*3<<endl;
		else if(a>=n) cout<<num*3+1<<endl;
		else if(a+b>=n) cout<<num*3+2<<endl;
		else cout<<num*3+3<<endl;
	}
	return 0;
} 
```
[AC 记录](https://codeforces.com/contest/2051/submission/297823821)

---

## 作者：_colin1112_ (赞：1)

## 思路

注意到 $n \leq 10^9$，于是考虑批量处理。

因为是 $3$ 次一循环，所以只需按照 $3$ 天处理一次，最后 $3$ 天会走多的部分特殊处理即可。

令剩余部分为 $k$。

1. $k$ 只需 $1$ 天即可走完（$k \leq a$）：天数加一；
2. $k$ 只需 $2$ 天即可走完（$k \leq a + b$）：天数加二；
3. $k$ 只需 $3$ 天即可走完（$k \leq a + b + c$）：天数加三。

最后输出 $3$ 天循环总数乘三再加上特殊处理的天数即可。

时间复杂度：$O(1)$。

## Code

```c++
#include <bits/stdc++.h>
#define endl '\n'
#define ll long long

#define PII pair<ll, ll>
#define x first
#define y second

using namespace std;
const int E = 1e6 + 5;
ll t, n, a, b, c, cnt;
inline void solve()
{
    cnt++;
    // cout << cnt << endl;
    cin >> n >> a >> b >> c;
    ll x = a + b + c;
    ll s = n / x;
    cerr << s << endl;
    if (n - s * x == 0)
        cout << s * 3 << endl;
    else
    {
        ll k = n - s * x;
        cerr << k << ' ' << s << endl;
        if (k <= a)
            cout << s * 3 + 1 << endl;
        else if (k <= a + b)
            cout << s * 3 + 2 << endl;
        else
            cout << s * 3 + 3 << endl;
    }
}
int main()
{
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：liuzhengtao (赞：1)

## 题目大意
Monocarp 决定徒步旅行。并且第一天他走 $a$ 公里，第二天他走 $b$ 公里，第三天他走 $c$ 公里，第四天也是 $a$ 公里，第五天 $b$ 公里，第六天 $c$ 公里，以此类推，一直循环下去。

而最终的问题是 Monocarp 会在走了至少 $n$ 公里的时候完成他的旅行。求他完成旅行的那一天是哪一天。
## 思路
这道题的做法是十分显然的，因为题意已经告诉我们了这是一个周期性问题，我们只用知道他走过了几个周期后剩下了多少公里，然后在判断剩下的路程是在哪一段范围，判断一下即可。具体实施代码已指出。
## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,b,c;	 
int main()
{
	cin>>T;
	while(T--)	
	{
		cin>>n>>a>>b>>c;
		int sum=a+b+c;
		int zq=n/sum*3/*大家一定注意不是(sum*x)*/,yu=n%sum;	
		// q是周期数，w是剩下的公里数。 
		if(yu==0) 
		{
			cout<<zq<<endl;//如果整除，直接输出 
		}
		else if(yu<=a) 
		{
			cout<<zq+1<<endl;//接下来的第一天内即可走完 
		}
		else if(yu<=a+b) 
		{
			cout<<zq+2<<endl;//接下来的第二天内即可走完
		}
		else cout<<zq+3<<endl;//剩下的情况 
	}
	return 0;
}
```

---

## 作者：alan1118 (赞：1)

## 题意
给你三个数 $a,b,c$。请你按照 $a,b,c,a,b,c,a,\dots$ 的顺序求和，请问加到第几个数的时候和会 $\geq n$。

## 思路
就是一个简单的周期问题，先把完整的周期算出来，再把最后剩下的部分按 $>0,>a,>a+b$ 处理一下就可以了，不懂的可以看代码。

## Code
``` cpp
#include <iostream>
using namespace std;
 
int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		int a, b, c;
		cin >> a >> b >> c;
		int d = n / (a+b+c) * 3;
		int q = n % (a+b+c);
		if(q > 0) d++;
		if(q > a) d++;
		if(q > a+b) d++;
		cout << d << endl;
	}
	return 0;
}
```

---

## 作者：Zhang_Shao_ (赞：0)

### 题意
三天划分为一组，第一天走 $a$ 千米，第二天走 $b$ 千米，第三天走 $c$ 千米。问多少天能走 $n$ 千米。
### 思路
将 $n$ 拆成 $(a+b+c)k+t$ 其中 $t<a+b+c$。当走了 $3k$ 天时，一共走了 $(a+b+c)k$ 千米。接下来分类讨论。如果 $t=0$，那么不用再走了；如果 $t \le a$，那么还需再走 $1$ 天；如果 $a < t \le a+b $，那么还需再走 $2$ 天；否则还需再走 $3$ 天。
### 代码
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,a,b,c,ans=0;
		scanf("%d%d%d%d",&n,&a,&b,&c);
		ans+=n/(a+b+c)*3,n%=(a+b+c);//拆分目标距离
		if(n==0){//分类讨论
			printf("%d\n",ans);
			continue;
		}
		if(a>=n){
			printf("%d\n",ans+1);
			continue;
		}
		if(a+b<n) printf("%d\n",ans+3);
		else printf("%d\n",ans+2);
	}
	return 0;//结束
}
```

---

## 作者：Weizhuohao114514 (赞：0)

这道题是一道周期问题，以三天为一个周期。如果暴力枚举会超时，所以要用数学方法。先判断是否有余数，如果没有，直接输出，有的话就三天挨个判断。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,c,t,x,y;
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld%lld%lld",&n,&a,&b,&c);
		x=n/(a+b+c)*3;
		y=n%(a+b+c);
		if(y==0) printf("%lld\n",x);
		else if((a+b+c)*(n/(a+b+c))+a>=n) printf("%lld\n",x+1);
		else if((a+b+c)*(n/(a+b+c))+a+b>=n) printf("%lld\n",x+2);
		else printf("%lld\n",x+3);
	}
	return 0;
}
```

---

## 作者：Lfz312g (赞：0)

# Solution
##  题目分析
小学奥数题。  
由于 $n$ 的数量级达到了 $10^9$ 显然无法进行一天天的模拟。   
考虑到由于每天走的路程三天一重复，所以我们可以把三天看作一个整体，剩下的以此判断即可。  
单组时间复杂度：$O(1)$。
## 代码实现

```cpp
#include <bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long ll;
const int Maxn=1e5+27,mod=1e9+7;
int a[105],b[105];
void solve() {
	ll n,a,b,c;
	cin>>n>>a>>b>>c;
	ll ans=0;
	ans+=(n/(a+b+c))*3;
	n-=(ans/3)*(a+b+c);
	if (n==0) cout<<ans<<'\n',n=mod;
	if (n>a) n-=a;
	else cout<<ans+1<<'\n',n=mod;
	if (n>b) n-=b;
	else cout<<ans+2<<'\n',n=mod;
	if (n>c) n-=c;
	else cout<<ans+3<<'\n';
}
int main()
{
	int T;
	cin>>T;
	while (T--) solve();
}
```

---

## 作者：huanglihuan (赞：0)

### Solution
因为 $n\le10^9$，暴力肯定不行，发现三天为一个周期，因此判断出现了几个整周期，再加上多的几天就是答案。
### 代码：

```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 988444333
#define MOD 1000000007
using namespace std;
const int N = 2e6 + 5,maxn = 5e3 + 5;
int a [maxn] [maxn];
map <int,int> mp;
inline int read ()
{
	int x = 0;
	bool f = 1;
	char c = getchar ();
	while (c < '0' || c > '9') f = (c == '-' ? !f : f),c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return (f ? x : -x);
}
inline void write (int x)
{
	if (x < 0) putchar ('-'),x = -x;
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
	return ;
}
signed main ()
{
	int T;
	cin >> T;
	while (T --)
	{
		int n,a,b,c;
		cin >> n >> a >> b >> c;
		int q = n / (a + b + c);
		int r = n % (a + b + c);
		q *= 3;
		if (r == 0) cout << q;
		else if (r <= a) cout << q + 1;
		else if (r <= a + b) cout << q + 2;
		else cout << q + 3;
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Chbin (赞：0)

[题面](https://www.luogu.com.cn/problem/CF2051B)

其实这题就是一个周期问题。Monocarp 第一天走 $a$ 公里，第二天走 $b$ 公里，第三天走 $c$ 公里，第四天又走 $a$ 公里，第五天又走 $b$ 公里，第六天又走 $c$ 公里，第七天又走 $a$ 公里......所以我们可以看出，在这个问题中，$3$ 天是一个周期， Monocarp 会一直循环往复地走下去。如果直接暴力枚举：
```cpp
    cin>>n>>a[1]>>a[2]>>a[0];//输入
		int d=0,l=0;
		while(l<n)//枚举
			d++,d%=3,l+=a[d];
		cout<<d<<endl;
```
你会惊奇地发现：你连测试样例都过不去，因为这段代码的时间复杂度是 $O(t\times n)$，且 $1 \le n \le 10^9$，百分百会超时。

这时我们可以发现：Monocarp 在一个周期（$3$ 天）内走过的公里数是相同的。也就是说：他第一到第三天走过的公里数为 $a+b+c$，第四到第六天走过的公里数也是 $a+b+c$，第七到第九天走过的公里数也是 $a+b+c$，以此类推。

所以我们只需求出他应走过几个完整的周期后，判断剩下的公里数走了几天，最后相加并输出即可，这样子也让时间复杂度变成了 $O(t)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[4],n;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n>>a[1]>>a[2]>>a[3];
		int d=0;
		d=n/(a[1]+a[2]+a[3])*3,n=n%(a[1]+a[2]+a[3]);//计算应走过几个完整的周期
		if(n!=0)//判断剩下的公里数走了几天，没有剩余就不判断
		{		
			if(n<=a[1]) d+=1;
			else if(n<=a[1]+a[2]) d+=2;
			else if(n<=a[1]+a[2]+a[3]) d+=3;
		}
		cout<<d<<endl;
	}
	return 0;
}
```

---

## 作者：MingRi_Doctor (赞：0)

## 思路：
这是一道周期问题。

我们只需要算出一个周期走的公里数和余下的公里数，接着一个一个判断即可。

- 如果是整周期，直接输出：周期数 $\times3$。因为每个周期都有三天。
- 如果多走 $1$ 天可以完成，输出：周期数 $\times 3 + 1$。
- 如果多走 $2$ 天可以完成，输出：周期数 $\times 3 + 2$。
- 如果多走 $3$ 天可以完成，输出：周期数 $\times 3+ 3$。
## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,b,c;
int main(){
	cin>>t;
	for(int i=0;i<t;i++)
	{
		cin>>n>>a>>b>>c;
		int x,y;
		x=n/(a+b+c);
		y=n%(a+b+c);
		if(y==0) cout<<x*3<<endl;//刚好x个周期，就是x*3天
		else if(y<=a) cout<<x*3+1<<endl;//x个周期多1天，就是x*3+1天
		else if(y<=a+b) cout<<x*3+2<<endl;//x个周期多2天，就是x*3+2天
		else cout<<x*3+3<<endl;//x个周期多3天，就是x*3+3天
	}
    
    return 0;
} 
```

---

## 作者：luoYiCheng_PrOI (赞：0)

### 分析
此题的 $t\le10^4;n\le10^9;a,b,c\le10^6$，此时可以 $O(t)$ 模拟求解答案。

### 解题方法
1. 用 $d$ 算出 Monocarp 每 $3$ 天也就是每一个周期所走的总距离 $a+b+c$；
   
3. 用 $e$ 计算目标距离 $n$ 所需的完整周期数，这里用 $(n+d-1)\div d$ 来算，相当于向上取整；

   
5. 用 $f$ 算出在 $e$ 个完整周期内 Monocarp 可以走的总距离 $d\times e$

7. 如果 $f>n$，说明在 $e$ 个周期中 Monocarp 已经超过了目标距离，因此需要减去完整周期数 $e$，以及相应地减去一个周期的距离 $d$，以便我们找到实际的距离 $f$;


9. 因为每个周期有 $3$ 天，所以答案的初始值是 $d\times 3$;

    
11. 然后我们处理剩余的天数，如果 $f<n$，则需要进一步判断 Monocarp 还需要多少天，具体步骤如下:
+ 如果加上第一天的 $a$ 之后就能达到目标 $n$，则增加 $1$ 天；
+ 如果加上第一天的 $a$ 和第二天的 $b$ 之后就能达到目标 $n$，则增加 $2$ 天；
+ 否则，增加 $3$ 天。

### 总结
最终代码时间复杂度 $O(t)$。

---

## 作者：GeYang (赞：0)

# 题意

给你三个数和一个目标数，按顺序依次累加这三个数，求达到目标数的时间。

# 思路

周期问题，先将这三个数加起来，用目标数除以这个和，若整除，直接输出商与三的乘积。

如果没有整除怎么办？

先取余数部分，用这三个数枚举，即先加第一个数，再加上第二个数，以此类推。枚举次数不会超过三，因为余数小于除数。

当某一刻，这个和大于余数时，记录。

全部相加并输出即可，记得商要乘三。

---

## 作者：dreamhzz (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF2051B)
## 题目大意
Monocarp 决定踏上漫长的徒步旅行。

第一天他走 $a$ 公里，第二天他走 $b$ 公里，第三天他走 $c$ 公里，第四天，就像第一天一样，走了 $a$ 公里，第五天，就像第二天一样，走了 $b$ 公里，第六天，就像第三天一样，走了 $c$ 公里，以此类推。

Monocarp 会在总共走了至少 $n$ 公里的时候完成他的旅行。你的任务是求他完成旅行的那一天是哪一天。
## 思路
通过看题我们可以发现，这其实就是一个周期问题。$a+b+c$ 公里，也就是三天为一周期。我们只需要求出 $n$ 中有几个周期，在判断剩下的公里数走了几天，最后相加。最后输出即可。
## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,b,c;	//定义 
int main(){
	cin>>t;
	while(t--)	//循环	
	{
		cin>>n>>a>>b>>c;
		int q=n/(a+b+c)*3,w=n%(a+b+c);	// q 为 n 中所拥有周期数，w为剩下的公里数。 
		if(w==0) cout<<q<<endl;//如果没有剩下的公里数，直接输出 
		else if(w==a) cout<<q+1<<endl;//只有a的情况 
		else if(w==a+b) cout<<q+2<<endl;//有a、b的情况 
	}
	return 0;
} 
```

---

## 作者：songhongying (赞：0)

## 题目大意

Monocarp 决定踏上漫长的徒步旅行。

他决定第一天他走 $a$ 公里，第二天他走 $b$ 公里，第三天他走 $c$ 公里，第四天，就像第一天一样，他走 $a$ 公里，第五天，就像第二天一样，他走 $b$ 公里， 第六天，就像第三天一样，他会走 $c$ 公里，依此类推。

Monocarp 将在他总共至少走了 $n$ 公里的那一天完成他的旅程。你的任务是确定 Monocarp 完成他的旅程的那一天。

## 解题思路：

观看 Monocarp 每天走的路程，就可以发现这是一个周期问题，每三天为一周期，重复往返下去，每三天走的路程为 $a + b + c$。接着先判断整周期有几天，再将剩余的公里数进行判断，找出在第几天能完成这个任务，最后输出即可。

## Code:


```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a, b, c;
int main(){
	
	cin >> t;
	while (t--) {
		cin >> n >> a >> b >> c;
		int q = n / (a + b + c ) * 3, w = n % (a + b + c);
		if (w == 0)  cout << q << endl;
		else if (w <= a)  cout << q + 1 << endl;
		else if (w <= a + b)  cout << q + 2 << endl;
		else if (w <= a + b + c)  cout << q + 3 << endl;
	}
	
	return 0;
}
```

---

## 作者：programmer330 (赞：0)

# 题解：CF2051B Journey

## 题意简述

给予四个数 $n,a,b,c$，从 $0$ 开始依次循环加上 $a,b,c$，问何时可以达到 $n$。

## 思路分析

题目很简单。

先求出 $a,b,c$ 的和，然后求出循环组数，用 $n$ 减掉后对剩下的值进行**分类讨论**即可。

注意考虑**不等式的取等**和**循环的整除**情况。

## 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
signed main(){
	cin>>t;
	while(t--){
		int n,a,b,c;
		cin>>n>>a>>b>>c;
		int sum=a+b+c;
		int num=n/sum;
		n-=num*sum;
		int extra;
		if(n==0)extra=0;
		else{
			if(a>=n){
				extra=1;
			}else{
				if(a+b>=n){
					extra=2;
				}else{
					extra=3;
				}
			}	
		}
		cout<<extra+num*3<<endl;
	}
	return 0;
}

```

---

## 作者：DoubleQLzn (赞：0)

本题是典型的周期性问题。

我们可以使 $3$ 天为一个周期，每个周期可以走 $(a+b+c)$ 千米。拿 $n$ 除以 $(a+b+c)$ 向下取整 $3$ 即可得到完整的天数。接着并不是一个完整的周期的部分可以写 $3$ 个判断：

- 判断是否可以在第一天离开。
- 判断是否可以在第二天离开。
- 判断是否可以在第三天离开。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
 
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t,n;
	cin>>t;
	while(t--){
	int a,b,c;
	cin>>n>>a>>b>>c;
	int day=n/(a+b+c)*3;
	int need=n-n/(a+b+c)*(a+b+c);
    if(need==0)cout<<day<<'\n';
	else if(a>=need)cout<<day+1<<'\n';
	else if(a+b>=need)cout<<day+2<<'\n';
	else if(a+b+c>=need)cout<<day+3<<'\n';
	}
	return 0;

}
```

---

## 作者：沉石鱼惊旋 (赞：0)

# B. Journey

数据范围如此大考虑 $\mathcal O(1)$ 的**数学**做法。

先算出需要的周期个数是 $\lfloor\frac{n}{a+b+c}\rfloor$。则 $\lfloor\frac{n}{a+b+c}\rfloor\times 3$ 天是周期内的答案。之后考虑 $n\bmod (a+b+c)$ 也就是剩余路程的大小。自己模拟这个周期的跑步流程。

答案是 $\lfloor\frac{n}{a+b+c}\rfloor\times 3+[n\bmod (a+b+c)\gt 0]+[n\bmod (a+b+c)-a\gt 0]+[n\bmod (a+b+c)-a-b\gt 0]$。

<https://codeforces.com/contest/2051/submission/297815421>

---

## 作者：Tiger_Rory (赞：0)

周期问题。

我们令 $k = a+b+c$，则 $k$ 为一个周期，共三天。那么周期数量为 $\frac{n}{k}$，所需时间为 $\frac{3n}{k}$。我们注意到这可能会产生余数。但因为余数肯定小于 $k$，我们写三个判断语句看下需要再加几天即可。

代码实现如下。


```cpp
    #include<bits/stdc++.h>
    using namespace std;
    #define ll long long
    int t;   
    int main() {
    	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    	cin>>t;
    	while(t--){
    		ll n,a,b,c;
    		cin>>n>>a>>b>>c; 
    		ll kkk = n / (a + b + c); 
    		ll ans = kkk * 3; 
    		ll ys = n % (a + b + c); 
    		ll sum = 0;
    		if(ys==sum) {
    			cout<<ans<<endl; 
    		} 
    		else if(sum+a>=ys) {
    			cout<<ans+1<<endl; 
    		}else if(sum+a+b>=ys) {
    			cout<<ans+2<<endl; 
    		} else {
    			cout<<ans+3<<endl; 
    		} 
    	}
    	return 0;
    }
```
如有不足，还请指出。

---

## 作者：wuyouawa (赞：0)

### 题目大意

Monocarp 决定开始一场长途徒步旅行。

他决定第一天走 $a$ 公里，第二天走 $b$ 公里，第三天走 $c$ 公里，第四天就像第一天一样走 $a$ 公里，第五天就像第二天一样走 $b$ 公里，第六天就像第三天一样走 $c$ 公里，以此类推。

Monocarp 会在总共走了至少 $n$ 公里的时候完成他的旅行。你的任务是确定 Monocarp 完成旅行的那一天是哪一天。

### 思路

这题是个典型的周期问题。

周期很明显为 $3$ 天，一共走了 $a+b+c$ 公里，那么 $n$ 公里我们先计算一共有多少个整的周期，再算余下来的可否用一天走完，或两天，或三天，再把整周期的个数 $\times 3$ 再加余下来的用多少天走完。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a,b,c,h,e,f;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>a>>b>>c;
		h=a+b+c,e=n/h,f=n%h;//计算整的和余下的
		if(f==0)  cout<<e*3<<endl;
		else  if(a>=f)  cout<<e*3+1<<endl;//余下的一天走完
		else  if(a+b>=f)  cout<<e*3+2<<endl;//余下的两天走完
		else  cout<<e*3+3<<endl;//余下的三天走完
	}
	return 0;
}
```

---

