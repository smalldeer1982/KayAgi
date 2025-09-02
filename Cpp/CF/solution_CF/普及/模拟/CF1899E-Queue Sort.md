# Queue Sort

## 题目描述

Vlad found an array $ a $ of $ n $ integers and decided to sort it in non-decreasing order.

To do this, Vlad can apply the following operation any number of times:

- Extract the first element of the array and insert it at the end;
- Swap that element with the previous one until it becomes the first or until it becomes strictly greater than the previous one.

Note that both actions are part of the operation, and for one operation, you must apply both actions.

For example, if you apply the operation to the array \[ $ 4, 3, 1, 2, 6, 4 $ \], it will change as follows:

- \[ $ \color{red}{4}, 3, 1, 2, 6, 4 $ \];
- \[ $ 3, 1, 2, 6, 4, \color{red}{4} $ \];
- \[ $ 3, 1, 2, 6, \color{red}{4}, 4 $ \];
- \[ $ 3, 1, 2, \color{red}{4}, 6, 4 $ \].

Vlad doesn't have time to perform all the operations, so he asks you to determine the minimum number of operations required to sort the array or report that it is impossible.

## 样例 #1

### 输入

```
5
5
6 4 1 2 5
7
4 5 3 7 8 6 2
6
4 3 1 2 6 4
4
5 2 4 2
3
2 2 3```

### 输出

```
2
6
-1
-1
0```

# 题解

## 作者：wmrqwq (赞：10)

# 题目链接

