# Shift and Reverse

## 题目描述

Given an array of integers $ a_1, a_2, \ldots, a_n $ . You can make two types of operations with this array:

- Shift: move the last element of array to the first place, and shift all other elements to the right, so you get the array $ a_n, a_1, a_2, \ldots, a_{n-1} $ .
- Reverse: reverse the whole array, so you get the array $ a_n, a_{n-1}, \ldots, a_1 $ .

Your task is to sort the array in non-decreasing order using the minimal number of operations, or say that it is impossible.

## 说明/提示

In the first test case of the example, to sort the array \[ $ 3, 2, 1, 5, 4 $ \] you need to perform $ 3 $ operations:

- Shift to obtain the array \[ $ 4, 3, 2, 1, 5 $ \];
- Shift to obtain the array \[ $ 5, 4, 3, 2, 1 $ \];
- Reverse to obtain the array \[ $ 1, 2, 3, 4, 5 $ \].

In the third test case of the example, it can be shown that it is impossible to sort the array using the given operations.

In the seventh test case of the example, to sort the array \[ $ 4, 1, 3, 4, 4 $ \] you need to perform $ 3 $ operations:

- Reverse to obtain the array \[ $ 4, 4, 3, 1, 4 $ \];
- Shift to obtain the array \[ $ 4, 4, 4, 3, 1 $ \];
- Reverse to obtain the array \[ $ 1, 3, 4, 4, 4 $ \].

## 样例 #1

### 输入

```
11
5
3 2 1 5 4
5
1 1 2 1 1
4
3 7 10 5
5
1 2 3 4 5
2
5 1
3
3 4 1
5
4 1 3 4 4
3
5 1 1
4
2 5 5 4
5
2 2 1 1 2
2
5 5```

### 输出

```
3
2
-1
0
1
1
3
1
2
2
0```

# 题解

## 作者：bigclever (赞：6)

## 思路：
我们可以把 $a$ 序列当做一个环，可以发现无论是移位还是翻转操作都不能改变**环上元素的相对顺序和大小关系**。所以如果一开始环上元素就无法满足**单调性**，则无论如何都无法使数组变为单调不降。考虑完无解情况，接下来考虑最小操作次数：

1. 若整个序列形如 $a_1,a_2 \dots a_n(a_i \le a_{i+1})$，那么数组本身即为单调不降，无需操作。
2. 若整个序列形如 $a_1,a_2 \dots a_n(a_i \ge a_{i+1})$，那么数组本身即为单调不升，只需翻转一次即可。
3. 若整个序列形如 $a_1 \le a_2 \le a_3 \le \dots \le a_{x-2} \le a_{x-1},a_{x-1} \ge a_x,a_x \le a_{x+1} \le a_{x+2} \le \dots \le a_{n-1} \le a_n \le a_1$，那么此时分为两种情况：
- 将最后面的 $n-x+1$ 个数依次移位到数列最前面，此时操作次数为 $n-x+1$。
- 先翻转一次，将后面的 $x-1$ 个数移位到数列最前面，再翻转回去，此时操作次数为 $1+(x-1)+1=x+1$。

