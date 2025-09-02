# Interesting Subarray

## 题目描述

For an array $ a $ of integers let's denote its maximal element as $ \max(a) $ , and minimal as $ \min(a) $ . We will call an array $ a $ of $ k $ integers interesting if $ \max(a) - \min(a) \ge k $ . For example, array $ [1, 3, 4, 3] $ isn't interesting as $ \max(a) - \min(a) = 4 - 1 = 3 < 4 $ while array $ [7, 3, 0, 4, 3] $ is as $ \max(a) - \min(a) = 7 - 0 = 7 \ge 5 $ .

You are given an array $ a $ of $ n $ integers. Find some interesting nonempty subarray of $ a $ , or tell that it doesn't exist.

An array $ b $ is a subarray of an array $ a $ if $ b $ can be obtained from $ a $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end. In particular, an array is a subarray of itself.

## 说明/提示

In the second test case of the example, one of the interesting subarrays is $ a = [2, 0, 1, 9] $ : $ \max(a) - \min(a) = 9 - 0 = 9 \ge 4 $ .

## 样例 #1

### 输入

```
3
5
1 2 3 4 5
4
2 0 1 9
2
2019 2020
```

### 输出

```
NO
YES
1 4
NO
```

# 题解

## 作者：tangber (赞：8)

## 思路
先看题，发现只用求一组可行解就行了，~~刚开始我甚至以为要求最长的一串~~，于是问题就变成了如何用最简单的方法寻找到任意一组可行解。

观察样例 2：
```
2 0 1 9
```
不难发现还有两个可行解：
```2 0``` 和 ```1 9```。

因此做出大胆猜测：只要有连续两个数差值大于（或等于）$2$，就有一组可行解，反之，只要整个序列没有任何两个相邻的数差值大于（或等于）$2$，那么就不存在可行解。

证明方法很简单：假设有一个长度为 $n$ 的序列，它连续两个数差值小于 $2$，则它的极差是 $n-1$（每两个数差为 $1$ 且不存在相同的数）。而 $n-1<n$，即极差小于长度。

## AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[200005];
bool flag;
signed main()
{
	cin>>t;//多测 
	for(int ask=1;ask<=t;ask++)
	{
		flag=0;//有多组数据，一定要清零！ 
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<n;i++)
		{
			if(abs(a[i]-a[i+1])>=2) 
			{
				flag=1;//有解标记 
				cout<<"Yes"<<endl<<i<<" "<<i+1<<endl;
				break;//有一组可行解就够了 
			}
		}
		if(!flag)cout<<"No"<<endl;//没有解 
	}
	return 0; 
}
```

---

## 作者：naroto2022 (赞：2)

#  CF1270B题解

### 题面

[题目传送门](https://www.luogu.com.cn/problem/CF1270B)

给出一个数列，要求找出一段连续的子数列满足这个子数列的最大值与最小值之差不小于其元素个数（子数列可以是原数列）。

即给定一个数组 $a$：$a_1,a_2,a_3\cdots a_n$，要找出两个下标 $l,r(l<r,l,r\in [1,n])$ 使得 $|a_r-a_l|\leqslant r-l+1$。

### 思路

首先，~~看到这题就想偷懒~~，于是就想到要是只用判断长度为 $2$ 的子串那多简单啊，可仔细一想，还真行！

那就要说我发现的一个结论了：有一个长度为 $n$ 的数组 $a$ 是合法的，至少有一个长度为 $2$ 的子序列也是合法的。

证明这个结论也很简单，其实就用反证法就行了：

假设有一个长度为 $n$ 的数组 $a$ 是合法的，但是 $a$ 的每一个长度为 $2$ 子序列都不合法。

那么，依假设，$|a_2-a_1|<2,|a_3-a_2|<2,\cdots,|a_n-a_{n-1}|<2$，

$\because a_i\in \mathbb{Z}(i\in[1,n])$，

$\therefore|a_2-a_1|\leqslant1,|a_3-a_2|\leqslant1,\cdots,|a_n-a_{n-1}|\leqslant1$，

$\therefore$ 数列最大值减数列最小值 $<n-1$，即数列不合法，与假设矛盾！

故有一个长度为 $n$ 的数组 $a$ 是合法的，至少有一个长度为 $2$ 的子序列也是合法的。

于是，只需判断长度为 $2$ 的子串即可。

### 总结

1. 反证法。

### 代码

```
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[200005],T,n;
int main(){
	scanf("%d",&T);
    while(T--){
    	scanf("%d",&n);
        for(int i=1; i<=n; i++) scanf("%d",&a[i]);
        bool ok=1;//判断是否有解 
        for(int i=2; i<=n; i++){
            if(abs(a[i]-a[i-1])>=2){//要是这个长度为2的子序列合法 
                ok=0;//有解
                printf("YES\n%d %d\n",i-1,i);
                break;
            }
        }
        if(ok) printf("NO\n");//无解则输出 NO
    }
    return 0;
}
```


---

## 作者：寒鸽儿 (赞：2)

需要找到极差大于长度的字串。  
记原序列为$A$。  
假设存在这样的字串$[l,r]$,那么必定有一个字串$[l', r']$,其中$A_l'$和$A_r'$为$[l,r]$的两个最值。  
根据定义$r' - l' + 1 \leqslant |A_l' - A_r'|$。子串的最大相邻位差必然大于2。  
所有差大于2的相邻元素构成的长度为2的子串必然符合条件。而所有更长的符合条件的子串也必然有相邻元素差大于2的子串,所以只要检验相邻元素差是否大于2即可。  
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t, n, tmp, lst, pls;
	bool flg = false;
	cin >> t;
	while(t--) {
		cin >> n >> lst;
		flg = false;
		for(int i = 2; i <= n; ++i) {
			cin >> tmp;
			if(abs(tmp - lst) >= 2) {
				pls = i;
				flg = true;
			}
			lst = tmp;
		}
		if(flg) cout << "YES\n" << pls - 1 << ' ' << pls << '\n';
		else cout << "NO\n";
	}
	return 0;
}
```

