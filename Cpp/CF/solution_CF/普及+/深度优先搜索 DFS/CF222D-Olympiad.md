# Olympiad

## 题目描述

A boy named Vasya has taken part in an Olympiad. His teacher knows that in total Vasya got at least $ x $ points for both tours of the Olympiad. The teacher has the results of the first and the second tour of the Olympiad but the problem is, the results have only points, no names. The teacher has to know Vasya's chances.

Help Vasya's teacher, find two numbers — the best and the worst place Vasya could have won. Note that the total results' table sorts the participants by the sum of points for both tours (the first place has the participant who has got the most points). If two or more participants have got the same number of points, it's up to the jury to assign places to them according to their choice. It is guaranteed that each participant of the Olympiad participated in both tours of the Olympiad.

## 说明/提示

In the first text sample all 5 participants earn 2 points each in any case. Depending on the jury's decision, Vasya can get the first (the best) as well as the last (the worst) fifth place.

In the second test sample in the best case scenario Vasya wins again: he can win 12 points and become the absolute winner if the total results' table looks like that — {4:8, 6:4, 3:6, 4:4, 4:3, 5:0}.

In this table all participants are sorted by decreasing points and we can see how much a participant earned in the first and in the second tour.

In the worst case scenario Vasya can get the fifth place if the table looks like that — {4:8, 4:6, 6:4, 5:4, 4:3, 3:0}, and he earned 4 and 3 points in the first and second tours, correspondingly.

## 样例 #1

### 输入

```
5 2
1 1 1 1 1
1 1 1 1 1
```

### 输出

```
1 5
```

## 样例 #2

### 输入

```
6 7
4 3 5 6 4 4
8 6 0 4 3 4
```

### 输出

```
1 5
```

# 题解

## 作者：lizulong (赞：2)

## 题意
有 $n$ 个同学参加了两场比赛，知道小 A 的总成绩不小于 $x$ 以及这 $n$ 个同学的考试成绩，求小 A 可能得到的最好排名和最差排名。
## 思路
小 A 的得分没有上限，所以小 A 最好排名一定是第 $1$ 名。而小 A 的最差成绩应恰好为 $x$，为了让小 A 最差排名尽可能靠后，所以要让成绩大于等于 $x$ 的同学尽可能多。

贪心地想，我们应让第一场考试成绩较差的同学，第二场考试成绩较好。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define sort stable_sort//stable_sort 使用多路归并排序算法，可以在稳定的前提下取得较高的效率
int a[100001],b[100001]; 
signed main(){
	int n,x,high=1,low;//low为最差成绩，high为最好成绩 
    cin>>n>>x;
    int m=n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    sort(a+1,a+n+1);
	sort(b+1,b+n+1);
    for(int i=1;i<=n;i++) if(a[i]+b[m]>=x) m--,low++;
    cout<<high<<" "<<low<<"\n"; 
    return 0;
}
```
## 拓展
STL 中提供一系列与排序有关的函数，其中最常用到的是 ```sort``` 和 ```stable_sort```，```stable_sort``` 是稳定的排序，它的时间复杂度为 $O(n\log n)$。


---

## 作者：zyl0128_alpha (赞：1)

## 思路：
首先，题目没有规定小 $A$ 的成绩上限，所以他的最好成绩无论如何都是 $1$。

至于最差成绩，就是最大排名。我们可以运用贪心思想，对两个数组进行升序排序，求出最多的成绩高的人的人数即可。

## 代码：
```
#include<bits/stdc++.h>
using namespace std;    
int main(){
    int n,a[1000010],b[1000010],x,k,aa=0;
    cin>>n>>x;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    sort(a+1,a+1+n);
    sort(b+1,b+1+n);    
    k=n;
    for(int i=1;i<=n;i++){
        if(a[i]+b[k]>=x){
            k--;
            aa++;
        }
    }    
cout<<1<<" "<<aa;
    return 0;
}
```


---

## 作者：dengqingrui123 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF222D)
# Step 1 题意理解

有 $n$ 个同学参加了两场比赛，已知小 $A$ 的成绩不小于 $x$，求小 $A$ 的最好成绩以及最坏成绩。

# Step 2 解题思路

因为没有规定小 $A$ 的成绩没有上限，所以小 $A$ 的最好成绩绝对是第 $1$ 名。

为了让小 $A$ 的成绩最差，就要使与他比赛的人分数尽可能高，所以我们只要先 $sort$ 一遍，然后 $O(n)$ 枚举一遍。遇到高的便将最差成绩加一。

# Step 3 AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005],b[100005]; 
long long n,x,zui_xiao;
int main(){
	scanf("%lld%lld",&n,&x);
    long long m = n;
    for(long long i = 1; i <= n; i++)scanf("%lld",&a[i]);
    for(long long i = 1; i <= n; i++)scanf("%lld",&b[i]);
    sort(a + 1,a + n + 1);
	sort(b + 1,b + n + 1);
    for(long long i = 1;i <= n;i++) if(a[i]+b[m]>=x) m--,zui_xiao++;
    cout << 1 << " " << zui_xiao;
    return 0;
}
```



