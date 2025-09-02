# Dominoes

## 题目描述

You are given $ n $ dominoes. Each domino has a left and a right cell. Each cell can be colored either black or white. Some cells are already colored, while some aren't yet.

The coloring is said to be valid if and only if it is possible to rearrange the dominoes in some order such that for each $ 1 \le i \le n $ the color of the right cell of the $ i $ -th domino is different from the color of the left cell of the $ ((i \bmod n)+1) $ -st domino.

Note that you can't rotate the dominoes, so the left cell always remains the left cell, and the right cell always remains the right cell.

Count the number of valid ways to color the yet uncolored cells of dominoes. Two ways are considered different if there is a cell that is colored white in one way and black in the other. In particular, colorings BW WB and WB BW different (and both invalid).

As this number can be very big, output it modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, there is only one domino, and we need the color of its right cell to be different from the color of its left cell. There is only one way to achieve this.

In the second test case, there are only $ 2 $ such colorings:

BB WW and WB WB.

## 样例 #1

### 输入

```
1
?W```

### 输出

```
1```

## 样例 #2

### 输入

```
2
??
W?```

### 输出

```
2```

## 样例 #3

### 输入

```
4
BB
??
W?
??```

### 输出

```
10```

# 题解

## 作者：Rainy7 (赞：13)

