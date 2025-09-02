# [ABC271D] Flip and Adjust

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc271/tasks/abc271_d

両面に整数が書かれたカードが $ N $ 枚あり、$ i\ \,\ (1\ \leq\ i\ \leq\ N) $ 枚目のカードの表には $ a_i $ が、裏には $ b_i $ が書かれています。

あなたは、それぞれのカードについて、表を上に向けて置くか裏を上に向けて置くかを自由に決めることができます。

上に向けられた面に書かれた整数の総和がちょうど $ S $ となるようにカードを置くことができるか判定し、可能ならそのようなカードの置き方の一例を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ S\ \leq\ 10000 $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ 100\ \,\ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数

### Sample Explanation 1

例えば次のように置くことで、上に向けられた面に書かれた整数の総和がちょうど $ S\ (=\ 11) $ となります。 - $ 1 $ 枚目は表、$ 2 $ 枚目は裏、$ 3 $ 枚目は裏を上に向けて置く。 - $ 1 $ 枚目は裏、$ 2 $ 枚目は表、$ 3 $ 枚目は表を上に向けて置く。 よって、`HTT` や `THH` といった出力が正解となります。

### Sample Explanation 2

上に向けられた面に書かれた整数の総和がちょうど $ S\ (=\ 25) $ となるようにカードを置くことはできません。

## 样例 #1

### 输入

```
3 11
1 4
2 3
5 7```

### 输出

```
Yes
THH```

## 样例 #2

### 输入

```
5 25
2 8
9 3
4 11
5 1
12 6```

### 输出

```
No```

# 题解

## 作者：DYYqwq (赞：14)

# Problem

给出 $n$ 个卡片，每个卡片有正反两面，分别写着 $a_i$ 和 $b_i$，对于每张卡片你可以选择正面或反面，问能否使这些数的和为 $m$。

能的话，输出 $\texttt{Yes}$，然后再输出任意一种放置方法；不能的话，输出 $\texttt{No}$。

# Solution

一眼 dp。

dp 表示应该很好想，直接一个 `bool` 的 dp 数组，表示前 $i$ 张牌能否组成 
$j$。

dp 式子也很显然。

$dp_{i,j+a_i} = dp_{i-1,j}$

$dp_{i,j+b_i} = dp_{i-1,j}$

意思就是第 $i$ 个卡片，如果第 $i - 1$ 个卡片能组成 $j$，那显然，对于第 $i$ 个卡片也能组成 $j+a_i$（第 $i$ 个卡片翻了个正面）或者 $j+b_i$（第 $i$ 个卡片翻了个背面）。

