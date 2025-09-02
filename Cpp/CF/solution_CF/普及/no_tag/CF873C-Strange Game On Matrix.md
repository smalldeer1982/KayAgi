# Strange Game On Matrix

## 题目描述

Ivan is playing a strange game.

He has a matrix $ a $ with $ n $ rows and $ m $ columns. Each element of the matrix is equal to either $ 0 $ or $ 1 $ . Rows and columns are $ 1 $ -indexed. Ivan can replace any number of ones in this matrix with zeroes. After that, his score in the game will be calculated as follows:

1. Initially Ivan's score is $ 0 $ ;
2. In each column, Ivan will find the topmost $ 1 $ (that is, if the current column is $ j $ , then he will find minimum $ i $ such that $ a_{i,j}=1 $ ). If there are no $ 1 $ 's in the column, this column is skipped;
3. Ivan will look at the next $ min(k,n-i+1) $ elements in this column (starting from the element he found) and count the number of $ 1 $ 's among these elements. This number will be added to his score.

Of course, Ivan wants to maximize his score in this strange game. Also he doesn't want to change many elements, so he will replace the minimum possible number of ones with zeroes. Help him to determine the maximum possible score he can get and the minimum possible number of replacements required to achieve that score.

## 说明/提示

In the first example Ivan will replace the element $ a_{1,2} $ .

## 样例 #1

### 输入

```
4 3 2
0 1 0
1 0 1
0 1 0
1 1 1
```

### 输出

```
4 1
```

## 样例 #2

### 输入

```
3 2 1
1 0
0 1
0 0
```

### 输出

```
2 0
```

# 题解

## 作者：Priori_Incantatem (赞：2)

题目：[CF873C Strange Game On Matrix
](https://www.luogu.com.cn/problem/CF873C)

双指针 - 贪心 - 前缀和

一道很简单的双指针题目，只不过是在矩阵上进行的，$O(n^2)$ 就可以搞定

对于这道题，题目已经给定了区间长度，没有平常的双指针那么复杂，直接枚举区间就可以了

枚举矩阵每一列，并维护出前缀和数组 $s$  
对于一个区间 $[l,r]$ （保证长度为 $k$），取这个区间的得分就为 $s_r-s_{l-1}$ （区间中 $\texttt1$ 的个数），那么为了获得这个区间而在这一列去掉的 $\texttt1$ 的个数就为 $s_{l-1}$（区间前 $\texttt1$ 的个数）

**AC代码**

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int Maxn=110;
int a[Maxn][Maxn],s[Maxn];
int ans,tot;
int n,m,k;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),m=read(),k=read();
	
	for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j)
	a[i][j]=read();
	
	for(int j=1;j<=m;++j)
	{
		int sum=0,cnt=0;
		for(int i=1;i<=n;++i)
		s[i]=s[i-1]+a[i][j];
		for(int i=1;i<=n;++i)
		{
			int tmp=s[i+k-1]-s[i-1];
			if(tmp>sum || (tmp==sum && s[i-1]<cnt))
			sum=tmp,cnt=s[i-1];
		}
		ans+=sum,tot+=cnt;
	}
	printf("%d %d\n",ans,tot);
	
	return 0;
}
```

---

## 作者：hellhell (赞：1)

### 题目描述

给你 $n\cdot m$ 的矩阵和 $k$，让你在每一列的里找 $i$ 最小的 $1$，从这个 $1$ 向下出发（包含），直到长度为	 $len=min(k,n-i+1)$。其中的 $1$ 的个数加到总分数中。

每一列找完之后，得到总分数。现在可以操作：把任意个 $1$ 变为 $0$。

现在想要总分数最大。求最大总分数和此时操作的最小次数。

### 思路分析

每列之间相互不影响，逐列统计答案即可。对于一列中的每个 $1$ 统计这个 $1$ 之前有多少个 $1$，以及这个 $1$ 往后走 $k$ 步有多少个 $1$，对于每一列中的所有 $1$ 找出包含 $1$ 的个数最大的即可。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 

using namespace std;

inline int read(){
	int res=0;
	int f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*f;
}

int n,m,k;
int a[105][105];
int sum[105][105];
int tot[105][105];
int ans_sum,ans_tot;

signed main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=read();
		}
	}
	for(int j=1;j<=m;j++){
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(!a[i][j])
				continue;
			tot[i][j]=cnt;
			cnt++;
			for(int l=0;i+l<=n && l<k;l++){
				sum[i][j]+=a[i+l][j];
			}
		}
	}
	for(int j=1;j<=m;j++){
		int Max=0;
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(!a[i][j])
				continue;
			if(sum[i][j]>Max){
				Max=sum[i][j];
				cnt=tot[i][j];
			}
		}
		ans_sum+=Max;
		ans_tot+=cnt;
	}
	printf("%lld %lld\n",ans_sum,ans_tot);
	return 0;
}
```


