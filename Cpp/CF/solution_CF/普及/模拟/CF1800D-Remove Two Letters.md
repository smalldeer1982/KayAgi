# Remove Two Letters

## 题目描述

Dmitry has a string $ s $ , consisting of lowercase Latin letters.

Dmitry decided to remove two consecutive characters from the string $ s $ and you are wondering how many different strings can be obtained after such an operation.

For example, Dmitry has a string "aaabcc". You can get the following different strings: "abcc"(by deleting the first two or second and third characters), "aacc"(by deleting the third and fourth characters),"aaac"(by deleting the fourth and the fifth character) and "aaab" (by deleting the last two).

## 说明/提示

The first example is explained in the statement.

In the third example, the following strings are obtained: "cdef", "adef", "abef", "abcf", "abcd".

In the seventh example, any deletion will result in the string "aba".

## 样例 #1

### 输入

```
7
6
aaabcc
10
aaaaaaaaaa
6
abcdef
7
abacaba
6
cccfff
4
abba
5
ababa```

### 输出

```
4
1
5
3
3
3
1```

# 题解

## 作者：LegendaryGrandmaster (赞：12)

当没有一次重复的时候，因为每次删去 2 个字符，所以为 $n-1$ 种。

设字符串中的连续三个字符分别为 $s1,s2,s3$，弹出两个字符后为 $S$。

当弹出 $s1,s2$ 时，$S=s3$。

当弹出 $s2,s3$ 时，$S=s1$。

可得，当 $s1=s3$ 时，字符串重复。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void slove()
{
	string st;
	int n;
	cin>>n>>st;
	int ans=n-1;
	for(int i=0;i<st.size()-2;i++)
		if(st[i]==st[i+2])ans--;
	cout<<ans<<'\n';
}
signed main()
{
	int t;
	cin>>t;
	while(t--)slove();
}
```

---

## 作者：cff_0102 (赞：3)

### 本题题意：

原来的翻译：给定一个长度为 $n$ 的字符串，通过删除其中的两个**连续**字符可以获得 $n-1$ 个新的字符串。求这些新的字符串中有多少个不同的。

可能不好理解，是吧？

比如 `cff_0102` 这个字符串，可以选择移去头两个字符 `cf`，得到的字符串就是 `f_0102`；还可以移去 `ff`，得到的就是 `c_0102`。按照这样，这个长度为 $8$ 的字符串就能产生 $7$ 个新的字符串。然后，求这些字符串中有几个不同的。

### 解法：

还是考虑 `cff_0102`，发现移掉 `01` 和移掉 `10` 后剩下的字符串都是 `cff_02`，这两个串是相同的。很容易可以发现，对于字符串 $a$ 中的字符 $a_i$，如果 $a_i=a_{i+2}$，那么移去 $a_i,a_{i+1}$ 和 $a_{i+1},a_{i+2}$ 后的结果是相同的，那么从头到尾扫一遍字符串每个字符，挨个判断会不会重复，再减掉重复个数就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;cin>>t;
	while(t--){//询问 $t$ 次 
		int n;cin>>n;
		char a[n];cin>>a;//输入
		int s=n-1;//最后不重复的数量，注意是从 $n-1$ 开始减的
		for(int i=0;i<n-2;i++){
			if(a[i]==a[i+2])s--;//这样的话删除中间两个数时最后得到的字符串就会相同，需减去 $1$ 
		}
		cout<<s<<endl;//输出最后的答案
	}
	return 0;
}
```


---

## 作者：I_am_kunzi (赞：1)

# CF1800D 题解

### 题目大意

有 $ t $ 组测试数据，其中每组有以下的输入输出。

> 给你一个 $ n$，还有一个长度为 $ n $ 的字符串，每次删去相邻的两个字符，求出删去后的 $ n - 1 $ 种情况中，有几种情况是互不相同的，输出这个值。

其中，有 $ 1 \le t \le 10 ^ 4 , 3 \le n \le 2 \times 10 ^ 5 , \sum n \le 2 \times 10 ^ 5$。

