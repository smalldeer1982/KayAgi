# [ABC394C] Debug

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc394/tasks/abc394_c

给定一个仅由大写字母组成的字符串 $S$。  
请输出对 $S$ 执行以下操作后得到的最终字符串：

> 只要字符串中包含连续的 `WA` 子字符串，就重复执行以下操作：
> 
> - 将字符串中首次出现的 `WA` 替换为 `AC`。

可以证明在本题的约束条件下，此操作最多只能执行有限次。

## 说明/提示

### 约束条件

- $S$ 是长度介于 $1$ 到 $3 \times 10^5$ 之间的仅由大写字母组成的字符串

### 样例解释 1

初始字符串为 $S=$ `WACWA`。该字符串包含从第 $1$ 到 $2$ 个字符和从第 $4$ 到 $5$ 个字符的 `WA` 子字符串。第一次操作将替换最先出现的部分（即第 $1$ 到 $2$ 个字符），得到 `ACCWA`。此时字符串仅剩第 $4$ 到 $5$ 个字符的 `WA`，第二次操作替换后得到 `ACCAC`。由于 `ACCAC` 不再包含 `WA`，操作终止，因此输出 `ACCAC`。

### 样例解释 2

初始字符串为 $S=$ `WWA`。该字符串仅在第 $2$ 到 $3$ 个字符处包含 `WA`。第一次操作替换后得到 `WAC`，此时新字符串在第 $1$ 到 $2$ 个字符处出现 `WA`。第二次操作替换后得到 `ACC`。由于不再包含 `WA`，操作终止，因此输出 `ACC`。

### 样例解释 3

原始字符串 $S$ 中不包含 `WA` 子字符串，因此无需任何操作，直接输出 `WWWWW`。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
WACWA```

### 输出

```
ACCAC```

## 样例 #2

### 输入

```
WWA```

### 输出

```
ACC```

## 样例 #3

### 输入

```
WWWWW```

### 输出

```
WWWWW```

# 题解

## 作者：ryf2011 (赞：2)

# 题目思路
我们枚举一遍字符串，找到所有出现子串 $\texttt{WA}$ 的位置并记录下来。

之后枚举每个 $\texttt{WA}$ 出现的位置，将其改为子串 $\texttt{AC}$，再从这个位置向左枚举，每遇到一个 $\texttt{WA}$ 就将其更改为 $\texttt{AC}$，直到枚举到头。

这种方法的速度较慢，但成功在本题时间限制内通过了题目，详见 [AtCoder abc394_c 通过记录](https://atcoder.jp/contests/abc394/submissions/63068887) 中的信息。

# 代码
注：本代码仅供参考。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int max_n=3e5+5;
char s[max_n];
int l,r,wa[max_n],cnt; //wa[i]：第 i 个子串 WA 所在位置 
int main(){
	scanf("%s",s+1);
	for(int i=1;i<=strlen(s+1)-1;i++){
		if(s[i]=='W'&&s[i+1]=='A'){
			cnt++;
			wa[cnt]=i;
		}
	}
	for(int i=1;i<=cnt;i++){
		//更改为 AC 
		s[wa[i]]='A';
		s[wa[i]+1]='C';
		for(int j=wa[i];j>=2;j--){ //向左枚举，将所有的 WA 都改为 AC 
			if(s[j]=='A'&&s[j-1]=='W'){
				s[j-1]='A';
				s[j]='C';
			}
			else{
				break;
			}
		}
	}
	for(int i=1;i<=strlen(s+1);i++){ //输出 
		printf("%c",s[i]);
	}
	printf("\n");
	return 0;
}
```

