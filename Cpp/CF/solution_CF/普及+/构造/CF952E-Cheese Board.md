# Cheese Board

## 题目描述

Not to be confused with [chessboard](https://en.wikipedia.org/wiki/Chessboard).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF952E/d088bd192ec24adc1aa0fd2afc4c2fb2b7ee4531.png)

## 样例 #1

### 输入

```
9
brie soft
camembert soft
feta soft
goat soft
muenster soft
asiago hard
cheddar hard
gouda hard
swiss hard
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6
parmesan hard
emmental hard
edam hard
colby hard
gruyere hard
asiago hard
```

### 输出

```
4
```

# 题解

## 作者：郑朝曦zzx (赞：9)

# 一 解题思路
## 第一步：
统计出软和硬两种奶酪的个数，以及哪种奶酪更多，有多少个。

```cpp
for (int i = 1; i <= n; ++i)
{
	cin >> s1 >> s2;
	if (s2 == "soft") ++s;
	else ++h;
}
//s 记录 soft 个数，h 记录 hard 个数， mx 记录更多地那种奶酪的个数
if (s > h) mx = s;
else mx = h;
```

## 第二步：
枚举边长判断是否有解。

什么样的情况有解？

**条件一** ：棋盘大小大于等于奶酪总数。 **（这一点很容易被忽视）**

**条件二** ：更多的那种奶酪能放的下，而且没有相邻。

**如何判断是否有相邻：**

一个变长为偶数的正方形，有一半的格子不相邻。

一个边长为奇数的正方形，有（总面积 + 1）一半的格子不相邻。
# 二 参考代码

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, s, h, mx;
string s1, s2;
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		cin >> s1 >> s2;
		if (s2 == "soft") ++s;
		else ++h;
	}
	if (s > h) mx = s;
	else mx = h;
	for (int i = 1; i <= n; ++i)
	{
		int k = (i * i + 1) >> 1;
		if (i * i >= n && k >= mx)
		{
			printf("%d\n", i);
			return 0;
		}
	}
}
```



---

## 作者：封禁用户 (赞：5)

## CF952E Cheese Board
[原题链接](https://www.luogu.com.cn/problem/CF952E)

## 分析
看到其他题解中有朋友直接枚举棋盘大小，但并未给出证明，下面简单解释一下：为什么棋盘面积的二分之一大于等于“软”与“硬”中较大值时，两种奶酪一定能够交替放置。

假设有一个 $4*4$ 的棋盘，并有“软”个数大于“硬”个数。那么单个“软”本质上只有三种不同的放置方式，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/jaeo99go.png)

我们发现，无论“软”如何放置，它的旁边总有2~4个可以放置“硬”的位置，如果“软”的个数还小于等于棋盘面积的一半，那么比它少的“硬”一定能够放入棋盘中。

## 思路
只需要对两个条件进行判断：
1. 棋盘面积的二分之一是否大于等于“软”与“硬”中较大值。
2. 棋盘面积是否大于等于奶酪总数。

将棋盘大小不断向上枚举，满足两个条件时，即为所求棋盘的面积。

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cmath>
using namespace std;
int main(){
	int n;cin>>n;
	string name,a[110];
	int x=0,y=0,k;
	for(int i=1;i<=n;i++){ //读入，用x,y进行计数 
		cin>>name>>a[i];
		if(a[i]=="soft")x++;
		if(a[i]=="hard")y++;
	}
	k=max(x,y); //得出较大值k 
    for(int j=1;;j++){
    	int size=pow(j,2); //当前棋盘面积 
    	if((size+1)/2>=k && size>=x+y){ //判断是否符合上文条件 
    		cout<<j;
		return 0; //end 
		}
    }
}

```



---

## 作者：Tan_Wei_Ye (赞：4)

# 首先看题 
找出方形“棋盘”的最小尺寸，在该棋盘上可以以这样的方式布置给定的奶酪，使得软奶酪和硬奶酪交替，并且相同类型的奶酪永远不会占据相邻的方块。

稍加思考后，可以发现**最后一句话**是~~废话~~。

