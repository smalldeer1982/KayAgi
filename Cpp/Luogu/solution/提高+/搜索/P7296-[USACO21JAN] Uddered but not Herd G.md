# [USACO21JAN] Uddered but not Herd G

## 题目描述


一个鲜为人知的事实是，奶牛拥有自己的文字：「牛文」。牛文由 26 个字母 'a' 到 'z' 组成，但是当奶牛说牛文时，可能与我们所熟悉的 'abcdefghijklmnopqrstuvwxyz' 不同，她会按某种特定的顺序排列字母。

为了打发时间，Bessie 的表妹 Mildred 在反复哼唱牛文字母歌，而 Farmer Nhoj 好奇她唱了多少遍。

给定一个小写字母组成的字符串，为 Farmer Nhoj 听到 Mildred 唱的字母，计算 Mildred 至少唱了几遍完整的牛文字母歌，使得 Farmer Nhoj 能够听到给定的字符串。Farmer Nhoj 并不始终注意 Mildred 所唱的内容，所以他可能会漏听 Mildred 唱过的一些字母。给定的字符串仅包含他记得他所听到的字母。

注意：本题每个测试点的时间限制为默认限制的两倍。 

## 说明/提示

Mildred 至少唱了三遍牛文字母歌。有可能 Mildred 只唱了三遍牛文字母歌，如果牛文字母表以 "mildre" 开头，并且 Farmer Nhoj 听到了以下被标记为大写的字母。

```
MILDREabcfghjknopqstuvwxyz
milDREabcfghjknopqstuvwxyz
mildrEabcfghjknopqstuvwxyz
```

#### 测试点性质：

 - 测试点 1-5 中，Farmer Nhoj 仅听到出现在 Mildred 或 Bessie 的名字中的字母。
 - 测试点 6-16 中，Farmer Nhoj 从未听到任何出现在 Mildred 名字中的字母。

供题：Nick Wu，Brian Dean 

## 样例 #1

### 输入

```
mildredree```

### 输出

```
3```

# 题解

## 作者：pocafup (赞：18)

Uddered but not Herd 题解

~~之前交错题解区了~~

神仙状压dp，赛时联想到状压的时候简直惊了。以后自己出题也会往这个方面想了

发现如果某个字母没有在他听到的东西内出现，那么这个字母毫无意义。同理，如果一个字母出现过，那么他必然有意义。

于是，题目转化为求一个子串，每次让这个子串跟给出的字符串进行匹配，求最小的匹配次数。

没思路？看一眼数据范围，发现刚刚好有6个字母不需要用。一共个 26 字母，6个不用，算下来只用计算20个字母。符合范围的好像只有状压了。

设当前的子串为 $ch$， 考虑在子串后面加入字母算贡献。发现每个字母都是独立的。换言之，不论之前子串的顺序如何，这个字母跟之前子串中的字母产生的贡献都相等。如果在字符串中当前字母前一个位置的字母在子串出现过，那么加入这个字母一定会使最终朗诵次数减少一次。

枚举二元组暴力预处理出当子串存在字母 $i$，目前要加入字母 $j$ 时的贡献，然后状压一下，每次加字母时积累贡献即可。字母要离散一下。答案即为 $n$ - 贡献

赛时写的方法是 $O(k^2n + k^2\times 2^k)$ 的，但应该可以通过一些状压上的小优化做到 $O(k^2n + k\times 2^k)$ 

