# Déjà Vu

## 题目描述

定义一个回文串为正着读与倒着读都相同的字符串，比如 `z`，`aba` 和 `abccba` 都是回文串。你恨回文串因为它给你“既视感”。

现有一字符串  $s$，你必须插入恰好一个字母 `a` 在  $s$ 的某处。若操作后的新字符串可能**不是**回文串，你需要找到一个例子；反之，你需要报告这是不可能的

比如，假设  $s$ 为 `cbabc`，通过插入一个字母 `a`，可以得到 `acbabc`、`cababc`、`cbaabc`、`cbabac`、或 `cbabca`。然而，`cbaabc` 是回文串，所以你应当输出其它字符串中的一个。

## 说明/提示

$1 \leq t \leq 10^4$

字符串总长度不超过  $3 \times 10^5$

## 样例 #1

### 输入

```
6
cbabc
ab
zza
ba
a
nutforajaroftuna```

### 输出

```
YES
cbabac
YES
aab
YES
zaza
YES
baa
NO
YES
nutforajarofatuna```

# 题解

## 作者：BYWYR (赞：3)

## Problem

给你一个字符串 $s$，让你插入一个字符 ```a```，使得新的字符串不是一个回文串。

多组数据。

题目 $\texttt{Déjà Vu}$ 的意思：~~以前见过？~~

## Soulution

考虑一个字符串不是回文串，即 $s[i] ≠ s[len-i-1]$。

也就是说，如果想要一个字符串加上 ```a```，变成不回文串，只要判断每个 $s[len-i-1]$ 是不是 ```a``` 就可以了。

当且仅当一个字符串里全是 ```a```，输出 ```NO```。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
string s;
int main(){
	cin>>t;
	while(t--){
		cin>>s;
		bool flag=false;
		int len=s.size();
		for(int i=0;i<len;i++){
			if(s[i]!='a'){
				flag=false;
				break;
			}
			flag=true;
		}
		if(flag==true){//字符串里全是a
			cout<<"NO\n";
			continue;
		}
		cout<<"YES\n";
		for(int i=0;i<len;i++){
			if(s[len-i-1]!='a'){//判断每个s[len-i-1]是不是a
				for(int j=0;j<i;j++)
					cout<<s[j];
				cout<<'a';
				for(int j=i;j<len;j++)
					cout<<s[j];
				cout<<endl;
				break;
			}
		}
	}
	return 0;	
}
```


---

## 作者：conprour (赞：2)

# 前言
一开始把数据范围看成了 $n\le 3\times 10^5$ ，难以下手。后来才发现其实是   $\sum n\le 3\times 10^5$ ，那么 $O(n)$ 算法即可，算是提醒一下和我一样看错的人。
# 分析
考虑输出 ``NO`` 的情况，当且仅当原串全是 ``a`` 。

对于其他情况，判断一个串是否是回文串有很多方法。

由于只需要考虑加上一个 ``a`` 之后是不是回文串，最简单地，从头到尾扫一遍，判断哪个位置有 ``s[len-i+1]!='a'``，即是一个合法的位置，记录位置后直接跳出循环，直接输出即可。

# 代码
十分清晰简短。
```cpp
int main()
{
	int T=read();
	while(T--)
	{
		scanf("%s",s+1);
		int len=strlen(s+1),pos=0;
		for(int i=1;i<=len;i++)	
			if(s[len-i+1]!='a') {pos=i;break;}
		if(!pos) printf("NO\n");
		else 
		{
			printf("YES\n");
			for(int i=1;i<pos;i++) putchar(s[i]);
			putchar('a');
			for(int i=pos;i<=len;i++) putchar(s[i]);
			putchar('\n');
		}
	}
	return 0;
}
```


---

## 作者：black_trees (赞：1)


这场有那么一丢丢毒瘤。

不过A题还是一如既往的送分。

---

看一下题面有啥要求。

>if there is no solution, output "NO".

那么考虑怎么判无解（很明显无解情况少一点）。

这里要求你添加 `'a'` 之后**不可以出现**回文。

思考一下：只有原串全部是 `'a'` 才无解。

为什么？

如果你的字符串里有任何 `'a'` 以外的东西。

因为回文是需要像 `a[i]=a[n-i+1]` 一样的对应的。

可以直接把 `a` 放到这个不同字符对应的位置上。

所以一定有解。

然后考虑怎么构造。

上面那里已经说了，回文是要两个两个对应的。

找到第一个不是 `'a'` 的位置，在对应位置加一个 `'a'`即可。

>If there are multiple solutions, you may print any.

这里多解任意输出即可，所以只要合法就行。

code:

```cpp


