# [ARC188A] ABC Symmetry

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc188/tasks/arc188_a

`A`, `B`, `C` からなる空でない文字列 $ T $ に対して、以下の $ 2 $ 種類の操作を好きな順で好きな回数だけ行い、空文字列とすることができる時、これを「よい文字列」と呼びます。

- 操作 $ 1 $ ：文字列に存在する同一の文字を $ 2 $ つ選び、削除する（同一の文字が $ 2 $ つ以上ない場合は行えない）
- 操作 $ 2 $ ：文字列に存在する `A`, `B`, `C` を $ 1 $ つずつ選び、削除する（`A`, `B`, `C` がそれぞれ $ 1 $ つ以上ない場合は行えない）

例えば、`ABACA` は、次のように操作を行うことで空文字列にできるため、よい文字列です。

- $ 2,4,5 $ 文字目を選んで削除する（操作 $ 2 $）。文字列は `AA` になる。
- $ 1,2 $ 文字目を選んで削除する（操作 $ 1 $）。文字列は空文字列になる。

`A`, `B`, `C`, `?` からなる長さ $ N $ の文字列 $ S $ が与えられます。`?` をそれぞれ `A`, `B`, `C` のいずれかに置き換えてできる文字列であって、よい文字列を連続する部分文字列として $ K $ 個**以上**含むものはいくつあるでしょうか。ただし、同じ文字列であるような部分文字列であっても、元の文字列内での位置が異なる場合は別々に数えます。

答えを $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 50 $
- $ 0\ \leq\ K\ \leq\ N(N+1)/2 $
- $ N,K $ は整数である
- $ |S|=N $
- $ S $ は `A`, `B`, `C`, `?` からなる文字列である

### Sample Explanation 1

`?` を `A`, `B`, `C` に置き換えてできる文字列は `AAAB`, `ABAB`, `ACAB` の $ 3 $ つあります。 このうち `AAAB` は $ 1,2 $ 文字目の `AA` および $ 2,3 $ 文字目の `AA` がよい文字列であるため、連続する部分文字列としてよい文字列を $ 2 $ 個含みます。ここで、同じ文字列であるような部分文字列であっても、元の文字列内での位置が異なる場合は別々に数えることに注意してください。 一方、`ABAB` が含むよい文字列は `ABAB` の $ 1 $ 個のみです。また、`ACAB` も `CAB` の $ 1 $ 個しかよい文字列を含みません。

### Sample Explanation 2

答えを $ 998244353 $ で割った余りを出力してください。

## 样例 #1

### 输入

```
4 2
A?AB```

### 输出

```
1```

## 样例 #2

### 输入

```
50 411
??AB??C???????????????????????????????A???C????A??```

### 输出

```
457279314```

## 样例 #3

### 输入

```
1 0
A```

### 输出

```
1```

# 题解

## 作者：roBotic (赞：8)

> 一个只包含包含 $\mathtt{A,B,C}$ 的字符串被称为好字符串当且仅当它能在进行若干次以下操作后变成空串。
>
> - 删除字符串中的 $\mathtt{A,B,C}$ 各一个，或者删除字符串中两个相同的字符。
> 
> 给定一个字符串包含 $\mathtt{A,B,C,?}$，问有多少种在问号处填入三种字符的方案满足它的好字符串子串的个数大于给定的 $K$。

首先，观察到一个字符串是不是好的只和三种字符个数有关，与相对位置无关，所以只需要统计个数便可以判断这个字符串是不是好的。我们注意到如下性质：

- 记三种字符的个数分别是 $a,b,c$，则这个字符串是好的的充要条件是 $a\equiv b\equiv c \pmod 2$。

- 充分性：当三者同余 $2$ 时，首先对每个字符都使用第二种操作，然后每种字符的个数变成了其模 $2$ 的余数，然后因为同余，所以余数都是 $0$ 或 $1$，都是 $0$ 就不用操作了，都是 $1$ 那么用第一种操作每种字符都删掉一个，然后就删完了。

- 必要性：首先我们注意到如果删除了两次 $\mathtt{A,B,C}$ 各一个，那么这等价于对每个字符进行了一次删除两个相同的，则任意一种删除的方案都可以转换为进行了若干次删除两个相同字符后删除了 $0$ 次或 $1$ 次三个字符，显然只有在进行完操作 $2$ 后剩下的余数相同才能删完，所以有必要性。

然后我们以类似前缀和的思想记录同余的状态。

然后发现我们只需要每种字符的个数在模 $2$ 下的意义即可。所以状压，用一个三位二进制数表示前缀和到当前这一位，三种字符的个数模 $2$ 的余数。这是八种情况，但其实每两个是等价的，因为余数同为 $0$ 或 $1$ 都行，则 $(000)_2$ 等价于 $(111)_2$，则我们只需要记录四种即可。

定义 $f_{a,b,c,d}$ 表示前缀和等价于 $(000)_2$ 的位置有 $a$ 个，等价于 $(001)_2$ 的位置有 $b$ 个，等价于 $(010)_2$ 的位置有 $c$ 个，等价于 $(011)_2$ 的位置有 $d$ 个的填字符串方案个数，那么这种方案最终会有以下这么多的好子串，只需要判断它是否大于等于 $K$ 然后累加答案即可。

$$\text{Good substr}=\binom{a}{2}+\binom{b}{2}+\binom{c}{2}+\binom{d}{2}.$$

然后我们考虑怎么统计方案的个数，显然是一个简单 dp，记 $g_{i,a,b,c,d,j}$ 表示当前是第 $i$ 位，状态分别是 $a,b,c,d$，当前前缀和这一位的状态等价于 $j$，那么枚举这一位填的字符转移。

然后这样空间疑似会炸，所以滚动掉 $i$ 这一维，然后因为 $a+b+c+d=i+1$，所以可以少存一维 $d$，然后就可以做了。具体可见代码。

