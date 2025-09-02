# Choosing Laptop

## 题目描述

Vasya想购买一台笔记本电脑。商场提供了n台电脑给顾客体验。
Vasya只对以下三个电脑指标比较感兴趣：CPU速度，内存和硬盘。因为Vasya是一个程序员而不是游戏玩家，因此他对其他指标并不感兴趣。
如果一台电脑的三个指标都小于另一台电脑，那么Vasya认为这台电脑是过时的。Vasya不考虑那些过时的电脑，他会在其他（不过时）电脑中选择一台最便宜的。

## 说明/提示

第一和第五台电脑是过时的，因为它们的三个指标都小于第三台。剩下的电脑中第四台最便宜，因此，输出是4。

## 样例 #1

### 输入

```
5
2100 512 150 200
2000 2048 240 350
2300 1024 200 320
2500 2048 80 300
2000 512 180 150
```

### 输出

```
4```

# 题解

## 作者：zhangyuhao9 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF106B)

题目大意
---
第一行输入 $n$，表示总共有 $n$ 个电脑。

每台电脑都按输入顺序依次编号接下来 $n$ 行，每行输入如题目意思的四个指标，如果一台电脑的三个指标都小于另一台电脑，则不考虑它。

剩下的电脑中第四项指标最小的电脑将被选中，输出该电脑的编号。

---
算法分析
---
题目的坑很少，先查询每个电脑是否被舍弃，再直接查找价格最少的电脑直接输出。

~~由于题目过于水，$n<=100$ ~~，这里不多做解释，直接上代码。

---
CODE
---
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101],b[101],c[101],d[101],n,num=0xffffff,ans,flag;//这里有一点要注意num要取一个足够大的数字
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
	cin>>a[i]>>b[i]>>c[i]>>d[i];//输入4个指标
    for(int i=1;i<=n;i++){
        flag=1;
        for(int j=1;j<=n;j++)
            if(a[i]<a[j] && b[i]<b[j] && c[i]<c[j])
	        flag=0;//查找是否过时
        if(flag)
            if(num>d[i])
		num=d[i],ans=i;//剩下的找价格最小值
    }
    cout<<ans;//输出
    return 0;
}
```

求过 $qwq$。

---

## 作者：yuangq (赞：2)

蒟蒻不才，用了一种笨方法

具体注释请看代码

~~~
#include<bits/stdc++.h>
using namespace std;
struct Com{
	int spe;
	int ram;
	int hdd;
	int cos;
}a[1001];//定义结构体 
int N; 
int costs[1001],cmp[1001];
int main()
{
	cin>>N;//输入 
	for(int i=0;i<N;i++)
	{
		cin>>a[i].spe;
		cin>>a[i].ram;
		cin>>a[i].hdd;
		cin>>a[i].cos;//花样输入 
	}
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++) 
		{
			//枚举出两个电脑 
			if(a[i].spe>a[j].spe && a[i].ram>a[j].ram && a[i].hdd>a[j].hdd)//如果编号为j的这台电脑过时了 
			{
				cmp[j]=1;//将j标注 
			}
			if(a[i].spe<a[j].spe && a[i].ram<a[j].ram && a[i].hdd<a[j].hdd)//如果编号为i的这台电脑过时了 
			{
				cmp[i]=1;//将i标注 
			}
		}
	}
	int k=0;//指针 
	for(int i=0;i<N;i++)
	{
		if(cmp[i]==0)//如果没有过时 
		{
			costs[k++]=a[i].cos;//把它的价格加入数组中 
		}
	}
	sort(costs,costs+k);//将价格数组排序 
	for(int i=0;i<N;i++)
	{
		if(a[i].cos==costs[0])//查找最小值对应的下标 
		{
			cout<<i+1;//输出 
			break;//跳出循环 
		}
	}
	return 0;
}

~~~

---

## 作者：lujunyu (赞：2)

## 思路
仔细分析一下，发现 $1\le n\le100$ ，完全可以用双层循环来做。因为本蒟蒻前不久才学了结构体，所以只想到了这一种方法（dalao们不喜勿喷）。先用双层循环排掉所有过时的电脑，在比较剩下电脑的费用，取最小值即可。
## 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct l{
    int cpu;
    int nei;
    int yin;
    int zong;
    int ok=1;//判定有没有过时（1为没过时，0为过时）
    int weizhi;//电脑的原位置
}a[105];
struct m{//没过时的电脑
    int qian;
    int weizhi;
}b[1005];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].cpu>>a[i].nei>>a[i].yin>>a[i].zong;
        a[i].weizhi=i;
    }
    for(int i=1;i<=n-1;i++)
        for(int j=i+1;j<=n;j++)//判断是否过时
        {
                if(a[i].cpu>a[j].cpu&&a[i].nei>a[j].nei&&a[i].yin>a[j].yin)
                    a[j].ok=0;
                if(a[i].cpu<a[j].cpu&&a[i].nei<a[j].nei&&a[i].yin<a[j].yin)
                    a[i].ok=0;    
        }
    int s=0;        
    for(int i=1;i<=n;i++)
        if(a[i].ok==1)
        {
            s++;//计数器加一
            b[s].weizhi=a[i].weizhi;
            b[s].qian=a[i].zong;
        }//保存没过时的电脑的原位置与价格
    int min=b[1].qian;
    int zuo=b[1].weizhi;
    for(int i=2;i<=s;i++)
        if(b[i].qian<min)
        {
            min=b[i].qian;
            zuo=b[i].weizhi;
        }//边找最小值边更新最小值的位置       
    cout<<zuo;  
    return 0;
}
```

