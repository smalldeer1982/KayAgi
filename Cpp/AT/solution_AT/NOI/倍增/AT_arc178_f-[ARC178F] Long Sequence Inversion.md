# [ARC178F] Long Sequence Inversion

## 题目描述

给定正整数 $N$、$M$、$K$ 以及长度为 $M$ 的非负整数序列 $A = (A_0, A_1, \dots, A_{M-1})$，满足 $2^{N-1} \leq K < 2^N$。

在输入中，$K$ 以二进制表示为 $N$ 位的数字，其他整数以十进制表示。

另外，序列 $A$ 并未直接给出，而是通过以下方式描述：对于每个 $i=0, 1, \ldots, M-1$，提供长度为 $L_i$ 的整数序列 $X_i = (X_{i,0}, X_{i,1}, \dots, X_{i,L_i-1})$，使得 $A_i = \sum_{j=0}^{L_i-1} 2^{X_{i,j}}$。条件是 $0 \leq X_{i,0} < X_{i,1} < \cdots < X_{i,L_i-1} < N$。

我们的目标是计算由以下规律构成的长度为 $MK$ 的序列 $B = (B_0, B_1, \dots, B_{MK-1})$ 的逆序对数，并输出该值对 $998244353$ 取模的结果。

- 对于任意 $0 \leq a < K$ 和任意 $0 \leq b < M$，有：
  - $B_{aM+b}$ 等于 $\operatorname{popcount}(a \operatorname{AND} A_b)$ 除以 $2$ 的余数。

其中，按位与运算符 $\operatorname{AND}$ 是怎样运算的？对整数 $A$ 和 $B$，其按位与运算 $A \operatorname{AND} B$ 在二进制表示下的第 $2^k$ 位（$k \geq 0$）的值，当且仅当 $A$ 和 $B$ 在该位上均为 $1$ 时为 $1$，否则为 $0$。

例如，$3 \operatorname{AND} 5 = 1$（二进制表示为 $011 \operatorname{AND} 101 = 001$）。不论先后顺序，多个整数按位与的结果是稳定的，可表达为 $(((p_1 \operatorname{AND} p_2) \operatorname{AND} \cdots) \operatorname{AND} p_k)$。

同时，$\operatorname{popcount}$ 函数作用于非负整数 $x$，返回其二进制表示中 $1$ 的总个数。具体来说，假设 $x = \sum_{i=0}^\infty b_i 2^i$，则 $\operatorname{popcount}(x) = \sum_{i=0}^\infty b_i$。举例来说，$13$ 在二进制下是 `1101`，因此 $\operatorname{popcount}(13) = 3$。

## 说明/提示

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq M \leq 2 \times 10^5$
- $2^{N-1} \leq K < 2^N$
- $0 \leq L_i \leq N$
- $\sum L_i \leq 2 \times 10^5$
- $0 \leq X_{i,0} < X_{i,1} < \cdots < X_{i,L_i-1} < N$
- 所有输入都是整数
- $K$ 已经用二进制表示
- 除 $K$ 以外其他数以十进制表示