代码只放主函数，需要全部代码的私戳
```cpp
signed main(){
  cin >> ch;
  int n = ch.size();
  For(i,0,ch.size()-1) {
    pos[i+1] = (int)(ch[i]-'a')+1;
    mp[pos[i+1]] = true;
  }
  For(i,1,26) if (mp[i]) head[i] = ++tot;
  For(i,1,n) pos[i] = head[pos[i]];//简单的离散,懒人直接用 map 瞎弄了
  //pref i j : 在字母 i 前一位的字母 j 数量
  For(i,1,tot){
    For(j,1,tot){
      int v = 0,tmp = 0;
      For(k,1,n)if (pos[k]==i && pos[k-1]==j) tmp++;
      pref[i][j]=  tmp;
    }
  }
  For(i,1,1<<tot){
    For(j,1,tot){
      if ((i>>(j-1)) & 1) continue;
      int tmp = 0;
      For(k,1,tot) if ((i>>(k-1))&1) tmp += pref[j][k];//将所有贡献累计
      dp[i+(1<<(j-1))] = chkmax(dp[i+(1<<(j-1))],dp[i]+tmp);//转移
      ans = chkmax(ans,dp[i+(1<<(j-1))]);//人懒,不想去想最终状态,直接取max了
    }
  }
  cout << n-ans;
}
```

---

## 作者：Diaоsi (赞：12)

