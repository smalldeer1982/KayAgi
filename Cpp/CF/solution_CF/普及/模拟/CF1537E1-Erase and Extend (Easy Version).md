# Erase and Extend (Easy Version)

## 题目描述

This is the easy version of the problem. The only difference is the constraints on $ n $ and $ k $ . You can make hacks only if all versions of the problem are solved.

You have a string $ s $ , and you can do two types of operations on it:

- Delete the last character of the string.
- Duplicate the string: $ s:=s+s $ , where $ + $ denotes concatenation.

You can use each operation any number of times (possibly none).

Your task is to find the lexicographically smallest string of length exactly $ k $ that can be obtained by doing these operations on string $ s $ .

A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a\ne b $ ;
- In the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

## 说明/提示

In the first test, it is optimal to make one duplication: "dbcadabc" $ \to $ "dbcadabcdbcadabc".

In the second test it is optimal to delete the last $ 3 $ characters, then duplicate the string $ 3 $ times, then delete the last $ 3 $ characters to make the string have length $ k $ .

"abcd" $ \to $ "abc" $ \to $ "ab" $ \to $ "a" $ \to $ "aa" $ \to $ "aaaa" $ \to $ "aaaaaaaa" $ \to $ "aaaaaaa" $ \to $ "aaaaaa" $ \to $ "aaaaa".

## 样例 #1

### 输入

```
8 16
dbcadabc```

### 输出

```
dbcadabcdbcadabc```

## 样例 #2

### 输入

```
4 5
abcd```

### 输出

```
aaaaa```

# 题解

## 作者：Tjaweiof (赞：2)

# CF1537E1
[题目传送门](https://www.luogu.com.cn/problem/CF1537E1)

思路：找到原串的最小的前缀，然后复制即可。因为数据范围较小，可以暴力找到最优的前缀，然后输出即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
string s, ans, s1;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ans = string(5000, 'z');
	cin >> n >> k >> s;
	for (int i = 1; i <= s.size(); i++){
		s1 = s.substr(0, i);
		while (s1.size() < k){
			s1 = s1 + s1;
		}
		ans = min(ans, s1.substr(0, k));
	}
	cout << ans;
	return 0;
}

```

---

## 作者：EDqwq (赞：2)

首先，从后往前删，得到的串一定是原串的前缀。

而复制粘贴，导致了操作后的串只可能会由几个前缀拼凑（删除只能删除最后的，复制之后，原来在后面的还是在后面）。

所以我们找到最小的前缀，把他拼凑多次，取前 $m$ 个就是答案了。

因为如果是不同前缀拼凑，一定有其中某个前缀最小，全部换成这个前缀显然最优。

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int n,m; 
string s;
string ans = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";

signed main(){
	cin>>n>>m;
	cin>>s;
	for(int i = 0;i <= n - 1;i ++){
		string ss = s.substr(0,i + 1);
		string s1 = ss;
		while(s1.length() < m)s1 = s1 + s1;
		ans = min(ans,s1.substr(0,m));
	}
	cout<<ans;
}
```

---

## 作者：Berd__ (赞：1)

## 题意
一个字符串，可以把该字符串的一个前缀复制粘贴，可以删除末尾元素，最终要使串长度为 $k$ 且字典序最小并输出。

## 思路
$n,k\le5000$，暴力枚举即可。

首先，从后面删，得到的串一定是原串的前缀。

与其交替着操作，不如直接先删到最优的前缀再进行复制。

比如 `bilibili` 这个字符串，设 $k$ 为 $15$，那么操作如下：

- 删最后，变成：`bilibil`
- 删最后，变成：`bilibi`
- 删最后，变成：`bilib`
- 删最后，变成：`bili`
- 删最后，变成：`bil`
- 删最后，变成：`bi`
- 删最后，变成：`b`
- 比较，发现 `b` 的字典序最小。
- 复制 `b`，发现长度大于 $k$ 时删除到长度为 $k$。
- 得到字符串 `bbbbbbbbbbbbbbb`。

