# Three Blocks Palindrome (easy version)

## 题目描述

The only difference between easy and hard versions is constraints.

You are given a sequence $ a $ consisting of $ n $ positive integers.

Let's define a three blocks palindrome as the sequence, consisting of at most two distinct elements (let these elements are $ a $ and $ b $ , $ a $ can be equal $ b $ ) and is as follows: $ [\underbrace{a, a, \dots, a}_{x}, \underbrace{b, b, \dots, b}_{y}, \underbrace{a, a, \dots, a}_{x}] $ . There $ x, y $ are integers greater than or equal to $ 0 $ . For example, sequences $ [] $ , $ [2] $ , $ [1, 1] $ , $ [1, 2, 1] $ , $ [1, 2, 2, 1] $ and $ [1, 1, 2, 1, 1] $ are three block palindromes but $ [1, 2, 3, 2, 1] $ , $ [1, 2, 1, 2, 1] $ and $ [1, 2] $ are not.

Your task is to choose the maximum by length subsequence of $ a $ that is a three blocks palindrome.

You have to answer $ t $ independent test cases.

Recall that the sequence $ t $ is a a subsequence of the sequence $ s $ if $ t $ can be derived from $ s $ by removing zero or more elements without changing the order of the remaining elements. For example, if $ s=[1, 2, 1, 3, 1, 2, 1] $ , then possible subsequences are: $ [1, 1, 1, 1] $ , $ [3] $ and $ [1, 2, 1, 3, 1, 2, 1] $ , but not $ [3, 2, 3] $ and $ [1, 1, 1, 1, 2] $ .

## 样例 #1

### 输入

```
6
8
1 1 2 2 3 2 1 1
3
1 3 3
4
1 10 10 1
1
26
2
2 1
3
1 1 1```

### 输出

```
7
2
4
1
1
3```

# 题解

## 作者：FCBM71 (赞：3)

居然没有人来发一波暴力？那就让菜鸡FCBM71来补上好了。

### 暴力思路

我们可以把三个子序列各看作被包含在一个区间中。我们需要做的就是寻找两个分界点，作为挡板，把整个数列一分为三，然后再在三个子区间中寻找符合条件的子序列。我们假设分出来的区间分别是 $[1,l]$，$(l,r]$，$(r,n]$，将它们命名为 $ls,ms,rs$。

对于区间 $ms$ 很好处理，因为题目中没有要求 $b$ 与 $a$ 有任何关系，所以在区间 $ms$ 中就只需要寻找一个整数 $b$ 使得 $b$ 在 $ms$ 中出现的次数最多。

那么区间 $ls,rs$ 呢？由于题目中有明确的要求，要求左子序列和右子序列元素个数相等，所以我们需要寻找一个整数 $a$ 使得 $\min(\text{a 在左区间中出现的次数，a在右区间中出现的次数})$ 有最大值。

### 代码流程

说到这里整个流程就呼之欲出了。

使用一重循环枚举 $l$，使用第二重循环枚举 $r$，第三重循环同时枚举 $a,b$。至于统计区间中 $a,b$ 的出现次数，可以使用前缀和快速解决。

核心代码。其中 `cnt[i][x]` 表示数 $i$ 在 $[1,x]$ 中出现的次数
```
inline void tomax(const int &a,const int &b){if(a<b)a=b;}

for(int l=1;l<=n;++l)
 for(int r=l;r<=n;++r){
 	int maxlr, maxmid=0;
 	for(int i=1;i<=26;++i){
 		tomax(maxlr, min(sum[i][l-1],sum[i][n]-sum[i][r]));
 		tomax(maxmid, min(sum[i][r]-sum[i][l-1]));
	}
	tomax(ans, maxlr*2+maxmid); //不要忘记*2
 }
```

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1335E1)

肯定是从值域入手，然后呢？

一开始考虑从中间的 $y$ 着手考虑，发现至少要枚举末位置和长度才能确定 $x$，不好搞，也考虑过 dp，感觉也不太会/yun

于是我开始考虑从 $x$ 着手。

考虑到一个很显然的贪心，考虑 $x$ 固定，那么对于 $a$ 而言肯定是越靠近两边越好，这样留给 $b$ 的位置就尽可能的多。

具体的，用一个 `vec` 维护每个数出现的位置。根据这个贪心，我们只要从两端向中间取就一定最优。

然后计算这个 $b$ 预处理前缀和扫一下值域就没了。