最后直接看 $dp_{n,m}$ 是否为 $1$，然后退回去输出方案。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , m;
int a[110] , b[110];
bool dp[110][10110]; // 注意是 bool 类型
string ans; // 统计最后的方案
void output(int x , int y)
{
    if(!x) return; // 没纸牌了！
    if(y >= a[x] && dp[x - 1][y - a[x]]) // 第 x 个用正面
    {
        output(x - 1 , y - a[x]); // 继续递归
        ans += 'H'; // 答案加一个正面
    }
    else if(y >= b[x] && dp[x - 1][y - b[x]]) // 同理
    {
        output(x - 1 , y - b[x]);
        ans += 'T';
    }
}
int main()
{
    dp[0][0] = true; // 初始化
    scanf("%d%d" , &n , &m);
    for(int i = 1 ; i <= n ; i ++)
        scanf("%d%d" , &a[i] , &b[i]);
    for(int i = 1 ; i <= n ; i ++)
    {
        for(int j = 0 ; j <= m ; j ++)
        {
            if(dp[i - 1][j])
            {
                dp[i][j + a[i]] = dp[i - 1][j];
                dp[i][j + b[i]] = dp[i - 1][j];
                // 转移方程，上面讲过
            }
        }
    }
    if(dp[n][m]) // 可以
    {
        printf("Yes\n");
        output(n , m); // 从第n个卡牌开始，总和是m
        cout << ans << "\n"; // 最后输出答案
    }
    else
        printf("No\n"); // 不可以，总司令！
    return 0;
}
```

我们注意 `output` 函数。

变量 $x$ 表示目前是第几个卡牌，变量 $y$ 表示目前还剩多少（因为是一个个扣的 正/反 面数），然后判一下到底剩下的数到底够不够扣一个 正/反 面的，还有就是判一下剩下的 $x-1$ 个数到底能不能组成你扣掉后 正/反 面的 $y$。

还有不懂就多看看注释吧 qwq

或者私信问我也行 QAQ

---

## 作者：_GW_ (赞：3)

## 思路
看到题马上想到爆搜，然而时间复杂度 $2^n$，绝对超时。

考虑剪枝。

看到 $M$ 的范围，可以记忆化搜索！

我们在 dfs 中传入当前选到了哪个数和当前数值。

由于 $N$ 最大 $10^2$，当前数值最大 $10^4$，所以记忆化数组只用开 $10^6$！

最后，我们需要在 dfs 的同时输出。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=114,M=10101;
int a[N][2],b[N],f[N][M],n,m,num,val;
bool flag;
void dfs(int i,int res)
{
    if(!i)
    {
        if(res==m)
        {
            cout<<"Yes"<<endl;
            flag=1;
            
        }return;
    }
    if(res>m||f[i][res])
    {
        return;
    }
    for(int j=0;j<=1;j++)
    {
        if(a[i][j]+res<=m)
        {
            dfs(i-1,res+a[i][j]);
            if(flag)
            {
                cout<<(j?"T":"H");
                return;
            }
        }
    }
    f[i][res]=1;
    return;
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i][0]>>a[i][1];
    dfs(n,0);
    if(!flag) cout<<"No"<<endl;
    return 0;
} 
```
## 练习
[P1434](https://www.luogu.com.cn/problem/P1434)

---

## 作者：MichaelDickson (赞：2)

## [ABC271D] Flip and Adjust

### 题目大意

给出 $n$ 给卡片，每个卡片有正反两面，分别写着 $a_i$ 和 $b_i$，对于每张卡片你可以选择正面或反面，问是否能使这些数的和为 $m$ 。如果能，输出 Yes 并输出一种方案，否则输出 No。

### 解题思路

记忆化搜索，用标记数组标记准备选第 $i$ 个数且此时选得的总和为 $sum$ 的这个状态是否搜到过。

- 如果 $sum$ 大于 $m$，怎么往后选也无力回天了，于是回溯。

- 如果有一次状态能搜成功， 返回 $1$，边回溯边输出方案。注意回溯的过程是倒过来的，所以我们的 $i$ 要从 $n$ 到 $1$ 反过来搞。

### 代码

```c++
#include <algorithm>
#include <iostream>

using namespace std;

int n, m, a[103][2];

bool f[103][10003];             // 标记数组

bool Dfs(int i, int sum) {
	if (i <= 0) {                 // 搜完了
		if (sum == m) {
			cout << "Yes\n";
			return 1;                 // 搜到了合法方案, 开始回溯输出方案 
		}
		return 0;
	}
	if (sum > m || f[i][sum]) {   // 剪枝+判重 
		return 0;
	}
	f[i][sum] = 1;
	for (int j = 0; j <= 1; j++) {
		if (Dfs(i - 1, sum + a[i][j])) {  // 进入后面的状态, 顺便看它能否成功 
			cout << (j ? 'T' : 'H');        // 能成功就输出方案 
			return 1;
		}
	}
	return 0;
}

signed main() {
	ios::sync_with_stdio(), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i][0] >> a[i][1];
	}
	if (!Dfs(n, 0)) {             // 注意从n到0搜索 
		cout << "No";
	}
	return 0;
}
```

---

## 作者：guanyf (赞：2)

### 分析、思路
先将题目用状态图表示出来，这个状态图一看就具有拓扑序，因此可以动态规划。

设状态为 $dp_{i,j,0/1}$ 表示前 $i$ 个卡片的和为 $j$，且第 $i$ 个卡片是正面或反面时，是否存在这样的情况。

状态转移方程：
$$(1 \le i \le n,1\le j \le m)$$
$$dp_{0,0,0} = dp_{0,0,1} = 1$$
$$dp_{i,j,0} = dp_{i-1,j-a_i,0} \operatorname{or} dp_{i-1,j-a_i,1}$$
$$dp_{i,j,1} = dp_{i-1,j-b_i,0} \operatorname{or} dp_{i-1,j-b_i,1}$$

当 $dp_{n,m,0}$ 或 $dp_{n,m,1}$ 为 $1$ 时，输出 `Yes`，否则输出 `No`。

当存在答案时，从 $dp_{n,m,0/1}$ 往回推。设前 $i$ 个卡片的和为 $s$，则如果 $dp_{i,s,0} = 1$ 时，则为正，$s \rightarrow s-a_i$；否则为反，$s \rightarrow s-b_i$。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 105, MAXM = 10005;
int n, a[MAXN], b[MAXN], s;
bool dp[MAXN][MAXM][2];
char ans[MAXN];
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> s;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
  }
  dp[0][0][0] = dp[0][0][1] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = a[i]; j <= s; j++) {
      dp[i][j][0] |= (dp[i - 1][j - a[i]][0] || dp[i - 1][j - a[i]][1]);
    }
    for (int j = b[i]; j <= s; j++) {
      dp[i][j][1] |= (dp[i - 1][j - b[i]][0] || dp[i - 1][j - b[i]][1]);
    }
  }
  if (dp[n][s][0] || dp[n][s][1]) {
    cout << "Yes\n";
    for (int i = n; i >= 1; i--) {
      if (dp[i][s][0]) {
        ans[i] = 'H', s -= a[i];
      } else {
        ans[i] = 'T', s -= b[i];
      }
    }
    for (int i = 1; i <= n; i++) {
      cout << ans[i];
    }
  } else {
    cout << "No";
  }
  return 0;
}
```


---

## 作者：ljc888 (赞：2)

## 题意翻译

给定 $n$ 个硬币，每个硬币正反两面都有个数 $a_i$ 和 $b_i$，问你能否改变硬币的方向使得朝上这面的数的硬币之和等于 $m$。

## 题解

很容易能看出这是一道 DP 题。

我们可以创建一个二维的 bool 数组 $f_{i,j}$ 表示前 $i$ 个硬币是否能凑到 $j$ 这个数。

状态转移方程如下：

$$
f_{i,j} = f_{i-1,j+a_{i}} \wedge f_{i-1,j+b_{i}}
$$

最后我们要注意的是因为这个题目要求我们输出硬币的正反方向，所以要用递归。


```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,a[110],b[110];
bool flag=0,f[110][10010];

