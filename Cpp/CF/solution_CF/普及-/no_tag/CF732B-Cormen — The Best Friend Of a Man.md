# Cormen — The Best Friend Of a Man

## 题目描述

Recently a dog was bought for Polycarp. The dog's name is Cormen. Now Polycarp has a lot of troubles. For example, Cormen likes going for a walk.

Empirically Polycarp learned that the dog needs at least $ k $ walks for any two consecutive days in order to feel good. For example, if $ k=5 $ and yesterday Polycarp went for a walk with Cormen $ 2 $ times, today he has to go for a walk at least $ 3 $ times.

Polycarp analysed all his affairs over the next $ n $ days and made a sequence of $ n $ integers $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ is the number of times Polycarp will walk with the dog on the $ i $ -th day while doing all his affairs (for example, he has to go to a shop, throw out the trash, etc.).

Help Polycarp determine the minimum number of walks he needs to do additionaly in the next $ n $ days so that Cormen will feel good during all the $ n $ days. You can assume that on the day before the first day and on the day after the $ n $ -th day Polycarp will go for a walk with Cormen exactly $ k $ times.

Write a program that will find the minumum number of additional walks and the appropriate schedule — the sequence of integers $ b_{1},b_{2},...,b_{n} $ ( $ b_{i}>=a_{i} $ ), where $ b_{i} $ means the total number of walks with the dog on the $ i $ -th day.

## 样例 #1

### 输入

```
3 5
2 0 1
```

### 输出

```
4
2 3 2
```

## 样例 #2

### 输入

```
3 1
0 0 0
```

### 输出

```
1
0 1 0
```

## 样例 #3

### 输入

```
4 6
2 4 3 5
```

### 输出

```
0
2 4 3 5
```

# 题解

## 作者：Da_un (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF732B)

题目大意是有一个序列，让你在这个序列上的某些数上增加它的数值使得这个序列中的任意两个相邻的数的和均不小于 $k$。

## 思路
贪心思想。

我们不难想到如果这个数的左右两边均有数，那么最优策略一定是在它身上增加数值使得两边均不小于 $k$，这样所增加的数值也是最小的。

于是，我们对代码整体也有了一定把握，对于队首，我们增加第二个数使他们不小于 $k$，对于队尾，我们增加倒数第二个数使他们不小于 $k$，对于其余的数均是对自身进行改动。

