# Birthday

## 题目描述

Cowboy Vlad has a birthday today! There are $ n $ children who came to the celebration. In order to greet Vlad, the children decided to form a circle around him. Among the children who came, there are both tall and low, so if they stand in a circle arbitrarily, it may turn out, that there is a tall and low child standing next to each other, and it will be difficult for them to hold hands. Therefore, children want to stand in a circle so that the maximum difference between the growth of two neighboring children would be minimal possible.

Formally, let's number children from $ 1 $ to $ n $ in a circle order, that is, for every $ i $ child with number $ i $ will stand next to the child with number $ i+1 $ , also the child with number $ 1 $ stands next to the child with number $ n $ . Then we will call the discomfort of the circle the maximum absolute difference of heights of the children, who stand next to each other.

Please help children to find out how they should reorder themselves, so that the resulting discomfort is smallest possible.

## 说明/提示

In the first example, the discomfort of the circle is equal to $ 1 $ , since the corresponding absolute differences are $ 1 $ , $ 1 $ , $ 1 $ and $ 0 $ . Note, that sequences $ [2, 3, 2, 1, 1] $ and $ [3, 2, 1, 1, 2] $ form the same circles and differ only by the selection of the starting point.

In the second example, the discomfort of the circle is equal to $ 20 $ , since the absolute difference of $ 10 $ and $ 30 $ is equal to $ 20 $ .

## 样例 #1

### 输入

```
5
2 1 1 3 2
```

### 输出

```
1 2 3 2 1
```

## 样例 #2

### 输入

```
3
30 10 20
```

### 输出

```
10 20 30
```

# 题解

## 作者：封禁用户 (赞：2)

## CF1131C Birthday
[原题链接](https://www.luogu.com.cn/problem/CF1131C) 代码最短，时间最优解。

## 分析
先写一组长度为奇数的数据 $a_{1}\sim a_{5}$，其长度记为 $n$：
- 1 4 3 8 6

将这组数据排序，得到有序数列 $(1,3,4,6,8)$，将它们围成一个环，显然不是最优情况。那么何时情况最优呢？可以尝试用贪心思想找到局部最优解。

先找到最大值和最小值，当 $1$ 与 $3$，$4$ 相邻时差值最小，$8$ 与 $4$，$6$ 相邻时差值最小。这时发现，最大值和最小值都与中位数 $4$ 相邻。
得到两个数列 $(3,1,4)$ 和 $(4,8,6)$，合并得 $(3,1,4,8,6)$。由于得到的数列是一个环，故可以表示为 $(1,4,8,6,3)$，排列方式为 $(a_{1},a_{3},a_{5},a_{4},a_{2})$，即先顺序排列 $a$ 的奇数位置，再从 $n-1$ 位置开始倒序排列 $a$ 的偶数位置。

再写一组长度为偶数的数据 $a_{1}\sim a_{4}$，长度同样记为 $n$：
- 2 6 3 1

排序，得到有序数列 $(1,2,3,6)$，找到最大值和最小值，当 $1$ 与 $2$，$3$ 相邻时差值最小，$6$ 与 $2$，$3$ 相邻时差值最小。发现，最大值和最小值都与 $2$，$3$ 相邻。得到数列 $(2,1,3)$ 和 $(3,6,2)$，合并得 $(1,3,6,2)$。依然是先顺序排列 $a$ 的奇数位置，但后面变成了从 $n$ 位置开始倒序排列 $a$ 的偶数位置。

简单归纳一下，将数列排序后：

1. $n$ 为奇数时，先顺序输出 $a$ 的奇数位置，再从 $n-1$ 位置开始倒序输出 $a$ 的偶数位置。

2. $n$ 为偶数时，先顺序输出 $a$ 的奇数位置，再从 $n$ 位置开始倒序输出 $a$ 的偶数位置。

用 ```sort()``` 排一遍序，输出奇数位，判断 $n$ 的奇偶性，输出偶数位，结束。

## Code
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[105],n;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i+=2) cout<<a[i]<<" "; //输出奇数位置 
    if(n%2==0) for(int i=n;i>=2;i-=2) cout<<a[i]<<" "; //长度为偶，从n开始 
    else for(int i=n-1;i>=2;i-=2) cout<<a[i]<<" "; //长度为奇，从n-1开始 
    return 0; 
}
```


---

## 作者：cff_0102 (赞：1)

把 $n$ 个数摆成一个环，使相邻的数的差之和最小。

显然，这个环的数据如果像下面一样排列，结果是最小的（假设 $a_1\le a_2\le\dots\le a_n$）：

- $a_1,a_3,a_5,a_7,\dots,a_{n-2},a_n,a_{n-1},a_{n-3},\dots,a_6,a_4,a_2,a_0$（$n$ 为奇数）
- $a_1,a_3,a_5,a_7,\dots,a_{n-3},a_{n-1},a_n,a_{n-2},a_{n-4},\dots,a_4,a_2,a_0$（$n$ 为偶数）

形象一点来说，要是排列像一个“山峰”时，答案是最小的。可以很容易证明，不可能有更小的答案。

题目要求输出这个序列，那就直接按照上面的排列输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[114];
int main(){
	int n;cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	sort(a,a+n);// 排序
	// 从小到大输出奇数位上的数
	for(int i=0;i<n;i++){
		if(i%2)cout<<a[i]<<" ";
	}
	// 从大到小输出偶数位上的数
	for(int i=n-1;i>=0;i--){
		if(i%2==0)cout<<a[i]<<" ";
	}
	return 0;
}
```

