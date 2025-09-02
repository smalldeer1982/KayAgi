# [ARC079E] Decrease (Judge ver.)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc079/tasks/arc079_c

長さ $ N $ の非負整数列 $ a_i $ に対し、数列の最大値が $ N-1 $ 以下になるまで以下の操作を繰り返し行うことを考えます。なお、この操作はD問題で考える操作と同一です。

- 数列のうち最も大きい要素を求める、複数ある場合はどれか $ 1 $ つ選ぶ。この要素の値を $ N $ 減らす。これ以外の要素の値を $ 1 $ 増やす。

なお、この操作を行い続けると、いつかは数列の最大値が $ N-1 $ 以下になることが証明できます。

ここで、数列 $ a_i $ が与えられるので、何回操作を行うことになるかを求めてください。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 50 $
- $ 0\ ≦\ a_i\ ≦\ 10^{16}\ +\ 1000 $

## 样例 #1

### 输入

```
4
3 3 3 3```

### 输出

```
0```

## 样例 #2

### 输入

```
3
1 0 3```

### 输出

```
1```

## 样例 #3

### 输入

```
2
2 2```

### 输出

```
2```

## 样例 #4

### 输入

```
7
27 0 0 0 0 0 0```

### 输出

```
3```

## 样例 #5

### 输入

```
10
1000 193 256 777 0 1 1192 1234567891011 48 425```

### 输出

```
1234567894848```

# 题解

## 作者：CQ_Bab (赞：3)

# 前言
考完一看蓝的，顿时慌了，在看几眼发现是远古题，那就放心了。
# 思路
我们其实直接用暴力即可，毕竟 $n\leq 50$。那么我们每次用一个大根堆，存下当时每一个数，若此时的堆顶都小于 $n$ 就不用再变了。那么我们没记直接计算出将堆顶变成小于 $n$ 的次数，然后将所有数都加上一个次数即可。
# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
#define rep1(i,x,y) for(ri i=x;i>=y;i--)
#define il inline
#define fire signed
#define pai(a,x,y) sort(a+x,a+y+1)
using namespace std ;
il int qmi(int a,int b) {
	int res=1;
	while(b) {
		if(b&1) res=(res*a);
		a=a*a;
		b>>=1;
	}
	return res;
}
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int a,n;
priority_queue<int>q,p;
fire main() {
	cin>>n;
	rep(i,1,n) cin>>a,q.push(a);
	int res=0;
	while(q.top()>=n) {
		int x=q.top();
		q.pop();
		int sum=x/n;
		res+=x/n;
		while(q.size()) {
			int x=q.top();
			p.push(x+sum);
			q.pop();
		}
		while(p.size()) {
			q.push(p.top());
			p.pop();
		}
		q.push(x%n);
	}
	print(res);
	return false;
}
/*
10
1000 193 256 777 0 1 1192 1234567891011 48 425
*/ 
```

---

## 作者：Krimson (赞：3)

上一题构造,这题写SPJ就离谱  



------------
没什么技巧,纯模拟就行了,不过要加一点优化  
对于一个数$a_i$,不论它是第几大,只要$a_i>=n$,最后肯定要对它操作的  
所以把减法的操作改为除法就好了   
直接放代码方便理解
```cpp
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il int max(const int &a,const int &b){return a>b?a:b;}
il int min(const int &a,const int &b){return a<b?a:b;}
int n;
ll K;
const int MAXN=55;
ll a[MAXN],res;
bool flag=true;
/*
%n +a[i]/n
*/
int main(){
    n=read();
    for(ri i=1;i<=n;++i){
        a[i]=read();
    }
    while(flag){
        flag=false;
        for(ri i=1;i<=n;++i){
            a[i]+=res;
            if(a[i]>=n){
                ll use=a[i]/n;
                K+=use;
                res+=use;
                a[i]%=n;
                for(ri j=1;j<i;++j){
                    a[j]+=use;
                }
                flag=true;
            }
        }
        res=0;
    }
    print(K);
    return 0;
}
```

接下来是复杂度分析  
设当前序列中最大的数为$x$  
对于每一个数$a_i$,它在$mod\ n$之后最多会被加上$\frac{n-1}{n}x$  
也就是说每一轮操作之后都会缩小到原来的$\frac{n-1}{n}$,当$n=50$的时候即每一轮操作都会缩小到原来的$0.98$  
每次操作的复杂度是$O(n^2)$~~可以用差分搞到O(n)~~  
然后一共要进行$log_{0.98}^{\frac{x}{n}}$次  
所以复杂度是$O(n^2log_{0.98}^{\frac{n}{x}})$  
看上去好像很大,实际上当$n=50$,$x=1e16$的时候 
上式也才为$4480000$左右,完全是能过的,并且卡不满

---

## 作者：封禁用户 (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/AT_arc079_c)。

这道题目的思路是通过循环，每次选择当前数组中的最大值来进行操作，直到所有的数都小于 $n$。

由此我们可以得到暴力代码：

```
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long
 main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int count = 0;
    while (true) {
        int max_val = *max_element(arr.begin(), arr.end());
        if (max_val < n) {
            break;// 如果最大值小于 n，退出循环
        }
        int max_idx = distance(arr.begin(), find(arr.begin(), arr.end(), max_val)); // 找到最大值
        arr[max_idx] -= n;
        for (int i = 0; i < n; i++) {
            if (i != max_idx) {
                arr[i] += 1;
            }
        }
        count++; // 操作次数加一
    }
    cout << count << endl;
    return 0;
}
```

可是放眼看一下数据：

 $ 2\ \le\ N\ \le\ 50 $
 
 $ 0\ \le\ a_i\ \le\ 10^{16}\ +\ 1000 $

这 $n$ 小的可怕， $a_i$ 却大到可怕。

这该怎么办呢？

正解：

咱们先将数组倒序排序，则 $a_0$ 为最大值，如果 $a_0$ 小于 $n$ 则能说明整个数组的数都小于 $n$ ，所以直接结束即可。（没必要计算，节省时间）

之后我们可以运用到一个公式：

$(x -(n-1)-1)\div n+1$

这个公式是用来计算操作次数的。

设 $a_0$ 是 $x$,先计算 $a_0$ 与 $n-1$ 相差多少，再整除 $n$ 最后加 $1$ （防止除不通）。

之后累加操作次数 。

最后在对数组 $a$ 进行操作，将选择的最大值 $a_0$ 减去 $k \times n$，然后将其他元素都增加 $k$。

通过此操作来使得最大值与其他元素的差保持不变。

代码：

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed  main() {
	int n;
	cin >> n;
	int a[51] = {0};
	for(int i = 0; i< n ;i++) {
		cin>>  a[i];
	}
	int ans = 0;
	while(true) {
		sort(a,a+n,greater<int>());
	//	cout << a[0] << " ";
		if(a[0] <= n - 1) break;//不用更改
		
		int k = (a[0] - (n - 1) - 1 )/ n + 1;
		cout << k << " ";
		ans += k;
		a[0] -= k * n;
		for(int i =  1 ;i < n;i++) {
			a[i] +=k;
		}
	}
	cout << ans << endl;
}
```



