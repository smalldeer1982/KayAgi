# [ABC385C] Illuminate Buildings

## 题目描述

## 翻译  
这里有 $N$ 栋建筑等距排成一行。记 $H_i$ 为第 $i$ 栋建筑的高度。

你想要给一些建筑装上灯光，有 2 个前提：   
1.选择的建筑都有相同的高度。  
2.选择的建筑以相等的间隔排列。  

请问你可以选择最多多少栋建筑？我们认为只选择一栋建筑是满足条件的。

## 样例 #1

### 输入

```
8
5 7 5 7 7 5 7 7```

### 输出

```
3```

## 样例 #2

### 输入

```
10
100 200 300 400 500 600 700 800 900 1000```

### 输出

```
1```

## 样例 #3

### 输入

```
32
3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3 2 3 8 4 6 2 6 4 3 3 8 3 2 7 9 5```

### 输出

```
3```

# 题解

## 作者：Tomwsc (赞：2)

## 题意：

给你一串数，让你求间隔相等且数值相同的最长子序列。

## 思路：

考虑 dp。

我们设 $dp[i][j]$ 表示到第 $i$ 个数字时，数列间隔为 $j$ 的最长子序列个数。

设计完状态，我们来推方程：

我们分两类讨论：

- 若 $h[i] = h[i - j]$ 则易得有 $dp[i][j] = dp[i - j][j] + 1$。
- 若 $h[i] \neq h[i - j]$ 则因为 $dp[i][j]$ 不能从 $dp[i - j][j]$ 转移而来，所以 $dp[i][j] = 1$。

答案即为 dp 数组中的最大值。

时间复杂度为：$O(n^2)$。

