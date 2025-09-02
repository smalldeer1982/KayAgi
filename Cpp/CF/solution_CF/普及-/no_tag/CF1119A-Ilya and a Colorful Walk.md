# Ilya and a Colorful Walk

## 题目描述

ilya 有很多房子，每个房子都有一个颜色。因为 ilya 喜欢散步，所以想要选最远的两个不同颜色的房子作为散步的起点和终点。输出这个最远距离。

## 样例 #1

### 输入

```
5
1 2 3 2 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3
1 2 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7
1 1 3 1 1 1 1
```

### 输出

```
4
```

# 题解

## 作者：yuy_ (赞：3)

## Udp：修改了代码效率（加了两个break）

~~看完样例就可以想到：~~

### 答案肯定包括第一座房子和最后一座房子。

简单证明一下。

#### 如果存在某个方案是选择 $a_i$ 和 $a_j$ $(1<i<j<n,c_i!=c_j)$ 的

#### 那么

#### 如果 $a_1$ 和 $a_i$ 颜色一样，那 $a_1$ 和 $a_j$ 这个方案更优。

#### 如果 $a_1$ 和 $a_i$ 颜色不一样，并且 $a_1$ 和 $a_j$ 颜色也不一样，那 $a_1$ 和 $a_j$ 这个方案更优。

#### 如果 $a_j$ 和 $a_n$ 颜色一样，那 $a_i$ 和 $a_n$ 这个方案更优。

#### 如果 $a_j$ 和 $a_n$ 颜色不一样，并且 $a_i$ 和 $a_n$ 颜色也不一样，那 $a_i$ 和 $a_n$ 这个方案更优。

#### 如果 $a_1$ 和 $a_j$ 颜色一样 并且 $a_i$ 和 $a_n$ 颜色一样呢？

#### 那么因为 $a_i$ 与 $a_j$ 颜色不一样所以 $a_1$ 与 $a_n$ 颜色也不一样啊！那没有比 “$a_1$ 和 $a_n$”  这个方案更好的方案了。

### code：

```cpp

#include<cstdio>
#include<cstring>
#define LL long long
#define Set(s,v) memset(s,v,sizeof(s))
using namespace std;
inline LL read(){
    LL ans=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch=getchar();}
    while(ch>='0'&&ch<='9'){ans=ans*10+ch-48;ch=getchar();}
    return ans*f;
}
void write(LL x){
    if(x<0){putchar('-');x=-x;}
    if(x>9){write(x/10);}
    putchar(x%10|48);
}
int n;
int a[300005];
int dis=-1;
int main(){
    n=read();
    for (int i=1;i<=n;i++){
        a[i]=read();
    }
    for (int i=n;i>1;i--){
        if(a[i]!=a[1]&&(i-1)>dis){
            dis=i-1;
            break;
        }
    }
    for (int i=1;i<n;i++){
        if(a[i]!=a[n]&&(n-i)>dis){
            dis=n-i;
            break;
        }
    }
    write(dis);
    puts("");
    return 0;
}

```

---

## 作者：Eason_AC (赞：2)

## Content
有一个长度为 $n$ 的数组 $a_1,a_2,a_3,...,a_n$，试求出两个不相等的数之间的距离的最大值。

**数据范围：$3\leqslant n\leqslant 3\times 10^5,1\leqslant a_i\leqslant n$。**
## Solution
弄两个指针 $l,r$，一开始将它们分别定为 $1,n$，然后分两次操作，第一次只将 $l$ 向右移，第二次只将 $r$ 向左移，直到 $a_l\neq a_r$ 为止，然后再求出这两次操作后距离之间的较大值。
## Code
```cpp
int n, a[300007], l, r, ans;

int main() {
	getint(n);
	_for(i, 1, n)	getint(a[i]);
	l = 1, r = n;
	while(l < r && a[l] == a[r])	l++;
	ans = r - l;
	l = 1, r = n;
	while(l < r && a[l] == a[r])	r--;
	ans = max(ans, r - l);
	writeint(ans);
	return 0;
}
```

---

## 作者：安舒阳 (赞：1)

本题的重点在于一个性质：**在答案大于零时组成答案的起点或终点必定是第一个或者最后一个建筑物**。

（观前提示：下文中的不等于首项或不等于末项是指**不等于首相或不等于末项或不等于首项和末项**，而不是同时不等于首相和末项）

