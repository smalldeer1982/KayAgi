# [ABC365C] Transportation Expenses

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc365/tasks/abc365_c

あるイベントには $ N $ 人が参加し、$ i $ 番目の人の交通費は $ A_i $ 円でした。

イベントの主催者である高橋くんは、交通費補助額の上限額 $ x $ を設定して、人 $ i $ には交通費補助額として $ \min(x,A_i) $ 円を支給することとしました。ここで $ x $ は非負整数である必要があります。

高橋くんの予算が $ M $ 円であり、$ N $ 人に渡す交通費補助額の総和を $ M $ 円以下にしたいとき、交通費補助額の上限額 $ x $ は最大でいくらにできますか？

ただし、交通費補助額の上限額を無限に大きくできる場合は代わりにそのことを報告してください。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ M\ \leq\ 2\times\ 10^{14} $
- $ 1\leq\ A_i\ \leq\ 10^9 $
- 入力される数値は全て整数
 
### Sample Explanation 1

交通費補助額の上限額を $ 2 $ 円にすると、$ N $ 人に渡す交通費補助額の総和は $ \min(2,1)\ +\ \min(2,3)\ +\ \min(2,2)\ +\ \min(2,4)\ =\ 7 $ 円となり、予算の $ 8 $ 円以下となります。 交通費補助額の上限額を $ 3 $ 円にすると、$ N $ 人に渡す交通費補助額の総和は $ \min(3,1)\ +\ \min(3,3)\ +\ \min(3,2)\ +\ \min(3,4)\ =\ 9 $ 円となり、予算の $ 8 $ 円を超えてしまいます。 よって、交通費補助額の上限額の最大値は $ 2 $ 円となります。

### Sample Explanation 2

交通費補助額の上限額を無限に大きくできます。

## 样例 #1

### 输入

```
4 8
1 3 2 4```

### 输出

```
2```

## 样例 #2

### 输入

```
3 20
5 3 2```

### 输出

```
infinite```

## 样例 #3

### 输入

```
10 23
2 5 6 5 2 1 7 9 7 2```

### 输出

```
2```

# 题解

## 作者：chinazhanghaoxun (赞：7)

## 题意

题目给了我们 $N$ 个人前来参加活动，每个人的路费为 $A_i$。现在主办方有 $M$ 元的预算，如果主办方决定每人的补贴为 $x$ 元，第 $i$ 个人获得的补贴就是 $\min(A_i,x)$。一句话概括，主办方想给每个人补贴，如果当前这个人的路费小于预计补贴，那就只补贴路费，主办方想让给每个人的补贴最大且不超出预算。
## 思路

看到这种求一个操作的最大值，应该就可以想到使用二分答案，直接二分枚举主办方给每个人的补贴 $x$。然后创建一个检查函数，看是否在预算之内。想到这里，这道题就变成了一道二分模版题。如果二分掌握得不熟练，可以练一练[这道题](https://www.luogu.com.cn/problem/P2249)
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long //int存不下！！！ 
using namespace std;
const int N=2e5+10;
int n,m,a[N],ans;
bool check(int x){
	int cnt=0; //当前花费的预算 
	for(int i=1;i<=n;i++){
		cnt+=min(x,a[i]);
		if(cnt>m){ //减少循环次数 
			return false;
		}
	}
	return cnt<=m; //这种方案可以 
}
signed main(){
	cin>>n>>m;
	int c=0; 
	for(int i=1;i<=n;i++){
		cin>>a[i];
		c+=min(1ll*1,a[i]); //每个人只给1块的补贴 
	}
	if(c>m){ //1块都超出预算 
		cout<<0;
		return 0;
	}
	int l=1,r=m+1; //二分 
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			l=mid+1;
			ans=mid; //要在这里记录一下答案 
		}else{
			r=mid-1;
		}
	}
	if(ans==m+1) //无限大也可以 
		cout<<"infinite";
	else cout<<ans; //输出 
	return 0;
}
```

---

## 作者：ikunTLE (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc365_c)

### 思路

题目要求补贴限额 $x$ 的最大可能值是多少，可以发现其答案具有单调性，考虑使用**二分答案**。

对于每一次选择的 $x$，对于第 $i$ 个人选择 $\min(x,A_i)$，判断其和是否 $>M$。若 $\displaystyle\sum_{i=1}^{N}A_i<M$，那么如果补贴限额可以无限大。

**注意事项**

- 不开 `long long` 见祖宗。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){long long x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=2e5+10,MAX=1e9;
int n,a[N];
long long m;
bool check(int x){
	long long sum=0;
	for(int i=1;i<=n;++i){
		sum+=min(x,a[i]);
		if(sum>m)
			return false;
	}
	return true;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	int l=0,r=MAX;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))
			l=mid+1;
		else r=mid-1;
	}
	if(r!=MAX)
		printf("%d\n",r);
	else printf("infinite\n");
	return 0;
}
```

---

## 作者：Little_x_starTYJ (赞：5)

### 解题思路
我们先来讨论答案可能无限大的情况吧。

我们设 $x$ 是我们要求的最高限额，序列 $a$ 是每个人的费用，$n$ 是总人数。

当 $(\displaystyle\sum_{i = 1}^{n}a_i)\le m$ 时，不管 $x$ 多大，$\displaystyle\sum_{i = 1}^{n}\min(a_i,x)$ 一定小于等于 $x$，所以遇到这种情况，我们直接打印 `infinite` 即可。

接着，我们讨论答案唯一的情况。

经过短暂的观察，我们发现 $\displaystyle\sum_{i = 1}^{n}\min(a_i,x)$ 的值是具有单调性的，这时，我们就可以使用二分答案进行求解。

我们二分 $x$ 的取值，如果满足条件就再尝试找到更大的解，如果不满足条件就得在小于当前取值的范围里面找。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int a[200010], n, m;

bool check(int k) {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += min(a[i], k);
		if (ans > m)
			return false;
	}
	return true;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n >> m;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	
	if (sum <= m) {
		cout << "infinite";
		return 0;
	}
	
	int l = 1, r = m;
	while (l < r) {
		int mid = l + (r - l + 1) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid - 1;
	}
	cout << l;
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：4)

# AT_abc365_c [ABC365C] Transportation Expenses 题解

### 解析

一眼就看出来我设置的价格越高，总花费就越高，答案存在单调性。所以我们二分答案。

然后就真的没有然后了，注意判无解。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5;
int n,m;
int a[N];
bool check(int x){
	int tot=0;
	for(int i=1;i<=n;i++){
		tot+=min(x,a[i]);
	}
return tot<=m;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	int l=0,r=2e16,mid,ans;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			l=mid+1,ans=mid;
		}
		else{
			r=mid-1;
		}
	}
	if(ans==2e16){
		cout<<"infinite";
	}
	else{
		cout<<ans;
	}
return 0;
}
```

---

## 作者：__qp__ (赞：3)

#### 题目简述

给定 $n$ 个人的交通费用 $a_i$，确定最大补贴额度 $x$，使得给每个人的补贴为 $\min(x,a_i)$，总补贴额度不超过 $m$。

#### 思路

显然 $x$ 越高，总补贴额度越高，$\sum_{i=1}^{n} \min(x, a[i])$ 具有单调性。

直接二分即可。

判 `Inf` 直接看 $\sum a_i$ 与 $m$ 的大小关系。

**注意：不开 `long long` 见祖宗！**

#### 代码


```cpp
#include <iostream>
#include <algorithm>

