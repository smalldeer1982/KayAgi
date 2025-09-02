# K Balanced Teams

## 题目描述

*题目名称：旗鼓相当的队友Ⅱ*  
您是本地大学的教练，有$n$位选手在你这里学习，并且已知第$i$位的能力值为$a_i$。  
现在您需要挑选出若干位选手组成至多$k$支队伍。众所周知，参赛的人数越多，你的大学获胜的概率越大。所以，你需要使得你选出的至多$k$支（至少$1$支）**非空**队伍的**总人数**最多。但是，你知道**每支**队伍中队员们的实力应当*差不多*，这意味着对于**任意**一支队伍，不应当存在两名实力值相差超过$5$的选手。所有的队伍都是相互独立的（这意味着我们不考虑来自两只不同队伍的选手的实力值差距）。  
可能有的选手不属于任何一支队伍。  
您的任务是求出满足以上要求的至多$k$（至少$1$）支**非空**队伍的**总人数**。  
**如果您是一名Python选手，您可以考虑在提交代码时选择`PyPy`而不是`Python`**。

## 说明/提示

对于所有数据，$1 \leq k \leq n \leq 5000, 1 \leq a_i \leq 10^9$。  
**如果您是一名Python选手，您可以考虑在提交代码时选择`PyPy`而不是`Python`**。

## 样例 #1

### 输入

```
5 2
1 2 15 15 15
```

### 输出

```
5
```

## 样例 #2

### 输入

```
6 1
36 4 1 25 9 16
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 4
1 10 100 1000
```

### 输出

```
4
```

# 题解

## 作者：米奇奇米 (赞：6)

## 题解- CF1133E K Balanced Teams

### 题面：
在$n$个人里分$k$段，并且保证这段中的 $maxh-minh\leq5$

### $Solution$
* $DP$的简单应用

* **状态：**$f[i][j]$表示前面$i$个人分成$j$段的最大贡献

* **转移：** $f[i][j]=max(f[i][j],f[pos][j-1]+i-pos)$ ,$pos$为对于这次转移是从哪里转移过来的位置，保证$h[pos]-h[i]\leq 5$(先对升高进行排序)，对于这次的贡献为$i-pos$

* **统计答案：** $ans=max(ans,f[n][1..k])$

* **时间复杂度：** $O(nk)$

### $Code$
```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int sum=0; char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) 
		sum=sum*10+(ch^48),ch=getchar();
	return sum;
}

const int maxn=5e3+5;
int n,m,h[maxn],f[maxn][maxn],ans;

int main() {
	n=read(),m=read();
	for ( int i=1;i<=n;i++ ) h[i]=read();
	sort(h+1,h+n+1);//排序
	f[1][1]=1;
	for ( int i=1;i<=n;i++ ) {
		int las=i;
		while(abs(h[las]-h[i])<=5 && las>=1) las--;
        //计算上次转移过来的位置las
		for ( int j=1;j<=m;j++ ) {
			f[i][j]=f[i-1][j];
			f[i][j]=max(f[i][j],f[las][j-1]+i-las);//转移
		}
	}
	for ( int i=1;i<=m;i++ ) ans=max(ans,f[n][i]);
	printf("%d\n",ans);
	return 0;
}
		
```


---

## 作者：封禁用户 (赞：2)

## 题解：CF1133E K Balanced Teams

看到题解区没人用**二分**优化 DP，来水一篇。

### 解题思路

首先，初始时要给 $a$ 数组排序，这点其他题解已经很详细了，不再赘述。

观察数据，可以开一个 $n^2$ 的数组，且是要考虑最优情况，所以思考 DP。不妨设 $dp_{i , j}$ 为前 $i$ 个人使用 $j$ 组。则转移状态为 $dp_{i , j} = \max(dp_{i - 1 , j} , dp_{i - tmp , j - 1} + i - tmp)$，其中 $tmp$ 为最大的使 $a_i - a_{tmp} > 5$ 的数。

