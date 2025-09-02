# Flag 2

## 题目描述

According to a new ISO standard, a flag of every country should have, strangely enough, a chequered field $ n×m $ , each square should be wholly painted one of 26 colours. The following restrictions are set:

- In each row at most two different colours can be used.
- No two adjacent squares can be painted the same colour.

Pay attention, please, that in one column more than two different colours can be used.

Berland's government took a decision to introduce changes into their country's flag in accordance with the new standard, at the same time they want these changes to be minimal. By the given description of Berland's flag you should find out the minimum amount of squares that need to be painted different colour to make the flag meet the new ISO standard. You are as well to build one of the possible variants of the new Berland's flag.

## 样例 #1

### 输入

```
3 4
aaaa
bbbb
cccc
```

### 输出

```
6
abab
baba
acac
```

## 样例 #2

### 输入

```
3 3
aba
aba
zzz
```

### 输出

```
4
aba
bab
zbz
```

# 题解

## 作者：幽理家的男人 (赞：6)

这么~~简单的题~~居然没有题解，我一定要来~~水一发~~

题目中说每一行最多两种颜色，相邻格颜色又不能相同，那就只有一种情况了：就是两种不同颜色交替填充一行。

所以状态就出来了：dp[i][j][k]表示第i行第一个填j，第二个填k时的最小ans

