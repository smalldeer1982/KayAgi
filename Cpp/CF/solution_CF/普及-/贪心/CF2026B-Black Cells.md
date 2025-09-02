# Black Cells

## 题目描述

You are given a strip divided into cells, numbered from left to right from $ 0 $ to $ 10^{18} $ . Initially, all cells are white.

You can perform the following operation: choose two white cells $ i $ and $ j $ , such that $ i \ne j $ and $ |i - j| \le k $ , and paint them black.

A list $ a $ is given. All cells from this list must be painted black. Additionally, at most one cell that is not in this list can also be painted black. Your task is to determine the minimum value of $ k $ for which this is possible.

## 说明/提示

In the first example, with $ k=1 $ , it is possible to paint the cells $ (1, 2) $ .

In the second example, with $ k=1 $ , it is possible to paint the cells $ (7, 8) $ .

In the third example, with $ k=2 $ , it is possible to paint the cells $ (2, 4) $ and $ (8, 9) $ .

In the fourth example, with $ k=3 $ , it is possible to paint the cells $ (0, 1) $ , $ (5, 8) $ and $ (10, 13) $ .

## 样例 #1

### 输入

```
4
2
1 2
1
7
3
2 4 9
5
1 5 8 10 13```

### 输出

```
1
1
2
3```

# 题解

## 作者：Yxy7952 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF2026B)

