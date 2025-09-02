# Minecraft

## 题目描述

### 题意翻译


在赢得一场紧张的 Bed Wars 起床战争游戏后, Masha 和 Olya 想放松一下, Masha 给了 Olya 一个长度为 $n$ 的数组 $a$ 和一个数字 $s$ 。现在请帮助Olya找到一个非负整数 $x$ ，使得 $ \displaystyle\sum_{i=1}^{n} a_i \oplus x = s$ ($ \oplus $表示异或运算)。但是这个任务对他们来说似乎太简单了，所以他们决定把数字变大并以长度为$ k $的二进制形式表示。

## 样例 #1

### 输入

```
4
4 5
01011
01110
00110
01100
01111
2 8
00101001
10111111
10011110
5 4
0101
0010
0000
0000
0010
0011
6 5
00011
10110
11001
01010
11100
10011
10000```

### 输出

```
01110
10011010
0010
-1```

# 题解

## 作者：MarSer020 (赞：9)

虾头 CF，2h8 题，E<G<D<F，赛后 5min 过样例，交一发过了。

$\Large\text{Solution}$

考虑对于每一位分开考虑。

由于只有 $n$ 个字符串，该位取 0/1 影响的只有向前 $O(\log n)$ 位。设 $dp_{i,j}=0/1$ 表示向前能影响到的若干位状压起来是 $j$，是否合法，转移考虑这一位取 $0$ 还是取 $1$，那么转移式就比较显然了。输出方案直接 dfs 一遍就可以了。

状态数 $O(nm)$，转移 $O(1)$，总时间复杂度 $O(\sum nm)$。

