# Splitting Items

## 题目描述

Alice 和 Bob 有 $n$ 个数，第 $i$ 个数为 $a_i$，他们决定玩一个游戏取走这些数。

游戏由 Alice 开始取数。

每一次玩家都可以拿走一个剩下的数，直到没有数字可拿走。

定义 $A$ 是 Alice 获取的数字和，$B$ 是 Bob 获取的数字和，游戏总分 $p = A - B$。

Alice 希望最大化 $p$，Bob 希望最小化 $p$，他们都绝顶聪明。

现在 Bob 拥有了修改数的权限，可以把一些数字（可以没有，也可以没有全部）**增加**一个整数值（可以增加不同的值），但是这样 Alice 可能会起疑心，所以总增加的数值必须小于等于 $k$。

请求出 Bob 能达到的 $p$ 的最小值。

## 样例 #1

### 输入

```
4
2 5
1 10
3 0
10 15 12
4 6
3 1 2 4
2 4
6 9```

### 输出

```
4
13
0
0```

# 题解

## 作者：GY程袁浩 (赞：2)

### 思路

考虑他们两个会采取的策略，通过他们的目的可以知道，他们实际上是希望自己拿的物品价值最高，所以是这样拿的 Alice 拿第一大，Bob 拿第二大，Alice 拿第三大......

考虑排序。

由于我们需要增加序列中的任意一些元素，总共增加 $k$ 的值，使 Bob 拿到的尽可能大。所以考虑所有的 $k$ 都给 Bob 拿的物品，即从编号为所有二的倍数的物品。但是！一旦我们通过增加一个物品使得它在物品价值中的排名改变，这个物品就会被 Alice 拿。所以 Bob 的值不能超过 Alice 的值，即将每个编号为二的倍数的物品的价值与编号比它小一的物品价值变为相等。（前提是 $k$ 足够）于是只需要计算出原来未修改之前的分数，答案就是那个分数减去 $k$ 之后与 $0$ 取 $\max$。（代码写的是比较直观，未转化的过程）

### Code
```cpp
#include <bits/stdc++.H>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],n,k,ans,sum;
signed main() {
    int tt;
    cin>>tt;
    while(tt--) {
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+1+n);
        reverse(a+1,a+1+n);
        for(int i=1;i<=n;i+=2) {
            if(i==n) {
                ans+=a[i];
                break;
            }
            sum+=a[i]-a[i+1];
            ans+=a[i]-a[i+1];
        }
        cout<<ans-min(sum,k)<<endl;
        sum=0,ans=0;
    }
    return 0;
}
```

---

## 作者：Stars_Traveller (赞：1)

## CF200C 题解
简单题。
### 分析
因为双方都想要自己取的元素最大，由于 Alice 是先手。所以将数组排序后，Alice 会取走所有编号为奇数的元素，Bob 便只能取偶数个。

那么 Bob 的修改操作怎么用呢？首先，肯定不能在所有情况下都全部用在一个元素当中，这样 Alice 会取走增加的那个元素，Bob 这次操作就亏了。所以我们要在保证增加的总值不大于 $k$ 的情况下尽可能让排序后所有偶数下标元素与它前面的奇数下标元素尽可能相等。

从大到小排序，然后对于每个排序后的偶数下标 $i$，如果 $k \ge a_{i-1} - a_i$，则补齐 $a_{i-1}$ 和 $a_i$ 的差值并从 $k$ 中 扣除，否则将 $k$ 加到当前的元素上，代表 $k$ 已经用完了，直接结束增加。

