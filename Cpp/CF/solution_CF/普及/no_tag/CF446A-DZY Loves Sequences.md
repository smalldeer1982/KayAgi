# DZY Loves Sequences

## 题目描述

给定一个长度为 $n$ 的序列 $a_1\sim a_n$，定义 $a_i,a_{i+1},a_{i+2},\cdots,a_j\left(1\le i\le j\le n\right)$ 的长度为 $j-i+1$，你可以最多更改一个数字，求最长的严格递增子段长度。

## 样例 #1

### 输入

```
6
7 2 3 1 5 6
```

### 输出

```
5
```

# 题解

## 作者：Binary_Lee (赞：7)

## [题面传送门](https://www.luogu.com.cn/problem/CF446A)

### 解决思路

本题可以从**最多更改一个数字**突破。修改后期望的最长严格递增子段应该是从这个数向两侧拓展的。

考虑什么时候可以构成严格递增子段。

设修改的数为 $a_x$，其严格递增子段长度为：

$\begin{cases}a_{x+1}-a_{x-1}\ge 2 & f1_{x-1}+f2_{x+1} +1\\a_{x+1}-a_{x-1}< 2 & \max(f1_{x-1},f2_{x+1} )+1\end{cases}$

其中 $f1_i$ 为以 $i$ 结尾的最长严格递增子段长度， $f2_i$ 为以 $i$ 开头的最长严格递增子段长度。

以 $a_{x+1}-a_{x-1}$ 与 $2$ 的大小关系分类的依据是：中间要有一个数（也就是改动的那个数）。

形象理解就是，我们找到了两段距离为 $1$ 的严格递增子段，但它们之间的一个数凸出来或凹下去了，我们可以通过拉平这样一个数得到一个更长的严格递增子段。

