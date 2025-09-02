# 「SFCOI-3」进行一个魔的除 I

## 题目背景

终于，勇士打败了魔王，他把走投无路的魔王困在了一个房间里。

魔王拥有在黑暗中随意穿行的能力，所以勇士只有把房间里所有的灯全部打开，才能找到魔王，最终彻底消灭他。

## 题目描述

房间中共有 $n$ 盏灯，初始状态可以用 $a_1\dots a_n$ 表示，其中 $\tt 0$ 表示这盏灯初始是关闭的，$\tt 1$ 表示这盏灯初始是打开的。

从第一天早晨开始，魔王与勇士轮流行动：

- 每天早晨，魔王可以选择 **连续的** 两盏灯，将它们的状态全部设定为 $\tt 0$；
- 每天晚上，勇士可以选择 **任意的** 至多三盏灯，将它们的状态全部设定为 $\tt 1$。

每次行动时选择的灯在设定前的状态任意。

假设双方均采用最优策略，不会进行任何不利于自己的行动。勇士想知道，**最少** 需要多少天（也即，他最少需要多少次操作）才能将所有灯状态设定为 $\tt 1$——这样，他才能抓到可恶的魔王，迎娶美丽的公主。

## 说明/提示

### 样例解释 1

+ 第一天早晨，魔王关闭第 $1{,}2$ 两盏灯；
+ 第一天晚上，勇士打开 $1{,}2{,}4$ 三盏灯。

### 样例解释 2

+ 第一天早晨，魔王关闭第 $4{,}5$ 两盏灯；
+ 第一天晚上，勇士打开 $2{,}3{,}4$ 三盏灯。
+ 第二天早晨，魔王关闭第 $1{,}2$ 两盏灯；
+ 第二天晚上，勇士打开 $1{,}2{,}5$ 三盏灯。

### 数据规模与约定

**本题采用捆绑测试**。

- Subtask 0（10 points）：$n \leq 10$，$T \leq 2046$。
- Subtask 1（30 points）：$ n \leq 2000$。
- Subtask 2（10 points）：初始所有灯都是关闭的。 
- Subtask 3（20 points）：数据随机生成。
- Subtask 4（30 points）：无特殊限制。

对于所有数据，$1 \leq T \leq 10^6$，$1 \leq n \leq 10^6$，$1 \leq \sum n \leq 3 \times 10^6$。

## 样例 #1

### 输入

```
4
5
1 0 1 0 1
5
1 0 0 1 1
9
0 0 0 0 0 0 0 0 0
13
0 1 0 0 1 0 1 0 0 0 0 0 0
```

### 输出

```
1
2
5
8```

# 题解

## 作者：sail_with_pleasure (赞：13)

为了与题面统一，称 $a_i$ 状态 $\tt 1 \to \tt 0$ 为消除，$\tt 0 \to \tt 1$ 为点亮。

### 算法零

由于状态只有 $2^n$ 种，因此记忆化所有状态，爆搜转移。

时间复杂度 $\mathcal O(n^32^n + T)$，可以通过 Subtask 0。

### 算法一

按算法四的思想模拟即可，不过多赘述。

时间复杂度 $\mathcal O(\sum n^2)$。

### 算法二

考虑初始灯全为 $0$。

这个时候，勇士可以直接贪心地先点亮所有编号为奇数的格子，这样魔王每次只能消除一个 $\tt 1$；直到勇士只能往 $\tt 1$ 空隙中点亮为止。

可以选择任何计算方法，时间复杂度 $\mathcal O(\sum n)$，还可以通过推结论的方法做到更优。

### 算法三

考虑数据随机。

一些缺少一些细节的贪心以及乱搞做法应该都能通过。

### 算法四

考虑魔王的每次消除 $\tt 1$ 的行动，按照时间推移，它形如：

