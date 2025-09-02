# Vasya and Basketball

## 题目描述

### 题意简述

Vasya 记录了一场篮球赛中两支队伍每次**命中的**投篮离篮筐的距离。他知道每一次成功的投篮可以得到 $2$ 分或 $3$ 分。如果一次**命中的**投篮离篮筐不超过 $d(d \ge 0)$ 米则得 $2$ 分，否则得 $3$ 分。Vasya 可以指定一个 $d$，同时他希望第一支队伍的分数 $a$ 减去第二支队伍的分数 $b$ 最大。

请你帮他求出这个 $d$。

## 样例 #1

### 输入

```
3
1 2 3
2
5 6
```

### 输出

```
9:6
```

## 样例 #2

### 输入

```
5
6 7 8 9 10
5
1 2 3 4 5
```

### 输出

```
15:10
```

# 题解

## 作者：Yang818 (赞：1)

# 题目传送门

[这里](https://www.luogu.com.cn/problem/CF493C)

# 分析

本题贪心

$d$ 有最优解的时候肯定是 $a_i$，这样才可能报证 a 队的 3 分球数量尽可能多，b 队尽可能少。按照 a 队的得分情况从大到小排列并逐个枚举，计算得分，顺便擂台法即可。

看代码中的具体注释吧！

记得吸氧

# 代码

```cpp
#include<bits/stdc++.h>
#define F(_x,_y) for(int i=_x;i<=_y;i++)
using namespace std;
const int MAXN=2e5+5;
int g_n,g_m;
int a[MAXN],b[MAXN];
int main(){
	cin>>g_n;
	F(1,g_n)	cin>>a[i];
	sort(a+1,a+g_n+1);//排序后方便贪心 
	cin>>g_m;
	F(1,g_m)	cin>>b[i];
	sort(b+1,b+g_m+1);
	int ans_a,tmp_a,ans_b,tmp_b;//tmp 记录每个 d 的得分，ans 记录最优解 
	tmp_a=ans_a=g_n*2;//初始化得分每队每球至少是 2 分 
	tmp_b=ans_b=g_m*2;
	for(int i=g_n,j=g_m;i>0;i--){//从大到小贪心 
		tmp_a++;//a 队的三分球数量多一个 
		for(;j>0&&b[j]>=a[i];j--)//计算 b 队的得分 
			tmp_b++;
		if(ans_a-ans_b<=tmp_a-tmp_b){//擂台法 
			ans_a=tmp_a,ans_b=tmp_b;
		}
	}
	cout<<ans_a<<":"<<ans_b;
	return 0;
} 
```


---

## 作者：liuli688 (赞：0)

提供一种简洁明了且易懂的方法，码量也不大。
### 思路
考虑最暴力的办法：对于 $\forall d \in [0,\max\{\max_{i=1}^n a_i,\max_{i=1}^m b_i\}]$，将这个 $d$ 作为三分线，再枚举一遍两个数组即可算出两队的分。可是题目中的数据范围是 $1 \le a_i,b_i \le 2 \cdot 10^9$，用这个暴力方法显然会 T 飞。

所以，我们需要思考一下：上面枚举的每个 $d$ 都是“有用”的吗？$n$ 和 $m$ 的范围是 $1 \le n,m \le 2 \cdot 10^5$，实际上当 $d \notin a \cup b$ 时 $d$ 可以用一个数 $d' \in a \cup b$ 代替，且 $d' > d$，$\forall x > d,x \ne d'$ 有 $x - d > d' - d$（说人话，就是在 $a$ 和 $b$ 的并集中找 $d$ 的后继啦）。

这样，我们成功地将时间复杂度从 $O(N \times \max a_i)$ 即约 $(2 \times 10^5) \times (2 \times 10^9)$ 降到了 $O(N^2)$。可是这样显然还是会 T。

看看哪里还能优化。枚举 $d$ 的 $O(N)$ 显然少不了，那么就只能优化内层计算分数的部分了。如何实现线性时间复杂度？在数组有序的情况下，每更改一次分数线只会改变一支队伍的分数。所以，我们想到通过排序的方式将复杂度降到 $O(N)$。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define reg register
#define fir first
#define sec second

constexpr int N = 2e5 + 1;
const int A = 0,B = 1;//标记该球的归属队
int n,m,ansa = INT_MIN,ansb = 0;
pair<int,bool> a[N<<1];

signed main()
{
    scanf("%d",&n);
    for(reg int i = 0;i < n;++i)
    {
        scanf("%d",&a[i].fir);
        a[i].sec = A;
    }
    scanf("%d",&m);
    for(reg int i = n;i < n + m;++i)//在输入时将两数组合并
    {
        scanf("%d",&a[i].fir);
        a[i].sec = B;
    }
    sort(a,a + n + m);//排序
    for(reg int i = n + m - 1,acnt = 0,bcnt = 0;~i;--i)
    {
        if(a[i].sec)//属于 B 球队
            ++bcnt;
        else//属于 A 球队
            ++acnt;
        if(((n << 1) + acnt) - ((m << 1) + bcnt) >= ansa - ansb)//当前差值更小（记得要用 >= 号，否则不符合“如果有相同的 a - b，最大化 a。”）
        {
            ansa = (n << 1) + acnt;
            ansb = (m << 1) + bcnt;
        }
    }
    if((n << 1) - (m << 1) > ansa - ansb)//不要忘了最后还要判断一次
        printf("%d:%d",(n << 1),(m << 1));
    else
    	printf("%d:%d",ansa,ansb);
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 分析
根据贪心思想，我们可以把两个球队分别按距离，从小到大排序。然后由于 $d$ 使答案最优时肯定是 $a_i$，所以可以倒着枚举 $i$，看另外一支队会多几个三分即可。
## CODE
```cpp
#include<bits/stdc++.h>

using namespace std;

int n,m;
int a[400000],b[400000];

int main()
{
	cin>>n;
	int ansx=2*n;
	int kx=ansx;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	
	cin>>m;
	int ansy=2*m;
	int ky=ansy;
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
	}
	sort(b+1,b+m+1);	

	for(int i=n,j=m;i>=1;i--)
	{
		ansx++;
		
		while(j>=1&&b[j]>=a[i]) 
		{
			j--;
			ansy++;
		}
		
		if(kx-ky<=ansx-ansy) 
		{
			kx=ansx;
			ky=ansy;
		}
	}
	
	cout<<kx<<":"<<ky;
	
	return 0;
}
```


---

## 作者：Computer1828 (赞：0)

贪心，把两个球队分别按距离从小到大排序，然后 $d$ 使答案最优时肯定是等于 $a_i$，所以倒序枚举每个 $i$，看另外一支队会多几个三分就行。

代码：

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,m,a[N],b[N],s1,s2;
int main(){
	scanf("%d",&n);for(int i = 1;i<=n;++i) scanf("%d",a+i);
	scanf("%d",&m);for(int i = 1;i<=m;++i) scanf("%d",b+i);
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	int ans1 = n*2,ans2 = m*2;
	s1 = ans1,s2 = ans2;
	for(int i = n,j = m;i;--i){
    //d = a[i]
		ans1++;
		while(j && b[j]>=a[i]) j--,ans2++;
		if(s1-s2 <= ans1-ans2) s1 = ans1,s2 = ans2;
	}
	printf("%d:%d",s1,s2);
	return 0;
}
```

---

