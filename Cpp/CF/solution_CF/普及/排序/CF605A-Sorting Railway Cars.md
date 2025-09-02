# Sorting Railway Cars

## 题目描述

An infinitely long railway has a train consisting of $ n $ cars, numbered from $ 1 $ to $ n $ (the numbers of all the cars are distinct) and positioned in arbitrary order. David Blaine wants to sort the railway cars in the order of increasing numbers. In one move he can make one of the cars disappear from its place and teleport it either to the beginning of the train, or to the end of the train, at his desire. What is the minimum number of actions David Blaine needs to perform in order to sort the train?

## 说明/提示

In the first sample you need first to teleport the $ 4 $ -th car, and then the $ 5 $ -th car to the end of the train.

## 样例 #1

### 输入

```
5
4 1 2 5 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
4 1 3 2
```

### 输出

```
2
```

# 题解

## 作者：sxyugao (赞：18)

**题意**


一个数组的元素为1至N的整数，现在要对这个数组进行排序，在排序时只能将元素放在数组的头部或尾部，问至少需要移动多少个数字，才能完成整个排序过程？


**输入**


第1行：1个数N(2 <= N <= 50000)。

第2 - N + 1行：每行1个数，对应排列中的元素。


**输出**


输出1个数，对应所需的最少移动次数。


**算法**


我们先不管初始序列，先看结果：一个1..n的整数序列，相邻的项差为1。


再看原序列，我们发现在此之中一开始就满足以上条件的子序列不需要移动，于是可以转化为类似最长上升子序列的模型，答案即为（总长度-最长序列的长度）。


但是n^2的时间复杂度还是难以承受，我们发现每次我们只是为了找上一个自然数，却花了O(n)的时间，再观察n最大只有50000，于是想到用桶标记，然后就愉快的AC了。  (￣▽￣)~\*


以下为代码：

```cpp
#include<cstdio>
int n,a,ans,f[500001];
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a);
        f[a]=f[a-1]+1;
        if(f[a]>ans)ans=f[a];
    }
    printf("%d",n-ans);
}
```

---

## 作者：_32bit_Silentnight (赞：7)

### [题目传送门](https://luogu.com.cn/problem/CF605A)
题目要用最少的操作次数使得数据为**单调上升序列**（我们使不进行移动的数字数量最大化）。

怎么让移动的次数最少呢？

我们用一个极端的样例试一试：

```cpp
输入    输出
5		4
5
4
3
2
1
```

简述一下移动过程：
$$5\space4\space3\space2\space 1 \Rightarrow 5\space4\space3\space1\space 2 \Rightarrow5\space4\space1\space2\space 3 \Rightarrow 5\space1\space2\space3\space 4 \Rightarrow1\space2\space3\space4\space 5 $$
4 次。

所以，最多的移动次数为 $n-1$ 次！

但是有一些特殊的，例如下面的：1 8 4 2 7 3
$$1\space8\space4\space2\space7\space3 \Rightarrow 1\space8\space2\space7\space3\space4\Rightarrow1\space8\space2\space3\space4\space7\Rightarrow1\space2\space3\space4\space7\space8 $$

3 次？！

为什么呢？1 2 3 可以永远不动，只需要 4 7 8 挨个往后移！ 