- A 段：若干次连续消除两个 $\tt 1$（可能没有）；
- B 段：若干次消除一个 $\tt 1$（可能没有）；
- C 段：若干次连续消除两个 $\tt 1$（如果一开始就是全 $\tt 1$ 那也可能没有）。

由于 A 段和 C 段每一天都只比前一天增加一盏亮着的灯，所以只需求出在 B 段花费的时间即可计算总时间。

考虑 A 段：先贪心地模拟魔王，每次消掉两个连续的 $\tt 1$，并直接算出它的时间。

在 A 段魔王消除之时，我们可以假设勇士知道魔王会如此消除（事实上，根据魔王每一步的消除，针对性地再点亮一些灯也可行），那么他的最优策略肯定是：在保证任意两个 $\tt 1$ 不连续的前提下，点亮尽可能多的 $\tt 1$，可以用 dp 求解。

考虑 B 段：由于魔王每次都会采取最优策略，那么勇士补上每次魔王消掉的那一盏灯，这同样也是最优的。可能有形如 $\tt{010000001000}$ 的特殊情况，即魔王第一天无论怎么选择都比较劣，可以首先进行一轮模拟或者特判掉。剩下的时间，就相当于每天点亮两盏灯。

考虑 C 段：在 A / B 段都已经求出来的情况下，可以直接求解。

时间复杂度 $\mathcal O(\sum n)$。

代码如下：
```cpp
#include<bits/stdc++.h>
#define pi pair<int,int> 
#define mid (l+r)/2
#define N 1000001
using namespace std;
int t,n,a[N],cnt,cnt1,dp[N],ans,cnt2,flag,flag1,pre[N],nxt[N];
int pan(){//单消段特判 
	int x=-1;
	for(int i=1;i<=n;i++){//计算每两个 1 之间的间隔 
		if(a[i]){
			pre[i]=i-x-1;
			nxt[i]=n+1-i;
			if(x>0)nxt[x]=pre[i];
			x=i;
		}
	}
	for(int i=1;i<=n;i++){//判断是否有较优的单消情况 
		if(a[i]==1&&((pre[i]%2==1||nxt[i]%2==1)||a[i-1]==1||a[i+1]==1)){
			return 0;
		}
	}
	if(a[n]==1)return 0;
	return 1;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=0;i<=n+2;i++){
			a[i]=pre[i]=nxt[i]=dp[i]=0;
		}
		cnt=cnt1=ans=cnt2=flag=flag1=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i])ans++,flag=1;
		}
		if(pan())flag1=1;
		for(int i=1;i<=n;i++){//判断初始双消段的长度 
			if(a[i]==a[i+1]&&a[i]==1){
				a[i]=a[i+1]=0;
				cnt++;
			}
		}
		for(int i=1;i<=n;i++){
			if(a[i]==1){
				dp[i]=max(dp[i-2],dp[i-3]);
			}else if(a[i+1]!=1&&a[i-1]!=1){
				dp[i]=max(dp[i-2],dp[i-3]);
				dp[i]++;
			}
			cnt1=max(cnt1,dp[i]);
		}
		if(n<=3){
			if(ans<n)cout<<1<<endl;
			else cout<<0<<endl;
			continue;
		}
		if(cnt1/3<cnt){//判断是否存在单消段 
			cout<<n-ans<<endl; 
			continue;
		}
		cnt1=cnt1-cnt*3;
		if(flag1&&flag)cnt1++;
		if(flag)cout<<n-ans-cnt1/2-1<<endl;
		else if(n<=5)cout<<2<<endl;
		else cout<<n-(cnt1-3)/2-3<<endl;	
	}	
	return 0;
}
```



PS：这题据说可能有神秘的 bitset 或者线段树等做法，大家可以试一试。

---

## 作者：irris (赞：7)

## Preface

~~感觉给了个大样例的话，就会好做很多啊！~~

~~不过贺 Leasier 的 $\mathcal O(n^32^n)$ 暴力对拍，10 分钟就可以调出来，太爽了。~~

## Solution

