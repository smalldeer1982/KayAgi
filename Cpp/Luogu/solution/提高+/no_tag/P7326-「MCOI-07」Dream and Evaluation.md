# 「MCOI-07」Dream and Evaluation

## 题目描述

George 在学位运算。他编了一个位运算表达式，但是他不会高效计算这个表达式的值，于是他找 Dream 帮他计算。  
George 的表达式有 $64$ 个 01 变量，分别编号为 $0$ 到 $63$。他提供了该表达式的[后缀表示法](https://baike.baidu.com/item/%E5%90%8E%E7%BC%80%E8%A1%A8%E7%A4%BA%E6%B3%95/20835385?fr=aladdin)。  
后缀表示法里可能含有以下符号：

 - $0,1,\dots,63$，代表对应变量
 - `!&|^`，代表对应位运算

现在 Dream 有 $m$ 个情况。每一个情况固定所有 $64$ 个变量的值。他需要你对每一个情况计算给定表达式的值。  
为了方便输入，这些情况进行压缩。定义 $a_{i,j}$ 为第 $i$ 情况里的第 $j$ 变量值，其中 $a_{i,j}\in\{0,1\}$；他会给你

$$b_i=\sum_{j=0}^{63}a_{i,j}2^j$$

可以证明，如果 $0\le b_i<2^{64}$，则 $b_i$ 唯一对应一组 $a_{i,0},a_{i,1},\dots,a_{i,63}$。

## 说明/提示

#### 样例 1 解释

如果 $x=1$，则变量 $0$ 为 $1$，其余变量为 $0$。  
如果 $x=9$，则仅变量 $0$ 和 $3$ 为 $1$。

#### 数据规模与约定

**本题采用捆绑测试。**

 - Subtask 1（7 pts）：$n,m\le10^3$。  
 - Subtask 2（11 pts）：$b_i\in[0,2^{8}-1]$。
 - Subtask 3（41 pts）：$n,m\le5\times10^4$。
 - Subtask 4（41 pts）：没有额外限制。

对于所有数据，$1\le n,m\le10^5$，$0\le b_i<2^{64}$。

## 样例 #1

### 输入

```
8
0 1 ^ 2 3 ! & |
7
1 9 1 9 8 1 0```

### 输出

```
1111010```

## 样例 #2

### 输入

```
23
0 ! ! 3 0 3 ^ ^ 3 | & 1 ! ^ 2 0 ! 3 ^ ! ^ ! ^
20
11 10 4 8 13 7 2 5 11 9 16 15 6 9 7 8 15 0 2 10```

### 输出

```
00110011010101011010```

# 题解

## 作者：w33z8kqrqk8zzzx33 (赞：13)

观察到在纯暴力里面，栈永远仅包含 01 值，操作也全是 01 值操作，相对浪费。  
于是可以 $\omega$ 个求值处一起计算；将当前状态用一个 `unsigned long long` 等结构绑起来。  
对每一个 $\omega$ 求值块，处理出来在这个块里的所有变量在块里所含有的值，用一个类似与转置的方法，可以 $O(\omega^2)$ 暴力解决。 
最后，可以直接用栈模拟这一块，和暴力本质没区别。   
整体时间复杂度 $O(nm/\omega)$。

---

## 作者：Strelitzia (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/P7326)

---

方法：$\text {bitset}$，分组查询（类似[掉进兔子洞](https://www.luogu.com.cn/problem/P4688)）。

希望不要杀我 qwq。

基本想法：

读懂了题目，我们就可以有 $\operatorname O(nm)$ 的做法了，就是模拟。

所以可以，利用 $\text {bitset}$ 暴力模拟。

但这样是不能过的，在内存为 $250 \operatorname M\operatorname B$ 都会 $\text{MLE}$ 两个点，限制空间的，就是 $\text {bitset}$ 的大小。

而 $\text{bitset}$ 的大小和 $\operatorname m$ 有关，我们可以想办法减小 $\operatorname m$ 的长度。

所以就可以利用分组处理的方法，减小 $\text {bitset}$ 的长度，用 $\text{STL}$ 模拟即可。 


```cpp
#include <queue>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <cstring>
using namespace std;

template<typename T>void read(T &x) {
	x = 0;T f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if (x < 0) putchar('-'),x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

const int N = 1e3 + 5;

int n,m,top;
char s[100005][3];
unsigned long long a[1005];
bitset<N> tmp1;
vector<bitset<N> > st;
bitset<N> b[64];

int main () {
	read(n);
	for (int i = 1 ; i <= n ; ++ i)
		scanf("%s",s[i]);
	read(m);
	int cnt = 0;
	int x;
	for (int i = 0 ; i < m ; ++ i) {
		read(a[cnt ++]);
		if (cnt == 1000) {
			for (int i = 0 ; i < 64 ; ++ i) {
				b[i].reset();
				for (int j = 0 ; j < cnt ; ++ j)
					if ((a[j] >> i) & 1)
						b[i].set(j);
			}
			for (int i = 1 ; i <= n ; ++ i) {
				if (s[i][0] != '!' && s[i][0] != '&' && s[i][0] != '|' && s[i][0] != '^') {
					sscanf(s[i],"%d",&x);
					st.push_back(b[x]);
					top ++;
				}
				else {
					if (s[i][0] == '!') {
						st[top - 1] = ~st[top - 1];
					}
					if (s[i][0] == '&') {
						tmp1 = st.back();
						st.pop_back();
						top --;
						st[top - 1] = tmp1 & st[top - 1];
					}
					if (s[i][0] == '|') {
						tmp1 = st.back();
						st.pop_back();
						top --;
						st[top - 1] = tmp1 | st[top - 1];
					}
					if (s[i][0] == '^') {
						tmp1 = st.back();
						st.pop_back();
						top --;
						st[top - 1] = tmp1 ^ st[top - 1];
					}
				}
			}
			for (int i = 0 ; i < cnt ; ++ i)
				putchar(st[0][i] + '0');
			st.pop_back();
			cnt = top = 0;
		}
	}
	for (int i = 0 ; i < 64 ; ++ i) {
		b[i].reset();
		for (int j = 0 ; j < cnt ; ++ j)
			if ((a[j] >> i) & 1)
				b[i].set(j);
	}
	for (int i = 1 ; i <= n ; ++ i) {
		if (s[i][0] != '!' && s[i][0] != '&' && s[i][0] != '|' && s[i][0] != '^') {
			sscanf(s[i],"%d",&x);
			st.push_back(b[x]);
			top ++;
		}
		else {
			if (s[i][0] == '!') {
				st[top - 1] = ~st[top - 1];
			}
			if (s[i][0] == '&') {
				tmp1 = st.back();
				st.pop_back();
				top --;
				st[top - 1] = tmp1 & st[top - 1];
			}
			if (s[i][0] == '|') {
				tmp1 = st.back();
				st.pop_back();
				top --;
				st[top - 1] = tmp1 | st[top - 1];
			}
			if (s[i][0] == '^') {
				tmp1 = st.back();
				st.pop_back();
				top --;
				st[top - 1] = tmp1 ^ st[top - 1];
			}
		}
	}
	for (int i = 0 ; i < cnt ; ++ i)
		putchar(st[0][i] + '0');
	return 0;
}
```

---

## 作者：wsyhb (赞：5)

## 题解

直接按照题意**用栈模拟**，时间复杂度为 $O(nm)$，如何优化呢？

注意到题目中的 $64$ 个变量 为 $01$ 变量，考虑**压位计算**：

将 $a_{1,i},a_{2,i},\cdots,a_{m,i}$ 压成第 $i$ 个长度为 $m$ 的 **bitset**，同样模拟即可做到 $O(\dfrac{nm}{w})(w:wordsize)$ 的**时间复杂度**。

但注意到这样**空间复杂度**为 $O(nm)$（较为精确的上限为 $\dfrac{n}{2} \times m = 5 \times 10^9$），**分组计算**即可——

每次取出前 $k$ 个 $01$ 变量压成长度为 $k$ 的 $64$ 个 **bitset**，即可做到 $O(nk)$ 的**空间复杂度**，**时间复杂度不变**。

## 代码

（此处取 $k=4000$）

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+5;
char op[max_n][5];
const int max_len=4e3+5;
bitset<max_len> a[64],x,y;
stack<bitset<max_len> > st;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%s",op[i]);
	int m;
	scanf("%d",&m);
	for(int k=1;k<=(m+3999)/4000;++k)
	{
		int l=(k-1)*4000+1,r=min(k*4000,m);
		for(int i=0;i<=r-l;++i)
		{
			unsigned long long b;
			scanf("%llu",&b);
			for(int j=0;j<=63;++j,b>>=1)
				a[j][i]=b&1;
		}
		for(int i=1;i<=n;++i)
		{
			if(op[i][0]>='0'&&op[i][0]<='9')
			{
				int id=op[i][0]-'0';
				if(int(strlen(op[i]))>1)
					id=id*10+(op[i][1]-'0');
				st.push(a[id]);
			}
			else if(op[i][0]=='!')
			{
				x=st.top();
				st.pop();
				st.push(~x);
			}
			else
			{
				x=st.top();
				st.pop();
				y=st.top();
				st.pop();
				if(op[i][0]=='&')
					st.push(x&y);
				else if(op[i][0]=='|')
					st.push(x|y);
				else
					st.push(x^y);
			}
		}
		for(int i=0;i<=r-l;++i)
			putchar(st.top()[i]+'0');
	}
	puts("");
	return 0;
}
```

## 后记

**截止本文发布时**，[本人的 $O(nm)$ 空间复杂度的算法](https://www.luogu.com.cn/paste/rhjjrv88)（不是上面那一份）仍能通过此题（[AC 记录](https://www.luogu.com.cn/record/46310129)），不知道大家的如何。为了方便大家理解空间复杂度，此处给出 Hack 数据的生成方式：

``` cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(NULL));
	freopen("data.in","w",stdout);
	int n=1e5-1;
	printf("%d\n",n);
	for(int i=1;i<=n/2+1;++i)
		printf("%d ",rand()&63);
	for(int i=1;i<=n/2;++i)
	{
		int k=rand()%3;
		printf("%c%c",k==0?'&':(k==1?'|':'^'),i<n/2?' ':'\n');
	}
	int m=1e5;
	printf("%d\n",m);
	for(int i=1;i<=m;++i)
	{
		unsigned long long b=0;
		for(int j=0;j<=63;++j)
			b=b<<1|(rand()&1);
		printf("%llu%c",b,i<m?' ':'\n');
	}
	return 0;
}
```

**UPD**：上述提到的空间复杂度为 $O(nm)$ 的算法已被卡掉（就在我刚刚提交完题解以后，出题人就在讨论帖里表示已经卡掉/wul）

---

## 作者：EternalEpic (赞：3)

时空复杂度较优，目前在第一页。

首先我们可以发现这道题暴力很好打，都不用建表达式树，可以直接用栈模拟，但是时间复杂度是 $O(nm)$ 的。

聪明的你发现这是ddl w33z出的题，想到似乎有一种优化技巧是用 $bitset$ 来分组优化暴力，于是你决定莽一莽，写了一个时间复杂度为 $O(\frac{nm}{w})$ 的算法，在比赛时切了此题。

可是后来w33z又卡空间了，这该怎么办？可以对于 $bitset$ 再分组让空间开销除以一个常数，因为这道题很凑巧，$nm=10^{10}$ 无论对空间还是时间来说都是很好优化的。

```cpp
#define gc() getchar()

