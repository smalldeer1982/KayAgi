# Twist the Permutation

## 题目描述

Petya got an array $ a $ of numbers from $ 1 $ to $ n $ , where $ a[i]=i $ .

He performed $ n $ operations sequentially. In the end, he received a new state of the $ a $ array.

At the $ i $ -th operation, Petya chose the first $ i $ elements of the array and cyclically shifted them to the right an arbitrary number of times (elements with indexes $ i+1 $ and more remain in their places). One cyclic shift to the right is such a transformation that the array $ a=[a_1, a_2, \dots, a_n] $ becomes equal to the array $ a = [a_i, a_1, a_2, \dots, a_{i-2}, a_{i-1}, a_{i+1}, a_{i+2}, \dots, a_n] $ .

For example, if $ a = [5,4,2,1,3] $ and $ i=3 $ (that is, this is the third operation), then as a result of this operation, he could get any of these three arrays:

- $ a = [5,4,2,1,3] $ (makes $ 0 $ cyclic shifts, or any number that is divisible by $ 3 $ );
- $ a = [2,5,4,1,3] $ (makes $ 1 $ cyclic shift, or any number that has a remainder of $ 1 $ when divided by $ 3 $ );
- $ a = [4,2,5,1,3] $ (makes $ 2 $ cyclic shifts, or any number that has a remainder of $ 2 $ when divided by $ 3 $ ).

Let's look at an example. Let $ n=6 $ , i.e. initially $ a=[1,2,3,4,5,6] $ . A possible scenario is described below.

- $ i=1 $ : no matter how many cyclic shifts Petya makes, the array $ a $ does not change.
- $ i=2 $ : let's say Petya decided to make a $ 1 $ cyclic shift, then the array will look like $ a = [\textbf{2}, \textbf{1}, 3, 4, 5, 6] $ .
- $ i=3 $ : let's say Petya decided to make $ 1 $ cyclic shift, then the array will look like $ a = [\textbf{3}, \textbf{2}, \textbf{1}, 4, 5, 6] $ .
- $ i=4 $ : let's say Petya decided to make $ 2 $ cyclic shifts, the original array will look like $ a = [\textbf{1}, \textbf{4}, \textbf{3}, \textbf{2}, 5, 6] $ .
- $ i=5 $ : let's say Petya decided to make $ 0 $ cyclic shifts, then the array won't change.
- $ i=6 $ : let's say Petya decided to make $ 4 $ cyclic shifts, the array will look like $ a = [\textbf{3}, \textbf{2}, \textbf{5}, \textbf{6}, \textbf{1}, \textbf{4}] $ .

You are given a final array state $ a $ after all $ n $ operations. Determine if there is a way to perform the operation that produces this result. In this case, if an answer exists, print the numbers of cyclical shifts that occurred during each of the $ n $ operations.

## 说明/提示

The first test case matches the example from the statement.

The second set of input data is simple. Note that the answer $ [3, 2, 1] $ also gives the same permutation, but since the total number of shifts $ 3+2+1 $ is greater than $ 0+0+1 $ , this answer is not correct.

## 样例 #1

### 输入

```
3
6
3 2 5 6 1 4
3
3 1 2
8
5 8 1 3 2 6 4 7```

### 输出

```
0 1 1 2 0 4 
0 0 1 
0 1 2 0 2 5 6 2```

# 题解

## 作者：lizhous (赞：7)

# 分析
**问题转换**：因为第 $i$ 轮的操作并不会影响到 $i$ 之后的数字，所以我们可以看成每次操作后往原序列末尾添加一个数。因为是从小到大添加，所以不可能在大数之间添加小数。  
**操作分析**：对于每一次操作，我们设操作完的序列为 $b$，$b$ 在经过若干次操作后将成为 $a$ 的一个不连续子序列，否则将无法完成操作。这次操作后插入一个数 $w$，为保证序列仍是 $a$ 的一个不连续子序列，设 $b$ 的最后一项在 $a$ 中位置为 $j$ ，则 $b_j$ 应为 $a_k(1 \le k \le j)$ 使得不存在 $z(k\le z \le j)$ 使得 $a_z<w$。们在这轮操作需要做的就是将当前 $b$ 中的这项移到末尾。说人话，就是将 $b$ 中的一个数，它在 $a$ 中在新加入的数的右边且是在当前 $b$ 中距离新加入的数最近，使用操作移到序列最末尾。  
**无解**：根据上面的操作，显然不可能无解。  
```cpp
scanf("%d", &t);
while (t--) {
	memset(ans, 0, sizeof(ans));
	itt = 2; //init
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		ton[a[i]] = i; //用桶标记i的位置
	}
	for (int i = 1; i < n; i++) {
		itt = ton[i]; //当前序列的结尾，就是上次插入的
		it = ton[i + 1]; //从新插入的数往前扫，找到最近的b[j]
		while (a[it] > i) { //往前找b[j]
			it--;
			if (it == 0) it = n;
		}
		while (a[itt] != a[it]) { //在当前b中找到j
			itt--;
			if (itt == 0) itt = n;
			while (a[itt] > i) {
				itt--;
				if (itt == 0) itt = n; //指针往前移动模拟一次操作
			}
			ans[i]++; //顺便累加操作次数
		}
	}
	itt = ton[n]; //最后将序列转到正确的位置
	it = n;
	while (a[itt] != a[it]) {
		itt--;
		if (itt == 0) itt = n;
		ans[n]++;
	}
	for (int i = 1; i <= n; i++) {
		cout << ans[i] << ' '; //输出
	}
	cout << endl;
}
```
时间复杂度 $O(n^2)$