**沿用官方题解关于 A 段，B 段，C 段的定义**，~~因为这一部分是我写的，不过那个时候我并不会这题。~~

+ 初始设有 $cnt$ 个 $\tt 1$。
+ 得到 A 段的结束状态：
	+ **这时魔王会把所有 $\tt 11$ 删掉。**
	+ 从前往后遍历序列，将 $\tt 11$ 贪心删掉。记我们删掉了 $cnt_A$ 对 $\tt 11$，那么 A 段则持续了 $cnt_A$ 个回合。
+ 得到 B 段的结束状态：
	+ **这时勇士会尽可能填充更多的 $\tt 1$。**
	+ 在 A 段的基础上，贪心地向里面填入 $\tt 1$，但不存在 $\tt 11$ 子串。
	+ 设我们最终总共有 $cnt_B$ 个 $\tt 1$，那么 B 段持续了 $step_B = \lfloor\frac{cnt_B - cnt_A - cnt}{2}\rfloor$ 回合。
	+ 上述式子的解释：**在 A 段每天增加一个 $\tt 1$，B 段每天增加两个 $\tt 1$**。
+ 得到 C 段的耗时：
	+ 这里有个小细节，就是若 $cnt_A + step_B$ 回合后，**恰好** 得到了 $cnt_B$ 个 $\tt 1$，那么下一回合 **依旧属于 B 段**，增加两个 $\tt 1$；否则下一回合属于 C 段（已经出现 $\tt 11$ 状物了），增加一个 $\tt 1$。
	+ 耗时为 $(n - cnt_B) - [cnt_B = cnt + cnt_A + 2step_B]$。
+ 输出 $cnt_A + step_B + (n - cnt_B) - [cnt_B = cnt + cnt_A + 2step_B]$。
    
## Hack

这一部分特判 **尤为重要**。

+ $cnt = 0$，若 $n \leq 4$ 输出 $1 + [n = 4]$，否则先行模拟一轮（$a_1, a_3, a_5 \gets \tt 1$）。
+ 特判所有 $n \leq 3$，你可能会输出一些不对的 $-1, 0, 1$。
+ $cnt + cnt_A \gt cnt_B$，也就是说甚至没有 B 段，直接跳到 C 段。你并不需要关心跳到的这个时刻是在什么时刻，只需输出 $n - cnt$ 即可（因为每回合增加一个 $\tt 1$）。
+ 注意到，若 **初始没有 A 段**，魔王有可能 **无论如何怎么消除都会让 $cnt_B$ 增加 $1$**（例如 $\tt{01000010}$），如勇士先手，根据定义 $cnt_B = 3$（$\tt{0100\color{green}1\color{normal}010}$）；但魔王一定要消除掉一个 $\tt 1$，那么这时 $cnt_B = 4$（$\tt{\color{red}1\color{normal}0\color{red}1\color{normal}0\color{red}1\color{normal}010}$）。
	+ 如果我们设 $a_{-1} = a_{n + 2} = \tt 1$，$a_{0} = a_{n + 1} = \tt 0$（**相当于规定了边界**），那么这里增加的条件可以转化为对于相邻的三个 $\tt 1$ 出现位置 $x \lt y \lt z$ 有 $z \equiv y + 1\equiv x \pmod 2$。
	+ 证明一下，相当于 $\lfloor\frac{z - y - 2}{2}\rfloor + \lfloor\frac{y - x - 2}{2}\rfloor \lt \lfloor\frac{z - x - 2}{2}\rfloor - 1$，即 $\lfloor\frac{z - y}{2}\rfloor + \lfloor\frac{y - x}{2}\rfloor \lt \lfloor\frac{z - x}{2}\rfloor$（这里无视掉 $z - y = 1$ 或 $y - x = 1$ 的特殊情况），那么显然只有在 $z - y$，$y - x$ 均为奇数时成立。
	+ 显然要求所有的 $x, y, z$ 对均满足上述条件才达成了这个特判，这时我们假装模拟了一轮，让 $cnt \gets cnt + 2, cnt_B \gets cnt_B + 1$ 即可。