![](https://cdn.luogu.com.cn/upload/image_hosting/tqrb9ea2.png)

然后代码实现就很简单了。

### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
using namespace std;
int n,a[100005],f1[100005],f2[100005],ans;
signed main(){
	IOS;TIE;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) f1[i]=(a[i]>a[i-1])?f1[i-1]+1:1;
	for(int i=n;i>=1;i--) f2[i]=(a[i]<a[i+1])?f2[i+1]+1:1;
	for(int i=1;i<=n;i++){
		if(a[i+1]-a[i-1]>=2) ans=max(ans,f1[i-1]+f2[i+1]+1);
		else ans=max(ans,max(f1[i-1],f2[i+1])+1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：4)

一道思维题，代码很简单，重在思路

设 $l_i$ 为以元素 $i$ 结尾的最长连续上升子序列的长度  
$r_i$ 为以元素 $i$ 开头的最长连续上升子序列的长度

最后，$ans$ 由三个东西转移过来：$ans = max\{ \max\limits_{i=2}^{n-1} l_{i-1}+1+r_{i+1},\max\limits_{i=2}^{n-1} l_{i-1}+1,\max\limits_{i=2}^{n-1} r_{i+1}+1 \}$

1. 将 $i$ 左右两边的连续上升序列拼起来，然后修改元素 $i$，构成一个更长的上升序列  
2. 修改元素 $i$，使得它可以加到前面的上升序列的尾部  
3. 修改元素 $i$，使得它可以加到后面的上升序列的头部  
这里方法2 和 方法3 对应的是元素 $i$ 两边不存在上升序列的情况

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int Maxn=100000+10;
int a[Maxn],l[Maxn],r[Maxn];
int n,ans;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	scanf("%d",a+i);
	l[1]=r[n]=1;
	for(int i=2;i<=n;++i) // 计算 l[i],r[i]
	if(a[i-1]<a[i])l[i]=l[i-1]+1;
	else l[i]=1;
	for(int i=n-1;i;--i)
	if(a[i]<a[i+1])r[i]=r[i+1]+1;
	else r[i]=1;
	for(int i=1;i<=n;++i) // 这里的边界写的跟上面描述的不一样，其实没区别
	{
		ans=max(ans,l[i-1]+1);
		ans=max(ans,1+r[i+1]);
		if(a[i-1]+1<a[i+1])
		ans=max(ans,l[i-1]+1+r[i+1]); // 求出答案
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：王梓涵 (赞：2)

## 01. 题目大意
给一个长度为 $n$ 的序列 $a$，定义$a_i,a_{i+1},a_{i+2}, \cdots,a_j$ 的长度为 $j-i+1$，其中 $1\leqslant i \leqslant j \leqslant n$，你可以最多更改一个数字，求最长的严格递增子段。

## 02. 题目分析
这道题看到之后就觉得可以使用一个三维数组 $f_{i. j. k}$ 来表示状态。其中这个三维数组第一个数表示前 $i$ 个数，第二个数表示是否用掉第 $i$ 个，第三个数表示是否和以前的相连的最长长度。

这样我们就分为两种情况：

当 $a_{i-1} < a_i$ 时，
$$f_{i,0,0} = \max(f_{i,0,0}, f_{i-1,0,0} + 1)$$
$$f_{i,1,0} = \max(f_{i,1,0}, f_{i-1,1,0} + 1)$$
$$f_{i,1,1} = \max(f_{i,1,1}, f_{i-1,0,0} + 1)$$

当 $a_{i-1} > a_i$ 时，
$$f_{i,1,1} = \max(f_{i,1,1}, f_{i-1,0,0} + 1)$$

之后

最后只需要输出 $\max(\max(\max(ans, f_{i,0,0}), f_{i,1,0}), f_{i,1,1})$ 就行了。

## 03. 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int NR = 1e5 + 10;
int a[NR], f[NR][3][3]; //定义三维数组，f[100010][3][3]就够了

int main()
{
	int n, ans = 0;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		f[i][0][0] = 1;
		f[i][1][1] = 1; //初始化
		if(!(i == 1))
		{
			f[i][1][0] = 2;
		}
		if(a[i - 1] < a[i])
		{
			f[i][0][0] = max(f[i][0][0], f[i - 1][0][0] + 1);
			f[i][1][0] = max(f[i][1][0], f[i - 1][1][0] + 1);
			f[i][1][1] = max(f[i][1][1], f[i - 1][0][0] + 1); //第一种情况
		}
		else
		{
			f[i][1][1] = max(f[i][1][1], f[i - 1][0][0] + 1); //第二种情况
		}
		if ((a[i - 2] + 1 < a[i]) && i != 1)
		{
			f[i][1][0] = max(f[i][1][0], f[i - 1][1][1] + 1);
		}
		ans = max(max(max(ans, f[i][0][0]), f[i][1][0]), f[i][1][1]); //输出最后的ans值
	}
	cout << ans << endl; //完结撒花~
}
```


---

## 作者：Pluto_Xz (赞：2)

因为题目上说的是子段不是子串，那么这道题就简单多了。

我们把这段序列扫两遍，第一遍维护以 $i$ 点结尾的最长上升子段长度 $lis_i$

第二遍维护以 $i$ 点作为起点的最长上升子段长度 $bh_i$ 。注意这两次扫描序列的时候要更新 $ans$

具体代码如下：

```cpp
	lis[1]=1,bh[n]=1;int ans=1;//此处ans初始为1
	for(register int i=2;i<=n;++i){
		read(a[i]);ans=max(ans,lis[i-1]+1);
		lis[i]=(a[i]>a[i-1])?lis[i-1]+1:1;
	}
	for(register int i=n-1;i;--i){
		ans=max(ans,bh[i+1]+1);
		bh[i]=(a[i]<a[i+1])?bh[i+1]+1:1;
	}
```
最后我们再枚举每一个点作为断点，且这个点必须满足 $a_{i+1}-a_{i-1} ≥ 2 $因为这样我们才能将中间的点修改为可以连接左右子段的值。

那么对 $ans$ 的贡献就是 $ans=max(ans,lis[i-1]+bh[i+1]+1)$

如下：

```cpp
	for(register int i=2;i<n;++i){
		if(a[i+1]-a[i-1]>1)
		ans=max(ans,lis[i-1]+bh[i+1]+1);
	}
```

### 最后是全部代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
template<class T>inline void read(T &re)
{
	char ch;int f=1;
	while((ch=getchar())<'0'||ch>'9')
	if(ch=='-')f=-1;
	re=ch-48;
	while((ch=getchar())>='0'&&ch<='9')
	re=(re<<3)+(re<<1)+ch-48;
	re*=f;
}
int n,lis[N],bh[N];
long long a[N];
int main()
{
	read(n);read(a[1]);
	lis[1]=1,bh[n]=1;int ans=1;
	for(register int i=2;i<=n;++i){
		read(a[i]);ans=max(ans,lis[i-1]+1);
		lis[i]=(a[i]>a[i-1])?lis[i-1]+1:1;
	}
	for(register int i=n-1;i;--i){
		ans=max(ans,bh[i+1]+1);
		bh[i]=(a[i]<a[i+1])?bh[i+1]+1:1;
	}
	for(register int i=2;i<n;++i){
		if(a[i+1]-a[i-1]>1)
		ans=max(ans,lis[i-1]+bh[i+1]+1);
	}
	printf("%d",ans);
}
```


---

## 作者：Nuyoah_awa (赞：1)

### 题目大意

给一个序列 $a$，求最多更改一个数字后，求最长的严格递增子段的长度。

### 题目分析

由于可以更改一个数字，我们可以视为最终的严格递增子段是由两个子段拼接而成的。

于是我们可以枚举断点 $\forall i \in [1,n]$，以这个点为断点,修改这个点后，如果左右最长的严格递增子段可以拼起来，以这个点为断点的最长的严格递增子段长度为左右最长的严格递增子段长度和 $+1$。如果不能，以这个点为断点的最长的严格递增子段长度为左右最长的严格递增子段长度的较大值。

上述方法的时间复杂度为 $O(n^2)$，很明显过不了。

我们可以用 $O(n)$ 的时间，求出以点 $i$ 结尾的最长严格递增子段 $f_i$，再求出以 $i$ 开头的最长严格递增子段 $g_i$，这个可以视为，从右到左以 $i$ 结尾的最长严格下降子段。

然后用 $O(n)$ 的时间求出以 $i$ 为断点的最长的严格递增子段长度（式子如上思路）。最后求所有断点答案的最大值。

最后总的时间效率为 $O(n)$。

### code
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 1e5 + 5;
int n, a[N], f[N], g[N], ans;
signed main()
{
	cin >> n;
	for(int i = 1;i <= n;i++)
		cin >> a[i];
	for(int i = 1;i <= n;i++)
	{
		if(a[i] > a[i-1])
			f[i] = f[i - 1] + 1;
		else
			f[i] = 1;
	}
	for(int i = n;i >= 1;i--)
	{
		if(a[i] < a[i+1])
			g[i] = g[i + 1] + 1;
		else
			g[i] = 1;
	}
	for(int i = 1;i <= n;i++)
	{
		if(a[i+1] - a[i-1] > 1)
			ans = max(ans, f[i-1] + g[i+1] + 1);
		else
			ans = max(ans, max(f[i - 1], g[i + 1]) + 1);
	}
	cout << ans;
	return 0;
}

```

---

## 作者：Aisaka_Taiga (赞：1)

今天的月赛签到题和这个重题了，赛后 AC 的代码被 hack 了所以来搞一下这道题目。

思路其实并不难，我们看到题目里面只需要我们修改一个数字，所以我们可以直接考虑一下如何让收益最大化。

分成两种情况：

1. 当前点修改后与前面的点形成一个严格递增的序列，但是和后面的不会接起来。

2. 当前点修改后可以与前后的点形成严格递增的序列，也就是比如 `1 3 4 1 9 10` 这种的，很显然修改第四个数就可以使序列最长为 $6$。

这时候我们要是一个一个遍历差修改后的序列长度的话肯定是会 TLE 的，所以我们考虑预处理一下以每一个数字为左端和右端的严格递增序列的最大长度，在判断第一种情况的时候，比如当前点为 $i$，我们可以直接用 $l_{i-1}+1$ 来表示修改后的此序列的长度；第二种情况我们需要先判断 $i$ 左右两个数的大小，因为都是整数，所以 $i$ 右边那个数至少比左边那个数大 $2$。

code：

```cpp
#include<bits/stdc++.h>
#define N 1001000 
using namespace std;
int n,a[N],l[N],r[N],ans; 
signed main()
{
	cin>>n;
	l[1]=1,r[n]=1;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=2;i<=n;i++)
	{
		if(a[i]>a[i-1])
		  l[i]=l[i-1]+1;
		else l[i]=1;
	}
	for(int i=n-1;i>=1;i--)
	{
		if(a[i]<a[i+1])
		  r[i]=r[i+1]+1;
		else r[i]=1;
	}
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,max(l[i-1]+1,r[i+1]+1));
		if(a[i-1]<a[i+1]-1)
		  ans=max(ans,l[i-1]+1+r[i+1]);
	}
	cout<<ans<<endl;
	return 0;
 } 
 ```

---

## 作者：ttq012 (赞：0)

[双倍经验](https://www.luogu.com.cn/problem/P9147)

$O(n^2)$ 做法：

暴力枚举修改的每一个数，然后计算最长严格上升子串的长度，取最大值即可。

期望得分：$\color{yellow}70$。

$O(n)$ 做法：

首先修改一个数一定不比不修改差。

设 $f_i$ 表示以 $i$ **结尾**的最长的严格递增子序列的长度，$g_i$ 表示以 $i$ **开头**的最长的严格递增子序列的长度。

现在如果想要修改第 $i$ 个数，如果：

+ $i = 1$，那么必然可以修改。
+ $i = n$，那么必然可以修改。
+ $2\le i\le n-1$，那么有：
  + $a_{i+1}-a_{i-1}\ge 2$，那么可以把 $a_i$ 的值修改成 $a_{i-1}+1\sim a_{i+1}-1$ 之间任意的一个正整数，让两个序列连续。于是贡献就是 $f_{i-1}+g_{i+1}+1$，其中 $f_{i-1}$ 表示 $i-1$ 结尾的连续子序列的贡献，$g_{i+1}$ 表示 $i+1$ 开头的连续子序列的贡献，$1$ 就是 $a_i$ 这一个元素的贡献。
  + $a_{i+1} - a_{i-1} < 2$，容易证明把 $a_i$ 修改成任意的数都不会让前面和后面的两段合并。那么修改的贡献就是 $\max(f_{i-1},g_{i+1})+1$。

然后按照上面的推理进行模拟即可。

期望得分：$\color{green}{100}$。

```cpp
#include <bits/stdc++.h>
const int N = 1e6 + 10;
int a[N], f[N], g[N];
signed main()
{
  int n;
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
  for (int i = 1; i <= n; i++)
    if (a[i] > a[i - 1])
      f[i] = f[i - 1] + 1;
    else
      f[i] = 1;
  for (int i = n; i; i--)
    if (a[i] < a[i + 1])
      g[i] = g[i + 1] + 1;
    else
      g[i] = 1;
  int mx = 0;
  for (int i = 1; i <= n; i++)
    if (a[i + 1] - a[i - 1] >= 2)
      mx = std::max(mx, f[i - 1] + g[i + 1] + 1);
    else
      mx = std::max(mx, std::max(f[i - 1], g[i + 1]) + 1);
  std::cout << mx << std::endl;
  return 0;
}
```



---

## 作者：快斗游鹿 (赞：0)

因为可以修改为任意整数，所以修改一定不会比不修改更劣。用 $s_i$ 表示以第 $i$ 位结尾的严格递增子段的长度，用 $t_i$ 以第 $i$ 位开头的严格递增子段的长度。

接下来分类讨论：

当 $a_{i+1}-a_{i-1}>1$ 时，说明可以更改 $a_i$ 使得左右两个严格递增子段变为一个。这时 $ans=\max(ans,s_{i-1}+1+t_{i+1})$。

否则 $ans=\max(ans,\max(s_{i-1}+1,t_{i+1}+1))$，即可以通过修改 $a_i$ 使它可以加到前面的严格递增子段的后面或后面的严格递增子段的前面。

这题就做完啦。

---

## 作者：Lee666666 (赞：0)

~~Codeforces 紫题现状~~

先补充一点，这道题还有一个前提翻译里没有给出来，就是**数列中所有的数以及任意一个修改完以后的数必须为整数**

**这道题就是让你求出修改一个整数以后这个数列能得到的严格递增子段的最大值。**

首先易知修改肯定比不修改要更优

那枚举修改位置 $i$

对于每个位置，分两类情况讨论：

第一种，修改完后的 $a_i$ 能够与以 $a_{i-1}$ 为结尾的严格递增子段**和**以 $a_{i+1}$ 为起始的严格递增字段共同构成一个严格递增子段。形式化的描述，即 $a_{i+1}-a_{i-1}>1$。

第二种，修改完后的 $a_i$ 无论如何都无法构成上述讨论中的匹配，仅能与以 $a_{i-1}$ 为结尾的严格递增子段**或**以 $a_{i+1}$ 为起始的严格递增子段共同构成一个严格递增子段。形式化地描述，即 $a_{i+1}-a_{i-1} \leq 1$。（这里注意，如果 $a_{i-1}$ 与 $a_{i+1}$ 仅满足 $a_{i-1}<a_{i+1}$ 是不一定可以将两个字段连接在一起的，感性地说，如果这两个元素中间没有足够的缝隙使修改后的 $a_i$ 插入进去的话同样不能完成讨论 1 中的构造。这一情况建立在我补充的前提的基础上提出。）

接下来是预处理部分。

设 $f1_i$ 表示以 $a_i$ 为结尾的严格递增子段的最长长度，$f2_i$ 表示已 $a_i$ 为起始的严格递增子段的最长长度，那么有状态转移方程
$$
f1_i=\begin{cases}f1_{i-1}+1&a_{i-1}<a_i\\1&a_{i-1} \geq a_i\end{cases}
$$

其中 $f1_1=1$

$$
f2_i=\begin{cases}f2_{i+1}+1&a_i<a_{i+1}\\1&a_i \geq a_{i+1}\end{cases}
$$
其中 $f2_n=1$

那么，如果修改 $a_i$，如果满足讨论 1，则修改后含 $a_i$ 的最长严格递增子段为 $f1_{i-1}+f2_{i+1}+1$；反之则满足讨论 2，则修改后含 $a_i$ 的最长严格递增子段为 $\max(f1_{i-1}+1,f2_{i+1}+1)$。修改 $a_1$ 和修改 $a_n$ 需要特判。

这样，我们就能用 $O(1)$ 的时间处理修改每个位置所对应的的严格递增子段的长度，最后将它们取最大值即可。

代码

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read() {
    int s = 0;
    char ch = getchar();
    while (ch < 48 || ch > 57) {
        ch = getchar();
    }
    while (ch > 47 && ch < 58) {
        s = (s << 3) + (s << 1) + ch - 48;
        ch = getchar();
    }
    return s;
}

int n, ans, a[100015], f1[100015], f2[100015];

int main(void) {
    n = read();
    for (register int i = 1; i <= n; i++) {
        a[i] = read();
    }
    f1[1] = 1; // 预处理
    for (register int i = 2; i <= n; i++) {
        f1[i] = a[i] > a[i - 1] ? f1[i - 1] + 1 : 1;
    }
    f2[n] = 1;
    for (register int i = n - 1; i > 0; i--) {
        f2[i] = a[i] < a[i + 1] ? f2[i + 1] + 1 : 1;
    }
    ans = max(ans, f2[2] + 1);
    for (register int i = 2; i < n; i++) { // 枚举位置分类讨论并更新 ans
        if (a[i + 1] - a[i - 1] > 1) {
            ans = max(ans, f1[i - 1] + 1 + f2[i + 1]);
        }
        else {
            ans = max(ans, max(f1[i - 1] + 1, f2[i + 1] + 1));
        }
    }
    ans = max(ans, f1[n - 1] + 1);
    printf("%d", ans);
    return 0;
}

```

