# A Cookie for You

## 题目描述

Anna is a girl so brave that she is loved by everyone in the city and citizens love her cookies. She is planning to hold a party with cookies. Now she has $ a $ vanilla cookies and $ b $ chocolate cookies for the party.

She invited $ n $ guests of the first type and $ m $ guests of the second type to the party. They will come to the party in some order. After coming to the party, each guest will choose the type of cookie (vanilla or chocolate) to eat. There is a difference in the way how they choose that type:

If there are $ v $ vanilla cookies and $ c $ chocolate cookies at the moment, when the guest comes, then

- if the guest of the first type: if $ v>c $ the guest selects a vanilla cookie. Otherwise, the guest selects a chocolate cookie.
- if the guest of the second type: if $ v>c $ the guest selects a chocolate cookie. Otherwise, the guest selects a vanilla cookie.

After that:

- If there is at least one cookie of the selected type, the guest eats one.
- Otherwise (there are no cookies of the selected type), the guest gets angry and returns to home.

Anna wants to know if there exists some order of guests, such that no one guest gets angry. Your task is to answer her question.

## 说明/提示

In the first test case, let's consider the order $ \{1, 2,       2\} $ of types of guests. Then:

- The first guest eats a chocolate cookie. After that, there are $ 2 $ vanilla cookies and $ 1 $ chocolate cookie.
- The second guest eats a chocolate cookie. After that, there are $ 2 $ vanilla cookies and $ 0 $ chocolate cookies.
- The last guest selects a chocolate cookie, but there are no chocolate cookies. So, the guest gets angry.

So, this order can't be chosen by Anna.

Let's consider the order $ \{2, 2, 1\} $ of types of guests. Then:

- The first guest eats a vanilla cookie. After that, there is $ 1 $ vanilla cookie and $ 2 $ chocolate cookies.
- The second guest eats a vanilla cookie. After that, there are $ 0 $ vanilla cookies and $ 2 $ chocolate cookies.
- The last guest eats a chocolate cookie. After that, there are $ 0 $ vanilla cookies and $ 1 $ chocolate cookie.

So, the answer to this test case is "Yes".

In the fifth test case, it is illustrated, that the number of cookies ( $ a + b $ ) can be equal to zero, but the number of guests ( $ n + m $ ) can't be equal to zero.

In the sixth test case, be careful about the overflow of $ 32 $ -bit integer type.

## 样例 #1

### 输入

```
6
2 2 1 2
0 100 0 1
12 13 25 1
27 83 14 25
0 0 1 0
1000000000000000000 1000000000000000000 1000000000000000000 1000000000000000000```

### 输出

```
Yes
No
No
Yes
No
Yes```

# 题解

## 作者：huayucaiji (赞：3)

~~这个题还是推理题~~

首先我们可以想到，第二类人（以下简称 $2$）做出任何选择不会印象第一类人（以下简称 $1$）的选择。因为 $2$ 选择数量少的，$1$ 选择数量多的。所以我们的考虑的主体一定是 $2$。

那么首先我们可以先判断，如果饼干总数比人数少，一定是 No。然后我们再继续。

我们可以考虑如果数量较少的那一类饼干数量大于等于 $2$ 的人数（~~听起来怪怪的~~），那么一定 Yes。因为此时 $a+b>n+m$。$2$ 解决完了，一定应付的过来 $1$。

如果数量较少的那一类饼干数量小于等于 $2$ 的人数，我们要考虑让 $1$ 去配合 $2$。但是我们可以发现是不可行的。因为为了让 $2$ 去吃原来数量多的那一类，就一定要让 $1$ 把原来多的吃掉很多，知道比原来较少的还要少。这个局面达不到得到，$1$ 的人数够不够多不说，我们可以发现此时的局面还不如一开始，因为现在较少的那一类饼干的数量比之前较少的那一类饼干的数量还要少。所以一定是 No。

~~由于 YES,NO 的大小写随意，程序就随意啦~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

int n,a,b,m;