template <class T> inline void read(T &x) {
	T f = 1; x = 0; static char c = gc();
	for (; !isdigit(c); c = gc()) if (c == '-') f = -f;
	for (; isdigit(c); c = gc()) x = (x << 1) + (x << 3) + (c & 15);
	x *= f;
}

inline void readstr(char *s) {
	do *s = gc(); while ((*s == '\n') || (*s == '\r'));
	do *(++s) = gc(); while ((~*s) && (*s != '\n') && (*s != '\r'));
	*s = 0; return;
}

typedef bitset <4000> bts;

const int S = 1e5 + 5;
int n, m, q, top; char s[(int) 2.45e5];
bts a[64], sta[S], x, y;

signed main(void) {
	read(n); readstr(s); read(n);
	for (int l = 1, r; l <= n; l = r + 1) {
		r = min(l + 3999, n);
		for (int i = 0; i + l <= r; i++) {
			ull b; read(b);
			for (int j = 0; j < 64; j++)
				if (b & (1ull << j)) a[j][i] = 1; else a[j][i] = 0;
		}
		
		top = 0;
		for (int i = 0; s[i]; i += 2) {
			if (isdigit(s[i])) {
				int num = s[i] - '0'; ++i;
				while (s[i] != ' ') {
					num = (num << 1) + (num << 3) + (s[i] & 15);
					++i;
				} i--; sta[++top] = a[num];
			} else if (s[i] == '&') {
				x = sta[top--];
				y = sta[top--];
				sta[++top] = x & y;
			} else if (s[i] == '|') {
				x = sta[top--];
				y = sta[top--];
				sta[++top] = x | y;
			} else if (s[i] == '^') {
				x = sta[top--];
				y = sta[top--];
				sta[++top] = x ^ y;
			} else sta[top].flip();
		}
		
		for (int i = 0; i + l <= r; i++) putchar('0' + sta[top][i]);
	}
}
```


---

## 作者：Rem_CandleFire (赞：1)

### 题意
给出后缀表达式和 $m$ 种情况每种情况各项的取值，求表达式的值。
### 做法与时空优化

根据题意，使用栈**模拟**，时间复杂度 $O(nm)$，空间复杂度 $O(n)$，期望得分 11pts。

考虑优化时间复杂度，观察到表达式为 $01$ 运算，联想到 **bitset** 位运算优化。

我们把 $m$ 种情况一起压入 bitset 中，这样子在做具体运算时就可以一起操作，从而得到时间复杂度 $O(\frac{nm}{w})$ 的优秀算法，其中 $w$ 为计算机位数。

[附 bitset 详解(来源：bdfs)](https://www.cnblogs.com/sshadows/p/bitset.html)

然而，此类优化相当于是用空间换时间，空间复杂度达到了 $O(nm)$ 级别，从而导致了 MLE。

观察到，$m$ 种情况其实没有什么区别，**不需要强行同时存入处理**，于是考虑设置常数 $k$，分开 $\frac{m}{k}$ 次读入，只处理当前的 $k$ 种，就可以把空间复杂度降级到 $O(nk)$，同时时间复杂度不变。

个人选择了 $k=2000$。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,L=2e3+5;//空间复杂度降级
int n,m;
unsigned long long b;
string s[N];
bitset<L> a[70],x,y;
stack<bitset<L> > sta;
int main()
{
	scanf("%d",&n); 
	for(int i=1;i<=n;i++)
		cin>>s[i];
	scanf("%d",&m);
	for(int k=1;k<=m/2000+(m%2000!=0);k++)//k=2000
	{
		for(int i=1;i<=min(2000,m);i++)
		{
			scanf("%llu",&b);
			for(int j=0;j<=63;j++,b>>=1)
				a[j][i]=b&1;
		}
		for(int i=1;i<=n;i++)//计算
		{
			if(s[i][0]>='0'&&s[i][0]<='9')
			{
				int id=s[i][0]-'0';
				if(s[i].size()>1) id=id*10+s[i][1]-'0';
				sta.push(a[id]);
			}
			else if(s[i][0]=='!')
			{
				x=sta.top();
				sta.pop();
				sta.push(~x);
			}
			else
			{
				x=sta.top(); sta.pop();
				y=sta.top(); sta.pop();
				if(s[i][0]=='&') sta.push(x&y);
				if(s[i][0]=='|') sta.push(x|y);
				if(s[i][0]=='^') sta.push(x^y);
			}
		}
		for(int i=1;i<=min(2000,m);i++)
			cout<<sta.top()[i];
		sta.pop();//多测不清空，亲人两行泪
	}
	
} 
```

