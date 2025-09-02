# Chiori and Doll Picking (easy version)

## 题目描述

This is the easy version of the problem. The only difference between easy and hard versions is the constraint of $ m $ . You can make hacks only if both versions are solved.

Chiori loves dolls and now she is going to decorate her bedroom!

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336E1/7f2871c87cb2f7ef2408d5e1359121eb7612b9c0.png)As a doll collector, Chiori has got $ n $ dolls. The $ i $ -th doll has a non-negative integer value $ a_i $ ( $ a_i < 2^m $ , $ m $ is given). Chiori wants to pick some (maybe zero) dolls for the decoration, so there are $ 2^n $ different picking ways.

Let $ x $ be the bitwise-xor-sum of values of dolls Chiori picks (in case Chiori picks no dolls $ x = 0 $ ). The value of this picking way is equal to the number of $ 1 $ -bits in the binary representation of $ x $ . More formally, it is also equal to the number of indices $ 0 \leq i < m $ , such that $ \left\lfloor \frac{x}{2^i} \right\rfloor $ is odd.

Tell her the number of picking ways with value $ i $ for each integer $ i $ from $ 0 $ to $ m $ . Due to the answers can be very huge, print them by modulo $ 998\,244\,353 $ .

## 样例 #1

### 输入

```
4 4
3 5 8 14```

### 输出

```
2 2 6 6 0```

## 样例 #2

### 输入

```
6 7
11 45 14 9 19 81```

### 输出

```
1 2 11 20 15 10 5 0```

# 题解

## 作者：Froggy (赞：12)

据EA说这题是状压？

晚上刚CF想到了正解，但是没写完呜呜呜，第二天早上20min就AC了。

**当 场 去 世**

---

这里提供一个比较“暴力”的做法：**线性基+折半搜索+FWT**

