# 「MXOI Round 1」宝箱

## 题目描述

小 C 喜欢在一款叫做渊深的游戏中收集宝箱。

现在，小 C 在一条数轴上，他在数轴的原点处。

同时，在这条数轴上还有两个宝箱，它们的坐标分别为 $a$ 和 $b$。

只要小 C 移动到某个宝箱的位置，就认为小 C 收集到了这个宝箱。特殊地，如果小 C 初始时就在某个宝箱的位置，那么他可以直接收集到这个宝箱；如果两个宝箱在同一个位置，那么他可以同时收集这两个宝箱。

小 C 每次可以沿着这条数轴的正方向或负方向移动一个单位长度。小 C 想知道，收集到这两个宝箱至少需要移动多少次？

## 说明/提示

#### 【样例解释 #1】

小 C 可以先沿着数轴的负方向移动 $1$ 次，再沿着数轴的正方向移动 $2$ 次。

可以证明小 C 至少需要移动 $3$ 次。

#### 【样例解释 #2】

小 C 可以直接沿着数轴的负方向移动 $5$ 次。

可以证明小 C 至少需要移动 $5$ 次。

#### 【数据范围】

对于 $100\%$ 的数据，$\vert a\vert,\vert b\vert \le 200$。

|测试点编号|特殊性质|
|:---:|:---:|
|$1\sim3$|保证 $\vert a\vert,\vert b\vert \le 1$|
|$4\sim6$|保证 $ab=0$|
|$7\sim10$|无|

## 样例 #1

### 输入

```
1 -1```

### 输出

```
3```

## 样例 #2

### 输入

```
-5 0```

### 输出

```
5```

## 样例 #3

### 输入

```
51 -154```

### 输出

```
256```

# 题解

## 作者：Coffee_zzz (赞：22)

### 分析

显然地，我们先假设我们首先移动到了一个宝箱，另一个宝箱还没有被收集，那么移动到另一个宝箱所需要移动的次数就是两个宝箱之间的距离，即 $|a-b|$。

那我们只需要先移动到离自己近的宝箱，然后再移动到另一个宝箱即可，所以答案为 $\min(|a|,|b|)+|a-b|$。

当然本题也可以根据两个宝箱在同侧还是异侧分类，直接计算答案即可。

### Code

```c++
#include <bits/stdc++.h>
using namespace std;
int main(){
	int a,b;
	cin>>a>>b;
	cout<<min(abs(a),abs(b))+abs(a-b);
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：10)

# P9581 宝箱 题解

其实本题很简单，简单判断一下 $a$ 和 $b$ 的正负性即可。

### 解析

开宝箱的路程无非是 原点 $\rightarrow b \rightarrow a$，或原点 $\rightarrow a \rightarrow b$。

因此我们知道，$a\leftrightarrow b$ 的这段路是一定要跑的，所以我们要尽可能压缩的是原点到任意一个宝箱的距离。那么肯定选更近的那个啦。

所以路程 $S=\text{min}(|a|,|b|)+|b-a|$。

### 代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int a,b;
int main(){
	cin>>a>>b;
	if(abs(a)<abs(b)){
		cout<<abs(a)+abs(b-a);
	}
	else{
		cout<<abs(b)+abs(b-a);
	}
return 0;
}
```

### 题外话

建议评红。

---

## 作者：佬头 (赞：6)

