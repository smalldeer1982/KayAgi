# [ABC296C] Gap Existence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc296/tasks/abc296_c

長さ $ N $ の数列 $ A=(A_1,\ldots,A_N) $ が与えられます。

$ 1\leq\ i,j\ \leq\ N $ である組 $ (i,j) $ であって、$ A_i-A_j=X $ となるものが存在するかどうか判定してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ -10^9\ \leq\ A_i\ \leq\ 10^9 $
- $ -10^9\ \leq\ X\ \leq\ 10^9 $
- 入力は全て整数である
 
### Sample Explanation 1

$ A_6-A_3=9-4=5 $ です。

### Sample Explanation 2

$ A_i-A_j=-4 $ となる組 $ (i,j) $ は存在しません。

### Sample Explanation 3

$ A_1-A_1=0 $ です。

## 样例 #1

### 输入

```
6 5
3 1 4 1 5 9```

### 输出

```
Yes```

## 样例 #2

### 输入

```
6 -4
-2 -7 -1 -8 -2 -8```

### 输出

```
No```

## 样例 #3

### 输入

```
2 0
141421356 17320508```

### 输出

```
Yes```

# 题解

## 作者：_Haoomff_ (赞：3)

$2 \le n \le 2 \times 10^5$，$n$ 太大，无法使用二层循环解决。于是，我便使用了简单的 map。

先用 map 统计每种数字出现的次数，然后在整个数组内求有多少个数等于 $a_i-c$，求完后的个数若等于 $0$，输出 “No”，否则输出 “Yes”。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,a[200005],cnt;
map<int,int> m;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>x;
	for(int i=0;i<n;++i){
		cin>>a[i];
		++m[a[i]];
	}
	for(int i=0;i<n;++i)cnt+=m[a[i]-x];
	if(cnt==0)cout<<"No";
	else cout<<"Yes"; 
	return 0;
}
```

---

## 作者：2c_s (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc296_c)

# 思路

**题意**：题目大意就是让我们在 $A_1,A_2,...,A_N$ 这 $N$ 个数中找出一对数 $A_i$ 和 $A_j$ 满足 $A_i-A_j=X$。

由于数据范围是 $1\le N\le 2\times 10^5$，所以我们最多只能用 $O(n\log n)$ 的算法。考虑输入数组后要排序和精确找对应数字的两个要求，可以用 set 做题。

循环读入数组时，每读入一个数 $A_i$ 就在 set 中插入 $A_i+X$。这样在寻找数字时，匹配的就正好是差为 $X$ 的两个数。

之后再次循环遍历，用 find 函数找 $A_i$，如果找到的返回值不是末尾，就说明找到了一组差为 $X$ 的数，输出 ``Yes`` 并结束程序。如果全部遍历完后仍然没有找到任何一对差为 $X$ 的数，输出 ``No``。

- 最后记得输出换行。

# AC Code

~~~cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,x,a[N];
set<int>st;
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
		st.insert(x+a[i]);
	}
	for(int i=1;i<=n;++i){//找匹配的数对。
		if(st.find(a[i])!=st.end()){
			cout<<"Yes\n";
			return 0;
		}
	}
	cout<<"No\n";
	return 0;
}
~~~

---

## 作者：PineappleSummer (赞：1)

[$\color{orangered}\text{题目传送门}$](https://www.luogu.com.cn/problem/AT_abc296_c)
## 题意
给出一个长度为 $N$ 的序列 $A=(A_1,\ldots,A_N)$ 和一个数 $X$。

对于任意的的 $i,j$，满足 $ 1\leq i,j\leq N $ 且 $A_i-A_j=X$，输出 `Yes`，否则输出 `No`。
## 分析
对于这道题，正解很多，本篇题解着重讲双指针做法。
### Part 0 坑点
我们来看看题目，发现有两个坑点需要注意。
- $i,j$ 可以相等
- $X$ 可能为负数

### Part 1 输入
可以看到数据范围为 $2\times 10^5$，建议用 `scanf` 或快读输入。
```cpp
scanf("%lld%lld",&n,&x);
for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
```

### Part 2 排序
从小到大排序和从大到小排序都可，为了简便，这里从大到小排序。
```cpp
sort(a+1,a+n+1);
```

### Part 3 双指针
左指针和右指针的初值为 $1$，这样也保证了 $i,j$ 可能相等。

判断相减的差要给 $X$ 带上绝对值，因为 $X$ 可能为负数。

代码讲解：
```cpp
while(l<=r&&r<=n)//条件：左指针要小于右指针，且都不能超过n
{
	if((a[r]-a[l])==abs(x))//差值为x的绝对值，输出Yes
	{
		cout<<"Yes";
		return 0;
	}
	else if(a[r]-a[l]<abs(x)) r++;//如果差值小了，让右指针加1
	else l++;//如果差值大了，让左指针加1
}
cout<<"No";//没有找到，输出No
```
## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,a[200100];
int main()
{
	scanf("%lld%lld",&n,&x);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	int l=1,r=1;
	sort(a+1,a+n+1);
	while(l<=r&&r<=n)
	{
		if((a[r]-a[l])==abs(x))
		{
			cout<<"Yes";
			return 0;
		}
		else if(a[r]-a[l]<abs(x)) r++;
		else l++;
	}
	cout<<"No";
   return 0;
}
```