signed main() {
	int t=read();
	while(t--) {
		a=read();b=read();n=read();m=read();
		
		if(a+b<n+m) {
			printf("No\n");
		}
		else if(min(a,b)>=m) {
			printf("Yes\n");
		}
		else {
			printf("nO\n");
		}
	}
	return 0;
}

```

---

## 作者：zlqwq (赞：2)

考虑两种一定不行的情况。

第一种是 $\min(a,b) < m$，这样选的少的客人就不满足。

第二种是 $n + m > a + b$，这样总数不满足。

如上暴力判断即可。


```cpp
#include<iostream>
#define int long long
#define debug cout << "zlqwq"
#define inf 1e18

using namespace std;
void solve() {
	int n,m,a,b;
	cin >> a >> b >> n >> m;
	if((min(a,b) < m) || (n + m > a + b)) cout << "No" << '\n';
	else cout << "Yes" << '\n';
}
signed main() {
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## CF1371C A Cookie for You
[原题链接](https://www.luogu.com.cn/problem/CF1371C)

## 分析
假如有 $v$ 块香草饼干，$c$ 块巧克力饼干。
- 如果 $v>c$，第一类客人会选择香草饼干，否则会选择巧克力饼干。
- 如果 $v>c$，第二类客人会选择巧克力饼干，否则会选择香草饼干。

简单来说，第一类客人哪种饼干多吃哪种，第二类客人哪种饼干少吃哪种。不难发现第二类客人不管如何选择都不会影响第一类客人。所以如果让第二类客人先吃，只需要考虑第二类客人。

第二类客人吃的饼干数就是两数中最小值，即 ```min(v,c)```。如果第二类客人不会生气，那么两数中最小值一定比第二类客人人数多。得出 ```min(v,c)>m```。而剩下的饼干如果比第一类客人的人数多，则第一类客人也不会生气。反之如果人数比剩下的饼干数多，那么肯定无法分配了。

## Code
```cpp
#include<iostream>
using namespace std;
long long a,b,n,m;
int main(){
    int t;cin>>t;
    while(t--){
        cin>>a>>b>>n>>m;
        if(min(a,b)<m||n>a+b-m)
		//较少饼干数量比第二类客人人数少
		//第一类客人比剩下饼干数量多 
			cout<<"No"<<endl;
        else
			cout<<"Yes"<<endl;
    }
    return 0;
}
```


---

## 作者：yaaaaaan (赞：0)

## 思路
这道题第一类客人是拿多的，第二类客人是拿少的。那我们就可以让第二类客人先拿，这样可以保证第一类客人最后肯定有拿的。

那我们考虑不可行的情况。
*   第一种情况是饼干根本不够拿，即 $n+m>a+b$。
*   第二种情况是第二类客人不够拿，即 $\min(a,b) < m$。

只要第二类客人够拿并且饼干够，则一定有解。
## code

```cpp
#include<bits/stdc++.h>
#define int long long
#pragma GCC optmize(3)
using namespace std;
int t;
int n,m,a,b;
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>a>>b>>n>>m;
		if(n+m>a+b||min(a,b)<m) cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}

```

---

## 作者：LZYAC (赞：0)

结论题。

我们先让第二种客人吃，因为他们不会对第一种客人造成影响。

发现输出 No 的情况只有两种：

+ 总饼干数量不够，也就是 $a+b<n+m$ 的时候。
+ 少的饼干不能让第二种客人吃够，也就是 $\min (a,b) < m$ 的时候。

发现没有其他可能输出 No ，所以这道题就做完了。

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1371C)

### $\texttt{Description}$

有 $2$ 种不一样的客人和 $2$ 种不一样的饼干，第一种客人会选择多的饼干，第二种客人会选择少的饼干，问是否有一种合适的方法，使得每个客人都能够吃到自己想要的饼干。

本题有多组数据。

### $\texttt{Solution}$

这题就是一个结论题。

我们都知道，少的饼干是有 $\min(a,b)$ 块，而第二种客人是有 $m$ 位，那么就可以判断 $\min(a,b)$ 是否 $\ge m$，如果不符合条件就直接输出 `No` 即可。

然后就只需要判断 $a+b$ 是否 $\ge n+m$，也就是判断总饼干数量是否足够，如果不符合条件就还是直接输出 `No` 即可。

否则就是满足条件，输出 `Yes` 就行。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int t;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> t;
	
	while (t--) {
		int a, b, n, m;
		cin >> a >> b >> n >> m;
		
		if (min(a, b) < m) {
			cout << "No\n";
			continue;
		}
		
		if (a + b < n + m) {
			cout << "No\n";
			continue;
		}
		
		cout << "Yes\n";
	}
	
	return 0;
}
```

注意数据范围：$0 \le a,b,n,m \le 10^{18}$ ，所以一定要开 `long long`。

完结。

---

## 作者：LRRabcd (赞：0)

# 题目分析

我们有 $a$ 块香草饼干和 $b$ 块巧克力饼干；$n$ 位第一类客人和 $m$ 位第二类客人。
第一类客人只吃多的那一类饼干，相反第二类客人只吃少的那一类饼干，第二类客人的条件更严格，所以先判断第二类客人。

----

## 判断第二类客人

少的那一类饼干的数量为 $\min(a,b)$ 块，第二类客人的数量为 $m$ 位。

这样就只需判断 $\min(a,b)$ 与 $m$ 的大小就可以了：

- 如果 $\min(a,b) \ge m$ 说明第二类客人都不会生气；
- 如果 $\min(a,b)<m$ 则有 $\min(a,b)-m$ 位第二类客人会生气。

## 再判断饼干总量与客人总量

饼干的数量为 $a+b$，客人的数量为 $n+m$，只需再判断 $a+b$ 与 $n+m$ 的大小即可：

- 如果 $\min(a,b) \ge m$ 并且 $a+b \ge n+m$ 则输出 `Yes`；
- 否则输出 `No`。

## 代码

```cpp
#include<iostream>
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
        long long a,b,n,m;//10^18,int存不下
        cin>>a>>b>>n>>m;
        if(!(a+b>=n+m&&min(a,b)>=m)){
            cout<<"No"<<endl;
        }else{
            cout<<"Yes"<<endl;
        }
    }
    return 0;
}
```

---

## 作者：luuia (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1371C)

## 题意

有 $2$ 类客人和 $2$ 类饼干，第一类客人会选择多的饼干，第二类客人会选择少的饼干，问是否有一种合适的方法，使得每个客人都能够吃到自己想要的饼干。

## 分析

可以看出，第二类客人只会吃少的饼干，那么少的饼干就会越吃越少，而多的饼干依然更多，所以第一类人仍然会选择最开始多的那种饼干，所以我们重点关注第二类人。

下面分 $2$ 种情况：

- 饼干总数和总人数的关系

- 较少饼干和第二类客人的关系

如果饼干总数少于总人数，那么因为每个人都要吃一块饼干，所以一定没有满足要求的方法，直接输出```NO```，否则继续进行下面的判断。

如果较少的饼干小于第二类客人的人数，那么第二类客人会一直吃较少的饼干，直到这种饼干被吃完，那么就没有合适的方法，输出```NO```。

如果以上两种情况都不满足，输出```YES```即可。

另外，本题输入输出量比较大，可以使用快读快写。附赠[快读快写模板](https://www.luogu.com.cn/paste/v1r84jv3)。
## 代码
下面是 AC 代码：[AC 代码](https://www.luogu.com.cn/paste/ceeo03xr)

```cpp
#include<bits/stdc++.h>
using namespace std;

