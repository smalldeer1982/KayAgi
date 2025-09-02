# Students in Railway Carriage

## 题目描述

There are $ n $ consecutive seat places in a railway carriage. Each place is either empty or occupied by a passenger.

The university team for the Olympiad consists of $ a $ student-programmers and $ b $ student-athletes. Determine the largest number of students from all $ a+b $ students, which you can put in the railway carriage so that:

- no student-programmer is sitting next to the student-programmer;
- and no student-athlete is sitting next to the student-athlete.

In the other words, there should not be two consecutive (adjacent) places where two student-athletes or two student-programmers are sitting.

Consider that initially occupied seat places are occupied by jury members (who obviously are not students at all).

## 说明/提示

In the first example you can put all student, for example, in the following way: \*.AB\*

In the second example you can put four students, for example, in the following way: \*BAB\*B

In the third example you can put seven students, for example, in the following way: B\*ABAB\*\*A\*B

The letter A means a student-programmer, and the letter B — student-athlete.

## 样例 #1

### 输入

```
5 1 1
*...*
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6 2 3
*...*.
```

### 输出

```
4
```

## 样例 #3

### 输入

```
11 3 10
.*....**.*.
```

### 输出

```
7
```

## 样例 #4

### 输入

```
3 2 3
***
```

### 输出

```
0
```

# 题解

## 作者：Nuyoah_awa (赞：3)

### 题目大意

有一个长度为 $n$ 的只含 `*.` 的字符串，你可以把其中的 `.` 换成 `A` 或 `B`，要求 `A` 不超过 $a$ 个， `B` 不超过 $b$ 个，且连续两个字符不能同时是 `A` 或者 `B`，求最多有多少个 `.` 被替换掉。

### 题目分析

我们可以以 `*` 为断点，将字符串分为很多个连续的 `.`，根据连续 `.` 的数量，我们可以分成如下两类：

1. `*.*`、`*...*`，单数个 `.`：我们可以把 `.` 染成任意形如 `ABA` 或 `BAB` 的形式，`A` 的个数和 `B` 的个数永远差 $1$，由于 `A,B` 的个数都是有限制的，为了使尽可能多的 `.` 被替换掉，我们可以优先染成剩余个数多的字母。

2. `*..*`、`*....*`，偶数个 `.`：我们可以染成 `ABAB` 或 `BABA` 两种形式，`A` 和 `B` 的个数是一样的，所以如何染色并无本质上的差别。

但是有可能在替换某个连续 `.` 段时替换到一半 `A` 或 `B` 的个数就用完了，所以我们在替换每个 `.` 段时都从剩余个数多的字母开始替换，然后交替替换，当某个字母用完后就用另一个字母间隔替换。