---

## 作者：wangyinghao (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc296_c)

几乎跟 [P1102](https://www.luogu.com.cn/problem/P1102) 一模一样。

### 分析

对算式进行移项，将 $A_i-A_j=X$ 转换为 $X+A_j=A_i$。$X$  是已知的，因此我们对每一个 $A_j$，都去寻找一个对应的 $A_i$，如果有，就代表有满足 $A_i-A_j=X$ 的情况。

查找方面要用二分，懒得手写二分，这里介绍一个函数：$\texttt{binary\_search}$，使用方法如下：

此函数格式为 ```binary_search(first,last,val)```，可以查在 $\texttt{[first,last)}$ 区间里有没有 $\texttt{val}$，有则返回 $\texttt{true}$，无则返回 $\texttt{false}$。

$\texttt{val}$ 在此题对应的值是 $a_i+X$，把这个函数套进去，就做完了。

### AC Code

```cpp
#include<iostream>
#include<algorithm>//二分函数的头文件
using namespace std;
int a[200005];

int main(){
	int n,c,cnt=0;
	cin>>n>>c;//c代表x
	for(int i=1;i<=n;i++){
		cin>>a[i]; 
	}
	sort(a+1,a+n+1);//二分必须保证数组有序
	for(int i=1;i<=n;i++){//对每一个A_j进行枚举
		if(binary_search(a+1,a+n+1,a[i]+c)==true){//二分 判断
			cout<<"Yes";//找到一个数对 输出并结束程序
			return 0;
		}
	}
	cout<<"No";//没有这种数对
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 题意

给定 $N$ 个整数，求有多少个 $(i,j)$ 满足，$A_i-A_j=x$？

## 思路

如果我们用 $n^2$ 的复杂度暴力枚举每一个 $i,j$，肯定会超时。所以我们考虑将题目变式一下。因为 $A_i-A_j=x$，所以对于所有满足的 $(i,j)$，一定是有 $A_j=A_i+x$ 的。$A_j$ 的值一定是固定的，所以我们只需要枚举每个 $A_i$，看看是否存在一个 $A_j=A_i+x$。判断一个数是否存在，我们只需要开个 `map<int,int>` 来存就行了。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
int n,x;
int a[N];
map <int,int> mp;
signed main()
{
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a[i],mp[a[i]]=1;
	for(int i=1;i<=n;i++) if(mp[a[i]+x]) return cout<<"Yes",0;
	return cout<<"No",0;
}
```


---

## 作者：Crazyouth (赞：1)

**翻译**

给你 $n$ 个数的数组 $a$ 与正整数 $x$，问数组 $a$ 中有没有两个数的差为 $x$。
****
**分析**

**思路上大体分析**

一切题目的算法总是要基于朴素算法的。

本题朴素算法很明显，就是枚举出所有的差，找到 $x$ 或者宣布找不到 $x$。那我们可以想到，将差值排序是个不错的优化方式，但是差值的求出也要 $O(n^2)$，所以可以考虑排序数组 $a$。

我们将数组 $a$ 从小到大排序。定义两个指针 $head,tail$，求出 $a_{tail}-a_{head}$，假如这个值小于 $x$，我们就增加被减数，又因为数组 $a$ 排过序了，给 $tail$ 加一就行；假如这个值大于 $x$，我们就增加减数，$head$ 加一即可，原因同上；假如这个值等于 $x$，输出 `yes`。假如枚举完了也没有输出 `yes`，那就输出 `no`。

这个代码最优情况复杂度 $O(n \log n)$，最坏情况 $O(n^2)$，~~不过 AT 的数据里一向没有“最坏情况”。~~

**细节处理**

这题细节还是不可忽视的，作者因为细节问题吃罚时掉分掉惨了。

1. 如果 $x=0$，这题可以直接输出 `yes`，因为找相同的数相减就行了。
2. $x$ 一定要赋值为 $|x|$，不然按上述思路会 WA。
3. 上面的枚举条件有且仅有 `while(tail<=n)`，千万不要加上 `head<tail`，不然还是会出错。
---
**AC Code**
```
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int a[int(2e5+10)];
int main()
{
	int n,x;
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(x==0)//特判x=0
	{
		cout<<"Yes";
		return 0;
	}
	x=abs(x);//细节处理
	int head=1,tail=2;
	sort(a+1,a+n+1);//排序
	while(tail<=n)//循环枚举差值
	{
		if(a[tail]-a[head]==x)
		{
			cout<<"Yes";
			return 0;
		}
		if(a[tail]-a[head]<x)
		{
			tail++;
			continue;
		}
		if(a[tail]-a[head]>x)
		{
			head++;
			continue;
		}
	}
	cout<<"No";
	return 0;
}
```


---

## 作者：_shine_ (赞：1)

## 题目大意
现在有一个 $n$ 个数字的序列 $a$，现在问你在 $a$ 中，是否有两个数 $i,j\left ( 1\le i,j \le n \right ) $，使得 $a_i-a_j=x$。
## 思路
因为 $n$ 太大，不可能用暴力二层循环来解决，我们可以使用一个数组 $p$，其中，$p_i$ 表示数 $i$ 是否 出现，接下来，我们来化简公式。

$a_i-a_j=x$，其实在左右移项变号之后，就变成了 $a_i=x+a_j$，因此，我们可以枚举 $a_j$，判断是否有 $x+a_j=a_i$ 即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')w=-1;ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';
        ch=getchar();
    }
    return s*w;
}
inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)write(x/10);
    putchar(x % 10 + '0');
}//快读优化部分
int n,x;
int a[maxn],ans;
map<int,int>p;//使用图来存储数i是否出现
signed main(){
	n=read(),x=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
	}
	for(int i=1;i<=n;++i){
		p[a[i]]++;
	}
	for(int i=1;i<=n;++i){
		int sum=x+a[i];
		if(p[sum]!=0){
			puts("Yes");
			return 0;
		}//说明出现过
	}
	puts("No");//没有出现
	return 0;
}

