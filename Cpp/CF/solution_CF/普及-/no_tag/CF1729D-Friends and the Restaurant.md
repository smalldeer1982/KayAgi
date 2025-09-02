# Friends and the Restaurant

## 题目描述

A group of $ n $ friends decide to go to a restaurant. Each of the friends plans to order meals for $ x_i $ burles and has a total of $ y_i $ burles ( $ 1 \le i \le n $ ).

The friends decide to split their visit to the restaurant into several days. Each day, some group of at least two friends goes to the restaurant. Each of the friends visits the restaurant no more than once (that is, these groups do not intersect). These groups must satisfy the condition that the total budget of each group must be not less than the amount of burles that the friends in the group are going to spend at the restaurant. In other words, the sum of all $ x_i $ values in the group must not exceed the sum of $ y_i $ values in the group.

What is the maximum number of days friends can visit the restaurant?

For example, let there be $ n = 6 $ friends for whom $ x $ = \[ $ 8, 3, 9, 2, 4, 5 $ \] and $ y $ = \[ $ 5, 3, 1, 4, 5, 10 $ \]. Then:

- first and sixth friends can go to the restaurant on the first day. They will spend $ 8+5=13 $ burles at the restaurant, and their total budget is $ 5+10=15 $ burles. Since $ 15 \ge 13 $ , they can actually form a group.
- friends with indices $ 2, 4, 5 $ can form a second group. They will spend $ 3+2+4=9 $ burles at the restaurant, and their total budget will be $ 3+4+5=12 $ burles ( $ 12 \ge 9 $ ).

It can be shown that they will not be able to form more groups so that each group has at least two friends and each group can pay the bill.

So, the maximum number of groups the friends can split into is $ 2 $ . Friends will visit the restaurant for a maximum of two days. Note that the $ 3 $ -rd friend will not visit the restaurant at all.

Output the maximum number of days the friends can visit the restaurant for given $ n $ , $ x $ and $ y $ .

## 说明/提示

The first test case in explained in the problem statement.

In the second test case, friends cannot form at least one group of two or more people.

In the third test case, one way to visit the restaurant in one day is to go in a group of all three friends ( $ 1+3+10 \ge 2+3+7 $ ). Note that they do not have the option of splitting into two groups.

## 样例 #1

### 输入

```
6
6
8 3 9 2 4 5
5 3 1 4 5 10
4
1 2 3 4
1 1 2 2
3
2 3 7
1 3 10
6
2 3 6 9 5 7
3 2 7 10 6 10
6
5 4 2 1 8 100
1 1 1 1 1 200
6
1 4 1 2 4 2
1 3 3 2 3 4```

### 输出

```
2
0
1
3
1
3```

# 题解

## 作者：lrqlrq250 (赞：4)

很不错的双指针练习题

## 解题思路
一个显然的结论是，如果我们想凑成尽量多的组，那最好每组都只有两个人。

因此我们先构造数组 `c[i] = y[i] - x[i]`，可以发现当 `c[i]` 是正数的时候他还可以带着一个人去恰饭。反之他就只能由另一个人带着去恰饭。

我们考虑从小到大排序 `c` 数组

维护两个指针 `p` 和 `q`，分别指向 `c` 数组的首尾。我们用双指针的方式将 `p` 和 `q` 凑成一对去恰饭，也就是不断将 `p` 向右移动，直到 `c[p] + c[q] >= 0`，也就是两个人的钱可以让他们吃饭。这时就将答案加一。

然后再将 `p` 向右移一位，将 `p` 向左移一位，就可以进行下一次匹配了。

**（关于双指针正确性不做额外的证明了，有需要可以去观赏其他博客）**

排序复杂度为单次 $O(n \log n)$。

双指针复杂度为单次 $O(n)$。

因此总的复杂度为 $O(\sum n \log n)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, x[100001], y[100001], c[100001];


int main(){
	int t;
	scanf("%d", &t);
	while (t--){
		scanf("%d", &n);
		for (int i=1; i<=n; i++) scanf("%d", &x[i]);
		for (int i=1; i<=n; i++) scanf("%d", &y[i]), c[i] = y[i] - x[i];
		stable_sort(c + 1, c + n + 1);
		int cnt = 0, p = 1, q = n;
		while (p < q){
			while (c[p] + c[q] < 0 && p < q) p++;
			if (p == q) break;//无法再匹配新的一对了
			if (c[p] + c[q] >= 0) cnt++;
			p++, q--; 
		}
		printf("%d\n", cnt);
	}
	return 0;
}

