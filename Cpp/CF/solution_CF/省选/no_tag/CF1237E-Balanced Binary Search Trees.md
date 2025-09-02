# Balanced Binary Search Trees

## 题目描述

Recall that a binary search tree is a rooted binary tree, whose nodes each store a key and each have at most two distinguished subtrees, left and right. The key in each node must be greater than any key stored in the left subtree, and less than any key stored in the right subtree.

The depth of a vertex is the number of edges on the simple path from the vertex to the root. In particular, the depth of the root is $ 0 $ .

Let's call a binary search tree perfectly balanced if there doesn't exist a binary search tree with the same number of vertices that has a strictly smaller sum of depths of its vertices.

Let's call a binary search tree with integer keys striped if both of the following conditions are satisfied for every vertex $ v $ :

- If $ v $ has a left subtree whose root is $ u $ , then the parity of the key of $ v $ is different from the parity of the key of $ u $ .
- If $ v $ has a right subtree whose root is $ w $ , then the parity of the key of $ v $ is the same as the parity of the key of $ w $ .

You are given a single integer $ n $ . Find the number of perfectly balanced striped binary search trees with $ n $ vertices that have distinct integer keys between $ 1 $ and $ n $ , inclusive. Output this number modulo $ 998\,244\,353 $ .

## 说明/提示

In the first example, this is the only tree that satisfies the conditions: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237E/4e380cf51a86e19e2f842af24fccbe15c0690783.png)

In the second example, here are various trees that don't satisfy some condition: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237E/2e8a40da0f5146c1c54bd64b0e3ffa3e8248274f.png)

## 样例 #1

### 输入

```
4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
```

### 输出

```
0
```

# 题解

## 作者：houzhiyuan (赞：13)

标签：构造。

神仙题。

手玩一下小数据，可以发现深度小于等于 $3$ 的只有树大小为 $1,2,4,5$ 四种情况，并且方案数都是 $1$。

显然，由于是平衡树，那么 $n$ 显然是根一直向右走到的点，可以发现必然与根节点奇偶性相同，所以右子树大小是偶数。

可以发现，一棵满足条件的树，它的左右子树也都必然满足条件。

所以可以从深度小的向深度大的递推。

设 $f_i$ 表示深度为 $i$ 的满足条件的平衡树的最小大小。

用归纳法证明只有大小为 $f_i,f_i+1$ 的树可以满足条件。

首先对 $i=1,2$ 显然成立。

假设对于 $i$ 成立，那么深度为 $i+1$ 的树必然是一个根再加上两个深度为 $i$ 的树。

深度为 $i$ 的树只有 $f_i,f_i+1$ 两种。

设左右两子树大小为 $L,R$，那么需要满足 $L+1$ 和 $L+R+1$ 奇偶性相同。

所以 $R$ 必然是偶数，$L$ 可以取 $f_i$ 和 $f_i+1$。

这样证明了上面的结论，也证明了方案数只可能是 $0,1$。

递推式也很简单：

$$
f_{i+1}=\begin{cases}2f_i+2&x\mod 2=1\\2f_i+1&x\mod 2=2\end{cases}
$$

[code](https://codeforces.com/contest/1237/submission/149885688)。

---

## 作者：Soulist (赞：9)

~~神仙题~~

$CF1237E ~Balanced~ Binary ~Search ~Trees$

**题意：**

需要求出有多少棵点数为$n(n\le 10^6)$点权为${1,2,...,n}$的二叉搜索树满足：

$1):$ 除了最下面一层外，所有层都是满的；

$2):$ 对于每个点，如果它有左儿子，那么左儿子的点权和它的奇偶性不同；如果它有右儿子，那么右儿子的点权和它的奇偶性相同。

答案对$998244353$取模

------

$\rm Sol:$

~~下面对于满二叉树的定义有问题，大家凑合着看吧...这里满二叉树是指满足定义$1$的树~~

可以发现定义$1$即这棵树是一个满二叉树，于是对于根节点，有除去其之后仍然有其为一颗满二叉树

