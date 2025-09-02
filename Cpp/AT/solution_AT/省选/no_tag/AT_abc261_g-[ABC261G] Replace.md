# [ABC261G] Replace

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc261/tasks/abc261_g

英小文字のみからなる $ 2 $ つの文字列 $ S,T $ が与えられます。

高橋君は文字列 $ S $ から始めて、 次の $ K $ 種類の操作のうち $ 1 $ つを選んで行う事を 好きなだけ繰り返す事ができます。  
 $ i $ 番目の操作は次の形で与えられます。

> コストを $ 1 $ 支払う。 その後、文字列中に**文字** $ C_i $ が含まれるとき、そのうちの $ 1 $ つを選び、**文字列** $ A_i $ に置き換える。 含まれないならば何も行わない。

文字列を $ T $ と一致させるために必要な最小コストを求めてください。 ただし、$ T $ と一致させることが不可能な場合は $ -1 $ を出力してください。

## 说明/提示

### 制約

- $ 1\leq\ |S|\leq\ |T|\leq\ 50 $
- $ 1\leq\ K\leq\ 50 $
- $ C_i $ は `a`, `b`,$ \ldots $, `z` のいずれか
- $ 1\leq\ |A_i|\leq\ 50 $
- $ S,T,A_i $ は英小文字のみからなる文字列
- $ C_i $ を長さ $ 1 $ の文字列としてみた時、$ C_i\neq\ A_i $
- $ (C_i,A_i) $ はすべて異なる。

### Sample Explanation 1

高橋君は $ S= $`ab` から始めて、次のように $ 4 $ 回操作を行う事で、 $ T= $`cbca` を作ることができます。 - `ab` の $ 1 $ 文字目 `a` を選んで `b` に置き換える ( $ 1 $ 番目の操作) 。文字列は `bb` となる。 - `bb` の $ 2 $ 文字目 `b` を選んで `ca` に置き換える ( $ 2 $ 番目の操作) 。文字列は `bca` となる。 - `bca` の $ 1 $ 文字目 `b` を選んで `ca` に置き換える ( $ 2 $ 番目の操作) 。文字列は `caca` となる。 - `caca` の $ 2 $ 文字目 `a` を選んで `b` に置き換える ( $ 1 $ 番目の操作) 。文字列は `cbca` となる。 各操作においてコストが $ 1 $ かかるため、必要なコストは $ 4 $ となり、このときが最小です。

### Sample Explanation 2

`a`$ \to $`aaa`$ \to $`aaaaa` とした時、必要なコストは $ 2 $ となり、 このときが最小です。

### Sample Explanation 3

どのように操作を行っても、$ S= $`a` から $ T= $`z` を作る事は出来ません。

## 样例 #1

### 输入

```
ab
cbca
3
a b
b ca
a efg```

### 输出

```
4```

## 样例 #2

### 输入

```
a
aaaaa
2
a aa
a aaa```

### 输出

```
2```

## 样例 #3

### 输入

```
a
z
1
a abc```

### 输出

```
-1```

# 题解

## 作者：beauty_son_whm (赞：5)

好难的区间DP。

首先发现一个性质，由于所有的 $C_i$ 长度都是1，所以在最后的答案里，我们的终串 $T$ 的每一段都会代表 $S$ 的单个字符。

对于这种两串匹配的问题我们有一个经典的 $dp$ 模型：

$dp_{i,j}$ 表示 $S$ 的前 $i$ 位和 $T$ 的前 $j$ 位完全相同了，我们需要的最小代价。那么转移就是：

$dp_{i,j}=\min(dp_{i-1,k}+f_{k+1,j,S_i})$

其中 $f_{l,r,c}$ 表示 $T$ 串的 $[l,r]$ 被我还原为单个字符 $c$ 的最小代价。

让我们想想 $f_{l,r,c}$ 怎么转移。首先有如果 $|A_i|=1$。那么 $f_{l,r,c}=\min(f_{l,r,c},f_{l,r,A_i}+1)$

更进一步的，我们可以对所有 $|A_i|=1$ 的字符串对，给 $A_i$ 到 $C_i$ 连一条有向边，我们可以用 $floyd$ 处理出来 $dis_{i,j}$ 表示字符 $i$ 只通过这种转换到字符 $j$ 的最短路。这里就不写 $floyd$ 的转移了。

