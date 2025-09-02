# [ABC062D] 3N Numbers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc062/tasks/arc074_b

$ N $ を $ 1 $ 以上の整数とします。

長さ $ 3N $ の数列 $ a\ =\ (a_1,\ a_2,\ ...,\ a_{3N}) $ があります。 すぬけ君は、$ a $ からちょうど $ N $ 個の要素を取り除き、残った $ 2N $ 個の要素を元の順序で並べ、長さ $ 2N $ の数列 $ a' $ を作ろうとしています。 このとき、$ a' $ のスコアを $ (a'\ の前半\ N\ 要素の総和)\ -\ (a'\ の後半\ N\ 要素の総和) $ と定義します。

$ a' $ のスコアの最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ <\ =\ N\ <\ =\ 10^5 $
- $ a_i $ は整数である。
- $ 1\ <\ =\ a_i\ <\ =\ 10^9 $

### 部分点

- $ 300 $ 点分のテストケースでは、$ N\ <\ =\ 1,000 $ が成り立つ。

### Sample Explanation 1

$ a_2 $, $ a_6 $ を取り除くと、$ a'\ =\ (3,\ 4,\ 1,\ 5) $ となり、スコアは $ (3\ +\ 4)\ -\ (1\ +\ 5)\ =\ 1 $ となります。

### Sample Explanation 2

例えば、$ a_1 $ を取り除くと、$ a'\ =\ (2,\ 3) $ となり、スコアは $ 2\ -\ 3\ =\ -1 $ となります。

### Sample Explanation 3

例えば、$ a_2 $, $ a_3 $, $ a_9 $ を取り除くと、$ a'\ =\ (8,\ 7,\ 4,\ 6,\ 5,\ 3) $ となり、スコアは $ (8\ +\ 7\ +\ 4)\ -\ (6\ +\ 5\ +\ 3)\ =\ 5 $ となります。

## 样例 #1

### 输入

```
2
3 1 4 1 5 9```

### 输出

```
1```

## 样例 #2

### 输入

```
1
1 2 3```

### 输出

```
-1```

## 样例 #3

### 输入

```
3
8 2 2 7 4 6 5 3 8```

### 输出

```
5```

# 题解

## 作者：liyichun001 (赞：6)

