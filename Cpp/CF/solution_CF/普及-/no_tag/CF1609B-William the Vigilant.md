# William the Vigilant

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1609B/bc27b81066321842bda936f44a55e1a8e3d4f0d8.png)Before becoming a successful trader William got a university degree. During his education an interesting situation happened, after which William started to listen to homework assignments much more attentively. What follows is the correct formal description of the homework assignment:

You are given a string $ s $ of length $ n $ only consisting of characters "a", "b" and "c". There are $ q $ queries of format ( $ pos, c $ ), meaning replacing the element of string $ s $ at position $ pos $ with character $ c $ . After each query you must output the minimal number of characters in the string, which have to be replaced, so that the string doesn't contain string "abc" as a substring. A valid replacement of a character is replacing it with "a", "b" or "c".

A string $ x $ is a substring of a string $ y $ if $ x $ can be obtained from $ y $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 说明/提示

Let's consider the state of the string after each query:

1. $ s = $ "abcabcabc". In this case $ 3 $ replacements can be performed to get, for instance, string $ s = $ "bbcaccabb". This string does not contain "abc" as a substring.
2. $ s = $ "bbcabcabc". In this case $ 2 $ replacements can be performed to get, for instance, string $ s = $ "bbcbbcbbc". This string does not contain "abc" as a substring.
3. $ s = $ "bccabcabc". In this case $ 2 $ replacements can be performed to get, for instance, string $ s = $ "bccbbcbbc". This string does not contain "abc" as a substring.
4. $ s = $ "bcaabcabc". In this case $ 2 $ replacements can be performed to get, for instance, string $ s = $ "bcabbcbbc". This string does not contain "abc" as a substring.
5. $ s = $ "bcabbcabc". In this case $ 1 $ replacements can be performed to get, for instance, string $ s = $ "bcabbcabb". This string does not contain "abc" as a substring.
6. $ s = $ "bcabccabc". In this case $ 2 $ replacements can be performed to get, for instance, string $ s = $ "bcabbcabb". This string does not contain "abc" as a substring.
7. $ s = $ "bcabccaac". In this case $ 1 $ replacements can be performed to get, for instance, string $ s = $ "bcabbcaac". This string does not contain "abc" as a substring.
8. $ s = $ "bcabccaab". In this case $ 1 $ replacements can be performed to get, for instance, string $ s = $ "bcabbcaab". This string does not contain "abc" as a substring.
9. $ s = $ "ccabccaab". In this case $ 1 $ replacements can be performed to get, for instance, string $ s = $ "ccabbcaab". This string does not contain "abc" as a substring.
10. $ s = $ "ccaaccaab". In this case the string does not contain "abc" as a substring and no replacements are needed.

## 样例 #1

### 输入

```
9 10
abcabcabc
1 a
1 b
2 c
3 a
4 b
5 c
8 a
9 b
1 c
4 a```

### 输出

```
3
2
2
2
1
2
1
1
1
0```

# 题解

## 作者：yhx0322 (赞：1)

## Description
给你一个长为 $n$ 的字符串，只包含 `abc` 三种字符。有 $q$ 次操作，每次把一个位置的字符改成给定字符，询问当前串至少修改几次满足不包含子串 `abc`。修改指把一个位置的字符修改成 `a`、`b`、`c` 三种字符之一。

$1\le n,q \le 10^5$。

## Solution
显然暴力会超时，考虑如何优化。

我们可以在输入字符串的时候就统计出字符串里连续子串 `abc` 的数量。

