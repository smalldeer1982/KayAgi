# Balanced Unshuffle (Hard)

## 题目描述

The only difference with the medium version is the maximum length of the input.

A parentheses sequence is a string consisting of characters "(" and ")", for example "(()((".

A balanced parentheses sequence is a parentheses sequence which can become a valid mathematical expression after inserting numbers and operations into it, for example "(()(()))".

The balance of a parentheses sequence is defined as the number of opening parentheses "(" minus the number of closing parentheses ")". For example, the balance of the sequence "(()((" is 3.

A balanced parentheses sequence can also be defined as a parentheses sequence with balance 0 such that each of its prefixes has a non-negative balance.

We define the balanced shuffle operation that takes a parentheses sequence and returns a parentheses sequence as follows: first, for every character of the input sequence, we compute the balance of the prefix of the sequence before that character and write those down in a table together with the positions of the characters in the input sequence, for example:

Prefix balance01212321Position12345678Character(()(()))Then, we sort the columns of this table in increasing order of prefix balance, breaking ties in decreasing order of position. In the above example, we get:

Prefix balance01112223Position18427536Character()(()())The last row of this table forms another parentheses sequence, in this case "()(()())". This sequence is called the result of applying the balanced shuffle operation to the input sequence, or in short just the balanced shuffle of the input sequence.

Surprisingly, it turns out that the balanced shuffle of any balanced parentheses sequence is always another balanced parentheses sequence (we will omit the proof for brevity). Even more surprisingly, the balanced shuffles of two different balanced parentheses sequences are always different, therefore the balanced shuffle operation is a bijection on the set of balanced parentheses sequences of any given length (we will omit this proof, too).

You are given a balanced parentheses sequence. Find its preimage: the balanced parentheses sequence the balanced shuffle of which is equal to the given sequence.

## 样例 #1

### 输入

```
()(()())```

### 输出

```
(()(()))```

# 题解

## 作者：cjh20090318 (赞：6)

学长组在模拟赛里的题，赛时因为 $50000$ 个 `std::stack` 爆零了，所以警示后人尽量少使用基于 `std::deque` 的容器。

看了下题解区另外的两篇题解，都写的比较长，这里讲一个实现简单的算法。

## 题意

