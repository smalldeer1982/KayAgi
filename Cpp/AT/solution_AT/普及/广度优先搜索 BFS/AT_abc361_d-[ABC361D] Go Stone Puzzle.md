# [ABC361D] Go Stone Puzzle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc361/tasks/abc361_d

$ N+2 $ 個のマスが横一列に並んでいます。左から $ i $ 番目のマスをマス $ i $ と表します。

マス $ 1 $ からマス $ N $ には石が $ 1 $ 個ずつ置かれています。  
 各 $ 1\leq\ i\ \leq\ N $ について、$ S_i $ が `W` のときマス $ i $ に置かれている石の色は白であり、$ S_i $ が `B` のときマス $ i $ に置かれている石の色は黒です。  
 マス $ N+1,N+2 $ には何も置かれていません。

あなたは以下の操作を好きな回数($ 0 $ 回でもよい)行うことができます。

- 石が $ 2 $ 個並んでいる箇所を選び、その $ 2 $ 個の石を順序を保って空きマスに移す。  
   より正確には次の通り。$ 1 $ 以上 $ N+1 $ 以下の整数 $ x $ であって、マス $ x,x+1 $ の両方に石が置かれているものを選ぶ。石の置かれていないマスを $ k,k+1 $ とする。マス $ x,x+1 $ にある石をそれぞれマス $ k,k+1 $ に移動する。
 
以下の状態にすることが可能か判定し、可能なら操作回数の最小値を求めてください。

- マス $ 1 $ からマス $ N $ には石が $ 1 $ 個ずつ置かれており、各 $ 1\leq\ i\ \leq\ N $ について、$ T_i $ が `W` のときマス $ i $ に置かれている石の色は白、$ T_i $ が `B` のときマス $ i $ に置かれている石の色は黒である。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 14 $
- $ N $ は整数である
- $ S,T $ は `B` および `W` のみからなる長さ $ N $ の文字列である
 
### Sample Explanation 1

石が置かれていないマスを `.` と表します。以下のようにして $ 4 $ 回の操作で目的の状態にすることができ、これが最小回数です。 - `BWBWBW..` - `BW..BWBW` - `BWWBB..W` - `..WBBBWW` - `WWWBBB..`

## 样例 #1

### 输入

```
6
BWBWBW
WWWBBB```

### 输出

```
4```

## 样例 #2

### 输入

```
6
BBBBBB
WWWWWW```

### 输出

```
-1```

## 样例 #3

### 输入

```
14
BBBWBWWWBBWWBW
WBWWBBWWWBWBBB```

### 输出

```
7```

# 题解

## 作者：shangruolin (赞：6)

