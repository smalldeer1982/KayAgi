# [ABC386C] Operate 1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc386/tasks/abc386_c

**この問題は F 問題 (Operate K) の部分問題であり、 $ K=1 $ です。**  
 **F 問題に正解するコードをこの問題に提出することで、この問題に正解できます。**

文字列 $ S $ に対して以下の操作を $ 0 $ 回以上 $ K $ 回以下行って、文字列 $ T $ と一致させられるか判定してください。

- 次の $ 3 $ 種類の操作のうちひとつを選択し、実行する。
  - $ S $ 中の (先頭や末尾を含む) 任意の位置に、任意の文字を $ 1 $ つ挿入する。
  - $ S $ 中の文字を $ 1 $ つ選び、削除する。
  - $ S $ 中の文字を $ 1 $ つ選び、別の $ 1 $ つの文字に変更する。

## 说明/提示

### 制約

- $ S,T $ は英小文字からなる長さ $ 1 $ 以上 $ 500000 $ 以下の文字列
- $ \color{red}{K=1} $
 
### Sample Explanation 1

`abc` の $ 2 $ 文字目の `b` を `g` に置き換えることで、 `abc` を $ 1 $ 回の操作で `agc` に変換できます。

### Sample Explanation 2

$ 1 $ 回の操作では `abc` を `awtf` に変換できません。

### Sample Explanation 3

`abc` の $ 2 $ 文字目の `b` を削除することで、 `abc` を $ 1 $ 回の操作で `ac` に変換できます。

### Sample Explanation 4

`back` の $ 1 $ 文字目と $ 2 $ 文字目の間に `l` を挿入することで、 `back` を $ 1 $ 回の操作で `black` に変換できます。

### Sample Explanation 5

初めから $ S=T $ である場合もあります。

## 样例 #1

### 输入

```
1
abc
agc```

### 输出

```
Yes```

## 样例 #2

### 输入

```
1
abc
awtf```

### 输出

```
No```

## 样例 #3

### 输入

```
1
abc
ac```

### 输出

```
Yes```

## 样例 #4

### 输入

```
1
back
black```

### 输出

```
Yes```

## 样例 #5

### 输入

```
1
same
same```

### 输出

```
Yes```

## 样例 #6

### 输入

```
1
leap
read```

### 输出

```
No```

# 题解

## 作者：zsq9 (赞：4)

