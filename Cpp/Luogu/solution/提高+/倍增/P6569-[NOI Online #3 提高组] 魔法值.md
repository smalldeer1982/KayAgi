# [NOI Online #3 提高组] 魔法值

## 题目描述

H 国的交通由 $n$ 座城市与 $m$ 条道路构成，城市与道路都从 $1$ 开始编号，其中 $1$ 号城市是 H 国的首都。H 国中一条道路将把两个不同城市直接相连，且任意两个城市间至多有一条道路。

H 国是一个信奉魔法的国家，在第 $j$ 天，$i$ 号城市的魔法值为 $f_{i,j}$。H 国的魔法师已观测到第 0 天时所有城市的魔法值 $f_{i,0}$，且他们还发现，之后的每一天每个城市的魔法值，都将会变为所有与该城市直接相连的城市的前一天魔法值的异或值，即

$$
f_{x,j}=f_{v_1,j-1}\oplus f_{v_2,j-1}\oplus \cdots\oplus f_{v_k,j-1}
$$

其中 $j\ge 1$，$v_1,v_2,\cdots,v_k$ 是所有与 $x$ 号城市直接相连的城市，$\oplus$ 为异或运算。

现在 H 国的国王问了你 $q$ 个问题，对于第 $i$（$1\le i\le q$）个问题你需要回答：第 $a_i$ 天时首都的魔法值是多少。

## 说明/提示

#### 数据规模与约定

- 对于 $20\%$ 的数据，满足 $a_i \leq 100$。
- 对于 $40\%$ 的数据，满足 $n \leq 20$。
- 另有 $30\%$ 的数据，满足 $m=\frac{n(n-1)}{2}$。
- 对于 $100\%$ 的数据，满足 $1 \leq n,q \leq 100$，$1 \leq m \leq \frac{n(n-1)}{2}$，$1\leq a_i < 2^{32}$，$0\leq f_{i,0} < 2^{32}$。

#### 说明

data provider ：@一扶苏一，数据有锅请联系她。如果被朴素的快速幂水过去了也请联系她。

## 样例 #1

### 输入

```
3 3 1
0 0 1
1 2
1 3
2 3
1
```

### 输出

```
1```

# 题解

## 作者：一扶苏一 (赞：69)

## 【倍增，矩阵乘法】【P6569】魔法值

### Analysis

upd：经评论区老哥提醒，一般情况下乘法对异或没有分配律，不能直接求和变换。内容已修改。

把题目的式子写的更清晰一点：设 $e_{u, v}$ 表示 $(u, v)$ 之间是否有边，有边为 $1$，无边为 $0$，再把题目里的 $f$ 的两个下角标交换一下，即设 $f_{i, j}$ 是在第 $i$ 天，城市 $j$ 的魔法值，则有：

$$f_{i, v} = \operatorname{xor}_{u = 1}^n f_{i - 1, u} \times e_{u, v}$$

现在定义一个 $a \times b$ 矩阵 $A$ 异或一个 $b \times c$ 矩阵 $B$ 的结果为一个 $a \times c$ 的矩阵 $C$，转移为

$$C_{i, j} = \operatorname{xor}_{k = 1}^b A_{i, k} \times B_{k, j}$$

设 $1 \times n$ 矩阵 $F_i$ 的第 $1$ 行第 $j$ 列表示第 $i$ 天城市 $j$ 的魔法值，$n \times n$ 矩阵 $E$ 的第 $i$ 行第 $j$ 列表示 $i, j$ 之间是否有边，可以发现 $F_i$ 是由 $F_{i - 1}$ 异或矩阵 $E$ 转移而来。

$$F_i = F_{i - 1} \operatorname{xor} E$$

式子看起来长得很像快速幂，快速幂的要求矩阵有结合律，即 $(A \operatorname{xor} B \operatorname{xor} C)_{i, j} = (A \operatorname{xor} (B \operatorname{xor} C))_{i, j}$，来尝试推一下。（下面省略两矩阵间的 $\operatorname{xor}$ 运算符）

设 $A$ 是 $n \times p$ 矩阵，$B$ 是 $p \times q$ 矩阵，$C$ 是 $q \times m$ 矩阵，则他们的异或和为 $n \times m$ 矩阵。

$$\begin{aligned}(ABC)_{i, j} = \operatorname{xor}_{x = 1}^q(\operatorname{xor}_{y = 1}^p A_{i, y} \times B_{y, x}) \times C_{x, j} \end{aligned}$$

需要注意的是，一般情况下，乘法对异或没有分配律。例如对于 $3, 1, 2$，$3 \times (1 \operatorname{xor} 2) = 9 \neq (1 \times 3)\operatorname{xor}(2 \times 3) = 5$，因此不能直接去掉上式中的括号。

但是注意到 C 矩阵一定是一个 $01$ 矩阵（显然如果进行快速幂，那么一个 $01$ 矩阵在只做乘法和异或的情况下一定不存在进位，结果还是一个 $01$ 矩阵）。考虑当 $C_{x, j} = 0$ 或 $1$ 时，将括号去掉把 $C_{x, j}$ 乘进去，式子是成立的。证明上可以考虑当 $C_{x, j} = 0$ 时，括号乘上 $C_{x, j}$ 的结果一定是 $0$，将 $C_{x, j}$ 乘进去后，每一项都是 $0$，异或和还是 $0$；当 $C_{x, j} = 1$ 时，括号内每一项的值都没有发生改变。而整个括号的值乘上 $1$ 的值也不会改变，因此二者是相等的。

由此得到

$$\begin{aligned}(ABC)_{i, j} = \operatorname{xor}_{x = 1}^q \operatorname{xor}_{y = 1}^p A_{i, y} \times B_{y, x} \times C_{x, j} \end{aligned}$$

同理，对于 $(A(BC))_{i, j}$，也可以写出式子后用同样的证明去括号，因此二者是相等的。在 $C$ 是 $01$ 矩阵时，矩阵异或具有结合律，可以进行快速幂。

因此有

$$F_{i} = F_0 \operatorname{xor} E^i$$

这里 $E^i$ 指 $E$ 自身异或 $i$ 次。

那么有一个 naive 的做法是每次询问都进行一次矩阵快速幂，$F_{a_i} = E^{a_i}$。时间复杂度为 $O(n^3q \log a)$。期望得分 $40$ 分。

注意到对于询问，如果对 $E$ 进行快速幂的话，由于 $E$ 是 $n \times n$ 的矩阵，因此做一次的复杂度就为 $O(n^3)$。但是 $F$ 是 $1 \times n$ 的矩阵，因此 $F$ 每次异或一个 $E$ 的幂的复杂度为 $O(n^2)$。考虑不进行快速幂，对 $a_i$ 进行二进制拆分，拆成 $O(\log a)$ 个 $2$ 的幂的形式 ，首先预处理出 $E^{2^k}$ 的值，然后用 $F$ 依次乘上对应的幂即可。

预处理的复杂度为 $O(n^3 \log a)$，单次询问的复杂度为 $O(n^2 \log a)$。因此总复杂度 $O(n^3 \log a) - O(n^2q \log a)$。

另外回复一下评论区疑问，上式复杂度中的 `-` 不代表减号。对于一个算法，用 $A-B$ 表示其预处理部分为 $A$ 的复杂度，$B$ 表示其余部分的时间复杂度。

### Code

```cpp
namespace Fusu {

const int maxt = 32;
const int maxn = 105;

int n, q, m;
ll a[maxn];

struct Mat {
  int x, y;
  ll mt[maxn][maxn];

  Mat(const int X = 0, const int Y = 0) : x(X), y(Y) {}

  Mat operator*(const Mat &o) const {
    Mat ret(x, o.y);
    for (int i = 1; i <= x; ++i) {
      for (int j = 1; j <= o.y; ++j) {
        ret.mt[i][j] = 0;
        for (int k = 1; k <= y; ++k) {
          ret.mt[i][j] ^= mt[i][k] * o.mt[k][j];
        }
      }
    }
    return ret;
  }
};
Mat g[maxt], f;

void Main() {
  qr(n); qr(m); qr(q);
  qra(a + 1, n);
  g[0].x = g[0].y = n;
  for (int u, v; m; --m) {
    qr(u); qr(v);
    g[0].mt[u][v] = g[0].mt[v][u] = 1;
  }
  for (int i = 1, di = i - 1; i < maxt; di = i++) {
    g[i] = g[di] * g[di];
  }
  for (ll x; q; --q) {
    qr(x);
    f.x = 1; f.y = n;
    memcpy(f.mt[1] + 1, a + 1, n * sizeof(ll));
    for (ll w = 1, i = 0; w <= x; w <<= 1, ++i) if (x & w) {
      f = f * g[i];
    }
    qw(f.mt[1][1], '\n');
  }
}

} // namespace Fusu
```

看到 U 群老哥用 `bitset` 乱杀感觉好厉害啊

---

## 作者：yangrunze (赞：53)

蒟蒻由于在whk和oi巨佬的双重打击下~~抑郁了~~，赛后跑来云吸题~（感觉这次比上次r2简单哎，T2自己想想再结合下题解就能A）

这个题的思路还是蛮新颖的，一看标签，嗬~，**矩阵运算**，那这个题有意思了

看看题目，图论题！反正 $n$ 和 $m$ 这么小，那咱们就先来整个**邻接矩阵**

不整则已，一弄这邻接矩阵，这个题就打开了新世界的大门！

首先，咱们来看看题目里面说的魔法值是咋定义的：

$$f_{x,i}=f_{v_1,i-1} \oplus f_{v_2,i-1} \oplus \cdots \oplus f_{v_k,i-1}$$

那有了邻接矩阵 $e$ 之后， **有边为$1$，没边为 $0$** ，我们的魔法值就可以这么定义啦！

$$f_{x,i}=f_{1,i-1}\times e_{1,x}\oplus f_{2,i-1}\times e_{2,x} \oplus \cdots \oplus f_{n,i-1}\times e_{n,x}$$

这时，看到这**似曾相识**的画面，你聪明的小脑袋里貌似冒出了这样一行式子……

$$c_{i,j}=a_{i,1} \times b_{1,j}+a_{i,2} \times b_{2,j}+\cdots+a_{i,n} \times b_{n,j}=\sum\limits_{k=1}^{n}a_{i,k}\times b_{k,j}$$

！！！！！

这是……**矩阵乘法**？！

没错，“异或版”的矩阵乘法


这样的话，我们可以重新定义两个矩阵 $a$ 和 $b$ 的乘法为 $a_{i,k}\times b_{k,j}$ 的**异或和**：

$$a \times b= a_{i,1} \times b_{1,j}\oplus a_{i,2} \times b_{2,j}\oplus\cdots\oplus a_{i,n} \times b_{n,j}$$

为了让这个“异或版矩阵乘法”的定义用得更顺手，咱们干脆把$f_{i,j}$的定义改一下，**$i$为天数，$j$为城市编号** ，即 $f_{i,j}$ 为第$i$天，城市$j$的魔法值。

这样一来，根据“异或版矩阵乘法”的定义，新一天各个城市的魔法值（它是一个 $1$ 行 $n$ 列的矩阵）就可以通过**前一天的魔法值**与**图的邻接矩阵**通过“异或版矩阵乘法”的运算得到啦！

那接下来是怎么搞呢？

我们都知道，矩阵乘法是有**结合律**的

那“异或版矩阵乘法”跟普通的矩阵乘法那么像，这家伙肯定也有结合律（不相信的话，自己乘两个试试？）

然鹅，事与愿违……

![](https://cdn.luogu.com.cn/upload/image_hosting/to646764.png)

算了反正可以这么算就是了……

（观众：yrz你今天休想这么混过去！）

好了我错了还不行吗，[我给你们证明就是了](https://www.luogu.com.cn/paste/t0oqqi6f)，饶了我吧……



前面我们说过，

$$f_i=f_{i -1}\times e$$

（$f_i$为第$i$天的魔法值矩阵，$e$是图的邻接矩阵）

那这样的话，

$$f_i=f_0\times e\times e\times e\times \cdots$$

根据刚才推出的的“（伪）结合律”，

$$f_i=f_0\times e^i$$

这是……**[矩阵快速幂](https://www.luogu.com.cn/blog/ravenclawyangrunze/solution-p3390)**？

可以是可以，但是别忘了这个题是**多组询问**，一次两次还好，弄个百儿八十次不又要……（you know what）

虽然直接憨憨地快速幂会T，不过我们可以取其精华，去其糟粕，利用**二进制拆分**的思想，**将这个矩阵的$2^i$次方预处理出来，循环利用**
，就没有问题啦~

然后接下来就是你们最关心的代码啦！

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct matrix{//用结构体存矩阵敲好使哒~
	long long qwq[105][105];
    int x,y;//x,y就是矩阵的行数和列数
	matrix(){x=0,y=0;memset(qwq,0,sizeof(qwq));};//构造函数，刚听说这玩意，用着玩玩
}; 
matrix operator * (const matrix &a,const matrix &b){//重载“异或版矩阵乘法”的运算符
	matrix c;
	c.x=a.x,c.y=b.y;
	for(int i=1;i<=a.x;i++){  
		for(int j=1;j<=b.y;j++){
			for(int k=1;k<=a.y;k++)
			c.qwq[i][j]^=a.qwq[i][k]*b.qwq[k][j];//和矩阵乘法别无二致，只不过就是改成异或
		}
	}
	return c;                   
}
matrix wyx[40];//存储e矩阵的2^i次方，取这个变量名是因为想借助神仙的力量AC本题
long long f[105];//每个城市的初始魔法值（提醒：十年OI一场空……）
int main(){
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
	scanf("%lld",&f[i]);
	wyx[0].x=n,wyx[0].y=n;//初始化一开始的邻接矩阵（也就是2的0次方）的大小
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		wyx[0].qwq[a][b]=wyx[0].qwq[b][a]=1;//给邻接矩阵连上边
	}
	for(int i=1;i<32;i++)wyx[i]=wyx[i-1]*wyx[i-1];//利用快速幂的思想，处理出邻接矩阵2的i次方
	while(q--){
		long long x;
		scanf("%lld",&x);
        matrix ans;
		for(int i=1;i<=n;i++)ans.qwq[1][i]=f[i];//一开始就是初始f值
		ans.x=1,ans.y=n;
		for(int i=0;i<32;i++){//开始进行二进制拆分
			if((x>>i)&1)//如果这一位是1
			ans=ans*wyx[i];//就乘上对应的2的i次方
		}
		printf("%lld\n",ans.qwq[1][1]);
	}
	return 0;
}
```
总之，这篇题解就这么（并不）完美地结束了，也许是因为最近压力大吧，感觉写得不怎么走心，**如有错误请在下方狂喷**，最近心情不好，真的好累啊……（求安慰/kel）


---

## 作者：small_rubbish (赞：43)

~~没想到比赛时候写的代码竟然 A 了。~~

因为 $a_i$ 很大，所以我们考虑倍增。

设 $d_{i,j,k}$ 表示 $i$ 到 $j$ 有多少条长度为 $2^k$ 的路径。

然后用一个 floyd 算这个值。

对于一个询问，把 $a_i$ 分成若干段 $2$ 的幂数，$dp_{i,j}$ 表示通过前 $j$ 段从 $1$ 到达 $i$ 的方案数。

然后就能解决了，复杂度 $n^3 \times \log_2n$。

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long f[105],jd[105],tot;
unsigned long long lj[105][105][40],dp[105][40];
int main()
{
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)scanf("%llu",&f[i]);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		lj[a][b][0]=lj[b][a][0]=1;
	}
	for(int i=1;i<=35;i++)for(int l=1;l<=n;l++)
		for(int j=1;j<=n;j++)for(int k=1;k<=n;k++)
			lj[j][k][i]+=lj[j][l][i-1]*lj[l][k][i-1];
	for(int i=1;i<=q;i++)
	{
		tot=0;
		unsigned long long aa,ans=0;
		scanf("%llu",&aa);
		memset(dp,0,sizeof(dp));
		for(int j=35;j>=0;j--)if((1ull<<j)<=aa)
		{
			jd[++tot]=j;
			aa-=1ull<<j;
		}
		dp[1][0]=1;
		for(int j=1;j<=tot;j++)for(int k=1;k<=n;k++)for(int l=1;l<=n;l++)
			dp[k][j]+=dp[l][j-1]*lj[l][k][jd[j]];
		for(int j=1;j<=n;j++)dp[j][tot]&=1;
		for(int j=1;j<=n;j++)if(dp[j][tot])ans^=f[j];
		printf("%llu\n",ans);
	}
	return 0;
}
```

---

## 作者：BFqwq (赞：20)

### 二进制拆分+矩阵乘法

很容易想到，这样的题目适合矩阵。

定义矩阵 $T$，

如果在某一时刻从 $i$ 号节点到 $j$ 号节点的路径数量为奇数条，则 $T_{i,j}$  为 $1$，否则为 $0$。

然后考虑矩阵乘法的形式，其实这一矩阵的转移，就是将标准矩阵乘法的 $\sum$ 变成了 $\operatorname{xor}$。

也就是：
$$ans_{i,j}=\operatorname{xor}a_{i,k}\ \&\ b_{k,j}$$

易证其正确性与结合律。

然后考虑二进制拆分：

由于矩阵是不变的，所以我们可以预处理出 $T^1,T^2,T^4\ldots T^{2147483648}$，也就是 $T^{2^n}$。

然后算答案的时候，如果步数中有这个值，我们就将 $f$ 数组乘上对应的矩阵，就可以得到答案。

```cpp
#include <bits/stdc++.h>
#define uit unsigned int
using namespace std;
inline uit read(){
	register uit x=0;
	register bool f=0;
	register char c=getchar();
	while(c<'0'||c>'9'){
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return f?-x:x;
}
char cr[200];int tt;
inline void print(register uit x,register char k='\n') {
    if(!x) putchar('0');
    while(x) cr[++tt]=x%10+'0',x/=10;
    while(tt) putchar(cr[tt--]);
    putchar(k);
}
int n,m,q;
uit f[105],g[105];
struct mt{
	bool a[105][105];
	mt(){
        memset(a,0,sizeof(a));
    }
	friend mt operator *(mt b,mt c){
		mt d;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					d.a[i][j]^=(b.a[i][k]&c.a[k][j]); 
				}
			}
		}
    	return d;
	}
}t[32];
void mul(uit wh){
	uit tmp[105];
	memset(tmp,0,sizeof(tmp));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(t[wh].a[i][j]){
				tmp[i]=tmp[i]^g[j]; 
			}
		}
	}
	for(int i=1;i<=n;i++){
		g[i]=tmp[i];
	}
}
int main(){
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++){
		f[i]=read();
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		t[0].a[u][v]=t[0].a[v][u]=1;
	}
	for(int i=1;i<=31;i++){
		t[i]=t[i-1]*t[i-1];
	}
	for(int i=1;i<=q;i++){
		for(int j=1;j<=n;j++){
			g[j]=f[j];
		}
		uit k=read();
		for(int j=0;j<=31;j++){
			if(k&(1u<<j)) mul(j);
		}
		print(g[1]);
	}
	return 0;
}
```


---

## 作者：Mophie (赞：14)

刚刚肝完比赛，来一发新鲜的题解~

注：题意在这就不翻译了，认真看的人都能看懂。

### 思路

前置芝士：对异或的基本了解，矩阵乘法，快速幂

首先我们能够发现，当同一个数异或两次后，会变成0，**也就是说我们可以当它不存在**

而且每一次都只有可能从原来的$f[i]$跳过来，所以我们只要记录它的值被哪几个$f[i]$影响即可。

那么，问题来了，**怎么记录呢？**

看着n范围这么小，建立一个01矩阵应该并不难想。

即建个矩阵$Map[i][j]$，当$Map[i][j]=1$时即i的数值被j所影响。

然后暴力，但这样暴力还不如普通暴力那样码量短，时间也相差无几。

看看数据范围，发现天数是$10^8$量级的。

所以一般会有两种想法，一是看看有没有周期性，二是能不能使复杂度变成$log{a_i}$。

但手玩几组数据后就会发现周期性完全不靠谱……

所以我们的路就只剩下了一条——寻找$log$量级的算法！

前面说过，可以建立01矩阵。而且$n$的范围还这么小，那么为什么不用矩阵乘法呢？

我们建立一个数组$Map[i][j][k]$，代表在进行了$2^i$步时k的值是否对j造成影响。

那么转移方程也挺好想的：如果$Map[i-1][j][k]=1$，那么：

$$Map[i][j][p]=Map[i][j][p]\bigoplus Map[i-1][k][p](1<=p<=n)$$

那么，最后询问时，只要将$a_i$分割成几段$2^i$，然后操作即可。

时间复杂度$O(32n^3+log{a_i}qn^2)$

我认为我的码风比较正常，大家应该能看懂吧……

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=105;
long long tot,k,a[35][N][N],n,m,Q,ans[N],f[N],last[N];
inline void init()
{
	for(int i=1;i<=32;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				if(a[i-1][j][k]==1)
					for(int l=1;l<=n;l++)
						a[i][j][l]^=a[i-1][k][l];
}
//初始化，记录2^n的状态，题解里应该讲的很清楚了 
inline void work()//精髓
{
	int now=0;//记录到了2的几次方 
	while(k>0)
	{
		if(k%2==1)//快速幂 
		{
			for(int i=1;i<=n;i++)last[i]=ans[i],ans[i]=0;//用last标记上一次的数据 
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(a[now][i][j]==1)
					{
						ans[i]=ans[i]^last[j];//如果j对i有影响那么异或上这一点 
					}
		}
		k=k/2,now++;//往下做 
	}
	return ;
}
int main() 
{
	//freopen("magic.in","r",stdin);
	//freopen("magic.out","w",stdout);
	//千万不要忘了加这个…… 
	cin>>n>>m>>Q;
	for(int i=1;i<=n;i++)cin>>f[i];
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		a[0][x][y]=1,a[0][y][x]=1;//即1天后y对x有影响，x对y有影响 
	}
	init();//初始化 
	for(int i=1;i<=Q;i++)
	{
		cin>>k;
		for(int j=1;j<=n;j++)ans[j]=f[j];//初始化 
		work();
		cout<<ans[1]<<endl;//一号点 
	}
	return 0;
}

```




---

## 作者：ez_lcw (赞：7)

# 矩阵快速幂

相信其他巨佬讲矩阵快速幂的原理和过程都已经很详细了，这里我就着重讲一讲用裸的矩阵快速幂算法之后，如何优化。

## 优化1：优化矩阵乘法

这个好几位大佬讲过了，我也不讲了，主要就是把 $O(n^3)$ 的矩阵乘法优化到 $O(n^2)$。

## 优化2：倍增预处理矩阵

倍增预处理矩阵的核心思想就是：

将 $2^k$ 个转移矩阵相乘出来的矩阵预处理出来，并记录为 $m_k$，那么通过 $m_k=m_{k-1}^2$ 就可以用 $32$ 次矩阵乘法把每个 $m_i$ 算出来。

那么对于一次询问为 $x$，也就是求 $2^x$ 个转移矩阵相乘出来的矩阵，我们就可以通过类似倍增一样的算法在 $\log(x)$ 次计算后计算出答案。

## 优化3：```bitset```

我们可以发现，在计算矩阵乘法时，可以用 ```bitset``` 优化。

比如，对于矩阵 $A$、$B$，现在要计算 $C=A\times B$。

那么根据定义，$C_{i,j}=\operatorname{xor}_{k=1}^{n} A_{i,k}\times B_{k,j}$。

形象地理解一下，$C_{i,j}$ 的值就是 $A$ 矩阵的第 $i$ 行和 $B$ 矩阵的第 $j$ 列一位一位地乘起来，再把这些乘出来的结果异或起来。

而且我们知道一个性质，$A$ 矩阵和 $B$ 矩阵中只可能出现 $0$ 或 $1$。

那么对于两个数 $x,y\in\{0,1\}$，必定有 $x\times y=x\operatorname{and}y$。

这时容易想到用 ```bitset``` 维护矩阵乘法。就是把矩阵每一行所代表的 $01$ 串存进 ```bitset<100>row[100]``` 内，把矩阵的每一列所代表的 $01$ 串存进 ```bitset<100>line[100]``` 内。然后 $A$ 矩阵的第 $i$ 行和 $B$ 矩阵的第 $j$ 列一位一位地乘起来就是 ```A.row[i]&B.line[j]```，这样我们就能解决乘法的问题了。

但是有一个问题，我们得到了乘出来的序列后，怎么把它们一个一个异或起来呢？注意到这个序列是个 $01$ 序列，那么如果这个序列中 $1$ 的个数为奇数，它们异或起来就是 $1$，否则就是 $0$，所以异或的部分我们就可以维护了，即 $C_{i,j}=\operatorname{count}()\bmod2$。

那么我们就顺利地把 $O(n^3)$ 的矩阵乘法成功优化到 $O(\frac{n^3}{64})$。（未加优化1）

## 优化4：询问离线

~~感觉最没用的优化。~~

显然，我们每次询问都算一次 $\operatorname{pow()}$，感觉会重复算了很多，所以不妨把询问给离线存下来，存进数组 $q$ 里面，并对它进行排序。

~~这个排序可能会导致程序变慢而不是变快。~~

那么不妨假设我们现在已经知道了转移矩阵 $t$ 的 $q_i$ 次方是多少，要求 $q_{i+1}$ 的询问，也就是要求出 $t^{q_{i+1}}$。那么我们只用求出 $t^{q_{i+1}-q_i}$，然后再乘上上次算出来的矩阵，就可以省下一些时间。

~~优化5：O2 优化和 IO 读写~~

最后贴一下代码：（没有加优化1卡过去的）

```cpp
#include<bits/stdc++.h>

#define N 110
#define LV 32

using namespace std;

struct Matrix
{
	bitset<N>row[N];//bitset优化
	bitset<N>line[N];
	Matrix()
	{
		memset(row,0,sizeof(row));
		memset(line,0,sizeof(line));
	}
}turn[LV],st;

struct Query
{
	unsigned int x;
	int id;
}ask[N];

int n,m,q;
unsigned int f[N],ans[N];
bool tmp[N][N];

inline Matrix operator * (Matrix a,Matrix b)
{
	Matrix ans;
	bitset<N>now;
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=n;j++)
		{
			now=a.row[i]&b.line[j];//上述的计算方法
			if(now.count()&1)
			{
				ans.row[i].set(j);
				ans.line[j].set(i);
			}
		}
	}
	return ans;
}

inline Matrix poww(unsigned int x)//倍增版的快速幂
{
	Matrix ans=st;
	for(int i=31;i>=0;i--)
	{
		if(x>=(1u<<i))
		{
			x-=(1u<<i);
			ans=turn[i]*ans;
		}
	}
	return ans;
}

inline void prework()//矩阵预处理
{
	for(register int i=1;i<LV;i++)
		turn[i]=turn[i-1]*turn[i-1];
}

inline bool cmp(const Query a,const Query b)
{
	return a.x<b.x;
}

inline unsigned int getans(const Matrix a)
{
	unsigned int ans=0;
	for(register int i=1;i<=n;i++)
		if(a.line[1][i])
			ans^=f[i];
	return ans;
}

inline int read()
{
	unsigned int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1u)+(x<<3u)+(ch^'0');
		ch=getchar();
	}
	return x;
}

