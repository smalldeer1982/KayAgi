# Birthday

## 题目描述

A MIPT student named Misha has a birthday today, and he decided to celebrate it in his country house in suburban Moscow. $ n $ friends came by, and after a typical party they decided to play blind man's buff.

The birthday boy gets blindfolded and the other players scatter around the house. The game is played in several rounds. In each round, Misha catches exactly one of his friends and has to guess who it is. The probability of catching the $ i $ -th friend does not change between rounds and is equal to $ p_{i} $ percent (as we know, it is directly proportional to the amount of alcohol consumed by the $ i $ -th friend) and $ p_{1}+p_{2}+...+p_{n}=100 $ holds. Misha has no information about who he caught. After Misha makes an attempt to guess the caught person, the round ends. Even then, Misha isn't told whether he guessed correctly, and a new round begins.

The game ends when Misha guesses every friend at least once, that is, there exists such set of rounds $ k_{1},k_{2},...,k_{n} $ , that during round number $ k_{i} $ Misha caught the $ i $ -th friend and guessed him. Misha wants to minimize the expectation of the number of rounds of the game. Despite the fact that at any point in the game Misha has no information about who he has already guessed, his friends are honest, and if they see that the condition for the end of the game is fulfilled, the game ends immediately. Find the expectation of the number of rounds in the game if Misha plays optimally.

## 说明/提示

The optimal strategy in the first sample is to guess friends alternately.

## 样例 #1

### 输入

```
2
50 50
```

### 输出

```
5.0000000000
```

## 样例 #2

### 输入

```
4
50 20 20 10
```

### 输出

```
39.2846263444
```

# 题解

## 作者：Su_Zipei (赞：4)

### 题目大意

一个人将眼睛蒙起来，然后随机游走，每抓住一个人就猜是谁，直到所有人都曾经被猜过一次后，游戏结束，求最小的期望步数。

### Solution

首先可以发现如果钦定游戏至多到第 $k$ 局结束，此时第 $i$ 个人被猜了 $c_i$ 次，一定有对于任意的 $i$ ， $ c_i > 0$， ~~废话~~。假设知道了到第 $k$ 局的时候任意 $c_i$ 的值，那么是否可以试着算出来至多到当前局结束的概率呢？答案是显然的。

因为最晚到当前局就结束了，所以对第 $i$ 个人猜的 $c_i$ 次里边至少有一次猜中了，这个概率直接算不好算，可以反过来算，用 $1$ 减去就行，即 $1-(1-p_i)^{c_i}$  ，容易得到当前的答案，

$$
ans_k=\prod_{i=1}^n1-(1-p_i)^{c_i}
$$

注意这个答案是至多到第$k$局结束的概率，它还包含着之前结束的概率，所以实际上对答案的贡献是$(ans_k-ans_{k-1})\times k$。

接下来的问题就是怎么得到$c_i$ ，很多题解都是用的贪心写法，事实上也是对的，做法就是首先全部猜一遍，因为任意$c_i>0$，所以最优的策略一定会先将所有人猜一遍，接着就每次枚举选择猜哪个人，然后用选择**当前**最优的选择更新答案 。

如果略微思考一下，不得不怀疑这个贪心的正确性，原因在于用当前局面最优解得到全局最优解是否合理，答案是合理，~~不然为什么能A~~，证明如下(借鉴了官方题解)。

假设在第$k$ 步，贪心得到第$i$ 个人被猜了$x_i$ 次，而实际上这一步里边最优的做法是第$i$ 个人被猜了$y_i$ 次，不妨令$p_i=1-p_i$，那么一定会存在两个数$a,b$ 满足以下两个条件
$$
1-p_a^{x_a}>1-p_a^{y_a}
$$
$$
1-p_b^{x_b}<1-p_b^{y_b}
$$

原因在于$\sum_{i=1}^n x_i=\sum_{i=1}^n y_i=k$ ，这个条件实际上还等价于$y_a<x_a\  \&\&\ x_b<y_b$ 。

不妨令$y_a=y_a+1$，那么此时最优解一定还是它，因为$1-p_a^{y_a+1}>1-p_a^{y_a}$，不过它就不满足$\sum_{i=1}^n y_i=k$，所以令$y_b=y_b-1$，那么这个式子虽然值变小了，但是$1-p_b^{x_b}\leq 1-p_b^{y_b}$ 仍然成立，所以这个仍然是最优解，于是就是一直变变变，最后就会发现对于任意的$i$ ，有$x_i=y_i$，证毕。

由于$p_i$是两位小数，所以这个式子收缩的估计会很快，事实的确如此，~~实践证明~~模拟大概$3\times10^5$ 次就够了。

