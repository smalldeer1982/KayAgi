# Sanatorium

## 题目描述

当瓦西里在疗养院度假回来，发现他完全忘了他的度假的细节！

每天疗养院的餐厅里都有早餐、午餐和晚餐（当然，按这个顺序）。瓦西里现在唯一拥有的就是一张餐厅的卡片，上面写着他吃过多少次早餐、午餐和晚餐（因此，卡片包含三个整数）。瓦西里有时可能会错过一些食物，例如，他可以吃早饭和晚餐，但晚餐不吃，或者也许在某些天，他根本没有在餐厅。

瓦西里不记得一天中他到达疗养院的时间（早餐前、午餐前、晚餐前或晚餐后），以及他离开疗养院的时间（早餐前、午餐前、晚餐前或晚餐后）。所以他考虑了这些选择中的任何一个。瓦西里来到疗养院后，一直呆在那里直到离开。请注意，瓦西里可能是在抵达疗养院的同一天离开的。

根据卡片上的说明，帮助瓦西里确定他可能错过的餐厅的最少用餐次数。我们不应算作瓦西里抵达前一天的误餐，也不应算作瓦西里离开后一天的误餐。

根据卡片上的说明，帮助瓦西里确定他可能错过的餐厅的最少用餐次数。我们不应算作瓦西里抵达前一天的没吃的餐，也不应算作瓦西里离开后一天的没吃的餐。

## 说明/提示

在第一个样例中，瓦西里可能错过了一顿晚餐，例如，如果他在早餐前到达，在疗养院呆了两天（包括抵达当天），然后在第三天早餐后离开。

在第二个样例中，瓦西里可以在早餐前到达，吃过它，然后立即离开疗养院，没有错过任何一顿饭。

在第三个样例中，瓦西里可能在疗养院呆了一天，没有错过任何一顿饭。

## 样例 #1

### 输入

```
3 2 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1 0 0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
1 1 1
```

### 输出

```
0
```

## 样例 #4

### 输入

```
1000000000000000000 0 1000000000000000000
```

### 输出

```
999999999999999999
```

# 题解

## 作者：MurderChara (赞：8)

### [CF732C Sanatorium](https://www.luogu.org/problemnew/show/CF732C)
emmm这种题目好像看上去很复杂，但是。。。~~只要看懂题了就算是是刚入洛谷的萌新也会做啊喂！~~


------------
#### 分析题目
~~刚看题目时就想模拟（蒟蒻本能），然鹅马上就被惊人的数据吓退了~~

仔细想下各种情况再看看栗子可以发现：
- 一日有三餐，这个人又可以随时来随时走

- 所以经过思考~~枚举~~可以发现他最多可以白嫖(即不错过也不吃)两种类型饭各一顿 

- 然后就必须将两个非最大的餐数像最大的餐数补齐至一日三餐。。。结合起来即可写出代码



------------
#### 举例说明
举个栗子：例如输入6 1 3，思考步骤如下

1. 按照刚刚说的，找出最大值为早餐餐数，有6顿
2. 所以其他两餐数量至少要补齐至4顿，即补齐至6 1(+4) 3(+2)，就是6 5 5，之所以不补成6 6 6，是因为前文说了他可以白嫖两种类型的饭各一顿
3. 于是输出便是4+2=6啦~\(≧▽≦)/~


------------
#### 代码实现
可能蒟蒻代码不够简便，请见谅QAQ


```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[4];
int main(){
	long long cha1,cha2; //注意题目的数据范围哦 
	for(int i=1;i<=3;i++)
    {
		cin>>a[i];
	}
	sort(a+1,a+4); //排个序方便找最大值 
	if(a[2]>=a[3]-1) //这是不用补的情况 
	{
		cha1=0;
	}
	else
	{
		cha1=a[3]-1-a[2]; //之所以减一是因为他可以白嫖(滑稽) 
	}
	if(a[1]>=a[3]-1) //这也是不用补的情况
	{ 
		cha2=0;
	}
	else
	{
		cha2=a[3]-1-a[1]; //同上个eles下的话 
	}
	cha1+=cha2; //两种加起来就是总共最少忘的餐数了 
	cout<<cha1;
	return 0;
}
```

#### PS
注意！！！~~不开longlong见祖宗！~~

第一次写题解，请多多关照=)

---

## 作者：PR_CYJ (赞：4)

# [题目传送门](https://www.luogu.com.cn/problem/CF732C)
# 思路
这道题的大致题意为：瓦西里可以在任意时间进出疗养院，现在给定瓦西里吃的早餐、午餐、晚餐的数量，请你求出瓦西里最少漏掉了几顿餐。