int main()
{
	n=read();m=read();q=read();
	for(register int i=1;i<=n;i++)
		st.row[i].set(i),st.line[i].set(i);
	for(register int i=1;i<=n;i++)
		f[i]=read();
	for(register int i=1;i<=m;i++)
	{
		const int u=read(),v=read();
		turn[0].row[u].set(v),turn[0].line[v].set(u);
		turn[0].row[v].set(u),turn[0].line[u].set(v);
	}
	prework();
   //下面是询问离线
	for(register int i=1;i<=q;i++)
	{
		ask[i].x=read();
		ask[i].id=i;
	}
	sort(ask+1,ask+q+1,cmp);
	Matrix last=poww(ask[1].x);
	ans[ask[1].id]=getans(last);
	for(register int i=2;i<=q;i++)
	{
		last=last*poww(ask[i].x-ask[i-1].x);
		ans[ask[i].id]=getans(last);
	}
	for(register int i=1;i<=q;i++)
		printf("%u\n",ans[i]);
	return 0;
}
```

---

## 作者：周子衡 (赞：6)

**算法一**

暴力全图计算 $f$，期望得分 $20$ 分。

**算法二**

为了方便讨论，令 $v_i(1\leq i\leq n)=f_{i,0}$，即输入的数值。

先只考虑单个询问：在第 $a$ 天时 $f_1$ 是多少。

显然可以知道：最后的 $f_1$ 是若干个 $v$ 异或若干次的结果。那么是哪些数呢？

对于每个城市 $i$，我们假想数字 $v_i$ 一开始站在 $i$ 上，每天向相邻的城市走一步。那么每次它走到 $1$ 时，就向 $f_1$ 贡献一次。换言之，**$v_i$ 对 $f_1$ 的贡献次数等于 $i$ 到 $1$ 的长度为 $a$ 的路径的条数。**而异或两次等于没有异或，我们只需要求出这个路径条数对 $2$ 取余的结果即可。

观察到 $a_i$ 很大而 $n$ 很小，考虑矩阵乘法。这个想法事实上是相当自然的。具体来说，用矩阵快速幂算出路径条数的奇偶性，把奇数的位置异或起来即可。

令 $W=\max \{a_i\}$，时间复杂度 $O(qn^3\log W)$。期望得分 $60$ 分。

**算法三**

（接下来的内容较为玄学，可能并非正解，请谨慎使用。）

观察到上面算法的瓶颈是：单次询问要计算 $O(\log n)$ 次矩阵乘法。

考虑通过预处理来进一步优化。观察到 $\sqrt{W}$ 在一个可接受的范围内，考虑根号分治。

我们预处理出所有 $\sqrt{W}$ 内和 $\sqrt{W}$ 的倍数的矩阵。两种矩阵都只有 $\sqrt{W}$ 个，总时间复杂度是 $O(n^3\sqrt W)$ 的。接下来每次询问的时候拆成两个矩阵相乘即可。

然而发现上面并不太平衡，预处理复杂度过高。考虑更高次数的根号分治：选定一个正整数 $k\geq 2$，令 $p=\sqrt[k]{W}$，对于每个 $i\in [0,k]$，预处理出 $0\times p^i,1\times p^i,...,(p-1)\times p^i$ 的矩阵。这样一共处理了 $O(k\sqrt[k]{W})$ 个矩阵，而一次询问只需要用到 $k$ 个矩阵相乘。

另外可以用 bitset 优化。总时间复杂度为 $O(\dfrac{kqn^3+k\sqrt[k]{W}n^3}{w})$，总空间复杂度为 $O(\dfrac{k\sqrt[k]Wn^2}{w})$，取 $k=4,5$ 即可通过此题。

---

## 作者：zzqDeco (赞：6)

一开始是考虑到了一个点对其他点的影响，发现和距离有关，那就看看$a_i$对距离上的影响

发现行不通，打出来不对，有点尴尬

看到了$n$是100，然后部分分有完全图的样子，$a_i$又异常的大

不禁想到矩阵加速，正好不久前才自己写了一个[blog](https://www.cnblogs.com/zzqdeco/p/12599296.html)，算是运气好

~~如果还不太会矩阵加速的原理的可以看看我的blog~~

考虑由于是异或，则可以直接每一位分开处理，正好和着题目的意思，当两个点之间又边的话，就会进行变换，结合异或的性质，有奇数个1当前位就为1，否则为0

变换的矩阵自然就是看连边

当两个点连边的时候，进行一次转换就是用其中一个来转化另一个，大概就是下面的样子
$$
I=
\left\{
\begin{matrix}
   0 & 1 & 1 \\
   1 & 0 & 1 \\
   1 & 1 & 0 \\
\end{matrix}
\right\}
$$
（上面那个是样例）

写成代码就是：

```cpp
for(int i=1;i<=m;i++)
{
  int a,b;
  scanf("%d%d",&a,&b);
  Ma.s[a][b]=1;
  Ma.s[b][a]=1;
}
```

矩阵乘法就可以写为：

```cpp
const int mod=2;