### 题目分析

暴力判断的话复杂度太高，会超时，那么我们需要其他便捷的做法。

为了更好的讲解，我会拿 ``` abacabc ``` 这个字符串来举例子。我们不妨先把删掉相邻两字符后的几种情况列出，分别是：```acabc acabc ababc ababc abaca```。

可以注意到，$1 , 2 $ 两种情况相同，$3 , 4 $ 两种情况相同，再观察一下，可以发现前两种情况分别删除了 ``` ab , ba```，而删掉 ``` ab ``` 时，留下了最后一个 ``` a```；删掉 ``` ba ``` 时，留下了第一个 ``` a```。

那么我们可以下结论，如果有三个连续的字符形如 ``` aba ``` 的形式，那么删去前两个和后两个的结果相同，而这个结论用于解释 $ 3 , 4 $ 两种情况相同也是说得通的。简而言之，如果满足 ``` s[i] == s[i + 2]```，那么情况数就要减一。

### 代码时间

```cpp
#include<iostream>
#include<cstring>
#include<string>
using namespace std;
signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		string s;
		cin >> s;
		int num = n - 1; //初始情况数要为长度减一 
		for(int i = 0 ; i < n - 2 ; i++) //注意字符串默认从 0 下标开始读入，且对于 string 类型亦可使用如 s[i] 的数组写法 
		{
			if(s[i] == s[i + 2]) //判断条件 
			{
				num--;
			}
		}
		cout << num << endl;
	}
    return 0;
}
```


---

## 作者：Larryyu (赞：1)

## _Description_

给定 $n$ 和一个长度为 $n$ 的字符串 $s$。

令 $s'$ 为 $s$ 删去两个连续字符后剩余的字符串，问共有多少个不同的 $s'$。

共 $t$ 组数据。
## _Solution_
例：```aabacac```

可以发现去掉第二三字母和去掉三四字母是一样的。

我们将整个字符串分成 ```a```，```aba```，```cac``` 三个部分，由于只改动二三四这三个字母，所以第一三部分忽略。删二三时，第二部分变成第四个字母 ```a```，而删三四时，第二部分变成 第二个字母 ```a```，所以如果 $s_i=s_{i+2}$，那么删 $i,i+1$ 和 $i+1,i+2$ 时剩余字母相同。

枚举重复的数量，即 $s_i=s_{i+2}$ 的数量，再用总数量 $\left\vert s\right\vert-1$ 减去重复数量即可。

## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int t;
int a[3005];
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve(){
	int n=read(),ans=0;
	string s;
	cin>>s;
	for(int i=2;i<n;i++){
		if(s[i]==s[i-2]) ans++;
	}
	cout<<n-1-ans<<endl;
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

## 作者：aeiouaoeiu (赞：1)

### 题意

给你一个长为 $n$ 的字符串 $s$，你可以从中删去两个连续的两个字符，问删去字符后能得到多少个不同的字符串。

### 解法

可以发现最多能得到 $n-1$ 个不同的字符串，那我们只需要去除重复的字符串就可以了。

设 $s=\overline{c_1c_2c_3\ldots c_n}$。

我们可以看看两个删去部分包含同一个字符的字符串：$s_1=\overline{c_1c_2c_3\ldots c_{k-1}c_{k+2}\ldots c_n}$ 与 $s_2=\overline{c_1c_2c_3\ldots c_{k-2}c_{k+1}\ldots c_n}$。

发现满足 $s_1=s_2$ 的充要条件是 $c_{k+1}=c_{k-1}
$。

那有没有一个 $s_3=\overline{c_1c_2c_3\ldots c_{q-1}c_{q+2}\ldots c_n}$，使得 $s_3\ne s_1$ 且 $s_3=s_2$ 呢？

答案是不存在，因为使得 $s_3=s_2$ 仍需要 $c_{k+1}=c_{k-1}$ 成立，而此时 $s_1=s_2$，则 $s_3=s_1$。

所以我们就有了一个方法：将答案初始值设为 $n-1$，枚举 $k$，看看 $c_{k+1}=c_{k-1}$ 是否成立，成立就将答案减去 $1$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=200005;
ll t,n;
string s;
int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin>>t;
    while(t--){
    	cin>>n>>s;
    	ll ans=n-1;
    	s=" "+s;
    	for(int i=2;i<=n-1;i++){
    		if(s[i-1]==s[i+1]) ans--;
		}
		cout<<ans<<"\n";
	}
    return 0;
}
```




---

## 作者：Pwtking (赞：0)

本题主要做题方法：**找规律**。

朴素的做法为暴力枚举每个新的字串再用 $n^2$ 复杂度去判重，但是这样显然超时！

实际上，我们可以枚举每一个将要删除的连续子串，观察每次删除后剩的字符串的规律。当我们发现若一个将要删除的字符串如 $\mathrm{ab}$ 时，若 $\mathrm{ab}$ 前或其后又有一个 $\mathrm{a}$，那么在这三个字符 $\mathrm{aba}$ 中，**无论我们删除哪个字串 $\mathrm{ab}$，都会剩下一个相同的字符**。这意味着，如果有相连的三个字符 $s1$，$s2$，$s3$，如果 $s1=s3$，那么这三个字符中的两种删除情况只会产生一种不同的字符串。对应到代码中，也就是把初始情况数减一。

初始情况数即为 $n-1$ 种字符串。

AC code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll T,n;
char c[200010];
signed main() {
	T=in();
	while (T--) {
		n=in();
		ll ans=n-1;
		for (ll i=1;i<=n;++i) cin>>c[i];
		for (ll i=1;i<=n-2;++i) {
			if (c[i]==c[i+2]) ans--;
		}
		cout<<ans<<endl;
	}
	return 0;
}

```


---

## 作者：sgl654321 (赞：0)

### 题目大意
- 给定一个长度为 $n$ 的字符串 $s$（下标从 $1$ 开始），对于 $\forall i\in[1,n-1]$，将 $s_i$ 和 $s_{i+1}$ 在字符串中删去，得到一个新的字符串 $t$。
- 询问不同的 $t$ 有几个。

### 解题思路
例如一个字符串 $\mathtt{abbbcc}$。

删去第 $2,3$ 的 $\mathtt{b}$ 和删去第 $3,4$ 的 $\mathtt{b}$，结果显然都是 $\mathtt{abcc}$。

考虑一般情况，对于删去第 $i,i+1$ 两个字母和删去第 $i+1,i+2$ 两个字母,由于前面的第 $1\sim i-1$ 个字母都是相同的，同理后面的 $i+3\sim n$ 也是相同的。

而第一种删的方法中间留下了 $s_{i+2}$，第二种删的方法中间留下了 $s_i$。

因此如果有一个 $s_i$ 与 $s_{i+2}$ 重复，就必然有两个相同的新字符串 $t$。

首先将答案设为 $n-1$，遍历 $i\in[1,n-2]$。如果有一个 $s_i$ 与 $s_{i+2}$ 相同，那么答案减去 $1$。

最终输出答案即可。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,ans;
char ch[200010]; 
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>ch[i];
		ans=n-1;
		for(int i=1;i<=n-2;i++)
			if(ch[i]==ch[i+2])ans--;
		cout<<ans<<endl;
	}
	return 0;
}
```




---

## 作者：lfxxx (赞：0)

虽然不同的难以统计，但是统计相同的却很简单。

由于每次删除相邻两个字符，因此我们考虑连续 $4$ 的情况。

`s1s2s3s4` 考虑删除 `s1s2` 和删除 `s2s3` 的区别。

删除后变成 `s3s4` 和 `s1s4` 因此，不同的情况当且仅当 $s_{i} = s_{i+2}$。

并且显然一共的方案只有 $n - 1$ 种。

所以用 $n - 1$ 减去统计的答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
void work(){
    string s;
    int n;
    cin>>n;
    cin>>s;
    int sum=0;
    for(int i=0;i+2<s.size();i++){
    	if(s[i]==s[i+2]) sum++;
	}
	cout<<s.size()-sum-1<<'\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    cin>>T;
    while(T--) work(); 
}


```


