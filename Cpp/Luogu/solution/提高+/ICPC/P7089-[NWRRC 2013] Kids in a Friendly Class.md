# [NWRRC 2013] Kids in a Friendly Class

## 题目描述

凯文的班级里有女生也有男生。他们中有些人是朋友，有些人不是。但是，如果A认为B是他的朋友，那么B也认为A是他的朋友。

有趣的是，每个女生都有 a 个女性朋友和 b 个男性朋友，而每个男生都有 c 个女性朋友和 d 个男性朋友。

凯文不记得自己班级的人数。请算出班级的人数，使得班级人数尽可能少，同时又能满足上面的条件。

## 样例 #1

### 输入

```
1 2 1 2
```

### 输出

```
2 4
1 2
1 3
1 5
2 4
2 6
3 4
3 5
4 6
5 6
```

# 题解

## 作者：AnteAntibe (赞：3)

一个晚上，我打开了这道题……    
思考良久无果，打开题解。发现题解居然没有讲述具体的思路？？无奈继续思考……

于是就有了这篇题解。

## Description

 首先读题。    
 
 我们可以将每一个学生抽象为一个点，于是答案就变成了一张图。注意到有“**如果 A 认为 B 是他的朋友，那么 B 也认为 A 是他的朋友**”一句话，因此图中的连边是双向边。   
 
现在分别规定每个男、女连向同性、异性的边数，我们要做的就是构造出一个满足该条件的图。同时我们需要最小化点的边数。

## Solution

乍一看好像很没有头绪？ 于是手玩一下样例。

