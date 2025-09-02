# Inna and Alarm Clock

## 题目描述

Inna loves sleeping very much, so she needs $ n $ alarm clocks in total to wake up. Let's suppose that Inna's room is a $ 100×100 $ square with the lower left corner at point $ (0,0) $ and with the upper right corner at point $ (100,100) $ . Then the alarm clocks are points with integer coordinates in this square.

The morning has come. All $ n $ alarm clocks in Inna's room are ringing, so Inna wants to turn them off. For that Inna has come up with an amusing game:

- First Inna chooses a type of segments that she will use throughout the game. The segments can be either vertical or horizontal.
- Then Inna makes multiple moves. In a single move, Inna can paint a segment of any length on the plane, she chooses its type at the beginning of the game (either vertical or horizontal), then all alarm clocks that are on this segment switch off. The game ends when all the alarm clocks are switched off.

Inna is very sleepy, so she wants to get through the alarm clocks as soon as possible. Help her, find the minimum number of moves in the game that she needs to turn off all the alarm clocks!

## 说明/提示

In the first sample, Inna first chooses type "vertical segments", and then she makes segments with ends at : $ (0,0) $ , $ (0,2) $ ; and, for example, $ (1,0) $ , $ (1,1) $ . If she paints horizontal segments, she will need at least 3 segments.

In the third sample it is important to note that Inna doesn't have the right to change the type of the segments during the game. That's why she will need 3 horizontal or 3 vertical segments to end the game.

## 样例 #1

### 输入

```
4
0 0
0 1
0 2
1 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
0 0
0 1
1 0
1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
1 1
1 2
2 3
3 3
```

### 输出

```
3
```

# 题解

## 作者：幻之陨梦 (赞：5)

## 一道被恶评的CF题
### [$\color{blue}\text{AC证据}$](https://www.luogu.org/recordnew/show/20399726)
题目大概意思是输入n次每次输入一个x和一个y。每次只能删除一次，一行或一列，最后输出最小值。
### AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,s1,s2;//定义,s1,s2,是用来记录行和列的删除情况
bool f1[101],f2[101];//记录行和列的数组
int main(void)
{
    scanf("%d",&n);//输入
    for(int i=1;i<=n;i++)//循环n次
    {
        scanf("%d%d",&x,&y);//每次输入x和y
        if(!f1[x])//如果这个地方没被标记过，那么就标记并计数器s1加1
        {
        	f1[x]=1;
        	s1++;
        }
        if(!f2[y])//如果这个地方没被标记过，那么就标记并计数器s2加1
        {
        	f2[y]=1;
        	s2++;
        }
    }
    printf("%d",min(s1,s2));//输出两个之中最小值
}
```

---

## 作者：pyyyyyy (赞：5)

##### 首先题目的翻译是真的有问题，看了翻译后一阵懵逼
![](https://t1.picb.cc/uploads/2019/03/26/V0lKjj.jpg)
### [雷锋精神](https://baike.so.com/doc/1171488-1239174.html)告诉我一定要造福广大同胞，所以为了践行毛主席提倡的"为人民服务"，时刻帮助人民，雪中送炭。
# 题意：
![](https://t1.picb.cc/uploads/2019/03/26/V0CIrX.jpg)
当你看完题目后一定会了吧！
如果不是请看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,n,i,x_state[2019],y_state[2019],ans,sum_x,sum_y;//2019纯属好看 
int main() {
	cin>>n;
	for(i=1; i<=n; i++) {
		cin>>x>>y;
		if(!x_state[x]) sum_x++;//记录出现闹钟的行 
		if(!y_state[y]) sum_y++;//记录出现闹钟的列 
		x_state[x]=1,y_state[y]=1;
	}
	if(sum_x>sum_y)//找出最小的 
	{
		ans=sum_y;
	}
	else 
		ans=sum_x;
	cout<<ans;
	return 0;
}
```


---

## 作者：无意识躺枪人 (赞：4)

这道题的翻译简直不负责~~（还好我看了原题面）~~

输入点后只能选择$\color{red}\text{一次}$横线或竖线来消点

因此不用什么DP之类的高级玩意儿~~（那还黑题？）~~

边读点，边记录是否占了行（或列），最后选择最少的那个即可

具体看代码

