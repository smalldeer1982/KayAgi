# Stas and the Queue at the Buffet

## 题目描述

During a break in the buffet of the scientific lyceum of the Kingdom of Kremland, there was formed a queue of $ n $ high school students numbered from $ 1 $ to $ n $ . Initially, each student $ i $ is on position $ i $ . Each student $ i $ is characterized by two numbers — $ a_i $ and $ b_i $ . Dissatisfaction of the person $ i $ equals the product of $ a_i $ by the number of people standing to the left of his position, add the product $ b_i $ by the number of people standing to the right of his position. Formally, the dissatisfaction of the student $ i $ , which is on the position $ j $ , equals $ a_i \cdot (j-1) + b_i \cdot (n-j) $ .

The director entrusted Stas with the task: rearrange the people in the queue so that minimize the total dissatisfaction.

Although Stas is able to solve such problems, this was not given to him. He turned for help to you.

## 说明/提示

In the first example it is optimal to put people in this order: ( $ 3, 1, 2 $ ). The first person is in the position of $ 2 $ , then his dissatisfaction will be equal to $ 4 \cdot 1+2 \cdot 1=6 $ . The second person is in the position of $ 3 $ , his dissatisfaction will be equal to $ 2 \cdot 2+3 \cdot 0=4 $ . The third person is in the position of $ 1 $ , his dissatisfaction will be equal to $ 6 \cdot 0+1 \cdot 2=2 $ . The total dissatisfaction will be $ 12 $ .

In the second example, you need to put people in this order: ( $ 3, 2, 4, 1 $ ). The total dissatisfaction will be $ 25 $ .

## 样例 #1

### 输入

```
3
4 2
2 3
6 1
```

### 输出

```
12```

## 样例 #2

### 输入

```
4
2 4
3 3
7 1
2 3
```

### 输出

```
25```

## 样例 #3

### 输入

```
10
5 10
12 4
31 45
20 55
30 17
29 30
41 32
7 1
5 5
3 15
```

### 输出

```
1423```

# 题解

## 作者：da32s1da (赞：10)

$a_i\cdot (j-1)+b_i\cdot (n-j)=(a_i-b_i)\cdot j+(-a_i+b_i\cdot n)$

后面的$(-a_i+b_i\cdot n)$是定值，只需令$(a_i-b_i)\cdot j$最小即可。

也就是按照$(a_i-b_i)$排序分配位置。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e5+50;
int n,x,y,a[N];
long long Ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		Ans-=x;Ans+=1ll*y*n;//加上定值
		a[i]=x-y;
	}
	sort(a+1,a+n+1);//排序
	for(int i=1;i<=n;i++)Ans+=1ll*a[i]*(n-i+1);//a_i-b_i小的分配后面的位置
	printf("%I64d\n",Ans);
}
```

---

## 作者：midsummer_zyl (赞：7)

# 前置芝士:

``1ll`` 中的 ``ll`` 代表的是 ``long long``。

``*1ll`` 是为了在计算时，把 ``int`` 类型的变量转化为 ``long long``，然后再赋值给 ``long long`` 类型的变量，使后面的计算不会溢出。


### 阅读题目可知：

与楼下大佬们的思路相同：

每个人的不满意度是 $ a[i] \times (j - 1) + b[i] \times (n - j) $。

求其最小值。

化简可得：$ (a[i] - b[i]) \times j + b[i] \times n - a[i] $。

~~众所周知~~：$ b[i] \times n - a[i] $ 为定值，我们先抛开它不管。

所以我们只需求出 $ (a[i] - b[i]) \times j $ 的最小值即可。

## ROUND 1

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e8;
int a[N], b[N], s[N];
int sum;
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &a[i], &b[i]);
	for (int i = 1; i <= n; i++) {
		s[i] = a[i] - b[i];
		sum += (n * b[i]) - a[i]; 
	}
	sort(s + 1, s + n + 1, less<int>());
	for (int i = 1; i <= n; i++)
		sum += s[i] * i;
	printf("%d", sum);
	return 0;
}
```
当我们信心满满提交代码时，会惊讶地发现 wa 了！？