4. 若整个序列形如 $a_1 \ge a_2 \ge a_3 \ge \dots \ge a_{x-2} \ge a_{x-1},a_{x-1} \le a_x,a_x \ge a_{x+1} \ge a_{x+2} \ge \dots \ge a_{n-1} \ge a_n \ge a_1$，那么此时分为两种情况：
- 将最后面的 $n-x+1$ 个数依次移位到数列最前面，然后再翻转一次，此时操作次数为 $n-x+2$。
- 先翻转一次，将后面的 $x-1$ 个数移位到数列最前面，此时操作次数为 $x$。
5. 如果序列不属于上述任意一种情况，则不满足单调性，此时无解。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main(){
	int t; scanf("%d",&t);
	while(t--){
		int n; scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",a+i);
		int cntd=0,idd,cntx=0,idx;
		for(int i=1;i<n;i++)
			if(a[i]>a[i+1])cntd++,idd=i+1;
			else if(a[i]<a[i+1])cntx++,idx=i+1;
		if(!cntd){puts("0");continue;}
		if(!cntx){puts("1");continue;}
		if(cntd>1&&cntx>1){puts("-1");continue;}
		int ans=1e9;
		if(cntd==1&&a[1]>=a[n])ans=min({ans,idd+1,n-idd+1});//将所有情况的操作次数取min，最小的即为答案
		if(cntx==1&&a[1]<=a[n])ans=min({ans,idx,n-idx+2});//同上
		printf("%d\n",ans==1e9?-1:ans);
	}
	return 0;
}
```

---

## 作者：Eazin_star (赞：4)

### 思路
把这个序列当成一个圆，可以发现第一种操作并没有改变序列，第二种操作只改变正逆序。因此知道如果序列最开始不是正序或逆序，则不能变为有序数列。而对于可以改变的序列，我们要找到序列的起始点，再判断最优即可。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, t, a[200005];

int main() {
    scanf("%d", &t);
    while(t--) {
    	scanf("%d", &n);
	    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), a[i+n] = a[i]; //将数组倍长，模拟圆
	    int up = 1, down = 1, now = 0, ans = 2*n;
	    for (int i = 2; i <= 2*n; i++) { //遍历看是先改变位置再倒序最优还是先倒序再改变位置最优
	        if (a[i] > a[i-1]) up++, down = 1;
	        else if (a[i] < a[i-1]) up = 1, down++;
	        else up++, down++;
	        if (up >= n || down >= n) { //更新最小值
	            if (down >= n) ans = min(ans, min(2*n-i+1,i-n+1)); 
	            if (up >= n) ans = min(ans, min(2*n-i,2+i-n));
	        }
	    }
	    if (ans != 2*n) printf("%d\n", ans); //如果可以则输出最小值
	    else puts("-1"); 否则输出-1
	}
    return 0;
}
```


---

## 作者：xlpg0713 (赞：3)

## 题意
对于数组 $a$，可以将其整体反转或者是向右移一位，即对于 $\forall_{1\le i<n} a[i]\rightarrow a[i+1], a[n] \rightarrow a[1]$。问是否可通过最少的次数将数组升序排序。

## 题解
发现向右移操作是建立在环上的，且反转操作和右移操作均不影响环上元素的相对顺序，判断如果环上元素是非单调的则无解，否则原数组可以表示为两个单调不降或不升序列拼在一起，分类之：

若原数组升序，序列的断点在 $p$，则有：$rs=\min(n-p+1,p+1)$。

前者后者分别对应直接转过去，先翻转一次在转成下降序列再反转回来。

原数组降序可同理推得。

易于证明，这样的做法是 $O(n)$ 的，复杂度在于判断合法和找到断点。

```cpp
#include<algorithm>
#include<iostream>
using std::min;
int t, n, cu, cd, pu, pd, a[100005];
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);std::cout.tie(0);
    std::cin >> t;
    while(t--){
        std::cin >> n; cu = cd = pu = pd = 0;
        for(int i = 1; i <= n; i++) std::cin >> a[i];
        for(int i = 1; i < n; i++)
            if(a[i] > a[i + 1]) ++cu, pu = i + 1;
        for(int i = 1; i < n; i++)
            if(a[i] < a[i + 1]) ++cd, pd = i + 1;
        if(cu == 0) {std::cout << "0\n"; continue;}
        if(cd == 0) {std::cout << "1\n"; continue;}
        if(cu > 1 && cd > 1) {std::cout << "-1\n"; continue;}
        int rs = 0x7fffffff;
        if(cu == 1 && a[1] >= a[n]) rs = min(rs, min(n - pu + 1, pu + 1));
        if(cd == 1 && a[1] <= a[n]) rs = min(rs, min(n - pd + 2, pd));
        std::cout << (rs == 0x7fffffff ? -1 : rs) << '\n';
    }
}
```

---

## 作者：abensyl (赞：2)