请输出对 $998244353$ 取模的逆序对数量。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2 4
11
1 0
2 0 1
0
1 1```

### 输出

```
9```

## 样例 #2

### 输入

```
3 3
101
2 1 2
2 0 1
1 0```

### 输出

```
23```

## 样例 #3

### 输入

```
16 7
1101010000100110
11 0 1 2 3 7 10 11 12 13 14 15
7 4 6 8 10 11 12 13
6 0 1 6 8 10 12
8 0 3 5 6 10 11 12 13
10 0 1 2 3 4 5 6 8 12 13
9 3 4 5 6 8 9 11 14 15
8 0 4 7 9 10 11 13 14```

### 输出

```
97754354```

## 样例 #4

### 输入

```
92 4
10101100101111111111011101111111101011001011111110011110111111101111111110100111100010111011
23 1 2 5 13 14 20 28 32 34 39 52 56 59 60 62 64 67 69 71 78 84 87 91
20 15 17 22 28 36 40 43 47 52 53 57 67 72 77 78 81 87 89 90 91
23 7 8 9 10 11 13 16 19 22 23 30 33 42 49 51 52 58 64 71 73 76 79 83
22 1 13 19 26 27 28 29 35 39 40 41 46 55 60 62 64 67 74 79 82 89 90```

### 输出

```
291412708```

# 题解

## 作者：隔壁泞2的如心 (赞：5)

古时候的人们谈及逆序对，没有不惊慌失措，对着天空长长地叹气，用自己的头撞击地面，之后几天都不敢再与人谈话的。后来有一个人从北方来，名字叫艾勒·埃恩·Y·酉乙，她说“**逆序对，如果是在 $01$ 序列里的话，就可以根据所有 $0$ 所在下标之和以及 $0$ 的个数计算出来**”，从这之后，人们才开始敢于研究 ARC178F 这样的问题。

后来的人们以这样的思想为基础，开始将每个 $A$ 分开算贡献。这个时候的人们十分擅长矩阵运算，他们分析 $M=1$ 时的序列变换方式，有写了 $6\times6$ 的矩阵刻画转移的，有通过讨论去除矩阵多余元素的，还有写了线段树从而想要方便地找到某段区间的矩阵的积的。他们用这样的方法，齐心协力地想要解决这道题，可是他们不是被分类讨论和矩阵元素的完形填空逼迫到丧失了信心，就是因为 TLE 而逃跑得十分狼狈。这时一个叫伍兹·露娜的人急忙跑来，对大家说：“所谓 $0$ 的个数，其实就是 $0$ 所在的下标的零次方和。难道你们忘记了愤怒的小 N 里面提及过的，在 T.M. 序列里，那个和元素 $k$ 次方和有关的性质了吗？” 人们听到这番话以后，纷纷要求她将代码写出来，但是过了很久她依然没有完成，于是愤怒的人们就拿着矛和戟将她刺死了。

很久以后人们再次开始研究这个问题，他们回到了 $M=1$ 的情况。人们发现，**如果 $\text{popcnt}(A_1)=2$，那么 $B$ 是 $000111000111111000111000$ 这样结构的循环，而这时 $0$ 的下标的和，竟然和 $1$ 的下标的和相等。** 而当 $\text{popcnt}(A_1)$ 更小时，问题本身就很简单；当 $\text{popcnt}(A_1)$ 更大时，$B$ 也不过只是这个结构经过反转、组合之后的结果，只要这个结构是完整的，$0$ 的下标的和就可以通过计算总数的一半来简单地算出来！而剩下的不完整结构，也就相当于是 $\text{popcnt}(A_1)$ 更小时的情况，不也是很简单吗！这时人们才发觉伍兹·露娜的说法是正确的，但是现在才后悔，实在是有些晚了啊。

艾勒·埃恩·Y·酉乙的发现，当然有着十分关键的作用，如果没有这个思想，那么恐怕无论如何也无法做到优于 $O(n^2)$。而人们原先研究的矩阵，应该也不一定不是可行的方法。如果他们愿意稍微深入思考一下矩阵相乘之后的情况，那么我想伍兹·露娜也不至于落得如此悲惨的下场，实在是让人唏嘘啊。我于是记下了这件事，用来作为后人的鉴戒。

---

总结：

1. 设 $s_0,s_1$ 分别为 $B$ 中 $0$ 的个数以及 $0$ 的下标和，则逆序对数 $=s_1-C_{s_0}^2$，问题被转化为计算 $s_0,s_1$，这样可以方便地对于每个 $A_i$ 分开算贡献。

2. 令 $X$ 为 $A_i$ 只保留二进制最低的两位的结果，则 $B$ 中由 $A_i$ 生成的项里的前 $A_i-X$ 项内 $0,1$ 的下标和相等，所以直接计算 $\dfrac{C_{A_i-X}^{2}}{2}$ 即可。后 $X$ 项结构不复杂，讨论即可。

3. 但是代码真的不好写！

以上每一条都卡了我好久，不过最后写完了就一遍对了，尽管 $s_0$ 幽默没取模调了一阵子。文化课对人的毒害，从这里就可以大概看出来了吧。

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#define mod 998244353
#define int long long
#define add(a,b) (a+=(b),a>=mod?a-=mod:0)
#define neg(x) ((x)&1?mod-1:1)
#define Q(a,b) C((a)+(b)-1,(b)-1)
#define inv2 499122177
using namespace std;
inline int qpow(int n1,int n2){
    int n3=n1,n4=1;
    while(n2){
        if(n2&1)n4*=n3,n4%=mod;
        n3*=n3,n3%=mod;n2>>=1;
    }return n4;
}
inline int mut(initializer_list<int> arg){
	int ret=1;
	for(auto i:arg)ret*=i,ret%=mod;
	return ret;
}
int n,m,p2[407693],a[407693],val[407693];
char str[205416];
signed main(){
    p2[0]=1;for(int i=1;i<=401010;i++)p2[i]=p2[i-1]*2%mod;
    scanf("%lld%lld%s",&n,&m,str);
    for(int i=0;i<n-1-i;i++)swap(str[i],str[n-1-i]);
    val[0]=str[0]-'0';for(int i=1;i<=n-1;i++)val[i]=(str[i]-'0')*p2[i],val[i]=(val[i]+val[i-1])%mod;
    int s0=0,s1=0;
    for(int i=0;i<m;i++){
    	int c0=0,c1=0;
    	a[0]=-1;int cnt;scanf("%lld",&cnt);for(int i=1;i<=cnt;i++)scanf("%lld",a+i);
    	if(cnt==0){
    		c0=val[n-1]%mod,c1=mut({val[n-1],val[n-1]-1,inv2});
		}
		else if(cnt==1){
			int flag=0;
			int r1=p2[a[1]];r1=mut({r1,r1-1,inv2});
			int r2=(val[n-1]-val[a[1]]+mod)*inv2%mod;
			c0+=r2%mod;
			c1+=mut({r2*2%mod-1,r2})-mut({p2[a[1]]+r2*2-1,r2,inv2})+mod;
			int h=(val[n-1]-val[a[1]]+mod)%mod;
			if(str[a[1]]=='1'){
				if(!flag)c0+=p2[a[1]],c1+=p2[a[1]]*h%mod+mut({p2[a[1]],p2[a[1]]-1,inv2});
				h+=p2[a[1]];
				flag=!flag;
			}
			if(a[1]>0){
				if(!flag)c0+=val[a[1]-1],c1+=val[a[1]-1]*h%mod+mut({val[a[1]-1],val[a[1]-1]-1,inv2});
			}
			c0%=mod;c1%=mod;
		}
		else{
			int flag=0;
			for(int i=cnt;i>2;i--)if(str[a[i]]=='1')flag=!flag;
			c0+=(val[n-1]-val[a[2]]+mod)*inv2%mod;c1+=mut({(val[n-1]-val[a[2]]+mod)%mod,(val[n-1]-val[a[2]]-1+mod)%mod,inv2,inv2});
			int h=(val[n-1]-val[a[2]]+mod)%mod;
			if(str[a[2]]=='1'){
				int u0=p2[a[2]-1],u1=mut({p2[a[1]]+p2[a[2]]-1,u0,inv2});
				c0+=u0;
				if(flag)c1+=u1+u0*h%mod;
				else c1+=mut({p2[a[2]]-1,p2[a[2]],inv2})-u1+mod+u0*h%mod;
				flag=!flag;h+=p2[a[2]];
			}
			int r1=p2[a[1]];r1=mut({r1,r1-1,inv2});
			int r2=(val[a[2]-1]-val[a[1]]+mod)*inv2%mod;
			c0+=r2%mod;
			if(flag)c1+=mut({p2[a[1]]+r2*2-1,r2,inv2})+mut({r2,h});
			else c1+=mut({r2*2%mod-1,r2})-mut({p2[a[1]]+r2*2-1,r2,inv2})+mod+mut({r2,h});
			h=(val[n-1]-val[a[1]]+mod)%mod;
			if(str[a[1]]=='1'){
				if(!flag)c0+=p2[a[1]],c1+=p2[a[1]]*h%mod+mut({p2[a[1]],p2[a[1]]-1,inv2});
				h+=p2[a[1]];
				flag=!flag;
			}
			if(a[1]>0){
				if(!flag)c0+=val[a[1]-1],c1+=val[a[1]-1]*h%mod+mut({val[a[1]-1],val[a[1]-1]-1,inv2});
			}
			c0%=mod;c1%=mod;
		}
//		printf("*%lld %lld\n",c0,c1);
		c1*=m;c1+=c0*i;c1%=mod;s0+=c0;s1+=c1;s0%=mod;
	}
//	printf("%lld %lld\n",s0,s1);
	printf("%lld",(s1-mut({s0,s0-1,inv2})+mod)%mod);
}
```