void dfs(int x,int y){  // dp
	if(x<1){        // 如果所有都递归过
		if(y==m){    // 如果能刚好凑出m
			cout <<"Yes" << endl;
			flag=1;    // 让回溯的时候输出状态
		}
		return ;
	}
	if(f[x][y])return ;   // 如果已经走过说明行不通
	if(y+a[x]<=m){      // 如果不会越界
		dfs(x-1,y+a[x]);  // 递归
		if(flag){      // 如果能凑出
			cout << "H";
			return ;
	    }
	}
	if(y+b[x]<=m){   // 同理
		dfs(x-1,y+b[x]);
		if(flag){
			cout << "T";
			return ;
		}
	}
	f[x][y]=1;   // 如果都没有凑出就记录它来过了
	return ;
}

int main(){
	cin >> n >> m;
	for(int i=1;i<=n;i++){
		cin >> a[i] >> b[i];
	}
	dfs(n,0);
	if(!flag)cout << "No";  // 如果没有找出
	return 0;
}
```

---

## 作者：fish_love_cat (赞：1)

一个还算常规的动归与一个挺费脑子的输出。

---

**挺正常の动归：**

我们定义一个 `bool` 类型的 $dp$ 数组，并定义 $dp_{i,j}$ 为用前 $i$ 项能否拼出 $j$。

据此，转移方程也不难推出：

$$dp_{i,j+a_i}=dp_{i-1,j}$$

$$dp_{i,j+b_i}=dp_{i-1,j}$$

解释：

截止上一个卡牌，如果能拼出 $j$，这一次就可以拼出 $j+a_i$ 和 $j+b_i$，证明显然。那么我们就把 $dp_{i-1,j}$ 的值赋给 $dp_{i,j+a_i}$ 与 $dp_{i,j+b_i}$ 即可。

那么只要 $dp_{n,m}$ 为真，就代表可以拼出来啦。

---

**超费脑の输出：**

其实可以用递归实现，我们把 $n,m$ 都传进去（下文命做 $x,y$），如果 $x\ne0$，那么如果 $m\ge a_x$ 而且这里选的是正面，那么就往下搜，并把 $x-1$，$y$ 减去这里加的数值。搜完，在最终答案后加个代表正面的 `H` 即可。

如果不满足，就选背面，搜索同理。

还有一点，若 $x=0$，就是搜到头了，记得直接返回！

---

**卡哇伊の代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110],b[110];
bool dp[110][10110];
int n,m;
string ans;
void sc(int x,int y){//超费脑の输出
    if(!x) return;
    if(y>=a[x]&&dp[x-1][y-a[x]]){
        sc(x-1,y-a[x]);
        ans+='H';
    }else if(y>=b[x]&&dp[x-1][y-b[x]]){
        sc(x-1,y-b[x]);
        ans+='T';
    }
}
int main(){
    dp[0][0]=true;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(dp[i-1][j]){
                dp[i][j+a[i]]=dp[i-1][j];
                dp[i][j+b[i]]=dp[i-1][j];
            }//挺正常の动归
        }
    }
    if(dp[n][m]){
        cout<<"Yes\n";
        sc(n,m);
        cout<<ans<<endl;
    }else{
        cout<<"No\n";
    }
    return 0;//诶嘿嘿の结束
}
```