---

## 作者：DPair (赞：1)

绝对不是蓝题，肯定是恶评。

## 【思路】
既然是水题那我就随便讲讲。

首先我们把每一列单独来做（因为每一列的操作与结果互不干扰）。

注意到我们只能把$1$改成$0$，可以意识到我们要做的一定是把**每一列最前面的$1$删去**（删中间的$1$只可能使结果更劣）。

然后就做完了。

先把每一列最多有几个符合条件的$1$求出来，然后把**所有满足最大值的$1$的位置中最前面的**找出来。

然后删去这个$1$前的所有$1$，显然，这是在达到单列最优解的情况下删去最少$1$个数的解法，并可以推广到全局最优解。

那用一下前缀和，记录每一个$1$可以作出的最大贡献（就是后面有几个$1$），然后再用一下前缀和，记录每一个$1$前面有多少个$1$，然后对于每一列，求出其**能构成最大贡献的最前位置**，就搞定了。

## 【代码】
~~这种题需要放代码吗。。。~~
```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline void read(T &x)
{
    char c;
    x = 0;
    int fu = 1;
    c = getchar();
    while(c > 57 || c < 48)
    {
        if(c == 45)
        {
            fu = -1;
        }
        c = getchar();
    }
    while(c <= 57 && c >= 48)
    {
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x)
{
    if(x < 0)
    {
        putchar(45);
        x = -x;
    }
    if(x > 9)
    {
        fprint(x / 10);
    }
    putchar(x % 10 + 48);
}
int n, m, k, dp[110][110], pos[110], b[110][110], a[110][110], ans, ret;

void work(int col)
{
	for (register int i = n;i >= n - k + 1;i --)
	{
		dp[i][col] = dp[i + 1][col] + a[i][col];
		if(a[i][col] && dp[i][col] >= dp[pos[col]][col]) pos[col] = i;
	}
	for (register int i = n - k;i >= 1;i --)
	{
		dp[i][col] = dp[i + 1][col] + a[i][col] - a[i + k][col];
		if(a[i][col] && dp[i][col] >= dp[pos[col]][col]) pos[col] = i;
	}
	ans += dp[pos[col]][col];
}

int main()
{
	read(n);read(m);read(k);
	for (register int i = 1;i <= n;i ++)
	{
		for (register int j = 1;j <= m;j ++)
		{
			read(a[i][j]);
			b[i][j] = b[i - 1][j] + a[i][j];
		}
	}
	for (register int i = 1;i <= m;i ++)
	{
		pos[i] = 1;
		work(i);
		ret += b[pos[i] - 1][i];
	}
	fprint(ans);
	putchar(32);
	fprint(ret);
} 
```

---

## 作者：czh___ (赞：0)

这个题还是比较简单的，唯一的难点在于题意，我看翻译都看的一愣一愣的，只能看完之后自己猜意思，这个题的意思是给一个 `01` 矩阵，每一列，从上往下，遇到第一个 $1$ 开始，在长度不超过 $k$ 的区间里面，$1$ 的个数就是这一列的分数，总的分数就是每一列的分数相加，现在可以把任意个 $1$ 变成 $0$，求最大的分数以及相应的最小的转换次数。

这个题第一个标尺是分数，先要保证分数最大，分数一样大了，那么要求转换次数最小，这个题因为是定长的区间，因为按照贪心的思想，把区间长度选定为 $k$ ，不会让结果变坏，那么我们就一直采用定长的区间，那么每一列上面，这个其实就是区间定长的滑动窗口问题了，这个题分类在尺取法里面，其实我看不是太合适，因为这个题情况太特殊了，区间是定长的，所以比较简单，行数是 $n$，那么就有 $n-k+1$ 个长度为 $k$ 的区间，我们求出这些区间里面 $1$ 最多的，同样多显然要取靠上的，然后就是这一列的分数，然后我们把这个区间上面的 $1$ 都累加，就是这一列的转换次数，

