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

## 作者：xiaozeyu (赞：4)

[题目链接 CF1591B Array Eversion
](https://www.luogu.com.cn/problem/CF1591B)

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

## 作者：zwyyy (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/CF1591B)

---

## 思路
这道题目的大意是让我们输出将最大的数字变换到最后的次数。

由于每一次变换会将小于等于最后一个数字的数拼接到前面去，所以我们只需要考虑大于最后一个数字的数即可。

答案即为倒序的上升子序列的长度减一。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int main(){
	int t, n;
	scanf("%d", &t);
	for(int i = 1; i <= t; ++i){
		int ma = 0;
		scanf("%d", &n);
		for(int j = 1; j <= n; ++j){
			scanf("%d", &a[j]);
			if(a[j] >= a[ma])	ma = j;
		}
		if(ma == n){
			printf("0\n");
			continue;
		}
		int m = 0;
		int jl = 0;
		for(int j = n; j > ma; --j){
			if(a[j] > a[jl]){
				++m;
				jl = j;
			}
		}
		printf("%d\n", m);
	}
	return 0;
}
```
[AC](https://www.luogu.com.cn/record/123121603)

---

## 作者：York佑佑 (赞：0)

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

## 作者：__YancBuxIya (赞：0)

#### [题目传送门](https://www.luogu.com.cn/problem/CF1591B)

-------

## 题目分析：

由题意我们知道，每当进行一次“外翻”操作，序列中最大的数都会被放在序列的右边。当最大的数被移到最右边时，整个操作停止。

那如何知道何时最大值才会被移到右边呢？我们想到，每次选最后一个数作为标准进行“外翻”，那么只需要从后向前遍历整个数组， 找到“倒序”最长上升子序列的长度减一（最大值不算）即可。

------------

## 代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005];
int main(){
	scanf("%d",&t);
	while(t--){
		int mx=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]),mx=max(mx,a[i]);
		int lst=0,cnt=0;
		for(int i=n;i>=1;i--){
			if(a[i]==mx) break;
			if(a[i]>lst){
				lst=a[i];
				cnt++;
			}
		}
		printf("%d\n",cnt);
	}
	return 0;
}
``` 

---

## 作者：FSHYLHX (赞：0)

# 题目大意
给定一个长度为 $n$ 的序列，取这个序列的最后一个元素，将整个序列中不大于它的元素按照原本的顺序放到第一个数组中，将其他的数放到第二个数组中。再将第二个数组拼接到第一个数组的后面，形成第三个数组，求出最少的操作数，使得第三个数组就是原本题目给出的序列。
# 思路分析
显然，正解不是模拟，这道题目包装的很好，因为如果要使最终形成的序列和原来的序列相等，就是要将最大值放在数组的末尾。所以只需要将数组从后往前枚举，如果枚举的这个元素比之前枚举过的元素都要大，那么就将答案加一。因为找到的最大的数要在末尾，所以要在最后把答案减一。
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

## 作者：Miyamizu_Mitsuha (赞：0)

只要想明白了就不难。从数组末尾开始向前遍历，维护一个最大元素值以及操作次数。当遇到一个比最大元素值大的元素时，增加操作次数并更新最大元素值。最后输出操作次数。整体复杂度为 $O(n)$。

```
#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        int a[100005];
        for (int i = 1; i <= n; i++) cin >> a[i];
        int m = a[n];
        int cnt = 0; 

        for (int i = n - 1; i >= 1; i--) {//从后向前遍历
            if (a[i] > m) {//找到了比最大值还大的
                cnt++; //操作数+1
                m = a[i]; //更新最大值
            }
        }

        cout << cnt << endl;
    }

    return 0;
}

```


---

## 作者：Amm_awa (赞：0)

[$\color{red}\fbox{\text{洛谷链接}}$](https://www.luogu.com.cn/problem/CF1591B)

[$\color{red}\fbox{\text{ CF 链接}}$](https://codeforces.com/contest/1591/problem/B)

## 分析
首先，这题不是模拟。
1. 按照样例手动模拟一遍数据，比如 $\left[2,4,5,1,3\right]\to\left[2,1,3,4,5\right]$ 用了 $1$ 次；$\left[5,3,2,4,1\right]\to\left[1,5,3,2,4\right]\to\left[1,3,2,4,5\right]$，用了 $2$ 次；三组测试数据无需改变。可以发现，当作后一个数字是数组中的最大值时，数组不会发生改变。
2. 由第 $1$ 条为基础进行思考，可以想到：对数组 $a$ 从后往前进行遍历，当 $a_i$ 大于当前最大末尾元素时，将最大末尾元素设为 $a_i$，计数器 $sum$ 加 $1$。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int a[200005];
inline int read()
{
    register int x=0,f=1;
    register char ch=getchar();
    while(!isdigit(ch))
	{if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))
	{x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
void solve()
{
    register int i=0,now=0,sum=0;
    for(i=n;i>=1;i--)//要倒序遍历
        if(a[i]>now)sum++,now=a[i];
    cout<<sum-1<<'\n';//输出要减 1
}
void readNum()//输入数据
{
	register int i;
	t=read();
	while(t--)
	{
	    n=read();
	    for(i=1;i<=n;i++)
	        a[i]=read();
        solve();
	}
}

int main()
{
	readNum();
	return 0;
}
```

---

## 作者：luguangxing (赞：0)

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

## 作者：XL4453 (赞：0)

### 解题思路：

当数组中最大的那一个元素到达最后一个位置的时候，无论如何都不可能有任何变化了，那么直接算出这个就行了。

这样就直接从后往前扫描，并维护当前放到左边不管了的最大值，如果当前值没有这个大就直接跳过，否则用当前值更新这个最大值，直到扫描到最大的一个数为止。

这样做是因为根据第一步转化仅仅需要最大数数到达最后一个位置的时间，而不需要记录下其他的值的位置，还是比较简单的。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,a[200005],maxn,ans,now;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		now=0;maxn=0;ans=0;
		for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),maxn=max(maxn,a[i]);
		for(int i=n;i>=1;i--){
			if(a[i]==maxn)break;
			if(a[i]<=now)continue;
			now=max(now,a[i]);
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：sszcdjr (赞：0)

## 题面简述

规定一种操作，把小于等于最后一个数的分在左边一组，大于的分在右边一组，然后左右两组拼接，就完成了操作。

给出一个数组 $a$，长度为 $n$。求这个数组至少经过多少次操作后才能使得操作一次依然是原来的数组。

## 大致解法

思考一个问题，假设现在这一次操作最后一个是 $a_n$ ，那么请问哪个将成为操作后的最后一个呢？

答案是比 $a_n$ 大且离 $a_n$ 最近的 $a_i$。

为什么呢？坐标在 $i$ 和 $n$ 之间每一个数均小于等于 $a_n$，否则就会和上面的定义不符，然而小于等于 $a_n$ 的所有数将排在 $a_n$ 前面，那么这些数一定不会是操作后的最后一个。所以 $a_i$ 才变成了操作后的最后一个。

此时我们可以通过从后往前扫描一遍，每次记录 ```last``` 指标表示上一个末尾的大小。一旦发现这个数比 ```last``` 大，就更新 ```last``` 并让 ```cnt``` 加一。最后输出即可。复杂度 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[n+1],maxv=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			maxv=max(maxv,a[i]);
		}
		int lst=0,cnt=0;
		for(int i=n;i>=1;i--){
			if(a[i]==maxv){
				break;
			}
			if(a[i]>lst){
				cnt++;
				lst=a[i];
			}
		}
		cout<<cnt<<endl;
	} 
	return 0;
}
```

---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF1591B)

## 题目描述

找到最右边的那个数字。

再将小于等于这个数的都按照原来顺序放到它左边，将大于这个数的都按照原来顺序放到它的右边。

问：经过几次外翻后，阵列 $a$ 停止变化。输出最小值 $k$，这样阵列在更新后就不会改变？问的其实是要几次操作才能让最大的到最右边。

## 分析

原来如果是 $51243$ ，那么第一次可以得到 $12354$，第二次可以得 $12345$ 就完成了。

 发现：每次会带着右边小的数字，答案就是从最后开始的上升子序列长度减一。
 
## 下面是 AC 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[1010000],maxn,ans;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
	maxn=0;
	ans=0;
	cin>>n;
    for(int i=1;i<=n;i++){cin>>a[i];}
    for(int i=n;i>=1;i--)
    {	
    		if(a[i]>maxn)
    		{
    			ans++;
    			maxn=a[i];
			}
	}
    cout<<ans-1<<endl;	
	}
    return 0;
}	 #include<bits/stdc++.h>
using namespace std;
int n,a[1010000],maxn,ans;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
	maxn=0;
	ans=0;
	cin>>n;
    for(int i=1;i<=n;i++){cin>>a[i];}
    for(int i=n;i>=1;i--)
    {	
    		if(a[i]>maxn)
    		{
    			ans++;
    			maxn=a[i];
			}
	}
    cout<<ans-1<<endl;	
	}
    return 0;
}	
```


---

