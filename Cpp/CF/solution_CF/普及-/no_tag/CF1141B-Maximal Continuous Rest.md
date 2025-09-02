# Maximal Continuous Rest

## 题目描述

Each day in Berland consists of $ n $ hours. Polycarp likes time management. That's why he has a fixed schedule for each day — it is a sequence $ a_1, a_2, \dots, a_n $ (each $ a_i $ is either $ 0 $ or $ 1 $ ), where $ a_i=0 $ if Polycarp works during the $ i $ -th hour of the day and $ a_i=1 $ if Polycarp rests during the $ i $ -th hour of the day.

Days go one after another endlessly and Polycarp uses the same schedule for each day.

What is the maximal number of continuous hours during which Polycarp rests? It is guaranteed that there is at least one working hour in a day.

## 说明/提示

In the first example, the maximal rest starts in last hour and goes to the first hour of the next day.

In the second example, Polycarp has maximal rest from the $ 4 $ -th to the $ 5 $ -th hour.

In the third example, Polycarp has maximal rest from the $ 3 $ -rd to the $ 5 $ -th hour.

In the fourth example, Polycarp has no rest at all.

## 样例 #1

### 输入

```
5
1 0 1 0 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
0 1 0 1 1 0
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7
1 0 1 1 1 0 1
```

### 输出

```
3
```

## 样例 #4

### 输入

```
3
0 0 0
```

### 输出

```
0
```

# 题解

## 作者：wuwenjiong (赞：3)

## 题意：
输入一个长度为 $n$ 的字符串，字符串为**环形序列**，只由 $0,1$ 两种字符构成，求最长的连续是 $1$ 的子串的长度。
#### 样例1分析：
样例输入：
```cpp
5
1 0 1 0 1
```
样例输出：
```cpp
2
```
字符串改成环形如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/izcq6k4q.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

不难看出，最长的连续是 $1$ 的子串的长度为 $2$ ，所以输出 $2$ 。那么，我们可以发现：当字符串的开始和末尾都是 $1$ 的子串时，得将两个子串的长度相加，得到的长度和再来判断是否是最长的，最后再输出长度。代码实现如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,k,f,s;
int main(){
	int a,n,i,x;
	cin>>n;//输入字符串的长度
	for(i=1;i<=n;i++){
		cin>>a;//输入字符
		if(a==1)//如果为1就记录子串的长度
			k++;
		else{//当不是1时，前一个1的子串长度是已知的
			if(f==0)//当它是最开始的子串时，记录长度
				f=1,x=k;
			if(k>s)//如果大于就改值
				s=k;
			k=0;
		}
	}
	if(k!=0)//判断环形的情况
		k+=x;
	s=max(s,k);//判断
	cout<<s;//输出
	return 0;
}
```
谢谢！！！

---

## 作者：1saunoya (赞：2)

># [更好的阅读体验](https://www.cnblogs.com/qf-breeze/p/10564158.html)
>告诉你一天n件事情
~~~
a[i]为1是休息 a[i]为2是工作
~~~
>求最长连续的休息时间（即最长的1
~~~
可以作为环状来求。(即环状最长的1
~~~

>这题就可以用前缀和贪心等什么操作。。
>然后用$ans1ans2$~~瞎搞~~


~~~
#include <bits/stdc++.h>
using namespace std;
typedef long long LL ;
inline LL In() { LL res(0),f(1); register char c ;
    while(isspace(c=getchar())) ; c == '-'? f = -1 , c = getchar() : f = 1 ;
    while(res = (res << 1) + (res << 3) + (c & 15) , isdigit(c=getchar())) ; return res * f ;
}
int n ;
int a[200000+5] ;
int cnt[200000+5] ;
int flag = 1 ;
int ans = 0 ;
int ans1 = 0 ;
int ans2 = 0 ;
signed main() {
    n = In() ;
    for(register int i=1;i<=n;i++) a[i] = In() ;//读入
    for(register int i=1;i<=n;i++)
    if(a[i]==1) cnt[i]=cnt[i-1]+1,ans1=max(ans1,cnt[i]);//求前缀和 即当前最长的1 ans1储存最大值
    else {
        if(flag) ans2+=(i-1),flag=0;//储存最前面的一段1
        cnt[i]=0;
    }
    if(cnt[n]) ans = cnt[n] + ans2;//如果第n个位置有连在一起的。
//则数字为 cnt[n]+ans2
    cout << max(ans,ans1) << endl ;//ans求的是序列中最大值。 ans是首尾环状。 要求的是最长的则取max
    return 0 ;
}
~~~

---

## 作者：清清老大 (赞：1)

## 思路

本题可以把首尾字符串加起来分别处理，但是有更简单的方法。

因为字符串是环形，所以需要把字符串复制一遍，这样首位就能相连了，可以用普通的方法求连续的 $1$ 。

例如把 $10101$ 变为 $1010110101$ ，首位的 $1$ 相连，再循环求一遍就得到答案是 $2$ 。

### 公式：$a_{i+n}=a_i$

## 代码

```
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,a[540097],sum = 0,maxsum = 0;
    cin >> n;
    for(int i = 0;i < n;i ++)
    {
        cin >> a[i];
        a[i + n] = a[i]; // 复制一遍字符串
    }
    //把复制后的字符串当成普通字符串处理，注意长度变为2n
    for(int i = 0;i < 2 * n;i ++)
    {
        if(a[i] == 1)
        {
            sum ++;
        }
        if(a[i] == 0)
        {
            maxsum = max(sum,maxsum);
            sum = 0;
        }
    }
    cout << maxsum;
}
```


---

## 作者：happybob (赞：1)

本题是破坏成链的模板题，其公式为：

$\LARGE a_{i + n} = a_i$

比如我们造一组数据：

```cpp
5
1 0 0 0 1
```
用这个公式将这个数组变为：

```cpp
1 0 0 0 1 1 0 0 0 1
```
你会发现原本一头一尾的1竟然连在了一起！那么接下来我们循环一遍就A过去了！

代码：

```cpp
#include <iostream>
using namespace std;

