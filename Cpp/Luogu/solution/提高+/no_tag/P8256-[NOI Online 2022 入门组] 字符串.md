# [NOI Online 2022 入门组] 字符串

## 题目背景

**经过管理员的考虑，我们打算将民间数据单独存放在最后一个 Subtask 中。这些测试点分数均为 0 分，但是没有通过其中的任何测试点将会视为此题不通过。**

**这一题中出现了评测记录测试点编号错乱的问题，是民间数据命名方式冲突导致的。但是我们保证其相对顺序没有混乱。**

民间数据提供者：@tiger2005。

## 题目描述

Kri 非常喜欢字符串，所以他准备找 $t$ 组字符串研究。

第 $i$ 次研究中，Kri 准备了两个字符串 $S$ 和 $R$ ，其中 $S$ 长度为 $n$，且只由 `0`, `1`, `-` 三种字符构成（注：这里的第三种字符是减号），$R$ 初始时为空。

每次研究，Zay 会带着一个美丽的长度为 $m$ 的字符串 $T$ 来找 Kri 玩，Kri 非常羡慕 Zay 拥有如此美丽的字符串，便也想用字符串 $S$ 和 $R$ 变出字符串 $T$。

具体地，Kri 将会进行 $n$ 次操作。每次操作中，Kri 会取出 $S$ 的第一个字符（记为 $c$），并将其从 $S$ 中删去。如果 $c = \texttt{-}$，则 Kri 要删去 $R$ 的开头字符或结尾字符（数据保证删去后 $R$ 不为空）。否则，Kri 会将 $c$ 加入到 $R$ 的末尾。

当进行完所有操作后，Kri 会检查 $R$ 是否和 $T$ 相等。如果 $R = T$，Kri 就会感到开心；否则，Kri 会感到难受。

请问在每次研究中，Kri 有多少种操作方式使自己最后感到开心？我们定义两种方案不同，当且仅当在某种方案的某次操作中， Kri 删去了 $R$ 的开头字符。而在另一种方案的这次操作中， Kri 删去了 $R$ 的结尾字符。

由于答案可能很大，你只需要输出答案除以 $1,000,000,007$（即 $10^9+7$）的余数。

## 说明/提示

**【样例 1 解释】**

对于第一组数据，有以下两种方案：

- 第一个 `-` 删 $R$ 的开头，第二个 `-` 删 $R$ 的开头。
- 第一个 `-` 删 $R$ 的结尾，第二个 `-` 删 $R$ 的开头。

**【数据范围】**

对于 $20\%$ 的数据，$n,m\le 15$。

对于 $30\%$ 的数据，$n,m\le 30$。

对于 $70\%$ 的数据，$n,m\le 80$。

对于另 $10\%$ 的数据，保证答案不超过 $1$。

对于 $100\%$ 的数据，$1\le t\le 5$，$1\le n,m\le 400$。

## 样例 #1

### 输入

```
3
6 2
10-01-
01
7 3
010-1-1
101
6 4
111-00
1100```

### 输出

```
2
1
2```

## 样例 #2

### 输入

```
见附件中的 string2.in```

### 输出

```
见附件中的 string2.out```

# 题解

## 作者：PosVII (赞：49)

**前言**

------------

我已经很久没有写题解了，有点小激动。

同学认为我的思路晦涩难懂，我很伤心。

**思路**

------------

首先我们要确定，每次加进去的字符是在一开始就决定了它的结果：被从 R 左边删除（称为 l）、被从 R 右边删除（称为 r）、成为 T 的一部分（称为 o）。由于加字符只能从后面加，所以当我们决定它要成为 T 的一部分时，它在 T 中所属的下标也唯一确定了。

因为 S 的操作确定，字符串 R 的长度也一定确定。

对于字符串 R，它的样子肯定长这样：

```
l l l l o o o o r r r r
```

解释一下为什么 l 和 r 中没有零散的 o，很简单，因为你要把左边该删掉的一定要连续地删掉，不能把不该删的删了，右边的同理。确定了 R 的形态，动态规划就比较好想了。

设 $dp_{i,j,k}$ 是当执行到第 $i$ 个操作时，左边有 $j$ 个字符要被删掉，右边有 $k$ 个字符要被删掉时方案数，由于此时 R 的长度一定，中间 o 的数量也确定了。

设此时 R 长度为 len，状态转移就是：

当 $s_{i}$ 是 '-' 时：

$dp_{i,j,k} = dp_{i-1,j+1,k} + dp_{i-1,j,k+1}$（此时选择删左边或删右边）。

当 $s_{i}$ 非 '-' 时：

$dp_{i,j,k} = dp_{i-1,j,k} + dp_{i-1,j,k-1}$（只要此时后面有必须要删的，就意味着新加的也要在后面被删掉，即：$1 \leq k$）。

$dp_{i,j,k} = dp_{i,j,k} + dp_{i-1,j,k}$（可以加在后面且匹配，即：$k = 0$ & $t_{len-j} = s_{i}$）。

$dp_{i,j,k} = dp_{i,j,k} + dp_{i-1,j-1,k}$（**重中之重**，当全都是 l 时，加在后边也可以在左边删除）。