---

## 作者：Chydz (赞：1)

这是一个不怎么优秀但是非常通俗易懂的解法。

最先想到的是 $O(n^2)$ 暴力：将表达式树建出来，每一种情况跑一遍 dfs。

然后发现每一种情况经历的过程是完全一样的，考虑如何一次 dfs 搞定。由于所有计算都是位运算，每个数的值也是 $0/1$，可以用方便的 $bitset$ 将 $m$ 种情况都存起来。于是，可以在每个（树上的）结点开一个 $bitset$，表示计算到这里，答案为 $1$ 的情况集合。

但是发现，这样会 **MLE**。~~然后我就开始了一系列愚蠢的卡空间行为。~~ 之所以说愚蠢，是因为我竟从头到尾都没想过去减少 $bitset$ 的位数。

经过两页半的提交尝试后可以得知，导致 MLE 的罪魁祸首就是 $bitset$ 的位数！！！

如何减少 $bitset$ 的位数？——分组。将 $m$ 分成 $sqrt(m)$ 组，分别进行 dfs。相当于增加时间减少空间。

具体看代码：
```cpp
#include<iostream>
#include<cstdio>
#include<bitset>
#define ll long long
#define bb bitset<565>
using namespace std;

int n,m,l[100005],r[100005],f[100005],id[100005],cnt[100005],bl[100005];
char s[100005],ch[5];
bb ss[65],se[16];
ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
void Dfs(int x)
{
	f[x]=1;
	if(l[x])Dfs(l[x]);
	if(r[x])Dfs(r[x]);
	f[x]+=max(f[l[x]],f[r[x]]);
}
void dfs(int x,int z)//朴素的dfs
{
	if(s[x]<=63){
		int y=s[x];
		se[z]=ss[y];
		return;
	}
	int p=z,q=z;
	if(f[l[x]]>f[r[x]]){//此处的f为没有实质用途的卡空间行为
		q+=1;
		if(l[x])dfs(l[x],p);
		if(r[x])dfs(r[x],q);
	}
	else{
		p+=1;
		if(r[x])dfs(r[x],q);
		if(l[x])dfs(l[x],p);
	}
	if(s[x]==64)se[z]=~se[p];
	if(s[x]==67)se[z]=se[p]|se[q];
	if(s[x]==66)se[z]=se[p]&se[q];
	if(s[x]==65)se[z]=se[p]^se[q];
}
int main()
{
	n=read();
	int x;
	for(int i=1;i<=n;i++){
		cin>>ch;
		if(ch[0]>='0'&&ch[0]<='9'){
			x=0;x=ch[0]-'0';
			if(ch[1]>='0'&&ch[1]<='9')x=x*10+ch[1]-'0';
			s[i]=(char)x;
		}
		if(ch[0]=='!')s[i]=64;
		if(ch[0]=='^')s[i]=65;
		if(ch[0]=='&')s[i]=66;
		if(ch[0]=='|')s[i]=67;
	}
	int rt=n;//建表达式树
	for(int i=n-1;i>=1;){
		while(s[rt]<=63)rt=f[rt];//此处的f是表达式树上结点的父亲
		if(!l[rt]){
			l[rt]=i;
			f[i]=rt;
			rt=i;i--;
		}
		else{
			if(!r[rt]&&s[rt]!=64){
				r[rt]=i;
				f[i]=rt;
				rt=i;i--;
			}
			else rt=f[rt];
		}
	}
	m=read();
	int block=m/320+1;//分组进行处理
	for(int i=1;i<=m;i++){
		bl[i]=i/320+1;
		id[i]=++cnt[bl[i]];
	}
	Dfs(n);//（没有实质用途的卡空间行为）
	int k=1;
	for(int i=1;i<=block;++i)
	{
		int pp=k;
		for(;k<=m&&bl[k]==i;++k){
			ll x=read();
			for(int j=0;j<64;++j)ss[j][id[k]-1]=(x&(1ll<<j));
		}
		dfs(n,0);//dfs一遍计算答案
		for(int j=pp;j<k;j++)cout<<se[0][id[j]-1];
	}
	return 0;
}
```


