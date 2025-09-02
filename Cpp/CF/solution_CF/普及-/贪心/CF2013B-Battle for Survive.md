# Battle for Survive

## 题目描述

Eralim（原文人名）作为 mafia（原文组织名）老大，管理着 $n$ 名战士。第 $i$ 名战士的评分为 $a_i$。

Eralim 安排了一场 $n-1$ 场战斗的锦标赛，每场战斗中都会选择两名尚未被淘汰的战士 $i$ 和 $j$（其中 $1 \le i < j \le n$），而战斗的结果是战士 $i$ 被淘汰出比赛，战士 $j$ 的评分会减去战士 $i$ 的评分相同。也就是说，$a_j$ 会减去 $a_i$。请注意，战士 $j$ 的评分可能会变为负数。战士们的编号不会改变。

Eralim 想知道，如果他最优地选择战斗，最后剩下的那名战士最多能保持多少评分。

## 说明/提示

在第一个例子中，你可以安排编号为 $1$ 和 $2$ 的战士之间的比赛，其中编号为 $2$ 的战士会获胜。最后一个战士的评分，即编号为 $2$ 的战士，将是 $1-2=-1$。

在第二个例子中，你可以先让编号为 $1$ 和 $2$ 的战士进行比赛，其中编号为 $2$ 的战士会获胜，然后让编号为 $2$ 和 $3$ 的战士进行比赛，其中编号为 $3$ 的战士会获胜。

在第一场比赛后，编号为 $2$ 的战士的评分将是 $2-2=0$。在第二场比赛后，编号为 $3$ 的战士的评分将是 $8-0=8$。

