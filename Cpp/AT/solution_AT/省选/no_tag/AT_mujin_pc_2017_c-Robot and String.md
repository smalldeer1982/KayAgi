# Robot and String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/mujin-pc-2017/tasks/mujin_pc_2017_c

あなたは、文字列を処理するロボットを開発しています。 英小文字のみからなる文字列 $ t $ をこのロボットに与えると、ロボットは次の手順に従って文字列を処理します。

1. $ t_i\ =\ t_{i\ +\ 1} $ であるような最小の $ i $ を選ぶ。 そのような $ i $ が存在しない場合、処理を終える。
2. $ t_i $ が `z` である場合、$ t_i $, $ t_{i\ +\ 1} $ を取り除く。 $ t_i $ が `z` でない場合、$ t_i $ の次のアルファベットを $ c $ として、$ t_i $, $ t_{i\ +\ 1} $ をまとめて$ 1 $ 文字の $ c $ へ置き換える。
3. 1. へ戻る。

例えば、文字列 `axxxxza` をロボットに与えると、文字列は `axxxxza` → `ayxxza` → `ayyza` → `azza` → `aa` → `b` と処理されます。

英小文字のみからなる文字列 $ s $ が与えられます。 $ s $ について $ Q $ 個の質問に答えてください。 $ i $ 番目の質問は次のようなものです。

- $ s $ の $ l_i $ 文字目から $ r_i $ 文字目までの連続した部分文字列をロボットに与えると、処理された後の文字列は空文字列になるか？

## 说明/提示

### 制約

- $ 1\ <\ =\ |s|\ <\ =\ 5\ ×\ 10^5 $
- $ s $ は英小文字のみからなる。
- $ 1\ <\ =\ Q\ <\ =\ 10^5 $
- $ 1\ <\ =\ l_i\ <\ =\ r_i\ <\ =\ |s| $

### Sample Explanation 1

\- $ 1 $ 番目の質問では、文字列は `axxxxza` → `ayxxza` → `ayyza` → `azza` → `aa` → `b` と処理されます。 - $ 2 $ 番目の質問では、文字列は `xxxxz` → `yxxz` → `yyz` → `zz` → `` と処理されます。

## 样例 #1

### 输入

```
axxxxza
2
1 7
2 6```

### 输出

```
No
Yes```

## 样例 #2

### 输入

```
aabcdefghijklmnopqrstuvwxyz
1
1 27```

### 输出

```
Yes```

## 样例 #3

### 输入

```
yzyyyzyzyyyz
8
1 6
7 12
1 12
6 11
1 1
1 3
4 9
3 8```

### 输出

```
Yes
Yes
Yes
Yes
No
No
No
No```

# 题解

## 作者：juruo999 (赞：12)

# AT2318 Robot and String