参见[题意翻译](https://www.luogu.com.cn/problem/CF1970A3)。

## 分析

因为这是一个合法的括号序列，所以 $x$ 的左括号数量和 $x+1$ 的右括号数量是相等的。

然后我们根据这个性质对变换出的结果进行分段，从左往右依次扫描统计 $x$ 的左括号数量直到遇到右括号，接着将 $x \gets x+1$，继续扫描直到右括号数量抵消掉左括号数量即可。

因为第二关键字是按在原序列中的位置降序排序，所以对于字符存在对应 $x$ 的栈中即可，最后模拟依次取出栈顶即可。

时间复杂度 $O(n)$。

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
#define MAXN 500005
using namespace std;
int n;
char s[MAXN];
stack<char,vector<char> > t[MAXN];//注意使用 std::vector 特化的 std::stack，否则空间会超限。
int main(){
	scanf("%s",s),n=strlen(s);
	int x=0,l=0,r;
	for(int i=0,j;i<n;i=j){
		for(j=i;j<n&&s[j]=='(';j++)t[x].push(s[j]),++l;
		++x;
		for(r=l,l=0;j<n&&r;j++) t[x].push(s[j]),s[j]=='('?++l:--r;//在抵消右括号数量的同时也要统计新的 x 的左括号数量。
	}
	x=0;
	for(char c;!t[x].empty();)
		putchar(c=t[x].top()),t[x].pop(),x+=c=='('?1:-1;//取出栈顶，然后计算新的 x。
	return 0;
}
```

---

## 作者：SFlyer (赞：5)

[A1](https://codeforces.com/contest/1970/problem/A1)

[A2](https://codeforces.com/contest/1970/problem/A2)

[A3](https://codeforces.com/contest/1970/problem/A3)

这个是比赛中我为队贡献的最有价值的一题，写一下吧。以下就是我的思考过程。

因为 A2, A3 方法差不多，就直接说 $\mathcal{O}(n)$ 的做法。

我们来研究一个例子 `((()))()(())`。他的前驱为 `((()()))()()`。

我们能得到的消息有，Prefix balance（PB） 为 $0$ 的有 $3$ 个，因为 `((()))()(())` 开头有 $3$ 个 `(`。（为什么呢？因为 `)` 显然 PB$\ge 1$，而且如果是小于 $3$ 个，一定会先出现一个 `)`，他是倒序排的）。所以，我们知道前驱是 `(...)(...)(...)` 这样的一个东西。

有 $3$ 个 `(`，一定会对应三个 `)`，所以 `((()))()(())` 中的 $4$ 到 $6$ 都是 PB 为 $1$ 的。怎么确定第 $7$ 个呢？同样，如果 PB 为 $2$，一定是 `)`。所以，第 $7$ 个 PB 为一。所以，我们知道前驱是 `((...)(...)(...)` 这样的一个东西。

第 $8$ 个告诉我们是 `((...))(...)(...)` 这样的一个东西。类似的，第 $9,10$ 个告诉我们是 `((...(...(...))(...)(...)` 这样的一个东西。最有两个，根据 PB 的值，我们就得到 `((()()))()()` 了！

这只是一个例子。我们怎么用具体描述？

按照 PB 把 `((()))()(())` 分类，有 `(((` 是 $0$，`)))(` 是 $1$，`)((` 是 $2$，`))` 是 $3$。我们可以发现，对于 PB 是 $i+1$ 的，塔里面的 `)` 数量是 $i+1$ 里的 `(` 数量。`)` 够了，要一直加到不是 `(` 为止。我们就求出哪些括号是什么 PB 了。

上面的东西，我们把 $i+1$ 中的 `)` 移到 $i$ 里面，我们得到了：`((()))`，`()`，`(())`，这说明，是 `()()()`，`()`，`()()` 逐层嵌套的形式。因为是 PB 相同的时候按照从大到小的编号，所以，约在后的要嵌套到前面。比如说，`()()` 嵌套在 `()` 里，变成 `(()())`。因为是 `)))(`，所以 `(()())` 应该嵌套在 `()()()` 的第一个里面，变成了 `((()()))()()` ！

具体是第几个，就是 reverse 后前面有多少个 `)` 加一个。很好理解。因此我们把嵌套的连一条边然后 dfs 就可以 $\mathcal{O}(n)$ 做完了。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 5e5+5;

string s;
vector<string> v;
vector<int> g[N],e[N];
int cnts[N],id[N];

void dfs(int u){
	if (e[u].size()==0){
		cout<<"()";
		return;
	}
	if (u) cout<<"(";
	for (auto v : e[u]){
		dfs(v);
	}
	if (u) cout<<")";
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>s;
	int i=0;
	string cur;
	while (s[i]=='('){
		cur.push_back('(');
		i++;
	}
	v.push_back(cur);
	int cnt=cur.size();
	cur.clear();
	while (i<s.size()){
		int ct=0,cc=0;
		while (ct<cnt){
			ct+=(s[i]==')');
			cc+=(s[i]=='(');
			cur.push_back(s[i]);
			i++;
		}
		while (i<s.size() && s[i]=='('){
			cc++;
			cur.push_back(s[i]);
			i++;
		}
		v.push_back(cur);
		cur="";
		cnt=cc;
	}
	for (int i=0; i<v.size(); i++){
		reverse(v[i].begin(),v[i].end());
	}
	for (int i=0; i+1<v.size(); i++){
		int cl=0;
		for (auto ch : v[i]){
			cl+=(ch=='(');
		}
		cnts[i]=cl;
	}
	for (int i=0; i<cnts[0]; i++){
		e[0].push_back(i+1);
	}
	id[0]=1;
	int sum=cnts[0];
	for (int i=1; i+1<v.size(); i++){
		id[i]=sum+1;
		sum+=cnts[i];
	}
	for (int i=0; i+1<v.size(); i++){
		int cur=0,cnt=0;
		for (auto ch : v[i+1]){
			if (ch=='('){
				e[id[i]+cur].push_back(id[i+1]+cnt);
				cnt++;
			}
			else{
				cur++;
			}
		}
	}
	dfs(0);
	return 0;
}
```

---

## 作者：EXODUS (赞：1)

# Part 1：前言

还挺有意思的一个题。

# Part 2：正文

直接做没有太好的想法，因此考虑从题目所给的结论入手。

- 平衡括号序列（balanced parentheses sequence）在做平衡洗牌（balanced shuffle）后得到的仍是平衡括号序列。

  考虑平衡洗牌的过程。我们相当于是把所有括号按照某个权值 $x_i$ 排序，因此我们考虑每个权值对应哪些括号。不难发现，如果我们把括号序列的括号树建出来的话，$x_i=0$ 的括号一定是括号树上第一层所有节点所代表的左括号，$x_i=1$ 的括号是括号树上第一层的右括号和第二层的左括号，以此类推。

  因此第 $i$ 层的左括号在平衡排序后一定出现在第 $i$ 层右括号的前面。故仍是平衡括号序列。

