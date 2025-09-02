# Robot's Task

## 题目描述

Robot Doc is located in the hall, with $ n $ computers stand in a line, numbered from left to right from $ 1 $ to $ n $ . Each computer contains exactly one piece of information, each of which Doc wants to get eventually. The computers are equipped with a security system, so to crack the $ i $ -th of them, the robot needs to collect at least $ a_{i} $ any pieces of information from the other computers. Doc can hack the computer only if he is right next to it.

The robot is assembled using modern technologies and can move along the line of computers in either of the two possible directions, but the change of direction requires a large amount of resources from Doc. Tell the minimum number of changes of direction, which the robot will have to make to collect all $ n $ parts of information if initially it is next to computer with number $ 1 $ .

It is guaranteed that there exists at least one sequence of the robot's actions, which leads to the collection of all information. Initially Doc doesn't have any pieces of information.

## 说明/提示

In the first sample you can assemble all the pieces of information in the optimal manner by assembling first the piece of information in the first computer, then in the third one, then change direction and move to the second one, and then, having 2 pieces of information, collect the last piece.

In the second sample to collect all the pieces of information in the optimal manner, Doc can go to the fourth computer and get the piece of information, then go to the fifth computer with one piece and get another one, then go to the second computer in the same manner, then to the third one and finally, to the first one. Changes of direction will take place before moving from the fifth to the second computer, then from the second to the third computer, then from the third to the first computer.

In the third sample the optimal order of collecting parts from computers can look like that: 1->3->4->6->2->5->7.

## 样例 #1

### 输入

```
3
0 2 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
4 2 3 0 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
7
0 3 1 0 5 2 6
```

### 输出

```
2
```

# 题解

## 作者：Ptilopsis_w (赞：4)

# 1.题意
某黑客的robot要黑掉 $n$ 台电脑，第 $i$ 台电脑需要事先黑掉 $a_i$ 台电脑才能黑，但是机器人回头需要耗费很多资源，求机器人最少需要回头多少次

# 2.思路
贪心，每回都走到头，把能黑的全黑了，这样每次回头能黑的电脑就更多，回头的次数就更少，然后模拟即可，剩下的注释都在代码里

