# Boolean Computer

## 题目描述

Alice 有一台可以操作 $w$ 位整数的计算机。该计算机有 $n$ 个寄存器用于存储数值。当前寄存器中的内容为数组 $a_1, a_2, \ldots, a_n$。

该计算机使用所谓的“数字门”来处理这些数据。每个“数字门”以两个寄存器作为输入，并计算这两个寄存器中存储的数值的某个函数。注意，你可以将同一个寄存器作为两个输入。

每个“数字门”由若干比特门组装而成。比特门共有六种类型：与（AND）、或（OR）、异或（XOR）、非与（NOT AND）、非或（NOT OR）、非异或（NOT XOR），分别用 “A”、 “O”、 “X”、 “a”、 “o”、 “x” 表示。每个比特门以两个比特作为输入。对于输入比特 $b_1$、$b_2$，其输出如下表所示：

$$
\begin{matrix}
b_1 & b_2 & A & O & X & a & o & x \\
0 & 0 & 0 & 0 & 0 & 1 & 1 & 1 \\
0 & 1 & 0 & 1 & 1 & 1 & 0 & 0 \\
1 & 0 & 0 & 1 & 1 & 1 & 0 & 0 \\
1 & 1 & 1 & 1 & 0 & 0 & 0 & 1 \\
\end{matrix}
$$

要构建一个“数字门”，需要将 $w$ 个比特门组装成一个数组。一个“数字门”以两个 $w$ 位整数 $x_1$ 和 $x_2$ 作为输入。该“数字门”会将整数拆分为 $w$ 个比特，并将每个输入的第 $i$ 位比特送入第 $i$ 个比特门。最后，将输出的比特重新组合成一个输出数值。

例如，对于 $4$ 位计算机，可以有一个“数字门” "AXoA"（与、异或、非或、与）。对于两个输入 $13 = 1101_2$ 和 $10 = 1010_2$，其输出为 $12 = 1100_2$，因为 $1$ 与 $1$ 得 $1$，$1$ 异或 $0$ 得 $1$，非（$0$ 或 $1$）得 $0$，最后 $1$ 与 $0$ 得 $0$。

现在给定 $m$ 个“数字门”的描述。对于每个门，你需要统计有多少对寄存器对，经过该“数字门”后输出为 $0$。换句话说，求有多少有序对 $(i,j)$，满足 $1 \leq i,j \leq n$，且 $w_k(a_i, a_j) = 0$，其中 $w_k$ 表示第 $k$ 个“数字门”所计算的函数。

## 说明/提示

