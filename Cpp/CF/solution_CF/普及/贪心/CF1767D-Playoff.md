# Playoff

## 题目描述

$ 2^n $ teams participate in a playoff tournament. The tournament consists of $ 2^n - 1 $ games. They are held as follows: in the first phase of the tournament, the teams are split into pairs: team $ 1 $ plays against team $ 2 $ , team $ 3 $ plays against team $ 4 $ , and so on (so, $ 2^{n-1} $ games are played in that phase). When a team loses a game, it is eliminated, and each game results in elimination of one team (there are no ties). After that, only $ 2^{n-1} $ teams remain. If only one team remains, it is declared the champion; otherwise, the second phase begins, where $ 2^{n-2} $ games are played: in the first one of them, the winner of the game " $ 1 $ vs $ 2 $ " plays against the winner of the game " $ 3 $ vs $ 4 $ ", then the winner of the game " $ 5 $ vs $ 6 $ " plays against the winner of the game " $ 7 $ vs $ 8 $ ", and so on. This process repeats until only one team remains.

The skill level of the $ i $ -th team is $ p_i $ , where $ p $ is a permutation of integers $ 1 $ , $ 2 $ , ..., $ 2^n $ (a permutation is an array where each element from $ 1 $ to $ 2^n $ occurs exactly once).

You are given a string $ s $ which consists of $ n $ characters. These characters denote the results of games in each phase of the tournament as follows:

- if $ s_i $ is equal to 0, then during the $ i $ -th phase (the phase with $ 2^{n-i} $ games), in each match, the team with the lower skill level wins;
- if $ s_i $ is equal to 1, then during the $ i $ -th phase (the phase with $ 2^{n-i} $ games), in each match, the team with the higher skill level wins.

Let's say that an integer $ x $ is winning if it is possible to find a permutation $ p $ such that the team with skill $ x $ wins the tournament. Find all winning integers.

## 样例 #1

### 输入

```
3
101```

### 输出

```
4 5 6 7```

## 样例 #2

### 输入

```
1
1```

### 输出

```
2```

## 样例 #3

### 输入

```
2
01```

### 输出

```
2 3```

# 题解

## 作者：honglan0301 (赞：10)

## 题目分析

先不考虑所谓的规律（稍微改一下就可以让这个规律消失），我们来想想更一般的做法。

不妨先按照题设规则，建出一棵完全二叉树来（事实上，改变树的形状也并不影响做法），那么问题即为在叶节点上任意给出 $1$ 至 $2^n$ 的点权 $w$，而对于其它节点 $u$, 若它的胜负规则为 $0$, 则 $w(u)=\min(w(son))$, 反之 $w(u)=\max(w(son))$, 我们要求出根节点点权的所有可能值。例如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/yc9bcflr.png)

容易知道只需要算出根节点可能的最大点权和最小点权，于是我们开始 dp, 令 $f(i)$ 表示 $w(i)$ 在 $i$ 的子树中最大排多少名， $g(i)$ 表示最小排多少名。

那么当 $w(i)=\min(w(son))$ 时，显然在 $i$ 的子树中至少有 $\sum f(son)$ 的点权比 $i$ 大，而至少只有 $\min(g(son))$ 个点权比 $i$ 小，故推出 $f(i)=\sum f(son),\ g(i)=\min(g(son))$。反之 $f(i)=\min(f(son)),\ g(i)=\sum g(son)$。

于是 dp 一遍，答案就是 $[g(1),2^n-f(1)+1]$ 内的所有正整数。

------------
再解释几个问题，一是为什么根节点排名的取值是连续的。这一点我们可以考虑自底向上归纳，因为叶节点点权的排名是连续的（固定的），而一次递推时必然介于最小值与最大值间的数都可以被构造出来，故都是连续的。

二是为什么会有“规律”。这次的题设比较简单，只给定了每一层全体的胜负规则，故每一层里所有节点的 $f$ 和 $g$ 都是相同的。那么我们不妨从上至下分层，设 $f(i)$ 表示第 $i$ 层节点的 $f$, $g(i)$ 表示第 $i$ 层节点的 $g$,每当这一层的规则为 $0$ 时，$f(i)=2\times f(i+1)$, 每当这一层的规则为 $1$ 时，$g(i)=2\times g(i+1)$，而又有 $f(n+1)=g(n+1)=1$, “规律”显然。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
using namespace std;