---

## 作者：Daniel_7216 (赞：1)

先考虑站成一排，显然每个位置旁边的；两个都要和这个数的差值尽量小，于是想到可以排序。

接下来考虑题中的环形。由于第一个位置和最后一个位置相邻，所以这两个位置上的数应该分别是最小和次小，或者最大或次大。这里就假设第一个位置放最小的值。根据刚才推出的站成一排的结论，第二个位置应放第三小值，倒数第二个应该放第四小值。以此类推，得出来的序列应该是山峰形。直观一点，假设一共十一个数，现在已经排好序了，那它们这么放的时候就是一种最优解：

$A_1,A_3,A_5,A_7,A_9,A_{11},A_{10},A_8A_6,A_4,A_2$

做的时候也很简单，先排序，然后维护一个双端队列，轮流向队头和队尾插入数字。

上代码：
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;
int n, a[101];
bool cmp(int a, int b){
	return a > b;
}
deque <int> ans;
int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}
	sort(a, a + n, cmp);
	for (int i = 0; i < n; i++){
		if (i % 2 == 0){
			ans.push_back(a[i]); 
		}else{
			ans.push_front(a[i]); 
		}
	}
	for (int i = 0; i < n; i++){
		printf("%d ", ans.front());
		ans.pop_front();
	}
	return 0;
}
```

---

## 作者：Rbu_nas (赞：1)

题意说的已经很清楚了，$n$个人站成一圈求彼此身高最大差值的最小值。很明显的贪心。

因为是环形，所以我们将$a$数组排序，奇数下标排一起，偶数下标逆序排一起，即：

$a_1$ $a_3$ $a_5$ $...$ $a_{2n-1}$ | $a_{2n}$ $...$ $a_6$ $a_4$ $a_2$

这样的排法彼此差值最小，因为如果按相邻下标放一起，得到的差值肯定不是最优：

当$n = 5\ \ ,\ a[]={1, 2, 3, 4, 5}$ 时

$1$ $2$ $3$ $4$ $5$ $\Rightarrow{} \ max=4$

$1$ $3$ $5$ $4$ $2$ $\Rightarrow{} \ max=2$

显然可以证明，任何情况下都有奇偶排法最优

$\mathcal{Code}$

![](https://i.loli.net/2019/03/02/5c79f4a934946.jpg)

---

## 作者：LJC00118 (赞：1)

先将 $ a $ 数组排序，$ a[1] $ 一定会和两个人相邻，最优的情况显然是 $ a[1] $ 和 $ a[2] $，$ a[1] $ 和 $ a[3] $ 相邻

这个时候 $ a[4] $ 显然要和 $ a[2] $ 或 $ a[3] $ 当中的一个相邻

如果 $ a[4] $ 和 $ a[3] $ 相邻，$ a[2] $ 必须找一个大于等于 $ a[4] $ 的放在他旁边，这样显然没有 $ a[4] $ 和 $ a[2] $ 相邻优秀，因此 $ a[4] $ 要和 $ a[2] $ 相邻

归纳一下发现是一个这样的排列方法 ：$ a[1], a[3], a[5], a[7], a[9] ...... a[n - 1], a[n], a[n - 2], a[n - 4], a[n - 6] ...... a[2] $（$ n $ 为偶数时的情况

$ n $ 为奇数时类似

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

template <typename T>
struct hash_map_t {
    vector <T> v, val, nxt;
    vector <int> head;
    int mod, tot, lastv;
    T lastans;
    bool have_ans;

    hash_map_t (int md = 0) {
        head.clear(); v.clear(); val.clear(); nxt.clear(); tot = 0; mod = md;
        nxt.resize(1); v.resize(1); val.resize(1); head.resize(mod);
        have_ans = 0;
    }

    bool count(int x) {
        int u = x % mod;
        for(register int i = head[u]; i; i = nxt[i]) {
            if(v[i] == x) {
                have_ans = 1;
                lastv = x;
                lastans = val[i];
                return 1;
            }
        }
        return 0;
    }

    void ins(int x, int y) {
        int u = x % mod;
        nxt.push_back(head[u]); head[u] = ++tot;
        v.push_back(x); val.push_back(y);
    }

    int qry(int x) {
        if(have_ans && lastv == x) return lastans;
        count(x);
        return lastans;
    }
};

const int N = 105, INF = 0x7fffffff;

int a[N];
int n, ans;

int main() {
    read(n);
    for(register int i = 1; i <= n; i++) read(a[i]);
    sort(a + 1, a + n + 1);
    if(n == 2) {
        cout << a[1] << " " << a[2] << endl;
        return 0;
    }
    ans = a[3] - a[1];
    for(register int i = 1; i <= n; i += 2) print(a[i], ' ');
    if(n & 1) {
        for(register int i = n - 1; i >= 2; i -= 2) print(a[i], ' ');
        putchar('\n');
        return 0;
    }
    for(register int i = n; i >= 2; i -= 2) print(a[i], ' ');
    putchar('\n');
    return 0;
}
```

