# Li Hua and Pattern

## 题目描述

Li Hua has a pattern of size $ n\times n $ , each cell is either blue or red. He can perform exactly $ k $  operations. In each operation, he chooses a cell and changes its color from red to blue or from blue to red. Each cell can be chosen as many times as he wants. Is it possible to make the pattern, that matches its rotation by $ 180^{\circ} $ ?

Suppose you were Li Hua, please solve this problem.

## 说明/提示

In test case 1, you can't perform any operation. The pattern after rotation is on the right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/debd4989c6daceeecb5305f7cb7ec257866c6bf5.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/187295f499fcefe17d924d6eb93da50e9773c4d3.png)In test case 2, you can perform operations on $ (2,1),(3,2),(3,4) $ . The pattern after operations is in the middle and the pattern after rotation is on the right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/0c0aed7c9c5dddd78137bdc2f8654231a7026420.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/3b36bd2af8c0789e62f808d71f3af4107dad02c2.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1797B/3b36bd2af8c0789e62f808d71f3af4107dad02c2.png)

## 样例 #1

### 输入

```
3
4 0
1 1 1 1
0 0 0 1
1 0 1 0
1 1 1 1
4 3
1 0 1 1
1 0 0 0
0 1 0 1
1 1 0 1
5 4
0 0 0 0 0
0 1 1 1 1
0 1 0 0 0
1 1 1 1 1
0 0 0 0 0```

### 输出

```
NO
YES
YES```

# 题解

## 作者：qifan_maker (赞：2)

### 题目链接
[洛谷](https://www.luogu.com.cn/problem/CF1797B)

[Codeforces](https://codeforces.com/contest/1797/problem/B)
### 题意分析
李华有一个 $n\times n$ 的图案，每个格子为蓝色或红色。他可以操作 $k$ 次，每次操作他可以修改一个格子的颜色，问能否使图案旋转 $180^{\circ}$ 后不变。
### 题目解法
我们可以枚举图案，并修改与对应位置颜色不同的格子，由于枚举的是整个图案，所以两个对应且不相同的格子会被计算两遍，$\min{k}$ 就是修改次数 $\div 2$。

如果 $k<\min{k}$，则不可能满足题意，答案为 `NO`。

否则 $k\ge\min{k}$，分为两种情况：

1. $n$ 为偶数。如果 $k-\min{k}$ 为偶数，则可将任一格子变为红色再变回蓝色抵消操作，答案为 `YES`；否则为奇数，则不可能满足题意，答案为 `NO`。
2. $n$ 为奇数。$k-\min{k}$ 的操作可以修改图案中心的颜色，不影响旋转后的图案，答案为 `YES`。

时间复杂度 $\mathcal{O}(n^2)$。
### [AC](https://www.luogu.com.cn/record/107746407) Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--){
		int n,k;
		cin >> n >> k;
		int a[1100][1100];
		for (int i=1;i<=n;i++){
			for (int j=1;j<=n;j++){
				cin >> a[i][j];
			}
		}
		int mink = 0;
		for (int i=1;i<=n;i++){
			for (int j=1;j<=n;j++){
				if (a[i][j] != a[n-i+1][n-j+1]){
					mink++;
				}
			}
		}
		mink /= 2;
		if (k < mink){
			cout << "NO" << endl;
		}
		else {
			if (n%2 == 0){
				if ((k-mink)%2 == 0){
					cout << "YES" << endl;
				}
				else {
					cout << "NO" << endl;
				}
			}
			else {
				cout << "YES" << endl;
			}
		}
	}
	return 0;
}

```

---

## 作者：jiangchen1234 (赞：1)

## 题目大意
李华有一个 $n×n$ 的图案，每个格子为蓝色或红色。他可以操作 $k$ 次，每次操作他可以修改一个格子的颜色，问能否使图案旋转 $180$ 度后不变。
## 题目分析
问能否使图案旋转 $180$ 度后不变，也就是说 $a_{i,j}$ 与 $a_{n - i + 1,n - j + 1}$ 是否相等，如果不相等，那么修改次数加一。

做完这些步骤后，本题的核心来了。

如果修改次数小于给定我们的修改次数，那么要分情况讨论了。

1.  情况 $1$ 图案的边长为奇数，我们只要修改最中间的那个格子就行了，那么能完成任务。
2. 情况 $2$ 图案的边长为偶数，如果剩下的次数为偶数，我们便找一个格子将它修改，最后这个格子还会是原来的格子的颜色，那么能完成任务。但如果是奇数最后那个格子会是原来的格子的颜色吗？不是。那么便不能完成任务。

 $*$ 注意 $:$ 找修改次数时。我们跑的是全图，修改次数要除二（因为两个不同的对应点各加了一次，重复了）。

### 废话不多说 c++ 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2000;
long long t,n,k,a[maxn][maxn];
bool p;
string st;
void in(long long n) {//输入
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin>>a[i][j];
		}
	}
}
bool find(long long d) {//核心步骤
	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(a[i][j] != a[n - i + 1][n - j + 1]) {//判定
				ans++;
			}
		}
	}
	ans /= 2;//重复了两遍，要除2
	if (ans > d) return 0;//比标准多 返回false
	if(ans % 2 == d % 2 or n % 2 == 1) {
		return 1;
	} else {
		return 0;
	}
}
int main() {
	cin>>t;
	for(int i = 0; i < t; i++) {
		cin>>n>>k;
		in(n);
		if(find(k)) {
			cout<<"YES"<<endl;
		} else {
			cout<<"NO"<<endl;
		}
	}
```