[[ABC361D] Go Stone Puzzle](https://www.luogu.com.cn/problem/AT_abc361_d)

ABC 日常 D 题搜索。

记题上所说的空格为 `#`。

考虑广搜，队列中存储的是当前步数、当前 `#` 位置和当前字符串。

遍历当前字符串，如果第 $i$ 位和第 $i + 1$ 位上都不为 `#`，则将这两位与两个 `#` 进行交换，并加入队列。

当第一次遇到答案字符串时，输出当前步数即可，因为广搜保证当前步数是最优的。

需要使用 `unordered_map` 进行记忆化。

队列中每个元素存储的是三个变量，在这里我使用了 `tuple`，可以一次存储多个变量，非常方便。

```cpp
#include <bits/stdc++.h>
#define int long long
#define MT make_tuple
using namespace std;
typedef long long LL;
typedef tuple <int, int, string> T;

const int N = 1e6 + 10;
int n;
string a, b;
unordered_map <string, bool> mp;

signed main ()
{
	cin >> n >> a >> b;
	a = ' ' + a, b = ' ' + b;
	a = a + "##", b = b + "##";
	 
	queue <T> q;
	q.push (MT (0, n + 1, a)); mp[a] = 1;
	while (!q.empty ()) {
		int x = get <0> (q.front ()), y = get <1> (q.front ());
		string s = get <2> (q.front ()); q.pop ();
		if (s == b) return cout << x, 0;
		for (int i = 1; i <= n + 1; i++) {
			if (s[i] != '#' && s[i + 1] != '#') {
				swap (s[i], s[y]);
				swap (s[i + 1], s[y + 1]);
				if (!mp[s]) { // 记忆化
					mp[s] = 1;
					q.push (MT (x + 1, i, s));
				}
				swap (s[i], s[y]);
				swap (s[i + 1], s[y + 1]);
			}
		}
	}
	cout << -1;
	return 0;
}
```

---

## 作者：include13_fAKe (赞：4)

## 前言
集训正式开始前最后一场 ABC，也是期末考试以来第一场 ABC。
## 题意
有 $N+2$ 个单元格排列成一行。设单元格 $i$ 表示从左起的第 $i$ 个单元格。

在从单元格 $1$ 到单元格 $N$ 的每个单元格中放置一块石头。

对于每个$1\le i\le N$，如果 $S_i$ 是 `W`，则单元格 $i$ 中的石头是白色的，如果 $S_i$ 是 `B`，则为黑色的。

单元格 $N+1$ 和 $N+2$ 为空。

您可以执行以下操作任意次数（**可能为零**）：

- 选择一对相邻的都包含石头的单元格，将这两块石头移动到空的两个单元格中，**同时保持它们的顺序**。更准确地说，选择一个整数 $x$，使得 $1\le x\le N+1$，并且单元格$x$ 和 $x+1$ 都包含石头。设 $k$ 和 $k+1$ 是空的两个单元格。将石头分别从单元 $x$ 和 $x+1$ 移动到单元 $k$ 和 $k+1$。

确定是否有可能实现以下状态，如果有，则找出所需的最小操作次数：

- 从单元格 $1$ 到单元格 $N$ 的每个单元格都包含一个石头，并且对于每个 $1\le i\le N$，如果 $T_i$ 是 `W`，则单元格 $i$ 中的石头是白色的，如果 $T_i$ 是 `B`，则为黑色的。
## 数据范围
- $2\le N\le 14$
- $N$ 是一个整数
- $S$ 和 $T$ 都是由 `B` 和 `W` 组成的长度为 $N$ 的串。
## 思路
先进行状压。

因为最多有  $16$ 个格子，所以最多有 $3^{16}$ 种不同的状态。**数组要开 $5\times 10^{7}$**。

然后 BFS 即可。

本题并不需要用到 Astar、迭代加深等高级技巧，仅需写普通搜索。

但本题细节很多，建议**一定要自己写**。要注意的地方包括：

- 不要把状压的转换写错了
- **switch 一定要 break**，笔者在这儿卡了不知多久
- 可以换位置应该具备哪些条件
- 没有 memset 时，0x3f 都是 $63$，而 memset 时，0x3f 所表示的数却很大。

## 花絮
我是在赛后发现这个问题的，主要是赛时 B 题卡的有点久。

那时是 $21:48:29$，已经有人在 vp 了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=5e7+5;
int ans[N];
bool goal[N];
char now2[N];
int n;
string s1;
string s2;
int now_init(int now){
	int whk=0;
	for(int i=n+2;i>=1;i--){
		int now1=now%3;
		switch(now1){
			case 0:now2[i]='B';break;
			case 1:now2[i]='W';break;
			case 2:{
				now2[i]='.';
				if(whk==0)	whk=i-1;
				break;
			}
		}
//		cout<<now%3<<endl; 
		now/=3;
	}
//	cout<<now2[4]<<endl;
	return whk;
}
int main(){
	cin>>n;
	cin>>s1>>s2;
	s1=' '+s1;
	s2=' '+s2;
	memset(ans,0x3f,sizeof(ans));
	int st=0; 
	for(int i=1;i<=n+2;i++){
		int now;
		switch(s1[i]){
			case 'B':now=0;break;
			case 'W':now=1;break;
			default:now=2;
		}
		st=st*3+now;
//		cout<<st<<endl;
	}
//	cout<<ed<<endl;
	ans[st]=0;
	int ed=0;
	for(int i=1;i<=n+2;i++){
		int now;
		switch(s2[i]){
			case 'B':now=0;break;
			case 'W':now=1;break;
			default:now=2;
		}
		ed=ed*3+now;
	}
//	cout<<ed<<endl;
//	goal[ed]=true;
	queue<int> q;
	q.push(st);
	while(!q.empty()){
		int now=q.front();
//		cout<<now<<' '<<ans[now]<<endl;
		q.pop();
		int dot=now_init(now);
//		for(int i=1;i<=n+2;i++){
//			cout<<now2[i];
//		}
//		cout<<endl;
//		cout<<dot<<endl;
		for(int i=1;i<=n+1;i++){
			if(i!=dot&&i!=dot+1&i!=dot-1){
//				cout<<'@'<<endl;
				swap(now2[i],now2[dot]);
				swap(now2[i+1],now2[dot+1]);
				int st1=0; 
				for(int j=1;j<=n+2;j++){
					int now;
					switch(now2[j]){
						case 'B':now=0;break;
						case 'W':now=1;break;
						default:now=2;
					}
					st1=st1*3+now;
				}
//				cout<<st1<<endl;
				if(ans[st1]>=1e9){
					ans[st1]=ans[now]+1;
					q.push(st1);
				}	
				swap(now2[i],now2[dot]);
				swap(now2[i+1],now2[dot+1]);		
			}
		}
	}
	if(ans[ed]>=1e9)	ans[ed]=-1; 
	cout<<ans[ed]<<endl;
	return 0;
}
/*
每一个位置上  B 为 0 W 为 1 . 为 2 
*/
```

---

## 作者：Ivan422 (赞：4)

题目大意：有黑色和白色的 $n$ 颗石子在长度为 $n+2$ 的石板上。每次可以将两颗连着的石子移到空格处，不能改变顺序。判断状态 $s$ 是否能到达状态 $t$，输出最少操作次数。

思路：最小次数用广搜。直接广搜即可，只是要处理好细节。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2050;
map<string,bool>mp;
int n,sp;
string nw,nd,no,ds;
queue<pair<string,int> >q;
signed main(){
    cin>>n;
    cin>>nw>>nd;
    nw+="  ";nd+="  ";
    q.push(make_pair(nw,0));mp[nw]=1;
    while(q.size()){
        pair<string,int>fr=q.front();
        q.pop();no=fr.first;
        if(no==nd){cout<<fr.second;return 0;}
        sp=0;
        for(int i=0;i<=n;i++){if(no[i]==' '&&no[i+1]==' ')sp=i;}
        for(int i=0;i<=n;i++){if(no[i]!=' '&&no[i+1]!=' '){
            ds=no;
            ds[sp]=ds[i];ds[sp+1]=ds[i+1];
            ds[i]=ds[i+1]=' ';
            if(mp[ds])continue;
            q.push(make_pair(ds,fr.second+1));mp[ds]=1;
        }}
    }
    cout<<-1;
    return 0;
}
```

---

## 作者：fzark (赞：1)

看了一圈题解，好像一个深搜的题解也没有，这里就提供一个比较经典的深搜思路吧

## 题意

[原题链接](https://www.luogu.com.cn/problem/AT_abc361_d)

给定一个字符串 $s$ ，假设存在一个长度为 $|s| + 2$ 的字符串 $s'$，的字符串，含义为原来的 $s$ 字符串中多出了两个 '.' 字符串。其中，$s'_i$ 为 'W' 代表棋盘颜色为白色；为 'B' 代表棋盘颜色为黑色；为 '.' 代表棋盘颜色为空。有一个可以执行无限次的操作：
  - 选择 $0 \le i \lt n+1$，并且 $s'_i \neq '.'$ 和 $s'_{i+1} \neq '.'$ ，将 $s'_i$ 和 $ s'_{i+1}$ 移动到 '.' 处

问最小操作次数：对于任意 $0 \le i \le n$ ，都有 $s_i = t_i$

## 思路

起初感觉是动态规划题目，看到 $2 \le n \le 14$ ，就考虑搜索，由于智慧不在线，没有想到 bfs ，所以考虑dfs。
然后我们按照题意进行深搜即可。关键在于，我们设定一个 $cur$ ，含义为：搜索过程中的 $s'$ 字符串。然后我们可以将 $cur$ 变成字符串，然后再进行记忆化，这样就不会超时了，下面直接看代码吧, 注释都有

## 代码


```python
# 更新cur，按照题意模拟
def update(cur,last,i):
    cur = cur.copy()
    cur[last] = cur[i]
    cur[last + 1] = cur[i + 1]
    cur[i],cur[i + 1] = '.','.'
    return cur

ans = float('inf')
def dfs(dp,dot,cur,vis,t,dep):
    global  ans
    # 关键在于，将cur字符串之后进行记忆化
    key = (dot,''.join(cur),dep)
    # 减枝
    if dep > ans:return
    # 记忆化
    if key in dp:return
    # 如果当前搜到的cur等于t串，则更新答案
    if cur == t:
        ans = min(ans,dep)
    # 深搜
    for i in range(len(cur)-1):
        # 如果当前是 . 或者说下一个是 . ,显然不行
        if i in vis or cur[i] == '.' or cur[i+1] == '.':continue
        # 使用set存储已经搜过的集合，经典深搜
        vis.add(i)
        dfs(dp,i,update(cur,dot,i),vis,t,dep + 1)
        # 记忆化
        dp[key] = 1
        vis.discard(i)
def solve():
    n = int(input())
    s = list(input()) + ['.','.']
    t = list(input()) + ['.','.']
    dfs({},len(s) - 2,s,set(),t,0)
    if ans == float('inf'):return -1
    return ans

print(solve())

```

---

## 作者：int_stl (赞：1)

一道广度优先搜索题。

我们定义二元组 $(s, t)$，其中 $s$ 表示当前的字符串，$t$ 表示当前的步骤。同时，我们使用 map 容器标记字符串有没有出现过。

我们为了模拟题目的步骤。我们先在 $S$ 和 $T$ 后面加两个空格。

起初，我们将 $(S, 0)$ 加入队列，然后进行状态的扩展，这一步很简单，按题意模拟即可。

当我们产生了新的字符串 $S'$ 时，我们就把 $(S', t + 1)$ 加入队列，然后重复上述步骤。

当我们找到一个 $S'$ 且满足 $S' = T$ 时，我们更新最小步骤即可。

时间复杂度为 $O(n2 ^ n)$。

[Submission Link.](https://atcoder.jp/contests/abc361/submissions/55314701)

---

## 作者：nightwatch.ryan (赞：1)

### 思路
注意到要求最少次数，所以应该使用广度优先搜索。

每次寻找两个空格的位置，遍历当前状态的所有字符，如果前一个格子和当前格子都不是空格，那么和空格交换，如果这个新状态没有出现过，那么将这个新状态加入队列，并且操作次数加一。

如果当前状态就是目标字符串，那么输出到达这个状态的次数即可。

如果队列空了，那么输出 `-1`，表示不能到达目标状态。
### 代码
```cpp
#include<iostream>
#include<queue>
#include<map>
#define N 20
int n;
std::string s,t;
struct Node{
	std::string sta;
	int step;
};
std::map<std::string,bool>vis;
signed main(){
	std::cin>>n>>s>>t;
	s+="..";
	t+="..";
	std::queue<Node>q;
	q.push({s,0});
	vis[s]=1;
	while(q.size()){
		int cs=q.front().step;
		std::string cur=q.front().sta;
		if(cur==t){
			std::cout<<cs;
			return 0;
		}
		q.pop();
		std::vector<int>PointPos;
		for(int i=0;i<cur.size();i++)
			if(cur[i]=='.')PointPos.push_back(i); 
		for(int i=1;i<cur.size();i++){
			if(cur[i]!='.'&&cur[i-1]!='.'){
				std::string nxt=cur;
				std::swap(nxt[i-1],nxt[PointPos[0]]);
				std::swap(nxt[i],nxt[PointPos[1]]);
				if(!vis[nxt]){
					q.push({nxt,cs+1});
					vis[nxt]=1;
				}
			}
		}
	}
	puts("-1");
}
```

---

## 作者：Heldivis (赞：1)

搜索题。

记空位置为 `#`，可以发现空位置总是连续的，记第一个空位置为 $p$。每次枚举 $1 \le i\lt n+2$，使得当前的字符串 $s$，满足 $s_i,s_{i+1} \neq \texttt\#$，交换 $(s_i, s_{i + 1})$ 和 $(s_{p}, s_{p + 1})$。

考虑搜索过程中，三种颜色（含空位）的点数量不变，在进行搜索时，状态个数为这三个点的排列个数，即 $\dfrac{(n+2)!}{2\cdot w!(n-w)!}$（$w$ 为白点数量），最大约为 $4\times 10^5$，跑的飞快。

代码:

```cpp
const int N = 20;
int n;
string s, t;
unordered_map<string, bool> f;
struct Node {
  string s;
  int w, fre;
};
signed main() {
  cin >> n >> s >> t;
  s = ' ' + s + '#' + '#';
  t = ' ' + t + '#' + '#';
  queue<Node> q;
  f[s] = 1;
  q.push({s, 0, n + 1});
  while (!q.empty()) {
    string s = q.front().s;
    int w = q.front().w, fre = q.front().fre;
    q.pop();
    if (s == t) return 0 * printf("%lld", w);
    for (int i = 1; i <= n + 1; i++) {  // 这里不要写成 i <= n + 2
      if (s[i] != '#' && s[i + 1] != '#') {
        swap(s[i], s[fre]);
        swap(s[i + 1], s[fre + 1]);
        if (!f[s]) {
          f[s] = 1;
          q.push({s, w + 1, i});
        }
        swap(s[i], s[fre]);
        swap(s[i + 1], s[fre + 1]);
      }
    }
  }
  return cout << "-1", 0;
}
```

---

## 作者：Starrykiller (赞：1)

简单题。

考虑到状态只能有 $2^{14}\times {16\choose 2}=1,966,080$ 个，可以接受，于是直接 BFS 即可。

状态直接用 $\texttt{std::string}$ 表示，然后用 $\texttt{std::unordered\_map}$ 来存储即可。这样判断比较容易。

[代码](https://atcoder.jp/contests/abc361/submissions/55289632)。

---

## 作者：wbh20090611 (赞：1)

这道题是一道**好题**啊！

## 以下是本**蒟蒻**的做法：

首先，我们可以很快的想到可以使用状态压缩来实现操作，然后使用广度优先搜索或者动态规划来求解。

~~本蒟蒻想不到怎么用 BFS 于是用了状压 DP。~~

首先进行输入加状压：

```cpp
string s, ll;
int n, a, b, c;
cin >> n >> s >> ll;
p = n;
for(int i = 0; i < n; i++)
{
	a += (s[i] == 'W');
	b += (s[i] == 'B');
	if (s[i] == 'W')
		x |= (1 << i);//状态压缩（'W'为1, 'B'为0）
  		//记录初始状态 
	a -= (ll[i] == 'W');
	b -= (ll[i] == 'B');
	if (ll[i] == 'W')
		y |= (1 << i), c++;//状态压缩（'W'为1, 'B'为0）
  		//记录最终状态 
}//c用于记录一共有多少个'W'
//a和b分别记录
if (a != 0 || b != 0)//如果'W'的个数不相同就不可能 
{
	cout << -1;
	return 0;
}
```
需要注意的是：先不用管 `.` 的表示方法，后面会提到。

预处理可能出现的状态，用动态数组存储：
### 1. 声明函数 check
```cpp
int check(int m) //数一个数的二进制中有多少个1
{
	int cnt = 0;
	while(m > 0)
	{
		m -= (m & -m);
		cnt++;
	}
	return cnt;
} //可以作为模板
```
### 主函数：
```cpp
vector <int> w;
for (int j = 0; j <= (1 << (n + 2)) - 1; j++)
{
  //c用于记录一共有多少个'W'
	if (check(j) == c) //当1的个数为c时成立
		w.push_back(j); //计入动态数组
}
```

### 动态规划：

```cpp
//开始 DP 
memset(dp, 0x3f3f3f3f, sizeof dp);
//把每个数变成 inf 
memset(l, -1, sizeof l);
//l用于记录 dp的初值 
//dp[i][j]表示空位在 i和 i+1的位置上，当前状态为 j 
dp[p][x] = 0;//初始值为 0 
r = true;
while((dp[p][y] == 0x3f3f3f3f || dp[p][y] != o) && (r)) //如果没有更改，就退出 
{
	r = false;
	o = dp[p][y];
	for (auto j : w) //枚举可能的状态 
	{
		for (int i = 0; i < n + 1; i++) //枚举第一个空位的位置 
		{
			//如果dp[i][j]和初值相同，就不必进行下一步 
			if(dp[i][j] >= dp[p][y] || dp[i][j] == l[i][j])
				continue;
			l[i][j] = dp[i][j];//更新初值 
			for (int z = 0, d, e, f, u, g; z < n + 1; z++) //枚举交换位的位置 
			{
				if(z == i || z == i + 1 || z == i - 1) //如果是空位，跳过 
					continue;
				u = j;
				//记录位置并使用位运算把该位移到正确位置 
				if (i < z)
				{
					d = ((j & (1 << z)) >> (z - i));
					e = ((j & (1 << i)) << (z - i));
					f = ((j & (1 << (z + 1))) >> (z - i));
					g = ((j & (1 << (i + 1))) << (z - i))；
				}
				else//由于在 <<或 >>运算中，不存在负数，因此： 
				{
					d = ((j & (1 << z)) << (i - z));
					e = ((j & (1 << i)) >> (i - z));
					f = ((j & (1 << (z + 1))) << (i - z));
        	   g = ((j & (1 << (i + 1))) >> (i - z));
				}
				if (j & (1 << z)) //删除该位 
					u -= (1 << z);
				u |= e; //改变该位 
				//以下同理 
				if (j & (1 << i))	
					u -= (1 << i);
				u |= d;
				if (j & (1 << (z + 1)))	
					u -= (1 << (z + 1));
				u |= g;
				if (j & (1 << (i + 1)))	
					u -= (1 << (i + 1));
				u |= f;
				dp[z][u] = min(dp[i][j] + 1, dp[z][u]); //dp递推式 
				r = true;//标记更改过了 
			}
		}
	}
}
//依题意输出 
if (dp[p][y] < 0x3f3f3f3f)cout << dp[p][y];
else cout << -1;
```

### 最后附上详细代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
vector <int> w;
int n, ans = INT_MAX;
int x, y, a, b, p, dp[21][100010], l[21][100010], c, o;
int check(int m)//数一个数的二进制中有多少个1
{
	int cnt = 0;
	while(m > 0)
	{
		m -= (m & -m);
		cnt++;
	}
	return cnt;
}//可以作为模板，时间复杂度O(log(n)) 
string s, ll;
bool r;
int main()
{
	cin >> n >> s >> ll;
	p = n;
	for(int i = 0; i < n; i++)
	{
		a += (s[i] == 'W');
		b += (s[i] == 'B');
		if (s[i] == 'W')
			x |= (1 << i);//状态压缩（'W'为 1, 'B'为 0）
			//记录初始状态 
		a -= (ll[i] == 'W');
		b -= (ll[i] == 'B');
		if (ll[i] == 'W')
			y |= (1 << i), c++;//状态压缩（'W'为 1, 'B'为 0）
			//记录最终状态 
	}
	//c用于记录一共有多少个'W'
	if (a != 0 || b != 0)//如果'W'的个数不相同就不可能 
	{
		cout << -1;
		return 0;
	}
	for (int j = 0; j <= (1 << (n + 2)) - 1; j++)
	{
		//c用于记录一共有多少个'W'
		if (check(j) == c) //当 1的个数为 c时成立
			w.push_back(j); //计入动态数组
	}
	//开始 DP 
	memset(dp, 0x3f3f3f3f, sizeof dp);
	//把每个数变成 inf 
	memset(l, -1, sizeof l);
	//l用于记录 dp的初值 
	//dp[i][j]表示空位在 i和 i+1的位置上，当前状态为 j 
	dp[p][x] = 0;//初始值为 0 
	r = true;
	while((dp[p][y] == 0x3f3f3f3f || dp[p][y] != o) && (r)) //如果没有更改，就退出 
	{
		r = false;
		o = dp[p][y];
		for (auto j : w) //枚举可能的状态 
		{
			for (int i = 0; i < n + 1; i++) //枚举第一个空位的位置 
			{
				//如果dp[i][j]和初值相同，就不必进行下一步 
				if(dp[i][j] >= dp[p][y] || dp[i][j] == l[i][j])
					continue;
				l[i][j] = dp[i][j];//更新初值 
				for (int z = 0, d, e, f, u, g; z < n + 1; z++) //枚举交换位的位置 
				{
					if(z == i || z == i + 1 || z == i - 1) //如果是空位，跳过 
						continue;
					u = j;
					//记录位置并使用位运算把该位移到正确位置 
					if (i < z)
					{
						d = ((j & (1 << z)) >> (z - i));
						e = ((j & (1 << i)) << (z - i));
						f = ((j & (1 << (z + 1))) >> (z - i));
						g = ((j & (1 << (i + 1))) << (z - i));
					}
					else//由于在 <<或 >>运算中，不存在负数，因此： 
					{
						d = ((j & (1 << z)) << (i - z));
						e = ((j & (1 << i)) >> (i - z));
						f = ((j & (1 << (z + 1))) << (i - z));
						g = ((j & (1 << (i + 1))) >> (i - z));
					}
					if (j & (1 << z)) //删除该位 
						u -= (1 << z);
					u |= e; //改变该位 
					//以下同理 
					if (j & (1 << i))	
						u -= (1 << i);
					u |= d;
					if (j & (1 << (z + 1)))	
						u -= (1 << (z + 1));
					u |= g;
					if (j & (1 << (i + 1)))	
						u -= (1 << (i + 1));
					u |= f;
					dp[z][u] = min(dp[i][j] + 1, dp[z][u]); //dp递推式 
					r = true;//标记更改过了 
				}
			}
		}
	}
	//依题意输出 
	if (dp[p][y] < 0x3f3f3f3f)cout << dp[p][y];
	else cout << -1;
}
```

---

## 作者：Redamancy_Lydic (赞：1)

## 背景

保佑刘畅能来一中。

## 题意

给你一个长度为 $n$ 的初始字符串和目标字符串，都由 `W` 和 `B` 两种字符构成。

现在初始字符串末尾接有两个空格字符，每次你可以在该字符串中选出连续两个非空格字符，并把它们按顺序与两个空格交换位置。问最少需要几步能得到目标字符串。

## 分析

首先如果两字符串中 `W` 和 `B` 字符的数量不相等，那么一定无解。

由于 $n\leq 14$，那么算法应该是搜索。因为要求最小步数，所以考虑 BFS 算法。

然后每次选出队头，枚举所有非空格字符，与空格字符交换后扔进队列，再写一个记忆化就能过了。

## Code

```cpp
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/trie_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define int long long
using namespace std;
using namespace  __gnu_pbds;
//gp_hash_table<string,int>mp2;
//__gnu_pbds::priority_queue<int,less<int>,pairing_heap_tag> q;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int mod=998244353;
const int maxn=1e6+10;
int n;
string s,t;
int sw,sb,tw,tb;
struct no
{
	string ss;
	int ans;
};
map<string,bool> mp;
signed main()
{
//	freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>n>>s>>t;
	for(int i=1;i<=2;i++)s=s+'.';
	for(int i=1;i<=2;i++)t=t+'.';
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='W')sw++;
		else sb++;
	}
	for(int i=0;i<t.size();i++)
	{
		if(t[i]=='W')tw++;
		else tb++;
	}
	if(sw!=tw||sb!=tb)return 0*printf("-1");
	queue<no>q;
	q.push({s,0});
	mp[s]=1;
	while(!q.empty())
	{
		string ss=q.front().ss;
		int ans=q.front().ans;
		q.pop();
		if(ss==t)
		{
			cout<<ans;
			return 0;
		}
		int tt=0;
		for(int i=0;i<ss.size()-1;i++)
		{
			if(ss[i]=='.'&&ss[i+1]=='.')
			{
				tt=i;
				break;
			}
		}
		for(int i=0;i<ss.size()-1;i++)
		{
			if(ss[i]!='.'&&ss[i+1]!='.')
			{
				swap(ss[i],ss[tt]);
				swap(ss[i+1],ss[tt+1]);
				if(!mp[ss]){mp[ss]=1;q.push({ss,ans+1});}
				swap(ss[i],ss[tt]);
				swap(ss[i+1],ss[tt+1]);
			}
		}
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：Hughpig (赞：0)

本题解默认下标从 $0$ 开始。

因为 $N\le 14$，所以最多有 $N+2$ 个位置，每个位置有黑色石头、白色石头和留空三种取值，最多 $3^{16}=43046721$ 种状态，可以用广度优先搜索解决。根据广搜的性质，显然第一次搜到的解就是最优解。

但是直接用字符串搜索因为常数原因可能会超时，因此我使用了状态压缩。把一个长为 $N+2$ 的字符串看作一个三进制数，$\texttt{B}$ 看作 $1$，$\texttt{W}$ 看作 $2$，空地看作 $0$。然后把状态看作三进制数进行搜索。

考虑如何转移。原来转移是找两个连续的非空位置和空位。在状压的视角下，记需要交换的两个非空位置分别为 $i$ 和 $i+1$，两个空位分别为 $p$ 和 $p+1$，原来的状态为 $s$。

考虑第 $i$ 位，它位于三进制数中，权重为 $3^i$，因此它的值为 $\lfloor\dfrac{s}{3^i}\rfloor\mod 3$。其余位同理。

交换后，两个原来的空位会被填上要交换的的两个非空位置的值，因此 $s$ 需要加上 $3^p\times (\lfloor\dfrac{s}{3^i}\rfloor\mod 3)+3^{p+1}\times (\lfloor\dfrac{s}{3^{i+1}}\rfloor\mod 3)$；两个非空位置要为空，因此 $s$ 需要减去 $3^i\times (\lfloor\dfrac{s}{3^i}\rfloor\mod 3)+3^{i+1}\times (\lfloor\dfrac{s}{3^{i+1}}\rfloor\mod 3)$；

注意把新状态放进队列后要再交换回来，方法差不多。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

constexpr int N=43080009;

int n,vis[N],pow3[N];

pair<int,int> getcnt(string s){
	int r1=0,r2=0;
	for(auto c:s)c=='W'?r1++:r2++;
	return make_pair(r1,r2);
}

int getstate(string s){
	int ret=0;
	for(auto c:s){
		ret*=3;
		if(c=='B')++ret;
		else if(c=='W')ret+=2;
	}
	return ret;
}

int main()
{
	pow3[0]=1;for(int i=1;i<=20;++i)pow3[i]=pow3[i-1]*3;
   	memset(vis,-1,sizeof(vis));
   	string s,t;
   	cin>>n>>s>>t;
   	if(getcnt(s)!=getcnt(t))cout<<-1,exit(0);
   	s+="..",t+="..";
  	int _s=getstate(s),_t=getstate(t);
   	queue<pair<int,int> > q;
	q.push(make_pair(_s,0));
	while(q.size()){
		int tmp=q.front().first,s_=q.front().second;q.pop();
		if(tmp==_t)cout<<s_,exit(0);
		vis[tmp]=s_;
		int pos;for(int i=0;i<=n+1;++i)if((tmp/pow3[i])%3==0)pos=i;--pos;
		for(int i=0;i<=n;++i){
			if((tmp/pow3[i])%3!=0&&(tmp/pow3[i+1])%3!=0){
				tmp+=pow3[pos]*((tmp/pow3[i])%3);
				tmp+=pow3[pos+1]*((tmp/pow3[i+1])%3);
				tmp-=pow3[i]*((tmp/pow3[i])%3);
				tmp-=pow3[i+1]*((tmp/pow3[i+1])%3);
				if(vis[tmp]==-1)q.push(make_pair(tmp,s_+1));
				tmp+=pow3[i]*((tmp/pow3[pos])%3);
				tmp+=pow3[i+1]*((tmp/pow3[pos+1])%3);
				tmp-=pow3[pos]*((tmp/pow3[pos])%3);
				tmp-=pow3[pos+1]*((tmp/pow3[pos+1])%3);
			}
		}
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

发现 $n\le 14$，启发使用指数级算法。每一个位置可以为 B，W 或者什么也没有，因此用 $0/1/2$ 来表示这三个状态。可以用一个 $n+2$ 位三进制数来存储当前的状态，广搜一遍求答案即可。时间复杂度为 $O(n^2\times 3^{n+2})$，看上去过不去，但是因为有效状态数量极少所以随便冲。

```cpp
bool begmem;
#include <bits/stdc++.h>
#define int long long
using namespace std;
class FastIO {
public:
    int read() {
        int o = 1, x; char ch;
        while (!isdigit(ch = getchar())) {
            if (ch == '-') {
                o = -1;
            }
        }
        x = ch ^ 48;
        while (isdigit(ch = getchar())) {
            x = (x << 3) + (x << 1) + (ch ^ 48);
        }
        return o * x;
    }
} ; FastIO io;

void calcqwq();
const int N = 500100, inf = 1e18;
inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }
inline void swap(int &a, int &b) { a ^= b ^= a ^= b; }
int n, now, mask; string s, t;
signed f[63333333];
signed main() {
    atexit(calcqwq);
    n = io.read();
    cin >> s >> t;
    now = 0, mask = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'B') now = now * 3 + 1;
        else now = now * 3 + 2;
        if (t[i] == 'B') mask = mask * 3 + 1;
        else mask = mask * 3 + 2;
    }
    now = now * 9, mask = mask * 9;
    memset(f, -1, sizeof f);
    f[now] = 0;
    queue<int> q;
    q.push(now);
    while (q.size()) {
        int t = q.front();
        q.pop();
        int f1 = 0, f2 = 0;
        vector<int> wei;
        int tmp = t;
        for (int i = 0; i < n + 2; ++i) {
            wei.push_back(tmp % 3);
            tmp /= 3;
        }
        reverse(wei.begin(), wei.end());
        for (int i = 0; i < n + 1; ++i)
            if (!wei[i] && !wei[i + 1]) f1 = i, f2 = i + 1;
        for (int i = 0; i < n + 1; ++i)
            if (wei[i] && wei[i + 1]) {
                vector<int> wei2 = wei;
                wei2[f1] = wei[i], wei2[f2] = wei[i + 1], wei2[i] = wei2[i + 1] = 0;
                int calc = 0;
                for (auto &j : wei2) calc = calc * 3 + j;
                if (!~f[calc]) {
                    f[calc] = f[t] + 1;
                    q.push(calc);
                }
            }
    }
    if (~f[mask]) cout << f[mask] << '\n';
    else cout << "-1\n";
}
bool endmem;
void calcqwq() {
    fprintf(stderr, "Memory = %.5lf\n", (&begmem - &endmem) / 1048576.);
}
```

---

## 作者：shitingjia (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc361_d)

### 思路

一道简单的广搜题，但是细节较多。

- 移动时必须是两个**连续石子**移动到两个连续空位上，用循环枚举就行，注意下标。
- 特判原始状态即是目标状态的情况，直接输出 $1$ 。
- 无解输出 $-1$ 。

另外，末尾添加空位用 string 比较方便。

### AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=-1;
string s,t;
map<string,int>mp;
struct node{
	string s1;
	int stp,point;//第1个是当前步数，第2个是靠前的一个空位 
};
void bfs(){
	queue<node>q;
	q.push({s,0,n});
	mp[s]=1;
	if(s==t){//细节2
		ans=0;
		return ;
	}
	while(q.size()){
		string l=q.front().s1;
		int r=q.front().stp,p1=q.front().point;//空位都是在一起的，下标为p1和p1+1
		for(int i=0;i<=n;i++){//字符串从0~n+1,最后一位不能作为靠前的空位，故循环从0~n 
			if(l[i]!='.'&&l[i+1]!='.'){
				string h=l;
				swap(h[i],h[p1]);
				swap(h[i+1],h[p1+1]);
				if(!mp[h]){
					mp[h]=1;
					q.push({h,r+1,i});
					if(h==t){
						ans=r+1;
						return ;
					}
				}
			}
		}
		q.pop();
	}
}
int main(){
	cin>>n>>s>>t;
	s+="..";t+="..";
	bfs();
	printf("%d",ans);
	return 0;
}
```

---

## 作者：joe_zxq (赞：0)

# Part 1 - 题面翻译

有 $N+2$ 个单元格排成一行。单元格 $i$ 表示从左边开始的第 $i$ 个单元格。

从单元格 $1$ 到单元格 $N$，每个单元格中都有一块石头。  
对于每一个 $1 \leq i \leq N$，如果 $S_i$ 是 `W`，那么 $i$ 单元格中的石头是白色的；如果 $S_i$ 是 `B`，那么 $S_i$ 中的石头是黑色的。单元格 $N+1$ 和 $N+2$ 为空。

你可以执行以下操作任意多次（可能为零次）：

- 选择一对都有石头的相邻单元格，然后将这两个石头移动到空的两个单元格中，同时保持它们的顺序。更确切地说，选择一个整数 $x$，使得 $1 \leq x \leq N+1$ 和 $x$ 以及 $x+1$ 两个单元格都包含石头。假设 $k$ 和 $k+1$ 是空的两个单元格。将 $x$ 和 $x+1$ 两个单元格中的石头分别移动到 $k$ 和 $k+1$ 两个单元格中。

判断是否可以达到下面的状态。如果可以，求所需的最小操作次数：

- 从单元格 $1$ 到 $N$ 的每个单元格中都有一颗石头，对于每个 $1 \leq i \leq N$，如果 $T_i$ 为 `W`，则 $i$ 单元格中的石头为白色；如果 $T_i$ 为 `B`，则 $i$ 单元格中的石头为黑色。

# Part 2 - 算法思路

~~现在 ABC 的 D 都这么水了吗，没有任何思维含量，广搜的模板题。~~

注意到 $N$ 非常小，字符串的每一种状态都可以被遍历到。因为求最少操作次数，考虑 BFS。从 $S$ 开始搜，更新每一种状态的最少操作次数。对于每一次转移，只需要找到空格的位置，枚举互换的石子位置，求出新的字符串即可。

最后，输出 $T$ 的最少操作次数。

# Part 3 - 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll n;
string s, t;
map<string, ll> dis;
queue<string> q;

int main() {

	cin >> n >> s >> t;
	s += '.';
	s += '.';
	t += '.';
	t += '.';
	q.push(s);
	dis[s] = 0;
	while (!q.empty()) {
		string r = q.front();
		q.pop();
		ll pos;
		for (ll i = 0; i < (ll)r.size(); i++) {
			if (r[i] == '.') {
				pos = i;
				break;
			}
		}
		for (ll i = 0; i < (ll)r.size() - 1; i++) {
			if (r[i] != '.' && r[i + 1] != '.') {
				string u = r;
				u[pos] = r[i];
				u[pos + 1] = r[i + 1];
				u[i] = '.';
				u[i + 1] = '.';
				if (dis.find(u) == dis.end()) {
					q.push(u);	
					dis[u] = dis[r] + 1;
				}
			}
		}
	}
	if (dis.find(t) == dis.end()) {
		cout << -1;
	} else {
		cout << dis[t];
	}
	
	return 0;
}

```

---

## 作者：I_will_AKIOI (赞：0)

首先一看范围 $n\le14$，一看就是爆搜。求最短路径我们选用 BFS，每个节点的状态里存当前空格的位置（靠左的空格），走的步数和当前格子的状态。判重就使用哈希，用 map 存一下就行。无解的情况当且仅当目标状态和初始状态棋子颜色不相等。

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
struct Data
{
  vector<char>c;
  int x,s;
}w;
int n,cnt[2];
vector<char>a(20),b(20);
map<int,bool>vis;
queue<Data>q;
int Hash(vector<char>&c)
{
  int res=0;
  for(int i=0;i<n;i++)
  {
    res=res*3;
    if(c[i]=='W') res++;
    if(c[i]=='.') res+=2;
  }
  return res;
}
bool check(vector<char>&c)
{
  for(int i=0;i<n;i++) if(c[i]!=b[i]) return 0;
  return 1;
}
int BFS()
{
  q.push(Data{a,n,0});
  while(!q.empty())
  {
    w=q.front();
    int x=w.x,s=w.s;
    if(check(w.c)) return s;
    for(int i=0;i<n+1;i++)
    {
      if(i==x||i+1==x||i==x+1) continue;//不能和空格交换
      swap(w.c[i],w.c[x]);
      swap(w.c[i+1],w.c[x+1]);
      int now=Hash(w.c);
      if(vis[now])//出现重复的状态
      {
        swap(w.c[i],w.c[x]);
        swap(w.c[i+1],w.c[x+1]);
        continue;
      }
      vis[now]=1;
      q.push(Data{w.c,i,s+1});
      swap(w.c[i],w.c[x]);
      swap(w.c[i+1],w.c[x+1]);
    }
    q.pop();
  }
  return -1;
}
int main()
{
	ios::sync_with_stdio(0);
  cin>>n;
  for(int i=0;i<n;i++) cin>>a[i],cnt[a[i]=='B']++;
  for(int i=0;i<n;i++) cin>>b[i],cnt[b[i]=='B']--;
  a[n]=a[n+1]=b[n]=b[n+1]='.';
  if(cnt[0]!=0||cnt[1]!=0)//无解
  {
    cout<<-1;
    return 0;
  }
  cout<<BFS();
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

注意到数据范围很小，且每次操作代价为 $1$，考虑 bfs。

状态为 $\{S,d,k\}$：

- $S$ 表示每个方格的状态：空，白，黑。

- $d$ 表示到达这个状态的操作数。

- $k$ 表示目前空的方格为 $k,k+1$。

那么可以枚举一个 $i$，若 $i,i+1$ 都不为空，那么可以与 $k,k+1$ 进行交换，到达下一个状态。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
using namespace std;
typedef double db;
typedef long long ll;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
inline char get(){
	char c;
	while(1){
		c=getchar();
		if(c=='B'||c=='W')
		  continue;
	}
	return c;
}
struct Node{
	string u;
	ll d,k;
};
ll n;
string s,t;
queue<Node> Q;
map<string,bool> f;
void bfs(){
	Q.push({s,0,n});
	while(!Q.empty()){
		auto x=Q.front();
		Q.pop();
		if(x.u==t){
			write(x.d);
			exit(0);
		}
		for(int i=0;i<(n+1);i++){
			if(x.u[i]!=' '&&x.u[i+1]!=' '){
				swap(x.u[i],x.u[x.k]);
				swap(x.u[i+1],x.u[x.k+1]);
				if(!f[x.u]){
					f[x.u]=1;
					Q.push({x.u,x.d+1,i});
				}
				swap(x.u[i],x.u[x.k]);
				swap(x.u[i+1],x.u[x.k+1]);				
			} 
		}
	}
}
int main(){
	n=read();
	cin>>s>>t;
    s+="  ",t+="  ";
	bfs();
	puts("-1");
	return 0;
}
```

---

## 作者：Big_Dinosaur (赞：0)

搜索好题！~~我吃了一发罚时。~~

记空位置为 `..`，石头堆可看作字符串。

对于每个 $S$，每一个 $1\le i<n+2$ 且 $S_i\ne\texttt.$，$S_{i+1}\ne\texttt.$，$S_i,S_{i+1}$ 都可以与两个 `.` 交换，每一种都可变出不同的 $S2$。

此外，每一个 $S$ 无论何时可变化出的 $S2$ 相同。因此每个 $S$ 只需访问一次。

因此，记录字符串与其对应的 `..` 位置，搜索即可，相同的 $S$ 只可遍历一次。此时最坏时间复杂度为 $C_{n+2}^2\times C_n^W$，$W$ 指字符串中 `W` 个数。

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc361_d)

## 思路

看到题目要求最小步数，想到动态规划和广搜；看到 $2\le N\le 14$，直接选择广搜。

读入数据后先寻找两个字符串的每种字母数量是否相等，如果不相等就肯定拼不成，输出 ``-1`` 结束程序。

然后将两个字符串的末尾按照题意随便加上两个字符（我选 `.`，方便对样例）。之后把当前字符串 $S$、当前步数 $0$、当前空位置 $N$（下标从 $0$ 开始的）压入队列并进行搜索。在搜索时可以用 ``map`` 标记这个字符串是否已经被搜索过，如果是就不搜了。

枚举位置的时候进行交换，压入队列，再交换回来。**注意交换枚举是从 $0$ 到 $N$，防止越界**。

如果当前字符串和目标字符串一样，输出当前步数并结束程序。如果整个搜完还没输出过，那么说明不可能找到，最后输出 ``-1``。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ss,tt;
string s,t;
struct node{
	string s;
	int step,posk;//posk 就是空白处的左端点位置。
};queue<node>q;
unordered_map<string,bool>vis;
signed main(){
	cin>>n>>s>>t;
	for(int i=0;i<n;++i){
		if(s[i]=='W')++ss;//统计一种字符即可。
		if(t[i]=='W')++tt;
	}
	if(ss!=tt){
		cout<<-1<<endl;
		return 0;
	}
	s+="..";
	t+="..";
	q.push({s,0,n});
	while(q.size()){
		auto now=q.front();
		q.pop();
		if(vis[now.s])continue;
		vis[now.s]=1;
		if(now.s==t){
			cout<<now.step<<endl;
			return 0;
		}
		for(int i=0;i<n+1;++i){
			if(i==now.posk||i+1==now.posk||i==now.posk+1)continue;//不能拆开空白处或者和自己交换。
			swap(now.s[i],now.s[now.posk]);
			swap(now.s[i+1],now.s[now.posk+1]);
			q.push({now.s,now.step+1,i});
			swap(now.s[i],now.s[now.posk]);
			swap(now.s[i+1],now.s[now.posk+1]);
		}
	}
	cout<<-1;
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc361/submissions/55300470)

---

## 作者：云裳 (赞：0)

题意挺明确的，就不说了。

**思路**

看到 $N\leq14$，一眼搜索，这篇题解采用广搜。

用 `map<string,int> m` 存储答案，`m[i]=j` 表示将原始字符串变为字符串 $i$ 的最小步数为 $j$。

搜索的时候先找出两个相邻的空格，再枚举两个相邻的棋子并尝试与空格交换，如果得到的新字符串没有被记录过就记录一下并将其压入队列。

**代码**

```cpp
#include<bits/stdc++.h>
#define up(i,l,r) for(int i=l,END##i=r;i<=END##i;i++)
#define dn(i,l,r) for(int i=l,END##i=r;i>=END##i;i--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const int INF=0x3f3f3f3f;
ll n;
string s,t;
map<string,ll> mp;
queue<string> q;
namespace sol {
	ll read() {
		ll f=0,x=0;
		char c=getchar();
		while(c<'0'||c>'9') f|=c=='-',c=getchar();
		while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
		return f?-x:x;
	}
	void write(ll x) {
		if(x<0) putchar('-'),x=-x;
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	void solve() {
		n=read();
		cin>>s>>t;
		s=' '+s+"..",t=' '+t+"..";//'.'表示空格
		q.push(s);
		while(!q.empty()) {
			string now=q.front();
			q.pop();
			ll nn=0;
			up(i,1,n+1) if(now[i]=='.'&&now[i+1]=='.') {
				nn=i;
				break;
			}
			up(i,1,n+1) {
				if(now[i]!='.'&&now[i+1]!='.') {
					string ch=now;
					swap(ch[i],ch[nn]),swap(ch[i+1],ch[nn+1]);
					if(!mp.count(ch)) mp[ch]=mp[now]+1,q.push(ch);//map 直接下标访问的话即使当前位置没有值也会给你另开一个，所以要用 count 判断
				}
			}
		}
		if(!mp.count(t)) puts("-1");
		else write(mp[t]);
	}
}
using namespace sol;
signed main() {
	solve();
	return 0;
}

```

---