M operator * (const M &x,const M &y)
{
  M now;
  now.clear();
  now.r=x.r;
  now.c=y.c;
  for(int k=1;k<=x.c;k++)
  {
    for(int i=1;i<=x.r;i++)
    {
      for(int j=1;j<=y.c;j++)
      {
        now.s[i][j]=(now.s[i][j]+x.s[i][k]*y.s[k][j]%mod)%mod;
      }
    }
  }
  return now;
}
```

初始矩阵的话，我（竟然）想了有20多分钟，然后发现就直接将每一位的0/1填上去就好了

大概就是这样：
$$
A=
\left\{
\begin{matrix}
   0 \\
   0 \\
   1 \\
\end{matrix}
\right\}
$$
（上面那个是样例）

代码大概是这样：

```cpp
for(int i=1;i<=n;i++)
{
  long long now;
  cin>>now;
  for(int j=0;j<=32;j++) a[j].s[1][i]=now&((long long)1<<(long long)j);
}
```

至于其他的就是板子了，不再赘述

但是直接这个样子在线做是会TLE的，应该是要二进制拆分

可以发现每次用到的可能有重复

就考虑直接转存下来，先预处理出每一个的1到32次方，直接使用

后面听说可以直接异或快速幂，感觉我这个分开位写的死了

某大佬说其实上面的矩阵乘法改成：

```cpp
M operator * (const M &x,const M &y)
{
  M now;
  now.clear();
  now.r=x.r;
  now.c=y.c;
  for(int k=1;k<=x.c;k++)
  {
    for(int i=1;i<=x.r;i++)
    {
      for(int j=1;j<=y.c;j++)
      {
        now.s[i][j]^=x.s[i][k]&y.s[k][j];
      }
    }
  }
  return now;
}
```

常数就少了不少

所以就直接变成了这样~~丑陋的~~代码：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int n,m,q;

struct M
{
  long long s[110][110],r,c;
  void clear()
  {
    memset(s,0,sizeof(s));
  }
}b,Ye[40];

M operator * (const M &x,const M &y)
{
  M now;
  now.clear();
  now.r=x.r;
  now.c=y.c;
  for(int k=1;k<=x.c;k++)
  {
    for(int i=1;i<=x.r;i++)
    {
      for(int j=1;j<=y.c;j++)
      {
        now.s[i][j]^=x.s[i][k]&y.s[k][j];
      }
    }
  }
  return now;
}

int main()
{
  scanf("%d%d%d",&n,&m,&q);
  b.clear();
  b.r=1;
  b.c=n;
  Ye[0].clear();
  Ye[0].r=n;
  Ye[0].c=n;
  for(int i=1;i<=n;i++)
  {
    long long now;
    cin>>now;
    b.s[1][i]=now;
  }
  for(int i=1;i<=m;i++)
  {
    int a,b;
    scanf("%d%d",&a,&b);
    Ye[0].s[a][b]=(1ll<<32)-1;
    Ye[0].s[b][a]=(1ll<<32)-1;
  }
  for(int i=1;i<=31;i++)
  {
    Ye[i]=Ye[i-1]*Ye[i-1];
  }
  for(int i=1;i<=q;i++)
  {
    long long now;
    cin>>now;
    M ans=b;
    for(int j=0;j<=31;j++)
    {
      if(now&(1ll<<j))
      {
        ans=ans*Ye[j];
      }
    }
    cout<<ans.s[1][1]<<endl;
  }
}
```



