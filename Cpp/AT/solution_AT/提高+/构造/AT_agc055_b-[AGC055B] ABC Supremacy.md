# [AGC055B] ABC Supremacy

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc055/tasks/agc055_b

`A`, `B`, `C` からなる長さ $ N $ の文字列 $ S $ が与えられます。あなたは、次の操作を何回でも行うことができます。

- $ S_iS_{i+1}S_{i+2} $ が `ABC`, `BCA`, `CAB` のいずれかに等しいような $ 1\ \le\ i\ \le\ N-2 $ を任意に選ぶ。そして、その三文字を `ABC`, `BCA`, `CAB` のいずれかで置換する。

例えば、文字列 `AABC` に対して、以下の変換を行うことができます。

- `AABC` $ \to $ `ABCA` $ \to $ `BCAA`

上記の操作を有限回行うことで（$ 0 $ 回でもよい）、文字列 $ S $ から文字列 $ T $ を得ることが可能か判定してください。

## 说明/提示

### 制約

- $ 3\le\ N\ \le\ 5\cdot\ 10^5 $
- $ S $ は、`A`, `B`, `C` からなる長さ $ N $ の文字列である。
- $ T $ は、`A`, `B`, `C` からなる長さ $ N $ の文字列である。

### Sample Explanation 1

これは問題文で説明した例です。

## 样例 #1

### 输入

```
4
AABC
BCAA```

### 输出

```
YES```

## 样例 #2

### 输入

```
4
ABCA
BCAB```

### 输出

```
NO```

# 题解

## 作者：LeBao2023 (赞：3)