#### 后记
更多内容，请移步至 [$\color{red}\texttt{ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")。

---

## 作者：boluo2014 (赞：2)

这是一道很简单的题目。
### 思路
首先，考虑一种情况，如果有 $k$ 个字母 W 的后面有一个 A，那最后变成 A 和 C 的结果就是一个 A 和 $k$ 个 C。

所以，我们只需要循环，找到 W，然后看到后面有几个 W，有没有 A。然后有可能要输出一个 A 和很多的 C。但是注意，输出了以后，一定要让循环变量 $i$ 跳过这一段，否则可能会超时。

### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	string s;
	int a,i;
	cin>>s;
	a=s.size();
	for(i=0;i<a;i++){
		if(s[i]!='W'){
			cout<<s[i];
			continue;
		}
		if(i==a-1){ 
			cout<<'W'<<endl;
			continue;
		}// 只需要考虑其他 W 的情况 
		int j,k;
		bool f=false;
		int w=0;
		for(j=i;j<a;j++){
			if(s[j]=='W'){
				w++;
			}
			if(s[j]!='W'){
				if(s[j]=='A'){//需要输出AC的情况 
					cout<<"A";
					for(k=1;k<=w;k++){
						cout<<"C";
					}
					i+=w;
					if(i+1>=a)return 0;
				}
				else{
					for(k=1;k<=w;k++){
						cout<<"W";
					}
					i+=(w-1); 
					if(i>=a)return 0;
				}
				break;
			}
		}
		if(j==a){
			for(k=1;k<=w;k++){
				cout<<'W';
			}
			break;
		}
	}
	cout<<endl;
	return 0;
} 
```

---

## 作者：Iron_Spade (赞：2)

啊这个题不是很那啥吗？为什么有的小朋友写了一大坨？

## Solution

注意到 `AC` 和 `WA` 是有 `A` 这个相同字符的，如果将 `WA` 变成 `AC` 那么这个 `AC` 中的 `A` 可能和前面的 `W` 继续组成一个新的 `WA` 变成 `AC`。

这样的操作启示了我们可以**倒着做这个问题**，具体直接看代码吧。

```cpp
void sol() {
	cin >> s; n = s.size(), s = ' ' + s;
	pre(i, n, 1) if(s[i] == 'A' && s[i - 1] == 'W') s[i - 1] = 'A', s[i] = 'C';
	rep(i, 1, n) cout << s[i];
}
```

---

## 作者：Tjaweiof (赞：1)

# AT_abc394_c 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc394_c)

从后往前枚举，看见 `WA` 改成 `AC` 就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int n;
string s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	n = s.size();
	for (int i = n - 1; i >= 1; i--){
		if (s[i - 1] == 'W' && s[i] == 'A'){
			s[i - 1] = 'A';
			s[i] = 'C';
		}
	}
	cout << s;
	return 0;
}

```

---

## 作者：getchar_unlocked (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc394_c)

### 思路

首先不难想到遍历整个字符串，把所有的 $\texttt{WA}$ 替换成 $\texttt{AC}$。然而这样遍历一遍，原字符串中可能会存在新的 $\texttt{WA}$。反复遍历最多会有 $N$ 次，时间复杂度 $\mathcal{O}(N^2)$，不可行。

所以倒着遍历，这样就会覆盖掉新的 $\texttt{WA}$。时间复杂度 $\mathcal{O}(N)$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	string s;cin>>s;
	for(int i=s.size()-1;i>=1;--i)
		if(s[i]=='A'&&s[i-1]=='W')
			s[i]='C',s[i-1]='A';
	cout<<s<<"\n";
	return 0;
}
```

---

## 作者：qhr2023 (赞：1)

## solution

模拟题。

每找到一个 ```WA``` 就把它替换成 ```AC```，替换后 ```A``` 可能和前面的构成 ```WA```，所以我们要退回去一个位置，实际上下标要减二，因为循环时下标会自增。还要注意若在开头下标减完可能为负，特判掉即可。

## code

[code](https://atcoder.jp/contests/abc394/submissions/63020661)。

---

## 作者：PDAFX (赞：1)

## 题目大意

有一个字符串，遇到 AC 替换成 WA，问最终字符串是多少。

## 思路

直接模拟的时间复杂度为 $O(n^2)$，无法过此题。\
我们模拟发现，更改第一个 AC 后，新的 WA 只会在 AC 前面，并且在上一个 AC 后。\
他只会影响他前面的 A。\
例如：WWA->WAC->ACC。\
发现后，我们按照此规律，从第一个 WA 一直向前搜，由于他只影响两个 AC 之间的 A, 所以时间复杂度仅有 $O(n)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int main()
{
	cin>>a;
	for(int i=0;i<a.size();i++)
	{
		if(a[i]=='W'&&a[i+1]=='A')
		{
			int tmp=i;
			while(tmp>=0&&a[tmp]=='W'&&a[tmp+1]=='A')
			{
//				cout<<tmp<<endl;
//				tmp--;
				a[tmp]='A';
				a[tmp+1]='C';
				tmp--;
			}
		}
	}
	cout<<a;
}
```

---

## 作者：hoko (赞：1)

根据题目描述，对于每一个 WA 要替换成 AC，如果我们从前往后遍历会出现问题，比如 WWA，从前往后遍历只会把结尾的 WA 换成 AC，也就会变成 WA，明显不正确。

