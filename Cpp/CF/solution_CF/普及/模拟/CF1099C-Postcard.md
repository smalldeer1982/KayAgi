# Postcard

## 题目描述

Andrey received a postcard from Irina. It contained only the words "Hello, Andrey!", and a strange string consisting of lowercase Latin letters, snowflakes and candy canes. Andrey thought that this string is an encrypted message, and decided to decrypt it.

Andrey noticed that snowflakes and candy canes always stand after the letters, so he supposed that the message was encrypted as follows. Candy cane means that the letter before it can be removed, or can be left. A snowflake means that the letter before it can be removed, left, or repeated several times.

For example, consider the following string:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1099C/29c2aaaec4bcea3ed5c1b5a1ebd8cbd0c6df45f2.png)This string can encode the message «happynewyear». For this, candy canes and snowflakes should be used as follows:

- candy cane 1: remove the letter w,
- snowflake 1: repeat the letter p twice,
- candy cane 2: leave the letter n,
- snowflake 2: remove the letter w,
- snowflake 3: leave the letter e.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1099C/26482915a1d9df0d76c8d735f29de9bbb88caf58.png)Please note that the same string can encode different messages. For example, the string above can encode «hayewyar», «happpppynewwwwwyear», and other messages.

Andrey knows that messages from Irina usually have a length of $ k $ letters. Help him to find out if a given string can encode a message of $ k $ letters, and if so, give an example of such a message.

## 样例 #1

### 输入

```
hw?ap*yn?eww*ye*ar
12
```

### 输出

```
happynewyear
```

## 样例 #2

### 输入

```
ab?a
2
```

### 输出

```
aa```

## 样例 #3

### 输入

```
ab?a
3
```

### 输出

```
aba```

## 样例 #4

### 输入

```
ababb
5
```

### 输出

```
ababb```

## 样例 #5

### 输入

```
ab?a
1
```

### 输出

```
Impossible```

# 题解

## 作者：lightningZ (赞：2)

## 思路
有一说一我觉得这蓝的有点水，主要分为两种情况。

1. 要求数量比原本数量**多**。

这时候我们只需要一个 $*$ 就可以很好的解决问题，因为 $*$ 可以无限制的复制字母，只需要增加补齐差距之后把其他的输出就可以了。（当然如果没有 $*$ 就是无解）

2. 要求数量比原本数量**少**。

这种情况就要看特殊字符（ $?$ 和 $*$ ）的数量，如果数量足够，就可以，否则无解。

