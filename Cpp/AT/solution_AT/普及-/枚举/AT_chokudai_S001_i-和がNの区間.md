# 和がNの区間

## 题目描述

[problemUrl]: https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_i

数列 $ a $ に含まれる連続した区間のうち、和が $ N $ になるものがいくつ存在するかを出力しなさい。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100,000 $

## 样例 #1

### 输入

```
5
3 1 5 4 2```

### 输出

```
1```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6```

### 输出

```
2```

## 样例 #3

### 输入

```
7
7 6 5 4 3 2 1```

### 输出

```
2```

## 样例 #4

### 输入

```
20
19 11 10 7 8 9 17 18 20 4 3 15 16 1 5 14 6 2 13 12```

### 输出

```
3```

# 题解

## 作者：伟大的王夫子 (赞：2)

先按照题意，读入 $n$, 再读入数组 $a$。

毕竟，这道题的难度在普及以下，正解必定是暴力。

那么，我们思路马上便有了。

枚举满足 $1 \le i \le n,i \le j \le n$ 的所有二元组 $(i, j)$，然后计算 $\sum_{k = i} ^ {j} a_k$,如果这个值等于 $n$ 那么就将答案加一

但是，这种算法的时间复杂度为 $O(n ^2)$，对于 $n \le 100000$ 的数据，必然会超时。

于是，我们观察一个性质。记 $s(i,j)$ 为 $i$ 到 $j$ 所有数之和，那么当 $i$ 不变时， 我们恒有 $s(i, j+1) > s(i, j)$。

所以说，第一层循环枚举 $i$，第二层枚举 $j$ 时，当和大于等于 $n$ 时，时间跳出下一层循环。

现在提供代码，供大家参考一下。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, a[100010], ans;
int main() {
	cin >> n;
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (register int i = 1; i <= n; ++i) {
		ll s = 0;
		for (register int j = i; j <= n; ++j) {
			s += a[j];
			if (s == n) {
				++ans;
				break;
			}
            if (s > n) break;
		}
	}
	cout << ans;
}
```

---

## 作者：Symbolize (赞：2)

# 思路
像这种区间和问题，一般都是前缀和。

首先输入 $n$ 和 $a$ 数组，定义一个 $s$ 数组，表示 $a$ 数组的前缀和。

然后二层暴力循环查找满足条件的区间，$l$ 从 $1$ 开始，$r$ 从 $l$ 当前的值开始。

当前区间和 $sum$ 的计算为 $s_r$ 与 $s_{l-1}$ 的差，即 $sum=s_r-s_{l-1}$。

接着只要找到一种满足条件的区间就让表示答案数的 $ans$ 加一即可。

最后输出 $ans$。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1e5+10;
using namespace std;
int n,a[N],s[N],ans;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) 
	{
		cin>>a[i];
		s[i]=s[i-1]+a[i];//前缀和
	}
	for(int l=1;l<=n;l++)
	{
		for(int r=l;r<=n;r++)
		{
			int sum=s[r]-s[l-1];
			if(sum==n) ++ans;//记录答案个数
			if(sum>n) break;//小优化
		}
	}
	cout<<ans<<endl;//输出答案
	return 0;//收尾
} 
```

---

## 作者：tZEROちゃん (赞：1)

### Solution

**前缀和。**

如果我们想求一个有 $n$ 个元素的序列 $a$ 从 $a_1$ 加到 $a_k (1\le k \le n)$ 的值，我们可以写一个 $1 \sim k$ 的循环，但是我们可以优化。

显然，我们可以使用前缀和。

设前缀合数组 $s$，$s_i$ 表示 $a_1 + a_2 + \cdots + a_{i - 1} + a_i$，那么 $a$ 的前缀和就是：

- $s_1 = a_1$。
- $s_2 = a_1 + a_2$。
- $s_3 = a_1 + a_2 + a_3$。
- $\cdots$
- $s_n = a_1 + a_2 + \cdots + a_n$。

那么我们可以发现：

- $s_1 = a_1$。
- $s_2 = s_1 + a_2$。
- $s_3 = s_2 + a_3$。
- $\cdots$
- $s_n = s_{n-1} + a_n$。

所以就有：

$$ s_i = s_{i - 1} + a_i $$

最终，$s_k$ 即为答案。

那么显然，如果要求 $[l, r]$ 这个区间和，我们发现如果只是 $s_r$ 的话，会多出 $s_{l-1}$ 的部分，将其减去即可。

于是你就可以用枚举左右端点 + 前缀和 + 一些优化（即当 $s_r - s_{l-1} > n$ 时，就可以结束一层循环，原因很简单，请自行思考）。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[114514];
int s[114514];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    s[i] = s[i - 1] + a[i];
  }
  int cnt = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      if (s[j] - s[i - 1] == n) {
        cnt++;
      } else if (s[j] - s[i - 1] > n) {
        break;
      }
    }
  } // i 和 j 分别对应分析中的 l 和 r。
  cout << cnt;
  return 0;
}
```

