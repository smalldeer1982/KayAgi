# Circle of Monsters

## 题目描述

You are playing another computer game, and now you have to slay $ n $ monsters. These monsters are standing in a circle, numbered clockwise from $ 1 $ to $ n $ . Initially, the $ i $ -th monster has $ a_i $ health.

You may shoot the monsters to kill them. Each shot requires exactly one bullet and decreases the health of the targeted monster by $ 1 $ (deals $ 1 $ damage to it). Furthermore, when the health of some monster $ i $ becomes $ 0 $ or less than $ 0 $ , it dies and explodes, dealing $ b_i $ damage to the next monster (monster $ i + 1 $ , if $ i < n $ , or monster $ 1 $ , if $ i = n $ ). If the next monster is already dead, then nothing happens. If the explosion kills the next monster, it explodes too, damaging the monster after it and possibly triggering another explosion, and so on.

You have to calculate the minimum number of bullets you have to fire to kill all $ n $ monsters in the circle.

## 样例 #1

### 输入

```
1
3
7 15
2 14
5 3```

### 输出

```
6```

# 题解

## 作者：rouxQ (赞：17)

## 题意简述
有 $n$ 头怪兽，第 $i$ 头怪兽有 $a_i$ 滴血，被打死了会把第 $(i\mod n) + 1$ 头怪兽炸掉 $b_i$ 滴血，你一次能选择一头怪兽打 $1$ 滴血，问最少多少次能把怪兽打完，多组数据。
## $\operatorname{solution}$
首先发现打死某一头怪兽有两种方法：1.直接打死 2.先打死前面一头，把怪兽炸残（或者直接炸死）再打死。

可以关注到显然第二种会更优，但是肯定要**选择一头怪兽用第一种方案打死，再不断推进用第二种方式打死全部怪兽**，所以我们设 $c_i$ 表示第 $i$ 头怪兽被炸之后还剩的血量，有 $c_i = \max (0, a_i - b_{i-1})$，特别的 $c_1=\max(0, a_1-b_n)$，然后枚举那个唯一的使用第一种方案打死的怪兽，找到最小的方案就行。


