# Cirno and Operations

## 题目描述

Cirno 有一个长度为 $n$ 的序列 $a$ 。她可以执行以下两种操作中的任意一种（可能零次），除非当前序列 $a$ 的长度为 $1$：

- 反转序列。严格来说，序列 $[a_1, a_2, \ldots, a_n]$ 变为 $[a_n, a_{n-1}, \ldots, a_1]$。
- 将序列替换为其差分序列。严格来说，序列 $[a_1, a_2, \ldots, a_n]$ 变为 $[a_2 - a_1, a_3 - a_2, \ldots, a_n - a_{n-1}]$。

在所有操作之后，找到序列 $a$ 的元素和的最大值。

## 说明/提示

在第一个测试用例中，Cirno 无法进行任何操作，因此答案是 $-1000$。

在第二个测试用例中，Cirno 首先反转序列，然后将其替换为差分序列：$[5, -3] \to [-3, 5] \to [8]$。可以证明这样能使总和最大化，因此答案是 $8$。

在第三个测试用例中，Cirno 可以选择不进行任何操作，因此答案是 $1001$。

## 样例 #1

### 输入

```
5
1
-1000
2
5 -3
2
1000 1
9
9 7 9 -9 9 -8 7 -8 9
11
678 201 340 444 453 922 128 987 127 752 0```

### 输出

```
-1000
8
1001
2056
269891```

# 题解

## 作者：Lovely_Elaina (赞：10)

通过模拟可以得到一个显然易见的性质，反转操作只是改变正负。

那么时间复杂度允许我们进行 $n$ 次差分操作，我们每次只需要求和然后取绝对值，在所有绝对值里取最大值即可。

```cpp
#include <bits/stdc++.h>
// #define int long long
#define endl '\n'
using namespace std;
const int N = 5e2+5;

long long n,a[N],b[N];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin >> T;
    while(T--){
        long long cnt1 = 0;
        long long cnt2 = 0;
        long long ma = -114514191;
        
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            cnt1 += a[i];
        }
        
        if(n == 1){
            cout << a[1] << endl;
            continue;
        }
        
        ma = cnt1;
        while(n > 1){
            cnt2 = 0;
            for(int i = 1; i < n; i++){
                b[i] = a[i+1]-a[i];
                cnt2 += b[i];
            }
            n--;
            for(int i = 1; i <= n; i++)
                a[i] = b[i];
            ma = max(ma,abs(cnt2));
        }
        cout << ma << endl;
    }
    
    return 0;
}
```

---

## 作者：Yannik (赞：4)

## 题目大意：
给你一个序列 $A_n$，同时两个操作：
- 翻转序列，比如：$[$ $1$ $3$ $2$ $]$ 变为 $[$ $2$ $1$ $3$ $]$。
- 用差值序列替换序列，形式上：$[a_n - a_{n-1}, a_{n-1} - a_{n-2}, \dots, a_2 - a_1]$。举个例子：$[$ $1$ $3$ $2$ $]$ 变为 $[$ $2$ $-1]$。

问序列 $A_n$ 经过若干次变化后（也可以不变）的和的最大值 $ans$。
## 分析：
一个序列执行若干次 $2$ 操作后所得的 $ans =$ 这个序列现在的和 $sum$ 的绝对值。因为我们可以进行 $1$ 操作翻转。观察数据范围 $n≤50$，直接暴力枚举进行多少次 $2$ 操作即可。