---

## 作者：hyfhaha (赞：1)

# CF大水题
题意：给你n个人，他们的身高是a[i]，让你将这几个人排成一个环，使得他们两两之间身高差的和最小。

思路：简单到爆了，恶意评分上蓝。直接将那几个人排个序，然后按序左右放就行了，也就是说1号放中间，2号放暂时序列最右边，3号放最左边，4号又放最右边，以此类推。

本人代码写的不规范，所以可能跑得会慢一些，但是以这题的数据量，绰绰有余了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10001],b[10001],n,flag;
int main(){
    memset(b,-1,sizeof(b));
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    sort(a+1,a+n+1);
    b[n]=a[1];
    for(int i=2;i<=n;i++){
        if(i%2==0)flag=1;else flag=-1;
        b[n+flag*(i/2)]=a[i];
    }
    for(int i=1;i<=n*3;i++)
        if(b[i]!=-1)printf("%d ",b[i]);
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# Solution

[原题传送门](https://codeforces.com/problemset/problem/1131/C)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1131C)

## Part 1 题目大意：

有 $n$ 个数摆放在一个环形中（最后一个与第一个相邻），需要改变这些数的顺序，使得相邻两个数的最大绝对差最小。如果有多种最佳方案，输出任意一种。

## Part 2 解题思路：

观察题目，发现是个环形树链，再看样例，可发现要使得相邻两个数的最大绝对差最小，需要将最大数放在中间，同一个山峰，想要达到这种效果，也就要排序后，奇偶数在两边输出，也就只用一个正序、一个倒序输出即可。

## Part 3 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101];
int main(){
    int n;cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);// 排序
    for(int i=1;i<=n;i++)// 正序奇数
        if(i%2)cout<<a[i]<<" ";
    for(int i=n;i>=1;i--)// 倒序偶数
        if(!(i%2))cout<<a[i]<<" ";
    return 0;
}
```

## Part 4 总结：

好了，这就是本题题解，难度不大，感谢大家的阅读！

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1131C)

一眼看去：绝对差最小不是只要排个序就行了吗？

这道也能算黄题？

但再看下去，发现事情没有这么简单：题目要求摆成环形。

那么排序就不行了，因为最大的和最小的会相邻，导致绝对差变最大了。

没办法，那就只能想**构造方法**。

观察样例 $1$，你发现了什么？

没错，数据像一个山峰，从 $a_1$ 到 $a_3$ 呈上升趋势，而 $a_3$ 到 $a_5$ 呈下降趋势。而 $a_1$ 和 $a_5$ 都是最小的 $1$，当然不会导致绝对差值变大啦。

而样例 $2$ 我们还可以变成：

```cpp
10 30 20
```
也是一个山峰。

那么构造方法就确定了：构造一个山峰，就能使绝对差最小。

具体的构造方法其实也是非常的简单的：先排序，然后把奇数下标的**从小到大**放在一起，把偶数下标的**从大到小**放在一起，就能构造出山峰了。

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[114];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		if(i%2==1)
			cout<<a[i]<<" "; 
	for(int i=n;i>=1;i--)
		if(i%2==0)
			cout<<a[i]<<" ";
	return 0;
}
```


---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现当把这 $n$ 个数摆成一个**山峰**时，相邻两个数的最大绝对差是最小的。例如有 $5$ 个数，将它们按从小到大排序后，输出为 $a_1~a_3~a_5~a_4~a_2$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(i%2==1){
			cout<<a[i]<<" ";
		}
	}
	for(int i=n;i>=1;i--){
		if(i%2==0){
			cout<<a[i]<<" ";
		}
	}
	return 0;
}
```


---

## 作者：Arrtan_73 (赞：0)

# 题解 CF1131C
## 题目大意
[传送门](https://www.luogu.com.cn/problem/CF1131C)
## 题目思路
从题目中很容易就可以看出来用贪心。首先我们把数列排个序，得到递增序列 $a_1,a_2,a_3,...,a_{n-1},a_n$，因为序列是首尾相接的，呈环状，所以首尾应都是最大或最小。经过整理，最优序列应为以下两种：
- $a_1,a_3,...,a_{n-1},a_n,a_{n-2},...,a_4,a_2$
- $a_n,a_{n-2},...,a_2,a_1,a_3,...,a_{n-3},a_{n-1}$

不难发现，整个序列是分为左右两部分，以奇偶区分，整体呈山峰形或低洼形即可。
## code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, a[N];
deque<int> q;//STL双头队列维护

bool cmp(int a, int b) {
	return a > b;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)cin >> a[i];
	sort(a + 1, a + n + 1, cmp);//快排
	for (int i = 1; i <= n; i++)
		if (i % 2 == 1)
			q.push_back(a[i]);//奇数放入头节点
		else 
			q.push_front(a[i]);//偶数放入尾节点
	for (int i = 1; i <= n; i++)
		cout << q.front() << " ",q.pop_front();//正序输出即可
	return 0;
}
```