using namespace std;
const int MAXN = 2 * 1e5;
long long N, M;
long long A[MAXN];
long long l = 0, r = 1e9 + 1, ans = 0;
int main(){
    cin >> N >> M;
    for (long long i = 0; i < N; i++) {
        cin >> A[i];
    }
    long long tot = 0;
    for (long long i = 0; i < N; i++) {
        tot += A[i];
    }
    if (tot <= M) {
        cout << "infinite" << endl;
        return 0;
    }
    while(l <= r){
        long long mid = l + (r - l) / 2;
        long long cnt = 0;
        for(long long i = 0;i < N;i++){
            cnt += min(mid, A[i]);
        }
        if (cnt <= M) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << ans << '\n';
    return 0;
}
```

---

## 作者：xuduang (赞：3)

### 题意

现在有 $m$ 个物品，要分给 $n$ 个人，每个人有一个上限 $a_i$，这意味着如果要给他 $x$ 个物品，他只会得到 $\min(x,a_i)$ 个物品。你需要找出一个最大的 $x$ 使得在不超过 $m$ 的花费下，剩下的物品最少。如果 $x$ 可以定为无限大，输出 `infinite`。

### 分析

首先解决无限大。发现每个人有上限，因此可以很简单的判定，当 $\displaystyle\sum_{i=1}^{n}a_i\le m$ 时是可以设为无限大的，因为所有人的上限都不足以破费。

我们可以发现，当我们设置的 $x$ 越大时，需要给出去的物品也更多，所以她具有单调性，因此可以考虑二分答案。

二分出当前的 $x$，用 $num$ 记录下来 $\displaystyle\sum_{i=1}^{n}\min(x,a_i)$，如果 $num \le m$，那么 $l=mid+1$，同时记录答案，否则 $r=mid-1$。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
    int s = 0, w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        s = (s << 3) + (s << 1) + (ch ^ 48);
        ch = getchar();
    }
    return s * w;
}
const int N = 3e6 + 10;
int n, m;
int a[N];
int check(int x)
{
    int num = 0;
    for(int i = 1; i <= n; i++) num += min(x, a[i]);
    return num;
    //用一个x计算花费
}
signed main()
{
    cin >> n >> m;
    int sum = 0;
    for(int i = 1; i <= n; i++) a[i] = read(), sum += a[i];
    if(sum <= m)//无限大情况
    {
        puts("infinite");
        exit(0);
    }
    int l = 1, r = 1000000000, ans;
    //注意左右端点
    while(l <= r)
    {
        int mid = (l + r) >> 1;//二分答案
        if(check(mid) <= m)
        {
            l = mid + 1;
            ans = mid;
        }
        else r = mid - 1;
    }
    cout << ans << endl;
	return 0;
}
```

---

## 作者：cyx012113 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc365_c)

[文章传送门](https://www.luogu.com.cn/article/5j9qn2e1)
### 题目大意
有 $N$ 人参加一项活动，第 $i$ 人的交通费用是 $A_i$ 日元。

活动组织者高桥（Takahashi）决定设定补贴的最高限额为 $x$。第 $i$ 人的补贴为 $\min(x, A_i)$ 日元。$x$ 必须是一个非负整数。

高桥的预算为 $M$ 日元，他希望所有 $N$ 人的交通补贴总额最多为 $M$ 日元，那么补贴限额 $x$ 的最大是多少？

如果补贴限额可以无限大，请报告 `infinite`。

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq M \leq 2 \times 10^{14}$
- $1 \leq A_i \leq 10^9$
- 所有输入值均为整数。
### 题目分析
考虑到 $1 \leq M \leq 2 \times 10^{14}$，**要开 long long**。

**十年 OI 一场空，不开 long long 见祖宗！**

#### 思路一：暴力
我们可以暴力枚举题目中的 $x$，但是经过暴力，会出现 TLE 以及无法处理要求输出 `infinite` 的问题，无法通过本题。

#### 思路二：求和与判断
使用这种 _~~玄学~~_ 做法，会发现：
- 对于一些数据，会出现结果有误；
- 对于一些要求补贴无限大的问题，会爆炸（RE）或超时（TLE）。

#### 思路三：二分
暴力枚举会使 $x$ 可能达到 $m$ 的极限，所以我们考虑使用更好的枚举算法。

我们考虑对 $x$ 进行二分，如果达到上限，则判断为可无限大。

我们可以将下限（$l$）设为 $0$，将上限（$r$）设为 int 最大值（$2^{31} - 1$）。

循环条件：`l <= r`；

$mid$ 取值：`mid = (l + r) / 2` 或 `mid = l + r >> 2`（位运算从左往右计算）。

状态转移：
- $l = mid - 1$
- $r = mid + 1$

> **为什么不“踩”$mid$ 呢？**
> $mid$ 就是本次循环要进行判断的，不需要重复判定。

（建议配合代码食用喵~。）
### 代码实现
```cpp
#include <bits/stdc++.h>
#define ll long long // 需要开 long long
using namespace std;

const int N = 2e5 + 2, inf = 0x7fffffff; // inf 为 int 上限，只需开到 A_i 的极限即可

ll a[N], n, m, mid, l, r, ans;

int main() {
	cin >> n >> m;
	for (int i = 1;i <= n;i++) cin >> a[i];
	l = 0; // 定义左端点和右端点
	r = inf;
	while (l <= r) {
		mid = l + r >> 1; // 更新 mid（中间值）
		ll cnt = 0;
		for (int i = 1;i <= n;i++) cnt += min(mid, a[i]); // 遍历数组，判断当前 mid 是否满足条件
		if (cnt <= m) l = mid + 1, ans = mid; // 状态转移
		else r = mid - 1;
	}
	if (ans == inf) cout << "infinite" << endl; // 判断是否为特殊情况
	else cout << ans << endl;
    return 0;
}
```
友情提醒：题解千万条，理解第一条。直接粘题解，棕名两行泪。

---

## 作者：Stars_Traveller (赞：1)

## AT_abc365_c [ABC365C] Transportation Expenses 题解
### 分析
真的真的很简单的一个二分（赛时一发过了没测样例）。

首先判无解，容易发现当 $a$ 数组元素之和小于或等于 $m$ 时，$x$ 可以取到任意值，输出 `infinite`。

否则二分 $x$ 的值，左边界 $0$，右边界为 $m+1$，每次判断 $\min(a_i,mid)$ 的和是否小于或等于 $m$ 即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[200005], m;
bool check(int x)
{
  int cnt=0;
  for(int i=1;i<=n;i++)cnt+=min(a[i],x);
  return cnt<=m;
}
signed main()
{
  cin>>n>>m;
  int cnt=0;
  for(int i=1;i<=n;i++){cin>>a[i];cnt+=a[i];}
  if(cnt<=m)
  {
    cout<<"infinite";
    return 0;
  }
  else
  {
    int lt=0, rt=m+1;
    while(lt+1<rt)
    {
      int mid=(lt+rt)>>1;
      if(check(mid))
      {
        lt=mid;
      }
      else rt=mid;
    }
    cout<<lt;
  }
}
```

---

## 作者：OIerWu_829 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc365_c)

我们要找到总补贴不超过预算 $M$ 的最大的补贴限额，由于第 $i$ 个人的补贴是 $\min(x,A_i)$，所以可以用二分解决。初始范围定为 $l=0,r=10^9$，每次通过函数计算补贴限额 $mid$ 下的总补贴，也就是：

$$\sum_{i=1}^{N} \min(mid,A_i)$$

如果这个结果 $\le M$，那么就更新答案。最后，如果最大的答案使得总补贴仍然小于等于 $M$ 或者 $N$ 个人的最小成本之和已经超过 $M$，那么就输出 `infinite`，否则输出答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 2e5 + 5;

LL n, m, c[N];

LL Calc(int x)
{
  LL ans = 0;
  for (int i = 1; i <= n; i++)
  {
    ans += min((LL)c[i], (LL)x);
  }
  return ans;
}

int main()
{
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
  {
    cin >> c[i];
  }
  LL l = 0, r = 1e9, ans = 0;
  while (l <= r)
  {
    LL mid = l + (r - l) / 2;
    LL sum = Calc(mid);
    if (sum <= m)
    {
      ans = mid;
      l = mid + 1;
    }
    else r = mid - 1;
  }
  if (ans >= 1e9 || accumulate(c + 1, c + 1 + n, 0LL) <= m)
  {
    puts("infinite");
  }
  else cout << ans << "\n";
  return 0;
}
```

---

## 作者：woden (赞：1)

一道简单的二分答案题。

大致思路：如果费用总和都小于 $m$，那么输出 `infinite`，否则二分 $x$，判断花费是否小于等于 $m$。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2E5+99;
int a[N],n,m,s;//s表示费用总和。
bool check(int x){
	s=0;
	for(int i=1;i<=n;i++){
		s+=min(a[i],x);//依次加上每人的补贴。
	}
	return s<=m;//判断是否超出预算。
}
signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s+=a[i];
	}
	if(s<=m){
		cout<<"infinite";//特判总花费是否小于等于m。
		return 0;
	}
	int l=1,r=m,mid,ans;//二分x。
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)){//如果补贴不超出预算，就可能有更高的补贴。
			l=mid+1;
			ans=mid;//修改左端点，记录答案。
		}else{
			r=mid-1;//如果补贴超出预算，就修改右端点。
		}
	}
	cout<<ans;//输出，AC！
	return 0;
}
```

---

## 作者：littleqwq (赞：1)

# AT_abc365_c [ABC365C] Transportation Expenses

### 大致思路：

考虑二分答案，可以二分 $x$，根据二分到的 $x$，用循环去计算，看看这个 $x$ 合不合法，记录下来即可，注意左右端点是和值域有关的，不能开小了。

### 代码实现：

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10;
int n, m, a[N];
bool check(int x)
{
	int sum = 0;
	for (int i = 1;i <= n; ++ i)
	{
		sum += min(a[i], x);
		if(sum > m) return 0;
	}
	return sum <= m;
}
signed main()
{
    cin >> n >> m;
    for (int i = 1;i <= n; ++ i) cin >> a[i];
	int l = 1, r = 2e14, res = 2e14 + 10;
    while(l <= r)
    {
    	int mid = (l + r) >> 1;
    	if (check(mid)) l = mid + 1, res = mid;
    	else r = mid - 1;
	}
	if(res >= (2e14)) cout << "infinite\n";
	else cout << res << "\n";
    return 0;
}
```

