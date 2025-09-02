# Unequal Array

## 题目描述

You are given an array $ a $ of length $ n $ . We define the equality of the array as the number of indices $ 1 \le i \le n - 1 $ such that $ a_i = a_{i + 1} $ . We are allowed to do the following operation:

- Select two integers $ i $ and $ x $ such that $ 1 \le i \le n - 1 $ and $ 1 \le x \le 10^9 $ . Then, set $ a_i $ and $ a_{i + 1} $ to be equal to $ x $ .

Find the minimum number of operations needed such that the equality of the array is less than or equal to $ 1 $ .

## 说明/提示

In the first test case, we can select $ i=2 $ and $ x=2 $ to form $ [1, 2, 2, 1, 1] $ . Then, we can select $ i=3 $ and $ x=3 $ to form $ [1, 2, 3, 3, 1] $ .

In the second test case, we can select $ i=3 $ and $ x=100 $ to form $ [2, 1, 100, 100, 2] $ .

## 样例 #1

### 输入

```
4
5
1 1 1 1 1
5
2 1 1 1 2
6
1 1 2 3 3 4
6
1 2 1 4 5 4```

### 输出

```
2
1
2
0```

# 题解

## 作者：_acat_ (赞：5)

注：本篇题解为转载题解，已通过作者本人同意。