## 代码实现：

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 3005 , MIN = -2147483648;
int n , ans = MIN * (- MIN);
int h[MAXN];
int dp[MAXN][MAXN];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(register int i = 1;i <= n;i ++)
		cin >> h[i];
	for(register int i = 0;i <= n;i ++)
		for(register int j = 0;j <= n;j ++)
			dp[i][j] = MIN * (-MIN);
	for(register int i = 1;i <= n;i ++) {
	    for(register int j = 1;j <= n;j ++)
	        dp[i][j] = 1;
		for(register int j = 1;j <= i;j ++) {
			dp[i][j] = 1;
			if(h[i] == h[i - j])
				dp[i][j] = dp[i - j][j] + 1;
			ans = max(ans , dp[i][j]);
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：hjyowl (赞：2)

### 思路

这个要求很明显是一个二维关系，直接处理并不好处理。

故考虑定住一位，即值相等，对于值相等的，再去考虑差值相等。

现在问题转变成了，有一个序列 $a$，请你求出当中的最长等差子序列。

我们直接对于其中的每一个元素，枚举差，然后去求出能往后跑多远，然后去一个最大值。

时间复杂度：$\Theta(n^2\log n)$，这里带有较小的常数因子。

### 复杂度证明

```cpp
	for (int i = 1; i <= 3000; i ++ ){
		if (vec[i].size()){
			for (int j = 1; j < vec[i].size(); j ++ ){
```

这两重循环，由于最多只有 $n$ 个数，所以说这一串遍历的时间复杂度为 $\Theta(n)$。

```cpp
				for (int k = 1; k <= 3000; k ++ ){
					int t = 0;
					int c = vec[i][j];
					while (mp[i][c] && c + k <= 3010){
						c += k;
						t ++ ;
					}
      }
```

这层循环，时间复杂度为：

 $$\sum_{i=1}^n \frac{n}{i}=O( n \log n)$$

$\Theta(n \log n)$ 乘上 $\Theta(n)$ 得到时间复杂度为 $\Theta(n \log n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
int n,m,x,y;
int a[N];
bool debug = 0;
vector<int>vec[N];
int mp[N][N];
int main(){
	cin >> n;
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i];
		if (vec[a[i]].size() == 0){
			vec[a[i]].push_back(-1);
		}
		vec[a[i]].push_back(i);
		mp[a[i]][i] = 1;
	}
	int res = 0;
	for (int i = 1; i <= 3000; i ++ ){
		if (vec[i].size()){
			for (int j = 1; j < vec[i].size(); j ++ ){
				for (int k = 1; k <= 3000; k ++ ){
					int t = 0;
					int c = vec[i][j];
					while (mp[i][c] && c + k <= 3010){
						c += k;
						t ++ ;
					}
					res = max(res,t);
				}
			}
		}
	}
	cout << res;
	return 0;
}
```

---

## 作者：DoubleQLzn (赞：1)

本题目考察动态规划。

我们可以设计状态 $dp_{i,k}$ 表示从 $1$ 到 $i$ 之间间隔为 $k$ 的最大值。由于最少有一个元素符合要求，因此任意的 $dp_{i,k}=1$，当 $a_i=a_j$ 且 $j<i$ 时可以发生一次转移，状态转移公式为 $dp_{i,i-j}=dp_{j,i-j}+1$。最后取最大值。

### Code 

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[3005][3005],a[3005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,x;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=1;j<=n;j++)dp[i][j]=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[i]==a[j]){
				dp[i][i-j]=max(dp[i][i-j],dp[j][i-j]+1);
			}
		}
	}
	int ma=INT_MIN;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)ma=max(ma,dp[i][j]);
	}
	cout<<ma;
	return 0;
}
```

---

## 作者：liuziqin (赞：1)

## 思路

由于 $N,H_i \le 3000$，$O(n^2 \log n)$ 级别的时间复杂度可过。

考虑枚举房屋之间的间隔 $t$，因此所枚举每个房屋的起始点为 $[1,t]$。最后在枚举的序列中找到最长的相等且相邻的元素即可。

## Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=3005;
int h[N];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>h[i];
	int ans=1;
	for(int t=1;t<=n;t++){//暴力枚举间隔
		for(int i=1;i<=t;i++){
			int sum=0;
			for(int j=i;j<=n;j+=t){
				ans=max(ans,sum);
				if(j==i||h[j]==h[j-t])sum++;
				else sum=1;
				ans=max(ans,sum);
			}//求出最长的合法序列
		}
	}
	cout<<ans<<"\n";
}
```

---

## 作者：Ivan422 (赞：1)

模版级动态规划，看在最长上升子序列的份上勉强评个黄应该可以。

题目就是我们考虑在 $n$ 个数里选数，让这些数两两相等，并且序列中相邻的两项在原序列中距离之差**相等**。

怎么做呢？定义 $f_{i,j}$ 为前 $i$ 个数，两两距离差 $j$。

考虑转移，按照最长上升子序列的模版，要是 $h_i=h_j$，可以转移。我们先给出转移式子 $f_{i,i-j}=f_{j,i-j}+1$。其实就是差可以求出来，就是 $i-j$，剩下原样转移即可。

这里初始化是 $f_{i,j}$ 为 $1$，因为自己也是一个子序列。

答案就是 $\max f_{i,j}$。

通过代码：[链接](https://atcoder.jp/contests/abc385/submissions/60962773)。

---

## 作者：Even_If (赞：1)

upd：修改了错误的时间复杂度。

~赛时脑子傻了，卡了 40 min。~

# $\texttt{Solution}$

发现 $n \le 3000$，考虑 $O(n^2)$ 的 DP。

那么我们可以借鉴[这一题](https://leetcode.cn/problems/longest-arithmetic-subsequence/?envType=study-plan-v2&envId=dynamic-programming)的 DP 思路。

令 $f_{i, dif}$ 表示在第 $i$ 栋楼，以 $dif$ 栋楼为间隔时可以挂彩灯的楼数。如果遍历 $j$ 为间隔，那么就有：
$$f_{i + j, j} = \max_{i + j \le n}(f_{i + j, j}, f_{i, j} + 1)$$

最后对所有的 $f_{i, j}$ 取 max 即可。

注意初始化。开始时所有的 $f_{i, j}$ 都是 $1$，因为可以只在一栋楼上挂彩灯。

# $\texttt{Code}$

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 3005;

int a[N];

int n;

int ans = 1;

int f[N][N];

signed main() {
	cin >> n;

	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}

	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			f[i][j] = 1; // 初始化
		}
	}

	for (int i = 1; i <= n; i ++) {
		for (int j = 1; i + j <= n; j ++) {
			if(a[i] == a[i + j]) {
				f[i + j][j] = max(f[i][j] + 1, f[i + j][j]);
			}
		}
	}

	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			ans = max(ans, f[i][j]); // 对所有的 f[i][j] 取 max
		}
	}

	cout << ans;

    return 0;
}
```

