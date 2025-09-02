# x-prime Substrings

## 题目描述

You are given an integer value $ x $ and a string $ s $ consisting of digits from $ 1 $ to $ 9 $ inclusive.

A substring of a string is a contiguous subsequence of that string.

Let $ f(l, r) $ be the sum of digits of a substring $ s[l..r] $ .

Let's call substring $ s[l_1..r_1] $  $ x $ -prime if

- $ f(l_1, r_1) = x $ ;
- there are no values $ l_2, r_2 $ such that 
  - $ l_1             \le l_2 \le r_2 \le r_1 $ ;
  - $ f(l_2, r_2) \neq x $ ;
  - $ x $ is divisible by $ f(l_2, r_2) $ .

You are allowed to erase some characters from the string. If you erase a character, the two resulting parts of the string are concatenated without changing their order.

What is the minimum number of characters you should erase from the string so that there are no  $ x $ -prime substrings in it? If there are no  $ x $ -prime substrings in the given string $ s $ , then print $ 0 $ .

## 说明/提示

In the first example there are two $ 8 $ -prime substrings "8" and "53". You can erase these characters to get rid of both: "116285317". The resulting string "1162317" contains no $ 8 $ -prime substrings. Removing these characters is also a valid answer: "116285317".

In the second example you just have to erase both ones.

In the third example there are no $ 13 $ -prime substrings. There are no substrings with the sum of digits equal to $ 13 $ at all.

In the fourth example you can have neither "34", nor "43" in a string. Thus, you have to erase either all threes or all fours. There are $ 5 $ of each of them, so it doesn't matter which.

## 样例 #1

### 输入

```
116285317
8```

### 输出

```
2```

## 样例 #2

### 输入

```
314159265359
1```

### 输出

```
2```

## 样例 #3

### 输入

```
13
13```

### 输出

```
0```

## 样例 #4

### 输入

```
3434343434
7```

### 输出

```
5```

# 题解

## 作者：Alex_Wei (赞：11)

- Update on 2022.11.7：重写题解。

