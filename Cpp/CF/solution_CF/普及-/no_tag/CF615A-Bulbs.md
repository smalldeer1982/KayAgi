# Bulbs

## 题目描述

Vasya wants to turn on Christmas lights consisting of $ m $ bulbs. Initially, all bulbs are turned off. There are $ n $ buttons, each of them is connected to some set of bulbs. Vasya can press any of these buttons. When the button is pressed, it turns on all the bulbs it's connected to. Can Vasya light up all the bulbs?

If Vasya presses the button such that some bulbs connected to it are already turned on, they do not change their state, i.e. remain turned on.

## 说明/提示

In the first sample you can press each button once and turn on all the bulbs. In the 2 sample it is impossible to turn on the 3-rd lamp.

## 样例 #1

### 输入

```
3 4
2 1 4
3 1 3 1
1 2
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 3
1 1
1 2
1 1
```

### 输出

```
NO
```

# 题解

## 作者：Ryan_Yu (赞：4)

此题可以利用桶排的思想解决。

先定义一个 `bool` 型数组 $flag$ ，将其置为 $false$ 。

读入数据后，如果某灯泡的号码为出现了，就把 $flag_{j}$ 置为 $true$ 。

操作结束后，出现一个灯泡的号码为 $false$ ，就输出 $\texttt{“NO”}$ ，否则输出 $\texttt{“YES”}$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,j,i,j,sum;bool flag[105]={false};
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        cin>>sum;
        while(sum--)//由于是多行数据读入，sum减到0就会自动跳出
        {
            cin>>j;
            flag[j]=true;
        }
    }
    for(i=1;i<=m;i++)
    {
        if(flag[i]==false)
            {
                cout<<"NO"<<endl;
                return 0;
            }
    }
    cout<<"YES"<<endl;
    return 0;
}
```


---

## 作者：Terraria (赞：2)

一个字算法：

# 桶。

怎么用桶呢？就是把每个按钮连接的所有灯泡都打上标记。如果最后存在有灯泡没有打上标记则需要输出```NO```，否则就是```YES```。

详细见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool f[10009];
int n,m;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		int k;
		cin>>k;
		while(k--){
			int a;
			cin>>a;
			f[a]=true;
		}
	}
	for(int i=1;i<=m;i++){
		if(f[i]==false){
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"YES"<<endl;
}
```


---

## 作者：封禁用户 (赞：1)

