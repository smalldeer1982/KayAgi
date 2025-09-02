# 移言丁真：Unavoided linyue

## 题目背景

**注：你不需要阅读此题题目背景。**

"$\textsf{linyue}$" 是我起过的唯一一个人名，所以 $\textsf{linyue}$ 成了唯一一个由我想象出来的角色。她是我脑海中所有故事的主角，对我而言非常地重要，以至于不知道为什么，每次我看到她的名字被写出来或是被读出来都会感到无所适从，所以我总是会想办法避免这样，比如说这个题的题面里我就用的是拼音作代替。

“跑团”这种游戏我最初了解的时候简直是“绝望地想要跟不管是谁玩随便什么”。可是疫情却让我的好多和同学玩的计划纷纷泡汤，所以我甚至走投无路到把它也纳入了计划的考虑范畴，不过由于它实在是太复杂了，没过多久我就把它抛诸脑后了（

“黑影杀”是一款在泞之翼官方交流群里兴起的游戏，玩家将会探索《泞之翼》原作的旅馆，躲避黑影以求逃出生天——对我而言没有比这更完美的事了！它完全实现了我上一段里的愿望，只要一有空，我便可以在群里“开鲨”！我给这个游戏准备了便于主持的程序，写了许多特殊规则，甚至还以它为背景出了题——尽管这题投到的比赛咕了（

《怪商一克拉》是一部我很喜欢的漫画。它的特点就是主角好像在每段故事里都只会最小程度地完成任务，然后哪怕这个故事还有好多未解之谜都只会跳到下一段故事。尽管这看起来像是没写好，但我相信这种效果作者是刻意为之。所以我期待着在未来看到这些故事的伏笔被精妙地解决，带来一个震撼的结局。可是有一天，我没有在漫画派对上看到这部漫画。这意味着以上就都不会发生了……我当时心态崩了好长时间，甚至都到泞之翼群里发癫了，不过事实上作者只是请了一个月假，接下来这漫画还会照常更新（

前两天，我终于又找到机会和同学出去玩了！这一次我们打算上一个主营镜土 TRPG 的店里试试跑团。要知道，这对我而言还是很有吸引力的，因为之前不管是玩什么，都是"我"在玩，跟 $\textsf{linyue}$ 没有什么关系。但要是玩跑团做角色卡的话，是不是就能填补这个遗憾了呢？所以这次我是有备而来！我提前十分费力地给 $\textsf{linyue}$ 画了一张简单的画，然后输入名字的时候，我决定不再回避——用她那两个汉字的真名，而非六个字母的替代。

然而，尽管我这一天听到和看到她名字的次数前所未有，但最后却并没什么很好的效果。我在游戏里确实是主打一个不入戏，对话内容有种全人类取平均的美，没推理出什么剧情的关键，也没想到什么新奇的点子。相信把我换成 Kimi AI 游戏绝对会更有趣……

——不过当然啦，这倒也在我意料之中，因为我知道我本来就非常非常不擅长这种角色扮演……看来对我而言，创造 $\textsf{linyue}$ 的故事会比别人更加困难。

所以我不会太受这个问题的困扰，一是因为习惯了，二是因为——我们出题组的比赛没过审。

