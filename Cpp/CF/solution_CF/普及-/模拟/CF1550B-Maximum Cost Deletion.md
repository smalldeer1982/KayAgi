# Maximum Cost Deletion

## 题目描述

You are given a string $ s $ of length $ n $ consisting only of the characters 0 and 1.

You perform the following operation until the string becomes empty: choose some consecutive substring of equal characters, erase it from the string and glue the remaining two parts together (any of them can be empty) in the same order. For example, if you erase the substring 111 from the string 111110, you will get the string 110. When you delete a substring of length $ l $ , you get $ a \cdot l + b $ points.

Your task is to calculate the maximum number of points that you can score in total, if you have to make the given string empty.

## 说明/提示

In the first example, it is enough to delete the entire string, then we will get $ 2 \cdot 3 + 0 = 6 $ points.

In the second example, if we delete characters one by one, then for each deleted character we will get $ (-2) \cdot 1 + 5 = 3 $ points, i. e. $ 15 $ points in total.

In the third example, we can delete the substring 00 from the string 100111, we get $ 1 \cdot 2 + (-4) = -2 $ points, and the string will be equal to 1111, removing it entirely we get $ 1 \cdot 4 + (-4) = 0 $ points. In total, we got $ -2 $ points for $ 2 $ operations.

## 样例 #1

### 输入

```
3
3 2 0
000
5 -2 5
11001
6 1 -4
100111```

### 输出

```
6
15
-2```

# 题解

## 作者：tongzhenxuan (赞：1)

# Solution
首先，本题采用了一种贪心的策略。题目要求我们使删除之后的费用越大。而删除一段长 $l$ 的字串可以得到 $a \times l+b$ 的费用。我们用 $fa$ 代表有关与 $a$ 的费用，用 $fb$ 代表有关 $b$ 的费用，并设共删除 $m$ 次。

总费用 $f=fa+fb$。

抛开 $+b$ 这一项，我们发现，最后整理有关 $a$ 项的费用可得：

1. $f_a = a \times \sum\limits_{i=1}^ml_i$;
2. $\sum\limits_{i=1}^ml_i = n$。

所以整理有关与 $a$ 的费用可得 $fa=a \times n$。

那么我们来看有关 $b$ 项的，显然，$b$ 的有关费用与删除的次数有关，即 $fb=m \times b$。

我们可以得出，$fa$ 是确定的，所以 $f$ 与 $fb$ 有关。

我们分两种情况讨论：

1.	$b > 0$ 此时需要删除的次数越多越好，即将每一个字母都删一边，可的最大值 $fb=n\times b$;
2.	$b = 0$ 此时 $fb=0$，$f$ 与 $fb$ 无关;
3.	$b < 0$ 此时需要删除的次数越少越好，所以我们可以把先把 $1$ 的串全删掉或把 $0$ 的串全删掉（取 $1$ 的串数和 $0$ 的串数的较小值），最后一次把剩下的删掉。此时的删除次数是最少的。

最后输出 $fa+fb$ 即可。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[10000];
int n,m;
int a,b;
int main()
{
	
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>a>>b;
		cin>>ch;
		if(b>=0) cout<<a*n+b*n<<"\n";//若b=0对此处不造成影响，因为第二项值恒为0 
		else if(b<0)
		{
			int l=1;//最后的一边删 
			for(int i=1;i<n;i++) if(ch[i]!=ch[i-1]) l++;//因为是01子串相间所以连续字串总数l为连续为1串与连续为0串的和，所以l/2的向下取整便是较小的连续为1或连续为0串。 
			cout<<a*n+b*(l/2+1)<<"\n";
		}
	}
	return 0; 
} 
```

---

## 作者：wheneveright (赞：1)

## 题意

给出一个 $\text{01}$ 序列，每次可以删除一段连续的子串，这个子串中每个数都必须相同，删除一段长度为 $l$ 的子串你会获得 $l \times a + b$ 的值，现在，你要清空这个序列，而且你要让你获得的值尽量大，请输出最大的值。

## 分析

可以证明无论如何都要有 $a \times n$ 的值（乘法分配律），然后再可以思考 $b$ 的大小对序列结果的影响。

首先如果 $0\le b$，那么我就要尽可能多的删除次数，那么就可以一个一个删除数字，获得的值是 $b\times n$。

然后考虑 $b < 0$，我们要尽可能少的删除次数，考虑将每一段连续的相同的串的长度对结果没有影响，只有每个元素相同的串的个数对长度有影响，那么 $O(n)$ 搞出每个元素相同的串的个数 $cnt$，那么最优的情况是从最中间往外取，多造几个情况试试就知道应该是 $\lfloor \frac {cnt} 2 \rfloor + 1$ 次，这个 $+1$ 是代表无论如何都要在最中间取一次才能让两边的数合并。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

int T, N, A, B, res;
char s[105];

int main () {
	cin >> T;
	while (T--) {
		cin >> N >> A >> B >> s + 1;
		if (B < 0) {
			int cnt = 0; res = A * N;
			for (int i = 1; i <= N; i++) {
				cnt++;
				while (s[i + 1] == s[i] && i + 1 <= N) i++;
			}
			cout << A * N + (cnt / 2 + 1) * B << endl;
		}
		else cout << (A + B) * N << endl;
	}
	return 0;
}
```

