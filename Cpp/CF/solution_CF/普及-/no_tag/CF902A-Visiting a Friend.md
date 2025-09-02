# Visiting a Friend

## 题目描述

Pig 想去拜访一位朋友。

Pig 的家位于坐标轴的起点，即点 $0$，而他朋友的家位于点 $m$。

在这段旅途中，Pig 可以通过传送门在坐标轴上移动。

在使用传送门时，Pig 需要先到达传送门所在位置，并从中选择一个目标位置。每个传送门都有其最远可达的终点，称为该传送门的限制点。

具体来说，位于点 $x$ 且限制点为 $y$ 的传送门可以将 Pig 从 $x$ 移动到 $[x, y]$ 之间（包括端点）的任意位置。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902A/92bc86959654b1405c61b81d368eac9f5c5fe404.png)请判断 Pig 是否可以仅通过传送门顺利抵达朋友的家，否则，Pig 将需要开车前往。

## 说明/提示

第一个例子如图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902A/753e62c3b07259c4bd5318fcbc1770c920417f65.png)

Pig 可以依次利用传送门，从家移动到点 $2$、再到点 $3$，最后到达朋友的家——点 $5$。

第二个例子如下图所示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF902A/907bb5d428f081e5cfddf9be149837a9d7265e2e.png)

可以看到，Pig 无法仅借助传送门从家到达朋友家。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3 5
0 2
2 4
3 5
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 7
0 4
2 5
6 7
```

### 输出

```
NO
```

# 题解

## 作者：yf最qhhh (赞：3)

这道题需要用到桶排序，没什么需要特别说明的，直接看代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool arr[100005];//定义一个桶
main(void){
	int n,m,a,b;
	scanf("%lld%lld",&n,&m);
	arr[0]=1;//他一开始的位置是0，所以需要把0标记为1
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a,&b);
		if(arr[a])for(int j=a;j<=b;j++)//即a在之前标记过的范围内，所以就用一个循环来把能传送的位置都标记
			arr[j]=1;
	}
	for(int i=0;i<=m;i++){
		if(!arr[i]){//一旦出现0，就意味着这个点传送不了，那么就输出 NO 并结束程序
			printf("NO");
			return 0;
		}
	}
	printf("YES");//如果所有点都包含了输出 YES 
	return >.<;
}
```


---

## 作者：TheMatrix (赞：3)


# 题解 CF902A 【Visiting a Friend】

### 思路1：

首先能想到的是对于n<=100,暴力解决问题不会超时， 那么我们就想到用桶排序，把a[x...y]的数标记一下，查看a[0...m]之间有没有断开的地方。

### ~~但是，这并不是最简单的方法~~
## 思路2：
再将原题读一遍，有一句话：
### 保证ai>=ai-1（2<=i<=n）。
这就告诉我们，这一列数是逐渐往后的。
### 所以，只需要判断前一个x和后一个y的大小，就可知前一段和后一段是否连续，我们用l...r表示最大可行范围，只需要判m在不在内就可以了。O（n）就OK了！

*注意：特判小猪的家和外界有无传送点。
————————————————————————————————————
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105];
int main()
{
    int n, m, x, y, l = 0, r;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) 
    {
    	cin >> x >> y;
    	if(i == 1 && x != 0) {cout << "NO" << endl;return 0;} 
    	if(i == 1) r = y;
    	else if(x <= r) r = max(r, y);
    }
    if(r >= m) cout << "YES" << endl;
    else cout << "NO" << endl;
	return 0;
}