---

## 作者：xiaoPanda (赞：1)

## D - Flip and Adjust

### Problem

给出 $n$ 个卡片，每个卡片有正反两面，分别写着 $a_i$ 和 $b_i$，对于每张卡片你可以选择正面或反面，问内否使这些数的和为 $m$。

$1\le n\le 100,1\le m\le 10^4$

### Solution

考虑 dp，设  $f[i][j]$ 表示用前 $i$ 张牌能否组成 $j$ ，那么有：

$f_{i,j}=f_{i,j}\operatorname{or} f_{i-1,j-a_i}$

$f_{i,j}=f_{i,j}\operatorname{or} f_{i-1,j-b_i}$


判断一下 $f[n][m]$ 是否为 $1$ 即可，然后再倒着往前面找记录答案，时间复杂度为 $O(nm)$ 。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105,S=1e4+5;
int f[N][S],g[N][S];
int a[N],b[N],n,s;
vector<char>ans;
int main(){
	cin>>n>>s;f[0][0]=1;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
	for(int i=1;i<=n;i++)
		for(int j=s;j>=0;j--){
			if(j-a[i]>=0&&f[i-1][j-a[i]])
				g[i][j]=0,f[i][j]=1;
			if(j-b[i]>=0&&f[i-1][j-b[i]])
				g[i][j]=1,f[i][j]=1;
		}
	if(!f[n][s])return puts("No"),0;
	while(true){
		if(g[n][s]==0)ans.push_back('H');
		else ans.push_back('T'); 
		int x=n,y=s;
		n--;s-=g[x][y]?b[x]:a[x];
		if(n==0)break;
	}reverse(ans.begin(),ans.end());
	puts("Yes");
	for(auto v:ans)cout<<v;cout<<endl;
	return 0;
} 
```


---

## 作者：紊莫 (赞：1)

## 题意简述

有 $n$ 张卡片，正面写着数字 $a_i$，反面写着数字 $b_i$。现在你需要确定这些卡片的正反面，使得所有卡片朝上的一面数字之和为 $S$。若有解，输出任意一组方案。

## 分析

一个可行性动规比较显然，$dp_{i,j}$ 表示前 $i$ 张卡片能否和为 $j$。   
转移方程也很简单：  

```cpp
if(dp[i][j]!=0)
	dp[i+1][j+a[i+1]]=dp[i+1][j+b[i+1]]=1;
```  

这题为了加点难度符合第四题的水平，于是加了个求转移路径，由于是任意输出一组解，那么就可以在每次成功转移时记录下是从哪里转移过来的，最后倒着搜索一遍即可。  

```cpp
if(dp[i][j]!=0)
{
	dp[i+1][j+a[i+1]]=dp[i+1][j+b[i+1]]=1;
	if(i==j&&i==0)
		path[i+1][j+a[i+1]]=path[i+1][j+b[i+1]]=make_pair(-1,-1);
	else
		path[i+1][j+a[i+1]]=path[i+1][j+b[i+1]]=make_pair(i,j);
}
```

```cpp
vector<int> ans;
void find(int i,int j)
{
	if(i!=-1&&j!=-1)
	{
		int x=path[i][j].first,y=path[i][j].second;
		if(x==-1||path[x][y]!=make_pair(0,0)) find(x,y);
	}
	if(j==-1) j=0;
	ans.push_back(j);
}
//-1 的使用是为了防止和全局变量的 0 混淆。
```
注：可能由于个人码风原因，写的不是那么容易接受，重点在理解思想。  

如果按照这种方法得到的答案是每次卡片的数字的前缀和，容易想到只需要前后相减就是当次选择的卡片。  

```cpp
for(int i=1;i<ans.size();i++)
	cout<<(ans[i]-ans[i-1]==a[i]?"H":"T"); 
