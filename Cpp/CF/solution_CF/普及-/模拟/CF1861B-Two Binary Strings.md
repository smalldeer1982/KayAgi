# Two Binary Strings

## 题目描述

You are given two strings $ a $ and $ b $ of equal length, consisting of only characters 0 and/or 1; both strings start with character 0 and end with character 1.

You can perform the following operation any number of times (possibly zero):

- choose one of the strings and two equal characters in it; then turn all characters between them into those characters.

Formally, you choose one of these two strings (let the chosen string be $ s $ ), then pick two integers $ l $ and $ r $ such that $ 1 \le l < r \le |s| $ and $ s_l = s_r $ , then replace every character $ s_i $ such that $ l < i < r $ with $ s_l $ .

For example, if the chosen string is 010101, you can transform it into one of the following strings by applying one operation:

- 000101 if you choose $ l = 1 $ and $ r = 3 $ ;
- 000001 if you choose $ l = 1 $ and $ r = 5 $ ;
- 010001 if you choose $ l = 3 $ and $ r = 5 $ ;
- 010111 if you choose $ l = 4 $ and $ r = 6 $ ;
- 011111 if you choose $ l = 2 $ and $ r = 6 $ ;
- 011101 if you choose $ l = 2 $ and $ r = 4 $ .

You have to determine if it's possible to make the given strings equal by applying this operation any number of times.

## 说明/提示

In the first test case, we can perform the following operations:

1. choose the string $ a $ , $ l = 2 $ , $ r = 4 $ ; after this operation, $ a $ is 01110001, $ b $ is 01110101;
2. choose the string $ b $ , $ l = 5 $ , $ r = 7 $ ; after this operation, $ a $ is 01110001, $ b $ is 01110001.

In the second test case, the strings are already equal.

In the third test case, we can perform the following operations:

1. choose the string $ a $ , $ l = 4 $ , $ r = 6 $ ; after this operation, $ a $ is 000111, $ b $ is 010111;
2. choose the string $ b $ , $ l = 1 $ , $ r = 3 $ ; after this operation, $ a $ is 000111, $ b $ is 000111;

In the fourth and fifth test cases, it's impossible to make the given strings equal.

## 样例 #1

### 输入

```
7
01010001
01110101
01001
01001
000101
010111
00001
01111
011
001
001001
011011
010001
011011```

### 输出

```
YES
YES
YES
NO
NO
NO
YES```

# 题解

## 作者：kimidonatsu (赞：4)

# CF1861B Two Binary Strings 题解

简单的找规律题，可以发现我们需要将序列处理成形如 $0000 \dots 01111\dots1$ 这样的形式，显然有 $a_{i}a_{i + 1} = b_{i}b_{i + 1} = 01$ 时可通过覆盖操作转换为所求的相同序列。

由于数据范围只有 $5000$ 且题目保证第一位为 $0$ 与最后一位为 $1$，考虑直接枚举。

```cpp
#include <bits/stdc++.h>

void solve() {
	int t;
	std::cin >> t;
	while (t--) {
		std::string a, b;
		std::cin >> a;
		std::cin >> b;
		
		bool flag = false;
		for (int i = 0; i + 1 < a.size(); i++) {
			if (a[i] == b[i] && a[i] == '0' && a[i + 1] == b[i + 1] && a[i + 1] == '1') {
				flag = true;
				break;
			}
		}
		
		if (flag) std::cout << "YES\n";
		else std::cout << "NO\n";
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	
	solve();
	return 0;
}

```


---

## 作者：Xy_top (赞：3)

没看到 $0$ 开始 $1$ 结尾的条件，写了个 DP，然后还过了，写篇题解纪念一下。

四个 DP 数组，分别代表两个字符串内 $l\cdots r$ 能不能变成 $1$ 或者 $0$，转移简单就不说了。