由于这一行只与上一行有关，所以我们枚举上一行的j'和k'，保证这两行不冲突就可以转移了，即
  
     dp[i][j][k]=min(dp[i][j][k],dp[i-1][j'][k']+cost[i][j][k]
     
其中j'!=j , i'！=i ，cost[i][j][k]表示把i行变为j，k时的代价，这个数组我们可以预处理出来

最后答案就是min(dp[n][i][j]),然后我们回溯打印路径(其实时间复杂度时O(n*(26^4)),好像有点超了，~~但是我ac了~~)

```cpp

#include <bits/stdc++.h>
using namespace std;
const int maxn=505;
int n,m,dp[maxn][27][27],cost[maxn][27][27];
char si[maxn][maxn];
void dfs(int cur,int l,int r){
	if(cur==0) return;
	int temp=dp[cur][l][r]-cost[cur][l][r];
	bool juge=false;
	for(int i=0;i<26;++i){
		if(juge) break;
		if(i==l) continue;
		for(int j=0;j<26;++j){
			if(j==r) continue;
			if(dp[cur-1][i][j]==temp){
				dfs(cur-1,i,j);
				juge=true;
				break;
			}
		}
	}
	for(int i=1;i<=m;++i){
		if(i&1) printf("%c",l+'a');
		else printf("%c",r+'a');
	}
	puts("");
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>si[i][j];
		}
	}
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;++i){
		for(int j=0;j<26;++j){
			for(int k=0;k<26;++k){
				for(int l=1;l<=m;++l){
					if((l&1)&&si[i][l]-'a'!=j) cost[i][j][k]++;
					else if(((l&1)==0)&&si[i][l]-'a'!=k) cost[i][j][k]++; //预处理cost
				}
			}
		}
	}
	for(int i=0;i<26;++i){
		for(int j=0;j<26;++j) dp[0][i][j]=0;
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<26;++j){
			for(int k=0;k<26;++k){
				if(j==k) continue;
				for(int o=0;o<26;++o){
					if(o==j) continue; 
					for(int p=0;p<26;++p){
						if(p==k||p==o) continue;
						dp[i][j][k]=min(dp[i][j][k],dp[i-1][o][p]+cost[i][j][k]);//状态转移
					}
				}
			} 
		}
	}
	int ans=234543543,l,r;
	for(int i=0;i<26;++i){
		for(int j=0;j<26;++j){
			if(dp[n][i][j]<ans){
				ans=dp[n][i][j];
				l=i;
				r=j;
			} 
		}
	}
	cout<<ans<<"\n";
	dfs(n,l,r);//回溯打印路径
	return 0;
}
```cpp

---

## 作者：封禁用户 (赞：3)

## 题解：CF18E Flag 2

**UPD：增加了亿点点内容。**

一道调了 $5$ 个小时的 **DP** 题。

### 解题思路

我们由题面可推知，每一行的字母都是交替摆放的，所以可以去枚举每行所使用的两个字母分别是什么就可以了。用图片来解释一下，也就是，只能按照下图的方法放字母：

![1](https://cdn.luogu.com.cn/upload/image_hosting/z2puj2mr.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

我首先写了一个记搜，结果：[TLE](https://www.luogu.com.cn/record/162653279)。

这里的主要问题是记忆化不一定每个位置都能一次跑到最优，比如 CF 上的 `#3`，我最后一层记搜被跑了整整 $5$ 遍！

有句话说得好，叫做：“**任何记搜，都能写成 DP。**”所以我将代码改成了 DP ~~（这就是为什么 DP 代码里面会有 `memory` 这个数组名）~~。

此时，我们的思路可以大致理为：

- 从最后一个状态搜起，也就是说起点在最下层。
- 四重暴力确定每个位置用什么字母，用 DP 转移并且标注。
- 由标注反推最后的国旗。

接下来是最重要的推 DP 转移方程。若我们设行数为 $i$，上一行所出现的两个数为：$j , k$（列数为 $1$ 时也就当它有两个数就行），操作次数为 $memory_{i , j , k}$。则最后的转移方程为：

$$dp_{i , j , k} = \min(dp_{i , j1 , k1} , dp_{i - 1 , j2 , k2} + memory_{i , j1 , k1})$$

由此，写出代码不难。但是要注意，因为我们的处理顺序是从下到上，所以我们要逆序输出。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)//卡常
using namespace std;
int n , m , dp[505][30][30] , dp2[505][30][30] , dp3[505][30][30] , memory[505][30][30] , ansn , minj , mink , p , q , tmp1 , tmp2 , cost , tmp;
char a[505][505] , ans[505][505];
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= m ; j++)
		{
			cin >> a[i][j];
		}
	}
	for(int i = 0 ; i <= n ; i++)
	{
		for(int j = 0 ; j <= 'z' ; j++)
		{
			for(int k = 0 ; k <= 'z' ; k++)
			{
				if(!i)//卡常
				{
					dp[i][j][k] = 0;
				}
				else
				{
					dp[i][j][k] = 1000000007;
				}
			}
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j1 = 0 ; j1 <= 25 ; j1++)
		{	
			for(int k1 = 0 ; k1 <= 25 ; k1++)
			{
				if(j1 != k1)//卡常
				{
					for(int j2 = 0 ; j2 <= 25 ; j2++)
					{
						if(j1 != j2)//卡常
						{
							for(int k2 = 0 ; k2 <= 25 ; k2++)
							{
								if(k1 != k2 && j2 != k2)
								{
									if(memory[i][j2][k2] != 0)
									{
										cost = memory[i][j2][k2];
									}
									else
									{
										tmp = 0;
										for(int l = 1 ; l <= m ; l++)
										{
											if(l % 2)
											{
												tmp += (a[i][l] != j2 + 'a');
											}
											else
											{
												tmp += (a[i][l] != k2 + 'a');
											}
										}
										memory[i][j2][k2] = tmp;
										cost = tmp;
									}
									if(dp[i - 1][j1][k1] + cost < dp[i][j2][k2])
									{
										dp[i][j2][k2] = dp[i - 1][j1][k1] + cost;
										dp2[i][j2][k2] = j1;
										dp3[i][j2][k2] = k1;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	ansn = 1000000007;
	for(int i = 0 ; i <= 25 ; i++)
	{
		for(int j = 0 ; j <= 25 ; j++)
		{
			if(dp[n][i][j] < ansn)
			{
				ansn = dp[n][i][j];
				minj = i;
				mink = j;
			}
		}
	}
	cout << ansn << '\n';
	p = minj;
	q = mink;
	for(int j = n ; j >= 1 ; j--)
	{
		for(int i = 1 ; i <= m ; i++)
		{
			if(i % 2)
			{
				ans[j][i] = p + 'a';
			}
			else
			{
				ans[j][i] = q + 'a';
			}
		}
		tmp1 = dp2[j][p][q];
		tmp2 = dp3[j][p][q];
		p = tmp1;
		q = tmp2;
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= m ; j++)
		{
			cout << ans[i][j];
		}
		cout << "\n";
	}
	return 0;
}
```

卡常 $1.9\text{s}$ 过。

### 优化介绍

- 第 $1$ 点，可以对模运算进行优化：
    + 若 $n = 2^k$，且 $k$ 为非负整数，则代码 `a % n` 可以写为 `a & (n - 1)`。
- 第 $2$ 点，可以降低内存抖动：
    + 在电脑的 CPU 中，有 $3$ 级 CaChe，最快的一级直接通往 CPU 进行运算，其余几级和更高一级 CaChe 进行数据交换，最低级 CaChe 和内存进程数据交换，所以我们可以通过降低交换次数来卡常。
    + 在 GCC 编译器中，会优先把连续的内存位置拿进 CaChe，所以说让编辑的变量或数组尽量连续，就可以提高速度。
    + 举个例子：下面这张图是我上面那份代码用 `dp1` 和 `dp2` 存储答案的过程：
    
    + ![2](https://cdn.luogu.com.cn/upload/image_hosting/tqg4x2pu.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)
    
    + 然后我将 `dp1` 和 `dp2` 合并进了 `dp`，数组，并且加了一维来存储，那么存储会变为：
    
    + ![3](https://cdn.luogu.com.cn/upload/image_hosting/ejp6jn07.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)
    
    + 所以有时对数组进行优化就会快很多。
    + 最后补充一点，我们熟知的 O2 优化中的一部分优化就是调整你代码中申请空间的顺序。
    
### 优化后的参考代码:

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)//卡常
using namespace std;
int n , m , dp[505][30][30][5] , memory[505][30][30] , ansn , minj , mink , p , q , tmp1 , tmp2 , cost , tmp;
char a[505][505] , ans[505][505];
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= m ; j++)
		{
			cin >> a[i][j];
		}
	}
	for(int i = 0 ; i <= n ; i++)
	{
		for(int j = 0 ; j <= 'z' ; j++)
		{
			for(int k = 0 ; k <= 'z' ; k++)
			{
				if(!i)//卡常
				{
					dp[i][j][k][1] = 0;
				}
				else
				{
					dp[i][j][k][1] = 1000000007;
				}
			}
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j1 = 0 ; j1 <= 25 ; j1++)
		{	
			for(int k1 = 0 ; k1 <= 25 ; k1++)
			{
				if(j1 != k1)//卡常
				{
					for(int j2 = 0 ; j2 <= 25 ; j2++)
					{
						if(j1 != j2)//卡常
						{
							for(int k2 = 0 ; k2 <= 25 ; k2++)
							{
								if(k1 != k2 && j2 != k2)
								{
									if(memory[i][j2][k2] != 0)
									{
										cost = memory[i][j2][k2];
									}
									else
									{
										tmp = 0;
										for(int l = 1 ; l <= m ; l++)
										{
											if(l & 1) 
											{
												tmp += (a[i][l] != j2 + 'a');
											}
											else
											{
												tmp += (a[i][l] != k2 + 'a');
											}
										}
										memory[i][j2][k2] = tmp;
										cost = tmp;
									}
									if(dp[i - 1][j1][k1][1] + cost < dp[i][j2][k2][1])
									{
										dp[i][j2][k2][1] = dp[i - 1][j1][k1][1] + cost;
										dp[i][j2][k2][2] = j1;
										dp[i][j2][k2][3] = k1;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	ansn = 1000000007;
	for(int i = 0 ; i <= 25 ; i++)
	{
		for(int j = 0 ; j <= 25 ; j++)
		{
			if(dp[n][i][j][1] < ansn)
			{
				ansn = dp[n][i][j][1];
				minj = i;
				mink = j;
			}
		}
	}
	cout << ansn << '\n';
	p = minj;
	q = mink;
	for(int j = n ; j >= 1 ; j--)
	{
		for(int i = 1 ; i <= m ; i++)
		{
			if(i & 1)//卡常 
			{
				ans[j][i] = p + 'a';
			}
			else
			{
				ans[j][i] = q + 'a';
			}
		}
		tmp1 = dp[j][p][q][2];
		tmp2 = dp[j][p][q][3];
		p = tmp1;
		q = tmp2;
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= m ; j++)
		{
			cout << ans[i][j];
		}
		cout << "\n";
	}
	return 0;
}
```

优化后用时减少了 $400\text{ms}$，最后用时 $1.5\text{s}$。

---

## 作者：mountain_climber (赞：1)

一道好题，但是感觉评紫太高了，毕竟某些 $2300$ 才评蓝呢。

首先我们注意到，根据题目描述显然可以得到，一行的格式一定是 $abababa....$ 也就是说奇数位置上是一个字母，偶数位置上是一个字母，那么一行的样式就被这一行的第一个字母和第二个字母唯一确定了。此时我们就可以想到一个对于每行贪心的简易贪心思路，但是注意到题目也要求上下相邻的两个字母不能相同，所以贪心就不行，开始考虑 $dp$。

观察到每行都有一个独立的性质，所以我们先考虑 $dp_{i}$ 表示第 $i$ 行所能取得的最大值，然后发现上下两行的字母不同可以变为这一行的字母和上一行的字母不同。最后我们又发现，每行可以用一个有序字符对 $(a,b)$ 来表示，$a$ 表示第一个字符，$b$ 表示第二个字符。那么可以设计出状态 $dp_{i,j,k}$ 表示第 $i$ 行的上一行第一个字符为 $j$，第二个字符为 $k$ 时所需要的最小操作次数。

状态设计完成了，状态转移就是显然的了，只要两个状态的 $j,k$ 不相同，就可以转移。即 $dp_{i,j,k}=\min dp_{i-1,j_{1},k_{1}}(j\neq j_{1},k\neq k_{1})+cost(i,j,k)$，其中 $cost(i,j,k)$ 表示第 $i$ 行变为第一个字符是 $j$，第二个字符是 $k$ 的格式所需的代价。

最后粘一下 $AC$ 记录罢（代码，就在其中！）。[AC](https://codeforces.com/contest/18/submission/231926475)

---

## 作者：daitangchen2008 (赞：0)

## 分析  
一行最多两个元素，相邻元素不相同，告诉我们每一行最多有两个字母。  
于是令 $dp_{i,a,b}$ 为第 $i$ 行奇数位字母为 $a$，偶数为字母为 $b$。
对于每层字母的选择造成的代价，我们对原数组遍历求出。设这个代价为 $x$。  
于是便有动态转移方程：  
$$dp_{i,a,b}=\min (dp_{i-1,c,d})+x,a \ne b,c \ne d,a \ne c,b \ne d $$
顺带记录转移路径，即可求出答案。

## 代码 

```cpp
#include<bits/stdc++.h>
using namespace std;
int jia[501][28];
int jib[501][28];
int dpa[501][28];
int dpb[501][28];
int dp[501][28][28];
int ch[502][502];
int numa;
int numb;
struct node
{
	int x;
	int y;
}tmd[5005][28][28];
int n,m;
void dfs(int k,int x,int y)
{
	if(k==1)
	{
		for(int i=0;i<m;i++)
		if(i%2==0)
			cout<<(char)(x+'a'-1);
		else
			cout<<(char)(y+'a'-1);
		cout<<endl;
		return ;
	}
	dfs(k-1,tmd[k][x][y].x,tmd[k][x][y].y);
	for(int i=0;i<m;i++)
	if(i%2==0)
	cout<<(char)(x+'a'-1);
	else
	cout<<(char)(y+'a'-1);
	cout<<endl;
}
int  main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		string st;
		cin>>st;
		for(int j=0;j<m;j++)
		{
			if(j%2==0)
			{
				jia[i][(int)(st[j]-'a')+1]++;
			if(i==1)
				numa++;
			}
			else
			{
				jib[i][(int)(st[j]-'a')+1]++;
				if(i==1)
				numb++;
			}
			ch[i][j]=(int)(st[j]-'a')+1;
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=26;j++)
		{
			dpa[i][j]=numa;
			dpb[i][j]=numb;
		}
	for(int i=1;i<=26;i++)
		for(int j=1;j<=26;j++)
		{
			dp[1][i][j]=m-jia[1][i]-jib[1][j];
			if(i==j)
			dp[1][i][j]=m;
		}
			
	for(int i=2;i<=n;i++)
		for(int j=1;j<=26;j++)
			for(int k=1;k<=26;k++)
				dp[i][j][k]=m*i;
	for(int i=2;i<=n;i++)
		for(int a=1;a<=26;a++)
			for(int b=1;b<=26;b++)
			{
				int x=a;
				int y=b;

				if(x==y)
				continue;
				for(int c=1;c<=26;c++)
					for(int d=1;d<=26;d++)
						if(x!=c&&y!=d&&c!=d)
						{
							if(dp[i][x][y]>dp[i-1][c][d]+m-jia[i][x]-jib[i][y])
							{
								dp[i][x][y]=min(dp[i][x][y],dp[i-1][c][d]+m-jia[i][x]-jib[i][y]);
								tmd[i][x][y].x=c;
								tmd[i][x][y].y=d;
							}
							
						}
							
			}
	int ans=n*m;
	int ansx=0;
	int ansy=0;
	for(int i=1;i<=26;i++)
		for(int j=1;j<=26;j++)
		{
			if(ans>dp[n][i][j])
			{
				ans=min(ans,dp[n][i][j]);
				ansx=i;
				ansy=j;
			}
		
		}
		cout<<ans<<endl;
	dfs(n,ansx,ansy);
	return 0;
}
```

---

## 作者：Svemit (赞：0)

[link](https://www.luogu.com.cn/problem/CF18E)

小清新 dp 题。

有点像[这道题](https://www.luogu.com.cn/problem/P1854)。

# Solution : 

发现 $n$ 和字符集大小都很小，考虑暴力 dp。

定义 $f_{i, j, k}$ 为已经填了前 $i$ 行，第 $i$ 行的前两个字符为 $j, k$ 的最小代价。$cost_{i, j, k}$ 为把第 $i$ 行的前两个字符改成 $j, k$ 的代价，$cost$ 是可以暴力算的。

转移方程是 
$$f_{i, j, k} = \min (f_{i-1, fst, scd}) + cost_{i, j, k}$$

输出方案的话，直接按一般的套路递归找就可以了。

code 

```cpp
int n, m;
string s[N];
int f[N][26][26], cost[N][26][26];
void output(int x, int fst, int scd) {
	if(!x) return;
	int lst = f[x][fst][scd] - cost[x][fst][scd];
	rep(i, 0, 25) rep(j, 0, 25)	{
		if(i == fst || j == scd || i == j) continue;
		if(f[x - 1][i][j] == lst) {
			output(x - 1, i, j); 
			goto ed;
		}	
	}
	ed:;
	rep(i, 1, m) 
		if(i & 1) cout << (char)('a' + fst);
		else cout << (char)('a' + scd);
	cout << '\n';
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cin >> n >> m;
	rep(i, 1, n) cin >> s[i], s[i] = " " + s[i];
	rep(i, 1, n) rep(j, 0, 25) rep(k, 0, 25) {
		auto &v = cost[i][j][k];
		rep(l, 1, m) {
			if(l & 1) v += s[i][l] != 'a' + j;
			else v += s[i][l] != 'a' + k;
		}
	}
	memset(f, 0x3f, sizeof f);
	rep(i, 0, 25) rep(j, 0, 25) f[0][i][j] = 0;
	rep(i, 1, n) rep(j, 0, 25) rep(k, 0, 25) {
		if(k == j) continue;
		rep(fst, 0, 25) {
			if(fst == j) continue;
			rep(scd, 0, 25) 
				if(scd != k && scd != fst) {
					f[i][j][k] = min(f[i][j][k], f[i - 1][fst][scd] + cost[i][j][k]);
				}	
		}
	}
	int ans = INF, fst, scd;
	rep(i, 0, 25) rep(j, 0, 25) 
		if(f[n][i][j] < ans) {
			ans = f[n][i][j];
			fst = i, scd = j;
		}
	cout << ans << '\n';
	output(n, fst, scd);
	return 0;
}
```



---

## 作者：_Extroversion (赞：0)

本题动态规划求最小答案不难，但毒瘤的是要输出方案，难以下手。因此，我重点讲解如何输出方案。


------------
## 求最小答案

对于每一行，只能两种颜色交替填涂，确定了前两个方格的颜色，这一行就被确定了。设 $dp[i][j][k]$ 表示填涂完前 $i$ 行，第 $i$ 行交替填涂第 $j,k$ 种颜色的最小答案。明显转移只依赖上一行的状态，找上一行合法状态的最小值，再加上本行填涂的代价即可，时间复杂度 $O(n\times 26^4)$，如果在当前状态不合法时提前跳过循环，复杂度就跑不满，本题时限 $2s$，这么做不会时间超限。

## 输出方案

先从第 $n$ 行分析，枚举每个 $dp[n][i][j]$，当其为最小值时，就能确定第 $n$ 行方案为第 $i,j$ 种颜色交替填涂。那该怎么处理第 $n-1$ 行呢？$dp[n][i][j]$ 的最小值减去以第 $n$ 行方案填涂的代价，就是转移到最小的 $dp[n][i][j]$ 的 $dp[n-1][i][j]$ 的值，找出此时的 $i,j$，就能确定第 $n-1$ 行的方案。

以此类推，每一行的方案都可以求解。题目要求从第一行输出，用二维数组存储输出，或使用递归实现逆序输出均可解决。

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF18E)

显然每行必须两个颜色交错放满。

考虑纯暴力，设 $dp_{i,j,k}$ 表示第 $i$ 行交错放 $j$ 和 $k$ 的最小答案。

然后相邻格子不同色，所以需要考虑上一行放的颜色 $j',k'$ 进行转移。预处理出 $f_{i,j,k}$ 表示把 $i$ 行填满 $j,k$ 的操作次数，转移方程即  $dp_{i,j,k}=\min (dp_{i,j,k},dp_{i-1,j',k'}+f_{i,j,k})$。

输出方案就从最后一行选的颜色起手，根据花费的代价一行行推回去即可，最后回溯的时候输出。

时间复杂度 $O(n|S|^4)$，其中 $|S|=26$。

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2000}$
---
### 解题思路：

每一行中只能出现两种颜色，而且相邻的颜色又不能相同，那么每一行的颜色一定是 $\text{ABABAB....}$ 的形式。

然后直接暴力 $\text{DP}$ 就可以了，设 $f_{i,j,k}$ 表示考虑到第 $i$ 行，其中上一行的第一个字母是 $j$，第二个是 $k$（后面两维就可以确定整行的序列了）的最小代价。

转移的时候，只要当前行与上一行的 $j$ 和 $k$ 完全不相等，那么就可以转移，每一行更改的代价可以记录下来以方便下一次使用。然后记下每一个位置是由哪一个转移过来的就行了。

---
### 代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,f[505][30][30],frj[505][30][30],frk[505][30][30],minx,minj,mink,nowj,nowk,nowi;
int cost[505][30][30];
char a[505][505],ans[505][505];
char get(){
	char c=getchar();
	while(c=='\n'||c=='\r'||c==' ')c=getchar();
	return c;
}
int calc(int now,char c1,char c2){
	if(cost[now][c1-'a'][c2-'a']!=0)return cost[now][c1-'a'][c2-'a'];
	int ans=0;
	for(int i=1;i<=m;i++){
		if(i&1)ans+=a[now][i]!=c1;
		else ans+=a[now][i]!=c2;
	}
	return cost[now][c1-'a'][c2-'a']=ans;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
	a[i][j]=get();
	
	memset(f,0x3f3f,sizeof(f));
	for(int i=0;i<=25;i++)
	for(int j=0;j<=25;j++)
	f[0][i][j]=0;
	
	for(int i=1;i<=n;i++){
		for(int j=0;j<=25;j++){	
			for(int k=0;k<=25;k++){
				if(j!=k)
				for(int j1=0;j1<=25;j1++){
					if(j!=j1)
					for(int k1=0;k1<=25;k1++){
						if(k!=k1&&j1!=k1){
							int cost=calc(i,j1+'a',k1+'a');
							if(f[i-1][j][k]+cost<f[i][j1][k1]){
								f[i][j1][k1]=f[i-1][j][k]+cost;
								frj[i][j1][k1]=j;
								frk[i][j1][k1]=k;
							}
						}
					}
				}
			}
		}
	}
	
	
	minx=2147483647;
	for(int i=0;i<=25;i++)
	for(int j=0;j<=25;j++){
		if(f[n][i][j]<minx){
			minx=f[n][i][j];
			minj=i;mink=j;
		}
	}
	printf("%d\n",minx);
	nowj=minj;nowk=mink;nowi=n;
	while(nowi!=0){
		for(int i=1;i<=m;i++){
			if(i&1)ans[nowi][i]=nowj+'a';
			else ans[nowi][i]=nowk+'a';
		}
		int nj=frj[nowi][nowj][nowk],nk=frk[nowi][nowj][nowk];
		nowj=nj;nowk=nk;
		nowi--;
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
		printf("%c",ans[i][j]);
		printf("\n");
	}
	return 0;
}
```


---

