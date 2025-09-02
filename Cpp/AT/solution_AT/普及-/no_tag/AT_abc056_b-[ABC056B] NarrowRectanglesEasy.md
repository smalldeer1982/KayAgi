# [ABC056B] NarrowRectanglesEasy

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc056/tasks/abc056_b

シカのAtCoDeerくんは縦の長さ $ 1 $、横の長さ $ W $ の形をした長方形が二つ机に置いてあるのを見つけました。 机を二次元平面とみなすと、以下の図のように、一つ目の長方形は 縦は $ [0,1] $ の範囲を、横は $ [a,a+W] $ の範囲を占めており、二つ目の長方形は縦は $ [1,2] $ の範囲を、横は $ [b,b+W] $ の範囲を占めています。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_abc056_b/68a8078bba22e318c7b5c2dbb4f781f4c60ac220.png)

AtCoDeerくんは二つ目の長方形を横に動かすことで、一つ目の長方形と連結にしようと考えました。 長方形を横に動かさないといけない距離の最小値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1≦W≦10^5 $
- $ 1≦a,b≦10^5 $

### Sample Explanation 1

問題文中の図のようになっています。この場合左に $ 1 $ 動かすのが最小です。

### Sample Explanation 2

はじめから連結になっているため、動かす必要はありません。

## 样例 #1

### 输入

```
3 2 6```

### 输出

```
1```

## 样例 #2

### 输入

```
3 1 3```

### 输出

```
0```

## 样例 #3

### 输入

```
5 10 1```

### 输出

```
4```

# 题解

## 作者：alex_liu (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT2344)

# 思路
首先，简化图像