所以从后往前遍历，便可以很好的解决这类问题。最终复杂度为 $O(n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int main(){
	getline(cin,s);
	for(int i=s.size()-1;i>=0;i--){
		if(s[i]=='A'&&s[max(i-1,0)]=='W'){
			s[i]='C',s[i-1]='A';
		}
	}
	cout<<s;
	return 0;
} 
```

---

## 作者：cqbzhzf (赞：1)

[vjudge 中文翻译](https://vjudge.net/problem/AtCoder-abc394_c#author=GPT_zh)
### 思路
首先考虑暴力，每次只要遇到 `WA` 就变成 `AC`，直到没有 `WA` 为止。这样肯定是会超时的。

进一步思考，发现修改 `WA` 为 `AC` 只会对前一个字符的答案有影响。例如字符串为 `WWA`，修改 `WA` 为 `AC` 后为 `WAC`，原本没有 `WA` 的地方出现了 `WA`，面对这种情况，只需要将位置 $i$ 减一即可，并不需要从头重新遍历，从而降低时间复杂度。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int i=0;
	string s;
	cin>>s;
	while(i<s.length())
	{
		if(s[i]=='W'&&s[i+1]=='A')
		{
			s[i]='A',s[i+1]='C';
			if(i>0)
				i--;
			else
				i=0;			
		}
		else
			i++;
	}
	cout<<s;
	return 0;
}
```

---

## 作者：lilong (赞：1)

模拟样例可以发现，操作本质上是将形如若干个 W 加上一个 A 的字符串变为同样长度的一个 A 加上若干个 C 的字符串。于是按照这个规则找到并替换这样的字符串即可。

时间复杂度 $O(n)$。


```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    string s;
    int n;
    cin >> s;
    n = s.size();
    for( int i = 0 ; i < n ; )
    {
        if( s[i] != 'W' )
        {
            cout << s[i];
            i ++;
            continue;
        }
        int j = i;
        while( j < n && s[j] == 'W' ) j ++;
        j --;
        if( j == n - 1 )
        {
            for( int k = i ; k <= j ; k ++ )
                cout << "W";
            i = j + 1;
        }
        else if( s[j + 1] != 'A' )
        {
            for( int k = i ; k <= j ; k ++ )
                cout << "W";
            i = j + 1;
        }
        else
        {
            cout << "A";
            for( int k = i + 1 ; k <= j + 1 ; k ++ )
                cout << "C";
            i = j + 2;
        }
    }
    return 0;
}
```

---

## 作者：dg114514 (赞：1)

### 题意

给定字符串 $S$，每次找到最左边的 `WA`，并替换为 `AC`。一直这样替换下去直到不能替换为止时，问最终的 $S$。

### 思路

暴力枚举时，当 $S=\texttt{WWW\dots A}$ 时，是 $O(|S|^2)$ 的。考虑优化。可以想到，每次将 `WA` 替换为 `AC` 时，仅当 `WA` 前面一个字符是 `W` 时才会产生新的 `WA`，即查找时的前面。所以可以直接每次枚举 $i$ 往 $i$ 前面（含）找 `WA` 并换为 `AC`。这样就可以 `AC` 了。

#### 复杂度

由于每个 `AC` 变成的 `WA` 和 `WA` 本身的总和为 $O(|S|)$ 级别，所以复杂度为 $O(|S|)$。

### 代码

非常简单。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	for(int i=1;i<s.size();i++){
		int j=i;
		while(j>=0&&s[j-1]=='W'&&s[j]=='A')
			s[j-1]='A',s[j]='C',j--;
	}
	cout<<s;
	return 0;
} 
```

---

## 作者：nr0728 (赞：1)

注意到 `WA` 变成 `AC` 后可以与前面的 `W` 再次组成 `WA`。例如 `WWA` 变为 `WAC` 之后应该再变为 `ACC`。

再次注意到一个 `WA` 变成 `AC` 只会影响前面，于是倒着扫一遍，如果是 `WA` 就改成 `AC` 即可。

---

## 作者：MaiJingYao666 (赞：1)

# AT_abc394_c [ABC394C] Debug 题解    
### 解题思路
非常简单的一道题啊，观察样例发现由于 AC 的第一个字符和 WA 的最后一个字符是一样的，所以为了保证影响，需要从后往前搜。  
然后就没有什么要注意的了。  

### AC 代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
char a[300005];
int main(){
	cin>>a;
	int len=strlen(a);
	for(int i=len-1;i>=0;i--){
		if(a[i]=='A' && a[i-1]=='W'){
			a[i-1]='A';
			a[i]='C';
		}
	}
	cout<<a;
}
```

---

## 作者：Tomwsc (赞：1)

