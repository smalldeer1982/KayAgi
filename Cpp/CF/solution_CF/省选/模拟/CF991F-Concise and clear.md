# Concise and clear

## 题目描述

Vasya is a regular participant at programming contests and is already experienced in finding important sentences in long statements. Of course, numbers constraints are important — factorization of a number less than 1000000 is easier than of a number less than 1000000000. However, sometimes it's hard to understand the number at the first glance. Could it be shortened? For example, instead of 1000000 you could write $ 10^{6} $ , instead of 1000000000 — $ 10^{9} $ , instead of 1000000007 — $ 10^{9}+7 $ .

Vasya decided that, to be concise, the notation should follow several rules:

- the notation should only consist of numbers, operations of addition ("+"), multiplication ("\*") and exponentiation ("^"), in particular, the use of braces is forbidden;
- the use of several exponentiation operations in a row is forbidden, for example, writing "2^3^4" is unacceptable;
- the value of the resulting expression equals to the initial number;
- the notation should consist of the minimal amount of symbols.

Given $ n $ , find the equivalent concise notation for it.

## 说明/提示

The third sample allows the answer 10^10 also of the length $ 5 $ .

## 样例 #1

### 输入

```
2018
```

### 输出

```
2018
```

## 样例 #2

### 输入

```
1000000007
```

### 输出

```
10^9+7
```

## 样例 #3

### 输入

```
10000000000
```

### 输出

```
100^5
```

## 样例 #4

### 输入

```
2000000000
```

### 输出

```
2*10^9
```

# 题解

## 作者：大菜鸡fks (赞：8)

非常简单的题。

仔细想一下会发现一定是大于根号n的数加上一个“简单数”表示的

预处理大于根号的幂次数

小于根号的幂次数一定是“原数”最优

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
map<ll,string>mp;
ll n;
int main(){
	scanf("%I64d",&n);
	for (ll i=2;i*i<=n;i++){
		for (ll j=i*i,k=2;j<=n;j*=i,k++){
			string tmp=to_string(i)+"^"+to_string(k);
			if (!mp.count(j)) mp[j]=to_string(j);
			if (tmp.size()<mp[j].size()) mp[j]=tmp;
		}
	}
	string ans=to_string(n);
	for (auto x:mp){
		string tmp="";
		ll k=n/x.first,b=n%x.first;
		if (k>1) tmp=(mp.count(k)?mp[k]:to_string(k))+"*";
		tmp+=x.second;
		if (b) tmp+="+"+(mp.count(b)?mp[b]:to_string(b));
		if (tmp.size()<ans.size()) ans=tmp; 
	}
	cout<<ans<<endl;
	return 0;
} 
```




---

## 作者：Eznibuil (赞：3)

首先预处理所有可能的 `a^b`。显然这是 $O(\sqrt n\log^2n)$ 的。

很容易发现如果不是原数则必定有 `^`。手玩一下有以下几种情况：
1. `a`
1. `a^b`
1. `a+b^c`
1. `a*b^c`
1. `a+b*c^d`
1. `a^b+c^d`
1. `a^b*c^d`
1. `a+b^c+d^e`
1. `a*b^c+d^e`
1. `a+b^c*d^e`
1. `a*b^c*d^e`

然后可以发现 8 不可能，因为最大也就 $9+9^9+9^9=774840987$，跟直接写原数一样。剩下的都只有一个 `+`。

9、10、11 都是全部个位数，暴力枚举就好。2、4、7 没有加号，所以随手分解一下即可，$O(\sqrt n\log n)$。接着发现 3、6 形式差不多，枚举其中形如 `a^b` 的项即可，$O(\sqrt n\log^2n)$。最后 5 稍稍费点计算量，需要先枚举 `c^d` 再枚举 `b` 所占的宽度得到最小的 `a`，$O(\sqrt n\log^3n)$。
```cpp
#include<iostream>
#include<map>
#include<string>
int main()
{
	std::cin.tie(nullptr)->sync_with_stdio(0);
	long long n;
	std::cin>>n;
	std::map<long long,std::string>e;
	for(long long i=2;i*i<=n;i++)
		for(long long j=i*i,k=2;j<=n;j*=i,k++)
		{
			std::string x=std::to_string(i)+"^"+std::to_string(k);
			if(!e.count(j))
				e[j]=std::to_string(j);
			if(e[j].size()>x.size())
				e[j]=x;
		}
	std::string ans=e.count(n)?e[n]:std::to_string(n);
	const auto upd=[&](std::string x){ans.size()>x.size()?ans=x:ans;};
	for(long long i=1;i*i<=n;i++)
		if(n%i==0)
			if(e.count(i)&&e.count(n/i))
				upd(e[i]+"*"+e[n/i]);
			else if(e.count(i))
				upd(std::to_string(n/i)+"*"+e[i]);
			else if(e.count(n/i))
				upd(std::to_string(i)+"*"+e[n/i]);
	for(auto i:e)
		if(n>i.first)
		{
			if(e.count(n-i.first))
				upd(i.second+"+"+e[n-i.first]);
			else
				upd(std::to_string(n-i.first)+"+"+i.second);
			upd(std::to_string(n%i.first)+"+"+std::to_string(n/i.first)+"*"+i.second);
			for(long long j=9;i.first*j<n;j=j*10+9)
				upd(std::to_string(n-i.first*j)+"+"+std::to_string(j)+"*"+i.second);
		}
	for(int i=1;i<10;i++)
		for(int j=2;j<10;j++)
			for(long long k=j*j,_k=2;k<n&&_k<10;k*=j,_k++)
				for(int l=2;l<10;l++)
					for(long long m=l*l,_m=2;m<n&&_m<10;m*=l,_m++)
					{
						if(i+k*m==n)
							upd(std::to_string(i)+"+"+e[k]+"*"+e[m]);
						if(i*k+m==n)
							upd(std::to_string(i)+"*"+e[k]+"+"+e[m]);
						if(i*k*m==n)
							upd(std::to_string(i)+"*"+e[k]+"*"+e[m]);
					}
	std::cout<<ans;
	return 0;
}
```

---

## 作者：QwQcOrZ (赞：3)

因为一个数本身也可以作为答案，所以原串长度即为答案上限

然后发现一个数肯定会被拆分成 $A\times B+C$ 的形式，其中 $A,B,C$ 为不填或 $a^b$ 的形式

然后所有 $a^b$ 直接预处理的复杂度是对的，那么暴力预处理然后塞进 `map` 里，拆数时在 `map `里查询即可

```cpp
#include<bits/stdc++.h>
#define iter map<int,string>::iterator
#define int long long
#define x first
#define y second
using namespace std;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
map<int,string>num;

