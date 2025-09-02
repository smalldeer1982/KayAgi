# Best Binary String

## 题目描述

You are given a string $ s $ consisting of the characters 0, 1 and/or ?. Let's call it a pattern.

Let's say that the binary string (a string where each character is either 0 or 1) matches the pattern if you can replace each character ? with 0 or 1 (for each character, the choice is independent) so that the strings become equal. For example, 0010 matches ?01?, but 010 doesn't match 1??, ??, or ????.

Let's define the cost of the binary string as the minimum number of operations of the form "reverse an arbitrary contiguous substring of the string" required to sort the string in non-descending order.

You have to find a binary string with the minimum possible cost among those that match the given pattern. If there are multiple answers, print any of them.

## 说明/提示

In the first test case of the example, the cost of the resulting string is $ 0 $ .

In the second test case, the cost of the resulting string is $ 2 $ : we can reverse the substring from the $ 1 $ -st character to the $ 5 $ -th character, and we obtain the string 00101. Then we reverse the substring from the $ 3 $ -rd to the $ 4 $ -th character, and we obtain the string 00011, which is sorted in non-descending order.

## 样例 #1

### 输入

```
4
??01?
10100
1??10?
0?1?10?10```

### 输出

```
00011
10100
111101
011110010```

# 题解

## 作者：Iniaugoty (赞：1)

## problem

给定由 `1` 或 `0` 或 `?` 所组成的字符串，你需要用 `0` 或 `1` 替换 `?`。

我们将 $s_l,s_{l+1},\dots,s_r$ 反转称为一次操作。

你要使通过“反转”操作使原字符串成为升序的操作次数尽可能的小。

问最终构造出的字符串，有多解输出其一。

## solution

先上结论：

- 对于 $i=1$，若 $s_i$ 是 `?`，则令 $s_i$ 为 `0`。

- 对于 $i>1$，若 $s_i$ 是 `?`，则令 $s_i$ 为 $s_{i-1}$。

证明：

- 当 $s_1$ 为 `?` 时，令 $s_1$ 为 `0`，其实对答案不影响，因为第一个字符已经是最小的 `0` 了，不需要用反转改变。

- 当 $s_{i-1}$ 为 `0` 时，令 $s_i$ 为 `0`，对答案不造成影响，因为如果要把 $s_{i-1}$ 反转到前面，可以带上 $s_i$ 一起反转。

- 当 $s_{i-1}$ 为 `1` 时，令 $s_i$ 为 `1`，对答案不造成影响，因为 $s_i$ 已经是最大的 `1`，不用反转到前面。

## code

```cpp
#include<bits/stdc++.h>

using namespace std;
int T;
string str;
signed main(){
	cin.tie(0),cout.tie(0);
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>str;
		if(str[0]=='?') str[0]='0';
		for(int i=1;i<str.size();i++)
			if(str[i]=='?')
				str[i]=str[i-1];
		cout<<str<<"\n";
	}
	return 0;
}
```

全文完。

---

## 作者：WA_sir (赞：1)

## [题目](https://codeforces.com/problemset/problem/1837/C)|[链接](https://www.luogu.com.cn/problem/CF1837C)

### 题目大意

给出一个不完整的 $01$ 字符串，可以在 $?$ 里填 $0$ 或 $1$。每一次操作，你可以把一个字串反转。求出一种方案，使得可以用最少的操作数让字符串升序排序。

### 题目分析

先举个例子：

`001110`

我们可以把**连续的相同字符**看作一个整体，就变成了这样：

`010`

由于题目中给出的操作是将子串反转，所以这个字符串的操作是：

- 将子串 `10` 反转。

也就是将原串的 `1110` 反转，得到 `000111`，操作数为 $1$。

再举个例子：

`1111111001111100`

这个字符串看起来很长，实际上可以看成：

`1010`

其中一种操作为：

- 将子串 `10`（第一个）反转，得到 `0110`；
- 将子串 `110` 反转，得到 `0011`。

由此不难看出，本题的字符串只有两种形式（连续的相同字符看作一个字符）：

1. `010101......`
1. `101010......`

而使操作数最小的关键，就是“**连续的相同字符**”这一整体最少。

如何达到这一要求呢？只需在填 $?$ 时使其与前一个字符相同。

特别的，若 $?$ 在字符串顶端，前一个字符默认为 $0$，毕竟是升序排序。

