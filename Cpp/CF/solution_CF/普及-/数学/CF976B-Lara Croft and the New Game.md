# Lara Croft and the New Game

## 题目描述

You might have heard about the next game in Lara Croft series coming out this year. You also might have watched its trailer. Though you definitely missed the main idea about its plot, so let me lift the veil of secrecy.

Lara is going to explore yet another dangerous dungeon. Game designers decided to use good old 2D environment. The dungeon can be represented as a rectangle matrix of $ n $ rows and $ m $ columns. Cell $ (x,y) $ is the cell in the $ x $ -th row in the $ y $ -th column. Lara can move between the neighbouring by side cells in all four directions.

Moreover, she has even chosen the path for herself to avoid all the traps. She enters the dungeon in cell $ (1,1) $ , that is top left corner of the matrix. Then she goes down all the way to cell $ (n,1) $ — the bottom left corner. Then she starts moving in the snake fashion — all the way to the right, one cell up, then to the left to the cell in $ 2 $ -nd column, one cell up. She moves until she runs out of non-visited cells. $ n $ and $ m $ given are such that she always end up in cell $ (1,2) $ .

Lara has already moved to a neighbouring cell $ k $ times. Can you determine her current position?

## 说明/提示

Here is her path on matrix $ 4 $ by $ 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF976B/1b2df8f31f927201c078b0cd1ef3dccbc8991311.png)

## 样例 #1

### 输入

```
4 3 0
```

### 输出

```
1 1
```

## 样例 #2

### 输入

```
4 3 11
```

### 输出

```
1 2
```

## 样例 #3

### 输入

```
4 3 7
```

### 输出

```
3 2
```

# 题解

## 作者：wwwidk1234 (赞：6)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF976B)