当然相等就不用考虑了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bool f=false;
int b;
int main()
{
    char a[205];
    scanf("%s",a+1);
    int n=strlen(a+1),num=0,cnt=0;
    for(int i=1;i<=n;i++)
    {
    	if(a[i]>='a'&&a[i]<='z') num++;//num记录字母的数量。
    	else if(a[i]=='*') //f记录是否有*，也就是第一种情况的无解。
		{
			cnt++;
			f=true;
		}
    	else if(a[i]=='?') cnt++;//cnt记录特殊字符的数量。
	}
	scanf("%d",&b);
	if(b>num)//第一种情况。
	{
		if(!f)//没有*时无解。
		{
			printf("Impossible");
			return 0;
		}
		else
		{
			bool flag=false;
			for(int i=1;i<=n;i++)//我认为有就一次性输出完就可以，不用管其他的特殊字符。
			{
				if(a[i+1]=='*')
				{
					if(!flag)//避免重复
					{
						for(int j=1;j<=b-num+1;j++) printf("%c",a[i]);
						flag=true;
					}
					else printf("%c",a[i]);
				}
				else if(a[i]<='z'&&a[i]>='a') printf("%c",a[i]);
			}
		}
	}
	else if(b==num)//记得特判
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i]<='z'&&a[i]>='a') printf("%c",a[i]);
		}
	}
	else//第二种情况
	{
		int tmp=num-b;
		if(tmp>cnt) //第二种情况的无解
		{
			printf("Impossible");
			return 0;
		}
		else
		{
			for(int i=1;i<=n;i++)
			{
				if(a[i]<='z'&&a[i]>='a') 
				{
					if(a[i+1]=='?'||a[i+1]=='*')//删字母
					{
						if(tmp>0) tmp--;
						else printf("%c",a[i]);
					}
					else printf("%c",a[i]);
				}
			}
		}
	}
	return 0;
}
```

完结撒花~~

---

## 作者：RYANGSJ (赞：2)

## 思路

考虑删掉所有的问号和星号，把删掉后剩下的字母的个数记为 $now$，考虑以下三种情况。

1.当 $now=k$ 时。

直接输出答案。

2.当 $now>k$ 时。

考虑能否通过删掉星号或问号前的字母来使得 $now=k$，如果不能则无解。

3.当 $now<k$ 时。

考虑是否有星号，如果没有则无解，有则用其中一个星号复制字符即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
using namespace std;
inline int read(){int f=1,res=0;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){res*=10;res+=ch-'0';ch=getchar();}return f*res;}
inline void write(int x){if(x<0){putchar('-');write(-x);}else if(x<=9){putchar(x+'0');}else{write(x/10);putchar((x%10)+'0');}return;}
string s;
char ch[2000005];
int n,len,tot,idx;
int flower,stick;
signed main(){
	cin>>s;
	len=s.length();
	n=read();
	for(int i=0;i<len;i++){
		if(s[i]=='?'){
			stick++;
		}if(s[i]=='*')flower++,idx=i;
	}
	int now=(len-stick-flower);
	if(now>n){
		if(now-stick-flower<=n){
			int del=now-n;
			for(int i=0;i<len;i++){
				if(s[i]=='?'||s[i]=='*')continue;
				if((s[i+1]=='?'||s[i+1]=='*')&&del>0){
					del--;
				}else cout<<s[i];
			}
		}else puts("Impossible");
	}else if(now<n){
		if(flower){
			int need=n-now;
			for(int i=0;i<len;i++){
				if(s[i]!='?'&&s[i]!='*')cout<<s[i];
				if(s[i+1]=='*'&&need>0){
					while(need>0){
						cout<<s[i];
						need--;
					}
				}
			}
		}else puts("Impossible");
	}else if(now==n){
		for(int i=0;i<len;i++){
			if(s[i]!='?'&&s[i]!='*')cout<<s[i];
		}
	}
	return 0;
}
/*
hap
*/
```

---

## 作者：MSqwq (赞：1)

