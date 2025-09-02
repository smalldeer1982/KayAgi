# Array Eversion

## 题目描述

You are given an array $ a $ of length $ n $ .

Let's define the eversion operation. Let $ x = a_n $ . Then array $ a $ is partitioned into two parts: left and right. The left part contains the elements of $ a $ that are not greater than $ x $ ( $ \le x $ ). The right part contains the elements of $ a $ that are strictly greater than $ x $ ( $ > x $ ). The order of elements in each part is kept the same as before the operation, i. e. the partition is stable. Then the array is replaced with the concatenation of the left and the right parts.

For example, if the array $ a $ is $ [2, 4, 1, 5, 3] $ , the eversion goes like this: $ [2, 4, 1, 5, 3] \to [2, 1, 3], [4, 5] \to [2, 1, 3, 4, 5] $ .

We start with the array $ a $ and perform eversions on this array. We can prove that after several eversions the array $ a $ stops changing. Output the minimum number $ k $ such that the array stops changing after $ k $ eversions.

## 说明/提示

Consider the fist example.

- The first eversion: $ a = [1, 4, 2, 5, 3] $ , $ x = 3 $ . $ [2, 4, 1, 5, 3] \to [2, 1, 3], [4, 5] \to [2, 1, 3, 4, 5] $ .
- The second and following eversions: $ a = [2, 1, 3, 4, 5] $ , $ x = 5 $ . $ [2, 1, 3, 4, 5] \to [2, 1, 3, 4, 5], [] \to [2, 1, 3, 4, 5] $ . This eversion does not change the array, so the answer is $ 1 $ .

Consider the second example.

- The first eversion: $ a = [5, 3, 2, 4, 1] $ , $ x = 1 $ . $ [5, 3, 2, 4, 1] \to [1], [5, 3, 2, 4] \to [1, 5, 3, 2, 4] $ .
- The second eversion: $ a = [1, 5, 3, 2, 4] $ , $ x = 4 $ . $ [1, 5, 3, 2, 4] \to [1, 3, 2, 4], [5] \to [1, 3, 2, 4, 5] $ .
- The third and following eversions: $ a = [1, 3, 2, 4, 5] $ , $ x = 5 $ . $ [1, 3, 2, 4, 5] \to [1, 3, 2, 4, 5], [] \to [1, 3, 2, 4, 5] $ . This eversion does not change the array, so the answer is $ 2 $ .

## 样例 #1

### 输入

```
3
5
2 4 1 5 3
5
5 3 2 4 1
4
1 1 1 1```

### 输出

```
1
2
0```

# 题解

## 作者：wmrqwq (赞：3)

# 原题链接

[CF1585B Array Eversion](https://www.luogu.com.cn/problem/CF1585B)

# 题目简述

现在有一个长度为 $n$ 的序列 $a$，每次操作将 $a$ 中不大于序列 $a$ 中最后一个数的元素按照在 $a$ 序列中的顺序放入 $b$ 序列中，大于序列 $a$ 中最后一个数的元素同样按照在 $a$ 中的顺序放入 $c$ 序列中，然后再将 $c$ 序列拼接到 $b$ 序列的后面，变成新的 $a$ 序列，求至少需要几次操作才能让 $a$ 序列不论再进行多少次操作，都不会发生变化。

# 解题思路

首先，这道题的正解肯定不是模拟。不难想出，让 $a$ 序列不再变化的时候，$a$ 序列的最后一位肯定是最大的。而每次操作后的最后一个数字一定是比当前最后一个数字大的最后一个数字，所以我们将最大值和每个数进行比较，如果大于最大值，就将次数加上 $1$，但是需要注意的是，因为最大值在末尾，所以最终的结果还要减去 $1$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define QwQ return 0
long long t,n,a[1000010],sum,maxn;
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		sum=0,maxn=-1;
		cin>>n;
		for(int i=0;i<n;i++)//依次输入每个数字
			cin>>a[i];
		for(int i=n-1;i>=0;i--)//依次枚举每个数字
			if(a[i]>maxn) //如果大于最大数
				maxn=a[i],sum++; //将最大数重新赋值并将次数加上一
		cout<<sum-1<<endl;//注意，这里要减去一
	}
	QwQ;//华丽的结束
}
```


---

## 作者：York佑佑 (赞：1)

## 题意

给定长度为 $n$ 的序列 $a$。每次操作取出序列中最后一个元素 $a_n$，记为 $x$。将 $a$ 中不大于 $x$ 的元素按照在 $a$ 中的顺序放入 $b$ 数组中，大于 $x$ 的元素同样按照在 $a$ 中的顺序放入 $c$ 数组中。然后将 $c$ 数组拼接到 $b$ 数组的后面，变成新的 $a$ 数组。

求一个最小的整数 $k$，使得进行了 $k$ 次操作后，不论再进行多少次操作，$a$ 数组都不会变化。
## 分析
别看题目很烦，仔细分析之后其实还是可以发现它还是很简单的。

先附上样例解释：
```cpp
3
5
2 4 1 5 3
5
5 3 2 4 1
4
1 1 1 1
```
第一次进行操作后 $a=[2,1,3,4,5]$。

之后每次操作都不变该数组即可（最后一位是最大的）。

所以，如果要让 $a$ 数组从始至终都不会变化，那么它的最后一位就是最大的。

既然知道了最后一位最大，那么我们就将数组**从后往前遍历**，如果遍历到的这一个数比最大数大，就将最大数设为这个数，并且统计一次操作。

**注意：最后统计出来的次数需要减 $1$，因为最后一次遍历时，最大的数已经在末尾了。**
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[10000005],t,n,ans,maxx;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)	cin>>a[i];
		ans=0,maxx=-2147483647;//maxx定义的尽量小 
		for(int i=n;i>=1;i--)
			if(a[i]>maxx)//如果这一个数比最大数大	
			maxx=a[i],ans++;//就将最大数设为这个数，并且统计一次操作
		cout<<ans-1<<endl;//统计出的次数要减1 
	}
	return 0;
}
```