每次询问的时候分情况讨论当前字符是 `a,b,c` 中的哪一种，然后判断输入的位置 `p` 的相邻字符是否为连续，即增加了子串 `abc`，或者减少了。每次将统计的变量，记为 `c`，根据情况加 $1$ 或减 $1$ 即可。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int n, q, p, c;
char s[N], ch;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> q >> (s + 1);
	for (int i = 1; i <= n; i++) {
		if (s[i] == 'a' && s[i + 1] == 'b' && s[i + 2] == 'c') c++;
	}
	while (q--) {
		cin >> p >> ch;
		if (ch == 'a') {
			if ((s[p - 1] == 'a' && s[p] == 'b' && s[p + 1] == 'c') ||
				(s[p - 2] == 'a' && s[p - 1] == 'b' && s[p] == 'c')) c--;
			if (s[p] != 'a' && s[p + 1] == 'b' && s[p + 2] == 'c') c++;
		} else if (ch == 'b') {
			if ((s[p] == 'a' && s[p + 1] == 'b' && s[p + 2] == 'c') ||
				(s[p - 2] == 'a' && s[p - 1] == 'b' && s[p] == 'c')) c--;
			if (s[p] != 'b' && s[p - 1] == 'a' && s[p + 1] == 'c') c++;
		} else if (ch == 'c') {
			if ((s[p] == 'a' && s[p + 1] == 'b' && s[p + 2] == 'c') ||
				(s[p - 1] == 'a' && s[p] == 'b' && s[p + 1] == 'c')) c--;
			if (s[p] != 'c' && s[p - 1] == 'b' && s[p - 2] == 'a') c++;
		}
		s[p] = ch;
		cout << c << '\n';
	}
	return 0;
}
```

---

## 作者：Marsrayd (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1609B)

## 题意简述



给你一个长为 $n$ 的字符串，只包含 ```abc``` 三种字符。$q$ 次操作，每次把一个位置的字符改成给定字符，询问当前串至少修改几次满足不包含子串 ```abc```。修改指把一个位置的字符修改成 ```a```、```b```、```c``` 三种字符之一。


## $\texttt{SOLUTION}$

首先我们可以得出一个十分显然的条件：当前穿至少修改几次才能满足不包含子串 ```abc``` ，这相当于在计算字符串中含有多少个子串 ```abc```。

那么我们的目标转化为了如何维护每时每刻子串 ```abc``` 的数量。

这十分 $\text{easy}$，判断每次操作后是否多了一个 ```abc``` 有是否少了一个 ```abc``` 即可（因为每次只改变一个字符，所以可能多了或少了 $1$ 个 ```abc```）。

具体的见代码。

$\texttt{AC CODE}$

```cpp
#include<bits/stdc++.h>
int n,q,pos,ans;
bool vis[100010];//vis[i]用来记录某个位置是否为一个子串abc开头的a，即字符串s[i],s[i+1],s[i+1]所构成的子串是否是abc。
char s[100010],wh[10];
int main()
{
	scanf("%d%d%s",&n,&q,s+1);
	for(int i=1;i<n-1;i++) if(s[i]=='a'&&s[i+1]=='b'&&s[i+2]=='c') vis[i]=1,++ans; //计算初始的abc个数。
	for(int i=1;i<=q;i++)
	{
		scanf("%d%s",&pos,wh);
		if(*wh==s[pos]) //如果修改后的字符和原来的字符相同，则abc的数量不会改变。
		{
			printf("%d\n",ans);
			continue;
		}
		//否则一定有变动。
		
		//减少的
		if((vis[pos]||vis[pos-1]||vis[pos-2])) --ans;//如果有 s[i] 或 s[i-1] 或 s[i-2] 打头的abc子串，那么子串一定被破坏了。
		//如果被破坏了，就更新 vis 数组		
		if(vis[pos]) vis[pos]=0;
		if(vis[pos-1]) vis[pos-1]=0;
		if(vis[pos-2]) vis[pos-2]=0;
		
		//新增的
		if(*wh=='a')
		{
			if(s[pos+1]=='b'&&s[pos+2]=='c') ++ans,vis[pos]=1;
		}
		if(*wh=='b')
		{
			if(s[pos-1]=='a'&&s[pos+1]=='c') ++ans,vis[pos-1]=1;
		}
		if(*wh=='c')
		{
			if(s[pos-2]=='a'&&s[pos-1]=='b') ++ans,vis[pos-2]=1;
		}
		
		//修改
		s[pos]=*wh;
		
		//输出答案
		printf("%d\n",ans);
	}
}
```


---

## 作者：Walrus (赞：0)

## 题意

给定一个长度为 $n$ 的字符串，只包含 `abc`  三种字符。这里我们将其命名为 $str$。

一共有 $q$ 次操作，每次给出一个整数 $x$ 和一个字符 $c$，当然这里的 $c$ 也是 `abc` 中的一个字符。此操作表示将字符串 $str$ 的**第 $x$ 位上的字符改为 $c$**，问你在修改完成后还要再修改几个字符才能使当前字符串不含字符串 "$abc$"。而且这里的修改同样也只能将某个字符改为 `abc` 的其中一个。



## 分析

将题意转化后发现，当完成当前修改后，对于题目要求的问题，我们通过观察发现，每一次修改一个字符要么什么事没有，要么多一个字符串 "$abc$"，要么少一个字符串 "$abc$"，所以原问题可转化为**当前字符串有多少个子串为 "$abc$"**。

想到 KMP，不过想到 KMP 的时间复杂度是 $O(n+m)$，而且本题相当于是多测，所以时间复杂度为 $O(q(n+m))$。不要又去想 AC 自动机，因为模式串永远只是 "$abc$"，所以我们只能去思考其他方法。

又回到转化的一步，还是那句话，每一次修改一个字符要么什么事没有，要么多一个字符串 "$abc$"，要么少一个字符串 "$abc$"，所以我们可以判断一下修改操作完成后是否对原串中的子串 "$abc$" 的数量有影响，记录其数量即可。单次判断时间复杂度仅有 $O(1)$，所以总时间复杂度为 $O(q)$。

先预处理出原来字符串中有多少个子串 "$abc$"，每次判断时看看有没有对 "$abc$" 的数量进行影响。





## 代码

大概意思差不多，浏览一下就是了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
char c, str[N];
int n, m, x, ans;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	cin >> (str + 1);
	for(int i = 3; i <= n; i++)//统计最开始有多少 "abc" 
		if(str[i] == 'c' && str[i - 1] == 'b' && str[i - 2] == 'a')
			++ans;
	for(int i = 1; i <= m; i++) {
		cin >> x >> c;
		if(str[x] != c) {//当然修改的时候只有和原串对应位置不相等才更改
			if(c == 'a' && str[x + 1] == 'b' && str[x + 2] == 'c')
				++ans;
			if(c == 'b' && str[x - 1] == 'a' && str[x + 1] == 'c')
				++ans;
			if(c == 'c' && str[x - 1] == 'b' && str[max(0, x - 2)] == 'a')//这里需注意会不会越界 
				++ans;
			
			//因为 str[0] 啥也没有，所以越界时直接与 0 取 max 

			if(str[x] == 'a' && str[x + 1] == 'b' && str[x + 2] == 'c')
				--ans;
			if(str[x] == 'b' && str[x - 1] == 'a' && str[x + 1] == 'c')
				--ans;
			if(str[x] == 'c' && str[x - 1] == 'b' && str[max(0, x - 2)] == 'a')//这里需注意会不会越界 
				--ans;

			str[x] = c;
		}
		cout << ans << '\n';
	}
	return 0;
}
```



