# Roma and Poker

## 题目描述

Each evening Roma plays online poker on his favourite website. The rules of poker on this website are a bit strange: there are always two players in a hand, there are no bets, and the winner takes $ 1 $ virtual bourle from the loser.

Last evening Roma started to play poker. He decided to spend no more than $ k $ virtual bourles — he will stop immediately if the number of his loses exceeds the number of his wins by $ k $ . Also Roma will leave the game if he wins enough money for the evening, i.e. if the number of wins exceeds the number of loses by $ k $ .

Next morning Roma found a piece of paper with a sequence on it representing his results. Roma doesn't remember the results exactly, and some characters in the sequence are written in a way such that it's impossible to recognize this character, so Roma can't recall whether he won $ k $ bourles or he lost.

The sequence written by Roma is a string $ s $ consisting of characters W (Roma won the corresponding hand), L (Roma lost), D (draw) and ? (unknown result). Roma wants to restore any valid sequence by changing all ? characters to W, L or D. The sequence is called valid if all these conditions are met:

- In the end the absolute difference between the number of wins and loses is equal to $ k $ ;
- There is no hand such that the absolute difference before this hand was equal to $ k $ .

Help Roma to restore any such sequence.

## 样例 #1

### 输入

```
3 2
L??
```

### 输出

```
LDL
```

## 样例 #2

### 输入

```
3 1
W??
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
20 5
?LLLLLWWWWW?????????
```

### 输出

```
WLLLLLWWWWWWWWLWLWDW
```

# 题解

## 作者：静静是他的， (赞：8)

#### 差分约束
看到一坨约束条件，就想到了差分约束。


- 记 W 为 $1$，L 为 $-1$, D 为 0，$\text {dis}_i$ 前$i$ 个字符的和。