## Code

给出一个对拍器，这里面有我的代码，~~改改就能贺了，给大家提供更多样的贺题解选择~~！

```cpp
#include <bits/stdc++.h>

#include <chrono>
std::mt19937 eng(std::chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r) { return std::uniform_int_distribution<int>(l, r)(eng); }

const int N = 10;
int cnt = 0;

#define MAXN 1000001
int a[MAXN], b[MAXN], dp[MAXN]; 

namespace Standard {
	int solve() {
		int cnt = 0, cntA = 0, ext = 0; a[0] = a[N + 1] = 0;
		for (int i = 0; i <= N + 1; ++i) dp[i] = 0;
		for (int i = 1; i <= N; ++i) cnt += a[i];
		if (cnt == 0) {
			if (N < 5) return 1 + (N == 4);
			a[1] = a[3] = a[5] = 1, cnt = 3, ext = 1;
		}
		if (N == 1) return 0;
		if (N <= 3) return cnt != N;
		for (int i = 1; i < N; ++i) if (a[i] == 1 && a[i + 1] == 1) // A 段
			++cntA, a[i] = a[i + 1] = 0;
		for (int i = 1; i <= N; ++i) // B 段结束时的效果
			dp[i] = std::max(dp[i - 2], dp[i - 3]) + (a[i] == 0 && a[i - 1] == 0 && a[i + 1] == 0) + (a[i] == 1);
		int cntB = *std::max_element(dp + 1, dp + N + 1);
		if (cntA == 0) {
			int lst = 1;
			for (int i = 1; i <= N; ++i) if (a[i] == 1) {
				if (((i - lst) & 1) == 0) break; lst = i;
			} else if (i == N && ((N - lst) & 1) == 1) cnt += 2, ++ext, ++cntB;
		}
		if (cnt + cntA > cntB) return N - cnt + ext;
		int stepB = (cntB - cntA - cnt) / 2, finalB = cnt + cntA + stepB * 2;
		return cntA + stepB + (N - cntB) - (finalB == cntB) + ext;
	}
};

namespace MySolve {
	int solve() { return -1; }
};

int main() {
	while (cnt < 10000) {
		for (int i = 1; i <= N; ++i) b[i] = a[i] = rnd(0, 1);
		
		int u = Standard::solve();
		for (int i = 1; i <= N; ++i) a[i] = b[i];
		int v = MySolve::solve();

		if (u != v) {
			printf("WA #%d\n", ++cnt);
			freopen("T4pWA.in", "w", stdout);
			printf("1\n%d\n", N);
			for (int i = 1; i <= N; ++i) printf("%d%c", b[i], " \n"[i == N]);
			freopen("T4pWA.out", "w", stdout);
			printf("%d %d\n", u, v);
			return 0;
		}
		printf("AC #%d\n", ++cnt);
	}
	return 0;
} 

```

---

## 作者：accgj_ (赞：4)

# 题解：[SFCOI-3]进行一个魔的除 I

