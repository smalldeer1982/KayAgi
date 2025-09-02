# Case of Fake Numbers

## 题目描述

Andrewid the Android is a galaxy-famous detective. He is now investigating a case of frauds who make fake copies of the famous Stolp's gears, puzzles that are as famous as the Rubik's cube once was.

Its most important components are a button and a line of $ n $ similar gears. Each gear has $ n $ teeth containing all numbers from $ 0 $ to $ n-1 $ in the counter-clockwise order. When you push a button, the first gear rotates clockwise, then the second gear rotates counter-clockwise, the the third gear rotates clockwise an so on.

Besides, each gear has exactly one active tooth. When a gear turns, a new active tooth is the one following after the current active tooth according to the direction of the rotation. For example, if $ n=5 $ , and the active tooth is the one containing number $ 0 $ , then clockwise rotation makes the tooth with number $ 1 $ active, or the counter-clockwise rotating makes the tooth number $ 4 $ active.

Andrewid remembers that the real puzzle has the following property: you can push the button multiple times in such a way that in the end the numbers on the active teeth of the gears from first to last form sequence $ 0,1,2,...,n-1 $ . Write a program that determines whether the given puzzle is real or fake.

## 说明/提示

In the first sample test when you push the button for the first time, the sequence of active teeth will be 2 2 1, when you push it for the second time, you get 0 1 2.

## 样例 #1

### 输入

```
3
1 0 0
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
5
4 2 1 4 3
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
4
0 2 3 1
```

### 输出

```
No
```

# 题解

## 作者：Little_x_starTYJ (赞：4)

### 解题思路：

对于齿轮的转动，我们只需要考虑第 $1$ 个齿轮的向右的转动次数，以此使后面的齿轮也一起转动，然后去考虑后面的齿轮是否处在正确的位置即可。

**特别注意：** 奇数齿轮与偶数齿轮的方向是不同的。

CODE:

```c
#include <stdio.h>
int main() {
	int n, x;
	scanf("%d%d", &n, &x);
	x -= n;
	for (int i = 2; i <= n; i++, x = -x){
		int y;
		scanf("%d", &y);
		if ((x + y + n) % n + 1 != i){
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	return 0;
}
```

---

## 作者：FwbAway (赞：2)

贪心算法我来说：

比如两个齿轮，第一个带着后面的动，就不能考虑这种情况。

对于排除这种情况，有两种办法：

设一个 $flag$，如果从第一个在动的时候第二个没动，$flag=-1$，然后跳出就行了。

还有：可以只从左往右判断，不间断。

此片题解请结合这@[流绪
](https://www.luogu.com.cn/user/287610)的题解来看，我帮他补充一下。

---

## 作者：流绪 (赞：2)

模拟！

因为后面的每个齿轮都是由第一个齿轮带动的，所以我们只要考虑第一个齿轮转到 0 要转几步，后面的都是一样的步数，只要注意奇偶转动方向不一样就好啦！

我们定义一个转动函数：
```cpp
bool turn(int i,int j,int s,int d)
{
	if(i%2==0)
		d*=-1;
	int p=(a[i]+s*d);
	if(p<0)
		p=n+p;
	else
		p%=n;
//	cout << p <<" " << a[i]<< " " << i << " " << s <<endl;
	if(p==j)
		return 1;
	return 0; 
}
```
传入的参数意义是：现在转的齿轮 i，i 要对应的值 j，转动步数 s，方向 d

我们每次传入的方向都是 1，如果 i 是偶数那乘个 -1来表示方向不同。

然后开始改变这个齿轮的值，改变完了如果等于 j 就返回 1 表示成功，反之返回 0 表示失败，如果有一个失败了，就不可能转出符合题目的齿轮了，用 flag=0 记录下来，最后根据 flag 来输出就好啦！

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#include<cstring>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
int a[maxn];
int n;
bool turn(int i,int j,int s,int d)
{
	if(i%2==0)
		d*=-1;
	int p=(a[i]+s*d);
	if(p<0)
		p=n+p;
	else
		p%=n;
//	cout << p <<" " << a[i]<< " " << i << " " << s <<endl;
	if(p==j)
		return 1;
	return 0; 
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i=1;i<=n;i++)
		cin >> a[i];
	int c;
	c=n-a[1];
	int flag = 1;
	for(int i=2;i<=n;i++)
		if(!turn(i,i-1,c,1))
			flag=0;
	if(flag)
		cout << "Yes";
	else
		cout << "No";		 
	return 0; 
}  
```


---

## 作者：wuzijie (赞：1)

## 题面解释：
有 $n$ 个互相啮合的齿轮，转动其中一个，让第 $i$ 个齿轮在第 $i-1$ 个齿上，问是否可行。

## 思路分析：
其实对于齿轮的旋转来说，我们只需要考虑第 $1$ 个齿轮往右转了几下，以此带动后面的齿轮。因为第 $1$ 个齿轮要满足在 $0$ 上只有这一种转发，然后去考虑后面的齿轮是否处于正确的位置。

注意：
- 齿轮的旋转方向又奇偶性决定，即每次换方向。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,x,y;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>x;
	x-=n;
	for(int i=2,y;i<=n;i++){
		cin>>y;
		if((x+y+n)%n!=i-1){
			cout<<"No";
			return 0;
		}
		x=-x;
	}
	cout<<"Yes";
	return 0;
}
```

