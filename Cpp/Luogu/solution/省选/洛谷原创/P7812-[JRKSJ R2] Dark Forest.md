# [JRKSJ R2] Dark Forest

## 题目背景

**本题为提交答案题。**

## 题目描述

给你一个长为 $n$ 的序列 $a$，定义 $1\dots n$ 的排列 $p$ 的权值为

$$\sum_{i=1}^n p_i a_{p_{i-1}} a_{p_i}a_{p_{i+1}}$$

你可以理解为这个排列是一个环，即 $p_{0}=p_n,p_{n+1}=p_1$。

请构造一个权值**尽量大**的 $1\dots n$ 的排列。

## 说明/提示

注意是 `a[p[i-1]] a[p[i+1]]`，数据有一定梯度。

### 数据范围

对于 $100\%$ 的数据，$1\le n,a_i\le 10^3$。

### 样例解释

该排列的权值为 $1\times2\times1\times3+3\times1\times3\times5+5\times3\times5\times4+2\times5\times4\times2+4\times4\times2\times1=463$，可以证明这是最优的排列之一。

### 评分方式

**本题使用 Special Judge**，每个测试点都有 $10$ 个参数 $v_1,v_2,\dots v_{10}$。如果你的输出的权值 $V\ge v_i$，则该测试点您至少会获得 $i$ 分。

特别的，如果您的输出不是一个 $1\dots n$ 的排列，您会在该测试点获得 $0$ 分。

评分参数已经放至附件。

## 样例 #1

### 输入

```
5
1 4 3 2 5```

### 输出

```
1 3 5 2 4```

# 题解

## 作者：critnos (赞：17)

### 1

全排列。

### 2

写了一个丢人的 $O(n^3 2^n)$ 的状压 dp 跑了 2min。

### 3

大眼观察不难得到结论：当 $n\ge 4$ 时，初始排列为 $\{1,2,3\}$，后面从 $4$ 开始每个数 $x$ 插入到 $x-1$ 和 $x-2$ 之间。

遗传应该比较难过，跑一晚上没准能过呢（

### 4~5

给退火的（我本机用退火跑 1s 造的数据，但是用退火过掉这两个点却很困难，不知道为什么）。

### 6~10

本来想给裸的遗传一点部分分的，然后发现裸的遗传比退火还差。

这些点是给遗传的。

定义“基因”为排列 $p$，定义一次“变异”为交换 $p$ 中的两个元素，定义一个基因的“优秀程度”为他的权值。

其实我写的也不算遗传（我用 TSP 尝试了下交配，发现并不比用大量变异代替交配优秀，另外多种群遗传也不比这个优秀），就是每次让每个基因变异生成 $10$ 个儿子，然后按照权值排序。限制种群大小，生成下一代之后只保留最优秀的 $maxn$ 个。

同时采取保留精英策略，把父辈中的最优秀基因完整复制到下一代中。

但这样仍然不足以通过本题，还需要一个优化：因为遗传局部收敛比较慢，所以改良上面的保留精英策略，把父辈中的最优秀基因先变异一次，然后对它爬山，爬山 $10000$ 次基本就可以了。

在测试 TSP 问题的时候，同样跑 10s，退火和爬山均是 28w 左右（路线总长），遗传是 25w 左右，上面的做法可以去到 16w 左右。

没有实现粒子群和蚁群，不知道能不能通过本题。

物竞天择，适者生存，这才是题目真正的意义。

代码不放了，需要者私信。

---

## 作者：chenxia25 (赞：16)

要什么遗传？模拟退火可以轻轻松松地，每个点跑两秒，再特判一下 #3 的特殊构造，就 AC 了。

和较劣的模拟退火实现相比较，最关键的一点在于：计算一个排列权值的复杂度。

我们都知道模拟退火的时间复杂度是 $\mathrm O(-F\log_{\Delta T}{T_0\over T_e})$，其中 $T_0$ 是初温度，$T_e$ 是末温度，$\Delta T$ 是降温系数，$F$ 是计算一个方案权值的时间。那么降低 $F$，就能允许我们跑更多次。

对于方案集合是排列的模拟退火，一般扰动方法都是随机交换两个位置。而交换前后的权值增量显然是能 $\mathrm O(1)$ 计算的，把交换的两个位置相邻三项的贡献加加减减即可……不需要每次都 $\mathrm O(n)$。

这样就是说，降温次数可以开到 $10^7\sim 10^8$ 量级，能在几秒内跑完。这使我们可以输入最奢侈的参数：$T_0=10^{15},T_e=10^{-15},\Delta T=1-10^6$。在有条件的情况下，尽量提高 $\Delta T$，相当于让降温过程更加精细，只跑一次，一般是要比不改变参数跑很多次效果好很多的。

这里还有一个问题：退火一般是把过程中得到的每个解都往答案里尝试更新一下，而不只看最后得到的那个解，这样无疑是不劣的。但这里更新答案的时间复杂度是 $\mathrm O(n)$，那肯定不行。一个解决方案是，把修改路径（就是每次交换的两个位置）和每次的权值记录下来，最后再还原。但这样空间复杂度就变为与降温次数同阶的了。并不是说开不下，总觉得不够优美。

一个比较好的解决方案是：采用定期重构，或者类似于分块 bitset 的思想，每 $\mathrm O(n)$ 次更新分为一块，每块内记录路径、更新一次，这样时空复杂度都达到了原来的水平。

但这是乱搞题，居然还搁这设计算法，真是多此一举了。事实上，一边退火一边更新答案只在 $\Delta T$ 较小（退火不够精细）的情况下有比较好的效果，$\Delta T$ 很大时基本上最后的解就是过程中的最优解了。所以干脆直接取最后的结果得了。

这样简单地实现一下，每个点花两秒跑一下就过了。然后看到了[这个贴子](https://www.luogu.com.cn/discuss/434991)，突发奇想如果我的退火每个点跑个 5min 会得到怎样的结果。于是令 $\Delta T=1-10^8$，跑出来 #4~10 的结果分别是 1420195017577、1637948882729、157875782146328、142779066317098、149662580014302、141775806487785、145539684174123，可以看到比贴子里给出的新答案还要高出一截。

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = double;
using pii = pair<int, int>;
#define mr make_pair
#define fi first
#define se second
using vi = vector<int>; using vii = vector<pii>;
#define pb emplace_back
#define sz(x) ((int)(x).size())
template<class T, class U> inline void cmn(T &x, const U &y) { if(y < x) x = y; }
template<class T, class U> inline void cmx(T &x, const U &y) { if(y > x) x = y; }
const char nl = '\n', nk = ' ';
const int inf = sizeof(int) == 4 ? 0x3f3f3f3f : 0x3f3f3f3f3f3f3f3f;

mt19937 rng(19171107);
int rnd(int l, int r) { return uniform_int_distribution<>(l, r)(rng); }
db rndb(db l, db r) { return uniform_real_distribution<>(l, r)(rng); }

const int N = 1010;

int n;
ll a[N];
int p[N];

ll res;

void calc(int x, int v) {
  int A = p[x > 2 ? x - 2 : x + n - 2], B = p[x > 1 ? x - 1 : n], &C = p[x], D = p[x < n ? x + 1 : 1], E = p[x < n - 1 ? x + 2 : x + 2 - n];
  res -= (a[A] * a[B] * B + a[B] * C * a[D] + D * a[D] * a[E]) * a[C];
  C = v;
  res += (a[A] * a[B] * B + a[B] * C * a[D] + D * a[D] * a[E]) * a[C];
}

void SA(db t0, db te, db dt) {
  res = 0;
  for(int i = 1; i <= n; ++i) calc(i, i);
  for(db t = t0; t >= te; t *= dt) {
    int x = rnd(1, n), y = rnd(1, n);
    ll ores = res;
    int px = p[x], py = p[y];
    calc(y, px), calc(x, py);
    if(res > ores || rndb(0, 1) <= exp((res - ores) / t));
    else res = ores, swap(p[x], p[y]);
//    cerr << t << ": " << res << nl;
  }
  cerr << "res = " << res << nl;
  for(int i = 1; i <= n; ++i) cout << p[i] << (i == n ? nl : nk);
}

void mian() {
  cin >> n;
  for(int i = 1; i <= n; ++i) cin >> a[i];
  SA(1e15, 1e-15, 0.99999999);
}

signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t = 1;
//  cin >> t;
  while(t--) mian();
  return 0;
}