[[USACO21JAN] Uddered but not Herd G](https://www.luogu.com.cn/problem/P7296)


首先考虑一个问题，如果字母表已经确定，如何将原串分割是最优的。

设原串为 $s$ ，原串中字母共有 $n$ 种，我们认为各个字符之间是可以比较的，在确定的字母表中，靠前的字母比靠后的字母小。

对于原串 $s$ ，若有 $s_i \geq s_{i+1}$ 显然 $s_i$ 和 $s_{i+1}$ 是要被“分割”开的

也就是说，对于这个确定的字母表，$s_i$ 和 $s_{i+1}$ 不会在同一个周期被念出来，$s_i$ 对答案的贡献为 $1$ 。

观察数据范围，发现 $n \leq 20$ ，这个数据范围是可以状压的，设集合 $S$ 表示当前加入的字母的集合，$f_S$ 表示 $S$ 集合中的字母对答案的贡献的最小值为多少。

维护向集合 $S$ 中加入字母 $c_j$ 的过程，根据我们上面得出的结论，$c_j$ 的贡献就是集合 $S$ 中满足字符位置为 $c_j$ 在原串中的下一位且小于等于 $c_j$ 的字符个数（相同的字符可能有多个位置满足要求），这个是可以预处理出来的。

于是根据上面的过程，我们可以得到状态转移方程：

$$f_S=\min_{c_j \in S}\{f_{S\backslash \{c_j\}}+\sum_{c_k \in S} cost_{j,k}\}$$

令初始状态为 $f_{\varnothing}=1$，因为要将第一次念字母表计算进去，最终答案为 $f_{S=\{c_1,c_2, \dots, c_n\}}$。

其中 $cost_{j,k}$ 表示在原串中所有 $c_j$ 的位置中满足 $c_k \leq c_j$ 且 $c_k$ 为 $c_j$ 的下一位的个数，将原串 $c$ 离散化之后可以预处理出来。

时间复杂度: $\mathcal{O(2^n\ast n^2)}$ 。

既然你能找到这题，我相信你能瞬间做出来的。

```Code:```

```cpp
#include<bits/stdc++.h>
typedef long long LL;
typedef long double LD;
using namespace std;
const int N=21,M=100010,INF=0x3f3f3f3f;
inline int Max(int x,int y){return x>y?x:y;}
inline int Min(int x,int y){return x<y?x:y;}
inline void Swap(int &x,int &y){x^=y^=x^=y;}
int n,m,ans=INF,f[1<<20],a[M],b[M],c[N][N];
char s[M];
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)b[i]=s[i];
	sort(b+1,b+n+1);
	int m=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+m+1,s[i])-b-1;
	for(int i=1;i<n;i++)c[a[i]][a[i+1]]++;
	memset(f,0x3f,sizeof(f));f[0]=1;
	for(int S=1;S<(1<<m);S++)
		for(int j=0;j<m;j++)
			if(S&1<<j){
				int sum=f[S^1<<j];
				for(int k=0;k<m;k++)
					if(S&1<<k)sum+=c[j][k];
				f[S]=Min(f[S],sum);
			}
	printf("%d\n",f[(1<<m)-1]);
	return 0;
}
```


---

## 作者：ETHANK (赞：10)

## P7296 [USACO21JAN] Uddered but not Herd G
题意： 给定字符串$S$。对于任意一个字母排列$P$，有将$S$划分成若干段后每一段都是$P$的子序列的最少段数。问所有排列最少段数的最小值。

数据范围：$1\le|S|\le10^5,|\Sigma|\le20$。

思路：看到数据范围对字符集的限制，想到状压$dp$。

首先如果确定了一个排列$P$，如何做出最少的分段呢？把$S$中的字符按照给定排列分配大小，我们发现如果$S[i]>=S[i+1]$，那么在第$i$个字符和第$i+1$个字符之间就必须进行划分，且这样的划分是最优的。方便起见，下文将字符集大小表述为$k$。定义$cost[i][j]$为$P$中第$i$个字符和第$j$个字符在$S$中的相邻次数，我们有：
$$ans=\sum_{i=1}^{k}\sum_{j=i-1}^{i}cost[i][j]$$
不难发现，如果我们逐个将字符填入$P$，新填入的字符$i$造成的代价只与前面字符的集合有关、而与排列无关。我们可以用状态$sta$来表示当前所选取字符的集合，令$f[sta]$为这些字符排列后的最小代价，$g[i][sta]$为将$i$放入该排列末尾后的代价，得出$dp$方程为：
$$f[i|1<<j]=\min(f[i|1<<j],f[i]+g[j][i|1<<j])$$
$$g[i][sta]=g[i][sta-(1<<j)]+cost[i][j]$$

时间复杂度：$O(k2^k)$。

代码：
```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(b);i>=(a);i--)
using namespace std;
inline int min(int a,int b){return a<b?a:b;}
int n,m,id[30],f[1<<20],up;
int a[30][30],g[26][1<<20];
bool vis[30];
string s;
int main(){
    cin>>s;
    n=s.size();
    rep(i,0,n-1)vis[s[i]-'a']=1;
    rep(i,0,25)if(vis[i])id[i]=m++;//字符集
    up=(1<<m)-1;
    rep(i,0,n-2)a[id[s[i]-'a']][id[s[i+1]-'a']]++;//预处理cost
    rep(i,0,m-1){//把第j个字母加入排列的代价
        rep(j,0,m-1)rep(k,1<<j,(2<<j)-1)
            g[i][k]=g[i][k-(1<<j)]+a[i][j];
    }
    rep(i,1,up)f[i]=1000005;//最大值
    rep(i,0,up){
        rep(j,0,m-1){
            if(!((i>>j)&1)){
                //把第j个字母加入排列
                f[i|1<<j]=min(f[i|1<<j],f[i]+g[j][i|1<<j]);
            }
        }
    }
    printf("%d\n",f[up]+1);
    return 0;
}
```

---

## 作者：Yang818 (赞：4)

看了一下其他大佬写的题解，发现没有人写如何将这题用记忆化搜索做的，本蒟蒻特此写了一篇题解。
### [题目传送门](https://www.luogu.com.cn/problem/P7296)

## 分析：
标准 $dp$ 题目，~~这么标准的 $dp$ 题目居然没人用记忆化~~。

我们来寻找一下规律哈：

不难发现，其实我们只用每次查看相邻的两个字母就行了，为什么呢？

我们拿 $apple$ 来举个例子：

先查看 $ap$ 如过给定的字母表里面$a<p$，那么 $ap$ 一定在一个循环里面，如果 $a>p$ ，那么就是 $......p......a.....$ ，所以这肯定是第一次循环到 $a$ ,第二次再循环到 $p$ ，肯定是两次循环。所以如果是第二种情况，答案就要 $+2$ 。有了这样的规律，我们继续往下走。

## 输入

根据分析，我们输入只用一个一个字母去读，然后和前面的字母比较就行了。这边展示其中一个读入的方法：
```cpp
int last = -1;
char c;
while (cin >> c) {
	......
}
```
在省略号的部分就可以做处理了。

## 记忆化

要是按照朴素做的还，只能拿30分，还是要记忆化。首先要先明白一点，要是想做记忆化，这个函数必须是一个纯函数，就是我们所说的 $pure$ $function$ 什么是纯函数？其实就是一个函数只依靠自己的参数，不依靠全局变量。这样的话，我们就需要把 $used$ 数组放到 $dp$ 函数的参数里面。明显，太大了，不行，怎么优化呢？

### 敲黑板

这里本蒟蒻讲一个方法：

我们可以把数组的每一维都转成二进制的一个数，这样子还可以把 $step$ 一维也省掉，因为 $used$ 这个变量的二进制当中 $1$ 的数量就是$step$ 的数量。真是一举两得啊！要调出来第 $n$ 位有没有被用过可以用一个掩码 
```cpp
musk=1<<n;
```
再用 $used & musk$ 是不是 $0$ 就可以知道第 $n$ 位有没有被用过了。

## 代码
```
#include<iostream>

using namespace std;
int cnt[26][26];
int ch[20];
bool exist[26];
int n;
int cache[1<<20];
int dp(int step, int used) { // pure function
  if (step == 0) return 1;
  if (cache[used] > 0) return cache[used];
  int ans = 1000000;
  for (int i = 0; i < n; ++i) {
    int mask = 1 << i;
    if ((used & mask) == 0) { //掩码
      int sum = cnt[ch[i]][ch[i]];
      for (int j = 0; j < n; ++j)
        if ((used & (1 << j)) != 0)
          sum += cnt[ch[i]][ch[j]];
      ans = min(ans, dp(step - 1, used ^ mask) + sum);
    }
  }
  return cache[used] = ans;
}

int main() {
  int last = -1;
  char c;
  while (cin >> c) {
    if (last >= 0) {
      ++cnt[last][c-'a'];
    }
    if (exist[c - 'a'] == false) {
      ch[n] = c - 'a';
	  ++n;
	  exist[c - 'a'] = true;
	}
    last = c - 'a';
  }
  cout << dp(n, 0); 
} 
```
望通过，谢谢。

---

## 作者：Eibon (赞：3)

发现原字母大小并无实际意义，不妨先进行离散化。

思考什么时候，一定会增加 $1$ 个周期。

发现在字母 $a_{i}$ 出现在字母 $a_{i+1}$ 时会发生，此时会对序列产生 $1$ 的贡献。

根据测试点性质，发现除去 Mildred 后还剩下 $20$ 个字母。于是联想到状压。

设 $dp_{s}$ 表示当前字母选取状态为 $s$ 时的对答案产生贡献。

设 $c_{i,j}$ 表示字母 $i$ 对字母 $j$ 产生的贡献。

则

$$dp_{s} \gets \min_{a_{j} \in s} (dp_{s},dp_{s \backslash a_{j}}+ \sum_{c_{k} \in s} c_{j,k})$$

初始化时 $dp_{0}$ 为 $1$，因为至少要唱 $1$ 遍字母歌。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+5;
const int inf=0x3f3f3f3f3f3f3f3f;
int T=1,n,m,ans=inf;
int a[maxn],b[maxn],c[25][25],dp[(1<<20)+5];
char s[maxn];
void solve()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++){
		b[i]=s[i];
	}
	sort(b+1,b+n+1);
	int m=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+m+1,s[i])-b;
	}
	for(int i=1;i<n;i++){
		c[a[i]][a[i+1]]++;
	}
	memset(dp,0x3f,sizeof dp);
	dp[0]=1;
	for(int s=1;s<(1<<m);s++){
		for(int i=1;i<=m;i++){
			if(s&(1<<(i-1))){
				int num=dp[s^(1<<(i-1))];
				for(int j=1;j<=m;j++){
					if(s&(1<<(j-1))){
						num+=c[i][j];
					}
				}
				dp[s]=min(dp[s],num);
			}
		}
	}
	printf("%lld\n",dp[(1<<m)-1]);
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
//	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：lory1608 (赞：2)

