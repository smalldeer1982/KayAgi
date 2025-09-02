# [AGC048F] 01 Record

## 题目描述

すぬけくん得到了一个大黑板。すぬけくん非常高兴，首先在黑板上写下了一些正整数。接着，すぬけくん不断重复以下操作，直到黑板上的整数全部消失为止。

- 从黑板上选择一个整数并擦除。设被擦除的整数为 $x$。然后，将 $x$ 除以 $2$ 的余数记录在笔记本上。最后，如果 $x \geq 2$，则将 $x-1$ 写回黑板。

すぬけくん的记录由一个仅包含 `0` 和 `1` 的字符串 $S$ 表示。也就是说，すぬけくん在第 $i$ 次操作中选择的整数除以 $2$ 的余数为 $S_i$。

すぬけくん忘记了最初在黑板上写下的正整数的组合。请根据字符串 $S$，求出作为最初黑板上正整数组合的可能方案数。这里，正整数组合 $a$ 和 $b$ 不同，意味着存在某个整数 $v$，使得 $a$ 中 $v$ 的个数与 $b$ 中 $v$ 的个数不同。由于答案可能非常大，请输出对 $10^9+7$ 取模的结果。如果すぬけくん的记录有误，无法满足条件，则输出 $0$。

## 说明/提示

## 限制

- $1 \leq |S| \leq 300$
- $S$ 是仅由 `0` 和 `1` 组成的字符串。

## 样例解释 1

作为最初黑板上整数的组合可能有 $\{1,2\}$、$\{3\}$ 共 $2$ 种。

## 样例解释 2

不存在满足条件的最初黑板上整数组合。

## 样例解释 3