E1 可以不用前缀和，暴力对每个数在该区间找就行。（写起来更麻烦），直接放 E2 代码了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define DEBUG cout<<"when can get npy"<<endl;
const int N =3e5+10;
int a[N],s[206][N],n,ans;
vector<int> g[206];
int Slove(int l,int r,int dus,int op){
	int sum=0;
	for(int i=1;i<=200;i++){
		if(op==i)	continue;
		int now=s[i][r-1]-s[i][l];
		sum=max(sum,now);
	}
	return sum;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		ans=0;
		for(int i=1;i<=200;i++)	g[i].clear();
		cin>>n;
		for(int i=1;i<=n;i++)	for(int j=1;j<=200;j++)	s[j][i]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i],g[a[i]].push_back(i),ans=max(ans,(int)g[a[i]].size());
			for(int j=1;j<=200;j++){
				if(j==a[i])	s[j][i]=s[j][i-1]+1;
				else	s[j][i]=s[j][i-1];
			}
		}
		for(int i=1;i<=200;i++){
			if(g[i].size()==0)	continue;
			int l=0,r=(int)(g[i].size())-1,len=1;
			
			while(l<=r){
//				if(i==3)	cout<<g[i][l]<<" "<<g[i][r]<<endl;
				int now=Slove(g[i][l],g[i][r],len,i);
				if(g[i][l]==g[i][r])	ans=max(ans,1);
				else ans=max(ans,len*2+now);
				l++,r--,len++;
			}
		}
		cout<<ans<<endl;
	}
	
	return 0;
}
// 22:00 begin 
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1335E1)   
Easy 版本就用些简单做法吧！    
## 解法
我们可以枚举这个子序列开始的位置和 $x$ 的大小，之后暴力寻找最大的 $y$（或者说最大的 $2x+y$）即可。   
我们发现这题唯一的难点在于寻找最大 $y$。   
我们注意到，当 $y$ 最大时，子序列的最后一项应该也是最远的。所以我们每次只需要找到子序列的最后一项即可。   
我们考虑维护以下内容：$nxt_{i,j}$ 表示 $a_i$ 之后第 $j$ 个和 $a_i$ 相等的元素的位置。（包括 $a_i$）   
相应地我们定义 $pre_{i,j}$ 为 $a_i$ 之前第 $j$ 个（包括 $a_i$）。    
那么，我们很容易定出中间 $y$ 项的左右界。我们设 $sum_{i,j}$ 表示 $i$ 在 $1$ 到 $j$ 的出现次数。我们求解最大 $y$ 时直接暴力枚举即可。    
注意为了比较好的求解，我们可以维护 $ed_i$ 表示 $i$ 在数列中出现的最后一项位置。   
CODE：   
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
cst int N=2e3,M=26;
int ans,t,n,a[N+10],nxt[N+10][N+10],pre[N+10][N+10],ed[M+10],sum[M+10][N+10];
il int get(int i,int x,int y){
	ret sum[i][y]-sum[i][x-1];
}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	t=read<int>();
	while(t--){
		ans=0;
		memset(pre,-1,sizeof(int)*(n+1)*(n+1));
		memset(nxt,-1,sizeof(int)*(n+1)*(n+1));
		n=read<int>();
		for(int i=1;i<=n;i++){
			a[i]=read<int>();
			for(int j=1;j<=M;j++){
				sum[j][i]=sum[j][i-1]+(a[i]==j);
			}
			ed[a[i]]=i;
			for(int j=1;j<=i;j++){
				if(a[i]==a[j]){
					nxt[j][get(a[i],j,i)]=i;
				}
			}
		}
		for(int i=n;i>=1;i--){
			for(int j=n;j>=i;j--){
				if(a[i]==a[j]){
					pre[j][get(a[i],i,j)]=i;	
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n/2;j++){
				if(nxt[i][j]==-1){
					break;
				}
				if(nxt[i][j]>=pre[ed[a[i]]][j]){
					break;
				}
				int l=nxt[i][j]+1;
				int r=pre[ed[a[i]]][j]-1;
				if(l>r){
					ans=_max<int>(ans,j*2);
				}else{
					for(int k=1;k<=M;k++){
						ans=_max<int>(ans,j*2+get(k,l,r));
					}
				}
			}
		}
		for(int l=1;l<=n;l++){
			for(int r=l;r<=n;r++){
				for(int k=1;k<=M;k++){
					ans=_max<int>(ans,get(k,l,r));
				}
			}
		}
		write(ans);
		edl;
	}
	ret 0;
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

发现一个进阶回文序列仅包含三个部分：$x$ 个连续的 $a$，$y$ 个连续的 $b$，$x$ 个连续的 $a$。

对于一个 $a$，我们一定会取最外面的两个 $a$，如果不取，则答案一定不小或不变，所以我们枚举到 $a$ 的时候，一定是确定了最外围的两个 $a$ 的位置。

接下来再枚举 $x$ 并算出最内层的 $a$ 的位置，统计这两个位置之间其他数字的最大个数，也就是 $y$ 然后更新答案即可。

可提前用 vector 储存每个数字出现的位置，用前缀和统计 $[1,i]$ 中某个数字出现的次数。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[2005],ans,num[2005][27],res;
vector<int>v[27];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		for(int i=1;i<=26;++i) v[i].clear();
		memset(num,0,sizeof(num));
		scanf("%d",&n),ans=1;//答案至少为1
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=26;++j) num[i][j]=num[i-1][j];
			scanf("%d",&a[i]),v[a[i]].push_back(i),++num[i][a[i]];//前缀和统计出现次数
		}
		for(int i=1;i<=26;++i)
			if(v[i].size()>1)
			{
					res=0;
					for(int j=0;j<=(int)ceil(1.0*(v[i].size()-2)/2);++j)//枚举x
					{
						int l=v[i][j],r=v[i][v[i].size()-j-1];//找到最中间两个的位置
						if(l==r) ans=max(ans,res+1);//如果一样，则没有y，直接更新答案
						else
						{
							res+=2;
							for(int k=1;k<=26;++k) if(k!=i) ans=max(ans,res+num[r-1][k]-num[l][k]);//枚举每个数字作为b的情况，并更新答案
						}
					}
			}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：do_while_true (赞：0)