## $\operatorname{code}$
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll a[300001], b[300001], c[300001];
int main (){
    int T;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)scanf("%lld%lld", &a[i], &b[i]);
        for (int i = 2; i <= n; i++)c[i] = max(0ll, a[i] - b[i - 1]);
        c[1] = max(0ll, a[1] - b[n]);
        //事实上这个c数组可以不用定义，但是看着明白一点就保留了
        ll sum = 0, Min = 9e18;
        for (int i = 1; i <= n; i++)sum += c[i];
        for (int i = 1; i <= n; i++)Min = min(Min, sum - c[i] + a[i]);//打擂台找到最小值
        printf("%lld\n", Min);
    }
    return 0;
}
```

---

## 作者：FCBM71 (赞：5)

一道比较裸的贪心，读者自证不难。

## 策略

对于每个怪兽，你要想使他的血量衰减，只有两种途径：

- 靠你的小手枪每次扣它一滴血
- 靠上一个怪兽爆炸对其造成大量伤害

**怪兽的血量是恒定的，为了最小化你的小手枪的伤害，就要最大化爆炸的伤害**。

怎么最大化呢？**能炸死就直接炸死，不能炸死就把它打残血到刚刚好能被炸死。**

假设当前怪兽血量为 $a$，上一个怪兽爆炸伤害为 $b$  
如果 $a\leq b$，则他可以被一次性炸死。  
如果 $a>b$，上一个怪兽炸不死它，而它剩下的血量必须要你用小手枪打。所以你**至少**要对它先打 $b-a$ 次小手枪。

可能有点难以理解，我们来模拟一下过程：  
对于样例，二三号都可以直接被炸死，暂时不用管，一号不能被直接炸死，故需要先对它打三枪，使他的血量降为3才能被直接炸死。

$$\begin{bmatrix}\color{red}7,\color{black}15\cr 2,14\cr 5,\color{green}3 \end{bmatrix}\rightarrow\begin{bmatrix}\color{red}3,\color{black}15\cr 2,14\cr 5,\color{green}3\end{bmatrix}$$

这样处理的目的是什么？我们现在就得到了一个环，因为每一个怪兽的血量都足够低以致于可以被上一个怪兽炸死，所以只要我们**打死任何一个怪兽**，其他所有的怪兽都会**连环爆炸**，然后游戏直接结束。 ~~读者可以想象一下场面之壮观~~ 我们可以直接从当前所有怪兽中选择**剩余血量最少**的一个，干掉他，然后所有怪兽都可以被炸死了。

## 代码

由于自己加了一堆预处理，所以就只贴出核心代码了。代码中**省略了多组数据的最外层循环**

```
scanf("%d",&n);
for(int i=1;i<=n;++i) scanf("%lld%lld",&a[i],&b[i]);
LL ans=0, minn;  //ans表示把所有怪兽的血量打到上一个怪兽爆炸范围内需要打多少枪，minn表示怪兽剩余血量中的最小值
if(a[1]>b[n]) ans=a[1]-b[n], a[1]=b[n]; //特判一号怪兽
minn=a[1];
for(int i=2;i<=n;++i){
	if(a[i]>b[i-1]){  
		 if(a[i]>b[i-1]) ans+=a[i]-b[i-1]; //如果上一个怪兽炸不死它，就先打到上一个怪兽的爆炸范围内
		 a[i]=b[i-1];
	}
	if(a[i]<minn) minn=a[i];  //更新最小值
}
printf("%lld\n",ans+minn);
```



---

## 作者：Blunt_Feeling (赞：4)

# CF1334C Circle of Monsters 题解
这是一道贪心的题目。怪兽们围成一个圈，那么很容易就能想到可以开长度为 $2n$ 的数组，把数据按照 $1$~$n$ 的顺序存两遍来处理。

我们要求的是把怪兽都炸掉所用的最小子弹数，那肯定有一个起点和一个终点。设终点的位置为 $i(n\leq i\leq 2n)$ ，那么起点的位置就为 $i$-$n$+$1$ 。**接下来是重点：** 求出 $1$ 到每个点所需的最小子弹数，用 $f_i$ 表示。再在 $n$~$2n$ 中找到一个最佳的终点 $p$ ，使得 $f_p-f_{p-n+1}$ 最小，这个最小值就是最终的答案。这两步操作可以在同一个 for 循环里完成。

由于这题的数据不怎么水（抑或是我的算法时间复杂度太高），我用了快读才AC。[TLE记录](https://www.luogu.com.cn/record/32663563)。以下是加了快读的AC代码，每组测试数据的时间复杂度为 $O(n)$ 。
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
const int maxn=300050;
inline long long read() { //long long类型的快读
    char c=getchar();long long x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x; return x;
}
int T,n;
long long a[maxn*2],b[maxn*2],f[maxn*2],ans;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		For(i,1,n)
		{
			a[i]=read(); b[i]=read();
			a[i+n]=a[i],b[i+n]=b[i]; //相当于存了两遍
		}
		ans=LLONG_MAX; //这里我本来写的是LONG_LONG_MAX，结果CE了。看来codeforces只支持LLONG_MAX的写法
		For(i,2,n*2)
		{
			f[i]=f[i-1];
			if(b[i-1]<a[i]) f[i]+=a[i]-b[i-1];//前一只怪兽的爆炸值不够杀死这只怪兽时，子弹数加上剩余的血量
			if(i>=n) ans=min(a[i-n+1]+f[i]-f[i-n+1],ans); //i可以作为终点时
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：gyh20 (赞：2)

贪心。

听说这道题卡 cin，快读选手表示不管。

首先，如果 $b_i>a_{i+1}$，可以理解为，多的那一些伤害被溢出了，没有用，将 $b_i$ 设为 $a_{i+1}$ 即可。

我们发现，如果我们干掉某一个怪物，那么他之前的怪物的 $b_i$ 就浪费了，所以我们只需要找出 $b_i$ 最小的并从它的下一个开始打就行了，沿着环扫一遍就是答案。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,a[600002],ans,b[600002],pos;
signed main(){
	t=read();
	while(t--){
		n=read();
		for(re int i=1;i<=n;++i)a[i]=a[i+n]=read(),b[i]=b[i+n]=read();
		b[n+1]=b[1];a[n+1]=a[1];pos=0;re int mn=1e18,ans=0;
		for(re int i=1;i<=n*2-1;++i){
			if(b[i]>a[i+1])b[i]=a[i+1];
			if(b[i]<mn){
				mn=b[i];
				pos=i+1;
			}
		}
		for(re int i=pos;i<pos+n;++i){
			ans+=a[i];a[i+1]-=b[i];
		}
		printf("%lld\n",ans);
	}
}
```


