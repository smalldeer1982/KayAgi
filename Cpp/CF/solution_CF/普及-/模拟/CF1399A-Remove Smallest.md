# Remove Smallest

## 题目描述

You are given the array $ a $ consisting of $ n $ positive (greater than zero) integers.

In one move, you can choose two indices $ i $ and $ j $ ( $ i       \ne j $ ) such that the absolute difference between $ a_i $ and $ a_j $ is no more than one ( $ |a_i - a_j| \le 1 $ ) and remove the smallest of these two elements. If two elements are equal, you can remove any of them (but exactly one).

Your task is to find if it is possible to obtain the array consisting of only one element using several (possibly, zero) such moves or not.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, we can perform the following sequence of moves:

- choose $ i=1 $ and $ j=3 $ and remove $ a_i $ (so $ a $ becomes $ [2; 2] $ );
- choose $ i=1 $ and $ j=2 $ and remove $ a_j $ (so $ a $ becomes $ [2] $ ).

In the second test case of the example, we can choose any possible $ i $ and $ j $ any move and it doesn't matter which element we remove.

In the third test case of the example, there is no way to get rid of $ 2 $ and $ 4 $ .

## 样例 #1

### 输入

```
5
3
1 2 2
4
5 5 5 5
3
1 2 4
4
1 3 4 4
1
100```

### 输出

```
YES
YES
NO
NO
YES```

# 题解

## 作者：引领天下 (赞：4)

因为每次只能删除较小的数，所以最后剩下的只能是最大的数。

那我们排个序，挨个判断不是最大的数能否删掉就好了。

代码：

```cpp
#include <bits/stdc++.h>
#define min(x,y) ((y)^(((x)^(y))&(-((x)<(y)))))
#define max(x,y) ((x)^(((x)^(y))&(-((x)<(y)))))
using namespace std;
int t,n,a[55];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        sort(a+1,a+n+1);bool ok=1;
        for(int i=n;i>1&&ok;i--)ok&=a[i]-a[i-1]<=1;//即：a[i-1]能否删去
        puts(ok?"YES":"NO");
    }
    return 0;
}
```

---

## 作者：GBLoi (赞：2)

### 题意

给出一个序列A,每次可以挑出任意两个`a[i]`,`a[j]`如果$∣a_i−a_j∣≤1 $,则删去最小的那个。                        

判断能不能使序列只剩下一个元素。

### 思路

我们有

- $a[i]$ 只能被 {$a[j]$ |$a[j]=a[i]+1$ 或 $a[j]=a[i],i \not=j$ } 里的元素删除 -------> $a[j]>=a[i]$ 

一个数只能被比它大的数删除，那如果数列中只剩一个数，这个数一定是数列的最大值。

对于值相同的$a[i],a[j]$ ，可以将其互删，只剩下一个。

现在只考虑不同值的 $a[i],a[j]$ 。

不妨把序列从小到大排序。

- 若所有 $a[i]+1=a[i+1]$ ,$i \in [1,n-1]$ 那我们每次用 $a[2]$ 删 $a[1]$ 就可以了。
- 若存在 $i \in [1,n-1]$ ,使得 $a[i]+1 \not = a[i+1]$ ,那么 $a[i]$ 必不能被删除，$a[n]$ 也不能被删除(见上)，不符题意，舍去。 

所以只要去掉相同值的有序序列满足 所有 $a[i]+1=a[i+1]$ ,$i \in [1,n-1]$ ，即可。

实际操作可以不用判断相同值，见代码。

```cpp
#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<stack>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
#define rint register int
using namespace std;
const int N=56;
int T;
int n;
int a[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(i=1;i<=n;i++) 
			scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		for(i=2;i<=n;i++) 
			if(a[i]-a[i-1]>1) break;
		if(i==n+1) puts("YES");
		else puts("NO");
	}
	return 0;
}
```



---

## 作者：159号程序员 (赞：2)

水题一枚，立马切。

### 题目大意
给定长度为 $n$ 的数组 $a$，每次可以选择其中两个不同的元素 $a_{i}$ 和 $a_{j}$，若 $|a_{i}-a_{j}|\le1$，则可以删去其中较小的一个（若相等，则任选一个删去）。重复操作，问能否将数组长度变为 $1$。**多测**