为何会出现错误呢？再次读题：

 $ 1 \le n \le 10^5;$

 $ 1 \le a[i], b[i] \le 10^8; $

真是十年 OI 一场空，不开龙龙（``long long``）见祖宗。

并且，我们应该使用 ``1ll`` 防止后面的计算溢出。

## ROUND 2

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6;
ll a[N], b[N], s[N];
ll sum, i, n;
int main() {
	scanf("%lld", &n);
	for (i = 1; i <= n; i++)
		scanf("%lld%lld", &a[i], &b[i]);
	for (i = 1; i <= n; i++) {
		s[i] = a[i] - b[i];
		sum += 1ll * b[i] * n - a[i];
	}
	sort(s + 1, s + n + 1, greater<int>());
	for (i = 1; i <= n; i++)
		sum += 1ll * s[i] * i;
	printf("%lld", sum);
	return 0;
}
```






## 最终代码（带注释）：
```cpp
#include <bits/stdc++.h>//万能头文件万岁！！
#define ll long long//偷个懒，嘻嘻。
using namespace std;
const int N = 1e6;
ll a[N], b[N], s[N];
ll sum, i, n;//全局变量自动赋初始值为0。
int main() {
	scanf("%lld", &n);
	for (i = 1; i <= n; i++)
		scanf("%lld%lld", &a[i], &b[i]);
	for (i = 1; i <= n; i++) {
		s[i] = a[i] - b[i];//s[i]存储a[i]与b[i]的差。
		sum += 1ll * b[i] * n - a[i];//运用推理的公式。
   		//"1ll"见前置芝士。
	}
	sort(s + 1, s + n + 1, greater<int>());//快排万岁！
   	//从大到小排列，从小到大是“less<int>()",或自创函数cmp。
	for (i = 1; i <= n; i++)
		sum += 1ll * s[i] * i;//"1ll"见前置芝士。
	printf("%lld", sum);
	return 0;
}//完结撒花~~
```
本蒟蒻的第一篇题解，求过！

点个赞吧！谢谢~

---

## 作者：Tarsal (赞：5)

本蒟蒻又双叒叕被爆踩辣！！！

[题目链接](https://www.luogu.org/problem/CF1151D)

~~这道题我个人觉得没有紫题的水平。~~

### 步入正题

先看题：

共有n个人，每个人2个属性,a,b;

窝们要求的是总的不满意度最小，最满意度的公式是什么？

$ai * (j - 1) + bi * (n - j)$

那么我将它化简就是这样的:

$ai * j - ai + bi * n - bi * j$

在化简：

$(ai - bi) * j + bi * n - ai$

窝们在把它拆开，分为:

$(ai - bi) * j$ 和 $bi * b - ai$

后者是不是一个定值？

前者的最小值是不是很好维护：

窝们将其排序，用小的序号对于大的权值，可以求解最小值。

那不就出来了？

```cpp
#include<bits/stdc++.h>

using namespace std;

const int dx[5] = {0, 1, -1, 0, 0};
const int dy[5] = {0, 0, 0, 1, -1};

//#define XRZ
#define int long long
#define maxn 100010
#define maxm
#define ll long long
#define mian main
#define inf 0x3f3f3f3f
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid (l + r >> 1)
#define debug(x) printf("now here is %d\n", x);
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout);
#define Rep(x, a, b) for(int x = a; x <= b; ++ x)
#define Dep(x, a, b) for(int x = a; x >= b; -- x)
#define Next(x, u) for(int i = head[u]; i ; i = e[i].nxt)

int n, a[maxn], b[maxn], c[maxn], ans;

bool cmp(int x, int y) {return x > y;}//因为要用小的序号对于大的权值，所以从大到小排序。