---

## 作者：Ferdina_zcjb (赞：1)

这道题有种贪心的感觉？其实以数学为主。

首先，考虑使用顺序表 $temp$ 存储数列，使用下标进行访问。

假设：$temp_i$ 为顺序表中最大值，$temp_j$ 为最小值。

暴力很简单，只需要每次将顺序表排序，在进行一次一次模拟即可。

但这样会 TLE 那该如何优化呢？

我们简单证明一件东西：

设 $temp_i = 4n,temp_j = 3n$。

当进行一次操作后， $temp_i = 3n,temp_j = 3n+1$ 则最大值成了 $3n+1$。但在进行一次操作后最大值又是 $temp_i$。说明这个变化存在轮换性。

根据上述轮换性，可以直接将 $temp_i$ 减为 $temp_i \operatorname{mod} n$，则其他数都加 $\lfloor \frac{temp_i}{n}\rfloor$。

通过上述，可以得到以下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,temp[100],ans;
signed main(){
    cin >> n;
    for(int i = 0;i < n;++i)cin >> temp[i];
    for(;;){
        sort(temp,temp+n,greater<int>());//排序，得到数列最大值。
        int x = temp[0];
        if(x < n)break;//如果满足题意，退出。
        int val = x/n;//floor(temp[i]/n)。
        temp[0] %= n;/*以下为变换操作。*/
        ans += val;
        for(int i = 1;i < n;++i)temp[i] += val;
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：lanos212 (赞：1)

这题一眼二分 qwq。

但是**这题如果纯二分是错的**，因为这题答案是否有解并不存在单调性。

比如说样例一，不操作是可行的，而操作了 $1$ 次却是不可行的。

可能数据太水，导致部分二分写法可以通过。

但是即便这样，我们也是可以进行二分的，考虑到把每 $N$ 个答案都组成一块，然后对块进行二分，每块内是否有解是存在单调性的。

下面给出证明：

首先可以发现，如果对于每个点都进行一次操作，共 $N$ 次操作后，所有数都会减少 $1$。那么如果 $x$ 次操作是有解的，那么 $x+N$ 次操作必然是有解的。所以假设最优解为 $y$，那么 $y+N,y+2N,\dots$ 必然有解，所以对于每 $N$ 个答案组成一块，在最优解前的块都是无解的，在最优解所在块及以后的块都是有解的。

所以先二分块，然后对于块内每一个答案暴力判断是否有解，最后从答案块内挑出最优解即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[51],sum,tmp,las=5e18;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;++i) cin>>a[i];
	long long l=0,r=2e16;
	while (l<r){
		long long mid=(l+r)/2*n; tmp=0;
		for (long long md=mid;md<mid+n;++md){
			sum=0;
			for (int i=1;i<=n;++i) sum+=(a[i]+md+1)/(n+1);
			if (sum<=md){tmp=md; las=min(las,md); break;}
		}
		if (tmp) r=mid/n;
		else l=mid/n+1;
	}
	cout<<las;
	return 0;
}
```

---

## 作者：迟暮天复明 (赞：1)

[题面](https://atcoder.jp/contests/arc079/tasks/arc079_c)

[没说更好的阅读体验](https://www.cnblogs.com/1358id/p/16226062.html)

Description:

给你 $n$ 个整数 $a_i$。每次可以选择一个数，进行以下操作：

+ 将该数减小 $n$。
+ 将其他数增加 $1$。

问至少几次操作才能让所有数均 $<n$。

-----
对于每次操作给他换个方式描述，变为：
+ 将该数减小 $n+1$。
+ 将所有数增加 $1$。


这样的话，在已知操作次数为 $k$ 的时候，我们可以算出第 $i$ 个数要减少的次数为 $\dfrac{a_i-n+k+1}{n+1}$。将每个数的操作次数加起来，和最初的 $k$ 进行比较，我们就能判断出操作次数为 $k$ 是否成立。

这明显是一个 $\text{check}$ 函数，很快想到二分 $k$。然后这个题目就做完了。

[代码](https://paste.ubuntu.com/p/tBHSFPbfSH/)

---

## 作者：251Sec (赞：0)

本题最重要的观察是：操作的顺序不影响答案，我们实际上可以把减最大值那个限制改成任意减，而答案不变。

于是我们每次找到最大的数，贪心地一次性对它作若干次操作使得它 $<n$ 即可通过。

对这个做法进行复杂度分析，设所有数和为 $S$，则最大值至少为 $\frac{S}{n}$，则操作次数至少为 $\frac{S}{n^2}$，每次操作至少使得 $S$ 减少 $1$，则一次操作至少使得 $S \gets \frac{n^2-1}{n^2}S$，那么操作次数一定不超过 $\log_{\frac{n^2}{n^2-1}}S=\frac{\ln S}{\ln(1+\frac{1}{n^2-1})}$，对下面的 $\ln$ 泰勒展开取第一项可以得到操作次数是 $O(n^2\log S)$ 的。每次操作要花费 $O(n)$ 的时间模拟。所以总复杂度为 $O(n^3 \log S)$。

---

## 作者：WaterSun (赞：0)

# 思路

首先，对于每一次操作，我们可以先找到最大值，然后对其操作。

这样，我们可以得到单次操作时间复杂度 $\Theta(n)$ 的代码，因为 $n$ 很小，所以这道题时间复杂度的瓶颈在于操作的数量。

那么，我们想到每一次找到最大值时，直接将其减到小于 $n$。

但是这样可能有一种问题，就是最大值减了一定次数，有可能就不是最大值了。

不难发现，对于本题的减的顺序对答案无影响，因为一个数要减到 $n$ 以下无论顺序需要的次数都一样。

因此，我们直接将最大值减到 $n$ 下次即可。

时间复杂度 $\Theta(n^2)$ 再多一点常数。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 55,inf = 1e18 + 10;
int n,ans;
int arr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline int up(int a,int b){
	if (a % b == 0) return a / b;
	return a / b + 1;
}

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	while (1){
		int Max = -inf,id = 0;
		for (re int i = 1;i <= n;i++){
			if (Max < arr[i]){
				Max = arr[i];
				id = i;
			}
		}
		if (Max < n) break;
		int cnt = up(Max - (n - 1),n);
		ans += cnt;
		arr[id] -= cnt * n;
		for (re int i = 1;i <= n;i++){
			if (i == id) continue;
			arr[i] += cnt;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