翻译者：[jiangyunuo](https://www.luogu.com.cn/user/1061050)。

## 样例 #1

### 输入

```
5
2
2 1
3
2 2 8
4
1 2 4 3
5
1 2 3 4 5
5
3 2 4 5 4```

### 输出

```
-1
8
2
7
8```

# 题解

## 作者：wangzhaohan2910 (赞：3)

## 思路

通过手推样例，可以发现 $a_{n-1}$ 永远在结果中是负的。于是我们发现存在让别的数都是正的，$a_{n-1}$ 是负的的符合题意的方法，是让 $a_{n-1}$ 依次减去 $a_1$ 到 $a_{n-2}$，再让 $a_n$ 减 $a_{n-1}$。

简化，可得：

$$\displaystyle\left(\sum_{i=1}^{n-2}a_i\right)-a_{n-1}+a_n$$

## 代码

不要忘开 `long long`！

不要忘记 `#define int long long` 后要用 `signed main`！

```cpp
#include<bits/stdc++.h>
#define int long long // 忘开long long见祖宗 
using namespace std;
signed main() // long long int main见祖宗 
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,s{};
		cin>>n;
		for(int i{1};i<=n;i++)
		{
			int x;
			cin>>x;
			if(i==n-1)
				s-=x;
			else
				s+=x;
		}
		cout<<s<<endl;
	}
	return 0;
}
```

---

## 作者：zlqwq (赞：2)

## 思路：

我们手玩几组样例，不难发现，留到最后数一定是 $a_n$。

从 $a_{n-2}$ 一直删除到 $a_1$，然后让 $a_n$ 删掉 $a_{n-1}$，即可得到答案。


```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,sum;
void solve() {
	int ans=0;
	for(int i=1;i<=n;++i){
		int x;
		cin>>x;
		if(x!=n-1) ans+=x;
		else ans-=x;
	}
	cout<<ans<<'\n';
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		solve();
	}
	return 0; 
}
```

---

## 作者：yangxikun (赞：1)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF2013B) [CF](https://codeforces.com/problemset/problem/2013/B)

### 题目大意

多测。

有 $n$ 个人，每个人有一个 Rating，第 $i$ 个人的 Rating 是 $a_i$。

你可以安排 $n-1$ 次决斗，每次选择两个还在场的 $i$ 和 $j$（$1\le i<j\le n$），让他们战斗。在这次战斗后，第 $i$ 个人会被淘汰出局，第 $j$ 个人的 Rating 也会变成 $a_j-a_i$。

你希望最后留下来的人最终 Rating 尽量高，求最后留下的人的 Rating。

**注意 Rating 可以变成负数。**

### 解法

由于每次选择的 $i$ 必须小于 $j$，所以可以得出最后剩下的肯定是第 $n$ 个人。那我们可以让第 $n-1$ 个人和前面所有人都打一架，让他变得很“虚弱”，最后让第 $n$ 个人坐收渔翁之利。

注意这题需要使用 `long long`。

### 代码

[CF 提交记录](https://codeforces.com/contest/2013/submission/284727060)

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[200005];
void solve(){
	ll n;
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<n-2;i++)a[n-2]-=a[i];
	cout<<a[n-1]-a[n-2]<<endl;
}
int main(){
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：lw393 (赞：1)

这道题需要注意的是一个限制条件，当 $i < j$ 时，战士 $i$ 与战士 $j$ 的战斗只能是战士 $j$ 赢。

于是就可以通过贪心，将战士 $n - 1$ 的等级去依次减去战士$1, 2, \cdots, n-2$ 的等级，再让战士 $n$ 与战士 $n - 1$ 战斗就好了，可以证明这是最大的答案。

于是 $\operatorname{ans} = \sum_{i=1}^n{a} - 2 \times a_{n - 1}$。

给出代码


```cpp
#include<iostream>
using namespace std;
const int N = 2e5 + 5;
#define int long long

int a[N];

void solve(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int sum = 0;
    for(int i = 1; i <= n; i++) sum += a[i];
    cout << sum - 2 * a[n - 1] << '\n';
}

signed main(){
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

```

---

## 作者：jiangyunuo (赞：0)

### 题目大意：
很简单，有 $n$ 个战士，第 $i$ 个战士的评分为 $a_i$，我们要开启一场锦标赛，每轮都会选两个未淘汰的战士：战士 $i$ 和战士 $j$（$1 \le i < j \le n$）。我们会让他们战斗，战士 $i$ 将会被淘汰，战士 $j$ 的评分将会减去战士 $i$ 的评分。问：如果最后剩下的战士选择战斗的最佳策略，他最多能保持多少评价？
### 大体思路：
显然，因为 $1 \le i < j \le n$，所以最后的战士一定是战士 $n$，战士 $n$ 要想保持最高的评分，应当先让其他战士先打，最好的方式就是让战士 $n-1$ 先和其他战士各打一场（否则战士 $n-1$ 的评分就不能最低，如果让战士 $n-1$ 的评分减去除战士 $n$ 以外的其他战士的评分，那么战士 $n-1$ 的评分就是最低的情况），最后战士 $n$ 和战士 $n-1$ 打一场，即可。  
化成算式就是 $a_n - a_{n-1} + a_{n-2} + \dots + a_1$。  
### 代码：
```cpp
#include<bits/stdc++.h>  
using namespace std;  
int main(){
    int t;
    cin>>t;  
    int n,a;
    long long ans;
    for(int i=1;i<=t;i++){
        cin>>n;
        ans=0;
        for(int j=1;j<=n;j++){   //计算答案。
            cin>>a;
            if(j==n-1)ans-=a;
            else ans+=a;
        }
        cout<<ans<<endl;
    }
    return 0;  
}
```

---

## 作者：fanjiayu666 (赞：0)

### 题目传送门
luogu: [link](https://www.luogu.com.cn/problem/CF2013B) || CF: [link](https://codeforces.com/problemset/problem/2013/B) || VJ: [link](https://vjudge.net/problem/CodeForces-2013B)
### 题意简述
Eralim 是黑手党的老大，管理着一群战士。战士 $i$
 的等级为 $a_i$。

Eralim 安排了一场由 $n−1$ 场战斗组成的锦标赛，每场比赛将选出两名尚未被淘汰的战士 $i$ 和 $j$（$1≤i<j≤n$），这场比赛里，战士 $i$ 将被淘汰出局，战士 $j$ 的评级将被战士 $i$ 的评级所降低。即 $a_j$ 减去 $a_i$。注意，士 $j$ 的评级可能变为负值。战士的索引没有变化。

Eralim 想知道如果他选择最优的战斗，最后剩下的战士能保持多大的最大等级。

### 方法概括

首先，我们可以注意到，不管如何选择，最后剩下的一定是第 $n$ 个战士为什么呢，我们以第 $2$ 个样例为例：
$$2,2,8$$
先让第 $1$ 个战士与第 $2$ 个战斗，第一个战士淘汰，第二个战士的武力值变为 $0$。情形如下：
$$0,8$$
再让剩余两个战士开打，第 $2$ 个战士淘汰，第 $3$ 个战士的武力值变为 $8$。

------

经过如上推理，发现最后剩余的一定是第 $n$ 个战士。（其余方法不再赘述）

所以只要从后往前枚举，保证第 $n-1$ 个战士剩余的武力值最小即可。（注意从后往前枚举时最小的跑到第一个位置）

------

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		long long n,a[200010]={0};
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=n-2;i>=1;i--){
			a[i]=a[i+1]-a[i];
		}
		cout<<a[n]-a[1]<<endl;
	}
} 
```
(勿抄)

---

## 作者：jubaoyi2011 (赞：0)

## 思路

首先假设 $a_n$ 留到最后，那么我们只需要让 $a_{n-1}$ 干掉从 $a_1$ 到 $a_{n-2}$ 的所有人，再让 $a_n$ 干掉 $a_{n-1}$ 即可。最终可以得到结果为 $a_n - a_{n-1} - a_{n-2} - \dots - a_3 - a_2 - a_1$ 

（~~这结论真的配得上黄题吗？~~）

---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2013B)

~~一道大 water 题，赶紧过来水一发题解。~~

### 题目大意
有一个长度为 $n$ 的数组 $a$，有 $n-1$ 次操作，对于每一次操作，选取两个元素 $i,j$，将 $a_j$ 变为 $a_j-a_i$，然后删除元素 $i$。请问最后剩下的元素值最大是多少？

### 解题思路

容易发现最后留下来的那个数永远是 $a_n$。所以我们要尽量让 $a_{n-1}$ 越小越好。所以我们就可以从 $a_{n-1}$ 中减去 $a_1,a_2,\cdots,a_{n-2}$，最后从 $a_n$ 中减去 $a_{n-1}$ 即可。最终得到的答案即为 $(\sum_{i=1}^n a_i)-a_{n-1} \times 2$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,sum;
int main(){
	cin>>T;
	while(T--){
		sum=0;
		cin>>n;
		for(int i=1,x;i<=n;i++){
			cin>>x;
			if(i==n-1) sum-=x;
			else sum+=x;
		}
		cout<<sum<<endl;
	}
}
```