## 小坑：
假设你不进行 $2$ 操作，进行 $1$ 操作是无意义的。
## 代码：
```cpp
#include<iostream>
#include<algorithm>
#define int long long 
using namespace std;
const int N = 100;
const int mod = 1e9 + 7;
int T,n,m,a[N];
signed main(){
	cin.tie(0)->ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n;
		int ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			ans+=a[i];
		}
		if(n==1){
			cout<<ans<<"\n";//不能进行1，2操作
			continue;
		}
		while(n){
			n--;
			for(int i=1;i<=n;i++){
				a[i]=a[i+1]-a[i];//2操作
			}
			int sum=0;
			for(int i=1;i<=n;i++) sum+=a[i];
			ans=max(ans,max(sum,-sum));//是否进行1操作
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：The_jester_from_Lst (赞：2)

注意到 $n$ 只有 $50$，可以考虑一些平方做法。

一次用差值替换序列后序列的长度会减少 $1$，因此这种操作至多进行 $49$ 次。所以我们不妨枚举这个操作的进行次数。

同时我们还观察到，用差值替换序列后，序列的和会变为未替换前的 $a_n-a_1$。据此我们可以在进行操作前判断逆转序列是否更优，即 $a_1-a_n$ 是否大于 $a_n-a_1$。大于则先逆转一下序列一定不劣。

这样，我们每次进行一次差值替换序列操作后将答案更新即可。

附上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define pii pair<int,int>
#define mk make_pair
#define fir first
#define sec second
#define pb emplace_back
#define mod 1000000007
#define put putchar
using namespace std;
il int rd(){
    int jya=0,tl=1;char jyt=getchar();
    while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
    while(isdigit(jyt)){jya=(jya<<1)+(jya<<3)+(jyt-'0');jyt=getchar();}
    return jya*tl;
}
il void wr(int jjy){
    if(jjy<0)putchar('-'),jjy=-jjy;
    if(jjy>9)wr(jjy/10);
    putchar(jjy%10+48);
}
const int JYAAKIOI=1e18,N=5e5+86,M=2e5+86;
int T,n,a[N],sum,ans;
signed main(){
	T=rd();
	while(T--){
		n=rd();
		ans=sum=0;
		for(int i=1;i<=n;++i){
			a[i]=rd();
			sum+=a[i];
		}
		ans=sum;
		while(n>1){
			if(a[n]-a[1]<a[1]-a[n])for(int i=1;i<=n/2;++i)swap(a[i],a[n-i+1]);
			ans=max(ans,a[n]-a[1]);
			for(int i=1;i<n;++i)a[i]=a[i+1]-a[i];
			--n;
		}
		wr(ans),put('\n');
	}
    return 0;
}
```

---

## 作者：feng_0108 (赞：1)

# Cirno and Operations 题解
## 解法说明：
如果只是简单反转数组不会对数组和产生任何影响，只有使用差分才会改变数组和。

对于一个长度为 $n$ 的数组来说，能进行 $n - 1$ 次差分操作（每次差分会减少一个元素），并且反转差分前的数组和绝对值等于反转差分后的数组和绝对值。例如 $[7, 9, -9]$ 差分后变成 $[2, -18]$，求和得到 $-16$，反转后并差分产生 $[18, -2]$，求和得到 $16$，所以每次差分完与最初数组和比较大小取最大即可。   
**注意：最终答案可能会爆int，建议使用long long。**

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 55;

int t, n, m, k;

LL a[N]; 

LL solve()
{
	cin >> n;
	LL ans = 0;
	for(int i = 1; i <= n; i ++ ) {
		cin >> a[i]; ans += a[i];
	}
	
	if(n == 1) return ans; // 无法反转差分
	
	while(n) // 不断差分
	{
		n --;
		LL tmp = 0;
		for(int i = 1; i <= n; i ++ ){
			a[i] = a[i + 1] - a[i];
			tmp += a[i];
		}
		
		ans = max(ans, llabs(tmp));
	}
	
	return ans;
}

int main()
{
	cin >> t;
	while(t -- )
		cout << solve() << endl;
	return 0;
 } 

```

---

## 作者：chinazhanghaoxun (赞：1)

## 题意
有两种对于长度为 $N$ 的序列的操作如下：

- 翻转整个序列。
- 将序列进行差分，设原长度为 $K$，则操作完后长度为 $K-1$。

关注数据范围，发现 $1\le N\le 50$，所以可以考虑 $O(n^2)$ 的实现方式。

模拟一下，发现翻转后进行差分后所有值的和会变为原来的相反数。如我们选择 $[5\ 7\ 3]$，此时 $x_1=-2$。翻转后变为 $[3\ 7 \ 5]$，$x_2=2$，即 $x_1=-x_2$。所以我们可以暴力枚举差分的次数，每次取 $\max(ans,-ans)$ 即可。
## 代码
[AC记录](https://codeforces.net/contest/2062/submission/303514627)
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[55],t; 
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		int ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			ans+=a[i];//至少有所有元素的和 
		}
		if(n==1){ //注意特判，因为只有一个会保持当前的和 
			cout<<ans<<endl;
			continue;
		}
		for(int i=1;i<n;i++){//枚举操作二的次数 
			int s=0;
			for(int j=1;j<=n-i;j++){//进行差分操作并求和 
				a[j]-=a[j+1];
				s+=a[j]; 
			}
			ans=max(ans,max(s,-s));//由于操作一会使和成为相反数，取较大值 
		}
		cout<<ans<<endl; 
	}	
	return 0;
}
```

---

## 作者：chenbs (赞：1)

题意简述：有两种操作，一种是**翻转数组**，一种是**将数组变为自身的差分数组**。你需要最大化数组元素的总和。

下文定义**翻转数组**为操作 $1$，**将数组变为自身的差分数组**为操作 $2$。

注意到，定义数组 $a$ 经过 $21$ 操作后的数组为 $b$，经过 $12$ 操作后的数组为 $c$，则 $c_i = -b_i (1 \le i <n)$。

