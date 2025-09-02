# Tennis Championship

## 题目描述

Famous Brazil city Rio de Janeiro holds a tennis tournament and Ostap Bender doesn't want to miss this event. There will be $ n $ players participating, and the tournament will follow knockout rules from the very first game. That means, that if someone loses a game he leaves the tournament immediately.

Organizers are still arranging tournament grid (i.e. the order games will happen and who is going to play with whom) but they have already fixed one rule: two players can play against each other only if the number of games one of them has already played differs by no more than one from the number of games the other one has already played. Of course, both players had to win all their games in order to continue participating in the tournament.

Tournament hasn't started yet so the audience is a bit bored. Ostap decided to find out what is the maximum number of games the winner of the tournament can take part in (assuming the rule above is used). However, it is unlikely he can deal with this problem without your help.

## 说明/提示

In all samples we consider that player number $ 1 $ is the winner.

In the first sample, there would be only one game so the answer is $ 1 $ .

In the second sample, player $ 1 $ can consequently beat players $ 2 $ and $ 3 $ .

In the third sample, player $ 1 $ can't play with each other player as after he plays with players $ 2 $ and $ 3 $ he can't play against player $ 4 $ , as he has $ 0 $ games played, while player $ 1 $ already played $ 2 $ . Thus, the answer is $ 2 $ and to achieve we make pairs $ (1,2) $ and $ (3,4) $ and then clash the winners.

## 样例 #1

### 输入

```
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
```

### 输出

```
2
```

## 样例 #4

### 输入

```
10
```

### 输出

```
4
```

# 题解

## 作者：Pkixzx (赞：3)

初看此题，毫无头绪，于是，我便想到了**递推**。

输入2时，输出1。

输入3时，输出2。

输入4时，输出2。

输入5时，输出3。

输入6时，输出3。

输入7时，输出3。

输入8时，输出4。

……………………

结果很显然，结果呈现了一个递增的状态（个数递增，数也递增）。

那么代码就简单多了，只要枚举数的个数就可以了。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,m,t=1,t1=1,t2=2,t3=3;//不开long long见祖宗
	cin>>n;
	while(t3<=n){
		t1=t2;
		t2=t3;
		t3=t1+t2;//枚举现在的个数
		t++;
	}
	cout<<t<<endl;
} 
```


---

## 作者：Mickey_snow (赞：2)

CF767E：递推，贪心。

这又是一道很有意思的CF题目。

题目大致意思是要我们安排一次有 $n$ 名参赛者参与的竞赛，在满足每场对决中的两名参赛者此前参加的比赛相差不超过1的前提下尽可能让竞赛的总场次多，要求这个最多的场次数量。

假设 $f(x) = $ 安排 $x$ 场比赛所需要的最少参赛者，那么题目要我们求的，就是一个最大的 $j$ 满足 $f(j) \leq n$ .所以我们需要解决的就是 $f$ 函数。

可以确定的是全部比赛结束之后只有1名参赛者，而且决赛是这名参赛者与亚军的对决，如果我们将规模缩小，$f$ 函数对应安排应该是与下图很像的。

![](https://cdn.luogu.com.cn/upload/pic/29115.png )

即，尽可能让两位已经参加场数相差为1的参赛者对决，按照这个逻辑，冠军和亚军在决赛之前参加的比赛场数应该分别为 $n-1$ 和 $n - 2$ ，而图中的这两个子树分别对应着 $f(n-1)$ 和 $f(n-2)$ 名参赛者，也就是说 $f(n) = f(n-1) + f(n-2)$ .

这样我们就可以递推 $f$ 函数了，边界条件为 $f(0) = f(-1) = 1$ .

AC代码如下：

```cpp
using System;

namespace CF767E
{
	class Program 
	{
		static void Main(string[] args) 
		{
			Int64 a = 1, b = 1, ans = 0, max = Convert.ToInt64(Console.ReadLine());

			for(int i = 1; true; i++) {
				ans = a + b;
				if(ans > max) {
					Console.WriteLine((i - 1).ToString());
					return;
				}
				a = b;b = ans;
			}
		}
	}
}

