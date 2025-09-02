# [ABC374F] Shipping

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc374/tasks/abc374_f

> キーエンスは即納で有名です。

この問題において、暦は $ 1 $ 日、 $ 2 $ 日、 $ 3 $ 日、 $ \dots $ と続いています。

注文 $ 1,2,\dots,N $ があり、注文 $ i $ は $ T_i $ 日に発生することが分かっています。  
 これらの注文に対し、以下のルールに従って出荷を行います。

- 出荷は注文 $ K $ 個分までまとめて行うことができる。
- 注文 $ i $ は、 $ T_i $ 日以降にしか出荷できない。
- 一度出荷すると、その出荷の $ X $ 日後になるまで次の出荷が行えない。
  - すなわち、 $ a $ 日に出荷を行った時、次の出荷ができるのは $ a+X $ 日である。
 
注文から出荷までにかかった日数 $ 1 $ 日につき、不満度が $ 1 $ 蓄積します。  
 すなわち、注文 $ i $ が $ S_i $ 日に出荷されたとき、その注文によって蓄積する不満度は $ (S_i\ -\ T_i) $ です。

出荷するタイミングを上手く定めた時、全ての注文において蓄積した不満度の総和として達成可能な最小値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ K\ \le\ N\ \le\ 100 $
- $ 1\ \le\ X\ \le\ 10^9 $
- $ 1\ \le\ T_1\ \le\ T_2\ \le\ \dots\ \le\ T_N\ \le\ 10^{12} $
 
### Sample Explanation 1

例えば、次の通り出荷することで不満度の総和を $ 2 $ にすることができ、これが達成可能な最小です。 - 注文 $ 1 $ を $ 1 $ 日に出荷する。 - これにより不満度は $ (1-1)\ =\ 0 $ 蓄積し、次の出荷ができるのは $ 4 $ 日である。 - 注文 $ 2,3 $ を $ 6 $ 日に出荷する。 - これにより不満度は $ (6-5)\ +\ (6-6)\ =\ 1 $ 蓄積し、次の出荷ができるのは $ 9 $ 日である。 - 注文 $ 4 $ を $ 10 $ 日に出荷する。 - これにより不満度は $ (10-10)=0 $ 蓄積し、次の出荷ができるのは $ 13 $ 日である。 - 注文 $ 5 $ を $ 13 $ 日に出荷する。 - これにより不満度は $ (13-12)=1 $ 蓄積し、次の出荷ができるのは $ 16 $ 日である。

## 样例 #1

### 输入

```
5 2 3
1 5 6 10 12```

### 输出

```
2```

## 样例 #2

### 输入

```
1 1 1000000000
1000000000000```

### 输出

```
0```

## 样例 #3

### 输入

```
15 4 5
1 3 3 6 6 6 10 10 10 10 15 15 15 15 15```

### 输出

```
35```

# 题解

## 作者：nb_jzy (赞：9)

# 题意
~~其实还挺复杂的~~

就是你有 $n$ 个订单，第 $i$ 个订单需要**在第 $T_i$ 天及以后完成**，你还可以让**至多 $K$ 个订单在同一天完成**，但是若你在第 $e$ 天完成了若干订单，你只能在**第 $e+X$ 天及以后**完成下一次订单，即你在第 $e+1\sim e+X-1$ 天内不能有任何操作。

同时，我们还定义了一个代价，对于第 $i$ 个订单，假设在第 $S_i$ 天完成，它会带来 $S_i-T_i$ 的代价，我们希望总代价最小。
# 思路
首先，我们肯定会被 $n\le 100$ 给迷惑，似乎无从下手，再看到 $T_i\le 10^{12}$，就更没法做了，~~其实赛时我也是这样的心路历程~~。

但是一个地方提醒了我们这道题的突破口，我们**可以让 $K$ 个订单一起完成**，容易发现一个比较显然的结论：一定存在一种方案，使得所有**在同一天完成的订单肯定是连续的**。

