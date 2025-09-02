# Clock and Strings

## 题目描述

There is a clock labeled with the numbers $ 1 $ through $ 12 $ in clockwise order, as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/dc1b9b8cdcc08927ff93e17ee0e104c325e2c451.png)In this example, $ (a,b,c,d)=(2,9,10,6) $ , and the strings intersect.

Alice and Bob have four distinct integers $ a $ , $ b $ , $ c $ , $ d $ not more than $ 12 $ . Alice ties a red string connecting $ a $ and $ b $ , and Bob ties a blue string connecting $ c $ and $ d $ . Do the strings intersect? (The strings are straight line segments.)

## 说明/提示

The first test case is pictured in the statement.

In the second test case, the strings do not intersect, as shown below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/23548bb954ac5431bdc4259b9b8d572eb5d94e6e.png)

## 样例 #1

### 输入

```
15
2 9 10 6
3 8 9 1
1 2 3 4
5 3 4 12
1 8 2 10
3 12 11 8
9 10 12 1
12 1 10 2
3 12 6 9
1 9 8 4
6 7 9 12
7 12 9 6
10 12 11 1
3 9 6 12
1 4 3 5```

### 输出

```
YES
NO
NO
YES
YES
NO
NO
NO
NO
NO
NO
YES
YES
YES
YES```

# 题解

## 作者：cute_overmind (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/CF1971C)
### 题目大意
给你一个钟表，然后给你两条线，判断两条线是否**相交**。

在思考的时候，想到过从一点引出的两条线段算不算相交呢？

在测试数据的时候，发现数据里面没有从一点引出的两条线段的情况，所以不做考虑。

### 题目分析
考虑**分类讨论**。

看到题目给的这张图，其实我们可以通过判断其中一条线段两端点所在的圆弧上是否有**多余的点**，对此进行分类讨论。如果有一个其它线段上的点，那么就输出 `NO`；反之输出 `YES`。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve()
{
	int a , b , c , d , cnt = 0;
	cin >> a >> b >> c >> d;
	if(a < b) swap(a , b);//为了方便下一步进行分类讨论 
	if(c >= b && c <= a) cnt++;
	if(d >= b && d <= a) cnt++;
	if(cnt % 2) cout << "YES" << "\n";//如果只有一个点，输出NO 
	else cout << "NO" << '\n';//反之输出YES 
}
int main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
} 
```

---

## 作者：fwtv_24 (赞：1)

### 题目大意
输入 $a,b,c,d$ $(a,b,c,d≤12)$ ， $a,b,c,d$ 为时钟上的点且并不相同，问线段 $ab$ 与 $cd$ 是否相交。
### 简单分析
我们将输入的 $a,b$ 进行处理，使 $a>b$ ，那么接下来我们就对相交的情况进行讨论。

 $c$ 一定在 $ab$ 一侧，举个例子： 当 $a<c<b$ 时
 
 则我们就可以对 $d$ 进行分类讨论：
1. 若 $d$ 点也在这一侧，那么就可以直接判定不相交。
 
2. 若 $d$ 在另外一侧，那么就一定会相交
 
 另一边也是一样的道理
 
 详细看注释
 
###  AC CODE
 ```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,b,c,d;