```

PS：由于洛谷 RMJ 正在维护，Codeforces 上的 AC 记录在[这里](https://codeforces.com/contest/1729/submission/175329390)

---

## 作者：endswitch (赞：3)

我们贪心地想，如果要使得凑成的组数尽量多，那么每组的人就要尽量少。

令 $z_i=y_i-x_i$，排序。维护两个指针 $l,r$。如果 $z_l+z_r<0$ 就右移 $l$ 指针，因为我们是按照从小到大排序的，右移才会有可能匹配到。否则就说明这两个元素得以匹配，可以将答案加一。我们将 $l$ 右移，$r$ 左移就可以开始新一轮的匹配了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n,x[N],y[N],z[N],l,r,ans;
int main() {
	ios_base::sync_with_stdio(NULL);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>T;
	while(T--) {
		cin>>n;
		ans=0,l=1,r=n;
		for(int i=1;i<=n;i++)
			cin>>x[i];
		for(int i=1;i<=n;i++)
			cin>>y[i],z[i]=y[i]-x[i];
		sort(z+1,z+1+n);
		while(l<r) {
			while(z[l]+z[r]<0&&l<r) l++;
			if(l==r) break;
			if(z[l]+z[r]>=0) ans++;
			l++,r--;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：XXXxm (赞：1)

## 题目

#### [题意](https://www.luogu.com.cn/problem/CF1729D)

## 思路

拿到题目，一目了然的是算法：双指针、贪心。

题干这句话是关键：求**最大**组数满足每组中 $x$ 的总和不大于 $y$ 的总和，并且每组的数量**至少**为 $2$。

那我们想到,最优解就是每组只有 **2** 人 ($x_i$ 和 $y_i$ 是捆绑式选取)。

于是我们可以开一个数组 $sum$ 去记录两个数组 $x$ 和 $y$ 两者的差值。

```cpp
int x[N],y[N],sum[N],n;
scanf("%d",&n);
for(int i = 1; i<=n; i++)
	scanf("%d",&x[i]);
for(int i = 1; i<=n; i++)
	scanf("%d",&y[i]);
for(int i = 1; i<=n; i++)
	sum[i] = y[i] - x[i];
```

只要 $sum$ 的值是大于 $0$ 的那么我们就可以选

我们可以 sort 对 $sum$ 进行排序，开头指针 $head$ 和尾指针 $tail$ **for 循环** $sum$ 的两边，如果满足 $sum_{head} + sum_{tail} \ge 0$ 那么就可以组成一组，答案加一。

### *code*
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int t;
int main() {
	scanf("%d",&t);
	while(t--) {
		int x[N],y[N],sum[N],n;
		scanf("%d",&n);
		for(int i = 1; i<=n; i++)
			scanf("%d",&x[i]);
		for(int i = 1; i<=n; i++)
			scanf("%d",&y[i]);
		for(int i = 1; i<=n; i++)
			sum[i] = y[i] - x[i];
		sort(sum + 1,sum + n + 1);
		int ans = 0,head = 1,tail = n;
		while(head < tail) {
//			printf("%d %d\n",head,tail);
			if(sum[head] + sum[tail] >= 0) ans++,head++,tail--;//维护头尾指针进行枚举配对 
			else head++;
		}
		printf("%d\n",ans);
	}
	return 0;
}


```


---

## 作者：djh0314 (赞：1)

### 题目链接 [ CF1729D](https://www.luogu.com.cn/problem/CF1729D)   

------------
 
### 题意 
 有长度为 n 的数组 $x$ 和 $y$ ,可以选择若干个下标，将选择的下标分成若干组（每组最少 2 个），使每组中下标对应的 $x$ 之和不大于 $y$ 之和。问最大的组数。
 
-----------

### 分析
因为每次都是选择对应的 $x_{i}$ 和 $y_{i}$,   
那么不妨再写一个数组 $f_{i}$ , $f_{i} = y_{i} - x_{i}$ 。
对于成立的每一组， $f$ 之和大于 0 。
所以每一组必有一个 $f$ $> =0$ 。
#### 结论 1 ：长度都为 2。
证明：  
对于长度大于 2 的每一组，一定可以将其中 $f<0$ 的全部不选，一定可以将其中多余的 $f>=0$ 的不选。    
因此，对于最终组数最多情况，必然存在每一组长度都为 2 的情况。