![](https://cdn.luogu.com.cn/upload/image_hosting/y1f74xpa.png)

图长这样。  

相信大家在画这个图的时候多少注意到：和同性连边、和异性连边是**相互独立**的两个过程。因为很显然，并不存在一个点即是女生又是男生。于是合法的点数只需要同时满足连得出同性、异性的条件即可。

先考虑异性。每个女性都拉出 $b$ 条边，那么总边数一定是 $b$ 的倍数，同理它也得是 $c$ 的倍数。于是我们可以很轻松的得到：    
$$m \times b = n \times c$$
换句话说：
$$\frac{c}{b} = \frac{m}{n}$$



接着考虑同性。看起来很简单：以女性举例，只需要有 $a$ 个人给这个点连线即可。样例好像可以跑对，但是实际上这个做法是存在问题的。 

同样先以女性举例：同性的好友关系一共 $m \times a$ 条，由于是双向边，所以边数共有 $\frac{m \times a}{2} $ 条。

发现问题了吗？如果 $m$ 与 $a$ 同为奇数，那么计算出的边数就不是一个整数。显然“连了半条边”这件事是不行的。$n$ 与 $b$ 的关系同理。于是同性间连边需要满足：    

- $m > a$ 并且 $n > d$。
- $m$ 与 $a$ 至少有一个为偶数，$n$ 与 $d$ 至少有一个为偶数。

求出满足如上条件的最小点数即可满足第一问。

现在问题只剩如何建边。只需要满足每个点连向异性、同性的边数没问题，那这个图怎么建都是对的。同时这题甚至没给数据范围，更不可能在复杂度上卡你，暴力建边即可。

我的做法是开个优先队列存一个点还有几条边没连，这样逻辑比较简单，只需要取队头一个点然后挨个连边连完就好了。应该有别的方法，不过我没试过。

程序：


```cpp
#include<bits/stdc++.h>
#define mkp make_pair 
#define pii pair<int ,int>
using namespace std;

int a ,b ,c ,d ,tmp1 ,tmp2 ,m ,n;

priority_queue<pair<int ,int> > q1 ,q2 ,q3 ,q4;

int main() {
	scanf("%d %d %d %d" ,&a ,&b ,&c ,&d);
	int tmp = __gcd(b ,c);
	tmp1 = c / tmp;
	tmp2 = b / tmp;
	m = c;
	n = b;
	for (; ;) {
		bool j1 = (m > a && n > d);
		bool j2 = (m % 2 != 1 || a % 2 != 1);
		bool j3 = (n % 2 != 1 || d % 2 != 1);
		if ((j1 && j2) && (j3 && j2)) {
			break;
		}
		m += tmp1;
		n += tmp2;	
	}
	printf("%d %d\n" ,m ,n);

    for (int i=1 ;i<=m ;i++) {
		q1.push(mkp(a ,i));
	}
	for (;q1.size();) {
		pii u = q1.top();
		q1.pop();
		for (;u.first > 0;) {
			u.first --;
			pii v = q1.top();
			v.first--;
			q1.pop();
			q1.push(v);
			printf("%d %d\n" ,u.second ,v.second);
		}
	}
	
	for (int i=1 ;i<=n ;i++) {
		q2.push(mkp(d ,m + i));
	}
	for (;q2.size();) {
		pii u = q2.top();
		q2.pop();
		for (;u.first > 0;) {
			u.first --;
			pii v = q2.top();
			v.first--;
			q2.pop();
			q2.push(v);
			printf("%d %d\n" ,u.second ,v.second);
		}
	}
	
	for (int i=1 ;i<=m ;i++) {
		q3.push(mkp(b ,i));
	}
	for (int i=1 ;i<=n ;i++) {
		q4.push(mkp(c ,m+i));
	}
	for(;q3.size();) {
		pii u = q3.top();
		q3.pop();
		for (;u.first > 0;) {
			u.first--;
			pii v = q4.top();
			v.first --;
			q4.pop();
			if (v.first > 0) {
				q4.push(v);
			}
			printf("%d %d\n" ,u.second ,v.second);
		}
	}
	
	return 0;
}
```

坑点还是有些的。注意取等条件。还有就是搞清楚六个字母分别代表什么，题目描述中的变量含义有一些反直觉。

---

## 作者：Daben1 (赞：3)

**题意简述**

凯文不知道班里的人数，女生有 $a$ 个女性，$b$ 个男性朋友。男生有 $c$ 个女性朋友和 $d$ 个男性朋友。

问班里男女生分别有多少人，还要求出每一对朋友。


------------

**思路分析**

一开始想打表，但是看到要求出每对朋友的对应关系就立刻发现这种方法不可能……但注意，**对应关系**！

我由对应关系想到了数据结构，因为这是多对多的关系，又由它联想到了**图**。

这道题没有什么太多图论的内容， 也就是说只要会建图就可以了。

用贪心来建边，然后判断数据即可。

**AC代码**
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int gcd(int a, int b) {
    if (b == 0)return a;
    return gcd(b, a % b);
}
int a, b, c, d;
bool check(int n, int m) {
    if (b > m) return false;
    if (c > n) return false;
    if (a >= n) return false;
    if (d >= m) return false;
    if (n % a != 0) return false;
    if (m % b != 0) return false;
    return true;
}
void getedge(int n, int m){
    priority_queue<pair<int, int> >Q;
    for (int i = 1; i <= n; i++)
        Q.push(make_pair(a, i));
    while (!Q.empty()) {
        pair<int, int> now = Q.top();
        Q.pop();
        for (int i = 0; i < now.first; i++) {
            pair<int, int> next = Q.top();
            Q.pop();
            printf("%d %d\n", now.second, next.second);
            next.first--;
            Q.push(next);
        }
    }

    for (int i = n + 1; i <= n + m; i++)
        Q.push(make_pair(d, i));
    while (!Q.empty()) {
        pair<int, int> now = Q.top();
        Q.pop();
        for (int i = 0; i < now.first; i++) {
            pair<int, int> next = Q.top();
            Q.pop();
            printf("%d %d\n", now.second, next.second);
            next.first--;
            Q.push(next);
        }
    }

    priority_queue<pair<int, int> >Q1;
    priority_queue<pair<int, int> >Q2;
    for (int i = 1; i <= n; i++)
        Q1.push(make_pair(b, i));
    for (int i = n + 1; i <= m + n; i++)
        Q2.push(make_pair(c, i));
    while (!Q1.empty()) {
        pair<int, int> now = Q1.top();
        Q1.pop();
        for (int i = 0; i < now.first; i++) {
            pair<int, int> next = Q2.top();
            Q2.pop();
            printf("%d %d\n", now.second, next.second);
            next.first--;
            if (next.first != 0)Q2.push(next);
        }
    }
}
int main() {
    cin >> a >> b >> c >> d;
    int t = gcd(b, c);
    int x = b / t, y = c / t;
    int n, m;
    for (n = b, m = c; n <= d || m <= a || (m & 1) && (a & 1) || (n & 1) && (d & 1); n += x, m += y);
    swap(n, m);
    cout << n << " " << m << endl;
    getedge(n, m);
}
```
**温馨提示：此题有SPJ，所以看到自己的结果与样例不一样没关系哦~**

---