signed main()
{
	cin>>T;
	while(T--)//多组数据
	{
		cin>>a>>b>>c>>d;
		if(a>b) swap(a,b);
		if(c>a&&c<b)//c 在 ab 其中一侧
		{
			if(d>a&&d<b) cout<<"NO"<<"\n";//若 d 也在同侧，则一定不相交
			else cout<<"YES"<<"\n";//d 不在同侧，一定相交
		}
		else if(d>a&&d<b)//当 c 不在这一侧，但是 d 在这一侧，即 c,d 二点异侧，一定相交
		{
			 cout<<"YES"<<"\n";
		}
		else cout<<"NO"<<"\n";//c,d 都不在这一侧，即 c,d 在 ab 的同侧，一定不相交
	}
	return 0;//完结撒花QWQ
}
```
### 彩蛋
值得注意的是，在英语原文的输出格式中提到： `You can output "YES" and "NO" in any case (for example, strings "yEs", "yes", and "Yes" will be recognized as a positive response).`

给大家翻译一下：`您可以以任意形式输出 "YES" 和 "NO" （例如，字符串 "yEs" 、 "yes" 和 "Yes" 都将会被识别）。`

所以这个彩蛋你还不去试试吗（大雾）

---

## 作者：JXR_Kalcium (赞：1)

## 题目大意
有一个表盘上有两条线段，端点分别为 $a,b$ 和 $c,d$，现在给出这四个数，问两条线段是否相交。

## 解题思路
首先，因为表盘被其中一条线段分成了两半，所以我们完全可以**只枚举一半上的数字**，如果只有 $c,d$ 其中之一，那么另一端点肯定在另一半，两条线段一定相交；否则，如果没有或有两个端点，那么两条线段就不会相交。

## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int t,a,b,c,d,bz;

int main()
{
	scanf("%d",&t);
	
	while(t--)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d); bz=0;
		if(a>b) swap(a,b); // 从a枚举到b
		
		for(int i=a+1; i<b; ++i)
		{
			if(i==c) ++bz;
			if(i==d) ++bz;
		}
		
		if(bz==1) printf("YES\n");
		else printf("NO\n");
	}

	return 0;
}
```

---

## 作者：Dream_Mr_li (赞：1)

## Problem

有一个时钟，上面按顺时针顺序标有 $1$ 到 $12$ 的数字。