$\Large\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s[2000005],T;
vector<bool>dp[2000005],a,b[2000005];
char ch;
void dfs(int cur,int val){
	if(cur==0)
		return;
	if(val>=s[cur]&&dp[cur-1][((val-s[cur])<<1)|a[cur-1]])
		cout<<0,dfs(cur-1,((val-s[cur])<<1)|a[cur-1]);
	else
		cout<<1,dfs(cur-1,((val-n+s[cur])<<1)|a[cur-1]);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>T;
	while(T--){
		cin>>n>>m,a.resize(m+1);
		for(int i=0;i<=m;i++)
			dp[i].resize(4*n+1),s[i]=0;
		for(int i=m;i>=1;i--)
			cin>>ch,a[i]=ch^48;
		for(int i=1;i<=n;i++){
			b[i].resize(m+1);
			for(int j=m;j>=1;j--)
				cin>>ch,b[i][j]=ch^48,s[j]+=b[i][j];
		}
		dp[0][0]=1;
		for(int i=0;i<m;i++)
			for(int j=0;j<=4*n;j++)
				if(dp[i][j]&&(j&1)==a[i])
					dp[i+1][(j>>1)+s[i+1]]=1,dp[i+1][(j>>1)+(n-s[i+1])]=1;
		if(dp[m][a[m]])
			dfs(m,a[m]),cout<<'\n';
		else
			cout<<"-1\n";
		for(int i=1;i<=n;i++)
			b[i].clear();
		for(int i=1;i<=m;i++)
			dp[i].clear();
		a.clear();
	}
	return 0;
}
```

---

## 作者：naroto2022 (赞：4)

# CF1994G 题解

## 题面

[原题传送门（洛谷）](https://www.luogu.com.cn/problem/CF1994G)

[原题传送门](https://codeforces.com/problemset/problem/1994/G)

## 实现

### 暴力

首先，看到异或，我们可以想到可以把每一位分开讨论，发现每一位的所有 $a$ 贡献的答案为其 $0$ 的个数或者 $1$ 的个数，（贡献为 $0$ 的个数则 $x$ 对应的这一位为 $1$，贡献为 $1$ 则相反）但注意，这个问题并没有这么简单，因为这是二进制**加法**，加法则可能会产生进位，所以我们还要维护进位的次数。

于是，就可以从个位（就是最后一位）开始往前爆搜了（至少我在我模拟赛做到这题的时候由于没时间了只好打爆搜，赛后打出正解很遗憾），每一次只要判断当前位的奇偶性是否与给定的 $s$ 相匹配，然后就可以爆搜，这里进位二进制是逢二进一，所以进位个数应除以二，注意**最高位（也就是第一位）不能再有进位**！！！

于是，这就是我模拟赛的时候打出的代码。。。

### 代码（暴力）

```cpp
v#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int MN=1e6+5;
ll n,k,sm,a[MN],t[MN],s[MN],ans[MN];
bool flag;
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
ll ksm(ll a, ll b){ll res=1;while(b){if(b&1)res*=a;a*=a;b>>=1;}return res;}
char gc(){char ch=getchar();while(ch!='0'&&ch!='1')ch=getchar();return ch;}
void print(ll num){for(int i=k-1; ~i; i--) write((num>>i)&1);putchar('\n');}
void dfs(ll step, ll num){
	if(flag) return; 
	if(!step&&!num){flag=true;return;}
	if(((n-t[step]+num)&1)==(s[step]&1)) ans[step]=1,dfs(step-1,(n-t[step]+num)>>1); 
	if(flag) return;
	if(((t[step]+num)&1)==(s[step]&1)) ans[step]=0,dfs(step-1,(t[step]+num)>>1);
}
void solve(){
	for(int i=1; i<=k; i++) t[i]=0,s[i]=0;
	n=read();k=read();flag=false;
	if(k<=10){sm=0;for(int i=1; i<=k; i++) sm+=ksm(2,k-i)*(gc()^48);for(int i=1; i<=n; i++){a[i]=0;for(int j=1; j<=k; j++) a[i]+=ksm(2,k-j)*(gc()^48);}for(int i=0; i<(1<<k); i++){ll num=0;for(int j=1; j<=n; j++) num+=(a[j]^i);if(num==sm){print(i);return;}}write(-1);putchar('\n');return;}
	for(int i=1; i<=k; i++) s[i]=(gc()^48);
	for(int i=1; i<=n; i++) for(int j=1; j<=k; j++) t[j]+=(gc()^48);
	dfs(k,0);
	if(!flag) write(-1);
	else for(int i=1; i<=k; i++) write(ans[i]);putchar('\n');
}
int main(){
    // freopen("raining.in","r",stdin);
    // freopen("raining.out","w",stdout);
	ll T=read();while(T--)solve();
    return 0;
}
```

### 正解

其实在考场上写爆搜的时候我就知道这是个 dp 了，考后也是实践好了。

设 $dp_{i,j}$ 为从后往前推到了第 $i$ 位并且当前位会对下一位产生 $j$ 个进位的合法性，转移式子也很好写，我用的是主动转移，初始第 $k+1$ 位进位个数为 $0$ 是肯定有的，所以有初始化 $dp_{k+1,0}\gets 1$。

然后先预处理每一位上 $1$ 的个数 $t_i$，那么 $0$ 的个数也可以得出来为 $n-t_i$。

接下来开始枚举位数 $i$ 和进位数 $j$，若有当前状态是合法的，则有如下转移：

$\left\{\begin{array}{l}dp_{i-1,\lfloor\frac{t_{i-1}+j}{2}\rfloor}\gets1,(t_{i-1}+j)\bmod2=s_{i-1}\bmod2\\dp_{i-1,\lfloor\frac{n-t_{i-1}+j}{2}\rfloor}\gets1,(n-t_{i-1}+j)\bmod2=s_{i-1}\bmod2\end{array}\right.$

最后只要判断 $dp_{1,0}$ 的合法性即可。（就是第 $1$ 位进位 $0$ 次的情况）

如果合法，那么我们就要考虑怎么输出答案，我的做法就是每一次主动转移，被动转移方记录上答案，最后一步步调回来就好了，记这个数组为 $pre$，则有转移。

$\left\{\begin{array}{l}pre_{i-1,\lfloor\frac{t_{i-1}+j}{2}\rfloor}\gets0,(t_{i-1}+j)\bmod2=s_{i-1}\bmod2\\pre_{i-1,\lfloor\frac{n-t_{i-1}+j}{2}\rfloor}\gets1,(n-t_{i-1}+j)\bmod2=s_{i-1}\bmod2\end{array}\right.$

第一行中因为是让 $1$ 的个数做贡献，所以要让对应的 $x$ 为 $0$，第二行同理。

现在考虑如何倒推，设当前在第 $i$ 位，第 $i+1$ 位有 $j$ 次进位，当前有 $num$ 次进位，怎么从 $num$ 推导出 $j$ 呢，这里以第一个式子为例，第二个式子留给读者自己推。

首先由转移式子我们有 $num=\lfloor\frac{t_i+j}{2}\rfloor$。

而第一行成立的前提条件为 $(t_i+j)\bmod2=s_{i}\bmod2$。

所以我们就有 $t_i+j=num\times2+s_i\bmod2$。

移项得 $j=num\times2+s_i\bmod2-t_i$。

第二个式子同理。

所以我们从第一位跳 $k$ 次输出答案即可，具体见代码。

### 实现细节

我的这种方法还是写起来有一定的细节，具体总结如下。

1. 由于本题的空间较为刁钻，所以需要动态数组。
2. 多测记得清空。
3. 至于动态数组每个数据的第二维要开多少，对于每一位，其单独会产生的进位最多进 $\lfloor\frac{n}{2}\rfloor$ 位，叠加一下，每一位最多进 $\lfloor\frac{3n}{4}\rfloor$ 位，所以差不多开 $n$ 就够了。

### 代码（正解）

[提交记录](https://codeforces.com/problemset/submission/1994/299380124)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#define ll long long
using namespace std;
const int MN=2e6+5;
ll n,k,t[MN],s[MN];
vector<bool> dp[MN],pre[MN];
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
char gc(){char ch=getchar();while(ch!='0'&&ch!='1')ch=getchar();return ch;}
void solve(){
	for(int i=0; i<=k+1; i++) t[i]=0,s[i]=0,dp[i].clear(),pre[i].clear();
	n=read();k=read();
    for(int i=0; i<=k+1; i++) dp[i].resize(n+1),pre[i].resize(n+1);
	for(int i=1; i<=k; i++) s[i]=(gc()^48);
	for(int i=1; i<=n; i++) for(int j=1; j<=k; j++) t[j]+=(gc()^48);
    dp[k+1][0]=1;
    for(int i=k+1; i>1; i--) for(int j=0; j<=n; j++) if(dp[i][j]){
        if(((t[i-1]+j)&1)==(s[i-1]&1)) dp[i-1][(t[i-1]+j)>>1]=1,pre[i-1][(t[i-1]+j)>>1]=0;
        if(((n-t[i-1]+j)&1)==(s[i-1]&1)) dp[i-1][(n-t[i-1]+j)>>1]=1,pre[i-1][(n-t[i-1]+j)>>1]=1;
    }
    if(!dp[1][0]) write(-1);
    else{
        ll num=0;
        for(int i=1; i<=k; i++){
            write(pre[i][num]?1:0);
            if(pre[i][num]) num=(num<<1)+(s[i]&1)-n+t[i];
            else num=(num<<1)+(s[i]&1)-t[i];
        }
    }putchar('\n');
}
int main(){
    // freopen("raining.in","r",stdin);
    // freopen("raining.out","w",stdout);
	ll T=read();while(T--)solve();
    return 0;
}
```

