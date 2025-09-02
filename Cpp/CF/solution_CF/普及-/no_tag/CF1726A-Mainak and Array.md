# Mainak and Array

## 题目描述

### 题目大意

给定一个长度为 $n$ 的数组 $a$，可以选定**一个**区间 $[l, \; r]$ 进行**恰好一次**操作，求操作后最大的 $a_n - a_1$。

操作方法：选定区间 $[l, \; r]$ 和旋转次数 $k$, 每次旋转为 $a_l = a_{l + 1}, \; a_{l + 1} = a_{l + 2}, \; \dots, \; a_{r - 1} = a_r, \; a_r = a_l$

## 样例 #1

### 输入

```
5
6
1 3 9 11 5 7
1
20
3
9 99 999
4
2 1 8 1
3
2 1 5```

### 输出

```
10
0
990
7
4```

# 题解

## 作者：ran_qwq (赞：3)

注意到，每个数列真正有用的使得 $a_n-a_1$ 最大的操作方法只有 $4$ 种：

1. 选择任意区间 $[l,r]$，并令 $k=r-l+1$，也就是不改变原来的数列，答案就是 $a_n-a_1$。

1. 选择区间 $[1,n-1]$，可以使 $[2,n-1]$ 的任意一个数移动到 $a_1$ 的位置与 $a_n$ 配对，使得 $a_n-a_1$ 最大，答案为 $\max_{i=2}^{n-1}a_n-a_i$。

1. 选择区间 $[2,n]$，可以使 $[2,n-1]$ 的任意一个数移动到 $a_n$ 的位置与 $a_1$ 配对，使得 $a_n-a_1$ 最大，答案为 $\max_{i=2}^{n-1}a_i-a_1$。

1. 选择区间 $[1,n]$，数列每相邻两个数都可以左边的到 $a_n$ 的位置，右边的到 $a_1$ 的位置，答案为 $max_{i=1}^{n-1}a_i-a_{i+1}$。

三种情况取最大值即可。

```cpp
#include<iostream>
using namespace std;
int T,n,a[2022];
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		int ans=0;
		for(int i=2;i<n;i++)
			ans=max(ans,a[n]-a[i]);
		for(int i=2;i<n;i++)
			ans=max(ans,a[i]-a[1]);
		for(int i=1;i<n;i++)
			ans=max(ans,a[i]-a[i+1]);
		ans=max(ans,a[n]-a[1]);
		cout<<ans<<endl;
	}
}
```


---

## 作者：abensyl (赞：1)

当时比赛时并没有打，但是赛后和大佬 [xzy090626](https://www.luogu.com.cn/user/562119) 讨论了好久（~~最后骂起来了~~）。

## 思路

明摆着这题只是一个 greedy。

分三种情况求最值：

1. 我们对 $(1,n]$ 的区间进行操作，此时我们当然想让其中的最大值跑到最后一位，令最大的元素的下标为 $maxi$，这样的话就是 $a[maxi]-[1]$。

2. 我们对 $[1,n)$ 的区间进行操作，此时我们当然想让其中的最小值跑到第一位，令最小的元素的下标为 $mini$，这样的话就是 $a[n]-[mini]$。

~~不得不说的是，很多人只想到了前两种情况。~~

3. 讲这个之前，在 $k$ 此操作后，哪样的数可以排在序列头和序列尾上？

- 不难发现，当两个数分别为 $a[i]$ 和 $a[i+1]$ 时，在经历了 $k$ 此操作后，一定可以在序列头和尾上。

所以我们第三种情况就出来了。

- 便利整个序列，找出 $a[i]-a[i+1]$ 的最大值即可。

然后对以上三种情况的值求最大值即可得到正确答案。

## 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int ans = 0;
        for (int i = 0; i < n - 1; i++) {
            ans = max(ans, a[i] - a[i + 1]);
        }
        for (int i = 1; i < n; i++) {
            ans = max(ans, a[i] - a[0]);
        }
        for (int i = 0; i < n - 1; i++) {
            ans = max(ans, a[n - 1] - a[i]);
        }
        cout << ans << '\n';
    }
    return 0;
}
 ```              
 求管理员授予通过，求各位看官大佬点赞！

---

## 作者：_FJX_ (赞：0)

我们可以分三种情况讨论：

1. $l,r$ 取值为 $[1,n)$，对于任意一个 $i$，可以让结果变为 $a_i$ $-$ $a_1$。
2. $l,r$ 取值为 $(1,n]$，对于任意一个 $i$，可以让结果变为 $a_n$ $-$ $a_i$。
3. $l,r$ 取值为 $(1,n)$，对于任意一个 $i$，可以让结果变为 $a_i$ $-$ $a_{i+1}$。

_AC code:_

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[5005];
void work()
{
	int n;
	cin >> n;
	int ans = 0;
	for (int i = 1; i <= n; i ++)
	{
		cin >> a[i];
		ans = max(ans, a[i] - a[1]);//第一种情况 
	}
	for (int i = 1; i <= n; i ++)
	{
        ans = max(ans, a[n] - a[i]);//第二种情况 
    }
    a[n + 1] = a[1];
	for (int i = 1; i <= n; i ++)
	{
		ans = max(ans, a[i] - a[i + 1]);//第三种情况 
	}
	cout << ans << endl; 
}
int main(){
    ios_base::sync_with_stdio(false);
	cin.tie (0);
	cout.tie (0);
	int T;
	cin >> T;
	while (T --)
	{
		work();
	 } 
	return 0;
}

```


