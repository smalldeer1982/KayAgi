# [USACO24FEB] Moorbles S

## 题目描述

Bessie 和 Elsie 正在玩弹珠游戏。游戏的玩法如下：Bessie 和 Elsie 开始时各有一定数量的弹珠。Bessie 取出 $A$ 个弹珠放在蹄子下，Elsie 猜测 $A$ 是偶数还是奇数。如果 Elsie 猜对了，她从 Bessie 那里赢得 $A$ 个弹珠，如果她猜错了，她输给 Bessie $A$ 个弹珠（如果 Elsie 有少于 $A$ 个弹珠，她就会输掉所有弹珠）。一名玩家失去所有弹珠时即失败。

游戏进行了一定回合后，Elsie 拥有 $N$（$1\le N\le 10^9$）个弹珠。她感觉获胜很难，但她只是想不要输。在与 Bessie 玩得足够久之后，Elsie 对 Bessie 的习惯有了很好的了解，她发现在回合 $i$，Bessie 只可能会取出 $K$（$1\le K\le 4$）种不同数量的弹珠。距离 Bessie 感到无聊退出游戏只有 $M$（$1\le M\le 3\cdot 10^5$）个回合了。你能求出一个字典序最小的行动序列，使得无论 Bessie 如何选择，Elsie 都不会输吗？

## 说明/提示

### 样例解释 1

在第一个测试用例中，唯一字典序更小的行动序列是 `Even Even Even`，但 Bessie 可以使 Elsie 输，通过先出 $5$，将 Elsie 的弹珠数量从 $10$ 减少到 $5$，然后再出 $3$，将 Elsie 的弹珠数量从 $5$ 减少到 $2$，然后出 $3$，这会输光她所有的弹珠。

如果 Elsie 采用正确的行动序列 `Even Even Odd`，那么如果 Bessie 以同样的方式进行游戏，最后当她出 $3$ 时，Elsie 将获得那 $3$ 个弹珠，将她的弹珠数量增加到 $5$。可以进一步证明，只要 Elsie 操作是 `Even Even Odd`，Bessie 无法以其他的方式赢走 Elsie 的所有弹珠。

在第二个测试用例中，可以证明，对于 Elsie 可以选择的任何行动顺序，Bessie 都存在一种方式可以赢走 Elsie 的所有弹珠。

### 测试点性质

- 测试点 $3$：$M\le 16$。
- 测试点 $4-6$：$M\le 1000$。
- 测试点 $7-12$：没有额外限制。

## 样例 #1

### 输入

```
2
10 3 2
2 5
1 3
1 3
10 3 3
2 7 5
8 3 4
2 5 6```

### 输出

```
Even Even Odd
-1```

## 样例 #2

### 输入

```
1
20 8 2
3 5
3 5
3 5
3 5
3 5
3 5
3 5
3 5```

### 输出

```
Even Even Even Odd Even Odd Even Odd```

# 题解

## 作者：rhn7 (赞：5)

~~话说这次银组前两题难度堪比铂金~~

考虑最坏情况，Elsie 猜偶数时 Bessie 拿出的是最大的奇数，没有奇数拿出的就是最小的偶数，Elsie 猜奇数时 Bessie 拿出的是最大的偶数，没有偶数拿出的就是最小的奇数。

我们设第 $i$ 轮 Elsie 猜偶数最多亏 $e_i$，猜奇数最多亏 $o_i$。

求字典序最小是一个简单贪心。对于每轮，如果出偶数能保证后面不输，就出偶数，否则出奇数。

关键是怎么判断后面不输，很容易想到对 $\min(e,o)$ 求后缀和，看其是否小于当前弹珠个数。

这样做过不了样例二，原因是题目要求任意时刻都有弹珠，上述方法只判断了最后时刻是否有弹珠，所以要看亏的最大的时刻有没有亏光，即对 $\min(e,o)$ 求以 $i$ 为开头的最大子段和。

代码如下：
```cpp
#include<bits/stdc++.h>
#define rd(x) scanf("%lld",&x)
using namespace std;
typedef long long ll;
const ll N=3e5+5;
ll T,n,m,k,x,e[N],o[N],f[N];
void solve(){
	rd(n);rd(m);rd(k);f[m+1]=0;
	for(ll i=1;i<=m;i++){
		ll m1=1e15,m2=1e15;o[i]=e[i]=0;
		for(ll j=1;j<=k;j++){
			rd(x);
			if(x&1) m1=min(m1,x),e[i]=max(e[i],x); 
			else m2=min(m2,x),o[i]=max(o[i],x);
		}
		if(e[i]==0) e[i]=-m2;if(o[i]==0) o[i]=-m1;
	}
	for(ll i=m;i>=1;i--) f[i]=max(0ll,f[i+1])+min(e[i],o[i]);//DP过程 
	if(f[1]>=n) return printf("-1"),void();//注意无解的判断 
	for(ll i=1;i<=m;i++){
		if(n-e[i]>f[i+1]&&n>e[i])printf("Even"),n-=e[i];//f[i+1]可能<0，所以要判断 n>e[i]
		else printf("Odd"),n-=o[i];
		if(i<m) printf(" ");
	}
}
int main(){rd(T);while(T--) solve(),printf("\n");}
```
本蒟蒻赛时脑残把 `f[i]=max(0ll,f[i+1])+min(e[i],o[i]);` 写成了 `f[i]=max(0ll,f[i+1]+min(e[i],o[i]));`，由于数据水居然过了，求大佬 hack。

---

## 作者：Guizy (赞：4)

我们可以开一个 $even$ 数组和一个 $odd$ 数组，分别记录到了第 $i$ 轮时选偶数和奇数的最坏情况要赚多少（亏了就是负数）。

```cpp
for(int i=1;i<=m;i++){
	maxe=maxo=-1,mine=mino=INT_MAX;
	for(int j=1;j<=k;j++){
		scanf("%lld",&a[i][j]);
		if(!(a[i][j]&1)) maxe=max(maxe,a[i][j]),mine=min(mine,a[i][j]);
		else maxo=max(maxo,a[i][j]),mino=min(mino,a[i][j]);
	}
	if(maxe==-1) even[i]=-maxo,odd[i]=mino;
	else if(maxo==-1) even[i]=mine,odd[i]=-maxe;
	else even[i]=-maxo,odd[i]=-maxe;
}
```

有了这两个数组，我们就可以求一段区间内的最优解。

既然要字典序最小，那我们就要从前往后枚举，能选 `Even` 就选 `Even`，否则选 `Odd`。

如何判断能否选 `Even`？

如果当前的石子数量加上 $even_i$ 再加上 $[i,n]$ 的最优解大于 $0$，并且当前石子数量加上 $even_i$ 大于 $0$ 就可以（因为石子数量不能是负数）。否则不行。

这时我们就要用一个后缀和数组 $suf$ 记录，$suf_i$ 表示 $[i,n]$ 的最优解。

判断能否选 `Odd` 同理。

如果两个都不能选，那么输出 `-1` 跑路。

Tips：计算 $suf$ 的时候要对 $0$ 取 $\min$，否则程序在判断能否选 `Even` 的时候以为后面可以赚回来，石子数就可能会形成一个正数到负数再回到正数的过程，然后到了后面程序发现石子数为负了，就会输出 `-1`。感觉说的有点抽象，不懂的可以去看 #3 的倒数第二组手模一下。