---

## 作者：int08 (赞：2)

## 前言
其实不难，甚至 F>G，安排比较如如。

## 题意
给定 $n$ 个数 $a_i$ 和 $p$，求一个 $x$ 使得 $\Sigma a_i\oplus x=p$。

但是 $a_i$ 和 $p$ 都是长为 $k$ 的二进制 `0-1` 串，而且 $n\times k\le 2\times 10^6$。
# Solution
我赛时想法是对的……

我们先观察官方 Solution：

> 1. Think of the most stupid solution you can do
>
> 3. Done!

如如！

官解是爆搜，记忆化，剪枝后复杂度就对了。

讲一下个人的 DP 做法：

容易发现我们可以按位操作，不同位之间操作独立（注意并不是互不影响！）

这样这 $n$ 个数具体是多少就不重要了，重要的只是每一位上有多少个 $1$。

对于第 $i$ 位有 $a_i$ 个 $1$，如果答案这一位选 $0$，这一位贡献 $a_i\times 2^i$、否则贡献为 $(n-a_i)\times 2^i$。

变成了：每一位上有两种选择方法，问能否凑出某个数，这是不简单的。

先变成默认选小的然后考虑 $n$ 个位置是否变大，如果全选小的和已经超过就不行。

我们可以从大到小位考虑，并设一个 $dp_{i,j}$ 表示当前已经考虑了前 $i$ 大的位是否增加后离 $s$ 还有 $j\times2^{k-i}$ 的距离（小的部分暂时忽略，后面扫到那位再加上）是否可行以及是从哪里转移来的。