所以， $f$ 数组的第一种转移就是：
$$f_{l,r,c}=\min(f_{l,r,t}+dis_{t,c})$$

考虑第二种转移，我们区间 $[l,r]$ 可能先合并成了一个字符串，然后这个字符串通过我的操作变成了一个单字符。

所以， $f$ 的第二种转移是：

$$f_{l,r,C_i}=\min(1+g_{l,r,i})$$

其中 $g_{l,r,i}$ 表示我的终串 $T[l.......r]$ 被我还原成 $A_i$ 的最小代价。

现在 $f$ 的转移已经没问题了，但是我们发现 $g$ 很难转移，所以我们给 $g$ 再加一维。$g_{l,r,i,j}$ 表示 $T[l,r]$ 被我转化为 $A_i[1,j]$ 的最小代价。那么转移式就很好写了：


$$g_{l,r,i,j}=\min(g_{l,k,i,j-1}+f_{k+1,r,A_{i,j}})$$

初始状态 $g_{l,r,i,1}=f_{l,r,a_{i,1}}$ 

乍一看没有什么问题，但是, $f$ 和 $g$ 之间的转移有环啊！！先别急，我们把所有转移写在一起观察一下。

1.$f_{l,r,c}=\min(1+g_{l,r,i,|A_i|})$

2.$f_{l,r,c}=\min(f_{l,r,t}+dis_{t,c})$

3.$g_{l,r,i,j}=\min(g_{l,k,i,j-1}+f_{k+1,r,A_{i,j}})$

4.$g_{l,r,i,1}=f_{l,r,A_{i,1}}$

首先3号转移肯定第一个做，因为它依赖的区间更小，一定被更新过了。这里我们可以钦定 $T[l,r]$ 变成单个字符的方式是：我们先由长度大于等于2的字符串转移来，然后通过 $dis$ 数组扩展到所有位置。而且我们发现通过第3种方式转移的 $g_{l,r,i,j}$ 中的 $j$ 是大于等于2的。所以我们接着做转移1,然后做转移2，最后做转移4。还有，转移2是有环的，所以得用类似 $bellmanford$ 的方式转移。

这里说不太清楚，可以自己意会一下，不懂可以私信我。

