# [ABC227D] Project Planning

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc227/tasks/abc227_d

キーエンスには $ N $ 個の部署があり、$ i\,(1\ \leq\ i\ \leq\ N) $ 番目の部署には $ A_i $ 人の社員が所属しています。異なる部署に同じ社員が所属していることはありません。

キーエンスは、部署をまたいだ全社横断プロジェクトを計画しています。$ 1 $ つのプロジェクトは $ K $ 個の相異なる部署から $ 1 $ 人ずつ選出して作り、ちょうど $ K $ 人から構成されるようにします。

プロジェクトは最大でいくつ作れますか？ただし、$ 1 $ 人が複数のプロジェクトに参加することはできません。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^{12} $
- 入力は全て整数

### Sample Explanation 1

$ 3 $ 個の部署それぞれから $ 1 $ 人ずつ選出したプロジェクトを $ 2 $ つ作ることができます。

## 样例 #1

### 输入

```
3 3
2 3 4```

### 输出

```
2```

## 样例 #2

### 输入

```
4 2
1 1 3 4```

### 输出

```
4```

## 样例 #3

### 输入

```
4 3
1 1 3 4```

### 输出

```
2```

# 题解

## 作者：Ag2O2_2010_AC_gu (赞：9)

## 题目大意

给出 $n$ 个数，每次把任意 $k$ 个数减去 $1$，等于 $0$ 的数不能减，问最多能减几次？

## 思路

**枚举可以减去的次数。**

那么如何判断是否能减去 $x$ 次呢？

根据样例一可以画出下图：