证明也比较简单：
  > 若我们不选择连续的若干天，那么肯定会有一天在中间中断而被放到下一次处理订单的时间。不妨设我们当前选择了 $i\sim i+x,i+x+2\sim i+y $ 这些订单一起处理，那么我们**如果把断开的第 $i+x+1$ 订单选进来**，从而**使第 $i+y$ 订单放到下一次**。也就是说我们把方案换成 $i\sim i+y-1$ 一起选，$i+y$ 放到下一次，假设这一次是在第 $z$ 天，下一次是在第 $w$ 天，那么显然有 $T_{i+x+1}\le T_{i+y} \le z \le w$，原来的代价是 $z-T_{y}+w-T_{i+x+1}$，改变后的方案即为 $z-T_{i+x+1}+w-T_{y}$，显然两者是相等的，并没有使答案更劣。

如图：
 ![](https://cdn.luogu.com.cn/upload/image_hosting/br27n525.png)

两个颜色的线段长度总和显然是相等的。

有了这一点观察后，我们就可以明显的感觉到：这不就是在做**区间划分**吗！

于是 dp 直接出来了。于是就 $f_i$ 表示搞完前 $i$ 个的最小代价？可这毕竟是一道 F 题，我们还没有考虑一个限制：两次处理订单的时间必须间隔至少 $X$ 天。这又怎么办呢？

如果直接将这一限制加在最后一维，$T_i\le 10^{12}$，直接爆了，所以肯定有更巧妙的方法。

我们容易发现的是，如果去掉这一个限制，那么假设 $i\sim j$ 这些订单一起做，他们显然**在第 $T_j$ 天做最优**。但是因为我们有必须间隔 $X$ 天这个限制，所以**达不到最优的情况**即为如下：
> 假设上一次在第 $u$ 天处理的，若 $u+X>T_j$，那么这一批订单最优就只能在第 $u+X$ 天统一处理。而如果 $u+X\le T_j$，这一批在 $T_j$ 天处理肯定更优。

于是，一个更加厉害的观察呼之欲出了：所有处理订单的天数**只有两种情况**：要么是某一个 $T_x$，要么就是某一个 $T_y+k\times X$。
# 做法
于是我们发现了一个惊人的事情，$x,y,k\le n\le 100$，我们**可以将其加在最后两维**！

我们便有了 dp 状态 $f_{i,j,k}$ 表示前 $i$ 个订单全部完成，且第 $i$ 个订单在第 $T_j+k\times X$ 天被完成。

然后就可以转移了，本人赛时感觉填表很难写，就写的刷表，这里 $sum_i$ 表示 $T_1+T_2...+T_i$ 的前缀和。 

$$
\begin{cases} f_{i+z,j,k+1}=\min\{f_{i+z,j,k+1},f_{i,j,k}+(T_j+(k+1)\times X)\times z-(sum_{i+z}-sum_i) \} & T_j+(k+1)\times X > T_{i+z}\\ f_{i+z,i+z,0}=\min\{f_{i+z,i+z,0},f_{i,j,k}+T_{i+z} \times z -(sum_{i+z}-sum_i)\} & T_j+(k+1)\times X \le T_{i+z} \end{cases}1\le z \le K 
$$
状态是 $n^3$ 的，时间复杂度 $\mathcal O(n^4)$，100 还是跑得很快的。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=105;
int f[maxn][maxn][maxn],N,K,X,t[maxn],sum[maxn],ans;
signed main(){
	cin>>N>>K>>X;
	for(int i=1;i<=N;i++){
		cin>>t[i];sum[i]=sum[i-1]+t[i];
	}
	memset(f,0x3f,sizeof f);
	t[0]=-X;
	f[0][0][0]=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<=N;j++){
			for(int k=0;k<N;k++){
				for(int z=1;z<=min(N-i,K);z++){
					if(t[j]+(k+1)*X>t[i+z]){
						f[i+z][j][k+1]=min(f[i+z][j][k+1],f[i][j][k]+(t[j]+(k+1)*X)*z-(sum[i+z]-sum[i]));
					}
					else{
						f[i+z][i+z][0]=min(f[i+z][i+z][0],f[i][j][k]+t[i+z]*z-(sum[i+z]-sum[i]));
					}
				}
			}
		}
	}
	int ans=1e16;
	for(int i=0;i<=N;i++){
		for(int j=0;j<=N;j++){
			ans=min(ans,f[N][i][j]);
		}
	}
	cout<<ans;
	return 0;
}
```
好题啊，~~这题让我 Rating 涨了不少。~~

---

## 作者：int_R (赞：3)

[更好的阅读体验](https://www.cnblogs.com/int-R/p/18450405/AT_abc374_f)

不难发现一次发出一定是 $a_i+kx,k\in \mathbb{Z}$ 的时刻，因为你一次发出不然就是可以发出抓紧发出，否则肯定是要等到下一次有新包裹要发出再发出，不然你中间等待没意义。也就是说相当于从一个时刻开始连续发送若干次。

设 $f_{i,j}$ 为在第 $i$ 个包裹到达时，总共有 $j$ 个包裹还没发出时，已发出包裹的发出时间和的最小值。

转移时枚举 $i,j$，再不断发出包裹，直至没有包裹要发出。每次发出一些包裹，然后时间 $+x$，再将这 $x$ 时间内的新到达的包裹数加上，转移到下一个包裹到达时。总时间复杂度 $O(n^3)$。

```cpp
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string.h>
#define int long long
#define ll long long
using namespace std;
const int MAXN=110,INF=1e15;
int n,k,x,t[MAXN],f[MAXN][MAXN],ans;
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    memset(f,0x3f3f3f,sizeof(f));
    cin>>n>>k>>x;f[0][0]=0;
    for(int i=1;i<=n;++i) cin>>t[i],ans-=t[i];
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<i;++j) f[i][j]=min(f[i][j],f[i-1][j]);
        for(int j=i;j;--j) f[i][j]=f[i][j-1];f[i][0]=INF;
        for(int j=1;j<=i;++j)
        {
            int now=j,tim=t[i],sum=0,k=i+1;
            while(now)
            {
                int cur=min(now,::k);
                sum+=cur*tim,now-=cur,tim+=::x;
                for(;k<=n&&t[k]<tim;++k) ++now;
                f[k][now]=min(f[k][now],f[i][j]+sum);
            }
        }
    }
    cout<<(ans+f[n+1][0])<<'\n';
}
```

---

## 作者：_JF_ (赞：3)

[Link](https://www.luogu.com.cn/problem/AT_abc374_f)

唉唉，没时间做F。今早起来独立切了。。。。

唉唉。

首先我们观察到，我们必然是取连续的一段货物进行运出，如果有相交或者包含，都能够用调整法（调整成一段一段的）证明出不优。


既然是连续段，那就很经典的 dp 了。

考虑 $dp_{i,j}$ 表示前 $i$ 件物品，在第 $j$ 天发完的答案。

这个转移是容易的，直接枚举我们在第 $j$ 天连续运出的物品段 $[k,i]$ 转移即可。

但是我们发现这时候，$j$ 这一维的状态数较多。我们需要优化。

我们不妨考虑一个贪心，对于物品段 $[k,i]$，若能在 $j$ 时间运出，那么我肯定不会选择在 $j+1$ 运出。就是，对于相同的物品段，我们希望运出的尽可能早。

换言之，对于每个物品段，存在一个“最早运输时间”。

由此，我们可以尝试记录有用的状态。

物品段数量级别是 $O(n^2)$ 的，所以状态数应该不超过这个上限。

$j$ 这维表示的数可能较大，用 `map` 维护即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =301;
#define int long long
int ans=LLONG_MAX,n,K,X,T[N]; 
map<int,int> mp[201],dp[201];
vector<int> vec[N]; 
int calc(int l,int r,int Date){
	int sum=0;
	for(int i=l;i<=r;i++)	sum+=Date-T[i];
	return sum;
}
void DP(){
	vec[0].push_back(0);
	mp[0][0]=1,dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=max(1ll*1,(i-K+1));j<=i;j++){
			for(int k=0;k<vec[j-1].size();k++){
				int now=vec[j-1][k],Date=max(T[i],(((j-1)==0)?now:now+X));
				if(mp[i][Date]==0)	vec[i].push_back(Date),mp[i][Date]=1,dp[i][Date]=LLONG_MAX;
				dp[i][Date]=min(dp[i][Date],dp[j-1][vec[j-1][k]]+calc(j,i,Date));
				if(i==n)	ans=min(ans,dp[i][Date]);
			}
		}
	}
//	cout<<mp[1][1]<<" "<<dp[1][1]<<endl;
	cout<<ans<<endl;
}
signed main(){
	cin>>n>>K>>X;
	for(int i=1;i<=n;i++)	cin>>T[i];
	sort(T+1,T+n+1);
	DP();
	return 0;
} 
```