简单贪心吧，不知道为啥蓝了，估计也就黄的水平，希望管理员能更改难度。  
首先是考虑无解的，我们把后面没有跟符号的字符撑为必须字符，那么必须字符的数量一定是小于等于 $k$ 的。如果全程都没有 '?' 那么如果全部能加的字符都加上总数量还小于 $k$ 那么就是也是无解的。  
其他情况是一定有解的，因为多了你可以不选特殊字符，少了你可以用后面带 '*' 的字符填。  
那么对于构造，我只需要知道我还需要填几个，如果还差就填，知道填满后面可填可不填的就不填了。  
就差不多了，代码就几行：  
```
const int N=210;
char a[N];
int main()
{
	cin>>a+1;int n=strlen(a+1);
	int m=read();
	int flag=0,ss=0,s=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]=='*'||a[i]=='?')continue;
		if(a[i+1]!='*'&&a[i+1]!='?')ss++;
		if(a[i+1]!='*')s++;
		else flag=1;
	}
	if((flag==0&&s<m)||ss>m)
	{
		cout<<"Impossible"<<endl;
		return 0;
	}
	ss=m-ss;
	string ans;
	for(int i=1;i<=n;i++)
	{
		if(a[i]=='*'||a[i]=='?')continue;
		if(a[i+1]=='?'&&ss>=1)ans+=a[i],ss--;
		if(a[i+1]=='*'&&ss>=1)
			while(ss--)ans+=a[i];
		if(a[i+1]!='?'&&a[i+1]!='*')ans+=a[i];
	}
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：一扶苏一 (赞：1)

[更好的阅读体验](https://www.cnblogs.com/yifusuyi/p/10231438.html)

## Description

给定一个长度为 $n$ 的字符串，尽可能包含小写字母，字符 '?' 和字符 ‘*’。保证上面两种特殊字符若出现则一定出现在一个小写字母的后面一位。要求构造一个长度为 $k$ 的新字符串，它和原串有如下关系：

> 按照原串的字母顺序向新串中填充，新串中含且仅含小写字母。
>
> 若原串的某小写字母后没有特殊字符，则这个字母在新串中必须保留
>
> 若原串的某小写字母后有字符 '?'，则这个字母在新串中可以被保留，也可以被删除
>
> 若原串某小写字母后有字符 '*'，则这个字母在新串中可以被保留，可以被删除，也可以被复读很多遍。

## Input

第一行是一个长度为 $n$ 的字符串，保证输入合法

第二行是一个整数 $k$ 代表要求构造的新串长度

## Output

输出一行一个长度为 $k$ 的字符串，为构造出的串。

若不存在这样的串，输出“Impossible”（不含引号）

## Hint

$1~\leq~n,k~\leq~200$

## Solution

为啥泥萌一个贪心就过了啊qaq，为啥就我一人写了个DP还fst了啊qaq，我咋这么菜啊qaq

我们发现一个字母分别有三种情况：保留，保留/删除，保留/删除/复读。

于是我们处理一个新的字符串，只含给定串中的小写字母，另开数组记录该字母对应哪种情况。一下说的原串均指这个只含小写字母的新串，设原串长度为 $len$。

于是问题就被转化为了按照原串一位一位的按照规则填能否填出一个长度为 $k$ 的字符串。这显然是可以DP的。

其实正着DP大概是可做的，但是比赛的时候有点困就直接倒着DP的。我们设 $f_{i,j}~=~true/false$ 为能否用原串 $[i,len]$ 位拼出新串的 $[j,k]$ 位。于是转移一共有三种情况：

#### 1、只能保留：

$$f_{i,j}~=~f_{i + 1,j + 1}$$

#### 2、保留或删除：

$$f_{i,j}~=~f_{i + 1,j + 1}~or~f_{i + 1,j}$$

#### 3、保留，删除，复读：

$$f_{i,j}~=~f_{i + 1,j + 1}~or~f_{i + 1,j}~or~\bigvee_{h = j + 2}^{k + 1} f_{i + 1, h}~=~\bigvee_{h = j}^{k + 1} f_{i + 1, h}$$

其中 $\bigvee_{i = a}^{b} s(i)$ 为若 $\exists~i_0~\in~[a,b],~s.t.~~s(i_0)~=~true$ 则返回 $true$，否则返回 $false$

初始化为 $f_{len + 1, k + 1} = true$

在转移时记录一下转移方向就可以输出方案了。

## Code

```cpp
#include <cstdio>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long ll;

namespace IPT {
    const int L = 1000000;
    char buf[L], *front=buf, *end=buf;
    char GetChar() {
        if (front == end) {
            end = buf + fread(front = buf, 1, L, stdin);
            if (front == end) return -1;
        }
        return *(front++);
    }
}

template <typename T>
inline void qr(T &x) {
    rg char ch = IPT::GetChar(), lst = ' ';
    while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
    while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
    if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
    rg char ch = IPT::GetChar(), lst = ' ';
    while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
    while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
    if (ch == '.') {
        ch = IPT::GetChar();
        double base = 1;
        while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
    }
    if (lst == '-') x = -x;
}

namespace OPT {
    char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
    if (x < 0) {x = -x, putchar('-');}
    rg int top=0;
    do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
    while (top) putchar(OPT::buf[top--]);
    if (pt) putchar(aft);
}

const int maxn = 210;

int Len, k, len;
char MU[maxn], CU[maxn];
int pre[maxn][maxn], vc[maxn];
bool frog[maxn][maxn];

void print(ci, ci);

int main() {
	freopen("1.in", "r", stdin);
	do MU[++Len] = IPT::GetChar(); while (((MU[Len] >= 'a') && (MU[Len] <= 'z')) || (MU[Len] == '?') || (MU[Len] == '*'));
	for (rg int i = 1; i <= Len; ++i) if ((MU[i] >= 'a') && (MU[i] <= 'z')) {
		CU[++len] = MU[i];
		switch (MU[i + 1]) {
			case '?': {
				vc[len] = 1;
				break;
			}
			case '*': {
				vc[len] = 2;
				break;
			}
		}
	}
	qr(k);
	frog[len + 1][k + 1] = true;
	rg int dk = k + 1;
	for (rg int i = len; i; --i) {
		rg int di = i + 1;
		for (rg int j = 1; j <= dk; ++j) {
			switch(vc[i]) {
				case 0: {
					if (frog[di][j + 1]) {
						frog[i][j] = true;
						pre[i][j] = j + 1;
					}
					break;
				}
				case 1: {
					if (frog[di][j + 1]) {
						frog[i][j] = true;
						pre[i][j] = j + 1;
					} else if (frog[di][j]) {
						frog[i][j] = true;
						pre[i][j] = j;
					}
					break;
				}
				case 2: {
					for (rg int h = j; h <= dk; ++h) if (frog[di][h]) {
						frog[i][j] = true;
						pre[i][j] = h;
						break;
					}
					break;
				}
			}
		}
	}
	if (frog[1][1]) print(1, 1);
	else puts("Impossible");
	return 0;
}

