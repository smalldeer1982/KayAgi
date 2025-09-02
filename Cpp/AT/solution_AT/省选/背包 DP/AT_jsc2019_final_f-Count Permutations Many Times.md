# Count Permutations Many Times

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jsc2019-final/tasks/jsc2019_final_f

長さ $ N $ の数列 $ A_0,A_1,\cdots,A_{N-1} $ があります。 次の $ Q $ 個の質問に答えてください。

- 質問 $ i $ ($ 0\ \leq\ i\ \leq\ Q-1 $): 整数 $ L_i,R_i $ ($ 0\ \leq\ L_i\ <\ R_i\ \leq\ N $) が与えられる。 $ (0,1,\cdots,N-1) $ の順列 $ p_0,p_1,\cdots,p_{N-1} $ であって、次の条件をみたすものの個数を求めよ。
  - 全ての $ j $ ($ L_i\ \leq\ j\ <\ R_i $) について、$ p_j\ \neq\ A_j $ である。

ただし、答えは非常に大きくなることがあるので、$ 998244353 $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2000 $
- $ 0\ \leq\ A_i\ \leq\ N-1 $
- $ 1\ \leq\ Q\ \leq\ 2000 $
- $ 0\ \leq\ L_i\ <\ R_i\ \leq\ N $
- 入力される値はすべて整数である。

### Sample Explanation 1

例えば質問 $ 0 $ について考えると、条件をみたす順列は $ (1,0,2),(1,2,0),(2,0,1),(2,1,0) $ の $ 4 $ 通りです。

## 样例 #1

### 输入

```
3 6
0 0 0
0 1
0 2
0 3
1 2
1 3
2 3```

### 输出

```
4
2
0
4
2
4```

## 样例 #2

### 输入

```
3 6
0 1 2
0 1
0 2
0 3
1 2
1 3
2 3```

### 输出

```
4
3
2
4
3
4```

## 样例 #3

### 输入

```
10 10
7 9 4 8 0 6 7 8 9 8
0 5
4 7
3 10
7 10
7 9
4 9
0 3
6 9
4 9
1 3```

### 输出

```
2170680
2656080
1712520
2620800
2943360
2170680
2656080
2656080
2170680
2943360```

# 题解

## 作者：CYZZ (赞：10)

## [Count Permutations Many Times](https://www.luogu.com.cn/problem/AT_jsc2019_final_f)

模拟赛考场上费劲心思想出正解，结果时限 6s 冲过一堆暴力，服了。不过好在我目前是 luogu/AT 最优解。

个人认为模拟赛上的 subtask 比较有启发性，所以笔者按 sub 的顺序讲。

### Sub1：$n\le 18$

$18$ 这个数让人想到 $2^n$，此时无非就两种做法：容斥或状压，我在考场上想的是容斥。

经典容斥，钦定一个点集 $S\subset [L,R]$ 使得 $S$ 中的点**必须满足** $p_j=a_j$，剩下的点任取的方案为 $f(S)$ ，答案就是 $\sum_{S}(-1)^{|S|}f(S)$。

不难发现 $f(S)$ 的取值基本固定：

- 若 $i\in S,a_i$ 中有重复的数，由于 $p$ 为排列，所以 $f(S)=0$。
- 如果没有重复的数，由于其他点任取，所以 $f(S)=(n-|S|)!$。

暴力枚举 $S$，暴力计算 $f(S)$，复杂度 $O(2^nn)$。

### Sub2：$a_i=i$

枚举 $S$ 复杂度太高了。我们发现 $f(S)$ 只与 $|S|$ 有关，并且 $a_i=i$ 保证了 $S$ 中不可能有相等数，所以 $f(S)$ 必定为 $(n-|S|)!$。

我们把 $|S|$ 相同的 $f(S)$ 合在一起计算，令 $g(i)=\sum_{|S|=i}f(S)=\binom{r-l+1}{i}\times (n-i)!$。

得到 $ans=\sum_i(-1)^ig(i)$。复杂度 $O(qn)$。

### Sub3：$Q=1$

我们考虑 $g(i)$ 的本质：我们把每个 $a_i$ 看成一种颜色，$g(i)$ 为**在 $a_{l \sim r}$ 中选取 $i$ 个不同颜色的数的方案数**。

