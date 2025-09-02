# [ARC109C] Large RPS Tournament

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc109/tasks/arc109_c

最強のじゃんけんの手を決めるため、トーナメント形式のじゃんけん大会が開催されます。 大会の参加者は $ 2^k $ 人で、それぞれ $ 0 $ 以上 $ 2^k $ 未満の整数が振られています。どの参加者もそれぞれ得意な手を持っていて、毎試合得意な手のみを出します。

参加者の得意な手は、長さ $ n $ の `R`, `P`, `S` からなる文字列 $ s $ によって表されます。 具体的には、番号 $ i $ の参加者の得意な手は $ s $ の $ (i\text{\ mod\ }\ n)\ +\ 1 $ 文字目の文字で表されます。ここで、`R` はグー、`P` はパー、`S` はチョキを表します。

$ r-l $ が $ 2 $ のべき乗であるような $ l,\ r $ について、番号が $ l $ 以上 $ r $ 未満の参加者による大会を開いたとき、勝者は次のようにして決定されます。

- $ r-l=1 $ であるとき（つまり、参加者がただ一人であるとき）、勝者は $ l $ とする。
- $ r-l\geq\ 2 $ であるとき、$ m=(l+r)/2 $ として、$ l $ 以上 $ m $ 未満の参加者による大会と、$ m $ 以上 $ r $ 未満の参加者による大会を開催する。それぞれの勝者が $ a,\ b $ であるとき、$ a $ と $ b $ がじゃんけんをして勝ったほうを勝者とする。あいこの場合 $ a $ を勝者とする。

番号が $ 0 $ 以上 $ 2^k $ 未満の参加者による大会の勝者の得意な手を求めてください。

## 说明/提示

### 注意

- $ a\text{\ mod\ }\ b $ は $ a $ を $ b $ で割ったあまりを表す
- じゃんけんの勝敗は次のように決められる
  - 同じ手同士はあいこである
  - `R` は `S` に勝つ
  - `P` は `R` に勝つ
  - `S` は `P` に勝つ

### 制約

- $ 1\ \leq\ n,k\ \leq\ 100 $
- $ s $ は `R`, `P`, `S` のみからなる長さ $ n $ の文字列

### Sample Explanation 1

\- 番号が $ 0 $ 以上 $ 2 $ 未満の参加者による大会の勝者の得意な手は `P` です。 - 番号が $ 2 $ 以上 $ 4 $ 未満の参加者による大会の勝者の得意な手は `R` です。 - 番号が $ 0 $ 以上 $ 4 $ 未満の参加者による大会の勝者の得意な手は `P` です。 よって、答えは `P` となります。 ``` P ┌─┴─┐ P R ┌┴┐ ┌┴┐ R P S R ```

## 样例 #1

### 输入

```
3 2
RPS```

### 输出

```
P```

## 样例 #2

### 输入

```
11 1
RPSSPRSPPRS```

### 输出

```
P```

## 样例 #3

### 输入

```
1 100
S```

### 输出

```
S```

# 题解

## 作者：XYQ_102 (赞：3)

## 题意

$2^k$ 个人玩石头剪刀布，他们站成一排，按照序号两两比赛，胜者进入下一轮，最后决出一个冠军。

所有人在所有比赛中都会固定出石头剪刀布的一个，而且，他们每个人出哪一个的偏好如果按照序号排成序列，是一个循环的序列，而且循环节很有限，不会超过 $m$。

## 思路
按照比赛次序一层一层处理，处理出下一次比赛中，站在不同位置选手的出石头剪刀布的情况，由于每个人出什么是循环的，所以每行只需要考虑序号最前的，等同于循环节两倍的选手，得到在下一层中，一个新的循环节。

再想想，实际上树的每一层都是以等长的循环节循环的，不妨假设这棵树高度无限，叶子节点数目也无限，我们要求的实际上是一棵子树的根节点。

## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	char win[222][222];
	win['R']['R']=win['R']['S']=win['S']['R']='R';
	win['S']['S']=win['S']['P']=win['P']['S']='S';
	win['P']['P']=win['P']['R']=win['R']['P']='P';
	int n,m;
	string s;
	cin>>n>>m>>s;
	while(m--) 
	{
		string t=s+s;
		for (int i=0;i<n;i++) 
			s[i]=win[t[i*2]][t[i*2+1]];
	}
	cout<<s[0]<<"\n";
	return 0;
}
```

---

## 作者：Mingrui_Yang (赞：2)

## 题意

有 $2^k$ 个玩家进行比赛。给定一个长度为 $n$ 且仅由 `RPS` 组成的字符串 $s$，玩家 $i$ 的手牌是 $s$ 中的第 $((i\bmod n) + 1)$ 个字符。   

比赛的举行方式是，选定 $l$ 和 $r$，在玩家 $l$ 到 玩家 $r - 1$ 之间进行比赛（$r - l$ 必须满足为 $2$ 的次幂）。 

比赛规则如下：

- 如果 $r - l = 1$，则 $l$ 胜出。
- 如果 $r - l \ge 2$，令 $m = (l + r) / 2$。分两部分举行比赛，第一部分为 $l$ 至 $m - 1$ 之间的玩家，第二部分为 $m$ 至 $r - 1$，胜出者再进行石头剪刀布


石头剪刀布的规则（`R` 为石头，`P` 为布，`S` 为剪刀）：

- `R` 胜 `S`
- `P` 胜 `R`
- `S` 胜 `P`

求玩家 $0$ 至玩家 $2^k$ 的胜出者的手牌。

## 思路

考虑 DP。

因为 $r - l$ 一定是 $2$ 的次幂，所以考虑倍增。

令 $f_{i, k}$ 表示从玩家 $i$ 开始，连续 $2^k$ 个玩家中的胜出者的手牌。   

转移比较容易，本质是搜索，记得加上记忆化，详见代码。

注意预处理 $2$ 的次幂，模上 $n$。

## CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int n, k;
int f[N][N];
char s[N];
int pow2[N];
void init() { // 预处理 
	pow2[0] = 1;
	for (int i = 1; i < 110; i ++ ) pow2[i] = pow2[i - 1] * 2 % n;
}
int dfs(int now, int k) {
	if (k == 0) { // r - l == 1 的情况 
		if (s[now] == 'R') return 1;
		else if (s[now] == 'P') return 2;
		else if (s[now] == 'S') return 3; 
	}
	if (f[now][k]) return f[now][k]; // 记忆化搜索 
	
	int l = dfs(now, k - 1), r = dfs((now + pow2[k - 1]) % n, k - 1); // 左右部分的胜出者 
	
	int x; // 本次胜出者 
	
	// 进行石头剪刀布 
	if (l == 1)
		if (r == 2) x = r;
		else x = l;
	else if (l == 2)
		if (r == 3) x = r;
		else x = l;
	else if (l == 3)
		if (r == 1) x = r;
		else x = l;
	
	// 记忆化 
	return f[now][k] = x;
}
signed main() {
	cin >> n >> k >> s;
	init();
	int t = dfs(0, k);
	if (t == 1) puts("R");
	else if (t == 2) puts("P");
	else if (t == 3) puts("S");
	return 0;
}
```


---

## 作者：leixinranYY (赞：1)

## 题意
求 $0$ 到 $2^k$ 获胜的那个人那个人的手牌。玩家 $i$ 的手牌是 $s$ 中的第 $((i \bmod n)+1)$ 张手牌。
## 思路
据推理知道每分一次组都会出现一个赢家，而且每个人出手牌的顺序都是循环的，所以只需要处理序列中的一段计算赢家即可。

计算赢家就定义一个 $w$ 的二维字符数组，存一下对应的赢家就行了。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char w[222][222];
string s;
int n,m;
int main()
{
    //赢家
	w['R']['R']=w['R']['S']=w['S']['R']='R';
	w['S']['S']=w['S']['P']=w['P']['S']='S';
	w['P']['P']=w['P']['R']=w['R']['P']='P';
	cin>>n>>m>>s;
	while(m--) 
	{
		string t=s+s;
		for(int i=0;i<n;i++) 
			s[i]=w[t[i*2]][t[i*2+1]];
	}
	cout<<s[0]<<"\n";
    //完结散花
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/197139359)

