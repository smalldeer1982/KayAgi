# Assembly via Minimums

## 题目描述

Sasha has an array $ a $ of $ n $ integers. He got bored and for all $ i $ , $ j $ ( $ i < j $ ), he wrote down the minimum value of $ a_i $ and $ a_j $ . He obtained a new array $ b $ of size $ \frac{n\cdot (n-1)}{2} $ .

For example, if $ a= $ \[ $ 2,3,5,1 $ \], he would write \[ $ \min(2, 3), \min(2, 5), \min(2, 1), \min(3, 5), \min(3, 1), min(5, 1) $ \] $ = $ \[ $ 2, 2, 1, 3, 1, 1 $ \].

Then, he randomly shuffled all the elements of the array $ b $ .

Unfortunately, he forgot the array $ a $ , and your task is to restore any possible array $ a $ from which the array $ b $ could have been obtained.

The elements of array $ a $ should be in the range $ [-10^9,10^9] $ .

## 说明/提示

In the first sample, Sasha chose the array $ [1,3,3] $ , then the array $ b $ will look like $ [\min(a_1,a_2)=1, \min(a_1,a_3)=1, \min(a_2,a_3)=3] $ , after shuffling its elements, the array can look like $ [1,3,1] $ .

In the second sample, there is only one pair, so the array $ [10,10] $ is suitable. Another suitable array could be $ [15,10] $ .

## 样例 #1

### 输入

```
5
3
1 3 1
2
10
4
7 5 3 5 3 3
5
2 2 2 2 2 2 2 2 2 2
5
3 0 0 -2 0 -2 0 0 -2 -2```

### 输出

```
1 3 3
10 10
7 5 3 12
2 2 2 2 2
0 -2 0 3 5```

# 题解

## 作者：WsW_ (赞：8)

### 思路
反向推一下。  
从题目中可以知道顺序对答案无影响，因此我们先将原数列 $a$ 从小到大排序。  
排序后 $a_1$ 显然是最小的，那么它和另外 $n-1$ 个数字比较的时候，结果都会是 $a_1$。也就是说，数列 $b$ 中会有 $n-1$ 个 $a_1$。  
同理，数列 $b$ 中会有 $n-2$ 个 $a_2$。  
以此类推，数列 $b$ 中会有 $i$ 个 $a_i$。

那么我们将数列 $b$ 从小到大排序，那么 $a_1$ 为 $b_1$，$a_2$ 为 $b_{n}$，$a_3$ 为 $b_{2n-2}$。  
对于 $a$ 数列中剩下的空位，我们要保证其比前面的数字大，那么我们放入一个极大的数字即可。

显然，只有 $a_n$ 比数列 $a$ 中其他所有数字都大，导致不会出现在数列 $b$ 中。所以只要输出一个极大的数字即可。