```





---

## 作者：违规用户名76G!ihcm (赞：14)

大概是看到了这道题

觉得挺有意思的

每次 rand 两个位置 swap 能更优就换

他表现还可以，获得了 $62$ 分的好成绩。

发现每次 rand 两个位置容易 rand 到换过的位置，很亏。

于是把 rand 两个位置改成了枚举两个位置，能换就换直到换不了。

他比爬山厉害很多，获得了 $92$ 分的好成绩。

换几个随机种子多测测，获得了 $99$ 分的好成绩。

发现第三个点有性质，看起来 奇数正序放前面 偶数逆序放后面 很厉害

就过了。

但他的优化空间还是很大的。

把 “每次换一个随机种子” 改成 “每次把答案排列随机换 $25$ 对”

表现非常好，~~获得了更换数据的好成绩~~ 新数据大概 $2min$ 出解。

代码 https://www.luogu.com.cn/paste/srsy19qf

实现难度主要在 $O(1)$ 交换两个数计算答案。

~~物竞天择，适者生存，这才是……~~

说起来我还不会遗传呢（


---

## 作者：__er (赞：7)

首先理解一下权值的定义，考虑模拟退火，每次随机交换序列中的两个数，考虑 $O(1)$ 求得权值的变化，只需要看相邻三项的变化即可，然后走标准退火流程，概率接收较劣解，最后输出排列即可。

流程并不难想，也并不难写，难点落在调参上。

特别地，用更好的参数跑一次退火远远优于使用更劣的参数跑多次退火，所以我们要尽量地卡满时限。

_以上为本题解法的说明，下面正文开始：_

> **本题为提交答案题。**

给自己上点难度，直接提交这个题：

>**4~5**
>给退火的（我本机用退火跑 1s 造的数据，但是用退火过掉这两个点却很困难，不知道为什么）。

啊？出题人点名卡掉退火甚至只特意给了它两个点？

**那我们直接挑战使用模拟退火直接提交并 AC。**

卡一下时限，发现 #9#10 跑得很快却没有 AC，显然浪费时限是不允许存在的，但是 #9 不小心直接过了，我们对 #10 写一个更精细的退火，即减慢降温速度，然后就过了，此时我们拿到了 99pts，#3 是一个有序的序列，本地浅跑一下看一眼趋势，两端大中间小，直接对 #3 进行一个构造。

然后就过掉了。

[Code](https://www.luogu.com.cn/paste/kppexklk)

结果发现了一个神奇调参法，进行一个大力调参，仅仅 $5$ 发就以除 #3 构造外平均 700ms 的好成绩再次直接提交砍下了这道题的 AC。

[Code](https://www.luogu.com.cn/paste/lgr6ih5b)

---

## 作者：破忆 (赞：7)

[P7812 [JRKSJ R2] Dark Forest](https://www.luogu.com.cn/problem/P7812)

很有意思的一道随机题，卡了一整天。

## 【题意】

给你一个长为 $n$ 的序列 $a$，求一个排列 $1\dots n$ 的排列 $p$，使得 $\sum_{i=1}^n a_i p_ip_{i-1}p_{i+1}$ 尽可能大。

## 【分析】

提交答案题，考虑使用随机化算法来做。

### #1~#2

于是一开始就写了模拟退火，每次交换两个位置，若更优则保留，否则以一定概率接受较劣解，轻松过掉了这两个点。

代码大概长这个样子。

```cpp
#include<bits/stdc++.h>
#include<windows.h>
#define DB double
#define LL long long
using namespace std;
const int maxn=1005;
int n;
LL a[maxn],p[maxn],P[maxn];
LL ans;
int mp[maxn];
LL calc(){
	LL ret=p[1]*a[p[n]]*a[p[1]]*a[p[2]]+p[n]*a[p[n-1]]*a[p[n]]*a[p[1]];
	for(int i=2;i<n;i++){
		ret+=p[i]*a[p[i-1]]*a[p[i]]*a[p[i+1]];
	}
	return ret;
}
const DB ST=1e15,ET=1e-5,DT=0.995;
void cpy(){
	cerr<<ans<<endl;
	for(int i=1;i<=n;i++) P[i]=p[i];
	freopen("lst.txt","w",stdout);
	for(int i=1;i<=n;i++) printf("%lld ",P[i]);
	if(ans>=52817386099ll){
		freopen("2.txt","w",stdout);
		for(int k=1;k<=n;k++) printf("%d ",P[k]);
		exit(0);
	}
}
void SA(){
	for(DB T=ST;T>ET;T*=DT){
		int x=rand()%n+1,y=rand()%n+1;
		while(x==y) x=rand()%n+1,y=rand()%n+1;
		swap(p[x],p[y]);
		LL now=calc(),del=now-ans;
		if(del>0){
			ans=now;
			cpy();
		}
		if(exp((DB)del/T)<=(DB)rand()/RAND_MAX) swap(p[x],p[y]);
	}
}
int main(){
	srand(GetTickCount());
	freopen("2.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),p[i]=P[i]=i;
	random_shuffle(P+1,P+1+n);
	while(1){
		for(int i=1;i<=n;i++) p[i]=P[i];
		SA();
	}
	return 0;
}
```


### #3

这个需要特殊构造，用后面的算法跑了几个小时，输出一个较优解，发现大致是两边大中间小，于是前面奇数递减、后面偶数递增，过掉了这个点。

### #4~#5

继续退火，疯狂调参过了 $4$，过不了 $5$。

然后看到了**遗传算法**。

大致是模拟生物进化的过程。

变异->淘汰->交配->遗传->繁殖->变异。

这题交配的过程比较麻烦，不用模拟。

把当前较优解集看成种群，把其中一组解看成一个个体，把交换一组解中的某几个位置看成变异。

每次选取种群中较优的个体保留，进行变异，较优秀个体可以多繁殖后代，重复操作。

试了几遍过了，代码里还是有点退火的影子。

```cpp
#include<bits/stdc++.h>
#include<windows.h>
#define DB double
#define LL long long
using namespace std;
const int maxn=1005;
int n;
LL a[maxn],p[maxn];
LL ans;
int mp[maxn];
struct P{
	int p[maxn];
	LL w;
	bool operator <(P b)const{return w>b.w;}
}s;
set<P> S1,S2;
set<P>::iterator it;
LL calc(){
	LL ret=s.p[1]*a[s.p[n]]*a[s.p[1]]*a[s.p[2]]+s.p[n]*a[s.p[n-1]]*a[s.p[n]]*a[s.p[1]];
	for(int i=1;i<n;i++){
		ret+=s.p[i]*a[s.p[i-1]]*a[s.p[i]]*a[s.p[i+1]];
	}
	return ret;
}
void print(){
	cerr<<ans<<endl;
	freopen("5.txt","w",stdout);
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++) printf("%d ",mp[i]);
	putchar(10);
}
const int B=30;
const DB ST=1e12,ET=1e-5,DT=0.99;
void SA(){
	for(DB T=ST;T>ET;T*=DT){
		int j=1;
		S2.insert(*S1.begin());
		for(it=S1.begin();it!=S1.end();++it,j++){
			int t=j<=3?10:(j<=10?5:2);
			for(int i=1;i<=n;i++) s.p[i]=(*it).p[i];
			for(int i=1;i<=t;i++){
				int x=rand()%n+1,y=rand()%n+1;
				while(x==y) x=rand()%n+1,y=rand()%n+1;
				swap(s.p[x],s.p[y]);
				LL now=calc(),del=now-ans;
				if(del>0){
					ans=now;
					for(int i=1;i<=n;i++) mp[i]=s.p[i];
					print();
				}
				s.w=now;
				S2.insert(s);
				if(del<0&&exp((DB)del/T)<=(DB)rand()/RAND_MAX) swap(s.p[x],s.p[y]);
			}
			while(S2.size()>B) S2.erase(--S2.end());
		}
		S1.clear();
		for(it=S2.begin();it!=S2.end();++it) S1.insert(*it);
	}
}
int main(){
	srand(GetTickCount());
	freopen("5.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),mp[i]=i;
	random_shuffle(mp+1,mp+1+n);
	while(1){
		for(int i=1;i<=n;i++) s.p[i]=mp[i];
		LL now=calc();
		s.w=now;
		if(now>ans){
			ans=now;
			print();
		}
		S1.clear();
		S1.insert(s);
		SA();
	}
	return 0;
}
```

### #6~#10

继续遗传。

$2000\ years\ later$，$6$ 和 $7$ 过了。

后面几个点非常困难，我不确定能否在有生之年跑出来。

**为什么随机交换的算法出解速度很慢？**

拜读了@76G!ihcm的题解之后，我恍然大悟。

因为做了很多无用交换。

若当前得到了一个较劣的解，它既有可能产生更优的解，又有可能退回更劣的解。

我们不知道这个较劣解会将结果导向何方，或为其花费资源试错，或忽视一条捷径。

所以要尽量避免出现此类状况。

对于当前状态，按**顺序**枚举两个位置，能更优就交换，这样就确保了每一次交换都能产生较大的收益。

**陷入僵局怎么办？**

无法操作时，随机选 $20$ 组点交换，抛砖引玉。

代码参考了@76G!ihcm。

```cpp
#include<bits/stdc++.h>
#include<windows.h>
#pragma GCC optimize(2)
#define LL long long
using namespace std;
const int maxn=1005;
int n;
LL a[maxn],p[maxn];
LL calc(){
	LL ret=p[1]*a[p[n]]*a[p[1]]*a[p[2]]+p[n]*a[p[n-1]]*a[p[n]]*a[p[1]];
	for(int i=2;i<n;i++){
		ret+=p[i]*a[p[i-1]]*a[p[i]]*a[p[i+1]];
	}
	return ret;
}
LL del(int x){
	LL ret=0;
	int l=x-1,r=x+1;
	ret+=p[x]*a[p[l]]*a[p[x]]*a[p[r]];
	ret+=p[l]*a[p[l-1]]*a[p[l]]*a[p[x]];
	ret+=p[r]*a[p[x]]*a[p[r]]*a[p[r+1]];
	return ret;
}
int id[maxn];
LL ans,now;
int P[maxn];
void cpy(){
	cerr<<ans<<endl;
	for(int i=1;i<=n;i++) P[i]=p[i];
	if(ans>145302138855600ll){
		freopen("10.txt","w",stdout);
		for(int k=1;k<=n;k++) printf("%d ",P[k]);
		exit(0);
	}
}
void work(){
	bool flg;
	do{
		flg=0;
		for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++){
			int x=id[i],y=id[j];
			LL nxt;
			if(abs(x-y)<=3||abs(x-y)>=n-2){
				swap(p[x],p[y]);
				nxt=calc();
			}else{
				nxt=now-del(x)-del(y);
				swap(p[x],p[y]);
				nxt+=del(x)+del(y);
			}
			if(nxt>ans){
				ans=now=nxt;
				cpy();
				flg=1;
			}else if(nxt>now) now=nxt,flg=1;
			else swap(p[x],p[y]);
		}
	}while(flg);
}
int main(){
	freopen("10.in","r",stdin);
	srand(GetTickCount());
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),p[i]=id[i]=i;
	random_shuffle(p+1,p+1+n);
	while(1){
		for(int i=1;i<=20;i++){
			int x=rand()%n+1,y=rand()%n+1;
			swap(p[x],p[y]);
		}
		now=calc();
		if(now>ans){
			ans=now;
			cpy();
		}
		random_shuffle(id+1,id+1+n);
		work();
	}
	return 0;
}
```
## 【算法】

随机化贪心/遗传/模拟退火

## 【注】

以上代码的参数均为作者复盘做题过程时回忆的，不是最优参数。

---

## 作者：tyccyt (赞：6)

一道很适合[模拟退火](https://oi-wiki.org/misc/simulated-annealing/)的题
# P7812 [JRKSJ R2] Dark Forest

## 题目大意

给你一个长为 $n$ 的序列 $a$ ，定义 $1\dots n$ 的排列 $p$ 的权值为 $\sum_{i=1}^n p_i a_{p_{i-1}} a_{p_i}a_{p_{i+1}}$ 

最大化 $\sum_{i=1}^n p_i a_{p_{i-1}} a_{p_i}a_{p_{i+1}}$ 

## 此题题解

- ### #3

  这个样例很有性质，**我们就使大的值尽量去乘大的值**，也就是奇数递增，偶数递减。

- ### 其他的测试点

  很明显可以退火。

  初始状态可以是 $ 1 \dots n $ 

  每次退火，随机两个值进行交换，我们发现改变序列权值的是你交换的两个数以及这两个数相邻的数，所以我们可以直接减去交换前这些值对权值的贡献再加上交换后这些值的贡献就行了，(注意：这里要用 ```map``` 或数组之类的去重)
代码的实现难度还好。

  温度什么的可以设成。

  ```long double T=1e11,T_min=1e7,d=0.999998;```
第一次写题解，求通过

---

## 作者：whiteqwq (赞：6)

[P7812 [JRKSJ R2] Dark Forest](https://www.luogu.com.cn/problem/P7812)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1816562)

## 题意

给定一个长度为 $n$ 的序列 $a$，定义一个排列 $p$ 的权值为 $\sum_{i=1}^np_ia_{p_{i-1}}a_{p_i}a_{p_{i+1}}$。

一共有 $10$ 个点，每个点都有一个评分参数，你需要构造一个权值尽可能大的排列让权值大于评分参数。

$1\leqslant n\leqslant 1000$。

## 分析

不愧是黑暗森林，你永远不知道什么时候会被一道大毒瘤题坑害。/cy

考虑随机化（这貌似不是完全的遗传算法），令排列 $p$ 为基因，令上面式子的值为一个基因的优异程度，令交换任意两个数为一次变异。

我们一开始随机生成若干个基因，每次一个基因诞生若干个后代，然后将后代按优异程度排序，删除部分不优秀的后代使得后代数量控制在一个范围内。然后每次再给最优秀的族群产生一个新的后代，并爬山得到较优的解。

然后就耐心跑吧，实在不行调调参，反正我一晚上就跑出来两个包。

也可以尝试加一些特判，比如如果陷入一个局部最优解就强行让部分后代变异若干次，然后改变一次生存法则之类的，这样应该会好一点。

我竟然跑出来了，难以置信。

代码不放了，想要私信。

---

## 作者：a1co0av5ce5az1cz0ap_ (赞：3)

这题太不牛了把。

首先一眼退火，直接开写。

既然要退火就要退的大一些，自然计算就要快一点。

每次只交换两个数，可以直接计算它们造成的影响。

之后直接退退退，$d=1-10^{-7},T_0=10^{15},T_e=10^{-6}$，直接过 #1#2#4#5#6#7#8#9#10.

\#3 过不去怎么办？退退退！

$d=1-10^{-8},T_e=10^{-2}$，多跑几次就过了。

事实上做了三个小时，中间有不少时间在调两个弱智问题（一个是 @FelderQwQ 把 #7 限制当成 149 开头然后做了半天做不出来，另一个是 $\frac{cur-lst}t$ 打成了 $\frac{|cur-lst|}t$ 导致挂飞），我很好奇为啥有那么多人模拟退火都过不去。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<int,ll> pil;
#define fi first
#define se second
#define endl '\n'
#define mp make_pair
#define pb push_back
#define all(x) x.begin(),x.end()
#define Cl(x) memset(x,0,sizeof(x))
const bool DC=0;
const ll mod=0;
const int N=0;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll qpow(ll a,ll b,ll p=mod){ll ans=1;for(;b;b>>=1,a=a*a%p)if(b&1)ans=ans*a%p;return ans;}
void NO(){cout<<"NO\n";}
void YES(){cout<<"YES\n";}
mt19937 rnd((unsigned long long)new char);
int rnad(){return abs((int)rnd());}
int rd(int l,int r){return rnad()%(r-l+1)+l;}

int n;
ll a[1005];
ll p[1005],r[1005],as[1005];
ll ans;
double d=0.99999999,eps=1e-2;
ll calc(int x,ll v,ll _){// 这里参考了 chenxia25 大神的写法
	ll A=p[x>2?x-2:x+n-2],B=p[x>1?x-1:n],&C=p[x],D=p[x<n?x+1:1],E=p[x<n-1?x+2:x+2-n];
	_-=(a[A]*a[B]*B+a[B]*C*a[D]+D*a[D]*a[E])*a[C];
	C=v;
	_+=(a[A]*a[B]*B+a[B]*C*a[D]+D*a[D]*a[E])*a[C];
	return _;
}
void upd(ll tmp){if(tmp>ans)ans=tmp,memcpy(as,p,sizeof(p));}
void sa(double t,bool st){
	ll lst=ans;
	ll cnt=0;
	if(st)for(int i=1;i<=n;i++)lst=ans=calc(i,i,lst);
	while(t>eps){
		int x=rd(1,n),y=rd(1,n),px=p[x],py=p[y];
		ll cur=calc(y,px,lst);
		cur=calc(x,py,cur);
		upd(cur);
		if(++cnt%1000000==0)cerr<<"cnt: "<<cnt<<", cur: "<<cur<<", ans: "<<ans<<", t: "<<t<<", "<<x<<" "<<y<<" "<<px<<" "<<py<<"\n";
		if(exp((cur-lst)/t)>rd(0,32767)/32767.0)lst=cur;
		else swap(p[x],p[y]);
		t*=d;
	}
}

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sa(1e15,1);cerr<<"ans: "<<ans<<"\n";
	cerr<<"total ans: "<<ans<<"\n";
	for(int i=1;i<=n;i++)cout<<as[i]<<" \n"[i==n];
}
int main(){/*freopen(".in","r",stdin);freopen(".out","w",stdout);*/__INIT__();int T;DC?cin>>T,1:T=1;for(int _CASE=1;_CASE<=T;_CASE++)__SOLVE__(_CASE);return 0;}

```

