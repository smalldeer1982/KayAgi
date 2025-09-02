# Maximum Sum

## 题目描述

You are given an array $ a_1, a_2, \dots, a_n $ , where all elements are different.

You have to perform exactly $ k $ operations with it. During each operation, you do exactly one of the following two actions (you choose which to do yourself):

- find two minimum elements in the array, and delete them;
- find the maximum element in the array, and delete it.

You have to calculate the maximum possible sum of elements in the resulting array.

## 说明/提示

In the first testcase, applying the first operation produces the following outcome:

- two minimums are $ 1 $ and $ 2 $ ; removing them leaves the array as $ [5, 10, 6] $ , with sum $ 21 $ ;
- a maximum is $ 10 $ ; removing it leaves the array as $ [2, 5, 1, 6] $ , with sum $ 14 $ .

 $ 21 $ is the best answer.

In the second testcase, it's optimal to first erase two minimums, then a maximum.

## 样例 #1

### 输入

```
6
5 1
2 5 1 10 6
5 2
2 5 1 10 6
3 1
1 2 3
6 1
15 22 12 10 13 11
6 2
15 22 12 10 13 11
5 1
999999996 999999999 999999997 999999998 999999995```

### 输出

```
21
11
3
62
46
3999999986```

# 题解

## 作者：Lovely_Chtholly (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF1832B)

### 【分析】

这里讲一种运用了双端队列的做法。

首先排序，然后求出全部删除 $1$ 个最大值时队列的和，接着把剩余序列前 $2$ 个值删掉，在序列末尾添加 $1$ 个已经通过删除最大值删掉的值（即减少 $1$ 次删除最大值的操作，增加 $1$ 次删除最小值的操作）。

以此类推寻找序列和的最大值即可，但是本题数据很大，需要开 long long（不开 long long 样例都过不了）。

### 【AC 代码】

```cpp
#include<algorithm>
#include<stdio.h>
#include<iostream>
#include<stack>
using namespace std;
#define int long long
const int N=2e5+10,INF=0x3f3f3f3f;
inline int read(char ch=getchar(),int n=0,int m=1)
{
	while(ch<'0' or ch>'9')
	{
		if(ch=='-')m=-1;
		ch=getchar();
	}
	while(ch>='0' and ch<='9')n=(n<<3)+(n<<1)+ch-'0',ch=getchar();
	return n*m;
}
ostream& operator <<(ostream& o,__uint128_t &a)
{
	__uint128_t x=a;
	stack<int>s;
	while(x)s.push(x%10),x/=10;
	while(!s.empty())o<<s.top(),s.pop();
	return o;
}
int t=read();
signed main()
{
	while(t--)
	{
		int n=read(),k=read(),a[N],sum=0,ans=-INF;
		deque<int>q;
		for(int i=1;i<=n;i++)a[i]=read();
		sort(a+1,a+1+n);
		for(int i=1;i<=n-k;i++)q.push_back(a[i]),sum+=a[i];
		ans=max(ans,sum);
		for(int i=n-k+1;i<=n;i++)sum+=a[i],q.push_back(a[i]),sum-=q.front(),q.pop_front(),sum-=q.front(),q.pop_front(),ans=max(ans,sum);
		cout<<ans<<"\n";
	}
	return 0;
}
```

ps：`#include<stack>` 和 `#include
<queue>`、`#include<deque>` 中竟然都包含 `deque`！

---

## 作者：LEle0309 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1832B)

乍一看是贪心，然后~~连样例都过不了~~。

于是，我想起了~~刚学的~~前缀和。

## 前缀和（大佬自行跳过）

前缀和是把一个数组 $ a $ 的第一项 $ a_1 $ 到第 $ i $ 项 $ a_i $ 的和存进前缀和数组 $ sum $ 的第 $ i $ 项 $ sum_i $ 里。

时间复杂度 $ O(n) $，十灰有用。

代码实现：

```cpp
//n是数组长度，sum十前缀和数组
//公式：sum[i]=sum[i-1]+a[i]
for(i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
```
回到本题，令删最小两数 $ i $ 次，则删最大数 $ k-i $ 次。

