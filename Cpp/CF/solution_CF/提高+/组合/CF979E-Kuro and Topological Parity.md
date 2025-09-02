# Kuro and Topological Parity

## 题目描述

给定 $n$ 个点，每个点有黑白两种颜色（如果没有颜色，那么你可以把它任意涂成黑色或白色），同时你可以在这个图上任意加入一些边（当然不能加入重边或自环），要求：加入的边必须从编号小的点指向编号大的点

我们称一条好的路径为经过的点为黑白相间的路径，如果一个图好的路径的总数 $\bmod 2=p$，那么我们称这个图为好的图，现在给定你 $n$ 个点的情况，求这 $n$ 个点能组成的好的图的个数，答案对 $10^9+7$ 取模。

## 样例 #1

### 输入

```
3 1
-1 0 1
```

### 输出

```
6```

## 样例 #2

### 输入

```
2 1
1 0
```

### 输出

```
1```

## 样例 #3

### 输入

```
1 1
-1
```

### 输出

```
2```

# 题解

## 作者：da32s1da (赞：37)

考虑一个$O(n)$的做法。

套路一下，把点分为**偶黑**,**偶白**,**奇黑**,**奇白**四类。（比如说，**奇白**代表有**奇数条**路径以该点为结尾且该点为**白色**）

考虑加入一个**白色**点$\ i\ $，我们讨论一下
- 连到**偶黑**，路径条数加上**一个偶数**，奇偶性不变。
- 连到**偶白和奇白**，**不是黑白相间的路径**，路径条数奇偶性不变。
- 下面讨论一下**奇黑**的情况
 - **存在**奇黑，我们可以**挑出一个奇黑点**来**控制奇偶性**，即这个白点作为**奇白和偶白**的方案数各为$2^{i-2}$
 - **不存在**奇黑，它**自己算一条**黑白相间的路径，**只能**作为**奇白**

至此，加入白色点的讨论就结束了。

~~黑色自行分析~~

理解了讨论，代码也很好懂了
```
//f[i][_][ob][ow]表示第i个点，路径条数奇偶性为_，有无奇黑，有无奇白的方案数。
#include<cstdio>
const int mod=1e9+7;
const int N=60;
int n,p,_2[N],a[N];
int f[N][2][2][2],ans;
void add(int &x,int y){
	x+=y;
	if(x>=mod)x-=mod;
}
int main(){
	scanf("%d%d",&n,&p);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	_2[0]=1;
	for(int i=1;i<=n;i++)_2[i]=(_2[i-1]<<1)%mod;
	f[0][0][0][0]=1;
	for(int i=1;i<=n;i++)
	for(int _=0;_<=1;_++)
	for(int ob=0;ob<=1;ob++)
	for(int ow=0;ow<=1;ow++){
		int qwq=f[i-1][_][ob][ow];
		if(a[i]!=0){//白点
			if(ob){//讨论有无奇黑
				add(f[i][_][ob][ow],1ll*qwq*_2[i-2]%mod);
				add(f[i][_^1][ob][ow|1],1ll*qwq*_2[i-2]%mod);
			}else add(f[i][_^1][ob][ow|1],1ll*qwq*_2[i-1]%mod);
		}
		if(a[i]!=1){
			if(ow){
				add(f[i][_][ob][ow],1ll*qwq*_2[i-2]%mod);
				add(f[i][_^1][ob|1][ow],1ll*qwq*_2[i-2]%mod);
			}else add(f[i][_^1][ob|1][ow],1ll*qwq*_2[i-1]%mod);
		}
	}
	for(int ob=0;ob<=1;ob++)
	for(int ow=0;ow<=1;ow++)
	add(ans,f[n][p][ob][ow]);
	printf("%d\n",ans);
}
```

---

## 作者：joke3579 (赞：14)

本题解提供由 $O(n^4)$ 优化至 $O(n)$ 的具体方法。

首先套路按编号顺序加点设计 dp 状态。  
我们设 $f_{i,j,k,l}$ 表示加入了 $i$ 个节点，当前节点中有 $j$ 个偶数条路径以该点结束的黑色节点，当前节点中有 $k$ 个偶数条路径以该点结束的白色节点，当前节点中有 $l$ 个奇数条路径以该点结束的黑色节点。分别记作偶黑点，偶白点，奇黑点。剩下的叫奇白点。

当前的状态数是 $O(n^4)$ 的。  
然后讨论当前加入一个白点。
1. 当前节点成为奇白点。这时需要奇数个奇黑点和任意偶黑点和当前点链接。考虑首先拿出一个奇黑点，则我们从剩下的奇黑点中选择任意个都可以通过控制这个点是否选择来保证选出节点的数量是奇数个，因此这部分的系数是 $2^{l-1}$。偶黑点可以任意选择，因此这部分的系数为 $2^k$。选择白点对路径条数的奇偶性没有贡献，因此乘法原理可得系数为 $2^j \times 2^k \times 2^{l-1} \times 2^{i-1-j-k-l} = 2^{i-2}$。
2. 当前节点成为偶白点。这时需要偶数个奇黑点和任意偶黑点和他链接。做法和上方类似，答案也是 $2^{i-2}$。
3. 当前不存在奇黑点。你发现上述的所有讨论都没法成立。这时我们只能将这个白点变成偶白点，因此贡献为 $2^{i-2} \times 2 = 2^{i-1}$。