如果在 DP 转移时暴力枚举 $tmp$，复杂度是 $O(n^2 k)$，显然不能通过。此时我们考虑优化：**二分**查找 $tmp$（因为给 $a$ 数组排过序，所以显然 $a_i - a_{tmp}$ 单调），复杂度 $O(n \log n k)$，足以通过此题。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n , k , a[5005] , tmp , dp[5005][5005] , ans;
int minp(int q)
{
	int l = 1 , r = n , mid , ans;
	while(l <= r)
	{
		mid = (l + r) / 2;
		if(q - a[mid] <= 5)
		{
			ans = mid;
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	return ans;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> a[i];
	}
	sort(a + 1 , a + n + 1);
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= k ; j++)
		{
			tmp = minp(a[i]) - 1;
			dp[i][j] = max(dp[i - 1][j] , dp[tmp][j - 1] + i - tmp);
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = 1 ; j <= k ; j++)
		{
			ans = max(ans , dp[i][j]);
		}
	}
	cout << min(ans , n);
	return 0;
}
```

---

## 作者：ncwzdlsd (赞：2)

显然，这道题可以用 DP 来解决。我们设计状态 $f(i,j)$ 表示对于前 $i$ 个人分成 $j$ 段能产生的最大总人数值。

显然，我们应该先将整个区间排序。接下来考虑如何进行状态转移，对于每一个点 $i$，我们考虑它能否入选队伍，如果不能入选，那么 $f(i,j)=f(i-1,j)$；如果能入选队伍，我们用一个变量来找到这队的第一个人，在寻找队首的过程中判断是否满足题目要求，即实力最大值与最小值的差即极差小于等于 $5$。如果能入选，假设找到的队首为 $p$，那么对最终结果产生的贡献为 $i-p$，于是乎我们就可以列出状态转移方程：$f(i.j)=\max(f(i-1,j),f(p,j-1)+(i-p))$，初始化 $f(1,1)=1$。

统计答案时不断更新最大值即可。整道题的时间复杂度为 $O(nk)$。

核心代码如下：

```cpp
  sort(a+1,a+n+1);
  f[1][1]=1;
  for(int i=1;i<=n;i++)
  {
      int p=i;
      while(p>=1&&a[i]-a[p]<=5) p--;
      for(int j=1;j<=k;j++) f[i][j]=max(f[i-1][j],f[p][j-1]+i-p);
  }
  int ans=-0x7f;
  for(int i=1;i<=n;i++) ans=max(ans,f[i][k]);
