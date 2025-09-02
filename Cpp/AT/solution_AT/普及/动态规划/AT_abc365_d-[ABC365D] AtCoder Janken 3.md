# [ABC365D] AtCoder Janken 3

## 题目描述

高桥和青木玩了 $N$ 次石头剪刀布。注：在这个游戏中，石头赢剪刀，剪刀赢纸，纸赢石头。

青木的动作由长度为 $N$ 的字符串 $S$ 表示，字符串由 `R`、`P` 和 `S` 组成。$S$ 中的第 $i$ 个字符表示青木在第 $i$ 盘棋局中的棋步：`R` 表示石头，`P` 表示 纸，`S` 表示剪刀。

高桥的棋步满足以下条件：

- 高桥从未输给过青木。
- 对于 $i=1,2,…,N−1$，高桥在第 $i$ 对局中的棋步与他在第 $i+1$ 对局中的棋步不同。

求高桥可能赢的最大对局数。

可以保证存在一个满足上述条件的高桥下棋顺序。

## 说明/提示

$1 \le n \le 2\times 10^5$

## 样例 #1

### 输入

```
6
PRSSRS```

### 输出

```
5```

## 样例 #2

### 输入

```
10
SSSSSSSSSS```

### 输出

```
5```

## 样例 #3

### 输入

```
24
SPRPSRRRRRPPRPRPSSRSPRSS```

### 输出

```
18```

# 题解

## 作者：xhxxwcr (赞：8)

~~这是我见过最简单的 D 题了~~，但由于将一个 0 写成了 1：

$\text{AC} \to \text{WA}$  
$100 \to 0$  
………………  

好，步入正题。

### 贪心

这题首先考虑贪心：在每一次可能获胜的情况下获胜。  

但是，如果我这一局选择平局，那么可能为下一局乃至最后增加更多的获胜机会。  

所以，贪心 PASS！

### 动规（dp）

那么，既然贪心被 PASS，那就得要 dp 闪亮登场了。  
由于我们不知道，每一局高桥是获胜好，还是平局好，所以我们需要一个二维 dp，$dp[i][0]$ 表示在第 $i$ 局平局的总最大获胜数，$dp[i][1]$ 表示在第 $i$ 局获胜的总最大获胜数。  

考虑一下两种情况：  
- 当青木与上一局出同一棋步：  

那么，在出同一棋步的情况下，如果这一轮高桥想要获胜，上一局一定平局；反之，上一局必定获胜。

```cpp
if(s[i - 1] == s[i]){
    dp[i][1] = dp[i - 1][0] + 1;
    dp[i][0] = dp[i - 1][1];
}
```

- 当青木与上一局出不同棋步：  
  1. 通过相同方式得来

     那么，高桥这一局如果获胜、平局，那么一定可以通过上一局的获胜、平局得来。
     
  1. 通过不同方式得来

     那么，有没有可能通过不同方式得来？当然有可能，但得建立在这个条件上：

     平局：上一句赢得条件不是这一局的平局条件。

     获胜：上一局平局条件不是这一句的获胜条件。
```cpp
else{
    dp[i][1] = dp[i - 1][1] + 1;
    dp[i][0] = dp[i - 1][0];
    if(!((s[i - 1] == 'P' && s[i] == 'S')||(s[i - 1] == 'S' && s[i] == 'R')||(s[i - 1] == 'R' && s[i] == 'P'))){
    dp[i][0] = max(dp[i][0],dp[i - 1][1]);
    }//如果上一局的获胜不是这一局平局的关键
    if(!((s[i] == 'P' && s[i - 1] == 'S')||(s[i] == 'S' && s[i - 1] == 'R')||(s[i] == 'R' && s[i - 1] == 'P'))){
    dp[i][1] = max(dp[i][1],dp[i - 1][0] + 1);
    }//如果上一局的平局不是这一局获胜的关键
}
```
### AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200010];
int dp[200010][2];//1:赢,0:平
int main(){
    int n,ans;
    cin >> n;
    dp[1][1] = 1;
    for(int i = 1;i <= n;i++){
        cin >> s[i];
    }
    for(int i = 2;i <= n;i++){
        if(s[i - 1] == s[i]){
            dp[i][1] = dp[i - 1][0] + 1;
            dp[i][0] = dp[i - 1][1];
        }else{
            dp[i][1] = dp[i - 1][1] + 1;
            dp[i][0] = dp[i - 1][0];
            if(!((s[i - 1] == 'P' && s[i] == 'S')||(s[i - 1] == 'S' && s[i] == 'R')||(s[i - 1] == 'R' && s[i] == 'P'))){
                dp[i][0] = max(dp[i][0],dp[i - 1][1]);
            }//如果上一局的获胜不是这一局平局的关键
            if(!((s[i] == 'P' && s[i - 1] == 'S')||(s[i] == 'S' && s[i - 1] == 'R')||(s[i] == 'R' && s[i - 1] == 'P'))){
                dp[i][1] = max(dp[i][1],dp[i - 1][0] + 1);
            }//如果上一局的平局不是这一局获胜的关键
        }
    }
    cout << max(dp[n][1],dp[n][0]);
}
```

---

## 作者：wo_hen_la (赞：5)

首先用 $dp_{i,j}$ 表示前 $i$ 局，且第 $i$ 局出剪刀、布、石头能赢的最大局数，其中 $j$ 的取值是 $1,2,3$，分别表示石头、布、剪刀。

转移，题中说不能输，所以我们只能出与对方相同的或能赢对方的，例如对方出石头，那么只有布和石头能**被**转移。其中布只能由剪刀和石头转移过来，且要加 $1$（布赢石头）。石头同理，但因为平局不能加 $1$。

### Code

```cpp
  cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];//1表示石头 2表示布 3表示剪刀
	for(int i=1;i<=n;i++){
		if(a[i]=='R'){//石头
			dp[i][1]=max(dp[i-1][2],dp[i-1][3]);
			dp[i][2]=max(dp[i-1][1],dp[i-1][3])+1;
		}
		if(a[i]=='P'){//布
			dp[i][3]=max(dp[i-1][1],dp[i-1][2])+1;
			dp[i][2]=max(dp[i-1][1],dp[i-1][3]);
		}
		if(a[i]=='S'){//剪刀
			dp[i][1]=max(dp[i-1][2],dp[i-1][3])+1;
			dp[i][3]=max(dp[i-1][1],dp[i-1][2]);
		}
	}
	int ans=max(dp[n][1],max(dp[n][2],dp[n][3]));
	cout<<ans;
```

---

## 作者：Pink_Cut_Tree (赞：5)

# AT_abc365_d [ABC365D] AtCoder Janken 3 题解

upd on 2024.8.11 感谢 [abstractROMANCE](https://www.luogu.com.cn/user/935976) 关于“后效性”的建议，已更新。

### 解析

一眼 dp。为什么呢？因为每一个操作都**无**后效性，说白了就是前面的操作**不会**对后面的操作产生影响。

我们定义状态为已经玩了 $i$ 局，上一局自己出了某种手势可以赢的最多方案数。

怎么转移呢？任何一种手势都是从上局没出过的两种手势中的最大值转移。输给对方的手势肯定不能出，压根不用转移直接设为 $-\infty$ 即可。与对方平的手势直接转移即可，赢对方的手势转移时要加 $1$。

### 代码


```cpp
#include<bits/stdc++.h> //抽象的头文件
using namespace std;
#define int long long
const int N=2e5+5,inf=-1e9; //注意这里 inf 不是 1e9 而是 -1e9！！！
int n,ans;
string s;
int dp[3][N]; //P-0,R-1,S-2
signed main(){
	cin.tie(0)->sync_with_stdio(0); //抽象的读优
	cin>>n; //抽象的读入
	cin>>s; //S->P->R->S
	if(s[0]=='R'){ //抽象的初始化
		dp[0][0]=1,dp[1][0]=0,dp[2][0]=inf;
	}
	else if(s[0]=='P'){
		dp[0][0]=0,dp[1][0]=inf,dp[2][0]=1;
	}
	else{
		dp[0][0]=inf,dp[1][0]=1,dp[2][0]=0;
	}
	for(int i=1;i<n;i++){ //抽象的转移
		if(s[i]=='R'){
			dp[2][i]=inf,dp[1][i]=max(dp[2][i-1],dp[0][i-1]),dp[0][i]=max(dp[1][i-1],dp[2][i-1])+1;
		}
		else if(s[i]=='P'){
			dp[1][i]=inf,dp[0][i]=max(dp[2][i-1],dp[1][i-1]),dp[2][i]=max(dp[1][i-1],dp[0][i-1])+1;
		}
		else{
			dp[0][i]=inf,dp[2][i]=max(dp[1][i-1],dp[0][i-1]),dp[1][i]=max(dp[0][i-1],dp[2][i-1])+1;
		}
	}
	cout<<max({dp[0][n-1],dp[1][n-1],dp[2][n-1]}); //抽象的输出
return 0;
}
```

---

## 作者：shitingjia (赞：3)

[传送门](https://www.luogu.com.cn/problem/AT_abc365_d)

### 题目思路
哇，简单的动态规划，这次第四题太让人感动了。

十分钟后：完了，样例三过不了，~~躺平~~。

为什么？题面中有一句话是“高桥从未输给过青木”。刚开始时没注意，后来一想，这句话的意思是：当高桥无法赢时，他选择**打平，不能输**。

用 $dp[i][j]$ 表示高桥在第 $i$ 局游戏中出某个手势，最多能赢的局数。其中 $0$ 代表石头，$1$ 代表布，$2$ 代表剪刀。每次转移时，根据上一次另外两个手势的最大答案来更新。接着，判断这次对手出的手势，将必赢的情况加一，将必输的情况设为无限小，代表走不通。

最后答案就是 $dp[n][0]$、$dp[n][1]$、$dp[n][2]$ 之中的最大值。

### AC Code

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=2e5+5;
int n,dp[N][4];//0 石头,1 布,2 剪刀     
char a[N]; 
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1;i<=n;i++){
		dp[i][0]=max(dp[i-1][1],dp[i-1][2]);//选不同的手势
		dp[i][1]=max(dp[i-1][0],dp[i-1][2]);
		dp[i][2]=max(dp[i-1][0],dp[i-1][1]);
		if(a[i]=='R'){
			dp[i][1]++;//赢了，赢的局数加一
			dp[i][2]=-1e9;//输了，一定不能出现这种情况，赋无限小
		}
		if(a[i]=='P'){
			dp[i][2]++;
			dp[i][0]=-1e9;
		}
		if(a[i]=='S'){
			dp[i][0]++;
			dp[i][1]=-1e9;
		}
	}
	int ans=max(dp[n][0],max(dp[n][1],dp[n][2]));
	cout<<ans;
	return 0;
}
```

