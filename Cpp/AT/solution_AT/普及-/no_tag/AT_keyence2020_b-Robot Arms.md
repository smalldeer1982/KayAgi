# Robot Arms

## 题目描述

## 题意描述

有n个区间,第i个区间的范围是[ x[i]-l[i],x[i]+l[i] ]。要求选择若干区间使其不重叠。求最多可以选择多少区间。

## 说明/提示

1<=n<=100000

0<=x[i]<=1000000000(10亿)

0<l[i]<=1000000000

## 样例 #1

### 输入

```
4
2 4
4 3
9 3
100 5```

### 输出

```
3```

## 样例 #2

### 输入

```
2
8 20
1 10```

### 输出

```
1```

## 样例 #3

### 输入

```
5
10 1
2 1
4 1
6 1
8 1```

### 输出

```
5```

# 题解

## 作者：Astatinear (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/AT5748)

### 思路
**很显然,这个题目一看就知道是一个贪心题目。**

首先,这个题目的意思是给定一些区间,让我们求出使所有区间不重叠,可以选择最多少个区间。比较容易,这个题目是贪心,我们仔细一想就可以想出怎么个贪心法子。

所以,我们为了放置更多的区间,我们就必须让上一个区间的右端点尽可能的小,这样我们才有更大的空间去放置更多的区间。所以根据这种思想,我们就想到了将每一个区间的右端点从小到大排序,然后再将排完序后的区间根据规则模拟一遍即可。

### 代码
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int n;
int x[100005],p[100005];
struct node
{
	int l,r;
	bool operator <(const node &n)const
	{
		return r<n.r;//按照右端点进行排序
	}
}arr[100005];//储存每个区间的右端点和左端点
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>x[i]>>p[i];
		arr[i].l=x[i]-p[i];//储存左端点
		arr[i].r=x[i]+p[i];//储存右端点
	}
	sort(arr+1,arr+n+1);//排序
	int now=INT_MIN,ans=0;
	for(int i=1;i<=n;++i)
	{
		if(arr[i].l>=now)//判断是否可以放下这个区间
		ans++,now=arr[i].r;
	}
	cout<<ans<<endl;//输出答案
}
```

### ~~完结撒花~~

---

## 作者：幻之陨梦 (赞：4)

$Solution:$

这道题基本上可以说是一道原题，[详细内容参考这里](https://loj.ac/problem/10000)，我们只需要稍微改动一部分就可以了，那就是在定义起点和终点的时候稍微算一下就可以了。那么为什么需要用每个区间的截止位置排序呢？因为当当前区间的截止为止越靠前后面留的空间也就越大，可以放下的区间也就越多，所以我们需要按每个区间的截止为止从小到大排序。

$code:$
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//标准数据库
inline int read()//快速读入
{
    int x=0;bool f=1;char c=getchar();
    if(c==EOF) return 0;
    while(c<'0' || c>'9'){if(c=='-') f=0;c=getchar();}
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return f?x:-x;
}
struct node//定义结构体
{
    int st,ed;//记录该区域起点与终点的数值
    bool operator < (const node &x)const//重载运算符
    {
        return ed<x.ed;
        //这里一定要在该区域的结束从小到大排序，因为这样可以让更多的区域加入进来
    }
}a[100010];
int n,t,ans=1;
int main()
{
    n=read();//读入n
    for(int i=0;i<n;i++)
    {
        int x=read(),l=read();//读入 x,l
        a[i].st=x-l;//左端点
        a[i].ed=x+l;//右端点
    }
    sort(a,a+n);//排序
    t=a[0].ed;//用一个变量记录下当前可行区域的结束位置
    for(int i=1;i<n;i++)
    {
        if(a[i].st>=t)//如果下一个区间的开头大于当前区间结尾
        {
            ans++;//计数器++
            t=a[i].ed;//更新结束位置
        }
    }
    printf("%d\n",ans);//输出答案，因为是AT的题，所以记得换行
    return 0;
}
```
如果这篇文章给予了你帮助，那你就点个赞再走吧，Thanks♪(･ω･)ﾉ

~~PS：这回说明不过少了吧~~

---

## 作者：eEfiuys (赞：1)