```cpp
for(int i=m;i>=1;i--)
	suf[i]=min(0ll,suf[i+1]+max(even[i],odd[i]));//Tips
for(int i=1;i<=m;i++){
	if(n+even[i]+suf[i+1]>0&&n+even[i]>0)
		ans+="Even ",n+=even[i];
	else if(n+odd[i]+suf[i+1]>0&&n+odd[i]>0)
		ans+="Odd ",n+=odd[i];
	else{
		puts("-1"),flag=0;
		break;
	}
}
```

---

## 作者：lumid (赞：3)

银组只会这题qwq

---

考虑将奇数和偶数分开计算。如果 Elsie 在回合 $i$ 猜奇数，那么对 Elise 的最坏可能是：

1. 存在偶数

Bessie 把 $a_{i,1},a_{i,2},\dots,a_{i,K}$ 中**最大的偶数**放在蹄子下。Elsie 的弹珠数量**减去**该数。

2. 不存在偶数

Bessie 把 $a_{i,1},a_{i,2},\dots,a_{i,K}$ 中**最小的奇数**放在蹄子下。Elsie 的弹珠数量**加上**该数。

猜偶数同理。

---


考虑倒过来想。如果要 Elsie 不输，那么游戏结束后（“第 $m+1$ 回合”）她至少要有 $1$ 个弹珠，且在游戏过程中没有出现少过 $1$ 个弹珠的回合。

考虑 DP。

**状态表示：**

$\text{exist}[x][0/1]$ = Bessie 在第 $x$ 回合的选择里是否存在偶/奇数。

$dp[x][0/1]$ = Elsie 最少需要多少个弹珠才能保证在回合 $x$ 猜偶/奇数不会输。

**转移方程：**

$dp[x][i]=\max\left(1,\min\limits_{j \in \{0,1\}}\{dp[x+1][j]\}+
\begin{cases}
\max\limits_{k \in [1,K]}\{a[k] \mid a[k] \not\equiv i \pmod{2} \}, & \text{if} \text{ exist}[x][\neg i]  \\
-\min\limits_{k \in [1,K]}\{a[k] \mid a[k] \equiv i \pmod{2} \}, & \text{otherwise}
\end{cases}\right)$

放 $\max(1,\cdots)$ 是为了满足弹珠数量在任何回合不能低过 $1$ 的条件。

**边界：**$dp[m+1][0/1]=1$

**目标：**

题目要求求出“字典序最小的行动序列”。因为 `Even` 的字典序小过 `Odd`，所以优先选择 `Even`。

现在我们已经知道对于所有回合 Elsie 最少应有的弹珠数量。只需遍历 $1 \le i \le m$，优先选择猜偶数。如果在回合 $i$ 发现拥有的弹珠数量少于 $dp[i][0/1]$，那么 Elsie 肯定会输掉游戏，所以输出 $-1$。

---

