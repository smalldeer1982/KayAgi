# Sasha and Magnetic Machines

## 题目描述

### 题意简述

有一个长度为$n$的正整数序列$a_{1..n}$。你可以对这个数列进行最多$1$次的如下操作：

- 选择$1 \leq i,j \leq n\ \ (i \neq j)$，并选择一个可以整除$a_i$的正整数$x$，然后将$a_i$变为$\frac{a_i}{x}$，将$a_j$变为$a_j \cdot x$。

问你操作后，该序列中所有数的和最小能达到多少。

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
14
```

## 样例 #2

### 输入

```
4
4 2 4 4
```

### 输出

```
14
```

## 样例 #3

### 输入

```
5
2 4 2 3 7
```

### 输出

```
18
```

# 题解

## 作者：Fuxh_18 (赞：3)

~~暴力大法好~~

## 问题分析

本题的数据范围不大，于是乎，本蒟蒻想到了暴力做法。

我们可以枚举每一个 $i$ 和 $x$ 和 $j$（如题）。若想要做到更优解，我们可以再次优化：先排序，想要 $a_j$ 是序列中最小的数，就可以找序列第一个数，也就是 $j=1$（因为 $i$ 不等于 $j$，若 $i=1$，$j$ 就为 $2$），于是就可以少枚举一次 $j$。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+1;
int a[N],n,ans=INT_MAX,sum;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i]; //记录初始值之和 
	}
	ans=sum;
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		for(int j=2;j<=sqrt(a[i]);j++){
			if(a[i]%j==0){ //可以除尽 
				int res=sum;
				res-=a[i]; //减去初始 
				res+=a[i]/j; //加上更改 
				if(i==1){ //由于 i!=j，当i=1时，a[j]最小值为a[2] 
					res-=a[2];
					res+=a[2]*j;
				}
				else{
					res-=a[1];
					res+=a[1]*j;
				}
				ans=min(ans,res); //更新最小值 
			}
		}
	}
	cout<<ans;
	return 0;
}
```

希望能帮助到大家。

---

## 作者：晴空一鹤 (赞：2)

### Solution

首先假如我们已经确定了 $i$ 和 $x$ ，由于要让和最小而 $a_j$ -> $a_{j}\times x$ 很明显 $x>=1$ 所以 $a_j$ 越小越好，所以我们要选尽量小的 $a_j$ 。

由于要求 $i\ne j$ 于是对原数组排序，如果一个数不是最小或最小有多个那都可以选最小，否则就选次小。

转移的话直接枚举 $i$ 和 $x$ ,如果 $a[i] \bmod x =0$ 则可以转移，时间复杂度 $O(n\times val)$ ( $val$ 表示值域范围 )。

其实还可以再优化，因为一个数的因子是成对出现的，较小的那个会小于等于 $\sqrt{a[i]}$ ，转移时可以一起作，时间复杂度 $O(n \times \sqrt{val} )$ 。

#### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],m,cm,sum,ans;
int main()
{
  cin>>n;
  for(int i=1;i<=n;i++)
  {
  cin>>a[i];
  sum+=a[i];
  }
  sort(a+1,a+n+1);
  m=a[1],cm=a[2];
  for(int i=1;i<=n;i++)
  for(int j=1;j<=sqrt(a[i]);j++)//注意不要写成j<=sqrt(i)
  if(a[i]%j==0&&i==1)
  ans=min(ans,cm*(j-1)-(a[i]-a[i]/j)),ans=min(ans,cm*(a[i]/j-1)-(a[i]-a[i]/(a[i]/j)));
  else if(a[i]%j==0&&i!=1)
  ans=min(ans,m*(j-1)-(a[i]-a[i]/j)),ans=min(ans,m*(a[i]/j-1)-(a[i]-a[i]/(a[i]/j)));
  printf("%d\n",sum+ans);
}
```


---

## 作者：lvyijia44 (赞：2)

虽然n比较大，但是因为 $a_i$ 在 $1\sim100$ 之间，所以在 $a_i$ 里会重复很多，而操作只有一次，所以多出来没有用，所以我们在这一百个数里 $O(n^3)$ 暴力枚举就可以了。
```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn=105;

