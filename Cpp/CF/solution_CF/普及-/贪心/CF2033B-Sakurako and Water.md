# Sakurako and Water

## 题目描述

During her journey with Kosuke, Sakurako and Kosuke found a valley that can be represented as a matrix of size $ n \times n $ , where at the intersection of the $ i $ -th row and the $ j $ -th column is a mountain with a height of $ a_{i,j} $ . If $ a_{i,j} < 0 $ , then there is a lake there.

Kosuke is very afraid of water, so Sakurako needs to help him:

- With her magic, she can select a square area of mountains and increase the height of each mountain on the main diagonal of that area by exactly one.

More formally, she can choose a submatrix with the upper left corner located at $ (i, j) $ and the lower right corner at $ (p, q) $ , such that $ p-i=q-j $ . She can then add one to each element at the intersection of the $ (i + k) $ -th row and the $ (j + k) $ -th column, for all $ k $ such that $ 0 \le k \le p-i $ .

Determine the minimum number of times Sakurako must use her magic so that there are no lakes.

## 样例 #1

### 输入

```
4
1
1
2
-1 2
3 0
3
1 2 3
-2 1 -1
0 0 -1
5
1 1 -1 -1 3
-3 1 4 4 -4
-1 -1 3 0 -5
4 5 3 -3 -1
3 1 -3 -1 5```

### 输出

```
0
1
4
19```

# 题解

## 作者：Super_Cube (赞：2)

# Solution

每个对角线互不影响，分开考虑。记 $v_k$ 为 $\displaystyle\min_{i-j=k}a_{i,j}$，那答案为 $\sum\max(0,-v_i)$，因为若 $v_i\ge 0$ 则该对角线无需操作，而 $v_i<0$ 只需操作 $-v_i$ 次整个对角线上的值都会非负。

---

## 作者：lailai0916 (赞：2)

## 原题链接