---

## 作者：穼柗° (赞：3)

#### 温馨提示：在[专栏](https://www.luogu.com/article/oragh0d9)食用效果更佳。

这道题可以用动态规划。

以下我用 $S_x$ 表示输入字符串的第 $x+1$ 个字符。

## 状态定义
$dp_{x,0}$ 表示第 $x$ 个位置使用剪刀，前 $x$ 轮赢的最多回合数；\
$dp_{x,1}$ 表示第 $x$ 个位置使用石头，前 $x$ 轮赢的最多回合数；\
$dp_{x,2}$ 表示第 $x$ 个位置使用布，前 $x$ 轮赢的最多回合数；\
特别地，如果使用该道具会输，那么为 $0$。

## **边界**
$
dp_{0,0} = \begin{Bmatrix}
1,S_i=P\\
0,S_i\neq P
\end{Bmatrix}\\
dp_{0,1} = \begin{Bmatrix}
1,S_i=S\\
0,S_i\neq S
\end{Bmatrix}\\
dp_{0,2} = \begin{Bmatrix}
1,S_i=R\\
0,S_i\neq R
\end{Bmatrix}\\
dp_{x,0}=dp_{x,1}=dp_{x,2}=0，0<x<n
$

## 状态转移
- 当 $S_i$ 为 `P` 时：\
$dp_{i,0}=\max \{ dp_{i-1,1},dp_{i-1,2} \}+1$，$dp_{i,2}=\max \{ dp_{i-1,0},dp_{i-1,1} \}$
- 当 $S_i$ 为 `S` 时：\
$dp_{i,0}=\max \{ dp_{i-1,1},dp_{i-1,2} \}$，$dp_{i,1}=\max \{ dp_{i-1,0},dp_{i-1,2} \}+1$
- 当 $S_i$ 为 `R` 时：\
$dp_{i,1}=\max \{ dp_{i-1,0},dp_{i-1,2} \}$，$dp_{i,2}=\max \{ dp_{i-1,0},dp_{i-1,1} \}+1$

答案就是 $\max\{dp_{n-1,0},dp_{n-1,1},dp_{n-1,2}\}$。

### Code
```cpp
#include <cstdio>
#include <algorithm>
#define S 0 
#define R 1
#define P 2
using namespace std;
char last,dec[128],s[200001];
int n,ans,ddc[128],dp[200000][3];
int main() {
	scanf("%d%s",&n,s),
	dec['S']='R',dec['P']='S',dec['R']='P', // dec[c] 能克 c
	ddc['S']=S,ddc['P']=P,ddc['R']=R, // 字符转数字，省dp数组的空间
	dp[0][ddc[dec[s[0]]]]=1;
	for(int i=1;i<n;i++)
		dp[i][ddc[dec[s[i]]]]=max(dp[i-1][(ddc[dec[s[i]]]+1)%3],dp[i-1][(ddc[dec[s[i]]]+2)%3])+1,
		dp[i][ddc[s[i]]]=max(dp[i-1][(ddc[s[i]]+1)%3],dp[i-1][(ddc[s[i]]+2)%3]);
	printf("%d",max({dp[n-1][S],dp[n-1][R],dp[n-1][P]}));
	return 0;
}
```

#### 注：禁止抄代码！

---

## 作者：PineappleSummer (赞：3)

太板了吧。

设 $dp_{i,1}$ 为第 $i$ 次出石头的最大获胜次数，$dp_{i,2}$ 为第 $i$ 次出布的最大获胜次数，$dp_{i,3}$ 为第 $i$ 次出剪刀的最大获胜次数。

分讨一下转移。

- 如果 $s_i$ 为 `R`，说明这一次只能出石头或布，$dp_{i,1}=\max(dp_{i-1,2},dp_{i-1,3})$，$dp_{i,2}=\max(dp_{i-1,1},dp_{i-1,3})+1$。

- 如果 $s_i$ 为 `P`，说明这一次只能出布或剪刀，$dp_{i,2}=\max(dp_{i-1,1},dp_{i-1,3})$，$dp_{i,3}=\max(dp_{i-1,1},dp_{i-1,2})+1$。

- 如果 $s_i$ 为 `S`，说明这一次只能出剪刀或石头，$dp_{i,3}=\max(dp_{i-1,1},dp_{i-1,2})$，$dp_{i,1}=\max(dp_{i-1,2},dp_{i-1,3})+1$。

