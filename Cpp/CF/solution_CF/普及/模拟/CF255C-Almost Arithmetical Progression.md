# Almost Arithmetical Progression

## 题目描述

先给出一个整数 $n$ ,再给出一个有 $n$ 个元素的序列 $b$。

现在要你求序列 $b$ 中最长的子序列，满足隔位的两个数相等，问这个最长的子序列的长度是多少。

## 样例 #1

### 输入

```
2
3 5
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
10 20 10 30
```

### 输出

```
3
```

# 题解

## 作者：tuzhewen (赞：12)

其实这道题写很好写，主要在想。

从那个$a_i=a_{i-1}+(-1)^{i+1}\times q$，可以比较明显的得出我们最后从$a$里面选出来的子序列，**下标是奇数的数字相同，下标是偶数的数字相同**，形如: `5 9 5 9` 或者 `2 3 2 3 2` 这样的

那么我们就开始设计转移方程：令 $dp_{i,j}$ 表示在第 $i$ 个位置前面的数字是 $a_j$ 的答案，那么比较容易可以得出转移方程：$dp_{i,a_j}=dp_{j,a_i}+1$（因为最终选出来的序列是循环的，所以得出这样一个方程）

然后要注意的就是值域是$10^6$，离散化一下就好。

其他就没啥了，详见代码/cy
```
#include<bits/stdc++.h>
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define D(i,r,l) for(register int i=r;i>=l;i--)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
#define fi first
#define se second
const int INF=0x7f7f7f7f,N=4005;
using namespace std;
int n;
int a[N],b[N];
int dp[N][N],ans;
int main() {
	scanf("%d",&n);
	if(n<=2) return printf("%d\n",n),0;
	F(i,1,n) scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+1+n);
	int m=unique(b+1,b+1+n)-b;
	F(i,1,n) a[i]=lower_bound(b+1,b+1+m,a[i])-b;
	F(i,1,n) {
		F(j,i+1,n) {
			dp[j][a[i]]=dp[i][a[j]]+1;
			ans=max(ans,dp[j][a[i]]);
		}
	}
	printf("%d\n",ans+1);
	return 0;
}
```
~~反手留赞~~

---

## 作者：wxzzzz (赞：4)

### 思路

动态规划。

