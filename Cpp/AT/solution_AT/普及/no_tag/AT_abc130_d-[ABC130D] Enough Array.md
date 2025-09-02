# [ABC130D] Enough Array

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc130/tasks/abc130_d

長さ $ N $ の正整数列 $ A=a_1,a_2,…,a_{N} $ と整数 $ K $ が与えられます。$ A $ の連続する部分列であって、以下の条件を満たすようなものは何個あるでしょうか。

- (条件) 連続部分列に含まれる全ての要素の値の和は、$ K $ 以上である。

ただし、ある二つの連続部分列が列として同じでも、取り出された位置が異なるならそれらは別々に数えるものとします。

出力が $ 32bit $ 整数型に収まらない場合があることに注意してください。

## 说明/提示

### 制約

- $ 1\ \leqq\ a_i\ \leqq\ 10^5 $
- $ 1\ \leqq\ N\ \leqq\ 10^5 $
- $ 1\ \leqq\ K\ \leqq\ 10^{10} $

### Sample Explanation 1

\- $ A[1..4]=a_1,a_2,a_3,a_4 $ (要素の値の和は $ 16 $) - $ A[2..4]=a_2,a_3,a_4 $ (要素の値の和は $ 10 $) の二通りです。

### Sample Explanation 2

ある二つの連続部分列が列として同じでも、取り出された位置が異なるならそれらは別々に数えることに注意してください。

## 样例 #1

### 输入

```
4 10
6 1 2 7```

### 输出

```
2```

## 样例 #2

### 输入

```
3 5
3 3 3```

### 输出

```
3```

## 样例 #3

### 输入

```
10 53462
103 35322 232 342 21099 90000 18843 9010 35221 19352```

### 输出

```
36```

# 题解

## 作者：Star_Wind (赞：5)

~~我感觉这个D和ABC155的D完全不是一个等级的~~