[评测记录](https://www.luogu.com.cn/record/148588841)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t;cin>>t;
    while(t--){
        ll n,m,k;cin>>n>>m>>k;
        bool exist[m+1][2];
        ll maxi[m+1][2],mini[m+1][2];
        memset(exist,0,sizeof(exist));
        memset(maxi,0,sizeof(maxi));
        memset(mini,0,sizeof(mini));
        for(int i=1;i<=m;i++){
            for(int j=0;j<k;j++){
                ll ai;cin>>ai;
                if(exist[i][ai%2]){
                    maxi[i][ai%2]=max(maxi[i][ai%2],ai);
                    mini[i][ai%2]=min(mini[i][ai%2],ai);
                }else{
                    maxi[i][ai%2]=ai;
                    mini[i][ai%2]=ai;
                }
                exist[i][ai%2]=1;
            }
        }

        // dp
        ll dp[m+2][2];
        memset(dp,0,sizeof(dp));
        dp[m+1][0]=1;dp[m+1][1]=1;
        for(int x=m;x>0;x--){
            dp[x][0]=min(dp[x+1][0],dp[x+1][1]);
            if(exist[x][1]) dp[x][0]+=maxi[x][1];
            else dp[x][0]-=mini[x][0];
            dp[x][0]=max(1ll,dp[x][0]);
            
            dp[x][1]=min(dp[x+1][0],dp[x+1][1]);
            if(exist[x][0]) dp[x][1]+=maxi[x][0];
            else dp[x][1]-=mini[x][1];
            dp[x][1]=max(1ll,dp[x][1]);
        }

        //
        bool flag=1;
        string ans="";
        for(int x=1;x<=m;x++){
            if(n<min(dp[x][0],dp[x][1])){flag=0;break;}
            if(ans.length())ans+=" ";
            if(n>=dp[x][0]){
                if(exist[x][1]) n-=maxi[x][1];
                else n+=mini[x][0];
                ans+="Even";
            }else{
                if(exist[x][0]) n-=maxi[x][0];
                else n+=mini[x][1];
                ans+="Odd";
            }
        }
        if(flag)cout<<ans<<'\n';
        else cout<<"-1\n";
    }
}
```

---

## 作者：huhangqi (赞：2)

总共只有猜奇数还是偶数两种情况，我们直接考虑两种的最坏情况，然后选择两种之间较好的情况即可。

那么我们就得到了是否可以不输。

但是题目还让字典序最小。

那么我们就找选择奇数的情况，如果可以改成偶数，那么把奇数变成偶数。

检验是否可以改变只需要取后缀最值即可。

此时的改变会改变之后所有的弹珠数量，所以要记录修改的弹珠数量。

然后本蒟蒻看到区间查询和区间修改直接就上线段树了，然而实际上并没有这么麻烦，反正你是从前向后遍历，后面查询的点一定是被前面修改的，直接后缀最小值再记录减少的弹珠数量即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,m,k,a[300005],b[300005],dp[300005],suf[300005];
bool ans[300005];
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>m>>k;
		for(int i=1;i<=m;i++)a[i]=b[i]=-1e18;
		for(int j=1;j<=m;j++){
			for(int i=1,x;i<=k;i++){
				cin>>x;
				if(x%2==0)b[j]=max(b[j],-x),a[j]=max(a[j],x);
				else a[j]=max(a[j],-x),b[j]=max(b[j],x);
			}	
		}
		int sum=n;
		for(int i=1;i<=m;i++){
			if(a[i]>b[i])sum-=b[i],ans[i]=0;
			else sum-=a[i],ans[i]=1;
			if(sum<=0)break;
			dp[i]=sum;
		}
		if(sum<=0){
			cout<<-1<<endl;
			continue;
		}
		suf[m]=dp[m];
		for(int i=m-1;i>=1;i--)suf[i]=min(suf[i+1],dp[i]);
		int tot=0;
		for(int i=1;i<=m;i++){
			if(ans[i]==0)continue;
			int tmp=suf[i]+tot;
			tmp=tmp-b[i]+a[i];
			if(tmp>0)tot+=-b[i]+a[i],ans[i]=0;
		}
		for(int i=1;i<=m;i++){
			if(ans[i])cout<<"Odd"<<' ';
			else cout<<"Even"<<' ';
		}
		puts("");
	}
	return 0;
}
``````

---

## 作者：cyj1314 (赞：2)

# 题解
以下为题解，题目是求一个字典序最小的回合序列，满足在每一回合中满足弹珠数量大于0

因为字典序，很明显，我们可以从前往后贪心做一遍，尽量让当前选 `Even`，实在不行选 `Odd`。 但这样会导致，我们在遍历途中莫名死掉。因为反悔的时候太晚了，所以需要及时预判。所以可以从后往前dp做一遍，对于每一回合 $i$ 中的选择 $j[Odd / Even]$, 有 $f_{ij}$ 的值为其至少需要的弹珠数量才能有解。搭配先前的贪心就能做了。

总的来说，就是预判自己走的贪心路是否是条死路。

# 核心代码

```cpp
f[m + 1][0] = f[m + 1][1] = 0;
tto (i, 1, m)
{
    ott (j, 0, 1) mi[j] = inf, mx[j] = -inf, f[i][j] = inf;
    ott (j, 1, l)
    {
    	int x = p[i][j];
    	mi[x & 1] = min (mi[x & 1], x), mx[x & 1] = max (mx[x & 1], x);
    }
	if (mi[0] == inf)
	{
		f[i][0] = min (f[i + 1][0], f[i + 1][1]) + (val[i][0] = mx[1]);
		f[i][1] = min (f[i + 1][0], f[i + 1][1]) + (val[i][1] = -mi[1]);
	}
	else if (mi[1] == inf)
	{
	    f[i][0] = min (f[i + 1][0], f[i + 1][1]) + (val[i][0] = -mi[0]);
	    f[i][1] = min (f[i + 1][0], f[i + 1][1]) + (val[i][1] = mx[0]);
	}
	else
	{
		f[i][0] = min (f[i + 1][0], f[i + 1][1]) + (val[i][0] = mx[1]);
		f[i][1] = min (f[i + 1][0], f[i + 1][1]) + (val[i][1] = mx[0]);
	}
	ott (j, 0, 1) f[i][j] = max (f[i][j], 0);//, printf ("f[%d][%d] = %d\n", i, j, f[i][j]);
}
if (n <= min (f[1][0], f[1][1])) {puts ("-1"); continue;}
ott (i, 1, m)
{
	if (n <= f[i][0]) ans[i] = 1, n -= val[i][1];
	else ans[i] = 0, n -= val[i][0];
}
ott (i, 1, m - 1) printf (ans[i] ? "Odd " : "Even ");
printf (ans[m] ? "Odd\n" : "Even\n");
```

# 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;

//#define int long long
#define ott(i, l, r) for (int i = (l); i <= (r); i ++)
#define tto(i, l, r) for (int i = (r); i >= (l); i --)

using db = double;
using ll = long long;
using pdd = pair <db, db>;
using pll = pair <ll, ll>;
using pii = pair <int, int>;

int read ()
{
	int x = 0, f = 1; char ch = getchar ();
	while (!isdigit (ch)) {if (ch == '-') f = -1; ch = getchar ();}
	while (isdigit (ch)) x = x * 10 + ch - '0', ch = getchar ();
	return x * f;
}

const int N = 1e6 + 110, mod = 1e9 + 7, inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int T;
int n, m, l;
int mi[2], mx[2];
bool ans[N];
int val[N][2], f[N][2], p[N][5];

int main ()
{ 
    
    T = read ();
    while (T --)
    {
    	n = read (), m = read (), l = read ();
    	ott (i, 1, m) 
    	    ott (j, 1, l)
    	        p[i][j] = read ();//多组数据初始化 
    	
    	//对于每一回合i选j[0/1], 至少需要fi,j的弹珠数量才能有解 
    	f[m + 1][0] = f[m + 1][1] = 0;//dp边界 
    	tto (i, 1, m)//倒序dp 
    	{
        //其中mi, mx分别为最小最大值。 
		//下标[0/1]又分为奇偶 
		//用来考虑最坏情况: 加的少，减的多 
		
		//在dp中顺便求val[i][0/1],原因是懒得复制粘贴了,其为回合i选[0/1]的代价
    		ott (j, 0, 1) mi[j] = inf, mx[j] = -inf, f[i][j] = inf;//初始化 
    		ott (j, 1, l)
    		{
    			int x = p[i][j];
    			mi[x & 1] = min (mi[x & 1], x), mx[x & 1] = max (mx[x & 1], x);
			}
			if (mi[0] == inf)//没有偶数 
			{
				f[i][0] = min (f[i + 1][0], f[i + 1][1]) + (val[i][0] = mx[1]);
				f[i][1] = min (f[i + 1][0], f[i + 1][1]) + (val[i][1] = -mi[1]);
			}
			else if (mi[1] == inf)//没有奇数 
			{
			    f[i][0] = min (f[i + 1][0], f[i + 1][1]) + (val[i][0] = -mi[0]);
				f[i][1] = min (f[i + 1][0], f[i + 1][1]) + (val[i][1] = mx[0]);
			}
			else//奇偶都有 
			{
				f[i][0] = min (f[i + 1][0], f[i + 1][1]) + (val[i][0] = mx[1]);
				f[i][1] = min (f[i + 1][0], f[i + 1][1]) + (val[i][1] = mx[0]);
			}
			ott (j, 0, 1) f[i][j] = max (f[i][j], 0);//, printf ("f[%d][%d] = %d\n", i, j, f[i][j]);
	    }
	    if (n <= min (f[1][0], f[1][1])) {puts ("-1"); continue;}//一上路就知道自己活不了 
		ott (i, 1, m)//正序贪心 
		{//能偶就偶
			if (n <= f[i][0]) ans[i] = 1, n -= val[i][1];//被迫选奇 
			else ans[i] = 0, n -= val[i][0];
		}
		ott (i, 1, m - 1) printf (ans[i] ? "Odd " : "Even ");
		printf (ans[m] ? "Odd\n" : "Even\n");
	}
	
	return 0;

}
/*
1
12 4 2 
2 5 
1 3 
1 3 
2 3

*/
/*
1
12 4 2 
2 5 
1 3 
1 3 
2 3

*/
```

---

## 作者：Aurie (赞：1)

# P10192 [USACO24FEB] Moorbles S 题解
为了方便讲解，先展示读数据的代码，避免读者不理解数据存储方式而看不懂。

```cpp
vector<int> a[N][2];
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>k;
		for(int i = 1;i<=m;i++){
			a[i][0].clear();// 多测不清空，爆零两行泪。
			a[i][1].clear();
			for(int j = 1;j<=k;j++){
				int x;
				cin>>x;
				if(x&1){// 若 x 为奇数，存入a[i][1]
					a[i][1].push_back(x);
				}else{// 奇数存 1 里面，偶数存 0 里面，比较人性化。
					a[i][0].push_back(x);
				}
			}
			sort(a[i][1].begin(),a[i][1].end());// 排序便于以后使用。
			sort(a[i][0].begin(),a[i][0].end());
		}
```

首先考虑判 $-1$。我们需要求出，最坏状况下最少能扣多少，设 $c_i$ 为从第一轮进行到底 $i$ 轮，在最坏情况下，最少失去了多少弹珠。

可写出如下代码：

```cpp
void pre(){
	for(int i = 1;i<=m;i++){
		c[i] = c[i-1];// 首先 c[i] = c[i-1]，要把前 i-1 轮扣的分都加上。
		if(a[i][0].empty()){
			c[i] -= a[i][1].front();// 如果没有偶数，只有奇数，选奇数一定能猜对，不会失去弹珠反而会加，最坏情况下只能加 front() 也就是最小值，因为 c[i] 记录的是扣分
		}else if(a[i][1].empty()){
			c[i] -= a[i][0].front();
		}else{
			c[i] += min(a[i][0].back(),a[i][1].back());//如果都有了话，选奇数会加偶数最大值，选偶数加奇数最大值，因此选出奇数和偶数最大值的最小值即可。
		}
	}
}
```

