# String Equality

## 题目描述

Ashish has two strings $ a $ and $ b $ , each of length $ n $ , and an integer $ k $ . The strings only contain lowercase English letters.

He wants to convert string $ a $ into string $ b $ by performing some (possibly zero) operations on $ a $ .

In one move, he can either

- choose an index $ i $ ( $ 1 \leq i\leq n-1 $ ) and swap $ a_i $ and $ a_{i+1} $ , or
- choose an index $ i $ ( $ 1 \leq i \leq n-k+1 $ ) and if $ a_i, a_{i+1}, \ldots, a_{i+k-1} $ are all equal to some character $ c $ ( $ c \neq $ 'z'), replace each one with the next character $ (c+1) $ , that is, 'a' is replaced by 'b', 'b' is replaced by 'c' and so on.

Note that he can perform any number of operations, and the operations can only be performed on string $ a $ .

Help Ashish determine if it is possible to convert string $ a $ into $ b $ after performing some (possibly zero) operations on it.

## 说明/提示

In the first test case it can be shown that it is impossible to convert $ a $ into $ b $ .

In the second test case,

"abba" $ \xrightarrow{\text{inc}} $ "acca" $ \xrightarrow{\text{inc}} $ $ \ldots $ $ \xrightarrow{\text{inc}} $ "azza".

Here "swap" denotes an operation of the first type, and "inc" denotes an operation of the second type.

In the fourth test case,

"aaabba" $ \xrightarrow{\text{swap}} $ "aaabab" $ \xrightarrow{\text{swap}} $ "aaaabb" $ \xrightarrow{\text{inc}} $ $ \ldots $ $ \xrightarrow{\text{inc}} $ "ddaabb" $ \xrightarrow{\text{inc}} $ $ \ldots $ $ \xrightarrow{\text{inc}} $ "ddddbb" $ \xrightarrow{\text{inc}} $ $ \ldots $ $ \xrightarrow{\text{inc}} $ "ddddcc".

## 样例 #1

### 输入

```
4
3 3
abc
bcd
4 2
abba
azza
2 1
zz
aa
6 2
aaabba
ddddcc```

### 输出

```
No
Yes
No
Yes```

# 题解

## 作者：Miko35 (赞：7)

题意概述：

给两个字符串，有两种操作：

1. 交换相邻两个；

2. 将 $k$ 个连续相同的字母变为它的下一个字母（不能从 `z` 变为 `a`）。

问第一个通过若干次操作能否变为第二个。

---

由于没有操作次数的限制，很容易想到对于任意 $k$ 个相同的字符，他们都可以通过交换换到一起之后修改。而对于两个按照字母顺序排序之后相同的字符串，从第一个也可以经过若干交换换到第二个。

所以问题变成了：在两个可重集中，一次可将 $k$ 个相同的字母变为它的下一个，问是否能把第一个变成第二个。

这样的话就知道可以统计字母出现次数，然后从字母 `a` 开始到字母 `z`，每次把第一个串中当前字母的个数，通过变成下一个字母，变得和第二个串的个数一样，如果不可行就输出 `No`。这样就线性通过此题。

---

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,k;
char s1[1000010],s2[1000010];
int cnta[30],cntb[30]; 
int main(){
	cin>>t;
	while(t--){
		cin>>n>>k>>s1+1>>s2+1;
		memset(cnta,0,sizeof cnta);
		memset(cntb,0,sizeof cntb);
		for(int i=1;i<=n;i++){
			cnta[s1[i]-'a']++;
			cntb[s2[i]-'a']++;
		}
		for(int i=0;i<26;i++){
			if(cnta[i]>=cntb[i]){
				int c=cnta[i]-cntb[i];
				if(c%k!=0){
					puts("No");
					goto tag;
				}
				else{
					cnta[i]=cntb[i];
					cnta[i+1]+=c;
				}
			}
			else{
				puts("No");
				goto tag;
			}
		}
		puts("Yes");
		tag:;
	}
	return 0;
}