题目传送>>[CF615A](https://www.luogu.com.cn/problem/CF615A)  
### 题意简述：  
- 给定 $n$ 个按钮和 $m$ 个灯，且已知各按钮对应几个灯和其灯的标号，求可否通过这些按钮控制所有灯。  
- $1\le n,m\le 100$。  
  
### 题目分析:  
解决此题的关键就是按钮与灯的一一对应关系，如果一灯至少有任一按钮对应，那么它就能被控制，所有说此题只需判断这 $m$ 个灯是否都有按钮对应。  
那么如何实现按钮与灯的对应呢？我们可以使用一个数组来表示各灯的被对应情况，先将其初始化为 $0$ 表示均无按钮对应，然后我们在读入各按钮对应的灯的标号时，在表示对应灯的数组上进行修改，最终再遍历一遍表示灯的数组，只要遇到一数组值依旧为 $0$ ，即无一按钮对应，那么这 $m$ 个灯就绝对不能全被控制，此时直接输出 "NO" 并结束程序即可，否则则 "YES" 有机会被输出。  
### Code:  
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int l[101]={0};   //开数组表示各灯的被对应情况，并初始化为0
int main()
{
	//freopen("light.in","r",stdin);   //输入文件名
	//freopen("light.out","w",stdout);   //输出文件名
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	int n,m,b,x;   //定义按钮的个数，灯的个数，各按钮对应灯的标号
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>b;
		for(int j=1;j<=b;j++)
		{
			cin>>x;
			l[x]++;   //在对应灯的数组上进行累加控制该灯的按钮个数
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(!l[i])   //如果该灯对应的按钮数为0，即无按钮对应，不能被控制
		{
			cout<<"NO";   
			return 0;   //直接输出NO并结束程序
		}
	}
	cout<<"YES";   //YES有机会被输出，即所以灯均可被控制
	//fclose(stdin);fclose(stdout);   关闭文件
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/pzqqx7s9.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：Chtholly_L (赞：0)

### 题意：

输入 $n$ 和 $m$，代表按钮的个数和灯的个数。接下来 $n$ 行，每行先输入一个数 $x_i$，再输入 $x_i$ 个数，代表编号为 $i$ 的按钮可以打开接下来的这些灯。问这些按钮是否可以控制所有的灯。

---

### 分析：

首先分析样例一。

```
3 4
2 1 4
3 1 3 1
1 2
```

当 $i=1$ 时，输入了 $1$ 和 $4$，那么编号为 $1$ 的按钮可以打开 $1$ 和 $4$ 两个灯。

当 $i=2$ 时，输入了 $1$、$3$ 和 $1$，那么编号为 $2$ 的点课可以打开 $1$ 和 $3$ 两个灯。

当 $i=3$ 时，输入了 $2$，那么编号为 $3$ 的点可以打开 $2$ 这台灯。

据此，我们得到了这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4oqitlij.png)

我们发现，所有的灯都至少有一个按钮可以控制，那么我们输出 `YES` 就可以了。

根据分析，我们可以开一个 `light` 数组来记录每个灯的控制情况，如果 `light[i]==1` 就代表这个灯可以被控制，反之，若 `light[i]==0` 就代表这个灯不可以被控制。

我们可以在输入时对相应的灯进行标记，最后再扫一遍所有的灯，若所有的的灯都可以被控制，就输出 `YES`，否则输出 `NO`。

---

### 代码：

```cpp
#include<iostream>
#include<cstdio>

using namespace std;

bool light[110];  //这里我们只需要 0 和 1，使用布尔型更省空间

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        for(int i=1;i<=x;i++){
            int y;
            cin>>y;
            light[y]=1;  //标记
        }
    }
    for(int i=1;i<=m;i++){  //扫一遍
        if(light[i]==0){
            cout<<"NO"<<endl;
            return 0;
        }
    }
    cout<<"YES"<<endl;
    return 0;
}
```

---

## 作者：Indulge_myself (赞：0)

# 题目大意：
首先吐槽一下这个题目的翻译，真的是什么都没有讲清楚。

大意：给定 $n$ 和 $m$， $n$ 是按钮，$m$ 是灯泡数量。灯泡从 1 到 $n$ 编号。接下来输入 $n$ 个数 $i$，表示第 $a_{i}$ 个按钮连接的灯泡数。接下来再输入 $i$ 个数，表示所连接的灯泡编号。

在操作开关时如果灯已设置完毕则不会改变其状态，求能不能关掉所有灯。

# 分析：
在这道题中，因为已经关掉的灯的状态不会被改变，所以我们只要找一找有没有不能被关掉的灯即可。

我们定义一个数组 $light_{n}$，设 $light_{i}$ 为第 $i$ 个灯的状态，并把所有的元素全部初始化为 0。

接着，在输入开关所控制的灯的编号 $y$ 时，就把 $light_{y}$ 设置为 1，表示这个灯可以被控制。

最后就好办了。我们只要循环遍历一下这个数组，如果有元素为 0 的就立即输出结果并结束程序。最后输出 $Yes$ 即可。 
```cpp
#include<bits/stdc++.h> 
using namespace std;
int light[100001]={0};
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		int y;
		for(int j=0;j<x;j++)
		{
		    cin>>y;
		    light[y]=1;
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(light[i]==0)
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```

无伤 AC 记录：

![](https://cdn.luogu.com.cn/upload/image_hosting/xg98s3nn.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

点个赞吧！

---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 个灯，一开始它们都是关着的。有 $m$ 个按钮，每个按钮可以开 $k$ 盏灯。求能否通过这 $m$ 个按钮使得所有灯全部都开着。

**数据范围：$1\leqslant n,m\leqslant100,k\leqslant n$。**
## Solution
只要所有的按钮按下去能使所有灯开那就可以使所有灯开，否则一定不能使所有灯开。因此，我们需要开个 $vis$ 数组，来存储每个按钮开的灯，最后看是否把所有的灯都开了。
## Code
```cpp
#include <cstdio>
using namespace std;

int n, m, k, x, vis[107];

int main() {
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; ++i) {
		scanf("%d", &k);
		for(int j = 1; j <= k; ++j)	{
			scanf("%d", &x);
			vis[x] = 1;
		}
	}
	for(int i = 1; i <= n; ++i)	if(!vis[i])	return printf("NO"), 0;
	return printf("YES"), 0;
}
```

---

## 作者：chenpengda (赞：0)

刚开始看到这道题目的时候以为按下一个按钮会切换所有连接的灯的开/关效果，比如一个开关连`1,2`一个连`1,3`就不可能。

但是后来发现这句话：`If Vasya presses the button such that some bulbs connected to it are already turned on, they do not change their state, i.e. remain turned on.`（如果Vasya按下按钮，使得与之相连的某些灯泡已打开，则它们**不会更改其状态**，即保持打开状态。）

也就是说，**只要一个灯泡被连接上，这个灯泡就一定可以被打开。**反正按下这个按钮不会关掉其他的灯，对开灯是没有妨碍的。

那不就简单了吗，只需要判定**一个灯泡有没有被连接上**（话说这样怎么关掉它们），一个bool数组就可以统计出来啦~

下面是代码。

```cpp
#include<bits/stdc++.h> 
using namespace std;
bool lian[105];//判断是否被连接 
int main()
{
	int n,m;
	cin>>n>>m;//RT。 
	for(int i=1;i<=n;i++)
	{
		//第i个按钮。
		int x;
		cin>>x;//连接灯泡的个数 
		int y;
		while(x--)
		{
			cin>>y;
			lian[y]=true; //这个灯泡被第i个开关连接上了 
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(!lian[i])//如果没有被连接(lian[i]==0也可以) 
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
} 
```

---

## 作者：chufuzhe (赞：0)

题意：有n个按钮和m个灯泡，每个按钮都可以连接到一些灯泡，问灯泡有没有都被连接。

思路：可以用一个bool数组（其实就是个桶）来记录每个的灯泡有没有被连接，下标为i的表示编号为i的灯泡有没有被连接，0表示没连接，1表示已连接。最后遍历这个桶，发现有没连接的就说明不能够通过这些按钮关闭所有的灯，输出NO并结束，如果遍历完仍没有发现没连接的就说明能够通过这些按钮关闭所有的灯，输出YES。

代码:
```cpp
#include<bits/stdc++.h> //头文件
using namespace std;
bool t[105]; //定义桶
int main()
{
	ios::sync_with_stdio(false); //输入输出优化流
	int n,m,l,a; //定义
	cin>>n>>m; //输入按钮的个数和灯泡的总数
	while(n--)
	{
		cin>>l; //输入按钮连接到的灯泡个数
		while(l--)
		{
			cin>>a; //输入按钮可以接到的灯泡
			t[a]=1; //标记编号为a的灯泡被连接了
		}
	}
	for(register int i=1;i<=m;i++) //遍历数组
	{
		if(!t[i]) //发现有没连接的
		{
			puts("NO"); //不能够通过这些按钮关闭所有的灯，输出
			return 0; //结束
		}
	}
	puts("YES"); //能够通过这些按钮关闭所有的灯，输出
	return 0;
}

```


---

## 作者：Cesare (赞：0)

题意大概就是给你n,m，n是按钮的个数，m是灯泡的总数，然后读入一个数，表示该按钮连接到的灯泡个数，然后输入灯泡个数。判断是否能够通过这些按钮关闭所有的灯。

思路也很简单，就是一个桶排，打完标记后遍历整个数组，如果有没被标记的，就输出NO，否则输出YES。

```cpp
#include <bits/stdc++.h>
#define re register
#define For(i,j,k) for(re int i=j;i<=k;i--)
using namespace std;
typedef long long ll;

ll n,m,vis[100010];

inline ll read() {
    ll x=0;bool f=0;char ch=getchar();
    for( ;!isdigit(ch); ch=getchar() )f^=( ch=='-' );
    for( ;isdigit(ch); ch=getchar() )x=( x<<3 )+( x<<1 )+( ch^48 );
    return f? -x: x;
}

int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    n=read(),m=read();
    for(re int i=1;i<=n;i++) {
        ll x=read();
        for(re int j=1;j<=x;j++)vis[read()]=1;
    }
    for(re int i=1;i<=m;i++)if( !vis[i] ) { puts("NO");return 0; }
    puts("YES");
    return 0;
}

```
温馨提示：请不要抄袭题解。

---

