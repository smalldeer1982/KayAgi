# New Year and Binary Tree Paths

## 题目描述

The New Year tree is an infinite perfect binary tree rooted in the node $ 1 $ . Each node $ v $ has two children: nodes indexed $ (2·v) $ and $ (2·v+1) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750G/5f3fba6843b56e8c74120fa68d53319463f26696.png)Polar bears love decorating the New Year tree and Limak is no exception. As he is only a little bear, he was told to decorate only one simple path between some pair of nodes. Though he was given an opportunity to pick the pair himself! Now he wants to know the number of unordered pairs of indices $ (u,v) $ ( $ u<=v $ ), such that the sum of indices of all nodes along the simple path between $ u $ and $ v $ (including endpoints) is equal to $ s $ . Can you help him and count this value?

## 说明/提示

In sample test, there are $ 4 $ paths with the sum of indices equal to $ 10 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF750G/c83b62a188e719702078b419fb6e934500dacd07.png)

## 样例 #1

### 输入

```
10
```

### 输出

```
4
```

# 题解

## 作者：Kelin (赞：18)

## 题意

一颗无穷个节点的完全二叉树 ，编号满足线段树分配。

求有多少条树上的简单路径编号和为 $s$ 。

$1\le s\le10^{15}$

---

## 题解

### $1.$考虑一条链

考虑从节点 $x$ 开始走的一条节点个数是 $h$ 的链。

假设一直往左子树里走 ，那么他的贡献是：

$$x\sum_{i=0}^{h-1}2^i=(2^h-1)x$$

若链从下往上的第 $i\in[1,h)$ 个点是右儿子则会给标号和带来**独立的** $\displaystyle\sum_{j=0}^{i-1}2^j=2^{i}-1$ 的贡献。

注意到 $x$ 的取值只能是 $\displaystyle\lfloor\frac{s}{2^h-1}\rfloor$ 。

证明:假设取 $x-1$  ，这条长 $h$ 的链全部往右子树里走的贡献是：

$$(2^h-1)(x-1)+\sum_{i=1}^{h-1}2^i-1=2^h-h\le 2^h-1$$

所以我们可以枚举 $h\in[1,\log_2s]$ ，并算出 $x$ ，令 $ret=s-$ 上面的贡献。

然后我们可以枚举看看能不能把某些点换成右儿子。

即从大到小贪心用 $2^{h-1}-1,\ldots,3,1$ 凑出 $ret$ 。

### $2.$考虑有分叉的情况

假设路径的 $lca$ 是 $x$ ，设从 $x$ 左儿子开始向下的链长度为 $h_1$  ，从 $x$ 右儿子开始向下的链长度为 $h_2$  ，枚举 $h_1,h_2\in[1,\log_2s]$ 。

假设这两条链都往左边走的贡献是：

$$
x+2x(2^{h_1}-1)+(2x+1)(2^{h_2}-1)+2^{h_2}-1
=(2^{h_1+1}+2^{h_2+1}-3)x+2^{h_2}-1
$$

同理 $x$ 的位置也是唯一确定的 ，令 $ret=s-$ 上面的贡献。

同样的我们可以考虑怎么用 $1,3,\ldots,2^{h_1}-1,1,3,\ldots,2^{h_2}-1$ 凑出 $ret$ 。

这样显然很难做 ，我们考虑用 $2,2^2,\ldots,2^{h_1},2,2^2,\ldots,2^{h_2}$ 来凑。

我们可以枚举选了 $n$ 个数 ，看看能不能用上面的数凑出 $ret+n$ 。

这个可以用 $O(h_1h_2)$ 的时间用数位 $DP$ 来求出。

### $3.$数位 $DP$

设 $f[i][j][k]$ 表示前 $i+1$ 位（因为待选数里没有 $1$ ）选了 $j$ 个数 ，这一位是否进位（ $k=1/0$ ）的方案数。

对于每一位枚举 $2,2^2,\ldots,2^{h_1}$ 和 $2,2^2,\ldots,2^{h_2}$ 中的这一位填不填。

注意到因为是第 $i+1$ 位如果 $i>h_1$ 那么这一位是不能选 $1$ 的 ，另一边同理。

假设 $2,2^2,\ldots,2^{h_1}$ 中这一位选了 $a\in[0,1]$  ，另外一个选了 $b\in[0,1]$ ，可得转移方程：

$$
f[i+1][j+a+b][\frac{a+b+k}2]=\sum f[i][j][k]
$$

注意转移是要满足 $\displaystyle a+b+k\equiv\lfloor\frac{ret+n}{2^i}\rfloor\pmod{2}$ 的。

具体实现~~以及卡常~~可以再看看代码思考一下。

时间复杂度 $O(\log^5s)$