---
### 代码和[提交记录](https://www.luogu.com.cn/record/119647338)
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,len;
int cnt;
int b[500003];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		cnt=n-1;
		len=((n-1)*n>>1);
		for(int i=1;i<=len;i++){
			scanf("%d",&b[i]);
		}
		sort(b+1,b+1+len);
		for(int i=1;i<=len;){
			printf("%d ",b[i]);
			i+=cnt;
			cnt--;
		}
		puts("1000000000");//这是a[n]
	}
	return 0;
}
```

---

## 作者：Kedit2007 (赞：2)

## CF1857 Assembly via Minimums 题解

### 简要题意

有一个长度为 $n$ 序列 $A$，其中任意两数的最小值构成序列 $B$，长度为 $\frac{n\cdot(n-1)}{2}$。

现将 $B$ 随机打乱，求出可能的 $A$。只需输出一种方案。

---

### 分析

若已知原数组 $A$，且其单调不降，考虑 $B$ 序列的构造过程。

由于序列单调不降，每个元素与其后方元素进行 $\min$ 操作所得均为该元素本身。例如序列 $A = [\red{1}, \orange{2}, \blue{3}, \green{4}]$，得到的 $B$ 序列为 $[\red{1, 1, 1}, \orange{2, 2}, \blue{3}]$。这意味着，在 $B$ 序列中，**有 $n - i$ 个在 $A$ 序列中第 $i$ 小的元素**。

有了这个结论，我们只需要将给定的 $B$ 序列排序，依次从开头取走 $(n-1), (n - 2), ...$ 个数即可。在这之后，原序列 $A$ 中还剩下一个最大的数没有得出来，只需要随意再添加一个比其他数大的数即可。

### 参考代码

```cpp
void work()
{
    int n;
    cin >> n;
    vector<int> arr(n * (n - 1) / 2);
    for (auto& i : arr)
    {
        cin >> i;
    }
    sort(arr.begin(), arr.end());
    for (int i = 0, j = n - 1; j > 0; i += j, j--)
    {
        cout << arr[i] << ' ';
    }
    cout << arr.back() << '\n';
}
```

---

## 作者：duchengjun (赞：1)

# 分析

题目给你了每一个二元组 $(i,j)$ 在数组 $a$ 上的最小值，且 $i,j$ 不相等，所以很容易想到将数组 $b$ 进行排序。下面，我将从题目中解释的样例进行分析。

该 $b$ 数组为 $[2,2,1,3,1,1]$，排序后变为 $[1,1,1,2,2,3]$，很明显看到相同的元素合到了一起，且个数呈递减的规律并每次减少一个，那么该结论就可以辅助我们做题了。

由于元素个数递减，我们就可以将数组排序，并每次将下标移到下一个元素即可。注意：数组 $a$ 找到后会缺少一个数，将该数变成最后一个元素即可，也就是赋值为最大值。千万不要加一，因为最大值可以达到 $10^9$，如果加一就超过了数组 $a$ 的最大限制了（别问我怎么知道的）。

## 证明

我们将数组 $a$ 排序，则最小值比其余的元素都小于或等于，所以最小值一定为数组 $b$ 的最小值，且出现个数为 $n-1$；那么，第二小的值则比除了最小值的其余元素都小，那么它的出现个数为 $n-2$；以此类推……

# Code

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<string.h>

using namespace std;

const int N=1e6+10;

int T;
int n;
int b[N];

void Solve(){
	
	scanf("%d",&n);
	int m=n*(n-1)/2;
	for(int i=1;i<=m;i++)
		scanf("%d",&b[i]);
	sort(b+1,b+1+m);
	int i=1,j=n-1;
	while(i<=m){
		printf("%d ",b[i]);
		i+=j;
		j--;
	}
	printf("%d\n",b[m]);
	return ;
	
}

int main(){
	
	scanf("%d",&T);
	while(T--){
		Solve();
	}
	return 0;
	
}
```

---

## 作者：hanjinghao (赞：1)

~~昨晚严重降智，这道题用了接近半小时才过。~~