然后我们从 $1$ 到 $m$ 遍历 $c_i$ 若存在一轮 $n \leq c_i$ 则，证明在那一轮最坏情况下的弹珠最小损失数量已经大于等于 $n$ 了，则无解，否则就至少存在一组解。

代码：
```cpp
for(int i = 1;i<=m;i++){
	if(c[i]>=n){
		puts("-1");
		goto ed;
	}
}
```

最后考虑怎么求最小字典序。由于要满足最小字典序，所以要让在前面的尽量是 $Even$，假如前面 $i-1$ 位已经确定，此时还剩下 $n$ 个弹珠，那就可以钦定当前位置为 $Even$，然后看当前位为 $Even$ 时后面是否存在一组任意解，如果存在，则当前位为 $Even$。后面即便全是 $Odd$ 也比前位为 $Odd$ 后面全是 $Even$ 要优。

现在问题在于如何判断当前位为 $Even$ 时，后面是否存在一组解使任意时刻剩下的弹珠个数都不为零。
首先如果猜了 $Even$ 则在本次最坏可能会扣除当前轮奇数的最大值，只剩下 $n-MaxOfOdd$ 供以后使用。在之前求出了 $c_i$，它类似一个前缀和数组，通过它能 $O(1)$ 的快速求出 $i$ 到 $j$ 轮最坏情况下最少会扣多少。

假设 $get(i,j) = i$ 到 $j$ 轮最坏情况下最少会扣多少 $= c[j]-c[i-1]$

那么可以用 $n-MaxOfOdd$ 减去 $get(i,m)$ 得到 $n-MaxOfOdd-get(i,m)$ 推出最后一轮时最多剩多少硬币，然后判断剩下硬币数是否大于零？

这存在一个问题，由于在猜的过程中可能会赚弹珠，所以即便 $n-MaxOfOdd-get(i,m)>0$。 也只保证了到最后不为 $0$，在过程中可能变成零，因此要判断 $n-MaxOfOdd-\max\limits_{i\leq j\leq m}(get(i,j))$ 是否大于零。

此时我们设 $f_i = \max\limits_{i\leq j\leq m}(get(i,j))$ 则有 $f_i = \max(f_{i+1}+get(i,i),get(i,i))$，就可以从 $m$ 到 $1$ 的倒序递推 $f_i$ 了。此时会发现 $c_i$ 存成前缀和数组多此一举，~~不过写都写完了，就不改了~~。

代码：
```cpp
#include<bits/stdc++.h> 
using namespace std;

const int N = 3e5+10;

int t,n,m,k,c[N];

vector<int> a[N][2];
void pre(){
	for(int i = 1;i<=m;i++){
		c[i] = c[i-1];
		if(a[i][0].empty()){
			c[i] -= a[i][1].front();
		}else if(a[i][1].empty()){
			c[i] -= a[i][0].front();
		}else{
			c[i] += min(a[i][0].back(),a[i][1].back());
		}
	}
}

int get(int x,int y){
	return c[y]-c[x-1];
}

int fr[N];
bitset<N> mk;

int f[N];
int main(){
	cin>>t;
	while(t--){
		mk.reset();
		cin>>n>>m>>k;
		memset(c,0,sizeof(c));
		memset(f,-0x3f,sizeof(f));
		for(int i = 1;i<=m;i++){
			a[i][0].clear();
			a[i][1].clear();
			for(int j = 1;j<=k;j++){
				int x;
				cin>>x;
				if(x&1){
					a[i][1].push_back(x);
				}else{
					a[i][0].push_back(x);
				}
			}
			sort(a[i][1].begin(),a[i][1].end());
			sort(a[i][0].begin(),a[i][0].end());
		}
		pre();
		for(int i = 1;i<=m;i++){
			if(c[i]>=n){
				puts("-1");
				goto ed;
			}
		}
		f[m+1] = 0;
		f[m] = get(m,m);
		for(int i = m-1;i>=1;i--){
			f[i] = max(f[i+1]+get(i,i),get(i,i));
		}
		for(int i = 1;i<=m;i++){
			if(a[i][1].empty()){
				mk[i]=0;
				n+=a[i][0].front();
			}else if(a[i][0].empty()){
				if(n-a[i][1].back()-f[i+1]>0&&n-a[i][1].back()>0){
					n-=a[i][1].back();
					mk[i] = 0;
				}else{
					n+=a[i][1].front();
					mk[i] = 1;
				}
			}else{
				if(n-a[i][1].back()-f[i+1]>0&&n-a[i][1].back()>0){
					n-=a[i][1].back();
					mk[i] = 0;
				}else{
					n-=a[i][0].back();
					mk[i] = 1;
				}
			}
		}
		for(int i = 1;i<=m;i++){
			if(mk[i]){
				cout<<"Odd ";
			}else{
				cout<<"Even ";
			}
		}
		cout<<'\n';
		ed:;
	}
	return 0;
}
```

---

## 作者：cff_0102 (赞：1)

可以用一个数组记录下如果在第 $i$ 局猜奇数或偶数，要让最后不输掉，这一局最少需要剩下多少弹珠。这个数组可以 $O(n)$ 计算出来。如果按最优方案来选第一局需要的最少的弹珠数量还是大于 $n$，则无解。