# 3.代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[1005];
bool vis[1005];//记录电脑是否被黑过

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	int tot = 0, ans = 0, i = 1, way = 1;//黑的电脑数，回头次数，当前位置，方向
	while(tot < n)
	{
		if(i < 1 or i > n)//走出去了，说明需要回头
		{
			way *= -1;//回头
			i += way;//因为本来就走出去了所以走一步再回来
			ans++;//记录回头的次数
		}
		if(!vis[i] and a[i] <= tot)//符合条件且没被黑过
		{
			vis[i] = true;//黑掉
			tot++;//累计
		}
		i += way;//向当前方向走一步
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Edmundino (赞：3)

# 题意

给你 $n$ 个电脑，当你要打开第 $i$ 个电脑，要先打开 $a_i$ 个电脑，小明要按 $1-n$ ，$n-1$ 的顺序打开电脑，问小明要转弯几次。

# 分析

由于 $n$ 最大才 $1000$，我们可以选择模拟。

以一个回合（$1-n-1$）为一个循环，

开一个变量 $s$ 来记录已经打开的电脑数，

$bo_i$ 表示第 $i$ 个电脑是否打开，$0$ 表示未打开，$1$ 则相反。

当 $bo_i=0 $ 并且 $a_i\le s$，那我们就可以把他打开。

就这样一直模拟下去，直到 $s=n$ 停止。

# 代码

**核心部分**

```cpp
	int o=0;
	while(o==0){
		for(int i=1;i<=n;i++){
			if(a[i]<=s&&bo[i]==0){
				bo[i]=1;s++;
			}
		}
	    
		if(s==n)break;
		o=0;zs++;//zs表示转弯次数
		for(int i=n;i>=1;i--){
			if(a[i]<=s&&bo[i]==0){
				bo[i]=1;s++;
			}
		}
		if(s==n)break;
		zs++;
	}
```


---

## 作者：Hanghang (赞：3)

# 一道水模拟题

## [AC记录](https://www.luogu.com.cn/record/44838504)

模拟每转一次弯

话不多说，直接上代码（有详细注释）

```cpp

#include<bits/stdc++.h>
using namespace std;
//万能头大法号

int n,a[1003],s,k;
//n表示电脑数量，a数组每台电脑分别需要多少信息
//s表示当前已经黑的电脑数量，k表示转了多少次弯
bool v[1003];
//v数组表示当前这个电脑是否被黑过，0表示是，1表示否
int main()
{
	cin>>n;
   //读入n
	for(int i=1;i<=n;i++)cin>>a[i];
   //读入数组a
	while(s<n)
   //当前是否黑了所有电脑，没有的话就进入
	{
		if(k%2==0)
     //看是从前往后还是从后往前
		{
			for(int i=1;i<=n;i++)
        //循环
				if(a[i]<=s&&v[i]==0)s++,v[i]=1;
           //判断当前电脑是否可以黑
			if(s==n)
         //判断是否黑完了所有电脑
			{
				cout<<k<<endl;return 0;
           //直接输出走人
			}
		}
		else
		{
			for(int i=n;i>0;i--)
        //循环
			    if(a[i]<=s&&v[i]==0)s++,v[i]=1;
            //判断当前电脑是否可以黑
			if(s>=n)
        //判断是否黑完了所有电脑
			{
				cout<<k<<endl;return 0;
           //直接输出走人
			}
		}
		k++;
     //转一次弯
	}
}

```
第一次写题解，求通过（万分感谢）

---

## 作者：谷民 (赞：2)

n台电脑，每台电脑有一条信息，一黑客每次黑掉一台电脑需要ai条信息，这个黑客会沿着电脑排成的序列来回走直至黑掉所有电脑，问这个黑客最少需要转弯几次

Input 

第一行为一整数n表示电脑数量，第二行n个整数表示黑掉这n台电脑分别需要多少条信息 

Output 

输出这名黑客黑掉所有电脑最少需要转弯几次 

每次贪心的选取最小的ai，具体操作就是对这个数组来回扫，令pre为当前黑客获得的信息，初始化pre=0，ans表示转弯次数，ans为奇则从后往前扫，ans为偶则从前往后扫，每次只要扫到ai<=pre就标记i表示黑掉第i台电脑，然后pre++表示获得一条信息，当pre=n时退出循环输出ans即可 
```cpp
#include<stdio.h>
#include<string.h>
int n,a[1001],vis[1001];
int main()
{
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        int pre=0,ans=0;
        memset(vis,0,sizeof(vis));
        while(1)
        {
            if(ans%2==0)
            {
                for(int i=1;i<=n;i++)
                    if(!vis[i]&&a[i]<=pre)
                    {
                        vis[i]=1;
                        pre++;
                    }
            }
            else
            {
                for(int i=n;i>=1;i--)
                    if(!vis[i]&&a[i]<=pre)
                    {
                        vis[i]=1;
                        pre++;
                    }
            }
            if(pre==n)break;
            ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：1)

~~要是我真有这位大佬那么厉害就好了~~

这道题观察到 $n$ 较小，故直接模拟即可。

所遇到一个能黑进去的就黑，然后 所得到的信息 $+1$ 。

最后只要有 $n$ 条信息就表明了所有的都黑了，停止模拟。

## _Code_

```cpp
#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
const int MAXN=1e3+5;
int n;
int a[MAXN];
int k=0;
int ans=-1;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	while(k<n){
		for(int i=1;i<=n;i++)
			if(a[i]<=k){
				k++;
				a[i]=1e9;
			}
		ans++;
		if(k==n)
			break;
		for(int i=n;i>=1;i--)
			if(a[i]<=k){
				k++;
				a[i]=1e9;
			}
		ans++;
	}
	cout<<ans;
}
```



---

## 作者：Meteorshower_Y (赞：1)

~~21中考以在即，发篇题解涨Rp。~~   

言归正传~  

题目传送门：[CF583B](https://www.luogu.com.cn/problem/CF583B)

## 题意解析

有 $n$ 台电脑排成一排，每个电脑里面有一条信息，黑掉它即可获取这条信息， 某黑客黑掉第 $i$ 个电脑需要   $a_i$ 个信息，这位黑客每次会从 $1$ 走到 $n$ 再从 $n$ 走到 $1$ ，问他最少需要转几次弯（掉几次头）可以黑掉所以电脑。

## 思路解析

1. 变量：  
> $cnt$ 为当前黑客掌握的信息数  
 $ans$ 为转弯次数

2. 内容：  
>一开始从 $1$ 到 $n$ ，黑掉可以黑掉的电脑， $a_i$ 标记为 $-1$ ，更新信息数 `cnt+=1` 。  
如果还有没有黑掉的电脑，转弯，次数 `ans+=1` ，从 $n$ 到 $1$ 继续重复上述操作。  
继续判断有无剩余电脑……  
有则转弯+操作，无则退出+输出

## Code

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[1010],ans,n,cnt;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i+=1)
		scanf("%d",&a[i]);
	while(1)
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i]==-1) continue;
			else if(cnt>=a[i]) 
            {
           		cnt+=1;
            	a[i]=-1;
           	}
		}
		if(cnt==n) break;
		else ans+=1;
		for(int i=n;i>=1;i--)
		{
			if(a[i]==-1) continue;
			else if(cnt>=a[i]) 
            {
            	cnt+=1;
            	a[i]=-1;
            }
		}
		if(cnt==n) break;
		else ans+=1;
	}
	printf("%d",ans);
	return 0;
}
```

### 结语

有误希望提醒更正，感谢对本S的支持


---