黑点同理。

这样做的复杂度是 $O(n^4)$ 的。

考虑进一步压缩状态。  
观察可发现，偶数节点对答案的贡献可以忽略，真正控制贡献情况的是奇白/黑点的存在与否。

我们考虑针对以上观察设计 dp 状态。设 $f_{i,j,k,l}$ 表示 $i$ 个节点，总路径数的奇偶性是 $j$，奇白点的存在性是 $k$，奇黑点的存在性是 $k$。  
这样状态数就被压缩为了 $O(n)$。

然后考虑转移。  
重复上面关于白点的讨论，我们能得到
1. 当前存在奇黑点。因此该白点可以选择成为奇黑点或偶黑点。两种转移的系数均为 $2^{i-2}$。  
	当成为偶黑点时，状态未改变。因此得到转移
	$$f_{i,j,k,l} \leftarrow 2^{i-2}\times f_{i-1,j,k,l}$$
	当成为奇黑点时，状态中 $k$ 定为真，且路径奇偶性反转。因此得到转移
	$$f_{i,\text{!}j,1,l} \leftarrow 2^{i-2}\times f_{i-1,j,k,l}$$
2. 当前不存在奇黑点。该白点只能成为偶黑点。状态里啥都没变。系数为 $2^{i-1}$。
	$$f_{i,j,k,l} \leftarrow 2^{i-1}\times f_{i-1,j,k,l}$$

转移即可。时间复杂度 $O(n)$。

$\text{code :}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define inline __attribute__((always_inline))
#define rep(i,a,b) for (register int i = (a), i##_ = (b) + 1; i < i##_; ++i)
#define pre(i,a,b) for (register int i = (a), i##_ = (b) - 1; i > i##_; --i)
const int N = 55, mod = 1e9 + 7;
int n, p, a[N], f[N][2][2][2], qp[N]; // i个点，路径条数 & 1，奇路径白点数>0，奇黑点数>0

inline int add(int a, int b) { return (a += b) >= mod ? a - mod : a; }