---

## 作者：lianchanghua (赞：1)

#### 题目大意

给定一个长度为 $n$ 的序列，找到序列中最后一个元素 $a_n$，将整个序列中不大于它的元素按原来的顺序放到一个序列中，将大于它的放到另一个序列中。再将大于 $a_n$ 的全部数拼接到不大于 $a_n$ 的后面，问：使得进行了 $k$ 次操作后，不论再进行多少次操作，新数组都不会变化时，$k$ 的最小值为多少？

#### 思路

开始本蒟蒻本来想要模拟的，但看到题解区，别的大佬的操作后，才知道：此题根本无需模拟！为了，使得新数组永远不会变化，我们就要使得：队列末尾的 $a_n$ 为最大值，这样，就不会分成两堆了，所以，我们只需从后往前搜，遇到比当前的 $\max$ 大时，我们的 $\max$ 就更新并 `cnt++` 即可。

#### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) 	cin>>a[i];
		int ma=INT_MIN,cnt=0;
		for(int i=n;i>=1;i--){
//			cout<<ma<<"\n";
			if(a[i]>ma){
				ma=a[i];
				cnt++;
			}
		}
		cout<<cnt-1<<"\n";
	}
	return 0;
} 
```

---

## 作者：luguangxing (赞：1)

这题我刚开始看的时候以为是一道模拟题，去做了以后测样例时看到了数据范围之后，才悟了。

样例解释：

```cpp
3
5
2 4 1 5 3
5
5 3 2 4 1
4
1 1 1 1
```
我们先看 $2 4 1 5 3$ 此时 $x$ 为 $3$，$b$ 数组中的元素为 $2$，$1$，$3$。$c$ 数组中元素为 $4$，$5$，拼接一下就是 $2 1 3 4 5$ 此时就不能再变动了输出 $1$，再来看 $5 3 2 4 1$ 第一次变动是 $1 5 3 2 4$ 再变动就是 $1 3 2 4 5$ 总共两次输出 $2$ 接着来看最后一组他是全一样的数字就不用变动了，根据这 $3$ 组样例分析看出所有元素最后一个都是数组中最大的数。

思路：

我们知道了改完后最后一个元素是数组中最大的一个数，我们可以找比最后一个元素大的第一个元素（从头开始遍历），如果大的话就把他替换，然后统计次数，最后得出的次数要减 $1$ 因为最后一次最大的元素已经在末尾了。

以上面的思路开始打程序：

[代码](https://www.luogu.com.cn/record/119782431)

大家记住：十年 OI 一场空不开 `long long` 见祖宗（也要开全局不然会 re）。

代码展示：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,a[1000005],n;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		cin>>a[i];
		int ans=0,sum=0;
		for(int i=n;i>=1;i--)
		if(a[i]>ans)
		{
			ans=a[i];
			sum++;
		}
		cout<<sum-1<<endl;
	}
	return 0;
}
```

---

## 作者：FSHYLHX (赞：0)