```cpp
#include<bits/stdc++.h>
#define fp(i,a,b) for(int i=a,i##end=(b)+1;i<i##end;++i)
#define fd(i,a,b) for(int i=a,i##end=(b)-1;i>i##end;--i)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
using namespace std;
const int N=52;
typedef long long ll;
/*-------------------------------------------------------------------------------------*/
int m,p;ll n,ans,mi[N],f[N][2*N][2];
inline ll sub(ll a,ll b){return a>=b?a-b:a;}
inline ll calc(ll s,ll q,int a,int b,int t){
    memset(f[p],0,sizeof f[p]);f[p][0][0]=1;
    fp(i,1,log2(s)+1){
        int d=(s>>i)&1;p^=1;memset(f[p],0,sizeof f[p]);
        fp(j,0,2*i-2)fp(k,0,1)if(f[p^1][j][k])
            fp(x,0,1)if(!x||i<a)fp(y,0,1)if(!y||i<b)
                if((k+x+y)%2==d)f[p][j+x+y][(k+x+y)/2]+=f[p^1][j][k];
    }
    return f[p][t][0];
}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
    scanf("%lld",&n);mi[0]=1;ll x,ret;
    while(mi[m-1]<=n){mi[m+1]=mi[m]<<1,++m;}--m;
    fp(i,1,m)if((x=n/(mi[i]-1))>0){
        ret=n-x*(mi[i]-1);
        fd(j,i-1,0)ret=sub(ret,mi[j]-1);
        if(!ret)++ans;
    }
    fp(i,1,m)for(int j=1;mi[j]-1<=n;++j)
        if((x=(n-mi[j]+1)/(mi[i+1]+mi[j+1]-3))>0){
            ret=(n-mi[j]+1)-x*(mi[i+1]+mi[j+1]-3);
            if(!ret){++ans;continue;}
            if(i==1&&j==1){ans+=ret==5*x+1;continue;}
            fp(k,1,i+j)if(~(ret+k)&1)
                ans+=calc(ret+k,x,i,j,k);
        }
    printf("%lld",ans);
return 0;
}
```
---
${\rm upd}:2020.08.10$

修正了一些 $\LaTeX$ 排版错误和题解错误。

---

## 作者：DaiRuiChen007 (赞：5)

# CF750G 题解