首先构造出 $a_i$ 的线性基 $\mathfrak{B}$，关于线性基有个很好的结论，有兴趣可以看看这道题：[P4869 albus就是要第一个出场](https://www.luogu.com.cn/problem/P4869)

> 线性基中组合成的 $2^{|\mathfrak{B}|}$ 种异或和出现的次数一样且每个数出现的次数都为 $2^{n-|\mathfrak{B}|}$

具体证明可以去看那道题目的题解。

现在我们把数据规模从 $2^n$ 缩小到 $2^m$ 了，最终的答案就是只考虑线性基中的数的答案再乘上 $2^{n-|\mathfrak{B}|}$。

看一看这个 $m$，有木有什么想法？对了，**折半搜索！**

令 $mid=\left\lfloor\frac{m+1}{2}\right\rfloor$

我们把线性基劈成两半分成“高位" $(mid+1\sim m)$ 和“低位” $(1\sim mid)$ 分别暴力枚举。

低位好办，直接统计即可。高位由于还有超出 $2^{mid}$ 的部分所以还要记录一下 $\mathrm{popcount}$。

这一部分复杂度是 $\mathcal{O}(2^{mid})$ 

下面就是合并了。

由于 $\mathrm{popcount}$ 只有 $1\sim m-mid+1$ 所以把这 $m-mid+1$ 种分别合并即可。

令高位构成的序列是 $f$ ，低位构成的序列是 $g$ ，线性基整体构成的序列是 $h$ 。（显然长度都为 $2^{mid}$ ）


那么显然：$h$ 是 $f$ 个 $g$ 的 $\operatorname{xor}$ 卷积。

即：

$$h_i=\sum\limits_{j\operatorname{xor}k=i}f_j\times g_k$$

这个直接用 $\mathrm{FWT}$ 计算即可。

每个 $h_i$ 会对 $\mathrm{popcount}(i)+c$ 的答案产生贡献。（$c$ 是枚举的高位的超出 $2^{mid}$ 的部分 $\mathrm{popcount}$ ）

这部分复杂度是 $\mathcal{O}(2^{mid}\times m^2)$ 

复杂度解释：$2^{mid}\times m$ 是 $\mathrm{FWT}$ 的复杂度，剩下的一个 $m$ 是枚举高位的超出 $2^{mid}$ 的部分 $\mathrm{popcount}$。

算一下也就 $10^8$ 左右，时限开了 $3s$ ，可以轻松通过。

*code：*

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define N 400020
typedef long long ll;
const ll mod=998244353;
int n,m,cnt,mid;
ll a[N],d[N],f[28][N],g[N],pcnt[N<<1],ans[N],tmp[N]; 
void Insert(ll x){             //加到线性基里
	for(int i=m-1;i>=0;--i){
		if((x>>i)&1){
			if(!d[i]){
				d[i]=x,++cnt;
				return;
			}
			else{
				x^=d[i];
			}
		}
	}
}
void dfs1(int u,ll num){
	if(u==mid-1){
		f[pcnt[num>>mid]][num&((1<<mid)-1)]++;
		
		return;
	}
	dfs1(u-1,num);
	if(d[u]){
		dfs1(u-1,num^d[u]);
	}
}
void dfs2(int u,ll num){
	if(u==mid){
		g[num]++;
		return;
	}
	dfs2(u+1,num);
	if(d[u]){
		dfs2(u+1,num^d[u]);
	}
}
ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void XOR(ll *f,ll x,int n){  //FWT_XOR
	for(int p=2;p<=n;p<<=1){
		int len=(p>>1);
		for(int k=0;k<n;k+=p){
			for(int i=k;i<k+len;++i){
				ll t1=f[i]+f[i+len],t2=f[i]-f[i+len];
				f[i]=t1*x%mod,f[i+len]=t2*x%mod;
			}
		}
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
		Insert(a[i]);
	}
	mid=(m+1)>>1;
	for(int i=1;i<=300000;++i){
		pcnt[i]=pcnt[i>>1]+(i&1);
	}
	dfs1(m-1,0);  //高低位分别折半搜索
	dfs2(0,0);
	memcpy(tmp,g,sizeof(g));
	for(int i=0;i<=m-mid;++i){    //枚举高位超出2^mid部分的popcount
		memcpy(g,tmp,sizeof(g));
		XOR(f[i],1,1<<mid);
		XOR(g,1,1<<mid);
		for(int j=0;j<(1<<mid);++j){
			f[i][j]=f[i][j]*g[j]%mod;
		}
		XOR(f[i],qpow(2LL,mod-2),1<<mid);
		for(int j=0;j<(1<<mid);++j){
			ans[i+pcnt[j]]=(ans[i+pcnt[j]]+f[i][j])%mod;
		}
	}
	for(int i=0;i<=m;++i){
		printf("%lld ",ans[i]*qpow(2LL,n-cnt)%mod);  //cnt是线性基的大小，别忘了最后乘 2^{n-cnt}
	}
	return 0;
}

```

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/)

#### 呱!!




---

## 作者：SDNetFriend (赞：5)

## CF1336E1 题解

#### 题意这里不再赘述啦

[CF1336E1 Chiori and Doll Picking (easy version)](https://www.luogu.com.cn/record/58983495)

#### 整体思路

异或这种东西看起来就很像是要用线性基搞，然后我们发现它确实可以用线性基搞。

我们知道线性基互相异或能得到原来这些数互相异或的所有结果，但问题是这里面 $0$ 是不会出现的。每次加元素后没能成功加入说明有元素互相异或能得到它，那它就会成为一个“自由元”。

对于线性基中任何一个能异或出的元素，都有 $2^{fr}$ 种方案能给它异或出来，其中 $fr$ 代表自由元个数。

如何证明？考虑首先用线性基异或出来它，然后在自由元里面任取一些元素异或进去，再用线性基内的元素给这些自由元异或结果异或成 $0$ 那么就还是原来的数。**注意这里线性基异或时直接看成取任意个均可以就可以了**，因为异或奇数个就是异或，偶数个就是不异或，所以不存在问题。

#### DP 思路

然后这个问题可以转化为 DP 问题。注意线性基的优秀性质：**低位的向量在高位是没有取值的**，那假设我们**从高到低一位一位考虑基底**，每次异或低位的基底时高位那些不会发生改变，这就为 DP 提供了方便。

那考虑**什么信息是我们需要的**，假设现在考虑到了第 $i$ 位的基底，那我们只需要知道：大于等于 $i$ 位共有多少个 $1$，低于 $i$ 位是个什么状态。

大于等于 $i$ 位这些在接下来的转移里面都不会发生改变，所以可以用来统计权值。小于 $i$ 位的用于更低位异或的运算。我们发现这两个信息很好维护。

那可以设 $f_{i,j,s}$ 表示考虑到第 $i$ 位的基底，大于等于 $i$ 位的有 $j$ 个 $1$，小于 $i$ 位的状态为 $s$ 时的方案总数，每到一位分成两种情况异或当前基底和不异或当前基底讨论即可。

#### 复杂度分析

朴素地看状态数是 $O(2^mm^2)$ 的，但其实第一维可以滚动掉，但这不影响时间复杂度。

对于时间复杂度，我们发现对于大于 $\frac{m}{2}$ 的位置，状态数被基底数量限制，也就是状态不超过 $O(2^{\frac{m}{2}})$，而对于小于 $\frac{m}{2}$ 的位置，状态数被位数限制，状态也是不超过 $O(2^{\frac{m}{2}})$ 的。

分析下来得到时间复杂度为 $O(2^{\frac{m}{2}}m^2)$，空间复杂度为 $O(2^{\frac{m}{2}}m)$，可以通过。

#### 实现细节

看前面大佬的题解是预处理了所有低位的状态的答案。这里我直接一起算，用 unordered_map 存掉最后一维。同时用 queue 来存下上一位有值的状态来转移即可。

注意可能有些基底值是 $0$，一概而论会导致答案 $\times 2$，这里我比较懒，直接特判然后把答案系数 $fr$ 除 $2$。

#### 贴代码

```cpp
#include <bits/stdc++.h>
#define lint long long
using namespace std;
inline lint read(){
	char c;lint f=1,res=0;
	while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
const lint B=36,md=998244353;
lint b[B+1],fr=1,n,m,ans[B+1]={0},iv2;
lint qpow(lint x,lint y){
	lint r=1;
	while(y){
		if(y&1)r=r*x%md;
		x=x*x%md;y>>=1;
	}return r;
}
void inst(lint x){
	for(int i=B;i>=0;--i){
		if(!((x>>i)&1))continue;
		if(b[i])x^=b[i];
		else{b[i]=x;return;}
	}
	fr=fr*2%md;
}
struct st{lint w,s;};
//w为1的个数 s为状态 
unordered_map<lint,lint> f[2][B];
//f[0/1][i][j]表示在大于等于当前位的位置有i个1 
//小于当前位的位置状态为j的方案总数 
queue<st> q[2];//上一位有值的状态 
int main(){
	n=read();m=read();
	for(int i=1;i<=n;++i)
		inst(read());
	int cu=1,pr=0;iv2=qpow(2,md-2);
	q[cu].push(st{0,0});f[cu][0][0]=1;
	for(int i=m;i>=0;--i){
		if(!b[i])fr=fr*iv2%md;
		//当前位没有就除个2,因为直接算答案会翻倍 
		cu^=1;pr^=1;
		while(!q[pr].empty()){
			//枚举前面被转移的状态
			st u=q[pr].front();q[pr].pop();
			if(!f[pr][u.w][u.s])continue;//防止重复转移 
			st v;lint t;//新状态 
			//不异或当前值
			t=u.s;
			v.w=u.w+((t>>i)&1);//加上第i位贡献 
			v.s=t&((1LL<<i)-1);//去掉第i位 
			f[cu][v.w][v.s]+=f[pr][u.w][u.s];
			f[cu][v.w][v.s]%=md;
			q[cu].push(v);
			//异或当前值 
			t=u.s^b[i];
			v.w=u.w+((t>>i)&1);//加上第i位贡献 
			v.s=t&((1LL<<i)-1);//去掉第i位
			f[cu][v.w][v.s]+=f[pr][u.w][u.s];
			f[cu][v.w][v.s]%=md;
			q[cu].push(v); 
			//转移之后变为0防止重复贡献 
			f[pr][u.w][u.s]=0;
		}
	}
	//当第0位转移结束之后统计答案 
	while(!q[cu].empty()){
		st u=q[cu].front();
		q[cu].pop();
		ans[u.w]=(ans[u.w]+f[cu][u.w][u.s])%md;
		f[cu][u.w][u.s]=0;
	}
	for(int i=0;i<=m;++i)
		printf("%lld ",fr*ans[i]%md);
	return 0;
}
```

---

## 作者：Gordon_Song (赞：1)

首先有一个结论：**原序列的所有 $2^n$ 种序列的异或和组成的可重集中，线性基的 $2^m$ 种异或结果分别出现了恰好 $2^{n-m}$ 次**。所以我们只需求出对于线性基中的元素的答案，乘以 $2^{n-m}$ 就是答案。问题的规模就这样缩到了很小。

由于 $m=35$ 仍然无法直接 dfs，所以考虑双向搜索，然后合并答案。设 $mid = \frac{m}{2}$，前 $mid$ 位组合的结果和后 $mid$ 位的结果分别存起来，再合并。然而，好像直接合并是做不了的……

此时就要使用另一个结论：设线性基中从小到大第 $i$ 位的值为 $x$，设 $x$ 的最高位是 $j$，那么恒有 $j \leq i$。也就是基中前 $mid$ 位 **不会影响** 最终异或出来的结果的后 $mid$ 位。

所以对于后 $mid$ 位，设数组 $f_{i,j}$ 表示后 $mid$ 位选数异或出来的结果中最大的 $mid$ 位中 $1$ 的个数是 $i$ 且最小的 $mid$ 位是 $j$ 的选数的方案数。对于前 $mid$ 位，设数组 $g_{i}$ 表示前 $mid$ 位选数异或出来的结果为 $i$ 的方案数。

由于上面的结论，设 $ans_i$ 表示要求的第 $i$ 个答案，那么有：

$$ans_i =\sum_{j=1}^{mid} \sum_{popc(x \oplus y) + j = i}{f_{j,x} \times g_y}$$。

直接维护是不优的。然而注意到柿子的后半部分有点像 FWT 的形式，所以使用这一黑科技。

具体地，枚举 $i$，通过 FWT 求出：

$$t_j = \sum_{popc(x \oplus y) =j} f_{i,x} g_y$$

然后用 $t$ 更新 $ans$。时间复杂度 $m^2 2^{\frac{m}{2}}$。

---

## 作者：loveJY (赞：1)

是的,这题是状压

## Part0

对于线性基里任意可表示出的值w,都有$2^{\text{自由元}}$种方案来凑出

证明考虑对于线性基内部凑齐他的方案数显然唯一,同时在考虑任意选取外部元素时,因为线性基可以将外部元素消为0,因此任意一种选取方案都合法,即达到了这个上界

于是现在问题就变成了计算这个线性基内部表示出的所有值的权值了

我们就有了一个$O(2^m*m)$的好做法

## Part1

考虑怎么优化这个事情

第一个思路是考虑不需要一起枚举所有数的01选取结果,而是将他们分开枚举,然后想办法合并

做法就是折半搜索,先得到前$2^{mid}$和后$2^{mid}$选取的结果,然后利用FWT合并即可$O(2^{mid}*m^2)$

## Part2

另一个想法就是状压DP,我们注意到线性基有一个很优秀的性质,**低位的向量在高位处是没有取值的**,即对于$j<i$处的向量j在i处的取值一定是0,这样就保证了我们的无后效性

$dp_{i,j,S}$表示前i个向量,然后对于大于等于i的位置我们有j个位数为1,然后剩下低于i位的当前异或和为S的方案数是什么

这个状态有个形象的解释

![tupian](https://cdn.luogu.com.cn/upload/image_hosting/7rdldtyh.png)

于是我们枚举第i+1个向量是否选择,对应的可以确定第i位是0或者1,贡献到j状态里,并且递归到剩余S集合更小的状态即可

但是显然直接dp的复杂度是$O(2^m*m^2)$...

不过你需要思考我们状态数可能达到$2^m$这个上界吗?

显然不可能!因为每个数只会有选择或者不选择这两个选项,因此在mid次决策中,我们本质不同的状态至多$2^{mid}$种

同时在后mid次决策中,因为S集合大小由$m-i$决定,因此也不会超过$2^{mid}$

因此我们只需要枚举有用的状态即可,不过实现起来只需要向暴力前mid个数,然后作为初始化状态给后mid个数dp用即可

复杂度还是$O(2^{mid}m^2)$

```cpp


#include<bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
const int MAXN = 2e5 + 7;
const int P = 998244353;

int B = 35;
int n, m, a[MAXN], b[MAXN], cnt;

inline int ksm(int x, int y) {
	int ans = 1;
	while(y) {
		if(y & 1)ans = ans * x % P;
		x = x * x % P;
		y >>= 1;
	}
	return ans;
}

inline int add(int x, int y) {
	x += y;
	if(x >= P)x -= P;
	return x;
}

inline void ins(int x) {
	for(int i = B; i >= 0; --i) {
		if(x >> i & 1) {
			if(!b[i]) {
				b[i] = x;
				break;
			}
			x ^= b[i];
		}
	}
	return;
}

int f[36][MAXN], g[36][MAXN];

inline void init() {
	int t = m - m / 2;
	int mS = (1 << t) - 1;
	int qS = (1 << ((m / 2))) - 1;
	for(int S = 0; S <= mS; ++S) {
		ll p = 0;
		bool flg = 1;
		for(int j = 0; j < t; ++j)
			if(S >> j & 1) {
				if(!b[j + m / 2]) {
					flg = 0;
					break;
				}
				p ^= b[j + m / 2];
			}
		if(!flg)continue;
		int tmp = 0;
		for(int j = m / 2; j <= B; ++j)
			if(p >> j & 1)
				tmp++;
		f[tmp][p & qS]++;
	}
	return ;
}

inline void solve() {//杀死地精!
	init();
	int t = m / 2 - 1;
	int mS = (1 << (t + 1)) - 1;
	for(int i = t + 1; i >= 1; --i) {
		mS = (1 << i) - 1; //只有这些自由位了
		for(int k = 0; k <= m - i; ++k) {//枚举高位挂掉了几个,别太多了吧?
			for(int S = 0; S <= mS; ++S) {//试看看!
				if(S >> (i - 1) & 1) {
					g[k + 1][S ^ (1 << (i - 1))] = add(g[k + 1][S ^ (1 << (i - 1))], f[k][S]); //直接做!
					if(b[i - 1])
						g[k][S ^ b[i - 1]] = add(g[k][S ^ b[i - 1]], f[k][S]);
				} else {
					g[k][S] = add(g[k][S], f[k][S]); //直接做!
					if(b[i - 1])
						g[k + 1][S ^ b[i - 1] ^ (1 << (i - 1))] =
							add(f[k][S], g[k + 1][S ^ b[i - 1] ^ (1 << (i - 1))]);
				}
			}
		}
		mS = (1 << i) - 1;
		for(int k = 0; k <= m - i + 1; ++k) {
			for(int S = 0; S <= mS; ++S) {
				f[k][S] = g[k][S];
				g[k][S] = 0;
			}
		}
	}
	for(int i = 0; i <= m; ++i) {
		printf("%lld ", 1ll * f[i][0] * cnt % P);
	}
	puts("");
	return;
}

signed main() {
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		ins(a[i]);
	}
	cnt = 0;
	for(int i = 0; i <= m; ++i) {
		if(b[i]) {
			cnt++;
			B = i;
		}
	}
	cnt = n - cnt;
	cnt = ksm(2, cnt);
	solve();
	return 0;
}


```

---

## 作者：tribool4_in (赞：0)

异或考虑线性基。消完后剩 $|B|\le 36$ 个，于是最终答案为这些的答案乘上 $2^{n-|B|}$。

$36$ 明示折半搜索，考虑取分界点 $mid$，分为低位 $[0,mid)$ 和高位 $[mid,m)$。对于线性基的低位，直接做出 $g_i$ 表示异或出 $i$ 的方案数。对于线性基的高位，发现其同时包含高低位不好处理。

考虑我们只关心高位的 $1$ 的个数，令其为 $c$，于是枚举高位的过程中设 $f_{c,i}$ 表示高位线性基异或出来的所有数字中，高位 $1$ 个数为 $c$ 的中低位为 $i$ 的方案数。答案贡献为 $\displaystyle ans_i=\sum_c \sum_{\operatorname{popcnt}(i\oplus j)+c=i}f_{c,i}g_i$。

然后枚举 $c$，发现后半部分就是个异或卷积，FWT 做出 $\displaystyle h_k=\sum_{i\oplus j=k}f_ig_i$，然后 $h_i$ 贡献到 $ans_{\operatorname{popcnt}(k)+c}$。

记得最后乘上 $2^{n-|B|}$。

代码有点混乱，调 corner case 调的。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, mod = 998244353, inv2 = 499122177;
int n, m, l, mid, mb, a[N], bt[40], b[40], ans[40];
void init() {
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        for (int j = m - 1; j >= 0; j--) {
            if (x >> j & 1) {
                if (bt[j]) x ^= bt[j];
                else {
                    bt[j] = x;
                    l += 1;
                    break;
                }
            }
        }
    }
}
void fwt_xor(int H[], int n, int flag = 1) {
    for (int k = 1, m = 0; k < n; k <<= 1, ++m) {
        for (int i = 0; i < n; i += (k << 1)) {
            for (int j = 0; j < k; j++) {
                int u = H[i + j], v = H[i + j + k];
                (H[i + j] = u + v) %= mod;
                (H[i + j + k] = (u - v + mod)) %= mod;
                (H[i + j] *= flag) %= mod;
                (H[i + j + k] *= flag) %= mod;
            }
        }
    }
}
int f[1 << 18], g[1 << 18], h[1 << 18];
void calc() {
    fwt_xor(f, 1ll << mb), fwt_xor(g, 1ll << mb);
    for (int i = 0; i < (1ll << mb); i++) h[i] = f[i] * g[i] % mod;
    fwt_xor(h, 1ll << mb, inv2);
}
int clz(int x) {
    if (x == 0) return 0;
    return __lg(x) + 1;
}
#define chkmod(x) (((x) >= mod) && ((x) -= mod))
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    init();
    for (int i = 0, j = 0; i < m; i++)
        if (bt[i]) b[j++] = bt[i];

    while (mid < l && clz(b[mid]) <= (m >> 1)) ++mid;

    mb = (mid == 0) ? 0 : (__lg(max(1ll, b[mid - 1])) + 1);

    for (int c = 0; c <= m - mb; c++) {
        memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g));
        for (int kl = 0; kl < (1ll << mid); kl++) {
            int v = 0;
            for (int i = 0; i < mid; i++)
                if (kl >> i & 1) v ^= b[i];
            g[v] += 1;
            chkmod(g[v]);
        }
        for (int kh = 0; kh < (1ll << l - mid); kh++) {
            int v = 0;
            for (int i = 0; i < l - mid; i++)
                if (kh >> i & 1) v ^= b[mid + i];
            if (__builtin_popcountll(v >> mb) == c) f[v & ((1ll << mb) - 1)] += 1, chkmod(f[v & ((1ll << mb) - 1)]);
        }
        calc();
        for (int k = 0; k < (1ll << mb); k++) {
            int tgt = __builtin_popcountll(k) + c;
            ans[tgt] += h[k];
            chkmod(ans[tgt]);
        }
    }
    int pw2 = 1;
    for (int i = 0; i < n - l; i++) pw2 *= 2, chkmod(pw2);
    for (int i = 0; i <= m; i++) cout << ans[i] * pw2 % mod << " \n"[i == m];
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

感觉这个 Easy Version 非常唐。

考虑求出原序列的一组线性基。那么线性基上的子集和原序列的子集形成了一一对应。（注意，我们仍考虑经过一系列处理变成了 $0$ 的元素。）

忽略那么多 $0$，我们只需要管有值的元素。而他们一个很重要的特征就是最高位互不相同。

于是考虑按照最高位分成 $18+17$ 的两组，前面一组是最高位比较高的元素。

有点类似于 Meet In the Middle，我们先用朴素的二的次幂的复杂度求出这两组所有的子集。

考虑怎么合并答案。事实上，第二组不可能有超过 $2^{17}$ 的位。于是可以用 $\text{FWT}$ 简单快速合并。（你可能要对第一组再多开一维记录 $2^{17}$ 位及以后有多少 $1$）。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000000+10,MAXM=40,MAXK=(1<<18)+10,MOD=998244353;
int n,m,N,mid,cnt0,mul=1,a[MAXN],bs[MAXK],ans[MAXN],pre[22][MAXK];
void insert(int u) {
	roff(i,m-1,0) if(u&(1ll<<i)) {
		if(bs[i]) u^=bs[i];
		else {bs[i]=u;return ;}
	}
	cnt0++;
	return ;
}
void fwt(int f[MAXK]) {
	for(int len=2;len<=N;len<<=1) {
		int lst=len>>1;
		ffor(id,0,N/len-1) {
			int l=id*len,r=l+len-1;
			ffor(i,l,l+lst-1) {
				int x=f[i],y=f[i+lst];
				f[i]=(x+y)%MOD,f[i+lst]=(x-y)%MOD;
			}
		}
	}
	return ;
}
void ifwt(int f[MAXK]) {
	for(int len=2;len<=N;len<<=1) {
		int lst=len>>1;
		ffor(id,0,N/len-1) {
			int l=id*len,r=l+len-1;
			ffor(i,l,l+lst-1) {
				int x=f[i],y=f[i+lst];
				f[i]=(x+y)%MOD*((MOD+1)/2)%MOD,f[i+lst]=(x-y)%MOD*((MOD+1)/2)%MOD;
			}
		}
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m,mid=m/2,N=(1<<mid+1);
	ffor(i,1,n) cin>>a[i],insert(a[i]);
	ffor(i,1,cnt0) mul=mul*2%MOD;
	vector<int> A,B;
	ffor(i,0,mid) if(bs[i]) B.push_back(bs[i]);
	ffor(i,mid+1,34) if(bs[i]) A.push_back(bs[i]);
	memset(bs,0,sizeof(bs));
	ffor(i,0,(1<<B.size())-1) {
		int x=0;
		ffor(j,0,(int)B.size()-1) if(i&(1<<j)) x=x^B[j];
		bs[x]++;
	}
	ffor(i,0,(1<<A.size())-1) {
		int x=0;
		ffor(j,0,(int)A.size()-1) if(i&(1<<j)) x=x^A[j];
		int LW=x&((1<<mid+1)-1),rst=__builtin_popcountll(x)-__builtin_popcount(LW);
		pre[rst][LW]++;
	}
	fwt(bs); ffor(i,0,19) fwt(pre[i]);
	ffor(i,0,19) {
		ffor(j,0,N-1) pre[i][j]=pre[i][j]*bs[j]%MOD;
		ifwt(pre[i]);	
		ffor(j,0,N-1) ans[__builtin_popcount(j)+i]=(ans[__builtin_popcount(j)+i]+pre[i][j])%MOD;
	}
	ffor(i,0,m) ans[i]=ans[i]*mul%MOD;
	ffor(i,0,m) cout<<(ans[i]%MOD+MOD)%MOD<<' ';	
	return 0;
}
```

---

