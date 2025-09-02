# [ABC102D] Equal Cut

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc102/tasks/arc100_b

すぬけ君は、長さ $ N $ の整数列 $ A $ を持っています。

すぬけ君は $ A $ を $ 3 $ 箇所で切って、$ 4 $ つの（空でない）連続する部分列 $ B,C,D,E $ に分解します。 切る位置は自由に選ぶことができます。

ここで、整数列 $ B,C,D,E $ について、その要素の総和をそれぞれ $ P,Q,R,S $ とおきます。 すぬけ君は、$ P,Q,R,S $ の最大値と最小値の差の絶対値が小さいほど嬉しいです。 $ P,Q,R,S $ の最大値と最小値の差の絶対値としてあり得る最も小さい値を求めてください。

## 说明/提示

### 制約

- $ 4\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

$ B,C,D,E=(3),(2),(4),(1,2) $ と分割すれば、$ P=3,Q=2,R=4,S=1+2=3 $ となります。 このとき、$ P,Q,R,S $ の最大値は $ 4 $、最小値は $ 2 $ で、その差の絶対値は $ 2 $ です。 最大値と最小値の差の絶対値を $ 2 $ 未満にすることは出来ないため、$ 2 $ が答えになります。

## 样例 #1

### 输入

```
5
3 2 4 1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
10
10 71 84 33 6 47 23 25 52 64```

### 输出

```
36```

## 样例 #3

### 输入

```
7
1 2 3 1000000000 4 5 6```

### 输出

```
999999994```

# 题解

## 作者：Kelin (赞：9)

## 题意

将一个序列 $a$ 划分成连续的四段，使得这四段的和的极差最小.

$4\le n\le 2\times10^5$

## 题解

先求前缀和，于是题目转化成从 $1\sim n-1$ 中选出三个数 $i,j,k$ 使得 $s_i,s_j-s_i,s_k-s_j,s_n-s_k$ 的极差最小.

考虑枚举 $j$ ，那么 $i,k$ 一定是把 $1\sim j-1$ 和 $j+1\sim n$ 划分得最平衡的分界点， 即使得 $|s_j-s_i-s_i|,|s_n-s_k-(s_k-s_j)|$ 最小的 $i,k$ .

因为如果不平衡，那么划分出的两段的和的最小值值一定比平衡状态下的最小值更小，最大值比平衡状态大，从而总体的极差可能会变大.

由于 $j$ 是从小到大枚举的，从而 $s_j-s_i$ 变大、 $s_k-s_j$ 变小，所以最优化划分点 $i,k$ 一定是单调不降的.

时间复杂度 $O(n)$ 

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int n; ll a[N];
int main(){
    scanf("%d",&n);
    ll Ans = LLONG_MAX;
    for (int i = 1; i <= n; ++i) scanf("%d", a + i), a[i] += a[i - 1];
    for (int i = 1, j = 2, k = 3; j < n; ++j) {
        while (i + 1 < j && abs(a[j] - 2 * a[i]) > abs(a[j] - 2 * a[i + 1])) ++i;
        while (k + 1 < n && abs(a[n] + a[j] - 2 * a[k]) > abs(a[n] + a[j] - 2 * a[k + 1])) ++k;
        Ans = min(Ans, max({a[i], a[j] - a[i], a[k] - a[j], a[n] - a[k]}) -
                       min({a[i], a[j] - a[i], a[k] - a[j], a[n] - a[k]}));
    }
    printf("%lld\n", Ans);
    return 0;
}
```

---

## 作者：Hoks (赞：4)

## 前言
[题目链接](https://www.luogu.com.cn/problem/AT_arc100_b)，[个人博客](https://www.luogu.com.cn/blog/Hok/solution-at-arc100-b)内食用可能也许大概会更佳。

~~模拟赛时没切出来。~~
## 思路分析
这题首先发现题目是要我们把一个数列分割成 $4$ 段的最小极差。考虑分成 $4$ 段则有 $3$ 个分割点。

既然是要考虑极差最小，首先枚举最中间的 $j$ 的分割位置，再考虑左右 $i,k$ 的位置。

因为要极差最小那肯定是左边的两段最接近而且右边的两段也最接近的情况，所以这个时候我们就可以求出 $i,k$ 的值。

然后因为 $j$ 的位置是单调递增的， $a_i$ 的值是大于 $0$ 的，所以 $i,k$ 的向右移动是单调的，所以时间复杂度就是 $O(n)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans=1145141919810;
int a[200010];
int read()
{
	char c=getchar();int x=0,f=1;
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read()+a[i-1];
	for(int i=1,j=2,k=3;j<n;j++)
	{
		while(i+1<j&&abs(a[j]-2*a[i])>abs(a[j]-2*a[i+1])) i++;
        while(k+1<n&&abs(a[n]+a[j]-2*a[k])>abs(a[n]+a[j]-2*a[k+1])) k++;
        ans=min(ans,max({a[i],a[j]-a[i],a[k]-a[j],a[n]-a[k]})-min({a[i],a[j]-a[i],a[k]-a[j],a[n]-a[k]}));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：皎月半洒花 (赞：4)

尝试写水题题解以换取贡献分.jpg

znm，长得一脸可三分的样子然而并不可三分，因为很容易知道在这种多峰函数三分本质上和爬山没啥区别。可能会有什么神必的退火或者遗传做法。但是个人感觉这个数据范围似乎不是很允许。

考虑暴力怎么做。尝试去枚举中间的第二段的右端点，这样再去枚举 $a,c,d$ ，复杂度是 $O(n^3)$ 的。

观察题目所给的性质。发现所有数都 $>0$。于是考虑枚举第二段的时候，对于一个与自己极差最小的第一段，由于第二段数一直在增多，所以第一段的右端点下标必然是不降的；对于第三、四段，这个性质同样成立。

于是可以想到枚举第二段，第一段和第三段都变成了 $O(1)$ 。最终复杂度 $O(n)$ 。

```cpp
int n ;
ll ans ;
ll S[4] ;
ll minx ;
ll maxx ;
ll sum[N] ;
ll base[N] ;
 
