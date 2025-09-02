# [ABC329E] Stamp

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc329/tasks/abc329_e

英大文字からなる長さ $ N $ の文字列 $ S $ と、英大文字からなる長さ $ M\ (\leq\ N) $ の文字列 $ T $ が与えられます。

`#` のみからなる長さ $ N $ の文字列 $ X $ があります。 以下の操作を好きな回数行うことで、$ X $ を $ S $ に一致させることができるか判定してください。

- $ X $ の中から連続する $ M $ 文字を選び、$ T $ で置き換える。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ M\ \leq\ \min(N, $ $ 5 $$ ) $
- $ S $ は英大文字からなる長さ $ N $ の文字列
- $ T $ は英大文字からなる長さ $ M $ の文字列

### Sample Explanation 1

以下、$ X $ の $ l $ 文字目から $ r $ 文字目までの部分を $ X[l:r] $ と表記します。 次のように操作を行うことで、$ X $ を $ S $ に一致させることができます。 1. $ X[3:5] $ を $ T $ で置き換える。$ X= $ `##ABC##` になる。 2. $ X[1:3] $ を $ T $ で置き換える。$ X= $ `ABCBC##` になる。 3. $ X[5:7] $ を $ T $ で置き換える。$ X= $ `ABCBABC` になる。

### Sample Explanation 2

どのように操作を行っても、$ X $ を $ S $ に一致させることはできません。

## 样例 #1

### 输入

```
7 3
ABCBABC
ABC```

### 输出

```
Yes```

## 样例 #2

### 输入

```
7 3
ABBCABC
ABC```

### 输出

```
No```

## 样例 #3

### 输入

```
12 2
XYXXYXXYYYXY
XY```

### 输出

```
Yes```

# 题解

## 作者：hjqhs (赞：15)

砍掉 Ex 后第一次切六题，留念。  
考虑 dp。设 $f_{i,j}$ 为 $S$ 前 $i$ 位和 $T$ 前 $j$ 位能否匹配。  
如果 $s_i=t_j$，分讨 $T$ 是接在后面还是新起一段。接在后面为 $f_{i-1,j-1}$，新起一段则是 $f_{i-1,m}$。  
如果 $s_i=t_1$，则只能是新起一段。
```cpp
// Problem: E - Stamp
// Contest: AtCoder - Ｓｋｙ Inc, Programming Contest 2023（AtCoder Beginner Contest 329）
// URL: https://atcoder.jp/contests/abc329/tasks/abc329_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Created Time: 2023-11-19 11:35:41
// Author: hjqhs
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

// #define int long long
#define rep(i, a, b) for (int i = a; i <= b; ++ i)
#define per(i, a, b) for (int i = a; i >= b; -- i)

using namespace std;

const int N = 200005;
const int M = 11;
const int INF = 0x3f3f3f3f;

int n, m, f[N][M];
string s, t;

void solve () {
	cin >> n >> m >> s >> t;
	s = ' ' + s, t = ' ' + t;
	
	f[0][0] = 1;
	
	rep (i, 1, n) {
		rep (j, 1, m) {
			if (s[i] == t[j]) f[i][j] |= f[i - 1][j - 1] | f[i - 1][m];
			if (s[i] == t[1]) f[i][1] |= f[i - 1][j];
		}
	}
	
	cout << (f[n][m] ? "Yes" : "No");
	
	return;
}

signed main () {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	solve();
	
	return 0;
}
```

---

## 作者：FL_sleake (赞：11)

### 题意简述

给定两个整数 $n,m$，两个长度分别为 $n,m$ 的字符串 $s,t$。现在你有一个长度为 $n$，且由 ```#``` 构成的字符串 $x$，你可以做以下操作任意多次：

选择 $x$ 中的连续 $m$ 个字符，替换为 $t$。

确定最终能否使 $s$ 和 $x$ 完全一样。

### 解题思路

非常巧妙，涨芝士了。

