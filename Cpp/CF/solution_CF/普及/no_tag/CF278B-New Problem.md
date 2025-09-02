# New Problem

## 题目描述

Coming up with a new problem isn't as easy as many people think. Sometimes it is hard enough to name it. We'll consider a title original if it doesn't occur as a substring in any titles of recent Codeforces problems.

You've got the titles of $ n $ last problems — the strings, consisting of lowercase English letters. Your task is to find the shortest original title for the new problem. If there are multiple such titles, choose the lexicographically minimum one. Note, that title of the problem can't be an empty string.

A substring $ s[l...\ r] $ $ (1<=l<=r<=|s|) $ of string $ s=s_{1}s_{2}...\ s_{|s|} $ (where $ |s| $ is the length of string $ s $ ) is string $ s_{l}s_{l+1}...\ s_{r} $ .

String $ x=x_{1}x_{2}...\ x_{p} $ is lexicographically smaller than string $ y=y_{1}y_{2}...\ y_{q} $ , if either $ p&lt;q $ and $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{p}=y_{p} $ , or there exists such number $ r $ $ (r&lt;p,r&lt;q) $ , that $ x_{1}=y_{1},x_{2}=y_{2},...\ ,x_{r}=y_{r} $ and $ x_{r+1}&lt;y_{r+1} $ . The string characters are compared by their ASCII codes.

## 说明/提示

In the first sample the first 9 letters of the English alphabet (a, b, c, d, e, f, g, h, i) occur in the problem titles, so the answer is letter j.

In the second sample the titles contain 26 English letters, so the shortest original title cannot have length 1. Title aa occurs as a substring in the first title.

## 样例 #1

### 输入

```
5
threehorses
goodsubstrings
secret
primematrix
beautifulyear
```

### 输出

```
j
```

## 样例 #2

### 输入

```
4
aa
bdefghijklmn
opqrstuvwxyz
c
```

### 输出

```
ab
```

# 题解

## 作者：__Immorta__ (赞：5)

**题目大意：**

给定 `n` 个字符串，需要求出一个字符或者字符串，要求改字符、字符串不是给定的字符串的任意一个字串。

**特殊要求：**

不得与给定的字符串重复其子串。

需要输出字典序最小的那一个。

**思维逻辑**

- 可以使用 `vector` 动态数组来存储输入的字符串。

- 暴力枚举一位子串，找到就直接返回输出。

- 注意顺序，先是一位，然后叠加。还需要注意字典序的顺序

- 记录方面可以使用 `set` 来记录，自带去重。

```c
for (char c = 'a'; c <= 'z'; ++c) {
        string num(1, c);
        bool flag = true;
        for (const string& str : vv) {
            if (str.find(num) != string::npos) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return num;
        }
    }
```

- 如果一位未找到枚举二位子串。

```c
for (char c1 = 'a'; c1 <= 'z'; ++c1) {
        for (char c2 = 'a'; c2 <= 'z'; ++c2) {
            string num(2, c1);
            num[1] = c2;
            bool flag = true;
            for (const string& str : vv) {
                if (str.find(num) != string::npos) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                return num;
            }
        }
    }
```

**其他方面：**

头文件可以使用一下三个，亦或是万能头。
```c
#include <vector>
#include <string>
#include <set>
```

**Code：**

查找部分已经放在了上面，所以下面只放输入部分的代码，（主函数）的部分。

```c
vector<string> v;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
    	string x;
    	cin>>x;
    	v.push_back(x);
	}
    string ans = find(v);
    cout<< ans << endl;
```