---

## 作者：KSToki (赞：1)

# 题目大意
给定一个长度为 $n$ 的 $01$ 串和系数 $a$ 和 $b$（可能为负数），你可以对其进行任意次操作，每次操作需删除长度为 $l$ 的连续的一段 $0$ 或 $1$。并将得到 $a\cdot l+b$ 的收益，要求最大化收益。
# 题目分析
对于 $a$ 的贡献，始终会是 $\sum l\cdot a=n\cdot a$，所以影响收益的在于 $b$。若 $b$ 为正数，那操作次数越多越好，即一个一个删；否则操作次数越少越好，即每次需完全消除一段 $0$ 或 $1$。这里我们可以 dp，但没有必要，只需统计 $0$ 或 $1$ 交替的总段数 $cnt$，随手一推就可以知道答案为 $(cnt/2+1)\cdot b$。
# 代码
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
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
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
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
int T,n,a,b,s[101],f[101][101]; 
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		a=read();
		b=read();
		for(R int i=1;i<=n;++i)
			scanf("%1d",&s[i]);
		if(b>0)
			putint(n*(a+b));
		else
		{
			int lst=1,cnt=1;
			for(R int i=2;i<=n;++i)
				if(s[i]!=s[lst])
				{
					lst=i;
					++cnt;
				}
			putint(n*a+(cnt/2+1)*b);
		}
	}
	return 0;
}
```


---

## 作者：Jur_Cai (赞：1)

### 大意
有一个01字符串，每次可以删去一段连续的0或1，删除一段长为 $ l $ 的字符串可得到 $ a\ast l + b $ 分，求最大分数。

------------

由于字符串最后必须变为空串，显然 $ a \ast l$ 合并同类项后为 $ a \ast n $ 故只需让 $ b $ 最大化即可。

由于 $ + b $ 的次数与删除次数有关所以分类讨论

- 当 $ b \ge 0 $ 时，取的越多越好，操作 $ n $ 次
- 当 $ b < 0 $ 时，取得越少越好，可以证明，先全部删去连续区间数量较少的，再一下把另一个全删了，操作次数最少

举个例子 $10011001$

最优解：$10011001 \Rightarrow 1111 \Rightarrow $ 空串

错解 $10011001 \Rightarrow 111001 \Rightarrow 001 \Rightarrow 1 \Rightarrow $ 空串

可见每个0串还是得单独删去，而1串删除的操作分为两步，故不如最优解。


------------

这样就很好实现了
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
char s[105];
int main()
{
	int t; 
	scanf("%d",&t);
	while(t--)
	{
		int n,a,b;
		scanf("%d%d%d",&n,&a,&b);
		scanf("%s",s);
		int ans=n*a;
		if(b>=0) ans+=b*n;
		else
		{
			int sum0=0,sum1=0;
			for(int i=0;i<n;)
			{
				if(s[i]=='0')
				{
					sum0++;
					while(s[i]=='0'&&i<n) i++;
				}
				else 
				{
					sum1++;
					while(s[i]=='1'&&i<n) i++;
				}
			}
			ans+=b*(min(sum0,sum1)+1);
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：Aw顿顿 (赞：0)

## 题意

给定一个 $01$ 串，每次删除一个长度为 $l$ 的区间获得 $al+b$ 的收益，问最大收益是多少。

## 分析

其实我们对于 $a$ 的贡献是不关心的，因为它无论如何都是 $an$，毕竟我们最后所有的区间都要删除，总和长度一定就是 $n$，这是毋庸置疑的。

对于 $b$，如果是一个正的贡献，我们当然希望它尽可能多，所以我们每一个字符当做单一的区间进行操作，会产生 $bn$ 的贡献，总答案显然就是 $(a+b)n$。

但是如果 $b$ 是负数呢？我们就考虑能够成块删除的区间，一共有 $tot$ 个，这样我们通过让他们隔块合并一起删除，这样得到一共会操作 $\left\lfloor\dfrac{tot}{2}\right\rfloor+1$ 次，因此把答案再加上 $an$ 就好了。

## 代码

这个代码要实现是极其容易的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,b;
string s;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>a>>b>>s;
		if(b>=0)cout<<(a+b)*n<<endl;
		else{
			int tot=0;
			for(int i=0;i<n;i++){
				tot++;
				while(s[i+1]==s[i]&&i<n-1)i++;
			}cout<<a*n+b*(tot/2+1)<<endl;
		}
	}return 0;
}
```

