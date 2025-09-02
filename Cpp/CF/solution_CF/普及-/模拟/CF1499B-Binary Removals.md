# Binary Removals

## 题目描述

You are given a string $ s $ , consisting only of characters '0' or '1'. Let $ |s| $ be the length of $ s $ .

You are asked to choose some integer $ k $ ( $ k > 0 $ ) and find a sequence $ a $ of length $ k $ such that:

- $ 1 \le a_1 < a_2 < \dots < a_k \le |s| $ ;
- $ a_{i-1} + 1 < a_i $ for all $ i $ from $ 2 $ to $ k $ .

The characters at positions $ a_1, a_2, \dots, a_k $ are removed, the remaining characters are concatenated without changing the order. So, in other words, the positions in the sequence $ a $ should not be adjacent.

Let the resulting string be $ s' $ . $ s' $ is called sorted if for all $ i $ from $ 2 $ to $ |s'| $ $ s'_{i-1} \le s'_i $ .

Does there exist such a sequence $ a $ that the resulting string $ s' $ is sorted?

## 说明/提示

In the first testcase you can choose a sequence $ a=[1,3,6,9] $ . Removing the underlined letters from "10101011011" will produce a string "0011111", which is sorted.

In the second and the third testcases the sequences are already sorted.

In the fourth testcase you can choose a sequence $ a=[3] $ . $ s'= $ "11", which is sorted.

In the fifth testcase there is no way to choose a sequence $ a $ such that $ s' $ is sorted.

## 样例 #1

### 输入

```
5
10101011011
0000
11111
110
1100```

### 输出

```
YES
YES
YES
YES
NO```

# 题解

## 作者：Silence_water (赞：4)

这是一篇另类的题解。

设计状态 $dp[i][0/1][0/1]$，表示当前到第 $i$ 个字母，最后一位是 $0/1$，第 $i$​ 个字母有没有被移除，是否存在一种移除方案满足题意。我们进行分类讨论：

1. 当前位字母为 $0$ 时，我们可以选择移除和不移除。

   - 若不移除，则转移来的字符串最后一位和当前最后一位肯定为 $0$。

   - 若移除，则 $i-1$ 位不能移除，最后一位可能为 $0$ 或 $1$。因此 $dp[i][0][1]$ 从 $dp[i-1][0][0]$ 处转移，$dp[i][1][1]$ 从 $dp[i-1][1][0]$ 和 $dp[i-1][0][0]$ 转移。

2. 当前位字母为 $1$ 时，我们同样也有两种选择。

   - 若不移除，则当前最后一位肯定为 $1$。此时 $i-1$ 位的 $4$ 种状态都可以转移过来。

   - 若移除，则 $i-1$ 位不能移除，最后一位可能为 $0$ 或 $1$。因此 $dp[i][0][1]$ 从 $dp[i-1][0][0]$ 处转移，$dp[i][1][1]$ 从 $dp[i-1][0][0]$ 和 $dp[i-1][1][0]$ 转移。

最初时没有删除任何字母，因此边界条件为 $dp[0][0][0]=1$。

最后时一定处于第 $n$​ 位，只要四种状态中有一种方案是符合题意的即为 `YES`，否则为 `NO`。

```cpp
void solve()
{
	scanf("%s",s+1);n=strlen(s+1);
	memset(dp,false,sizeof(dp));
	dp[0][0][0]=true;
	for(int i=1;i<=n;i++)
	{
		int c=s[i]-'0';
		if(c==0)
		{
			dp[i][0][0]|=(dp[i-1][0][0]||dp[i-1][0][1]);
			dp[i][0][1]|=(dp[i-1][0][0]);
			dp[i][1][1]|=(dp[i-1][1][0]||dp[i-1][0][0]);
		}
		else
		{
			dp[i][1][1]|=(dp[i-1][0][0]||dp[i-1][1][0]);
			dp[i][1][0]|=(dp[i-1][0][0]||dp[i-1][0][1]||dp[i-1][1][0]||dp[i-1][1][1]);
			dp[i][0][1]|=(dp[i-1][0][0]);
		}
	}
	bool ac=(dp[n][0][0]||dp[n][0][1]||dp[n][1][0]||dp[n][1][1]);
	if(ac)puts("YES");
	else puts("NO");
}
```



---

## 作者：__zyq_666_kpzc__ (赞：3)

### [题目传送门](https://www.luogu.com.cn/problem/CF1499B)
### 思路分析
题目已经给出：不能连续删字符串中的字符，就说明，如果字符串中出现了 $11$ 或者 $00$，那么无论你怎么删，最终都会剩下一个 $1$ 或者一个 $0$。

