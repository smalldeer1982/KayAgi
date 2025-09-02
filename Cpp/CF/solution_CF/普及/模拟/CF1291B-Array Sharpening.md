# Array Sharpening

## 题目描述

You're given an array $ a_1, \ldots, a_n $ of $ n $ non-negative integers.

Let's call it sharpened if and only if there exists an integer $ 1 \le k \le n $ such that $ a_1 < a_2 < \ldots < a_k $ and $ a_k > a_{k+1} > \ldots > a_n $ . In particular, any strictly increasing or strictly decreasing array is sharpened. For example:

- The arrays $ [4] $ , $ [0, 1] $ , $ [12, 10, 8] $ and $ [3, 11, 15, 9, 7, 4] $ are sharpened;
- The arrays $ [2, 8, 2, 8, 6, 5] $ , $ [0, 1, 1, 0] $ and $ [2, 5, 6, 9, 8, 8] $ are not sharpened.

You can do the following operation as many times as you want: choose any strictly positive element of the array, and decrease it by one. Formally, you can choose any $ i $ ( $ 1 \le i \le n $ ) such that $ a_i>0 $ and assign $ a_i := a_i - 1 $ .

Tell if it's possible to make the given array sharpened using some number (possibly zero) of these operations.

## 说明/提示

In the first and the second test case of the first test, the given array is already sharpened.

In the third test case of the first test, we can transform the array into $ [3, 11, 15, 9, 7, 4] $ (decrease the first element $ 97 $ times and decrease the last element $ 4 $ times). It is sharpened because $ 3 < 11 < 15 $ and $ 15 > 9 > 7 > 4 $ .

In the fourth test case of the first test, it's impossible to make the given array sharpened.

## 样例 #1

### 输入

```
10
1
248618
3
12 10 8
6
100 11 15 9 7 8
4
0 1 1 0
2
0 0
2
0 1
2
1 0
2
1 1
3
0 1 0
3
1 0 1```

### 输出

```
Yes
Yes
Yes
No
No
Yes
Yes
Yes
Yes
No```

# 题解

## 作者：liuyongle (赞：1)

#### 思路分析

如何知道是否可以使前缀 $[1,k]$ 严格单调递增？我们只需要考虑以下简单的贪心解决方案：将值取为 $0,1,\dots ,k-1$（最小可能值）。 只有在整个前缀中都满足 $a_i \geq i-1$ 时，才有可能。

类似地，只要且仅当在整个后缀中都满足 $a_i \geq n-i$ 时，才能使后缀 $k;n$ 严格单调递减。

使用这些思想，我们可以在 $O(n)$ 内计算出严格单调递增的最长前缀和严格单调递减的后缀。最后，我们只需要检查它们的交集是否为非空即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int nbTests; cin >> nbTests;
    while (nbTests--) {
	    int nbElem; cin >> nbElem;
	    vector<int> tab(nbElem);

	    for (int i = 0; i < nbElem; ++i)
		    cin >> tab[i];

	    int prefixEnd = -1, suffixEnd = nbElem;

	    for (int i = 0; i < nbElem; ++i) {
		    if (tab[i] < i) break;
		    prefixEnd = i;
	    }
	    for (int i = nbElem-1; i >= 0; --i) {
		    if (tab[i] < (nbElem-1)-i) break;
		    suffixEnd = i;
	    }

	    if (suffixEnd <= prefixEnd) // Non-empty intersection
		    cout << "Yes\n";
	    else
		    cout << "No\n";
    }
}
```

---

## 作者：Loser_King (赞：1)

这次比赛我增了11分，保住了我青名(```specialist```)的称号。

~~然而并没有什么卵用~~

这题作为```Div.2```的$B$题来说还是比较水的。

~~然而还是花了一个小时多一点的时间~~

## 进入正题

### 题意
> 定义```锐化数组```(```Sharpened Array```)$A$为存在一个数$k$,使得$1\leq k \leq n$且$a_1<a_2<...<a_k$且$a_k>a_{k+1}>a_{k+2}>...>a_n$。

现在给定一个数组$A$(保证所有数非负)和一种操作：

- 将一个**严格为正**的数-1.

问：

是否可以进行有限次该操作使数组$A$为```锐化数组```。

### 思路

既然~~良心~~出题人没有规定操作的次数，那我们就开始模拟锐化操作。

一个总和最小的```锐化数组```应该是这样的：

$$0,1,2,...,k-2,k-1,k,k-1,k-2,...,2,1,0$$

我们就进行模拟，看是否能构造出类似这样的数组。

### 做法

定义变量```l```为可以构建$a_1,a_2,...,a_l$使几次操作后可以变成$1,2,...l$。

定义变量```r```为可以构建$a_{n-r+1},a_{n-r+2},...,a_n$使几次操作后可以变成$n-r+1,n-r+2,...n$。

我们找出最大的```l```和```r```，然后判断“峰顶”是否比它们都要高。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
int t,n,a[300010];
int main(){
   scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		a[0]=a[n+1]=-1;//因为要使a[1]和a[n]为0
		int l=1,r=n;
		while(a[l-1]<a[l+1]-1&&a[l]>a[l-1])a[l]=a[l-1]+1,l++;//找出最大的l
		while(a[r-1]-1>a[r+1]&&a[r]>a[r+1])a[r]=a[r+1]+1,r--;//找出最大的r
		puts(l>=r||l==r-1&&a[l+1]>a[r]&&a[l+1]>a[l]?"Yes":"No");//判断峰顶
	}
}
```

