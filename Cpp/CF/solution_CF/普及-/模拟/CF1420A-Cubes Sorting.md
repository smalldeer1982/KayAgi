# Cubes Sorting

## 题目描述

For god's sake, you're boxes with legs! It is literally your only purpose! Walking onto buttons! How can you not do the one thing you were designed for?Oh, that's funny, is it? Oh it's funny? Because we've been at this for twelve hours and you haven't solved it either, so I don't know why you're laughing. You've got one hour! Solve it!





Wheatley decided to try to make a test chamber. He made a nice test chamber, but there was only one detail absent — cubes.

For completing the chamber Wheatley needs $ n $ cubes. $ i $ -th cube has a volume $ a_i $ .

Wheatley has to place cubes in such a way that they would be sorted in a non-decreasing order by their volume. Formally, for each $ i>1 $ , $ a_{i-1} \le a_i $ must hold.

To achieve his goal, Wheatley can exchange two neighbouring cubes. It means that for any $ i>1 $ you can exchange cubes on positions $ i-1 $ and $ i $ .

But there is a problem: Wheatley is very impatient. If Wheatley needs more than $ \frac{n \cdot (n-1)}{2}-1 $ exchange operations, he won't do this boring work.

Wheatly wants to know: can cubes be sorted under this conditions?

## 说明/提示

In the first test case it is possible to sort all the cubes in $ 7 $ exchanges.

In the second test case the cubes are already sorted.

In the third test case we can make $ 0 $ exchanges, but the cubes are not sorted yet, so the answer is "NO".

## 样例 #1

### 输入

```
3
5
5 3 2 1 4
6
2 2 2 2 2 2
2
2 1```

### 输出

```
YES
YES
NO```

# 题解

## 作者：yzh_Error404 (赞：5)

看到此题，最开始想的是树状数组

好像就是普通的逆序对啊

但这个$\frac{n*(n-1)}{2}-1$一看就不简单

手推发现，$\frac{n*(n-1)}{2}$就是一个单调递减的数列变为单调递增的次数

所以只要这个序列不是单调递减，都可以完成排序

上代码
```cpp
#include<bits/stdc++.h>
#define N 50005
using namespace std;
int n,t;
int a[N];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		bool flag=false;
		scanf("%d",&n);
		for(register int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(register int i=2;i<=n;i++)
			if(a[i]>=a[i-1])flag=true;//判断是否为单调递减
		if(flag==false)printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```

---

## 作者：STDquantum (赞：3)

发现这个序列变成不降的序列所需要的次数就是逆序对（$i\lt j$ 且 $a_i>a_j$）数，因为每次操作都会减少一个逆序对。

于是我们想出了第一种AC做法：树状数组求逆序对。

先把 $a$ 数组离散化（最大值设为 $top$），然后开一个权值树状数组。

每次加入 $a_i$ 前，查询 $[a_i+1,top]$ 内有多少数字，也就是比 $a_i$ 早还比它大，把个数统计入答案。

这样下来，就可以得到序列的逆序对数，和 $\displaystyle \frac{n\cdot (n-1)}2-1$ 比较一下输出答案就好。

代码：

```cpp
typedef long long ll;
const int N = 1e5 + 10;

int top, T[N];
inline void add(int x, int w) {
  for (; x <= top; x += x & -x) { T[x] += w; }
}
inline int query(int x) {
  int tmp = 0;
  for (; x; x -= x & -x) { tmp += T[x]; }
  return tmp;
}

int t, n, a[N], b[N];
ll ans;
inline void main() {
  for (read(t); t--;) {
    read(n), ans = 0;
    for (int i = 1; i <= n; ++i) { read(a[i]), b[i] = a[i]; }
    sort(b + 1, b + n + 1);
    top = unique(b + 1, b + n + 1) - b - 1;
    memset(T, 0, sizeof(T));
    for (int i = 1; i <= n; ++i) {
      a[i] = lower_bound(b + 1, b + top + 1, a[i]) - b;
      ans += query(top) - query(a[i]); // r处前缀和减去l-1处前缀和
      add(a[i], 1);
    }
    if (ans > (ll)n * (n - 1) / 2 - 1) {
      puts("NO");
    } else {
      puts("YES");
    }
  }
}
```

这就能 AC 了。

---

第二种 AC 解法。

不过要是熟悉 $\displaystyle \frac{n\cdot (n-1)}2$ 这个数就会发现这个数就是 $\left(\begin{array}{c} n\\2\end{array}\right)$。

这意义不就是说，从 $n$ 中任选两个都是逆序对吗？而逆序对数为 $\left(\begin{array}{c} n\\2\end{array}\right)$ 的序列只可能是单调递减的序列。