因为在洛谷里 `CF` 交不了，所以整体代码放在[这里](https://www.luogu.com.cn/paste/2fyijzzp)，方便审核

---

## 作者：opzc35 (赞：3)

# CF278B 题解
[==>题目传送门<==](/problem/CF278B)
## 题意

给你 $n$ 个字符串，让你构造一个字典序最小的字符串，使得这个字符串不是这 $n$ 个字符串中任意一个的字串。

## 分析

这道题看到大家都是用的 DFS 解决的，我来交一个 BFS 解决的方法。

我们可以从空串开始，每一次都在队列中加入本来的字符串加上任意一个字符的字符串。如果我们看到这个字符串没有是任何一个的字串，我们就可以认定这个字符串为答案。

鉴于题目 $n \le 30$ 且 $\lvert s_i \rvert \le 20$，摆明了想让我们暴力解决了这个题

## 代码片段

首先，我们需要一个函数来判断一个字符串是否是这些字符串的子串

```cpp
bool check(string str){
	for(auto v:s){
		//查看是否是已经被占用过的名字的
		for(int i=0;i+str.size()-1<v.size();i++){
			string tmp=v.substr(i,str.size());
			if(str==tmp){
				return true;
			}
		}
	}
	return false;
}
```

然后就是 BFS 的核心代码

我们只需要从空串开始，每次将队列头增加 a 到 z 的每一个字符。

如果队列头的字符串不是任意一个字符串的子串，我们就可以认定它为一个答案，并且由于 BFS 的性质，第一个找到的字符串肯定是最优的答案

```cpp
void bfs(){
	queue<string> q;
	q.push("");
	//从空串开始
	while(s.size()){
		string top=q.front();
		q.pop();
		if(!check(top)&&top!=""){
			//符合题意，并且为字典序最小的字符串
			cout<<top;
			return;
		}
		for(char x='a';x<='z';x++){
			q.push(top+x);
		}
	}
}
```

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<string> s;
bool check(string str){
	for(auto v:s){
		//查看是否被占用过
		for(int i=0;i+str.size()-1<v.size();i++){
			string tmp=v.substr(i,str.size());
			if(str==tmp){
				return true;
			}
		}
	}
	return false;
}
void bfs(){
	queue<string> q;
	q.push("");
	//从空串开始
	while(s.size()){
		string top=q.front();
		q.pop();
		if(!check(top)&&top!=""){
			//符合题意，并且为字典序最小的字符串
			cout<<top;
			return;
		}
		for(char x='a';x<='z';x++){
			q.push(top+x);
		}
	}
}
int n;
string x;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		s.push_back(x);
	}
	bfs();
	return 0;
}
```
AC记录：https://codeforces.com/contest/278/submission/290355703

---

## 作者：Patients (赞：3)

[题目由此去](https://www.luogu.com.cn/problem/CF278B)

------------

~~你谷交不了CF的题了，但不妨碍我写题解。~~

## 分析：

考场时没有想出来具体做法，写了个偏分代码走人了（骗了 $ 50 $ 分）。

考后一分析，发现还是比较水的。

标签 ： ``` 搜索 ```。

1. 将所有不行的名字全部找出来，用 map 来储存。

2. 将所有的情况都列举一遍，用 DFS 处理。

3. 对于大于已经算出的结果的答案，可以直接剪掉。

好，这题就结束了。

### 代码：

```cpp
#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n,Min=0x7fffffff/2;
string a[10086],ans;
map<string,bool>t;
void dfs(int k,string s)
{
	if(k>1 && !t[s])
	{
		if(s.length()<Min)
		{
			Min=s.length();
			ans=s;
		}
		return ;
	}
	for(char i='a';i<='z';i++) dfs(k+1,s+i);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=0;j<a[i].length();j++)
			for(int k=j;k<a[i].length();k++)
			{
				string ss=a[i].substr(j,k-j+1);
				t[ss]=1;
			}
	dfs(1,"");
	cout<<ans;
	return 0;
}
```


---

## 作者：szh_AK_all (赞：2)

### 题意
一共有 $n$ 个字符串，我们要求出一个字典序最小的字符串，使得该字符串不为 $n$ 个字符串中任意字符串的子串。

### 分析
~~这题肯定用字典树来做啊~~

我们需要将每个字符串所包含的所有子串加入字典树中，由于普通的字典树是用来存储字符串的所有前缀的，所以我们可以倒着枚举每个字符串，这样，就可以将所有子串加入字典树中。

举个例子，我们要将 `abc` 的所有子串加入字典树中，则按照如上所述的方法，倒着枚举 `abc`。

1. 枚举到 `c`，将 `c` 加入字典树中；
2. 枚举到 `bc`，将 `b` 和 `bc` 加入字典树中；
3. 枚举到 `abc`，将 `a`、`ab` 和 `abc` 加入字典树中。

处理完子串后，由字典序从小到大暴力枚举每个字符串，看看该字符串在字典树中是否出现，若没出现，继续搜索，否则，直接输出答案。

那么如何由字典序从小到大枚举字符串呢？首先，枚举我们要得出的字符串的长度，在搜索中，若搜得的字符串大小与期望长度相等，则进行判断；否则，按照 $26$ 个字母的顺序依次尝试加入字符串末尾。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;

namespace trie {
	const int S = 300005;
	int son[S][30], siz = 1;
	int sum[S];

	void in(string s) {
		int p = 0;
		sum[p]++;
		for (int i = 0; i < s.size(); i++) {
			int e = s[i] - 'a' + 1;
			if (son[p][e])
				p = son[p][e];
			else
				p = son[p][e] = siz++;
			sum[p]++;
		}
	}

	int ask(string s) {
		int p = 0;
		for (int i = 0; i < s.size(); i++) {
			int e = s[i] - 'a' + 1;
			if (son[p][e])
				p = son[p][e];
			else
				return 0;
		}
		return sum[p];
	}
}

void dfs(int len, int x, string s) {
	if (x > len) {
		if (!trie::ask(s)) {
			cout << s;
			exit(0);
		}
		return;
	}
	for (int i = 0; i < 26; i++) {
		string t = s;
		s += char('a' + i);
		dfs(len, x + 1, s);
		s = t;
	}
}

int main() {
	int n;
	cin >> n;
	int maxn = 0;
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		string t = "";
		for (int j = s.size() - 1; j >= 0; j--) {
			t += s[j];
			string k = t;
			for (int y = 0; y < t.size(); y++)
				k[t.size() - y - 1] = t[y];
			trie::in(k);
		}
	}
	for (int i = 1; i <= 20; i++)
		dfs(i, 1, "");
}
```