---

## 作者：_shine_ (赞：0)

## 题目大意
现在有 $n$ 个数，被放成了一个环形，现在问你如何能让相邻的两项的绝对值之差最小。
## 思路
我们采用破坏成链的思想，既然要让每一项的绝对值差距最小，那我们其实就可以通过排序的方法，每次插着输出：

假设序列为 $1,2,3,4,5,6,7$，那我们就可以发现，最优的方案为 $1,3,5,7,6,4,2$，因为这样能使得每一项的绝对值之差小于 $2$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e2+10;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')w=-1;ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';
        ch=getchar();
    }
    return s*w;
}
inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)write(x/10);
    putchar(x % 10 + '0');
}
int n,a[maxn];
vector<int>ans;
signed main(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i){
		if(i%2==0)ans.push_back(a[i]);
		else cout << a[i] << " ";
	}
	for(int i=ans.size()-1;i>=0;--i){
		cout << ans[i] << " ";
	}
	return 0;
}

```


---

## 作者：CQ_Bab (赞：0)

# 思路
这道题我们发现它是一个环形数链，所以我们不能直接输出从小到大的 $a$ 所以我们要让第 $a_1$ 与 $a_n$ 个的差值最小，那么 $a_n$ 就是 $a_2$，然后我们再观察一下样例一，我们就能发现若此序列为山峰序列那么它的差值一定最小，所以我们只需要用这 $n$ 个数构成一个山峰序列即可。那么我们就将排完序后的奇数项正着输出，然后将偶数项倒着输出即可。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define rep(i,x,y) for(int i=x;i<=y;++i)
int n,a[1001000];
int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	rep(i,1,n) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i+=2) cout<<a[i]<<" ";//奇数项正着输出
	for(int i=n;i>=2;i--) if(i%2==0) cout<<a[i]<<" "; //偶数项倒序输出
	return false;
}
```
这个代码还是很简单的！