$\text{upd:2022/10/20}$：代码中组合数没判断 $y<x$ 的情况，可能导致 ub。已修改。感谢 @[with_no_signal](https://www.luogu.com.cn/user/302803) 指出。

- **分析**

  首先，最后若干个骨牌一定满足有 $n$ 个黑色，$n$ 个白色。
  
  先考虑不存在一个骨牌上两个格子同一个颜色的情况（即保证每个骨牌都是一黑一白）。那么最后的染色结果一定只有 左边都是黑色 或者 右边都是黑色 的 2 种情况。
  
  如果存在一个骨牌全是黑色，那么也一定存在一个骨牌全是白色。
  
  我们发现，用这种全黑（或白）骨牌可以将左黑右白的骨牌与左白右黑的骨牌分开，使他们合法。
  
  ![](https://s2.loli.net/2021/12/12/ZcsEP7WQvzLtlH1.png)
  
  也就是说，如果骨牌中存在全黑（白）骨牌，那么剩下的颜色在满足 $n$ 个黑色 $n$ 个白色的情况下，就可以随意取。
  
  接下来考虑初始情况。设初始给了 $s_w$ 个白色和 $s_b$ 个黑色。
  
  如果初始情况存在一个全黑（白）骨牌，那么答案即为 $C_{2n-s_w-s_b}^{n-s_w}$。
  
  如果初始不存在，用上面那个组合数再减去不合法情况即可。
  
  即减去没有染色出全黑（白）骨牌的所有情况，再加上 左边都是黑色 或者 右边都是黑色 的 2 种情况。注意一下这两种情况是否会出现即可。
  

------------

- **代码**

``` cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int N=2e5+5;
const int Mod=998244353;
int n,ans,cnt,s1,s2,cnt1,cnt2,mul[N],inv[N];
char s[N][5];
int qpow(int x,int k)
{   int res=1;
    while(k)
    {   if(k&1)res=1ll*res*x%Mod;
        x=1ll*x*x%Mod;
        k>>=1;
    }
    return res;
}
int C(int x,int y)
{	if(y<x||x<0)return 0;
    return 1ll*mul[y]*inv[x]%Mod*inv[y-x]%Mod;
}
int main()
{   scanf("%d",&n);
    mul[0]=inv[0]=1;
    for(int i=1;i<=(N-5);i++)mul[i]=1ll*mul[i-1]*i%Mod,inv[i]=qpow(mul[i],Mod-2);
    for(int i=1;i<=n;i++)
    {   scanf("%s",s[i]);
        cnt+=(s[i][0]!='?')+(s[i][1]!='?');
        s1+=(s[i][0]=='W')+(s[i][1]=='W');
        s2+=(s[i][0]=='B')+(s[i][1]=='B');
    }
//  printf("cnt:%d s1:%d s2:%d\n",cnt,s1,s2);
    for(int i=1;i<=n;i++)
    {   if(s[i][0]=='W'&&s[i][1]=='W')cnt1++;
        if(s[i][0]=='B'&&s[i][1]=='B')cnt2++;
    }
//  printf("C:%d %d\n",n-s1,2*n-cnt);
    if(cnt1||cnt2)printf("%d\n",C(n-s1,2*n-cnt));
    else{
        ans=C(n-s1,2*n-cnt);
        cnt1=cnt2=0;
        for(int i=1;i<=n;i++)
        {   if(s[i][0]=='W'||s[i][1]=='B')cnt1++;
            if(s[i][1]=='W'||s[i][0]=='B')cnt2++;
        }
//      printf("%d\n",ans);
//      printf("%d %d\n",cnt1,cnt2);
        if(!cnt1)ans++;
        if(!cnt2)ans++;
        ans=(1ll*ans+Mod-qpow(2,n-cnt1-cnt2))%Mod;
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：Tony2 (赞：6)

众所周知，D < C。

![](https://cdn.luogu.com.cn/upload/image_hosting/7nlwczho.png)

这张图解释的是摆放好后某个骨牌后面的骨牌能是什么。

我们发现实际上我们要确定所有骨牌的颜色，累加到对应位置上（如 `BW`，`WB`），表示这个位置能在图上被经过几次。我们从一个位置开始游走，游走 $n$ 步恰好回到起点，每个点恰好经过一开始累计的次数。

我们进行分类讨论。

第一种情况：只有 `BW` 情况。答案显然（在呆码中是 `ok1`）。

第二种情况：只有 `WB` 情况。答案显然（在呆码中是 `ok2`）。

第三种情况，出现了 `BB` 或者 `WW`。

因为所有骨牌排成一个圈，我们钦定 `BB` 是起始点。

我们发现必然从 `BB` 出发到 `WW`，也就是说 `BB` 的经过次数必然与 `WW` 的经过次数相等。我们可以在 `BW` 或者 `WB` 上转圈圈，所以只要 `BB`(`WW`) 出现过，其它两种（`BW`，`WB`）都可以经过任意次（实际上就是无条件了）。

所以我们设数组 $f$，下标可以是负数，且无限延申。

$f_i$ ：$i$ 是 `WW` 的出现次数减去 `BB` 的出现次数的值，$f_i$ 是确定前若干个骨牌之后出现以上情况（次数差值为 $i$）的情况数量。

我们以任意顺序考虑每个骨牌。

设 $f$ 为当前数组，$f'$为下次数组。

如果一个骨牌可以被确定为 `WW`，那么 $f'_i = f'_i+f_{i-1}$，所有位置同时进行；如果一个骨牌可以被确定为 `BB`，那么 $f'_i = f'_i+f_{i+1}$，所有位置同时进行。

如果一个位置可以被确定为 `WB` 或者 `BW`，那么这个位置的值可以加到 $f'$ 数组上（位置相同）。这个 `WB` 和 `BW` 是分开进行的。

给一个伪代码：

```
if 能确定为 "BB":
	for i: f`[i] += f[i+1]
if 能确定为 "WW":
	for i: f`[i] += f[i-1]
if 能确定为 "WB":
	for i: f`[i] += f[i]
if 能确定为 "BW":
	for i: f`[i] += f[i]
```

这个过程实际上就是暴力求组合数的过程。具体写的时候也可以参照上面 $f$ 的位置来求。

然后有一个小细节，我们需要减掉这个分讨中没有 `BB` 或者 `WW` 出现的情况数量（在呆码里写成 `extraans`）。这个也很好求。

code:

```cpp
#include <bits/stdc++.h>
#define mod 998244353
#define ll long long
using namespace std;
const int N = 2e5+5;
int T, n;
int cnt, cnt1, cnt2;
ll f[N], invf[N];
ll extraans;
ll aans;
ll qpow(ll x, ll y){
	ll res = 1;
	while (y){
		if (y&1) res = res*x%mod;
		x = x*x%mod; 
		y >>= 1;
	}
	return res;
}
ll C(int n, int m){
	return f[n]*invf[m]%mod*invf[n-m]%mod;
}
int main(){
	std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	f[0] = 1;
	for (int i = 1; i <= 2e5; i++)
		f[i] = f[i-1]*i%mod;
	invf[200000] = qpow(f[200000], mod-2);
	for (int i = 2e5-1; i >= 0; i--)
		invf[i] = invf[i+1]*(i+1)%mod;
	extraans = 1;
	cin >> n;
	bool ok1 = 1, ok2 = 1;
	for (int i = 1; i <= n; i++){
		string s;
		cin >> s;
		if (s == "WW") extraans = 0;
		else if (s == "BB") extraans = 0;
		else if (s == "??"){
			extraans = extraans*2%mod;
			cnt++;
		}else if (s[0] == '?'){
			if (s[1] == 'W') cnt1++;
			else cnt2++;
		}else if (s[1] == '?'){
			if (s[0] == 'W') cnt1++;
			else cnt2++;
		}
		if (s[0] == 'B' || s[1] == 'W') ok1 = 0;
		if (s[0] == 'W' || s[1] == 'B') ok2 = 0;
	}
	aans = C(cnt*2+cnt1+cnt2, cnt+cnt2)+ok1+ok2-extraans;
	aans = (aans%mod+mod)%mod;
	cout << aans << endl;
	return 0;
}
```

---

## 作者：enucai (赞：4)

~~**前言：这可能是蒟蒻能写出来的计数题的难度上限了**~~

## 题意简述

让你给 $n$ 个多米诺骨牌黑白染色，每个骨牌有两个格子。

若将这 $n$ 个骨牌重新排列后**至少存在**一种方案，使得 $\forall i$，第i个骨牌右边格子颜色与第 $(i\bmod n)+1$ 个骨牌左边颜色不同，则这种染色方法合法。

问你有几种**合法**的染色方案。

~~可能不是讲得很清楚，看不懂去看英文题面吧（逃~~

## 思路简述

首先通过观察，我们发现对于任意一种合法的染色方案：

- `BB` 和 `WW` 这两种颜色类型的骨牌数量一定是相等的。

- 如果有 `BW` 和 `WB` 种类的骨牌，那么至少要有 $1$ 个 `BB` 和 $1$ 个 `WW` 类型的骨牌。

而且这两个条件是合法染色方案的充要条件。接下来是对以上两个结论的感性证明：

- 对于第一条结论，我们可以认为 `WW` 与 `BB` 为骨牌序列的**转折点**，因为一个连续的 `WB` 序列后面跟上一个 `WW` 序列后，后面就会变成连续的 `BW` 序列。因为所有的序列构成一个环后始终符合条件。所以，我们可以清晰地看到，两种转折点地数量一定相等。

![](https://cdn.luogu.com.cn/upload/image_hosting/1xc0lu9x.png)

- 可以来张图片：我们认为 `BW` 的连续序列为橙色线段，`WB` 的连续序列为绿色线段。那么黑点表示 `BB`，作为 `BW` 与 `WB` 的转折点；灰点表示 `WW`，作为 `WB` 与 `BW` 的转折点。因为最后环上一定是橙绿线段首尾衔接的，所以橙线段与绿线段数量相等，黑点与灰点数量相等，所以 `BB` 与 `WW` 数量也就一样多了。

- 对于第二条结论，如果 `BW` 与 `WB` 都存在，那么必定存在至少一个转折点，所以必定有 `WW` 与 `BB`。

**性质观察完了，我们开始想想应该怎么算。**

我们先定义：出现在一个骨牌左边的 `W` 为 `W1`，右边的 `W` 为 `W2`。同理，有 `B1`，`B2`，`Q1` 与 `Q2` （ `Q` 表示 `?` ）。假设 `B1` 有 $i$ 个，`W2` 也有 $i$ 个，那么可得 `B2` 有 $n-i$ 个，`W1` 也有 $n-i$ 个。枚举这个 $i$ 即可算出**大致合法**的有几个，公式为：

$$\sum\limits_{i=1}^n C_{Q1}^{i-B1}\times C_{Q2}^{n-i-B2}$$

但是这并不符合我们推出来的结论，我们想想他们之间的差距在哪里。

经过观察，我们发现，不符合第二条结论的情况会被数进去。因此要减去有 `BW` 与 `WB` 但是没有 `WW` 与 `BB` 的情况。我们可以先减去没有 `WW` 与 `BB` 的情况，再加回只有 `WB` 与 `BW` 的情况。

要算没有 `BB` 与 `WW` 的情况，由于 `BB` 和 `WW` 的数量一定相等，所以如果已经有 `BB` 或 `WW` 了，那么就不用减。减的数量为：

$$2^{??}$$

因为只有 `??` 可以构造出 `BW` 与 `WB` 两种情况，其他的 `W?`,`?W`,`?B`,`B?` 都只能构造出一种不是 `BB` 且不是 `WW` 的情况，相当于乘了 $1$，等于没乘。

最后，还要算只有 `WB` 与 `BW` 的情况，那么有两种情况会加 $1$：

- `W1` 与 `B2` 都是 $0$。

- `B1` 与 `W2` 都是 $0$。

好了，总算算完了。所以最后的公式是：

$$\sum\limits_{i=1}^n C_{Q1}^{i-B1}\times C_{Q2}^{n-i-B2}-[bb=0\&ww=0]\times 2^{??}+[w1=0\&b2=0]+[b1=0\&w2=0]$$

## 蒟蒻代码

**Talk is cheap, show me the code.**

```cpp
#define mod 998244353
#define int long long
int n,cnt[3][3];
string s;
int change(char x){
	if(x=='?') return 0;
	else if(x=='W') return 1;
	else if(x=='B') return 2;
}//将字符转化为数字，方便统计
int inv[100010],fact[100010],ifact[100010];
void init(){
	inv[1]=1;
	For(i,2,100000) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	fact[0]=ifact[0]=1;
	For(i,1,100000) fact[i]=fact[i-1]*i%mod;
	For(i,1,100000) ifact[i]=ifact[i-1]*inv[i]%mod;
}//阶乘预处理，用来算组合数
int C(int n,int m){
	if(n<m||m<0) return 0;
	return fact[n]*ifact[m]%mod*ifact[n-m]%mod;
}//组合数的简单计算
int qpow(int a,int p){
	if(p==0) return 1;
	int qwq=qpow(a,p/2);
	if(p%2==1) return qwq*qwq%mod*a%mod;
	else return qwq*qwq%mod;
}//快速幂模板
signed main(){
	init();
	n=read();
	For(i,1,n){
		cin>>s;
		cnt[change(s[0])][change(s[1])]++;//统计各种类型的数量
	}
	int w1=cnt[1][0]+cnt[1][1]+cnt[1][2];//算w1
	int b1=cnt[2][0]+cnt[2][1]+cnt[2][2];//算b1
	int w2=cnt[0][1]+cnt[1][1]+cnt[2][1];//算w2
	int b2=cnt[0][2]+cnt[1][2]+cnt[2][2];//算b2
	int q1=n-w1-b1,q2=n-w2-b2;//算q1和q2
	int ans=0;
	For(i,0,n) ans=(ans+C(q1,i-b1)*C(q2,n-i-b2))%mod;//先算第一个sigma
	if(cnt[1][1]==0&&cnt[2][2]==0) ans-=qpow(2,cnt[0][0]);//减去没有WW和BB的
	if(w1==0&&b2==0) ans++;
	if(b1==0&&w2==0) ans++;//加回只有BW和WB的
	cout<<ans<<endl;//Happy Ending
}
```

---

## 作者：hgzxwzf (赞：3)

### [CF1608D](https://codeforces.com/problemset/problem/1608/D)

一个涂色方案合法的必要条件是恰好有 $n$ 个 $\verb!W!$ 和 $n$ 个 $\verb!B!$，因为一前一后两个骨牌，前者右边和后者左边不同，意味着其中一个是 $\verb!W!$，另一个是 $\verb!B!$，所以出现一个 $\verb!W!$，一定会出现一个 $\verb!B!$。

我们可以计算 $\verb!W!$ 的数量 $c_1$ 和 $\verb!?!$ 的数量 $c_0$，那么满足必要条件的方案数就等于 $\tbinom{c_0}{n-c_1}$。

这并不是最后的答案，我们还要减掉满足必要条件的方案数中不合法的方案。

我们先减掉所有骨牌左右颜色都不同的方案数，再加上全为 $\verb!WB!$ 或 $\verb!BW!$ 的方案数，容易发现所有骨牌左右颜色都不同的方案中只有全为 $\verb!WB!$ 或 $\verb!BW!$ 才合法，在满足必要条件的前提下不是所有骨牌左右颜色都相同的方案一定合法。

```cpp
#include<cstdio>
#include<set>
#include<algorithm>
#include<vector>
#include<stack>
#include<cmath>
#include<vector>
#include<cstring>
#include<queue>
#include<string>
#include<iostream>
#include<map>
#include<bitset>
#include<ctime>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)
#define LL long long
#define pi pair<int,int>
#define mk make_pair
#define fi first
#define se second

using namespace std;
const int N=2e5+10,mod=998244353;

int cnt[2],po[N],inv[N];
char c[2];

inline int ksm(int x,int y)
{
	int s=1;
	while(y)
	{
		if(y&1) s=1ll*x*s%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}

inline int C(int n,int k)
{
	if(k>n) return 0;
	if(k==0||n==k) return 1;
	return 1ll*po[n]*inv[k]%mod*inv[n-k]%mod;
}

inline int add(int x,int y)
{
	x+=y;
	if(x>=mod) x-=mod;
	return x;
}

inline int sub(int x,int y)
{
	x-=y;
	if(x<0) x+=mod;
	return x;
}

int main()
{
	int n;
	scanf("%d",&n);
	po[0]=1;
	rep(i,1,2*n) po[i]=1ll*po[i-1]*i%mod;
	inv[2*n]=ksm(po[2*n],mod-2);
	per(i,1,2*n) inv[i-1]=1ll*inv[i]*i%mod;
	int dif=1,WB=1,BW=1;
	rep(i,1,n)
	{
		scanf("%s",c);
		rep(j,0,1)
			if(c[j]=='?') cnt[0]++;
			else if(c[j]=='W') cnt[1]++;
		if(c[0]==c[1]&&c[0]!='?') dif=0;
		if(c[0]=='B'||c[1]=='W') WB=0;
		if(c[0]=='W'||c[1]=='B') BW=0;
		if(c[0]==c[1]&&c[0]=='?') dif=1ll*dif*2%mod;
	}
	if(cnt[1]>n) return puts("0"),0;
	int ans=C(cnt[0],n-cnt[1]);
	printf("%d",add(add(sub(ans,dif),WB),BW));
	return 0;
}
```


---

## 作者：lfxxx (赞：1)

要求相邻骨牌左右边不同色貌似不好处理，那如果是要求同色呢？

考虑将骨牌变成第一个色块的颜色到第二个色块的颜色的一条边，合法当且仅当存在欧拉回路并且连通块数量为 $1$，两者都容易通过组合与容斥计算。

那怎么把不同色限制变为同色限制呢？将每个骨牌的第二个色块的颜色反转即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxn = 2e5+114;
int In[3],Out[3];
int fac[maxn],inv[maxn];
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
int C(int n,int m){
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int ans;
int n;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    fac[0]=inv[0]=1;
    for(int i=1;i<=2*n;i++) fac[i]=fac[i-1]*i%mod,inv[i]=qpow(fac[i],mod-2);
    int res=1;
    int cntW=0,cntB=0,cntQ=0;
    for(int i=1;i<=n;i++){
        char c,t;
        cin>>c>>t;
        if(c=='W') Out[0]++;
        else if(c=='B') Out[1]++;
        else Out[2]++;
        if(t=='B') t='W';
        else if(t=='W') t='B';
        if(t=='W') In[0]++;
        else if(t=='B') In[1]++;
        else In[2]++;
        if(c=='W'&&t=='B') res=res*0;
        else if(c=='B'&&t=='W') res=res*0;
        else if(c==t){
            if(c=='?') cntQ++;
            if(c=='W') cntW++;
            if(c=='B') cntB++;
        }else{
            if(c=='W'||t=='W') cntW++;
            else cntB++;
        }
    }
    if(res!=0){
        res=res*qpow(2,cntQ);
        if(cntB==0&&cntQ!=0) res=(res+mod-1)%mod;
        if(cntW==0&&cntQ!=0) res=(res+mod-1)%mod;
        if(cntQ==0&&(cntB==0||cntW==0)) res=0;        
    }
    for(int k=0;k<=Out[2];k++){
        //k 条问号出边从 W 出发
        int p=k+Out[0]-In[0];
        //p 条问号入边进入 W
        if(p<=In[2]&&p>=0) ans=(ans+C(Out[2],k)*C(In[2],p)%mod)%mod;
    }
    cout<<(ans+mod-res)%mod<<'\n';
    return 0;
}
```

---

## 作者：williamwei (赞：0)

考虑什么情况下一个状态才能满足条件。

对于传统的多米诺骨牌问题，满足条件当且仅当存在欧拉回路。

因为这道题的多米诺骨牌只有两个颜色，会发现只要将所有的第一个字符的反转和第二个字符连边形成一个欧拉回路，就满足条件。

有向图存在欧拉回路的条件：每个点**入度 = 出度**，且图连通。

**注意：本文种将所有多米诺骨牌的第一个字符都反转了，例如 BW 变成 WW，WB 变成 BB。**

记录下 B/W 这两点已知的出入度，假设 B 的入度为 $I_B$，出度为 $O_B$，W的入度为 $I_W$，出度为 $O_W$

考虑枚举钦定多少个未知的起始字符选 B，假设钦定了 $x$ 个，则 B 的出度增加 $x$，入度也需要对应补齐，也就是要对应的再选 $O_B+x-I_B$ 个 B。剩下的必定选 W。

所以对于 $x$ 个 B 有 $\dbinom{n-O_B-O_W}{x}\dbinom{n-I_B-I_W}{O_B+x-I_B}$，这步不难推导。

枚举 $x$ 预处理组合数直接算即可。时间复杂度 $\mathcal{O}(n)$。有一些边界可以在组合数出特判，也可以算出上下界。

然而到这里就结束了吗？你会发现过不了样例 $2$，因为会有一些不合法的情况被算入答案。

要求图连通，所以要将不存在 BW/WB 这种边且 B/W 都出现的情况减掉。对于题目输入中存在 BW/WB 的情况，忽略不计。

先将为 ?? 的骨牌总数记录，设为 $c$。

减去不合法的情况，即这些地方全选 BB/WW，一共有 $2^c$ 种。

如果总共出现的字符数量不到 $2$，需要再加上一些特例。假设已知出现了 $x$ 个字符，则答案再加上 $2-x$。可以参考代码理解。

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int mod = 998244353;
int n, ans, a[2], b[2], f[maxn], inv[maxn];
bool id(char ch) { return ch == 'W'; }
int qpow(int a, int b) {
	int res = 1; for (; b; b >>= 1, a = (ll)a * a % mod)
		if (b & 1) res = (ll)res * a % mod; return res;
}
int C(int n, int m) { return (ll)f[n] * inv[m] % mod * inv[n - m] % mod; }
int main() {
	ios::sync_with_stdio(false);
	cin >> n; f[0] = 1;
	for (int i = 1; i <= n; i++) f[i] = (ll)f[i - 1] * i % mod;
	inv[n] = qpow(f[n], mod - 2);
	for (int i = n - 1; ~i; i--) inv[i] = (ll)inv[i + 1] * (i + 1) % mod;
	bool F = true; int cur = 0;
	for (int i = 1; i <= n; i++) {
		char c1, c2; cin >> c1 >> c2;
		F &= c1 == '?' || c2 == '?' || c1 != c2;
		cur += c1 == '?' && c2 == '?';
		if (c1 != '?') ++a[id(c1) ^ 1];
		if (c2 != '?') ++b[id(c2)];
	}
	int l = max(b[0] - a[0], 0), r = n - a[0] - max(a[1], b[1]);
	for (int i = l; i <= r; i++)
		ans = (ans + (ll)C(n - a[0] - a[1], i) * C(n - b[0] - b[1], a[0] - b[0] + i)) % mod;
	if (F) {
		ans -= qpow(2, cur) - (!a[0] && !b[0]) - (!a[1] && !b[1]);
		if (ans < 0) ans += mod;
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：清烛 (赞：0)

## Description
给定 $n$ 个左右格的多米诺骨牌，要求黑白染色，有些格子已经预染色。问存在几种方案使得重排后任意第 $i$ 个骨牌的右半边和第 $(i\bmod n) + 1$ 个骨牌的左半边颜色不同。方案数对 $998244353$ 取模。

## Solution
可能算是比较基础（？）的计数题，可惜场上没去想。拿到这道题，可以先观察一下题目性质，去寻找什么情况下染色方案是合法的，然后进行统计。

首先我们知道，一个染色方案合法当且仅当 W 和 B 的数量相同，以及 WW 和 BB 的数量相同。计算 W 和 B 的数量，若其大于 $n$，则显然无解。

否则，无解的情况就是 WB 和 BW 同时存在却没有 WW 或 BB。其他都为合法情况，方案大家可以在草稿纸上尝试进行构造。设问号有 $c_0$ 个，W 有 $c_B$ 个，则显然总染色方案数为 $\dbinom{c_0}{n - c_B}$。然后处理一下无解的情况。

同时存在 WB 和 BW 却没有 WW 或 BB 的方案数其实就是用 **不存在 WW 和 BB 的方案数** 减去 **全是 WB** 和 **全是 BW** 的情况。设 ?? 有 $c_P$ 个，则对于第一个“不存在 WW 和 BB 的”的方案数就是 $2^{c_P}$，且不存在 BB 或 WW；对于全是 WB 的至多一种，且不能存在 Bx 或 Wx，全是 BW 同理。

## Implementation
```cpp
const int maxn = 2e5 + 5;
modint fac[maxn], ifac[maxn];
int n;
char s[maxn][5];

modint binom(int n, int m) {
    return fac[n] * ifac[n - m] * ifac[m];
}

int main() {
    read(n);
    fac[0] = 1;
    FOR(i, 1, 2 * n) fac[i] = i * fac[i - 1];
    ifac[2 * n] = qPow(fac[2 * n], mod - 2);
    DEC(i, 2 * n - 1, 0) ifac[i] = (i + 1) * ifac[i + 1];
    int cntb = 0, cntw = 0, cntp = 0, cntq = 0;
    bool checkwb = 1, checkbw = 1, checksame = 1;
    FOR(i, 1, n) {
        read(s[i] + 1);
        if (s[i][1] == '?' && s[i][2] == '?') ++cntp;
        if (s[i][1] == s[i][2] && s[i][1] != '?') checksame = 0;
        cntb += (s[i][1] == 'B') + (s[i][2] == 'B');
        cntw += (s[i][1] == 'W') + (s[i][2] == 'W');
        cntq += (s[i][1] == '?') + (s[i][2] == '?');
        if (s[i][1] == 'B'|| s[i][2] == 'W') checkwb = 0;
        if (s[i][1] == 'W'|| s[i][2] == 'B') checkbw = 0;
    }
    if (cntb > n || cntw > n) return print(0), output(), 0;
    modint ans = binom(cntq, n - cntb);
    ans -= checksame * qPow(2, cntp) - checkwb - checkbw;
    print(ans);
    return output(), 0;
}
```

---