[代码](https://atcoder.jp/contests/abc365/submissions/56467554)，时间复杂度 $\mathcal O(n)$。

---

## 作者：gejunyi1Longer2csbs (赞：2)

### AT_abc365_D Atcoder Janken 3 题解

---

**题意**

已知对方 $ n $ 局石头剪刀布的出法，让你规划你的出法使得赢的局数最多且相邻两局出不同手势。注意：你永远也不会输。

**思路**

考虑动态规划，设 $ dp_{i,j} $ 为在第 $ i $ 局出手势 $ j $ 赢的最大局数。若当前对方手势为 $ x_i $，出 $ need_x $ 可以赢，出 $ x_i $ 平局，容易推出以下式子：

$$
\left\{\begin{matrix}
dp_{i,x_i} = max\left\{\begin{matrix}
dp_{i-1,x_{i-1}} & (x_{i-1} != x_i)\\
dp_{i-1,need_{x_{i-1}}} & (need_{x_{i-1}} != x_i)
\end{matrix}\right.\\
dp_{i,need_{x_i}} = max\left\{\begin{matrix}
dp_{i-1,x_{i-1}} & (x_{i-1} != need_{x_i})\\
dp_{i-1,need_{x_{i-1}}} & (need_{x_{i-1}} != need_{x_i})
\end{matrix}\right.+1\\
\end{matrix}\right.
$$

输了不转移，剩下的就从上一局其他两个选最大值更新即可。

**code**

~~~cpp

#include <bits/stdc++.h>
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
using namespace std;
int n,need[4] = {0,2,3,1},a[200005],dp[200005][4];
char s;
int main(){
  fst
  cin >> n;
  for (int i = 1;i <= n;i++){
    cin >> s;
    if (s == 'S') a[i] = 1;
    else if (s == 'R') a[i] = 2;
    else a[i] = 3;
  }
  for (int i = 1;i <= n;i++){
    dp[i][a[i]] = max(a[i - 1] != a[i] ? dp[i - 1][a[i - 1]] : 0,need[a[i - 1]] != a[i] ? dp[i - 1][need[a[i - 1]]] : 0);
    dp[i][need[a[i]]] = max(need[a[i - 1]] != need[a[i]] ? dp[i - 1][need[a[i - 1]]] : 0,need[a[i]] != a[i - 1] ? dp[i - 1][a[i - 1]] : 0) + 1;
  }
  cout << max(dp[n][need[a[n]]],dp[n][a[n]]);
  return 0;
}

~~~

---

## 作者：Ivan422 (赞：1)

定义 $f_{j,i}$ 为第 $i$ 局出 $j$ 的最大胜局数。

当 $s_i$ 不为 `S`，可以出 `P`，$f_{0,i}=\max(f_{1,i-1},f_{2,i-1})$，如果在 $s_i$ 为 `R`，那么 $f_{0,i}=\max(f_{1,i-1},f_{2,i-1})+1$。

当 $s_i$ 不为 `P`，可以出 `R`，$f_{1,i}=\max(f_{0,i-1},f_{2,i-1})$，如果在 $s_i$ 为 `S`，那么 $f_{1,i}=\max(f_{0,i-1},f_{2,i-1})+1$。

当 $s_i$ 不为 `R`，可以出 `S`，$f_{2,i}=\max(f_{0,i-1},f_{1,i-1})$，如果在 $s_i$ 为 `P`，那么 $f_{2,i}=\max(f_{0,i-1},f_{1,i-1})+1$。

转移完成。最终答案即为 $\max(f_{0,n},f_{1,n},f_{2,n})$。


```pascal
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=1e6+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,cnt,len,f[3][N];
string s;
signed main(){
	cin>>n>>s;s=" "+s;
	for(int i=1;i<=n;i++){
		if(s[i]!='S')f[0][i]=max(f[1][i-1],f[2][i-1])+int(s[i]=='R');
		if(s[i]!='P')f[1][i]=max(f[0][i-1],f[2][i-1])+int(s[i]=='S');
		if(s[i]!='R')f[2][i]=max(f[0][i-1],f[1][i-1])+int(s[i]=='P');
	}
	cout<<max({f[0][n],f[1][n],f[2][n]});
    return 0;
}
```

---

## 作者：Ame_wiki (赞：1)

原题链接：[link](https://atcoder.jp/contests/abc365/tasks/abc365_d)。

题意：
已知对方 $n$ 局石头剪刀布的出法，让你规划你的出法使得赢的局数最多且相邻两局出不同手势。

思路：考虑 dp 转移，设 $f_{i,j}$ 为在第 $i$ 局出手势 $j$ 赢的最大局数。若当前对方手势为 $x$，出 $y$ 可以赢，出 $x$ 不赢不输，出 $k$ 输，容易推出以下式子：

$\left\{\begin{matrix} 
f_{i,y}=\max (f_{i-1,x},f_{i-1,k})+1\\
f_{i,x}=\max (f_{i-1,y},f_{i-1,k})
\end{matrix}\right. $

输了自然不转移，剩下的就从上一局其他两个选最大值更新即可。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define endl "\n"
#define lowbit(x) (x&(-x))
#define sort stable_sort

const int N=2e5+5,M=5005,inf=1e18;

int n;
char s[N];
int f[N][40];

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++){
		if(s[i]=='R'){
			f[i]['R'-'A']=max(f[i-1]['S'-'A'],f[i-1]['P'-'A']);
			f[i]['P'-'A']=max(f[i-1]['S'-'A'],f[i-1]['R'-'A'])+1;
		}
		if(s[i]=='S'){
			f[i]['R'-'A']=max(f[i-1]['S'-'A'],f[i-1]['P'-'A'])+1;
			f[i]['S'-'A']=max(f[i-1]['P'-'A'],f[i-1]['R'-'A']);
		}
		if(s[i]=='P'){
			f[i]['S'-'A']=max(f[i-1]['P'-'A'],f[i-1]['R'-'A'])+1;
			f[i]['P'-'A']=max(f[i-1]['S'-'A'],f[i-1]['R'-'A']);
		}
	}
	cout<<max(max(f[n]['P'-'A'],f[n]['S'-'A']),f[n]['R'-'A']);//取最后三个手势最大的 
	return 0;
}


```

---

## 作者：hymcr05 (赞：1)

# D - AtCoder Janken 3题解

## 题意

    高桥和青木要玩石头剪刀布，给你一个长度为 $n$ 的字符串 $s$，$s$ 表示青木在第 $i$ 局游戏中的动作（`R` 表示石头，`P` 表示布，`S` 表示剪刀）。

    **高桥不可以在任何一局中输给青木**（即：高桥和青木只可以平局或高桥赢青木），且高桥第 $i$ 局出的和第 $i-1$ 局出的不能一样，现在，问你高桥可以胜几局？

## 解题思路

很明显是一道 DP 题。

### 定义状态
$f_{i,j}$ 表示第 $i$ 局出 $j$ 时最多可以获胜的局数（$j = 1$ 时表示出石头，$j = 2$ 时表示出布，$j = 3$ 时表示出剪刀）。

### 初始化：

```cpp
if (s[0] == 'R') {
        f[0][1] = 0; // 两人一起出石头，不计分
        f[0][2] = 1; // 高桥出布，高桥加一分
        // 注意：高桥不可以输给青木，所以 f[0][3] 不可以初始化为 -1
    }
    if (s[0] == 'P') {
        f[0][2] = 0; // 同理
        f[0][3] = 1;
    }
    if (s[0] == 'S') {
        f[0][1] = 1;
        f[0][3] = 0;
}
```

### 转移方程：   
当 $s_i =\textrm{R}$ 时： 
$$
f_{i,1} = \max(f_{i-1,2}, f_{i-1,3})\\
f_{i,2} = \max(f_{i-1,1}, f_{i-1,3}) + 1
$$
（注意：$f_{i,1}$ 是被 $f_{i-1,2}$ 和 $f_{i-1,3}$ 转移过来的，因为高桥第 $i$ 局出的和第 $i-1$ 局出的不能一样，  
**高桥不可以输给青木**，所以 $j$ 不可以取 $3$，即：不可以出剪刀）。   
当 $s_i =\textrm{P}$ 时： 
$$
f_{i,2} = \max(f_{i-1,1}, f_{i-1,3})\\
f_{i,3} = \max(f_{i-1,2}, f_{i-1,3}) + 1
$$
当 $s_i =\textrm{S}$ 时： 
$$
f_{i,1} = \max(f_{i-1,2}, f_{i-1,3}) + 1\\
f_{i,3} = \max(f_{i-1,1}, f_{i-1,2})
$$
答案就取 $\max(f_{n - 1,1},f_{n - 1,2},f_{n - 1,3})$，（我的字符串 $s$ 下标从 $0$ 开始存）。
## Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int n, ans, f[N][10];
string s;
main() {
    cin >> n >> s;
    if (s[0] == 'R') {
        f[0][1] = 0;
        f[0][2] = 1;
    }
    if (s[0] == 'P') {
        f[0][2] = 0;
        f[0][3] = 1;
    }
    if (s[0] == 'S') {
        f[0][1] = 1;
        f[0][3] = 0;
    }
    for (int i = 1; i < n; i++) {
        if (s[i] == 'R') {
            f[i][1] = max(f[i - 1][2], f[i - 1][3]);
            f[i][2] = max(f[i - 1][1], f[i - 1][3]) + 1;
        }
        if (s[i] == 'P') {
            f[i][2] = max(f[i - 1][1], f[i - 1][3]);
            f[i][3] = max(f[i - 1][1], f[i - 1][2]) + 1;
        }
        if (s[i] == 'S') {
            f[i][1] = max(f[i - 1][2], f[i - 1][3]) + 1;
            f[i][3] = max(f[i - 1][1], f[i - 1][2]);
        }
    }
    cout << max({f[n - 1][1], f[n - 1][2], f[n - 1][3]});
    return 0;
}
```

---

## 作者：L_xcy (赞：1)

## D - AtCoder Janken 3

### 解题思路

题目中说高桥的第 $i$ 步肯定和他的第 $i+1$ 步不同。换句话说，他的这一步肯定和上一步不同。

这一点满足无后效性，所以可以考虑 DP。

设 $f_{i,j}$ 表示高桥在第 $i$ 步出 $j$（$0$ 表示石头，$1$ 表示布，$2$ 表示剪刀）最多可以赢几局。

假设青木这一局出石头，如果高桥也出石头，那么他既没输也没赢，那么这一种状态就是高桥上一局出剪刀和布取一个最大值，即 $f_{i,0}=\max(f_{i-1,1},f_{i-1,2})$。

如果高桥出布，那么他赢了这一局，那么这一种状态就是高桥上一局出剪刀和石头取一个最大值再 $+1$，即 $f_{i,1}=\max(f_{i-1,0},f_{i-1,2})+1$。

如果高桥出剪刀，那么他输了这一局，注意，因为题目说高桥不会输，所以不用设置这个状态，即 $f_{i,2}=0$（这个点卡了我半个小时）。

如果青木出其他两种情况也是同理。

最后的答案就是 $f_{n,0},f_{n,1},f_{n,2}$ 的最大值。

时间复杂度：$O(n)$。

### Code

码风偏丑，请见谅。

``` cpp
#include <bits/stdc++.h>
using namespace std;
int n, f[200005][3]; // 0r1p2s
char s;
int a[200005];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        if (s == 'R') a[i] = 0;
        if (s == 'P') a[i] = 1;
        if (s == 'S') a[i] = 2;
    }
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == 0) {
            f[i][0] = max(f[i - 1][1], f[i - 1][2]);
            f[i][1] = max(f[i - 1][0], f[i - 1][2]) + 1;
        }
        if (a[i] == 1) {
            f[i][1] = max(f[i - 1][2], f[i - 1][0]);
            f[i][2] = max(f[i - 1][0], f[i - 1][1]) + 1;
        }
        if (a[i] == 2) {
            f[i][2] = max(f[i - 1][1], f[i - 1][0]);
            f[i][0] = max(f[i - 1][1], f[i - 1][2]) + 1;
        }
    }
    cout << max(f[n][0], max(f[n][1], f[n][2]));
    return 0;
}
```

---

## 作者：JXR_Kalcium (赞：1)

## 题目大意

Aoki 会有一个石头剪刀布序列，一共有 $N$ 轮，Takahashi 也要构建一个石头剪刀布序列，要保证自己不输，并且上一轮和这一轮出的不能相同，求他能获胜的最多场数。

## 解题思路

很明显这是一个简单的 **DP**，设 $f_{i,0/1/2}$ 表示 Takahashi 在第 $i$ 轮出剪刀、石头或者布时的最多获胜场数，则如果当前 Aoki 出剪刀，那么便可得到转移方程：

$$
f_{i,0}=\max(f_{i-1,1},f_{i-1,2})
$$

$$
f_{i,1}=\max(f_{i-1,0},f_{i-1,2})+1
$$

剩下的两种情况也是同理，最后的答案即为 $\max(f_{n,0},f_{n,1},f_{n,2})$。要注意，如果你第三个样例输出 $19$，题目中说了 Takahashi 一定不会输，所以对于 Aoki 每次出的招数，三个转移有一个是多余的。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
using namespace std;

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48); return;
}

ll n,f[200001][3];
char s[200001];

int main()
{
    n=read(); scanf("%s",s);

    for(int i=1; i<=n; ++i)
    {
        if(s[i-1]=='S')
        {
            f[i][0]=max(f[i-1][1],f[i-1][2]);
            f[i][1]=max(f[i-1][0],f[i-1][2])+1;
        }

        else if(s[i-1]=='R')
        {
            f[i][1]=max(f[i-1][0],f[i-1][2]);
            f[i][2]=max(f[i-1][0],f[i-1][1])+1;
        }

        else 
        {
            f[i][0]=max(f[i-1][1],f[i-1][2])+1;
            f[i][2]=max(f[i-1][0],f[i-1][1]);
        }
    }

    write(max(f[n][0],max(f[n][1],f[n][2])));
    return 0;
}
```

---

## 作者：xuduang (赞：1)

### 题意

A 和 B 在玩石头剪刀布。但是 A 可以知道 B 之后要出什么。现在有两个约束。

1. A 一直都没有输过（平局不算输）。
2. A 连续两次出的不能相同。

问 A 最多可以赢几局。
### 分析

既然我们知道了 B 的策略，我们可以贪心的做。

当这局能赢的时候就赢，不然赢不了一定能平。

但是这样会出现一个问题，形如 `SSP` 的数据就会少算，因为没有考虑到后面的情况。

那贪心做不了，可以尝试一下 dp？

设 $dp[i][0/1]$ 表示到了第 $i$ 局，平了这局最多能赢多少局，赢了这局最多能赢多少局。

又要用到上面的结论，赢和平绝对有一种能够转移，这个很好证，想一下几种情况就好了。那同时转移方程也显然了。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
    int s = 0, w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        s = (s << 3) + (s << 1) + (ch ^ 48);
        ch = getchar();
    }
    return s * w;
}
const int N = 3e6 + 10;
bool win(char a, char b)
{
    if((a == 'R' && b == 'S') || (a == 'S' && b == 'P') || (a == 'P' && b == 'R')) return 1;
    return 0;
}
int n;
string s;
int dp[N][2];
char ls[N][2];//上一局赢需要出的
signed main()
{
    cin >> n;
    cin >> s;
    s = "!" + s;
    for(int i = 1; i <= n; i++)
    {
        char ws;//赢这局需要出的
        if(s[i] == 'P') ws = 'S';
        if(s[i] == 'R') ws = 'P';
        if(s[i] == 'S') ws = 'R';
        if(ls[i - 1][0] != ws)//这局可以赢
        {
            //从上一局平转移
            dp[i][1] = max(dp[i - 1][0] + 1, dp[i][1]); 
        }
        if(ls[i - 1][1] != ws)
        {
            //从上一局赢转移
            dp[i][1] = max(dp[i - 1][1] + 1, dp[i][1]);
        }
        if(ls[i - 1][0] != s[i])
        {
            //从上一局平转移
            dp[i][0] = max(dp[i][0], dp[i - 1][0]);
        }
        if(ls[i - 1][1] != s[i])
        {
            //从上一局赢转移
            dp[i][0] = max(dp[i][0], dp[i - 1][1]);
        }
        ls[i][0] = s[i];
        ls[i][1] = ws;//记录，后面用
    }
    cout << max(dp[n][0], dp[n][1]) << endl;//对两种情况取最大
    return 0;
}
/*
PS

123456789012345678901234
SPRPSRRRRRPPRPRPSSRSPRSS
RSPSRPRPRPSPRSPSRSPRSPRS
111111010110011110111110
*/
```

---

## 作者：stripe_python (赞：0)

你说的对，但本蒟蒻赛时 DP 写挂改了个丑陋的记搜。

简单的线性 DP。令 $dp_{i,j}$ 表示第 $i$ 个位置，上一把出了手势 $j$ 的最大赢局数目，转移如下：

- 若 $s_i$ 为 `R` 则这一次只能出 `P` 或 `R`，转移为 $dp_{i,j}=\max(dp_{i-1,0} [j \ne 0],(dp_{i-1,1}+1) [j \ne 1])$。
- 若 $s_i$ 为 `P` 则这一次只能出 `P` 或 `S`，转移为 $dp_{i,j}=\max(dp_{i-1,1} [j \ne 1],(dp_{i-1,2}+1) [j \ne 2])$。
- 若 $s_i$ 为 `S` 则这一次只能出 `R` 或 `S`，转移为 $dp_{i,j}=\max(dp_{i-1,2} [j \ne 2],(dp_{i-1,0}+1) [j \ne 0])$。

复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 200005
int n;
char s[N];

int dp[4][N];
// dp[0/1/2][i]：上一把出R/P/S，位置为i的最大赢数

int dfs(int last, int i) {
	if (i > n) return 0;
	if (dp[last][i] >= 0) return dp[last][i];
	if (s[i] == 'R')   // P/R
		return dp[last][i] = max(last != 0 ? dfs(0, i + 1) : 0, 
			last != 1 ? dfs(1, i + 1) + 1 : 0);
	else if (s[i] == 'P') // P/S
		return dp[last][i] = max(last != 1 ? dfs(1, i + 1) : 0, 
			last != 2 ? dfs(2, i + 1) + 1 : 0);
	else
		return dp[last][i] = max(last != 0 ? dfs(0, i + 1) + 1 : 0, 
			last != 2 ? dfs(2, i + 1) : 0);
}

void _main() {
	cin >> n >> (s + 1);
	memset(dp, 0xcf, sizeof(dp));
	cout << dfs(3, 1);
} signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	_main();
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

既然每一局都不能输，那就只有赢和平局两种情况。我们可以开一个递推数组，对于每个位置存储在该位置出拳平局或赢两种情况。每一种情况都可以由上一位置与该情况出拳不同的情况推得。在该位置获胜的情况中，答案为上一位置可行情况的最大值 $+1$，否则该位置答案即为上一位置最大可行答案。

可以建一个函数或映射表存储每种出拳对哪种拳获胜，方便调用。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[2][1000005];
char a[1000005];
char ff(char c){
	if(c=='P') return 'S';
	if(c=='R') return 'P';
	if(c=='S') return 'R';
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		int maxn=0;
		if(a[i]!=a[i-1]) maxn=max(maxn,f[0][i-1]);
		if(a[i]!=ff(a[i-1])) maxn=max(maxn,f[1][i-1]);
		f[0][i]=maxn,maxn=0;
		if(ff(a[i])!=a[i-1]) maxn=max(maxn,f[0][i-1]);
		if(ff(a[i])!=ff(a[i-1])) maxn=max(maxn,f[1][i-1]);
		f[1][i]=maxn+1;
	}
	cout<<max(f[0][n],f[1][n]);
	return 0;
}
```

---

## 作者：da_ke (赞：0)

# AT_abc365_d [ABC365D]

## 前言

[更好的阅读体验](https://mahaoming2022.github.io/2024/08/09/%E9%A2%98%E8%A7%A3%EF%BC%9AAT-abc365-d-ABC365D-AtCoder-Janken-3/)?

又是一道 dp 题……

## 翻译

先规定石头剪刀布的规则为：`R` 打败 `S`，`S` 打败 `P`，`P` 打败 `R`，出相同的字符视为平局。下简记三种出发为「手法」。

给出对方的 $n$ 次出法的序列（一个长度为 $n$ 字符串），要求你出一个对策，满足：

- 你不会输任何一局（若平局不算为输给对方）。
- 你出的相邻两个手法不能重复。

**数据保证存在一种策略满足以上要求**。

## 思路

### 引入

为什么不是贪心？

一种可能的思路是碰到对手一样的出发就隔一个赢一次，但是很幸运的没有过第 3 个样例。

各种分类后发现根本没有通用的方法，故采用 dp。

众所周知 dp 很多都是将暴力指数级算法优化成很多维的算法。但这道题只允许线性或 $O(n\log n)$ 的算法通过，故确定复杂度且确定为**线性 dp**。

### 动态规划

若出了手法 $s$ 出了下一个就不能 $s$，只能出不同于 $s$ 的另外两个，不妨设另外两个为 $s_1,s_2$。

故转移为：$dp(i,s)=dp(i+1,s_1)+dp(i+1,s_2)$

其中 $i$ 表示决策到了第 $i$ 次，其他的如上文所述。

放代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)

using namespace std;

typedef long long ll;
typedef double db;

const int N=2e5+23;

int n;
string s;
int mem[N][5],c[N];

/*
Paper 1
Sissor 2
Rock 3
*/

inline int dp(int d,int lst)
{
    int& ans=mem[d][lst];
    if(ans!=-1) return ans;
    if(d==n+1) return 0;
    int ans1=0,ans2=0;
    if(c[d]==1)
    {
        if(lst!=2) ans1=1+dp(d+1,2);
        if(lst!=1) ans2=dp(d+1,1);
    }
    if(c[d]==2)
    {
        if(lst!=3) ans1=1+dp(d+1,3);
        if(lst!=2) ans2=dp(d+1,2);
    }
    if(c[d]==3)
    {
        if(lst!=1) ans1=1+dp(d+1,1);
        if(lst!=3) ans2=dp(d+1,3);
    }
    return ans=max(ans1,ans2);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    cin>>n>>s;
    s=' '+s;
    rep(i,1,n)
    {
        if(s[i]=='P') c[i]=1;
        if(s[i]=='S') c[i]=2;
        if(s[i]=='R') c[i]=3;
    }
    memset(mem,-1,sizeof(mem));
    cout<<dp(1,0);
}
```

实现采用了思路比较清晰的记忆化搜索。

然后就愉快的 AC 了：<https://www.luogu.com.cn/record/171653457>

## 总结

类似于博弈、游戏等题目不能局限于贪心或一种方法，可以大胆开拓新的思路。

## 广告

安利一下我的代码仓库。AtCoder 的部分题目代码即调试信息、避坑可以在[这里](https://kkgithub.com/mahaoming2022/lib/tree/m)找到。

---

## 作者：zjj2024 (赞：0)

### 思路

动态规划题。

定义 $f_{i,0}$ 表示第 $i$ 局平的获胜盘数最大值，$f_{i,1}$ 表示第 $i$ 局赢的获胜盘数最大值。

考虑 $f_{i,0}$。

1. 如果 $s_{i-1}=s_i$ 则 $f_{i,0}=f_{i-1,1}$。
2. 如果克 $s_{i-1}$ 字符等于 $s_i$ 则 $f_{i,0}=f_{i-1,0}$。
3. 否则 $f_{i,0}$ 等于 $f_{i-1,0}$ 和 $f_{i-1,1}$ 中的最大值。

$f_{i,1}$ 的求解方法类似。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
ll f[N][2];
string s;
char to(char ch)//用to(x)表示能克x的手势
{
	if(ch=='P')return 'S';
	if(ch=='R')return 'P';
	if(ch=='S')return 'R';
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n>>s;
	s=' '+s;
	f[1][0]=0;
	f[1][1]=1;
	for(int i=2;i<=n;i++)
	{
		if(s[i-1]==s[i])f[i][0]=f[i-1][1];
		else if(to(s[i-1])==s[i])f[i][0]=f[i-1][0];
		else f[i][0]=max(f[i-1][0],f[i-1][1]);
		if(s[i-1]==s[i])f[i][1]=f[i-1][0]+1;//要加1
		else if(to(s[i])==s[i-1])f[i][1]=f[i-1][1]+1;
		else f[i][1]=max(f[i-1][0],f[i-1][1])+1;
	}
	cout<<max(f[n][0],f[n][1])<<'\n';
	return 0;
}
```

---

## 作者：_Hzx_ (赞：0)

感觉很 dp。

---

【**解法**】

设 $dp_{i,0}$ 为第 $i$ 轮出石头的最大获胜次数，$dp_{i,1}$ 为第 $i$ 轮出布的最大获胜次数，$dp_{i,2}$ 为第 $i$ 轮出剪刀的最大获胜次数。那么最终的答案就是 $\max(dp_{n,0},dp_{n,1},dp_{n,2})$。

状态与状态想好了，只剩下转移。

$$s_i = \begin{cases} \text{R} & dp_{i,0} = \max(dp_{i - 1,1}, dp_{i - 1,2}), dp_{i,2} = \max(dp_{i - 1,1}, dp_{i - 1,0}) + 1\\ \text{P} & dp_{i,1} = \max(dp_{i - 1,0}, dp_{i - 1,2}) + 1,dp_{i,2} = \max(dp_{i - 1,1}, dp_{i - 1,0}) \\ \text{S} & dp_{i,0} = \max(dp_{i - 1,1}, dp_{i - 1,2}) + 1,dp_{i,1} = \max(dp_{i - 1,2}, dp_{i - 1,0}) \end{cases}$$

根据上文转移即可。

----

【**代码**】

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

string s;
int n, dp[N][3];

int main() {
	cin >> n >> s;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'R') {
			dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]);
			dp[i][2] = max(dp[i - 1][1], dp[i - 1][0]) + 1;
		}
		if (s[i] == 'P') {
			dp[i][1] = max(dp[i - 1][0], dp[i - 1][2]) + 1;
			dp[i][2] = max(dp[i - 1][1], dp[i - 1][0]);
		}
		if (s[i] == 'S') {
			dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]) + 1;
			dp[i][1] = max(dp[i - 1][2], dp[i - 1][0]);
		}
	}
	printf("%d\n", max(dp[n][0], max(dp[n][1], dp[n][2])));
}

```

---

## 作者：Kotobuki_Tsumugi (赞：0)

我们沿用了 [AT_dp_c](https://www.luogu.com.cn/problem/AT_dp_c) 的思路。令 $dp_{i,0}$ 表示第 $i$ 次，我方出石头的最大胜场；同理，$dp_{i,1}$，$dp_{i,2}$ 分别表示出剪刀和布的最大胜场。 

由于我方没有输过一次，所以我们只能胜利或平局。根据实际，若对方出石头，我们不能出剪刀，所以我们要把石头、布的答案更新。即我们要更新 $dp_{i,0}$ 和 $dp_{i,2}$。

又由于每一次的抉择不能和上一次相同，我们在更新时，要注意从不同的方式转移过来。

例如现在要更新 $dp_{i,0}$，我们只能从 $dp_{i-1,1}$ 或 $dp_{i-1,2}$ 这两个状态中转移过来。

$$dp_{i,0}=\max(dp_{i-1,1},dp_{i-1,2})$$

例如现在要更新 $dp_{i,2}$，我们只能从 $dp_{i-1,0}$ 或 $dp_{i-1,1}$ 这两个状态中转移过来。

$$dp_{i,2}=\max(dp_{i-1,0},dp_{i-1,1})+1$$

其中，布胜了对方的石头，所以更新时要加一。

上述讨论了对方出石头的情况，若对方出剪刀或布也同理。读者可以自己推理。

下面给出代码。

```cpp
#include<iostream>//R1,P2,S3
using namespace std;
const int N = 2e5+10;
int n,dp[N][4];
char a[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i = 1;i<=n;i++) cin>>a[i];
	for(int i = 1;i<=n;i++){
		if(a[i] == 'R'){
			dp[i][1] = max(dp[i-1][2],dp[i-1][3]);
			dp[i][2] = max(dp[i-1][1],dp[i-1][3])+1;
		}
		if(a[i] == 'P'){
			dp[i][2] = max(dp[i-1][1],dp[i-1][3]);
			dp[i][3] = max(dp[i-1][1],dp[i-1][2])+1;
		}
		if(a[i] == 'S'){
			dp[i][3] = max(dp[i-1][1],dp[i-1][2]);
			dp[i][1] = max(dp[i-1][2],dp[i-1][3])+1;
		}
	}
	cout<<max(max(dp[n][1],dp[n][2]),dp[n][3]);
	return 0;
}
```

---

## 作者：Merge_all (赞：0)

## 思路：
### 分析题目：
- 由于是求解最大胜局数且每一个状态都会影响到后面的结果，因此可以用 dp 来做。
### 定义状态：
1. 我们发现每次**要么是赢**，**要么是平**，说明有那种不同的状态我们需要考虑。
2. 定义 $f_{i_0}$ 来表示比赛进行到第 $i$ 轮，高桥和青木**打平时**，**此时高桥胜局数的最大值**。
3. 定义 $f_{i_1}$ 来表示比赛进行到第 $i$ 轮，高桥**赢了**青木，**此时高桥胜局数的最大值**。

### 状态转移：
我们先用 $mp$ 数组记录一下每种出法会被那种出法打赢。

即下面这样：

```
mp['R']='P',mp['S']='R',mp['P']='S';
```
我们用 $s_i$ 表示青木在第 $i$ 轮中出的动作。

1. 显然在第 1 局中：$f_{i_0}=0,f_{i_1}=1$。
2. 在第 $i$ 局中，分别有以下 2 中情况：
- $s_i=s_{i-1}$，如果上一局高桥赢了，那么这一局高桥就必须平局，反之就可以赢下这一局。
- $s_i\neq s_{i-1}$，那有会有以下 4 中情况：

  第一：$mp_{s_i}\neq s_{i-1}$，这时说明高桥可以赢且上局是平局，则 $f_{i_1}=\max(f_{i_1},f_{i-1_0}+1)$。
  
  第二：$mp_{s_i}\neq mp_{s_{i-1}}$，这时说明高桥依旧能赢，且还能多赢一次，则 $f_{i_1}=\max(f_{i-1},f_{i-1_1}+1$。

  第三：$s_i\neq s_{i-1}$，这时说明高桥不能再赢了，而且还要再平局一次，则 $f_{i_0}=\max(f_{i_0},f_{i-1_0})$。

  第四：$s_i\neq mp_{s_{i-1}}$，这时说明高桥不能再赢，但上一局一定是赢了的，则 $f_{i_0}=\max(f_{i_0},f_{i-1_1})$。

## 代码：
```
#include<bits/stdc++.h>
#define rep(i,a,b) for(register int i=(a);i<=(b);i=-~i)
using namespace std;
int n;
string s;
map<char,char> mp;
int f[200010][2];
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>s;
	mp['R']='P',mp['S']='R',mp['P']='S';
	memset(f,-0x3f,sizeof f);
	f[0][0]=0,f[0][1]=1;//这里从 0 开始
	rep(i,1,n-1){
		if(s[i]!=s[i-1]){
			if(mp[s[i]]!=s[i-1]) f[i][1]=max(f[i][1],f[i-1][0]+1);
			if(mp[s[i]]!=mp[s[i-1]]) f[i][1]=max(f[i][1],f[i-1][1]+1);
			if(s[i]!=s[i-1]) f[i][0]=max(f[i][0],f[i-1][0]);
			//if(s[i]!=mp[s[i-1]]) f[i][1]=max(f[i][0],f[i-1][1]+1);
			if(s[i]!=mp[s[i-1]]) f[i][0]=max(f[i][0],f[i-1][1]);
		}
		else f[i][1]=f[i-1][0]+1,f[i][0]=f[i-1][1];
	}
	/*
	  for(int i=1;i<=n;i++) ans=max(ans,max(f[i][0],f[i][1]);
	 */
	cout<<max(f[n-1][0],f[n-1][1]);
	return 0;
}
/*
  
  
 */
```

---

## 作者：Breath_of_the_Wild (赞：0)

这是一道 dp 题。

设 $dp_{i,j}$ 为玩到第 $i$ 局出 $j$ 这个东西（石头、剪刀、布）能赢的次数。$j$ 代表什么自己设。

比如现在到了第 $i$ 局，我们拿对手出的是剪刀为例。

这一局出石头显然能赢，那么这一局出石头所能赢的次数就可以由上一局出与这一局不同的，即布和石头的最大值再加 $1$ 得来。因为不能连续两局出同样的，所以不能再和上一局出剪刀的取最大值。

还没完。这一局我们也可以出与对手同样的，即剪刀。那么就赢不了了，所以由上一局出与当前的不同的（石头、布）中取最大值。赢不了没法加 $1$。

拿公式总结一下。设对手出的是 $x$，能赢 $x$ 的东西是 $y$，剩下一个是 $z$，就可以得到两个转移式：
- $dp_{i,x}=\max\{dp_{i-1,y},dp_{i-1,z}\}$。
- $dp_{i,y}=\max\{dp_{i-1,x},dp_{i-1,y}\}+1$。

代码只给对于石头的出法了。
```
  if(s[i]=='R'){
    f[i][1]=max(f[i-1][2],f[i-1][3]);
    f[i][3]=max(f[i-1][2],f[i-1][1])+1;
}
```

---

## 作者：__O_v_O__ (赞：0)

此题正解为动态规划。

定义 $f_{i,0/1/2}$ 表示前 $i$ 次游戏，第 $i$ 次出石头、布、剪刀赢的最大局数。

考虑转移。因为 $s_i$ 是 `R` 或 `P` 或 `S` 是一样的，所以这里只考虑 $s_i$ 是 `R` 时的转移。

首先，高桥不能输，所以当前局只能出石头或布。

如果高桥出石头：$f_{i,0}=\max(f_{i-1,1},f_{i-1,2})$。

如果高桥出布：$f_{i,1}=\max(f_{i-1,0},f_{i-1,2})+1$。

至此，这题成功解决。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,f[200001][3];string s;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>s,s=' '+s;
	for(int i=1;i<=n;i++){
		if(s[i]=='R'){
			f[i][0]=max(f[i-1][1],f[i-1][2]);
			f[i][1]=max(f[i-1][0],f[i-1][2])+1;
		}else if(s[i]=='P'){
			f[i][1]=max(f[i-1][0],f[i-1][2]);
			f[i][2]=max(f[i-1][0],f[i-1][1])+1;
		}else{
			f[i][2]=max(f[i-1][1],f[i-1][0]);
			f[i][0]=max(f[i-1][1],f[i-1][2])+1;
		}
	}
	cout<<max(f[n][0],max(f[n][1],f[n][2]));
	return 0;
}
```

---

## 作者：Alex_smy (赞：0)

## 题意简述
A 和 B 正在玩石头剪刀布的游戏，其中 `R` 代表石头，`P` 代表布，`S` 代表剪刀。比赛一共有 $N$ 局，给出 A 每一局出了什么，又已知以下条件：
- B 从未输给过 A。
- B 每相邻两局出的都不一样。

求 B 最多能赢多少局。
## 解题思路
一道动态规划题。

为什么是动态规划呢？因为每一局的操作都有后效性，即这一局出的下一局不能再出。

我们首先来定义状态。设 $dp[1][i]$ 表示 B 第 $i$ 局时如果出石头，前 $i$ 局最多能赢多少局，$dp[2][i]$ 表示 B 第 $i$ 局时如果出布，前 $i$ 局最多能赢多少局，$dp[3][i]$ 表示 B 第 $i$ 局时如果出剪刀，前 $i$ 局最多能赢多少局。

接下来考虑如何进行状态转移。因为每相邻两局不能出同样的手势，所以每一种手势都是从上局的另外两种手势中的较大值转移。如果是赢的手势需要加 $1$，平的手势直接转移。

但是要注意，还有一个条件是 B 从未输给过 A，因此输的手势不能出，这里不用转移，直接设成 $0$ 或者负数即可。

具体实现请见代码。
## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,dp[5][200005];
string s;
int main(){
	scanf("%d",&n);
	cin>>s;
	if(s[0]=='R') dp[2][1]=1;
	else if(s[0]=='P') dp[3][1]=1;
	else dp[1][1]=1;
	for(int i=2;i<=n;i++){
		if(s[i-1]=='R'){
			dp[1][i]=max(dp[2][i-1],dp[3][i-1]);
			dp[2][i]=max(dp[1][i-1],dp[3][i-1])+1;
		}
		else if(s[i-1]=='P'){
			dp[2][i]=max(dp[1][i-1],dp[3][i-1]);
			dp[3][i]=max(dp[1][i-1],dp[2][i-1])+1;
		}
		else{
			dp[3][i]=max(dp[1][i-1],dp[2][i-1]);
			dp[1][i]=max(dp[2][i-1],dp[3][i-1])+1;
		}
	}
	printf("%d",max({dp[1][n],dp[2][n],dp[3][n]}));
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# AT_abc365_d 题解

## 思路

题目给出了 Aoki 的序列，要求 Takahashi 从不输给 Aoki，也就是要么平局要么赢，又要求 Takahashi 不能连续两局出一样的，可以考虑 DP，设 $f_{i,j}$ 为第 $i$ 轮出 $j$ 时，Takahashi 最多能赢多少局，用 $0,1,2$ 来表示剪刀石头布，不难写出状态转移方程 $f_{i,j}=\max (f_{i-1,k}+t)$，其中 $j,k \in [0,2]$ 且 $j \neq k$，如果出 $k$ 的时候赢了，则 $t=1$ 否则 $t=0$。

$O(n)$ 跑一遍 DP 即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=200005;

int n;
char s[N];
int arr[N];
int f[N][3];

bool loseto(int a,int b) {
    if (b==-1) return false;
    if (a==0 && b==1) return true;
    if (a==1 && b==2) return true;
    if (a==2 && b==0) return true;
    return false;
}

int max3(int a,int b,int c) {
    return max(max(a,b),c);
}

int main() {
    scanf("%d",&n);
    scanf("%s",s+1);
    for (int i=1;i<=n;++i) {
        if (s[i]=='R') arr[i]=0;
        else if (s[i]=='P') arr[i]=1;
        else arr[i]=2;
    }
    arr[0]=-1;
    for (int i=1;i<=n;++i) {
        for (int j=0;j<=2;++j) {
            if (loseto(j,arr[i])) continue;
            for (int k=0;k<=2;++k) {
                if (loseto(k,arr[i-1]) || j==k) continue;
                if (j==arr[i]) {
                    f[i][j]=max(f[i][j],f[i-1][k]);
                } else {
                    f[i][j]=max(f[i][j],f[i-1][k]+1);
                }
            }
        }
    }
    printf("%d",max3(f[n][0],f[n][1],f[n][2]));
    return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
设 $dp_{i,j}$ 表示第 $i$ 轮出 $j$ 时前 $i$ 轮中最多赢的次数。然后只要分讨判断输赢，若输了则设 $dp_{i,j}=-\infin$，因为题目说了不能输。若平局则 $dp_{i,j}=\max\limits_{k=0}^2dp_{i-1,k}$，若赢了则再加 $1$。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const int inf = -1e9;
int n, dp[200005][3];
string a;
int check (const char x, const int y) {
	if (x == 'R')
		if (y == 0)
			return 0;
		else if (y == 1)
			return 1;
		else
			return -1;
	else if (x == 'P')
		if (y == 0)
			return -1;
		else if (y == 1)
			return 0;
		else
			return 1;
	else if (y == 0)
		return 1;
	else if (y == 1)
		return -1;
	else
		return 0;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> a;
	a = '*' + a;
	for (int i = 1; i <= n; ++ i)
		for (int j = 0; j < 3; ++ j) {
			const int op = check (a[i], j);
			if (op < 0) {
				dp[i][j] = inf;
				continue ;
			}
			for (int k = 0; k < 3; ++ k)
				if (j != k)
					dp[i][j] = max (dp[i][j], dp[i - 1][k] + op);
		}
	cout << max ({dp[n][0], dp[n][1], dp[n][2]});
	I AK IOI
}
````

---

## 作者：Liuhy2996 (赞：0)

## 思路
石头用 $0$ 表示，布用 $1$ 表示，剪刀用 $2$ 表示。

$dp_{i,j}$ 表示前 $i$ 次石头剪刀布，第 $i$ 次出 $j$ 最多赢多少次。初始值 $dp_{0,0},dp_{0,1},dp_{0,2}$ 为 $0$ 其他设为负无穷（$-10^9$），转移时枚举当前手势和前一次手势，若不相等且当前手势不输则更新。
## 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+10;
int n,a[N],dp[N][3],c[N];
char x;
int chk(int x,int y){
	if((x+1)%3==y) return -1;
	if(x^y) return 1;
	return 0;
}
signed main(){
	c['R']=0,c['P']=1,c['S']=2;
	cin>>n;
	for(int i=1;i<=n;++i) cin>>x,a[i]=c[x];
	for(int i=1;i<=n;++i)
		for(int j=0;j<3;++j) dp[i][j]=-1e9;
	for(int i=1;i<=n;++i)
		for(int j=0;j<3;++j)     //枚举前一次手势
			for(int k=0;k<3;++k) //枚举当前手势
				if(chk(k,a[i])>=0&&j!=k) dp[i][k]=max(dp[i][k],dp[i-1][j]+chk(k,a[i])); //符合条件更新答案
	cout<<max(dp[n][0],max(dp[n][1],dp[n][2]));
	return 0;
}
```

---

## 作者：luckyqwq (赞：0)

# AT_abc365_d [ABC365D] AtCoder Janken 3 题解

### 大致思路：

这是一道简单的 dp 题目，首先我们设计状态 $dp_{i, 0/1/2}$ 表示在第 $i$ 局石头剪刀布中分别出石头，布，剪刀的情况下，赢的局数的最大值，那么转移方程也十分简单：

- 首先是对方出石头的情况，显然转移方程为 $dp_{i, 0} = \max(dp_{i - 1, 1}, dp_{i - 1, 2})$，因为如果本局出石头，那么也就是平局，而相邻两局不能出同一种，所以状态不能从 $dp_{i - 1, 0}$ 中转移过来，显然 $dp_{i, 1}$ 转移方程为 $dp_{i, 1} = \max(dp_{i - 1, 0}, dp_{i - 1, 2}) + 1$，因为在这种情况下本局是赢得，所以说需要从前面两种状态中取最大值加上 $1$，而在这种情况下 $dp_{i, 2}$ 是不用转移的，因为题目要求不能输，而 $dp_{i, 2}$ 是本局剪刀的情况，会输，所以不用转移。


- 再是对手出布的情况，显然转移方程也分别为 $dp_{i, 1} = \max(dp_{i - 1, 0}, dp_{i - 1, 2})$ 和 $dp_{i, 2} = \max(dp_{i - 1, 0}, dp_{i - 1, 1}) + 1$，这里就不过多解释了。

- 最后是对手出剪刀的情况，以此类推，转移方程为 $dp_{i, 2} = \max(dp_{i - 1, 0}, dp_{i - 1, 1})$ 和 $dp_{i, 0} = \max(dp_{i - 1, 1}, dp_{i - 1, 2}) + 1$。

根据这样转移就能够得出最后的答案。

### 代码实现：

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
long long dp[200005][5];
signed main()
{
    cin >> n;
    string s;
    cin >> s;
    s = " " + s;
    for (int i = 1;i <= n; ++ i)
    {
    	if(s[i] == 'R')
    	{
    		dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]);
			dp[i][1] = max(dp[i - 1][0], dp[i - 1][2]) + 1;
			//dp[i][2] = max(dp[i - 1][0], dp[i - 1][1]);
		}
		else if(s[i] == 'P')
		{
			dp[i][1] = max(dp[i - 1][0], dp[i - 1][2]);
			//dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]);
			dp[i][2] = max(dp[i - 1][0], dp[i - 1][1]) + 1;
		}
		else if(s[i] == 'S')
		{
			dp[i][2] = max(dp[i - 1][0], dp[i - 1][1]);
			dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]) + 1;
			//dp[i][1] = max(dp[i - 1][2], dp[i - 1][0]);
		}
	}
	cout << max({dp[n][0], dp[n][1], dp[n][2]}) << "\n";
    return 0;
}
```

这样这道题目就完成啦！！！

---

## 作者：Lotus_Land (赞：0)

### 题意

高桥和青木玩了 $N$ 次剪刀石头布。注：在这个游戏中，石头赢剪刀，剪刀赢纸，纸赢石头。

青木的动作由长度为 $N$ 的字符串 $S$ 表示，字符串由 “R”、“P” 和 “S” 组成。 $S$ 中的第 $i$ 个字符表示青木在第 $i$ 对局中的棋步：“R” 表示 “石头“，“P” 表示 "纸"，“S” 表示 "剪刀"。

高桥的棋步满足以下条件：

- 高桥从未输给过青木。

- 对于 $i=1,2,\ldots,N-1$，高桥在第 $i$ 对局中的棋步与他在第 $(i+1)$ 对局中的棋步不同。

请确定高桥的最大胜局数。

可以保证存在一个满足这些条件的高桥下棋顺序。

### 分析

简单的线性 DP。

要满足第一个条件，对于青木的每一步，高桥都有可行两种动作：一种是平局，一种是获胜。满足第二个条件，则要求状态转移是从上一步的不同动作转移来的。

设 $f_{i,0/1/2}$ 表示高桥第 $i$ 部出石头/纸/剪刀，能获得的最大胜局数。状态转移方程见代码。


```cpp
int n,f[200005][3];
string s;
int main(){
	cin>>n>>s;
	s=" "+s;
	//R P S
	//0 1 2
	for(int i=1;i<=n;i++){
		if(s[i]=='R'){
			f[i][0]=max(f[i-1][1],f[i-1][2]);
			f[i][1]=max(f[i-1][0],f[i-1][2])+1;
		}else if(s[i]=='P'){
			f[i][1]=max(f[i-1][0],f[i-1][2]);
			f[i][2]=max(f[i-1][1],f[i-1][0])+1;
		}else{
			f[i][2]=max(f[i-1][1],f[i-1][0]);
			f[i][0]=max(f[i-1][1],f[i-1][2])+1;
		}
	}
	cout<<max(f[n][0],max(f[n][1],f[n][2]));
	return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

这道题一开始我把题意读错了，甚至以为是红题。

所以再把题意说一遍：

高桥和某个人玩剪刀石头布，他不能输给这个人，并且相邻两次不能出同样的手势，问他最多能赢多少局。

注意，“不输”和“赢”是两种概念，不输还可以出的和对手一样。

所以想到 dp。

设 $f_{i, 0/1/2}$ 表示现在到了第 $i$ 轮，出剪刀、石头、布的赢的最多局数。

那么公式就很好推了。

如果对手这轮出的是剪刀，那么 $f_{i, 2}$ 就是 $0$，因为不能出布。

$f_{i, 0} = \max(f_{i - 1, 1}, f_{i - 1, 2})$。因为这局没有赢，所以赢的局数不加 $1$。

$f_{i, 1} = \max(f_{i - 1, 0}, f_{i - 1, 2}) + 1$。如果这局出石头，就赢了。

同理。若对手这局出的是石头：

$$f_{i, 1} = \max(f_{i - 1, 0}, f_{i - 1, 2})$$
$$f_{i, 2} = \max(f_{i - 1, 0}, f_{i - 1, 1}) + 1$$

若对手这局出的是布：

$$f_{i, 2} = \max(f_{i - 1, 0}, f_{i - 1, 1})$$
$$f_{i, 0} = \max(f_{i - 1, 1}, f_{i - 1, 2}) + 1$$

那么代码就很好写了。

---

## 作者：yanlikun (赞：0)

# 题意
甲和乙玩石头剪刀布，他们一共玩了 $n$ 局，已知甲每局出的手势，求乙最多能赢多少局？
# 题目要求
1. 乙在每局游戏中都不会输（只会赢或平手）。
2. 乙在相邻两局中所出的手势都不同。
# 思路
一开始想成了贪心，后来发现贪心是错解。显然的，这道题应该用动规。我们设 $dp_{i,j}$ 表示在第 $i$ 局里出第 $j$ 种手势能赢的最大局数。那么状态转移方程也呼之欲出了（详见代码）。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dp[200005][3];//0表示出石头，1表示出布，2表示出剪刀。
string s;
int main()
{
	cin>>n>>s;
	for(int i=1;i<=n;i++)
	{
		if(s[i-1]=='R')
		{
			dp[i][1]=max(dp[i-1][0],dp[i-1][2])+1;//若该局选择赢，则在上一局中取赢的最大局数再加 1。
			dp[i][0]=max(dp[i-1][1],dp[i-1][2]);//若该局选择平手，从上一局中取赢的最大局数。
		}
		if(s[i-1]=='P')
		{
			dp[i][2]=max(dp[i-1][0],dp[i-1][1])+1;
			dp[i][1]=max(dp[i-1][0],dp[i-1][2]);
		}
		if(s[i-1]=='S')
		{
			dp[i][0]=max(dp[i-1][1],dp[i-1][2])+1;
			dp[i][2]=max(dp[i-1][1],dp[i-1][0]);
		}
		//cout<<dp[i][0]<<" "<<dp[i][1]<<" "<<dp[i][2]<<"\n";
	}
	cout<<max(dp[n][0],max(dp[n][1],dp[n][2]));
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

### 题意
高桥和青木正在玩石头剪刀布。   
高桥已经知道了青木接下来 $n$ 轮的手势，用一个长度为 $n$ 的字符串表示。在这个字符串中，`R` 表示石头，`S` 表示剪刀，`P` 表示布。     
高桥想找到一个最佳手势策略，使得他赢的次数尽可能多。但是他需要遵守两条规则：

- 他不能在任何一轮中输给青木。
- 对于第 $i(1 \le i < n)$ 次石头剪刀布，高桥的手势不能和第 $i+1$ 轮中的相同。

求高桥最多能赢多少次。    
数据范围：$n \le 2 \times 10^5$。

### 分析
线性 DP。        
设 $f_{i,0/1/2}$ 表示当前进行到第 $i$ 轮，高桥出了石头、剪刀或者布的最多胜利次数。   
非常显然可以得到：
$$f_{i,j}=(\displaystyle\max^{2}_{i=0} f_{i,k}[k \ne j])[j \operatorname{not\,lose} s_i]+[j \operatorname{win} s_i]$$    
其中，$i \operatorname{not\,lose} j$ 表示 $i$ 代表的手势不会输给 $j$ 代表的手势（赢或平局），$i \operatorname{win} j$ 表示 $i$ 代表的手势能赢 $j$ 代表的手势。（$i,j$ 都是数字。）    
转移是 $O(1)$ 的，枚举 $i$ 是 $O(n)$ 的，所以总的复杂度为 $O(n)$。
### 代码
在这里，$1$ 代表布，$2$ 代表剪刀，$3$ 代表石头。
```cpp
#include<stdio.h>
int n,s[200005],f[200005][5],ans;char sr[200005];
int main()
{
    scanf("%d%s",&n,sr+1);for(int i=1;i<=n;i++) s[i]=sr[i]=='P'?1:sr[i]=='S'?2:3;
    for(int i=1;i<=n;i++) for(int j=1;j<=3;j++)
    {
        if(s[i]==1&&j==3||s[i]==2&&j==1||s[i]==3&&j==2) continue; 
        for(int k=1;k<=3;k++) if(j!=k) f[i][j]=f[i][j]>f[i-1][k]+(s[i]==j?0:1)
        ?f[i][j]:f[i-1][k]+(s[i]==j?0:1);
    }
    for(int i=1;i<=3;i++) if(f[n][i]>ans) ans=f[n][i];
    printf("%d",ans);
}
```

---

## 作者：I_Love_DS (赞：0)

## 前言

庆祝一下，这是本蒟蒻第一道 dp 题解。

## 思路

原本想贪心的，结果假了。

直接说正解：

设 $dp_{i, 0/1}$ 表示进行到了第 $i$ 局，选择平局或是胜局的最大胜利场数（因为题面说了不能输）。

转移（实现代码时要判断是否与上回的决策一样，如果一样，就不能从这里转移）：

$$dp_{i, j} = \max(dp_{i - 1, 0}, dp_{i - 1, 1}) + j$$

初始化：

$$dp_{1, 1} = 1, dp_{1, 0} = 0$$

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 50;
int n, dp[N][2]; // 0 和局，1 胜局
char a[N];
map <char, char> m1; // 存能赢这个手势的手势是什么
int main() {
	scanf("%d%s", &n, a + 1);
	m1['R'] = 'P';
	m1['P'] = 'S';
	m1['S'] = 'R';
	dp[1][1] = 1, dp[1][0] = 0;
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= 1; j++) {
			int _0 = (a[i - 1] != (j == 0 ? a[i] : m1[a[i]]) ? dp[i - 1][0] : 0); //
			int _1 = (m1[a[i - 1]] != (j == 0 ? a[i] : m1[a[i]]) ? dp[i - 1][1] : 0); // 保证了不与上回的决策重复
			dp[i][j] = max(_0, _1) + j;
		}
	}
	printf("%d", max(dp[n][0], dp[n][1])); // 最后答案取 max
	return 0;
}
```

## 彩蛋

一组专对贪心的 Hack：

in:

```
6
RSSPPP
```

out:

```
4
```

原理很简单，如果贪心，第 $2$ 局选择赢，那么第三局只能出剪刀，后面的局就只能出“布，剪刀，布”。

而 dp 就可以在第 $2$ 局选择平，第 $3$ 局选择赢，后面的局就可以出“剪刀，布，剪刀”。

可以看出 dp 更优。

---

## 作者：LuukLuuk (赞：0)

# 题解：AT_abc365_d [ABC365D] AtCoder Janken 3
---
### 题目大意
给定长度为 $N$ 的字符串表示对手接下来 $N$ 次游戏的策略，包含 `R`,`S`,`P` 三种字符，表示石头，剪刀和布。你按照以下规则制定策略：一、不能输；二、相邻两次出的不能一样。问最多赢多少局。

数据范围：$1 \le N \le 2 \times 10 ^ 5 $

---

### 思路
由于每一局的最优解只和之前的策略有关，可以考虑 dp。状态 $dp_{i,j}$ 表示当前第 $i$ 局，策略是什么，$j=1$ 对应石头，$j=2$ 对应布，$j=3$ 对应剪刀。转移时枚举三种策略，每种策略从上一局的另外两种策略转移，并加上当前局赢的贡献。注意输的时候该状态变为 $0$，因为高桥不能输（什么意思）。

---
### 代码
```cpp

