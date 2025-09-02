# Strange Device

## 题目描述

This problem is interactive.

We have hidden an array $ a $ of $ n $ pairwise different numbers (this means that no two numbers are equal). You can get some information about this array using a new device you just ordered on Amazon.

This device can answer queries of the following form: in response to the positions of $ k $ different elements of the array, it will return the position and value of the $ m $ -th among them in the ascending order.

Unfortunately, the instruction for the device was lost during delivery. However, you remember $ k $ , but don't remember $ m $ . Your task is to find $ m $ using queries to this device.

You can ask not more than $ n $ queries.

Note that the array $ a $ and number $ m $ are fixed before the start of the interaction and don't depend on your queries. In other words, interactor is not adaptive.

Note that you don't have to minimize the number of queries, and you don't need to guess array $ a $ . You just have to guess $ m $ .

## 说明/提示

In the example, $ n = 4 $ , $ k = 3 $ , $ m = 3 $ , $ a = [2, 0, 1, 9] $ .

## 样例 #1

### 输入

```
4 3
4 9
4 9
4 9
1 2```

### 输出

```
? 2 3 4
? 1 3 4
? 1 2 4
? 1 2 3
! 3
```

# 题解

## 作者：是个汉子 (赞：9)

本蒟蒻并没有看懂两位大佬写的题解，所以来写一篇蒟蒻都能看懂的题解。
### Solution

我们可以对前 $k+1$ 个元素询问 $k+1$ 次，因为题目中明确说明 $k<n$ ，所以是不会超的。

这样做的正确性：每次会少一个数，当你少的是第 $m$ 个数之前的数或 $m$ 时，返回的会是第 $m+1$ 大的数，当你少的是 $m$ 之后的数时，返回的是第 $m$ 大的数。

第 $m+1$ 大的数会出现 $m$ 次，第 $m$ 大的数会出现 $k+1-m$ 次，所以统计较大数出现次数即可。

```c++
#include<bits/stdc++.h>

using namespace std;
map<int,int> f;

int main(){
    ios::sync_with_stdio(false);
    int n,k;
    cin>>n>>k;
    int maxx=0;
    for(int i=1;i<=k+1;i++){
        putchar('?');
        for(int j=1;j<=k+1;j++){
            if(i==j) continue;
            printf(" %d",j);
        }
        puts("");
        fflush(stdout);
        int x,y;
        cin>>x>>y;
        f[y]++;
        maxx=max(maxx,y);
    }
    printf("! %d\n",f[maxx]);
    return 0;
}
```



---

## 作者：ZMQ_Ink6556 (赞：2)

## 题解：[CF1270D Strange Device](https://www.luogu.com.cn/problem/CF1270D)

### 解题思路

做法与 $n$ 完全无关。只要询问前 $k + 1$ 个数 $k + 1$ 次，使每次询问的元素个数为 $k$ 且每次询问不相同。

此时有两种可能，如果去除的数在前 $m$ 小，则返回一个更大的数，否则返回一个较小的数。