---

## 作者：TemplateClass (赞：0)

首先直接用栈进行计算是 $O(nm)$ 的，考虑优化。

发现我们每次操作的变量都是单比特的，一个个计算过于浪费。所以我们用 `unsigned long long` 把 $64$ 个变量压到一起进行计算即可，时间复杂度 $O(nm/\omega)$，其中 $\omega = 64$。

```cpp
#include<iostream>
#include<string>
#include<stack>
#include<cctype>
#include<cstring>

typedef long long ll;
typedef unsigned long long ull;

constexpr int N = 1e5 + 1;
constexpr int L = 64;

int n, m; int op[N]; ull x[L];

inline ull p(std::stack<ull>& s) { ull r = s.top(); s.pop(); return r; }
inline void prc(int l) {
	std::stack<ull> s;
	for(int i = 1; i <= n; ++i) {
		if(op[i] >= 0) s.push(x[op[i]]);
		else {
			char og = -op[i];
			if(og == '!') { s.push(~p(s)); continue; }
			ull f1 = p(s), f2 = p(s);
			if(og == '&') s.push(f1 & f2);
			if(og == '|') s.push(f1 | f2);
			if(og == '^') s.push(f1 ^ f2);
		}
	}
	ull fr = p(s);
	for(int i = 0; i < l; ++i) 
		std::cout << (bool)(fr & (1ull << i));
	std::memset(x, 0, sizeof x);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> n;
	for(int i = 1; i <= n; ++i) {
		std::string s; std::cin >> s;
		if(std::isdigit(s[0])) op[i] = std::stoi(s);
		else op[i] = -s[0];
	}
	std::cin >> m;
	for(int _ = 1, p = 0; _ <= m; ++_) {
		ull b; std::cin >> b;
		for(int i = 0; i < 64; ++i) {
			if(b & (1ull << i)) x[i] |= (1ull << p);
		}
		if((++p) == L || _ == m) prc(p), p = 0;
	}
	
	return 0;
}
```