```


---

## 作者：Bc2_ChickenDreamer (赞：1)

## AT_abc296_c [ABC296C] Gap Existence 题解

### 题目分析

二分练习题。我们先把数组排好序，并定义一个 $ans$ 保存答案。然后从 $1$ 枚举到 $n$，然后每次在 $a$ 数组里查找有多少个 $a_i + x$，并保存起止位置和终止位置。这里我用到了 $\text{lower\_bound}$ 和 $\text{upper\_bound}$，不知道的可以[参考这篇文章](https://www.cnblogs.com/cherishui/p/16924108.html)。如果起始位置 $\mathrlap{\,/}{= n + 1}$，就把 $ans$ 加上终止位置减去起始位置，否则把 $ans$ 加 $0$。然后遍历完之后判断 $ans$ 是否 $> 0$ 是则输出 `Yes`，否则输出 `No`。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define qwq ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
const int N = 200020;
int n, c, a[N], ans = 0;

int solve(int ans)
{
	int start = lower_bound(a + 1, a + n + 1, ans) - a;
	int last = upper_bound(a + 1, a + n + 1, ans) - a;
	if (start != n + 1)
		return last - start;
	else
		return 0;
}

signed main()
{
	qwq;
	cin >> n >> c;
	for (int i = 1; i <= n; ++ i)
	{
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++ i)
	{
		ans += solve(a[i] + c);
	}
	if (ans > 0)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	return 0;
}
```


---

## 作者：chlchl (赞：1)

~~（突然发现洛谷这边好像没 AC，赶紧先交一发）~~

## 题意简述
给定长度为 $n$ 的数组 $A=(A_1,A_2,\cdots,A_n)$ 和整数 $x$，问能否找到 $1\leq i,j\leq n$，满足 $a_i-a_j=x$。

注意 $i$ 和 $j$ 可以相等。

## Solution
$a_i-a_j=x$，我们可以转化为 $a_j=a_i-x$。固定 $i$，将数组排好序，直接二分数组中最接近 $a_i-x$ 的数 $b$，再判断差是否为 $x$ 即可。

找这个“最接近”可以转化为第一个不小于 $a_i-x$ 的数，使用 C++ 中的 `lower_bound` 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, x, a[N];