统计答案就用从大到小排序后所有奇数下标元素的和减去偶数下标元素的和即可。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000005], n, k, t;
bool cmp(int x, int y){return x>y;}
signed main()
{
    for(cin>>t;t;t--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++)cin>>a[i];
        sort(a+1,a+1+n,cmp);
        for(int i=2;i<=n;i+=2)
        {
            if(k>=a[i-1]-a[i])
            {
                k-=a[i-1]-a[i];
                a[i]=a[i-1];
            }
            else
            {
                a[i]+=k;
                break;
            }
        }
        int cnt=0;
        for(int i=1;i<=n;i++)
        {
            if(i&1)
            {
                cnt+=a[i];
            }
            else cnt-=a[i];
        }
        cout<<cnt<<"\n";
    }
}
```

---

## 作者：Redamancy_Lydic (赞：0)

## 题意

两个人玩游戏，轮流从序列 $a$ 中取数字，和大的获胜，所有人都按照最优策略行动。

现在一个人可以增加一些数字的值，需要保证总增加数不超过一个给定的 $k$。问另一个人的分数减去这个人分数的最小值。

## 分析

先从大到小排序，贪心地想如何修改最优。

首先，因为先手是另一个人，所以疯狂改一个数字肯定不优，所以想到平均地修改数字。

在当前序列中，我们找到这个人该选择的所有数字，根据刚才的策略，我们要尽可能不改变原序列中数字的相对大小关系，可以对于每个偶数位置的 $i$，修改 $a_i$ 为 $a_{i-1}$。

为什么这样最优呢？因为这样修改完以后无论再修改哪个数字都一定会使答案更劣，所以这样修改保证了考虑到所有使答案更优的方法。

一点小细节，中途如果 $k$ 不够了，直接给 $a_i$ 赋值为 $a_i+k$ 然后跳出即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int mod=998244353;
const int maxn=1e6+10;
const int inf=1e17;
const double eps=1e-10;
int n,k,a[maxn];
void Main()
{
	n=read(),k=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	sort(a+1,a+n+1);
	reverse(a+1,a+n+1);
	for(int i=2;i<=n;i+=2)
	{
		int delta=a[i-1]-a[i];
		if(delta<=k)
		{
			a[i]=a[i-1];
			k-=delta;
		}
		else
		{
			a[i]+=k;
			break;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i+=2)ans=ans+a[i];
	for(int i=2;i<=n;i+=2)ans=ans-a[i];
	cout<<ans<<endl;
}
signed main()
{
	int T=read();
	while(T--)Main();
	return 0;
}
```

---

## 作者：RaymondOccam (赞：0)