[传送门](https://www.luogu.com.cn/problem/AT2318)  考点：倍增 & DP

题解较详细，适合新手阅读

## 确定递推式

首先考虑将**以某个端点作为左端点的子串**变换为空

为了方便，将以 $ i $ 为左端点，可以变换为空的最小子串右端点的**后一位**记为 $ t_{i,26} $

 _P.S._  选择后一位仅是为了实现方便，字符串下标从 $ 1 $ 开始，长度为 $ n $

既然只有 ```zz``` 可以变换为空，我们就把以 $ i $ 为左端点，可以变换为 ```z``` 的最小子串右端点的后一位记为 $ t_{i,25} $

以此类推，我们将以 $ i $ 为左端点，可以变换为第 $ j $ 个字母的最小子串右端点的后一位记为 $ t_{i,j} $ （```a``` 为第 $ 0 $ 个字母 ）

如何求出 $ t_{i,j} $ 的值呢？我们可以得到下列递推式：

$$
t_{i,j}=\left\{
\begin{aligned}
i+1 & & j=s_i \\
t_{t_{i,j-1},j-1} & & j>s_i \\
t_{t_{i,26},j} & & j<s_i
\end{aligned}
\right.
$$

其中 $ s_i $ 表示输入字符串的第 $ i $ 位字母的编号，$ i $ 从 $ n $ 到 $ 1 $ 遍历

这个式子中，第一行是初始条件，第二行表示 $ j $ 从两个可以变为 $ j-1 $ 的子串**合并而来**，第三行表示可以先消除以 $ i $ 开头的一段子串，再从该子串右端点的**后一位**开始消除为 $ j $

## 确定边界条件

因为我们取了目标子串的后一位，所以子串的最后一定要有一个占位符（编号 $ n+1 $），为了方便，我们再规定占位符的后一位是结束符（$ n+2 $），并把 $ t_{n+1,x} $ 和 $ t_{n+2,x} $ 设为 $ n+2 $

## DP核心代码

```cpp
for(int i=1;i<=n+2;i++){
	for(int j=0;j<=26;j++){
		t[i][j]=n+2;		// 边界
	}
}

for(int i=n;i>=1;i--){			// 下标从 1 开始
	int nw=s[i]-'a';
	t[i][nw]=i+1;
	for(int j=nw+1;j<=26;j++){
		t[i][j]=t[t[i][j-1]][j-1];
	}
	for(int j=0;j<nw;j++){
		t[i][j]=t[t[i][26]][j];
	}
}
```

只要沿着 $ t_{x,26} $ 一直跳转即可

```cpp
while(q--){
	int l,r;
	scanf("%d%d",&l,&r);
	r++;
	while(1){
		if(t[l][26]<=r){
			l=t[l][26];
		}
	}
	if(l==r){
		puts("Yes");
	}else{
		puts("No");
	}
}
```


## 倍增

然鹅还没完……

这样会TLE吧？

我们可以倍增处理以 $ i $ 为左端点第 $ 2^j $ 短的子串，记为 $ f_{i,j} $ 。求得递推式 $ f_{i,j}=f_{f_{i,j-1},j-1} $

起始条件为 $ f_{i,0}=t_{i,26} $

跳转时，直接从大往小试即可。

## 100Pts Code

~~~cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

char s[500005];
int n,q;
int t[500005][31],f[500005][31];

int main(){
	
	scanf("%s%d",s+1,&q);
	n=strlen(s+1);
	
	for(int i=1;i<=n+2;i++){
		for(int j=0;j<=26;j++){
			t[i][j]=n+2;		// 边界
			f[i][j]=n+2;
		}
	}
	
	for(int i=n;i>=1;i--){		// DP
		int nw=s[i]-'a';
		t[i][nw]=i+1;
		for(int j=nw+1;j<=26;j++){
			t[i][j]=t[t[i][j-1]][j-1];
		}
		for(int j=0;j<nw;j++){
			t[i][j]=t[t[i][26]][j];
		}
	}
	
	for(int i=1;i<=n;i++){				// 倍增预处理
		f[i][0]=t[i][26];
	}
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
	
	while(q--){
		int l,r;
		scanf("%d%d",&l,&r);
		r++;
		for(int j=20;j>=0;j--){			// 倍增跳转
			if(f[l][j]<=r){
				l=f[l][j];
			}
		}
		if(l==r){
			puts("Yes");
		}else{
			puts("No");
		}
	}
	
	return 0;
}

~~~



---

## 作者：鱼跃于渊 (赞：3)

一道神仙 dp 题。  

## 做法

令 $\texttt{a}\to 0,\texttt{b}\to 1\ldots \texttt{z}\to 25,26$ 为空。  
我们设 $f_{i,j}$ 为一个最小的 $k$，使得 $[i,k-1]$ 内的字符串可以变换成状态 $j$。  
则转移方程如下所示：  

$$ f_{i,j}=\begin{cases} 
i+1 &\text{if } j=s_i\\
f_{f_{i,j-1},j-1} &\text{if }j>s_i\\
f_{f_{i,26},j} &\text{if }j<s_i
\end{cases}$$

如果 $j=s_i$，显然 $f_{i,j}=i+1$；如果 $j>s_i$，只要把两段可以变换成 $j-1$ 的区间拼起来就可以把整个区间变换成 $j$；如果 $j<s_i$，只要把一段可以变换为空的区间和一段可以变化为 $j$ 的区间拼起来即可。  
对于一次查询操作，我们不断地跳 $f_{l,26}$，看最终是否能够跳到 $r+1$。  
但是这样是 $O(n^2)$ 的，太慢了。  
于是我们可以想到倍增优化，设 $g_{i,j}$ 为从 $j$ 开始跳 $2^i$ 步会跳到的位置。  
于是就可以做到单次查询 $O(\log n)$ 了，可以通过。  

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
#define tr(x) ((x)-'a')
const int N=5e5+5,S=26;
char s[N];
int n,m,lim,t[N][S+5],f[S+5][N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>(s+1)>>m;n=strlen(s+1);lim=__lg(n);
	per(i,1,n+2) per(j,0,S) t[i][j]=f[j][i]=n+2;
	rep(i,n,1){
		t[i][tr(s[i])]=i+1;
		per(j,tr(s[i])+1,S) t[i][j]=t[t[i][j-1]][j-1];
		per(j,0,tr(s[i])-1) t[i][j]=t[t[i][S]][j];
	}
	per(i,1,n) f[0][i]=t[i][S];
	per(i,1,lim) per(j,1,n)
		f[i][j]=f[i-1][f[i-1][j]];
	for(int i=1,l,r;i<=m;i++){
		cin>>l>>r;r++;
		rep(j,lim,0) if(f[j][l]<=r) l=f[j][l];
		cout<<(l==r?"Yes\n":"No\n");
	}
	return 0;
}
```

---

## 作者：徐伟航 (赞：3)

楼上的大佬已经写的很好了，但~~本蒟蒻刚看的时候还是有些疑问~~ ,在此想发出来帮助可能会和我有相同疑问的人(~~(!蒟蒻) 可忽略~~)。

按照题意，假定该字串是可以变为空串的，我们的操作过程应该是从任意字母  $ X $ **单向地** 向后推进直到最终 $ ZZ $ 后的空串。 

观察到 $ s $ 串的长度，由于我们需要维护**较大的状态空间，线性递推会 $ TLE $**，因此我们想到使用倍增。

对于以下这个例子：

------------
```cpp
S = xxyz yyz = zz zz = 空
```
------------

容易发现合法结果是由**若干个可变成空的子串**合成，而我们在研究完前一个小子串后，**需要的元素是该小子串的后一位**。因此我们开一个数组 $ dp[ i ][ j ] $ ,其含义为**从 $ i $ 开始可变为第 $ j $ 个字母的子串的后一位为 $ dp[ i ][ j ] $**。

我们在转换时 $ a $ 对应的是 $ 0 $，索性**用 $ 0 $ ~ $ 25 $ 代表 $ a $ ~ $ z $** ，空格记为 $ 26 $。

所以 $ dp[ i ][ 26 ] $ 就代表上一个可处理为空的小子串的后一位，以便我们对下一小串进行操作。

~~代码是按照楼上大佬的思路写的，其中包含我的个人理解~~。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
#define sf scanf

char s[maxn];
int dp[maxn][30], f[maxn][30], len;

inline void pre_work()
{
	for(int i = 1; i <= len + 2; i++)
	{//处理到 len 长度后两位（一位是第 len 位的后一位）
		for(int j = 0; j <= 26; j++)
		{
			dp[i][j] = f[i][j] = len + 2;
		}
	}
	for(int i = len; i >= 1; i--)
	{	//此处反向遍历！！
		int pos = s[i] - 'a';
		dp[i][pos] = i + 1;
		//以下两个循环分别从 pos + 1 ~ 26（空格）、0 ~ pos - 1
		for(int j = pos + 1; j <= 26; j++)
		{//字母 j 向后处理直至空格
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
		}
		for(int j = 0; j < pos; j++)
		{//承接前面的
			dp[i][j] = dp[dp[i][26]][j];
		}
	}
	for(int i = 1; i <= len; i++)f[i][0] = dp[i][26];
	//f 的边界处理
	for(int j = 1; (1 << j) <= len; j++)
	{//倍增的体现，快速遍历数据！！
		for(int i = 1; i <= len; i++)
		{
			f[i][j] = f[f[i][j - 1]][j - 1];
		}
	}
	return;
}

int main()
{
	int q;
	sf("%s%d", s + 1, &q);//使 s 的起始下标为 1
	len = strlen(s + 1);
	pre_work();
	while(q--)
	{
		int l,r;
		sf("%d%d", &l, &r);
		r++;	//呼应dp数组
		for(int j = 26; j >= 0; j--)
		{
			if(f[l][j] <= r)l = f[l][j];
		}
		if(l == r)puts("Yes");
		else puts("No");
	} 
	return 0;
}
```


---

## 作者：Inui_Sana (赞：1)

其实是简单题。

令 $a\to 0,b\to 1,\cdots,z\to25$，$26$ 表示已经消掉。考虑设 $f_{i,j}$ 为一个最小的 $p$ 使得 $[l,p-1]$ 内的数可以合成一个 $j$。则 $f_{i,j}=f_{f_{i,j-1},j-1}$。同时注意到可能有 `azza` 这样，两个 `a` 跨过中间删掉的 `zz` 合并，于是还有 $f_{i,j}=f_{f_{i,26},j}$。

然后发现，若最后区间全部删完，则可以表示为从 $l$ 开始，跳若干次 $f_{i,26}$ 到 $r$。跳的次数很多所以不能暴力跳，于是类似地考虑倍增，设 $g_{i,j}$ 表示从 $i$ 开始跳 $2^j$ 步会到哪里。简单维护一下即可。

code：

```cpp
int n,m,f[N][31],g[N][23];
char s[N];
void Yorushika(){
	scanf("%s",s+1),n=strlen(s+1);
	drep(i,n,1){
		f[i][s[i]-'a']=i+1;
		rep(j,s[i]-'a'+1,26){
			f[i][j]=f[f[i][j-1]][j-1];
		}
		g[i][0]=f[i][26];
		rep(j,1,20){
			g[i][j]=g[g[i][j-1]][j-1];
		}
		rep(j,0,s[i]-'a'-1){
			f[i][j]=f[g[i][0]][j];
		}
	}
	read(m);
	while(m--){
		int l,r;read(l,r);
		drep(i,20,0){
			if(g[l][i]&&g[l][i]<=r+1){
				l=g[l][i];
			}
		}
		if(l==r+1){
			puts("Yes");
		}else{
			puts("No");
		}
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：Filberte (赞：0)

把小写字母与 $0\sim25$ 这些数一一对应，$a$ 对应 $1$，$b$ 对应 $2$，以此类推。

令 $f_{i,j}$ 表示从第 $i$ 个位置开始，进行变换操作，**最早**在 $f_{i,j} - 1$ 这个位置时，只剩下 $j$ 这个字母。其中 $j = 26$ 时，表示这一段区间没有任何字母。

对于第 $i$ 位，有 $f_{i,s_i} = i + 1$，考虑其他 $j \not= s_i$ 如何转移。合并的过程只会产生越来越大的字母，最终消失。当 $j > s_i$ 时，可以经过一系列合并得到比当前字母 $s_i$ 大的字母  $j$，有  $f_{i,j} = f_{f_{i,j - 1},j - 1}$；当 $j < s_i$ 时，想处理掉 $s_i$，只能是一系列变换后变成了空串，然后再进行变换产生单个字母 $j$，有 $f_{i,j} = f_{f_{i,26},j}$。因为 $\forall j > s_i$，$f_{i,j}$ 的计算都基于 $f_{i,j - 1}$，而 $\forall j < s_i$ 都需要基于 $f_{i,26}$，所以对于同一个 $i$ 而言，应当先从小到大计算 $j\in[s_i + 1, 26]$ 的部分，再计算 $j\in[1,s_i - 1]$ 的部分。

此时对于单次询问，令 $u = l$，暴力跳 $u = f_{u,26}$，相当于不断删去能变成空串的一段，最后判断 $u$ 是否与 $r + 1 $ 相等（注意定义）即可。但这样最坏复杂度是 $O(n)$，无法通过此题，看到这种往后跳的操作，套路化的想到倍增优化，优化后的复杂度是 $O(\log n)$，总复杂度 $O(q \log n)$，可以通过此题。

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 100;
int n, q;
char s[N];
int f[N][30], dp[N][21];
int main(){
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for(int i = 1;i <= n + 2;i++){
        for(int j = 0;j < 30;j++) f[i][j] = n + 2;
        for(int j = 0;j < 20;j++) dp[i][j] = n + 2;
    }
    for(int i = n;i >= 1;i--){
        int c = s[i] - 'a';
        f[i][c] = i + 1;
        for(int j = c + 1;j <= 26;j++)
            f[i][j] = f[f[i][j - 1]][j - 1];
        for(int j = 0;j < c;j++)
            f[i][j] = f[f[i][26]][j];
        
    }
    for(int i = 1;i <= n;i++) dp[i][0] = f[i][26];
    for(int j = 1;j <= 20;j++)
        for(int i = 1;i <= n;i++)
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
    scanf("%d",&q);while(q--){
        int l, r, cur;
        scanf("%d%d",&l,&r);
        cur = l;
        for(int j = 20;j >= 0;j--)
            if(dp[cur][j] <= r + 1) cur = dp[cur][j];
        if(cur == r + 1) puts("Yes");
        else puts("No");
    }
    return 0;
}
```

---

## 作者：Kreado (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_mujin_pc_2017_c)。

## 思路

对于每个 $i$，不妨求出最小的 $j$ 满足子串 $[i,j]$ 能被消成空串。

定义 $t_{i,j}$ 表示以 $i$ 为左端点，最小右端点的 $k$ 使得区间 $[i,k)$ 经过操作后得到字符 $j$，同理定义 $t_{i,27}$ 表示以 $i$ 为左端点，最小的 $k$ 使得区间 $[i,k)$ 能被消完。

显然有转移 

$$
t_{i,j}=\begin{cases}
i+1&(s_i=j)\\
t_{t_{i,j-1},j-1}&(s_i<j)\\
t_{t_{i,27},j}&(s_i>j)
\end{cases}
$$

查询我们每次**倍增跳**即可。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=5e5+7,inf=1e9;
int t[Maxn][28],f[Maxn][20];
char S[Maxn];
int n,Q;

int main(){
    scanf("%s",S+1);
    n=strlen(S+1);scanf("%d",&Q);
    for(int i=1;i<=n+2;i++) 
        for(int j=0;j<=27;j++)
            t[i][j]=n+2;
    for(int i=n;i;i--){
        int num=S[i]-'a'+1;
        t[i][num]=i+1;
        for(int j=num+1;j<=27;j++) t[i][j]=t[t[i][j-1]][j-1];
        for(int j=1;j<num;j++) t[i][j]=t[t[i][27]][j];
    }

    for(int i=1;i<=n;i++) f[i][0]=t[i][27];
    for(int i=1;i<=19;i++)
        for(int j=1;j<=n;j++)
            f[j][i]=f[f[j][i-1]][i-1];
    while(Q--){
        int l,r;
        scanf("%d%d",&l,&r);
        for(int j=19;~j;j--) if(f[l][j] and f[l][j]<=r+1) l=f[l][j];
        if(l!=r+1) cout<<"No\n";
        else cout<<"Yes\n"; 
    }
    system("pause");

    return 0;
}
```

---