爱丽丝和鲍勃有四个**不同的**整数 $a$、$b$、$c$、$d$，且不大于 $12$。爱丽丝用红色字符串连接 $a$ 和 $b$，鲍勃用蓝色字符串连接 $c$ 和 $d$。这两条线相交吗？(字符串是直线段）。

## Solution

这题一看就是找规律，只需要造一个数轴，统计他们在数轴上的位置，最后再看他们是否交叉就好啦。

拿一组样例来看：

`
2 9 10 6
`

![](https://espresso.codeforces.com/61e348551b1e468c2730b6e3b36e33b76e3132ca.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/70z0p581.png)

可以看到，他们的两个端点在数轴上是交叉的，所以输出 `YES`。

最后输出 `YES` 或 `NO` 就可以。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
void solve(){
	int a,b,c,d;
	string s;
	cin>>a>>b>>c>>d;
	for(int i=1;i<=12;i++){
		if(i==a||i==b){//记录在数轴上
			s+="1";
		}if(i==c||i==d){
			s+="2";
		}
	}
	if(s=="1212"||s=="2121"){
		cout<<"YES\n";
	}else{
		cout<<"NO\n";
	}
}
int n;
signed main(){
	cin>>n;
	while(n--){
		solve();
	}
	return 0;
} 
```

---

## 作者：Just_A_Sentence (赞：1)

# 题意翻译

输入 $t(1\le t\le 5940)$ 行，每行 $4$ 个整数 $a,b,c,d(1\le a,b,c,d\le 12)$，表示钟面上两条线段的四个端点所对应的刻度，问这两条线段会不会在钟面上相交。如果会，则输出“YES”，不会则输出“NO”。

# 分析

很显然，研究一条线段比研究两条线段容易得多。所以我们固定好一条线段，来研究另一条线段。

而另一条线段要和第一条线段相交，就必须让它的两个端点在第一条线段的两端。

所以这题代码如下：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		if(a>b) swap(a,b);\\让小的端点在前面，方便判断。
		if(c>d) swap(c,d);\\同上
		if(c>=a&&c<=b){\\如果第二条线段有一个端点在第一条线段下面。
			if(d<=a||d>=b){\\如果另一个端点在第一条线段上面，则两条线段相交。
				printf("YES\n");
			}
			else printf("NO\n");\\否则不相交。
		}
		else{\\和上面相似。
			if(d>=a&&d<=b){
				printf("YES\n");
			}
			else printf("NO\n");
		}	
	}
	return 0;//完结撒花~~
}
~~~

---

## 作者：L_xcy (赞：0)

[Clock and Strings](https://codeforces.com/contest/1971/problem/C)

---
### 题目大意
给你四个整数 $a$ , $b$ , $c$ , $d$ $(1 \le a,b,c,d \le 12)$ ,分别代表钟表上的四个点。

其中 $a$ 和 $b$ 连一条直线， $c$ 和 $d$ 连一条直线，如果两条线相交，输出 ``YES`` ，否则输出 ``NO`` 。



 当  $(a,b,c,d)=(2,9,10,6)$，如图：
 
 ![](https://espresso.codeforces.com/61e348551b1e468c2730b6e3b36e33b76e3132ca.png)
 
 ---
 ### 解题思路
 
把每个点走一次，如果我们连续经过两次第一条线或两次第二条线，则字符串不会相交；反之，则会相交。

---
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
void solve() {
	int a,b,c,d,bz[13];
	memset(bz,0,sizeof(bz));
	cin>>a>>b>>c>>d;
	string ans;
	for(int i=1;i<=12;i++) {
		if(i==a or i==b) {
			ans+='1';
		}
		if(i==c or i==d) {
			ans+='2';
		}
	}
	if(ans=="1212" or ans=="2121") {
		cout<<"YES\n";
	}
	else {
		cout<<"NO\n";
	}
}
int main() {
	cin>>T;
	while(T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：liuhongyang123 (赞：0)

# 题目大意

一共有 $T$ 组数据，每组数据给你一个时钟，并且会给出两条直线的四个顶点，要求你去判断这两条之间是否相交。

# 解法

我们先让 $a < b$ 且 $c < d$，那么相交的情况只有两种:

1. $a<c<b<d$
2. $c<a<d<b$

其他情况都不可能。

# Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,b,c,d;
signed main(){
	cin>>T;
	while(T--){
		cin>>a>>b>>c>>d;
		if(a>b) swap(a,b);
		if(c>d) swap(c,d);
		if(a<c&&c<b&&b<d) cout<<"YES";
		else if(c<a&&a<d&&d<b) cout<<"YES";
		else cout<<"NO";
		cout<<endl;
	}
	return 0;
}
```

### 完结散花

---

## 作者：zzx114514 (赞：0)

# 题目大意
给定 $a,b,c,d$ $4$ 个整数，表示在钟面上的 $4$ 个点，分别连接 $a,b$ 和 $c,d$，若两条线段相交输出 `YES`，否则输出 `NO`。  
# 解题思路
先把 $a,b,c,d$ 分别按顺序排列，方便处理。   
显然，当 $a,b,c,d$ 在钟面上交替排列时线段会相交，即 $a<c<b<d$ 或 $c<a<d<b$，否则不会相交，判断一下即可。
# 完整代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll t,a,b,c,d; 
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>a>>b>>c>>d;
		if (a>b) swap(a,b);
		if (c>d) swap(c,d);
		if ((a<c && c<b && b<d) || (c<a && a<d && d<b)) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}

```

---

## 作者：Annihilation_y (赞：0)

# 思路
可以不难看出，$a$ 和 $b$ 这条线可以将这个钟分成两部分。如下图所示，这个图会被分成红绿两部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/m30ya6m5.png)

那么，我们可以设置一个 $num$ 变量，记录从 $a$ 节点顺时针旋转到 $b$ 节点过程中，如果碰到了 $c$ 或 $d$ 节点，就将 $num \gets num + 1$。如果 $num$ 是 $1$ 的话，就有交叉。

~~~c++
#include <bits/stdc++.h>
using namespace std;
int main(){
	int T;cin>>T;
	while(T--){
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		int num=0;
		for(int i=a;i<=((b<a)?(b+12):b);i++){
			int x=i>12?(i%12):i;
			if(x==c||x==d) num++; 
		}
		if(num==1) cout<<"Yes\n";
		else cout<<"No\n";
	}
}
~~~

---

## 作者：zhangxiaohan007 (赞：0)

## 思路
![](https://cdn.luogu.com.cn/upload/image_hosting/2r5upqez.png)
由题可得，大概有两种不相交的情况（见上图），我们只需要把 $a,b,c,d$ 按照 $a>b,c>d$ 的顺序排序，接着进行判断即可。
## AC代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define maxn 500+10
#define inf 1e9+7
using namespace std;
int a,b,c,d;
void solve()
{
	cin>>a>>b>>c>>d;
	int e=a,f=c;
	a=max(a,b);
	b=min(e,b);
	c=max(c,d);
	d=min(f,d);
	if(a>c&&b<d||c>a&&b>d||b>c||a<d)//不相交  
	{
		cout<<"NO\n";
	}
	else cout<<"YES\n";
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		solve();//多测 
	}
	return 0;
}

```

---

## 作者：ggylz49 (赞：0)

## 思路分析
本题的重点在于，如何判断两条线在钟面上是否相交。

首先，Alice 拉出一条 $a$ 到 $b$ 的线，这条线把钟面分成了不平均的两半。

于是，Bob 也拉了一条线。这条线的头尾若正好分别在钟面的两半（一头在左边一半，另一头在右边一半）或是和 $a,b$ 重合，则两条线相交，否则不相交。

### 形式化

钟面左边一半包含的数字可以用一个集合 $s1$ 表示。例如当 $a=2,b=9,c=10,d=6$ 时，$s1=\{2,3,4,5,6,7,8,9\}$ 或 $\{9,10,11,12,1,2\}$。而钟面另一半的 $s2=\{9,10,11,12,1,2\}$ 或 $\{2,3,4,5,6,7,8,9\}$。总之，$s1$ 和 $s2$ 必须分别表示钟面两半，顺序没有太大的关系。

此时 $c=10,d=6$。可以发现，$c,d$ 分别处于两个集合中。这说明 Bob 拉的线横跨了钟面两半，则线相交。反之，$c,d$ **只处于同一个集合中**（**另一个集合没有** $c,d$），则没有横跨钟面两半，线不相交。
## 逐步解决
首先需要一个集合构造器。可以使用 STL 中的 set 容器进行存储集合。set 在本题可以运用到：
- `set<int>s;` 构造出数据类型为 int 的集合 $s$。例如 `set<int>s1,s2;` 就构造出 int 类型的两个集合 $s1,s2$。当然数据类型也可以换成其他的类型，也可以是自己定义的结构体。
- `s.insert(x);` 在集合中加入元素 $x$。
- `s.end()` 返回集合中最后一个元素的下一个元素的地址。很少直接使用，一般会配合其他函数进行比较，以确认某个元素是否存在。
- `s.find(x)` 在集合中查找 $x$。找到，返回 $x$ 的地址。否则返回 `s.end()`。

于是我们用一个函数配合 set 存储某一半的钟面。
```cpp
void make(int x,int y,set<int>&s)//&对s进行引用传参，相当于修改输入的 set 容器；制作从x到y的一半钟面
{
    do
    {
        s.insert(x);//加入x
        x++;
        if (x>12)x-=12;//如果超出钟面范围（13），减去12变成1继续
    }while(x!=y);//循环条件：x不等于y
    s.insert(y);//y还没有加入集合中呢！加入y
}
```
接着，判断输入数据的局部程序：
```cpp
int a,b,c,d;
cin>>a>>b>>c>>d;
set<int>s1,s2;
make(a,b,s1);//制作钟面，从b到a的一半和从a到b的一半，存进集合s1和s2
make(b,a,s2);
if ((s1.find(c)!=s1.end()&&s2.find(d)!=s2.end())||(s1.find(d)!=s1.end()&&s2.find(c)!=s2.end()))cout<<"YES\n";
//不是end()说明找到了，否则没找到。注意c和d在两个集合中的位置可能是颠倒的，例如c在s1，d在s2，反之亦然，再加一个判定（||之后）
else cout<<"NO\n";//不相交
```
## Code
```cpp
#include <iostream>
#include <set>//使用set加<set>头文件
using namespace std;
void make(int x,int y,set<int>&s)
{
    do
    {
        s.insert(x);
        x++;
        if (x>12)x-=12;
    }while(x!=y);
    s.insert(y);
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        set<int>s1,s2;
        make(a,b,s1);
        make(b,a,s2);
        if ((s1.find(c)!=s1.end()&&s2.find(d)!=s2.end())||(s1.find(d)!=s1.end()&&s2.find(c)!=s2.end()))cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
```

---

## 作者：zhangyuhaoaa (赞：0)

## 题意

有一个时钟，给出四个数 $a,b,c,d$，把 $a,b$，$c,d$ 连线。问 $ab$ 和 $cd$ 是否能交叉。

## 思路

这道题我们可以判断这四个数是否是 $a,c,b,d$ 或 $a,d,b,c$ 或 $b,d,a,c$ 或 $b,c,a,d$ 或 $c,a,b,d$ 或 $c,b,d,a$ 或 $d,a,c,b$ 或 $d,b,c,a$。这几种情况都可以的。挨个判断即可。

## code

```cpp
#include <bits/stdc++.h>
#define re register
#define il inline
#define int long long
#define endl '\n'
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int P = 998244353;
const int INF = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e6 + 5;

int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return x * f;
}

int a, b, c, d;

void work() {
	cin >> a >> b >> c >> d;
	if (a < c && c < b && b < d) {
		cout << "YES" << endl;
	} else if (b < c && c < a && a < d) {
		cout << "YES" << endl;
	} else if (a < d && d < b && b < c) {
		cout << "YES" << endl;
	} else if (b < d && d < a && a < c) {
		cout << "YES" << endl;
	} else if (c < a && a < d && d < b) {
		cout << "YES" << endl;
	} else if (c < b && b < d && d < a) {
		cout << "YES" << endl;
	} else if (d < a && a < c && c < b) {
		cout << "YES" << endl;
	} else if (d < b && b < c && c < a) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}

signed main() {
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    fst;
    
    int t;
    cin >> t;
    while (t --) {
    	work();
	}

    return 0;
}
```

---

## 作者：keep_shining (赞：0)

## 题目大意：
有 $T$ 组数据，每组数据输入 $a,b,c,d$ 四个数，在钟表上将 $a,b$ 连起来，$c,d$ 连起来，问这两条连线是否相交。

## 思路：
首先我们保证 $a \le b$，这样对后面有帮助。

然后我们来想，要想两线相交，必须一个在 $a,b$ 连线的下面，一个在 $a,b$ 连线的上面，也就是 $c$ 和 $d$ 中间只能有一个大于等于 $a$，小于等于 $b$ 的，那么我们可以用
```cpp
if(((c>=a&&c<=b)&&!(d>=a&&d<=b))||((!(c>=a&&c<=b)&&(d>=a&&d<=b))))
```
来判断是否 $c,d$ 中只有一个满足条件。

这样我们就可以解决掉本题了。

## AC code:
```cpp
#include <bits/stdc++.h>

using namespace std;

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int t;

void work()
{
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	if(a>b)swap(a,b);//保证a<=b
	if(((c>=a&&c<=b)&&!(d>=a&&d<=b))||((!(c>=a&&c<=b)&&(d>=a&&d<=b))))cout<<"YES"<<endl;//如果c,d之中只有一个小于等于a,大于等于b的，那两条线就会相交
	else cout<<"NO"<<endl;//否则不会相交
}
int main(){
	fst
	cin>>t;
	while(t--)work();
	return 0;
}

```

---

## 作者：All_Unluck_Beginning (赞：0)

# 题解：CF1971C Clock and Strings

## 题意

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/dc1b9b8cdcc08927ff93e17ee0e104c325e2c451.png)