$\text{Update}$：更改了码风

---

## 作者：封禁用户 (赞：2)

## CF1650D Twist the Permutation 题解

### 解题思路
因为每一次变换只会影响 $1$ 到 $i$ 个元素，所以只有最后一次变换可以影响到最后一位元素，由于最后一次变换固定下来了最后一位，所以我们可以忽略最后一位，继续往前推进。运用递推的方法可以轻松构造出这一题。

### 代码
```
#include<bits/stdc++.h>
#pragma GCC optimize(1)
#pragma GCC optimize(2) 
#pragma G++ optimize(3) 
#pragma GCC optimize("Ofast")
using namespace std;
int t , n , a[2005] , b[2005] , c[2005] , tmp , ctmp;
int main()
{
	ios::sync_with_stdio(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a[i];
		}
		for(int i = n ; i >= 1 ; i--)
		{
			if(a[i] == i)
			{
				b[i] = 0;
				continue;
			}
			for(int j = 1 ; j <= n ; j++)
			{
				if(a[j] == i)
				{
					tmp = j;
				}
			}
			b[i] = tmp;
			ctmp = 1;
			for(int j = tmp + 1 ; j <= i ; j++)
			{
				c[ctmp] = a[j];
				ctmp++;
			}
			for(int j = 1 ; j <= tmp ; j++)
			{
				c[ctmp] = a[j];
				ctmp++;
			}
			for(int j = 1 ; j <= n ; j++)
			{
				a[j] = c[j];
			}
		}
		for(int i = 1 ; i <= n ; i++)
		{
			cout << b[i] << " ";
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：AllenReder (赞：1)

建议看英文题意，中文翻译有点迷惑性。

大概题意就是操作 $n$ 次，第 $i$ 次操作可以选择一个数 $x$，让数列中前 $i$ 个数向右循环移动 $x$ 步。给出最终数列，求每次的 $x$ 选值。

看一眼范围，很小，那直接模拟过程就行，借助 STL 的 Vector 维护整个数列。

第 $i$ 次操作前， $a_{i+1}$ 应该就等于 $i+1$，寻找变化后的位置就是这次操作的 $x$。


```cpp
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
const int N = 1e4 + 10;
const int NN = N << 2;
const int INF = 0x3f3f3f3f;
const long long LINF = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'
#define int long long
typedef pair<int, int> PII;

int n;
int b[N];
int ans[N];

void solve() {
    cin >> n;
    vector<int> v;
    for (int i = 1; i <= n; ++i)
        cin >> b[i], v.push_back(b[i]);
    for (int i = n; i >= 1; --i) {
        int j;
        // 
        for (j = 0; j < v.size(); ++j)
            if (v[j] == i)
                break;
        j++;
        // 核心部分
        ans[i] = j % i;
        // 如果等于 0，说明没有移动
        if (ans[i] == 0)
            continue;
        int t = i - j;
        while (t--) {
       		  // 借助vecotr的相关操作维护数列
            // 类似队列出队再入队的操作，从长度为 i 的区间尾部进行
            int tmp = *(v.end() - n + i - 1);
            v.erase(v.end() - n + i - 1);
            v.insert(v.begin(), tmp);
        }
    }
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " ";
    cout << endl;
}