接着从前到后选，为了让字典序最小，每次优先猜偶数，如果猜了偶数会输就只能猜奇数了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int a[N][5];
int gt[N][2];//0 为偶数 1 为奇，代表这局猜的几，要在最后不输掉，这局必须剩多少
int mian(){
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)for(int j=1;j<=k;j++)cin>>a[i][j];
    gt[m+1][0]=gt[m+1][1]=1;//这里记得初始化，不然样例都会 WA 
    for(int i=m;i>=1;i--){
        int minodd=1e4,maxodd=0,mineven=1e4,maxeven=0;
        for(int j=1;j<=k;j++){
            if(a[i][j]%2){
                minodd=min(minodd,a[i][j]);
                maxodd=max(maxodd,a[i][j]);
            }else{
                mineven=min(mineven,a[i][j]);
                maxeven=max(maxeven,a[i][j]);
            }
        }
        //如果这局猜偶数，应该这样计算出
        if(maxodd){
            //扣掉最大的奇数
            gt[i][0]=min(gt[i+1][0],gt[i+1][1])+maxodd;
        }else{
            //没有就选最小数
            gt[i][0]=min(gt[i+1][0],gt[i+1][1])-mineven;
        }
        //如果这局猜奇数，应该这样计算出
        if(maxeven){
            //扣掉最大的偶数
            gt[i][1]=min(gt[i+1][0],gt[i+1][1])+maxeven;
        }else{
            //没有就选最小数
            gt[i][1]=min(gt[i+1][0],gt[i+1][1])-minodd;
        }
        //永远不能小于一，取更大值就可以 
        gt[i][0]=max(gt[i][0],1);
        gt[i][1]=max(gt[i][1],1);
    }
    if(min(gt[1][0],gt[1][1])>n)return cout<<-1<<endl,0;//开局注定不能赢，不判无解怎么行
    for(int i=1;i<=m;i++){
        int minodd=1e4,maxodd=0,mineven=1e4,maxeven=0;
        for(int j=1;j<=k;j++){
            if(a[i][j]%2){
                minodd=min(minodd,a[i][j]);
                maxodd=max(maxodd,a[i][j]);
            }else{
                mineven=min(mineven,a[i][j]);
                maxeven=max(maxeven,a[i][j]);
            }
        }
        //偶数字典序更小，这样选取更有效
        //如果能猜就可以
        if(gt[i][0]<=n){
            n+=(maxodd)?(-maxodd):mineven;
            cout<<"Even ";continue;
        }
        //否则只能输出奇 
        n+=(maxeven)?(-maxeven):minodd;
        cout<<"Odd "; 
    }
    cout<<endl;
    return 0;
}
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t;cin>>t;
    while(t--){
        mian();
    }
    return 0;
}
```

---

## 作者：TG_Space_Station (赞：1)

# 思路
要保证不输，就要让 `Bessie` 知道 `Elsie` 的策略并处处针对。

怎么处处针对呢。我们开两个数组 $even$ 和 $odd$。分别表示当 `Elsie` 选择 `Even` 和 `Odd` 时他最坏情况下会赚多少（亏则为负）。  
$$even_i = {\min}^{j = 1}_k (-a_{i,j}[a_{i,j}\mod 2 = 1] + a_{i,j}[a_{i,j}\mod 2 = 0]$$
$$odd_i = {\min}^{j = 1}_k (-a_{i,j}[a_{i,j}\mod 2 = 0] + a_{i,j}[a_{i,j}\mod 2 = 1]$$

容易知道，最优决策为 $\max(odd_i, even_i)$。记 $suf_i$ 为其后缀和。

需注意，由于不能欠钱，应在计算 $suf_i$ 时随时对 $0$ 取 $\max$。

最终判断能不能取 `Even`，若能，取之。  
否则，判 `Odd`，若能，取之。  
若亦不能，是为 `-1`。
# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const long long N = 3e5 + 5;
long long T;
string ans;
long long n, m, k, x[5];
long long odd[N], even[N], suf[N];

int main()
{
	long long i, j;
	cin >> T;

	while(T--)
	{
		cin >> n >> m >> k;
		long long ps = n;
		suf[m + 1] = 0;
		ans = "";
		
		for(i = 1; i <= m; i++)
		{
			even[i] = odd[i] = 1e9;

			for(j = 1; j <= k; j++)
			{
				cin >> x[j];
				
				if(x[j] % 2 == 1)
					even[i] = min(even[i], -x[j]);
				else
					odd[i] = min(odd[i], -x[j]);
			}

			if(even[i] == 1e9)
				for(j = 1; j <= k; j++)
					even[i] = min(even[i], x[j]);
			if(odd[i] == 1e9)
				for(j = 1; j <= k; j++)
					odd[i] = min(odd[i], x[j]);
		}
		
		for(i = m; i >= 1; i--)
			suf[i] = min(0ll, suf[i + 1] + max(even[i], odd[i]));
		
		if(suf[1] + n <= 0)
		{
			cout << "-1\n";
			continue;
		}
		
		for(i = 1; i <= m; i++)
		{
			if(ps + even[i] + suf[i + 1] > 0 && ps + even[i] > 0)
			{
				ans += "Even ";
				ps += even[i];
			}
			else if(ps + odd[i] + suf[i + 1] > 0 && ps + odd[i] > 0)
			{
				ans += "Odd ";
				ps += odd[i];
			}
			else
			{
				cout << -1;
				break;
			}
		}
		
		if(i == m + 1)
			cout << ans;

		cout << "\n";
	}
	return 0;
}
```

---

## 作者：GFyyx (赞：0)

### 解题思路
先考虑最坏情况，正如前面大佬所说，在博弈时，双方采用最佳策略。

Elsie 猜偶数时 Bessie 拿出的是最大的奇数，没有奇数拿出的就是最小的偶数，Elsie 猜奇数时 Bessie 拿出的是最大的偶数，没有偶数拿出的就是最小的奇数。

既然大佬们用的都是 DP 做法，我在这里给一个返悔贪心的解法。

### 思想逻辑
题目要求字典序最大，贪心地想，能选偶数就选偶数，无法选偶数才选奇数，选奇数的时间越晚越好。

假设我们先无脑选偶数，当我们发现选完偶数开销超过 $N$，我们再从后往前考虑是否要将以前所选的偶数改为奇数。

对于每一次开销更大的偶数选择，先进后出，使用栈记录下来，如果栈空仍然违法，则代表一定会亏光，输出非法值。

### 代码
贪心的思路其实不难，难在代码实现上的小边界条件，不建议直接对着代码写题。

```
#include <iostream>
#include <stack>
using namespace std;
const int maxn=3e5+1; 
int n,m,k,me[maxn],mo[maxn];//cost of choosing even & odd
bool ans[maxn];
void solve(){
	cin >> n >> m >> k;
	stack<int> st; 
	for(register int i=1,tot=0; i<=m; i++){
		me[i]=-maxn;mo[i]=-maxn;
		for(int j=1,x; j<=k; j++){
			cin >> x;
			if(x&1){
				me[i]=max(me[i],x);
				mo[i]=max(mo[i],-x);
			}else{
				mo[i]=max(mo[i],x);
				me[i]=max(me[i],-x);
			}
		}
		if(tot+me[i]<n){
			tot+=me[i];
			if(me[i]>mo[i]) st.push(i);
		}else if(tot+mo[i]<n){
			tot+=mo[i];
			ans[i]=1; 
		}else{
			int pos=i;
			if(me[i]<=mo[i]){
				while(tot+me[i]>=n){
					if(st.empty()){
						cout << "-1\n";
						return;
					}
					pos=st.top();st.pop();
					tot+=mo[pos]-me[pos];//反悔去选奇数
					ans[pos]=1;
				}
				tot+=me[i];
			}else{
				while(tot+mo[i]>=n){
					if(st.empty()){
						cout << "-1\n";
						return;
					}
					pos=st.top();st.pop();
					tot+=mo[pos]-me[pos];
					ans[pos]=1;
				}
				if(tot+me[i]<=m) tot+=me[i]-mo[i],st.push(i);
				else tot+=mo[i],ans[i]=1;
			}
		}
	}
	for(register int i=1; i<=m; i++){
		if(ans[i]) cout << "Odd";
		else cout << "Even";
		if(i<m) cout << ' ';
		else cout << '\n';
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int q; cin >> q;
	while(q--) solve();
}
```

---

## 作者：not_so_littlekayen (赞：0)

在看到这道题时，我的第一反应是用 DFS 来实现奇偶数的划分，然后加了一个最优性剪枝。但是在 $M≤3⋅10^ 
5
 $ 的数据下会超时。下面是代码。
