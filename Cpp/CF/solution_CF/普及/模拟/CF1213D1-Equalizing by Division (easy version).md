# Equalizing by Division (easy version)

## 题目描述

简单版和困难版之间的唯一区别在于数组元素的数量。

给定一个数组$a$，包含$n$个整数。每次操作你可以选择任一$a_i$并且将其除$2$向下取整（也就是说，每次操作中你可以使$a_i:=\lfloor \frac{a_i}{2} \rfloor$）。

你可以对任何$a_i$进行任意次（可以是零次）操作。

你的任务是计算最小的操作次数使得至少$k$个数组中的数字相等。

别忘了在几次操作后可能会有$a_i=0$的情况出现，因此答案始终存在。

## 样例 #1

### 输入

```
5 3
1 2 2 4 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 3
1 2 3 4 5
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 3
1 2 3 3 3
```

### 输出

```
0
```

# 题解

## 作者：andyli (赞：6)

将原序列中所有数进行处理，将当前处理的数计算所有它能变成的数以及变成那些数需要花费的**最小**次数，考虑如何最小化，只需将原序列从小到大依次处理即可。  
代码如下：  
```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 55, maxm = 200005;

int A[maxn];  // 原序列
int cnts[maxm]; // cnts[i]表示变成所有数均变成i需要的次数
int cntc[maxm]; // cntc[i]表示变成i的数量
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);
    sort(A + 1, A + n + 1); // 需要从小到大依次处理
    for (int i = 1; i <= n; i++) {
        int x = A[i], sum = 0;
        while (x) {
            if (cntc[x] < k) 
                cntc[x]++, cnts[x] += sum;
            // else 
            //  已经达到k个数字了，为了保证最小化次数所以不进行操作
            
            x /= 2;
            sum++;
        }
    }
    int ans = -1u / 2; // -1u/2=2^31-1
    for (int i = 1; i <= maxm; i++)
        if (cntc[i] >= k)
            ans = min(ans, cnts[i]); // 在所有满足条件的数中取出次数最小的
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：copper_ingot (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1213D1)

这里写的是困难版的做法，~~绝对不是因为困难版写不了题解才来这里写的。~~

首先，为了让操作次数尽量小，要给数组从小到大排序。

接下来我们定义 $cnt_x$ 为可以被化为 $x$ 的数的个数，$s_x$ 为让 $k$ 个数变成 $x$ 的最小花费。

我们从 $1$ 到 $n$ 枚举，设当前枚举的数为 $x$，同时定义一个累加器 $sum$ 计算花费。

每次让 $cnt_x$ 加上一，因为原来的 $x$ 能达到现在的 $x$。其次让 $s_x$ 加上 $sum$ 累计花费，然后更新 $x$ 的值，让 $x$ 变成 $x \div 2$。最后让 $sum$ 加一累计接下来的花费。如果 $cnt_x$ 已经达到了 $k$ 就不再累加 $cnt_x$ 和 $s_x$，因为已经足够了。

最后输出满足 $cnt_x \ge k$ 的 $x$ 对应的 $s_x$ 的最小值。

算法的时间复杂度是 $O(n\log n)$（代码时间复杂度最高的部分是排序），在 $n \le 2 \times 10^5$ 的情况下可以过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, a[200001], s[200001], cnt[200001], ans = 2147483647;
int main(){
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++){
		int x = a[i], sum = 0;
		while (x){
			if (cnt[x] < k) cnt[x]++, s[x] += sum;
			x /= 2; sum++;
		}
	}
	for (int i = 1; i <= 200000; i++)
		if (cnt[i] >= k) ans = min(ans, s[i]);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：wuyixiang (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1213D1)

题目大意：$n$ 个数，每次可以将任意一个数除以二，问至少需要操作多少次才能使至少 $k$ 个数相同。

思路：直接将每个数除以二的次数都用 $\operatorname{vector}$ 记录一遍，然后直接遍历答案中 $k$ 个相同的数值取前 $k$ 小即可。如果没有 $k$ 个，则直接进行下一次循环。答案取 $\operatorname{min}$ 即可。复杂度 $O(n \log n)$。

### AC code:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int a[200005],n,k,minn = 1e9;
vector<int>ve[200005];
int main()
{
    cin >> n >> k;
    for(int i = 1;i <= n;i ++)
    {
        cin >> a[i];
        int p = a[i],t = 0,r = 0;
        while(p >= 0 && r == 0)//0也要记录
        {
            if(p == 0 && r == 0)r = 1;
            ve[p].push_back(t);//vector记录
            t ++,p /= 2;
        }
    }
    for(int i = 0;i <= 200000;i ++)
    {
        if(ve[i].size() < k)continue;
        sort(ve[i].begin(),ve[i].end());//排序
        int u = 0;
        for(int j = 0;j < k;j ++)u += ve[i][j];//前k小
        minn = min(minn,u);//取最小值
    }
    cout << minn;//输出
}
```