```
## Accepted 
用时: 737ms / 内存: 4KB

第二篇题解， 还有许多不足之处， 我会继续努力的。
（第一篇CF875A）


---

## 作者：asasas (赞：2)

这题有一点像一道非常经典的题目：[P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)

为什么这么说呢？因为两题都用到了**桶**。

读入起点（也是左区间）和右区间。然后判断**起点**是否已经被打过标记了，打过了的话，就从左到右将这个区间里的所有点都标记一遍。最后判断从起点到终点的所有点是否被打过标记了。

### 注意  
小猪家的起点（也就是0这个点）一开始就要标记为0，否则没有区间里的点会被标记。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
bool a[100005];//桶
int main(){
	int n,m,ok=0;
	a[0]=1;
	cin >> n >> m;
	int qwq,qaq;
	for (register int i=1;i<=n;i++){
		cin >> qwq >> qaq;//读入
		if (a[qwq]!=0)
		for (register int j=qwq;j<=qaq;j++){
			a[j]=1;//将这个区间里的点标记
		}
	}
	for (register int i=0;i<=m;i++){
		if (a[i]==0){
			cout << "NO\n";//在1~m中有点没被标记，则输出NO
			return 0;
		}
	}
	cout << "YES\n";否则输出YES
}
```


---

## 作者：lwx20211103 (赞：1)

# CF902A Visiting a Friend

## 思路：