那么不难想到，**从小到大**枚举棋盘大小，看看是否合法就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,soft,hard;
string s,k;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>s>>k;
		if(k=="soft") soft++;
		else hard++;
	}
	int x=max(soft,hard),i;
	for(i=1;(i*i+1)/2<x || i*i<soft+hard;i++) ;
	cout<<i<<endl;
	return 0;
}
```
~~好像目前题解里最短的代码~~

---

## 作者：Peter0701 (赞：2)

这是一道 $CodeForces$ $2018$ 年愚人节比赛的 $E$ 题。

题意是给出 $n$ 块奶酪的名字（确保每块名字不同）和硬度（分为软和硬两种），请将其放入一张特制的国际象棋棋盘内，使得软硬奶酪分开（行和列上都不允许有连续的相同硬度的奶酪）。求出棋盘最小的边长（每格算作 $1$ 个单位长度）。

因为保证每块奶酪名字不同，最后排入棋盘时也与奶酪名无关，所以读入后可以直接舍弃。软硬度的大小才是关键。又因为排入棋盘时与奶酪顺序无关，所以只需要记录总的软奶酪数和硬奶酪数。

先分析 $x$ 层的棋盘可以放多少软奶酪和硬奶酪。若 $x$ 为偶数，则两种奶酪均可以放 $\frac{x \times x}{2}$ 块；若 $x$ 为奇数，则一种奶酪可以放 $\frac{x \times x}{2}$ 块，另一种奶酪可以放 $\frac{x \times x}{2}+1$ 块。

由此可得， $n \leqslant 100$ 时，棋盘边长最多为 $\lceil \sqrt{100 \times 2} \rceil =15$ ，因此我们可以枚举奶酪的边长。

边长为 $1$ 时，一定只能放下一块奶酪，故 $n=1$ 时直接特判即可。剩余的 $n$ 值直接从边长为 $2$ 开始枚举即可。枚举到 $x$ 层时，若满足了记录的软奶酪数和硬奶酪数条件，就直接输出答案即可。否则枚举到 $15$ 层时停止，输出答案即可。

如有疑问，评论区见！

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int ret=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		ret=(ret<<1)+(ret<<3)+ch-'0';
		ch=getchar();
	}
	return ret*f;
}
int n,s,h,ans;
char str[15];
inline int geta(int k)
{
	if(k==15)
		return k;
	int tmp1=k*k/2;
	if(k&1)
	{
		int tmp2=k*k-tmp1;
		if((s<=tmp1&&h<=tmp2)||(s<=tmp2&&h<=tmp1))
		{
			if(s+h<=k*k)
				return k;
		}
		return geta(k+1);
	}
	else
	{
		tmp1=k*k/2;
		if(s<=tmp1&&h<=tmp1)
		{
			if(s+h<=k*k)
				return k;
		}
		return geta(k+1);
	}
}
int main()
{
	n=read();
	if(n==1)
	{
		puts("1");
		return 0;
	}
	for(register int i=1;i<=n;i++)
	{
		cin>>str;
		cin>>str;
		if(str[0]=='s'&&str[1]=='o'&&str[2]=='f'&&str[3]=='t')
			s++;
		else
			h++;
	}
	ans=geta(2);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：WCG2025 (赞：2)

为CF~~水题~~写题解



------------
首先，这道题是一道愚人节题目，它的大意是给你N个chess，有软硬两种区别，你要把这N个chess放在一个chessboard上，同种的不能相邻（即上下左右不能是同一种），问chessboard最小为多少

这道题乍一看还是比较难，实际上当你发现你只要将这个chessboard的值/2大于芝士的最大值就好了（只要连数量大的那种芝士都能放下，那么数量小的肯定放的下）
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    char ch=getchar();
    int x=0,f=1;
    while(ch<'0'||ch>'9')
    {
       if(ch=='-') f=-1;
       ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
       x=x*10+ch-'0';
       ch=getchar();
    }
    return x*f;
}
int n;
int anss,ansh;//s,h分别是soft与hard芝士的数量
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        string s1,s2;
        cin>>s1>>s2;//注意同种芝士是指后面的软硬程度，与芝士名称无关
        if(s2=="hard")
        ansh++;
        else
        anss++;
    }
    int sum=0;
    while((sum*sum/2)<min(ansh,anss)||(sum*sum+1)/2<max(anss,ansh))//如果chessboard的面积连最小的和最大的都不能满足，那么它必须变大
    sum++;
    printf("%d",sum);
    return 0;
}

```
CF~~毒瘤~~

---

## 作者：ivyjiao (赞：1)

一道大水紫。思路：

**第一步：统计出软和硬哪种奶酪更多，有多少个。**

这一步字符串 $x$ 是完全没用的。

模拟即可。

```cpp
for(int i=1;i<=n;i++){
    cin>>x>>t;
    if(t=="soft"){
        s++;
    }
    else{
        h++;
    }
}
maxn=int(max(s,h));
```

**第二步：从 $1$ 枚举边长，判断是否有解。如果有解，输出并退出枚举。**

第一个条件：奶酪总数不小于棋盘大小。

这个好办，判断 $i^2$ 是否不小于 $n$ 即可。

第二个条件：更多的那种奶酪能放下且没有相邻。

让更多的那种奶酪数量不大于棋盘大小的一半，即 $(i^2+1)/2$ 要不小于 $maxn$。

注意这两个条件都要满足才能输出。

```cpp
for(int i=1;i<=n;i++){
    int k=(i*i+1)/2;
    if(i*i>=n&&k>=maxn){
        cout<<i<<endl;
        return 0;//注意这里要return 0否则会输出很多个i
    }
}
```

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,h,maxn;
string x,t;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x>>t;
		if(t=="soft"){
            	s++;
        }
		else{
            	h++;
        }
	}
    maxn=int(max(s,h));
	for(int i=1;i<=n;i++){
		int k=(i*i+1)/2;
		if(i*i>=n&&k>=maxn){
			cout<<i<<endl;
			return 0;
		}
	}
}

```


---