感觉这个不是很难，要我看难度就是在于题意，贪心，定长区间滑动窗口，都很好想。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=101;
int a[N][N],n,m,k;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	int ans1=0,ans2=0;
	for(int i=1;i<=m;i++){
		int cur=0,Max=0,row;
		for (int j=1;j<=n;j++){
			if(j>k&&a[j-k][i]) 
				cur--;
			if(a[j][i]) 
				cur++;
			if(j>=k&&cur>Max)
				Max=cur,
				row=j;
		}
		ans1+=Max;
		for(int j=1;j<=row-k;j++)
			ans2+=a[j][i];
	}
	cout<<ans1<<' '<<ans2;
	return 0;
}
```

[改编于](https://blog.csdn.net/m0_73035684/article/details/128465443?ops_request_misc=&request_id=&biz_id=102&utm_term=Strange%20Game%20On%20Matrix&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-128465443.142^v100^pc_search_result_base5&spm=1018.2226.3001.4187)

---

## 作者：Y2y7m (赞：0)

~~我一开始读错题意然后干瞪眼瞪了20分钟。~~

因为要优先保证总分数最大，所以先处理出每一列的最大值是多少、位置在哪里，然后计算需要改掉多少个 $1$ 即可。由于 $n,m\leq100$，所以 $n^3$ 暴力计算即可。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
int n,m,k;
int a[110][110];
int f[110][110];
int mxp[110];
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(!a[i][j]) continue;
			for(int e=i,c=1;e<=n&&c<=k;e++,c++)
			{
				if(a[e][j]!=0)
					f[i][j]++;
			}
		}
	}
	int ans=0;
	for(int j=1;j<=m;j++)
	{
		for(int i=1;i<=n;i++)
		{
			if(f[i][j]>f[mxp[j]][j])
				mxp[j]=i;
		}
		for(int i=mxp[j]-1;i>=1;i--)
			ans+=a[i][j];
	}
	int sum=0;
	for(int j=1;j<=m;j++)
		sum+=f[mxp[j]][j];
	cout<<sum<<" "<<ans<<endl;
	return 0;
}
```

~~说实话这题真够水的。~~

---

## 作者：yszs (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF873C)

## $\texttt{Description}$
给定 $m$ 个 `01` 串，每个串长度为 $n$ 。

你可以进行无数次操作，可以将 `1` 改为 `0`， 给定一个 $k$ ，求每个串从上到下遇到的第一个 `1` 到向下 $k$ 个单位(不能超过 $n$ ）中 `1` 的个数和。
输出**个数和**和**操作次数**
## $\texttt{Solution}$

贪心 ~~（显然）~~

无论怎么进行操作，操作之后的串与原串 `1` 的个数和都是一样的
。我们先遍历一遍找到在 $k$ 长度的区间内`1`的个数和最大值和最大值之前`1`的个数，可以用前缀和优化。本题完
## $\texttt{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[105],ansi[105],a[105][105],tot,tot1;
int main()
{
	int n,m,p;
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[j][i];
		} 
	}
//	for(int i=1;i<=m;i++)
//	{
//		for(int j=1;j<=n;j++)
//		{
//			cout<<a[i][j]<<" ";
//		} 
//		cout<<endl;
//	}
	for(int i=1;i<=m;i++)
	{
		int cnt=0,chu;
		for(int j=1;j<=n;j++)
		{
			if(a[i][j]==1)
			{
				chu=j;
				break;
			}
		}
		for(int j=chu;j<=n;j++)
		{
			cnt=0;
//			cout<<"QWQ"<<i<<" "<<k<<" "<<p+k-1<<endl;
			for(int k=j;k<=min(p+j-1,n);k++)
			{
				if(a[i][k]==1)
				{
					cnt++;
//					cout<<i<<" "<<j<<" "<<k<<endl;
				}
			}
			if(ans[i]<cnt)
			{
				ans[i]=cnt;
				ansi[i]=j;
			}
		}
		for(int j=chu;j<=ansi[i]-1;j++)
		{
			if(a[i][j]==1)
			{
				tot++;
			}
		}
	}
	for(int i=1;i<=m;i++)
	{
		tot1+=ans[i];
	}
	cout<<tot1<<" "<<tot<<endl;
	return 0;
}
```


---