```cpp
//56pts
#include <bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
struct round{
	int emax, emin, omax, omin;
}a[300005];
int be[300005], bo[300005];
int ch[300005];int n, m, k;
short route[300005];
bool flag = 0;
void dfs(int pos, int cnt)
{
	if(flag)return ;
	if(cnt <= 0)return ;
	if(cnt <= ch[pos]&&ch[pos] != 0)return ;
	ch[pos] = cnt;
	if(pos > m)
	{
		for(int i = 1;i <= m;i++)
			if(route[i] == 0)cout << "Even ";
			else cout << "Odd ";
		puts("");
		flag = 1;
		return ;
	}
	//even
	route[pos] = 0;
	cnt += be[pos];
	dfs(pos+1, cnt);
	cnt -= be[pos];
	//odd
	route[pos] = 1;
	cnt += bo[pos];
	dfs(pos+1, cnt);
	cnt -= bo[pos];
	route[pos] = -1;
}
int main()
{
	int t;
	cin >> t;
	memset(route, -1, sizeof(route));
	while(t--)
	{
		flag = 0;
		memset(ch, 0, sizeof(ch));
		int best = 0;
		cin >> n >> m >> k;
		for(int i = 1;i <= m;i++)
			a[i].emax = -inf, a[i].omax = -inf, a[i].emin = inf, a[i].omin = inf;
		for(int i = 1;i <= m;i++)
		{
			bool even = 0, odd = 0;
			for(int j = 1;j <= k;j++)
			{
				int num;
				cin >> num;
				if(num%2 == 0)a[i].emax = max(a[i].emax, num),a[i].emin = min(a[i].emin, num),even = 1;
				else a[i].omax = max(a[i].omax, num),a[i].omin = min(a[i].omin, num),odd = 1;
			}
			if(odd == 0)be[i] = a[i].emin, bo[i] = -a[i].emax, best -= a[i].emin;
			else if(even == 0)bo[i] = a[i].omin, be[i] = -a[i].omax, best -= a[i].omin;
			else be[i] = -a[i].omax, bo[i] = -a[i].emax, best += min(a[i].omax, a[i].emax);
		}
		if(best >= n)
		{
			cout << -1 << endl;
			continue;
		}
		dfs(0, n);
		if(!flag)cout << -1 << endl;
	}
	return 0;
}
```
后来，我加上了后缀和优化。将本来不是那么优秀的时间复杂度提升到了 $O(M)$ 的速度。


后缀和优化的实现：
```cpp
for(int i = m;i >= 1;i--)
        sum[i] = max(0, sum[i+1]+add[i]);
//add[i]是每回合的最优分数，即每回合best加上的数
```

这时候有读者就要问了：为什么 $sum_i$ 还要和 $0$ 进行比较呢？DFS 中不是也可以判断先负后正的异常情况吗？

确实，你说的是没错。但是可不可能存在这样一种情况，使得程序在看到之后最优情况下为正实则中间中间弹珠数为负数的情况呢？在这种情况下，我们就需要回溯，这样就无法保证 $O(M)$ 的时间复杂度了。

修改后的代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
struct round{
	int emax, emin, omax, omin;
}a[300005];
int be[300005], bo[300005], sum[300005], add[300005];
int ch[300005];int n, m, k;
short route[300005];
bool flag = 0;
void dfs(int pos, int cnt)
{
	if(flag)return ;
	if(cnt <= 0)return ;
	if(cnt-sum[pos] <= 0)return ;
	if(cnt <= ch[pos]&&ch[pos] != 0)return ;
	ch[pos] = cnt;
	if(pos > m)
	{
		for(int i = 1;i <= m;i++)
			if(route[i] == 1)cout << "Odd ";
			else cout << "Even ";
	        puts("");
		flag = 1;
		return ;
	}
	//even
	route[pos] = 0;
	cnt += be[pos];
	dfs(pos+1, cnt);
	cnt -= be[pos];
	//odd
	route[pos] = 1;
	cnt += bo[pos];
	dfs(pos+1, cnt);
	cnt -= bo[pos];
	route[pos] = -1;
}
int main()
{
	int t;
	cin >> t;
	memset(route, -1, sizeof(route));
	while(t--)
	{
		flag = 0;
		memset(ch, 0, sizeof(ch));
		memset(sum, 0, sizeof(sum));
		int best = 0;
		cin >> n >> m >> k;
		for(int i = 1;i <= m;i++)
			a[i].emax = -inf, a[i].omax = -inf, a[i].emin = inf, a[i].omin = inf;
		for(int i = 1;i <= m;i++)
		{
			bool even = 0, odd = 0;
			for(int j = 1;j <= k;j++)
			{
				int num;
				cin >> num;
				if(num%2 == 0)a[i].emax = max(a[i].emax, num),a[i].emin = min(a[i].emin, num),even = 1;
				else a[i].omax = max(a[i].omax, num),a[i].omin = min(a[i].omin, num),odd = 1;
			}
			int save = best;
			if(odd == 0)be[i] = a[i].emin, bo[i] = -a[i].emax, best -= a[i].emin;
			else if(even == 0)bo[i] = a[i].omin, be[i] = -a[i].omax, best -= a[i].omin;
			else be[i] = -a[i].omax, bo[i] = -a[i].emax, best += min(a[i].omax, a[i].emax);
			add[i] = best-save;
		}
		for(int i = m;i >= 1;i--)
			sum[i] = max(0, sum[i+1]+add[i]);
		if(best >= n)
		{
			cout << -1 << endl;
			continue;
		}
		dfs(0, n);
		if(!flag)cout << -1 << endl;
	}
	return 0;
}
```

---

## 作者：zcr0202 (赞：0)

## 题目大意

有两个人在玩游戏，给你 $n$ 和 $m$ 和 $k$，每轮对手会给你 $k$ 个数。然后你要猜测是奇数还是偶数，猜对加上那个数，猜错减去那个数，求在最坏情况下分数大于零的操作方案，并且字典序最小。

## 解题思路

首先我们考虑贪心算法，结果发现会答案错误，为什么？因为如果使用贪心算法就无法保证每一步的分数都小于零，只可以保证最后一步小于零，所以我们可以用 DP 算法。分别求出选奇数和偶数分别可以获得的分数，接着再用贪心解决字典序问题，于是我们可以手切灰题了。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 1;
const int inf = 9999999;
int T;
int n, m, k, d;
int f[N][2], ans[N], ff[N];
signed main() {
// 	freopen("Moorbles.in", "r", stdin);
// 	freopen("Moorbles.out", "w", stdout);
	cin >> T;
	while(T--) {
		memset(ans, 0, sizeof(ans));
		d = 0;
		bool p = 0;
		cin >> n >> m >> k;
		int t = n;
		ff[m + 1] = 0;
		for(int i = 1; i <= m; i++) {
			f[i][0] = f[i][1] = inf;
			int x[10];
			memset(x, 0, sizeof(x));
			for(int j = 1; j <= k; j++) {
				cin >> x[j];
				if(x[j] % 2 == 1) {
					f[i][0] = min(f[i][0], -x[j]);
				}
				else {
					f[i][1] = min(f[i][1], -x[j]);
				}
			}
			if(f[i][0] == inf) {
				for(int j = 1; j <= k; j++) {
					f[i][0] = min(f[i][0], x[j]);
				}
			}
			if(f[i][1] == inf) {
				for(int j = 1; j <= k; j++) {
					f[i][1] = min(f[i][1], x[j]);
				}
			}
		}
		for(int i = m; i >= 1; i--) {
			ff[i] = min(0ll, ff[i + 1] + max(f[i][0], f[i][1]));
		}
//		for(int i = 1; i <= m; i++) {
//			cout << f[i][0] << " ";
//		}
//		cout << '\n';
		if(ff[1] + n <= 0) {
			cout << "-1\n";
		} else {
			for(int i = 1; i <= m; i++) {
				if(t + f[i][0] + ff[i + 1] > 0 && t + f[i][0] > 0) {
					ans[++d] = 0;
					t += f[i][0];
				}
				else if(t + f[i][1] + ff[i + 1] > 0 && t + f[i][1] > 0) {
					ans[++d] = 1;
					t += f[i][1];
				}
				else {
					p = 1;
					cout << "-1\n";
					break;
				}
			}
			if(!p) {
				for(int i = 1; i <= d; i++) {
					if(ans[i] == 0) {
						cout << "Even ";
					} else {
						cout << "Odd ";
					}
				}
				cout << '\n';
			}
		}
	}
	return 0;
}
```

