# Add to Neighbour and Remove

## 题目描述

Polycarp was given an array of $ a[1 \dots n] $ of $ n $ integers. He can perform the following operation with the array $ a $ no more than $ n $ times:

- Polycarp selects the index $ i $ and adds the value $ a_i $ to one of his choice of its neighbors. More formally, Polycarp adds the value of $ a_i $ to $ a_{i-1} $ or to $ a_{i+1} $ (if such a neighbor does not exist, then it is impossible to add to it).
- After adding it, Polycarp removes the $ i $ -th element from the $ a $ array. During this step the length of $ a $ is decreased by $ 1 $ .

The two items above together denote one single operation.

For example, if Polycarp has an array $ a = [3, 1, 6, 6, 2] $ , then it can perform the following sequence of operations with it:

- Polycarp selects $ i = 2 $ and adds the value $ a_i $ to $ (i-1) $ -th element: $ a = [4, 6, 6, 2] $ .
- Polycarp selects $ i = 1 $ and adds the value $ a_i $ to $ (i+1) $ -th element: $ a = [10, 6, 2] $ .
- Polycarp selects $ i = 3 $ and adds the value $ a_i $ to $ (i-1) $ -th element: $ a = [10, 8] $ .
- Polycarp selects $ i = 2 $ and adds the value $ a_i $ to $ (i-1) $ -th element: $ a = [18] $ .

Note that Polycarp could stop performing operations at any time.

Polycarp wondered how many minimum operations he would need to perform to make all the elements of $ a $ equal (i.e., he wants all $ a_i $ are equal to each other).

## 说明/提示

In the first test case of the example, the answer can be constructed like this (just one way among many other ways):

 $ [3, 1, 6, 6, 2] $ $ \xrightarrow[]{i=4,~add~to~left} $ $ [3, 1, 12, 2] $ $ \xrightarrow[]{i=2,~add~to~right} $ $ [3, 13, 2] $ $ \xrightarrow[]{i=1,~add~to~right} $ $ [16, 2] $ $ \xrightarrow[]{i=2,~add~to~left} $ $ [18] $ . All elements of the array $ [18] $ are the same.

In the second test case of the example, the answer can be constructed like this (just one way among other ways):

 $ [1, 2, 2, 1] $ $ \xrightarrow[]{i=1,~add~to~right} $ $ [3, 2, 1] $ $ \xrightarrow[]{i=3,~add~to~left} $ $ [3, 3] $ . All elements of the array $ [3, 3] $ are the same.

In the third test case of the example, Polycarp doesn't need to perform any operations since $ [2, 2, 2] $ contains equal (same) elements only.

In the fourth test case of the example, the answer can be constructed like this (just one way among other ways):

 $ [6, 3, 2, 1] $ $ \xrightarrow[]{i=3,~add~to~right} $ $ [6, 3, 3] $ $ \xrightarrow[]{i=3,~add~to~left} $ $ [6, 6] $ . All elements of the array $ [6, 6] $ are the same.

## 样例 #1

### 输入

```
4
5
3 1 6 6 2
4
1 2 2 1
3
2 2 2
4
6 3 2 1```

### 输出

```
4
2
0
2```

# 题解

## 作者：xiaomuyun (赞：22)