[原题链接](https://www.luogu.com.cn/problem/AT_agc055_b)

~~这道题是一道十分恶心的题，主要是赛时的题目描述看了我很久，十分毒瘤。~~

简要题意：

给定两个长度为 $n$ 的字符串 $a,b$。

你可以进行若干次以下操作：若 $a$ 中的一个子串为 ABC，BCA 或 CAB，那么可以将这个子串替换为 ABC，BCA 或 CAB。

求能否将 $a$ 变成 $b$，输出 YES 或 NO。

------------

我们容易发现变换可逆。我们可以将 $a$ 转换成 $x1$，$b$ 使用同种方法转换成 $x2$，看 $x1$ 是否等于 $x2$。

我们看见 ABC 的转换，就可以向 ABC 思考。

设 X 为任意字母，我们发现 ABCX 可以转换成 XABC。

证明如下：

1. X 为 A，ABCA $\to$ AABC

2. X 为 B，ABCB $\to$ BCAB $\to$ BABC

3. X 为 C，ABCC $\to$ CABC

因为变换可逆，所以 XABC 可以转换成 ABCX，ABC 可以在序列里任意移动，同理，BCA 和 CAB 也可以移动，删除也没有问题。

我们可以把 $a,b$ 中的所有 ABC 删除，得到 $x1,x2$，比较 $x1,x2$ 是否相等，可以得出结果。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string bx(string a)
{
	stack<int> s;a=" "+a;
	for(int i=1;i<=n;i++)
	{
		s.push(a[i]-'A');
		if(s.size()>=3)
		{
			int u=s.top();s.pop();
			int v=s.top();s.pop();
			if(s.top()==(u+1)%3&&u==(v+1)%3&&v==(s.top()+1)%3)
			{
				s.pop();
			}
			else
			{
				s.push(v);s.push(u);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		a[i]=5;
	}
	for(int i=s.size();i>=1;i--)
	{
		a[i]=s.top();s.pop();
	}
	return a;
}
string s;
int main()
{
	cin>>n>>s;
	s=bx(s);
	int q=1;string a;
	while(q--)
	{
		cin>>a;
		a=bx(a);
		int flag=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=s[i])
			{
				flag=1;
				break;
			}
		}
		if(flag==1)
		{
			cout<<"NO\n";
		}
		else
		{
			cout<<"YES\n";
		}
	}
}
```

时间发杂度：$O(n)$。

---

## 作者：include13_fAKe (赞：2)

## 前言

萌新的第一篇 AGC 题解。

## 题意

您会得到一个长度为 $N$ 的字符串 $S$，由 $\texttt A$、$\texttt B$ 和 $\texttt C$ 组成。您可以执行以下操作任意次数：

选择满足 $1\le i \le N-2$ 的任何一个 $i$，使其满足 $S_iS_{i+1}S_{i+2}$ 为 $\texttt{ABC}$ 或 $\texttt{BCA}$ 或 $\texttt{CAB}$。并将 $S_iS_{i+1}S_{i+2}$ 替换为 $\texttt{ABC}$ 或 $\texttt{BCA}$ 或 $\texttt{CAB}$。

按照以上规则，你可以如下手玩字符串 $\texttt{AABC}$：

- $\texttt{AABC}\to\texttt{ABCA}\to\texttt{BCAA}$。

请判断能否将字符串 $S$ 转化为字符串 $T$。如果能，输出 $\texttt{YES}$，如果不能，输出 $\texttt{NO}$。

$3\le N\le 5\times 10^5$。

## 思路

首先，这个操作是具有**可逆性**的。

以下用字符 $\texttt{?}$ 代表任意字符串。

通过手玩可以猜出结论：对于字符串 $\texttt{?ABC}$，一定可以转化为 $\texttt{ABC?}$。（前后 $\texttt{?}$ 所代表的字符串完全相同）

于是出现了一种全新的思路。

每当出现一个 $\texttt{ABC}$ 或者 $\texttt{BCA}$ 或者 $\texttt{CAB}$ 时，就将其从原字符串中删除，再判断两字符串是否**完全相同**即可。

注意本题的数据范围（笔者在这里调了很久没找到错因）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[5*114514],b[5*114514];
int ptr1=0,ptr2=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		int x=c-'A'+1;
		a[++ptr1]=x;
		if(ptr1>=3){
					if(a[ptr1-2]==1&&a[ptr1-1]==2&&a[ptr1]==3)	ptr1-=3;
			else	if(a[ptr1-2]==2&&a[ptr1-1]==3&&a[ptr1]==1)	ptr1-=3;
			else	if(a[ptr1-2]==3&&a[ptr1-1]==1&&a[ptr1]==2)	ptr1-=3;
		}	
	}
	for(int i=1;i<=n;i++){
		char c;
		cin>>c;
		int x=c-'A'+1;
		b[++ptr2]=x;
		if(ptr2>=3){
					if(b[ptr2-2]==1&&b[ptr2-1]==2&&b[ptr2]==3)	ptr2-=3;
			else	if(b[ptr2-2]==2&&b[ptr2-1]==3&&b[ptr2]==1)	ptr2-=3;
			else	if(b[ptr2-2]==3&&b[ptr2-1]==1&&b[ptr2]==2)	ptr2-=3;
		}	
	}
//	if(ptr1!=ptr2){
//		puts("NO");
//		return 0;
//	}
	for(int i=1;i<=ptr1;i++){
//		cout<<a[i]<<' '<<b[i]<<endl;
		if(a[i]!=b[i]){
			puts("NO");
			return 0;
		} 
	}
	puts("YES");
	return 0;
}
```

---

## 作者：Jsxts_ (赞：2)

由于只是求能否达成，并且操作可逆，可以考虑把两个串同时向一种比较特殊的串转化，最后如果是一样的就代表可行。

考虑一个字符串 `?ABC`，一定可以通过某些操作使其变为 `ABC?`。所以我们可以考虑把 s 和 t 都转换成前缀尽有可能多连续 `ABC` 的字符串，判断这两个字符串是否相等即可（连续的 `BCA` 和 `CAB` 也都转成 `ABC` 方便比较）。

代码就不给了，都很简单，只是考察思维。

---

## 作者：M_CI (赞：1)

### 前言

今天联考 T2 是这道，又成唐氏了，巨简单题又没想出正解。

### 思路

由题面，我们知道本题中字符串的每一个长成 $\texttt{ABC}, \texttt{BCA}$ 或 $\texttt{CAB}$ 其一的子串都是可以换成另两个其一。

先给大家看三个小转换：

$\texttt{AABC} \rightarrow \texttt{ABCA}$

$\texttt{BABC} \rightarrow \texttt{BCAB} \rightarrow \texttt{ABCB}$

$\texttt{CABC} \rightarrow \texttt{ABCC}$

发现了什么？

没错，我们可以用题面中的转换方式将任何形如 $\texttt{XABC}$ 的串转换为 $\texttt{ABCX}$ 的形式。

这时，我们的脑海里自然的出现一个思路：我们尽量多的把 $\texttt{ABC}$“推”到 $S$ 和 $T$ 的前面，比较推完后的串是否相等就可以了。

（注：上文中的 $\texttt{ABC}$ 均可用 $\texttt{BCA}$ 或 $\texttt{CAB}$ 代替，因为我们可以通过一次交换将 $\texttt{BCA}$ 或 $\texttt{CAB}$ 换为 $\texttt{ABC}$，这显然是等价的。）

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace rab {
	const string d[3]={"ABC","BCA","CAB"};
	
	int n,k;
	string s,t,p,q,g;
	
	void init () {
		for (int i=0;i<n;i++) {
			p+=s[i];
			if (p.size ()>=3) {
				g=p.substr (p.size ()-3,3);
				for (int j=0;j<3;j++)
					if (g==d[j]) {
						p.pop_back ();
						p.pop_back ();
						p.pop_back ();
						break;
					}
			}
		}
	}
	
	void solve () {
		cin>> t;
		q.clear ();
		for (int i=0;i<n;i++) {
			q+=t[i];
			if (q.size ()>=3) {
				g=q.substr (q.size ()-3,3);
				for (int j=0;j<3;j++)
					if (g==d[j]) {
						q.pop_back ();
						q.pop_back ();
						q.pop_back ();
						break;
					}
			}
		}
		if (p==q) cout<< "YES\n";
		else cout<< "NO\n";
		return ;
	}
	
	int main () {
		cin>> n>> s;
		k=1;
		init (); 
		while (k--) solve ();
		return 0;
	}
}

signed main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	return rab::main ();
}
```

### 后言

为什么联考最容易拿分的总是不是 T1！！！

---

## 作者：tZEROちゃん (赞：1)

可爱洛谷 AtCoder Remote Judge 寄了，难绷。


你注意到这个操作是可逆的，那你就把这两个串按照一个规则转化成另一个串，比较这两个串一不一样就行。

然后你手玩一下，形如 `?ABC` 的子串都能变成 `ABC?`。

那这样所有的 `ABC` 都可以被移到最前面，然后因为题目里的另外两个字符串也能转换成 `ABC`，我们一起把他扔到前面。

然后你判断一下这两个一不一样就行。

有一个好写的做法是，我们从前往后跑一下，每次往新字符串后面加一个字符，如果最后三个字符是可以变化的字符串，那就删掉最后三个。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i, l, r) for(auto i = (l); i <= (r); ++i)
#define _rep(i, l, r) for(auto i = (l); i < (r); ++i)

#define pb push_back
#define fi first
#define se second

#define i64 long long

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n; string s, t; 
  cin >> n >> s >> t;
  string S, T;
  _rep (i, 0, s.size()) {
    S += s[i], T += t[i];
    if (S.size() >= 3) {
      string tmp = "$$$";
      tmp[0] = S[S.size() - 3];
      tmp[1] = S[S.size() - 2];
      tmp[2] = S[S.size() - 1];
      if (tmp == "ABC" || tmp == "BCA" || tmp == "CAB") {
        S.pop_back();
        S.pop_back();
        S.pop_back();
      }
    }
    if (T.size() >= 3) {
      string tmp = "$$$";
      tmp[0] = T[T.size() - 3];
      tmp[1] = T[T.size() - 2];
      tmp[2] = T[T.size() - 1];
      if (tmp == "ABC" || tmp == "BCA" || tmp == "CAB") {
        T.pop_back();
        T.pop_back();
        T.pop_back();
      }
    }
  }
  if (S == T) cout << "YES\n";
  else cout << "NO\n";
  return ~~(0 ^ 0);
}
```