显然，$|\sum|\leq 20$ 考虑状压DP。

对于每两个相邻的位置 $i$ 与 $i+1$ ，只有当 $s[i]$在字母串中的位置在 $s[i+1]$ 之后才会产生 $1$ 的贡献，状压DP并枚举第 $i$ 个选择的字母在最前面或者最后面即可。

复杂度$O(2^{|\sum|}+|S|)$ 。

```cpp
//#pragma GCC optimize(4)
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(u) for(int i=p[u];i!=-1;i=e[i].nxt)
#define PII pair<int,int>
#define ll long long
#define pb push_back
#define PLL pair<ll,ll>
#define fi first
#define se second
#define sz(x) (int)(x.size())
#define rd (rand()<<16^rand())
#define gc getchar()//(_p1==_p2&&(_p2=(_p1=_buf)+fread(_buf,1,100000,stdin),_p1==_p2)?EOF:*_p1++)
using namespace std;
char _buf[100000],*_p1=_buf,*_p2=_buf;
inline int gi()
{
	int x=0,f=1;
	char ch=gc;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=gc;
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=gc;
	}
	return (f==1)?x:-x;
}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int maxn=1e5+5;
char s[maxn];
int dp[2][1<<20],now,last;
bool vis[maxn];
int cnt[26][26],n,cnt2[26][26],tot;
int mp[maxn];
vector<int>vec[26];
inline void init()
{

}
inline void input()
{
	scanf("%s",s+1);
	n=strlen(s+1);
}
inline int count(int x){int ret=0;while(x){ret+=x&1;x>>=1;}return ret;}
inline int calc_front(int x,int j)
{
	int ret=0;
	FOR(i,0,tot-1)if(x>>i&1)ret+=cnt[i][j];
	return ret;
}
inline int calc_back(int x,int j)
{
	int ret=0;
	FOR(i,0,tot-1)if(x>>i&1)ret+=cnt2[i][j];
	return ret;
}
inline void solve()
{
	///cnt before it cnt2 after it
	FOR(i,1,n)vis[s[i]-'a']=1;
	FOR(i,0,25)
	{
		if(vis[i])
		{
			mp[i]=tot;
			tot++;
		}
	}
	FOR(i,1,n-1)cnt[mp[s[i]-'a']][mp[s[i+1]-'a']]++;
	FOR(i,2,n)cnt2[mp[s[i]-'a']][mp[s[i-1]-'a']]++;
	FOR(i,0,(1<<tot)-1)vec[count(i)].pb(i);
	memset(dp,0x3f,sizeof(dp));
	dp[now][0]=0;
	FOR(i,1,tot)
	{
		now=now^1,last=now^1;
		memset(dp[now],0x3f,sizeof(dp[now]));
		for(auto x:vec[i-1])
		{
			if(dp[last][x]>n)continue;
			FOR(j,0,tot-1)
			{
				if(x>>j&1)continue;
				dp[now][x|(1<<j)]=min(dp[now][x|(1<<j)],min(calc_front(x,j),calc_back(x,j))+cnt[j][j]+dp[last][x]);
			}
		}
	}
	printf("%d\n",dp[now][(1<<tot)-1]+1);
}
int main()
{
	int T=1;
//	T=gi();
	while(T--)
	{
		init();
		input();
		solve();
	}
	return 0;
}
```