---

## 作者：Frictional (赞：0)

## 题意
李华有一个 $n\times n$ 的矩阵,每个格子为红 $(1)$ 或蓝 $(0)$ 的一种颜色。判断他恰好操作 $k$ 次后，每次操作可以选取一个格子改变颜色，一个格子可以操作多次，能否使这个矩阵中心对称。
## 思路
首先，我们先来了解一下中心对称，即当把这个图形旋转 $180^\circ$ 后这个旋转后的图形能和原图形重叠的话，那么这个图形就是中心对称的。

那么经过多次的画图观察，我们发现旋转 $180^\circ$ 后，$f_{i,j}$ 对应的是 $f_{n-i-1,j-i-1}$，这是坐标从 $0$ 开始的情况。如果对应的格子不相等那么操作次数加1。

之后如果这个操作次数比 $k$ 大，那么输出 $NO$，相等输出 $YES$
但是如果少于规定次数的话，那就要分情况而定了。

1. 当这个矩阵有中心点，也就是 $n$ 是奇数，那么就可以一直修改中心点，所以这种情况是可行的。
2. 当 $n$ 是偶数时，如果算出来的操作次数与 $k$ 的差为奇数时，那就没法在恰好为 $k$ 次的时候，修改成中心对称的矩阵。如果是偶数，那么就可以通过一直修改同一个格子，来保持，是可行的。

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1e3+5;
int t;
int n,k;	
int f[N][N];
int cnt;
signed main(){
	std::cin>>t;
	while(t--){
		cnt=0;
		std::cin>>n>>k;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				std::cin>>f[i][j];
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(f[i][j]!=f[n-i-1][n-j-1]) cnt++;
			}
		}
		cnt/=2;
		if(cnt>k) puts("NO");
		else if(cnt%2==k%2||n%2) puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：Spir1t (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1797B)

#### 思路：

首先我们需要知道数组中对称位置上的元素是否相等，即：`a[i][j] != a[n-i+1][n-j+1]`，如果成立，那么将 $ans$ 加一，然后因为对称位置上的两个元素只需要计算一次，所以还需将 $ans{\div} 2$，然后进行如下操作：

- 根据不相等个数 $ans$ 与操作次数 $k$ 的关系进行判断输出结果：
1. 如果 `k<ans`,输出 `NO`。
2. 否则，根据数组大小 $n$ 的奇偶性再次进行条件判断：

     - 当 $n$ 为奇数时，由于只需要对着中心点一个点进行操作，可以保证恰好用完 $k$ 次操作，返回 `YES`。
     - 当 $n$ 为偶数时，如果 `(k-ans)%2==0`，则说明剩余的操作次数可以将一个点变化后保持原样，返回 `YES`；否则返回 `NO`。
     
代码就不放了，大家都有。

---

## 作者：ylch (赞：0)

# CF1797B Li Hua and Pattern 题解