时间复杂度 $O(n^3)$，和他人不同。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
template<typename G>inline void read(G&x) {x=0;G f=1;char ch=getchar();while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();if(ch=='-') {f=-1;ch=getchar();}while(ch>='0'&&ch<='9') {x=x*10+(ch^48);ch=getchar();}x*=f;}
const int MAXN=405,p=1e9+7;
int T,n,m,tot,dp[MAXN][MAXN][MAXN];
char s[MAXN],t[MAXN];
int main() {
	read(T);
	while(T--) {
		read(n),read(m);
		cin>>(s+1)>>(t+1);
		tot=0;
		for(int i=1;i<=n;++i) {
			if(s[i]=='-') ++tot;
		}
		if(n-tot*2!=m) {
			puts("0");
			continue;
		}
		int len=0;
		memset(dp,0,sizeof(dp));
		dp[0][0][0]=1;
		for(int i=1;i<=n;++i) {
			if(s[i]=='-') --len;
			else ++len;
			for(int j=0;j<=tot;++j) {
				for(int k=0;k<=tot;++k) {
					if(s[i]=='-') {
						dp[i][j][k]=(dp[i-1][j+1][k]+dp[i-1][j][k+1])%p;
					}
					else {
						if(k>0) dp[i][j][k]=dp[i-1][j][k-1];
						else if(t[len-j]==s[i]) dp[i][j][k]=dp[i-1][j][k]; 
						if(len==j) dp[i][j][k]=(dp[i][j][k]+dp[i-1][j-1][k])%p;
					}
				}
			}
		}	
		printf("%d\n",dp[n][0][0]);
	}
	return 0;
}
```

---

## 作者：gyyyyx (赞：22)

2025/3/15 Update：修改了一些错误。

---


在考场上没想出来，只打了个暴力，后来看了题解才知道怎么做。

首先一看这题就知道肯定是 DP。

先说说状态。

设 $dp_{i,j,k,l}$ 表示决策到 $S$ 的第 $i$ 位，$R$ 中有 $j$ 位是无需删除的，并且需要删除 $R$ 的前 $k$ 位和后 $l$ 位。

转移方程就很好想了。

1. $S_i=-$，那么 $dp_{i,j,k,l}$ 可以转移到 $dp_{i+1,j,k-1,l}$ 和 $dp_{i+1,j,k,l-1}$，即删除首位或者末尾。

2. $S_i\neq-$，那么 $dp_{i,j,k,l}$ 可以转移到 $dp_{i+1,j,k,l+1}$，即以后会被当成删除末尾来处理。

3. $S_i\neq-$ 且 $j=0$ 且 $l=0$，那么 $dp_{i,j,k,l}$ 可以转移到 $dp_{i+1,0,k+1,0}$，即以后会被当成删除首位来处理（$j=0$ 且 $l=0$ 表示需要它的前面所有位置都是被当成删除首位来处理）。

4. $S_i\neq-$ 且 $S_i=T_{j+1}$ 且 $l=0$，那么 $dp_{i,j,k,l}$ 可以转移到 $dp_{i+1,j+1,k,0}$，即永远不会删除它（$S_i=T_{j+1}$ 且 $l=0$ 表示需要它和 $R$ 中正确的那一位的后一位相同以及没有末尾会被删除）。

但是，发现时间和空间都会炸掉。

我们会发现 $j$，$k$，$l$ 三位加起来一定等于 $i$。

也就是说知道其中两位和 $i$ 就一定知道另外一位。

那么 $dp_{i,j,k,l}$ 就改为 $dp_{i,j,k}$，把一位压掉了。

循环也可以减少一层。

最终时间复杂度是 $O(nm^2)$。

之后就是打代码啦。

代码用的记忆化搜索，方便理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define ll long long
#define N 405
int t,n,m;
string S,T;
ll dp[N][N][N];
#undef N
ll Solve(int i,int j,int k,int l){
    if(i>n) return j==m&&!k&&!l;
    if(~dp[i][j][k]) return dp[i][j][k];
    ll res(0);
    if(S[i-1]=='-'){
        if(k) res=(res+Solve(i+1,j,k-1,l))%mod;
        if(l) res=(res+Solve(i+1,j,k,l-1))%mod;
    }
    else{
        res=Solve(i+1,j,k,l+1)%mod;
        if(!j&&!l) res=(res+Solve(i+1,0,k+1,0))%mod;
        if(S[i-1]==T[j]&&!l) res=(res+Solve(i+1,j+1,k,0))%mod;
    }
    return dp[i][j][k]=res%mod;
}
#undef ll
int main(){
    std::ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>m>>S>>T;
        memset(dp,-1,sizeof(dp));
        cout<<Solve(1,0,0,0)%mod<<endl;
    }
    return 0;
}
```

完结撒花！

---

## 作者：ttq012 (赞：22)

### 第一部分：题意简述

一共有 $t$ 组数据。

对于每一组数据，给定两个字符串 $S$，$T$，其中 $S$ 的长度为 $n$ 并且每一个字符都是 `0`，`1` 或者 `-` 这三个字符中的一个。

还有一个初始为空的字符串 $R$。

现在要进行 $n$ 次操作，每一次操作取出 $S$ 的第一个字符 $c$，然后将其在 $S$ 中删除。如果 $c$ 是字符 `-`，那么删除 $R$ 的开头字符或者结尾字符，否则将 $c$ 插入到字符串 $R$ 的结尾。

问有多少种方式让 $R = T$。答案对 $10^9 + 7$ 取模。

$1\le |S|, |T|\le 400$，$1\le t\le 5$。

### 第二部分：Subtask #2 搜索

这一类求总方案数的题，第一眼看上去比较像搜索，但是答案对 $10^9+7$ 取模证明了答案很大，不能直接使用普通的搜索，会超时，可以得到 $30$ 分。时间复杂度为 $O(N\times N!)$。

### 第三部分：Subtask #3 动态规划

那么考虑动态规划。

可以发现序列以下的性质：当 $c$ 为字符 `-` 的时候，要么删除字符串的开头，要么删除字符串的结尾。所以字符串 $R$ 的删除方式一定是在前面连续地删除 $d_1$ 个，后面连续地删除 $d_2$ 个的。

那么可以考虑开一个这样的动态规划数组：$dp[i][j][k][h]$ 代表现在字符串 $S$ 判断到了 $i$ 这个位置，$j$ 是字符串 $R$ 实际有用的字符的数量，$k$ 是 $R$ 现在开头需要删的字符的数量，$h$ 是 $R$ 现在结尾需要删的字符的数量。

由于当 $c$ 是字符 `-` 的时候，$f[i][j][k][h]$ 可以删除开头字符转移到 $f[i + 1][j][k - 1][h]$，也可以删除结尾的字符转移到 $f[i + 1][j][k][h - 1]$。

否则，也就是 $c$ 是字符 `0` 或者是字符 `1` 的时候，就要将字符 $c$ 插入到字符串 $R$ 的结尾，$f[i][j][k][h]$ 可以转移到 $f[i + 1][j][k][h + 1]$。

如果在满足 $c$ 是字符 `0` 或者是字符 `1` 的前提下，有当前 $S$ 字符串枚举到的字符 $c$ 和当前 $T$ 字符串枚举到的字符 $T_j$ 是一样的，并且最后需要删除的字符数量 $h$ 为 $0$，也就是这个字符 $c$ 和答案串的字符 $T_j$ 相同，并且结尾没有需要删除的字符，那么 $f[i][j][k][h]$ 可以转移到 $f[i + 1][j +1][k][h]$ 这个状态。

因此可以发现这是一个区间动态规划类的题。

答案状态：$f[n+1][m][0][0]$。