写完这题我就换一个有 modint 的计数板子（

---

## 作者：JWRuixi (赞：2)

### 题意

给定整数 $N, M, K$，以及集合序列 $\{A_M\}$，集合中元素均 $\in [0, N - 1]$。

构造序列 $\{B_{MK}\}$，若令 $S_x$ 表示整数 $x$ 二进制形式形成的集合（即 $i \in S_x$ 当且仅当 $x$ 二进制形式第 $i$ 位为 $1$），则 $B_{aM + b} := |S_a \cap A_b| \bmod 2$。

求 $\pi(B)$（即 $B$​ 的逆序对数）。

$N, M, \sum|A_i| \le 2 \times 10^5$。

### 分析

对于一个 01 序列 $\{a_n\}$，设 $P := \sum\limits_{0 \le i < n}[a_i = 0], Q := \sum\limits_{a_i = 0}i$，则 $\pi(a) = Q - \dbinom{P}{2}$。于是问题转化为求序列 $B$ 中 $0$ 的数量和坐标和。

考虑将 $B$ 拆成 $M$ 个子序列 $\{C_M\}$，其中 $C_{i, j} := |A_i \cap S_j| \bmod 2$。若设 $P_i := \sum\limits_{0 \le j < n}[C_{i, j} = 0], Q_i := \sum\limits_{C_{i, j} = 0}j$，则有 $\pi(B) = \sum\limits_{0 \le i < M}iP_i + MQ_i$，所以只需求出 $\{P_M\}, \{Q_M\}$ 即可。