[【题目传送门】](https://www.luogu.com.cn/problem/CF1797B)

## 题目大意

给你一个由 $0$ 和 $1$ 组成的正方形，请问能不能在 $k$ 步内将正方形变为中心对称的图形？

## 题目分析

中心对称图形：在平面内，把一个图形绕着某个点旋转 $180$ 度，如果旋转后的图形能与原来的图形重合，那么这个图形叫做中心对称图形，这个点叫做它的对称中心。

下面两个图形都是中心对称图形：

![中心对称1](https://bkw-oldfile.oss-cn-shenzhen.aliyuncs.com/bakcover/2019-06-27/c54c804913c81364833a7b5a96f87d87.bmp)

![中心对称2](https://bpic.588ku.com/element_origin_min_pic/19/05/10/0407b75e2e2f047ffcbb0553c5a08cd3.jpg)

中心对称的数组下标递推式为：

$$a_{i,j} = a_{n-i+1,n-j-1}$$

## 解题步骤

1.依据中心对称的数组下标递推式把数组跑一遍，记录不相等的个数 $ans$。

2.因为全部跑一遍会造成不一样的两个点被重复计算了 $2$ 次，所以将刚才的答案 $ans \div 2$。

3.判断不相等个数与 $k$ 的关系。

3.1.如果 $ans > k$，直接返回 `NO`。

3.2.如果 $ans \le k$，分情况讨论：

因为题目要求必须正好将 $k$ 用完，当 $n$ 为奇数时，只要对着中心点一个点一直搞就行，返回 `YES`；

当 $n$ 为偶数时，如果 $k - ans$ 为偶数，则可以将一个点在多次变化后保持原样，返回 `YES`，但是奇数的话就不行，因为无法变化后保持原样，返回 `NO`。

## AC 代码

时间复杂度 $\text{O}(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[1100][1100];
int T,n,k;

int main()
{
	cin >> T;
	while (T--)
	{
		cin >> n >> k;
		for (int i=1; i<=n; i++)
			for (int j=1; j<=n; j++)
				cin >> a[i][j];
		int ans = 0;
		for (int i=1; i<=n; i++)
			for (int j=1; j<=n; j++)
				if (a[i][j] != a[n-i+1][n-j+1])	ans++;
		ans /= 2;
		if (k < ans)
		{
			puts("NO");
		}
		else
		{
			if (n%2 == 0)
				puts((k-ans)%2==0? "YES" : "NO");
			if (n%2 == 1)
				puts("YES");
		}
	}
	return 0;
}
```

End
-------------

管理员大大辛苦啦~	

谢谢大家！

---

## 作者：FSHYLHX (赞：0)

# 题目大意
给定一个只由 $0$ 和 $1$ 组成的正方形，求能否正好进行 $k$ 次修改，使得这个正方形中心对称。
# 思路分析
观察本题数据，发现可以进行大模拟。首先枚举整个图案，计算出对应的格子的颜色是否相同，不同的话将答案数加一。因为是枚举整个图案，所以最后答案数还要除以二。接下来分类两种情况：

如果答案数大于 $k$，则不可能达成题意，无解。

如果答案数小于 $k$，则还要分类两种情况：

如果 $n$ 为奇数，则一定可以修改中心的格子的颜色，所以一定有解。

如果 $n$ 为偶数：如果 $k - ans$ 为偶数，则可将随便一个格子不断变化颜色，一定有解；否则为奇数，则不可能满足题意，无解。
# 代码实现
```c
#include<bits/stdc++.h>
using namespace std;
int i,j,k,m,n,ans,sum,t;
int a[1005][1005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				scanf("%d",&a[i][j]);
			}
		}
		int ans = 0;
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(a[i][j] != a[n-i+1][n-j+1]) ans++;
			}
		}
		ans /= 2;//这步很关键
		if(ans > k) printf("NO\n");
		else if((k - ans) % 2 == 0) printf("YES\n");
		else if(n % 2 == 1) printf("YES\n");
		else printf("No\n");
	}
	return 0;
} 
```


---

## 作者：251Sec (赞：0)

写个水题。

首先可以求出修改的最小次数：对于每个格子，我们可以找到唯一的一个位置与它中心对称。我们统计它们的颜色是否相同即可。如果不相同则需要进行一次修改。注意这样计算完之后需要除以二，因为每一对格子被算了两次。

记修改的最小次数为 $x$，如果 $k$ 小于 $x$ 显然无解，否则，若 $n$ 为奇数，我们后续的操作都可以修改正中间的格子，显然合法。若 $n$ 为偶数且 $k-x$ 为偶数，则后续操作可以选择同一个格子。最终仍然合法，若 $n$ 为偶数且 $k-x$ 为奇数，则无解，理由是每次操作一定会使得「不对称」格子的个数奇偶性改变。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T, n, k;
int a[1005][1005];
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i][j] != a[n - i + 1][n - j + 1]) ans++;
            }
        }
        ans >>= 1;
        if (ans > k) puts("NO");
        else if (!((k - ans) & 1)) puts("YES");
        else if (n & 1) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：abensyl (赞：0)

原题：[CF1797B Li Hua and Pattern](https://www.luogu.com.cn/problem/CF1797B)。

真的是非常好的一道题。

## 思路

首先，我们要知道旋转 $180^\circ$ 后与原图形相等是中心对称图形。

我们先考虑最少需要多少次操作能将其变为中心对称图形。

很显然，次数即：
$$\sum^n_{i=1}\sum^n_{j=1}(a_{i,j}\neq a_{n-i+1,n-j+1})\over 2$$

那么，当我们算出次数之后，如果给定的次数不够用，那么一定无解。

但是其他情况下也不都有解。

当 $n\bmod 2=1$ 时，最中心一格永远与自己中心对称，无论多多少次，直接将最中心一个进行不停反转即可。

但是当 $n\bmod 2=0$ 时，必须使得剩下的次数是偶数次，才能使得左右抵消，两两进行翻转，否则则不能完成。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;
  
const int N = 1005;

bool b[N][N];
 
void solve() {
	memset(b,0,sizeof b);
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			cin>>b[i][j];
	int ct=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(b[i][j]!=b[n+1-i][n+1-j])
				ct++;
	ct/=2;
	if(k>=ct&&((k-ct)%2==0||n%2==1)) cout<<"Yes\n";
	else cout<<"No\n";
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin>>t;
    while (t--) solve();
    return 0;
}
```


---

