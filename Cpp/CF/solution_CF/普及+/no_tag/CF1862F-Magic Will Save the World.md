# Magic Will Save the World

## 题目描述

A portal of dark forces has opened at the border of worlds, and now the whole world is under a terrible threat. To close the portal and save the world, you need to defeat $ n $ monsters that emerge from the portal one after another.

Only the sorceress Vika can handle this. She possesses two magical powers — water magic and fire magic. In one second, Vika can generate $ w $ units of water mana and $ f $ units of fire mana. She will need mana to cast spells. Initially Vika have $ 0 $ units of water mana and $ 0 $ units of fire mana.

Each of the $ n $ monsters that emerge from the portal has its own strength, expressed as a positive integer. To defeat the $ i $ -th monster with strength $ s_i $ , Vika needs to cast a water spell or a fire spell of at least the same strength. In other words, Vika can spend at least $ s_i $ units of water mana on a water spell, or at least $ s_i $ units of fire mana on a fire spell.

Vika can create and cast spells instantly. Vika can cast an unlimited number of spells every second as long she has enough mana for that.

The sorceress wants to save the world as quickly as possible, so tell her how much time she will need.

## 说明/提示

In the first sample, after the first second, Vika can spend $ 2 $ units of fire mana to kill the first monster. Then she has $ 2 $ units of water mana and $ 1 $ unit of fire mana. After the third second, she will have $ 6 $ units of water mana and $ 7 $ units of fire mana at her disposal. This will be enough to immediately kill the second and third monsters.

## 样例 #1

### 输入

```
4
2 3
3
2 6 7
37 58
1
93
190 90
2
23 97
13 4
4
10 10 2 45```

### 输出

```
3
2
1
5```

# 题解

## 作者：ax_by_c (赞：13)

# 题意描述

有若干怪物，都有自己的血量。

巫师有 $2$ 种能量，可以释放 $2$ 种魔法。

然后巫师每秒钟会获得若干的第一种能量和若干的第二种能量。

如果施法就会耗费若干能量，然后对怪物造成等量的伤害。

但是一个怪物自始至终只能受到一种魔法的伤害。

每秒钟巫师可以选择是否施法，请问至少几秒能让巫师击败怪物？

# 解题思路

首先，如果巫师先攒能量，最后再使用，完全是可行的。

那么如果巫师希望用第一种魔法击败血量总和为 $A$ 的怪物，用第二种魔法击败血量总和为 $B$ 的怪物，每秒获得的第一种能量为 $wa$，每秒获得的第二种能量为 $wb$，则时间应为 $\max(\lceil A/wa \rceil , \lceil B/wb \rceil)$。

所以就是用 DP 来维护所有可能的 $A$，根据减法算出 $B$，然后计算最小值。

核心代码：

```cpp
int n,m;
int a[N];
int wa,wb;
bool f[M];
int calc(int sa,int sb)
{
	return max(ceil(double(sa)/double(wa)),ceil(double(sb)/double(wb)));
}
void solve()
{
	cin>>wa>>wb;
	cin>>n;
	m=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		m+=a[i];
	}
	f[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=a[i];j--)
		{
			f[j]|=f[j-a[i]];
		}
	}
	int ans=min(calc(0,m),calc(m,0));
	for(int i=1;i<m;i++)
	{
		if(f[i])
		{
			ans=min(ans,calc(i,m-i));
		}
	}
	for(int i=0;i<=m;i++)
	{
		f[i]=0;
	}
	cout<<ans<<'\n';
}
```

---

## 作者：WrongAnswer_90 (赞：8)

bitset 优化可行性 DP。

注意到所有怪物需要魔法的和是一定的，问题转为判定是否能够恰好消耗 $i$ 点水魔法和 $sum-i$ 点火魔法，用 $f_i$ 表示这种分割方案是否可行，直接 dp 大概率会超时，使用 bitset 优化即可，最后根据 $f_i$ 统计答案。

代码：

```cpp
int T,A,B,n,minn,sum;
inline void mian()
{
	read(T);int x;
	while(T--)
	{
		read(A,B,n),sum=0,minn=INF;
		bitset<1000001> f;f[0]=1;
		while(n--)read(x),f|=(f<<x),sum+=x;
		for(int i=0;i<=1000000;++i)if(f[i])minn=min(minn,max((i-1)/A+1,(sum-i-1)/B+1));
		write(minn,'\n');
	}
}

```