所以，我们这需要判断字符串中有没有一段 $11$ 在另一段 $00$ 前面即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
  	int T,ma_x=-1e9,ma_y=-1e9;
	cin>>T;
	while(T--){
		string s;
		cin>>s;
		bool f=false;
		bool ff=false;
		for(int i=1;i<s.size();i++){
			if(s[i]==s[i-1]){
				if(s[i]=='1')f=true;
				else if(f==true)ff=true;
			}
		}
		if(f==ff&&f==true)cout<<"NO\n";
		else cout<<"YES\n";
	} 
	return 0;
} 
```

---

## 作者：slzx2021zjx (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1499B)
## 思路

这道题很简单，不用什么高级的算法也能做出来。言归正传——

由于 $ a_{i-1} + 1 < a_i $。即表明选的数一定要间隔，不能连续。

又由于剩下的序列中 $ s'_{i-1} \le s'_i $。

所以考虑当 $1100$ 时，无论怎么去非间隔的的几个数，剩下总会存在 $10$  串，所以不行。

综上所述，这道题只要考虑 $11$（至少两个一）后面有没有 $ 00 $（至少两个零）即可。

代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,T;
char a[105];
bool k,kk;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>a+1;
		for(int i=1;i<=101;i++){
			if(a[i]=='1'&&a[i+1]=='1') k=1;
			if(k==1&&a[i]=='0'&&a[i+1]=='0') kk=1;
		}
		if(kk==1) cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
		k=0,kk=0;
	}
	return 0;
}


---

## 作者：我梦见一片焦土 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF1499B)

------------
# 思路：
想要出现否的情况那一定会有 $0$ 在 $1$ 的后面，而我们的删除操作只能隔着删，所以当出现两个 $00$ 或两个 $11$ 必然会留下一个，所以从后往前遍历，如果发现出现 $00$ 之后又出现 $11$ 则最终无论怎么删都会留下一个 $…1…0…$ 的情况。

------------
代码：
```cpp
#include <queue>
#include <math.h>
#include <stack>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=1e5+10;
const int M=1e3+10;
const int MOD=1000007;
const int INF=(int)0x3f3f3f3f3f3f3f3f;
int n,T,a[N];
string s;
int main(){
	cin>>T;
	while(T--){
		cin>>s;
		int pos1=0,pos0=0,l=s.size();
		for(int i=1;i<l;i++){
			if(s[i]=='1'&&s[i-1]=='1'&&pos1==0){
				pos1=i;
			}
			if(s[i]=='0'&&s[i-1]=='0'){
				pos0=i;
			}
		}
		if(pos1&&pos0&&pos1<pos0){
			cout<<"NO"<<endl;
		}else{
			cout<<"YES"<<endl;
		}
	}
}
```

---

## 作者：Zzzzzzzm (赞：1)

## 题目难度：
**橙色**的构造题

## 题目分析
通过样例我们可以发现每次$01$相间那么只要每次删$0$或者$1$就可以保持单调，无数个$0$后接无数个$1$也可以。

那么什么时候不可以呢？

**在若干个$1$之后跟了若干个$0$**，若干$\geq$2。

即只要有$11$后有$00$，那么就会无法实现，因为无论如何你也无法将两个$1$全部删去或把两个$0$全部删去。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
 
int t;
string a;
int lenth;
 
template<typename T>									//快读快写 
inline void read(T&x){
	x=0; char q; bool f=1;
	while(!isdigit(q = getchar()))	if(q == '-')	f = 0;
	while(isdigit(q)){
		x = (x<<1)+(x<<3)+(q^48);
		q = getchar();
	}
	x = f?x:-x;
}
 
template<typename T>
inline void write(T x){
	if(x<0){
		putchar('-');
		x = -x;
	}
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
 
int main(){
	read(t);
	while(t--){											//t组数据 
		cin >> a;
		int lenth = a.size(); 
		a = ' ' + a;									//方便从i=1开始循环 
		int num = 0;
		for(register int i = 1; i < lenth; ++i)			//找"11" 
			if(a[i] == '1' && a[i+1] == '1'){
				num = i+2;
				break;
			}
		if(num == 0){
			printf("YES\n");
			continue;
		}
		bool flag = 1;
		for(register int i = num; i < lenth; ++i)		//"11"之后找"00" 
			if(a[i] == '0' && a[i+1] == '0'){
				printf("NO\n");
				flag = 0;
				break;
			}
		if(flag)	printf("YES\n");
	}
	return 0;
}
```


---

## 作者：Tulip_ (赞：0)

### 题意

给定一个仅由 $0$ 和 $1$ 组成的字符串 $s$，$|s|$ 是它的长度