---

## 作者：LOvO (赞：0)

# CF1609B William the Vigilant 题解

## [题目传送门](https://codeforces.com/contest/1609/problem/B)

### 题意简述：

有一个长为 $n$ 的字符串，只包含 `a`、`b`、`c` 三种字符。有 $q$ 次操作，每次把一个位置的字符改成 `a`、`b` 或 `c`，询问当前串至少修改几次满足不包含子串 `abc`。

### 解题思路：

显而易见，我们改一个字符，就可以消除掉一个子串 `abc`。

所以，我们的问题就变成了母串有几个子串 `abc`。

这个问题可以直接使用朴素算法，遍历数组。 ~~（我以为是 [KMP](https://oi-wiki.org/string/kmp/) ）~~ 

但是，题目还要我们修改母串，所以，我们就需要维护子串 `abc` 的数量。

显然，我们不能每修改一次就遍历一遍数组，时间承受不住。

注意到题目一次只修改母串的一个字符，所以这里我们可以枚举每种情况：

```cpp
/*
s为母串，x为修改的位置，num为子串 abc 的个数。
这里以修改后的字符为 a 为例。
修改后的字符为 b、c 同理。
*/
if (s[x] != 'a' && s[x + 1] == 'b' && s[x + 2] == 'c') num++;
//bbc、cbc -> abc,子串数量增加
if (s[x - 1] == 'a' && s[x] == 'b' && s[x + 1] == 'c') num--;
//abc -> aac,子串数量减少
if (s[x - 2] == 'a' && s[x - 1] == 'b' && s[x] == 'c') num--;	
//abc -> aba,子串数量减少
```

别忘了修改完 `abc` 出现的个数后，修改数组。

然后快乐 AC ！

## Code：

```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    cin.tie(0);
    cout.tie(0);
	string s;			// STL 里的字符数组，相当于char[]。
	int n, m;
	cin >> n >> m >> s;
	int num = 0;
	for (int i = 0; i < n - 2; i++)												//求原始数组中 abc 的个数。
		if (s[i] == 'a' && s[i + 1] == 'b' && s[i + 2] == 'c')
			num++;
	while (m--) {
		int x;			//修改的位置
		char c;			//修改后的字符
		cin >> x >> c;
        x--;			//std::string 下标默认从0开始，但观察样例后发现题目给出的修改的位置下标从1开始。
		switch(c) {
			case 'a': {															//当修改后的字符为 a。
				if (s[x] != 'a' && s[x + 1] == 'b' && s[x + 2] == 'c') num++;
				if (s[x - 1] == 'a' && s[x] == 'b' && s[x + 1] == 'c') num--;
				if (s[x - 2] == 'a' && s[x - 1] == 'b' && s[x] == 'c') num--;
				break;
			}
			case 'b': {															//当修改后的字符为 b。
				if (s[x] == 'a' && s[x + 1] == 'b' && s[x + 2] == 'c') num--;
				if (s[x - 1] == 'a' && s[x] != 'b' && s[x + 1] == 'c') num++;
				if (s[x - 2] == 'a' && s[x - 1] == 'b' && s[x] == 'c') num--;
				break;
			}
			case 'c': {															//当修改后的字符为 c。
				if (s[x] == 'a' && s[x + 1] == 'b' && s[x + 2] == 'c') num--;
				if (s[x - 1] == 'a' && s[x] == 'b' && s[x + 1] == 'c') num--;
				if (s[x - 2] == 'a' && s[x - 1] == 'b' && s[x] != 'c') num++;
				break;
			}
		}
		s[x] = c;				//修改
		cout << num << endl;	//输出
	}
	return 0;
}
```

---

## 作者：PvbeLLN (赞：0)

# CF1609B
### 分析
根据题意，要求“还要至少多少次变化才能使序列中不含`abc`”，而每次操作可以产生或消除一个`abc`，因此所求最小操作次数即为当前序列中`abc`的个数。

由于 $1\leq n,q\leq10^5$，每次更改过后重新扫描序列统计`abc`的个数显然会超时。考虑到每次操作只会更改相临近的几个字母构成的序列中“`abc`的存在个数”，因此可以在输入整个序列后先统计出序列中的`abc`总个数`cnt`，对于以后的每次询问，只要判断是增加了还是减少了`abc`，并在`cnt`的基础加 $1$ 或减 $1$ 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,cnt,pos;
char s[100005],now;

int main()
{
	cin>>n>>q;
	for (int i=1;i<=n;i++) cin>>s[i];
	for (int i=1;i<=n;i++) if (s[i]=='a'&&s[i+1]=='b'&&s[i+2]=='c') cnt++;    //统计原序列中abc个数 
	for (int i=1;i<=q;i++)
	{
		cin>>pos>>now;     //输入每次操作 
		if (now=='a')     //对于不同的输入分别判断abc是增加了还是减少了 
		                  //只看代码可能有点难理解，可以自己模拟一下 
		{
			if (s[pos-1]=='a'&&s[pos]=='b'&&s[pos+1]=='c') cnt--;
			if (s[pos-2]=='a'&&s[pos-1]=='b'&&s[pos]=='c') cnt--;
			if (s[pos]!='a'&&s[pos+1]=='b'&&s[pos+2]=='c') cnt++;
		}
		else if (now=='b')
		{
			if (s[pos]=='a'&&s[pos+1]=='b'&&s[pos+2]=='c') cnt--;
			if (s[pos-2]=='a'&&s[pos-1]=='b'&&s[pos]=='c') cnt--;
			if (s[pos]!='b'&&s[pos-1]=='a'&&s[pos+1]=='c') cnt++;
		}
		else if (now=='c')
		{
			if (s[pos]=='a'&&s[pos+1]=='b'&&s[pos+2]=='c') cnt--;
			if (s[pos-1]=='a'&&s[pos]=='b'&&s[pos+1]=='c') cnt--;
			if (s[pos]!='c'&&s[pos-1]=='b'&&s[pos-2]=='a') cnt++;
		}
		s[pos]=now;
		printf("%d\n",cnt);      //输出答案 
	}
	return 0;
}
```


---

## 作者：_zhx (赞：0)

#  CF1609B William the Vigilant 题解

## 题目大意

一个长为 $n$ 的字符串，只包含 $a$、$b$、$c$ 三种字符。$q$ 次操作，每次把一个位置的字符改成 $a$、$b$、$c$ 三种字符之一，询问当前串至少修改几次满足不包含子串 $abc$。

### 题目分析

我们可以先求出子串 $abc$ 的数量。

对于每次操作，我们只需判断操作后是否多了一个子串 $abc$ 或是少了一个子串 $abc$ 就可以了。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,x,d=0;bool f[100010];string s;char c;
//d是子串abc的数量统计，f是标记数组，bool省空间（int也行）
int main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>q>>s;
	for(int i=0;i<n-2;i++) if(s[i]=='a'&&s[i+1]=='b'&&s[i+2]=='c') f[i]=1,d++;
    //从s[0]~s[n-2]，如：abcbca 因为一次判三个，最后两个在倒数第三个已经判过了
	for(int i=1;i<=q;i++)
	{
		cin>>x>>c;
		if(s[--x]==c)//如果修改的字符和原来的字符相同，那么子串 abc 的数量不变，所以可以跳过
		{
			printf("%d\n",d);
			continue;
		}
		if((f[x]==1||f[x-1]==1||f[x-2]==1)) d--;//子串 abc 减少了
     //改变 f 数组
		if(f[x]==1) f[x]=0;
		if(f[x-1]==1) f[x-1]=0;
		if(f[x-2]==1) f[x-2]=0;
        //新增的子串 abc
		if(c=='a'&&s[x+1]=='b'&&s[x+2]=='c') d++,f[x]=1;
		if(c=='b'&&s[x-1]=='a'&&s[x+1]=='c') d++,f[x-1]=1;
		if(c=='c'&&s[x-2]=='a'&&s[x-1]=='b') d++,f[x-2]=1;
		s[x]=c;
		printf("%d\n",d);
	}
	return 0;
}
```


---

## 作者：hao_zi6366 (赞：0)

## 题意简述

有一个由字母 abc 组成的字符串，每次把其中一个字符修改成指定字符，输出进行这次修改后至少还要进行几次修改才能使该串不包含子串 abc。

## 题目分析

不包含子串 abc，换而言之，就是求出现在有的子串 abc 的数量。可以考虑暴力枚举，每改一次就求一遍子串 abc 的数量。  

不过这么做显然会超时。观察发现，改一次只会对周围几个字符产生影响，所以判断一次更改后会不会在周围产生或消除子串 abc 即可。

以判断改变成 a 会不会有影响为例：
```cpp
if(c=='a' && s[now]!='a'){		//如果把非 a 的字母改成了 a 
            if(s[now+1]=='b' && s[now+2]=='c')cnt++;				//是否会和后面两个字母组合产生新的abc 
            if(s[now]=='b' && s[now-1]=='a' && s[now+1]=='c')cnt--;	//是否会消除一个原有的 abc
            if(s[now]=='c' && s[now-2]=='a' && s[now-1]=='b')cnt--;	//是否会消除一个原有的 abc
        }
```
改成 b 或 c 也如此操作即可。

## 完整代码
```cpp
#include<bits/stdc++.h>
#define N 100005
typedef long long ll;

int n,q,cnt=0;
std::string s;
int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
    
    std::cin>>n>>q;
    std::cin>>s;
    for(int i=2;i<s.size();i++){	//先算一遍abc的数量 
        if(s[i]=='c' && s[i-1]=='b' && s[i-2]=='a')cnt++;
    }
    for(int i=0;i<q;i++){
        int now;char c;
        std::cin>>now>>c;now--; 
        if(c=='a' && s[now]!='a'){		//如果把非a的字母改成了a 
            if(s[now+1]=='b' && s[now+2]=='c')cnt++;				//是否会产生新的abc 
            if(s[now]=='b' && s[now-1]=='a' && s[now+1]=='c')cnt--;	//是否会消除一个abc
            if(s[now]=='c' && s[now-2]=='a' && s[now-1]=='b')cnt--;	
        }
        if(c=='b' && s[now]!='b'){		//如果把非b的字母改成了b 
            if(s[now-1]=='a' && s[now+1]=='c')cnt++;				//是否会产生新的abc 
            if(s[now]=='a' && s[now+1]=='b' && s[now+2]=='c')cnt--;	//是否会消除一个abc
            if(s[now]=='c' && s[now-2]=='a' && s[now-1]=='b')cnt--;
        }
        if(c=='c' && s[now]!='c'){		//如果把非c的字母改成了c
            if(s[now-2]=='a' && s[now-1]=='b')cnt++;				//是否会产生新的abc 
            if(s[now]=='a' && s[now+1]=='b' && s[now+2]=='c')cnt--;	//是否会消除一个abc
            if(s[now]=='b' && s[now-1]=='a' && s[now+1]=='c')cnt--;
        }
        std::cout<<cnt<<"\n";
        s[now]=c;						//不要忘记把s[now]更新哦！ 
    }
	return 0;
}
```



---

## 作者：智子 (赞：0)

## 题意

给你一个长为 $n$ 的字符串，只包含 `abc` 三种字符。$q$ 次操作，每次把一个位置的字符改成给定字符，询问当前串至少要修改几次才能满足不包含子串 `abc`。修改指把一个位置的字符修改成 `a`、`b`、`c` 三种字符之一。

## 思路

首先，每一个 `abc` 子串绝对不可能会重叠，所以有多少个 `abc` 子串就要修改多少次。所以每次修改时维护一共有多少个 `abc` 子串，输出当前的 `abc` 子串个数即可。

具体来说，修改第 $pos$ 个字符最多只会影响 $[pos - 3, pos + 3]$ 区间内的 `abc`，修改前扫一遍，修改后扫一遍，答案改变的值就是两者的差。

## 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 100000 + 5;

char s[MAXN];
int n, q, cnt;

int main() {
    scanf("%d%d%s", &n, &q, s + 1);
    for(int i = 1; i + 2 <= n; i++) {
        if(s[i] == 'a' && s[i + 1] == 'b' && s[i + 2] == 'c') {
            cnt++;
        }
    }
    for(int i = 1; i <= q; i++) {
        char op[10], c;
        int pos, sum1 = 0, sum2 = 0;

        scanf("%d%s", &pos, op);
        for(int i = max(1, pos - 5); i <= min(n, pos + 5); i++) {
            if(s[i] == 'a' && s[i + 1] == 'b' && s[i + 2] == 'c') {
                sum1++;
            }
        }
        s[pos] = op[0];
        for(int i = max(1, pos - 5); i <= min(n, pos + 5); i++) {
            if(s[i] == 'a' && s[i + 1] == 'b' && s[i + 2] == 'c') {
                sum2++;
            }
        }
        cnt = cnt - (sum1 - sum2);
        
        printf("%d\n", cnt);
    }

    return 0;
}

```

---

## 作者：XL4453 (赞：0)

### 解题思路：

发现每一个字符串需要修改的次数就是这个串中 abc 的个数。从两方面考虑，首先不可能小于，因为一次修改最多能使得一个 abc 变成非 abc；另一方面，一定存在一种方案使得只修改 abc 出现次数次就能将所有的 abc 消除。

所以只需要统计当前修改后的串中有多少 abc 就行了，但是，直接进行统计复杂度是 $O(n^2)$ 的，不能通过，考虑加一个小优化。

发现每一次修改只会影响周围的一点点部分，考虑直接计算贡献，也就是先减去更改前有的更改后没了的，然后加上更改前没有，更改后有了的，这样单次复杂度就是 $O(1)$ 的了。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
char c,s[100005];
int n,m,x,tot;
char get(){
	char c1=getchar();
	while(c1==' '||c1=='\n'||c1=='\r')c1=getchar();
	return c1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	s[i]=get();
	for(int i=3;i<=n;i++)
	if(s[i]=='c'&&s[i-1]=='b'&&s[i-2]=='a')tot++;
	for(int i=1;i<=m;i++){
		scanf("%d",&x);c=get();
		if(s[x]!=c){
			if(c=='c'&&s[x-1]=='b'&&s[max(0,x-2)]=='a')tot++;
			if(c=='b'&&s[x-1]=='a'&&s[x+1]=='c')tot++;
			if(c=='a'&&s[x+1]=='b'&&s[x+2]=='c')tot++;
			
			if(s[x]=='a'&&s[x+1]=='b'&&s[x+2]=='c')tot--;
			if(s[x]=='b'&&s[x-1]=='a'&&s[x+1]=='c')tot--;
			if(s[x]=='c'&&s[x-1]=='b'&&s[max(0,x-2)]=='a')tot--;
			
			s[x]=c;
		}
		printf("%d\n",tot);
	}
	return 0;
}
```


---

## 作者：Lovely_Elaina (赞：0)

### 思路

因为 `abc` 不能和自己匹配前后串，即不会出现重叠的情况。

那么对于任意一次修改，最多只能消去一个 `abc` 串，也最多只能创造出一个 `abc` 串。

那么先计算出原始字符串含有几个 `abc` 串（即原始字符串需要修改几次才能消去所有 `abc` 串）。

对于每次操作：

- 如果并没有改变，所需删除次数不变；
- 如果多创造出了一个 `abc` 串，所需删除次数加 $1$；
- 如果消去了一个 `abc` 串，所需删除次数减 $1$。

判断消去和创造直接分讨目标字符修改成 `a`、`b`、`c` 的情况就可以了。

换而言之就是简单模拟。

### 代码

```cpp
#include <bits/stdc++.h>
// #define int long long
#define endl '\n'
using namespace std;
const int N = 1e5+5;

int q,n;
string s;
char c;
int cnt,x;

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    cin >> n >> q >> s;
    
    int si = s.size();
    s = '-' + s;
    for(int i = 1; i < si-1; i++){
        if(s[i] != 'a' || s[i+1] != 'b' || s[i+2] != 'c')
            continue;
        cnt++;
    }
    
    while(q--){
        cin >> x >> c;
        if(s[x] == c){
            cout << cnt << endl;
            continue;
        }
        
        if(x < si-1 && s[x] == 'a' && s[x+1] == 'b' && s[x+2] == 'c'
          || x > 1 && x < si && s[x-1] == 'a' && s[x] == 'b' && s[x+1] == 'c'
          || x > 2 && s[x-2] == 'a' && s[x-1] == 'b' && s[x] == 'c'){
            cnt--,s[x] = c;;
        }
        
        if(c == 'a' && x < si-1 && s[x+1] == 'b' && s[x+2] == 'c') cnt++;
        else if(c == 'b' && x > 1 && x < si && s[x-1] == 'a' && s[x+1] == 'c') cnt++;
        else if(c == 'c' && x > 2 && s[x-2] == 'a' && s[x-1] == 'b') cnt++;
        
        s[x] = c;
        cout << cnt << endl;
        // cout << s << endl;
    }
    return 0;
}
```

---