设 $\{Z_{L}\}$ 满足 $0 \le Z_0 < Z_1 < \cdots < Z_{L - 1} < N$ 且 $\sum\limits_{0 \le i < L}2^{Z_i} = K$。则可以将 $[0, K)$ 拆分成 $L$ 个区间 $[0, 2^{Z_{L - 1}}), [2^{Z_{L - 1}}, 2^{Z_{L - 1}} + 2^{Z_{L - 2}}), \cdots, [K - 2^{Z_0}, K)$，对每个区间分别考虑。进一步可以简化成求 $P^\prime_i = \sum\limits_{0 \le j < M}[a_j = 0] - [a_j = 1]$，$Q^\prime_i$ 同理。

以 $[K - 2^{Z_0}, K)$ 为例，分别考虑：

- 对 $P^\prime_i$ 的贡献：
  - 若 $A_i \cap S_{2^{Z_0} - 1} = \empty$：则序列上该区间全部为 $0$ 或全部为 $1$；
  - 否则：贡献为 $0$（奇偶相消）。

- 对 $Q^\prime_i$ 的贡献：
  - 若 $A_i \cap S_{2^{Z_0} - 1} = \empty$：同上；
  - 若 $A_i \cap S_{2^{Z_0} - 1} = \{x\}$：令 $o := |A_i \cap S_{K - 2^{Z_0}}| \bmod 2$，则 $\sum_j([C_{i,j} \not = o] - [C_{i, j} = o]) = 2^{Z_0 - 1} \times 2^x$；
  - 否则：贡献为 $0$。

不难发现对于其它区间同理。

实际上我们发现绝大部分区间贡献相同，所以可以将他们放在一起考虑，做简单的预处理和分类讨论可以做到 $\mathcal O(|A_i|)$ 计算 $P_i, Q_i$。

总复杂度 $\mathcal O(N + \sum|A_i|)$。

### Code

提交记录：<https://atcoder.jp/contests/arc178/submissions/54455657>。

---

## 作者：aimat (赞：0)

一个关键的想法是将统计逆序对数转换为统计 $0$ 的个数和为 $0$ 的下标之和，设个数为 $P$，下标和为 $Q$。可以得到 $\pi(B)=Q-\frac{P(P-1)}2$。

考虑对于每个 $A_i$ 计算贡献，则将 $B$ 按 $\mod K$ 拆为 $M$ 个长为 $K$ 的序列，其中第 $i$ 个序列，设 $P_i,Q_i$ 分别为第 $i$ 个序列 $0$ 的个数和为 $0$ 的下标之和，手推一下可以得到 $Q=\sum_{i=0}^{M-1}{iP_i+MQ_i}$，$P=\sum_{i=0}^{M-1}P_i$。

按 $X_{i,j}=1$ 的 $j$ 将 $A_i$ 分成一些段，按段考虑。为了方便，我们设 $a_j=X_{i,j}$。发现个数不好统计，我们可以统计 $0$ 的个数与 $1$ 的个数的差，下标和同理。

令 $R_x=\lfloor\frac K{2^x}\rfloor\times2^x$，能观察到一个惊人的结论：区间 $[0,R_{a_1+1}]$ 没有贡献。证明的话可以参照 Thue Morse 序列感性理解。