又因为操作 $1$ 不影响数组总和，所以任何的操作序列，都可以看成若干次操作 $2$ 或操作 $2$ 加取相反数。因此，只需要一直差分，用总和的绝对值去更新答案即可。

```cpp
#include<bits/stdc++.h>
// 每次差分操作，值域最多变为原来的两倍，所以要 long long
#define int long long
using namespace std;
int t, n, a[55], b[55];
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>t;
	while(t--) {
		cin>>n;
		for(int i=1; i<=n; i++) cin>>a[i];
		int ans=-1e9;
		for(int i=n; i>=1; i--) {
			int s=0;
			for(int j=1; j<=i; j++) s+=a[j];
			ans=max(ans, i==n ? s : abs(s)); // 注意第一次不能取绝对值
			
			for(int j=1; j<i; j++) a[j]=a[j+1]-a[j]; // 执行差分操作
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：1)

虽然我是分析出的，但是我的好朋友告诉我大力手玩也能得出结论。~~真有必要吗。~~

对数列 $[a_1,a_2,\dots,a_n]$ 进行第一次操作可以得到 $[a_n,\dots,a_2,a_1]$。我们对这两个数列分别进行第二次操作，可以得到 $[a_2-a_1,a_3-a_2,\dots,a_n-a_{n-1}]$，$[a_{n-1}-a_n,\dots,a_1-a_2]$。

我们~~惊喜地~~发现这两个数组是相反的，并且值也是相反的。这是因为，我们仍然是对相邻两个元素做差，只是每个式子的减数和被减数反了过来。再对它们分别进行这两种操作得到的情况是类似的，所有的值都是一样的，但是可能位置相反或者符号相反。

于是我们只需要对原数组不断做差，然后求和，让答案和数组和以及其相反数取最大值即可。

代码：
```
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 55;

int a[N];

void solve() {
  int n, ans = -1145141919810114514, sum = 0;
  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
    sum += a[i];
  }
  ans = max(ans, sum);
  for(int i = 1; i < n; i++) {
    sum = 0;
    for(int j = 1; j + i <= n; j++) {
      a[j] -= a[j + 1];
      sum += a[j];
    }
    ans = max(ans, abs(sum));
  }
  cout << ans << '\n';
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
}
```

---

## 作者：Milthm (赞：0)

注意到差分和先翻转再差分两种操作，仅仅是一个正负号的变化。因为 $n\le 50$，我们可以直接暴力做差分，然后对和取绝对值更新答案即可。

当然还有个坑，就是虽然差分和先翻转再差分只有符号区别，但是当你不做差分操作的时候，你不能对它取绝对值（不然你连样例都过不去啊喂）。

另外这个 $n\le 50$ 和复杂度没啥关系，只是为了保证你的答案不会爆掉弄得这么小。


```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,a[55];
signed main(){
	cin>>T;
	while(T--){
		cin>>n;int ans=-1e9;
		for(int i=1;i<=n;++i)cin>>a[i];
		for(int i=n;i>=1;--i){
			int sum=0;
			for(int j=1;j<=i;++j)sum+=a[j];
			if(i<n)ans=max(ans,abs(sum));
			else ans=max(ans,sum);
			for(int j=1;j<i;++j)a[j]=a[j+1]-a[j];
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：nochiras (赞：0)

考虑 reverse 操作和 replace 操作对答案的影响：

* 单独 reverse
* 单独 replace
* reverse 后 replace
* replace 后 reverse

注意到第二种操作和后两种操作没有本质区别，只是 reverse 次数的不同，这点在代码实现上更明显。

重点的第三种、第四种操作对答案影响的区别也比较显然：

$$
\begin{aligned}
\text{rev + rep}&: [a_{n - 1} - a_n, a_{n - 2} - a_{n - 1}, \dots, a_1 - a_2] \\
\text{rep + rev}&: [a_n - a_{n - 1}, a_{n - 1} - a_{n - 2}, \dots, a_2 - a_1] \\
\end{aligned}
$$

单独拉出一项来看就容易发现其实只是正负性发生了变化，每项的正负性区别体现出 $sum$ 的符号差异，我们可以直接计算其中一种之后取一个相反数即可。

所以答案就是在若干次 reverse + repeat 操作之后 $sum$ 绝对值的最大值。

注意到 $n \leq 50$ 允许我们直接从 $0 \to 49$ 枚举差分的次数，然后取 $\max sum$，**注意到 $0$ 次操作时只有一种符号**。

还有非常致命的一点，答案的上界为 $10^3 \times 2^{50}$，需要开 `long long`。

---

