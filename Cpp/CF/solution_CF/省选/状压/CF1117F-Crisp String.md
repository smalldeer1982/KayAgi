# Crisp String

## 题目描述

给定一个长度为 $n$ 的字符串。字符串中的每个字符都是前 $p$ 个小写拉丁字母之一。

同时给定一个大小为 $p \times p$ 的二进制矩阵 $A$。该矩阵是对称的（即 $A_{ij} = A_{ji}$）。$A_{ij} = 1$ 表示字符串中第 $i$ 个和第 $j$ 个拉丁字母可以相邻。

如果字符串中所有相邻字符都可以相邻（即在矩阵 $A$ 的对应位置为 $1$），则称该字符串为“清脆的”。

你可以进行如下操作：任选一个字母，将其在字符串中的所有出现全部删除，并将剩余部分按原顺序拼接。例如，从 "abacaba" 中删除字母 'a'，会得到 "bcb"。

给定的字符串是清脆的。你每次操作后得到的新字符串也必须保持清脆。

你可以进行任意次数的操作（也可以不操作）。你能得到的最短字符串长度是多少？

## 说明/提示

在第一个样例中，不能删除任何字母。

在第二个样例中，可以依次删除字母 'b'、'c'、'a'。中间过程的字符串分别为："abacaba" $\rightarrow$ "aacaa" $\rightarrow$ "aaaa" $\rightarrow$ ""。

在第三个样例中，只能删除字母 'b'。

在第四个样例中，可以依次删除字母 'c'、'b'，但不能先删 'b' 再删 'c'，因为两个 'c' 不能相邻。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7 3
abacaba
0 1 1
1 0 0
1 0 0
```

### 输出

```
7
```

## 样例 #2

### 输入

```
7 3
abacaba
1 1 1
1 0 0
1 0 0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
7 4
bacadab
0 1 1 1
1 0 0 0
1 0 0 0
1 0 0 0
```

### 输出

```
5
```

## 样例 #4

### 输入

```
3 3
cbc
0 0 0
0 0 1
0 1 0
```

### 输出

```
0
```

# 题解

## 作者：是个汉子 (赞：4)

没有用DP，搞了个搜索

### Solution

​		如果要枚举合法对的话，~~用脑子想想~~是很困难的，所以我们**正难则反**——枚举非法对。

​		思考一下如果 $a$ 和 $b$ 对应的数为 $0$ 即不能相邻的话，将 $a,b$ 中间的字符消完就是非法操作。举个例子： $acadbc$ ，那么删除 $d$ 就是非法的，而删除 $d$ 非法了，删除 $d(b)c$ 也是非法的。当然，不能确定 $ad$ 是非法操作，因为枚举的时候，非法对的字符不能删。

​		因为 $p\leq 17$ ，所以可以用状压来存储状态。所以存所有非法对的状态，从最开始的状态往外搜索即可。

### 代码

```c++
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>


using namespace std;
const int INF=0x3f3f3f3f,N=1e6+10;
int n,p,P,ans=INF,a[N],tmp[1<<17],f[1<<17],ln[1<<17],g[17][17];
char s[N];

void dfs0(int x){
    if(tmp[x]) return ;
    tmp[x]=1;
    for(int y=x;y;y^=y&-y) dfs0(x^y&-y);
}

void dfs1(int x){
    if(f[x]||tmp[x]) return ;
    tmp[x]=1;
    ans=min(ans,ln[x]);
    for(int y=x;y;y^=y&-y) dfs1(x^y&-y);
}