- [洛谷 CF2033B Sakurako and Water](https://www.luogu.com.cn/problem/CF2033B)

## 解题思路

每个子矩阵的主对角线操作是相互独立的。

因此可以单独处理每条对角线。我们首先考虑每条对角线，找到该对角线上的最小值，然后将其提升到非负数，这样整条对角线上的所有值都变为非负。

将每个 $a_{i,j}$ 统计到其所在的对角线编号 $i-j+ n$。

对于每条对角线，如果最小值 $b_i$ 为负数，我们需要执行 $-b_i$ 次操作将其提升到非负值。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
const int N=505;
int a[N][N],b[N<<1];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=(n<<1)-1;i++)
		{
			b[i]=inf;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				cin>>a[i][j];
				b[i-j+n]=min(b[i-j+n],a[i][j]);
			}
		}
		int ans=0;
		for(int i=1;i<=(n<<1)-1;i++)
		{
			if(b[i]<0)ans-=b[i];
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：chenxi2009 (赞：1)

# 思路
每一次可以操作一个正方形对角线上的数字使其加上一。我们肯定希望一次可以操作尽可能多的数字，发现大正方形中位置行数与列数差相等（$i-j$ 为定值）的位置都可以放在同一个正方形的对角线上，所以它们可以一起操作。

整理一下，就是求大正方形每条左上到右下的斜线（$i-j=x$）上的数需要操作的次数的最大值之和。

时间复杂度 $O(\sum n^2)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[501][501],ans,x[2000];
int main(){
	scanf("%d",&T);
	while(T --){
		ans = 0;
		scanf("%d",&n);
		for(int i = 1;i < n << 1;i ++){
			x[i] = 0;
		}
		for(int i = 1;i <= n;i ++){
			for(int j = 1;j <= n;j ++){
				scanf("%d",&a[i][j]);
				if(a[i][j] < 0){
					x[i - j + n] = max(x[i - j + n],-a[i][j]);//防止出现负下标，x 数组整体上移 
				}
			}
		}
		for(int i = 1;i < n << 1;i ++){
			ans += x[i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：ZG10086 (赞：0)

# 思路
每次操作可以选择一个子矩阵区域，并对其主对角线上的元素全部增加 1。为实现最优解，我们将湖泊按其所在的对角线进行分组，找出每条对角线所需的最大增高量，因为一次操作可以同时作用于一整条对角线上的所有湖泊。

遍历矩阵时，每个位置的对角线可由 $c = i - j$ 唯一确定。为了便于处理，将这个值映射到数组索引范围 $0$ 到 $2n - 2$。对于每条对角线，我们记录其所需的最大增高量。最后，我们将所有对角线的最大增高量相加，即为最少操作次数。

CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[510][510];
int maxx[1010];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
    	memset(maxx,0,sizeof(maxx));
    	int n,ans=0;
    	cin>>n;
    	for(int i=1;i<=n;i++)
    	{
    		for(int j=1;j<=n;j++)
    		{
    			cin>>a[i][j];
			}
		}
		int num=2*n-1;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				int it=-a[i][j];
				int c=i-j;
				int id=c+n-1;
				maxx[id]=max(maxx[id],it);
			}
		}
		for(int i=0;i<=num;i++)
		{
			ans+=maxx[i];
		}
		cout<<ans<<'\n';
	}
}
```

---

## 作者：long_long__int (赞：0)

# 题目翻译
在与 Kosuke 的旅程中，Sakurako 和 Kosuke 发现了一个山谷，可以用大小为 $n\times n$ 的矩阵来表示，在第 $i$ 行和第 $j$ 列的交点处是一座高度为 $a_{i,j}$ 的山。如果 $a_{i,j}<0$，那么那里有一个湖。

Kosuke 非常怕水，所以 Sakurako 需要你的帮助：

- 凭借她的魔法，她可以绘制一块方形的山脉，并将该区域主对角线上的每座山的高度增加一。

更正式地说，她可以选择一个子矩阵，左上角位于 $(i,j)$，右下角位于 $(p,q)$，使 $p-i=q-j$。然后，她可以在第 $(i+k)$ 行和第 $(j+k)$ 列的交点处为每个地方的高度添加一，对于所有的 $k$，要使 $0\le k\le p-i$。

Sakurako 想要知道她必须使用魔法，使得不会有湖泊的最低次数。
# 题目解法
由于给你的矩阵是正方形的，所以可以直接扫一遍对角线，即 $(1,n);(1,n-1),(2,n)\dots$。对于每一个对角线，存一下它们的最小值，如果最小者为负数，就说明有湖，需要使用魔法填，把答案减去最小值，即把答案加上最小值的相反数。最后输出答案即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T; 
int n,a[505][505];
void work(){
	int ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&a[i][j]);
	for(int i=1;i<=2*n-1;i++){//扫对角线
		int minn=1000000;
		int q=n-i+1;
		for(int x=1,y=q;x<=n and y<=n;x++,y++){//扫对角线
			if(x<=0 or y<=0) continue;
			minn=min(minn,a[x][y]);
		}
		ans+=max(-minn,0);//把答案加上最小值的相反数
	}
	printf("%d\n",ans);
}
signed main(){
	scanf("%d",&T);
	while(T--) work();
	return 0;
}
```

---

## 作者：sintle (赞：0)

## 题目链接

- [洛谷 CF2033B Sakurako and Water](https://www.luogu.com.cn/problem/CF2033B)

## 解题思路

因为只需要不小于零就可以了，所以想到每次可以选中完整的对角线。

于是代价就变成了每条从左上到右下的斜线上最小的值的绝对值（如果最小值是整数则为零）。

之后只要遍历每条斜线找出代价并累积就好了。

## 参考代码

```cpp
#include <bits/stdc++.h>
#define N 505
using namespace std;

int T , n , a[N][N] , ans = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while(T--)
    {
        ans = 0;
        cin >> n;
        for(int i = 1 ; i <= n ; i++)
        {
            for(int j = 1 ; j <= n ; j++)
            {
                cin >> a[i][j];
            }
        }
        for(int i = 2 ; i <= n ; i++)
        {
            int minn = 0;
            for(int j = 1 ; j <= i ; j++)
            {
                minn = min(minn , a[i - j][n - j + 1]);
            }
            ans -= minn;
        }
        for(int i = 0 ; i < n ; i++)
        {
            int minn = 0;
            for(int j = 1 ; j <= n - i ; j++)
            {
                minn = min(minn , a[i + j][j]);
            }
            ans -= minn;
        }
        cout << ans << endl;
    }
    //system("pause");
    return 0;
}
```

---

## 作者：chatoudp (赞：0)

~~猪~~主对角线：正方形的左上角到右上角上的所有点。

我们发现修改一个小的正方形一定比比它的的正方形差，而且主对角线的所有点行列之差一定相同，因此我们可以把每条对角线按行列之差分组，求出需要加几次。每条对角线需要次数之和即为答案。

AC 代码：

```cpp
#include <bits/stdc++.h>
#define AC 0;
using namespace std;
int T,n,a[505][505],maxn[1005];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(maxn,0,sizeof(maxn));
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",&a[i][j]),maxn[i-j+n]=max(maxn[i-j+n],-a[i][j]);
		long long IAKIOI=0;
		for(int i=0;i<2*n;i++) IAKIOI+=maxn[i];
		printf("%lld\n",IAKIOI); 
	}
	return AC
}
```

---

## 作者：dutianchen1 (赞：0)

# CF2033B

~~听说考前发题解有利于攒rp。~~

### 思路简析

由于我们的操作只能操作主对角线，所以我们只需要统计每个矩阵中需要操作次数最多的那个元素即可。

最后累加就是答案。

```cpp
#include<bits/stdc++.h>
using namespace std; 
typedef long long ll;
const int N = 1e3+5;
inline ll read()
{
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
ll n;
ll a[N][N];
map<ll,ll> mp;
void solve(){
	mp.clear();
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=read();
			if(a[i][j]<0){
				mp[i-j]=(min(mp[i-j],a[i][j]));
			}
		}
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(mp[i-j]<0){
				ans+=(-mp[i-j]);
				mp[i-j]=0;
			}
		}
	}
	cout<<ans<<'\n';
}
signed main()
{
	ll T=read();
	while(T--){
		solve();
	}
	
	return 0;
}
```

---

## 作者：banglee (赞：0)

## CF2033B Sakurako and Water 题解
[洛谷传送门](https://www.luogu.com.cn/problem/CF2033B)

由于洛谷的 RemoteJudge 无法使用，所以建议前往 [这里](https://codeforces.com/problemset/problem/2033/B) 提交。

### 题目大意
通过对矩阵的主对角线元素进行增量操作来消除所有的湖泊（即矩阵中的负数）。每次操作可以选择一个子矩阵，并对其主对角线上的所有元素加 $1$。目标是找到最少的操作次数。

### 思路
考虑贪心。

贪心的策略是从右下角开始处理矩阵，逐行逐列地向上和向左检查。对于每个元素，如果它是负数，则需要进行一次操作以使其变为非负数。由于此操作会影响主对角线上的多个元素，所以需要确保在处理当前元素时，其右下方的元素已经被处理过了。

### Code
代码就不给了，过于简单。

---

## 作者：篮网总冠军 (赞：0)

本代码已经在原网站上通过本题，请放心食用。

题面说了，我们可以选择一个正方形，将其正对角线上所有数加上 $1$。我们肯定每次尽可能加更多的数，因为目的是让所有数都不小于 $0$。

于是我们贪心，枚举每条最长对角线上的最小的数 $x$，如果其小于 $0$，就加上 $-x$ 即可。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

int a[505][505];
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		long long cnt=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>a[i][j];
			}
		}
		for(int i=1;i<=n;i++){
			int x=1,y=i;
			int rt=0; 
			while(y<=n){
				rt=min(rt,a[x][y]);
				x++,y++;
			}
			cnt=cnt+0-rt;
		}
		for(int i=2;i<=n;i++){
			int x=i,y=1;
			int rt=0; 
			while(x<=n){
				rt=min(rt,a[x][y]);
				x++,y++;
			}
			cnt=cnt+0-rt;
		}
		cout<<cnt<<endl;
	}
	return 0;
}
```

---

## 作者：splendore (赞：0)

因为每次操作只能让左上至右下对角线上的值加上 $1$，所以在不同对角线上的操作互不干扰。

那么如果要让一条左上至右下对角线上的所有值非负，只要加上这条对角线上的最小值即可。

找出矩阵中每条左上至右下对角线上的最小值，它们的和就是答案。

```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1005;
int a[N][N];
void solve(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			a[i][j]=min(a[i][j],a[i-1][j-1]);
		}
	}
	int ans=0;
	for(int i=1;i<=n;++i){
		if(a[n][i]<0)ans+=-a[n][i];
	}
	for(int i=1;i<n;++i){
		if(a[i][n]<0)ans+=-a[i][n];
	}
	printf("%d\n",ans);
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

