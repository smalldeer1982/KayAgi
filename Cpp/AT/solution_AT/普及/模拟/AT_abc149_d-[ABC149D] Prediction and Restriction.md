# [ABC149D] Prediction and Restriction

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc149/tasks/abc149_d

高橋君は、ゲームセンターで「じゃんけんバトル」というゲームをプレイすることにしました。このゲームのルールは以下の通りです。

- プレイヤーは筐体と $ N $ 回じゃんけんを行う (あいこの場合も $ 1 $ 回のジャンケンと数える)。
- プレイヤーがじゃんけんで勝った場合、プレイヤーは出した手に応じて以下のスコアを得る (あいこや負けは $ 0 $ 点)。
  - グーで勝った場合、 $ R $ 点
  - チョキで勝った場合、 $ S $ 点
  - パーで勝った場合、 $ P $ 点
- ただし、ちょうど $ K $ 回前のじゃんけんで出した手と同じ手を出すことはできない。( $ K $ 回目までのじゃんけんでは好きな手を出せる。)

筐体は、各回のジャンケンで出す手をゲーム開始前に決定します。能力者である高橋君は、ゲーム開始前にこれをすべて読み取りました。

高橋君が読み取った情報は文字列 $ T $ として与えられます。$ T $ の $ i(1\ \leq\ i\ \leq\ N) $ 文字目が `r` のときは $ i $ 回目のじゃんけんで筐体がグーを出すことを、`s` のときはチョキを出すことを、`p` のときはパーを出すことを表します。

高橋君が $ N $ 回のじゃんけんで出す手を最適に選んだとき、ゲーム終了までに最大で合計何点を得られるでしょうか。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ K\ \leq\ N-1 $
- $ 1\ \leq\ R,S,P\ \leq\ 10^4 $
- $ N,K,R,S,P $ は全て整数である。
- $ |T|\ =\ N $
- $ T $ に含まれる文字は `r` , `s` , `p` のいずれかである。

### Sample Explanation 1

筐体は、{グー、チョキ、グー、パー、グー} と手を出します。 これに対して、例えば {パー、グー、グー、チョキ、パー} と出せば、$ 27 $ 点を獲得できます。 これより大きい点は獲得できないので、$ 27 $ を出力します。

## 样例 #1

### 输入

```
5 2
8 7 6
rsrpr```

### 输出

```
27```

## 样例 #2

### 输入

```
7 1
100 10 1
ssssppr```

### 输出

```
211```

## 样例 #3

### 输入

```
30 5
325 234 123
rspsspspsrpspsppprpsprpssprpsr```

### 输出

```
4996```

# 题解

## 作者：kkxacj (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc149_d)

#### 思路

如果 $t_{i}$ 与 $t_{i - k}$ 相同，那么选 $t_{i - k}$ 最优，因为有可能 $t_{i}$ 与 $t_{i + k}$ 相同，然后能赢尽量赢，否则出与 $t_{i + k}$ 相反的，因为要尽可能多赢，我们模拟即可。

#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,r,s,p,ans;
string t,t1;
int main()
{
	cin >> n >> k >> r >> s >> p >> t;
	for(int i = 0;i < n;i++)
	{
		if(i < k)
		{
			if(t[i] == 'r') t1 += 'p',ans += p;
			else if(t[i] == 'p') t1 += 's',ans += s;
			else t1 += 'r',ans += r;
		}
		else
		{
			if(t[i] == 'r') 
			{
				if(t1[i - k] != 'p') t1 += 'p',ans += p;
				else t1 += 'w';//可以出其它两个中任意一个，由 t[i+k] 决定
			}
			else if(t[i] == 'p') 
			{
				if(t1[i - k] != 's') t1 += 's',ans += s;
				else t1 += 'w';
			}
			else 
			{
				if(t1[i - k] != 'r') t1 += 'r',ans += r;
				else t1 += 'w';
			}
		}
	}
	cout << ans;
	return 0;
}