---

## 作者：Kevin_Zhen (赞：1)

## 题目大意
给你一个序列，询问这个序列中有多少对端点 $l$ 和 $r$，满足这两个端点之间的数的和为 $n$。
## 解题过程
**思路一：** 我会抱莉！  
第一层循环左端点 $l$，第二层循环右端点 $r$，第三层循环求区间和。  
时间复杂度 $O(n^{3})$。  
**CODE**
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int n, ans = 0;
int a[100010];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			int sum = 0;
			for (int k = i; k <= j; ++k) {
				sum += a[k];
			}
			if (sum == n) ++ans;
		}
	}
	printf("%d\n", ans);
	return 0;
}
```
[取得了 0pts 的好成绩。](https://www.luogu.com.cn/record/32034011)


------------

**思路二：** 我会优化！  
第一层循环左端点 $l$，第二层从 $l$ 处开始循环并累加区间和，直到 $sum$ 的值大于等于 $n$ 为止。  
时间复杂度 $O(n^{2})$  
**CODE**
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int n, ans = 0;
int a[100010];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) {
		int sum = 0;
		for (int j = i; j <= n; ++j) {
			sum += a[j];
			if (sum >= n) {
				if (sum == n) ++ans;
				break;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
```
[记录详情。](https://www.luogu.com.cn/record/32034269)


------------

**思路三：** 我会前缀和！  
一个前缀和数组 $sum$。第一层循环左端点 $l$，第二层循环右端点 $r$，如果区间和等于 $n$，记录答案即可。  
**注意：** 这里需要有一步优化，[不加会TLE](https://www.luogu.com.cn/record/32035203)。如果区间和大于 $n$，则循环不必继续，跳出当前循环即可。代码实现如下。
```cpp
if (sum[j] - sum[i] > n) break;
```
**CODE**
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int n, ans = 0;
int a[100010];
int sum[100010] = { 0 };

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) sum[i] = a[i] + sum[i - 1];
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (sum[j] - sum[i] == n) ++ans;
			if (sum[j] - sum[i] > n) break;
		}
	}
	printf("%d\n", ans);
	return 0;
}
```
[记录详情。](https://www.luogu.com.cn/record/32035302)
## 感谢观赏！

---

## 作者：Ciyang (赞：1)

### 我刚看这个题以为是数学题,然后用暴力枚举就过了，那就水一篇题解
### 我的方法是暴力,做这种题(除了我)应该都是大佬,我就直接放代码
```cpp
#include <iostream>
#include <stdio.h>
using namespace std;
int n, t, a[100001], th;
int main() {
	cin >> n;
	for(int i= 0; i < n; i++) {
		cin >> a[i];
	}
	for(int i= 0; i < n; i++) {
    //头指针i,指向枚举的区间第一个元素
		th= 0;
		for(int j= i; j < n; j++) {
        //尾指针j,指向枚举的区间最后一个元素
			th+= a[j];
			if(th == n) {
				++t;
				break;
			}
			if(th > n) break;
		}
	}
	cout << t << endl;
	return 0;
}
```
### 没错就是这么简单,难度入门~普及-   
### 思路:  
### 就是设一个头指针i,指向区间第一个元素,j从i开始循环加1,每次加a(j)  
### 直到和为n,就让计数器增加,或者和已经超过n就直接break.然后头指针i增加   
### 最后直接输出   

---

## 作者：AirQwQ (赞：0)

## 入手


- 看到区间和，马上就想到了前缀和。

- 因为 $ N \le 100000 $ 只需要用暴力加剪枝即可。


## 前缀和

- 基本上就是板子题，不会的移步至[B3612](https://www.luogu.com.cn/problem/B3612)。

- 因为需要求**所有**区间，时间复杂度 $O(n^2)$，所以这里也需要剪枝。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[6666666];
inline int read(){
   register int s=0,w=1;
   register char ch=getchar(); 
   while(ch<'0'||ch>'9'){
        if(ch=='-'){
            w=-1;
            ch=getchar();
        }
   }
   while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';
        ch=getchar();
   }
   return s*w;
}
int main() {
	int n=read(),ans=0;
	for(int i=1;i<=n;i++) {
		int num=read();
		a[i]=a[i-1]+num;
	}
	for(int i=0;i<n;i++)
		for(int j=i+1;j<=n;j++){
			if(a[j]-a[i]==n){
				ans++;
				break;
			}
            if(a[j]-a[i]>n}
                break;
        }//往后j越大，和越大，一定会大于n。
	cout<<ans<<'\n';
	return 0;
}	
		
```

