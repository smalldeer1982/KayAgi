# Lost Array

## 题目描述

Bajtek, known for his unusual gifts, recently got an integer array $ x_0, x_1, \ldots, x_{k-1} $ .

Unfortunately, after a huge array-party with his extraordinary friends, he realized that he'd lost it. After hours spent on searching for a new toy, Bajtek found on the arrays producer's website another array $ a $ of length $ n + 1 $ . As a formal description of $ a $ says, $ a_0 = 0 $ and for all other $ i $ ( $ 1 \le i \le n $ ) $ a_i = x_{(i-1)\bmod k} + a_{i-1} $ , where $ p \bmod q $ denotes the remainder of division $ p $ by $ q $ .

For example, if the $ x = [1, 2, 3] $ and $ n = 5 $ , then:

- $ a_0 = 0 $ ,
- $ a_1 = x_{0\bmod 3}+a_0=x_0+0=1 $ ,
- $ a_2 = x_{1\bmod 3}+a_1=x_1+1=3 $ ,
- $ a_3 = x_{2\bmod 3}+a_2=x_2+3=6 $ ,
- $ a_4 = x_{3\bmod 3}+a_3=x_0+6=7 $ ,
- $ a_5 = x_{4\bmod 3}+a_4=x_1+7=9 $ .

So, if the $ x = [1, 2, 3] $ and $ n = 5 $ , then $ a = [0, 1, 3, 6, 7, 9] $ .

Now the boy hopes that he will be able to restore $ x $ from $ a $ ! Knowing that $ 1 \le k \le n $ , help him and find all possible values of $ k $ — possible lengths of the lost array.

## 说明/提示

In the first example, any $ k $ is suitable, since $ a $ is an arithmetic progression.

Possible arrays $ x $ :

- $ [1] $
- $ [1, 1] $
- $ [1, 1, 1] $
- $ [1, 1, 1, 1] $
- $ [1, 1, 1, 1, 1] $

In the second example, Bajtek's array can have three or five elements.

Possible arrays $ x $ :

- $ [1, 2, 2] $
- $ [1, 2, 2, 1, 2] $

For example, $ k = 4 $ is bad, since it leads to $ 6 + x_0 = 8 $ and $ 0 + x_0 = 1 $ , which is an obvious contradiction.

In the third example, only $ k = n $ is good.

Array $ [1, 4, -2] $ satisfies the requirements.

Note that $ x_i $ may be negative.

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
5
1 2 3 4 5 ```

## 样例 #2

### 输入

```
5
1 3 5 6 8
```

### 输出

```
2
3 5 ```

## 样例 #3

### 输入

```
3
1 5 3
```

### 输出

```
1
3 ```

# 题解

## 作者：Digital_Sunrise (赞：0)

## CF1043B题解

[CF1043题解合集](https://www.luogu.com.cn/blog/yl2330/I-Love-YR-Forever)

[Markdonw源代码](https://yhwh-group.coding.net/public/codingwiki/files/git/files/master/blog/CF1043/B.Markdown)

Update 21.11.17 更正博客地址

### 题意简述

给出 $n$ 个数以及数组 $a$，要求出 $x$ 数组的长度，并输出 $x$ 数组。

其中满足 $a_i = x_{(i - 1)\,\bmod\,k} + a_{i-1}$ 。

### 思路

如果不考虑 $a_i = x_{(i - 1)\,\bmod\,k} + a_{i-1}$ 中的 $\bmod \, k$ ，

$x$ 就是单纯的对于 $a$ 的差分数组。

所以我们先把 $x$ 数组全用对于 $a$ 的差分数组填充，然后筛掉不符合条件啊的 $x_i(1 \le i \le n)$ 。

至于怎么筛掉，检查一下是否 $x$ 数组每 $k$ 个值都相同（因为 $\bmod k$ ）。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 5;

int n,cnt;
int a[maxn],x[maxn];
int ans[maxn];

bool check(int i,int k)
{
	int pos = i;
	int num = x[i];
	while(pos <= n)
    {
		if(x[pos] != x[i])
            return 0;
		pos += k;
	}
	return 1;
}

int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >>  a[i];
	for(int i = 1;i <= n;i++)
		x[i] = a[i] - a[i - 1];
	for(int k = 1;k <= n;k++)
    {
		for(int i = 1;i <= k;i++)
			if(!check(i,k))
				goto Next;
        ans[++cnt] = k;
        Next:;
	}
	cout << cnt << endl;
	for(int i = 1; i <= cnt; i++)
		cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：gogoduan (赞：0)

这道题可以观察到x数组是a数组的相邻两项差。
然后我们只需要暴力枚举k，看是否每隔k个都一样就可以判断了。
代码如下：
```cpp
#include<bits/stdc++.h>
#define MAXN 1005
using namespace std;
int n;
int a[MAXN];
int x[MAXN];
int cnt;
int ans[MAXN];
bool check(int i,int k){
	int pos=i;
	int num=x[i];
	while(pos<=n){
		if(x[pos]!=x[i]) return 0;
		pos+=k;
	}
	return 1;
}
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=1; i<=n; i++){
		x[i]=a[i]-a[i-1];
	}
	
	for(int k=1; k<=n; k++){
		bool flag=0;
		for(int i=1; i<=k; i++){
			if(!check(i,k)){
				flag=1;
				break;
			}
		}
		if(flag==0) ans[++cnt]=k;
	}
	printf("%d\n",cnt);
	for(int i=1; i<=cnt; i++){
		printf("%d ",ans[i]);
	}
	return 0;
}
```

---

## 作者：liuyz11 (赞：0)

## 广告：[这场比赛题解的原地址](https://www.cnblogs.com/nblyz2003/p/9868480.html)

## 这题是给你个数组a，长度为n，满足![](http://images.cnblogs.com/cnblogs_com/nblyz2003/1329739/o_jietu2.jpg)（k是x的长度）。当k = 3， x = {1, 2, 3}, n = 5时a如下图。
![](http://images.cnblogs.com/cnblogs_com/nblyz2003/1329739/o_jietu.jpg)
## 让你求所有x数组的方案数和，以及每种方案的长度k（从大到小）。

## 这题看上去很麻烦，其实很简单。只要求出他们相邻的差，就是一种x的方案。另外的其他几个方案就是由这串差的循环节组成（为什么？自己试试就知道了）。

## 然而我找循环节炸了，我也不知道为啥，主要还是代码太丑。后来听了大佬的建议，才改进了一点。

## 改过后的代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(x, l, r) for(int x = (int)l; x <= (int)r; x++)
#define repd(x, r, l) for(int x = (int)r; x >= (int)l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define mp(x, y) make_pair(x, y)
#define INF 1 << 30
#define MAXN 1005
using namespace std;
typedef long long LL;
typedef pair<int,int> par;

int n;
int a[MAXN], b[MAXN], ansk[MAXN];

bool judge(int len){
    rep(i, len, n - 1)
        if(a[i] != a[i % len]) return 0;
    return 1;
}

int main(){
    scanf("%d", &n);
    rep(i, 1, n){
        scanf("%d", &b[i]);
        a[i - 1] = b[i] - b[i - 1];
    }
    int ans = 0;
    rep(i, 1, n)
        if(judge(i)) ansk[++ans] = i;
    printf("%d\n", ans);
    rep(i, 1, ans) printf("%d ", ansk[i]);
    puts("");
    return 0;
}
```

---