先给出[AC记录](https://codeforces.com/problemset/status?my=on)。
## 题目大意

输入一个有 $n$ 个数的单调递增的序列 $a$，请求出相邻两数之间差的最大值，已经求完差的数不能再使用。

在任意位置 $i$ 你可以使用一个魔法（仅能使用 $1$ 次），这个魔法能创造一个数 $a_{i}+1$ 使 $a_{i}$ 和 $a_{i}+1$ 做差（这样的作用是使有一个差为 $1$）。
## 思路
一道简单贪心题。

显然，为了使两数之间差最小，肯定能使用魔法就使用，但一定注意只有 $n$ 为奇数时才能使用（其实这时一定会使用，不管是题目要求还是答案最优的情况）。因为如果 $n$ 为偶数时，则序列中的数刚好两两配对。

又因为数据范围过小，支持 $O(TN^2)$ 的时间复杂度，所以直接枚举在哪个位置使用魔法。

直接看代码。
## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll T,n,a[2005];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		ll ans;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(n%2){//n 为奇数。
			ans=1e18;//答案初始定义最大值。
			for(int i=1;i<=n;i++){//枚举在 i 处使用魔法。
				ll s=1;//使用魔法后差最小为 1。
				for(int j=1;j<i;j+=2) s=max(s,a[j+1]-a[j]);
				for(int j=i+1;j<=n;j+=2) s=max(s,a[j+1]-a[j]);
                //跳过 i 计算差值
				ans=min(ans,s);//求最大差中的最小值。
			}
		}
		else{
			ans=1;
			for(int i=1;i<=n;i+=2) ans=max(ans,a[i+1]-a[i]);
            //n 为偶数则直接计算最大差
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Goodans (赞：3)

# 解题思路
## 基本观察：

要使 $k$ 较小，我们只能涂染那些距离比较近的单元格。要求每两个单元格之间的距离不超过 $k$，求 $k$ 的最小值。
## 策略：

计算最小的 $k$：遍历 $a$ 中的值，计算每两个相邻单元格的间隔。

# 代码：
```python
import sys
INF = 10**18


def solve():
    n = int(input())
    a = list(map(int, input().split()))
    if n == 1:
        print(1) #因为n==1时，只有一个数据，直接输出。
    elif n % 2 == 1:
        ans = INF
        for i in range(1, n + 1, 2):
            mx = 0
            for j in range(1, i, 2):
                mxx = max(mxx, a[j] - a[j - 1])
            for j in range(i + 1, n, 2):
                mxx = max(mxx, a[j] - a[j - 1])
            ans = min(ans, mxx)

        print(max(1, ans))
    else:
        mxx = 0
        for i in range(1, n, 2):
            mxx = max(mxx, a[i] - a[i - 1])
        print(mxx)


def main():
    T = int(input())
    for _ in range(T):
        solve()


if __name__ == "__main__":
    main()

```

---

## 作者：zsq9 (赞：2)

[AC 记录](https://codeforces.com/problemset/submission/2026/296521449)

[传送门](https://www.luogu.com.cn/problem/CF2026B)

## 思路

二分答案在这个编号范围内找到最小的 $k$ 的值，所以只要暴力判断是否满足条件，满足就记录下来，二分有 $\log n$ 次每一次是 $n^2$ 一共是 $\log n\times n^2$（精确就有 $60\times 2000\times 2000$）刚好两秒。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[10005],minn=1e18;
bool u[10005];
bool check(long long k){
	memset(u,0,sizeof(u));
	long long ans=0;
	for(int i = 1 ; i <= n ; i++){
		for(int j = i+1 ; j <= n ; j++){
			if(u[i]==0&&u[j]==0&&abs(a[j]-a[i])<=k){//如果没被染过就染上 
				u[i]=1,u[j]=1;//打上标记 
				ans+=2;
			}
			
		}
	}
	if(n-ans<=minn){
		minn=n-ans;
		return 1;//最后判断有没有差值小于最小值满不满足
	}else {
		return 0;	
	}
}
int main(){
	cin>>t;
	while(t--){
		long long ans=0;
		minn=1e18;
		cin>>n;
		for(int i = 1 ; i <= n ; i++){
			cin>>a[i];
		}
		long long l=1,r=1e18;
		while(l<r){//二分
			long long mid=(r-l)/2+l;
			if(check(mid)){
				r=mid;
			}else{
				l=mid+1;
			}
		}
		cout<<l<<"\n";
		/*这样二分也行 
		long long l=1,r=1e18,ans=0; 
			while(l<=r){
				mid=(r-l)/2+l;
				if(check(mid,n)){
					ans=mid;
					r=mid-1;
				}else l=mid+1;
			}
			cout<<ans<<"\n";
		*/
	}
	return 0;
}
```

---

## 作者：Ybll_ (赞：2)

[AC 记录](https://cdn.luogu.com.cn/upload/image_hosting/50jluu88.png)
# 题意：
一个列表 $a$ 中有 $n$ 个数，这些数最初**全是**白色，要**全部**染黑，每次选择两个**白色**的数 $a_i$ 和 $a_j$，且 $|a_i-a_j|\le k$，然后将这两个数染黑，此外，还可以将**至多一个**不在此列表中的单元格涂成黑色。
# 思路：
**二分答案**，题目已经给了二分的**区间** $[1,10^{18}-1]$，每次判断这个答案**是否合法**时直接**暴力**遍历一遍。
# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100005];
int init()
{
	int sum;
	cin>>sum;
	for(int i=0;i<sum;i++)
	{
		cin>>a[i];
	}
	return sum;
}
bool check(int k,int n)
{
	int cnt=0;
	bool vis[100005]={0};
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(vis[i]||vis[j])continue;
			if(abs(a[j]-a[i])<=k)
			{
				vis[j]=vis[i]=1;
				cnt+=2;
			}
		}
	}
	return (n-cnt<2?1:0);
}
void solve()
{
	int n=init(),l=1,r=1e18,mid,ans;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid,n))
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	cout<<ans<<"\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：QAQ2012 (赞：1)

[题目跳楼机](https://www.luogu.com.cn/problem/CF2026B)

## 思路

这道题从 $k$ 能看出，二分答案能在这个编号范围内找到最小的 $k$ 的值，类似于二分查找，最后判断是否合理，有没有差值大于他的，所以使用二分答案。


```
#include<bits/stdc++.h>

using namespace std;
//警示后人，必须要开long long
long long t,n,a[10005],used[10005]={0};
bool check(long long k){
	memset(used,0,sizeof(used));
	int ans=0;
	for(int i = 1 ; i <= n ; i++){
		for(int j = i+1 ; j <= n ; j++){
			if(!used[i]&&!used[j]&&abs(a[j]-a[i])<=k){//判断是否能一起染色
				used[i]=1;
				used[j]=1;
				ans+=2;
			}
			
		}
	}
	if(n-ans<=1){//判断是否剩一个点或者更少
		return true;
	}
	else{
		return false;
	}
}
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		long long maxs=0;
		for(int i = 1 ; i <= n ; i++){
			cin>>a[i];
		}
		long long l=1,r=1e18;
		while(l<r){//二分查找k
			long long mid=(l+r)/2;
			if(check(mid)){
				r=mid;
			}
			else{
				l=mid+1;
			}
		}
		cout<<l<<endl;
	}
	
	return 0;
}

```

---

## 作者：wuyouawa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2026B)

### 思路

看到最小，考虑使用二分答案。

我们可以二分 $k$ 的值，由于最多只能涂 $n$ 个格，并且还有一个在外面的，所以最大值是 $n-1$，check 函数里面暴力枚举 $i$ 和 $j$，看最多可以涂多少个黑色，最后判断是否 $\ge n-1$，如果小于就是符合条件，要更小，动 $r$，否则动 $l$。

注意开 long long。
### 代码


```cpp
#include<bits/stdc++.h>
#define int long long//自动开long long 
using namespace std;
int t,n,a[2005],l,r,mid,b[2005];
int check(int x)
{
	int s=0;
	for(int i=1;i<=n;i++)  b[i]=0;//重新赋值 
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)//暴力枚举 
		{
			if(abs(a[j]-a[i])<=x&&b[i]!=-1&&b[j]!=-1)//判断是否符合条件并可用 
			{
				s+=2;
				b[j]=-1;
				b[i]=-1;//置为不可用 
			}
		}
	}
	return s;//是否小于最大值 
}
signed main(){
	scanf("%lld",&t);
	while(t--)//注意多测 
	{
	    scanf("%lld",&n);
	    for(int i=1;i<=n;i++)  scanf("%lld",&a[i]);
	    l=0,r=a[n]-a[1]+1;//初始化 
	    while(l+1<r)
	    {
	    	mid=(l+r)/2;
	    	if(n-check(mid)<=1)  r=mid;
	    	else  l=mid;//决定动哪边 
	    }
		cout<<r<<endl;//r才是答案 
	}
	return 0;
} 
```

---

## 作者：_acat_ (赞：0)

## 题目大意

给定一个由单元格组成的条带，单元格从左到右编号，编号从 $0$ 到 $ 10^{18} $。最开始，所有单元格都是白色的。

给你一条长条，从左到右从 $0$ 到 $10^{18}$ 分成若干个单元格。最初，所有单元格都是白色的。你可以选 $2$ 个数 $a_i$ 和 $a_j$，保证满足 $ a_i \ne a_j $ 且 $ |a_i - a_j| \le k$，并将它们涂成黑色。这里给出了一个列表 $a$
 。该列表中的所有单元格都必须涂黑。此外，不在列表中的单元格也可以涂成黑色。求 $k_{\min}$。

## 思路

显然，如果要两个点被涂黑，那么 $|a_i-a_j|\le k$，当 $k$ 比较大时，不等式总是成立。所以可以二分答案，然后判断此时的 $k$ 是否可以涂黑。

因为 $n \le 2000$，所以只要暴力枚举所有的点对，然后判断是否满足条件，满足就记录下来，最后判断是否涂黑了至少 $n-1$ 个点。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[2010];
bool ck(int mid){
    int cnt=0;
    bool vis[10000]={0};

    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            if(vis[i]||vis[j]){
                continue;
            }
            if(abs(a[j]-a[i])<=mid){
                vis[j]=1;
                vis[i]=1;
                cnt+=2;
            }
        }
    }
    cnt=n-cnt;
    if(cnt<=1){
        return 1;
	}
    return 0;
}
void sol(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int l=0,r=1e17;
    while(l+1<r){
        int mid=l+(r-l)/2;
        if(ck(mid)){
            r=mid;
        }
        else{
            l=mid;
        }
    }
    cout<<r<<endl;
    return ;
}
signed main(){
    int t;
    cin>>t;
    while(t--){
		sol();
	}
	return 0; 
}
```

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF2026B) & [CF链接](https://codeforces.com/problemset/problem/2026/B)

# 思路分析：

分类讨论。

因为每次必须涂两个，且不能重复涂，所以 $n$ 为偶数时，显然要相邻两个数配对，排序后 $a_2-a_1,a_4-a_3,\dots,a_n-a_{n-1}$ 的最大值就是答案。

时间复杂度为 $O(n)$。

---

然后考虑 $n$ 为奇数，需要找一个不在涂色序列中的点与序列中的一个点配对，这样就能转化为 $n$ 为偶数的情况，如果序列中的点为 $a_i$，那么与之配对的点要么在 $a_i-1$，要么在 $a_i+1$，因为只有这样才能使这一对点对总答案的贡献最小。

可以枚举序列中需要配对的那个点，然后再按照 $n$ 为偶数的情况求一遍答案最后求最小值即可。

我们可以利用 STL 中的 vector，它可以快速的插入和删除任意位置的元素，也支持随机访问，这样就可以每次把序列之外需要涂色的点加入序列中计算答案了。

时间复杂度为 $O(n^2)$。

# 代码：


```cpp
//code by xxxalq
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=2003;

int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch>57||ch<48){
		if(ch==45){
			f=-1;
		}
		ch=getchar();
	}
	while(ch>=48&&ch<=57){
		x=(x<<1)+(x<<3)+(ch-48);
		ch=getchar();
	}
	return x*f;
}

int T,n,a[maxn],d1,d2;

vector<int>vec;

signed main(){
	T=read();
	while(T--){
		d1=d2=0;
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		sort(a+1,a+1+n);
		a[0]=a[1]-1,a[n+1]=a[n+1];
		if(n==1){
			cout<<'1'<<"\n";
			continue;
		}
		if(n%2==0){
			for(int i=2;i<=n;i+=2){
				d1=max(d1,a[i]-a[i-1]);
			}
			cout<<d1<<"\n";
			continue;
		}
		d1=1e18;
		vec.clear();
		for(int i=1;i<=n;i++){
			vec.push_back(a[i]);
		}
		for(int i=1;i<=n+1;i++){
			d2=0;
			if(i%2==1){
				if(i==n+1){
					vec.insert(vec.end(),1,a[i]-1);
				}else{
					vec.insert(vec.begin()+i-1,1,a[i]-1);
				}
			}else{
				if(i==n+1){
					vec.insert(vec.end(),1,a[i-1]+1);
				}else{
					vec.insert(vec.begin()+i-1,1,a[i-1]+1);
				}
			}
			for(int j=0;j<=n;j++){
				if(j%2==1){
					d2=max(d2,vec[j]-vec[j-1]);
				}
			}
			d1=min(d1,d2);
			vec.erase(vec.begin()+i-1);
		}
		cout<<d1<<"\n";
	}
	return 0;
}
```

---

## 作者：zhouruoheng (赞：0)

赛时罚时吃爽了 qwq。

首先若 $n$ 为偶数，必须是两两匹配涂黑的，不能有列表外的被涂黑。涂 $(1,2)$，$(3,4)$，$(5,6)$ 等等。在这些的差值取最大就是 $k$。

若 $n$ 为奇数，那么就是能且必须有一个数不是和列表中的数匹配涂黑，枚举这个数 $i$，将数组分为两部分 $(1,i-1)$ 和 $(i+1,n)$，和 $n$ 为偶数的情况一样考虑两部分。$O(n^2)$ 复杂度完全可以。

一开始认为奇数情况下只能让开头和末尾的和其他的数涂黑所以一直吃罚时 qwq。
``` cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>

using namespace std;
typedef long long ll;
const int N=2005;
const ll inf=1e18;
int n;
ll a[N];

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    ll ans=inf;
    if(n&1)
    {
        ll ans=inf;
        for(int i=1;i<=n;i+=2)
        {
            ll mx=0;
            for(int j=1;j<i;j+=2) mx=max(mx,a[j+1]-a[j]);
            for(int j=i+1;j<=n;j+=2) mx=max(mx,a[j+1]-a[j]);
            ans=min(ans,mx);
        }
        cout<<max(1ll,ans)<<'\n';
    }   
    else 
    {
        ll mx=0;
        for(int i=2;i<=n;i+=2) mx=max(mx,a[i]-a[i-1]);
        cout<<mx<<'\n';
    } 
}
int main ()
{
    #ifndef ONLINE_JUDGE 
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：CodeZhangBorui (赞：0)

## 题意

给定一个由白色单元格组成的纸带，定义一次操作为选定两个白色单元格 $i,j$ 满足 $|i - j| \le k$，将 $i$ 和 $j$ 单元格涂为黑色

给定一个长度为 $n$ 的列表 $a$，必须通过多次上述操作使得 $a$ 中的所有单元格均涂为黑色，此外 **最多可以涂黑一个** 不在列表 $a$ 中的单元格。

## 思路

二分答案思想。

由于题目给定单元格最大数量为 $10^{18}$ 次方，因此可以二分 $k$ 的值。对于每个 $k$ 检查是否符合题意（即能够涂 $\frac{n}2$ 对单元格）。

最坏时间复杂度为 $O(n \log D)$，其中 $D = \texttt{a[n]} - \texttt{a[1]}$（即 $k$ 可能的最大值），可以通过此题。

注意到计算 $\texttt{mid}$ 时 $\texttt{left} + \texttt{right}$ 可能溢出，因此使用 `left + ((right - left) >> 1)` 的方法防止溢出。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#define INF 0x3f3f3f3f
#define N 2003
#define MOD 998'244'353
#define ll long long
using namespace std;
int n;
ll a[N];

bool check(ll k) {
    int cnt = 0;
    for(int i = 1; i < n; i++) {
        if(a[i + 1] - a[i] <= k) {
            // 如果这两个单元格可以被涂黑，则计数器++，移动到下一对单元格
            cnt++;
            i++;
        }
        // 否则，向右移动一个单元格而不是一对
    }
    return cnt >= n / 2;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        if(n == 1) { // 对于 n = 1 的情况特判
            scanf("%lld", &a[1]);
            puts("1");
            continue;
        }
        for(int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
        }
        // 题目已保证数组 a 是递增的
        ll left = 0, right = a[n] - a[1], ans = right;
        // 对 k 进行二分
        while(left <= right) {
            ll mid = left + ((right - left) >> 1); // 防止溢出
            if(check(mid)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        printf("%lld\n", ans);
    }
}
```

[提交记录](https://codeforces.com/contest/2026/submission/288653830)

---