[CodeForces 题目传送门](https://codeforces.com/problemset/problem/976/B)

[更好的阅读体验？](https://wwwidk1234.github.io/)

## 题目简介
这是一道很考验思维的数学题。

## 题意
一个 $n \times m$ 的矩阵，从左上角 $(1,1)$ 出发，从上走到下之后按照蛇形方式走到终点 $(1,2)$。给定一个步数 $k$，求走 $k$ 步之后的坐标。

## 分析
通过数据量 $2\le n,m \le 10^9,0\le k \le n \cdot m$ 得知模拟小人走的路径是不可以的。因此，我们考虑常数时间复杂度的数学算法。

分析一下，可以得知小人走的路径分为两部分：**从左上角走到左下角**和**从左下角走到终点**两部分。

### 第一部分
走一步时，小人在 $(2,1)$；走两步时，小人在 $(3,1)$……走 $k(k<n)$ 步时，小人在 $(k+1,1)$。

所以我们可以得到第一部分的代码：

```cpp
if(k<n) cout<<k+1<<" "<<1<<endl;
```

### 第二部分
第二部分的路径可以分为两种情况：**从左往右走**和**从右往左走**。设 $k_1=k-n$，那么 $k_1$ 即为第二部分走的步数。

通过分析 $k_1$ 我们可以得到一个规律：

- 当 $\left \lfloor \dfrac{k_1}{m-1} \right \rfloor $ 为**偶数**时，即为从**左往右**走，此时小人的坐标为 $(n-\dfrac{k_1}{m-1},k_1 \bmod (m-1)+2)$

- 当 $\left \lfloor \dfrac{k_1}{m-1} \right \rfloor $ 为**奇数**时，即为从**右往左**走，此时小人的坐标为 $(n-\dfrac{k_1}{m-1},m-k_1 \bmod (m-1))$

于是我们可以得到第二部分的代码：
```cpp
long long k1=k-n;
if((k1/(m-1))%2==1) cout<<n-k1/(m-1)<<" "<<m-k1%(m-1)<<endl;
else cout<<n-k1/(m-1)<<" "<<k1%(m-1)+2<<endl;
```

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);	cout.tie(0);
	long long n,m,k;
	cin>>n>>m>>k;
	if(k<n) cout<<k+1<<" "<<1<<endl;
	else
	{
		long long k1=k-n;
		if((k1/(m-1))%2==1) cout<<n-k1/(m-1)<<" "<<m-k1%(m-1)<<endl;
		else cout<<n-k1/(m-1)<<" "<<k1%(m-1)+2<<endl;
	}
	return 0;
}
```

最后提醒：注意数据范围，此题需要**开 long long**！

---

## 作者：KEBrantily (赞：3)

这是一道考验思维~~找规律~~的题，很有可做性。

真 · 思考两小时 写码两分钟



------------
# 正文
## 题意
一个 n * m 的矩阵，从左上角（1 , 1） 开始，先向下走直到最下方，再向右走到最右，再向上走一个，再走到最左......一直走到（1 , 2）为止

然后问你走完第k步后当前的坐标



------------
## 分析

正常走然后算是不行的，时间太长，而且还很难写。

既然行走规则是固定的，那我们就试着找一下规律。

### 我们把行走分成两部分：

- **第一部分：从（1 , 1）开始一直走到（n ，1）的过程（也就是从左上角走到左下角的过程）。**

  这个过程我们可以知道，走完第k步的坐标是（k+1 ， 1）；
- **第二部分，从（n ，2）开始走回到（1 ， 2）的过程。**
  
  这个过程我们首先可以看出，当走到第 n - i 行时，若 i 是偶数，则是从左向右走，是奇数则相反；

然后问题就转化成了求当前行是从左往右走还是从右往左走，那我们就把 k 截取第二部分的步数，根据 k 与 m-1（因为第一行已经走过） 的商是否为偶数来判断走向，然后根据在当前行走的步数来确定具体走到哪一格；

这样的方法可以确定 y ，那怎么确定 x 呢？

~~你确定了行数 x 不就出来了吗~~


------------
## 代码

ps：注释掉的是我一开始的写法，思路一样但是比较冗余，化简后就是这个亚子了
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstdlib>
#include<cmath>
#define maxn 100010

using namespace std;

long long n,m,k,ans,x,y;

int main(){
	cin>>n>>m>>k;
	if(k<n){
		cout<<k+1<<" "<<1;
		return 0;
	}
	k=k-n+1;
	long long t=(k-1)/(m-1);
	long long q=(k-1)%(m-1);
	x=n-t;
	if(k==0){
		cout<<n<<" "<<1;
		return 0;
	}
//	if(q==0 &&t%2!=0){
//		y=m;
//		cout<<x<<" "<<y;
//		return 0;
//	}
//	if(q==0 &&t%2==0){
//		y=2;
//		cout<<x<<" "<<y;
//		return 0;
//	}
	if(x%2==0){
		y=q+2;
		cout<<x<<" "<<y;
//		if ( ((t%2)+1)%2==0 ){
//			y=m-q+1;
//		}
//		if ( ((t%2)+1)%2!=0 ){
//			y=q+1;
//		}
	}
	else cout<<x<<" "<<m-q;
//	cout<<k<<" "<<q<<" "<<t;
	return 0;
}
```

若有问题请及时告知我，制作不易，不喜勿喷，谢谢。

---

## 作者：GordonLu (赞：2)

# CF976B 题解
## 题意

