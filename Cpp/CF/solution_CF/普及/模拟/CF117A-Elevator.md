# Elevator

## 题目描述

**题意简述**

一栋楼共 $m$ 层，当中有一个神奇的电梯，它不受人控制，只会在所有楼层之间来回移动（即从 $1$ 楼一直向上到 $m$ 楼之后又从 $m$ 楼一直向下到 $1$ 楼，反复地无休止地运动），每移动一层需要 $1$ 单位时间。

现有 $n$ 个人，第 $i$ 个人在 $t_i$ 时到达电梯门口，要从 $s_i$ 楼到 $t_i$ 楼。求每个人到达应到楼层的最小时间。

## 样例 #1

### 输入

```
7 4
2 4 3
1 2 0
2 2 0
1 2 1
4 3 5
1 2 2
4 2 0
```

### 输出

```
9
1
0
7
10
7
5
```

## 样例 #2

### 输入

```
5 5
1 5 4
1 3 1
1 3 4
3 1 5
4 2 5
```

### 输出

```
12
10
10
8
7
```

# 题解

## 作者：123456zmy (赞：1)

题意：  
有一个电梯，在 $1$ 到 $m$ 层之间来回移动，每运动一层需要 $1$ 单位时间，有 $n$ 个人，第 $i$ 个人要从  $s_i$ 到 $f_i$，在 $t_i$ 时到电梯门口，输出这些人什么时候能到。
___
~~推个公式再按照 s 与 f 的关系分类讨论一下就行了。~~

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,f,t,ans;
int main()
{
	scanf("%d%d",&n,&m);
	while(n--)
	{
		scanf("%d%d%d",&s,&f,&t);
		if(s>f)
		{
			ans=(t/(m-1<<1))*(m-1<<1);
			t%=m-1<<1;
			if(t>(m<<1)-s-1)ans+=m-1<<1;
			ans+=(m<<1)-f-1;
		}
		else if(s<f)
		{
			ans=(t/(m-1<<1))*(m-1<<1);
			t%=m-1<<1;
			if(t>=s)ans+=m-1<<1;
			ans+=f-1;
		}
		else ans=t; 
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：小杨小小杨 (赞：1)

## 题意
有一个直上直下的电梯，每一个人想要从 $x$ 楼到 $y$ 楼去，问最少要多少时间？
## 思路
这个电梯是直上直下的，每一次都必须从 $1$ 到 $n$ 再回到 $1$。    
特别的，在时间 $1$ 时，电梯已经到了 $2$ 层。   
设这栋楼有 $n$ 层，我们要从 $x$ 层到 $y$ 层去，在 $z$ 的时间等候。   
令 $m = n \times 2 - 2$，也就是电梯来回一趟所需的时间。   
##### 针对于 $x < y$ 的情况：
一共需要用 $\left\lfloor\dfrac{z}{m}\right\rfloor \times m$ 的时间跑完所有完整来回，再加上剩下的时间 $n \times 2 - y - 1$ 。此时有两种情况：
1. 当 $ z \mod m > n \times 2 - x - 1$ 时，加上 $m$。
2. 当 $ z \mod m \le n \times 2 - x - 1$ 时，不做处理。

##### 针对于 $x > y$ 的情况：
一共需要用 $\left\lfloor\dfrac{z}{m}\right\rfloor \times m$ 的时间跑完所有完整来回，再加上剩下的时间 $y - 1$ 。此时有两种情况：
1. 当 $ z \mod m \ge x$ 时，加上 $m$。
2. 当 $ z \mod m < x$ 时，不做处理。

##### 针对于 $x = y$ 的情况：
所用时间即为 $z$。
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,x,y,z;
int main(){
	scanf("%d%d",&T,&n);int m=n*2-2;
	while (T--){
		scanf("%d%d%d",&x,&y,&z);
		if (x>y) printf("%d\n",z/m*m+n*2-y-1+((z%m>n*2-x-1)?m:0));
		else if (x<y) printf("%d\n",z/m*m+y-1+((z%m>=x)?m:0));
		else printf("%d\n",z);
	}
	return 0;
}

```



---

## 作者：syf159 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF117A)

## 分析

对于本题，我们可以对以下几种情况进行分类讨论：

1. 目标在起点上方；
2. 目标在起点下方；
3. 目标即为起点。

对于第三种情况，我们直接输出起始时间即可。

对于前两种情况，需要再分两种情况：

1. 电梯需要折返才可以将人送到；
2. 电梯可以直接送到。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,m,s,f,t;
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1; i<=n; i++)
	{
		cin>>s>>f>>t;
		if(s==f)//第三种情况 
		{
			cout<<t<<"\n";
			continue;
		}
		int ans=0;
		if(s>f)//第一种情况 
		{
			ans=(t/(m-1<<1))*(m-1<<1);
			t%=m-1<<1;
			if(t>(m<<1)-s-1) ans+=m-1<<1;
			ans+=(m<<1)-f-1;
		}
		else//第二种情况 
		{
			ans=(t/(m-1<<1))*(m-1<<1);
			t%=m-1<<1;
			if(t>=s) ans+=m-1<<1;
			ans+=f-1;
		}
		cout<<ans<<"\n";
	}
	
	return 0;
}
```

---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF117A)
# 思路

每个要乘坐电梯的人有三种情况：

 - 所去楼层为上电梯前所在的楼层，即 $s=f$，此时答案为 $t$。
 - 所去楼层大于上电梯前所在的楼层，即 $s<f$，电梯要上行。
 - 所去楼层小于上电梯前所在的楼层，即 $s>f$，电梯要下行。

以这三种情况分类讨论，计算出电梯跑完所有来回的时间，再加上接人的时间即可。

# AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n,m;
	cin >>n>>m;
	while(n--)
	{
		int s,f,t;
		cin >>s>>f>>t;
		int ans=0;
		if(s==f) ans=t;
		if(s<f) //电梯需要上行 
		{
			ans+=(t-(t%(2*m-2)));
			t%=(2*m-2);
			if(t >= s) ans+=(2*m-2);
			ans+=(f-1);
		}
		if(s>f) //电梯需要下行
		{
			ans+=(t-(t%(2*m-2)));
			t%=(2*m-2);
			if(t > (m*2-s-1)) ans+=(2*m-2);
			ans+=(m*2-f-1);
		}
		cout <<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：Zhang_Shao_ (赞：0)

## 题意
一栋 $m$ 层高的房子里有一个电梯从 $1$ 层到 $m$ 层来回移动，问第 $i$ 个人 $t_i$ 秒时从 $s_i$ 层坐电梯到 $f_i$ 层的时间。
## 解法
对于每一个人，判断他来之后最早一次的电梯（分类讨论向上和向下），并求出到达终点的时间。

该方法时间复杂度是 $O(n)$，不会超时。
## 代码
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		int s,f,t;
		scanf("%d%d%d",&s,&f,&t);
		if(s==f){
			printf("%d\n",t);
			continue;
		}//不需要坐电梯
		int ans=t/(2*m-2);
		ans*=(2*m-2),t%=(2*m-2);//取2m-2的最小倍数和时间除以它的余数
		if(s>f){
			if(2*m-s-1>=t) printf("%d\n",ans+2*m-f-1);
			else printf("%d\n",ans+4*m-f-3);
			//t以后经过s后最早经过f的时刻
			continue;
		}//电梯下行
		if(s>t) printf("%d\n",ans+f-1);
		else printf("%d\n",ans+2*m+f-3);
		//电梯上行
	}
	return 0;
}//结束
``````

