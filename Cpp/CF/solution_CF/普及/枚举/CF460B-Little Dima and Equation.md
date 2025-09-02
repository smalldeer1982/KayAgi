# Little Dima and Equation

## 题目描述

Little Dima misbehaved during a math lesson a lot and the nasty teacher Mr. Pickles gave him the following problem as a punishment.

Find all integer solutions $ x $ $ (0&lt;x&lt;10^{9}) $ of the equation:

 $ x=b·s(x)^{a}+c, $ where $ a $ , $ b $ , $ c $ are some predetermined constant values and function $ s(x) $ determines the sum of all digits in the decimal representation of number $ x $ .

The teacher gives this problem to Dima for each lesson. He changes only the parameters of the equation: $ a $ , $ b $ , $ c $ . Dima got sick of getting bad marks and he asks you to help him solve this challenging problem.

## 样例 #1

### 输入

```
3 2 8
```

### 输出

```
3
10 2008 13726 ```

## 样例 #2

### 输入

```
1 2 -18
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 2 -1
```

### 输出

```
4
1 31 337 967 ```

# 题解

## 作者：SakurajiamaMai (赞：3)

**正难则反，考虑枚举数码和**。由于不会快速幂就随便写了个幂运算，计算当前位数是否符合位数总和，枚举每位的数码和，然后利用题目中给的公式看看是否符合条件，利用 set 数组存更加简便，自动排序和去重。
## **代码:**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
long long res,a,b,c,p;
set<int>x;
long long qpow(long long q)
{
    long long ans=1;
    for(int i=0;i<a;i++) ans*=q;
    return ans;
}
int main()
{
    cin>>a>>b>>c;
    for(int i=1;i<=81;i++){
        p=b*qpow(i)+c;
        if(p>1e9) continue;
        long long num=0,tmp=p;
        while(p)
        {
            num+=(p%10);
            p/=10;
        }
        if(num==i) res++,x.insert(tmp);
    }
    cout<<res<<endl;
    for(auto t:x) cout<<t<<" "; 
    return 0;
}   
```


---

## 作者：TheOnlyMan (赞：3)

## 题意
给定一个函数 $S(x)$ 表示 $x$ 的十进制表示下的数码和。其中给定等式 
$$x=b*S(x)^a+c $$ 

当 $x$ 严格小于 $10^9$ 且满足此等式时，则 $x$ 是所求答案之一。
## 思路
考虑到枚举 $x$ 的方式不现实，因为 $x$ 的范围到了 $10^9$，这是妥妥超时的。但是注意到数码和这个条件，在 $10^9$ 的范围下最大的数码和不会超过 $81$，这就给了我们枚举数码和的想法。同时观察等式，在数码和相同的情况下，左边 $x$ 的值是唯一的，这就说明枚举数码和是可行的。对于每个数码和，用数码和求出左边的值，然后再用左边值的数码和判断是否等于该次枚举的数码和即可，相等即是答案。最后输出，完结！

```cpp
#include<iostream>
#include<algorithm>
#include<queue> 
#include<cmath>

using namespace std;
typedef long long ll;
queue<ll>ans;

ll qpow(ll a,ll b)
{
	ll ans=1;
	while(b)
	{
		if(b&1)ans*=a;
		b>>=1; a*=a;
	} 
	return ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	ll a,b,c; cin>>a>>b>>c;
	for(int i=1;i<=81;i++)
	{
		ll k=b*qpow(i,a)+c,p=k;
		ll x=0;
		if(k>=1e9)continue;
		while(k)x+=k%10,k/=10;
		if(x==i)ans.push(p);
	}
	cout<<ans.size()<<"\n";
	while(!ans.empty())
	{
		cout<<ans.front()<<" ";
		ans.pop();
	}
	return 0; 
}
```


---

## 作者：hjfjwl (赞：0)

思路：

给定等式 $x=b\times S(x)^a+c $，$S(X)$ 表示 $x$ 在十进制下的各个位数的和，问你有多少个 $x$ 满足上面的等式。我们会发现如果枚举 $x$ 的时间复杂度很高达到了 $10^9$，我们可以变成枚举 $S(x)$ 来求出 $x$ 并验证是否符合。注意 $0 < x < 10^9$。

Ac code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int p(int a,int b)
{
	int ans = 1;
	while(b)
	{
		if(b & 1)ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}
vector<int>aa;
int cnt = 0;
signed main()
{
	int a,b,c;
	cin >> a >> b >> c;
	for(int i = 0;i <= 81;i++)
	{
		int x = b * p(i,a) + c;
		int t = x;
		int tt = 0;
		while(t)
		{
			tt = tt + t % 10;
			t /= 10;
		}
		if(x && x < 1000000000 && tt == i)
		{
			aa.push_back(x);
			cnt++;
		}
	}
	cout << cnt << endl;
	for(int i = 0;i < aa.size();i++)
	{
		cout << aa[i] << " ";
	}
	return 0;
}
```

