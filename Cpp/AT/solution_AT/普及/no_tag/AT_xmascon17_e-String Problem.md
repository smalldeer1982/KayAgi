# String Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/xmascon17/tasks/xmascon17_e

$ 2 $ つの文字列 $ S,\ T $ が与えられます。 以下のような操作を好きな順番で好きなだけ行うことで $ S $ を $ T $ にできるかどうかを判定してください。

- 操作 $ A $：$ S $ に含まれる文字 `A` を $ 1 $ つ削除する。
- 操作 $ B $：$ S $ の好きな位置に文字 `B` を $ 1 $ つ挿入する。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|,\ |T|\ \leq\ 1000 $
- $ S,\ T $ は大文字アルファベットのみからなる

### 部分点

- $ |S|\ \leq\ 10 $ を満たすデータセットに正解した場合は、$ 50 $ 点が与えられる。
- 追加制約のないデータセットに正解した場合は、上記とは別に $ 50 $ 点が与えられる。

### Sample Explanation 1

例えば `XMAS` → `XBMAS` → `XBMS` のように操作すれば良いです。

### Sample Explanation 2

例えば `AABABA` → `ABABA` → `BABABA` → `BABABAB` → `BABBABAB` のように操作すれば良いです。

## 样例 #1

### 输入

```
XMAS
XBMS```

### 输出

```
YES```

## 样例 #2

### 输入

```
AABABA
BABBABAB```

### 输出

```
YES```

## 样例 #3

### 输入

```
AB
AA```

### 输出

```
NO```

## 样例 #4

### 输入

```
ATCODER
CONTEST```

### 输出

```
NO```

# 题解

## 作者：Warriors_Cat (赞：11)

~~感觉这道题是一个很自然的 DP 题啊……~~

### $Solution:$

考虑 DP，我们定义 $f[i][j]$ 表示 $S$ 的前 $i$ 个字符与 $T$ 的前 $j$ 个字符是否能够匹配。很明显 $f[0][0]=1$。

那么，考虑枚举所有的 $(i, j)$ 数对，有以下情况：

若 $S[i]$ 为字符 $A$，那么 $f[i][j]$ 就可以从 $f[i - 1][j]$ 转移过来。

若 $T[j]$ 为字符 $B$，那么 $f[i][j]$ 就可以从 $f[i][j - 1]$ 转移过来。

若 $S[i]$ 与 $T[j]$ 相同，那么 $f[i][j]$ 就可以从 $f[i - 1][j - 1]$ 转移过来。

最后判断 $f[|S|][|T|]$ 是否为真就行了。

附代码：

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int f[1010][1010], n, m;
char s[1010], t[1010];
int main(){
	scanf("%s%s", s + 1, t + 1);
	f[0][0] = 1;//边界条件
	n = strlen(s + 1); m = strlen(t + 1);
	for(int i = 1; i <= n; ++i) if(s[i] == 'A') f[i][0] |= f[i - 1][0];//像过河卒一样特判边界
	for(int i = 1; i <= m; ++i) if(t[i] == 'B') f[0][i] |= f[0][i - 1];//同上
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m; ++j){
			if(s[i] == 'A') f[i][j] |= f[i - 1][j];
			if(t[j] == 'B') f[i][j] |= f[i][j - 1];
			if(s[i] == t[j]) f[i][j] |= f[i - 1][j - 1];
		}
	}// 如上
	if(f[n][m]) puts("YES"); else puts("NO");
	return 0;//完结撒花-v-
}

```

---

## 作者：皎月半洒花 (赞：11)

兔这么可爱，最喜欢兔了，所以就要跟着兔做题鸭

~~xht：兔是我的我的~~

以上是扯淡。看到兔发的讨论就来秒一秒，结果真秒了（

大家别再抄 std 或者兔的代码啦，这样一点也不帅。还是自己想想比较好吧。

____


根据第一个样例不难想到，加 B 和删 A 这两个操作本质上没有任何关系，所以可以分开做。那么可以知道，如果只看加 B 的操作，那么需要 $t$ 在 $s$ 加完 B 之后，是 $s$ 的某个子序列。这个可以直接仿照 LCS 的 dp，$f_{i,j}$ 表示最多匹配多少位。xxs转移不再赘述。

考虑接下来是删 A。那么如果确定了 $t$ 是 $s$ 的子序列，那么就只需要知道 $s$ 中是否有奇怪的、没法被删的多余元素。于是再维护一个 $g_{i,j}$ 表示若想要 $s_i$ 和 $t_j$ 匹配上，最少需要向 $s$ 内添加多少个 B。之后就只需要比较一下是否 $s$ 比 $t$ 只是多一堆 A 即可。

~~应该从 0 开始枚举，挂了一发；改成 0 之后越界了，于是又挂了一发，我太难了~~

```cpp