[AC 记录](https://www.luogu.com.cn/record/196839373)

## 思路

首先判断如果 $len_a-len_b>1$ 就直接输出 `No` 在分别讨论 $len_a>len_b$ 和 $len_a<len_b$ 的情况 如果 $len_a>len_b$ 就是删除了一个字符，我们先找到删除了字符的地方，然后就比较这个序列当前这个数和另一个序列当前这个数前面的数，如果不一样就输出 `No`。 如果 $len_a>len_b$ 就是插入一个字符，我们就先找到插入了字符的地方，然后就比较这个序列当前这个数前面的数和另一个序列当前这个数，如果不一样就输出 `No`。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a,mz3=0;
string b,c;
bool mz2=0,mz1=0,xmz2=0,xmz1=0;
int main(){
	cin>>a>>b>>c;
	if((int)(b.size()-c.size())>=2||int(c.size()-b.size())>=2){
	   cout<<"No";
   	 return 0;
	}
	if(b.size()>c.size())mz2=1;
	else if(b.size()<c.size())mz1=1;
	for(int i=0;i<b.size();i++){
		if(xmz2==1){
			if(i!=(b.size()-1)){
				if(b[i]!=c[i-1]){
					cout<<"No";
					return 0;	
				}
			}
		}else if(xmz1==1){
			if(b[i]!=c[i+1]){
				cout<<"No";
				return 0;	
			}
		}else if(b[i]!=c[i]){
			if(mz2==1){
				xmz2=1;
			}else if(mz1==1){
				xmz1=1;
				if(b[i]!=c[i+1]){
					cout<<"No";
					return 0;
				}
			}else{
				mz3++;
				if(mz3>1){
					cout<<"No";
					return 0;
				}
			}
		}
	}
	cout<<"Yes";
return 0;
}
```

---

## 作者：_anll_ (赞：3)

简单模拟题，但为什么打这道的时候莫名其妙电脑死机。
## 思路
显然可以分成四种情况讨论。

- 当 $s=t$ 时，直接输出 `Yes`。
  
- 当 $len_s$ 与 $len_t$ 之间的差值 $>1$，直接输出 `No`。
- 当 $len_s=len_t$ 时，遍历字符串并记录 $s[i]\neq t[i]$ 的次数，若 $>1$ 输出 `No`，否则输出 `Yes`。
- 发现删除 $s$ 的字符相当于给 $t$ 在对应位置添加一个字符，所以其实它们本质是一样的。不妨钦定 $len_s>len_t$，遍历 $t$，定义 $x$，若 $s[x]\neq t[i]$ 就记录次数并增加 $x$。最后若次数 $>1$ 输出 `No`，否则输出 `Yes`。

## 代码
赛时代码丑得惨不忍睹，凑活看。
```cpp
#include<iostream>
#define int long long
using namespace std;
int t,n1,n2;
string s1,s2;
void solve1(){
	int x=1,tot=0;
	for(int i=1;i<=n2;i++){
		while(x<=n1&&s1[x]!=s2[i])
			tot++,x++;
		if(x>n1) break;
		if(s1[x]==s2[i]) x++;
	}
	cout<<(tot>1?"No\n":"Yes\n");
}
void solve3(){
	int tot=0;
	for(int i=1;i<=n1;i++)
		if(s1[i]!=s2[i]) tot++;
	cout<<(tot>1?"No\n":"Yes\n");
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	cin>>s1>>s2;n1=s1.size(),n2=s2.size(),s1='6'+s1,s2='6'+s2;
	if(s1==s2) return cout<<"Yes\n",0;
	if(n1-n2==1) solve1();
	else if(n2-n1==1){
		swap(s1,s2);swap(n1,n2);
    	solve1();
	}
	else if(n1==n2) solve3();
	else cout<<"No\n";
	return 0;
}
```

---

## 作者：Yuexingfei_qwq (赞：3)

模拟。  
## 思路  
分类讨论。  
首先，如果 $s = t$，那么直接输出`Yes`。  
其次，记 $n$ 为 $s$ 的长度，$m$ 为 $t$ 的长度：  
- 当 $|n - m| > 1$，说明长度差大于 $1$，输出`No`。
- 当 $n = m$ ，建立计数器 $cnt = 0$，遍历 $s$ 和 $t$ 的每个位置，如果同一位置上有不同字符，就将 $cnt + 1$；如果遍历后 $cnt > 1$，输出`No`，否则输出`Yes`。
- 当 $|n - m| = 1$，可以用两个桶来记两个字符串里每个字符出现的数量；接下来建立计数器 $cnt = 0$，遍历所有小写字母，将两个桶里每个字母的数量差记录在 $cnt$ 里 。如果遍历后 $cnt > 1$，输出`No`，否则输出`Yes`。
## AC CODE
赛时代码。  

```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a * b / __gcd(a, b)
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

int k;
str s, t;
std::map<char, int> cnts, cntt;

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> k >> s >> t;
	if (s == t) {
		cout << "Yes" << el;
		r0;
	}
	if (s.size() == t.size()) {
		int cnt = 0;
		F(i, 0, s.size() - 1, 1) {
			cnt += (s[i] != t[i]);
		}
		if (cnt <= 1) {
			cout << "Yes" << el;
		} else {
			cout << "No" << el;
		}
		r0;
	}
	if (abs((int)s.size() - (int)t.size()) > k) {
		cout << "No" << el;
		r0;
	}
	for (auto i : s) {
		cnts[i]++;
	}
	for (auto i : t) {
		cntt[i]++;
	}
	int cnt = 0;
	for (char i = 'a'; i <= 'z'; i++) {
		cnt += abs(cnts[i] - cntt[i]);
	}
	if (cnt <= 1) {
		cout << "Yes" << el;
	} else {
		cout << "No" << el;
	}
	r0;
}
```

[AC记录](https://atcoder.jp/contests/abc386/submissions/61165715)

---
完结~~不~~散花。

---

## 作者：_qumingnan_ (赞：2)

[题目跳楼机](https://www.luogu.com.cn/problem/AT_abc386_c)

# 正文开始

## 阅读理解

有两个字符串 $S$ 与 $T$，你可以进行以下操作：

- 改变其中 $1$ 个字符串的第 $i$ 个字符。
- 在其中 $1$ 个字符串的第 $i$ 个字符前添加 $1$ 个字符。
- 删除其中 $1$ 个字符串的第 $i$ 个字符。

在执行完 $1$ 次操作后，是否可以让两个字符串相同？

## 思路：

很明显，无论我们对哪个字符串进行修改都可以，所以我们就默认修改第 $1$ 个字符串。

根据这 $3$ 个操作我们可以将其分为 $3$ 种情况：

- 当 $\lvert S\rvert=\lvert T\rvert$ 时，对第 $1$ 个字符串进行第 $1$ 个操作。
- 当 $\lvert S\rvert<\lvert T\rvert$ 时，对第 $1$ 个字符串进行第 $2$ 个操作。
- 当 $\lvert S\rvert>\lvert T\rvert$ 时，对第 $1$ 个字符串进行第 $3$ 个操作。

注：规定 $\lvert S\rvert$ 位字符串 $S$ 的长度。

针对这 $3$ 种情况，我们皆可以采用找到第 $1$ 个不一样的地方进行修改的策略。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define itn int
using namespace std;
int n;
string S,T;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>S>>T;
	int lens=S.size(),lent=T.size();
	if(S==T){cout<<"Yes\n";return 0;}
	if(lens==lent){//第一种情况
		string s;
		bool b=1;
		for(int i=0;i<lens;i++)//对第一处进行修改，其它照抄
			if(S[i]!=T[i]&&b){s+=T[i];b=0;}
			else s+=S[i];
		if(s==T)cout<<"Yes\n";
		else cout<<"No\n"; 
		return 0;
	}
	if(lens<lent){//第二种情况
		string s;
		int i=0;
		for(;i<=lens;i++){//对第一处进行修改
			if(S[i]!=T[i]){s+=T[i];break;}
			s+=S[i]; 
		}
		for(;i<lens;i++)s+=S[i];//其它照抄
		if(s==T)cout<<"Yes\n";
		else cout<<"No\n";
		return 0;
	}
	if(lens>lent){//第三种情况
		string t;
		int i=0;
		for(;i<=lent;i++){//对第一处进行修改
			if(S[i]!=T[i]){t+=S[i];break;}
			t+=T[i];
		}
		for(;i<lent;i++)t+=T[i];//其它照抄
		if(S==t)cout<<"Yes\n";
		else cout<<"No\n";
		return 0;
	}
	return 0;
}
```

