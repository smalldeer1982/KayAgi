# Sum of Cubes

## 题目描述

给您一个正整数  $x$ ，问这个正整数能否拆分成两个立方数之和。

也就是说，是否存在  $1\le a, b$ 满足  $a^3+b^3=x$ 。

## 样例 #1

### 输入

```
7
1
2
4
34
35
16
703657519796```

### 输出

```
NO
YES
NO
NO
YES
YES
YES```

# 题解

## 作者：冰糖鸽子 (赞：7)

枚举小水题

----

发现 $x$ 并不算特别大，$\sqrt[3]{x}$ 也只有 $10^4$ ，考虑枚举 $a$ 并判断 $b$ 是否为整数。

- 立方根：灵活运用 `pow` 函数，也就是 `pow(xxx,1.0/3)`

- 有一个要注意的地方，`pow` 可能会有误差，所以要尝试一下 `pow(xxx,1.0/3)+1`

至此本题就做完了，代码：

```cpp

// Problem: C. Sum of Cubes
// Contest: Codeforces - Codeforces Round #702 (Div. 3)
// URL: https://codeforces.ml/contest/1490/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
#define int long long
int T,n,x,y,tag;
signed main()
{
	cin>>T;
	for(int t=1;t<=T;t++)
	{
		cin>>n;tag=0;
		for(int i=1;i*i*i<n;i++)
		{
			x=n-i*i*i;
			y=pow(x,1.0/3);
			// cout<<i<<' '<<x<<' '<<y<<endl;
			if(y*y*y==x&&y)
			{
				cout<<"yeS"<<endl;
				tag=1;
				break;
			}
			y++;
			if(y*y*y==x)
			{
				cout<<"yeS"<<endl;
				tag=1;
				break;
			}
		}
		if(!tag) cout<<"nO"<<endl;
	}
	return 0;
}
```

---

## 作者：zplqwq (赞：5)

# Sum of Cubes

没错，这道题的翻译就是我给的，出锅的话记得@我，谢谢！

## 题目分析

题意就是叫你判断是否存在  $1\le a, b$ 满足  $a^3+b^3=x$ 。

思路应该不难想，就模拟判断就可以了。

那具体怎么做呢？

首先我们枚举$a$。

其次，我们用$x$-$a^3$求出$b$。

然后判断$a^3$与**强转成整数型**的$b$开立方的立方的和是否为$x$。

补充：

- 在c++里，开立方可以用$cbrt(x)$。
- 如果用$pow$的话**可能**会出锅（亲测）

## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;

const int N=10000010;

int a[N];
int flag;//用来标记是否满足题意
signed main()
{
	int T;
	cin>>T;
	while(T--)//多组数据
	{
		int x;
		cin>>x;
		for(int i=1;i<=cbrt(x);i++)//枚举a
		{
			int j=x-i*i*i;
			if(i*i*i+(int)cbrt(j)*(int)cbrt(j)*(int)cbrt(j)==x and (int)cbrt(j)>0)//判断，注意，这里有个坑，(int)cbrt(j)必须要大于0
			{
				cout<<"Yes"<<endl;//满足题意
				flag=1;//标记
				break;//跳出
			}
		}
		if(flag==0)
		{
			cout<<"No"<<endl;
		}
		flag=0;//多测不清空，报零两行泪！
	}
    return 0;
}

```



---

## 作者：EDqwq (赞：2)

### 思路：

$10^{12}$很小，开立方根最多也只是$10^{4}$，所以直接预处理10000以内数对应的立方数，然后循环，从1到10000，用$n$去减去这个立方数，如果减出来的数是立方数就输出YES。

***

### 代码：

```cpp
/*
  Author: EnderDeer
  Online Judge: Luogu
*/

#include<bits/stdc++.h>

#define int long long
#define mem(x) memset(x,0,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int t;

map <int,int> q;