```

---

## 作者：3a51_ (赞：1)

考虑将原数组排序。

接下来我们可以对于每一个满足 $1\le i\le n$ 的数 $i$，都寻找一个 $\text{tmp}$ 为第一个满足 $\text{tmp}<i$，并且 $a_i-a_{\text{tmp}}>5$。显然对于每一个 $i$，$\text{tmp}$ 都是唯一的。

接下来运用 $\texttt{DP}$ 的思路，然后推出转移方程：

$$\text{dp}_{i,j}=\max(\text{dp}_{i-\text{tmp},j-1}+i-\text{tmp},\text{dp}_{i-1,j});$$

其中 $\text{dp}_{\text{tmp},j-1}+i-\text{tmp}$ 表示选择 $tmp$ 至 $i$ 这个区间，并且答案增加 $i-\text{tmp}$，$\text{dp}_{i-1,j}$ 表示不选择这个人进入队伍。

注意原题选择 $1\sim k$ 都行，所以最终还需要循环一遍，总共时间复杂度 $O(nk)$，不会超时。

$\text{Code:}$

```cpp
#include<bits/stdc++.h>
#define int long long
#define Tothetime_tolife using
#define AK namespace
#define IOI std
Tothetime_tolife AK IOI;
const int Mod1=998244353;
const int Mod2=1000000007;
int gcd(int a,int b){return __gcd(a,b);}
int lcm(int a,int b){return a*b/gcd(a,b);}
void read(int &x){x=0;char ch=' ';while(ch>'9' || ch<'0'){ch=getchar();}while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}return;}
void write(int x){if(x>9){write(x/10);}putchar(x%10+'0');return;}
void we(int x){write(x);printf("\n");}
void wk(int x){write(x);printf(" ");}
void w(int x){write(x);}
const int N=5005;
int n,k,ans,cnt,a[N],dp[N][N];
signed main(){
	read(n);read(k);
	for(int i=1;i<=n;i++) read(a[i]);
	sort(a+1,a+n+1);int tmp=1;
	for(int i=1;i<=n;i++){
		tmp=i;//从i向下枚举
		while(a[i]-a[tmp]<=5 && tmp>=1) tmp--;//记录tmp
		for(int j=1;j<=k;j++) dp[i][j]=max(dp[tmp][j-1]+i-tmp,dp[i-1][j]);//状态转移
	}
	for(int i=1;i<=k;i++){
		ans=max(ans,dp[n][i]);//记录答案
	}
	write(ans);
	return 0;
}
```

---

## 作者：Mine_King (赞：1)

这题我们首先对每位选手的实力值 $h$ 从小到大排序，这样每个队伍的选手都是连续的一段区间。  
然后再思考，如果一个队伍的选手是区间 $[l,r]$ 中的人，此时若 $h_l-h_{l-1} \le 5$，那么把区间扩展为 $[l-1,r]$ 显然是更优的，$h_{r+1}-h_r \le 5$ 时同理，所以选一个队伍时肯定选的是一个**无法继续向两边扩展**的区间。

接下来，我们用 DP 来解决这道题。

设 $dp_{i,j}$ 表示前 $i$ 个人，选出 $j$ 组的最多的人数，那么容易得出：

$$dp_{i,j}=\max(dp_{i-1,j},dp_{pos,j-1}+i-pos)$$

解释以下：  
$dp_{i-1,j}$ 表示不选第 $i$ 个人。  
$\max$ 函数的第二个参数中，我们设区间 $[pos+1,i]$ 为无法继续向左的，以 $i$ 结尾的区间，那么如果把 $i$ 选上，这是最优的选法，然后贡献的人数为 $i-(pos+1)+1=i-pos$。这里我们不需要考虑是否能向右扩展，这回在枚举之后的 $i$ 中解决。  
至于 $pos$，因为已经把 $h$ 从小到大排序，可以直接从 $i$ 开始枚举 $O(n)$ 找到，总复杂度为 $O(n^2)$。

代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,a[5005];
int ans,dp[5005][5005];
int max(int _x,int _y){return _x>_y?_x:_y;}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		int pos=i;
		while(a[i]-a[pos]<=5&&pos>=1) pos--;
		for(int j=1;j<=k;j++) dp[i][j]=max(dp[i-1][j],dp[pos][j-1]+i-pos);
	}
	for(int i=1;i<=k;i++) ans=max(ans,dp[n][i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：字如其人 (赞：1)

$f[i][j]$ 表示前 $i$ 个队员分成 $j$ 组的最大人数。

$f[i][j]=f[k][j-1]+i-k$，$k$ 表示 $k+1$ ~ $i$ 为新的一队 。

显然有 $0<=f[i+1][j]-f[i][j]<=1$ ，所以 $f[i][j]+w-i-(f[i+1][j]+w-(i+1))>=0$ ，即对于当前想要转移的 $f[i][j]$ ，若存在合法的 $k1$，$k2$ 且 $k1<k2$ 那么 $k1$ 一定比 $k2$ 优。

具体来说，可以对于每个状态 $i$ ，先求出最优的 $k$ ，再对于每个 $j$ 进行转移。

贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[5005],f[5005][5005];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);f[1][1]=1;
	for(int i=1;i<=n;i++){
		int p=i;
		while(a[i]-a[p]<=5&&p>=1)p--;
		for(int j=1;j<=k;j++)f[i][j]=max(f[i-1][j],f[p][j-1]+i-p);
	}
	printf("%d",f[n][k]);
	return 0;
}
```