---

## 作者：Claire0918 (赞：0)

记 $d = \{\texttt{ABC}, \texttt{BCA}, \texttt{CAB}\}$。

我们注意到操作是可逆的，从而考虑将 $a$ 和 $b$ 都转化成一种更为简洁的形式来比较。

我们发现这一性质：对于任意的 $x \in \{\texttt{A}, \texttt{B}, \texttt{C}\}$ 和 $y \in d$，总可以将 $xy$ 转化为 $yx$。

换而言之，如果有一个字母在一个 $y \in d$ 前，我们总可以将其移动到 $y$ 后且不对其他位置造成影响。

我们于是想到可以将所有 $a$ 和 $b$ 在 $d$ 中的子串移动到最开头，再比较不能被移动的部分是否相等。这等价于删除所有在 $d$ 中的子串。我们将 $a$ 和 $b$ 经过这样的操作得到的字符串分别记作 $p$ 和 $q$。

特别指出，如果在一轮删除后剩余的子序列又重新组合出了新的在 $d$ 中的子串，我们仍然要将其删除。即我们的删除在字符串中仍然存在 $d$ 中的子串时就不能停止。

接下来给出这种做法的正确性证明。

首先是充分性，即如果 $p = q$，那么 $a$ 就可以转化为 $b$。这运用操作的可逆性质即可证明。具体来说，如果二者在这种做法后都得到了 $p$，那么实际上可以先将 $a$ 转化为 $p$，再将 $p$ 转化为 $b$。