---

## 作者：DgNeHzL7777 (赞：1)

## 题意
题目翻译仅限于理解能力强的选手，对于和我一样理解能力差的选手，画个图应该会更好理解。（以样例一为例）
(字不是很好看请见谅)

![图片](https://cdn.luogu.com.cn/upload/image_hosting/if63gp1j.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


所以输出的是 $\texttt{P}$。

## 思路

很显然，每个人出拳的序列是**循环**的。而且，我们还可以发现，一轮结束之后，上一轮胜出的那些人的出拳序列也是**循环**的。

给个图应该会更好理解。（还是以样例一为例）

![图片](https://cdn.luogu.com.cn/upload/image_hosting/mwufukxt.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

## 具体实施

因为当前这一轮所有人的出拳序列是循环的，我们只需要处理这个序列中的一段就可以了。

1. 我们把两个循环节拼起来，然后看哪些人赢了，把赢的人出的拳存到一个字符串中。

2. 刚才那个字符串就是新的循环节，我们再执行一次操作1，操作1一共执行   $k$   次。

## 代码部分

为了知道两个人中到底是谁赢了，我们需要写一个函数。
```
char winner(char p1,char p2){
	if(p1==p2) return p1;
	//比如样例3，所有人出的拳都是一样的，所以我们特判。
	//我们需要处理的是所出的拳，所以返回p1和返回p2本质上是一样的 
	if(p1=='R'&&p2=='S') return 'R';
	if(p1=='P'&&p2=='R') return 'P';
	if(p1=='S'&&p2=='P') return 'S';
	if(p1=='S'&&p2=='R') return 'R';
	if(p1=='R'&&p2=='P') return 'P';
	if(p1=='P'&&p2=='S') return 'S';
//祝大家CSP-J/S 2024 RP++
}
```
主函数部分：
```
signed main() {
	cin>>n>>k>>s;
	//s是一个循环节 
	for(int i=1;i<=k;++i){
		string ns=s+s;
		//把两个循环节拼起来 
		for(int j=0;j<ns.size();j+=2){
			s[j/2]=winner(ns[j],ns[j+1]);
		}
	}
	cout<<s[0];
	return 0;
}
```
## 疑问
但是这里还有个问题，为什么不能这么写？
```
string ns;
if(s.size()&1) ns=s+s;
else ns=s;
```
其实，这么写理论上是可以的。但是，这么写有个小问题。

第一种写法可以很好地保证   $s$   的长度是不变的。如果像上边那么写，如果  $s$  长度为偶数，就会导致   $s$  的后半部分没被更新，相当于多测不清空，警钟敲烂。

## 完整代码
```
/*By DgNeHzL*/
#include<iostream>
using namespace std;
int n,k;
string s; 
char winner(char p1,char p2){
	if(p1==p2) return p1;
	if(p1=='R'&&p2=='S') return 'R';
	if(p1=='P'&&p2=='R') return 'P';
	if(p1=='S'&&p2=='P') return 'S';
	if(p1=='S'&&p2=='R') return 'R';
	if(p1=='R'&&p2=='P') return 'P';
	if(p1=='P'&&p2=='S') return 'S';
}
signed main() {
	cin>>n>>k>>s;
	for(int i=1;i<=k;++i){
		string ns=s+s;
		for(int j=0;j<ns.size();j+=2){
			s[j/2]=winner(ns[j],ns[j+1]);
		}
	}
	cout<<s[0]<<"\n";
	return 0;
}
```
最后祝大家 RP++

---

## 作者：__Creeper__ (赞：0)

## 题意

有 $2^k$ 个玩家进行比赛。给定一个长度为 $n$ 且仅由 `RPS` 组成的字符串 $s$。

他们所有人站成一排，按照序号两两比赛，胜者进入下一轮，最后胜出一个冠军。并且玩家 $i$ 的手牌是 $s$ 中的第 $((i \bmod n) + 1)$ 个字符。

## 思路

我们可以发现每轮都是在相邻两个人中决出胜负，即第 $i \times 2$ 和 $i \times 2 + 1$ 个人决出胜负（$i$ 起始下标为 $0$）。所以我们可以用 $i$ 和 $j$ 循环模拟胜负玩家和轮数，将比赛次序一层一层处理。胜利玩家存在 $s_i$ 中，答案为 $s_0$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

map<char, map<char, char> > win;
int n, m;
string s;

void solve() {
    win['R']['R'] = win['R']['S'] = win['S']['R'] = 'R';
	win['S']['S'] = win['S']['P'] = win['P']['S'] = 'S';
	win['P']['P'] = win['P']['R'] = win['R']['P'] = 'P';
	cin >> n >> m >> s;
	while(m--) {
		string t = s + s;
		for (int i = 0; i < n; i++) s[i] = win[t[i * 2]][t[i * 2 + 1]];
	}
	cout << s[0];
}

signed main() {
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while(T--) solve();
	return 0;
}
```

---

## 作者：NY_An18623091997 (赞：0)

## 题目大意
有 $2^k$ 个玩家，第 $i$ 个玩家的手牌为 $s_{((i \bmod n)+1)}$，问最后胜出的玩家的手牌。
### 规则
每轮选定 $l,r$，当该轮进行比赛的玩家值有两位时，通过石头剪刀布决胜，否则再分成两组进行比赛。 
## 思路
首先我们来形象地分析样例 $1$。 
![](https://cdn.luogu.com.cn/upload/image_hosting/fwc77vha.png)   
我们可以发现每轮都是在第 $i \times 2$ 和 $i \times 2+1$ 个选手中决出胜负（因为 $s$ 的起始下标为 $0$）。所以我们可以用 $j$ 循环模拟轮数，$i$ 循环模拟胜负玩家，将胜利玩家存在 $s_i$，最后输出 $s_0$ 即可。
## AC代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
string s,ss;
ll n,k;
unordered_map<char,ll> m;
char w[5][5];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k>>s;
	m['R']=1,m['P']=2,m['S']=3;
	w[1][1]=w[1][3]=w[3][1]='R';
	w[2][2]=w[1][2]=w[2][1]='P';
	w[3][3]=w[2][3]=w[3][2]='S';
	for(int j=1;j<=k;j++){
		ss=s+s;
		for(int i=0;i<n;i++)	s[i]=w[m[ss[i*2]]][m[ss[i*2+1]]];
	}
	cout<<s[0];
	return 0;
}
```
**[AC记录](https://www.luogu.com.cn/record/197664283)**

---

## 作者：Demons_Killer (赞：0)

# 解题思路：
考虑记忆化搜索加动态规划。

题目保证 $r-l$ 一定为 $2$ 的次幂，可以使用倍增。其中 $f_{i,j}$ 表示从 $i$ 开始，到 $2^{k}$ 个玩家众胜利者的手牌。转移可直接对两者进行判断。最后从 $0$ 到 $k$ 的搜索结果为最后答案。

# code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=110;
int n,k,f[N][N],p[N];
char s[N];
int dfs(int now,int k){
	if(k==0){
		if (s[now] == 'R') return 1;
		else if (s[now] == 'P') return 2;
		else if (s[now] == 'S') return 3; 
	}
	if (f[now][k]) return f[now][k];
	int l=dfs(now,k-1),r=dfs((now+p[k-1])%n,k-1);
	int x;
	if (l==1)
		if (r==2) x=r;
		else x=l;
	else if (l==2)
		if (r==3) x=r;
		else x=l;
	else if (l==3)
		if (r==1) x=r;
		else x=l;
	return f[now][k]=x;
}
signed main(){
	cin>>n>>k>>s;
	p[0]=1;
	for(int i=1;i<=n;i++) p[i]=(2*p[i-1])%n;
	int t=dfs(0,k);
	if(t==1) cout<<"R";
	else if(t==2) cout<<"P";
	else cout<<"S";
	return 0;
}
```

---