signed main()
{
	num.clear();
	int n=read();
	for (int i=2;i*i<=n;i++)
	for (int j=2,k=i*i;k<=n;j++,k*=i)
	{
		string now=to_string(i)+'^'+to_string(j);
		if (!num.count(k)) num[k]=now;
		if (num[k].length()>now.length()) num[k]=now;
	}
    //暴力预处理a^b
	string ans=to_string(n);
	for (iter i=num.begin();i!=num.end();i++)
	if (i->y.length()>to_string(i->x).length())
	i->y=to_string(i->x);
    //因为a^b这个串（由a^b构成的串）长度可能大于a^b这个数（a^b这单个数）的长度，所以要取个min
	for (iter i=num.begin();i!=num.end();i++)
	{
		string now=i->y;
		int a=i->x,b=n/a,c=n-a*b;
		if (!num.count(b)) num[b]=to_string(b);
		if (!num.count(c)) num[c]=to_string(c);
		if (b>1) now+='*'+num[b];
		if (c) now+='+'+num[c];
		if (ans.length()>now.length()) ans=now;
	}
    //拆A*B+C
	cout<<ans;

	return 0;
}
```

---

## 作者：奇米 (赞：3)

# 题解 - $\mathrm{CF991F}$

## 题目意思

[题目传送门](https://www.luogu.com.cn/problem/CF991F)

## $\mathrm{Sol}$

我的方法特别复杂，细节及其多，代码长达 $320$ 行

我们考虑构造形式：

$x=a+b\times c^d$

$x=c^d+e^f$

$x=c^d\times e^f+a$

$x=c^d\times b+a$

对于第一种情况我们暴力枚举 $c^d$ 可以轻松算出 $a,b$ 

对于 $c^d+e^f$ 这样的情况，我们可以先把 $f_{x}$ 表示 $x$ 用 $b^c$ 类型表示出来的最短长度。然后枚举 $c^d$ 同时可以记录 $e^f$ 的长度到最后统计答案的时候还原幂次形式即可。幂乘幂同理可得。

对于第三和四的情况我们可以枚举加的数 $a$ 再与上面同理的做法计算即可。

最后答案与本身长度去小即可。

```cpp
const int mod=1e9+7;
const int mo=998244353;
const int N=5e5+5;