---

## 作者：Zhao_daodao (赞：3)

# F - Shipping

## Description

给你三个数 $n$，$K$，$X$。

你需要运 $n$ 个货物，每一个货物将在 $T_i$ 的时刻被送到。

有三个限制：

- 每一个货物必须在送到之后才能够运送。
- 每一次运送货物至多可以运送 $K$ 个货物。
- 两次运送货物之间必须间隔至少 $X$ 的时间。

每一个货物有一个不满意度：即运送时间差。

如果货物 $i$ 在时刻 $S_i$ 被运送，那么货物 $i$ 的不满意度就是 $S_i-T_i$。

求所有货物的不满意度之和的最小值。

$1\le K\le n\le 100$，$1\le X\le 10^9$，$1\le T_i\le 10^{12}$。

其中 $T_i$ 按顺序给出。

## Solution

**性质**

首先每一批次的货物肯定是连续的。

就是按照 $T_i$ 排序后，每一次运送出去的货物是一个区间。

调整法，调整成一个区间肯定不会更劣，只会让 $X$ 的限制更松。

---

其次，转化一下 `ans` 的求法。

$$ans=\sum\limits_{i=1}^{n}S_i-T_i=\sum\limits_{i=1}^{n}S_i-\sum\limits_{i=1}^{n}T_i$$