题目：[AT5748](https://www.luogu.com.cn/problem/AT5748)
## 贪心。
- 用 struct 或 pair 存左右端点；
- 这里用 struct, $s(i).a$ 表示左端点 $x(i)-l(i)$, $s(i).b$ 表示右端点 $x(i)+l(i)$；
	- **当 $s(i).a \ge s(j).b$ 时区间 $s(i)$ 与 $s(j)$ 不重叠**；
    - 当 $l(i)<x(i)$ 时, $s(i).a<0$。
- 要使第 $i$ 次选择后能选的最多, $s(i).b$ 就要最小，所以**按照右端点排序**后**从 $s(1)$ 枚举到 $s(n)$**。
	- 用 $r$ 存最后一个选择的区间的右端点；
    	- 因为 $s(i).a$ 可能为负，所以 **$r$ 初始为 $-1e9$**。
    - 当 $s(i).a \ge r$ 时，**最后一个选择的区间更新为 $s(i)$**。

------------

**AC代码如下：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r=-1e9,ans;
const int N=1e5+1;
struct node
{
	int a,b;	
}s[N]; //结构体存端点。
bool cmp(node x,node y)
{
	return x.b<y.b;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x,l;
		cin>>x>>l;
		s[i].a=(x-l);
		s[i].b=(x+l);
	}
	sort(s+1,s+n+1,cmp); //按照右端点排序。
	for(int i=1;i<=n;i++)
		if(s[i].a>=r) //不重叠。
		{
			ans++;
			r=s[i].b;
		}
	cout<<ans;
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：0)

贪心。

题目要求你在一个数轴上放机器人，每个机器人的占的位置是 $[ x-l,x+l]$，问最多能放多少个。

我们考虑从前往后放，那么显然，对于两个机器人，结束位置较小的那一个，剩余的空间就会相对多，此时，在剩余的空间内，可以放置更多的机器人。

于是我们可以按照结束位置对 $n$ 个机器人进行排序，设 $now$ 表示剩余部分的起点位置，那么当第 $i$ 个机器人的开始位置 $start_i \ge now$ 的时候，我们就放这个机器人，然后 $now \leftarrow ended_i$ 就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Node {
  int start,
      ended;
} a[114514];
bool cmp(Node a, Node b) {
  return a.ended < b.ended;
}
signed main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    int x, l;
    cin >> x >> l;
    a[i].start = x - l, a[i].ended = x + l;
  }
  sort(a + 1, a + n + 1, cmp);
  int now = a[1].ended, cnt = 1;
  for (int i = 2; i <= n; ++i) {
    if (a[i].start >= now) {
      ++cnt;
      now = a[i].ended;
    }
  }
  cout << cnt;
}
```

---

## 作者：iminzhi (赞：0)

# 贪心
## [题目传送门](https://www.luogu.com.cn/problem/AT5748)
因为所选区间不能重叠，所以我们要让右端点尽量小，那样我们才有更多的选择余地

对于输入和计算左右端点的部分，为了方便，我们可以建立一个结构体来存储，再用函数对其右端点进行排序

选择区间阶段，我们可以比较前后两个区间的右端点和左端点，如果之后区间的左端点大与现选区间的右端点，计数++

下面贴上代码(含注释)
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
struct arm{//定义 
	int x,y,l,r;//x,y用来输入,l,r是左右端点 
}a[100005];
bool Cmp(arm xx, arm yy){//排序函数 
	return xx.r < yy.r;//按照右端点从小到大排序 
}
int main(){
	int n,ans = 1;//因为第一个区间总是可以取的,所以ans = 1 
	cin >> n;
	for(int i = 0; i < n; i++){//输入 
		cin >> a[i].x >> a[i].y;
		a[i].l = a[i].x - a[i].y;
		a[i].r = a[i].x + a[i].y;
	}
	sort(a, a + n, Cmp);//排序 
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(a[j].l >= a[i].r){//比较 
				ans++;
				i = j;//如果能选取,跳到新选的区间 
			}
		}
	}
	cout << ans << endl;
	return 0;//结束撒花^_^
} 
```
蒟蒻的第一篇题解，望管理员大大通过

最后，~~我想不要脸地要个赞~~，谢谢您的观看

---

## 作者：Buried_Dream (赞：0)

## 题意：

给定 $n$ 个区间，找到最多的不重复的区间。

## 思路：

因为要找到尽肯能多的重复的区间，

如果一个区间的右端过长，导致后面的区间无法放，那这肯定不是最优解，

可以考虑贪心，那应该怎么去贪呢，

既然想要尽量多的不重复的区间，就要让上一个放的区间右端点尽可能小，

所以按照每个区间的右端点去排序就可以了。

这里用到结构体排序：