思路：对读入的数做前缀和，之后 while 循环双指针枚举。直到$sum[r]-sum[l]$大于$k$

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum[111111],n,k,x,ans,l,r;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		sum[i]=sum[i-1]+x;	
	}
	while(r<=n)
	{
		if(sum[r]-sum[l]<k) {r++;continue;}
		ans+=(n-r+1);
		l++;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Justinalx (赞：1)

# **1.开始**
不再废话了。直接用尺取。
# **2.思路**
尺取解释：
定义 $l$ 和 $r$ 为数组第一个元素下标。然后 $r$ 开始递增且累加 $a_i$，直到满足题目条件,记下这个子序列的长度。形成一个新的子序列。再判断新的子序列和满不满足条件,如果满足条件，$l$ 向右移动，形成一个新的子序列。如果不满足则往后加一个新元素，直到子序列和满足条件为止。如果遇到求子序列和一直加到数组最后一个元素还是不满足条件，就可以跳出循环。

给出 $n$ 个数，问这些数中有多少个连续子序列的和大于等于 $k$。我们用两个指针 $l$ 和 $r$，分别表示左指针和右指针，用 $sum$ 表示记录的个数。两个指针从第一个位置开始，每一次 $r$ 向右移一位，都判断有没有超过 $k$，如果超过，停止执行，$sum$ 加上 $n-r+1$,因为当前位置已经满足题目条件了，那再加下去肯定也满足题目条件。**注意，此题中数据不包含负数，如果有负数另当别论。因为加上负数有可能小于曾经的最大值。** 然后 $l$ 向右移，循环再进行一遍。直到 $l$ 到达最后。

为了加快速度，我们可以用**前缀和**，如此我们可以轻而易举的算出 $a_r$ 到 $a_l$ 之间的总和，不用再一遍遍的去累加。
# **3.程序（仅供参考）**
尺取部分：
```cpp
	if(sum[r]-sum[l]<k) {r++;continue;}
	ans+=(n-r+1);
	l++;
```
# **4.最后**
此题的重难点在于，**尺取的思路和尺取时的优化**，即 
```cpp
             ans+=(n-r+1);
```



---

## 作者：BMTXLRC (赞：1)

看到这题首先可以想到一个 $\mathcal{O}(n^2)$ 的暴力，原理是枚举 $i,j$，找到所有满足 $sum_i-sum_{j-1}\geqslant k$ 的 $(i,j)$。

我们可以改变一下柿子，一端只包含 $i$，另一端只包含 $j$，那么就会变成这样：

$$
sum_i-k\geqslant sum_{j-1}
$$

继续往下思考，发现整个 $sum$ 数组都是静态的（显然我也懒得说），那么我们就可以创建一棵平衡树，存储 $sum_i$，每次找到小于等于 $sum_i-k$ 的节点有多少个。

注意：因为 $j-1$ 是有可能等于 $0$ 的，所以我们一开始就可以把 $0$ 插入到平衡树中。

这样时间复杂度变成 $\mathcal{O}(n\log n)$，我是用 FHQ Treap 实现的，打校内比赛因为思路错了（错了就是指的想到平衡树上了），所以浪费了很多时间没时间开后面题（但我知道后面还有一道线段树呜呜呜）。

~~警示后人：看上去明显不是平衡树的题就别用平衡树做了。~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+5;
int n,m,cnt,root;
struct FHQ_treap{
    int l,r,x,pri;
    int size;
}a[N];
int new_node(int x){
    a[++cnt].x=x;
    a[cnt].pri=rand();
    a[cnt].size=1;
    return cnt;
}
void pushup(int x){
    a[x].size=a[a[x].r].size+a[a[x].l].size+1;
    return;
}
void split(int now,int k,int &x,int &y){
    if(!now){
        x=y=0;
        return;
    }
    if(a[now].x<=k){
        x=now;
        split(a[now].r,k,a[now].r,y);
    }else{
        y=now;
        split(a[now].l,k,x,a[now].l);
    }
    pushup(now);
}
int merge(int x,int y){
    if(!x||!y) return x+y;
    if(a[x].pri<a[y].pri){
        a[x].r=merge(a[x].r,y);
        pushup(x);
        return x;
    }else{
        a[y].l=merge(x,a[y].l);
        pushup(y);
        return y;
    }
}
int ans=0,sum=0;
signed main(){
    scanf("%lld %lld",&n,&m);
    int x,y;
    split(root,0,x,y);
    root=merge(merge(x,new_node(0)),y);
    for(register int i=1;i<=n;i++){
        int k,x,y;
        scanf("%lld",&k);
        sum+=k;
        split(root,sum-m,x,y);
        ans+=a[x].size;
        root=merge(x,y);
        split(root,sum,x,y);
        root=merge(merge(x,new_node(sum)),y);
    }
    printf("%lld\n",ans);
}
```


---

## 作者：iiawaKL (赞：1)

# 蒟蒻写题解啦awa

PS：本蒟蒻刚刚买了LOFREE的键盘，好用极啦！

话不多说，直奔主题。

枚举两个点，暴力搜中间的算法不行，前缀和也会t，那就只剩下->二分了。

 _Code->_ 
 
 ```
#include<bits/stdc++.h>
using namespace std;
long long n,k,x,a[100010],ans;
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>x;
        a[i]=a[i-1]+x;
    }
    for(int i=0;i<n;i++){
        int mid=lower_bound(a+1,a+n+1,a[i]+k)-a;
        ans+=n+1-mid;
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：_szs9601 (赞：0)

#### 思路
这题的题意已经在题目中给出了，所以我直接讲思路。

写代码之前，我们需要想到一件事。就是如果当前的这个子序列的和已经大于等于 $m$ 了，我们就可以不用继续往下去做。因为 $a_i$ 都是正数，继续往后加只会越来越大。

通过这个，我们可以很容易想到前缀和优化。之后 ``while`` 循环双指针枚举，直到子序列之和大于等于 $m$。
#### 代码
```cpp
#include<bits/stdc++.h>
#define LL long long//因为需要前缀和，所以和很容易超过int
using namespace std;
LL n,m,i,t,w,a[100100],s,ans;
int main(){
	scanf("%lld%lld",&n,&m);
	for(i=1;i<=n;i++) scanf("%lld",&a[i]),a[i]+=a[i-1];
	t=1;w=1;//双指针
	while(w<=n){
		if(a[w]-a[t-1]<m){w++;continue;}
		ans+=n-w+1;
		t++;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Otue (赞：0)

做法：前缀和 + 二分。

# 思路
可以想到：对于一个数 $a_i$，慢慢往后面加数，等总和大于 $k$ 时，就可以停止了，因为继续往后加肯定比 $k$ 大。 

所以对于一个 $a_i$ ，只需要找到一个位置使得加起来的总和大于 $k$ 即可。

由于所有数是正数，慢慢加肯定越来越大，具有单调性，故可以二分。

# 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e5 + 5;
int n, k, a[N], sum[N];
int res;

signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i], sum[i] = sum[i - 1] + a[i];    //sum 是前缀和
	for (int i = 1; i <= n; i++) {
		if (sum[n] - sum[i - 1] < k) continue; 
		int l = i, r = n;   // 二分边界
		while (l < r) {
			int mid = (l + r) / 2;
			if (sum[mid] - sum[i - 1] >= k) r = mid;
			else l = mid + 1;
		}
		res += n - l + 1;
	}
	cout << res << endl;
}
```

---

## 作者：xiaoPanda (赞：0)

### Problem
给出 $n$ 个数，问有多少个连续子序列的和大于等于 $k$。

### Solution
#### 尺取法
先对原数列求前缀和 $sum_i$ 以便求区间和，很明显，前缀和具有单调性。

然后令 $l,r$ 表示选了区间 ，很明显 $\sum_l^r=sum_r-sum_{l-1}$。

令 $s$ 表示 $sum_r-sum_{l-1}$，这时候分成两种情况：

+ $s\ge k$，注意 $sum_{r+w}-sum_{l-1}>sum_{r}-sum_{l-1}\ge k(w>0)$，所以让 $l$ 为左端点， $r$ 到 $n$ 中任意一个点为右端点的子序列，其和一定大于等于 $k$，答案增加 $n-r+1$ 个,进行完此步以后要尝试更小的区间，所以左端点 $l$ 加 $1$。

+ $s<k$，同样还是 $sum_{r+w}-sum_{l-1}>sum_{r}-sum_{l-1}(w>0)$，所以这时应该让 $r$ 增加，因为不知道 $r$ 要增加多少才大于等于 $k$ 所以 $r$ 应该只增加 $1$。但是不能增加 $l$ ,应为 $l-1$ 在之前的程序中已经计算过了。

当 $l>r$ 或者 $r>n$ 的时候代表已经没有其他答案了，直接输出。

注意一下初始时区间是 $[1,1]$ 的，也就是说 $l=r=1$。

因为 $l$ 和 $r$ 不会走回头路，而每次判断总会有一个加 $1$，所以时间复杂度为 $O(n)$。
### 二分法
暴力枚举左端点 $l$ ，因为前缀和具有单调性，所以可以二分第一个满足和大于等于 $k$ 的右端点 $r$。

具体的，找到一个右端点 $r$ 使得 $sum_{r-1}-sum_{l-1}<sum_r-sum_{l-1}$ 并且 $sum_r-sum_{l-1}\ge k$，根据上面的情况 $1$ 的推论，答案应该增加 $n-r+1$ 个。

其实二分可以用 lower_bound， $sum_r-sum_{l-1}\ge k$ 可以变成  $sum_r\ge k+sum_{l-1}$ ,时间复杂度为 $O(n\log n)$。
### Code
```cpp
/* 尺取法 */
int n,m,l,r,ans=0;
cin>>n>>m;l=r=1;
for(int i=1;i<=n;i++)
cin>>a[i],sum[i]=sum[i-1]+a[i];//前缀和
while(l<=r&&r<=n)
{
	if(sum[r]-sum[l-1]>=m)//情况1
	ans+=n-r+1,l++;//统计答案
	if(sum[r]-sum[l-1]<m)//情况2
	r++;
}
cout<<ans;
```
```cpp
/* 二分法 */
int n,m,ans=0;
cin>>n>>m; 
for(int i=1;i<=n;i++)
cin>>a[i],sum[i]=sum[i-1]+a[i];//前缀和
for(int i=1;i<=n;i++)
{
	int k=lower_bound(sum+1,sum+n+1,sum[i-1]+m)-sum;//二分
	ans+=n-k+1;//统计答案
}
cout<<ans;
```

---