![](https://cdn.luogu.com.cn/upload/image_hosting/7qwdep44.png)

“移言丁真”是这场比赛的原定 E 题之一，可是它被鉴定为了典……显然这最主要是我的锅。所以我现在的当务之急是要想一个新的 idea……

## 题目描述

定义一个括号串的权值为其中可配对的括号组数。也就是你重复地在里面删除掉某个为 ```()``` 的子串，最多可以删除的次数。

你会遇到 $m$ 个括号串，第 $i$ 个的长度是 $l_i$。你可以将它们按照任意顺序连接起来，然后连成一个长的括号串，而你的目标就是让最终的串的权值最小。

如果这 $m$ 个串是等概率随机生成的，而你的操作是最优的，请你求出最终权值的期望。也就是说你要对于初始括号串的所有可能性求出最小权值的和再除以 $2^n$，$n$ 为这些字符串的总长。对 $10^9+7$ 取模。

## 说明/提示

**【样例解释1】**

这里 $\{S_1,S_2\}$ 表示两个括号串构成的无序可重集合，$P$ 表示取到这样集合的概率。

| $\{S_1,S_2\}$ | $P$ | 最优方案 | 权值 |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $\{$```((```$,$```((```$\}$ | $\frac{1}{16}$ | ```((((``` | $0$
| $\{$```((```$,$```()```$\}$ | $\frac{1}{8}$ | 任意 | $1$
| $\{$```((```$,$```)(```$\}$ | $\frac{1}{8}$ | ```)(((``` | $0$
| $\{$```((```$,$```))```$\}$ | $\frac{1}{8}$ | ```))((``` | $0$
| $\{$```()```$,$```()```$\}$ | $\frac{1}{16}$ | ```()()``` | $2$
| $\{$```()```$,$```)(```$\}$ | $\frac{1}{8}$ | 任意 | $1$
| $\{$```()```$,$```))```$\}$ | $\frac{1}{8}$ | 任意 | $1$
| $\{$```)(```$,$```)(```$\}$ | $\frac{1}{16}$ | ```)()(``` | $1$
| $\{$```)(```$,$```))```$\}$ | $\frac{1}{8}$ | ```)))(``` | $0$
| $\{$```))```$,$```))```$\}$ | $\frac{1}{16}$ | ```))))``` | $0$

最终答案为 $\dfrac{9}{16}$。

**【数据范围】**

令 $n$ 为 $l_i$ 的总和。

子任务 $1$（$20$ 分）: $n \le 20$。

子任务 $2$（$30$ 分）: $n \le 5000$。

子任务 $3$（$50$ 分）: $n \le 4000000$。

保证 $l_i \ge 1$。

**【后记】**

左括号和右括号可以是 $\textsf{linyue}$ 名字的第一个字和第二个字，也可以是一段故事的萌芽和结果。

下一次跑团遥遥无期，黑影杀渐渐无人问津，我们团的三个原定 E 题和其他好多好多的 idea 不知道何去何从，那些和 $\textsf{linyue}$ 有关的故事和设想更是也难以被呈现。有时我感觉自己就像是在《怪商一克拉》里一样，好多段经历都没等到自己的右括号，有种被最小化了权值的美。所以，我总是期待这些故事的伏笔被精妙地解决，带来最大的幸福。不过在这之前，我只好继续回避 “$\textsf{linyue}$” 了。

## 样例 #1

### 输入

```
2
2 2```

### 输出

```
62500001```

## 样例 #2

### 输入

```
5
1 2 3 4 5```

### 输出

```
762695321```

# 题解

## 作者：Anoshag_Ruwan (赞：7)

这道题的核心在于括号序列向格路计数的转化以及找 $h_1+h_2$ 的思路，主要想（保姆级）补充一下 [linyue](https://www.luogu.com.cn/user/222901) 官方题解中的数学推导部分。

首先，答案与 $h_1+h_2$ 的关系是 $ans=\frac{n-h_1-h_2}{2}$，这个易得，删去括号串中最左侧的 $h_1$ 个右括号与最右侧的 $h_2$ 个左括号，总能得到一个合法的括号匹配序列。关键在于求所有串 $|h_1-h_2|$ 以及 $\max(\min(h_1,h_2))$ 的期望。

首先有结论，从 $(0,h_1)$ 以格路走到 $(n,h_2)(h_1,h_2\ge 0)$，要求中间不穿过 $x$ 轴的路线数为 $g(n,h_1,h_2)=(\tbinom{n}{\frac{n-h_1+h_2}{2}}-\tbinom{n}{\frac{n+h_1+h_2+2}{2}})[h_1+h_2\equiv n\bmod2]$。这是计数的常见套路，假设另一个人从 $(0,-2-h_1)$ 走到同样的终点，将其从起点到第一次经过 $y=-1$ 的路径轴对称到上方，则每个从 $(0,h_1)$ 到 $(n,h_2)$ 的不合法路径与起点关于 $y=-1$ 轴对称的任意路径便建立了一一对应。若限定 $h_1$ 与 $h_2$ 的值也可直接差分就行。

对于第一部分即求 $E(k,|h_1-h_2|)$（$k$ 为字符串长度），这个不需要上述结论，考虑让路径长度 $+1$ 的过程，末尾可以添加向上或向下一步，若 $h_1\ne h_2$，则答案有均等概率 $+1$ 或 $-1$，仅有 $h_1=h_2$ 时无论如何只会导致答案 $+1$，因此 $E(|h_1-h_2|)$ 的增量就等于 $h_1=h_2$ 的方案数，前缀和得 $E(k,|h_1-h_2|)=\sum\limits_{i=0}^{\lfloor\frac{k+1}{2}\rfloor}\tbinom{2i}{i}\frac{1}{4^i}$，$O(n)$ 递推处理即可。

对于第二部分 $E(\max)$ 就不能相互独立来求了，先一步转化 $E(\max(h))=\sum\limits_{k\ge 1}P(\max(h)\ge k)=\sum\limits_{k\ge 0}(1-P(\forall a_i,\min(h_1,h_2)\le k))$，对于每个 $k$ 就满足 $a_i$ 相互独立了。为避免容斥再启动第一部分的递推，当且仅当 $h_1> k,h_2=k$ 或 $k+1$ 时，末尾添加一步可以产生概率的贡献。因此 $P(n,\min\le k)=1+\frac{1}{2}\sum\limits_{m\le 1}^{n-1}(P(m,h_1>k,h_2=k+1)-P(m,h_1>k,h_2=k))$。

  应用一开始的结论，$P(m,h_1>k,h_2=k)=2^{-m}(\sum\limits_{ k_1>k}g(m,k_1,k)-g(m,k_1-1,k-1))$，$\sum\limits_{k_1>k}g(m,k_1,k)=\sum\limits{\tbinom{n}{\frac{n-k_1+k}{2}}-\tbinom{m}{\frac{m-k_1-k-2}{2}}}=\sum\limits_{i=1}^{2k+1}\tbinom{m}{\frac{m-i}{2}}$，因此 $P(m,h_1>k,h_2=k)=2^{-m}\tbinom{m}{\lfloor\frac{m-2k-1}{2}\rfloor}$，同理 $P(m,h_1>k,h_2=k+1)=2^{-m}\tbinom{m}{\lfloor\frac{m-2k-2}{2}\rfloor}$，而当 $m$ 为偶数时，对概率的贡献严格为 $0$，$P(n,\min\le k)=\sum\limits_{i=0}^{\lfloor\frac{k-1}{2}\rfloor}2^{-1-2i}(\tbinom{2i+1}{i-k}-\tbinom{2i+1}{i-k-1})$，设 $n_0=n+1+(n\bmod 2)$，由杨辉三角结论可得 $P(n,\min\le k)=2^{n_0+1}\sum\limits_{i=0}^k\tbinom{n_0}{\frac{n_0-1}{2}-i}$，十分优美的形式。

然后现在到代码实现环节，你发现数据范围是关于 $\sum{a_i}$ 线性的，开 $a_i$ 个指针在杨辉三角对应行上移动即可，时间复杂度 $O(n+m)$，代码十分简洁。


```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define LL long long
using namespace std;
const int p=1e9+7,N=4e6+11,iv=5e8+4;
LL a[N],b[N],c1[N],c2[N],frc[N],inv[N];
inline LL add(LL x,LL y){return x+y>=p?x+y-p:x+y;}
inline LL cmb(LL x,LL y){return x<y||y<0?0:frc[x]*inv[y]%p*inv[x-y]%p;}
inline LL ksm(LL x,LL y){
	LL k=1,l=x;
	while(y){if(y&1)k=k*l%p;l=l*l%p,y>>=1;}
	return k;}
inline LL rd(){
	LL i=0,j=1;char g=getchar();
	while(g>57||g<48){if(g=='-')j=-1;g=getchar();}
	while(g>47&&g<58)i=(i<<3)+(i<<1)+g-48,g=getchar();
	return i*j;
}
int main()
{
	LL i,j,h,k,m=0,n=rd(),ans=0,as=0;
	for(i=1;i<=n;i++)a[i]=rd(),m=add(m,a[i]);sort(a+1,a+n+1);
	for(i=frc[0]=b[0]=1;i<=m;i++)frc[i]=frc[i-1]*i%p,b[i]=b[i-1]*iv%p;
	for(i=m,inv[m]=ksm(frc[m],p-2);i;i--)inv[i-1]=inv[i]*i%p;
	for(i=2;i<=m+1;i+=2)c1[i]=c1[i-1]=add(c1[i-2],cmb(i-2,i-2>>1)*b[i-2]%p);
	for(i=1;i<=n;i++)ans=add(ans,c1[a[i]]),a[i]>>=1;
	for(i=0,j=1;i<a[n];i++){
		for(k=1,h=j;h<=n;h++)c2[h]=add(c2[h],cmb((a[h]<<1)+1,a[h]-i)*b[a[h]<<1]%p),k=k*c2[h]%p;
		while(a[j]<=i)j++;as=add(as+1,p-k);
	}ans=add(m,p-add(ans,add(as,as)))*iv%p;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：隔壁泞2的如心 (赞：6)

这种题当然要把括号序转化成格路啦！（如果你没见过这个操作，建议换道题做）

将左括号视为向上走，右括号视为向下走，那么容易发现：

![](https://cdn.luogu.com.cn/upload/image_hosting/pgdb4op3.png)

最终括号串的权值只和它的 $h_1+h_2$ 有关，我们相当于要最大化最后长串的 $h_1+h_2$。如果我们已知了所有括号串的 $h_1$ 和 $h_2$，那么假如已知某个串作为了最低点所在的串，其他串里 $h_1 \le h_2$ 的都应该放到这个串右边，否则就放到这个串左边，它们对答案的贡献都是 $|h_1-h_2|$，而那个作为最低点的串对答案的贡献是 $h_1+h_2＝|h_1-h_2|+2\min(h_1,h_2)$。因此，如果选 $\min(h_1,h_2)$ 最大的串作为最低点所在的串，不仅可以最大化答案，并且还一定可以成功让其处于最低点！

所以说，我们想求出长串 $h_1+h_2$ 的最大值的期望，只需先求出每个串 $|h_1-h_2|$ 的期望，再对于每个自然数 $k$ 求出最后各串 $\min(h_1,h_2)$ 的最大值为 $k$ 的概率即可。可以改为求最大值不大于 $k$ 的概率，然后作差分。这样的话只要对于每个串求出它的 $\min(h_1,h_2)$ 不大于 $k$ 的概率再乘起来，而这个又可以被写成 $1-P(h_1,h_2＞k)$。

现在我们只要对于每个串快速求出它的 $h_1,h_2$ 均大于 $k$ 的概率。考虑枚举第一个最低点，那么向两边走时需要满足的限制为“不能比起点低，终点要比某坐标高”，而这样的方案数其实和“没有特殊限制，终点坐标为一定值”一样，这样问题就被转化为了“固定起点终点，求路径与某直线相交次数和”，你可以用喜欢的方法推出答案为组合数前缀和，然后递推就可以实现 $O(n)$，这题做完啦！

```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cassert>
#define mod 1000000007
#define inv2 500000004
#define int long long
#define add(a,b) (a+=(b),a>=mod?a-=mod:0)
#define neg(x) ((x)&1?mod-1:1)
#define Q(a,b) C((a)+(b)-1,(b)-1)
using namespace std;
int fac[4007693],ifac[4007693];
int C(int n1,int m1){
    if(m1<0||m1>n1)return 0;
    return fac[n1]*ifac[m1]%mod*ifac[n1-m1]%mod;
}
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
int m,n,l[4076930],cnt,ans,ca[4076930],ck[4076930],r[4076930];     
signed main(){
    fac[0]=1;for(int i=1;i<=4001010;i++)fac[i]=fac[i-1]*i%mod;
    ifac[4001010]=qpow(fac[4001010],mod-2);for(int i=4001010;i>=1;i--)ifac[i-1]=ifac[i]*i%mod;
    scanf("%lld",&m);
    for(int i=1;i<=m;i++)scanf("%lld",l+i),n+=l[i],r[l[i]]++;
    for(int i=0;i<=n;i++)ca[i]=1;
    for(int i=1;i<=n;i++){
    	if(r[i]==0)continue;
    	ck[0]=1;for(int j=1;j+j<=i;j++)ck[j]=(ck[j-1]+C(i,j))%mod;
//        for(int j=0;j+j<=i;j++)printf("%lld ",ck[j]);printf("\n");
    	int p2=qpow(2,i),ip2=qpow(p2,mod-2);
    	for(int j=0;j+j<=i;j++){
    		if(i&1)ca[j]=ca[j]*qpow((p2-2*(i/2-1>=j?ck[i/2-j-1]:0)+2*mod)%mod*ip2%mod,r[i])%mod;
    		else ca[j]=ca[j]*qpow((p2-(i/2-1>=j?ck[i/2-j-1]:0)-(i/2-2>=j?ck[i/2-j-2]:0)+2*mod)%mod*ip2%mod,r[i])%mod;
		}
	}
//   for(int i=0;i<=n;i++)printf("%lld ",ca[i]*qpow(2,n)%mod);printf("\n");
	for(int i=n;i>=1;i--)add(ca[i],mod-ca[i-1]);
//	for(int i=0;i<=n;i++)printf("%lld ",ca[i]*qpow(2,n)%mod);printf("\n");
	for(int i=1;i<=n;i++)ans=(ans+ca[i]*i*2)%mod;
//    printf("%lld\n",ans*qpow(2,n)%mod);
	for(int i=1;i<=n;i++){
    	if(r[i]==0)continue;
    	int cur=0;for(int j=0;j<=i;j++)cur+=max(i-j*2,j*2-i)*C(i,j)%mod;
    	ans=(ans+mut({r[i],cur%mod,qpow(inv2,i)}))%mod;
	}
//	printf("%lld\n",ans*qpow(2,n)%mod);
    ans=(n-ans+mod)*inv2%mod;
//    printf("%lld\n",ans*qpow(2,n)%mod);
	printf("%lld",ans);
}
```
---

["相关链接"](https://www.luogu.com.cn/article/qecqadkz)

---

## 作者：DaiRuiChen007 (赞：5)

[Problem Link](https://www.luogu.com.cn/problem/P10896)

**题目大意**

> 定义一个括号串 $S$ 的权值为其最大括号匹配的大小。
>
> 对于 $m$ 个括号串 $S_1\sim S_m$，定义其权值为：任意重排 $S_1\sim S_m$ 后连接成完整括号串 $S$，$S$ 最小的权值。
>
> 已知 $S_1\sim S_m$ 的长度，在 $S_i$ 的每个字符都均匀随机生成的情况下，求每组 $S_1\sim S_m$ 的期望。
>
> 数据范围：$M=\sum |S_i|\le 4\times 10^6$。

**思路分析**

考虑如何刻画一个括号串 $S$ 的权值，考虑一个经典结论，将 $S$ 看成 $\pm 1$ 序列，即每一步向右上或右下方移动的折线。

求出起点到最低点的距离 $L$，终点到最低点的距离 $R$，那么 $S$ 中删除 $L+R$ 个括号后就可以完美匹配，即其权值为 $\dfrac{|S|-L-R}2$，因此我们只要求 $\mathrm{Ex}(L+R)$。

然后考虑刻画 $S_1\sim S_m$ 的权值，类似对每个串定义 $L_i,R_i$，不妨假设整个串的最低点值在 $S_i$ 上，那么第 $i$ 个串对答案的贡献是 $L_i+R_i$。

那么对于其他的每个串 $j$，如果 $L_j>R_j$，把 $S_j$ 放在 $S_i$ 左边，否则 $S_j$ 放在 $S_i$ 右边，每个 $j$ 对答案的贡献都是 $|L_j-R_j|$。

那么一组 $S_1\sim S_n$ 的权值就是 $\max_i L_i+R_i+\sum_{j\ne i}|L_j-R_j|$。

注意到 $L_i+R_i=|L_i-R_i|+2\min(L_i,R_i)$，因此其权值又等于 $\sum_{j=1}^m |L_j-R_j|+2\max_i\{\min(L_i,R_i)\}$。

考虑拆贡献，先处理前一部分的贡献，我们可以对于每个 $j$ 分别算出 $\mathrm{Ex}(|L_j-R_j|)$，注意到这个值就等于 $S_i$ 的左括号个数减去右括号个数，容易做到 $\mathcal O(a_j)$。

因此我们就将原问题转成求 $\mathrm{Ex}(\max\{\min(L_i,R_i)\})$，考虑对每个 $k\ge 1$ 求出 $\max\{\min(L_i,R_i)\}\ge k$ 的概率求和。

反面考虑，等价于对每个 $k\ge 0$ 求出 $\max\{\min(L_i,R_i)\}\le k$ 的概率求和，这又相当于对每个 $i$ 求出 $\min(L_i,R_i)\le k$ 的概率乘起来。

因此我们得到：
$$
\mathrm{Ex}(\max\{\min(L_i,R_i)\})=\sum_{k=0}^\infty 1-\prod_{i=1}^m\mathrm{Pr}(\min(L_i,R_i)\le k)
$$
考虑如何解决单个 $\mathrm{Pr}(\min(L_i,R_i)\le k)$，以下均记 $n=a_i$。

这就相当于求有多少条折线长度为 $n$，起点 $\le k$ 或终点 $\le k$，且最低高度恰好为 $0$。

考虑 $n-1\to n$ 时答案的变化量，相当于求新加入一步后，会有多少路径从合法变不合法或从不合法变合法。

- 只有起点高度 $>k$ 且最后一步终点从 $k+1\to k$ 的路径会从不合法变合法。
- 只有起点高度 $>k$ 且最后一步终点从 $k\to k+1$ 的路径会从不合法变合法。

我们设 $f(m,s,t)$ 表示长度为 $m$，起点高度 $>s$，终点高度 $=t$，的折线数量。

初始概率为 $1$，考虑每次答案变化量的差分得到：
$$
\mathrm{Pr}(\min(L_i,R_i)\le k)=1+\sum_{m=1}^{n-1} (f(m,k,k+1)-f(m,k,k))2^{-m-1}
$$
对 $f(m,s,t)$，枚举起点高度，然后反射容斥求最低高度恰好为 $0$ 的概率，容易发现正负项可以抵消：
$$
f(m,s,t)=\sum_{i=s+1}^{\infty} \binom{m}{\tfrac{m+i+t}2}-\binom{m}{\tfrac{m+i+t+2}{2}}=\binom{m}{\lfloor\tfrac{m+s+t+2}{2}\rfloor}
$$
带入得到：
$$
f(m,k,k+1)-f(m,k,k)=\binom{m}{\lfloor\tfrac{m+2k+3}2\rfloor}-\binom{m}{\lfloor\tfrac{m+2k+2}t\rfloor}
$$
注意到 $m$ 为偶数时 $f(m,k,k+1)-f(m,k,k)=0$，因此我们只要考虑 $m=2p-1$ 的情况，其中 $p=1\sim \left\lfloor\dfrac n2\right\rfloor$：
$$
\mathrm{Pr}(\min(L_i,R_i)\le k)=1+\sum_{p=1}^{\lfloor n/2\rfloor} \left(\binom{2p-1}{k+p+1}-\binom{2p-1}{k+p}\right)2^{-2p-2}
$$
考虑用和式表示，记 $w(n,k)=\sum_{p=1}^n4^{-p-1}\left(\binom{2p-1}{k+p+1}-\binom{2p-1}{k+p}\right)$，观察差分得到：
$$
\begin{aligned}
w(n,k)-w(n,k-1)
&=\sum_{p=1}^n 4^{-p-1}\left(\binom{2p-1}{k+p+1}-2\binom{2p-1}{k+p}+\binom{2p-1}{k+p-1}\right)\\
&=\sum_{p=1}^n 4^{-p-1}\left(\binom{2p-1}{k+p+1}+2\binom{2p-1}{k+p}+\binom{2p-1}{k+p-1}-4\binom{2p-1}{k+p}\right)\\
&=\sum_{p=1}^n 4^{-p-1}\left(\binom{2p+1}{k+p+1}-4\binom{2p-1}{k+p}\right)\\
&=\sum_{p=1}^n 4^{-p-1}\binom{2p+1}{k+p+1}-4^{-p}\binom{2p-1}{k+p}\\
&=2^{-2n}\binom{2n+1}{k+n+1}-\binom{1}{k+1}
\end{aligned}
$$
边界条件是 $w(n,-1)=0$，注意 $k=0$ 时 $\binom{1}{k+1}=1$，带入原式得到：
$$
\mathrm{Pr}(\min(L_i,R_i)\le k)=\sum_{p=0}^{k} 2^{-2\lfloor n/2\rfloor}\binom{2\lfloor n/2\rfloor+1}{k+\lfloor n/2\rfloor+1}
$$
注意到 $w(n,0)-w(n,-1)$ 时的 $-1$ 恰好与原式前面的 $+1$ 抵消了。

很显然 $k>\lfloor n/2\rfloor$ 的概率肯定为 $1$，因此我们暴力求组合数前缀和就能 $\mathcal O(a_i)$ 计算出每个 $k$ 的答案。

时间复杂度 $\mathcal O(M)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=4e6+5,MOD=1e9+7,inv=(MOD+1)/2;
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
ll fac[MAXN],ifac[MAXN],ipw[MAXN],p[MAXN];
ll C(int x,int y) {
	if(x<0||y<0||y>x) return 0;
	return fac[x]*ifac[y]%MOD*ifac[x-y]%MOD;
}
int n,m,a[MAXN];
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),m+=a[i];
	for(int i=fac[0]=ipw[0]=1;i<=m;++i) fac[i]=fac[i-1]*i%MOD,ipw[i]=ipw[i-1]*inv%MOD;
	ifac[m]=ksm(fac[m]);
	for(int i=m;i;--i) ifac[i-1]=ifac[i]*i%MOD;
	for(int i=0;i<=m;++i) p[i]=1;
	for(int o=1;o<=n;++o) {
		int x=a[o]/2; ll w=0;
		for(int i=0;i<=x;++i) w=(w+C(2*x+1,i+x+1)*ipw[2*x])%MOD,p[i]=p[i]*w%MOD;
	}
	ll ans=0,sum=0;
	for(int i=0;i<m;++i) ans=(ans+1+MOD-p[i])%MOD;
	for(int o=1;o<=n;++o) {
		int x=a[o];
		for(int i=0;i<=x;++i) sum=(sum+ipw[x]*C(x,i)%MOD*abs(2*i-x))%MOD;
	}
	printf("%lld\n",(m+MOD-(sum+2*ans)%MOD)*inv%MOD);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：4)

不知道其他题解在推什么。

下文设 $n$ 为原题面中的 $m$，$a_i$ 为原题面中的 $l_i$。

考虑给你 $n$ 个括号串怎么做。经过一些推导，不难发现答案是 $\sum\limits_{i = 1}^n \min(p_i, q_i) - \max\limits_{i = 1}^n \min(x_i, y_i)$，其中 $p_i$ 和 $q_i$ 分别为第 $i$ 个串的左括号和右括号数量，$x_i$ 为把括号串视为网格图上的折线，起点与最低点的距离，$y_i$ 为终点与最低点的距离。

前者是容易的，枚举每个括号串有多少个左括号即可。答案为 $\sum\limits_{i = 1}^n \sum\limits_{j = 0}^{a_i} \min(j, a_i - j) \times \binom{a_i}{j} \times 2^{-a_i}$。

后者考虑拆贡献，计算 $\sum\limits_{k \ge 1} P(\max\limits_{i = 1}^n \min(x_i, y_i) \ge k) = \sum\limits_{k \ge 1} (1 - \prod\limits_{i = 1}^n (1 - P(\min(x_i, y_i) \ge k)))$。所以我们考虑先枚举 $i, k$，对单个 $a_i$ 算 $\min(x_i, y_i) \ge k$ 的方案数。

将最低点设为 $0$，要求就是起点和终点都 $\ge k$。考虑枚举起点 $= s$，终点 $= t$。最低点恰好为 $0$ 可以容斥掉，即方案数等于经过 $y = 0$ 的方案数减去经过 $y = -1$ 的方案数。所以固定 $s, t$ 的方案数为 $\binom{a_i}{\frac{a_i + s + t}{2}} - \binom{a_i}{\frac{a_i + s + t + 2}{2}}$。

答案即为：

$$
\sum\limits_{s \ge k} \sum\limits_{t \ge k} [(a_i + s + t) \bmod 2 = 0] (\binom{a_i}{\frac{a_i + s + t}{2}} - \binom{a_i}{\frac{a_i + s + t + 2}{2}})
$$

发现固定 $s$ 后正负号抵消，上述式子等于：

$$
\sum\limits_{s \ge k} \binom{a_i}{\left\lfloor\frac{a_i + s + k + 1}{2}\right\rfloor}
$$

这个很明显是组合数后缀和的形式。所以在最外层枚举 $i$，预处理组合数后缀和，即可 $O(1)$ 求出上述式子。

时间复杂度 $O(\sum a_i)$。

```cpp
#include <bits/stdc++.h>
#define fst first
#define scd second
#define pb emplace_back
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef pair<int, int> pii;

namespace IO {
	const int maxn = 1 << 20;
	
	char ibuf[maxn], *iS, *iT, obuf[maxn], *oS = obuf;

	inline char gc() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, maxn, stdin), (iS == iT ? EOF : *iS++) : *iS++);
	}

	template<typename T = int>
	inline T read() {
		char c = gc();
		T x = 0;
		bool f = 0;
		while (c < '0' || c > '9') {
			f |= (c == '-');
			c = gc();
		}
		while (c >= '0' && c <= '9') {
			x = (x << 1) + (x << 3) + (c ^ 48);
			c = gc();
		}
		return f ? ~(x - 1) : x;
	}
	
	inline int reads(char *s) {
		char c = gc();
		int len = 0;
		while (isspace(c)) {
			c = gc();
		}
		while (!isspace(c) && c != -1) {
			s[len++] = c;
			c = gc();
		}
		return len;
	}

	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	
	struct Flusher {
		~Flusher() {
			flush();
		}
	} AutoFlush;

	inline void pc(char ch) {
		if (oS == obuf + maxn) {
			flush();
		}
		*oS++ = ch;
	}

	template<typename T>
	inline void write(T x) {
		static char stk[64], *tp = stk;
		if (x < 0) {
			x = ~(x - 1);
			pc('-');
		}
		do {
			*tp++ = x % 10;
			x /= 10;
		} while (x);
		while (tp != stk) {
			pc((*--tp) | 48);
		}
	}
	
	template<typename T>
	inline void writesp(T x) {
		write(x);
		pc(' ');
	}
	
	template<typename T>
	inline void writeln(T x) {
		write(x);
		pc('\n');
	}
}