signed mian(){
	// file(a);
    scanf("%lld", &n);//读入
    Rep(i, 1, n){
        scanf("%lld%lld", &a[i], &b[i]);//输入每个角色的属性，好像a[],b[]并没有什么鸟用
        c[i] = a[i] - b[i];//这里是窝们求的(a[i] - b[i])，窝们只要维护它即可。
        ans += (n * b[i]) - a[i];//先加上定值。
    }
    sort(c + 1, c + n + 1, cmp);//排序。。。
    Rep(i, 1, n) ans += c[i] * i;//小的序号对于大的权值
    printf("%lld", ans);//输出
	return 0;
}


```


---

## 作者：OIerWu_829 (赞：4)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1151D) / [Codeforces 传送门](https://codeforces.com/problemset/problem/1151/D)

贪心题。

我们先来转化一下题目中的式子：

$$
\begin{aligned}
s_i&=a_i\cdot(i-1)+b_i\cdot(n-i)\\
   &=a_i\cdot i-a_i+b_i\cdot n-b_i\cdot i\\
   &=(a_i-b_i)\cdot i+b_i\cdot n-a_i
\end{aligned}
$$

注意到式子中有 $a_i-b_i$，所以我们按 $a_i-b_i$ 从大到小排序，然后按照上面的式子计算每个人的不满意度，最后累加输出即可。

注意数据范围是 $10^8$，**需要开 `long long`**。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

using LL = long long;

const LL N = 1e5 + 5;

struct Node
{
	LL a, b;
} p[N];

bool cmp(Node x, Node y)
{
	return x.a - x.b > y.a - y.b;
}

int main()
{
	LL n;
	cin >> n;
	for (LL i = 1; i <= n; i++)
		cin >> p[i].a >> p[i].b;
	sort(p + 1, p + 1 + n, cmp);
	LL ans = 0;
	for (LL i = 1; i <= n; i++)
		ans += (p[i].a - p[i].b) * i - p[i].a + p[i].b * n;
	cout << ans;
    return 0;
}
```

---

## 作者：lianchanghua (赞：4)

#### 题目大意
$n$ 个人，每个人有两个属性值 $a_i$，$b_i$。现在给他们重排，如果第 $i$ 个人站在第 $j$ 个位置，那么这个人的不满意度是 $a_i \times (j-1) + b_i \times (n-j)$。求出他们不满意程度的最小值。

#### 思路

我们先将式子展开看一下：

$a_i \times (j-1) + b_i \times (n-j)=a_i \times j-a_i+b_i \times n-b_i \times j=(a_i-b_i) \times j-a_i+b_i \times n$

我们可以把这个式子拆成两部分看：
$(a_i-b_i) \times j$ 和 $-a_i+b_i \times n$

我们就可以知道：后半部分基本定型，而前半部分还有改的余地，所以我们就可以先排序，然后再计算，排序规则为：按 $(a_i-b_i)$ 从大到小排，最后进行加和即可。

#### AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int x;
	int y;
}a[100005];
bool cmp(node x,node y){
	return x.x-x.y>y.x-y.y;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i].x>>a[i].y;
	sort(a+1,a+1+n,cmp);
	int sum=0;
	for(int i=1;i<=n;i++){
		int t=a[i].x*(i-1)+a[i].y*(n-i);
		sum+=t;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：Second_Gardenia (赞：3)

## 思路：
算法：贪心和排序。

重点：推式子。

过程：$ a_i \times(j - 1)+ b_i \times (n - j) = a_i \times j - a_i + b_i \times n - b_i \times j = j \times (a_i - b_i) + b_i \times n - a_i$

$b_i \times n - a_i$ 的部分是不会因为人的位置而改变的，所以我们可以先统计这些值，再进行排序，让 $a_i - b_i$ 小的排在前面，打的排在后面，这样子不满意度就会最小（贪心思想）。

## Code

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

#define int long long//小提示：要开longlong
const int N = 1e5 + 10;
int a , b , c[N];
int n , sum;

bool cmp(int a , int b){//从大到小排序
	return a > b;
}

signed main(){
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1;i <= n;++ i){
		cin >> a >> b;
		sum += b * n - a;//先用sum统计固定的b*n-a
		c[i] = a - b;//可以不用开a和b数组存，只用记录下a-b的值就行
	}
	sort(c + 1 , c + n + 1 , cmp);
	for(int i = 1;i <= n;++ i){
		sum += i * c[i];//sum再加上i*(a-b)
	}
	cout << sum << endl;
	return 0;
}
```


---

## 作者：sqrt404 (赞：2)

# CF1151D
$\text{Author: }$ [$\color{black}{\text{Sqrt404}}$](https://www.luogu.com.cn/user/637410)

### 思路
每个人对答案的贡献为：$a_i \times (j-1) + b_i \times (n-j)$。

我们将这个式子化简，得到 $j \times (a_i - b_i) + b_i \times n - a$。

可以发现一个人的不满意度中 $j \times (a_i - b_i)$ 会随着人的位置（$j$）变化，而 $b_i \times n - a$ 则为定值。

为了使答案最小，$a_i - b_i$ 大的时候就需要乘以小的 $j$，$a_i - b_i$ 小的时候就需要乘以越大的 $j$。所以我们只需计算出所有 $a_i - b_i$ 的值，然后根据 $a_i - b_i$ 的大小从大到小进行排序。最后统计答案。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int a, b, XD; // 存储每个人，XD 储存 a - b 的值
}x[100005];
int n, ans;
bool cmp(node s, node t)
{
	return s.XD > t.XD; 
}
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> x[i].a >> x[i].b;
		x[i].XD = x[i].a - x[i].b;
	}
	sort(x + 1, x + n + 1, cmp); // 从大到小进行排序
	for(int i = 1; i <= n; i++) ans += x[i].XD * i + x[i].b * n - x[i].a; // 统计答案
	cout << ans << endl;
	return 0;
}
```

---

## 作者：RioFutaba (赞：1)

## 题意
有 $n$ 个人，第 $i$ 个人有 $a_i$ 和 $b_i$。当第 $i$ 个人站在第 $j$ 个位置的时候，他的不满意度为 $a_i \times (j-1)+b_i \times (n-j)$。重排这 $n$ 个人，使得所有人的不满意度的和最小。
## 思路
首先化简式子。化简后每个人的不满意度为 $(a_i-b_i) \times j-a_i+b_i \times n$。

可以发现化简式子后面的 $-a_i+b_i \times n$ 是固定的，所以我们只需要使得 $(a_i-b_i) \times j$ 最小即可。

可以将 $a_i-b_i$ 小的放在下标较大的位置，这样就可以保证答案最小了。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long 
const int maxn=1e5+5;
int n,ans;
struct node{
	int a,b;
	bool operator<(node o){
		return a-b>o.a-o.b;
	}
}t[maxn];
signed main(){
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> t[i].a >> t[i].b;
		ans+=-t[i].a+t[i].b*n;
	}
	sort(t+1,t+n+1);
	for(int i=1;i<=n;i++) ans+=(t[i].a-t[i].b)*i;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Peter20122012 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1151D)

## 思路
首先我们分析一下第 $i$ 个人站在位置 $j$ 时的不满意度：
$$
a_{i} \cdot (j - 1) + b_{i} \cdot (n - j) = a_{i} \cdot j - a_{i} + b_{i} \cdot n - b_{i} \cdot j
$$
注意到这个多项式中的 $-a_{i}$ 与 $b_{i} \cdot n$ 这两个单项式是与 $j$ 无关的，也就是无论这个人站在哪里，都对答案有 $-a_{i} + b_{i} \cdot n $ 的贡献。而当其站在位置 $j$ 时将会额外有
$$
a_{i} \cdot j - b_{i} \cdot j = j \cdot (a_{i} - b_{i})
$$
的贡献，发现要尽可能的使 $j \cdot (a_{i} - b_{i})$ 大的人站在前面（使 $j$ 尽可能小），于是考虑贪心。