---

## 作者：skyskyCCC (赞：1)

**前言。**

一道循环与判断题。

同时也是一道可以用结构体做的题，但是，本片题解的做法不是结构体。

**分析。**

这是本道题的精华：**如果一台电脑的三个指标都小于另一台电脑，那么认为这台电脑是过时的。**

那我们就可以先将第 $i$ 台电脑与其他电脑比，如果发现有一台电脑的三项指标都大于第 $i$ 台电脑，那么第 $i$ 台电脑就过时了，如果没有，那么就在**那台电脑也没有过时的前提下**比较价格，如果更划算，就将答案替换。

最后，输出即可。

代码如下，仅供参考：
```
#include<algorithm>
#include<iostream>//可以只用这一个头文件
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int n,s[105],r[105],h[105],c[105];
//s指speed r指ram h指hdd c指cost
int minn=1000005,ans;//minn要开的足够大
bool pd;
int main(){
    ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);//以上三行均是加速，可省去
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>s[i]>>r[i]>>h[i]>>c[i];//输入
    }
    for(int i=1;i<=n;i++){
        pd=0;//判断初始化
        for(int j=1;j<=n;j++){
            if(s[i]<s[j]&&r[i]<r[j]&&h[i]<h[j]){
            	//符合过时电脑的定义
                pd=1;//过时了
            }
        }
        if(!pd&&minn>c[i]){//没有过时且价格低于目前已找到的最小值
        	minn=c[i];
        	ans=i;//替换价格并记录编号
        }
    }
    cout<<ans<<"\n";//输出
    return 0;
}

```
**后记。**

这道题还是太简单。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：NKL丶 (赞：1)

首先吐槽一句，这个$Vasya$真的~~弱智~~睿智……  
为什么这么说呢？来看这个样例  
```
2
4199 4096 500 100
4200 4096 500 1000
```
很明显，选择1号明显~~赚大发了~~，但是，$Vasya$：我说你过时就是过时……   
1号电脑：？？？
## 以上纯属对题目的吐槽，以下是正题  
考虑到n的范围较小（只有$100$），所以直接按照题意双重循环一遍过即可，由于题意也就比较简洁，所以不需要进行别的处理。  
直接附上代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int a[105],b[105],c[105],d[105],n,minn=1<<30,rans,flag;
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i]>>b[i]>>c[i]>>d[i];//速度，内存，容量，价格
    for(int i=1;i<=n;i++)
    {
        flag=1;
        for(int j=1;j<=n;j++)//双重循环寻找，查看是否过时
            if(a[i]<a[j]&&b[i]<b[j]&&c[i]<c[j])flag=0;
        if(flag)
            if(minn>d[i])minn=d[i],rans=i;//不过时，更新最小值，并记录序号
    }
    cout<<rans;
    return 0;
}
```


---

## 作者：708151_qwq (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF106B)

# 题意简述

`Vasya` 想购买一台笔记本电脑。

商场提供了 $n$ 台电脑给顾客体验，`Vasya` 只对以下三个电脑指标比较感兴趣：CPU 速度，内存和硬盘。

因为 `Vasya` 是一个程序员而不是游戏玩家，因此他对其他指标并不感兴趣。

如果一台电脑的三个指标都小于另一台电脑，那么 `Vasya` 认为这台电脑是过时的。

`Vasya` 不考虑那些过时的电脑，他会在其他（不过时）电脑中选择一台最便宜的。

# Solution

因为此题~~过水~~数据范围小（ $ n \le 100$ ），所以直接暴力枚举即可。

首先，先输入每台电脑的四项指标（ CPU 速度、内存、硬盘、价格 ）。

然后双层循环判断每台电脑是不是过时的。

最后，再不过时的电脑里选择价格最便宜的输出。

# AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, cpu[105], ram[105], hdd[105], cost[105], cnt;
	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		int flag = 0, mini = 1000000;
		scanf("%d%d%d%d", &cpu[i], &ram[i], &hdd[i], &cost[i]);
		for(int j=1; j<=n; j++) {
			if(cpu[i]<cpu[j] && ram[i]<ram[j] && hdd[i]<hdd[j]) flag = 1;
			if(!(flag&1)) {if(cost[i]<mini) {mini = cost[i]; cnt = i; }}
		}
	}
	printf("%d\n", cnt);
	return 0;
}
```