## Description
数轴上有两个[**宝箱**](https://www.luogu.com.cn/problem/P9581)，坐标分别为 $a$ 和 $b$，求从原点出发收集完宝箱的最小移动距离。

## Solution
分两种情况:
1. 当两个宝箱在原点异侧时，则肯定先去收集距离原点最近的宝箱，再返回原点去收集另一个宝箱，则答案为 $\min(|a|,|b|)+|a|+|b|$。
2. 当两个宝箱在原点同侧时，则可以直接去收集距离原点最远的宝箱，途中收集另一个宝箱，则答案为 $\max(|a|,|b|)$。

## Code
```cpp
#include <iostream>
using namespace std;
int a, b;
int read(){
	int x = 0;
	char a = getchar();
	bool tf = 0;
	while(a < '0' || '9' < a){
		if(a == '-') tf = 1;
		a = getchar();
	}
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return tf? -x: x;
}
void write(int x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
int main(){
	a = read(), b = read();
	if(a >= 0 && b >= 0) write(max(a, b));
	else if(a <= 0 && b <= 0) write(max(-a, -b));
	else if(a < 0 && b > 0) write(min(-a, b) + b - a);
	else write(min(a, -b) + a - b);
	return 0;
}
```


---

## 作者：wdd2929 (赞：4)

本题涉及内容：初一「有理数」的知识。

---
举个例子：假设小 C 在 $114$ 的位置，现在要走到 $514$，那么他要走多少格？

用~~多年的小学数学知识~~可知，他要走 $514-114=400$ 格。

当然，你也可以用 $114-514=-400$，但是这样会算出来负数，移动的距离总不能是负数吧（初中范围内）？所以给 $-400$ 求个绝对值就行了，结果也是 $400$。


**附：**

> 绝对值的几何定义：一个数在数轴上到原点的距离。

> 大白话：正数的绝对值等于它本身，负数的绝对值等于其相反数，$0$ 的绝对值等于 $0$。

> 符号表示：$a$ 的绝对值表示为 $|a|$。


因此，我们可以得到一个结论：对于数轴上两点 $a$ 和 $b$ 间距离等于它们的差的绝对值，用式子表达 $a$ 到 $b$ 的距离就是 $|a-b|$。

本题也是同理，虽然说要到达两个点，我们可以把这段路分成两部分：到 $a$ 和到 $b$ 的。

1. 从原点到 $a$，是 $|a-0|$ 的结果，也就是 $|a|$。
1. 从 $a$ 到 $b$，是 $|a-b|$ 的结果。

然后，两式相加，就是最终答案。

---
但是有个问题，当 $|a|\le |b|$ 时，上述思路才能算出最优解。如果 $|a|>|b|$， 这个时候先走 $|a|$ 格，就比先走 $|b|$ 格要远了，不是最优解。

如图：

![A~FQ5M`SQB4C53SDG2J5__W.png](https://pic.ziyuan.wang/2023/08/26/guest_8eb0f48cd90e0.png)



红色线是非最优解，蓝色线是最优解。

因此，如果 $|a|>|b|$ 的话，我们就把 $a$ 和 $b$ 的值调换过来。

以下给出我的核心代码：



```cpp
int main(){
    int a,b;
    cin>>a>>b;
    if(abs(a)>abs(b)){
        swap(a,b);
    }
    cout<<abs(a)+abs(a-b);
    return 1;
}
```

```abs``` 函数是求绝对值函数，至于怎么写，我就不说了。

---

## 作者：lemon_qwq (赞：2)

签到题，分类讨论即可，但是大佬们的做法不用这么麻烦，如果想要了解可以参考别的题解。

首先考虑 $a,b$ 两数有一个数是 $0$ 的情况，很明显出生点就能拿到其中的一个宝箱，直接输出另一个数即可，如果两数都是 $0$，直接输出 $0$，因为刚出生你就拿到了两个宝箱。

然后，如果两数都是负数或整数，输出绝对值较大的那个数即可，因为去拿大的那个宝箱的时候就会路过小的宝箱。

如果一负一正，先去拿绝对值小的那个宝箱，因为这段路程要走两遍，我们要最小化路程。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b;
	cin>>a>>b;
	if(a==0){
		cout<<abs(b)<<endl; 
		return 0;
	}
	else if(b==0){
		cout<<abs(a)<<endl;
		return 0;
	}
	if(a<=0&&b>=0||a>=0&&b<=0){
	    int aa=abs(0-a),bb=abs(0-b);
	    cout<<min(aa*2+bb,bb*2+aa)<<endl;
	}
	else{
	    cout<<max(abs(a),abs(b));
	}
	return 0;
}
```

完结撒花！

---

## 作者：FurippuWRY (赞：1)

题意：设数轴上有两定点 $A,B$，一动点 $P$ 位于原点，求 $P$ 到达 $A,B$ 所需的最短路径的距离。  

------------

本题需分类讨论。

设 $a,b$ 分别为 $A,B$ 的坐标。

若 $A,B$ 都同时位于点 $P$ 左侧或右侧，即坐标正负性相同，此时 $P$ 到达 $A,B$ 的最短距离就是 $\max(|a|,|b|)$，因为 $P$ 可以经过一点到达另一点。

若 $A,B$ 坐标正负性不同，则 $P$ 到达一点后还需要原路返回至原点，再向另一点运动，此时最短距离就是 $2\times\min(|a|,|b|)+\max(|a|,|b|)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

int a, b, absa, absb;

int main() {
	cin >> a >> b;
	absa = abs(a);
	absb = abs(b);
	if ((a >= 0 && b >= 0) || (a < 0 && b < 0)) {
		cout << max(absa, absb);
	}
	else
	cout << 2 * min(absa, absb) + max(absa, absb);
	return 0;
}
```

---

## 作者：_colin1112_ (赞：1)

+ 一道简单的模拟题。


## 思路

需要考虑 $5$ 种情况。

1. 如果 $a=0$，输出 $\vert b\vert$。

2. 如果 $b=0$，输出 $\vert a\vert$。

3. 如果 $a=b$，输出 $\vert a\vert$ 或 $\vert b\vert$。

4. 如果 $a$ 与 $b$ 同号，输出 $\max(\vert a\vert,\vert b\vert)$。

5. 如果以上 $4$ 种情况都没有成立，则输出 $\min(\vert a\vert,\vert b\vert)\times 2 + \max(\vert a\vert,\vert b\vert)$。

按照上面的规则进行模拟即可。

## AC Code

```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define ll long long

using namespace std;
const int E=1e6+5;
ll a,b;
int main(){
    cin >>a>>b;
    if(a==0){
        cout <<abs(b);
    }
    else if(b==0){
        cout <<abs(a);
    }
    else if(a==b){
        cout <<abs(a);
    }
    else if((a<0 && b<0) || (a>0 && b>0)){
        cout <<max(abs(a),abs(b));
    }
    else cout <<min(abs(a),abs(b))*2+max(abs(a),abs(b));
    return 0;
}
```

---

## 作者：zhang_Jimmy (赞：1)

这题我们可以分成两种情况：

1. $a$ 和 $b$ 异号。  
   如果 $a$ 和 $b$ 异号的话，考虑贪心，先取离原点距离最近的宝箱，然后再去取另一个宝箱，答案为 $\min( \left\vert a \right\vert,\left\vert b \right\vert) + \left\vert a \right\vert + \left\vert b \right\vert$。
   
   
   以下是一个例子（$a = -3, b = 2$）：
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/amipiqo9.png)
2. $a$ 和 $b$ 同号。  
   如果同号的话，可以先去取最近的一个宝箱，再走 $\left\vert a - b \right\vert$ 的距离，那么答案就为 $\min(\left\vert a \right\vert,\left\vert b \right\vert) + \left\vert a - b \right\vert$，简化为 $\max(\left\vert a \right\vert,\left\vert b \right\vert)$。
   
   以下是一个例子（$a = 3, b = 7$）：
   
   ![](https://cdn.luogu.com.cn/upload/image_hosting/91bmeygo.png)
   
代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL a, b;
int main(){
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);
    cin >> a >> b;
    if(min(a, b) < 0 && max(a, b) > 0){
        cout << llabs(a) + llabs(b) +llabs(min(llabs(a), llabs(b)));
    }else{
        cout << max(llabs(a), llabs(b));
    }
    return 0;
}

```


---

## 作者：zly2009 (赞：1)

分讨一下：

1. $a,b$ 均为正数，则只需朝正方向移动，则需要移动两坐标间最大值。

2. $a,b$ 均为负数，则只需朝负方向移动，则需要移动两坐标间最小值的绝对值（或两坐标间绝对值的最大值）。

3. $a,b$ 符号不同，则要到其中一个坐标后，再走个两坐标间距离，由于求最小值，则另加上两坐标绝对值的最小值。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int a,b;
    cin>>a>>b;
    if(a>0&&b>0)cout<<max(a,b);
    else if(a<0&&b<0)cout<<abs(min(a,b));//也可写成 max(abs(a),abs(b))。
    else cout<<abs(a-b)+min(abs(a),abs(b));
}
```

当 $a>0$ 时，$|a|=a$，所以代码可再次化简，同号的时候朝同一方向，所以需要移动两坐标间绝对值的最大值。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int a,b;
    cin>>a>>b;
    cout<<(a&&b&&a/b>0?max(abs(a),abs(b)):abs(a-b)+min(abs(a),abs(b)));
}
```

---

## 作者：__YancBuxIya (赞：0)

## P9581 宝箱 题解

-----------------
### 题目大意：

已知两个宝箱，从原点开始，求最少的脚步到达两个宝箱所在地。

-----------------

### 题目解释： 

根据题目可知，数轴上的点会有负数，所以我们可以现将坐标进行求绝对值。然后根据贪心思想，我们肯定是先走离原点近的宝箱，再走远的。所以最终答案就是：
$$ Ans=|L_a-L_b|+min(|a|,|b|) $$


-----------------

### 代码：

```cpp

#include<algorithm>
#include<stdio.h>
using namespace std;
int a,b;
int main(){
	scanf("%d%d",&a,&b);
	int ka=abs(a),kb=abs(b);
	printf("%d\n",min(ka,kb)+abs(a-b));
	return 0;
}
  
``` 

---

## 作者：zwyyy (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/P9581)

## 思路
这是一道比较简单的题目，直接分类讨论即可。

- $a,b\ge0$，直接输出较大的数；
- $a,b<0$，直接输出绝对值更大的数；
- 两个宝箱在原点两侧，就先设绝对值更小的数的绝对值为 $x$，另一个数的绝对值为 $y$，输出 $2\times x+y$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int a, b, ans;
	scanf("%d%d", &a, &b);
	if(a >= 0 && b >= 0){
		ans = max(a, b);
	}
	else if(a < 0 && b < 0){
		ans = abs(min(a, b));
	}
	else{
		ans = 2 * min(abs(a), abs(b)) + max(abs(a), abs(b));
	}
	printf("%d", ans);
	return 0;
}
```
[AC](https://www.luogu.com.cn/record/122917971)

---

## 作者：Xdwjs (赞：0)

分两种情况讨论。

第一种情况是 $a$ 和 $b$ 分别在原点两端，我们需要先去绝对值较小的一端拿到宝箱，再去另一端拿到另外一个宝箱。

第二种情况是 $a$ 和 $b$ 在原点的同一端，这个时候我们直接取最大的绝对值即可。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b;
    cin>>a>>b;
    if(a>b) swap(a,b);
    if(a<0&&b>0)
    {
        a=abs(a);
        cout<<min(a,b)+a+b;
    }
    else
    {
        a=abs(a);
        b=abs(b);
        cout<<max(a,b);
    }
    //system("pause");
    return 0;
}
```

---

## 作者：zjjc1104111 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9581)

# 思路

这题分 ${3}$ 种情况。

1. ${a}$ 和 ${b}$ 在同一位置。

这时，我们只需要找到到这个点到原点的距离，再直接输出。

2. ${a}$ 和 ${b}$ 在原点的其中一侧。

那我们只需要找出哪个点距离原点更远，再输出距离就行了，因为在拿到这个宝箱时，另一个宝箱已经被我们顺路拿到了。

3. ${a}$ 和 ${b}$ 在原点两侧。

当我们遇到这种情况时，可以先算出两点到原点的距离，离得更近的那个点就需要走两次，离得远的就只需要走一次。

那我们只需要判断满足哪个条件就行了。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int a,b;
	cin>>a>>b;
	if(a==b) cout<<abs(a);
	else if(a*b>=0) cout<<max(abs(a),abs(b));//a*b大于等于0说明在同一侧
	else cout<<min(abs(a),abs(b))*2+max(abs(a),abs(b));
	return 0;
}

```


---