```


---

## 作者：henrytb (赞：2)

考虑开一个桶，然后在里面乱搞。

首先发现这两个字符串的顺序是可以随便打乱的。那么就是一个统计数量的问题了。

我开的桶数组 $aa_x$ 表示 $a$ 与 $b$ 中字符 $x$ 的数量差。

那么就可以从 `z` 到 `a` 考虑。因为操作 $2$ 只能让字符变大，不能变小，那么如果有地方需要让字符变小了（代码中的 `now<0`），就直接输出 `No` 。由于 $aa_x$ 是 $x$ 字符需要改变的量，而一次只能改变 $k$ 个字符，所以如果说有的字符的 $aa$ 值不整除于 $k$ 了，也得直接输出 `No`。

详细见代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
int _,n,k;
char a[1000005],b[1000005];
int aa[26];
int main(){
    for(scanf("%d",&_);_;--_) {
        scanf("%d%d",&n,&k);
        scanf("%s%s",a+1,b+1);
        memset(aa,0,sizeof(aa));
        rep(i,1,n) aa[a[i]-'a']++;
        rep(i,1,n) aa[b[i]-'a']--;
        int now=0;bool flg=1;
        per(i,25,0) {
            now-=aa[i];
            if(now<0||aa[i]%k!=0) {flg=0;break;}
        }
        if(flg) puts("Yes");
        else puts("No");
    }
    return 0;
}
```

---

## 作者：_hxh (赞：1)

## 题目核心

对字符串 $a$ 有 $2$ 种操作：

1. 交换相邻两个字符。

2. 选择一段区间 $a_i,a_{i + 1},\dots,a_{i + k - 1} (1 \le i \le n - k + 1)$，若区间内的字符都等于某个字符 $c (c \ne z)$，则可以把这段区间内的所有字符都变为 $(c + 1)$。

## 分析

题目并没有限制我们操作次数，所以我们实际上可以集中 $k$ 个字符统一修改。既然这样，我们为什么不开一个桶直接存储字符串 $a$ 和 $b$ 呢，直接集中所有相同的字符，非常方便。