## 具体过程
对于输入的每一个 $a_{i}$ 和 $b_{i}$ 计算出 $c_{i} = a_{i} - b_{i}$，并按 $c_{i}$ 从大到小排序。然后对于每一个 $i$ 按 $a_{i} \cdot j - a_{i} + b_{i} \cdot n - b_{i} \cdot j$ 计算出对答案的贡献并求和。

**注意：十年 OI 一场空，不开 long long 见祖宗！**  
**还有：运算过程中注意 int 转 long long。**

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAX(x, y) (((x) >= (y)) ?(x) :(y))
#define MIN(x, y) (((x) <= (y)) ?(x) :(y))
#define FOR(st, ed, i) for (int i = st; i <= ed; ++i)
#define RFOR(st, ed, i) for (int i = ed; i >= st; --i)
#define fir first
#define sec second

//#define debug

typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int maxn = 1e5 + 10;

int n, a, b;

ll ans;
pll c[maxn];

int main () {
	scanf("%i", &n);
	FOR (1, n, i) {
		scanf("%i%i", &a, &b);
		
		c[i] = {a - b, (ll)(b)*n - a};
	}
	
	sort(c + 1, c + n + 1, greater<>());
	FOR (1, n, i) {
		ans += c[i].fir*i + c[i].sec;
	}
	
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：drah_yrev (赞：0)

### 思路
这道题的难点就在推出计算式子，让我们来分析一下：

$a_i\times(j-1)+b_i\times(n-j)$

$=a_i\times j-a_i\times1+b_i\times n-b_i\times j$

$=a_i\times j-b_i\times j-a_i\times1+b_i\times n$

$=(a_i-b_i)\times j+b_i\times n-a_i$

我们看后面的 $b_i\times n-a_i$，很显然它是个定值，与 $j$ 无关。

所以只要把 $(a_i-b_i)\times j$ 做到最小就好了，我们只需要将最大的 $a_i-b_i$ 乘上最小的 $j$，第二大的 $a_i-b_i$ 乘上第二最小的 $j$……，只需要将 $a_i-b_i$ 的值排序再乘上对应的 $j$，就可以了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,y,ans,i;
priority_queue<long long,vector<long long>,greater<long long> >q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		q.push(x-y);
		ans+=y*n-x;
	}
	i=n;
	while(!q.empty()){
		ans+=q.top() *i;
		q.pop();
		i--;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

这道题涉及到排队论和最优化理论，要求我们最小化一个特定函数的值。我们可以将其转化为一个更易处理的问题。

首先，我们将每个学生的不满意度函数重写为：
$$
f_i(j) = a_i \cdot (j-1) + b_i \cdot (n-j)
$$
其中，$f_i(j)$ 表示第 $i$ 个人在队伍中排在第 $j$ 位时的不满意度，$a_i$ 和 $b_i$ 分别表示该学生的两个属性值，$n$ 是队伍中总人数。

为了求解这个问题，我们先观察函数 $f_i(j)$ 的形式。可以发现，当 $j$ 越大时，由于 $a_i \cdot (j-1)$ 增长而 $b_i \cdot (n-j)$ 减小，不满意度的值将趋于减小；反之，当 $j$ 越小时，由于 $a_i \cdot (j-1)$ 减小而 $b_i \cdot (n-j)$ 增长，不满意度的值将趋于增大。因此，对于每个学生 $i$，存在一个最优的位置 $j_i$，使得 $f_i(j_i)$ 最小。

接下来，我们用数学方法求解。对 $f_i(j)$ 求最小值，可以转化为以下线性规划问题：

$$
\begin{aligned}
& \text{minimize} && \sum_{i=1}^{n} f_i(j_i) \
& \text{subject to} && 1 \leq j_i \leq n, \quad \forall i = 1, 2, \ldots, n
\end{aligned}
$$

由于每个 $f_i(j)$ 都是一个关于 $j$ 的线性函数，因此这个问题可以简化为比较 $a_i$ 和 $b_i$ 的大小。如果 $a_i > b_i$，那么 $j_i$ 应该尽可能小；如果 $a_i < b_i$，那么 $j_i$ 应该尽可能大。由此，我们可以得到一种贪心策略：按照 $a_i - b_i$ 的非减序排列学生，并依次放置他们，这样就能保证总不满意度最小。

最终算法如下：

对所有的 $a_i - b_i$ 进行非减序排序；
从前往后遍历排序后的学生数组，对于每个学生，计算其应在队伍中的位置，并将学生放入队伍；
计算总不满意度。

---

## 作者：qusia_MC (赞：0)

废话不多说，直接开始。
## 题目描述
给定 $a_{1…n}$，$b_{1…n}$ 求所有 $a_i\times(j-1)+b_i\times (n-j)$ 和的最小值。
## round 1
既然原式带括号，那么先将括号去掉，化简。

$a_i\times(j-1)+b_i\times (n-j)$ 去括号，利用乘法分配律变成：

$a_i\times j-a_i+b_i\times n-j\times b_i$ 再合并：

$(a_i-b_i)\times j-[a_i+b_i\times n]$。

后面（用中括号括起来的部分）是一锤子定死的，不能改变的，但是前面的部分会随着 $j$ 的变化而变化。

所以这道题就转化成了：求所有 $(a_i-b_i)\times j$ 和的最小值。
## round 2
接下来我们就要考虑怎么让 $(a_i-b_i)\times j$ 的和最小。首先，越大的数要配一个越小的 $j$ 让它发挥不出他的“威力”。所以，我们把它排个序，从小到大排，从第一个开始，每个数都配一个当前还能匹配的最小的 $j$。其实具体的关系和反比例相似，$(a_i-b_i)$ 越大，$j$ 就越小。

这里简称 $(a_i-b_i)$ 放在一个 $k$ 数组里。

以下是他们的关系：

这里我们假设 $n$ 为 $5$ ，排完序的 $k$ 数组就是 $1$ ~ $5$ 的数。

| j的值 |  5|  4|3  | 2 |1  |  越来越小|
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| k[i]的值| 1 |  2|  3|4  |5  |越来越大

有了这些，我们就可以轻松的打出代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,ai,bi,k[100010];
//k同上，ai,bi由于不需要保留，不用开数组
int cnt;//答案
signed main(){
    cin>>n;//输入
	for(int i=1;i<=n;i++){
	    cin>>ai>>bi;
        //输入ai,bi
	    cnt=cnt-ai+bi*n;
        //先把后面那一大坨“一锤子定死”的东西加上
	    k[i]=ai-bi;//累加k数组
	}
	sort(k+1,k+n+1);//排个序
	for(int i=n;i>=1;i--)cnt=cnt+k[(n-i+1)]*i;//k数组从小到大，j从大到小
	cout<<cnt;//输出
}
```

---

## 作者：wanghx (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1151D)

### 前置芝士
~~无~~，会化简~~柿~~子就可以

***

题目让我们最小化 $a_i\cdot(j-1)+b_i\cdot(n-j)$。

我们化简一下。

$$
\begin{aligned}

a_i\cdot(j-1)+b_i\cdot(n-j)&=a_i\cdot j-a_i+b_i\cdot n-b_i\cdot j \\
&=j\cdot(a_i-b_i)-a_i+b_i\cdot n

\end{aligned}
$$
我们可以发现后半部分 $-a_i+b_i\cdot n$ 是固定的值，和怎么放没有关系，可以在读入的时候直接计算。
所以就变成了最小化 $j\cdot(a_i-b_i)$。

我们将 $a_i-b_i$ 排序，用小的下标对大的差就可以了。

~~~cpp
#define int long long
int n,cha[N],a,b,ans; //cha[i]存的是第i个人属性值的差
signed main(){
	n=read();
	for(int i=1;i<=n;++i) a=read(),b=read(),ans+=b*n-a,cha[i]=a-b;
	sort(cha+1,cha+n+1);
	for(int i=1;i<=n;++i) ans+=cha[i]*(n-i+1);
	write(ans),ed;
	return 0;
}
~~~

---

## 作者：_HiKou_ (赞：0)

依照题目，每个人的不满意度为：

$$a_i × (j-1)+ b_i × (n-j) $$

化简可得：

$$(a_i-b_i)×j-a_i+b_i×n$$

把第 $i$ 个人放在任何一个位置，式子后半部分的结果 $-a_i+b_i×n$ 都是固定的。要让不满意度最小必须让前面的式子 $(a_i-b_i)×j$ 最小。

因为 $j$ 的总和是不变的，所以应该使较大的 $(a_i-b_i)$ 与较小的 $j$ 相乘即可使总和最小。具体原因可以自己琢磨。

至于排序部分我用的是结构体排序。

CODE:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,i,ans;
struct qwq{//结构体
	ll x,y;
} a[114514];
bool cmp(qwq a,qwq b)//排序函数
{return a.x-a.y>b.x-b.y;}//从大到小排序
int main(){
	scanf("%lld",&n);
	for(i=1;i<=n;i++)
	scanf("%lld%lld",&a[i].x,&a[i].y);
	sort(a+1,a+1+n,cmp);
	for(i=1;i<=n;i++)
		ans+=a[i].x*(i-1)+a[i].y*(n-i);//相加
	printf("%lld",ans);
	return 0; 
} 
```

---

## 作者：OYL2007 (赞：0)

**本人第一篇题解呦**

这一道题我自己推导了一遍

发现一个小问题，

如果用原本的公式去推导。

可不只是推导不出来这么简单~~而是已被本地测试答案错误气哭~~。

所以我把公式化简为 $(-a+b\cdot n)+j*(a-b)$ 

前面的值对于每一个数 $i$ 来说都是一个定值

关于乘法，我们应该尽可能使两个因数的差值尽可能小一点

所以我们只需要尽可能使较小的 $j$ 对应较大的 $(a-b)$ 即可

不说了，上代码
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
int pop[100010];
unsigned long long sum=0;
int n;
bool mycmp(int x,int y){
	return x>y;
}
int main(){
	cin>>n;
	int a,b;
	for(int i=1;i<=n;++i){
		cin>>a>>b;
		sum+=1ll*b*n-a;
		pop[i]=a-b;
	}
	sort(pop+1,pop+n+1,mycmp);
	for(int i=1;i<=n;++i){
		sum+=1ll*i*pop[i];//原来错了好多遍，最后这里想了想，虽然运算和不会越界，但单个数据有越界的可能，如果不加的话其实会有一个点卡住
	}
	printf("%lld",sum);
	return 0;
}
//a[i]-a[i]*j+b[i]*n-b[i]*j
//(-a[i]+b[i]*n)+j*(a[i]-b[i])
```


---

## 作者：wangyi_c (赞：0)



这一道题，看很多犇犇在输入时干很多很腻害的事，但本蒟蒻完全看不懂，用简单易懂的结构体结合快排自定义规则来完成这篇题解。

先理解题意，即让前面的式子 $(a_i - b_i)×j $ 保持最小，此结论可以用合并同类项得：

$$ (a_i - b_i)×j - a_i + b_i × n $$

分为前后两部分：$ (a_i - b_i)×j $ 和 $ - a_i + b_i × n $

然后发现式子中，对于每个 $ i $, $ - a_i + b_i × n $ 都是个定值，而前者的最小值很好维护，所以我们就可写出如下代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	int a,b;
}person[100010];//定义结构体
bool cmp(node x,node y){
	return x.a-x.b>y.a-y.b;//结构体排序
}
int main(){
	int sum=0;
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>person[i].a>>person[i].b;
    }
    sort(person+1,person+n+1,cmp);//用std库中的sort函数来排序
    for(int i=1;i<=n;i++){
        sum+=person[i].a*(i-1)+person[i].b*(n-i);//进行累加求值
    }
    cout<<sum;
    return 0;//完美结束
}
```
_THE END_

谢谢观看

By wangyi

---