---

## 作者：xkcdjerry (赞：0)

由乘法分配律可得，分数为 $a \times n + b \times op$ （ $op$ 为操作次数）。  

如 $b \leqslant 0$ ，则需要最大化操作次数，显然是一个个去，答案最大为 $an+bn$ 。  

如 $b<0$ ：  
显然，如有 $x$ 个 A 串和 $y$ 个 B 串 ( $x \leqslant y$ )  
那么尽可能少的去除次数显然为 $x+1$ 次（去除 $x$ 次 A ，一次去完所有 B ）  
因为如果 A 没有去完而去去 B 的，最多每去一次 B 连起来两个 A 的，即多一次 B 省一次 A ，显然没有更优。  
故答案最大为 $(x+1)b+na$ 。  

代码：
```cpp
/*
    Code by xkcdjerry
    Time: 2021-07-14
    Generated by cf-tools
*/
#include <cstdio>

#define int long long
#define N 110
char s[N];
void once()
{
    int n,a,b;
	scanf("%lld%lld%lld%s",&n,&a,&b,s);
	if(b>=0)
	{
		printf("%lld\n",(a+b)*n);
		return;
	}
	else
	{
		int run0=0,run1=0;
		int p=0;
		while(p!=n)
		{
			if(s[p]=='0')
			{
				while(s[p]=='0') p++;
				run0++;
			}
			else
			{
				while(s[p]=='1') p++;
				run1++;
			}
		}
		printf("%lld\n",run0<run1?(run0+1)*b+n*a:(run1+1)*b+n*a);
	}
}
#undef int


int main()
{
    int t;
    scanf("%d",&t);
    while(t--) once();
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/53429648)

---

## 作者：_ajthreac_ (赞：0)

观察题中给出的贡献 $al+b$，我们发现如果把一段长度为 $l$ 的相同字符拆成两段长度为 $l_1,l_2$ 分别删除，那么贡献是 $al_1+b+al_2+b=al+2b$，比整段删多了一个 $b$。

那么就可以给出一个贪心策略：如果 $b$ 为正数，那么分的段数越多越好，直接分别删除每个字符；否则，我们要尽量让一次删除的更长，观察可知我们应该统计出每段的长度，由于这些段一定是 $\texttt{01}$ 交错的，然后看哪种字符段数少就先删，最后把另一种字符一起删掉。

核心代码：
```cpp
int T,n,a,b;char s[110];
int main(){
  Read(T);
  while(T--){
    Read(n),Read(a),Read(b);
    scanf("%s",s+1);
    if(b>=0)cout<<(LL)n*(a+b)<<endl;
    else {
      int cnt0=0,cnt1=0;
      for(rg int i=1;i<=n;i++){
        if(s[i]!=s[i-1]&&s[i]=='0')cnt0++;
        else if(s[i]!=s[i-1]&&s[i]=='1')cnt1++;
      }
      int mn=min(cnt0,cnt1);
      cout<<(LL)a*n+(LL)b*(mn+1)<<endl;
    }
  }
  KafuuChino HotoKokoa
}
```

---

## 作者：ʕ•ﻌ•ʔ (赞：0)

传送门：[CF题面](https://codeforces.com/contest/1550/problem/B)。

## 题目大意：
给你一个长度为 $n$ 的 $01$ 串，你每次可以选择一段连续的 $0$ 或 $1$ 将其删除，每次删除你将得到：$a \times l +b$ 分，其中的 $l$ 为你删除的串的长度。你最后要将这个串**全部删掉**。

输出 $n \ \ a\ \ b$ 。

输出你能得到的**最高分**。

---

## 题目分析：

观察得分的式子不难发现，既然我们要将整个串都删光，那每次得分的 $a \times l$ 部分最后就等于 $a \times n$ 。

也就是说，不同的删法只会使后面的 $+b$ 部分有所差别。如果 $b$ 大于等于  $0$ ，那删的次数越多越好。显然，一个一个的删得分最高。反之，删的次数越少越好。

经过以上步骤，我们把问题转化为“给定一个$01$串，怎么删能删的次数最少”。

例：对于串“ $1110011001$ ”，在真正操作的时候是不是可以看作“ $10101$ ”？**（不管有几个 $1$ 或者 $0$ ，是不是都只要删一次？）**

我们用 $f$ 数组记录一下真正要进行操作的序列，数组长度为 $num$ 。

那么我们有了一个长为 $num$ 的数组之后又该删几次才是最少呢？

比如“ $10101$ ”,是不是把 $0$ 删光了之后再删一次就可以了？ $0$ 的个数为 $num/2$ 。

## AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b,ans,n,num;
int f[100010];
string s;
inline void sol(){
	memset(f,0,sizeof(f));
	cin>>n>>a>>b>>s;
	ans=a*n;
	int now=s[0]-'0';num=1;
	f[1]=now;
	for(int i=1;i<n;i++){
		if(s[i]-'0'==now)
			continue;
		else f[++num]=s[i]-'0',now=s[i]-'0';
	}
	if(b<=0) 
		ans+=(num/2+1)*b;
	else ans+=b*n;
	cout<<ans<<endl;
} 
int main(){
	cin>>t;
	while(t--) sol();
	return 0;
}
```