---

## 作者：OIer_Hhy (赞：0)

第一眼看到这题，会想到暴力枚举每个 `k`。

但一看数据范围，$O(N^2)$ 的算法肯定 TLE。

于是我们转变思路……

   很显然，序列 $a$ 为 $0,1,\cdots,n-1$ 时满足条件，为 $n-1,n-2,\cdots,0$ 时也满足条件。

   所以，我们要找最后一个满足序列 $a_1,a_2,\dots,a_l$ 严格单调递增的点 $l$ 和第一个满足序列 $a_r,a_{r+1},\dots,a_n$ 严格单调递降的点 $r$。

   若 $l \ge r$，说明至少有一个点 $k (r \le k \le l) $ 符合题意。

   否则序列 $a$ 不可能变成一个前半部分单调递增，后半部分单调递降的序列。
 
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
void LALakerAKIOI(){
	#define endl '\n'
	#define int long long
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
int t,n,a[300010];
string ans[2]={"No\n","Yes\n"};
signed main(){
	LALakerAKIOI();
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i]; 
		int l=0,r=n+1;
		for(int i=1;i<=n;i++){
			if(a[i]<i-1) break;
			l=i;
		}
		for(int i=n;i>=1;i--){
			if(a[i]<n-i) break;
			r=i;
		}
		cout<<ans[(r<=l)];
	}
	
	return 0;
}
```

---

## 作者：liuli688 (赞：0)

## 思路：

若数组的前 $kf$ 项能够 sharpened 且数组的后 $kb$ 项能够 sharpened，在 $kf \ge kb$ 时可以将整个数组变 sharpened。

判定数组能被 sharpened 的方法：考虑使用贪心，将第 $a_i$ 项减到最小，使数组严格单调递增或严格单调递减。

### 手玩样例：

#### \#1:

以 $[100$，$11$，$15$，$9$，$7$，$8]$ 为例。

从前往后搜索：

$$100 \gets 0$$

$$11 \gets 1$$

$$15 \gets 2$$

$$9 \gets 3$$

$$7 \gets 4$$

$$8 \gets 5$$

始终没有出现不能将第 $a_i$ 项减到最小的值，故有解。

#### \#2:

以 $[4$，$1$，$5$，$4$，$1$，$1]$ 为例。

从前往后搜索：

$$4 \gets 0$$

$$1 \gets 1$$

$$5 \gets 2$$

$$4 \gets 3$$

此时，$1$ 无法变成 $4$，则 $kf \gets 3$（我是按下标为 $0$ 算的）。

从后往前搜索：

$$1 \gets 0$$

$$1 \gets 1$$

$$4 \gets 2$$

$$5 \gets 3$$

此时，$1$ 无法变成 $4$，则 $kb \gets 2$。

$3 \ge 2$，故有解。

考虑扫描两次数组，第一次从前往后搜索，记录 $kf$，第二次从后往前搜索，记录 $kb$。然后判断是否 $kf \ge kb$ 便可得出结论。

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[300005],n,t,kf,kb,i;
int main()
{
    ios::sync_with_stdio(0);//<iostream>加速
	cin >> t;
	while(t--)
	{
		cin >> n;
		kf = -1;//记录特判
		kb = -1;
		for(i = 0;i < n;i++)
			cin >> a[i];
		for(i = 0;i < n;i++)//从前往后搜索
			if(a[i] < i)
			{
				kf = i - 1;
				break;
			}
		for(i = n - 1;i >= 0;i--)//从后往前搜索
			if(a[i] < n - i - 1)
			{
				kb = i + 1;
				break;
			}
		if(!(kf + 1) || !(kb + 1))//特判
		{
			cout << "Yes\n";
			continue;
		}
		if(kb <= kf)//正常判断
		{
			cout << "Yes\n";
			continue;
		}
		cout << "No\n";
	}
	return 0;
}

```

---

## 作者：Ba_creeper (赞：0)

#### 题目分析

对于一个序列 $a$，我们需要找一个分界线，使左半边严格单调递增，而右半边严格单调递减。