---

## 作者：songlll (赞：2)

# 分析

题目给了三种操作——插入、删除和替换。这些操作最多只能对字符串 $S$ 做一次。

不难发现，插入和删除都会导致 $S$ 的长度变化，且操作次数 $K=1$，所以 $S$ 的长度与 $T$ 的长度的差为 $1$。故此可以通过两字符串长度确定应该使用什么操作。

同时，为简化代码，我们可以将对 $S$ 添加字符视作对 $T$ 删除字符，并将 $S$ 与 $T$ 交换，判断能否通过对目标字符串删除字符得到已知字符。

剩下的就是简单的判断过程了。直接看代码吧。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int k;
	cin>>k;
	string a,b;//相当于题目中的S和T
	cin>>a>>b;
	if(abs((int)a.size()/*string.size()的返回值是unsigned类型，不能直接相减！！！！！*/-(int)b.size())==1){//需要进行删除或插入操作
		if(a.size()>b.size())swap(a,b);
		int f=0;
		for(int i=0;i<b.size();i++){
			if(a[i]!=b[i+f]){
				if(f){
					cout<<"No";
					return 0;
				}
				f=1;
			}
		}
		cout<<"Yes";
		return 0;
	}
	else if(a.size()==b.size()){//需要替换字符
		int cnt=0;//记录两字符串有多少字符不相同
		for(int i=0;i<a.size();i++){
			if(a[i]!=b[i])cnt++;
		}
		if(cnt<=1)cout<<"Yes";//如果两字符串完全相同也要输出Yes
		else cout<<"No";
		return 0;
	}
	cout<<"No";
}
```

---

## 作者：Drifty (赞：1)

### Solution

简单模拟题。

先判断长度，如果长度差 $>1$ 直接无解。

如果长度差 $=0$ 就逐个判断字符是否相同，如果超过两个字符不同就无解。

否则，长度差为 $1$，那么找到第一个不相同的地方，跳过这个地方继续比较，如果还有不相同，那么无解。

[My Submission.](https://atcoder.jp/contests/abc386/submissions/61160273)

---

## 作者：dg114514 (赞：1)

由于笔者习惯，将 $S$ 写为 $a$，$T$ 写为 $b$，且 $|a|<|b|$。\
一道模拟题。\
注意到只需进行 $1$ 次操作，来一个小分讨。

- 如果 $|b|-|a|>1$，显然不可能，输出 `No`。
- 否则，如果 $|a| \ne |b|$，令 $cnt=0$，$i$ 从 $1 \sim |b|$ 遍历。如果 $a_i \ne b_i$，则 $cnt$ 自增 $1$，把 $b_i$ 插入至 $a_i$ 和 $a_{i+1}$ 之间。（笔者使用的是 STL string 中的 `insert` 函数），如果 $cnt>1$，说明执行了多次操作，不符合题目，所以直接输出 `No`。如果 $cnt$ 一直都 $\le 1$，输出 `Yes`。（这里是判插入，之所以不判删除是因为插入跟删除其实一样）
- 如果 $|a|=|b|$，直接找不同字符，如果 $>1$ 输出 `No`，否则输出 `Yes`。\
注：不需要特判判 $a=b$ 是因为程序本来就能正常输出 `Yes`。
##  代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200010;
signed main(){
	int k;
	string a,b,t;
	cin>>k>>a>>b;
	if(a.size()>b.size())swap(a,b);
	if(a.size()!=b.size()){
		int cnt=0;
		for(int i=0;i<b.size();i++){
			t+=b[i];//insert太坑了，所以这里用 string
			if(a[i]!=b[i])cnt++,a.insert(i,t);//同上 
			if(cnt>1)puts("No"),exit(0);
			t.pop_back();//删除 
		}
	}else{
		int cnt=0;
		for(int i=0;i<b.size();i++){
			if(a[i]!=b[i])cnt++;
			if(cnt>1)puts("No"),exit(0);
		}
		puts("Yes");
	}
	return 0;
}
```

