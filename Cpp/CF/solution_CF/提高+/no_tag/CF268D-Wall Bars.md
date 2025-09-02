# Wall Bars

## 题目描述

Manao 正在一家建筑公司工作。最近这家公司要在一个儿童公园建造墙杆。Manao 受委托制定一项建造计划。

Manao 的正确设计描述如下：

- 建筑中心是一根高度为 $n$ 的主杆。
- 在高度 $1, 2, ..., n$ 处，正好有一根水平横杠从主杆上伸出。每根横杠都会向四个方向中的一个方向突出。
- 孩子可以从一根栏杆爬到另一根横杠，当且仅当它们之间的高度差不超过 $h$，并且它们突出在同一个方向。如果一个孩子在地上，他可以在 $1$ 到 $h$ 之间的高度爬到任何一个横杠上。在 Manao 的设计中，一个孩子应该能够在高度 $n - h + 1, n - h + 2, ..., n$ 爬到至少一个横杠，并且他从地面开始爬。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF268D/bc1fee4f00c4ecff99428a170ac845531c9eb3e6.png) 

上图是一个建造示例。

Manao 想知道，有多少种建筑满足要求？由于答案可能非常大，**所以对 $10^9 + 9$ 取模**。如果有这样的高度 $i$，则两种设计被认为是不同的，即这些设计中高度 $i$ 上的横杠不会朝同一方向突出。

## 样例 #1

### 输入

```
5 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
148
```

## 样例 #3

### 输入

```
4 3
```

### 输出

```
256
```

## 样例 #4

### 输入

```
5 2
```

### 输出

```
376
```

# 题解

## 作者：是个汉子 (赞：4)

### Solution

给我的感觉就是很暴力的计数DP。

~~因为再暴力，这也算个DP~~

那么我们可以显然的构造出一个状态 $f_{i,a,b,c,1/0}$ ，表示现在是第 $i$ 个踏板放在某个面上，其它三个面的下一个踏板距离这个的距离为 $a,b,c$ ，当前这个踏板是/否能从地面到达。

在此我们是优化了一维，也就是将 $i$ 踏板所在面下一个距离这个踏板的距离优化成了 $1/0$ ，因为能到达的时候距离是 $<h$ 的，不能时是 $\geq h$ 的，也是两个状态。

再思考另一个问题，开了五维数组，那么空间复杂度是 $O(n\times n\times n\times n\times 2)=O(n^4)$ ，显然是会炸的。我们还得优化空间，发现题目中说明 $h\leq \min(n,30)$ ，所以可以将 $a,b,c$ 三维的空间变成30，当距离 $\geq h$ 时，赋为 $h$ 。此时为 $O(2\cdot 30^3\cdot n)$ ，完全可以。

再看时间复杂度。发现我们在优化空间的时候，把时间复杂度也降低了。本来要枚举五维，复杂度是 $O(n^5)$ ，现在也变成了 $O(2\cdot 30^3\cdot n)$ 。

现在终于到了最重要的转移方程：
$$
f_{i+1,a+1,b+1,c+1,1/0}+=f_{i,a,b,c,1/0}
$$
这个是还在本来的那个面上
$$
f_{i+1,1/h,b+1,c+1,[a<h]}+=f_{i,a,b,c,1/0}
$$
这是换到另一个面
$$
f_{i+1,a+1,1/h,c+1,[b<h]}+=f_{i,a,b,c,1/0},
f_{i+1,a+1,b+1,1/h,[c<h]}+=f_{i,a,b,c,1/0}
$$
这两个同理。

答案随便求求即可。

### 代码

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int mod=1e9+9;
int n,h,ans;
int f[1010][31][31][31][2];

#define add(i,a,b,c,j,val) (f[i][min(a,h)][min(b,h)][min(c,h)][j]+=val)%=mod;
ll read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
	return x*f;
}