![捕获.PNG](https://cdn.acwing.com/media/article/image/2023/04/05/159702_de0ee5fbd3-捕获.PNG) 

我们就先假设 $x=2$ 吧。

**对于每一个数，分为两种情况：大于等于 $x$ 和小于 $x$。**

### 当这个数大于等于 $x$ 时：

那么这个数减去 $x$ 次是肯定没有问题的了。

计数器加 $1$。

这时，$3$ 和 $4$ 就已经被毙掉了，剩个 $2$。

![捕获.PNG](https://cdn.acwing.com/media/article/image/2023/04/05/159702_fb914142d3-捕获.PNG) 

有人可能会问：$x$ 明明是 $2$，减去后 $3$ 和 $4$ 难道不应该变成 $1$ 和 $2$ 吗？

实际上，当这个数大于等于 $x$ 时，减去和毙掉没什么区别。

因为就算你把这个数减去 $x$，它剩下的也没有任何用处了。因为在 $x$ 次减去的过程中，这个数每一次都参与了，没有多出来的机会给剩下的来减。

这个细节其实在纸上模拟一下减去的过程就能想通了。

### 当这个数小于 $x$ 时：

剩下这些零零碎碎的，全部加起来，最后再看看能够凑出几个 $x$ 来。

于是我们把剩下的所有数加起来，到最后计数器加总和除以 $x$ 就行了。

刚刚已经把 $3$ 和 $4$ 毙掉了，剩下 $2$。

加起来的总和是 $2$，最后计数器只能加 $0$。

最终计数器是 $2$。

我们最后只需要判断计数器是否大于等于 $x$，如果大于等于的话就是能减去 $x$ 次，否则不能。

故能够减去 $2$ 次。

我们再去看一看数据范围，枚举很明显会超时。

**众所周知，二分答案是个好东西。**

## c++代码

```
#include<bits/stdc++.h>
#define ll long long//不开long long见祖宗
using namespace std;
int n,c;
ll h[1000100],l=0,r=1e18+1,mid,ans;
bool check(ll x) {
	ll sum=0,s=0;
	for(int i=1; i<=n; i++) {
		if(h[i]>=x) s++;//可以减x次
		else sum+=h[i];//零碎的加进去
	}
	s+=sum/x;//零碎凑出几个x
	return s>=c;//x的个数是否符合
}
int main() {
	scanf("%d%d",&n,&c);
	for(int i=1; i<=n; i++) scanf("%lld",&h[i]);
	if(n<c) {
		printf("0");
		return 0;
	}
	while(l+1<r) {//二分同时建立项目的个数
		mid=(l+r)/2;
		if(check(mid)) {
			l=mid;
			ans=mid;
		} else r=mid;
	}
	printf("%lld",ans);
	return 0;
}
```

**10 年 oi 一场空，不开 long long 见祖宗！**

---

## 作者：guanyf (赞：6)

 ### PART 1 题意:
一个公司有 $N$ 个部门，第 $i$ 个部门有 $A_i$ 名员工。不会有员工同时属于多个不同部门。
公司计划建立若干个横跨不同部门的项目，一个项目必须由来自不同部门的恰好 $K$ 名员工组成。
问最多可以同时建立多少个项目？

 ### PART 2 分析:
题目要求每 $K$ 个不同部门的员工组成一个项目，因此很容易的就会想到用项目来选员工，接着就延伸出了两种方法：

- **每次随便选出 $K$ 个部门**，将它们的人数减一，重复上述操作，直到有一个部门的人数为 0。

- **每次选出人数最大的 $K$ 个部门**，将它们的人数减一，重复上述操作，直到有一个部门的人数为 0。

当选则第一种方法时，可能会出现一种情况：没人的部门多，有人的部门虽然人数多却部门数量少。因为题目要求是**不同部门**的恰好 $K$ 名员工，这样做肯定不是最优的。

显然，选择第二种情况是正确的，但有许多缺点，因此肯定会超时。超时的原因：

- 排序次数多。

- 人多导致次数多。

[第一个点就 TLE 了](https://www.luogu.com.cn/record/102232428)
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int n,k,a[MAXN],ans;
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	int begin=1,end=n;//begin表示第一个不为0的值的下标
	while(end-begin+1>=k){
		ans++;
		for(int i=end;i>end-k;i--){
			a[i]--;
		}
		sort(a+begin,a+end+1);
		for(;!a[begin];begin++){}
		
	}
	cout<<ans;
	return 0;
}
```
### PART 3 思路:
既然上述思路会 TLE，因此不妨换一种视角去看题目：每次按部门来选人。因为直接选择比较困难，所以假定 $C$ 为项目数量，每个部门都包含着 $C$ 个项目的第 $i(1 \leq i \leq K)$ 项。
```cpp

样例：2
      1------------c=4
      2   1   
      3   2    
      4   3   4   0

长度：4   3   1   1
```
相同数字表示在同一个项目，0 表示未选择。

------------

当 $A_i$ 大于或者等于 $C$ 时，则可以将部门划分成两部分：

- 前 $C$ 个员工可以进入第 $j(1 \leq j \leq C)$ 项目的第 $i$ 项。
- 剩下的员工则直接放弃。



而当 $A_i$ 小于 $C$ 时，则将下一个部门与当前部门合并，大于 $C$ 的剩下的人保留在下一个部门。当前部门的 $C$ 个员工可以进入第 $j(1 \leq j \leq C)$ 项目的第 $i$ 项。

当每个项目都至少可以有 $K$ 个员工时，则当前答案合法，
否则当前答案不合法。

------------
接下来就是枚举 $C$，直接枚举肯定会 TLE。而通过 **如果当前答案即可行，则小于当前答案的任何答案也都可行**这个结论可以得出 $C$ 具有单调性。因此考虑二分答案。

左边界为 1，右边界为 $\sum{A_i}$。最后输出 $l-1$。

时间复杂度：$\mathit{O(N\log(\sum{A_i}))}$。
### PART 4 代码：
```cpp
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;
const int MAXN = 2e5 + 5;
long int n, k, a[MAXN], sum;
int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sum += a[i];
  }
  long int l = 1, r = sum;
  while (l <= r) {
    long int mid = (l + r) >> 1, cnt = 0, num = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] >= mid) {
        cnt++;
      } else {
        num += a[i];
        if (num >= mid) {
          cnt++, num %= mid;
        }
      }
    }
    cnt >= k ? l = mid + 1 : r = mid - 1;
  }
  cout << l - 1;
  return 0;
}

```
### PART 5 扩展：
```cpp

样例：2
      1   id=2
      2   1----------c=3
      3   2    
      4   3   4   0