## 暴力

- 枚举首位指针再循环求和，时间复杂度 $ O(n^3) $，肯定超时。

- 同样枚举首位指针，每次循环加 $a_j$。

- 同样要剪枝，与前缀和几乎无差别。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
inline int read(){
   register int s=0,w=1;
   register char ch=getchar(); 
   while(ch<'0'||ch>'9'){
        if(ch=='-'){
            w=-1;
            ch=getchar();
        }
   }
   while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';
        ch=getchar();
   }
   return s*w;
}
int main(){
    int n=read(),ans=0;
    for(int i=1;i<=n;i++)
        a[i]=read();
    for(int i=1;i<=n;i++){
        long long sum=0;
        for(int j=i;j<=n;j++){
            sum+=a[j];
            if(sum==n) 
                ans++;
            if(sum>n)
                break;
        }
    }
    cout<<ans<<'\n';
	return 0;
}
```
~~侥幸最优解，欢迎各路神仙打破。~~

---

## 作者：Limury (赞：0)

### 题意

给定 $n$ 个数，求有多少个子区间满足区间和为 $n$ 。

### 思路

首先看数据范围 $1 \le n \le 100,000$ ，很明显两重循环 $O(n^2)$ 及以上的算法是过不了的。让我们思考一下，对于每一个左端点 $l$ ，我们可以定义变量 $sum$ 为 $0$ ，然后从 $l$ 到 $n$ 枚举右端点，将此时的值加给 $sum$ ，当 $sum$ 等于 $n$ 时，将答案加一。当答案大于等于 $n$ 时，因为越往后加值越大，所以可以直接跳出。最后输出即可。

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=100005;
int n,ans;
int a[maxn];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=i;j<=n;j++){
			sum+=a[j];
			if(sum>=n){
				if(sum==n){
					ans++;
				}
				j=n+1;
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：happybob (赞：0)

前缀和好题，但不知道为什么标签是 $\color{blue} \text{数论。}$

然后将前缀和加进去最后暴力枚举一下。但这里注意，暴力时如果已经超过了`n`那么就得终止循环，不然你会得到`TLE`。

代码如下:

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<long long> sum(100005); //前缀和数组

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0); // 前2为读入输出优化，也可以用快读
    int n;
    cin >> n; // 读入数字的个数
    for(register int i = 1; i <= n; i++)
    {
        long long x;
        cin >> x; // 读入每个数，注意不要读入数组中
        sum[i] = sum[i - 1] + x; // 前缀和加入这个数
    }
    int cnt = 0; // 定义统计答案个数的变量
    for(register int i = 1; i <= n; i++)
    {
        if(sum[i] == n) {cnt++; continue;}
        for(register int j = i; j <= n; j++)
        {
            if(sum[j] - sum[i] == n) cnt++;
            else if(sum[j] - sum[i] > n) break; // 这里一定要加！不然会T
        }
    }
    cout << cnt << endl;
    return 0;
}
```


---

## 作者：a2920353120 (赞：0)

## $$\color{gold}\text{题解 AT2828 【和がNの区間】}$$
### 比较简单的一道题

> 思路如下


```暴力 + 前缀和```


详解见代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int N = 100009;//数组大小
int a[N], f[N];//a存放原数组,f为前缀和数组

int main() {
	int n, i, j, ans = 0;//ans记录答案个数
	cin >> n;
	for(i = 1; i <= n; i++) {
		cin >> a[i];
		f[i] = f[i - 1] + a[i];//前缀和
	}
	for(i = 0; i < n; i++) {//注意要从0开始枚举左端点
		for(j = i + 1; j <= n; j++) {//从左端点+1开始枚举又端点
			if(f[j] - f[i] == n) {
				ans++;//找到答案
				break;
			}
			if(f[j] - f[i] > n) break;
            //注意两个break的作用:可行性剪枝,不加会T
            //如果当前差值已经大于n了那么一定不会存在j1,使f[j1]-f[i] == n
		}
	}
	cout << ans << endl;//输出答案
	return 0;
}
		
```

---