int main(){
	n=read();h=read();
	f[1][1][1][1][1]=4;
	for(int i=1;i<=n;i++)
		for(int a=1;a<=h;a++)
			for(int b=1;b<=h;b++)
				for(int c=1;c<=h;c++)
					for(int j=0;j<2;j++)
						if(f[i][a][b][c][j]){
							add(i+1,a+1,b+1,c+1,j,f[i][a][b][c][j]);
							int d=1;if(j==0) d=h;
							add(i+1,d,b+1,c+1,a<h,f[i][a][b][c][j]);
							add(i+1,a+1,d,c+1,b<h,f[i][a][b][c][j]);
							add(i+1,a+1,b+1,d,c<h,f[i][a][b][c][j]);
						}
	for(int a=1;a<=h;a++)
		for(int b=1;b<=h;b++)
			for(int c=1;c<=h;c++)
				for(int j=0;j<2;j++)
					if(j||a<h||b<h||c<h) ans=(ans+f[n][a][b][c][j])%mod;
	printf("%d\n",ans);
}
```



---

## 作者：封禁用户 (赞：3)

DP[I][J][K][L][M]表示当前高度为I，四个方向上离I最近的横杠与I的差为J,K,L,M，其中J,K,L,M=0的话，表示差值大于了h，这样的话J,K,L,M的范围是0-30, 复杂度为9亿，需要继续优化，发现其中一个杆子的差值必然为0/1，那么只要 1000x30x30x30x2的复杂度就够啦

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long dp[1001][31][31][31][2];
int mod=1e9+9; 
int n,h,ans;
int main()
{
	cin>>n>>h;
	dp[1][1][1][1][1]=4;
	if(h==1)
	{
		cout<<4<<endl;
		return 0;
	}
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=h;j++)
		{
			for(int k=1;k<=h;k++)
			{
				for(int l=1;l<=h;l++)
				{
					for(int _=0;_<2;_++)
					{
						if(dp[i-1][j][k][l][_])
						{
							dp[i][min(j+1,h)][min(k+1,h)][min(l+1,h)][_]=(dp[i][min(j+1,h)][min(k+1,h)][min(l+1,h)][_]+dp[i-1][j][k][l][_])%mod;
							long long d=_==0?h:1;
							dp[i][d][min(k+1,h)][min(l+1,h)][j<h?1:0]=(dp[i][d][min(k+1,h)][min(l+1,h)][j<h]+dp[i-1][j][k][l][_])%mod;
							dp[i][min(j+1,h)][d][min(l+1,h)][k<h?1:0]=(dp[i][min(j+1,h)][d][min(l+1,h)][k<h]+dp[i-1][j][k][l][_])%mod;
							dp[i][min(j+1,h)][min(k+1,h)][d][l<h?1:0]=(dp[i][min(j+1,h)][min(k+1,h)][d][l<h]+dp[i-1][j][k][l][_])%mod;
						}
					}
				}
			}
		}
	}
	for(int i=1;i<=h;i++)
		for(int j=1;j<=h;j++)
			for(int k=1;k<=h;k++)
				for(int l=0;l<2;l++)
					if(l||i<h||j<h||k<h)
						ans=(ans+dp[n][i][j][k][l])%mod;
	cout<<ans<<endl;
	return 0;
}


```

是不是感觉很丑很繁琐？这边再放一个rng_58神仙的代码，其实原理是一样的。

code:

```cpp
#include<bits/stdc++.h>
#define mod 1000000009
using namespace std;
int h,s,n;
vector<int>state[10000];
map<vector<int>,int>mp;
int trans[10000][4];
int dp[1010][10000];
int get_state(vector<int>v)
{
	if(mp.find(v)!=mp.end())
		return mp[v];
	state[s]=v;
	mp[v]=s;
	s++;
	return s-1;
}
void func(int id)
{
	for(int i=0;i<4;i++)
	{
		vector<int>w=state[id];
		for(int j=0;j<4;j++)
		{
			if(j==i)
				w[j]=((w[j]==h)?h:0);
			else
				w[j]=min(w[j]+1,h);
		}
		sort(w.begin(),w.end());
		trans[id][i]=get_state(w);
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>h;
	vector<int>init;
	for(int i=0;i<4;i++)
		init.push_back(0);
	get_state(init);
	int pos=0;
	while(pos<s)
	{
		func(pos);
		pos++;
	}
	dp[0][0]=1;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<s;j++)
		{
			for(int k=0;k<4;k++)
			{
				int j2=trans[j][k];
				dp[i+1][j2]+=dp[i][j];
				if(dp[i+1][j2]>=mod)
					dp[i+1][j2]-=mod;
			}
		}
	}
	int ans=0;
	for(int i=0;i<s;i++)
	{
		bool good=false;
		for(int j=0;j<4;j++)
			if(state[i][j]!=h)
				good=true;
		if(good)
		{
			ans+=dp[n][i];
			if(ans>=mod)
				ans-=mod;
		}
	} 
	cout<<ans<<endl;
	return 0;
}

```