- 平衡括号序列与做平衡洗牌后形成的括号序列形成双射关系。

  审视第一个结论的证明过程，我们可以考虑把排序后的序列分段，每段中括号的权值 $x_i$ 相同。经过进一步的思考，我们发现可以按照如下的方式分段。

  - 设每一段的左右端点分别为 $l_i$ 和 $r_i$，则 $l_i=r_{i-1}+1$。
  - 设在第 $k-1$ 段中的左括号数为 $y_{k-1}$，则 $[l_k,r_k]$ 为 $l_k=r_{k-1}+1$ 时最长的包含 $k$ 个右括号的子段。特别的，定义 $y_0=0$。

  这样分段后第 $k$ 段中所有括号 $i$ 的权值 $x_i$ 均为 $k$。

  接下来考虑还原括号序列。注意到，对于每一段，在第 $i$ 和第 $i+1$ 个右括号之间的左括号，会被嵌套到上一层中从后到前的第 $i$ 个括号里。

分析至此，我们已经有一个明确的解法了。对于 A2，我们可以分段后暴力模拟。对于 A3，我们发现，右括号不决定括号树的结构，只决定括号间的分段情况，因此我们直接以左括号为基本单位维护括号树结构，最后一遍 dfs 还原括号序列即可。

# Part 3：代码

```cpp
// To all the dreams made
// 在一切仍然可控之际
// The ones not too late
// 别让梦想从指尖溜走
// Just remember
// 你只需谨记
// It's okay to start again
// 重新振作，本不可耻

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;

#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define File(filename) freopen(filename ".in","r",stdin),freopen(filename ".out","w",stdout)
#define Exit(p) fprintf(stderr,"[exit]: at breakpoint %d\n",p),exit(0);

#ifdef EXODUS
	#define Debug(...) fprintf(stderr,__VA_ARGS__)
#else
	#define Debug(...) 0
#endif

//=========================================================================================================
// Something about IO

template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T>
void seq_read(T bg,T ed){for(auto i=bg;i!=ed;++i)read(*i);}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}

//=========================================================================================================
//Some useful function

template<typename T>
void cmax(T& x,T y){x=max(x,y);}
template<typename T,typename... Args>
void cmax(T& x,T y,Args ...args){cmax(x,y);cmax(x,args...);}
template<typename T>
void cmin(T& x,T y){x=min(x,y);}
template<typename T,typename... Args>
void cmin(T& x,T y,Args ...args){cmin(x,y);cmin(x,args...);}
template<typename T,typename U>
void seq_assign(T bg,T ed,U val){for(auto i=bg;i!=ed;++i)(*i)=val;}
template<typename T,class F,class=enable_if_t<is_invocable_v<F>>>
void seq_assign(T bg,T ed,F func){for(auto i=bg;i!=ed;++i)(*i)=func(i);}
template<typename T>
void seq_copy(T dstbg,T dsted,T srcbg,T srced){for(auto i=dstbg,j=srcbg;i!=dsted&&j!=srced;++i,++j)(*i)=(*j);}

//=========================================================================================================
// Define the global variables here.

bool membg=0;

constexpr int N=5e5+7;
int n,tot;
vector<int>g[N];
char s[N];
vector<int>seq;

bool memed=0;

//=========================================================================================================
// Code here.

void dfs(int u){
	seq.emplace_back(0);
	for(auto v:g[u]){
		dfs(v);
	}
	seq.emplace_back(1);
}

void solve(){
	scanf("%s",s+1);
	n=strlen(s+1);
	vector<int>pos;
	int j=1;
	while(j<=n){
		if(s[j]==')')
			break;
		pos.emplace_back(++tot);
		++j;
	}
	++j;
	int bound=tot;
	for(;j<=n;){
		vector<int>npos;
		auto it=pos.rbegin();
		while(it!=pos.rend()&&j<=n){
			if(s[j]==')')
				reverse(g[*it].begin(),g[*it].end()),++it,++j;
			else
				npos.emplace_back(++tot),g[*it].emplace_back(tot),++j;
		}
		reverse(npos.begin(),npos.end());
		swap(pos,npos);
	}
	for(int i=1;i<=bound;i++)
		dfs(i);
	for(int i=0;i<n;i++)
		putchar(seq[i]?')':'(');
	putchar('\n');
	return;
}


//=========================================================================================================

int main(){
	Debug("%.3lfMB\n",fabs(&memed-&membg)/1024.0/1024.0);
	int timbg=clock();
	int T=1;
	while(T--)solve();
	int timed=clock();
	Debug("%.3lfs\n",1.0*(timed-timbg)/CLOCKS_PER_SEC);
	fflush(stdout);
	return 0;
}
```

---

