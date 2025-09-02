# Scenes From a Memory

## 题目描述

给出一个正整数 $n$，$n$ 中不包含 $0$。求最大删去多少位使其变成一个合数或 $1$。数据保证一定存在答案。

素数是指除 $1$ 和它本身外没有除数的数。合数是指一个有两个以上除数的数。$1$ 既不是质数也不是合数。

## 样例 #1

### 输入

```
7
3
237
5
44444
3
221
2
35
3
773
1
4
30
626221626221626221626221626221```

### 输出

```
2
27
1
4
1
1
2
35
2
77
1
4
1
6```

# 题解

## 作者：CSP_Sept (赞：4)

### Background

赛时这题交了 5 发直接 $-4$，59min 时 PP，只拿了 514 分（悲

### Description

给定一个 $k$ 位数，要求对其删除若干位后使其是一个 **非质数**（等于 $1$ 或是一个合数），该数中不含 $\tt0$。

只要输出一种方案即可，保证有解，多测。

### Solution

我们先证明一个简单的结论：

>**引理** 对于一个三位数 $n$，你总可以找到一种方案，删掉至少 $1$ 位，使其剩下最多 $2$ 位且是一个 **非质数**。
>
>**证明** 注意到可以分成以下几种情况考虑：
>
>1. $n$ 中本身含有 $\tt 1,4,6,8,9$ 之一，只保留这一位即可。
>2. $n$ 中第 $i(i>1)$ 位是 $\tt2,5$ 之一，保留第 $1,i$ 位即可。
>3. $n$ 中有两个相同的数，只保留这两个相同的数即可。
>4. $n$ 中第 $1$ 位是 $\tt2,5$ 之一，第 $i(i>1)$ 位是 $\tt7$，保留第 $1,i$ 位即可。
>
>可以证明，这 4 种情况覆盖了所有的合法三位数。
>

运用数学归纳法可以把「**引理**」拓展至 $k$ 位数。

