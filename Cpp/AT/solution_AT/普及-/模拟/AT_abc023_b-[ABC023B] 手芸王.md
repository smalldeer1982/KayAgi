# [ABC023B] 手芸王

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc023/tasks/abc023_b

高橋君は趣味でアクセサリーを作っている。

アクセサリーは `a`, `b`, `c` のいずれか $ 1 $ 文字が書かれたブロックを横 $ 1 $ 列に並べることで作成できる。

高橋君は、以下の手順でアクセサリーの作成を行う：

- 手順 $ 0 $ : 高橋君は `b` $ 1 $ 文字からなるアクセサリーを作成する。

以降の手順では、既にあるアクセサリーの両端にブロックを $ 1 $ つずつ追加することでアクセサリーを改造する。

- 手順 $ 3n\ +\ 1\ (n\ ≧\ 0) $ : 手順 $ 3n $ で完成したアクセサリーの左端に文字 `a` が書かれたブロックを、右端に文字 `c` が書かれたブロックを付け足す。
- 手順 $ 3n\ +\ 2\ (n\ ≧\ 0) $ : 手順 $ 3n+1 $ で完成したアクセサリーの左端に文字 `c` が書かれたブロックを、右端に文字 `a` が書かれたブロックを付け足す。
- 手順 $ 3n\ (n\ ≧\ 1) $ : 手順 $ 3n-1 $ で完成したアクセサリーの左端に文字 `b` が書かれたブロックを、右端に文字 `b` が書かれたブロックを付け足す。

高橋君はアクセサリーの作成を好きな手順の直後に終了することができる。終了した場合、アクセサリーには、アクセサリーを構成するブロックに書かれた文字を左から右に読んだものと同じ名前が付けられる。

例えば、手順 $ 0 $, $ 1 $, $ 2 $, $ 3 $ それぞれの直後にアクセサリーの作成を終了した場合、アクセサリーの名前は順に、`b`, `abc`, `cabca`, `bcabcab` となる。

文字列 $ S $ が与えられるので、その文字列がアクセサリーの名前として考えられるかを判定し、考えられるなら何番目の手順の直後にアクセサリーの作成を終了したのかを求めよ。

## 说明/提示

### Sample Explanation 1

\- 手順 $ 1 $ の直後にアクセサリーの作成を終了したときのアクセサリーの名前は `abc` となる。

### Sample Explanation 2

\- 文字列 `abcabc` はアクセサリーの名前として考えられない。

### Sample Explanation 3

\- 文字列 $ S $ には `a`, `b`, `c` 以外の文字が入ることがある。

## 样例 #1

### 输入

```
3
abc```

### 输出

```
1```

## 样例 #2

### 输入

```
6
abcabc```

### 输出

```
-1```

## 样例 #3

### 输入

```
7
atcoder```

### 输出

```
-1```

## 样例 #4

### 输入

```
19
bcabcabcabcabcabcab```

### 输出

```
9```

# 题解

## 作者：亦枫 (赞：4)

## Solution

题意：给你一个最大操作次数 $ n $ 和一个字符串 $ a $，问你能否按题目中的规则进行小于等于 $ n $ 次操作后，得到 $ a $。

首先，第 $ 0 $ 次操作是将一个空串 $ s $ 赋值为 ```b```。

然后：
对于第 $ i $ 次操作

1.$a\equiv1\pmod{3}$ 则在 $ s $ 左边加上一个字符 ```a```，右边加上字符 ```c```。

1.$a\equiv2\pmod{3}$ 则在 $ s $ 左边加上一个字符 ```c```，右边加上字符 ```a```。

1.$a\equiv0\pmod{3}$ 则在 $ s $ 左边加上一个字符 ```b```，右边加上字符 ```b```。