你需要选择一个整数 $k\ (k>0)$，然后找到一个长度为 $k$ 序列 $a$ 满足：

- $1≤a_1＜a_2＜ ⋯ ＜a_k≤|s|$ ;
- $a_{i-1}+1＜a_i\ (2≤i≤k)$ ;

将字符串 $s$ 中 $a_1,a_2,...,a_k$ 位置的字符移除，其它字符位置不变进行重新拼合组成字符串 $s'$

是否存在一个序列 $a$ 使得字符串 $s'$ 满足 $s'_{i-1}≤s'_i\ (2≤i≤|s'|)$ ?

一共有 $t$ 次询问，每次询问给定字符串 $s\ (2≤|s|≤100)$

对于每次询问，如果可以找到一个序列 $a$ 满足条件输出 `YES`，否则输出 `NO`。

### 思路

我们为了使得**序列单调不降**，我们要保证**删除过后的序列要满足前段是 $0$，后段是 $1$**，但是**只能删除不连续的数字**，所以只要有连续的 $1$ 出现在连续的 $0$ 之前，序列就不能变成**单调不减的序列**了。

那我们就可以分别**从左和右**来判断。

也就是说：

判断 $0$ 时，从序列的 $0$ 开始，一只判断到 `s.zise()-1`；而判断 $1$ 时，从序列的 `s.zise()-1` 开始，一只判断到 $1$。

若**连续的 $1$ 比连续的 $0$ 出现的早**，则输出 `NO`，否则输出 `YES`。

那这道题就解决了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,o,o2;
string s; 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
    	o=-1,o2=1e9;
    	cin>>s;
    	for(int i=0;i<s.size()-1;i++)
    		if(s[i]=='0'&&s[i+1]=='0')o=i;
		for(int i=s.size()-1;i>0;i--)
    		if(s[i]=='1'&&s[i-1]=='1')o2=i;
		if(o>o2)cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
	}
	
	return 0;
}

```

[AC](https://www.luogu.com.cn/record/162676553)

---

## 作者：oceanfish (赞：0)

## 题目
[原题传送门](https://www.luogu.com.cn/problem/CF1499B)

本文中，连续指**两个**元素的相邻关系。

给出一个 $01$ 序列，问能不能通过删除此序列中不连续的几个数字，使得删除后的序列单调不降。

## 方法
我们考虑到，为了使得这个序列单调不降，我们要保证删除过后的序列要满足前段是 $0$，后段是 $1$，但是因为只能删除不连续的数字，所以一旦有连续的 $1$ 出现在连续的 $0$ 之前，这个序列就不能变成单调不减的序列了。

对于程序，我们可以先从右往左，找出第一个连续的 $1$ 出现的位置，再从左往右，找出最后一个连续的 $0$ 出现的位置，若连续的 $1$ 比连续的 $0$ 出现的早，则输出 `NO`，否则输出 `YES`。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
int T;
string s;

void check(string s) {
	int f = inf, l = -1;
	for (int i = s.size() - 1; i > 0; i--)
		if (s[i] == '1' && s[i - 1] == '1')
			f = i;
	for (int i = 0; i < s.size() - 1; i++)
		if (s[i] == '0' && s[i + 1] == '0')
			l = i;
	if (f < l)
		cout << "NO\n";
	else
		cout << "YES\n";
}

int main() {
	cin >> T;
	while (T--) {
		cin >> s;
		check(s);
	}
	return 0;
}
```


---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/CF1499B)

## 思路

输出 ``YES`` 的情况就只有两种：

- 只要没有连续 $0$ 或 $1$ 的都可以完全改变。

- 如果先连续 $0$ 后有连续的 $1$ 也可以。