然后 $A_i$ 整体就可以分成五部分：$[0,R_{a_1+1}),[R_{a_1+1},R_{a_1}),[R_{a_1},R_{a_0+1}),[R_{a_0+1},R_{a_0}),[R_{a_0},K)$。

- $[R_{a_1+1},R_{a_1})$：对下标和有 $\pm2^{a_0}\times $ 的贡献当且仅当 $K \operatorname{AND} 2^{a_1}=2^{a_1}$。

- $[R_{a_1},R_{a_0+1})$：

  - 当 $L_i=1$ 时对下标和有 $\pm2^{a_0}\times R_{a_0+1}$ 的贡献。

  - 当 $L_i>1$ 时对下标和有 $\pm2^{a_0}\times (R_{a_0+1}-R_{a_1})$ 的贡献。
 
- $[R_{a_0+1},R_{a_0})$：对个数有 $\pm(R_{a_0}-R_{a_0+1})$ 的贡献且对下标和有 $\pm\frac{(R_{a_0}+R_{a_0+1}-1)\times(R_{a_0}-R_{a_0+1})}2$ 的贡献当且仅当 $K \operatorname{AND} 2^{a_0}=2^{a_0}$。

- $[R_{a_0},K)$：对个数有 $\pm(K-R_{a_0})$ 的贡献且对下标和有 $\pm\frac{(K+R_{a_0}-1)\times(K-R_{a_0})}2$ 的贡献。

以上正负取决于贡献时 $\operatorname{popcount}$ 的奇偶性。

注意特判 $L_i<2$。

视 $N,M,\sum{L_i}$ 同阶，复杂度为 $O(N)$。

代码仅供参考，马蜂较差，不喜勿喷（（
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int p=998244353;
char *p1,*p2,buf[100010];
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
int read(){
	int x=0;
	char c=gc();
    while(c<48)c=gc();
	while(47<c)x=(x<<3)+(x<<1)+(c&15),c=gc();
	return x;
}
int n=read(),m=read(),len,a[200010],w[200010],pw[200010];
unsigned char K[200010];
int MOD(const int&x){
	return x<p?x:x-p;
}
pair<int,int>solve(){
	if(!len)return make_pair(w[0],(w[0]*(w[0]-1ll)>>1)%p);
	//1:
	int P=0,Q=0,o=1;
	if(len>1){
		for(int i=1;i<len;++i)if(K[a[i]])o=p-o;
		//2:
		if(K[a[1]])Q=(ll)o*pw[a[0]]%p*pw[a[1]-1]%p;
	}
	//3:
	Q=(Q+499122176ll*o%p*pw[a[0]]%p*(w[a[0]+1]-w[len>1?a[1]:200000]))%p;
	//4:
	if(K[a[0]]){
		P=MOD((P+(ll)o*(w[a[0]]-w[a[0]+1]))%p+p);
		Q=MOD((Q+((w[a[0]]+w[a[0]+1]-1ll)*(w[a[0]]-w[a[0]+1])>>1)%p*o)%p+p);
		o=p-o;
	}
	//5:
	P=(P+(ll)o*MOD(w[0]-w[a[0]]+p))%p;
	Q=MOD((Q+((w[a[0]]+w[0]-1ll)*(w[0]-w[a[0]])>>1)%p*o)%p+p);
	P=(P+w[0])*499122177ll%p;
	Q=(Q+(w[0]*(w[0]-1ll)>>1))%p*499122177%p;
	return make_pair(P,Q);
}
int main(){
	int sump=0,sumq=0;
	pair<int,int>tmp;
	for(int i=0;i<n;++i)K[n-i-1]=gc()&1;
	for(int i=pw[0]=1;i<n;++i){
		pw[i]=MOD(pw[i-1]<<1);
	}
	for(int i=n-1;~i;--i){
		w[i]=w[i+1];
		if(K[i])w[i]=MOD(w[i]+pw[i]);
	}
	for(int i=0;i<m;++i){
		len=read();
		for(int i=0;i<len;++i)a[i]=read();
		tmp=solve();
		sump=MOD(sump+tmp.first);
		sumq=(sumq+(ll)i*tmp.first+(ll)m*tmp.second)%p;
	}
	printf("%d",MOD((sumq-(sump*(sump-1ll)>>1))%p+p));
	return 0;
}
```

---