然后是必要性，即如果 $p \neq q$，那么 $a$ 就不可以转化为 $b$。运用反证法。假设 $p \neq q$ 且 $a$ 可以转化为 $b$，我们不妨直接将 $a$ 转化为 $b$，再对两个字符串进行做法中的操作。显然同一个字符串只能得到相同的结果，所以这样得到的 $p$ 和 $q$ 是相等的，与题设矛盾，从而假设错误，命题得证。

综上所述，我们完整地证明了该做法的正确性。$\square$

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const string temp[3] = {"ABC", "BCA", "CAB"};

int n;
string s, t, base, now;

inline void change(string s, string& res){
    res.clear();
    for (int i = 0; i < n; i++){
        res += s[i];
        for (int j = 0; j < 3; j++){
            if (res.size() >= 3 && res.substr(res.size() - 3, res.size()) == temp[j]){
                res.pop_back();
                res.pop_back();
                res.pop_back();
            }
        }
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(false);
    cin>>n>>s>>t;
    change(s, base);
    change(t, now);
    cout<<(base == now ? "YES" : "NO")<<endl;

return 0;
}
```

---

## 作者：AKPC (赞：0)

真是道好题啊。

两个性质：

1. 操作可逆。

因为 `ABC`、`BCA`、`CAB` 之间是可以相互转化的，故显然该性质成立。

2. `ABCX` 和 `XABC` 之间是可以相互转化的，换句话说，`X` 前方或后方若存在 `ABC`，则可以越过它们往前放。其中 `X` 可以代表任何一个在 `A`、`B`、`C` 以内的字符。

你可以考虑枚举 `X` 代表的字符并考虑如何操作 `ABCX` 到 `XABC`：

- `ABCA`：将后面的 `BCA` 改为 `ABC`，达到 `AABC`。
- `ABCB`：将前面的 `ABC` 改为 `BCA`，达到 `BCAB`，然后将后面的 `CAB` 改为 `ABC`，达到 `BABC`。
- `ABCC`：将前面的 `ABC` 改为 `CAB`，达到 `CABC`。

由于操作可逆，故 `XABC` 也能转化到 `ABCX`。

考虑把 $s,t$ 中的 `BCA` 和 `CAB` 都全部转化为 `ABC`，然后把所有的 `ABC` 往前移动。因为操作可逆，所以可以对两个字符串都进行操作。最后判断一下是否相等即可。

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

聪明题。

考虑把两个串都转化为某种特殊形态。

发现所有的形如 `ABCX` 的串都一定可以转化为 `XABC` 形状，手玩可以证明，所以我们可以把所有题目给定的三种串都放到串的最后面。

由于题目给定的三种串可以相互转化，所有的给定串都可以转化为相同的，所以我们无脑将其删掉。

对于剩下的无法转化的串，若相等则两串可以相互转化，否则不行。

实现上模拟过程，每遇到一个给定串就删掉即可。

### $\text{code}$

```cpp
int n;

string s1,s2;

string change(string s){
	string kk="";
	for(int i=0;i<n;i++){
		kk+=s[i];
		if(kk.size()>=3){
			string bk="";
			for(int j=kk.size()-3;j<(int)kk.size();j++){
				bk+=kk[j];
			}
			if(bk=="ABC"||bk=="BCA"||bk=="CAB"){
				kk.erase(kk.size()-3);
			}
		}
	}
	return kk;
}

void solve(){
	n=read();
	cin>>s1>>s2;
	string a=change(s1),b=change(s2);
	if(a==b){
		puts("YES");
		return ;
	}
	else{
		puts("NO");
		return ;
	}
	return ;
}
```

---

## 作者：Forever_LYD (赞：0)

一道蓝题，思维含量很高，但是代码实现要求低，理解也就非常好写了。

其他题解也都提到可逆，确实这个词在这道题里也是至关重要的决策。

所以不难发现 $\texttt{cab}$ 和 $\texttt{bac}$ 都可以转化的 $\texttt{abc}$ 的形式。

都可以相互转化。

关于给定的两个字符串 $a$ 和 $b$ 中，又基于可逆，再结合样例，我们就可以发现,任何一个 $\texttt{xabc}$ 也都可以转化为 $\texttt{abcx}$ 的形式。

那么我们可以很轻松的把这个整体移到最前面不就行了？接着比较两个字符串后面的字符是否相等即可。

代码实现起来就很简单了，注意如果直接把所有形如上述的字符移到最前面，可能会爆，所以像另一篇题解说的一样，直接将其删除即可。

---

## 作者：HEzzz (赞：0)

## 前言
 
这是我第一次写 AGC 比赛的题解。

## 分析

#### 结论：
>我们发现如果字符串 $s$ 能通过规则变成字符串 $t$，那么 $s$ 能变成的字符串，$t$ 也可以变成相同的字符串。

这也是挺好理解的，我们只需手玩多一点的数据即可，或者你可以大胆想象。

根据以上结论，我们只需要把两个字符串实施一下几点。

- 从头到尾依次把字符串存入一个一开始为空串的字符串中。

- 当这个字符串的长度不小于了 $3$ 时，立即判断这个字符串的末三位能否依题意改变，如果能，则把这个字符串所能改变的末三位去掉。

最后，判断一下由 $s$ 生成的字符串是否和由 $t$ 生成的字符串相同，若相同，输出 ```YES```,否则输出 ```NO```。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int n;
pair<int,string> change(string s)
{
	int now=0;
	string tmp=""; 
	for(int i=0;i<n;i++)
	{
		tmp+=s[i];
		int m=tmp.size();
		if(m<=2)continue; 
		string t=tmp.substr(m-3,3);
		if(t=="ABC"||t=="BCA"||t=="CAB")
		{
			now++;
			tmp.pop_back(); tmp.pop_back(); tmp.pop_back();
		}
	}
	return make_pair(now,tmp);
}
int main()
{
	cin>>n;
	cin>>s>>t;
	if(change(s)==change(t))cout<<"YES\n";
	else cout<<"NO\n";
}
```


---

## 作者：MurataHimeko (赞：0)

操作可逆。

所以可以尝试将 $S, T$ 都通过某种规则变为同种形式，然后再判断是否相等即可。

进一步的，我们发现形如 ```XABC``` 的子串都可以变化为 ```ABCX```:

```
AABC->ABCA

BABC->BCAB->ABCB

CABC->ABCC

```

同时我们可以将所有的 ```BCA, CAB``` 都变为 ```ABC```，然后提到序列最前面。

然后再判断 $S$ 和 $T$ 是否相等即可。
 

---

## 作者：hfjh (赞：0)

# [AGC055B] ABC Supremacy 题解

## 题目描述

给定两个长度为 $n$ 的字符串 $a$，$b$。

你可以进行若干次以下操作：

- 若 $a$ 中的一个**子串**为 `ABC`，`BCA` 或 `CAB`，那么可以将这个子串替换为 `ABC`，`BCA` 或 `CAB`。

求能否将 $a$ 变成 $b$，输出 `YES` 或 `NO`。

## 解析

不难发现，我们可以根据一些变换将`ABC`，`BCA` 或 `CAB` 和单个字母 `A` 换位置。

具体操作如下：

$$
A \overline{ABC}\rightarrow \overline{ABC}A \\
B\overline{ABC}\rightarrow BCAB \rightarrow \overline{ABC}B\\
C\overline{ABC} \rightarrow \overline{ABC}C
$$

> `BCA` `CAB` 都可以转换成 `ABC`

我们可以把字符串 $a$，$b$ 所有的 `ABC`，`BCA` 或 `CAB` 移动到最前面，剩余部分如果一样就可以转换。

## 实现

我们不需要真的把所有的 `ABC`，`BCA` 或 `CAB` 移动到最前面，只需要将他们删除，再比对剩余串。

用 `vector` 实现比较方便。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
char ck[4][4]={{'0','0','0'},
{'A','B','C'},
{'B','C','A'},
{'C','A','B'}
};
int n,na,nb;
char a[N],b[N];
vector<char>q;
bool pd(int x){
	for(int i = 1; i <= 3; ++i)
		if(q[x] == ck[i][0] && q[x + 1] == ck[i][1] && q[x + 2] == ck[i][2])
			return 1;

	return 0;
}
void op(char x[],int &nx){
	q = vector<char>();
	for(int i = 0; i < n; ++i){
		q.push_back(x[i]);
		while(q.size() >= 3 && pd(q.size() - 3))
			q.pop_back();q.pop_back();q.pop_back();
            
	}
	nx = q.size();
	for(int i = 0;i < q.size(); ++i)
		x[i] = q[i];
}
void output(){
	if(na != nb){
		cout<<"NO"<<'\n';
		return ;
	}
	for(int i = 0;i < na; ++i){
		if(a[i] != b[i]){
			cout<<"NO"<<'\n';
			return ;
		}
	}
	cout<<"YES"<<'\n';
}
int main(){
	cin>>n>>a>>b;
	op(a,na);op(b,nb);
	output();
	return 0;
}
```

---