## 代码
马蜂惨不忍睹
```cpp
#include<algorithm>
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
int main()
{
    int n,kkksc03;
    string s;
    cin>>n>>kkksc03;
    cin>>s;
    string Min = "~~~~~~~~~~~~~~~~", nw = "";
    for(int i=1;i<=s.size();i++){
        nw=s.substr(0,i);
        while(nw.size()<kkksc03) {
		    nw=nw+nw;
		}
        Min=min(Min,nw.substr(0,kkksc03));
    }
    cout<<Min<<endl;
    return 0;
}
```

---

## 作者：JustinXiaoJunyang (赞：1)

思路分析：

注意：这道题是简化版。
存第一个字符一直枚举到都存下来，再取字典序最小，可以用 STL 的 `substr` 函数解决。

我们不停去克隆字串，直到达到了 $k$ 的长度。

因为这里要打擂台，擂主得是个非常大的东西，这样谁都比它小。

最后得到的擂主就是答案。

参考代码：

代码似乎不难写，这个是 [AC 记录](https://www.luogu.com.cn/record/83919647)。

---

## 作者：hyc1026 (赞：1)

一道比较好的字符串入门和思维题。

### 思路：

本题既然要求字符串字典序最小，那么我们可以暴力枚举一下。从字符串只保留第 $1$ 个字符开始，一直枚举到全部保留（也就是不删掉任何字符）。

枚举完 $n$ 种情况后取最小即可，不可能有别的情况。

每次我们可以用 `s.substr(l,r)` 这个函数取字符串的从第 $l+1$ 位开始，到第 $r$ 位结束的一个子串。

### 做法：

首先拿一个字符串 $minn$，将其赋成无穷大。在本题中，只要比 $\tt{z}$ 大即可（字典序）。
 
枚举保留 $i$ 个字符时，先用 `s.substr(0,i)` 取得子串（注意字符串下标从 $0$ 开始，并且如上文，该函数左闭右开，注意取值）。

然后用一个 `while` 循环，不停的让这个字符串复制，直到长度大于等于 $k$ 为止。（也就是题目中的将 $s$ 变为 $s+s$ 这一步）

最后再用 `s.substr()` 函数取得上面的字符串的前 $k$ 位，拿 $minn$ 与之比较，如果该字符串较小则将 $minn$ 更新为该字符串。

这样将 $1$ 到 $n$ 全部枚举一边，得到的 $minn$ 一定是当中最小的，也就是本题答案。

### AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    string minn = "{}", now = "";
    for(int i=1; i<=n; i++)
    {
        now = s.substr(0,i);
        while(now.size() < k) now = now + now;
        minn = min(minn, now.substr(0,k));
    }
    cout << minn << endl;
}
//
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1537E1)
## 解题思路
暴力枚举。

先让 $i$ 从 $1$ 到 $n$，枚举删去字符串的最后一个字符后字符串的长度。然后，重复第二个操作，直到它的长度大于（或等于）$m$。为了保险，我循环了 $\dfrac{m}{i}+1$ 次。

在然后，取当前字符串的前 $m$ 位，取最小值即可。
## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	string a,minn(5000,'z');
	cin>>n>>m>>a;
	for(int i=1;i<=n;i++)
	{
		string now="",b=a.substr(0,i);
		for(int j=1;j<=m/i+1;j++)
			now+=b;
		minn=min(minn,now.substr(0,m));
	}
	cout<<minn;
	return 0;
}

```

---

## 作者：King_duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1537E1)

$n,k≤5000$，暴力枚举就可以了。首先，从后面删，得到的串一定是原串的前缀，所以交替着操作，不如直接先删到最优的前缀再进行复制。

直接上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
string s;
int main()
{
    cin>>n>>k;
    cin>>s;
    string minn="~~~~~~~~~~~~~~~~~~~~~~~",w="";
    for(int i=1;i<=s.size();i++)
	{
        w=s.substr(0,i);
        while(w.size()<k) 
		{
		    w=w+w;
		}
        minn=min(minn,w.substr(0,k));
    }
    cout<<minn<<endl;
    return 0;
}
```

---

## 作者：PigJokerYellow (赞：0)

# CF1537E1Erase and Extend (Easy Version)

### 前言

- `str.substr(begin,length)`

