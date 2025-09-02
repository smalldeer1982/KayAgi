# Decypher the String

## 题目描述

这是一个交互题。在与测试程序通信时，请记得刷新输出。你可以在 C++ 中使用 fflush(stdout)，在 Java 中使用 system.out.flush()，在 Python 中使用 stdout.flush()，在 Pascal 中使用 flush(output) 来刷新输出。如果你使用其他编程语言，请查阅其文档。你也可以参考关于交互题的指南：<https://codeforces.com/blog/entry/45307>。

给定一个由 $n$ 个小写拉丁字母组成的字符串 $t$。该字符串是通过如下方式加密得到的：最初，评测系统有一个由 $n$ 个小写拉丁字母组成的字符串 $s$。然后，他们对 $s$ 进行了不超过 $n$ 次（可能为零次）操作。第 $i$ 次操作用两个整数 $a_i$ 和 $b_i$（$1 \le a_i, b_i \le n$）表示，表示交换字符串中下标为 $a_i$ 和 $b_i$ 的两个字符。所有操作按顺序依次进行。例如，如果 $s$ 为 xyz，执行以下两次操作：$a_1 = 1, b_1 = 2$；$a_2 = 2, b_2 = 3$，那么第一次操作后当前字符串为 yxz，第二次操作后为 yzx，因此 $t$ 为 yzx。

你的任务是还原原始字符串 $s$。不幸的是，你无法获得关于操作序列的任何信息（你甚至不知道是否进行了操作）。但你可以对任意你想要的字符串（只要它只包含小写拉丁字母且长度为 $n$）执行同样的操作序列，并获得经过这些操作后的结果字符串。

你能否在不超过 $3$ 次询问的情况下，猜出原始字符串 $s$？

对于每个测试，字符串 $s$ 和交换操作序列都是固定的；交互器不会根据你的解法调整测试数据。

## 说明/提示

在样例中，测试用例如题面所述。参赛者第一次询问字符串 baa，被变换为 aab。第二次询问字符串 aba，被变换为 baa。第三次询问字符串 aab，被变换为 aba。参赛者可以由此推断出原始字符串 $s$ 是 xyz。

Hack 阶段说明：

在 Hack 阶段提交测试数据时，格式如下：

第一行是你猜测的字符串 $s$，由 $n \in [1, 10000]$ 个小写拉丁字母组成。

第二行是 $k$（$0 \le k \le n$）——操作序列的交换次数。

接下来 $k$ 行，每行两个整数 $a_i$ 和 $b_i$（$1 \le a_i, b_i \le n$），表示第 $i$ 次操作。

例如，样例测试数据如下：

xyz

2

1 2

2 3

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
yzx
aab
baa
aba```

### 输出

```
? baa
? aba
? aab
! xyz
```

# 题解

## 作者：_sys (赞：11)

本来都$AFO$了不想写题解了，但是这道题实在是太妙了，忍不住写几句。
Luogu现在还没搬，所以先写成非分类文章。

题意是现在有一个长度$\leq10000$的字符串和一个位置上的双射$f$，使得字符串$i$上的字符走到$f(i)$上来。

你有三次交互机会，每次给一个长度与原串相等的字符串，返回经过$f$后的字符串。

现在给你$f($原串$)$，求原串

我们考虑一下，$3,10000,26$有什么关系

发现$26^2<10000<26^3$

就考虑如何一次交互如何扩大$26$倍

我们可以通过以下方式

第一次:

$aaa...aaa(26*26)bbb...bbb(26*26)ccc...ccc(26*26)...$

我们称$26*26$个为一个大块

第二次:

$aaa...aaa(26)bbb...bbb(26)ccc...ccc(26)...$

我们称$26$个为一个小块

第三次:

$abcdefg...xyzabcdefg...xyz$

这样，对于一个位置i，第一次我们可以知道$f(i)$属于哪一个大块，第二次可以知道属于哪一个小块，第三次便可以知道属于哪里

当然还有另外一种方法，第一次使用26个字母循环，第二次使用25个，第三次23个，这样就可以知道$f(i) \mod 26/25/23$的值，再使用$CRT$合并即可

不过$26*25*23 < 15000 < 26^3 $

所以，如果$n=15000$第二个方法就不行

代码我只写了第一种方法的：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Maxn=10005;
int bel[Maxn],n;
string str,res,print;
char ans[Maxn];
int main()
{
	cin>>res;
	int siz=res.size();
	print="? ";
	char ch='a';
	for(int i=0;i<siz;i++)
	{
		print+=ch;
		if((i+1)%(26*26)==0) ch++;
	}
	cout<<print<<endl;
	cin>>str;
	for(int i=0;i<siz;i++)
		bel[i]+=(str[i]-'a')*26*26;
	ch='a';
	print="? ";
	for(int i=0;i<siz;i++)
	{
		print+=ch;
		if((i+1)%26==0) ch++;
		if(ch=='z'+1) ch='a';
	}
	cout<<print<<endl;
	cin>>str;
	for(int i=0;i<siz;i++)
		bel[i]+=(str[i]-'a')*26;
	ch='a';
	print="? ";
	for(int i=0;i<siz;i++)
	{
		print+=ch;
		ch++;
		if(ch=='z'+1) ch='a';
	}
	cout<<print<<endl;
	cin>>str;
	for(int i=0;i<siz;i++)
		bel[i]+=str[i]-'a';
	for(int i=0;i<siz;i++)
		ans[bel[i]]=res[i];
	printf("! %s",ans);
	fflush(stdout); 
	return 0;
}
```

