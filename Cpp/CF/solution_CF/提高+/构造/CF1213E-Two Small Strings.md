# Two Small Strings

## 题目描述

给定两个长度为 $2$ 的字符串 $s$ 和 $t$，它们只包含字符 'a'、'b' 和 'c'。

字符串 $s$ 和 $t$ 的可能示例有："ab"、"ca"、"bb"。

你需要构造一个长度为 $3n$ 的字符串 $res$，其中恰好有 $n$ 个字符 'a'，$n$ 个字符 'b'，$n$ 个字符 'c'，并且 $s$ 和 $t$ 不能作为 $res$ 的子串出现。

一个字符串的子串是该字符串的一个连续子序列。例如，字符串 "abacc" 的子串有 "ab"、"ac" 和 "cc"，但 "bc"、"aa" 和 "cb" 不是其子串。

如果有多种答案，你可以输出任意一种。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
ab
bc
```

### 输出

```
YES
acbbac
```

## 样例 #2

### 输入

```
3
aa
bc
```

### 输出

```
YES
cacbacbab
```

## 样例 #3

### 输入

```
1
cb
ac
```

### 输出

```
YES
abc
```

# 题解

## 作者：Guess00 (赞：6)

~~调了半天终于过了~~

这题是个图论$.s,t$表示不能走的路$.$比如$,$当$s="ab"$时$,$表示路径$a\rightarrow b$是不通的$.$因为只有$s,t$两个字符串$,$所以可以得出一个$3$个顶点$,7$条边$($包括顶点到自己的边$)$的图$.$

然后分类讨论$:$
- 三个顶点**都能**通过一条边回到自己$:$

![](https://i.loli.net/2019/09/07/7eHTtNCuhAzGc5j.png)

这样我们可以构造一种格局使得第一与第二个点联通且第二与第三个点联通$,$构造出后**分别**重复$n$次即可$.$

举个例子$:$
> $3$
>
> $a\ b$
> 
> $b\ c$

答案:$aaacccbbb$


- 三个顶点**无法都能**通过一条边回到自己$:$

这样我们可以构造一种格局使得第一与第二个点联通且第二与第三个点联通且第一与第三个点联通$,$构造出后**集体**重复$n$次即可$.$

举个例子$:$
> $3$
>
> $a\ a$
> 
> $b\ c$

答案:$cbacbacba$

$\therefore$定可构造出

### $\mathbb{CODE:}$

```cpp
#include <bits/stdc++.h>
int n,i,j,k,a[5][5];
char c,c2,c3;
signed main(void)
{
	scanf("%d",&n);
	for (i=1;i<4;i++)
		for (j=1;j<4;j++)
			a[i][j]=true; //邻接矩阵赋初值 
	//读入 
	c=getchar();
	while (c!='a' && c!='b' && c!='c')
		c=getchar();
	c2=getchar();
	while (c2!='a' && c2!='b' && c2!='c')
		c2=getchar();
	a[c-'a'+1][c2-'a'+1]=0;  //拆边 
	c=getchar();
	while (c!='a' && c!='b' && c!='c')
		c=getchar();
	c2=getchar();
	while (c2!='a' && c2!='b' && c2!='c')
		c2=getchar();
	a[c-'a'+1][c2-'a'+1]=0;  //拆边 
	putchar('Y'),putchar('E'),putchar('S'),putchar('\n');//必为YES 
	if (!(a[1][1] && a[2][2] && a[3][3]))  //第二种 
	{
		for (i=1;i<4;i++)
			for (j=1;j<4;j++)
				for (k=1;k<4;k++)
					if (a[i][j] && a[j][k] && a[k][i] && i!=j && i!=k && j!=k)
						c=i-1+'a',c2=j-1+'a',c3=k-1+'a';
		for (i=1;i<=n;i++)  //集体重复 
			putchar(c),putchar(c2),putchar(c3);
		return 0;
	}
	//第一种 
	for (i=1;i<4;i++)
		for (j=1;j<4;j++)
			for (k=1;k<4;k++)
				if (a[i][j] && a[j][k] && i!=j && i!=k && j!=k)
					c=i-1+'a',c2=j-1+'a',c3=k-1+'a';
	//分别重复 
	for (i=1;i<=n;i++)
		putchar(c);
	for (i=1;i<=n;i++)
		putchar(c2);
	for (i=1;i<=n;i++)
		putchar(c3);
	return 0;
} 
```

---

## 作者：youngk (赞：2)

这道题应该属于一道模拟题，不如我们分成两种情况，给予的两个字符串中出现了连续的如aa，bb，cc和不出现连续的情况。

我们先讨论出现不连续的情况，呢么这样的我们可以构造出型如aaabbbccc或者aaacccbbb这样的答案，显然这种情况只会有两种限制，枚举所有的可能找到能输出的答案，这里就不得不提一个神奇的函数next_permutation可以帮助枚举。

如果s和t穿中出现了aa，bb，cc的情况，我们可以构造出型如abcabcabc或者acbacbacb的情况，这种构造只会受到一种限制(aa，bb，cc无法限制)，所以打表枚举一下就好了

代码:

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<set>
#define _USE_MATH_DEFINES
#include<math.h>
#include<queue>
#include<vector>
#include<limits.h>
#include<functional>
#include<stack>
typedef long long ll;
#pragma GCC optimize(2)
using namespace std;
inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
string s, t;
int n;
signed main()
{
	n = read();
	cin >> s >> t;
	cout << "YES\n";
	if (s[0] != s[1] && t[0] != t[1])
	{
		char str[5] = "abc";
		while (true) {
			if (!((str[0] == s[0] && str[1] == s[1]) || (str[0] == t[0] && str[1] == t[1]) || (str[1] == s[0] && str[2] == s[1]) || (str[1] == t[0] && str[2] == t[1])))
				break;
			next_permutation(str, str + 3);
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < n; j++)
				cout << str[i];
	}
	else
	{
		if (t != "aa" && t != "bb" && t != "cc")
			swap(s, t);
		if (s != "ab" && s != "bc" && s != "ca")
			for (int i = 1; i <= n; i++)
				cout << "abc";
		else if (s != "ac" && s != "cb" && s != "ba")
			for (int i = 1; i <= n; i++)
				cout << "acb";
		else if (s != "ba" && s != "ac" && s != "cb")
			for (int i = 1; i <= n; i++)
				cout << "bac";
		else if (s != "bc" && s != "ca" && s != "ab")
			for (int i = 1; i <= n; i++)
				cout << "bca";
		else if (s != "ca" && s != "ab" && s != "bc")
			for (int i = 1; i <= n; i++)
				cout << "cab";
		else if (s != "cb" && s != "ba" && s != "ac")
			for (int i = 1; i <= n; i++)
				cout << "cba";
	}
	return 0;
}
```