这时候发现一个重要性质：后面所有位能加的都加，由于每位最多 $n\times 2^{k-x}$，后面所有位加起来也不到 $n\times 2^{k-i}$。

换句话说第二维开到 $n$ 即可，超过 $n$ 的必不是答案，然后直接 DP 即可，复杂度 $O(nk)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
#define N 2085555
int s[N],a[N],ans[N],inc[N],i,j;
char op;
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		int n,k;
		cin>>n>>k;
		for(i=1;i<=k;i++) cin>>op,s[i]=(op=='1')?1:0;
		for(i=1;i<=n;i++)
			for(j=1;j<=k;j++) cin>>op,a[j]+=(op=='1')?1:0;
		for(i=1;i<=k;i++)
		{
			if(a[i]>n/2) a[i]=n-a[i],ans[i]=1;
			inc[i]=abs(n-2*a[i]);
		}
		for(i=k;i>1;i--) a[i-1]+=a[i]/2,a[i]%=2;
		int flag=0;
		for(i=1;i<=k;i++)
		{
			if(s[i]==a[i]) continue;
			flag=a[i]>s[i]?1:0;
			break;
		}
		if(flag==1)
		{
			cout<<"-1\n";
			for(i=0;i<=k+10;i++) s[i]=a[i]=inc[i]=ans[i]=0;
			continue;
		}
		for(i=k;i>=1;i--)
		{
			s[i]=s[i]-a[i];
			int exa=abs(s[i]%2);
			s[i-1]+=(s[i]-exa)/2;
			s[i]=exa;
		}
		pair<int,int> mov[k+5][2*n+10];
		for(i=0;i<=k+4;i++)
			for(j=0;j<=2*n+9;j++) mov[i][j]={-1,-1};
		mov[0][0]={0,0};
		for(i=1;i<=k;i++)
			for(j=0;j<=2*n+3;j++)
			if(mov[i-1][j].first!=-1)
			{
				int res=j*2+s[i];
				if(res-inc[i]>=0&&res-inc[i]<=2*n+3) mov[i][res-inc[i]]={j,1};
				if(res>=0&&res<=2*n+3) mov[i][res]={j,0};
			}
		if(mov[k][0].first==-1)
			cout<<"-1\n";
		else
		{
			int prs=0;
			for(i=k;i>=1;i--)
			{
				ans[i]^=mov[i][prs].second;
				prs=mov[i][prs].first;
			}
			for(i=1;i<=k;i++) cout<<ans[i];
			cout<<"\n";
		}
		for(i=0;i<=k+10;i++) s[i]=a[i]=inc[i]=ans[i]=0;
	}
	return 0;
}
```

---

## 作者：LYY_yyyy (赞：1)

这是哪门子 *2600？？？？

记 $f_{i,j}$ 表示从低到高考虑到第 $i$ 位，满足第 $0$ 到 $i$ 位所有限制，第 $i$ 位向上一位进位 $j$ 是否可行。转移就考虑这一位填 $1$ 还是 $0$ 即可 $O(1)$ 转移。注意到 $j$ 的最大值为 $\frac n2 +\frac n4+\cdots+\frac n{2^{k+1}}< n$，所以第二维开到 $n$ 即可，时空复杂度 $O(nk)$。

代码：

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define ll long long
#define all(b) b.begin(),b.end()
using namespace std;
int t;
vector<int> f[2000010],g[2000010],p[2000010];
string a[2000010];
string s;
int n,k;
int main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		cin>>s;
		reverse(all(s));
		s='0'+s;
		for(int i=1;i<=n;i++) cin>>a[i],reverse(all(a[i])),a[i]='0'+a[i];
		for(int i=0;i<=k;i++) f[i].clear(),f[i].resize(n+1),g[i].resize(n+1),p[i].resize(n+1);
		f[0][0]=1;
		for(int i=1;i<=k;i++)
		{
			int f0=0,f1=0;
			for(int j=1;j<=n;j++) 
			{
				if(a[j][i]=='0') f1++;
				else f0++;
			}
			for(int j=0;j<=n;j++)
			{
				if(!f[i-1][j]) continue;
				if((f0+j)%2==s[i]-'0') 
				{
					f[i][(j+f0)/2]=1;
					g[i][(j+f0)/2]=j;
					p[i][(j+f0)/2]=0;
				}
				if((f1+j)%2==s[i]-'0')
				{
					f[i][(j+f1)/2]=1;
					g[i][(j+f1)/2]=j;
					p[i][(j+f1)/2]=1;
				}
			}
		}
		if(!f[k][0]) cout<<-1<<"\n";
		else
		{
			int j=0;
			while(k)
			{
				cout<<p[k][j];
				j=g[k][j];
				k--;
			}
			cout<<"\n";
		}
	}
	return 0;
}

```