ll gt(ll x){
    return x < 0 ? -x : x ;
}
void chkmin(ll x){
    minx = x >= minx ? minx : x ;
}
void chkmax(ll x){
    maxx = x >= maxx ? x : maxx ;
}
int main(){
    cin >> n ;
    ans = (1ll << 62) ;
    for (int i = 1 ; i <= n ; ++ i){
        scanf("%lld", &base[i]) ;
        sum[i] = sum[i - 1] + base[i] ;
    }
    int l = 2, r = 4 ;
    S[0] = base[1] ; S[2] = base[3] ;
    S[1] = base[2] ; S[3] = sum[n] - sum[3] ;
    for (int i = 3 ; i <= n ; ++ i){
        while (l < i && gt(S[0] - S[1]) > gt(S[0] + base[l] - S[1] + base[l])){
            S[0] += base[l], S[1] -= base[l], ++ l ;
        }
        while (r <= n && gt(S[3] - S[2]) > gt(S[2] + base[r] - S[3] + base[r])){
            S[2] += base[r], S[3] -= base[r], ++ r ;
        }
        minx = (1ll << 61) ; maxx = -(1ll << 61) ;
        for (int j = 0 ; j <= 3 ; ++ j) chkmin(S[j]), chkmax(S[j]) ;
        ans = min(ans, maxx - minx) ; S[1] += base[i] ; S[2] -= base[i] ;
        //for (int j = 0 ; j <= 3 ; ++ j) cout << S[j] << " " ; puts("") ;
    }
    cout << ans << endl ; return 0 ;
}
```



---

## 作者：_ZML_ (赞：2)

## 题意

这道题是让我们把一段区间分成四个不为空的连续子序列，并算出每个区间的和，最后用四个和的最大值减去最小值，算出最终答案。

## 分析

大家首先想到的肯定是暴力法用三个循环枚举四个区间，对于每一个区间，在单独算和，这样的时间复杂度 $O(n^4)$，肯定会超时。

现在我们进行优化：最后求和的过程我们可以预处理 $1\sim n$ 的前缀和。最后就省去了算区间和的过程，时间复杂度为 $O(n^3)$，还是会超时。

接下来，就是终极优化：方便讲述，定义第一个区间范围为 $1\sim i$；第二个区间范围为 $i\sim j$；第三个区间范围为 $j\sim k$；第四个区间范围为 $k\sim n$。

我们枚举 $j$ 从 $2$ 至 $(n-1)$，那 $i$ 和 $k$ 一定是把 $1\sim (j-1)$，$j\sim n$ 这两个区间分得最均匀点的点。

这种方法的时间复杂度是 $O(n)$ 不会超时。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
long long a[maxn];
long long sum[maxn];
long long mx(long long a,long long b,long long c,long long d){
	long long p=max(a,b);
	long long q=max(c,d);
	return max(p,q);
}
long long mn(long long a,long long b,long long c,long long d){
	long long p=min(a,b);
	long long q=min(c,d);
	return min(p,q);
}
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];
	} 
	
	long long ans=2100000000;
	
	for(int i=1,j=2,k=3;j<n;j++){
		while(i+1<j&&abs(sum[j]-2*sum[i])>abs(sum[j]-2*sum[i+1]))i++;
		while(k+1<n&&abs(sum[n]-2*sum[k]+sum[j])>abs(sum[n]-2*sum[k+1]+sum[j]))k++;
		ans=min(ans,mx(sum[i],sum[j]-sum[i],sum[k]-sum[j],sum[n]-sum[k])-mn(sum[i],sum[j]-sum[i],sum[k]-sum[j],sum[n]-sum[k]));
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：Acerkaio (赞：1)

[题面](https://www.luogu.com.cn/problem/AT4167)
## 思路
用一个前缀和数组先储存数据。  
要求最小化这四段的极差的最小值，即要求**这四段最平衡的状态**咯。  
分四段，即需要三个节点 $i,j,k$，且 $i< j< k$。  
枚举中间节点 $j$（暴力思想体现），即求 $[1,j-1], [j+1,n]$ 最平衡。那么 $i,k$ 一定要把 $\left | \left ( sum_j-sum_i \right ) - sum_i \right |,\left | \left ( sum_n - sum_k \right )  - \left ( sum_k - sum_j \right ) \right | $ 最小化咯（这里有些跳跃，好好理解）。
## CODE
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, sum[1000001], answer = 0;
void find(int &x) {
	x = 0x7fffffff;
	for(int i = 1, j = 2, k = 3; j < n; j++) {
		while((i + 1 < j) && (abs(sum[j] - sum[i] - sum[i]) > abs(sum[j] - sum[i + 1] - sum[i + 1]))) 
		i++;
		while((k + 1 < n) && (abs(sum[n] - sum[k] - sum[k] + sum[j]) > abs(sum[n] - sum[k + 1] - sum[k + 1] + sum[j])))
		k++;
		x = min(x, max(sum[i], max(sum[j] - sum[i], max(sum[k] - sum[j], sum[n] - sum[k]))) - min(sum[i], min(sum[j] - sum[i], min(sum[k] - sum[j], sum[n] - sum[k]))));
	}
}
signed main() {
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		sum[i] = sum[i - 1] + x;
	}
	find(answer);
	cout << answer << '\n';
	return 0;
}
```