把两个矩形当做一个线段，放在数轴上，就成了这样
![图](https://cdn.luogu.com.cn/upload/image_hosting/zw62g4m7.png)
那第二个矩阵连接到第一个矩阵上的最小横向距离，不就是 $abs(b-a-w)$ 吗？？？

但是需要考虑 $a$ 图形在 $b$ 图形的右侧的情况，如图：
![图](https://cdn.luogu.com.cn/upload/image_hosting/gw7ygnjh.png)

最后就是特判：

当点 $a$ 在点 $b$ 与点 $b+w$ 中间时，第二个矩阵与第一个矩阵的最小横向距离就是 $0$ 啦！

![图](https://cdn.luogu.com.cn/upload/image_hosting/pg0tt6ik.png)


最期待的时刻：上代码！
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int main(){
	int w,a,b;
	cin>>w>>a>>b;//输入
	if(a>b)swap(a,b);//交换两个图形
	int q=b-a-w;//距离
	if(q>=0)cout<<q<<endl;//有距离
	else cout<<0<<endl;//无距离
	return 0;
}
```

本人的第一篇题解，点个赞呗

---

## 作者：lgvc (赞：4)

不妨设 $a \le b$。

考虑两种情况：

1.  两个矩形已经连接。

答案为 $0$。

2.  两个矩形尚未连接。

答案为 $b-a-W$。

代码：

```cpp
#include <bits/stdc++.h>
int A,B,W;
signed main(void) {
	scanf("%d %d %d",&W,&A,&B);
	if(A>B) std::swap(A,B);
	printf("%d",std::max(B-A-W,0));
    return 0;
}
```


---

## 作者：BlackPanda (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/AT2344)**

------------
### 题意：
给出两个长、宽分别为 $1$ 和 $w$ 的矩形，它们到原点的距离分别为 $a$ 和 $b$，将这两个矩形水平移动，合成一个长方形，求移动的最小距离。

------------
### 思路：
根据题目所给出的图得知：
- 这两个矩阵的水平最短距离为：$b-(a+W)$。
![](https://cdn.luogu.com.cn/upload/image_hosting/j3zae1za.png)

- 化简后得：$b-a-W$。
- 题目中并没有给定 $b$ 是大于 $a$ 的，而我们默认的是 $b>a$，所以在一开始就要判断 $a$ 和 $b$ 的大小关系。
- 最后要考虑特判，如果两个矩阵已经连接，答案就是 $0$。

------------
### code：
```cpp
#include <bits/stdc++.h>
using namespace std;

long long w,a,b; 

int main(){
	cin>>w>>a>>b;
	if(a>b){
		swap(a,b);
	}
	int sum=b-a-w;
	if(sum<0)	sum=0;
	cout<<sum<<endl;
	return 0;
}


```


---

## 作者：TsH_GD (赞：0)

### 题目的一点小问题

样例 $2$ 的输出应为 $0$。

在做的时候要注意。

## 解题

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT2344/68a8078bba22e318c7b5c2dbb4f781f4c60ac220.png)

由图可知，两个矩阵的最短直线距离为：`b-(a+w)=b-a-w`。

注：因为 $a$,$b$ 的位置不确定，在计算的时候要用绝对值。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long w,a,b;
int main(){
	cin>>w>>a>>b;
	int ans=abs(b-a)-w;
	if(ans>=0) cout<<ans;
	else cout<<0<<endl;
}
```

---

## 作者：xiaomuyun (赞：0)

# AT2344 [ABC056B] NarrowRectanglesEasy 题解
[题目传送门](https://www.luogu.com.cn/problem/AT2344)
## 题目分析
通过观察题目里的图可以发现，“将第二个矩阵连接到第一个矩阵上的最小横向距离”即为点 $a$ 和 $b$ 之间的距离减 $w$。

不过我们会发现，有可能一开始的时候两个长方形就是连在一起的。所以如果点 $a$ 和 $b$ 之间的距离是 $x$，那么输出的就是 $\max(x-w,0)$。
## 代码实现
```cpp
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
int a,b,w;
int main(){
	scanf("%d%d%d",&w,&a,&b);
	printf("%d\n",max(abs(b-a)-w,0));
	return 0;
}
```

---

## 作者：eEfiuys (赞：0)

题目：[AT2344](https://www.luogu.com.cn/problem/AT2344)
### 原图：
![before](https://cdn.luogu.com.cn/upload/image_hosting/0yojkymn.png)
- 要连接两个矩形：
	- 纵坐标：
		- 固定，不用考虑。
	- 横坐标：
		- 让左边矩形的右端点 $a+w$ 与右边矩形的左端点 $b$ 重合。
### 移动后的图：
![after](https://cdn.luogu.com.cn/upload/image_hosting/1e4ich98.png)
- 可以发现，移动的距离就是 $b-(a+w)$。
- 如果本来就连接，即 $(a+w) \geq b$，就输出```0```。
- 当 $(a+w) \geq b$ 时, $b-(a+w) \leq 0$，因此不用判断，直接输出 $max(0,b-(a+w))$ 即可。
- 题目中并没有说 $a \leq b$ ，为了方便，我们默认 $a$ 在 $b$ 的左侧，即当 $a > b$ 时交换 $a$ 与 $b$。

------------

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int w,a,b;
signed main()
{
	cin>>w>>a>>b;
	if(a>b) //a在b的右侧。
		swap(a,b);
	cout<<max(0,b-(a+w))<<endl; //AT的题文末记得换行。
	return 0;
}
```

---

## 作者：Black_Porridge (赞：0)

这道题又没翻译orz 

于是乎我只能当一把翻译了!

[原题戳我](https://atcoder.jp/contests/abc056/tasks/abc056_b)

~~小朋友你是否有很多问号~~我来解释一下题意.

给定两个长方形 红红和绿绿以及一个坐标系 红红的高是$[0,1]$,绿绿的高是$[1,2]$.红红的宽是$[a,a+w]$,绿绿的宽是$[b,b+w]$.然后呢将红红和绿绿移到水平位置合成一个长方形,求合成长方形需要移动的最小距离 ~~那高的坐标有啥用?~~ 

然后就真的没啥可说了(感觉红题难度) 具体看代码吧

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int a, b, w, ans;//定义

int main()
{
	int ans;
	cin >> w >> a >> b;//输入
	if(b + w <a)
		ans = a - b - w;//b在a前面 的情况
	if(a + w < b)
		ans = b - a - w;//a在b前面的情况
	cout << ans << endl;//如果a和b有重叠部分那么直接输出0就完了
    return 0;
}

---