---

## 作者：__HHX__ (赞：1)

# 思路
对于 easy 版，我们可以枚举要变成什么数 $b$，若 $a_i$ 能变成 $b$ 则记录步数，然后取前 $k$ 小的数，最后取最小数。

时间复杂度分析：

单次检查时，最坏情况为 $O(\log v)$。

查看每点时，时间复杂度故为 $O(v \log v)$。

因为要看到，前 $k$ 小的数，所以我们就用 $O(n \log n)$ 排序一下。

故最后时间复杂度 $O(v \log v + vn \log n)$。

带入最大值 $2 \times 10^5 \times 19 + 2 \times 10^5 \times 50 \times 7 = 73,800,000 \approx 8 \times 10^7 < 10^8$ 故不超时。

# 代码
```cpp
#include<iostream>
#include<algorithm>

using namespace std;

const int MaxV = 2e5 + 3, MaxN = 5e1 + 3;

int mi[MaxN], a[MaxN], minn = MaxV, maxx;

int cz(int x, int y){
	if(y == 0 && x != y) {
		return MaxV;
	}
	return x == y ? 0 : cz(x, y / 2) + 1;
}

int main() {
	int n, k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		maxx = max(maxx, a[i]);
	}
	for(int i = 0, sum = 0; i <= maxx; i++, sum = 0) {
		for(int j = 1; j <= n; j++) {
			mi[j] = cz(i, a[j]);
		}
		sort(mi + 1, mi + n + 1);
		for(int j = 1; j <= k; j++) {
			sum += mi[j];
		}
		minn = min(minn, sum);
	}
	cout << minn;
	return 0;
}
```

---

## 作者：Helium_Ship (赞：1)

介绍一种比较暴力的解法，对于 $\dfrac{a_i}{2^x}$，我们考虑建一个`vector`数组，下标对应 $\dfrac{a_i}{2^x}$，元素为 $x$，对于如果有大于 $k$ 个数的某个取值相同，我们就将`vector`排序，累加前 $k$ 个次数，答案即为所有和的最小值。