# 题目大意
给定一个长度为 $n$ 的序列，取这个序列的最后一个元素，将整个序列中不大于它的元素按照原本的顺序放到第一个数组中，将其他的数放到第二个数组中。再将第二个数组拼接到第一个数组的后面，形成第三个数组，求出最少的操作数，使得第三个数组就是原本题目给出的序列。
# 思路分析
一开始以为这道题是一道模拟题，直到看了样例才发现，这道题目包装的很好，因为如果要使最终形成的序列和原来的序列相等，就是要将最大值放在数组的末尾。所以只需要将数组从后往前枚举，如果枚举的这个元素比之前枚举过的元素都要大，那么就将答案加一。因为找到的最大的数要在末尾，所以要在最后把答案减一。
# 代码实现
```c
#include<bits/stdc++.h>
using namespace std;
int i,j,k,m,n,ans,sum,t;
int a[200005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++) scanf("%d",&a[i]);
		int maxx = -1e9, ans = 0;
		for(int i=n; i>=1; i--){
			if(a[i] > maxx){
				maxx = a[i];
				ans++;
			}
		}
		printf("%d\n", ans-1);
	}
	return 0;
} 
```


---

## 作者：封禁用户 (赞：0)

## 题目描述

[Array Eversion](https://www.luogu.com.cn/problem/CF1585B)

## 算法思路

看到范围 $1 \le n \le 2 \times 10^5$ 就可以想到不能用模拟。

如果要让 $a$ 数组无论如何都不会变化，那么 $a$ 数组的最后一位肯定是最大的。

而且我们可以发现，每次都是把最后面的第一个比当前最后一个数字大的移到最后一个位置。

所以我们从 $n$ 循环到 $1$，每次比较当前的最大值，如果大于最大值的话，次数 $+1$，最后答案还要 $-1$（因为第一个最大值已经在末尾了）。

### 样例解释

一开始 $a = [2,4,1,5,3]$。

第一次翻转操作后 $a = [2,1,3,4,5]$。

以后每次翻转都不变。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long
const ll N=200010,INF=0x3f3f3f3f3f3f3f3f;//INF为无限大 
ll t,n,a[N],ans,maxx;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;//t组数据 
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		ans=0;//归0 
		maxx=-INF;//maxx设为无限小 
		for(int i=n;i>=1;i--)//从后往前枚举 
		{
			if(a[i]>maxx)//如果大于现在的最大值 
			{
				maxx=a[i];
				ans++;//答案+1 
			}
		}
		cout<<ans-1<<"\n";//输出答案-1 
	}
	return 0;
}
```

---

## 作者：xiaozeyu (赞：0)

[题目链接 CF1585B Array Eversion](https://www.luogu.com.cn/problem/CF1585B)

每组数据中有 $n$ 个数字。

规定每一次的变换如下:

先找到最右边的那个数字。

再将小于等于这个数的都按照原来顺序放到它左边，将大于这个数的都按照原来顺序放到它的右边。

问需要几次操作再能使这串数字稳定，就是不能再变成其他样子。

要求变稳定，那么最后变成的这串数字里一定不会有数字向右挪动，也就是说此时最右边的数字一定是最大的。

那我们在分析一下变换过程。

可以发现，每次变换后，只有比变换前最右边的数字大的数字，相对顺序都保持不变。

而我们正好要让最大的在最右边，正好不用管更小的一些数字。

那样例来说明：

原来是 $53241$,此时把比 $1$ 小的都赶走，变成 $15324$。

显然 $1$ 不能赶走大的数。 

再变换，变成 $13245$。

如果你只看最大数及右边的数，会发现 $53241\to5324\to5$,每次右边会带走更小的数字，那我们要求的答案，其实就变成了反过来看的上升子序列的长度再减去一。



---

代码如下:

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=a;i<=b;i++)
#define Rep(i,a,b) for(register int i=a;i>=b;i--)
using namespace std;
int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
const int maxn=200010;
const int maxm=100010;
int T,n,ans,M,a[maxn];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		For(i,1,n) a[i]=read();
		M=-1;
		ans=-1;
		Rep(i,n,1)
		{
			if(a[i]>M)
			{
				M=a[i];
				ans++;
			}
		}
		printf("%d\n",ans);
	}
}
```

感谢管理员的审核。

---

## 作者：Crasole (赞：0)

## 思路

因为 $n \le 2 \times 10^5$，所以模拟可能会超时（但我没试过）。

观察样例的说明，我们要使最后的数组保持不变，那么我们就要的现在的 $x$ 在目前数组里是最大的。假设当前数组为 $a_1 , a_2 , a_3 , ... , a_j$，也就要让 $a_j$ 是数组 $a$ 中最大的。

那么对于每一次输入的 $a_1 , a_2 , a_3 , ... , a_n$ ，先定义变量 $maxn$ 记录当前最大值，如果找到的 $a_i$ 大于 $maxn$ 的数值，把 $maxn$ 更新为 $a_i$，同时 `k++`。

最后输出要 `k-1`，因为把 $maxn$ 也考虑进去了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n,a[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		int k=0,maxn=-1;
		for(int i=n;i>=1;i--)//注意，从后往前 
			if(a[i]>maxn) maxn=a[i],k++;//如果大于maxn就更新 
		cout<<k-1<<endl;
		//一定要k-1 
	}
	return 0;
}
```

---