---

## 作者：Sol1 (赞：6)

首先这个题一看就是个矩阵乘法优化，转移方式也非常明显，就是拆位，点通过边转移，异或转化成加法模 $2$。

然后你就得到了 $O(qn^3\log ^2a)$ 的一个过不去算法。。。

通过压位来降 log 是老套路，考虑压位。

我们发现，矩阵乘法中的“乘”可以转化为按位 $\operatorname{and}$ 计算，于是我们把 $32$ 个 $0/1$ 矩阵压缩为一个矩阵，乘法的运算规则变为：

$$c_{i,j}=(a_{i,1}\& b_{1,j})\oplus(a_{i,2}\& b_{2,j})\oplus(a_{i,3}\& b_{3,j})\oplus\cdots\oplus(a_{i,m}\& b_{m,j})$$

然后你就得到了 $O(qn^3\log a)$ 的另外一个过不去算法。。。

我们发现如果倍增维护，那么单次询问就只需要做 $O(\log a)$ 次 $[1\times n]\times[n\times n]$ 的矩阵乘法，然后倍增预处理也只需要做 $O(\log a)$ 次 $[n\times n]\times[n\times n]$ 的矩阵乘法。

于是倍增一下这道题就做完啦~

最终复杂度 $O(n^3\log a+qn^2\log a)$，常数很小。

代码：

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;

#define int long long

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

struct Matrix {
	int a[105][105], n, m;
	Matrix() {
		n = m = 0;
		memset(a, 0, sizeof(a));
	}
	inline Matrix operator * (const Matrix& b) const {
		Matrix c;
		c.n = n;
		c.m = b.m;
		for (register int i = 1;i <= n;i++) {
			for (register int j = 1;j <= b.m;j++) {
				for (register int k = 1;k <= m;k++) {
					c.a[i][j] ^= (a[i][k] & b.a[k][j]);
				}
			}
		}
		return c;
	}
};
Matrix ans, trans[35];

int n, m, q, f[105];

inline void Read() {
	n = qread(); m = qread(); q = qread();
	for (register int i = 1;i <= n;i++) f[i] = qread();
	for (register int i = 1;i <= m;i++) {
		register int u = qread(), v = qread();
		trans[0].a[u][v] = trans[0].a[v][u] = (1ll << 32) - 1;
	}
}

inline void Prefix() {
	trans[0].n = trans[0].m = n;
	for (register int i = 1;i < 32;i++) trans[i] = trans[i - 1] * trans[i - 1];
}

inline void Solve() {
	while (q--) {
		register int t = qread();
		ans.n = 1; ans.m = n;
		for (register int i = 1;i <= n;i++) ans.a[1][i] = f[i];
		for (register int i = 0;i < 32;i++) {
			if (t & (1ll << i)) ans = ans * trans[i];
		}
		printf("%lld\n", ans.a[1][1]);
	}
}

signed main() {
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	Read();
	Prefix();
	Solve();
	return 0;
}
```

---

## 作者：Alear (赞：3)

[题面传送门](https://www.luogu.com.cn/problem/P6569)

虽然事后想想这就是一道矩阵快速幂的题目，但是由于我太菜了，导致没有想到这方面，这里提供我考场上的想法。

从算法流程和式子上来看，这个做法和矩阵快速幂是等价的。

首先通过读题，可以发现问题可以转化为从$1$好节点出发，经过$a_i$条边到达节点$u$的方案数的奇偶性，如果为奇数则用答案异或上这个节点的魔法值。

考虑转化之后的问题，100的数据范围很容易让人想到$floyd$，再观察巨大的$a_i$，考虑二进制拆分。

预处理出所有走$2^k$步的方案数矩阵,枚举中继点，转移方程如下：  
$e_{i,j,k} = XOR_{u=1}^{n} \ e_{i,u,k-1} \ and \ e_{u, j, k - 1}$  
一步的情况直接输入的时候处理即可。

接下来是$dp$。

将$a_i$按二进制拆分成$log$位，将走$a_i$步看成走若干步，每步大小为$2^k$，其中$a_i$的第$k$位为$1$。

使用滚动数组减少时空开销。

$h_{u,i}$表示在考虑前$i$位，从方案数的奇偶性，通过预处理出来的矩阵转移。
$h_{v,i}= XOR_{u=1}^{n} \ h_{u,i-1} \ and \ e_{u, v, i}$

使用滚动数组减少时空开销，仅当前位为1时转移。

正确性可以理解为枚举中继点。

注意数据范围需要使用$unsign$或$long\ long$。~~(输出%d当场裂开)~~


## code
$ Talk \  is \ cheap ,show\ you\ the\ code. $  

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned read(){
	unsigned c=0,nx,sign=1;
	while(!isdigit(nx = getchar()))
		if(nx == '-')
			sign = -1;
	while(isdigit(nx))
		c = c * 10 + nx - '0', nx = getchar();
	return sign * c;
}
const int N = 205;
int e[N][N][40];
int h[2][N];
unsigned a[N];

int main(){
//	freopen("magic.in","r",stdin);
//	freopen("magic.out","w",stdout);
	int n = read(), m = read(), Q = read();
	
	for(int i=1;i<=n;i++)
		a[i] = read();
	
	for(int i=1;i<=m;i++){
		int u = read(), v = read();
		e[u][v][0] = e[v][u][0] = 1;
	}
	
	for(int p=1;p<32;p++){
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					e[i][j][p] ^= e[k][i][p - 1] & e[k][j][p - 1];
	}
	
	while(Q--){
		unsigned x = read(), t = 1;
		memset(h[0], 0, sizeof(h[0]));
		h[0][1] = 1;
		for(unsigned p=0, tt = log(x) / log(2);p<=tt;p++){
			if(!((1 << p) & x))
				continue;
			memset(h[t], 0, sizeof(h[t]));
			
			for(int u=1;u<=n;u++)
				for(int v=1;v<=n;v++)
					h[t][v] ^= h[!t][u] & e[u][v][p];
			t ^= 1;
		}
		t ^= 1;
		
		unsigned ans = 0;
		for(int i=1;i<=n;i++)
			if(h[t][i])
				ans ^= a[i];
		printf("%u\n", ans);
	}
}
```


