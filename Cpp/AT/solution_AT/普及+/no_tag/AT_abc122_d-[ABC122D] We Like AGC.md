# [ABC122D] We Like AGC

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc122/tasks/abc122_d

整数 $ N $ が与えられます。次の条件を満たす長さ $ N $ の文字列の数を $ 10^9+7 $ で割った余りを求めてください。

- `A`, `C`, `G`, `T` 以外の文字を含まない。
- `AGC` を部分文字列として含まない。
- 隣接する $ 2 $ 文字の入れ替えを $ 1 $ 回行うことで上記の条件に違反させることはできない。

## 说明/提示

### 注記

文字列 $ T $ の部分文字列とは、$ T $ の先頭と末尾から $ 0 $ 文字以上を取り去って得られる文字列です。

例えば、`ATCODER` の部分文字列には `TCO`, `AT`, `CODER`, `ATCODER`, `` (空文字列) が含まれ、`AC` は含まれません。

### 制約

- $ 3\ \leq\ N\ \leq\ 100 $

### Sample Explanation 1

`A`, `C`, `G`, `T` 以外の文字を含まない長さ $ 3 $ の文字列は $ 4^3\ =\ 64 $ 通り存在し、そのうち `AGC`, `ACG`, `GAC` のみが条件に違反するため、答えは $ 64\ -\ 3\ =\ 61 $ 通りです。

### Sample Explanation 3

文字列の数を $ 10^9+7 $ で割った余りを出力することをお忘れなく。

## 样例 #1

### 输入

```
3```

### 输出

```
61```

## 样例 #2

### 输入

```
4```

### 输出

```
230```

## 样例 #3

### 输入

```
100```

### 输出

```
388130742```

# 题解

## 作者：hxhhxh (赞：5)

### 大意

求长度为n的，满足

- 只有字符`A`，`G`，`C`，`T`
- 没有子串`AGC` 
- 在单次操作（交换相邻两个字符）后仍然满足上述条件

的串的个数。

### 思路

考虑把第三个限制去掉。

不满足限制的字符串有：

- `AGC` ，违反第二条限制
- `ACG` ，交换`C`，`G`之后违反
- `GAC` ，交换`G`，`A`之后违反
- `AGGC` ，交换`G`，`A`之后违反
- `AGTC` ，交换`T`，`C`之后违反
- `ATGC` ，交换`T`，`A`之后违反

以及以它们为字串的字符串（这里不考虑违反第一条限制的字符串）。

我们使用 $ 5 $ 进制。用 $ 0 $ 表示` `，即没用字符；用 $ 1 $ 表示`A`，用 $ 2 $ 表示`G`，用 $ 3 $ 表示`C`，用 $ 4 $ 表示`T`，用长度为 $ 3 $ 的五进制数表示三个连续字符。

令 $ a = (\text{前面三个字符})_5 \times (10)_5 + (\text{当前选的字符})_5 $ ，则如果：

$$ a \begin{cases} \mod 125 & = & \begin{cases} 38 & (AGC) \\ 42 & (ACG) \\ 58 & (GAC) \end{cases} \\ & = & \begin{cases} 188 & (AGGC) \\ 198 & (AGTC) \\ 238 & (ATGC) \end{cases} \end{cases} $$ 

那么违反限制，不能选，否则都可以进行转移。

代码如下：

### 代码
```cpp
#include<bits/stdc++.h>
#define mod 1000000007 
int n,dp[123][1000],ans;
int main(){
	scanf("%d",&n),dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<125;j++){
			if(dp[i-1][j]){
				for(int k=j*5+1;k<=j*5+4;k++){
					if(!(k%125==38||k%125==42||k%125==58||k==188||k==198||k==238)){
						dp[i][k%125]=(dp[i][k%125]+dp[i-1][j])%mod;
                    }
                }
            }
        }
    }
	for(int i=0;i<125;i++) ans=(ans+dp[n][i])%mod;
	printf("%d",ans);
}
```

---

## 作者：igAC (赞：2)

# $\text{Describe}$