![](https://cdn.luogu.com.cn/upload/image_hosting/seeypg7w.png)

# 思路

先把 $ b $ 数组从小到大排序并去重。如果去重后还剩 $ n $ 个数，直接输出即可。

否则，我们令去重前的数组为 $ c $。对于每一个 $ b_i $，设 $ c $ 中比它大的数的个数为 $ x_i $，原数组 $ a $ 中比它大的数的个数为 $ y_i $。显然，$ x_i = y_i \cdot (y_i - 1) / 2 $。$ x_i $ 可以直接用一个指针求出，随后便能求出 $ y_i $。

接下来，$ y_i - y_{i + 1} $ 即为原数组 $ a $ 中等于 $ b_{i + 1} $ 的数的个数。我们输出这么多个 $ b_{i + 1} $ 即可。特别地，对于最后一个数，我们输出这么多个 $ 10 ^ 9 $。

剩余的数，用 $ b_1 $ 来补充。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template < typename T >
inline const void read(T &x)
{
	bool flg = x = 0;
	char c;
	while ((c = getchar()) < 48 || c > 57)
		flg |= c == '-';
	do
		x = (x << 1) + (x << 3) + (c ^ 48);
	while ((c = getchar()) > 47 && c < 58);
	if (flg) x = -x;
}

int OUTPUT[45];

template < typename T >
inline const void write(T x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	int len = 0;
	do
	{
		OUTPUT[++len] = x % 10 | 48;
		x /= 10;
	}while (x);
	while (len)
		putchar(OUTPUT[len--]);
}

template < typename T >
inline const void writesp(const T x)
{
	write(x);
	putchar(32);
}

template < typename T >
inline const void writeln(const T x)
{
	write(x);
	putchar(10);
}

const int N = 1e6 + 5;
int T, n, a[N], b[N], c[N], f[N];

int main()
{
	read(T);
	while (T--)
	{
		int n;
		read(n);
		int m = (n * (n - 1)) >> 1;
		for (int i = 1; i <= m; ++i)
		{
			read(a[i]);
			b[i] = a[i];
		}
		sort(b + 1, b + m + 1);
		int len = unique(b + 1, b + m + 1) - b - 1;
		if (len >= n)
		{
			for (int i = 1; i <= n; ++i)
				writesp(b[i]);
			putchar(10);
			continue;
		}
		sort(a + 1, a + m + 1);
		int p = m + 1;
		for (int i = len; i; --i)
		{
			while (p > 1 && a[p - 1] > b[i])
				--p;
			f[i] = m - p + 1;
			f[i] = sqrt(2 * f[i]);
			++f[i];
		}
		for (int i = 1; i < len; ++i)
			f[i] -= f[i + 1];
		int cnt = 0;
		for (int i = 1; i <= len; ++i)
			if (f[i])
			{
				if (i == len)
				{
					for (int j = 1; j <= f[i]; ++j)
						writesp(1000000000);
				}
				else
				{
					for (int j = 1; j <= f[i]; ++j)
						writesp(b[i + 1]);
				}
				cnt += f[i];
			}
		while (cnt < n)
		{
			++cnt;
			writesp(b[1]);
		}
		putchar(10);
	}
	return 0;
}
```

---

## 作者：NBest (赞：0)

## 思路：
考虑到一个最小值对答案的贡献，发现如果是序列最小值，因为配对了 $n-1$ 次，而每次配对的结果都是它，所以在 $b$ 中会出现 $n-1$ 次。

同理，次小值（可能与最小值相同）出现 $n-2$ 次，第三小出现 $n-3$ 次等。因为保证有解，所以我们只需要给 $b$ 数组排好序后跳相应的步数并且输出当前数即可，最后注意 $a$ 数组最大值只需要大于等于 $b$ 数组最大值即可，这里我出于方便直接取等了。
## $Code$
```cpp
int T,n,m,a[1000006];
int main(){
    for(T=read();T--;){
        n=read();
        m=n*(n-1)>>1;
        for(int i=1;i<=m;i++){
            a[i]=read();
        }
        sort(a+1,a+1+m);
        int o=0;
        for(int i=1;i<=m;i+=n-o){
            printf("%d ",a[i]);
            o++;
            if(i==m){
                printf("%d\n",a[i]);
                break;
            }
        }
    }
}
```

---

## 作者：Dream_poetry (赞：0)

### 思路分析：
通过对样例的 $B$ 数组排序，我们发现了一些规律：第 $n$ 大的数出现了 $\frac{n(n+1)}{2}$ 次。

由于输出任意可能的答案即可，我们并不需要知道最大值，随便输出一个即可。

对于答案，将 $B$ 数组排好序后，倒着输出，依次跳过不需要的数，最后再输出一个无穷大即可。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int b[1000005];
signed main(){
	cin>>t;
	while (t--){
		cin>>n;
		int m=n*(n-1)/2; // B数组的长度 
		for (int i=1;i<=m;i++) cin>>b[i];
		if (n==2){ //特判 
			cout<<b[1]<<' '<<0x3f3f3f3f<<endl;
			continue;
		}
		sort(b+1,b+m+1);
		int tep=0;
		for (int i=1;i<n;i++){
			int tepi=i*(i+1)/2; //计算位置 
			cout<<b[m-tepi+1]<<' '; //倒着搞得话，还要用m减去他+1. 
		}
		cout<<0x3f3f3f3f<<endl; //输出无穷大 
	}
	return 0;
}
```


---

## 作者：Wf_yjqd (赞：0)

挺离谱的结论题。

------------

一开始我读错题了，以为 $b$ 是有序的。

每个数和其他所有数都取了 $\min$，所以它必须是所有与他有关的最小值中的最大值，否则必有不符合的。

然后我发现样例没过。。于是注意到 $b$ 打乱过。

蒙了个结论，将 $b$ 从小到大排序后求答案即可。

若某个数 $x$ 为 $a$ 中第 $i$ 小的数，$b$ 中将有连续 $n-i$ 个数为 $x$。

而排序刚好可以将从小到大将相同的数放在一起。

------------

真没想到一遍过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+84;
int T,n,a[maxn],b[maxn*maxn],c,cnt;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            a[i]=-0x3f3f3f3f;
        for(int i=1;i<=n*(n-1)/2;i++)
            scanf("%d",&b[i]);
        sort(b+1,b+n*(n-1)/2+1);
        cnt=0;
        for(int i=1;i<n;i++)
            for(int j=i+1;j<=n;j++){
                c=b[++cnt];
                a[i]=max(a[i],c);
                a[j]=max(a[j],c);
            }
        for(int i=1;i<=n;i++)
            printf("%d ",a[i]);
        puts("");
    }
    return 0;
}
```


---

## 作者：Special_Tony (赞：0)

[洛谷传送门](/problem/CF1857C) & [CF 传送门](//codeforces.com/problemset/problem/1857/C)
# 思路
因为这题有 SPJ，我们可以输出任意一种答案，所以我们可以将元素从小到大排序，然后我们可以发现，$a_0$ 出现了 $n-1$ 次，$a_1$ 出现了 $n-2$ 次，……，$a_{n-1}$ 出现了 $0$ 次，$a_i$ 出现了 $n-i-1$ 次，然后我们只要在输出的时候跳着输出即可。
# 代码
```cpp
# include <bits/stdc++.h> //万能头
using namespace std;
int t, n, a[1000005], m;
int main () {
	cin >> t;
	while (t --) {
		cin >> n;
		m = (n - 1) * n >> 1; //计算输入序列长度
		for (int i = 0; i < m; ++ i)
			cin >> a[i];
		sort (a, a + m); //排序
		for (int i = n, j = 0; -- i /*i 从 n-1 枚举到 1*/; j += i /*循环增量*/)
			cout << a[j] << ' ';
		cout << (int) 1e9 << '\n'; //a[n-1] 随便设一个极大值就可以了，但是不能超过题目给定的 1e9
	}
	return 0; //结束程序
}
```

---

## 作者：MrPython (赞：0)

## 题意简述
有一个长度为 $n$ 数组 $a$。将 $a$ 中的元素两两求最小值，打乱后得到长度为 $\frac{n\left(n-1\right)}{2}$ 的数组 $b$。

现在已知 $b$，求原数组 $a$。保证有解，构造任意一组解即可。

## 思路
假设将 $a$ 排序然后开始构造 $b$。$a_0$ 是数组中最小的，因此显然可以得到 对于每一个整数 $i(1\le i\le n)$ 都有 $\min(a_0,a_i)=a_0$，则数组 $b$ 中就会有 $n-1$ 个 $a_0$。对于 $a_1$ 同理，数组 $b$ 中会有 $n-2$ 个 $a_1$，以此类推，$i$ 每增加 $1$，则数组 $b$ 中的 $a_i$ 数量就会减少 $1$。

因此，将 $b$ 从大到小排序一下，然后取出 $a_0,a_{n-1},a_{(n-1)+(n-2)},a_{(n-1)+(n-2)+(n-3)}\dots$ 即可。

不过数组 $a$ 中还有一个最大的元素无法在 $b$ 中体现，怎么解决？我们只需要构造出任意一组解，那最后的元素直接输出一个极大值就可以了。

```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t T;
    cin>>T;
    while (T--){
        size_t n;
        cin>>n;
        vector<int> a((n*n-n)>>1);
        for (int& i:a) cin>>i;
        sort(a.begin(),a.end());
        for (vector<int>::iterator it=a.begin();it<a.end();it+=(--n)) cout<<*it<<' ';
        cout<<"1000000000\n";
    }
    return 0;
}
```

---

## 作者：LCat90 (赞：0)

首先排序，发现对于 $a_1$，其后 $n-1$ 个 $\min$ 都是他。普遍的，如果序列单调不减，那么第 $i$ 个位置带来的 $\min$ 值有 $n-i+1$ 个，包括自己。

所以我们将输入的 $b$ 进行排序，如果有解的话那么最小的数一定在最前面且个数和上面的推导一样，每次往后跳相应的个数输出即可。
 
这样会剩下没有影响的最后一个数，我们只需要保证它大于等于最后一个数即可。最好是等于，因为 $a$ 和 $b$ 的上界相同，避免越界。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int t, n, a[N], b[N]; 
signed main() {
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 1;i <= n * (n - 1) / 2; ++i) scanf("%d", &b[i]);
		sort(b + 1, b + n * (n - 1) / 2 + 1);
		int sum = 0;
		for(int i = 2;i <= n; ++i) {
			sum += n - i + 1;
			printf("%d ", b[sum]);
		}
		printf("%d", b[sum]);
		puts("");
	}
	return 0;
}
```