---

## 作者：cff_0102 (赞：1)

假设有一个合法的长度为 $n$ 的子序列，但是其中每个长度为 $2$ 的子序列都不合法，即 $|a_2-a_1|<2,|a_3-a_2|<2,\dots,|a_n-a_{n-1}|<2$。因为 $a_1,a_2$ 都是整数，所以 $|a_2-a_1|<2$ 可以转化成 $|a_2-a_1|\le 1$。

因为 $|a_2-a_1|\le1,|a_3-a_2|\le1,\dots,|a_n-a_{n-1}|\le1$，所以整个序列的最大值和最小值之差会超过 $n-1$。那么这个长度为 $n$ 的子序列必然是不合法的，与刚开始的假设矛盾。

因此，“有一个合法的长度为 $n$ 的子序列，但是其中每个长度为 $2$ 的子序列都不合法”的情况不存在，那么可以得出“若一个长度为 $n$ 的子序列是合法的，则这个序列必有一个长度为 $2$ 的子序列也是合法的”，“若一个序列中每个长度为 $2$ 的子序列都不合法，则这个序列必然不是合法的”。

那么，只用判断每个长度为 $2$ 的子序列是否合法即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[229028];
int main(){
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        bool t=1;//判断是否无解（无解为 1，有解为 0）
        for(int i=1;i<n;i++){
            if(abs(a[i]-a[i-1])>=2){
                t=0;//有解
                cout<<"YES\n"<<i<<" "<<i+1<<endl;//输出 YES 还有这段子序列的起始位置和终止位置
                break;
            }
        }
        if(t)cout<<"NO\n";//无解则输出 NO
    }
    return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

这道题刚开始被我想复杂了，就随手胡了个性质也就是 $min$ 和 $max$ 都是在这个子序列的两端的，否则我们可以剔除多余的元素，然后就有手胡了棵区间加区间查 $max$ 的线段树，然后就调了一个小时……   
调崩溃了后就果断继续口胡更深的性质：如果两两之间没有一个可以满足题目要求，题目中就没有满足题目要求的连续子序列了。   
我们就假装模拟一下，假设现在 $a$ 数组里有三个元素，$a_1 , a_2 , a_3$，如果此时 $abs(a_1 - a_2) \leq 1$ , $abs(a_2 - a_3) \leq 1$ ，那么说明这三个数里面的最大值减最小值一定小于等于 $2$ ，即证明此时所有长度为 $3$ 的子序列不合法，推广到所有形式中，进行数学归纳证明后亦可得证此时所有元素不合法。   
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,x[2],a,b;
int main()
{
	int T;
	scanf("%d",&T);
	while(T --)
	{
		bool flag = false;
		scanf("%d",&n);
		for(int i = 1 ; i <= n ; i ++)
		{
			scanf("%d",&x[i % 2]);
			if(i == 1) continue;
			if(abs(x[1] - x[0]) > 1)
			{
				a = i - 1 , b = i;
				flag = true;
			}
		}
		if(flag) printf("YES\n%d %d\n" , a , b);
		if(!flag) printf("NO\n");
	}
	return 0;
}
```

---

## 作者：liuyz11 (赞：1)

# 题解 CF1270B 【Interesting Subarray】

该场比赛的所有题题解：[我的博客求围观](https://www.cnblogs.com/nblyz2003/p/12161998.html)

题目大意：有一个数列a，让你找任意一个子段满足子段的最大值减最小值大于等于子段长度。

感觉这套的B题也比之前的难了点，看着屏幕愣了半天，可能最近脑子不对劲。

如果子段(l，r)满足条件，那么必定存在i，j满足a[i] - i < a[j] - j ，或者a[i] + i > a[j] + j。

那么只需记录下在所有的i，j( i <= j )，最小的a[i] - i和最大的a[i] + i，如果满足上面的条件就输出这一对。

代码如下:

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define MAXN 200005
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 1 << 30;
const int p = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % p; a = 1ll * a * a % p;} return x % p;}

int a[MAXN];

int main(){
	int t;
	scanf("%d", &t);
	rep(times, 1, t){
		int n;
		scanf("%d", &n);
		rep(i, 1, n) scanf("%d", &a[i]);
		int s = INF, id = 0, ans = 0;
		rep(i, 1, n){
			if(s < a[i] - i){
				printf("YES\n%d %d\n", id, i);
				ans = 1;
				break;
			}
			if(a[i] - i < s){
				s = a[i] - i;
				id = i;
			}
		}
		if(!ans){
			s = 0, id = 0;
			rep(i, 1, n){
				if(s > a[i] + i){
					printf("YES\n%d %d\n", id, i);
					ans = 1;
					break;
				}
				if(a[i] + i > s){
					s = a[i] + i;
					id = i;
				}
			}
		}
		if(!ans) puts("NO");
	}
    return 0;
}
```