---

## 作者：accomplishment (赞：1)

[传送门](https://www.luogu.com.cn/problem/P6569)

这道题我们看到 $a$ 大的离谱，肯定不能普通 dp 解决，考虑矩阵优化。

### 基础做法

设邻接矩阵为 $x$，有行向量 $f$，则：

$$\begin{bmatrix}f_{1,a-1}&f_{2,0}&\cdots&f_{n,a-1}\end{bmatrix} \times \begin{bmatrix}x_{1,1}&x_{1,2}&\cdots&x_{1,n}\\x_{2,1}&x_{2,2}&\cdots&x_{2,n}\\\vdots&\vdots&\ddots&\vdots\\x_{n,1}&x_{n,2}&\cdots&x_{n,n}\end{bmatrix}$$

就是第 $a$ 天的魔法值。

第 $1$ 天的魔法值为：

$$\begin{bmatrix}f_{1,0}&f_{2,0}&\cdots&f_{n,0}\end{bmatrix} \times \begin{bmatrix}x_{1,1}&x_{1,2}&\cdots&x_{1,n}\\x_{2,1}&x_{2,2}&\cdots&x_{2,n}\\\vdots&\vdots&\ddots&\vdots\\x_{n,1}&x_{n,2}&\cdots&x_{n,n}\end{bmatrix} = \begin{bmatrix}f_{1,1}&f_{2,1}&\cdots&f_{n,1}\end{bmatrix}$$

第 $2$ 天的魔法值为：

$$\begin{bmatrix}f_{1,0}&f_{2,0}&\cdots&f_{n,0}\end{bmatrix} \times {\begin{bmatrix}x_{1,1}&x_{1,2}&\cdots&x_{1,n}\\x_{2,1}&x_{2,2}&\cdots&x_{2,n}\\\vdots&\vdots&\ddots&\vdots\\x_{n,1}&x_{n,2}&\cdots&x_{n,n}\end{bmatrix}}^2 = \begin{bmatrix}f_{1,2}&f_{2,2}&\cdots&f_{n,2}\end{bmatrix}$$

以此类推，则第 $a$ 天魔法值为：

$$\begin{bmatrix}f_{1,0}&f_{2,0}&\cdots&f_{n,0}\end{bmatrix} \times {\begin{bmatrix}x_{1,1}&x_{1,2}&\cdots&x_{1,n}\\x_{2,1}&x_{2,2}&\cdots&x_{2,n}\\\vdots&\vdots&\ddots&\vdots\\x_{n,1}&x_{n,2}&\cdots&x_{n,n}\end{bmatrix}}^a = \begin{bmatrix}f_{1,a}&f_{2,a}&\cdots&f_{n,a}\end{bmatrix}$$

注：此处的乘法不是普通的矩阵乘法，而是异或矩阵乘法。

矩阵部分代码：

[代码](https://www.luogu.com.cn/paste/7dl0plca)

那么我们可以用矩阵快速幂将矩阵每次乘 $a$ 次，然后再用行向量去乘，因为矩阵乘法复杂度是 $O(n^3)$，总时间复杂度为 $O(qn^3 \log a)$，在超时的边缘疯狂试探，卡常应该能过。

### 完美做法

发现 $f$ 是行向量，那么每次用 $f$ 乘 $x$ 是 $O(n^2)$ 的，那干脆不快速幂了，直接倍增。我们将 $x$ 的 $2$ 的整数次幂次方算出来，然后用 $f$ 依次去乘，预处理复杂度 $O(n^3\log{a})$，求解时间复杂度 $O(qn^2 \log a)$。

[代码](https://www.luogu.com.cn/paste/8qcr0vlm)

---

## 作者：jia_shengyuan (赞：1)

初三蒟蒻第一篇蓝题题解

看到题解全都是矩阵乘法，本蒟蒻表示一脸懵b...这玩意不用矩阵啊

题目中 $n,q \le 100,a_i < 2^{32}$，这个暗示很明显了，因为必须将时间、空间复杂度中的 $a_i$ 项降至对数级别，才有可能不爆 T 和 M。因此我们可以想到倍增。

那么倍增是否可行呢？经过分析，不难发现任意一个城市任意一天的魔法值一定等于若干个城市的初始魔法值异或在一起的结果，即 $∀f_{x,j}$，有 $f_{x,j}=f_{x_1,0}⊕f_{x_2,0}⊕\cdots ⊕f_{x_k,0}$。

证明：

若 $j=0$，则 $f_{x,j}=f_{x,0}$。

若 $j>0$，依据题目定义，$f_{x,j}=f_{v_1,j-1}⊕f_{v_2,j-1}⊕\cdots⊕f_{v_k,j-1}$，而所有的 $f_{v,j-1}$ 也同样满足此规律。递归过程中，$j$ 持续降低直至 $0$，因此最终 $f_{x,j}$ 便可以被表达为若干个 $f_{x_k,0}$ 相异或的结果。

可以看成上述命题成立。因此 $∀f_{x,j}$，都一定能被表示成 $f_{x_1,0}⊕f_{x_2,0}⊕\cdots ⊕f_{x_k,0}$ 的形式。

为了简化问题，我们可以先不考虑每个城市具体的魔法值，把魔法值当成一个集合，这个集合内的元素就是**会影响该城市魔法值的城市的编号**，也就是 $\{x_1,x_2,\cdots,x_k\}$。

举个例子，如图![](https://cdn.luogu.com.cn/upload/image_hosting/916x60qq.png)

在我们的简化下，$f_{1,1}=\{2,3\},f_{2,1}=\{1,3\},f_{3,1}=\{1,2,4\},f_{4,1}=\{3\}$

我们还会发现，经过相同的时间后，魔法值的传递一定是一样的。也就是说，如果 $f_{x,j} = \{x_1,x_2,\cdots,x_k\}$，则 $f_{x,j\times2}=f_{x_1,j}⊕f_{x_2,j}⊕\cdots⊕f_{x_k,j}$。（这里集合的异或和数的异或有异曲同工之妙，$a⊕b=\complement_{(a\cup b)}({a\cap b})$）

我们注意到，这里用来表示 $f_{x,j\times2}$ 的集合全部为 $f_{x_i,j}$。这和我们之前便想到的倍增不谋而合。我们用 $dp_{x,j}$ 来表示影响第 $i$ 座城市第 $2^j$ 天魔法值的城市的集合，则可以得到状态转移方程 $dp_{x,j}=dp_{x_1,j-1}⊕dp_{x_2,j-1}⊕\cdots dp_{x_k,j-1}$；$dp_{x_i,0}$ 等于与第 $i$ 座城市相连的城市的集合。

最后需要做的就是在每次询问时回答，每次找到最大的 $2^k$ 使这个数不大于剩余天数，然后对于第 $x$ 座城市，将它的魔法值异或 $dp_{x,k}$ 中的每一座城市当前的魔法值，之后令剩余天数降低 $2^k$。

全部更新完毕后，便可以得到一个表示 $f_{1,j}$ 的集合，答案便是这个集合中每个元素所对应城市初始魔法值相异或的值。

这里我们可以用 bitset 来存储这个集合，这样可以直接进行异或运算而且速度极快（这里 $N \le 100$，是很小的，所以 bitset 的时间复杂度可以当成是 $O(1)$ )。

时间复杂度 $O(n^2log_{a_i})$，空间复杂度 $O(n^2log_{a_i})$

AC code：
```cpp
#include <cstring>
#include <cstdio>
#include <bitset>

using namespace std;
const int MAXN = 105, MAXL = 35;

typedef bitset<MAXN> huge;
typedef long long ll;

huge dp[MAXN][MAXL], cur[MAXN], tmp[MAXN];
ll magic[MAXN]; //我知道不会爆int，但是这种卡边数据开大点保险
int n, m, q;

inline void Read() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &magic[i]);
    }
    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        dp[u][0][v] = true; // 把边等效为集合内第1天的元素
        dp[v][0][u] = true;
    }
}

inline void Dp() {
    for (int t = 1; t < MAXL; t++)
        for (int i = 1; i <= n; i++)
            for (int k = 1; k <= n; k++)
                if (dp[i][t - 1][k]) dp[i][t] ^= dp[k][t - 1];
}

inline void Ans(ll ask) {

    ll ans = 0;
    bool flag = true;
    for (int i = 1; i <= n; i++) cur[i].reset(); // 初始化

    for (int t = 31; t >= 0; t--) {

        if ((1LL << t) > ask) continue;
        ask -= (1LL << t);

        if (flag) { // 如果是第一个，操作会不太一样
            flag = false;
            for (int i = 1; i <= n; i++) cur[i] = dp[i][t];
            continue;
        }

        for (int i = 1; i <= n; i++) tmp[i].reset(); // 初始化

        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= n; k++) {
                if (dp[i][t][k]) { // 如果2^t天后影响i的城市有k
                    tmp[i] ^= cur[k];
                }
            }
        }
        memcpy(cur, tmp, sizeof(cur)); // 快速赋值
    }

    for (int i = 1; i <= n; i++) {
        if (cur[1][i]) ans ^= magic[i]; // 计算魔法值
    }
    printf("%lld\n", ans);
    
}

int main() {
    Read();
    Dp();
    while (q--) {
        ll ask;
        scanf("%lld", &ask);
        Ans(ask);
    }
    return 0;
}
```


---

## 作者：Caro23333 (赞：1)

本来应该滚去学文化课的，但是还是想水篇题解。

显然，任意时刻一个点的答案应该是一系列初始权值的异或和。定义一系列 $n\times n$ 的 $01$ 矩阵 $A^{(0)}, A^{(1)}, \dots$，其中$A^{(k)}_{i,j}$ 为 $1$ 当且仅当第 $k$ 轮时，$f_j$ 对点 $i$ 的答案有贡献。

为了方便，定义两个 $01$ 矩阵 $A$ 和 $B$ 的乘积 $C$ 为：

$$C_{i,j} = \textrm{xor}_{B_{i,k}=1} A_{k,j}$$

不难验证如此定义的矩阵乘法满足结合律，且可以用 bitset 优化。

显然，$A^{(0)}$ 为 $n$ 阶单位矩阵，$A^{(1)}$ 为邻接矩阵（不妨记为 $G$）。进一步不难发现 $A^{(k)} = G^k$。那么对每次询问求出 $G^{(a_i)}$ 即可计算答案。

考虑到直接进行矩阵快速幂的复杂度是 $O(\frac{1}{w}qn^3\log a_i)$ 的（其中 $w=64$），勉强可以接受，但为了保险还可以进一步优化。

考虑分块：计算出 $B^{(0)}=G, B^{(1)}=G^{2^{8}}, B^{(2)}=G^{2^{16}}, B^{(3)}=G^{2^{24}}$ 以及它们的 $1,2,\dots,255$ 次方，这样根据矩阵乘法的结合律，我们可以利用 $256 $ 进制的思想，将一次查询转化为：
$$G^{a_i}=(B^{(0)})^{t_0}\times (B^{(1)})^{t_1}\times (B^{(2)})^{t_2}\times (B^{(3)})^{t_3}$$

其中 $t_0,t_1,t_2,t_3$ 都是 $[0,255]$ 的正整数，这样根据预处理的内容我们将一次查询的矩阵乘法次数降至了 $4$ 次。

至此，总复杂度变为 $O(\frac{n^3}{w}(t+q)\log_t a_i))$，其中恒有 $t=256,w=64$，略优于 $O(\frac{1}{w}qn^3\log a_i)$（用时大约是 $\frac{1}{2}$）。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <bitset>
#define base 256

using namespace std;
typedef long long ll;
const int MAXN = 105;
inline ll readint()
{
	ll res = 0, f = 1;
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
int n,m,q;
ll a[MAXN];
struct Matrix
{
	int n;
	bitset<MAXN> a[MAXN];
	Matrix(int nn = 0)
	{
		memset(a,0,sizeof(a));
		n = nn;
	}
	Matrix operator*(const Matrix t) const
	{
		Matrix res(n);
		for(int i = 1; i<=n; i++)
			for(int j = 1; j<=n; j++)
				if(t.a[i][j])
					res.a[i] ^= a[j];
		return res; 
	}
}b0[260],b1[260],b2[260],b3[260],G;

int main()
{
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	n = readint(), m = readint(), q = readint();
	for(int i = 1; i<=n; i++)
		a[i] = readint();
	for(int i = 1; i<=m; i++)
	{
		int u = readint(), v = readint();
		G.a[u][v] = G.a[v][u] = 1;
	}
	Matrix I(n);
	for(int i = 1; i<=n; i++)
		I.a[i][i] = 1;
	b0[0] = b1[0] = b2[0] = b3[0] = I;
	for(int i = 1; i<=256; i++)
		b0[i] = b0[i-1]*G;
	for(int i = 1; i<=256; i++)
		b1[i] = b1[i-1]*b0[256];
	for(int i = 1; i<=256; i++)
		b2[i] = b2[i-1]*b1[256];
	for(int i = 1; i<=255; i++)
		b3[i] = b3[i-1]*b2[256];
	for(int i = 1; i<=q; i++)
	{
		ll x = readint();
		int t3 = x/(base*base*base);
		x %= base*base*base;
		int t2 = x/(base*base);
		x %= base*base;
		int t1 = x/base;
		x %= base;
		int t0 = x;
		Matrix res = b3[t3]*b2[t2]*b1[t1]*b0[t0];
		ll ans = 0;
		for(int j = 1; j<=n; j++)
			if(res.a[1][j])
				ans ^= a[j];
		printf("%lld\n",ans);
	}
	return 0;
}

```


---

## 作者：lfxxx (赞：0)

首先需要观察到的事情是，无论哪一天，哪个城市，其魔法值都是若干城市初始魔法值异或的结果。

所以设计状态 $g_{i,j,k}$ 表示第 $k$ 天，城市 $i$ 的魔法值的异或中是否有城市 $j$ 的初始魔法值。由于第三维太大，我们去掉第三维，转而将 $g$ 描述的时间跨度称为一个过程。

然后假设考虑在两个过程，第 $1 \sim k_1$ 天，与第 $k_1 \sim k_2$ 天的转移中，假若知道两个过程分别的 $g_1,g_2$ 值，能否求出这两个过程前后拼接后的 $g_3$ 值。

手推一下不难得出有 ${g_3}_{i,j} = \oplus_{1 \leq k \leq n} {g_1}_{i,k} \And {g_2}_{k,j}$。

再手玩一下或者可以直接猜出来这个矩阵运算具有结合律，于是考虑矩阵快速幂，转移矩阵实际上就是邻接矩阵，但是朴素地做是 $O(q \times n^3 \log a)$，难以接受。

于是考虑修改一下状态，$g_{i,j}$ 表示城市 $i$ 的魔法值因为城市 $j$ 的贡献要异或上多少，那么最开始的 $f$ 可以作为一个 $1 \times n$ 的向量，而转移矩阵的每个位置权值也从 $1$ 改变为全集，这样修改后，我们发现将向量乘上天数对应的转移矩阵后得到的新向量就是每个城市在对应天数后的魔法值！

剩下的就简单了，考虑倍增预处理出转移矩阵的 $2^i$ 次幂，由于矩阵乘向量是 $O(n^2)$ 的，于是复杂度被优化到 $O(n^3 \log a + q \times n^2 \log a)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 114;
int n,m,q;
struct Matrix{
    int a[maxn][maxn],n,m;
    Matrix(int N=0,int M=0){
        n=N,m=M;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++) a[i][j]=0;
        return ;
    }
    Matrix operator*(const Matrix& x)const{
        Matrix res=Matrix(n,x.m);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                for(int k=1;k<=x.m;k++) res.a[i][k]^=(a[i][j]&x.a[j][k]);
            }
        }
        return res;
    }
}e,base[32];
const int U = (1ll<<32)-1;
int f[maxn];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++) cin>>f[i];
    e=Matrix(1,n),base[0]=Matrix(n,n);
    for(int i=1;i<=n;i++) e.a[1][i]=f[i];
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        base[0].a[u][v]=base[0].a[v][u]=U;
    }
    for(int i=1;i<32;i++) base[i]=base[i-1]*base[i-1];
    while(q--){
        int x;
        cin>>x;
        Matrix res=e;
        for(int i=0;i<32;i++){
            if((1ll<<i)&x) res=res*base[i];
        }
        cout<<res.a[1][1]<<'\n';
    }
    return 0;
}
```

为什么异或与运算会有结合律？

拆位考虑，你发现当只有 $0,1$ 时这相当于模 $2$ 意义下的加乘运算。

---

## 作者：phil071128 (赞：0)

前言：事实上，本题想到构造广义矩阵乘法的过程并不容易，而题解几乎都是简单给出最终做法，而并没有思维过程。更重要的，广义矩阵乘法必须要满足结合律，这一点实际上是必须要证明且不可忽略的。感觉本题的精髓并不在向量 trick 上，而是对广义矩阵乘法结合律的证明。

一点小思维，看到异或按位考虑。但是初始可能会想模拟找规律，不过可以发现相当于每一位 $\bmod 2$ 意义下的矩阵乘法。暴力做时间复杂度 $O(T(n^3)\log^2)$，多次询问可以通过 P4007 和 P6772 的 trick 变成 $O(n^3\log ^2+Tn^2\log)$，这里后面再说，不过依旧过不了，而 $\bmod 2$ 的操作显然是很浪费的。

这说明不应该按位考虑，套路的，把 32 位 `int` 状压起来，那么乘 $1$ 就相当于 $\And $ 全集，乘以 $0$ 就是 $\And \ 0$，此时矩阵乘法为 `(xor,and)` 矩阵，我们最后会证明它有结合律。

对于多次询问同一 $n$ 较大矩阵的若干次幂，我们可以提前预处理它的 $2^k$ 次方。这部分的复杂度是 $O(n^3\log ^2)$ 的。

每次询问，我们直接对指数二进制拆开，相当于初始矩阵乘以 $\log$ 个转移矩阵，这样貌似仍然是 $O(Tn^3\log)$ 的，但绝大多数情况下初始矩阵都是**向量**的形式，向量乘以矩阵只需要 $O(n^2)$ 的复杂度。所以总时间复杂度优化至 $O(n^3\log ^2+T n^2\log)$。

证明 `(xor,and)` 广义矩阵乘法有结合律：


$$
\begin{aligned}
((AB)C)_{i,j}&=\mathrm{xor} \  (AB)_{i,l}\And C_{l,j}
\\
&=\mathrm{xor} \  (\mathrm{xor} \ A_{i,k}\And B_{k,l}) \And C_{l,j}

\\
(A(BC))_{i,j}&=\mathrm{xor} \  A_{i,l}\And (BC)_{l,j}
\\
&= \mathrm{xor} \ A_{i,l}\And (\mathrm{xor} \  B_{l,k}\And C_{k,j}) 
\end{aligned}
$$

交换求和下标，即证：
$$
\mathrm{xor} \  (\mathrm{xor} \ A_{i,k}\And B_{k,l}) \And C_{l,j}=
\mathrm{xor} \ A_{i,k}\And (\mathrm{xor} \  B_{k,l}\And C_{l,j})
$$
回忆我们如何证明 `(+,*)` 矩阵的：
$$
\sum_l (\sum_k A_{i,k}\times B_{k,l})\times C_{l,j}=\sum_{l}C_{l,j}\times\sum_k A_{i,k}\times \sum_{k,l} B_{k,l}
$$
而右手边也可以拆成这样的形式，这样做的原因在于乘法对加法有分配率。那么，只需证 $\And$ 对 $\mathrm{xor}$ 有分配率：
$$
(a\  \mathrm {xor} \ b)\And c= (a\And c)\ \mathrm{xor} \ (b\And c)
$$

- 按位考虑，如果 $c=0$：

  此时 $a,b$ 无论如何取，左右两边均为 $0$。

- 如果 $c=1$：

  此时，当且仅当 $a,b$ 不同是为 $1$，否则为 $0$。可以很简单地验证。

因此：
$$
\mathrm{xor} \  (\mathop{xor} \ A_{i,k}\And B_{k,l}) \And C_{l,j}
= \mathop{\mathrm{xor}} \limits _{l} \ C_{l,j}   \And \  \mathop{\mathrm{xor}} \limits _{k} \ A_{i,k}\ \And \ \mathop{\mathrm{xor}} \limits _{k,l} \ B_{k,l}
$$
右手边同理。

upd：实际上，与运算就是 $\bmod 2$ 意义下的乘法， $\oplus $ 就是加法，感性理解的话发现和 `(+,*)` 矩阵是一样的，所以证明也不是那么必要。


```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int read(){
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil(){
	freopen("P6569_2.in","r",stdin);
	freopen("data.out","w",stdout);
}
const int U=(1ll<<32ll)-1;
struct mat{
	int a[100][100];
	mat () {
		memset(a,0,sizeof a);
	}
	void init() {
		for(int i=0;i<100;i++) a[i][i]=U;
	}
	int * operator [] (int x) {
		return a[x];
	}
	mat operator * (mat b) {
		mat c;
		for(int k=0;k<100;k++) {
			for(int i=0;i<100;i++) {
				for(int j=0;j<100;j++) {
					c.a[i][j]^=(a[i][k]&b.a[k][j]);
				}
			}
		}
		return c;
	}
}trans,mi[333];
struct vec{
	int a[100];
	vec() {
		memset(a,0,sizeof a);
	}
	vec operator * (mat b) {
		vec c;
		for(int k=0;k<100;k++) {
			for(int j=0;j<100;j++) {
				c.a[j]^=(a[k]&b.a[k][j]);
			}
		}
		return c;
	}
}v0,v;
mat ksm(mat a,int b) {
	if(b==1) return a;
	mat s=ksm(a,b/2);s=s*s;
	if(b%2==1) s=s*a;
	return s;
}
signed main(){
//	fil();
	int n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++) {
		int x=read();
		v0.a[i-1]=x;
	}
	for(int i=1;i<=m;i++) {
		int u=read(),v=read();
		trans[u-1][v-1]=trans[v-1][u-1]=U;
	}
	for(int i=0;i<=31;i++) mi[i]=ksm(trans,1ll<<i);
	for(int i=1;i<=q;i++) {
		int x=read();
		v=v0;
		for(int j=31;j>=0;j--) {
			if(x>=(1ll<<j)) {
				v=v*mi[j];x-=(1ll<<j);	
			}
		}
		cout<<v.a[0]<<"\n";
	}
	return 0;
}
```

---

## 作者：TangyixiaoQAQ (赞：0)

# 思路解析
当天城市 $x$ 的魔法值由 $1$ 天前某些城市的魔法值异或得到，$1$ 天前城市 $x$ 的魔法值由 $2$ 天前的某些城市的魔法值异或得到。由此，可以合并得到当天城市 $x$ 的魔法值由 $2$ 天前哪些城市异或得到，单次合并时间复杂度 $O(n^2)$。应用倍增思想，可以推出每个城市当天魔法值与 $1,2,4,8,16,...$ 等 $2^i$ 天前所有城市魔法值的关系。

使用 $01$ 矩阵维护上述信息。令 $f[k][i][j]$ 为 $0/1$ 代表当天城市 $i$ 的魔法值 需要/不需要 异或上 $2^k$ 天前的城市 $j$ 的魔法值。这一步可以用类似矩阵快速幂的方式完成。

单倍矩阵倍增递推 $O(n^3)$，总共进行 $O(\log a)$ 次，若对每组询问分别跑一遍矩阵倍增，则总时间复杂度为 $O(qn^3 \log a)$。显然不能通过此题。

人类的智慧：注意到只需要 $1$ 号城市的魔法值，因此可以预处理出每个相隔 $2^i$ 天的矩阵，对每组询问的天数进行二进制拆分（再次倍增），只依次合并 $1$ 号城市在 $f$ 矩阵中的对应的那一行即可。

时间复杂度 $O(n^3 \log a + qn^2 \log a)$。

# 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e2 + 10, lgN = 35;
int n, m, q, f[N], a[N];
namespace fast_read_write {
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {  //! isdigit(ch)
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')  // isdigit(ch)
        x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    return x * f;
}
inline void write(int x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}
}  // namespace fast_read_write
using namespace fast_read_write;
namespace MATRIX {
struct Matrix {
    int NN, MM, arr[N][N];
    Matrix() {
        NN = MM = 0;
        memset(arr, 0, sizeof(arr));
    }
    inline void build() {
        for (int i = 1; i <= NN; i++) {
            arr[i][i] = 1;
        }
    }
    Matrix operator*(const Matrix& brr) {
        Matrix crr;
        crr.NN = NN, crr.MM = brr.MM;
        for (int i = 1; i <= NN; i++) {
            for (int j = 1; j <= brr.MM; j++) {
                crr.arr[i][j] = 0;
                for (int k = 1; k <= MM; k++) {
                    crr.arr[i][j] ^= (arr[i][k] * brr.arr[k][j]);
                }
            }
        }
        return crr;
    }
};
}  // namespace MATRIX
using namespace MATRIX;
Matrix lg[lgN];
inline void input() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        cin >> f[i];
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        lg[0].arr[u][v] = lg[0].arr[v][u] = 1;
    }
    return;
}
// 预处理矩阵的2^i次幂
inline void init() {
    lg[0].NN = lg[0].MM = n;
    for (int i = 1; i < 32; i++) {
        lg[i] = lg[i - 1] * lg[i - 1];
    }
    return;
}
inline void solve() {
    for (int i = 1; i <= q; i++) {
        Matrix ans;
        ans.NN = 1, ans.MM = n;
        cin >> a[i];
        for (int j = 1; j <= n; j++) {
            ans.arr[1][j] = f[j];
        }
        for (int j = 0; j < 32; j++) {
            if ((a[i] >> j) & 1) {
                ans = ans * lg[j];
            }
        }
        cout << ans.arr[1][1] << '\n';
    }
    return;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    input();
    init();
    solve();
    return 0;
}
```

---

## 作者：P_VICVIC_R (赞：0)

### 思路

我们[读题](https://www.luogu.com.cn/problem/P6569)后，发现就是一个经典的矩阵快速幂优化图论DP题目。

这种题目都有一个共同的特点——可以用**邻接矩阵**。

那么我们先将图搞成邻接矩阵 $e$ ，然后我们发现本题的式子与矩阵乘法有关

具体的：

$$
f_{x,i}=e_{x,1}\times f_{1,i-1}  \oplus e_{x,2}\times f_{2,i-1} \oplus e_{x,3}\times f_{3,i-1}  \oplus \dots \oplus e_{x,n}\times f_{n,i-1} 
$$

发现这玩意长的和下面这玩意是不是有点像：

$$
C_{i,j}=A_{i,1}\times B_{1,j} \ + \ A_{i,2} \times B_{2,j} \ + \ A_{i,3} \times B_{3,j} \ + \dots + \ A_{i,n} \times B_{n,j} = \sum_{k=1}^{n} A_{i,k} \times B_{k,j} 
$$
这就是用矩阵乘法改出来的，但是不确定能不能快速幂。

考试的时候一般就猜结论了，在这里，~~（学习某人题解后决定浅搬一下）~~[（ban yun）](https://www.luogu.com/paste/t0oqqi6f)。


#### 简单的证明:

我们知道：矩阵快速幂的依据是矩阵乘法有**结合律**，不然就要一个一个矩阵相乘~~效率上天~~。

好在正经矩阵乘法有依托于**乘法分配律**的**结合律**（因为矩阵乘法本质上是加法和乘法），但是**乘法对于异或没有分配律**，所以正常情况下不能使用矩阵快速幂，但本题用的邻接矩阵是一个特例（零一矩阵）

我们用 $\oplus$ 表示题目中的“新定义矩阵乘法”，$xor^n_{i=1}$ 表示 $a_1$ 到 $a_n$ 的异或和，定义 $A,B,C,D$ 四个矩阵，考虑如下一个式子：

$$
D=A \oplus B \oplus C
$$

那么：

$$
D_{i,j}=xor^n_{f_1=1} (xor^n_{f_2=1}A_{i,f_2} \times B_{f_2,f_1}) \times C_{f1,j}
$$

我们发现：

1.$C_{i,j}=0$，那么前面的这一堆 $xor^n_{f_2=1}A_{i,f_2}\times B_{f_2,f_1}$ 之类，是什么都不重要，反正乘上 $C_{i,j}$ 之后都是 $0$，括号有没有无所谓，毕竟一堆 $0$ 的异或和还是 $0$。

2.$C_{i,j}=1$，那么前面的这一堆 $xor^n_{f_2=1}A_{i,f_2}\times B_{f_2,f_1}$ 之类乘上 $C_{i,j}$ 之后都是原本的值，所以加不加括号无所谓。

综上所述这道题**限定可以用结合律**。

最后注意本题多询问，可以将快速幂用的矩阵幂的二的次方幂（$E^{2^k}$）存一下，询问时用存好的矩阵直接乘，毕竟矩阵乘法又不是 $O(1)$ 的，如果每次都现用现推，复杂度还是有不少冗余的。（**二进制拆分**。）

完事，[代码](https://www.luogu.com.cn/paste/utb14tz1)。（如果没被我误删）

文末感谢一下@ yangrunze的题解（上文中证明的来源），写的比我好，如有侵权请私信。

---

## 作者：OldDriverTree (赞：0)

怎么题解区大部分都是人类智慧啊/jk。

本文讲解 `bitset` 优化做法。

# Solution
可以发现 $f_{x,k}$ 就等于从 $x$ 开始走恰好 $k$ 步能到的点（不同路径到同一个点算多个点）的异或和。

那么对于每个询问，只需要求出 $1$ 到每个点恰好走 $a_i$ 步的方案数，再把方案数为奇数的异或起来就是答案。

这个就和 [AT_dp_r](https://www.luogu.com.cn/problem/AT_dp_r) 做法一样，矩阵加速即可，时间复杂度为 $O(qn^3\log a)$，这个时间复杂度显然过不了，考虑优化。

可以发现答案只和方案数的 **奇偶性** 有关，考虑把矩阵改成存方案数的奇偶性。

考虑矩阵乘法式子的变化，可以发现加法得到的的奇偶性就和 $\operatorname{xor}$ 相同，乘法得到的奇偶性就和 $\operatorname{and}$ 相同。

那么式子就变成了 $C_{x,y}=\operatorname{xor}_{z=1}^n A_{x,z}\operatorname{and} B_{z,y}$。

考虑 `bitset` 优化矩阵乘法：把矩阵的存储改成 $n$ 个 `bitset`。

由于矩阵的第二维是 `bitset`，能快速处理，那么就枚举两个矩阵的第一维。

考虑枚举 $x$ 和 $z$，式子就变成了如果 $A_{x,z}=1$，那么就把 $C_x$ 的每一位异或上 $B_z$ 对应的位置。

时间复杂度为 $O(q\dfrac{n^3}w\log a)$，可以通过。

# Code
```c++
#include<bits/stdc++.h>
#define int unsigned
using namespace std;
const int N=101;
int n,m,q,a[N];

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar(); 
	return x;
}
struct Matrix
{
	bitset<N> a[N];
	Matrix() { for (int i=1;i<=n;i++) a[i].reset(); }
	void I() { for (int i=1;i<=n;i++) a[i][i]=1; }
	Matrix friend operator *(Matrix a,Matrix b)
	{
		Matrix c;
		for (int i=1;i<=n;i++)
			for (int k=1;k<=n;k++)
				if (a.a[i][k]) c.a[i]^=b.a[k];
		return c;
	}
	Matrix friend operator ^(Matrix a,int b)
	{
		Matrix ans; ans.I();
		while (b) {
			if (b&1) ans=ans*a;
			a=a*a,b>>=1;
		}
		return ans;
	}
}ans,base;