前置：[离散化](https://oi-wiki.org/misc/discrete/)。

#### 状态设置

在本题中，要表示一个状态有两样不可缺少的东西：子序列有多长、隔位相等的数是什么。

因此，设 $f_{i,j}$ 为在 $i$ 之前，隔位相等的数为 $j$ 的最长子序列的长度。

#### 状态转移

枚举 $i,j$，当前状态为 $f_{i,b_j}$，上一个状态为 $f_{j,b_i}$。

显然 $f_{i,b_j}=f_{j,b_i}+1$。

#### 小细节

- 因为枚举的是 $i$ 之前的子序列，所以最后答案要加 $1$。

- 因为 $b_i$ 值域较大，所以先用 map 离散化。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, cnt, ans, b[4005], f[4005][4005];
map<int, int> dis;
int main() {
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> b[i];

		if (!dis[b[i]]) {
			dis[b[i]] = ++cnt;
		}
	}

	for (int i = 1; i <= n; i++) {
		b[i] = dis[b[i]];
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			f[i][b[j]] = f[j][b[i]] + 1;
			ans = max(ans, f[i][b[j]]);
		}
	}

	cout << ans + 1;
	return 0;
}
```

---

## 作者：XL4453 (赞：2)

### 解题思路：

动态规划。

由于 $b$ 数组的范围很大且只需要考虑相等关系，考虑先将其整个 $b$ 数组离散化处理。

然后设 $f_{i,j}$ 表示到 $i$ 的位置之前的相等数（离散化后）为 $j$ 的最长长度。可以发现，两个数中的另一个就是当前 $i$ 表示的 $b_i$。

由此状态转移就很显然了：$f_{i,a_j}=\max(f_{j,b_i})$。

总复杂度是 $O(n^2)$ 的，可以通过本题。

---
### 代码:

```cpp
#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;
int n,a[4005],f[4005][4005],cnt,ans;
map <int,int> m;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(m[a[i]]==0)m[a[i]]=++cnt;
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<i;j++)
	ans=max(ans,f[i][m[a[j]]]=max(f[i][m[a[j]]],f[j][m[a[i]]]+1));
	printf("%d\n",ans+1);
	return 0;
}
```


---

## 作者：Kotobuki_Tsumugi (赞：1)

令 $dp_{i,j}$ 表示第 $i$ 个数、且前一个数是第 $j$ 个的最大答案。

转移方程如下。

$$dp_{i,j}=\max \limits_{j<i,k<j,a_i=a_j} dp_{j,k}+1$$

直接转移是 $O(n^3)$ 的。

考虑优化：预处理出数组 $f_{i,j}=\max \limits_{k<j,a_i=a_k} k$。

把转移方程化为：$dp_{i,j}=dp_{j,f_{i,j}}+1$。

为什么这样转化是正确的？对于任意 $j<k$，有 $dp_{i,j}\le dp_{i,k}$。

因此我们只要找一个最大的，且与 $a_i$ 相等的 $a_k$ ，把这个 $k$ 存入一个数组即可。这便是上述数组 $f$ 的实质。

这样转移就是 $O(n^2)$ 的了。可以通过。 

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 4e3+10;
int a[N],f[N][N],dp[N][N],n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i = 1;i<=n;i++){
		cin>>a[i];
		for(int j = 1;j<i-1;j++){
			if(a[i] == a[j]) f[i][j+1] = j;
			else f[i][j+1] = f[i][j];
		}
	}
	if(n == 1){
		cout<<1<<endl;
		return 0;
	}
	dp[1][0] = 1;
	dp[2][1] = 2,dp[2][0] = 1;
	int ans = 2;
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<i;j++){
			dp[i][j] = 2;
			dp[i][j] = max(dp[i][j],dp[j][f[i][j]]+1);
			ans = max(dp[i][j],ans);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：C6H14 (赞：1)

## 一点废话

[题目传送门](https://www.luogu.com.cn/problem/CF255C)

[My blog](https://www.luogu.com.cn/blog/128433/#)

分班考期间作死来机房摸大鱼……~~我可真勇~~

## 思路

最原始的想法是定义 $f(i,j)$ 为 $1$ 到 $i$ 个数中，上一个数为 $a_j$ 的最长子序列，转移时枚举 $a_{j-1}$，这样做时间复杂度为 $O(n^3)$，~~喜提TLE~~。

再看看题目，条件为 $\forall 1 \leqslant i \leqslant n-2,a_i=a_{i+2}$。

那么 $a_1=a_3= \dots =a_{2i+1}$，$a_2=a_4= \dots a_{2i}$，也就是奇数位和偶数位各选一个数凑成子序列。

那么定义 $f(i,j,0/1)$ 表示数列奇数位为 $a_i$，偶数位为 $a_j$，当前为偶数或者奇数位的最长子序列长度，时间复杂度为 $O(n^2)$。

为了枚举方便，离散化一下即可。

## 代码
```cpp
int n,a[4005],b[4005],c[4005],f[4005][4005][2],ans;
int main()
{
	n=read();
	for (int i=1;i<=n;++i)
		a[i]=b[i]=read();
	sort(b+1,b+1+n);
	for (int i=1;i<=n;++i)
		c[i]=lower_bound(b+1,b+1+n,a[i])-b;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
		{
			int tmp1=f[c[i]][j][1],tmp2=f[j][c[i]][0];
			f[c[i]][j][0]=tmp1+1,f[j][c[i]][1]=tmp2+1;
		}
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			ans=max(ans,f[i][j][0]),ans=max(ans,f[i][j][1]);
	write(ans);
	return 0;
}