bool a[400005];

int main()
{
    int n;
    cin >> n;
    for(register int i = 1; i <= n; i++)
    {
        cin >> a[i];
        a[i + n] = a[i];
    }
    int max = 0, cnt = 0;
    n <<= 1;
    for(register int i = 1; i <= n; i++)
    {
        if(a[i]) cnt++;
        else {max = (cnt > max ? cnt : max); cnt = 0;}
    }
    max = (cnt > max ? cnt : max);
    cout << max << endl;
    return 0;
}
```



---

## 作者：wlzhouzhuan (赞：1)

这道题有两种方法：

第1种，先扫一遍序列，然后特殊判断一下头和尾的情况，但这样比较复杂，容易出小问题。

第2种，破环成链，我们将序列同等复制一遍，这样就可以将首尾拼接起来了。


破环成链，即：$a[i+n]=a[i]$


$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define RE register
#define rep(i, l, r) for (RE int i = l; i <= r; i++)
#define req(i, l, r) for (RE int i = l; i >= r; i--)
#define For(i, l, r) rep(i, l, r - 1)

void read(int &x) {
    x = 0; int f = 1;
    char op = getchar();
    while (!isdigit(op)) {
        if (op == '-') f = -1;
        op = getchar();
    }
    while (isdigit(op)) {
        x = 10 * x + op - '0';
        op = getchar();
    }
    x *= f;
}

const int N = 400005;
int a[N], n;

int main() {
	read(n);
	rep(i, 1, n) {
		read(a[i]);
		a[i + n] = a[i];
	}
	n <<= 1;
	int ans = 0;
	for (int i = 1; i <= n; ) {
		if (!a[i]) i++;
		int tot = 0;
		while (a[i]) {
			tot++; i++;
		}
		ans = ans > tot ? ans : tot;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：1)

> 题意：给你n个数，每个数都是0或1，找出最长的连续“1”（可以由数列尾接到数列头--样例1）

解法：和A题一样，模拟。。。

先找出数列中连续1的个数的最大值，再和（队头连续1的个数+队尾连续1的个数）比个max。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for (i=x;i<=y;i++)
typedef long long ll;
const long long INF=214748347;

int max(ll x,ll y)//这里手写了个max函数
{
	if (x>y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

int main()
{
	int n;
	cin>>n;
	bool f[n+1];
	int i;
	rep(i,1,n)
	{
		cin>>f[i];
	}
	ll maxv,cnt;
	cnt=0;
	maxv=-1;
	rep(i,1,n)
	{
		if (f[i]==1)
		{
			cnt++;
			maxv=max(cnt,maxv);//找数列中连续1的个数的最大值
		}
		else
		{
			cnt=0;
		}
		maxv=max(cnt,maxv);
	}
	ll cnt2;
	cnt2=0;
	rep(i,1,n)
	{
		if (f[i]==1)
		{
			cnt2++;
		}
		else
		{
			break;
		}
	}
	for (i=n;i>=1;i--)//计算队头连续1的个数+队尾连续1的个数
	{
		if (f[i]==1)
		{
			cnt2++;
		}
		else
		{
			break;
		}
	}
	cout<<max(cnt2,maxv)<<endl;和（队头连续1的个数+队尾连续1的个数）比大
	return 0;
}
```

---

## 作者：zhy12138 (赞：0)

本文同步发表于[我的博客](https://zhy12138.github.io/2019/03/24/CF-1141-div3/)

简单题，直接读入01串，然后查询最长的全为1的子串长度即可。

由于Polycarp每天用相同的时间表，还要将答案与最长1前缀和最长1后缀的长度和做比较。

注：本题保证至少有一个0，所以不用考虑全为1的情况

```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<ctime>
#define ll long long
using namespace std;
inline int read()
{
    int kkk=0,x=1;
    char c=getchar();
    while((c<'0' || c>'9') && c!='-')
        c=getchar();
    if(c=='-')
        c=getchar(),x=-1;
    while(c>='0' && c<='9')
        kkk=(kkk<<3)+(kkk<<1)+(c-'0'),c=getchar();
    return kkk*x;
}
int n,a[200001],ans;
int main()
{
	n=read();
	int num=0;
	for(register int i=1;i<=n;++i)
	{
		a[i]=read();
		if(a[i]==0)
		{
			ans=max(ans,num);
			num=0;
		}
		else
			++num;
	}
	int ar_ans=0;
	for(register int i=1;i<=n;++i)
		if(a[i]==0)
		{
			ar_ans+=(i-1);
			break;
		}
	for(register int i=n;i>=1;--i)
		if(a[i]==0)
		{
			ar_ans+=(n-i);
			break;
		}
	printf("%d\n",max(ans,ar_ans));
    return 0;
}
```

---