敲代码时，还要注意以下几点：
1. 有多组数据；
1. 输入速度。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>t;
	while(t--){
		cin>>s;
		char a='0';
		for(int i=0;i<s.size();i++)s[i]=='?'?s[i]=a:a=s[i];
		cout<<s<<endl;
	}
	return 0;
}
```
感谢你看到这里，Bye~Bye~ヾ(￣▽￣)！

---

## 作者：igAC (赞：1)

# $\text{Describe}$

[CFlink](https://codeforces.com/contest/1837/problem/C)

[洛谷 link](https://www.luogu.com.cn/problem/CF1837C)

题意：

给定由 ``1`` ``0`` ``?`` 所组成的字符串，你需要用 ``0`` 或 ``1`` 替换 ``?``。

我们将 $s_l,s_{l+1},\dots,s_r$ 反转成为一次操作。

你要使通过“反转”操作使原字符串成为升序的操作次数尽可能的小。

问最终构造出的字符串，有多解输出其一。

# $\text{Solution}$

简单题。

要使反转操作尽可能地少，就要让 ``0`` ``1`` 的块尽可能的少。

块的定义：如字符串 ``0110001111``，其中 ``0``、``000`` 是 ``0`` 块，``11``、``1111`` 是 ``1`` 块。

怎么做到呢？

这是简单的，我们将 ``?`` 填充为上一个字符就好了。

如果 ``?`` 在开头怎么办呢？

让它为 ``0`` 就好了，这样开头就不用动，对于剩下长度为 $n-1$ 的字符串进行操作就行了。

具体实现可参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int T,n;
string s;
void solve(){
	cin>>s;n=s.length();
	vector<int>zero;
	for(int i=0;i<n;++i) if(s[i]=='?') zero.push_back(i);
	if(zero.empty()){
		cout<<s<<"\n";
		return;
	}
	if(!zero[0]) s[zero[0]]='0';
	else s[zero[0]]=s[zero[0]-1];
	for(int i=1;i<zero.size();++i) s[zero[i]]=s[zero[i]-1];
	cout<<s<<"\n";
}
int main(){
	T=read();
	while(T--) solve();
	return 0;
}
```

作者实现过于丑陋，这里再贴一份官方题解代码。

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    char x = '0';
    for (auto& c : s) {
      if (c == '?') c = x;
      x = c;
    }
    cout << s << '\n';
  }
}
```

---

## 作者：Aveiro7 (赞：0)

## 题目：

给定由 ``1`` ``0`` ``?`` 所组成的字符串，你需要用 ``0`` 或 ``1`` 替换 ``?``。

我们将 $s_l,s_{l+1},\dots,s_r$ 反转称为一次操作。

你要使通过“反转”操作使原字符串成为升序的操作次数尽可能的小。

问最终构造出的字符串，有多解输出其一。

## 思路

经过观察，我们可以发现一个规律：

* 若 $s_i$ 为 ``?``，且 $i=1$ 时，$s_i=0$ 即可；

* 若 $s_i$ 为 ``?``，且 $i\ne 1$ 时，$s_i=s_{i-1}$ 即可。

有了这条规律，代码也就能很轻松地解决了。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i;
int main()
{
	cin>>n;
	while(n--)
	{
		string s;
		cin>>s;
		if(s[0]=='?')//如果第一个是？，那么它的值赋为0
			s[0]='0';
		for(i=1;i<s.size();i++)
		{
			if(s[i]=='?')//如果不是第一个为？，那么这个数就等于他前面一个数
				s[i]=s[i-1];
		}
		cout<<s<<endl;//输出
	 } 
	 return 0;
 } 
```


---

## 作者：Vct14 (赞：0)

为了方便，我们把形如 `11...1`，并且两侧均为 $0$ 的序列叫作全 $1$ 序列，把形如 `00...0`，并且两侧均为 $1$ 的序列叫作全 $0$ 序列，把用一个全 $1$ 序列和一个全 $0$ 序列拼起来的，形如 `11...100...0` 的序列叫作 $10$ 序列。

因为要求将字符串变为升序，所以要将所有 $1$ 放到序列的最后面。那么相较于一个一个的往后挪，一次性将连在一起的一个全 $1$ 序列往后翻一定是更优的。

因此对于每次操作，我们都选定一个最前面的最长 $10$ 序列进行操作，将前面的全 $1$ 序列移到全 $0$ 序列后面，与下一段全 $1$ 序列接上。

那么每次操作我们就可以减少一个全 $1$ 序列，并将它往后移，直到只剩一个全 $1$ 序列，并将其移到最后。

所以为了使操作次数尽量少，我们需使全 $1$ 序列的数量尽量少。相应的，全 $0$ 序列的数量也要尽量少。

再给出的序列的基础上，我们不再新增全 $1$ 序列和全 $0$ 序列的个数即可。

对于 $a_0$ 为 `?`，令其为 $0$；对于其它任意一个 `?`，我们让它与它的前一个数相等即可。这样可以不增加甚至减少全 $1$ 序列的数量。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;cin>>t;
	while(t--){
		string a;cin>>a;
		if(a[0]=='?') a[0]=='0';
		for(int i=1; i<a.size(); i++){
			if(a[i]=='?') a[i]=a[i-1];
			cout<<a[i];
		}
		cout<<endl;
	}
	return 0;
} 
```

---

## 作者：Light_az (赞：0)

# 题意

现在题目给定一个有些字母未知的字符串，可以将其中一个子串进行一次翻转操作，问如何构造一个字符串使得我们可以用最小次数翻转字符串让该字符串升序。

# 分析

由于需要最小次数翻转字符串，那么我们要让字符串中的 `0` 和 `1` 连续数量最多，具体表现为字符串 `00?111?111` 将构造成 `0011111111`。

因为只要 `0` 和 `1` 的次数越多，那么我们所需要的翻转次数就越小。那么构造字符串时我们只需要注意对于每次未知字符 `?`，将它变成前一个字符，保证连续次数最多即可。

如果某字符串以 `?` 开头，那么我们将它默认 `0` 即可，因为它并不会对字符串的升序产生影响。

# 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define B(i,j,n) for(ll i=j;i>=n;i--)
#define D double
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e7+10;
ll n,m,k,x,y,u,v,w,cnt,ans,t,l,r,len,T;
ll mn=INT_MAX,mx=0;
string s,s1,s2;

int main(){
	cin>>T;
	while(T--){
		cin>>s;
		len=s.size();
		char x='0';//默认为0
		F(i,0,len-1){
			if(s[i]=='?') cout<<x;//输出前一个
			else x=s[i],cout<<x;//已经有字符
		}
		cout<<"\n";
	}

	return 0;
}

```