### 题目传送门
[link](http://codeforces.com/problemset/problem/2004/C)

### 题意
爱丽丝和鲍勃有 $n$ 个数，他们决定玩一个游戏，取走这些数。第 $i$ 数字的大小为 $a_i$ 。从爱丽丝开始取数。

在每一回合中，玩家选择一个剩余的数并拿走它。游戏继续，直到没有数剩下。

假设 $A$ 是 Alice 获取的项目的数字总和， $B$ 是 Bob 项目的数字总和。然后游戏的得分将等于 $A-B$ 。

爱丽丝想要最大化分数，而鲍勃想要最小化分数。假设爱丽丝和鲍勃都很聪明，会按照最优策略取数。

但是游戏明天就要开始了，所以今天鲍勃可以稍微修改一下数字。他可以将几个(可能没有或全部)项目的数字 $a_i$ 增加一个整数值(可能是同一个值或每个项目的不同值)。但是，总增加量必须小于或等于 $k$ 。否则，爱丽丝可能会起疑心。请注意，Bob**不能减少**数字大小，只能增加。

鲍勃能达到的最低分数是多少？

### 思路
我们发现，Alice 要想使 $A-B$ 尽量大，则 Alice 会取最大值使得 $A$ 变大，$A-B$ 便会变大；Bob 要想使 $A-B$ 尽量小，则 Bob 会取最大值使得 $B$ 变大，$A-B$ 便会变小。

发现了这一点后，我们可以对 $a$ 进行降序排序，因为 Alice 是第一个取数的玩家，所以 Alice 一定会取数字中的第奇数个；Bob 同理，他一定会取第偶数个，那么我们在降序排序后只需要对数组的第偶数个元素做修改。

注意每次修改的第偶数个数字不能超过它的前一个数，因为这样会打乱排序后的顺序，我们便不能保证这个数一定会被 Bob 取走。

每次对数进行操作时修改 $k$，如果剩下的 $k$ 不够加到前一个数，便让这个数加上剩下的 $k$，将 $k$ 置零即可。

### 代码

```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

ll t;

ll n, k;
ll A, B;
ll a[200005];

ll x;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;

    while (t--)
    {
        cin >> n >> k;

        A = 0, B = 0;

        for (ll i = 1; i <= n; i++)
            cin >> a[i];

        sort(a + 1, a + n + 1, greater<ll>());

        for (ll i = 1; i <= n; i++)
        {
            if (i & 1)
                continue;
            
            x = a[i - 1] - a[i];
            if (k >= x)
                a[i] += x,
                k -= x;
            else
                a[i] += k,
                k = 0;
        }

        for (ll i = 1; i <= n; i++)
            if (i & 1)
                A += a[i];
            else
                B += a[i];
        
        cout << A - B << '\n';
    }
    return 0;
}
```

---

## 作者：Scean_Tong (赞：0)

## CF2004C Splitting Items tijie

### 题意
Alice 和 Bob 取数，Alice 先取，总和为 $A$；Bob 后取，总和为 $B$。Alice 想最最大化 $A-B$，Bob 想最小化 $A-B$，双方都使用最优策略。Bob 可以**增加**一些数，更改总和不超过 $k$，求 Bob 能达到的最低分数。

### 思路
因为 Alice 想最大化 $A-B$，Bob 想最小化 $A-B$，双方都使用最优策略，所以双方一定会取当前的最大值。


那么考虑降序排序，则 Alice 一定会取排序后第奇数个，Bob 一定会取排序后第偶数个。为了使 $A-B$ 尽量小，那么就要让 Bob 取的尽量大，那么显然可以将排序后第偶数个数增加但是不能超过它的前一个数。如果剩余的 $k$ 不能够加到前一个数，就将当前数加 $k$，并标记 $k$ 为零，详见代码。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
const int maxn=2e5+7;
int a[maxn];
bool cmp(int a,int b){
	return a>b;
}
void solve(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	int A=0,B=0;
	for(int i=2;i<=n;i++){
		if(i%2==1)continue;
		if(k>=(a[i-1]-a[i])){
			k-=(a[i-1]-a[i]);
			a[i]=a[i-1];		
		}
		else{
			a[i]+=k;
			k=0;
		}
	}
	for(int i=1;i<=n;i++){
		if(i&1)A+=a[i];
		else B+=a[i];
	}
	cout<<A-B<<'\n';
}

int32_t main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

### 思路

分析题目会发现，无论是 Alice 还是 Bob，他们都希望自己取的数尽量大。因此如果每个数按照从大到小的顺序排列，那么肯定是 Alice 取第 $1$ 个，Bob 取第 $2$ 个，以此类推可以得出，把数列按照从大到小排列后，Alice 会取走所有编号为单数的数，Bob 会取走所有为双数的数。

其次，Bob 既然需要取双数个，那他直接把所有双数个的数全部 $+ k$，他不就取到自己能取到的最大值了吗？并不！如果某个数在 $+k$ 后比前一个数更大，那这个数就会被放到前面，也就可能被 Alice 取到了。因此我们对于每个双数编号的数，需要增加的值为 $k$ 与两数之差之间的最大值。

然后这道题就做出来了。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k,a[200005],cnt;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		sort(a+1,a+n+1,greater<int>());
		cnt=0;
		for(int i=1;i<=n;i++){
			if(i%2) cnt+=a[i];
			else cnt-=min(a[i-1],a[i]+k);
		}
		cout<<cnt<<"\n";
	}
	return 0;
}
```

---

## 作者：Cyx20110930 (赞：0)

# 题意简述

Alice 和 Bob 有 $n$ 个数，他们决定取走这些数。

Alice 开始取，定义 $A$ 是 Alice 获取的数字和，$B$ 是 Bob 获取的数字和，游戏总分 $p=A−B$。

现在 Bob 拥有了修改数的权限，可以把一些数增加一个整数值，但是总增加的数值必须小于等于 $k$。

请求出最优修改，取数策略能达到的 $p$ 的最小值。

# Sol

很明显，在一个修改完的数列后，每人都会选当前最大的数取走。那么 Bob 就是要修改像第二大，第四大的数，尽可能修改为前一个比他大的数，这样可以使这次操作 Alice 得分增加量减小至 $0$。

# Code

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[200005];
bool cmp(int a,int b){
	return a>b;
}
void solve(){
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1,cmp);
	int cnta=0,cntb=0;
	for(int i=2;i<=n;i++){
		if(i&1) continue;
		if(k>=a[i-1]-a[i]){
			k-=a[i-1]-a[i];a[i]=a[i-1];
		}
		else{
			a[i]+=k;k=0;
		}
	}
	for(int i=1;i<=n;i++)
		if(i&1) cnta+=a[i];
		else cntb+=a[i];
	cout<<cnta-cntb<<endl;
}
signed main(){
	int t;cin>>t;
	while(t--)
		solve();
}
```

---