[题目链接](https://www.luogu.com.cn/problem/P9495)

### 题目大意：

给定一个 $01$ 序列，每一回合魔王先走，选择相邻的两个位置置为 $0$，然后勇者选择任意的三个位置置为 $1$。问，在双方采用最优策略下，勇者至少要多少回合才能将序列置为全 $1$。如果开始时就是全 $1$，答案为 $0$。

--------------

首先考虑双方的最优策略是什么。

以下，我将魔王一次操作改变两个位置（即两个相邻的 $1$）称为“改 2”，以此类推有“改 1”。

首先发现，对于魔王而言，如果能改 2，那么他一定不会改 1 或不改，那么考虑勇者已经在采用最优策略了，那么魔王可以能改 2 就改 2，否则就改 1，最差只存在于开局全 $0$ 没有改的。因为勇者每回合至少净挣一个 $1$，所以和最终回合数有关的就是魔王改 1 的回合数以及没改的回合。

然后再考虑勇者。我们发现，如果勇者空一格放一个 $1$，放不下再和原先的挨着放，那么一定是相当优秀的，因为这很大程度地避免了被改 2，而 $0$ 不会被魔王消掉，所以优先把间隔着放 $1$ 的位置都先放了一定不劣于挨着放，然后被改 2 拖累一回合乃至更多。

考虑初始全 $0$，这时可以轻易发现，勇者的最优策略就是先把奇数位全部变为 $1$，然后每回合先把被魔王变回 $0$ 的位再变为 $1$，然后多走一个偶数位。因为这样魔王改 1 的回合数是最多的。

回到一般情况，那么勇者的最优策略已经出来了，但是魔王的还有问题，因为改 1 显然不能随便挑一个改，比如 $1 0 0 1 0 0 0$，如果改中间的 $1$，那么勇者可以将其变为 $1 0 1 0 1 0 1$，这样回合数为 $3$，而改左边的 $1$，可以发现回合数为 $4$。

那么这是为什么呢？这是因为第二个 $1$ 不论左侧还是右侧的空位，间隔着放 $1$ 后都会有位置空出来被浪费，即一段连续的 $0$（左侧与右侧都有 $1$），若其长度为偶数，那么它在保证没有 $1$ 相邻放了之后，会有一对相邻的 $0$，奇数则不然，所以连续的长度为奇数的 $0$，它两侧的 $1$ 更重要，以下我将左右两侧有至少一边的 $0$ 的数量为奇数（如果这些 $0$ 碰到了边界，要求变为偶数）的 $1$ 称为“好的 $1$”，以此类推有“坏的 $1$”。

那有没有一种可能，就是勇者故意放一个挨着的 $1$ 让魔王删，这样可以把坏的 $1$ 去掉使得最终答案反而更优。我们先不考虑魔王的应对，考虑如下情况（魔王在勇者放之前没有改 2，并且勇者可以走出不让魔王改 2 的方案）$\dots 1 0 0 1 0 0 1 \dots$，假使现在有 $num_1$ 个可以不挨着放 $1$ 的位置，那么放它们可以获得的回合数为 $num_1/2$（奇偶的讨论后面会有，这里先给结论），而诱使魔王删去中间的 $1$，可以获得 $(num_1+2+1)/2-1$ 回合，对于 $num_1$ 的奇偶分别有所不同，但是可以发现，不诱导魔王是更优的。

那么到这里就已经结束了，那么要注意的是，当开局没有改 2，且没有好的 $1$ 时，会增加一次讨论并重复除此之外的全部讨论（就是模拟一轮然后再跑，虽然可以也写成分讨，但是要讨论左右两段连续 $0$ 的奇偶性，还要复制一份），为避免代码过长，建议写成函数。

接下来是不同情况的讨论（可以直接照着敲的那种）。

令 $num_0$ 为开局时可以改 2 的次数（不考虑勇者的操作），$num_1$ 为勇者可以不挨着放的 $1$ 的数量（受前面改 2 的影响），$flag$ 为有没有好的 $1$ ，$tot$ 为初始局面 $0$ 的数量。

注：有些情况可能可以合并，但是我并不确定自己是否把边界情况想到了。从前往后讨论，遇到一次符合即得出答案。



1.  $num_0 \times 3 \geq num_1 \land num_0 \neq 0$，即魔王一直可以改 2，注意，当 $num_0 \times 3 = num_1 \land num_0 \ne 0$ 时，魔王会有一次不能改 2。此时 $ans=tot-[num_0 \times 3=num_1]$。
2.  $num_0=num_1=0$，和上面那个其实差不多 ，魔王只有第一步不能改 2，此时当 $tot \leq 1$ 时，$ans=tot$，否则 $ans=tot-1$。
3.  $num_0=0 \land flag=0$，此时用初始序列模拟一回合然后从头讨论（将讨论过程写成函数可以递归调用，显然只会模拟最多一个回合）。
4. 除以上外，首先进行 $num_0$ 轮，勇者还要放的好的 $1$ 数量为 $num_1-num_0 \times 3$，那么就要用 $(num_1-num_0 \times 3)/2$ 回合，因为当 $(num_1-num_0 \times 3) \bmod 2=1$ 时，勇者还要放一个空，那么就再走一轮（即除这个位置外还会放一个位置，如果是偶数，那就是两个位置），此时空位数量只剩 $tot+num_0 \times 2-num_1-1-[(num_1-num_0 \times 3) \bmod 2=0]$，那么答案就为：$ans=num_0+(num_1-num_0 \times 3)/2+1+\max(0,tot+num_0 \times 2-num_1-1-[(num_1-num_0 \times 3) \bmod 2=0])$


代码：

``````cpp
#include<bits/stdc++.h>
using namespace std;

char *p1,*p2,buf[100000];
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
	int x=0;char ch=nc();
	while(ch<'0' or ch>'9')ch=nc();
	while(ch>='0' and ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=nc();
	return x;
}

int t;
int n;
int a[1000001];

int b[1000001];

int las[1000001];

inline int getans()
{
	for(int i=1;i<=n+1;i++)b[i]=las[i]=0;
	
	for(int i=1;i<=n;i++)b[i]=a[i];
	
	int num0=0,num1=0,tot=0;
	bool flag=0,flag2=0;
	int las=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]==1)flag2=1;
		tot+=(a[i]==0);
		if(a[i]==1)
		{
			if(las==0)
			{
				if(i&1)flag=1;
				las=i;
			}
			else
			{
				if((i-las+1)&1)flag=1;
				las=i;
			}
		}
		if(b[i]==1 and b[i-1]==1)
		{
			b[i]=0;b[i-1]=0;
			flag=1;
			num0++;
		}
	}
	
	if(las!=0)
	{
		if((n+1-las)&1)flag=1;
	}
	
	for(int i=1;i<=n;i++)
	{
		if(b[i-1]==0 and b[i]==0 and b[i+1]==0)
		{
			b[i]=1;
			num1++;
		}
	}
	//printf("%d %d %d\n",num0,num1,tot);
	if(num0*3>=num1 and num0!=0)
	{
		return tot-(num0*3==num1);
	}
	
	if(num0==0 and num1==0)
	{
		if(tot==0)return 0;
		if(tot==1)return 1;
		return tot-1;
	}
	
	if(num0==0 and flag==0)
	{
		
		for(int i=1;i<=n;i++)
		{
			if(a[i]==1)
			{
				a[i]=0;break;
			}
		}
		int numad=3;
		for(int i=1;i<=n;i++)
		{
			if(numad<=0)continue;
			if(a[i-1]==0 and a[i]==0 and a[i+1]==0)
			{
				numad--;
				a[i]=1;
			}
		}
		
		for(int i=1;i<=n;i++)
		{
			if(numad<=0)continue;
			if(a[i]==0)
			{
				numad--;
				a[i]=1;
			}
		}
		
		return getans()+1;
		
	}
	
	
	return num0+(num1-num0*3)/2+1+max(0,tot+num0*2-num1-1-((num1*3-num0)%2==0));
}