inline int read(){//快读
	int ans=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		ans=(ans<<3)+(ans<<1)+(ch&15);
		ch=getchar();
	}
	return ans*f;
}
inline void p(int m){
	printf("%d ",m);
}

int n,sum;
bool a[maxn];

int main(){
	n=read();
	for(int i=1;i<=n;i++){
		int k=read();
		a[k]=true;
		sum+=k;
	}
	
	int minn=99999999;//先赋一个很大的值，防止对最终结果产生影响
	for(int i=1;i<=100;i++)
		for(int j=1;j<=100;j++)
			for(int m=1;m<=i;m++)
				if(a[i] && a[j] && !(i%m))
					minn=min(minn,(i/m+j*m-i-j));
              				//minn是对最终结果的贡献
	
	p(sum+minn);
	return 0;		
} 
```

随便加个快读就跑了406ms。。。

---

## 作者：rqzhangzehao (赞：0)

拿到题目，发现数据 $a_i$ 小的一批，第一时间考虑暴力。

## 思路
因为 $a_i$ 非常小，所以我们在用到 $a_i$ 的时候，就用 $vis$ 数组标记一下就行（其实可以把 $n$ 所缩小到 $\max a_i$ 大小，可以节约一点时间）。

## 做法
每次暴力枚举 $a_i$ 和 $a_j$，然后枚举 $x$，然后如果能整除，就记录答案。

时间复杂度：$O((\max a_i)^3)$。

## 代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
bool vis[105];
int sum,ans=1e18;
int minn=1e18,maxx=-1e18;
signed main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		vis[x]=1;
		sum+=x;
		minn=min(minn,x),maxx=max(maxx,x);
	}
	for(int ai=minn;ai<=maxx;ai++){
		for(int aj=minn;aj<=maxx;aj++){
			for(int k=1;k<=ai;k++){
				if(vis[ai]&&vis[aj]&&ai%k==0){
					ans=min(ans,sum-ai-aj+ai/k+aj*k);
				}
			}
		}
	}
	cout<<ans;
}
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述

有一个长度为 $n$ 的正整数序列。你可以对这个数列进行最多 $1$ 次的如下操作：

- 选择两个数 $i$ 和 $j$，其中 $1 \leq i,j \leq n$ 并且 $i \neq j$，并选择一个可以整除 $a_i$ 的正整数 $x$，然后将 $a_i$ 变为 $\frac{a_i}{x}$，将 $a_j$ 变为 $a_j \cdot x$。

问你操作后，该序列中所有数的和最小能达到多少。

$2 \leq n \leq 5 \cdot 10^4$，$1 \leq a_i \leq 100$。

## 题目分析

考虑枚举每一个 $a_i$，由于 $a_i$ 很小，所以可以直接枚举 $a_i$ 的因子 $x$，因为要让操作后的和最小，所以 $a_j$ 一定是序列中除了 $a_i$ 的最小值，维护一个最小值和次小值，如果 $a_i$ 是最小值，那么 $a_j$ 就是次小值，否则 $a_j$ 就是最小值，确定了以上三个值后按照题意更新答案即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define random(a,b) (rand()%(b-a+1)+a)
#define se second
#define fi first
#define pr pair<int,int>
#define pb push_back
#define ph push
#define ft front
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
#define mem(a,b) memset(a,b,sizeof a)
const int N=5e4+10;
int a[N],Min=N,Min2=N,sum,ans=N*1000,n;
void solve()
{
	cin>>n;
	For(i,1,n)
	{
		cin>>a[i];
		sum+=a[i];
		if(a[i]<Min)
		{
			Min=a[i];
		}
	}
	For(i,1,n)
	{
		if(a[i]>Min&&a[i]<Min2)
		{
			Min2=a[i];
		}
	}
	For(i,1,n)
	{
		int temp=(a[i]==Min?Min2:Min);
		For(j,1,a[i])
		{
			if(a[i]%j==0)
			{
				ans=min(ans,sum-a[i]+a[i]/j+temp*(j-1));
			}
		}
	}
	cout<<ans;
}
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
	return 0;
}
```