![pic](https://cdn.luogu.com.cn/upload/image_hosting/nbm0duls.png)

因为是去除恰好一个数，所以会出现恰好两种回答。答案就是所有询问出现的较大的回答的个数。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , k , pos , x , a[505] , ans;
int main()
{
	cin >> n >> k;
	for(int i = 1 ; i <= k + 1 ; i++)
	{
		cout << "? ";
		for(int j = 1 ; j <= k + 1 ; j++)
		{
			if(j != i)
			{
				cout << j << ' ';
			}
		}
		cout << endl;
		cin >> pos >> x;
		a[i] = x;
	}
	sort(a + 1 , a + 1 + k + 1);
	for(int i = 1 ; i <= k + 1 ; i++)
	{
		if(a[i] != a[1])
		{
			ans++;
		}
	}
	cout << "! " << ans << endl;
	return 0; 
}
```

---

## 作者：yangmuguang (赞：1)

### 题意

这是一道交互题。

有一个长为 $n$ 的数组 $a$，你能做出至多 $n$ 次询问，每次询问 $a$ 中的 $k$ 个元素 $a_{x_1},a_{x_2},a_{x_3}\cdots a_{x_k}$ 中第 $m$ 小的数的下标以及它的值。

起初，你只知道 $n$ 和 $k$，你要通过至多 $n$ 次询问求出 $m$。

$1\le k <n\le 500$。

### 思路

其实只要问 $k+1$ 个问题就够了。第 $i$ 次询问 $1$ 到 $k+1$ 中除 $i$ 以外的 $k$ 个数。

此时，若第 $i$ 个数在前 $m$ 小的数中，交互程序会返回 $1$ 到 $k+1$ 中第 $m+1$ 大的数。

否则，交互程序会返回第 $m$ 小的数。

![](https://cdn.luogu.com.cn/upload/image_hosting/7c0b19g7.png)

由于前 $m$ 小的数有 $m$ 个，所以第一种情况会发生恰好 $m$ 次。

所以，$m$ 就等于所有的询问中返回的最大的数的出现次数。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define faster ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0)
ll n,k,cnt[505],ans,mx;
int main()
{
	faster;
	cin>>n>>k;
	for (ll i=1;i<=k+1;i++)
	{
		cout<<"? ";
		for (ll j=1;j<=k+1;j++)
		{
			if (i==j)continue;
			cout<<j<<" ";
		}
		cout<<endl;
		ll a,b;
		cin>>a>>b;
		cnt[a]++;
		if (b>mx)
		{
			mx=b;
			ans=a;
		}
	}
	cout<<"! "<<cnt[ans]<<endl;
	return 0;
}
```

##

---

## 作者：sgl654321 (赞：1)

### 题目大意
交互题，给定 $n, k$，每次你要询问 $k$ 个互不相同的位置上的数，交互器会返回其中第 $m$ 大的数是多少，并告诉你它的位置。

请你在 $n$ 次询问后还原出 $m$ 的值。保证每个位置上的数都不同。

### 解题思路
如果遇到这种比较复杂的交互题，应从样例开始分析。思考样例是如何得出正确答案的？

当 $n = 4, k = 3$ 时，四次询问显然是把 $C_4^3$ 种情况都问一遍。设这四个数分别是 $a,b,c,d$，其中 $a<b<c<d$。

那么四次询问就是分别问：
$(a,b,c)$，$(a,b,d)$，$(a,c,d)$，$(b,c,d)$。

- 若 $m = 1$，则较小的数 $(a)$ 出现了 $3$ 次，较大的数 $(b)$ 出现了 $1$ 次。

- 若 $m = 2$，则较小的数 $(b)$ 出现了 $2$ 次，较大的数 $(c)$ 出现了 $2$ 次。

- 若 $m = 3$，则较小的数 $(c)$ 出现了 $1$ 次，较大的数 $(d)$ 出现了 $3$ 次。

因此我们根据返回的数出现的**次数**及其**大小关系**，就可以还原出 $m$ 的值。

推广一下:

- 当 $k$ 还是等于 $3$，$n > 4$ 时怎么办？

显然只需要问前四个数，问四次就可以得出答案了。后面的数都没什么用。

- 当 $k$ 变成任意值了怎么办？

首先由于 $n > k$ 所以肯定是问前 $k + 1$ 个数，得到答案。通过再次手摸，不难证明不管 $m$ 是多少，返回的数只可能有两个，一个较小一个较大。

进一步地，如果出现较小数的次数为 $k + 1 - x$ 次，较大数的次数为 $x$ 次，那么 $m = x$。

这样从特殊到一般就解决问题了。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k, ret1, ret2, a[510], num1, num2;
int main(){
	cin >> n >> k;
	for(int i = 1; i <= k + 1; i++){
		cout << "? ";
		for(int j = 1; j <= k + 1; j++)
			if(j == i) continue;
			else cout << j << ' ';
		cout << endl;
		cin >> ret1 >> ret2; a[i] = ret2;
	}
	sort(a + 1, a + 1 + k + 1);
	for(int i = 1; i <= k + 1; i++)
		if(a[i] == a[1]) num1++;
		else num2++;
	cout << "! " << num2 << endl;
	return 0; 
}
```

---

## 作者：xht (赞：1)

交互题。

首先可以通过 $n-k+1$ 次询问确定 $n-k+1$ 个位置的值。

若 $n - k + 1 \ge k$，则直接询问已知的 $k$ 个找到 $m$ 即可。

否则，考虑最后一次询问会产生一个已知的位置 $x$ 和 $k-1$ 个未知的位置，我们可以拿另外一个已知的位置 $y$ 分别替换这 $k-1$ 个未知的位置，然后根据回答与不替换时的回答是否一致判断这个位置与 $x$ 位置上的数的大小关系，即可找到这些数中有多少个比位置 $x$ 上的数小，从而求出 $m$。

```cpp
const int N = 507;
int n, k, a[N];

inline pi ask(vi o) {
	vi O = o;
	sort(o.begin(), o.end());
	cout << '?';
	for (auto c : o) cout << ' ' << c;
	cout << endl;
	fflush(stdout);
	int a, b;
	cin >> a >> b;
	o = O;
	return mp(a, b);
}

int main() {
	cin >> n >> k;
	if (k == 1) return cout << "! 1" << endl, 0;
	vi o, q;
	for (int i = 1; i <= k; i++) o.pb(i);
	for (int i = k; i <= n; i++) {
		pi p = ask(o);
		a[p.fi] = p.se;
		q.pb(p.fi);
		if (i != n)
			for (ui j = 0; j < o.size(); j++)
				if (o[j] == p.fi) o[j] = i + 1;
	}
	if (n - k + 1 >= k) {
		o.clear();
		for (int i = 0; i < k; i++) o.pb(q[i]);
		pi p = ask(o);
		int ans = 0;
		for (int i = 0; i < k; i++)
			if (a[o[i]] <= p.se) ++ans;
		cout << "! " << ans << endl;
		return 0;
	}
	int x = q.back();
	q.pop_back();
	int y = q.back();
	for (ui i = 1; i < o.size(); i++)
		if (o[i] == x) swap(o[0], o[i]);
	int ans = 0;
	for (ui i = 1; i < o.size(); i++) {
		int z = o[i];
		o[i] = y;
		pi p = ask(o);
		if (p.fi == x) ans += a[y] < a[x];
		else ans += a[x] < a[y];
		o[i] = z;
	}
	cout << "! "  << ans + 1 << endl;
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
交互题加思维题。

挺好想的。
## 分析。
想要求出 $m$ 则需要查询 $k+1$ 次，那么对于前 $k+1$ 个数，每次都删去一个数，则如果要去查询剩下的 $k$ 的个数，则有两种情况。然后你就一直输出 ```?``` 进行询问，然后缩小范围，最终确定答案。

设第 $m$ 大的数为 $M$ 并贯通下文。

如果我们删去的这个数 $x\leq M$ 则我们得到的肯定是第 $m+1$ 个大的数，并且出现的次数是第 $m$ 位。

另一种情况就是我们删去的这个数 $x> M$ 则我们得到的肯定是 $M$ 本身，并且出现的次数是第 $k-1+m$ 位。

反推一下，我们只要求出第 $m+1$ 大的数，就可以知道 $m$ 的答案，所以这样找即可。

代码如下，仅供参考：
```
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
map<int,int> m;
int n,k,p,a;
int main(){
    cin>>n>>k;
    for(int i=1;i<=k+1;i++){
        cout<<"? ";
        for(int j=1;j<i;j++){
        	cout<<j<<" ";
		}
        for(int j=i+1;j<=k+1;j++){
        	cout<<j<<" ";
		}
        cout<<"\n";
        fflush(stdout);
        cin>>p>>a;
        m[a]++;
    }
    cout<<"! "<<m.rbegin()->second<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Exber (赞：0)

先问前 $k$ 个的答案 $a_{x}$，我们只要确定前 $k$ 个里有多少个比 $a_x$ 小即可。

那么我们问 $k+1$ 次，第一次问前 $k$ 个，设答案为 $a_x$。

接下来第 $i$ 次（$i\ge 2$）问前 $k+1$ 个除了第 $i-1$ 个，设第 $i$ 次询问答案为 $a_{w_i}$。

那么若 $a_{w_{x+1}}>a_x$ 则 $a_{k+1}>a_x$ 否则 $a_{k+1}<a_x$。

分类讨论：

- 若 $a_{k+1}>a_x$，那么对于第 $i$ 次询问（$2\le i$），若 $a_{w_i}>a_x$ 那么 $a_i<a_x$，否则 $a_i>a_x$；
- 若 $a_{k+1}<a_x$，那么对于第 $i$ 次询问（$2\le i$），若 $a_{w_i}=a_x$ 那么 $a_i<a_x$，否则 $a_i>a_x$。

具体证明考虑 $<a_x$ 的数的个数变化即可。

代码如下：

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int S=505;

int n,k;
int pos[S];
int w[S],val[S];

inline void que(int &id,int &x)
{
	printf("? ");
	for(int i=1;i<=k;i++) printf("%d ",pos[i]);
	printf("\n");
	fflush(stdout);
	scanf("%d%d",&id,&x);
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++) pos[i]=i;
	que(w[1],val[1]);
	for(int i=2;i<=k+1;i++)
	{
		for(int j=1;j<=i-2;j++) pos[j]=j;
		for(int j=i;j<=k+1;j++) pos[j-1]=j;
		que(w[i],val[i]);
	}
	int x=w[1],m=1;
	if(val[x+1]>val[1])
	{
		for(int i=1;i<=k;i++)
		{
			if(i==x) continue;
			m+=val[i+1]>val[1];
		}
	}
	else
	{
		for(int i=1;i<=k;i++)
		{
			if(i==x) continue;
			m+=val[i+1]==val[1];
		}
	}
	printf("! %d\n",m);
	return 0;
}
```

---

## 作者：liuyz11 (赞：0)

# 题解 CF1270D 【Strange Device】

**该场比赛的所有题解：[我的博客求围观](https://www.cnblogs.com/nblyz2003/p/12161998.html)**

题目大意：有一个长为n数列a，值已确定，但是你不知道。现在有个设备，你可以输入长为k的上升序列p1,p2,…,pk，进行询问，它会回答ap1，ap2,...,apk中第m小的数在原数列的坐标和这个数的值。现在给你n和k，让你在最多询问n次后回答m的大小。

作为以往交互题直接跳的人，这题拿到一脸懵，后来还是看题解才有的思路。

我们只需要询问k+1次，第i次询问序列为{ x | 1 <= x <= k + 1, x <> i }

假设n = 4， k = 3，询问分别为

    2 3 4

    1 3 4

    1 2 4

    1 2 3

这样问有一个好处，第i次询问，若是i <= m，那么返回的必然是[a1..ak +1]中第m + 1小的数，否则返回的数必然是第m小的数。

那么在k+1次询问后，m+1小的数恰好返回了m次，于是我们答案就是返回的较大的一个数的次数。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

map<int, int> f;

int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	int maxx = 0;
	rep(i, 1, k + 1){
		putchar('?');
		rep(j, 1, k + 1){
			if(i == j) continue;
			printf(" %d", j);
		}
		puts("");
		fflush(stdout);
		int x, y;
		scanf("%d%d", &x, &y);
		f[y]++;
		maxx = max(maxx, y);
	}
	printf("! %d\n", f[maxx]);
    return 0;
}
```

---