---

## 作者：doubleyu (赞：2)

### 分析

因为 $n$ 最大为 $30$，字符串长度最大为 $20$，所以最多出现 $600$ 个字符。而两个字符的，有 $26\times26 = 676$（第一和第二个字母都有 $26$ 种），也就是说可能性共有 $676$ 种，即最多只能存在两个字符。

也就是说输出的只有可能是一个字符或两个字符。

如果实在没想出来，也可以用 DFS 做，法二就是使用的这种方法实现的。

------------
### 代码实现

#### 法一：

```cpp
#include <bits/stdc++.h>
using namespace  std;
struct node{
	string b;
}a[105];
int n,cc,p[30],dd,f[30][30];//f[i(第一个字母),j（第二个字母）]
int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i].b;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<a[i].b.size();j++){
			p[a[i].b[j]-97]+=1;//先判断是否是输出一个字符，a[i].b[j]-97相当于在求下标
		}
	}
	for(int i=0;i<25;i++){//一个一个判断
		if(p[i]==0){
			cout<<char(i+97);
			dd=1;
			return 0;
		}
	}
	if(dd!=1){//是输出两个字符
		for(int i=0;i<n;i++){//将所有的两个字符存起来
			for(int j=0;j<a[i].b.size();j++){
				if(j!=a[i].b.size()-1){
					f[a[i].b[j]-97[a[i].b[j+1]-97]=1;
				}
		}
	}
		
		for(int i=0;i<25;i++){//循环找字典序最小且没有出现过的字符
			for(int j=0;j<25;j++){
				if(f[i][j]==0){
					cout<<char(i+97)<<char(j+97);
					return 0;
				}
			}
		}
	}
	return 0;
}
```
------------
#### 法二 (DFS)

```cpp
#include<bits/stdc++.h>
using namespace std;
map<string,bool> M;
string p;
bool flag;
void dfs(int t){
	for(int i=0;i<=25;i++){
		string pp=p;
		p+=char(97+i);
		if(M[p]==0){
			cout<<p; 
			flag=1;
			return;
		}
		p=pp;
	}
	for(int i=0;i<=25;i++){
		string pp=p;
		p+=char(97+i);
		dfs(t+1);
		if(flag)return;
		p=pp;
	}
	return; 
}
int main(){

	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		for(int j=0;j<=s.length()-1;j++){
			for(int k=j;k<=s.length()-1;k++){
				string ne;
				int cnt=-1;
				for(int x=j;x<=k;x++){
					ne+=s[x];
				} 
				M[ne]=1;
			}
		}
	}
	dfs(0);
	return 0;
} 
```