int n, m ;
int sa, ta ;
int f[N][N] ;
int g[N][N] ;
char s[N], t[N] ;

int main(){
    cin >> (s + 1) >> (t + 1) ;
    n = strlen(s + 1), m = strlen(t + 1) ; s[0] = '#' ;
    memset(g, 63, sizeof(g)) ; g[0][0] = g[1][0] = g[0][1] = 0 ;
    for (int i = 0 ; i <= n ; ++ i)
        for (int j = 1 ; j <= m ; ++ j){
            if (f[i - 1][j] > f[i][j] || (f[i - 1][j] == f[i][j] && g[i - 1][j] < g[i][j]))
                g[i][j] = g[i - 1][j], f[i][j] = f[i - 1][j] ;
            if (f[i][j - 1] > f[i][j] || (f[i][j - 1] == f[i][j] && g[i][j - 1] < g[i][j]))
                g[i][j] = g[i][j - 1], f[i][j] = f[i][j - 1] ;
            if (t[j] == 'B'){
                int w = f[i][j - 1] + 1 ;
                if (w > f[i][j] || (w == f[i][j] && g[i][j - 1] + 1 < g[i][j]))
                    g[i][j] = g[i][j - 1] + 1, f[i][j] = f[i][j - 1] + 1 ;
            }
            if (s[i] == t[j]){
                int w = f[i - 1][j - 1] + 1 ;
                if (w > f[i][j] || (w == f[i][j] && g[i - 1][j - 1] < g[i][j]))
                    g[i][j] = g[i - 1][j - 1], f[i][j] = f[i - 1][j - 1] + 1 ;
            }
//            printf("%d %d %d\n", i, j, f[i][j]) ;
        }
//    cout << f[n][m] << '\n' ;
//    cout << g[n][m] << '\n' ;
    if (f[n][m] < m) return puts("NO"), 0 ;
    for (int i = 1 ; i <= n ; ++ i) sa += s[i] == 'A' ;
    for (int i = 1 ; i <= m ; ++ i) ta += t[i] == 'A' ;
    if (sa - ta != n + g[n][m] - m) return puts("NO"), 0 ; else return puts("YES"), 0 ;
}

```


---

## 作者：SamariumPhosphide (赞：6)

这道题目可以使用 DP 进行实现。为了方便 DP，可以把两个操作都改为删除操作。

操作1为 S 中删除一个字符 A，操作 2 为从 T 中删除一个字母 B。

然后就很容易 DP 啦，用 $dp[i][j]$ 表示 S 的前 $i$ 个字母与 T 的前 $j$ 个字母能不能通过这些操作变为一样的字符串。

那么，如果 S 的第 $i$ 个字母为 A，S 的第 $i$ 个字符可以删除，可以从 $dp[i - 1][j]$ 转移。

同样的，如果 T 的第 $j$ 个字母为 B，T 的第 $j$ 个字符可以删除，可以从 $dp[i][j-1]$ 转移。

如果 S 的第 $i$ 个字母和 T 的第 $j$ 本来就一样，那么可以不用管这两个字符，从 $dp[i-1][j-1]$ 转移。

最后取个 $\max$ 就可以了。

~~开始为了抢神兔后第一个AC结果犯了几件自己都无法想象有多傻逼的事情。~~

最后贴上无注释代码，~~码风很丑不要喷哦~~。

```cpp
#include <cstdio>
#include <iostream>
#include <string>

const int N = 1100;

bool dp[N][N];
std::string s, t;

void input() {
  std::cin >> s >> t;
}

void solve() {
  for (int i = 0; i <= (int) s.length(); i++) {
    for (int j = 0; j <= (int) t.length(); j++) {
      if (i == 0 && j == 0) {
        dp[i][j] = true;
        continue;
      }
      if (i != 0 && s[i - 1] == 'A') {
        dp[i][j] |= dp[i - 1][j];
      }
      if (j != 0 && t[j - 1] == 'B') {
        dp[i][j] |= dp[i][j - 1];
      }
      if (i != 0 && j != 0 && s[i - 1] == t[j - 1]) {
        dp[i][j] |= dp[i - 1][j - 1];
      }
    }
  }
}

