# Reverse Grid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cf16-final/tasks/codefestival_2016_final_i

縦 $ H $ 行、横 $ W $ 列のマス目があり、$ i $ 行目の $ j $ 列目のマスには文字 $ S_{i,j} $ が書かれています。

すぬけくんはこのマス目に対して以下の $ 2 $ 種類の操作を行うことが出来ます。

- 行リバース：行を $ 1 $ つ選び、その行をリバースする。
- 列リバース：列を $ 1 $ つ選び、その列をリバースする。

例えば、$ 2 $ 行目をリバースした後に $ 4 $ 列目をリバースすると以下のように変化します。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_codefestival_2016_final_i/2c78e6cf67ba2ff8a353121894255544acf43c84.png)

上記の操作を好きな順番で何回か行うことによって作ることの出来る文字の配置は何通り考えられるでしょうか？

## 说明/提示

### 制約

- $ 1≦H,W≦200 $
- $ S_{i,j} $ は小文字アルファベット（`a`-`z`）である。

### Sample Explanation 1

以下の $ 6 $ 通りの配置が考えられます。 !\[\](https://atcoder.jp/img/code-festival-2016-final/ddf2925467af2c9734194a886f819a2b.png)

## 样例 #1

### 输入

```
2 2
cf
cf```

### 输出

```
6```

## 样例 #2

### 输入

```
1 12
codefestival```

### 输出

```
2```

# 题解

## 作者：Francais_Drake (赞：4)

### 题意
有一个 $H\times W$ 的矩阵 $a$，可以进行若干次操作，每次选择一行或一列翻转，求最后能够生成的本质不同的矩阵有多少种。$H,W\le 200,$ 矩阵内的元素均为小写字母。
### 解法
考虑某个 $a_{i,j}$ 只会变到 $a_{H-i+1,j},a_{i,W-j+1},a_{H-i+1,W-j+1}$ 的位置。（对于 $H,W$ 为奇数的情况，可以直接乘上中间能否变化的方案数，则其他元素都有四种可能出现的位置）所以这四个元素可以看成一个四元组整体处理。设四个位置的数分别为 $a,b,c,d$，则可以通过下面的方式使得只有 $a,b,c,d$ 之间的顺序进行变化（箭头表示行/列内其他元素的顺序）：

![](https://cdn.luogu.com.cn/upload/image_hosting/cwelaeok.png)

同理其他任意三个元素也可以按照这样的方式变化，打表可以发现这些元素出现的顺序有 $12$ 种。同时可以发现将同在一行/一列的元素调换位置可得所有 $4!$ 种方式中另外 $12$ 种出现方式，意味着某行被翻转将导致该行上若干个四元组能够变换的位置同时变化。注意如果某个四元组内部出现了相同的数，则它们一定可以在某次变化后出现在同一行，它们在被翻转某行/某列后能够变换出的顺序一样，可以把对应的贡献先乘上；否则在翻转某行/某列后对应能够变换出的顺序会变化。

考虑将每一行和每一列看成点，然后对于某个内部元素互不相同的四元组 $\{a_{i,j},a_{H-i+1,j},a_{i,W-j+1},a_{H-i+1,W-j+1}\}(2i\le H,2j\le W)$，在第 $i$ 行和第 $j$ 列之间连边。在翻转某行/某列之后对应出边的四元组状态也会改变，所以可以对于某个连通块 $S$ 求出某棵生成树，然后对于树上的边的 $2^{|S|-1}$ 种状态，自顶向下确定某行/某列是否翻转（可以确定两种等效的方式），进一步确定其他所有边的状态（只会有一种）；所以该连通块对答案的贡献为 $2^{|S|-1}$。并查集维护即可，时间复杂度为 $O(HW)$。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=210;
const int maxt=maxn<<1;
const int md=1000000007; 
int n,m,i,j,k,p,w,a,b,ans=1,c[4];
int fa[maxt],siz[maxt];
char s[maxn][maxn];
int Find(int x){
	if(x==fa[x]) return x;
	return fa[x]=Find(fa[x]);
}
inline void Merge(int x,int y){
	x=Find(x); y=Find(y);
	if(x==y) return;
	if(siz[x]>siz[y]) swap(x,y);
	fa[x]=y; siz[y]+=siz[x]; siz[x]=1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i) scanf("%s",s[i]+1);
	a=(n>>1)+1; b=(m>>1)+1;
	if(n&1){
		for(i=1;s[a][i]==s[a][m-i+1]&&i<=m;++i);
		if(i<=m) ans<<=1;
	}
	if(m&1){
		for(i=1;s[i][b]==s[n-i+1][b]&&i<=n;++i);
		if(i<=n) ans<<=1;
	}
	for(i=1,j=a+b-2;i<=j;++i) fa[i]=i,siz[i]=1;
	for(i=1;i<a;++i){
		for(j=1;j<b;++j){
			char t[4]={s[i][j],s[i][m-j+1],
					   s[n-i+1][j],s[n-i+1][m-j+1]};
			sort(t,t+4); w=24;
			for(k=c[p=0]=1;k<4;++k)
				w/=(++c[p+=(t[k]!=t[k-1])]);
			if(p==3) Merge(i,a+j-1),w=12;
			ans=(1LL*ans*w)%md;
			memset(c,0,(p+1)<<2);
		}
	}
	for(i=1,j=a+b-2;i<=j;++i)
		for(w=siz[i];--w;ans-=((ans<<=1)>=md)*md); 
	printf("%d\n",ans);
}
```

---

## 作者：xtx1092515503 (赞：2)

首先可以把翻转看成某种置换。~~于是事实上本题就是给定矩阵在置换群操作下的轨道大小求解~~。

但是事实上不需要使用轨道之类高深的群论技巧。具体而言，观察到某个格子中的元素仅可能出现在四个位置中，列出四个位置如下图：

```
  .  .
  .  .
..A..B..
  .  .
  .  .
..C..D..
  .  .
  .  .
```

即图中的 `ABCD` 四个位置，它们在矩阵中的位置是对称的。

然后接着我们可以发现先翻转 `AC`，再翻转 `CD`，再翻转 `AC`，再翻转 `CD` 后，除了 `ACD` 三个元素以外其它所有元素的位置都没变，而这三个元素循环了一位。

除了 `ACD` 间可以这么做以外，`ABC`，`ABD`，`BCD` 都可以被实现。于是把这些操作结合起来写一个程序验证一下，发现这四种操作总共可以组合出 $12$ 种不同的操作。

四个元素的排列总共有 $24$ 种。而我们发现，只要 `ABCD` 中任两个元素被交换，再结合上述四种操作，都可以得到剩下 $12$ 种操作。

注意到我们可以翻转一行或一列使得其中所有四元组的置换由原本的 $12$ 种变成另 $12$ 种。这意味着我们如果把每个四元组的状态用一个 `bit` 来表示，则每个四元组翻转与否的状态即可用一个 $O(nm)$ 的二进制数来表示。翻转每行每列的操作就对应了异或关系。

这很明显是一个线性基问题。可以直接解出所有翻转操作对应二进制数构成的集合的秩来解决问题。但是需要注意的是，有时正 $12$ 种和反 $12$ 种操作是等效的。具体而言，除非 `ABCD` 四个元素都不同，否则正反操作是等效的。于是，对于存在相同元素的位置，直接把它对应的位从二进制数中删去即可。

还有就是当 $n,m$ 为奇数时，正中央的那一行/列的四元组退化了。这时就直接暴力验证一下翻转操作会不会改变矩阵即可。

线性基的秩求解可以用 `bitset` 优化。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m,res=1;
struct perm{
	int a[4];
	perm(){memset(a,0,sizeof(a));}
	int&operator[](const int&x){return a[x];}
	friend perm operator*(perm&u,perm&v){
		perm w;
		for(int i=0;i<4;i++)w[i]=v[u[i]];
		return w;
	}
	friend bool operator<(const perm&u,const perm&v){
		for(int i=0;i<4;i++)if(u.a[i]!=v.a[i])return u.a[i]<v.a[i];
		return false; 
	}
};
set<perm>s;
char g[210][210];
bool sp[110][110];
bitset<10100>bs[210];
int main(){
	perm p;
	p[0]=1,p[1]=2,p[2]=0,p[3]=3;s.insert(p);
	p[0]=2,p[2]=3,p[3]=0,p[1]=1;s.insert(p);
	p[0]=1,p[1]=3,p[3]=0,p[2]=2;s.insert(p);
	p[0]=0,p[1]=2,p[2]=3,p[3]=1;s.insert(p);
	p[0]=0,p[1]=1,p[2]=2,p[3]=3;s.insert(p);
	for(int i=0;i<s.size();i++){
		set<perm>t=s;
		for(auto x:t)for(auto y:t)s.insert(x*y);
	}
//	for(auto x:s)printf("%d %d %d %d\n",x[0],x[1],x[2],x[3]);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%s",g[i]+1);
	for(int i=1;i<=(n>>1);i++)for(int j=1;j<=(m>>1);j++){
		int I=(n+1)-i,J=(m+1)-j;
		set<perm>t;
		perm p;p[0]=g[i][j],p[1]=g[i][J],p[2]=g[I][j],p[3]=g[I][J];
		for(auto x:s)t.insert(x*p); 
		res=1ll*res*t.size()%mod;
		bool ok=true;
		for(int u=0;u<4;u++)for(int v=u+1;v<4;v++)if(p[u]==p[v])ok=false;
		sp[i-1][j-1]=ok;
	}
	if(n&1){
		bool ok=false;
		for(int i=1;i<=m;i++)if(g[(n+1)>>1][i]!=g[(n+1)>>1][m-i+1])ok=true;
		if(ok)(res<<=1)%=mod;
	}
	if(m&1){
		bool ok=false;
		for(int i=1;i<=n;i++)if(g[i][(m+1)>>1]!=g[n-i+1][(m+1)>>1])ok=true;
		if(ok)(res<<=1)%=mod;
	}
	n>>=1,m>>=1;
//	for(int i=0;i<n;i++){for(int j=0;j<m;j++)printf("%d",sp[i][j]);puts("");}
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(sp[i][j])bs[i].set(i*m+j),bs[n+j].set(i*m+j);
	for(int i=0,j=0;i<n*m;i++){
		if(!bs[j].test(i))for(int k=j+1;k<n+m;k++)if(bs[k].test(i)){swap(bs[j],bs[k]);break;}
		if(!bs[j].test(i))continue;
		(res<<=1)%=mod;
		for(int k=j+1;k<n+m;k++)if(bs[k].test(i))bs[k]^=bs[j];
		j++;
	}
	printf("%d\n",res);
	return 0;
} 
```





---

## 作者：masterhuang (赞：0)

> 给定 $n\times m$ 的 $a\sim z$ 字母矩阵，可以进行任意次行 $\text{reverse}$ 或列 $\text{reverse}$，求最终可能的不同矩阵形态个数，对 $10^9+7$ 取模。
>
> $1\le n,m\le 200$

考虑某个 $a_{i,j}$ 只会变到 $a_{n-i+1,j},a_{i,m-j+1},a_{n-i+1,m-j+1}$​ 的位置。

> 特别的，若 $n$ 是奇数，则中间那行怎么动都不影响，应该先看看是否 $\times 2$。$m$ 同理。特判后忽略所有中间行。

所以这四个元素可以看成一个**四元组整体**处理。设四个位置的数分别为 $a, b, c, d$，则可以通过下面的方式使得只有 $a, b, c, d$ 之间的顺序进行变化（箭头表示行/列内其他元素的顺序）：

```
a-b      b-a	   c-a		a-c		 b-c
| | ---> | |  ---> | | ---> | | ---> | |
c-d      c-d	   b-d		b-d		 a-d
```

于是注意到 $a,b,c$ 可以任意换位置。

同理这四个中的**任意三个字母可以任意换位置**，并且不影响其他字母。

结合起来打表，发现此时能凑出 $4!=24$ 种中的 $12$ 种。

> 其中：如果存在至少两个数相同，那么其实我们凑全了所有变换，就不必担心下面问题，但是贡献系数就不一定是 $12$ 了，自己组合计数算一下。

如果不全相同呢？我们可以发现将同在一行/一列的元素调换位置可得所有 $4!$ 种方式中另外 $12$​ 种出现方式，但是此时影响了其他位置。

接下来考虑将每一行和每一列看成点，然后对上述**互不相同**的四元组 $\{a_{i,j}, a_{n-i+1,j}, a_{i,m-j+1}, a_{n-i+1,m-j+1}\}(2i \leq H, 2j \leq W)$，在第 $i$ 行和第 $j$ 列之间连边。

在翻转某行/列之后对应出边的四元组状态也会改变，所以可以对于某个连通块 $S$ 求出某棵生成树，然后对于树上的边的 $2^{|S|-1}$ 种状态，自顶向下确定某行/列是否翻转（可以确定两种等效的方式），进一步确定其他所有边的状态（只会有一种）。

所以该连通块对答案的贡献为 $2^{|S|-1}$。并查集维护即可，时间复杂度为 $O(nm)$​。

---

## 作者：unputdownable (赞：0)

看到置换题，先上传统艺能 $x,y,x^{-1},y^{-1}$ 观察一下有什么效果：

$$
\begin{aligned}
\texttt{abcd}&&\texttt{\color{red}dcba}&&\texttt{dcb\color{red}g}&&\texttt{\color{red}gbcd}&&\texttt{gbc\color{red}a}\\
\texttt{...e}&&\texttt{...e}&&\texttt{...\color{red}f}&&\texttt{...f}&&\texttt{...\color{red}e}\\
\texttt{...f}&&\texttt{...f}&&\texttt{...\color{red}e}&&\texttt{...e}&&\texttt{...\color{red}f}\\
\texttt{...g}&&\texttt{...g}&&\texttt{...\color{red}a}&&\texttt{...a}&&\texttt{...\color{red}d}\\
\end{aligned}
$$
注意到可以保持其他位置不变而 $\texttt{a,d,g}$ 三个位置循环位移。

--------

记 $s_{i,u},s_{n-i+1,u},s_{i,m-u+1},s_{n-i+1,m-u+1}$ 为一个**四元组**。（就是 $i,u$ 关于横纵两条对称轴对称出来的四个点）

四元组之间相对是独立的，四元组内元素只会在组内交换。

如果限定只能使用上面那个循环移位 $3$ 个数的操作，方案数是好算的；此时四元组之间完全独立，对于每个四元组单独算答案就好。

但是这样显然不能构造出所有可能的字符矩阵，因为只用上述操作，四个元素互不相同的四元组内部只能达到 $12$ 种状态，而非 $4!=24$ 种，这是因为**逆序对奇偶性**的限制。

如果四元组内部有相同元素，那么交换相同元素就可以抵消奇偶性，对于这些四元组，可以只用上述操作构造出所有状态。

而奇偶排列数量相等，所以相当于只需要计算**互不相同的四元组**有多少可能的奇偶性状态。

逆序对奇偶性可以且只可以通过单独的操作改变。（下图 $\texttt{X}$ 只表示占位）
$$
\begin{aligned}
\texttt{\color{blue}X\color{green}X\color{red}XX\color{green}X\color{blue}X}&&\texttt{\color{blue}X\color{green}X\color{red}XX\color{green}X\color{blue}X}\\
\texttt{\color{orange}X\color{purple}X\color{cyan}XX\color{purple}X\color{orange}X}&&\texttt{\color{orange}X\color{black}.\color{cyan}XX\color{black}.\color{orange}X}\\
\texttt{\color{orange}X\color{purple}X\color{cyan}XX\color{purple}X\color{orange}X}&&\texttt{\color{orange}X\color{black}.\color{cyan}XX\color{black}.\color{orange}X}\\
\texttt{\color{blue}X\color{green}X\color{red}XX\color{green}X\color{blue}X}&&\texttt{\color{blue}X\color{green}X\color{red}XX\color{green}X\color{blue}X}\\
\end{aligned}
$$
只关注左上角，有相同元素的四元组相当于从里面扣掉一些变成空白。

~~不想动脑~~，剩下的部分只需要暴力线性基即可。

对于 $n,m$ 是奇数时，记得分讨四元组退化为两元组甚至单点的情况。

复杂度最劣 $O(\frac{nm(n+m)^2}w)$，但是实际上跑的飞快，代码：

```c++
const int p=1000000007;
inline int ksm(int x,int a=p-2) {
    int res=1;
    for(; a; a>>=1,x=1ll*x*x%p) (a&1) && (res=1ll*res*x%p);
    return res;
} 
int n,m,mul,Ans;
char s[203][203];
int num[103][103],cntnum;
int vis[10004],cnt; 
bitset <10004> b[10004],cur;
inline void insert(void) {  // insert cur into b
    while(1) {
        int pos=cur._Find_first();
        if(pos==cur.size()) return ;
        if(!vis[pos]) {
            vis[pos]=1;
            ++cnt;
            b[pos]=cur;
            return ;
        }
        cur^=b[pos];
    }
}
signed main() {
    n=read(); m=read(); mul=1;
    for(int i=1; i<=n; ++i) scanf("%s",s[i]+1);
    int H=(n+1)/2,W=(m+1)/2;
    for(int i=1; i<=H; ++i) {
        for(int u=1; u<=W; ++u) {
            if(i*2==n+1&u*2==m+1) {
                continue;
            } else if(i*2==n+1) {
                char a=s[i][u],b=s[i][m-u+1];
                if(a==b) continue;
                num[i][u]=++cntnum;
            } else if(u*2==m+1) {
                char a=s[i][u],b=s[n-i+1][u];
                if(a==b) continue;
                num[i][u]=++cntnum;
            } else {
                char tmp[4]={s[i][u],s[i][m-u+1],s[n-i+1][u],s[n-i+1][m-u+1]};
                sort(tmp,tmp+4);
                if((tmp[0]!=tmp[1])&&(tmp[1]!=tmp[2])&&(tmp[2]!=tmp[3])) { num[i][u]=++cntnum; mul=mul*12%p; continue; }
                int res=1;
                while(next_permutation(tmp,tmp+4)) ++res;
                mul=mul*res%p;
            }
        }
    }
    for(int i=1; i<=H; ++i) {
        cur.reset();
        for(int u=1; u<=W; ++u) if(num[i][u]&&(2*u!=m+1)) cur[num[i][u]]=1; 
        insert();
    }
    for(int u=1; u<=W; ++u) {
        cur.reset();
        for(int i=1; i<=H; ++i) if(num[i][u]&&(2*i!=n+1)) cur[num[i][u]]=1; 
        insert();
    }
    Ans=ksm(2,cnt)*mul%p;
    write(Ans); puts("");
    // fprintf(stderr,"%.4lf\n",1.0*clock()/CLOCKS_PER_SEC);
    return 0;
}
```

---