---

## 作者：Defy_HeavenS (赞：0)

### 题意

简单说下题意：每次把在后面的一个数的权值减去在前面的一个数的权值后把前面那个数（及其权值）删掉，问最后剩下的数的权值最多是多少。

### 思路

最后剩下的一定是最后一个数，我们要使最后一个数最大。首先因为任何数都大于 $0$，所以任何一个原始的权值减到最后一个数上都是不优秀的，所以要减到另一个数上，哪一个数呢？似乎只有倒数第二个数能接受前面所有的数（若不是倒数第二个数，那么那个数就无法被倒数第二个数减），所以我们把前面所有数都减到倒数第二个数上，最后在把最后一个数减去倒数第二个数。

$$
a[n]-(a[n-1]-(\sum_{i=1}^n a[i]-a[n]-a[n-1]))
$$

化简后就是

$$
\sum_{i=1}^n a[i]-2\times a[i-1]
$$

还有另外一种理解方式：除了倒数第二个数的所有数的和再减去倒数第二个数。

### 代码

```cpp
#include<bits/stdc++.h>
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define pb push_back

using namespace std;
typedef long long LL;
typedef pair<int,int> PII;

const int N=2e5+5;
LL n,a[N];

void solve(){
	cin>>n;
	LL sum=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	cout<<sum-2*a[n-1]<<"\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t=1;cin>>t;
	while(t--) solve();
	return 0;
}
/*

*/
```

