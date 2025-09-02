# [ABC328G] Cut and Reorder

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc328/tasks/abc328_g

長さ $ N $ の数列 $ A=(A\ _\ 1,A\ _\ 2,\ldots,A\ _\ N),B=(B\ _\ 1,B\ _\ 2,\ldots,B\ _\ N) $ が与えられます。

あなたは、数列 $ A $ に対して次の $ 2 $ 種類の操作を好きな順番で好きな回数行うことができます。

- $ A $ を好きな位置で分割し、分割された列を自由に並べ替える。分割した位置 $ 1 $ つにつきコストが $ C $ かかる。 厳密には、$ (X-1)C $ のコストをかけて長さ $ X+1 $ の列 $ (i\ _\ 0,i\ _\ 1,i\ _\ 2,\ldots,i\ _\ X)\ (0=i\ _\ 0\lt\ i\ _\ 1\lt\ i\ _\ 2\lt\cdots\lt\ i\ _\ X=N) $ と $ (1,2,\ldots,X) $ の順列 $ p $ を自由にとり、$ (A\ _\ {i\ _\ {p\ _\ j-1}+1},A\ _\ {i\ _\ {p\ _\ j-1}+2},\ldots,A\ _\ {i\ _\ {p\ _\ j}}) $ を $ j $ の昇順に連結したものを新しい $ A $ とする。
- 整数 $ k $ と $ A $ の好きな要素を $ 1 $ つ選び、選んだ要素の値に $ k $ を加える。コストが $ |k| $ かかる。

操作をすべて終えたときに $ A $ と $ B $ が等しくなるように操作を行うとき、必要なコストの合計の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq22 $
- $ 1\leq\ C\leq10^{15} $
- $ 1\leq\ A\ _\ i\leq 10^{15}\ (1\leq\ i\leq\ N) $
- $ 1\leq\ B\ _\ i\leq 10^{15}\ (1\leq\ i\leq\ N) $
- 入力はすべて整数

### Sample Explanation 1

例えば、次のように操作をすることで $ A $ と $ B $ を等しくすることができます。 - $ A\ _\ 2 $ に $ 2 $ を加える。コストが $ 2 $ かかり、$ A=(3,3,4,1,5) $ となる。 - $ A\ _\ 4 $ に $ 1 $ を加える。コストが $ 1 $ かかり、$ A=(3,3,4,2,5) $ となる。 - $ A\ _\ 3 $ に $ 3 $ を加える。コストが $ 3 $ かかり、$ A=(3,3,7,2,5) $ となる。 - $ A $ を $ (3,3) $ と $ (7,2,5) $ に分割し、順番を入れ替える。コストが $ 1 $ かかり、$ A=(7,2,5,3,3) $ となる。 - $ A\ _\ 3 $ に $ 1 $ を加える。コストが $ 1 $ かかり、$ A=(7,2,6,3,3) $ となる。 - $ A\ _\ 4 $ に $ 2 $ を加える。コストが $ 2 $ かかり、$ A=(7,2,6,5,3) $ となる。 - $ A\ _\ 1 $ に $ 2 $ を加える。コストが $ 2 $ かかり、$ A=(9,2,6,5,3) $ となる。 かかるコストの合計は $ 2+1+3+1+1+2+2=12 $ となります。 コストの合計を $ 11 $ 以下にして $ A $ と $ B $ を等しくすることはできないため、$ 12 $ と出力してください。

### Sample Explanation 2

例えば、次のように操作をすることで $ A $ と $ B $ を等しくすることができます。 - $ A\ _\ 1 $ に $ 6 $ を加える。コストが $ 6 $ かかり、$ A=(9,1,4,1,5) $ となる。 - $ A\ _\ 2 $ に $ 1 $ を加える。コストが $ 1 $ かかり、$ A=(9,2,4,1,5) $ となる。 - $ A\ _\ 3 $ に $ 2 $ を加える。コストが $ 2 $ かかり、$ A=(9,2,6,1,5) $ となる。 - $ A\ _\ 4 $ に $ 4 $ を加える。コストが $ 4 $ かかり、$ A=(9,2,6,5,5) $ となる。 - $ A\ _\ 5 $ に $ -2 $ を加える。コストが $ 2 $ かかり、$ A=(9,2,6,5,3) $ となる。 かかるコストの合計は $ 15 $ となります。 コストの合計を $ 14 $ 以下にして $ A $ と $ B $ を等しくすることはできないため、$ 15 $ と出力してください。

### Sample Explanation 3

入力や答えが $ 32\operatorname{bit} $ 整数に収まらない場合があります。

## 样例 #1

### 输入

```
5 1
3 1 4 1 5
9 2 6 5 3```

### 输出

```
12```

## 样例 #2

### 输入

```
5 1000000000
3 1 4 1 5
9 2 6 5 3```

### 输出

```
15```

## 样例 #3

### 输入