这个形式看起来很简单，有一种想法是莫队直接维护。

很不幸，笔者在考场上想了 30min，并没有想出直接莫队的方法。先把它扔在一边。

我们回到 $Q=1$，这给了我们一个机会，可以用单次询问 $O(n^2)$ 的高复杂度 dp 计算。

设 $dp_{i,j}$ 表示考虑了前 $i$ 种颜色，已经选出来了 $j$ 个不同数的方案数。

转移：$dp_{i,j}\leftarrow dp_{i-1,j}+dp_{i-1,j-1} \times cnt_i$，其中 $cnt_i$ 表示颜色为 $i$ 的数的个数。

最终 $g(i)=dp_{col,i}$。$col$ 为 $a_{l\sim r}$ 中颜色的总数。

复杂度 $O(qn^2)$，也是能冲过去的做法。

### 正解

考虑优化这个 dp。我们把莫队捡回来，试着**一边莫队一边 dp**。

令 $len=r-l+1$，我们需要**动态维护 $dp_{len}$**。

分析加入一个数 $x$ 造成的影响（删除类似）。发现只有 $cnt_x$ 变了。

一个简单但重要的观察：**颜色的枚举顺序并不影响最终结果**，这启示我们进行**可撤销 dp**。

类似可撤销背包，我们进行下面的操作：

1.  撤销颜色 $x$ 的影响，即 $dp_{len-1,j}\coloneqq dp_{len,j}-dp_{len-1,j-1}\times cnt_x$。

2.  算上新加进来的 $x$，即 $cnt_x\coloneqq cnt_x+1$。

3.  重新计算 $dp_{len}$，即 $dp_{len,j}\coloneqq dp_{len-1,j}+dp_{len-1,j-1}\times cnt_x$。

这样，我们就完成了一次莫队指针的移动，单次复杂度 $O(n)$。

因为我们把单次 $O(n^2)$ 的 dp 摊进莫队里，默认 $n,q$ 同阶，总时间复杂度 $O(n^2\sqrt{n})$。

### 代码