证明的话我们将这个东西数学化一下：对于数列中的一个数字 $a_i$，它如果不等于首相或末项，那么以它在内答案一定和首相或末项有关，这点很好理解。唯一需要考虑的是如果他等于首相或末项怎么办？这种情况下他就**一定不是正确答案**（在此排除整个序列全相等答案为零的情况），我们可以设有一个数 $a_{i+1}$ 不等于首相或末项，**那么 $i+1$ 与首相和末项组成的答案中的一个一定比 $i$ 组成的要大**（在此处是 $+1$，故应为与首项组成的答案大）。

数据全输入进来跑一遍就好。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	//输入 
	int n;
	scanf("%d",&n);
	int data[300005];
	for(int i=0;i<n;i++){
		scanf("%d",&data[i]);
	}
	
	//判定 
	int ans=0;
	for(int i=1;i<n;i++){
		if(data[i]!=data[0]){
			ans=max(ans,i);
		}
	}//以首项为答案
	for(int i=n-2;i>=0;i--){
		if(data[i]!=data[n-1]){
			ans=max(ans,n-1-i);
		}
	}//以末项为答案
	printf("%d",ans);
	return 0;
}
```


---

## 作者：_Glassy_Sky_ (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1119A)

这道题目一到手，我首先想到的就是两重爆搜。先在输入过程中进行一个特判，判断如果所有的颜色都一样，输出 $0$ 并结束程序。否则用 $l$ 模拟左端点，用 $r$ 模拟右端点，依次搜索每一小段，如果左端点和右端点的颜色不一样，就用 $ans$ 来维护此时的最大值，最后输出答案。

具体代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 5;
int a[MAXN];
int main()
{
	int n, ans = 0, sum = 0;
	cin >> n;
	cin >> a[1]; 
	for(int i = 2; i <= n; i ++)
	{
		cin >> a[i];
		if(a[i] == a[i - 1])//特判统计 
			sum ++;
	}
	if(sum == n - 1)//特判全部一样的情况 
	{
		cout << 0;
		return 0;
	}
	for(int l = 1; l <= n; l ++)//两层爆搜 
		for(int r = l; r <= n; r ++)
			if(a[l] != a[r])
				ans = max(ans, r - l);
	cout << ans;
	return 0;
}
```
但是这份代码交上去是会 [TLE](https://www.luogu.com.cn/record/120976568) 的，为什么？因为 $n$ 的范围高达 $300000$，而我们还用了两重循环！于是，现在改进的方法只有将两重循环变成一重循环，并且还要使长度最长。顺着这个思路，我们很容易就想到答案一定包含第一个房子或者最后一个房子，甚至两者都囊括！所以我们就把问题简化成了两个一重循环，一个从头上扫，遇到不一样的，就与之前的最大值比较取最大值。一个从尾巴上扫，原理和之前一样。最后输出两者最大值就好了。下面详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 5;
int a[MAXN];
int main()
{
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int n, sum = 0, ansl = 0, ansr = 0, ans = 0;
	cin >> n;
	for(int i = 1; i <= n; i ++)
	{
		cin >> a[i];
		if(a[i] == a[i - 1])
			sum ++;
	}
	if(sum == n - 1)//还是特判 
	{
		cout << 0;
		return 0;
	}
	for(int l = 1; l <= n; l ++)//从前往后扫 
		if(a[l] != a[n])
			ansl = max(ansl, n - l);
	for(int r = n; r >= 1; r --)//从后往前扫 
		if(a[r] != a[1])
			ansr = max(ansr, r - 1);
	ans = max(ansl, ansr);//两者最大值 
	cout << ans;
	return 0;
}

```
放一个 [AC](https://www.luogu.com.cn/record/120977315) 凭据吧。

---

## 作者：liruixiong0101 (赞：0)

## P0 前置知识：
贪心，一点点数学。

## P1 题意：
给你 $n$ 和 $n$ 个数 $a_1,a_2,\dots,a_n$，让你求出 $\max\{a_i-a_j\}(1\le i\lt j\le n,a_i\neq a_j)$。

## P2 思路：
本题有两种做法。

### 第一种做法：
第一种做法就是贪心，由于需要让两个数的距离最远且不相等，若不考虑不相等的条件，肯定是要让初始位置最小，最终位置最大。  

---

设 $c_{0,i}$ 为 $a_j=i$ 的 最小的 $j$，$c_{1,i}$ 为最大的 $j$。  
那么不考虑不相等的条件的话，答案就是 $\max\{c_{1,i}\}-\max\{c_{1,j}\}(i\le m,j\le m)$（$m$ 为 $a$ 数组去重后的种类数）。

---

如果考虑不相等的条件的话，就要判断 $\max\{c_{1,i}\}$ 的 $i$ 不等于 $\max\{c_{1,j}\}$ 的 $j$ 即可。实现这样的操作可以用结构体加排序解决。

<https://codeforces.com/problemset/submission/1119/209101521>

### 第二种做法：
考虑最极端情况答案最大为 $n-1$，但前提是 $a_1\neq a_n$。  
若 $a_1 = a_n$ 怎么办呢？  
手造几个 $a_1\neq a_n$ 的样例可以发现答案的最大值的左右端点总是包含 $a_1$ 或 $a_n$，我们猜测答案的左右端点一定包含 $a_1$ 或 $a_n$，我们需要证明这一点。

---

若答案区间为 $[i,j](i\neq 1,j\neq n)$。  
我们考虑把 $i$ 挪到 $1$ 的位置，若 $a_1\neq a_i$ 的话，答案显然比 $[i,j]$ 好，若 $a_1=a_i$，因为 $a_i\neq a_j,a_1\neq a_n,a_1=a_i$ 所以 $a_i\neq a_n$ 这样的答案也一定比 $[i,j]$ 好，所以我们的猜想成立。  

---

接下来代码就很好写了。

<https://codeforces.com/problemset/submission/1119/209073882>

---

## 作者：xuhanxi_dada117 (赞：0)

[题目大意&题目传送门](https://www.luogu.com.cn/problem/CF1119A)

# 解法

## 猜想：答案区间包含 $1$ 或 $n$。

## 证明：

+ $a_1 \neq a_n$

取第一个和最后一个即可，答案为 $n-1$。

+ $a_1 = a_n$

考虑可行区间 $i,j$：$a_i\neq a_j$。

1. $a_1=a_n=a_j$：区间 $i,n$ 明显更优。

2. $a_1=a_n=a_i$：区间 $1,j$ 明显更优。

3. $a_1=a_n\neq a_i,a_j$：区间 $1,j$ 与 $i,n$ 明显更优。

得证。

从前向后，从后向前各扫一遍即可。

时间复杂度 $\Theta(n)$。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[300010];
int main(){
	cin>>n;int ans=-1;
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=n;i>=1;--i)
		if(a[i]!=a[1]){
			ans=max(ans,i-1);break;
		}
	for(int i=1;i<=n;++i)
		if(a[i]!=a[n]){
			ans=max(ans,n-i);break;
		}
	cout<<ans;
	return 0;
}

```

[AC 记录](https://www.luogu.com.cn/record/112194553)



---

## 作者：Lyrella (赞：0)

# 题意

找两个点 $i$ 和 $j$，满足 $color_i \neq color_j$ 且 $\mid i-j\mid$ 最大。

# 猜想

最优点必定**包括** $1$ 或 $n$。

# 证明

设最优点为 $i$ 和 $j$ $(i < j)$ 且 $i\neq 1,j\neq n$。

## 如果 $color_1\neq color_n$：

最优点就为 $1$ 和 $n$，假设不成立。

## 如果 $color_1=color_n$：

1. $color_1=color_n=color_i\neq color_j$：

> 则最优点就为 $1$ 和 $j$，假设不成立。

2. $color_1=color_n=color_j\neq color_i$：

> 则最优点就为 $i$ 和 $n$，假设不成立。

3. $color_1=color_n\neq color_i\neq color_j$：

> 则最优点就为 $\max(j-1,n-i)$，假设不成立。

# 思路

直接两次循环跑 $1$ 到 $i$ 和 $j$ 到 $n$。最后取最大值即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int n, a[N], ans1, ans2;
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)scanf("%d", &a[i]);
	int i = n;
	while(a[i] == a[1] and i > 1)i--;
	ans1 = i - 1;
	i = 1;
	while(a[i] == a[n] and i < n)i++;
	ans2 = n - i;
	cout << max(ans1, ans2);
	return 0;
}
```

---

## 作者：_lmz_ (赞：0)

## 简化题意：
给出一个数组 $a$，求这个数组中值不相同的两个元素的下标之差的最小值。
## 解题思路：
我们可以发现，其实就是让两个元素左边的那个最左，右边那个最右。

我们定义两个游标 $l$ 和 $r$，如果 $a_l$ 等于 $a_r$，就继续将 $l \gets l+1$，直到 $a_l$ 不等于 $a_r$ 了，就把 $r-l$ 的值存下来，即两个元素指尖的距离。

还要再从右边开始枚举一次，和上一次的操作差不多，只是把 $l \gets l+1$ 改成 $r \gets r+1$。

最后在两次枚举的值取最大值，就是我们最后的答案。

---

## 作者：Colead (赞：0)

【一片良心到初学OI一星期的新手都可以看懂的题解】

#### CF1119A

说是一条街上求最远的两栋不同颜色的房子，实质上就是求一个数组里面**最远的两个不同元素的距离**。

提出猜想：先从最后一个开始往前搜，搜到第一个和 $a[1]$ 不同的点就求距离 $ans1$ ，

然后从第一个往后搜，搜到第一个和 $a[n]$ 不同的点就求距离 $ans2$。

$ans1$ 和 $ans2$ 之中小的那个就是我们的答案 $ans$.

[**猜想是对的！（AC记录）**](https://www.luogu.com.cn/record/53435249)

接下来应该证明一下这个猜想。

假设我们有这样一条街：

red/ red/ blue/ green/ red/ blue /red/ red

那么肉眼可见 $ans1=ans2=ans=5$

以**从左向右搜**为例：

如果 $a[1]$ 和 $a[2]$ 同色，那么目标点到 $a[1]$ 的距离一定比到 $a[2]$ 的距离大1.

如果 $a[1]$ 和 $a[2]$ 异色，只有在数列末尾连续出现多个和 $a[1]$ 一样颜色的方格时，会导致 $ans1$ **不是真正的最小值**。但这时 $a[n]$ 一定和 $a[1]$ 同色，也就是说 $a[2]$ 与 $a[n]$ **一定异色**,则 $ans2$ 一定可以代替 $ans1$ 取到最大值。

证完了，不上代码怎么行？

```
void solve()
{
   cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	int ans1=0,ans2=0;
	for(int i=n;i>=1;i--)
	{
		if(a[i]!=a[1])
		{
			ans1=i-1;
			break;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=a[n])
		{
			ans2=n-i;
			break;
		}
	}
	cout<<max(ans1,ans2)<<endl;
}
```

再见啦~

---

## 作者：京润 (赞：0)

## CF1119A 【Ilya and a Colorful Walk】
### 明确：

1、题意翻译是错的，应该输出最大距离。


2、贪心思想：既然要求两个数不相同且下标相距最远，那么我们就进行两次遍历，一遍从左往右，一遍从右往左，（具体可参见代码）比较两次的答案，输出最大值即可。

3、具体做法：
首先设两个变量l，r作为遍历的房子编号，以从左往右为例，只要l与r所对应的房子颜色相同，则l++，直到第一次出现l与r所对应的房子颜色不相同为止，此时记录ans=r-l；

### 代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[300300],n,ans=0;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int l=1,r=n;
	while(a[l]==a[r])	//从左往右
	{
		l++;
	}
	ans=r-l;
	l=1;			//重新赋值
	while(a[l]==a[r])	//从右往左
	{
		r--;
	}
	ans=max(ans,r-l);
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：xht (赞：0)

题目地址：[CF1119A Ilya and a Colorful Walk](https://www.luogu.org/problemnew/show/CF1119A)

$O(n^2)$ 肯定过不掉

记 $p_i$ 为**从下标 $1$ 开始连续出现 $i$ 的个数**

那么对于每一个 $i$ ，在 $i$ 之前离 $i$ 最远的与 $a_i$ 不同的数的距离显然为 $i-p_{a_i}-1$ 。

取 $max$ 就好了

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 6;
int n, a[N], p[N], ans;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        if (p[a[i]] == i - 1) p[a[i]] = i;
    for (int i = 1; i <= n; i++)
        ans = max(ans, i - p[a[i]] - 1);
    cout << ans << endl;
    return 0;
}
```

---

## 作者：xh39 (赞：0)

题目真啰嗦......题目大意就是:给你一个数组,让你找出两个不同的元素,并让它们的下标差距最大。

思路(有点难理解):这两个元素一定会有一个在边上。证明方法如下(必须自己用笔画一下)。

假设这两个元素都在中间,值为a或b,由此可知a肯定和b不一样,而如果在中间,说明最左边一定和b一样(如果不一样就与假设矛盾,因为就可以从第一个到b了),同理,最右边也一定是a。

此时数组的情况
```cpp
{b,xxx,a,xxx,b,xxx,a}
```
于是从数组可以发现:这两个元素是第一个和最后一个。与假设矛盾。

∴代码=
```cpp
#include<bits/stdc++.h>
using namespace std;
long long c[570000];
int main(){
    int n,Max=0,i;
    cin>>n;
    int l,r;
    for(i=1;i<=n;i++){
        cin>>c[i];
    }
    for(i=1;i<n;i++){
        if(c[n]!=c[i]){
            l=n-i;
            break;//找到了。
        }
    }
    for(i=n;i>=2;i--){
        if(c[1]!=c[i]){
            r=i-1;
            break;
        }
    }
    cout<<max(l,r);//取最大值很关键。
    return 0;
}
```

---