在上图的一个圆中，给予你四个点 $a,b,c,d$，判断线段 $ab$ 与线段 $cd$ 是否相交。

## 思路

先设置一个字符串 $s$。

从 $1$ 到 $12$ 扫描，如果扫描到 $a,b$，则在 $s$ 中加入 $a$，如果扫到 $c,d$，则加入 $b$。

经过实践足以证明，若 $ab$ 与 $cd$ 相交，$s$ 必为 $abab$ 或 $baba$。

## Ac code

```
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,t;
int main() {
	cin>>t;
	while(t--) {
		cin>>a>>b>>c>>d;
		string s;
		for (int i=1;i<=12;i++) {
			if(i==a||i==b)s+="a";
			if(i==c||i==d)s+="b";
		}
		if(s=="abab"||s=="baba"){
			cout<<"YES\n";
		}else{
			cout<<"NO\n";
		}
	}
	return 0;
}
```

---

## 作者：roumeideclown (赞：0)

# 题解：CF1971C Clock and Strings

## 题意简述

给出 $4$ 个在 $[1,12]$ 间的相异整数 $a,b,c,d$，判断在时钟上线段 $ab$ 与线段 $cd$ 是否相交。

## 解法分析

通过观察不难发现，若点 $c$ 与点 $d$ 在线段 $ab$ 的同侧，则不相交；否则相交。分类讨论即可：令 $a<b$，可以发现对于 $c$，当 $c>a$ 且 $c<b$ 时 $c$ 处在线段 $ab$ 一侧，否则处在另一侧；对于 $d$ 同理。