[The Submission](https://atcoder.jp/contests/arc188/submissions/60129429)。

---

## 作者：A2_Zenith (赞：4)

居然还能交题解？来写一发。

首先我们对这个串是否合法来考虑。操作之间的先后顺序显然没啥关系，所以我们把移除 ABC 的操作放在前面。这样就一定存在一个时刻，我们后面只会做移除两个相同字符的操作。不难发现这时若这个这个串是合法的，那 A 的数量，B 的数量，C 的数量都需要是偶数。再加上不定的减去的 ABC 的数量，我们不难发现：**一个串合法，当且仅当这个串中 A 的数量，B 的数量和 C 的数量的奇偶性相同。**

所以，我们便可以用一个长 $3$ 的二进制串来表示一个字符串，分别表示 A/B/C 的奇偶性。当且仅当这个串是 $000/111$ 的时候这个串是合法的。

然后看到要对子串这种神秘东西计数，不难想到对 A/B/C 的数量做前缀和再差分回去，而这个前缀的 A/B/C 的状态也可以用二进制串表示。

这时我们发现一个显然的事实：设 $x_i$ 为长 $i$ 的前缀的状态，那么 $[i,j]$ 是合法字符串当且仅当 $x_{i-1} \oplus x_j$ 是 $000/111$。从我们上一段的这个想法来看，这是很容易证明的。我们称这样的两个状态是同构的。

发现互不同构的状态只有 $4$ 种。

那考虑我们拿到了这个前缀状态序列，对它的合法子串计数。分别记 $C_0,C_1,C_2,C_3$ 为这个序列中第 $0/1/2/3$ 种状态的数量，发现任意两个状态相同的位置都是一个合法子串。组合数算一下就是 $\dbinom{C_0}{2}+\dbinom{C_1}{2}+\dbinom{C_2}{2}+\dbinom{C_3}{2}$。容易判断这个东西的字串数量是否大于 $k$。

那我们就可以直接设计 DP 状态了，设 $dp_{i,C_0,C_1,C_2,C_3,S}$ 是填到第 $i$ 位，前缀有 $C_i$ 个第 $i$ 种状态，现在这个状态（长 $i$ 的前缀）是 $S$ 的方案数。转移是简单而繁琐的，直接枚举现在的这一位是填 A，B 还是 C 就好了，故略去不表。时间复杂度看似是 $n^52^\Sigma$ 的，但是不难注意到 $i,C_0,C_1,C_2,C_3$ 知道其中 $4$ 个就能推剩下的一个，所以可以做到 $n^42^\Sigma$。这里的 $\Sigma =3$。这个东西算出来可能是 $2 \times 10^8$，但是合法的 $C_0,C_1,C_2,C_3$ 状态数其实是组合数，所以常数很小，随便过。

代码有点丑，不喜勿喷。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=57;
const int mod=998244353;
int n,k;
int s[N];
int bel(int S){return min(S,7-S);}
int dp[N][N][N][N][8];
inline int C(int x){
    return x*(x-1)/2;
}
inline int Calc(int a,int b,int c){
    return C(a)+C(b)+C(c)+C(n+1-a-b-c);
}
//dp i,a,b,c
//a:000/111
//b:001/110
//c:010/101
//i+1-a-b-c:011/100
signed main(){
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        char t;
        cin>>t;
        if(t=='?')s[i]=-1;
        else s[i]=t-'A';
    }
    // for(int i=1;i<=n;i++)cout<<s[i]<<" ";
    // cout<<endl;
    dp[0][1][0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int S=0;S<=7;S++){
            for(int a=0;a<=i;a++){
                for(int b=0;b<=i-a;b++){
                    for(int c=0;c<=i-a-b;c++){
                        if((s[i]!=1)&&(s[i]!=2)){
                            // cout<<i<<" A"<<endl;
                            int T=S^1;
                            int j=bel(T);
                            if(j==0)(dp[i][a+1][b][c][T]+=dp[i-1][a][b][c][S])%=mod;
                            if(j==1)(dp[i][a][b+1][c][T]+=dp[i-1][a][b][c][S])%=mod;
                            if(j==2)(dp[i][a][b][c+1][T]+=dp[i-1][a][b][c][S])%=mod;
                            if(j==3)(dp[i][a][b][c][T]+=dp[i-1][a][b][c][S])%=mod;
                        }
                        if((s[i]!=0)&&(s[i]!=2)){
                            // cout<<i<<" B"<<endl;
                            int T=S^2;
                            int j=bel(T);
                            if(j==0)(dp[i][a+1][b][c][T]+=dp[i-1][a][b][c][S])%=mod;
                            if(j==1)(dp[i][a][b+1][c][T]+=dp[i-1][a][b][c][S])%=mod;
                            if(j==2)(dp[i][a][b][c+1][T]+=dp[i-1][a][b][c][S])%=mod;
                            if(j==3)(dp[i][a][b][c][T]+=dp[i-1][a][b][c][S])%=mod;
                        }
                        if((s[i]!=0)&&(s[i]!=1)){
                            // cout<<i<<" C"<<endl;
                            int T=S^4;
                            int j=bel(T);
                            if(j==0)(dp[i][a+1][b][c][T]+=dp[i-1][a][b][c][S])%=mod;
                            if(j==1)(dp[i][a][b+1][c][T]+=dp[i-1][a][b][c][S])%=mod;
                            if(j==2)(dp[i][a][b][c+1][T]+=dp[i-1][a][b][c][S])%=mod;
                            if(j==3)(dp[i][a][b][c][T]+=dp[i-1][a][b][c][S])%=mod;
                        }
                    }
                }
            }
        }
    }
    int ans=0;
    for(int a=0;a<=n+1;a++){
        for(int b=0;b<=n+1-a;b++){
            for(int c=0;c<=n+1-a-b;c++){
                // cout<<a<<" "<<b<<" "<<c<<" "<<Calc(a,b,c)<<endl;
                if(Calc(a,b,c)>=k){
                    for(int S=0;S<=7;S++)(ans+=dp[n][a][b][c][S])%=mod;
                }
            }
        }
    }
    cout<<ans<<endl;
}
```

---

## 作者：ran_qwq (赞：2)

upd on 2024/11/26：$\texttt{c}$ -> $\texttt{C}$。

考虑更好地刻画条件。

注意到选的是子序列，所以任意排列字符串不影响一个字符串是否为好。即一个字符串是否为好只和每种字符的出现次数有关。

更进一步地，先全用消除每种字符各一个的操作把出现次数最少的字符清掉，接下来用消除两个同种字符的操作。

设 $cnt_A$ 为 $\texttt{A}$ 的出现次数，$\texttt{B}$、$\texttt{C}$ 同理。这个字符串好当且仅当 $cnt_A\equiv cnt_B\equiv cnt_C\pmod2$。

而对于一个子串 $s[l\dots r]$，$cnt_j$ 又可以表示为 $s_{r,j}-s_{l-1,j}$，这里 $s_{i,j}$ 是 $j$ 出现次数的前缀和的奇偶性。

即对 $c\in\{\texttt{A,B,C}\}$，$s_{r,c}$ 要么全等于 $s_{l-1,c}$，要么全不等于。

对于一个前缀，我们可以把每种字符出现次数奇偶性状压成一个状态 $st_i$，一共 $8$ 种。

则 $st_i$ 可以和 $st_j=st_i$ 或 $st_j=7-st_i$ 的 $j$ 匹配。

对于一对数 $(i,7-i),i\in[0,3]$，它对答案的贡献是 $\binom{tot_{st_i}+tot_{7-st_i}}2$，这里 $tot_i$ 为状态 $i$ 的出现次数（包括 $st_0=0$），且不同 $i$ 之间状态独立。

推到这里就可以愉快地 dp 了。设 $dp_{i,p,j,k,l,m}$ 为前 $i$ 个字符，当前前缀和状态为 $p$，前面有 $j$ 个状态为 $0$ 或 $7$，$k$ 个 $1$ 或 $6$，$l$ 个 $2$ 或 $5$，$m$ 个 $3$ 或 $4$。

转移是平凡的，$m=i+1-j-k-l$ 可以压掉。

时间复杂度 $O(n^4)$，空间复杂度 $O(n^3)$（滚动数组）。

```cpp
int n,m,ans,dp[2][8][N][N][N]; string s;
il int c(int x) {return x*(x-1)/2;}
void QwQ() {
	n=rd(),m=rd(),cin>>s,s=" "+s,dp[0][0][1][0][0]=1;
	for(int i=1,o=1;i<=n;i++,o^=1) {
		mst(dp[o],0);
		for(int p=0;p<8;p++) for(int j=0;j<=i+1;j++) for(int k=0;j+k<=i+1;k++) for(int l=0;j+k+l<=i+1;l++) {
			if(!j&&(!p||p==7)||!k&&(p==1||p==6)||!l&&(p==2||p==5)||j+k+l==i+1&&(p==3||p==4)) continue;
			if(s[i]=='A'||s[i]=='?') cadd(dp[o][p][j][k][l],dp[o^1][p^1][j-(!p||p==7)][k-(p==1||p==6)][l-(p==2||p==5)]);
			if(s[i]=='B'||s[i]=='?') cadd(dp[o][p][j][k][l],dp[o^1][p^2][j-(!p||p==7)][k-(p==1||p==6)][l-(p==2||p==5)]);
			if(s[i]=='C'||s[i]=='?') cadd(dp[o][p][j][k][l],dp[o^1][p^4][j-(!p||p==7)][k-(p==1||p==6)][l-(p==2||p==5)]);
		}
	}
	for(int p=0;p<8;p++) for(int j=0;j<=n+1;j++) for(int k=0;j+k<=n+1;k++) for(int l=0;j+k+l<=n+1;l++)
		if(c(j)+c(k)+c(l)+c(n+1-j-k-l)>=m) cadd(ans,dp[n&1][p][j][k][l]);
	wr(ans,"\n");
}
```

---

## 作者：Link_Cut_Y (赞：2)

是什么人会 A 不会 B 呢？

提供一个好写的做法。

首先需要一个 Observation，即：**一个串是好字符串，当且仅当其中 $\texttt{a}, \texttt{b}, \texttt{c}$ 出现次数的奇偶性相同。**

原因很简单，同时去除一个 $\texttt{abc}$ 三种字母出现次数的奇偶性的影响是相同的。而同时去除两个相同字母，不改变该字母出现次数的奇偶性。

接下来我们发现奇偶性本身也是不重要的，我们只关心哪种字母与其他两种奇偶性不同。

考虑一个非常暴力的 dp：设 $f(i, a, b, c, k, l)$ 表示已经填完了前 $i$ 个字符；以 $i$ 为结尾的，奇偶性与其他两个不同的是 $\texttt{a}, \texttt{b}, \texttt{c}$ 的后缀分别有 $a, b, c$ 个；以 $i$ 结尾，$\texttt{a}, \texttt{b}, \texttt{c}$ 出现次数奇偶性相同的后缀有 $k$ 个；前面**总共**有 $l$ 个好子串。

这个 dp 一共有 $6$ 维，总状态数乍一看是 $O(n ^ {7})$ 的。但是我们猜测他的有效状态很少。事实上，总状态数只有 $1.6 \times 10 ^ 5$ 级别。

因此我们将 dp 数组换成 STL map 即可通过。

```cpp
int n, m;
map<array<int, 5>, int> f[N];
char s[N]; int ans;
void sub() {
	read(n, m);
	scanf("%s", s + 1);
	f[0][{0, 0, 0, 0, 0}] = 1;
	rop(i, 0, n) {
		for (auto j : f[i]) {
			array<int, 5> t = j.x;
			if (s[i + 1] == 'A')
				(f[i + 1][{t[3] + 1, t[2], t[1], t[0], t[4] + t[0]}] += j.y) %= mod;
			if (s[i + 1] == 'B')
				(f[i + 1][{t[2], t[3] + 1, t[0], t[1], t[4] + t[1]}] += j.y) %= mod;
			if (s[i + 1] == 'C')
				(f[i + 1][{t[1], t[0], t[3] + 1, t[2], t[4] + t[2]}] += j.y) %= mod;
			if (s[i + 1] == '?') {
				(f[i + 1][{t[3] + 1, t[2], t[1], t[0], t[4] + t[0]}] += j.y) %= mod;
				(f[i + 1][{t[2], t[3] + 1, t[0], t[1], t[4] + t[1]}] += j.y) %= mod;
				(f[i + 1][{t[1], t[0], t[3] + 1, t[2], t[4] + t[2]}] += j.y) %= mod;
			}
		}
	} for (auto j : f[n]) if ((j.x)[4] >= m) (ans += j.y) %= mod;
	printf("%lld\n", ans);
}
```

---

## 作者：luanyanjia (赞：2)

容易发现一个串是好的的充要条件是：`A`,`B`,`C` 出现次数的奇偶性都相同。因此我们也可以将所有的串分为四类：好的，只有 `A` 和其他两个的奇偶性不同，只有 `B` 和其他两个的奇偶性不同，只有 `C` 和其他两个的奇偶性不同。

大于 $k$ 的不好统计，可以直接用总数减去小于 $k$ 的总和。

设 $ f_{i,x,g,a,b,c} $ 为到第 $i$ 个时，已经凑成了 $x$ 个好的字串，此时所有后缀中，上面说的四类串分别有 $g,a,b,c$ 个。那么转移方程就显而易见了。

当第 $i$ 个字符给定且为 `A` 时：

$$ f_{i,x,g,a,b,c} \rightarrow f_{i+1,x+a,g+1,c,b}$$

当第 $i$ 个字符给定且为 `B` 时：

$$ f_{i,x,g,a,b,c} \rightarrow f_{i+1,x+b,c,g+1,a}$$

当第 $i$ 个字符给定且为 `C` 时：

$$ f_{i,x,g,a,b,c} \rightarrow f_{i+1,x+c,b,a,g+1}$$

当第 $i$ 个字符为 `?` 时，上面三种转移都进行。

时间复杂度 $O(n^7)$ 难以通过。

显然 $ g = i - a - b - c$ 所以可以省掉一维，时间复杂度变为 $ O(n^6) $。

直觉上不能过，但你滚动数组之后就直接过了。因为首先 h好串数量一定小于 $\dfrac{n^2}{4}$，毕竟如果 $s_{l \dots r}$ 是好串，那么 $ s_{l-1 \dots r} $ 就一定不是。其次 $ a + b + c \le n$，相当于有带了 $\dfrac{1}{6}$ 的小常数。所以算一下就是对的。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	char ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);
}
const int N=55,mod=998244353;
int f[2][N*N/4][N][N][N],n,k;
char s[N];
inline int KSM(int x,int n){
	int ans=1;
	while(n){
		if(n&1)ans=1ll*ans*x%mod;
		x=1ll*x*x%mod;
		n>>=1;
	}return ans;
}
signed main(){
	rd(n,k);
	if(k>n*(n+10)/4){
		printf("0\n");
		return 0;
	}
	scanf("%s",s+1);
	int t=0,cnt=0;
	for(int i=0;i<n;i++){
		t^=1;
		if(s[i+1]=='?')++cnt;
		if(!i)f[t][0][0][0][0]=1;
		for(int x=0;x<=min(k,i*(i+1)/2);x++){
			for(int A=0;A<=i;A++){
				for(int B=0;B+A<=i;B++){
					for(int C=0;A+B+C<=i;C++){
						int G=i-A-B-C;
						if(s[i+1]=='A'){
							f[t^1][x+A][G+1][C][B]+=f[t][x][A][B][C];
							if(f[t^1][x+A][G+1][C][B]>=mod)f[t^1][x+A][G+1][C][B]-=mod;
						}else if(s[i+1]=='B'){
							f[t^1][x+B][C][G+1][A]+=f[t][x][A][B][C];
							if(f[t^1][x+B][C][G+1][A]>=mod)f[t^1][x+B][C][G+1][A]-=mod;
						}else if(s[i+1]=='C'){
							f[t^1][x+C][B][A][G+1]+=f[t][x][A][B][C];
							if(f[t^1][x+C][B][A][G+1]>=mod)f[t^1][x+C][B][A][G+1]-=mod;
						}else{
							f[t^1][x+A][G+1][C][B]+=f[t][x][A][B][C];
							if(f[t^1][x+A][G+1][C][B]>=mod)f[t^1][x+A][G+1][C][B]-=mod;
							f[t^1][x+B][C][G+1][A]+=f[t][x][A][B][C];
							if(f[t^1][x+B][C][G+1][A]>=mod)f[t^1][x+B][C][G+1][A]-=mod;
							f[t^1][x+C][B][A][G+1]+=f[t][x][A][B][C];
							if(f[t^1][x+C][B][A][G+1]>=mod)f[t^1][x+C][B][A][G+1]-=mod;
						}
						f[t][x][A][B][C]=0;
					}
				}
			}
		}
	}
	t^=1;
	int ans=0;
	for(int i=0;i<k;i++){
		for(int A=0;A<=n;A++)
			for(int B=0;B+A<=n;B++)
				for(int C=0;A+B+C<=n;C++)(ans+=f[t][i][A][B][C])%=mod;
	}
	printf("%d\n",(KSM(3,cnt)-ans+mod)%mod);
	return 0;
}

```