int main()
{
	t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		
		a[n+1]=0;
		
		printf("%d\n",getans());
		
		
		
	}
	
	return 0;
}
``````

---

## 作者：irris (赞：0)

嘟嘟嘟。

我们把先手叫做 Alice，后手叫做 Bob。

首先这个博弈是显然能够在有限轮内结束的：$2 < 3$，所以每一轮结束后 $1$ 的个数至少会增加 $1$ 个。

一旦存在 $1$，显然 Alice 至少删一个是不劣的，那么当且仅当 $\forall a_i = 0$ 的第一轮时 $1$ 的个数会增加 $3$ 个，否则 **只会增加 $\boldsymbol{[1, 2]}$ 个**。我们可以把题面改写为：作为 Bob，你需要最大化增加 $2$ 个的轮数；而作为 Alice，你需要最小化增加 $2$ 个的轮数。那么，**一旦存在连续的两个 $\bm 1$，Alice 一定会删除这连续的两个 $\bm 1$**。并且由我们后面的做法可以知道，如果有多种不同的选择，那么任选一对 $1$ 删除是对的。这里先按下不表。

Bob 可以假装 Alice 先把原序列里所有连续的 $1$ 删掉（因为 Alice 的策略是极其固定的），然后再填充若干的 $1$。Bob 需要最大化增加 $2$ 个的轮数，所以 Bob 最后将会在新的序列里填写若干个 $1$，使得这若干个 $1$ 互不相邻，记这个时候序列里的 $1$ 个数为 $cnt$，那么某一轮结束后 $1$ 的个数增加 $1$ 个当且仅当轮数不超过原序列里 Alice 删除的连续 $1$ 的个数，或者当前 $1$ 的个数已经大于 $cnt$。