这样这道题目就完成啦！！！

---

## 作者：donnieguo (赞：0)

## 题意简述

求最大的 $x$，使得

$$\sum\limits_{i=1}^n\min(x,a_i)\leq m$$

$1\leq n \leq 2 \times 10^5$，$1 \leq m \leq 2 \times 10^{14}$，$1 \leq a_i \leq 10^9$。

## 思路

明显 $\sum\limits_{i=1}^n\min(x,a_i)$ 具有单调性。考虑二分 $x$。

无解只需要在输入的时候判断一下 $\sum\limits^n_{i=1}a_i$ 是否小于 $m$ 即可。

记得开 `long long`。

然后就做完了。

## AC code

```cpp
#include <iostream>
#define int long long
#define N 200010
using namespace std;

int n, m;
int a[N];

bool check(int x)
{
	int sum = 0;
	for (int i = 1; i <= n; i++) sum += min(x, a[i]);
	return sum <= m;
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	int sum = 0;
	for (int i = 1; i <= n; i++) {cin >> a[i]; sum += a[i];}
	if (sum <= m) {cout << "infinite" << '\n'; return 0;}
	int ans = 0, l = 1, r = 2e14;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (check(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：stripe_python (赞：0)

显然答案单调，当 $x$ 增加时花钱也多，所以可以二分。

check 是简单的，按题意模拟即可。注意特判 $\sum A \le m$ 时 $x$ 可以无限大。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 200005
long long n, a[N];
long long m;

inline long long check(long long x) {
	long long res = 0;
	for (int i = 1; i <= n; i++) res += min(x, a[i]);
	return res;
}

void _main() {
	cin >> n >> m;
	long long tot = 0;
	for (int i = 1; i <= n; i++) cin >> a[i], tot += a[i];
	if (tot <= m) return cout << "infinite", void();
	long long l = 0, r = 1e18, res = 0;
	while (l <= r) {
		long long mid = (l + r) >> 1;
		if (check(mid) <= m) l = mid + 1, res = mid;
		else r = mid - 1;
	}
	cout << res;
} signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	_main();
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

首先，显然当所有人路费的总和小于等于 $m$ 时，补贴上限可以开到无限大。

对于其他情况，一种很简单的计算方法是二分答案。我们使用二分查找枚举补贴上限，计算对于这个上限，支付所有人的路费补贴要花多少钱。若总钱数低于 $m$，则上限可以更大；否则上限需要更小。最终就可以逼近到最大的可行上限。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[1000005];
bool f(int x){
	int sum=0;
	for(int i=1;i<=n;i++) sum+=min(a[i],x);
	return sum<=m;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	int sum=0;
	for(int i=1;i<=n;i++) sum+=a[i];
	if(sum<=m){
		cout<<"infinite";
		return 0;
	}
	int l=0,r=2e9,mid,k=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(f(mid)) l=mid+1,k=mid;
		else r=mid-1;
	}
	cout<<k;
	return 0;
}
```

---

## 作者：cqbzhr (赞：0)

根据数据范围，$1 \le m \le 2 \times 10^{14}$，显然不能用暴力枚举的方式解决，所以考虑二分，因为补贴的金额一定小于等于 $\lfloor m \div n \rfloor$，即 $10^9$，所以只需要二分枚举 $0$ 到 $10^9$ 的补贴金额，再暴力判断是否满足要求即可，时间复杂度 $O(n \log \lfloor m \div n \rfloor)$。
#### AC code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[200005],tot,ans;
bool check(int x){
	int s=0;
	for(int i=0;i<n;i++){
		s+=min(x,a[i]);
		if(s>m)return 0;
	}
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>a[i];
		tot+=a[i];
	}
	if(tot<=m){
		cout<<"infinite";
		return 0;
	}
	int l=0,r=1e9;
	while(l<=r){
		int mid=l+(r-l)/2;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	if(ans==0)cout<<"infinite";
	else cout<<ans; 
	return 0;
}
```

---

## 作者：xzz_0611 (赞：0)

[洛谷传送门](/problem/AT_abc365_c)  
[AtCoder 传送门](https://atcoder.jp/contests/abc365/tasks/abc365_c)
### 题目大意
有 $N$ 个人，高桥要给这其中的第 $i$ 个人 $\min(A_i,x)$ 元钱，保证 $x\ge0$。

请问在保证高桥给的钱的总数不大于 $M$ 的情况下，$x$ 的值最大是多少，若 $x$ 可以无限大，那么输出 `infinite`。
### 题目分析
先考虑 $x$ 可以无限大的情况：
- 容易得到高桥给的钱的总数为 $\displaystyle\sum^n_{i=1}\min(x,A_i)$，由于 $x$ 的值无限大，所以上式可以简化为 $\displaystyle\sum^n_{i=1}A_i$。又因为高桥最多只能给出 $M$ 元，所以在 $x$ 无限大的时候 $\displaystyle\sum^n_{i=1}A_i$ 是小于等于 $M$ 的。

对于其余情况，只需要二分查找即可。
### Code
```cpp
//请不要抄袭代码
//本代码中变量与题目中的不一样，例如大写 M 在这里是小写 m，需要注意
#include <iostream>
#define int long long//不开 long long 见祖宗
using namespace std;
int n, m, arr[200000];
bool chk(int x) {//判断 x 是否小于等于 M
	int cnt = 0;
	for (int i = 0; i < n && cnt <= m/*当当前花费已经大于 M 时就退出*/; ++i) cnt += min(x, arr[i]);
	return cnt <= m;
}
int findAns(int ma) {//二分函数，这里不推荐函数名写 find，因为有个库函数也叫 find
	int l = 0, r = ma - 1;//二分的右边界为 A 中的最大值减 1，因为只有此时才能减少花费
	while (l <= r) {
		int mid = (l + r) / 2;
		if (chk(mid)) l = mid + 1;//当当前 x 的值不大于 M 时就更新左边界
		else r = mid - 1;//反之则更新右边界
	}
	return r;//返回答案
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> m;
	int cnt = 0, ma = 0;
	for (int i = 0; i < n; ++i) cin >> arr[i], cnt += arr[i], ma = max(ma, arr[i]);//累加数组和，计算数组最大值
	if (cnt <= m) return cout << "infinite", 0;//若 A 数组元素和小于等于 M 就输出 infinite
	cout << findAns(ma);
	return 0;
}
```
### AC 记录
[AtCoder 记录](https://atcoder.jp/contests/abc365/submissions/56484271)  
**注：由于开了完隐就不展示洛谷 AC 记录了。**

---

## 作者：zjj2024 (赞：0)

### 思路
二分题。

二分 $x$，如果原先总和大于等于 $m$ 则表示可以为无穷大，否则输出答案。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
ll a[N],m,n;
bool ok(ll k)//判断每个x是否可行
{
	ll sum=0;
	for(int i=1;i<=n;i++)
		sum+=min(a[i],k);
	if(sum>m)return 0;
	return 1;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll sum=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
	}
	if(sum<=m)//总和小于等于m表示无穷大
	{
		cout<<"infinite\n";
		return 0;
	}
	ll l=0,r=1e16,mid;
	while(l<r)//二分答案
	{
		mid=(l+r+1)>>1;
		if(ok(mid))l=mid;
		else r=mid-1;
	}
	cout<<l<<'\n';
	return 0;
}

```