具体细节见如下代码。

## 代码实现

```cpp
#include<bits/stdc++.h>
//#pragma G++ optimize(2,3,"Ofast")
using namespace std;
typedef long long ll;
void work() {
	int a,b,c,d;
	scanf("%d%d%d%d",&a,&b,&c,&d); //输入
	if(a>b) { //保证 a<b，方便处理
		swap(a,b);
	}
	if(c>a&&c<b) { //若 c 被夹在 a 与 b 之间
		if(!(d>a&&d<b)) { //若 d 没有被夹在中间
			printf("YES");
		}
		else {
			printf("NO");
		}
	}
	else { //若 c 没有夹在 a 与 b 之间
		if(!(d>a&&d<b)) { //若 d 没有被夹在中间
			printf("NO");
		}
		else {
			printf("YES");
		}
	}
	printf("\n");
}
int main() {
//  ios::sync_with_stdio(false);
//  cin.tie(0),cout.tie(0);
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++) { //多组数据
		work();
	}
	return 0;
}

```

---

## 作者：tder (赞：0)

[CF1971 场记](https://tder6.github.io/articles/CF1971A%20to%20CF1971G%20%E5%9C%BA%E8%AE%B0.html) 食用效果更佳。

---

**【题意】**

在时钟上的 $1\sim12$ 刻度处有 $4$ 点 $A,B,C,D$，连接 $AB$ 和 $CD$，判断是否有交点。多测。

**【思路】**

令 $A(a),B(b),C(c),D(d)$。考虑将 $A$ 和 $B$ 交换，使得 $a\le b$，其余同理。

不难发现若四点满足 $a\le c\le b\le d$ 或是 $c\le a\le d\le b$ 则有交点，即 $[a,b]\cup[c,d]$ 不为 $\varnothing$。此处可以感性理解一下。

具体实现的时候可以先特判一下两点重合的情况。

单组数据时间复杂度 $O(1)$。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 1e5 + 5;
int a, b, c, d;
void solve() {
	cin>>a>>b>>c>>d;
	if(a == c || b == c || a == d || b == d) {
		cout<<"YES"<<endl;
		return;
	} else if(a == b || c == d) {
		cout<<"NO"<<endl;
		return;
	}
	if(a > b) swap(a, b);
	if(c > d) swap(c, d);
	if(a < c && c < b && b < d) {
		cout<<"YES"<<endl;
		return;
	}
	if(c < a && a < d && d < b) {
		cout<<"YES"<<endl;
		return;
	}
	cout<<"NO"<<endl;
}
int t;
signed main() {
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：huanglihuan (赞：0)

## [原题链接](https://codeforces.com/contest/1971/problem/C)
### 题目大意和目的
给你一个时钟，并且会给出两条直线的四个顶点，要求你去判断这两条之间是否相交。
### 题目分析和思路
通过观察我们不难发现，如果两条直线交叉，那么按照遍历到的顶点分类，顺序只有两种：
- $红顶点 - > 蓝顶点 - > 红顶点 - > 蓝顶点$ 
- $蓝顶点 - > 红顶点 - > 蓝顶点 - > 红顶点$

因此，只需要把钟面上的每个顶点暴力搜索一遍，然后判断是否为可能的两种情况并输出就可以了。
### Code：
```cpp
#include <bits/stdc++.h>
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 998244353
#define MOD 1000000007
using namespace std;
const int N = 1e5 + 5;

int a [N];

void solve ()
{
	int a,b,c,d;
	cin >> a >> b >> c >> d;
	string s = "";
	for (int i = 1;i <= 12;i ++)
		if (i == a || i == b) s += 'R';// 用R代表红色
		else if (i == c || i == d) s += 'B';// 用B代表蓝色
	if (s == "RBRB" || s == "BRBR") cout << "YES";
	else cout << "NO";
	cout << endl;
}
signed main () {
	ios :: sync_with_stdio (false);
	cin.tie (0),cout.tie (0);
	int T;
	cin >> T;
	while (T --) solve ();
	return 0;
}
```

---

## 作者：Xssion37_XY (赞：0)

### 前情提要

[题目链接](https://www.luogu.com.cn/problem/CF1971C)

[更好的阅读体验](https://www.luogu.com.cn/article/r8rmr8lj)

### 实际分析

刚开始我还想用斜率做的，但是没找到第二个点，就放弃了。

简单分析一下线的相交即可。

我们假设 $a<b,c<d$。

那么这两条线相交满足:

$$a<c<b<d$$

$$c<a<d<b$$

输出题目对应的要求即可。

### 代码部分

```cpp
#include <iostream>
#define int long long
using namespace std;
const int MAXX = 1e6 + 11;
signed main() {
	int T;
	cin >> T;
	while (T --) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		if (a > b) {
			swap (a, b);
		}
		if (c > d) {
			swap (c, d);
		}
		if (a < c and c < b and b < d) {
			cout << "YES\n";
		} else if (c < a and a < d and d < b) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
	return 0;
}
```

完结撒花！

---

## 作者：mc_xiexie (赞：0)

# CF1971C Clock and Strings
## 题意

给出红线与蓝线的端点，判断红线与蓝线是否相交。

## 思路
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/dc1b9b8cdcc08927ff93e17ee0e104c325e2c451.png)

由此图可见，蓝线和红线要相交，蓝线的两个点分别在红线两端，此时输出 YES。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1971C/23548bb954ac5431bdc4259b9b8d572eb5d94e6e.png)

由此图可见，蓝线的两个点不在红线两端只在红线一侧，就不相交，此时输出 NO。

由此可得：
~~~
	for (int i = 1; i <= 12; i++) {
    		if (i == a || i == b) {
    		    s += "r";
    		}
    		if (i == c || i == d) {
    		    s += "b";
    		}
    	}
    	if(s == "rbrb" || s == "brbr"){
    	    cout<<"YES\n";
    	}
      	else{
    	    cout<<"NO\n";
    	}
~~~
## 完整代码
```
#include <bits/stdc++.h>
using namespace std;
int main() {
	int t; cin >> t; 
	while(t--){
	    int a, b, c, d;
    	cin >> a >> b >> c >> d;
    	string s;
    	for (int i = 1; i <= 12; i++) {
    		if (i == a || i == b) {
    		    s += "r";
    		}
    		if (i == c || i == d) {
    		    s += "b";
    		}
    	}
    	if(s == "rbrb" || s == "brbr"){
    	    cout<<"YES\n";
    	}
    	else{
    	    cout<<"NO\n";
    	}
	}
}
```

---

## 作者：Harrylzh (赞：0)

先把输入设为 $a<b,c<d$，考虑相交的情况一定是如下两种：

- $a<c<b<d$
- $c<a<d<b$

判断这两种情况输出 `YES`，其他情况输出 `NO` 即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		long long a,b,c,d;
		cin>>a>>b>>c>>d;
		if(a>b) swap(a,b);
		if(c>d) swap(c,d);
		if((a<c&&c<b&&b<d)) cout<<"YES\n";
		else if((c<a&&a<d&&d<b)) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

