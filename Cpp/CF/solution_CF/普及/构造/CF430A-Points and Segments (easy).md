# Points and Segments (easy)

## 题目描述

Iahub isn't well prepared on geometry problems, but he heard that this year there will be a lot of geometry problems on the IOI selection camp. Scared, Iahub locked himself in the basement and started thinking of new problems of this kind. One of them is the following.

Iahub wants to draw $ n $ distinct points and $ m $ segments on the $ OX $ axis. He can draw each point with either red or blue. The drawing is good if and only if the following requirement is met: for each segment $ [l_{i},r_{i}] $ consider all the red points belong to it ( $ r_{i} $ points), and all the blue points belong to it ( $ b_{i} $ points); each segment $ i $ should satisfy the inequality $ |r_{i}-b_{i}|<=1 $ .

Iahub thinks that point $ x $ belongs to segment $ [l,r] $ , if inequality $ l<=x<=r $ holds.

Iahub gives to you all coordinates of points and segments. Please, help him to find any good drawing.

## 样例 #1

### 输入

```
3 3
3 7 14
1 5
6 10
11 15
```

### 输出

```
0 0 0```

## 样例 #2

### 输入

```
3 4
1 2 3
1 2
2 3
5 6
2 2
```

### 输出

```
1 0 1 ```

# 题解

## 作者：alan1118 (赞：9)

本人第一篇题解，求过！

看到其他人的题解都用了排序，但是题里给的数据范围 $n,m$ 都 $\le 100$，也太小了吧！所以根本不用排序。

其实这道题跟那 $m$ 个线段没什么关系，只需要把它们输入进来就行了。而想要让红色点和蓝色点的数量最大相差 $1$，只需要按照红、蓝、红、蓝...... 染色就可以了，如果理解不了请看下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/j2ne4wcf.png)

剩下的就是枚举每一个数，然后每次把这 $n$ 个数里 $<a_i$ 的数的数量算出来，如果为奇输出 $1$，否则输出 $0$ 就好了（相反输出也可以）。

## 代码

```cpp
#include <iostream>
using namespace std;

int a[105], l[105], r[105];
int b[105], cur;

int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= m; i++)
        cin >> l[i] >> r[i];
    
    for(int i = 1; i <= n; i++)
    {
        int cnt = 0;
        for(int j = 1; j <= n; j++)
            if(a[j] < a[i]) cnt++;
        if(cnt % 2) cout << 0 << " ";
        else cout << 1 << " ";
    }
    return 0;
}
```

---

## 作者：YWJ20140130 (赞：2)

## 题目：[Points and Segments (easy)](https://www.luogu.com.cn/problem/CF430A)
### 思路：
题目中要求整段红点蓝点数量相差不超过 $1$，可以用到交替染色。  
题目输出中的 $0$ 和 $1$ 可以当作红色和蓝色。  
其实这道题和线没什么关系，只需要~~盲目~~给点交替染色就好了。  
循环统计一下每次小于 $a_i$ 的数，如果是奇数输出 $0$（红色），偶数输出 $1$（蓝色）。

### 分段代码：
#### 输入
输入只需要输入 $n,m,a_i$ 就可以了。  
```c++
cin>>n>>m;
for(int i=1;i<=n;i++) cin>>a[i];
```
线就只需要输入一个临时变量。（如果不输入的话有可能会出一些问题，保险起见还是输入。）
```c++
int P;
for(int i=1;i<=m;i++) cin>>P>>P;
```
#### 处理
按分析即可。
```c++
for(int i=1;i<=n;i++){
  int cnt=0;              //等于零！！！
  for(int j=1;j<=n;j++)
    if(a[j]<a[i])
      cnt++;
  //输出
}
```
#### 输出
在每次外循环结束前，判断一下累加器奇偶，输出 $1$ 与 $0$。
```c++
cout<<!(cnt%2)<<' ';    //空格！！！
```

### Code
```c++
#include<bits/stdc++.h>
#define io ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
int n, m, a[1001];
int main() {
	io
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	int P;												//临时变量
	for (int i = 1; i <= m; i++) cin >> P >> P;			//怕出问题
	for (int i = 1; i <= n; i++) {						//累加器统计
		int cnt = 0;									//等于零！！！
		for (int j = 1; j <= n; j++)
			if (a[j] < a[i])							//使用更加令人明了的代码格式
				cnt++;
		cout<<!(cnt%2)<<' ';							//空格！！！
	}
	return 0;
}
```
### 总结：
- 思路打开，多去思考
- 没有用的输入可以用临时变量输入
- 局部累加器要赋初始值（$0$）
- 注意输出格式

## 最后祝大家在信奥的路上越走越远！

---

## 作者：Y_ATM_K (赞：2)