[CF1899E Queue Sort](https://www.luogu.com.cn/problem/CF1899E)

# 题意简述

现在有一个长度为 $n$ 的序列，你可以将它进行无限次操作，对于每次操作，你会进行以下两个步骤：

1. 提取数组的第一个元素，并将其插入末尾；

2. 将这个元素与前一个元素对调，直到它成为第一个元素或严格大于前一个元素。

求你是否能讲这个序列经过若干次操作后将这个序列从小到大排序，若可以，则输出最小操作次数，否则输出 `-1`。

# 解题思路

首先大家一定会有一个贪心的思路，那就是若能经过若干次操作后使这个序列从小到大排序，则操作次数一定小于 $n$。否则一定无法将这个序列经过若干次操作后从小到大排序。

然后我们容易得出，若有解，则操作次数一定为序列中第一个最小值出现的位置 $-1$，因为最后的序列一定是要从小到大排序的，最后我们可以发现，我们要从小到大插入每一个数，那么最小值后面的数是一定要依次从小到大排序的，否则操作的时候这个序列一定会乱序，也就会无解。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[200010],b[200010],sum,ans,minn,pd;
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
int main()
{
	IOS;
	cin>>t;
	while(t--)
	{
		minn=1e18,pd=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i],b[i]=a[i],minn=min(minn,a[i]);
		for(int i=1;i<=n;i++)
		{
			if(a[i]==minn)
			{
				sort(b+1+i,b+1+n);
				for(int j=i;j<=n;j++)
				{
					if(a[j]!=b[j])
					{
						pd=1;
						break;
					}
				}
				if(pd)
					cout<<-1<<endl;
				else
					cout<<i-1<<endl;
				break;
			}
		}
	}
	QwQ;
}
```

---

## 作者：lailai0916 (赞：3)

## 原题链接

- [洛谷 CF1899E Queue Sort](https://www.luogu.com.cn/problem/CF1899E)

## 解题思路

对非最小元素进行操作，都会将该元素在数列中排序。

设数列中最小的元素值为 $m$，考虑无解情况：

- 当第一个 $m$ 到达最左边时，且数列不是有序的，那么 $x$ 会移动到最右边。
- 但由于 $x$ 是最小的元素，又会一直向左移动到最左边，形成死循环。

所以在第一个 $m$ 到达最左边时，数组有序，才会有解。

操作次数为开始时第一个 $m$ 前面的元素个数。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;
const int N=200005;
int a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		int k=1;
		for(int i=1;i<=n;i++)
		{
			if(a[i]<a[k])
			{
				k=i;
			}
		}
		if(is_sorted(a+k,a+n+1))
		{
			cout<<k-1<<'\n';
		}
		else
		{
			cout<<"-1"<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：szhqwq (赞：1)

## $\tt{Solution}$

可以发现此序列里**最小**的数为序列的第一个元素时，在进行一次操作后还是在原来的位置。

那么我们可以考虑找到最小的数的位置，将其前面的数均进行操作（没有则不进行）即为最小操作数。

无解的情况则是在最小的数后面出现了递减的情况，无法将其进行操作。

[Link](https://codeforces.com/contest/1899/submission/233536377)

---

## 作者：zct_sky (赞：1)

### Solution
-----
显然，当排序操作执行到最小值时，会将其放到最后，然后一直向前移，直至到第一位。那么这时数组就和此次操作前一样，并且如果操作前数组并非有序，则会一直重复此操作，即永远不能将该数组变成有序的，输出 $-1$。

否则，若执行此次操作前数组已经有序，则输出之前的操作数即可。

时间复杂度 $\mathcal{O}(n)$。
### Code
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x*y;

}
const int N=2e5+7;
ll T,n,minn,a[N];
int main(){
	T=read();
	while(T--){
		n=read();
		minn=LLONG_MAX;
		for(int i=1;i<=n;i++)
			a[i]=read(),minn=min(minn,a[i]);
		ll ans=0;
		for(int i=1;i<=n;i++)
			if(a[i]==minn){
				ans=i-1;
				break;
			}
		for(int i=ans+2;i<=n;i++)
			if(a[i]<a[i-1]){
				ans=-1;
				break;
			}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：FireRain (赞：0)

# 思路

比较一眼。

令 $i$ 表示最小的满足 $a_i = \min\{a\}$ 的值，那么，$a_i$ 操作将无意义，因为 $a_{1 \sim (i - 1)}$ 操作过后，此时 $a_i$ 在第一位，它操作后依旧会在第一位。

所以 $a_{i \sim n}$ 将都不能操作，所以如果合法一定要满足 $a_{i \sim n}$ 有序。另外，操作数显然是 $i - 1$。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10,inf = 1e9 + 10;
int T,n;
int arr[N],brr[N];

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

inline void solve(){
    int id,Min = inf;
    n = read();
    for (re int i = 1;i <= n;i++){
        arr[i] = read();
        Min = min(Min,arr[i]);
    }
    for (re int i = 1;i <= n;i++){
        if (arr[i] == Min){
            id = i;
            break;
        }
    }
    for (re int i = id + 1;i <= n;i++){
        if (arr[i] < arr[i - 1]){
            puts("-1");
            return;
        }
    }
    printf("%d\n",id - 1);
}

int main(){
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：WA_sir (赞：0)

## [题目](https://codeforces.com/problemset/problem/1899/E)|[链接](https://www.luogu.com.cn/problem/CF1899E)

### 题目大意

你现在要用一种特殊的排序方法对一个长为 $n$ 的数组进行操作。每次操作，你将 $a_1$ 放在数组中最后一个小于等于它的元素后面（没有就不动）。求这种排序方法是否可以使得数组升序排列？

### 题目分析

通过观察可以发现，当 $a_1$ 为原始数组中最后一个最小的数时，题目中的操作变得无意义。而此时数组是否升序，取决于原始数组最后一个最小值后的元素是否升序。

举个例子：

$1,4,2,5,1,$ $\large{6},\large{3}$

此时最后一个 $1$ 后的元素不升序。

进行操作（注意之前不升序的元素）：

$4,2,5,1,1,6,3$

$2,5,1,1,6,3,4$

$5,1,1,2,6,3,4$

$1,1,2,6,3,4,5$

此时陷入循环，原始数组不升序的地方仍存在。

得出结论：原始数组最后一个最小值后的元素升序时操作数为这个元素的下标减一（简单不证）。否则无解。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		int mi=2e9,mi_i;
		bool f=true;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",a+i);
			if(mi>a[i])mi=a[i],mi_i=i;
		}
		for(int i=mi_i+1;i<n;i++)if(a[i]>a[i+1])f=false;
		if(f)printf("%d\n",mi_i-1);
		else printf("-1\n");
	}
	return 0;
}
```
感谢您的阅读。