---

## 作者：Symbolize (赞：0)

# 思路
这道题毫无疑问，破环成链，然后因为是求最值的题，先排序再说，排完序过后发现，如果我们构造一个单峰的数组，那么一定是最优的，，因为这样满足局部最优解，及对于新的数组，有 $\forall i,j,k \in [1,n],|a_i-a_{i-1}|+|a_i-a_{i+1}| \le |a_i-a_j|+|a_i-a_k|$。

如何解决呢？

前面已经排过序了，那最后的数组就是 $a_1,a_3,a_5\dots a_{2 \times k + 1},a_{\lfloor \frac{n}{2} \rfloor \times 2},a_{(\lfloor \frac{n}{2} \rfloor - 1) \times 2},a_{(\lfloor \frac{n}{2} \rfloor - 2) \times 2}\dots a_2$。

# Code
下面附上 AC 代码！！！

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e5+10;
using namespace std;
int n,a[N];
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
signed main()
{
	n=read();
	rep1(i,1,n) a[i]=read();
	sort(a+1,a+1+n);//排序
	rep1(i,1,n) if(i&1/*奇数*/) cout<<a[i]<<' ';//正序输出下标为奇数的数
	rep2(i,n,1) if(!(i&1)/*偶数*/) cout<<a[i]<<' ';//倒序输出下标为偶数的数
	return 0;//收场
}
```

---

## 作者：SGColin (赞：0)

首先最后得到的序列显然只有一个“山峰”，因为排序后数组相邻元素的差值显然要优于“山峰”相邻元素的差值。

 现在考虑怎么往最大的值两侧放其他的值，首先一定要两侧都放，然后相邻的不能差太大。因此可以偶数项按从大到小放到最大值右侧，奇数项放左侧，微扰法即可证明这样是最优的。
 
```C++
 for (int i = 1; i <= n; ++i) a[i] = rd();
 sort(a + 1, a + 1 + n);
 s[1] = a[n];
 for (int i = n - 1, ptr1 = 2, ptr2 = n; i; --i)
   if (i & 1) {s[ptr1] = a[i]; ++ptr1;}
   else {s[ptr2] = a[i]; --ptr2;}
 for (int i = 1; i <= n; ++i) printf("%I64d ", s[i]);
```

---