---

## 作者：aeiouaoeiu (赞：0)

先考虑如何计算反转一个字符串所需要的最小次数。

我们省略后导的 `1`，则我们只需依次反转所有的非后导 `1` 块到最后面即可，所以最小次数即为所有的非后导 `1` 块的数量。

既然我们要构造次数最小的字符串，那么就要让所有的非后导 `1` 块的数量最少，所以对于所有的非后导 `?` 块，我们只需要检查其两边的前后两个字符是否都为 `1` 即可，因为这样才能减少块的数量。

最后注意两个细节：第一位前为 `0`，最后一位后为 `1`。
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long ll;
const int maxn=200005;
const ll inf=0x3f,p=100003;
ll n,l,r;
string s;
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll T=1;
	cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>s;
		n=s.length(),s="0"+s+"1",l=-1;
		for(int i=1;i<=n;i++){
			if(s[i]!='?'&&l!=-1){
				for(int j=l;j<=r;j++) s[j]=(s[l-1]=='1'&&s[r+1]=='1')?'1':'0';
				l=-1;
			}else if(s[i]=='?'){
				if(l==-1) l=r=i;
				else r++;
			}
		}
		if(l!=-1){
			for(int j=l;j<=r;j++) s[j]=(s[l-1]=='1'&&s[r+1]=='1')?'1':'0';
		}
		cout<<s.substr(1,n)<<"\n";
	}
	return 0;
}
```

---

## 作者：FinderHT (赞：0)

### 题意简述：
给你一个含有 `?` 的二进制字符串，你要把问号替换成 `0` 或 `1`，可以反转字符串的任意连续子串作为一次操作，要求以非降序的方式对字符串进行排序，输出操作数最小的满足要求的字符串。

### 思路分析：
推结论。我们把相邻的 $0$ 看做一段，相邻的 $1$ 看做一段，如果字符串的最后是 $1$ 的段，反转次数为 $1$ 的段数减一；如果没有，反转次数为 $1$ 的段数。我们可以设置从左往右的贪心策略，尽可能让 $1$ 的段连起来：如果第一个是问号，设置为 $0$，这样就可以确保第一个字符是最小的，如果这个字符是问号，就让它与上一个字符相同，否则就是原来的。这种情况可保证操作次数是最少的。

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
inline void solve(){
	string s;
	cin>>s;
	int l=s.size();
	s="0"+s;//小技巧，如果第一个字符是问号可以将其变成0
	for(int i=1;i<=l;i++)
		if(s[i]=='?')s[i]=s[i-1];//转换
	for(int i=1;i<=l;i++)putchar(s[i]);
	putchar('\n');
}
signed main(){
	int T;
	scanf("%d",&T);
	while(T--)
		solve();
	return 0;
}
```

## The End!

---

## 作者：张语诚ZYC (赞：0)

## 题目翻译

给定一个字符串 $s$，仅由 `1`，`0` 或者 `?` 构成，你需要用 `1`，`0` 填充 `?`。

你可以对填充完的字符串进行操作，对任何一部分进行翻转。要求让操作次数最少使得并且字符串单调不下降。

输出填充完数字的后的字符串，如果有多解，输出一个解即可。

## 题意分析

一看就是构造题！我们可以**大胆猜想，小心证明**地贪心。

先说结论：令每一个 `?` 等于它前面的字符，如果最前面一个是 `?` 让它为 `0` 即可。

下面开始证明：

- 如果最前面一个是 `?` 让它为 `0`，不会使字符串变大，因此不会增加翻转的次数。

- 如果不是第一位，令每一个 `?` 等于它前面的字符，其实就是在翻转操作时把后面以为顺便带上了，因此也不会增加翻转的次数。同理，令每一个 `?` 等于它后面的字符也行。



## $\texttt{AC Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read_int() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') {
			w=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=10*s+ch-'0';
		ch=getchar();
	}
	return s*w;
}
int main() {
	int T=read_int();
	for(int ti=1;ti<=T;ti+=1){
		string c;
		cin>>c;
		int l=c.length();
		if(c[0]=='?'){
			c[0]='0';
		}
		for(int ti=1;ti<l;ti+=1){
			if(c[ti]=='?'){
				c[ti]=c[ti-1];
			}
		}
		cout<<c<<endl;
	} 
	return 0;
}
```


---