考虑反过来思考，每次从 $s$ 中选一些和 $t$ 一样的字符，让它们变成 ```#```。其实相当于一个撕贴纸的过程，$t$ 就是贴纸。

注意此时我们认定 ```#``` 相当于任意字符。即，若 $s$ 的一个子串为 ```#BC```，$t$ 为 ```ABC```，则可以将 $s$ 变为 ```###```。因为在贴贴纸的过程中会有覆盖掉的部分，而我们不知道。

实现可以用搜索。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
string s,t;
bool check(int st){
	bool ck=0;
	for(int i=st,j=1;j<=m;i++,j++){
		if(s[i]!='#'){
			if(s[i]!=t[j]) return 0;
			ck=1;
		}
        //注意如果s全部为#就跳过，否则会TLE
	}
	if(ck) for(int i=st;i<=st+m-1;i++) s[i]='#';
	return ck;
}
void dfs(int l){
	//往后m位
	for(int i=l;i<=min(n-m+1,l+m);i++) if(check(i)) dfs(i);
   	//往前m位
	for(int i=l;i>=max(1ll,l-m);i--) if(check(i)) dfs(i);
}
signed main(){
	cin>>n>>m>>s>>t;
	s=" "+s,t=" "+t;
	for(int i=1;i<=n-m+1;i++) if(check(i)) dfs(i);
	for(int i=1;i<=n;i++){
		if(s[i]!='#'){
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}
```

---

## 作者：Genius_Star (赞：6)

### 题意：

给定两个字符串 $A$ 和 $B$，可以将 $B$ 在白板上进行任意次拓印，每次拓印会将上一次同一位置的拓印覆盖掉。

问是否可以进行若干次操作，使得白板上的字符串和 $A$ 相同。

### 思路：

因为 $M$ 的长度很小，只有 $5$，考虑动态规划算法。

定义 $dp_{i,j}$ 表示第 $i$ 个位置**最终**被第 $B_j$ 给拓印。

若 $A_i=B_j$，那么很容易想到 $2$ 种情况：

- $i$ 位置被重新覆盖，且 $i-1$ 并没有被重新覆盖，有两种可能：

    - $i-1$ 位置被 $b_{j-1}$ 拓印。（即顺次拓印）
    
    - $i-1$ 位置被 $b_m$ 拓印。（这个就是说，将 $b_j$ 拓印上去后，$b_j$ 前面可能会改变，但是只要在 $i-1$ 这个位置是 $b_m$ 的话，那么久可以在 $i-1$ 出再次拓印，可能说起来有些绕）
    
- 当 $j=1$ 时，前面的 $i-1$ 位置可以被任意的字符拓印。

则状态转移方程为：

$$dp_{i,j}=\begin{cases}dp_{i-1,j-1}|dp_{i-1,m}&A_i=B_j\\dp_{i,j}|dp_{i-1,k}(1 \le k \le m)&A_i=B_j,j=1\end{cases}$$

时间复杂度为：$O(N \times M)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200200,M=10;
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
ll n,m;
char s1[N],s2[M];
bool dp[N][M];
int main(){
	n=read(),m=read();
	cin.getline(s1+1,N);
	cin.getline(s2+1,N);
	dp[1][1]=(s1[1]==s2[1]);
    for(int i=2;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s1[i]!=s2[j]) 
		      continue;
            dp[i][j]=dp[i-1][j-1]|dp[i-1][m];
            if(j==1){
			    for(int k=1;k<=m;k++)
                  dp[i][j]|=dp[i-1][k];
			}
        }
    }
    puts(dp[n][m]?"Yes":"No");
	return 0;
}
```


---

## 作者：FReQuenter (赞：3)

转化一下，题目就是要求每次把 $S$ 中一个每一位等于 $T_i$ 或者 `#` 的子串全部赋值成 `#`。问最后能不能把 $S$ 全部变成 `#`。

转化做完就简单了。我们记录下所有符合这个条件的点，每次更新它们，更新之后把新的符合条件的点继续更新直到无法更新的时候就可以检查 $S$ 是否全是 `#` 了。

复杂度 $O(nm^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
bool vis[200005];
int n,m;
queue<int> q;
void check(int pos){
	if(!vis[pos]){
		bool flag=1;
		for(int j=0;j<m;j++) flag&=(s[pos+j]==t[j]||s[pos+j]=='#');
		if(flag) vis[pos]=1,q.push(pos);
	}
}
signed main(){
	cin>>n>>m>>s>>t;
	for(int i=0;i+m-1<n;i++) check(i);
	while(!q.empty()){
		int fr=q.front();
		q.pop();
		for(int j=0;j<m;j++) s[fr+j]='#';
		for(int j=max(fr-m+1,0);j<=min(fr+m-1,n-m);j++) check(j);
	}
	cout<<(s==string(n,'#')?"Yes":"No");
} 
```

---

## 作者：Expert_Dream (赞：3)

### 题目翻译 
给你两个字符串：$S$ 由大写英文字母组成，长度为 $N$；$T$ 也由大写英文字母组成，长度为 $M$，小于 $N$。有一个长度为 $N$ 的字符串 $X$，它只由 `#` 字符组成。请判断是否有可能通过执行以下任意次数的操作使 $X$ 与 $S$ 匹配：在 $X$ 中选择 $M$ 个连续字符，并用 $T$ 替换它们。

## 分析

问题一：我们什么时候能够替换？

按照样例来解释：

```
7 3
ABCBABC
ABC
```

可以看出，样例是放了三个 $T$。

在考虑 $S$ 的其他情况。如果 $S$ 为 `ABBC` 那么就是不可以的，因为无法用两个 $T$ 来组成，因为两个字符串都会失去前缀和后缀。

在自己列举几种后发现：

两个 $T$，前者没有部分后缀或者后者没有部分前缀是可以相匹配的，但是呢，两个并存是不可以的。

问题二：怎么做呢？

我们可以使用 DP 的方式记录状态 $dp_{i,j}$ 代表到第 $i$ 个字符，此时位置是 $T$ 中的下标几，然后表示能不能到达。

于是我们可以得到转移：当 $dp_{i-1,j-1}$ 成立时，$dp_{i,j}$ 和 $dp_{i,1}$ 都成立，如果 $dp_{i-1,m}$ 成立，那么对于所有的 $j$，都有 $dp_{i,j}$ 成立。

然后再判断一下两个字符串是否相等，如果不相等，把他换回不成立。

AC code：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define fir first
#define se second
#define endl '\n'
#define debug puts("AK IOI")
using namespace std;
const int N = 2e5+5;
int n,m;
string s,t;
bool dp[N][10];

int main(){
	cin >> n >> m;
	cin >> s >> t;
	s=' '+s;
	t=' '+t;
	if(s[1] == t[1])dp[1][1]=1;
	
	for(int i = 1;i <= n;i++){
		for(int j = 2;j <= m;j++)
			if(dp[i-1][j-1]) dp[i][j]=dp[i][1]=1;
		if(dp[i-1][m]) for(int j = 1;j <= m;j++)dp[i][j]=1;
		
		bool ac=0;
		for(int k = 1;k <= m;k++){
			if(t[k]==s[i] && dp[i][k]) ac=1;
			else if(dp[i][k]) dp[i][k] = 0;
		}if(ac==0){
			cout<<"No";	
			return 0;
		}
	}if(dp[n][m])cout<<"Yes";
	else cout<<"No";
	return 0;
}
```

---

## 作者：Register_int (赞：3)

先来看看样例：

$$\color{red}\verb!ABC!\color{green}\verb!B!\color{blue}\verb!ABC!$$

可以大胆猜想，一个合法的邮票串，实际上是由几个邮票的子串拼接起来的。于是考虑 $dp_i$ 表示前 $i$ 个字符组成的前缀是否合法，枚举邮票子串转移。但是样例二打了我们的脸：

$$\color{red}\verb!AB!\color{green}\verb!BC!\color{blue}\verb!ABC!$$

这个串并不能被表示，因为如果要覆盖出这种形状，红色部分的尾部要被绿色盖掉，绿色部分的头部又要被红色盖掉。为了防止这种情况，我们加入一些限制：

- 如果这次加入的子串是邮票的前缀，那么直接转移。
- 如果不是，则仅在上次加入的子串为后缀时转移。

这样就解决了两张邮票相互覆盖的问题。设 $dp_{i,0/1}$ 表示前 $i$ 个字符是否能被覆盖且上一个子串是/不是邮票的后缀，答案即为 $dp_{n,1}$。由于 $m$ 较小，怎么实现都行，这里用的是 $O(nm^2)$ 的做法。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int n, m; bool dp[MAXN][10];

char s[MAXN], t[10];

int main() {
    scanf("%d%d%s%s", &n, &m, s + 1, t + 1), dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < m; j++) {
    		for (int k = 1; i + k <= n && j + k <= m; k++) {
    			if (s[i + k] != t[j + k]) break;
    			if (!j) dp[i + k][j + k == m] |= dp[i][0] | dp[i][1];
    			else dp[i + k][j + k == m] |= dp[i][1];
			}
		}
	}
	puts(dp[n][1] ? "Yes" : "No");
}
```

---

## 作者：yhx0322 (赞：3)

update on $2023.12.13$：更改了描述模糊的内容
## Description
有两个字符串 $S$ 和 $T$，还有一个长度为 $N$ 的仅由字符 `#` 构成的字符串 $X$。

现在可以执行若干次操作，每次可以选择字符串 $X$ 中连续的 $M$ 段覆盖为 $T$。

求：是否能通过若干次操作，使得 $X$ 和 $S$ 相等。
## Solution
考虑一个覆盖时间的序列（钦定每一次覆盖记录在其右端点上），发现对于当前点 $p$：

只有 $[p,p+m-1]$ 这一段区间会影响该点的取值，考虑爆搜，对于当前位置 $p$，只需要考虑 $[p-m+1,p]$ 这一段长度为 $m$ 的时间序列，枚举当前一个新的位置的相对时间排名，确定下来 $[p-m+1,p]$ 的相对时间顺序，于是位置 $p-m+1$ 的值会被 $[p-m+1,p]$ 中时间值最大的点覆盖掉，再判断 $p-m+1$ 的值是否与 $S$ 串对应位置相等即可。


优化点，即当前状态包含当前位置 $p$，和前面的时间序列 $st$，若之前已经走到过 `<p,st>` 这样一个状态，那当前就没必要继续往下搜了。
## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

unordered_map<int, int> mp;
int n, m;

int gethash(int now, int stat[5]) {
    int hsh = now;
    for (int i = 0; i < m - 1; i++) hsh = hsh * m + stat[i];
    return hsh;
}

char s[200055];
char t[55];

bool search(int now, int stat[5]) {
    int hsh = gethash(now, stat);
    if (mp.find(hsh) != mp.end()) return false;
    mp[hsh] = 1;
    if (now == n + 1) {
        char x[6];
        for (int j = 1; j < m; j++) {
            for (int k = 0; k < m - 1; k++) {
                if (stat[k] == j) {
                    for (int l = 2; l <= m - k; l++) {
                        x[l] = t[l + k];
                    }
                }
            }
        }
        for (int i = 2; i <= m; i++) if (s[n + i - m] != x[i]) return false;
        return true;
    }
    for (int i = 1; i <= m; i++) {
        int new_stat[5];
        new_stat[0] = i;
        for (int j = 1; j < m; j++) {
            new_stat[j] = stat[j - 1];
            if (stat[j - 1] >= i) ++new_stat[j];
        }
        bool flag = true;
        for (int j = 0; j < m; j++) {
            if (new_stat[j] == m) {
                if (s[now - m + 1] != t[j + 1]) flag = false;
            }
        }
        if (!flag) continue;
        for (int j = 0; j < m - 1; j++) {
            if (new_stat[j] > new_stat[m - 1]) --new_stat[j];
        }
        if (search(now + 1, new_stat)) return true;
    }
    return false;
}

int stat[5];
int main() {
    cin >> n >> m;
    scanf("%s%s", s + 1, t + 1);
    if (s[1] != t[1]) {
        puts("No");
        return 0;
    }
    for (int i = 0; i < 5; i++) stat[i] = m - i - 1;
    if (search(m + 1, stat)) {
        printf("Yes");
        return 0;
    }
    printf("No");
    return 0;
}
```

---

## 作者：fcy20180201 (赞：2)

看其他大佬都用二三十行的 DP 过，但蒟蒻不会，只会暴力判断 QWQ。

## 题意
在一个长度为 $N$，初始为空的字符串 $X$ 上覆盖任意多次长度为 $M$ 的字符串 $T$，问最后是否能得到长度为 $N$ 的字符串 $S$。

## 思路
一开始一脸懵，但看到 $1 \le M \le \min(N,5)$ 时就······（你看出题人都把 $5$ 标红了）

我们能快速发现，覆盖到 $X$ 上的若干个 $T$ 若有用（即能被看见一些），只有四种情况：

- 整个都能在 $S$ 中都被看到；
- 左边被遮挡，只能看见右边的一部分；
- 右边被遮挡，只能看见左边的一部分；
- 两边都被遮挡，只能看见中间的一部分。

**由于每个 $T$ 长度相等，不可能出现“中间被覆盖，只能看到两边”的情况。**

因此我们先在 $S$ 中找到所有整个的 $T$，然后再考虑被遮挡的 $T$，即考虑整个的 $T$ 之间的区间。如果发现区间**最左边**有 $T$ 的**后缀**，则这是一段被**遮挡左边**的 $T$；如果发现区间**最右边**有 $T$ 的**前缀**，则这是一段被**遮挡右边**的 $T$。去掉这些前缀后缀之后，区间中间剩下的一定是**一段**被遮挡两边的 $T$。首先如果这一段长度大于 $M-2$，则不可能被同时遮挡两边；否则直接暴力判断这一段是否是 $T$ 的连续子串即可。时间复杂度 $O(NM)$，但常数很大 ，不过不影响。

### 细节

- 首先 $S$ 的最左边一定等于 $T$ 的最左边，因为只有一种覆盖它的方法；$S$ 的最右边同理等于 $T$ 的最右边。

- 一定要考虑最左边完整 $T$ 的左边区间和最右边完整 $T$ 的右边区间（见代码）。

- 刚才说去掉前缀后缀的一段长度一定小于等于 $N-2$，其实此处要特判 $M=1$。当 $M=1$ 时，$M-1=0$，即存在两个完整的 $T$ 之间只有一堆前缀后缀，但按照上面的思路会误判为不合法，因此要特判（见代码）。

## 又臭又长的代码
**提示：请勿 Ctrl+C 再 Ctrl+V。**

```cpp
int n,m,num,st[200005],en[200005];
char s[200005],t[200005];
int mian(){
	scanf("%d%d%s%s",&n,&m,s+1,t+1);
	if(s[1]!=t[1] || s[n]!=t[m]){//特判注意事项 1。
		puts("No");return 0;
	}
	st[++num]=0,en[num]=0;//注意事项 2，可以采用在两边加上虚拟的完整 T 的方式。
	for(int i=1;i<=n-m+1;i++){
		bool flag=true;
		for(int j=1;j<=m;j++)if(s[i+j-1]!=t[j]){flag=false;break;}
		if(flag)st[++num]=i,en[num]=i+m-1,i=en[num];//记录完整的 T。
	}
	st[++num]=n+1,en[num]=n+1;//注意事项 2，同上。
	for(int i=1;i<num;i++){
		while(en[i]<st[i+1]-1){
			bool flag2=false;
			for(int j=min(m,st[i+1]-en[i]-1);j>0;j--){//查找左边的后缀
				bool flag=true;
				for(int k=1;k<=j;k++)if(s[en[i]+k]!=t[k+(m-j)]){flag=false;break;}
				if(flag){en[i]+=j;flag2=true;break;}
			}
			for(int j=min(m,st[i+1]-en[i]-1);j>0;j--){//查找右边的前缀
				bool flag=true;
				for(int k=1;k<=j;k++)if(s[st[i+1]-j+k-1]!=t[k]){flag=false;break;}
				if(flag){st[i+1]-=j;flag2=true;break;}
			}
			if(!flag2)break;//如果前、后缀都处理完了就退出。
		}
		if(m>1 && st[i+1]-en[i]>=m || m==1 && st[i+1]-en[i]>1){//如果剩下的一段长度不符合，直接输出 No。注意事项 3。
			puts("No");
			return 0;
		}
		bool flag2=true;
		if(st[i+1]-en[i]>1){
			for(int j=1;j<=m-(st[i+1]-en[i])+1;j++){//暴力判断剩余部分是否是 T 的连续子串。
				bool flag=true;
				for(int k=en[i]+1;k<st[i+1];k++)if(s[k]!=t[k-en[i]-1+j]){flag=false;break;}
				if(flag){flag2=false;break;}
			}
			if(flag2){
				puts("No");
				return 0;
			}			
		}
	}
	puts("Yes");
   	return 0;
}
```

---

## 作者：aeiouaoeiu (赞：2)

看到 $m$ 非常小，考虑 dp。

设 $f_{i,j}$ 表示考虑到 $s_i$ 且 $s_i$ 与 $t_j$ 相等的可行性。

对于放进 $x$ 的字符串 $t=\overline{t_1t_2\ldots t_m}$，我们考虑它如何与它正前面的 $t'=\overline{t'_1t'_2\ldots t'_m}$ 连接。

* 直接连接：$\overline{t'_1t'_2\ldots t'_m~t_1t_2\ldots t_m}$。
  
* 左压右：$\overline{t'_1t'_2\ldots t'_m~t_xt_2\ldots t_m}(x>1)$。
  
* 右压左：$\overline{t'_1t'_2\ldots t'_x~t_1t_2\ldots t_m}(x<m)$。
  

不难发现 $t_1$ 可以与任意 $t'_i $ 连接，而对于 $x\neq1$，$t_x$ 只能与 $t'_m$ 连接。

再考虑到对于 $x\neq1$，$t_x$ 可以在 $t_{x-1}$ 之后，我们有如下转移方程：

$$
f_{i,j}=\begin{cases}    0 & s_i\neq t_j\\    f_{i-1,j-1}|f_{i-1,m} & s_i=t_j\land j\neq1 \\    f_{i-1,1}|f_{i-1,2}|\cdots|f_{i-1,m} & s_i=t_j\land j=1 \\\end{cases}
$$

其中 $|$ 表示或运算，答案为 $f_{n,m}$，在特判 $s_1\neq t_1$ 后可直接令 $f_{1,1}=1$。

时间复杂度 $\mathcal{O}(nm)$。

    #include<bits/stdc++.h>
    #define pb push_back
    #define pob pop_back
    #define mp make_pair
    #define Debug if(0)
    using namespace std;
    typedef long long ll;
    typedef long double db;
    const int maxn=200007,dx[4]={0,0,-1,1},dy[4]={-1,1,0,0};
    const ll inf=1300000007ll,p=998244353,hsp=993244853,hsb=1145141;
    const ll ee=1000000000000000007ll;
    ll n,m,f[maxn][7];
    string s,t;
    int main(void){
        //freopen("data.in","r",stdin);
        //freopen("data.out","w",stdout);
        ios::sync_with_stdio(0);
        cin.tie(0);
        ll T=1;
        //cin>>T;
        //init();
        for(int tcs=1;tcs<=T;tcs++){
            cin>>n>>m>>s>>t; s=" "+s,t=" "+t;
            if(s[1]!=t[1]){cout<<"No\n"; exit(0);}
            f[1][1]=1;
            for(ll i=2;i<=n;i++){
                for(int j=1;j<=min(i,m);j++){
                    if(s[i]!=t[j]) continue;
                    f[i][j]|=f[i-1][j-1]|f[i-1][m];
                    if(j==1) f[i][j]|=f[i-1][1]|f[i-1][2]|f[i-1][3]|f[i-1][4]|f[i-1][5];
                }
            }
            cout<<(f[n][m]?"Yes\n":"No\n");
        }
        return 0;
    }

---

## 作者：DerrickLo (赞：0)

可以考虑 `dp`。

使用 $dp_{i,j}$ 表示 第 $i$ 个字符使用 $T$ 串的第 $j$ 个字符填充是否可行，若 $j=0$，那么第 $i-1$ 位填什么字符都满足条件；若 $j\neq0$，则需要满足 $i$ 前的 $j-1$ 位都与 $T$ 的前 $j-1$ 位对应，或者如果有一位和 $T$ 的最后一位对应也是可以的。

复杂度 $O(nm)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,vis[200005],dp[200005][10],ans;
string s,t;
signed main(){
	cin>>n>>m>>s>>t;s=" "+s,t=" "+t;
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<min(i,m);j++){
			if(s[i]!=t[j+1])continue;
			dp[i][j]=1;
			if(j==0){
				int flag=0;
				for(int k=0;k<m;k++)flag|=dp[i-1][k];
				dp[i][j]&=flag;
			}
			else{
				for(int k=0;k<j;k++){
					if(dp[i-k-1][m-1])break;
					dp[i][j]&=(dp[i-k-1][j-k-1]);
				}
			}
		}
	}
	if(dp[n][m-1])cout<<"Yes";
	else cout<<"No";
}
```

---

## 作者：WhileTrueRP (赞：0)

# ABC 329 E - Stamp 题解

## 题目翻译

给定一个长度为 $N$ 的字符串 $S$ 和长度为 $M$ 的字符串 $T$，求在一个长度为 $N$ 的空字符串上添加若干个 $T$ 字符串，问是否可以变为 $S$ 字符串。

+ $1\leq N\leq2\times10^5$

+ $1\leq M\leq\min(N,5)$

## 题目分析

对于每次添加的字符串 $T$，可能会被其他字符串覆盖，但**一定是从前面或者后面开始覆盖的**，即一个字符串 $T$ 一定保留了中间的部分，而前后两部分被其它字符串覆盖。证明是显然的，因为每个字符串的长度都相等，当且仅当两个字符串完全重合时，才可能覆盖到中间部分，此时相当于只有一个字符串了。

我们不妨逆向思维，看原字符串 $S$ 是否可以通过**删去**若干个 $T$ 变为空字符串。

每个字符串只会在前面开始或者从后面开始被覆盖，我们便可以从**前后两个方向**开始查找每一部分是否可以被删去。

## 代码实现

时间复杂度为 $O(nm)$，关键代码如下：

```cpp
for(int i=0;i<n;i++){
	bool flag = true;
	for(int j=0;j<m;j++){
		if(s[i+j] == t[j] || s[i+j] == '#'){
			continue;
		}else{
			flag = false;
		}
	}
	if(flag){
		for(int j=0;j<m;j++){
			s[i+j] = '#';
		}
	}
}
```

**然后再倒叙枚举一遍**，最后判断字符串是否为空即可。

[完整代码]([Submission #47708059 - Ｓｋｙ Inc, Programming Contest 2023（AtCoder Beginner Contest 329）](https://atcoder.jp/contests/abc329/submissions/47708059))。

---

## 作者：Heavy_Data_Struct (赞：0)

## [AT 题面传送门](https://atcoder.jp/contests/abc329/tasks/abc329_e)

## [题面传送门](https://www.luogu.com.cn/problem/at_abc329_e)

## 题目大意
给定字符串 $S$ 和 $T$，求经过下列变换能否得到 $S$：

你有一个长度为 $N$ 的 “空字符串”。

每一次，你可以在任意位置**完整地**把 $T$ 复制到该位置，覆盖之前的字符。例如当前字符串为 `ABCABC`，$T$ 为 `ABC`，则可以把 $T$ 复制到位置 $2$，原字符串变为 `AABCBC`。

## 思路
可能有找规律的做法，不过我用的 dp。

显然的，我们可以把覆盖操作转化为“在之前字符串的下面复制”。

建立 $dp_{i,0}$ 表示 $T$ 的任意前缀出现在位置 $i$ 是否可能，用 $T^\prime$ 表示这个前缀，$|T^\prime|$ 表示它的大小，$\oplus$ 表示逻辑或，则有：
$$dp_{i,0}=dp_{i-|T^\prime|,0}\oplus dp_{i-|T^\prime|,1}\oplus dp_{i-|T^\prime|,2}$$

建立 $dp_{i,1}$ 表示 $T$ 的任意后缀出现在位置 $i$ 是否可能：
$$dp_{i,1}=\begin{cases}
dp_{i-|T^\prime|,1} & T^\prime \ne T\\
dp_{i-|T^\prime|,0}\oplus dp_{i-|T^\prime|,1}\oplus dp_{i-|T^\prime|,2} & T^\prime = T
\end{cases}$$

建立 $dp_{i,2}$ 表示 $T$ 的任意子串出现在位置 $i$ 是否可能：

$$dp_{i,2}=\begin{cases}
dp_{i-|T^\prime|,1} & T^\prime \ne T\\
dp_{i-|T^\prime|,0}\oplus dp_{i-|T^\prime|,1}\oplus dp_{i-|T^\prime|,2} & T^\prime = T
\end{cases}$$

答案就是 $dp_{N,0}\oplus dp_{N,1}\oplus dp_{N,2}$。

不过请注意，$T$ 中出现的位置为 $i$ 的字符，只会在 $\ge i$ 的位置出现，这个要特判。

## 代码

```cpp
#include<bits/stdc++.h>
#define HEAD 0
#define ENDING 1
#define SUBSTR 2
using namespace std;
int n, m;
string s, t;
vector<string>g;
bool dp[200005][3];
int main() {
    dp[0][1] = dp[0][0] = dp[0][2] = true;
    cin >> n >> m >> s >> t;
    for(int i = 0;i < t.size();i ++)
        for(int j = i; j < t.size();j ++)
            g.push_back(t.substr(i, j - i + 1));
    for(int i = 1;i <= s.size();i ++) {
        for(int x = 0;x < t.size();x ++) {
            string j = t.substr(x), k = t.substr(0, x + 1);
            if(j.size() <= i && s.substr(i - j.size(), j.size()) == j)
                    dp[i][ENDING]   |= dp[i - j.size()][ENDING] | (j == t && (dp[i - j.size()][HEAD] | dp[i - j.size()][SUBSTR]));
            if(k.size() <= i && s.substr(i - k.size(), k.size()) == k)
                    dp[i][HEAD]     |= dp[i - k.size()][HEAD] | dp[i - k.size()][ENDING] | dp[i - k.size()][SUBSTR];
            if(i < t.size())dp[i][ENDING] = false;
        }
        for(int f = 0;f < t.size();f ++)
            for(int e = f;e < t.size();e ++){
                string j = t.substr(f, e - f + 1);
                if(j.size() <= i && s.substr(i - j.size(), j.size()) == j && i > e)
                    dp[i][SUBSTR]       |= dp[i - j.size()][ENDING] | (j == t && (dp[i - j.size()][HEAD] | dp[i - j.size()][SUBSTR]));
            }//cout << dp[i][HEAD] << " " << dp[i][ENDING] << " " << dp[i][SUBSTR] << endl;
    }
    if(dp[n][ENDING])cout << "Yes";
    else cout << "No";
    return 0;
}
```

---