---

## 作者：TEoS (赞：1)

22:20下晚自习所以只打了10+min，然而这并不能成为我脑抽没一眼看出B题的借口，所以又掉回绿名了qwq。所以我还是太菜了。

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/12120667.html)

**题意分析**

给出一个数列，要求找出一段连续的子数列满足这个子数列的最大值与最小值之差不小于其元素个数。

**思路分析**

我们从最少的元素开始考虑。只有一个元素的子数列显然是不可行的，考虑含有两个元素的子数列。

可以发现，只要这两个元素的差不小于2即为可行，因此我们在输入的同时比较相邻的元素判断是否可行即可。

进一步分析可以发现，若整个数列都找不到满足上面这个条件的两个元素的子数列，则整个数列一定也不可行。因此按上面的方法判断即可。

```c++
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int t,n;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		bool ok=0;
		for(int i=1,x1=-1,x2;i<=n;i++)
		{
			scanf("%d",&x2);
			if(abs(x1-x2)>1 && !ok && x1!=-1)
				printf("YES\n%d %d\n",i-1,i),ok=1;
			x1=x2;
		}
		if(!ok)
			puts("NO");
	}
	return 0;
}
```



---

## 作者：Wide_Master (赞：0)

## 题意

$t$ 组数据。

给你一个包含 $n$ 个正整数的序列 $a$，你需要从中找到一个连续子序列，使得这个连续子序列的最大值减最小值的差大于等于这个连续子序列的元素个数。如果能找到，还要输出一种构造方案。

## 分析

明显发现，如果这个序列所有长度为 $2$ 的连续子序列都不符合要求，那么答案显然无解，反之有解。

那么问题来了，为什么长度为 $1$，长度为 $3$，或者更长的不行呢？

我们一个一个看。

1. 如果长度为 $1$，那么最大值和最小值均为本身，那么最大值减最小值为 $0$，不符合要求。
2. 如果长度为 $3$ 或者更大，我们发现，他的存在是基于长度为 $2$ 的连续子序列不存在的情况下而诞生的，但是我们发现，如果长度为 $2$ 的连续子序列都找不到，那么长度为 $3$ 的连续子序列就更找不到了，更何况更大的呢。 因为你没有任何一种情况满足长度为 $2$ 的子序列不符合要求，但是长度为 $3$ 的子序列却符合要求了。所以不符合要求。

## 总结

综上所述，如果说长度为 $2$ 的连续子序列没有符合情况的，那么就无解，否则输出这两个数的位置即可。

## 代码

