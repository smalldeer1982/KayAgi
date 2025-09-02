# [ABC142E] Get Everything

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc142/tasks/abc142_e

鍵のかかった宝箱が $ N $ 個あり、$ 1 $ から $ N $ までの番号がつけられています。

店で $ M $ 個の鍵が売られています。$ i $ 個目の鍵は $ a_i $ 円で販売されており、$ b_i $ 種類の宝箱 $ c_{i1} $ , $ c_{i2} $ , ..., $ c_{i{b_i}} $ を開けることが出来ます。購入した鍵は何度でも使うことが出来ます。

全ての宝箱を開ける為に必要な費用の最小値を答えてください。全ての宝箱を開けることが不可能である場合は $ -1 $ を出力してください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ <\ =\ N\ <\ =\ 12 $
- $ 1\ <\ =\ M\ <\ =\ 10^3 $
- $ 1\ \leq\ a_i\ \leq\ 10^5 $
- $ 1\ \leq\ b_i\ \leq\ N $
- $ 1\ \leq\ c_{i1}\ <\ c_{i2}\ <\ ...\ <\ c_{i{b_i}}\ \leq\ N $

### Sample Explanation 1

鍵 $ 1 $ と鍵 $ 2 $ を購入すると、全ての宝箱を開けることが出来ます。このときの費用は $ 25 $ 円であり、これが最小値です。

### Sample Explanation 2

全ての宝箱を開けることは出来ません。

## 样例 #1

### 输入

```
2 3
10 1
1
15 1
2
30 2
1 2```

### 输出

```
25```

## 样例 #2

### 输入

```
12 1
100000 1
2```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 6
67786 3
1 3 4
3497 1
2
44908 3
2 3 4
2156 3
2 3 4
26230 1
2
86918 1
3```

### 输出

```
69942```

# 题解

## 作者：__Chx__ (赞：2)

## 题目大意
给出 $N$ 个箱子和 $M$ 把钥匙，每把钥匙能开 $b_i$ 个固定编号箱子，且价值为 $a_i$，求打开全部门的费用的最小值。如果不能打开所有门，则输出 $-1$。

## 思路
因为 $1 \leq N \leq 12$，考虑状态压缩，设 $dp_i$ 为在 $i$ 状态下的费用的最小值，则转移方程为 $dp_i=\min(dp_i,dp_j+dp_{i \oplus j})$。这种转移显然是有问题的，每个给出的状态不一定相互对应，所以我考虑到一种 $down_i$ 操作：

- 对于给出状态 $i$，枚举状态 $0 \leq j \leq i$
- 如果 $i \mid j=i$，$dp_j=\min(dp_j,dp_i)$

$down_i$ 解释：当状态 $j$ 开的箱子数量不大于状态 $i$，且对于状态 $i$ 未打开的每个箱子状态 $j$ 也未打开，这时花 $dp_i$ 的代价也可以开状态 $j$ 的箱子。

至于判无解，可以统计钥匙的种类数，如果种类数小于箱子数，即为无解。

具体细节请参考代码。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,dp[5005],c[5005],s;
bool k[5005];
signed main(){
	cin>>n>>m;
	c[1]=1;
	for(int i=2;i<=n;i++) c[i]=c[i-1]*2;//预处理2的次方 
	memset(dp,0x3f,sizeof dp); //初始化 
	for(int i=1;i<=m;i++){
		int a,b,w=0;
		cin>>a>>b;
		for(int j=1;j<=b;j++){
			int x;
			cin>>x;
			w+=c[x];
			if(!k[x]) k[x]=1,s++;//统计钥匙种类 
		}
		for(int j=0;j<=w;j++)//down操作 
			if((w|j)==w) dp[j]=min(dp[j],a);
	}
	if(s<n){//判无解 
		cout<<-1;
		return 0;
	}
	for(int i=0;i<(1<<n);i++)
		for(int j=0;j<=i;j++)
			dp[i]=min(dp[i],dp[i^j]+dp[j]);//状态转移 
	cout<<dp[(1<<n)-1]<<endl;
	return 0;
}
```


---

## 作者：StevenLiTheOIer (赞：1)

## 思路：
看到 $n\le12$ 就可以考虑搜索或状压了。这里给出状态压缩 dp 的解法。