---

## 作者：ivyjiao (赞：0)

闲话：感觉 C 比 B 简单。

因为数据是打乱的，直接算没法算，所以我们把原数组从小到大排序（也可以从大到小排，做法相似），即我们默认了 $a_i\leq a_{i+1}$。

我们以样例为例，排序后，变成了这个样子：

```
5
3
1 1 3
2
10
4
3 3 3 5 5 7
5
2 2 2 2 2 2 2 2 2 2
5
-2 -2 -2 -2 0 0 0 0 0 3
```

还是感觉没什么思路，我们把样例“断句”：

```
5
3
1 1 / 3
2
10
4
3 3 3 / 5 5 / 7
5
2 2 2 2 / 2 2 2 / 2 2 / 2
5
-2 -2 -2 -2 / 0 0 0 / 0 0 / 3
```

容易发现，$[1,n-1]$ 一定是 $a_1$，因为我们已经默认了 $a_i\leq a_{i+1}$，也就是 $a_1$ 是最小值，而排序后 $[1,n-1]$ 里的数分别是 $\min(a_1,a_2),\min(a_1,a_3)\cdots \min(a_1,a_n)$ 的值，所以这些数一定相等且为 $a_1$。

同样的，$[n,2n-2]$ 为 $a_2$，$[(k-1)n-k+2,kn-k]$ 为 $a_k$。

