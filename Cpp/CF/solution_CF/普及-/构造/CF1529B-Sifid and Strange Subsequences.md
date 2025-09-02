# Sifid and Strange Subsequences

## 题目描述

A sequence $ (b_1, b_2, \ldots, b_k) $ is called strange, if the absolute difference between any pair of its elements is greater than or equal to the maximum element in the sequence. Formally speaking, it's strange if for every pair $ (i, j) $ with $ 1 \le i<j \le k $ , we have $ |a_i-a_j|\geq MAX $ , where $ MAX $ is the largest element of the sequence. In particular, any sequence of length at most $ 1 $ is strange.

For example, the sequences $ (-2021, -1, -1, -1) $ and $ (-1, 0, 1) $ are strange, but $ (3, 0, 1) $ is not, because $ |0 - 1| < 3 $ .

Sifid has an array $ a $ of $ n $ integers. Sifid likes everything big, so among all the strange subsequences of $ a $ , he wants to find the length of the longest one. Can you help him?

A sequence $ c $ is a subsequence of an array $ d $ if $ c $ can be obtained from $ d $ by deletion of several (possibly, zero or all) elements.

## 说明/提示

In the first test case, one of the longest strange subsequences is $ (a_1, a_2, a_3, a_4) $

In the second test case, one of the longest strange subsequences is $ (a_1, a_3, a_4, a_5, a_7) $ .

In the third test case, one of the longest strange subsequences is $ (a_1, a_3, a_4, a_5) $ .

In the fourth test case, one of the longest strange subsequences is $ (a_2) $ .

In the fifth test case, one of the longest strange subsequences is $ (a_1, a_2, a_4) $ .

## 样例 #1

### 输入

```
6
4
-1 -2 0 0
7
-3 4 -2 0 -4 6 1
5
0 5 -3 2 -5
3
2 3 1
4
-3 0 2 0
6
-3 -2 -1 1 1 1```

### 输出

```
4
5
4
1
3
4```

# 题解

## 作者：iMya_nlgau (赞：3)

### 题目大意

给你一个序列 $a$，求一个子集 $S$，使对于任意 $a_i,a_j\in S$，有 $|a_i-a_j|\ge MAX$，$MAX$ 表示 $S$ 内元素最大值，输出元素个数。

### 思路

设序列的最大值为 $a_{p}$，则对于任意 $i\neq p$ 应该有 $a_p-a_i\geq a_p$ 即 $a_i\leq 0$。也就是说，选出的序列中至多有一个数大于零。显然所有小于等于零的数都是可以选的，然后再判断一下能否选上最小的正数。

具体地，设小于等于零的数个数为 $num$，所有小于等于零的数里最小的 $|a_i-a_j|$ 为 $mn$，若存在大于零的数且最小的正数小于等于 $mn$，答案为 $num+1$，否则答案为 $num$。