---

## 作者：qifan_maker (赞：0)

### 题目链接
[洛谷](https://www.luogu.com.cn/problem/CF1800D)

[Codeforces](https://codeforces.com/contest/1800/problem/D)
### 题意分析
给定一个长度为 $n$ 的字符串 $s$，你可以删除两个连续的字符，问能得到多少种不同的字符串。
### 题目解法
首先，我们假设字符串 $s$ 为 `abcde`，

可以发现有 $4$ 种情况：

删除 $\rm\fbox{ab}cde$，得到 `cde`，

删除 $\rm a\fbox{bc}de$，得到 `ade`，

删除 $\rm ab\fbox{cd}e$，得到 `abe`，

删除 $\rm abc\fbox{de}$，得到 `abc`，

可以发现在没有重复字符的情况下，可能的情况有 $n-1$ 种。

但是我们考虑一种情况，假设字符串 $s$ 为 `aaabc`，

如果按照之前的规律，有 $4$ 种情况：

删除 $\rm\fbox{aa}abc$，得到 `abc`，

删除 $\rm a\fbox{aa}bc$，得到 `abc`，

删除 $\rm aa\fbox{ab}c$，得到 `aac`，

删除 $\rm aaa\fbox{bc}$，得到 `aaa`，

可以发现第 $1$ 种和第 $2$ 种情况是重复的，

也就是如果有 $3$ 个连续的字符，如 `aaa`、`aba`，

我们可以删除前 $2$ 个或后 $2$ 个字符，这时就会剩下第 $1$ 个字符或第 $3$ 个字符，

但是如果第 $1$ 个字符和第 $3$ 个字符是相等的，那么这两种可能就重复了，

所以如果 $s[i-1]=s[i+1]$，那么可能的数量就要减少 $1$，

我们把重复可能的数量用一个变量 $cnt$ 记录下来，

最后输出 $n-1-cnt$ 就可以了。
### [AC](https://www.luogu.com.cn/record/103660877) Code
```cpp
/*
题目编号：
D. Remove Two Letters
思路：
无
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
    while (t--){
    	int n;
		string s;
    	cin >> n >> s;
    	int cnt=0;
    	for (int i=1;i<n-1;i++){
    		if (s[i-1] == s[i+1]){
    			cnt++;
			}
		}
		cout << n-1-cnt << endl;
	}
	return 0;
}
```

---

## 作者：wukaichen888 (赞：0)

令 $D_i$ 表示删除 $[i-1,i]$ 字符得到的字符串，下文中 $j\lt i$。

对于每个 $i$（$2\le i\le n$），如果 $D_i$ 未在 $D_j$ 出现过，则不同字符串的数量加 $1$。于是有暴力判断的 $O(n^3)$ 做法。

观察 $D_i=D_j$ 的条件。

![](https://cdn.luogu.com.cn/upload/image_hosting/lc6i820u.png)

如图，红色线段表示删除的字符。

显然前后缀是一定相等的，所以当 $a=b$ 时，$D_i=D_j$。当 $D_i=D_j$ 时，$a=b$。

当 $D_i=D_j$ 时，$S_i=S_{i-2}$，此时 $D_i=D_{i-1}$。

当 $D_i\ne D_{i-1}$ 时，$S_i\ne S_{i-2}$，此时 $D_i\ne D_j$。

于是我们线性扫一遍，统计答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
typedef long long ll;
const int N=2e6+5;
ll t,n,ans;
char s[N];
int main(){
	cin>>t;
	while(t--){
		scanf("%lld%s",&n,s+1);
		ans=1;
		for(int i=3;i<=n;i++)
			if(s[i-2]!=s[i])
				ans++;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

