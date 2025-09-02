# Fun with Even Subarrays

## 题目描述

You are given an array $ a $ of $ n $ elements. You can apply the following operation to it any number of times:

- Select some subarray from $ a $ of even size $ 2k $ that begins at position $ l $ ( $ 1\le l \le l+2\cdot{k}-1\le n $ , $ k \ge 1 $ ) and for each $ i $ between $ 0 $ and $ k-1 $ (inclusive), assign the value $ a_{l+k+i} $ to $ a_{l+i} $ .

For example, if $ a = [2, 1, 3, 4, 5, 3] $ , then choose $ l = 1 $ and $ k = 2 $ , applying this operation the array will become $ a = [3, 4, 3, 4, 5, 3] $ .

Find the minimum number of operations (possibly zero) needed to make all the elements of the array equal.

## 说明/提示

In the first test, all elements are equal, therefore no operations are needed.

In the second test, you can apply one operation with $ k=1 $ and $ l=1 $ , set $ a_1 := a_2 $ , and the array becomes $ [1, 1] $ with $ 1 $ operation.

In the third test, you can apply one operation with $ k=1 $ and $ l=4 $ , set $ a_4 := a_5 $ , and the array becomes $ [4, 4, 4, 4, 4] $ .

In the fourth test, you can apply one operation with $ k=1 $ and $ l=3 $ , set $ a_3 := a_4 $ , and the array becomes $ [4, 2, 3, 3] $ , then you can apply another operation with $ k=2 $ and $ l=1 $ , set $ a_1 := a_3 $ , $ a_2 := a_4 $ , and the array becomes $ [3, 3, 3, 3] $ .

In the fifth test, there is only one element, therefore no operations are needed.

## 样例 #1

### 输入

```
5
3
1 1 1
2
2 1
5
4 4 4 2 4
4
4 2 1 3
1
1```

### 输出

```
0
1
1
2
0```

# 题解

## 作者：Accepted_Error (赞：2)