int n,cnt,head[600005],dp1[600005],dp2[600005],zt[600005];

char s[25];

struct edge
{
	int son;
	int next;
}edge[600005];
void adde(int x,int y)
{
	cnt++;
	edge[cnt].son=y;
	edge[cnt].next=head[x];
	head[x]=cnt;
}

void dfs(int now)
{
	if(now>=(1<<n))
	{
		dp1[now]=dp2[now]=1;
		return;
	}
	dp1[now]=10000000,dp2[now]=10000000;
	if(!zt[now])
	{
		dp1[now]=0;
		for(int i=head[now];i>0;i=edge[i].next)
		{
			dfs(edge[i].son);
			dp1[now]+=dp1[edge[i].son];
			dp2[now]=min(dp2[now],dp2[edge[i].son]);
		}
	}
	else
	{
		dp2[now]=0;
		for(int i=head[now];i>0;i=edge[i].next)
		{
			dfs(edge[i].son);
			dp2[now]+=dp2[edge[i].son];
			dp1[now]=min(dp1[now],dp1[edge[i].son]);
		}
	}
}

int main()
{
	cin>>n;
	for(int i=1;i<=(1<<n)-1;i++)
	{
		adde(i,2*i);
		adde(i,2*i+1);
	}
	cin>>s;
	for(int i=0;i<=n-1;i++)
	{
		if(s[i]=='0')
		{
			for(int j=(1<<(n-1-i));j<(1<<(n-i));j++)
			{
				zt[j]=0;
			}
		}
		else
		{
			for(int j=(1<<(n-1-i));j<(1<<(n-i));j++)
			{
				zt[j]=1;
			}
		}
	}
	/*for(int i=1;i<=(1<<n)-1;i++)
	{
		cout<<i<<" "<<zt[i]<<endl;
	}*/
	dfs(1);
	for(int i=dp2[1];i<=(1<<n)-dp1[1]+1;i++)
	{
		cout<<i<<" ";
	}
}
```


---

## 作者：Leasier (赞：9)

Update on 2023.8.5：感谢 [KannaStella](https://www.luogu.com.cn/user/773833)。

------------

考虑建出一棵 $n + 1$ 层的完全二叉树。

直接计算具体哪些数可以为胜者不太方便，考虑先求出胜者的最大和最小值。

设 $f(x), g(x)$ 分别表示 $x$ 子树内胜者的最大排名（从小到大）和最小排名（从大到小），则：

- $\forall x \in \operatorname{leaf}$，$f(x) = g(x) = 1$。
- $\forall x \not\in \operatorname{leaf}$，当 $s_{n - depth_x + 1} = 0$，$f(x) = f(ls_x) + f(rs_x)$，$g(x) = \min(g(ls_x), g(rs_x))$；否则，$f(x) = \min(f(ls_x), f(rs_x))$，$g(x) = g(ls_x) + g(rs_x)$。

设 $1$ 的个数为 $x$，则 $f(root) = 2^x$，$g(root) = 2^{n - x}$，于是 $[2^x, 2^n - 2^{n - x} + 1]$ 中的数才可能成为胜者。

不难归纳证明，对于树上任意点 $x$，排名在 $[f(x), size_x - g(x) + 1]$ 内的数都可能成为胜者，于是输出上面那个区间内的数即可。

代码：
```cpp
#include <stdio.h>

char s[27];

