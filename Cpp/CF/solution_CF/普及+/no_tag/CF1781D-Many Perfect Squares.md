# Many Perfect Squares

## 题目描述

You are given a set $ a_1, a_2, \ldots, a_n $ of distinct positive integers.

We define the squareness of an integer $ x $ as the number of perfect squares among the numbers $ a_1 + x, a_2 + x, \ldots, a_n + x $ .

Find the maximum squareness among all integers $ x $ between $ 0 $ and $ 10^{18} $ , inclusive.

Perfect squares are integers of the form $ t^2 $ , where $ t $ is a non-negative integer. The smallest perfect squares are $ 0, 1, 4, 9, 16, \ldots $ .

## 说明/提示

In the first test case, for $ x = 0 $ the set contains two perfect squares: $ 1 $ and $ 4 $ . It is impossible to obtain more than two perfect squares.

In the second test case, for $ x = 3 $ the set looks like $ 4, 9, 16, 25, 100 $ , that is, all its elements are perfect squares.

## 样例 #1

### 输入

```
4
5
1 2 3 4 5
5
1 6 13 22 97
1
100
5
2 5 10 17 26```

### 输出

```
2
5
1
2```

# 题解

## 作者：WilliamFranklin (赞：11)

omg tourist round

这题主要用了初中的一点点小知识。。。

### 主要思路

声明一下：我们设 $g(x)$ 为 $a_1 + x, a_2 + x, \cdots , a_n + x$ 中完全平方数的个数。

首先，答案至少为 $1$，这里不再证明。

那么我们就想，如何让答案更大，也就是至少等于 $2$。

首先我们枚举两个下标 $i \left(i \le n\right)$ 与 $j \left(j \le n\right)$，其中 $i < j$。

下面，找出 $x$ 与 $a_i$ 和 $a_j$ 的关系即可。

那么我们设 $a_i + x = p^2$ 与 $a_j + x = q^2$。然后，我们用第二个式子减第一个式子得出 $a_j - a_i = q^2 - p^2$。发现等式右边可以用平方差公式，式子也就变为：$a_j - a_i = (q - p)(q + p)$。我们发现，这个 $q - p$ 是 $a_j - a_i$ 的一个因数，那么我们就设 $q - p$ 为 $d$，就会得到下面两个等式：

$$\begin{cases} q - p = d \\ q + p = \frac{a_j - a_i}{d} \end{cases}$$

然后，两个等式一减一加，我们就可以得出 $p$ 与 $q$：

$$\begin{cases} p = \frac{1}{2}(\frac{a_j - a_i}{d} - d) \\ q = \frac{1}{2}(\frac{a_j - a_i}{d} + d) \\ \end{cases}$$

好，那么下一步该干什么呢？

对！求 $x$！！！

其实只要把 $p$ 和 $q$ 带到原来的式子里即可：$x = \frac{1}{4}(\frac{a_j - a_i}{d} - d)^2 - a_i = \frac{1}{4}(\frac{a_j - a_i}{d} + d)^2 - a_j$

都已经求出 $x$ 了，求 $g(x)$ 还难吗？直接枚举就行了啊！

不过。。。提一点：有些人在判断某个数是否为完全平方数时，想到了用质因数分解求因数个数，看看这个数的因数是否为奇数，例如下面代码：