但是时间复杂度和空间复杂度都是 $O(N^3\times M)$ 的，既会超时又会超空。

### 第四部分：满分算法 状态的优化

由于上面的四维动态规划状态数组会超时超空，所以考虑优化最后一位 $h$ 的状态。

容易发现 $h = i - k - j - 1$，因为删掉不删除的字符，删掉开头的字符，剩下的字符就是结尾的字符的数量 $h$ 了。

那么可以推出一个三维的动态规划状态数组：$f[i][j][k]$。

那么当字符 $c$ 是字符 `-` 的时候，要么删除字符串的开头要么删除字符串的结尾，$f[i + 1][j][k - 1] = f[i + 1][j][k - 1] + f[i][j][k]$，$f[i + 1][j][k] = f[i + 1][j][k] + f[i][j][k]$。

否则，将字符 $c$ 插入到字符串 $R$ 的结尾。$f[i + 1][j][k] = f[i + 1][j][k] + f[i][j][k]$。

如果字符 $c$ 和字符 $T_j$ 相同，并且结尾没有要删除的字符，那么 $f[i + 1][j + 1][k] = f[i + 1][j + 1][k] + f[i][j][k]$。

最后的答案状态：$f[n + 1][m][0]$。

时间和空间复杂度都是 $O(N^2\times M)$ 的，就可以通过这个题了。

友情提示：

>   数据千万条，清空第一条。
>
>   多测不清空，爆零两行泪。
>
>   多测假清空，爆零三行泪。
>
>   卡常反写挂，爆零四行泪。
>   

**Code**

```cpp
#include <bits/stdc++.h>
#define size(s) s.size()

using namespace std;

string S, T;

const int N = 410;
int s_[N];
int f[N][N][N];

void ClearAll() {
    // 多测不清空，爆零两行泪。
    memset (f, 0, sizeof f);
    memset (s_, 0, sizeof s_);
    S.clear(), T.clear();
}

const int mod = (int) 1e9 + 7;

inline int ksm(int a, int b, int c) { // 快速幂
    if (! b)
        return 1;
    int ans = ksm(a, b >> 1, c);
    ans = 1LL * ans * ans % c;
    if (b & 1)
        ans = 1LL * ans * a % c;
    return ans;
}

signed main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        ClearAll();
        cin >> n >> m >> S >> T;
        for (int i = 0; i < size(S); i ++)
            if (S[i] == '-')
                s_[i + 1] = s_[i + 1] + s_[i] + 1;
            else
                s_[i + 1] = s_[i + 1] + s_[i];
        for (int i = 1; i <= n; i ++)
            for (int j = 0; j <= min(i, m); j ++)
                for (int k = 0; k < i; k ++) {
                    int h = i - 1 - j - k - s_[i - 1] * 2;
                    if (h >= 0) {
                        if (i - 1 - s_[i - 1] * 2 == k)
                            if (j == 0)
                                f[i][0][i - s_[i - 1] * 2 - 1] = ksm(2, s_[i - 1], mod); // 初始化
                        if (S[i - 1] ^ '-') {
                            f[i + 1][j][k] = f[i + 1][j][k] + f[i][j][k], f[i + 1][j][k] %= mod;
                            if (j != m && S[i - 1] == T[j])
                                if (h == 0)
                                    f[i + 1][j + 1][k] = f[i + 1][j + 1][k] + f[i][j][k], f[i + 1][j + 1][k] %= mod;
                        } else {
                            if (k)
                                f[i + 1][j][k - 1] = f[i + 1][j][k - 1] + f[i][j][k], f[i + 1][j][k - 1] %= mod;
                            if (h > 0) 
                                f[i + 1][j][k] = f[i + 1][j][k] + f[i][j][k], f[i + 1][j][k] %= mod;
                        }
                    }
                    // cout << i << ' ' << j << ' ' << k << ' ' << f[i][j][k] << '\n';
                }
        cout << f[n + 1][m][0] << '\n';
    }
    return 0;
}

```



---

## 作者：Grisses (赞：10)