以上是大体的思路，实现上推荐大家对拍修补细节问题。提示：原序列里没有连续的 $1$，Alice 会不会有额外的策略？

---

## 作者：mRXxy0o0 (赞：0)

新数据好水啊。

# 分析

若最初不是全 $0$，那么魔王灭的灯为 $1$ 或 $2$ 个。考虑计算出只灭了 $1$ 个灯的轮数 $t1$，最初有 $cnt0$ 个 $0$。答案即为 $cnt0-t1$。

不妨先让魔王一直点最初连续的 $1$，勇士再点同样的轮数。先算出勇士计划放的位置，即放最多的 $1$ 使没有 $1$ 相邻的个数。尽管魔王仍在消除初始局面已有的 $1$，但实际上对所放位置（奇偶性）没有影响。

比较两边的轮数，即可得知魔王只点一个 $1$ 的轮数。设魔王一直点最初连续的 $1$，勇士再点同样的轮数后还有 $cnt$ 个计划点的 $1$ 没点，此时 $t1=\lfloor\frac {cnt} 2\rfloor+1$。

# 特殊情况

- `000100001000`，魔王不管点哪一个都会让勇者有一种更优的计划方案，计划的 $1$ 可以多一个。注意到只有没有初始连续的 $1$ 且每个 $1$ 左右 $0$ 连续段长度为偶数是会这样点一次（可以认为 $a_0=a_{n+1}=0$）。

- 魔王点一次后全 $0$，直接算。

- 全 $1$，$0$。

- $t1\le0$，直接算。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=1e6+10;
int n,a[N];
inline int solve(){
	scanf("%d",&n);
	int cnta=0,cntb=0,cnt0=0;
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		cnt0+=(!a[i]);
		if(a[i]&&a[i-1]) a[i]=a[i-1]=0,++cnta;
	}
	if(!cnt0) return 0;
	if(n<=3) return 1;
	if(cnt0>=n-1||(cnta&&cnt0==n-2)) return n==4?2:n-3-((n+1)/2-3)/2;
	int cnt=1,ff=(!cnta),la=1;
	a[n+1]=0;
	for(int i=1;i<=n;++i){
		if(a[i]){
			if(cnt&1) ff=0;
			cnt=0;
		}
		else ++cnt;
		if(!a[i]&&!a[i+1]&&(i&1)==la) a[i]=1,++cntb;
		if(a[i]) la=i&1;
	}
	++cnt;
	if(cnt&1) ff=0;
	if(cnta*3>cntb) return cnt0;
	cntb-=cnta*3;
	int t1=ff?((cntb-1)>>1)+2:cntb/2+1;
	return cnt0-t1;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--) printf("%d\n",solve());
	return 0;
}
```

---

