# Omkar and Circle

## 题目描述

Danny, the local Math Maniac, is fascinated by circles, Omkar's most recent creation. Help him solve this circle problem!

You are given $ n $ nonnegative integers $ a_1, a_2, \dots,       a_n $ arranged in a circle, where $ n $ must be odd (ie. $ n-1 $ is divisible by $ 2 $ ). Formally, for all $ i $ such that $ 2 \leq i \leq n $ , the elements $ a_{i - 1} $ and $ a_i $ are considered to be adjacent, and $ a_n $ and $ a_1 $ are also considered to be adjacent. In one operation, you pick a number on the circle, replace it with the sum of the two elements adjacent to it, and then delete the two adjacent elements from the circle. This is repeated until only one number remains in the circle, which we call the circular value.

Help Danny find the maximum possible circular value after some sequences of operations.

## 说明/提示

For the first test case, here's how a circular value of $ 17 $ is obtained:

Pick the number at index $ 3 $ . The sum of adjacent elements equals $ 17 $ . Delete $ 7 $ and $ 10 $ from the circle and replace $ 2 $ with $ 17 $ .

Note that the answer may not fit in a $ 32 $ -bit integer.

## 样例 #1

### 输入

```
3
7 10 2```

### 输出

```
17```

## 样例 #2

### 输入

```
1
4```

### 输出

```
4```

# 题解

## 作者：thostever (赞：6)

题目中的操作可以理解为删除一个数，然后将它两边的数相加，合并为一个数。

首先我们拆环为链。

我们来引入一个结论：对于两个位置 $i$ 和 $j$，它们两个能够（通过若干步）合并到一起，当且仅当 $i\equiv j(\mod 2)$，即 $i$ 与 $j$ 奇偶性相同。
这个很好理解，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/uedkq10n.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们进行一次操作，**未删除的数 位置的奇偶性不会发生变化。** 所以我们只能将位置的奇偶性相同的数相加。

由于 $a_i\geq 0$，所以我们一定会贪心的将所有能取的数都取了。即取所有奇数位上的数或偶数位上的数。

这不就做完了吗ヾ(@^▽^@)ノ

我们只需要枚举拆环为链的断点，预处理一下，直接算所有奇数位上数的和就好了。（偶数位不用算是因为在后续枚举断点的过程中会被枚举到。）

~~代码瞎搞就行了~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int a[200010];
int l[200010],r[200010];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(n==1)
	{
		cout<<a[1]<<"\n";
		return 0;
	}
	l[1]=a[1]; l[2]=a[2];
	for(int i=3;i<=n;i++) l[i]=l[i-2]+a[i];
	r[n]=a[n]; r[n-1]=a[n-1];
	for(int i=n-2;i;i--) r[i]=r[i+2]+a[i];
	int ans=r[1];
	for(int i=2;i<=n;i++) ans=max(ans,r[i]+l[i-1]);
	cout<<ans<<"\n";
}
/*

*/
```


---

## 作者：cosmicAC (赞：2)

题意：有一个$n$个元素的环$a$，一次操作可以把子串$\{a_x,a_{x+1},a_{x+2}\}$变成$\{a_x+a_{x+2}\}$。要求最后剩下的元素最大。

---

首先我想到了一个贪心，使用堆维护，每次把最小的删了，变成旁边两个的和。结果就假了，WA on pretest 5。然后我对拍了一下，Hack数据：
```plain
5
9 4 2 3 7 
```

这样我就会首先贪$2$,变成$\{9,7,7\}$，然后贪$7$，变成$\{16\}$。然而最优解会先选$3$，变成$\{9,4,9\}$，然后选$4$，变成$\{18\}$。思考一下，可以发现错误的根本在于选了$2$之后，**其相邻的数就不能选了**，只能舍近求远去选$7$。所以这个贪心是假的。

试图修锅，我发现选择一个数之后，相邻的数就不能再被选到，并且其他数的选择仍然是自由的。答案就是所有元素之和扣除掉选择的数的贡献。这样子就可以把原题面转化成下面的问题:

> 有一个$n$个元素的环$a$，要求从中选出$k$个不相邻的元素，使其总和最小。

其中的$k=\dfrac{n-1}2$。不难写出一个$O(n^2)$的DP，$f_{i,j,0/1,0/1}$表示破环成链之后，前$i$个元素中选了$j$个，第一个元素选了/没选，第$i$个元素选了/没选的最优解。答案就是$\max{\{f_{n,k,0,0},f_{n,k,1,0},f_{n,k,0,1}\}}$。

考虑优化这个DP。可以发现$f_{i,j,x,y}-f_{i,j-1,x,y}\le f_{i,j+1,x,y}-f_{i,j,x,y}$，所以直接上带权二分，让每选择一个元素都要附加$w$的贡献。

有一个代码细节：这里的$w$的下界不能只开到$-10^9-10$这种级别的数，否则会WA on pretest 6。我也不知道这是为什么（感觉上够了啊?）但是把下界开更小一点就AC了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n;ll a[1<<18],tot;
struct st{ll f;int c;}f[1<<18][2][2];
bool operator<(st a,st b){return a.f<b.f || a.f==b.f && a.c<b.c;}
st chk(ll w){
	for(int i=1;i<=n;i++)
		f[i][0][0].f=f[i][0][1].f=f[i][1][0].f=f[i][1][1].f=4e18;
	f[1][0][0]={0,0},f[1][1][1]={a[1]+w,1};
	for(int i=2;i<=n;i++)for(int j:{0,1}){
		f[i][j][0]=min(f[i-1][j][0],f[i-1][j][1]);
		f[i][j][1]={f[i-1][j][0].f+a[i]+w,f[i-1][j][0].c+1};
	}
	return min({f[n][1][0],f[n][0][0],f[n][0][1]});
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",a+i),tot+=a[i];
	ll l=-2e12-10,r=10,mid;
	while(l<r){
		mid=l+r>>1;
		if(chk(mid).c>(n-1)/2)l=mid+1;else r=mid;
	}
	st x=chk(l);
	printf("%lld\n",tot-(x.f-x.c*l));
	return 0;
}
```