---

## 作者：MolotovM (赞：2)

## [P7296 [USACO21JAN] Uddered but not Herd G](https://www.luogu.com.cn/problem/P7296)
**题意：**
给定字符串s，试构造一种小写字母排列p，使得将s划分为若干组，每组字符串均为p的子序列，且使得组数最少，输出最少组数。

保证s长度小于等于1e5且s出现的不同字符不超过二十个



**题解：**

因为$|p|$很小，可以考虑状压DP

正难则反，考虑把每个字符划分为一段

如果相邻两个字母在排列中顺序就把他们合并起来

设$dp[i]$表示当前的排列中已经选择了的字母集合

更新时枚举下一个字母的选择

对于在排列中出现过的字母如果在原串中位于当前字母之后

则他们无法合并，产生对答案的贡献

可以先处理出每一对相邻字母数量

记忆化搜索即可

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int Read(){
  	int s = 0 , w = 1;
	char ch = getchar();
	while(ch > '9' || ch < '0'){
		if(ch == '-') w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		s = (s << 1) + (s << 3) + ch - '0';
		ch = getchar();
	}
	return s * w;
}
const int MAXN = 1e5 + 50;
char s[MAXN];
int a[MAXN];
int p[25][25];
int n;
int id[300],tot = 0;
int f[(1 << 21) + 10];
int DP(int ss){
	if(ss == (1 << tot) - 1) return 0;
	if(f[ss]) return f[ss];
	int res = 0;
	for(int i = 1 ; i <= tot ; i ++){
		if((ss >> (i - 1)) & 1) continue;
		int tmp = 0;
		for(int j = 1 ; j <= tot ; j ++){
			if((ss >> (j - 1)) & 1){
				tmp += p[j][i];
			}
		}
		res = max(res,tmp + DP((1 << (i - 1)) | ss));
	}
	return (f[ss] = res);
}
int main(){
	scanf("%s",s + 1);
	n = strlen(s + 1);
	for(int i = 1 ; i <= n ; i ++){
		if(!id[s[i]]) id[s[i]] = ++ tot;
		a[i] = id[s[i]];
	}
	for(int i = 1 ; i + 1 <= n ; i ++){
		p[a[i]][a[i + 1]] ++;
	}
	int ans = 0x3f3f3f3f;
	for(int i = 1 ; i <= 20 ; i ++){
		ans = min(ans,n - DP(1 << (i - 1)));
	}
	cout << ans << endl;
 	return 0;
}
```

---

## 作者：LiuQJun_1119 (赞：2)

这道题也是改了几个小时，虽然代码不长，但非常考验对状压 DP 的理解和运用。

这题目的表达很有趣

 - 测试点 1-5 中，Farmer Nhoj 仅听到出现在 Mildred 或 Bessie 的名字中的字母。
 - 测试点 6-16 中，Farmer Nhoj 从未听到任何出现在 Mildred 名字中的字母。

最后的两句话看似没有任何意义，事实上告诉了我们这道题的数据范围，即这道题只有 20 个不同的字母，只用枚举 $2^{20}$ 种状态即可。

初始化：先将字母离散化，重新编号后记录两个字母相邻的次数 $a[i][j]$。即 $a[i][j]$ 表示编号为 $i$ 和 $j$ 的字母在原字符串中出现的次数。

那么我们就设 $f[i]$ 代表在 $i$ 的情况下顺序与字母表顺序相符的对数的最大值。

离散化之后，我们可以得到 $t$ 个不同的字母。这时我们枚举 $2^{t}$ 种状态 $s$。虽然 $s$ 是以十进制数表示的，但我们把它看作一个二进制数，它的第 $k$ 位就代表编号为 $k$ 的字母要不要选。

那么，到底怎么转移呢？我的思路是找 $s$ 中每一位要选的，然后我们从不选这一位的情况再转移到 $s$。具体请看代码注释。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5,MAXN=(1<<20),INF=2147483647;
int n,a[30][30],f[MAXN+5],h[30],t;
char s[N+5];
bool bz[30];
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++) bz[s[i]-'a']=true;
	for(int i=0;i<26;i++) if(bz[i]) h[i]=++t;//离散化
	for(int i=1;i<n;i++) a[h[s[i]-'a']][h[s[i+1]-'a']]++;//初始化
	for(int i=1;i<(1<<t);i++) f[i]=INF;//初始化
	f[0]=1;//同上
	for(int s=0;s<(1<<t);s++){//枚举情况
		for(int i=1;i<=t;i++){
			if(s&(1<<i-1)){//找到要选编号为i的字母
				int tt=s^(1<<i-1);
				int ss=f[tt];//不选这一位的状态
				for(int j=1;j<=t;j++) if(s&(1<<j-1)) ss+=a[i][j];//枚举其他要选的，计算选了编号为i的字母会发生的变化
				f[s]=min(f[s],ss);//更新f[s]
			}
		}
	}
	printf("%d",f[(1<<t)-1]);//输出答案
}
```