那么，接下来，我们直接模拟即可。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
string s="b",a;
int main() {
	scanf("%d\n",&n);
	cin>>a;
	if(n==1&&a=="b") {
		printf("0\n");
		return 0;
	}//一个特判，注意这种情况 
	for(int i=1; i<=n; i++) {
		if(i%3==1)s='a'+s+'c';
		else if(i%3==2)s='c'+s+'a';
		else s='b'+s+'b';
		if(s.size()>n)break;//如果已经超出a的长度则直接结束 
		if(s==a) {
			printf("%d\n",i);
			return 0;
		}
	}
	printf("-1\n");
}
```


---

## 作者：伟大的王夫子 (赞：3)

毕竟是 ABC 的题目，但是洛谷上其他题解的解法都十分复杂，这里提供一种 string 实现的方便的算法。

暴力枚举每一步，对于 $i$ 这一步，求出 $i$ 除以 3 的余数，判断应该采取什么决策，然后在 string 字符串进行更新，相加。如果相等，就输出。

接下来，问题来了，我们怎么判断是否可行呢？

其实也很简单。在中途累加时，如果当前字符串长度大于目标字符串长度 $n$ ，那么直接输出 -1。时间复杂度为 $O(n)$。

我看到有些题解各种神奇的解法都有，个人认为，在这种题上用实在意义不是非常大，实现也较为复杂。杀鸡焉用牛刀。应该通过暴力算法，来挖掘问题的本质。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string a;
int main() {
	scanf("%d", &n);
	cin >> a;
	string b;
	b = 'b';
	for (register int i = 1; i <= 10000; ++i) {
		if (b == a) {
			printf("%d\n", i - 1);
			return 0;
		}
		if (b.size() > n) break;
		if (i % 3 == 1) b = 'a' + b + 'c';
		if (i % 3 == 2) b = 'c' + b + 'a'; 
		if (i % 3 == 0) b = 'b' + b + 'b';
	}
	puts("-1");
}
```

---

## 作者：火车司机 (赞：2)

## 简要分析

另外一篇题解应该是错误的，他可能题意理解错了

在正确的题意中操作是要按顺序来的

第 $0$ 步建立一个字符串 "b"

第 $3n+1$ 步将原先的字符串 s 变为 "a"+s+"c"

第 $3n+2$ 步将原先的字符串 s 变为 "c"+s+"a"

第 $3(n+1)$ 步将原先的字符串 s 变为 "b"+s+"b" 

所以在那篇题解的基础上我们还需要判断操作的顺序有没有错误