```

---

## 作者：QWQ_123 (赞：0)

找规律。

看一个 $dep = 3$ 的：

![](https://cdn.luogu.com.cn/upload/image_hosting/7rptpxof.png)

我们发现其实就是在长度为 $2dep$ 的链上挂了一些其他的更小的情况。

比如在 $1$ 上挂了个 $dep=1$ 的点。

于是考虑 $f_i$ 表示深度为 $i$ 是所需的最小点数，$s_i$ 表示前 $i$ 个 $dep$ 的最小点数的总和。

那么 $f_i=2i+s_{i-3}+s_{i-4}$，然后就可以递推做了。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

long long n;
ll f[100], s[100];

int main() {
	cin >> n;
	if (n == 2) return puts("1"), 0;
	else if (n <= 4) return puts("2"), 0;

	f[0] = s[0] = 1, f[1] = 2, f[2] = 4, s[1] = 3, s[2] = 7;
	for (int i = 3; ; ++i) {
		f[i] = 2 * i + s[i - 3];
		if (i >= 4) f[i] += s[i - 4];
		// cout << f[i] << endl;
		if (f[i] >= n) {
			printf("%d\n", i);
			return 0;
		}
		
		s[i] = s[i - 1] + f[i];
	}
	return 0;
}

---

## 作者：gxxjqqiang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF735C)


------------


可以看一下英文题面

刚看题的时候一脸懵，不过仔细推一下还是挺好做的。



------------
**思路**

我们可以发现，要让比赛次数（树的深度）最多，且符合题目要求（最大深度差不超过 $1$），总共 $n$ 人的比赛我们让赛了 $n-1$ 和 $n-2$ 场的人来打，以此类推。诶，就是斐波那契数列啊。



------------
**CODE**

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,x=1,y=2,z=3,cnt=1;
int main(){
    scanf("%lld",&n);
    while(z<=n){x=y;y=z;z=x+y;cnt++;}
    return !printf("%lld",cnt);
}
```


------------
最后提醒一下，不开 long long 见祖宗哦。



---

## 作者：fisheep (赞：0)

## 想法:
首先看到翻译觉得这是一道图论题，但是根据原文发现并不是这样的(虽然英语蒟蒻)。

通过比赛场数分析：

* 赢1场：至少需要2个人

* 赢2场：至少需要3个人

* 赢3场：至少需要 至少赢2场人数 + 至少赢1场人数

* 赢4场：至少需要 至少赢3场人数 + 至少赢2场人数

* 赢5场：至少需要 至少赢4场人数 + 至少赢3场人数

......

* 赢n场：至少需要 至少赢n-1场人数 + 至少赢n-2场人数

所以我们只需要通过枚举场数判断参赛人数是否达到要求即可。

简单点来说就是：$\quad \sum\limits_{i=1}^nf[i]$

其中$f[i]$表示斐波那契数列。

## Code
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
inline int read(){
  int x=0,f=1;
  char ch=getchar();
  while(ch>'9'||ch<'0'){
    if(ch=='-') f=-1;
    ch=getchar();
  }
  while(ch>='0'&&ch<='9'){
    x=(x<<1)+(x<<3)+(ch^48);
    ch=getchar();
  }
  return x*f;
}
int n,ans=1;
signed main(){
      n=read();
  int x=1, y=2, z=x+y;
      while (z<=n) {
          x=y;y=z;z=x+y;
          ans++;
      }
      printf("%lld\n", ans);
  }

```


---

## 作者：__Hacheylight__ (赞：0)

思路：不要只往人数上想，可以往场数上想：

赢 1 把： 至少要 2 个人。

2把：至少要 3个人。

3把：至少为 至少2把的人数+至少1把的人数。

4把：至少为 至少3把的+至少2把的（因为比赛次数差不能超过1）。

i 把：f[i-1]+f[i-2];


斐波那契数列很大，所以把f[i]全部算出找就行。

```cpp
#include <bits/stdc++.h>
using namespace std ;
typedef long long ll ;
ll n ;

int main(){
    scanf("%lld", &n) ;
    ll ans = 1, a = 1, b = 2, c = a + b ;
    while (c <= n) {
        a = b ;
        b = c ;
        c = a + b ;
        ans++ ;
    } 
    printf("%lld\n", ans) ;
}

```

---