---

## 作者：Nightingale_OI (赞：1)

### 大意

给定一个长度为 $ n $ 的数组 $ a $ （ $ n \geq 4 $ ）。

把这个数组分为四段，记录这四段的和分别是 $ p $ ， $ q $ ， $ r $ ， $ s $ 。

求 $ \max\{p,q,r,s\} - \min\{p,q,r,s\} $ 的最小值。

### 思路

先考虑枚举在哪里将这个数组分成两段，将这两段再分别这样：将这段分为差值最小两段，最多有两种情况。

把左边的两种情况和右边的两种情况一一匹配出现四种情况，这就是当前来看可能最优的四种解。

易证如果第二次分为的两段差值不是最小的，差值最小的方案一定不劣。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
#define rcll register const long long
long long a[202020];
long long ans,p1,p2,q1,q2,r1,r2,s1,s2;
long long Min(rcll& x,rcll& y){return x<y?x:y;}
long long Max(rcll& x,rcll& y){return x>y?x:y;}
long long ask(rcll& p,rcll& q,rcll& r,rcll& s){return Max(Max(p,q),Max(r,s))-Min(Min(p,q),Min(r,s));}
void doing(int l,int r,long long& x1,long long& x2,long long& y1,long long& y2){
	int le=l,ri=r,mid;
	while(le<ri){
		mid=(le+ri+1)/2;
		if(a[mid]-a[l-1]<=a[r]-a[mid-1])le=mid;
		else ri=mid-1;
	}
	x1=a[le]-a[l-1];y1=a[r]-a[le];
	++le;
	x2=a[le]-a[l-1];y2=a[r]-a[le];
}
int main(){
	cin>>n;
	f(i,1,n)scanf("%lld",&a[i]);
	f(i,1,n)a[i]+=a[i-1];
	ans=a[n];
	f(i,2,n-2){
		doing(1,i,p1,p2,q1,q2);
		doing(i+1,n,r1,r2,s1,s2);
		ans=Min(ans,Min(ask(p1,q1,r1,s1),ask(p1,q1,r2,s2)));
		ans=Min(ans,Min(ask(p2,q2,r1,s1),ask(p2,q2,r2,s2)));
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：MVP_Harry (赞：1)

写一波题解，~~造福后人。~~

首先想到的算法肯定就是枚举三个点，但很明显复杂度不对。此时，我们可以换一种思路：先枚举中间那个节点，此时分为两段，$L$和$R$。然后，我们需要把$L$分为$L_1, L_2$（$R$同理）。我们发现，不论$R$怎么分，我们肯定要让$|L_1 - L_2|$尽量小，$R$同理。由于$A_i \ge 1$，故它们的和递增，可以用双指针$O(n)$解决（我采用的是用双指针表示$L$和$R$的“中点”）。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i, m, n) for(ll i = m; i <= n; i++)

const ll maxn = 2e5 + 5;

ll a[maxn], sum[maxn], N; 

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0); 
    cin >> N;
    rep(i, 1, N) cin >> a[i], sum[i] = sum[i - 1] + a[i];
    ll ans = 1e18; 
    //分别表示为L的“中点”，R的“中点”，以及四段和
    ll mid1 = 1, mid2 = 2, first_sum, second_sum, third_sum, fourth_sum; 
    for (ll i = 2; i <= N - 2; i++) {
    	// 1 - i is the first half, while i + 1 - N is the second half;
    	first_sum = sum[mid1], second_sum = sum[i] - sum[mid1]; 
    	ll temp = abs(first_sum - second_sum), temp_mid = mid1; 
    	// 1 ~ mid is first_sum, mid + 1 ~ i is second_sum; want to evenly distribute sum1 and sum2; 
    	for (ll l = temp_mid + 1; l <= i - 1; l++) {
    		first_sum += a[l];
    		second_sum -= a[l]; 
    		if (abs(first_sum - second_sum) <= temp) temp = abs(first_sum - second_sum), mid1 = l; 
    		else break; 
    	} 
    	third_sum = sum[mid2] - sum[i], fourth_sum = sum[N] - sum[mid2]; 
    	temp = abs(third_sum - fourth_sum), temp_mid = mid2;
    	for (ll r = temp_mid + 1; r <= N - 1; r++) {
    		third_sum += a[r], fourth_sum -= a[r]; 
    		if (abs(third_sum - fourth_sum) <= temp) temp = abs(third_sum - fourth_sum), mid2 = r;
    		else break;
    	}  
    	ll minn = min(min(sum[mid1], sum[i] - sum[mid1]), min(sum[mid2] - sum[i], sum[N] - sum[mid2])); 
    	ll maxx = max(max(sum[mid1], sum[i] - sum[mid1]), max(sum[mid2] - sum[i], sum[N] - sum[mid2])); 
    	ans = min(ans, maxx - minn); 
    }
    cout << ans << endl; 
    return 0; 
}
```

---

## 作者：AirQwQ (赞：1)

## 分析

首先先放一个朴素的 $O(n^3)$ 的暴力，思路是用 ```i,j,k``` 把序列分成 $4$ 份（还是要用到基本的前缀和）。

```cpp
int minn=9e18;
for(int i=1;i<n;i++)
	for(int j=i+1;j<n;j++)
		for(int k=j+1;k<n;k++){
			int a1=sum[i]-sum[0];
			int b1=sum[j]-sum[i];
			int c1=sum[k]-sum[j];
			int d1=sum[n]-sum[k];
			int maxx=max(max(a1,b1),max(c1,d1));
			int minx=min(min(a1,b1),min(c1,d1));
			minn=min(minn,(maxx-minx));
		}
cout<<minn;

```

显然会 T 的很惨，考虑优化。


- 观察发现，当我们确定中间的 ```j``` 时， ```i,k``` 就能够确定最优解。

- 注意到题中 $n$ 中的范围，很容易想到二分查找。

- 所以，分别找前一半平分的位置，和后一半平分的位置即可。

- 因为大概率数据不能正好平分，所以要分为前大于后，后大于前两种，排列组合可知，共 $4$ 种。

这样我们的时间复杂度就降低到 $O(n \log n)$ 了，可以通过本题。

此外，当 ```j``` 递增时，```i,k``` 也是单调递增的，所以可以用类似于双指针的方法优化到 $O(n)$ 同样可以通过，其他大佬讲的很多了，不再详细说了。

~~AC 代码就先不放了。~~

---