---

## 作者：BYR_KKK (赞：0)

# 思路

非常水的一道题。

明显，每次操作的意义就是将最前面的数排到“正确”的位置，直到最前面是最小的数为止。

所以我们就发现了当最小的后面不是有序时，无解。

否则最小解就是最小值前面数的个数。

# code

```cpp

#include<bits/stdc++.h>
#define int long long
#define pii std::pair<int,int>
#define mk(P,Q) std::make_pair((P),(Q))
#define rep(j,k,z) for(int i=j;i<=k;i+=z)
#define per(j,k,z) for(int i=j;i>=z;i-=z)

const int maxn=2e5+10;

int a[maxn];

signed main(){
	int t;
	std::cin>>t;
	while(t--){
		int n;
		std::cin>>n;
		int min=0x3f3f3f3f,mw;
		for(int i=1;i<=n;i++) {
			std::cin>>a[i];
			if(a[i]<min) min=a[i],mw=i;
		}
		bool find=1;
		for(int i=mw+1;i<=n;i++){
			if(a[i]<a[i-1]) {
				find=0;
				break;
			}
		}
		if(!find) std::cout<<-1<<'\n';
		else std::cout<<mw-1<<'\n';
	}
	return 0;
}

```

---

## 作者：LucasXu80 (赞：0)

远比同场 D 简单的一道 E。

考虑一个首项为最小值、未完成排序的数列，根据题目“只能选择数列首项排序”的规定，我们将会陷入选择首项这一最小值 $ \rightarrow$ 排序 $ \rightarrow$ 这一最小值回到首项的循环中。

因此有结论，数列最小值以后的项应当已经从小到大排序完成，这一条件是数组可以最终完成排序的充要条件。此后只需要将最小值前的项一一放到数组最后进行排序即可，操作数显然为 最小值所在位置下标 $-1$。

```cpp
#include <iostream>
using namespace std;
int t,n,a[200001];
int main()
{
    cin>>t;
    while (t--)
    {
        cin>>n;
        int minn=2e9,minidx;
        for (int i=1; i<=n; i++)
        {
            cin>>a[i];
            if (a[i]<minn)
            {
                minn=a[i];
                minidx=i; // 找到最小值所在位置
            }
        }
        bool flag=0;
        for (int i=minidx+2; i<=n; i++)
        {
            if (a[i]<a[i-1]) // 最小值后未排序完成
            {
                flag=1;
                break;
            }
        }
        if (!flag) cout<<minidx-1<<'\n';
        else cout<<-1<<'\n';
    }
    return 0;
}
```


---

## 作者：DerrickLo (赞：0)

我们注意到，如果不能通过这样的操作使得序列有序，那么必然是第一个数操作后还是第一个数，也就是说第一个数是最小的数。

那么也就相当于，等到第一个数是最小数时，序列必须有序，否则无法使序列有序。

又因为最小数前的数会插入对应的位置，所以只需要判断最小数后的数是否是有序的即可，而操作次数与最小数的位置有关。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[200005];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int minn=LONG_LONG_MAX,pos,flag=1;
		for(int i=1;i<=n;i++)if(a[i]<minn)minn=a[i],pos=i;
		for(int i=pos;i<n;i++)flag&=(a[i]<=a[i+1]);
		if(!flag){
			cout<<"-1\n";
			continue;
		}
		cout<<pos-1<<'\n';
	}
	return 0;
}
```

---

## 作者：bluewindde (赞：0)

容易发现，这个算法的过程就是把最小元素一个个地向前挪动，所以有以下结论：

- 当逆序对出现在最小的元素后时，无解。
- 否则，答案为最小的元素的位置减 $1$。

代码

```cpp
#include <iostream>