所以根本没有上面那么麻烦，只要序列不是单调递减，都是`YES`。

连数组也不用开hhhhh。

代码：

```cpp
int t, n, las;
inline void main() {
  for (read(t); t--;) {
    read(n), las = 0x3f3f3f3f;
    for (int i = 1, a; i <= n; ++i) {
      read(a);
      if (a >= las) { // 要是不是单调递减
        puts("YES"); // YES就好了
        while (n - i) read(a), ++i; // 记得把剩下的a读完
        goto school; // 省去bool变量判断
      }
      las = a;
    }
    puts("NO");
  school:;
  }
}
```

# 

---

## 作者：Meaninglessness (赞：2)

## A. Cubes Sorting

**题目大意:**

> 给你一个数列 $a$,如果$a_i > a_j$ 且 $i<j$,那么就交换 $a_i,a_j$,如果交换的次数大于 $\frac{n(n-1)}{2}-1$,输出NO,否则输出YES。

***

**解题思路:**

看到交换次数,想到了逆序对个数。那么我们就将问题转换为了**求逆序对个数。**

我们发现,长度为 $n$ 的序列有 $\frac{n(n-1)}{2}$ 对数,所以如果有$1$个不是逆序对,那么就肯定可以满足要求。如果 $a$ 数组是严格降序序列,那么不能满足要求。

***