谢谢！

---

## 作者：zsh_haha (赞：0)

### 题目大意

直接看题目有点难懂，我们把题目形式化一下。

给定数组 $a$ 和变量 $n$，数组 $a$ 中第 $i$ 个数为 $a_i$，且 $0\le a_i<n$。

定义一次操作：

设变量 $i$，且 $0\le i<n$；

若 $i\bmod2=0$，那么把 $a_i$ 的值改为 $(a_i+1)\bmod n$，否则把 $a_i$ 的值改为 $(a_i-1+n)\bmod n$。

现在你可以对**所有**齿轮**各**做 $k$ 次操作，其中 $k$ 可以为任意非负整数，使得 $a_i=i$。

### 思路讲解

通过观察形式化题目，很容易发现，只要每个齿轮需要的**最少**操作次数两两相等，那么 Stolp 的齿轮谜题就是真的，亦而反之。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,x,y;
	cin>>n;
	cin>>x;
	for(int i=1;i<n;i++){
		y=x;
		cin>>x;
		if(i%2==1){
			if((i-y+n)%n!=(x-(i-1)+n)%n){
				cout<<"No";
				return 0;
			}
		}else{
			if((i-x+n)%n!=(y-(i-1)+n)%n){
				cout<<"No";
				return 0;
			}
		}
	}
	cout<<"Yes";
    return 0;
}
```

---

## 作者：Vegetableless (赞：0)

根据题意，每个奇数位上的齿轮顺时针旋转，偶数位上的齿轮逆时针旋转。

这道题目 $n \le 1000$，所以可以考虑暴力模拟，我们一直旋转齿轮，直到第一个齿轮为 $0$ 时，查看整个齿轮序列是否为 $0 , 1 , 2 , 3 , \cdots , n-1$，如果不是，则输出 `No` 否则就输出 `Yes`。

这样的时间复杂度是 $O(n^{2})$。

这里就不给出代码了。

我们可以选择不模拟，对于旋转齿轮，我们定义初始状态为 $x$，目标状态为 $y$。

首先先考虑顺时针旋转，我们分为两种情况考虑，第一种是 $y$ 大于等于 $x$ 的时候：

这个好办，需要旋转次数就为 $y-x$。

第二种是 $y$ 小于 $x$ 的时候：

首先我们考虑 $x$ 到 $n-1$ 需要的旋转次数 $c1$，由上文的式子得到：
$$c1 = n - 1 - x$$

然后我们考虑 $0$ 到 $y$ 需要的旋转次数 $c2$，同理可得：
$$c2 = y$$

又因为 $n - 1$ 变为 $0$ 需要一次旋转次数，所以实际上真正需要的旋转次数 $c3$ 为：
$$c3 = c1 + c2 + 1$$

也就是：
$$c3 = n - 1 - x + y + 1 = n - x + y$$

然后考虑逆时针旋转：

我们知道，一个齿轮从 $x$ 顺时针转动为 $y$ 需要 $c$ 次，那么从 $y$ 逆时针转动到 $x$ 同样也要 $c$ 次。所以我们可以把从 $x$ 逆时针转动到 $y$ 转换为从 $y$ 顺时针转动到 $x$，根据上文处理顺时针转动的方法来。

在考虑完如何求需要的旋转次数后，我们再来看题目。因为每次旋转每个齿轮都会改变，所以仅当每个齿轮状态变为各自的目标状态需要的旋转次数一样时，输出 `Yes`，否则就输出 `No`。

时间复杂度为 $O(n)$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;

inline int read(){
	register char ch = getchar();
	register int x = 0;
	register bool f = 0;
	while(!isdigit(ch)) f = (ch == '-') , ch = getchar();
	while(isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48) , ch = getchar();
	return f ? -x : x;
}

int n , a[N] , b[N];

int main(){
	n = read();
	for(register int i = 1;i <= n;++i) a[i] = read();
	for(register int i = 1;i <= n;++i){
		int x , y;//初始状态，目标状态 
		
		if(i & 1)
			x = a[i] , y = i - 1;//对于每个齿轮，初始状态是a[i]，目标状态是i-1 
		else x = i - 1 , y = a[i];//如果为偶数（也就是需要逆时针旋转），就可以变成从目标状态顺时针转到初始状态 
		
		if(x <= y) b[i] = y - x; 
		else b[i] = n - x + y;//这里就是分类讨论 
		//用 b 数组记录每个齿轮需要的旋转次数
	}
	for(register int i = 2;i <= n;++i){
		if(b[i] != b[i - 1]){//每个齿轮需要的旋转次数必须一样，否则就无法达到目标状态 
			cout << "No";
			return 0;
		}
	}
	cout << "Yes";
	return 0;
}
```