则剩下的和为 $ sum_{n-(k-i)}-sum_{2 \times i} $，然后打擂台求 $ ans $ 的值。

其中，$ sum_{n-(k-i)} $ 表示删最大数后剩下的和，$ sum_{2 \times i} $ 表示删掉的最小两数的和。

[AC 记录](https://www.luogu.com.cn/record/111450529)

AC Code：

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#define int long long//防见祖宗神器
using namespace std;
int a[200005],sum[200005],t,n,k,i;//俩数组
signed main()
{
    cin>>t;//t组数据
    while(t--)
    {
        int ans=0;
        memset(a,0,sizeof(a));//多测不清空，提交两行泪
        cin>>n>>k;
        for(i=1;i<=n;i++)cin>>a[i];
        sort(a+1,a+n+1);
        for(i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];//求前缀和
        for(i=0;i<=k;i++)ans=max(ans,sum[n-(k-i)]-sum[2*i]);//暴力枚举所有i，套公式，打擂台求最大值
        cout<<ans<<endl;//输出，注意换行
    }
    return 0;//养成好习惯
}
```

---

## 作者：winter2020 (赞：2)

考虑将 $a$ 数组排序，容易发现最后取的所有数是一个前缀和一个后缀。

枚举这个后缀的长度，可以计算出前缀取了多少个数，和可以用前缀和、后缀和优化。

时间复杂度 $O(n)$，可以通过。

计算出可行的前后缀长度时，必然可以通过一定的顺序完成删除操作，故只要前后缀长度正确，其和必然能取到。所以正确性得证。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 2e5 + 10;
int n, k;
LL a[N], s[N];

void solve() {
    cin >> n >> k;
    long long sum = 0, ans = 0;
    for (int i = 1; i <= n; i ++ ) {
        cin >> a[i];
        sum += a[i];
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i ++ ) s[i] = s[i - 1] + a[i];
    LL now = 0;
    a[n + 1] = 0;
    for (int i = n + 1; i > n - k; i -- ) {
        now += a[i];
        int t = k - (n - i + 1);
        ans = max(ans, sum - s[t * 2] - now);
    }
    cout << ans << endl;
    return;
}

int main()
{
    int T;
    cin >> T;
    while (T -- ) solve();
    return 0;
}
```

---

## 作者：Furina_Hate_Comma (赞：2)

一道简单题，考虑**双端队列**维护。

先排序，然后插入 $k$ 个元素。

接下来，每次滑过 $1$ 个窗口，从尾部弹出 $2$ 个元素，再从头插入 $1$ 个元素,然后更新最大值。

code:

```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
int a[500000];
using namespace std;
signed main(){
     int t;
     cin>>t;
     while(t--){
        deque<int>q;
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        sort(a+1,a+1+n);
//        for(int i=1;i<=n;i++)
//                cout<<a[i]<<" ";
//        cout<<endl<<k<<endl;
        int sum=0,ans=0,r;
        for(r=1;r<=n-k;r++){
            q.push_back(a[r]);
            sum+=a[r];
        }
//        cout<<r-1<<" "<<sum<<'\n';
        ans=max(ans,sum);
        for(;r<=n;r++){
            sum+=a[r];q.push_back(a[r]);
            sum-=q.front();q.pop_front();sum-=q.front();q.pop_front();
//            cout<<r<<" "<<sum<<'\n';
            ans=max(ans,sum);
        }
        cout<<ans<<"\n";
     }
}
```

---

## 作者：Sundar_2022 (赞：1)

### **【题目描述】**

给定一个长度为 $n$ 的数列，其中每个元素互不相同，进行 $k$ 次操作，每次可以选择删除序列中最小的两个数或最大的一个数。求操作后剩余数的和的最大值。


### **【思路】**

我们构造一组数据：

![](https://cdn.luogu.com.cn/upload/image_hosting/l6dmj0bp.png)

首先我们看到题目中的一句话：`每次可以选择删除序列中最小的两个数或最大的一个数。`，说明要对数组的最大值、最小值进行访问，于是考虑排序：

![](https://cdn.luogu.com.cn/upload/image_hosting/l77f5fwg.png)

假设我们现在的 $k$ 是 $3$，那么我们可以有以下几种删数的方法：

 - 删三次最大值:
![](https://cdn.luogu.com.cn/upload/image_hosting/nq9642o0.png)

 - 删两次最大值，一次最小值
![](https://cdn.luogu.com.cn/upload/image_hosting/d18sw8sj.png)

 - 删一次最大值，两次最小值
 ![](https://cdn.luogu.com.cn/upload/image_hosting/wk03l29y.png)
 
 - 删三次最小值
 ![](https://cdn.luogu.com.cn/upload/image_hosting/3wzzuikv.png)

**我们发现了什么？** 每一种删法都是删一段小元素，删一段大元素！我们可以使用前缀和先预处理一下，就可以求出剩下元素的和了。

代码 $O(n)$ 复杂度：
```cpp
#include <bits/stdc++.h>
using namespace std;

long long ans,a[1000005];
long long sum[1000005];
int T,n,k;

int main()
{
	scanf("%d",&T);
	while(T--)
	{
	    ans=0;
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}sort(a+1,a+1+n);
		for(int i=1;i<=n;i++){
			sum[i]=a[i]+sum[i-1];
		}
		for(int i=0;i<=k;i++){//枚举取多少个最大值
			ans=max(ans,sum[n-(k-i)]-sum[i*2]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：FinderHT (赞：1)

### 题目分析：
一个朴素的想法：每次排序，删除两个最小值或一个最大值之后求和，再维护最大值，但很明显会超出时间限制，因此我们要考虑其他方法。

我们先排序，这样每个操作要么删除两个最左边的元素，要么删除一个最右边的元素。排序后再求出输入的数组的前缀和，枚举操作次数设删除两个最小值时迭代操作次数为 $x$，那么删除最小值就是 $2x$ 次，也容易得出删除最大值就是 $k-x$ 次。因此，排序完且删除元素后数组所有元素的和为：
$h_{n-(k-x)}-h_{2 \times x}$。

### Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+10;
int a[MAXN];
ll h[MAXN];//由于前缀和增长速度快，所以用long long
inline void solve(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);//排序，数组保持有序是使所推出式子成立的条件
	for(int i=1;i<=n;i++)h[i]=h[i-1]+a[i];//前缀和
	ll maxa=0;
	for(int x=0;x<=k;x++)
		maxa=max(maxa,h[n-(k-x)]-h[2*x]);//排序后就可根据式子维护答案
	printf("%lld\n",maxa);
}
signed main(){
	int T;
	scanf("%d",&T);
	while(T--)
		solve();
	return 0;
}
```

## The End!

---

## 作者：__Dist__ (赞：1)

### 题目描述

详见[原题](https://www.luogu.com.cn/problem/CF1832B)

### 思路讲解

 $ n $ 和 $ k $ 的范围都很大，如果每次都重新算出剩余数的和，一定会超时。考虑优化，既然是求和，我们不妨排序后运用[前缀和](https://oi-wiki.org/basic/prefix-sum/)的知识，在输入结束后排序，然后求前缀和。最后维护 $ ans $ 求最大值，输出即可。
 
 多测别忘记清空！
 
 ### 代码环节
 ```cpp
#include<bits/stdc++.h>
#define int long long//由于前缀和增长地很快，保险用long long
using namespace std;
const int MAXN=2e5+5;
int T;
int qzh[MAXN],a[MAXN],k,n;
signed main(){
	cin>>T;
	while(T--){
		memset(qzh,0,sizeof qzh);
		memset(a,0,sizeof a);//多测不清空，爆零两行泪
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);//排序
		for(int i=1;i<=n;i++){
			qzh[i]=qzh[i-1]+a[i];//求前缀和
		}
		int ans=0;
		for(int i=0;i<=k;i++)//别忘了是从0开始 
			ans=max(ans,qzh[n-(k-i)]-qzh[2*i]);//维护ans 
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：sto_5k_orz (赞：1)

考虑枚举删最小两个的次数。

然后就可以确定删最大的次数。

于是维护一个前缀和，后缀和，记录一下删 $i$ 次最小的两个的和，删最大的数的次数的前缀和，暴力枚举删最小两个的次数，就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define CI const int
#define gc getchar
#define Mt(a, b) memset(a, b, sizeof a)
#define pc putchar
#define W while
#define I inline
#define pb push_back
#define ll long long
#define mk_p make_pair
#define pii pair<int, int>
#define int long long
namespace SlowIO {
	I int read() {
		int x = 0, f = 1; char ch = gc();
		W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
		W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
		return x * f;
	}
	I void Read(int &x) {x = read();}
	I void Read(int &x, int &y) {Read(x), Read(y);}
	I void write(int x) {
		if(x < 0) pc('-'), x = -x;
		if(x > 9) write(x / 10);
		pc(x % 10 + '0');
	}
	I void writeln(int x) {write(x); pc('\n');}
	I void Write(int x) {write(x); pc(' ');}
} using namespace SlowIO;
const int N = 200010; int a[N], s1[N], s2[N];
signed main() {
	int t; Read(t); W(t--) {
		int n, k, sum = 0; Read(n, k); for(int i = 1; i <= n; i++) Read(a[i]), sum += a[i];
		sort(a + 1, a + 1+ n);
		for(int i = 1; i <= k; i++) s1[i] = s1[i - 1] + a[2 * i - 1] + a[2 * i], s2[i] = s2[i - 1] + a[n - i + 1];
//		for(int i = 1; i <= k; i++) cout << s1[i] << ' ' << s2[i] << endl;
		int mi = 1e18; for(int i= 0; i <= k; i++) mi = min(mi, s1[i] + s2[k - i]);
		writeln(sum - mi);
	}
	return 0;
}
```

---

## 作者：WA_sir (赞：1)

## [题目](https://codeforces.com/problemset/problem/1832/B)|[链接](https://www.luogu.com.cn/problem/CF1832B)

说句题外话，这道题还是在语文课刚下课时突然想出来解法的（

题目中给出了两种操作：

1. 删除数列两个最小值

1. 删除数列一个最大值

因为 $2k$ $\leq$ $n$，所以这两种操作不会相互干扰。因此，执行顺序就不重要了，可以直接看操作后的结果。

因为操作的总量是固定的，和不变，两种操作的组合也只有 $k+1$ 种。所以可以用一个循环来计算每一种可能性，在从中取最大值，得出结果。

大家可能都会想到用前缀和优化，但我的方法是直接用两个变量来模拟两种操作各使数列剩余总和减少的量。

### 注意：

- 排序

- 有多组数据

### 参考程序：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,n,k,a[200005],b[200005];
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		scanf("%lld%lld",&n,&k);
		ll x=0,y=0,bb=0,sum=0,ans=0;
		for(ll i=1;i<=n;i++)scanf("%lld",a+i),sum+=a[i];
		sort(a+1,a+n+1);
		for(ll i=1;bb<=k;i+=2)b[++bb]=a[i]+a[i+1],x+=b[bb];
		x-=b[bb];
		for(ll i=1;i<k+2;i++)ans=max(ans,sum-x-y),x-=b[k-i+1],y+=a[n-i+1];
		printf("%lld\n",ans);
	}
	return 0;
}
```

感谢你读到这里！

---

## 作者：PCCP (赞：1)

作为 CF div.2 的第二题，这道题一定非常简单。所以我们从最简单的做法去思考。~~简单题最怕的就是想复杂了。~~

首先，题目告诉我们每次有两种操作：第一种操作是取数组里最小的两个数；第二种是取数组里最大的一个数。

不难发现，如果我们把数组按升序排序，第一种操作实际上就是取走队头的两个数，第二种实际上是取走最后的一个数。由于数组是固定不变的，所以不管我们怎么取，任何一种操作的任意一次取走的数都是固定不变的（前提是没有被另一种取走）。

这样就可以得到做法：从 $ \operatorname{0} $ 开始枚举第一种操作的次数，可以得到第二种操作的次数，进而得到每次取走了哪些数。然后求出剩余的数的和，取最大值即可。

设进行了 $ \operatorname{i} $ 次第一种操作，对应取走前 $ \operatorname{2} \times \operatorname{i}  $ 个数，则进行了 $ \operatorname{k} - \operatorname{i} $ 次第二种操作，对应取走后 $ \operatorname{k} - \operatorname{i} $ 个数，求和可以用前缀和快速求和。

代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int N=1e6+10;
int t,n,k;
long long res,a[N],sum[N];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}
		sort(a+1,a+1+n);
		for(int i=1;i<=n;i++){
			sum[i]=a[i]+sum[i-1];
		}
		for(int i=0;i<=k;i++){
			res=max(res,sum[n-(k-i)]-sum[i*2]);
		}
		printf("%lld\n",res);
		res=0;
		for(int i=1;i<=n;i++){
			a[i]=sum[i]=0;
		}
	}
}
```


---

## 作者：CheZiHe929 (赞：0)

# CF1832B 题解
## 原题链接
[**洛谷CF1832B**](https://www.luogu.com.cn/problem/CF1832B)

## 思路分析
**$sort$ 排序 $+$ 前缀和**

首先先建立一个前缀和数组 $s$，其中 $s_i$ 代表的就是前 $i$ 个数的总和。

让我们来推导一下公式：

既然只能进行 $2$ 种操作，所以我们不妨设第一种操作（即每次删掉最小的两个数）可以进行 $i$ 次，自然地，第二种操作（即每次删掉最大的一个数）就可以进行 $ k - i $ 次，那么我们就得到了剩下的数的和为:

$ s_{ n - ( k - i )} - s_{ 2 \times i }$。


其外，我们要注意题目中的一句话：
**本题有多组测试数据。**

很难不想到：多测不清空，爆零两行泪！所以我们每次要清空前缀和数组（长度为 $n$ 的序列 $a$ 数组其实不用清空）。

最后这道题就自然而然的解决了：

1. 每次清空前缀和数组 $s$。
2. 排序。
3. 求前缀和 $s$ 数组。
4. 定义 $ans = 0$，每次利用上面的公式求最大值（这里要注意一点，$0 \leq i\leq k$，所以我们循环的时候要从 $0$ 开始）。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long s[200005],a[200005],T,n,k,ans;
signed main(){
	cin>>T;
	while(T--){
		memset(s,0,sizeof(qzh));//清空前缀和数组（步骤一） 
		cin>>n>>k;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		sort(a+1,a+n+1);//排序（步骤二） 
		for(int i=1;i<=n;i++)
			s[i]=s[i-1]+a[i];//求前缀和（步骤三） 
		ans=0;
		for(int i=0;i<=k;i++)//别忘了是从0开始 
			ans=max(ans,s[n-(k-i)]-s[2*i]);//利用公式维护ans的值（步骤四） 
		cout<<ans<<endl;
	}
	return 0;
} 
```

## [AC 记录](https://www.luogu.com.cn/record/110776559)

**THE END.**

**THANK YOU.**

---

## 作者：yangmingshuo114514 (赞：0)

## 思路

考虑用排序与前缀和。

设一个前缀和数组 $s$，$s_i$ 表示前 $i$ 个数的和。

设删除最小的两个数的操作有 $i$ 次，则删除最大的一个数的操作有 $n-i$ 次。剩下的数的和就是 $s_{n-k+i}-s_{i \times 2}$。

答案即为 $\min_{i=0}^{k}\{s_{n-k+1}-s_{i \times 2}\}$。

## 代码

```cpp

#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#define ll long long
const int M=2e5+5;
using namespace std;
ll t,n,k,a[M],s[M],ans;
int main(){
	scanf("%lld",&t);
	while(t--){
		memset(s,0,sizeof s);
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
		ans=0;
		for(int i=0;i<=k;i++) ans=max(ans,s[n-k+i]-s[i*2]);
		printf("%lld\n",ans);
	}
	return 0;
}

---