随时累加增加数值，更改序列中的元素，最后输出即可。

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define MAXN 600
using namespace std;
int n,k;
int f[MAXN],ans;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&f[i]);
	for(int i=2;i<=n;i++){//取i与i-1,于是从2开始 
		if(f[i]+f[i-1]<k){//此时需要更改数值 
			int t=k-f[i-1];//t是f[i]要到的最小数值 
			ans+=(t-f[i]);//累加增加的数值 
			f[i]+=(t-f[i]);//更改f[i]使之达到符合条件的最小值 
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
		printf("%d ",f[i]);
	//输出 
	return 0;
	//完结撒花~~ 
} 

```
### [AC记录](https://www.luogu.com.cn/record/60217445)

---

## 作者：yxy666 (赞：1)

嘿嘿，美味的估值。。。

思路：妥妥的贪心啊。如果这两个数的加和要小于 $k$ ,那就将后面这个数加一点，刚好满足两个数的加和等于 $k$ 。然后继续做。因为是贪心的想法吗，后面这个数在接下来还会再用上一次，所以当然加给后面的数啊。前面的数用完就丢一边了。

$code$ ：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans,a[505];
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
    return ret*f;
}//快读
int main(){
    n=read();k=read();
    for(int i=1;i<=n;i++)a[i]=read();//输入
    for(int i=2;i<=n;i++){//因为第一个数前面没有数，所以从第二个开始找
        if(a[i]+a[i-1]<k){
            ans+=k-a[i]-a[i-1];a[i]+=k-a[i]-a[i-1];
        }//如果加和不够，贪心的想法，加给后面的数。答案累加
    }
    printf("%d\n",ans); 
    for(int i=1;i<=n;i++)printf("%d ",a[i]);//输出
    return 0;
}
```


---

## 作者：Yh0326 (赞：0)

~~我怎么觉得应该评红啊~~

读完题面，我们很快就能想到正解：贪心！

枚举 $i$ ，看看两数之和是否超过 $k$ ，若没有，就在靠后的那个数上加上与 $k$ 的差，可以发现这样是最优的。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a[502];
long long ans=0;
int main(){
    cin>>n>>k>>a[1];
    for(int i=2;i<=n;++i){
        scanf("%d",a+i);
        int x=max(0-(a[i-1]+a[i]-k),0);
        ans+=x;
        a[i]+=x;
    }
    cout<<ans<<'\n';
    for(int i=1;i<=n;++i) cout<<a[i]<<' ';
    return 0;
}
```
完结END。。。

---

## 作者：封禁用户 (赞：0)

### [传送门](https://www.luogu.com.cn/problem/CF732B)

~~本题其实比较水~~

这题数据很小，可以考虑暴力。

当 $a[i]$ $+$ $a[i-1]$ $<$ $k$ 时，因为贪心，我们要将 $a[i]$ 使劲加。

当然，只要加到 $a[i]$ $+$ $a[i-1]$ $\ge$ $k$ 即可。

具体细节见代码。

###   AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,i,s,a[510];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(i=1;i<=n;i++)cin>>a[i];
	for(i=2;i<=n;i++)        //for从2开始，一直到n 
		if(a[i]+a[i-1]<k){   //如果不符合条件 
			while(a[i]+a[i-1]<k)a[i]++,s++;
			//while循环一直加到符合条件为止 
		}
	cout<<s<<"\n"<<a[1];
	for(i=2;i<=n;i++)cout<<" "<<a[i];	//输出 
	return 0;//！！！完结撒花！！！
}


```

---

## 作者：ttq012 (赞：0)

**题意**

我们需要满足以下的条件：在任意两天的遛狗次数的和大于 $k$。

输出在给定的遛狗的情况之下额外遛狗的次数。

**题解**

动态规划和贪心的融合。

对于任意的 $b_i(i\ge 1)$，如果 $b_{i - 1} + b_i < k$，那么我们就需要额外增加一些遛狗的次数。

我们在这里需要使用贪心的思想，我们是按照顺序枚举的，在枚举到 $b_i$ 的时候，$b_{i - 2} + b_{i - 1}, b_{i - 3} + b_{i - 2}, \cdots, b_2 + b_1$ 肯定都是 $\ge k$ 的。

因此，$b_{i - 1}$ 的修改只对 $b_i$ 有效，而 $b_i$ 的修改同时对 $b_{i - 1}$ 和 $b_{i + 1}$ 有效，所以我们将 $b_i$ 改为 $\max(a_i, k - a_{i - 1})$ 即可。

**代码**

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10;

int a[N], b[N];

signed main() {
    int n, k;
    cin >> n >> k;
    long long ans = 0;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1; i <= n; i ++) b[i] = a[i];
    for (int i = 2; i <= n; i ++) {
        b[i] = max(b[i], k - b[i - 1]);
        ans += (b[i] - a[i]);
    } cout << ans << '\n';
    for (int i = 1; i <= n; i ++) cout << b[i] << ' ';
    cout << '\n';
    return 0;
}

```



---

## 作者：_Scaley (赞：0)

一道贪心题

# 思路：

首先我们可以知道，要想让相邻两个数的和不小于 `k`，而又要求增加数值之和最小，

那么最优的方案当然是是每相邻两个数的和正好等于 `k` 。

做到这一点的最简单的方法当然是贪心了。

我们可以把两个数的和加起来，然后与 `k` 比较：

* 如果比 `k` 小，那么在两个数中的第二个数加上和与 `k` 的差。

* 如果比 `k` 大，那么就不做任何改变。

可以用 `ans` 来记录需要增加数值之和，用 `d` 来记录两个数之和与 `k` 的差。

## 贪心思路解释：

#### 考虑当前情况：

两个数的和必须要大于等于 `k` ，增加数值之和要最小；

最优的方案是相邻两个数恰好等于 `k` 。

在为两数加和时，加上的数为两个数之和与 `k` 的差，

* 如果为第一个数加和，那么这个数的值改变后不对下一对数的和有任何改变（无贡献）。

* 如果为第二个数加和，那么这个数将作为下一对数的第一个数（有贡献）。

显然，为第二个数加和可以使下一对数增加的数值更小，

故为第二个数加和最优。

# 几点注意：

1. 如果 `d` 为负数，说明两个数的和已经超过了 `k`，此时不需要再讲这个负数加入 `ans` 。

2. 如果 `d` 为负数，那这两个数的值就不必改变，不要把这个负值加到第二个数中。

## 代码：

```
#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN 501
#define F1(i, a, b) for (int i = a; i <= b; ++i) // 懒人必备。
#define F2(i, a, b) for (int i = a; i >= b; --i)
using namespace std;