长度：4   3   1   1
```
实际上，每次 $C$ 是可以平滑的变化的。根据前面的构造方法可以得知，实际上只要 $CK\leq$ 当前可用员工总数量时，$C$ 就是合法的。为了更方便的理解，可以想象成 $C$ 是一条分割线，把 $A$ 的顶端削去了一部分，剩下的部分 $\geq CK$，则答案合法。

假设当前选择到了部门 $i(0\leq i < N)$ 那么可以选择的人数就可以算出来（$A_i$ 是单调递减的，$pre$ 是前缀和），既然人数可以算出来，那么 $C$ 的最大取值也可以算出来：
$$Ci+pre_n-pre_i=CK$$
$$\frac{Ci+pre_n-pre_i}{C}=K$$
$$i+\frac{pre_n-pre_i}{C}=K$$
$$\frac{pre_n-pre_i}{C}=K-i$$
$$C=\frac{pre_n-pre_i}{K-i}$$
然而，可能出现两种情况：
- $C>A_i$：这样的话会使原来没有的 $C-A_i$多算进去，答案因此可能不合法。

-  $C<A_i+1$ 这样的话会将 $C$ 削去的部分算进去，因此也不合法。

实际上：$C$ 只是答案的最大取值，因此适当的更改取值范围即可让答案合法。

注意：答案有可能 $> A_1$，因此 $i$ 要从 0 开始遍历。 

另外：当找到第一个合法的答案时，那么那个答案一定时最优的。

时间复杂度：$\mathit{O(N\log(N))}$。
### code
```cpp
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;
using LL = long long;
const int MAXN = 2e5 + 5;
LL n, k, a[MAXN], sum[MAXN], c;
int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + 1 + n, greater<LL>());
  for (int i = 1; i <= n; i++) {
    sum[i] = sum[i - 1] + a[i];
  }
  a[0] = 1e18;
  for (c = 0; c < k && (sum[n] - sum[c]) / (k - c) < a[c + 1]; c++) {
  }
  cout << (sum[n] - sum[c]) / (k - c);
  return 0;
}

```


---

## 作者：Chenyanxi0829 (赞：3)

# 题意
一个公司有 $n$ 个部门，第 $i$ 个部门有 $a_i$ 名员工。一个项目必须由来自不同部门的恰好 $k$ 名员工组成。 问最多可以同时建立多少个项目？
# 暴力
如果随便选人的话，最后可能会出现人很多但却没有 $k$ 个部门不为空的情况，但如果每回都选人最多的那 $k$ 个部门的话，就能保证人数不为空的部门尽可能的多。

所以暴力思路就很容易想到了：每次将人最多的那 $k$ 个部门的人数减 $1$ ，直到没有 $k$ 个部门不为空。能减多少次就能建立多少项目。

可是这个思路的时间复杂度非常高，因为人数非常多并且人还是一个一个挑的。
# 满分做法

设每个部门的那 $a_i$ 个人的编号为 $j = 1 ,2 ,\dots,a_i $。

上面的思路是根据任务选人，可以换一个角度，根据部门来选人。先假设 $c$ 是需要建立的项目的个数，那校验的方法就是：看每个部门里编号 $\le c$ 的总人数人是否能凑足每个项目的 $k$ 个人。

构造方案的方法是：依次分人。

举个例子：有三个部门， $c=5 , k=2$ 
```cpp
5	\\凑出这5个项目的第一个人
2	\\凑出前2个项目的第二个人
3	\\凑出后3个项目的第二个人
```

### 怎么求出 $c$
最暴力的方法当然是枚举。

但可以发现， $c$ 是有单调性的，因为 $c$ 越小，能凑足这 $c$ 个项目的 $k$ 个人的可能性就越大。所以二分出 $c$ 就可以了。
```cpp
#include <algorithm>
#include <iostream>

using namespace std;
using LL = long long;

const int kMaxN = 2e5 + 5;

int n, k;
LL a[kMaxN], l = 1e12 + 1, r, mid;

bool C(LL c) {
  LL s = 0;
  for (int i = 1; i <= n; i++) {
    s += min(c, a[i]);
  }
  return s / c >= k;
}

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    l = min(l, a[i]);
    r += a[i];
  }
  while (l <= r) {
    mid = (l + r) / 2;
    if (C(mid)) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << r;
  return 0;
}
```

---

## 作者：mysterys (赞：1)

# 前言
这道题题意稍微复杂的一点，在做这道题之前可以先来看一下 [这一道题](https://www.luogu.com.cn/problem/P10184)。如果你的语文理解能力够好，就可以发现两道题其实一模一样。
# 题意简化
给你一个序列，每次可以将序列中的 $k$ 个数减一，数列的每一个元素必须大于等于 $0$，问最多可以减几次？
# 思路
- 发现：如果 $k$ 满足条件，则 $k-1$ 一定满足条件，所以答案**具有单调性。**
- $ 1\ \leq\ K\ \leq\ N\ \leq\ 2\ \times\ 10^5 $。

**综上，考虑二分答案。**

对于第 $i$ 个人数，设我们二分到的值为 $x$，则如果 $a_i \le x$，则全部都要加上，否则由于我们每天只需要加上 $x$ 即可。
# 注意事项
- $ 1\ \leq\ A_i\ \leq\ 10^{12} $，需要 ```long long```。
- 如果用乘法可能会爆，将乘法改成除法即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5E5+10;
long long n,k,a[MAXN],sum;
bool check(long long x){
	long long res=0;
	for(int i=1;i<=n;i++){
		if(a[i]>=x) res+=x;
		else res+=a[i];
	}
	return res/x>=k;//乘法改为除法。
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	long long r=sum,l=0,m,x=0;
	while(l<=r){
		m=l+((r-l)>>1);//防止溢出。
		if(check(m)){
			l=m+1;
			x=m;
		}else{
			r=m-1;
		}
	}
	cout<<x;
	return 0;
}
```