#### 结论2 ： 每一组的 $f$ 要么是都 $>=0$ , 或者有一个 $<0$ 。
证明显然。

#### 结论3 ：对于每一个 $f >=0$ 的下标，能选择 $f<0$ 的就不让其选择 $f >= 0 $ 的。
因为要使组数最大，因此显然。



------------

如此我们就有了代码的思路：    
先对 $f$ 进行排序，并标记排序后第一个 $f>=0$ 的下标。   
对于这个 $f$ ，   
判断与我们现在没有选择的最大负值 $f$ 相加是否大于等于 0 ，    
否则将其下一个 $f$ 与之组成一组。


------------

### AC 代码 
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
int n, m;
int a[N];
int T;
signed main() {
	cin>>T;
	while(T--) {
		cin>>n;
		for(int i=1; i<=n; ++i) {
			cin>>a[i];
		}
		for(int j=1; j<=n; ++j) {
			int x;
			cin>>x;
			a[j]=x-a[j];
		}
		sort(a+1,a+n+1);
		int l=0;
		for(int i=1; i<=n; ++i ) {
			if(a[i]<0) l=i;
			else break;
		}
		int cnt=0;
		for(int i=l+1; i<=n; ++i) {
			if(l!=0&&a[i]+a[l]>=0) cnt++,l--;
			else {
				++i;
				if(i<=n)
					cnt++;
			}
		}
		cout<<cnt<<endl;;
	}
	return 0;
}
```



---

## 作者：lyt_awa (赞：1)

## 题意
[<传送门>](https://www.luogu.com.cn/problem/CF1729D)
## 思路
### 贪心
因为要求的是**最大组数**且**每组的数量至少为 $2$**（这里的 $2$ 是指 $x$ 和 $y$ 各两个，顺便说一下 $x_i$ 和 $y_i$是捆绑的），那最优解一定是**每组只有两个人**。

于是就可以将每一个人对于 $y_i-x_i$ 进行排序，然后就从两端进行配对，设左边的下标为 $l$ 右边为 $r$，那么只要满足 $y_l - x_l + y_r - x_r \ge 0$，$l$ 和 $r$ 就可以组成一组，并且这样组队一定是最优的。

于是我们就可以愉快地切掉这题啦！
## $code$
代码奉上。
```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e5 + 5;

inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x * f;
}

int t, n, x[N], y[N], c[N], ans, l, r;

