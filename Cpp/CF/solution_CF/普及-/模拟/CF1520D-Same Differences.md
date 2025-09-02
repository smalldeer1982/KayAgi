# Same Differences

## 题目描述

You are given an array $ a $ of $ n $ integers. Count the number of pairs of indices $ (i, j) $ such that $ i < j $ and $ a_j - a_i = j - i $ .

## 样例 #1

### 输入

```
4
6
3 5 1 4 6 6
3
1 2 3
4
1 3 3 4
6
1 6 3 4 5 6```

### 输出

```
1
3
3
10```

# 题解

## 作者：oimaster (赞：5)

我们拿到 $a_j-a_i=j-i$ 后，可以进行整理。

1. $a_j-a_i=j-i$
2. $a_j=j-i+a_i$
3. $a_j-j=a_i-i$

接下来，我们发现只需要计算这个数和下标的差就可以知道匹配个数了。

那么只需要开桶统计即可。这时候我们会发现 $a_i$ 可能会小于 $i$，所以减出来的可能会是负数。那么我们的传统数组就无法解决这个问题。

那么把凶狠的眼光放在 STL 上，发现 map 可以帮我们解决这个问题。map 的单次修改是 $\log n$ 级别的，也很优秀。

那么一共做 $n$ 次操作，每次是 $\log n$，复杂度为 $\text{O}(n\log n)$。

```cpp
#include<iostream>
#include<map>
#define int long long
using namespace std;
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[n+1];
		for(int i=1;i<=n;++i){
			cin>>a[i];
			a[i]-=i;
		}
		int ans=0;
		map<int,int>m;
		for(int i=1;i<=n;++i){
			if(m.count(a[i]))
				ans+=m[a[i]];
			++m[a[i]];
		}
		cout<<ans<<endl;
	}
}
```

---