**所以，次数为：$n$ 减挨个上升的“子序列”的长度！**

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b[200001]={0},i,m=-1,k=0,x;scanf("%d",&a);//定义变量。
   /*
   为什么要 b[200001]={0}？因为：第 8 句涉及到 b[0]。
   m=-1 是保险起见。
   */
	for(i=1;i<=a;i++){
		cin>>x;
		b[x]=b[x-1]+1;//关键，求“最长上升子序列”。
		m=max(m,b[x]);//更新。
	}
	cout<<a-m;
}
```

~~重题 AT_agc024_b~~~~

---

## 作者：1qaz234Q (赞：2)

### 题意简述
有一列有 $n$ 节车厢组成的火车，车厢的编号由 $1$ 到 $n$ 排列。每次操作把这列火车中的一节车厢移动到这列火车的开头或结尾。求让火车车厢编号从小到大排列的最小操作次数。
### 题目分析
这道题要使用动态规划算法。

为了让移动尽可能少，我们就要让不需移动的车厢尽可能多。不难发现，不需移动的车厢数就是车厢编号的最长上升子序列的长度。

因为车厢编号都是由 $1$ 到 $n$ 排列的，所以动态规划的状态转移方程为 $f_p=f_{p-1}+1$，$f_i$ 表示以 $i$ 为结尾的最长上升子序列的长度，边界条件为 $f_1=1$。

令车厢编号的最长上升子序列的长度为 $maxn$，那么 $maxn=\max(f_i)$。最后计算出需要移动的车厢数，也就是 $n-maxn$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int f[N];
int main(){
	int n;
	int maxn=0;//最长上升子序列的长度
	cin>>n;
	for(int i=1;i<=n;i++){
		int p;
		cin>>p;
		if(p==1){
			f[1]=1;//边界条件，以1为结尾的最长上升子序列的长度为1 
		}
		else{
			f[p]=f[p-1]+1;//转移方程，以p-1为结尾的最长上升子序列的长度加上1就是p的最长上升子序列的长度
		}
		maxn=max(maxn,f[p]);//更新最长上升子序列的长度
	}
	int ans=n-maxn;//求出最小操作次数 
	cout<<ans;
}
```

---

## 作者：Scorilon (赞：1)

To [CF](https://codeforces.com/problemset/problem/605/A)

这道题依题意可得最终答案为序列长度-最长子序列长度。

数据范围至 $100000$ 用 $O(n^2)$ 的复杂度肯定会炸。

用 $O(nlogn)$ 的复杂度却在第 $21$ 个测试点莫名出错。

于是换一种思路可得 $dp[s]=dp[s-1]+1$ 即类似于求最长子序列长度。

最后用序列长度-最长子序列长度即为答案。

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n;
int s;
int dp[100005];
int ans;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&s);
		dp[s]=dp[s-1]+1;
		ans=max(ans,dp[s]);//最长子序列长度
	}
	printf("%d",n-ans);//序列长度减去最长子序列长度
	return 0;
}
```


---

## 作者：Fengyiwei1234 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF605A)

# 思路

我们考虑那些不用改的数字。

他们不用改，说明原来他们就是单调上升的，也就是上升子序列。

而为了改动最少，所以不用改的要尽量多，也就是最长上升子序列。

所以答案就是（总长度减去最长上升子序列的长度）。

动归求一下最长上升子序列的长度即可。

AC 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int x,n,dp[100009],ans=-1;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        dp[x]=dp[x-1]+1;
        ans=max(ans,dp[x]);
    }
    cout<<n-ans<<endl;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/109851666)

---

## 作者：COsm0s (赞：0)

## 题意：

给出一个 $1$ 到 $n$ 的排列，每次操作可以将某个位置的数字移动到最前面或最后面，求将排列从小到大排序的最小操作次数。

## 思路

动态规划。

移动尽可能少，那么就是没移动的越多越好。

那什么情况下不用移动的最多呢？

因为是 $1-n$ 的排列，所以很容易想到**最大上升子序列**。

考虑 dp 转移：设 $dp_i$ 为以 $i$ 为终点的最大上升子序列长度。那么可以得到：

$dp_{a_i}=dp_{a_i-1}$。

答案即为序列长度减去 $\max(dp_{a_i})$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a, ans, f[500001];
signed main(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a;
        f[a] = f[a - 1] + 1;
        if(f[a] > ans) ans = f[a];
    }
    cout << n - ans;
}
```


---

## 作者：Huhu12346 (赞：0)

大水题！

本题思路：观察对比可以：一个 $1$，$2$，$3$ …… $n$ 的整数序列，相邻的项差为 $1$。