---

## 作者：Saliеri (赞：4)

写这篇题解的初衷其实是觉得题解区的代码太难看了……

___

题目就是要让我们把作用在原字符串上的置换求出来。

很自然地我们可以有一个想法：如果我们的字符集是 $10^4$，那么直接使得询问字符串的每一位都不相同，我们就可以整个得到这个置换。

虽然本题的字符集只有 $26$，但是上面的思想还是可以沿用的——只不过有了一个问题：我们**不知道**这一次放了相同字符的位置**内部的置换关系**。

但是我们可以发现，这个过程是可以递归进行的——内部的位置关系可以通过又一次询问得到，然后分成更小的小段。因为 $26^3 = 17576 \ge 10^4$，所以我们可以保证三次之内出结果。

___

解法就到这里，接下来就是实现问题。

其实我们并不需要像上面说的一样递归地去构造询问串，有一种非常简单的想法是这样的：

我们将每个位置映射为一个 $3$ 位 $26$ 进制数，每一位分别塞进三个询问串的对应位置去。

然后我们会得到三个答案串，将每一个位置上的三个字符看做 $3$ 位 $26$ 进制数，它的值就是我们需要的东西：这个位置上现在的数原先在哪个位置。直接将 $s$ 每个字符映射到该去的地方即可。

代码：

```cpp
#include <cstdio>
#include <cstring>
const int maxn = 1e4+5,pw[] = {1,26,676,17576};
int n,qry[3][maxn];char s[maxn],t[3][maxn],ans[maxn];
int main(){
	scanf("%s",s),n = strlen(s);
	for(int _=0;_<3;++_){
		for(int j=0;j<n;++j)
			qry[_][j] = j%pw[_+1]/pw[_];
		printf("? ");
		for(int j=0;j<n;++j)putchar('a'+qry[_][j]);
		puts(""),fflush(stdout);
		scanf("%s",t[_]);
	}
	for(int i=0;i<n;++i){
		int pos = 0;
		for(int _=0;_<3;++_)
			pos += (t[_][i]-'a')*pw[_]; 
		ans[pos] = s[i];
	}
	return printf("! %s",ans),fflush(stdout),0;
}
```

---

## 作者：是个汉子 (赞：3)

#交互题。

这题需要一个很精妙的构造，所以写一篇题解来加深自己的理解。

### Solution

如果直接看见 $3$ 次机会和 $10000$ 的 $|s|$ 可能会很迷茫，但是还有一个 $26$ ，那我们就可以~~瞎~~写一个 $26^2<10000<26^3$ ，然后就到了精妙的构造了。

第一次机会：

$aaa...aaa(26*26)bbb...bbb(26*26)ccc...ccc(26*26)...$ 

每一个 $26*26$ 是大块

第二次机会：

$aaa...aaa(26)bbb...bbb(26)ccc...ccc(26)...$ 

每一个 $26$ 是小块

第三次机会：