#include<bits/stdc++.h>
using namespace std;

int T;

int main(){
	cin>>T;
	for(register int _=1;_<=T;++_){
		string s;
		cin>>s;int n=s.size();
		s=' '+s;
		int fuc=0;
		for(register int i=1;i<=n;++i){
			if(s[i]!='a'){
				fuc=0;break;
			}
			fuc=1;
		}
		if(fuc==1){
			cout<<"NO\n";
			continue;
		}//无解
		cout<<"YES\n";
		for(register int i=1;i<=n;++i){
			if(s[n-i+1]!='a'){//找到第一个位置
				for(register int j=1;j<i;++j){
					cout<<s[j];
				}cout<<"a";
				for(register int j=i;j<=n;++j){
					cout<<s[j];
				}cout<<endl;
				break;
			}
		}
	}
	return 0;
}
```


---

## 作者：Hooch (赞：0)

### 题目大意

给你一个字符串，让你插入一个字符 `a`，使得新字符串**不是一个回文串**。

### 思路

首先我们思考**一个字符串是回文串**的条件。

也就是：设原字符串 $s$ 长度为 $n$，则对于每一个下标 $i\ (1\le i\le n)$，$s_i=s_{n-i+1}$。

那么我们插入这个字符 `a`，**必须不满足成为一个回文串的条件**。设 $x$ 为插入的字符 `a` 在新字符串的下标，则 $s_x\ne s_{n-x+1}$。我们要找到这样的一个位置，找到有解，没找到则无解。

关于这个策略的正确性也很好证，设字符 `a` 插入的下标是 $x$。

若 $s_x=s_{n-x+1}$ 也仍不是个回文串，那么**一定有其它位置不满足 $s_i=s_{n-i+1}$**，那么可以将 `a` 插入到**这两个位置的其中一个的对应位置**，新串一定不是个回文串。

否则 $s_x\ne s_{n-x+1}$，仍不是个回文串。

### 代码解析

注释都在代码中。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t; string s;
main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> s; int pos = 0x3f3f3f3f; //pos 即代表我所说的 x
		for (int i = 0; i < s.length(); ++i) {
			if (s[s.length() - i - 1] != 'a') { //找到了那个使新串不是回文串的下标 x
				pos = i;
				break;
			}
		}
		if (pos ^ 0x3f3f3f3f) {
			cout << "YES" << endl;
			for (int i = 0; i < s.length(); ++i) {
				if (i == pos) cout << 'a'; //到了 a 插入的位置，输出字符 a
				cout << s[i];
			} 
			cout << endl;
		} else cout << "NO" << endl; //无解
	}
}
```

---

## 作者：听取MLE声一片 (赞：0)

很容易发现，只要插入一个 `a` 使得字符串不回文就直接输出就行。

我们一眼就可以看出可以从头到尾遍历，往里面插入 `a` ，并不断看新字符串是不是回文串，但是复杂度为 $n^2$ ，不能通过本题。

根据回文的定义，回文串左右两遍是对称的，也就是编号为 `i` 的字符与编号为 `n-i-1` 的字符是相同的（下标从 `1` 开始）,也就是说只要判断每个 `n-i-1` 是不是 `a` 就可以了。

因为这道题不卡常（主要是因为懒），我用的 `string` 实现，本质上是在原字符串中插入一个 `a` 。