By 2022.6.12 蒟蒻的第九篇题解

---

## 作者：Yh0326 (赞：0)

看完题面，立有思路。

用结构体存下每台电脑的信息（包括编号），输入后再用自定义函数排序一下，并暴力扫一遍，把不过时的电脑存进一个 vector ，再将价格排序，输出最便宜的电脑的编号即可。

代码实现也非常简单：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct comp{
	int s;//cpu速度
	int r;//内存大小
	int h;//硬盘容量
	int c;//价格
	int x;//编号
} v[102];
int n;
inline bool cmp(comp a,comp b){
	if(a.s!=b.s) return a.s>b.s;
	if(a.r!=b.r) return a.r>b.r;
	if(a.h!=b.h) return a.h>b.h;
	return a.c<b.c;
}//按价值排序
inline bool cheap(comp x,comp y){
	return x.c<y.c;
}//按价格排序
vector<comp> w;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){scanf("%d%d%d%d",&v[i].s,&v[i].r,&v[i].h,&v[i].c);v[i].x=i;}
	sort(v+1,v+n+1,cmp);
	for(int i=1;i<=n;++i){
		bool b=1;
		for(int j=1;j<=n;++j){
			if(i==j) continue;
			if(v[i].s<v[j].s&&v[i].r<v[j].r&&v[i].h<v[j].h){b=0;break;}
		}
		if(b) w.push_back(v[i]);
	}//暴力扫，并记录哪些电脑不过时
	sort(w.begin(),w.end(),cheap);//价格排序
	cout<<w[0].x;//输出最便宜的电脑的编号
}
```


---

## 作者：Firstly (赞：0)

这一道题可以使用结构体完成。

## **题目思路：**

我们可知如果一台电脑除价钱之外的所有信息均不如另一台电脑，那么这台电脑就被判定为过时的，不列入考虑范围之内。鉴于该题的数据范围很小，直接二重循环枚举不会超时。那么我们就直接枚举，如果发现前一台电脑除价钱之外的所有信息均不如另一台电脑，那么将其标记为过时的。

在二重循环之后，我们再将所有电脑的信息扫一遍。如果一台电脑没有被标记为过时电脑，且其价格要小于当前最小值，那么更新信息，最后输出即可。

## **Code：**

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
bool guoshi[105];
int n,minn=0x3f3f3f3f,minnum;
struct computer{
	int speed,ram,hdd,cost;
}a[105];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].speed>>a[i].ram>>a[i].hdd>>a[i].cost;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i].speed<a[j].speed&&a[i].ram<a[j].ram&&a[i].hdd<a[j].hdd)
				guoshi[i]=true;
	for(int i=1;i<=n;i++){
		if(guoshi[i])continue;
		if(minn>a[i].cost)minn=a[i].cost,minnum=i;
	}cout<<minnum;
	return 0;
}
```


---

## 作者：hereiszd (赞：0)

比较水的题了，~~但我又被淹死了~~。

## 思路
大体分三步：

1. 电脑数量 $n$ 的范围较小 $(n<100)$，所以直接双重循环一遍过即可，由于题意也就比较简洁，所以不需要进行别的处理。

2. 双重循环判断每台电脑是否过时，这里注意过时的条件是每个参数同时小于一台电脑，而不是小于最大值。

3. 可以用一个变量同时维护是否过时和下标（详见代码）。

## 代码
**重点在于结构体的运用。**

```cpp
#include<bits/stdc++.h>
#define N 105
using namespace std;
struct Node{
	int s;//速度 
	int r;//内存 
	int h;//硬盘 
	int v;//花费 
	int ok;//维护是否过时和下标 
}f[N];
int m;
void check(){//判断是否过时 
	for(int i=0;i<m-1;i++){//枚举出两个电脑
		for(int j=i+1;j<m;j++){
			if(f[i].s<=f[j].s&&f[i].r<=f[j].r&&f[i].h<=f[j].h)
				f[i].ok=-1;//用-1标记过时 
			if(f[j].s<=f[i].s&&f[j].r<=f[i].r&&f[j].h<=f[i].h)
				f[j].ok=-1;
		}	
	}
}
int main(){
	cin>>m;
	for(int i=0;i<m;i++){
		cin>>f[i].s>>f[i].r>>f[i].h>>f[i].v;
		f[i].ok=i+1;//储存下标 
	}
	check();
	Node minn;//循环求最小值 
	minn.v=10000;
	for(int i=0;i<m;i++){//枚举出两个电脑
		if(f[i].ok!=-1&&f[i].v<minn.v)minn=f[i];
		else continue;
	}
	cout<<minn.ok;//输出最小值 
}
```

完结撒花，这题难度也不是很高，建议评红或橙。

---