$abcdefg...xyzabcdefg...xyz...$ 

这样对于变化后的串 $s’$ 的每一位都可以找到大块中的小块中的准确位置，即整个原串。



（或者这样理解：将 $s'$ 拆开，三次操作相当于找到位置 $i$ 所对应的26进制数）

### 代码

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=10005;
int pos[N];
string s,print,res;
char ans[N];

int main(){
    cin>>res;
    int len=res.size();
    print="? ";
    char ch='a';
    //先分成26*26的大块，确定在大块的位置
    for(int i=0;i<len;i++){
        print+=ch;
        if((i+1)%(26*26)==0) ch++;
    }
    cout<<print<<endl;
    cin>>s;
    for(int i=0;i<len;i++) pos[i]+=(s[i]-'a')*26*26;
    ch='a';
    print="? ";
    //分成26的小块，确定在小块的位置
    for(int i=0;i<len;i++){
        print+=ch;
        if((i+1)%26==0) ch++;
        if(ch=='z'+1) ch='a';
    }
    cout<<print<<endl;
    cin>>s;
    for(int i=0;i<len;i++) pos[i]+=(s[i]-'a')*26;
    ch='a';
    print="? ";
    //分成1，确定最终的位置
    for(int i=0;i<len;i++){
        print+=ch;
        ch++;
        if(ch=='z'+1) ch='a'; 
    }
    cout<<print<<endl;
    cin>>s;
    for(int i=0;i<len;i++) pos[i]+=(s[i]-'a');
    for(int i=0;i<len;i++)
        ans[pos[i]]=res[i];
    printf("! %s",ans);
    fflush(stdout);
    return 0;
}
```



---

## 作者：Nelofus (赞：2)

## 题解

当 $len\le 26$ 的时候问题是非常简单的。我们直接询问 `abcd...z`，考虑第 $i$ 个字符到的位置 $j$，然后令 $ans_i=s_j$ 就行了。

那么 $len=|\Sigma|$ 的情况显然就是这样，但是显然我们 $|\Sigma|=26$ 没法整这种东西，怎么办呢！其实这个告诉我们我们的关键就是要知道每个位置最后被换到了哪里。

如果不在乎询问次数，我们可以每次询问 `aaabaaaa` 这种，然后考虑最后 `b` 的位置，我们就知道了 `b` 最后被换到了什么位置。

用 $\mathcal O(n)$ 次询问就能问出来最后的答案了！但是这个东西显然有点过于笨蛋了，我们每次就用了两种字符。

考虑把两种做法结合起来，先想 $len\le 26^2$ 怎么做，这个时候我们可以这样询问

1.   `abcd...xyzabcd...xyz...`，用 `abcd...xyz` 循环。
2.   `aaa...a(26)bbb...b(26)...zzz...z(26)` 用每段长度为 $26$ 的字符连续段循环。

那么换位的时候，假设第 $i$ 个位置在第一个串里面被换成了 $c_i$，而在第二个串里面没有变，说明一定是和自己这段长度为 $26$ 的同色段里，第一段中的 $c_i$ 交换的位置。

如果第 $i$ 个位置在第二个串里面被换成了 $p_i$，第一个串里变成了 $c_i$，说明是和 $p_i$ 那一段里面的 $c_i$ 做了交换。

所以我们就确定了每个位置被换到的位置。

所以我们就会做 $len\le 26^3$ 了，只要再询问一个

3.   `aaa...a(26*26)bbb...b(26*26)...zzz...z(26*26)`

确定它在第三层的位置即可。

## 代码

写得很整齐（

```cpp
#include <bits/stdc++.h>
using i64 = int64_t;