最后，我们将 $a_n$ 设为最大，即 $10^9$。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int t,n,a[1000001];
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n*(n-1)/2;i++) cin>>a[i];
        sort(a+1,a+1+n*(n-1)/2);
        for(int i=1,j=1;i<=n*(n-1)/2;i+=(n-j),j++) cout<<a[i]<<" ";
        cout<<1000000000<<endl;
    }
}
```

---

## 作者：__Allen_123__ (赞：0)

### 题意简述

有一个长度为 $n$ 的序列 $a$，我们把在其中任意选择两个数求得的所有的最小值放入长度为 $\frac{n(n-1)}{2}$ 的序列 $b$ 中并将其随意打乱，请通过 $b$ 还原 $a$，如果可能的序列 $a$ 不止一种，输出任意一种即可。

本题有多测，共 $t$ 组数据。

$1\le t \le 200, n\ge 2, \sum n \le 10^3, |b_i|\le 10^9$。

### 题目分析

由于我们可以输出任何一种可能的 $a$，我们可以**假设 $a$ 有序**。又因为我们随机打乱了 $b$ 中内容，我们可以将其排序，不影响结果。

设 $a$ 中最小值为 $x$，那么它与任何其他元素取最小值的结果均为 $x$，则排序后的 $b$ 开始时会有 $n-1$ 个 $x$。同理，设 $a$ 中次小值为 $y$，那么它与除了 $x$ 以外其他任何元素取最小值均为它本身，那么 $b$ 中跟随在 $x$ 后的会有 $n-2$ 个 $y$。以此类推，我们可以通过 $b$ 来依次反推出 $a_1, a_2, \cdots, a_{n-1}$，因为 $a_n$ 在 $b$ 中不会出现，所以输出任意一个 $\ge a_{n-1}$ 的元素作为 $a_n$ 就可以。

### 代码

```cpp
#include <bits/stdc++.h>
#define itn int 
#define cosnt const
#define logn long
using namespace std;
const int MAXN = 1e3 + 5, MAXX = 1e6 + 5;
int t, n, a[MAXN], b[MAXX];
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1;i <= n * (n - 1) / 2;i++){
			scanf("%d", &b[i]);
		}
		sort(b + 1, b + n * (n - 1) / 2 + 1); // 将 b 排序
		int cnt = 0, ind = 0;
		for(int i = n - 1;i;i--){
			cnt += i;
			a[++ind] = b[cnt]; // 根据排序后的 b 依次求出 a_1 到 a_(n-1)
		}
		for(int i = 1;i < n;i++){
			printf("%d ", a[i]);
		}
		printf("%d\n", a[n - 1]); // 这里我们假设 a_n=a_(n-1)
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