总的时间效率是 $O(n)$ 的。
### code
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n, a, b, ans;
string s;
int main()
{
	scanf("%d %d %d", &n, &a, &b);
	cin >> s;
	if(s[0] == '.')
	{
		if(a > b)
			a--, s[0] = 'A', ans++;
		else if(b)
			b--, s[0] = 'B', ans++;
	}
	for(int i = 0;i < n;i++)
	{
		if(s[i] != '.')
			continue;
		if(s[i-1] == '*' || s[i-1] == '.')
		{
			if(a > b)
				a--, s[i] = 'A', ans++;
			else if(b)
				b--, s[i] = 'B', ans++;
		}
		else
		{
			if(b && s[i-1] == 'A')
				b--, s[i] = 'B', ans++;
			if(a && s[i-1] == 'B')
				a--, s[i] = 'A', ans++;
		}
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：qW__Wp (赞：3)

[更好的阅读体验？](https://www.luogu.com.cn/blog/zhangruien/solution-cf962b)

### 题目大意

你手上有 $a$ 个 $\texttt A$ 和 $b$ 个 $\texttt B$ ，给你一个只包含 $\texttt .$ 和 $\texttt *$ 的字符串，你可以在手上的 $\texttt A$ 或 $\texttt B$ 没用完时将 $\texttt .$ 改变为 $\texttt A$ 或 $\texttt B$ ，但前提是字符串中不能有连续的 $\texttt A$ 或连续的 $\texttt A$ (一个不算连续)，问你最多能改变多少个 $\texttt .$。 

### 思路

这题大概是贪心吧。

枚举字符串 $s$ 的每一个字符，如果当前字符为 $\texttt .$ ，又如果上一个字符是 $\texttt *$ 或 $\texttt .$，那么如果 $a \ge b$，我们将 $s[i]$ 改成 $\texttt A$，否则，将 $s[i]$ 改成 $\texttt B$，并将 $\max(a,b)-1$，然后把统计结果的 $ans+1$。否则如果 $s[i-1]$ 是 $\texttt A$ ，那么如果 $b$ 的值不为 $0$，就将$s[i]$ 改为 $\texttt B$，然后把 $b-1$，再将 $ans+1$。
再否则如果 $s[i-1]$ 是 $\texttt B$，那么如果 $a$ 的值不为 $0$，就将$s[i]$ 改为 $\texttt A$，然后把 $a-1$，再将 $ans+1$。但是但是，在读入后，我们需要特判 (我的算法要)。如果 $s[0]$ 为 $\texttt .$ ，由于题目保证 $a+b>0$，于是我们就将 $s[0]$ 改为手上 $\texttt A$ 和 $\texttt B$ 的数量的最大值，并将 $\max(a,b)-1$，再将 $ans+1$ 。最后输出 $ans$ 即可。

### AC代码

```cpp
#include<iostream>
using namespace std;
int l,a,b,ans;
string s;
int main(){
	cin>>l>>a>>b>>s;
	if(s[0]=='.'){
		if(a>=b){
			s[0]='A';
			a--;
			ans++;
		}else if(b>=a){
			s[0]='B';
			b--;
			ans++;
		}
	}
	for(int i=1;i<l;i++){
		if(s[i]=='.'){
			if(s[i-1]=='*'||s[i-1]=='.'){
				if(a>=b&&a>0){
					s[i]='A';
					a--;
					ans++;
				}
				if(b>=a&&b>0){
					s[i]='B';
					b--;
					ans++;
				}
			}else if(s[i-1]=='A'&&b>0){
				s[i]='B';
				b--;
				ans++;
			}else if(s[i-1]=='B'&&a>0){
				s[i]='A';
				a--;
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

### 提醒

一时作弊一时棕，一直作弊一直封。

---

## 作者：封禁用户 (赞：2)

贪心水题，从左往右找到空位，插入max(a,b);并记录下前一个是什么，（当然如果前一个是'*'就没事了）

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace program {
	int n,a,b;
	inline void work() {
		string s;
		scanf("%d%d%d",&n,&a,&b);
		getchar();
		getline(cin,s);
		int res=0;
		bool limit=0;
		int now=-1;//记录前一个是什么
		for(int i=0; i<s.size(); i++) {
			if(s[i]=='*') {
				limit=0;
				continue;
			}//是评委直接跳过
			if(!limit) {
				if(!(max(a,b)))break;//a,b都为0
				limit=(max(a,b)==a?1:0);
				if(a>=b) {
					a-=1;
					now=1;
					res+=1;
					limit=1;//插入a
				} else {
					b-=1;
					now=0;
					res+=1;
					limit=1;//插入b
				}
			} else {
				if(now)if(b)b-=1,res+=1,now=0;
					else now=0;
				else if(a)a-=1,res+=1,now=1;
				else now=1;
			}
		}
		printf("%d\n",res);
	}
} int main() {
	program::work();
	return 0;
}
```

---

## 作者：Not_defined (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF962B)
## 思路
考虑贪心，很显然 `A` 或 `B` 数量多的优先填，这样可以使得字符多的可以在后面隔一个字符填一个，填的数目更多，且要满足相邻两个字符不能相同，所以我们可以需要判定上一个字符是否与当前字符相等，以及需要记录 `A` 或 `B` 剩余的数量。 
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a,b,ans;
char s[N];
int main()
{
	cin>>n>>a>>b;
	s[0]='*';
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)
	{
		if(s[i]=='*')continue;
		else
		{
			if(a>=b)
			{
				if(a>0&&s[i-1]!='a')ans++,a--,s[i]='a';
				else if(b>0&&s[i-1]!='b')ans++,b--,s[i]='b';
			}
			else
			{
				if(b>0&&s[i-1]!='b')ans++,b--,s[i]='b';
				else if(a>0&&s[i-1]!='a')ans++,a--,s[i]='a';
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/CF962B)
## 题意：
有一个长度为 $n$ 的只含 ```*.``` 的字符串 $S$，你可以把其中的 ```.``` 换成 ```A``` 或 ```B```，要求 ```A``` 不超过 $a$ 个， ```B``` 不超过 $b$ 个，且连续两个字符不能同时是 ```A``` 或者 ```B```，求最多有多少个 ```.``` 被替换掉。
## 思路：
我们可以以 ```*``` 为断点，将字符串分为很多个连续的 ```.```，根据连续 ```.``` 的数量，我们可以分成 ```.``` 个数为奇数个和偶数个两类：

1.```*.* *...*```，单数个 ```.```：我们可以把 ```.``` 变成任意形如 ```ABA``` $\cdots$ 或 ```BAB```  $\cdots$ 的形式，```A``` 的个数和 ```B``` 的个数永远差 $1$，由于 ```A,B``` 的个数都是有限制的，为了使尽可能多的 . 被替换掉，我们可以优先染成剩余个数多的字母。

2.```*..* *....*```，偶数个 ```.```：我们可以变成 ```ABAB```  $\cdots$ 或 ```BABA```  $\cdots$ 两种形式，A 和 B 的个数是一样的，所以如何变化并无本质上的差别。

但是有可能在替换某个连续 ```.``` 段时替换到一半 ```A``` 或 ```B``` 的个数就用完了，所以我们在替换每个 ```.``` 段时都从剩余个数多的字母开始替换，然后交替替换，当某个字母用完后就用另一个字母间隔替换。

特殊的，要先对 $S_0$ 进行操作 
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n=0,a=0,b=0,ans=0;
string s;
int main(){
	scanf("%lld%lld%lld",&n,&a,&b);
	cin>>s;
	if(s[0]=='.'){//特殊的，要先对s[0]进行操作 
		if(a>b){//当 'A' 的数量大于 'B' 的数量时，用 'A' 来代替 '.' 
			a--;
			s[0]='A';
			ans++;
		}else if(b!=0){
		    b--;
			s[0]='B';
			ans++;
		}
	}
	for(long long i=1;i<n;i++){
		if(s[i]!='.'){//这个字符不是'.'，不进行操作
			continue;
		}
		if(s[i-1]=='*'||s[i-1]=='.'){//当字符是在 '*' 后的 '.' 时，进行与 s[0] 一样的操作 
			if(a>b){
				a--;
				s[i]='A';
				ans++;
			}else if(b!=0){
				b--;
				s[i]='B';
				ans++;
			}
		}else{//当字符不是在 '*' 后的 '.' 时
			if(b!=0&&s[i-1]=='A'){
				b--;
				s[i]='B';
				ans++;
			}
			if(a!=0&&s[i-1]=='B'){
				a--;
				s[i]='A';
				ans++;
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

贪心加上分类讨论。

-  这一位可以选 $A$ 或 $B$（前一位是 ``.`` 或 ``*`` ）。           
如果 $A$ 能选的个数大于 $B$ 能选的个数，就选 $A$，否则选 $B$。
  
   理由：
   
   如 ``...`` ，$A=2$，$B=1$。
   
   对于第一位只能选 $A$ 。
   
- 这一位的前一位是 $A$ 或 $B$。

	当然就选与前一位不同的。
	
（二）

AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int len,a,b,ans;
string st;
signed main(){
	cin>>len>>a>>b>>st;
	if(st[0]=='.'){
		if(a>b){
			a--;
			st[0]='A';
			ans++;
		}
		else if(b){
			b--;
			st[0]='B';
			ans++;
		}
	}//第一位特殊考虑
	for(int i=1;i<len;i++)
		if(st[i]=='.'){
			if(st[i-1]=='*'||st[i-1]=='.'){
				if(a>b){
					a--;
					st[i]='A';
					ans++;
				}
				else if(b){
					b--;
					st[i]='B';
					ans++;
				}
			}
			else{
				if(b&&st[i-1]=='A'){
					b--;
					st[i]='B';
					ans++;
				}
				if(a&&st[i-1]=='B'){
					a--;
					st[i]='A';
					ans++;
				}
			}
		}
	cout<<ans;
	return 0;
}
```

  

---

## 作者：QianianXY (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF962B)

## 题目分析

签到题。

最优方案要求 `A`，`B` 相间放置，且注意到 `A`，`B` 实质上等价。

两种字符数量需尽可能接近，保证间隔的 `.` 能被填上。

这样就得到了一个贪心方案，从左到右操作，能放就放，且尽可能先用剩余最多的字符。

复杂度 $O(n)$，喜提最优解。

## code

```cpp
#include <bits/stdc++.h>
#define rei register int
#define N 200010
using namespace std;

template <typename T> inline void read(T &x)
{
	x = 0; T f = 1; char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -f; ch = getchar();}
	while (isdigit(ch)) {x = x * 10 + ch - 48; ch = getchar();}
	x *= f;
}

int n, a, b, len, ans;
char c[N];

int main()
{
	read(n); read(a); read(b); scanf("%s", c + 1); len = strlen(c + 1);
	for (rei i = 1; i <= len; i++)
	{
		if (!a && !b) break;
		if (c[i] == '*') continue;
		if (i == 1 || c[i - 1] == '.' || c[i - 1] == '*')
		{
			if (a > b) c[i] = 'A', --a, ++ans;
			else c[i] = 'B', --b, ++ans;
		}
		else if (c[i - 1] == 'A' && b) c[i - 1] == 'B', --b, ++ans;
		else if (c[i - 1] == 'B' && a) c[i - 1] == 'A', --a, ++ans;
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：WsW_ (赞：0)

直接贪心即可  
另外，翻译太烂了，导致我之前做错，最终还是上CF用的机翻（  
题目中的意思是，相邻两个人，不能够相同，也就是说 $A$ 和 $A$ 不能相邻， $B$ 和 $B$ 不能相邻，于是好的方法就是交叉排列，也就是说一个 $A$ 一个 $B$，如果有一个没了，就只能空一格。  
如果上一个是 $*$ 那就不能放，只能空着，而下一个随便放。  
如果上一个空着，那这个就可以放既可以放 $A$ 也可以放 $B$ 。显而易见我们应当放两者中剩余数量多的，才能保证最大化利用。
## 代码注释很详细
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,n;
int ansa,ansb;//a、b的个数 
int aorb;//0是空，1是a，2是b 
char ch;
int main(){
	scanf("%d%d%d",&n,&a,&b);
	for(int i=1;i<=n;i++){
		cin>>ch;
		if(ch=='*'){//有人了，只能空着
			aorb=0;
			continue;
		}
		if(ch=='.'){//如果可以放 
			if(aorb==1){//如果上一个是a 
				if(ansb<b){
					ansb++;//如果可以放b就放b 
					aorb=2;//标记放的是b
				}
				else aorb=0;//不然空着 
			}
			else if(aorb==2){//如果上一个是b 
				if(ansa<a){
					ansa++;//如果可以放a就放a 
					aorb=1;//标记放的是a
				}
				else aorb=0;//不然空着 
			}
			else if(aorb==0){//如果上一个空着
				if(a-ansa>b-ansb){//哪个种类剩余多放哪个
					if(a>ansa){//如果可以放a
						ansa++;就放a
						aorb=1;//标记
					}
				}
				else if(b>ansb){//同上
					ansb++;
					aorb=2;
				}
			}
		}
	}
	printf("%d",min(ansa+ansb,a+b));//min不加应该也没事
	return 0;
}
```
update 2021/10/15修改错误

---