> 数组：为什么我不行？![kk](https://cdn.luogu.com.cn/upload/pic/62227.png)

> 博主：谁说的！

我们注意到，所有减去的下标最多是 $n$，那么我们只需要把所有的差值统一加上 $n$ 不就进入正数范围了？

不过这时候，因为如果没有减出负数，加完 $n$ 后大小可能会达到 $2n$。

那么我们开 $2n$ 大小的数组，不就可以了？

```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
signed main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[n+1];
		for(int i=1;i<=n;++i){
			cin>>a[i];
			a[i]-=i;
		}
		int ans=0;
		int m[2*n+1];
		fill(m,m+2*n+1,0);
		for(int i=1;i<=n;++i){
			ans+=m[a[i]+n];
			++m[a[i]+n];
		}
		cout<<ans<<endl;
	}
}
```

因为查询数组是 $\text{O}(1)$，时间复杂度就为 $\text{O}(n)$。

这就是不会 STL 的同学可以走的取巧路线。题解就这么多了。

---

## 作者：Eason_AC (赞：3)

## Content
给定 $n$ 个数 $a_1,a_2,\dots,a_n$，求有多少个二元组 $(i,j)$ 满足：

- $i<j$。
- $a_j-a_i=j-i$。

**数据范围：$t$ 组数据，$1\leqslant a_i\leqslant n,\sum n\leqslant 2\times 10^5$，$1\leqslant t\leqslant 10^4$。**
## Solution
很简单的一道题目。

我们将题目中的这个等式稍微移项一下就可以得到 $a_i-i=a_j-j$。然后这个题目就可以转化了。我们只需要边输入当前的 $a_i$，边加上 $a_i-i$ 在前面 $i-1$ 个数当中出现的次数，更新 $a_i-i$ 出现的次数即可得到答案。计数器可以用 map 实现。
## Code
```cpp
int a[200007];

int main() {
	MT {
		map<int, int> vis;
		int n = Rint; ll ans = 0;
		F(int, i, 1, n) a[i] = Rint, ans += vis[a[i] - i], vis[a[i] - i]++;
		println(ans);
	}
    return 0;
}
``` 

---

## 作者：LinkZelda (赞：1)

- **题意**：给定一个长度为 $n$ 的序列 $a$，统计数对 $(i,j)$ 个数满足 $a_j-a_i=j-i$。

- $Solution$:

考虑将条件移项变为 $a_j-j=a_i-i$。那么问题转化为对于每个位置 $i$，求 $i<j$ 且 $a_j-j=a_i-i$ 的个数。我们发现值域很小，于是可以对每一个值开一个桶来维护出现次数，按顺序扫描即可，扫描到一个数就算答案，然后这个数的个数 $+1$。

值得一提的是 $a_i-i$ 可能为负数，那我们应该开 `map` 来作为桶，这样的时间复杂度是 $\mathit{O}(n\log n)$ 的。还有一种做法是对于每一个值加上一个偏移量，这个偏移量设为 $n$ 即可，因为 $a_i>0$ 那么有 $a_i-i>-n$，这样做的时间复杂度是 $\mathit{O}(n)$ 的。

- [代码](https://www.luogu.com.cn/paste/cdzbjvwh) $(\ \mathit{O}(n)\ )$

---

## 作者：wheneveright (赞：1)

## 题意

给出 $T$ 组序列 $a$，长度为 $N$，询问有多少对 $(i,j)$ 满足 $i < j$ 且 $a_j - a_i = j - i$。

## 分析

这个题目很经典，入门好题！

当满足 $a_j - a_i = j - i$ 时，令 $x = j - i$ 则 $a_i = a_j - x \to a_i = a_j - j + i \to a_i - i = a_j - j$，发现如果可以把 $a_i - i$ 预处理出来，然后再看有多少相同的数字，统计对数就好了。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

int T, N, A[200005];
long long ans;

int main () {
	scanf ("%d", &T);
	while (T--) {
		scanf ("%d", &N); ans = 0;
		for (int i = 1; i <= N; i++) {
			scanf ("%d", &A[i]);
			A[i] -= i; // 预处理
		}	sort (A + 1, A + 1 + N); A[N + 1] = 2147483640;
		// 排序后就可以让相同的靠在一起
		// 这里有个小细节就是将 A[N + 1] 赋值，因为这样后面的那个 if 就不会出锅了
		for (int i = 1; i <= N; i++) {
			int j; long long now; // j 满足与 i 相同
			for (j = i + 1; j <= N; j++) if (A[j] != A[i]) break;
			if (A[j] != A[i]) j--; now = j - i + 1; // now 就是长度
			ans += (now * (now - 1)) / 2; // 统计数字，now 记得开 long long
			i = j;
		}
		printf ("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：network_master (赞：0)

### **思路分析**

这道题也是非常的简单

首先我们看到了 $a_j-a_i=j-i$

我们可以将这个式子变形,化为 $a_j-j=a_i-i$

到了这一步，做法就很显然了,我们可以在输入的时候预处理一下 $a_i=a_i-i$,

然后排序一下,整个桶,按顺序扫描连续的段 (数字)

扫描后统计扫描出连续段的项数，然后统计答案

### 小坑点

由于 $a_i-i$ 可能是负数,这个时候你用数组就光荣 RE 了,

~~这个时候我果断去写指针~~

指针那玩意这么麻烦，本菜鸟可不会用

这里我们可以用 C++ 自带的 STL map ,这样就方便多了。

不知道的小伙伴可以去百度一下

好，废话不说，直接贴代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans,n; //答案和n
#define int long long
//懒人专用
int a[200001]; // 英语题目中有说
map<int,int> mp;//mp数组表示减完后等于a[i]-i的a[j]-j
main() // 我是懒人，见笑了
{
  int t; //数据组数
  cin>>t;
  while(t--)
  {
    scanf("%lld",&n);
    for(int i=1; i<=n; i++)
    {
      scanf("%lld",&a[i]);
      a[i] = a[i]-i;
      //进行预处理,计算出序列-i的值
    }
    ans = 0;
    mp.clear();
    //21~22 为初始化
    for (int i=1; i<=n; i++)
    {
      if(mp.count(a[i])!=0) // 如果找到的这个次数不是0，代表找到了
      {
        ans +=mp[a[i]];
      }
      mp[a[i]]++;
      //代表a[i]-i（现a[i]）这个值的次数，每次做完记得加1
    }
    printf("%lld\n",ans);
  }
  return 0;
}
```


------------
**本代码在 Codeforces 原站以 AC**

~~笑死竟然不用快读~~

---

## 作者：tribool4_in (赞：0)

有一定思维的题。

首先看到式子 $a_j-a_i=j-i$，对其进行变形，将含 $i$ 的项挪到等式一边：$a_i-i=a_j-j$。

因此，做法显然，记 $x=a_i-i$，在输入的同时记录每个 $x$ 的出现次数，对于当前 $x$ 只需查询在此之前 $x$ 的出现次数并累加到答案上，并将 $x$ 的出现次数 +1。

具体实现则可以用 `map`（类似一个数组，可以存 `int` 范围的数）。

另外要注意 `long long` 和清空 `map`。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
inline int read() {
	int s = 0; char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) s = s * 10 + c - '0', c = getchar();
	return s;
}
int T, n, a[N];
map<int, int> mp; // 定义 map
signed main() {
	T = read();
	while (T--) {
		mp.clear();
		n = read();
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			a[i] = read();
			cnt += (mp[a[i] - i]++);
		}
		printf("%lld\n", cnt);
	}
	return 0;
}
```

---

## 作者：Waaifu_D (赞：0)

## 题意简述

给出 $T$ 组序列 $a$，长度为 $N$，询问有多少对 $(i,j)$ 满足 $i<j$ 并且 $a_j-a_i=j-i$ 。

## 解题思路

看到这题我们的第一个思路肯定是打一个无脑暴力，每个数都模拟一遍，但是 $ 1 \le t \le 10^4 $ 以及 $ 1 \le n \le 2 \cdot 10^5 $ 的数据范围是不会让我们这么简单的就通过这道题的，所以我们来研究一下正解

首先观察一下给我们的公式 

$a_j-a_i=j-i$

稍微变一下形式

$a_j-j=a_i-i$

可以发现变成这种形式后，我们只需要在输入的时候计算出输入数和 $i$ 的差，找到差相等的所有 $a_i$ 和 $a_j$ 即可

所以我们快乐的拿着初份代码去交了，愉悦RE，因为这个公式有可能出现负数，而我们的鸡肋数组解决不了这种问题

因此我们需要考虑怎么解决负数的问题

数组下标能为负数，我们就会想到 STL 中的 map容器 ，它支持下标可以是任意数据类型，所以我们利用它来解决这个问题

## Code

```cpp
#include<cstdio>
#include<iostream>
#include<map>
using namespace std;
long long n,ans;
map<long long,long long> k;//k表示差等于m[i]-i的m[j]-j
int main()
{
	long long t;//t组数据
	cin>>t;
	while(t--)
	{
		cin>>n;//输入n
		long long m[n+10];
		for(long long i=1; i<=n;i++)
		{
			scanf("%lld",&m[i]);//输入序列
			m[i]-=i;//计算序列值减去i的值
		}
		ans=0;//归0答案（易错）
		k.clear();//clear（）函数，可以清空map里的所有元素
		for(long long i=1; i<=n;i++)//从1到n枚举
		{
			if(k.count(m[i])) ans+=k[m[i]];
            		/*
                        count()函数返回指定元素出现的次数，如果不为0，答案就加上k[m[i]]，
                        即满足题目中给与的公式的两个序列中的数的数量
                        */
			++k[m[i]];//m[i]-i的差这个值出现了几次
            		
		}
		cout<<ans<<endl;
	}
}
```




---

## 作者：云浅知处 (赞：0)

## D. Same Differences

### Description

给一个长为 $n$ 的序列 $a$，求有多少组 $(i,j)$ 满足 $i<j$，且 $a_j-a_i=j-i$。

$t$ 组询问，$1\le t\le 10^4,1\le n\le 2\times10^5,1\le a_i\le n,\sum n\le 2\times10^5$。

### Solution

一眼题。

$$
a_j-a_i=j-i\iff a_j-j=a_i-i
$$

故对每个 $i$ 处理出 $a_i-i$，然后计数。

如果 $a_i-i$ 这个值出现了 $k$ 次，那么对答案的贡献就是 $C_k^2=\dfrac{k(k-1)}{2}$。

注意有可能 $a_i-i<0$，因此平移一下值域，把这一堆全部加上 $n$ 变成正的，再建桶计数。

（一开始以为 $n$ 范围是 $10^5$ 所以 WA 了两发）

```cpp
#include<cstdlib>
#include<iostream>
#include<cstring>

#define int long long

using namespace std;

int n,t;
int a[200005],b[400005],p[400005];

signed main(void){

    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=2*n;i++)b[i]=p[i]=0;
        int ans=0;
        for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i]-i+n;
        for(int i=1;i<=n;i++)p[b[i]]++;
        for(int i=1;i<=n*2;i++)ans+=(p[i]*(p[i]-1))/2;
        cout<<ans<<endl;
    }

    return 0;
}
```


---

## 作者：信守天下 (赞：0)

## [CF传送门](https://codeforces.ml/contest/1520/problem/D)
## [洛谷传送门](https://www.luogu.com.cn/problem/CF1520D)
## 思路
我们可以将式子进行移项。

$a_i - a_j = i - j \iff a_i - i = a_j - j$ 

那么我们可以在输入时就处理好每一组 $a_i - i$ 。

然后直接排序，再找相同的项，排序后相同的项是连续的一段。

统计当前相同数的项数，再统计方案数就好了。
## $code$
~~~cpp
#include <algorithm>
#include <iostream>
using namespace std;
const int kMaxN = 2e5 + 1;
int t, n;
long long ans, sum;
int a[kMaxN];
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      a[i] -= i;                   //预处理
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++) {
      if (i != n && a[i] == a[i + 1]) {
        ++sum;
      } else {
        ++sum;                  //注意还要加上当前数
        if (sum >= 2) {
          ans += sum * (sum - 1) / 2;//统计总方案数
        }
        sum = 0;
      }
    }
    cout << ans << endl;
    ans = sum = 0;
  }
  return 0;
}
~~~

---

## 作者：moqizhu2005 (赞：0)

###  题目大意

给你一个数列，判断$a_j-a_i=j-i(j>i)$的个数

### 解法

移项可得$a_j-j=a_i-i$，所以可以把每一项减去本身的位置。

接下来通过排序判断每项相等的个数。

最后通过等差数列分别判断每对相等的项的个数即可。

### 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll maxn=200005;
ll t,n,a[maxn];
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			a[i]-=i;
		}
		sort(a+1,a+1+n);
		ll cnt=1,ans=0;
		a[n+1]=999999999;
		for(int i=1;i<=n;i++){
			if(a[i]!=a[i+1]){
				ans+=cnt*(cnt-1)/2;
				cnt=1;
			}
			else cnt++;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