int read()//快读
{
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}

int main()
{
	int T;
	T = read();
	while(T--)
	{
		int a,b,m,n;
		a = read();
		b = read();
		m = read();
		n = read();
		if((a + b) < (m + n))
		{
			cout << "NO" << endl;
		}
		else
		{
			if(min(a,b) < m)
			{
				cout << "NO" << endl;
			}
			else
			{
				cout << "YES" << endl;
			}
		}
	}
	return 0;
}
```


---

## 作者：可爱的甜甜猫 (赞：0)

这道题是非常简单的，首先说注意事项：看好数据范围！  
$ 0 \le a,b,n,m \le 10^{18}$，我们需要开 ``` long long```。 

然后就可以分析这道题了：想要两类客人都不生气，首先要保证饼干比客人多，这是显而易见的。

然后我们就要考虑优先满足哪一类客人。~~刁钻作妖的~~吃数量少的饼干的第二类客人应该优先满足。在饼干比客人多（或相等）且两种饼干中数量少的那种比第二类客人多（或相等）的情况下，我们输出 ```Yes```，否则输出 ```No```。  

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,n,m;
int t;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>a>>b>>n>>m;
		if(a+b>=m+n&&min(a,b)>=m){
			cout<<"Yes"<<endl;
		}else{
			cout<<"No"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：0)

### 题意

- 有数量分别为 $a,b$ 的两种饼干和数量分别为 $n,m$ 的两种客人
。
- 数量为 $n$ 的客人每次选数量较多的饼干吃，而数量为 $m$ 的客人每次选数量较少的饼干吃。

- 如果客人选择的饼干还至少有一块，他就会拿走一块，否则就会生气。

- 问是否存在一种客人选择饼干的顺序使客人不会生气。

- $t \le 1000, 1 \le a,b,n,m \le 10^{18}$。

### 思路

我们不妨先考虑先吃数量少的饼干的客人，因为他们不会对另一类客人造成影响（被他们吃的饼干只会越来越少，所以不会影响两种饼干的数量关系）。刚开始，$m$ 位客人选择了 $\min(a,b)$ 的饼干开始吃，而自此以后他们会一直吃这种饼干直到吃完，然后剩下的全部留给其余的 $n$ 位客人吃。所以如果方案存在，只需要满足以下两点要求：

- $\min(a,b) \ge m$，要让选少的吃的客人有足够的饼干吃。

- $a+b \ge n+m$，要保证 $m$ 位客人吃完后 $n$ 位客人还有足够的饼干吃。

注意数据可以达到 $10^{18}$，所以一定要记得开 long long！！！

### 代码

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
long long t,a,b,n,m;
int main(){
    cin >> t;
    while(t--){
    	cin >> a >> b >> n >> m;
		if(a+b >= n+m && min(a,b) >= m){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}  
	}
	return 0;
}
```