- 表示切割字符串 $ str $，从下标 $ begin $ 处开始，长度为 $ length $ 来切片。


### 题意

对于一个字符串，进行翻倍或减掉最后一位的操作，使其修改后长度为 $ k $ 且字典序最小，找出这个字符串并输出。

### 思路

枚举这个字符串所有的前缀字符串，看哪一个前缀字符串翻倍到有 $ k $ 位时（多余的位数舍去）字典序最小，则此字符串即为答案。

### 算法

额，暴力枚举。

### 注意事项

`substr` 注意截取的位数。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

long long n,k;
//原位数和修改后的位数 
string str,ans="zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
//原字符串和答案
//答案设成多个z，因为z的ASCII最大 

string check(string a,string b){
	while(a.size()<k) a+=a;
	while(b.size()<k) b+=b;
	//不断复制的过程 
	return min(a.substr(0,k),b.substr(0,k));
	//只截取前k位 
}

int main(){
	cin>>n>>k;
	cin>>str;
	for(long long i=1;i<=n;i++){
		ans=check(str.substr(0,i),ans);
		//截取每个前缀 
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：WOL_GO (赞：0)

由于是 `Easy Version`，直接暴枚方可。

我们可以从后往前删，删到一个最小值时停止，然后疯狂复制，直到字符串的长度 $\ge k$。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int n,k;
string s,minn,s1;
int main(){
	cin>>n>>k>>s;
	for(int i=1;i<=1000000;i++)minn+=max('z','Z');
	for(int i=1;i<=s.size();i++){
		s1=s.substr(0,i);
		while(s1.size()<k)s1=s1+s1;
		minn=min(minn,s1.substr(0,k));
	}
	cout<<minn;
}

```

## 附带个升级版代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace read_write{
	typedef long long ll;
	template<typename T> 
	void read(T &x){
		x = 0;char ch = getchar();ll f = 1;
		while(!isdigit(ch)){if(ch == '-')f*=-1;ch=getchar();}
		while(isdigit(ch)){x = x*10+ch-48;ch=getchar();}x*=f;
	}
	template<typename T, typename... Args> void read(T &first, Args& ... args){
		read(first);
		read(args...);
	}
	template<typename T>
	void write(T x){
		if(x<0){
			putchar('-');
			x*=-1;
		}
		if(x>9){
			write(x/10);
		}
		putchar(x%10+'0');
	}
	template<typename T, typename... Args> void write(T &first, Args& ... args){
		write(first);
		write(args...);
	}
	template<typename T>
	void readm(T *a,T l,T r){
		for(int i=l;i<=r;++i)read(a[i]);
	}
	template<typename T>
	void writem(T *a,T l,T r,char c=0){
		for(int i=l;i<=r;++i)write(a[i]),c?putchar(c):c=0;
	}
}
using namespace read_write;
int n,k,p=1;
string s;
int main() {
	read(n,k);
	cin>>s;
	s=" "+s;
	for(int i=1;i<=n&&s[i]<=s[(i-1)%p+1];i++)if(s[i]<s[(i-1)%p+1])p=i;
	for(int i=1;i<=k;i++)putchar(s[(i-1)%p+1]);
	return 0;
}
```


---

## 作者：NightmareAlita (赞：0)

## 简要题意

给你一个字符串，找到该字符串的一个前缀并不断复制，可以删除末尾元素，最终要使得得到的字符串长度为 $k$ 且字典序最小。

## 策略分析

对于此类构造题，我们一般需要运用逆向思维，也就是说我们要从前往后扫而不是从后往前删。为什么这样想呢？我们可以发现，字典序最小当且仅当我们要找的前缀的第 $i$ 位比第 $i \bmod len$ 位的字典序小 ，这样拼接起来才能够使得字典序最小，这个结论是显然的，证明可以使用反证法。

## 参考代码

```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

namespace SHAWN {
    int n, k, l = 1;
    string s;
    int work()
    {
        cin >> n >> k >> s;
        for (int i = 0; i < n; ++i) {
            if (s[i] < s[i % l]) { l = i + 1; }
            else if (s[i] > s[i % l]) { break; }
        }
        for (int i = 0; i < k; ++i) {
            cout << s[i % l];
        }
        return 0;
    }
}

signed int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    return SHAWN :: work();
}
```



---

## 作者：xxxr_2024 (赞：0)

# CF1537E1 Erase and Extend 题解
## 分析
通过观察题目，可以证明结果一定是由多次前缀复制得来的。

题目要求你进行删和复制的操作，与其交替着操作，不如直接先删到最优的前缀再进行复制。

现在就是要找最优的前缀。从头一位一位往后遍历。用 $l$ 来存储目前最优前缀的长度，第 $i$ 位对应复制后的 $k$ 位最优前缀就是第 $i\bmod l$ 位。在往后遍历时，如果下一位的 ASCII 码比最优前缀第 $i\bmod l$ 位的大，就说明后面没有最优解了，直接 `break`。如果小于的话，说明当前的解更优，更新一下长度即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Raiden
{
    int work()
    {
        string s;
        int n,k;
        int l=1;
        cin>>n>>k>>s;
        for(int i=0;i<n;i++)
        {
            if(s[i]>s[i%l])
                break;
            else if(s[i]<s[i%l])
                l=i+1;
        }
        for(int i=0;i<k;i++)
            cout<<s[i%l];
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return Raiden::work();
}
```

---

## 作者：zhang_kevin (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1537E1)

# Content

你有一个字符串 $s$，你可以进行两种操作。
- 删去字符串的最后一个字符。
- 将 $s$ 变为 $s+s$，$+$ 表示字符串连接，也就是复制一次字符串。

你可以随意的进行操作，也可以不进行操作。

你需要找到 $s$ 进行操作后获得的所有长度为 $k$ 的字符串中**字典序最小**的字符串。

# Solution

这道题可以先找到最优字符串的前缀，然后复制它，直到字符串的长度大于 $k$，最后删除多余的元素。

我们先放宽要求，以便可以在字符串中找到一个位置，使得每次你要么返回开头，要么遍历下一个字符。答案为字典序最小的无限字符串的前 $k$ 个字符。

从给定的位置开始，它的最优字符串是唯一的，因此你可以准确地选择一个最优决策。

我们证明了选择一个前缀，复制它直到长度大于 $k$，然后删除多余的元素是最优的。由于限制很低，我们可以遍历原始字符串上的每个前缀并用它制作一个长度为 $k$ 的字符串。然后我们取所有这些字符串中的最小值作为答案（$\verb!C++!$ 中的 $\verb!min!$ 函数对字符串比较时默认使用字典排序，不用自己写比较函数）。

时间复杂度为 $O(n \cdot k)$。

# Code

```cpp
#include<bits/stdc++.h> 
using namespace std;
string get(string s, int k){
    while(s.length() < k){
        s = s + s;
    }
    while(s.length() > k){
        s.pop_back();
    }
    return s;
}
int main(){
    int n, k;
    string s;
    cin >> n >> k >> s;
    string str = "";
    str += s[0];
    string Min = get(str, k);
    for(int i = 1; i < n; i++){
        if(s[i] > s[0]){
        	break;
		}
        str += s[i];
        Min = min(Min, get(str, k));
    }
    cout << Min << endl;
    return 0;
}
```


---

## 作者：pomelo_nene (赞：0)

因为这个数据范围着实小，对于每个前缀暴力生成长度为 $k$ 的字符串比较出最小的输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1005];
int n,k;
bool getMin(int x,int y)
{
	for(int i=1;i<=3*n;++i)
	{
		int lx=i%x,ly=i%y;
		if(lx==0)	lx=x;
		if(ly==0)	ly=y;
		if(s[lx]<s[ly])	return true;
		if(s[lx]>s[ly])	return false;
	}
	return false;
}
int main(){
	scanf("%d %d",&n,&k);
	scanf("%s",s+1);
	int ls=1;
	for(int i=2;i<=n;++i)	if(getMin(i,ls))	ls=i;
	for(int i=1;i<=k;++i)
	{
		int x=i%ls;
		if(x==0)	x=ls;
		putchar(s[x]);
	}
	return 0;
}
```

---