[代码实现](https://www.luogu.com.cn/paste/j6kmtgiu)

---

## 作者：filletoto (赞：2)

## 思路
题意中说 $\vert a_i-a_j\vert$，根据绝对值的概念可以得知它的值一定 $\ge 0$。

所以我们要把所有的非正数都给选上，再去查找最小的满足条件的第一个正数。

此处我们可以用 `sort` 实现。

~~码风较难看，代码就不贴了。~~

---

## 作者：feicheng (赞：2)

## $\text{Description}$

给定长度为 $n$ 的序列 $a$，求一个子集 $S$，使得 $\forall i,j\in S,|a_i-a_j|\ge \text{MAX}$，其中 $\text{MAX}=\max_{i\in S} a_i$，最大化 $|S|$。

## $\text{Solution}$

首先对于所有的非正数，都是可以添加进来的。因为添加所有的非正数，$\text{MAX}\le0$，而一个数的绝对值 $\ge 0$，所以一定是满足条件的。

而对于正数，有如下两个结论：

1. 最多只能添加一个正数。

$\text{proof:}$ 考虑反证法，设选择了 $x,y$，假设 $0\lt x\le y $，则有 $y-x \lt y$，与条件相悖，故原命题成立。

2. 如果能添加正数，添加的正数一定是最小的正数。

考虑将所有负数想象成数轴上的点，那么添加正数等同于询问是否有两个点的距离小于这个正数，如果有很显然不成立。那么如果连最小的正数都不能满足，之后的正数一定不能满足这个条件。

而如何检验一个正数是否能加进来呢？

其实方法已经在结论 $2$ 的证明中提到了，我们将所有数排序，看是否有两个数之间的差小于该正数即可。

时间复杂度：$\Theta(n\log n)$ （排序的复杂度）。

代码不难写，就不放了。


---

## 作者：FutaRimeWoawaSete (赞：2)

首先考虑把所有负数都选上。             

接着我们考虑原序列有没有正数，没有正数就直接输出 $n$ 就好了。           

否则，我们判断可不可以选正数。由于正数至多选择一个，我们只需要看是否可以选择第一个正数就好了。        


```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
int n,m,a[Len];
inline Iabs(int x){return x < 0 ? -x : x;}
int main()
{
	int t;scanf("%d",&t);
	while(t --)
	{
		scanf("%d",&n);
		for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
		bool flag = false ;int flaw = 0;int ans = 0;
		for(int i = 1 ; i <= n ; i ++) if(a[i] < 0) ans ++;
		for(int i = 1 ; i <= n ; i ++) 
		{
			if(a[i] > 0) flag |= 1;
			if(a[i] == 0) flaw ++;
		}
		sort(a + 1 , a + 1 + n);
		int idx = 1;
		for(; idx <= n ; idx ++) if(a[idx] > 0) break;
		if(!flag){printf("%d\n",ans + flaw);continue;}
		int Ans = ans + flaw;bool flalwd = true;
		for(int i = 2 ; i < idx ; i ++) if(Iabs(a[i] - a[i - 1]) < a[idx]) {flalwd = false ; break;}
		if(flalwd) printf("%d\n",Ans + 1);
		else printf("%d\n",Ans);
	}
	return 0;
}
```

---

## 作者：RuntimeErr (赞：1)

首先对于所有的**非正数**肯定是要先选上的，因为 $MAX\leq 0$， 而任意两个数的差的绝对值都是非负数。

我们先预处理好任意两数之差的绝对值的**最小值**（因为只要这个最小值不小于 $MAX$ 就行了），然后我们按**从小到大**的顺序依次考虑加入每个正数：先更新最小值，然后看最小值是否**不小于**加入的正数，可以则增加答案，否则结束枚举（因为最小值都小于这个数了后面的就更不可能了）。

### $code:$

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

const int N=1e5+10,inf=0x7fffffff;

int n,a[N],ans;

int main(){
	int t;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);ans=0;
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
			if(a[i]<=0)++ans;
		}
		sort(a+1,a+n+1);
		int minn=inf;
		for(int i=1;i<ans;++i)minn=min(minn,a[i+1]-a[i]);
		for(int i=ans+1;i<=n;++i){
			minn=min(minn,a[i]-a[i-1]);
			if(minn>=a[i])++ans;
			else break;
		}
		printf("%d\n",ans);
	}
	return 0;
}
}
```

---

## 作者：Hooch (赞：0)

### 思路

首先我们发现题意中的 $|a_i - a_j|$ 根据绝对值的性质一定 $\ge 0$。

既然这样首先就**把非正数全部选上**，因为这样 $MAX$ 就是非正数，一定小于等于任意一个数的绝对值。

然后我们还是从小的开始选，**因为 $MAX$ 越小，能选的数就越多**。

### 代码

注释都在代码中。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, t, k, a[100005];
main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i(1); i <= n; ++i) cin >> a[i];
		sort(a + 1, a + n + 1); //从小到大排序
		int ma = a[1], jg = 2000000001, cnt = 1; //一定要选a[1]
        //jg 已是极值。
		for (int i(2); i <= n; ++i) {
			int nj = a[i] - a[i - 1]; //因为排过序了所以 a[i] - a[i - 1] = |a[i] - a[i - 1]|
			if (min(nj, jg) >= max(ma, a[i])) { //如果能选就选
				++cnt;
				jg = min(jg, nj); //更新新的最小的 |a[i]-a[i-1]|
				ma = max(ma, a[i]); //更新最大值
			}
		}
		cout << cnt << endl;
	}
}
```

---

## 作者：きりと (赞：0)

### 题目大意

给定一段长度为 $n$ 的序列，求其中满足 $| a_i-a_j|\ge maxn$，$1 \le  i,j\le n$，$maxn=\max(a_1,a_2,\cdots,a_n)$的最长子序列长度 $l$。