---

## 作者：Symbolize (赞：1)

# $\tt{Solution}$
首先最终的答案一定不会大于最大的 $a_i$，又由于 $1 \leq a_i \leq 10^{12}$，答案又具备单调性，所以不难想到二分答案，怎么判断当前答案是否可行呢？从本质入手，假设现在要判断能否完成 $x$ 个项目，那么每个部门最多派出 $x$ 个人，否则一定会有一个项目存在多个人属于同一个部门，然后你会发现，每个部门都把自己能选出来的人选出来（不够 $x$ 的部门就把所有人拿出来），那么这些人一定能够有一种匹配方案，使得没匹配上的人的个数不足 $x$，这就像你网桶里面放不同颜色的球，按一种颜色的球的个数从大到小放，每个桶至多只有一个某一颜色的球。最后的判断条件就是能派出的人的总人数是否大于需要的不同部门的个数乘上 $x$。

```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(auto i:x)
#define debug() puts("----------")
const int N=2e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
int n,k,a[N]; 
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
bool check(int x)
{
	int cnt=0;
	rep1(i,1,n) cnt+=min(x,a[i]);
	if(cnt>=x*k) return 1;
	return 0;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	k=read();
	int sum=0;
	rep1(i,1,n) a[i]=read(),sum+=a[i];
	int l=0,r=sum/k+1;
	while(l<r)
	{
		int mid=l+r+1>>1;
		if(check(mid)) l=mid;
		else r=mid-1;
	}
	cout<<l<<endl;
	return 0;
}

```

---

## 作者：WaterSun (赞：1)

# 思路

看到 $a_i \leq 10^{12}$ 这种较大值域的题，应当考虑二分。

不妨二分最终的答案，记作 $x$。那么，将题可以抽象为，有一个 $k \times x$ 的方阵，每一列放置的元素不能相同，对于第 $i$ 元素，放置的数量不得超过 $a_i$。

不难发现，如果单独考虑第 $i$ 种元素的放置情况，其中 $r$ 表示当前放置的这一行的元素数量，$t$ 表示当前已经放置完毕的行数。

1. $a_i \geq k$，说明第 $i$ 种元素可以将所有的 $x$ 列都放置一次，因此将 $t$ 加 $1$。

2. $a_i < x - r$，说明第 $i$ 种元素无法将当前行填满，因此将 $r$ 加 $a_i$。

3. $x - r \leq a_i < k$，说明第 $i$ 种元素可以将当前行填满，但是不能在所有的 $x$ 列中填上，因此将 $t$ 加 $1$，并将 $r$ 设为 $a_i - (x - r)$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10;
int n,k;
int arr[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 1) + (r << 3) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline bool check(int x){
    int cnt = 0,res = 0;
    for (re int i = 1;i <= n;i++){
        if (arr[i] >= x) cnt++;
        else if (arr[i] < x - res) res += arr[i];
        else{
            cnt++;
            res = arr[i] - (x - res);
        }
    }
    return (cnt >= k);
}