## 题意
- 给定 $n$ 个点和 $m$ 条线段，对每个点染上红色或蓝色。
- 求一种染色方案，使得每条线段包含的红色点和蓝色点个数之差不超过 $1$。
- $1\le n,m\le100$

## 分析
注意到一条线段包含的是一段区间，可以给每个点排个序，

把线段转化为排序后序列上的一段区间，这样问题就变成了：

给你一个长度为 $n$ 的序列和 $m$ 个区间，求一个染色方案，使得每个区间包含的红点和蓝点个数之差不超过 $1$。

直接枚举染色方案时间复杂度是 $O(2^n)$，肯定不行。考虑直接构造合法方案。

当区间长度为 $1$ 时，显然随便染色就可以。

当区间长度为 $2$ 时，把两个点染成不同颜色即可。

当区间长度为 $3$ 时，因为颜色交换不影响答案，所以可以染成 $\text{bbr}$，$\text{rbb}$，$\text{brb}$ 这三种。

哪个更好呢？可以发现对于 $\text{bbr}$，若有另一个区间包含前两个点，就不合法了；$\text{rbb}$ 同理；

而 $\text{brb}$，被它包含的区间都是合法的。

当区间长度为 $4$ 时，我们发现 $\text{brbr}$ 也满足**被它包含的区间都合法**这一性质。

以此类推，只要把序列染成 $\text{brbrbrbr...}$ 这样的，无论区间怎样取，都是合法的。

于是方案就是，把点按照 $x$ 坐标排序，然后交替染色就可以了。

时间复杂度 $O(n\log n)$。

## 代码
```cpp
#include <bits/stdc++.h>
#define N 105
using namespace std;
int n,m;
struct node {
	int x,u;//u存序号
	bool operator <(node a) const {
		return x<a.x;
	}
} a[N];
void init() {
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i].x);
		a[i].u=i;
	}
	//甚至不需要输入线段
}
int ans[N];
int main() {
	scanf("%d%d",&n,&m);
	init();
	sort(a+1,a+1+n);
	for(int i=1;i<=n;++i) {
		ans[a[i].u]=i&1;//按照奇偶性就是交替染色
	}
	for(int i=1;i<=n;++i) {
		printf("%d ",ans[i]);
	}
	return 0;
}
```

---

## 作者：Yiyi_52MIYEON1314 (赞：0)

# 题意
给你一个长为 $n$ 的序列，以及 $m$ 个区间，现在将 $n$ 的每个点染成红色或蓝色，使得每个区间的蓝色点数和红色点数相差最大为 $1$，求一种合法的染色方法。

# 思路
不难发现，**交替染色**无论如何最大相差都不会超过 $1$。

- 首先，输入序列 $n$ 中数的位置，再输入 $m$ 个区间的首位，其实这个没啥用。
- 其次，因为我们输入的位置是**无序**的，而我们要获得有序后每个数的位置，所以大家可以选择**排序**或判断有多少个比当前位置**小**的位置。
- 然后我们把有序后的位置，也就是它本来的位置设为`cnt`，然后交替输出，也就是输出 $cnt\bmod2$ 或 $cnt\bmod2$ 取反都可以。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],l,r,n,m;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>l>>r;
	}
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(int j=1;j<=n;j++){
			if(a[j]<a[i])cnt++;
		}
		cout<<!(cnt%2)<<' ';
	}
 	return 0;
}

```
### 谢谢！

---

## 作者：_xdd_ (赞：0)

洛谷评分黄题，奶龙黄是吧。

显然红蓝交替构造的方法，不管查询哪个区间，都是合法的，听了这个题解全班都炸了，所以读入之后做一遍排序，然后判断奇偶输出 `1` 或 `0` 即可。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define r0 return 0
#define inf (0x7fffffff)
#define maxn ( 1000 +5)
//#define int long long
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
int n,a[maxn],m;
signed main(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        if(i%2==1){
            cout << 1 << ' ';
        }else{
            cout << 0 << ' ';
        }
    }
    return 0;
}
```

---

## 作者：yaaaaaan (赞：0)

### 思路
这道题可以先把点进行排序，要使区间内红蓝点数差不超过 $1$ 
很显然可以给所有的点交替染色。因为如果红蓝点数差超过 $1$ 的话，必定会有相邻两点是同种颜色，而交替染色就避免了这种情况的发生。排序前记录一下序号，排序后按序号顺序输出即可。