1. 考虑相邻条件。

 	 a. 第 $i$ 位分别是W, L, D时，就有
    $$\text {dis}_i - \text {dis}_{i - 1} = 1$$
    $$\text {dis}_i - \text {dis}_{i - 1} = -1$$
    $$\text {dis}_i - \text {dis}_{i - 1} = 0$$
    分别拆成
    $$ \left\{
    \begin{aligned}
  	  \text {dis}_i - \text {dis}_{i - 1} \leq 1 \\
     \text {dis}_i - \text {dis}_{i - 1} \geq 1 \\
    \end{aligned}
    \right.
    
     \left\{
    \begin{aligned}
  	  \text {dis}_i - \text {dis}_{i - 1} \leq -1 \\
     \text {dis}_i - \text {dis}_{i - 1} \geq -1 \\
    \end{aligned}
    \right.
    
     \left\{
    \begin{aligned}
  	  \text {dis}_i - \text {dis}_{i - 1} \leq 0 \\
     \text {dis}_i - \text {dis}_{i - 1} \geq 0 \\
    \end{aligned}
    \right.
    $$
   b. 第 $i$ 位是 ?, 就有
   	 $$ \left\{
    \begin{aligned}
  	  &\text {dis}_i - \text {dis}_{i - 1} \leq &1 \\
     &\text {dis}_i - \text {dis}_{i - 1} \geq &-1\\
    \end{aligned}
    \right.
    $$
2. 考虑前缀和绝对值 $<k$。
	$$
   \left\{
   \begin{aligned}
   &\text {dis}_i - \text {dis}_0 \leq &k -1 \\
   &\text {dis}_i - \text {dis}_0 \geq &-(k -1) \\
   \end{aligned}
   \right.
   $$
3. 考虑全部和的绝对值 $=k$。
	
   分别考虑
    $$\text {dis}_n - \text {dis}_0 = k$$
    $$\text {dis}_n - \text {dis}_0 = -k$$
   拆成
    $$ \left\{
    \begin{aligned}
  	  \text {dis}_n -\text {dis}_{0} \leq k \\
     \text {dis}_n - \text {dis}_{0} \geq k \\
    \end{aligned}
    \right.
    
     \left\{
    \begin{aligned}
  	  \text {dis}_n - \text {dis}_{0} \leq -k \\
     \text {dis}_n - \text {dis}_{0} \geq -k\\
    \end{aligned}
    \right.
    $$
   
- 将上面的约束条件变成 $\text {dis}_u \leq \text {dis}_v + w(u,v)$的形式，连一条 $v$ 到 $u$ 的权值为 $w(u, v)$ 的边，跑 spfa 就能得到一组解。有负环时无解，输出 NO 即可。

最坏时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
template <typename T>
void Read(T &x){
	T f = 1; x = 0; char a= getchar();
	for(; a < '0' || '9' < a; a = getchar()) if (a == '-') f = -f;
	for(; '0' <= a && a <= '9'; a = getchar()) x = (x << 1) + (x << 3) + (a ^ 48);
	x *= f; 
}
int n, k;
struct edge {
	int point, next, len;
}e[MAXN * MAXN];
int cnt, first[MAXN];
bool cut[MAXN * MAXN];
void add(int u, int v, int w) {
	++cnt;
	e[cnt].point = v;
	e[cnt].len = w;
	e[cnt].next = first[u];
	first[u] = cnt;
}

bool vis[MAXN];
int ind[MAXN], dis[MAXN];
#define INF 0x3f3f3f3f
bool spfa(int s) {
	for(int i = 0; i <= n; i ++)
		vis[i] = 0, dis[i] = INF, ind[i] = 0;
	queue<int> q;
	q.push(s);
	dis[s] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = 0;
		for(int i = first[u]; i; i = e[i].next) {
			int v = e[i].point;
			if (cut[i]) continue;
			if (dis[v] > dis[u] + e[i].len) {
				dis[v] = dis[u] + e[i].len;	
				if (!vis[v]) {
					if (++ind[v] > n) return false;
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return 1;
}

char a[MAXN];
int main(){
	Read(n); Read(k);
	scanf("%s", a + 1);
	for(int i = 1; i <= n; i++) {
		if (a[i] == '?') {
			add(i - 1, i, 1);
			add(i, i - 1, 1);
		}
		if (a[i] == 'W') {
			add(i - 1, i, 1);
			add(i, i - 1, -1);
		}
		if (a[i] == 'L') {
			add(i - 1, i, -1);
			add(i, i - 1, 1);
		}
		if (a[i] == 'D') {
			add(i - 1, i, 0);
			add(i, i - 1, 0);
		}
		if (i < n) {
			add(i, 0, (k - 1));
			add(0, i, (k - 1));
		}
	} 
	
	add(n, 0, -k);
	add(0, n, k);
	if (spfa(0)) {
		for(int i = 1; i <= n; i++)
			switch(dis[i] - dis[i - 1]) {
				case 1: putchar('W');break;
				case 0: putchar('D');break;
				case -1:putchar('L');break;
			}
		return 0;
	}
	cut[cnt] = cut[cnt - 1] = 1;
	
	add(n, 0, k);
	add(0, n, -k);
	if (spfa(0)) {
		for(int i = 1; i <= n; i++)
			switch(dis[i] - dis[i - 1]) {
				case 1: putchar('W');break;
				case 0: putchar('D');break;
				case -1:putchar('L');break;
			}
		return 0;
	}
	
	puts("NO");
	return 0;
}

```

---

## 作者：cqbztz2 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF803E)


~~我一定要纪念一下这道题，花费了我40分钟才评测出来~~

# 思路：

设 $ dp[i][j] $ 表示前 i 场游戏，胜场与负场的差为 j 的情况能不能达到；
能达到就为 $ true $；并记录是怎么达到的(即是赢一场达到的还是输还是……)
这样进行 DP。

第一层枚举从 $ 0……n-1 $，然后第二层循环只从 $ 1-k $ 枚举到 $ k-1 $，这样能保证在进行 DP 的时候选举的状态都是胜场与负场的差的绝对值小于 k 的；然后最后一秒(第 n 秒是可以为 k 的)刚好也能更新到。

# 代码：

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,k,tot;
  char dp[1005][2005];
  bool f[1005][2005];
  char a[1005];
  string ans;
  int main(){
      cin>>n>>k>>a+1;
      f[0][1005]=true;
      for(int i=0;i<n;i++){
          for(int j=1-k;j<=k-1;j++){
              if(f[i][j+1005]==true){
                  if(a[i+1]=='W'||a[i+1]=='?'){
                      f[i+1][j+1006]=true;
                      dp[i+1][j+1006]='W';
                  }
                  if(a[i+1]=='L'||a[i+1]=='?'){
                      f[i+1][j+1004]=true;
                      dp[i+1][j+1004]='L';
                  }
                  if(a[i+1]=='D'||a[i+1]=='?'){
                      f[i+1][j+1005]=true;
                      dp[i+1][j+1005]='D';
                  }
              }
          }
      }
      if(f[n][1005-k]==true||f[n][k+1005]==true){
          if(f[n][k+1005]==true){
              tot=1005+k;
          }
          else{
              tot=1005-k;
          }
          for(int i=n;i>=1;i--){
              ans=dp[i][tot]+ans;
              if(dp[i][tot]=='W'){
                  tot--;
              }
              if(dp[i][tot]=='L'){
                  tot++;
              }   
          }
          cout<<ans;
      }
      else{
          cout<<"NO";
      }  
      return 0;
  }
```


---

## 作者：DHT666 (赞：1)

## 题意
给一个包含 W、L、D、? 的长度为 $n$ 的字符串和整数 $k$，W 表示 $+1$，L 表示 $-1$，D 表示 $0$，? 可以替换为任意其它三个字母。要求替换所有 ?，使前 $n-1$ 个前缀和的绝对值都小于 $k$，且第 $n$ 个前缀和（即所有数的和）必须为 $k$ 或 $-k$，亦报告无解。

## 思路
一个明显 DP。

设 $dp_{i,j}$ 表示替换到第 $i$ 位，前缀和为 $j$ 的情况是否存在。

转移也很好想，问号就是其它三种字母的组合，判完无解后倒着看转移来源，输出方案即可。

注意负数下标要整体移位。

具体转移见代码。

## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LL;

const int N = 1010;

int n, k;
char a[N];
bool dp[N][N * 2];
char res[N];

void dfs(int i, int j) {
	if(i == 0) return;
	if(a[i] == 'W') { // 找转移
		res[i] = 'W';
		dfs(i - 1, j - 1);
	} else if(a[i] == 'L') {
		res[i] = 'L';
		dfs(i - 1, j + 1);
	} else if(a[i] == 'D') {
		res[i] = 'D';
		dfs(i - 1, j);
	} else {
		if(dp[i - 1][j - 1]) {
			res[i] = 'W';
			dfs(i - 1, j - 1);
		} else if(dp[i - 1][j + 1]) {
			res[i] = 'L';
			dfs(i - 1, j + 1);
		} else if(dp[i - 1][j]) {
			res[i] = 'D';
			dfs(i - 1, j);
		}
	}
}

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1;i <= n;i++) {
		scanf(" %c", &a[i]);
	}
	
	dp[0][k] = 1;
	for(int i = 1;i <= n;i++) {
		for(int j = 0;j <= 2 * k;j++) {
			if(i != n && (j == 0 || j == 2 * k)) continue; // 即题意中的过程中不能出现前缀和为正负 k
			if(a[i] == 'W') { // 转移
				if(j >= 1) dp[i][j] = dp[i - 1][j - 1];
			} else if(a[i] == 'L') {
				dp[i][j] = dp[i - 1][j + 1];
			} else if(a[i] == 'D') {
				dp[i][j] = dp[i - 1][j];
			} else {
				if(j >= 1) dp[i][j] = dp[i - 1][j - 1];
				dp[i][j] |= dp[i - 1][j] | dp[i - 1][j + 1];
			}
		}
	}
	
	if(!dp[n][0] && !dp[n][k * 2]) {
		printf("NO");
		return 0;
	}
	
	if(dp[n][0]) dfs(n, 0);
	else dfs(n, k * 2);
	
	for(int i = 1;i <= n;i++) {
		printf("%c", res[i]);
	}
	
	return 0;
}
```

---

## 作者：Minuit (赞：1)

设 $dp_{i,j}$ 表示对于字符串前 $i$ 位，出现次数差的绝对值为 $j$ 时是否有解。$dp_{0,0}$ 显然初始化为 `true` ，则有如下转移方程。
$$dp_{i,j+1}=true,s_i=W$$
$$dp_{i,j}=true,s_i=D$$
$$dp_{i,j-1}=true,s_i=L$$
$$dp_{i,j+1}=dp_{i,j}=dp_{i,j-1}=true,s_i=2$$
注意不要像某些题解一样访问数组负下标。

另外开一个数组记录某状态是由哪一状态转移过来的即可。

```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
const int N=1005;
int n,k;
string s;
map<int,int> dp[N],tow[N];//tow记录方案.
int main() {
	ios::sync_with_stdio(false);
	cin>>n>>k>>s;
	s=' '+s;
	dp[0][0]=true;
	for (int i=1; i<=n; i++)
		for (int j=-k+1; j<=k-1; j++) {
			if (dp[i-1][j]==false) continue;
			if (s[i]=='W'||s[i]=='?')
				dp[i][j+1]=true,tow[i][j+1]=j;
			if (s[i]=='D'||s[i]=='?')
				dp[i][j]=true,tow[i][j]=j;
			if (s[i]=='L'||s[i]=='?')
				dp[i][j-1]=true,tow[i][j-1]=j;
		}
	if (!dp[n][k]&&!dp[n][-k])
		cout<<"NO"<<endl;
	else {
		string ans="";
		if (dp[n][k]) {
			int now=k;
			for (int i=n; i>0; i--) {
				if (tow[i][now]==now-1) { //now是从now-1转移来的,说明过程中加了1,所以是W
					ans='W'+ans;
					now=now-1;//迭代到转移来的地方继续转移.
				} else if(tow[i][now]==now) {
					ans='D'+ans;
					now=now;
				} else if (tow[i][now]==now+1) {
					ans='L'+ans;
					now=now+1;
				}
			}
			cout<<ans<<endl;
		} else {
			int now=-k;
			for (int i=n; i>0; i--) {
				if (tow[i][now]==now-1) {
					ans='W'+ans;
					now=now-1;
				} else if(tow[i][now]==now) {
					ans='D'+ans;
					now=now;
				} else if (tow[i][now]==now+1) {
					ans='L'+ans;
					now=now+1;
				}
			}
			cout<<ans<<endl;
		}
	}
}
```

---

考虑优化，首先容易发现所有为 `true` 的 dp 数组必然在给定的 $i$ 上形成连续段。这是由于初始为真的只有一个位置，而之后的每次更新都只会向上\下\上下平移 $1$ 格，所以必然形成连续段。这样,每次只需要从之前保存的 $i-1$ 时为真的 dp 数组的左右端转移即可。这样就做到 $O(n)$ 的复杂度。

~~据说还有更快的栈+贪心做法~~

代码来自 @[mig](https://codeforces.com/profile/mig)

```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int , int> w[2006];
int main() {
	int n, k;
	bool flag = false;
	string s;
	cin>> n >> k;
	cin>> s;
	s = " " + s;
	for(int i = 1; i < n; i++) {
		if(s[i] == 'W') {
			w[i-1].first + 1 < k ? w[i].first = w[i-1].first + 1 : flag = true;
			w[i-1].second + 1 < k ? w[i].second = w[i-1].second + 1 : w[i].second = w[i-1].second;
		} else if(s[i] == 'L') {
			w[i-1].first - 1 > -k ? w[i].first = w[i-1].first - 1 : w[i].first = w[i-1].first;
			w[i-1].second - 1 > -k ? w[i].second = w[i-1].second - 1 : flag = true;
		} else if(s[i] == 'D')
			w[i].first = w[i-1].first, w[i].second = w[i-1].second;
		else {
			w[i-1].second + 1 < k ? w[i].second = w[i-1].second + 1 : w[i].second = w[i-1].second;
			w[i-1].first - 1 > -k ? w[i].first = w[i-1].first - 1 : w[i].first = w[i-1].first;
		}
		if(flag)
			return 0*puts("NO");
	}
	if(s[n] == 'W') {
		w[n].first = w[n-1].first + 1;
		w[n].second = w[n-1].second + 1;
	} else if(s[n] == 'L') {
		w[n].first = w[n-1].first - 1;
		w[n].second = w[n-1].second - 1;
	} else if(s[n] == 'D') {
		w[n].first = w[n-1].first;
		w[n].second = w[n-1].second;
	} else {
		w[n].first = w[n-1].first - 1;
		w[n].second = w[n-1].second + 1;
	}
	if(w[n].first > -k && w[n].second < k)
		return 0*puts("NO");
	int j;
	w[n].second == k ? j = k : j = -k;
	for(int i = n; i > 0; i--) {
		char c = s[i];
		if(c == 'W')
			j--;
		else if(c == 'L')
			j++;
		else if(c == '?') {
			if(j - 1 >= w[i-1].first)
				s[i] = 'W', j--;
			else if(j + 1 <= w[i-1].second)
				s[i] = 'L', j++;
			else
				s[i] = 'D';
		}
	}
	cout<< s.substr(1, n);
	return 0;
}
```







---

## 作者：jzh817 (赞：1)

这道题实际上就是一个记忆化搜索的模板题

题目要求输赢相差不超过k且在最后一回合是必须等于k，就可以用这做完终止条件
```cpp
	if(x==n and abs(y)==k)return true;
	if(x==n or abs(y)>=k)return false;
```
然后，若当前回合输赢已经确定，就直接进入下一层递归；否则，枚举3种情况分别递归，只要有一种情况成立，就返回true
```cpp
	if(s[x]=='W')return dfs(x+1,y+1);
	if(s[x]=='D')return dfs(x+1,y);
	if(s[x]=='L')return dfs(x+1,y-1);
	if(dfs(x+1,y+1))return s[x]='W',true;
	if(dfs(x+1,y))return s[x]='D',true;
	if(dfs(x+1,y-1))return s[x]='L',true;
```
然而，这样做肯定超时，于是开始记忆化搜索

用dp[x][y]表示在第x回合时赢的回合-输的回合数是y，当然，y有可能是负数

记忆化的过程也很简单，只要在递归函数中间加一个dp[x][y]=1就行了

上完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read(){
	ll a=0,b=getchar(),c=1;
	while(!isdigit(b))c=b=='-'?-1:1,b=getchar();
	while(isdigit(b))a=a*10+b-'0',b=getchar();
	return a*c;
}
int n,k,dp[1005][1005];
string s;
bool dfs(int x,int y){
	if(x==n and abs(y)==k)return true;
	if(x==n or abs(y)>=k)return false;
	if(dp[x][y])return false;
	dp[x][y]=1;
	if(s[x]=='W')return dfs(x+1,y+1);
	if(s[x]=='D')return dfs(x+1,y);
	if(s[x]=='L')return dfs(x+1,y-1);
	if(dfs(x+1,y+1))return s[x]='W',true;
	if(dfs(x+1,y))return s[x]='D',true;
	if(dfs(x+1,y-1))return s[x]='L',true;
}
int main(){
	n=read(),k=read();
	cin >> s;
	if(dfs(0,0))cout << s;
	else puts("NO");
	return 0;
}
```

---

## 作者：cppcppcpp3 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF803E)

~~跟官方题解差不多，主要感觉代码写得比较简短。~~

把 W、D、L 分别看作 $+1,0$ 和 $-1$。题面变成将每个问号处替换成 $+1,0$ 或 $-1$，对序列做前缀和 $s_i=\sum_{j=1}^i a_j$，满足 $\forall i \in [1,n-1],-k \le s_i \le k$ 且 $s_n=k$ 或 $s_n=-k$。

dp，设 $f_{i,j}=1/0$ 表示 $s_i$ 能否为 $j$，初始 $f_{0,0}=1$。

转移：

- $a_i=\texttt{W}$：$f_{i,j}=f_{i,j-1}$

- $a_i=\texttt{D}$：$f_{i,j}=f_{i,j}$

- $a_i=\texttt{L}$：$f_{i,j}=f_{i,j+1}$

- $a_i=\texttt{?}$：上述三种情况的所有转移。

其中当 $i<n$ 时 $-k < j < k$；$i=n$ 时 $j$ 可以取到 $k,-k$。

最后以 $f_{n,-k}$ 和 $f_{n,k}$ 的值判断是否有构造方案。

转移时顺带记录 $lst_{i,j}$ 表示 $f_{i,j}$ 从 $f_{i-1,j-1/j/j+1}$ 转移来，递归输出答案。一个实现细节是要把第二位下标全部加上 $k$，防止越界。

复杂度 $O(nk)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;

int n,k,lst[N][N<<1];
bool f[N][N<<1];
char c[N];

void w(int i,int j,int x,int y){
	if(f[x][y] && !f[i][j]) f[i][j]=f[x][y],lst[i][j]=y;
}

void write(int x,int y){
	if(!x) return;
	write(x-1,lst[x][y]);
	putchar(lst[x][y]==y ? 'D' : (lst[x][y]==y-1 ? 'W' : 'L'));
}

signed main(){
	scanf("%d%d%s",&n,&k,c+1);
	f[0][k]=1;
	for(int i=1;i<n;++i){
		if(c[i]=='D') for(int j=1;j<2*k;++j) w(i,j,i-1,j);
		else if(c[i]=='L') for(int j=1;j<2*k;++j) w(i,j,i-1,j+1);
		else if(c[i]=='W') for(int j=1;j<2*k;++j) w(i,j,i-1,j-1); 
		else for(int j=1;j<2*k;++j) w(i,j,i-1,j),w(i,j,i-1,j-1),w(i,j,i-1,j+1);
	}
	if(c[n]=='?' || c[n]=='W') w(n,2*k,n-1,2*k-1);
	if(c[n]=='?' || c[n]=='L') w(n,0,n-1,1);
	
	if(f[n][0]) write(n,0);
	else if(f[n][2*k]) write(n,2*k);
	else puts("NO");
	return 0;
}
```

---