`STL` 中的sort可以排结构体，定义好排序规则就可以了。

这里给出链接：[STL排序](https://oi-wiki.org/basic/stl-sort/)

# AC code：

为了防抄袭，给出核心代码：
```cpp
	int n = read();
	for(int i = 1; i <= n; i++) {
		l_a[i] = read(), r_b[i] = read();
		qj[i].l = l_a[i] - r_b[i]; 
 		qj[i].r = l_a[i] + r_b[i]; 
 	} 
 	sort(qj + 1, qj + n + 1, cmp);
 	for(int i = 1; i <= n; i++) {
 		if(qj[i].l >= r) {
 			ans++;
 			r = qj[i].r;
		 }
	 }
	 cout << ans;
```


---

## 作者：Coros_Trusds (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15208784.html)

$\texttt{\color{red}upd~on~2021/9/1:}$修改了反例，更改了部分语句。

## 分析

看到这道题，可以说被翻译明示这是贪心题。

我们把每条线段的起点和终点算出来之后，再按照右端点从小到大排序。

**证明：按右端点升序排列可以得到最优值**

把右端点从左向右排，使得右端点以后的区间能有更大的空间覆盖。

比如现在有 $5$ 条线段，如下：

```plain
---
-
  ----
        -----
    ------
```

按右端点升序排序后：

```plain
-
---
  ----
    ------
        -----
```

最优解为：

```plain
-
  ----
        -----
```

如果按左端点升序排列，会发现什么？~~会发现我给的样例不好。~~

会发现答案还是一样。

那么如果把线段 $[1,3]$ 换成 $[2,\inf]$ 会这样（按左端点升序排列）：

```plain
-
 ------------------....------------
  ----
    ------
        -----
```
按这个形式的最优解就为：

```plain
-
 ---------------...-----

```

发现反例，所以得证。（~~伪证啊喂~~

## 代码

```cpp
//2021/8/30

#include <iostream>

#include <cstdio>

#include <algorithm>

#define int long long

#define debug(c) cerr<<#c<<" = "<<c<<endl

namespace Newstd
{
	inline int read()
	{
		int x=0,f=1;char ch=getchar();
		while(ch<'0' || ch>'9')
		{
			if(ch=='-')
			{
				f=-1;ch=getchar();
			}
		}
		while(ch>='0' && ch<='9')
		{
			x=x*10+ch-48;ch=getchar();
		}
		return x*f;
	}
	inline void print(int x)
	{
		if(x<0)
		{
			putchar('-');x=-x;
		}
		if(x>9)
		{
			print(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

const int ma=100005;

struct Node
{
	int l;
	
	int r;
};

Node node[ma];

inline bool cmp(Node x,Node y)
{
	return x.r<y.r;
}

#undef int

int main(void)
{
	#define int long long
	
	int n=read();
	
	for(register int i=1;i<=n;i++)
	{
		int x,L;
		
		scanf("%lld%lld",&x,&L);
		
		node[i].l=x-L;
		
		node[i].r=x+L;
	}
	
	sort(node+1,node+n+1,cmp);
	
	int now=node[1].r,ans=1;
	
	for(register int i=2;i<=n;i++)
	{
		if(node[i].l>=now)
		{
			now=node[i].r;
			
			ans++;
		}
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
```

题解不易，留个赞吧~ $\texttt{qwq}$

---

## 作者：xh39 (赞：0)

贪心。

因为区间不能重叠,于是我们要让已选择的区间右端点尽量小,我们后面选择的空间才会更大。

所以我们可以直接按右端点从小到大排序,选择未重叠的并且右端点最小的。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct bisai{
	int begin;
	int end;
};
bisai a[1000005];
struct rule1{
	bool operator()(const bisai &s1,const bisai &s2){
		return s1.end<s2.end;
	}
};
int main(){
	int n,i,t=-2147483647,count=0;
	cin>>n;
	for(i=0;i<n;i++){
		cin>>a[i].begin>>a[i].end;
		a[i].begin-=a[i].end; //开始与结束为止处理,若不清楚,可以直接先输入x,l,然后begin=x-l,end=x+l;
		a[i].end=a[i].begin+(a[i].end<<1);
	}
	sort(a,a+n,rule1());
	for(i=0;i<n;i++){
		if(a[i].begin>=t){ //t表示覆盖到了t的位置。当大于t则未重叠。选择。
			count++;
			t=a[i].end;
		}
	}
	cout<<count;
} 
```

---