signed main() {
    cin >> n >> p; qp[0] = 1;
    rep(i,1,n) cin >> a[i], qp[i] = (qp[i-1] << 1) % mod;

    f[0][0][0][0] = 1;
    rep(i,1,n) rep(j,0,1) rep(k,0,1) rep(l,0,1) {
        int cont = 1ll * f[i-1][j][k][l] * qp[i - 2] % mod;
        if (a[i] != 0) {
            if (k) {
                f[i][j][k][l] = add(f[i][j][k][l], cont);
                f[i][j^1][k][l|1] = add(f[i][j^1][k][l|1], cont);
            } else {
                f[i][j^1][k][l|1] = add(f[i][j^1][k][l|1], i == 1 ? f[i-1][j][k][l] : add(cont, cont));
            }
        } 
        if (a[i] != 1) {
            if (l) {
                f[i][j][k][l] = add(f[i][j][k][l], cont);
                f[i][j^1][k|1][l] = add(f[i][j^1][k|1][l], cont);
            } else {
                f[i][j^1][k|1][l] = add(f[i][j^1][k|1][l], i == 1 ? f[i-1][j][k][l] : add(cont, cont));
            }
        }
    } 

    cout << add(add(f[n][p][0][0], f[n][p][1][0]), add(f[n][p][0][1], f[n][p][1][1]));
}
```

---

## 作者：leozhang (赞：6)

更好的阅读体验看[这里](https://blog.csdn.net/lleozhang/article/details/83655677)

非常好的dp，非常考dp的能力

很显然是个计数问题，那么很显然要么是排列组合，要么是递推，这道题很显然递推的面更大一些。

那么我们来设计一下状态：

设状态f[i][j][k][p]表示目前到了第i个点，这i个点中有j个白点是奇数条好的路径的结尾，k个黑点是奇数条好的路径的结尾，p个白点是偶数条好的路径的结尾的方案数

可能这个状态本身不是特别好懂，我们详细解释一下：

这样的图的个数会取决于好的路径的条数，而好的路径的条数又可以分成两类：以黑点为结尾和以白点为结尾

那么对于每一个黑点或白点，他只有两种可能：有奇数条好的路径在这结尾和有偶数条好的路径在这结尾。

这样我们就将整个图的点分为了4类：白点是奇数条好的路径的结尾，黑点是奇数条好的路径的结尾，白点是偶数条好的路径的结尾，黑点是偶数条好的路径的结尾。

我们将其中三种扔进状态里，而第四个就可以算出来。

接着我们考虑转移：

分类转移：如果一个节点是白色，那么一个合法的路径一定会从上一个黑点转过来。

而且如果想要影响这个白点奇偶性，上面一定会连上一个奇数黑点，因为偶数黑点对这个白点的奇偶性没有影响。

我们讨论这个白点是奇数白点还是偶数白点：如果这个白点是奇数白点，那么从上面的奇数黑点转过来时，要连1个，3个...奇数个，这样才能保证这个白点是奇数的。

那么如果设之前奇数黑点的数量为k，总方案数2^(k-1)

利用这一点，乘原来方案数转移即可

那么这个白点是偶数白点的转移也同理，总方案数即为2^(k-1)

同理转移即可

最后，考虑其他点：由于别的点对这个白点的奇偶性没有影响，所以对于别的点可以随便连，也就是2^别的点的个数，乘这个东西即可

那么黑点也就同理了。

贴代码：

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#define ll long long
#define mode 1000000007
using namespace std;
ll dp[55][55][55][55];//到了第几个点，奇数白点，奇数黑点，偶数白点 
int n,typ;
int c[55];
ll mul[55];
int main()
{
    scanf("%d%d",&n,&typ);
    mul[0]=1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&c[i]);//0黑1白-1任意 
        mul[i]=(mul[i-1]<<1)%mode;
    }
    ll ret=0;
    if(c[1]==0||c[1]==-1)
    {
        dp[1][0][1][0]=1; 
        if(typ==1&&n==1)
        {
            ret++;
        }
    }
    if(c[1]==1||c[1]==-1)
    {
        dp[1][1][0][0]=1;
        if(typ==1&&n==1)
        {
            ret++;
        }
    }
    for(int i=2;i<=n;i++)
    {
        for(int j=0;j<=i;j++)//奇数白 
        {
            for(int k=0;k+j<=i;k++)//奇数黑 
            {
                for(int p=0;j+k+p<=i;p++)//偶数白 
                {
                    int t=i-j-k-p;//偶数黑 
                    if(c[i]==1||c[i]==-1)
                    {
                        ll s=0;
                        if(j+p)
                        {
                            if(j)
                            {
                                if(!k)
                                {
                                    s+=dp[i-1][j-1][k][p];
                                }else
                                {
                                    s+=mul[k-1]*dp[i-1][j-1][k][p]%mode;
                                }
                                s%=mode;
                            }
                            if(p)
                            {
                                if(k)
                                {
                                    s+=mul[k-1]*dp[i-1][j][k][p-1]%mode;	
                                }
                                s%=mode;
                            }							
                        }
                        s*=mul[j+p+t-1];
                        s%=mode;
                        dp[i][j][k][p]+=s;
                        dp[i][j][k][p]%=mode;
                    }
                    if(c[i]==0||c[i]==-1)
                    {
                        ll s=0;
                        if(k+t)
                        {
                            if(k)
                            {
                                if(!j)
                                {
                                    s+=dp[i-1][j][k-1][p];
                                }else
                                {
                                    s+=mul[j-1]*dp[i-1][j][k-1][p]%mode;
                                }
                                s%=mode;
                            }
                            if(t)
                            {
                                if(j)
                                {
                                    s+=mul[j-1]*dp[i-1][j][k][p]%mode;	
                                }
                                s%=mode;
                            }							
                        }
                        s*=mul[k+p+t-1];
                        s%=mode;
                        dp[i][j][k][p]+=s;
                        dp[i][j][k][p]%=mode;
                    }
                    if(i==n)
                    {
                        if((j+k)%2==typ)
                        {
                            ret+=dp[i][j][k][p];
                            ret%=mode;
                        }
                    }
                }
            }
        }
    }
    printf("%lld\n",ret);
    return 0;
}
```

---

## 作者：Booksnow (赞：2)

# Kuro and Topological Parity

## 题目描述

给定一个 $n$ 个点的图，每个点有黑白两种颜色(可能存在没有颜色的点，你可以将其涂成黑色或白色)。同时，你可以在这张图上加入一些边，要求**不存在重边和自环**且加入的边必须**从编号小的点指向编号大的点**。

称一条好的路径经过的点**黑白相间**。值得注意的是，每个点**自身也是一条好的路径**。如果对于 $p\in \{0,1 \}$，一张图好的路径的数量满足 $\mod 2$ 刚好**等于** $p$，则称这张图是好的图。

给定 $n$ 个点的部分情况，求这 $n$ 个点可以组成的好的图的数量，答案取模 $1000000007$。

**数据范围**

$n\leq 50,p\in \{0,1 \}$

对于每个点的情况，用一个整数 $a_i$ 表示，若 $a_i = 0$，则这个点为黑点，若 $a_i = 1$，则为白点，若 $a_i = -1$，则这个点的颜色不确定。

## 分析

考虑对于一条长度为 $d$ 的合法路径，在其末尾添加一个节点，使其仍然合法。那么，包括新加入的点自身，我们会得到 $d+1$ 条新的合法路径。由于我们最后要对总路径进行**奇偶讨论**，那么这里对 $d$ 我们也进行奇偶讨论。我们不妨设出一下四种表示，奇黑、奇白、偶黑、偶白。

其中，例如奇黑的定义为，**有奇数条以该点为结尾的合法路径的点，且该点颜色为黑**。另外三种表示的定义类似。