---

## 作者：small_john (赞：1)

## 前言

怎么题解区都是 $O(n^4)$ 的啊，我来发一个复杂度比较奇妙的特好写做法。

## 思路

首先有结论：一个字符串是好的，当且仅当字符串中 $\mathtt{A,B,C}$ 的奇偶性相同。

- 充分性：当每个字母的奇偶性相同时，可以先使用操作一使得每个字母的个数小于 $2$，此时每个字母还剩下其个数对二取模的值，如果还有剩下的就再使用一次操作二消完；
- 必要性：操作一不会使任何字母个数的奇偶性改变，操作二会使每个字母的奇偶性改变，最终的状态需要将每个字母个数变成 $0$，即都是偶数，所以最初的奇偶性必须相同。

一种朴素的 DP 就是设 $f_{i,j,a_{0,0,0},a_{0,0,1},a_{0,1,0},\cdots,a_{1,1,1}}$ 表示前 $i$ 个字母，有 $j$ 个合法的子串，满足 $l<i$ 且 $l\sim i$ 组成的字符串中 $\mathtt{A,B,C}$ 对 $2$ 取模的值分别为 $x,y,z$ 的 $l$ 的个数为 $a_{x,y,z}$ 的方案数。

这样子显然跑不过，考虑优化，将 $\{0,0,0\},\{1,1,1\}$ 分为一组，将 $\{0,0,1\},\{1,1,0\}$ 分为一组，将 $\{0,1,0\},\{1,0,1\}$ 分为一组，将 $\{1,0,0\},\{0,1,1\}$ 分为一组。