设满足定义$2$的满二叉树为完美树，则可以发现由于原树为一棵二叉查找树，于是其最右边的点一定为$n$，所以有根的奇偶性与$n$的奇偶性相同

不难看出两个性质：

$1):$ 一棵完美树的子树仍然是完美树

$2):$ 由于权值为$1-n$，所以这棵二叉搜索树的中序遍历为$1-n$，每棵子树则可以对应成为一个区间

考虑假设某一个数$x$作为根，此时有$x$的奇偶性与$n$相同，则其左子树的区间可以表示为$[1,x-1]$，右子树区间则可以表示为$[x+1,n]$，且有左子树大小为$x-1$，右子树大小为$n-x$，因为$n$的奇偶性和$x$相同，所以$n-x$必然为偶数，且$x-1$的奇偶性与$x$相反，由于左子树仍然是一棵完美树，所以再使用上述结论可以得到：

**一颗完美树满足其左子树根的奇偶性与子树大小相同，而右子树大小为偶数**

接下来由于二叉搜索树只关心相对的大小关系且其某一个子树可以被表示成为一个区间$[l,r]$，所以我们使用$[1,r-l+1]$对应替换此树所有节点对于答案没有影响，容易发现假设其原先为一棵完美树则替换后仍然是一颗完美树

所以问题与原树对应的区间编号无关而之和此树大小有关

接下来考虑将两颗完美树合并成为一颗大完美树以及其合法性，按照前面的条件我们可以得到合并之后的树为完美树当且仅当：$1.$合并之后满足原树为满二叉树，$2.$右子树大小为偶数

我们可以手玩得到：大小为$1,2,3,4,5$的完美树形态如下：

$size=1:\quad 1$

$size=2:\quad 2.left\to 1$

$size=3:$ 不存在合法

$size=4:$为样例

$size=5:$仅存在一个，为：

$3.left\to 2,2.left\to1,3.right\to 5,5.left \to 4$

可以观察到除去$size=1$之外的所有完美树高度均$>1$且不为完全二叉树(完全二叉树是指全部都是满的，这种定义真的记不得...凑合看吧QAQ)

由于 **性质$1$** 我们知道对于一个大小$>5$的完美树，有其最底层仍然是一棵完美树，换而言之其除去根之后必然是不满的，所以我们可以得出一个可怕的结论：

将两颗完美树合并成一棵大小$>5$的完美树当且仅当$1.):$ 其左右子树为完美树且高度相同，$2):$右子树大小为偶数

现在我们可以设计一个非常粗略的$dp$了，令$dp_{i,j}$表示大小为$i$的完美树高度为$j$的时候的方案数，然后利用这个东西转移，转移是一个卷积的形式，这样是$O(n\log^2 n)$的做法

仔细思考会发现一个更可怕的东西

我们知道前$5$项的高度和方案数(前为高度，后为方案数)大致如此：

$(1,1),(2,1),(-,-),(3,1),(3,1)$

注意到右子树的大小仅能是$2$和$4$

对于右子树$2$而言唯一的合并是左$2$右$2$，合并得到$5$

对于右子树$4$而言唯一的合并是左$4/5$右$4$，合并得到大小为$9/10$的完美树，高度为$4$

那么这样对于大小为$6-8$的树其均不具有完美树，于是接下来可以用的大小仅有$9/10$

类似合并可以发现$9/10$仅能通过合并得到$20/21$，然后可行的为$41/42$...可以发现合法的树均只有$1$种

于是只需要拿$4/5$作为初值递推下去即可，复杂度$O(\log n)$