[提交记录](https://atcoder.jp/contests/jsc2019-final/submissions/55899798)

### 后记

这应该是我模拟赛上切过最难的题，留个纪念。

其实我考场上文件名写错了，100pts -> 0pts，哭晕。

---

## 作者：Inui_Sana (赞：8)

模拟赛题。赛时暴力被放过了。

考虑如下 $O(n^2q)$ 暴力：将询问区间拎出来成一个序列并排序，设 $dp_{i,j}$ 表示前 $i$ 个数，已经钦定了 $j$ 个位置 $a_i=p_i$。转移是 naive 的，枚举当前位置是否钦定即可。因为有重复数字所以再加一维 $0/1$ 表示当前相同数字是否选过。最后乘上没钦定的数量的阶乘。

然后考虑优化。考虑分治，因为不同的数字之间不关联，考虑将前后两半出现过的不同元素数平均。然后考虑合并两边答案，会发现要进行的操作类似 $dp_{l,i}\times dp_{r,j}\to dp_{r,i+j}$ 。是卷积形式，使 NTT。单次时间复杂度是 $T(n)=2T(\frac{n}{2})+O(n\log n)=O(n\log^2n)$。总复杂度为 $O(nq\log^2n)$。可能需要一定卡常。

冷知识：暴力卷积刚好卡过。某些实现的好的（可能是内存访问连续的）$O(n^2q)$ 暴力也能过。

code：

```cpp
int n,m,q,pw[27][2],a[N],b[N],fac[N],dp[N][N<<1],to[N<<1];
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1){
			ret=1ll*ret*x%mod;
		}
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
const int G=3,iG=qpow(G,mod-2);
void NTT(int id,int n,bool op){
	rep(i,0,n-1){
		if(i<to[i]){
			swap(dp[id][i],dp[id][to[i]]);
		}
	}
	for(int k=2,lg=1;k<=n;k<<=1,lg++){
		int p=1,dt=op?pw[lg][0]:pw[lg][1],l=k/2;
		for(int i=0;i<n;i+=k){
			int p=1;
			rep(j,i,i+l-1){
				int tmp=1ll*dp[id][j+l]*p%mod;
				dp[id][j+l]=Mod(dp[id][j],mod-tmp);
				dp[id][j]=Mod(dp[id][j],tmp);
				p=1ll*p*dt%mod;
			}
		}
	}
	if(!op){
		int tmp=qpow(n,mod-2);
		rep(i,0,n-1){
			dp[id][i]=1ll*dp[id][i]*tmp%mod;
		}
	}
}
void solve(int l,int r){
	int cnt=0;
	rep(i,l,r){
		cnt+=b[i]!=b[i-1];
	}
	if(cnt==1){
		dp[r][0]=1,dp[r][1]=mod-(r-l+1);
		return;
	}
	int tmp=0,p=0;
	rep(i,l,r){
		tmp+=b[i]!=b[i-1];
		if(tmp==cnt/2+1){
			p=i-1;
			break;
		}
	}
	tmp--;
	solve(l,p),solve(p+1,r);
	int len=1;
	while(len<=cnt){
		len<<=1;
	}
	rep(i,0,len-1){
		to[i]=(to[i>>1]>>1)|((i&1)?((len+1)>>1):0);
	}
	rep(i,tmp+1,len){
		dp[p][i]=0;
	}
	rep(i,cnt-tmp+1,len){
		dp[r][i]=0;
	}
	NTT(p,len,1),NTT(r,len,1);
	rep(i,0,len-1){
		dp[r][i]=1ll*dp[r][i]*dp[p][i]%mod;
	}
	NTT(r,len,0);
}
void Yorushika(){
	read(n,q);
	fac[0]=1;
	rep(i,1,n){
		read(a[i]);
		fac[i]=1ll*fac[i-1]*i%mod;
	}
	b[0]=-1;
	rep(i,1,20){
		pw[i][0]=qpow(G,(mod-1)/(1<<i));
		pw[i][1]=qpow(iG,(mod-1)/(1<<i));
	}
	while(q--){
		int l,r;read(l,r);
		l++;
		rep(i,l,r){
			b[i-l+1]=a[i];
		}
		m=r-l+1;
		sort(b+1,b+m+1);
		int cnt=0;
		rep(i,1,m){
			if(b[i]!=b[i-1]){
				cnt++;
			}
		}
		solve(1,m);
		int ans=0;
		rep(i,0,cnt){
			ans=Mod(ans,1ll*dp[m][i]*fac[n-i]%mod);
		}
		printf("%d\n",ans);
	}
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

但是考场上忘了 NTT 怎么写于是写了个 $O(n^2q)$，模拟赛数据跑了 700ms。

---

## 作者：WOL_GO (赞：6)

看见不强制在线的多次求区间问题，可以考虑莫队。

## 思路

因为这题数据范围 $n \le 2000$，普通莫队时间复杂度是 $O(n \sqrt{n})$，所以我们考虑 $O(n)$ 转移。我们考虑容斥，维护当前区间的答案。对于新加入的数，我们只需要维护这个数的贡献，即 $\frac{1+\left(\text{t }_{a_{i}}+1\right)x}{1+\operatorname{t}_{a_{i}} x}$（其中 $t_{a_{i}}$ 是 $a_{i}$ 出现的次数）。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+5,mod=998244353;
int cnt[maxn],n,m,a[maxn],l,r,sum,sqrn,frac[maxn],ans[maxn];
struct que{
	int x,y,id;
}q[maxn];
bool cmp(que x,que y){
	if (x.x/sqrn!=y.x/sqrn) return x.x<y.x;
	if (x.x/sqrn&1)return x.y<y.y;
	return x.y>y.y;
}
bool tmp(que x,que y){
	return x.id<y.id;
}
vector<int>f;
void add(int x){
    if(cnt[a[x]]){
        for(int i=1;i<f.size();i++)f[i]-=f[i-1]*cnt[a[x]],f[i]=(f[i]+mod)%mod;
	    f.pop_back();
    }
	cnt[a[x]]++;
	if(cnt[a[x]]){
        f.push_back(0);
	    for(int i=f.size()-1;i;i--)f[i]+=f[i-1]*cnt[a[x]],f[i]%=mod;
    }
}
void del(int x){
    if(cnt[a[x]]){
        for(int i=1;i<f.size();i++)f[i]-=f[i-1]*cnt[a[x]],f[i]=(f[i]+mod)%mod;
	    f.pop_back();
    }
	cnt[a[x]]--;
	if(cnt[a[x]]){
        f.push_back(0);
	    for(int i=f.size()-1;i;i--)f[i]+=f[i-1]*cnt[a[x]],f[i]%=mod;
    }
}
main(){
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    sqrn=sqrt(n);
    f.emplace_back(1);
    for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>q[i].x>>q[i].y,q[i].id=i,q[i].x++;
    frac[0]=1;
    for(int i=1;i<=2000;i++)frac[i]=frac[i-1]*i%mod;
	sort(q+1,q+m+1,cmp);
	l=1;
	for(int i=1;i<=m;i++){
		while(l>q[i].x)add(--l);
		while(r<q[i].y)add(++r);
		while(l<q[i].x)del(l++);
		while(r>q[i].y)del(r--);
        for(int j=0;j<f.size();j++){
            ans[q[i].id]+=(f[j]*frac[n-j]%mod)*(((bool)(j&1))*2-1)*-1;
            ans[q[i].id]=(ans[q[i].id]+mod)%mod;
        }
	}
    for(int i=1;i<=m;i++)cout<<ans[i]<<"\n";
}
```

---

## 作者：Shiina_Mahiru (赞：4)

本题同步收录在 [Atcoder 题目补全计划](https://www.luogu.com.cn/training/256520) 中，欢迎支持。

这个题给我们写玉玉了，ATcoder 的题对取模是否有什么特别的追求，最后手写了一个 `modint` 类才通过。

### 题目分析：

排列方案，剔除一部分，大概可以想到容斥吧。

我们设区间 $[L,R)$ 中 $i$ 出现的次数为 $cnt_i$，则有

$$\sum_{S \in [N]} (-1)^{\lvert S \rvert}(N - \lvert S \rvert)!\prod \limits_{i \in S} cnt_i$$

$S$ 为不合法整数集合，$[N]= \{0,1,\cdots,n-1 \}$。

前面两个东西都挺好搞的，$\prod \limits_{i \in S} cnt_i$ 有点难，它属于一堆数的组合。

组合？那再生成函数一下吧，它的生成函数表示出来就是

$$f(x)=(1+cnt_0x)(1+cnt_1x) \cdots(1+cnt_{n-1}x) = \prod \limits_{i=0}^{n-1}(1+cnt_i)$$

设 $\prod \limits_{i \in S} cnt_i$ 中集合 $S$ 的元素个数为 $k$，则 $\prod \limits_{i \in S} cnt_i$ 就是 $f(x)$ 的 $k$ 次项系数。

已经很努力了，但这样单次硬算是 $n^2$，如果你 $O(n^3)$ 碾过去了那我不好说。

进一步的，如果只是 $cnt_i$ 加 $1$ 的话，就相当于乘上 $\frac{1+(cnt_i+1)x}{1+cnt_ix}$；反之，减 $1$ 就是乘上 $\frac{1+(cnt_i-1)x}{1+cnt_ix}$。这样操作是 $O(n)$ 的。

什么东西，某个层面上可以快速维护加一减一？莫队。

所以我们每次指针移动改变 $cnt_i$ 的时候就顺便 $O(n)$ 的维护一下多项式 $f(x)$ 就可以了。

时间复杂度：$O(n^2 \sqrt n)$。

### Code.

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0;char c=getchar(); bool f=0;
	for(;c<'0'||c>'9';c=getchar()) f|=(c=='-');
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	return x=f ? -x : x;
}
const int N=2010,p=998244353;
struct modint
{
	int x;
	modint(int o=0) {x=o;}
	modint &operator = (int o){return x=o,*this;}
	modint &operator +=(modint o){return x=x+o.x>=p?x+o.x-p:x+o.x,*this;}
	modint &operator -=(modint o){return x=x-o.x<0?x-o.x+p:x-o.x,*this;}
	modint &operator *=(modint o){return x=1ll*x*o.x%p,*this;}
	friend modint operator +(modint a,modint b) {return a+=b;}
	friend modint operator -(modint a,modint b) {return a-=b;}
	friend modint operator *(modint a,modint b) {return a*=b;}
	modint operator - () {return x?p-x:0;}
} ans[N],fin[N];
int a[N],n,m,len,cnt[N]; vector<modint> f;
int get(int x) {return x/len;}
struct node
{
	int l,r,id;
	bool operator < (const node &o) const {
		if(get(l) == get(o.l)) return get(l)&1 ? r < o.r : r > o.r;
		return get(l) < get(o.l);
	}
} q[N];
void mul(int x)
{
	if(! x) return ; f.emplace_back(0);
	for(int i=(int)f.size()-1;i;i--) f[i]+=f[i-1]*x;
}
void div(int x)
{
	if(! x) return ;
	for(int i=1;i<(int)f.size();i++) f[i]-=f[i-1]*x;
	f.pop_back();
}
void del(int x) {div(cnt[a[x]]); cnt[a[x]]--; mul(cnt[a[x]]);}
void add(int x) {div(cnt[a[x]]); cnt[a[x]]++; mul(cnt[a[x]]);}
int main()
{
	fin[0]=1; for(int i=1;i<=2000;i++) fin[i]=fin[i-1]*i; f.emplace_back(1);
	n=read(); m=read(); len=(int)sqrt(n)+1; for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++) q[i].l=read()+1,q[i].r=read(),q[i].id=i;
	stable_sort(q+1,q+1+m); int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		int l1=q[i].l,r1=q[i].r,id=q[i].id;
		while(l > l1) add(--l);
		while(r < r1) add(++r);
		while(l < l1) del(l++);
		while(r > r1) del(r--);
		for(int k=0;k<(int)f.size();k++) {k&1 ? ans[id]-=(f[k]*fin[n-k]) : ans[id]+=(f[k]*fin[n-k]);}
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i].x);
	return 0;
}
```

---

## 作者：Hkueen (赞：3)

提供一种简单好写的做法。

---

我们先假定 $A$ 是一个排列，考虑此时怎么做。

可以想到容斥，设 $f_i$ 表示至少违反 $i$ 条限制的方案数，则答案为 $\sum\limits_{i=0}^{r-l}(-1)^if_i$，现在的问题就转化为怎么求 $f_i$。

$f_i$ 非常好求，一共 $r-l$ 个限制，选 $i$ 个违反，剩下 $n-i$ 个点随便填，所以 $f_i$ 就等于 $\mathrm{C}_{r-l}^i\times (n-i)!$。

这样就做完了，时间复杂度 $\mathrm{O}(nq)$。

---

接下来考虑 $A$ 不是个排列怎么做：

此时某些 $A_i$ 和 $A_j$ 可能会相等，就会出现一种情况：钦定某个点不合法后，另一些点可能就一定合法了。换言之，有一些点是捆绑在一起的，每次只能选其中的一个。

我们把捆绑在一起的看成一个大点，设 $size$ 表示一个大点是由 $size$ 个点捆绑在一起的。

按照刚刚的做法做，发现唯一的区别就在于，我们选到大点时，方案数要额外乘上它的 $size$，因为我能且仅能选这个大点中的一个点违反限制。

于是只需要魔改一下原来的系数 $\mathrm{C}_{r-l}^i$ 即可，考虑用 `dp` 计算。

原来是在 $r-l$ 个数里面选 $i$ 个，且每个数对方案的贡献都是 $1$，则 dp 式可以写为：

```cpp
f[0][0]=1;//设f[i][j]表示前i个点选j个的方案数。
for(int i=1;i<=r-l;++i)for(int j=0;j<=i;++j)f[i][j]=f[i-1][j]+f[i-1][j-1]*1;
```

现在是在 $m$（$m$ 是捆绑完之后剩下的点数）个数里面选 $i$ 个，且每个数对方案的贡献是 $size$，则 dp 式可以写为：

```cpp
f[0][0]=1;//设f[i][j]表示前i个点选j个的方案数。
for(int i=1;i<=m;++i)for(int j=0;j<=i;++j)f[i][j]=f[i-1][j]+f[i-1][j-1]*size[i];
```

最后我们的贡献系数即为 $f_{m,i}$，对应原来的系数 $\mathrm{C}_{r-l}^i$。

分析一下复杂度，每次询问算一遍 $f$，则复杂度为 $\mathrm{O}(n^2q)$，dp 转移附带 $\frac{1}{2}$ 的常数，不能通过。

但是我们注意到，$size_i$ 的相对顺序是不影响答案的。我们把 $size$ 从小到大排序，前面会有若干个 $size=1$ 的小点，我们预处理这部分的 dp 值，每次询问就只需要 dp $size>1$ 的点了。

最坏情况下，所有的点 $size=2$ ，那么最多只有 $\frac{n}{2}$ 个点，复杂度为 $\mathrm{O}(n^2q)$，附带 $\frac{1}{8}$ 的常数，可以通过，最慢的点只跑了 $1.2$ 秒。

参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void re(int &x){
	x=0;
	int c=getchar();
	while(c<48||c>57)c=getchar();
	while(c>47&&c<58)x=(x<<3)+(x<<1)+(c&15),c=getchar();
}
constexpr ll N=2010,mod=998244353;
int n,q,i,l,r,num[N],m,a[N],siz[N],j;
ll ans,f[N][N],g[N][N],jc[N];
int main(){
//	double st=clock();
	re(n),re(q);
	for(jc[0]=i=1;i<=n;++i)jc[i]=jc[i-1]*i%mod;
	for(i=0;i<n;++i)re(a[i]);
	g[0][0]=1;
	for(i=1;i<=n;++i)for(j=0;j<=i;++j)g[i][j]=(g[i-1][j]+(j?g[i-1][j-1]:0))%mod;
	while(q--){
		re(l),re(r);
		for(i=0;i<n;++i)num[i]=0;
		m=ans=0;
		for(i=l;i<r;++i)++num[a[i]];
		for(i=0;i<n;++i)if(num[i]==1)siz[++m]=1;
		int st=m+1;
		for(i=0;i<n;++i)if(num[i]>1)siz[++m]=num[i];
		for(j=0;j<st;++j)f[st-1][j]=g[st-1][j];
		for(i=st;i<=m;++i)for(j=0;j<=i;++j)f[i][j]=(f[i-1][j]+(j?f[i-1][j-1]*siz[i]:0))%mod;
		ans=jc[n];
		for(i=1;i<=m;++i)ans=(ans+(i&1?mod-1:1)*f[m][i]%mod*jc[n-i]%mod)%mod;
		printf("%lld\n",ans);
	}
//	printf("%.0lfms",clock()-st);
	return 0;
}

---

## 作者：Zhao_daodao (赞：2)

# Count Permutations Many Times

## solution

给一个根号做法的正解。

你会发现题目所求非常容斥，答案就是所有排列数量减去任意位置相同的排列数量。

所以可以设函数 $f_i$ 表示 **钦定** $i$ 个位置相同的排列数量。

最终答案容斥一下，就是 $\sum\limits_{i=0}^{len}(-1)^{i}f_i$。

发现函数中只认定了 $i$ 个位置，其他位置可以随便放，方案数量是一定的。

所以 $f_i$ 可以拆成 $g_i\times (n-i)!$。其中 $g_i$ 表示在范围内钦定 $i$ 个数相同，能够形成排列的方案数。

发现一种钦定方式合法当且仅当：

- 每一个数互不相同。
- 任意一数 $x$，满足 $0\le x \le N-1$。

第二个条件题目中已经帮你满足了，所以只用考虑第一个条件。

发现直接做非常不好，同时值域只有 $[0,N)$，所以在值域上考虑。

设 $i$ 在 $[l,r]$ 中出现 $cnt_i$ 次。枚举一下：

$$g_1=\sum\limits_{i=0}^{n-1}cnt_i$$

$$g_2=\sum\limits_{i=0}^{n-1}\sum\limits_{j=i+1}^{n-1}cnt_icnt_j$$

以此类推。

如果加入一个 $cnt_i$，相当于每一个 $g_j$ 又有了一个 $g_{j-1}\times cnt_i$ 的贡献。

只需要每次枚举 $[l,r]$，最后就能够通过容斥知道答案。

于是你知道了一个 $O(n^2q)$ 的做法。

发现这个东西类似一个背包，众所周知，背包是可以撤回的。

加入就是先把贡献去除，把 $cnt_{a_i}$ 加 1，在把贡献加上。删除类似。

所以这个东西 支持 **加入，删除，查找答案**。复杂度都是 $O(n)$ 的。

现在可以莫队直接做。复杂度大概是 $O(nq\sqrt{n})$。但是这个东西跑不满，时间限制还是 $6s$，所以随便冲。

实测跑了 2s 出头，还是比较稳的。

~~明明有强的数据，为什么要把暴力放过去啊！~~

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e3+5;
const int mod=998244353;
namespace Read{...}
using namespace Read;
int n,q;int a[MAXN];
int fac[MAXN];
int bl[MAXN],B;
struct Query{
    int l,r,id;
    inline friend bool operator <(Query a,Query b){
        if(bl[a.l]^bl[b.l])return bl[a.l]<bl[b.l];
        if(bl[a.l]^1)return a.r<b.r;
        return a.r>b.r;
    }
}Q[MAXN];
int ans[MAXN];ll g[MAXN];
int col[MAXN];
inline void upd1(const int id){for(int i=1;i<=n;i++)(g[i]-=1ll*g[i-1]*col[id]%mod-mod)%=mod;}
inline void upd2(const int id){for(int i=n;i>=1;i--)(g[i]+=1ll*g[i-1]*col[id]%mod)%=mod;}
inline void add(const int id){upd1(id);col[id]++;upd2(id);}
inline void del(const int id){upd1(id);col[id]--;upd2(id);}
inline int chkans(){
    ll ans=0;ll now=1;
        for(int i=0;i<=n;i++){
            (ans+=1ll*now*fac[n-i]%mod*g[i]%mod)%=mod;
            now=mod-now;
        }
    return ans;
}
signed main(){
    read(n,q);B=max(1,(int)sqrt(n));
    for(int i=1;i<=n;i++)read(a[i]),a[i]++;
    for(int i=1;i<=n;i++)bl[i]=(i-1)/B+1;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=(1ll*fac[i-1]*i)%mod;
    for(int i=1;i<=q;i++){
        read(Q[i].l,Q[i].r);
        Q[i].l++;Q[i].id=i;
    }
    sort(Q+1,Q+q+1);
    int l=1,r=0;g[0]=1;
    for(int i=1;i<=q;i++){
        while(r<Q[i].r)add(a[++r]);
        while(l>Q[i].l)add(a[--l]);
        while(r>Q[i].r)del(a[r--]);
        while(l<Q[i].l)del(a[l++]);
        ans[Q[i].id]=chkans();
    }
    for(int i=1;i<=q;i++)write(ans[i],'\n');
}
```