注：打乱字符串 $b$ 的顺序并没有关系，因为我们可以进行操作 $1$。我们只需要记录每个字符的出现**次数**。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,k,a[30],b[30];
char c;
bool flag = 1;
int main()
{
	cin >> t;
	while (t--)
	{
		flag = 1; 
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b)); 
		cin >> n >> k;
		for (int i = 1;i <= n;i++)
		{
			cin >> c;
			a[c - 'a' + 1]++;//把 a~z 的字符转化成 1~26 数字，方便操作 
		}
		for (int i = 1;i <= n;i++)
		{
			cin >> c;
			b[c - 'a' + 1]++;//同上 
		}
		for (int i = 1;i <= 26;i++)
		{
			if (a[i] >= b[i])
			{
				if ((a[i] - b[i]) % k)//若差值不是是 k 的倍数，则无解 
				{
					cout << "No" << endl;
					flag = 0;
					break;
				}
				else//否则将多出来的部分加到下一组 
				{
					a[i + 1] += a[i] - b[i];
				}
			}
			else//因为只能向下转化（即 c 转化成 c+1），所以当 a[i] < b[i] 时就无解了 
			{
				cout << "No" << endl;
				flag = 0;
				break;
			}
		}
		if (flag)//中途没有输出 No 就输出 Yes 
			cout << "Yes" << endl;
	}
	return 0;
}
```

---

## 作者：RNTBW (赞：0)

## 题意

给两个字符串 $a,b$，与一个数 $k$，每次可以进行两个操作：

- 交换 $a$ 中的任意两个字符。

- 选中 $i$，如果 $a_i=a_{i+1}=...=a_{i+k-1}$ 则将这段区间内的字符全部 $+1$。

求**能否**将 $a$ 变成 $b$。

## 思路

由于 1 操作的存在，$a$ 序列的排列与答案无关。

那么问题就来到了如何使用 2 操作。

我们可以对 $a,b$ 根据字符排序，再用两个数组 $c1,c2$ 记录 $a,b$ 序列中每个字符出现的次数，再将相同的字符尽量配对。

排序后枚举每个字符 $i$：

1. $c1_i\geq c2_i$。

此时我们将 $a$ 序列与 $b$ 序列配对完后，又出现了两种情况：

- $c1_i-c2_i \bmod k>0$。

说明这几个剩下的字符无法被一次 2 操作处理完。

很显然，它们永远也不会被处理完，所以无解。

反之，则可以继续进行操作。

2. $c1_i<c2_i$。

那么 $b$ 序列反而会多几个字符。

由于我们的字符是从前往后枚举，所以之后便不会处理到字符 $i$ 了，$b$ 序列多的几个字符也不会被处理了。

所以也判断无解。

其实在实现的过程中，我们不需要真的对字符串排序，因为我们从小到大枚举字符，就已经实现了类似于桶排序的有序化处理。

## 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int c1[501],c2[501];
int t,n,m,i,k;
char a[1000001],b[1000001];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		scanf("%s%s",a,b);
		memset(c1,0,sizeof(c1));
		memset(c2,0,sizeof(c2));
		for(i=0;i<n;i++) c1[a[i]-'a']++,c2[b[i]-'a']++;//桶
		for(i=0;i<26;i++)
		{
			if(c1[i]<c2[i])break;
			k=c1[i]-c2[i];
			if(k%m)break;
			c1[i+1]+=k;//这一步相当于是把a配对后剩下的字符用几次2操作变成下一个字符，放到下一个字符去讨论
		}
		if(i>25)puts("Yes");
		else puts("No");
	}
	return 0;
}
```


---

## 作者：TEoS (赞：0)

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/14027537.html)


------------


**题意分析**

给出两个仅由小写字母组成的字符串 $a,b$ ，可以对字符串 $a$ 的字母进行顺序变换或者把连续的 $k$ 个相同的字母换为 ASCII 码更大的字母，求 $a$ 是否能变换成 $b$ 。

**思路分析**