```c
#include<bits/stdc++.h>
using namespace std;
int n,x,y,xcnt,ycnt;
bool xvis[105],yvis[105];
int main()
{
	cin>>n;
	while (n--)
	{
		cin>>x>>y;
		if (!xvis[x]) {xvis[x]=1;xcnt++;}
		if (!yvis[y]) {yvis[y]=1;ycnt++;} 
	}
	printf("%d",min(xcnt,ycnt));
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

[CF390A](https://www.luogu.com.cn/problem/CF390A)  
### 题意简述：  
一个 100 * 100 的矩阵上有 $n$ 个闹钟，可选择以横向或纵向的一种方式关掉一行上任意多的闹钟，问最少需要多少步。  
### 题目分析:  
因为只能选择以横向或纵向的一种方式关闹钟，所以我们可以分别计算以横向的方式关闹钟和以纵向的方式关闹钟所需要的步数，进行比较，其最小值即为最终结果。关于求每种方式所需步数，我们可以累加其有闹钟的列或行的个数，即只要该列或行出现了闹钟就加上。  
### Code:  
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int x[100]={0},y[100]={0};   //开数组存各列或行上有无闹钟
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("print.out","w",stdout);
	ios::sync_with_stdio(0);    //关同步流加速cin输入和cout输出
	int n;   //定义闹钟个数
	int xi,yi,xs=0,ys=0;   //定义每个闹钟所在列、行，分别以列、行方式关闹钟所需步数
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>xi>>yi;
		x[xi]++;   //列上占闹钟
		y[yi]++;   //行上占闹钟
	}
	for(int i=0;i<100;i++)
	{
		if(x[i])
		{
			xs++;   //列上有闹钟，累加有闹钟的列数
		}
		if(y[i])
		{
			ys++;   //行上有闹钟，累加有闹钟的行数
		}
	}
	cout<<min(xs,ys);   //比较最优解输出
	return 0;   //结束整个程序
}
```  
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/p3fi77rj.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：Eason_AC (赞：1)

## Content
平面内有 $n$ 个整点 $(x_i,y_i)$。每次可以去掉一行或一列的点，问最少去几次（按行去点或按列去点二者只能选择一种）。

**数据范围：$1\leqslant n\leqslant 10^5,0\leqslant x_i,y_i\leqslant 100$。**
## Solution
既然按行去点或按列去点二者不可得兼，那么我们考虑哪一个需要的次数更少。因此，统计横坐标和纵坐标的种数，就可以计算出按行去点和按列去点需要的次数，再在其中取最小值即可。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int n, x, y, row[107], line[107], ans1, ans2;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &x, &y);
		if(!row[x])		ans1 += (row[x] = 1);
		if(!line[y])	ans2 += (line[y] = 1);
	}
	printf("%d", min(ans1, ans2));
}
```

---

## 作者：清清老大 (赞：0)

## 题意

平面内有 $n$ 个点，每步能删去一行或一列上的点（每一次只能选一个方式），问最少要几步。

## 思路

边读边记录，如果一个点所在的行上没有其他点，要删的行数就加一，如果一个点所在的列上没有其他点，要删的列数就加一，最后统计哪种方式步骤少。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,x,y,xs = 0,ys = 0;
    bool xm[1212121] = {0},ym[2121212] = {0};
    cin >> n;
    while(n --)
    {
        cin >> x >> y;
        if(!xm[x])
        {
            xm[x] = 1;
            xs ++;
        }
        if(!ym[y])
        {
            ym[y] = 1;
            ys ++;
        }
    }
    cout << min(xs,ys);
}
```


---

## 作者：Su_Zipei (赞：0)

翻译说的很清楚，按照行去掉点和按照列去掉点只能选择一个，既然不能兼得，那么肯定要贪心的按照最少的删，所以把两种方式取一个最小值即可。
```cpp
#include<cstdio>
const int N=110;
int visx[N],visy[N];
int main(){
	int n;
	scanf("%d",&n);
	int cnt1=0,cnt2=0;
	for(int i=1;i<=n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		cnt1+=!visx[x]++;
		cnt2+=!visy[y]++;
	}
	printf("%d\n",cnt1>cnt2?cnt2:cnt1);
	return 0;
}

```

---

## 作者：CobaltChloride (赞：0)

```
#include<bits/stdc++.h>
using namespace std;
int x,y,n,i,used_x[101],used_y[101],ans,totx,toty;//x,y代表坐标,used_x,used_y代表该行/列是否有闹钟,totx,toty统计有闹钟的行/列个数,
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>x>>y;
		if(!used_x[x]) totx++;//该行还没有
		if(!used_y[y]) toty++;//该列还没有
		used_x[x]=1,used_y[y]=1;//标记
	}
	ans=totx>toty?toty:totx;//取较小值
	cout<<ans;
	return 0;
}
```

---