void output() {
  if (dp[s.length()][t.length()]) {
    puts("YES");
  } else {
    puts("NO");
  }
}

int main() {
  input();
  solve();
  output();
  return 0;
}
```



---

## 作者：FZzzz (赞：5)

昨天似乎有人说有人 A 了这题他女装还是怎么样，我看了两眼题然后秒了，结果那个贴被删了就没写。

今天看到兔队写了这题，想着复习一下普及组 dp 也是好事，就写了一发。

事实证明我的 dp 水平已经退化到不知道成什么样了，写个记搜 `vis[x][y]=1` 都能忘。

就是一眼设 $dp_{x,y}$ 为当前匹配到 $s$ 的第 $x$ 个字符，$t$ 的第 $y$ 个字符，然后可不可能。

转移的话分三种，一种是直接匹配，一种是如果 $s$ 这一位为 `A` 的话可以直接删掉，如果 $t$ 这一位是 `B` 就可以加进来，然后取一个或就可以了。
```cpp
#include<cstring>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=1e3+5;
int n,m;
char s[maxn],t[maxn];
bool d[maxn][maxn],vis[maxn][maxn];
bool dp(int x,int y){
	if(x==n&&y==m) return 1;
	if(vis[x][y]) return d[x][y];
	vis[x][y]=1;
	d[x][y]=0;
	if(x<n&&y<m&&s[x]==t[y]) d[x][y]|=dp(x+1,y+1);
	if(x<n&&s[x]=='A') d[x][y]|=dp(x+1,y);
	if(y<m&&t[y]=='B') d[x][y]|=dp(x,y+1);
	return d[x][y];
}
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	scanf("%s%s",s,t);
	n=strlen(s);
	m=strlen(t);
	printf(dp(0,0)?"YES\n":"NO\n");
	return 0;
}
```

---

## 作者：qip101 (赞：0)

### Solution:

这是一道简单的普及组动态规划题。

设计状态：$f(i,j)$ 表示字符串 $A$ 的前 $i$ 个字符和字符串 $B$ 的前 $j$ 个字符是否匹配。

状态转移主要就是讨论当前这个字符是 $A$ 还是 $B$,从 $f(i,j)$ 转移到 $f(i,j+1)$ 或者 $f(i+1,j)$ 或者 $f(i+1,j+1)$。

记得还要初始化 $f(0,0)$ 为1。

### Core code:

```cpp
int main()
{
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	f[0][0]=1;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++) 
			if(f[i][j])
			{
				if(i<n && j<m && s[i+1]==t[j+1]) 
					f[i+1][j+1]=1;
				if(i< n&&s[i+1]=='A') 
					f[i+1][j]=1;
				if(j< m&&t[j+1]=='B') 
					f[i][j+1]=1;
			}
	puts(f[n][m]?"YES":"NO");
    return 0;
}
```



---

## 作者：zjc5 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_xmascon17_e)

**思路：**

可以把题目意思转换成：

$\bullet$ 操作 $A$：删除 $S$ 中任意位置的字母 $A$。

$\bullet$ 操作 $B$：删除 $T$ 中任意位置的字母 $B$。

能否让 $S=T$。

那么可以用递归来做。

递归里面两个参数，分别表示 $S$ 遍历到的位置和 $T$ 遍历到的位置。

当 $S$ 和 $T$ 都遍历完了，就代表成功。

代码时间复杂度 $O(|S|\times|T|)$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
int ls, lt;
bool bl[1010][1010];
char s[1010], t[1010];
void dfs(int a, int b) {
	if (bl[a][b]) return ;//记忆化搜索，保证时间复杂度不超过ls*lt
	bl[a][b] = true;
	if (a == ls && b == lt) {
		puts("YES");
		exit(0);
	}
	if (s[a] == t[b]) dfs(a + 1, b + 1);//相等，继续下一个位置
	if (t[b] != 'B' && s[a] != 'A') return ;//无法继续
	if (t[b] == 'B') dfs(a, b + 1);//删除T中的字母B
	if (s[a] == 'A') dfs(a + 1, b);//删除S中的字母A
}
int main() {
	scanf("%s%s", s, t);
	ls = strlen(s);
	lt = strlen(t);
	dfs(0, 0);
	puts("NO");
	return 0;
}
```