main()
{
	n=read(),m=read(),q=read();
	for (int i=1;i<=n;i++) a[i]=read();
	while (m--) {
		int x=read(),y=read();
		base.a[x][y]=base.a[y][x]=1;
	}
	while (q--) {
		ans=base^read(); int res=0;
		for (int i=1;i<=n;i++) if (ans.a[1][i]) res^=a[i];
		printf("%u\n",res);
	}
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：0)

建立邻接矩阵 $\boldsymbol A \in \mathbb F_2^{n \times n}$。不难发现每一次操作相当于一次矩阵乘法，这样可以直接计算 $\boldsymbol A^{a} \boldsymbol f_0$。但这样会 TLE，注意到基域是 $\mathbb F_2$，考虑如下方法：
$$
\begin{aligned}
(\boldsymbol A \boldsymbol B)_{ij} &= \bigoplus_k a_{ik} \wedge b_{kj} \\
&= \bigoplus_k a_{ik} \wedge b^\top_{jk} \\
&= \bigoplus_k (a_i \wedge b^\top_j)_k,
\end{aligned}
$$
（$\land$ 表示 `bool` 值上的与，$\oplus$ 表示 `bool` 值上的异或。）使用 bitset 存储，可以 $O\left(\dfrac n \omega\right)$ 算出矩阵的某一项，这样算整个矩阵乘法就是 $O\left(\dfrac{n^3}{\omega}\right)$。所以回答 $q$ 次询问的复杂度为 $O\left(\dfrac{n^3 q \max a} \omega\right)$，大概在 $5 \times 10^7$ 量级。