在第一个测试用例中，输入的二进制数为 $1101$、$1010$、$0110$。输出为 $0$ 的有序对为 $(13, 6)$、$(6, 13)$ 和 $(6, 6)$。如题目所述，$13 \oplus 10 = 10 \oplus 13 = 12$。其他的有序对有 $13 \oplus 13 = 11$，$10 \oplus 10 = 8$，$10 \oplus 6 = 6 \oplus 10 = 4$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 3 1
13 10 6
AXoA
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 7 6
0 1 1 0 1 0 0
A
O
X
a
o
x
```

### 输出

```
40
16
25
9
33
24
```

## 样例 #3

### 输入

```
6 2 4
47 12
AOXaox
AAaaAA
xxxxxx
XXXXXX
```

### 输出

```
2
3
0
2
```

## 样例 #4

### 输入

```
2 2 2
2 0
xO
Ox
```

### 输出

```
2
0
```

# 题解

## 作者：Caro23333 (赞：8)

意料之外情理之中的奇思妙想，很有意思。

首先考虑平凡一些的做法。首先对$a_1,a_2,\dots,a_n$统计$[0,2^w)$中每一个数的出现次数。对于任意一种位运算来说，使得输出为$0$的输入最多有$3$种，这意味着我们可以给每一位枚举至多$3$种情况然后通过先前的统计计算答案。这显然是$O(m3^w)$的，不够优秀。

然后怎么办呢？~~说起来你可能不信，我差点就抄起fwt开始淦了~~

但是思索一下发现fwt$O(mw2^w)$复杂度也不太对，所以大概应该要做到$O(m2^w)$就好了？

思考：位运算的真值表本质上是从$\{0,1\}^2$到$\{0,1\}$的映射，而满足结果为$0$的原像至多有$3$种，这导致了过高的复杂度。能否将它通过某种方式压缩为某个其他东西到$\{0,1\}$的映射，使得合法的原像只有不超过$2$种呢？

答案是肯定的。

首先我们考虑$\textrm{and}$这一位运算，它在输入为$(0,0),(0,1),(1,0)$时输出都为$0$。但是这时能够注意到，假设我们考虑输入的两个数的和，那么当且仅当和为$0$或$1$时输出为$0$。作为一种映射来考虑的话，合法的原像数量减少到了$2$个。

用这种压缩的方法一一验证，发现对于六种位运算都能使得合法原像不多于$2$个。那么我们对于每次查询的每一位，枚举$0,1,2$中合法的那些作为两个输入在当前位的和，最后只要通过已经预处理好的数组来统计答案即可。

那么，我们要预处理什么？实际上是这样一个数组：$cnt_{[s_1,s_2,\dots,s_w]}$表示使得$a_p,a_q$第$i$位的和恰为$s_i$的$(p,q)$的对数。考虑到$s_i\le 2$，所以可以用三进制来大幅简化实现。

具体来说，将输入的每一个数，从二进制直接切换到三进制，但是每一位上的数都不变，然后令$cnt_i$为满足$a_p+a_q=i$的$(p,q)$对数，暴力$O(4^w)$预处理即可。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;
const int MAXN = 30005, MAXS = 550005;
inline int readint()
{
	int res = 0, f = 1;
	char c = 0;
	while(!isdigit(c))
	{
		c = getchar();
		if(c=='-')
			f = -1;
	}
	while(isdigit(c))
		res = res*10+c-'0', c = getchar();
	return res*f;
}
int w,n,m,a[MAXN],b[MAXN],pw[15];
ll tcnt[MAXS],cnt[MAXS]; 
inline int calc(int x)
{
	int res = 0;
	for(int i = 0; i<w; i++)
	    res += ((x>>i)&1)*pw[i];
	return res;
}
char str[15];
inline ll dfs(int k, int now)
{
	if(k==w+1)
	    return cnt[now];
	if(str[k]=='A')
	    return dfs(k+1,now)+dfs(k+1,now+pw[w-k]);
	if(str[k]=='O')
	    return dfs(k+1,now);
	if(str[k]=='X')
	    return dfs(k+1,now)+dfs(k+1,now+2*pw[w-k]);
	if(str[k]=='a')
	    return dfs(k+1,now+2*pw[w-k]);
	if(str[k]=='o')
	    return dfs(k+1,now+pw[w-k])+dfs(k+1,now+2*pw[w-k]);
	if(str[k]=='x')
	    return dfs(k+1,now+pw[w-k]);
}

int main()
{
	w = readint(), n = readint(), m = readint();
	pw[0] = 1;
	for(int i = 1; i<=w; i++)
	    pw[i] = pw[i-1]*3;
	for(int i = 1; i<=n; i++)
	    a[i] = readint(), tcnt[a[i]]++;
	for(int i = 0; i<(1<<w); i++)
	    for(int j = 0; j<(1<<w); j++)
	        cnt[calc(i)+calc(j)] += 1ll*tcnt[i]*tcnt[j];
	while(m--)
	{
        scanf("%s",str+1);
        printf("%lld\n",dfs(1,0));
	}
	return 0;
}

```


---

## 作者：Soulist (赞：6)

~~来水题解了~~

发现真值表不是任意给的，应该和这方面有关，枚举可能的成为答案的对子，然后查表，可以发现真值表上只有两种操作：```A``` 与 ```o``` 是有三种初值情况可以得到 $0$ 的，因此将这两类操作拎出来做，其余暴力。

对于这两类容斥一下即可，设 A 与 o 有 $cnt$ 个，单次查询复杂度为 $\mathcal O(2^{cnt}\times 2^{w-cnt})$。

预处理上需要知道删除某些位之后某种值有多少个，朴素做可以在 $\mathcal O((n+m)2^w)$ 内完成。

---

## 作者：Petit_Souris (赞：5)

只要数据开得大，人人都是发明家！

事实证明，把数据范围开到 $w=16$ 之后，大家都可以爆标！