int main(){
    scanf("%d%d%s",&n,&p,s+1);P=(1<<p)-1;
    for(int i=1;i<=n;i++) ++ln[1<<(a[i]=s[i]-'a')];
    for(int i=1;i<=P;i++) ln[i]=ln[i^i&-i]+ln[i&-i];
    for(int i=0;i<p;i++)
        for(int j=0;j<p;j++) scanf("%d",&g[i][j]);
    for(int i=0;i<p;i++)
        for(int j=0;j<p;j++)
            if(!g[i][j]){
                int now=0,pre=-1;
                for(int k=1;k<=n;k++){
                    if(a[k]==i||a[k]==j){
                        if(a[k]==i&&pre==j||a[k]==j&&pre==i) dfs0(P^now);
                        now=0,pre=a[k];
                    }
                    else now|=1<<a[k];
                }
                int t=1<<i|1<<j;
                for(int k=0;k<=P;k++){
                    if((k&t)==t) f[k]|=tmp[k];
                    tmp[k]=0;
                }
            }
    dfs1(P);
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：_edge_ (赞：2)

这下这下了，拿到了最劣解。

我们先思考后半部分，我们发现 $p$ 特别小，可以直接设 $f_{S}$ 表示 $S$ 这个集合里面的字母都没删掉了之后是否合法，考虑转移就是枚举另一个字母删掉，考虑其是否合法还需要去原字符串 check，如何 check 成为问题的瓶颈。

一个简单的想法就是去枚举非法的字母对，比方说 $a$ 和 $b$ 是不能相邻的，那么中间一堆东西删掉的话他们两个其中之一也必须被删掉，或者是中间一堆东西没有被删掉。

于是我们考虑枚举非法对，首先，一个点往前匹配非法对最多有 $p$ 对，由于再前面的肯定是没有用的，比方说 `x...x...a`，对于 $a$ 而言，如果 $x$ 不能和 $a$ 相邻，那么最前面那个 $x$ 肯定没用。

然后我们就得到了 $n \times p$ 对非法对，中间的字符集是很好计算的，可以利用前缀和来判断！于是问题转化为现在我们知道一个集合 $S$，然后判断是否存在一种情况使得某个非法对不合法。

可以在状压的时候直接枚举哪两个字母，这样比较方便处理，然后问题就是 $S$ 的子集有没有不合法的，这东西可以随手高维前缀和处理掉。

但是复杂度比较劣，是 $O(p^3 \times 2^p)$ 的。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF=35;
const int INFN=2e5+5;
const int INFM=19;
int n,p,Map[INF][INF],pre[INF],sum1[INFN][INF],num[INF];
bool sum2[INFM][INFM][INFN];
int f[INFN];
string s1;
signed main()
{
	memset(f,-63,sizeof f);
	ios::sync_with_stdio(false);
	cin>>n>>p>>s1; s1=" "+s1;
	for (int i=1;i<=n;i++)
		for (int j=0;j<p;j++)
			sum1[i][j]=sum1[i-1][j]+(s1[i]-'a'==j);
	for (int j=0;j<p;j++) num[j]=sum1[n][j];
	for (int i=0;i<p;i++)
		for (int j=0;j<p;j++)
			cin>>Map[i][j];
	for (int i=1;i<=n;i++) {
		for (int k=0;k<p;k++) {
			if (Map[s1[i]-'a'][k]) continue;
			if (!pre[k]) continue;
			// pre[k] -> s1[i]-'a'
			int kk=0;
			for (int l=0;l<p;l++) 
				if (sum1[i-1][l]-sum1[pre[k]][l]) kk|=(1<<l);
			
			int x=s1[i]-'a',y=k;
			if (x>y) swap(x,y);
			sum2[x][y][kk]=1;
		}
		pre[s1[i]-'a']=i;
	}
	
	for (int i=0;i<p;i++) {
		for (int j=i;j<p;j++) {
			for (int q=0;q<p;q++) {
				for (int k=0;k<(1<<p);k++) {
					if (k&(1<<q))
						sum2[i][j][k]|=sum2[i][j][k^(1<<q)];
				}
			}
		}
	}
	f[0]=0;
	int ans=n;
	for (int i=0;i<(1<<p);i++) {
		for (int j=0;j<p;j++) {
			if (i&(1<<j)) continue;
			for (int k=j;k<p;k++) {
				if (i&(1<<k)) continue;
				if (sum2[j][k][i]) f[i]=-1e9;
			}
		}
		ans=min(ans,n-f[i]);
		for (int j=0;j<p;j++) {
			if (i&(1<<j)) continue;
			f[i|(1<<j)]=max(f[i|(1<<j)],f[i]+num[j]);
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：xtx1092515503 (赞：2)

这题为什么要用FWT呀orz……

好神仙的题。

因为$p\leq 17$，考虑状压。我们设一个$f_x$表示当前的删除情况为$x$时，这个状态是否合法（即有无不合法的相邻字符）。其中$0$的位置表示没删，$1$的位置表示删了。

我们可以枚举所有不合法的**字符对**$(a,b)$（注意这里$a$和$b$都是值，不是下标）。考虑原串中字符$a$的任何一次出现，找到它右侧离它最近的一次字符$b$的出现。这样的话，如果删光这个$a$和下一个$b$之间所有的字符，那么这两个$a$和$b$就会紧贴在一起，就不合法了。当然，这两个字符间不能出现其他的$a$和$b$，不然你必须在删掉$a$或$b$后还保留着$a$和$b$！这就是为什么我们要找到**右侧离它最近**的字符$b$。并且，我们还得确保当前这个$a$的右侧离它最近的下一个$a$在这个$b$的右侧，不然这段$(a,b)$间就有了其他的$a$。

这是找$(a,b)$的代码（其中$nxt_{i,j}$意为位置$i$往后下一个字符$j$的位置，$ok$是能否相邻的数组）：

```cpp
for(int i=0;i<n;i++)for(int j=0;j<p;j++){
	if(ok[s[i]-'a'][j]||nxt[i][j]==0x3f3f3f3f||nxt[i][s[i]-'a']<nxt[i][j])continue;
	int sta=0;
	for(int k=0;k<p;k++)if(nxt[i][k]<nxt[i][j])sta|=(1<<k);
	dye(sta,s[i]-'a',j);
}
```


当我们找出一对这样的$a,b$后，我们考虑用它排除一些不合法的状态。显然，当$(a,b)$段中间的字符全为$1$，而$a$和$b$的状态全为$0$，其它字符随便时，这个状态不合法。

我们令一个函数$\operatorname{dye}(sta,a,b)$表示：中间出现的字符状态为$sta$，$a,b$同上文。这个函数采取记忆化搜索的形式实现：维护一个布尔数组$mask$。当我们调用$\operatorname{dye}(sta,a,b)$时，如果$mask[sta][a][b]$已经为$false$，即其已经被访问过，直接返回。否则，将$f[sta]$和$mask[sta][a][b]$一并赋为$false$，枚举$sta$中一个非$1$非$a$非$b$位，继续$\operatorname{dye}$下去。

即这段代码：

```cpp
void dye(int sta,int a,int b){
	if(!mask[sta][a][b])return;mask[sta][a][b]=f[sta]=false;
	for(int i=0;i<p;i++)if(!(sta&(1<<i))&&i!=a&&i!=b)dye(sta|(1<<i),a,b);
}
```
然后就可以从状态$0$（全都没删）开始状压dp，只能进入$f_x=true$的状态。则所有状态$0$能转移到的状态即为所有合法的状态。

复杂度：$O(p^22^p)$（记忆化复杂度）+$O(p^2n)$（枚举$(a,b)$复杂度）=$O(p^22^p+p^2n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,nxt[100100][18],MAXN,cnt[18],res=0x3f3f3f3f;
bool ok[18][18],f[1<<18],mask[1<<18][18][18],g[1<<18];
char s[100100];
void dye(int sta,int a,int b){
	if(!mask[sta][a][b])return;mask[sta][a][b]=f[sta]=false;
	for(int i=0;i<p;i++)if(!(sta&(1<<i))&&i!=a&&i!=b)dye(sta|(1<<i),a,b);
}
int main(){
	scanf("%d%d",&n,&p),memset(nxt,0x3f3f3f3f,sizeof(nxt)),memset(f,true,sizeof(f)),memset(mask,true,sizeof(mask)),MAXN=1<<p;
	scanf("%s",s);
	for(int i=0;i<n;i++)cnt[s[i]-'a']++;
	for(int i=n-2;i>=0;i--){
		for(int j=0;j<p;j++)nxt[i][j]=nxt[i+1][j];
		nxt[i][s[i+1]-'a']=i+1;
	}
//	for(int i=0;i<p;i++){for(int j=0;j<n;j++)printf("%d ",nxt[j][i]);puts("");}
	for(int i=0;i<p;i++)for(int j=0;j<p;j++)scanf("%d",&ok[i][j]);
	for(int i=0;i<n;i++)for(int j=0;j<p;j++){
		if(ok[s[i]-'a'][j]||nxt[i][j]==0x3f3f3f3f||nxt[i][s[i]-'a']<nxt[i][j])continue;
		int sta=0;
		for(int k=0;k<p;k++)if(nxt[i][k]<nxt[i][j])sta|=(1<<k);
//		printf("%d:%d(%d %d)\n",i,sta,s[i]-'a',j);
		dye(sta,s[i]-'a',j);
	}
	g[0]=true;
	for(int i=0;i<MAXN;i++)if(f[i]&&g[i])for(int j=0;j<p;j++)if(!(i&(1<<j))&&f[i|(1<<j)])g[i|(1<<j)]|=g[i];
	for(int i=0;i<MAXN;i++){
		if(!g[i])continue;
		int sum=n;
		for(int j=0;j<p;j++)if(i&(1<<j))sum-=cnt[j];
		res=min(res,sum);
	}
	printf("%d\n",res);
	return 0;
}
```


---

## 作者：ywy_c_asm (赞：2)

首先我们发现删去一些字符之后可能就会有若干对不能挨着的字符挨着了，但注意到$p<=17$，我们不妨$O(p^2)$考虑每一对不能挨着的字符$(a,b)$，然后对于一对相邻的$(a,b)$（这里的相邻是指中间没别的$a,b$了）我们找出它们中间都有些什么字符，设这个字符集合为$S$，那么，我们在任意时刻都不能删了$S$的字符而不删$a,b$。

考虑找出所有不能出现在任意时刻的被删除的字符集合，那么，我们相当于是把$S$的不包含$a,b$的所有超集都标记一遍，这可以$FWT$先把每个$S$的超集标记上，再挑选出不含$a,b$的重新标记，就可以了。

然后的做法就很显然了，我们相当于是要找出一个价值最大的操作序列使得任意前缀构成的集合都没被标记过，这个状压$dp$一下就好了。

复杂度$O(p^2n+p^32^p)$，但是上界并不严格所以跑的很快……

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
namespace ywy {
	int v[20][20];
	char str[200001];
	int bit[1048576], val[1048576];
	vector<int> vec[30];
	unsigned char dp[1048576], g[131073], f[1048576];
	void ywymain() {
	    int n, p;
	    cin >> n >> p;
	    cin >> str + 1;
	    for (register int i = 1; i <= n; i++) vec[str[i] - 'a'].push_back(i);
	    for (register int i = 0; i < p; i++) {
	        for (register int j = 0; j < p; j++) cin >> v[i][j];
	    }
	    for (register int i = 0; i < p; i++) {
	        for (register int j = 0; j <= i; j++) {
	            if (v[i][j])
	                continue;
	            unsigned char bswitch = 0;
	            for (register int k = 0; k < vec[i].size(); k++) {
	                int s = 0;
	                for (register int a = vec[i][k] + 1; a <= n; a++) {
	                    if (str[a] - 'a' == j) {
	                        g[s] = 1;
	                        bswitch = 1;
	                        break;
	                    }
	                    if (str[a] - 'a' == i)
	                        break;
	                    s |= (1 << (str[a] - 'a'));
	                }
	            }
	            for (register int k = 0; k < vec[j].size(); k++) {
	                int s = 0;
	                for (register int a = vec[j][k] + 1; a <= n; a++) {
	                    if (str[a] - 'a' == i) {
	                        g[s] = 1;
	                        bswitch = 1;
	                        break;
	                    }
	                    if (str[a] - 'a' == j)
	                        break;
	                    s |= (1 << (str[a] - 'a'));
	                }
	            }
	            if (!bswitch)
	                continue;
	            for (register int bit = 2; bit <= (1 << p); bit <<= 1) {
	                for (register int a = 0; a < (1 << p); a += bit) {
	                    for (register int b = a; b < a + (bit >> 1); b++) g[b + (bit >> 1)] |= g[b];
	                }
	            }
	            for (register int k = 0; k < (1 << p); k++) {
	                if (!g[k])
	                    continue;
	                g[k] = 0;
	                if ((k & (1 << i)) || (k & (1 << j)))
	                    continue;
	                f[k] = 1;
	            }
	        }
	    }
	    for (register int i = 0; i < p; i++) bit[1 << i] = vec[i].size();
	    for (register int i = 1; i < (1 << p); i++) val[i] = val[i - (i & -i)] + bit[i & -i];
	    if (f[0]) {
	        cout << n << endl;
	        return;
	    }
	    dp[0] = 1;
	    for (register int i = 0; i < (1 << p); i++) {
	        if (!dp[i])
	            continue;
	        for (register int j = 0; j < p; j++) {
	            if (i & (1 << j))
	                continue;
	            if (!f[i | (1 << j)])
	                dp[i | (1 << j)] = 1;
	        }
	    }
	    int maxn = 0;
	    for (register int i = 0; i < (1 << p); i++)
	        if (dp[i])
	            maxn = max(maxn, val[i]);
	    cout << n - maxn << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}

```

---

## 作者：ifffer_2137 (赞：1)

### 题意
给定一个字符串，钦定若干对字符不能相邻，求删除若干种字符（每一步后都合法）后的最小长度。
### 分析
$|\Sigma|\le17$ 容易想到指数级做法。

因为删除状态只有 $2^{|\Sigma|}$ 种，所以考虑求出每种状态是否合法。具体地，枚举不合法字符对，把所有位置找出来，因为我们钦定了这两种字符不删（否则就不会产生不合法），所以显然只需要考虑相邻的位置。一对相邻的位置对删除状态的影响是，不能同时删掉中间所有的字符并保留两端的字符。这个限制的状压结果是 $O(|\Sigma|)$ 求的，然后每个位置枚举次数是 $O(|\Sigma|)$，所以这部分复杂度是 $O(n|\Sigma|^2)$ 的。

求出限制的状压结果后，向超集转移不合法标记，容易想到直接赋值的 SOSDP。但是要求超集不能含有两端字符不好处理，因为只有两个，所以容斥掉再做高维前缀和，如果一个状态标记数为 $0$ 就是合法的。

然后再转移一遍求一下每一步都合法的状态，直接枚举上一步用 SOSDP 的结果 check 即可，答案把所有合法状态答案取 min 即可。时间复杂度 $O(n|\Sigma|^2+2^{|\Sigma|}|\Sigma|)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
mt19937 rnd(time(NULL));
const int maxn=1e5+5;
const int maxm=18;
int n,S,ans;
string s;
int sm[maxm][maxn];
vector<int> p[maxm];
int a[maxm][maxm];
int dp[1<<maxm],ck[1<<maxm];
vector<int> t;
int getmsk(int l,int r){
	int msk=0;
	for(int i=0;i<S;i++) if(sm[i][r]^sm[i][l-1]) msk|=(1<<i);
	return msk;
}
void add(int msk,int u,int v){dp[msk]++,dp[msk|(1<<u)]--,dp[msk|(1<<v)]--,dp[msk|(1<<u)|(1<<v)]++;}
void pushtag(int u,int v){
	t.clear();
	for(int i:p[u]) t.eb(i);
	if(u^v) for(int i:p[v]) t.eb(i);
	sort(t.begin(),t.end());
	for(int i=1;i<(int)t.size();i++) if(s[t[i-1]]-'a'+s[t[i]]-'a'==u+v) add(getmsk(t[i-1]+1,t[i]-1),u,v);
}
int calc(int msk){int res=n;for(int i=0;i<S;i++) if(msk&(1<<i)) res-=p[i].size();return res;}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read(),S=read();
	cin>>s;s=' '+s;
	for(int i=1;i<=n;i++) p[s[i]-'a'].eb(i);
	for(int i=1;i<=n;i++) for(int j=0;j<S;j++) sm[j][i]=sm[j][i-1]+(s[i]-'a'==j);
	for(int i=0;i<S;i++) for(int j=0;j<S;j++) a[i][j]=read();
	for(int i=0;i<S;i++) for(int j=i;j<S;j++) if(!a[i][j]) pushtag(i,j);
	for(int i=0;i<S;i++) for(int msk=0;msk<(1<<S);msk++) if(msk&(1<<i)) dp[msk]+=dp[msk^(1<<i)];
	ck[0]=1;for(int msk=1;msk<(1<<S);msk++) if(!dp[msk]) for(int i=0;i<S;i++) if(msk&(1<<i)&&!dp[msk^(1<<i)]) ck[msk]|=ck[msk^(1<<i)]; 
	ans=n; for(int msk=0;msk<(1<<S);msk++) if(ck[msk]) ans=min(ans,calc(msk));
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：BreakPlus (赞：1)

提供一个不用脑子的 $\mathcal{O}(p^32^p +p^2n)$ 的做法。

原题是从字符集全集开始删，每次删完都要满足条件，我们可以先判断每种状态是否满足条件，记为 $p(S)$，然后状压 DP，从全集走到该集合，每一步都要满足 $p(S)=1$。

考虑求 $p$。

充分利用字符集很小的性质，我们考虑虽然串很长，但是不符合条件的字符对数并不多。考虑枚举一对字符 $(c_1,c_2)$，在整个串中找到它们所处的位置。两个 $c_1,c_2$ 夹着中间的字符不能删光，那么不选的字符集若包含这个中间的字符集就不行。预处理出哪些不选的字符集是可行的。具体地，$f(c_1,c_2,S)$ 表示若 $c_1$，$c_2$ 选了，是否可以不选 $S$。这玩意明显可以 $\mathcal{O}(p^32^p)$ 做完。

求 $p(S)$ 时，枚举 $S$ 内两个字符，check 即可。

注意令 $c_1<c_2$，$f$ 的存储用 bitset 以减小常数。

```cpp
ll w[20][20], n, p;
char str[100005];
vector<ll>vec[20],t;
ll tmp[100005], col[100005], cnt, q[100005], fla[131072], dp[131072], len[131072];
bitset<131072>f[20][20];
void solve(){
	n=read(), p=read();
	scanf("%s",(str+1));
	for(ll i=1;i<=n;i++) vec[str[i]-'a'].emplace_back(i);
	for(ll i=0;i<p;i++)
		for(ll j=0;j<p;j++) w[i][j]=read();
	for(ll i=0;i<p;i++){
		for(ll j=i+1;j<p;j++){
			memset(q,0,sizeof(q));
			if(w[i][j]) continue;
			for(auto k: vec[i]) q[k] = 1;
			for(auto k: vec[j]) q[k] = 2;
			ll lst = -1, lcol = 0;
			for(ll k=1;k<=n;k++){
				if(!q[k]) continue;
				if(lst != -1){
					if(lcol != q[k]) {
						ll sta = 0;
						for(ll l=lst+1;l<=k-1;l++)
							sta |= (1<<(str[l]-'a'));
						f[i][j][sta] = 1;
					}
				}
				lst = k, lcol = q[k];
			}
			for(ll k=0;k<p;k++){
				for(ll l=0;l<(1<<p);l++){
					if((l>>k)&1) f[i][j][l] = f[i][j][l] | f[i][j][l^(1ll<<k)];
				}
			}
		}
		if(!w[i][i]){
			memset(q,0,sizeof(q));
			for(auto k: vec[i]) q[k] = 1;
			ll lst = -1;
			for(ll k=1;k<=n;k++){
				if(!q[k]) continue;
				if(lst != -1){
					ll sta = 0;
					for(ll l=lst+1;l<=k-1;l++)
						sta |= (1ll<<(str[l]-'a'));
					f[i][i][sta] = 1;
				}
				lst = k;
			}
			for(ll k=0;k<p;k++){
				for(ll l=0;l<(1<<p);l++){
					if((l>>k)&1) f[i][i][l] = f[i][i][l] | f[i][i][l^(1ll<<k)];
				}
			}
		}
	}
	ll Ans = n; ll to[55], tl=0;
	for(ll i=0;i<(1ll<<p);i++){
		tl=0;
		for(ll j=0;j<p;j++){
			if((i>>j)&1) to[++tl]=j, len[i]+=vec[j].size();
		}
		bool flag = 1;
		for(ll j=1;j<=tl;j++){
			for(ll k=j;k<=tl;k++){
				if(!w[to[j]][to[k]] && f[to[j]][to[k]][(1ll<<p)-1-i]){
					flag=0;
					break;
				} 
			}
		}
		fla[i] = flag;
	}
	dp[(1ll<<p)-1] = 1;
	for(ll i=(1ll<<p)-1;i>=0;i--){
		if(!dp[i]) continue;
		for(ll j=0;j<p;j++){
			if((i>>j)&1)
				if(fla[i^(1ll<<j)]) dp[i^(1ll<<j)] = 1; 
		}
		if(dp[i]) Ans = minn(Ans, len[i]);
	}
	printf("%d\n", Ans);
}
```

---

## 作者：45dino (赞：1)

提供一种崭新的想法。

显然，当留下的字母类型是固定时，字符串也是固定的。

所以用 $f(mask)$ 表示已经去除了一些字母后，剩下的长度。

每次枚举下一个去除哪一个字母，再进行暴力判断即可。

在状态中可以再加一维 $s$，表示当前的字符串。

这样的理论复杂度为 $\Theta(2^k\times n)$，但实际远远低于此，只用了 46ms

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=0;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
    return (flag?x:~(x-1));
}
int ans,k,a[18][18];
string s;
void solve(int x,string ss)
{
	for(int i=1;i<=k;i++)
		if(!(x&(1<<(i-1))))
		{
			int flag=1;
			string t="";
			for(int l=0;l<ss.size();l++)
				if(ss[l]-'a'!=i-1)
				{
					if(!t.empty()&&!a[t[t.size()-1]-'a'+1][ss[l]-'a'+1])
					{
						flag=0;
						break;
					}
					t+=ss[l];
				}
			if(flag)
			{
				ans=min(ans,(long long)t.size());
				solve(x+(1<<(i-1)),t);
				break;
			}
		}
}
signed main()
{
	ans=read();
	k=read();
	cin>>s;
	for(int i=1;i<=k;i++)
		for(int l=1;l<=k;l++)
			a[i][l]=read();
	solve(0,s);
	cout<<ans; 
	return 0;
}

```


---

## 作者：daniEl_lElE (赞：0)

考虑二元字母组 $(i,j)$ 什么时候会相邻。

对于每个 $s_i$，求出下一个 $j$ 出现的位置 $pos$，删除 $i+1,i+2,\dots,pos-1$ 的字母后 $(s_i,j)$ 会相邻。

对于每组 $G_{s_i,j}=0$，不难发现删除 $i+1,i+2,\dots,pos-1$ 的字母后不合法。也就是说，删除子集包含 $s_{i+1},s_{i+2},\dots,s_{pos-1}$ 且不包含 $s_i,j$ 时不合法。同时一个子集不合法也一定满足某个 $i,j$ 的以上条件。

也就是说，我们需要对于所有包含 $s_{i+1},s_{i+2},\dots,s_{pos-1}$ 且不包含 $s_i,j$ 的子集打上标签表示不能经过。不难发现不包含的只有两个，可以通过高维差分+容斥+高维前缀和计算出哪些子集不能出现。

然后只需要做一遍状压 dp 求出每个没被打标签的子集是否可以从 $\{\emptyset\}$ 到达即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int f[200005],g[200005],h[200005],G[17][17],siz[200005],cnt[17];
vector<pair<int,int>> ban[17];
deque<int> q;
signed main(){
	int n,p; cin>>n>>p;
	string s; cin>>s;
	for(int i=0;i<p;i++) for(int j=0;j<p;j++) cin>>G[i][j];
	for(int i=n-1;i>=0;i--){
		cnt[s[i]-'a']++;
		int now=0;
		deque<int> sc;
		while(!q.empty()){
			int p=q.front();
			q.pop_front();
			now|=(1<<p);
			if(!q.empty()){
				if(!G[s[i]-'a'][q.front()]){
					g[now]--;
					g[now|(1<<(s[i]-'a'))]++;
					g[now|(1<<q.front())]++;
					g[now|(1<<(s[i]-'a'))|(1<<q.front())]--;
				}
			}
			if(p!=s[i]-'a') sc.push_back(p);
		}
		sc.push_front(s[i]-'a');
		swap(sc,q);
	}
	for(int k=0;k<p;k++){
		for(int j=0;j<(1<<p);j++){
			if((j>>k)&1){
				g[j]+=g[j^(1<<k)];
			}
		}
	}
	for(int j=0;j<(1<<p);j++) f[j]=(g[j]>=0);
	for(int j=0;j<(1<<p);j++) for(int k=0;k<p;k++) siz[j]+=cnt[k]*((j>>k)&1);
	int maxv=0;
	for(int j=1;j<(1<<p);j++){
		int ok=0;
		for(int k=0;k<p;k++){
			if((j>>k)&1){
				ok|=f[j^(1<<k)];
			}
		}
		f[j]&=ok;
		maxv=max(maxv,f[j]*siz[j]);
		if(f[j]){
// 			cout<<j<<" "<<siz[j]<<"\n";
		}
	}
	cout<<n-maxv;
	return 0;
}
```

---