代码：

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int a[300001],b[300001],c[300001];
int n,t;
int main()
{
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++){
			char x;
			cin>>x;
			a[i]=x-'0';
		}
		for(int i=1;i<=n;i++){
			char x;
			cin>>x;
			b[i]=x-'0';
		}
		int s1=0,s2=0;
		for(int i=1;i<=n;i++){
			c[i]=0;
			if(a[i]==0)
				s1++;
			if(a[i]==1)
				s2++;
			if(s1==s2)
				c[i]=1;
		}
		int pd=1,sum=0;
		for(int i=n;i>=1;i--){
			if(!pd)
				break;
			a[i]=(a[i]+sum)%2;
			if(c[i]==0){
				if(a[i]!=b[i]){
					pd=0;
					cout<<"NO\n";
				}
				continue;
			}
			else{
				if(a[i]!=b[i])
					sum++;
			}
		}
		if(pd)
			cout<<"YES\n";
	}
	return 0;
}

```


---

## 作者：vectorwyx (赞：0)

如果 $s$ 为全 `a` 串，那么答案一定为 `NO`。

否则，找到任意一个不为 `a` 的 $s_i$（下标从 $0$ 开始）。如果 $i< n-i$，那么就在 $s_{n-i}$ 的右面插入 `a`，否则在 $s_{n-i}$ 的左面插入 `a`。不难看出这样插入的 `a` 和 $s_i$ 在新串中一定是对称的，由于 $s_i$ 不为 `a`，所以得到的新串一定不是回文串。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

void work(){
	string s;
	cin>>s;
	int n=s.size()-1;
	fo(i,0,n) if(s[i]!='a'){
		puts("YES");
		int k=n-i;
		if(k<=i){
			fo(j,0,k-1) putchar(s[j]);
			putchar('a');
			fo(j,k,n) putchar(s[j]);
			puts("");			
		}else{
			fo(j,0,k) putchar(s[j]);
			putchar('a');
			fo(j,k+1,n) putchar(s[j]);
			puts("");							
		}
		return;
	}
	puts("NO");
}

int main(){
	int T=read();
	while(T--) work(); 
	return 0;
}
```


---

## 作者：kradcigam (赞：0)

开场真的降智了。

题目翻译：

给定一个字符串问您能不能在任意位置添加一个字符a，使得新字符串不回文。

这道题目想一想就会发现除非字符串全是a，否则一定有解。为什么，因为如果不是全a就一定可以找到一个位置添加a，和它对面的字符不是a。

代码：
```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define LL long long
#define mp make_pair
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){
	char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
int main(){
	int _=read();F(__,1,_){
		string st;
		cin>>st;
		bool f=true;
		F(i,0,SZ(st))
			if(st[i]!='a'){
				f=false;
				puts("YES");
				break;
			}
		if(f)puts("NO");
		else{
			bool fg=true;
			F(i,0,SZ(st)){
				if(fg&&st[SZ(st)-i]!='a'){
					putchar('a');
					fg=false;
				}
				putchar(st[i]);
			}puts("");
		}
	}
	return 0;
}
```

---

## 作者：feicheng (赞：0)

## $\textbf{Description}$

多组询问，每次给定一个长度为 $n$ 的字符串，求一种方案使得加入一个字符 `a` 后使其不是回文串，无解输出 `NO`

**限制**

$1\le T \le 10^4,1\le \sum n \le3\times 10^5$

## $\textbf{Solution}$

由于 $n$ 的范围比较小，我们可以考虑枚举 `a` 出现的位置，然后判断加入之后是否是回文串即可。

如何判断回文串？

只要在 `a` 的对应位置不是 `a` 就不是回文串。

时间复杂度：$\Theta(\sum n)$

## $\textbf{Code}$

```cpp
inline void solve() {
    int pos = 0 ;
    const int len = strlen(s+1) ;
    for(int i = 1;i <= len;++i) if(s[len+1-i] != 'a') { pos = i ;break;}//寻找位置，找到一个就可以
    if(!pos) return cout << "NO\n",void() ;
    cout << "YES\n" ;
    for(int i = 1;i < pos;++i) cout << s[i] ;
    cout << 'a' ;
    for(int i = pos;i <= len;++i) cout << s[i] ;
    cout << '\n' ;
}
```



---

