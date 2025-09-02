# Young Photographer

## 题目描述

Among other things, Bob is keen on photography. Especially he likes to take pictures of sportsmen. That was the reason why he placed himself in position $ x_{0} $ of a long straight racetrack and got ready to take pictures. But the problem was that not all the runners passed him. The total amount of sportsmen, training at that racetrack, equals $ n $ . And each of them regularly runs distances within a particular segment of the racetrack, which is the same for each sportsman. For example, the first sportsman runs from position $ a_{1} $ to position $ b_{1} $ , the second — from $ a_{2} $ to $ b_{2} $

What is the minimum distance that Bob should move to have a chance to take pictures of each sportsman? Bob can take a picture of a sportsman, if he stands within the segment that this sportsman covers on the racetrack.

## 样例 #1

### 输入

```
3 3
0 7
14 2
4 6
```

### 输出

```
1
```

# 题解

## 作者：Harry27182 (赞：8)

~~这道题很简单，由于数据范围很小，所以暴力模拟就可以过......~~

# 思路
暴力的思路主要是开一个数组记录每一个点的出现次数，具体方法是从 l 到 r 枚举一遍，把出现次数都加一。同时记录 l 和 r 的最小值和最大值。然后从最小值到最大值枚举，如果这个点的出现次数和区间个数相同，那这个点就是这些区间的公共部分，然后用这个点到 m 的距离更新最小值即可。
# AC code
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=0x3f3f3f3f,l,r,minn,maxn,flag;
int a[1005];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&l,&r);
		if(l>r)swap(l,r);
		for(int j=l;j<=r;j++)
		{
			a[j]++;
		}
		minn=min(minn,l);
		maxn=max(maxn,r);
	}
	for(int i=minn;i<=maxn;i++)
	{
		if(a[i]==n)
		{
			ans=min(ans,abs(i-m));
			flag=1;
		}
	}
	if(flag==0)cout<<-1<<endl;
	else cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：Miraik (赞：3)

这题其实不难。

题面大致是：求$n$条线段的**公共区间**与一个点的距离。

我们设题目中的点为$x$，每条线段的左端点为$l_{i}$，右端点为$r_{i}$（$l_{i}<r_{i}$)。

则很显然它们的公共区间的左端点即为$left=\max\{l_{i}\}$，右端点即为$right=\min\{r_{i}\}$。

然后将这个区间与题目中的点进行比较：

1.$left>right$，很显然此时没有公共区间，输出$-1$即可。

2.$left \le x \le right$，此时$x$已在公共区间内，输出$0$即可。

3.$x<left$，输出$left-x$即可。

4.$x<right$，输出$x-right$即可。

**坑点：读入不保证$l_{i}<r_{i}$，因此当$l_{i}>r_{i}$时，应将$l_{i}$和$r_{i}$互换！**

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,k,x,y,l,r=1005;
inline int _max(int x,int y){return x>y?x:y;}
inline int _min(int x,int y){return x<y?x:y;}
inline int _abs(int x){return x>0?x:-x;}
int main(){
	n=read(),k=read();//k为题目中的点x 
	while(n--)
		x=read(),y=read(),//x为l[i]，y为r[i] 
		l=_max(_min(x,y),l),r=_min(_max(x,y),r);//不保证l[i]<r[i]，因此要取max和min 
	//printf("%d %d\n",l,r);
	printf("%d\n",l>r?-1:(k>=l&&k<=r)?0:_min(_abs(k-l),_abs(k-r)));
	//三目运算符：l>r时，输出-1；点在区间内时，输出0；否则输出点与l距离和r距离的较小值（结合第3和第4点） 
	return 0;
}

```



---

## 作者：UKE自动稽 (赞：1)

题目说$0<=a_i,b_i<=1000$

数据贼~~jb~~小

所以可以暴力枚举离$x_0$最近的点，找不到输出$-1$。

顺便提一句，$a_i$有可能大于$b_i$

Code:

```
#include<bits/stdc++.h>
using namespace std;
#define INF 0x7fffffff
char did;
#define ak *
#define re register int
inline int read() {
    re ioi=1,cz=0;
    did=getchar();
    while(!isdigit(did))
        ioi=did=='-'?-1:ioi,did=getchar();
    while(isdigit(did))
        cz=(cz<<3)+(cz<<1)+did-'0',did=getchar();
    return cz ak ioi; //不要管
}
int n,a[5005],x,y,ans=INF,x0;
int main() {
	n=read(),x0=read();
	for(int i=0; i<n; i++) {
		x=read(),y=read();
		if(x>y)
			swap(x,y);//ai可能大于bi
		for(int j=x; j<=y; j++) {
			a[j]++;//枚举点
			if(a[j]==n) {
				if(abs(j-x0)<ans)//找最近距离
					ans=abs(j-x0);
			}
		}
	}
	if(ans==INF)
		ans=-1;
	printf("%d\n",ans);
}