首先先把原题过一下！我们考虑每一位的限制是什么意思，实际上对于 $\texttt{O,x,a}$，相当于限定对应位上的 $x,y$ 之和为 $0/1/2$；对于 $\texttt{A,X,o}$，相当于限定对应位上的 $x,y$ 之和为 $0/1$，$0/2$，$1/2$。这可以轻松导出一个 $\mathcal O(4^w+q2^w)$ 的做法：首先平方枚举，预处理出三进制下所有 $x+y$ 对应的方案数。查询的时候直接对于 $\texttt{A,X,o}$ 枚举选了哪一个，这样就确定了 $x+y$ 的值了。

接着考虑优化发现 $\texttt{A,X,o}$ 个数比较少的时候这个做法已经可以 work 了，我们考虑一下 $\texttt{O,x,a}$ 比较少的情况。

刚刚做的事情实际上是把大小为 $2$ 的限制拆成了大小为 $1$ 的限制，那么我们不妨试试把大小为 $1$ 的限制拆成大小为 $2$ 的限制。设 $f_{S}$ 表示限制集合为 $S$ 的方案数，那么我们可以这样拆：$f_{0}=\frac{f_{0,1}+f_{0,2}-f_{1,2}}{2}$，这样我们可以对于每个大小为 $1$ 的限制枚举取了这三个中的哪一个（带容斥系数），最后除掉一个 $2^k$ 就行了。

现在剩下的事情就变成了，给定一个三进制数 $X$，要求 $x+y$ 的每一位都和 $X$ 不同，求方案数。这个问题可以扩展一下三维 FWT 的过程，即对于每位做 $a'_0=a_1+a_2,a'_1=a_0+a_2,a'_2=a_0+a_1$。于是我们得到了一个 $\mathcal O(4^w+3^ww+q\min(2^k,3^{w-k}))$ 的做法，其中 $k$ 表示问询中 $\texttt{A,X,o}$ 的个数。当 $k\le 10$ 时用 $2^k$ 的做法，$k>10$ 时用 $3^{w-k}$ 的做法。

能不能再给力一点？其实仔细一想发现这个 $4^w$ 也可以优化掉的。最搞笑的方法是用 FFT（因为这是个加法卷积），但是常数太大了。我们发现由于 $x,y$ 转成三进制之后每位都是 $0$ 或 $1$，所以实际上做三进制不进位加法的 FWT 就是对的了，因为根本不会进位。最终复杂度为 $\mathcal O(3^ww+q\min(2^k,3^{w-k}))$。

其实也不是很外星人，循规蹈矩地一步一步做就能做出来了。爆标了还是很开心的，感谢 z 宝提供的机会。

---

## 作者：Yu_Jie (赞：5)

贡献一种不用脑子的暴力做法。

对每个询问，枚举 $a_x$。因为 $a_x\odot a_y=0$，所以可以确定 $a_y$ 一些位上的取值，其他位任意。统计有多少这样的 $a_y$，这个可以 $O(4^w)$ 预处理。

于是询问的复杂度为 $O(nmw)$，去个重就是 $O(2^wmw)$。$w$ 很讨厌，想办法去掉。

因为运算只有 $6$ 种，可以再预处理：设 $g_{i,j}$ 表示 $a_x$ 为 $i$，$s$ 在六进制下为 $j$ 时 $a_y$ 的取值。用三进制表示，$2$ 为任意。这样的复杂度是 $O(2^w6^ww=12^ww)$。又因为各位是独立的，所以可以将 $w$ 位的数视为两个 $\frac{w}{2}$ 位的数拼接而成。于是变为 $O(12^{w/2}w)$。