因为每个数 $a_i$ 最多贡献 $log(a_i)$ 个 $x$，而只有大于 $k$ 个数的某个取值相同，我们才进行后面的操作，所以时间复杂度应为 $O(\frac{\sum_{i=1}^{n}\log(a_i)}{k}\times(k \log(k)+k))$ 简化为 $O(n\log(v)\log(k))$，足矣通过这题。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[200010],ans=1e9,maxn;
vector<int> G[200010];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		cin>>a[i];
		int tmp=a[i];
		maxn=max(maxn,a[i]);
		int cnt=0;
		while (tmp){
			G[tmp].push_back(cnt);
			tmp>>=1;
			cnt++;
		}
	}
	for (int i=0;i<=200000;i++){
		if (G[i].size()<k)continue;
		sort(G[i].begin(),G[i].end());
		int sum=0;
		for (int j=0;j<k;j++){
			sum+=G[i][j];
		}
		ans=min(ans,sum);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：youngk (赞：1)

发现绝大多数的人都和官方题解的思路类似，然而其实可以不用的排序的方法也能AC这道题，就是这个题目的数字范围小于等于200000，呢么统计每个值的个数，从小到大往大的方向bfs搜索，当搜索到值大于200000时就可以不再搜索了，这样的复杂度也是O(nlogn)，但在cf中跑的比官方题解快很多，而且元素的个数也可再增加

代码:

```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<set>
#define _USE_MATH_DEFINES
#include<math.h>
#include<queue>
#include<vector>
#include<limits.h>
#include<functional>
#include<stack>
typedef long long ll;
#pragma GCC optimize(2)
using namespace std;
inline void write(int x)
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
int a[300000];
int n, k, ans[300000];
int aans = INT_MAX;
struct node
{
	int num, times;
};
void bfs(int x)
{
	int num = k;
	queue<node> q;
	q.push({ x,0 });
	while (num > 0)
	{
		node u = q.front();
		q.pop();
		int xx = u.num, yy = u.times;
		if (xx > 200000)
		{
			ans[x] = -1;
			return;
		}
		if (num > a[xx])
		{
			num -= a[xx];
			ans[x] += a[xx] * yy;
		}
		else
		{
			ans[x] += num * yy;
			return;
		}
		if (xx == 0)
		{
			q.push({ 1,yy + 1 });
		}
		else
		{
			q.push({ (xx << 1),yy + 1 });
			q.push({ (xx << 1) + 1,yy + 1 });
		}

	}
}
signed main()
{
	n = read(), k = read();
	for (int i = 0; i < n; i++)
		a[read()]++;
	for (int i = 0; i <= 200000; i++)
	{
		bfs(i);
	}
	for (int i = 0; i <= 200000; i++)
	{
		if (ans[i] == -1)
			continue;
		aans = min(ans[i], aans);
	}
	write(aans);
	return 0;
}

```


---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1213D1)

## 思路
这里介绍的是困难版的 $O(n \log n)$ 做法，~~绝对不是因为我做的是困难版的。~~

我们可以对于每个 $a_{i}$ 都记录下其能够变成的数与需要的操作次数，然后以变成的数、所需操作次数这两个关键字从小到大排序。

然后记录下已变成相同的数的个数 $cnt$ 与所需的总操作次数 $need$，每次当变成的数与之前不一样时将这两个清零，当 $cnt \ge k$ 时令答案 $ans = \min(ans, need)$。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (int i = ed; i >= st; --i)
#define fir first
#define sec second

//#define debug

typedef long long ll;
typedef double db;
typedef pair<ll, ll> pll;

struct Num {
	int val, stp;

	bool operator< (Num x) const {
		return ((val != x.val) ?(val < x.val) :(stp < x.stp));
	}
};
const int inf = 0x3f3f3f3f;
const int maxn = 2e5 + 10;
const int maxlogn = 18 + 10;

int n, k;
	int a;

int len, cnt, need, ans = inf;
Num num[maxn*maxlogn];