---

## 作者：lizhixun (赞：1)

[题目传送门在这里](https://codeforces.com/problemset/problem/278/B)。

这题是黄题，但是不是很难。一遍就 AC 了，呵呵呵。虽然洛谷上不能提交，但还是不影响我做题呵呵呵。

### 题意简析

给定 $n$ 个字符串，让你求一个字典序最小的，满足其不是任何一个字符串的子串的字符串。

### 思路

暴力枚举，按字典序大小一个一个字符串枚举，长度越来越长。

当然我们可以用 DFS 搜索来做这道题。

DFS 函数里三个参数，分别如下：

|参数|类型|表示的意义|
|:-:|:-:|:-:|
|step|int|当前在函数里的字符串长度，也可以省略|
|sz|int|当前字符串需要达到的长度，搜索结束的条件|
|ss|string|当前的字符串|

那么搜索或者是枚举的长度的范围是什么呢？

答案如下：

假如我们设输入的字符串的最大长度是 $maxn$，那么需要枚举的长度最多也就是 $maxn+1$。

因为如果你枚举的字符串的长度比任何一个输入的字符串都要长，那么肯定就绝对不会是任何一个字符串的子串。

那么我们如何判断字符串是否符合要求呢？

接下来我们就要引入一个函数：`find`。

这个 STL 函数的用法：
```cpp
string s, ss = "abc";
s = "abcabc";
cout << s.find(ss);
```

他会返回你要查找的字符串在另外一个字符串第一次出现的下标，如果没有出现返回`-1`。

像上面这段程序就会输出 $0$。

那我们的判断函数就可以这样写：

```cpp
bool check(string ss) {
	for (int i = 1; i <= n; i++) {
		if (s[i].find(ss) != -1) return 0; //如果字符串是s[i]的子串，就直接返回0
	}
	
	return 1; //满足条件，返回1
}
```

DFS 部分就是直接枚举就行了，没有太多技术含量。只要找到了符合条件的，那就一定是字典序最小的，输出后直接退出程序即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e2 + 5;
int n, maxn = -1e18;
string s[N];

bool check(string ss) {
	for (int i = 1; i <= n; i++) {
		if (s[i].find(ss) != -1) return 0;
	}
	
	return 1;
}

void dfs(int step, int sz, string ss) {
	if (step == sz + 1) {
		if (check(ss) == 1) {
			cout << ss;
			exit(0);
		}
		
		return;
	}
	
	for (char i = 'a'; i <= 'z'; i++) dfs(step + 1, sz, ss + i);
}

signed main() {
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		int len = s[i].size();
		maxn = max(maxn, len);
	}
	
	for (int i = 1; i <= maxn + 1; i++) dfs(1, i, "");
	return 0;
}
```

注意一点，警钟敲烂！

输入字符串的时候，求最大长度一定要**定义中间变量**，要不然你会喜提 CE 大礼包一份的。

完结撒花。

---

## 作者：Paracelestia (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF278B)

## $\texttt{Description}$

见题面。

## $\texttt{Solution}$

题目要求的串没有规定长度，考虑使用迭代加深搜索。

设答案串长度为 $len$，时间复杂度 $\mathcal{O} (26^{len}n)$。

最多有 $30$ 个串，每个串长度不超过 $20$，手玩一下感觉 $len$ 很难超过 $2$，应该能过。

实际提交后发现 $len$ 均不大于 $2$，轻松通过。

## $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 114514
#define M 1919810
#define fi first
#define se second

typedef long long ll;
typedef pair<int, int> pii;

template<typename T> inline T read() {
    T x = 0, f = 1; char ch = 0;
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch - '0');
    return x * f;
}

template<typename T> inline void write(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

template<typename T> inline void print(T x, char ed = '\n') {
    write(x), putchar(ed);
}

int n, dep;
string s[N];

void dfs(string t) {
    if(t.size() > dep) return ;
    bool f = 0;
    for(int i = 1; i <= n; ++ i) 
        if(s[i].find(t) != -1) {f = 1; break;}
    if(!f) {
        cout << t << endl;
        exit(0);
    }
    for(char ch = 'a' ; ch <= 'z'; ++ ch) dfs(t + ch);
}

signed main() {
    n = read<int>();
    for(int i = 1; i <= n; ++ i) cin >> s[i];
    for(dep = 1; dep <= 20; ++ dep) dfs("");
    return 0;
}
```