# AT_abc394_c [ABC394C] Debug 题解

## 题意

给定一个字符串，要求把所有的 ```WA``` 替换成 ```AC```。替换完之后还出现的 ```WA``` 也要再次替换。

## 思路

我们发现，如果将 ```WA``` 替换成 ```AC``` 后能再组成 ```WA``` 的只可能是 ```WA``` 前面还有 ```W``` 的情况。但这样并不好正序处理，于是我们不妨从后往前遍历，遇到 ```WA``` 就替换成 ```AC```，然后就做完了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf (1ll << 62)
using namespace std;
const int MAXN = 3e5 + 10;
string s;
char c[MAXN];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	int len = s.length();
	for(register int i = len - 1;i >= 0;i --)
		if(s[i] == 'A' && s[i - 1] == 'W') {
			s[i] = 'C';
			s[i - 1] = 'A';
		}
	cout << s;
	return 0;
}
```

---

## 作者：__Accepted_ZYF__ (赞：0)

稍微有点绕。

我们注意到一次修改 `WA` 改为 `AC` 是有可能出现 `WWA` 这种修改一个而出现可以修改的另一个字符串的情况。

但是我们可以倒着修改，这样修改之后不会出现其他在后面需要匹配的新字符串，而倒着修改，就算出现了新字符串，也会在接下来的修改中被覆盖。

具体手玩一下也可以会。


```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ivan422{
	#define ll long long
	#define ld long double 
	#define il __int128
	#define fl __float128
	#define x0 x_0
	#define x1 x_1
	#define y0 y_0
	#define y1 y_1
	#define yn y_n
	#define j0 j_0
	#define j1 j_1
	#define k0 k_0
	#define k1 k_1
	#define d0 d_0
	#define d1 d_1
	#define pb push_back
	#define pf push_front
	#define mp make_pair
	#define ar array<int,3>
	#define us unsigned
	#define io ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
};
using namespace ivan422;
const int N=2e5+10,M=1e3+10;
const int P1=1e9+7,P9=998244353;
const double pi=3.1415926535,eps=1e-7;
string s;
int n;
signed main(){
	io;
	cin>>s;n=s.size();
	for(int i=n-2;i>=0;i--){
		if(s[i]=='W'&&s[i+1]=='A'){
			s[i]='A';
			s[i+1]='C';
		}
	}
	cout<<s;
	return 0;
}
```

---

## 作者：Furina_Saikou (赞：0)

# 题目大意

给定一个字符串 $s$，把 $s$ 中所有的 `WA` 改成 `AC`，注意改完之后可能会出现新的。

# 思路

扫一遍 $s$，如果出现 `WA`，就改成 `AC`，再一直往前扫是否有新的 `WA`，因为改完之后已经扫过的串结尾是 `C`，所以不会出现同一个点被多次改的情况，所以时间复杂度是 $O(n)$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	cin>>s;
	for(int i=1;i<s.size();i++)//STL的size都是O(1)的
	{
		int j=i;
		while(s[j-1]=='W'&&s[j]=='A')
		{
			s[j]='C';
			s[--j]='A';
		}
	}
	cout<<s;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

注意到一个 `WA` 变成 `AC` 后左边的 `A` 可能会与其他 `W` 组成新的 `WA`。

所以只需要从右往左判断，每遇到 `WA` 改成 `AC` 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char c[1000005];
int main(){
	cin>>c+1;
	n=strlen(c+1);
	for(int i=n;i>=1;i--){
		if(c[i]=='A'&&c[i-1]=='W')
			c[i]='C',c[i-1]='A';
	}
	cout<<c+1;
	return 0;
}
```

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_abc394_c)

题目要求：将最后的 WA 改成 AC，不断执行此操作，直到没有 WA 了。

从最后开始找，找到一个换一个就行。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define endl '\n'
#define inf INT_MAX 
using namespace std;
const int N=1e6+7;
const int M=1e6+7;
const int mod=1e9+7;
const double eps=1e-6;
signed main(){
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	string s;
    cin >>s;
    for(int i=s.size()-1;i>=1;i--){//遍历字符串，要保证不越界
    	if(s[i]=='A'&&s[i-1]=='W'){//判断，更改
    		s[i]='C';
    		s[i-1]='A';
		}
	}
	cout<<s<<endl;//输出
	return 0;
}
```

---

## 作者：yaaaaaan (赞：0)

## 思路
首先，容易想到直接扫一遍，遇到 `WA` 就替换为 `AC`。

然而这种思路很容易被卡掉，例如 `WWA`，当把后两位改成 `AC` 后，第一位的 $W$ 和第二位的 $A$ 又会形成 `WA`，又要改成 `AC`。

我们可以观察出，当把 `WA` 改成 `AC` 后，只需要判断前面是否有 $W$，而对后面没有影响。那我们不妨直接倒着模拟，就不需要特判了。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
#define ll long long
using namespace std;
string s;
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>s;
	for(int i=s.size()-1;i>=0;i--)
	{
		if(s[i]=='W'&&s[i+1]=='A')
		{
			s[i]='A';
			s[i+1]='C';
		}
	}
	cout<<s<<"\n";
	return 0;
}
```