[题面链接](https://www.luogu.com.cn/problem/CF1462D)

## 题目分析

实际上题目说的操作最终就是要把整个序列分成若干段，且每一段的和相等。

其实可以通过看题面发现很多有用的东西。

> It is guaranteed that the sum of $n$ over all test cases does not exceed $3000$.（可以保证，每组测试数据中 $n$ 的和不会超过 $3000$）

因此 $\mathcal{O}(n^2)$ 算法肯定是可以过的。这时我们可以从 $\mathcal{O}(n^2)$ 的角度想。想到 $n^2$，也就不难想到枚举。枚举什么呢？简单想一想就能发现，可以枚举第一段序列的长度。因为这段序列的左端点是 $1$，所以只要枚举右端点即可。

每当枚举出一个第一段序列的长度 $i$，我们就可以从 $i+1$ 开始往后枚举，并维护一个 $sum$，当 $sum>$ 第一段序列的数之和 时，就说明答案不可行；当 $sum=$ 第一段序列的数之和 时，就说明这一段已经满了。这时就可以把维护的 $sum$ 归 $0$，然后开始下一段序列。
## 代码实现
```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
int t,n,a[3001];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i) scanf("%d",&a[i]);
		int sum=0,acnt=0,cnt,res=0x3f3f3f3f;
		for(int i=1;i<=n;++i){
			sum+=a[i];
			if(i>1) ++acnt;//注意如果是一段的开头的话不用增加操作数
			cnt=acnt;
			int tmpsum=0;//用来存每一段的和
			bool flag=true;
			for(int j=i+1;j<=n;++j){
				if(tmpsum) ++cnt;//同上
				tmpsum+=a[j];
				if(tmpsum==sum) tmpsum=0;
				else if(tmpsum>sum){//答案不可行
					flag=false;
					break;
				}
			}
			if(flag&&!tmpsum) res=min(cnt,res);//更新答案
		}
		printf("%d\n",res);
	}
	return 0;
}
```
## 写在最后
希望这篇题解能让大家有所收获，有所收获的同时不要忘了留下一个免费的赞（

---

## 作者：菲斯斯夫斯基 (赞：5)

### CF1462D Add to Neighbour and Remove 题解

$\color{green}\textbf{题目大意}$

将两个数合并成一个数，进行若干次合并后，使数组中所有数相等。

$\color{red}\textbf{我的思路}$

**暴力枚举！**

我们先看数据，$n\le3\times10^3$，$O(n^2)$ 没有任何的问题。

枚举什么呢？枚举合并的次数。

我们枚举合并的次数为 $i$。

因为它们是不断合并的，所以它们的和不会变，又因为合并后每个数相同，所以知道了 $i$ 后，就可以知道合并后的数了。

$\color{blue}\textbf{程序实现}$

有了上面的思路后就很简单了，我们只需要判断两个：

- 它们的和 $sum$ 是否能够整除剩下的数的个数。

- 设最后剩下的数均为 $k$，判断这些数能否刚好合成 $(n-i)$ 个 $k$。

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;
int t,n,a[100010],sum;
bool pd(int k,int w)//k代表剩下的数，w代表剩下几个数，即 n-i
{
	 int l=0,x=0;
	 for(int i=1;i<=n;i++)
	 {
		 l+=a[i];//加上当前数
		 if(l>k)return false;//大于则不能合成
		 if(l==k)
			 l=0,x++;//相等则可以多合成一个k,个数加一
	 }
	 if(x==w)return true;//能刚好合成 (n-i) 个 k
}
int main()
{
     cin>>t;
	 while(t)
	 {
		 t--;
		 cin>>n;
		 sum=0;
		 for(int i=1;i<=n;i++)
			 cin>>a[i],sum+=a[i];//求和
		 for(int i=0;i<n;i++)
		 {
			 if(sum%(n-i))continue;//如果不能整除就跳过
			 if(pd(sum/(n-i),n-i))//判断是否能刚好合成 (n-i) 个 k
			 {
				 cout<<i<<endl;
				 break;
			 }
		 }
	 }
    return 0;
}
```


---

## 作者：ChrisWangZi (赞：2)

# CF1462D Add to Neighbour and Remove 题解

## [题目传送门](https://www.luogu.com.cn/problem/CF1462D)

## 思路分析

由于序列最后要变成若干个相同的数，而操作过程中它们的和是不会发生改变的，所以：**最后序列中的那个数一定是一开始序列和的因数**。

当我们知道这一点时，大概思路就有了：

1. 求和；

2. 列出和的因数（这里我们要用 $\mathcal{O(\sqrt{sum})}$ 的方法做，否则 ${O(\text T \times sum)}$ 的总复杂度会超时）；

3. 验证（线性扫描）。

具体见注释：

```cpp
#include<iostream>
#include<vector>
using namespace std;
int a[3005];
vector<long long> y;//存因数
int n;
int ck(int g){
	int cnt=0;
	int now=0;
	for(int j=1;j<=n;j++){
		now+=a[j];
		if(now==g){//如果累计的一段区间和与预期的一样，就计数变量加一
			cnt++;
			now=0;
		}
		else if(now>g){//肯定不合法
			return 0;
		}
	}
	return cnt;
}
int main(){
	int T;
	cin>>T;
	while(T--){
		y.clear();
		cin>>n;
		long long sum=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			sum+=a[i];//求和
		}
		for(long long i=1;i*i<=sum;i++){//O(sqrt(n))
			if(sum%i==0){
				y.push_back(i);
			}
		}
		int si=y.size();
		for(int i=si-1;i>=0;i--){//倒着来一遍
			y.push_back(sum/y[i]);
		}
		for(int i=0;i<y.size();i++){
			int g=y[i];
			int ans=ck(g);
			if(ans){//如果能合法分完
				cout<<n-sum/g<<'\n';//合并次数
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：Jorisy (赞：1)

这一题其实只要暴力求解。

如果要合并成几个相同的数，那么这个数必然是 $\sum_{i=1}^{n}a_i$ 的因数。

那么，我们只要用 $O(n\sqrt{sum})$（令 $sum=\sum_{i=1}^{n}a_i$）的时间去枚举因数，然后求出是否可行及所需步骤数即可。

AC Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int n,a[100005],sum,ans;

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		sum=0;
		ans=1e9;//多测注意初始值
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			sum+=a[i];//求和
		}
		if(sum==0)//特判
		{
			cout<<0<<endl;
			continue;
		}
		for(int i=1;i*i<=sum;i++)//每次枚举两个因数
		{
			if(sum%i) continue;
			int x=i,f=1,t=0;//枚举因数 i
			ll s=0;
			for(int j=1;j<=n;j++)
			{
				s+=a[j];
				if(s==x)//与目标数相同
				{
					t++;
					s=0;
				}
				else if(s>x)//不能合成数
				{
					f=0;
					break;
				}
			}
			if(f) ans=min(ans,n-t);//可行则求值，下同
			x=sum/i;//枚举因数 sum/i
			f=1;
			t=s=0;
			for(int j=1;j<=n;j++)
			{
				s+=a[j];
				if(s==x)
				{
					t++;
					s=0;
				}
				else if(s>x)
				{
					f=0;
					break;
				}
			}
			if(f) ans=min(ans,n-t);
		}
		cout<<ans<<endl;
	}
 	return 0;
}
```

---

## 作者：Natsume_Rin (赞：1)

题意：给出一个长度为 $n$ 的序列 $a_1,a_2,a_3\dots a_n$，用最少的合并次数，将所有数变为一个相同的数。

观察，我们定义一个变量 $sum=\sum_i a_i$。

那么最后的结果将所有的数字变为一个数字 $k$，必须满足 $k | sum$。

所以我们可以用 $O(n)$ 枚举一个数字 $sum/k$。以此，可以计算出 $k$ 的值。再用 $O(n)$ 检查是否合法，如果合法就更新答案，否则跳过。

总时间复杂度 $O(n^2)$。

代码：

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
int t;
int n;
const int MAXN = 3005;
int a[MAXN];
int sum;
int ans;
int cnt;
int now;
int main(){
        cin>>t;
        while(t--){
                sum=0;
                cin>>n;
                for(RI i=1;i<=n;++i){
                        cin>>a[i];
                        sum+=a[i];
                }
                ans=n;
                for(RI j=1;j<=n;++j) {
                        if(sum%j==0){
                                cnt=0;
                                now=0;
                                for(RI i=1;i<=n;++i){
                                        if(now==0) cnt--;
                                        now+=a[i];
                                        cnt++;
                                        if(now<sum/j) continue;
                                        if(now>sum/j){
                                                cnt=2147483647;
                                                break;
                                        }
                                        if(now==sum/j) now=0;
                                }
                                ans=min(ans,cnt);
                        }
                }
                cout<<ans<<endl;
        }
}

```

---

## 作者：PikachuQAQ (赞：0)

## Description

[Link](https://www.luogu.com.cn/problem/CF1462D)

## Solution

数学加模拟题。

这个题目看起来无从下手，实际上我们可以找规律。

手玩样例发现，合并的每个数一定是这几个数的和的因数，因为所有数合并起来也是和的因数，数的和也一定再数列最大数和它们的和之间，考虑拆解数列和的因数，再进行构造。

我们称一个数的合法因数为这个因数比当前数列小或相等，并且比数列中最大的数要大或相等。

对于合法的每个因数，设从 $a_i$ 到 $a_j$ 的和为 $totalsum$，$g_i$ 为数列，和的其中一个合法因数。

首先，先把 $a_{j+1}$ 的值加入 $totalsum$。

如果当前区间的和等于 $g_i$，说明合法的合并又多了一个，再把 $totalsum$ 归零，判断下一个区间和是否合法。

否则如果区间和比 $g_i$ 大，说明数列中的所有数不能被全部合并成 $g_i$，判断下一个因数能否被全部合并。

最后取所有情况中最小的 $n$ 减去合法合并段数即可。

对于每一组数据，最坏时间复杂度为 $O(\sqrt{sum} + n)$。

## Code

```cpp
// 2023/5/1 Accept__

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int kMaxN = 3007;

int t, n, a[kMaxN], maxn, sum, ans = 0x3f3f3f3f, gc[kMaxN], cnt, tots, j;
bool flag = 1;

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (cin >> t; t; t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i], maxn = max(a[i], maxn), sum += a[i];
        }
        for (int i = 1; i * i <= sum; i++) {
            (!(sum % i)) && ((i >= maxn) && (gc[cnt++] = i), (sum / i >= maxn) && (gc[cnt++] = sum / i));
        }
        sort(gc, gc + cnt);
        for (int i = 0, k = 0; i < cnt; i++) {
            for (j = tots = 0; j < n && flag; j++)  {
                tots += a[j], (tots == gc[i]) ? (tots = 0, k++) : ((tots > gc[i]) && (flag = 0));
            }
            (flag) && (ans = min(ans, n - k)), flag = 1, k = 0;
        }
        cout << ans << '\n', sum = cnt = maxn = 0, ans = 0x3f3f3f3f;
    }

    return 0;
}
```


---

## 作者：Zaku (赞：0)

这题跟P8183完全一致，但是数据范围水多了。。。
### 思路:
每次合并，数字个数就会 -1，那么最终的数字个数就是 $N-x$，并且最终合并完成后，每一堆都是 $sum/(N-x)$。
于是就可以枚举 $(N-x)$ 了。如果合并后数目大于 $sum/(N-x)$，跳出。
### 解法：
由题意可得，最终每一项的值（这里设为 $cnt$）一定是 $sum$ 的因数，所以遍历 $1-\sqrt{sum}$, 求出 $sum$ 的因数并加以判断即可。

判断方法：首先要能被分成大小为 $cnt$ 的若干堆，其次，分完的堆数要等于 $sum/cnt$ 才可以。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],n;
bool check(int cnt){//判断能否合并
	for(int i=0,sum=0;i<n;i++){
		sum+=a[i];//加上当前一堆
		if(sum>cnt)return false;//无解
		if(sum==cnt)sum=0;//当前这一段找到了，清空sum并枚举下一段
	}
	return true;
}
int main(){
	int T;cin>>T;
	while(T--){
		cin>>n;
		int sum=0;
		for(int i=0;i<n;i++){
			cin>>a[i];
			sum+=a[i];
		}
		for(int i=n;i;i--)
		if(sum%i==0&&check(sum/i)){//是sum的因数，并且判断成立
			cout<<n-i<<endl;//操作数就是n-堆数
			break;
		}
	}
	return 0;
}
```

---