所以，只需要看连续的 $1$ 后面是否有连续的 $0$ 即可。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int main() 
{
	int n;
	cin>>n;
	while(n--)
	{
		string s;
		cin>>s;
		bool f1=false,f2=false;
		for(int i=0;i<s.size();i++)
		{
			if(s[i]=='1'&&s[i-1]=='1')f1=true;
			if(f1==true&&s[i]=='0'&&s[i-1]=='0')
			{
				f2=true;
				break;
			}
		}
		if(f2==true)cout<<"NO\n"; 
		else cout<<"YES\n";
	}
	return 0;
}
```


---

## 作者：Timon080923 (赞：0)

[原题链接](https://codeforces.com/contest/1499/problem/B)  
题目大意：从一个 $01$ 字符串中删去一些字符，使得这个字符串单调不降。
但是原字符串中不能有连续的两个字符被删去。
请问这样的删除方案是否存在。字符串长度不超过 $100$。  
思路：  
这道题就是模拟。如果前方出现了连续的 $0$，意味着删 $0$ 只能到这一位为止了。同理，如果后方出现了连续的 $1$，删 $1$ 也就结束了。  
那么，我们可以贪心地找出从后往前删 $0$ 最多是哪一位后面都是有序的 $1$，从前往后删 $1$ 最多是哪一位前面都是有序的 $0$。如果这两个区间可合法覆盖整个数组，那就可以了。  
核心代码：
```cpp
void test_case(int test){
	string s;
	cin>>s;
	int first1=1e9;
	for(int i=0;i+1<s.size();++i){
		if(s[i]=='1'&&s[i+1]=='1'){
			first1=i;
			break;
		}
	}
	int last0=-1;
	for(int i=0;i+1<s.size();++i){
		if(s[i]=='0'&&s[i+1]=='0'){
			last0=i;
		}
	}
	if(last0>first1){
		cout<<"NO\\n";
	}else{
		cout<<"YES\n";
	}
}
```


---

## 作者：__O_w_O__ (赞：0)

两种情况，第一种是这一段都不相同，可以直接改变；第二种是先连续的 00 后连续的 11，这种情况也可以直接改变，其余的情况无法满足单调不降的条件所以无法改变。

因此，这道题的做法显然就是看连续的 11 后面是否有连续的 00 就好了。

[通过记录](https://codeforces.com/contest/1499/submission/276063783)

```cpp
#include<bits/stdc++.h>
using namespace std;

int main()  {
	int t;
	scanf("%d", &t);
	while(t--) {
		string s;
		cin >> s;
		int len = s.size();
		bool f = 0, flag = 0;
		for (int i = 1; i < len; i++) {
			if (s[i] == '1' && s[i - 1] == '1') f = 1;
			if (f && s[i] == '0' && s[i - 1] == '0') {
				flag = 1;
				break;
			}
		}
		printf("%s\n", flag ? "NO" : "YES");
	}
	return 0;
}
```

---

## 作者：littlebug (赞：0)

## Description

简要题意：给定一个 $01$ 字符串 $s$，要求从 $s$ 中删除**任意两个不相邻**的一些数，使得 $s$ 变为单调不降的（或者说先是一堆 $0$，然后是一堆 $1$）。

## Solution

直接考虑如何可以满足要求似乎是困难的，所以我们考虑 $s$ 怎样才不可能满足要求。

首先，$s$ 不满足要求当且仅当 $s$ 在被操作后一定会存在至少一处 $0$ 在 $1$ 后面，也就是说有至少一个不会被删除的 $0$ 在一个不会被删除的 $1$ 后面，那么如何构造才能使得一个 $0$ 一定不会被删除呢？

我们发现，当且仅当存在形如 $00$ 的子串时，一定有一个 $0$ 不会被删除，所以 $1$ 同理，那么我们就只需要找到是否有 $00$ 在 $11$ 后面即可。

## Code

```cpp
#include<iostream>
#include<cstdio>
//#define int long long
#define il inline
using namespace std;

string s;
int n;

il void solve()
{
    cin>>s;
    n=s.size(); s="$"+s+"qwqawa";

    bool flag=0;
    for(int i=1;i<=n;++i)
    {
        if(s[i]=='1' && s[i+1]=='1') flag=1;
        if(flag && s[i]=='0' && s[i+1]=='0')
        {
            cout<<"NO\n";
            return;
        }
    }
    cout<<"YES\n";
}

signed main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF1499B)

如果出错，请告诉哪里错了，谢谢。

## 题目大意

字符串中，可以删去一些字符，但不能连续删去两个相同的。使得这个字符串单调不降。问是否可以。

## 分析

只要没有连续的都可以完全改变，但是如果有连续的 $0$ 或连续的 $1$ 就不能全部删去。而如果先连续 $0$ 后连续的 $1$ 也可以，如果反过来，就不行了。因为无法完成单调不降。所以只有看连续的 $1$ 后是否有连续的 $0$ 就好了。

## 下面是AC代码

```
#include<bits/stdc++.h>
using namespace std;
int main() 
{
	int n;
	cin>>n;
	while(n--)
	{
		string s;
		cin>>s;
		int l=s.size();
		bool s1=false,s2=false;
		for(int i=1;i<l;i++)
		{
			if(s[i]=='1'&&s[i-1]=='1')
			{
				s1=true;
			}
			
			if(s1==true&&s[i]=='0'&&s[i-1]=='0')
			{
				s2=true;
				break;
			}
		}
	//	cout<<s1;
		if(s2==true)
		{
			cout<<"NO"; 
		}
		else
		{
			cout<<"YES";
		}
		cout<<endl;
	}
}
```


---

