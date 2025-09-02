# ARMY - Army Strength

## 题目描述

The next MechaGodzilla invasion is on its way to Earth. And once again, Earth will be the battleground for an epic war.

MechaGodzilla's army consists of many nasty alien monsters, such as Space Godzilla, King Gidorah, and MechaGodzilla herself.

To stop them and defend Earth, Godzilla and her friends are preparing for the battle.

## 样例 #1

### 输入

```
2

1 1
1
1

3 2
1 3 2
5 5```

### 输出

```
Godzilla
MechaGodzilla```

# 题解

## 作者：ahawzlc (赞：6)

这是蒟蒻的第一篇题解，下面记录一下我做道题的真实思路过程。

首先看题，两个军队互怼，一个人一个人的打，战斗力高的获胜。

那我们可以考虑一下直接模拟，开两个数组，或者 $vector$ 也行，然后输入每个人的战斗值，开两个指针，哪一方军队实力较差，就让它的指针向后一个位置。

我们又看到 $1.46GB$ 的限制，那没问题，可劲造。

```cpp
int t1=1,t2=1;
while(t1<=n&&t2<=m) {
	if(a[t1]>=b[t2]) t2++;
	else t1++;
}
if(t1>n) puts("MechaGodzilla");
else puts("Godzilla");
```

差不多就是这个样子

这道题水，所以这就行了。

但我们这种好学生怎么能不继续探索呢？

我们可以用一个大根堆，每次用两个军队中较NB的两个士兵互怼，这样理论上可以有一点优化。

```cpp
while(a.size()&&b.size()) {
	int t1=a.top();
	int t2=b.top();
	if(t1<t2)a.pop();
	else b.pop();
}
if(a.size()) {
	while(a.size()) a.pop();
	puts("Godzilla");
} else {
	while(b.size()) b.pop();
	puts("MechaGodzilla");
}

```
差不多就是这个样子。

欸，等等。

我们在想到堆后，可以直接想了：我们可以直接取每支军队中最NB的两个人。让他们俩进行巅峰对决。谁赢了就可以称霸世界 ~~（滑稽）~~ 

为什么呢？因为在这场战争中，NB的那个人永远不会挂掉。所以只要拥有强者的一方，就能赢得胜利。

这样就比前两者都NB多了。

```cpp
for(int i=1;i<=n;i++) {
	cin>>va;
	f1=max(va,f1);
}
for(int i=1;i<=m;i++) {
	cin>>va;
	f2=max(va,f2);
}
if(f1>=f2) puts("Godzilla");
else puts("MechaGodzilla");

```
好了，这就结束了。

 _注明：本题解为防抄，只采用部分代码。_ 

---

## 作者：封禁用户 (赞：4)

这是一道大模拟。

嗯，有点像打擂台。

其实很好理解，就是胜者存，败者亡，更厉害的才能继续战斗。

那么就用两个数组来模拟这一过程，$a_i$ 就代表Godzilla军队的第$i$ 个士兵，$b_i$ 就代表MechaGodzilla军队的第$i$ 个士兵。

然后定义$x$ 和$y$ 这两个变量。$x$ 代表Godzilla军队现在战斗的士兵，$y$ 代表MechaGodzilla军队现在战斗的士兵。

根据战斗规则，分三种情况讨论：

1. Godzilla军队的第$x$ 士兵赢了。

$y \gets y+1$，其含义就是士兵$y$ 不能战斗了。

2. MechaGodzilla军队的第$y$ 士兵赢了。

$x \gets x+1$，其含义就是士兵$x$ 不能战斗了。

3. 两个军队的士兵战斗力相等。

根据规则，胜利属于Godzilla军队，所以$y \gets y+1$ 。

当有一个军队的所有士兵都不能战斗了（即$x>n$ 或$y>m$ ），则另一个军队获胜，输出结果。