```


---

## 作者：Sirkey (赞：2)

这道题太简单了。

对于前 $k$ 个，没有限制，那肯定能赢就赢。

对于后面的，唯一的限制是前面 $k$ 轮和当前轮不一样。

我们考虑前面能够赢的是否一样。

如果一样，那前面那一轮赢还是当前轮赢都无所谓，所以我们要记一下赢的情况。

不一样直接用。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define tell(ans) out(ans),printf("\n");
#define say(ans) out(ans),printf(" ");
#define pb push_back
#define mid (l+r)>>1
//
//
//
using namespace std;
inline ll read() {
	ll f=0,t=0;
	char c=getchar();
	while(!isdigit(c)) t|=(c=='-'),c=getchar();
	while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
	return t?-f:f;
}
inline void out(ll x) {
	if(x<0) putchar('-');
	if(x>9) out(x/10);
	putchar('0'+x%10);
}
const ll MX=1e5+10;
ll anss[MX];
int main() {
	ll n=read(),k=read(),r=read(),s=read(),p=read();
	string st;
	cin>>st;
	ll ans=0;
	FOR(i,0,n-1) {
		if(i<k) {
			anss[i]=1;
			if(st[i]=='r') ans+=p;
			if(st[i]=='p') ans+=s;
			if(st[i]=='s') ans+=r;
		} else {
			if(st[i]==st[i-k]) {
				if(anss[i-k]==0) {
					anss[i]=1;
					if(st[i]=='r') ans+=p;
					if(st[i]=='p') ans+=s;
					if(st[i]=='s') ans+=r;
				} else anss[i]=0;
			} else {
				anss[i]=1;
				if(st[i]=='r') ans+=p;
				if(st[i]=='p') ans+=s;
				if(st[i]=='s') ans+=r;
			}
		}
//		cout<<ans<<" ";
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Chinese_zjc_ (赞：1)

考虑第 $i$ 轮只受到第 $i-k$ 轮的影响.

因此我们分开计算它们的分数.

定义 $DP[i][0/1/2]$ 分别表示第 $i$ 轮出 石头/剪刀/布 ,第 $i$ 轮,第 $i-k$ 轮,第 $i-2k$ 轮,…,最大能得到的分数的总和.

那么状态转移就十分地显然了.
$$
\begin{cases}
DP[i][j]=[j\ can\ win]\times w[j]\\
DP[i][j]=\max\{DP[i-k][l(l\not=j)]\}+[j\ can\ win]\times w[j]\\
\end{cases}
$$
最后再把它们合并,求出:
$$
\sum_{i+k>n}\max\{DP[i][0],DP[i][1],DP[i][2]\}
$$
这样这题就 $AC$ 了.

$Code$:

```cpp
//This code was made by Chinese_zjc_.
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#define int long long
#define INF 0x3fffffffffffffff
using namespace std;
string t;
int n,k,w[3],a[100001],dp[3][100001],ans;
signed main()
{
	std::ios::sync_with_stdio(false);
	cin>>n>>k>>w[1]>>w[2]>>w[0]>>t;
	for(int i=0;i<n;++i)
	{
		if(t[i]=='r')
		{
			a[i+1]=0;
		}
		if(t[i]=='s')
		{
			a[i+1]=1;
		}
		if(t[i]=='p')
		{
			a[i+1]=2;
		}
	}
	for(int i=1;i<=k;++i)
	{
		if(a[i]==0)
		{
			dp[0][i]=w[0];
			dp[1][i]=0;
			dp[2][i]=0;
		}
		if(a[i]==1)
		{
			dp[0][i]=0;
			dp[1][i]=w[1];
			dp[2][i]=0;
		}
		if(a[i]==2)
		{
			dp[0][i]=0;
			dp[1][i]=0;
			dp[2][i]=w[2];
		}
		for(int j=i+k;j<=n;j+=k)
		{
			if(a[j]==0)
			{
				dp[0][j]=max(dp[1][j-k],dp[2][j-k])+w[0];
				dp[1][j]=max(dp[0][j-k],dp[2][j-k]);
				dp[2][j]=max(dp[0][j-k],dp[1][j-k]);
			}
			if(a[j]==1)
			{
				dp[0][j]=max(dp[1][j-k],dp[2][j-k]);
				dp[1][j]=max(dp[0][j-k],dp[2][j-k])+w[1];
				dp[2][j]=max(dp[0][j-k],dp[1][j-k]);
			}
			if(a[j]==2)
			{
				dp[0][j]=max(dp[1][j-k],dp[2][j-k]);
				dp[1][j]=max(dp[0][j-k],dp[2][j-k]);
				dp[2][j]=max(dp[0][j-k],dp[1][j-k])+w[2];
			}
		}
	}
	for(int i=n;i+k>n;--i)
	{
		ans+=max(max(dp[0][i],dp[1][i]),dp[2][i]);
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：L_zaa_L (赞：1)

## 题意
知道对方出的手势，以及你出石头、剪刀、布赢了后分别能得到的分数，且第 $i$ 次和第 $i-k$ 次不能相同（$i>k$），求最多能得到多少分数。
## 做法
可以考虑贪心，因为两个不能一样，那么也就是对方两次手势不能一样，那么至少要丢弃一个，而最优的肯定是几个连续的数中，第一个赢，第二个不赢，第三个不赢……那么就可以用一个数组来记录上一轮选的哪个，如果相同，就选一个与接下来一轮不一样的（保证能继续最优）。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define mid ((l+r)>>1)
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
#define modj(x) ((x)-=((x)>=MOD)?MOD:0)
#define qmin(x,y) ((x)=min((x),(y)))
#define qmax(x,y) ((x)=max((x),(y)))
using namespace std;
inline ll read(){
	ll t=0,f=0;char v=getchar();
	while(!isdigit(v))f|=(v=='-'),v=getchar();
	while(isdigit(v))t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
inline void write(ll x){
	if(x<0){x*=-1; putchar('-');}
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
char a[1000005];
int n,m,k,r,s,p;
int ans;
int now[1000005];//now是指上一个是哪个手势
signed main(){
	n=read(),k=read();
	r=read(),s=read(),p=read();
	cin>>a;
	FOR(i,0,min(n-1,k-1)){
		if(a[i]=='r') ans+=p,now[i%k]=2;//r 2,s 0,p 1
		if(a[i]=='s') ans+=r,now[i%k]=0;
		if(a[i]=='p') ans+=s,now[i%k]=1;
	}//先将第一遍的所有都算赢，保证最优
	FOR(i,k,n-1){
		if(a[i]=='r'&&now[i%k]!=2) ans+=p,now[i%k]=2;
		else if(a[i]=='r'&&now[i%k]==2){
			if(a[i+k]=='r') now[i%k]=1;
			if(a[i+k]=='s') now[i%k]=1;
			if(a[i+k]=='p') now[i%k]=2;
		}//选一个与上一个和下一个都不一样的数
		if(a[i]=='s'&&now[i%k]!=0) ans+=r,now[i%k]=0;
		else if(a[i]=='s'&&now[i%k]==0){
			if(a[i+k]=='r') now[i%k]=1;
			if(a[i+k]=='s') now[i%k]=1;
			if(a[i+k]=='p') now[i%k]=2;
		}
		if(a[i]=='p'&&now[i%k]!=1) ans+=s,now[i%k]=1;
		else if(a[i]=='p'&&now[i%k]==1){
			if(a[i+k]=='r') now[i%k]=0;
			if(a[i+k]=='s') now[i%k]=2;
			if(a[i+k]=='p') now[i%k]=0;
		}
	}
	cout<<ans;
    return 0;
}

```

---

## 作者：highkj (赞：0)

# 前言
某个聪明人说这是 Div.2 的 $A$。
# 思路
我们由于对于 $i$ 和 $i-k$ 出的手势不能相同，所以我们可以将前 $k-1$ 个不管了，直接按照赢得方法出。然后对于后面的，我们若第 $i$ 个对手出的和第 $i-k$ 个出的一样，但是如果前一个又由于之前的而改变了那么我们可以继续出想出的那一个手势。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
long long n,k,res;
string s="";
int a1,a2,a3;
int a[4]= {0};
bool vis[1000010];
int main() {
	cin>>n>>k;
	a1=a2=a3=0;
	cin>>a[1]>>a[2]>>a[3];
	cin>>s;
	for(int i=0; i<k; ++i) {
		if(s[i]=='s') res+=a[1];
		if(s[i]=='r') res+=a[3];
		if(s[i]=='p') res+=a[2];
	}
	for(int i=k; s[i]; ++i) {
		if(s[i]==s[i-k]) {
			if(!vis[i-k]) vis[i]=1; //没改只能改这一个
			else {
				if(s[i]=='s') res+=a[1]; //随意出
				if(s[i]=='r') res+=a[3];
				if(s[i]=='p') res+=a[2];
			}
		} else {
			if(s[i]=='s') res+=a[1];
			if(s[i]=='r') res+=a[3];
			if(s[i]=='p') res+=a[2];
		}
	}
	cout<<res<<endl;
	return false;
}
```

---

## 作者：Populus_euphratica (赞：0)

## 题意
进行石头剪刀布游戏，已知对方的出法，我方如果出石头获胜得 $R$ 分，出布得 $P$ 分，出剪刀得 $S$ 分，要求第 $i(i < k)$ 此出拳不能与第 $i-k$  时，可以次相同，问最多能得多少分（$r$ 表示石头，$s$ 表示剪刀，$p$ 表示布）。
## 做法
经过分析可以得到想要得分只有一种出法，所以如果对方出的第 $i$ 次和第 $i+k$ 次相同，我们第 $i$ 次出可以赢的，第 $i+k$ 此出相同的。但如果 $i$,$i+k$,$i+2k$ 都相同，可以 $i$ 出可以赢的，$i+k$ 与对方出的相同，$i+2k$ 出可以赢的，所以可得如下条件：\
1、如果 $i$ 等于 $i+k$ 且 $i$ 没被标记，标记 $i+k$。\
2、如果 $i$ 没有标记，加上得分。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
long long ans;
int vis[100010];
int r,s,p;
char a[100010];
signed main()
{
    cin>>n>>k>>r>>s>>p;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=n;i++)
    {
        if(a[i+k]==a[i]&&vis[i]==0)
            vis[i+k]=1;
        if(vis[i]==0)
        {
            if(a[i]=='r')
                ans+=p;
            if(a[i]=='s')
                ans+=r;
            if(a[i]=='p')
                ans+=s;
         }
    }
	cout<<ans;
    cout<<endl;
    return 0;
}

```


---

## 作者：封禁用户 (赞：0)

## 思路

直接模拟就可以啦。这里我们要知道一个常识性的问题：石头赢剪刀，剪刀赢布，布赢石头。同时，在这道题里，我们还要知道一件事，若我们选了 $s[i]$，则在 $s[i+k]$ 与其相同时，$s[i+k]$ 是不能赢的。所以我们可以正着枚举 $s$，在 $s[i+k]$ 与 $s[i]$ 相同时标记一下 $s[i+k]$ 即可。

## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int A,B,C;
string s;
int a[10];
int ans;
bool vis[1000000];
int main()
{
	cin>>n>>k>>A>>B>>C;
	cin>>s;
	a[1]=C,a[2]=A,a[3]=B;
	for(int i=0;i<s.size();i++)
	{
    	if(vis[i]==1) continue;
		if(s[i]=='r')
		{
			ans+=a[1];
			if(s[i+k]=='r') vis[i+k]=1;
		}
		else if(s[i]=='s')
		{
			ans+=a[2];
		 	if(s[i+k]=='s') vis[i+k]=1;
	
		}
		else
		{
			ans+=a[3];
            if(s[i+k]=='p') vis[i+k]=1;
	
		}
	}
	cout<<ans;
}
```


---

## 作者：zhujiangyuan (赞：0)

我的这个方法比题解区已有的代码都要简单些。

其实就是个贪心。

我们用 $rr$ 表示出石头赢了所得的分数，$pp$ 表示出布赢了所得的分数，$ss$ 表示出剪刀赢了所得的分数。

对于每轮对方出的手势，一般情况下：
```cpp
if(s[i]=='r') ans+=pp;//如果对方出石头，我们出布
if(s[i]=='p') ans+=ss;//如果对方出布，我们剪刀
if(s[i]=='s') ans+=rr;//如果对方出剪刀，我们出石头
```

题目中有一点要注意：
>你第 $i-k$ 轮和第 $i(i>k)$ 轮出的手势不能相同.

我们做一个判断：
```cpp
if(s[i+k]==s[i]) s[i+k]='f'; 
//如果第i轮和第i+k轮对方出的手势相同，我们就要对第i+k个进行标记，这样第i+k轮就不会出手势，直接跳过。而第i+k*2轮则不受影响。
```
最后输出 $ans$ 即可。

完整代码：
```cpp
#include<bits/stdc++.h>
#define rd(n) scanf("%d",&n)
#define wt(n) printf("%lld",n)
using namespace std;
int n,k,rr,pp,ss;
long long ans=0;
char s[200100];
int main()
{
    rd(n);rd(k);rd(rr);rd(ss);rd(pp);
    for(int i=1;i<=n;i++) cin>>s[i];
    for(int i=1;i<=n;i++)
    {
    	if(s[i]=='r') ans+=pp;
    	if(s[i]=='p') ans+=ss;
    	if(s[i]=='s') ans+=rr;
    	if(s[i+k]==s[i]) s[i+k]='f'; 
	}
	wt(ans);
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

贪心题，如果能赢就赢，不能赢就平。

用 `used` 记录这一局是不是赢了，对于第 $i$ 局来说，如果第 $i-k$ 局也赢了并且机器两次出的一样，这一局就必须要平。

## _Code_
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=1e5+5;
int n,r,s,p,k;
string t;
int ans=0;
bool used[MAXN*2];
int main(){
	cin>>n>>k>>r>>s>>p;
	cin>>t;
	for(int i=1;i<=n;i++)
		t=" "+t;//防越界
	for(int i=n;i<=2*n-1;i++){
		if(t[i]!=t[i-k]||!used[i-k]){
			if(t[i]=='r')
				ans+=p;
			if(t[i]=='s')
				ans+=r;
			if(t[i]=='p')
				ans+=s;
			used[i]=true;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：洛璟 (赞：0)

## Solution：

介绍一种贪心的做法。

我们会发现，如果去掉了 “第  $i-k$ 轮和第 $i(i>k)$ 轮出的手势不能相同.” 的限制，就是一个简单的模拟题目，但是因为有此限制，所以我们需要谨慎地选择。 

~~但其实也没必要。~~

我们发现，如果第 $i$ 个 与第 $i-k$ 个不同，那么完全不用理他，因为你的选择是一定会不一样的。~~当然不排除个别人不想要分数~~

那么接下来就是相同的情况了，很多人也许会因为这个玩意以为这次的决策会影响到第 $i+k$ 次的决策，其实不然。

我们来思考一下，如果第 $i$ 个与 第 $i-k$ 个相同，那么因为其获得分数相同，那我们就假定第 $i-k$ 个被选择，那么第 $i$ 个就有除了获胜以外两种选择，那么我们再假定第 $i+k$ 个与当前这个不同，那么由于第 $i$ 个有两种选择，所以我们一定可以完美避开下一次决策的得分答案。

简而言之，我们只需要判定第 $i-k$ 个是否与当前相同即可，若相同，则不加上当前的分数。

### code:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans;
bool f[1000010];
int n, k, r, p, s;
string c;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
int main()
{
    n = read();
    k = read();
    r = read();
    s = read();
    p = read();
    cin >> c;
    for (int i = 0;i < k;++i)
    {
        if (c[i] == 's')
        {
            ans += r;
            f[i] = 1;
        }
        else if (c[i] == 'r')
        {
            ans += p;
            f[i] = 1;
        }
        else if (c[i] == 'p')
        {
            ans += s;
            f[i] = 1;
        }
    }
    for (int i = k;i < n;++i)
    {
        if (c[i - k] == c[i] && f[i - k] == 1)
        {
            continue;
        }
        if (c[i] == 's')
        {
            ans += r;
            f[i] = 1;
        }
        else if (c[i] == 'r')
        {
            ans += p;
            f[i] = 1;
        }
        else if (c[i] == 'p')
        {
            ans += s;
            f[i] = 1;
        }
    }
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：CaiXY06 (赞：0)

# 题目大意
你知道了对手出的石头剪刀布的顺序，你出的手势第 $i$ 个不能和第 $i-k$ 个相同 $(i>k)$ ，求能得到的最大收益。

# Solution

我们考虑贪心，能赢尽量赢。

因为第 $i$ 个手势不能和第$i-k,i+k$ 手势相同,所以我们尽量选 $i-k,i+k$ 的得到两倍收益。

假如第 $i$ 个与 $i-k$ 相同与 $i+k$ 不同，因为有三种选择，显然中间那个可以刚好避开，与 $i-k,i+k$ 不同，保证了做法的正确性。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[3],ans;
bool flag[1000010];
char s[100010];
int main(){
	scanf("%d%d",&n,&k);
	scanf("%d%d%d",&a[0],&a[1],&a[2]);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
	if(i<=k||s[i]!=s[i-k]||(s[i]==s[i-k]&&!flag[i-k])){
		flag[i]=1;
		if(s[i]=='s')ans+=a[0];
		if(s[i]=='p')ans+=a[1];
		if(s[i]=='r')ans+=a[2];
	}
	printf("%d",ans);
	return 0;
}
```
我们给胜利的回合打上标记，保证不会冲突。

---

## 作者：whx2009 (赞：0)

## 本题思路：
这道题其实很简单，我们只需要按照能克制机器人的方式出即可，若本次机器人出的手势与前面第 $k$ 个相同就打平，并更改这次机器人的出招即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[100001];
int main()
{
	long long n,k,r,s,p,ans=0;
	cin>>n>>k>>r>>s>>p;
	cin>>a+1;
	for(int i=1;i<=n;i++)
	{
		if(i>=k && a[i]==a[i-k]) a[i]=0;
		if(a[i]=='r') ans+=p;
		if(a[i]=='s') ans+=r;
		if(a[i]=='p') ans+=s;
	//	cout<<ans<<" ";
	}
	cout<<ans;
 	return 0;
}

```


---

## 作者：_Above_the_clouds_ (赞：0)

# 思路：
如果对手出石头，我们最优解是出布，但我们出的第 $i-k$ 个手势就不能是布。
其他的也是类似。

如果本局赢了，$ans$ 加上当前手势所得的分数；否则 $ans$ 就不加分，也不用记录本局所用的手势。因为不管出什么手势，要么平局，要么输掉，都不加分，也不影响第 $i+k$ 个手势如何出。

最后输出 $ans$ 即可。

# 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int Max=1e5+5,mod=1e9+7;
int n,k,r,s,p,ans;
string t;
char a[Max];
signed main(){
	cin>>n>>k>>r>>s>>p>>t;
	t=" "+t;
	for(int i=1;i<=n;i++)
		if(t[i]=='r'&&a[max(i-k,0)]!='p') ans+=p,a[i]='p';
		else if(t[i]=='s'&&a[max(i-k,0)]!='r') ans+=r,a[i]='r';
		else if(t[i]=='p'&&a[max(i-k,0)]!='s') ans+=s,a[i]='s';
	cout<<ans;	
	return 0;
}


```


---

## 作者：_AyachiNene (赞：0)

# 思路：
这题第一眼感觉是 dp，但是第 $i$ 次只会影响第 $i+k$ 次，而且每次只能选一个，所以可以考虑用贪心。要让总和更大，我们每一次都用能加分的那一种，因为只会影响第 $i+k$ 次，第 $i$ 次用和第 $i+1$ 次是一样的。如果第 $i-k$ 次用了这次要用的，因为输了或平局不扣分且每次只能选一个，所以对后面没有影响。只需要开一个数组记录每次选的是什么就行了。
# Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k;
int r,s,p;
int vis[114514];
//1表示r 2表示s 3表示p 
string t;
int ans;
signed main()
{
	cin>>n>>k>>r>>s>>p>>t;
	t=' '+t;
	for(int i=1;i<=n;i++)
	{
		if(i<=k)
		{
			if(t[i]=='r')
				ans+=p,vis[i]=3;
			else if(t[i]=='s')
				ans+=r,vis[i]=1;
			else
				ans+=s,vis[i]=2;
		}
		else
		{
			int be=vis[i-k];
			if(t[i]=='r')
			{
				if(be!=3)
					ans+=p,vis[i]=3;
			}
			else if(t[i]=='s')
			{
				if(be!=1)
					ans+=r,vis[i]=1;
			}
			else 
			{
				if(be!=2)
					ans+=s,vis[i]=2;
			}
		}
	}
	cout<<ans;
}
```


---