---

## 作者：aaron0919 (赞：0)

# [P10192 の题解](https://www.luogu.com.cn/problem/P10192)

### 理性分析

这道题要求字典序最小并保证不输，我们先考虑最坏情况。

最坏情况就是猜偶数时是最大的奇数（扣最多），没有就出最小偶数（加最少），反之亦然。

我们求出每个点最坏情况猜奇数得分和偶数得分最大的那个，再求一遍后缀和进行贪心。

贪心很简单，只要不输就就选 `Even`，因为字典序要求最小。

### 代码实现

注意行末无空格，结尾有换行。

### code

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3e5 + 10;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int n, m, k;
int a[N][2], mn[N], ans[N];

void solve()
{
    memset(a, 0, sizeof(a));
    memset(mn, 0, sizeof(mn));
    memset(ans, 0, sizeof(ans));
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 1; i <= m; i++)
    {
        a[i][0] = INF;
        a[i][1] = INF;
        for (int j = 1, x; j <= k; j++)
        {
            scanf("%d", &x);
            a[i][x & 1] = min(a[i][x & 1], x);
            a[i][(x & 1) ^ 1] = min(a[i][(x & 1) ^ 1], -x);
        }
    }
    for (int i = m; i >= 1; i--)
    {
        mn[i] = min(0, max(a[i][0], a[i][1]) + mn[i + 1]);
    }
    if (n + mn[1] <= 0)
    {
        puts("-1");
        return;
    }
    for (int i = 1; i <= m; i++)
    {
        int p = (n + a[i][0] + mn[i + 1] <= 0) ? 1 : 0;
        ans[i] = p;
        n += a[i][p];
    }
    for (int i = 1; i <= m; i++)
    {
        if (ans[i] == 0)
        {
            printf("Even%c", " \n"[i == m]);
        }
        else
        {
            printf("Odd%c", " \n"[i == m]);
        }
    }
    return;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("Moorbles.in", "r", stdin);
    freopen("Moorbles.out", "w", stdout);
#endif

    int T;
    scanf("%d", &T);
    while (T--)
    {
        solve();
    }

    return 0;
}
```

---

## 作者：不知名用户 (赞：0)

题意：最开始有 $n$ 分，有 $m$ 轮，每轮对手会亮出事先输入的 $k$ 个数之一。然后你要猜测是奇数还是偶数，猜对分数加上那个数，猜错减去，求在**最劣情况下**保证**每轮**过后分数大于零的情况下最小会操作字典序（偶数字典序小于奇数）。

显然你猜奇数，对方在有偶数的情况下亮最大的偶数，否则亮最小的奇数，反之同理。我的代码用 $e_i,o_i$ 表示第 $i$ 轮亮奇数/偶数时的最劣收益（可能为负）。

```cpp
for(i=1;i<=m;i++)
{
	for(j=1;j<=k;j++)
	{
		cin>>a[j];
		if(a[j]&1) o[i] = min(o[i],a[j]), e[i] = min(e[i],-a[j]);
		else e[i] = min(e[i],a[j]), o[i] = min(o[i],-a[j]);
	}
}
```

然后你要尽可能把猜奇数变成猜偶数，为了保证之后不会掉到 0 分一下，记 $w_i$ 表示开始分数为零，直到游戏结束的分数最小值（不是最终值，因为可能半路输）。所以 $w_i=\min(\max(e_i,o_i)+w_{i+1},0)$。第 $i$ 轮操作结束分数 $score_i$ 可行当且仅当 $score_i+w_{i+1}>0$。然后从前往后贪心即可，循环同时记录当前在不会输的情况下字典序最小时剩下的分数。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 3e5 + 10;

int o[N], e[N], a[10], w[N];

int Main()
{
	int n, m, k, i, j;
	cin>>n>>m>>k;
	memset(o,0x3f,sizeof o), memset(e,0x3f,sizeof e);
	for(i=1;i<=m;i++)
	{
		for(j=1;j<=k;j++)
		{
			cin>>a[j];
			if(a[j]&1) o[i] = min(o[i],a[j]), e[i] = min(e[i],-a[j]);
			else e[i] = min(e[i],a[j]), o[i] = min(o[i],-a[j]);
		}
		w[i] = max(e[i],o[i]);
	}
	w[m+1] = 0;
	for(i=m;i>=1;i--) w[i] = min(w[i]+w[i+1],0ll);
	if(n+w[1]<=0) return cout<<"-1\n", 0;
	for(i=1;i<=m;i++)
	{
		n += max(e[i],o[i]);
		if(e[i]>=o[i]) cout<<"Even ";
		else if(n-o[i]+e[i]+w[i+1]>0) cout<<"Even ", n = n - o[i] + e[i];
		else cout<<"Odd ";
		assert(n>0);
	}
	cout<<'\n';
	return 0;
}

signed main()
{
	int t;cin>>t;
	while(t--) Main();
	return 0;
}
```

---

## 作者：OAer (赞：0)

这题我们要采用一种非常常用的策略：考虑最坏情况。假设贝茜已经知道你要选什么，她可以选择对她来说最优的弹珠组合。（此处假设你是艾尔西）

在任意回合，若你选择 `odd`，贝茜肯定会选择能使你扣分最多的组合，此时把它记录下来。反之，若你选择 `even`，你也可以知道这回合你最多会被扣多少分。

到了决策环节时，选择能使你扣分最少的方案。若这种方案都会使你的弹珠数量小于等于 $0$，就可以直接输出 `-1`。

不过题目要求你输出字典序最小的方案，就不能看哪种方案剩的弹珠最多了。

在你到达第 $i$ 回合时，你肯定是如果能选 `even` 就选 `even`，否则选 `odd`。假设到达这一个回合时你的弹珠数量有 $N'$，你选择 `even` 的话会获得 $f$ 颗弹珠（损失弹珠为负数）。那么你选了 `even` 之后就会有 $(N'+f)$ 颗弹珠。  
最大的问题是：选了 `even` 会不会使你失败？若你害怕失败，后面还是按最优解执行稳妥。若 $(N'+f)$ 再加上后面采用最优办法获得的弹珠数小于等于 $0$ 了，那么就不能选，反之就选（前面更好，总体更好）。

这里，我们可以使用后缀和统计最优解会得到的弹珠数量。不过要注意一下，若弹珠数变成负数再得到弹珠也是不可能的。所以，后缀和的时候若为正数，则变成 $0$。代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
int k,m;
ll n;
ll f[500005][2];	//选择odd/even会得到的（损失的）弹珠数，odd为1，even为0 
ll a[500005][10];
ll suf[500005];	//后缀和数组 
void forcase(){
	scanf("%lld %d %d",&n,&m,&k);
	for(int i=0;i<=m+1;i++){	//多测要清空 
		f[i][0]=f[i][1]=0x3f3f3f3f3f3f3f3f;
		suf[i]=0;
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=k;j++){
			scanf("%lld",&a[i][j]);
			int oe=a[i][j]&1;	//判断奇偶性 
			f[i][oe]=min(f[i][oe],a[i][j]);	//猜对了就加 
			f[i][oe^1]=min(f[i][oe^1],-a[i][j]);	//猜错了就减 
		}
	}
	for(int i=m;i>=1;i--)	//后缀和 
		suf[i]=min(0LL,max(f[i][0],f[i][1])+suf[i+1]);
	if(n+suf[1]<=0){	//无解 
		printf("-1\n");
		return;
	}
	for(int i=1;i<=m;i++){
		if(n+f[i][0]+suf[i+1]<=0) printf("Odd "),n+=f[i][1];	//实在不行输出odd 
		else printf("Even "),n+=f[i][0];	//要不然就输出even 
	}
	printf("\n");
	return; 
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--) forcase();
	return 0;
}
```

---

## 作者：Red_river (赞：0)

### 题目大意
没什么好说的，就是博弈论，但是不是那么的贪，要分类讨论。具体可直接看分析思路和代码理解。
### 题意分析
我们要给每一步剩余的弹珠求一个后缀最小值，为了让字典序最小，就要从前往后判断能不能将这一步改变成偶数。如果是偶数那么就直接跳过。如果中没有，那么就判断这一步的后缀最小值是否大于这一步奇数的最大值加上前面修改后减少弹珠的个数，情况如下：

1.  如果大于，那么就直接改成选偶数，然后更新修改后减少弹珠的个数。

1. 不变，继续判断。

### CODE
```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
#define N 300005
#define INF 2147483647
#define f(x,k,y,z) for(int x=k;x<=y;x+=z)
using namespace std;
int n,m,k,jk,pop[N];
int tot,dis[N],wis[N],vis[N],f[N];
void read(int &x)
{
	x=0;int ff=1;
	char ch=getchar();
	while (ch<'0'||ch>'9')
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	x*=ff;return;
}