void print(ci cur, ci v) {
	if (cur > len) return;
	for (rg int i = v; i < pre[cur][v]; ++i) putchar(CU[cur]);
	print(cur + 1, pre[cur][v]);
}
```



---

## 作者：jess1ca1o0g3 (赞：0)

题意：给定一个字符串 $s$，如果 $s_i$ 是 `?`，那么可以删掉 $s_{i-1}$，也可以不动；如果 $s_i$ 是 `*`，可以删掉 $s_{i-1}$，可以复制 $s_{i-1}$ 任意多次，也可以不动。使最后的字符串长度为 $k$，或者输出无解。

分三种情况：
- 如果 $k>l$（$l$ 指去掉 `*` 和 `?` 后的长度），那么只要有 `*`，就可以无限复制，分段输出即可，否则就无解了；
- 如果 $k<l$，那么不管是 `?` 还是 `*` 都删前一个，直到 $k=l$，如果最后 $k\neq l$ 无解；
- 如果 $k=l$，什么都不需要做。

但实际上后两种情况可以写在一起。

时间复杂度 $\mathcal{O}(|s|)$。

奉上丑陋代码：

```cpp
#include<bits/stdc++.h>
#define i64 long long
#define L(a,b,c)for(int i=a;i<=b;i+=c)
#define R(a,b,c)for(int i=a;i>=b;i-=c)
using namespace std;

void solve();
int k,l;
string s;
bool f=1;

signed main(){
  solve();
  return 0;
}