注意到 $n\leq 50$，考虑设状态 $f[i][a][b][c]$ 表示当枚举到第 $i$ 个点时，奇黑、奇白、偶黑的数量分别为 $a$，$b$，$c$，而偶白的数量我们显然可以通过这四种状态求得，考虑转移。

假设转移一个白点（黑点的情况类似）。

显然，新增加的合法路径条数一定和这个点有关。一开始，如果不向其进行任何连边，则增加的合法路径数是**奇数**，考虑四种点向其进行连边时可能会出现的情况（注意下述新增合法路径不包括其本身形成的合法路径）：

- 奇、偶白向其连边，不会新增加合法路径，也就不会改变奇偶。

- 偶黑向其连边也只会增加偶数条合法，只有奇黑才**有可能**改变其奇偶。假设有 $j$ 个奇黑，显然必须要经过奇数个奇黑才能改变奇偶，显然，有 $2^{j - 1}$ 次方中不同的取法取得奇数个奇黑，亦有 $2^{j-1}$ 次方中不同的取法取得偶数个奇黑。其他点由于不影响，随便取，共 $2^{i - 1 - j}$ 种可能，则转移则针对这两种奇偶转变讨论即可。

显然，这样做的复杂度是 $O(n^4)$ 的，足以通过此题。但 $da32s1da$ 大佬给出了一种 $O(n)$ 的做法。

我们优化我们的状态为 $f[i][j][a][b]$ 表示枚举到第 $i$ 个点，好的路径条数的奇偶性，是否存在奇白，是否存在奇黑。

因为事实上，每次更新我们只需要知道奇黑或者奇白是否存在即可，因为只要其存在，那我们所有的转移就会**对半分**。在上述的讨论中不难发现这一点，另一个理解是：我们可以从奇黑和奇白中挑选出一个**控制奇偶性**。

具体的转移还需要关注该点插入后，会变成奇黑(白)还是偶黑(白)。具体的，还是以插入白点为例。

- 如果不存在奇黑，显然这个白点只能作为奇白存在，得到的贡献即位上一个状态乘上 $2^{i - 1}$，即所有边任意连。

- 如果存在奇黑，则这个白点作为奇白、偶白存在的情况**对半分**，分别得到上一个状态乘上 $2^{i - 2}$ 的贡献，具体原因如上，下不赘述；。

这样做的复杂度会有一个 $8$ 的常数，但基本忽略不计，即 $O(n)$。