---

## 作者：Katz (赞：1)

五维动态规划。

首先我们可以想到用 $f_{i,a,b,c,d}$ 来表示高度为 $i$ 到四个方向的高度差值分别为 $a$，$b$，$c$，$d$ 时的方案数，如果高度差超过了 $h$ 就将其设为 $h$，因为都是无法跳上去的状态。但是 $O(n\times h^4)$ 的时间复杂度显然无法接受。需要优化。

我们可以通过将一维转化为 $0/1$ 两个值，即为 $f_{i,a,b,c,0/1}$，该维表示所选的该面可不可以到达，其余的即为其他各个方向到 $i$ 的高度差。这样的时间和空间复杂度显然是可以接受的。

附上可读性不良好的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+9;
int n,h,ans,t,tmp,f[1010][40][40][40][2];
int main()
{
	cin>>n>>h;
	f[1][1][1][1][1]=4;//记得初始化
	for(int i=2;i<=n+1;i++)
	{
		for(int a=2;a<=h+1;a++)
		{
			for(int b=2;b<=h+1;b++)
			{
				for(int c=2;c<=h+1;c++)
				{
					for(int j=0;j<2;j++)
					{
						tmp=f[i-1][a-1][b-1][c-1][j];
						if(tmp==0) continue;
						(f[i][min(a,h)][min(b,h)][min(c,h)][j]+=tmp)%=mod;
						if(j!=0) t=1; else t=h;
						(f[i][min(t,h)][min(b,h)][min(c,h)][a<=h]+=tmp)%=mod;
						(f[i][min(a,h)][min(t,h)][min(c,h)][b<=h]+=tmp)%=mod;
						(f[i][min(a,h)][min(b,h)][min(t,h)][c<=h]+=tmp)%=mod;
					}
				}
			}
		}
	}
	for(int a=1;a<=h;a++)
	for(int b=1;b<=h;b++)
	for(int c=1;c<=h;c++)
	for(int i=0;i<2;i++)
	if(a<h||b<h||c<h||i==1)
	(ans+=f[n][a][b][c][i])%=mod;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：tribool4_in (赞：0)

CF 黑题中评分最低的一题。

考虑 dp。首先一眼列出 $dp_{i,a,b,c,d}$ 表示当前位于高度 $i$，四根杆子距离当前位置的距离（差值）分别为 $a$、$b$、$c$、$d$。注意到如果一根杆子之前的某个位置差大于 $h$，则这根杆子不再能爬到，为避免特判可以直接令其为 $h$。时间复杂度 $\mathcal O(nh^4)$。有点危险。

发现然后你发现由于每个位置必须连出一根杆子，所以必有一维为 $i$，所以可以直接砍掉一维。但是你注意到这样无法表示出这根杆子当前能否到达，所以你再增加一维 $0/1$ 来表示，于是列出 $dp_{i,a,b,c,0/1}$ 表示当前位于高度 $i$，其他三根杆子距离当前位置的距离（差值）分别为 $a$、$b$、$c$ 且当前 $i$ 所在杆子能否爬到。

转移时分讨放在哪个杆子上即可。具体见代码。

```cpp
dp[0][0][0][0][0] = 1;
for (int i = 0; i < n; i++) {
  for (int a = 0; a <= k; a++) {
    for (int b = 0; b <= k; b++) {
      for (int c = 0; c <= k; c++) {
        // At i
        (dp[i + 1][min(k, a + 1)][min(k, b + 1)][min(k, c + 1)][0] += dp[i][a][b][c][0]) %= mod;
        (dp[i + 1][min(k, a + 1)][min(k, b + 1)][min(k, c + 1)][1] += dp[i][a][b][c][1]) %= mod;
        // At a
        (dp[i + 1][1][min(k, b + 1)][min(k, c + 1)][a == k] += dp[i][a][b][c][0]) %= mod;
        (dp[i + 1][k][min(k, b + 1)][min(k, c + 1)][a == k] += dp[i][a][b][c][1]) %= mod;
        // At b
        (dp[i + 1][min(k, a + 1)][1][min(k, c + 1)][b == k] += dp[i][a][b][c][0]) %= mod;
        (dp[i + 1][min(k, a + 1)][k][min(k, c + 1)][b == k] += dp[i][a][b][c][1]) %= mod;
        // At c
        (dp[i + 1][min(k, a + 1)][min(k, b + 1)][1][c == k] += dp[i][a][b][c][0]) %= mod;
        (dp[i + 1][min(k, a + 1)][min(k, b + 1)][k][c == k] += dp[i][a][b][c][1]) %= mod;
      }
    }
  }
}
int ans = 0;
for (int a = 0; a <= k; a++) {
  for (int b = 0; b <= k; b++) {
    for (int c = 0; c <= k; c++) {
      if (a < k || b < k || c < k) (ans += dp[n][a][b][c][1]) %= mod;
      (ans += dp[n][a][b][c][0]) %= mod;
    }
  }
}
cout << ans << '\n';
```

---

## 作者：_segmenttree (赞：0)

## 思路

首先我们先思考最暴力的 dp 状态 $f_{i,j1,j2,j3,j4}$ 来表示现在要放的高度为 $i$ ,距离第 $i$ 面上一次放差 $ji$ ，这样做空间复杂度 $O(n^5)$ 。接下来是第一个优化，其实我们放高度为 $i$ 的条时，高度 $1$ 到 高度 $i-h-1$ 其实是一样的。那么我们的后四维的范围就可以缩小为 $h$ ，那么这样的空间复杂度已经缩小到 $O(n\times h^4)$ ，但这样还是不能够过掉这题。

![](https://cdn.luogu.com.cn/upload/image_hosting/jcwo8qfn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们接下来考虑第二个优化，我们发现如果当前放的这个面的状态其实只需要知道上次放的是否大于等于 $h$ 就可以了，那么我们就可以把后四维中一维优化,那么现在的时间复杂度就是 $O(h^3\times n)$ 。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,h,dp[1010][31][31][31][2],mo=1e9+9; 
signed main() {
	cin>>n>>h;
	dp[1][1][1][1][1]=4; 
	for(int i=1;i<=n;i++) 
		for(int j1=1;j1<=h;j1++)
		    for(int j2=1;j2<=h;j2++)
		        for(int j3=1;j3<=h;j3++)
		            for(int k=0;k<=1;k++) {
		            	int nj1=min(j1+1,h),nj2=min(j2+1,h),nj3=min(j3+1,h);
		            	dp[i+1][nj1][nj2][nj3][k]=(dp[i+1][nj1][nj2][nj3][k]+dp[i][j1][j2][j3][k])%mo;
		            	int jl=1;
		            	if(k==0) jl=h;
		            	dp[i+1][jl][nj2][nj3][j1<h]=(dp[i+1][jl][nj2][nj3][j1<h]+dp[i][j1][j2][j3][k])%mo;
						dp[i+1][nj1][jl][nj3][j2<h]=(dp[i+1][nj1][jl][nj3][j2<h]+dp[i][j1][j2][j3][k])%mo;
						dp[i+1][nj1][nj2][jl][j3<h]=(dp[i+1][nj1][nj2][jl][j3<h]+dp[i][j1][j2][j3][k])%mo;
					}
	int ans=0;
	for(int j1=1;j1<=h;j1++)
	    for(int j2=1;j2<=h;j2++)
	        for(int j3=1;j3<=h;j3++)
	            for(int k=0;k<=1;k++) 
	                if(j1<h||j2<h||j3<h||k)
	                    ans=(ans+dp[n][j1][j2][j3][k])%mo;
	cout<<ans;
	return 0;
}
```

---