void solve(){
  cin>>s>>k;
  L(0,s.size()-1,1){
    if(s[i]!='?'&&s[i]!='*') l++;
  }
  if(l<k){
    L(1,s.size()-1,1){
      if(s[i]=='*'){
        for(int j=0;j<i;j++) if(s[j]!='?'&&s[j]!='*') cout<<s[j];
        for(int j=1;j<=k-l;j++) cout<<s[i-1];
        for(int j=i+1;j<s.size();j++) if(s[j]!='?'&&s[j]!='*') cout<<s[j];
        f=0;
        break;
      }
    }
  }
  else{
    L(1,s.size()-1,1){
      if(s[i]=='?'&&l-k) s[i-1]='#',l--;
      if(s[i]=='*'&&l-k) s[i-1]='#',l--;
    }
    if(k!=l) f=1;
    else{
      f=0;
      L(0,s.size()-1,1){
        if(s[i]!='?'&&s[i]!='*'&&s[i]!='#') cout<<s[i];
      }
    }
  }
  if(f) cout<<"Impossible";
}
```

---

## 作者：lsr1409111459 (赞：0)

#### 1 题目描述

（[传送门](https://www.luogu.com.cn/problem/CF1099C)）

洛谷有翻译，不做描述。点链接查看即可。

#### 2 解题思路

思维题。

分为三种情况：

- 字符串中字母的个数等于 $k$ ：直接输出所有字母。
- 字符串中字母的个数大于 $k$ ：可以用 '?' 和 '\*' 删掉多余的字母。判断 '?' 和 '\*' 的个数是否足够删掉多余的字母，如果够，删掉多余的字母；否则输出 ``Impossible`` 。
- 字符串中字母的个数小于 $k$ ：可以用 '\*' 重复一个字母很多次。判断是否有 '\*' ，如果有，则重复第一个 '\*' 前的字母直到补上缺失的字母个数；否则输出 ``Impossible`` 。

#### 3 解题代码

```cpp
#include <iostream>
#include <cstring>
using namespace std;
char s[210];
int k;
char ans[210];
int main()
{
    scanf("%s%d",s,&k);
    int cnt1=0,cnt2=0;
    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]=='?')cnt1++;
        if(s[i]=='*')cnt2++;
    }
    int cnt3=strlen(s)-cnt1-cnt2;//cnt3是字母的个数
    bool flag=true;
    int cnt=0;
    if(cnt3<k)
    {
        if(cnt2==0)flag=false;
        else
        {
            for(int i=0;i<strlen(s);i++)
            {
                if(s[i]=='?')continue;
                if(s[i]=='*')
                {
                    while(k>cnt3)
                    {
                        ans[++cnt]=s[i-1];
                        cnt3++;
                    }
                }
                else ans[++cnt]=s[i];
            }
        }
    }
    else if(cnt3>k)
    {
        if(cnt3-k>cnt1+cnt2)flag=false;
        else
        {
            for(int i=0;i<strlen(s);i++)
            {
                if((s[i]=='*')||(s[i]=='?'))
                {
                    if(k<cnt3)
                    {
                        cnt--;
                        cnt3--;
                    }
                }
                else ans[++cnt]=s[i];
            }
        }
    }
    else 
    {
        for(int i=0;i<strlen(s);i++)
        {
            if((s[i]=='*')||(s[i]=='?'))continue;
            ans[++cnt]=s[i];
        }
    }
    if(flag)
    {
        for(int i=1;i<=cnt;i++)printf("%c",ans[i]);
        printf("\n");
    }
    else printf("Impossible\n");
    return 0;
}
```

#### 4 解题心得

思维题。注意 '*' 是可以重复一个字符多次而不是一次。考场上因为这个 WA 了。注意 SPJ ，想明白题意暴力即可。

---

## 作者：QQH08 (赞：0)

先看无解的情况：

1. 如果把所有可以删的都删了，还比 $k$ 长，就无解。
2. 所有问号都不删，且没有星号（不然可以无穷长），还比 $k$ 短，也无解。

然后来分 $2$ 类构造：

1. 有星号：非常简单，直接把所有问号都删了，用星号补到 $k$。
2. 没星号：每次找到问号先判断够不够到 $k$ ，不够就保留，不然就删。

代码实现也很简单啦。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=205;	
char s[N];
int m,flag;
int main(){
	scanf("%s",s+1);
	int n=strlen(s+1);
	scanf("%d",&m);
	int cnt1=0,cnt2=0,nn=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='?'||s[i]=='*')continue;
		nn++;
		if(s[i+1]=='?')cnt1+=2,cnt2++;
		if(s[i+1]=='*')cnt1+=2,cnt2++,flag=1;
	}
	if(n-cnt1>m){
		puts("Impossible");
		return 0;
	}
	int tmp=m-(nn-cnt2);
	if(tmp>cnt2&&flag==0){
		puts("Impossible");
		return 0;
	}
	if(flag==0){
		for(int i=1;i<=n;i++){
			if(s[i]=='?'||s[i]=='*')continue;
			if(s[i+1]=='?'&&tmp>0){
				tmp--;
				cout<<s[i];
			}
			if(s[i+1]!='?')cout<<s[i];
		}
	}
	else{
		int vis=0;
		for(int i=1;i<=n;i++){
			if(s[i]=='?'||s[i]=='*'||s[i+1]=='?')continue;
			if(s[i+1]=='*'&&!vis){
				vis=1;
				for(int j=1;j<=tmp;j++)cout<<s[i];
			}
			if(s[i+1]!='*')cout<<s[i];
		}
	}
	return 0;
}
```


---

## 作者：oimaster (赞：0)

我又来写题解了！
## 思路
这是一道经典的模拟。
由于宏观简单，我们就看微观了。
```cpp
/* Generated by powerful Codeforces Tool
 * You can download the binary file in here https://github.com/xalanq/cf-tool
 * Author: OI_Master
 * Time: 2020-04-11 03:33:32
**/
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
```
毫无质量的东西，这些是板子。
```cpp
string s;
int k;
cin>>s>>k;
```
毫无质量的东西，这些是输入。
```cpp
int sum=0;                   
for(int i=0;i<s.size();++i)  
	if(s[i]>='a'&&s[i]<='z') 
		++sum;               
	else if(s[i]=='*'){      
		sum=10000000000000;  
		break;               
	}                        
if(sum<k){                   
	cout<<"Impossible"<<endl;
		return 0;
}
```
~~毫无质量的东西，这些是循环。~~