int main(){
	int n, x = 0, up;
	scanf("%d", &n);
	scanf("%s", &s[1]);
	for (int i = 1; i <= n; i++){
		if (s[i] == '1') x++;
	}
	up = (1 << n) - (1 << (n - x)) + 1;
	for (int i = 1 << x; i <= up; i++){
		printf("%d ", i);
	}
	return 0;
}
```

---

## 作者：pineappler (赞：4)

非常好 trick，使我的大脑旋转。  

先说结论：  

**设在题目给出的 $s$ 数组中有 $x$ 个 $1$，$y$ 个 $0$。**  
**则可以最终获胜的队伍的能力值为闭区间 $[2^x,2^n-2^y+1]$ 中的任意值。**

以下将采用递推方法证明此结论。

![](https://cdn.luogu.com.cn/upload/image_hosting/chdafj5j.png)

以样例三为例，$s=\{0,1\}$（圆圈内的值是节点编号，用 $i\times 2$ 表示点 $i$ 的左儿子，$i \times 2 + 1$ 表示点 $i$ 的右儿子）。

设 $g$ 数组中，$g_i$ 表示**以这个节点为根的子树中**有至少多少个**叶子节点**的能力值比它**小**；$h_i$ 表示**以这个节点为根的子树中**有至少多少个**叶子节点**的能力值比它**大**。

根据定义得到 $g$ 数组和 $h$ 数组从下至上的转移方程：  
如果这个点的层数在 $s$ 中对应的规则为 $1$，则：   
$g_i = g_{i \times 2} + g_{i\times 2+1}+1$  
$h_i = \max(f_{i\times 2},f_{i\times 2+1})$  
反之，则：    
$g_i = \max(g_{i\times 2},g_{i\times 2+1})$  
$h_i = h_{i \times 2} + h_{i\times 2+1}+1$  

最终答案为 $[h_{root}+1,g_{root}-1]$。  

到这里，使用这个转移方程，采用暴力递推的方法已经可以通过此题了，接下来我们来尝试找更简单的规律：

在给出的例子中：  
$g_1=1$，$h_1=1$  
$g_2=g_3=1$，$h_2=h_3=0$  
$g_4=g_5=g_6=g_7=0$，$h_4=h_5=h_6=h_7=0$（叶子节点默认为 $0$）  

很容易发现，每一层的 $h$ 值都相等，$g$ 值同理（从公式也能看出来）。所以 $\max$ 可以省略，还很容易发现，$h$ 和 $g$ 互相独立。

于是，改设 $h$ 和 $g$ 的下标表示第 $i$ 层的共同值，得到：
如果这个点对应的规则为 $1$，则：   
$g_i = g_{i+2}\times 2+1$  
$h_i = h_{i+1}$  
如果这个点对应的规则为 $0$，则：    
$g_i = g_{i+1}$  
$h_i = h_{i+1} \times 2+1$  

通过这四个式子很容易发现其实比赛规则在哪一层并不重要，我们只关心每种规则有多少个。简而言之，每当 $s$ 数组中出现了一个 $1$，便会对 $g$ 产生贡献，反之会对 $h$ 产生贡献。简单归纳便可推出最终答案。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=20;
char c[N];
int quickpow(int a,int k){
	int ans=1;
	while(k){
		if(k&1) ans*=a;
		a*=a;
		k/=2;
	}
	return ans;
}
int main(){
	int n;
	scanf("%d",&n);
	scanf("%s",c+1);
	int cnt1=0,cnt0=0;
	for(int i=1;i<=n;i++){
		if(c[i]=='0') cnt0++;
		else cnt1++;
	}
	for(int i=quickpow(2,cnt1);i<=quickpow(2,n)-quickpow(2,cnt0)+1;i++){
		printf("%d ",i);
	}
	return 0;
}
```

---

## 作者：CashCollectFactory (赞：1)

# 启发式打表题解看这里

首先，我们根据题意写一个暴力程序，用于打表。考虑到 ```next_permutation()```  函数在此时会导致程序统计大量的重复答案，当 $n$ 超过 $4$ 时就无法在可以忍受时间内算出所有答案，我们采用 ```random_shuffle()``` 这个随机打乱函数，这样效率就大大提升啦！具体代码实现如下：


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[300005]; //大于2^18即可 
set<int> st; //一个用于去重的set 
int main(){
	int n;
	string s;
	cin>>n>>s;
	int m=1<<n;
	for(int i=1;i<=m;i++) a[i]=i; //创造初始排列 
	do{
		random_shuffle(a+1,a+1+m); //随机打乱一下 
		vector<int> v,tem;
		for(int i=1;i<=m;i++) v.push_back(a[i]);
		for(int i=0;i<n;i++){
			int sz=v.size();
			for(int j=0;j<sz;j+=2){
				if(s[i]=='1') tem.push_back(max(v[j],v[j+1]));
				else tem.push_back(min(v[j],v[j+1]));
			}
			v=tem;
			tem.clear();
		}//暴力统计此时的最终能力值 
		if(st.count(v[0])==0) cout<<v[0]<<" "; //将可能的答案输出 
		st.insert(v[0]);
	}while(1);//死循环，一直找
	return 0;
}
```
当 $n=3$ 时，最终打表结果：


| $s=$ |结果|
|:-:|:-:|
| $000$ | $1$ |
| $001$ | $2,3,4,5$ |
| $010$ | $2,3,4,5$ |
| $100$ | $2,3,4,5$ |
| $110$ | $4,5,6,7$ |
| $101$ | $4,5,6,7$ |
| $011$ | $4,5,6,7$ |
| $111$ | $8$ |

初步发现，结果与 $0$ 和 $1$ 的位置无关，仅与 $0$ 和 $1$ 的数目有关。

当 $n=4$ 时，最终打表结果：

| $s$ 里面几个 $1$ |结果|
|:-:|:-:|
|$0$|$1$|
|$1$|$2,3,4,5,6,7,8,9$|
|$2$|$4,5,6,7,8,9,10,11,12,13$|
|$3$|$8,9,10,11,12,13,14,15$|
|$4$|$16$|

首先观察到，设 $s$ 里面 $1$ 的个数为 $cnt$，则结果的第一个数永远是 $2^{cnt}$。

然后，我们不难发现结果具有严格的对称性，即从上到下增加的数的个数和从下到上对称位置增加的数的个数是相同的，由此可以推算出最后一个数为 $2^n-2^{n-cnt}+1$。

最终结果仅需输出这两个边界之间的数即可，具体实现参考下方代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	string s;
	cin>>n>>s;
	int cnt=0;
	for(int i=0;i<n;i++) if(s[i]=='1') cnt++;
	int l=(1<<cnt);//左边界 
	cnt=n-cnt;
	int r=(1<<n)-(1<<cnt)+1; //右边界 
	for(int i=l;i<=r;i++) cout<<i<<" ";
	return 0;
}

```