---

## 作者：yzh_Error404 (赞：0)

我们先观察题目给出的式子 $l \times a +b$ 。

不难发现 $\sum{l}=n$ ， 所以 $l \times a$ 的部分就变成了定值，只需重点考虑 $b$ 的部分。

将 $b$ 分类讨论可分为两种情况：

1. $b \geq 0$ 时，删的次数越多越好，次数最多为 $n$ 次，答案为 $n \times a+n \times b$ 。

2. $b \lt 0$ 时，次数当然是越少越好，要次数最少，应当先把连续区间少的删掉，留下所有的某一种数，再一次性删掉，区间数在输入时统计即可（即代码中的 $sum_z$ 和 $sum_o$），答案为 $n \times a+\min(sum_z,sum_o)\times b+b$

具体实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=105;
int t;
int n,a,b;
char q[MAXN];//因为输入序列中没有空格，于是用了char数组
int sum_z,sum_o;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		sum_z=0,sum_o=0;
		scanf("%d%d%d",&n,&a,&b);
		for(register int i=0;i<n;i++)
		{
			cin>>q[i];
			if(q[i]=='0'&&q[i-1]!='0')sum_z++;
			if(q[i]=='1'&&q[i-1]!='1')sum_o++;//统计0/1区间
		}	
		if(b>=0)printf("%d\n",(a+b)*n);//上面的情况1
		else //情况2
		{
			int ans=n*a;
			if(sum_z<sum_o)ans+=(sum_z+1)*b;
			else ans+=(sum_o+1)*b;
			printf("%d\n",ans);
		}
	}
	return 0;
}


```

---