才怪呢，我们发现，只要是字母都把它加上去，如果是 `*` 就说明能重复无数次。

原来是看最大能到多少。
```cpp
sum=0;                   
for(int i=0;i<s.size();++i)
	if(s[i]=='?'||s[i]=='*')
		--sum;
	else
		++sum;
if(sum>k){
	cout<<"Impossible"<<endl;
	return 0;
}
```
~~毫无质量的东西，这些也是循环。~~

我们再来看看这是什么用的。
我们发现，当 $s_i$ 是字母的话，那么 $sum$ 加 $1$ ，如果是字符，就让 $sum$ 扣掉 $1$。

发现，我们算的东西就是最少长度是多少，只要一个字母后面有 `*` 或者是 `?` 的话，就不算这个字母（删掉）。
最后比较一下。
```cpp
vector<char>ans;
for(int i=1;i<s.size();++i)
	if(s[i]>='a'&&s[i]<='z'&&s[i-1]>='a'&&s[i-1]<='z')
		ans.push_back(s[i-1]);
	else if(s[i]=='?'&&sum<k){
		++sum;
		ans.push_back(s[i-1]);
	}
	else if(s[i]=='*'&&sum<k)
		while(sum<k){
			++sum;
			ans.push_back(s[i-1]);
		}
```
核心部分啦！

如果这个字符是字母，不是符号，前面一个也不是符号，那么就说明前面一个必须要选，进 $ans$ 里面。

否则，如果是问号的话，并且串长不够，那么就把字母压到 $ans$ 里。

如果是 `*` 的话，那么可以把串长补到够，一直加，没有副作用。