于是根据这个结论枚举即可。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;
int a[60], k;
int c[10];
void Sol(){
	memset(a, 0, sizeof(a));
	memset(c, 0, sizeof(c));
	scanf("%d", &k);
	for(int i = 0 ; i < k ; i++)
		scanf("%1d", &a[i]);
	for(int i = 0 ; i < k ; i++){
		if(a[i] == 1 || (a[i] != 2 && a[i] % 2 == 0) || a[i] == 9){
			puts("1");
			printf("%d\n", a[i]);
			return;
		}
	}
	for(int i = 1 ; i < k ; i++){
		if(a[i] == 2 || a[i] == 5){
			puts("2");
			printf("%d%d\n", a[i - 1], a[i]);
			return;
		}
	}
	for(int i = 0 ; i < k ; i++){
		if(c[a[i]]){
			puts("2");
			printf("%d%d\n", a[i], a[i]);
			return;
		}
		c[a[i]] = 1;
	}
	for(int i = 1 ; i < k ; i++){
		if((a[0] == 2 || a[0] == 5) && a[i] == 7){
			puts("2");
			printf("%d%d\n", a[0], a[i]);
			return;
		}
	}
}
int main(){
	int T;
	scanf("%d", &T);
	while(T--)
	    Sol();
	return 0;
}
```

---

## 作者：Jur_Cai (赞：3)

先给出结论：取出的一位、两位数中必有符合要求的解

### 下面给出证明：
1. 若其中有数字 $1$、$4$、$6$、$8$、$9$，则只剩下这个数就满足了要求。

2. 考虑去除这些数后的两位数，只由 $2$、$3$、$5$、$7$ 组成，构成的两位数中，又只有 $23$、$37$、$53$、$73$ 是质数，所以一个数作为十位和剩下两个数可以构成一组解。很容易发现，一个长度大于二的数必能分割出一组解，而题目又保证有解，长度等于二的数也大力匹配就好啦！


------------

最后贴一个代码

```cpp
#include <iostream>
using namespace std;
int n;
string s;
bool prime[100];
void solve() {
	for (int i=0;i<n;i++)
	    if (s[i]=='1'||s[i]=='4'||s[i]=='6'||s[i]=='8'||s[i]=='9') {
		    cout<<1<<endl<<s[i]<<endl;
		    return;
		}
		for (int i=0;i<n;i++) {
			for (int j=i+1;j<n;j++) {
			    if (!prime[(s[i]-'0')*10+(s[j]-'0')]) {
					cout<<2<<endl;
					cout<<s[i]<<s[j]<<endl;
			    	return ;
				}
			}
		}
}
int main() {
    for (int i=2;i<100;i++) {
	    prime[i]=1;
	    for(int j=2;j*j<=i;j++)
		    if (i%j==0) {
		    	prime[i]=0;
		    	break;
			}
	}
    int T;
    scanf("%d",&T);
    while (T--) {
	    cin>>n>>s;
	    solve();
	}
}
```


---

## 作者：Diana773 (赞：3)

# 题意简述
给定 $t$ ( $1 \le t \le 10000$ ) 个不含 $0$ 的 $k$ ( $1 \le k \le 50$ ，$\sum k \le 10000$ ) 位整数 $n$。对于每个 $n$，删除尽可能多但严格小于 $k$ 个的数位使 $n$ 变成非质数 （ $1$ 不是质数，题目数据保证有解），并分两行输出删除后的 $n$ 的位数和 $n$。
# 题目分析

要删除尽可能多，就要依次考虑将 $n$ 删除到只剩下 $1$ 位、$2$ 位、$3$ 位等。考虑了所有剩下 $1$ 位和大部分剩下 $2$ 位的情况，会发现剩下的数字很小，可以直接暴力枚举删除操作解决。

1. $n$ 中存在数字 $1$、$4$、$6$、$8$、$9$ 时，直接将 $n$ 删除到只剩下其中任意一个数字即可。

2. $n$ 不满足条件 $1$ 时，若 $n$ 的数位上存在两个相同的数字 $2$、$3$、$5$、$7$ 时，则直接将 $n$ 删除到只剩下两个相同的数字即可。

3. $n$ 不满足条件 $1$ 和条件 $2$ 时，$n$ 此时只包含数字 $2$、$3$、$5$、$7$，并且每个数字必定只出现一次。此时的 $n$ 最多只能是四位数的，可以预处理所有 $8000$ 以内的质数，然后暴力枚举 $n$ 的所有删除方式找到最优解。

# 参考代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>

using namespace std;

int t,oos,ans,l,pl,bi,ansss;
int k,pp,anss;
string s,s1;
int ss[80];
int pan[8100]; //大于0的是非质数
char c;

void init()  //预处理所有的质数
{
	pan[1]=1;
	for (int i=3; i<= 8000; i++)
	{
		pp=sqrt(i);
		for (int j=2; j<=pp; j++)
		  if(i%j==0)
		    pan[i]++;
		//cout<<i<<" "<<pan[i]<<endl; 
	}
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin>>t;
    init();
    for (int qqw=1; qqw<=t; qqw++)
    {
    	cin>>k;
    	cin>>s;
    	for (int i=1; i<=10; i++)
    	  ss[i]=0;
    	for (int i=0; i<k; i++)
    	{
    		c=s[i];
    		l=c-'0';
    		ss[l]++;
			if (l==1||l==4||l==6||l==8||l==9) //满足条件1直接输出
				goto ars;
		}
		    		
		for (int i=2; i<=7; i++) //满足条件2直接输出
	    {			
	        l=i;
			if (ss[l]>=2)
    		    goto ksm; 
    	}

    	bi=999;
		for (int i=1; i<(1<<k); i++) //位运算暴力枚举所有剩余的情况
		{
			l=0;
			pp=i;
            for (int j=0; j<=k-1; j++)
			{
				if ((i>>j)&1)
				{
					c=s[j];
					l=l*10+c-'0';
				}
			} 
			if (pan[l]) //删除后满足条件的
			{
		      anss=1;
		      if (l/10)
		        anss++;
		      if (l/100)
		        anss++;
		      if (l/1000)
		        anss++;		
			  if (bi>anss) //取剩余位数最小的作为答案
		      {
		    	  bi=anss;
		    	  ansss=l;
			  }
		    }
		}

		cout<<bi<<'\n';
		cout<<ansss<<'\n'; 
		
		continue;
		ksm:
		  cout<<2<<'\n'; 
		  cout<<l<<l<<'\n';
		continue;
    	ars:
    	cout<<1<<'\n';
    	cout<<l<<'\n';	
	}

	return 0;	
}
```
### 后记
比赛时题目没看完整，问了出题人才知道问题所在。