---

## 作者：Guizy (赞：0)

#### 题目描述

找到一个最大的 $x$ 使得 $\sum \min(a_i,x)\le m$。如果 $x$ 可以无限大，输出 `infinite`。

#### 分析

因为 $n \le 2\times 10^5$，所以考虑使用 $O(n\log n)$ 或 $O(n)$ 的算法，这里使用二分。

每次二分一个 $mid$，判断 $\sum \min(a_i,mid)$ 是否小于等于 $m$。

如果是，就把 $l=mid+1,ans=mid$，继续找更大的 $x$，否则将 $r=mid-1$， 找更小的 $x$。

无解的情况就是 $ans$ 等于初始的右端点。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,a[1000001],m;

int check(int x){
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=min(x,a[i]);
	}
	return sum;
}

signed main(){
	
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	int l=0,r=INT_MAX,mid,ans;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)<=m){
			l=(ans=mid)+1;
		}
		else r=mid-1;
	}
	if(ans==INT_MAX) cout<<"infinite";
	else cout<<ans;
	
}
```

---

## 作者：jiangruibo (赞：0)

### 思路：
这里通过题目就可以直接发现要求的是一个**最值**，而且对这个**最值**还有一定的**限制**，以及对于着每一个 $x$ 总花费是单调递增的，那就不难想到用**二分**，二分去枚举那个 $x$，要使这个 $x$ 最大且对于这个 $x$ 总额不超过 $m$ 就行了。

### 代码：

```cpp
#include <bits/stdc++.h>
#define AK 0
#define IOI ;
#define I return
#define int long long
#define lowbit(x) ((x)&-(x))
#define ull unsigned long long
using namespace std;

int a[200010];
int n,m;
bool check(int mid)
{
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		sum+=min(mid,a[i]);
	}
	return sum<=m;
}
signed main()
{
	cin>>n>>m;
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];	
	}
	int l=0,r=2e16;
	int ans=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(mid)==true)
		{
			l=mid+1;
			ans=mid;
		}
		else
		{
			r=mid-1;
		}
	}
	if(ans==2e16) 
	{
		cout<<"infinite";
		return 0;
	}
	cout<<ans<<endl;
	I AK IOI
}
/*
 */

```

---

## 作者：PineappleSummer (赞：0)

二分答案板子。

二分补贴的上限 $x$，初始 $l=0,r=m$，check 时计算一下 $\sum\limits_{i=1}^n\min(a_i,x)$ 是否不超过为 $m$ 即可。

如果最后二分出来的答案为 $m$，说明补贴可以无限大，输出 `infinite`，否则输出 $l$。

时间复杂度 $\mathcal O(n\log m)$。

```cpp
bool check (int x) {
	int res = 0;
	for (int i = 1; i <= n; i++) res += min (x, a[i]);
	return res <= m;
}
signed main () {
	ios::sync_with_stdio (false);
	cin.tie (0); cout.tie (0);
	
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int l = 0, r = m;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (check (mid)) l = mid;
		else r = mid - 1;
	}
	if (l == m) cout << "infinite";
	else cout << l;
	return 0;
}
```

---

## 作者：__const_int__ (赞：0)

### Desciption
求满足 $\sum_{i=1}^{N} \min(x,a_i) \leq M$ 的 $x$ 的最大值。
### Analysis
观察发现，$x$ 越大补贴的越多，因此我们可知：答案具有单调性，所以可以二分求解 $x$。我们判断一下当前二分到的 $x$ 合不合法：如果 $\sum_{i=1}^{N} \min(x,a_i) \leq M$，则说明当前二分到的 $x$ 是合法的，记录答案并且让 $l = mid + 1$。否则说明当前二分到的 $x$ 大了，那么将 $r = mid - 1$。
### Code
```cpp
#include<bits/stdc++.h>

using ll = long long;
const int maxn = 200005;
const ll inf = 2000000000000000ll;

ll a[maxn], n, m;

int main(){
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    std::cin >> a[i];
  }
  ll l = 0, r = inf, x = 0;
  while (l <= r) {
    ll mid = (l + r) >> 1, sum = 0;
    for (int i = 1; i <= n; i++) {
      sum += std::min(a[i], mid);
    }
    if (m >= sum) {
      l = mid + 1;
      x = mid;
    } else {
      r = mid - 1;
    }
  }
  if (x == inf) {
    std::cout << "infinite\n";
  } else {
    std::cout << x;
  }
}

```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
$x$ 越大，需要补贴的钱越多，所以答案具有单调性。那么我们二分 $x$。初始时将左边界 $l$ 设为 $0$，右边界 $r$ 设为 $10^{14} \times 2$。求一下 $\sum_{i=1}^{N} \min(a_i,mid)$，如果这个值小于等于 $M$，那么我们记录一下答案，并且将 $l$ 变为 $mid+1$，继续二分。否则，我们将 $r$ 变为 $mid-1$，因为超出预算了。

最后输出答案。
### 代码
```cpp
#include<iostream>
#define int long long 
const int inf=(10e14)*2;
const int N=200005;
int a[N],n,m,result,sum;
signed main(){
    std::cin>>n>>m;
    for(int i=1;i<=n;i++){
        std::cin>>a[i];
        sum+=a[i];
    }
    int l=0,r=inf;
    while(l<=r){
        int mid=(l+r)>>1,ans=0;
        for(int i=1;i<=n;i++)
            ans+=std::min(a[i],mid);
        if(m>=ans){
            l=mid+1;
            result=mid;
        }else{
            r=mid-1;
        }
    }
    if(result==inf)puts("infinite");
    else std::cout<<result;
}

```

---

## 作者：Breath_of_the_Wild (赞：0)

二分答案板子题。

注意到题面中的 $x$ 有单调性，考虑二分答案。

因为 $A_i$ 最小为 $1$，所以左端点取 $0$ 或 $1$ 无所谓。右端点可以设到 $10^9+7$。

然后做一遍二分答案就行了。最后注意判断一下是否答案是无穷大。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e5+5,M=1e9;
ll n,m,a[N];
bool Chk(ll x){
	ll ans=0;
	for(ll i=1;i<=n;i++){
		ans+=min(x,a[i]);
	}
	return ans<=m;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	ll l=1,r=M+7;
	while(l<r){
		ll mid=l+r+1>>1;
		if(Chk(mid)) l=mid;
		else r=mid-1;
	}
	if(l>M) cout<<"infinite\n";
	else cout<<l<<'\n';
	return 0;
}
```