[题面](https://www.luogu.com.cn/problem/P8256)

我们可以设 $dp_{i,j,k,l}$ 表示字符串 $S$ 已经去了前 $i$ 个字符，字符串 $R$ 里面有 $j$ 个字符是以匹配的，需要在前面和后面分别删去 $k,l$  个字符时的方案总数。

如果 $S_i="-"$，那么可以在前面或后面删去一个字符，即转移到 $dp_{i+1,j,k-1,l}$ 和 $dp_{i+1,j,k,l-1}$。

否则，就可以加在后面充当一个在后面的转移从后面删去的字符，即转移到 $dp_{i+1,j,k,l+1}$。如果此时全为要从前面删去的字符（$j=0\And l=0$），可以转移到 $dp_{i+1,0,k+1,0}$。如果 $S_i=T_{j+1}\And l=0$，那就可以成为新的一个已确定的字符，转移到 $dp_{i+1,j+1,k,0}$。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  const int mod=1e9+7;
  int T,n,m,dp[405][405][405];
  char s[405],t[405];
  int dfs(int i,int j,int k,int l){
      if(i>n)return j==m&&!k&&!l;//S取完了
      if(dp[i][j][k]!=-1)return dp[i][j][k];//记忆化搜索
      int tot=0;
      if(s[i]=='-'){
          if(k)tot+=dfs(i+1,j,k-1,l);//删去前面的
          if(l)tot=(tot+dfs(i+1,j,k,l-1))%mod;//删去后面的
      }
      else{
          tot=dfs(i+1,j,k,l+1);//直接加
          if(!j&&!l)tot=(tot+dfs(i+1,0,k+1,0))%mod;//全是需要从前面删的
          if(s[i]==t[j+1]&&l==0)tot=(tot+dfs(i+1,j+1,k,l))%mod;//可成为确定字符
      }
      return dp[i][j][k]=tot;
  }
  int main()
  {
      scanf("%d",&T);
      while(T--){
          scanf("%d%d",&n,&m);
          scanf("%s%s",s+1,t+1);
          memset(dp,-1,sizeof(dp));
          printf("%d\n",dfs(1,0,0,0));
      }
      return 0;
  }
```

---

## 作者：Mistybranch (赞：7)

[传送门](https://www.luogu.com.cn/problem/P8256)

题目大概意思是：有 $T$ 组字符串 $S$，$R$ 和 $T$，其中 $S$，$T$ 是输入，$R$开始为空。$S$ 开始会有三种字符：$\texttt{0}$，$\texttt{1}$ 和 $\texttt{-}$。

- $S_i = \texttt{0}$ 或 $S_i = \texttt{1}$ 时，

	将 $S_i$ 加到 $R$ 的末尾。
    
- $S_i = \texttt{-}$ 时，

	删除 $R$ 的开头**或**结尾。
    
只用看最后的 $R$ 是否能够等于 $T$，如果能，输出方案数，否则输出 $-1$。

这道题是那种一眼能看出来是 dp 的题，首先我们知道 $R$ 中有三类字符串，定义：

- 前无效字符：在 $R$ 最前面的字符串，是需要在后面的操作中删除的，所以不用知道具体的字符分别是什么。

- 有效字符：在前无效字符后面的字符串，是需要保留的字符串，由于需要保留所以要保证第 $i$ 位有效字符等于 $T_i$，所以只用知道长度即可知道具体的字符是什么。

- 后无效字符：在有效字符后面的字符串，也是在 $R$最后面的字符串，是需要在后面的操作中删除的，所以不用知道具体的字符是什么。

然后我们可以 dp，记 $f_{i, j, k}$ 表示 $S_1$ ~ $S_i$ 中，有 $j$ 个前无效字符， $k$ 个有效字符（后无效字符可以由 $i$、$j$、$k$ 以及 $S_1$ ~ $S_i$ 操作后 $R$ 的长度（记为 $a_i$）而算出，结果为 $a_i - j - k$）的方案数。

- 若 $S_i = \texttt{-}$

	则要么删了一个前无效，要么删了一个后无效。
    
   $$f_{i, j, k} = f_{i - 1, j + 1, k} + f_{i - 1, j, k}$$
   
```cpp
if (_s[i] == '-') {
	_f[i][j][k] += _f[i - 1][j + 1][k];
	_f[i][j][k] %= mod;
	_f[i][j][k] += _f[i - 1][j][k]; 
	_f[i][j][k] %= mod;
}
```

- 否则，若 $S_i = T_k$，即为 $S_i$ 可以为有效字符

	- 若 $a_i - j - k > 0$
    
    	必须为后无效字符。
        
        $$f_{i, j, k} = f_{i - 1, j, k}$$
        
   - 否则，若 $k > 0$
   
   		必须为有效字符。
        
        $$f_{i, j, k} = f_{i - 1, j, k - 1}$$
   
   - 否则，若 $j > 0$
   		
       必须为前无效字符。
       
       $$f_{i, j, k} = f_{i - 1, j - 1, k}$$
       
```cpp
else if (k <= _m && _s[i] == _t[k]) {
	if (l) {
		_f[i][j][k] += _f[i - 1][j][k];
		_f[i][j][k] %= mod;
	}
	else if (k) {
		_f[i][j][k] += _f[i - 1][j][k - 1]; 
		_f[i][j][k] %= mod;
	}
	else if (j) {
		_f[i][j][k] += _f[i - 1][j - 1][k];
		_f[i][j][k] %= mod;
	}
}
```
       
- 否则，若 $S_i = \texttt{0}$ 或 $S_i = \texttt{1}$，即为 $S_i$ 必须为无效字符

	- 若 $a_i - j - k > 0$
    
    	必须为后无效字符。
        
        $$f_{i, j, k} = f_{i - 1, j, k}$$
        
   - 否则，若 $j > 0$ 并且 $k = 0$
   
   		必须为前无效字符。
        
        $$f_{i, j, k} = f_{i - 1, j - 1, k}$$
        
```cpp
else {
	if (l) {
		_f[i][j][k] += _f[i - 1][j][k];
		_f[i][j][k] %= mod;
	} 
	else if (j && !k) {
		_f[i][j][k] += _f[i - 1][j - 1][k];
		_f[i][j][k] %= mod;
	}
}
```
   
完整代码：

```cpp


#include <bits/stdc++.h> 

using namespace std;

const int mod = 1e9 + 7;
int _n, _m, _f[409][409][409], _a[409];
char _s[409], _t[409];

void ParseIn () {
	cin >> _n >> _m >> (_s + 1) >> (_t + 1); 
}

void Core () {
	int l;
	
	memset(_f, 0, sizeof(_f));
	
	for (int i = 1; i <= _n; i++) {
		_a[i] = (_s[i] == '0' || _s[i] == '1') ? (_a[i - 1] + 1) : (_a[i - 1] - 1);
	}
	
	_f[0][0][0] = 1;
	
	for (int i = 1; i <= _n; i++) {//1 - i
		for (int j = 0; j <= _a[i]; j++) {//j 个前无效 
			for (int k = 0; k <= _a[i] - j; k++) {//k 个有效 
				l = _a[i] - j - k;//l 个后无效 
				
				if (_s[i] == '-') {
					_f[i][j][k] += _f[i - 1][j + 1][k];
					_f[i][j][k] %= mod;
					
					_f[i][j][k] += _f[i - 1][j][k]; 
					_f[i][j][k] %= mod;
				}
				
				else if (k <= _m && _s[i] == _t[k]) {//s[i]可以作为有效 
					if (l) {//有后无效，则只能为后无效 
						_f[i][j][k] += _f[i - 1][j][k];
						_f[i][j][k] %= mod;
					}
					
					else if (k) {//有有效，则只能为有效 
						_f[i][j][k] += _f[i - 1][j][k - 1]; 
						_f[i][j][k] %= mod;
					}
					
					else if (j) {//有前无效，则只能为前无效 
						_f[i][j][k] += _f[i - 1][j - 1][k];
						_f[i][j][k] %= mod;
					}
				}
				
				else {//s[i]只能作为无效 
					if (l) {//有后无效，则只能为后无效 
						_f[i][j][k] += _f[i - 1][j][k];
						_f[i][j][k] %= mod;
					} 
					
					else if (j && !k) {//只有前无效，则只能为前无效 
						_f[i][j][k] += _f[i - 1][j - 1][k];
						_f[i][j][k] %= mod;
					}
				}
				
				//cout << i << ' ' << j << ' ' << k << ' ' << _f[i][j][k] << endl;
			}
		}
	}
}

void WriteOut () {
    if (_a[_n] != _m) {
        cout << 0 << endl;
        return ;
    }
    
	cout << _f[_n][0][_a[_n]] << endl;
}

int main () {
	int T;
	
	cin >> T;
	
	while (T--) {
		ParseIn();
		Core();
		WriteOut(); 
	}
	
	return 0; 
}
```

---

## 作者：Unnamed114514 (赞：6)

### Update
2022.4.7 更改了一个笔误
> 十年 OI 一场空

> 不开 long long 见祖宗

因为 `long long` 的问题，没掉了 QWQ。

本题重点是状态的定义，设 $dfs(i,j,k,l)$ 表示当前执行第 $i$ 个操作，已经匹配了 $j$ 个 字符，左边需要删除 $k$ 个，右边需要删除 $l$ 个。

这里分两种情况讨论：

1. `s[i]=='-'`

此时我们可以减少一次左边或右边的需求，注意需求量不能变成负数。

如果 $k\ne0$，可以从左边满足一个，那么就是 $dfs(i+1,j,k-1,l)$。

同理，如果 $l\ne0$，就可以从右边满足一个，那么就是 $dfs(i+1,j,k,l-1)$。

2. `s[i]!='-'`

此时我们可以直接从末尾把 $s_i$ 删除，即 $dfs(i+1,j,k,l+1)$。

也可以用 $s_i$ 来匹配：此时 $s_i$ 不能被删掉，那么 $y=0$，并且如果要匹配，还有满足匹配的条件：$s_i=t_{j+1}$。那么就是 $dfs(i+1,j+1,k,l)$。

也可以从前面删：因为有可能匹配 $t_1$ 的在后面，此时先满足 $t_1$，那么就一直删前面，所以后面没得删，即 $l=0$。此时要保证前面没有匹配，即 $j=0$，此时就是 $dfs(i+1,0,k+1,0)$。

我们可以知道，$l+k$ 是一个常数，那么我们可以用 $k$ 表示 $l$，那么记忆化只需要三维，即 $dp_{i,j,k}$。

这里给出记搜的代码，用了时间戳后民间和官方数据共计 $2.11$ 秒。
```cpp
int dfs(int i,int j,int k,int l){
	if(i>n)
		return j==m&&!k&&!l;
	if(tag[i][j][k]==tot)//时间戳，注意此处不能开 long long
		return dp[i][j][k];
	tag[i][j][k]=tot;
	long long val=0;
	if(s[i]=='-'){
		if(k)
			val=dfs(i+1,j,k-1,l);
		if(l)
			val+=dfs(i+1,j,k,l-1);
	} else{
		val=dfs(i+1,j,k,l+1);
		if(!j&&!l)
			val+=dfs(i+1,0,k+1,0);
		if(s[i]==t[j+1]&&!l)
			val+=dfs(i+1,j+1,k,l);
	}
	return dp[i][j][k]=val%mod;
}
```

---

## 作者：NightTide (赞：5)

# NOI Oline 2022 普及组 T3 字符串

## PART 01 题目大意

有一个长度为 $n$ ，且仅含 `0` , `1` , `-`的字符串 $s$ ，遍历字符串 $s$ ，如果 $s_i$ 为 `0`  或 `1` ，则将其加入字符串 $r$ 中；如果 $s_i$ 为 `-` ，则删去 $r$ 的开头或结尾的字符。求使得 $r = t$ 的方案数。

## PART 02 解题思路

### 30pts 做法

由于 $n,m \le 30$，所以减号个数少于 $15$ 个，可以直接用搜索，时间复杂度 $O(2^{cnt})$ ，其中 $cnt$ 表示减号个数。

### 70pts 做法

把字符串分成两段，双向搜索，时间复杂度 $O(2^{1+cnt/2})$ 。这个做法听说可能能拿到满分，但是我没有去做。

### 100pts 做法

下面就是满分做法了，从数据范围可以看出来，标算的时间复杂度大约是 $O(n^3)$ 级别的。我们发现，最后得到的 $R$ 无非是 $S$ 中的数字删去开头和结尾的一段，不妨设 $f_{i,j,k,l}$ 表示当前枚举到 $s$ 的第 $i$ 位，已经匹配了 $t$  的前 $j$ 位，当前的 $r$ 中开头和结尾分别需要删去 $k$ 和 $l$ 个数字。分情况讨论：

> 1.若 $s_i =$  '-'  ，则 $f_{i,j,k,l}$ 可以转移到 $f_{i+1,j,k-1,l}$ 和 $f_{i+1,j,k,l-1}$ 中。

> 2.若 $s_i = $ '0' 或 '1'，则 $f_{i,j,k,l}$ 可以转移到 $f_{i+1,j,k,l+1}$ 中

> 3.在满足 2 的情况下，如果还满足 $s_{i+1} = t_{j+1} ,l = 0$  ，则 $f_{i,j,k,l}$ 可以转移到  $f_{i+1,j+1,k,l}$  中

> 4.在满足 2 的情况下，如果还满足 $j = 0,l = 0$ ，则 $f_{i,j,k,l}$ 还可以转移到 $f_{i+1,j,k+1,l}$ 中

这样的时间复杂度是 $O(n^3m)$ 的，我们还需要进一步去优化。观察到 $i,j,k,l$ 四者中，知道任意三者可以推算出另一个，所以实际有用的状态数只有 $O(n^3)$ 或 $O(n^2m)$。这里把 $j$ 这一维减掉了。根据题意易得，有$j = i - k - l - sum_i$ ，其中 $sum_i$ 表示 $s$ 前 $i$ 个字符中 `-` 的个数。

但是要注意特判 $s$ 最终的到的 $r$ 的长度和 $t$ 不相等的请况。由于数字和减号的数量是确定的，$r$ 的长度也是确定的，有 $len_r = len_s - cnt \times 2$，$cnt$ 表示 $s$ 中减号的数量，当 $len_r = len_t$ 时才有必要进行接下来的程序，否则答案会错（没有这个特判断可以过掉官方数据，但是过不掉洛谷民间数据）。

## PART 3 CODE

```c++
#include<bits/stdc++.h>
#define MAXN 410
#define MOD (ll)(1e9+7)
using namespace std;
typedef long long ll;
int n,m,cas;
string s,r,t;
ll f[2][MAXN][MAXN],sum[MAXN];
//字符串读入
string read(){
    char c; string tmp;
    while(!(isdigit(c) || c=='-')) c=getchar();
    while(isdigit(c) || c=='-'){
        tmp+=c; c=getchar();
    }
    return tmp;
}
int main(){
    scanf("%d",&cas);
    while(cas--){
        s.clear(); t.clear();
        scanf("%d%d",&n,&m);
        s += ' '; t += ' ';
        s+=read(); t+=read();
        //特判
        int cnt = 0;
        for(int i=1;i<=n;i++) if(s[i]=='-') cnt++;
        if(n-cnt*2 != m){
            printf("0\n"); continue;
        }
        for(int i=1;i<=n;i++) sum[i] = sum[i-1] + (s[i] == '-');
        f[0][0][0] = 1;
        for(int i=0;i<n;i++){
            memset(f[(i+1) & 1],0,sizeof(f[(i+1) & 1]));
            for(int k=0;i - k - sum[i] * 2 >= 0;k++){
                for(int l=0;i - k - l - sum[i] * 2 >= 0;l++){
                    int j = i - k - l - sum[i] * 2;
                    if(s[i+1] == '-'){
                        if(k > 0){ // 删去开头的数字
                            f[(i+1) & 1][k-1][l] += f[i & 1][k][l];
                            f[(i+1) & 1][k-1][l] %= MOD;
                        }
                        if(l > 0){ // 删去末尾的数字
                            f[(i+1) & 1][k][l-1] += f[i & 1][k][l];
                            f[(i+1) & 1][k][l-1] %= MOD;
                        }
                    }else{
                        f[(i+1) & 1][k][l+1] += f[i & 1][k][l]; // 加入末尾的数字不需要
                        f[(i+1) & 1][k][l+1] %= MOD;
                        if(j == 0 && l == 0){
                            f[(i+1) & 1][k+1][l] += f[i & 1][k][l];
                            f[(i+1) & 1][k+1][l] %= MOD;
                        }
                        if(s[i+1] == t[j+1] && l==0){
                            f[(i+1) & 1][k][l] += f[i & 1][k][l];
                            f[(i+1) & 1][k][l] %= MOD;
                        }
                    }
                }
            }
        }
        printf("%lld\n",f[n & 1][0][0]);
    }
    return 0;
}
```



---

## 作者：ListenSnow (赞：4)

[原题链接](https://www.luogu.com.cn/problem/P8256)

## 题意

给定两个由 `0`,`1`,`-` 组成的字符串 $S$，$T$，以及一个空串 $R$。$S$ 的长度为 $n$。

现在要进行 $n$ 次操作，每一次操作取出 $S$ 的第一个字符 $c$，然后将其在 $S$ 中删除。如果 $c$ 是字符 `-`，那么删除 $R$ 的开头字符或者结尾字符，否则将 `c` 插入到字符串 $R$ 的结尾。

#### 数据范围

$1\leq |S|,|T| \leq 400$。

## 思路

设 $f_{i,j,k}$ 表示现在取出了 $S$ 中的第 $i$ 个字符，$R$ 中开头**还要**删除 $j$ 个字符，结尾**还要**删除 $k$ 个字符的方案数。最终的答案就是 $f_{n,0,0}$。

当 $s_i=-$ 时，就要从 $R$ 的开头或结尾删去一个数，有：

$f_{i,j,k}=f_{i,j+1,k}+f_{i,j,k+1}$。

设当前 $R$ 的长度为 $now$，由于开头还要删去 $j$ 个数，当前的 $s_i$ 就对应到 $t_{now-j}$，如果它们相等，那么此时结尾就不需要删除字符，就有：

$f_{i,j,k}=f_{i-1,j,k}(k=0)$。

而如果不相等，那么意味着结尾要多删除一个字符，就有：

$f_{i,j,k}=f_{i-1,j,k-1}(k>0)$。

只有当 $R$ 中的目前的字符都会从开头删去时，才可以将当前字符从开头删去，就有：

$f_{i,j,k}=f_{i-1,j-1,k}(j=now)$。

最后，多测别忘了清空。

## code：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=410,mod=1e9+7;
char s[N],t[N];
int n,m,f[N][N][N];
void solve()
{
	scanf("%d%d",&n,&m);scanf("%s%s",s+1,t+1);int tot=0;
	for(int i=1;i<=n;i++) tot+=(s[i]=='-');
	if(n-2*tot!=m) return puts("0"),void();int now=0;
	memset(f,0,sizeof(f));f[0][0][0]=1;
	for(int i=1;i<=n;i++)
	{
		now+=(s[i]=='-'?-1:1);
		for(int j=0;j<=tot;j++)
		    for(int k=0;k<=tot;k++)
		    {
		    	if(s[i]=='-') f[i][j][k]=(f[i-1][j][k+1]+f[i-1][j+1][k])%mod;
		    	else
		    	{
		    		if(k) f[i][j][k]=f[i-1][j][k-1];
		    		else if(s[i]==t[now-j]) f[i][j][k]=f[i-1][j][k];
		    		if(now==j) f[i][j][k]=(f[i][j][k]+f[i-1][j-1][k])%mod;
				}
			}
	}
	printf("%d\n",f[n][0][0]);
}
int main()
{
	int T;scanf("%d",&T);while(T--) solve();
	return 0;
}
```


---

## 作者：sunyizhe (赞：4)

本人当时没学记忆化搜索，在考场上写了 DFS 直接没了……
## 一、题意
- 有 $t$ 组数据。

- 给定字符串 $S$ 和 $T$，字符串 $R$ 为空，问有几种变换方法使 $R=T$，答案对 $10^9+7$ 取模。变换方法不再赘述。

## 二、数据范围
$1 \le t \le 5$，$1 \le n,m \le 400$。

## 三、思路
### 1.基本思路
这题一开始看上去像 DFS，但发现答案要求对 $10^9+7$ 取模，暴搜绝对会**超时**。该办法不可取。

因此，我们要采用**记忆化搜索**的办法解决该题。定义 $f_{i,j,k,l}$ 表示现在决策到了 $S$ 的第 $i$ 个字母，最终的 $R$ 的前 $j$ 位由某些 $S$ 中的字母提供已经确定，当前 $R$ 中开头有 $k$ 个需要删除的字母，结尾有 $l$ 个需要删除的字母。

我们分三类转移 $f_{i,j,k,l}$：
1. 若 $S_i=\texttt{-}$，则转移到 $f_{i+1,j,k-1,l}$ 和 $f_{i+1,j,k,l-1}$。
1. 若 $S_i\not=\texttt{-}$，则转移到 $f_{i+1,j,k-1,l+1}$。
1. 若 $S_i\not=\texttt{-}$ 且 $S_i=T_{j+1}$ 且 $l=0$，则转移到 $f_{i+1,j,k-1,l}$ 和 $f_{i+1,j,k,l-1}$。

但以这种算法，时间复杂度与空间复杂度都是 $O(n^3m)$，严重 **TLE 和 MLE**。我们来优化一下。

### 2.优化
注意到取出 $S$ 中的前 $i$ 个字母后，$R$ 当前字母的总数就确定了。如果还知道了 $R$ 开头有多少个字母要删，中间有多少个字母要保留，就能得到 $R$ 结尾有多少个字母要删。所以如果知道了 $i,j,k$，就能求出 $l$。我们完全可以省掉 $l$。

因此时间复杂度与空间复杂度都变成了 $O(n^2m)$，可以 AC。

## 四、细节
1. 即使要取模，还是得**开 long long**。

2. 记住题目如果有多组解，一定要**初始化**。

3. 即使优化了，数组大小也要开的很细节，如果三个下标都开 410，一看没差多少，其实还会 [MLE](https://www.luogu.com.cn/record/84658458)。

## 五、代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int Mod=1e9+7,N=401;
typedef long long ll;
int n,m;
string s,t;
ll f[N][N][N];
ll work(int i,int j,int k,int l)
{
	if(i>n)return j==m&&!k&&!l;
	if(~f[i][j][k])return f[i][j][k];
	ll ans=0;
	if(s[i-1]=='-')
	{
		if(k)ans=(ans+work(i+1,j,k-1,l))%Mod;
		if(l)ans=(ans+work(i+1,j,k,l-1))%Mod;
	}
	else
	{
		ans=work(i+1,j,k,l+1)%Mod;
		if(!j&&!l)ans=(ans+work(i+1,j,k+1,l))%Mod;
		if(s[i-1]==t[j]&&!l)ans=(ans+work(i+1,j+1,k,l))%Mod;
	}
	return f[i][j][k]=(ans%Mod);
}
int main() 
{
	int T;
	cin>>T;
	while (T--)
	{
		cin>>n>>m>>s>>t;
		memset(f,-1,sizeof(f));
		cout<<work(1,0,0,0)%Mod<<endl;
	}
	return 0;
}
```

\*借鉴：CCF

---

## 作者：Lgx_Q (赞：1)

题意：有一个字符串 $S$，$|S|=n$，然后重复 $n$ 次操作：

1. 取出 $c=S_1$，删除 $S_1$。

2. 如果 $c=$‘$-$’，那么删除字符串 $R$ 的第一个字符 $R_1$ 或最后一个字符 $R_{|R|}$。

3. 如果 $c$ 是 $0/1$，那么把 $c$ 插入到 $R$ 的结尾。

4. 保证删除时 $R$ 非空。

最终你需要使得 $R=T$，给出 $S,T$，问有多少种操作方案。

分析：

个人认为正面推理十分低困难，因为难以维护删除开头的操作（自己推一下就知道了）。

不妨反面思考，倒序处理。

如果 $S_i$ 为 ‘$-$’，要么需要删除前面最近的字符，要么删除最开头的字符。

如果 $S_i$ 为 $0/1$，要么被后面的操作删除，要么和 $T$ 匹配。

设 $f(i,j,k)$ 表示假设已经把 $S_1...S_i$ 和 $T_1...T_j$ 匹配，并且已经提前删除了最近的 $k$ 个字符，最终达到 $T$ 的方案数。

类似的 DP 也可以正序直接弄完。当然，如果从反面思考，干脆直接倒着推！

对于当前状态 $(i,j,k)$，思考对哪些状态有贡献。

1. 当 $S_i=-$ 时

删除结尾：$f(i-1,j,k+1)$

删除开头，这时可以考虑不计状态，等到最后匹配完之后，再一一删除：$f(i-1,j,k)$

2. 当 $S_i=0/1$ 时

如果 $k≠0$，必须删除（不删除的话自己可以画几张图，发现删除的不是结尾，而是中间！）：$f(i-1,j,k-1)$

否则，如果还能匹配（$j≠0$），判断是否可以匹配（$S_i=T_j$）：$f(i-1,j-1,0)$

否则说明匹配完了，接下来可以删除开头：$f(i-1,0,0)$

**注意！这样的 DP 还要判断删完后长度是否一致！（如果不信自己可以调一调）否则会被民间数据卡！**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=410,mod=1e9+7;
int T,n,m,cnt,f[maxn][maxn][maxn];
char s[maxn],t[maxn];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%s%s",&n,&m,s+1,t+1);
		cnt=0;
		for(int i=1;i<=n;i++)
		{
			if(s[i]=='-') --cnt;
			else ++cnt;
		}
		if(cnt!=m) //判断删除后长度是否一致
		{
			printf("0\n");
			continue;
		}
		cnt=0;
		memset(f,0,sizeof f);
		f[n][m][0]=1;
		for(int i=n;i>=1;i--)
		{
			for(int j=m;j>=0;j--)
			{
				for(int k=0;k<=cnt;k++)
				{
					if(s[i]=='-')
					{
						f[i-1][j][k+1]=(f[i-1][j][k+1]+f[i][j][k])%mod;
						f[i-1][j][k]=(f[i-1][j][k]+f[i][j][k])%mod;
					}
					else
					{
						if(k) f[i-1][j][k-1]=(f[i-1][j][k-1]+f[i][j][k])%mod;
						else if(j)
						{
							if(s[i]==t[j]) f[i-1][j-1][k]=(f[i-1][j-1][k]+f[i][j][k])%mod;
						}
						else f[i-1][j][k]=(f[i-1][j][k]+f[i][j][k])%mod;
					}
				}
			}
			cnt+=(s[i]=='-');
		}
		printf("%d\n",f[0][0][0]);
	}
	return 0;
}
```

---

## 作者：Graphcity (赞：1)

考虑倒着做这个操作。

假设已经确定好了每个减号删除的是开头还是结尾。先令 $R=T$，然后从右往左读取 $S$ 中的字符：

- 当前字符为 `-`：往 $R$ 中的开头 / 结尾位置加上一个通配符 `-`（通配符可以看作 `0` 或 `1` 中的任意一个）。
- 当前字符为 `0` 或 `1`：查看 $R$ 的结尾字符。如果结尾字符为通配符或与当前字符相同，则删除结尾字符。否则失败。

可以发现过程中 $T$ 中的字符所在的一定是 $R$ 中一段连续区间。设 $f_{i,j,k}$ 表示从后往前处理完 $S_i$ 字符，当前的 $R$ 中有 $j$ 个通配符在最前面，后接 $T_{1\cdots k}$ 的方案数。

然后按照读取的过程就可以完成整个 DP。注意特判 $T$ 中字符被删空的情况。时间复杂度 $O(Tn^3)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=400,Mod=1e9+7;

int T,n,m,h[Maxn+5]; char s[Maxn+5],t[Maxn+5];
int f[2][Maxn+5][Maxn+5];
inline void add(int &x,int y) {x=(x+y)%Mod;}

inline void Solve()
{
    scanf("%d%d%s%s",&n,&m,s+1,t+1),h[0]=0;
    For(i,1,n) {if(s[i]=='-') h[i]=h[i-1]-1; else h[i]=h[i-1]+1;}
    if(h[n]!=m) {printf("0\n"); return;}
    memset(f,0,sizeof(f)),f[n+1&1][0][m]=1;
    Rof(i,n,1)
    {
        int o=(i&1),p=(o^1); memset(f[o],0,sizeof(f[o]));
        For(l,0,h[i]) For(r,0,h[i]-l) if(f[p][l][r])
        {
            if(s[i]=='-')
            {
                if(r) add(f[o][l+1][r],f[p][l][r]),add(f[o][l][r],f[p][l][r]);
                else add(f[o][l+1][r],f[p][l][r]*2%Mod);
            }
            else
            {
                if(!r) {if(l) add(f[o][l-1][r],f[p][l][r]);}
                else if(l+r<h[i]) add(f[o][l][r],f[p][l][r]);
                else if(t[r]==s[i])
                {
                    if(r>1) add(f[o][l][r-1],f[p][l][r]);
                    else add(f[o][h[i-1]][0],f[p][l][r]);
                }
            }
        }
    }
    printf("%d\n",f[1][0][0]);
}

int main()
{
    scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
```


---

## 作者：SunsetGlow95 (赞：0)

# 题解 - \[NOI Online 2022 入门组\] 字符串

NOI 数据太水。

## 简述题意

给定操作序列 $S$ 和字符串 $T$。考虑这样的过程：维护一个初始为空的字符串 $R$，依次执行 $S$ 中的操作：若为 `0` 或 `1` 则在 $R$ 末尾加入此字符，否则为 `-` 就删去 $R$ 开头或末尾字符。求有多少种不同的方案，使得最终 $R$ 与 $T$ 相同。两方案不同当且仅当一次删除操作的方向不同。$|S|,|T|\le 400$。

## 分析

正向考虑这一过程，会首先想到维护字符串本身，再想办法刻画它与 $T$ 匹配的情形。感觉不简单，所以考虑反向操作。整个过程就变成：要对 $T$ 进行操作，让它最后为空。

于是发现删除操作会变成在头或尾加入一个任意字符，令它为 `X`。原先的 `0` 操作会变成删除末尾的 `X` 或 `0`，`1` 操作会变成删除末尾的 `X` 或 `1`。由于现在的删除只在末尾操作，发现不为 `X` 的部分必然为 $T$ 的一个前缀（可以为空）。所以当前字符串的状态就更易于刻画。

考虑动态规划计数。令 $f_{i,j,k}$ 表示做完了（正向）第 $i$ 次及其往后的操作，当前字符串开头有 $j$ 个 `X`，紧接着是 $T$ 的长度为 $k$ 的前缀。总长度可以预处理为 $l_i$，故末尾的 `X` 数量为 $l_i-j-k$。

初始状态：$f_{n,0,m}=1$。

对于 `-` 操作，前后各转移一次：

$$f_{i-1,j,k}:=f_{i-1,j,k}+f_{i,j,k}$$

$$f_{i-1,j+1,k}:=f_{i-1,j+1,k}+f_{i,j,k}$$

对于 `0`/`1` 操作：

当 $j+k\neq l_i$ 时，删除末尾的 `X`：

$$f_{i-1,j,k}:=f_{i-1,j,k}+f_{i,j,k}$$

否则在末字符匹配得上的条件下：

$$f_{i-1,j,k-1}:=f_{i-1,j,k-1}+f_{i,j,k}$$

一个在状态设计上的细节：对于 $k=0$ 的时候最好只转移一个 $j$，避免出现尴尬情况。以下钦定 $k=0$ 时 $j=0$。答案就是 $f_{0,0,0}$。

时间复杂度 $O(tn^2m)$，空间上可以使用滚动数组做到 $O(nm)$，这样做也极大优化了时间常数。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MXN = 405;
const int DVS = 1e9 + 7;
int T, N, M, len[MXN], cnt[2][MXN][MXN];
char ops[MXN], pat[MXN];

inline void add(int &x, int y) {
  if ((x += y) >= DVS) x -= DVS;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> T;
  while (T--) {
    cin >> N >> M >> ops >> pat;
    len[0] = 0;
    for (int i(0); i != N; ++i)
      len[i + 1] = len[i] + (ops[i] == '-' ? -1 : 1);
    if (len[N] != M) {
      cout << 0 << endl;
      continue;
    }
    memset(cnt[N & 1], 0, sizeof cnt[N & 1]);
    cnt[N & 1][0][M] = 1;
    for (int i(N); i >= 1; --i) {
      bool ii(i & 1);
      memset(cnt[!ii], 0, sizeof cnt[!ii]);
      if (ops[i - 1] == '-') {
        for (int j(0); j < len[i]; ++j) {
          for (int k(1); j + k <= len[i]; ++k) {
            add(cnt[!ii][j + 1][k], cnt[ii][j][k]);
            add(cnt[!ii][j][k], cnt[ii][j][k]);
          }
        }
        add(cnt[!ii][0][0], cnt[ii][0][0]);
        add(cnt[!ii][0][0], cnt[ii][0][0]);
      } else {
        for (int j(0); j < len[i]; ++j) {
          for (int k(1); j + k < len[i]; ++k) {
            add(cnt[!ii][j][k], cnt[ii][j][k]);
          }
          if (pat[len[i] - j - 1] == ops[i - 1])
            add(cnt[!ii][len[i] - j - 1 == 0 ? 0 : j][len[i] - j - 1],
                cnt[ii][j][len[i] - j]);
        }
        add(cnt[!ii][0][0], cnt[ii][0][0]);
      }
    }
    cout << cnt[0][0][0] << endl;
  }
  return 0;
}
```

---