```
22 467772225675200
814424018890229 837987908732596 281175505732576 405797525366223 319378664987871 305374284356649 519144936694626 316916938328237 590332737480143 506785561790072 945769796193819 365498597798550 5386616044591 672368930784037 478017750715806 340276460237787 176509793332130 2734777402752 677509027289850 250325127275409 260270543315523 103584313625431
720386673780641 77160494100361 540947273460639 255177791002759 969333325196025 477751866935037 369600749728569 466236682780196 343161112138696 541310338013515 42740499599240 165778332156355 618106559852784 16582487395877 591851763813728 221861304303645 982850624742022 728669467505250 337968530842725 746724490610504 61587851254728 451153536869240```

### 输出

```
4370668608634071```

# 题解

## 作者：sunzz3183 (赞：19)

# [ABC328G] Cut and Reorder 题解

## 题意

给定两个长度为 $n$ 的序列 $a,b$ 和一个数字 $c$，有两种操作。

- 把 $a$ 分成任意 $x$ 个子段，并任意摆列他们的顺序，组成新的 $a$ 序列，代价为 $c\times (x-1)$。

- 把 $a_i$ 加上 $x$（$x$ 为任意**整数**）代价是 $|x|$。

问把 $a$ 变成 $b$ 的最小代价。

## 分析

发现第一个操作只会做一次，更进一步发现先做一次操作一，然后把每个数更改，代价就是第一次操作的代价加上 $\sum_{i=1}^n |a_i-b_i|$。后面的好做，前面的因为 $n\leq 22$ 所以考虑状压，枚举 $a_i$ 每次填入了哪个位置，如果当前数填的位置恰好是上一个数的后一个位置，就不会有 $c$ 的代价。

记录状态 $f_{S,i}$ 为当前被填的位置状态为 $S$，上一次填的位置为 $i$，每次转移时把 $|S|$ 看作阶段，式子很好写：

$$ 
f_{S\cup \left \{ j \right \},j}=
\begin{cases} 
f_{S,i}+|b_j-a_{|S|+1}|&j=i+1
\\f_{S,i}+|b_j-a_{|S|+1}|+c&otherwise
\end{cases}
$$

分析时间复杂度（$O(2^nn^2)$）和空间复杂度（$O(2^nn)$）发现都不足以通过此题，考虑优化。

换一种方法，不考虑上一个数填在哪里，我们可以在确定当前数字填在哪里后可以直接朝后枚举每一个位置，如果没有填过数字就可以填下一个数字，这样就不用记录 $f$ 的第二维和分类讨论。代码如下：

```cpp
f[0]=-c;//第一个次填数不需要+c，所以先减去
for(int i=0;i<1<<n;i++){
    int now=__builtin_popcountll(i);//当前填了多少个数字，那么当前要填的数字就是 a_sum(a从0开始编号)
    for(int j=0;j<n;j++)
        if(!(i>>j&1)){//当前位置可以填数
            int t=i,sum=c;//t:当前状态，sum：从当前数往后填数后的代价
            for(int l=j,k=now;!(i>>l&1)&&l<n;l++,k++){//l：位置 k：填第几个数
                t|=1<<l;
                sum+=abs(b[l]-a[k]);
                f[t]=min(f[t],f[i]+sum);//转移
            }
        }
}
```


这样空间复杂度为 $O(2^n)$，时间复杂度为 $O(2^nn)$，可以通过此题。

### 时间复杂度计算

实际上最后一个循环是枚举了一个子段并填进去，而长度为 $k$ 的子串所处的集合一共有 $2^{n-k}$ 个，子段的起始位置一共有 $n-k+1$ 个，所以转移总数为