---

## 作者：yu1128_AKIOI (赞：0)

## 思路

二分。用 $\operatorname{f}$ 函数计算每个可取值 $x$ 的 $\sum_{i=1}^{n}\min(a_i,x)$。再用二分答案，计算出满足  $\operatorname{f}(x)\le m$ 中 $x$ 的最大值。在答案为 $r$ 时输出  `infinite`。

注意要开 `long long`。

## 代码


```cpp
#include<iostream>
using namespace std;
long long n,m,a[200005];
long long f(long long x){
	long long s=0;
	for(int i=1;i<=n;i++){
		s+=min(a[i],x);
	}
	return s;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	long long l=0,r=1e15;
	while(l<r){
		long long mid=(l+r)/2;
		if(f(mid)<=m) l=mid+1;
		else r=mid;
	}
	if(l<1e15)cout<<l-1;
	else cout<<"infinite";
}
```

---

## 作者：__O_v_O__ (赞：0)

先来判断无限大的情况：$x$ 再大，支出总费用也不会超过 $\sum\limits_{i=1}^na_i$ 之和，所以如果 $\sum\limits_{i=1}^na_i$ 之和小于等于 $m$，则 $x$ 可以无限大。

显然，这道题具有单调性，于是可以二分。具体来说，二分 $x$，在 `check` 函数中计算出总费用，与 $m$ 比较即可。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[1000001],mx,r,l,an;
bool ch(int x){
	int su=0;
	for(int i=1;i<=n;i++){
		su+=min(x,a[i]);
	}
    return su<=m;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
        cin>>a[i],mx+=a[i],r=max(r,a[i]);
	if(mx<=m){cout<<"infinite";return 0;}
	while(l<=r){
		int mi=l+r>>1;
		if(ch(mi))l=mi+1,an=mi;
		else r=mi-1;
	}
    cout<<an;
	return 0;
}
```

---

## 作者：COKENOTFOUND (赞：0)

# 题解：AT_abc365_c [ABC365C] Transportation Expenses

题目大意就是求一个正整数 $x$，将 $x$ 分别和序列中的每个元素求最小值，使得这些最小值之和最大且不超过 $M$。一个二分查找就能解决。

在二分过程中，需将每个 $mid$ 作为 $x$，判断结果是否大于 $M$，如果是则收缩右边界，反之收缩左边界。


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MX=1e6+10;
const int mod=1e9+7;
const int INF=0x3f3f3f;
ll n,m,a[MX];
ll check(ll k){
	ll res=0;
	for(ll i=1;i<=n;i++){
		res+=min(a[i],k);
	}
	return res;
}
void search(){
	ll L=1,R=1e18,mid;
	while(L<=R){
		mid=(L+R)>>1;
		if(check(mid)>m){
			R=mid-1;
		}
		else{
			L=mid+1;
		}
	}
	if(R==1e18){
		cout << "infinite\n";
		return ;
	}
	cout << R << "\n";
	return ; 
}
int main(){
	ll sum=0;
	cin >> n >> m;
	for(ll i=1;i<=n;i++){
		cin >> a[i];
	}
	sort(a+1,a+n+1);
	search();
	return 0;
}
//十年OI一场空，不开郎朗见祖宗
//数据不清空，爆零两行泪
```

---

## 作者：Ancap (赞：0)

首先，鉴于 Atcoder Beginner Contest 以及前两道题的难度，尝试暴力枚举。

```cpp
#include <bits/stdc++.h>
#define N 1000'0010
using namespace std;
int arr[N],sum=0,res=0;
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>arr[i],sum+=arr[i];
    if(sum<=m) cout<<"infinite";
    else
    {
        sum=0;
        while(sum<=m)
        {
            sum=0;
            res++;
            for(int i=1;i<=n;i++) sum+=min(res,arr[i]);
            //cout<<res<<sum;
        }
        cout<<res-1;
    }
	return 0;
}
```