int main() {
	std::ios::sync_with_stdio(false);

	std::string origin;
	std::string answer;
	std::string query1;
	std::string query2;
	std::string query3;

	std::cin >> origin;
	int n = origin.length();
	answer.resize(n);
	query1.resize(n);
	query2.resize(n);
	query3.resize(n);
	std::vector<int> to1(n);
	std::vector<int> to2(n);
	std::vector<int> to3(n);
	// 维护变成了什么字符
	
	for (int i = 0; i < n; i++)
		query1[i] = (i % 26) + 'a';	

	for (int i = 0; i < n; i++)
		query2[i] = (i / 26 % 26) + 'a';

	for (int i = 0; i < n; i++)
		query3[i] = (i / 26 / 26) + 'a';

	auto ask = [&](std::string &query, std::vector<int> &answer) -> void {
		std::string reply;
		std::cout << "? " << query << std::endl;

		std::cin >> reply;
		for (int i = 0; i < n; i++)
			answer[i] = reply[i] - 'a';
	};

	ask(query1, to1);
	ask(query2, to2);
	ask(query3, to3);

	for (int i = 0; i < n; i++) {
		int pos = to3[i] * 26 * 26 + to2[i] * 26 + to1[i];
		answer[pos] = origin[i];
	}
	std::cout << "! " << answer << std::endl;
	return 0;
}
```



---

## 作者：TLE_Automat (赞：1)

## 题意：

**这是一个交互题。**

交互器有一个字符串 $s$ ，现在交互器将随机生成一个 $1$ 到 $|s|$ 的排列 $p$ 和一个字符串 $t$ ，满足 $t_{p_i} = s_i$ 。

现在给出生成的字符串 $t$ ，要求通过给交互器一些询问得到字符串 $s$ 。

你最多可以进行 $3$ 次询问，每次询问给交互器一个长度为 $|s|$ 的字符串 $s^{'}$ ，交互器将按照一开始的排列 $p$ 返回一个字符串 $t^{'}$ 满足 $t^{'}_{p_i} = s^{'}_i$ 。

## 数据范围：

$1\le |s| \le 10^{4}$ 。

## 做法：

看到题解里没有人细讲中国剩余定理的做法，那我就来写一篇题解讲一讲。

- **第一步：考虑我们每次询问能够得到什么**

  假设我们询问的字符串为 $ask$ ，询问得到的字符串为 $ans$ ，则对于 $ans_i$ 来说，它可能是 $s$ 中的任意一个满足 $s_j = ans_i$ 的位置 $j$ 转移过来的。

- **第二步：考虑进行有规律的构造**

  假设我们构造一个长度为 $len$ 的循环，假设 $len = 3$ ，那就一直 $\texttt{abcabc}\cdots$ 这样构造下去。

  根据第一步的观察，发现若 $ans_i$ 为 $\texttt{a}$ ，则它在原串的位置集合只能是 $\{1,4,\cdots,1+len\times k\}$ 。

- **第三步：总结结论得出解法**

  我们先令 $f(i)$ 表示在结果串 $t$ 和待猜串 $s$ 中满足 $t_i = s_{f(i)}$ ，那么我们求出 $f(i)$ 也就解决了此题。

  根据第二步的构造方法和结论，我们发现每次构造一个长度为 $len$ 的循环，实际上就是给 $f(i)$ 加了一个 $f(i) \equiv m \pmod{len}$ 的限制。

  然后我们发现 $26 \times 25 \times 23 = 14950 > 10^{4}$ 且它们两两互质，那么我们只要分别构造 $len= 26 , 25 ,24$ 的循环，就可以保证 $f(i)$ 在 $14950$ 内有且仅有一个解，就可以通过中国剩余定理解出来了！
  

$\text{Source :}$

```cpp
#include <bits/stdc++.h>

using namespace std;

#define y1 lyptxdy
#define y2 wscyyds
#define SZ(x) ((int)((x).size()))
#define lb(x) ((x)&(-(x)))
#define mkp make_pair
#define pb push_back
#define fi first
#define se second
typedef long long ll;
typedef pair<int,int> pii;

const int MAXN=1e4+10;

inline int exgcd(int a,int b,int &x,int &y)
{
    if(!b) return x=1,y=0,a;
    int g=exgcd(b,a%b,x,y);
    int tmp=x; x=y; y=tmp-a/b*y;
    return g;
}

char tmp[MAXN];
inline void ask(int *f,int n,int len)
{
    for(int i=1,cur=0;i<=n;i++)
        tmp[i]=cur+'a',cur=(cur+1)%len;
    printf("? %s\n",tmp+1);
    fflush(stdout);

    scanf("%s",tmp+1);
    for(int i=1;i<=n;i++)
        f[i]=tmp[i]-'a';
}

int n;
char s[MAXN];
int f[3][MAXN];     // mod 26 , mod 25 , mod 23
int p[MAXN];