---

## 作者：信息向阳花木 (赞：4)

好不容易做出来 F，结果还差 $2$ 分钟没交上。。。

方法没有楼上大佬高级，我用的就是二分和背包。直接二分时间，然后以一个元素作为背包体积，跑一遍 01 背包，算出另外一个元素最多有多少，最后判断一下即可。

有一个小小的剪枝，那就是任何一个元素超过怪物能量总和，就直接返回可以。

代码中用的是 `bool` 类型的 dp，$f_i = 1$ 表示可以释放 $i$ 个水魔法。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int N = 2000010;

int t, a, b, n, sum;
int s[N];
bool f[N];

bool check(int x)
{
	memset(f, 0, sizeof f);
	
	if(1ll * a * x >= 1ll * sum || 1ll * b * x >= 1ll * sum) return 1;
	
	f[0] = 1;
	for (int i = 1; i <= n; i ++ )
        for (int j = (int)min(1ll * sum, 1ll * a * x); j >= s[i]; j -- )
            f[j] |= f[j - s[i]];
    
    for (int i = 0; i <= sum; i ++ )
    	if(f[i] && sum - i <= b * x) return 1;
    	
    return 0;
}

int main()
{
	scanf("%d", &t);
	while (t -- )
	{
		scanf("%d%d%d", &a, &b, &n); sum = 0;
		for (int i = 1; i <= n; i ++ ) { scanf("%d", &s[i]); sum += s[i]; }
		                                                            
		int l = 0, r = sum;
		while ( l <= r)
		{
			int mid = l + r >> 1;
			if(check(mid)) r = mid - 1;
			else l = mid + 1;
		}
		printf("%d\n", l);
	}
}
```

---

## 作者：Special_Tony (赞：4)

[洛谷传送门](/problem/CF1862F) & [CF 传送门](//codeforces.com/problemset/problem/1862/F)
# 思路
这题我们可以把能量攒起来，最后把怪物一起打死。设怪物总血量为 $sum$，把能量和为 $x$ 的怪物都用冰打死，需要耗费 $\lceil\frac xw\rceil$ 的时间；把剩下的怪物（能量和为 $sum-x$ 的怪物）都用火打死，需要耗费 $\lceil\frac{sum-x}f\rceil$ 时间。所以我们把能量和为 $x$ 的怪物都用冰打死，剩下的用火打死，总共要耗费 $\max(\lceil\frac xw\rceil,\lceil\frac{sum-x}f\rceil)$ 的时间。我们只要枚举每个可能的 $x$ 即可。

枚举每个可行的 $x$，我们可以用背包问题解决。当然，为了优化常数你也可以用 [bitset](//oi-wiki.org/lang/csl/bitset) 进行优化。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, w, f, minx, a[105], sum, n;
bitset <1000005> dp;
int main () {
	cin >> t;
	while (t --) {
		cin >> w >> f >> n;
		sum = 0, minx = 1e9; //多组数据要清零
		dp.reset (); //多组数据要清空
		dp.set (0, 1); //多组数据要初始化
		for (int i = 0; i < n; ++ i)
			cin >> a[i], sum += a[i], dp |= dp << a[i]; //bitset 多方便啊
		for (int i = 0; i <= sum; ++ i)
			if (dp[i])
				minx = min (minx, max ((i + w - 1) / w, (sum - i + f - 1) / f));
		cout << minx << '\n';
	}
	return 0;
}
```

---

## 作者：ChenZQ (赞：3)

直接动态规划，然后使用 `bitset` 优化就好了。

`bitset` 是用来储存多位二进制数的东西。定义 `bitset` 里面填的数就是代表了这个二进制数是多少位。