$$\sum_{k=1}^n 2^{n-k}(n-k+1)=2^n(n-3)+2=O(2^nn)$$

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int N=22;
int n,c;
int a[N],b[N];
int f[1<<N];
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    n=read();c=read();
    for(int i=0;i<n;i++)a[i]=read();
    for(int i=0;i<n;i++)b[i]=read();
    memset(f,0x3f,sizeof(f));
    f[0]=-c;
    for(int i=0;i<1<<n;i++){
        int now=__builtin_popcountll(i);
        for(int j=0;j<n;j++)
            if(!(i>>j&1)){
                int t=i,sum=c;
                for(int l=j,k=now;!(i>>l&1)&&l<n;l++,k++){
                    t|=1<<l;
                    sum+=abs(b[l]-a[k]);
                    f[t]=min(f[t],f[i]+sum);
                }
            }
    }
    printf("%lld",f[(1<<n)-1]);
    return 0;
}
```


---

## 作者：cancan123456 (赞：4)

容易发现最优决策一定是对 $A$ 仅执行 $1$ 次 $1$ 操作，然后直接通过 $n$ 次 $2$ 操作将其变为 $B$。

考虑状压，设 $f_{i,S}$ 为考虑了 $A_{1\sim i}$ 要放到 $B$ 中的位置，位置集合为 $S$ 的最小代价。

转移，考虑枚举所有区间 $[i+1,j]$，设将其放到 $B$ 中 $[k,k+j-i-1]$ 位置，那么 $S$ 与 $[k,k+j-i-1]$ 交集为空，并付出 $\sum_{i=1}^{j-i}|A_{i+j}-B_{k+j}|+C$ 的代价（其中 $+C$ 是因为段数加一），并转移到 $i'=j,S'=S\cup[k,k+j-i-1]$。

边界条件为 $f_{0,0}=0$，答案为 $f_{n,\{1,2,3,\dots,n\}}-C$，因为最后一段不需要 $+C$，需要减去，我们发现 $i=\operatorname{popcount}(S)$，因此可以省去一维。

时间复杂度看似为 $O(n^22^n)$，实则 $O(n2^n)$，为什么呢？设区间 $[k,k+j-i-1]$ 长度为 $l$，那么其会被枚举 $2^{n-l}$ 次，所以总时间复杂度为：

$$O\left(\sum_{l=1}^n2^{n-l}n\right)=O(n2^n)$$

可以通过此题。

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;
ll a[22], b[22], f[1 << 22], w[22][23][22];
ll min(ll a, ll b) {
	return a < b ? a : b;
}
ll abs(ll x) {
	return x < 0 ? -x : x;
}
int main() {
	int n;
	ll c;
	scanf("%d %lld", &n, &c);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &a[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%lld", &b[i]);
	}
	for (int l1 = 0; l1 < n; l1++) {
		for (int r1 = l1 + 1; r1 <= n; r1++) {
			for (int l2 = 0; l2 < n; l2++) {
				int len = r1 - l1;
				if (l2 + len <= n) {
					for (int i = 0; i < len; i++) {
						w[l1][r1][l2] += abs(a[i + l1] - b[i + l2]);
					}
				}
			}
		}
	}
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for (int S = 0; S <= (1 << n) - 1; S++) {
		int i = __builtin_popcount(S);
		for (int j = i + 1; j <= n; j++) {
			int len = j - i;
			for (int k = 0; k + len <= n; k++) {
				if (((S >> k) & ((1 << len) - 1)) == 0) {
					int T = S | (((1 << len) - 1) << k);
					f[T] = min(f[T], f[S] + w[i][j][k] + c);
				}
			}
		}
	}
	printf("%lld", f[(1 << n) - 1] - c);
	return 0;
}
```

---

## 作者：_fairytale_ (赞：3)

感谢 [@lyc1001](https://www.luogu.com.cn/user/627867)，给我讲懂了。/kt/bx

看到 $n\le 22$，考虑状压 DP。

可以把题目的两种操作看作，把 $a$ 数组划分成若干段，再一段一段填进 $b$ 数组中。

设 $f[i][S]$ 为 $a$ 数组中前 $i$ 个数填进 $b$ 数组中状态为 $S$ 的位置上的最小花费。

在状态转移的时候，我们使用刷表法而不用填表法，即用已知的状态 $S$ 去更新未知的状态 $S'$。

我们从小到大枚举状态 $S$，注意到 $i$ 实际上就是 $popcount(S)$，所以可以直接把这一维优化掉。此时 $f[S]$ 已经被更新好，我们接着要枚举一个 $st$，表示从 $b$ 数组中的哪里开始填进去，再枚举一个 $len$，表示 $a$ 数组下一段填进 $b$ 数组的长度。设填进去后的状态为 $S'$，那么转移方程为：
$$
f[S']=min(f[S'],f[S]+\sum_{j=i+1}^{i+len}|b_{j-i+st-1}-a_j|+c)
$$

注意到这样转移会多算一次花费 $c$，所以可以直接把 $f[0]$ 设为 $-c$，后面的 $\sum$ 可以在枚举的时候同时算好，所以复杂度是 $\mathcal O(2^nn^2)$。