void solve()
{
	scanf("%s",s+1);
    n=strlen(s+1);

    ask(f[0],n,26);
    ask(f[1],n,25);
    ask(f[2],n,23);

    int N=26*25*23;
    for(int i=1;i<=n;i++)
    {
        int a1=N/26,x1,y1; exgcd(a1,-26,x1,y1); x1*=f[0][i];
        int a2=N/25,x2,y2; exgcd(a2,-25,x2,y2); x2*=f[1][i];
        int a3=N/23,x3,y3; exgcd(a3,-23,x3,y3); x3*=f[2][i];
        p[i]=((a1*x1+a2*x2+a3*x3)%N+N)%N+1;
    }

    static char ans[MAXN];
    for(int i=1;i<=n;i++)
        ans[p[i]]=s[i];
    printf("! %s\n",ans+1);
    fflush(stdout);
}

int main()
{
	int T=1;
	while(T--) solve();
	return 0;
}
```

完结撒花！！(′・∀・『)



---

## 作者：Halberd_Cease (赞：1)

实在是很好的题。

先从 $|s|\le26$ 开始考虑，我们显然只需要询问一次就可以获得其变换顺序。

这本质上是把变换后的串和原串的每一位进行对应，在 $s$ 的位数很小的时候，可以用字符集中的字符进行对应。

然后我们考虑 $|s|\le 10^4$ 的情况，如果我们不考虑询问的字符集 $26$ 个可用字母限制（即我们可以用任意数字进行询问），这其实和上面的是一样的。

接下来，我们考虑把数字用字母表示出来。

题目给出 $3$ 次询问上限，又因为题目本身的性质：每次询问中在同一位置的字母在每次回答中的位置永远相同，我们想到用 $3$ 个字母来表示一个数，最多可以表示 $26^3=17576$ 个数，大于题目范围 $10^4$。

然后这道题就做完了。

总结方法如下：

将每一个 $10$ 进制数转换成一个三位 $26$ 进制数，用 $26$ 个字母分别表示，分 $3$ 次询问，每次询问一个位，最后把变换后的目标串变回去就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
string str;
string ans;
string s1,s2,s3;
int miepu[200010];
signed main()
{
    cin>>str;
    ans.resize(str.size());
    int n=str.size();
    cout<<"? ";
    for(int i=0;i<n;i++)
    {
        cout<<(char)(i/(26*26)+'a');
    }
    cout<<endl;
    cin>>s1;
    cout<<"? ";
    for(int i=0;i<n;i++)
    {
        cout<<(char)((i/26)%26+'a');
    }
    cout<<endl;
    cin>>s2;
    cout<<"? ";
    for(int i=0;i<n;i++)
    {
        cout<<(char)(i%26+'a');
    }
    cout<<endl;
    cin>>s3;
    for(int i=0;i<n;i++)
    {
        miepu[i]=(s1[i]-'a')*26*26+(s2[i]-'a')*26+s3[i]-'a';
        ans[miepu[i]]=str[i];
    }
    cout<<"! "<<ans;
}
```

---

## 作者：Purslane (赞：0)

# Solution

考虑 $26^3 > 10^4$，所以可以构造若干个 $26$ 进制数（用 $a$ 到 $z$ 表示每一位），通过三次询问就知道最后得到的置换是什么样的。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e4+10;
string query(string output) {string input;return cout<<"? "<<output<<endl,cin>>input,input;}
int n,rnk,p[MAXN];
string S,id[MAXN],psl[MAXN];
map<string,int> rev;
int main() {
	ffor(c1,'a','z') ffor(c2,'a','z') ffor(c3,'a','z') {
		string ans; rnk++,ans+=c1;ans+=c2,ans+=c3;
		id[rnk]=ans,rev[ans]=rnk;
	}
	cin>>S,n=S.size(),S="&"+S;
	ffor(op,1,3) {
		string output,input;
		ffor(j,1,n) output+=id[j][op-1];
		input=query(output);
		ffor(j,1,n) psl[j]+=input[j-1];
	}
	cout<<"! ";
	ffor(i,1,n) p[rev[psl[i]]]=i;
	ffor(i,1,n) cout<<S[p[i]];
	cout<<endl;
	return 0;
}
```

---