---

## 作者：2021zjhs005 (赞：0)

一道暴力题。


$\boxed{Question's\ meaning}$
------------

[题目传送门](https://www.luogu.com.cn/problem/CF460B)。

翻译其实已经讲得很明白了。



------------
定 $S(x)$ 表示 $x$ 的所有数位上的数字之和。

给定 $a$，$b$，$c$，令 $x=b\times S(a)^x + c$，求出所有满足如上等式并且 $0<x<10^9$ 的 $x$。



$\boxed{solution}$
------------

我想不会有人暴力枚举 $x$ 吧。。。

首先看 $x$ 的范围：$0<x<10^9$，暴力枚举 $x$ 肯定 $\texttt{TLE}$。

所以说，我们不能枚举 $x$。

那么可以枚举什么呢？可以枚举 $S(x)$，也就是数码和。

为了求出 $S(x)$ 的枚举上限，我们又要观察 $x$ 的范围：$0<x<10^9$。

贪心，让每一位尽量都是 $9$，也就是说，最大的 $S(x) = S(999999999) = 81$。

然后计算出式子的值，为 $num$。乘方可以用**快速幂**优化，也可以直接累乘。

如果 $0<num<10^9$ 且 $S(num) = i$，就将 $num$ 存入**优先队列**。

为了保证升序排列，所以用了优先队列。

最后输出长度和每个可能的 $num$ 即可。


$\boxed{code}$
------------

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a,b,c,i;
priority_queue <ll,vector<ll>,greater<ll> > que;//定义升序优先队列。
ll quick_pow(ll a,ll p){//快速幂模板，用累乘也可以。
    ll ans=1;
    while(p){
        if(p&1) ans=ans*a;
        a=a*a;
        p>>=1;
    }
    return ans;
}
ll S(ll p){//计算 S(p)。
    ll sum=0;
    while(p){
        sum+=p%10;
        p/=10;
    }
    return sum;
}
int main(){
    cin>>a>>b>>c;
    for(i=1;i<=81;i++){//枚举数码和。
        ll num=b*quick_pow(i,a)+c;//计算式子。
        if(num>0&&num<1e9&&S(num)==i) que.push(num);//满足条件就加入优先队列。
    }
    cout<<que.size()<<endl;
    while(que.size()){//注意，不要忘了。
        cout<<que.top()<<" ";//优先队列没有下标，所以需要边输出边 pop()。
        que.pop();
    }
	return 0;
}
```

---

## 作者：tallnut (赞：0)

这题在 CF 里面有一个 $\text{number theory}$ 标签，其实它跟数论完全没有关系啊 QaQ。
# 思路
$1 \times 10 ^ {9}$ 的数据范围，直接去枚举每个数字不 $\color{#052242}\text{TLE}$ 才怪呢。。。

但是我们发现，$a,b,c$ 都是常数，而 $S(x)$ 最多就是 $81$（$\le 1 \times 10 ^ {9}$ 的数中数位和最大的也就是 $999999999$），因此我们可以直接枚举 $S(x)$，判断运算出来的数的数位和是否正确即可。

我是将 $S(x)$ 从 $1$ 到 $81$ 依次枚举了一遍，这样可以保证得出的答案单调递增。用 vector 存储即可。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/127454101)，代码中有注释。（保险起见开了 long long，但其实没必要）
```
#include <iostream>
#include <vector>
using namespace std;
long long a,b,c,tmp;
//计算数位和
long long calc(long long n)
{
	long long ret = 0;
	while (n)
	{
		ret += n % 10;
		n /= 10;
	}
	return ret;
}
long long pow(long long a,long long b)
{
	long long ret = 1;
	for (long long i = 0;i < b;i++)
		ret *= a;
	return ret;
}
//使用容器 vector 存储所有答案
vector<long long> v;
int main()
{
	cin >> a >> b >> c;
	//枚举数位和
	for (long long i = 1;i <= 81;i++)
	{
		tmp = b * pow(i,a) + c;
		//由于 i 不断增大，而 a,b,c 不变，所以枚举出的所有答案必然单调递增
		if (tmp < 1e9 && calc(tmp) == i) v.push_back(tmp);
	}
	cout << v.size() << '\n';
	for (int i = 0;i < v.size();i++)
		cout << v[i] << ' ';
}
```

---

## 作者：_WHITE_NIGHT_ (赞：0)

首先，看到本题，应该注意的是数据范围：

$1 \le a \le 5,1 \le b \le 10^4,-10^4 \le c \le 10 ^ 4$

并且，所求的数 $x$ 不超过 $10^9$，这就说明函数 $S(x) \in [0,81]$。若枚举 $x$，那么仅计算枚举的时间复杂度就已经不能被接受，所以，我们“反其道而行之”，枚举 $S(x)$，通过给出的公式 $x = b \times S(x)^a + c$ 求解出 $x$ 即可。

那么，我们就可以**枚举 $S(x)$**，再**判断求解出的 $x$ 是否合法**，假如合法，加入答案即可。

具体实现请看代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long

namespace FastIO
{
	const int Mt = 1e5;
	inline char getch()
	{
		static char buf[Mt],*p1 = buf,*p2 = buf;
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,Mt,stdin),p1 == p2) ? EOF : *p1++;
	}
	
	inline int input()
	{
		int num = 0,f = 1;
		char ch = getch();
		while(ch < '0' || ch > '9')
		{
			if(ch == '-') f = -1;
			ch = getch();
		}
		while(ch >= '0' && ch <= '9')
		{
			num = (num << 1) + (num << 3) + (ch ^ 48);
			ch = getch();
		}
		return num * f;
	}
	
	inline void printNum(int num)
	{
		if(num >= 10) printNum(num / 10);
		putchar(num % 10 + 48);
	}
	
	inline void print(int num,char ch = ' ')
	{
		if(num < 0) putchar('-'),num = -num;
		printNum(num);
		putchar(ch);
	}
}
using FastIO::input;
using FastIO::print;

int a,b,c;
vector <int> ans;

int qpow(int a,int b)
{
    int res = 1;
    for(;b;b >>= 1)
    {
        if(b & 1) res *= a;
        a *= a;
    }
    return res;
}

bool check(int aim,int num)//判断答案是否合法
{
    int sum = 0;//记录数位和
    while(aim) sum += aim % 10,aim /= 10;
    return sum == num;
}

void query(int num)//求解x
{
    int aim = b * qpow(num,a) + c;//aim表示求解出的x
    if(aim >= 1e9) return;//判断是否在合法范围内
    if(check(aim,num)) ans.push_back(aim);
}

signed main()
{
    a = input(),b = input(),c = input();
    for(int i = 1;i <= 81;i++) //枚举S(x)
        query(i);
    print(ans.size(),'\n');
    for(int num : ans) print(num);
}
```

效率为 $O(k\times\log_{10}{x})$，$k = 81$。

---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF460B)

duel bot.duel bot.duel bot.

$x$ 是不可能枚举的，但是 $\max_{i=1}^{10^9} S(i)=81$，考虑枚举它。

显然对于一个数位和 $k$，$x$ 能直接算出来。此时判断 $S(x)=k$ 即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100;
int a,b,c,ans,k;
long long r[N];
long long Pow(int x,int y){
    long long ret=1;
    for(int i=1;i<=y;i++)ret*=x;
    return ret;
}
long long F(int u){
    return 1ll*b*Pow(u,a)+c;
}
int C(long long u){
    int ret=0;
    while(u)ret+=u%10,u/=10;
    return ret;
}
signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d%d%d",&a,&b,&c);
    for(int i=1;i<=81;i++)if(F(i)<1e9&&C(F(i))==i)r[++k]=F(i);
    printf("%d\n",k);
    sort(r+1,r+k+1);
    for(int i=1;i<=k;i++)printf("%lld ",r[i]);
    puts("");
    system("pause");
    return 0;
}
```

[record](https://www.luogu.com.cn/record/123620916)

---