![](https://img-blog.csdnimg.cn/20210827172342172.png)

---

## 作者：uid_310801 (赞：2)

### 题目大意

给定若干个 $k$ 位数，你需要删除掉**尽可能多**的数（至少留一个数），使得留下来的数**不是质数**。

- $1\leqslant k \leqslant 50$。
- 读入的数中不含 $0$
- $1$ 在本题中被认作不是质数。
- 保证有解，有多组数据。

### 题目解析

首先考虑只留下来一位的情况：

一个数字删去若干位后可能不是质数，当且仅当这个数字中某些位数是 $1$ 或 $4$ 或 $6$ 或 $8$ 或 $9$。

即，如果读入的数字中含有 $1,4,6,8,9$ ,显然可以只留下其中一个数字。

---

否则，就需要保留至少两位数：

1.如果该数字中某些数位是$2$（或 $5$ ）且这个数位不在首位，那么这个数一定可以通过保留这个数位和它的前一位数，来使剩下的数能被$2$（或 $5$）整除。

2.如果该数字中有超过两个数位是 $7$ 或者超过两个数位是 $3$ ，那么这个数一定可以通过保留两个 $7$（或 $3$ ）来使剩下的数能被 $11$ 整除（即 $77$ 或 $33$ ）。

3.剩下的情况，则是首位数是唯一的 $2$（或 $5$ ）。由于数据一定有解，而 $23$ 和 $53$ 都是质数，便可通过首位数来判断该保留的是 $27$ 还是 $57$。

### 正确性证明：

如果存在一个数，使得它必须保留至少三位才能保证它不是质数，那么根据上文提到的，该数不能有数位是 $1$ 或 $4$ 或 $6$ 或 $8$ 或 $9$，不能有超过两个 $3$ 或 $7$ ，如果存在 $2$ （或 $5$ ），那么 $2$（或 $5$ ）就必须在首位，不能有数位是 $0$ （题目要求），这样的数数量是有限的，总共就这些：

$2,5,23,27,53,57,37,73,237,273,537,573$

又因为题目保证有解，所以前 $8$ 个数除 $27,57$ 外都不成立，后4个数便可保留首位数和一个 $7$ ，长度都为 $2$。

综上，**不存在一个数使得其满足题目要求且必须保留至少三位才能保证剩余的数不是质数**。

### 代码：

```cpp
#include<bits/stdc++.h>
typedef long long ll; 
using namespace std;
ll t,k,ton[10];
char c[55];
signed main(){
	scanf("%lld",&t);
	while(t--){
		memset(ton,0,sizeof(ton));
		int flag=0;
		scanf("%lld",&k);
		cin>>c;
		for(int i=0;i<k;i++){
			ton[c[i]-'0']++;
			if(c[i]=='1'||c[i]=='4'||c[i]=='6'||c[i]=='8'||c[i]=='9'){
				printf("1\n%d\n",int(c[i]-'0'));
				flag=1;
				break;
			}
		}
		if(flag==1)	continue;
		for(int i=0;i<k;i++){
			if((c[i]=='2'||c[i]=='5')&&i!=0){
				printf("2\n%c%c\n",c[i-1],c[i]);
				flag=1;
				break;
			}
			if((c[i]=='3'||c[i]=='7')&&ton[c[i]-'0']>=2){
				printf("2\n%c%c\n",c[i],c[i]);
				flag=1;
				break;
			}
			
		}
		if(flag==0){
			if(c[0]=='2')
				printf("2\n27\n");
			else
				printf("2\n57\n");
		}
		
	}
	return 0;
}
```

蒟蒻文笔不好，大佬轻喷！！(

---

## 作者：Doqin07 (赞：1)

#### 题面: 
给出一个位数为 $n$ 的数，求出最多能删除几位使其变为一个非素数，即合数和 $1$。


------------

#### Solution: 

分类讨论。

 1. 若一个数包含 $1, 4, 6, 8, 9$，那么答案必然为 这个数位，因为他们本身就是非素数。
 
 21. 若不包含这个几个数。我们考虑答案长度为 $2$ 的情况，若含有 $2,5$ 且不在最开头，可以任找一个数字放在前面，构成非素数。所有两位相同的数 $22,33,55,77$ 都可以被 $11$ 整除，也是非素数。

 31. 我们再来考虑最后三位的情况，把以上的限制排除掉之后，只剩下了 $237 , 273, 537, 573$ ，可以算出这些都可以删掉一位使其变成非素数。所以最后得出结论所有的数最终的答案都是两位数。

所以若不满足 1 的结论时，一一枚举所有的两位数，判断是否为非素数即可，可以事先对于 $\le 100$ 的数，处理出是否为非素数，这样每次查询的时候就是 $O(1)$ 的时间复杂度。


------------

#### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

int T, k;
string s;
bool isPrime[100];
bool check(int x){
	if (x < 2)return false;
	for (int i = 2; i * i <= x; ++i){
		if (x % i == 0)return false;
	}
	return true;
}
void pre_work(){
	for (int i = 2; i <= 99; ++i) isPrime[i] = check(i);
}
void solve(){
	for (int i = 0; i < s.size(); ++i)
		if (s[i] == '1' || s[i] == '4' || s[i] == '6' || s[i] == '8' || s[i] == '9'){
			cout << "1\n";
			cout << s[i] << endl;
			return;	
		}
	}
	for (int i = 0; i < s.size(); ++i){
		for (int j = i + 1; j < s.size(); ++j){
			int cur = (s[i] - '0') * 10 + (s[j] - '0');
			if (!isPrime[cur]){
				cout << "2\n";
				cout << cur << endl;
				return;
			}
		}
	}
	return;
}
int main(){
	std::ios::sync_with_stdio(false);
	cin >> T;
	pre_work();
	while (T--){
		cin >> k >> s;
		solve();
	}
	return 0;
}







?
```



---

## 作者：BotDand (赞：1)

# $\text{Problems}$

给出 $n$，求在 $n$ 中删除的最大数字，使得最终的 $n$ 为一个合数或 $1$。

请注意，你不能将所有数字删完，且数据保证有解。

若有多种方案，输出一种即可。

# $\text{Answer}$

不难发现，当 $n$ 含有 `1,4,6,8,9` 这些数时，一定能将 $n$ 删为一位合数或 $1$。

考虑 $n$ 只含 `2,3,5,7`。

当 $n$ 的位数大于等于 $5$ 时，则必可删为 `22,33,55,77`，这些数均为合数。

如果 `2,5` 不在开头，则 $n$ 也可删为 $2$ 或 $5$ 的倍数。

于是可以发现剩余的 $n$ 只可能为 `237,273,537,573`，不难发现这 $4$ 个数均可删为 $3$ 的倍数。

于是可得最终答案必然小于等于 $2$，双重循环枚举即可。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int a[52];
char ch;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(int x)
{
    write(x);
    putchar('\n');
}
inline bool check(int n)
{
    if(n<=1) return true;
    for(int i=2;i*i<=n;++i) if(n%i==0) return true;
    return false;
}
inline void work()
{
    n=read();
    for(int i=1;i<=n;++i)
    {
        ch=getchar();
        a[i]=ch-48;
    }
    for(int i=1;i<=n;++i)
        if(check(a[i]))
        {
            print(1);
            print(a[i]);
            return;
        }
    for(int i=1;i<n;++i)
        for(int j=i+1;j<=n;++j)
            if(check(a[i]*10+a[j]))
            {
                print(2);
                print(a[i]*10+a[j]);
                return;
            }
}
int main()
{
    t=read();
    while(t--) work();
    return 0;
}
```


---

## 作者：youyou2007 (赞：1)

## Description
共有 $T$ 组询问。

给定一个长度为 $k$ 的正整数 $n$，求最多能去掉多少位，使得剩下的数为合数或 $1$，并输出剩余位数及剩下的数的任意一种解。

题目保证有解。
## Solution
分类讨论每一种情况。

**第一种：这个数中有一位是合数或 $1$**。

那肯定可以把其他数都删去，输出这一位即可。

例子：$2439$ --> $4$


**第二种：有数字 $2$ 或 $5$ 不在第一位**。

因为除了 $2$ 和 $5$ 本身为质数外，其余的末尾为 $2$ 或 $5$ 的数必为 $2$ 或 $5$ 的倍数，所以最小剩两位，即输出 $2$ 或 $5$ 以及它的前一位。

例子：$372$ --> $72$。

**第三种：$3$ 或 $7$ 至少出现了$2$次。**

将前两种情况排除后，这个数除第一位外只会剩下 $3$ 和 $7$。

所以可以统计一下 $3$ 和 $7$ 的出现次数，$3$ 的个数超过了 $2$ 就输出 $33$，$7$ 的个数超过了 $2$ 就输出 $77$，如果都超过了 ，则任意输出一个即可。

例子：$233$ --> $33$。

**特判：$237$，$273$，$537$，$573$，$57$，$53$**

由于这几个数 $2$ 或 $5$ 在首位，$3$、$7$ 个数也没超过，但有解（答案为 $27$ 或 $57$），所以需要特判一下。
## Code
```cpp
// by youyou2007 Aug.
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#define rep(i, x, y) for(register int i = x; i <= y; i++)
#define per(i, x, y) for(register int i = x; i >= y; i--)
using namespace std;
int T,len;
string s;
int p[]={0,2,3,5,7};
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>len>>s;
		int f=0;
		rep(i,0,len-1)//判断第一种情况
		{
			int ff=0;
			rep(j,1,4)
			{
				if((s[i]-'0')==p[j])
				{
					ff=1;break;
				}
			}
			if(!ff)
			{
				cout<<"1"<<endl<<s[i]<<endl;
				f=1;
				break;
			}
		}
		if(f==1) continue;
		rep(i,1,len-1)//判断第二种情况
		{
			if(s[i]=='2'||s[i]=='5')
			{
				f=1;
				cout<<"2"<<endl;
				rep(j,i-1,i)
				{
					cout<<s[j];
				}
				cout<<endl;
				break;
			}
		}
		if(f==1) continue;
		
		if(s=="237"||s=="273"||s=="27")//六个数的特判
		{
			cout<<"2"<<endl<<"27"<<endl;
			continue;
		}
		if(s=="57"||s=="537"||s=="573")
		{
			cout<<"2"<<endl<<"57"<<endl;
			continue;
		}
		int s1=0,s2=0;
		rep(i,0,len-1)//判断第三种情况
		{
			if(s[i]=='3') s1++;
			else if(s[i]=='7') s2++;
		}
		if(s1>=2) cout<<"2"<<endl<<"33"<<endl;
		else if(s2>=2) cout<<"2"<<endl<<"77"<<endl;
	}
	return 0;
}


```



---

## 作者：KSToki (赞：1)

# 题目大意
给定一个不含 $0$ 的 $k$ 位数，需要删除尽可能多的数（至少留一个数），使最后剩下的数组成的数不是质数（可以为 $1$）。
# 题目分析
这是一道大分类讨论题。首先，如果给出的串中如果含有 $1$，$4$，$6$，$8$，$9$，是可以删到只剩一个的；其次，不含这些数就必须至少有两位，那么**不在第一位**含有 $2$ 或 $5$ 可以满足条件；然后，这时只有第一位可能为 $2$ 或 $5$，其余位均为 $3$ 或 $7$，显然如果 $3$ 或 $7$ 有两个或以上就能输出 $33$ 或 $77$；最后剩余的情况就只有其余位最多有一个 $3$ 或 $7$，而题目保证有解，$23$ 以及 $53$ 均为质数，那么根据第一位是 $2$ 还是 $5$ 即可判断应该输出 $27$ 还是 $57$。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,Mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define For2(i,x,y,k) for(R int i=x;i<=y;i+=k)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define Rof2(i,x,y,k) for(R int i=x;i>=y;i-=k)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,cnt[10];
char num[51];
int main()
{
	T=read();
	while(T--)
	{
		memset(cnt,0,sizeof(cnt));
		n=read();
		scanf("%s",num+1);
		For(i,1,n)
			++cnt[num[i]-'0'];
		For(i,1,n)
			if(num[i]=='1'||num[i]=='4'||num[i]=='6'||num[i]=='8'||num[i]=='9')
			{
				puts("1");
				putchar(num[i]);
				puts("");
				goto over;
			}
		For(i,2,n)
			if(num[i]=='2'||num[i]=='5')
			{
				puts("2");
				putchar(num[i-1]);
				putchar(num[i]);
				puts("");
				goto over;
			}
		if(cnt[3]>=2)
		{
			puts("2");
			puts("33");
			goto over;
		}
		if(cnt[7]>=2)
		{
			puts("2");
			puts("77");
			goto over;
		}
		if(cnt[2]==1)
		{
			puts("2");
			puts("27");
			goto over;
		}
		if(cnt[5]==1)
		{
			puts("2");
			puts("57");
			goto over;
		}
		over:;
	}
	return 0;
}

```

---

## 作者：Jairon314 (赞：0)

$ Solution $

----------

可以发现，答案的位数最大是 $ 2 . $ 因为如果给定的串中的某一位是合数，直接输出这个数字就好了；如果除了第一位，后面某一位出现了数字 $ 5 $ 或者数字 $ 2 $ ，则答案一定是两位的（前面选一个数字，作为十位，这个位置的数字作为个位，一定是合数）；如果出现了相同的两个数字，答案也一定是两位的（这两个相同的数字肯定能组成 $ 11 $ 的倍数）；那么剩下的情况中，除了第一位，后面的每一位都只能是 $ 3 $ 或者 $ 7 $ 且这两个数字只能出现一次（发现这样满足的算第一个位置的最大长度为 $ 3 $），否则都会被前面的几条判定出来，考虑第一位是什么，因为题目保证了会有合法情况，所以第一位一定能和后面两位中的一位形成一个合数，所以这种情况的答案的最大位数也是 $ 2 .$

注意题目说明，有 $ 1 $ 直接输出 $ 1 $ 即可

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
 
#define $int long long
 
/***************快读***************/
 
namespace IO {
char buf[1<<21], *p1 = buf, *p2 = buf, buf1[1<<21];
inline char gc () {return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}
 
#ifndef ONLINE_JUDGE
#endif
 
#define gc getchar
 
template<class I>
inline void read(I &x) {
    x = 0; I f = 1; char c = gc();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = gc(); }
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = gc(); }
    x *= f;
}
 
template<class I>
inline void write(I x) {
    if(x == 0) {putchar('0'); return;}
    I tmp = x > 0 ? x : -x;
    if(x < 0) putchar('-');
    int cnt = 0;
    while(tmp > 0) {
        buf1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while(cnt > 0) putchar(buf1[--cnt]);
}
 
#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')
 
} using namespace IO;
 
/***************快读***************/
 
#define maxn 1000010
 
int T,n;
int a[maxn];
bool vis[maxn];
 
int dabiao[]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
 
char s[maxn];
 
int main(){
	read(T);
	for(int i=1;i<=25;i++){vis[dabiao[i]]=1;}
	while(T--){
		// puts("");
		bool flag=false;
		read(n);
		::cin>>(s+1);
		for(int i=1;i<=n;i++){a[i]=s[i]-'0';}
		for(int i=1;i<=n&&flag==false;i++){if((a[i]%2==0&&a[i]!=2)||a[i]==9||a[i]==1){outn(1);outn(a[i]);flag=true;}}
		for(int i=1;i<=n&&flag==false;i++){
			for(int j=i+1;j<=n&&flag==false;j++){
				if(!vis[a[i]*10+a[j]]){
					outn(2);
					outn(a[i]*10+a[j]);
					flag=true;
				}
			}
		}
		// puts("");
	}
	return 0;
}
```


---

## 作者：pufanyi (赞：0)

窝萌考虑尽量批量解决一些能解决数。

考虑到如果一个数字含有 $1, 4, 6, 8, 9$，那么这个数只要保留这一位即可，而其余情况均需保留两位。

如果没有这些数，也就是只有 $2, 3, 5, 7$，如果存在两个数字相同，那么只要保留这两个数字就一定被 $11$ 整除，于是位数大于等于 $5$ 位的数字都解决了。

然后考虑到只要 $2$ 和 $7$、$5$ 和 $7$ 在一起，那么取这两个数就一定被 $3$ 整除，于是 $4$ 位数也解决了。

然后如果 $2$ 和 $5$ 不放在第一位，那么就可以整出一个尾数是 $2$ 或尾数 $5$ 的两位数，分别被 $5$ 和 $2$ 整除。

也就是说现在窝萌还不能解决的应该是个三位数，又因为 $2$ 和 $5$ 至少会有一个数被选进这个三位数（$2, 3, 5, 7$ 四个数里选三个嘛），所以 $7$ 就不能来了，这样 $2, 3, 5$ 一定要进场，但是 $2$ 和 $5$ 又都要在开头，所以是不可能的。

于是窝萌发现其实两位及以上的数字窝萌都只需要上面说的 $4$ 个特判就可以了。

总结一下，先判有没有 $1, 4, 6, 8, 9$，如果没有看有没有同时出现 $2$ 和 $7$、$5$ 和 $7$，如果还没有，那我看一下有没有不放在开头的 $2$ 和 $5$。这样就能覆盖到所有可行的数字了。

---

## 作者：HerikoDeltana (赞：0)

## CF1562B Scenes From a Memory

稍微有点绕的一道题，不过也不算难。

### 题意简述

给出一个长度为 $k$ 且不含 $0$ 的字符串，求字符串内包含的最短非质数。

这里的非质数指 $1$ 和合数。

### 思路简述

因为这个题是要求字符串内包含的最短非质数，于是我们就从最短的情况依次考虑：

#### 答案长度为 1

当字符串中存在小于 $10$ 的非质数时（即存在 $1,4,6,8,9$ 时），此时答案即为这个非质数，长度为 $1$。

若不存在小于 $10$ 的非质数，说明此字符串由 $2,3,5,7$ 组成，说明不存在长度为 $1$ 的答案。

#### 答案长度为 2

显然，当字符串中存在多个相同的数字时，这个数字重复两次组成的两位数即为最短答案。

剩下的情况没有什么特殊的性质，只能判断是否为质数。

而当字符串长度为 $3$ 时，总能从中选取两个数组结合为一个非质数，因为更长的字符串都可以先转化为长度为 $3$ 的字符串再求解，所以答案的长度最长为 $2$。

于是我们只需要筛一遍素数判断即可。

### Code

```cpp
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cstring>
#define Heriko return
#define Deltana 0
#define Romanno 1
#define S signed
#define LL long long
#define R register
#define I inline
#define CI const int
#define mst(a, b) memset(a, b, sizeof(a))
#define ON std::ios::sync_with_stdio(false);cin.tie(0)
using namespace std;

template<typename J>
I void fr(J &x)
{
    static short f(1);
    char c=getchar();
    x=0;
    while(c<'0' or c>'9')
    {
        if(c=='-') f=-1;
        c=getchar();
    }
    while (c>='0' and c<='9') 
    {
        x=(x<<3)+(x<<1)+(c^=48);
        c=getchar();
    }
    x*=f;
}

template<typename J>
I void fw(J x,bool k)
{
    x<0?x=-x,putchar('-'):1;
    static short stak[35],top(0);
    do
    {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);
    while(top) putchar(stak[--top]+'0');
    k?puts(""):putchar(' ');
}

int t,k;

int a[10001];

char s;

bool prime[85];

I void Pre()
{
    for(R int i(2);prime[i]=1,i<=80;++i)
        for(R int j(2);j*j<=i;++j)
            if(!(i%j))
                prime[i]=0;
        
}

S main()
{
    Pre();
    fr(t);
    while(t--)
    {
        fr(k);bool flag(0);
        for(R int i(1);i<=k;++i) cin>>s,a[i]=s-'0';
        for(R int i(1);i<=k;++i) 
        {
            if(a[i]==1 or a[i]==9 or a[i]==4 or a[i]==6 or a[i]==8)
            {
                puts("1");
                fw(a[i],1);
                flag=1;
                break;
            }
        }
        if(flag) continue;
        for(R int i(1);i<=k and !flag;++i)
            for(R int j(i+1);j<=k;++j)
                if(!prime[(a[i]<<3)+(a[i]<<1)+a[j]])
                {
                    puts("2");
                    printf("%d%d\n",a[i],a[j]);
                    flag=1;
                    break;
                }
        if(flag) continue;
    }
    Heriko Deltana;
}
```

---

## 作者：LRL65 (赞：0)

### 题意：

有一个 $k$ 位的数，要删除尽量多的位数，是得这个数为非质数（ $1$ 也包含），保证能删除少于 $k$ 位，使得这个数为非质数，并且在任何位上不会出现 $0$ 。输出剩下的位数和剩下的数。

### 思路：

1. 如果数中出现 $1、4、6、8、9$ ，直接输出这一位即可。
1. 如果数中只出现 $2、3、5、7$ ，因为题目保证能成为非质数，所以不能只出现一个数字。如果出现任意两个数字，那么除了 $23、37、53、73$ 其它都是非质数。题目中保证能删除成为非质数，所以当出现 $23、37、53、73$ 时，此数肯定不止两位（不然就不保证了），那么如果有任意一位，都能凑成一个两位的非质数。所以，我们只需暴力选取数中的任意两位，必有一个数是非质数。

总结一下，当出现 $1、4、6、8、9$ 时，直接输出。否则必有一个两位数是非质数。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,k;
string s;
int vis[15];
int main() {
    cin>>t;
    while(t--) {
        cin>>k>>s;
        memset(vis,0,sizeof(vis));
        for(int i=0;i<k;i++)
            vis[(int)(s[i]-'0')]++;
        bool flag=0;
        for(int i=1;i<=9;i++) {
            if(vis[i]>=1) {
                if(i==1||i==4||i==6||i==8||i==9) {
                    cout<<1<<endl<<i<<endl;
                    flag=1;
                    break;
                }
            }
        }
        if(flag==0) {
            bool flag2=0;
            for(int i=0;i<k;i++) {
                for(int j=i+1;j<k;j++) {
                    int p=(s[i]-'0')*10+(s[j]-'0');
                    if(p!=23&&p!=37&&p!=53&&p!=73) {
                        cout<<2<<endl<<p<<endl;
                        flag2=1;
                        break;
                    }
                }
                if(flag2==1)break;
            }
        }
    }
}
```


---

## 作者：Cocoly1990 (赞：0)

很牛逼的题目。

大概就是给你一个很长的数，问你**最多**能删掉几位使得剩下的数是合数，保证有解。

显然如果有某一位是合数，那么只保留这一位就好了，思考如果序列全为质数怎么办。看数据范围。明显的，这题 $\mathcal{O}\left(k^2\right)$ 可以过。

考虑猜结论，就是最后保留的数不可能超过 $2$ 个，这个很好证明，然后就随便枚举一下字符串就好了。

可是出题人的标答告诉了你一个迷惑的结论。

```
It can be shown that such a brute-force solution will work for O(k).

Asymptotics: O(k) per test case.
```

就是最后对于每一个测试点是渐进于 $\mathcal{O}\left(k\right)$ 的。

然后贴了一个证明，就是对于每三位数字，如果把它们两两分组，总能找到答案，所以这样可以做到 $\mathcal{O}\left(k\right)$ 。

当然了他还教你怎么做到 $\mathcal{O}\left(k^2\right)$，有兴趣的可以去看看。

[My submission](https://codeforces.com/contest/1562/submission/127103495)

[出题人标算](https://codeforces.com/blog/entry/94278)


---

## 作者：reailikezhu (赞：0)

首先有一个结论，就是所剩的数位数最多不超过 $2$。

首先，对于每一位判断有没有 $1,4,6,8,9$。如果有直接输出。

否则，对于所有由 $2,3,5,7$ 组成的两位合数一一判断。

可以先判断有没有两个 $2,3,5,7$，如果有直接输出。

否则记录下每一个 $2,3,5,7$ 中的数的位置，一一判断 $2,3,5,7$ 中没有重复数字的合数。

判断的方式就是看这个合数的十位数在 $n$ 中是否在其个位数的前面，如果是，输出，如果不是，继续判断。

代码：
```cpp
#include<stdio.h>
#include<string.h>

int t;
int k;
char a[55];

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&k);
		scanf("%s",a+1);
		int flag1=0;
		for(int i=1;i<=k;i++){
			if(a[i]=='1'||a[i]=='4'||a[i]=='6'||a[i]=='8'||a[i]=='9'){
				printf("1\n%d\n",a[i]-'0');
				flag1=1;
				break;
			}
		}
		if(flag1==1) continue;
		int sum[10];
			memset(sum,0,sizeof(sum));
			for(int i=1;i<=k;i++) sum[a[i]-'0']++;
			bool flag=0;
			for(int i=2;i<=7;i++){
				if(sum[i]>=2){
					printf("2\n%d%d\n",i,i);
					flag=1;
					break;
				}
			}
			if(flag) continue;
			int pos[10];
			memset(pos,0,sizeof(pos));
			for(int i=1;i<=k;i++) pos[a[i]-'0']=i;
			if(pos[2]!=0){
				if(pos[5]>pos[2]){
					printf("2\n25\n");
					continue;
				}
				if(pos[7]>pos[2]){
					printf("2\n27\n");
					continue;
				}
			}
			if(pos[3]!=0){
				if(pos[2]>pos[3]){
					printf("2\n32\n");
					continue;
				}
				if(pos[5]>pos[3]){
					printf("2\n35\n");
					continue;
				}
			}
			if(pos[5]!=0){
				if(pos[2]>pos[5]){
					printf("2\n52\n");
					continue;
				}
				if(pos[7]>pos[5]){
					printf("2\n57\n");
					continue;
				}
			}
			if(pos[7]!=0){
				if(pos[2]>pos[7]){
					printf("2\n72\n");
					continue;
				}
				if(pos[5]>pos[7]){
					printf("2\n75\n");
					continue;
				}
			}
	}
	return 0;
}
```

---

## 作者：Chouquet (赞：0)

因为有多组解时输出任意解，所以这题没那么麻烦。

+ $k=1$ 时直接输出 $k,n$，因为题目保证有解，而此时 $k$ 一定为合数或 $1$。

+ 如果 $n$ 中有一位是 $1$ 或合数，那么直接保留这位数就行了。

+ 否则，$n$ 中只包含 $2,3,5,7$，其中 $2,5$ 只能在首位，且 $n$ 中没有数字重复。假设 $n = 3$（$n = 2$ 时一定有解）：
	
    - 首位为 $2$：
    
    	$n$ 可能为 $237,273$，此时 $27$ 构成合数。
        
	- 首位为 $5$：
    	
    	$n$ 可能为 $537,573$，此时 $57$ 构成合数。
        
    - 首位为 $3,7$
    
    	因为其它位不能是 $2,5$，而且只能出现一次，所以这种情况不存在。
        
	因此 $n=3$ 时一定有解，且一定有两位数能构成合数，$n=4,5,6\dots$ 时更是这样。所以这种情况只需要判断 $n$ 中是否有两位数为合数，保留这两位就行。
    
时间复杂度最坏 $O(tk^2)$，代码：

```cpp
#include <cstdio>
char n[53];
int t, k;
bool notprime(int x) {//判断x是否为1或合数
    if (x == 1)
        return 1;
    for (int i = 2; i * i <= x; i++)
        if (!(x % i))
            return 1;
    return 0;
}
int judge() {//判断n中是否有一位是1或合数，-1表示无
    int pos = -1;
    for (int i = 0; i < k; i++)
        if (notprime(n[i] - '0')) {
            pos = i;
            break;
        }
    return pos;
}
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%s", &k, n);
        if (k == 1)//k=1时原样输出
            printf("%d\n%s\n", k, n);
        else {
            int pos = judge();
            if (pos != -1)//如果有就直接保留这一位
                printf("1\n%c\n", n[pos]);
            else {
                bool ok = 0;
                //判断n中是否有两位能构成合数
                for (int i = 0; i < k - 1; i++) {
                    int s = n[i] - '0';
                    for (int j = i + 1; j < k; j++)
                        if (notprime(s * 10 + (n[j] - '0'))) {
                            ok = 1;
                            printf("2\n%d\n", s * 10 + (n[j] - '0'));//保留这两位
                            break;
                        }
                    if (ok)
                        break;
                }
                if (!ok)//这种情况其实不存在
                    puts("-1");
            }
        }
    }
    return 0;
}
```

---