**代码实现:[Code](https://www.luogu.com.cn/paste/yrjjrilz)　复杂度$O(Tn)$**

---

## 作者：Sktic (赞：1)

## Problem
给你一个长度为 $n$ 的数列，每次只能交换相邻的两个数，如果你能在 $\frac{n(n-1)}{2}-1$ 的次数下排序完这个数列，则输出“YES”，否则输出“NO”。
## Solution
看到这题，我们马上想到了一个有好的排序：冒泡排序。可以知道，冒泡排序如果发现大小不对，则会交换位置，如果一个序列最差情况（单调递减），则共会交换    $\frac{n(n-1)}{2}$ 次，刚好超出题目要求 $1$ 次，所以只有当序列单调递减是输出“NO”，其他则为“YES”。
## Code
```C++
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
int a[maxn];
int main()
{
	int n,t;
	cin>>t;
	while(t--)
	{
		int f=1;
		cin>>n;
		for(register int i=1;i<=n;i++)
			cin>>a[i];
		for(register int i=2;i<=n;i++)
			if(a[i]>=a[i-1])
				f=0;
		if(f==0)
			cout<<"YES\n";
		else
			cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：hmya (赞：1)

看到这道题目，心里想到了奇奇怪怪的算法

但是呢，看看：Div.2第一题怕个啥子玩意？

只要能在那个次数之内，就是YES！

那么，什么排列不会在那个次数之内呢？

首先考虑极端情况

先看降序排列：

最后一个数-->第一需要n-1次

倒数第二个数-->第二需要n-2次

………………

第一个数移到最后只需要1次！

那么，只需要求一个等差数列：

n*（n-1）/2

与答案限制 n*（n-1）/2 只有一次的差距！

那么，也就是说：只要**不是单调递减**的，就是输出YES，否则就是输出NO

就这样，代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int main(){
	scanf("%d",&t);
	for(int i=1;i<=t;i++){//t组数据
		int n;
		bool flag=false;//是不是单调递减的
		scanf("%d",&n);
		int a[n+1];//定义数组
		for(int j=1;j<=n;j++){
			scanf("%d",&a[j]);
		}
		for(int j=2;j<=n;j++){
			if(a[j]>=a[j-1]){//这样就一定不是单调递减的，输出YES
				printf("YES\n");
				flag=true;
				break;
			}
		}
		if(flag==false){//如果途中都没有进判断，就输出NO
			printf("NO\n");
		}
	}
	return 0;//END
}
```

这题为什么能够用这么简单的方法呢？

因为他只需要YES和NO，不需要过程

如果需要过程的话，大概率会出现在Div.2的C部分了

题解就到这里了，喜欢就点个赞吧

看不懂的可以私信作者

---

## 作者：king_xbz (赞：1)

看到还没有题解，那我就来发一下吧。

有两种思路，一种暴力，一种算是推性质的正解，两种方法都可以过。

# 先来看暴力
我们可以从题意得知，我们要统计的就是冒泡排序中交换相邻元素的操作。但是用冒泡排序硬搞肯定不彳亍，然而，有一个很重要的性质：排序中相邻元素的交换次数=序列中逆序对的数量。那么我们直接用归并排序求个逆序对不就完了！

时间复杂度$O(NlogN)$
```cpp
signed main()
{
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		cin>>a[i];
		memset(c,0,sizeof(c));
		t=0;
		msort(1,n);
		if(t<=(n-1)*n/2-1)
		puts("YES");
		else
		puts("NO");
	}
	return 0;
} 
inline void msort(int x,int y)
{
	if(x==y)
	return ;
	int mid=(x+y)/2;
	int i=x;
	int j=mid+1;
	int k=x;
	msort(x,mid);
	msort(mid+1,y);
	while(i<=mid&&j<=y)
	if(a[i]<=a[j])
	c[k++]=a[i++];
	else
	{
		c[k++]=a[j++];
		t+=(mid-i+1);
	}
	while(i<=mid)
	c[k++]=a[i++];
	while(j<=y)
	c[k++]=a[j++];
	for(int i=x;i<=y;i++)
	a[i]=c[i];
	return ;
}
```
# 再来看正解
我们来手模一下冒泡排序的过程，最坏情况下每次将最左侧元素移位到最右侧，这样下来的交换次数为$\frac {N*(N-1)}2$,而我们在这里最多能接受的交换次数是多少？
$\frac {N*(N-1)}2-1$！也就是说，只要不是最坏情况都可以`puts("YES");`而最坏情况显然是数列为严格递减情况(如果不严格递减，总会有不交换的时候)。

那么只要判断数列中是否有相等或递增元素即可。

代码：
```cpp
int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	lb:
	while(T--)
	{
		int n;
		cin>>n;
		for(fint i=1;i<=n;i++)
		cin>>a[i];
		for(fint i=2;i<=n;i++)
		if(a[i]>=a[i-1])
		{
			puts("YES");
			goto lb;
		}
		puts("NO");
	}
	return 0;
}
```

如果各位神犇有别的方法也可以在下面交流，祝大家AC愉快！

---

## 作者：过往梦魇之殇 (赞：0)

### [CF1420A Cubes Sorting](https://www.luogu.com.cn/problem/CF1420A)

**思路简述：**

首先我们知道，从$n$个数里面选出两个凑成一对共有$\dfrac{n\times (n-1)}{2}$种选法，也可以理解为长度为$n$的序列中逆序对的个数大于等于$0$个、小于等于$C^2_n$个。

下限$0$当且仅当该序列单调不下降时取到，上限$C^2_n$当且仅当该序列严格单调递减时取到。

由题：
```
每次你可以交换相邻的两个数，如果你可以在 n*(n-1)/2−1 次内使得数列有序(单调不减)，输出 YES,否则输出 NO。
```
可知只要序列不是严格的单调递减，都输出 $YES.$

~~就酱。~~

**代码展示：**

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
const int maxn=5e4+10;
int t,n,a[maxn];
int main(){
    scanf("%d",&t);
    while(t--){
        bool flag=false;
        scanf("%d",&n);  
        for(re int i=1;i<=n;++i){  
            scanf("%d",&a[i]);     
            if(i>1){
                if(a[i]>=a[i-1]){
                    flag=true;
                }
            }
        }
        if(flag){
            puts("YES");
        }
        else{
            puts("NO");
        }
    }     
    return 0;
}
```
> $Thanks$ $For$ $Watching!$

---

## 作者：_jimmywang_ (赞：0)

众所周知我们亲爱的冒泡排序，最坏情况下要交换$\dfrac{n(n-1)}{2}$

而最坏情况就是每对数都得换。

没错，这个时候序列**严格递减**

而题目中说小于$\dfrac{n(n-1)}{2}-1$的为`YES`,要不然就是`NO`

所以**严格递减**的序列输出`NO`，其他的都是`YES`

$code:$

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll r() {
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d r()
ll t;
ll n;
int main(){
	t=d;
	while(t--){
		n=d;
		ll x=d;
		bool fl=0;
		f(i,2,n){
			ll y=d;
			if(y>=x)fl=1;
			x=y;
		}
		if(fl)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：引领天下 (赞：0)

显然当且仅当原序列为**严格**递减时答案为 `NO` 。

证明：

当原序列为严格递减时，$a_n$ 需要调整至 $1$，耗费 $n-1$ 次操作；随后 $a_{n-1}$ 需要调整至 $2$，耗费 $n-2$ 次操作……总共需耗费 $\frac{n\times (n-1)}{2}$ 次操作。

其他情况下必然存在某个 $a_i$ 比上述情况中调整 $a_i$ 所需的操作数量少，故必然满足。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[50005];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        bool ans=1;a[0]=1<<30;
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),ans&=a[i]<a[i-1];
        puts(ans?"NO":"YES");
    }
    return 0;
}
```

---

## 作者：SuperTNT (赞：0)

我们第一眼看会感觉是要求逆序对，这么做也行，但我们发现这道题给的限制$n(n - 1)/2-1$只卡了单调下降序列,因此除了单调下降序列以外其他均是$Yes$,我们只要在输入的时候判断一下是否是单调下降序列即可
```c++
#include<bits/stdc++.h>

#define re register

namespace TNT
{
    const int MAXN = 5e4 + 10;

    inline int read()
    {
        int x = 0;
        char ch = getchar();
        while(ch < '0' || ch > '9')
            ch = getchar();
        while (ch >= '0' && ch <= '9')
        {
            x = x * 10 + ch - '0';
            ch  =getchar();
        }
        return x;
    }

    inline void main()
    {
        int t = read();
        while(t--)
        {
            int n = read();
            int m = read();
            int flag = 0;
            for(re int i = 2; i <= n;i++)
            {
                int x = read();
                if(m <= x)   
                    flag = 1;
                m = x; 
            }
            if(!flag)
                puts("No");
            else
                puts("Yes");
        }
        return;
    }
}

int main()
{
    TNT::main();
    return 0;
}
```

---

## 作者：—维尼— (赞：0)

~~吐槽：刚看到这题几分钟就想到了正解，然后发现这次cf没报名，悲痛万分之后来给大家发题解~~
## 题目大意
给定n个立方体的体积，问是否可以通过最多$\frac{n*(n-1)}{2}-1$次操作，（每次操作可以交换两个相邻的数）将数列按从小到大排序（非严格大于）
## 题目思路：
一看就知道是个找规律题，我们可以从最坏的例子入手，看看与题目描述的操作次数有没有规律

假设有这样一种最坏情况
```c++
5 4 3 2 1
```
可以手写一个冒泡来计算操作次数（也可以自己口胡


查询排序次数的冒泡代码：
```cpp
int main(){
	int a[1005];
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
    	cin>>a[i];
	}
	for(int i=1;i<=n-1;i++){
    for(int j=1;j<=n-i;j++){
        if(a[j]>a[j+1]){
            int x=a[j];
        	a[j]=a[j+1];
        	a[j+1]=x;
        	ans++;
			}	
    	}
	}
	cout<<ans;
}
```


不管口胡还是写程序，我们都可以得出给这种排列排序需要$10$次交换，刚好比规定的（$\frac {5*(5-1)}{2}-1$）多$1$

而次劣情况
```c++
5 4 3 1 2
```
就已经是在范围内的了（9次）

所以

**只要不是最劣情况都可以在要求范围内排序成功**

ps:你也可以自己多试几次来确认这个规律



所以这题就能很简单的做出来了

## 简单的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500004];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int x=false;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		if(n<=2&&a[2]<a[1]){//这里我确保没问题特判了一下n小的情况，不要应该也行
			cout<<"NO"<<endl;
			continue;
		}
		for(int i=2;i<=n;i++){
			if(a[i]>=a[i-1]){
				x=true;
			}
		}
		if(x)
		cout<<"YES"<<endl;
		else
		cout<<"NO"<<endl;
	}
	
} 
```



---

## 作者：nztyz (赞：0)

#### 题意:
给一个n个数的数列,相邻之间数可交换,并且最多可交换$n*(n-1)/2-1$次,若在有效次数内可以交换为非递减序列,则输出$YES$,否则输出$NO$
####
熟悉冒泡排序的可以发现在最坏的情况下n个数需要交换$n*(n-1)$次,所以只需判断是不是最坏情况,如果不是,则交换次数必在有效次数之内
```c
#include <bits/stdc++.h>
using namespace std;
int t,n,a[50005],ans;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		ans = 0;
		for(int i = 1 ; i <= n ; i++){
			cin>>a[i];
		}
		bool vis = true;
		for(int i = 2 ; i <= n ; i++){
			if(a[i-1] > a[i]) continue;
			else{
				vis = false;
				break;
			}
		}
		if(vis==false) cout<<"YES"<<endl;
		else
		cout<<"NO"<<endl;
	}
	return 0;
}
```

---

## 作者：忘怀星 (赞：0)

A题给我们一个数列，每次可以交换相邻元素的位置，问我们能不能在 $\frac{n(n-1)}{2}-1$ 次操作内将元素调整为不下降序列。

刚一看到这道题的时候表示十分蒙，但是看到了 $\frac{n(n-1)}{2}$ 这个熟悉的式子，想到一个序列的最多逆序对数量也就是 $\frac{n(n-1)}{2}$ 且仅当序列为严格递减的时候成立，那么我们只需要检查所给序列是否为严格递减序列即可

---