#include <algorithm>
#include <cstdio>
using namespace std;

int dp[200010][4];
char s[200010];
int a[200010];
int n;

int main() {
	scanf("%d%s", &n, s + 1);
	for (int i = 1; i <= n; ++i) {
		if (s[i] == 'R')	a[i] = 1;//石头为1 
		if (s[i] == 'P')	a[i] = 2;//布为2 
		if (s[i] == 'S')	a[i] = 3;//剪刀为3 
	}
	for (int i = 1; i <= n; ++i) {
		dp[i][1] = max(dp[i - 1][2], dp[i - 1][3]) + (a[i] == 3);//出石头从布和剪刀转移，若当前对方出剪刀再加1 
		dp[i][2] = max(dp[i - 1][1], dp[i - 1][3]) + (a[i] == 1);//和石头一样的 
		dp[i][3] = max(dp[i - 1][1], dp[i - 1][2]) + (a[i] == 2);//一样的 
		if (a[i] == 1)	dp[i][3] = 0;//如果对方出石头，出不了剪刀 
		if (a[i] == 2)	dp[i][1] = 0;//一样的 
		if (a[i] == 3)	dp[i][2] = 0;//同上 
	}
	printf("%d", max(dp[n][1], max(dp[n][2], dp[n][3])));//从三种情况找最优 
	return 0;
}

```

---

## 作者：luogu_gza (赞：0)

不难有 dp。

设 $f_{i,0/1/2}$ 表示当前在第 $i$ 个位置，当前回合出手是石头或剪刀或布的最大胜利局数。

转移不难枚举当前局的决策和上一局的决策。

注意到要么平手要么赢，输是不可能的，所以有些转移是不行的。

[code](https://atcoder.jp/contests/abc365/submissions/56263727)。

---

