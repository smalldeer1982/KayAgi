# Fish Weight

## 题目描述

It is known that there are $ k $ fish species in the polar ocean, numbered from $ 1 $ to $ k $ . They are sorted by non-decreasing order of their weight, which is a positive number. Let the weight of the $ i $ -th type of fish be $ w_{i} $ , then $ 0&lt;w_{1}<=w_{2}<=...<=w_{k} $ holds.

Polar bears Alice and Bob each have caught some fish, and they are guessing who has the larger sum of weight of the fish he/she's caught. Given the type of the fish they've caught, determine whether it is possible that the fish caught by Alice has a strictly larger total weight than Bob's. In other words, does there exist a sequence of weights $ w_{i} $ (not necessary integers), such that the fish caught by Alice has a strictly larger total weight?

## 说明/提示

In the first sample, if $ w_{1}=1,w_{2}=2,w_{3}=2.5 $ , then Alice has a total of $ 2+2+2=6 $ weight units, while Bob only has $ 1+1+2.5=4.5 $ .

In the second sample, the fish that Alice caught is a subset of Bob's. Therefore, the total weight of Bob’s fish is always not less than the total weight of Alice’s fish.

## 样例 #1

### 输入

```
3 3 3
2 2 2
1 1 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 7 9
5 2 7 3
3 5 2 7 3 8 7
```

### 输出

```
NO
```

# 题解

## 作者：Morax2022 (赞：3)

# CF297B 题解
设 Alice 抓了 $n$ 条鱼， Bob 抓了 $m$ 条。

若 $n > m$ 直接输出 yes。

反之，若有 $k$ 种鱼 Alice 抓的大于 Bob 抓的，将这些值置于极大，将其他值置为 $0$，则必有 Alice 的鱼重量大于 Bob 的。否则一定不行。

# AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, k, a[1000001], b[1000001];
main()
{
	ios::sync_with_stdio(0); //关闭流同步
	cin.tie(0); cout.tie(0);
	cin >> n >> m >> k;
	if (n > m)
	{
		cout << "YES";
		return 0;
	 } 
	 for (int i = 1; i <= n; i++) cin >> a[i];
	 for (int i = 1; i <= m; i++) cin >> b[i];
	 sort(a + 1, a + n + 1); sort(b + 1, b + m + 1);
	 for (int i = 1; i <= n; i++)
	 {
	 	if (a[i] > b[m - n + i])
	 	{
	 		cout << "YES"; 
	 		return 0;
		 }
	 }
	 cout << "NO";
}
```
希望本题解能给大家带来帮助！

---

## 作者：KXY_Moon (赞：2)

## 解法

十分简单的推论好题。

分类讨论一下各种情况的做法：

先假设 Alice 对于 $i$ 种鱼抓了 $x_i$ 条鱼，

Bob 对于 $i$ 种鱼抓了 $y_i$ 条鱼。

那么有：

 - 若 $x_{总和}>y_{总和}$，输出```YES```。
 - 若有 $k$ 种鱼且 $x_k>y_k$，输出```YES```。
 - 否则输出```NO```。

## 代码：


```cpp
# include<bits/stdc++.h>
using namespace std;
const int n=1e6+5;
#define int long long
int x,y,k,p[n],r[n];
signed main()
{   scanf("%d",&x,&y,&k);
	if(x>y) cout<<"YES";
	else{ for(int i=1;i<=x;i++) cin>>p[i];
	    for(int i=1;i<=y;i++) cin>>r[i];
	    sort(p+1,p+x+1); sort(r+1,r+y+1);
	    for(int i=1;i<=x;i++){
		    if(p[i]>r[y-x+i]) cout<<"YES";
		    else cout<<"NO";}
	}return 0;
}
```
End.

---

## 作者：shenmadongdong (赞：1)

考虑如果存在一个值，使得 Alice 抓的权值不小于这个值的鱼的数目比Bob多，那么只要使得这个权值以下的鱼重量都为 0 ，以上重量都为极大值即可。

否则 Alice 的序列将严格小于 Bob,肯定不可能

代码：

```cpp
#include <bits/stdc++.h>
#define rd(a) a=read()
#define ll long long
using namespace std;
ll read(){ll x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
ll n,m,k,a[1000010],b[100010];
int main()
{
	cin>>n>>m>>k;
	if (n>m) return puts("YES"),0;//如果Alice抓的鱼比Bob多，那么一定可能
	for(int i=1;i<=n;i++) rd(a[i]);
	for(int i=1;i<=m;i++) rd(b[i]);
	sort(a+1,a+n+1);
    sort(b+1,b+m+1);//排序
	for(int i=1;i<=n;i++) if (a[i]>b[m-n+i]) return puts("YES"),0;//比较Alice抓的鱼与Bob抓的鱼中重量最大的
	puts("NO");
	return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：1)

	由于是 0 < w1 ≤ w2 ≤ ... ≤ wk。
    
	当B中排序最后的鱼序号有大于A排序最后的鱼，那么将B的这鱼重量和A当前最大的鱼定为相等，则这两条鱼的重量相抵消。所以如果这么做，只要A还有鱼，就能保证每次B所有的总重量都不会大于A的总重量。这么抵消下去，一旦A有条鱼的序号大于B所剩的所有鱼，那么A就可以胜利了。因为可以令小于A这条鱼的所有鱼重量无穷小。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k,a[100005],b[100005];
bool fxt()
{
	while (m && n && b[m]>=a[n]) 
	{
		m--;
		n--;
	}
	if (n && (!m || a[n]>b[m])) 
	{
		return true;
	}
	return false;
}
int main()
{      
	int i,j;
	cin>>n>>m>>k;
	for (i=1;i<=n;i++) 
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for (i=1;i<=m;i++)
	{
		cin>>b[i];
	}
	sort(b+1,b+m+1);
	if (fxt()) 
	{
		cout<<"YES\n";
	}
	else
	{
		cout<<"NO\n";
	}
	return 0;
}

```

---

## 作者：freedom_wang (赞：0)

### 思路：
当 $n>m$ 时：显然正确。

只要存在 $k$ 使得 Alice 抓第 $k$ 种鱼的数量比 Bob 多，那么第 $k$ 种鱼的重量设为正无穷，Alice 就比 Bob 抓到的鱼重量更高。
### AC Code:
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n,m,k,a[100005],b[100005];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	rep(i,1,n)
		cin>>a[i];
	rep(i,1,m)
		cin>>b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	if(n>m){
		cout<<"YES";
		return 0;
	}
	rep(i,1,n)
		if(a[i]>b[m-n+i]){
			cout<<"YES";
			return 0;
		}
	cout<<"NO\n";
	return 0;
}
```

---

## 作者：Fuxh_18 (赞：0)

## [原题](https://www.luogu.com.cn/problem/CF297B)
$\texttt{Alice}$ 抓了 $n$ 条鱼，$\texttt{Bob}$ 抓了 $m$ 条鱼。问 $\texttt{Alice}$ 可不可能比 $\texttt{Bob}$ 抓的鱼重。
## 思路
分类讨论：

1. 如果 $n > m$，肯定可能。
2. 否则，把他们鱼的编号从大到小排序，如果 $\texttt{Alice}$ 的第 $i$ 条鱼的编号比 $\texttt{Bob}$ 的第 $m-n+i$ 条鱼的编号大，就可能。如果都不满足，就不可能。
## [AC](https://www.luogu.com.cn/record/168270734) Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
int a[N],b[N];
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	if(n>m){ //第 1 种情况 
		cout<<"YES";
		return 0;
	}
	sort(a+1,a+1+n);
	sort(b+1,b+1+m);
	for(int i=1;i<=n;i++){
		if(a[i]>b[m-n+i]){ //满足，直接输出 YES 
			cout<<"YES";
			return 0;
		}
	}
	cout<<"NO"; //没有满足情况，输出 NO 
	return 0;
}
```
~~达成成就，结束了？~~

---

## 作者：liuli688 (赞：0)

### 思路
首先，由于鱼的重量能够自己选定，所以实际上我们只要构造符合题目的解即可。

如果 $n > m$，也就是 Alice 的鱼比 Bob 的多，又因为鱼的重量是**单调不降**而不是**单调上升**，所以我们只要将所有鱼的重量设为一样，即可达到目标。

否则，我们需要运用贪心思想：如果 Alice 拥有最重的鱼，那么将这条鱼的重量设为 $1$，剩下的重量设为 $0$ 即可。

那么又有问题：没有最重的鱼怎么办？没有最重的鱼，但有几种重量排名都在最前的鱼，那么只需要将这几种鱼重量设为 $1$，剩下的重量设为 $0$。

总结一下：如果 Alice 有一种鱼的数量大于 Bob 的数量，那么将这种鱼重量设为 $1$，剩下的设为 $0$。否则不能构造符合要求的解。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define reg register

constexpr int MAX = 1e5 + 1;
int n,m,k,a[MAX],b[MAX];

signed main()
{
    reg int i;
    scanf("%d%d%d",&n,&m,&k);
    if(n > m)
    {
        printf("YES");
        return 0;
    }
    for(i = 0;i < n;++i)
        scanf("%d",&a[i]);
    for(i = 0;i < m;++i)
        scanf("%d",&b[i]);
    sort(a,a + n);
    sort(b,b + m);
    for(i = 0;i < n;++i)
        if(a[i] > b[m-n+i])
        {
            printf("YES");
            return 0;
        }
    printf("NO");
    return 0;
}
```