原文链接：[Link](https://blog.csdn.net/cannothit/article/details/124391234)
### 题意
给定长度为 $n$ 的序列 $a$ 中，通过 $0$ 次或多次以下操作使得 序列中只出现 $0$ 次或 $1$ 次相邻两个数相等的情况。
- 选定两个相邻的点位并将其同时赋值为 $x$，形式上为：选定 $i$（小于 $n$），使得 $a_i = a_{i+1} = x$，$x$ 为任意取值。

### 思路
我发现，如果我们使用了一次操作，则选择的两个位置上就会变成相同的，即会贡献 $1$ 对相等
我们尝试一些例子，如下图：

- $\{1,1,1\}$
则直接修改一次即可。
![](https://img-blog.csdnimg.cn/e1fd0d094acf423c953aea8df0f8cdf0.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5LiA5Liq5LiN54ix5omTY2bnmoRhY21lcuWQpw==,size_8,color_FFFFFF,t_70,g_se,x_16)  
- $\{1,1,1,1\}$
则也是修改一次。
![](https://img-blog.csdnimg.cn/6d277c3866e14ed089ffc05c63aca5d4.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5LiA5Liq5LiN54ix5omTY2bnmoRhY21lcuWQpw==,size_11,color_FFFFFF,t_70,g_se,x_16)

可以手动模拟一下 $\{1,1,1,1,1\}$，则需要两次。

会发现除了 $\{1,1,1\}$ 比较特殊，其余都是 $r-l-1$ 的次数。

综上对于连续出现的可以这样子修改。

但是对于不连续出现的，因为每次操作都会留下 $1$ 对相等，则我们并不能分开处理每一批连续出现的数。

所以实际上我们相当于通过操作将每片连在一起，即从最左边第一次出现相邻相等的数，一直链接到最右边相邻相等的数。

如以下：

$\{1,1,2,1,1\}$

$\{1,1,2,3,1,1\}$

![](https://img-blog.csdnimg.cn/4dfe2e727a86455197777c79d3d51e88.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5LiA5Liq5LiN54ix5omTY2bnmoRhY21lcuWQpw==,size_13,color_FFFFFF,t_70,g_se,x_16)

![](https://img-blog.csdnimg.cn/7d57a4f0ddb2471f8c63cbc8f644a19e.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBA5LiA5Liq5LiN54ix5omTY2bnmoRhY21lcuWQpw==,size_15,color_FFFFFF,t_70,g_se,x_16)

最后会发现答案的计算都为：$r-l-1$，最后记得对长度为 $3$ 就特判一下，不然公式会计算为 $0$。

### AC 代码
- $cnt$ 为统计出现相邻相等的对数。
- $l,r$ 记录最左端和最右端。
```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define AC return 0;
using namespace std;
//#define ll long long
//#define int long long
int a[200005];
void slove()
{
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        int l = n,r = 1;
        int cnt = 0;
        for(int i = 2; i <= n; i++)
        {
            if(a[i] == a[i - 1])
            {
                l = min(l,i - 1);
                r = max(r,i);
                cnt++;
            }
        }
        if(cnt < 2)
            cout << 0 << endl;
        else
        {
            int k = r - l - 1;
            if(k == 1)
                cout << 1 << endl;
            else
                cout << k - 1 << endl;
        }   
}
signed main()
{
        ios::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
        int T;
        cin >> T;
        while(T--)
            slove();
        AC
}
```

---

## 作者：__little__Cabbage__ (赞：2)

## Soluiton

首先，如果原序列中只出现了 $\le 1$ 次 $a_i = a_{i+1}$ 的情况，答案为 $0$。接下来讨论出现次数 $> 1$ 的情况。

考虑序列 $\{ 1 , 1 , \dots , 1 \}$，设这里共有 $k$ 个 $1$，那么当我们队**第二个** $1$ 进行操作时，序列变为 $\{ 1 , 2 , 2 , 1 , \dots , 1 \}$，于是我们又需要对**第三个** $1$ 进行操作，接下来是**第四个**，**第五个**……可以发现，一直需要操作到第 $k-2$ 个，此时序列变为 $\{ 1 , 2 , 3 , 4 , \dots , x , x , 1 \}$，总共需要操作 $k-3$ 次，满足要求。

再考虑出现的 $a_i = a_{i+1}$ 不连续的情况，但是我们在进行一次操作后又会新产生一对 $a_{i+1} = a_{i+2}$，这样总情况数还是 $> 1$，所以**是否连续出现并不重要**，我们只需要统计第一次出现和最后一次出现就可以惹。

设第一次出现的位置为 $l$，最后一次为 $r$，则总长度为 $r-l+2$，那么答案即为 $r-l+2-3$，也就是 $r-l-1$。然后注意需要特判 $r-l+2=3$ 的情况就可以了。

## Code

```cpp
#include<iostream>
#include<cstdio>
//#define int long long
#define il inline
using namespace std;
const int MAXN=2e5+5;
int n,a[MAXN];
il void solve()
{
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	int l=-1,r=-1,cnt=0;
	for(int i=1;i<n;++i)
	{
		if(a[i]!=a[i+1]) continue;
		if(l==-1) l=i;
		r=i;
		++cnt;
	}
	if(cnt<=1)
	{
		cout<<0<<'\n';
		return;
	}
	if(r-l+2==3) cout<<1<<'\n';
	else cout<<r-l-1<<'\n';
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：_little_Cabbage_ (赞：2)

# CF1672C Unequal Array 题解

~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-cf1672c)~~

这是一道找规律题。

首先，如果只有一对相同的或者没有相同，那么直接输出 $0$ 就行。

然后我们发现，如果相同的每一对数中，设 $i-1$ 的位置为 $x$，$i$ 的位置为 $y$，然后我们求出 $x$ 的最小值 $l$ 与 $y$ 的最大值 $r$，如果 $r-l=2$ 我们就输出 $1$，否则输出 $r-l-2$。

为什么呢？

因为我们举几个例子后发现，$l+2$ 和 $r-2$ 中间的数可以不用操作，我们只用管最左边的一对数，即 $a_l$ 和 $a_{l+1}$，和最右边的一对数，即 $a_r$ 和 $a_{r-1}$ 就行了，所以我们直接把 $l$ 不断往右移，需要 $r-l-3$ 次操作，然后再进行一次合并，就是 $r-l-2$ 次了。

但是对于 $a=[1,1,1]$ 的情况，可得需要 $1$ 次操作，但是代入公式可得 $3-1-2=0$ 次，所以我们需要进行特判。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[200010];
//long long f[200010];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		int cnt=0,l=1e9,r=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
			if(i!=1)
			{
				if(a[i]==a[i-1])
				{
					cnt++;
					l=min(l,i-1);
					r=max(r,i);
				}
			}
		}
		if(cnt<2)
		{
			printf("0\n");
		}
		else
		{
			if(r-l==2)
			{
				printf("1\n");
			}
			else
			{
				printf("%d\n",r-l-2);
			}
		}
	}
}
```
[AC 记录](https://codeforces.com/contest/1672/submission/240372387)

---

## 作者：happy_zero (赞：2)

## 思路
我们先从一次操作入手：先单独拎出三个元素，$a_1=1$，$a_2=1$，$a_3=2$，考虑对 $a_2$ 和 $a_3$ 进行一次操作，将它们都改成2，那么这时$a_1$=1，$a_2$=2，$a_3$=2，把它们放在一起比对一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/3kcwawfl.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们发现，不考虑具体的数值变化，这次操作就相当于把相同的一对数的位置向后移了一位！

这时，我们考虑更复杂的情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/d5t2z6t3.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于这个情况，我们该怎么办？依据刚才的推断，我们对这串数进行操作，每次将相同的一对数（这里指第一个和第二个）往后移，直到这串数变成这样(这里的两个 $x$ 为相同的数）：
![](https://cdn.luogu.com.cn/upload/image_hosting/y4dpzcuy.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

马上就要成功了！最后一步：![](https://cdn.luogu.com.cn/upload/image_hosting/fgth4dw5.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这时，操作结束。

最后再来考虑普通的情况，对于以下这个数列:![](https://cdn.luogu.com.cn/upload/image_hosting/e8s1b6ik.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
这个数列中有许多相同的一对数，如果向上面那样两对两对合并的话未免太复杂了，但我们知道，如果只有要合并最左边的 $a_1$，$a_2$ 和最右边的 $a_7$，$a_8$ 就和上面一样了，那我们不妨先把这两对合并。由上面可得，我们将相同的一对数不停往右移动，在这个过程中我们会发现：中间的 $a_3$，$a_4$ 这一对数也被消除了！

由此，我们得出，求合并的最小操作数，只和最左边和最右边的一对数相关，其它的数均会被覆盖掉。

那么最小操作步数如何计算？我们不妨设最左边的那一对数的第一个数的位置为 $l$，最右边的那一对数的第二个数的位置为 $r$，首先我们要把 $l$“移到”$r-3$ 的位置，这里需要 $r-3-l$ 的操作次数，最后一次合并也需要一次操作，所以最小操作步数为 $r-l-2$ 次。

就这么简单吗？当然不是。对于 $a_1=1$，$a_2=1$，$a_3=1$，易得它共需要1次操作，但再看得出的公式，将 $l=1$，$r=3$ 带入计算，发现结果是0。这是因为我们的公式中因为要考虑最小操作次数，所以并不会计算两对相同的数重叠的情况，所以这里我们要加一次特判：
```cpp
if(r-l-2==0)cout<<1<<endl;
```
## 实现
思路分析完了，让我们来看一下如何实现：先输入，接着用 $cnt$ 变量统计相同的一对数的个数，并用 $l$ 和 $r$ 记录最左边的那一对数的第一个数的位置和最右边的那一对数的第二个数的位置。接下来先判断如果不需要操作（$cnt=1$）那么就直接输出零，否则先特判（如上），最后输出 $r-l-2$ 的结果。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt;
int l=1e9,r;
int a[200005];
int main(){
    int t;
    cin>>t;
    while(t--){
    	cnt=0;l=1e9;r=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=2;i<=n;i++){
            if(a[i]!=a[i-1])continue;
            cnt++;
            l=min(l,i-1);
            r=max(r,i);
        }
        if(cnt==1||cnt==0){
            cout<<0<<endl;
            continue;
        }
        if(r-l-2==0)cout<<1<<endl;
        else cout<<r-l-2<<endl;
    }
    return 0;
}
```


---

## 作者：JS_TZ_ZHR (赞：1)

## 题意：

给定一个长为 $n$ 的数组 $a$。每次你可以使一对相邻的数都变为任意的同一个数。问最少几次操作使得这个数组中只有一对相邻的数相等。

## 题解：

显然初始数组满足条件的话直接输出零即可。

否则考虑到最后一次操作一定产生仅存的一对相邻的数，从初始数组的第一对开始，每次把相等的数的后一个和它的下一个数变为没有出现过的一个数，同时统计相等的相邻的数对的个数，符合条件时输出操作数即可。

```cpp
#include<bits/stdc++.h> 
#define int long long
#define N 1000005
using namespace std;
int T,n,a[N],sum,ans,now,cnt;
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		now=1e9+1;
		ans=0;
		cnt=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=2;i<=n;i++)if(a[i]==a[i-1])cnt++;
		if(cnt<=1)cout<<0<<endl;
		else{
			for(int i=2;i<=n;i++){
				if(a[i]==a[i-1]){
					if(a[i+1]==a[i+2])cnt--;
					if(a[i]==a[i+1])cnt--;
					a[i]=a[i+1]=now;
					now++;
					ans++;
				}
				if(cnt<=1)break;
			}
			cout<<ans<<endl;
			ans=0;
		}
	} 
}

```


---

## 作者：yhx0322 (赞：1)

## Description
现有一个长度为 $n$ 的序列 $a$。每次可以将 $a_i$ 和 $a_{i+1}$ 的值赋为 $x$。求最少操作次数使得数组中只有一对**相邻的数对**是相等的。

## Solution
首先我们统计出原始数组中所有**相邻相等数对**的数量，记为 $c$。

循环 $[2,n]$，如果发现当前数和前一个数相等，即 $a_i = a_{i-1}$，修改 $a_i$ 和 $a_{i-1}$ 为数组中没有出现过的数，避免重复。这里可以直接设数据范围中 $a_i$ 的最大值 $+1$，即 $10 ^ 9 + 1$。

修改之后，我们便可以计算修改后对于答案的影响：

- 如果 $a_{i} = a_{i+1}$，说明修改了 $a_{i}$ 后，答案会少 $1$。
- 或者满足 $a_{i+1} = a_{i+2}$，答案也同样会受到影响，需要 $-1$。

当发现 $c \le 1$ 的时候输出答案即可。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, INF = 1e9 + 1;
int T, a[N], n, ans, c, x;

inline void solve() {
	x = INF + 1;
	c = ans = 0;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 2; i <= n; i++) c += (a[i] == a[i - 1]);
	if (c <= 1) return cout << 0 << '\n', void();
	for (int i = 2; i <= n; i++) {
		if (a[i] == a[i - 1]) {
			c -= (a[i] == a[i + 1]);
			c -= (a[i + 1] == a[i + 2]);
			a[i] = a[i + 1] = x++, ans++;
		}
		if (c <= 1) break;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：Tulip_ (赞：0)

### 题意

您有一个长度为 $n$ 的数组 $a$。

我们将数组 $a$ 的相等性定义为索引数 $1 \le i \le n - 1$ 使得 $a_i = a_{i + 1}$。我们可以执行以下操作：

- 选择两个整数 $i$ 和 $x$，使得 $1 \le i \le n - 1$ 和 $1 \le x \le 10^9$。然后，将 $a_i$ 和 $a_{i + 1}$ 设置为 $x$。

找到所需的最小操作数，使数组的相等性 $\le1$。

### 思路

当我们看到**所需的最小操作数**和**使数组的相等性** $\le1$，再结合题目，就可以发现这是一道规律题。

那就举个“栗”子吧：

$$
1,1,2
$$

$$
1,2,2
$$

我们会发现将第一个变成第二个，就相当于把相同的一对数的位置向后移了一位。

多举几个“栗”子，就知道规律：

- **只有一对相同**的或者**没有相同**，那么直接输出 $0$ 就行。

如果相同的每一对数中，**设 $i-1$ 的位置为 $x$，$i$ 的位置为 $y$**，然后我们求出 $x$ 的最小值 $l$ 与 $y$ 的最大值 $r$。

- $r-l=2$ 我们就输出 $1$，否则输出 $r-l-2$。

但是对于这组数据（如下）。

$$
1,1,1
$$

可得**需要 $1$ 次操作**，但是代入公式为 $0$ 次（$3-1-2=0$），所以我们**需要进行特判**。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
int a[200005];
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		int cnt=0,l=1e9,r=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
				if(a[i]==a[i-1]&&i!=1)	cnt++,l=min(l,i-1),r=max(r,i);
		}
		if(cnt<2)cout<<0<<endl;
		else{
			if(r-l==2)cout<<1<<endl;
			else	cout<<r-l-2<<endl;
		}
	}
	return 0; 
}
```

### 注意

- 一定要初始化。

- 数组至少开大 $5$。

---

## 作者：yzc20100218 (赞：0)

## CF1672C 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1672C)

简单翻译一下：（换个好理解的说法）  
有一个含有 $n$ 个元素的数列，可以执行一次操作使得数列中一对相邻元素变成相同的数，此数可以任意取。请问最少执行多少次操作使得数组内相邻元素相同的数对至多存在 $1$ 个？

假如，我们有数列 $1,1,1,1,1$，我们可以如下操作：  
$1,1,1,1,1 \to 1,2,2,1,1 \to 1,2,3,3,1$

对于任意一个数列 $\{a_i\}$，我们都可以和上面一样操作 $n-2$ 次，使得数列变成 $\{a_1,b_1,b_2,\dotsb,b_{n-3},b_{n-3},a_n\}$，其中 $b_1\sim b_n,a_1,a_n$ 均不相等（$a_1$ 可能等于 $a_n$）。

这样操作即可：  
$\{a_1,a_2,a_3,a_4,a_5\dotsb,a_n\}\to$  
$\{a_1,b_1,b_1,a_4,a_5,\dotsb,a_n\}\to$  
$\{a_1,b_1,b_2,b_2,a_5,\dotsb,a_n\}\to$  
$\{a_1,b_1,b_2,b_3,b_3,\dotsb,a_n\}\to\dots$  

可以发现处理到倒数第二个数对 $(a_{n-2},a_{n-1})$ 时已经满足要求，结束操作。

则除开第一个数对 $(a_1,a_2)$ 和最后一个数对 $(a_{n-1},a_n)$ 无需处理，其他所有数对均需处理，共 $n-3$ 次。（共有 $n-1$ 个数对，去掉第一个和最后一个即为所求）

但是一个数列中不一定需要全部如此处理，我们可以去掉已经满足要求的两端，处理中间即可。

所以，可以遍历数列，找到第一个和最后一个相同的数对，将它们标记为起点 $st$ 和终点 $ed$，对中间进行上述操作即可，需要 $ed-st-2$ 此操作。（当然，注意到 $3$ 个元素时，需要一次操作，特判即可）

但是有一个奇怪的问题，为什么数列只能这么处理？

因为数列中的每一个相同的相邻数，只能对第二个元素以及其下一个数进行操作以去除这一对，但是代价是又添加了一对，我们仅仅是将不满足要求的数对向右平移了一个位置。

但是这个数对在向右的过程中也可以吞噬其它不满足要求的数对，使得整个数列中不满足要求的只有这个数对，这就是我们所期望的。

于是，我们自然就可以让它从第一个不满足要求的数对开始吞噬一直到最后一个不满足要求的数对，这样所有不满足要求的数对就被这个数对独揽。

最后的最后，一个值得注意的是如果数对中不存在不满足要求的数对，需要输出 $0$。

代码如下：  
注 最后输出的时候，特判如果结果为 $0$ 说明长度为 $3$ 则改为 $1$ 输出；如果结果为负数说明不存在不满足要求的数对则改为 $0$ 输出。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define in read()
typedef long long ll;
#define int ll

int read()
{
	int x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch))
	{
		if(ch == '-')
		{
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch))
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}

void solve()
{
	int n = in;
	int last,st,ed;
	last = in;
	st = n;
	ed = 1;
	for(int i = 2;i <= n;i++)
	{
		int tot = in;
		if(tot == last)
		{
			st = min(st,i - 1);
			ed = max(ed,i);
		}
		last = tot;
	}
	int ans = ed - st - 2;
	printf("%d\n",ans == 0? 1 : (ans < 0? 0 : ans));
}

signed main()
{
	int t = in;
	while(t--)
	{
		solve();
	}
	return 0;
}
```

$\texttt{AC}$ 记录：[Record](https://www.luogu.com.cn/record/142196742)

---