```


---

## 作者：_Weslie_ (赞：0)

## Solution CF255C

### Idea

隔位相等，启示我们 dp（显然枚举两个数算答案是过不去的）。

我们设 $dp_{i,j}$ 表示最后一个数是 $a_i$，倒数第二个数是 $j$ 可以达到的序列长度的最大值。

则显然有：$dp_{i,a_j}=max(dp_{i,a_j},dp_{j,a_i}+1)$。

解释一下转移：如果序列形如 $\{\cdots,a_i,a_j,a_i\}$，则必须从 $\{\cdots,a_i,a_j\}$ 的状态转移来，另外加 $1$ 表示加入 $a_i$。

然后统计最大值即可（注意不是最后一个是 $a_n$ 的最大值，样例二可以启示这一点）。因为我们并没有初始化序列的第一个数的 $dp$，因此最后统计出的最大值要加 $1$ 再输出。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=4005;
int n,a[N],b[N],dp[N][N];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    int len=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            dp[i][a[j]]=max(dp[i][a[j]],dp[j][a[i]]+1);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            ans=max(ans,dp[i][a[j]]);
        }
    }
    printf("%d",ans+1);
}
```

---

## 作者：Error_Eric (赞：0)

### 前言

估——值——

### 正文

题目描述：先给出一个整数 $n$ ,再给出一个有 $n$ 个元素的序列 $b$。求序列 $b$ 中最长的子序列，满足隔位的两个数相等，问这个最长的子序列的长度是多少。

不难发现这是一个dp。

首先因为 $n\le10^4$ 但是 $b_i\le 10^6$ ，可以考虑离散化。

因为刚开始把数据范围看错了，又不会用STL，所以我采用了朴素的排序离散化方法。

然后就考虑 $f_{i,j,k}$ 表示到了第 $i$ 位时最后两位是 $j,k$ 的最长长度。

但是这样子的话时间空间复杂度均为 $O(n^3)$ ，显然会 $\color{purple}\texttt{MLE}\color{black}/\color{purple}\texttt{TLE}$ 。

然后不难发现最外层枚举 $i$ 可以剪掉第一维。

这样子的话就可以写出方程:

$$ f_{a_i,a_j}=\max\{f_{a_j,a_i}+1,f_{a_i,a_j}\} $$ 

但是要注意后效性，所以应当将当前的 $f_{i,j}$ 存在另一者数组中，然后赋值过去。

然后就可以开始写代码了。

P.S:原有的那篇题解看不懂...

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
#define il inline
#define rei register int
const int size=4005;
int n,m,ans=-1,a[size],f[size][size],g[size][size];
il void readln(int &I){//快读
	I=0;char C=getchar();
	while(!isdigit(C))C=getchar();
	while( isdigit(C))I=I*10+C-'0',C=getchar();
}
struct y{int x,d;}b[size];//朴素的结构体排序
bool cmp(y ya,y yb){return ya.x<yb.x;}
il void li(){//朴素的离散化
	for(rei i=1;i<=n;i++)b[i].x=a[i],b[i].d=i;
	sort(b+1,b+n+1,cmp),b[0].x=-1;
	for(rei i=1;i<=n;i++){
		if(b[i].x!=b[i-1].x)m++;
		a[b[i].d]=m;
	}
}
int main(){
	readln(n);//这个dp不用初始化，想想为什么.
	for(rei i=1;i<=n;i++)readln(a[i]);li();//输入+离散化
	for(rei i=1;i<=n;i++){
		for(rei j=1;j<i;j++)
			g[a[i]][a[j]]=f[a[j]][a[i]]+1;//dp
		for(rei j=1;j<i;j++)
			f[a[i]][a[j]]=max(f[a[i]][a[j]],g[a[i]][a[j]]);//dp
	}
	for(rei i=1;i<=n;i++)
		for(rei j=1;j<=i;j++)
			ans=max(ans,f[a[i]][a[j]]);//答案为f[i][j]中最大的。
	return printf("%d\n",ans+1),0;//想想为什么要+1.
} 
```

---

