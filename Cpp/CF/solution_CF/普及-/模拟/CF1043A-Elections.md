# Elections

## 题目描述

Awruk is taking part in elections in his school. It is the final round. He has only one opponent — Elodreip. The are $ n $ students in the school. Each student has exactly $ k $ votes and is obligated to use all of them. So Awruk knows that if a person gives $ a_i $ votes for Elodreip, than he will get exactly $ k - a_i $ votes from this person. Of course $ 0 \le k - a_i $ holds.

Awruk knows that if he loses his life is over. He has been speaking a lot with his friends and now he knows $ a_1, a_2, \dots, a_n $ — how many votes for Elodreip each student wants to give. Now he wants to change the number $ k $ to win the elections. Of course he knows that bigger $ k $ means bigger chance that somebody may notice that he has changed something and then he will be disqualified.

So, Awruk knows $ a_1, a_2, \dots, a_n $ — how many votes each student will give to his opponent. Help him select the smallest winning number $ k $ . In order to win, Awruk needs to get strictly more votes than Elodreip.

## 说明/提示

In the first example, Elodreip gets $ 1 + 1 + 1 + 5 + 1 = 9 $ votes. The smallest possible $ k $ is $ 5 $ (it surely can't be less due to the fourth person), and it leads to $ 4 + 4 + 4 + 0 + 4 = 16 $ votes for Awruk, which is enough to win.

In the second example, Elodreip gets $ 11 $ votes. If $ k = 4 $ , Awruk gets $ 9 $ votes and loses to Elodreip.

## 样例 #1

### 输入

```
5
1 1 1 5 1
```

### 输出

```
5```

## 样例 #2

### 输入

```
5
2 2 3 2 2
```

### 输出

```
5```

# 题解

## 作者：Node_Edge (赞：3)

这题可以转化为一道数学题，运用到不等式的知识，小 A 的票数大于小 B 的票数，小 B 的票数可以表示为 $s$，小 A 的票数可以表示为 $n*k-s$，所以列出不等式 $n*k-s>s$，解得 $n=\dfrac{2s}{k}$。由于 $k\ge\max\left\{a_i\right\}$，所以最后 $\max\left\{a_i,\frac{2s}{k}\right\}$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],cnt,maxn;
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
        cnt+=a[i];
        maxn=max(maxn,a[i]);
    }
    cout<<max(maxn,cnt*2/n+1);
    return 0;
}
```


---

## 作者：WCG2025 (赞：2)

这道题感觉楼上只给了代码，没说意思，我就把我的思路阐释一下



------------

首先，我们先算出在当下情况下投给小B的票的总数，然后用当下投给小B票最高的票数当做最低票数，如果小A的票数大于小B的票数，直接输出就好了

如果在上面一种情况不成立的话，就将小B的总票数算出来+1，即为小A获胜票数的最低值，除以每一个人，如果整除就输出，整除不了就向下取整后+1
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int x;
int sum;
int maxx;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        sum+=x;
        maxx=max(x,maxx);//记录最大值
    }
    if(maxx*n-sum>sum)//情况1
    {
        printf("%d",maxx);
        return 0;
    }
    int res;
    int sum2=sum+1;
 	if((sum+sum2)%n)//情况2,3的讨论
        res=(sum+sum2)/n+1;
    else
        res=(sum+sum2)/n;
    printf("%d",res);
    return 0;
}
```
~~c++毁我青春~~

---

## 作者：Eason_AC (赞：1)

## Content
有两个人参加选举，其中已知 $n$ 位选民投给第二个人的票数为 $a_1,a_2,a_3,...,a_n$。第一个人很想赢，所以想通过调整每位选民**只能投的票数** $k$ 来让自己得票数比第二个人多，试求出最小的 $k$。

**数据范围：$1\leqslant n,a_i\leqslant 100,k\geqslant \max\{a_i\}$。**
## Solution
你们怎么都用的是直接枚举啊qwq，那我来一个偏数学的题解吧。

设选民给第二个人投的总票数为 $s$，我们可以列出这样的不等式：$nk-s>s$。解得 $k>\dfrac{2s}{n}$，所以我们的答案就是 $\max\{\dfrac{2s}{n}+1,\max\{a_i\}\}$。
## Code
```cpp
int n, a[107], sum, maxi, ans;

int main() {
	getint(n);
	_for(i, 1, n) {
		getint(a[i]);
		sum += a[i];
		maxi = max(maxi, a[i]);
	}
	ans = max(sum * 2 / n + 1, maxi);
	writeint(ans);
	return 0;
}
```

---

## 作者：Digital_Sunrise (赞：0)

## CF1043A题解