---

## 作者：开始新的记忆 (赞：1)

## 题目大意：
现有n个人，每个人都有各自的能力值，要你把他们分成k组（每组人数不限），使得每组中任意两个人的能力值之差不超过5，问你最多可以把多少人分到组中。

## 大致思路：
动态规划。先排序，然后维护一个数组s，si表示如果让ai（已排序）新开一个组，那么最多可以放多少能力值比他大的人。然后我们在考虑状态转移方程的时候有以下两种情况：

（1）新开一组 。

（2）将这个人新开一组并将后si个人都放进去。

f[i][j]代表前i-1个人分到j组中最多可以分多少人，于是转移方程如下：

f[i+1][j]=max(f[i][j],f[i+1][j]);

f[i+s[i]][j+1]=max(f[i+s[i]][j+1],f[i][j]+s[i]);
最后再统计一下最大值即可。

code：

```
#include<bits/stdc++.h>
using namespace std;
int n,k,f[5010][5010],a[5010],s[5010],ans=0;

int main()
{	cin>>n>>k;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	sort(a+1,a+n+1);
	int t=1,tt=2;
	while(t<=n)
	{
		while(tt<=n && a[tt]-a[t]<=5)
			++tt;
		s[t]+=(tt-t);
		++t;
	}
	for(int i=1;i<=n;++i)
        for(int j=0;j<=min(i,k);++j)
		{
            f[i+1][j]=max(f[i][j],f[i+1][j]);
            f[i+s[i]][j+1]=max(f[i+s[i]][j+1],f[i][j]+s[i]);
        }
    for(int i=0;i<=k;++i)
    	ans=max(ans,f[n+1][i]);
    cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：rex_qwq (赞：1)

+ **题目简述**

对于每一件物品有一个数值 $a_i$，我们有 $k$ 个箱子，每个箱子中可以装任意件物品，但是在同一个箱子中的任意两个物品必须满足 $|a_i-a_j| \leq 5$。

+ **考虑动态规划**

由于本题需要求**总物件数的最大值**。

所以我们考虑 dp。

设 $dp_{i,j}$ 表示前 $i$ 个物件中，用了 $j$ 个箱子的最大答案。

显然答案为 $\max{dp_{i,j}}(1 \leq i \leq n,1 \leq j \leq k)$。

+ **转移**

有了状态和答案，我们来考虑转移。

由于我们设的状态，我们可以找到一个转移 $dp_{i,j}=\max{dp_{k,j}+1}(k \leq i,|a_i-a_k| \leq 5)$。

但是这显然有问题。

我们可以构造出一种 $hack$：
```
3 1
1 4 9
```

对于上面的转移由于 $9,4$ 可以放在同一个箱子里，$1,4$ 也能放在同一个箱子里，但是 $dp_{4,1}$ 会比 $dp_{9,1}$ 先更新于是我们就会把 $1,9$ 放在同一个箱子里。

于是我们又找到了一个不会有冲突的转移 $dp_{i,j}=\max{dp_{pos,j}+1}$，其中 $pos$ 表示在 $i$ 最后一个之前不能与 $a_i$ 放在一起的物品。

边界显然为 $dp_{1,1}=1$。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int  long long
#define kg putchar(' ')
#define endl puts("")
inline int read(){
    int vis=1,ans=0;
    char x=getchar();
    while(x<'0'||x>'9'){
        if(x=='-')vis=-1;
        x=getchar();
    }
    while(x>='0'&&x<='9'){
        ans=ans*10+x-'0';
        x=getchar();
    }
    return vis*ans;
}
inline void print(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
const int N=5090;
int dp[N][N];
int a[N];
int n=read(),k=read();
signed main(){
	for(int i=1;i<=n;i++)a[i]=read();
	dp[1][1]=1;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		int j=i;
		for(;abs(a[i]-a[j])<=5&&j>=1;j--){}
		for(int num=1;num<=k;num++){
			dp[i][num]=dp[i-1][num];//注意一定要写啊 
			dp[i][num]=max(dp[i][num],dp[j][num-1]+(i-j));//转移 
		}
	}
	int maxn=0;
	for(int i=1;i<=n;i++)for(int j=0;j<=k;j++)maxn=max(maxn,dp[i][j]);//答案 
	print(maxn);
    return 0;
}

```