[传送门](https://www.luogu.com.cn/problem/solution/CF1631B)

## 题目分析
根据题意可得最终我们得到的数组中的值一定等于原数组中最后一个数的值，因此我们可以先找出 **数组末端** 最长的子数组，在用这个子数组去更新前面的数，这样便可以使操作次数最小。
## AC Code
```cpp
#include<iostream>
#include<cstdio>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#include<utility>
#include<cmath>
#include<cstring>
#include<string>
#include<map>
#include<set>
#include<cstdlib>
#define ll long long
using namespace std;
const int N=2e5+10;
int a[N];
int t,n,tmp,cnt;
int main()
{
    cin>>t;
    while(t--)
	{
		cnt=0;
        cin>>n;
        tmp=n-1;
        for(int i=1;i<=n;i++)
        {
        	cin>>a[i];
		}
        while(tmp>0)
		{
            if(a[tmp]!=a[tmp+1])
			{
                cnt++;
                tmp=tmp+tmp-n;
                if(tmp<0) break;
                a[tmp+1]=a[n];
            }
			else tmp--;
        }
        cout<<cnt<<endl;
    }
    return 0;
}

```

---

## 作者：Morgen_Kornblume (赞：1)

由题意，可以得知这样一个性质：最后的数组里所有的数一定是原先数组里最后一个数（因为只能从后向前复制）。

所以我们每次将数组里从后往前最长的连续一段（值都等于最后一个数），向前复制，直到整个数组中所有数相同。即可得到最优答案。

```cpp
#include<bits/stdc++.h>
using namespace std;

int T;

int n;

const int maxn=200010;

int a[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	
	cin>>T;
	
	while(T--){
		
		cin>>n;
		
		for(int i=1;i<=n;i++)cin>>a[i];
		
		int ans=0;
		for(int i=n;i>=1;){
			while(a[i]==a[n]){
				i--;
			}
			if(!i)break;
			ans++;
			for(int j=0;j<n-i&&i-j>0;j++){
				a[i-j]=a[n];
			}
		}
		
		cout<<ans<<endl;
	}
	
	return 0;
}
```


---

## 作者：FiraCode (赞：0)

## 题解思路：
有一个很显然的性质：

最后相同的元素一定是 $a_n$。

所以我们每次要尽可能多的去贴数字到前面。

比如：

$4\ 4\ 2\ 4\ 4$ 那么我们一定会把 $4\ 4$ 移过去，因为这样变成相同的元素才能尽可能的多。

## AC CODE:
```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int N = 200010;
int a[N];
int main() {
    int T;
    cin >> T;
    while (T --) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++ i)
            cin >> a[i];
        int p = n - 1 , ans = 0;
        while (p > 0) {
            if (a[p] != a[p + 1]) {
                ans ++;
                p -= n - p;
                if (p < 0)
                    break;
                a[p + 1] = a[n];//把元素复制过来
            }else -- p;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Mr__Cat (赞：0)

### 题目思路

根据题意描述可知，最后数组里的所有数绝对是原数组最后一个数。

那么让他们都变成最后一个数就行。

我们要从后往前扫，当遇到不一样的就取不超过当前位置的等于后缀相同数的 $k$。

不过这道题要把所有数都进行修改，所以还要考虑一下复杂度。

### 题目代码

```cpp
#include<bitsdc++.h>
using namespace std;
int n,T,a[200011],s;
void work(int x,int l)
{
  	for(int i=0;i<l;i++)
    {
		if(x-i<=0)return;
		a[x-i]=a[n];
	}
	return;
}
int main()
{
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		s=0;
		for(int i=n-1;i>=1;i--)
        {
			if(a[i]!=a[n])s++,work(i,n-i);
		}
		cout<<s<<endl;
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

首先发现最后一个数无论做什么操作都无法更改，所以最后一定是序列所有数都等于最后一个数。

那么直接从后往前扫描，每当遇到不一样的就取不超过当前位置的等于后缀相同数的 $k$ 作为操作数。

由于一个数都至多被修改一次以及查询一次，所以总复杂度 $O(n)$。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int n,T,a[200005],ans;
void work(int now,int len){
	for(int i=0;i<len;i++){
		if(now-i<=0)return;
		a[now-i]=a[n];
	}
	return;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		ans=0;
		for(int i=n-1;i>=1;i--){
			if(a[i]!=a[n])ans++,work(i,n-i);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

首先，寻找一个**位于数组末端的**所有数据相同的子数组，且使这个子数组尽量长。

设子数组的长度为 $l$。

若 $2\times l\le n$，则将题中的 $i$ 设为 $n-2\times l+1$，将题中的 $k$ 设为 $l$，执行操作。

否则，将题中的 $i$ 设为 $1$，将题中的 $k$ 设为 $\left \lfloor n\div2 \right \rfloor $，执行操作。显然，这次操作执行完毕后，数组的数据就全部一样了。

重复执行以上操作，即可。

### 二、完整代码

```
#include<cstdio>
using namespace std;
int t;
int n;
int a[200005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		int ans=0;
		if(n==1)
		{
			printf("0\n");
			continue;
		}
		for(int i=n-1;i>=1;i--)
		{
			if(a[i]!=a[i+1])
			{
				ans++;
				int l=n-i;
				if(l<=i)
				{
					for(int j=i+1;j<=n;j++)
					{
						a[j-l]=a[j];
					}
				}
				else
				{
					for(int j=1;j<=i;j++)
					{
						a[j]=a[j+i];
					}
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：wzy2021 (赞：0)

因为题意是由后面复制到前面，那我们就从后往前考虑，

假设最后数组中全是 $x$，

因为最后一个数没有其他数能复制到它，所以 $x = a[n]$，

那我们做如下操作：

每次我们就找到末尾最长的全为 $a[n]$ 的串，设其长度为 $k$，

然后选 $n - 2k + 1 \sim n$，即将 $n - k + 1 \sim n$ 复制到 $n - 2k + 1 \sim n - k$，

由于 $n - k + 1 \sim n$ 全是 $a[n]$，通过刚才的操作，$n - 2k + 1 \sim n$ 也全是 $a[n]$，

可以发现末尾最长段一定是单调递增的，所以用一个数存一下刘好了，

那么我们不断进行以上操作，直到满足要求位置。

上述情况中先不考虑越界问题。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int maxn = 2e5 + 10;
int a[maxn], sum[maxn]; 

int main() {
	int T; scanf ("%d", &T);
	while (T --) {
		int n; scanf ("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf ("%d", &a[i]);
		}
		a[0] = 1e9;
		int ans = 0, res = 1;
		while (res < n) {
			while (a[n - res] == a[n]) res ++;
			if (res == n) break; // 防止越界
			res = 2 * res;
			ans ++;
		}
		printf ("%d\n", ans);
	}
	return 0;
}
```


---

## 作者：IvanZhang2009 (赞：0)

## 题意
给定长度为 $n$ 的数组 $a$，可以选择一段连续子串**向前**复制,使得数组中所有数相等。求最少操作次数。（题意仅供回忆原题，具体请看[原题](https://www.luogu.com.cn/problem/CF1631B)）

## 解法
由于只能向前复制，那么要使数组中所有数相等，只能让它们都变成最后一个数。考虑使用指针模拟复制操作，每次尽可能从后往前选择相同的数向前复制。

需要注意的是进行操作后要再次往前找相同的数再进行操作。

## 代码
为了方便，本蒟蒻将原数组颠倒过来从前往后操作，思考难度更小。具体细节见注释。
```cpp
#define REP(i,a,n) for(int i=(a);i<(n);i++)
...
int n;
int a[200005];
int ans;
void Main() {
	cin>>n;
	ans=0;
	REP(i,0,n)cin>>a[n-i-1]; //反过来输入。注意i从0开始。
	int x=0;
	for(;x<n-1&&a[1+x]==a[0];x++);  //第一次找最后一个连续的与第一个数相同的数
	while(x<n-1){
		x=x*2+1;
//x下标从0开始，复制（*2）使注意先还原成起始下标为1的数，操作后再还原：x=(x+1)*2-1=x*2+1
		ans++;
		while(x<n-1&&a[1+x]==a[0])x++;
	}
	cout<<ans<<endl;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 题意

有一个长度为 $n$ 的数组 $a$。

现在，你可以进行一些操作：

分别决定 $l$ 和 $k$ 的值（要求 $l$ 和 $k$ 为正整数），满足 $1\le l\le l+k\times2-1\le n$。

然后，将 $a[l+k]$ 到 $a[l+k\times2-1]$ 的值，赋给 $a[l]$ 到 $a[l+k-1]$。

求出，使得 $a$ 里所有元素相等的最少操作次数。

### 2 思路

很简单，我们可以优先处理后面的，并且每次处理争取 $k$ 更大。

我们可以设 $p$ 为能够满足 $a[p]$ 到 $a[n]$ 都相等的最小值，那么，$k$ 就为 $n-p+1$，$l$ 就设为 $p-k$，进行操作。

这样可以保证次数最小。

### 3 代码与记录

代码里没有进行真正的操作，只是改一改 $p$（代码里为 $i$）。

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 200000
int t;
int n;
int a[max_n+2];
int ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1631B_1.in","r",stdin);
	freopen("CF1631B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
		}
		ans=0;
		for(int i=n-1;i>=1;){
			if(a[i]!=a[n]){
				i=i-(n-i);
				++ans;
			}
			else --i;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/68455297)

By **dengziyue**

---