```  

## 参考代码

由于篇幅较大，且略丑，故不展示。  
有需者亦可自取：  

[$\text{Code}$](https://www.luogu.com.cn/paste/jnmkr5ep)





---

## 作者：Mr_Gengar (赞：0)

## Problem

给出 $n$ 个卡片，每个卡片有正反两面，分别写着 $a_i$ 和 $b_i$，对于每张卡片你可以选择正面或反面，问内否使这些数的和为 $m$。

$1\le n\le 100,1\le m\le 10^4$

~~（没错这是复制粘贴的题面）~~

## Solution
很明显是一道DP题，基本就是个板子。

定义状态 $f_{i,j}$ 表示已经考虑了前 $i$ 个硬币，所得的和为 $j$。

显然，状态转移方程为：

$f_{i,j} = f_{i-1,j-a_i} ∧ f_{i-1,j-b_i}$

不过题目还要求求出转移路径，使用递归求解即可。~~（毕竟D题就考个板子有点过分）~~

最后记得注意些细节，比如递归边界和数组越界。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 101, kMaxM = 1e4 + 1;

int n, s, a[kMaxN], b[kMaxN];
bool dp[kMaxN][kMaxM];

void print(int i, int s) {
  if (i) {
    if (s >= a[i] && dp[i - 1][s - a[i]]) {
      print(i - 1, s - a[i]);
      cout << 'H';
    } else if (s >= b[i] && dp[i - 1][s - b[i]]) {
      print(i - 1, s - b[i]);
      cout << 'T';
    }
  }
}

int main() {
  cin >> n >> s;
  for (int i = 1; i <= n; i++) {
    cin >> a[i] >> b[i];
  }
  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < kMaxM; j++) {
      if (j >= a[i]) {
        dp[i][j] |= dp[i - 1][j - a[i]];
      }
      if (j >= b[i]) {
        dp[i][j] |= dp[i - 1][j - b[i]];
      }
    }
  }
  if (dp[n][s]) {
    cout << "Yes\n";
    print(n, s);
  } else {
    cout << "No\n";
  }
  return 0;
}
```

---

## 作者：Tsawke (赞：0)

# [[ABC271D] Flip and Adjust](https://www.luogu.com.cn/problem/AT_abc271_d) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC271D)

## 题面

给定 $ n $ 张卡片，正面是 $ a_i $，背面是 $ b_i $，给定 $ S $ 要求构造方案钦定这 $ n $ 张卡片选择正面的数或反面的数，使得求和后洽等于 $ S $，无解输出 `No`，反之输出 `Yes` 并输出任意方案。

## Solution

一般的思路都是 DP 同时记录决策点然后最后跑一遍答案，不过这样还需要动脑，本题范围较小不如暴力一点，我们直接在 DP 过程中的每一个状态记录所有牌的正反，最开始的思路是开一个 `bitset` 这样多出来的复杂度是 $ O(\dfrac{n}{w}) $ 也就是 $ O(1) $，不过仔细一想这东西直接开个 `basic_string < char >` 无脑维护就行了，这样转移会多一个复制的 $ O(n) $，空间也会多一个 $ O(n) $，最终时空复杂度都是 $ O(n^2S) $，刚好 `1e8`。

转移显然：
$$
dp(i, j) = dp(i - 1, j - a_i) + H
$$

$$
dp(i, j) = dp(i - 1, j - b_i) + T
$$

然后中间判断一下是否能转移，也就是 `dp[i][j].size()` 是否为 $ i $，以及 $ j - a_i \ge 0 $ 和 $ j - b_i \ge 0 $ 即可。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}
#define ROPNEW_NODE void* Node::operator new(size_t){static Node* P = nd; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N, S;
int A[110], B[110];
basic_string < char> dp[110][11000];

int main(){
    N = read(), S = read();
    for(int i = 1; i <= N; ++i)A[i] = read(), B[i] = read();
    dp[1][A[1]] += 'H', dp[1][B[1]] += 'T';
    for(int i = 2; i <= N; ++i)
        for(int j = 0; j <= S; ++j){
            if(j - A[i] >= 0 && (int)dp[i - 1][j - A[i]].size() == i - 1)dp[i][j] = dp[i - 1][j - A[i]] + 'H';
            if(j - B[i] >= 0 && (int)dp[i - 1][j - B[i]].size() == i - 1)dp[i][j] = dp[i - 1][j - B[i]] + 'T';
        }
    if((int)dp[N][S].size() != N)printf("No\n"), exit(0);
    printf("Yes\n");
    for(auto v : dp[N][S])printf("%c", v);
    printf("\n");
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_02_09 初稿

---