点[**这里**](https://www.luogu.com.cn/problem/CF976B)查看原题。

给定一个 $n \times m$ 的矩阵（$n$ 是偶数），现在从左上角出发，走到终点 $(1,2)$。首先从 $(1,1)$ 向下一直走到 $(n,1)$，然后从 $(n,1)$ 向右一直走到 $(n,m)$，之后不断按照 S 型方式走，也就是先向上走一步到 $(n-1,m)$，然后从 $(n-1,m)$ 走到 $(n-1,2)$，再向上走一步到 $(n-2,2)$，再向右走到 $(n-2,m)$，一直走到 $(2,m)$，在向上一步走到 $(1,m)$，最后向左走到终点 $(1,2)$。问当走到第 $k$ 步的时候，小人位置坐标是什么。

## 分析

直接模拟到第 $k$ 步是没问题的，但是时间复杂度是 $O(k)$，肯定会 TLE 的。那么我们就可以考虑不直接模拟，直接求出第 $k$ 步的坐标。

显然是可以的，因为我们发现整个过程可以被分为两个部分：
- 从 $(1,1)$ 直线到 $(n,1)$；
- 从 $(n,1)$ 走 S 形到 $(1,2)$。

这样就简单了，只需要先特判掉第一种，在算出第 $k$ 步所在行数，然后分情况算出第 $k$ 步的具体位置。

## 代码

```cpp
#include <cstdio>
long long n,m,k;
int main() {
    scanf("%lld %lld %lld",&n,&m,&k);
	if(k<n)printf("%lld %d",k+1,1);
	else {
		k-=n;printf("%lld ",n-k/(m-1));
		if(k/(m-1)&1)printf("%lld",m-k%(m-1));else printf("%lld",k%(m-1)+2);
	}
	return 0;
}
```


很简单，也很短。

---

## 作者：EternalAlexander (赞：2)

肯定是模拟嘛。
最朴素的模拟就是按题意一步一步走O(k)显然是不行的
然后发现很长的一条可以一次跳完。快了很多，但是最坏应该是O(n)的。事实上也过不去。
因此采用直接计算的方法O(1)出解

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

long long n, m; long long k;

int main() {
	cin >> n >> m >> k;
	if (k<n) {
		cout << k+1 << " " << 1 << endl;
		return 0;
	}k-=n-1;
	if (k==0) {
		cout << n << " "<<1;
		return 0;
	}k-=1;
	long long l = (long long)k/(m-1);
	//cout << n << " " << m << " " << k << " " << l << endl;
	k%=(m-1);
	if ((n-l)%2==0) cout << n-l << " " << k+2<<endl;
	else cout << n-l << " " << m-k<<endl;
	//cout << n << " " << m << " " << k << " " << l << endl;
	return 0;
}
```

~~我才不会说我一开始用%d读long long调了几十分钟~~

---

## 作者：___cjy__ (赞：0)

# CF976B Lara Croft and the New Game 题解

[题目传送门](https://www.luogu.com.cn/problem/CF976B)

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-cf976b)

### 题目大意：

给定一个 $n \times m$ 的矩阵，从左上角出发，直线走到 $(n,1)$。接着向右走 S 型直到走到 $(1,2)$。

求走 $k$ 步时的坐标。

### 正文：

可以将矩阵划分为两个部分：

1. $(1,1)$ 直线到 $(n,1)$。

1. $(n,2)$ S 型到 $(1,2)$。

这样先特判掉第一种情况，坐标为 $(k+1,1)$，再另外计算第二种情况的行数，通过行的奇偶来判断当前坐标的列数，从而得到答案。

### AC Code：

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, m, k;

signed main(){
	cin >> n >> m >> k;
	
	if(k < n) cout << k + 1 << " 1\n";
	else{
		k -= n;
		int line = k / (m - 1);
		int t = k % (m - 1);//[0, m - 2]
		if(line & 1){
			line = n - line;
			t = m - t;
		}else{
			line = n - line;
			t = t + 2;
		}
		cout << line << ' ' << t << endl;
	} 
	
	return 0;
} 
```

---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF976B)

这题第一眼看，是一道模拟。正常模拟不行的，时间太长，而且还很难写。

行走方式固定，可以找规律。

## 分析

把这题分为 $2$ 种不同的情况讨论。

1.$k<n$ 就是从左上向左下。小人在 $(k+1,$  $1)$ 的位置 第一段的代码是

```
	if(k<n){cout<<k+1<<" "<<"1";}
```
2. 第二部分的路径可以分为两种情况：从左往右走和从右往左走。设   $k_1=k-n$ 那么 $k_1$ 即为第二部分走的步数。