---

## 作者：jjy2023 (赞：0)

# CF117A Elevator
## 思路：
计算出电梯跑完所有来回的时间，再加上接人的时间即可。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,f,t,ans;//s为开始楼层，f为结束楼层，t为到达时间
int main()
{
   ios::sync_with_stdio(false);
   cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>s>>f>>t;
		if(s>f)
		{
			ans=(t/(m-1<<1))*(m-1<<1);
			t%=m-1<<1;
			if(t>(m<<1)-s-1)ans+=m-1<<1;
			ans+=(m<<1)-f-1;
		}
		else if(s<f)
		{
			ans=(t/(m-1<<1))*(m-1<<1);
			t%=m-1<<1;
			if(t>=s)ans+=m-1<<1;
			ans+=f-1;
		}
		else ans=t; 
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Tracy_Loght (赞：0)

# Elevator



### 题意简述

**更正原本题目错误点**：（出现了两个 $t_i$，一个时间，一个楼层，故错误）。

**正确如下：**

一个电梯在 $m$ 层内，从第一层出发，到 $m$ 层，又到一层，无限的反复这样的移动。移动一层要 $1$ 单位时间。

现有 $n$ 个人，第 $i$ 个人在 $t_i$ 时到达电梯门口，要从 $s_i$ 楼到 $f_i$ 楼。求每个人到达应到楼层的最小时间。

### 思路

仔细读题，发现电梯在每一层只会停留 $1$ 单位时间，所以当有 $m$ 层的时候，在 $0$，$2m-2$，$4m-4$，$8m-8$······这些时间会来一层接正在等待的人，而以一层接待的时间，将此分为一次循环。

所以，分为三个小版块解题：

- 排序

不难发现样例中的时间没有按照纯上升子序列，所以要排序一下（用 struct）

- 判断

 1. $s_i$ 小于 $f_i$，当然是接待时间加 $f_i$ 减 $s_i$。
 
 2. $s_i$ 大于 $f_i$，当然是楼层 $m$ 加接待时间加 $m$ 减 $f_i$。
 
 （为什么是 $m$？因为电梯要先到顶楼，再来到要求的 $f_i$）
 
 没明白也没啥，看图。
 ![](https://cdn.luogu.com.cn/upload/image_hosting/d3rd6tnk.png)
 
 这个电梯肯定是从 $1$ 到 $m$，再 $m$ 到 $6$ 接到它，最后 $6$ 到 $3$。
 
 - 输出
 
 将找到的时间减去它出现的时间，来求出它的等待值。
 
 完结撒花！
 


---

