# Serval and Inversion Magic

## 题目描述

Serval has a string $ s $ that only consists of 0 and 1 of length $ n $ . The $ i $ -th character of $ s $ is denoted as $ s_i $ , where $ 1\leq i\leq n $ .

Serval can perform the following operation called Inversion Magic on the string $ s $ :

- Choose an segment $ [l, r] $ ( $ 1\leq l\leq r\leq n $ ). For $ l\leq i\leq r $ , change $ s_i $ into 1 if $ s_i $ is 0, and change $ s_i $ into 0 if $ s_i $ is 1.

For example, let $ s $ be 010100 and the segment $ [2,5] $ is chosen. The string $ s $ will be 001010 after performing the Inversion Magic.

Serval wants to make $ s $ a palindrome after performing Inversion Magic exactly once. Help him to determine whether it is possible.

A string is a palindrome iff it reads the same backwards as forwards. For example, 010010 is a palindrome but 10111 is not.

## 说明/提示

In the first test case, Serval can perform Inversion Magic on the segment $ [1,4] $ . The string $ s $ will be 0110 after the magic.

In the second test case, Serval can perform Inversion Magic on the segment $ [1,3] $ . The string $ s $ will be 01110 after the magic.

In the third test case, Serval can't make $ s $ a palindrome by performing Inversion Magic exactly once.

## 样例 #1

### 输入

```
3
4
1001
5
10010
7
0111011```

### 输出

```
Yes
Yes
No```

# 题解

## 作者：liaiyang (赞：1)

这道题的题意是将一个字符串变成一个回文串，这个串只有 0 和  1 两个字符，并且可以挑选一段区间，使得这个区间里的所有数倒过来，0 变成 1，1 变成 0。

我们用两个指针从两端向中间扫，如果两端不同，说明其中一边肯定要改，因为只能改一次，所以我们就一直改左边的就好了。

如果发现有两个要改的地方，并且这两个地方中间有不需要改的，说明区间断开了，至少要改两次，就说明不能变成回文串。

如果区间没有断开，说明它可以。

时间复杂度 $O(n)$。
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define _cin(i,n) for(int i=0;i<n;i++)
#define _for(i,a,b) for(int i=a;i<=b;i++)
#define for_(i,a,b) for(int i=a;i>=b;i--)
#define cin_(a,n) for(int i=0;i<n;i++){int x;cin>>x;a.push_back(x);}
const int inf=~0U>>1;
const int linf=~0ULL>>1;
const int mod=1e9+7;
const int gmod=998244353,g=3,invg=332748118;
const int N=2e5+10;
int _,n,flag1,flag;
string a; 
void work(){
	cin>>n>>a;flag=flag1=0;
	for(int i=0;i<(n>>1);i++){
		if(a[i]!=a[n-i-1]){
			if(flag&&flag1){
				cout<<"No"<<endl;
				return ;
			}
			flag=1;
		}
		else if(flag) flag1=1;
	}
	cout<<"Yes"<<endl;
}
main(){
	cin>>_;
	while(_--) work();
	return 0;
} 
```


---

## 作者：Strelitzia_ (赞：1)

## 题目大意

给你一个长度为 $n$ 的 01 串 $s$，你可以选择**一个**区间，将区间内的所有 0 变成 1，所有 1 变成 0。问能不能通过仅这一次的操作将 $s$ 变为一个回文串。

------------
## 思路

首先 $s$ 的长度确定了，那么我们就可以知道他的回文中心。我们只考虑回文中心的右侧：

- 如果一个位置上的字符与左侧相应位置上的字符匹配，那么这个位置取反之后一定不匹配；

- 如果想要左侧与右侧完全匹配，那么右侧的所有不匹配字符必须都被取反。

综上，我们需要找到 $s$ 对称中心右侧的一个连续区间，使得这个区间包括了所有不匹配的位置，不包括任何已经匹配的位置。也就是说，我们需要判断所有不匹配的位置是不是连续的。

提供一种实现思路：从最右侧开始，找到一个**极长连续的**不匹配的串，将其取反，然后检查整个字符串是否回文即可。时间复杂度 $O(n)$。

代码如下：

```cpp
bool pd() {
	for (int i = 1; i <= mid; i++) if (ch[i] != ch[n - i + 1]) return 0;
	return 1;
}//判断回文

bool sol() {
	n = read(), mid = n >> 1, nowres = n;
	scanf("%s", ch + 1);
	while (ch[nowres] == ch[n - nowres + 1] && nowres > mid) nowres--;
	if (nowres == mid) return 1;
	mxid = nowres;
	while (ch[nowres] != ch[n - nowres + 1] && nowres > mid) nowres--;
	for (int i = nowres + 1; i <= mxid; i++) ch[i] = (ch[i] == '0' ? '1' : '0');
	return pd();
}