---

## 作者：JXR_Kalcium (赞：1)

## 题目大意
给出一个字符串 $s$，要找一个字串，按照这个字串给 $s$ 分段，求最少段数。  
例：当 $s=\textrm{mildredree}$，字串为 `mildre` 时，就可以划分为 $3$ 个部分，为 `mildre/dre/e`。

## 解题思路
### 暴力
题目中给出 $s$ 中的字母要么只有 `mildre`，要么只有除了 `mildre` 之外的所有字母，所以 $s$ 中最多只有 $20$ 个字母。于是我们可以通过深搜枚举这些字母所有的排列方式，再通过一次 $O(N)$ 的循环扫一遍，统计部分即可，时间复杂度 $O(20!$ $N)$。

### 状压 DP
很明显，就拿样例来说，字串中有一个 `de`，假如在 $s$ 中找到了 `ed`，那么肯定要再分一个段；同样对于 `md`、`ld` 等也是如此。于是我们就可以发现其实不用关心字串是什么，只要知道哪些字母出现过，以及哪些字母的位置相反即可。所以此题满足无后效性，最多又只有 $20$ 个字母，可以用状压 DP 来做。

先对 $s$ 中所有出现的字母离散化，按照字母表（$0\sim25$）顺序分别标号 $0\sim cnt-1$（出现的字母个数为 $cnt$），记录在 $t_i$ 中，然后统计 $s$ 中每两个相邻字母出现的个数 $c_{i,j}$。例如对于样例中的 $s$，就有离散化后的 $t_3=d=0,$ $t_4=e=1,$ $t_8=i=2\cdots$，这个时候 $c_{12,8}=1$（$m$ 和 $i$ 相邻）。