void work_n () {
	scanf("%i", &a);

	num[++len] = {a, 0};
	int cnt = 0;
	while (a) {
		a /= 2;
		++cnt;
		num[++len] = {a, cnt};
	}
}
int main () {
	scanf("%i%i", &n, &k);
	FOR (1, n, i) {work_n();}

	sort(num + 1, num + len + 1);
	FOR (1, len, i) {
		if (num[i].val != num[i - 1].val) {
			cnt = need = 0;
		}
		++cnt;
		need += num[i].stp;
		if (cnt >= k) {
			ans = MIN(ans, need);
		}
	}

	printf("%i\n", ans);
	return 0;
}
```

---

## 作者：czh___ (赞：0)

题意：一次操作是数组中的某个元素除以 $2$ 下取整。问最少操作多少次可以使这个数组中有 $k$ 个相等的数字。

思路：我们用 $num_x$ 记录 $x$ 出现过的次数，$cnt_x$ 记录到达现在的 $x$ 数量，需要操作的次数。不断的更新最小值。

代码如下：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxx=2e5+1;
int cnt[maxx],num[maxx],a[maxx],n,k;
signed main(){
	scanf("%d%d",&n,&k);
	memset(cnt,0,sizeof(cnt));
	memset(num,0,sizeof(num));
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),
		num[a[i]]++;
	stable_sort(a+1,a+1+n);
	int ans=0x7f7f7f7f;
	for(int i=1;i<=n;i++){
		int x=a[i];
		int cnt1=0;
		while(x){
			if(num[x]>=k) ans=min(ans,cnt[x]);
			x>>=1;
			cnt1++;
			num[x]++;
			cnt[x]+=cnt1;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

[改编于](https://blog.csdn.net/starlet_kiss/article/details/102511626?ops_request_misc=&request_id=&biz_id=102&utm_term=CF1213D1%20Equalizing%20by%20Divisio&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-102511626.142^v100^pc_search_result_base5&spm=1018.2226.3001.4187)

---

## 作者：HEzzz (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1213D1)

## 解析

我们先对于原数列的每一个数都求出它可能变成的那些数以及需要的次数，定义 $cnt_i$ 表示当前有多少个数字 $i$，$s_i$ 表示当前数字 $i$ 有 $cnt_i$ 个的最小操作次数。

为了得到数字 $i$ 的最小操作次数，我们可以贪心地将原数列排序，这样得到的数字 $i$ 的操作次数变少，例如我们有两个数分别为 $8$ 和 $32$，那么得到数字 $2$ 的操作次数分别为 $2$ 和 $4$ 次，显然把 $4$ 变成数字 $2$ 更优于数字 $32$。所以我们排序后一旦 $cnt_i$ 已经达到了 $k$ 个，那么后面的数字就不要变成数字 $i$ 了，同时记录 $s_i$ 操作次数。

最后我们依次枚举答案是哪个数字判断是否可行并求出最小的操作次数即可。

## code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _antirep(i,a,b) for(int i=(a);i>=(b);--i) 
using namespace std;
typedef long long LL;
typedef double db;
const int N=5e1+5,M=2e5+5;  
int n,k,a[N],s[M],cnt[M],ans=INT_MAX;
signed main()
{        
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);  
	cin>>n>>k;
	_rep(i,1,n) cin>>a[i];
	sort(a+1,a+n+1);
	_rep(i,1,n)
	{
		int x=a[i],res=0;
		while(x)
		{
			if(cnt[x]<k) cnt[x]++,s[x]+=res;
			x/=2,res++;
		}
	} 
	_rep(i,1,M-1) if(cnt[i]>=k) ans=min(ans,s[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

直接暴力！！！

对于每一个数，枚举它能生成的数。

然后对于每一个可能的答案，开长度为 $k$ 的优先队列维护，同时统计操作次数和。

时间复杂度为 $Θ(\log^2_2n)$。
惊讶地发现顺便把[双倍经验](https://www.luogu.com.cn/problem/CF1213D2)给切了。（卡过）

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,n,k,sum[200010],ans=INT_MAX;
priority_queue<int>q[200010];
void add(int x,int pos){
	if(q[pos].size()<k)sum[pos]+=x,q[pos].push(x);
	else if(q[pos].top()>x){
		sum[pos]-=q[pos].top();
		q[pos].pop();
		sum[pos]+=x;
		q[pos].push(x);
	}
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		add(0,x);
		int cnt=0;
		while(x){
			cnt++;
			x>>=1;
			add(cnt,x);
		}
	}
	for(int i=0;i<=200000;i++)
		if(q[i].size()==k)ans=min(ans,sum[i]);
	printf("%d",ans);
	return 0;
} 
```

---

## 作者：guozhe6241 (赞：0)

# 题目传送门