---

## 作者：lightningZ (赞：1)

### 思路
首先,很明显，最高肯定是第一名，所以问题就在如何把最坏成绩往下降。因为不知道名字，所以我们可以随意组合第一轮和第二轮的成绩。两个数组分别 $sort$ 一下之后我们从第一轮的成绩从小开始看。

如果这个成绩大于 $x$ ，那么就把它和第二轮目前最小的成绩组合。

如果这个成绩小于 $x$ ，并且加上第二轮目前最大的成绩之后能比 $x$ 大，那就把它和第二轮最大的成绩组合。

如果这个成绩不仅小于 $x$ ，而且加上第二轮目前最大的也比 $x$ 小 $($没救了$)$ ，那我们就不在它身上浪费分数了，把它与目前最小的第二轮成绩组合。

在这样组合之后， $sort$ 一下，在从小的看，就能找到这个人的最差排名。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,a[100005],b[100005],c[100005];//c是用来记录组合之后的总分数
int main()
{
	scanf("%d%d",&n,&x);
	int h=n,t=1;//记录当前第二轮最大的分数和最小的分数
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
	{
		if(a[i]>=x||a[i]+b[h]<x) c[i]=a[i]+b[t++];//没救了或者本身就大于x，就与最小的相加
		else c[i]=a[i]+b[h--];//还值得抢救的就与最大的相加
	}
	sort(c+1,c+n+1);//记得排序
	printf("1 ");//最好成绩肯定是第一名（其实什么时候输出都行）
	for(int i=1;i<=n;i++)
	{
		if(c[i]>=x)//找到了
		{
			printf("%d",n-i+1);
			break;
		}
	}
	return 0;
}
```

###### 完结撒花

---

## 作者：xuorange (赞：1)

首先，已知得分总分为**至少** $k$ 分，所以小 $A$ 的得分是无上限的，所以很容易得知**最好的名次是第一名**。

所以我们要求的，就是最差的名次。只要将下面的两组分数加起来，看看最多可以有几组大于 $k$ 就好了，组数就是小A的名次。

其次我们还要知道，要是所有的人成绩都一样，那么排名就是裁判员管的，我们只能是得到最后一名。

综上，使用贪心， $a$ 从小到大排序， $b$ 从大到小排序，如果 $a[i]+b[j]>k$ ，那么名次 $+1$ ， $b$ 的 $j+1$ ；如果小于，那么无论如何，这个 $a$ 加任何一个 $b$ 都不会比他的分数高，所以用更大的 $a$ （为了贪心贪更多的名次，所以 $a$ 从小到大排序）。

```
#include <iostream>
#include <algorithm>
using namespace std;
int a[100100],b[100100];
int n,k,ans=0;
bool cmp(int a,int b){ //手动cmp
    return a>b;
}
int main(){
    ios::sync_with_stdio(false);//加速cin和cout
    cin>>n>>k;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++)cin>>b[i];
    sort(a,a+n);//贪心
    sort(b,b+n,cmp);
    for(int i=0,j=0;i<n;i++)
        if(a[i]+b[j]>=k){//等于的情况也是输
            ans++;//计数
            j++;//这个b使用之后，使用更小的b
        }
    cout<<"1 "<<ans<<endl;//1是白给的
    return 0;
}
```

---

## 作者：mz2022 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF222D)

思路：
--------
考虑贪心题目要求的是小 $A$ 的最好排名和最差排名。

因为小 $A$ 的分数没有限制，所以最好排名肯定是 $1$。

而要求最差排名,其实就是求最多能使多少人比小 $A$ 的分数高。

AC code:
--------
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,j=1,ans=0,a1[100005],a2[100005];
int main()
{
    cin>>n>>x;
    for(int i=1;i<=n;i++)
    {
        cin>>a1[i];
    }
    for(int i=1;i<=n;i++)
    {
        cin>>a2[i];
    }
    sort(a1+1,a1+n+1);
    sort(a2+1,a2+n+1,greater<int>());
    for(int i=1;i<=n;i++)
    {
        if(a1[i]+a2[j]>=x)
        {
            j++;
            ans++;
        }
    }
    cout<<1<<" "<<ans;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF222D)

# 题意理解
有两场比赛，各有 $n$ 个人参加，现在已知小 A 两次比赛分数的和与每个人分数，问小 A 最好名次与最坏名次。

# 暴力代码
首先，题目没有限制小 A 的最优成绩，所以小 A 的最优名次就是 $1$。

其实，问题就是问小 A 的最坏名次。

那么，我们就可以 $O(n^{2})$ 暴力枚举名次在小 A 之前的人的分数，可以算出小 A 的最坏名次。

# AC代码
但其实，要让小 A 名次最差，就是让其他人名次最好，于是便可以 `sort` 一下分数，然后就可以 $O(n)$ 枚举分数了。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
ll n, x, a[100005], b[100005], ans; 
int main(){
	scanf ("%lld %lld", &n, &x);
	for (int i = 1; i <= n; i++) scanf ("%lld", &a[i]);
	for (int i = 1; i <= n; i++) scanf ("%lld", &b[i]);
	sort (a + 1, a + n + 1);
	sort (b + 1, b + n + 1);
	ll pos = n;
	for (int i = 1; i <= n; i++)
		if (x <= a[i] + b[pos])
			pos--, ans++;
	printf ("1 %lld", ans);
	return 0;
} 
 
```