再回到原序列，我们发现序列不需要移动，于是可以转化为类似最长不下降（上升）子序列的模型，可以推出（总长度减去最长序列的长度），就结束了。

下面奉上我的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a, ans, cnt1[500010];
int main()
{
    cin >> n;
    memset(cnt1, 0, sizeof(cnt1));
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        cnt1[a] = cnt1[a - 1] + 1;//状态转移
        if (cnt1[a] > ans)
        {
            ans = cnt1[a];
        }
    }
    cout << n - ans << endl;//输出最少操作次数
}
```



---

## 作者：Chicken_Rrog (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF605A)

## 题意
给出一个有 $n$ 个元素的序列，要给序列排序，要求每个操作只能将一个数移动到最前面或者最后面，求最少的操作次数。
## 思路
只有一个数本身就在他的相对位置上，它才不会改变，让我们看一组样例：

```latex
2 5 3 4 1 
```
我们发现在原数组中 $2$ 不在它的相对位置上，但是仍然可以不用改动？
因为 $1$ 的改动使得 $2$ 的位置也发生了改动。
而如果我们处理这种大量的改动，恐怕很难在规定的时限算出来。


------------
那么换一种思路来思考，如果有些数本来就排好了序呢？
在上一个样例中，我们可以发现如果扔掉   $5,1$  ，原序列就会变成 $2,3,4$ ，而这个序列是有序的！
那么在修改时就可以不动 $2,3,4$ 而只对 $1,5$ 进行修改就可以了。
除此之外我们还发现了另一个有趣的东西。
如果遵循上述思路，我们就可以先把排序过程视为拿出所有的数，放进一个新序列里。
然后我们发现有些数在拿出一部分数后自己就变得有序了。
而这些数就成为了一个连续的序列？！
让我用一个样例解释一下：
```latex
5 7 9 10 11 8 6 4 1 3 2
```
不难发现这个东西里最长的连续上升序列是 $9,10,11$ ，那么我们不需要动他们，拿出其他的所有数，挨个放进去就好了，
所以我们发现这道题其实就是先将原来的数离散化处理，然后使用 $O(n)$ 的算法求出最长连续上升子序列，那么这个题我们就证完了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,mx=-1;
long long a[100005],f[100005];
int search1(int s){
	long long l=1,r=n,mid;
	while(l<=r){
		mid=(l+r)/2;
		if(f[mid]==s){
			return mid;
		}
		if(f[mid]<s) l=mid+1;
		else r=mid-1; }
	return r;
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
	scanf("%lld",&a[i]);
	f[i]=a[i];
        }
	sort(f+1,f+1+n);
	for(int i=1;i<=n;i++){
	a[i]=search1(a[i]);//离散化。
	}
    	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++){//求最长连续上升子序列。
        f[a[i]]=f[a[i]-1]+1;
        mx=max(mx,f[a[i]]);
    	}
	printf("%lld\n",n-mx);
	return 0;
}
```


---

## 作者：cxy000 (赞：0)

由于这道题是可以将数列内任意位置的数放置在最前或最后，又因为是要求从小到大，所以我们只需要求出数列原本的最长递增子序列即可。

又因为数列是由 $1$ 到 $n$，所以我们可以发现状态转移方程为：

```cpp
d[a[i]]=d[a[i]-1]+1; //a[i]是输入的数
```

最后再用一个变量存储最长子序列即可。

注意：答案是输出个数减去存储最长递增子序列长度的变量。

## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100100];
int dp[100010];
int ans;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		dp[a[i]]=dp[a[i]-1]+1;
		ans=max(ans,dp[a[i]]);
	}
	cout<<n-ans;
	return 0;
}
```


---

## 作者：猜一猜我是谁 (赞：0)

# 题意简述
一个长度为 $n$ 的数组，是 $1$ 到 $n$ 的一种排列，要求每次操作把其中一个数提到数组的最前或最后，问至少需要几次操作。

# 思路
先看看样例 $1$，数组为 $\{4,1,2,5,3\}$，把 $4$ 和 $5$ 分别放到最后即可。可以发现没移动的 $3$ 个数 $\{1,2,3\}$ 为相邻元素差为 $1$ 的**最长上升子序列**。

那么就可以用 $dp$ 思想，开一个长度为 $n$ 的桶，$dp_i$ 就表示以第 $i$ 个元素结尾的最长上升子序列长度，每次输入 $a_i$，那么 $dp_{a_{i}}=dp_{a_{i}-1}+1$，并统计所有 $dp_{a_i}$ 的最大值，答案即为 $n-\max(dp_{a_i})$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,a[100005],dp[100005];
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
        dp[a[i]]=dp[a[i]-1]+1;
        ans=max(dp[a[i]],ans);//统计最大值
    }
    cout<<n-ans;
}
```

---

## 作者：pengzy (赞：0)

### 题意：

有一个长度为 $n$ 的序列是 $1$ 到 $n$ 的任意顺序 **排列**。定义一次操作可以将任意一个数移到排列最前或最后，问至少多少次操作可以使得它变成一个 **严格单调递增的$1$到$n$的排列**。

### 思路：

根据样例，可以发现每一次 **最优** 操作都是把那些插在 **最长上升子序列（此处要求元素之差正好为1）** 中的所有数都移到排列的头或尾。小就移到头，大就移到尾。所以，我们可以采用 $dp$ 思想，开一个长度为 $n$ 的桶，$dp_{i}$ 表示最后一个元素为 $i$ 的 **最长上升子序列** 的长度。每一次输入第 $i$ 元素，以它为最后一个元素的最长上升子序列的长度，就是 $dp_{i-1}+1$，表示是它前一个比它小 $1$ 的最长上升相差为 $1$ 子序列的长度加一，因为加入了 $i$ 这个元素。每一次循环同时更新答案，取最长的满足要求的子序列。最后的答案就是 $n-len$，因为中间那些连不上的元素总能前移或后移达到目的。

不懂可以回复。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}
const int MAX=1e5+5;
int n,x,dp[MAX],ans=-1;
int main()
{
	n=read();
	for(int i=1;i<=n;i++) {
		x=read();
		dp[x]=dp[x-1]+1;
		ans=max(ans,dp[x]);
	}
	cout<<n-ans;
	return 0;
}
```

---

## 作者：一只大龙猫 (赞：0)

这是一篇 **Python** 题解。

我们可以换个角度来看这道题：

这道题其实就是从序列中挑出一些数，将它们移动到最前面或最后面，**使剩下的没有移动的数最多**。

不难发现，剩下的肯定是原序列的一个子序列，因为排序后要满足序列为从 $1$ 到 $n$ 严格单调递增，所以这个剩下的子序列肯定为一个**公差为 $1$ 的严格递增的等差数列**。

例如，如果这个子序列第一个数为 $l$，最后一个数为 $r$ 的话，那么这个子序列为

$$l,l+1,l+2,...,r-2,r-1-r$$

我们可以用动态规划去做这道题。

如果 $x-1$ 在 $x$ 前面，这时 $x$ 就可以连到 $x-1$ 所在的子序列，即 $f(x)=f(x-1)+1$；

否则，$x$ 就只能是在一个新的子序列里，即 $f(x)=1$。

算出了最多能剩下的数，就很容易能求出最少要操作多少次了。

代码如下。

```python
n=int(input())
f={} #在这里使用字典来代替C++中的数组
ans=0
p=list(map(int,input().split()))
for i in p:
    if f.__contains__(i-1): #判断i-1是否在字典f中，即i-1是否在i的前面
        f[i]=f[i-1]+1
    else:
        f[i]=1
    if f[i]>ans:
        ans=f[i]
print(n-ans) #ans为最多能剩下的数，n-ans即最少的操作次数
```

另：中文注释会导致程序编译错误，请不要问有关程序编译错误的问题。

---