---

## 作者：123zbk (赞：1)

题目的意思是每次可以在环上将序列 $\{a_i,a_{i+1},a_{i+2}\}$ 变成 $a_i+a_{i+2}$，求最后剩一个数的最大值。

首先想在链上怎么做。

对于每次操作，相当于是减少了两个数字，也就是从一开始每个数字在链上的奇偶性是不变的。只有两个奇偶性相同的数字才可以合并成它们的和。

但是如何才能让最后剩的数最大呢？

比如这组数：$1,2,3,4,5,6,7,8,9$。

第一步，让 $1$ 和 $3$ 相加：$4,4,5,6,7,8,9$。

第二步，让 $7$ 和 $9$ 相加：$4,4,5,6,16$。

第三步：让 $4$ 和 $5$ 相加：$9,6,16$。

最后一步：让 $9$ 和 $16$ 相加：$25$。

我们发现，最后的答案其实是由 $1+3+5+7+9$ 得来的，也就是每个奇数位置的值相加。

也就是说，我们通过贪心一定可以构造出一种方案，使最后的答案是所有奇数位置或偶数位置的数相加。而只有两个奇偶性相同的数字才可以合并，所以这一定能使最后的答案最大。

先倍长一遍数组，再每次枚举破环成链的断点，更新最大值即可。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=4e5+10;
int n,a[maxn],sum[maxn],ans,num;
signed main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
	{
        scanf("%lld",&a[i]);
        num+=a[i];
        a[i+n]=a[i];//倍长
    }
    for(int i=1;i<=2*n;i++)
	{
        if(i&1)
		{
            sum[i]=sum[i-1]+a[i];
        }
        else
		{
            sum[i]=sum[i-1];//奇数位置的前缀和
        }
    }
//    for(int i=1;i<=2*n;i++)
//    {
//    	cout<<sum[i]<<" ";
//	}
    for(int i=n+1;i<=2*n;i++)//枚举断点
	{
        ans=max({ans,sum[i]-sum[i-n],num-(sum[i]-sum[i-n])});//奇数和偶数取max
        //cout<<ans<<" ";
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1372D Omkar and Circle(*2100)](https://www.luogu.com.cn/problem/CF1372D)

# 解题思路

发现问题等价于在环上砍一刀形成一个序列然后取其中不相邻的数字使得和最大。

如果这是一个序列，我们只需要取奇数位上的数字和和偶数位上的数字和的最大值即可。

我们发现你砍掉一刀等价于把后缀拿到最前面来。

于是我们可以直接前后缀和维护一下然后枚举断点即可。

时间复杂度 $O(n)$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
ll _t_;
void _clear(){}
ll n;
ll a[200010],b[200010],ans;
ll pre[200010],suf[200010];
void solve()
{
    _clear();
	cin>>n;
	forl(i,1,n)
		cin>>a[i];
	if(n==1)
	{
		cout<<a[1]<<endl;
		return ;
	}
	pre[1]=a[1];
	forl(i,2,n)
		pre[i]=pre[i-2]+a[i];
	forr(i,n,2)
		suf[i]=suf[i+2]+a[i];
	Max(ans,max(pre[n],pre[n-1]));
	forl(i,1,n)
		Max(ans,pre[i]+suf[i+1+((i%2)==(n-i)%2)]);
	cout<<ans<<endl; 
}
int main()
{
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
    IOS;
    _t_=1;
  //  cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：happybob (赞：0)

来介绍一个新做法。

先破环为链。

注意到问题等价于，在 $n$ 个点的环上选 $\lfloor \dfrac{n}{2} \rfloor$ 个点，使得这些点两两之间不相邻，最小化点权和。

你要是直接想什么 $f_{i,j,0/1}$ 表示前 $i$ 个选了 $j$ 个，$i$ 是否被选了的 DP，就没有任何前途了，因为你基本没法优化。

但是你注意到你要选的是 $\lfloor \dfrac{n}{2} \rfloor$ 个点，且题目中保证 $n$ 是奇数，不妨枚举某个点不选，接着就是在剩下 $n-1$ 个中，每两个中恰好选一个，就可以直接  DP 了，状态为 $f_{i,0/1}$ 表示第 $i$ 组选的是第一个或第二个，前面 $i$ 组的答案。

这样就是 $O(n^2)$ 的复杂度。但是容易发现，我们随机 $c$ 次，每次在 $[1,n]$ 中均匀随机一个不选的位置，$c$ 次都没求出答案的概率大概为 $\dfrac{1}{2^c}$，然后你只需要取 $c=60$ 左右即可通过，事实上取小一点应该也可以。

---