#define int long long

using namespace std;

int T, n;
int a[200005];
int b[200005];
int tot;

static inline void msort(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    int l1 = l, r1 = mid, l2 = mid + 1, r2 = r, k = l;
    msort(l1, r1);
    msort(l2, r2);
    while (l1 <= mid && l2 <= r)
    {
        if (a[l1] <= a[l2])
        {
            b[k] = a[l1];
            ++l1, ++k;
        }
        else
        {
            b[k] = a[l2];
            ++l2, ++k;
            tot += mid - l1 + 1;
        }
    }
    while (l1 <= mid)
        b[k] = a[l1], ++l1, ++k;
    while (l2 <= r)
        b[k] = a[l2], ++l2, ++k;
    for (int i = l; i <= r; ++i)
        a[i] = b[i];
}

signed main()
{
#ifdef DEBUG
    freopen("T5.in", "r", stdin);
#endif
    cin >> T;
    while (T--)
    {
        cin >> n;
        int mn = 1e18, mi = -1;
        for (int i = 1; i <= n; ++i)
        {
            int x;
            cin >> x;
            if (x < mn)
            {
                mi = i;
                mn = x;
            }
            a[i] = x;
        }
        tot = 0;
        if (mi + 1 <= n)
            msort(mi + 1, n);
        if (tot)
        {
            cout << "-1" << endl;
        }
        else
        {
            cout << mi - 1 << endl;
        }
    }
    return 0;
}

/*
gcc T5.cpp -o T5.exe -lstdc++ -std=c++2a -Wall -Wextra -Wconversion -Wshadow -DDEBUG
*/
```


---

## 作者：indream (赞：0)

## CF1899E Queue Sort 题解
[CF1899E](https://www.luogu.com.cn/problem/CF1899E) | [AC](https://www.luogu.com.cn/record/136259690)
### 思路
容易发现，当数列中的最小值到达第一个位置时，一次操作后仍到队首，于是陷入了死循环——此时若最小值后的竖列仍未完成排序，便是无解；若完成了排序，设最小值为 $a_i$（下标从 0 开始），则一定操作了 $i$ 次（把前面的 $i$ 个移到 $a_i$ 后）。

注意，判最小值时要 $a_i < minn$，而不是 $a_i \le minn$。因为如果有多个相同的最小值，操作到第一个最小值时就会进入死循环。

算法复杂度 $O(tn)$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int a[200005],t,n,minn,mini;
bool judge;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    cin>>t;
    while(t--){
        cin>>n;
        minn=1E9+10;//记得初始化
        judge=0;
        for(int i=0;i<n;i++){
            cin>>a[i];
            if(a[i]<minn){
                minn=a[i];
                mini=i;
            }
        }
        for(int i=mini+1;i<n-1;i++){
            if(a[i+1]<a[i]){
                cout<<-1<<'\n';
                judge=1;
                break;
            }
        }
        if(judge)
            continue;
        else
            cout<<mini<<'\n';
    }
    return 0;
}
```

---

## 作者：DFbd (赞：0)

## 思路
如果当前第一个数是最小的，那么一次操作后，数组没有变化。

所以在最小数前的数会经过一次操作自动排好序，而最小数后的不会。

那么最小后的数就必须有序，否则就无法排序。

能排序时，操作次数就是在最小数前的数的数量。

## 代码
```
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t, n, a[N], minn, x, f;
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    minn = 1e9 + 1;
    f = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      if (a[i] < minn) {
        minn = a[i];//求最小数并记录位置
        x = i;
      }
    }
    for (int i = x; i < n; i++) {
      if (a[i] > a[i + 1]) f = 1;//判断最小数后是否有序
    }
    if (f)
      cout << "-1\n";
    else
      cout << x - 1 << "\n";
  }
  return 0;
}
```

---