using IO::read;
using IO::reads;
using IO::write;
using IO::pc;
using IO::writesp;
using IO::writeln;

const int maxn = 4000100;
const ll mod = 1000000007;
const ll inv2 = (mod + 1) / 2;

inline ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) {
			res = res * b % mod;
		}
		b = b * b % mod;
		p >>= 1;
	}
	return res;
}

ll n, m, a[maxn], fac[maxn], ifac[maxn], pw[maxn], ipw[maxn], f[maxn], g[maxn];

inline ll C(ll n, ll m) {
	if (n < m || n < 0 || m < 0) {
		return 0;
	} else {
		return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
	}
}

void solve() {
	n = read();
	for (int i = 1; i <= n; ++i) {
		a[i] = read();
		m += a[i];
	}
	fac[0] = pw[0] = ipw[0] = 1;
	for (int i = 1; i <= m + 5; ++i) {
		fac[i] = fac[i - 1] * i % mod;
		pw[i] = pw[i - 1] * 2 % mod;
		ipw[i] = ipw[i - 1] * inv2 % mod;
	}
	ifac[m + 5] = qpow(fac[m + 5], mod - 2);
	for (int i = m + 4; ~i; --i) {
		ifac[i] = ifac[i + 1] * (i + 1) % mod;
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (ll j = 0; j <= a[i]; ++j) {
			ans = (ans + min(j, a[i] - j) * C(a[i], j) % mod * ipw[a[i]]) % mod;
		}
	}
	for (int i = 1; i <= m; ++i) {
		f[i] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		g[a[i] + 1] = 0;
		for (int j = a[i]; ~j; --j) {
			g[j] = (g[j + 1] + C(a[i], j)) % mod;
		}
		for (int k = 1; k <= a[i] / 2; ++k) {
			ll x = 0;
			if ((a[i] + 1) & 1) {
				x = (C(a[i], (a[i] + 1) / 2 + k) + g[a[i] / 2 + k + 1] * 2) % mod;
			} else {
				x = g[(a[i] + 1) / 2 + k] * 2 % mod;
			}
			f[k] = f[k] * (mod + 1 - x * ipw[a[i]] % mod) % mod;
		}
	}
	for (int i = 1; i <= m; ++i) {
		ans = (ans + mod + f[i] - 1) % mod;
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

---

