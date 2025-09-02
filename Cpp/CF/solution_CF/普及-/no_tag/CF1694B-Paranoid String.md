# Paranoid String

## 题目描述

Let's call a binary string $ T $ of length $ m $ indexed from $ 1 $ to $ m $ paranoid if we can obtain a string of length $ 1 $ by performing the following two kinds of operations $ m-1 $ times in any order :

- Select any substring of $ T $ that is equal to 01, and then replace it with 1.
- Select any substring of $ T $ that is equal to 10, and then replace it with 0.For example, if $ T =  $ 001, we can select the substring $ [T_2T_3] $ and perform the first operation. So we obtain $ T =  $ 01.

You are given a binary string $ S $ of length $ n $ indexed from $ 1 $ to $ n $ . Find the number of pairs of integers $ (l, r) $ $ 1 \le l \le r \le n $ such that $ S[l \ldots r] $ (the substring of $ S $ from $ l $ to $ r $ ) is a paranoid string.

## 说明/提示

In the first sample, $ S $ already has length $ 1 $ and doesn't need any operations.

In the second sample, all substrings of $ S $ are paranoid. For the entire string, it's enough to perform the first operation.

In the third sample, all substrings of $ S $ are paranoid except $ [S_2S_3] $ , because we can't perform any operations on it, and $ [S_1S_2S_3] $ (the entire string).

## 样例 #1

### 输入

```
5
1
1
2
01
3
100
4
1001
5
11111```

### 输出

```
1
3
4
8
5```

# 题解

## 作者：良心WA题人 (赞：3)

**谨以此题解纪念长时间停打 CF 后的第一场比赛**

### 思路

题目的操作方法将操作的本质给的比较含蓄。所以我们换一种方法表达：

> 对于字符串两个相邻的字符，若二者不相等，则可以删去左边的。

现在，对于一个字符串，必然是从左往右删到只剩下一个字符。所以，我们可以尝试来模拟一下操作。

考虑对于字符 $i$ 能否被删去。不难看出，若从左往右把能删的尽量全部删掉，那么 $i$ 必然会被右边第一个字符不为 $s_i$ 的位置删掉。所以，我们最后会得到这样一个串：

$xxxxxxxxx.....$

因为只能删去左边的字符，所以不难证明上面的字符串不能用其他方法删去（因为这些字符串是原串的一个后缀）。所以，我们题目要求的就是让上面的字符串长度为 $1$ 的原串个数。

所以，可以看出，当且仅当最后两个字符不相等或原串长度为 $1$ 时上述字符串长度为 $1$。所以，我们可以将串 $s$ 的字符分为两类：

* $s_i\not=s_{i-1}$，此时将 $i$ 作为原串的右端点时，左端点可以取任何不大于 $i$ 的值，答案加上 $i$。
* $s_i=s_{i-1}$，此时只能让原串长度为 $1$ 才可以。所以答案加上 $1$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200004];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		long long ans=0;
		scanf("%d%s",&n,s+1);
		for(int i=1;i<=n;i++)
			if(s[i]!=s[i-1])
				ans+=i;
			else
				ans++;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Together_ (赞：1)

这里我就讲一下思路，代码去看楼上的吧！

## 思路：

对于一个 $\mathtt{01}$ 串，有 $\mathtt2$ 种操作：

1. 将子串 $\mathtt{01}$ 变成 $\mathtt1$。

2. 将子串 $\mathtt{10}$ 变成 $\mathtt0$。

无论是将 $\mathtt{01}$ 变成 $\mathtt1$ 还是将 $\mathtt{10}$ 变成 $\mathtt0$，都是将第一个字符去掉，保留第二个字符。所以无论如何，最后一位都不会被删掉。

对于以 $S_i$ 结尾的字符串：

当 $S_i=S_{i-1}$，此时对答案贡献为 $1$。

当 $S_i \ne S_{i-1}$ ，此时对答案贡献为 $i$。

遍历一遍字符串，然后把贡献记录下来，输出即可。（注意开**long long**）

### 时间复杂度：

单组数据的复杂度最多为 $O(n)$，有 $T$ 组数据，所以总的时间复杂度为 $O(nT)$，$n\leq2\times10^5$，$T\leq1000$，所以时间对多为 $2 \times 10^5\times1000$，不会超时。



---

## 作者：猜一猜我是谁 (赞：1)

# 思路
可以发现，这两种操作的本质都是删去两个不同字符中左边的一个。