signed main() {
    // ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
```


---

## 作者：yanhao40340 (赞：1)

~~别的大佬都用什么双端队列……蒟蒻只会用for模拟。（还是太弱了）~~

题意已经翻译的比较清楚了，不清楚可以看题面。

因为每次操作都只是让 $a_1\sim a_i$ 轮换一下，并不影响到第 $i$ 位后面的数字，所以显然可以倒推。

如果第 $i$ 位的数字就是 $i$ ，说明没有移动，也就是说明 $x=0$。

否则数字 $i$ 在第几位，那么 $x$ 就为几。

简要证一下：

设现在数字 $i$ 在第 $y$ 位，那么则有 $(i+x) \bmod i=y$。即 $x \bmod i=y$。又因为 $x<i$ ，所以 $x=y$ 。

代码很好写，码量较小。时间复杂度 $O(n^2)$，可以通过。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=2005;
int a[maxn];
int main(){
	int t,n;scanf("%d",&t);
	while (t--){
		scanf("%d",&n);int ans[maxn]={0};
		for (int i=1;i<=n;++i) scanf("%d",&a[i]);
		for (int i=n;i>=1;--i){
			int pos=find(a+1,a+n+1,i)-a;
			ans[i]=pos;int b[maxn]={0};
			for (int j=1;j<=i;++j) b[j]=a[j];
			for (int j=1;j<=i;++j) a[j]=b[(j+pos-1)%i+1];
		}
		for (int i=1;i<=n;++i) printf("%d ",ans[i]==i?0:ans[i]);
		putchar('\n');
	}
	return 0;
}
```

后记：以后凡是在数组中要查找一个量，可以使用 $\text{algorithm}$ 库中的 $\text{find}$ 函数。

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1650D (luogu)](https://www.luogu.com.cn/problem/CF1650D)

[CF1650D (codeforces)](https://codeforces.com/contest/1650/problem/D)

# 解题思路

我们发现要想让第 $i$ 个数变换一次就需要给第 $i \sim n$ 中的一个位置做一次操作，因此我们很自然的就想到了倒推，容易证明这样是不劣的。

时间复杂度 $O(n^2)$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define forll(i,a,b,c) for(register long long i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(register long long i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
ll t;
/*
就是说，我们倒推回去

发现一定是最优的。

结束。

O(n^2) 
*/
ll n,a[100010];
void f(ll x)//前x位向左循环一次
{
	forl(i,2,x)
		swap(a[i],a[i-1]); 
}
ll ans[100010];
void clear(ll x){
	forl(i,0,x+1)
		ans[i]=0;
}
void solve()
{
	cin>>n;
	clear(n);
	forl(i,1,n)
		cin>>a[i];
	forr(i,n,1)
		while(a[i]!=i)
			f(i),ans[i]++;
	forl(i,1,n)
		cout<<ans[i]<<' ';
	cout<<endl;
}
int main()
{
	IOS;
	t=1;
	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：King_duck (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1650D)

这道题的题意是操作 $n$ 次，第 $i$ 次操作可以选择一个数 $x$，让数列中前 $i$ 个数向右循环移动 $x$ 步。给出最终数列，求每次的 $x$ 选值。先瞅一眼范围，小，那可以直接用 vector 模拟。在第 $i$ 次操作前，$a_{i+1}$ 应该等于 $i+1$，寻找变化后的位置就是这次操作的 $x$。

代码就不上了。（逃）

---

## 作者：XiaoQuQu (赞：0)

# CF1650D Solution

拿到题目，发现是个构造题。有没有什么通用的构造方法？

发现数列长度为 $n$，操作次数也为 $n$。说明平均下来，我们每一次操作都让一个 $a_i=i$。

考虑逆着把操作后的 $a$ 推到原来去，发现若第 $i$ 轮想要使 $a_i=i$，可 $a_j=i$，则第 $i$ 轮应该令 $x=i-j$。

考虑使用一个双端队列存下这个序列，保存 $1\sim i$ 的排列即可。

![image.png](https://s2.loli.net/2022/03/21/PTbBvmVwxKgZ1SG.png)



---

## 作者：tuxuanming2024 (赞：0)

# 题目大意

有一个长度为 $n$ 数组 $a$ 满足 $a_i=i(1 \le i \le n)$。需要进行 $n$ 次操作，第 $i$ 次操作可将 $a_i$ 放到数组最前面若干次，设这个次数为 $s$。现给出一个 $1 \sim n$ 的排列，请求出每轮操作的 $s$。

# 题解

这个题乍一看不好直接做，那么让我们倒着想：其实就是给一个 $1 \sim n$ 的排列按一个特殊的方法排序。好，有思路，让我们分析一下样例：

第 $6$ 轮操作结束后的 $a=[3,2,5,6,1,4]$，第 $5$ 轮操作后 $a=[1,4,3,2,5,6]$。我们发现不管第 $5$ 轮怎样变换，都不会影响到 $a_6$ 的值，$a_6$ 的位置变化都是在第 $6$ 轮进行的。以此类推，$a_i$ 的位置变化都是在第 $i$ 轮开始进行的，这意味着第 $i$ 轮之前 $a_i$ 一直等于 $i$。

因此，我们只需要倒着从 $n \sim 1$，对于每个 $i$ 让当前数组中值等于 $i$ 的那个数交换到最后即可。设在第 $i$ 轮 $a_{pos}=i$，那么当前轮就有 $pos$ 个数被移动到了最前面，即 $s_i=pos$。特别地，当 $pos=i$ 时，$s_i=0$。

此算法时间复杂度为 $O(n^2)$，具体实现如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
int a[2005],b[2005],ans[2005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		memset(ans,0,sizeof(ans)); //注意每组数据要将 ans 清零 
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=n;i>=1;i--)
		{
			memset(b,0,sizeof(b));
			int pos=1;
			while(a[pos]!=i) pos++; //寻找 a[pos]=i 
			if(pos==i) continue; //如果 i 本身就在第 i 个位置，则说明当前轮未进行操作 
			//交换 
			for(int j=pos+1;j<=i;j++) b[++b[0]]=a[j];
			for(int j=1;j<=pos;j++) b[++b[0]]=a[j];
			for(int j=i+1;j<=n;j++) b[++b[0]]=a[j];
			memcpy(a,b,sizeof(b));
			ans[i]+=pos; //记录答案 
		}
		for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：0)

# $\text{CF1650D - Twist the Permutation}$ 题解

## 题目大意

你有一个 $1\sim n$ 的排列 $a$，最开始时 $a_i=i$，你可以对这个排列 $a$ 执行 $n$ 次操作，每次指定一个正整数 $x$ ，第 $i$ 次时将 $a_1\sim a_i$ 中的每个数 $a_j$ 变成 $a_{j+x\bmod i}$。

现在告诉你 $n$ 次操作完成后的排列 $a$，请你还原出每轮选择的 $x$ 的值。

数据范围保证：$n\le2\times 10^3$。

## 思路分析

很聪明的构造题。

考虑倒序计算，以结束时的 $a$ 从第 $n$ 轮开始逆推，有一个非常显然的思路：第 $i$ 轮时让 $a_i=i$。

那么假设第 $i$ 轮前值为 $i$ 的数在第 $j$ 位，那么第 $i$ 轮选择的 $x$ 应该是 $i-j$，然后将 $1\sim i$ 都按顺序移动即可。

所以可以用一个双端队列存 $1\sim i $ 当前的排列，每次重复将队首放到队尾（因为是逆推所以操作方向也是反的）知道队尾元素为 $i$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2049;
int ans[MAXN];
inline void solve() {
	int n;
	scanf("%d",&n);
	deque <int> q;
	memset(ans,0,sizeof(ans));
	for(register int i=1;i<=n;++i) {
		int input;
		scanf("%d",&input);
		q.push_back(input);
	}
	for(register int i=n;i>=1;--i) {
		while(q.back()!=i) {
			q.push_back(q.front());
			q.pop_front();
			++ans[i];
		}
		q.pop_back();
	}
	for(register int i=1;i<=n;++i) printf("%d ",ans[i]);
	putchar('\n');
	return ;
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：happy_dengziyue (赞：0)

### 1 思路

我们不如将这道题变为“若将操作后序列变为原序列该怎么处理”的问题。

很明显，设此时操作 $[1,o]$ 的序列，我们必须将数字 $o$ 往左方向挪到 $o$ 位置上。设它的位置为 $x$，那么就要挪 $x\operatorname{mod}o$ 次。

反推过来即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 2000
int t;
int n;
int a[max_n+2];
int b[max_n+2];
int d[max_n+2];
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1650D_1.in","r",stdin);
	freopen("CF1650D_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		for(int o=n,x;o>=1;--o){
			for(x=o;x>=1&&a[x]!=o;--x);
			d[o]=x%o;
			for(int i=1;i<=o;++i){
				if(i<=x)b[i-x+o]=a[i];
				else b[i-x]=a[i];
			}
			for(int i=1;i<=o;++i)a[i]=b[i];
			//for(int i=1;i<=n;++i)printf("%d ",a[i]);printf("\n");
		}
		for(int i=1;i<=n;++i)printf("%d ",d[i]);
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/71017440)

By **dengziyue**

---