---

## 作者：_dijkstra_ (赞：0)

$a_i$ 非常小，考虑暴力。

## 思路

既然 $a_i$ 很小，我们可以试图在计算时，把 $n$ 缩小到 $\max a_i$ 的阶级。

做法也很容易：看看哪些数用过，标记好。

每次暴力枚举 $a_i$ 与 $a_j$，暴力枚举 $x$，如果能整除，暴力计算答案。

然后就做完了。时间复杂度按大的算， $O(\ (\max a_i)^3)$，codeforces 评测机轻松跑过。

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int inf = 2147483647;
bool vis[105];
int main()
{
	int n, sum = 0, ans = inf;
	int mn = inf, mx = -inf;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int x; scanf("%d", &x);
		vis[x] = true, sum += x;
		mn = min(mn, x), mx = max(mx, x);
	}
	for (int ai = mn; ai <= mx; ai++)
		for (int aj = mn; aj <= mx; aj++)
			for (int k = 1; k <= ai; k++) //枚举因数
				 if (vis[ai] && vis[aj] && ai % k == 0)
				 	ans = min(ans, sum - ai - aj + ai / k + aj * k);
	cout << ans;
	return 0;
}
```

希望能帮助到大家！

---

## 作者：lzyqwq (赞：0)

~~这题能评蓝真的是个奇迹。~~

### $\texttt{Description}$

首先，我们枚举 $a_1\sim a_n$ 的因数作为 $x_i$，那么 $a_i$ 就变成了 $\dfrac{a_i}{x_i}$，考虑将 $a_j$ 乘上 $x_i$ 后和最小，说明 $a_j$ 要尽量小。因此我们处理出原数组的最小值以及次小值（因为 $i\ne j$，所以当 $a_i$ 为最小值时，要使 $a_j$ 尽量小，则 $a_j$ 应该为次小值）。

当然，当原数组有多个最小值时，$a_j$ 仍取到最小值 ，我的代码的最小值是可以考虑到这种情况的。


最后别忘记考虑不改变的情况，所以要先将原数组的和处理出来。

这样的方法时间复杂度为 $\Theta(\sum\limits_{i=1}^n\sqrt{a_i})$，空间复杂度为 $\Theta(n)$。当 $n$ 和 $a_i$ 都取到最大时，时间复杂度不会超过 $\Theta(10^6)$，所以还是比较快的了。

讲完了。

### $\texttt{Solution}$

$40$ 行不压行代码，本蒟蒻自认为码风比较规范。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e4 + 5;
int n, a[N], t, u = 0x3f3f3f3f, ans, s = 0x3f3f3f3f;
int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    cin >> n;
    a[0] = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ans += a[i];
        if (a[i] < a[t]) {//求最小值，其中 a[t] 为最小值
            t = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (i != t) {
            u = min(a[i], u);//求次小值，u 为次小值
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 2, k; j * j <= a[i]; j++) {
        //枚举因数，注意这里枚举的是指数不超过 1/2 的因数
        //还有与它匹配的指数不低于 1/2 的因数需要用 a[i] / j 得到。
        //这里直接从 2 开始枚举，因为 j = 1 时相当于没改
            if (!(a[i] % j)) {
                k = a[i] / j;
                if (i == t) {
                    s = min(s, ans - a[i] + a[i] / j - u + u * j);
                    s = min(s, ans - a[i] + a[i] / k - u + u * k);
                } else {
                    s = min(s, ans - a[i] + a[i] / j - a[t] + a[t] * j);
                    s = min(s, ans - a[i] + a[i] / k - a[t] + a[t] * k);
                }
            }
        }
    }
    cout << min(ans, s) << '\n';
    return 0;
}
```

完结撒花！

---

## 作者：wol_qq (赞：0)

此题是大水题，用一遍贪心就好了，~~作者错了十几遍就对了~~。

### 题目大意

输入一串数，可以对两个数 $i,j(i\ne j)$，找出 $a_i$ 的一个因子 $x$，把 $a_i$  变成 $\dfrac{a_i}{x}$ ，把 $a_j$ 变成 $a_j\times x$，求一次修改后 $\sum\limits_{i=1}^na_i$ 最小是多少？

