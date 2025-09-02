# Unnatural Language Processing

## 题目描述

Lura 感到无聊，决定用五个字母 $\texttt{a}$、$\texttt{b}$、$\texttt{c}$、$\texttt{d}$、$\texttt{e}$ 创造一种简单的语言。该语言中有两类字母：

- 元音字母：$\texttt{a}$ 和 $\texttt{e}$，用 $\textsf{V}$ 表示。
- 辅音字母：$\texttt{b}$、$\texttt{c}$、$\texttt{d}$，用 $\textsf{C}$ 表示。

该语言中有两种音节类型：$\textsf{CV}$（辅音加元音）或 $\textsf{CVC}$（元音前后都有辅音）。例如，$\texttt{ba}$、$\texttt{ced}$、$\texttt{bab}$ 都是音节，但 $\texttt{aa}$、$\texttt{eda}$、$\texttt{baba}$ 不是。该语言中的一个单词由若干音节组成。Lura 已经写下了一个单词，但她不知道如何将其划分为音节。请你帮助她将单词划分为音节。

例如，给定单词 $\texttt{bacedbab}$，可以划分为 $\texttt{ba.ced.bab}$（点号 $\texttt{.}$ 表示音节分界）。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
8
bacedbab
4
baba
13
daddecabeddad
3
dac
6
dacdac
22
dababbabababbabbababba```

### 输出

```
ba.ced.bab
ba.ba
dad.de.ca.bed.dad
dac
dac.dac
da.bab.ba.ba.bab.bab.ba.bab.ba```

# 题解

## 作者：KidA (赞：5)

容易发现音节的划分不仅要求子串形如 $\texttt{CV}$ 或 $\texttt{CVC}$，并且接下来的两个字符也必须是 $\texttt{CV}$，不然会导致无法划分下去。

于是我们遍历字符串，找出所有满足上述条件的子串，记录需要输出 $\texttt{.}$ 的位置即可。

实现：

```cpp
int n; string s,ans,t="";
cin>>n>>s,ans=s,memset(x,-1,sizeof(x)),tot=0; //x是记录需要输出.的位置的数组
for(int i=0;i<s.size();i++){
	if(s[i]=='a'||s[i]=='e') s[i]='V';
	else s[i]='C';
}
for(int i=0;i<s.size();i++){
	t+=s[i];
	if((t=="CV"||t=="CVC")&&(s[i+1]=='C'&&s[i+2]=='V')) x[++tot]=i,t="";
}
for(int i=0,j=1;i<ans.size();i++){
	cout<<ans[i];
	if(i==x[j]) cout<<'.',j++;
}
cout<<'\n';
```

---

## 作者：wsx248 (赞：2)

不妨设元音为 $1$，辅音为 $0$。

则原序列可以转化成这样的一些形式：`01`、`010`、`0101`、`01001`。

不难看出，如果连续两个位置是 `0`，则第一个 `0` 后面需要分割；其他情况下都可以直接按照 `01` 的方式分割小节。

定义 $g_i$ 为转化后的 `01` 序列，为了防止 `010` 这种情况出现在结尾导致分割出错，标记 $g_{n+1}=0$。

```
#include<iostream>
#include<cmath>
using namespace std;

const int N = 2e5+5;
int g[N];
char s[N];

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n>>s+1;
		for(int i=1;i<=n;i++)
		{
			if(s[i]=='a' || s[i]=='e')
				g[i] = 1;
			else
				g[i] = 0;
		}
		g[n+1] = 0;
		cout<<s[1]<<s[2];
		for(int i=3;i<=n;i++)
		{
			if(g[i]==0 && g[i+1]==1)
			{
				cout<<"."<<s[i]<<s[i+1];
				i++;
			}
			else if(g[i]==0 && g[i+1]==0)
				cout<<s[i];
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：_fallen_leaves_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1915D)

## 思路：
如果这个字符串的一位是元音字母，就有两种方案，
- 如果后面两位都是辅音字母，就输出辅元辅结构。
- 否则就输出辅元结构，但是要防止这个元音字母在后两位，如果在后两位，就会多输出点，在倒数第二位，就不是输出辅元结构，而是输出辅元辅结构，如果在最后一位，会在末尾多输出点，所以这两种情况要考虑一下。

贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
	cin>>t;
	while(t--)
	{
		int n;
		string s;
		cin>>n>>s;
		for(int i=0;i<s.size();i++)
		{
			cout<<s[i];
			if((s[i]=='a'||s[i]=='e')&&(s[i+1]=='b'||s[i+1]=='c'||s[i+1]=='d')&&(s[i+2]=='b'||s[i+2]=='c'||s[i+2]=='d'))
			{
				cout<<s[i+1]<<".";
				i++;
			}
			else if((s[i]=='a'||s[i]=='e')&&i!=s.size()-2&&i!=s.size()-1) cout<<".";
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：liangjindong0504 (赞：1)

### 题意简述
有一个国家，只用 ```a b c d e``` 来表示单词。其中，```a e``` 是元音字母，```b c d``` 是辅音字母。

而这个国家的音节有两种构成方式：辅元辅（如 ```dab```），辅元（如 ```ca```）。

现在，有个人给了你几个单词及它们的长度，需要让你将它们的音节用 ```.``` 隔开。数据保证有解。

**注意有多组数据。**
### 大致思路
首先，关注到**数据保证有解**。因此，结尾一定是一个完整的音节。于是，可以先预处理出结尾音节（不然放入循环中最后会有 ```.``` 输出。

判断结尾是什么音节：判倒数第二个字符是元音还是辅音即可。
```cpp
if(str[str.size()-1]=='a'||str[str.size()-1]=='e') len=str.size()-2;
else len=str.size()-3;
```
不过可以通过用 $n$ 来代替，代码更短。

接下来，如果有两个辅音字母相连，则必须在它们之间断开（每个音节都没有两个辅音字母相连）。
```cpp
if((str[i]=='b'||str[i]=='c'||str[i]=='d')&&(str[i+1]=='b'||str[i+1]=='c'||str[i+1]=='d')){
	cout<<str[i]<<".";
}
```
最后，如果上面这个条件也不满足且前一个字符为远因字母，那么将出现：元辅元，必须在第一个“元”后断开。
```cpp
else{
	if(str[i-1]=='a'||str[i-1]=='e') cout<<"."<<str[i]; 
	else cout<<str[i];
}
```
这里还有一个隐藏信息：由于没有 ```str[-1]```（即 ```str[0-1]```） 这种东西，因此必须在一开始就输出第一个字符。

完整代码就不贴了，建议评橙。

---

## 作者：DrAlfred (赞：0)

摘要：字符串，模拟

[传送门：https://www.luogu.com.cn/problem/CF1915D](https://www.luogu.com.cn/problem/CF1915D)

## 题意

定义 $ \texttt{a} $ 和 $ \texttt{e} $ 为元音，记作 $ \texttt{V} $。

定义 $ \texttt{b} $，$ \texttt{c} $ 和 $ \texttt{d} $ 为辅音，记作 $ \texttt{C} $。

定义 $ \texttt{CV} $ 或 $ \texttt{CVC} $ 的字母组合为一个音节。现在给定一个未划分音节的单词，保证按照上述划分方法有唯一分法。求这个单词的划分（分隔处用 `.` 表示）。

## 分析思路

如果遇到了一个 $ \texttt{V} $，则需要考虑是否结束这个音节。

如果这个字母后面的第二个字母是一个 $ \texttt{C}$，则代表当前音节是 $ \texttt{CVC} $ 类型的，应当在下一个字母后面输出 `.`。

否则，代表当前音节是 $ \texttt{CV} $ 类型的，应当这个字母后面输出 `.`。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
inline int tp(char x) {
    return x == 'a' || x == 'e' ? 1 : 2;
}   // 1 代表 V, 2 代表 C
char c[N];
int t, n, tg; // tg 代表下一个输出句号的位置的标记
inline void solve(void) {
    cin >> n >> (c + 1);
    for (int i = 1; i <= n; i++) {
        cout << c[i];
        if (i == tg) cout << '.', tg = 0;
        if (i >= n - 1) continue;
        if (tp(c[i]) == 1) {
            if (tp(c[i + 2]) == 2) {
                tg = i + 1;
            } else {
                cout << '.';
            }
        }
    }
    cout << '\n';
}

int main(int argc, char const *argv[]) {
    cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：indream (赞：0)

## CF1915D Unnatural Language Processing 题解
[CF](https://codeforces.com/contest/1915/problem/D) | [洛谷](https://www.luogu.com.cn/problem/CF1915D) | [AC](https://codeforces.com/contest/1915/submission/239310850)
### 思路
可以用队列实现。

可以维护队头下标、队尾下标，如果队列中有至少 $4$ 个字母，就**讨论最后一个字符**：如果是元音，说明是 $\text{CV+CV(C)}$；否则是 $\text{CVC+CV(C)}$。每种情况输出已经确定的字符，别忘了打印 `.`，然后将队头下标增加对应数字即可。这样可以保证其正确性。注意最后要把队列剩下的内容输出。

时间复杂度 $O(Tn)$，可以通过此题。具体实现见代码。
### 代码
~~丑陋赛时代码，勿喷~~
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,tail,head,sz;
char Q[200005];
char a,tmp1,tmp2,tmp3,tmp4;
int main(){
    scanf("%d\n",&t);
    while(t--){
        scanf("%d\n",&n);
        tail=0;head=0;sz=0;
        for(int i=0;i<n;i++){
            a=getchar();
            Q[tail++]=a;++sz;
            if(sz>=4){
                tmp1=Q[head++];--sz;
                tmp2=Q[head++];--sz;
                tmp3=Q[head];
                tmp4=Q[head+1];
                putchar(tmp1);
                putchar(tmp2);
                if(tmp4!='a'&&tmp4!='e'){
                    ++head;
                    --sz;
                    putchar(tmp3);
                }
                putchar('.');
            }
        }
        for(int i=head;i<sz+head;i++)
            putchar(Q[i]);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：ThySecret (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1915D)

## 题目大意

给定一个只有五个字母的字符串，拆分成特定的音节并且输出。

## 解题思路

通过题目可以知道，两种音节分别为 $\texttt{CV}$ 和 $\texttt{CVC}$。两种音节不同在于他们的后缀不同，如果正向搜寻，那么需要分类讨论，所谓**正难则反**，因此我们可以逆序遍历求解答案。

定义一个 `vector` 数组，将字母和 `.` 加入进去，最后翻转输出即可（由于最后一个字符一定是 `.`，所以从第二个开始遍历）

## AC Code

```c++ 
// Problem: D. Unnatural Language Processing
// Contest: Codeforces - Codeforces Round 918 (Div. 4)
// URL: https://codeforces.com/contest/1915/problem/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
// #define int long long
const int INF = 0x3f3f3f3f;

const int N = 2e5 + 9;

char s[N], ans[N];
vector<char> vc;

void solve()
{
    vc.clear();
    int n; cin >> n;
    cin >> s + 1;
    for (int i = 1; i <= n; i ++)
    {
        if (s[i] == 'a' || s[i] == 'e') ans[i] = 'V';
        else ans[i] = 'C';
    }
    cout << '\n';
    for (int i = 1; i <= n; i ++) cout << ans[i];
    cout << '\n';*/
    
    for (int i = n; i >= 2; i --)
    {
    	if (ans[i] == 'C') 
    	{
    	    vc.push_back(s[i]);
    	    vc.push_back(s[i - 1]);
    	    vc.push_back(s[i - 2]);
    	    vc.push_back('.');
    	    i -= 2;
    	}
    	else
    	{
    	    vc.push_back(s[i]);
    	    vc.push_back(s[i - 1]);
    	    vc.push_back('.');
    	    i --;
    	}
    }
    reverse(vc.begin(), vc.end());
    for (int i = 1; i < vc.size(); i ++) cout << vc[i];
    cout << '\n';
}

signed main()
{
	// ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T; cin >> T;
    while (T --) solve();
	return 0;
}
```

以上是丑陋的赛事代码，直接用数组存也可以，仅供参考。

---

## 作者：Natori (赞：0)

>[CF1915D Unnatural Language Processing](https://www.luogu.com.cn/problem/CF1915D)

我们抓住“保证有解”这个条件。如果有解，那么结尾处必然存在完整的音节。因此从后向前找完整的音节即可。

一个方法是把元音和辅音分别标记出来，然后就比较好判断。

代码写得比较丑，甚至用了 ```stack```。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
const int N=2e5+8;
int n;
char str[N];
int a[N];
void mian(){
	for(int i=1;i<=n;i++)
		a[i]=0;
	cin>>n;stack<char> stc;
	cin>>(str+1);
	for(int i=1;i<=n;i++){
		if(str[i]=='a'||str[i]=='e')
			a[i]=2;
		else
			a[i]=1;
	}
	for(int i=n;i>=1;i--){
		if(a[i]==2){
			stc.push(str[i]);
			stc.push(str[i-1]);
			i-=1;
		}
		else{
			stc.push(str[i]);
			stc.push(str[i-1]);
			stc.push(str[i-2]);
			i-=2;
		}
		if(i!=1)
			stc.push('.');
	}
	while(stc.empty()==0){
		cout<<stc.top();
		stc.pop();
	}
	cout<<'\n';
}
bool Mend;
int main(){
//	File_Work();
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cerr<<fixed<<setprecision(3)<<(&Mbegin-&Mend)/1048576.0<<" MB\n\n\n";
	int testnum=1;
	cin>>testnum;
	while(testnum--)
		mian();
	cerr<<"\n\n\n"<<fixed<<setprecision(0)<<1e3*clock()/CLOCKS_PER_SEC<<" ms";
	return 0;
}
```

---