想了解得更深入看[这篇文章](https://blog.csdn.net/qq_44872284/article/details/116741628)。

```
#include <bits/stdc++.h>
using namespace std;
const int inf = 100000000;
int __,n,minn,sum;
int main()
{
	scanf("%d",&__);
	int x;
	while(__--)
	{
		int a,b;
	    scanf("%d%d%d",&a,&b,&n);
		sum=0,minn=inf;
		bitset<1000000> f;//定义。
		f[0]=1;
		while(n--)scanf("%d",&x),f|=(f<<x),sum+=x;
		for(int i=0;i<=1000000;++i)if(f[i])minn=min(minn,max((i-1)/a+1,(sum-i-1)/b+1));//动态规划。
		printf("%d\n",minn);
	}
}

```

---

## 作者：Windy_Hill (赞：1)

## 题意
有 $n$ 个怪物，Vika 有两种魔法，第一种魔法每秒恢复   $w$ 点，第二种魔法每秒恢复 $f$ 点，对于第 $i$ 个怪物，它有 $s_i$ 点血，每次 Vika 可以用 **一种魔法** 打死一个怪物，打死后怪物就没了，同时这种魔法会被消耗 $s_i$ 点，Vika 问你至少要用多少秒才可以打死所有怪物。

## 思路
由于 $1 \le s_i \le 10^4$ 且 $1 \le n \le 100$，则我们可以用 dp 预处理出来怪物血量和的可能值，然后用一种魔法打死这堆怪物，剩下的怪物用另一种魔法打死，这里可以二分枚举答案，时间复杂度 $n\sum_{i = 1}^{n} s_i \approx 10^8$。

## 代码
```
#include <bits/stdc++.h>

#define int long long 

using namespace std;

int a[110];
int b[1000010];
int dp[1000010];

signed main()
{
    int T;
    cin >> T;
    
    while (T -- )
    {
        int w, f;
        cin >> w >> f;
        
        int n;
        cin >> n;
        
        int sum = 0;//怪物血量总和
        for (int i = 1; i <= n; i ++ ) cin >> a[i], sum += a[i];
        for (int i = 0; i <= sum; i ++ ) dp[i] = 0;
        dp[0] = 1;
        //预处理怪物血量的和的可能值
        for (int i = 1; i <= n; i ++ )
            for (int j = sum; j >= a[i]; j -- )
                dp[j] |= dp[j - a[i]];
                
        int g = 0;
        for (int i = 1; i <= sum; i ++ )
        {
            if (dp[i] == 1) g = i;
            b[i] = g;//有i点魔法时可以击败怪物血量和的可能值的最大值
        }
        //二分枚举答案
        int l = 0, r = 100000000;
        while (l < r)
        {
            int mid = (l + r) / 2;
            if (sum - b[min(sum, mid * w)] <= mid * f) r = mid;//判断是否可以
            else l = mid + 1;
        }
        cout << l << endl;
    }
    
    return 0;
}
```

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1862F)

&nbsp;

### 题目大意：
小明和利乌尔想要买下 $n$ 件商品，每件商品的价格为 $a_i$，每天小明会获得  $m$ 元工资，利乌尔则会获得 $k$ 元。

出于某些特殊的原因，他们只能使用自己赚到的钱购买商品，现在需要你求出他们二人至少要才能购买完这些商品，需要注意的是，每一天他们所能购买的商品数量是无限的。

### 解题思路：
考虑背包 `dp`。

可以注意到题面中提到：“每一天他们所能购买的商品数量是无限的。”这也就意味着我们并不需要关注他们如何买，只需要知道钱什么时候够即可。

而又由于两人只能使用自己的钱购买商品，则我们可以假设这 $n$ 件商品的总价为 $x$ 元，小明购买了 $y$ 元，不难得出此时两人最少耗费的时间为   $\max(\left\lceil\dfrac{y}{m}\right\rceil,\left\lceil\dfrac{x-y}{k}\right\rceil)$。

然后我们可以注意到数据范围中，$n\leq 100 \text{，} a_i\leq 10^4$，也就是说所有的可能和不会超过 $10^6$，于是我们便可以枚举一下所有的可能和，然后通过上面的式子求最小值即可。

当然，在所有的可能和中，肯定会出现许多重复的，我们只需要建立一个数组来记录有哪些数还没出现过，然后把出现过的数统一存储到一个数组中，对于新枚举到的 $a_i$，只要将它与这个数组中的所有数相加后判断是否出现过即可。