首先模拟一下，我们可以把这看成**寻找区间是否有重合**。在样例一可以模拟成![](https://cdn.luogu.com.cn/upload/image_hosting/5tvfjidd.png)

因为 $0-2-2-4-3-5$ 有重合部分，所以可以通过，只要找到最后一个 $a$ 和第一个 $b$ 中，$b$ 是否小于等于 $a$ 就可以了。

于是，代码一就出来了，如有雷同，纯属巧合。

```cpp
#include<bits//stdc++.h>
using namespace std;

int main()
{
	int n, m, a, b, r = 0;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin >> a >> b;
		if (a <= r)//如果a != 0，直接跳出循环，不用特判
		{
			if (b > r)
			{
				r = b;//也可以简写成r = max(r, b)
			}
		}
	}
	if (r < m)
	{
		cout << "NO";
	}
	else
	{
		cout << “YES";
	}
	return 0
}
```

当然，大多数人选择的是桶标记，就是把区间 $[a, b]$ 之内的数都标记，如果 $a$ 没有标记过，那么就不进行标记，一旦碰到没有标记的元素就直接返回 "NO" ，上代码

```cpp
#include<bits/stdc++.h>
using namespace std;

bool p[114514] = {1};//预处理

int main()
{
	int n, m, a, b;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> a >> b;
		if (p[a])
		{
			for (int j = a; j <= b; j++)
			{
				p[j] = true;
			}
		}
		
	}
	for (int i = 0; i <= m; i++)
	{
		if (!p[i])
		{
			cout << "NO"；
			return 0;
		}
	}
	cout << "YES";
	return 0;
}
```
## 其他

题解仅供参考，这是蒟蒻我的第一篇题解，感谢收看～

---

## 作者：_JF_ (赞：1)

# **CF902A Visiting a Friend**

这道题其实还是一个模拟 ~~（建议下降难度）~~

题目大意： 输入一个 $n$,表示 $n$ 组数据，在输入 $m$,表示该序列长度。 然后起始点在 $0$,接着输入 $n$ 次的 $x$ 和 $y$ 表示在 $x$ 和 $y$ 这个区间内的数值是可行的。最后问从 $0$ 开始，可不可以到达终点。

这个题目，仔细审读一下便可以发现：如果可以通过，那么 $x$ 和 $y$ 就必须覆盖到这一个区间内的每一个点上。所以我们只需要先对每一个 $x$ 和 $y$ 之间的值变成 true,注意要判断，就是当前的点是在被标记过的范围内，才可以进行更新。最后在寻找一遍，如果有一个点是 false 的话，输出 NO 并且 exit（0）即可。最后如果都是 true 的话，输出 YES 即可 

所以代码便是：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
bool a[N];
int main()
{
	int n,m;
	cin>>n>>m;
	memset(a,false,sizeof(a));// 初始化
	a[0]=true;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		if(a[x]) //在当前的点是可以在标记的范围内
		{
			for(int j=x;j<=y;j++)	
				a[j]=true;
		}
	}
	for(int i=0;i<=m;i++)
	{
		if(a[i]==false) //当前的点没有被更新过
		{
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"YES";
   return 0;
}
```

---

## 作者：ink_ngm (赞：1)

这道题可以使用 **桶** 来记录小猪是否可以通过。


每次读入传送门的 $\verb![x,y]!$ 将 $x$ 到 $y$ 的所有点位做标记。最后从起始点到目的地朋友家扫一遍每个点位。


如果其中有不能通过的点，则小猪不可前往便可以输出 $\verb!NO!$。否则便可输出 $\verb!YES!$ 。


```
#include<bits/stdc++.h>
using namespace std;
bool tong[114514];
int main(){
	int n,m;
	tong[0]=true;//初始小猪在的点位
	scanf ("%d%d",&n,&m);
	for (int i=1;i<=n;++i){
		int x,y;
		scanf ("%d%d",&x,&y);
		if (tong[x]) for (int j=x;j<=y;++j) tong[j]=true;
		/*注意！本处如果不判断初始点x是否可以通过的话，会导致如[1,2],[3,4]两个传送门原本不能通过的情况，误判为可以通过*/
	}
	for (int i=0;i<=m;++i)if (tong[i]!=true){
					printf ("NO\n");
					return 0;
				}
	printf ("YES\n");
	return 0;
} 
```



---

## 作者：cxy000 (赞：0)

解析：

其实看这道题的数据范围，我们就可以大概猜出是要用桶排序了。

先初始化起点为 $1$，然后如果输入的起点可以从已标记的点传送，那么我们也将此区间标记。

若枚举时有点不可以传送，那么我们直接输出 NO 就结束。

否则输出 YES 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1010];
int main(){
	int n,m;
	cin>>n>>m;
	int x,y;
	a[0]=1;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		if(a[x]>0){
			for(int j=x;j<=y;j++){
				a[j]++;
			}
		}
	}
	for(int i=0;i<=m;i++){
		if(a[i]==0){
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"YES"<<endl;
	return 0;
}
```


---

## 作者：Sternenlicht (赞：0)

思路：桶。

用桶的思想，$a_i$ 为 $1$ 表示第 $i$ 个点可以到达，$a_i$ 为 $0$ 表示第 $i$ 个点不能到达。

先将 $a_0$ 初始化为 $1$，读入时，若 $a_x$ 标记过，就将读入区间都打上标记。

遍历 $a_{0} \sim a_m$，若有一个点为 $0$，表示无法到达，输出 NO 并结束程序。遍历结束，说明每个点都可以到达，输出 YES。

```cpp
#include <bits/stdc++.h>
#define LL long long
inline LL read(){
	LL x=0,f=1;char c=getchar();
	for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
	for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
	return x*f;
}using namespace std;

const int N = 1e5+10;
int a[N],n,m;//a[i]=1表示第i个点可以到达 
int main(){
	n=read(),m=read();a[0]=1;
	for (int i=1;i<=n;i++){//边读入边处理 
		int x=read(),y=read();
		if (a[x])
			for (int j=x;j<=y;j++)
				a[j]=1;//标记区间 
	}
	for (int i=0;i<=m;i++)
		if (!a[i])//有一个点无法到达，输出NO并结束 
			{puts("NO");return 0;}
	puts("YES");//可以到达 
	return 0;
}
```

---

## 作者：_Harrisonwhl_ (赞：0)

## [传送门](https://www.luogu.com.cn/problem/CF902A)

介绍一种最适合萌新的做法：

由于传送门可以传送到 $[x,y]$,所以我们可以用一个筒，只要能到 $x$,就把 $[x,y]$ 标记为 $true$,最后查找 $0$ ~ $m$ 中有没有不能传送到的点，如果没有，则输出 YES,否则输出 NO。 
```cpp
#include <iostream>
using namespace std;
bool a[105];
int n,m,x,y;
int main()
{
    cin >> n >> m;
    a[0] = 1;
    for (int i = 1;i <= n;i++)
    {
        cin >> x >> y;
        if (a[x])//一定要判断，本人就在这个位置调了好久的错，因为上一次要是到x-1的话，如果不判断就会符合要求，实际是不符合的。
            for (int j = x;j <= y;j++)
                a[j] = 1;//标记
    }
    bool flag = 1;
    for (int i = 0;i <= m;i++)
        if (!a[i])
            flag = 0;
    if (flag)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
```


---

## 作者：KazamiHina (赞：0)

这个题嘛，大概就是从左区间到右区间打上标记，然后如果这到达不了，就不用打标记，最后在 $0$ ~ $m$ 的区间内判断一遍，这个点有没有打过标记，没打过就输出 $NO$

$code:$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int a[105];//标记数组
int n,m,x,y;

void R(int & x){//好像没什么用的读优
	x=0;char ch=getchar();
	while((ch<'0') || (ch>'9'))ch=getchar();
	while((ch>='0') && (ch<='9')){
		x=(x*10)+(ch-'0');
		ch=getchar();
	}
}

int main(){
	R(n);R(m);a[0]=1;//a[0]要先打标记，因为是从0开始走的
	for(int i=1;i<=n;i++){
		R(x);R(y);
		if(a[x]!=0){//如果这个点打过标记了，就在 x~y 区间内打标记
			for(int j=x;j<=y;j++)
				a[j]++;
		}
	}
	for(int i=0;i<=m;i++){//统计
		if(a[i]==0){//没出现过就输出NO
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}
```
$qwq$

---

## 作者：Mysterious_bird (赞：0)

此题的思路就是桶排序（也叫小学生排序）

我们只要把传送点-限制地点这其中的所有点都赋一遍值，然后再遍历一遍就行了

而这题需要输入两个相关联的量，所以我就想到了pair

pair

一个 std::pair 类型数组，可以存储两个相关联的量

定义：
```cpp
pair <int,int> a[1005]; //一个 std::pair 类型数组
```
## code：
```cpp
#include <bits/stdc++.h>
using namespace std;
pair <int,int> a[1005]; //一个 std::pair 类型数组
int v[105];     //存下每个坐标能不能达到
int main()
{
    int n,m;
    cin>>n>>m;
    v[0]=1;     //特判
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].first>>a[i].second;   //输入传送点和限制
        if(v[a[i].first]!=0)
        for(int j=a[i].first;j<=a[i].second;j++)
        {
            v[j]=1;     //赋值
        }
    }
    for(int i=0;i<=m;i++)
    {
        if(v[i]==0)
        {
            cout<<"NO"<<'\n';   //遍历一遍
            return 0;   //如果找到就return
        }
    }
    cout<<"YES"<<'\n';  //因为上面return过了，所以不用担心输出两个量
    return 0;
}
```
THE END.

---

## 作者：会打沙包的猫 (赞：0)

这道题就是桶的思想，遍历整个数组，把所有能达到的点打上标记，最后查看如果有点没有打标记即不能到达
很简单
### 一定要绑cf账号之后交，不然会**UKE**，切记！
~~~cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
struct att{
    int l,r;
};
att b[10000000];
int tong[10000],fasd[1000000];
int m,n,sd,d,sa,aaw;
int main()
{
    cin>>n>>m;
    tong[0]=1;
    for(int i=1;i<=n;i++)
      {
          cin>>b[i].l>>b[i].r;
          if(tong[b[i].l]!=0)
            for(int j=b[i].l;j<=b[i].r;j++)
              tong[j]=1;
      }
    for(int i=0;i<=m;i++)
      {
          if(tong[i]==0)
          {
              cout<<"no";
              return 0;
          }
      }
      cout<<"yes";
    return 0;
}
~~~

---