### code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,b[1001],m;
struct st{
	int x,ii;
}a[1001];
bool cmp(st a,st b)
{
	return a.x<b.x;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x;
		a[i].ii=i;//排序前存序号方便输出
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		b[a[i].ii]=i%2;//交替染色
	}
	for(int i=1;i<=n;i++)
	{
		cout<<b[i]<<" ";//输出方案
	}
	return 0;
}
```

---

## 作者：Nuclear_Fish_cyq (赞：0)

## 思路

我们知道一个区间覆盖的点都是一整段的，所以我们可以先把点进行排序。要使区间内红蓝点数差不超过 $1$，而且考虑到区间有可能重叠，很显然可以给所有的点交替染色。所以这道题我们可以先对点排序，然后给排序后的点交替染色，最后把点放回去。我们甚至不需要用到线段的信息。

顺带提一下为什么交替染色的点一定能使区间红蓝点数差不超过 $1$：如果这个区间红蓝点数差超过 $1$ 的话那么必定有相邻两个点颜色相同，否则点数差不能超过 $1$。但是交替染色刚好不可能存在相邻的点颜色相同，所以所有区间红蓝点数差不能超过 $1$。

上代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
//#define mod
//#define range
using namespace std;
int n, m, a[100], b[100], c[105];

//如果再忘记把题目给的1~n变为0~n-1自罚20仰卧起坐
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b, b + n);
	for(int i = 0; i < n; i++){
		c[b[i]] = i;
	}
	for(int i = 0; i < n; i++){
		cout << c[a[i]] % 2 << " ";
	}
	return 0;
}

```

---

## 作者：luuia (赞：0)

## 题意

给你数轴上的 $n$ 个点，和 $m$ 条线段，求一种染色方法，每个点染红色或蓝色，使得每条线段中蓝色数与红色数差的绝对小于 $2$。

## 分析

构造题。

我们发现，如果按照蓝，红，蓝，红交替染色，那么无论这个线段在哪，都满足题目要求。

### 证明

设这个线段左端点为 $l$，右端点为 $r$。

- $l \equiv 0\pmod 2$，$r \equiv 0\pmod 2$

红色数目为 $\dfrac{r-l+2}{2}$，蓝色数目为 $\dfrac{r-l}{2}$，红色比蓝色多 $1$。

- $l \equiv 0\pmod 2$，$r \equiv 1\pmod 2$

红色数目为 $\dfrac{r-l+1}{2}$，蓝色数目为 $\dfrac{r-l+1}{2}$，红色和蓝色相等。

- $l \equiv 1\pmod 2$，$r \equiv 0\pmod 2$

红色数目为 $\dfrac{r-l+1}{2}$，蓝色数目为 $\dfrac{r-l+1}{2}$，红色和蓝色相等。

- $l \equiv 1\pmod 2$，$r \equiv 1\pmod 2$

红色数目为 $\dfrac{r-l}{2}$，蓝色数目为 $\dfrac{r-l+2}{2}$，蓝色比红色多 $1$。

综上，结论成立。

## 代码

注意给出的 $n$ 个点不是升序排列，可以先按照坐标排序再染色，最后再按最初的顺序输出即可。

[AC 记录](https://www.luogu.com.cn/record/146241633)

```cpp
#include<bits/stdc++.h>
using namespace std;

struct Point{int x,color,i;}a[110];

int main()
{
	int n,m,x,y;
	cin >> n >> m;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i].x;
		a[i].i = i;
	}
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j < n;j++)
		{
			if(a[j].x > a[j + 1].x)
			{
				Point p = a[j];
				a[j] = a[j + 1];
				a[j + 1] = p;
			}
		}
	}
	for(int i = 1;i <= n;i++)
	{
		a[i].color = i % 2;
	}
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j < n;j++)
		{
			if(a[j].i > a[j + 1].i)
			{
				Point p = a[j];
				a[j] = a[j + 1];
				a[j + 1] = p;
			}
		}
	}
	for(int i = 1;i <= m;i++)
	{
		cin >> x >> y;
	}
	for(int i = 1;i <= n;i++)
	{
		cout << a[i].color << " ";
	}
	return 0;
}
```


---

## 作者：zyl0128_alpha (赞：0)

## 思路：
首先，对点进行排序。接着开始染色。既然要求出一种红蓝数量差不超过 $1$ 的方案，就交替染色，染的颜色就是 $i$ 对 $2$ 取余的值。

## 代码：
```
#include<bits/stdc++.h>
using namespace std;
struct node{
    int x,x1,xd;
}a[100010];
bool cmp(node x,node y){return x.x<y.x;}
int main(){
    int n,m,b[100010];
    bool f=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i].x;
    }
    for(int i=1;i<=n;i++){
        a[i].x1=i;
    } 
    for(int i=1;i<=m;i++){
        cin>>a[i].xd;
        if(a[i].xd>n||a[i].xd<1){
            f=1;
        }
    }  
    if(f==1){
        cout<<-1;
        return 0;//未满足要求
    }
    sort(a+1,a+1+n,cmp);  
    for(int i=1;i<=n;i++){
        b[a[i].x1]=i%2;
    }  
    for(int i=1;i<=n;i++){
        cout<<b[i]<<" ";
    }    
    return 0; 
}
```


---