代码如下：
```cpp
int main(){
	//freopen("test.in","r",stdin);
	scanf("%d",&t);
	
	int sum=0;
	while(t--){
		for(int i=1;i<=sum;i++) have[i]=0;
		scanf("%d%d%d",&m,&k,&n);
		
		sum=0;
		int tp=0;
		stk[0]=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			int tmp=tp;
			for(int j=0;j<=tmp;j++){
				if(!have[stk[j]+a[i]]) stk[++tp]=stk[j]+a[i];//判断是否出现过
				//cout<<j<<" "<<n<<endl;
			}
		//	cout<<n<<" "<<	"111111111"<<endl;
			sum+=a[i];
		}
	//	cout<<"111111111111111"<<endl;
		int ans=10000000;
		for(int i=0;i<=tp;i++){//枚举可能的购买金额
			ans=min(ans,max(stk[i]/m+((stk[i]%m)!=0),(sum-stk[i])/k+(((sum-stk[i])%k)!=0)));//求最小时间
		}
		printf("%d\n",ans);
	}
	return 0;
}

```
完结撒花 OvO！！！

---

## 作者：buaa_czx (赞：0)

## 题目大意

你有两个魔法，水魔法和火魔法。每秒你分别能获得 $s,f$ 点对应的魔力。现在有 $n$ 个怪物，每个怪物的强度为 $s_i$。强度为 $s_i$ 的怪物需要 $s_i$ 点魔力的任意魔法消灭。施法不耗任何时间，请问最少几秒后可以杀完全部的怪物？

## 思路

显然放到最后一起杀更方便处理，问题转变成判断 $curr_s,curr_f$ 的水魔法和火魔法能不能杀光全部的怪物。消灭怪物所需的能量总和 $sum_s$ 是固定的，贪心的考虑，我们需要让 $curr_s$ 的水魔法尽可能的使用得更多去消灭怪兽（这个操作可以用 01 背包预处理好），然后判断剩下的怪兽能不能被火能量消灭。

一开始写了一个裸的二维 01 背包，不出意外的 MLE 了，之后优化成一维背包竟然一发就过了。

## 代码

```cpp
int w, f, n, sum_s, cnt, s[110],
    dp[1000010]; // dp[i][j]表示用j个水打前i个，最多能用掉多少水
void solve() {
    sum_s = cnt = 0;
    cin >> w >> f >> n;
    rep(i, 1, n) {
        cin >> s[i];
        sum_s += s[i];
    }
    rep(j, 1, sum_s) dp[j] = 0;
    rep(i, 1, n) {
        per(j, sum_s, 1) {
            if (j >= s[i])
                dp[j] = max(dp[j], dp[j - s[i]] + s[i]);
        }
    }
    int curr_w = 0, curr_f = 0;
    while (++cnt) {
        curr_w += w, curr_f += f;
        if (curr_f >= sum_s - dp[min(curr_w, sum_s)]) {
            break;
        }
    }
    cout << cnt << endl;
}
```

---

## 作者：Natori (赞：0)