---

## 作者：Li_Yichen (赞：2)

模拟退火。算是模拟退火裸题了，只不过坑点比较多。第一点，这是一个环，要处理边界值的前后问题。模拟退火计算函数的实现要寻找一个计算时间为 $O(1)$ 的算法。第二点，也是很多题解里并没有提到的，关于为什么要加取地址符，以及为什么不加就会错。第三点，对于第三个点的特殊构造，我们需要特殊处理。前两个坑点在。前两个坑点在代码里都有体现，详见代码注释。除了第三个点，其他的直接模拟退火即可，因为是提交答案题，参数可以尽可能的精确，在经过反复调参后得到以下代码，可以通过除第三个点外的所有。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int times = 1;
const double T1 = 1e-15;
const double Dleta_T = 0.9999993;
int n;
int a[1005];
int p[1005];
int ans;
//rand()函数复杂度太劣了，选择mt19937 
mt19937 rng(rand());
int rand(int l,int r){//生成整数类型的随机数，从l到r 
	return uniform_int_distribution<>(l,r)(rng);
}
double generate(int l,int r){//生成小数类型的随机数，从l到r 
	return uniform_real_distribution<>(l,r)(rng);
}
//把第x位置的权值换为l后的值
void value(int x,int l){
	/*
	如果不是环： 
	A = p[x-2]
	B = p[x-1]
	C = p[x]
	D = p[x+1]
	E = p[x+2]
	是环的情况需要用分支结构判断（或三目运算符）(坑点一) 
	*/
	int A,B,D,E;
	if(x - 2 > 0) A = p[x-2];
	else A = p[x+n-2];
	if(x - 1 > 0) B = p[x-1];
	else B = p[n];
	if(x - n < 0) D = p[x+1];
	else D = p[1];
	if(x - n + 1 < 0) E = p[x+2];
	else E = p[x-n+2];
	int &C = p[x];//带了取地址符 (坑点二) 
	/*
	计算原理类似于计算1到100的数字和后，把数字x换成y
	1.O(n)算法即为把x换为y后再次累加
	2.O(1)算法：把数字和-x+y即可
	其中第二种方法类似于本题的计算方法,但是和第二种方法的唯一区别为此算法会影响到周围的数，需要额外处理，只是思想相同 
	*/
	ans -= (a[A] * a[B] * B + a[B] * C * a[D] + D * a[D] * a[E]) * a[C];
  	C = l;
  	ans += (a[A] * a[B] * B + a[B] * C * a[D] + D * a[D] * a[E]) * a[C];
}
void simulated_annealing(){
	double T0 = 1e15;
	while(T0 >= T1){
		int x = rand(1,n);
		int y = rand(1,n);
		int last = ans;
		//实际上已经交换了，因为C带了取地址符 
		int px = p[x];
		int py = p[y];
		value(y,px);
		value(x,py);
		int Dleta_E = ans - last;
		if(Dleta_E > 0 || exp(Dleta_E/T0) >= generate(0,1));//接受了，不需要做什么 
		else{//不接受 
			ans = last;//保存以前的最优解 
			swap(p[x],p[y]);//交换回来 
		}
		T0 *= Dleta_T; 
	}
}
void work(){
	for(int i=1;i<=times;i++){
		simulated_annealing();
	}
}
signed main(){
	//freopen("10.in","r",stdin);
	//freopen("11.out","w",stdout);
	srand(time(NULL));
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		value(i,i);
	}
	work();
	cout << ans << endl;
	for(int i=1;i<=n;i++){
		cout << p[i] << " ";
	} 
	return 0;
} 
```

接下来就要考虑第三个特殊构造的点，发现输入就是一个递增的排列，通过上面代码得到的较优解虽然不能获得答案，但能够帮我们找到规律。寻找一个比较接近答案的较优解，发现基本上数字大小是按照两边大中间小来排列的，即为按照山谷的形状分布，我们不妨假设这种山谷的构造方式是最优的，按照此规律构造测试样例即可通过第三个点。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[1005];
int p[1005];
int ans;
int cnt = 0;
signed main(){
	cin >> n;
	for(int i=n-1;i>1;i-=2){
		p[++cnt] = i;
	}
	p[++cnt] = 1;
	for(int i=1;i<=n&&cnt<n;i+=2){
		p[++cnt] = i + 1;
	}
	for(int i=1;i<=cnt;i++){
		cout << p[i] << " ";
	}
	cout << endl << ans;
	return 0;
} 
```