---

## 作者：惟有泪千行 (赞：0)

题目大意 

现在有两种饼干，两种人，一种人选多的吃，一种人选少的吃，求是否能满足条件。

分析

首先如果饼干数是少于总人数是不行的，然后我们来看一下第二种情况，也就是有一种人不能吃够。

如果说是让第一类人吃不够那么按照他们的原则他们一定会吃最多的所以假设现在有$a,b$块饼干，$a>b$或$b<a$则一定会吃成$a=b$的情况，接下来每吃两次就会相等一次，所以只有当$a+b>m$（已排除）才能够吃不够。

那么来看一下第二种人，容易发现对于$a,b$,它能吃的最多个数为$(\min(a,b))$。

那我们就考虑先让第二种人吃，再让第一种人吃，就可以保证最优了。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int t,a,b,n,m;
inline int read(){
	int x=0;char ch=getchar();
	while(ch>'9'||ch<'0')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
signed main(){
	t=read();
	while(t--){
		a=read(),b=read(),n=read(),m=read();
		if((a+b)<(n+m)||min(a,b)<m){
			puts("No");
		}
		else puts("Yes");
	}
	return 0;
}
```


---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF1371C)

## 思路

因为第二类人只选择少的饼干，所以先考虑这类人。

如果较少饼干数，即 $\min(a,b)$ 的饼干满足不了 $m$ 位客人，输出 NO。

如果饼干总数小于总人数，也要输出 NO。

若两种情况都不满足，输出 YES 即可。

数据范围 $1 \le a,b,n,m \le 10^{18}$，注意 long long。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,a,b,n,m;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>a>>b>>n>>m;
        if(min(a,b)<m||a+b<m+n) cout<<"NO\n";
        else cout<<"YES\n";
    }
    return 0;
}
```

---