然后这 $cnt$ 种字母中每个都有选或不选（$1/0$）两种状态，于是就可以枚举 $1\sim 2^{cnt}-1$ 这些状态。设 $f_i$ 表示状态为 $i$ 时最少的分段数，那么我们可以枚举这一个状态中已经选了的字母 $j$，于是上一个转移过来的状态就应该是 $i-2^j$（$f_0=1$，因为一个都不选就只有一个段）。

接下来再去看，如果我们把 $j$ 加进来后会多出多少个段。可以再枚举一下已经选了的字母 $k$，那么多出来的段数自然就是 $c_{j,k}$。综上所述，动态转移方程为：

$f_i=\textrm{min}(f_i,f_{i-2^j}+\displaystyle\sum c_{j,k})$ $(1\le i\lt2^{cnt},$ $\textrm{binary}(i)_{j,k}=1)$（$\textrm{binary}$ 为转二进制）。

最后的答案即是 $f_{2^{cnt}-1}$，时间复杂度 $O(2^{cnt}\times cnt^2)$，最多只有 $419430400$ 次循环，开吸氧能过。

## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n,bz[31],t[31],c[31][31],cnt,f[2000001]={1},sum;
char s[100001];

int main()
{
	scanf("%s",s); n=strlen(s);
	for(int i=0; i<n; ++i) bz[s[i]-97]=1;
	for(int i=0; i<26; ++i) t[i]=bz[i]?cnt++:0;
	for(int i=1; i<n; ++i) ++c[t[s[i-1]-97]][t[s[i]-97]];
	for(int i=1; i<(1<<cnt); ++i) f[i]=INT_MAX;
	
	for(int i=1; i<(1<<cnt); ++i)
	{
		for(int j=0; j<cnt; ++j)
		{
			if(!(i&(1<<j))) continue; sum=0;
			
			for(int k=0; k<cnt; ++k)
			{
				if(i&(1<<k)) sum+=c[j][k];
			}
			
			f[i]=min(f[i],f[i-(1<<j)]+sum);
		}
	}
	
	printf("%d",f[(1<<cnt)-1]+1);
	return 0;
}
```
```