显然对于类似冒泡的操作 $1$ ，相当于可以任意变换字母的顺序，因此我们只关心各个字母的个数。因为每次只能变换 $k$ 个相同的字母，那么需要变换的每个字母个数都一定要是 $k$ 的整数倍。还要注意判断是否可以变成更大的字母，即从小到大统计字母个数和然后比较即可，若字符串 $a$ 当前字母及之前的字母的个数比 $b$ 中的要大，则需要变成更小的字母，不合法。

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
int T,n,k,suma,sumb;
int cnta[30],cntb[30];
string a,b;
bool pd;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&k);cin>>a>>b;
		for(int i=0;i<26;i++)
			cnta[i]=cntb[i]=0;pd=suma=sumb=0;//初始化
		for(int i=0;i<n;i++)
			cnta[a[i]-'a']++,cntb[b[i]-'a']++;//统计每个字母的个数
		for(int i=0;i<26 && !pd;i++)
			pd=(abs(cnta[i]-cntb[i])%k>0)||((suma=suma+cnta[i])<(sumb=sumb+cntb[i]));//不能被 k 整除或需要变得更小则不合法
		puts(pd?"No":"Yes");
	}
	return 0;
}
```



---

## 作者：shihoghmean (赞：0)

## 题意

给定一个数$k$和两个只包含小写字母的字符串$a$和$b$。

对于字符串$a$，可进行下列两种操作：

1. 交换任意两个相邻的字母。

2. 若在长度为$k$的连续子串中，所有字母都相同，则把所有字母变成下一个字母（$z$不能变成$a$）。

问字符串$a$能否变成与$b$。

## 思路

对于操作$1$，显然可使字符串$a$变成任意顺序的字符串，又因为题目要求的步骤不限，所以可以不看字母在字符串中的位置，只需要存字符串中的每种字母数即可。

对于操作$2$，因为操作$1$，可知只要有$k$个相同的字母就可以将这$k$个字母变成任意$k$个大于等于原先的字母。

又因为无法对$b$进行修改，所以只要从最小的字母往上扫（因为操作$2$只能从小变到大）。

设一种字母字符串$a$中的数量为$A$,可以变成这种字母的其他字母的数量为$L$,这种字母在$b$中的数量为$B$，若$A+L<B$或 $ \left| A+L-B \right|$  $%$ $k$ $!=0$（说明不管进行多少操作$2$,这种字母数都不会与$b$相同）则输出$NO$。全扫完后若没输出$NO$，则输出$YES$。

## Code
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
char a[10000001],b[10000001];
int num,numa[27],numb[27];
//num为可以变成此时字母的其他字母的数量。
//numa为字母字符串a中的数量，numb为在b中的数量
inline int read(){
	int x=0,k=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') k=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*=k;
}
int main(){
	t=read();
	while(t--){
		n=read();k=read();
		cin>>(a+1);
		cin>>(b+1);
		num=0;
		int bb=0;
		for(int i=1;i<=26;i++) numa[i]=numb[i]=0;
		for(int i=1;i<=n;i++){
			numa[a[i]-'a'+1]++;
			numb[b[i]-'a'+1]++;
		}
		for(int i=1;i<=26;i++){
			if(numb[i]==numa[i]) continue;
			if(abs(numb[i]-numa[i])%k!=0){//进行多少操作2,这种字母数都不会与b相同，num始终是k的倍数，所以不用考虑
				printf("NO\n");
				bb=1;
				break;
			}
			if(numb[i]>numa[i]&&num+numa[i]<numb[i]){//加起来还不够直接输出NO
				printf("NO\n");
				bb=1;
				break;
			}
			if(numb[i]>numa[i]&&num+numa[i]>=numb[i]){//需要下面的字母
				num-=numb[i]-numa[i];
			}
			if(numb[i]<numa[i]){//如果有多余的数量可以向上移
				num+=numa[i]-numb[i];
			}
		}
		if(!bb) printf("YES\n");
	}
	return 0;
}
 

---

## 作者：H6_6Q (赞：0)

## [1451C - String Equality](https://codeforces.com/contest/1421/problem/C)

### 题目大意

给定两个字符串 $A$ 和 $B$，每次可以交换 $A$ 中的两个字符或把 $A$ 中的连续 $k$ 个字符全部变为下一个（$a\rightarrow b$,$y\rightarrow z$,$z$ 不变）

问能否将 $A$ 变成 $B$

### 解题思路
因为可以无限交换，所以所有位置要求全都无效。

所以第二个操作可以转化为将 $A$ 中的任意 $k$ 个相同字符都变为下一个，目标也变为让 $A$ 所含的字符与 $B$ 所含的字符一样。

因为字符只能从小到大变，所以可以从 $a$ 开始，枚举 $B$ 中有多少个该字符，如果 $A$ 中的不够就肯定不行，如果够了多出来的就 $k$ 个 $k$ 个全部变成下一个字符，如果有字符剩余，那么同样不行。

### Code
```cpp
const int N=1e6+5;
int t,n,k,fl,s1[30],s2[30];
char s[N],e[N];