### 题目思路
我们可以将 $a$ 数组排序，看看 $a_{i}$ 与 $a_{i-1}$ 的大小，如果差 $\le1$，就删掉前一个数，最后看看还剩几个数。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T, n, a[1000010];
int main()
{
	cin >> T;
	while(T--)//多测
	{
		cin >> n;
		for(int i = 1; i <= n; i++)//读入
		{
		    scanf("%d", &a[i]);
		}
		sort(a + 1, a + n + 1);//排序
		int sum = n;
		for(int i = 1; i <= n - 1; i++)//比较
		{
			if(a[i + 1] - a[i] <= 1)
			{
			    sum--;
			}
		}
		if(sum <= 1)//判断
		{
		    printf("%s\n", "YES");
		}
		else
		{
		    printf("%s\n", "NO");
		}
	}
	return 0;
}
```

引用：

感谢[rouXQ](https://www.luogu.com.cn/blog/Roux-cuber-Q/solution-cf1399a)大佬告诉了我翻译（英语还是不好啊）

---

## 作者：_jimmywang_ (赞：1)

拿到这题，我们看到了 $\left|a_i-a_j\right|$ ,又看到了删除较小的一个。

这不就比大小吗？

那就先让你比大小比到底！

咋弄呢？排序啊！

可以想到一个贪心思路，排序完后每次比较相邻的两个数（因为排完序后相邻两个数的差最小），如果差$\leq 1$,那就删除前一个数（其实就是最少剩下的数-1）。最后看看是否只剩下了一个数就行了。


$code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll r() {
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d r()
ll T;
ll n;
ll a[1000010];
int main(){
	T=d;
	while(T--){
		n=d;
		f(i,1,n)a[i]=d;
		sort(a+1,a+n+1);
		ll cmp=n;
		f(i,1,n-1)
			if(a[i+1]-a[i]<=1)cmp--;
		if(cmp<=1)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：KSToki (赞：0)

题目大意就是给你$n$个数，你每次可以选择两个差不超过$1$数，删去较小的（相同则随便删一个），问最后是否能只剩下一个数。

很显然，如果最后只剩一个数，一定是剩$n$个数中最大的那个数，所以我们对数组$a$进行排序。从最后一个数推起，最后一次操作删去的一定是大小等于$a_n$或$a_n-1$的数。针对每个数，都有这样的结果。

因此，对于排序后的$a$，我们只需判断相邻的两个数是否差大于一，如果有则输出NO，没有则输出YES。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t,n,a[51];
bool f;
inline int read()
{
	int res=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		    flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		f=0;
		for(register int i=1;i<=n;++i)
			a[i]=read();
		sort(a+1,a+n+1);
		for(register int i=1;i<n;++i)
		    if(a[i+1]-a[i]>1)
		    {
		    	f=1;
		    	break;
		    }
		if(f)
			printf("NO\n");
		else
		    printf("YES\n");
	}
	return 0;
}
```


---

## 作者：wmy_goes_to_thu (赞：0)

假设有三个从小到大的数 $a,b,c$，那么我们应该如何操作呢？显然，先操作 $a,b$，然后是 $b,c$ 或者先操作 $b,c$，再操作 $a,b$ 是最优的。所以选相邻的是最优的。我们只需从小到大排序，相邻元素比较即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[55];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+n+1);
		int flag=0;
		for(int i=1;i<n;i++)if(a[i+1]-a[i]>1)flag=1;
		if(!flag)puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：Lylighte (赞：0)

> 时隔 $3.5$ 个月，我又回来了……

#### CF1399A 题意~~简~~述

给定长度为 $n$ 的整型数组 $a$，每次可以选取其中差小于等于 $1$ 的两个整数，删去较小的一个。

问能否通过 $n-1$ 次如上的操作，使得数组中只剩下 $1$ 个整数。

$t$ 组数据，每组数据包括整数 $n(n\le 50)$，和数组 $a(1\le a_i\le 100,i\in[1,n])$，对于每组数据输出 `YES` 或 `NO`。

> …… and remove the **smallest** of these **two** elements.
>
> 吐槽下题面：两个物体的比较用最高级？喵喵喵？

#### 贪心做法

每次选取数组 $a$ 中最小和第二小的整数，判断差是否小于等于 $1$，不成立就说明无法使数组中只剩下 $1$ 个整数，成立则删去最小的那个，重复 $n-1$ 次即可。

至于证明……（以后可能补充，请借鉴其他 DALAO 们的题解，~~也可能不用证~~。）

#### 具体实现