这一段我故意写得稍微有些简洁，想让大家再看几下代码，好好理解。
```cpp
    if(s[s.size()-1]>='a'&&s[s.size()-1]<='z')
		ans.push_back(s[s.size()-1]);
	for(int i=0;i<ans.size();++i)
		cout<<ans[i];
    return 0;
}
```
这一段好像的确没什么难的了，就是打印。
## 代码
如果你不想一个一个拼，可以看完整代码，在 [这里](https://oi-master.github.io/post/codeforces-contest-1099-c-ti-jie/) 哦！

---

## 作者：览遍千秋 (赞：0)

本题解同步发布于[本场$\mathrm{CF}$总题解](https://www.luogu.org/blog/kaiming/CF530Div2)，欢迎来踩。

---

## C - Postcard

### 无解

首先考虑无解的情况。

假设原字符串$s$中有$cnt$个字母，$xing$个`*`，$wen$个`?`。

当以下两种情况时，无解：

- $cnt-xing-wen>k$
    
也就是把能删的字符全部删完还比$k$多。

- $cnt<k$且$xing=0$

也就是本来字符不够，还不能增加。

### 分类讨论

判断完无解后，自然想到分两种情况考虑：

- $cnt \le k$

即原来字母不够，需要增加字母。

首先遇到字母就输出

设$add=k-cnt$

遇到第$1$个跟着有`*`的字母，额外多输出$add$个这样的字母。

- $cnt > k$

即原来字母足够，需要删除字母。

设$del=cnt-k$

遇到的前$del$个跟着`*`或`?`的字母不输出。

其他字母全部输出。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;

string s;
int k,l;
int cnt;
int xing,wen;

template<typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh;
	while(ch!='-'&&(ch>'9'||ch<'0')) ch=getchar();
	if(ch=='-'){
		ch=getchar();fh=-1;
	}
	else fh=1;
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}

int mian(){
	cin>>s;cin>>k;
	l=s.size();
	for(register int i=0;i<l;i++){
		if(s[i]>='a'&&s[i]<='z') cnt++;
		else if(s[i]=='*') xing++;
		else wen++;
	}
	if(cnt-xing-wen>k||(cnt<k&&xing==0)){
		puts("Impossible");return 0;
	}
	if(cnt>=k){
		int del=cnt-k;
		for(register int i=0;i<l;i++){
			if(s[i]=='*'||s[i]=='?') continue;
			if(i==l-1||(s[i+1]>='a'&&s[i+1]<='z')) putchar(s[i]);
			else if(!del){
				putchar(s[i]);
			}
			else del--;
		}
		return 0;
	}
	else{
		int add=k-cnt;
		for(register int i=0;i<l;i++){
			if(s[i]=='*'||s[i]=='?') continue;
			if(i==l-1||(s[i+1]>='a'&&s[i+1]<='z')) putchar(s[i]);
			else if(!add) putchar(s[i]);
			else{
				putchar(s[i]);
				if(s[i+1]=='*'){
					while(add){
						putchar(s[i]);add--;
					}
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：PeyNiKge (赞：0)

~~这么水的蓝题？？！！~~

### 题意描述

给定一个只含有小写字母、星号、问号的字符串。

星号和问号前一定是字母。

星号表示前面的字母可以删除、出现任意次。

问号便是前面的字符可以删除、出现一次。

求给出操作完后只含有 $k$ 个小写字母的字符串。

无解输出 `Impossible`。

### 题面分析

设 $sum$ 是原字符串的字母数量。

观察题面，发现只有三种情况：

- $k < sum$

容易看出需要删除 $sum - k$ 个字符。

令 $sum - k$ 个星号或问号删除前面的字母，其余字母不变即可。

如果星号或问号总数小于 $sum - k$，那就是无解。

- $k = sum$

直接输出原字符串中的所有字母即可。

- $k > sum$

容易看出需要增加 $k - sum$ 个字符。

令一个星号增加前面的字符 $k - sum$ 次，其余字母不变即可。

如果没有星号，那就是无解。

### 代码

```c++
#include<bits/stdc++.h>
#define ll long long
#define PII pair<int, int>
#define Kg putchar(' ')
#define Ed puts("")
#define inf 0x7fffffff
#define INF 0x7fffffffffffffff
using namespace std;
const int N = 2e6 + 10, M = 5e3 + 10;
void read(int &ans){ans = 0;int f = 1;char ch = getchar();while(ch < '0' || ch > '9'){if(ch == '-'){f = -1;}ch = getchar();}while(ch >= '0' && ch <= '9'){ans = (ans << 1) + (ans << 3) + (ch ^ 48), ch = getchar();}ans *= f;}
void read(ll &ans){ans = 0;ll f = 1;char ch = getchar();while(ch < '0' || ch > '9'){if(ch == '-'){f = -1;}ch = getchar();}while(ch >= '0' && ch <= '9'){ans = (ans << 1) + (ans << 3) + (ch ^ 48), ch = getchar();}ans *= f;}
void print(int x){if(x < 0){putchar('-'), print(-x);}else if(x < 10){putchar(x % 10 + '0');}else{print(x / 10);putchar(x % 10 + '0');}}
void print(ll x){if(x < 0){putchar('-'), print(-x);}else if(x < 10){putchar(x % 10 + '0');}else{print(x / 10), putchar(x % 10 + '0');}}
int n, sum, k;
int sumx;
char s[N];
signed main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; i++){
		if(s[i] >= 'a' && s[i] <= 'z'){
			sum++;
		}
		if(s[i] == '*'){
			sumx = 1;
		}
	}
	read(k);
	if(k < sum){
		int sk = sum - k;
		if(sk > n - sum){
			puts("Impossible");
			return 0;
		}
		for(int i = 1; i <= n; i++){
			if(s[i] >= 'a' && s[i] <= 'z'){
				if(sk && (s[i + 1] < 'a' || s[i + 1] > 'z')) sk--;
				else putchar(s[i]);
			}
		}
	}
	else if(k == sum){
		for(int i = 1; i <= n; i++){
			if(s[i] >= 'a' && s[i] <= 'z'){
				putchar(s[i]);
			}
		}
	}
	else if(k > sum){
		int sk = k - sum;
		if(!sumx){
			puts("Impossible");
			return 0;
		}
		for(int i = 1; i <= n; i++){
			if(s[i] >= 'a' && s[i] <= 'z'){
				putchar(s[i]);
			}
			if(s[i] == '*' && sk){
				for(int j = 1; j <= sk; j++){
					putchar(s[i - 1]);
				}sk = 0;
			}
		}
	}
	return 0;
}
```

---