---

## 作者：Officer_Xia_ZhuRen (赞：0)

容斥题，考虑容斥。

由于个人习惯，规定序列从 $\bold{1}$ 开始，且询问区间为 $\bold{[l,r]}$ 。

对于一个简单的情况，假设每种限制都只出现一次，则式子为：

$\bold{\sum_{s = 1}^{r-l+1}(-1)^{s}{r-l+1 \choose s}(n-s)!}$

考虑出现重复的情况，参考组合数的 DP 形式，我们写出转移式 $C_{x,y}=C_{x-1,y}+C_{x-1,y-1}\times cnt_{x}$。

套用原式即可，发现为超出限制数的地方一定是 $0$。

考虑优化现在 $\mathcal{O}(qn^{2})$ 的算法。

由定义容易发现这个式子的第一维可以省略，且省略之后，与 DP 顺序无关。

所以每次更改 $cnt_{x}$ 直接假设在最后一次 DP 转移的时候倒推回去，再把新的加上就行，代码长这样：


```cpp
void update(int x,int ad){
	c[0]=1;
	for(int i=1;i<=n;i++)
	c[i]=(c[i]-((c[i-1]*cnt[x])%mod)+mod)%mod;
	cnt[x]+=ad;
	for(int i=n;i;i--)
	c[i]=(c[i]+c[i-1]*cnt[x]%mod)%mod;
}
```