无需删除数组元素。先把数组 $a$ 从小到大排序，再从小到大循环比较 $a_{i+1}-a_i\le 1$（$i\in[1,n-1]$） 是否成立，有一个不成立即输出 `NO`，全部成立则输出 `YES`。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[1010];
int t, n;
bool ret;

int main(){
	cin >> t;
	while(t>0){
		--t;
		ret = true;
		cin >> n;
		for(int i=1; i<=n; ++i)
			cin >> a[i];
		sort(a+1,a+n+1);
		for(int i=1; i<n; ++i)
			if(a[i+1]-a[i]>1){
				ret = false;
				break;
			}
		if(ret)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}
 
```



---

## 作者：Doubeecat (赞：0)


## [CF1399A. Remove Smallest](https://codeforc.es/problemset/problem/1399/A)
> 给你一个数列 $a$,你可以进行很多次操作,每次操作选择两个$|a_i - a_j| \leq 1$ 的元素,消去其中较小那个。求这个数列最后能否被消到只剩下一个元素。
> $T \leq 1000,n \leq 50,a_i \leq 100$


### 思路

贪心题。

首先分析一下这个题目的条件,可以发现,每次消去的一个元素要么递增,要么是相同的.

由此我们可以大胆猜想,是否当这个数列为单调递增时这个就有解？

要证明这个结论,我们可以先排序整个序列,因为整个序列的次序与操作是没有关系的。

排完序后我们可以发现,对于每个单调递增的序列来说,从小到大删肯定是最好的方案。

所以我们只要判断一下从 $2 - n$ 中有没有元素满足 $a_{i+1} - a_i > 1$,如果有就输出 `NO`,否则是 `YES`.

关注到这里的 $a_i$ 非常小，直接开个桶存一下判断即可。

### 代码

```cpp

int n;
bool a[101];
signed main() {
	int T;read(T);
	while (T--) {
		memset(a,0,sizeof a);
		read(n);
		if (n == 1) {flag = 1;}
		int minn = INF,maxx = -INF;
		for (int i = 1;i <= n;++i) {
			int x;read(x);
			a[x] = 1;
			minn = min(minn,x),maxx = max(maxx,x);
		}
		bool flag = 0;
		for (int i = minn;i <= maxx;++i) {
			if (!a[i]) {
				flag = 1;
			}
		}
		if (flag) puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：rouxQ (赞：0)

## 题意
给定长度为 $n$ 的数组 $a$，每次可以选择其中两个不同的元素 $a_i$ 和 $a_j$，若 $|a_i-a_j|\le 1$，则可以删去其中较小的一个（若相等，则任选一个删去）。重复操作，问能否将数组长度变为 $1$。
## $\operatorname{Sol}$
由于删除条件是绝对值小于 $1$，那么要使删除操作能够一直顺利进行，就要使剩余元素**尽量接近**，所以我们应把数组排序后，**从数组的任一端向另一端不断删除**。那么代码就很容易写出了。
## $\operatorname{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[60];
int main (){
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)cin >> a[i];
        sort(a + 1, a + 1 + n);
        while(n > 1 && a[n] - a[n - 1] <= 1)n--;
        printf("%s\n", n == 1 ? "YES" : "NO");
    }
    return 0;
}
```

---

## 作者：crh1272336175 (赞：0)

思路应该不难想，把数组排个序，检查相邻两个元素是否超过1。只要有一对相邻元素超过1，就一定不可能实现“最终只剩1个元素”，输出NO，否则输出YES

代码：

```cpp
#include<bits/stdc++.h>
#pragma GCC opitimize(2)
using namespace std;
typedef long long ll;
const int N=55;
ll a[N];
namespace Read
{
    inline ll read()
    {
        ll s=0,f=1; char ch=getchar();
        while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
        while(isdigit(ch)) s=s*10+(ch^48),ch=getchar();
        return s*f;
    }
    inline void write(ll x)
    {
        if(x<0) putchar('-'),x=-x;
        if(x>9) write(x/10);
        putchar(x%10+'0');
    }
}using namespace Read;
inline void solve()
{
	memset(a,0,sizeof a);
	ll n=read();
	for(ll i=1; i<=n; i++) a[i]=read();
	if(n==1) {puts("YES");return;}
	sort(a+1,a+1+n);
	for(ll i=2; i<=n; i++)
		if(a[i]-a[i-1]>1){puts("NO");return;}
	puts("YES");
}
int main()
{
	ll t=read();
	while(t--) solve();
	return 0;
}
```


---