---

## 作者：MeteorFlower (赞：2)

[更好的阅读体验。](https://www.cnblogs.com/DRPLANT/p/dark_forest.html)

超级大乱搞题。~~考察了选手的电脑配置。~~

首先构造一下把 #3 过掉。构造方法是每次把 $x$ 插到 $x-2$ 与 $x-1$ 两者之间。初始序列是 $\{1,2,3\}$。可以证明 $x-2$ 与 $x-1$ 一定是靠在一起的。

然后按照出题人题解实现了一下。因为没写过遗传也没看过一个字遗传的代码所以以下内容全是基于出题人题解口胡的。

定义“基因”为一组排列，“变异”为交换一组排列中的两个元素。设两个常数 $limit$ 和 $best$（$best \approx 0.01 \times limit$）。首先随 $limit$ 个基因，把它们按照权值降序排序。每次让所有基因变异 10 次生成 10 个儿子并把所有子代排序。同时采取所谓的“保留精英”策略，把亲代基因中权值最大的 $best$ 个归并进去。种群中排名超过 $limit$ 的部分扔掉。

然而这个所谓的“保留精英”策略其实并不是很好，因为这些所谓的精英可能也没那么优秀。所以在把它们归并进去之前先变异一次然后做一下爬山。这样逼近答案的速度可能会快一点。

很快地把 #1~5 跑出来了。#6 跑了一个中午，#7 跑了一个早上。之后的怎么也跑不出来了。

然后观察题解发现了一个跑得很快的暴力。就是直接枚举两个位置，若交换它们能更优则交换。如果无论如何交换都无法更优就变异 20 次再做。我用这个策略代替了那个神必的爬山（之所以如此神必很可能是因为我爬山写的是假的）。此外再增加了让那 $best$ 个精英产生更多后代（100 个）的策略。这个改良后的算法跑得很快。学校机房的老年机都能在 2min 左右跑完，似乎比那个朴素的暴力稍微快一点？（不确定。）总之比较猛。

可能有点抽象。所以把核心代码放上来。

```cpp
mt19937 rnd(random_device{}());
inline int random(int l, int r) {
  return rnd() % (r - l + 1) + l;
}

class Gene {
 private:
  int p[maxn];
  i64 val = 0;
  inline void calc() {
    val = 0, p[0] = p[n], p[n + 1] = p[1];
    for (int i = 1; i <= n; i++)
      val += p[i] * w[p[i - 1]] * w[p[i]] * w[p[i + 1]];
    p[0] = p[n + 1] = 0;
  }
  inline void erase(int x) {
    val -= p[x] * w[p[x - 1]] * w[p[x]] * w[p[x + 1]];
    val -= p[x - 1] * w[p[x - 2]] * w[p[x - 1]] * w[p[x]];
    val -= p[x + 1] * w[p[x]] * w[p[x + 1]] * w[p[x + 2]];
  }
  inline void insert(int x) {
    val += p[x] * w[p[x - 1]] * w[p[x]] * w[p[x + 1]];
    val += p[x - 1] * w[p[x - 2]] * w[p[x - 1]] * w[p[x]];
    val += p[x + 1] * w[p[x]] * w[p[x + 1]] * w[p[x + 2]];
  }

 public:
  inline bool operator<(const Gene &q) const {
    return val > q.val;
  }
  inline i64 Val() const {
    return val;
  }
  inline void Output() const {
    for (int i = 1; i <= n; i++)
      out(p[i]), space;
    fflush(stdout);
  }
  inline friend Gene Generate();
  inline friend void Sort(Gene *const, Gene *const);
  inline friend void educate();
  inline Gene Variate() const {
    Gene res = *this;
    static int a, b;
    a = random(1, n), b = random(1, n), swap(res.p[a], res.p[b]);
    res.calc();
    return res;
  }
  inline void Educate() {
    Gene _tmp = *this;
    int *p = _tmp.p, sign = 1;
    while (sign) {
      sign = 0;
      for (int x = 1; x <= n; x++)
        for (int y = x + 1; y <= n; y++) {
          i64 rec = _tmp.val;
          if (x <= 3 || x >= n - 2 || y <= 3 || y >= n - 2 || abs(x - y) <= 4)
            swap(p[x], p[y]), _tmp.calc();
          else
            _tmp.erase(x), _tmp.erase(y), swap(p[x], p[y]), _tmp.insert(x), _tmp.insert(y);
          if (_tmp.val > val)
            *this = _tmp;
          (_tmp.val > rec) ? (sign = 1) : (swap(p[x], p[y]), _tmp.val = rec);
        }
    }
  }
} pop[limit + 10], son[limit * 10 + best * 100 + 10], *top, tmp[limit << 1];

inline Gene Generate() {
  Gene res;
  for (int i = 1; i <= n; i++)
    res.p[i] = i;
  shuffle(res.p + 1, res.p + n + 1, rnd);
  res.calc();
  return res;
}
inline void Sort(Gene *const a, Gene *const end) {
  // 这里省略一个极其冗长的基数排序。
}

inline void init() {
  for (int i = 0; i < limit; i++)
    pop[i] = Generate();
  Sort(pop, pop + limit);
}
inline void variate() {
  top = son;
  for (int i = 0; i < limit; i++) {
    int T = i < best ? 100 : 10;
    while (T--)
      *top++ = pop[i].Variate();
  }
  Sort(son, top);
}
inline void educate() {
  for (int i = 0; i < best; i++) {
    Gene _tmp = pop[i];
    int T     = 10;
    while (T--) {
      _tmp.Educate();
      if (_tmp.val > pop[i].val)
        pop[i] = _tmp;
      for (int i = 1, a, b; i <= 20; i++)
        a = random(1, n), b = random(1, n), swap(_tmp.p[a], _tmp.p[b]);
      _tmp.calc();
    }
  }
  Sort(pop, pop + best);
}
inline void Merge() {
  merge(pop, pop + best, son, son + limit, tmp);
  memcpy(pop, tmp, sizeof(Gene) * limit);
}

signed main() {
  // 前面省略一堆文件输入输出和读入啥的。
  init();
  while (1) {
    variate(), educate(), Merge();
    cerr << pop[0].Val() << endl;
    if (pop[0].Val() >= stop) {
      pop[0].Output();
      break;
    }
  }
}
```


---

## 作者：Aventurine_stone (赞：1)

## 1. 题目分析
简单的读完题目，相信经常写模拟退火的人第一想到的就是模拟退火。  
这道题要我们构造的排列，随即交换其中两个数造成的影响也不大，函数具有连续性，可以使用模拟退火。
## 2. 题目做法
先讲一下交换两值时如何快速求出新的排列权值。首先最朴素的思想是交换后从头到尾重新求一遍，这样一次修改时间复杂度便为 $O(n)$。但是经过仔细观察，不难发现交换两个数最多会影响到这两个点及其左右两个点的权值，于是我们便可以将修改操作优化成 $O(1)$ 的，其中注意一下不要重复计算一个点即可。  
更快的修改自然可以允许我们使用更好的参数，但是交上去却只有寥寥几分，我果断放弃用退火交上去直接过的想法。这是一道提交答案题，我们可以将答案在本地跑出来之后再提交，直接得到了 97 分。  
这时在原来的退火上优化已经效果甚微了，我只能手写一个新的枚举，具体是枚举任意两点如果交换后更优则一定交换。当退火跑完一遍，再枚举一遍，直到跑出答案为止，这样便可以得 99 分。  
为什么过不了？因为第三个测试点是一个特殊的构造点，我退火跑了一个晚上都没跑出来。  
具体构造方法，先构造一个初始序列 $1,2,3$，后面的每个数 $x$ 都插入到 $x-1$ 与 $x-2$ 之间，这样可以保证大的数尽量与大的数相乘。  
这样我们便可以完成此题。
## 3. 代码
这里只放退火代码，不放答案代码，大家自己本地算一下就出来了。  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
int n;
long long a[N],p[N],ans1,ans2[N];
long long now,fu;
double T,dt;
inline double rand(double l,double r)
{
	return (double)rand()/RAND_MAX*(r-l)+l;
}
inline long long ask(int i) 
{
	return p[i]*a[p[i-1]]*a[p[i]]*a[p[i+1]];
}
int x,y,xa,xb,ya,yb;
bool m[N];
inline long long change()
{
	if(x==y)
		return now;
	long long s=now;
	xa=x==1?n:x-1,xb=x==n?1:x+1;
	ya=y==1?n:y-1,yb=y==n?1:y+1;
	m[xa]=m[x]=m[xb]=1;
	s-=ask(xa);
	s-=ask(x);
	s-=ask(xb);
	if(!m[ya])s-=ask(ya);
	if(!m[y])s-=ask(y);
	if(!m[yb])s-=ask(yb);
	swap(p[x],p[y]);
	p[0]=p[n],p[n+1]=p[1];
	s+=ask(xa);
	s+=ask(x);
	s+=ask(xb);
	if(!m[ya])s+=ask(ya);
	if(!m[y])s+=ask(y);
	if(!m[yb])s+=ask(yb);
	m[xa]=m[x]=m[xb]=0;
	if(s>ans1)
	{
		ans1=s;
		for(int i=1;i<=n;i++)
			ans2[i]=p[i];
	}
	return s;
}
long long biao=200495008992328;
void SA()
{
	T=1e15;
	while(T>1e-15)
	{
		x=rand()%n+1,y=rand()%n+1;
		fu=change();
		dt=fu-now;
		if(exp(dt/T)>rand(0,1))
			now=fu;
		else
			swap(p[x],p[y]),p[0]=p[n],p[n+1]=p[1];
		T*=0.999996;
	}
}
void SA2()
{
	T=1e15;
	x=y=1;
	while(T>1e-15)
	{
		fu=change();
		dt=fu-now;
		if(exp(dt/T)>rand(0,1))
			now=fu;
		else
			swap(p[x],p[y]),p[0]=p[n],p[n+1]=p[1];
		T*=0.999996;
		y++;
		if(y>n)
		{
			y=1,x++;
			if(x>n)
				x=1;
		}
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),ans2[i]=p[i]=i;
	p[0]=p[n],p[n+1]=p[1];
	for(int i=1;i<=n;i++)
		ans1+=ask(i);
	now=ans1;
	while(ans1<biao)
	{
		SA2();
		SA();
		for(int i=1;i<=n;i++)
			printf("%lld ",ans2[i]);putchar(10);
	}
	for(int i=1;i<=n;i++)
		printf("%lld ",ans2[i]);
	return 0;
}

```

---

## 作者：UncleSam_Died (赞：1)

蒟蒻的第一篇黑题题解。
### 题目描述
[Link](https://www.luogu.com.cn/problem/P7812)
### 解题思路
模拟退火，考虑每次随机交换两个 $p_i$，然后计算当前情况下的排列的权值，如果比当前的最优解要优，那么直接更新即可，同时更新最优排列，否则的话，以一定的概率接受，但是不需要更新最优排列。然后就慢慢跑吧，蒟蒻实测跑 $1$ 分钟可以获得 $95$ 分的好成绩，跑 $5$ 分钟可以获得 $98$ 分的好成绩，再多跑一会儿（指约 $3.2$ 个小时）就过了。

以下是蒟蒻的一些参数（显然单次迭代次数增加比多次迭代次数没有那么多的更好）：
- 初始温度 $10^{20}$；
- 结束温度 $10^{-20}$；
- $\Delta=0.99999997$；
- 只需要跑 $1$ 次模拟退火。
### 注意事项
我们每次在进行模拟退火的时候一定要重新开一个数组记录当前的 $p$，如果找到了一个更优解，那么再把新的数组复制给 $p$，否则可能因为取了一些不是最优解的解从而把最优的排列覆盖掉。
### AC 代码
需要者私信。

---

## 作者：Night_sea_64 (赞：1)

本蒟蒻过的第一道黑。只用了模拟退火。这里就不讲模拟退火算法了。

着重讲一下交换两个元素之后快速更新权值。假设交换了 $x,y$ 两个位置的元素，那么显然 $x-1,x,x+1,y-1,y,y+1$ 的位置值都会发生更新。但是我们直接把这些位置减掉再加上新的，这是不对的。因为这些位置中有可能有重复的位置。比如交换了 $3,5$ 两个位置，$3+1$ 和 $5-1$ 的位置是重复的，此时只能算一次，算两次的话会错。

于是我就记录了一个 $flag$ 数组，表示这个位置是不是发生更新的位置。因为更新的位置很少，所以不要用 memset（这样速度就慢了），记录一份更新的位置具体有哪些，处理完再挨个取消标记就好。

直接交，再优化一下模拟退火的参数，但是怎么也 A 不了（优化得很好的话能拿 $98\sim99$ 分），这样的话，直接复制到洛谷 IDE 上，再将递归次数调多一些，就可以过掉没过的一两个点。然后特判数据点，就把这题~~水~~过了。

```cpp
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
int n,a[1010],p[1010],ans[1010],id[7];
long long maxn,nowans;
bool flag[1010];
long double t=1e11,tend=1e7,k=0.9999985;//模拟退火的参数，调成这样可以拿到 97~99 分
long long calc(int x){
    return(long long)p[x]*a[p[(x==1?n:x-1)]]*a[p[x]]*a[p[(x==n?1:x+1)]];
}
void pre()
{
    srand(time(0));
 	for(int i=1;i<=(n>>1);i++)
      	ans[i]=p[i]=(i<<1);
 	for(int i=(n>>1)+1;i<=n;i++)
      	ans[i]=p[i]=((n-i+1)<<1)-1;
    for(int i=1;i<=n;i++)nowans+=calc(i);
    maxn=nowans;
}
int chg(int x){
    if(x==0)return n;
    if(x==n+1)return 1;
    return x;
}
void SA()
{
    if(t<=tend)return;
    if(nowans>maxn)
    {
        maxn=nowans;
        for(int i=1;i<=n;i++)
            ans[i]=p[i];
    }
    int x=1+rand()%n,y=1+rand()%n;
    long long newans=nowans;
    int cur=0;
    for(int i=-1;i<=1;i++)
    {
        if(!flag[chg(x+i)])
            flag[chg(x+i)]=1,id[++cur]=chg(x+i);
        if(!flag[chg(y+i)])
            flag[chg(y+i)]=1,id[++cur]=chg(y+i);
    }
    for(int i=1;i<=cur;i++)newans-=calc(id[i]);
    swap(p[x],p[y]);
    for(int i=1;i<=cur;i++)newans+=calc(id[i]);
    for(int i=1;i<=cur;i++)flag[id[i]]=0;
    if(newans>nowans)nowans=newans;
    else if(expl((newans-nowans)/t)>rand()*1.0/RAND_MAX)
        nowans=newans;
    else swap(p[x],p[y]);
    t*=k,SA();
}
signed main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    if(n==1000&&a[1]==841)
    {
        cout<<""<<endl;
        return 0;
    }
    if(n==1000&&a[1]==851)
    {
        cout<<""<<endl;
        return 0;
    }
    if(n==1000&&a[1]==824)
    {
        cout<<""<<endl;
        return 0;
    }//以上特判了 8~10 三个点，由于代码太长，所以把特判输出的内容删了
    pre();
    SA();
    for(int i=1;i<=n;i++)printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：_LiWenX_ (赞：0)

谁说退火不能过。

分享一个退火做法，是我和另一个[同学](https://www.luogu.com.cn/user/478461)玩出来的。

首先看完题，又是奇怪的计算贡献方式，又是提交答案，感觉非常像退火，然后让我们把答案跑出来就好。

所以你可以光速写出来一个很基础的退火算法，大概每个点都跑 $100$ 次，降温降快点，你就获得了 $49$ 分，只通过了 $1,2,4,5$ 四个测试点，看了看 $3$，应该是待会留给我特意构造答案的点，先不管。

接下来尝试改变参数，大概调了调，还是无法通过第六个测试点，然后可以干这么一件事：用上一次退火跑出来的东西与答案取最优之后，再用这个答案去跑模拟退火，相当于是迭代答案，然后就通过了第六个点。

第七个点比较困难了，我先进行了这样的操作：先用降温快的参数跑 $100$ 轮，再用降温慢的策略跑下去，加上去的确有用，但是依然无法通过。

然后你发现问题是现在的局面可能进入了一个死胡同，很难使用退火产生更优的局面，于是我们手动更新，直接随机交换 $20$ 组位置，然后继续退火，通过调参，直接通过测试点 $7,8,9,10$！而且貌似如果我继续跑下去答案还会更大/qiang。

至于第三个点，直接猜测结论，把 $1000$ 放到 $1000$ 的位置上，左右轮流填下去即可，大概会有一个形如 $...996,998,1000,999,997...$ 的局面。

跑出来刚好摸到了答案，然后过了。

放一下跑出来第十个点的程序：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[100005],n;
ll s=0;
int p[100005];
ll ans,Ans[100005];
int le[100005],re[100005],cnt; 
ll suan(int x){
	return 1ll*p[x]*a[p[x]]*a[p[le[x]]]*a[p[re[x]]];
}
mt19937 rd(time(NULL));
uniform_real_distribution<double>gen(0,1);
double P(){
	return gen(rd);
}
void solve(){
	double tm=cnt<=100?1e3:1e5;
	for(int i=1;i<=n;i++){
		p[i]=Ans[i];
	}
	if(cnt>100)
		for(int i=1;i<=5;i++){
			swap(p[rd()%n+1],p[rd()%n+1]);
		}
	s=0;
	for(int i=1;i<=n;i++){
		s+=suan(i);
	}
	while(tm>(cnt<=100?1e-3:1e-5)){
		int x,y;
		x=rd()%n+1;y=rd()%n+1;
		while(x==y){
			x=rd()%n+1;
			y=rd()%n+1;
		}
		vector<int> S;
		S.push_back(le[x]);
		S.push_back(x);
		S.push_back(re[x]);
		S.push_back(le[y]);
		S.push_back(y);
		S.push_back(re[y]);
		#define all(S) (S).begin(), (S).end()
		sort(all(S)),S.erase(unique(all(S)),S.end());
		ll nxt=s;
		for(int u:S) nxt-=suan(u);
		swap(p[x],p[y]);
		for(int u:S) nxt+=suan(u);
		if(exp((nxt-s)/tm)<P()){
			swap(p[x],p[y]);
		}
		else s=nxt;
		tm=tm*(cnt<=100?0.9999:0.99999);
	}
}
signed main(){
	freopen("10.in","r",stdin);
	freopen("10.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		le[i]=i-1;
		re[i]=i+1;
		if(i==1) le[i]=n;
		if(i==n) re[i]=1;
		Ans[i]=i;
	}
	p[1000]=1000;
	int r=le[1000],l=re[1000];
	int num=999;
	while(!p[l]&&!p[r]){
		p[r]=num;num--;
		r=le[r];
		
		if(p[r]) break;
		p[r]=num;num--;
		r=le[r];
		
		p[l]=num;num--;
		l=re[l];
		
	}
	while(ans<200495008992328){
		solve();
		if(s>ans){
			ans=s;
			for(int j=1;j<=n;j++){
				Ans[j]=p[j];
			}
		}
		++cnt;
		if(cnt%5==0){
			cerr<<ans<<'\n';
		}
	}
	cerr<<ans<<'\n';
	for(int i=1;i<=n;i++){
		cout<<Ans[i]<<' ';
		p[i]=Ans[i];
	}
} 
```

---

## 作者：JustPureH2O (赞：0)

[更好的阅读体验](https://justpureh2o.cn/articles/27039)

题目地址：[P7812](https://www.luogu.com.cn/problem/P7812)

> **本题为提交答案题**
>
> 给你一个长为 $n$ 的序列 $a$，定义 $1\dots n$ 的排列 $p$ 的权值为：
>
> $\sum_{i=1}^n p_i a_{p_{i-1}} a_{p_i}a_{p_{i+1}}$
>
> 并且 $p_{0}=p_n,p_{n+1}=p_1$。请构造一个权值**尽量大**的 $1\dots n$ 的排列。

提交答案题？直接打表！

首先我们需要明确如何才能构造出一个符合题意的排列，暴力枚举的复杂度是 $\mathcal O(n!)$ 的，显然是不可取的做法。因此我们考虑随机化做法。 

## 测试点 1\~2

提到随机化，我们有模拟退火。先随机一个 $1\sim n$ 的排列，再任意交换若干元素并与先前的序列权值进行比较，若更优则直接采纳，否则就依据 $\texttt{Metropolis}$ 准则概率接受，其余情况则恢复原状。

在本地跑没有时限，可以把参数调精一点。

```cpp
#include <bits/stdc++.h>
#define N 1010
#define PRINT_TABLE
using namespace std;

typedef long long ll;

int n;
ll a[N], p[N], q[N];
random_device rd;
ll ans = 0;

double rand(double l, double r) {
    return (double) rd() / random_device::max() * (r - l) + l;
}

int rand(int l, int r) {
    return (int) (rd() % (r - l + 1)) + l;
}

ll calc() {
    // 计算权值
    ll sum = p[1] * a[p[n]] * a[p[1]] * a[p[2]];
    for (int i = 2; i < n; i++) sum += p[i] * a[p[i - 1]] * a[p[i]] * a[p[i + 1]];
    sum += p[n] * a[p[n - 1]] * a[p[n]] * a[p[1]];
    return sum;
}

void SA() {
    double T = 1e10;
    ans = max(ans, calc());
    while (T > 1e-17) {
        int a = rand(1, n), b = rand(1, n);
        swap(p[a], p[b]);
        ll now = calc();
        long double delta = now - ans;
        if (delta > 0) {
            memcpy(q, p, sizeof p);
            ans = now;
        } else if (exp(delta / T) <= (double) rd() / random_device::max()) swap(p[a], p[b]);
        T *= 0.99996;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // Test Point #1 #2
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) p[i] = i;
    shuffle(p + 1, p + 1 + n, mt19937(rd()));
    SA();
    clog << ans << endl;
// 打表格式化
#ifdef PRINT_TABLE
    cout << '{';
    for (int i = 1; i < n; i++) cout << q[i] << ", ";
    cout << q[n] << "},\n";
#else
    for (int i = 1; i <= n; i++) cout << q[i] << ' ';
#endif
    return 0;
}
```

一般来说一秒之内可以出答案。

## 测试点 3

测试点 $3$ 的数据很有意思，它是一个单调递增的排列。模拟退火跑了很久，得出的排列有两头大、中间小的特征。于是大胆构造一个特解——从左至右奇数递减、从右至左偶数递减。

## 测试点 4\~10

模拟退火调了半天参数就是过不去……同机房的大佬好像用加强版的模拟退火跑了几天才跑过？这里推荐一个叫“遗传算法”的解决方案。

---

遗传算法能通过模拟生物繁衍、自然选择等自然现象来实现求解全局最优解的功能。具体是让当前的优解进行变换，期望能得到一个更优的解。

```cpp
#include <bits/stdc++.h>
#define N 1010
#define PRINT_TABLE
#define LIMIT 141473199965824ll // 每个测试点的最大值

#pragma optimize(3)

using namespace std;

typedef long long ll;

int n;
ll ans = 0, submax = 0;
random_device rd;
ll a[N], p[N], q[N], id[N];

ll calc(const ll arr[] = p) {
    ll sum = arr[1] * a[arr[n]] * a[arr[1]] * a[arr[2]];
    for (int i = 2; i < n; i++) sum += arr[i] * a[arr[i - 1]] * a[arr[i]] * a[arr[i + 1]];
    sum += arr[n] * a[arr[n - 1]] * a[arr[n]] * a[arr[1]];
    return sum;
}

ll d(int pos1, int pos2) {
    // 处理交换前后的变化量
    ll sum = 0;
    sum -= p[pos1] * a[p[pos1 - 1]] * a[p[pos1]] * a[p[pos1 + 1]] + p[pos1 + 1] * a[p[pos1]] * a[p[pos1 + 1]] * a[p[pos1 + 2]] + p[pos1 - 1] * a[p[pos1 - 2]] * a[p[pos1 - 1]] * a[p[pos1]];
    sum -= p[pos2] * a[p[pos2 - 1]] * a[p[pos2]] * a[p[pos2 + 1]] + p[pos2 + 1] * a[p[pos2]] * a[p[pos2 + 1]] * a[p[pos2 + 2]] + p[pos2 - 1] * a[p[pos2 - 2]] * a[p[pos2 - 1]] * a[p[pos2]];
    swap(p[pos1], p[pos2]);
    sum += p[pos1] * a[p[pos1 - 1]] * a[p[pos1]] * a[p[pos1 + 1]] + p[pos1 + 1] * a[p[pos1]] * a[p[pos1 + 1]] * a[p[pos1 + 2]] + p[pos1 - 1] * a[p[pos1 - 2]] * a[p[pos1 - 1]] * a[p[pos1]];
    sum += p[pos2] * a[p[pos2 - 1]] * a[p[pos2]] * a[p[pos2 + 1]] + p[pos2 + 1] * a[p[pos2]] * a[p[pos2 + 1]] * a[p[pos2 + 2]] + p[pos2 - 1] * a[p[pos2 - 2]] * a[p[pos2 - 1]] * a[p[pos2]];
    return sum;
}

int rand(int l, int r) {
    return (int) (rd() % (r - l + 1)) + l;
}

void GA() {
    while (ans < LIMIT) {
        for (int i = 1; i <= 20; i++) {
            int a = rand(1, n), b = rand(1, n);
            swap(p[a], p[b]);
        }
        submax = calc(); // 当前值
        shuffle(id + 1, id + 1 + n, mt19937(rd())); // 每次打乱枚举顺序
        bool flag;
        do { // 还能变得更优就继续下去
            flag = false;
            #pragma unroll 20
            for (int i = 1; i < n; i++) {
                for (int j = i + 1; j <= n; j++) {
                    ll cur;
                    int pos1 = id[i], pos2 = id[j];
                    if (abs(pos2 - pos1) <= 5 || abs(pos2 - pos1) >= n - 5) {
                        swap(p[pos1], p[pos2]);
                        cur = calc();
                    } else {
                        cur = submax + d(pos1, pos2);
                    }
                    if (cur > ans) {
                        ans = submax = cur;
                        memcpy(q, p, sizeof p);
                        if (ans > (ll) (LIMIT * 0.999)) cerr << ans << endl;
                        flag = true;
                        if (ans >= LIMIT) return;
                    } else if (cur > submax) {
                        submax = cur;
                        flag = true;
                    } else swap(p[pos1], p[pos2]);
                }
            }
        } while (flag);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // Test Point #4 #5 #6 #7 #8 #9
    freopen("9.in", "r", stdin);
    freopen("9.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) p[i] = i, id[i] = i;
    GA();
    clog << "Final Answer: " << calc(q) << " Overloaded: " << calc(q) - LIMIT << endl;
#ifdef PRINT_TABLE
    cout << '{';
    for (int i = 1; i < n; i++) cout << q[i] << ", ";
    cout << q[n] << "}\n";
#else
    for (int i = 1; i <= n; i++) cout << q[i] << ' ';
#endif
    return 0;
}
```

跑得稍久一些，但是还是比较快的。

$\texttt{The End}$

---

## 作者：WorldMachine (赞：0)

神仙题。膜拜交代码过的神仙。

首先写了个 `random_shuffle`，发现这特别没前途第二个点都过不去，扬了。

发现这个的问题在于太随机了，完全没有最优化。考虑每次随机一对数，交换后更优就换。

然后发现这玩意样例过不去，因为我们这个只能得到局部最优解。

所以不能交换之后我们就将排列打乱一下继续跑，这玩意还可以。但远远没达到期望分数。

发现这个的问题在于太随机了，考虑直接把所有的数对枚举一遍看能不能换。

这玩意还不错，除了 $\#3,\#9,\#10$ 以外的点都能在 $20\text{s}$ 左右得到 $10$ 分解，$\#9,\#10$ 这两个点也能在 $40\text{s}$ 左右得到 $10$ 分解。（本地电脑比较辣鸡）

但是第三个点非常折磨，至少我跑了 $12\text{min}$ 也没跑出 $10$ 分解。

本来我都打算跑一晚上的，打开输入文件一看，发现它就是一个 $1\sim 1000$ 按照顺序的排列。而 $10$ 分的标准比 $9$ 分高那么高一看就是要让你找结论。

发现跑出来的解大概就是两边大中间小，构造一下就可以过掉。

然后就愉快地 A 掉这道题啦。o(\*￣▽￣\*)ブ

代码非常好写就不放了。

---