---

## 作者：cqbzhzf (赞：0)

### 思路
- 当 $n=2$ 时，$ans=a_2-a_1$。
- 当 $n=3$ 时，$ans=a_3-a_2=a_3-(a_2-a_1)=a_3-a_2+a_1$。
  
所以，推广至全局，$ans=a_n-a_{n-1}=a_n-(a_{n-1}-a_{n-2})=a_n-a_{n-1}+a_{n-2}=\cdots=a_n-a_{n-1}+\sum_{i=2}^{n}a_i=a_n-a_{n-1}+(\sum_{i=1}^{n}a_i-a_n-a_{n-1})=\sum_{i=1}^{n}a_i-2 \times a_{n-1}$。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long//注意
using namespace std;
const int N=2e5+5;
int t,n,a[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		int sum=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i],sum+=a[i];
		cout<<sum-a[n-1]*2<<"\n";
	}
	return 0;
}
```

---

## 作者：furina_yyds (赞：0)

写完翻译，又看到可以写题解，过来水一篇。
### 思路
易得 $a_n$ 是最后活下来的那个，因此，我们可以断定其他人必然会被打死，故我们要想办法让 $a_{n-1}$ 的等级最小，根据题意，所有等级均为正数，故我们让让 $a_{n-1}$ 打死其他人就好了。~~这题不配当黄题~~

这样，最后的总和就是 $a_1 + a_2 + \ldots + a_{n-2} - a_{n-1} + a_n$。

```cpp
#include<cstdio>
using namespace std;
int T;
const int MR = 2e5 + 5;
int main(){
    scanf("%d", &T);
    for(int csp_rp = 1, n, a[MR]; csp_rp <= t; csp_rp++){
        scanf("%d", &n);
        long long cnt = 0;
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
            cnt += a[i];
        }
        printf("%d\n", cnt - a[n - 1] * 2);
    }
    return 0;
}
```
~~凭什么CF到现在都不能交！！！~~

---

## 作者：NEKO_Daze (赞：0)

[洛谷CF2013B](https://www.luogu.com.cn/problem/CF2013B) || [CodeForces 2013 B](https://codeforces.com/contest/2013/problem/B)

### 简要题意
有一个长度为 $n$ 的数组 $a$，要进行 $n-1$ 次操作，每次选取两个元素 $i,j(1\le i<j\le n)$，使 $a_j$ 减少 $a_i$，然后删除元素 $i$。请问怎样操作才能使最后剩下的元素值最大？

### 思路
观察可知 $a_{n-1}$ 的值在最终结果中总是负数，因此，我们可以从 $a_{n-1}$ 中减去总和 $a_1 + a_2 + \ldots + a_{n-2}$，再从 $a_n$ 中减去 $a_{n-1}$。然后从 $a_n$ 减去 $a_{n-1}$。

这样，最后的总和就是 $a_1 + a_2 + \ldots + a_{n-2} - a_{n-1} + a_n$。由于 $a_{n-1}$ 总是负数，所以不能超过这个值，这就是最大的答案。

[记录](https://codeforces.com/contest/2013/submission/284014518)

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200005];
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        long long sum = 0;
        for (int i = 1; i <= n; i++) {cin >> a[i]; sum += a[i];}
        cout << sum - a[n-1]*2 << endl;
    }
}
```

---

## 作者：RaymondOccam (赞：0)

### 题意
Eralim 管理着 $n$ 个战士。战士 $i$ 的等级为 $a_i$ 。

Eralim 安排了一场由 $n - 1$ 场战斗组成的比赛，其中每场比赛选择两名尚未淘汰的战士 $i$ 和 $j$，战士 $i$ 被淘汰，而战士 $j$ 的等级将会减少战士 $i$ 的等级，战士 $j$ 的等级可以变为负数。

Eralim 想知道如果他按照最优情况选择战士，最后剩下的战士最大等级是多少。