---

## 作者：scp020 (赞：0)

### 题意

给定两个字符串 $s$ 和 $t$，可以对 $s$ 字符串进行如下的两种操作：

- 对字符串 $s$ 的任意位置删去 $A$ 字符。

- 对字符串 $s$ 的任意位置插入 $B$ 字符。

问是否可以进行若干次操作后将 $s$ 变为 $t$。

### 解决

考虑动态规划做法，时间复杂度 $O(l_s \times l_t)$。

一个动态规划数组 $f$，$\mathit{f}_{i,j}$ 表示 $s_i$ 和 $t_j$ 是否能匹配。

动态规划分成两个阶段解决。

1. 初始化：

$\mathit{f}_{0,0}=1$（这个前往别忘）

$\begin{cases}\mathit{f}_{i,0}=\mathit{f}_{i,0}|\mathit{f}_{i-1,0}&s_i=A\\\mathit{f}_{0,i}=\mathit{f}_{0,i}|\mathit{f}_{0,i-1}&t_i=B\end{cases}$

2. 动态规划：

$\mathit{f}_{i,j}=\begin{cases}\mathit{f}_{i,j}|\mathit{f}_{i-1,j}&s_i=A\\\mathit{f}_{i,l}|\mathit{f}_{i,l-1}&t_i=B\\\mathit{f}_{i,j}|\mathit{f}_{i-1,j-1}&s_i=t_j\end{cases}$

最后判断 $\mathit{f}_{l_s,l_t}$ 是否为真即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
bool f[1010][1010];
int main()
{
    cin>>s>>t,f[0][0]=1,s='0'+s,t='0'+t;
    for(int i=1;i<s.size();i++) if(s[i]=='A') f[i][0]=f[i][0]|f[i-1][0];
    for(int i=1;i<t.size();i++) if(t[i]=='B') f[0][i]=f[0][i]|f[0][i-1];
    for(int i=1;i<s.size();i++)
    {
        for(int j=1;j<t.size();j++)
        {
            if(s[i]=='A') f[i][j]=f[i][j]|f[i-1][j];
            if(t[j]=='B') f[i][j]=f[i][j]|f[i][j-1];
            if(s[i]==t[j]) f[i][j]=f[i][j]|f[i-1][j-1];
        }
    }
    if(f[s.size()-1][t.size()-1]) cout<<"YES";
    else cout<<"NO";
    return 0;
}
```


---

## 作者：lytqwq (赞：0)

~~看神兔发帖来做的+1~~

题意：可以在字符串$S$中加字符$B$删字符$A$，问能不能转化为字符串$T$

设$f[i][j]$为$S$串前$i$个字符和$T$串前$j$个字符能不能转化

当$S[i]==T[j]$时，$f[i][j]$只考虑$f[i-1][j-1]$，当$f[i-1][j-1]$能转化时，$f[i][j]$就能转化

如果$S[i]$为$A$，当$f[i-1][j]$能转化时，$f[i][j]$就能转化，就相当于去掉这个$A$

如果$T[i]$为$B$，当$f[i][j-1]$能转化时，$f[i][j]$就能转化，就相当于在$S[i]$后面加个$B$

**注意在$S,T$最前面或者最后面也留个空用来供转移就行了。**

初始化$f[0][0]$为能转化，其他的都不能，然后推完后看看$f[lenS][lenT]$就行了

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1001;
int a[N][N];
char S[N],T[N];
int main(){
	scanf("%s",S+1);
	scanf("%s",T+1);
	int Sn=strlen(S+1),Tn=strlen(T+1);
	memset(a,-1,sizeof(a));
	a[0][0]=0;//0代表能转化，-1代表不行 
	for(int i=0;i<=Sn;i++){
		for(int o=0;o<=Tn;o++){
			if(S[i]==T[o]&&i!=0&&o!=0){
				a[i][o]=a[i-1][o-1];
			}
			else{
				if(S[i]=='A'&&i!=0){
					a[i][o]=a[i-1][o];
				}
				if(T[o]=='B'&&o!=0){
					a[i][o]=max(a[i][o],a[i][o-1]);
				}
			}
		}
	}
	if(a[Sn][Tn]==0){
		printf("YES\n");
	}
	else{
		printf("NO\n");
	}
}
```



---