[CF 1043 题解合集](https://www.luogu.com.cn/blog/yl2330/I-Love-YR-Forever)

[Mardown 源代码](https://yhwh-group.coding.net/public/codingwiki/files/git/files/master/blog/CF1043/A.Markdown)

Update 21.11.17 更正博客地址

### 题意简述

有两个人参加选举，其中已知 $n$ 位投票者投给第二个人的票数为 $a_1,a_2,a_3,...,a_n$。

你的任务是通过调整每位选民只能投的票数 $k$ 来让第一个人的得票数比第二个人多，试求出最小的 $k$ 。

### 思路

想一下，最坏情况时 $a_1 = a_2 = a_3 = ... = a_n$ 。

此时 $k = 2 \times a_1 + 1$ 才能达成要求（严格大于） 。

推广一下，对于任意的 $a_1,a_2,a_3...,a_n$ 。

$k$ 必然在 $2 \times \max(a_1,a_2,a_3...,a_n) + 1$ 以内（别忘了要严格大于） 。

而 $2 \times \max(a_1,a_2,a_3...,a_n) + 1$ 最大为 $2 \times 100 + 1 = 201$ ，直接枚举即可 。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, a[110], maxa, cnt1;

int main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
		cnt1 += a[i];
		maxa = max(maxa, a[i]);
	}
	while (true)
	{
		int cnt2 = 0;
		for (int i = 1;i <= n;i ++)
			cnt2 += maxa - a[i];
		if (cnt2 > cnt1)
		{
			cout << maxa;
			break;
		}
		maxa ++;
	}
	return 0;
}
```

---

## 作者：infinities (赞：0)

这是一道水题，难度大概在~~已经死去的~~NOIP普及组T1~T2之间，其$n \le 100$的数据范围让我们可以随意写暴力（或小学数论）. 只要不是$O(2^n),O(n^4)$之类的神仙做法，基本都能过. 但是本题有几个比较小的坑点需要注意一下

1. 嗯，要注意k绝对不能小于所有$a_i$中的最大值(其实原题面有，只是翻译不给力，没写出来)

2. 如果打暴力枚举，不能只枚举到100就停，至少也要枚举到500才够

3. 好像没了..

code（仅供餐烤）：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
#include<queue>
#define int unsigned long long

int n,ans,a,start;

signed main(){
    std::ios::sync_with_stdio(false);
    
    std::cin>>n;
    
    for(register int i=1;i<=n;i++){//输入
        std::cin>>a;
        
        ans+=a,start=std::max(start,a);
    }
    
    for(register int i=start;;i++)//暴力枚举
        if(i*n>(ans<<1)){//中间那个两个小于好是左移位运算符，也就是乘上2的n次方
            std::cout<<i;
            
            return 0;
        }
}
```


---

## 作者：WKAHPM (赞：0)

一看数据范围， $1 \le n \le 100 $，此时不枚举更待何时？（雾）

注意获胜是指小$A$的票数大于小$B$的票数，而不是大于等于。（原谅作者语文不好$qwq$）

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[110];
int sum1,sum2;
bool comp(int a,int b)//自定义排序函数，从大到小排
{
	return a>b;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],sum1+=a[i];//预处理小B的票数
	sort(a+1,a+n+1,comp);//因为k>=max{ai}，所以考虑先排序
	for(int k=a[1];;k++)
	{
		sum2=0;//一定要初始化！
		for(int i=1;i<=n;i++)
		  sum2+=k-a[i];//每个人投给小A的票数就是每个人可以投的票数减去每个人投给小B的票数
		if(sum2>sum1)//是>不是>=
		{
			cout<<k;
			return 0;
		}
	}
	return 0;
}

```

观察一下代码，我们发现可以在求小$A$的票数部分做一些小小的优化

观察可以发现，$sum2$=$\sum_{i=1}^{n}(k-a_{i})$

原式

$=$ $k\times n-\sum_{i=1}^{n}a_{i}$ 

$=$ $k\times n-sum1$

于是在求小$A$的票数部分可以优化到$O(1)$复杂度

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[110];
int sum1,sum2;
bool comp(int a,int b)
{
	return a>b;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],sum1+=a[i];
	sort(a+1,a+n+1,comp);
	for(int k=a[1];;k++)
	{
		sum2=k*n-sum1;//求小A的票数，当然你也可以不用再设一个变量直接比较
		if(sum2>sum1)
		{
			cout<<k;
			return 0;
		}
	}
	return 0;
}

```


接下来我们再观察一下这个程序，我们发现，这个程序其实就要求最小的$k$，使得$k$满足$k\times n-sum1>sum1$

这不就是一个不等式吗

移项： $k\times n>2\times sum1$

系数化一: $k>2\times sum1 /n$

于是在求答案的部分就可以优化到$O(1)$复杂度


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[110];
int sum1;
bool comp(int a,int b)
{
	return a>b;
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],sum1+=a[i];
	sort(a+1,a+n+1,comp);
	if(2*sum1/n+1<a[1]) cout<<a[1];//因为k要>=max a[i]，所以如果2*sum/n+1<a[1]要输出a[1]
	else cout<<2*sum1/n+1;
	return 0;
}

```


---

## 作者：liuyz11 (赞：0)

广告：[这场比赛题解的原地址](https://www.cnblogs.com/nblyz2003/p/9868480.html)

这题很简单，就是说有n个人，每人投k张票，给你或你对手。第i个人会给你的对手投ai票，让你求最少的k。使得你的票数比你的对手多。模拟一下就好了，不多说。然而这题我又犯傻忘记了k >= max{ai}，wa了一次。

弱弱地放上我的代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x,y) memset(x, y, sizeof(x))
#define mp(x, y) make_pair(x, y)
#define INF 1 << 30
#define MAXN 
using namespace std;
typedef long long LL;
typedef pair<int,int> par;

int main(){
    int n;
    scanf("%d", &n);
    int sum = 0, maxx = 0;
    rep(i, 1, n){
        int x;
        scanf("%d", &x);
        sum += x;
        maxx = max(maxx, x);
    }
    int ans = 2 * sum / n + 1;
    if(ans < maxx) ans = maxx;
    printf("%d\n", ans);
    return 0;
}
```

---