*[CF1400F x-prime Substrings](https://www.luogu.com.cn/problem/CF1400F)

不错的题目。

题目限制出现 “不能出现某字符串”，首先考虑将所有非法字符串拎出来建 ACAM。因为 $x$ 的真因数均不能作为数码，所以 $1$ 不可以作为数码，这样一来非法字符串的数量就很少了。爆搜发现对于 $x = 19$，建出的字典树总大小为 $S = 4852$，可以接受。

因此，设 $f_{i, j}$ 表示将 $s[1, i]$ 删去若干字符后合法，且在 ACAM 上匹配到状态 $j$ 的最小代价。枚举是否删去当前字符转移即可。时间复杂度 $\mathcal{O}(|s|S)$。[代码](https://codeforces.com/contest/1400/submission/179830052)。

---

## 作者：ZigZagKmp (赞：6)

本文同步发表于[我的cnblog](https://www.cnblogs.com/ZigZagKmp/p/13563143.html)

本场题解可见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1400-edu-94-solution)
## 题意简述
给定一个数字字符串$s$，定义$f(l,r)$为$s_l,s_{l+1},\cdots,s_{r}$的数字和。

定义一个区间$[l,r]$是$x-prime$的，当且仅当满足如下条件：

- $f(l,r)=x$
- 不存在$[l,r]$的子区间$[l_2,r_2]$，使得$f(l_2,r_2)$是$x$的真因数。

求最少要删除$s$中的字符个数，使得删除后的$s$不存在$x-prime$区间。

$1\le |s|\le 1000$，$1\le x\le 20$。
### 算法考察
特殊性质观察，AC自动机上DP
## 算法分析
通过某种方法我们可以发现$x\le 20$的范围内$x-prime$的字符串很少，最多的是$x=19$时，共有2399个。

因此我们可以把所有的$x-prime$生成出来，问题就转化为对给定的字符串$s$，求其最长子序列，使得这个子序列不存在最多$2399$个非法字符串。

这是一个经典问题，我们考虑AC自动机上DP。

设计状态dp[i][j]表示考虑前$i$个字符的子序列，其中如果放在AC自动机上匹配，当前状态处于$j$的最长子序列长度。

考虑下一步的转移，不难写出状态转移方程：
$$dp(i,j)=\min{\{dp(i-1,j),dp(i-1,k)+1\}}$$

其中ch[k][s[i]]=j，且$j$不是某一个非法字符串的终末状态。

可以使用滚动数组优化空间，总时间复杂度为$O(nm)$，其中$m$为建出的AC自动机总状态数。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
#define maxm 2505
#define inf 0x3f3f3f3f
#define LL long long
#define mod 1000000007
#define local
template <typename Tp> void read(Tp &x){
	int fh=1;char c=getchar();x=0;
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c&15);c=getchar();}x*=fh;
}
int n,m,X;
string s0;
int ch[maxm*10][10],fail[maxm*10],edp[maxm*20],tot;
void ins(string ss){
	int p=0;
	for(unsigned i=0;i<ss.size();i++){
		int dir=ss[i]-'0';
		if(!ch[p][dir])ch[p][dir]=++tot;
		p=ch[p][dir];
	}
	edp[p]++;
}
void build(){//AC自动机初始化
	queue<int>q;int p=0;
	for(int i=1;i<10;i++)
		if(ch[0][i])q.push(ch[0][i]),fail[ch[0][i]]=0;
	while(!q.empty()){
		p=q.front();q.pop();
		for(int i=1;i<10;i++){
			if(ch[p][i])fail[ch[p][i]]=ch[fail[p]][i],q.push(ch[p][i]);
			else ch[p][i]=ch[fail[p]][i];
		}
	}
}
int dp[2][maxm*10];
int check(string ss){//暴力检验，可以通过
	int sm=0;
	for(int l=0;l<ss.size();l++){
		sm=0;
		for(int r=l;r<ss.size();r++){
			sm+=ss[r]-'0';
			if(sm!=X&&X%sm==0)return 0;
		}
	}
	return 1;
}
void generate(string st,int sm){
	if(sm>X)return;
	if(sm==X){
		if(check(st))ins(st);
		return;
	}
	for(int i=1;i<10;i++){
		generate(st+(char)(i+'0'),sm+i);
	}
}
signed main(){
	cin>>s0;
	n=s0.size();
	read(X);
	generate("",0);//生成所有x-prime
	build();
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	int p=1,q=0;
	for(int i=0;i<n;i++){
		swap(p,q);
		for(int j=0;j<=tot;j++)dp[q][j]=inf;
		for(int j=0;j<=tot;j++){
			dp[q][j]=min(dp[q][j],dp[p][j]+1);//转移1
			if(!edp[ch[j][s0[i]-'0']])dp[q][ch[j][s0[i]-'0']]=min(dp[q][ch[j][s0[i]-'0']],dp[p][j]);//转移2
		}
	}
	int ans=inf;
	for(int i=0;i<=tot;i++)ans=min(ans,dp[q][i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Suiseiseki (赞：5)

官方题解看懂了，但是想不到一个高效的构造方法，所以放弃。（还是菜，~~虽然后来发现暴力就能过~~

翻了一下提交记录学到了另一个做法。

我们考虑 DP，设$f[i][mask]$表示当前已经到了第$i$个位置，前缀和表示为$mask$时向后的最小删除个数。

这样的转移方法就是枚举当前位置选或不选，然后往把一个位置的 DP 值拿过来即可。

然后判断前缀和是否合法也很简单，先判断前缀和中有没有$x$（大于$x$的前缀和已经全部可以删掉了），如果有再判断有没有前缀和是$x$的约数的。

但是很明显这种方法会有反例，但是我们发现其实如果出现$x$的约数的话，那么前缀和中比这个约数大的（也就是在前缀和中构成这个约数之前的数）可以全部删掉了，这样的话正确性得到了保证，还减少了状态数。

但是这样的话粗略上界是$O(n\cdot d)$（其中$d$为有效的状态数）的，看起来很不能过的样子。

但是本题的性质保证$d$不会很大（更加准确一些的说，是不会超过$5000$），所以这种做法能够通过。

存储状态的话直接用 unordered_map 就可以了。

代码：[My Blog](https://www.cnblogs.com/withhope/p/13574978.html)

---

## 作者：Sanyueyetu (赞：1)

这里是不需要 acam 的做法。

## solution

看到 $x \leq 20$ 考虑状压。

我们用 $f_{i,j}$ 表示当前在第 $i$ 位，用 $j$ 表示以 $i$ 结尾的子串的和的集合。

如果 $x$ 在 $j$ 这个集合中，且 $j$ 当中没有 $x$ 的约数，那么当前位就必须删去。

我们可以进一步发现，大于等于 $x$ 的数是不用记录的，这是显然的。

大于等于 $j$ 当中最小的 $x$ 的约数的数也不需要记录，因为包含这个子串的串必定有一个子串的和等于 $j$ 中的最小约数，所以必定不 x-prime。

也不用记录 1，因为包含 1 的子串肯定不 x-prime。

然后 $j$ 的规模就降到了 $2^{18}$，开一下滚动数组就能过了，实测跑得飞快。
## Code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lowbit(x) x&-x
int f[1<<18],yin,lst[1<<18],ans=1e18;
int cnt,x,n;
string s;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>s>>x;
    n=s.size();
    s='#'+s;
    if(x<=2){
        for(int i=1;i<=n;i++){
            if(s[i]=='0'+x){
                cnt++;
            }
        }
        cout<<cnt;
        return 0;
    }
    for(int i=2;i*i<=n,i<n;i++){
        if(x%i==0){
            yin|=(1<<(i-2));
            yin|=(1<<(x/i-2));
        }
    }
    for(int j=1;j<(1<<(x-2));j++){
        f[j]=1e18;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<(1<<(x-2));j++){
            lst[j]=f[j];
            f[j]=1e18;
        }
        for(int j=0;j<(1<<(x-2));j++){
            if(lst[j]==1e18) continue;
            int num=s[i]-'0';
            if(num==1||num>x){
                f[0]=min(f[0],lst[j]);
                continue;
            }
            if(num==x){
                f[j]=min(f[j],lst[j]+1);
                continue;
            }
            int nxt=(j<<num)&((1<<(x-2))-1);
            if(num<x) nxt|=(1<<(num-2));
            int temp=(nxt&yin);
            int bit=lowbit(temp);
            if(((j<<num)>>(x-2)&1)&&bit==0){
                f[j]=min(f[j],lst[j]+1);
                continue;
            }
            f[j]=min(f[j],lst[j]+1);
            if(bit==0){
                f[nxt]=min(f[nxt],lst[j]);
            }
            else{
                f[nxt&(bit-1)]=min(f[nxt&(bit-1)],lst[j]);
            }
        }
    }
    for(int j=0;j<(1<<(x-2));j++){
        ans=min(ans,f[j]);
    }
    cout<<ans;
}
```

---

## 作者：wind_whisper (赞：1)

## $\text{Foreword}$
虽然做法同样是自动机上 dp，但切入点似乎不太一样？  
最差情况下（$n=19$）的状态数是 3946，比 AC 自动机的做法少将近一半。  
## $\text{Solution}$
首先，显然本题应该是 dp。  
既然是 dp，我们就要想想我们需要记录什么。  
一个比较直观的想法是：记录一下最后填的几位数。那么我们要确定需要记录到哪几位。  
设当前填的是第 $i$ 位。维护一个指针 $j$ 往前扫，记录 $now=\sum_{p=j}^ia_p$。  
分几种情况讨论：  
1. $now> x$。那么显然 $j$ 和之前的位都不可能成为要求串的左端点了，把这些前缀去掉即可。
2. $now<x\&\&now|x$。此时如果左端点在 $j$ 或者更左，那么得到的串必然含有一个加和为 $now$ 的子串，也就必然不合法，所有也可以把 $j$ 及其前面的前缀去掉。
3. $now=x$。由于没有被第 2 条判掉，此时的串 $(j,i)$ 必然不含有加和为 $x$ 真因子的子串，所以此时必然是走到了一个非法状态。
4. 前三种情况都不满足，那么就保留第 $j$ 位，继续左移 $j$ 指针考虑前一位即可。

通过这样的转移，我们就建出了一个自动机。由于不能填 1 ，它的结点不会太多，写个简单的暴搜就可以发现只有几千，完全可以接受。  
最后跑一个简单的自动机 dp 就行了。
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define ok debug("OK\n")
using namespace std;

const int N=1e4+100;
const int mod=1e9+7;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)) {if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

inline ll ksm(ll x,ll k){
  ll res(1);
  while(k){
    if(k&1) res=res*x%mod;
    x=x*x%mod;
    k>>=1;
  }
  return res;
}
int n,k;

int key=10;
inline ull Hash(int *x,int num){
  ull res(0);
  for(int i=num;i>=1;i--) res=res*key+x[i];
  return res;
}
inline int dcode(int *x,ull h){
  int cnt=0;
  while(h){
    x[++cnt]=h%key;
    h/=key;
  }
  return cnt;
}
map<ull,int>mp;
int trans[N][10];
ull transh[N][10];
int tot;
int s[20],t[20];
bool vis[N];
void dfs(int x,ull h){
  if(vis[x]) return;
  vis[x]=1;
  int num=dcode(s,h);
  for(int i=1;i<=9;i++){
    s[num+1]=i;
    int pl=num+1,now=0;
    bool flag=1;
    while(pl>=1){
      now+=s[pl];
      if(now==k){
	flag=0;break;
      }
      if(k%now==0||now>k) break;
      pl--;
    }
    
    int cnt=0;
    for(int j=pl+1;j<=num+1;j++) t[++cnt]=s[j];
    
    if(!flag){
      trans[x][i]=0;continue;
    }

    ull nh=Hash(t,cnt);
    if(!mp.count(nh)) mp[nh]=++tot;
    trans[x][i]=mp[nh];
    transh[x][i]=nh;
  }
  for(int i=1;i<=9;i++){
    if(trans[x][i]) dfs(trans[x][i],transh[x][i]);
  }
  return;
}
void init(){
  mp[0]=++tot;
  dfs(1,0);
}

int dp[1050][N];
char a[N];
signed main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  #endif
  memset(dp,0x3f,sizeof(dp));
  scanf(" %s",a+1);
  n=strlen(a+1);
  k=read();
  init();
  debug("tot=%d\n",tot);
  dp[0][1]=0;
  for(int i=0;i<n;i++){
    int c=a[i+1]-'0';
    for(int j=1;j<=tot;j++){      
      if(trans[j][c]){
	dp[i+1][trans[j][c]]=min(dp[i+1][trans[j][c]],dp[i][j]);
      }
      dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
    }
  }
  int ans=1e9;
  for(int i=1;i<=tot;i++) ans=min(ans,dp[n][i]);
  printf("%d\n",ans);
  return 0;
}

```


---

## 作者：happybob (赞：0)

注意到本质就是给定若干字符串，要求删若干字符使得这个串中不出现给定串，对给定串建 ACAM 然后 DP 即可解决问题。

进一步注意到合法字符串数量很小，当 $x=19$ 时数量取到最大值为 $2399$，所以直接做就是对的。

---

## 作者：Purslane (赞：0)

# Solution

难点在于知道这道题是字符串题。

不妨设 $x > 1$，考虑所有的 $\rm x-prime$ 串，**其中一定不会有字符 $1$**。打表发现，这样的串的长度总和小于 $2 \times 10^5$。

因此建立 $\rm AC$ 自动机在上面 $\rm DP$ 即可，复杂度 $O(n \sum |S|)$，足以通过本题。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,dp[2][MAXN],fail[MAXN],flg[MAXN],tr[MAXN][11],x,tot=1;
string S;
void insert(string S) {
	int u=1;
	for(auto ch:S) {
		if(!tr[u][ch-'0']) tr[u][ch-'0']=++tot;
		u=tr[u][ch-'0'];	
	}
	return flg[u]=1,void();
}
void build(void) {
	queue<int> q;
	ffor(i,1,9) if(tr[1][i]) q.push(tr[1][i]),fail[tr[1][i]]=1;
	else tr[1][i]=1;
	while(!q.empty()) {
		int u=q.front();
		q.pop();
		ffor(i,1,9) if(tr[u][i]) fail[tr[u][i]]=tr[fail[u]][i],q.push(tr[u][i]);
		else tr[u][i]=tr[fail[u]][i];	
	}
	return ;
}
int check(string S) {
	ffor(i,0,S.size()-1) {
		int sum=0;
		ffor(j,i,S.size()-1) {
			sum+=S[j]-'0';
			if(sum!=x&&x%sum==0) return 0;
		}
	}
	return 1;
}
void dfs(string S,int tot) {
	if(tot==x) if(check(S)) insert(S);	
	if(tot>=x) return ;
	ffor(i,2,9) dfs(S+(char)(i+'0'),tot+i);
	return ; 
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>S>>x,n=S.size(),S="&"+S;
	if(x==1) insert("1");
	dfs("",0),build();
	memset(dp,-0x3f,sizeof(dp));
	dp[0][1]=0;
	ffor(i,1,n) {
		ffor(j,1,tot) dp[i&1][j]=dp[(i&1)^1][j];
		ffor(j,1,tot) if(!flg[j]) ffor(t,S[i]-'0',S[i]-'0') if(!flg[tr[j][t]]) {
			int to=tr[j][t];
			dp[i&1][to]=max(dp[i&1][to],dp[(i&1)^1][j]+1);
		}
	}
	int mx=0;
	ffor(j,1,tot) mx=max(mx,dp[n&1][j]);
	cout<<n-mx;
	return 0;
}
```

---

## 作者：roger_yrj (赞：0)

## Solution

由于这题的 $x$ 很小，我们通过观察发现 $x-prime$ 区间也很少，我们可以把所有的 $x-prime$ 区间通过暴力枚举求出来。

回到问题：删去最少的字符，使得 $s$ 不与任何一个 $x-prime$ 区间匹配。这让我们想到了 AC 自动机。

定义 $f_{i,j}$ 为当前处理到 $s$ 的前 $i$ 个字符，在 AC 自动机的位置为 $j$ 的答案。

转移的话注意不要转移到 $x-prime$ 区间结尾处就行了，具体细节看代码。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1010;
int n,a[N],m,ch[N*20][20],tot,f[N][N*20],vis[N*20],fail[N*20];
char s[N];
int p[30];
void insert(int x){
	int u=0;
	for(int i=1;i<=x;i++){
		if(ch[u][p[i]])u=ch[u][p[i]];
		else u=ch[u][p[i]]=++tot;
	}
	vis[u]=1;
}
void get_fail(){
	queue<int>q;
	for(int i=1;i<=9;i++)if(ch[0][i])q.push(ch[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=1;i<=9;i++){
			if(ch[u][i])fail[ch[u][i]]=ch[fail[u]][i],q.push(ch[u][i]);
			else ch[u][i]=ch[fail[u]][i];
		}
	}
}
void dfs(int x,int y){
	if(y>m)return;
	if(y==m){
		for(int l=1;l<x;l++){
			int tmp=0;
			for(int r=l;r<x;r++){
				tmp+=p[r];
				if(m%tmp==0&&m!=tmp)return;
			}
		}
		insert(x-1);
		return;
	}
	for(int i=1;i<=9;i++)p[x]=i,dfs(x+1,y+i);
}
int main(){
	cin>>(s+1)>>m;n=strlen(s+1);
	for(int i=1;i<=n;i++)a[i]=s[i]-'0';
	dfs(1,0);
	get_fail();
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<=tot;j++){
			f[i+1][j]=min(f[i+1][j],f[i][j]+1);
			int v=ch[j][a[i+1]];
			if(!vis[v])f[i+1][v]=min(f[i+1][v],f[i][j]);
		}
	}
	int ans=1145141919;
	for(int i=0;i<=tot;i++)ans=min(ans,f[n][i]);
	cout<<ans;
}
```

---

## 作者：TernaryTree (赞：0)

考虑如下事实：$x$-prime 的区间不会很多。当 $x\ge 2$ 时，$1$ 一定不能出现，所以长度最多是 $10$，搜一下你会发现确实很少，$n=19$ 的时候只有 $2399$ 个。

上 AC 自动机，$n=19$ 时 $2399$ 个串建出的 trie 只有 $4852$ 个结点。然后我们令 $f_{i,u}$ 表示前 $i$ 个字符，走到了结点 $u$ 删掉的最少字符，转移简单。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fs first
#define sc second
#define ls (u << 1)
#define rs (u << 1 | 1)
#define mid ((l + r) >> 1)
#define lc ls, l, mid
#define rc rs, mid + 1, r
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define per(i, r, l) for (int i = (r); i >= (l); --i)
#define gc getchar
#define pc putchar

using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;

const int maxn = 5e3 + 10;
const bool multidata = 0;

template<typename T = int>
T read() {
	T x = 0, f = 1; char c = gc();
	while (c < '0' || c > '9') { if (c == '-') f = -f; c = gc(); }
	while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = gc();
	return x * f;
}

template<typename T = int>
void write(T x) {
	if (x < 0) pc('-'), x = -x;
	if (x < 10) return void (pc(x + '0'));
	write<T>(x / 10), pc(x % 10 + '0');
}

char tmp[maxn];
int tmps[maxn];
char t[maxn], s[maxn][21];
int len[maxn];
int x, n;

void dfs(int pos, int sum) {
	if (!sum) {
		rep(l, 1, pos - 1) tmps[l] = tmps[l - 1] + tmp[l] - '0';
		bool fl = 1;
		rep(l, 1, pos - 1) rep(r, l, pos - 1) if ((x % (tmps[r] - tmps[l - 1]) == 0) && (l != 1 || r != pos - 1)) fl = 0;
		if (fl) {
			++n;
			rep(l, 1, pos - 1) s[n][l] = tmp[l];
			len[n] = pos - 1;
		}
		return; 
	}
	rep(i, 2, min(sum, 9ll)) {
		tmp[pos] = i + '0';
		dfs(pos + 1, sum - i);
	}
}

struct node {
	int ch[10] = {}, end, fail;
	node() = default;
};

node tr[maxn];
int tot, rt;

void insert(char * s, int n) {
	int u = rt;
	rep(i, 1, n) {
		if (!tr[u].ch[s[i] - '0']) tr[u].ch[s[i] - '0'] = ++tot;
		u = tr[u].ch[s[i] - '0'];
	}
	tr[u].end++;
}

void build() {
	queue<int> q;
	for (int v : tr[0].ch) if (v) q.push(v);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		rep(i, 0, 9) {
			int &v = tr[u].ch[i];
			if (v) tr[v].fail = tr[tr[u].fail].ch[i], q.push(v), tr[v].end += tr[tr[v].fail].end;
			else v = tr[tr[u].fail].ch[i];
		}
	}
}

int f[maxn][maxn];

void fake_main() {
	cin >> t + 1 >> x;
	dfs(1, x);
	if (x == 1) s[++n][1] = '1', len[n] = 1;
	rep(i, 1, n) insert(s[i], len[i]);
	build();
//	cout<<tot<<endl;
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	int m = strlen(t + 1);
	rep(i, 1, m) {
		rep(u, 0, tot) {
			if (!tr[tr[u].ch[t[i] - '0']].end) f[i][tr[u].ch[t[i] - '0']] = min(f[i][tr[u].ch[t[i] - '0']], f[i - 1][u]);
			f[i][u] = min(f[i][u], f[i - 1][u] + 1);
		}
	}
	int ans = f[0][tot + 1];
	rep(u, 0, tot) ans = min(ans, f[m][u]);
	write(ans);
}

signed main() {
	int T = multidata ? read() : 1;
	while (T--) fake_main();
	return 0;
}

```

---

## 作者：gyyyyx (赞：0)

[题面](https://www.luogu.com.cn/problem/CF1400F)

这是一个正常的解法。

首先可以看出，由于 $x-prime$ 特殊限制和 $x$ 的范围不大，$x-prime$ 字符串的数量其实不多。

稍微枚举一下发现 $19-prime$ 数量最多，但也仅仅为 $2399$ 个。

那问题转化为：给定文本串字符串和至多 $2399$ 个模式串，删去文本串中一些字符使之与任意模式串都无法匹配。

考虑 DP。

设 $dp_{i,j}$ 表示 $s_{1\sim i}$ 中最少需要删除多少个字符使其后缀为 $j$（这里的 $j$ 可以先理解为一段字符串）。

则有 $dp_{i,j}=\min(dp_{i-1,j}+1,dp_{i-1,k})$。

其中 $k+s_i=j$ 且 $j$ 不与任何模式串匹配。

但由于后缀状态数量很多，直接跑肯定跑不动。

考虑只处理有效的后缀状态。

发现有效的后缀状态一定是模式串的前缀，因为只有这样才可能匹配出模式串。

而不是模式串前缀的后缀状态由于都不可能在继续添加字符后匹配到任何模式串，也就是和无后缀本质相同，因此可以统一存在 $dp_{i,0}$ 中。

现在只需要知道如何求得所有模式串前缀了。

容易想到 trie 树。

将所有模式串建成一棵 trie 树，那么每一个节点都相当于一个不重复的前缀，也就是一个后缀状态。

建完树发现最多只有 $4852$ 个节点。

那么转移方程就变为：$dp_{i,son_{j,t_i}}=\min(dp_{i-1,son_{j,t_i}}+1,dp_{i-1,j})$。

同样的是 $j$ 不与任何模式串匹配，这在 trie 树上很好判断。

但由于我们没有规定后缀的长度，因此有些节点不一定只能由父亲节点转移过来。

比如 $dp_{\ 2,\{234\}}$ 可以由 $dp_{\ 1,\{23\}}$ 转移过来，也可以由 $dp_{\ 1,\{123\}}$ 转移过来。

显然 $\{123\}$ 不可能为 $\{234\}$ 的父亲节点。

而处理这种失配问题完全可以用 ac 自动机。

因此最终就是在 ac 自动机上跑 DP，转移方程按上面给的写就行了。

代码：

```cpp
#include<bits/stdc++.h>
#define N 1005
#define M 5000
using namespace std;
char t[N];int x,np,vis;
int cnt,son[M][10];bool flg[M];
inline void Insert(string s){
	int u(0);
	for(int i(0);i<s.size();++i){
		int c(s[i]-'0');
		if(!son[u][c]) son[u][c]=++cnt;
		u=son[u][c];
	}
	flg[u]=1;
}
void DFS(string s,int sum){
	if(sum==x){
		Insert(s);
		return;
	}
	for(int i(1);i<=9&&sum+i<=x;++i){
		int tmp(vis);
		vis=vis<<i|(1<<i-1);
		if((vis&np)==0)
			DFS(s+char(i+'0'),sum+i);
		vis=tmp;
	}
}
int fail[M];
inline void Build(){
	queue <int> q;
	fail[0]=0;
	for(int i(1);i<=9;++i)
		if(son[0][i]){
			fail[son[0][i]]=0;
			q.push(son[0][i]);
		}
	while(!q.empty()){
		int u(q.front());q.pop();
		for(int i(1);i<=9;++i){
			if(son[u][i]){
				fail[son[u][i]]=son[fail[u]][i];
				q.push(son[u][i]);
			}
			else son[u][i]=son[fail[u]][i];
		}
	}
}
int dp[N][M],ans(0x3f3f3f3f);
int main(){
	scanf(" %s%d",t+1,&x);
	for(int i(x-1);i>=1;--i)
		np=np<<1|(!(x%i));
	DFS("",0);
	Build();
	memset(dp[0],0x3f3f3f3f,sizeof(dp[0]));dp[0][0]=0;
	int len(strlen(t+1));
	for(int i(1);i<=len;++i){
		for(int j(0);j<=cnt;++j) dp[i][j]=dp[i-1][j]+1;
		for(int j(0);j<=cnt;++j){
			int v(son[j][t[i]-'0']);
			if(!flg[v]) dp[i][v]=min(dp[i][v],dp[i-1][j]);
		}
	}
	for(int i(0);i<=cnt;++i) ans=min(ans,dp[len][i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：yzyjh (赞：0)

蒟蒻又来写题解了awa


### 思路

我们发现$s$非常小，所以不合法的串是非常少的，所以我们就可以暴力找出所有不合法的串，然后就可以$DP$$+$ $枚举$$+$$ac自动机$

放上代码：


```cpp
#include <algorithm>

#include <array>

#include <cassert>

#include <iostream>

#include <vector>

using namespace std;



template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }

template<typename T, size_t size> ostream& operator<<(ostream &os, const array<T, size> &arr) { os << '{'; string sep; for (const auto &x : arr) os << sep << x, sep = ", "; return os << '}'; }

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }



void dbg_out() { cerr << endl; }

template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }



#ifdef NEAL_DEBUG

#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

#else

#define dbg(...)

#endif



// This version of aho_corasick uses more memory and depends on a small alphabet, but it provides O(1) suffix links.

template<char MIN_CHAR = 'a', int ALPHABET = 26>

struct aho_corasick {

    struct node {

        // suff = the index of the node of the longest strict suffix of the current node that's also in the tree.

        //   Also see "blue arcs" on Wikipedia: https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm

        // dict = the index of the node of the longest strict suffix of the current node that's in the word list.

        //   Also see "green arcs" on Wikipedia.

        // depth = normal trie depth (root is 0). Can be removed to save memory.

        // word_index = the index of the *first* word ending at this node. -1 if none.

        // word_count = the total number of words ending at this node. Used in count_total_matches().

        // link = the trie connections and/or suffix connections from this node.

        int suff = -1, dict = -1, depth = 0;

        int word_index = -1, word_count = 0;

        int link[ALPHABET];



        node() {

            fill(link, link + ALPHABET, -1);

        }



        int& operator[](char c) {

            return link[c - MIN_CHAR];

        }

    };



    vector<node> nodes;

    int W;

    vector<int> word_location;

    vector<int> word_indices_by_depth;

    vector<int> defer;



    aho_corasick(const vector<string> &words = {}) {

        if (!words.empty())

            build(words);

    }



    // Builds the adj list based on suffix parents. Often we want to perform DP and/or queries on this tree.

    vector<vector<int>> build_suffix_adj() const {

        vector<vector<int>> adj(nodes.size());



        for (int i = 1; i < int(nodes.size()); i++)

            adj[nodes[i].suff].push_back(i);



        return adj;

    }



    int get_or_add_child(int current, char c) {

        if (nodes[current][c] >= 0)

            return nodes[current][c];



        int index = int(nodes.size());

        nodes[current][c] = index;

        nodes.emplace_back();

        nodes.back().depth = nodes[current].depth + 1;

        return index;

    }



    int add_word(const string &word, int word_index) {

        assert(!nodes.empty());

        int current = 0;



        for (char c : word)

            current = get_or_add_child(current, c);



        if (nodes[current].word_index < 0)

            nodes[current].word_index = word_index;



        nodes[current].word_count++;

        return current;

    }



    // Returns where in the trie we should end up after starting at `location` and adding char `c`. Runs in O(1).

    int get_suffix_link(int location, char c) const {

        if (location >= 0)

            location = nodes[location].link[c - MIN_CHAR];



        return max(location, 0);

    }



    void build(const vector<string> &words) {

        nodes = {node()};

        W = int(words.size());

        word_location.resize(W);

        defer.resize(W);

        int max_depth = 0;



        for (int i = 0; i < W; i++) {

            word_location[i] = add_word(words[i], i);

            max_depth = max(max_depth, int(words[i].size()));

            defer[i] = nodes[word_location[i]].word_index;

        }



        // Create a list of word indices in decreasing order of depth, in linear time via counting sort.

        word_indices_by_depth.resize(W);

        vector<int> depth_freq(max_depth + 1, 0);



        for (int i = 0; i < W; i++)

            depth_freq[words[i].size()]++;



        for (int i = max_depth - 1; i >= 0; i--)

            depth_freq[i] += depth_freq[i + 1];



        for (int i = 0; i < W; i++)

            word_indices_by_depth[--depth_freq[words[i].size()]] = i;



        // Solve suffix parents by traversing in order of depth (BFS order).

        vector<int> q = {0};



        for (int i = 0; i < int(q.size()); i++) {

            int current = q[i];



            for (char c = MIN_CHAR; c < MIN_CHAR + ALPHABET; c++) {

                int &index = nodes[current][c];



                if (index >= 0) {

                    // Find index's suffix parent by traversing suffix parents of current until one of them has a child c.

                    int suffix_parent = get_suffix_link(nodes[current].suff, c);

                    nodes[index].suff = suffix_parent;

                    nodes[index].word_count += nodes[suffix_parent].word_count;

                    nodes[index].dict = nodes[suffix_parent].word_index < 0 ? nodes[suffix_parent].dict : suffix_parent;

                    q.push_back(index);

                } else {

                    index = get_suffix_link(nodes[current].suff, c);

                }

            }

        }

    }



    // Counts the number of matches of each word in O(text length + num words).

    vector<int> count_matches(const string &text) const {

        vector<int> matches(W, 0);

        int current = 0;



        for (char c : text) {

            current = get_suffix_link(current, c);

            int dict_node = nodes[current].word_index < 0 ? nodes[current].dict : current;



            if (dict_node >= 0)

                matches[nodes[dict_node].word_index]++;

        }



        // Iterate in decreasing order of depth.

        for (int word_index : word_indices_by_depth) {

            int location = word_location[word_index];

            int dict_node = nodes[location].dict;



            if (dict_node >= 0)

                matches[nodes[dict_node].word_index] += matches[word_index];

        }



        for (int i = 0; i < W; i++)

            matches[i] = matches[defer[i]];



        return matches;

    }



    // Counts the number of matches over all words at each ending position in `text` in O(text length).

    vector<int> count_matches_by_position(const string &text) const {

        vector<int> matches(text.size());

        int current = 0;



        for (int i = 0; i < int(text.size()); i++) {

            current = get_suffix_link(current, text[i]);

            matches[i] = nodes[current].word_count;

        }



        return matches;

    }



    // Counts the total number of matches of all words within `text` in O(text length).

    int64_t count_total_matches(const string &text) const {

        int64_t matches = 0;

        int current = 0;



        for (char c : text) {

            current = get_suffix_link(current, c);

            matches += nodes[current].word_count;

        }



        return matches;

    }

};





const int INF = 1e9 + 5;



int N, X;

string S;

vector<string> prime;

aho_corasick<'1', 9> AC;



bool check(string str) {

    int n = int(str.size());



    for (int i = 0; i < n; i++) {

        int sum = 0;



        for (int j = i; j < n; j++) {

            sum += str[j] - '0';



            if (sum < X && X % sum == 0)

                return false;

        }

    }



    return true;

}



void generate(string str, int sum) {

    if (sum > X)

        return;



    if (sum == X) {

        if (check(str))

            prime.push_back(str);



        return;

    }



    for (int d = 1; d <= 9 && sum + d <= X; d++)

        generate(str + char(d + '0'), sum + d);

}



int main() {

    ios::sync_with_stdio(false);

#ifndef NEAL_DEBUG

    cin.tie(nullptr);

#endif



    cin >> S >> X;

    N = int(S.size());

    generate("", 0);

    dbg(prime);

    AC.build(prime);

    int ST = int(AC.nodes.size());

    vector<int> dp(ST, INF);

    dp[0] = 0;



    for (auto &ch : S) {

        vector<int> next_dp(ST, INF);



        for (int state = 0; state < ST; state++)

            if (dp[state] < INF) {

                next_dp[state] = min(next_dp[state], dp[state] + 1);

                int transition = AC.get_suffix_link(state, ch);



                if (AC.nodes[transition].word_index < 0)

                    next_dp[transition] = min(next_dp[transition], dp[state]);

            }



        swap(dp, next_dp);

    }



    cout << *min_element(dp.begin(), dp.end()) << '\n';

}


```


---