---

读了题目，作者马上想到了用暴力。

### 暴搜思路

直接用 $n^2$ 枚举所有的 $(i,j)$ 点对，枚举 $a_i$ 的一个因数 $x$，然后就可以求出 $ans=\min\limits_{i=1}^n\min\limits_{j=1}^n\min\limits_{x\mid
a_i}\dfrac{a_i}{x}-a_i+a_j\times x-a_j[i\ne j]$。

显而易见，这样暴力的时间复杂度为$O(n^2\times\max\limits_{i=1}^na_i)$。

这样就能拿到前七个点的分了。

### 部份分代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,a[maxn],anss;
int ans=0x3f3f3f3f3f3f3f3f;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){//枚举a
		for(int j=1;j<=i;j++){
			if(a[i]%j==0){//枚举a的因数
				for(int l=1;l<=n;l++){
					if(l!=i){
						for(int k=1;k<=n;k++){//枚举b
							if(k==i)anss+=a[i]/j;
							else if(k==l)anss+=a[l]*j;
							else anss+=a[k];
						}
						ans=min(anss,ans);//求出修改后的最小值
						anss=0;
					}
				}
			}
		}
	}
	cout<<ans;
}
```

### 贪心思路

我们肯定要选一个最小的数去做乘法。设 $f(i,j,x)=\dfrac{a_i}{x}-a_i+a_j\times x-a_j$，因为当 $i$ 和 $x$ 确定后，$f(i,j,x)$ 的大小之和 $j$ 有关，即 $a_j\times(x-1)$，所以选择使 $a_j$ 最小的 $j$ 可以使 $f(i,j,x)$ 最小。

因此，我们只需要求出原数列中的最小值和次小值就可以进行贪心，当 $i,x$ 确定的时候，若 $i$ 本身的最小值，那么就选择次小值，否则就选择最小值。


然后就 AC 了。

### 满分代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
int n,a[maxn],anss,sum=0;
int ans=0x3f3f3f3f;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],sum+=a[i];
    sort(a+1,a+n+1);// 这样 a[1] 为最小值，a[2] 为次小值。
    for(int i=1;i<=n;i++){
        if(i==1){//特判 i 为最小值
            for(int j=1;j<=a[i];j++){
                if(a[i]%j==0){//枚举因数
                    ans=min(ans,sum-a[i]-a[2]+a[i]/j+a[2]*j);
                }
            }
        }
        else {
            for(int j=1;j<=a[i];j++){
                if(a[i]%j==0){//枚举因数
                    ans=min(ans,sum-a[1]-a[i]+a[i]/j+a[1]*j);
                }
            }
        }
    }
    cout<<ans;
}
```

### 再次改进思路

可以看见，上面代码枚举因数时间复杂度为 $O(\max\limits_{i=1}^na_i)$ ，而枚举一个数 $k$ 的因数时其实只用枚举 $\sqrt k$，对于求出来的所有因数 $x$，再计算一下 $\dfrac{k}{x}$。

时间复杂度可以是 $O(\sqrt{\max\limits_{i=1}^na_i})$。所以作者又改进了一下枚举因数的过程。

### 真正的满分代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
int n,a[maxn],anss,sum=0;
int ans=0x3f3f3f3f;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],sum+=a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        if(i==1){
            for(int j=1;j<=a[i];j++){
                if(a[i]%j==0){//枚举因数（优化版）
                    ans=min(ans,sum-a[2]-a[i]+a[i]/j+a[2]*j);
                    int l=a[i]/j;
                    ans=min(ans,sum-a[2]-a[i]+a[i]/l+a[2]*l);
                }
            }
        }
        else {
            for(int j=1;j*j<=a[i];j++){
                if(a[i]%j==0){//枚举因数（优化版）
                    ans=min(ans,sum-a[1]-a[i]+a[i]/j+a[1]*j);
                    int l=a[i]/j;
                    ans=min(ans,sum-a[1]-a[i]+a[i]/l+a[1]*l);
                }
            }
        }
    }
    cout<<ans;
}
```

---