时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

---

## 作者：Yukinoshita_Yukino (赞：0)

题意：你可以修改一个数列中的一个数，求修改后数列的最长上升子段的长度。

我们设 $l_i$ 为原数列到以第 $i$ 位结尾最长上升子段的长度，设 $r_i$ 为原数列到以第 $i$ 位开头最长上升子段的长度。

接着对原数列逐个元素枚举，那么枚举到第 $i$ 位，以这一位为中间节点的答案就是 $l_{i-1}+1+r_{i+1}$。

不过这样做的话会有一点问题。

```1 1 2 3 4 9 5 6```

注意到，按照上面算的最优解是 $l_{5}+1+r_{7}$，即为 $7$。不过把第六位的 $9$ 换成任意一个正整数都不能使答案数列一直上升。

所以上述情况只有枚举到的元素的左右两个数相差大于 $2$ 即可，注意是右边的数比左边的大。

```cpp

#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int n,cnt[maxn],l[maxn],r[maxn]; 
int main()
{
	cin>>n;
	l[1]=1,r[n]=1;
	for(int i=1;i<=n;i++)
	{
		cin>>cnt[i];
	}
	for(int i=2;i<=n;i++)
	{
		if(cnt[i]>cnt[i-1]) l[i]=l[i-1]+1;
		else l[i]=1;
	}
	for(int i=n-1;i>=0;i--)
	{
		if(cnt[i]<cnt[i+1]) r[i]=r[i+1]+1;
		else r[i]=1;
	}
	int ans=-1;
	for(int i=1;i<=n;i++)
	{
		ans=max(ans,max(l[i-1]+1,r[i+1]+1));
		if(cnt[i-1]<=cnt[i+1]-2) ans=max(ans,l[i-1]+1+r[i+1]);
	}
	cout<<ans;
	return 0;
 } 

```