思路：
删除 n 个数后，剩下的 2n 个数顺序不变，由于这 2n 个数的分界点一定是在 n~2n 这 n 个数之间，因此可以对前 n 个数、后 n 个数分别求和，使用一个优先队列来维护最大和，再用一个优先队列来维护最小和。
代码如下：
```cpp
#include<bits/stdc++.h>
#define LL long long
const int N = 1000000+5;
using namespace std;

LL a[N];
LL before[N],last[N];
int main() {
    int n;
    scanf("%d",&n);

    LL maxSum=0,minSum=0;
    priority_queue<LL> minSumQ;
    priority_queue<LL, vector<LL>, greater<LL> > maxSumQ;
    for(int i=1;i<=3*n;i++){
        scanf("%d",&a[i]);
        if(i<=n){
            maxSum+=a[i];
            maxSumQ.push(a[i]);
        }
        else if(i>2*n){
            minSum+=a[i];
            minSumQ.push(a[i]);
        }
    }

    before[n]=maxSum;
    for(int i=n+1;i<=2*n;i++) {
        LL temp=maxSumQ.top();
        if(temp<a[i]){
            maxSum+=a[i]-temp;
            maxSumQ.pop();
            maxSumQ.push(a[i]);
        }
        before[i]=maxSum;
    }

    last[2*n]=minSum;
    for(int i=2*n-1;i>=n;i--){
        LL temp=minSumQ.top();
        if(temp>a[i+1]){
            minSum+=a[i+1]-temp;
            minSumQ.pop();
            minSumQ.push(a[i+1]);
        }
        last[i]=minSum;
    }

    LL res=before[n]-last[n];
    for(int i=n+1;i<=2*n;i++)
        res=max(res,before[i]-last[i]);
    printf("%lld\n",res);

    return 0;
}

---

## 作者：cjh_trailblazer (赞：1)

[原题面](https://www.luogu.com.cn/problem/AT_arc074_b)
## 题目分析：
注意到求解前 $n$ 个元素与后 $n$ 个元素之差的最大值，且序列顺序不可变。  
因此在长度为 $3n$ 的序列中需要动态维护前 $n$ 大与后 $n$ 小的值，考虑开两个优先队列分别维护。  

详细请看代码注释。
## 代码如下：
```cpp
#include<bits/stdc++.h>
#define mihoyo freopen
#define starrail main
#define int long long//注意 
#define lowbit(x)  (x&(-x))
using namespace std;
inline int read(){
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=3e5+10;
int n,a[N],ans=0xefefefefefefefef/*极小值，不懂请自行百度*/,f[N],g[N];
int sum=0,maxx,minn;
priority_queue<int>q1;//大根堆用 g[N] 维护后 n 小值 
priority_queue<int,vector<int>,greater<int>>q2;//小根堆用 f[N] 维护前 n 大值 
signed starrail()
{
	n=read();
	for(int i=1;i<=3*n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++){
		sum+=a[i];
		q2.push(a[i]);
	}
	f[n]=sum;
	for(int i=n+1;i<=3*n;i++){
		q2.push(a[i]); sum+=a[i];
		minn=q2.top(); q2.pop();
		sum-=minn;//去除后续最小值，保证最大。 
		f[i]=sum;
	}
	sum=0;
	for(int i=3*n;i>=2*n+1;i--){
		q1.push(a[i]);
		sum+=a[i];
	}
	g[2*n+1]=sum;
	for(int i=2*n;i>=1;i--){
		q1.push(a[i]); sum+=a[i];
		maxx=q1.top();
		sum-=maxx;//去除后续最大值，保证最小。
		q1.pop();
		g[i]=sum;
	}
	for(int i=n;i<=2*n;i++)//前 f 与 后 g 分界 
		ans=max(ans,f[i]-g[i+1]);
	write(ans);
	return 0;
}

//划一刀
//前面n个最大值-后面n个最小值
//前18，后12
//前10大 后10小
// 
```

---

## 作者：ruik (赞：0)

### 题意
给你一个大小为 $3 \times n$ 数组，要你找到一位置 $i(1 \le i \le 3 \times n)$ 将它分为两个数组，并在两个数组中分别选取 $n$ 个数并分别求和，使得两数组和的差最大。
### 思路
由于最后求和的两个数组不能有重合部分，所以我们只需要对所有的 $i(n \le i \le 2 \times n)$ 进行枚举，取最大的值即可为什么为 $(n \le i \le 2 \times n)$？因为两个数组都必须至少有 $n$ 个数。

那对于一个 $i$，如何求出它两边数组差的最大值呢？这我们就需要用到**优先队列**了。优先队列总的说就是一种可以对集合中的数求最小或最大的工具，具体用法可以自行查阅。总之，我们先将 $n$ 个数放入优先队列，然后在便利的同时将优先队列中更小的数去除，加入更大的数来维持优先队列中存的是集合中的最大的 $n$ 个数。
### code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[300200],f[300200],sum[300200],m=-1e18;
priority_queue<long long>q; 
priority_queue<long long>p; 
int main(){
    scanf("%lld",&n);
    for(int i=1;i<=3*n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++){
    	q.push(-a[i]);
    	f[i]=f[i-1]+a[i];
	}
	for(int i=n+1;i<=2*n;i++){
		f[i]=f[i-1];
		if(a[i]>-q.top()){
			f[i]=f[i-1]+q.top()+a[i];
			q.pop();
			q.push(-a[i]);
		}
	}
	for(int i=3*n;i>2*n;i--){
		sum[2*n+1]+=a[i];
		p.push(a[i]);
	}
	for(int i=2*n;i>=n;i--){
		if(a[i]<p.top()){
			sum[i]=sum[i+1]-p.top()+a[i];
			p.pop();
			p.push(a[i]);
		}
		else sum[i]=sum[i+1];
		m=max(m,f[i]-sum[i+1]);
	}
	cout<<m;
    return 0;
}
```

---

## 作者：Adam1101 (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_arc074_b)

### 题意简述
给定一个有 $ 3n $ 个整数的序列 $ a $，让你从中删除 $ n $ 个数，使得剩下的 $ 2n $ 个数中前 $ \sum_{i = 1}^n a_i - \sum_{i = n + 1}^{2n} a_i $ 最大。

### 思路
我们可以枚举一个分割点，该点的范围是 $ [n + 1, 2n + 1] $，假设分割点为 $ k $，那问题就转化为求在第 $ 1 $ 至 $ k - 1 $ 个数中求出最大的 $ n $ 个数的和，减去在第 $ k $ 至 $ 3n $ 个数中求出最小的 $ n $ 个数的和。记 $ maxn_k $ 为第 $ 1 $ 至 $ k $ 个数中最大的 $ n $ 个数的和，$ minn_k $ 为第 $ k $ 至 $ 3n $ 个数中最小的 $ n $ 个数的和，那么问题就变成了求 $ maxn_k - minn_k $ 的最大值。

对于 $ 1 \le i \le n $，显然 $ maxn_i = \sum_{j = 1} ^ i a_j $，而对于 $ 2n + 1 \le i \le 3n $，显然 $ minn_i = \sum_{j = i} ^ {3n} a_j $。

对于其他的 $ i $，我们可以用一个小根堆维护前 $ i - 1 $ 个数中最小的数，并把它替换为它和 $ a_i $ 中更大的值，同时更新 $ maxn_i $，这样可以保证 $ maxn_i $ 始终是前 $ i $ 个数中最大的 $ n $ 个数的和。$ minn_i $ 同理。

### 复杂度分析
时间复杂度：$ O(n \log n) $。

空间复杂度：$ O(n) $。

### 代码实现
```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long

int a[300010];
priority_queue<int, vector<int>, greater<int> > q1; //小根堆
priority_queue<int> q2; //大根堆
int maxn[300010];
int minn[300010];

signed main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n * 3; i++) {
        cin >> a[i];
    }
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += a[i];
        maxn[i] = sum;
        q1.push(a[i]);
    }
    for (int i = n + 1; i <= n * 3; i++) { //维护前 i 个数中最大的 n 个数的和
        if (a[i] > q1.top()) {
            sum += a[i] - q1.top();
            q1.pop();
            q1.push(a[i]);
        }
        maxn[i] = sum;
    }
    sum = 0;
    for (int i = n * 3; i >= n * 2 + 1; i--) {
        sum += a[i];
        minn[i] = sum;
        q2.push(a[i]);
    }
    for (int i = n * 2; i >= 1; i--) { //维护第 i 至 3n 个数中最小的 n 个数的和
        if (a[i] < q2.top()) {
            sum += a[i] - q2.top();
            q2.pop();
            q2.push(a[i]);
        }
        minn[i] = sum;
    }
    int ans = -1e18;
    for (int i = n + 1; i <= n * 2 + 1; i++) { //枚举分割点
        ans = max(ans, maxn[i - 1] - minn[i]);
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：aCssen (赞：0)

### Solution
最终序列长度为 $2N$，所以就是前 $N$ 个数减后 $N$ 个数。

为使这个数最大，所以前 $N$ 个数的和要尽量大，后 $N$ 个数的和要尽量小。

枚举 $i$ 作为前 $N$ 个数的结束位置，那么此时我们就要前 $i$ 个数中前 $N$ 大的数的和。记这个数为 $L_i$，如果没有 $N$ 个数就令 $L_i =- \infty$。由于 $N$ 固定，所以只需要使用一个小根堆维护即可。这里使用小根堆的原因是我们要留下大的，所以就要丢掉小的。

类似求出 $R_i$，答案即为 $\max(L_i-R_{i+1})$。

### Code

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout);
using namespace std;
typedef long long ll;
namespace FastIO{
	template<typename T=int> T read(){
		T x=0;int f=1;char c=getchar();
		while(!isdigit(c)){if(c=='-') f=~f+1;c=getchar();}
		while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
		return x*f;
	}
	template<typename T> void write(T x){
		if(x<0){putchar('-');x=-x;}
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	template<typename T> void Write(T x,char c='\n'){write(x);putchar(c);}
}
using namespace FastIO;
const int maxn=3e5+5;
priority_queue<int,vector<int>,greater<int> >p;
priority_queue<int>q;
bool Cl[maxn],Cr[maxn];
ll L[maxn],R[maxn];
int a[maxn];
int main(){
	int n=read();
	for(int i=1;i<=3*n;i++) a[i]=read();
	ll s=0;
	for(int i=1;i<=3*n;i++){
		p.push(a[i]);s+=a[i];
		while(p.size()>n) s-=p.top(),p.pop();
		if(p.size()==n) L[i]=s,Cl[i]=true;
	}
	s=0;
	for(int i=3*n;i>=1;i--){
		q.push(a[i]);s+=a[i];
		while(q.size()>n) s-=q.top(),q.pop();
		if(q.size()==n) R[i]=s,Cr[i]=true;
	}
	ll ans=-9e18;
	for(int i=1;i<=3*n;i++)
		if(Cr[i+1]&&Cl[i]) ans=max(ans,L[i]-R[i+1]);
	write(ans);
	return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

[优先队列](https://blog.csdn.net/weixin_47257473/article/details/129262572)

我们可以发现，一定有一个 $K$，删除 $N$ 个数后的数组，前 $N$ 个数是原数组的前 $K$ 个数，后 $N$ 个数是原数组的后 $N-K$ 个数。而且 $N \le K \le 2N$。

那我们可以枚举 $K$，并用优先队列维护 $f$ 和 $g$ 数组。

$f_i$ 表示 前 $i$ 个数中最大的 $N$ 个数之和，其中 $i \ge N$，$g_i$ 表示后 $3N-i$ 个数中最小的 $N$ 个数之和，其中 $i \le 2N+1$。

最后答案就是 $f_i-g_{i+1}$ 的最大值，其中 $N \le i \le 2N$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[300010];
long long f[300010],g[300010],sum,ans=-10000000000000000;//ans初始化成-(10^16),避免答案为负 
int main(){
    scanf("%d",&n);
    for(int w=1;w<=3*n;w++)scanf("%d",&a[w]);
    priority_queue<int>q1;//q1是求g的优先队列 
    priority_queue<int, vector<int>, greater<int> >q2;//q2是求f的优先队列 
    for(int w=1;w<=n;w++)q2.push(a[w]),sum+=a[w];
    f[n]=sum;
    for(int w=n+1;w<=3*n;w++){//f数组 
    	q2.push(a[w]),sum+=a[w];
    	int t=q2.top();
    	sum-=t,q2.pop(),f[w]=sum;
	}
	sum=0;
	for(int w=3*n;w>2*n;w--)q1.push(a[w]),sum+=a[w];
	g[2*n+1]=sum;
	for(int w=2*n;w;w--){//g数组 
		q1.push(a[w]),sum+=a[w];
		int t=q1.top();
		sum-=t,q1.pop(),g[w]=sum;
	}
	for(int w=n;w<=2*n;w++)ans=max(ans,f[w]-g[w+1]);//N<=k<=2N,max(前w个最大的N个之和减后3N-w个最小的N个之和)就是答案 
	printf("%lld",ans);//输出，别忘了long long 
    return 0;
}
```


---

## 作者：abensyl (赞：0)

原题：[ABC062D 3N Numbers](https://www.luogu.com.cn/problem/AT_arc074_b)。

非常好的一道题。

## 思路

本体我们可以把整个数列划分成两部分，取第一部分（前一段）前 $n$ 大的值，第二部分（后一段）前 $n$ 小的值。这样对两段分别加和，然后将两端的和作差即可。

很容易想到枚举分界线，对分界线两边的数字分别取最大值，时间复杂度 $O(n^2\log n)$，不可取。

枚举分界线的操作没有二分的性质，二分也不可取。

那么如果我们能够与处理好每个分界线所对应的前后两短的最大最小值，那么问题就迎刃而解了。

很显而易见，我们可以维护一个优先队列，最大值即为整个优先队列里前 $n$ 大的值，维护最小值亦然，便于处理完成了。

代码整体时间复杂度：$O(n \log n)$。

注意：**不开 long long 见祖宗！**

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 3e5 + 2;

int a[N], q[N], p[N];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  priority_queue<int, vector<int>, greater<int>> pq;
  int sum = 0;
  for (int i = 1; i <= 3 * n; ++i) {
    cin >> a[i];
    pq.push(a[i]), sum += a[i];
    while (pq.size() > n) sum -= pq.top(), pq.pop();
    q[i] = sum;
  }
  priority_queue<int> qp;
  sum = 0;
  for (int i = 3 * n; i >= 1; --i) {
    qp.push(a[i]), sum += a[i];
    while (qp.size() > n) sum -= qp.top(), qp.pop();
    p[i] = sum;
  }
  int res = -1e18;
  for (int i = n; i <= n * 2; ++i) res = max(res, q[i] - p[i + 1]);
  cout << res << '\n';
  return 0;
}
```

---

## 作者：TB_TOP (赞：0)

## 题面翻译

给一个长度为 $3 \times N$ 的数组 $a=(a_1,a_2,...,a_n)$，要求删去其中 $N$ 个数使得剩余的 $2 \times N$ 个数中前 $N$ 个数之和与后 $N$ 个数之和的差最大。

## 思路
1. 删除 $N$个数后，剩下的 $2 \times N$ 个数顺序不变，
2. 由于这 $2 \times N$ 个数的分界点一定是在 $N$ 到 $2 \times N$ 这 $N$ 个数之间，因此可以对前 $N$ 个数、后 $N$ 个数分别求和
## 具体实现
使用一个优先队列来维护最大和，再用一个优先队列来维护最小和。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 10;
int n;
int a[N], sum1[N], sum2[N];
priority_queue<int> q1, q2;
signed main() {
	cin >> n;
	int len = 3 * n; 
	for (int i = 1; i <= len; i++) 
		scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) {
		sum1[n] += a[i];
		q1.push(-a[i]);
	}
	for (int i = n + 1; i <= len - n; i++) {
		 int p = -q1.top();
		 sum1[i] = sum1[i - 1];
		 if (p < a[i]) {
		 	sum1[i] = sum1[i] - p + a[i];
		 	q1.pop();
		 	q1.push(-a[i]);
		 }
	} 
	for (int i = len; i > len - n; i--) {
		sum2[len - n + 1] += a[i];
		q2.push(a[i]);
	}
	for (int i = len - n; i > n; i--) {
		int p = q2.top();
		sum2[i] = sum2[i + 1];
		 if (p > a[i]) {
		 	sum2[i] = sum2[i] - p + a[i];
		 	q2.pop();
		 	q2.push(a[i]);
		 }
	}
	int ans = -1e9;
	for (int i = n; i <= len - n; i++) {
		ans = max(ans, sum1[i] - sum2[i + 1]);
	}
	cout << ans << endl;
	return 0;
} 


```


---