---

## 作者：luo_shen (赞：0)

**题意**  
给定长度为 $n$ 的数组 $a$，可以选择一个区间 $\begin{bmatrix}l,r\end{bmatrix}$ 并对其进行若干次如下操作：
- 令 $a_l = a_{l + 1}, \; a_{l + 1} = a_{l + 2}, \; \dots, \; a_{r - 1} = a_r, \; a_r = a_l$

求操作后 $a_n-a_1$ 的最大值。  
**解析**  
实质上，真正有效的 $l,r$ 的取值只有三种，$\begin{bmatrix}1,n-1\end{bmatrix}$，$\begin{bmatrix}2,n\end{bmatrix}$，$\begin{bmatrix}1,n\end{bmatrix}$。对于任何一个 $i$，第一种可以让结果变为 $a_n-a_i$，第二种可以让结果变为 $a_i-a_1$，第三种可以让结果变为 $a_i-a_{i+1}$。最终的结果只需在所有的结果里取最大值即可。  
**代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,a[2010];
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        int mx=0;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            mx=max(mx,a[i]-a[1]);//第二种
        }
        for(int i=1;i<=n;i++){
            mx=max(a[n]-a[i],mx);//第一种
        }
        a[n+1]=a[1];
        for(int i=1;i<=n;i++){
            mx=max(a[i]-a[i+1],mx);//第三种
        }
        cout<<mx<<endl;
    }
    return 0;
}
```

---

## 作者：cyhtxdy (赞：0)

## 题意：
使用题目中的操作，操作一次，最大化 $a_n-a_1$ 的值。

## 思路：
首先搞清楚题目中操作的本质，这个操作就是将一个环中的每个值变为前一个值。

对于一个区间中的一个位置，我们可以使该位置变为**这个区间中的任何数字**。

最大化 $a_n-a_1$，可以分为三种情况计算答案：

- 第一类：当 $a_1$ 为这个数组中的最小值时。

	那么就需要最大化 $a_n$，那么就把 $a_n$ 设为 $a_2$ 到 $a_n$ 中的最大值。
    
- 第二类：当 $a_n$ 为这个数组中的最大值时：

	那么就需要最小化 $a_1$，那么就把 $a_1$ 设为 $a_1$ 到 $a_{n-1}$ 中的最小值。
    
- 第三类：当 $a_1$ 既不是这个数组中的最小值，$a_n$ 也不是这个数组中的最大值时：
	
那么就可以枚举所有操作的 $a_n-a_1$，找出最大值。

## 代码：
```
#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 7;

int T, n, a[N];