~~时间$3s$和$n$只有$10^6$应该是为了放其他大常数非正解做法过...~~

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
int n ; 
signed main()
{
    n = gi() ; 
    if( n == 1 || n == 2 ) puts("1") ;
    else {
        int x = 4, y = 5 ; 
        while( max( x, y ) < n ) {
            int ux = x, uy = y ;
            if( ux & 1 ) x = ux + uy + 1, y = uy + uy + 1 ;
            else x = ux + uy + 1, y = ux + ux + 1 ; 
            if( x > y ) swap( x, y ) ;
        }
        if( x == n || y == n ) puts("1") ;
        else puts("0") ;
    }
	return 0 ;
}
```

---

## 作者：Lynkcat (赞：7)

发一个逊一点的 $O(n)$ 做法。

先不考虑最后一层，也就是说现在有一棵 $d$ 层的 $n=2^d-1$ 的二叉树。并且我们选择不考虑节点的标号，只考虑其奇偶性 $0/1$，然后我们显然要是要在 $d+1$ 层上加点使得它满足其中序遍历满足 $10101010……$ 的形式，这样我们才能填上 $1\sim n$ 的每个数。

我们再次发现对于每个中序遍历上相邻位置值相同的位置，后面的必然是叶子。

证明考虑一个点，如果它下一步往右子树跳一定跳到了一个叶子，并且这个叶子如果编号奇偶性与当前点相同我们可以选择在那个叶子的左儿子处加一个点来使得其合法。

否则一个点肯定是往上跳，并且向左上方跳完一条编号奇偶性相同的链后再往右上方跳一个，这时候奇偶性显然不同，不用管。

这样就很好做了，先枚举根的标号奇偶性，直接把这棵满二叉树中序遍历求出来，再在中间加点直到满足中序遍历满足 $10101010……$ 的形式，判一下总节点个数是不是 $=n$ 即可。

$n=2$ 需要特判。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
//#define int ll
#define N 2000005
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,cnt,now,del,a[N];
int ans;
void dfs(int k,int w)
{
	if (k*2<=now)
	{
		dfs(k*2,w^1);
	}
	a[++cnt]=w;
	if (k*2+1<=now)
	{
		dfs(k*2+1,w);
	}
}
signed main()
{
	n=read();
	if (n==2) return puts("1"),0;
	now=1;
	for (int i=1;i;i++)
	{
		if (now*2-1>n)
		{
			break;
		}
		now=now*2;
	}
	now-=1;
	cnt=0;del=0;
	dfs(1,0);
	if (a[1]==0) del++;
	for (int i=1;i<cnt;i++)
	{
		if (a[i]==a[i+1])
		{
			del++;
		}
	}
	if (now+del==n) ans++;
	cnt=0;del=0;
	dfs(1,1);
	if (a[1]==0) del++;
	for (int i=1;i<cnt;i++)
	{
		if (a[i]==a[i+1])
		{
			del++;
		}
	}
	if (now+del==n) ans++;
	writeln(ans);
	
}
/*

*/




---

## 作者：w4p3r (赞：5)

~~给大家带来指定放过的$nlogn$的做法~~

怎么说，其实感觉考场上多半想到的应该还是这种解法吧（至少对我这种蒟蒻来说是这样的），毕竟又是对$998244353$取模，$n$又是$10^6$的，这种算法也被放过了，只是码量大亿点点而已。~~（然而vp时我还是没调出来）~~

首先寻找性质，设当前根节点为$u$，左儿子为$x$，右儿子为$y$。并设$l_x$表示$x$的左儿子，$r_x$表示$x$的右儿子，$sz_x$表示$x$子树的大小，$d_x$表示$x$中序遍历的序号，那么有：

$d_u \ mod \ 2 \ne \ d_x \ mod\ 2$

又因为$d_x=sz_{l_x}+1$，所以有：

$sz_x\ mod \ 2 \ne sz_{l_x} \ mod \ 2$

又因为$sz_x=sz_{l_x}+sz_{r_x}+1$

所以$sz_{r_x}\ mod \ 2 \ =0$

同理，由$d_u \ mod \ 2 = \ d_y \ mod \ 2$，可以推得：

$sz_{l_y}\ mod \ 2\ =\ 1$

发现满足条件只跟$x,y$的左子树/右子树的奇偶有关，所以假设$f_{d,x,0/1,0/1}$表示由深度为$d$的满二叉树再加上$x$个深度为$d+1$的点组成的完全二叉树，根节点的左子树大小为奇/偶，右子树大小为奇/偶。

转移方程较为简单，不再赘述（可以看代码），然后因为是个卷积形式，所以可以考虑NTT优化，时间复杂度$O(nlogn)$。

（我的代码实现是把两个$0/1$合成了一个$0/1/2/3$来表示的，并且用滚动数组优化了一下）

```cpp
//W4P3R
#include<bits/stdc++.h>
#define inf 1e9
#define eps 1e-6
#define mp make_pair
#define pb push_back
#define re register int
#define fr first
#define sd second
#define pa pair<int,int>
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define REP(i,a,b) for(re i=a;i>=b;i--)
#define MEM(a) memset(a,0,sizeof(a))
#define N 4000010
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
inline ll read()
{
	char ch=getchar();
	ll s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
inline int lowbit(int x){return x&(-x);}
int A[N],B[N],limit,l=1,C[N];
int r[N],n;
const int mod=998244353;
inline int Z(int x){return x>=mod?x-mod:x;}
int f[4][N],g[4][N];
inline int ksm(int a,int b)
{
	int ans=1;
	while(b){if(b&1)ans=1LL*ans*a%mod;b>>=1;a=1LL*a*a%mod;}
	return ans;
}
inline void NTT(int a[],int type)
{
	FOR(i,0,limit-1)if(i<r[i])swap(a[i],a[r[i]]);
	for(re mid=1;mid<limit;mid<<=1)
	{
		int wn=ksm(3,(mod-1)/(mid<<1));if(type<0)wn=ksm(wn,mod-2);
		for(re R=(mid<<1),j=0;j<limit;j+=R)
		{
			int w=1;
			for(re k=0;k<mid;k++,w=1LL*w*wn%mod)
			{
				int x=a[j+k],y=1LL*a[j+k+mid]*w%mod;
				a[j+k]=Z(x+y);a[j+k+mid]=Z(x+mod-y);
			}
		}
	}
	if(type<0){int inv=ksm(limit,mod-2);FOR(i,0,limit-1){a[i]=1LL*a[i]*inv%mod;}}
}
int main()
{
	//ios::sync_with_stdio(false);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();int Max=3;
	f[0][0]=1;f[1][1]=1;
	while(Max<n)//n个点的dp值应该是f[log2(n)][n-2^log2(n)][0/1][0/1] 
	{
		limit=1,l=0;
		while(limit<=Max*2+1)limit<<=1,l++;
		FOR(i,0,limit-1)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
		FOR(j,Max+1,limit-1)FOR(i,0,3)f[i][j]=0;
		FOR(i,0,3)NTT(f[i],1);//先把所有数组DFT了来，不然常数爆炸 
		FOR(i,0,Max*2+1)g[1][i]=Z(g[1][i]+1LL*f[0][i]*f[1][i]%mod);
		FOR(i,0,Max*2+1)g[3][i]=Z(g[3][i]+1LL*f[0][i]*f[3][i]%mod);
		FOR(i,0,Max*2+1)g[0][i]=Z(g[0][i]+1LL*f[1][i]*f[1][i]%mod);
		FOR(i,0,Max*2+1)g[2][i]=Z(g[2][i]+1LL*f[1][i]*f[3][i]%mod);
		FOR(i,0,3)NTT(g[i],-1);
		FOR(i,0,Max*2+1)FOR(j,0,3){f[j][i]=g[j][i];}
		FOR(j,0,limit-1)FOR(i,0,3)g[i][j]=0;
		Max=Max*2+1;
	}
	int t=1;
	while(t<n){t=t*2+1;}t=(t-1)/2;
	int ans=0;
	FOR(j,0,3)ans=Z(ans+f[j][n-t]);cout<<ans<<'\n';
	return 0;
}
//gl
```


**如果你觉得这篇题解对你有帮助，那你可以点个赞支持我一下qwq。如果你对题解有任何问题/认为我的题解有任何问题，可以私信/在评论区发出来，当然如果你对我的题解有任何意见/建议也欢迎指出。我会尽我全力把我题解写到最好的qwq**



---

## 作者：皎月半洒花 (赞：5)

发现这个 `balanced` 是个很强的约束，可以观察到在第一个条件下根节点只能是 $\left\lceil\dfrac{n}{2} \right\rceil$ 或者 $\left\lfloor\dfrac{n}{2} \right\rfloor$ 。然后紧接着可以发现每个子树在第一个约束下都只能是类似状态。然后考虑第二个条件，一个很重要的事实在于，可以发现键值 $n$ 永远是在最右侧的链，所以可以知道 $n$ 一定和 $root$ 的键值奇偶性相同。接着，由于右子树的点集是 $[root,n]$ ，那么不难知道**每个根的右子树 $size$ 都必然是偶数** 。

有了这些性质，可以发现对于每个 $n$ ，答案至多为 $1$ 。

证明可以考虑假设有两个均满足条件的树 $T_1,T_2$ ，那么他们一定有某部分同构，剩下的部分不同构。考虑不同构的那部分，由于要满足 `perfect balanced` ，所以可以知道「不同构」只能是把某个点的某个子树的一个点移到另一颗子树里，这要满足两个子树 size 之前相差 $1$ ，所以 $T_1,T_2$ 中必然有一棵树满足存在一个点，其右子树的 size 是奇数。所以可知答案至多为 $1$ 。

于是就可以直接从 $size=1$ 开始构造了。复杂度 $\log n$ 。

```cpp
#include <cstdio>

int n ;
int ans ;

int main(){
    ans = 1 ;
    scanf("%d", &n) ;
    while (ans <= n){
        if (ans == n || ans == n - 1) return puts("1"), 0 ;
        if (ans & 1) (ans <<= 1) += 2 ; else (ans <<= 1) += 1 ;
    }
    return puts("0"), 0 ;
}
```


---

## 作者：Nemlit (赞：5)

首先我们要注意到一个性质：由于根与右子树的根奇偶性相同，那么根的奇偶性与$N$相同

然后我们发现对于一个完美树，他的左右两个儿子都是完美树

也就是说，一颗完美树是由两棵完美树拼成的

注意到另一个性质：由于权值是一个排列，假设根节点为$x$，那么左子树的范围是$[1, x - 1]$，右子树为$[x + 1, n]$

由于根节点和$N$奇偶性相同，那么左子树的大小与$N$的奇偶性相反，所以右子树大小为偶数

如果子树区间为$[l, r]$，那么其实可以把它看成$[1, r - l + 1]$，所以只和子树大小有关，和子树权值无关

手玩一波小数据：

当$N=1$时，就是一个点

当$N=2$时，二为根，一为根的左子树

当$N=3/4$时为样例

当$N=5$时，可以用两个2的子树拼成

然后我们发现，能作为右子树的只有$2/4$，前五个都不是满二叉树，所以我们可以合并两颗树，当且仅当两个二叉树高度相同

发现2的高度为2，没有与之相同树高的树，所以能作为右子树的只有$4$

所以我们就有：用$4/5$可以凑出$9/10$，$9/10$又可以拼出$19/20$……

所以我们就可以用$4/5$一路递推下去，发现每次都*了$2$，所以复杂度为$O(logN)$
## $Code:$
```
#include<bits/stdc++.h>
using namespace std;
int main() {
	int n, x = 4, y = 5;
	scanf("%d", &n);
	if(n == 1 || n == 2) return puts("1"), 0;
	while(y < n) {
		if(x & 1) x = 2 * y, y = x + 1;
		else x = 2 * y - 1, y = x + 1;
	}
	return printf("%d", (x == n || y == n)), 0;
}

```

---

## 作者：81179332_ (赞：1)

$n$ 一定在根不停向右走的最后一个节点，则 $n$ 与根节点奇偶性相同

由于是完全二叉树，所以 $root=\lfloor\dfrac n2\rfloor\text{或}\lceil \dfrac n2\rceil$

则可以知道对于一个 $n$ 只有一种合法的根节点，由于 $root$ 和 $n$ 奇偶性相同，所以它的右子树的大小为偶数

容易发现，$root$ 的左右子树为两个高度相同的合法树，或为两个高度相差为 $1$ 且高度较小的子树是完美二叉树

考虑使用大小为 $1$ 和 $2$ 的合法树构造其他的合法树

由于右子树一定是偶数，所以只有 $2$ 可以作为右子树，所以可以构造出的树大小为 $4$ 和 $5$

我们接着构造，可以发现，虽然大小为 $2$ 和 $4$ 的子树高度相差为 $1$，但 $2$ 这个树不是完美二叉树，同理，其他用 $1,2$ 和 $4,5$ 组合的情况也是不合法的

所以只能 $4,5$ 组合，$4$ 是偶数放在右子树，所以可以构造出的树为 $9,10$

以此类推

再证明唯一性，使用数学归纳法即可，大小为 $1,2$ 的树是唯一的，对于一棵合法的树，通过上面的构造方法可知，它的左右子树要么全是偶数且相同，要么一个偶数一个奇数，这两种情况一种交换后树不变，一种无法交换，而根据数学归纳法，左右子树都是唯一的，所以这棵树是唯一的

```cpp
int n,now;
int main()
{
	now = 1,n = read();
	while(now <= n)
	{
		if(now == n || now == n - 1) { puts("1");return 0; }
		now = now * 2 + 1 + (now & 1);
	}puts("0");
}
```

---

## 作者：hhhqx (赞：0)

对 https://www.luogu.com.cn/article/fd9qi7ie 的一些补充。

step1：容易发现根的奇偶性和 $n$ 的奇偶性相同。所以根的右子树大小一定是偶数。

step2：一颗合法的树，满足根的左右子树也是合法的树。

step3：$2^k - 1$ 显然是奇数，所以一颗满二叉树（除了只有一个点的树）一定是不合法的。

step4：一个合法的树，根的左右子树也都是合法的树。

考虑两个合法的树合并为一个合法的树。

题目中要求每个点到根的距离的和最小，也就是树是一颗满二叉树在最后一层删除一些点得到。所以那两个合法的树必须高度相同为 $i$（如果不同，第一种情况是其中一棵树是满二叉树，这不合法，第二种情况反之，这样合并出来的树不合法）。

设 $f_i$ 表示深度为 $i$ 的合法的树的最小大小。对于 $i \le 2$ 先特判掉。

接下来**需要证明深度为 $i(i \ge 3)$ 的合法的数的大小值有且只有可能 $f_i$ 或 $f_i+1$**。考虑归纳法证明：

- 对于 $i=3$ 成立（暴推验证）。设根左子树大小为 $L$，根右子树大小为 $R$。
- $R$ 只能是偶数，而 $L$ 也只能是 $f_{i-1}$ 或 $f_{i-1}+1$。

顺便也得出了转移式 $f_i = 2 \times f_{i-1} + 1 + [f_{i-1} \bmod 2 = 1]$。

```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

int n, f[30];

int main(){
	cin >> n;
	if(n == 1 || n == 2 || n == 4 || n == 5){
		cout << 1;
		return 0;
	}else if(n == 3){
		cout << 0;
		return 0;
	}
	f[3] = 4;
	for(int i = 4; i <= 25; i++){
		f[i] = 2 * f[i - 1] + 1 + (f[i - 1] % 2 == 1);
		if(f[i] == n || f[i] + 1 == n){
			cout << 1;
			return 0;
		}
	}
	cout << 0;
	return 0;
}
```

---

## 作者：CarroT1212 (赞：0)

缺乏注意力，便提供一个乱搞思路。

浅手玩一下发现 $n=1,2,4,5,9,10$ 时答案都是 $1$，否则 $0$。

结合题目限制自信猜测答案只能是 $0$ 或者 $1$。

考虑直接进行 DP。设 $dp_{i,0/1}$ 表示 $n=i$ 时是否可行，如果可行的话取哪个点作根。转移时直接枚举左右子树大小 $x,y$，如果两个子树都分别有解，拼起来是完全二叉树，且记录下的根满足奇偶性限制，那就直接转移过去。$O(n^2)$。

其中完全二叉树的限制颅内风暴一下会得到它是 $x,y\ge 2^{\lfloor\log_2\lceil\frac{i}{2}\rceil\rfloor}-1$ 且 $\lfloor\log_2\max(x,y)\rfloor+1=\lfloor\log_2i\rfloor$。

考虑优化。记录下 $i$ 之前有解的所有可能子树大小，转移时只枚举那些确定有解的 $x$，算出 $y$。然后 $x,y\ge 2^{\lfloor\log_2\lceil\frac{i}{2}\rceil\rfloor}-1$ 这个限制要求 $x$ 取在某个区间内，那么在前面记录的所有有解子树大小上二分一下找到最小的可能的 $x$ 开始枚举直到 $y$ 不合法为止即可。

跑一下 $n=10^6$ 发现飞快。

正经做法移步其他题解，其实正解正好说明了上面这坨神秘 DP 的转移量确实是 $O(n)$ 的，带个二分的 $\log$。

```cpp
ll n;
pll dp[N];
vector<ll> v;
ll geh(ll x) { return x==0?-1:__lg(x); }
void mian() {
	dp[0]={1,0};
	dp[1]={1,1};
	dp[2]={1,2};
	v.pb(1),v.pb(2);
	for (ll i=4;i<N;i++) {
		ll lim=(1ll<<__lg((i-1)/2+1))-1;
		ll st=lower_bound(v.begin(),v.end(),lim)-v.begin();
		for (ll j=st;j<v.size();j++) {
			ll p=v[j]+1,x=v[j],y=i-p;
			if (y<lim) break;
			if (!dp[y].fi) continue;
			ll gx=geh(x),gy=geh(y),gg=geh(i);
			if (max(gx,gy)+1==gg) {
				if (dp[x].fi&&dp[y].fi&&(dp[x].se&1^1)==(p&1)&&(dp[y].se+p&1)==(p&1)) dp[i]={1,p};
			}
		}
		if (dp[i].fi) v.pb(i);
	}
	scanf("%lld",&n);
	cout<<dp[n].fi<<"\n";
}
```

---

## 作者：happybob (赞：0)

题意：

给定 $n$，计算有多少棵 $n$ 个点的二叉搜索树满足：

+ 树上每个点写着一个权值，权值互不相同且构成 $1\sim n$ 的排列。
+ 所有点到根的距离之和最小。
+ 点 $u$ 如果有左儿子 $v$，那么 $u$ 和 $v$ 的点权奇偶性不同；点 $u$ 如果有右儿子 $w$，那么 $u$ 和 $w$ 的点权奇偶性相同。

答案对 $998244353$ 取模。

$1 \le n \le 10^6$。$3$ 秒，$512$ MB。

解法：

考虑一个什么样的二叉搜索树是合法的。条件二显然等价于上面若干层全都填满，最后一层中选了若干个。条件 $1$ 不需要考虑，只要树的结构确定则点权必然唯一确定。条件 $3$ 是我们唯一需要考虑的。事实上我们对于每个点 $u$，对于其左儿子和右儿子，在树的中序遍历上考虑，这样可以得到形如 $u$ 左儿子或右儿子的左或右儿子子树大小为奇数或偶数的一些条件。注意到这是一个完全二叉树，直接做背包的话次数是对的。但是背包是卷积形式，上个 NTT 就做完了。

[Submission Link.](https://codeforces.com/contest/1237/submission/285994388)

---