int main() {
	t = read();
	while (t--) {
		ans = 0;
		n = read();
		for (int i = 1; i <= n; ++i) x[i] = read();
		for (int i = 1; i <= n; ++i) {
			y[i] = read();
			c[i] = y[i] - x[i];
		}
		sort(c + 1, c + n + 1);
		l = 1, r = n;
		while (l < r) {
			while (c[l] + c[r] < 0 && l < r) ++l;
			if (l == r) break;
			if (c[l] + c[r] >= 0) ++ans;
			l++, r--;
		}
		printf("%d\n", ans);
	}
	return 0;
}
```



---

## 作者：abensyl (赞：1)

~~比赛时觉得D比B好写。~~

本人看到题解里有各种各样的奇特做法，但我觉得还是我的更好理解。

原题：[CF1729D Friends and the Restaurant](https://www.luogu.com.cn/problem/CF1729D)

## 思路

本题算法：双指针、排序、贪心。

1. 输入两个数组 ~~（学过都知道要这样做）~~。

2. 将每个人吃饭的钱与每个人拥有的钱的差存入一个数组 $f$。

- Q.为什么要这样做？

> 当我们要选取 $i$ 和 $j$ 两个人一起吃饭的时候，我们只要判断 $f_i + f_j \geq 0$ 即可。

> 而要使用双指针算法，必须将 $f$ 数组进行排序。

3. 排序

4. 双指针扫描区间

- 如何两个指针 $i$ 和 $j$ 来扫描整个区间？

- 如何计算答案？

> 这是本程序最关键的一步。

> 如果我们想让一起吃饭的人组数尽可能多，如果每组只有两个人，那么就是最优解。

> 由于 $f$ 数组现已是有序的，所以只要判断 $f_i + f_j \geq 0$ 的真假性来的值是否两人可以一起去吃饭。

> 首先让指针 $i$ 指向 $f$ 数组头，让指针 $j$ 指向 $f$ 数组末尾。

> 如果 $f_i + f_j < 0$ 则，将 $i$ 向后移动，直至 $f_i + f_j \geq 0$，此时，我们找到一个合法对，于是将答案加一。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+3;
int x[N],y[N];
int main() {
  int t;
  cin>>t;
  while(t--) {
    int n;
    cin>>n;
    vector<int> f;
    for(int i=1;i<=n;++i) cin>>x[i];
    for(int i=1;i<=n;++i) cin>>y[i];
    for(int i=1;i<=n;++i) f.push_back(y[i]-x[i]);
    sort(f.begin(),f.end());
    int ans=0;
    int i=0,j=n-1;
    while(i<j) {
      while(true) if(f[i]+f[j]<0&&i<j) i++; else break;
      if(i>=j) break;
      if(f[i]+f[j]>=0) ans++;
      j--,++i; 
    }
    cout<<ans<<'\n';
  }
  return 0;
}
//只有27行
```
我的 [AC记录](https://codeforces.com/contest/1729/submission/171907886)

---

## 作者：2huk (赞：0)

# D. [Friends and the Restaurant](https://codeforces.com/contest/1729/problem/D)

## Description

给定 $n$ 和长为 $n$ 的 $a, b$ 数组。现要从其中选出一些数，并将它们分组，使得第 $i$ 组满足 $\sum a_k \le \sum b_k$，且一组中的元素个数 $\ge 2$。问最多能分的组数。

## Solution

考虑贪心。

既然题目要求分的组数尽量多且一组内元素至少有 $2$ 个，那么我们就让一组有 $2$ 个元素，能匹配的匹配，不能匹配的放弃。

记 $q_i = b_i - a_i$，那么将 $i$ 和 $j$ 分到一组时只需要满足 $q_i + q_j \ge 0$ 即可。

尝试让最大的 $q_r$ 和最小的 $q_l$ 合并。如果可以合并则合并，不能则找到次小的 $q_l'$，还不行继续找，直到可以合并时就合并。

这个过程其实就是两个指针 $l, r$ 的移动。因此首先将 $q$ 从小到大排序，然后让上面那样做一个双指针即可。

注意边界条件，在 $l = r$ 时结束循环，因为题目要求了一组要有至少 $2$ 个元素。

## Code

```cpp
int T, n, a[N], b[N], q[N];
 
int Solve()
{
	scanf("%d", &n);
	
	for (int i = 1; i <= n; ++ i )
		scanf("%d", a + i);
	
	for (int i = 1; i <= n; ++ i )
		scanf("%d", b + i);
	
	for (int i = 1; i <= n; ++ i )
		q[i] = b[i] - a[i];
	
	std::sort(q + 1, q + n + 1);
	
	int res = 0;
	for (int l = 1, r = n; l < r; ++ l, -- r )
	{
		while (l < r && q[l] + q[r] < 0)
			++ l;
		
		if (l == r) break;
		
		if (q[l] + q[r] >= 0)
			++ res;
	}
	
	return res;
}
```

---

## 作者：free_fall (赞：0)

# 题目大意
给出长度为 $n$ 的数组 $x$ 和 $y$，你可以从中选出一些数，且将这些数分为若干组，求最大组数满足每组的数量至少为 $2$ 且每组中 $x$ 的总和不大于 $y$ 的总和。
# 思路
因为当选择了 $x_i$ 时 $y_i$ 也必须选，所以可以只记录它们的差，用 $a_i$ 表示 $y_i-x_i$ 的值。这里有一个简单的贪心，为了使选择的组数最多，每组选 $2$ 对肯定不会比选 $2$ 对以上要劣，所以为了方便，我们可以将每组都只选 $2$ 对。

但是即使是这样，枚举每组中的两对还是需要两层循环，明显会超时。

这时候用 $a_i$ 表示 $y_i-x_i$ 的优势就体现出来了，我们可以将 $a$ 数组排序，越大的数与越小的数组成一组，这样只用一层循环就可以得到答案了。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int t,n,ans,a[N],now,sum;
int main(){
	scanf("%d",&t);
	while(t--){
		ans=0,now=1;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n;i++){
			int x;
			scanf("%d",&x);
			a[i]=x-a[i];
		}
		sort(a+1,a+n+1);
		for(int i=n;i>=1;i--){
			for(int j=now;j<i;j++){
				now=j+1;
				if(a[i]+a[j]>=0){
					ans++;
					break;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：cyhtxdy (赞：0)

需要思考一下的贪心。

题目说明每个组至少两人，那么贪心的考虑，每个组就只选取两个人，最大化答案。

将每个 $b_i-a_i$ 记作 $v_i$，$v_x+v_y\ge0$ 则代表 $x$ 和 $y$ 可以凑成一组。

若直接将非负数的配对，那么答案就是非负数总个数 $\lfloor \frac{tot}{2} \rfloor$。我们尽量将符合条件一个正数和一个负数配对，这样就能减少非负数的使用，从而最大化答案。

记录非负数的个数以及第一个非负数的位置 $pos$，令 $l=pos-1$，$r=pos$。每次都将 $v_l+v_r \ge 0$ 记录下，并将非负数个数减去一，将 $l$ 向左移一位，将 $r$ 向右移一位。最终将还没有配对的非负数再两两配对即可。

得到代码：
```
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

#define int long long

int T, _x[N], _y[N], n, v[N];

signed main () {
	cin >> T;
	while (T --) {
		cin >> n;
		for (int i = 1; i <= n; i ++) {
			cin >> _x[i];
		}
		for (int i = 1; i <= n; i ++) {
			cin >> _y[i];
		}
		for (int i = 1; i <= n; i ++) {
			v[i] = _y[i] - _x[i];
		}
		sort (v + 1, v + 1 + n);//v从小到大排序 
		int cntpo = 0, pos = 0;
		for (int i = n; i >= 1; i --) {
			if (v[i] >= 0) {
				cntpo ++;//记录非负数个数 
				pos = i;//pos记录第一个非负数位置 
			}
		}
		int ans = 0;
		int l = pos - 1, r = pos;
		while (l >= 1 && r <= n) {
			while (r <= n && v[l] + v[r] < 0) {
				r ++;
			}//此时的l和r符合条件 
			if (r > n) {
				break;
			}
			cntpo --;//非负数个数减一 
			ans ++;//答案加一 
			l --;//l向左移一位 
			r ++;//r向右移一位 
		}
		ans += cntpo / 2;//还没配对的非负数两两配对 
		cout << ans << endl;
	}

	return 0;
}
```


---

## 作者：BotDand (赞：0)

# $\text{Problems}$

给出长度为 $n$ 的数组 $x$ 和 $y$，你可以从中选出一些数，且将这些数分为若干组，求最大组数满足每组的数量至少为 $2$ 且每组中 $x$ 的总和不大于 $y$ 的总和。

注意 $x$ 和 $y$ 是捆绑在一起的，也就是说，如果你选了 $x_{i}$ 那么你也必须选 $y_{i}$。

感谢 @[YunYuan](https://www.luogu.com.cn/user/164883)。

# $\text{Answer}$

令 $a_{i}=y_{i}-x_{i}$，那么题目就变成了求最大组数满足每组的数量至少为 $2$ 且每组中 $a$ 的总和不小于 $0$。

不难发现两个非负的 $a_{i}$ 组合起来总和一定不小于 $0$。

但这样每组都要用掉两个非负的 $a_{i}$，不够优。

考虑如果有 $a_{i}<0,a_{j}\ge0,a_{i}+a_{j}\ge0$，那么可以将这两个数并在一起，这样只消耗了一个非负的 $a_{i}$。

剩余的非负的 $a_{i}$ 按每组两个分配。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int x[100002],y[100002];
int a[100002];
int ans;
void work()
{
    cin>>n;
    for(int i=1;i<=n;++i) cin>>x[i];
    for(int i=1;i<=n;++i) cin>>y[i];
    for(int i=1;i<=n;++i) a[i]=y[i]-x[i];
    // 求最大组数使得每组至少为两人且 sum(a[i])>=0
    sort(a+1,a+n+1);
    int cnt=0,sum=0;
    for(int i=n;i>=1;--i)
        if(a[i]>=0)
        {
            cnt=i;
            sum++;
        }
    int i=cnt-1,j=cnt;
    int ans=0;
    while(i>=1&&j<=n)
    {
        while(j<=n&&a[i]+a[j]<0) j++;
        if(j>n) break;
        sum--;
        ans++;
        i--;j++;
    }
    ans+=sum/2;
    cout<<ans<<"\n";
}
int main()
{
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