int main () {
	cin >> T;
	while (T --) {
		cin >> n;
		for (int i = 1; i <= n; i ++) {
			cin >> a[i];
		}
		int ans = -1, p = -1;
		for (int i = 2; i <= n; i ++) {
			p = max (p, a[i]);
		}
		ans = max (ans, p - a[1]);//第一类 
		p = 10000;
		for (int i = 1; i < n; i ++) {
			p = min (p, a[i]);
		}
		ans = max (a[n] - p, ans);//第二类 
		int r = n, l = 1, t = n;
		while (t --) {
			ans = max (a[r] - a[l], ans);//第三类枚举 
			r ++;
			l ++;
			if (r > n) {
				r -= n;
			}
			if (l > n) {
				l -= n;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
```


---

## 作者：Abilene (赞：0)

总得来说是一条比较简单的思维题吧。

总共会有三种情况

1.最小值就是第一位  
这个情况下一定可以保证有一种操作使得最后一位是最大值（例如顺次将最大值移到最后），故直接输出最大值减去最小值即可

2.最大值就是最后一位  
同理第一种情况，一定可以保证能将最小值调整至第一位，直接输出最大值减最小值


3.两种情况均不符合  
那么最大值会在相邻两位之差（前-后）、最大值减第一位，最后一位减最小值中出现，比较三者输出最大的即可

**附上赛时AC代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2070;
int n,a[maxn],t;
int minn=1007,maxx=-1;
int tmp=-1;

int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            minn=min(minn,a[i]);
            maxx=max(maxx,a[i]);
        }
        for(int i=1;i<=n-1;i++)
        {
            tmp=max(tmp,a[i]-a[i+1]);
        }
        tmp=max(tmp,a[n]-a[1]);
        if(minn==a[1])
        {
            cout<<maxx-minn<<endl;
            tmp=-1,minn=0x3f3f3f,maxx=-1;//注意多测清空
            continue;
        }
        if(maxx==a[n])
        {
            cout<<maxx-minn<<endl;
            tmp=-1,minn=0x3f3f3f,maxx=-1;
            continue;
        }
        int i,j;
        i=a[n]-minn;
        j=maxx-a[1];
        i=max(i,j);
        tmp=max(i,tmp);
        cout<<tmp<<endl;
        tmp=-1,minn=0x3f3f3f,maxx=-1;
    }
    return 0;
}
```
完结撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。

---

## 作者：Zigh_Wang (赞：0)

推荐[博客](https://blog.csdn.net/YunYuanWang/article/details/126757566?spm=1001.2014.3001.5501)内食用哦

# 题面

> ### 题目大意
> 
> 给定一个长度为 $n$ 的数组 $a$，可以选定**一个**区间 $[l, \; r]$ 进行**恰好一次**操作，求操作后最大的 $a_n - a_1$。
> 
> 操作方法：选定区间 $[l, \; r]$ 和旋转次数 $k$, 每次旋转为 $a_l = a_{l + 1}, \; a_{l + 1}  = a_{l + 2}, \; \dots, \; a_{r - 1} = a_r, \; a_r = a_l$
> 
> ### 输入格式
> 
> 第一行一个整数 $T \; (1 \leqslant T \leqslant 50)$，表示测试样例组数。
> 
> 对于每组测试样例，第一行为一个整数 $n \; (1 \leqslant n \leqslant 2000)$ 表示数组长度。
> 
> 接下来的一行含有 $n$ 个整数 $a_i \; (1 \leqslant a_i \leqslant 999)$，表示该数组。
> 
> 数据保证 $\sum n \leqslant 2000$。
> 
> ### 输出格式
> 
> 对于每组测试样例包含一行一个整数，表示最大的 $a_n - a_1$。
> 
> $Translated \; by \; Zigh$

# 分析
根据题面，我们不难发现有效的操作只有 $3$ 种 $[1,  \; n], [2, \; n], [1, \; n - 1]$。因为 $l \geqslant 2 \; \&\& \;  r \leqslant n - 1$ 的操作一定是无效的，因为这样的操作显然不会影响答案。

对于 $[2, \; n]$ 这样的操作不难发现答案是 $\max_{i = 2}^{n} \{a_i\} -a_1$，$[1, n - 1]$ 的同理为 $a_n - \min_{i = 1}^{n - 1} \{a_i\}$。

对于 $[1, \; n]$ 的操作，我们可以发现当原序列中的 $a_i$ 作为结尾时，作为开头的一定是在原序列中的 $a_{i + 1}$。特别的，当 $i = n$ 时开头应为 $a_1$。我们只需要取出最大的 $a_i - a_{i + 1}$ 即可。( 千万不要以为只用找这里面的最大数及它对应的开头 和 里面的最小数及它对应的结尾就行了，别问我怎么知道的，问就是不知道)。

# 代码
```cpp
//省略快读和头文件
int T;
int n;
int a[MAXN];

int main()
{
	T = inpt();
	while(T--) {
		n = inpt();
		for(int i = 1; i <= n; i++)
			a[i] = inpt();
			
		int max_suf = -1e5, min_pre = 1e5;
		int tmp = -1e5;
		for(int i = 1; i <= n; i++) {
			if(i != 1) {
				max_suf = max(max_suf, a[i]);
			}
			if(i != n) {
				min_pre = min(min_pre, a[i]);
			}
			
			tmp = max(tmp, a[i] - a[i + 1 > n ? 1 : i + 1]);
		}
		
		int ans = max(a[n] - min_pre, max_suf - a[1]);
		ans = max(ans, tmp);
		
		printf("%d\n", ans);
	}

 	return 0;
}
```

最后来猜猜题目翻译里的 $Zigh$ 是谁呢Qwq。

---