考虑先将 $b$ 从小到大排序。

先考虑最小数的出现次数，设其为 $x$。那么他与其他点的贡献为 $\dbinom{x}{2} + x(n-x)$。于是我们可以求出最小值在原序列的出现次数。

同理其他数也可以，就做完了。

---

## 作者：I_am_kunzi (赞：0)

# CF1857C 题解

### 题目翻译

给你一个 $ n$，和 $ \frac {n \times (n - 1)} {2} $ 个数，是打乱后的 $ \min(a_1 , a_2) , \cdot \cdot \cdot , \min(a_1 , a_n) , \min(a_2 , a_3) , \cdot \cdot \cdot , min(a_{n - 1} , a_n)$。现在请你求出 **可能** 的原数组。

### 题目思路

我们将 $ \frac {n \times (n - 1)} {2} $ 个数从小到大排序，并规定 $ a_1 \le a_2 \le a_3 \le \cdot \cdot \cdot \le a_n$，即将原数组从小到大排序，那么前 $ n - 1 $ 个数的最小值一定是 $ a_1$。

证明：因为整个序列都是单调不减的，那么 $ \min(a_1 , a_2) , \cdot \cdot \cdot , \min(a_1 , a_n) $ 的值只有在整个数组相等时才可以是 $ a_1 \sim a_n $ 中任意一个位置的值（见样例 #4），但此时整个数组都相等，所以这个值与 $ a_1 $ 相等；否则找到最后一个位置 $ k $ 使得 $ a_k = a_1 , a_{k + 1} > a_1$，那么第二种情况可以转化为第一种情况，所以得到结论：前 $ n - 1 $ 个数的最小值一定是 $ a_1$。

同理可得，从第 $ n $ 个开始向下 $ n - 2 $ 个的最小值为 $ a_2$，一直推到第 $ \frac {n \times (n - 1)} {2} $ 个位置的值为 $ a_{n - 1}$。

那么第 $ n $ 个位置应该是什么？我们可以把第 $ n $ 个位置的值设为大于等于 $ a_{n - 1} $ 的任何值，这样不会改变最小值，也是为什么题面说 **可能** 的原数组的原因。

### 题目代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long // 可以在保证题目内存足够的情况下加上，比较保险
int a[1000005]; // 因为 n <= 1000，所以数组开到 1000 * 1000 即可，保险又不会 MLE
signed main()
{
	int t;
	cin >> t;
	while(t--)
	{
		memset(a , 0 , sizeof(a)); // 多测记得清空（虽然每次会覆盖之前的数据，但是清空会更保险）
		int n;
		cin >> n;
		for(int i = 1 ; i <= (n * (n - 1) / 2) ; i++)
		{
			cin >> a[i];
		}
		sort(a + 1 , a + (n * (n - 1) / 2) + 1);
		int minn = 2e9; // 最小值 minn 初始成比较大的 2e9
		int now = 1;
		for(int i = n - 1 ; i >= 1 ; i--) // 因为每轮需要的数越来越少，所以 i 也逐渐减少
		{
			minn = 2e9; // 每次重新赋值
			for(int j = 1 ; j <= i ; j++)
			{
				minn = min(minn , a[now]);
				now++; // 记录 now 为当前比较到的位置，避免了繁琐的计算
			}
			cout << minn << ' '; // 每次输出这一轮的最小值
		}
		cout << minn << endl; // 保险起见最后重新输出最后一轮比较的最小值
	}
    return 0;
}
```

---