这样转移仍然是对的，因为这一位填什么所对应的状态贡献是唯一的，转移也仍然是 $O(1)$ 的。

根据插板法，状态的个数上界为为 $\binom{54}{4}\times \frac{n(n-1)}{2}\approx 4\times10^8$，但是实际上，状态数只有 $149500$，使用记忆化搜索就能轻松通过。

## 代码

```cpp
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define int long long
const int N = 55,mod = 998244353;
int n,k;
string s;
gp_hash_table<int,int> mp;
gp_hash_table<int,bool> vis;
int dfs(int p,int now,int a,int b,int c,int d)
{
//	cout<<p<<' '<<now<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<'\n';
	if(p>n) return (now>=k);
	int pp = p+now*100+a*1000000+b*100000000+c*10000000000+d*1000000000000;
	if(vis[pp]) return mp[pp];
	vis[pp] = 1;
	int res = 0;
	if(s[p]=='?'||s[p]=='A') res+=dfs(p+1,now+c,c,d,a+1,b); 
	if(s[p]=='?'||s[p]=='B') res+=dfs(p+1,now+d,d,c,b,a+1);
	if(s[p]=='?'||s[p]=='C') res+=dfs(p+1,now+b,b,a+1,d,c);
	res%=mod;
	return mp[pp] = res;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k>>s,s = ' '+s;
	cout<<dfs(1,0,0,0,0,0);
	return 0;
}
````

---

## 作者：Hell0_W0rld (赞：1)

第一次表现分 $\color{#FF8000}\text{2400+}$，写篇题解纪念一下。

# ARC188A ABC Symmetry
Difficulty: $\color{#0000FF}\text{1914}$。

## 题目大意
给你一个字符串，定义好串为可以通过执行以下两种操作变为空串的字符串：
+ 删除两个相同的字符。
+ 删除一组任意顺序的 `A`、`B`、`C`。

你可以把字符串中每一个 `?` 替换为 `A`、`B`、`C` 中的任意一个，求有多少种**替换方式**，使得替换完成后能够有至少 $K$ 个子串是好串。
## 解题思路
先观察好串的性质：`A`，`B`，`C` 个数奇偶性相同。证明很简单，此处略。

考虑对一个没有 `?` 的串进行前缀和，由于我们只关注 `A`、`B`、`C` 个数的奇偶性，将前缀和对 $2$ 取模。

不妨对于所有 `A` 个数为奇数的前缀和，将所有 $3$ 个计数器全部 $\operatorname{xor} 1$。于是前缀和便只有 $4$ 种可能。

所以子串中好串的个数为 $\sum C^x_2$，其中 $x$ 分别取到前缀和中 $000, 001, 010, 011$ 的个数。

将这个个数设计进入状态里，dp 状态为：$dp_{i,c0,c1,c2,c3,x}$ 表示前 $i$ 位，前缀和为 $000,001,010,011$ 的个数分别为 $c0,c1,c2,c3$ 个，并且 $i$ 对应的前缀和为 $x$ 的替换方案数。空间大约占用 $2.3 G$，会炸。

注意到 $c0+c1+c2+c3=i+1$，将 $c3$ 移出状态，空间便可以减少一维，可以通过。

时间复杂度 $O(N^4)$。转移是显然的，具体见代码实现。
## 代码实现
为什么这题能到 *1914 啊。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
#define all(x) x.begin(),x.end()
#define Set(x,y) memset(x,y,sizeof(x))
#define Cpy(x,y) memcpy(x,y,sizeof(x))
#define cll const long long
using namespace std;
template<class T>
void death(T s){cout<<s<<endl;exit(0);}
template<cll MOD> class modint{
//此处不展示
};
using mint=modint<998244353>;
cll N=59;
mint f[N][N][N][N][4];
ll n,k;
char c[N];
ll C(ll x){return x*(x-1)/2;}
int main(){
	cin>>n>>k>>(c+1);
	f[0][1][0][0][0]=1;
	rep(i,1,n){
		ll cn=i+1;
		rep(c00,1,cn)rep(c01,0,cn-c00)rep(c10,0,cn-c00-c01){
			if(c[i]=='A'||c[i]=='?'){
				f[i][c00+1][c01][c10][0]+=f[i-1][c00][c01][c10][3];
				f[i][c00][c01+1][c10][1]+=f[i-1][c00][c01][c10][2];
				f[i][c00][c01][c10+1][2]+=f[i-1][c00][c01][c10][1];
				f[i][c00][c01][c10][3]+=f[i-1][c00][c01][c10][0];
			}
			if(c[i]=='B'||c[i]=='?'){
				f[i][c00+1][c01][c10][0]+=f[i-1][c00][c01][c10][2];
				f[i][c00][c01+1][c10][1]+=f[i-1][c00][c01][c10][3];
				f[i][c00][c01][c10+1][2]+=f[i-1][c00][c01][c10][0];
				f[i][c00][c01][c10][3]+=f[i-1][c00][c01][c10][1];
			}
			if(c[i]=='C'||c[i]=='?'){
				f[i][c00+1][c01][c10][0]+=f[i-1][c00][c01][c10][1];
				f[i][c00][c01+1][c10][1]+=f[i-1][c00][c01][c10][0];
				f[i][c00][c01][c10+1][2]+=f[i-1][c00][c01][c10][3];
				f[i][c00][c01][c10][3]+=f[i-1][c00][c01][c10][2];
			}
		}
	}
	mint ans=0;
	rep(c00,1,n+1)rep(c01,0,n+1-c00)rep(c10,0,n+1-c00-c01){
		ll c11=n+1-c00-c01-c10;
		if(C(c00)+C(c01)+C(c10)+C(c11)>=k)rep(x,0,3)ans+=f[n][c00][c01][c10][x];
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：_lmh_ (赞：1)

一次操作要么删去两个相同的字母，要么删去三个不同的字母，显然这两个操作都不会改变字母数量的差的奇偶性，因而容易证明，一个序列可以消完当且仅当 $A,B,C$ 的数量奇偶性相同。（构造方案是显然的：尽可能删相同的字母，最后要么啥都没有要么剩下 $A,B,C$ 各一个）

令 $S_A,S_B,S_C$ 代表三种字母的出现次数，用 $f_{i,j,k,l,s}$ 代表 $S_B-S_A,S_C-S_A$ 四种可能的奇偶性状态分别出现了 $i,j,k,l$ 次，且最后一个出现的状态是 $s$，转移是显然的。最后合法的字串个数自然就是 $\frac{i(i-1)+j(j-1)+k(k-1)+l(l-1)}{2}$。

时间复杂度 $O(n^4)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
const ll N=53,M=1300,MOD=998244353;
ll n,k,ans,f[N][N][N][N][4];
char s[N];
void add(int& x,const int& y){x+=y;if (x>=MOD) x-=MOD;}
//000 100 010 110
int main(){
	cin>>n>>k>>(s+1);f[1][0][0][0][0]=1;
	for (int i=1;i<=n;++i) for (int j=0;i+j<=n;++j) for (int k=0;i+j+k<=n;++k) for (int l=0;i+j+k+l<=n;++l){
		char c=s[i+j+k+l];
		if (c=='A'|c=='?'){
			add(f[i+1][j][k][l][0],f[i][j][k][l][1]);
			add(f[i][j+1][k][l][1],f[i][j][k][l][0]);
			add(f[i][j][k+1][l][2],f[i][j][k][l][3]);
			add(f[i][j][k][l+1][3],f[i][j][k][l][2]);
		}
		if (c=='B'||c=='?'){
			add(f[i+1][j][k][l][0],f[i][j][k][l][2]);
			add(f[i][j+1][k][l][1],f[i][j][k][l][3]);
			add(f[i][j][k+1][l][2],f[i][j][k][l][0]);
			add(f[i][j][k][l+1][3],f[i][j][k][l][1]);
		}
		if (c=='C'||c=='?'){
			add(f[i+1][j][k][l][0],f[i][j][k][l][3]);
			add(f[i][j+1][k][l][1],f[i][j][k][l][2]);
			add(f[i][j][k+1][l][2],f[i][j][k][l][1]);
			add(f[i][j][k][l+1][3],f[i][j][k][l][0]);
		}
	}
	++n;k<<=1;
	for (int i=1;i<=n;++i) for (int j=0;i+j<=n;++j) for (int o=0;i+j+o<=n;++o){
		int p=n-i-j-o;
		if (i*(i-1)+j*(j-1)+o*(o-1)+p*(p-1)>=k) for (int s=0;s<4;++s) add(ans,f[i][j][o][p][s]);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：gcx12012 (赞：1)

### 前言
赛时推这题性质推了好久，唐。

估计是上位绿/下位蓝。
### Solution
显然根据题意我们发现：一个串被称之为好串，当且仅当三个字符的出现次数的奇偶性相同。

因此我们一开始可以设计一个状态 $S$ 表示三个字符当前数量的奇偶性，然后我们考虑如何计数子串。

显然这个状态 $S$ 有异或性，我们可以将其前缀异或，设前缀状态 $S$ 在状态中出现了 $x$ 次，那么其好串子串的个数为 $\frac{x(x-1)}{2}$。于是可以实时记录各种状态的出现次数。

但是这样的状态有 8 种，省去无需记录的一种，我们的时间复杂度也需要 $O(n^8)$。考虑优化状态，我们只需记录三个字符两两之间的奇偶性是否相同，你发现这样的不同状态只有 4 种，于是可以 dp，转移显然，时间复杂度为 $O(n^4)$。
### Code

```cpp
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define lll __int128
#define ull unsigned long long
#define N 400010
#define For(i,a,b) for(int i=a;i<=b;++i)
#define Rof(i,a,b) for(int i=a;i>=b;--i)
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r 
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<int,int>