- 第偶数行上人从第 $2$ 列走到第 $m$ 列，坐标是 $k \bmod (m - 1) + 2$。

- 奇数行上人从第 $m$ 到第 $2$，坐标是 $ m-k \bmod (m - 1)$。

第二部分的代码是。

```
		k-=n;
		long long h=n-k/(m-1);
       		cout<<h;
		if(k/(m-1) %2==1)
		{	
        		l=m-k%(m-1);
		}
		else 
      		{
        		l=k%(m-1)+2;
		}
		cout<<" "<<l; 
            
```


## 下面是 AC 代码
```
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,l,h;
int main()
 {
    cin>>n>>m>>k;
	if(k<n)
	{
		cout<<k+1<<" "<<"1";
	}
	else {
		k-=n;
		long long h=n-k/(m-1);
		cout<<h;
		if(k/(m-1) %2==1)
		{
			l=m-k%(m-1);
		}
		else 
		{
			l=k%(m-1)+2;	
		}
			cout<<" "<<l; 
	}
	return 0;
}
```


---

## 作者：Yizhixiaoyun (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF976B)

## 题目分析

拿到题目，第一反应毫无疑问是模拟。然后一看数据范围，时间复杂度为 $O(k)$ 的模拟显然过不去。

那么我们推式子，考虑 $O(1)$ 出结果。

首先特判一种情况，即从 $(1,1)$ 到 $(n,1)$ ，这种情况由于是直线走，因此直接输出。

另外的情况就是从 $(n,1)$ 开始，走 $\text{S}$ 形到达 $(1,2)$。

这种情况我们分偶数、奇数的情况求出其所在行数，然后即可轻松求出答案。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
int tot;
inline void init(){cin>>n>>m>>k;}
signed main(){
    init();
	if(k<n) cout<<k+1<<" "<<"1",exit(0);
	k-=n;
	if(k==-1) cout<<n<<" "<<1,exit(0);
	tot=k/(m-1);k%=m-1;n-=tot;
	if(n%2==0) cout<<n<<" "<<k+2;
	else cout<<n<<" "<<m-k;
}
```

---

## 作者：Rhapsodia (赞：0)

时限两秒，暴力做法感觉不太可取。

如何优化？我们可以把暴力枚举的过程分拆可以简单求的路段。在已知行数的情况下算出列坐标。

- 从左上角走到左下角（ $k<n$ 的部分）
- 第偶数行上人从第 $2$ 列走到第 $m$ 列，坐标是 $k \bmod (m - 1) + 2$ 。
- 第奇数行上人从第 $m$ 列走到第 $2$ 列，坐标是 $m - k \bmod (m - 1)$ 。

#### 注意要分奇偶的情况，因为人是按照 $S$ 型走的。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, m, k, x;

signed main() 
{
	scanf("%d%d%lld", &n, &m, &k);
	if(k < n)
	{
		k++; // cout << k << endl;
		printf("%lld 1\n", k);
		return 0;
	}
	k -= n;
	x = k / (m - 1);
	printf("%lld ", n - x);
	if(x % 2 == 1)
		printf("%lld\n", m - k % (m - 1));
	else
		printf("%lld\n", k % (m - 1) + 2);
}
```

---

## 作者：mzyc_pzx (赞：0)

[CF976B Lara Croft and the New Game](https://www.luogu.com.cn/problem/CF976B)
### 思路：
本题可以找到规律。
1. 从左上到左下。
2. 从第 $n$ 排第 2 个旋回到第 1 排第 2 个。
3. 特判 $n>k$ 时输出 $k+1$ 和 $1$ 。
### 特判部分：
```cpp
   if(k<n)
	cout<<k+1<<" "<<1;
```
### 主要部分
```cpp
	else
	{
		k-=n;
		cout<<n-k/(m-1)<<" ";
		if(k/(m-1)&1)
		cout<<m-k%(m-1);
		else 
		cout<<k%(m-1)+2;
	}
```


---