[Problem Link](https://www.luogu.com.cn/problem/CF750G)

**题目大意**

> 给一棵完全二叉树，求有多少简单路径经过的点标号和为 $n$。
>
> 数据范围：$n\le 10^{15}$。

**思路分析**

先考虑一条链的情况，设这条链从 $x$ 开始，深度为 $i$，先默认全走左边，得到的权值和是 $x(2^i-1)$。

若我们把一条边从左改成右，设这条边下面有 $j$ 个点，权值和变化量就是 $2^j-1$。

注意到所有边都走右时，权值增加 $(2^1-1)+\cdots+(2^{i-1}-1)=2^i-i<2^i-1$，因此起点 $x$ 一定等于 $\left\lfloor\dfrac n{2^i-1}\right\rfloor$。

然后从大到小看每个 $2^j-1$ 要不要加入即可。

同理考虑一条路径，设去掉 LCA $x$ 后得到两条长度为 $i,j$ 的路径，还是设每条分链都向左走，那么总权值和是 $x+2x(2^i-1)+(2x+1)(2^j-1)=(2^{i+1}+2^{j+1}-3)x+2^j-1$。

假设每条分链都往右，变化量为 $2^i+2^j-i-j<2^{i+1}+2^{j+1}-2$，因此这种情况起点也是确定的，一定是 $\left\lfloor\dfrac{n-2^j+1}{2^{i+1}+2^{j+1}-3}\right\rfloor$。 

那么剩余的问题相当于在 $2^1-1\sim 2^{i-1}-1,2^1-1\sim2^{j-1}-1$ 这些数中选若干个使得和为一个定值 $r$。

考虑给每个数 $+1$，枚举选择数的个数，然后数位 dp 即可维护选 $k$ 个 $2$ 的某个次幂求出和为 $r+k$ 的方案数。

时间复杂度 $\mathcal O(\log^5n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int bit(int x) { return 1ll<<x; }
inline int dig(int x,int i) { return (x>>i)&1; }
inline int DP(int sum,int cnt,int s,int t) {
	static int f[105][2],g[105][2];
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for(int d=1;bit(d)<=sum;++d) {
		memset(g,0,sizeof(g));
		int z=dig(sum,d);
		for(int k=0;k<=cnt;++k) for(int b:{0,1}) if(f[k][b]) for(int x:{0,1}) {
			int y=z^b^x;
			if((!x||d<s)&&(!y||d<t)) g[k+x+y][(b+x+y)>>1]+=f[k][b];
		}
		swap(f,g);
	}
	return f[cnt][0];
}
signed main() {
	int n,ans=0;
	scanf("%lld",&n);
	for(int i=1;bit(i)-1<=n;++i) {
		int st=n/(bit(i)-1),rem=n-st*(bit(i)-1);
		for(int j=i-1;~j;--j) if(rem>=bit(j)-1) rem-=bit(j)-1;
		if(!rem) ++ans;
	}
	for(int i=1;bit(i)<=n;++i) for(int j=1;bit(j)-1<=n;++j) {
		int st=(n-bit(j)+1)/(bit(i+1)+bit(j+1)-3);
		if(st<=0) continue;
		int rem=n-((bit(i+1)+bit(j+1)-3)*st+bit(j)-1);
		for(int k=0;k<=i+j-2;++k) if((rem+k)%2==0) ans+=DP(rem+k,k,i,j);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Feyn (赞：5)

[My Blog](https://www.cnblogs.com/feyn)

答案路径有三种形式。一种是单点，显然是存在的。一种是一个点是另一个点的祖先，假设这个祖先是 $t$，并且枚举二者的深度差 $h$（认为 $h\ge 1$，下同），会发现一件非常有趣的事情。首先路径上每个点在二进制下都会有前缀 $t$，所以首先就有一个贡献值为 $t(2^{h+1}-1)$。然后思考除此之外的后缀 $1$ 的影响，发现从低到高的第 $i$ 位的 $1$ 会在后 $i$ 个数中出现，所以会有 $2^i-1$ 的贡献，所以呢我们希望的就是 $t(2^{h+1}-1)+\sum\limits_{i=1}^hp_i(2^i-1)=w$，其中 $p$ 是某一位是否是 $1$ 的决策。发现后面那一堆即使取满也不会达到 $2^h-1$ 的大小，所以是 $t$ 的值已经固定下来了，只需要思考是否存在合法的 $p$，贪心即可。

最后就是存在分叉的情况，假设 LCA 是 $t$，那么两个孩子应该分别是 $2t,2t+1$ 的孩子。还是按照前面的方法，枚举两个孩子和 LCA 左右孩子的深度差 $h,s$，那么总的贡献应该是 $2t(2^{h+1}-1)+(2t+1)(2^{s+1}-1)+t$，后续相应地也有 $\sum\limits_{i=1}^hp_i(2^i-1)+\sum\limits_{i=1}^sq_i(2^i-1)$ 的贡献，还是影响不到前面的，所以 $t$ 的值还是固定的。但是呢后者无法用贪心来解决，所以只能使用数位 DP 了，套用经典的做法。由于那个 $-1$ 很烦，于是枚举选择的数的个数，然后用 $f_{x,y,0/1}$ 表示已经选了最低的 $x$ 位，并且已经用了 $y$ 个数，这 $x$ 位有没有向上进位的方案，随便做就可以了。总复杂度发现是 $O(n^5)$，常数大概比较小。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
using namespace std;
const int N=55;
inline void read(int &wh){
	wh=0;char w=getchar();int f=1;
	while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
	while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
	wh*=f;return;
}

int lim=50;

inline int dep(int wh){
	int an=0;
	while(wh)++an,wh>>=1;
	return an;
}
int solve1(int h,int w){
	int t=w/((1ll<<(h+1))-1);
	if(dep(t)+h>lim||t==0)return 0;
	int left=w-t*((1ll<<(h+1))-1);
	for(int i=h;i;i--){
		int now=(1ll<<i)-1;
		if(left>=now)left-=now;
	}
	return left==0;
}
int f[N][N<<1][2];
int work(int h,int s,int want,int num){
	if(want&1)return 0;
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	int Dep=dep(want);
	for(int x=0;x<=Dep;x++)for(int y=0;y<=num;y++){
		int wt=(want&(1ll<<(x+1)))>0;
		for(int in=0;in<2;in++){
			if(f[x][y][in]==0)continue;
			for(int a=0;a<=(x<h);a++)for(int b=0;b<=(x<s);b++){
				int now=(a+b+in)&1,nxt=(a+b+in)>>1;
				if(now!=wt)continue;
				f[x+1][y+a+b][nxt]+=f[x][y][in];
			}
		}
	}
	return f[Dep+1][num][0];
}
int solve2(int h,int s,int w){
	int an=0,t=(w+1-(1ll<<(s+1)))/((1ll<<(s+2))+(1ll<<(h+2))-3);
	if(dep(t)+1+max(h,s)>lim||t==0)return 0;
	int left=w+1-(1ll<<(s+1))-t*((1ll<<(s+2))+(1ll<<(h+2))-3);
	for(int num=0;num<=h+s;num++){
		an+=work(h,s,left+num,num);
	}
	return an;
}

void solve(){
	int val,ans=0;read(val);
	if(val<(1ll<<lim))ans++;
	for(int i=1;i<lim;i++)ans+=solve1(i,val);
	for(int i=0;i<lim;i++){
		for(int j=0;j<lim;j++){
			ans+=solve2(i,j,val);
		}
	}
	printf("%lld\n",ans);
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	int test=1;
	while(test--)solve(); 
	
	return 0;
}
```

---

## 作者：_maojun_ (赞：3)

$O(\log^4V)$ 的做法。

---

前面的推导类似：

设路径 lca 为 $x$。

若不分叉，设 $x$ 下接链长度为 $h$，以下不等式：

$$(2^{h+1}-1)x\le s\le (2^{h+1}-1)(x+1)-h$$

只有一个解，即枚举 $h$ 后可以直接得到 $x$。

先假设全部选左儿子，每把一个子树深度为 $d$ 的儿子左边右，对编号和的贡献为 $2^d-1$。

相当于问 $2^1-1,2^2-1,\dots,2^h-1$ 凑出 $s-(2^{h+1}-1)x$ 的方案数。由于这些物品每个都比之前的和还要大，所以直接从大往小贪心即可，最后得到 $0$ 方案数就是 $1$，否则就是 $0$。

考虑分叉的情况，也是类似的。设左链长度为 $h_1$，右链长度为 $h_2$，则：

$$(2^{h_1+1}-1+2^{h_2+1}-2)x+2^{h_2+1}-1\le s\\\le (2^{h_1+1}-1+2^{h_2+1}-2)x+2^{h_2+1}-1+2^{h_1}-h_1-1+2^{h_2}-h_2-1$$

也是唯一解。

现在所求变为 $2^1-1,2_2-1,\dots,2^{h_1-1}-1$ 和 $2^1-1,2^2-1,\dots,2^{h_2}-1$ 凑出 $s-(2^{h_1+1}-1+2^{h_2+1}-2)x$ 的方案数，这是一个经典问题。

记 $t=s-(2^{h_1+1}-1+2^{h_2+1}-2)x-2^{h_2+1}-1$

枚举所选数的数量 $n$，求 $[i<h_1]+[i<h_2]$ 个 $2^i$ 凑出 $t+n$ 的方案数，设 $f_{i,j,k}$ 表示前 $i$ 位填好，选了 $j$ 个是否对 $i+1$ 位有进位，dp 复杂度 $O(\log^3V)$。

注意到由 $n$ 变为 $n+1$ 时，$t+n$ 只有末尾的几个位会改变，重新 dp 很亏。考虑更改状态位 $f_{i,j,k}$ 表示 $\ge i$ 的位填好，选了 $j$ 个数，前面的数对第 $i$ 位的进位为 $k$，然后每次更新这个前缀。

这样的复杂度用 $1$ 的数量势能分析：一次进位形如 `1110...` $\to$ `0001...`，消耗 $x$ 个 $1$ 才能让更新长度变为 $x+1$。那么复杂度考虑 $1$ 的个数：初始有不超过 $\log t$ 个 $1$，每次 $+1$ 会增加一个 $1$，数量均摊为 $O(\log V)$。

于是单次 dp 复杂度 $O(\log^2V)$，算上枚举总共 $O(\log^4 V)$。

```cpp
typedef long long ll;

ll f[55][110][2],C[3][3];int a[55];
inline void main(){
	ll s;scanf("%lld",&s);
	C[0][0]=C[1][0]=C[1][1]=C[2][0]=C[2][2]=1;C[2][1]=2;
	ll rs=0;f[51][0][0]=1;
	// 无分叉
	for(int h=0;(1ll<<h+1)-1<=s;h++){
		ll t=s%((1ll<<h+1)-1);
		for(int i=h;i;i--)if(t>=(1ll<<i)-1)t-=(1ll<<i)-1;
		if(!t)rs++;
	}
	// 分叉
	for(int h1=1;(1ll<<h1+1)-1<=s;h1++)for(int h2=1;(1ll<<h1+1)+(1ll<<h2+1)+(1ll<<h2)-4<=s;h2++){
		ll t=(s-(1ll<<h2)+1)%((1ll<<h1+1)+(1ll<<h2+1)-3);
		if(!t){rs++;continue;}
		for(int i=0;i<50;i++)a[i]=t>>i&1;
		for(int n=1;n<=h1+h2-2;n++){
			int p=0;a[0]++;
			for(;a[p]&2;p++){a[p]^=2;a[p+1]++;}
			if(n==1)p=50;
			for(int i=p;i;i--){
				memset(f[i],0,sizeof*f);
				for(int j=0;j<=h1+h2-2;j++)for(int o=0;o<2;o++)if(f[i+1][j][o]){
					for(int k=0;k<=(i<h1)+(i<h2)&&j+k<=h1+h2-2;k++){
						int w=(o<<1|(a[i]&1))-k;
						if(w==0||w==1)f[i][j+k][w]+=f[i+1][j][o]*C[(i<h1)+(i<h2)][k];
					}
				}
			}
			if(~a[0]&1)rs+=f[1][n][0];
		}
	}
	printf("%lld\n",rs);
}
```

---

## 作者：happybob (赞：0)

这个题有点智慧。

树上两点形态一点都不容易刻画，在这个方向上思考不是很有前途。考虑到 $x$ 的父亲为 $\lfloor \dfrac{x}{2} \rfloor$，考虑从二进制角度刻画 $u,v$ 路径点编号和。

显然 $u$ 到根路径经过点为所有前缀，所以 $u,v$ 的 LCA 即为两个数的 LCP。

现在考虑 $u,v$ 的路径点权和是什么。假设 $u,v$ 的 LCP 在 $u$ 中最靠右的位置是 $x$ 位，在 $v$ 中是第 $y$ 位，则对于 $x$ 之后的每个位置 $i$，其贡献为 $\sum \limits_{j=0}^i 2^j = 2^{i+1} - 1$。则贡献最多为 $\sum \limits_{i=0}^{x-1} 2^{i+1} - 1 + \sum \limits_{i=0}^{y-1} 2^{i+1}-1$。

而对于 LCP 部分，设 LCP 为 $a$，则贡献不难算出为 $a(2^{x+1}+2^{y+1}-3)$。不难发现 LCP 部分的最小贡献大于后面的最大贡献，所以 $x,y$ 确定时，$a$ 唯一确定，为 $\lfloor \dfrac{s}{2^{x+1}+2^{y+1}-3} \rfloor$。

后面就容易了。相当于是你有若干个 $2^i-1$，你要取若干使得和为 $s$。枚举取了多少个后从前往后背包即可。总复杂度 $O(\log^5 V)$，但其实随着枚举选的数增加 $1$，只需要对后缀的 DP 进行修改，可以优化到 $O(\log^4 V)$。

---

## 作者：Helenty (赞：0)

首先我们 ~~（充分发挥人类智慧）~~ 注意到这个我们考虑过 $1$ 的链（一下简称根为 $1$），可以加上 $2^{dep_u}+2^{dep_v}-3$ 的倍数来转化，同时你又注意到 $len$ 是 $O(\log s)$ 的，所以这是好的直接枚举 $dep_u,dep_v$ 即可。

注意到 $2^{dep_u}+2^{dep_v}-3$ 这个东西显然是大于我们所取得这个 $(u,v)$。

也就是说根不同的链的最小值最大值构成的区间是不相交的。

因此 $\lfloor\dfrac{s-2^{dep_{v-1}}+1}{2^{dep_u}+2^{dep_v}-3}\rfloor$ 就恰好是我们所要的根，所以问题就是有没有 $(u,v)$ 等于余出来的数。

我们把最小的 $(u,v)$ 拉出来减掉这个余数。

也就是说我们要从左子树 $dep_u$ 的一行和右子树 $dep_v$ 的一行各选一个到根的值。

注意到一行到根的值的差分为 $+1,+2,+1,+3,+1,+2,+1,+4$ 这个东西是一个经典数列，其前缀和的通项可以表示为 $2x-\operatorname{popcount}(x)$。

注意到 $\operatorname{popcount}(x)$ 是 $O(\log s)$ 的。

我们考虑枚举 $u,v$ 的 $\operatorname{popcount}$ 后看是否存在这样的 $u+v=t$。

这个东西我们做一个进位的数位 DP 即可。

---

## 作者：Otomachi_Una_ (赞：0)

来点人类智慧。

假设 $z=\operatorname{lca}(x,y)$。枚举 $z$ 的深度 $c$，$x,y$ 到 $z$ 的距离 $a,b$。我们即得到 $z=\overline{1z_1z_2\dots z_c}$。然后 $x$ 形如 $\overline{z0x_1x_2\dots x_a}$，$y$ 形如 $\overline{z1y_1y_2\dots y_b}$。其中 $x_i,y_i,z_i$ 都是随意挑选的。

相当于我们有 $a+b+c+O(1)$ 个 $01$ 变量 $x_i$，解决 $\sum A_ix_i=C$ 的问题。其中 $A_i,C$ 给定。

把 $A_i$ 从大到小之后直接搜索，把相同的 $A_i$ 直接合并到一起。剪枝一下跑得动。但是比较慢。

注意一下发现出现了两次的 $A_i$ 必然形如 $2^i-1,2^{i-1}-1,\dots,1$。这里直接记忆化这部分就能跑得飞快了。

---

## 作者：Arghariza (赞：0)

考虑枚举路径的 LCA 为 $x$。

如果是一条直链，设其长度（点数）为 $l$，那么一直往左子树走的话，总和就是：

$$x+2x+4x+\cdots +2^{l-1}x=(2^l-1)x\le s$$

由于 $l$ 是 $O(\log s)$ 的，考虑枚举 $l$，反解出 $x$： 

$$x\le \left\lfloor\frac{s}{2^l-1}\right\rfloor$$

不难发现这同样是 $x$ 的下界。具体地，令 $x'=x-1$，考虑从 $x'$ 一直往右子树走的路径，此时路径和取到最大，只需证明这个最大值小于 $x$ 为开头的链的最小值（一直往左走）即可：

$$\begin{aligned}x'+(2x'+1)+(2(2x'+1)+1)+\cdots&=(2^l-1)x'+2^l-l-1
\\&=(2^l-1)x-l< (2^l-1)x\end{aligned}$$

所以此时的 $x$ 是固定的。所以枚举 $l$，算出 $x$ 后自顶向下调整（将某层的左儿子翻转到右儿子）判断是否能取到 $s$ 即可。

类似直链的情况，拓展到分叉上：枚举以左儿子为开头向下的链长度（点数）为 $l_1$，右儿子为 $l_2$。这条路径的总和为：

$$\begin{aligned}f(x,l_1,l_2)&=x+(2^{l_1}-1)2x+(2^{l_2}-1)(2x+1)\\&=(2^{l_1+1}+2^{l_2+1}-3)x+2^{l_2}-1\le s\end{aligned}$$

$$x\le \left\lfloor\frac{s-2^{l_2}+1}{2^{l_1+1}+2^{l_2+1}-3}\right\rfloor$$

同样可以发现这里的 $x$ 是固定的，解出 $x$ 后令 $r=s-f(x)$。考虑翻转链上一个左儿子产生的贡献，等价于下列问题：

> 给定 $2$ 个集合 $\{2^{1}-1,2^{2}-1,\cdots ,2^{l_1}-1\}$ 和 $\{2^{1}-1,2^{2}-1,\cdots ,2^{l_2}-1\}$，从中选择若干元素，使得总和为 $r$，求方案数。

这东西显然很不好做，考虑转成 $2$ 的幂，枚举选出来元素的个数 $n$，相当于从 $\{2^1,2^2,\cdots, 2^{l_1}\}\cup\{2^1,2^2,\cdots, 2^{l_2}\}$ 中选择 $n$ 个元素，和为 $r+n$。这里的集合为可重集。

显然 $2\nmid (r+n)$ 时无解，否则整体除 $2$ 后数位 dp。令 $f_{i,j,0/1}$ 表示从小到大考虑到 $t=\frac{r+n}{2}$ 的第 $i$ 位，选了 $j$ 个数，当前位是否有进位的方案数。答案就是 $f_{\log t,n,0}$，转移的话考虑两边同时取/取一个/都不取分类讨论一下即可。

复杂度 $O(\log^5 s)$。

```cpp
// Problem: New Year and Binary Tree Paths
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF750G
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Med;

const int N = 55;

int s, n;
int f[N][N << 1][2];

int calc(int x, int y, int r, int c) {
	if ((x < 2 && y < 2) || !c) return 0;
 	memset(f, 0, sizeof(f));
	if (r & 1) f[0][1][0] = (x > 1) + (y > 1);
	else f[0][0][0] = 1, f[0][2][1] = (x > 1) && (y > 1);
	int lim = ceil(log2(r)) + 1;
	for (int i = 0; i < lim; i++) {
		for (int j = 0; j <= ((i + 1) << 1); j++) {
			for (int k = 0; k <= 1; k++) {
				int t = (r >> (i + 1)) & 1, w = f[i][j][k];
				if (k == t) {
					f[i + 1][j][0] += w;
					if (i + 1 < x - 1 && i + 1 < y - 1) f[i + 1][j + 2][1] += w;
				} else {
					if (i + 1 < x - 1) f[i + 1][j + 1][k] += w;
					if (i + 1 < y - 1) f[i + 1][j + 1][k] += w;
				}
			}
		}
	}
	return f[lim][c][0];
}

int cal(int x) {
	
}

void solve() {
	cin >> s, n = ceil(log2(s));
	if (!n) return puts("1"), void();
	int res = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int x = (s - (1ll << j) + 1) / ((1ll << (i + 1)) + (1ll << (j + 1)) - 3);
			if (!x) continue;
			int r = s - x * ((1ll << (i + 1)) + (1ll << (j + 1)) - 3) - (1ll << j) + 1;
			if (!r) { res++; continue; }
			for (int k = 0; k <= i + j; k++) {
				if ((k + r) & 1) continue;
				res += calc(i, j, (k + r) >> 1, k);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		int x = s / ((1ll << i) - 1);
		if (!x) continue;
		int r = s - x * ((1ll << i) - 1);
		if (!r) { res++; continue; }
		for (int j = i; j; j--) {
			if (r >= (1ll << j) - 1) r -= (1ll << j) - 1;
			if (!r) { res++; break; }
		}
	}
	cout << res << '\n';
}

bool Mbe;
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Med - &Mbe) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout); 
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：by_chance (赞：0)

[Link](https://codeforces.com/contest/750/problem/G)&[Submission](https://codeforces.com/contest/750/submission/222005880).

假设 $a$ 到 $b$ 的路径和为 $s$，$a,b$ 的 LCA 为 $x$。固定 $x$，设 $x$ 的深度为 $d$（$1$ 的深度为 $0$）。再固定 $a,b$ 的深度 $dl,dr$，放缩一下可以感觉到，如果 $d,dl,dr$ 固定了，那么 $x$ 至多一个。

事实上，做一下计算，固定 $x,d,dl,dr$ 时，路径和最小值当然是 $x$ 不断向左 $dl-d$ 次（算上 $x$ 经过 $dl-d+1$ 个点），$2x+1$ 不断向左 $dr-d-1$ 次；最大值是 $x$ 不断向右 $dr-d$ 次，$2x$ 不断向右 $dl-d-1$ 次。可以算出此时路径和的取值范围是

$$[(2^{dl-d+1}+2^{dr-d+1}-3)x+(2^{dr-d}-1),(2^{dl-d+1}+2^{dr-d+1}-3)(x+1)-(2^{dl-d}-1)-(dl-d)-(dr-d)]$$

那么这个式子就证实了刚才的感觉。

枚举 $d,dl,dr$，计算 $x$，假设 $s$ 离上面的左端点还有 $t$。我们把路径的两个端点在相应的层右移。找规律会发现，从一个点开始不断右移，它到根的距离增加量是这样一个数列：$1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,5,\cdots$。找规律，第 $i$ 项是 $v_2(i)+1$。对它求和得到，如果 $u$ 是 $x$ 子树内这一层的第 $n+1$ 个点，则 $u$ 到 $x$ 的路径的总和比这棵子树内第一个点增加了 $v_2(n!)+n=2n-S_2(n)$。这里 $v_2(i),s_2(i)$ 分别表示 $i$ 中 $2$ 的幂次，$i$ 在二进制下 $1$ 的个数。最后一个式子是数论中的一个熟知结论。

~~虽然有一点找规律，但是可以归纳证明，而且理解起来也不困难~~


所以我们只要求一个方程的解数：$2n-S_2(n)+2m-S_2(m)=t$。$n,m$ 就代表了左右端点分别是第几个，范围限制是 $n\lt 2^{dl-d-1},m\lt 2^{dr-d-1}$。

会发现 $S_2(n),S_2(m)\le \log_2 10^{15}\lt V=50$，所以考虑枚举 $S_2(n)+S_2(m)=q$，可以算出 $n+m=p$。对于这个问题 DP 解决，$dp_{i,j,0/1}$ 表示已经填好了 $n,m$ 的最低 $i$ 位，其中填了 $j$ 个 $1$，下一位有没有进位。递推是容易的。

时间复杂度的一个上界是 $O(V^6)$，但根本跑不满，最后跑的飞快（156ms）。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll s,ans;
ll dp[55][105][2];
ll work(ll x,int y,int lenx,int leny){
	if(lenx<leny)swap(lenx,leny);
	dp[0][0][0]=1;
	for(int i=1;i<=lenx;i++){
		int c1,c2;
		if(i>leny)c1=1,c2=0;
		else c1=2,c2=1;
		if((x>>i-1)&1){
			for(int j=0;j<=2*i;j++){
				dp[i][j][0]=dp[i][j][1]=0;
				if(j>=2)dp[i][j][1]+=c2*dp[i-1][j-2][1];
				if(j>=1)dp[i][j][0]+=c1*dp[i-1][j-1][0];
				dp[i][j][0]+=dp[i-1][j][1];
			}
		}
		else{
			for(int j=0;j<=2*i;j++){
				dp[i][j][0]=dp[i][j][1]=0;
				if(j>=2)dp[i][j][1]+=c2*dp[i-1][j-2][0];
				if(j>=1)dp[i][j][1]+=c1*dp[i-1][j-1][1];
				dp[i][j][0]+=dp[i-1][j][0];
			}
		}
	}
	return dp[lenx][y][(x>>lenx)&1];
}
int main(){
	cin>>s;
	for(int d=0;d<=50;d++)
	for(int dl=d;dl<=50;dl++)
	for(int dr=d;dr<=50;dr++){
		ll k=(1ll<<dl-d+1)+(1ll<<dr-d+1)-3;
		ll x=s/k;
		if(x<(1ll<<d)||x>=(1ll<<d+1))continue;
		ll lef=k*x+(1ll<<dr-d)-1,rig=k*(x+1)-(dl-d)-(dr-d)-(1ll<<dl-d);
		if(s<lef||s>rig)continue;
		int lx=max(dl-d-1,0),ly=max(dr-d-1,0);
		for(int i=0;i<=lx+ly;i++)
			if((i+s-lef)%2==0)ans+=work((i+s-lef)/2,i,lx,ly);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 写在前面

时隔多年，再切黑题，可堪回首，熟悉之感。

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF750G)

[CF](https://codeforces.com/problemset/problem/750/G)

### 题意

在一个无限大的二叉树上，$\forall u,\mathrm{lson}_u = 2u,\mathrm{rson}_u = 2u+1$，求有多少条简单路径的编号和为给定值。

### 分析

刚拿到这道题，看到“无限大的二叉树”，似乎很难下手，这时不妨本着先易后难的原则，试着分类讨论。

#### 情况一

当 $u$ 是 $v$ 的祖先时，原路径是一条自上而下的链，此时，我们枚举长度为 $h$，显然 $h \le \log(s+1)$

当 $u$ 一直往左子树延伸时，$sum = (2^h-1)u$。

可以算出 $u = \lfloor{\dfrac{s}{2^h-1}}\rfloor$。

因为当 $u > \lfloor{\dfrac{s}{2^h-1}}\rfloor$ 全部选左子树都太大了，当 $u < \lfloor{\dfrac{s}{2^h-1}}\rfloor$ 全选右子树也不够。

如果此时当自上而下第 $x(x \le h-1)$ 个点向右子树延伸时，它一开始和相邻左子树的差值为 $1$，每下去一层差值变为原来的两倍，故贡献为 $2^x-1$。

发现所有节点的贡献是相互独立的，所以可以背包。

**真的需要背包吗？**

再次发现有 $\forall x \ge 1,\sum_{i=1}^{x-1}2^i-1 < 2^x-1$，所以可以从大到小地“填”，此时如果差值大于等于某个节点的贡献就必须选，因为此时不选即使把所有更小的选过来也不够，因此必须选这个。

如果最后能使差值为 $0$ 则答案加一。

#### 情况二

当 $u$ 和 $v$ 互相没有祖先关系时，情况变得复杂了起来。

为了方便，我们重新设两点的 LCA 为 $u$。

我们枚举 $u$ 左链的长度为 $i$，右链的长度为 $j$。

此时，如果两链头均向左子树延伸，$sum = u + 2u \times (2^i-1) + (2u+1) \times (2^j - 1)$，即 $sum = (2^{i+1} + 2^{j+1}-3)u + 2^j - 1$，此时 $u = \lfloor{\dfrac{s-2^j+1}{2^{i+1} + 2^{j+1}-3}}\rfloor$，可以证明 $u$ 在 $i$ 和 $j$ 一定时最多只有这一个取值。

此时，我们仿照上次列出贡献，对于 $x \in [1,i-1]$，有贡献 $2^x-1$，对于 $x \in [1,j-1]$，有贡献 $2^x-1$。

但现在不能从大到小进行贪心了，因为小的的贡献和可能大于大的。

然后对这些贡献进行背包。

但你惊讶地发现这些贡献太大，背包根本存不下。

我们来到了这题最关键的一步，再思考一遍：

**真的需要背包吗？**

答案显然是否定的，对于贡献 $2^x-1$，这个减一特别烦，因为没有减一只是 $2^x$ 就可以进行数位 DP 了。

我们先枚举选的个数，设为 $k$，我们把差值加上 $k$ 作为需要的贡献，设为 $t$。

显然 $t$ 必须为偶数。

我们设计 DP 状态为 $dp_{p,c,0/1}$，表示最后 $p$ 位，选了 $c$ 个，是否需要进位的方案个数。

最后把答案加上 $dp_{len,k,0}$ 即可。

时间复杂度为 $O(\log^{5}s)$，其中 $\log 10^{15} \approx 50$，可以通过本题。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define ll long long
#define N 55
ll pw[N],dp[N][N<<1][2];
ll n,ans = 0,u,ret,t;
int h = 0;
int main()
{
	scanf("%lld",&n);
	F(i,0,50)
	{
		pw[i] = 1ll<<i;
		if(pw[i] > n+1) 
		{
			h = i-1;
			break;
		}
	}
	F(i,1,h)
	{
		u = n / (pw[i] - 1);
		ret = n - u * (pw[i] - 1);
		D(j,i-1,1)
			if(ret >= pw[j] - 1)
				ret -= pw[j] - 1;
		if(!ret) ++ans;
	}
	F(i,1,h)
		F(j,1,h)
		{
			u = (n-(pw[j]-1)) / (pw[i+1]+pw[j+1]-3);
			if(!u) continue;
			ret = n - (u * (pw[i+1]+pw[j+1]-3) + (pw[j]-1));
			F(k,0,i+j-2)
			{
				t = ret + k;
				if(t & 1) continue;
				int len = 0,lim,v1,v2;
				while(pw[len+1] <= t) ++len;
				F(p,0,len)
					F(c,0,k)
						dp[p][c][0] = dp[p][c][1] = 0;
				dp[0][0][0] = 1;
				F(p,1,len)
				{
					lim = min(k,min(p,i-1) + min(p,j-1));
					v1 = ((p < i) + (p < j)),v2 = (p < i&&p < j);
					if(((t>>p)&1)^1)
						F(c,0,lim)
						{
							dp[p][c][0] = dp[p-1][c][0];
							if(c >= 1&&v1) dp[p][c][1] += dp[p-1][c-1][1] * v1;
							if(c >= 2&&v2) dp[p][c][1] += dp[p-1][c-2][0] * v2; 
						}
					else 
						F(c,0,lim)
						{
							dp[p][c][0] = dp[p-1][c][1];
							if(c >= 1&&v1) dp[p][c][0] += dp[p-1][c-1][0] * v1;
							if(c >= 2&&v2) dp[p][c][1] += dp[p-1][c-2][1] * v2;
						}
				}
				ans += dp[len][k][0];
			}
		}
	printf("%lld",ans);
	return 0;
}//由于评测只因故障，此代码并没有通过测试而是显示 UnknowError，请谨慎对拍。
```


---