[洛谷 link](https://www.luogu.com.cn/problem/AT_abc122_d)

[ATlink](https://atcoder.jp/contests/abc122/tasks/abc122_d)

# $\text{Solution}$

对于这类计数问题，首先考虑 dp。

设 $f_{i,a,b,c}$ 表示长度为 $i$ 且最后三位分别为 $a,b,c$ 的字符串的个数。

状态有了，接下来考虑如何转移。

我们令 $check$ 表示是否合法。

$$
f_{i,a,b,c}=\sum_{check} f_{i-1,lst,a,b}
$$

$lst$ 为倒数第 $4$ 个字符。

那么何时 $check$ 才合法呢？

我们令 $b_{a,b,c}$ 表示字符 $a,b,c$ 所组成的字符串是否合法。

我们在原来枚举后三位的基础上再枚举第四位 $lst$。

那么

$$

check=b_{a,b,c} ~ \land ~ b_{a,c,b} ~ \land ~ b_{b,a,c} ~ \land ~ b_{lst,a,c}  \land ~ b_{lst,b,c}
$$

发现结论的过程需要读者自己手玩一下。

具体实现可作者的参考代码。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 505
#define Mod 1000000007
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,f[N][4][4][4],ans;
const char c[]={'A','C','G','T'};
bool check(int i,int j,int k){return !(c[i]=='A' && c[j]=='G' && c[k]=='C');}
int main(){
	n=read();
	for(int a=0;a<4;++a){
		for(int b=0;b<4;++b){
			for(int c=0;c<4;++c){
				if(check(a,b,c) && check(a,c,b) && check(b,a,c)){
					f[3][a][b][c]=1;
				}
			}
		}
	}
	for(int i=4;i<=n;++i){
		for(int a=0;a<4;++a){
			for(int b=0;b<4;++b){
				for(int c=0;c<4;++c){
					for(int x=0;x<4;++x){
						if(check(a,b,c) && check(a,c,b) && check(b,a,c) && check(x,a,c) && check(x,b,c)){
							f[i][a][b][c]=(f[i][a][b][c]+f[i-1][x][a][b])%Mod;
						}
					}
				}
			}
		}
	}
	for(int a=0;a<4;++a){
		for(int b=0;b<4;++b){
			for(int c=0;c<4;++c){
				ans=(ans+f[n][a][b][c])%Mod;
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：_Weslie_ (赞：1)

你说得对，但是我不喜欢 AGC。

## 思路

先考虑什么样的字符串是不能出现的。

不难发现，违反限制 $2$ 的有：

- `AGC`。

违反限制 $3$ 的有：

- `ACG`（交换 `C` 和 `G`）；
- `GAC`（交换 `G` 和 `A`）；
- `AG?C`（交换 `?` 和 `C`，其中 `?` 是 `A`、`C`、`G`、`T` 中任一个）；
- `A?GC`（交换 `A` 和 `?`）。

然后就可以 dp 了。

我们用 $0$ 代表 `A`，$1$ 代表 `G`，$2$ 代表 `C`，$3$ 代表 `T`。

设 $dp_{i,j,k,l}$ 表示现在前 $i-1$ 位的串已经覆盖好，最后三位分别是 $j$ 和 $k$ 和 $l$ 的方案数。

那么我们枚举第 $i$ 位 $p$。如果构成了上面的五种串，则不可行，反之就让 $dp_{i,k,l,p}$ 加上 $dp_{i-1,j,k,l}$，即这个状态可以从上一个状态转移来。

于是做完了。

## 代码

```
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int n,dp[105][4][4][4];
int ans;
int main(){
	scanf("%d",&n);
	if(n==1){
		printf("4");
		return 0;
	}
	if(n==2){
		printf("16");
		return 0;
	}
	if(n==3){
		printf("61");
		return 0;
	}
	//A0 G1 C2 T3
	dp[0][3][3][3]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				for(int l=0;l<4;l++){
					for(int p=0;p<4;p++){
						if(k==0&&l==1&&p==2)continue;//AGC
						if(k==0&&l==2&&p==1)continue;//ACG
						if(k==1&&l==0&&p==2)continue;//GAC
						if(j==0&&k==1&&p==2)continue;//AG-C
						if(j==0&&l==1&&p==2)continue;//A-GC 
						dp[i][k][l][p]=(dp[i-1][j][k][l]+dp[i][k][l][p])%mod;
					}
				}
			}
		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<=3;j++){
			for(int k=0;k<=3;k++){
				ans=(ans+dp[n][i][j][k])%mod;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：StayAlone (赞：1)

感觉比较板，思维含量低，实现难度也挺低的。

为了方便叙述：

`const string P = "ACGT";`

定义状态 $f_{l,i=0\sim3,j=0\sim3,k=0\sim3,p=0\sim3}$ 表示长度为 $l$ 的字符串，最后的四个字母分别是 $P_i,P_j,P_k,P_p$ 时的合法方案数。


既然 $1\leq N\leq 100$，那么我们就干脆写暴力一点，免得出现奇怪的细节。

写一个简单的函数判断一个字符串是否合法：

```cpp
#define rep1(i, l, r) for (int i = l; i <= int(r); ++i)

bool check(string s) {
	int len = s.size();
	rep1(i, 0, len - 2) {
		swap(s[i], s[i + 1]);
		if (~s.find("AGC")) return false;
		swap(s[i], s[i + 1]);
	} return !~s.find("AGC");
}
```

那么转移很简单。枚举一个 $s\in[0,3]$，那么 $f_{l,i,j,k,p}$ 可以从 $f_{l-1,s,i,j,k}$ 转移过来当且仅当：$P_s,P_i,P_j,P_k,P_p$ 顺次组成的字符串合法。

就完了。$n=3$ 的情况要特判，时间复杂度好像炸到了 $\mathcal O(ns^8),s=4$，即使是这样在这个数据范围下仍然非常松，而且这样写没有任何细节需要考虑，代码难度也几乎为 $0$。

[AC record](https://www.luogu.com.cn/record/110708170)

```cpp
int n; ll f[110][4][4][4][4]; const int mod = 1e9 + 7;
const string P = "ACGT";

il bool check(string s) {
	int len = s.size();
	rep1(i, 0, len - 2) {
		swap(s[i], s[i + 1]);
		if (~s.find("AGC")) return false;
		swap(s[i], s[i + 1]);
	} return !~s.find("AGC");
}

int main() {
	read(n);
	if (n == 3) return puts("61"), 0;
	rep1(i, 0, 3) rep1(j, 0, 3) rep1(k, 0, 3) rep1(p, 0, 3) {
		char v = P[i], v2 = P[j], v3 = P[k], v4 = P[p];
		string now; now += v; now += v2; now += v3; now += v4;
		if (check(now)) f[4][i][j][k][p] = 1;
	}
	rep1(l, 5, n) rep1(i, 0, 3) rep1(j, 0, 3) rep1(k, 0, 3) rep1(p, 0, 3) {
		string t; t += P[i]; t += P[j]; t += P[k]; t += P[p];
		if (!check(t)) continue;
		rep1(s, 0, 3) {
			string now = P[s] + t;
			if (check(now)) f[l][i][j][k][p] += f[l - 1][s][i][j][k];
		} f[l][i][j][k][p] %= mod;
	} ll ans = 0;
	rep1(i, 0, 3) rep1(j, 0, 3) rep1(k, 0, 3) rep1(p, 0, 3) {
		(ans += f[n][i][j][k][p]) %= mod;
	} printf("%lld\n", ans);
	rout;
}
```

---

## 作者：Vincent615 (赞：0)

# AT_abc122_d [ABC122D] We Like AGC 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc122_d)

## 分析题目

~~作者没给标签，wuwuwu~~。没事，无伤大雅。

根据题意，以下子串被淘汰：

-  ```AGC```
-  ```ACG```
-  ```GAC```
-  ```AG?C```
-  ```A?GC```

做法是动态规划啦。

让 $0$ 代表 $A$，让 $1$ 代表 $G$，让 $2$ 代表 $C$，让 $3$ 代表 $T$。

## 动转方程

暴力一点，五重循环。

有 $i , w , x , y , z $。

代码：

```cpp
for(int i=1;i<=n;i++){
    for(int w=0;w<=3;w++){
        for(int x=0;x<=3;x++){
            for(int y=0;y<=3;y++){
                for(int z=0;z<=3;z++){
                    
                }
            }
        }
    }
}
```
长度为 $i+1$ 的字符串的方案数 $=$ 长度为 $i$ 的字符串的方案数加一个字母。

状态转移：$ dp_{i,x,y,z}=dp_{i-1,w,x,y}+dp_{i,x,y,z} $。

完事儿！

## 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int dp[105][4][4][4];
const ll mod=(1e9)+(7);
bool check(int w,int x,int y,int z){      //非法子串判断
    if (x == 0 && y == 2 && z == 1) return false;
    if (x == 2 && y == 0 && z == 1) return false;
    if (x == 0 && y == 1 && z == 2) return false;
    if (w == 0 && y == 2 && z == 1) return false;
    if (w == 0 && x == 2 && z == 1) return false;
    return true;
}
int main(){
    int n; cin>>n;
    if(n==1){        //特判
		printf("4");
		return 0;
	}
	if(n==2){
		printf("16");
		return 0;
	}
	if(n==3){
		printf("61");
		return 0;
	}
    dp[0][3][3][3]=1;      //初始
    for(int i=1;i<=n;i++){
        for(int w=0;w<=3;w++){
            for(int x=0;x<=3;x++){
                for(int y=0;y<=3;y++){
                    for(int z=0;z<=3;z++){
                        if(check(w,x,y,z)){
                            dp[i][x][y][z]+=dp[i - 1][w][x][y];      //动转方程
                            dp[i][x][y][z]%=mod;
                        }
                    }
                }
            }
        }
    }
    ll ans=0;
    for(int i=0;i<4;i++) {
        for(int j=0; j<4;j++) {
            for(int k=0;k<4;k++) {
                ans+=dp[n][i][j][k];
            }
        }
    }
    cout<<ans%mod;         //记得取余，AC!
    return 0;
}
```

## AC 记录

[AC!](https://www.luogu.com.cn/record/179771300)

---

## 作者：LiSA_OLiVE (赞：0)

~~半退竞人士来写题解。~~
## 思路
我们先来考虑一下，什么样的子串是不合法的。

1. `AGC` 肯定不合法。
2. `ACG` `CAG` 这些长为 $3$ 的子串都可以通过交换相邻两位得到 `ACG`，也不合法。
3. `AC_G` `A_CG`（其中 `_` 可以为任何字符）这些长为 $4$ 的子串也可以通过交换相邻两位得到 `ACG`，不合法。

我们能看到，当前位 $i$ 能够填的字符，只跟第 $i-3$、$i-2$、$i-1$ 位的字符有关。这样的问题显然就是记忆化或者 DP 的问题。我这里使用记忆化。

我们记忆化搜索的过程中，对于第 $now$ 位，记录下之前第 $now-3$、$now-2$、$now-1$ 位填的字符 $lst1$、$lst2$、$lst3$。此处为了方便表示， `A` `C` `G` `T` 分别用 `1` `2` `3` `4` 表示。特别的，如果 $i\le3$ 尚不存在 $lst1$、$lst2$ 或 $lst3$ 的时候，这些位我们用 `0` 表示。我们也定义记忆化数组 $rem[now][lst1][lst2][lst3]$ 表示第 $i$ 位在之前的三位为 $lst1$、$lst2$、$lst3$ 的时候，第 $i$ 位及之后的所有填法中总合法方案数。

然后我们枚举当前位填什么。如果当前填的字符 $i$ 合法，那么 $rem[now][lst1][lst2][lst3]$ 加上 $\operatorname{dfs}(now+1,lst2,lst3,i)$。之后再碰见询问 $rem[now][lst1][lst2][lst3]$ 时，就不用再计算，直接返回记录下的答案即可，**这也是记忆化可以把搜索优化为 DP 复杂度的原因。**

然后我们直接输出 $\operatorname{dfs}(1,0,0,0)$ 就好啦！
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n;
int rem[200][5][5][5];//三维分别表示 now lst1 lst2 lst3
int dfs(int now,int lst1,int lst2,int lst3){
	if(now>n){
		return 1;
	}
	if(rem[now][lst1][lst2][lst3]!=-1) return rem[now][lst1][lst2][lst3];//记忆化
	int ans=0;
	for(int i=1;i<=4;i++){
		if(!((lst2==1 && lst3==3 && i==2)||(lst2==1 && lst3==2 && i==3)||(lst2==3 && lst3==1 && i==2)||(lst1==1 && lst2==3 && i==2)||(lst1==1 && lst3==3 && i==2))) ans+=dfs(now+1,lst2,lst3,i);//搜索当前位答案
	}
	ans%=mod;
	rem[now][lst1][lst2][lst3]=ans;
	return ans;
}
signed main(){
	cin>>n;
	memset(rem,-1,sizeof(rem));
	cout<<dfs(1,0,0,0);
	return 0;
}
```

---

## 作者：_Gabriel_ (赞：0)

### 题意

给你一个数字 $N$，让你求出有多少种可能的字符串，使之由 `A`，`C`，`G`，`T` 组成，而且字符串不含有子串 `AGC`，并且交换一次相邻的字符也不含有子串 `AGC`。

### 思路

做法是 `DP`。

可以先考虑第三个限制。

不满足第三个限制的字符串有：`AGC`，`GAC`，`ACG`，`A?GC`，`AG?C`。

我们只需要在计算时，把这 $5$ 种会产生不符合条件的字符串不计入计数即可。

现在来看 `DP`：

$dp_{n,i,j,k}$ 表示长度为 $n$ 的字符串中，后三位字符串依次是 $i,j,k$ 的字符串有多少种。

转移方程：$dp_{i,y,z,j}=dp_{i,y,z,j}+dp_{i-1,x,y,z}$，注意 $dp_{i,y,z,j}$ 需要 $\bmod$ $10^9 + 7$。
 
### 代码

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll mod = 1e9 + 7;
const int N = 1e2 + 10;
ll dp[N][4][4][4];

int main() {
    int n;
    cin >> n;
    dp[0][3][3][3] = 1;
    for (int i = 1; i <= n; i++) {
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                for (int z = 0; z < 4; z++) {
                    for (int j = 0; j < 4; j++) {
                        if (y == 0 && z == 2 && j == 1) continue;// AGC
                        if (y == 2 && z == 0 && j == 1) continue;// GAC
                        if (y == 0 && z == 1 && j == 2) continue;// ACG
                        if (x == 0 && z == 2 && j == 1) continue;// A?GC
                        if (x == 0 && y == 2 && j == 1) continue;// AG?C
                        dp[i][y][z][j] += dp[i - 1][x][y][z];
                        dp[i][y][z][j] %= mod;
                    }
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                ans += dp[n][i][j][k];
            }
        }
    }
    cout << ans % mod;
    return 0;
}
```

---

## 作者：Jsxts_ (赞：0)

考虑所有不合法的子串：`AGC GAC ACG AGAC AGGC AGTC ACGC ATGC`

把这些全部插入 AC 自动机中，在上面跑 DP 即可（类似 P4052）。

具体的，设 $f_{i,j}$ 表示长度为 $i$，当前匹配到 AC 自动机节点为 $j$ 的方案数。如果这个节点不是某个上面字符串的结束节点（或者是包含这个字符串的节点，即 fail 树上的儿子），就可以转移。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int n,m;
char s[110];
ll qpow(ll a,ll b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		b >>= 1, a = a * a % mod;
	}
	return res;
}
int to(char ch) {
	return ch == 'A' ? 0 : ch == 'C' ? 1 : ch == 'G' ? 2 : 3;
}
struct Aho_Corasick_automaton {
	int ch[6010][26];
	int End[6010],tot;
	int fail[6010];
	int f[110][6010];
	Aho_Corasick_automaton() {
		tot = 0;
		memset(ch,0,sizeof ch);
		memset(End,0,sizeof End);
		memset(fail,0,sizeof fail);
	}
	void insert(string s) {
		int u = 0,l = s.size();
		for (int i = 0;i < l;i ++ ) {
			int x = to(s[i]);
			if (!ch[u][x]) ch[u][x] = ++tot;
			u = ch[u][x];
		}
		End[u] ++;
	}
	void build() {
		queue<int> q;
		for (int i = 0;i < 26;i ++ )
			if (ch[0][i]) q.push(ch[0][i]), fail[ch[0][i]] = 0;
		while (!q.empty()) {
			int u = q.front();q.pop();
			for (int i = 0;i < 26;i ++ )
				if (ch[u][i]) {
					fail[ch[u][i]] = ch[fail[u]][i];
					q.push(ch[u][i]);
				}
				else ch[u][i] = ch[fail[u]][i];
			End[u] += End[fail[u]];
		}
	}
	void solve() {
		f[0][0] = 1;
		for (int i = 1;i <= m;i ++ )
			for (int j = 0;j <= tot;j ++ )
				for (int k = 0;k < 4;k ++ )
					if (!End[ch[j][k]])
						f[i][ch[j][k]] = (f[i][ch[j][k]] + f[i-1][j]) % mod;
		int ans = 0;
		for (int i = 0;i <= tot;i ++ ) ans = (ans + f[m][i]) % mod;
		printf("%d",ans);
	}
}AUT;
int main() {
	scanf("%d",&m);
	AUT.insert("AGC");
	AUT.insert("GAC");
	AUT.insert("ACG");
	AUT.insert("AGAC");
	AUT.insert("AGGC");
	AUT.insert("AGTC");
	AUT.insert("AGGC");
	AUT.insert("ACGC");
	AUT.insert("ATGC");
	AUT.build(), AUT.solve();
	return 0;
}
```


---

## 作者：Nightingale_OI (赞：0)

### 大意

问有多少长度为 $ n $ 的字符串满足以下条件：

1. 由 A C G T 构成。

2. 不含子串 AGC 。

3. 任意交换其中两个字符依然符合上面的要求。

### 思路

想办法把第 $ 3 $ 条约束去掉后，约束变成如下：

1. 由 A C G T 构成。

2. 不含子串 AGC 、 GAC 、ACG 、ACGC 、AGGC 、ATGC 、AGAC 、AGGC 、AGTC 。

用 $ dp_{i,j,k,l} $ 记录长度为 $ i $ 的符和要求且后 $ 3 $ 个位置分别是 $ j $ ， $ k $ ， $ l $ 的字符串。

枚举下一位选什么并转移即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
const int mo=1e9+7;
int p[9][4]={{4,0,2,1},{4,2,0,1},{4,0,1,2},{0,2,0,1},{0,2,2,1},{0,2,3,1},{0,1,2,1},{0,2,2,1},{0,3,2,1}};
int dp[101][4][4][4];
int main(){
    cin>>n;
    dp[0][1][1][1]=1;
    f(i,0,n-1)f(a,0,3)f(b,0,3)f(c,0,3)f(d,0,3){
        int q[4]={a,b,c,d};
        f(j,0,8){
            f(k,0,3)if(p[j][k]!=q[k] && p[j][k]!=4)goto no;
            goto end;
            no:;
        }
        dp[i+1][b][c][d]=(dp[i+1][b][c][d]+dp[i][a][b][c])%mo;
        end:;
    }
    f(a,0,3)f(b,0,3)f(c,0,3)s=(s+dp[n][a][b][c])%mo;
    printf("%d\n",s);
    return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

$\mathsf{upd:}$ 更改了 $\LaTeX$，以此文祝我初赛过吧ww！

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15257364.html)

## 前言

第一篇题解。

~~我只希望 @liubinze 和 @Sham_Devour 能提前看到这篇题解...~~

## 题目描述

给定一个整数 $N$，请找出满足下列要求的长度为 $N$ 的字符串的数目，答案对 $10^9+7$ 取模。

+ 该字符串仅由 `A C G T` 四种字符组成

+ 该字符串不包含子串 `AGC`

+ 交换相邻两个字符一次不违反上述要求

## 题目分析

因为我们必须满足『交换相邻两个字符一次不违反上述要求』这一条件，而上述要求即『该字符串不包含子串 `AGC`』，所以可以得到『字串必然不包括`ACG,GAC,AGC,A?GC,AG?C`』。

其中 `?` 是 `A C G T` 中任一字符。

我们令 $dp[i][a][b][c]$ 表示在长度为 $i$ 的字符串中，最后三个字符为 $a,b,c$ 且满足条件的字符串数量。

我们令 $1$ 代表 `A`，$2$ 代表 `C`,$3$ 代表 `G`，$4$ 代表 `T`。

那么我们在枚举的时候排除一下 `ACG,GAC,AGC,A?GC,AG?C` 的情况即可：

```cpp
if(a==1 && b==2 && d==3)continue;
if(a==1 && c==2 && d==3)continue;
if(b==1 && c==2 && d==3)continue;
if(b==1 && c==3 && d==2)continue;
if(b==2 && c==1 && d==3)continue;
```

由于 $\rm exlg$ 插入代码的缩进有点点问题，一行一行的修改过于麻烦，代码可以到 $\rm blog$ 里去看看 $\texttt{qwq}$。

---

## 作者：AlanFong (赞：0)

## 思路导向  
对于这类求合法数量的问题，用搜索难以通过，我们考虑 dp。
## 解法  
将 $dp_{i,a,b,c}$ 解释为长度为 $i$ 且最后三位分别为 a,b,c 的字符串个数。   
我们从第三位开始初始化，枚举这个字符串，若合法就将其个数记为一。  
状态和初始化有是有了，可是，如何转移才能够确保合法呢？  
首先，我们先理清有什么样的字串不可以出现在字符串中。  
- 长为 $3$ 的有 `AGC`，`ACG`，`GAC`。    
- 长为 $4$ 的有 `AGGC`，`ATGC`，`AGTC`。

那么，我们只要确定以上字串不出现就好了，我们需要枚举当前字符串的最后四位，包括当前写入位，再判断这四位是否合法。   
需要大家自己写判断，需要一点时间。  
对了，当 $N \le 3$ 时，需要特判。  
## 代码实现  
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int dp[105][5][5][5];//1a2c3g4t
int vis[5];
const int mod=1e9+7;
void dfs(int now,int step)//通过 DFS 来枚举后四位
{
    if(step>4)
    {
        int s1=vis[1],s2=vis[2],s3=vis[3],s4=vis[4];
        bool flag=0;
        if((s2==1&&s3==3&&s4==2)||(s2==1&&s3==2&&s4==3)||(s2==3&&s3==1&&s4==2)||(s1==1&&s2==3&&s3==3&&s4==2)||(s1==1&&s2==4&&s3==3&&s4==2)||(s1==1&&s2==3&&s3==4&&s4==2)) //排除不合法情况
        {
            flag=1;
        }else{
            if(flag==0)
            {
                //cout<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<endl;
                dp[now][s2][s3][s4]+=dp[now-1][s1][s2][s3];//如果合法即转移
                dp[now][s2][s3][s4]=dp[now][s2][s3][s4]%mod;    
            }
        }
        return;
    }
    for(int i=1;i<=4;i++)
    {
        vis[step]=i;
        dfs(now,step+1);
    }
}
signed main()
{
    //freopen("acgt.in","r",stdin);
    //freopen("acgt.out","w",stdout);
    cin>>n;
    for(int i=1;i<=4;i++)//从第三位开始初始化
    {
        for(int j=1;j<=4;j++)
        {
            for(int z=1;z<=4;z++)
            {
                if((i==1&&j==3&&z==2)||(i==1&&j==2&&z==3)||(i==3&&j==1&&z==2))
                {
                    dp[3][i][j][z]=0;
                }else{
                    dp[3][i][j][z]=1;
                }
            }
        }
    }
    for(int i=4;i<=n;i++)//不断枚举
    {
        dfs(i,1);
    }
    if(n==1)//特判
    {
        cout<<4<<endl;
    }else if(n==2)
    {
        cout<<16<<endl;
    }else if(n==3)
    {
        cout<<61<<endl;
    }else{
        int ans=0;
        for(int i=1;i<=4;i++)//求末四位所有情况的和
        {
            for(int j=1;j<=4;j++)
            {
                for(int z=1;z<=4;z++)
                {
                    ans+=dp[n][i][j][z];
                    ans=ans%mod;
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