---

## 作者：SmileMask (赞：1)

# 题解

可能大家一上来看到这个题有些蒙，不知道怎么去贪心。
首先，我们必须先打死 $1$ 个怪兽，才能让他对 $i+1$ 个怪兽造成伤害，我们可以先考虑枚举先打死的那个怪兽，那接下来怎么办呢？

我们可以预处理出一个数组 $c_i$，这个数代表着第 $i-1$ 个怪兽死后，爆炸后第 $i$ 个怪兽剩余的血量，为 $c_i=\max(a_i-b_{i-1},0)$。

接下来就好办了，我们先算出每个怪兽被炸后剩余的血量。

$$sum=\sum_{i=1}^{n} c_i $$

然后枚举第一个被打死的怪兽 $i$。

$$ans=\max_{i=1}^{n}({{sum-c_i+a_i})}$$

$sum-c_i$ 表示除了 $i$ 以外其他怪兽被炸后剩余的血量，在加上第一个被打死的怪兽 $a_i$ 的血量，就可得出要打多少伤害了。

# code

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n;
ll a[300010],b[300010],c[300010];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld %lld",&a[i],&b[i]);
		}
		for(int i=1;i<=n;i++){
			if(i==1) c[i]=max(0ll,a[1]-b[n]);
			else c[i]=max(0ll,a[i]-b[i-1]);
		}
		ll sum=0;
		for(int i=1;i<=n;i++) sum+=c[i];
		ll ans=1e18;
		for(int i=1;i<=n;i++) ans=min(ans,sum-c[i]+a[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：LYF926 (赞：1)

### 一、题意

$n$ 只怪兽围成一个环，由 $1$ 到 $n$，第 $i$ 只怪兽有 $a_i$ 点血量，死掉之后会对下一只怪兽造成 $b_i$ 点伤害。

### 二、思路

不难发现，这头怪兽的死法很简单，要么被子弹打死，要么直接炸死。

直接炸死的话，消耗的子弹肯定是更少的。

所以我们贪心地认为：被炸死的怪兽多多益善！

由于肯定至少有一只是被子弹打死的，那么接下来只要找到让哪一只完全是被被子弹打死的最优即可。

### 三、代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[300005],b[300005];
int main()
{
	int q;
	cin>>q;
	while(q--)//多测
	{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld %lld",&a[i],&b[i]);//输入a[i],b[i]
		long long ans=0,mn;
	for(int i=1;i<=n-1;i++)
	{
		ans+=max(0ll,a[i+1]-b[i]);//下一只如果是先打残再炸死需要的子弹
		a[i+1]=min(a[i+1],b[i]);//打残后剩余血量
	}
	ans+=max(0ll,a[1]-b[n]);//注意是个环
	a[1]=min(a[1],b[n]);//处理和循环内一样的
	mn=a[1];
	for(int i=1;i<=n;i++)
	mn=min(mn,a[i]);//找到最小的一个干掉，然后剩下都残了，上一个死了下一个直接炸死
	cout<<ans+mn<<endl;
}
	return 0;
}
```

---

## 作者：AutumnKite (赞：1)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

### 题解

为方便描述，下文中 $i+1$ 表示环上 $i$ 的下一个怪物，$i-1$ 表示环上 $i$ 的上一个怪物。

首先我们将 $b_i$ 与 $a_{i+1}$ 取 $\min$，这显然不会影响答案。

对于一个怪物 $i$，打败他至少需要的操作次数为 $a_i-b_{i-1}$，即打 $a_i-b_{i-1}$ 枪，剩下的血量用上一个怪物炸。

那么总的操作次数的下界即为 $\sum\limits_{i=1}^{n} a_i-b_{i-1}$。

但是这是一个环形，我们不可能做到每个怪物都被上一个怪物炸，必须有一个怪物是手动打死的。

而在之前的操作次数下界的基础上，手动打死怪物 $i$ 需要花费额外的 $b_i$ 次操作，所以我们只要选择 $b_i$ 最小的那个怪物手动打死即可。

总花费即为 $\min\limits_{1\le i\le n} b_i+\sum\limits_{i=1}^{n} a_i-b_{i-1}$。

### 代码

```cpp
const int N = 300005;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n;
long long a[N], b[N];

void solve() {
	read(n);
	long long sum = 0, mn = INF;
	for (int i = 1; i <= n; ++i) {
		read(a[i]), read(b[i]);
		sum += a[i];
	}
	for (int i = 1; i <= n; ++i) {
		b[i] = std::min(b[i], a[i % n + 1]);
		mn = std::min(mn, b[i]);
		sum -= b[i];
	}
	print(sum + mn);
}
```

---

## 作者：寒鸽儿 (赞：0)

关键在于考虑尽量利用 $b_i$ 。  

一个怪 $i$ 如果对后面一个产生爆炸伤害 , 就节省 $c_i = \min \{b_i , a_{(i+1)\%n}\}$ 。  

如果是在一条链上 , 显然从头部打到尾部 , 就能充分利用 $c_i$ 。  

在一个环上 , 我们首先打掉一个怪 $i$ ， 那么怪 $i-1 \mod n$ 对答案的贡献 $c_{i-1 \mod n}$ 就不能计在内了 , 因此考虑找出最小的 $c_i$  , 舍去其爆炸伤害的贡献。  

```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define per(i,a,b) for(int i=a;i>=(b);--i)
#define repp(i,a,b) for(int i=a;i<(b);++i)
#define perr(i,a,b) for(int i=a;i>(b);--i)
#define pb push_back
#define rz resize
#define VI vector<int>
#define VL vector<long long>
#define VD vector<double>

using namespace std;

typedef long long ll;


const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3f;

VL a, b;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tests;
	cin>>tests;
	while(tests--) {
		int n;
		ll ans = 0, reg = linf;
		cin >> n;
		a.resize(n + 2);
		b.resize(n + 2);
		rep(i,1,n) cin >> a[i] >> b[i], ans += a[i];
		rep(i,1,n) {
			ans -= min(b[i], a[i%n+1]);
			reg = min(reg, min(b[i], a[i%n+1]));
		}
		ans += reg;
		cout << ans << endl;
	}

	return 0;
}
```

---

## 作者：oimaster (赞：0)

这一道题我昨天晚上做了很久，不过最后居然 AC 了。

## 题面
### 英文题面
为什么要给呢，直接去 [这里](https://codeforces.com/contest/1334/problem/C) 就好了啊。
### 中文题面
有 $N$ 头凶猛的怪兽，他们围成一个圈圈，顺时针编号 $1, 2, 3, 4, \dots , N$ 每一头怪兽都有 $2$ 个属性——一个是它的生命值，第二个是它的爆炸值。爆炸会发生在它生命值小于等于 $0$，就是说他死掉的时候，它的下一头怪兽会遭到 它的爆炸值 点伤害。如果下一头怪兽已经死了，则无伤害。如果这回又把下一头怪兽给弄死了，那么下一头怪兽也会爆炸，连环炸到下下头怪兽……你还有一把枪，每发子弹可以伤害一头怪兽的生命值 $1$ 点。问你，把怪兽都炸掉，要用多少子弹。
## 思路
我们知道，打掉怪兽有 $2$ 种可能。第一种，就是专门拿枪一发一发地打它，一种是先打 这个怪兽的生命值-上个怪兽的爆炸值 发，也就是说，最后让上一个怪兽把它爆掉。我们发现，不管怎么打， “这个怪兽的生命值-上个怪兽的爆炸值 发”肯定是要的，于是我们先打这么多发。

这时候，又出现了一个情况。我们发现，在怪兽中间，出现了一个“环”，只要有一个怪兽死了，大家都会被连环炸掉。所以，我们只需要打死现在生命值最小的怪兽即可。
## 代码
请在 [这里](https://oi-master.github.io/post/codeforces-contest-1134-c-ti-jie/) 查看。

---