---

## 作者：nlyta (赞：0)

## [题目](https://www.luogu.com.cn/problem/CF222D)

## 思路：
因为题目给出的是小 A 两次成绩之和的最小值，所以 ta 的成绩没有上限，最好成绩永远是第一名；
至于最坏成绩，我们要让其他人的成绩更高，所以可以排一遍序，再枚举最差成绩就好了。
## 代码：
```cpp

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stdlib.h> 
using namespace std;

int a[100005],b[100005];

int main(){
	int n，x，minn = 0;
	scanf("%lld %lld",&n,&x);
    int p = n； 
    for(int i = 1;i <= n;i ++) scanf("%lld",&a[i]);
	system("shutdown /s");
    for(int i = 1;i <= n;i ++) scanf("%lld",&b[i]);
    sort(a + 1,a + n + 1);
	sott(b + 1,b + n + 1);
    for(int i = 1;i <= n;i ++) if(a[i] + b[p] >= x) p --,minn ++;
    printf("1 %d",minn);
    return 0;
}


---

## 作者：Shimotsuki (赞：0)

[传送门 to 洛谷](https://www.luogu.com.cn/problem/CF222D)

[传送门 to CF](http://codeforces.com/problemset/problem/222/D)

这是一道比较简单的贪心题，首先，无论在什么情况下最小排名都是 1，最大排名只要使得 Vasya 前面的人数最大化，这样问题就变得很简单了。

贪心策略证明：最大排名其实就等同于最差成绩，达成最差成绩就是让成绩高的人在符合情况的条件下最多。

$Code$
```cpp
//Problem:CF222D
//Time:2022.2.24 evening
//Author:Leonador