---

## 作者：CAO654321 (赞：1)

## Solution:

这道题我们只考虑 $x$ 至少比多少个数大，比多少个数小，以前者为例。若这一层需要比对方小，忽略；否则，比对方大。设当前比 $a$ 个人大，由对称性，现在 PK 的人也比 $a$ 个人大，且还要算上那个人，那么执行赋值操作 $a=2a + 1$。

## Code:
```c
#include <bits/stdc++.h>
#define x first
#define int long long
#define y second
#define ios ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<char,int> PCI;
typedef pair<LL,LL> PLL;
typedef unsigned long long ULL;
const int N=2e5+10,INF = 1e9 ,mod = 1e9 + 7 ,P = 131;
const double eps = 1e-7;
int p[N],q[N]; 
vector<int> pos[N];
int n;
void solve()
{
    string s;    
    cin >> n >> s ;
    int k = count(s.begin(),s.end(),'1');  
    for(int x = 1 << k ;x <= (1<<n) - (1<<(n-k)) + 1;x ++ )
    cout << x  << " ";
}
signed main()
{
    ios
    LL T=1;
    while(T -- )
    {
        solve();
    }
    return 0;
}

```

---

## 作者：浮光掠影 (赞：0)

### 题目大意

读入 $n$，代表有 $2^n$ 个队伍参加比赛，每次相邻的两个队比赛，字符串中 ``0`` 表示分低的胜利，``1`` 表示分高的胜利。

### 解题思路

对于 $a<b<c<d$：字符串是 ``01`` 或者 ``10``，可以发现都只有 $b,c$ 可以赢得比赛，字符串中 ``01`` 的顺序对答案没有影响。

- ``1`` 的个数 $x$：使得前 $[1,2^x)$ 都会被淘汰掉；
- ``0`` 的个数 $y$：使得后面 $(2^n-2^y+1,2^n]$ 都被淘汰掉；

最终留下 $[2^x,2^n - 2^y +1]$。


### AC 代码


```cpp
#include <bits/stdc++.h>
#define x first
#define int long long
#define y second
#define ios ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
using namespace std;
 
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<char,int> PCI;
typedef pair<LL,LL> PLL;
//typedef __int128 i128;
typedef unsigned long long ULL;
const int N=2e5+10,INF = 1e9 ,mod = 1e9 + 7 ,P = 131;
const double eps = 1e-7;
int p[N],q[N]; 
vector<int> pos[N];
 
 
int n;
void solve()
{
    string s;    
    cin >> n >> s ;
    int k = count(s.begin(),s.end(),'1');
    
    for(int x = 1 << k ;x <= (1<<n) - (1<<(n-k)) + 1;x ++ )
    cout << x  << " ";
}
signed main()
{
//    freopen("1.txt","r",stdin);
    ios
    LL T=1;
//    cin>>T;
    while(T -- )
    {
        solve();
    }
    return 0;
}
```

---