### 解题思路

对于一段全为非正数的序列，它显然符合条件，因为绝对值 $\ge 0$，而其中的 $maxn\le 0$。

所以在计算最长子序列的时候，我们首先将所有非正数全部放入序列。

接下来考虑能否再放入一些正数，由于正数之差的绝对值一定小于原数中较大的那个，所以正数个数 $\le 1$。所以我们要优先保证非正数能在序列中，其次判断能否塞下一个正数。

正数的存在导致 $maxn$ 是确定的，那么我们只需一一判断两个非正数之间的绝对值的差是否小于 $maxn$ 即可。这一部分可以用 `sort` 实现。

### Code

```cpp
#include<bits/stdc++.h> 
#define int long long
using namespace std;
const int N=2e5+10;
int a[N];
int abss(int q)
{
	return q<0LL?-q:q;
}
signed main()
{
	int t;
	cin>>t;
	int n;
	flag:while(t--)
	{
		cin>>n;
		int minn=1e10,x=0;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]>0)
			{
				minn=min(minn,a[i]);
			}
			else
			{
				x++;
			}
		}
		if(n==1)
		{
			cout<<1<<endl;
			goto flag;
		}
		sort(a+1,a+n+1);
		if(minn==0)
		{
			cout<<max(1LL,x)<<endl;
			continue;
		}
		for(int i=1;i<n;i++)
		{
			if(a[i+1]<=0&&abss(a[i]-a[i+1])<minn)
			{
				cout<<max(1LL,x)<<endl;
				goto flag;
			}
			if(a[i+1]>0)
			{
				break;
			}
		}
		cout<<x+1LL<<endl;
	}
	return 0;
}
```

---

## 作者：lrmlrm_ (赞：0)

## 题意

给出一个长度为 $n$ 的数组 $a_i$，在其中选择 $k$ 个数，使得任意两个元素 $a_i,a_j$ 的差比 $k$ 个数中的最大值大。问 $k$ 最大是多少？

## 思路

首先容易想到任意两个数的差都肯定比 $0$ 大（ $\left\vert a_i-a_j \right\vert >0$ ），那么小于等于 $0$ 的数就可以全部选上。然后我们考虑大于 $0$ 的数。考虑选 $2$ 个大于 $0$ 的数 $a_i , a_j$，设 $a_i>a_j$，那么显然 $ a_i-a_j > a_i$，与题目要求不符。选 $2$ 个都不行，显然选 $>2$ 个也不行。那我们来考虑 $1$ 个，假设 $>0$ 的数是 $x$，那么 $x-0=x$，只需要考虑其他的数满不满足条件即可。为了方便比较（不超时），我们对数组进行排序，排序后相邻两个数的差 $a_{i+1}-a_i$ 肯定是尽量小的，只有差值小才有可能使得差值小于最大值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,xx=-1;
int a[100010];
int main(){
	scanf("%d",&t);
	while(t--){
		xx=-1;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++){
			if(a[i]>0){
				xx=i;
				break;
			}
		}
		if(xx==-1)printf("%d\n",n);
		else{
//		printf("%d %d\n",xx,a[xx]);
			int p=0;
			for(int i=2;i<xx;i++)
				if(abs(a[i]-a[i-1])<a[xx]){
					p=1;
					break;
				}
			if(p==0)printf("%d\n",xx);
			else printf("%d\n",xx-1);
		}
	}
	
	return 0;
}
```

---

## 作者：expnoi (赞：0)

首先所有负数一定得要选，至少配一个正数就可以押着所有负数。

然后再选符合条件的所有正数即可。



代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int T,n,a[100001];
int main()
{
	T=read();
	while(T--)
	{
		memset(a,0,sizeof(a));
		n=read();
		int ans=0,maxn=1e9;
		for(int i=1;i<=n;i++)
		{
			a[i]=read();
			if(a[i]<=0)ans++;
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
		{
			if((a[i]<=0)&&a[i-1]<=0&&i>1)
			{
				maxn=min(maxn,abs(a[i]-a[i-1]));
			}
		}
		for(int i=1;i<=n;i++)
		{
			if((a[i]>0)&&(maxn>=a[i]))
			{
				ans++;
				break;
			}
		}
		write(ans);
		puts("");
	}
}
```


---