得到一个 $\textcolor{#F0AB4A}{\text{WA}}$，判断算法并没有可见的缺陷，因此，需要更改算法。

发现随着变量 $x$ 数值的增加，其 $sum$ 呈单调递增顺序，因此，考虑二分法，得到如下代码。

```cpp
#include <bits/stdc++.h>
#define N 1000'0010
using namespace std;
int arr[N],sum=0;
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>arr[i],sum+=arr[i];
    sort(arr+1,arr+1+n);
    if(sum<=m) cout<<"infinite";
    else
    {
        int l=0,r=sum;
        while(l<=r)
        {
            int mid=(l+r+1)>>1,sum=0;
            for(int i=1;i<=n;i++) sum+=min(mid,arr[i]);
            if(sum<=m) l=mid+1;
            else r=mid-1;
        }
        cout<<l;
    }
	return 0;
}
```

分数更低了 QWQ

由于二分答案的复杂性，可以认为其中存在 bug，进行 debug 发现在部分情况下左右指针如果交叉，会导致 $l$ 意外移动到错误值，导致答案错误，所以应该留下一个，改为类似浮点二分的写法，即 `l-r>1||r-l>1` 或 `abs(l-r)>1` 或 `abs(r-l)>1` 的写法，***必须要判断 `l-r` 与 `r-l` 的结果或者使用绝对值，否则容易因为指针交叉而无法跳出循环***。

代码：

```cpp
#include <bits/stdc++.h>
#define N 1000'0010
using namespace std;
long long arr[N],sum=0;
signed main()
{
    long long n,m;
    cin>>n>>m;
    for(long long i=1;i<=n;i++) cin>>arr[i],sum+=arr[i];
    long long l=0,r=sum;
    while(l-r>1||r-l>1)
    {
        long long mid=(l+r+1)>>1,sum=0;
        for(long long i=1;i<=n;i++) sum+=min(mid,arr[i]);
        if(sum<=m) l=mid;
        else r=mid;
    }
    cout<<l;
	return 0;
}
```

但是，由于使用原题中说明日元数量要使用 $\min(x,A_i)$，所以有一种情况 $x$ 的值无效：$m \leq sum$ 原题中的对于这个情况的应对是输出 `infinite`，所以加上 `if(sum<=m) cout<<"infinite";` 进行特判。

完整代码：

```cpp
#include <bits/stdc++.h>
#define N 1000'0010
using namespace std;
long long arr[N],sum=0;
signed main()
{
    long long n,m;
    cin>>n>>m;
    for(long long i=1;i<=n;i++) cin>>arr[i],sum+=arr[i];
    if(sum<=m) cout<<"infinite";
    else
    {
        long long l=0,r=sum;
        while(l-r>1||r-l>1)
        {
            long long mid=(l+r+1)>>1,sum=0;
            for(long long i=1;i<=n;i++) sum+=min(mid,arr[i]);
            if(sum<=m) l=mid;
            else r=mid;
        }
        cout<<l;
    }
	return 0;
}
```

[提交记录。](https://atcoder.jp/contests/abc365/submissions/56449402)

---

## 作者：Special_Tony (赞：0)

# 思路
二分板子题，二分 $x$，每次判断 $\sum\min(x,a_i)\le m$ 是否成立即可。若 $\sum a_i\le m$，则 $x$ 不管多大都成立，输出 $\texttt{infinite}$。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, a[200005], l, r, mid, best;
ll sum, m;
bool check () {
	ll sum = 0;
	for (int i = 0; i < n; ++ i)
		sum += min (a[i], mid);
	return sum <= m;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	for (int i = 0; i < n; ++ i)
		cin >> a[i], r = max (r, a[i]), sum += a[i];
	if (sum <= m) {
		cout << "infinite";
		I AK IOI
	}
	while (l <= r) {
		mid = l + r >> 1;
		if (check ())
			l = mid + 1, best = mid;
		else
			r = mid - 1;
	}
	cout << best;
	I AK IOI
}
```

---

## 作者：popcoount (赞：0)

## 思路

二分一下 $x$，每次都统计一下补贴总额，如果符合要求，就记录答案。我们可以在二分前记录一下 $r$ 的初始值（$a_i$ 的最大值），如果直到二分结束 $r$ 的值都没有变，那么就说明 $x$ 是可以无限大的，输出 `infinite` 即可。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 10;
int a[N], n, m;
bool check(int mid) {
	int s = 0;
	for (int i = 1; i <= n; i++) s += min(mid, a[i]);
	return s <= m;
}
signed main() {
	scanf("%lld%lld", &n, &m);
	int l = 1, r = -0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		r = max(r, a[i]);
	}
	int t = r;
	int ans = -1;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid)) {
			ans = mid;
			l = mid + 1;
		} else r = mid - 1;
	}
	if (r == t) printf("infinite\n");
	else printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Alex_smy (赞：0)

## 题意简述
有 $N$ 个人参加了一次活动，其中第 $i$ 个人的交通费是 $A_i$ 日元。活动的组织者高桥决定为交通补贴设定最高限额 $x$，他会为第 $i$ 个人补贴 $\min(x,A_i)$ 日元。现在高桥希望所有人的交通补贴总额最多为 $M$ 日元，请你求出 $x$ 的最大可能值。如果 $x$ 可以无限大，输出 `infinite`。
## 解题思路
一道二分答案题。

基本思路：设定一个检查函数 $check$，然后在 $\left [ 0,m \right ]$ 这个区间内寻找 $x$。每次取中间值 $mid$，如果 $mid$ 符合条件，那么说明 $x$ 还可能更大，则让 $l=mid$；否则 $x$ 必须更小，则让 $r=mid-1$。

检查函数：枚举每个人，按照题意计算交通补贴总额 $sum$，如果 $sum>M$，那么返回假，否则返回真。

判断无限大：如果 $check(m)$ 为真，那么则说明 $x$ 可以无限大。为什么请读者自行思考。

整个程序的时间复杂度是 $O(n \log m)$。

记得开 long long。
## 参考代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,a[200010];
bool check(ll x){
	ll sum=0;
	for(int i=1;i<=n;i++){
		sum+=min(a[i],x);
		if(sum>m) return false;
	}
	return true;
}//检查函数
int main(){
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);//输入
	if(check(m)){
		printf("infinite");
		return 0;
	}//无限大
	ll l=0,r=m;
	while(l<r){
		ll mid=(l+r+1)>>1;//取中间值
		if(check(mid)) l=mid;//可行
		else r=mid-1;//不可行
	}//二分答案
	printf("%lld",l);
	return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：0)

# 题解：AT_abc365_c [ABC365C] Transportation Expenses
题目需要我们求的是最大的 $x$，而在满足条件的情况下，交通费补贴上限可以无限大。因此，如果 $\sum_{i=1}^{N}{A_i} \leq M$，则答案为 `infinite`；否则，答案必须介于 $0$ 和 $\max\{A_1,\dots,A_N\}$ 之间。

接下来我们考虑如何在这个区间内用二分查找答案。设当前猜测的答案为 $x$。尝试用每个人的交通费和 $x$ 比较，将结果求和，得出所有人中能够获得补贴的人的补贴总额。如果总额不超过 $M$，我们就可以将候选答案向右移动以增加 $x$；否则，我们就将候选答案向左移动以减小 $x$。在二分搜索结束后，所得到的 $x$ 就是所求的答案。

时间复杂度 $O(N\log W)$，其中 $W=\max\{A_1,\dots,A_N,M\}$。

---

## 作者：Leo2011 (赞：0)

[~~无耻的广告~~ 更好的阅读体验~](https://www.cnblogs.com/leo2011/p/18341200)

注：为了方便，下文以 $Sum$ 表示 $\sum_{i = 1}^{n} A_i$。

---

$N = 2 \times 10^5$，考虑二分答案。

所以，答案有单调性吗？或者说，可以二分吗？

当然！如果 $x = k$ 时可以满足条件，那么 $x = k - 1$ 时显然只会更少（上面取 $\min$ 的基本都没变，变了的取了更少的），一样能满足条件。

$\operatorname{check}$ 函数怎么写？扫一遍嘛，时间复杂度 $O(n)$，鉴于后面是 $\log$ 级别的复杂度这里就算暴力扫也超不了。

这样我们只需要考虑二分的上下界就好了。最低直接让 $x = 0$ 好了，最高肯定不会超过 $Sum$（超了那还了得？多的钱幽灵拿了？），就以此为界二分吧！

等等，我们漏了一个很重要的情况！那就是——无！解！

啥时候可以取到无限啊？

按照题意，需要的钱数最大也只有 $Sum$ 这么多，如果这还不到 $m$，即 $Sum \le m$，那么 $x$ 自然可以随便取，反正钱数都没它啥事儿……

还有一点，上面这一大堆东西时间复杂度到底是多少呢？

显然时间复杂度为 $\Theta(N \log Sum)$。感觉会超？注意时间限制是 2s ！~~拿计算器摁一下~~，最大值（两项都取到最大）大概是 $9.5 \times  10^7$，不会超~

然后就真的结束了……

---

ACCode:
```cpp
/*Code by Leo2011*/
#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define EPS 1e-8
#define FOR(i, l, r) for (ll(i) = (l); (i) <= (r); ++(i))
#define log printf
#define IOS                      \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);            \
	cout.tie(nullptr);

using namespace std;

typedef __int128 i128;
typedef long long ll;
typedef pair<ll, ll> PII;

const ll N = 2e5 + 10;
ll m, n, a[N], sum;

template <typename T>

inline T read() {
	T sum = 0, fl = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

template <typename T>

inline void write(T x) {
	if (x < 0) {
		putchar('-'), write<T>(-x);
		return;
	}
	static T sta[35];
	ll top = 0;
	do { sta[top++] = x % 10, x /= 10; } while (x);
	while (top) putchar(sta[--top] + 48);
}

inline bool chk(ll q) {
	ll sum = 0;
	FOR(i, 1, n) {
		sum += min(q, a[i]);
		if (sum > m) return 0;
	}
	return sum <= m;
}

int main() {
	scanf("%lld%lld", &n, &m);
	FOR(i, 1, n) scanf("%lld", &a[i]), sum += a[i];
	if (sum <= m) {
		log("infinite");
		return 0;
	}
	ll l = 0, r = sum, ret = -1;
	while (l <= r) {
		ll mid = (l + r) >> 1;
		if (chk(mid)) {
			ret = mid;
			l = mid + 1;
		} else r = mid - 1;
	}
	log("%lld\n", ret);
	return 0;
}
```

[AC 记录~](https://atcoder.jp/contests/abc365/submissions/56324104)

理解万岁！

---

## 作者：n_ni (赞：0)

## abc365-C 题解
### 题面
#### 题意
有 $N$ 人参加一项活动，第 $i$ 人的交通费用是 $A_i$。

活动组织者决定为交通补贴设定一个最大限额 $x$。第 $i$ 人的补贴为 $\min(x, A_i)$。这里，$x$ 必须是一个非负整数。

活动组织者预算为 $M$，他希望所有 $N$ 人的交通补贴总额最多为 $M$，那么补贴限额 $x$ 的最大可能值是多少？

如果补贴限额可以无限大，请输出 `infinite`。

#### 数据范围
-   $1 \leq N \leq 2 \times 10^5$
-   $1 \leq M \leq 2 \times 10^{14}$
-   $1 \leq A_i \leq 10^9$
### 思路
我们很容易发现 $x$ 越大，补贴越多；$x$ 越小，补贴越小。

这就满足了单调性，所以我们使用二分。

二分的下限是 $0$，上限是 $\max(A_i)$，因为如果 $x>\max(A_i)$，那么补贴总是 $\sum A_i$。我们还可以通过判断 $M$ 是否大于等于 $\sum A_i$ 来判断 $x$ 是否可以达到无穷大。如果是，那么 $x$ 可以达到无穷大，因为 $x$ 无论怎么增大，补贴都不会增长；否则 $x$ 不能达到无穷大。
#### 复杂度分析
时间复杂度：
- 二分：$\Theta (\log \max A_i )$
- 检查：$\Theta (N)$
- 总复杂度：$\Theta (N \log \max A_i)$

空间复杂度：$\Theta(N)$

可以轻松通过此题。

### 代码
```cpp
#include<iostream>
using namespace std;
#define int long long
#define Min(x,y) ((x)<(y)?(x):(y))
#define Max(x,y) ((x)>(y)?(x):(y))

int a[200010],sum,ma; //sum记录a总和，ma记录a中最大值
int n,m;

int bs(){
    int l=0,r=sum;
    while(l<r){
        int mid=(l+r)-(l+r>>1); //向上取整，因为如果r=l+1并且使用向下取整会死循环
        int tmp=0;
        for(int i=0;i<n;i++){
            tmp+=Min(a[i],mid);
        }
        if(tmp<=m)l=mid; //补贴小于等于m -> x小于等于正确答案
        else r=mid-1; //补贴大于m -> x大于正确答案
    }
    return l;
}

signed main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>a[i];
        sum+=a[i];
        ma=Max(ma,a[i]);
    }
    if(sum<=m){
        cout<<"infinite";
        return 0;
    }
    else cout<<bs();
    return 0;
}
```

---

## 作者：I_Love_DS (赞：0)

## 翻译

鉴于我的翻译机翻译的太差，就写一下吧。

------------------------------

有 $n$ 个人，第 $i$ 个人花了 $a_i$ 块钱。

小 K 手中有 $m$ 块钱，他觉得这些人花的钱好多，所以决定做一些补贴。他设定一个整数 $x$，他需要给第 $i$ 个人 $\min(a_i, x)$ 块钱。

显然，补贴总额**不能超过** $m$，所以请找出最大的 $x$。

如果 $x$ 可以为 $\infty$，输出 `infinite`。

## 思路

由题可知，随着 $x$ 的增大，补贴总额一定是单调不减的。

所以二分 $x$，找出可行的最大值。

如果最大值是我们设定的无限大的值，输出 `infinite`。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 50;
int n, a[N];
ll m;
bool check(int x) {
	ll sum = 0;
	for (int i = 1; i <= n; i++) sum += min(x, a[i]);
	return sum <= m;
}
int main() {
	scanf("%d%lld", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int l = 0, r = 1e9 + 50;
	while (l + 1 < r) {
		int mid = (l + r) / 2;
		if (check(mid)) l = mid;
		else r = mid;
	}
	if (r == 1e9 + 50) printf("infinite");
	else printf("%d", l);
	return 0;
}
```

有任何问题可在评论区提问，会一一私信解答。

---

## 作者：Cosine_Func (赞：0)

题意：对于给定的数列 $A$，找到一个最大的数 $X$ 使得 $\sum_{i-1}^{N}\max{X,A_i} \leq M$。若 $X$ 的最大值不存在，输出 `infinite`。

显而易见，$X$ 具有单调性，即 $\sum_{i-1}^{N}\max{X,A_i}$ 随着 $X$ 的增加而增加，因此可以考虑二分答案。令左端点为 $0$，右端点为 $A_{max}$，二分查找到答案。`check` 函数很好写，判断式子是否小于等于 $M$ 即可。该算法时间复杂度为 $O(N \times \log V)$，其中 $V$ 是 数列 $A$ 中的最大值。

`check` 函数参考代码：
```cpp
bool check(itn x){
	long long res=0;
	for(int i=1;i<=n;i++)
		res+=min(a[i],x);
	return res<=m;
}
```

二分部分参考代码：
```cpp
while(l<=r){
	int mid=l+(r-l)/2;
	if(check(mid))l=mid+1;
	else r=mid-1;
}
```

[完整参考代码](https://atcoder.jp/contests/abc365/submissions/56272819)

---

## 作者：Hog_Dawa_IOI (赞：0)

### 题意
有 $n$ 个人出差，要报销交通费，第 $i$ 个人的交通费为 $a_i$ 元。
如果钦定报销额度为 $x$ 元，那么对于第 $i$ 个人，公司会为它报销 $\min(x,a_i)$ 元。     
现在公司总共只有 $m$ 元用于交通费报销，问报销额度最高是多少？         
如果报销额度可以为无限大，那么输出 `infinite`。    
数据范围：$1 \le n \le 2 \times 10^5,1 \le m \le 2 \times 10^{14},1 \le a_i \le 1 \times 10^9$。    
### 分析
我们考虑二分这个报销额度。（是的，又是二分，似乎 ABC 系列比赛的 C、D 题很喜欢考二分。）    
对于二分出的答案，暴力遍历每个人算出公司对这个人报销的价钱，检查这个总和是否超过公司能提供的总金额。  
需要注意报销额度不会超过 $a_i$ 的最大值，所以可以把二分的上界 $r$ 设为 $(\max a_i) +1$。如果发现二分出的最后答案还是 $=(\max a_i) +1$，那么证明报销额度可以取到无限大。
### 代码
```cpp
#include<stdio.h>
long long n,m,s[200005],max;
int main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&s[i]),max=max>s[i]?max:s[i];
    long long l=0,r=max+1,ans;
    while(l<=r)
    {
      long long mid=(l+r)/2,sum=0;
      for(int i=1;i<=n;i++) sum+=(mid<s[i]?mid:s[i]);
      if(sum<=m) ans=mid,l=mid+1;
      else r=mid-1;
    }
    if(r==max+1) printf("infinite");
    else printf("%lld",ans);
}
```

---

## 作者：yegengghost (赞：0)

对于该题，我们发现数据较大，暴力枚举会超时，所以考虑二分答案。

可以先提前特判下是否已经满足要求：


```cpp
if(sum<=m)
	{
		cout<<"infinite"<<'\n';
		return 0;
	}
```

接着开始二分答案。主要核心函数大致是：将所有处理过的数值累加，每一次累加都要判断答案是否超过 $M$。最后就是满足结果的那一部分。就是这样步步紧逼，最后找到结果：


```cpp
bool check(int num)
{
	int funsum=0;
	for(int i=1;i<=n;i++)
	{
		funsum+=min(a[i],num);
		if(funsum>m)
			return false;
	}
	return true;
}
```
完整代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int mod=1;
int n,m;
int a[N];
int maxx;
int ksm(int x,int k)
{
	int ans=1,base=x;
	while(k)
	{
		if(k&1) ans=1ll*ans*base%mod;
		base=1ll*base*base%mod; k>>=1;
	}
	return ans;
}
int read()
{
	int f=1,x=0;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return f*x;
}
bool check(int num)
{
	int funsum=0;
	for(int i=1;i<=n;i++)
	{
		funsum+=min(a[i],num);
		if(funsum>m)
			return false;
	}
	return true;
}
signed main()
{
	n=read();
	m=read();
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		sum+=a[i];
		maxx=max(maxx,a[i]);
	}
	if(sum<=m)
	{
		cout<<"infinite"<<'\n';
		return 0;
	}
	sort(a+1,a+1+n);
	int l=1,r=maxx;
	int ans;
	while(l<r)
	{
		int mid=l+r+1>>1;
		if(check(mid))
		{
			l=mid;
		}
		else
		{
			r=mid-1;
		}
	}
	cout<<l<<'\n';
	return 0;
}
```

最后来一个编码时的小插曲来彰显我的唐化程度：

![](https://cdn.luogu.com.cn/upload/image_hosting/m0dknt43.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/hdfgobvq.png)

---

## 作者：L_xcy (赞：0)

建议评橙。

标签：二分答案。

### 解题思路

可以对 $[1,m]$ 这个区间进行二分，取的 $mid$ 就是现在拟定的答案。

统计当前答案下补贴的最大金额，如果这个金额小于等于 $m$，说明它是合法的，存起来，$L=mid+1$，否则说明它是不合法的，$R=mid-1$。

无限的情况也挺好想的，如果 $\sum_{i=1}^n a_i \le m$，说明无论最高限额有多高，也不会超过 $m$，输出 `infinite`。

[Code](https://atcoder.jp/contests/abc365/submissions/56322746)

---

## 作者：LuukLuuk (赞：0)

# 题解：AT_abc365_c [ABC365C] Transportation Expenses
---
### 题目大意
给定 $N$ 个数 $a_1,\dots,a_N$，叫你求出最大的 $x$，满足 $\sum_{i = 1}^n\min(a_i,x) \le M$，若可取到无限大，输出 infinite。

数据范围：$1 \le N,M \le 2 \times 10 ^ 5$,$1 \le a_i \le 10^9$

---
### 思路
从数据范围可以推出最大时间复杂度在 $\mathcal{O}(N \log N)$，考虑二分 $\mathcal{O}(\log N)$ 枚举 $x$，$\mathcal{O}(N)$ 时间暴力求和判断 $x$ 是否满足要求。另外，无解相当于 $\sum_{i = 1}^n a_i \le M$，令 $\min(a_i,x) = a_i$，因此直接求和判断即可。

---

### 代码

***一个细节：要开 long long！***
```cpp

#include <algorithm>
#include <cstdio>
using namespace std;

#define int long long

int a[200010];
int n, m, sum;

bool check(int mid) {
	int num = 0;
	for (int i = 1; i <= n; ++i) {//按照题意模拟 
		num += min(mid, a[i]);
	}
	return num <= m;//看和是否小于m 
}

signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		sum += a[i];//求和 
	}
	if (sum <= m) {//判无解 
		printf("infinite");
		return 0;
	}
	int l = 0, r = m + 1;//x一定在有解的情况下小于等于m 
	while (l < r) {//二分 
		int mid = (l + r + 1) >> 1;
		if (check(mid)) {
			l = mid;
		} else {
			r = mid - 1;
		}
	}
	printf("%lld", l);
	return 0;
}