---

## 作者：hytallenxu (赞：0)

## 前言
喵喵的，~~萌新写萌新题~~。

## 正文
就是一个基础的动态规划，~~差点没瞪出来~~。

这个数据范围就是给 $O(n^2)$ 的，那显然我们可以用一个二维的 $\text{dp}$。

设 $dp_{i,j}$ 为「下标为 $i$，和前一个相同数间隔为 $j$」能选的最多的数。

考虑转移。

显然：

假如 $h_{i-j}=h_i$ 就转移，转移式为 $dp_{i,j}=dp_{i-j,j}+1$。

注意初始化，因为每个数无论什么间隔都肯定有最小答案 $1$，所以我们大力将每个 $dp_{i,j}$ 设为 $1$ 即可。

## Code
如上所述，时空复杂度皆为 $O(n^2)$。

[赛时提交链接](https://atcoder.jp/contests/abc385/submissions/60966645)。

---

## 作者：Red_river (赞：0)

### 题目大意
本题给定了 $n$ 栋排成一列等间隔的建筑物，每栋建筑物有对应的高度，要求选择一些建筑物进行装饰，需同时满足所选建筑物**高度相等且等间隔排列**时最多能选择多少栋建筑物，并且规定只选**一栋建筑物**时也视为满足条件。
### 算法思路

暴力枚举：从起始建筑物往后确定另一个建筑物，以此来尝试寻找高度相同的建筑物对。

判断等间隔并计数：当找到高度相同的两个建筑物后，计算它们之间的间隔，然后从起始位置开始，按照这个间隔往后遍历，每遇到一个与起始所选的两个建筑物高度相同的就计算贡献，否则不同的就停止这个间隔的判断。

更新最大值：每次计算完一组等间隔且高度相同的建筑物数量后，更新全局的最大可选择的建筑物数量。

### CODE

```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define ll long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 50005
#define NO printf("No\n")
#define YES printf("Yes\n")

using namespace std;
int n,m,k,jk,ans,sum,num,cnt,tot;
int head[N],dis[N],vis[N],wis[N],f[N];

void read(int &x)
{
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

void write(int x)
{
	if(x==0){
		putchar('0');
		return;
	}
	if(x<0){
		x=-x;
		putchar('-');
	}
	char asd[201];int ip=0;
	while(x) asd[++ip]=x%10+'0',x/=10;
	for(int i=ip;i>=1;i--) putchar(asd[i]);
	return;
}

signed main()
{
	read(n);
	for(int i=1;i<=n;i++) read(dis[i]);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(dis[i]!=dis[j]) continue;//是否满足条件。
			int x=j-i,y=i;ans=1;//计算差距。
			while(y<=n){
				y+=x;
				if(dis[y]==dis[j]) ans++;//计算答案。
				else break;/退出。
			}
			sum=max(sum,ans);//更新。
		}
	}sum=max(1,sum);//一栋建筑也可以。
	wh(sum);
	return 0;
}
```

---

## 作者：linjinkun (赞：0)

简单动态规划。

设 $f_{i,j}$ 表示以 $i$ 结尾的距离为 $j$ 的选取方案最多能选几个数。状态转移方程也很简单，$f_{i,j} = \max(f_{i,j},\max(f_{i-j,j},f_{i-j,0})+1)$。

然后就……没了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e3+5;
int f[N][N];
int a[N];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		f[i][0] = 1;//初始化
	}
	int maxx = 1;//最小是1
	for(int i = 1;i<=n;i++)
	{
		for(int j = 1;j<i;j++)
		{
			if(a[i] == a[i-j])
			{
				f[i][j] = max(f[i][j],max(f[i-j][j],f[i-j][0])+1);	
			}
			maxx = max(maxx,f[i][j]);//取最小值
		}
	}
	printf("%d",maxx);
	return 0;
}
```

---