---

## 作者：ClearluvXL (赞：0)

# Uddered but not Herd G
## 思路
根据本题来看，肯定是有一个贪心的思路的：相邻的两个字符，如果编号是升序的话，在一轮里肯定是更优的。如果不是，那么肯定又唱了一轮。
 	
例子：`A...C...A` 。
 	
大写字母表示他听到了的。在常规字母表中，对于 `A..C` ，能在一轮中出现，对于 `C..A` ，因为字母表中 C 在 A 后。A 肯定就在第二轮了。
   
我们想让通过重新编号，让这样的**相邻非升序对**的个数最小。
   
根据题目最大的数据来看 **从未听到任何出现在 Mildred 名字中的字母**，所以本题最多有 20 个字母，可以联想到状压。
   
我们将出现的字母离散化，使我们能用二进制数的每一个 01 位表示他们是否被编号。一个二进制数表示一个 01 串，对应位置是 1 的表示这个字母已经分配了编号。假设当前有 $x$ 个位置是 1，现在要将一个 0 变为 1，那么对应的编号就为 $x+1$ ，这样我们就能保证每分配一个字母新的编号，所构成的相邻对都是非升序的。而我们要做的就是保证这个非升序对的数量最小。
   
很难动态展现这个分配编号的过程，我画了个图，但是尽量自己想象。
  
其实此时 1，2，3 编号具体是哪个字母已经不重要了，**你只需要知道那些字母对应位置的编号都比新编号 4 小**，因为我们只需要此时 $f_{stat}$ 的最小值和加入 4 所构成的新增非升序对的数量。
![](https://cdn.luogu.com.cn/upload/image_hosting/8buj3ycv.png)

现在我们状态里有 4 个 1，那么我们随机选择 3 个 1 保留，将剩余的那个 1 视作新分配编号的点，那么离散话后所有对应这个 1 的位置都会被分配上这个新编号 4，而此时与后面相邻的并且早就被分配编号的点一定会构成逆序对。如果此时有两个相邻的点都是新编号，那么他们构成非升序对。

## 代码
```c++
#include<bits/stdc++.h>
#define endl '\n'

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N=1e5+10;
const int INF=0x3f3f3f3f;

map<char,int> mp;
int n,tot; 
char s[N];
int cnt[30][30]; 

//贪心思路:尽可能的使其有最少的相邻两个数组成的逆序对

int id(int x){
	if(!mp[s[x]]) mp[s[x]]=++tot;
	return mp[s[x]];
}//end

int f[1<<21];

int main(){
	
//	freopen("notherd.in","r",stdin);
//	freopen("notherd.out","w",stdout);
	
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin>>(s+1);
	n=strlen(s+1);
	
	for(int i=1;i<n;i++){
		cnt[id(i)][id(i+1)]++;//预处理出相邻点对的数量
	}
	
	memset(f,INF,sizeof f);
	
	f[0]=1;
	
	for(int stat=1;stat<1<<tot;stat++){
		for(int j=0;j<tot;j++){
			if((stat>>j)&1){
				int lststat=stat^(1<<j);//将第j位变为0
				int sum=cnt[j+1][j+1];
				//很重要，相等也要增加次数
				//sum是将该字母变成加入的贡献
				for(int k=0;k<tot;k++){
					if((lststat>>k)&1) sum+=cnt[j+1][k+1];
				}
				f[stat]=min(f[stat],f[lststat]+sum);
			}
		}
	}
	
	cout<<f[(1<<tot)-1]<<endl;	
	
	return 0;
}//end

```

---