首先将三个数顺序排序，并保存到 $a$ 数组里（$a_1\le a_2\le a_3$）。很容易想到，如果瓦西里没有漏掉任何一餐，那么任意两餐的数量差值都应当小于 $1$。所以，如果 $a_3-a_1\le 1$，那么瓦西里就没有漏掉任何一餐。否则就考虑补齐，分别计算 $a_1$ 和 $a_2$ 对答案的贡献即可。
# 代码
- 切勿抄袭！！！

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
	ll a[5]={};
	for(int i=1;i<=3;i++)
		cin>>a[i];
	sort(a+1,a+4);
	if (a[3]-a[1]<=1)
		cout<<0<<endl;
	else
		if (a[3]-a[2]<=1)
			cout<<a[3]-1-a[1]<<endl;
		else
			cout<<a[3]-1-a[2]+a[3]-1-a[1]<<endl;
}
```

---

## 作者：2023gdgz01 (赞：2)

通过分析可得知，如果 $b,d,s$ 任意两数的差值小于等于 $1$，那么瓦西里就没有错过任何一顿饭。我们可以分类讨论来证实，不妨假定 $b\le d\le s$：

1. $d=s=b+1$，瓦西里可以在第一天早饭后午饭前的时候来，在最后一天晚饭后走；

2. $d=b,s=b+1$，瓦西里可以在第一天午饭后晚饭前的时候来，在最后一天晚饭后走；

3. $b=d=s$，瓦西里可以在第一天早饭前的时候来，在最后一天晚饭后走。

而求最少可能错过的顿数，只用求出将 $b,d,s$ 补齐至任意两数的差值小于等于 $1$ 即可。可以证明这是最优方案。令 $maxn=\max(b,d,s)$，则最终答案为 $\max(maxn-b-1,0)+\max(maxn-d-1,0)+\max(maxn-s-1,0)$。最后注意一下 `long long` 的问题就可以了。代码如下：

```cpp
#include <cstdio>

long long b, d, s, maxn;

inline long long max(long long x, long long y) {
	if (x > y) {
		return x;
	}
	return y;
}

int main() {
	scanf("%lld%lld%lld", &b, &d, &s);
	maxn = max(max(b, d), s);
	printf("%lld", max(maxn - b - 1, 0) + max(maxn - d - 1, 0) + max(maxn - s - 1, 0));
	return 0;
}
```

时间复杂度为 $O(1)$。[AC 链接](https://www.luogu.com.cn/record/161296781)

---

## 作者：linan04195 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF732C)
---
## 思路
瓦西里肯定要吃一日三餐，如果他每一顿饭都吃了，则最大差值 $sum$ 肯定不超过 $1$。若三餐中有一顿小于 $sum$，则错过了 $sum-1$ 再减去那一顿。

## Code
```cpp

#include<bits/stdc++.h>
using namespace std;

long long breakfast,lunch,dinner;
long long ma(long long a,long long b,long long c){
	return max(max(a,b),c);
}

int main(){
	cin>>breakfast>>lunch>>dinner;
	
	int maxn=ma(breakfast,lunch,dinner);
	maxn--;
	
	breakfast=max(maxx-breakfast,0);
	lunch=max(maxx-lunch,0);
	dinner=max(maxx-dinner,0);
	
	cout<<breakfast+lunch+dinner;
	return 0;
}
```

---

## 作者：keep_shining (赞：1)

我又来水题解了！

## 题意：
给你 $a,b,c$ 三个数，表示早饭，午饭，晚饭的数量，你可以在任意时间来，问你最少会错过几顿饭。

## 思路：
要全吃到，那三顿饭顿数的差值不能超过 $1$，否则就会有饭吃不到。

那如果第 $a_i$ 顿的数量小于最大值减 $1$，那他肯定就有 $max-1-a_i$ 顿这样的饭吃不到（别忘了减 $1$！），最后我们再把每顿饭吃不到的次数加起来就好了。

### 警示，要开 long long！

## AC code：
```cpp
#include<bits/stdc++.h>

using namespace std;

#define fst ios::sync_with_stdio(false);cin.tie();cout.tie();
#define Endl endl
#define itn int
#define For(i,a,b) for(int i=a;i<=b;i++)
#define int long long//要开long long！

const int N=1e5+5;
const int P=1e9+7;

int n;

int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}

void write(int x)
{
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}

signed main()
{
    int a=read(),b=read(),c=read();
    int ma=max(max(a,b),c)-1,s=0;//求出最大值，别忘了减1
    a=max(s,ma-a);//算出第一顿少吃了多少，因为有可能减出负数，所以要和0取较大值,我用s是因为max只能比较相同数据类型的
    b=max(s,ma-b);//同上
    c=max(s,ma-c);//同上
    cout<<a+b+c;//算出和
    return 0;
}