signed main()
{
	t=read();
	while(t--)
	{
		n=read();k=read();
		scanf("%s",s+1);
		scanf("%s",e+1);
		memset(s1,0,sizeof(s1));
		memset(s2,0,sizeof(s2));
		for(int i=1;i<=n;++i)
			s1[s[i]-'a'+1]++,s2[e[i]-'a'+1]++;
		fl=1;
		for(int i=1;i<=26;++i)
		{
			if(s1[i]<s2[i]) QWQ
			s1[i]-=s2[i];
			if(i!=26)
			{
				s1[i+1]+=s1[i]/k*k;
				s1[i]%=k;
			}
			if(s1[i]!=0) QWQ;
		}
		if(fl) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---

## 作者：pomelo_nene (赞：0)

因为操作可以做无限次，所以说整个字符串可以重排。所以字符串的顺序并不重要。通过第二个操作看，实际上重要的是每个字符的个数。

显然，出现了相同的字符，我们直接匹配，相当于减少两个串中这个字符减少出现次数就行了。因为这个相同的字符如果不匹配，就一定会变成更大的字符，永远不能够匹配这个字符了。

于是，如果字符个数相同，匹配；否则将能匹配的匹配了，然后转移给下一个字符。注意到有 $k$ 的限制，注意下转移时判断一下是否是 $k$ 的倍数。桶排瞎贪心即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[29],b[29],q,n,k;
char s[1000005],t[1000005];
int main(){
	scanf("%d",&q);
	while(q-->0)
	{
		scanf("%d %d",&n,&k);
		memset(a,0,sizeof a);
		memset(b,0,sizeof b);
		scanf("%s",s+1);
		scanf("%s",t+1);
		for(int i=1;i<=n;++i)	++a[int(s[i]-'a')];
		for(int i=1;i<=n;++i)	++b[int(t[i]-'a')];
		for(int i=0;i<=25;++i)
		{
			int tmp=min(a[i],b[i]);
			a[i]-=tmp;
			b[i]-=tmp;
		}
		for(int i=0;i<=25;++i)
		{
			int tmp=min(a[i],b[i]);
			a[i]-=tmp;
			b[i]-=tmp;
			a[i+1]+=a[i]/k*k;
			a[i]-=a[i]/k*k;
		}
		bool flag=false;
		for(int i=0;i<=25;++i)	if(a[i] || b[i]){flag=true;break;}
		puts(flag?"No":"Yes");
	}
	return 0;
}
```

---

## 作者：一Iris一 (赞：0)

# 思路
根据性质1，我们可以对序列进行交换，保证了序列可以组成我们任何想要的次序

分析性质二，相当于我们可以进行区间加法但只能对连续且相同的k个数进行，这保证了如果存在一段数$num$个，那么无论怎么修改，终究会使这段剩下的数$len$，使得$num \equiv len \pmod{k} $


设目标区间该段数个数为$Len$
反过来想，如果$num \equiv Len \pmod{k} $，那么是这个区间为$Yes$的必要条件

于是我们就可以根据上述结论写出这道题了

# Code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
 
using namespace std;
 
const int p=1e6+5;
 
#define int long long
#define INF 1<<30
 
template<typename _T>
inline void read(_T &x)
{
	x=0;char s=getchar();int f=1;
	while(s<'0'||s>'9') {f=1;if(s=='-')f=-1;s=getchar();}
	while('0'<=s&&s<='9'){x=(x<<3)+(x<<1)+s-'0';s=getchar();}
	x*=f;
}
 
int a[29];
int b[29];
char c[p],ch[p];
 
signed  main()
{
	
	int T;
	
	read(T);
	
	while(T--)
	{
	
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
		
	int n,k;
	
	read(n);read(k);
	
	scanf("%s",c+1);scanf("%s",ch+1);
	
	for(int i=1;i<=n;i++)
	{
		a[c[i]-'a'+1]++;
		b[ch[i]-'a'+1]++;
	 } 
	int oks=0;
	for(int i=1,cnt;i<=25;i++)
	{
		if(a[i]%k == b[i]%k && a[i] >=b[i])
		{
			cnt = a[i]-b[i];//将多余的数都扔到下一段去
			a[i+1] += cnt; 
		}
		else 
		{
			printf("No\n");oks =1;break;
		}
	}
	
	if(oks) continue;
	
	if(a[26] == b[26]) printf("Yes\n");
	else printf("No\n");		
		
	}
	
 
 }
```

---