```cpp
#include <iostream>
#include <sstream>
#include <cmath> 
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

#define int long long

const int N = 55;

long long a[N];
int n;

bool check(int x) {
	int i = 2;
	int ans = 1;
	
	while (x != 1) {
		int cnt = 0;
		while (x % i == 0) {
			x /= i;
			cnt++;
		}
		ans = ans * (cnt + 1);
		i++;
		if (x < i) break;
	}
	
	if (x != 1) {
		ans *= 2;
	}
	
	return ans % 2;
}

signed main() {
	int t;
	
	cin >> t;
	
	while (t--) {
		cin >> n;
		
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		
		int ans = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				for (int k = 1; k * k <= (a[j] - a[i]); k++) {
					if ((a[j] - a[i]) % k == 0) {
						long long q = ((a[j] - a[i]) / k + k);
						
						if (q % 2 == 0) { 
							q /= 2;
							if (q * q >= a[j]) {
								int x = q * q - a[j];
								int nans = 0;
								
								//cout << k << ' ' << q << ' ' << x << ' ' << nans << endl;
								
								for (int l = 1; l <= n; l++) {
									if (check(a[l] + x)) {
										nans++;
									}
								}
								
								ans = max(ans, nans);
							}
						}
						
						q = ((a[j] - a[i]) / ((a[j] - a[i]) / k) + (a[j] - a[i]) / k);
						
						if (q % 2 == 0) {
							q /= 2;
							if (q >= a[j]) {
								int x = q * q - a[i];
								int nans = 0;
								
								//cout << (a[j] - a[i]) / k << ' ' << ' ' << q << ' ' << x << ' ' << nans << endl;
								
								for (int l = 1; l <= n; l++) {
									if (check(a[l] + x)) {
										nans++;
									}
								}
								
								ans = max(ans, nans);
							}
						}
					}
				}
			}
		}
		
		cout << ans << endl;
	}
	
	return 0;
} 
```
完美的 TLE 了。

为什么呢？

很简单，我们来算一下时间复杂度。

首先我们要枚举 $i$ 和 $j$，是 $O(n^2)$ 的，然后内层还要枚举一下 $a_j - a_i$ 的因数，目前时间复杂度就是 $O(n^2 \cdot f(a_n))$ 的，其中 $f(a_n)$ 表示 $a_1, a_2, \cdots, a_n$ 中最多的因数个数，计算 $x$ 是 $O(1)$ 的，但是求 $g(x)$ 时，是 $O(n \cdot \sqrt{a_n + x})$ 的，所以总的时间复杂度是远超于 $O(n^3 \cdot f(a_n) \cdot \sqrt{a_n})$ 的。所以，不超时才怪。

那么如何优化时间复杂度呢？

我们可以从判断完全平方数来入手。具体看代码的 check 函数。

### AC Code

```cpp
#include <iostream>
#include <sstream>
#include <cmath> 
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

#define int long long

const int N = 55;

long long a[N];
int n;

//Look here!!!
bool check(int x) {
	int y = sqrt(x);
	
	if (y * y == x) return 1;
	else return 0;
}

signed main() {
	int t;
	
	cin >> t;
	
	while (t--) {
		cin >> n;
		
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		
		int ans = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				for (int k = 1; k * k <= (a[j] - a[i]); k++) {
					if ((a[j] - a[i]) % k == 0) {
						long long q = ((a[j] - a[i]) / k + k);
						
						if (q % 2 == 0) { 
							q /= 2;
							if (q * q >= a[j]) {
								int x = q * q - a[j];
								int nans = 0;
								
								//cout << k << ' ' << q << ' ' << x << ' ' << nans << endl;
								
								for (int l = 1; l <= n; l++) {
									if (check(a[l] + x)) {
										nans++;
									}
								}
								
								ans = max(ans, nans);
							}
						}
						
						q = ((a[j] - a[i]) / ((a[j] - a[i]) / k) + (a[j] - a[i]) / k);
						
						if (q % 2 == 0) {
							q /= 2;
							if (q >= a[j]) {
								int x = q * q - a[i];
								int nans = 0;
								
								//cout << (a[j] - a[i]) / k << ' ' << ' ' << q << ' ' << x << ' ' << nans << endl;
								
								for (int l = 1; l <= n; l++) {
									if (check(a[l] + x)) {
										nans++;
									}
								}
								
								ans = max(ans, nans);
							}
						}
					}
				}
			}
		}
		
		cout << ans << endl;
	}
	
	return 0;
} 
```