int f[MAXN]; // f 数组用来存数列的各个数。

int main() {
	int n, k, d, ans = 0;
	scanf("%d %d", &n, &k);
	F1(i, 1, n) scanf("%d", &f[i]);
	F1(i, 2, n) { // 因为从第二个数加起（第一对数的第二个数），所以从 2 开始循环。
		d = k - f[i - 1] - f[i];
		if (d >= 0) ans += d; // 注意第一条。
		if (d >= 0) f[i] += d; // 注意第二条。
	}
	printf("%d\n", ans);
	F1(i, 1, n) printf("%d ", f[i]);
	return 0;
}
```

---

## 作者：ModestCoder_ (赞：0)

非常简单的一个贪心

让$m$减去上一个值，如果大于自己就改变

Code：

```cpp
#include <bits/stdc++.h>
#define maxn 1010
using namespace std;
int n, m, a[maxn], ans;

inline int read(){
	int s = 0, w = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') w = -1;
	for (; isdigit(c); c = getchar()) s = (s << 1) + (s << 3) + (c ^ 48);
	return s * w;
}

int main(){
	n = read(), m = read();
	a[1] = read(); 
	for (int i = 2; i <= n; ++i){
		a[i] = read();
		int x = m - a[i - 1];
		if (x > a[i]) ans += x - a[i], a[i] = x;
	}
	printf("%d\n", ans);
	for (int i = 1; i <= n; ++i) printf("%d ", a[i]);
	return 0;
}
```


---

## 作者：Erina (赞：0)

**核心思想：贪心**

对于每一个b[i]和b[i-1],如果数量不足k,那么肯定要增加b[i]

 因为b[i]对b[i-1],b[i+1]都生效
 
 所以增加b[i]=max(b[i],0,k-b[i-1]);
 
 附上代码：
 
 ```cpp
#include<iostream>
using namespace std;
int n,k;
int num[505];
int walk;
int ans;
int main(){
	cin>>n>>k;
	cin>>num[0];
	for(int i=1;i<n;i++){
		cin>>num[i];
		walk=num[i];
		num[i]=max(num[i],max(k-num[i-1],0));
		ans-=walk-num[i];
	}
	cout<<ans<<endl;
	for(int i=0;i<n;i++){
		cout<<num[i]<<' ';
	}
}
 ```

---

## 作者：梦游的小雪球 (赞：0)

### 梦雪的思路：
- 如果这个数和前一个数的和**小于k**，就把这个数变成**k-前一个数。** **（注意：第一个数不用进行此操作）**
## 实现代码：
#### 若思路不清楚请见注释
```
#include<bits/stdc++.h>
using namespace std;
int n,k,c[502],s;//c为序列,s统计增加数值
int main(){
	cin>>n>>k;
	for(int i=1;i<=a;i++){
		cin>>c[i];//输入
		if(i>1)//第一个数不进行此操作
			if(c[i]<k-c[i-1]){	//即如果这个数+前一个数<k
				s=s+k-c[i-1]-c[i];//s加上增加的量
				c[i]=k-c[i-1];//把这个数变成k-前一个数
			}
	}
	cout<<s<<endl<<c[1];
	for(int i=2;i<=n;i++)
		cout<<" "<<c[i];//输出
	return 0;
}
```
望通过

---