## $code$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 60, lim = 50, mod = 1e9 + 7;
inline int read()
{
	int s = 0, w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') w *= -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w; 
}
int n, p, ans;
int fac[N], col[N], f[N][2][2][2];
signed main()
{
	n = read(), p = read();
	for(register int i = 1; i <= n; i++) col[i] = read();
	fac[0] = 1;
	for(register int i = 1; i <= lim; i++) fac[i] = (fac[i - 1] << 1) % mod;
	f[0][0][0][0] = 1;
	for(register int i = 1; i <= n; i++){
		for(register int j = 0; j <= 1; j++){ //枚举奇偶性 
			for(register int a = 0; a <= 1; a++){ //枚举奇白是否存在 
				for(register int b = 0; b <= 1; b++){ //枚举奇黑是否存在 
					if(col[i] != 0){ //这个点可能是白点 
						if(b){ //奇数黑点存在 
							f[i][j][a][b] = (f[i][j][a][b] + f[i - 1][j][a][b] * fac[i - 2] % mod) % mod;
							f[i][j ^ 1][a | 1][b] = (f[i][j ^ 1][a | 1][b] + f[i - 1][j][a][b] * fac[i - 2] % mod) % mod;
						}
						else f[i][j ^ 1][a | 1][b] = (f[i][j ^ 1][a | 1][b] + f[i - 1][j][a][b] * fac[i - 1] % mod) % mod;
					}
					if(col[i] != 1){ //这个点可能是黑点 
						if(a){ //奇数白点存在 
							f[i][j][a][b] = (f[i][j][a][b] + f[i - 1][j][a][b] * fac[i - 2] % mod) % mod;
							f[i][j ^ 1][a][b | 1] = (f[i][j ^ 1][a][b | 1] + f[i - 1][j][a][b] * fac[i - 2] % mod) %mod;
						}
						else f[i][j ^ 1][a][b | 1] = (f[i][j ^ 1][a][b | 1] + f[i - 1][j][a][b] * fac[i - 1] % mod) % mod;
					}
				}
			}
		}
	}
	int ans = 0;
	for(register int a = 0; a <= 1; a++)
		for(register int b = 0; b <= 1; b++) ans = (ans + f[n][p][a][b]) % mod;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：A_Pikachu (赞：2)

### [题目传送门](https://www.luogu.com.cn/problem/CF979E)
（如果 $\LaTeX$ 炸了，请到博客[观看](https://www.luogu.com.cn/blog/thats-me/ti-xie-cf979e-kuro-and-topological-parity)）

$\Large\mathscr{P}\mathit{art}\,\,1\;\;\text{基本思路}$

考虑对于一条长度为 $d$ 的合法路径，在其末尾添一个节点，使其依旧是合法的，增加的好的路径条数为 $d$。由于我们需要对于路径总数模二，那么也要对 $d$ 的奇偶进行讨论。但此时我们发现既要讨论路径长度，又要讨论点的颜色，对象太多，所以不妨都集中讨论点的颜色和它应该被安排到的路径条数的奇偶。

注意到 $n \le 50$，便萌生出了一种大胆的想法，直接讨论不同状态的点的个数的方案。设 $f[i][j][k][l][m]$ 表示在计算到第 $i$ 个点的时候，奇黑（用状态表示一类点，下同），偶黑，奇白，偶白的个数分别为 $j$，$k$，$l$，$m$ 时所得的答案。由于最后一维可以由前四维推出，便在此省略。

首先考虑初始化：一个点时满足颜色条件的奇数点方案数为 $1$。

其次考虑转移：首先，参与转移的两个状态一定是异色状态，并且，偶数点不能影响方案的奇偶性，所以真正要讨论的只有奇数点。如果想要从奇数点转移过来，必须经过奇数个奇数点才能保证其为奇，而此时多出的方案数即为 $2^{j-1}$，其中 $j$ 表示奇黑的个数。而其它点因为对方案奇偶没有影响，所以可以随便取，共 $2^{i-1-j}$ 种，最终方案数相乘即可。

$\Large\mathscr{P}\mathit{art}\,\,2\;\;\text{Code}$

```cpp
#include <cstdio>
const int N=55,MOD=1000000007;
int n,p,u,ans,p2[N],f[N][N][N][N]; //jh,oh,jb,ob
int main(){
	scanf("%d%d%d",&n,&p,&u);
	if(n==1){
		printf("%d\n",p?(u==-1?2:1):0);
		return 0;
	}
	p2[0]=1; for(int i=1; i<=n; i++) p2[i]=(p2[i-1]<<1LL)%MOD;
	if(u!=1) f[1][1][0][0]=1;
	if(u!=0) f[1][0][0][1]=1;
	for(int i=2; i<=n; i++){
		scanf("%d",&u);
		for(int j=0; j<=i; j++){
			for(int k=0; j+k<=i; k++){
				for(int l=0; j+k+l<=i; l++){
					int m=i-j-k-l,res=0;
					if(u!=1){
						res=0;
						if(j) res=(res+(l?1LL*p2[l-1]*f[i-1][j-1][k][l]%MOD:f[i-1][j-1][k][l]))%MOD;
						if(k) res=(res+(l?1LL*p2[l-1]*f[i-1][j][k-1][l]%MOD:0))%MOD;
						f[i][j][k][l]=1LL*res*p2[i-1-l]%MOD;
					}
					if(u!=0){
						res=0;
						if(l) res=(res+(j?1LL*p2[j-1]*f[i-1][j][k][l-1]%MOD:f[i-1][j][k][l-1]))%MOD;
						if(m) res=(res+(j?1LL*p2[j-1]*f[i-1][j][k][l]%MOD:0))%MOD;
						f[i][j][k][l]=(f[i][j][k][l]+1LL*res*p2[i-1-j]%MOD)%MOD;
					}
					if(i==n&&(((j+l)&1)==p)) ans=(ans+f[i][j][k][l])%MOD;
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

时间复杂度 $\Theta(n^4)$。

---

## 作者：forest114514 (赞：1)

### CF979E Kuro and Topological Parity

首先固定了一个图，怎么对路径的奇偶性来计数？

可以考虑 DP，$g_{i,j,k}$ 表示考虑了前 $i$ 个点，有 $j$ 个黑点结束的路径为奇数，有 $k$ 个白点结束的路径方案数为奇数时此时的路径奇偶性，转移是容易的，根据现有的点类型转移即可。


知道怎么对路径奇偶性计数后可以考虑 DP 套 DP，我们把 $g_{i,j,k}$ 的值也作为状态的一维：设 $f_{i,j,k,u}$ 表示前 $i$ 个点，有 $j$ 个黑点结束的路径为奇数，有 $k$ 个白点结束的路径方案数为奇数，此时路径奇偶性即 $g_{i,j,k}$ 为 $u$ 的方案数。

首先偶数点不会影响任何点的结果，所以只用枚举前面有几个异色奇数点连向自己，就能 $O(n^4)$ 做完这个 DP 了，而且常数不大，此时已经能通过。

但是我们能优化这个 DP 套 DP 状态吗？

你玩一玩就发现，只要存在异色的奇数点，无论有几个奇数点，都恰好有一半的方案有奇数个异色奇数点连向自己，一半的方案有偶数个异色奇数点连向自己；否则只能新增一个奇数点，我们发现状态之和奇偶点的存在性有关了，就不用记录具体的数值，只用记录是否存在即可。

设 $f_{i,0/1,0/1,0/1}$ 为前 $i$ 个点，是否有奇数方案的白点、黑点，路径奇偶性为偶/奇时的方案数。

转移是简单的，枚举当前点颜色和是否成为奇数点，预处理 $2$ 的幂次即可，转移以白点为例。

1. 之前没有奇黑点，只能成为奇白点。
   $$
   f_{i,j,0,u}\times 2^i\to f_{i+1,1,0,u\oplus 1}
   $$

2. 之前有奇黑点，可以决定现在点的奇偶性。

   1. 成为奇白点：
      $$
      f_{i,j,1,u}\times 2^{i-1}\to f_{i+1,1,1,u\oplus 1}
      $$

   2. 成为偶白点：
      $$
      f_{i,j,1,u}\times 2^{i-1}\to f_{i+1,j,1,u}
      $$

时间复杂度 $O(n)$。

---

## 作者：zac2010 (赞：1)

本题采用 DP 套 DP。

首先，我们考虑怎么在确定所有点颜色且确定所有连边的情况下算方案数。不难发现可以采用 DAG 上 DP。

令 $g_i$ 表示以 $i$ 开头的路径数量，那么他可以从所有颜色和他不同的点转移过来。转移顺序的话按照 DAG 的反图上的拓扑顺序来。

再考虑外层 DP。令 $f_{i,j,k,t}$ 表示以 $i$ 到 $n$ 中，总路径条数的为奇数/偶数（$j=0$ 为奇数，$j=1$ 为偶数），存在/不存在 $g_x \equiv 1 \pmod{2}$ 的黑点（$k=0$ 表示不存在，$k=1$ 则反之），存在/不存在 $g_x \equiv 1 \pmod{2}$ 为奇数的白点（$t=0$ 表示不存在，$t=1$ 则反之）的方案数。

转移的话就很简单，我们枚举可以选的颜色，然后挑选一个其它颜色且 $g_x \equiv 1 \pmod{2}$ 的点用来协调整奇偶性，其它点可以有选/不选两种方案。若没有这样一个点，那么当前点开头路径数的奇偶性只能为奇数（注意当前点本身也算一条路径）。

```cpp
#include <bits/stdc++.h>
#define L(i, a, b) for(int i = a; i <= b; i++)
#define R(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
const int N = 50 + 10, mod = 1e9 + 7;
int n, p, ans, c[N], pw[N] = {1}, f[N][2][2][2];
int main(){
    scanf("%d%d", &n, &p);
    L(i, 1, n) scanf("%d", &c[i]);
    L(i, 1, n) pw[i] = (pw[i - 1] << 1) % mod;
    f[n + 1][0][0][0] = 1;
    R(i, n, 1) L(j, 0, 1) L(k, 0, 1) L(t, 0, 1){
    	if(!f[i + 1][j][k][t]) continue;
    	if(c[i] != 1){
    		if(t){
    			(f[i][j][k][t] += 1ll * pw[n - i - 1] * f[i + 1][j][k][t] % mod) %= mod;
    			(f[i][j ^ 1][1][t] += 1ll * pw[n - i - 1] * f[i + 1][j][k][t] % mod) %= mod;
			}
			else (f[i][j ^ 1][1][t] += 1ll * pw[n - i] * f[i + 1][j][k][t] % mod) %= mod;
		}
		if(c[i] != 0){
			if(k){
    			(f[i][j][k][t] += 1ll * pw[n - i - 1] * f[i + 1][j][k][t] % mod) %= mod;
    			(f[i][j ^ 1][k][1] += 1ll * pw[n - i - 1] * f[i + 1][j][k][t] % mod) %= mod;
			}
			else (f[i][j ^ 1][k][1] += 1ll * pw[n - i] * f[i + 1][j][k][t] % mod) %= mod;
		}
	}
	L(k, 0, 1) L(t, 0, 1) (ans += f[1][p][k][t]) %= mod;
	printf("%d\n", ans);
    return 0;
}
```


---

## 作者：Felix72 (赞：1)

考虑动态规划，用四个维度分别讨论当前有几个黑色、白色，以及分别有着奇数或偶数种方案。

我们发现，只有从异色奇数点连边时，答案奇偶性才会改变，那么预处理出二的次幂直接转移即可。

下面的代码第五维是第二维和第四维的加和，可以略去。相应地转移方程可以少一半。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 52, mod = 1e9 + 7;
int n, m, col[N]; long long dp[N][N][N][N][2], C[N][N], pw[N * 4], ans;
inline void Plus(long long &now, long long add)
{now += add; if(now > mod) now -= mod;}
inline void init()
{
	C[0][0] = 1; pw[0] = 1;
	for(int i = 1; i <= 200; ++i) pw[i] = pw[i - 1] * 2 % mod;
	for(int i = 1; i <= 50; ++i)
	{
		C[i][0] = 1;
		for(int j = 1; j <= i; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	init();
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) cin >> col[i];
	dp[0][0][0][0][0] = 1;
	for(int b0 = 0; b0 <= n; ++b0)
	{
		for(int b1 = 0; b1 <= n - b0; ++b1)
		{
			for(int w0 = 0; w0 <= n - b0 - b1; ++w0)
			{
				for(int w1 = 0; w1 <= n - b0 - b1 - w0; ++w1)
				{
//					cout << b0 << " " << b1 << " " << w0 << " " << w1 << " " << dp[b0][b1][w0][w1][0] << " " << dp[b0][b1][w0][w1][1] << '\n';
					int now = b0 + b1 + w0 + w1;
					if(now == n) {Plus(ans, dp[b0][b1][w0][w1][m]); continue;}
					if(col[now + 1] != 1)
					{
						if(w1)
						{
							// next is even(black)
							Plus(dp[b0 + 1][b1][w0][w1][0], dp[b0][b1][w0][w1][0] * pw[b0 + b1 + w0 + w1 - 1] % mod);
							Plus(dp[b0 + 1][b1][w0][w1][1], dp[b0][b1][w0][w1][1] * pw[b0 + b1 + w0 + w1 - 1] % mod);
						}
						//next id odd(black)
						Plus(dp[b0][b1 + 1][w0][w1][0], dp[b0][b1][w0][w1][1] * pw[b0 + b1 + w0 + max(w1 - 1, 0)] % mod);
						Plus(dp[b0][b1 + 1][w0][w1][1], dp[b0][b1][w0][w1][0] * pw[b0 + b1 + w0 + max(w1 - 1, 0)] % mod);
					}
					if(col[now + 1] != 0)
					{
						if(b1)
						{
							//next is even(white)
							Plus(dp[b0][b1][w0 + 1][w1][0], dp[b0][b1][w0][w1][0] * pw[b0 + b1 - 1 + w0 + w1] % mod);
							Plus(dp[b0][b1][w0 + 1][w1][1], dp[b0][b1][w0][w1][1] * pw[b0 + b1 - 1 + w0 + w1] % mod);
						}
						//next is odd(white)
						Plus(dp[b0][b1][w0][w1 + 1][0], dp[b0][b1][w0][w1][1] * pw[b0 + max(b1 - 1, 0) + w0 + w1] % mod);
						Plus(dp[b0][b1][w0][w1 + 1][1], dp[b0][b1][w0][w1][0] * pw[b0 + max(b1 - 1, 0) + w0 + w1] % mod);
					}
				}
			}
		}
	}
	cout << ans << '\n';
	return 0;
}
/*

*/
```

---

## 作者：Priestess_SLG (赞：0)

比较奇怪的 dp 题。设 $f_{i,j,k,p}$ 表示 $i\sim n$ 的点中路径条数为 $j$，黑色奇点数目为 $k$，白色奇点数目为 $p$ 方案数是多少。转移直接计数即可是容易的，时间复杂度为 $O(n^4)$。

是否可以优化？答案是可行的。观察到其实路径条数 / 黑色奇点数目 / 白色奇点数目都只需要区分奇偶性即可，因此后三个维度的范围都为 $2$，预处理 $2$ 的幂次之后时间复杂度为 $O(n)$。具体见代码。

```cpp
#pragma GCC optimize(3,"Ofast","inline","unroll-loops")
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=55,mod=1e9+7;
int f[N][2][2][2],pwr[N],a[N];
signed main(){
    cin.tie(0)->sync_with_stdio(false);
    int n,p;cin>>n>>p;
    for(int i=1;i<=n;++i)cin>>a[i];
    pwr[0]=1;
    for(int i=1;i<N;++i)pwr[i]=pwr[i-1]*2%mod;
    f[n+1][0][0][0]=1;
    for(int i=n;i;--i)
        for(int j=0;j<2;++j)
            for(int k=0;k<2;++k) 
                for(int p=0;p<2;++p){
                    if(a[i]==0||a[i]==-1){
                        if(p){
                            f[i][j][k][p]=(f[i][j][k][p]+pwr[n-i-1]*f[i+1][j][k][p])%mod;
                            f[i][j^1][1][p]=(f[i][j^1][1][p]+pwr[n-i-1]*f[i+1][j][k][p])%mod;
                        }else f[i][j^1][1][p]=(f[i][j^1][1][p]+pwr[n-i]*f[i+1][j][k][p])%mod;
                    }
                    if(a[i]==1||a[i]==-1){
                        if(k){
                            f[i][j][k][p]=(f[i][j][k][p]+pwr[n-i-1]*f[i+1][j][k][p])%mod;
                            f[i][j^1][k][1]=(f[i][j^1][k][1]+pwr[n-i-1]*f[i+1][j][k][p])%mod;
                        }else f[i][j^1][k][1]=(f[i][j^1][k][1]+pwr[n-i]*f[i+1][j][k][p])%mod;
                    }
                }
    cout<<(f[1][p][0][0]+f[1][p][0][1]+f[1][p][1][0]+f[1][p][1][1])%mod<<'\n';
    return 0;
}
```

---

## 作者：xuantianhao (赞：0)

# [Kuro and Topological Parity](https://www.luogu.com.cn/problem/CF979E)

我们考虑在一张染色完成的图里，我们连上了一条边，会有何影响？

$\bullet$ 在同色节点间连边——明显不会有任何影响。

$\bullet$ 在异色节点间连边，但是出发点是个偶点（即有偶数条路径以其为终点的节点），终点的路径数增加了，但增加的是偶数，故也无影响。

$\bullet$ 在异色节点间连边，但是出发点是个奇点，终点的路径数的奇偶态变化，有影响。

故我们只需要考虑状况三即可。

于是我们就可以构造出如下的 DP：

设 $f[i,j,k,l]$ 表示当前 DP 到了位置 $i$，总路径数是 $j(0/1)$，且无（有）奇黑点，无（有）奇白点。

下面以位置 $i+1$ 填入白色为例：

$\bullet$ 存在至少一个奇黑点（即 $k=1$），则对于任意一组其它 $i-1$ 个节点的连边方式，总有一种方式使得总数为奇，一种方式使得总数为偶（受此奇黑点的控制）。于是就有 $f[i,j,k,l]\times 2^{i-1}\rightarrow f[i+1,j,k,l]$ 与 $f[i,j,k,l]\times 2^{i-1}\rightarrow f[i+1,\lnot j,k,\operatorname{true}]$。

$\bullet$ 不存在奇黑点（即 $k=0$），则无论怎么连，$i+1$ 的奇偶性都不会变化，始终为奇态（被看作是以它自己为起点的路径的终点）。故有 $f[i,j,k,l]\times 2^i\rightarrow f[i+1,\lnot j,k,\operatorname{true}]$

填入黑色则同理。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int N=110;
int n,p,res;
int a[N],f[N][2][2][2],bin[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin>>n>>p;
	bin[0]=1;
    for(int i=1;i<=n;i++){
		cin>>a[i];
		bin[i]=(bin[i-1]<<1)%mod;
	}
    f[0][0][0][0]=1;
    for(int i=0;i<n;i++)
	for(int j=0;j<2;j++)
	for(int k=0;k<2;k++)
	for(int l=0;l<2;l++){
		if(!f[i][j][k][l]) continue;
		int tmp=f[i][j][k][l];
		if(a[i+1]!=0){
			if(k){
				(f[i+1][j][k][l]+=tmp*bin[i-1]%mod)%=mod;
				(f[i+1][j^1][k][true]+=tmp*bin[i-1]%mod)%=mod;
			}else (f[i+1][j^1][k][true]+=tmp*bin[i]%mod)%=mod;
		}
		if(a[i+1]!=1){
			if(l){
				(f[i+1][j][k][l]+=tmp*bin[i-1]%mod)%=mod;
				(f[i+1][j^1][true][l]+=tmp*bin[i-1]%mod)%=mod;
			}else (f[i+1][j^1][true][l]+=tmp*bin[i]%mod)%=mod;
		}
	}
    for(int k=0;k<2;k++) for(int l=0;l<2;l++) (res+=f[n][p][k][l])%=mod;
    cout<<res;
    return 0;
}
```


---

## 作者：User_Unauthorized (赞：0)

我们首先考虑在确定节点颜色的情况下如何计数，设 $f_{u, 0 / 1, 0 / 1}$ 表示考虑标号不大于 $u$ 的所有点，以 $u$ 结尾的合法路径条数模 $2$ 后的值为 $0 / 1$，且好的合法路径条数总数模 $2$ 后的值为 $0 / 1$ 的方案数。我们对于某个节点 $u$，若以 $u$ 结尾的合法路径条数模 $2$ 后的值为 $1$，那么我们称之为奇点，反之为偶点。那么对于上述 DP 时在转移时枚举异色奇点有多少个与之相连即可。

不难发现影响路径总数奇偶性的是奇点个数的奇偶性，而决定一个点奇偶性的是与之相连的异色奇数点个数，这启示我们将黑色奇点和白色奇点的个数作为状态进行奇数，设 $f_{i, j, k}$ 表示考虑标号不大于 $i$ 的所有点，黑色奇点的个数为 $j$，白色奇点的个数为 $k$ 的方案数。每次转移时考虑新增节点的颜色和其奇偶性即可。

现在还剩一个问题，若我们希望新增点数为奇点，那么我们便要选择偶数个异色奇点（该新增点自身为一条路径），设有 $m$ 个异色奇点，那么其方案数为：

$$\sum\limits_{i \,\text{is even}}\dbinom{m}{i}$$

我们可以证明其为 $2^{m - 1}$，具体的，考虑选偶数个和选奇数个的方案数之差，我们有：

$$\begin{aligned}
&\sum\limits_{i \,\text{is even}}\dbinom{m}{i} - \sum\limits_{i \,\text{is odd}}\dbinom{m}{i}\\
=&\sum\limits_{i = 0}^{m}\left(-1\right)^i\dbinom{m}{i} \\
=&\sum\limits_{i = 0}^{m}1^{m - i}\left(-1\right)^i\dbinom{m}{i} \\
=&\left(1 - 1\right)^m\\
=&\left[m = 0\right]
\end{aligned}$$

因此直接进行转移即可，复杂度为 $\mathcal{O}(n^3)$。

---