作为最初黑板上整数的组合可能有 $\{2,2,2\}$、$\{2,4\}$、$\{6\}$ 共 $3$ 种。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
101```

### 输出

```
2```

## 样例 #2

### 输入

```
100```

### 输出

```
0```

## 样例 #3

### 输入

```
010101```

### 输出

```
3```

## 样例 #4

### 输入

```
11101000111110111101001011110010111110101111110111```

### 输出

```
3904```

# 题解

## 作者：UltiMadow (赞：5)

将 $S$ 反过来，则一个数的贡献为一个形如 `101010...` 的串，称这种字符串为好的字符串。

考虑不断贪心地从 $S$ 中取出最长的好串，记它们的长度为 $l_1,l_2,\dots,l_k$。

假设原先在黑板上的数从大到小为 $x_1,x_2,\dots,x_m$，则这些数合法当且仅当下列条件被满足：

1. $\sum x=\sum l$。
  
2. 对于 $\forall 1\le i\le k$，有 $\sum\limits_{j\le i}\lfloor \frac{l_j}2\rfloor\ge \sum\limits_{j\le i}\lfloor\frac{x_j}2\rfloor$（限制了 $0$ 的个数）。
  
3. 对于 $\forall 1\le i\le k$，有 $\sum\limits_{j\le i}\lceil \frac{l_j}2\rceil\ge \sum\limits_{j\le i}\lceil\frac{x_j}2\rceil$（限制了 $1$ 的个数）。
  

必要性显然，下证充分性：

引理：对于两个好的字符串 $a,b$，其中 $|a|\le|b|$，以任意顺序合并，得到的串一定能拆成两个好串 $c,d$，其中 $|a|\le|c|\le|d|\le |b|$，且 $a,b$ 中的 $0,1$ 个数和 $c,d$ 中的 $0,1$ 个数相等。

证明：从 $a,b$ 合并之后的串中取出一个最长的好串 $p$，剩余的字符一定组成另一个好串 $q$。

则 $|c|\ge |q|$，所以可以把所有 $q$ 放到 $c$ 中，再取一些其他的点一定能构成 $c$（由 $|c|\le |p|$）。

由于 $k\le m$，所以不妨在数列 $l$ 后面添加若干个 $0$，使得 $k=m$，目标变为对于所有 $i$ 都有 $l_i=x_i$。

根据引理，有如下操作：

1. 若不存在 $l_i<x_i$，说明操作已经完成。
  
2. 假设存在 $i$ 使得 $l_i<x_i$，且存在 $j<i$ 使得 $l_j\ge x_j+2$，则有 $l_i<x_i\le x_j\le l_j-2$，根据引理，可以将 $l_i,l_j$ 调整为 $l_i+2$ 和 $l_j-2$。
  
3. 若不存在 $j<i$ 使得 $l_j\ge x_j+2$，则一定存在 $j<i$ 使得 $l_j=x_j+1$ 且 $l_j\not\equiv l_i\pmod 2$，根据引理，可以将 $l_i,l_j$ 调整为 $l_i+1$ 和 $l_j-1$。
  

以上步骤可以在有限步内结束，即充分性得证。

然后考虑 dp：设 $f_{i,j,k,l}$ 为考虑前 $i$ 个 $x$，$x_i=j$，$\sum\limits_{j\le i}\lfloor\frac{x_j}2\rfloor=k$，$\sum\limits_{j\le i}\lceil\frac{x_j}2\rceil=l$ 的方案数。

由于 $i$ 之前的 $x$ 都 $\ge j$，所以状态数只有 $\mathcal O(n^3\ln n)$ 个，而转移可以通过前缀和在 $\mathcal O(1)$ 内完成，所以总复杂度 $\mathcal O(n^3\ln n)$。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 310
#define p 1000000007
using namespace std;
int n;
char s[MAXN];
int vis[MAXN],len[MAXN],cnt;
int sa[MAXN],sb[MAXN];
int f[MAXN][MAXN][MAXN],g[MAXN][MAXN][MAXN];
int sum[MAXN][MAXN][MAXN];
signed main(){
	scanf("%s",s+1);n=strlen(s+1);
	reverse(s+1,s+n+1);
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		if(s[i]=='0')return printf("0"),0;
		cnt++;len[cnt]=1;
		for(int j=i+1;j<=n;j++){
			if(vis[j])continue;
			if((s[j]=='0')^(len[cnt]&1))continue;
			len[cnt]++;vis[j]=1;
		}
	}
	for(int i=1;i<=n;i++)sa[i]=sa[i-1]+len[i]/2,sb[i]=sb[i-1]+(len[i]+1)/2;
	f[n][0][0]=1;int ans=0;
	for(int i=1;i<=n;i++){
		memset(sum[n/max(1ll,i-1)+1],0,sizeof(sum[n/max(1ll,i-1)+1]));
		for(int j=n/max(1ll,i-1);j;j--){
			memcpy(g[j],f[j],sizeof(f[j])),memset(f[j],0,sizeof(f[j]));
			memcpy(sum[j],g[j],sizeof(sum[j]));
			for(int a=0;a<=n;a++)
				for(int b=0;b<=n;b++)
					sum[j][a][b]=(sum[j][a][b]+sum[j+1][a][b])%p;
		}
		for(int j=1;j<=n/i;j++)
			for(int a=j/2;a<=sa[i];a++)
				for(int b=(j+1)/2;b<=sb[i];b++)
					f[j][a][b]=sum[j][a-j/2][b-(j+1)/2];
		if(i<cnt)continue;
		for(int j=1;j<=n/i;j++)ans=(ans+f[j][sa[i]][sb[i]])%p;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：takanashi_mifuru (赞：1)

我们发现如果是一个偶数，出来的就是类似 `010101...0101` 的东西，而如果是奇数的话，就是 `101010...10101` 的东西，开头都不同，正着做比较困难，所以考虑倒着做，然后瞬间清晰很多。

我们称长得像 `10101010....`的串为「间隔串」，而两个间隔串通过类似归并的方式随意地拼起来得到的大串，我们称之为「和串」。

我们定义一个串的「极大间隔串」为从第一位开始，能够成为新的间隔串就成为新的间隔串，最后所得到的串即为「极大间隔串」。

那么我们发现：「和串」挖掉「极大间隔串」之后，剩下的仍是一个「间隔串」。

为什么呢，考虑假设有两个点 $i$ 和 $j$ 是最早的产生矛盾的点，就假设他们两个共同为 $1$ 吧，而产生这一点，正是因为 $(i,j)$ 都被取走了，而 $i$ 和 $j$ 恰好没有被取走，对于前面，因为匹配极大间隔串的过程中没有把 $i$ 算进去，所以前面匹配到这里的时候一定前面有一个长度为奇数的子序列，又因为 $i$ 和 $j$ 是第一对出现矛盾的点，所以 $i$ 前面是正常的，即 $i$ 前面匹配到 $i$ 身上的子序列长度为奇数，也就是 $i-1$ 为奇数。

那么 $i-1$ 的前缀如果要分，无论如何分都是一奇一偶，偶数肯定和 $i$ 匹配，然后中间 $(i,j)$ 一长段 肯定给奇数匹配，那么这样的话我们发现，第 $j$ 位无论是谁都没法匹配，第一个子序列末尾为 $i$，和 $j$ 必然相同，而中间的 $j-1$ 和 $j$ 也必然相同否则 $j$ 就被取走了，也就是说这个串根本没办法分成两个间隔串，即这个串根本不是和串，矛盾了。

---

然后我们又发现我们能证明一个更掉的东西了。

对于一个和串，假设他们由间隔串 $A$ 和间隔串 $B$ 拼起来得到（设 $|A|\leqslant|B|$），则对于任意一对 $|A|\leqslant L_1\leqslant L_2\leqslant |B|$（显然如果 $|A|$ 和 $|B|$ 奇偶性相同的时候，$L_1$ 和 $L_2$ 的奇偶性也必须和 $|A|$ 与 $|B|$ 的奇偶性相同。如果 $|A|$ 和 $|B|$ 的奇偶性不同就不需要考虑），而 $L_1+L_2=|A|+|B|$，则必然能够构造出一组间隔串 $C$ 和 $D$，使得 $|C|=L_1$ 且 $|D|=L_2$，同时 $C$ 和 $D$ 的和串与 $A$ 和 $B$ 的和串相同。

为什么呢，我们考虑把他们的和串的极大间隔串与剩下的串找出来，然后以剩下的串的视角看问题。

![](https://pic.imgdb.cn/item/667cba3fd9c307b7e9b35883.png)

如图，红色为剩下的串，容易发现对于每两个点之间的数，必然可以拉出其中偶数个出来转移给小串，即每一段对 $2$ 取模，于是大串的长度可以就这样一点一点变成原本的小串的长度，而大串原本是极大间隔串，$|B|$ 肯定比大串的长度要小，既然从大串到小串之间的每一对 $L_1$ 和 $L_2$ 都能被选取，那么从 $|A|$ 到 $|B|$ 之间的每一对 $L_1$ 和 $L_2$ 也一定都能被选取。

---

我们有了这样一个结论可以将题目所求进行转化。

考虑对原串不断取极大间隔串直到取空，设这样取出来的长度序列为 $D$，长度为 $k_0$。

对于一个单调不增的长度序列 $T$，长度为 $k_1$，什么时候 $T$ 是合法的？

结论是 $T$ 需要满足三个条件：

1. $\sum T=\sum D=n$
2. 对于每个 $i\leqslant k_0$，$T$ 的前缀的数包含的 $0$ 的数量必须不多于 $D$ 的前缀的数包含的 $0$ 的数量。
3. 对于每个 $i\leqslant k_0$，$T$ 的前缀的数包含的 $1$ 的数量必须不多于 $D$ 的前缀的数包含的 $1$ 的数量。

我们来证明一下他为什么是充要的。

首先是必要性，因为如果这个是合法的，前几个数量又比极大还多，那极大可以直接换成 $T$。

其次是充分性，我们考虑如果我们能把 $D$ 变成 $T$ 就能证明出来。

考虑给序列 $D$ 补上 $m-k$ 个长度为 $0$ 的间隔串，则考虑倒过来考虑：

1. 如果 $D_y=T_y$，那就不管。
2. 对于目前枚举到的 $D_y$，考虑在前面找是否有能给他拨两个的（因为我们证明了拨两个给他肯定是合法的），如果有那就给他发两个。
3. 如果没有能发两个的，那么必然存在一个点 $x$ 使得在 $x<y$ 的情况下 $D_x$ 与 $D_y$ 奇偶性不相同，并且 $D_x=T_x+1$，为什么这样的点必然存在呢？考虑我们知道 $D$ 的前缀的 $0$ 的数量比 $T$ 的前缀的 $0$ 的数量要多，而因为可匹配的数如果是奇数则给前缀的 $0$ 的数量的差贡献 $1$，否则给前缀的 $0$ 的数量的差贡献 $1$，而我们看到第 $y$ 个数，假设他的转变需要 $a$ 个 $0$ 和 $b$ 个 $1$，那么他给前缀的 $0$ 的差的贡献就是 $-a$，因为我们知道前缀的 $0$ 的差必须是非负整数，所以前面必然有至少 $a$ 个可用的 $0$ 等在那里，对于 $1$ 则是同理，而又因为我们已经去除了所有 $D_x\geqslant T_x+2$ 的点，所以前缀的 $0$ 和 $1$ 一定都是可用的。

于是我们可以通过若干次操作将 $D$ 转化为 $T$，充分性得证。

---

有了上面这个转化，状态就呼之欲出了，设 $dp_{i,j,k,l}$ 表示有 $i$ 个数，最后一个数为 $j$，前缀 $0$ 的个数为 $k$，$1$ 的个数为 $l$，转移是显然的。

这个东西需要 $O(n^4)$，非常的垃圾，考虑第二维是否真的需要？

在转移方面，倒序枚举 $j$ 即可解决转移中关于 $j$ 的大小的矛盾，所以第二维可以直接丢掉；而你又发现，对于一个 $j$，因为前 $i$ 个数不比 $j$ 小，所以他至少占用了 $i\times j$ 的长度，也就是说 $i$ 和 $j$ 的总共的合法状态数量其实是 $n\ln n$ 的。

到这里时间复杂度 $O(n^3\ln n)$ 已经可以过了，但是不只有 $i$ 可以节省，$k$ 和 $l$ 也可以通过前面有 $i$ 个必然不比 $j$ 小的数计算下界，在加上这个优化后，这份代码轻松跑进了本题最优解，比次优解快了不少。

```cpp
#include<bits/stdc++.h>
using namespace std;
string S;
int n;
bool vis[305];
int L[305],m;
int neta[305];
const int P=1e9+7;
void getL(){
    int all=0;
    while(all<n){
        int need=1;
        int len=0;
        for(int i=1;i<=n;i++){
            if(vis[i])continue;
            if(neta[i]==need){
                need^=1;
                vis[i]=true;
                len++;
            }
        }
        if(len==0){
            puts("0");
            exit(0);
        }
        all+=len;
        L[++m]=len;
        // printf("%lld\n",len);
    }
    return;
}
int dp[305][305][305];
int pre0[305],pre1[305];
void getdp(int all0,int all1){
    dp[0][0][0]=1;
    for(int j=n;j>=1;j--){
        int lim=n/j;
        int num0=j/2;
        int num1=j/2+(j&1);
        for(int i=1;i<=lim;i++){
            for(int k=i*num0;k<=pre0[i];k++){
                for(int l=i*num1;l<=pre1[i];l++){
                    dp[i][k][l]+=dp[i-1][k-num0][l-num1];
                    if(dp[i][k][l]>=P)dp[i][k][l]-=P;
                }
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        ans+=dp[i][all0][all1];
        if(ans>=P)ans-=P;
    }
    cout<<ans;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>S;
    n=S.size();
    S='?'+S;
    int st=1,ed=n;
    while(st<ed)swap(S[st++],S[ed--]);
    for(int i=1;i<=n;i++)neta[i]=S[i]-'0';
    getL();
    for(int i=1;i<=n;i++){
        pre0[i]=pre0[i-1]+L[i]/2;
        pre1[i]=pre1[i-1]+L[i]/2+(L[i]&1);
    }
    getdp(pre0[n],pre1[n]);
    return 0;
}
```

---

## 作者：masterhuang (赞：0)

> 给定一个 $01$ 序列 $s$。
>
> 你可以生成一个多重集 $A$，生成方式如下：
>
> *   在当前 $s$ 中找出一个子序列 $s_{p_1}, s_{p_2}, \dots, s_{p_k}$，满足 $s_{p_k} = 1, s_{p_i} \neq s_{p_{i-1}}$。
> *   将这个子序列从 $s$ 中删去，并将 $k$ 加入 $A$。
>
> 问可以生成多少个不同的多重集（集合无序），对 $10^9+7$ 取模。
>
> $|s|\le 300$。

为了好看，`rev` 一下 $s$，这样 $s_{p_k}=1\to s_{p_1}=1$。

每次就是选一个 $101010\dots$​ 这样的，记为**好串**。

- 考虑找到一个合法解，发现每次选最长好串删除，此时容易调整证明**若有解**这个**一定是一组解**。

- 考虑选 $10$ 交替这种东西很能调整啊，猜一手：对于一个合法状态（比如上面求的那个），

  每步调整 $\epsilon$ 个 $01$ 的归属，能遍历所有合法状态。

具体的，你考虑这么个结论：

**引理**：对于两个好串 $a, b$，其中 $|a| \leq |b|$，以任意顺序合并，得到的串一定能拆成两个好串 $c, d$。

其中 $|a| \leq |c| \leq |d| \leq |b|$，特别的，$|a|,|b|$ 同偶 $|c|,|d|$​ 也得同偶。同奇同理。

**证明：** 从 $a, b$ 合并之后的串中取出一个**最长好串** $p$，剩余字符一定是另一个好串 $q$​。
$$
{\color{blue}{1}}{\color{red}{1}}{\color{blue}{0}}\cdots{\color{blue}{0}}{\color{red}{0}}{\color{blue}{1}}\cdots{\color{blue}{1}}{\color{red}{1}}{\color{blue}{0}}\cdots {\color{blue}{0}}{\color{red}{0}}{\color{blue}{1}}
$$
如上，红色为剩余的串，容易发现对于每两个点之间的数，必然可以拉偶数个给剩余串，即中间段对 $2$ 取模！

这样一点点调整就能得到 $|c|,|d|$ 的串了。由于**取了最长**，显然 $|q|\le |a|\le |b|\le |p|$，界更宽显然没问题。

---

然后你形式化描述你猜的结论：

设不断贪心取最长取出的长度为 $l_1\ge l_2\ge  \dots\ge l_k$。

则集合 $x_1\ge x_2\ge \cdots \ge x_m$ 合法**当且仅当**：

- $\sum \lfloor \frac{l_j}{2} \rfloor = \sum \lfloor \frac{x_j}{2} \rfloor,\sum\limits \lceil \frac{l_j}{2} \rceil = \sum \lceil \frac{x_j}{2} \rceil$，即 $01$ 个数要正确。
- 对于 $\forall 1 \leq i \leq k$，有 $\sum\limits_{j \leq i} \lfloor \frac{l_j}{2} \rfloor \geq \sum\limits_{j \leq i} \lfloor \frac{x_j}{2} \rfloor$，限制 $0$ 的个数。
- 对于 $\forall 1 \leq i \leq k$，有 $\sum\limits_{j \leq i} \lceil \frac{l_j}{2} \rceil \geq \sum_{j \leq i}\limits \lceil \frac{x_j}{2} \rceil$，限制 $1$​ 的个数。

> 证明自然就考虑按上述引理从 $x$ 调整到 $l$。不妨设 $l$ 后面补 $0$ 补到长为 $m$。
>
> 根据引理，有如下操作：
>
> - 若不存在 $l_i < x_i$，说明操作已经完成。
>
> - 若存在 $i$ 使得 $l_i < x_i$，且存在 $j < i$ 使得 $l_j \ge x_j + 2$，则有 $l_i < x_i \le x_j \le l_j - 2$。
>
>   根据引理，可以将 $l_i, l_j$ 调整为 $l_i + 2$ 和 $l_j - 2$，此时一定奇偶正确。
>
> - 若不存在 $j < i$ 使得 $l_j \ge x_j + 2$，则分析 $01$ 个数容易发现：
>
>   一定存在 $j < i$ 使得 $l_j = x_j + 1$ 且 $l_j \not\equiv l_i \pmod 2$。
>
>   根据引理，可以将 $l_i, l_j$ 调整为 $l_i + 1$ 和 $l_j - 1$​。

接下来设计 **dp** 是平凡的。

$f_{i,j,s_1,s_2}$ 表示考虑到 $\ge i$ 的数，选了 $j$ 个，下取整/上取整的和分别为 $s_1,s_2$ 的方案数。

考虑之前选的数的和 $s\ge ij,s\le n$，所以前两维总共只有 $O(n\ln n)$ 种状态。

空间滚动第一位即可，总复杂度 $O(n^3\ln n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=305,mod=1e9+7;
int n,m,a[N],l[N],f[N][N][N],s1[N],s2[N],ans;
string S;bool v[N];
inline void ad(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>S;n=S.size();
	for(int i=1;i<=n;i++) a[n-i+1]=S[i-1]-'0';
	for(int x=n;x;)
	{
		int c=0;
		for(int i=1,o=1;i<=n;i++) if(!v[i]&&a[i]==o) c++,v[i]=1,o^=1;
		if(!c) return cout<<0,0;
		l[++m]=c,x-=c;
	}f[0][0][0]=1;
	for(int i=1;i<=n;i++) s1[i]=s1[i-1]+l[i]/2,s2[i]=s2[i-1]+(l[i]+1)/2;
	for(int j=n;j;j--)
	{
		int F=j/2,G=(j+1)/2;
		for(int i=1;i*j<=n;i++)
			for(int o=i*F;o<=s1[i];o++) for(int p=i*G;p<=s2[i];p++)
				ad(f[i][o][p],f[i-1][o-F][p-G]);
	}
	for(int i=1;i<=n;i++) ad(ans,f[i][s1[n]][s2[n]]);
	return cout<<ans,0;
}
```

---