```cpp
#include <bits/stdc++.h>
using namespace std;

using Mat = vector<bitset<128>>;
using Vec = bitset<128>;

Mat T(Mat A) {
    Mat B(128);
    for (int i = 0; i < 128; ++ i)
        for (int j = 0; j < 128; ++ j)
            B[j][i] = A[i][j];
    return B;
}

Mat Mul(Mat A, Mat B) {
    B = T(B);
    Mat C(128);
    for (int i = 0; i < 128; ++ i)
        for (int j = 0; j < 128; ++ j)
            C[i][j] = (A[i] & B[j]).count() % 2;
    return C;
}

vector<unsigned> MMul(Mat A, vector<unsigned> x) {
    vector<unsigned> ret(128);
    for (int i = 0; i < 128; ++ i)
        for (int k = 0; k < 128; ++ k)
            ret[i] ^= (unsigned)A[i][k] * x[k];
    return ret;
}

Mat QPOW(Mat A, int n) {
    if (n == 1) return A;
    Mat B = Mul(A, A);
    if (n % 2 == 0) return QPOW(B, n / 2);
    if (n % 2 == 1) return Mul(QPOW(B, n / 2), A);
}

int n, m, q; vector<unsigned> f0(128); 
Mat A(128);

int main() {
    cin >>n >> m >> q;
    for (int k = 1; k <= n; ++ k) cin >> f0[k];
    while (m --) {
        int u, v; cin >> u >> v;
        A[u][v] = A[v][u] = 1;
    }
    while (q --) {
        int a; cin >> a;
        cout << MMul(QPOW(A, a), f0)[1] << endl;
    }
}
```