```cpp
#include<bits/stdc++.h>
#define re register
#define rep(x,a,b) for(re int (x)=(a);(x)<=(b);++(x))
using namespace std;
#define int long long
#define maxn 25
int n,c;
int a[maxn],b[maxn];
int f[(1<<22)+5];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n>>c;
    rep(i,1,n)cin>>a[i];
    rep(i,1,n)cin>>b[i];
    memset(f,0x3f,sizeof f);
    f[0]=-c;
    rep(S,0,(1<<n)-1){
    	int i=__builtin_popcount(S);
		rep(st,1,n){
    		int sum=0,Snew=S;
    		//st+len-1<=n && i+len<=n -> len<=n+1-st&&len<=n-i
    		rep(len,1,min(n-i,n+1-st)){
    			int aend=i+len,bend=st+len-1;
    			if((S>>(bend-1))&1)break;
    			sum+=abs(a[aend]-b[bend]);
    			Snew|=(1<<(bend-1));
				f[Snew]=min(f[Snew],f[S]+sum+c);
			}
		}
	}
	cout<<f[(1<<n)-1];
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：2)

## 题目大意

给你两个长度为 $N$ 的序列 $A,B$ 和常数 $C$。你可以对 $A$ 进行如下操作：

- 将 $A_i$ 加上 $k$，产生 $|k|$ 的代价。

- 将 $A$ 分成 $X$ 段，并以任意顺序将这些段重新拼接，产生 $(X-1)C$。

最小化使得 $A$ 和 $B$ 完全相等的代价。

## 题目分析

水。

首先，这两个操作是互不影响的。我们肯定要先将第二种操作的效果给可视化。

初始的 $A_i$ 最终到位置 $j$，类似于二分图的匹配。不妨先指定每个 $A_i$ 最终会到达的位置 $j$，则第一种操作的代价是固定的，第二种操作的作用则是让它们到达指定的位置。最朴素的是直接分成 $N$ 段然后重排，但如果存在一段区间指向一段区间，则可以直接合并，代价更小。

结合 $N$ 的范围，不难想到状压 dp。具体的，我们设 $dp_{i,S}$ 表示已经处理好 $A$ 的前 $i$ 个元素，$B$ 中的元素是否被匹配的最小代价。然后对于每一个 $i$，枚举连续的区间，再看 $B$ 中没被匹配的连续区间有哪些（找 $B$ 的连续区间可以用位运算达到 $O(1)$），暴力计算贡献并转移即可。这样的暴力 dp 的空间复杂度为 $O(2^nn)$，时间复杂度为 $O(2^nn^3)$。都无法接受。

注意到对于每一个 $i$，对应集合的 $1$ 的个数是固定的，剪枝即可。这样状态设计只需要 $dp_S$，对应的 $i$ 只要求个 $1$ 的个数是多少。而计算贡献可以直接 $O(n^3)$ 预处理，这样空间复杂度 $O(2^n)$，时间复杂度 $O(2^nn^2)$，常数很小，没有刻意卡都[极限](https://atcoder.jp/contests/abc328/submissions/47498978)通过。

#### update:删除了卡时限过的代码，并更新了更加可靠的写法。

事实上，我们可以不枚举 $i$，直接枚举集合，因为一个集合的子集总是在自己之前被处理。

在此基础上枚举可行的区间，代码常数大大减小，也简洁了许多。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =3e5+5,M=4.2e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=998244353,bas=131;
using namespace std;
int n,c,a[N],b[N],f[M],ct[M],ans;
inline int bitcount(int x){
    int ans=0;
    while(x)ans++,x-=x&-x;
    return ans;
}
inline bool ok(int l,int r,int s){
    return !((s>>l-1)%(1<<r-l+1));
}
inline int get(int l,int r){
    int ans=(1<<r-l+1)-1;
    return ans<<l-1;
}
ll cs[25][25][25][25];
signed main(){
    n=read(),c=read();
    int S=(1<<n)-1;
    rep(i,0,S)ct[i]=bitcount(i);
    rep(i,1,n)a[i]=read();
    rep(i,1,n)b[i]=read();
    rep(i,1,n)ans+=abs(a[i]-b[i]);
    rep(i,0,S)f[i]=llf;
    rep(l,1,n)rep(r,l,n){
        int len=r-l+1;
        rep(Ll,1,n-len+1){
            int Rr=Ll+len-1;
            rep(i,l,r)cs[l][r][Ll][Rr]+=abs(a[i]-b[Ll+i-l]);
        }
    }
    f[0]=0;
    rep(s,0,S){
    	rep(j,1,n)rep(k,j,n){
			if(ok(j,k,s)){
				int del=k-j+1,i=ct[s]+del;     	   
				int nxs=s|get(j,j+del-1),sm=f[s]+c;
        	    if(s==0)sm-=c;
           		sm+=cs[i-del+1][i][j][j+del-1];
            	f[nxs]=min(f[nxs],sm);
        	}else break;
		}
	}
    ans=min(ans,f[S]);
    pf(ans);
    return 0;
}
```


---

## 作者：OMG_wc (赞：2)

这题的操作是每次从 $A$ 数组里选一个线段，最后拼起来组成一个新的数列 $A^{\prime}$，总花费就是 $C$ 乘以段数 $-1$，再加上第二个操作 $\sum\limits_{i=1}^n |A_i^{\prime}-B_i|$。

做法就是状压 DP，考虑 $B$ 数组的前 $i$ 项对应的 $A$ 数组子集为 $f_s$。转移为 $f_s$ 每次扩展一段区间 $[x,y]$，保证区间内元素和 $s$ 是不重复的，花费为 $C+\sum\limits_{j=x}^{y}|A_j-B_{i+1+j-x}|$。

这样枚举区间 $[x,y]$ 虽然是 $O(n^2)$ 的，但只要遇到重复就 `break`，总时间复杂度 $O(2^n\cdot n)$，这是因为：

长度为 $k$ 的区间有 $n+1-k$ 个，转移时都是不交的集合，这样的集合有 $2^{n-k}$ 种，所以 $\sum\limits_{k=1}^n2^{n-k}(n+1-k)=2^nn-2^n+1$。（就是一个等差比数列很好推）