---

## 作者：Φρανκ (赞：1)

题意：求由 a b c 各 $n$ 个构成的字符串，使给定的两个字符串不成为其子串。

核心思想：枚举

解：

发现循环可以极大降低解的复杂度，并且 s t 各只有九种可能，可以枚举：

![情况表](https://cdn.luogu.com.cn/upload/image_hosting/fz93y2nt.png)

其中，abc 表示 abc 重复 $n$ 次，cba 同理。对于其余的情况，有两类较简单的构造：两个字符交替 $n$ 次，前或后有连续的 $n$ 个第三种字符；或三种字符各连续出现 $n$ 次。两种构造都能解决问题，但后一种较简便，故采用。对剩余的 $6$ 种排列方式，每种分别枚举即可。

代码：
```
#include <bits/stdc++.h>
using namespace std;
int n;
char s[2], t[2];
int main()
{
	cin>>n;
	cin>>s[0]>>s[1]>>t[0]>>t[1];
	cout<<"YES"<<endl;
	if(s[0]==s[1])
		if((t[0]=='a' && t[1]=='b') || (t[0]=='b' && t[1]=='c') || (t[0]=='c' && t[1]=='a'))
			for(int i=1; i<=n; i++)
				cout<<"cba";//一行二列
		else
			for(int i=1; i<=n; i++)
				cout<<"abc";//一行一三列
	else if(t[0]==t[1])
		if((s[0]=='a' && s[1]=='b') || (s[0]=='b' && s[1]=='c') || (s[0]=='c' && s[1]=='a'))
			for(int i=1; i<=n; i++)
				cout<<"cba";//二行一列
		else
			for(int i=1; i<=n; i++)
				cout<<"abc";//三行一列
	else if((s[0]=='a' && s[1]=='b') || (s[0]=='b' && s[1]=='c') || (s[0]=='c' && s[1]=='a'))
		if((t[0]=='a' && t[1]=='b') || (t[0]=='b' && t[1]=='c') || (t[0]=='c' && t[1]=='a'))
			for(int i=1; i<=n; i++)
				cout<<"cba";//二行二列
		else
			if(s[0]=='a' && s[1]=='b')
			{
				for(int i=1; i<=n; i++)
					cout<<"b";
				for(int i=1; i<=n; i++)
					cout<<"c";
				for(int i=1; i<=n; i++)
					cout<<"a";
			}
			else if(s[0]=='b' && s[1]=='c')
			{
				for(int i=1; i<=n; i++)
					cout<<"c";
				for(int i=1; i<=n; i++)
					cout<<"a";
				for(int i=1; i<=n; i++)
					cout<<"b";
			}
			else
			{
				for(int i=1; i<=n; i++)
					cout<<"a";
				for(int i=1; i<=n; i++)
					cout<<"b";
				for(int i=1; i<=n; i++)
					cout<<"c";
			}//二行三列
	else
		if((t[0]=='a' && t[1]=='b') || (t[0]=='b' && t[1]=='c') || (t[0]=='c' && t[1]=='a'))
			if(s[0]=='b' && s[1]=='a')
			{
				for(int i=1; i<=n; i++)
					cout<<"a";
				for(int i=1; i<=n; i++)
					cout<<"c";
				for(int i=1; i<=n; i++)
					cout<<"b";
			}
			else if(s[0]=='c' && s[1]=='b')
			{
				for(int i=1; i<=n; i++)
					cout<<"b";
				for(int i=1; i<=n; i++)
					cout<<"a";
				for(int i=1; i<=n; i++)
					cout<<"c";
			}
			else
			{
				for(int i=1; i<=n; i++)
					cout<<"c";
				for(int i=1; i<=n; i++)
					cout<<"b";
				for(int i=1; i<=n; i++)
					cout<<"a";
			}//三行二列
		else
			for(int i=1; i<=n; i++)
				cout<<"abc";//三行三列
	return 0;
}
```

---

## 作者：孑彧 (赞：1)

[听说进入我的博客观感更佳哦](https://hybjzzq.blog.luogu.org/)
## E.Two Small String

### 题意描述

给你两个由'a','b','c'组成且长度为2的字符串$s,t$.

给定$n$,让你构造一个由$n$个'a',$n$个'b',$n$个'c'组成且长度为$3\times n$的字符串$res$,使得s,t*s*,*t*不是$res$的子串..

若不可以,,输出"NO",否则,,第一行输出"YES",第二行输出任意一种符合条件的$res$.

### 思路

一个显而易见的思路是，我们去枚举每个位置上可能出现的字母，然后构造出一个可行的字符串，但是明显的来说，这个算法肯定会超时，所以我们就可以去构造出一个子串满足这个条件，然后将这个子串翻倍，就可以得到我们的目标字符串

当我们的子串满足条件的时候，自然可以构造出一个目标串，但是子串不满足条件的话，为什么就没有目标串呢？

我们的子串会找出所有的组合，假如说这些所有的组合都不满足条件的话，那么由这些所有组合构成的目标串也一定不满足条件

但是这个题还是有很多细节需要注意的，比如说一些情况下的特判

### 代码

```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#define maxn 5
using namespace std;
char a[maxn],b[maxn];
char s[maxn];
char getc(){
	char c=getchar();
	while(c!='a'&&c!='b'&&c!='c'){
		c=getchar();
	}
	return c;
}
bool flag,win;
bool used[3];
int tot=0;
int n;
void dfs(int cnt){
	if(win){
		return;
	}
	if(cnt==4){
		if(n==1||flag==0){
			win=1;
			return;
		}
		s[4]=s[1];
		if((s[3]==a[0]&&s[4]==a[1])||(s[3]==b[0]&&s[4]==b[1])){
			return;
		}
		else{
			win=1;
			return;
		}
	}
	for(int i=0;i<=2;i++){
		if(used[i]){
			continue;
		}
		if(cnt==1){
			s[cnt]=i+'a';
			used[i]=1;
			dfs(cnt+1);
			if(win){
				return;
			}
			s[cnt]=0;
			used[i]=0;
			continue;
		}
		if((s[cnt-1]==a[0]&&i+'a'==a[1])||(s[cnt-1]==b[0]&&i+'a'==b[1])){
			continue;
		}
		s[cnt]=i+'a';
		used[i]=1;
		dfs(cnt+1);
		if(win){
			return;
		}
		s[cnt]=0;
		used[i]=0;
	}
	return;
}
int main(){
	scanf("%d",&n);
	flag=0;
	for(int i=0;i<=1;i++){
		a[i]=getc();
	}
	if(a[0]==a[1]){
		flag=1;
	}
	for(int i=0;i<=1;i++){
		b[i]=getc();
	}
	if(b[0]==b[1]){
		flag=1;
	}
	dfs(1);
	if(win){
		printf("YES\n");
	}
	else{
		printf("NO");
		return 0;
	}
	if(flag){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=3;j++){
				cout<<s[j];
			}
		}
	}
	else{
		for(int i=1;i<=3;i++){
			for(int j=1;j<=n;j++){
				cout<<s[i];
			}
		}
	}
	return 0;
}
```
点个赞再走吧（QAQ

---

## 作者：弦巻こころ (赞：1)

一开始,看到这道题.感觉跟[POI[2000]病毒](https://www.luogu.org/problem/P2444)很像,于是就敲半天AC自动机+dfs. 一交完却发现WA了.结果发现看漏了条件.题目中要求需要n个a,n个b,n个c而我爆搜时却没考虑这点,但我改完又发现它一直输出NO.然后我就发现自己sb了.但这题只用一个简单的构造就行了

下面讲下如何构造出答案.首先,我们发现.这道题的输出是3*n也就是3的倍数.所以我们就考虑是否可以通过构造来解决问题.

我们构造一个3个互不相同包含a,b,c的字符串.也就是
$$
abca
$$
$$
acba
$$
$$
cabc
$$
$$
cbac
$$
$$
bacb
$$
$$bcab
$$
这几个字符串,然后我们通过枚举每个字符串是否含有模式串,如果不含有就直接打印.

但需要考虑一种特殊情况

也就是让这六个字符串都不包含它.但可以通过 n个a,n个b,n个c交换输出来解决.

例如: 
```
输入
3
ac
ab
输出
bbbaaaccc
```
这种情况就需要特判,防止输出NO导致去世.

考试代码,略丑:
```cpp
#include<bits/stdc++.h>
using namespace std;	
char s[13][13];
char c[13][13];
int n,by;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=2;i++)
	{
		scanf("%s",s[i]);
	}
	for(int i=1;i<=2;i++)
	{
		c[i][1] = 'a';
		c[i+4][1]='b';
		c[i+2][1]='c';
		c[i][4] = 'a';
		c[i+4][4]='b';
		c[i+2][4]='c';
	}
	c[1][2]='b',c[2][2]='c',c[3][2]='a';
	c[4][2]='b',c[6][2]='c',c[5][2]='a';
	c[2][3]='b',c[1][3]='c',c[4][3]='a';
	c[3][3]='b',c[5][3]='c',c[6][3]='a';
   //以上为处理六个字符串
	char a1=s[1][0],a2=s[1][1],b1=s[2][0],b2=s[2][1];
	bool pd=0;
	for(int i=1;i<=6;i++)
	{
		pd=0;
		for(int j=1;j<=3;j++)
		{
			if(j==3)
			{
				by=i;//特判特殊情况
			}
			if(a1==c[i][j]&&a2==c[i][j+1])
			{
				pd=1;break;
			}
			if(b1==c[i][j]&&b2==c[i][j+1])
			{
				pd=1;break;
			}
		}
		if(pd==0)//如果不包含模式串
		{
			printf("YES\n");
			for(int k=1;k<=n;k++)
			{
				printf("%c%c%c",c[i][1],c[i][2],c[i][3]);
			}
			return 0;
		}
	}
	if(by!=0)//特殊情况的话.
	{
		printf("YES\n");
		for(int i=1;i<=3;i++)
		{
			for(int j=1;j<=n;j++)
			{
				printf("%c",c[by][i]);
			}
		}
		return 0;
	}
	printf("NO");
	return 0;
}

```


---

## 作者：UperFicial (赞：0)

本题有两种构造方式，且都要考虑到。

- 第一种构造方式：

每种字符都恰好出现 $n$ 次，这提示我们可以构造一个长度为 $3$ 的循环节，循环节内 `a`、`b`、`c` 三种字符都恰好出现一次。

此时需要满足任意相邻的位置都不是字符串 $s$ 或 $t$。

特殊的，两个循环节首尾相连，还需要判断最后一个字母和第一个字母所构成的字符串是不是 $s$ 或 $t$。

- 第二种构造方式：

我们可以让第一个字母出现 $n$ 次，第二个字出现 $n$ 次，第三个字母出现 $n$ 次。

这就意味着它们相接的地方不能是 $s$ 或 $t$。这里只有两种情况。

为什么不用判断 `s` 或 `t` 是否是 `aa`、`bb` 或 `cc` 的形式呢？因为如果一旦 $s$ 或 $t$ 是这种形式，那么我们可以通过第一种构造方式解决。换句话说，我们应先考虑第一种构造方式，不可能的情况下， 再考虑第二种构造方式。

---

## 作者：Mine_King (赞：0)

这题要求构造长度为 $3n$ 的，字符 'a','b','c' 都出现 $n$ 次的字符串，那么不妨构造出一个长度为 $3$ 的，字符 'a','b','c' 都出现一次的字符串，然后重复输出 $n$ 次。  
对于这个长度为 $3$ 的字符串，其实可以直接暴力枚举找。

但是上面这种构造方案会过不了下面的数据：
```
2
ab
cb
```
也就是 $s$ 和 $t$ 的第二个字符都相同的情况。  
那么此时真的没有方法构造出字符串了吗？其实是有的，手动模拟以下就会发现可以构造出下面这个字符串：
```
bbaacc
```
究其本质，它其实 "bac" 的每个字符重复 $n$ 次得到的。  
也就是说，如果上面那种构造方式构造不出答案，那么就构造一个每个字符重复 $n$ 次的字符串。  
同样的，这个字符串的本质还是三个字符，也可以暴力枚举找出来。

最后我们发现，无论如何都能构造出满足要求的字符串。

Code:
```cpp
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n;
string s,t;
bool f[5][5];
int main()
{
	scanf("%d",&n);
	cin>>s>>t;
	puts("YES");
	f[s[0]-'a'][s[1]-'a']=true;
	f[t[0]-'a'][t[1]-'a']=true;
	for(char i='a';i<='c';i++)
		for(char j='a';j<='c';j++)
			for(char k='a';k<='c';k++)
				if(f[i-'a'][j-'a']==false&&f[j-'a'][k-'a']==false&&f[k-'a'][i-'a']==false)
					if(i!=j&&j!=k&&i!=k)
					{
						for(int l=1;l<=n;l++) printf("%c%c%c",i,j,k);
						return 0;
					}
                    //上面是第一种构造方法
                    //如果运行到了这里，说明第一种构造方法行不通
                    //那么就做下面的第二种构造方法。
	for(char i='a';i<='c';i++)
		for(char j='a';j<='c';j++)
			for(char k='a';k<='c';k++)
				if(f[i-'a'][j-'a']==false&&f[j-'a'][k-'a']==false)
					if(i!=j&&j!=k&&i!=k)
					{
						for(int l=1;l<=n;l++) printf("%c",i);
						for(int l=1;l<=n;l++) printf("%c",j);
						for(int l=1;l<=n;l++) printf("%c",k);
						return 0;
					}
	return 0;
}
```

---