int main(){
	scanf("%d%d", &n, &x);
	for(int i=1;i<=n;i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	for(int i=1;i<=n;i++){
		int b = *lower_bound(a + 1, a + 1 + n, a[i] - x);
		if(a[i] - b == x)
			return printf("Yes\n"), 0;
	}
	printf("No\n");
	return 0;
}
```

---

## 作者：AKPC (赞：0)

水题，[类似的经典题目](https://www.luogu.com.cn/problem/P1102)。
### 题意
给出 $n$ 个数的数列 $a$ 和一个 $c$，求出 $n$ 个数中，有多少组 $(a_i,a_j)$ 满足 $a_i-a_j=c$ 且 $i > j$。
### 思路
根据类似的经典题可以得知，有两种做法：二分和 map。这里讲的是代码更简单的 map 做法。

统计每个数字出现的次数，遍历每个 $a_i$，求出有多少个数等于 $a_i-c$ 并加入答案，最后判断答案是否为 $0$，如果是，输出 No，反之输出 Yes。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,c,a[200005],ans=0;
unordered_map<int,int>t;
signed main(){
	cin>>n>>c;
	for (int i=0;i<n;i++) {cin>>a[i];t[a[i]]++;}
	for (int i=0;i<n;i++) ans+=t[a[i]-c];
	if (ans==0) cout<<"No";
	else cout<<"Yes";
	return 0;
}
```

---

## 作者：Butterfly___qwq (赞：0)

# 思路
一看数据范围，**惊**，还想写暴力，显然不行，于是换思路。下面给出一种思路，可以使用二分法，有人肯定问，两个序列还能二分套二分？这还能是比赛的第三题难度吗？这不是前两次的第六题吗？不，可以转换思路：
- 第一步，用 $O(n \log n)$ 的效率快速排序。
- 第二步，用 $O(n)$ 的效率把每个数 $a_i$ 扫一遍。
- 第三步，用 $O(\log n)$ 的效率在这个数组中寻找有没有 $x-a_i$ 这个数。
- 第四步，出结果。

综上所述，时间复杂度 $O(n \log n)$，可以通过本题。
# 代码：
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
	int n,x;
	cin>>n>>x;
	int a[888888];
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(binary_search(a+1,a+n+1,x-a[i])){
			cout<<"Yes"<<endl;
			return 0;
		}
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：_dijkstra_ (赞：0)

C 题，利用 STL 迅速解决。

## 思路

题目就是说，是否存在某个 $1 \le i,j\le n$ 满足 $a_j - a_i = x$。

简单变形： $a_j = a_i + x$。

所以我们可以考虑对每个 $(a_i + x)$ 标记一下，然后再扫一次数组，如果 $a_i$ 被标记过，说明存在 $a_j = a_i + x$。

唯一的问题是 $a_i$ 较大，可以使用 STL 中的 map 容器存储。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
map <int, bool> mp;
int a[200005];
int main()
{
	int n, x;
	scanf("%d%d", &n, &x);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), mp[a[i]] = true;
	for (int i = 1; i <= n; i++)
		if (mp.count(a[i] + x))
			return puts("Yes"), 0;
	puts("No");
	return 0;
}
```

---

## 作者：tkdqmx (赞：0)

## 题目大意

给定一个数组 $A$，求是否存在 $A_i-A_j=X$。

## 解题思路

可以将题目转换成求是否存在 $A_j=A_i+X$，就可以发现这是一道简单的二分搜索题。代码如下：

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,s[200005],x;
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++) cin>>s[i];
	sort(s+1,s+n+1);
	for(int i=n;i>0;i--){
		int l=1,r=n;
		while(l<=r){
			int mid=(l+r)>>1;
			if(s[mid]>s[i]-x) r=mid-1;
			else if(s[mid]==s[i]-x){
				cout<<"Yes";
				return 0;
			}
			else l=mid+1;
		}
	}
	cout<<"No";
} 
```


---

## 作者：LegendaryGrandmaster (赞：0)

这重题了吧。