```cpp

#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef double db;
db p[110],nowp[110],res;
int main(){
	int n;
	scanf("%d",&n);
	res=1.0;
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		p[i]=nowp[i]=(100-x)/100.0;
		res=res*(1-nowp[i]);
	}
	db ans=res*n;
	for(int i=n+1;i<=3e5;i++){
		int pos=1;db now=res/(1-nowp[1])*(1-nowp[1]*p[1]);
		for(int j=2;j<=n;j++){
			db tmp=res/(1-nowp[j])*(1-nowp[j]*p[j]);
			if(tmp>now){
				now=tmp;
				pos=j;
			}
		}
		ans+=(now-res)*i;
		res=now;
		nowp[pos]*=p[pos];
	}
	printf("%.10lf\n",ans);
	return 0;
}
```


---

## 作者：DarthVictor (赞：3)

# 题目
[原题地址](http://codeforces.com/problemset/problem/623/D)
# 解说
假设到目前为止第 $i$ 个人被猜到了 $c_i$ 遍，那么考虑目前游戏结束的概率。

显然第 $i$ 个人一次也没有被猜中的概率是 $(1-p_i)^{c_i}$，则第 $i$ 个人至少被猜中一次的概率为 $1-(1-p_i)^{c_i}$，其乘积即为游戏结束的概率，即
$$ f=\prod_{i=1}^n 1-(1-p_i)^{c_i} $$

那么显然我们可以根据贪心策略先把每个人猜一遍，之后每局选择可以使结束概率增加最多的人。

现在考虑每一局选择猜哪个人最优。假设我们这一局选择猜第 $i$ 个人，那么概率变化量为
$$(1-(1-p_i)^{c_{i+1}})-(1-(1-p_i)^{c_i})$$
化简之后即为
$$p(1-p)^c$$
所以在之后的每一局中我们依据上式得到贡献最大的人并将答案加上这一局的期望即可。

关于精度问题，由于 $p_i \geqslant  0.01$ 所以上述收敛的很快，只要游戏次数枚举到 $3 \times 10^5$ 即可达到精度要求。所以最后时间复杂度为 $ O(n\times 3\times 10^5) $。

## 代码
```cpp


#include<bits/stdc++.h>
#define re register
#define db double
using namespace std;
const int lzw=100+3;
int n,a[lzw];
db f[lzw],p[lzw],ans,lst,g;//f[i]表示目前第i个人已经被猜到的概率
db cal(int x){
	return f[x]+(1-f[x])*p[x];
}
int main(){
	freopen("party.in","r",stdin);
	freopen("party.out","w",stdout);
	scanf("%d",&n);
	for(re int i=1;i<=n;i++) scanf("%d",&a[i]),p[i]=f[i]=a[i]/100.0;
	lst=1;
	for(re int i=1;i<=n;i++) lst*=p[i];
	ans=lst*n;//先将所有人猜一遍
	for(re int i=n+1;i<=300000;i++){
		int tmp=1;
		for(re int j=1;j<=n;j++) if(cal(j)/f[j]>cal(tmp)/f[tmp]) tmp=j;//选取最优的人
		g=lst*cal(tmp)/f[tmp],f[tmp]=cal(tmp),ans+=(g-lst)*i,lst=g;
	}
	printf("%.12lf\n",ans);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

首先往第 $i$ 个位置抓 $k$ 次，抓成功的概率是 $1-(1-p_i)^{k}$。设每个位置分别抓了 $b_i$ 次，那么总的概率是 $\prod_{i=1}^n(1-(1-p_i)^{b_i})$。

考虑每次多抓一次 $x$，贪心地想肯定会最大化目前总的抓住概率（否则交换两次可以达到更优期望）。将所有的 $(1-(1-p_i)^{b_i+1})-(1-(1-p_i)^{b_i})$ 取一个最大值，并选择这个位置抓即可。这样做单次选择可以做到 $O(n)$ 或 $O(\log n)$（堆维护）。

~~秉着只要不 T 能多跑不少跑的原则~~我们观察到只需要输出小数且允许误差，跑若干次单次选择逼近期望即可。实测 $w=10^6$ 次可以通过。

总复杂度 $O(nw)$。

分析一下，$0.99^{10000}$ 大约为 $10^{-43}$，误差确实够小了。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
double nowv[105],ans,tot,lst;
signed main(){
	int n; cin>>n;
	double p[n+1]; for(int i=1;i<=n;i++) cin>>p[i],p[i]/=100,p[i]=1-p[i];
	tot=1;
	for(int i=1;i<=n;i++) nowv[i]=p[i],tot*=(1-p[i]);
	for(int i=n;i<=1000000;i++){
		ans+=(tot-lst)*i;
		lst=tot;
		double maxv=0;
		int maxp=0;
		for(int j=1;j<=n;j++){
			if((1-nowv[j]*p[j])/(1-nowv[j])>maxv){
				maxv=(1-nowv[j]*p[j])/(1-nowv[j]);
				maxp=j;
			}
		}
		if(nowv[maxp]==1) break;
		tot=tot/(1-nowv[maxp])*(1-nowv[maxp]*p[maxp]);
		nowv[maxp]*=p[maxp];
	}
	cout<<fixed<<setprecision(10)<<ans;
	return 0;
}
```

---

## 作者：ww3113306 (赞：1)

[我的博客](https://i.cnblogs.com/EditPosts.aspx?postid=10206511)

题意：n个人，玩抓人游戏，每抓住一个人都要猜这个人是谁。对于每一局，第i个人有$p_{i}$的概率被抓到。游戏结束当且仅当每个人都在某局中被抓到并且猜中自己的名字，求一个合适的策略来使得期望游戏局数最少，输出这个期望最少局数.
题解：设$g[i]$表示到$i$局为止，已经全部被猜中过的概率，$f[i][x]$表示到第$i$局为止，已经猜中过第$x$个人的概率。
那么有$$ans = \sum_{i = 1}^{\infty} (g[i] - g[i - 1])i$$
随游戏局数增长，$g[x]$会趋近于1，要让期望最小，显然在$x$越小时，要让$g[x] - g[x - 1]$越大越好，即$g[x]$增长的越快越好。
若在第$i$局猜被抓到的是$k$，那么有：
$f[i][x] = \begin{cases}
f[i - 1][x] + (1 - f[i - 1][x]) p_{x} \quad x == k\\
f[i - 1][x] \quad x != k
\end{cases}$
$g[x] = g[x - 1] \frac{f[x][k]}{f[x - 1][k]}($因为只有$f[x][k]$变化了)
因此我们只需要让$\frac{f[x][k]}{f[x - 1][k]}$最大即可。
$$\frac{f[x][k]}{f[x - 1][k]} = \frac{f[x - 1][k] + (1 - f[x - 1][k])p_{k}}{f[x - 1][k]} = 1 + \frac{(1 - f[x - 1][k])p_{k}}{f[x - 1][k]}$$
所以要使$\frac{(1 - f[x - 1][k])p_{k}}{f[x - 1][k]}$最大。
因此我们枚举$k$,贪心的找最优策略并更新答案，大约$3e5$次可以满足精度要求

这里注意为了满足初始化的要求(在没有把n个人都猜过之前，是没有概率全部猜中的)，所以要在最开始先把n个人都猜一遍，然后再继续贪心

代码在我的博客里有

---

## 作者：sodak (赞：0)

## 思路
男孩在游戏结束之前不能得到任何信息,而且每一次男孩抓到的人概
率是定值,所以游戏是否结束的概率只和每个人被猜了多少次有关。
假设第i个人男孩猜了$c_i$ 遍,那么游戏结束的概率就是
	
>>> $\prod^{n}_{i=1}1-(1-p_i)^{c_i}$
 
 考虑在什么情况下男孩开始有成功的概率，显然是每个人都猜过一遍之后，这时候才能开始计算答案。
 
 设恰好在第$i$局游戏结束的概率为$P_i$，那么第$i$局结束贡献的期望就是$i*P_i$，为了使期望局数最小，所以应该在$i$较小的时候，让$P_i$尽量大,这样才能让游戏尽可能早的结束。
 
 所以男孩的最优策略一定是先把每个人猜一遍,然后每次选择一
个让游戏结束概率最大的猜测。

那么如何选择一个最优的猜测呢，因为期望是连乘得到的，所以我们一定会选择一个人多选择一次会游戏结束的概率变化尽量大的，即，$\frac{1-(1-p^{c_{i}+1})}{1-(i-p^{c_i})}$尽量大，这个东西我们可以用堆来处理一下，每次贪心选最大的，模拟$3e5$次，精度就不会出问题了。

需要注意的是 $\prod^{n}_{i=1}1-(1-p_i)^{c_i}$这个式子求出来的实在第$i$局游戏结束的概率，包括了在小于$i$局游戏结束的概率，假设 $g_i=\prod^{n}_{i=1}1-(1-p_i)^{c_i}$，那么恰好在第$i$局结束的概率$P_i$就是$g_i-g_{i-1}$，把从$n-3e5$局之间的贡献计算求和就可以了。



## code
```cpp


#include<bits/stdc++.h>
#define re register
#define db double
#define gc getchar()
#define getch while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=gc;}
#define getnu while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-'0';ch=gc;}
using namespace std;
inline int read(){int s=0,f=1;char ch=gc;getch;getnu;return s*f;}
const int maxn=110;
priority_queue<pair<db,int> >q;
db p[maxn];
db lans[maxn];
int main(){
	int n=read();
	db now=1;
	for(int i=1;i<=n;i++){
		p[i]=(db)read()/100;
		db nowans=1-(1-p[i]);
		db nxtans=1-(1-p[i])*(1-p[i]);
		q.push(make_pair(nxtans/nowans,i));
		lans[i]=nowans;
		now*=lans[i];
	}
	db ans=0;
	db lgl=now;
	ans+=now*n;
	for(int i=1;i<=300000;i++){
		db del=q.top().first;
		int id=q.top().second;
		q.pop();
		now/=lans[id];
		now*=(lans[id]*del);
		ans+=(now-lgl)*(n+i);
		lgl=now;
		lans[id]=lans[id]*del;
		db nxtans=(1-(1-lans[id])*(1-p[id]));
		q.push(make_pair(nxtans/lans[id],id));
	}
	printf("%.10lf\n",ans);
}

```

---