考虑~~暴力~~枚举。

首先我们通过枚举 $a$，然后枚举 $x$，暴力遍历除去两边 $x$ 个 $a$ ，求出中间 $y$ 的最大值。把跑出来的所有解取个max即可。

枚举 $x$ 我们可以用 ```vector``` 记录下 $a$ 出现的下标，然后就能做到 $\mathcal{O}(n)$ 枚举的效果。

时间复杂度 $\mathcal{O}(Tn^2)$。

[$\mathcal{Code}$](http://codeforces.com/contest/1335/submission/80865753)

为了调试方便，稍微压了一下行。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
int T,n,x,cnt[27],a[100010],vis[27];
void solve()
{
	vector<int>sum[27];
	scanf("%d",&n);
	for(int i=1;i<=26;i++)
		cnt[i]=0;
	int ans=0;
	for(int i=1;i<=n;i++) {
		scanf("%d",&x);
		a[i]=x;
		cnt[x]++;
		ans=max(ans,cnt[x]);
		sum[x].push_back(i);
	}
	for(int k=1;k<=26;k++)//枚举a 
	{
		if(cnt[k]==1||cnt[k]==0) continue;//特判无x 
		for(int i=0;i<=(cnt[k]-2)/2;i++) {//枚举x 
			int l=sum[k][i],r=sum[k][cnt[k]-i-1],maxn=0,maxx=0;
			//l,r即为y出现的区间
			for(int j=0;j<=26;j++) vis[j]=0;
			for(int j=l+1;j<r;j++) {vis[a[j]]++;maxx=max(maxx,vis[a[j]]);}
			//找一个最大的y 
			ans=max(ans,maxx+(i+1)*2);
			//判断答案 
		}
	}
	printf("%d\n",ans);
}
int main()
{
	scanf("%d",&T);
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：ctq1999 (赞：0)

$Div3$ 的 $E$  $\text{Three Blocks Palindrome}$。

## 题解

注意到 $a_i$ 是只有 $1 \leq a_i \leq 200$ ，所以可以通过枚举两个不同颜色的方式来算出答案。

定义 $sum[i][j]$ 表示在 $[1,j]$ 的范围内 $i$ 的个数。
定义 $at[i][j]$ 表示第 $j$ 个 $i$ 在数组上位置。

先 $i$ 枚举外面两个区间的颜色。再 $j$ 枚举外面两个区间的长度。得到外面区间与内区间在原数组的断点。

```cpp
int from = at[i][j - 1];
int to = at[i][sum[i][n] - j];
```

即 $[1,from]$ 和 $[to,n]$ 是两个外区间，$[from+1, to-1]$ 是内区间。

再 $k$ 枚举里面区间的长度。

```cpp
ans = max(ans, sum[i][from] + sum[k][to - 1] - sum[k][from] + sum[i][n] - sum[i][to - 1]);
```

不用 $vector$ 好像会 $\text{MLE}$，好像出题人卡空间了。

## 代码

```cpp
#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int MAXN = 200010;
const int MAXM = 210;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;

int n, m, k;
int ans, tot;

int a[MAXN];

int main(){
	int t;
	cin >> t;
	while (t--) {
		ans = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		m = 200;
		vector<vector<int> > at(m + 1);
		vector<vector<int> > sum(m + 1, vector<int>(n + 1));
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				sum[i][j] = sum[i][j - 1] + (a[j] == i);
				if (a[j] == i) {
					at[i].push_back(j);
				}
			}
		}
		for (int i = 1; i <= m; i++) {
			ans = max(ans, sum[i][n]);
			for (int j = 1; 2 * j <= sum[i][n]; j++) {
				int from = at[i][j - 1];
				int to = at[i][sum[i][n] - j];
				for (int k = 1; k <= m; k++) {
					ans = max(ans, sum[i][from] + sum[k][to - 1] - sum[k][from] + sum[i][n] - sum[i][to - 1]);
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

```




---