这个代码的时间复杂度为 $O(n^3 \cdot f(a_n))$，并且 $n \le 50$，$a_i \le 10^9$，所以不会超时。

这题还算简单吧，[tourist](https://codeforces.com/profile/tourist) 出的题太经典了。

也许有一些不对或不严谨的地方，请各位大佬指出，谢谢！

注：2023.7.16 修复了一个式子 bug，感谢 [精神小伙！](https://www.luogu.com.cn/user/304211) 大佬提出。

---

## 作者：shipeiqian (赞：7)

## 题意

给出一个长度为 $n$ 的数组 $a$，找出一个 $x(0\leq x\leq 10^{18})$ 使 $(a_1+x,a_2+x,\dots,a_n+x)$ 中完全平方数的数量最多。

## 思路

首先可以想到，在一个数组中，通过给每个元素加上某个 $x$，必然会出现至少一个完全平方数，所以可以考虑两个完全平方数的情况，然后再统计其对应的的 $x$ 能让数组中出现多少个完全平方数，取最大值即可。

假设有两个数 $a_i$ 和 $a_j$,且 $(a_i+x)$ 与 $(a_j+x)$ 均为完全平方数

$\left\{\begin{matrix}
a_i+x=p^2\quad①\\
a_j+x=q^2\quad ②
\end{matrix}
\right.$

$①-②$ 得

$a_i-a_j=p^2-q^2$

$\therefore a_i-a_j=(p-q)(p+q)$

$(a_i-a_j)$ 为固定值，枚举 $(p-q)$

令 $(p-q)=t$

$\therefore(p+q)=\frac{a_i-a_j}{t}$

$\therefore\left\{\begin{matrix}
p-q=t\\
p+q=\frac{a_i-a_j}{t}
\end{matrix}
\right.$

解得 $\left\{\begin{matrix}
p=\frac{t+\frac{a_i-a_j}{t}}{2}\\
q=\frac{\frac{a_i-a_j}{t}-t}{2}
\end{matrix}
\right.$


$\therefore x=(\frac{t+\frac{a_i-a_j}{t}}{2})^2-a_i=(\frac{\frac{a_i-a_j}{t}-t}{2})^2-a_j$

枚举 $(a_i-a_j)$ 的其中一个因子 $t$，求出 $x$，然后遍历数组 $a$，将 $(a_1,a_2,…,a_n)$ 依次加上 $x$，统计有几个完全平方数,并用 $ans$ 每次记录最大值即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,ans,a[55];
void solve(){
    ans=1;//本来就一定有一个
    cin >>n;
    for(int i=1;i<=n;i++)cin >>a[i];
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){//枚举a_i和a_j
            int diff=a[j]-a[i];
            for(int t=1;t*t<=diff;t++){
                if(diff%t!=0||(diff/t+t)%2==1)continue;//除不尽直接跳过
                ll temp=(diff/t-t)/2;//这里分开来
                ll x=temp*temp-a[i];//算防止爆long long
                if(x<0)continue;//x必须>=0
                int cnt=0;//记录
                for(int k=1;k<=n;k++){
                    ll now=sqrtl(a[k]+x);
                    if(now*now==a[k]+x)cnt++;//判断是否为完全平方数
                }
                ans=max(ans,cnt);
            }
        }
    }
    cout <<ans <<"\n";
}
int main(){
    int t;
    cin >>t;
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：Andy_Li (赞：6)

# CF1781D Many Perfect Squares 题解

## 题意

$n$ 个数，对于每个 $a_i$，将其加上一个 $x$，问最多有几个 $a_i + x$ 后是完全平方数。

## 思路

因为每个 $a_i$ 加的数是一样的，加了之后差并不会变，并且 $n$ 很小，最大只有 $50$，所以我们枚举两个数之间的差 $a_j - a_i \ (j > i)$。

设两数之差为 $t$。

设两个完全平方数是 $a , b \ (a > b)$。则这两个数的差是 $(a+b) \times (a-b)$。所以我们枚举 $t$ 的因子。

设 $d_1$ 是 $t$ 的因子，则 $ \frac{t}{d_1}$ 也是 $t$ 的因子，设为 $d_2$。

每次考虑给 $n$ 个数加上一个值 $p$。

$$ p = {(d_1 + {  \frac {d_2 - d_1}{2} })} ^ 2 - a_j$$

如果 $p \le 0$，直接 $continue$。

## 关于复杂度

理论复杂度：$O(n^3 \times \sqrt{1e9} \ ) \ = \ 4e9$

实际复杂度：$O(250 \times n^3 \ + \ n^2 \times \sqrt{1e9} \ ) \ = \ 1e8$

因为 $a_i \le 1e9$ 的缘故，$a_j - a_i$ 最大为 $1e9$。所以因子个数最多为 $500$。又因为只枚举一半的因数，所以枚举因子数为 $250$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
const int maxn=2e5+7;
ll a[55];
signed main()
{
	cin.tie(0);
	std::ios::sync_with_stdio(false);
// srand((unsigned)time(NULL));
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
	int t;
	cin>>t;
	while(t--)
	{
		int n,ans=1,cnt=0;
		ll tt=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if((ll)(sqrt(a[i]))*(ll)(sqrt(a[i]))==a[i])
				cnt++;
		}
		ans=max(ans,cnt);
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
			{
//				cout<<" "<<x<<endl;
				ll xx=a[j]-a[i];
				for(ll k=1;k*k<=xx;k++)
					if(xx%k==0)
					{
						ll x=k,y=xx/k;
//						if(y<x)
//							swap(x,y);
						if((y-x)%2==1)
							continue;
						ll d=x+(y-x)/2;
						ll e=d-x;
						ll t=max(d,e)*max(d,e)-a[j];
						if(t<=0)
							continue;
						int cnt=0;
						for(int q=1;q<=n;q++)
							if((ll)(sqrt(a[q]+t))*(ll)(sqrt(a[q]+t))==a[q]+t)
								cnt++;
						if(cnt>ans)
						{
							ans=cnt;
							tt=t;
						}
//						cout<<" "<<t<<endl;
					}
			}
		cout<<ans/*<<" "<<tt*/<<endl;
	}
	return 0;
}
//
//
```

---

## 作者：wwwwwza (赞：5)

**题目化简：**   
你自己给出一个 $x$，使得 $a_1+x,a_2+x,\cdots,a_n+x$ 中的完全平方数最多，输出有多少个。  
**做法:**   
假设 $a_i+x$ 和 $a_j+x$ 都是完全平方数，将它们分别表示为 $p^{2}$ 和 $q^{2}$。  
根据平方差公式可得 $p^{2}-q^{2}=(p+q)(p-q)$  
接着枚举 $(p+q)(p-q)$ 的每一个因数，代入式子，算出 $p$ 和 $q$。就可算出 $x$。  
最后枚举 $a$ 数组，看看有几个 $a_i+x$ 为完全平方数，输出最多的一个即可。    
**代码：**
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
int t,n,a[55];
bool cmp(int a,int b){
	return a>b;
}
signed main(){
	cin >>t;
	while(t--){
		cin >>n;//输入 
		int ans=1;
		for(int i=1;i<=n;i++){
			cin >>a[i];
		}
		sort(a+1,a+1+n,cmp);//排序，不然计算时要用绝对值 
		for(int i=1;i<n;i++){
			for(int j=i+1;j<=n;j++){//枚举每两个数 
				int p=a[i]-a[j];
				for(int k=1;k*k<=p;k++){//算出差值 
					if(p%k==0){//判断x是否存在 
						if((k+p/k)%2==1)continue;
						int x=(k+p/k)/2;
						int y=p/k-x;
						if(x*x<a[i]||y*y<a[j])continue;
						int f=x*x-a[i],sum=0;
						for(int l=1;l<=n;l++){//枚举加上x后有多少完全平方数 
							if(sqrt(a[l]+f)==(int)sqrt(a[l]+f))sum++;
						}
						ans=max(ans,sum);
					}
				}
			}
		}
		cout <<ans<<endl;//输出 
	}
	return 0;
}

```

---

## 作者：daiarineko (赞：2)

# 题解【CF1781D Many Perfect Squares】

## 0. 题意

给出长度为 $n$ 的数组 $a_1\dots a_n$，任选一个 $0\leq x\leq 10^{18}$，使得 $a_1+x,a_2+x,\dots,a_n+x$ 组成的数组里有最多的完全平方数，并求出这个最多的完全平方数个数（不需要给出 $x$）。

## 1. 思路

考虑对每个 $1\leq i<j\leq n$ 求出 $a_j-a_i$，若 $a_i+x$ 和 $a_j+x$ 都为完全平方数，则设 $a_i+x=u^2$，$a_j+x=v^2$，这时 $a_j-a_i=(v+u)(v-u)$。

我们可以通过 $a_j-a_i$ 推出所有可能的二元组 $(u,v)$，因为 $a_j-a_i$ 是 $10^9$ 量级的，而 $d_i$（因数个数）在 $10^9$ 范围内至多为大约 $1000$，所以这样的二元组并不会有很多（$O(n^2d)$），可以存下。

抽象来看，对于任意 $i,j$ 的一个二元组 $(u,v)$ 相当于分层图上 $(u_i,v_j)$ 的一条连边。而最多的完全平方数个数就相当于这个分层图上的最长路径，这是可以深搜求出的。

## 2. 实现

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[52];
vector<pair<int, int>> d[52][52];
void D(int n, vector<pair<int, int>> &ans, int u, int v)
{ // 作用：求出某个 i, j 对应的所有二元组，存储到容器 ans 中
// 参数：n 为 a[j]-a[i], u 为 i, v 为 j
    ans.clear();
    for (int i = 1; i * i <= n; ++i)
    { // 求出可能的 (u, v)
        int apb = n / i, amb = i; // (a+b)(a-b)=n
        int a = (apb + amb) / 2;  // a+b+a-b=2a
        int b = apb - a;          // a+b-a=b
        if (::a[u] <= b * b && a >= 0 && b >= 0 && a > b && (a + b) * (a - b) == n) // 进行一些边界判断，因为 x 不能为负
            ans.emplace_back(b, a);
    }
    return;
}
vector<int> tmp;
int ans;
void dfs(int u, int dep, int num)
{ // 参数：当前层数 搜索深度 当前节点
// 层数对应的是原题中 a 的元素，节点对应的是当前的数值
    ans = max(ans, dep); // 注意有可能没办法到达最后一层，因此搜索到每个节点都要保存答案
    if (u == n)
        return;
    if (dep + n - u <= ans)
        return; // 进行最优性剪枝，可以加快搜索速度
    for (int v = u + 1; v <= n; ++v)
        for (auto k : d[u][v])
            if (k.first == num)
                dfs(v, dep + 1, k.second);
}
signed main()
{
    int t;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t--)
    {
        cin >> n;
        ans = 1;
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
                D(a[j] - a[i], d[i][j], i, j);
        for (int i = 1; i <= n; ++i)
        { // 枚举层数
            tmp.clear();
            for (int j = i + 1; j <= n; ++j)
                for (auto k : d[i][j])
                {
                    tmp.emplace_back(k.first); // 枚举当前层从哪些节点开始能够进行搜索，减少函数调用次数
                }
            int k = unique(tmp.begin(), tmp.end()) - tmp.begin();
            for (int j = 0; j < k; ++j)
                dfs(i, 1, tmp[j]);
        }
        cout << ans << endl;
    }
    cout.flush();
    return 0;
}
```

## 3. 附注

本题中对每个 $i,j$ 求出 $a_j-a_i$，之后套用平方差公式求出可能的 $(u,v)$。求差求和、套用公式是常用的构造技巧；同时对于较小的数据范围，搜索往往有奇效。


---

## 作者：REAL_曼巴 (赞：1)

此题是一个数学题。

题意是给定 $n$ 个数，让你找到一个数 $x$ 加到每个数上，问能使得所有数中最多有多少完全平方数。

我们可以设一个方程组来解决这个问题。我们把原数组的两个数设为 $a_1$ 与 $a_2$，之后他们都要加 $x$，变成 $a_1+x$ 与 $a_2+x$，让他们都是一个完全平方数。

则有：

$\begin{cases}a_{1}+x=p^{2}&\\ a_{2}+x=q^{2}&\end{cases} $ 

之后两式子相减并用平方差公式化简。

之后会得到 $x$ 为 $({\frac{\frac{a_1-a_2}{p-q}\pm {p-q}}{2} })^2 - a_{1,2} $。

所以我们这个式子中唯一不知道的量就是 $a_1-a_2$ 我们只需要枚举其和其因数得到 $x$ 进行验证，复杂度就会大大降低（因为不是所有数都要进行检验）。最后取出最大的情况即可。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool check(int cur){
    bool f=((long long)(sqrt(cur))*(long long)(sqrt(cur))==cur);
    return f;
}
int a[501];
signed main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        int maxn=-1;
        for(int i=1;i<=n;++i){
            for(int j=i+1;j<=n;++j){
                int a1_a2=a[j]-a[i];//p-q倍数
                for(int k=1;k*k<=a1_a2;++k){
                    if(a1_a2%k==0){//shi1
                        if((a1_a2/k+k)%2==0){
                                int x=((a1_a2/k-k)/2)*((a1_a2/k-k)/2)-a[i];
                                if(x<0)continue;
                                int ans=0;
                                for(int w=1;w<=n;++w)if(check(a[w]+x))ans++;
                                maxn=max(maxn,ans);
                            }
                        }
                    }
                }
            }
        cout<<abs(maxn)<<endl;
    }
    return 0;
}
```


---

## 作者：Hedgehog_210508 (赞：1)

**题目传送门**：[here](https://www.luogu.com.cn/problem/CF1781D)

**思路**：首先发现 $n$ 很小。
对于任何一个 $a_i$，显然存在一个 $x$ 使它为平方。然而对单个 $a_i$ 满足条件的 $x$ 只能做到 $1$，没有意义，若直接枚举会有大量无意义的解，导致超时。我们考虑同时对两个数满足条件的 $a_i$，平方差处理。把所有这样可能的解存入数据结构选取最大的即可。

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t;
int main(){
	std::ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		ll n,a[109],ans=0;
		map<ll,ll> x;
		set<ll> m[109];
		cin>>n;
		for(ll i=1;i<=n;i++) cin>>a[i];
		x.clear();
		for(ll i=1;i<=n;i++) m[i].clear();
		for(ll i=1;i<=n;i++){
			for(ll j=i+1;j<=n;j++){
				ll tmp=a[j]-a[i];
				for(ll k=1;k*k<tmp;k++){
					if(tmp%k) continue;
					if((k+tmp/k)&1) continue;
					ll c=(tmp/k-k)/2;
					if(c*c<a[i]) continue;
					c=c*c-a[i];
					m[i].insert(c),m[j].insert(c);
				}
			}
		}
		set<ll>::iterator sit;
		for(ll i=1;i<=n;i++){
			for(sit=m[i].begin();sit!=m[i].end();sit++) x[*sit]++,ans=max(x[*sit],ans);
		}
		cout<<max(ans,ll(1))<<endl;
	}
	return 0;
}

```


---