using namespace std;
bool st;
const ll mod=998244353;
ll f[52][52][52][52][8];
char s[55];
int n,K;
bool ed;

ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}


int main()
{
	//fprintf(stderr,"%.2lf",(double)(&ed-&st)/1024/1024);
	//freopen("festival.in","r",stdin);
	//freopen("festival.out","w",stdout);
	n=read(),K=read();
	cin.getline(s+1,110);
	f[0][0][0][0][0]=1;
	For(i,0,n-1){
		For(j,0,i){
			For(k,0,i){
				For(l,0,i){
					if(j+k+l>i+1) break;
					if(s[i+1]=='A' || s[i+1]=='?'){
						f[i+1][j+1][k][l][3]=(f[i+1][j+1][k][l][3]+f[i][j][k][l][0])%mod;
						f[i+1][j][k][l][0]=(f[i+1][j][k][l][0]+f[i][j][k][l][3])%mod;
						f[i+1][j][k+1][l][5]=(f[i+1][j][k+1][l][5]+f[i][j][k][l][6])%mod;
						f[i+1][j][k][l+1][6]=(f[i+1][j][k][l+1][6]+f[i][j][k][l][5])%mod;
					}
					if(s[i+1]=='B' || s[i+1]=='?'){
						f[i+1][j][k+1][l][5]=(f[i+1][j][k+1][l][5]+f[i][j][k][l][0])%mod;
						f[i+1][j][k][l][0]=(f[i+1][j][k][l][0]+f[i][j][k][l][5])%mod;
						f[i+1][j+1][k][l][3]=(f[i+1][j+1][k][l][3]+f[i][j][k][l][6])%mod;
						f[i+1][j][k][l+1][6]=(f[i+1][j][k][l+1][6]+f[i][j][k][l][3])%mod;
					}
					if(s[i+1]=='C' || s[i+1]=='?'){
						f[i+1][j][k][l+1][6]=(f[i+1][j][k][l+1][6]+f[i][j][k][l][0])%mod;
						f[i+1][j][k][l][0]=(f[i+1][j][k][l][0]+f[i][j][k][l][6])%mod;
						f[i+1][j+1][k][l][3]=(f[i+1][j+1][k][l][3]+f[i][j][k][l][5])%mod;
						f[i+1][j][k+1][l][5]=(f[i+1][j][k+1][l][5]+f[i][j][k][l][3])%mod;
					}
				}
			}
		}
	}
	ll ans=0;
	For(i,0,n){
		For(j,0,n){
			For(k,0,n){
				if(i+j+k>n+1) break;
				For(l,0,7){
					ll p1=i,p2=j,p3=k,p4=n+1-i-j-k;
					p1=p1*(p1-1)/2,p2=p2*(p2-1)/2,p3=p3*(p3-1)/2,p4=p4*(p4-1)/2;
					//cout<<i<<' '<<j<<' '<<k<<' '<<l<<' '<<f[n][i][j][k][l]<<endl;
					if(p1+p2+p3+p4>=K) ans=(ans+f[n][i][j][k][l])%mod;
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
/*

*/
```

---

## 作者：keysky (赞：0)

solution by [XiangXunYi](https://www.luogu.com.cn/user/841182)
## 思路推导
### step 1
首先题目中操作二同时删掉 `A`，`B`，`C` 的条件相当于同时将三者数量减一，操作一删掉两个相同字符等同于将某一字符的数量减二，那么我们可以发现只使用操作一不会改变奇偶，操作二则是同时反转奇偶，所以一个字符串是个好字符串的必要条件是其中三个字母数量的奇偶性相同，同时容易构造出一组解使其变为空字符串，故也是必要条件。\
构造解：执行操作一直到不能执行为止，最后视情况执行操作二。
### step2
由于题目的~~抽象~~数据范围较小且对于问号的抉择相互影响较大，联想到 dp。首先会想到把 $K$ 放入 dp 状态中来 check 是否合法，但我们发现每次新增一个字符时算贡献是需要枚举之前前缀三个字符的奇偶性，但上一个状态又并不完全由所枚举的单个状态转移过来，dp 的转移就很扑朔迷离（至少我是这样）。所以要改变 dp 的定义，但又要计算好子段个数，所以状态必须能计算 $K$ 值。
### step 3
设一段区间 `A` 的数量对 $2$ 取模为 $a$，`B` 的数量对 $2$ 取模为 $b$，`C` 的数量对 $2$ 取模为 $c$。\
因为好字段必须要三个字符数量奇偶性相同，抽象的理解为 $0/1$ 状态，即区间和为 $0$，前缀和呀！只要两点的前缀和值相等，这个区间就是一个好子段。我们设计一个 dp 状态 $dp_{i,j,k,l,0/1/2/3}$ 表示存在 $i$ 个位置前缀区间满足情况 $0$[^1]，$j$ 个位置前缀区间满足情况 $1$[^2]，$k$ 个位置前缀区间满足情况 $2$[^3]，$l$ 个位置前缀区间满足情况 $3$[^4]且上一个位置前缀区间满足情况 $0/1/2/3$ 的方案数。\
在这种 dp 状态的设计下，我们可以发现，四种情况不重不漏的涵盖了所有区间，当一个区间满足右端点和左端点减一是同一种情况就是一个好子段，最后好子段的个数就是 $\frac{i \times (i + 1) + j \times (j - 1) + k \times (k - 1) + l \times (l - 1)}{2}$ 答案即为所有该值大于 $K$ 的 $dp_{i,j,k,l,0/1/2/3}$ 累加起来。
### step 4
定义有了，该题的转移并不难想，只要根据上一个位置的状态加上当前位置的字符即可转移（给个建议：用刷表）。
## solution
定义 $dp_{i,j,k,l,lst \in \{0/1/2/3\}}$ 表示有 $i$ 个前缀满足情况 $0$，$j$ 个前缀满足情况 $1$，$k$ 个前缀满足情况 $2$，$l$ 个前缀满足情况 $3$，上一个前缀的情况为 $lst$。\
对于当前字符为 `A` 时，情况 $0$ 与情况 $3$ 互换，情况 $1$ 与情况 $2$ 互换。\
对于当前字符为 `B` 时，情况 $0$ 与情况 $1$ 互换，情况 $2$ 与情况 $3$ 互换。\
对于当前字符为 `C` 时，情况 $0$ 与情况 $2$ 互换，情况 $1$ 与情况 $3$ 互换。
```cpp
int pos = i + j + k + l;
int tmp[4] = { i, j, k, l };
int x = lst ^ 3, y = lst ^ 1, z = lst ^ 2;
if ((s[pos] == '?' || s[pos] == 'A') && tmp[x] + 1 <= n) {
    tmp[x]++;
    trans(dp[tmp[0]][tmp[1]][tmp[2]][tmp[3]][x] , dp[i][j][k][l][lst]);
    tmp[x]--;
}
if ((s[pos] == '?' || s[pos] == 'B') && tmp[y] + 1 <= n) {
    tmp[y]++;
    trans(dp[tmp[0]][tmp[1]][tmp[2]][tmp[3]][y] ,dp[i][j][k][l][lst]);
    tmp[y]--;
}
if ((s[pos] == '?' || s[pos] == 'C') && tmp[z] + 1 <= n) {
    tmp[z]++;
    trans(dp[tmp[0]][tmp[1]][tmp[2]][tmp[3]][z] , dp[i][j][k][l][lst]);
    tmp[z]--;
}
```
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 55;
const int mod = 998244353;
int n, least, dp[N][N][N][N][4];
char s[55];
inline void trans(int& x, int y) { x = (x + y) % mod; }
int main() {
    scanf("%d%d%s", &n, &least, s);
    dp[0][0][0][0][0] = 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                for (int l = 0; l < n; ++l)
                    if (i + j + k + l < n)
                        for (int lst = 0; lst < 4; ++lst) {
                            int pos = i + j + k + l;
                            int tmp[4] = { i, j, k, l };
                            int x = lst ^ 3, y = lst ^ 1, z = lst ^ 2;
                            if ((s[pos] == '?' || s[pos] == 'A') && tmp[x] + 1 <= n) {
                                tmp[x]++;
                                trans(dp[tmp[0]][tmp[1]][tmp[2]][tmp[3]][x] , dp[i][j][k][l][lst]);
                                tmp[x]--;
                            }
                            if ((s[pos] == '?' || s[pos] == 'B') && tmp[y] + 1 <= n) {
                                tmp[y]++;
                                trans(dp[tmp[0]][tmp[1]][tmp[2]][tmp[3]][y] ,dp[i][j][k][l][lst]);
                                tmp[y]--;
                            }
                            if ((s[pos] == '?' || s[pos] == 'C') && tmp[z] + 1 <= n) {
                                tmp[z]++;
                                trans(dp[tmp[0]][tmp[1]][tmp[2]][tmp[3]][z] , dp[i][j][k][l][lst]);
                                tmp[z]--;
                            }
                        }
    int ans = 0;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            for (int k = 0; k <= n; ++k)
                for (int l = 0; l <= n; ++l)
                    for (int lst = 0; lst < 4; ++lst)
                        if (i + j + k + l == n && i * (i + 1) + j * (j - 1) + k * (k - 1) + l * (l - 1) >> 1 >= least)
                            trans(ans, dp[i][j][k][l][lst]);
    printf("%d\n", ans);
    return 0;
}
```

[^1]:$a = b \ and \ a = c$
[^2]:$a = c \ and \ a \neq b$
[^3]:$a = b \ and \ a \neq c$
[^4]:$a \neq b \ and \ b = c$

---

## 作者：xiazha (赞：0)

小清新 dp 题，好玩。

首先简化题目对“好的”字符串的定义：

设 ```A``` 出现次数为 $s_A$，另外两个字符类似的，分别为 $s_B$，$s_C$。

则 $s_A$ 与 $s_B$ 与 $s_C$ 三数模 $2$ 同余。

这启示我们只需记录每种字符出现奇偶即可，于是考虑状压，设到当前这一位置，三种字符模 $2$ 的余数，则共有 $(000)_2$，$(001)_2$ 等 $2^3=8$ 种情况。

那么设第 $i$ 个位置的前缀状态为 $p_1$，第 $j$ 个位置的前缀状态为 $p_2$，只要 $p_1$ 与 $p_2$ 每个字符奇偶皆相同或皆不同则 $j+1$ 至 $i$ 这一段即可为合法子串，所以我们可以将像 $000$ 和 $111$，或者 $001$ 和 $110$ 合并为一种，如此一来，我们会发现只有 $4$ 种状态了，我的四种状态是 $000$，$001$，$010$，$100$，当然大家也可以选择其他组合。

接着考虑 dp，设 $dp_{i,c1,c2,c3,c4,st}$ 为统计到了第 $i$ 个位置，目前已有 $c1$ 个状态 $000$，$c2$ 个状态 $001$，其余同理，且 $1\sim i$ 的字符状态为 $st$ 的方案数，其中 $1\le st\le 4$，然后枚举可填字符转移即可。

注意其中边界为 $dp_{0,1,0,0,0,1}=1$，因为在空串时所有字符个数皆为偶数。

最后让我们来统计答案，注意到 $dp_{n,c1,c2,c3,c4,1/2/3/4}$ 的好的子串方案数为 $C_{c1}^2+C_{c2}^2+C_{c3}^2+C_{c4}^2$，接着只需判断与 $k$ 的大小关系加到答案里即可。

注意到这样时空双爆，考虑优化：

- 滚动数组将 $i$ 那一维滚掉。

- 一个性质是 $c1+c2+c3+c4=i-1$，于是时间空间同时省掉一维。

没了，时间复杂度 $O(n^4)$，空间 $O(n^3)$。

[代码](https://atcoder.jp/contests/arc188/submissions/60204395)

---

## 作者：KinNa_Sky (赞：0)

考虑一下什么区间是合法的。  
- 首先如果三种字符的出现次数都是偶数那么是可行的（各自用操作 1）。
- 此外我们发现操作 2 是同时改变三种字符出现次数的奇偶性。

所以区间合法的充要条件是三种字符出现次数的奇偶性相同。  
三种字符出现次数的奇偶性让人很想压起来。

现在我们要计数 dp。  
考虑如何设计状态。  
首先有一维表示当前处理到第 $i$ 位（这一维滚掉），其次 $k$ 应该也要放到状态里。  
在转移时要处理 $k$ 的改变量。  
一种想法是同时把每种状态的后缀数量都塞到状态里，显然无法承受；  
考虑对其优化，我们发现对于奇偶性相同我们并不在意其是 `000` 还是 `111`，能不能把这两种（类）状态合并起来？  
所以我们设计状态 $f_{i, d, a, b, c, k}$ 表示当前处理到第 $i$ 位，当前有 $d$ 个后缀奇偶性相同，有 $a$ 个后缀是 $A$ 与 $B,C$ 奇偶性不同，有 $b$ 个后缀是 $B$ 与 $A,C$ 奇偶性不同，有 $c$ 个后缀是 $C$ 与 $A, B$ 奇偶性不同，且当前合法区间数为 $k$ 的方案数。

注意到时刻有 $d+a+b+c = i$ 所以其实还能再压一维。由于我们对 $k \ge K$ 都视为合法，所以 $k$ 可以和 $K$ 取 $\min$。

那么如果填 $A$，原来需要 $A$ 的就合法了，原来合法的需要 $A$ 了，$B,C$ 的需求互换了，那么转移为：  
$f_{i, d, a, b, c, k} \to f_{i + 1, a, d + 1, c, b, k + a}$。  
类似的，如果填 $B$，那么转移为：  
$f_{i, d, a, b, c, k} \to f_{i + 1, b, c, d + 1, a, k + b}$。  
如果填 $C$，那么转移为：  
$f_{i, d, a, b, c, k} \to f_{i + 1, c, b, a, d + 1, k + c}$。  

复杂度不是很会分析，DP 复杂度无非就是状态数乘上转移复杂度，转移是 $O(1)$ 的。状态数考虑是前面对于 $i$ 分成 $4$ 份（插板）后面乘个 $nk$，总之卡不太到上界，这里放一下状态数：  
![](https://cdn.luogu.com.cn/upload/image_hosting/jnulnvs8.png)  

dp 状态可以写成 `vector` 用 `map` 存（复杂度 $+\log$）。

[Code](https://atcoder.jp/contests/arc188/submissions/60139590)  
AT 上也是飞快，`82ms`。

---

## 作者：封禁用户 (赞：0)

一道不大容易看出结论的计数题。

首先，我们单独考虑一个字符串是否能被消成空串：

- 消掉一个 `A`、一个 `B`、一个 `C` 会一起改变三个字母出现次数的奇偶性。

- 消掉两个相同的字母不会改变这个字母出现次数的奇偶性。

那么，我们可以得到一个结论：一个串可以被消成空串，仅当三个字母出现次数的奇偶性相同。

如果均为奇数，我们可以先各消掉一个字母，这样剩下 `A,B,C` 出现次数均为偶数，我们再两个两个消即可。

如果均为偶数，直接两个两个消即可。

现在，我们知道了：一个串可以被消成空串**当且仅当**三个字母出现次数奇偶性相同。

继续。如果我们知道了一个字符串，那么我们会得到这个字符串的所有前缀（包括空串）的出现次数奇偶性，例如字符串 `AABC`，它的 $5$ 个前缀的次数奇偶性分别是：

| 前缀位置 | A | B | C |
| - | - | - | - |
| 0 | 0 | 0 | 0 |
| 1 | 1 | 0 | 0 |
| 2 | 0 | 0 | 0 |
| 3 | 0 | 1 | 0 |
| 4 | 0 | 1 | 1 |

那么一个连续的子串的次数奇偶性其实就是两个不同的前缀的奇偶性异或和。如果这个子串合法，那么异或和必须是 $000$ 或者 $111$。

于是，我们可以设立一个动态规划的状态：对于一个前缀，记录 $2^3=8$ 个可能的奇偶性出现次数和当前这个前缀的奇偶性。计最后 $ijk$ 出现次数为 $c_{ijk}$，最终统计答案时只需要看 $\sum_{ijk}\frac{c_{ijk}(c_{ijk}-1)}{2}+\sum_{ijk,i=0}c_{ijk}c_{(1-i)(1-j)(1-k)}$ 是否 $\ge K$ 即可。

但是很明显，这个动态规划的时间复杂度已经爆炸了，因为这个时间复杂度为 $O(\binom{n}{8})$。

不过，我们注意到，$000,111$ 的出现次数完全可以合并，同理，$001,110$ 也可以······以此类推。

于是我们砍掉了 $4$ 个状态，每次只用记录 $c_{000}+c_{111},c_{001}+c_{110},c_{010}+c_{101},c_{011}+c_{100}$ 和当前奇偶性即可。我们计上述四个值分别为 $e,f,g,h$，那么字符串最终合法当且仅当 $\frac{e(e-1)+f(f-1)+g(g-1)+h(h-1)}{2}\ge K$。

边界条件为 $e=1,f=g=h=0$，当前奇偶性为 $000$，值为 $1$，转移很好理解。最终状态为 $e+f+g+h=N+1$。

时间复杂度为 $O(\binom{n}{4})$，并带 $8$ 倍常数。

实现套路：你可以在记录奇偶性这一维的时候混淆 $000,111$，或者 $001,110$ 之类的。这样会使你写的快得多，还会砍掉一倍常数。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,K,lsh[55][55][55][55],Nlsh[500005][4],pt1,dp[500005][4],ans;
string s;vector<pair<pair<int,int>,pair<int,int> > >V[55];
const int modp=998244353;

int main(){
	cin>>n>>K>>s;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			for(int k=0;k<=n;k++){
				for(int l=0;l<=n;l++){
					if(i+j+k+l<=n+1){
						lsh[i][j][k][l]=++pt1;
						V[i+j+k+l-1].push_back(make_pair(make_pair(i,j),make_pair(k,l)));
						Nlsh[pt1][0]=i;Nlsh[pt1][1]=j;
						Nlsh[pt1][2]=k;Nlsh[pt1][3]=l;
					}
				}
			}
		}
	}
	dp[lsh[1][0][0][0]][0]=1;
	for(int C=0;C<n;C++){
		for(auto uu:V[C]){
			int i=uu.first.first,j=uu.first.second,k=uu.second.first,l=uu.second.second;
			for(int o=0;o<4;o++){
				if(s[C]!='?'){
					if(s[C]=='A'){
						int zt=o^1;
						dp[lsh[i+(zt==0)][j+(zt==1)][k+(zt==2)][l+(zt==3)]][zt]+=dp[lsh[i][j][k][l]][o];
						dp[lsh[i+(zt==0)][j+(zt==1)][k+(zt==2)][l+(zt==3)]][zt]%=modp;
					}
					else if(s[C]=='B'){
						int zt=o^2;
						dp[lsh[i+(zt==0)][j+(zt==1)][k+(zt==2)][l+(zt==3)]][zt]+=dp[lsh[i][j][k][l]][o];
						dp[lsh[i+(zt==0)][j+(zt==1)][k+(zt==2)][l+(zt==3)]][zt]%=modp;
					}
					else{
						int zt=o^3;
						dp[lsh[i+(zt==0)][j+(zt==1)][k+(zt==2)][l+(zt==3)]][zt]+=dp[lsh[i][j][k][l]][o];
						dp[lsh[i+(zt==0)][j+(zt==1)][k+(zt==2)][l+(zt==3)]][zt]%=modp;
					}
				}
				else{
					for(int cao=1;cao<4;cao++){
						int zt=o^cao;
						dp[lsh[i+(zt==0)][j+(zt==1)][k+(zt==2)][l+(zt==3)]][zt]+=dp[lsh[i][j][k][l]][o];
						dp[lsh[i+(zt==0)][j+(zt==1)][k+(zt==2)][l+(zt==3)]][zt]%=modp;
					}
				}
			}
		}
	}
	for(auto uu:V[n]){
		for(int o=0;o<4;o++){
			int i=uu.first.first,j=uu.first.second,k=uu.second.first,l=uu.second.second;
			if(i*(i-1)+j*(j-1)+k*(k-1)+l*(l-1)>=2*K){
				ans=(ans+dp[lsh[i][j][k][l]][o])%modp;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