---

## 作者：Forever_LYD (赞：0)

简单模拟。我们都知道齿轮是相互咬合的，所以只要前面一个齿轮转动，旁边的所有齿轮也都会以同样方式转动，有了这个就很能很简单的解决。所以只要把第一个齿轮转到 $0$ 需要的步数 $ans$ 求出即可，因为后面的齿轮也都是以第一个齿轮的方式旋转。

---

## 作者：wang_freedom (赞：0)

### 思路：
模拟题。

由于第一个齿轮会把后面的齿轮也带动，因此，我们只要计算第一个齿轮转到 $0$ 要转几步，后面的齿轮也都是这个步数。

### AC Code:
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
int a[1000005],n,c;
bool flag=1;
bool trn(int i,int j,int s,int d){
	if(i%2==0)
		d=-d;
	int p=a[i]+s*d;
	if(p<0)
		p+=n;
	else
		p%=n;
	if(p==j)
		return 1;
	return 0;
} 
signed main(){
	cin.tie(0);cout.tie(0);std::ios::sync_with_stdio(0);
	cin>>n;
	rep(i,1,n)
		cin>>a[i];
	c=n-a[1];
	rep(i,2,n)
		if(!trn(i,i-1,c,1))
			flag=0;
	if(flag)
		cout<<"Yes";
	else
		cout<<"No";
	return 0;
}
/*

*/

```
[AC记录](https://www.luogu.com.cn/record/125402158)

---

## 作者：Six_chestnuts (赞：0)

趁着这题还没有暴力写法，赶紧来一发暴力兼构造题解。


------------
题意
------------
给你 $N$ 个齿轮，和每个齿轮向上的齿的编号，每个齿轮上有 $N$ 个齿，每个齿都有一个编号，一个齿轮上齿的编号是 $0$ 到 $N-1$，然后按逆时针排序，然后第一个齿轮连接着一个按钮，这个按钮按几下，第一个齿轮则按照顺时针旋转几格，第二个则逆时针，第三个顺时针，依此类推。如果有一种可能使按钮按几下，然后从第一个齿轮到最后一个齿轮的上面的齿的编号刚好依次为 $0$ 到 $N-1$ 则输出 YES，否则输出 NO。



------------
思路
------------

首先当我看到 $N$ 的范围大小只有 $(1\le N\le 1000)$ 时我高兴的想到可以用暴力，且时间有两秒，足够了。首先分三步：

首先暴力枚举每一种按下去的结果，而当你按了 $N$ 此时就刚好转一圈回来，所以从按了 $0$ 到 $N-1$ 次数来枚举。 

然后再把枚举了的按的次数拿去构造出每一个齿轮朝上的齿轮的编号。

最后把构造出的进行对比看是否符合条件即可。



------------
部分代码
------------

枚举代码：

```c
for(int i=0;i<n;i++)
{
	check(i);
	if(cmp()==true)
	{
		cout<<"YES";
		return 0;
	}
}
```

构造代码：

```c
void check(int x)
{
	int k=-1;
	for(int i=1;i<=n;i++)
		now[i]=(a[i]+k*x)%n,k=-k;
}
```

对比代码：

```c
bool cmp()
{
	for(int i=1;i<=n;i++)
	{
		while(now[i]<0)
			now[i]+=n;
		if(now[i]!=i-1)
			return false;
	}
	return true;
}
```


------------


---

## 作者：andyli (赞：0)

模拟每次按下按钮时齿轮的转动，判断是否达到状态。  
可以在模拟前将所有 $a_i$ 变为 $(a_i - i) \bmod n$，这样只需判断数组是否全为 $0$ 即可。  

```python
n, *a = map(int, open(0).read().split())
for i in range(n):
    a[i] = (a[i] - i) % n
for _ in range(n):
    for i in range(n):
        if i % 2:
            a[i] += 1
        else:
            a[i] -= 1
        a[i] %= n
    if sum(a) == 0:
        exit(print('Yes'))
print('No')
```

---