---

## 作者：xuyiyang (赞：0)

### [P7326 「MCOI-07」Dream and Evaluation](https://www.luogu.com.cn/problem/P7326)
### Solution
分组压位。每 $64$ 个询问压在一个 `ull` 中一起做询问。做的时候就拿个栈扫一遍就好了。$\mathcal O(\frac{nm}{\omega})$。其中 $\omega = 64$。空间是优秀的线性！本质上和 `bitset` 做法相同，只是本做法分组做更多，但是又有相同的常数，所以空间降了。
```cpp
const int N = 1e5 + 10;
typedef unsigned long long ull;

int n, m, top;
int s[N];
ull w[N], val[N];
ull stk[N];

void solve(int l, int r) {
  for (int i = 0; i < 64; i ++ ) val[i] = 0;
  for (int i = l; i <= r; i ++ ) {
    for (int j = 0; j < 64; j ++ )
      val[j] |= (w[i] >> j & 1) << (i - l);
  } 
  top = 0;
  for (int i = 1; i <= n; i ++ ) {
    if (s[i] <= 64) stk[ ++ top] = val[s[i]];
    else {
      char ch = (char)(s[i] - 127);
      if (ch == '!') stk[top] = ~stk[top];
      else {
       ull x = stk[top -- ]; ull y = stk[top -- ];
       if (ch == '&') stk[ ++ top] = x & y;
       else if (ch == '|') stk[ ++ top] = x | y;
       else stk[ ++ top] = x ^ y;
      }
    }
  }
  for (int i = l; i <= r; i ++ ) putchar((stk[1] >> (i - l) & 1) + 48);
}

int main() {
//  freopen("a.in", "r", stdin); freopen("a.out", "w", stdout);
  scanf("%d\n", &n);
  for (int i = 1; i <= n; i ++ ) {
    string str; cin >> str;
    if ((int)str.size() > 1) s[i] = (str[0] - '0') * 10 + str[1] - '0';
    else if (isdigit(str[0])) s[i] = str[0] - '0';
    else s[i] = str[0] + 127;
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; i ++ ) scanf("%llu", &w[i]);
  int L = 1;
  while (L <= m) solve(L, min(L + 63, m)), L += 64;
  return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

# 前言
赛时感觉是 $bitset$ ，毕竟前一段时间碰到了一道累似的题，然后觉得时间复杂度不对，又不敢继续细想磨磨蹭蹭还是没搞最后知道正解是 $bitset$ ，后悔后悔后悔，果然 $Dream$ 场我就是松饼小队成员！！！      

# 正文      

首先其实我个人认为这么出题还是不好？毕竟 $bitset$ 过 $O(3e8),3s$ 还是有点恶心，这也是我比赛时不敢做 $bitset$ 的原因。       

首先我们看到这道题，感觉很难读？感觉是一个信息压缩的二进制数然后要求你快速运算，一看操作，怎么有 ```!&|^``` 啊？如果单给两个位运算说不定还可以找运算，现在通过运算种类解题的思路基本没了。       

接着，我就感觉很难开这道题了，除了个 $O(nm)$ 的暴力什么不会，那么现在只能从暴力下手了。        

突然想起来，这个暴力全是位运算，那么自然而然的上 $bitset$ 大哥了，然后就发现是个 $O(3e8),3s$ ，~~理论~~跑得过的时间复杂度。      

不过我们现在如果直接一位一位跑就很浪费时间了，又发现这些数都是 $01$ 运算，所以我们不妨考虑直接开 $64$ 个 $1e5$ 的 $bitset$ 令其为 $b$ ，然后 $b_{i,j}$ 第 $j$ 位保存第 $j$ 个询问的第 $i$ 位，也就是题目中所述的 $a_{j,i}$ ，接着我们把它们拉出来一起跑就行了。      

接着我们就发现我们空间炸了，如果你是一个忠实的 $Ynoi$ 热爱者，那么我问你 $bitset$ 炸空间，并且 $bitset$ 的长度还和询问个数有关时怎么办？这很明显兔子洞嘛，我们暴力拆询问，拆成个 $1000 * 100$ 的 $100$ 组询问即可，并且由于我们的程序是暴力改进，所以说我们的时间复杂度不会变，就好比你之前是一个 $O(10000 \times 10000)$ ， 那么现在我就是 $O(100 \times 10000 \times 100)$ 最后还是一样的时间复杂度，只不过组数越多你的一些附加操作例如清空其实也是会影响时间复杂度的，所以只要分组量不往极端走时间复杂度就没什么大变化。       

然后这道题就差不多了，如果还能改一个数据结构上来有望和兔子洞比一比？     
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>void read(T &x) {
	x = 0;T f = 1;char ch = getchar();
	while (!isdigit(ch)) {if (ch == '-') f = -1;ch = getchar();}
	while (isdigit(ch)) {x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if (x < 0) putchar('-'),x = -x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
const int N = 1+ 5;
int n,m,top,cnt;
unsigned long long a[100005];
bitset<N> st[100005];
bitset<N> b[64];
bitset<N> calc;
char s[100005][3];
int main()
{
	scanf("%d",&n);
	for (int i = 1 ; i <= n ; ++ i)
		scanf("%s",s[i]);
	scanf("%d",&m);
	for(int i = 0 ; i < m ; i ++) 
	{
		read(a[cnt ++]);
		if(cnt == 1)
		{
			for(int i = 0 ; i < 64 ; i ++)
			{
				b[i].reset();	
				for(int j = 0 ; j < cnt ; j ++) if((a[j] >> i) & 1) b[i].set(j);
			}
			int top = 0;int x;
			for(int i = 1 ; i <= n ; i ++)
			{
				if(s[i][0] != '|' && s[i][0] != '&' && s[i][0] != '^' && s[i][0] != '!') 
				{
					sscanf(s[i],"%d",&x);
					st[++ top] = b[x];
				}
				else
				{
					if(s[i][0] == '|')
					{
						calc = st[top --];
						st[top] = calc | st[top];
					}
					else if(s[i][0] == '&')
					{
						calc = st[top --];
						st[top] = calc & st[top];
					}
					else if(s[i][0] == '^')
					{
						calc = st[top --];
						st[top] = calc ^ st[top];
					}
					else st[top] = ~st[top];
				}
			}
			for(int i = 0 ; i < cnt ; i ++) putchar(st[1][i] + '0');
			cnt = 0;
			//for(int i = 1 ; i <= 1000 ; i ++) st[i].reset();
		}
	}
	for(int i = 0 ; i < 64 ; i ++)
	{
		b[i].reset();	
		for(int j = 0 ; j < cnt ; j ++) if((a[j] >> i) & 1) b[i].set(j);
	}
	int tot = 0 , top = 0;int x;
	for(int i = 1 ; i <= n ; i ++)
	{
		if(s[i][0] != '|' && s[i][0] != '&' && s[i][0] != '^' && s[i][0] != '!') 
		{
			sscanf(s[i],"%d",&x);
			st[++ top] = b[x];
		}
		else
		{
			if(s[i][0] == '|')
			{
				calc = st[top --];
				st[top] = calc | st[top];
			}
			else if(s[i][0] == '&')
			{
				calc = st[top --];
				st[top] = calc & st[top];
			}
			else if(s[i][0] == '^')
			{
				calc = st[top --];
				st[top] = calc ^ st[top];
			}
			else st[top] = ~st[top];
		}
	}
	for(int i = 0 ; i < cnt ; i ++) putchar(st[1][i] + '0');
	return 0;
}
```