---

## 作者：_xxxxx_ (赞：0)

### 题意

Alice 和 Bob 在一起抓鱼，Alice 抓了 $n$ 条，Bob 抓了 $m$ 条。每条鱼都有种类，现在知道 Alice 和 Bob 抓的每条鱼的种类，问是否可以构造出一组鱼的重量，使相同种类的鱼的重量相同，最终使得 Alice 抓的鱼的总重量大于 Bob 抓的鱼的总重量。

### 分析

构造题，但是不用输出解，考虑找规律。

首先发现，如果 $n>m$，即 Alice 的鱼比 Bob 的多，每条鱼重量都为一个相同数就可以实现。

每种鱼都是相同重量，这句话非常关键。

每种鱼都是相同重量，我们看 Alice 是否有一种鱼的个数大于 Bob 所拥有的这种鱼的个数，如果有，将这种鱼的重量设为正无穷，那自然就满足了。

现在只需要找一种鱼合法就可以了。我们把他们抓到的鱼排序，看是否有 $a_i>b_{m-n+i}$，有就找到一个大于的了，相同种类的鱼会被滤掉。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
const int N = 1e5 + 10;
using namespace std;
int n, m, k;
int a[N], b[N];
signed main()
{
	cin >> n >> m >> k;
	if(n > m)
	{
		puts("YES");
		exit(0);
	}
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) cin >> b[i];
	sort(a + 1, a + n + 1);
	sort(b + 1, b + m + 1);
	for(int i = 1; i <= n; i++)
	{
		if(a[i] > b[m - n + i])//找到了 
		{
			puts("YES");
			exit(0);
		}
	}
	puts("NO");
	return 0;
}
/*
2 3 5 7
2 3 3 5 7 7 8
*/
```

---

## 作者：xuduang (赞：0)

简单构造题。

显然如果 A 抓的鱼比 B 多，那么一定合法，可以全部种类重量设成 $1$。

寻找一个种类 $x$，使得 $x$ 被 A 抓的次数比 B 抓的多，把 $x$ 的重量设为无限大即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k;
int a[100005],b[100005];
int main()
{
	cin>>n>>m>>k;
	if(n>m)
	{
		printf("YES");
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=1,j=m-n+1;i<=n,j<=m;i++,j++)
	{
		//寻找A数量大于B的鱼x 
		if(a[i]>b[j])
		{
			printf("YES");
			return 0;
		}
	}
	printf("NO");
	return 0;
}
```

---

## 作者：卷王 (赞：0)

一道超级简单的结论题。

我们来分两种情况讨论：

* 如果 $m<n$。输出 `YES`。可以把所有 $w_i$ 都设为 $1$，显然这时 $a$ 数组大。

* 否则，即 $m\ge n$。可以发现，把 $a$ 和 $b$ 数组从大到小排序后，可以发现，只要有一个 $b_i < a_i$，把 $w_{a_i}$ 赋为尽可能大的数后，总是有方法让 $a$ 数组大，输出 `YES`。最后，如果对于所有 $i(1\le i\le n)$， $b_i\ge a_i$，那就没有办法了，输出 `NO`。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
int a[100007], b[100007];

inline bool cmp(int x, int y) {
	return x > y;
}