我们可以构建出最小的满足题意的序列 $b$，如下面这样：

$$
0,1,2,...,M-1,M,M-1,...,2,1,0
$$

那么，我们可以将 $a_i$ 与 $b_i$ 作比较，如果 $a_i < b_i$，那么一定不合法。

当 $n$ 为奇数时，上方叙述成立。但是当 $n$ 为偶数时，我们需要构造这样两个 $b$ 数列：

$$
0,1,2,...,M-1,M,M-1,M-2,...,2,1,0
$$

$$
0,1,2,...,M-2,M-1,M,M-1,...,2,1,0
$$

然后比较是否 $a_i < b_i$ 即可。

#### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll T, n;
ll a[300005], b[300005];

void C(){ //不能初始化整个数组，否则会 TLE
    memset(a, 0, sizeof(long long) * (n + 1));
    memset(b, 0, sizeof(long long) * (n + 1));
}

int main()
{
    T = read();
    while (T--){
        C();
        n = read();
        if (n % 2 == 1) { //n为奇数
            for (int i = 1; i <= n; ++i)
                a[i] = read();
            ll h = 1, t = n, cnt = -1;
            while (1) { //构造 b 数列
                if (h == t){
                    b[h] = ++cnt;
                    break;
                }
                b[h] = b[t] = ++cnt;
                h++, t--;
            }
            bool ok = 0;
            for (int i = 1; i <= n; ++i) {
                if (a[i] < b[i]) {
                    puts("No");
                    ok = 1;
                    break;
                }
            }
            if (ok == 0)
                puts("Yes");
        }
        else { //n为偶数
            int sb;
            for (int i = 1; i <= n; ++i)
                a[i] = read();

            ll h = 1, t = n, cnt = -1;
            while (1) { //构造 b 数列
                if (h + 1 == t) {
                    b[h] = b[t] = ++cnt;
                    sb = h;
                    b[h]++;
                    break;
                }

                b[h] = b[t] = ++cnt;
                h++, t--;
            }
            bool ok = 0;
            for (int i = 1; i <= n; ++i) {
                if (a[i] < b[i]) {
                    ok = 1;
                    break;
                }
            }
            if (ok == 0) {
                puts("Yes");
                continue;
            }

            b[sb]--; //换成第二个 b 数列
            b[sb + 1]++;

            ok = 0;
            for (int i = 1; i <= n; ++i) {
                if (a[i] < b[i]) {
                    puts("No");
                    ok = 1;
                    break;
                }
            }
            if (ok == 0)
                puts("Yes");
        }
    }
    return 0;
}
```

---

## 作者：邓布利多6 (赞：0)

## **[Codeforces Round #616 B](http://codeforces.com/contest/1291)**


### **题目翻译**
若一个序列 $a$ 中存在一个 $ k(1 \le k \le n)$ ，使得 $a_{1} < a_{2} < ... < a_{k} $ 且 $a_{k} > a_{k + 1} > ... > a_{n} $，则我们可以称它  $sharpened $。

现在给定一个非负整数序列，每次可以使其中一个正整数的值 $-1$，问能否把它变 $sharpened $。

输入包含 $t$ 组数据，每组有一个 $n$ 和一个长度为 $n$ 的序列，问能否把它变 $sharpened $ ,  能输出 
$Yes$， 否则输出 $No$。


### **思路**
由于只能变小不能变大，所以单调上升的部分必须满足 $a[i] \geq i-1$ ,单调下降的满足 $a[i] \geq n-i$ 。

我们从前往后扫找到第一个不满足 $a[i] \geq i-1$ 的，那么它的前面都是可以通过不断 $-1$ 满足单调上升的； 从后往前找第一个不满足 $a[i] \geq n-i$ 的，那么它的后面都是可以通过不断 $-1$ 满足单调递减的。 如果两数有交集说明有解，否则无解。

### **代码**
```cpp
#include <iostream>
using namespace std;
const int N = 1000001;
int t, n, a[N], high, high2;
int main()
{
	cin >> t;
	while(t--)
	{
		cin >> n; high = high2 = 0;
		for(int i = 1; i <= n; i++) cin >> a[i];
		for(int i = 1; i <= n; i++)
			if(a[i] < i - 1) { high = i - 1; break; }
		//找第一个不满足 a[i] >= i - 1 的（从前往后）
		if(!high) high = n;
		for(int i = n; i; i--) 
			if(a[i] < (n - i)) { high2 = i + 1; break; }
		//找第一个不满足 a[i] >= n - i 的（从后往前）
		if(!high2) high2 = 1;
		cout << (high2 > high ? "No" : "Yes") << endl;
		//判断是否有交集，输出答案
	}
	return 0;
}
```

---