int n,ans,P,BA,CS,Mul;
map<int,int> f;

inline int ksm(int x,int y)
{
	int ans=1ll;
	while(y)
	{
		if(y&1ll) ans=ans*x;
		x=x*x;
		y>>=1ll;
	}
	return ans;
}

inline int calc(int x)
{
	if(!x) return 0;
	return (int)log10(x)+1;
}

signed main()
{
	io.read(n);
	ans=calc(n);
	int S=sqrt(n);
	For(i,2,S) For(j,2,50)
	{
		int x=ksm(i,j);
		if(x>n) break;
		if(!f[x]) f[x]=calc(i)+calc(j)+1;
		else f[x]=min(f[x],calc(i)+calc(j)+1);
	}
	int base=2;
	int AA=0,BB=0,CC=0,Else=0,fll=0,FF=0;
	
	For(del,0,10)
	{
		int goal=n-del;
		base=2;
		for (;;)
		{
			if(base*base>goal) break;
			For(i,2,50)
			{
				int x=ksm(base,i);
				if(x>goal) break;
				int step=f[goal-x];
				if(!step&&x!=goal) continue;
				if(x==goal) 
				{
					int AD=calc(del)+(del>0);
					if(calc(base)+calc(i)+1+AD<ans) ans=AD+calc(base)+calc(i)+1,AA=base,BB=i,FF=del,CC=0;
				}
				else 
				{
					int AD=calc(del)+(del>0);
					if(calc(base)+calc(i)+2+step+AD<ans) ans=AD+calc(base)+calc(i)+2+step,AA=base,BB=i,CC=goal-x,Else=step,FF=del;
				}
			}
			base++;
		}
	}
	int Ans1=ans;
	int AAA=0,BBB=0,CCC=0,EElse=0,FFF=0;
	
	For(del,0,10)
	{
		int goal=n-del;
		base=2;
		for (;;)
		{
			if(base*base>goal) break;
			For(i,1,50)
			{
				int x=ksm(base,i);
				if(x>goal) break;
				if(goal%x) continue;
				int step=f[goal/x];
				if(!step&&x!=goal) continue;
				if(x==goal) 
				{
					int AD=calc(del)+(del>0);
					if(calc(base)+calc(i)+1+AD<ans) ans=AD+calc(base)+calc(i)+1,AAA=base,BBB=i,FFF=del,CCC=0;
				}
				else 
				{
					int AD=calc(del)+(del>0);
					if(calc(base)+calc(i)+2+step+AD<ans) ans=AD+calc(base)+calc(i)+2+step,AAA=base,BBB=i,CCC=goal/x,EElse=step,FFF=del;
				}
			}
			base++;
		}
	}
	
	int Ans2=ans;
	
	P=n;
	base=2;
	for (;;)
	{
		if(base*base>n) break;
		For(i,1,50)
		{
			int x=ksm(base,i);
			if(x>n) break;
			int rem=n/x;
			int A=calc(rem);
			if(rem==1) A=0;
			int B=calc(n-rem*x);
			if(f[n-rem*x]) B=min(B,f[n-rem*x]);
			int C=calc(i);
			int D=calc(base);
			if(n-rem*x) B++;
			if(i>1) C++;
			if(A>1) A++;
			if(A+B+C+D<ans) 
			{
				ans=A+B+C+D;
				P=n-rem*x;
				BA=base;
				CS=i;
				Mul=rem;
			}
		}
		base++;
	}
	
	if(ans==Ans2&&AAA&&BBB)
	{
		printf("%lld^%lld",AAA,BBB);
		int FFA=0,FFB=0;
		if(FFF)
		{
			int len=calc(FFF);
			if(f[FFF]<len)
			{
				For(i,2,S) For(j,2,50)
				{
					int x=ksm(i,j);
					if(x>FFF) break;
					if(x==FFF) 
					{
						if(calc(i)+calc(j)+1==f[FFF]) FFA=i,FFB=j;
					}
					if(FFA&&FFB) break;
				}
			}
		}
		if(CCC)
		{
			putchar('*');
			int DD=0,EE=0;
			For(i,2,S) For(j,2,50)
			{
				int x=ksm(i,j);
				if(x>n) break;
				if(x==CCC) 
				{
					if(calc(i)+calc(j)+1==EElse) DD=i,EE=j;
				}
				if(DD&&EE) break;
			}
			printf("%lld^%lld",DD,EE);
			if(FFF) 
			{
				putchar('+');
				if(FFA) printf("%lld^%lld",FFA,FFB);
				else printf("%lld",FFF);
			}
		}
		else if(FFF) 
		{
			putchar('+');
			if(FFA) printf("%lld^%lld",FFA,FFB);
			else printf("%lld",FFF);
		}
		return 0;
	}
	
	if(ans==Ans1&&AA&&BB)
	{
		printf("%lld^%lld",AA,BB);
		int FFA=0,FFB=0;
		if(FF)
		{
			int len=calc(FF);
			if(f[FF]<len)
			{
				For(i,2,S) For(j,2,50)
				{
					int x=ksm(i,j);
					if(x>FF) break;
					if(x==FF) 
					{
						if(calc(i)+calc(j)+1==f[FF]) FFA=i,FFB=j;
					}
					if(FFA&&FFB) break;
				}
			}
		}
		if(CC) 
		{
			putchar('+');
			int DD=0,EE=0;
			For(i,2,S) For(j,2,50)
			{
				int x=ksm(i,j);
				if(x>n) break;
				if(x==CC) 
				{
					if(calc(i)+calc(j)+1==Else) DD=i,EE=j;
				}
				if(DD&&EE) break;
			}
			printf("%lld^%lld",DD,EE);
			if(FF) 
			{
				putchar('+');
				if(FFA) printf("%lld^%lld",FFA,FFB);
				else printf("%lld",FF);
			}
		}
		else if(FF) 
		{
			putchar('+');
			if(FFA) printf("%lld^%lld",FFA,FFB);
			else printf("%lld",FF);
		}
		return 0;
	}
	if(P) 
	{
		int FFA=0,FFB=0;
		int len=calc(P);
		if(f[P]<len)
		{
			For(i,2,S) For(j,2,50)
			{
				int x=ksm(i,j);
				if(x>P) break;
				if(x==P) 
				{
					if(calc(i)+calc(j)+1==f[P]) FFA=i,FFB=j;
				}
				if(FFA&&FFB) break;
			}
		}
		if(FFA) printf("%lld^%lld",FFA,FFB);
		else printf("%lld",P);
	}
	if(BA) 
	{
		if(P) printf("+%lld^%lld",BA,CS);
		else printf("%lld^%lld",BA,CS);
	}
	if(Mul>1) printf("*%lld",Mul);
	return 0;
}
```


---

## 作者：SegTree (赞：0)

## 前言 / Preface
这也是题？
## 题意 / Statement
构造一个长度最短的只包含 $0\sim 9$ 和 `+*^` 的表达式（`^` 表示次幂），不能出现幂套幂，使其值为 $n$。

$n\le 10^{10}$。
## 题解 / Solution
特判 $n=10^{10}$ 的情况，则只需要考虑串长 $\le 9$ 时合法的所有串。

+ 注意到：串中不存在数字乘数字。证明：设两数字长度为 $a,b$，则乘法消耗的代价为 $a+b+1$，直接做代价也不超过 $a+b+1$。同样，显然的有不存在数字加数字。

因此，更优的串中一定存在次幂运算。又因为长度 $\le 9$ 启发对表达式的所有情况进行分类讨论。

下记 $m$ 为 $10^{10}$ 内 $a^b(a,b\in N^+,b>1)$ 的个数。

+ $a^b$
+ $a^bc$
+ $a^b+c$

以上三类都可以 $O(m)$ 枚举得到。

+ $a^bc^d$
+ $a^b+c^d$
+ $a^bc+d$

对于以上三类，由于此时对于任意一个元素，剩下的数和字符至少消耗 $6$ 的代价，所以只需要枚举 $a^b$ 中 $a<1000$ 的部分。运算量级约为 $1000^2$。

+ $a^bc^d+e$
+ $a^bc^de$
+ $a^bc+d^e$

这三种情况可以继续套用上面的做法，枚举 $a^b$ 和 $c^d$。

显然对于更长的串长度至少在 $11$ 以上，没有原数更优，因此只需要分类讨论以上情况。

---