---

## 作者：sjh0626 (赞：0)

## 题意概括
判断是否有可能在 $0$ 到 $K$ 之间对字符串 $S$ 进行以下操作，使其与字符串 $T$ 相同。

- 从以下三个操作中选择一个并执行。
    - 在 $S$ 的任意位置（可能是开头或结尾）插入任意一个字符。
    - 从 $S$ 中删除一个字符。
    - 在 $S$ 中选择一个字符并替换为另一个字符。
## 思路分析
我们可以采用模拟的方式来解决此题。

首先，如果两个字符串相同，那毋庸置疑，肯定输出 `Yes`。

然后我们比较长度，若长度之差 $> k$，那么输出 `No`。

然后如果 $S$ 的长度 $< T$ 的长度，交换 $S$ 和 $T$。

接着我们比较它们的前缀子串，直到存在一个最小的 $i$，使得 $S_i \ne T_i$。

若它们长度不同，有两种情况：

- $S$ 从第 $i+1$ 位开始的后缀子串 $\ne T$ 从第 $i$ 位开始的后缀子串，则输出 `No`，因为我们在第 $i$ 位不相同的情况下，其他的一定相同。

- 反之，输出 `Yes`。

若长度相同，则一位一位比较，若不同字符的个数 $> 1$，则输出 `No`，反之输出 `Yes`。
## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
#define ll long long
using namespace std;
class FastIO{
	public:
	inline int read(){
		int x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
		return x*f;
	}
	FastIO &operator>>(int &x){
		x=read();
		return *this;
	}
};
FastIO qin;
int k,l1,l2,i,cnt;
string s,t;
map<char,int>m;
int main(){
	qin>>k;
	cin>>s>>t;
	if(s==t){
		cout<<"Yes";
		sjh0626s code;
	} 
	l1=s.size(),l2=t.size();
	if(abs(l1-l2)>1){
		cout<<"No";
		sjh0626s code;
	}
	if(l1<l2)swap(s,t);
	for(i=0;i<l2;i++){
		if(s[i]!=t[i])break;
	}
	if(l1!=l2&&s.substr(i+1)!=t.substr(i)){
		cout<<"No";
	}
	else if(s.substr(i+1)==t.substr(i)){
		cout<<"Yes";
	}
	else {
		for(int i=0;i<l2;i++){
			if(s[i]!=t[i])cnt++;
			if(cnt>1){
				cout<<"No";
				sjh0626s code;
			}
		}
		cout<<"Yes";
	}
	sjh0626s code;
}
```

---

## 作者：cqbzhzf (赞：0)

[vjudge中文翻译](https://vjudge.net/problem/AtCoder-abc386_c#author=GPT_zh)
### 思路
- 当两个字符串的长度差大于 $1$ 时，无解。
- 当两个字符串的长度差小于等于 $1$ 时，遍历字符串并统计 $a_i \neq b_j$ 的数量 $cnt$，当 $cnt>1$ 时无解，否则有解。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int k,n,m;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    cout.tie(0);
	cin>>k>>s>>t;
	n=s.size();m=t.size();
	s=' '+s;t=' '+t;
	if(abs(n-m)>1)
    {
		cout<<"No";
		return 0;
	}
	if(n<m)
    {
		int cnt=0;
		for(int i=1,j=1;i<=n;i++,j++)
        {
			if(s[i]!=t[j])
            {
				cnt++;
				j++;
			}
		}
		if(cnt>1)
			cout<<"No";
		else 
            cout<<"Yes";
	}
	if(n==m)
    {
		int cnt=0;
		for(int i=1;i<=n;i++)
        {
			if(s[i]!=t[i])
				cnt++;
		}
		if(cnt>1)
            cout<<"No";
		else 
            cout<<"Yes";
	}
	if(n>m)
    {
		int cnt=0;
		for(int i=1,j=1;i<=n;i++,j++)
        {
			if(s[i]!=t[j])
            {
				cnt++;
				i++;
			}
		}
		if(cnt>1)
			cout<<"No";
		else 
            cout<<"Yes";
	}
	return 0;
}
```

---