```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

找到一个 $x$，使得 $\sum_{i=1}^{N} \min(x,a_i)\le m$，求出 $x_{\max}$。

## 解题思路

这一题考的是**二分**，二分 $x$ 对于 $0\sim m+1$ 这个区间，每个区间求一遍和 $ans$，如果 $ans>m$ 就 $r=mid-1$，反之 $l=mid+1$，最后的 $r$ 就是答案，如果 $r>m$ 就是 `infinite`。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
using namespace std;

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48); return;
}

ll n,m,a[200001],l,r,mid,ans;

int main()
{
    n=read(); m=read(); r=m+1;
    for(int i=1; i<=n; ++i) a[i]=read();

    while(l<=r)
    {
        mid=l+r>>1; ans=0;
        for(int i=1; i<=n; ++i) ans+=min(a[i],mid);
        if(ans>m) r=mid-1;
        else l=mid+1;
    }

    if(r>m) printf("infinite");
    else write(r);
    return 0;
}
```

---

## 作者：IronMen (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc365_c)

[AtCoder链接](https://atcoder.jp/contests/abc365/tasks/abc365_c)

---
## 题目
有 $N$ 个人，第 $i$ 个人的交通费用是 $A_i$ 日元。

高桥决定为交通补贴设定一个最高限额 $x$。第 $i$ 个人的补贴为 $\min(x,A_i)$ 日元。这里，$x$ 必须是一个非负整数。

高桥的预算为 $M$ 日元，他希望所有 $N$ 人的交通补贴总额最多为 $M$ 日元，那么补贴限额 $x$ 的最大可能值是多少？

如果补贴限额可以无限大，请输出 `infinite`。

---
## 思路
由题意得，如果 $N$ 个人的补贴总额没有超过 $M$，那么就说明 $x$ 可以是无限大。

下一问，$x$ 的最大值。如果采用暴力，肯定会 TLE。

那么，我们考虑二分。

对于一个答案 $x$，算出所需付的补贴金额，判断是否大于 $m$，如果在 $m$ 范围内，让 $x$ 变大，否则变小。

**十年 OI 一场空，不开 long long 见祖宗！**

---
### 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

long long n, m, a[200010], sum, l, r, md;

long long check(long long x)
{
	long long res = 0;
	for (long long i = 1; i <= n; i ++ )
		res += min(x, a[i]);
	return res;
}

int main()
{
	scanf("%lld %lld", &n, &m);
	for (long long i = 1; i <= n; i ++ )
	{
		scanf("%lld", &a[i]);
		sum += a[i];
	}
	if (sum <= m)
	{
		puts("infinite");
		return 0;
	}
	r = sum;
	while (l < r)
	{
		md = (l + r + 1) / 2;
		if (check(md) > m)
			r = md - 1;
		else
			l = md;
	}
	cout << l << '\n';
	return 0;
}
```

---

## 作者：Fantasy_Segment_Tree (赞：0)

## 题意

高桥有一笔 $M$ 元的钱，有 $n$ 个人需要，第 $i$ 个人的需求是 $A_i$。若高桥选定的最大值为 $X$，则第 $i$ 个人就会得到 $\min(A_i, X)$ 元的钱。现在请求出在总共钱数不超过 $M$ 的情况下， $X$ 的最大值。$X$ 必须是整数。

## 做法

容易发现，当 $X$ 越来越大，总共需要的钱也会越来越多。发现答案具有单调性，考虑二分答案。

若所有人的需求总和 $\leq M$，则可以达到无穷大。这点需要特判。

否则，对于每个值，若需要的钱数总和 $\leq M$，则将左端点提升，否则将右端点下降。

代码不放了。

---

## 作者：zhangxiaohan007 (赞：0)

这道题其实不要想得太复杂，也就一个二分套二分，没有很难。由于二分是 $O(\log{n})$ 的时间复杂度，所以二分套二分就是 $O(\log^2{n})$ 的时间复杂度，足以通过此题。

那具体怎么做呢？其实就是枚举最高津贴。但是看到 $m$ 很大的数据范围，怎么办呢？没错，这里我们就要用到二分答案。我们可以二分出最大津贴，然后检验当前枚举到的最大津贴是否符合要求。但是，每个人获得的津贴不一样，不好检测怎么办？这里，我们可以先给我们的 $a$ 数组排序，比当前最大津贴大的按最大津贴算，小的就按 $a_{i}$ 算。后面都用的是最大津贴很好算，那前面的又该怎么办呢？其实也很简单，因为 $a$ 数组已经是有序的了，而这里要求前面一些连续的数的和，那我们这里就可以在 $a$ 数组排完序后对其求一个前缀和就可以了。

下面给出参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define inf 2e9
using namespace std;
ll n,m,a[200005],sum[200005],maxn;
bool check(ll k)
{
	ll l=1,r=n,mid,ans=-1,ss;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(a[mid]>=k)
		{
			ans=mid;
			r=mid-1;
		}
		else
		{
			l=mid+1;
		}
	}
	ss=sum[ans-1]+(n-ans+1)*k;
	return ss<=m;
}
int main()
{
	cin>>n>>m;
	for(ll i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(ll i=1;i<=n;i++)
	{
		sum[i]=sum[i-1]+a[i];
	}
	if(sum[n]<=m)
	{
		cout<<"infinite";
		return 0;
	}
	ll l=0,r=a[n],mid,ans=-1;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))
		{
			ans=mid;
			l=mid+1;
		}
		else
		{
			r=mid-1;
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：luogu_gza (赞：0)

不难发现，问题等价于求最大的 $x$ 使得：

$$\sum_{i=1}^{n}\min(x,a_i) \leq m$$

容易发现左半边的柿子有单调性，因此二分即可。

[code](https://atcoder.jp/contests/abc365/submissions/56248776)。

---