void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}

int mymax(int x,int y){
	return x>y?x:y;
}

int mymin(int x,int y){
	return y>x?x:y;
}

signed main()
{
	read(tot);
	while(tot--)
	{
		read(n),read(m),read(k);
		for(int i=1;i<=m;i++)
		{
			vis[i]=f[i]=INF;
			for(int j=1;j<=k;j++)
			{
				read(dis[j]);//奇偶性
				if(dis[j]%2==0) vis[i]=min(vis[i],-dis[j]);
				if(dis[j]%2==1) f[i]=min(f[i],-dis[j]);
			}
			if(vis[i]==INF) for(int j=1;j<=k;j++) vis[i]=min(vis[i],dis[j]);
			if(f[i]==INF) for(int j=1;j<=k;j++) f[i]=min(f[i],dis[j]);
		}
		wis[m+1]=0;bool flag=0;
		for(int i=m;i>=1;i--)
		wis[i]=mymin(0,wis[i+1]+max(f[i],vis[i]));
		if(wis[1]+n<=0) printf("-1\n");//不合法
		else
		{
			for(int i=1;i<=m;i++)//判断是否合法
			{
				if(n+f[i]+wis[i+1]>0&&n+f[i]>0) pop[i]=1,n+=f[i];
				else if(n+vis[i]+wis[i+1]>0&&n+vis[i]>0) pop[i]=2,n+=vis[i];
				else {flag=1,printf("-1");break;}
			}
			if(flag==0)
			{
				for(int i=1;i<=m;i++)
				{
					if(pop[i]==1) printf("Even ");//输出
					else printf("Odd ");
				}
			}
			printf("\n");
		}
	}
	return 0;
}
```

---

## 作者：Lame_Joke (赞：0)

- ### 大体思路
	这次月赛除了第一题题目大意都挺简单的，就不过多解释了。这道题要求我们让字典序最小，偶数的字典序小于奇数的字典序，不难想出，我们要尽量让前面选偶数。
    
   首先我们先做最坏的打算，也就是让最后剩余弹珠最多的方案。要求得这种方案，我们要求出可选弹珠中偶数的最小值和最大值，奇数的最小值和最大值，这四个数要存下来备用，然后最会出现三种情况：没有偶数，没有奇数，两种都有，没有偶数的时候为了让剩余弹珠最多我们必定会选择奇数，但又是最坏打算，所以我们的弹珠数只能加上这组奇数的最小值，没有奇数的时候同理。两种都有的时候我们就要比较奇数和偶数的最大值，弹珠数减去两数间的最小值，这应该也很好理解，都是在做最坏的打算。在求这个方案的过程中，如果弹珠数小于等于 $0$，那么就证明无论哪种方案，我们不能保证一定胜利，因为我们求的是能让剩余弹珠最多的最优策略。
   
   相信大家也都看出来求上面那个策略是为了判断存不存在保证胜利的方案。我们要给每一步剩余的弹珠求一个后缀最小值，然后我们为了让字典序最小，我们就要从前往后判断能不能将这一步改变成偶数。如果这一步是偶数那么就可以直接跳过。如果这一步中没有偶数，那么就判断这一步的后缀最小值是否大于这一步奇数的最大值加上前面修改后减少弹珠的个数，如果大于，那么就直接改成选偶数，然后更新修改后减少弹珠的个数，否则不变，继续判断。如果这一步中既有偶数又有奇数，那么就判断这一步的后缀最小值是否大于这一步奇数的最大值加上前面修改后减少弹珠的个数再减去这一步偶数的最大值，这里应该也挺好理解的，自己想要一下，如果可以的话同上，不可以的话就跳过。最后就可以输出答案了。
- ### 参考代码
	```cpp
	#include<bits/stdc++.h>
	using namespace std;
	long long t,n,m,k,a[5],qmx[500005],qmn[500005],jmn[500005],jmx[500005],n1,ans[500005],s,ans1[500005],cnt;
	int main()
	{
		scanf("%lld",&t);
		while(t--)
		{
			scanf("%lld%lld%lld",&n,&m,&k);
			n1=n;
			s=0;
			for(int i=1;i<=m;i++)
			{
				jmx[i]=-0x7f7f7f7f;
				jmn[i]=0x7f7f7f7f;
				qmn[i]=0x7f7f7f7f;
				qmx[i]=-0x7f7f7f7f;
				
				for(int j=1;j<=k;j++)
				{
					scanf("%d",&a[j]);
					if(a[j]%2==0)
					{
						qmx[i]=max(qmx[i],a[j]);
						qmn[i]=min(qmn[i],a[j]);
					}
					else
					{
						jmx[i]=max(jmx[i],a[j]);
						jmn[i]=min(jmn[i],a[j]);
						
					}
					
				}
				
				if(qmx[i]==-0x7f7f7f7f) n1+=jmn[i],ans[i]=1;
				else if(jmx[i]==-0x7f7f7f7f) n1+=qmn[i],ans[i]=0;
				else
				{
					if(qmx[i]<jmx[i])
					{
						ans[i]=1;
						n1-=qmx[i];
					}
					else
					{
						ans[i]=0;
						n1-=jmx[i];
					}
					if(n1<=0) s=1;
				}
				ans1[i]=n1;
			}
			if(s==1) printf("-1\n");
			else
			{
				for(int j=m-1;j>=1;j--) ans1[j]=min(ans1[j+1],ans1[j]);
				cnt=0;
				for(int i=1;i<=m;i++)
				{
					
					if(ans[i]==0) continue;
					if(qmx[i]==-0x7f7f7f7f)
					{
						if(ans1[i]-cnt-jmx[i]-jmn[i]>0)
						{
							ans[i]=0;
							cnt+=jmx[i]+jmn[i];
						}
					}
					else
					{
						if(ans1[i]-cnt+qmx[i]-jmx[i]>0)
						{
							ans[i]=0;
							cnt-=qmx[i];
							cnt+=jmx[i];
						}
					}
				}
				for(int i=1;i<=m;i++)
				{
					if(ans[i]==0) printf("Even ");
					else printf("Odd ");
				}
				printf("\n");
			}
		}
	}

---