每一把钥匙所能打开的箱子集合都可以表示为一个不超过 $2^n$ 的二进制数，如样例 #3 中的
```cpp
1 3 4
```
就可以表示为二进制数 $1101$。

设计状态 $dp_S$ 表示开启集合 $S$ 中的箱子所需的最小代价，$T_i$ 为第 $i$ 把钥匙能打开的箱子集合。则可以设计出转移方程为：

```cpp
dp[S | T[i]] = min(dp[S | T[i]], dp[S] + cost[i]);
```
从小到大枚举并转移即可。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[(1 << 12) + 6], a[1006], cnt[1006];
int main()
{
	int n, m;
	cin >> n >> m;
	memset(dp, 0x3f, sizeof(dp));
	for (int i = 1; i <= m; i++)
	{
		cin >> a[i];
		int b;
		cin >> b;
		for (int j = 1; j <= b; j++)
		{
			int c;
			cin >> c;
			cnt[i] |= (1 << (c - 1));//预先计算出每把钥匙能打开的箱子集合
		}
	}
	dp[0] = 0;//警示后人，要初始化
	for (int S = 0; S <= (1 << n) - 1; S++)
	{
		if (dp[S] == 0x3f3f3f3f) continue;
		for (int i = 1; i <= m; i++)
			dp[S | cnt[i]] = min(dp[S | cnt[i]], dp[S] + a[i]);
	}
	if (dp[(1 << n) - 1] == 0x3f3f3f3f) cout << -1 << endl;
	else cout << dp[(1 << n) - 1]<< endl;
    //最终答案为dp[(1 << n) - 1]
	return 0;
}
```

---

## 作者：liyixi09 (赞：1)

# 题目大意

现在有 $N$ 个不同的箱子和 $M$ 把钥匙，第 $i$ 把钥匙总共可以打开编号为 $c_1,c_2,...,c_{b_i}$ 的箱子，价格为 $a_i$。现在想打开所有的箱子，请问最小代价是多少。输出这个最小代价。

------------

# 思路

我们可以注意到：$1 \le N \le 12$，所以我们可以用一个二进制数来表示每把钥匙可以开哪些箱子。比如第 $1$ 把钥匙可以可以开第 $1,3,4$ 个箱子，则我们可以表示为：$c_1=(1011)_2$。

使用这种方法,我们记录目前可以打开的箱子的时间复杂度由 $O(b_i)$ 降为 $O(1)$。

考虑记忆化搜索，记忆能够打开的箱子的最小代价。

剪枝：当目前打开箱子的代价大于已记录的当前最小代价，就没有必要继续搜了。

注意：如果买下所有钥匙也不能打开所有箱子，直接输出 ```-1``` 。

------------

# code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,all,can_run;
int a[1005],b[1005],c[1005];
int f[500005];
inline int read(){
	int f=1,x=0;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		f=-1;
		c=getchar();
	}
	while(isdigit(c))
	x=x*10+c-'0',c=getchar();
	return x*f;
}
void dfs(int x,int xans,int cnt){
	if(x>m)
	return ;
	if(f[cnt]<xans)
	return ;
	f[cnt]=min(f[cnt],xans);
	if(cnt==all)
	{
		return ;
	}
	dfs(x+1,xans,cnt);
	dfs(x+1,xans+a[x],cnt|c[x]);
}
signed main(){
	n=read();
	m=read();
	memset(f,0x3f,sizeof f);
	for(int i=1;i<=n;i++)
	all|=(1<<(i-1));
	for(int i=1;i<=m;i++)
	{
		a[i]=read();
		b[i]=read();
		for(int j=1;j<=b[i];j++)
		{
			int x;
			x=read();
			c[i]|=(1<<(x-1));
		}
		can_run|=c[i];
	}
	if(can_run!=all)
	{
		printf("%d\n",-1);
		return 0;
	}
	dfs(1,0,0);
	printf("%lld\n",f[all]);
	return 0;
} 
```


---

## 作者：dd_d (赞：1)