[Code](https://atcoder.jp/contests/jsc2019-final/submissions/61592083)。

---

## 作者：happybob (赞：0)

题意：

给定一个长度为 $n$ 序列 $a_0,a_1,\cdots,a_{n-1}$。然后给定 $q$ 次询问，每次给定 $l,r$，求有多少 $0$ 到 $n - 1$ 的排列 $p_0,p_1,\cdots,p_{n-1}$，使得 $\forall i \in [l,r),p_i \neq a_i$，答案对 $998244353$ 取模。

$1 \leq n, q \leq 2000$，时限 $6$ 秒。

解法：

假设询问区间为 $[l,r]$。

考虑只有一次询问怎么做，直接进行容斥，令 $b_i$ 表示在区间中选 $i$ 个不同的数的方案数，则答案为 $\sum \limits_{i=0}^{r-l+1} (n-i)! \times b_i \times (-1)^i$。问题仅在于如何计算 $b_i$。

记 $c_i$ 表示 $i$ 在区间 $[l,r]$ 中出现次数，直接从前往后 DP 可以做到 $O(n^2)$，总复杂度 $O(n^3)$，无法通过。

考虑序列 $b$ 的 OGF，则显然可以得到 $b_i = [x^i] \prod \limits_{j=0}^{n-1} (1+c_j x)$。直接回滚莫队暴力卷积可以做到 $O(n^2 \sqrt n)$，或者分治 NTT 可以做到 $O(n^2 \log^2 n)$。

[Submission Link.](https://atcoder.jp/contests/jsc2019-final/submissions/60626052)

---

## 作者：Priestess_SLG (赞：0)

赛时 20min 速切，于是（赛后）来补一个题解。

------

题意：

一个长度为 $n$ 下标从 $0$ 开始的序列 $a$，$Q$ 次询问，每次询问区间 $[l,r)$ 问有多少个 $0\sim n-1$ 的排列 $p$，满足 $\forall j\in[l,r)\cap\mathbb{N_+},a_j\neq p_j$。

数据范围：$1\le n,Q\le 2000$。

题解：

直接计数看上去很困难，于是考虑容斥计算答案。对于每一个要计数的区间 $[l,r)$，都对每一个集合分别计算答案并乘上容斥系数，则可以得到下面的式子：

$$
\sum\limits_{\text{p是}0\sim n-1{的排列的子集}}
(-1)^{|p|}(n-|p|)!\red{\prod\limits_{i\in p}b_i}
$$

其中 $b_i$ 表示 $[l,r)$ 区间内，$i$ 元素出现的次数。此时直接计算答案可以做到 $O(2^nn)$，通过 $n\le 18$ 的部分。

但是这显然是不够的。考虑后面红色的 $\prod\limits_{i\in p}b_i$，把这个部分用生成函数展开，得到 

$$
F(x)=\prod\limits_{i=0}^{n-1}(1+b_i)
$$

其中上式红色部分等于 $F(x)$ 多项式在 $x^{|p|}$ 项的系数。这里记 $F_{|p|}$ 为这个值，于是原式可以变为：

$$
\sum\limits_{\text{p是}0\sim n-1{的排列的子集}}(-1)^{|p|}(n-|p|)!F_{|p|}
$$

此时上式已经和 $p$ 排列具体的值无关，只和 $|p|$ 有关。因此考虑枚举 $|p|\in[1,n]$ 的值，然后直接推平计算答案并乘以满足该情况的排列的数量（可以直接计算）。

此时看上去时间复杂度为 $O(nQ)$，但是实际上因为要计算 $F$ 第 $k$ 项的系数，因此总时间复杂度为 $O(n^2Q)$，但是此时卡卡常已经能场上通过了（我是不会告诉你其实是我算错复杂度了的）

但是考虑到每一次询问一个区间，因此考虑上 ds。但是这个信息十分的奇怪，以至于普通的 ds 难以维护。因此考虑相对较灵活的根号或根号 $\log$ ds。

因此这里选用莫队维护，发现左右端点上 $\pm1$ 是十分容易维护的，因此只需要在莫队上暴力更新答案，时间复杂度即为 $O(n^\frac{3}{2}Q+Q\log Q)$，可以通过。

[AC 记录](http://oj.daimayuan.top/submission/3376240)

upd：发现 OJ 不显示代码，于是 [代码](https://www.luogu.com.cn/paste/deckxgb3)。

---