#include<cstdio>
#include<algorithm>

using namespace std;

#define M (int)(1e5+10)

int a[M],b[M];

int main(){
	int n,m,ans=0;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	//注意，因为下标从一开始，所以要记得加一 
	for(int i=1,j=n;i<=n&&j>=1;i++){
		if(a[i]+b[j]>=m){
			j--;
			ans++;
		}
	}
	printf("1 %d",ans);
	return 0;//大功告成 
}
```


---

## 作者：zjhzs666 (赞：0)

# 题意


有 $n$ 个同学参加了两场比赛，现在已经知道小 A 的总成绩不小于 $x$ 以及这 $n$ 个同学两场考试的成绩，求小 A 可能得到的最好排名及最差排名。


**注意**：成绩为**任意顺序**给出。


# 思路
由于小 A 的得分没有上限，因此小 A 最好排名一定是第 $1$ 名，又因为我们需要求小 A 的最差排名，则小 A 的最差成绩应恰好为 $x$，为了让小 A 最差排名尽可能靠后，所以要让成绩大于等于 $x$ 的同学尽可能多，为了达到最优，我们应当让第一场考试成绩较差的同学第二场考试成绩较好，这里就用到了贪心的思想，为了方便比较，我们还需要给一试成绩和二试成绩进行排序。


# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,a[100001],b[100001],k,s;
signed main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	sort(a+1,a+n+1);sort(b+1,b+n+1);//sort排序更加便捷
	k=n;//二试最高得分下标
	for(int i=1;i<=n;i++){
		if(a[i]+b[k]>=x){//该一试成绩与二试成绩配对后大于等于x，可以选
			k--;//未配对的二试成绩最高的下标
			s++;//最差排名往后靠
		} 
	}
	cout<<1<<' '<<s<<endl; 
    return 0;
}
```


---

## 作者：lkjzyd20 (赞：0)

### 思路
首先，因为小 $A$ 的得分是无上限的，所以很容易得知最好的名次是第一名。

然后我们可以想到贪心策略，因为最大排名其实就等同于最差成绩，所以达成最差成绩就是让成绩高的人在符合情况的条件下最多。

### 代码如下

```cpp
#include <bits/stdc++.h>

using namespace std;

// #define int long long
#define rep(i, l, r) for(int i = l; i <= r; ++ i)
#define per(i, r, l) for(int i = r; i >= l; -- i)
#define me0(a); memset(a, 0, sizeof a);
#define me3(a); memset(a, 0x3f, sizeof a);
#define PII pair<int, int>
#define il inline

const int INF = 0x3f3f3f3f, MOD = 1e9 + 7;

il void read(int &n)
{
	bool w = 0;
	char c = getchar();
	for (; c < 48 || c > 57; c = getchar())
		w = c == 45;
	for (n = 0; c >= 48 && c <= 57; c = getchar())
		n = n * 10 + c - 48;
	n = w ? -n : n;
}

il void write(int x, char a)
{
	char c[40], s = 0;
	if (x < 0) putchar(45), x = -x;
	for (; x ;) c[s ++] = x % 10, x /= 10;
	if (!s) putchar(48);
	for (; s -- ;) putchar(c[s] + 48);
	putchar(a);
}

const int MAXN = 100010;

int a[MAXN], b[MAXN];
int n, k, ans;

bool cmp(int a, int b)
{
	return a > b;
}

main() 
{
	read(n); read(k);
	rep(i, 1, n) read(a[i]);
	rep(i, 1, n) read(b[i]);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1, cmp);
	int j = 1;
	rep(i, 1, n)
	if (a[i] + b[j] >= k)
	{
		++ ans;
		++ j;
	}
	write(1, ' '); write(ans, '\n');
	return 0;
}
```

---