signed main() {
	n = read(), m = read(), k = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= m; i++) b[i] = read();
	if(m < n) {
		cout << "YES";
		return 0;
	}
	sort(a + 1, a + n + 1, cmp);
	sort(b + 1, b + m + 1, cmp);
	for(int i = 1; i <= n; i++)
		if(b[i] < a[i]) {
			cout << "YES";
			return 0;
		}
	cout << "NO";
	return 0;
}
```

---

## 作者：Samhu07 (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF297B)&[CF 链接](https://codeforces.com/problemset/problem/297/B)

## 题目简述

海洋中有 $k$ 种鱼类，下标从 $1 \sim k$ 。保证为递增正数列。$\text{Alice}$ 和 $\text{Bob}$ 各自抓了一些鱼。判断 $\text{Alice}$ 抓的鱼的重量之和能否比 $\text{Bob}$ 大。

## 思路

**分类讨论**。

当 $N > M$ 时，**直接输出** `YES` 即可。

而当 $N \le M$ 时需要思考一下，如果**存在** $\text{Alice}$ 抓的鱼比 $\text{Bob}$ 抓的大，那么仅需把这种鱼的**重量放很大**，而其它是 $0$ 即可使 $\text{Alice}$ 的价值比 $\text{Bob}$ 大。如果**不存在**这种情况，输出 `NO` 即可。

**时间复杂度 $O(N)$ 可以通过**。

经过以上分析，很容易即可得出**代码**了：

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define fo(i,x,y) for(int i = x;i<=y;i++)
#define go(i,x,y) for(int i = x;i>=y;i--)
const int inf = 2147483647;
const int mod = 1000000007;
using namespace std;
int n,m,k,a[100005],b[100005];
int main(){
	scanf("%d%d%d",&n,&m,&k);
    if(n>m) {
        printf("YES\n");// 特判
        return 0;
    } 
    // 输入
    fo(i,1,n)
    	scanf("%d",&a[i]);
    fo(i,1,m)
    	scanf("%d",&b[i]);
    // 排序
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    // 遍历 N 判断情况 2 是否存在
    fo(i,1,n)
        if(a[i]>b[m-n+i]){
            printf("YES\n"); // 存在直接输出结束
            return 0; 
        }
    printf("NO\n"); // 不存在，换行好习惯
}
```

$$\text{The End!}$$

---

## 作者：Composite_Function (赞：0)

# 题意

海洋中有 $k$ 种鱼类，下标从 $1$ 到 $k$ 。保证为递增正数列。$\texttt{Alice}$ 和 $\texttt{Bob}$ 各自抓了一些鱼。判断 $\texttt{Alice}$ 抓的鱼的重量之和能否比 $\texttt{Bob}$ 大。

------------

# 思路

如果 $\texttt{Alice}$ 抓的鱼数比 $\texttt{Bob}$ **多**，那么**把所有设为一样**，直接成立，输出 $\texttt{YES}$。

否则，求其**极端值**。 $\forall 1 \leq i \leq n ~~ a_i>b_{m - n + i}$，即 $\texttt{Alice}$ 的下一条鱼比 $\texttt{Bob}$ 大，就说明一定有解，输出 $\texttt{YES}$。

判断到了最后，以上两种情况**都不满足**，输出 $\texttt{NO}$。

------------

# AC 代码

**最激动的环节~**

由于上面已经说了，就不写注释了。

```cpp
//有点压行，凑合着看看吧
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100010;
int n,m,k,a[N],b[N];
signed main(){
    cin>>n>>m>>k;
    if(n>m){cout<<"YES"<<endl;return 0;}
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>b[i];
    sort(a+1,a+n+1),sort(b+1,b+m+1);
    for(int i=1;i<=n;i++)
        if(a[i]>b[m-n+i])
            {cout<<"YES"<<endl;return 0;}
    cout<<"NO"<<endl;
    return 0;
}
```

------------

# 总结

$\texttt{codeforces}$ 的难题不考复杂的代码，考的是复杂的思维，还是要多思考。

------------

最后——

千山万水总是情，给个点赞行不行~~

---

## 作者：XL4453 (赞：0)

### 解题思路：

首先如果 $n>m$，也就是第一个人抓的鱼比第二个人多，那么只需要将所有的鱼的重量设为一样就行了。

反之如果存在某一个值，使得第一个人抓到的比这个重量大的鱼比第二个人多，那么可以将这个重量之前的鱼的重量设为一个极大，从而达到使得第一个人抓的鱼更重的目的。

---
实现上，每一次将双方最重的两种鱼取出，然后比较两者鱼的多少，若第一个人的鱼比第二个人的多，那么就有解。

为了方便书写，我采用的方法是每一次取出一条鱼，如果第一个人的下一条鱼的编号比第二个人大，那么说明至少还能取出一条，也就是有解。

---
### 代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[100005],b[100005],m,k;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)scanf("%d",&b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	if(n>m){
		printf("YES\n");
		return 0;
	}
	while(n){
		if(a[n]>b[m]){
			printf("YES\n");
			return 0;
		}
		n--;
		m--;
	}
	printf("NO\n");
	return 0;
}
```


---