---

## 作者：pyz51 (赞：0)

[题目传送门（CF）](https://codeforces.com/problemset/problem/278/B)

[AC记录](https://codeforces.com/contest/278/submission/286083561)

# 题目简介
给定 $n$ 个字符串，求字典序最小的不属于其中任何一个字符串的子串的字符串。
# 题解
这题和我之前做过的[一道题](https://www.luogu.com.cn/problem/CF1536B)很像。  
两题都是以字典序从小到大暴力搜索。

Q：为什么可以呢？  
A：因为 $n\le30,|s|\le20$，那么这些字符串中最多就 $(20-1)\times30=570$ 个由两个字符构成的子串，而所有的由两个字符构成的字符串就有 $26^2=676$ 个，所以无论数据如何，**答案最多就两个字符**。
### 结论：仅需枚举长度为 $1$ 和 $2$ 的字符串。
那么代码就好写了。
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define mem(a,b) memset(a,b,sizeof a)
int t,n,flag;
char now[3];
string s[50];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>s[i];
	bool vis=0;
	rep(i,0,25){
		flag=0;
		now[0]='a'+i;
		rep(j,1,n){
    		rep(r,0,s[j].size()){
    			if(now[0]==s[j][r]){
    				flag=1;
    				break;
    			}
    		}
		}
		if(!flag&&!vis) cout<<now[0]<<'\n',vis=1;
	}//长度为1
	rep(i,0,25){
		rep(j,0,25){
			flag=0;
			now[0]='a'+i,now[1]='a'+j;
			rep(k,1,n){
			    rep(r,0,s[k].size()-1){
			    	if(now[0]==s[k][r]&&now[1]==s[k][r+1]){
			    		flag=1;
			    		break;
			    	}
			    }
			}
			if(!flag&&!vis) cout<<now[0]<<now[1]<<'\n',vis=1;
		}
	}//长度为2
    return 0;
}
```

---

## 作者：CR7_siu (赞：0)

这题是一道 $\texttt{DFS}$ 枚举的[题目](https://www.luogu.com.cn/problem/CF278B)。我们只需要把所有属于给出的字符串的子串存进一个 $\texttt{set}$ 里面，在 $\texttt{DFS}$ 枚举出来之后，如果这个字符串在 $\texttt{set}$ 里面没有出现过，那么不属于任何一个字符串的子串，直接输出并结束程序即可。

那么 $\texttt{DFS}$ 会不会超时呢，答案是不会，因为输入的字符串最多出现 $30 \times 20 = 600$ 种字符，而光是两个字符就有 $26^2=676$ 种，所以答案的字符串的长度不可能超过 $2$ 个字符。既然长度这么短，那就肯定不会 $\texttt{TLE}$ 的。

我们的 $\texttt{DFS}$ 函数里只需要两个参数，一个是字符串，初始为空串，还有一个是枚举的长度，根据上面的分析，我们只需要枚举到 $2$ 就行。

思路已经很清楚了，代码就不贴了。

---

## 作者：chrispang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF278B)

---

### 分析：
这道题看着很复杂，其实只有把关系弄明白就很简单了。

- $1$、首先我们定义一个 unordered_map，第一位放 string 类型，第二位放 bool 类型，之后把所有字符串的子串都记录下。
- $2$、进行 DFS，枚举 $26$ 个字母，每次在这个字符串的后面加上这个字母，接着继续搜索。
- $3$、最后是边界条件。如果这个字符串 s 的长度 $num > 1$，或者 s 没有遍历过（即 s 不是执行 $1$ 操作时遍历到的字串），则进行记录。如果 s 的长度小于上一个符合要求的字符串的长度 mint，则进行更新，否则直接跳过。

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, mint = 0x3f3f3f3f; //mint表示上一个符合字符串的长度 
string ans, s[35];
unordered_map<string, bool>vis; //一般unordered_map查询速度更快 
void dfs(int num, string t) { //num表示字符串里已经有多少字符了，t表示当前字符串 
	if(t.size() >= num) return; //剪枝，注意这里是>=，而不是>，因为我们要求字典序最高的那一个 
	if(num >= 1 && !vis[t]) { //如果字符数量大于1，说明已经是一个像样的字符串了，并且还要没有被访问过 
		if(num < mint) { //如果长度小于上一个符合字符串的长度，则说明可以 
			mint = t.size(); //记录符合字符串的新长度 
			ans = t; //记录答案 
			vis[t] = 1; //进行标记 
		}
		return;
	}
	for (char c = 'a'; c <= 'z'; c++) dfs(num + 1, t + c); //枚举新字符串 
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> s[i];
	for (int i = 1; i <= n; i++) //枚举没以字符串 
		for (int j = 0; j < s[i].size(); j++) //枚举字串左端点 
			for (int k = j + 1; k <= s[i].size(); k++) //枚举子串右端点 
				vis[s[i].substr(j, k - j)] = 1; //进行标记 
	dfs(0, ""); //开始dfs 
	cout << ans << endl;
	return 0;
}
```
好了，到此题解就完了，希望屏幕前的你能为本蒟蒻点个赞，好吗！

---

## 作者：AK_lwh_888 (赞：0)

## 题目大意
题目的意思大概是这样的：我们要求出一个字典最小并且不是题目给我们的那些字符串的子串的一个字符串，将它输出。
## 题解
题目首先会输出一堆字符串，我们可以用字符串数组给那些字符串存储起来，我就用 ```a[]``` 来表示了。而我们将要输出的那个字符串我就用字符来表示，但是还要加一个表示长度的一个变量。


```cpp
const int N=31;
string a[N];
char s[101];
int n,len=1;
```

而 ```check``` 函数的功能就是判断我们的字符串 ```s``` 是不是题目给我们的那几个字符串的子串，如果不是就返回 ```false``` 否则就返回 ```true```。这个函数我们要循环题目给我们的 ```n``` 个字符串，在一一判断一下我们的字符串 ```s``` 是否等于子串，如果等于就 ```return false;```

以下是 ```check``` 的代码：

```cpp
bool check(){
	int s1;
	for(int i=1;i<=len;++i){
		s1+=s[i];
	}
	bool flag=true;
	for(int i=1;i<=n;++i){
		string ch;
		for(int j=0;j<a[i].size();++j){
			ch+=a[i][j];
			if(ch==s1){
				flag=false;
				break;
			}
		}
		if(flag==false)break;
	}
	if(flag==false){
		return false;
	}
	else return true;
}
```

最后就是 ```main``` 函数里面的了。题目让我们求字典最小的一个字符串，我们可以用 ```while``` 循环来写。如果 ```check``` 函数一旦返回的是 ```false``` 那么 ```while``` 循环就会退出，否则就会将字符串 ```s``` 的最后一个字符加 $1$，但如果是 ```z``` 那么就不可以加 $1$ 了，要再加一个字母 ```a```。

最后就是代码了
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=31;
string a[N];
char s[101];
int n,len=1;
bool check(){
	int s1;
	for(int i=1;i<=len;++i){
		s1+=s[i];
	}
	bool flag=true;
	for(int i=1;i<=n;++i){
		string ch;
		for(int j=0;j<a[i].size();++j){
			ch+=a[i][j];
			if(ch==s1){
				flag=false;
				break;
			}
		}
		if(flag==false)break;
	}
	if(flag==false){
		return false;
	}
	else return true;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	while(!check()){
		if(s[len]=='z'){
			len++;
			s[len]+='a';
		}
		else s[len]++;
	}
	for(int i=1;i<=len;++i){
		cout<<s[i];
	}
	cout<<"\n";
	return 0;
} 
```

---