---

## 作者：cmll02 (赞：0)

调了一下午+一晚上终于过了，感谢 @zimujunqwq

首先思路是用栈把表达式的树建出来，然后加上奇奇怪怪的优化，但是会以 6s 多 T 掉 \#10。。。

由于复杂度是 $O(nm)$ 的，我们考虑 bitset 优化，所有询问一起处理，常数大幅缩小，可以过掉。

然而良心出题人赛后卡了空间，还是过不去。。

我们发现空间大在栈的 `std::bitset<100005> st[100005]`。

栈空间没法变小，只能让这个 `<100005>` 变小。

变小就 分段，分段，分段，然后『每一段』查询（雾

重复利用.jpg

$1000$ 个询问一分可以过。

Code:

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <assert.h>
#include <bitset>
#include <stdlib.h>
#include <iostream>
#define int unsigned long long
inline int read()
{
	int num = 0; char c = getchar();
	while (c<48 || c>57)c = getchar();
	while (c >= 48 && c <= 57)num = (num << 3) + (num << 1) + (c ^ 48), c = getchar();
	return num;
};
//std::stack<Node*> s;
int pos=0;
int m;std::bitset<1005> bs[64];
char c[100005][3];
std::bitset<1005> s[100005];
signed main()
{
	int n=read(),ans=0;
	for(int i=0;i<n;i++)scanf("%s",c[i]);
	m=read();
	for(int qaq=1;1000*qaq<=m;qaq++)
	{
		pos=0;
		for(int i=0;i<64;i++)bs[i]=0;
		for(int ii=0;ii<1000;ii++)
		{
			int a=read();
			for(int i=0;i<64;i++)if((a>>i)&1)bs[i][ii]=1;
		}
		for(int i=0;i<n;i++)
		{
			//puts("AL");
			if(c[i][1])
			{
				//Node *e;
				s[pos++]=bs[c[i][0]*10+c[i][1]-528];
			}
			else if(c[i][0]>47&&c[i][0]<58)
			{
				s[pos++]=bs[c[i][0]-48];
			}
			else
			{
				if(c[i][0]=='!')
				{
					s[pos-1]=~s[pos-1];
				}
				else
				{
					//Node *e;
					if(c[i][0]=='^')s[pos-2]=s[pos-2]^s[pos-1];
					if(c[i][0]=='&')s[pos-2]=s[pos-2]&s[pos-1];
					if(c[i][0]=='|')s[pos-2]=s[pos-2]|s[pos-1];
					pos--;
				}
			}
		}
		for(int i=0;i<1000;i++)printf("%d",s[0].test(i));
			
	}
	for(int i=0;i<64;i++)bs[i]=0;
	for(int ii=0;ii<m%1000;ii++)
	{
		int a=read();
		for(int i=0;i<64;i++)if((a>>i)&1)bs[i][ii]=1;
	}
	pos=0;
	for(int i=0;i<n;i++)
	{
		//puts("AL");
		if(c[i][1])
		{
			//Node *e;
			s[pos++]=bs[c[i][0]*10+c[i][1]-528];
		}
		else if(c[i][0]>47&&c[i][0]<58)
		{
			s[pos++]=bs[c[i][0]-48];
		}
		else
		{
			if(c[i][0]=='!')
			{
				s[pos-1]=~s[pos-1];
			}
			else
			{
				//Node *e;
				if(c[i][0]=='^')s[pos-2]=s[pos-2]^s[pos-1];
				if(c[i][0]=='&')s[pos-2]=s[pos-2]&s[pos-1];
				if(c[i][0]=='|')s[pos-2]=s[pos-2]|s[pos-1];
				pos--;
			}
		}
	}
	for(int i=0;i<m%1000;i++)printf("%d",s[0].test(i));
		

	//build(r);
	//printf("%lld\n",);
	return 0;
}
```

---