答案怎么得呢，令 $ans_i$ 为 $1\cdots i$ 能不能一样，然后 $ans_i \to ans_i | (ans_{j-1}\&\text{(j 到 i 能否一样)})$ 即可。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
#define N 5005
using namespace std;
string s, t;
bool fs[N][N], gs[N][N];
bool ft[N][N], gt[N][N];
bool ans[N];
vector <int> v, v_;
void solve () {
	v.clear ();
	v_.clear ();
	cin >> s >> t;
	For (i, 0, s.size())ans[i] = 0;
	For (i, 1, s.size()) {
		For (j, 1, s.size()) fs[i][j] = gs[i][j] = ft[i][j] = gt[i][j] = 0;
	}
	For (i, 0, s.size() - 1) {
		if (s[i] == '0') v.push_back (i + 1);
		else v_.push_back (i + 1);
	}
	for (int i = 0; i < v.size(); i ++) for (int j = i + 1; j < v.size(); j ++) fs[v[i]][v[j]] = true;
	for (int i = 0; i < v_.size(); i ++) for (int j = i + 1; j < v_.size(); j ++) gs[v_[i]][v_[j]] = true;
	for (int i : v) fs[i][i] = 1;
	for (int i : v_) gs[i][i] = 1;
	v.clear ();
	v_.clear ();
	For (i, 0, t.size() - 1) {
		if (t[i] == '0') v.push_back (i + 1);
		else v_.push_back (i + 1);
	}
	for (int i = 0; i < v.size(); i ++) for (int j = i + 1; j < v.size(); j ++) ft[v[i]][v[j]] = true;
	for (int i = 0; i < v_.size(); i ++) for (int j = i + 1; j < v_.size(); j ++) gt[v_[i]][v_[j]] = true;
	for (int i : v) ft[i][i] = 1;
	for (int i : v_) gt[i][i] = 1;
	ans[0] = true;
	For (i, 1, s.size()) {
		For (j, 1, i) {
			ans[i] |= ans[j - 1] && ((fs[j][i] && ft[j][i]) || (gs[j][i] && gt[j][i]));
		}
	}
	if (ans[s.size()]) cout << "YES";
	else cout << "NO";
	For (i, 1, s.size()) {
		For (j, 1, i) {
			ans[i] |= ans[j - 1] && ((fs[j][i] && ft[j][i]) || (gs[j][i] && gt[j][i]))
		}
	}
}
signed main () { 
	ios :: sync_with_stdio (false);
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：int_stl (赞：1)

对于这道题，如果你是一个~~爱观察的好孩子~~，就会发现一个规律。  
对于样例一，我们发现：  
$\textcolor{blue}{01}010001$  
$\textcolor{blue}{01}110101$  
$\textcolor{blue}{01}001$  
$\textcolor{blue}{01}001$  
$00\textcolor{blue}{01}01$  
$01\textcolor{blue}{01}11$  
$00001$  
$01111$  
$011$  
$001$  
$001001$  
$011011$  
$\textcolor{blue}{01}0001$  
$\textcolor{blue}{01}1011$  
可见，只要是出现 $01$ 并且所在位置相同，那就输出 `YES`，否则输出 `NO`。  
根据这个思路，可得到以下代码：
```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string init(string a, string b) {
    for (int i = 0; i < a.size() - 1; i++) {
        for (int j = 0; j < b.size() - 1; j++) {
            if (a[i] == b[i] && a[i] == '0' && b[i] == '0' && a[i + 1] == b[i + 1] && a[i + 1] == '1' && b[i + 1] == '1') {
                return "YES";
            }
        }
    }
    return "NO";
}

int main() {
    int t;
    cin >> t;
    cin.ignore();
    while (t--) {
        string a, b;
        getline(cin, a);
        getline(cin, b);
        string result = init(a, b);
        cout << result << endl;
    }

    return 0;
}

```
~~所以说，这道题只要有脑子就能想出来。~~

---

## 作者：_空白_ (赞：1)

从题中发现最左端一定为 $0$，最右端一定为 $1$，因而只要把两个字符串都刷成左边全 $0$，右边全 $1$ 的相同字符串即可。

而要满足这个条件只需找到一对相同位置且相邻的 $0$ 和 $1$ 即可满足。

$AC$ $code$：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5100;
char a[MAXN],b[MAXN];
int main()
{
	int n;
	cin>>n;
	while(n--)
	{
		cin>>a>>b;
		int len=strlen(a);
		bool fl=1;
		for(int i=1;i<=len-1;i++)
		{
			if(a[i]=='1'&&b[i]=='1'&&a[i-1]=='0'&&b[i-1]=='0')
			{
				cout<<"YES\n";
				fl=0;
				break;
			}
		}
		if(fl)
			cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：_Haoomff_ (赞：1)

### 翻译
有两个长度相等且以 $0$ 开头、以 $1$ 结尾的 $01$ 串。现在可以对任意一个串不限次数的做操作：选择两个下标 $l,r$（在串上这两个位置的字符必须相同），把 $[l,r]$ 区间内的字符全部替换为与它们相同的字符。

求能否在若干次操作后两字符串相等。

若能达到，输出 ```YES```；否则输出 ```NO```。
### 思路
由于字符串必须是 $0$ 开头 $1$ 结尾，且不限操作次数，为了方便，我们不妨将两个字符串都替换为 $000…01…111$（即前面若干个连续的 $0$，后面若干个连续的 $1$）。这样的话，只要能找出一个位置满足 $a_i=0$ 且 $a_{i+1}=1$，那么必定有解，因为开头必须为 $0$ 结尾必须为 $1$，从开头到 $i$ 位置替换为 $0$，从 $i+1$ 位置到末尾替换为 $1$ 就可以了。

所以问题就转化成了：是否有一个位置（下标为 $i$），满足 $a_i=0$ 且 $a_{i+1}=1$ 且 $b_i=0$ 且 $b_{i+1}=1$。若有，则输出 ```YES```；否则输出 ```NO```。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	for(string a,b;t--;){
		bool flag=false;
		cin>>a>>b;
		for(int i=0;i<a.size()-1;++i)
			if(a[i]=='0'&&a[i+1]=='1'&&b[i]=='0'&&b[i+1]=='1'){
				cout<<"YES\n";
				flag=true;
				break;
			}
		if(!flag)cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：Crazyouth (赞：1)

**翻译**

有两个等长 $01$ 串 $a,b$，以 $0$ 开头以 $1$ 结尾，你可以对任意一个使用不限次数的以下操作：

- 选择两个下标 $i,j$，需保证这你要操作的串上的这两个位置上的字符相同，把它们中间的字符全部替换为它们。

问能否使 $a=b$。

**分析**

$0$ 开头 $1$ 结尾是关键。打 CF 一定要学会研究样例。不妨把两个字符串都变成 $000\cdots01\cdots111$，则问题转化为能否找到一个下标 $i$ 使 $a_i=0,b_i=0,a_{i+1}=1,b_{i+1}=1$。有则 `YES`，否则 `NO`。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int flag=0;
		string a,b;
		cin>>a>>b;
		for(int i=1;i<a.size();i++)
		{
			if(a[i]=='1'&&b[i]=='1'&&a[i-1]=='0'&&b[i-1]=='0')
			{
				cout<<"YES"<<endl;
				flag=1;
				break;
			}
		}
		if(!flag) cout<<"NO"<<endl;
	}
}

---

## 作者：myyyIisq2R (赞：0)

### [CF1861B Two Binary Strings](https://www.luogu.com.cn/problem/CF1861B)

## Solution

研究样例发现只要在串中出现一对位置相同的 $\text{01}$ 串便可输出 $\text{YES}$，否则输出 $\text{NO}$。

例如：

$\color{red}\text{01}\color{black} \text{010001}$ 和 $\color{red}\text{01}\color{black}\text{110101}$

$\text{00}\color{red}\text{01}\color{black}\text{01}$ 和 $\text{01}\color{red}\text{01}\color{black}\text{11}$

## AC Code
```cpp
#include <bits/stdc++.h> //较短
using namespace std;
#define int long long
void solve() {
	string a, b;
	cin >> a >> b;
	for (int i = 0; i < a.length() - 1; i++) {
		if (a.substr(i, 2) == "01") {
			if (b.substr(i, 2) == "01") {
				cout << "YES" << endl;
				return;
			}
		}
	}
	cout << "NO" << endl;
}
 
signed main() {
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}
```

---

## 作者：tang_mx (赞：0)

很简单的一道题，赛时写假了，改完之后来写篇题解。

这题一个很简单的思路就是找到一个位置 $i$，使得字符串 $s$ 从 $s[0]$ 到 $s[i]$ 全为变成 $0$，剩下的全部变为 $1$，从而使字符串变为类似 $00011111$ 的样式。

直接扫 $a,b$ 两个字符串，看能否找到一个相同的位置 $i$，使得 $a[i],b[i]$ 均为 $0$ 并且$a[i+1],b[i+1]$ 均为 $1$。

```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long

using namespace std;

inline int read(){
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*y;
}

const int N=2e5+10;
string a,b;
int t,n;

void solve(){
	cin>>a>>b;
	int len=a.length();
	for(int i=1;i<len;i++){
		if(a[i]=='1'&&a[i-1]=='0'&&b[i]=='1'&&b[i-1]=='0'){
			cout<<"YES\n";return;
		}
	}
	cout<<"NO\n";
}

int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```


---

## 作者：One_JuRuo (赞：0)

## 思路

~~最近熬夜打 CF，视力下降了。没看到题目里给了第一位和最后一位必定是 $0$ 和 $1$，导致想了半天。~~

考虑枚举字符串的位置 $i$。

首先如果遇到了两个串第 $i$ 位都是 $1$，那么可以直接覆盖中间的片段，一定能成功。

如果遇到不同的位置，考虑找到最近的 $0$ 与第一位的 $0$ 做操作，选最近的是为了减少损失相同 $1$ 的可能。如果找不到就肯定无解。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,flag,xz;
char s1[5005],s2[5005];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%s",s1+1,s2+1),n=strlen(s1+1),flag=0;
		for(int i=1;i<=n;++i)
		{
			if(s1[i]=='1'&&s2[i]=='1'){break;}
			if(s1[i]!=s2[i])
			{
				int ff=0;
				for(int j=i+1;j<n;++j)
					if(s1[j]==s2[j]&&s1[j]=='0')
					{
						ff=1,i=j;break;
					}
				if(!ff)
				{
					flag=1;break;
				}
			}
		}
		if(flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
 
```

---