signed main() {
	t = read();
	while (t--) puts(sol() ? "YES" : "NO");
	return Strelitzia_;
}
```

---

## 作者：arrow_king (赞：0)

## 简要题意

给定一个长度为 $n$ 的 01 字符串 $s$，第 $i$ 个字符为 $s_i$。

你可以使用一次且仅可以使用一次操作，使得区间 $[l,r]$ 的字符取反，即将 $\texttt{0}$ 变为 $\texttt{1}$，$\texttt{1}$ 变为 $\texttt{0}$。如果在使用操作后可以使得字符串变为回文输出 `Yes`，否则输出 `No`。

## 思路

首先如果 $n$ 为奇数，正中间的字符是可以修改也可以不修改的。

对于一对对应的字符（即，编号之和为 $n+1$），若不同显然是只需要修改一个的，不可能两个都修改。

所以可以得到这样一个思路：判断前 $\left\lfloor\dfrac{n}{2}\right\rfloor$ 个字符，如果这个字符和与它配对的字符相同则扔掉不管，不同则将这个字符标记一下。最后判断需要修改的标记是否为连续的区间就可以了。

时间复杂度 $\mathcal O(n)$。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define N 100005
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t,n,tag[N];
char s[N];
int main() {
	t=read();
	while(t--) {
		n=read();
		scanf("%s",s+1);
		for(int i=1;i<=n;i++) tag[i]=0;
		for(int i=1;i<=n/2;i++) if(s[i]!=s[n-i+1]) tag[i]=1;
		int cnt=0;
		for(int i=2;i<=n;i++) if(tag[i]!=tag[i-1]) cnt++;
		if(cnt<=2) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

[赛时 AC 记录](https://codeforces.com/contest/1789/submission/195027432)

---

## 作者：BlackPanda (赞：0)

*[Problem](https://www.luogu.com.cn/problem/CF1789B)*

------------
## Description

有 $t$ 次询问，每次给出 $n$ 和一个长度为 $n$ 的 $\verb!01!$ 串，询问是否可以通过一次操作使得原串变成回文串。

定义操作如下：

取 $[l, r]$ 区间（$1 \le l, r \le n$），使得区间内每个元素取反。（$0$ 变成 $1$，$1$ 变成 $0$）

------------
## Solution

数据范围 $t \le 10^4, n \le 10^5$，考虑双指针。从两端往里遍历，找不同元素的个数，定义当前遍历到的两个元素分别为：$s_i$ 和 $s_j$，下标从 $1$ 开始。

- 如果 $s_i \neq s_j$，判断之前是否出现过需要翻转的情况。例如：$\verb!101110110!$，首先将区间 $[1,2]$ 翻转，变成 $\verb!011110110!$，但是 $s_4$ 和 $s_6$ 不相同，也就是需要第二次翻转，返回 $\verb!No!$。

- 如果 $s_i = s_j$，继续遍历即可。

------------
## Code

**赛时 AC 代码**

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string s;

void solve()
{
    cin >> n >> s;
    int len = s.length();
    bool f = 1;
    int sum = 0;
    for (int i = 0, j = len - 1; i < j; i ++, j -- )
    {
        if (s[i] != s[j]){if (sum % 2 == 0) sum ++ ;}
        else {if (sum % 2 == 1)  sum ++ ;}
        if (sum > 2)   
        {
            puts("No");
            return ;
        }
    }
    puts("Yes");
    return ;
}

int main()
{
    int T; cin >> T;
    while (T -- )   solve();
    return 0;
}
```

---

## 作者：Fleeing_loser (赞：0)

## 题目大意

给定 $\text{t}$ 个长度为 $\text{n}$ 的 $01$ 串，求对一个连续区间 $\left[
l,r \right]$ 中的串反转一次后的，该 $01$ 串是否回文。

## 解题思路

不难发现，回文串满足的一个条件是在区间 $\left[1,\left \lfloor \frac{n}{2} \right \rfloor \right]$ 中第 $i$ 位置的字符与第 $n-i+1$ 位置的字符相等即可。

要想一次反转做到每一个 $i$ 位置的字符与 $n-i+1$ 位置的字符相等，那原来的串中 $i$ 位置的字符与 $n-i+1$ 位置的字符不相等时 $i$ 必须是连续的,是连续的则符合条件，不是连续的就不符合条件。

## code

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5; 
int n,t,sum,ss,flag;
char s[N];
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		cin>>s+1;
		ss=sum=0; flag=1;
		for(int i=1;i<=(n/2);++i)
		{
			if(s[i]!=s[n-i+1]) ++sum,ss+=flag;//ss记录不相等时的i是否是连续的
			else if(ss) flag=0;//如果相等，那不相等的i就断开了
		}
		if(ss!=sum) printf("No\n");
		else printf("Yes\n");//都是连续的就符合条件
	}
	return 0;
}
```

---