原题：[CF1907F Shift and Reverse](https://www.luogu.com.cn/problem/CF1907F)。

想到了一周之前做的一道题目：[AT_abc190_f Shift and Inversions](https://www.luogu.com.cn/problem/AT_abc190_f)，于是我就用一种特殊的思路解决了这道题目。

## 思路

看过 [Shift and Inversions](https://www.luogu.com.cn/problem/AT_abc190_f) 这道题目之后，可以启发我们从另一个思路考虑最终我们要使得序列单调递增的这个要求，排成正序不就是逆序对数量为 $0$ 吗？

那么，先考虑 Reverse 操作，首先要明确最多使用几次，经过分类讨论可以发现，最多使用 $2$ 次 Reverse 操作，并且，这两次操作只可能排在头尾，大致分为以下四种情况：

1. 不使用 Reverse，操作序列为 $\text{S\dots S}$；  
2. 使用 $1$ 次 Reverse，操作序列为 $\text{RS\dots S}$；  
3. 使用 $1$ 次 Reverse，操作序列为 $\text{S\dots SR}$；  
4. 使用 $2$ 次 Reverse，操作序列为 $\text{RS\dots SR}$； 

（其中，R 就代表 Reverse 操作，S 就代表 Shift 操作）

这样的话，我们就分四类进行一下讨论就可以了，其中把情况 $1$ 和情况 $2$，视作一类，因为他们在排序后都是正序，而另外两类都是倒序，需要最后再 Reverse 一次。

对于正序，逆序对的数量应为 $0$，对于倒序，可以预处理出逆序对数量，当你尝试 Shift 一定的次数后达到了预期的逆序对数量，那么操作结束，否则，继续操作，如果 Shift 了 $n$ 次，也就是说 Shift 了整整一轮之后仍然没有达到预期，那么这种情况就是不可能满足的。

对于所有可能满足的情况，求出他们操作次数的最小值，如果四种情况都不行，就输出 `-1`，别忘了，Reverse 也算是一次操作哦。

用树状数组求逆序对，时间复杂度 $\Theta (n\log n)$，虽然多一个 log，但是我觉得我的思路更容易理解。

## 代码
```cpp
struct BIT{
	ll N;
	ll a[maxn];	
	void init() {
		for(int i=1;i<=N;i++) a[i] = 0; 
	}
	void add(ll p,ll x) {
		while(1 <= p && p <= N) {
			a[p] += x;
			p += lowbit(p);
		}
	}
	ll query(ll p) {
		ll ret = 0;
		while(p > 0) {
			ret += a[p];
			p -= lowbit(p);
		}
		return ret;
	}	
	ll query(ll l,ll r) {
		return query(r)-query(l-1);
	}
}t;
int n,m,a[maxn],b[maxn];
int find(int aim) {
	t.init();
	ll s=0;
	for(int i=n;i>=1;--i) {
		s+=t.query(a[i]-1);
		t.add(a[i],1);
	}
	if(s==aim) return 0;
	for(int i=n,j=1;i>=1;--i,++j) {
		s+=t.query(a[i]-1);
		s-=t.query(a[i]+1,n);
		if(s==aim) return j;
	} return 1e9;
}
int qnxd() {
	ll s=0;
	t.init();
	for(int i=n;i>=1;i--) {
		s+=t.query(a[i]-1);
		t.add(a[i],1);
	} return s;
}
int solve() {
	for(int i=1;i<=n;++i) b[i]=a[i];
	sort(a+1,a+n+1);
	int ta=qnxd();
	reverse(a+1,a+n+1);
	int tb=qnxd();
	for(int i=1;i<=n;++i) a[i]=b[i];
	int res1=find(ta)+(ta!=0);
	int res2=find(tb)+(tb!=0);
	return min(res1,res2);
}
void Solve() {
	cin>>n,t.N=n;
	vector<int> v;
	for(int i=1;i<=n;++i)
		cin>>a[i],v.push_back(a[i]);
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(int i=1;i<=n;++i) a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
	int res1=solve();
	reverse(a+1,a+n+1);
	int res2=solve()+1;
	if(min(res1,res2)>1e8) cout<<"-1\n";
	else cout<<min(res1,res2)<<'\n';
}
```
[我的 AC 记录](https://codeforces.com/contest/1907/submission/235925096)。 

---

## 作者：Tjaweiof (赞：1)

# CF1907F 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1907F)

我们把序列 $a$ 想象成环形的，那么【移位】就变成了旋转，【翻转】就是把旋转的方向变一下。

那么这道题就很简单了。首先判断把序列 $a$ 拼成一个环形再断开是否能成为一个单调不下降序列。如果能，找到需要断开的位置，计算答案即可（具体见代码）；否则输出 `-1`。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int t, n, a[200001], ans, res;
bool cnt;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--){
		cin >> n;
		for (int i = 1; i <= n; i++){
			cin >> a[i];
		}
		ans = 0x3f3f3f3f;
		cnt = false;
		res = 0;
		for (int i = 2; i <= n; i++){
			if (a[i - 1] > a[i]){
				if (cnt){
					res = 0x3f3f3f3f;
					break;
				}
				cnt = true;
				res = min(n - i + 1, i + 1);
			}
		}
		if (cnt && a[1] < a[n]){
			res = 0x3f3f3f3f;
		}
		ans = min(ans, res);
		cnt = false;
		res = 1;
		for (int i = n - 1; i >= 1; i--){
			if (a[i + 1] > a[i]){
				if (cnt){
					res = 0x3f3f3f3f;
					break;
				}
				cnt = true;
				res = min(i + 1, n - i + 1);
			}
		}
		if (cnt && a[n] < a[1]){
			res = 0x3f3f3f3f;
		}
		ans = min(ans, res);
		if (ans == 0x3f3f3f3f){
			cout << "-1\n";
		} else {
			cout << ans << "\n";
		}
	}
	return 0;
}
```

---

## 作者：cosf (赞：0)

我们先看看是否可行。

很显然，最后的 $a$ 数组一定是一下之一（$a_0 = a_n, 1 \le t \le n$）：

$$
\begin{cases}
a_t \le a_{t + 1} \le \dots \le a_n \le a_1 \le a_2 \le \dots \le a_{t - 1}\\
a_{t - 1} \le \dots \le a_2 \le a_1 \le a_n \le \dots \le a_{t + 1} \le a_t
\end{cases}
$$

很容易想到，如果 $a$ 中存在 $\gt 1$ 个 $1 \le i \le n$ 使得 $a_i \gt a_{i + 1}$，则它不可能成为第一种情况。反之，如果 $a$ 中存在 $\gt 1$ 个 $1 \le i \le n$ 使得 $a_i \lt a_{i + 1}$，则它不可能成为第二种情况。

如果可以写成第一种情况，假设满足 $a_i \gt a_{i + 1}$ 的 $i$ 为 $s$（不存在假定为 $n$），则现在有三种选择：

- 直接不断移位，操作数为 $n - s$。
- 翻转后移位再翻转，操作数为 $s + 2$。
- 如果 $s=n$，则 $a$ 本身就满足条件，$0$ 步即可。

如果可以写成第二种情况，假设满足 $a_i \lt a_{i + 1}$ 的 $i$ 为 $s$（不存在假定为 $0$），则现在有两种选择：

- 先翻转再移位，操作数为 $s + 1$。
- 先移位再翻转，操作数为 $n - s + 1$。

再综合一下即可。

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 100005

int n;

int val[MAXN];

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> val[i];
    }
    val[n + 1] = val[1];
    int c[2] = {}, s[2] = {n};
    for (int i = 1; i <= n; i++)
    {
        if (val[i] > val[i + 1])
        {
            c[0]++;
            s[0] = i;
        }
        if (val[i] < val[i + 1])
        {
            c[1]++;
            s[1] = i;
        }
    }
    if (c[0] > 1 && c[1] > 1)
    {
        cout << -1 << endl;
        return;
    }
    int res = MAXN;
    if (c[0] < 2)
    {
        res = min({
            s[0] % n + 2 * (s[0] != n),
            n - s[0],
        });
    }
    if (c[1] < 2)
    {
        res = min({
            res,
            s[1] % n + 1,
            n - s[1] + 1,
        });
    }
    cout << res << endl;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

```

---

## 作者：tmp_get_zip_diff (赞：0)

我们可以通过最终结果倒推出可能的状态。

最终结果必然是一个单调不降序列，比如说这一个状态：

![](https://cdn.luogu.com.cn/upload/image_hosting/jb15dfaz.png)

也就是说，必然存在一个点 $p_1 \in [1,n]$，$[1,p_1)$ 单调不降，$[p_1,n]$ 也单调不降，且满足 $a_1 \ge a_n$。

但是如果没有一个 $p_1$ 满足条件呢？我们可以将数组反转过来用类似的方法求出 $p_2$。

- 如果 $p_1=1$，也就是整个序列本来就是单调不降的，此时答案为 $0$。
- 如果 $p_2=1$，代表整个序列单调不升，翻转一次，答案为 $1$。
- 如果 $p_1>1$ 且 $a_1 \ge a_n$，那么可以直接将后面的部分一个一个移到前面来，也可以先反转数组，再将其变为不升序列再反转回来。
- 如果 $p_2>1$ 且 $a_n \ge a_1$，那么既可以先反转再一个一个挪，也可以先变为不下降序列，再反转。
- 如果第 $3,4$ 种同时满足，那么 $3,4$ 种的所有情况取 $\min$ 即可。

按照上面的模拟，$T$ 组数据，代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=2e5+5;
int n,a[N],af[N];

pair<int,int> help(int p[])
{
	int num=1,pos=0;
	for(int i=2;i<=n;i++)
		if(p[i-1]>p[i])
			num++,pos=i;
	return {num,pos};
}

void Work()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		af[n-i+1]=a[i];
	}
	auto k1=help(a);
	auto k2=help(af);
	if(k1.first==1)
		puts("0");
	else if(k2.first==1)
		puts("1");
	else if(k1.first==2&&k2.first==2&&a[1]==a[n])
		cout<<min({k1.second+1,n-k1.second+1,k2.second,n-k2.second+2})<<"\n";
	else if(k1.first==2&&a[1]>=a[n])
		cout<<min(k1.second+1,n-k1.second+1)<<"\n";
	else if(k2.first==2&&a[n]>=a[1])
		cout<<min(k2.second,n-k2.second+2)<<"\n";
	else
		puts("-1");
	return ;
}

signed main()
{
	int T;
	cin>>T;
	while(T--)
		Work();
	return 0;
}
```

---

## 作者：Ericby666 (赞：0)

## [题目链接](https://www.luogu.com.cn/problem/CF1907F)
如果把 $a$ 序列当成一个环，那么移位不会改变序列，翻转只会改变正逆序，所以如果环上的元素不满足单调性，则无法通过若干次操作使得 $a$ 单调不降。

如果环上元素满足单调性，则此时分为四种情况。

1.如果 $a$ 本身单调不降，则不需要进行操作（即进行 $0$ 次操作）。

2.如果 $a$ 本身单调不升，则需要进行 $1$ 次操作（翻转 $1$ 次）。

3.如果 $a$ 中有一个元素大于它的后一个元素，其余元素都小于等于它的后一个元素（$a$ 的最后一个元素除外）。

不妨设该元素的位置为 $x$，则此时要么将 $x$ 之后的元素全部移位（操作次数为 $n-x+1$ 次）。要么先翻转 $1$ 次，把 $x$ 之前的元素全部移位，再翻转 $1$ 次（操作次数为 $1+\left(x-1\right)+1=x+1$ 次）。两者取最小值即可。

4.如果 $a$ 中有一个元素小于它的后一个元素，其余元素都大于等于它的后一个元素（$a$ 的最后一个元素除外）。

不妨设该元素的位置为 $x$，则此时要么将 $x$ 之后的元素全部移位，再翻转 $1$ 次（操作次数为 $\left(n-x+1\right)+1=n-x+2$ 次）。要么先翻转 $1$ 次，再将 $x$ 之前的元素全部移位（操作次数为 $1+\left(x-1\right)=x$ 次）。两者取最小值即可。

AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[100005];
int main(){
    scanf("%d",&t);
    while(t--){
        int n,sh=0,xi=0,ps,px,ans=2e9;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        for(int i=2;i<=n;i++){
            if(a[i]<a[i-1]){
                sh++;
                ps=i;//第3种情况中的x
            }
            else if(a[i]>a[i-1]){
                xi++;
                px=i;//第4种情况中的x
            }
        }
        if(sh==0)printf("0\n");
        else if(xi==0)printf("1\n");
        else if(sh>1 && xi>1)printf("-1\n");//不满足单调性
        else{
            if(sh==1 && a[1]>=a[n])ans=min({ans,ps+1,n-ps+1});
            if(xi==1 && a[n]>=a[1])ans=min({ans,px,n-px+2});
            if(ans==2e9)printf("-1\n");//不符合任意一种情况
            else printf("%d\n",ans);
        }
    }
    return 0;
}
```

---

## 作者：Dawn_cx (赞：0)

题意：对于一个序列，你可以做两种操作，第一种是把最后一个放到最前面，第二种是把整个序列倒序，问最少用几次操作可以把数列变为从小到大的有序序列。不能变则输出 $-1$。

如果把这个序列当成循环序列，不难发现第一种操作没有改变序列，第二种操作只是改变了顺序和倒序，因此如果序列最开始不是顺序或逆序，则不能变为有序数列。

对于可以改变的序列，我们要找到序列的起始点，再分别判断先改变位置再倒序和先倒序再改变位置哪个更优，输出操作次数最少的那个即可。

赛时有点困想出来的时候还有五分钟，再加上想出来的方法比较麻烦所以就没做这个题，实际上直接倍长数组就比较方便。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5+10;
const ll mod = 998244353;
inline void read(int &x){
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){s=(s<<3)+(s<<1)+(ch&15);ch=getchar();}
    x=s*w;
}
int n,t,a[N<<1];
void solve(){
    read(n);
    for(int i=1;i<=n;i++)read(a[i]),a[i+n]=a[i];
    int b=1,s=1,now=0,ans=n<<1;
    for(int i=2;i<=n*2;i++){
        if(a[i]>a[i-1])b++,s=1;
        else if(a[i]<a[i-1])s++,b=1;
        else s++,b++;
        if(s>=n||b>=n){
            now=i-n+1;
            if(s>=n)ans=min(ans,min(1+n-now+1,now));
            if(b>=n)ans=min(ans,min(n-now+1,2+now-1));
        }
    }
    if(ans!=n*2)printf("%d\n",ans);
    else puts("-1");
}
int main(){
    read(t);
    while(t--)solve();
    return 0;
}
```


---

## 作者：yshpdyt (赞：0)

## 题意
一个序列 $a_i$，每次可以将 $a_n$ （最后一项）移到序列开头，求最小操作次数让序列单调不降，或报告无解。

## Sol
提供一种比较暴力显然的方法。

考虑没有 **反转** 操作，要想单调不降，最大值必须在最右边，最小值必须在最左边。那我们可以有以下两种操作：

1. 对应左图，$rmax $ 表示最大值最后一次出现的位置，将 $rmax $ 右边（$i>rmax$）所有的元素移到序列的开头，使得最大值之后不存在比它小的元素。

2. 对应右图，$lmin $ 表示最小值第一次出现的位置，将 $lmin $ **及其**右边（$i \ge lmin$）的所有元素移到序列的开头，使得最小值之前不存在比它大的元素。
![](https://cdn.luogu.com.cn/upload/image_hosting/u5b96ypz.png)

然后我们可以暴力的去判断是否符合题意，单次判断复杂度 $O(n)$，如果符合题意答案为 $n-rmax$ 或 $n-lmin+1$。

考虑反转以后的情况。

由于可以反转，所有**单调不增**的情况也可以符合题意，只需要最后将整个序列进行反转就可以了。类似的，这种情况对应两种情况（形成单调不增序列）：

1. 对应左图，$lmax $ 表示最大值第一次出现的位置，将 $lmax $ **及其**右边（$i \ge lmax$）的所有元素移到序列的开头，使得最大值之前不存在比它小的元素。

2. 对应右图，$rmin $ 表示最小值最后一次出现的位置，将 $rmin $ 右边（$i>rmin$）所有的元素移到序列的开头，使得最小值之后不存在比它大的元素

同样暴力的去判断是否符合题意，因为最后多了一次翻转操作，所以符合题意答案为 $n-lmax+2$ 或 $n-rmin+1$。

这样的算法还有一些漏洞，对于 `2 5 5 4` 这样的样例，上述算法运行结果是 `4`，而答案为 `2`，这是因为我们可以先进行一次翻转操作变成 `4 5 5 2`，接着把 最后一项移到开头就符合题意了，于是可以在我们算法的基础上，**将序列反转过来后再判断一次** ，注意此时答案要 $+1$ 。

upd：好似只需要讨论四种就可以了，但反正能过，就暴力一些吧。

总的时间复杂度为 $O(Tn)$ 。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n;
ll xl,xr,mx;
ll il,ir,mi;
ll a[N],b[N];
int check(){
    ll fl1=1,fl2=1;// 升 降
    for(int i=2;i<=n;i++){
        if(b[i]>b[i-1])fl2=0;
        if(b[i]<b[i-1])fl1=0;
        if(!fl2&&!fl1)return 0;
    }
    if(fl1&&fl2)return 3;//注意此处，序列可能都为一个值，这样的序列即是增的又是降的
    if(fl1)return 1;//序列是单调不降的
    if(fl2)return 2;//序列是单调不增的
}
ll sol1(){
    xl=il=n+1;
    xr=ir=0;
    for(ll i=1;i<=n;i++){
        if(a[i]==mx){
            //x:max，省略一些
            xl=min(i,xl);
            xr=max(i,xr);
        }
        if(a[i]==mi){
            //i:min
            il=min(i,il);
            ir=max(i,ir);
        }
    }
    // a[n]=xr,升
    ll ans=inf,now=0;
    ll t=0;
    for(int i=xr+1;i<=n;i++){
        b[++t]=a[i];
        now++;
    }
    for(int i=1;i<=xr;i++)b[++t]=a[i];
    ll q=check();
    if(q==1||q==3)ans=min(ans,now);

    // a[n]=ir,降
    t=now=0;
    for(int i=ir+1;i<=n;i++){
        b[++t]=a[i];
        now++;
    }
    for(int i=1;i<=ir;i++)b[++t]=a[i];
    q=check();

    // a[1]=il,升
    if(q==2||q==3)ans=min(ans,now+1);
    t=now=0;
    for(int i=il;i<=n;i++){
        b[++t]=a[i];
        now++;
    }
    for(int i=1;i<il;i++)b[++t]=a[i];
    q=check();
    if(q==1||q==3)ans=min(ans,now);

    // a[1]=xl,降
    t=now=0;
    for(int i=xl;i<=n;i++){
        b[++t]=a[i];
        now++;
    }
    for(int i=1;i<xl;i++)b[++t]=a[i];
    q=check();
    if(q==2||q==3)ans=min(ans,now+1);
    return ans;
}
void sol(){
    cin>>n;
    mx=-inf,mi=inf;
    for(ll i=1;i<=n;i++){
        cin>>a[i];
        mx=max(a[i],mx);
        mi=min(a[i],mi);
    }
    ll ans=sol1();
    reverse(a+1,a+n+1);//反转操作
    ans=min(sol1()+1,ans);
    if(ans==inf)ans=-1;
    cout<<ans<<endl;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```