AT输出要换行千万不能忘！！！

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
using namespace std;
int n, ans;
char s[105];
signed main()
{
	scanf("%lld%s", &n, s + 1);
	if (!(n & 1))
	{
		puts("-1");
		return 0;
	}
	for (ri i = 1; i <= n; ++i)
		if (s[i] < 'a' || s[i] > 'c')
		{
			puts("-1");
			return 0;
		}
	if (s[(n + 1) >> 1] != 'b')
	{
		puts("-1");
		return 0;
	}
	if (n == 1)
	{
		puts("0");
		return 0;
	}
	for (ri i = ((n + 1) >> 1) + 1, j = i - 2; j; ++i, --j)
	{
		++ans;
		if (ans % 3 == 1)
		{
			if (s[i] != 'c' || s[j] != 'a')
			{
				puts("-1");
				return 0;
			}
		}
		if (ans % 3 == 2)
		{
			if (s[i] != 'a' || s[j] != 'c')
			{
				puts("-1");
				return 0;
			}
		}
		if (ans % 3 == 0)
		{
			if (s[i] != 'b' || s[j] != 'b')
			{
				puts("-1");
				return 0;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：Krimson (赞：2)

~~某车司机:我看你要几发才能A掉这题~~

------------
毕竟是ABC的B题,还是非常水的,主要难度在于从这个机翻上读懂题意  
就是每次有三个操作,分别可以做到  
1.'a'+S+'c'  
2.'c'+S+'a'  
3.'b'+S+'b'  
问从开头的一个串“b”经过k次操作之后能否得到最后给定的串  
首先不难发现如果能实现,那k肯定为$\lfloor\frac{n}{2} \rfloor$  
然后$n$是奇数  
最后再用两个指针从头和尾模拟一下就好了  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
int n;
string s;
int main(){
    cin>>n;
    cin>>s;
    s=" "+s;
    if(!(n&1)){
        puts("-1");
        return 0;
    }
    ri l,r;
    for(l=1,r=n;l<r;++l,--r){
        if(!((s[l]=='c'&&s[r]=='a')||(s[l]=='a'&&s[r]=='c')||(s[l]=='b'&&s[r]=='b')))break;
    }
    if(l!=r) puts("-1");
    else if(s[l]!='b') puts("-1");  
    else print(n/2);
    return 0;
}
```


---

## 作者：cff_0102 (赞：1)

~~这道题难就难在读懂机翻。~~

[这里有一篇题解思路错误](https://endless1936.blog.luogu.org/solution-at1328)，没有必要这么麻烦。这个题解可以被 `5 bbbbb` hack掉。

首先，我们有一个字符串 $s$，内容是 `b`。

接着进行 $n$ 次操作，其中第 $i$ 次操作：

1. $i\equiv1\pmod{3}$ 时，在 $s$ 左边加上一个字符 `a`，右边加上字符 `c`。

1. $i\equiv2\pmod{3}$ 时，在 $s$ 左边加上一个字符 `c`，右边加上字符 `a`。

1. $i\equiv0\pmod{3}$ 时，在 $s$ 左边加上一个字符 `b`，右边加上字符 `b`。

给出 $n$ 和一个字符串 $s$，问在 $n$ 次操作内是否可以得到 $s$ 。

那么我们直接模拟就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string a;
int main(){
	cin>>n>>a;
	string s="b";//初始化
	for(int i=1;i<=n;i++){
		if(s==a){//ok了就直接输出，也不用特判a=="b"
			cout<<i-1<<endl;//注意必须换行
			exit(0);
		}
		if(i%3==0){//按题意做
			s="b"+s+"b";
		}else if(i%3==1){
			s="a"+s+"c";
		}else{
			s="c"+s+"a";
		}
	}if(s==a){//最后判断一次
		cout<<(n-1)/2<<endl;
		exit(0);
	}cout<<-1<<endl;//否则输出-1
	return 0//轻松AC；
}//不要抄
```
希望管理可以过这篇题解。

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc023_b)   
题意：   
给你一个字符串 $s$，这个字符串是按照一定规则构成的：   
对于第 $i$ 次操作，如果 $i \bmod3 =0$，那么就在 $s$ 的最前面和最后面各加 $1$ 个 ```b```；如果 $i \bmod3=1$，那么就在 $s$ 的最前面加上 ```a```，最后面加上 ```c```；如果 $i\bmod3=2$，那么就在 $s$ 的最前面加上 ```c```，最后面加上 ```a```。   
给你一个字符串 $a$，它初始只有一个字符 ```b```，按照上述规则构造，如果可以经过 $m$ 次操作构造出来，那么就 输出 $m$，否则输出 $-1$。   
解法：   
按题意模拟就可以，但是要特判 $s$ 是 ```b``` 的情况。   
CODE：  
```cpp
#include <iostream>
#include <string>
using namespace std;
int n;
string s,a="b"; 
int main(void){
	cin>>n>>s;
	for(int i=1;;i++){
		if(a==s){
			cout<<i-1<<endl;
			return 0;
		}
		if(a.length()>n){
			cout<<"-1"<<endl;
			return 0;
		}
		if(i%3==1){
			a="a"+a+"c";
		}else if(i%3==2){
			a="c"+a+"a";
		}else{
			a="b"+a+"b";
		}
	}
}
```


---

## 作者：Tear_stains (赞：0)

题意：

给定一个初始字符串 $b$ 和 $n$ 次操作，

第 $i$ 次操作方法为：

如果 $i \bmod 3 = 1$，则在前加 $a$ 后加 $c$；

如果 $i \bmod 3 = 2$，则在前加 $c$ 后加 $a$；

如果 $i \bmod 3 = 0$，则在前加 $b$ 后加 $b$；

思路：

判断每次操作的方法，模拟即可。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;string a, s ="b";
string x = "a", y = "b", z = "c";
int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	cin >> a;
	if(n == 1 && a == "b") {
		cout << "0" << endl;
		return 0;
	} else {
		for(int i = 1;i <= n; ++i) {
			if(i % 3 == 1) {
	            s = x + s + z;
			} else if(i % 3 == 2) {
				s = z + s + x;
			} else {
				s = y + s + y;
			}
			if(s.size() > a.size()) {
				break;
			}
			if(s == a) {
				cout << i << endl;
				return 0;
			}
		}
	}
	cout << "-1" << endl;
	return 0;
}
```




---