### 思路
考虑让所有人与 $a_{n-1}$ 打，那么让 $a_{n-1}$ 变为尽可能小的数，再用 $a_n-a_{n-1}$ 便可以让 $a_n$ 胜利，同时减去 $a_{n-1}$，可以让 $a_n$ 的值最优化（当 $a_{n-1}$ 为负数，$a_n$ 将会变得比原来还大）。

分析一下，要想保持最优，一定是一个大值减去一个小值，那么就要使得这个小值尽可能的小，大值尽可能的大。而且被淘汰的人的索引不可能大于或等于被晋级的人。所以只能让 $a_{n-1}$ 减去 $a_1,a_2,\ldots,a_{n-2}$ 的等级，再用 $a_n-a_{n-1}$，所以这种情况是最优的，结果为

$$
  a_{n}-\sum_{i=1}^{n-1} a_i
$$

考虑为什么不能用 $a_{n-2}$ 变成尽可能小的值，因为在剩下的 $a_{n-2},a_{n-1},a_n$ 三个人当中，只能保留 $a_{n}$。因为想要选择保留 $a_{n-1}$ 时，只能使用 $a_{n}-a_{n-2}$，之后 $a_{n-1}$ 和 $a_{n}$ 只能选择索引较大的 $a_{n}$ 保留。那么 $a_{n-1}$ 就会比较大，$a_n-a_{n-1}$ 的情况完全差于前一种情况。所以剩下奇数个人的情况是不可行的。

再来考虑一下剩下偶数个战士的情况。就拿剩下 $a_{n-3},a_{n-2},\ldots,a_n$ 的情况举例，不难发现 $a_{n-3}$ 淘汰 $a_1,a_2,\ldots,a_{n-4}$ 的战士后，$a_{n-3}$ 的情况就是负数。之后 $a_{n-2}$ 变为正数，$a_{n-3}$ 变为小值，正负性质不能确定，取决于 $a_{n-2}$ 与 $a_{n-3}$ 的大小关系。最优情况下，最终结果为

$$
  a_{n}-\sum_{i=1}^{n-4} a_i-a_{n-3}-a_{n-2}-a_{n-1}
$$

套上括号，减号变号：

$$
  a_{n}-(\sum_{i=1}^{n-4} a_i+a_{n-3}+a_{n-2}+a_{n-1})
$$

化简得到：

$$
  a_{n}-\sum_{i=1}^{n-1} a_i
$$

发现这种情况的结果完全等于用 $a_{n-1}$ 淘汰所有人，再用 $a_n$ 淘汰 $a_{n-1}$ 的结果，所以剩下偶数个人的情况是等于剩下 $2$ 个人的情况。

因此知道，对于任意一个 $k(k\le n-1)$，让 $a_k$ 淘汰 $a_1,a_2,\ldots,a_{k-1}$，再用 $a_{k+1},a_{k+2},\ldots,a_{n-1}$ 依次淘汰前一名战士，再用 $a_n$ 淘汰 $a_{n-1}$，其结果为

$$
  a_n-\sum_{i-1}^{k-1} a_i-a_k-\sum_{i=k+1}^{n-1} a_i
$$

化简得到

$$
  a_n-\sum_{i-1}^{n-1} a_i
$$

所以得出结论，在任何情况下，最优情况就是让 $a_{n-1}$ 淘汰所有能够淘汰的人（也就是说淘汰索引比自己小的人），之后让 $a_n$ 淘汰 $a_{n-1}$。

所以只需求出 $a_{n}-\sum_{i=1}^{n-1} a_i$ 即可。

### 代码

```cpp
#include <iostream>
#define ll long long
using namespace std;

ll t;

ll n;
ll x, ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;

    while (t--)
    {
        cin >> n;

        ans = 0;

        for (ll i = 1; i <= n; i++)
        {
            cin >> x;
            ans += x;

            if (i == n - 1)
                ans -= x * 2; // 前面多加了一个 x，所以减去 x * 2;
        }

        cout << ans << '\n';
    }
    return 0;
}
```

---

