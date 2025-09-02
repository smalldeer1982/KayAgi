# [ABC403F] Shortest One Formula

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc403/tasks/abc403_f

给定一个正整数 $N$。

请找出由字符 `1`、`+`、`*`、`(`、`)` 组成的数学表达式中，满足以下所有条件的最短表达式 $S$：
1. $S$ 符合以下 [BNF 语法](https://ja.wikipedia.org/wiki/%E3%83%90%E3%83%83%E3%82%AB%E3%82%B9%E3%83%BB%E3%83%8A%E3%82%A6%E3%82%A2%E8%A8%98%E6%B3%95) 中 `<expr>` 符号的定义
2. $S$ 表示的数学表达式计算结果等于 $N$

BNF 语法定义如下：

```
<expr>   ::= <term> | <expr> "+" <term>
<term>   ::= <factor> | <term> "*" <factor>
<factor> ::= <number> | "(" <expr> ")"
<number> ::= "1" | "1" <number> 
```

符合 `<expr>` 定义的表达式示例：
- `1111+111`：表示 $1111+111$
- `(1+1)*(1+1)`：表示 $(1+1)\times (1+1)$
- `(11+(1+1)*(1+1))+1`：表示 $(11+(1+1)\times (1+1))+1$

不符合 `<expr>` 定义的表达式示例：
- `(1+1)(1+1)`
- `1+2`
- `1-1`
- `1/1`
- `)1(`
- `1++1`
- `+1`
- `(+1)`
- `1*+1`

## 说明/提示

### 约束条件

- $1 \leq N \leq 2000$
- 输入均为整数

### 样例解释 #1

值为 $9$ 的表达式可能有多种形式，例如：
- `(1+1+1)*(1+1+1)`
- `1+1+1+1+1+1+1+1+1`
- `(1+1)*(1+1)*(1+1)+1`

其中 `(1+1+1)*(1+1+1)` 是最短的表达式。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
9```

### 输出

```
(1+1+1)*(1+1+1)```

## 样例 #2

### 输入

```
11```

### 输出

```
11```

## 样例 #3

### 输入

```
403```

### 输出

```
1+(1+1+1)*(1+11+11+111)```

# 题解

## 作者：chenxi2009 (赞：7)

## 思路
看到题解区代码都挺长的，我来发一发。

令 $f_i$ 为表示 $i$ 的最短字符串长度，$g_i$ 为表示 $i$ 的字符串中，最后一步运算不是加法（加了括号或只有一个数字也算）的最短字符串长度。

我们为每一种表达式中的符号设定转移方程：
- `1`：$f_1=g_1=1,f_{11}=g_{11}=2,f_{111}=g_{111}=3,f_{1111}=g_{1111}=4$；
- `+`：$f_i=\min\limits_{j=1}^{i-1} (f_j+f_{i-j}+1)$
- `*`：$f_i=g_i=\min\limits_{j\times k=i}(g_j+g_k+1)$
- `()`：$g_i=\min(g_i,f_i+2)$

然后我们就可以算出表示 $N$ 的字符串的最短长度了。

但是我们还要找出一个对应的字符串 $S$，所以我们还要记录 $ff_i$ 表示 $f_i$ **是从哪里来的**，$gf_i$ 记录 $g_i$ 是从哪里来的，输出的时候递归分类讨论。

具体分讨：
- 当前需要输出 $f_x$ 对应的字符串：
  - $x\in\{1,11,111,1111\}$，直接输出 $x$；
  - $f_x$ 来自于 $j,k$ 相加，先输出字符串 $f_j$，在输出加号，再输出字符串 $f_k$；
  - $f_x$ 来自于 $j,k$ 相乘，输出 $g_x$ 对应的字符串；
- 输出 $g_x$ 对应的字符串： 
  -  $x$ 由 $1$ 组成，直接输出；
  -  $g_x$ 由 $f_x$ 加上括号构成，先输出左括号，然后输出 $f_x$，再输出右括号；
  -  $g_x$ 由 $j,k$ 相乘得到，先输出 $g_j$，再输出乘号，再输出 $g_k$。

时间复杂度 $O(N^2)$，看转移式挺简单的不知道能不能做到 $O(N\log N)$ 呢。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[3000],g[3000],ff[3000],gf[3000];
void output(int x,int kind){
	if(kind){//输出 g[x]
		if(!gf[x]) printf("%d",x);//由 1 组成
		else if(gf[x] == x) printf("("),output(x,0),printf(")");//f[x] 加上括号得到
		else output(gf[x],1),printf("*"),output(x / gf[x],1);//相乘得到
	}
	else{//输出 f[x]
		if(ff[x] == x) printf("%d",x);//由 1 组成
		else if(!ff[x]) output(x,1);//相乘得到
		else output(ff[x],0),printf("+"),output(x - ff[x],0);//相加得到
	}
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++){
		if(i == 1) f[i] = g[i] = 1,ff[i] = 1,gf[i] = 0;
		else if(i == 11) f[i] = g[i] = 2,ff[i] = 11,gf[i] = 0;
		else if(i == 111) f[i] = g[i] = 3,ff[i] = 111,gf[i] = 0;
		else if(i == 1111) f[i] = g[i] = 4,ff[i] = 1111,gf[i] = 0;
		else{
			f[i] = 1e9;
			for(int j = 1;j < i;j ++) if(f[j] + f[i - j] + 1 < f[i]) f[i] = f[j] + f[i - j] + 1,ff[i] = j;//加法转移
			g[i] = f[i] + 2,gf[i] = i;//括号转移
			for(int j = 2;j < i;j ++) if(i % j == 0) if(g[j] + g[i / j] + 1 < g[i]) g[i] = g[j] + g[i / j] + 1,gf[i] = j;//乘法转移
			if(g[i] < f[i]) f[i] = g[i],ff[i] = 0;//f[x] 也有可能由乘法得到
		}
	}
	output(n,0);
	return 0;
}
```

---

## 作者：39xiemy (赞：3)

## 题目大意

给定一个数 $N$，构造一个只包含 `1`，`+`，`*`，`(`，`)` 的合法算数表达式，使其结果恰好为 $N$，并使其长度最短，输出一种构造方案。

## 分析

由于只有 `+` 和 `*` 两种运算符，所以一个数一定表示为两个数的和或两个数的积，因此可以枚举 $N$ 的所有因数和加数，然后递归并记忆化即可。特殊的，当 $N=1$ 或 $N=11$ 或 $N=111$ 或 $N=1111$ 时，应直接返回 $N$。

需要注意的是，当 $N=x\times y$ 时，若 $x,y$ 为某两个数的和，就需要加上左括号和右括号，再判断长度是否比当前答案更短。

时间复杂度为 $O(N^2)$，空间复杂度为 $O(N)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define mk make_pair
#define f1 first
#define s2 second
using namespace std;
int n;pair<string,string> sum[2002],ans;
//pair的第一个参数是和式的最短构造方案，第二个参数是乘积式的最短构造方案
inline pair<string,string> solve(int x)
{
	if(x==1) return mk("1","1");
	if(x==11) return mk("11","11");
	if(x==111) return mk("111","111");
	if(x==1111) return mk("1111","1111");
	if(sum[x].f1.size()) return sum[x];
	pair<string,string> t1,t2;int a=INT_MAX,b,c1,d1,c2,d2;string s,y,f;
	for(int i=2;i*i<=x;++i)
	{
		if(!(x%i))
		{
			t1=solve(i),t2=solve(x/i),c1=t1.f1.size(),d1=t1.s2.size(),c2=t2.f1.size(),d2=t2.s2.size();
			if(c1+2<=d1||!d1) b=c1+3,f='('+t1.f1+")*";//质数无法用乘积表示，故d1和d2有可能为0 
			else b=d1+1,f=t1.s2+'*';
			if(c2+2<=d2||!d2) b+=c2+2,f+='('+t2.f1+')';//若是和式，长度要加2 
			else b+=d2,f+=t2.s2;
			if(a>b) a=b,s=f;
		}
	}
	a=INT_MAX; 
	for(int i=1;i+i<=x;++i)
	{
		t1=solve(i),t2=solve(x-i),c1=t1.f1.size(),d1=t1.s2.size(),c2=t2.f1.size(),d2=t2.s2.size();
		if(c1<=d1||!d1) b=c1+1,f=t1.f1+'+';
		else b=d1+1,f=t1.s2+'+';//要把加号的长度计算在内 
		if(c2<=d2||!d2) b+=c2,f+=t2.f1;
		else b+=d2,f+=t2.s2;
		if(a>b) a=b,y=f;
	}
	sum[x]=mk(y,s);return sum[x]; 
}
signed main()
{
	cin>>n;ans=solve(n);
	if(ans.f1.size()<ans.s2.size()||!ans.s2.size()) cout<<ans.f1;
	else cout<<ans.s2;return 0;
}
```

---

## 作者：Inv_day_in_R (赞：2)

刚刚看这题时被题面吓到了，实际上赛后直接秒了。其实这道题可以用优先队列 bfs 解决（就像最短路里的 dijkstra 算法）。

设数字 $i$ 的最短表达式为 $dp_i$，但这样有一个问题，由于加完再乘需要加括号，所以把最后一次运算为加或乘分开考虑。所以设最后一次运算为加时数字 $i$ 的最短表达式为 $dp_{i,0}$，最后一次是乘号或没有运算过的数字 $i$ 的最短表达式为 $dp_{i,1}$。

一开始先将所有一连串的一放入优先队列：
```cpp
dp[1][1]="1";
dp[11][1]="11";
dp[111][1]="111";
dp[1111][1]="1111";
priority_queue<tuple<int,int,string,int>,vector<tuple<int,int,string,int>>,greater<tuple<int,int,string,int>>>q;
q.push({1,1,"1",1});
q.push({2,11,"11",1});
q.push({3,111,"111",1});
q.push({4,1111,"1111",1});
```
将每一次的队头拿出来，枚举所有 $n$ 以下的最短字符串，与队头运算。此时需要分类讨论加法或乘法，是否在 $n$ 以内，是否要加括号：
```cpp
while(q.size()){
	auto[x,y,s,last]=q.top();
	q.pop();
	if(vis[y][last])continue;
	vis[y][last]=1;
	if(y==n){
	    cout<<s<<endl;
	    return;
	}
	if(y<n){
	    for(int i=1;i<n;i++){
			if(y+i<=n&&dp[i][0].size()&&(dp[y+i][0].size()==0||dp[y+i][0].size()>dp[y][last].size()+dp[i][0].size()+1)){
				dp[y+i][0]=dp[y][last]+"+"+dp[i][0];
				q.push({dp[y+i][0].size(),y+i,dp[y+i][0],0});
			}
			if(y+i<=n&&dp[i][1].size()&&(dp[y+i][0].size()==0||dp[y+i][0].size()>dp[y][last].size()+dp[i][1].size()+1)){
				dp[y+i][0]=dp[y][last]+"+"+dp[i][1];
				q.push({dp[y+i][0].size(),y+i,dp[y+i][0],0});
			}
			if(last==0){//乘法，队头要加括号
				string S='('+s+')';
				if(y*i<=n&&dp[i][0].size()&&(dp[y*i][1].size()==0||dp[y*i][1].size()>S.size()+dp[i][0].size()+3)){
					dp[y*i][1]=S+"*("+dp[i][0]+")";
					q.push({dp[y*i][1].size(),y*i,dp[y*i][1],1});
				}
				if(y*i<=n&&dp[i][1].size()&&(dp[y*i][1].size()==0||dp[y*i][1].size()>S.size()+dp[i][1].size()+1)){
					dp[y*i][1]=S+"*"+dp[i][1];
					q.push({dp[y*i][1].size(),y*i,dp[y*i][1],1});
				}
			}
			else{//乘法，队头不加括号
				string S=s;
				if(y*i<=n&&dp[i][0].size()&&(dp[y*i][1].size()==0||dp[y*i][1].size()>S.size()+dp[i][0].size()+3)){
					dp[y*i][1]=S+"*("+dp[i][0]+")";
					q.push({dp[y*i][1].size(),y*i,dp[y*i][1],1});
				}
				if(y*i<=n&&dp[i][1].size()&&(dp[y*i][1].size()==0||dp[y*i][1].size()>S.size()+dp[i][1].size()+1)){
					dp[y*i][1]=S+"*"+dp[i][1];
					q.push({dp[y*i][1].size(),y*i,dp[y*i][1],1});
				}
			}
		}
	}
}
```
时间复杂度为 $O(n^2\log n)$，差不多能过。完整代码就不放了，把上面两端组合起来也差不多了。

---

## 作者：include13_fAKe (赞：2)

~~唐得没边的 dp 为啥机房只有我切了？~~

考虑 $O(n^2)$ 的 dp：每一个数的最优情况都可以从两个较小的数的 dp 值连接转移而来。

枚举使用乘法还是加法。dp 值要维护最后使用加法连接的和用乘法连接的最小答案。同时维护它是从哪两个数转移而来的，方便打印答案。

注意当且仅当外层乘法、内层加法时需要加括号。

最后递归打印答案即可。

注意点：

- $1$、$11$、$111$、$1111$ 都要初始化最小长度为其本身。
- 合理选择从加法连接转移而来还是从乘法连接转移而来，保证最终长度最小。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=2025;
int n;
int minlen1[N],l1[N],r1[N];	//使用乘法连接 
int minlen2[N],l2[N],r2[N];	//使用加法链接 
void write(int n,int style){
//	cout<<style<<endl;
	if(n==1||n==11||n==111||n==1111){
		cout<<n;
		return;
	}
	if(style==1){
		int lnxt=l1[n],rnxt=r1[n];
		if(minlen1[lnxt]<minlen2[lnxt]+2){
			write(lnxt,1);
		}
		else{
			cout<<'(';
			write(lnxt,2);
			cout<<')';
		}
		cout<<'*';
		if(minlen1[rnxt]<minlen2[rnxt]+2){
			write(rnxt,1);
		}
		else{
			cout<<'(';
			write(rnxt,2);
			cout<<')';
		}
	}
	else{
		int lnxt=l2[n],rnxt=r2[n];
		if(minlen1[lnxt]<minlen2[lnxt]){
			write(lnxt,1);
		}
		else{
//			cout<<'(';
			write(lnxt,2);
//			cout<<')';
		}
		cout<<'+';
		if(minlen1[rnxt]<minlen2[rnxt]){
			write(rnxt,1);
		}
		else{
//			cout<<'(';
			write(rnxt,2);
//			cout<<')';
		}
	}
	return;
}
signed main(){
	cin>>n;
	memset(minlen1,0x3f,sizeof(minlen1));
	memset(minlen2,0x3f,sizeof(minlen2));
	minlen1[1]=minlen2[1]=1;
	minlen1[11]=minlen2[11]=2;
	minlen1[111]=minlen2[111]=3;
	minlen1[1111]=minlen2[1111]=4;	//首先是不拼接的情况 
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++){
			int k=i-j;
			if(min(minlen1[j],minlen2[j])+min(minlen1[k],minlen2[k])+1<minlen2[i]){
				minlen2[i]=min(minlen1[j],minlen2[j])+min(minlen1[k],minlen2[k])+1;
				l2[i]=j,r2[i]=k;
			} 
		}
		for(int j=1;j<=i;j++){
			int k=i/j;
			if(j*k!=i)	continue;
			if(min(minlen1[j],minlen2[j]+2)+min(minlen1[k],minlen2[k]+2)+1<minlen1[i]){
				minlen1[i]=min(minlen1[j],minlen2[j]+2)+min(minlen1[k],minlen2[k]+2)+1;
				l1[i]=j,r1[i]=k;
			}
		}
	} //1+(1+1+1)*(1+11+11+111)
//	cout<<minlen2[403]<<endl;
	if(minlen1[n]<minlen2[n])	write(n,1);
	else	write(n,2);
	return 0;
}//ABC403F 
```

---

## 作者：kkxacj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc403_f) 

差点被 `E` 题肘死了，还好后面两个题极限翻回去。

#### 思路

很自然的想到我们要求 $f_i$ 表示第 $i$ 个表示出来最小长度。

当然，有四个数是固定的，分别是 $1,11,111,1111$，这个原因很显然。

$i$ 可以通过两个数加起来或乘起来表示出来，不过你会发现一个问题，在进行乘法时需要打括号！

若以将式子设为 $f_{i,0/1}$ 表示第 $i$ 个数是否支持乘一个数不加括号，转移就很好搞了，枚举两种操作分别用的数即可，具体转移看代码。

**code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1 == p2 && (p2 = (p1 = buf1) + fread(buf1, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf1[1 << 23], *p1 = buf1, *p2 = buf1, ubuf[1 << 23], *u = ubuf;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 2010;
int n,o,o1;
string s,f[N][2];
signed main()
{
	read(n);
	for(int i = 1;i <= 1000;i++) s += "*";
	for(int i = 1;i <= 2000;i++) f[i][0] = f[i][1] = s;
	f[1][0] = f[1][1] = "1";
	f[11][0] = f[11][1] = "11";
	f[111][0] = f[111][1] = "111";
	f[1111][0] = f[1111][1] = "1111";//初值 
	for(int i = 2;i <= 2000;i++)
	{
		if(f[i][0].size() <= 4) continue;
		o = o1 = 0;
		for(int j = 1;j < i;j++)
			if(o == 0 || o1 > min(f[j][1].size(),f[j][0].size())+1+min(f[i-j][1].size(),f[i-j][0].size())) 
				o = j,o1 = min(f[j][1].size(),f[j][0].size())+1+min(f[i-j][1].size(),f[i-j][0].size());
		//加法有无括号都可 
		if(f[o][1].size() < f[o][0].size()) f[i][0] = f[o][1];
		else f[i][0] = f[o][0];
		f[i][0] += "+";
		if(f[i-o][1].size() < f[i-o][0].size()) f[i][0] += f[i-o][1];
		else f[i][0] += f[i-o][0];
		o = o1 = 0;
		for(int j = 2;j < i;j++)
			if(i%j==0)
			{
			if(o == 0 || o1 > min(f[j][1].size(),f[j][0].size()+2)+1+min(f[i/j][1].size(),f[i/j][0].size()+2)) 
				o = j,o1 = min(f[j][1].size(),f[j][0].size()+2)+1+min(f[i/j][1].size(),f[i/j][0].size()+2);
			}
		if(o)
		{
			if(f[o][1].size() < f[o][0].size()+2) f[i][1] = f[o][1];//看哪个小 
			else f[i][1] = "("+f[o][0]+")";
			f[i][1] += "*";
			if(f[i/o][1].size() < f[i/o][0].size()+2) f[i][1] += f[i/o][1];
			else f[i][1] += "("+f[i/o][0]+")";
		}
	}
	if(f[n][0].size() < f[n][1].size()) cout<<f[n][0];
	else cout<<f[n][1];
	return 0;
}
/*
每个数肯定都有最小表示
f_(i*j) = f_{i}*f_{j}
f_(i+j) = f_{i}+f_{j} 
(1+1+1+1+1+1) 
(1+1)*(1+1+1)
*/
```

---

## 作者：qwqerty (赞：1)

# 解题思路
~~这是一篇使用了 `string dp` 的题解。~~  
细节挺多的感觉，调了好久。   
让我们暴力点想，这题的 $N$ 才 $2000$，所以 $O(N^2)$ 是可以过的。  
考虑动态规划，分两种情况讨论：
- 加法：将 $N$ 表示为某两个数之和，可以先枚举第一个数，再算出另一个数并算出它们长度之和加一（也就是中间的 `+`）的最小值。
- 乘法：将 $N$ 表示为某两个数的乘积，按照一样的思路枚举其中的一个数，计算出另一个数并算出它们长度的最小值。注意特判，若 $N$ 是表示为两个数之和，则要加括号。

直接转移即可。
# AC 代码
我的这份代码常数巨大，赛时不知道怎么想的写出了这份逆天代码，反正能过就完了。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
string dp[2005];
bool check(string x) {
	int f = 0;
	for (char ch : x) {
		if (ch == '(') f++;
		else if (ch == ')') f--;
		if (f == 0 && ch == '+') return 0;
	}
	return 1;
} 
signed main() {
	dp[1] = "1";
	dp[11] = "11";
	dp[111] = "111";
	dp[1111] = "1111";
	cin >> n;
	for (int i = 2; i <= n; i++) {
		if (i == 11 || i == 111 || i == 1111) continue;
		int minsize = LLONG_MAX;
		string ans;
		for (int j = i - 1; j >= 1; j--) {
			if (dp[i - j].size() + 1 + dp[j].size() < minsize) {
				minsize = dp[i - j].size() + 1 + dp[j].size();
				ans = dp[i - j] + "+" + dp[j];
			}
		}
		for (int j = i / 2; j >= 2; j--) {
			if (i % j == 0) {
				int size_;
				if (check(dp[i / j]) && check(dp[j])) {
					size_ = dp[i / j].size() + 1 + dp[j].size();
					if (size_ < minsize) {
						minsize = size_;
						ans = dp[i / j] + "*" + dp[j];
					} 
				} else if (check(dp[i / j]) && !check(dp[j])) {
					size_ = dp[i / j].size() + 3 + dp[j].size();
					if (size_ < minsize) {
						minsize = size_;
						ans = dp[i / j] + "*(" + dp[j] + ")";
					}
				} else if (!check(dp[i / j]) && check(dp[j])) {
					size_ = dp[i / j].size() + 3 + dp[j].size();
					if (size_ < minsize) {
						minsize = size_;
						ans = "(" + dp[i / j] + ")*" + dp[j];
					}					
				} else {
					size_ = dp[i / j].size() + 5 + dp[j].size();
					if (size_ < minsize) {
						minsize = size_;
						ans = "(" + dp[i / j] + ")*(" + dp[j] + ")"; 
					}
				}
			}
		}
		dp[i] = ans;
	}
	cout << dp[n]; 
	return 0;
}
```

---

## 作者：lihaochen123 (赞：1)

### 题意

用一个只包含 `+`、`*`、`1`、`(` 和 `)` 的表达式表示出 $N$，求最短的满足条件的表达式。

### 思路

DP。

定义 $f_i$ 为能凑出 $i$ 的最短的表达式。$g_i$ 为能凑出 $i$ 的且优先级比 `+` 高的最短的表达式，$\min$ 表示多个字符串中长度最短的，$\circ$ 表示字符串拼接，$\texttt{+}$ 表示 `+` 这个字符串，$\texttt{*},\texttt{(},\texttt{)}$ 的定义与上面类似。

- 对于加法，$f_i=\min\limits_{1 \leq j < i}\{f_i \circ \texttt{+} \circ g_{i-j}\}$。
- 对于乘法，则 $g_i=\min\limits_{1 < j < i,j | i}\{g_i \circ \texttt{*} \circ g_{\frac{i}{j}}\}$。
- 最后，根据 $f,g$ 的定义，$f_i=\min\{f_i,g_i\},g_i=\min\{\texttt{(} \circ f_i \circ \texttt{)}\}$。

我们可以将 $N$ 表示为二进制的形式，例如 `6=(1*(1+1)+1)*(1+1)`，此时表达式的长度是 $O(\log N)$ 的，根据 $f_i,g_i$ 的定义，$f_i,g_i$ 的上界是 $O(\log N)$ 的，则时间复杂度为 $O(N^2 \log N)$。

[code](https://atcoder.jp/contests/abc403/submissions/65301871)

---

## 作者：Halberd_Cease (赞：1)

题目允许 $O(n^2)$ 做法通过，那直接 dp 就可以了。

考虑到加法和乘法的优先级不同，我们分开来设 dp 状态，即 $dp_{0/1,i}$ 表示最后一次操作分别是加法还是乘法，凑出 $i$ 需要多少个字符。

转移有两种，一种是加法转移，一种是乘法转移。

加法就是枚举 $j\in[1,i-1]$，然后和 $\min(dp_{0,j},dp_{1,j})+\min(dp_{0,i-j},dp_{1,i-j})$ 取最小值存在 $dp_{0,i}$ 中。因为加法运算优先级不高，所以不用加括号。

乘法转移需要考虑多一点，枚举 $i$ 的因数 $j$，因为优先级的原因，最后一次操作是加法的需要额外加括号，所以应该和 $\min(dp_{0,j}+2,dp_{1,j})+\min(dp_{0,\frac ij}+2,dp_{1,\frac ij})$ 取最小值放在 $dp_{1,i}$ 中。

初始状态可以将 $1,11,111,1111$ 放在对应的 $dp_{1,i}$ 中，因为 $dp_{1,i}$ 使用优先级比 $dp_{0,i}$ 高。

输出方案就直接 dp 的时候存一个最优答案对应的字符串就可以了。

[submission](https://atcoder.jp/contests/abc403/submissions/65288042)

---

## 作者：ZZ0520 (赞：1)

## 题目大意

给定一个数 $N$，构造一个只包含 `1`，`+`，`*`，`(`，`)` 的合法算数表达式，使其结果恰好为 $N$，并使其长度最短，输出一种构造方案。

## 思路

-   用 `dp[i]` 表示数字 $i$ 的最短字符串是什么，`g[i]` 表示数字 $i$ 的字符串能否直接用于乘法（即不需要加括号）。

-   对于加法：`dp[i]`$=$`dp[j]`$+$`'+'`$+$`dp[i-j]`。

-   对于乘法：`dp[i]`$=$`dp[j]`$+$`'*'`$+$`dp[i-j]`。

-   注意：乘法的 `dp[j]` 和 `dp[i-1]` 前后需要根据情况加括号，是否加括号，可以取决于其之前是否是由乘法运算得来，如果是乘法运算得来，肯定可以直接用于乘法运算，所以我们需要辅助数组 `g[i]` 来表示数字 $i$ 是否可以直接用于乘法运算。

-   固定的：当 $N$ 为 $1$，$11$，$111$，$1111$ 时，直接返回 $N$。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e3+5;
int g[N];
/*
	dp[i] -> 数字i的字符串长什么样
	g[i] -> 数字i的字符串有没有括号
*/
int main(){
	int m=2009;
	vector<string> dp(m,string(2 * m,'!'));
	dp[1]="1"; 
    dp[11]="11"; 
    dp[111]="111"; 
    dp[1111]="1111";
	g[1]=g[11]=g[111]=g[1111]=1;
	for(int i=2;i<m;i++){
		if(i==11||i==111||i==1111){
			continue;
        }
		for(int j=1;i-j>=1;j++){
			if(dp[j].size()+dp[i-j].size()+1<dp[i].size()){
				dp[i]=dp[j]+"+"+dp[i-j];
			}
		}
		for (int j=2;j*j<=i;j++){
			if(i%j==0){
				if(dp[j].size()+dp[i/j].size()+1+2*!g[j]+2*!g[i/j]<=dp[i].size()){
					string cur;
					if(g[j]==0) cur+="(";
					cur+=dp[j];
					if(g[j]==0) cur+=")";
					cur+="*";
					if(g[i/j]==0) cur+="(";
					cur+=dp[i/j];
					if(g[i/j]==0) cur+=")";
					dp[i]=cur;
					g[i]=1;
				}
			}
		}
	}
	int n;
	cin>>n;
	cout<<dp[n]<<endl;
    return 0;
}
```

---

## 作者：cheng2010 (赞：1)

打题时被自己唐死了。

首先拿到题感觉似乎不太可做，但看到 $n \le 2000$ 果断暴搜。

首先肯定要记忆化。

我们定义 $f(x)$ 为组成 $x$ 的最短字符串，在搜索中先找加再找积，然后取 $\min$，于是很容易可以写出代码：

```cpp

bz[1]="1";
bz[11]="11";
bz[111]="111";
bz[1111]="1111";

string dfs(int x)
{
	if(bz[x]!="\0") return bz[x];
	if(f[x]!="\0") return f[x];
	string res="\0";
	for(int i=1;i<x;i++) res=cmp(res,dfs(i)+'+'+dfs(x-i));
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
			res=cmp(res,'('+dfs(i)+')'+'*'+'('+dfs(x/i)+')');
	return f[x]=res;
}
```

~~然后就发现 WA 了。~~

想想为什么？

我们发现有一个 bug 就是在乘的时候我们加了两个括号！这就导致加了两个括号后长度加了 $2$ 使得答案变劣。

比如：

```
987=11+(1+1)*(1+1+1+1)*(11+111)=11+(1+1+1+1)*(11+11+111+111)
```

它们的区别就是对 $244$ 的分解。

```
244=(1+1)*(11+111)=11+11+111+111
```

对 $244$ 而言，显然后者更优，但对于 $987$ 就是前者，这就是括号的问题。

那该怎么办？我们只用加一维：$f(x,pos)$ 表示外层是否有括号，这样在加时添上括号即可，于是有了最终代码：

```cpp
inline string dfs(int x,bool pos)
{
	if(bz[x]!="\0") return bz[x];
	if(f[x][pos]!="\0") return f[x][pos];
	string res="\0";
	if(pos)
	{
		for(int i=1;i<x;i++) res=cmp(res,'('+dfs(i,0)+'+'+dfs(x-i,0)+')');
	}
	else
	{
		for(int i=1;i<x;i++) res=cmp(res,dfs(i,0)+'+'+dfs(x-i,0));
	}
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
			res=cmp(res,dfs(i,1)+'*'+dfs(x/i,1));
	return f[x][pos]=res;
}
```

时间应该是 $O(n^2)$ 的。

---

## 作者：Double_Light (赞：1)

发现 $n\leq2000$，考虑暴力 DP。

设 $f_i$ 表示 $i$ 最少需要的 BNF 式子的长度。我们同时在转移过程中能够记录下这个式子。

那么我们可以枚举 $1\leq j<i$ 的 $j$，用 $f_j$ 更新 $f_i$。

具体地，枚举 $j$，判断 $f_j$ 对应的这个式子是否全是 $1$，如果是，可以在 $j$ 的式子后面加上一个 $1$。

如果 $i$ 能被 $j$ 整除，用 $j$ 的式子和 $\dfrac{i}{j}$ 的式子相乘，注意记录式子有没有加号，这决定了乘法要不要加括号。

用 $j$ 的式子和 $i-j$ 的式子相加，去更新 $f_i$。

注意上面的顺序不能调换。

```cpp
#include<iostream>
#include<map>
using namespace std;
int n;
int dp[2005];
map<int,string>m;
int jia[2005];
int main(){
	cin>>n;
	dp[1]=1;m[1]="1";
	for(int i=2;i<=n;i++){
		dp[i]=1e9;
		for(int j=1;j<i;j++){
			if(j*10+1==i&&!jia[j]&&dp[j]+1<dp[i]){//直接加 1
				int f=1;
				for(int k=0;k<m[j].size();k++){
					if(m[j][k]!='1')f=0;
				}
				if(f){
					dp[i]=dp[j]+1;
					m[i]=m[j]+"1";
					jia[i]=0;
				}
			}
			if(i%j==0&&dp[j]+dp[i/j]+jia[j]*2+jia[i/j]*2+1<dp[i]){//两个式子相乘
				dp[i]=dp[j]+dp[i/j]+jia[j]*2+jia[i/j]*2+1;
				m[i]="";
				if(jia[j])m[i]="(";
				m[i]+=m[j];
				if(jia[j])m[i]+=")";
				m[i]+="*";
				if(jia[i/j])m[i]+="(";
				m[i]+=m[i/j];
				if(jia[i/j])m[i]+=")";
				jia[i]=0;
			}
			if(dp[j]+dp[i-j]+1<dp[i]){//两个式子相加
				dp[i]=dp[j]+dp[i-j]+1;
				m[i]=m[j]+"+"+m[i-j];
				jia[i]=1;
			}
		}
	}
	cout<<m[n]<<endl;
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

题意：给一个数 $n$，现在要找到一个长度最短的“expr”表达式，使得这个表达式的值为 $n$。     
一些定义如下：     

- number 表达式：形如 `111...111`（一串 $1$）的表达式叫做 number 表达式。
- factor 表达式：形如 `<number>` 或 `(<expr>)`（一个 expr 表达式外面加了一对括号，使得它变成了一个整体）的表达式叫做 factor 表达式。
- term 表达式：形如 `<factor>*<factor>*...*<factor>*<factor>`（一串 factor 表达式中间加了 `*` 号）的表达式叫做 term 表达式。单独一个 factor 表达式也是 term 表达式。
- expr 表达式：形如 `<term>+<term>+...+<term>+<term>`（一串 term 表达式中间加了 `+` 号）的表达式叫做 expr 表达式。单独一个 term 表达式也是 expr 表达式。

说人话，这个“expr”表达式就是一个普通的正则表达式，但是只由 `1,(,),+,*` 这 $5$ 种符号组成。    

这个 $n \le 2000$，提示我们这道题可以 $O(n^2)$ 解决。   
我们考虑 DP，$f_{i,0/1}$ 表示当前表达式的值为 $i$，它是否是 term 表达式（即参与合并的时候是否必须加括号来维护计算优先级）的情况下的表达式最短长度。   
我们有如下的转移方程：
$$\begin{cases}
  f_{i,0}=\min(\min(f_{j,0},f_{j,1})+\min(f_{i-j,0},f_{i-j,1})+1) \\
  f_{i,1}=\min(\min(f_{j,0}+2,f_{j,1})+\min(f_{i/j,0}+2,f_{i/j,1})+1) \\
\end{cases}$$   

显然在转移 $f_{i,1}$ 的时候要满足 $j \mid i$。  
解释一下，term 表达式是由 `*` 号连接的，因此如果要把一个 expr 表达式（非 term 表达式，即里面有 `+` 号）加入到这个 `term` 表达式内，那么必须要在外面添一对括号。而对于一个本来就是 term 表达式的东西，只需要把它加到后面即可，不需要额外添加字符。   
而对于 expr（非 term）表达式，运算优先级不受影响，只需要直接把表达式添到后面即可。    
DP 的时候顺便记录它的上一个状态，输出答案的时候从最终状态往回 DFS，就可以输出这个表达式。   

代码中的 $f_{i,0/1}$ 意义和上文相反，别看反了。  
```cpp
#include<stdio.h>
#include<string.h>
int n,f[2005][2],lst[2005][2][5];
int min(int a,int b){return a<b?a:b;}
void dfs(int num,int typ)
{
	if(!lst[num][typ][1]) {printf("%d",num);return;}
	if(!typ&&lst[num][typ][2]) printf("(");
	dfs(lst[num][typ][1],lst[num][typ][2]);
	if(!typ&&lst[num][typ][2]) printf(")");
	if(typ) printf("+");else printf("*");
	if(!typ&&lst[num][typ][3]) printf("(");
	if(typ) dfs(num-lst[num][typ][1],lst[num][typ][3]);
	else dfs(num/lst[num][typ][1],lst[num][typ][3]);
	if(!typ&&lst[num][typ][3]) printf(")");
}
int main()
{
	scanf("%d",&n),memset(f,0x3f,sizeof(f)),
	f[1][0]=1,f[11][0]=2,f[111][0]=3,f[1111][0]=4;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++) if(f[i][1]>min(f[j][0],
		f[j][1])+min(f[i-j][0],f[i-j][1])+1)
		{
			f[i][1]=min(f[j][0],f[j][1])+min(f[i-j][0],f[i-j][1])+1,
			lst[i][1][1]=j,lst[i][1][2]=(f[j][1]<f[j][0]),
			lst[i][1][3]=(f[i-j][1]<f[i-j][0]);
		}
		for(int j=2;j<i;j++) if(i%j==0&&f[i][0]>
		min(f[j][0],f[j][1]+2)+min(f[i/j][0],f[i/j][1]+2)+1)
		{
			f[i][0]=min(f[j][0],f[j][1]+2)+min(f[i/j][0],f[i/j][1]+2)+1;
			lst[i][0][1]=j,lst[i][0][2]=(f[j][1]+2<f[j][0]),
			lst[i][0][3]=(f[i/j][1]+2<f[i/j][0]);
		}
	}if(f[n][0]<f[n][1]) dfs(n,0);else dfs(n,1);
}
```

---

## 作者：Dtw_ (赞：0)

## 题意
给你 $n$，问你是否可以用只含 $1$ 和 `+ * ()` 的式子表示出 $n$，求最短的方案。

$n\leq 2000$。
## Solution
考虑一个数肯定由一些数拼起来，但是我们只需要算两个拼起来，因为一些数拼起来可以转换成两个拼起来。

所以当前这个数要么由两个数加起来，要么由两个数乘起来。加法无所谓，但是乘法的话如果里面有加法就得打括号。

所以设 $f_{i,0/1}$ 表示凑出 $i$ 来式子外头有/没有加号的最短长度。

转移就是枚举 $j$：

$$\begin{cases}
 f_{i, 1} = \min(\min(f_{j,0},f_{j,1}) + \min(f_{i-j,0},f_{i-j,1})) + 1 \\
f_{i,0} = \min(\min(f_{j,0},f_{j,1} + 2) + \min(f_{\frac{i}{j},0},f_{\frac{i}{j},1} + 2))+1
\end{cases}$$

然后我们用 $pre_{i,0/1}$ 分别记录他们的 $f$ 值是从哪里转移过来的。

具体可以开个结构体分别存一下，然后就 dfs 找方案。

当找到全是 $1$ 的数时直接结束就行。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 2e3 + 10, inf = 0x3f3f3f3f;

int n, f[N][2];
struct node { int a, b, c, d; } pre[N][2];
map<pair<int, int>, string> mp;
map<pair<int, int>, bool> v;
bool vis[N];

string dfs(int i, int j)
{
    if (v[{i, j}]) return mp[{i, j}];
    if (vis[i]) {
        int x = i; string s;
        while (x) {
            s += (x % 10) + '0';
            x /= 10;
        }
        return s;
    }
    string t = "";
    if (!j && pre[i][j].b) t = "(";
    t += dfs(pre[i][j].a, pre[i][j].b);
    if (!j && pre[i][j].b) t += ")";
    if (!j) t += "*";
    else t += "+";
    if (!j && pre[i][j].d) t += "(";
    t += dfs(pre[i][j].c, pre[i][j].d);
    if (!j && pre[i][j].d) t += ")";
    v[{i, j}] = 1;
    mp[{i, j}] = t;
    return t;
}

int main()
{
    fst
    cin >> n;
    memset(f, inf, sizeof f);
    for (int i = 1; i <= n; i++) {
        int x = i, c = 0; bool ok = 1;
        while (x) {
            if (x % 10 != 1) ok = 0;
            c++; x /= 10;
        }
        if (ok) f[i][0] = f[i][1] = c, vis[i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            int x = f[i][1], y = min(f[j][0], f[j][1]) + min(f[i - j][0], f[i - j][1]) + 1;
            if (x > y) {
                f[i][1] = y;
                if (f[j][0] > f[j][1]) pre[i][1].a = j, pre[i][1].b = 1;
                else pre[i][1].a = j, pre[i][1].b = 0;
                if (f[i - j][0] > f[i - j][1]) pre[i][1].c = i - j, pre[i][1].d = 1;
                else pre[i][1].c = i - j, pre[i][1].d = 0;
            }
            if (i % j == 0) {
                int b = i / j;
                int x = f[i][0], y = min(f[j][0], f[j][1] + 2) + min(f[b][0], f[b][1] + 2) + 1;
                if (x > y) {
                    f[i][0] = y;
                    if (f[j][0] > f[j][1] + 2) pre[i][0].a = j, pre[i][0].b = 1;
                    else pre[i][0].a = j, pre[i][0].b = 0;
                    if (f[b][0] > f[b][1] + 2) pre[i][0].c = b, pre[i][0].d = 1;
                    else pre[i][0].c = b, pre[i][0].d = 0;
                }
            }
        }
    }
    if (f[n][0] > f[n][1]) cout << dfs(n, 1);
    else cout << dfs(n, 0);
    return 0;
}
```

---