```cpp
//By xiaozhou001
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+7;
int t,n,a[N],flag;
int main()
{
    ios::sync_with_stdio(false);//解除cin/cout的流绑定
    cin>>t;
    while(t--){
        flag=1;//一定要注意多测清空
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];//我是输入
        for(int i=1;i<n;i++)
            if(abs(a[i]-a[i+1])>=2){//我是判断
                cout<<"YES"<<endl<<i<<" "<<i+1<<endl;//输出有解情况
                flag=0;//代表已经找到了一组解
                break;//一种情况就够了，SPJ会帮你扫清一切障碍
            }
        if(flag)cout<<"NO"<<endl;//无解
    }
    return 0;
}
``````

---

## 作者：Wrong_Accept (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1270B)

## 前置知识
反证法：若发现某条件**不可能不成立**，那么这个条件就**一定**成立。（大概）

## 题目分析
关于此题有一个结论：能找出合法子串的序列，**一定**能找出长度是 $2$ 的合法子串。

这个结论可用**反证法**证明：假设长度为 $n$ 的序列 $a$，**不能**找出长度是 $2$ 的合法子串，也就是：
$$\left | a_1 - a_2 \right | < 2, \left | a_2 - a_3 \right | < 2, \left | a_3 - a_4 \right | < 2, \cdots , \left | a_{n - 2} - a_{n - 1} \right | < 2, \left | a_{n - 1} - a_n \right | < 2$$
$\because a$ 中都是**整数**。
$$\therefore \left | a_1 - a_2 \right | \le 1, \left | a_2 - a_3 \right | \le 1, \left | a_3 - a_4 \right | \le 1, \cdots , \left | a_{n - 2} - a_{n - 1} \right | \le 1, \left | a_{n - 1} - a_n \right | \le 1$$
$\therefore$ 序列最大值 $-$ 序列最小值  $\le n - 1$

$\therefore$ **不能**找出长度是 $2$ 的合法子串的序列，**一定不能**找出合法子串。也就是说，能找出合法子串的序列，**一定**能找出长度是 $2$ 的合法子串。

所以我们只需要枚举长度是 $2$ 的子串就行了。

## AC code
```python
test_cases_amount = int(input())
while test_cases_amount:
    input()
    array = list(map(int, input().split()))
    for index, value in enumerate(array):
        if index and abs(value - array[index - 1]) >= 2:
            print('YES')
            print(index, index + 1)
            break
    else:
        print('NO')
    test_cases_amount -= 1
```

---

## 作者：IYSY2009I (赞：0)

我们凭借人类直觉想出正解：只要检查由于相邻两个数之差是否 $>1$ 就可以了，如果有，输出 $\texttt{YES}$ 和这两个数组成的区间，否则输出 $\texttt{NO}$。

我们来考虑一下如何证明这个结论。由于如果相邻两个数之差是否 $>1$ 就存在解很显然，那么我们只需要证明如果相邻两个数之差 $ \le 1$ 就不存在解就可以了。

我们设区间长度为 $len$，那么这个区间最大值与最小值之差最大值只会是一端是最小值，一端是最大值，这个区间为一个等差数列。设最小值为 $x$，则最大值就为 $x+len-1$，所以最大值 $-$ 最小值 $=len-1<len$，于是我们就证出来了。

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[200005];
void cf(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<n;i++)
		if(abs(a[i+1]-a[i])>=2){
			printf("YES\n%d %d\n",i,i+1);
			return;
		}
	printf("NO\n");
	return;
}
int main(){
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
		cf();
}
```


---

## 作者：Acerkaio (赞：0)

### 题目

[传送门](https://www.luogu.com.cn/problem/CF1270B)

### 思路

由特殊到一般，首先，我们从最简单的只含有一个元素的子序列（为了方便描述，以下子序列皆表示连续的子序列）开始分析。

1. 显然，最大值最小值都是这个元素，其差为零，不符合题意，所以排除只含有一个元素的子序列。
1. 然后分析只含有两个元素的子序列，发现只要子序列第一个元素与第二个元素的差的绝对值不小于二就可以得到答案。
1. 然后就是含有三个元素的子序列，它基于在所有的只含有两个元素的子序列都找不到答案之上，因为如果找到了就获得了答案，没必要再找含有三个元素的子序列，我们发现，这样找不到了，为什么？因为它基于在所有的只含有两个元素的子序列都找不到答案，所以子序列第一个元素与第二个元素之差的绝对值小于二，第二个元素与第三个元素之差的绝对值小于二，所以第一个元素与第二个元素之差的绝对值小于三，所以不存在。多个元素子序列以此类推。

### 总结思路

枚举每一个只含有两个元素的子序列，如果其差绝对值不小于二就输出答案。

如果没有找到，就代表不存在。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {
	int n = 0, m = 1;
	char a = getchar();
	while (!isdigit(a)) {
		if (a == '-') m = -1;
		a = getchar();
	}
	while (isdigit(a)) {
		n = (n << 3) + (n << 1) + (a ^ 48);
		a = getchar();
	}
	return n * m;
}
signed main() {
	int t =  read();
	while (t--) {
		int n = read(), now, last;
		bool flag = 0;
		for (int i = 1; i <= n; i++) {
			now = read();
			if(i == 1) {
				last = now;
				continue;
			}
			if(abs(now - last) > 1 && !flag) {
				cout << "YES\n";
				cout << i - 1 << " " << i << '\n';
				flag = 1;
			}
			last = now;
		}
		if (!flag) cout << "NO\n";
	}
	return 0;
}
```


---