---

## 作者：lzyqwq (赞：0)

# 一、阶段
阶段不难看出是从 $1$ 到 $n$ 枚举每一位改不改变。
# 二、状态
我们用 $f1_i$ 表示以 $a_i$ 为结尾的最长上升子串，用 $f2_i$ 表示以 $a_i$ 开头的最长上升子串。注意，和子序列不同，子串必须是连续的一串。
# 三、策略
如果我们使前后两个子串能连接，则当前的长度为以 $a_i-1$ 为结尾的最长上升子串的长度加上以 $a_i+1$ 为开头的最长上升子串的长度加上 $a_i$ 本身为 $1$ 的长度，即 $f1_{i-1}+1+f2_{i+1}$。当然，由于序列中的全是自然数，所以相邻两数之差最小为 $1$，即 $a_i-a_{i-1}\geqslant1$，故 $a_{i+1}-a_{i-1}\geqslant2$ 时才可以改动 $a_i$。

否则当前的长度为以 $a_{i-1}$ 为结尾的最长上升子串的长度和以 $a_{i+1}$ 为开头的最长上升子串的长度的最大值，即 $\max(f1_{i-1},f2_{i+1})+1$。
# 四、代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],f1[100005],f2[100005],n,ans=1;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		f1[i]=f2[i]=1;//初始化
	}
	for(int i=2;i<=n;i++)//f1[i]为以i结尾的最长上升子串 
	{
		f1[i]=a[i]>a[i-1]?f1[i-1]+1:f1[i];
	}
	for(int i=n-1;i>0;i--)//f2[i]为以i开头的最长上升子串 
	{
		f2[i]=a[i]<a[i+1]?f2[i+1]+1:f2[i];
	}
	for(int i=2;i<n;i++)
	{
		if(a[i-1]<a[i+1]-1)//能连接，a[i-1]<a[i+1]-1
		{
			ans=max(f1[i-1]+f2[i+1]+1,ans);
		}
		else//不能连接
		{
			ans=max(ans,max(f1[i-1],f2[i+1])+1);
		}
	}
	ans=max(ans,max(f1[n-1],f2[2])+1);//补上1和n的方案 
	printf("%d\n",ans);
	return 0;
}
```


---