在这个式子中，后面的东西是一个定值，所以只需要 $S_i$ 的和尽量小就可以了。

**朴素算法**

因为每一次送出去的货物是连续的，那么就可以 `dp` 了。

设状态 $dp_{i,t}$ 表示运送完 $[1,i]$ 的货物，当前时间为 $t$ 的 $\sum\limits_{j=1}^{i}S_j$ 的最小值。

满足 $t\ge T_i$，不然当前的送出货物就不合法了。

转移就是枚举一个 $j$，表示上一个货物区间的结尾，$j$ 满足 $i-j\le K$。

再枚举一个 $t'$，使得 $t-t'\ge X$。

此时 $dp_{i,t}=\min(dp_{j,t'}+(i-j)\times t)$。

区间 $[j+1,i]$ 的所有货物的 $S_i$ 都是 $t$，所以当前额外的代价就是 $(i-j)\times t$。

发现贡献**跟 $t'$ 没有关系**，所以 $dp_{i,t}$ 可以和 $dp_{i,t-1}$ 取 $\min$，这样转移就不用枚举 $t'$，直接将 $t'$ 赋值成 $t-X$ 就行了。

 初始时 $dp_{0,i}=0$，其他赋值 `inf`。

答案为 $dp_{n,inf}-\sum\limits_{i=1}^{n}T_i$。

**正确算法**

上面的做法已经接近正确，但是时间 $T_i$ 的范围太大了，连状态都不能设下来。

但是看着就很对啊！

所以可以**缩减状态**，就是不压维，但是将时间 $t$ 的取值缩小一点。

下面非常重要。

**因为每一段运输的时间，要么是最后一个位置的 $T_i$，要么是上一个位置的时间加 $X$，所以最优答案中每一段运输的时间都可以表示为 $T_i+aX$，$a\le n$**。 

所以第二维只需要 $O(n^2)$ 就可以表示并且计算出正确答案。

转移方程和刚才一样。

唯一需要注意的是，时间 $t'$ 不能直接减，而是用双指针从后往前扫，统计每一个 $t$ 的 $t'$ 的取值。

时间复杂度 $O(n^4)$，但是常数非常小，所以能够通过。

---

## 作者：_AyachiNene (赞：2)

# 思路：
一眼发现是分段 dp，但发现状态要记时间，不然难以转移，难点就在于如何记录上次的发货时间。一个显然的贪心，每次的发货时间一定是最后选的一件物品能发货时间或上一次发货时间加上 $x$，发现有意义的时间点很少，任意一个有意义的时间点一定可以表示为 $t_i+jx$，且 $0\leq j<i\leq n$。那么容易设计出状态 $f_{i,j,k}$ 表示最后一件发货物品为 $i$ 件物品下次可发货时间为 $t_j+kx$ 的最小不满意度。转移很简单枚举上一个点的状态分讨一下当前时间和上次状态求出的发货时间，简单前缀和算下贡献就行了，没什么好说的。复杂度 $O(n^4)$ 在加上小常数这个数据范围就够了。
# Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'a'||ch>'z')ch=getch();while(ch>='a'&&ch<='z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
int n,m,x;
int t[114514];
int sum[114514];
int f[105][105][105];
signed main()
{
	read(n,m,x);
	for(int i=1;i<=n;i++) read(t[i]);
	sort(t+1,t+n+1);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+t[i];
	memset(f,0x3f,sizeof f);
	f[0][0][0]=0;
	for(int i=1;i<=n;i++)
		for(int k=max(0ll,i-m);k<i;k++)
			for(int d=0;d<=k;d++)
				for(int j=0;j<=i;j++)
				{
					if(t[d]+j*x<=t[i]) f[i][i][1]=min(f[i][i][1],f[k][d][j]+(i-k)*t[i]-(sum[i]-sum[k]));
					else f[i][d][j+1]=min(f[i][d][j+1],f[k][d][j]+(i-k)*(t[d]+j*x)-(sum[i]-sum[k]));
				}
	int ans=1e18;
	for(int i=0;i<=101;i++) 
		for(int j=0;j<=101;j++) ans=min(ans,f[n][i][j]);
	write(ans); 
	flush();
}
```

---

## 作者：happy_zero (赞：2)

$n,k$ 的数据范围提示可能是 dp。

记 $f_{i,j}$ 表示前 $i$ 个包裹，最后一次在 $j$ 时寄出的最小不满意值。$j$ 很大，且会影响到后面的状态所以不好删去。考虑把 $j$ 这一维缩小来做。

结论：包裹只有可能在 $t_i+kx,k\in N$ 时被寄出。很好理解，寄出时有两种情况：不受 $x$ 限制和受 $x$ 限制。不受限制的情况，肯定是要在某个 $t_i$ 时寄出，否则多的时间没有任何意义；受限制的则是在上一次寄出时间加 $x$ 时寄出，上一次也是如此，直到递归到在 $t_i$ 时寄出的位置，因此是 $t_i+kx$。

不难证明只有小于等于 $n-i+1$ 的 $k$ 是合法的，因此可以把 $j$ 这一维的状态数缩减到 $\frac{n^2}{2}$ 左右。

而状态转移是比较容易的，设 $s$ 为 $t$ 的前缀和，对于 $i<p\le \min(n,i+k)$，可以主动转移：

$$f_{p,\max(t_p,j+x)}\leftarrow\min\{f_{p,\max(t_p,j+x)}, f_{i,j}+j\times (p-i)-(s_p-s_i)\}$$

意思为把 $i+1\sim p$ 这一段的包裹在 $\max(t_p,j+x)$ 时一起寄出。

具体实现时，可以将所有可能的 $j$ 离散在 $b$ 中，状态中的 $j$ 实际对应的发货时间是 $b_j$。

复杂度可以做到 $O(n^2\log {n^2}+n^3k\log n^2)$，转移时多的 $\log$ 是查找 $\max(t_p,j+x)$ 对应 $b$ 的下标，可以通过预处理省去，但常数不大，多只 $\log$ 完全可以接受。~~赛时因边界问题吃了两发罚时。~~

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 105;
int f[N][N * N], a[N], b[N * N], s[N];
signed main() {
	int n, k, x, ts = 0; cin >> n >> k >> x;
	for (int i = 1; i <= n; i++) {
		cin >> a[i]; s[i] = s[i - 1] + a[i];
		for (int j = 0; j <= n - i + 1; j++)
			b[++ts] = a[i] + j * x;
	}
	sort(b + 1, b + 1 + ts); ts = unique(b + 1, b + 1 + ts) - b - 1;
	memset(f, 0x1f, sizeof(f)); 
	b[0] = -f[0][0], f[0][0] = 0; int ans = f[0][1];
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= ts; j++)
			if (f[i][j] != f[0][1])
				for (int p = i + 1; p <= i + k && p <= n; p++) 
					if (b[j] + x <= b[ts]) {
						int t1 = (b[j] < 0 ? 0 : lower_bound(b + 1, b + 1 + ts, b[j] + x) - b);
						int t2 = lower_bound(b + 1, b + 1 + ts, a[p]) - b, tim = max(t1, t2);
						f[p][tim] = min(f[p][tim], f[i][j] + b[tim] * (p - i) - (s[p] - s[i]));
					}
	for (int i = 0; i <= ts; i++) ans = min(ans, f[n][i]);
	cout << ans << '\n';
	return 0;
```

---

## 作者：SJZ2010 (赞：1)

### 题意

一堆货，可以打包发货但一次最多 $K$ 个，发货后还有 $X$ 天不能发货。每个货有个时间 $T_i$，只能在 $T_i$ 及之后发货。

而且每个货物有个不满意度，是实际发货时间 $S_i$ 减 $T_i$。你要最小化不满意度。

$N \le 100$。

### 做法

很明显我们每次打包的都是连续一段。不然肯定亏了。证明不难，留给读者。

于是我们可以考虑 DP。考虑算贡献需要时间，于是我们记录时间维。但时间很大，用 `map` 存。设状态为 $dp(i, t)$，转移不难。可以看代码。

这样……不会爆吗？

不会的。因为考虑状态里的时间只能是 $T_i + kx$ 的形式，其中 $k$ 一定是 $\le N$ 的，因为打包发货才会造成延迟。于是状态数大概是 $\sum_{i = 1}^n i^2 = O(n^3)$。怎么说也过得去。

直接暴力转移总复杂度 $O(n^3 k^2)$ 看似复杂度飞起，然而常数极其小。当然可以优化效率到 $O(n^3k)$。不过过了就懒得写了。

[AC.](https://atcoder.jp/contests/abc374/submissions/58479736)

---

## 作者：CQ_Bob (赞：1)

被薄纱了。

## 分析

首先发现 $\sum (S_i-T_i)$ 等价于 $\sum S_i -\sum T_i$，后者是定值，只需要维护前者。

考虑 DP。定义状态函数 $f_{i,j}$ 表示最后一次一起发货是从 $j\sim i$ 的时候的最小代价。发现我们还需要一个时间，那么不难发现在 $f_{i,j}$ 最小的情况下，时间小的一定最优。然后暴力转移就行了，复杂度是 $O(nk^2)$ 的。

---

## 作者：zrl123456 (赞：0)

[[ABC374F] Shipping]( https://www.luogu.com.cn/problem/AT_abc374_f)  

题目考察：离散化，dp。  
题目简述：  
给你序列 $\{s_n\}$ 和两个正整数 $x,k$，求序列 $\{p_n\},\{t_n\}$ 满足：  
- $\forall i\in[1,n],s_{p_i}\le t_{p_i}$。
- $\forall i\in[1,n),t_{p_i}=t_{p_{i+1}}$ 或 $t_{p_i}+x\le t_{p_{i+1}}$。
- $\forall i\in[1,n-k],t_{p_i}\ne t_{p_i+k}$。

使得 $\displaystyle\sum_{i=1}^nt_i-s_i$ 最小，求这个值。  
数据范围：
- $1\le k\le n\le 100$。
- $1\le x\le 10^9$。
- $\forall i\in[1,n),s_i\le s_{i+1}$。
- $\forall i\in[1,n],1\le s_i\le 10^{12}$。
---
本题的难点是缩小 $t$ 的范围。  

首先，$p$ 序列的顺序是不影响答案的。  
> 因为 $\displaystyle\sum_{i=1}^nt_i-s_i=\sum_{i=1}^nt_i-\sum_{i=1}^ns_i$，顺序不影响 $s,t$ 的和。  

然后我们发现 $t_i$ 只可能是两种值（$1\le pos\le n$）：  
- 可能是某一个 $s_{pos}$。
- 可能是某一个 $t_{pos}+x$。
> 贪心的想，第一种显然是因为若 $t_i$ 不是某一个 $s_{pos}$ 节点，则一定不如是前面的那一个 $s_{pos}$ 节点。  
> 第二种是特例，$t_i$ 不能是前面的那一个 $s_{pos}$。

那么我们将时间节点变成所有的 $s_i+jx$（$1\le i,j\le n$），有效的时间变成了 $\Theta(n^2)$ 个。  

我们这样就可以 dp 了，将有效的时间离散化（设为序列 $a$），设 $f_{i,j}$ 表示在第 $i$ 位上，且上一个 $t_{pos}$ 是 $j$ 的 $t$ 的和的最小值。    
> $j$ 这一维一定要加，要不然你不知道是哪一个时间节点。

$f_{i,j}$ 的转移方程比较难写，我们考虑应用刷表法（我们将从 $f_{i,j}$ 转移到 $f_{pos_i,pos_j}$）。  
$\max(a_j+x,s_{pos_i})$ 是 $t_{pos}$ 应该设的值，应该设 $pos_i-i$ 个。这样的话我们就可用 $f_{pos_i,pos_j}=\min(f_{pos_i,pos_j},f_{i,j}+\max(a_j+x,s_{pos_i})\times(pos_i-i))$ 这个式子来转移了。  

时间复杂度因为实现细节可能是 $\Theta(n^3k)$ 或 $\Theta(n^3k\log n^2)$。  

[代码](https://www.luogu.com.cn/record/180434492)

---

## 作者：Take_A_Single_6 (赞：0)

赛时过不了，是不是自己不够努力。  
看到这题，首先想到的就是dp。观察数据范围，$n$ 和 $k$ 的范围都很小，$T$ 和 $x$ 范围很大。考虑如何设计，发现时间和不满意度都需要维护，不满意度显然应该设为dp数组值。考虑 $T$ 的取值，发现只有可能为 $t_0+ax$ 这种形式，总数 $n^2$ 级别。进而我们可以把复杂度降为 $O(n^3k)$，显然常数不大，可以过。  
具体转移方程，设 $dp_{i,j}$ 表示第 $i$ 个时间点已经发送了 $j$ 个订单的最小不满意度，往后刷表即可。  
转移有两种：
- 什么都不做，直接转移到下个时间点。
- 从当前订单开始，连续 $s$ 个订单一块发，转移到对应的下个时间点。  

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 1024523
#define fir first
#define sec second
#define pr pair<int,int>
#define mk make_pair
#define inf 1000000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX% 10 + '0');
}
int T,n,k,m,t[maxn],dp[20005][105],ans=inf;
vector<int>ti;
signed main()
{
	n=read(),k=read(),m=read();
	for(int i=1;i<=n;i++)t[i]=read();
	for(int i=1;i<=n;i++)
		for(int j=0;j<=n;j++)ti.push_back(m*j+t[i]);
	for(int i=0;i<ti.size();i++)for(int j=1;j<=n;j++)dp[i][j]=inf;
	sort(ti.begin(),ti.end());
	ti.erase(unique(ti.begin(),ti.end()),ti.end());//存有意义的时间点
	for(int u=0,um=0;u<ti.size();u++)
	{
		while(um<ti.size()&&ti[um]<ti[u]+m)um++;//这个时间点发货后下次发货的时间
		for(int i=0;i<n;i++)
		{
			if(dp[u][i]==inf)continue;
			dp[u+1][i]=min(dp[u+1][i],dp[u][i]);//直接转移
			int s=dp[u][i];
			for(int j=i+1;j<=min(n,i+k);j++)
			{
				if(ti[u]<t[j])break;
				s+=ti[u]-t[j];
				if(j==n)ans=min(ans,s);
				if(um<ti.size())dp[um][j]=min(dp[um][j],s);
			}//枚举发货订单数量
		}
	}
	write(ans);
	return 0;
}
```

---