signed main(){
	for(int i = 1;i <= 10000;i ++)q[i * i * i] = 1;
	cin>>t;
	while(t --){
		bool flag = false;
		int n;
		n = read();
		for(int i = 1;i <= 10000;i ++){
			int x = n - i * i * i;
			if(x <= 0)break;
			if(q[x]){
				flag = true;
				break;
			}
		}
		if(flag)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：1)

upd. 修改了一些错误，添加了第一个代码。

### Description

> 输入 $n$，判断 $n$ 是否满足
> $$ i^3 + j^3 = n\ (i,\ j \ge 1)$$
> 满足输出 $\tt{YES}$，不满足输出 $\tt{NO}$，不区分大小写

### Solution

首先我们可以想到两重循环直接枚举 $i$ 和 $j$，然后判断 $i\cdot i\cdot i + j\cdot j\cdot j$ 是否等于 $n$，只要找到就输出 $\tt{YES}$，找不到输出 $\tt{NO}$，但是显然会超时（[核心代码](https://www.luogu.com.cn/paste/g7hpicbe)）。

![你不会知道我是谁](https://cdn.luogu.com.cn/upload/image_hosting/xlbq80dr.png)

考虑优化这个方法，显然，只用枚举 $i$，然后就可以算出 $j$，也就是

$$ j = \sqrt[3]{n - i \cdot i \cdot i} $$

算完以后，要验证一下 $(j \cdot j \cdot j)^3$ 是否与 $n - i \cdot i \cdot i$ 相等。

另外，还要注意的是要数据规定了 $i,\ j \ge 1$，所以我们还要判断 $j$ 是否大于或等于 $1$。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int t; cin >> t;
	while (t--)
	{
		bool flg = 0;
		int n;
		cin >> n;
		for (int i = 1; i * i * i <= n; i++)
		{
			int j = n - i * i * i;
			int k = (int)(cbrt(j));
			if (i * i * i + j == n && k * k * k == j && j > 0)
			{
				cout << "YES";
				flg = 1;
				break;
			}
		}
		if (!flg) cout << "NO"; puts("");
	}
}
```



---

## 作者：xh39 (赞：1)

$a^{3}+b^{3}$ 是一个对称式(即交换 $a,b$ 原式值不变)。所以可以认为 $a<=b$,因为 $a>b$ 的情况相当于把 $a$ 与 $b$ 交换。

所以可以直接枚举 $a$,然后算出 $b=^{3}\kern{-8pt}\sqrt{n-a^{3}}$。如果 $b$ 是正整数,则输出```yes```并结束程序。否则继续枚举。若枚举完所有 $a$ 仍未找到,则输出```no```。

现在的重点是如何求 $^{3}\kern{-8pt}\sqrt{n-a^{3}}$,设结果为 $ans$,由于 $ans^{2}$ 满足单调性,所以二分 $ans$ 即可。

小技巧:由于 $^{3}\kern{-8pt}\sqrt{n-a^{3}}$ 可能不为整数,这时如果把小数的值也枚举出来很费时间,所以只需要枚举其整数值,然后判断 $ans^{3}$ 是否等于 $n-a$ 即可。若等于则说明是整数,输出```yes```,否则继续枚举。

细节:注意二分的上界最多为 $10^{4}$。不然算立方时会爆longlong。

单组数据时间复杂度:$O(^{3}\kern{-8pt}\sqrt{x}\times log_2(x))$。
```cpp
#include<iostream>
using namespace std;
long long sqrt3(long long a){
	long long l=1,r=min(10000ll,a),m;
	while(l<=r){
		m=l+r>>1ll;
		if(m*m*m<a){
			l=m+1ll;
		}else{
			r=m-1ll;
		}
	}
	return l;
}
void Main(){
	long long n,i,a,b=9223372036854775807ll; //b一定要初始化,否则一开始就进不去a<=b的循环。
	cin>>n;
	for(a=1;a<=b;a++){
		b=sqrt3(n-a*a*a);
		if(a*a*a+b*b*b==n){
			cout<<"yes"<<endl;
			return;
		}
	}
	cout<<"no"<<endl;
}
int main(){
	long long t,i;
	cin>>t;
	for(i=0;i<t;i++){
		Main();
	}
	return 0;
}
```

---

## 作者：清烛 (赞：0)

（挂一下 [My Blog](https://imyangty.com/oi/1309)）

## 题意
$T(T\le 100)$ 次询问一个整数 $x(x\le 10^{12})$ 是否可以拆分为两个正整数的立方和。

## 题解
注意到 $\sqrt[3]{10^{12}}$ 的值为 $10^4$，因此我们只需要考虑 $10^4$ 个数的立方和是否能凑出 $x$。直接将这些数存进一个 `std::set<long long>` 然后从小到大枚举 $a$，看 $x - a^3$ 在不在 `set` 中即可。时间复杂度为 $O(Tx\log x)$，大概估算一下是 $10^7$ 数量级的，能过。

提醒：对于这种时间比较宽裕的题**尽量不要**用 `std::unordered_map`，可能会被有心人利用 hash 的性质给 hack 掉，详见 [Blowing up unordered_map, and how to stop getting hacked on it](https://codeforces.com/blog/entry/62393 "Blowing up unordered_map, and how to stop getting hacked on it")。**赛时有人因为用了 `std::unordered_map` 被叉掉的。改成 `std::map` 就过了。**

```cpp
std::set<int> cube;

signed main()
{
    int T = read();
    FOR(i, 1, 10000)
        cube.insert(i * i * i);
    while (T--)
    {
        int x = read();
        bool flag = 0;
        FOR(i, 1, 10000)
            if (cube.count(x - i * i * i))
            {
                flag = 1;
                break;
            }
        if (flag) YES;
        else NO;
    }
    return 0;
}
```

---

## 作者：registerGen (赞：0)

[宣传一下这次 div3 的题解](https://registergen.github.io/post/solution-codeforces-round-702-div-3/)


预处理 $1\sim 10^{12}$ 的完全立方数（共 $10^4$ 个），把它们插到 `std::set` 里。每次询问先枚举 $a$，如果 `std::set` 里有 $x-a^3$，则输出 `YES`。

```cpp
std::set<ll> s;
 
void init(){
	for(ll i=1;i<=10000;i++)
		s.insert(1LL*i*i*i);
}
 
void solve(){
	ll x;
	scanf("%lld",&x);
	for(ll i=1;i<=10000;i++){
		ll b=x-1LL*i*i*i;
		if(s.find(b)!=s.end()){puts("YES");return;}
	}
	puts("NO");
}
```

---

## 作者：唐一文 (赞：0)

## Description

给定一个数 $n$，判断是否存在 $1\leq a,b$，使得 $a^3+b^3=n$。

## Solution

发现 $n\leq10^{12}$，$\sqrt[3]{n}\leq10^4$，所以可以预处理出 $1$ 到 $n$ 中所有的立方数，暴力枚举 $1$ 到 $\sqrt[3]{n}$ 再判断即可。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
int T;
map<ll,bool>vis;
ll n;
int main(){
  for(re ll i=1;i<=10000;++i)vis[i*i*i]=true;
  for(scanf("%d",&T);T--;){
    scanf("%lld",&n);bool flag=false;ll k=pow(n,1.0/3);
    for(re ll i=1;i<=k;++i)if(vis[n-i*i*i]){flag=true;break;}
    printf(flag?"YES\n":"NO\n");
  }
}
```

---

## 作者：云浅知处 (赞：0)

[珂能并不会有更好的阅读体验](https://yunqian-qwq.github.io/post/solution-cf1490c)

------------

### Description

[题目 Link](https://codeforces.com/problem/1490/C)

>- 给一个数 $x$ ，判断其是否能表示为两个立方数之和。
>- 即：是否存在 $a,b$ 使 $a^3+b^3=x$。
>- $t$ 组询问，$1\le t\le 100,1\le x\le 10^{12}$。

------------

暴力即可......

只需要在 $[1,\sqrt[3]{x}]$ 范围内暴力查找 $a$，然后计算 $x-a$ 是否为完全立方数即可。

计算 $x-a$ 是否为完全立方数时，可以提前用 `map` 把 $[1,10^{12}]$ 内的所有完全立方数存一遍，也可以用 `pow` 来开三次根号判断qwq。

顺便，不要乱想那个什么 $a^3+b^3=(a+b)(a^2-ab+b^2)$，然后枚举 $x$ 的所有因数qwq，这么做复杂度很屑的/dk

我是开了个 `map`，不过这样会多一个 $\log$，导致复杂度变为 $O(t\sqrt[3]{x}\log10000)$。

不开 `map` 的话复杂度就是直接 $O(t\sqrt[3]{x})$ 的qwq。

```cpp
#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<iomanip>
#include<map>

#define int long long

using namespace std;

int t,x;

map<int,int>mp;

signed main(){

    mp.clear();
    for(int i=1;i<=10000;i++)mp[i*i*i]=1;

    cin>>t;
    while(t--){
        cin>>x;
        int f=0;
        for(int i=1;i*i*i<=x;i++){
            int t=i*i*i;
            if(mp[x-t]==1){
                cout<<"YES\n";
                f=1;
                break;
            }
        }
        if(!f)cout<<"NO\n";
    }

    return 0;
}
```

---

## 作者：henrytb (赞：0)

因为 $1\le x\le 10^{12}$，因此 $a,b$ 不会超过 $\sqrt[3]{10^{12}}=10^4$。

所以我们枚举 $1\sim 10^4$ 这些数的三次方。把这些三次方数扔进一个 `set` 里。

然后对于每一个询问，我们遍历一遍 `set`，看看这个数减去遍历到的数是不是在那个 `set` 里面。如果是的话，这个数就可以表示成 $a^3+b^3$ 的形式。如果遍历了一遍都不是的话，就不行。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n;
set<int> s;
signed main() {
    rep(i,1,10000) s.insert(i*i*i);
    for(scanf("%lld",&_);_;--_) {
        scanf("%lld",&n);
        bool flg=0;
        for(set<int>::iterator ii=s.begin();ii!=s.end();++ii) {
            int qwq=(*ii);
            if(qwq>=n) break;
            int rem=n-qwq;
            if(s.count(rem)) {flg=1;break;}
        }
        if(flg) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：_caiji_ (赞：0)

这道题直接暴力就可以了。方法是从 $1$ 枚举到 $\sqrt[3]{x}$，每次检验 $x-a^3$ 是否能写成 $b^3$ 的形式，如果可以，输出 `YES`，否则下一轮。如果枚举完还没有输出 `YES`，就输出 `NO`。

那如何检验 $x-a^3$ 是否能写成 $b^3$ 的形式呢？~~我们都知道~~ cmath 头文件里有个非常好用的函数叫 $\operatorname{cbrt}(n)$，它可以求出 $\sqrt[3]{n}$。我们只需要检验 $\lfloor\operatorname{cbrt}(x-a^3)\rfloor^3$ 是否等于 $x$ 就行了。注意还要特判 $\lfloor\operatorname{cbrt}(x-a^3)\rfloor=0$ 的情况，因为题目要求 $1\leq a,b$。

这种方法的复杂度为 $O(T\sqrt[3]{x})=O(100\times \sqrt[3]{10^{12}})=O(10^6)$，可以轻松通过。

```cpp
#include <cstdio>
#include <cmath>//cbrt在这里
using namespace std;
int T;
long long x;
void solve(){
    for(long long a=1;a<=cbrt(x);a++){
        long long b=x-a*a*a;
        long long tmp=cbrt(b);//避免重复计算，用tmp存值
        if(tmp*tmp*tmp==b&&tmp!=0){//顺便特判tmp=0的情况
            puts("YES");
            return ;
        }
    }
    puts("NO");
}
int main(){
    for(scanf("%d",&T);T--;){
        scanf("%lld",&x);
        solve();
    }
    return 0;
}
```

---