signed main(){
    n = read();
    k = read();
    for (re int i = 1;i <= n;i++) arr[i] = read();
    int l = 0,r = (int)(1e18);
    while (l < r){
        int mid = l + r + 1 >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    printf("%lld",l);
    return 0;
}
```

---

## 作者：GFyyx (赞：1)

### 审题&分析
  一个公司有 $N(1 \leq N \leq 2 \times 10^5)$ 个部门，第 $i$ 个部门有 $A_i$ 名员工。不会有员工同时属于多个不同部门。 公司计划建立若干个横跨不同部门的项目，一个项目必须由来自不同部门的恰好 $K(1 \leq K \leq N \leq 2 \times 10^5)$ 名员工组成。问最多可以同时建立多少个项目？

数据范围在 $10^5$ 范围内的题目我们能想到贪心或二分，
因为答案有单调性，这里主要介绍二分的思想。

### 解题思路
  直接二分答案项目数，设为 $x$，在每个部门中选取不超过 $x$ 但尽量多的员工，如果总人数超过 $x \times k$ 则该 $x$ 的取值合法。

### AC 代码（附有注释）
```cpp
#include <iostream>
using namespace std;
long long n,k,a[229028];//数组开够，开long long
inline bool check(long long x){
	long long res=0;
	for(register long long i=1; i<=n; i++) 
		res+=min(a[i],x);
	return res<x*k;
}//检索x
signed main(){
	cin >> n >> k;
	for(register long long i=1; i<=n; i++)
		cin >> a[i];
	long long l=1,r=1e18/k,mid;//二分 
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout << l-1 << endl;//答案为l-1 
	return 0;
}
```


---

## 作者：jiangruibo (赞：0)

### 思路：
一看这题的数据暴力是行不通的，而很明显的能看出这有一个单调性（项目数），所以我们就利用二分去枚举项目书即可，函数里面就统计零碎的和整的的个数是否满足要求，注意看数据范围。

### 代码
```
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define ull unsigned long long
#define write(n,x) cout<<setprecision(n)<<fixed<<x
typedef long long LL;
using namespace std;
int n,k;
int a[200010];
bool check(int mid) 
{
	int sum=0;
	int cnt=0;
	for(int i=1;i<=n;i++) 
	{
		if(a[i]>=mid) 
		{
			cnt++;
		}
		else 
		{
			sum+=a[i];
		}
	}
	cnt+=sum/mid;
	return cnt>=k;
}
signed main() 
{
	cin>>n>>k;
	for(int i=1;i<=n;i++) 
	{
		cin>>a[i];
	}
	int l=0;
	int r=1e18;
	int ans=0;
	while(l<=r) 
	{
		int mid=(l+r)/2;
		if(check(mid)==true) 
		{
			l=mid+1;
			ans=mid;
		} 
		else
		{
			r=mid-1;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：dhpzy (赞：0)

# 题意分析
首先，题目中说，一个项目必须由来自不同部门的恰好 $K$ 名员工组成，求最多能有几个项目。

根据贪心，每次选人时，每个部门只选一个人，因为这样可以剩下的人数更多，从而建立更多的项目。

于是题目便转化成：给你 $n$ 个数，每次选取 $k$ 个数减去一。若一个数为零，则不能选，问最多可以减几次。
# 思路
我们发现这个答案具有单调性，于是可以考虑二分。

若可以减 $x$ 次，那么总共会减去 $x \times K$。如果 $a_i \leq x$，那么这个数最多选 $a_i$ 次。反之，若 $a_i>x$，那么最多选 $x$ 次。

所以我们可以把每个数最多选几次加在一起，最后在判断是否小于 $x \times K$，若小于，则不行，否则可以。

```
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[1000001],l=1e18,r,ans;
bool check(long long x)
{
	long long s=0;
	for(int i=1;i<=n;i++) s+=min(a[i],x);
	return s/x>=t;
}
int main()
{
	cin>>n>>t;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),l=min(l,a[i]),r+=a[i];
	while(l<=r)
	{
		long long mid=l+r>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	cout<<r;
}
```

---

## 作者：loser_seele (赞：0)

首先考虑答案为 $ P $ 的情况。

设 $ sum $ 为 $ \min({a_i},P) $ 之和，当 $ P \times K > sum $ 的时候显然无解。否则我们可以证明当 $ P \times K \leq sum $ 的时候一定有解。

证明：

当有至少 $ K $ 个元素 $ \geq P $ 的时候显然能够造出一组解，否则我们每次选出 $ a_i $ 中最大的 $ K $ 个即可，满足条件。

于是二分答案 $ P $，时间复杂度 $ \mathcal{O}(n \times \log{\sum{a_i}}) $，可以通过。

代码：

```cpp
#import<bits/stdc++.h>
using namespace std;
#define int long long
int n,res,k,sum,a[1000001];
signed main() 
{
	cin>>n>>k;
	for (int i=1;i<=n;i++) 
	cin>>a[i];
	int l=0,r=1e18;
	while(l<r) 
	{
		int mid=(l+r+1)>>1;
		res=mid;
		sum=0;
		for (int i=n;i;i--) 
		{
			if (a[i]>=mid) 
			++sum; 
			else 
			res-=a[i];
			if(res<=0) 
			++sum,res+=mid;
		}
		if (sum>=k) 
		l=mid; 
		else 
		r=mid-1;
	}
	cout<<l;
}
```


---

## 作者：xz001 (赞：0)

- 首先一定是每次选择最大的 $k$ 个部门拖人，由于答案具有单调性，考虑二分答案。
- 然后我们对于每个部门，如果他的人数大于等于我们二分的 $mid$，则直接可选的部门加一，不大于等于的我们求一个和 $sum$，让他们互帮互助（其他的也会帮忙），再将可选的部门数加上 $\frac{sum}{mid} $，看看其数目有无超过 $k$ 即可。
- 时间复杂度 $O(n\log n)$，代码如下：

```cpp
#include <bits/stdc++.h>

using namespace std;

// define
#define re register
#define fi first
#define se second
#define il inline
#define co const
#define ls (u << 1)
#define rs (u << 1 | 1)
#define fup(x, l, r) for (re int x = (l), eNd = (r); x <= eNd; ++ x )
#define fdw(x, r, l) for (re int x = (r), eNd = (l); x >= eNd; -- x )
#define int long long
#define lowbit(x) ((x)&(-x))

// typedef
typedef pair<int, int> PII;
typedef long long LL;
typedef long double LD;

// const
const int N = 1e6 + 10, M = 1e9 + 1;
const int INF = 2e9, mod = 998244353;
const double eps = 1e-6;


// debug
const bool DeBug = true;
int db_cnt;
il void db() { if (DeBug) puts("--------------"); return; }
il void db(auto a) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << '\n'; return; }
il void db(auto a, auto b) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << ", " << b << '\n'; return; }
il void db(auto a, auto b, auto c) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << '\n'; return; }
il void db(auto a, auto b, auto c, auto d) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << ", " << d << '\n'; return; }
il void db(auto a, auto b, auto c, auto d, auto e) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : " << a << ", " << b << ", " << c << ", " << d << ", " << e << '\n'; return; }
il void db(auto *a, auto len) { if (DeBug) { ++ db_cnt; cout << "-- | t" << db_cnt << " : {"; if (!len) cout << "empty";else { cout << a[1]; for (int i = 2; i <= len; ++ i ) cout << ", " << a[i]; } cout << "}\n"; } return; }
il void db(pair<auto, auto> a) { if (DeBug) ++ db_cnt, cout << "-- | t" << db_cnt << " : <" << a.first << ", " << a.second << ">\n"; return; }

// common functions
il int Max(co int a, co int b) { return a > b ? a : b; }
il int Min(co int a, co int b) { return a < b ? a : b; }
il int read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { (c == '-') ? f = false : 0; c = getchar(); }while (c > 47 && c < 58) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(re auto x) { (x < 0) ? putchar('-'), x = -x : 0; (x > 9) ? write(x / 10) : void(); putchar(x % 10 + 48); return; }
il void wel(co auto x) { write(x), putchar('\n'); return; }
il void wel(co auto x, co int y) { write(x), putchar(' '), write(y), putchar('\n'); return; }
il void wel(co auto x, co int y, co int z) { write(x), putchar(' '), write(y), putchar(' '), write(z), putchar('\n'); return; }
il void wsp(co auto x) { write(x), putchar(' '); return; }

int n, k, a[N];

bool check (int mid) {
	int sum1 = 0, sum2 = 0;
	for (int i = 1; i <= n; ++ i) {
		if (a[i] >= mid) ++ sum1;
		else sum2 += a[i];
	}
	sum1 += sum2 / mid;
	return sum1 >= k;
}

signed main() {
    scanf("%lld%lld", &n, &k);
    for (int i = 1; i <= n; ++ i) 
    	scanf("%lld", a + i);
   
    int l = 1, r = 1e18, ans;
    while (l <= r) {
    	int mid = (l + r) >> 1;
    	if (check(mid)) {
    		ans = mid;
    		l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	printf("%lld\n", ans);
	return 0;
}


```

---