总复杂度为 $O(4^w+12^{w/2}w+2^wm)$。最大的点跑了 $1.5\texttt{s}$，好像还挺快？

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mp[6][2]={2,0,0,-1,0,1,-1,1,1,2,1,0};
int w,n,m,t,q,p2[13],p3[13],p6[7],a[4096],f[531441],g[2][64][46656];
int read() {
	int x=0; char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c>='a'&&c<='z'||c>='A'&&c<='Z')
        return c=='A'?0:c=='O'?1:c=='X'?2:c=='a'?3:c=='o'?4:5;
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-48;
	return x;
}
int get(int x,int *p,int i) {return x/p[i]%p[1];}
void dfs(int i,int s,int x,int v) {
    if(i==w) {f[s]+=v; return ;}
    dfs(i+1,s+get(x,p2,i)*p3[i],x,v);
    dfs(i+1,s+2*p3[i],x,v);
}
int main() {
    w=read(); t=read(); q=read(); n=(w+1)/2; m=w-n;
    p2[0]=1; for(int i=1;i<=12;i++) p2[i]=p2[i-1]*2;
    p3[0]=1; for(int i=1;i<=12;i++) p3[i]=p3[i-1]*3;
    p6[0]=1; for(int i=1;i<=6;i++) p6[i]=p6[i-1]*6;
    while(t--) a[read()]++;
    for(int i=0;i<p2[w];i++) if(a[i]) dfs(0,0,i,a[i]);
    for(int l=0;l<2;l++)
        for(int i=0;i<p2[n];i++)
            for(int j=0;j<p6[n];j++)
                for(int k=0;k<(l?m:n);k++) {
                    int v=mp[get(j,p6,k)][get(i,p2,k)];
                    if(~v) g[l][i][j]+=v*p3[k];
                    else {g[l][i][j]=-1; break;}
                }
    while(q--) {
        int x=0,y=0,ans=0;
        for(int i=m-1;i>=0;i--) y+=p6[i]*read();
        for(int i=n-1;i>=0;i--) x+=p6[i]*read();
        for(int i=0;i<p2[w];i++) if(a[i]) {
            int v1=g[0][i%p2[n]][x],v2=g[1][i/p2[n]][y];
            if(~v1&&~v2) ans+=a[i]*f[v1+v2*p3[n]];
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Mr_Wu (赞：3)

虽然每位的位运算不同，但是仍然可以 FWT。只需要对于 FWT 的每一层做不同的变换即可。如果了解 FWT 的根本原理就可以发现这是正确的。$O(mw2^w)$。虽然复杂度劣但很好想。

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<set>
#include<queue>
using namespace std;

typedef long long ll;
const int MAXN=5e5+5;

template<typename T> void chkmax(T& x,T y){if(y>x)x=y;}
template<typename T> void chkmin(T& x,T y){if(y<x)x=y;}

int W,N,M,a[1<<12];char S[12];

double f[1<<12];
void fwt(double* f){
	for(int l=0;l<W;++l){
		for(int i=0;i<(1<<W);i+=(1<<(l+1))){
			for(int j=0;j<(1<<l);++j){
				double f0=f[i|j],f1=f[i|j|(1<<l)];
				if(S[l]=='A'||S[l]=='a'){
					f[i|j]=f0+f1;
					f[i|j|(1<<l)]=f1;
				}else if(S[l]=='O'||S[l]=='o'){
					f[i|j]=f0;
					f[i|j|(1<<l)]=f0+f1;
				}else{
					f[i|j]=f0+f1;
					f[i|j|(1<<l)]=f0-f1;
				}
			}
		}
	}
}
void ifwt(double* f){
	for(int l=0;l<W;++l){
		for(int i=0;i<(1<<W);i+=(1<<(l+1))){
			for(int j=0;j<(1<<l);++j){
				double f0=f[i|j],f1=f[i|j|(1<<l)];
				if(S[l]=='A'||S[l]=='a'){
					f[i|j]=f0-f1;
					f[i|j|(1<<l)]=f1;
				}else if(S[l]=='O'||S[l]=='o'){
					f[i|j]=f0;
					f[i|j|(1<<l)]=-f0+f1;
				}else{
					f[i|j]=0.5*(f0+f1);
					f[i|j|(1<<l)]=0.5*(f0-f1);
				}
			}
		}
	}
}

int main(){
	scanf("%d%d%d",&W,&N,&M);int x;
	for(int i=1;i<=N;++i)scanf("%d",&x),++a[x];
	while(M--){
		scanf("%s",S);
		for(int i=0;i<W-1-i;++i)swap(S[i],S[W-1-i]);
		for(int i=0;i<(1<<W);++i)f[i]=a[i];
		fwt(f);
		for(int i=0;i<(1<<W);++i)f[i]=f[i]*f[i];
		ifwt(f);
		int pos=0;
		for(int i=0;i<W;++i){
			if(S[i]=='a'||S[i]=='o'||S[i]=='x')pos^=1<<i;
		}
		printf("%.0lf\n",f[pos]);
	}
	return 0;
}
```

---