changelog:
- 7.18 创建，交了两次审核 没通过，题解不要用英文标点/ll

---

## 作者：Find_Yourself (赞：0)

和美食家那道题用到了同一个 trick。

直接算复杂度 $O(n^3\cdot q\cdot\log T)$，不行。

我们考虑倍增预处理。

定义 $B_i=A^i$，然后将询问从小到大排序，每次直接倍增相乘。

因为第一个矩阵为 $1\times n$ 的，所以单次乘法 $O(n^2)$，复杂度 $O(n^2\cdot q\cdot\log T)$。

总复杂度 $O(n^3\log T+n^2\cdot q\cdot \log T)$。

code:

```cpp
#include<bits/stdc++.h>
#define int unsigned int
using namespace std;
const int N=100+5,inf=(1LL<<32LL)-1;
struct node{int n,m,a[N][N];}ans,A[33];
node operator*(const node &x,const node &y){
  node res;res.n=x.n;res.m=y.m;for(int i=1;i<=res.n;++i)for(int j=1;j<=res.m;++j)res.a[i][j]=0;
  for(int i=1;i<=res.n;++i)for(int j=1;j<=res.m;++j)for(int k=1;k<=x.m;++k)res.a[i][j]^=x.a[i][k]&y.a[k][j];
  return res;
}
struct query{int id,v;}b[N];
int n,m,q,c[N];
bool cmp(query x,query y){return x.v<y.v;}
signed main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>m>>q;
  ans.n=1;ans.m=n;
  for(int i=1;i<=n;++i)cin>>ans.a[1][i];
  for(int i=1;i<=m;++i){
    int u,v;cin>>u>>v;
    A[0].a[u][v]=A[0].a[v][u]=inf;
  }
  A[0].n=A[0].m=n;
  for(int i=1;i<=31;++i)A[i]=A[i-1]*A[i-1];
  for(int i=1;i<=q;++i){cin>>b[i].v;b[i].id=i;}
  sort(b+1,b+q+1,cmp);
  for(int i=1;i<=q;++i){
    int t=b[i].v-b[i-1].v;
    for(int j=0;j<=31;++j){
      if((t>>j)&1){
        ans=ans*A[j];
      }
    }
    c[b[i].id]=ans.a[1][1];
  }
  for(int i=1;i<=q;++i)cout<<c[i]<<endl;
  return 0;
}

```


---

## 作者：FutaRimeWoawaSete (赞：0)

$NOI Online 3$ 第一次进全国前 $25%$ ，就是靠着把这道题分骗满进的……     

$NOIP$ 前来补补这道题增增 $rp$ ？   

可能讲思考过程的地方有点略多，请见谅。

首先这道题看到 $n ^ 3$ 针对于知识点相对较少的提高组赛场，可以联想到的算法无非两样：    

- 区间 $DP$    
- 矩阵乘法   

考场上就很快想到了矩阵乘法，就是说我们每条边连接的两个点都会互相为后一天的两个点的 $f$ 值计算，并且观察到每一个 $f_{i,j}$ 只与 $f_{v , j -1}$ 有关，也就是说我们可以采用递推的形式进行计算，而中间的优化就直接矩阵加加速就好了。    

可是当你开开心心以为这是道板子题码完后又看了看数据范围又想了想：   

cow，怎么有一个 $O(qn ^ 3logmax(a_i))$ 啊，炸成 $40pts$ 了。    

由于那时我没学过倍增，所以就骗了后面的 $30pts$ 就开始发呆了……   

现在我们的主要问题就是解决如何尽量优化这个时间复杂度，很明显如果去一个 $q$ 或者 $n$ 这个时间复杂度就很可观。     

如果往去掉 $q$ 的思路想的话，我们唯一可以选择的方法就是离线处理一波，但是很可惜这是矩阵快速幂……这条路就直接被掐死了。

如果考虑去 $n$ 的话，我们发现我们在进行查询时，一个 $n \times 1$ 的矩阵却一起计算了 $n \times n$ ，可不可以考虑在这里去一维，即我们没有 $01$ 矩阵之间的乘法。    

这时我们发现我们这个矩阵还是比较~~单薄~~，没有什么花里胡哨的东西，所以考虑倍增直接记录我们 $01$ 矩阵的 $2 ^ i$ 形式。     

这样的话我们只付出了 $O(n ^ 3logmax(a_i))$ 的预处理代价就换掉了这个 $n$ ，没多大问题了。    

最后时间复杂度 $O(n ^ 3logmax(a_i) + qn^2loga_i)$ ， 本以为还会有点小卡，结果只跑了 $300ms$ 左右……   

一翻题解，怎么还有只有 $200ms$ 的啊，哭了哭了……   

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 105;
long long n,m,q,f[Len],ques[Len],Maxq;
struct node
{
	long long a[Len][Len];
	node(){memset(a , 0 , sizeof a);}
	inline void build(){for(int i = 1 ; i <= n ; i ++) a[i][i] = 1;}
}Matrix,ans,Fir,Now,fMatrix,Multi[35];
node operator * (const node &x,const node &y)
{
	node z;
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= n ; j ++)
			for(int k = 1 ; k <= n ; k ++)
				z.a[i][j] = (z.a[i][j] ^ (y.a[i][k] * x.a[k][j]));
	return z;
}
node mul(const node x,const node y)
{
	node z;
	for(int i = 1 ; i <= n ; i ++)
		for(int j = 1 ; j <= 1 ; j ++)
			for(int k = 1 ; k <= n ; k ++)
				z.a[i][j] = (z.a[i][j] ^ (y.a[i][k] * x.a[k][j]));
	return z;
}
int main()
{
	scanf("%lld %lld %lld",&n,&m,&q);
	for(int i = 1 ; i <= n ; i ++) scanf("%lld",&f[i]);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		fMatrix.a[x][y] = fMatrix.a[y][x] = 1;
	}
	for(int i = 1 ; i <= n ; i ++) Fir.a[i][1] = f[i];
	ans.build();
	for(int i = 1 ; i <= q ; i ++)
	{
		scanf("%lld",&ques[i]);
		Maxq = max(Maxq , ques[i]);
	}
	Multi[0] = fMatrix;
	int now = 1;
	for( ; (1LL << now) <= Maxq && now <= 32 ; now ++) Multi[now] = Multi[now - 1] * Multi[now - 1];
	for(int i = 1 ; i <= q ; i ++)
	{
		ans = Fir;
		for(int j = now ; j >= 0 ; j --)
		{
			if(ques[i] >= (1LL << j))
			{
				ques[i] -= (1LL << j);
				ans = mul(ans , Multi[j]);
			}
		}
		printf("%lld\n",ans.a[1][1]);
	}
	return 0;
}
```

---