以样例的倒数第二组数据为例，也就是 $1001$。我们分别计算以第 $i$ 个字符结尾并最终能转化为只有一个字符的字串有多少个。以第 $1$ 个字符结尾的显然只有它本身；以第 $2$ 个结尾的有 $10,0$；以第 $3$ 个结尾的也只有它本身；以第 $4$ 个结尾的可以有 $1001,001,01,1$。

可以发现一个有趣的性质：
- 如果 $s_i\ne s_{i-1}$，那么以 $s_i$ 结尾，从 $s_1,s_2,s_3,\cdots,s_i$ 开头的字串最终都能转化为只有一个字符的字串，一共有 $i$ 个。

- 如果 $s_i=s_{i-1}$，那么以 $s_i$ 结尾并能能转化为只有一个字符的字串的只有 $s_i$ 本身。

时间复杂度 $O(Tn)$，可以接受。

注意：因为答案最大可能是 $\sum\limits_{i=1}^ni=\dfrac{200000\times200000}{2}=2\times10^{10}$，所以答案需要开 `long long`。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans;
int main(){
    int t;
    cin>>t;
    while(t--){
        ans=0;
        int n;
        string s;
        cin>>n>>s;
        s=' '+s;//往后挪一格
        for(int i=1;i<=n;i++)
            if(s[i]!=s[i-1]) ans+=i;
            else ans++;
        cout<<ans<<endl;
    }
}
```

---

## 作者：_ouhsnaijgnat_ (赞：1)

这道题稍加思考就能写出来。

## 思路

将 $01$ 改成 $1$，就是将 $0$ 删了，将 $10$ 改成 $0$ 也是这样。那么每次操作就是将前面删掉，那么最后留下的就是最后一位。

而 $s_{i}$ 和 $s_{i-1}$ 有什么关系呢？

如果 $s_{i}=s_{i-1}$，那么代价为 $1$。

如果 $s_{i}\not=s_{i-1}$，那么代价就为 $i$。

呐，代码就写出来了。只要遍历一边 $1\backsim n$，再记录下答案就行了。

代码太丑，就不放了。

---

## 作者：lovely_hyzhuo (赞：1)

本蒟蒻第二篇题解，轻喷。

### [题目链接](https://www.luogu.com.cn/problem/CF1694B)

题意简述：给定一个 $01$ 字符串可将为 $01$ 的字串变成 $1$，$10$ 的字串变成 $0$。
求最小操作次数。

通过观察可以看出，每次操作相当于保留了后一位，删除了前一位。所以无论通过多少次操作，最后一位永远不会被删除。

而有 $T$ 组数据，单组复杂度为 $O(n)$，总复杂度为 $O(Tn)$，时间复杂度不会炸。


```cpp
#include<iostream>
#define int long long
using namespace std;
int a[1000010];
string str;
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int ans=0;
		int n;
		cin>>n;
		cin>>str;
		str+=' ';
		for(int i=1;i<=n;i++)
		{
			a[i]=str[i-1]-'0';
			if(a[i]==a[i-1])
			{
				ans++;
			}
			else
			{
				ans+=i;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```



---

## 作者：Le_Saint_Chevalier (赞：0)

# 思路:
仔细观察替换操作，可以发现，该操作其实就是：
### 当字符串的两个相邻元素不同时，删去左边的元素，如果相同，则不变。
那么，就需要判断两个相邻元素是否相等。

显然地，如果下标为 $i$ 和 $i-1$ 的两个元素不相等，那么符合要求的子串数为 $i$。

如果相等，那么，因为这两个相邻元素长度均为 $1$，而前面的元素已经比较过，所以只需将答案加一即可。
# 代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
long long ans=0,t;
string str;
int main()
{
    cin>>t;
    while(t--)
    {
        ans=0;
        long long n;
        cin>>n>>str;
        str+=' ';
        for(int i=1;i<=n;i++)
            if(str[i]!=str[i-1])
                ans+=i;
            else
                ans++;
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：Sternenlicht (赞：0)

思路：

经观察，发现两种操作都是将前一位删除，后一位保留，并且操作只针对相邻且不同的两个数。

对于结尾为 $str_i$ 的子串，对答案产生的贡献有两类：

1. $str_i = str_{i-1}$，此时对答案贡献为 $1$。

2. $str_i \ne str_{i-1}$，此时对答案贡献为 $i$。

判断后加入总和即可，注意答案开 long long。

```cpp
#include <bits/stdc++.h>
namespace IO{
	#define LL long long
	inline LL read(){
		LL x=0,f=1;char c=getchar();
		for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
		for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
		return x*f;
	}
	inline void write(LL x,char c='\n'){
		if (x){
			if (x<0)x=-x,putchar('-');
			char a[30];short l;
			for (l=0;x;x/=10)a[l++]=x%10^48;
			for (l--;l>=0;l--)putchar(a[l]);
		}else putchar('0');putchar(c);
	}
}using namespace IO;
using namespace std;

const int N = 2e5+10;
bool a[N];
int main(){
	int T=read();
	while (T--){
		int n=read();
		for (int i=1;i<=n;i++){char c;cin>>c;a[i]=c-48;}
		a[0]=a[1];LL ans=0;//注意开long long 
		for (int i=1;i<=n;i++)ans+=(a[i]==a[i-1]?1:i);//求贡献总和 
		write(ans);
	}
	return 0;
}
```

---

## 作者：hanzhang666 (赞：0)

# 分析
- 发现两种操作在本质上都是将前一位删掉，由此可得一个子串的最后一位一定会被保留。

- 给定的操作都只针对相邻且不同的两个数，对于两个相邻且相同的数，我们不能进行任何操作。

综上知，结尾为 $s_i$ 的子串满足 $s_i \not= s_{i-1}$ 时对答案的贡献为 $i$，不满足时为 $1$。暴力枚举子串的结尾即可。时间复杂度 $\mathcal{O}(Tn)$。

**十年 OI 一场空，不开 long long 见祖宗。**
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
bool a[200005];
signed main(){
	int T=read();
	while(T--){
		int n=read();
		for(int z=1;z<=n;z++){
			char c;
			cin>>c;
			a[z]=c-'0';
		}
		a[0]=a[1];
		int ans=0;
		for(int z=1;z<=n;z++){
			ans+=((a[z]!=a[z-1])?z:1); 
		} 
		cout<<ans<<endl;
	}
}
```


---

## 作者：Mr__Cat (赞：0)

### 题目翻译

有 $T$ 数据，问几次能将所给 $\tt{01}$ 字符串 $s$ 的长度改为 $1$。

对一个  $\tt{01}$ 串，有以下两种操作：

将子串  $\tt{01}$ 替换为  $\tt{1}$。

将子串  $\tt{10}$ 替换为  $\tt{0}$。

### 题目思路

观察到操作总是删除连续两个字符中的前一个字符。即对一个串进行若干次操作，最后一个字符总会保留。时间复杂度为 $\Theta(Tn)$，可以接受。

### 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//mamer再也不用担心我忘开long long了 
main(){
    int T;
    cin>>T;//输入T 
    while(T--){
        int n;
		int ans=0;
		string s;
        cin>>n>>s;//输入长度和01字符串 
        s=' '+s;
        for(int i=1;i<=n;i++){
            if(s[i]==s[i-1])ans++;//操作1 
            else ans+=i;//操作2 
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：hsfzLZH1 (赞：0)

### 题目大意

对一个 01 串，有以下两种操作：

- 将子串 01 替换为 1

- 将子串 10 替换为 0

$t$ 组数据，每组给定一个长度为 $n$ 的 01 串 $S$ 。求 $S$ 的子串个数，满足经过若干次操作，可令长度等于 $1$ 。

$1\le t\le 1000,1\le n\le 2\times 10^5,\sum n\le 2\times 10^5$

### 解题思路

（以下所说的“后”即下标较大）

观察到操作总是删除连续两个字符中的前一个字符。即对一个串进行若干次操作，最后一个字符总会保留。

若子串长度为 $1$ ：无需操作已满足题意。

若长度大于 $1$ ：若最后两个字符相同，无论如何操作均不可能删去这两个字符，该串不合题意；若最后两个字符不同，可给出一种构造方法：先删去子串中所有与最后一个字符相同的字符（这些字符后一定存在一个与最后一个字符不同的字符），再删除所有不同的字符。

枚举子串结束的位置，求和即可。记得开 `long long` 。时间复杂度 $O(n)$ 。

### 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=200010;
#define int long long
int T,n,ans;
char s[maxn];
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%s",&n,s+1);
		ans=0;
		for(int i=1;i<=n;i++)if(s[i]==s[i-1])ans++;else ans+=i;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