[代码点我](https://atcoder.jp/contests/abc328/submissions/47513356)








---

## 作者：elbissoPtImaerD (赞：1)

纸老虎。

考虑将操作一一次一次拆开考虑。

考虑 dp：设 $f_{S}$ 表示 $a$ 中 $S$ 状态对应的集合（$S$ 第 $i$ 位为 $1$ 那么 $a_i$ 被使用）生成 $b$ 前 $\operatorname{popcount}(S)$ 个数的最小代价。

转移自然是枚举新的一段区间 $[l,r]$ 加入 $S$，代价是 $\sum \limits _ {i=0}^{r-l} |a_{l+i} - b_{\operatorname{popcount}(S)+i}|+C$，前提条件是 $[l,r]$ 和 $S$ 无交。

最后答案即为 $f_{U}-C$。

细节看代码。
```cpp
il void Solve()
{
  int n;
  LL m;
  rd(n),rd(m);
  sd vector<LL>a(n),b(n);
  for(LL&x:a) rd(x);
  for(LL&x:b) rd(x);
  #define lim (1<<n)
  sd vector<LL>f(lim,LONG_LONG_MAX>>1);
  f[0]=0;
  for(int S=0;S<lim;++S)
  {
    const int cnt=__builtin_popcount(S);
    for(int l=0;l<n;++l)
    {
      LL s=m;
      auto F=[&](int l,int r){return (1<<r+1)-(1<<l);};
      for(int r=l,p=cnt;r<n;++r,++p)
        if(S>>r&1) break;
        else s+=sd abs(a[r]-b[p]),cn(f[S|F(l,r)],f[S]+s);
    }
  }
  wrt(f[lim-1]-m);
  return;
}
```

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/abc328/submissions/47519966)。

---

## 作者：LCat90 (赞：1)

首先明确，我们可以先进行 split 操作，然后容易地计算答案。

看到 $n=22$，我们考虑状压。

并且单次转移，我们只使用 $1$ 个 $c$，即只处理连续的一段。

关于状态的设计，我们把 $a$ 和 $b$ 都考虑进去，设 $dp_{i,S}$ 表示将 $[a_1,a_i]$ 对应到 $b_j$（$S$ 状态的 $j$ 位置为 $1$）的最小花费。

容易发现 $i$ 和 $\text{popcount}(S)$ 相等，因为一一对应。

转移本质上就是将 $[i+1,k]$ 填到 $S$ 中目前一段连续的区间（全为 $0$），于是我们枚举这个区间的左右端点即可，根据长度算出 $k$。

时间复杂度是 $O(n2^n)$。不是 $n^2$。证明如下：

我们把在 $S$ 中枚举 $[l,r]$ 的过程等价成：枚举一段区间 $[l,r]$，其中的 $S_i$ 均为 $0$，枚举对应的 $S$。

考虑枚举连续区间长度 $len$，复杂度实际上是 $\sum_{i=1}^n (n-i+1)\times 2^{n-i}$，即区间可能存在的位置乘上其它位置 $S$ 随便取二点方案。