思路讲完了，代码应该很好实现吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000001],b[1000001],t,x,y;
int main() {
    scanf("%d",&t);
    while(t--) {
        scanf("%d%d",&n,&m);
        for(int i=1; i<=n; ++i) scanf("%d",&a[i]);
        for(int i=1; i<=m; ++i) scanf("%d",&b[i]);
        x=1;
        y=1;
        while(1) {
            if(y>m) {
                printf("Godzilla\n");
                break;
            }
            if(x>n) {
                printf("MechaGodzilla\n");
                break;
            }
            if(a[x]==b[y]) y++;
            else if(a[x]<b[y]) x++;
            else if(a[x]>b[y]) y++;
        }
    }
    return 0;
}
```
>PS：这题有点坑，数据范围没写，导致我第一次因为数组开小而RE。建议在题目的最后加一句$1\leq N,M \leq 10^6$。

---

## 作者：大菜鸡Tey_rl (赞：2)

既然战斗力最强的士兵永远不会被打败，哪只军队拥有最强的
士兵，就可以无敌了。但要注意两支军队都有战斗力最强的士兵的情况，这时根据规则，杀死 MechaGodzilla 军队中的士兵，Godzilla 获胜。

附上代码：
```cpp
#include<cstdio>//不解释的头文件
int m,n,i,x,maxa,maxb;
int t;
int main()
{
	scanf("%d",&t);//测试数据t组
	for(int o=1;o<=t;o++)
	{
		maxa=0;//不要忘记初始化！
		maxb=0;//不要忘记初始化！
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++)
		{
			scanf("%d",&x);
			if(x>maxa)
			{
				maxa=x;//记录Godzilla军队的最强士兵
			}
		}
		for(i=1;i<=m;i++)
		{
			scanf("%d",&x);
			if(x>maxb)
			{
				maxb=x;//记录MechaGodzilla军队的最强士兵
			}
		}
		if(maxa>=maxb)//比较一下
		{
			printf("Godzilla\n");
		}
		else
		{
			printf("MechaGodzilla\n");
		}
	}
	return 0;
}
```

---

## 作者：Bla_Bla (赞：1)

**嗯...本蒟蒻的第一篇题解。**

众人：你不是蒟蒻吗？你怎么会AC绿题？

我：这题很水。


------------
首先，1.64GB的内存限制，出题人肯定是想让我们干件大事！正解应该是让我们模拟出来。~~但是！我不会~~（超小声

但是在脑中想一下：两支军队将派出各自战斗力最低的一个士兵迎战，战斗力低的士兵会被杀死。一直杀到后面，会剩下两支军队最强的人战斗。那么直接找出来让他两打一场不就好了？~~还可以使伤亡降到最小~~

这样，思路就出来了。

### 代码：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int i,j,n,m,a,x[10000],ma=0,mb=0,t;
	cin>>t;
	for(i=1;i<=t;i++)//t组数据,直接开个for 
	{
		cin>>n>>m;
		for(j=1;j<=n;j++)//Godzilla的人 
		{
			cin>>a;
			if(a>ma)//读的时候比较,留下最能打的
			ma=a;
		}
		for(j=1;j<=m;j++)//MechaGodzilla的人
		{
			cin>>a;//废物利用 变废为宝 
			if(a>mb)
			mb=a;//同上 
		}
		if(ma>=mb)//仔细审题,如果两队一样是 Godzilla赢 
		x[i]=1;
		else
		x[i]=0;//记录结果
		ma=0;
		mb=0;//记得清零 
	}
	for(i=1;i<=t;i++)
	{
		if(x[i]==1)
		cout<<"Godzilla"<<endl;
		else
		cout<<"MechaGodzilla"<<endl;
	}//输出 
	return 0;//华丽水过 
}
```
然后，我们就~~水过~~AC过了一道绿题。

---

## 作者：tobie (赞：1)

这道题如果使用模拟的话就会炸（亲测TLE），所以我们必须换一个更快的算法。

注意到每一次都是战斗力低的士兵死亡，所以说PK到最后剩下的士兵一定是战斗力最高的士兵。

所以我们只要找到两军队战斗力最高的士兵进行PK即可。

代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int t,a,b,c,i,ans1=-1,ans2=-1;
int main()
{
    scanf("%d",&t);//t组数据
    while(t--)
    {
        ans1=-1,ans2=-1;//初始化
        scanf("%d%d",&a,&b);
        for(i=1;i<=a;i++)//找出Godzilla军队中战斗力最大的士兵。
        {
            scanf("%d",&c);
            ans1=max(ans1,c);
        }
        for(i=1;i<=b;i++)//找出MechaGodzilla军队中战斗力最大的士兵。
        {
            scanf("%d",&c);
            ans2=max(ans2,c);
        }
        if(ans1>=ans2) printf("Godzilla\n");
        else printf("MechaGodzilla\n");
    }
    return 0;
}
```


---