```


---

## 作者：FiraCode (赞：0)


[【题目链接】](https://www.luogu.com.cn/problem/CF14B)
## 思路：
因为数据范围 $a , b \le 1000$ 很小，所以我们可以用一个数组来存一个数他出现的次数。

然后用两个数，储存数的 $l$ 最小值和 $r$ 的最大值。

依次枚举每个数，看看这个数出现的次数是否等与区间个数 $n$，如果是的话，就更新距离。

如果枚举完都没有一个满足条件的，输出 $-1$。

[【AC记录】](https://www.luogu.com.cn/record/73691887)

## AC code:

```
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1010 , INF = 0x3f3f3f3f;
int a[N];//存出现个数的数组
int ans = INF;//答案，因为要区最小值，所以设成很大的值
bool t = false;//判断是否输出-1 
int n , k , minl , maxr;
int main(){
	cin >> n >> k;
	for (int i = 1; i <= n; ++ i) {
		int l , r;//区间的左右端点
		cin >> l >> r;
		if (l > r) swap (l , r);//若l比r大，那么交换l，r 
		minl = min (minl , l);//左端点的最小值
		maxr = max (maxr , r);//右端点的最大值
		for (int j = l; j <= r; ++ j)
			a[j] ++;//将这个区间里的数的出现次数++
	}
	for (int i = minl; i <= maxr; ++ i) //枚举每一个数
		if (a[i] == n) {//如果他是公共点
			ans = min (ans , abs(i - k));//更新答案
			t = true;//那么他就有公共节点，不用输出-1，把他设成false 
		}
	if (!t) puts("-1");//如果他们没有公共区间，输出-1。 
	else cout << ans << endl;
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
在一个坐标轴上给出 $n$ 个区间 $[\min(a_i,b_i),\max(a_i,b_i)]$ 和一个点 $x_0$，问这些区间的公共部分距离这个点的最近距离，如果不存在，输出 `-1`。

**数据范围：$1\leqslant n\leqslant 100$，$0\leqslant x_0,a_i,b_i\leqslant 1000$，$a_i\neq b_i$。**
## Solution
由于数据范围很小，因此我们考虑直接暴力模拟标记所有数轴上的点，然后再计算出所有被标记了 $n$ 次（即公共部分）的点到 $x_0$ 的距离的最小值即可。

注意可能有 $a_i>b_i$ 的情况，先交换再处理。另外需要特判一下无解。
## Code
```cpp
namespace Solution {
    const int N = 107;
	const int M = 1007;
    int n;
	int x;
	int ans = 0x3f3f3f3f;
	int l[N];
	int r[N];
	int vis[M];

 	void Main() {
        read(n, x);
		for(int i = 1; i <= n; ++i) {
			read(l[i], r[i]);
			if(l[i] > r[i])
				swap(l[i], r[i]);
			for(int j = l[i]; j <= r[i]; ++j)
				vis[j]++;
		}
		for(int i = 0; i <= 1000; ++i)
			if(vis[i] == n)
				ans = min(ans, abs(i - x));
		if(ans == 0x3f3f3f3f)
			write(-1);
		else
			write(ans);
		return;
	}
}
```

---

## 作者：AllanPan (赞：0)

## 一、本题的思路

我们先把题目抽象化：给定一堆区间，假如它们交为空，则输出$-1$，否则输出一个定点**走进**这个区间所需的最小距离。这样一来，我们的步骤也变得明确了：
### 1. 读出区间的交集
```cpp
for (int i = 1; i <= n; i++)
{
	cin >> a >> b;
	start[i] = min(a, b); // 每一个的起点
	end[i] = max(a, b); // 终点
	if (start[i] > startmax) // 最靠右的起点
		startmax = start[i];
	if (end[i] < endmin) // 最靠左的终点
		endmin = end[i];
}
```
### 2. 走进这个区间所需的最小距离
```cpp
if (startmax <= pos && pos <= endmin) // 在里面
		cout << 0;
else
{
	if (pos < startmax) // 在左边
		cout << (startmax - pos);
	else // 在右边
	{
		cout << (pos - endmin);
	}
}
```

## 二、完整代码
```cpp
#include <iostream>
using namespace std;

int main()
{
	int n, pos, start[105], end[105], a, b;
	int startmax = -1, endmin = 9999;
	cin >> n >> pos;
	for (int i = 1; i <= n; i++)
	{
		cin >> a >> b;
		start[i] = min(a, b);
		end[i] = max(a, b);
		if (start[i] > startmax)
			startmax = start[i];
		if (end[i] < endmin)
			endmin = end[i];
	}
	if (endmin < startmax)
		cout << -1;
	else
	{
		if (startmax <= pos && pos <= endmin)
			cout << 0;
		else
		{
			if (pos < startmax)
				cout << (startmax - pos);
			else
			{
				cout << (pos - endmin);
			}
		}
	}
	return 0;
}

```

---

## 作者：Ba_creeper (赞：0)

#### 题目大意

这道题主要思路是模拟，也用了一点暴力的思想。

题目给出一个一维的坐标轴，并在上面选取了一个点 $x_0$。之后给了我们 $n$ 个区间，要求我们找出这些区间的公共区间，输出这个子区间中对 $x_0$ 的最短距离。

在题目翻译中可能对于公共区间的表述不是很清楚。所有区间的共同部分才是公共区间。而不是只要有公共的即可。

#### 解决思路

对于上面公共区间的定义，我们可以清楚。只有当全部的区间都读入之后，我们才能找到公共区间。

看到数据范围，区间长度最大只有 $1000$，那么我们想到直接暴力开桶，用来存放坐标轴上的每个点被 $n$ 个区间覆盖的次数。很容易得出，只有覆盖次数为 $n$ 次时，这个点才是公共区间的一个元素。

当存到最后一个区间时，如果次数为 $n$，那么我们可以进行计算，不断更新最小的距离。

如果区间全部扫完，答案没有被更新，则说明没有公共区间。细节见代码部分。

#### Code

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;

ll n, x0, ans = 998244353; //ans记录答案
int a[1003]; //统计每个点出现的次数

int main()
{
    cin >> n >> x0; //如题目描述
    for (int i = 1; i <= n; ++i)
    {
        int l, r; //待读入区间的左端点和右端点
        cin >> l >> r; //读入区间
        if (l > r) //保证区间左边小，右边大，方便后续操作
            swap(l, r);
        for (int i = l; i <= r; ++i)
        {
            a[i]++; //累加每个点出现的次数
            if (a[i] == n) 
            /*
            当出现点的次数为 n 时，
            即此时的区间已经全部读入，
            说明这个点是公共区间的一部分。
            */
            {
                ll cha = i - x0; //计算这个点到x0的距离
                ans = min(ans, (cha >= 0 ? cha : -cha)); //更新答案
            }
        }
    }
    if (ans == 998244353) //ans的值没有被修改，说明没有公共区间
        ans = -1; //即输出 -1
    printf("%lld\n", ans); //输出答案
    return 0; //养成好习惯
}
```

---

## 作者：_Scaley (赞：0)

## 题目大意

给出 $n$ 个区间和一个点，求出这 $n$ 个区间的公共区间到这个点的距离并输出。

## 题目分析

这毫无疑问是求所有区间的交集，然后计算出给出的点到这个公共区间的距离，可以考虑模拟：

1. 设定所求公共区间的左右断点为 $l$ 和 $r$。

2. 在读入的时候不断缩短所查找的区间。

3. 计算点到区间的距离并输出。

**注意：输入的区间左右端点可能不按照顺序排列，需要判断一下。**



## 代码实现

```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 1000001
#define Mod 100003
using namespace std;
//-------------定义结构体-------------

//--------------定义变量--------------
int l, r, n, star;
//--------------定义函数--------------
inline int read() { // 快读
	int x = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
void swap(int &x, int &y) { // 交换函数
	x ^= y ^= x ^= y;
}
//---------------主函数---------------
int main() {
	n = read(); star = read();
	l = read(); r = read(); // 先把第一个区间读入
	if (l > r) swap(l, r); // 有的给出区间左右端点未按照顺序排列，需要判断一下
	for (int i = 2, x, y; i <= n; ++i) {
		x = read(); y = read();
		if (x > y) swap(x, y); // 判断左右端点顺序，避免出现空集
		if (x > l) l = x; // 缩短查找区间范围
		if (y < r) r = y;
	}
	if (l > r) puts("-1"); // 空集，不存在答案，输出 -1
	else if (l <= star && r >= star) puts("0"); // 点在区间范围内，距离为 0
	else if (l > star) printf("%d\n", l - star); // 如果点在区间左边，则距离为点到区间左端点的距离
	else printf("%d\n", star - r); // 如果点在区间右边，则距离为点到区间右端点的距离
	return 0;
}
```

---