上式一定严格小于 $n\times \sum_{i=1}^n 2^i=n\times (2^{n+1}-1)$，故时间复杂度为 $O(n2^n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 23;
int n, c, a[N], b[N], dp[1 << 22 + 2]; 
int popcount(int x) {
	if(x == 0 or x == 1) return x;
	return popcount(x / 2) + x % 2;
}
signed main() {
	memset(dp, 0x3f, sizeof dp); 
	cin >> n >> c;
	for(int i = 1;i <= n; ++i) cin >> a[i];
	for(int i = 1;i <= n; ++i) cin >> b[i];
	dp[0] = 0;
	for(int i = 0;i < (1 << n) - 1; ++i) {
		int x = popcount(i);
		 // 接着 [1,i] 注意，可以随意选取一段 
		for(int l = 1;l <= n; ++l) {
			int sub = i, sum = c, add = 1; 
			if(!(i & (1 << (l - 1))))
				for(int k = l;k <= n; ++k) { // 连续的一段的转移 [l,r] 
					if(i & (1 << (k - 1))) break ;
					sub |= 1 << (k - 1); add = k - l + 1; 
					sum += abs(b[k] - a[x + add]); 
					dp[sub] = min(dp[sub], dp[i] + sum); 
				}
		}
	}
	cout << dp[(1 << n) - 1] - c << "\n"; // 段数 -1 刀 
	return 0;
}
/* 
假设我们第一步直接重新乱切
后面就可以 O(n) 的计算答案  
考虑状态的设计，
定义 dp{S} 表示我们现在已经确定了状态 S（s_i=1 说明 b_i 已经对应并计算）+
那些 b 的话，我们是用的 [1, i] 去填充的  
现在我们采用刷表法进行转移 
单次转移，我们就考虑一个连续段即可 
然后 i = popcount(S)，即 1 的个数 
*/
```

---

## 作者：LYY_yyyy (赞：1)

AT官方题解做法。赛时没想出来有点菜了。

设 $S$ 为 $A$ 中已经用过的数的集合。$f_S$ 表示使用了 $S$ 集合中的数，与 $B$ 中前 $\left|S\right|$ 个数匹配的最小代价。我们考虑如何转化操作1。我们可以枚举区间 $[l,r]$ 满足 $l\le i \le r,i\notin S$。此时将 $A$ 中  $[l,r]$ 与 $B$ 中 $[\left|S\right|+1,\left|S\right|+r-l+1]$ 进行匹配的代价为 $cost=c+\displaystyle\sum_{i=l}^{r} \left| a_i-b_{\left|S\right|+i-l+1}\right|$，依据这个进行转移即可。于是本题解决。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;ll c,a[31],b[31];
ll dp[1<<22];
inline ll abss(ll x){
	return x<0?-x:x;
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>c;for(int i=0;i<n;i++) cin>>a[i];for(int i=0;i<n;i++) cin>>b[i];
	for(int i=1;i<(1<<n);i++) dp[i]=1e18;dp[0]=-c;
	for(int i=0;i<(1<<n);i++)
	{
		for(int l=0;l<n;l++)
		{
			ll cost=c;int cnt=-1;int be=__builtin_popcount(i);
			for(int r=l;r<n;r++)
			{
				if((i>>r)&1) break;cnt++;
				cost+=abss(b[be+cnt]-a[r]);
				dp[i|(1<<r+1)-(1<<l)]=min(dp[i|(1<<r+1)-(1<<l)],dp[i]+cost);
			}
		}
	}
	cout<<dp[(1<<n)-1];
	return 0;
}
```

---

## 作者：roger_yrj (赞：0)

## 解题思路

首先肯定是先做操作一再做操作二。当做好操作一时，操作二也确定了，答案也确定了。所以说，找的就是操作一的切法。

先看看数据范围：

$\large{1\le N\le 22}$

一眼状压dp。我们考虑每次从 $a$ 中切出一段扔到答案序列中。

设 $f_s$ 为将 $a$ 的子集 $s$ 填入答案序列。

对于每个 $s$，每次枚举 $l,r$，将 $a_l$ ~ $a_r$ 切出来扔到答案序列中，设新的状态为 $ss$。

$f_{ss}=f_s+c+\sum_{i\in[l,r]}|a_i-b_{cnt_s+i-l+1}|$

时间复杂度 $O(n^22^n)$

这题的时间是 $2.8s$，所以这个复杂度能过。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N=30,NN=(1<<22)+10; 
int n,cnt[NN];
ll a[N],b[N],f[NN],c;//注意开 long long 
int main(){
	memset(f,0x3f,sizeof(f));
	cin>>n>>c;
	for(int i=0;i<n;i++)scanf("%lld",&a[i]);
	for(int i=0;i<n;i++)scanf("%lld",&b[i]);//注意这里a和b下标从0开始 
	for(int i=1;i<(1<<n);i++)cnt[i]=cnt[i>>1]+(i&1);
	f[0]=-c;//第一段不用加 c 
	for(int s=0;s<(1<<n);s++){
		for(int i=0;i<n;i++){
			ll t=c;int ss=s;
			for(int j=i;j<n;j++){
				if(s&(1<<j))break;
				t+=abs(a[j]-b[cnt[ss]]);
				ss|=(1<<j);
				f[ss]=min(f[ss],f[s]+t);
			}
		}
	}
	cout<<f[(1<<n)-1];
}
```

---

## 作者：Assembly_line (赞：0)

[ABC328G](https://atcoder.jp/contests/abc328/tasks/abc328_g)。

参考了[题解](https://zhuanlan.zhihu.com/p/666457575)和官方题解，基本上是复读。

场上没想到，难过。

容易发现的是重排操作只用做 $1$ 次。考虑最后的匹配情况：$(A_{p_1},A_{p_2},...,A_{p_n})$ 与 $(B_1,B_2,...,B_n)$，加减操作的答案显然是 $\sum_{i=1}^n|A_{p_i}-B_i|$。需要计算重排操作的代价。

最简单的操作方法就是每个数都花费一次代价放过去。在确定最终排列的情况下，显然操作次数要尽可能小，需要减少一些冗余操作。如果 $A_{p_i},A_{p_{i+1}}...$ 在原序列中已经连续，显然可以把它们一起操作到最终的序列中。

此时已经得出正解：设 $f_{S}$ 为已经将 $A$ 中 $S$ 集合所对应的元素操作完毕，转移就枚举 $A$ 中一个连续段进行转移。

时间复杂度证明：对于一个长度为 $k$ 的连续段，有 $2^{n-k}$ 个集合会对它进行转移，共有 $n-k+1$ 个这样的连续段，复杂度为 $\sum_{k=1}^n2^{n-k}(n-k+1)$，为 $O(2^nn)$。

[code](https://atcoder.jp/contests/abc328/submissions/47620087)。

---

## 作者：zhongpeilin (赞：0)

# 题目大意:
现在有两个长度为 $N$ 的序列 A，B 现在有两种操作：  
1. 将他分成 $P$ 段，然后将他们排列，花费 $(P-1)C$。
2. 花费 $|k|$，并选一个 $i$，将 $a_{i} = a_{i} + k$。

现在请输出最小使得 $A = B$ 的最小代价。  
# 解题思路：
首先，不难发现第一个操作最多执行一次，因为将一次操作变成两次一定不优，那么我们发现干完 $1$ 操作时，答案还要加上 $\sum |a_{i}-b_{i}|$。  
而 $N \le 22$，考虑状压，设 $dp_{S}$ 表示已经确定最终状态下集合为 $S$ 的位置，现在所需要花的最小代价，这里要加上分段的代价和 $\sum_{i \in S} |a_{i} - b_{i}|$。  
我们为什么不用再枚举个 $i$ 表示有多少个数确定了？因为 $S$ 中 `1` 的个数就是已经确定的个数，而我们每次都是一个一个前缀确定的，所以是一定的。  
那么转移的时候就是枚举下一个分割点 $j$，然后再枚举对应的 $B$ 的起始位置，然后再一一对应上 $a_{i}$ 和 $b_{i}$ 的差值，这是 $O(2 ^ n \times n^2)$ 的，为什么不是 $O(2^n \times n^3)$ 呢？因为复杂度均摊是这样 $\dots$   
我们还是考虑优化，只需要枚举对应 $B$ 中的起点，然后用指针维护 A 的当前位置，一点一点右移。  
这样是 $O(2^n \times n)$ 的，还是因为均摊 $\dots$  
怎么处理 $(P-1) \times C$ 呢？我们只需要将 $dp_{0} = -C$ 就行。  
# CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, C, a[30], b[30], dp[5000000];
signed main(){
	cin >> n >> C;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) cin >> b[i];
	
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = -C;
	for(int i = 0; i < (1 << n); i++){
		int cnt = 0, bci = i;
		while(bci){
			cnt += bci % 2;
			bci /= 2;
		}
		for(int j = 1; j <= n; j++){
			if((i & (1 << (j - 1))) > 0) continue;
			
			int S = i, sum = 0;
			for(int k = j, l = cnt; k <= n; k++){ //维护一个A右移的指针
				if((i & (1 << (k - 1))) > 0) break;
				S |= (1 << (k - 1));
				sum += abs(a[++l] - b[k]);
				
				dp[S] = min(dp[S], dp[i] + C + sum);
			}
		}
	}
	cout << dp[(1 << n) - 1] << endl;
	return 0;
}

---

## 作者：DengDuck (赞：0)

首先感谢群友成功地让我意识到了昨天看错了题并会了这题。

我们发现这题可以只做一次操作一，因为多次操作一的内容可以合并成一次。

然后我们就发现 $n$ 很小，考虑状压，我们设 $f_{S}$ 表示目前我们把集合 $S$ 里面的所有位置用于填充 $B$ 数组的前 $|S|$ 位，考虑转移。

显然转移就是要找到一个新的划分的区域，然后用于填充 $B$ 数组 $|S|$ 之后之后的几位，考虑枚举一个与 $S$ 无交的区间然后直接填充算加减的贡献就行了。

注意这里的时间复杂度是 $\mathcal O(n^22^n)$ 的，略需剪枝优化，所以需要注意一些实现细节。

我们应该枚举左端点，然后向右拓展，更新别的状态，要是拓展到 $S$ 中的元素，就停止拓展。

同时我们可以求出加减的贡献，这个也比较简单。

其他就没啥难点了。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=25;
const LL M=(1<<22)+5;
//const LL mod;
//const LF eps;
//const LL P;
LL lowbit(LL x)
{
	return x&-x;
}
LL popcount(LL x)
{
	LL cnt=0;
	while(x)
	{
		cnt++;
		x-=lowbit(x);
	}
	return cnt;
}
LL n,c,a[N],b[N],f[M],lst[N];
int main()
{
	cin>>n>>c;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<n;i++)cin>>b[i];
	LL cnt=(1<<n)-1;
	memset(f,127,sizeof(f));
	f[0]=-c;
	for(LL i=0;i<=cnt;i++)
	{
		LL cnt=popcount(i);
		for(int l=0;l<n;l++)
		{
			if((i>>l)&1)continue;
			LL k=c;
			for(int r=l,t=cnt;r<n;r++,t++)
			{
				if((i>>r)&1)break;
				
				k+=abs(a[r]-b[t]);
				LL to=i|((1ll<<(r+1))-((1ll<<l)));
				f[to]=min(f[to],f[i]+k);
			}
		}
	}
	printf("%lld",f[cnt]);
	return 0;
}
//RP++
```

---

## 作者：liangbowen (赞：0)

[blog](https://www.cnblogs.com/liangbowen/p/17826815.html)。剩下几分钟的时候胡出来了，但是时间不够，痛失 AK /dk。

---

$N\le22$，显然状压 DP。$dp_s$ 表示确定 $s$ 集合的元素所需的代价（这些元素都放在最前面）。

确定了 $s$ 后，发现会有 $\operatorname{popcount}(s)$ 个元素堆在前面，那么枚举 $[L,R]$ 接在后面，也就是 $[\operatorname{popcount}(s)+1,\operatorname{popcount}(s)+(R-L+1)]$ 的位置。

枚举 $[L,R]$， 需满足 $\forall L\le i\le R, i\notin s$。$dp_{s\cup[L,R]}\gets dp_s+C+\sum\limits_{i=L}^R|a_i-b_{i\text{ 对应的位置}}|$。

直接枚举 $[L,R]$， 时间复杂度 $O(n^22^n)$。枚举出 $L$ 后 $[L,R]$ 可以递推，时间复杂度 $O(n2^n)$。

[code](https://atcoder.jp/contests/abc328/submissions/47518376)，时间复杂度 $O(n2^n)$。

---

## 作者：allenchoi (赞：0)

## 前言：  
离 AK 最近的一次...  
场上还剩十几分钟的时候口胡出来，但没时间写了...  
## 科技：  
状压 DP  
## 思路：  
首先明显可以先排好序再做加减操作。  
然后容易想到枚举 $A$ 中的一段对应 $B$ 中长度相等的一段。  
但是不能重复覆盖，再结合 $n$ 的范围想到状压 DP。  
我们设 $dp_{p,t}$ 表示已经确定好 $A[1,p]$ 在 $B$ 中对应的位置，已用掉 $B$ 中包括在集合 $t$ 内的位置时的最小值。  
那么将 $p$ 从左往右扫，再枚举最右一段的左端点 $i(1\le i \le p)$。  
接下来，枚举 $A[1,i-1]$ 可能已用过的 $B$ 的位置的集合 $s$ ，然后枚举在 $B$ 中剩下的位置中哪些区间 $[l,r]$ 可以放下区间 $[i,p]$（需满足 $s $ 与 $[l,r]$ 交集为空）。设新的集合为 $t$（$s$ 与 $[l,r]$ 的并），那么 $dp_{p,t}=\min(dp_{p,t},dp_{i,s}+c+\sum \left| A_x-B_y\right|)$。  
这样时间复杂度是 $O(n^32^n)$ 的（枚举区间时，已知长度，枚举左端点即可；最后一项预处理，后面会讲），过不了。  
发现枚举可能集合的时候很多是无用的，显然 $i$ 可能的集合 $s$ 必然满足 $\operatorname{popcount(s)}=i$。  
于是我们可以提前将所有集合塞到它们的 $\operatorname{popcount}$ 所对应的链表里面去（代码中用链式前向星实现），这样我们可以快速遍历 $i$ 所有可能的集合，时间复杂度去掉一个 $n$（所有集合数量 $O(2^n)$，枚举 $p,[l,r]$ 都是 $O(n)$ 的，所以总复杂度 $O(n^22^n)$）。  
打个[代码](https://www.luogu.com.cn/paste/ux2yo61x)，计算量 7e8，由于时限较大且 AT 机子性能好，所以可过。  
还有一个问题：$dp$ 数组似乎太大了，会爆空间。  
解决这个问题很简单，把第一维删掉，因为集合 $s$ 只能对应一个 $i(=\operatorname{popcount(s)})$。     
为了方便，我们再预处理两个东西：  
$st_{l,r}$ 表示由区间 $[l,r]$ 内所有位置所构成的集合的二进制表达。  
$q_{a,b,l}=\sum_{i=1}^{l}\left| A_{a+i-1}-B_{b+i-1}\right|$。  
注意要令初始状态 $dp_0=-c$。
## 代码：  
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 23,M = (1 << 22) + 5;
int n,tot,st[N][N],head[N],to[M],nxt[M];
ll c,q[N][N][N],a[N],b[N],dp[M];
void add_(int x,int y)
{
	to[++tot] = y;
	nxt[tot] = head[x],head[x] = tot;
}
int pc(int x)
{
	int ret = 0;
	for(;x;x >>= 1) ret += (x & 1);
	return ret;
}
int main()
{
	scanf("%d%lld",&n,&c);
	for(int i = 1;i <= n;i++) scanf("%lld",&a[i]);
	for(int i = 1;i <= n;i++) scanf("%lld",&b[i]);
	for(int i = 1;i <= n;i++)
		for(int j = i;j <= n;j++)
			for(int t = i;t <= j;t++)
				st[i][j] |= (1 << (t - 1));
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++)
			for(int l = 1;l <= min(n - i + 1,n - j + 1);l++)
				q[i][j][l] = q[i][j][l - 1] + abs(a[i + l - 1] - b[j + l - 1]);
	for(int i = 0;i < (1 << n);i++) add_(pc(i),i);
	memset(dp,0x3f3f,sizeof(dp));
	dp[0] = -c;
	for(int p = 1;p <= n;p++)
		for(int i = 0;i < p;i++)
			for(int j = head[i],s;j;j = nxt[j])
			{
				s = to[j];
				for(int l = 1,r = p - i;r <= n;l++,r++)
					if(!(s & st[l][r]))
						dp[s | st[l][r]] = min(dp[s | st[l][r]],dp[s] + c + q[i + 1][l][p - i]);
			}
	printf("%lld\n",dp[(1 << n) - 1]);
	return 0;
}
```

---