```

---

## 作者：WA_sir (赞：1)

## [题目](https://codeforces.com/problemset/problem/732/C)|[链接](https://www.luogu.com.cn/problem/CF732C)

### 题目大意

每天疗养院都有早餐、午餐和晚餐，瓦西里可以在任意时间（餐前餐后）来到或离开。现给出瓦西里在疗养院所吃的三餐顿数，求出他最少可能错过了几顿饭。

### 题目分析

针对没有错过任意一顿饭的情况下，三餐顿数之间的差值最多为 $1$。因此，当三餐顿数中任意一个小于了三餐中最大值减 $1$，就肯定是错过了的。而错过的顿数，为 $max-1-a_i$ 顿。只需补齐 $max-1-a_i$ 顿，就可以使其与最大值差为 $1$。

### 参考代码

```cpp
#include<bits/stdc++.h>
#define l long long
using namespace std;
l a,b,c,ma;
int main()
{
	scanf("%lld%lld%lld",&a,&b,&c);
	ma=max(max(a,b),c)-1;
	a=max(ma-a,0ll);
	b=max(ma-b,0ll);
	c=max(ma-c,0ll);
	printf("%lld",a+b+c);
	return 0;
}
```
感谢您的阅读！

---

## 作者：封禁用户 (赞：1)

## 思路
~~人是铁，饭是钢~~，肯定要吃一日三餐。所以有以下几个情况：
1. 如果他每一顿饭都吃了，则最大差值 $sum$ 肯定不超过 $1$。 
2. 三餐中有一顿小于 $sum$，则错过了 $sum−1$ 再减去那一顿。

---

## 作者：Storm_Lightning (赞：1)

# 题解：CF732C Sanatorium

## 思路分析

我们设两两之间数量的最大差值为 $max$。

- 若瓦西能全部吃掉，则 $max$ 不能超过 $1$。

- 若三餐数量中任意一个小于了 $max$ 减 $1$。则一定错过了，而错过的数量为 $max-1-a_i$，所以只需再补这么多，就可以使得饭的数量两两之间不超过 $1$。

## 示例代码

套公式。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define itn int
#define itn long long
int a,b,c,maxx;
int main()
{
	cin>>a>>b>>c;
	maxx=max(max(a,b),c);
	maxx-=1;
	a=max(maxx-a,0ll);
	b=max(maxx-b,0ll);
	c=max(maxx-c,0ll);
	cout<<(a+b+c)<<endl;
	return 0;
}
```

---

## 作者：andyli (赞：0)

分类讨论，分别考虑早、中、晚到达，早、中、晚离开，假设早上到达，则假定早上的用餐次数为实际早上的用餐次数（早上不缺席），可据此推出其他时段总餐数，对应减去实际餐数记入答案。

分 9 类。  

```cpp
int main() {
    dR(i64, a, b, c);
    i64 ans = inf<i64>;
    // 0~0
    // (a, a-1, a-1)
    if (b <= a - 1 && c <= a - 1)
        chkmin(ans, a - 1 - b + a - 1 - c);
    // 0~1
    // (a, a, a-1)
    if (b <= a && c <= a - 1)
        chkmin(ans, a - b + a - 1 - c);
    // 0~2
    // (a, a, a)
    if (b <= a && c <= a)
        chkmin(ans, a - b + a - c);
    // 1~1
    // (b-1, b, b-1)
    if (a <= b - 1 && c <= b - 1)
        chkmin(ans, b - 1 - a + b - 1 - c);
    // 1~2
    // (b-1, b, b)
    if (a <= b - 1 && c <= b)
        chkmin(ans, b - 1 - a + b - c);
    // 1~0
    // (b, b, b)
    if (a <= b && c <= b)
        chkmin(ans, b - a + b - c);
    // 2~2
    // (c-1, c-1, c)
    if (a <= c - 1 && b <= c - 1)
        chkmin(ans, c - 1 - a + c - 1 - b);
    // 2~0
    // (c, c - 1, c)
    if (a <= c && b <= c - 1)
        chkmin(ans, c - a + c - 1 - b);
    // 2~1
    // (c, c, c)
    if (a <= c && b <= c)
        chkmin(ans, c - a + c - b);
    
    print(ans);
    return 0;
}
```

---

## 作者：szh_AK_all (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF732C)

做这道题并不需要什么高难度的算法，只需要理解即可。我们发现，瓦西里可以“赊”的餐数最多为 $2$（与楼上大佬说的一样）。举个例子：当瓦西里在吃过早餐后离开餐厅，那么他就可以“赊”中餐和晚餐。所以，我们得出一个结论：
1. 瓦西里最多赊两种餐类，因为在最小情况下，我们将他吃的最多的餐类视为为赊的餐类；
2. 考虑食用次数非最大的两种餐类，可以先让他们加 $1$，再判断错过了几餐。

综上所述，得出代码。
```c
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    long long a,b,c;
    cin>>a>>b>>c;
    long long k=max(a,max(b,c));//得出最大餐类
    long long k1=min(a,min(b,c));//得出最小餐类
    long long k2=a+b+c-k-k1;//得出中间餐类
    long long p=0;
    long long tmp=max(p,k-k2-1);//注意，这里的p不应直接写成0，因为会报错（类型不一致）
    tmp+=max(p,k-k1-1);
    cout<<tmp;
    return 0;
}
```
[在这里看效果更佳](https://www.luogu.com.cn/blog/jdsndjknddb/solution-cf732c)

---