---

## 作者：lbh666 (赞：0)

## 思路分析

### 暴力

注意到异或可以拆位，也就是说，整体异或的贡献可以被拆为每一位异或的贡献的和。

然后我们暴搜每一位是 $0$ 还是 $1$，$\mathcal O(1)$ 算出这一位异或的贡献（$0$ 只能贡献给 $1$，$1$ 只能贡献给 $0$，因此是 $\mathcal O(1)$ 的），找出一组总和等于 $s$ 的解即可。

### 正解

我们从暴搜中得到启发，为何不用 dp？

记 $f_{i,j}$ 为从低位到高位考虑，考虑到第 $i$ 位，向 $i+1$ 位进 $j$ 的可能性（即给 $i+1$ 加上 $j \times 2^{i-1}$ 的可能性）。

类似地，记 $lst_{i,j}$ 表示从哪一个点转移过来，$wk_{i,j}$ 表示最后填这位时是 $0$ 还是 $1$。

再记一个 $cnt_i$ 表示从低位到高位考虑，第 $i$ 位 $1$ 的个数。

考虑使用刷表法，从 $f_{i-1,j}$ 刷表过来，根据进位后奇偶性的分析，转移式就比较显然了，具体转移参见代码。

最后，若 $f_{n,0} = 0$，一定无解。否则，不断用 $lst$ 往前跳，一边跳一边输出 $wk$ 对应的值即可。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,l,r) for(int i=l;i<=r;++i)
using namespace std;

const int N=2e6+5;
int T,n,k;
string s,a[N];
vector<int> dp[N],lst[N],wk[N];
int cnt[N];//1的个数 
//dp[i][j]->低位到高位的顺序，考虑到第i位，向第i+1位进j(即加上j* (2^(i-1)) ) 的可能性 
//类似地，lst[i][j]记录从哪一个节点转移过来，wk[i][j]表示这位是0还是1 

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		cin>>n>>k;
		cin>>s;
		reverse(s.begin(),s.end());
		s="#"+s;
		rep(i,0,k){
			dp[i].clear();
			lst[i].resize(n+5);
			wk[i].resize(n+5);
			dp[i].resize(n+5);
			cnt[i]=0;
		}
		rep(i,1,n){
			cin>>a[i];
			reverse(a[i].begin(),a[i].end());
			a[i]="@"+a[i];
			rep(j,1,k){
				cnt[j]+=(a[i][j]-'0'); 
			}
		}
		dp[0][0]=1;
		rep(i,1,k){
			rep(j,0,n){
				//从dp[i-1][j]刷表而来
				if(!dp[i-1][j])continue;
				if((j+cnt[i])%2==(s[i]-'0')){ //当前位选0的贡献 
					dp[i][(j+cnt[i])/2]=1;
					lst[i][(j+cnt[i])/2]=j;
					wk[i][(j+cnt[i])/2]=0;
				}
				if((j+n-cnt[i])%2==(s[i]-'0')){ //当前位选1的贡献 
					dp[i][(j+n-cnt[i])/2]=1;
					lst[i][(j+n-cnt[i])/2]=j;
					wk[i][(j+n-cnt[i])/2]=1;
				}    
			}
		}
		if(!dp[k][0]){
			cout<<"-1\n";
			continue;
		}
		int now=k,p=0;
		while(now){
			cout<<wk[now][p];
			p=lst[now][p];
			now--;
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：freoepn (赞：0)

考虑从低位到高位统计，$dp_{i,j}$ 表示 $1$ 到 $i$ 位都已经匹配完成，并向 $i+1$ 位产生了 $j$ 的进位，因为每一位定多向下一位产生 $\lfloor \frac{n}{2} \rfloor$ 的进位，则进位数顶多为 $\frac{n}{2} + \frac{n}{4}+ \frac{n}{8} …$，这是一个调和级数，一定小于等于 $n$，所以进位数顶多为 $n$，直接 $dp$ 即可。

---