## Sol
看到 $n$ 这么小，考虑状压。  
设 $dp_{stat}$ 表示开了状态为 $stat$ 的箱子所需最小花费。  
则方程为 ``` f[i|d[j]]=min(f[i|d[j]],f[i]+a[j]); ```  
其中 $i$ 即为 $stat$，$d_j$ 存了第 $j$ 把钥匙的能开的箱子。  
具体细节看代码。
## Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=1001;
int n,m,a[N],b[N],c[N][N],d[N],f[100001];
signed main()
{
	n=read(); m=read();
	for (int i=1;i<=m;i++)
	{
		a[i]=read(); b[i]=read();
		for (int j=1;j<=b[i];j++)
			c[i][read()]=1;
		d[i]=0;
		for (int j=1;j<=n;j++)
		{
			d[i]*=2;
			if (c[i][j]==1) d[i]++;
		}
	}
	int k=(1<<n)-1; //k表示每个箱子都开的状态。
	for (int i=1;i<=k;i++)
		f[i]=1e9;
	f[0]=0;  //注意f[0]的初值。
	for (int i=0;i<=k;i++)
		for (int j=1;j<=m;j++)
			f[i|d[j]]=min(f[i|d[j]],f[i]+a[j]);
	if (f[k]==1e9) puts("-1");
	else writeln(f[k]);
}



```


---

## 作者：_zexal_ (赞：1)

#### 思路
注意到 $n \leq 12$，不妨考虑一下状压。我们用 $S$ 表示我们的状态，如果 $S$ 的二进制第 $i$ 为是 $1$ 表示我们拿了他了，这样方程就显而易见了，我们用 $f_S$ 表示拿的状态为 $S$ 时的最小花费即可。转移更简单，只需要枚举每一种状态，然后用或运算即可。
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int Maxn=2e6;
long long n,m,f[1<<15],h[Maxn],num[Maxn],k,k1;
vector <int> v[15]; 
signed main(){
		memset(f,0x7f,sizeof f);
	for(int i=1;i<=(1<<13);i++) f[i]=1e14;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>h[i];
		cin>>k;
		for(int j=1;j<=k;j++){
			cin>>k1;
			num[i]+=(1<<(k1-1));
			f[(1<<(k1-1))]=min(h[i],f[(1<<(k1-1))]);
		}
	}
//	for(int i=0;i<m;i++) cout<<num[i]<<endl;

	f[0]=0;
	for(int i=0;i<(1<<n);i++){
		for(int j=0;j<m;j++){
			f[i|num[j]]=min(f[i|num[j]],f[i]+h[j]);
		//	cout<<(i|num[j])<<" "<<f[i|num[j]]<<endl;
		}
	}
	//cout<<f[8];
	if(f[(1<<(n))-1]!=1e14)cout<<f[(1<<n)-1];
	else cout<<-1;
	return 0;
}	
```


---

## 作者：Kreado (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc142_e)。

#### 思路

由于 $n\le12$，结合经验得出这是一道状压 dp。 

另外说一下，此题是一个极其入门的状压 dp，非常适合用来练练手。

我们令 $S$ 表示当前箱子状态，$P_i$ 表示第 $i$ 把钥匙能开的箱子。

设 $f_S$ 表示开启当前状态箱子的最小花费。

能得到转移方程

$$f_{P_i|i}=\min(f_{P_i|i},f_i+a_i)$$

时间复杂度 $O(2^nnm)$，实际可以优化到 $O(2^nm)$。

#### 贴贴代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll Maxn=1e3+7,Maxm=(1<<13),inf=1e13;
ll n,m,a[Maxn],f[Maxm],b[Maxn],c[Maxn][20];
int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=m;i++){
		scanf("%lld%lld",&a[i],&b[i]);
		for(ll j=1;j<=b[i];j++) scanf("%lld",&c[i][j]);
	}
	for(ll i=1;i<=Maxm-1;i++) f[i]=inf;
    // 这里省略了 f[0]=0;
	for(ll i=0;i<(1<<n);i++){
		for(ll j=1;j<=m;j++){ 
			ll p=i;
			for(ll k=1;k<=b[j];k++)
				if(!(p&(1<<(c[j][k]-1))))p=p^(1<<(c[j][k]-1));
			f[p]=min(f[p],f[i]+a[j]);
		}
	}
	if(f[(1<<n)-1]==inf) printf("-1");
	else printf("%lld",f[(1<<n)-1]);
	return 0;
}
```


---