[CF1213D1](https://www.luogu.com.cn/problem/CF1213D1)

# 思路

简单版和困难版区别就在于 $n$ 的范围，一个是 $50$，另一个是 $2\cdot10^5$，但本质做法没有区别。

这题我们需要两个数组，一个存这个数可以出现多少次，另一个存到这个数的次数。

我们在输入时取数组中最大值，方便最后输出。

对于每个数，我们考虑这个数能变成哪些数，每次对这个数除以 $2$，如果这个数的出现次数小于 $k$，那么我们将个数加一，次数加上与上一个变出这个数的操作间隔次数。

最后从 $1$ 遍历到最大值，如果这个数出现次数大于 $k$，我们就将答案取最小值，最后输出即可。

时间复杂度 $O(n \log n)$，意味着此代码可以同时通过简单和困难版。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+5;
int n,k;
int maxx=-1000000000;
int ans=1000000000;
int a[maxn];
int cnt1[maxn],cnt2[maxn];
signed main(){
	cin>>n>>k;
	memset(cnt1,0,sizeof(cnt1));
	memset(cnt2,0,sizeof(cnt2));
	for(int i=1;i<=n;i++){
		cin>>a[i];
		maxx=max(maxx,a[i]);
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		int tmp=a[i],sum=0;
		while(tmp){
			if(cnt1[tmp]<k){
				cnt1[tmp]++;
				cnt2[tmp]+=sum;
			}
			tmp/=2;
			sum++;
		}
	}
	for(int i=1;i<=maxx;i++){
		if(cnt1[i]>=k){
			ans=min(ans,cnt2[i]);
		}
	}
	cout<<ans<<endl;
    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/142486804)

---

## 作者：minVan (赞：0)

**题目大意**

给定 $n$ 个数，每次操作可以将一个数除以 $2$ 再向下取整，求最少几次操作可以让至少 $k$ 个数相同。

**解题思路**

可以发现对于一个数字 $x$，它不停的除以 $2$ 再向下取整，最多可以产生 $\log_{2}x$ 个数字，所以最多有 $n\times\log_{2}n$ 个数字，我们把这些数字出现所需要进行的除法次数放到动态数组 $b_i$ 里面，$b_i$ 里面保存的是把这 $n$ 个数字变成 $i$ 所需要的次数，当然，有的数字不能变成 $i$。然后我们只需要从所有的 $b_i$ 分别计算他们自己中最小的 $k$ 个数字之和，这表示把数字变成 $i$ 的所需要的操作次数最小的 $k$ 个数的次数之和是多少。然后从 $0$ 至 $200000$ 都找一遍，就得到最小的答案。

**AC 代码，请勿抄袭**

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, k;
int a[N];
vector<int> b[N];
int ans = INT_MAX, sum;
inline void solve(int x) {
    int cnt = 0;
    while(x > 0) {
        b[x].push_back(cnt);
        x /= 2;
        cnt++;
    }
    b[x].push_back(cnt);
}
int main() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        solve(a[i]);
    }
    for(int i = 0; i < N; i++) {
        sum = 0;
        if(b[i].size() < k) {
            continue;
        }
        sort(b[i].begin(), b[i].end());
        for(int j = 0; j < k; j++) {
            sum += b[i][j];
        }
        ans = min(ans, sum);
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：览遍千秋 (赞：0)

这道题不算很难，我直接切的D2qwq

---

## $\mathrm{D1,D2}$的区别

观察D1和D2的区别，发现主要是$n,k$的范围不太一样，发现$a_i$的范围同样都是$\le 2 \times 10^5$，不像常规题目$a_i$的范围都是$\le 2 \times 10^9$，于是想到从$a_i$上面搞些事情。

---

## 解法

考虑枚举最后变成的数，只需要预处理出所有$a_i$可以变成的数$b_j$和需要的步数，按照变成的数$b$为第一关键字，需要的步数为第二关键字排序，枚举$b$即可。

---

## $\mathrm{code}$

```
#include<bits/stdc++.h>
using namespace std;
 
#define maxn 5000007
#define maxm 200007
 
//#define edgew
 
template <typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh;
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-'){
		fh=-1;ch=getchar();
	}
	else fh=1;
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}
 
struct node{
	int num,val;
};
 
int n,m;
node a[maxn];
 
void readin(){
	for(int i=1;i<=n;i++) read(a[i].num);
}
 
 
int tot;
 
bool comp(node a,node b){
	return a.num==b.num?a.val<b.val:a.num<b.num;
}
 
int cnt,ans=0x3f3f3f3f,ret;
int lim;
int main(){
	read(n);read(lim);tot=n;
	readin();
	for(register int i=1;i<=n;i++){
		int k=a[i].num;int p=0;
		do{
			k>>=1;;++p;
			a[++tot].num=k,a[tot].val=p;
		}while(k);
	}//
	sort(a+1,a+tot+1,comp);
	for(register int i=1;i<=tot;i++){
		if(a[i].num!=a[i-1].num||i==1){
			ret=a[i].val;cnt=1;
		}
		else{
			ret+=a[i].val,cnt++;
		}
		if(cnt>=lim) ans=min(ans,ret);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