---

## 作者：FireFy (赞：0)

### CF1133E K Balanced Teams
拿到题，先看数据范围。

$1\le k \le n \le 5000$

很明显我们可以使用 $O(n^{2})$ 的时间复杂度通过此题。

考虑 $dp$。

#### 设计状态
题意要求是在 $n$ 个人里选至多 $k$ 支队伍，使得队伍人员最大化。所以不妨设 $dp_{i,j}$ 表示在前 $i$ 个人里分 $j$ 段所可以取得的最大收益。

那么可得转移方程如下：

$dp_{i,j}=\max(dp_{i-1,j},\ dp_{pos,j-1}+i-pos)$

解释一下其中含义：

如果要取 $a_{i}$ 作为当前队伍 $j$ 的其中一员，那么当前队伍 $j$ 当中可能会有与 $a[i]$ 相差 $\gt5$ 的队员，设其位置为 $pos$，所以 $\max(dp_{i-1,j},\ dp_{pos,j-1}+i-pos)$ 就是在考虑加不加当前队员。

至于 $pos$ 的位置可以二分预处理，也可以现找，反正时间复杂度也不高。但是因为我懒，所以就直接暴力找了。

附上 $20$ 行代码，仅供参考。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[5010],dp[5010][5010],cut[5010];
signed main()
{
	int i,j,k,n,m,ans=-1;
	cin>>n>>k;
	for(i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	dp[1][1]=1;
	for(i=1;i<=n;i++)
	{
		int temp=i;
		while(abs(a[temp]-a[i])<=5&&temp>=1) temp--;	
		for(j=1;j<=k;j++) dp[i][j]=max(dp[i-1][j],max(dp[i][j],dp[temp][j-1]+i-temp));
	}
	for(i=1;i<=k;i++) ans=max(dp[n][i],ans);
	cout<<ans;
}
```

---

## 作者：Michael1234 (赞：0)

- 本题可以使用**二分**和**动态规划**的思路：

- 我们可以先将每个人的实力值**排序**，并通过**二分**找到**最小的** $pos_i$ 使得 $a_i-a_{pos_i} \le 5$。

- 接下来可以**设计动态规划状态**，$dp_{i,j}$ 表示在前 $i$ 个人中分成 $j$ 组所能选择的**最多人数**。

- 推出状态转移方程：（$dp_{1,1}=1$）

$$dp_{i,j}=\max(dp_{i-1,j},dp_{pos_i-1,j-1}+i-pos_i+1)$$

- 在转移时，我们可以选择**不选择**这个人，或者**新开**一组，并从最远可触及的人的状态转移。

- 所以最终答案为：

$$\sum_{i=1}^{k}{dp_{n,i}}$$

## CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n,k,l,r,res,ans,a[N],pos[N],dp[N][N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);//排序
	dp[1][1]=1;
	for(int i=1;i<=n;i++)
	{
		l=1,r=i,res=0;
		while(l<=r)
		{
			int mid=l+r>>1;
			if(a[i]-a[mid]<=5)
			{
				res=mid;
				r=mid-1;
			}
			else
			{
				l=mid+1;
			}
		}
		pos[i]=res;//找pos[i]
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=k;j++)
		{//转移
			dp[i][j]=max(dp[i-1][j],dp[pos[i]-1][j-1]+i-pos[i]+1);
		}
	}
	for(int i=1;i<=k;i++)
	{//统计答案
		ans=max(ans,dp[n][i]);
	}
	cout<<ans;
	exit(0);
}
```

---

## 作者：__LZH__ (赞：0)

# K Balanced Teams

## 题意

有一个长为 $n$ 的数组 $a$，你可以将他们分为至多 $k$ 组，不过每一组的（设这一组为数组 $p$）$\max(a_i)$ 与 $\min(a_i)$ 的差不能超过 $5$，求出满足以上要求的至多 $k$（最少 $1$）个非空组的元素总数。

## 思路

第一眼想到的就是动态规划，所以直接动态规划来做。

## 状态和转移

状态：$dp_{i,j}$ 表示在前 $i$ 个中选出 $j$ 组后那 $j$ 组的元素总量。

转移：$dp_{i,j}=\max(dp_{i-1,j},dp_{l,j-1}+i-l)$，其中上一段的结尾为 $l$，$dp_{l,j-1}$ 表示以 $l$ 结尾，选了 $j-1$ 段。

初始化：$dp_{1,1}=1$。

## 时间复杂度

时间：枚举 $i$ 的时间为 $O(k)$，求 $l$ 最多为 $O(n)$，枚举 $j$ 的时间为 $O(k)$，总时间复杂度为 $O(n(n+k))$，但实际跑不满，大概是 $O(nk)$ 左右。

code：

```cpp
#include<bits/stdc++.h>

using namespace std;

int n, k, a[5010], dp[5010][5010];

int main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> k;
  for(int i = 1; i <= n; i++){
  	cin >> a[i];
	}
	dp[1][1] = 1;
	sort(a + 1, a + 1 + n);
	for(int i = 1, l = 1; i <= n; i++, l = i){
		while(a[i] - a[l] <= 5 && l >= 1){
			l--;
		}
		for(int j = 1; j <= k; j++){
			dp[i][j] = max(dp[i - 1][j], dp[l][j - 1] + i - l);
		}
	}
	cout << *max_element(dp[n] + 1, dp[n] + 1 + n);
  return 0;
}
```

---

## 作者：__HHX__ (赞：0)

# 思路
先排序 $a$，此时对于 $a$ 数组的位置 $i$ 可以在 $a_{j - 1} - a_i \leq 5$ 的情况下区间 $[i, j)$ 下的人可以为一组，即在以位置 $i$ 为开始满足 $a_{j - 1} - a_i \leq 5$ 最大位置 $j - 1$。

我们记 $len_i$ 为 $j - i$，即以 $i$ 为队伍中最弱的能选人数的最大值。

很显然当我选择了区间 $[l, r]$，则不存在区间 $[a, b]$ 满足 $[a,b] \cap [l, r] \neq \emptyset$。

然后我们就可以设计状态与转移了。

状态：$(p, s, val)$ 表示从位置 $p - 1$ 结束下还剩余 $s$ 个团队的最大总人数 $val$。

转移：$(p, s, val)\rightarrow(p + len_p, s - 1, val + len_p)$。

易证：在 $p$ 下 $p \rightarrow p + len_p$ 的转移永远是最优的。

拓扑序即是：$s$ 从 $1$ 到 $k$，$p$ 从 $1$ 到 $n$。

核心代码：
```cpp
for (int i = 1; i <= n; i++) {
  for (int j = 1; j <= k; j++) {
    ans = max(ans, dp[i + len[i]][j] = max(dp[i + len[i]][j], (dp[i][j - 1] = max(dp[i][j - 1] , dp[i - 1][j - 1])) + len[i]));
  }
}
```

---

## 作者：AlicX (赞：0)

## Solution 

想到每一组一定是连续的一段数，所以先将 $a$ 数组排序，方便后续的处理。

定义 $f_{i,j}$ 表示将前 $i$ 个数分成 $j$ 组时最多的入选人数。

不难得到朴素方程 $f_{i,j}=\max\{f_{i-1,j},f_{i-1,j-1}+1,f_{p-1,j-1}+i-p+1\}$，时间复杂度为 $O(n^3)$。

考虑时间复杂度瓶颈在于枚举 $p$，于是得到以下两种处理方式：

1. 建立 $k$ 颗线段树，每次查询第 $j-1$ 颗线段树的 $(l,i)$ 之间的最大值，$l$ 为可以与 $i$ 一组的最远的点，二分或者预处理可以得到，时间复杂度为 $O(nk\log n)$，对于差值大于 $5$ 的情况也可以用。 

2. 观察到题目要求差值小于 $5$，于是考虑离散化，将原来的 $a$ 数组去重后，$l \geq i-5$，所以暴力时间复杂度即为 $O(Vn^2)$，$V$ 是差值 $5$，但是 $V$ 大了后便不再可用。

提供第二种写法的代码。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=5010; 
int n,k; 
int f[N][N]; 
int a[N],b[N],s[N]; 
signed main(){ 
	int num; scanf("%d%d",&num,&k); 
	for(int i=1;i<=num;i++) scanf("%d",&b[i]); 
	sort(b+1,b+num+1); 
	for(int i=1;i<=num;i++){
		if(b[i]==b[i-1]) s[n]++; 
		else a[++n]=b[i],s[n]=s[n-1]+1; 
	} int ans=0; 
	for(int i=1;i<=n;i++){ 
		for(int j=1;j<=k;j++){ 
			f[i][j]=max(f[i-1][j],f[i-1][j-1]+s[i]-s[i-1]); 
			for(int p=i-1;p>=1;p--){ 
				if(a[i]-a[p]<=5) f[i][j]=max(f[i][j],f[p-1][j-1]+s[i]-s[p-1]); 
				else break; 
			} ans=max(ans,f[i][j]); 
		} 
	} printf("%d\n",ans); return 0; 
} 
```


---

## 作者：YYen (赞：0)

### 思路：动态规划+双指针优化
 _约定 $ n $  个选手已经按照实力值从小到大排序。_ 

状态定义：

**$ dp[j][i] $ 表示前 $ 1 $ ~ $ i $ 个选手里面可以分成 $ j $ 组的最大挑选人数。**

状态转移：

情况①：不选第 $ i $ 名选手，则 $ dp[j][i] = dp[j][i - 1] $ ;

情况②：选第 $ i $ 名选手，则 $ dp[j][i] = dp[j - 1][m] + i - m $ ， $ m $ 是第 $ i $ 名选手前方第一个与自己实力差距超过 $ 5 $ 的选手下标。

那么情况①和情况②取 $ \max $ 即可。

### 代码
朴素 DP （时间复杂度 $ O(n^2k) $ ）
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int a[5005];
int dp[5005][5005];

int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int j = 1; j <= k; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            int m = i;
            while (a[i] - a[m] <= 5 && m >= 1) m--;
            dp[j][i] = max(dp[j][i - 1], dp[j - 1][m] + i - m);
        }
    }
    cout << dp[k][n] << endl;
    return 0;
}
```
 while 循环计算第 $ i $ 名选手前方第一个与自己实力差距超过 $ 5 $ 的选手下标这一过程可以通过双指针算法用 $ O(n) $ 的复杂度预处理出来进行优化。

双指针优化 DP （时间复杂度 $ O(nk) $ ）
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int a[5005];
int pre[5005]; // pre[i]代表第i名选手前方第一个与自己实力差距超过5的选手下标
int dp[5005][5005];

int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
	
    // 预处理pre
    int l = 0, r = 1;
    while (r <= n)
    {
        while (l + 1 < r && a[r] - a[l + 1] > 5) l++;
        pre[r] = l;
        r++;
    }
	
    for (int j = 1; j <= k; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            dp[j][i] = max(dp[j][i - 1], dp[j - 1][pre[i]] + i - pre[i]);
        }
    }
    cout << dp[k][n] << endl;
    return 0;
}
```


---