[A-B 数对](https://www.luogu.com.cn/problem/P1102)

每次记录当前出现的数字，由于题目的等式可以变成 $A_i=X+A_j$，所以当某一个数加上 $X$ 存在这样的数的话，则满足条件。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
unordered_map<int,int> mp;
int a[200005],n,c,ans;
signed main()
{
	cin>>n>>c;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mp[a[i]]++;
	}
	for(int i=1;i<=n;i++)
		if(mp[a[i]+c]){
			puts("Yes");
			return 0;
		}
	puts("No");
}
```

---

## 作者：Loser_Syx (赞：0)

## 思路

可以用一个桶数组来存储每个值是否出现过。

但是数据范围 $-10^9 \leq A_i \leq 10^9$，这么的数据显然纯数组是建不下的，但是我们有万能的 STL：`map`。

很显然统计完是否出现后，再遍历一次数组，由于 $a_i + a_j = m$，那么 $m - a_i = a_j$，所以我们找到一个 $a_i$ 之后判定一下 $m - a_i$ 是否出现过即可。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
#define int long long
#define f(W, X, Y, Z) for(int W = X; W <= Y; W += Z)
#define F(W, X, Y, Z) for(int W = X; W >= Y; W -= Z)
#define debug puts("QAQ")
inline int read(){
	register int x = 0, s = 1;
	char c = getchar();
	while(c < '0' || c > '9'){
		if(c == '-') s = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		x = (x << 1) + (x << 3) + (c ^ '0');
		c = getchar();
	}
	return x * s;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9) write(x / 10);
	putchar((x % 10) + '0');
}
map<int,bool> MAP;
int a[200010];
signed main(){
	int n = read(), m = read();
	f(i, 1, n, 1){
		a[i] = read();
		MAP[a[i]] = 1;
	}
	f(i, 1, n, 1){
		if(MAP[a[i] - m]){
			puts("Yes");
			return 0;
		}
	}
	puts("No");
	return 0;
}
```

---

## 作者：Escapism (赞：0)

[一道极其相似的题目](https://www.luogu.com.cn/problem/P1102)

[ATC 原题](https://atcoder.jp/contests/abc296/tasks/abc296_c)

# 题意

给定一串数 $a_1$ 到 $a_n$，问是否存在 $i,j$ 使得 $a_i$ 与 $a_j$ 差为 $m$。

# 思路

### 二分

将这串数排个序，若 $i<j$，对于某一个 $a_i$ 来说，$a_{i+1},a_{i+2}....a_{n}$ 与 $a_i$ 之间的差必然**逐渐增大**。

这就满足了单调性，然后就可以二分了。枚举每一个 $a_i$，如果发现找到的 $a_j$ 的 $a_j-a_i>m$，就往前折半查找；如果发现 $a_j-a_i<m$，就往后折半查找；如果发现 $a_j-a_i=m$，直接输出 ``Yes``。如果从头至尾没有任何一个 $i$ 或 $j$ 满足条件，输出 ``No``。

时间复杂度 $O(n\log_2 n)$，可以通过。

### map

数组记录对于每一个 $a_i-m$，再用一个 ``map`` 记录每一个 $a_i$。

枚举数组中存储的每一个 $a_i-m$，如果有某一个 $a_i-m$ 存在于 ``map`` 中，就说明必然有一对 $a_i$ 和 $a_j$ 满足条件，输出 ``Yes``。如果没有找到，输出 ``No``。

# 代码

这份代码是 ``map`` 的 ``AC`` 代码。

[记录](https://atcoder.jp/contests/abc296/submissions/40297198)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
 
LL a[200005];
map<LL,LL> MP;
 
int main() {
    LL n,m;
    cin >> n >> m;
    for(int i = 1;i <= n;i++) {
        cin >> a[i];
        MP[a[i]]++;
        a[i] -= m;
    } 
    for(int i = 1;i <= n;i++){
      	if (MP[a[i]] == true){
          	cout<<"Yes";
          	return 0;
        }
    }
    cout<<"No";
    return 0;
}
```

这份代码是赛时调炸的二分代码，仅供参考。（赛时用 ``map`` 过的）

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 2 * 1e5 + 5;
int a[MAXN];
int n,m;
 
int main(){
    cin>>n>>m;
    for (int i = 1;i <= n;i++) cin>>a[i];
    if (m == 0){ //如果差为 0，只需要 i 和 j 相同就可以，直接输出 Yes。
        cout<<"Yes"<<endl;
        return 0;
    }
    sort(a + 1,a + n + 1); //排序
    for (int i = 1;i <= n;i++){
        int l = i,r = n;
        while(true){
            if (l >= r || l > n || l < 1 || r > n || r < 1) break; //不存在满足条件的数对，弹出
            int mid = (l + r) / 2 + 1; //折半
            if (a[mid] - a[i] == m){
                cout<<"Yes"<<endl;
                return 0;
            }
            //cout<<l<<" "<<r;
            if (a[mid] - a[i] > m) r = mid - 1; //折半
            if (a[mid] - a[i] < m) l = mid + 1;//折半
        }
    }
    cout<<"No"<<endl;
}
```


---