>[CF1862F Magic Will Save the World](https://www.luogu.com.cn/problem/CF1862F)

~~魔法将会拯救世界！！！~~

注意到 Vika 显然不会用两种咒语攻击同一只怪物，因为根据题意，必然有一种咒语不会起作用，这就产生了浪费。所以 Vika 击败所有怪物所需要消耗的能量是不变的，即 $\sum_{i=1}^{n}s_i$，下设这个值为 $suma$。

注意到能量之和的值域上限并不大（$100 \times 10^4 = 10^6$），考虑枚举消耗了多少水能量（记为 $x$），那么就会消耗火能量 $suma-x$。现在需要判断这样的分割方案是否可行，若可行，则使用念火系咒语的时间和念水系咒语的时间中的较大值更新答案，即 $ans \leftarrow \min\{ans,\max\{\lceil{\dfrac{x}{w}\rceil},\lceil{\dfrac{suma-x}{f}\rceil}\}\}$。

判断可行性可以 DP：设 $dp_x$ 表示使用 $x$ 单位的水能量、$suma-x$ 单位的火能量是否可行。转移就是 $\text{01}$ 背包的形式。

由于 $dp$ 数组中存的全都是 $0$ 和 $1$，考虑使用 ```bitset``` 进行优化，具体见代码。时间复杂度 $\mathcal{O}(\dfrac{n \sum s_i}{w})$，其中 $w=64$，可以轻松通过。

注意有多组测试数据。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
namespace Fast_In_Out{
	char buf[1<<21],*P1=buf,*P2=buf;
	#define gc (P1==P2&&(P2=(P1=buf)+fread(buf,1,1<<21,stdin),P1==P2)?EOF:*P1++)
	int read(){
		int f=1,x=0;
		char c=gc;
		while(c<'0'||c>'9'){
			if(c=='-')
			    f=-1;
			c=gc;
		}
		while(c>='0'&&c<='9'){
			x=x*10+c-'0';
			c=gc;
		}
		return f*x;
	}
	void write(int x){
		if(x<0)
			x=-x,putchar('-');
		if(x>9)
			write(x/10);
		putchar(x%10+'0');
	}
	#undef gc
}
using namespace Fast_In_Out;
const int N=108,lim=1e6+8,oo=1e9+8;
int n,vw,vf,a[N],suma;
bitset<lim> dp;
int calc(int sw,int sf){
	return max(ceil(1.0*sw/vw),ceil(1.0*sf/vf));
}
void solve(){
	suma=0;
	dp&=0;
	vw=read(),vf=read();
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		suma+=a[i];
	}
	dp[0]=1;
	for(int i=1;i<=n;i++)
		dp|=(dp<<a[i]);
	int ans=oo;
	for(int x=0;x<=suma;x++)
		if(dp[x]==1)
			ans=min(ans,calc(x,suma-x));
	write(ans),putchar('\n');
}
bool Mend;
int main(){
//	File_Work();
	fprintf(stderr,"%.3lf MB\n\n\n",(&Mbegin-&Mend)/1048576.0);
	int testnum=read();
	while(testnum--)
		solve();
	fprintf(stderr,"\n\n\n%.0lf ms",1e3*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

可以发现一个一个的地消灭怪物和把所有魔法值攒到一起在一秒内消灭所有怪物没有区别，于是我们可以转化成找到一个最小的正整数 $x$，满足可以把 $s$ 分成两组 $a,b$，使得 $fx \ge \sum a,wx \ge \sum b$，明显可以二分。接下来需要考虑的是对于一个已知的 $x$，如何判定是否可行。

首先特判一下两种魔法中有没有一种能消灭掉所有的怪物，然后我们设 $f_{i,j}$ 表示已经考虑完了前 $i$ 个怪物，其中生命值为 $j$ 的怪物被分到了 $j$ 组的方案是否可行。转移类似背包 `dp`：

$$f_{i,j}=f_{i-1,j} \texttt{ OR } f_{i-1,j-s_i}$$

其中 $\texttt{OR}$ 表示或操作。

如果存在一个 $j$，满足 $(\sum s)-xw \le j \le xf$ 且 $f_{n,j}=\texttt{True}$，则说明方案可行。时间复杂度为 $O(nV \log V)$，其中 $V= \sum s$。因为 $n \le 100,V \le 10^6$，复杂度看起来比较悬。

注意到 $f$ 值只有 $\texttt{True}$ 和 $\texttt{False}$，所以可以使用 `bitset` 优化，时间复杂度为 $O(\dfrac{nV \log V}{w}+V \log V)$，其中 $w=32$。足以通过此题。

### [AC 代码](https://codeforces.com/contest/1862/submission/220252655)

ps：好像有同校同学不用 `bitset` 水过去了？

---

## 作者：One_JuRuo (赞：0)

## 思路

假设总共耗时是 $s$ 秒，那么最多可以消灭的总生命值是 $s\times(w+f)$。

所以我们可以先求出所有怪物的生命值之和 $sum$，那么，至少需要时间 $t=\lfloor \frac{sum}{w+f} \rfloor$。

然后我们可以算出用这些时间最多可以用水魔法消灭的生命值为 $w\times t$。

那么，我们可以用 dp 求出若干个怪物的生命值之和在小于 $w\times t$ 的情况下的最大值 $sum_w$，那么，在这种情况下，答案就是 $\max(\lceil \frac {sum_w} w \rceil,\lceil \frac {sum-sum_w} f \rceil)$。

因为最后答案可能比 $t$ 大，所以我们可以把所有的可能都求一边，赛时没多想，随手遍历了 $t\sim t+10$ 居然可以 AC，就没多想去看下一题了（主要是当时时间不多了），好像被 hack 了。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,w,f,n,a[105],dp[1000005],sum,ans,res;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld",&w,&f,&n),sum=0,ans=0x3f3f3f3f3f3f3f3f;
		for(long long i=1;i<=n;++i) scanf("%lld",&a[i]),sum+=a[i];
		if(sum<w||sum<f){printf("1\n");continue;}
		long long s=ceil(1.0*sum/(w+f));
		for(long long k=s;k<=s+10;++k)
		{
			memset(dp,0,sizeof(dp));
			for(long long i=1;i<=n;i++) for(long long j=k*w;j>=a[i];j--) dp[j]=max(dp[j],dp[j-a[i]]+a[i]);
			res=max((long long)ceil(1.0*dp[k*w]/w),(long long)ceil(1.0*(sum-dp[k*w])/f));
			if(res<ans) ans=res;
			//else break;
		}
		printf("%lld\n",ans);
	}
}
```

比赛水过去就水过去了，比完了就要思考正确的解法了。

第一种优化方式是减少 dp 次数，也就是枚举 $j$ 的时候只枚举新增的那部分，但是时间复杂度仍然比较高。

所以我们换种思路，既然 dp 是为了得到若干个数加起来小于某个值的最大值，那么我们可以预处理出所有的可能的和，然后在来枚举得到答案不就行了？

那么，如何得到所有的可能的和呢？嗯，还是 dp，如下：

```cpp
for(int i=1;i<=n;++i) for(int j=sum;j>=a[i];--j) dp[j]=dp[j]||dp[j-a[i]];
```

然后枚举所有可能的情况，然后算出答案即可。

```cpp
for(int i=0;i<=sum;++i)if(dp[i]) ans=min(ans,max((long long)ceil(1.0*i/w),(long long)ceil(1.0*(sum-i)/f)));
```

完整代码就不放了。

---

## 作者：minVan (赞：0)

**解题思路**

我们可以用 dp 预处理血量和的所有可能值，边界条件为 $dp_0=1$。代码如下：

```cpp
dp[0] = 1;
for (int i = 1; i <= n; ++i) {
  for (int j = sum; j >= a[i]; --j) {
    dp[j] |= dp[j - a[i]];
  }
}
```

其中 `sum` 为 $\sum\limits_{i=1}^na_i$。

然后用一种魔法打死这堆怪物，剩下的怪物用另一种魔法打死，这里可以二分枚举答案。

**AC 代码，请勿抄袭**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
int a[105];
bool dp[N];
int c[N];
signed main() {
  int t;
  cin >> t;
  while (t--) {
    memset(dp, 0, sizeof(dp));
    int cnt = 0;
    int x, y;
    cin >> x >> y;
    if (x < y)
      swap(x, y);
    int n;
    cin >> n;
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      sum += a[i];
    }
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
      for (int j = sum; j >= a[i]; --j) {
        dp[j] |= dp[j - a[i]];
      }
    }
    for (int i = 0; i <= 1000000; i++) {
      if (dp[i])
        c[++cnt] = i;
    }
    for (int i = 0; i <= sum / x + 1; i++) {
      int l = 1, r = cnt, ans = 0;
      while (l <= r) {
        int mid = (l + r) / 2;
        if (c[mid] <= i * x) {
          l = mid + 1;
          ans = mid;
        } else {
          r = mid - 1;
        }
      }
      int p = sum - c[ans];
      if (p / y + (p % y != 0) > i)
        continue;
      else {
        cout << i << endl;
        break;
      }
    }
  }
  return 0;
}
```

---

## 作者：DerrickLo (赞：0)

可以想到枚举在 $[0,\sum{s_i}]$ 中的所有数，作为第一种魔法对付的怪物的强度之和，这样就能算出所需的时间。然后在这之前先用类似 01背包 的方法求出在 $[0,\sum{s_i}]$ 中所有数是否可以被若干种 $s_i$ 凑出，然后就做完了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,w,f,n,a[105],dp[1000005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>w>>f>>n;
		int sum=0,ans=INT_MAX; 
		memset(dp,0,sizeof dp);
		dp[0]=1;
		for(int i=1;i<=n;i++)cin>>a[i],sum+=a[i];
		for(int i=1;i<=n;i++){
			for(int j=sum;j>=a[i];j--){
				dp[j]|=dp[j-a[i]];
			}
		}
		for(int i=0;i<=sum;i++){
			if(dp[i]){
				ans=min(ans,(int)max(ceil(double(i)/w),ceil(double(sum-i)/f)));
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