---

## 作者：guozhe6241 (赞：0)

# 题目传送门

[CF1907F](https://www.luogu.com.cn/problem/CF1907F)

# 思路

这题我们把序列当做一个环，我们分类讨论两种操作。

第一种操作不会改变数列的顺序，第二种操作改变元素的正反。

那么我们要找到一个点，使它可以通过移位或反转成为一个有序序列。

如果不能通过操作成为有序序列，直接输出 $-1$。

否则我们需要找到这个点，然后判断最小值。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
int a[100005];
void solve(){
	cin>>n;
	int m=0,l=0,idm=0,idl=0,ans=1e9;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<n;i++){
		if(a[i]>a[i+1]){
			l++;
			idm=i+1;
		}else if(a[i]<a[i+1]){
			m++;
			idl=i+1;
		}
	}
	if(l==0){
		cout<<0<<endl;
	}else if(m==0){
		cout<<1<<endl;
	}else if(l>1&&m>1){
		cout<<-1<<endl;
	}else{
		if(l==1&&a[1]>=a[n]){
			ans=min(ans,min(idm+1,n-idm+1));
		}
		if(m==1&&a[1]<=a[n]){
			ans=min(ans,min(idl,n-idl+2));
		}
		cout<<(ans==1e9?-1:ans)<<endl;
	}
}
signed main(){
	cin>>t;
	while(t--){
		solve();
	}
    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/141033023)

---