---

## 作者：cqbzcjh (赞：0)

首先暴力是肯定会 T 飞的。

考虑什么时候会产生新的 `WA`，可以发现 `AC` 的第一个字符是 `A`，所以如果前面还有一个 `W` 就会产生新的 `WA`。如果前面有多个 `W` 就会不断产生 `WA` 然后改为 `AC`。

所以找到一个 `A` 就往前找连续的 `W`，并将第一个 `W` 改为 `A`，其他的 `W` 和 `A` 都改为 `C` 即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>s;n=s.size();
	for(int i=0;i<n;i++){
		if(s[i]=='A'&&s[i-1]=='W'){
			int j=i;
			while(s[j-1]=='W'){
				s[j]='C';
				j--;
			}
			s[j]='A';
		}
	}
	cout<<s;
	return 0;
}
```

---

## 作者：yr409892525 (赞：0)

## 题解：AT_abc394_c [ABC394C] Debug
从后向前遍历如果，遇到 WA 就改成 AC，最后直接输出修改后的字符串。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,inf=1e9;
string s;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>s;
    int n=s.size();
    s=" "+s;
    for(int i=n-1;i>=1;i--){
        if(s[i]=='W'&&s[i+1]=='A'){
            s[i]='A',s[i+1]='C';
        } 
    }
    cout<<s;
	return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

注意到当每次 `WA` 改成 `AC` 后，会对前面的操作产生影响（如样例 $2$）。

所以倒着修改即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 10;
const int M = 4e2 + 10;
const int inf = 1e16;
int T,n;
string s;
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
signed main(){
	close();
	cin >> s;
	n = s.size();
	for (int i = n - 1 ; i >= 1 ; i--){ // 倒序修改
		if (s[i] == 'A' && s[i - 1] == 'W'){ // 能改就改
			s[i] = 'C';
			s[i - 1] = 'A';
		}
	}
	cout << s << endl;
	return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

将 WA 变成 AC 等价于将一个 A 往前推一格。

找到每个 A 前面接的一串 W，将最前一个 W 变为 A，将 A 以及除了第一个 W 之外的 W 变为 C。

然后就做完了。
```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#include <chrono>
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
const int N = 1e5 + 10;
string s;
int n;
void run()
{
	cin >> s;
	n = s.size();
	for (int i = 0, j = 0; i < n; i++)
	{
		if (s[i] != 'A')
			continue;
		if (!i or s[i - 1] != 'W')
			continue;
		j = i - 1;
		while (~j and s[j] == 'W')
			j--;
		j++;
		s[j] = 'A';
		j++;
		while (j <= i)
			s[j] = 'C', j++;
	}
	cout << s;
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	run();
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

## 作者：xiaobeng_0912 (赞：0)

## $\mathbf{Knowledge}$

1. 模拟

## $\mathbf{Solution}$

分析样例，我们不难发现，在每次将 `WA` 替换成 `AC` 时，都有可能产生一个额外的 `WA`。例如 `WWA`，当你将 `WA` 替换成 `AC` 后，整个字符串就变成了 `WAC`，此时又出现了一个 `WA`，我们还需要将它换成 `AC`，最终得到 `ACC`。

对于这种额外的 `WA` 的处理，我们可以在遍历到某个字符时，判断这个字符和下一个字符是否组成 `WA`，如果组成，则将其替换成 `AC`，然后回到上一个字符处，判断是否产生了新的 `WA`，直到遍历结束。

## $\mathbf{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int i;
int main(){
	cin>>s;
	while(i<s.size()-1){
		if(s[i]=='W'&&s[i+1]=='A'){//如果发现一个 WA
			s[i]='A'; //修改成 AC
			s[i+1]='C';
			i=max(i-1,0); //回到上一个，看看有没有新形成的 WA（如果当前这个字符是这个字符串的首字符就不用回到上一个了）
		}else{
			i++;
		}
	}
	cout<<s;
	return 0;
}
```

---