```
#include<bits/stdc++.h>
#define ll long long
#define pc putchar
#define mk make_pair
#define fi first
#define se second
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
inline void write(int x){
	if(x==0){pc('0');return ;}
	if(x<0)pc('-'),x=-x;
	char nnu[25];int top=0;
	while(x){nnu[++top]=x%10+'0';x/=10;}
	for(int i=top;i;i--) pc(nnu[i]);
	return ;
}
string S,T;
int n,m;
int k;
char C[55];
string A[55];
int g[55][55][55][55];
int f[55][55][30];
int dis[30][30];
int dp[55][55];
signed main(){
	cin>>S>>T;
	n=S.size(),m=T.size();
	S='-'+S;T='-'+T;
	k=read();
	memset(g,0x3f,sizeof(g));
	memset(f,0x3f,sizeof(f));
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=k;i++) cin>>C[i]>>A[i];
	for(int i=1;i<=k;i++){
		A[i]='-'+A[i];
		if((signed)A[i].size()==2){
			dis[A[i][1]-'a'][C[i]-'a']=1;
		}
	}
	for(int k=0;k<=25;k++) for(int i=0;i<26;i++) for(int j=0;j<26;j++) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(int i=1;i<=m;i++) f[i][i][T[i]-'a']=0;
	for(int i=1;i<=m;i++) for(int j=1;j<=k;j++) g[i][i][j][1]=f[i][i][A[i][1]-'a'];
	for(int len=1;len<=m;len++){
		for(int l=1;l+len-1<=m;l++){
			int r=l+len-1;
			for(int i=1;i<=k;i++){
				for(int j=1;j<(signed)A[i].size();j++){
					for(int k=l;k<r;k++){
						g[l][r][i][j]=min(g[l][r][i][j],g[l][k][i][j-1]+f[k+1][r][A[i][j]-'a']);
					}
				}
			}
			for(int i=1;i<=k;i++) for(int c=0;c<=25;c++) if(C[i]-'a'==c&&A[i].size()>=3) f[l][r][c]=min(f[l][r][c],g[l][r][i][(signed)A[i].size()-1]+1);
			for(int tim=0;tim<=25;tim++){
				for(int c=0;c<=25;c++){
					for(int t=0;t<=25;t++){
						f[l][r][c]=min(f[l][r][t]+dis[t][c],f[l][r][c]);
					}
				}
			}
			for(int i=1;i<=k;i++) g[l][r][i][1]=f[l][r][A[i][1]-'a'];
		}
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<j;k++){
				dp[i][j]=min(dp[i-1][k]+f[k+1][j][S[i]-'a'],dp[i][j]);
			}
		}
	}
	if(dp[n][m]>=1e9)cout<<-1<<endl;
	else cout<<dp[n][m]<<endl;
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：2)

[Problem Link](https://www.luogu.com.cn/problem/AT_abc261_g)

**题目大意**

> 给定字符串 $S,T$，$n$ 种操作，第 $i$ 种可以把 $S$ 中的字符 $c$ 变成字符串 $a_i$，求 $S\to T$ 的最小操作次数。
>
> 数据范围：$|S|,|T|,n,|a_i|\le 50$。

**思路分析**

考虑 dp，先设 $dp_{i,j}$ 表示 $S[1,i]\to T[1,j]$ 的最小代价，转移时我们要求 $S[i,i]\to T[j+1,k]$ 的最小代价，因此设 $f_{c,l,r}$ 表示 $c\to T[l,r]$ 的最小代价。

但是 $f_{c,l,r}$ 依然不好转移，考虑 $c$ 的上一步，对于 $|a_i|=1$ 的变换，用 Floyd 提前处理出最短路更新，我们只要考虑上一步 $|a_i|>1$ 的情况。

那么进一步，我们可以设 $g_{i,j,l,r}$ 表示 $a_{i}[1,j]\to T[l,r]$ 的最小代价，转移就是 $g_{i,j,l,r}\gets g_{i,j-1,l,k}+f_{a_{i,j},k+1,r}$，然后内部转移 $f_{c,l,r}$ 通过 $|a_i|=1$ 的操作得到，再更新 $g_{i,1,l,r}$。

时间复杂度 $\mathcal O(|T|^3\sum |a_i|)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
string s,t,a[55];
char c[55];
int n,m,p,len[55],dp[55][55],f[55][55][26],g[55][55][55][55],d[26][26];
void upd(int &x,int y) { x=x<y?x:y; }
signed main() {
	ios::sync_with_stdio(false);
	memset(f,0x3f,sizeof(f));
	memset(g,0x3f,sizeof(g));
	memset(d,0x3f,sizeof(d));
	memset(dp,0x3f,sizeof(dp));
	cin>>s>>t>>n,m=t.size(),p=s.size();
	for(int i=0;i<26;++i) d[i][i]=1;
	for(int i=1;i<=n;++i) {
		cin>>c[i]>>a[i],len[i]=a[i].size();
		if(len[i]==1) d[a[i][0]-'a'][c[i]-'a']=1;
	}
	for(int k=0;k<26;++k) for(int i=0;i<26;++i) for(int j=0;j<26;++j) {
		upd(d[i][j],d[i][k]+d[k][j]);
	}
	for(int L=1;L<=m;++L) for(int l=1,r=L;r<=m;++l,++r) {
		if(l==r) f[l][r][t[l-1]-'a']=0;
		for(int i=1;i<=n;++i) if(len[i]>1) {
			for(int j=2;j<=len[i];++j) {
				for(int k=l;k<=r;++k) {
					upd(g[l][r][i][j],g[l][k][i][j-1]+f[k+1][r][a[i][j-1]-'a']);
				}
			}
			upd(f[l][r][c[i]-'a'],g[l][r][i][len[i]]+1);
		}
		for(int i=0;i<26;++i) for(int j=0;j<26;++j) upd(f[l][r][i],f[l][r][j]+d[j][i]);
		for(int i=1;i<=n;++i) g[l][r][i][1]=f[l][r][a[i][0]-'a'];
	}
	dp[0][0]=0;
	for(int i=1;i<=p;++i) for(int j=1;j<=m;++j) {
		for(int k=1;k<=j;++k) upd(dp[i][j],dp[i-1][k-1]+f[k][j][s[i-1]-'a']);
	}
	if(dp[p][m]>inf) cout<<"-1\n";
	else cout<<dp[p][m]<<"\n";
	return 0;
}
```

---

