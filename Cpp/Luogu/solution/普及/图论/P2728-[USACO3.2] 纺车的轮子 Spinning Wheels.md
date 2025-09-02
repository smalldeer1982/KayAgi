# [USACO3.2] 纺车的轮子 Spinning Wheels

## 题目背景

一架纺车有五个纺轮（也就是五个同心圆），这五个不透明的轮子边缘上都有一些缺口。这些缺口必须被迅速而准确地排列好。每个轮子都有一个起始标记（在0度），这样所有的轮子都可以在统一的已知位置开始转动。轮子按照角度变大的方向旋转（即0经过旋转到达1的位置），所以从起始位置开始，在一定的时间内，它们依次转过1度，2度等等（虽然这些轮子很可能不会同时转过这些角度）。


## 题目描述

这是一个整数问题。轮子不会转过1.5度或23.51234123度这样的角度。例如，轮子可能在一秒钟内转过20到25度甚至30到40度（如果转得快的话）。

这个问题中的所有角度都限制在 0 <= 角度 <= 359 这个范围内。轮子转过 359 度后接下来就是 0 度。每个轮子都有一个确定的旋转速度，以秒作为单位。1 <= 速度 <= 180。

轮子上的缺口的起始角度和缺口大小（或宽度）各由一个整数表示，都以度为单位。在一个轮子上，两个缺口之间至少有一度的间隔。宽度也包含缺口起始的角度，**即0 179包括0..179共计180个角度**

在起始位置，设时间为 0，所有的轮子的起始标记排列成一条直线。你的程序必须计算，最早出现每个的轮子上的缺口同其他轮子上的缺口对准（也就是一束光可以通过五个轮子上的五个缺口）情况的时间。这些缺口在任意一个角度对准。


## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 3.2


## 样例 #1

### 输入

```
30 1 0 120
50 1 150 90
60 1 60 90
70 1 180 180
90 1 180 60```

### 输出

```
9```

# 题解

## 作者：「QQ红包」 (赞：17)

模拟题。找不到就输出none。

```cpp
/*
ID: ylx14274
PROG: spin
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int v[6];//速度
int s[6];//数量
int x[6][6],y[6][6];//5个轮子5个洞
int i,j,k,t;//循环控制变量 
int a[361]; 
int b[6]; 
int main() 
{
    freopen("spin.in","r",stdin);
    freopen("spin.out","w",stdout); 
    for (i=1;i<=5;i++)
    {
        scanf("%d%d",&v[i],&s[i]);//读入速度和洞的数量
        for (j=1;j<=s[i];j++)//读入s[i]个洞 
            scanf("%d%d",&x[i][j],&y[i][j]);//读入洞的位置和宽度
    } //读入完毕
    //读进来了。要干嘛来着……
    for (t=0;t<=360;t++)//可能一开始就有一个地方5个轮子在那都是洞 
    {
        memset(a,0,sizeof(a));//a清0 
        for (i=1;i<=5;i++)//5个轮子
        {
            for (j=1;j<=s[i];j++)//s[i]个洞 
            {
                for (k=x[i][j];k<=x[i][j]+y[i][j];k++)//标记到数组a
                    a[k%360]++;//标记。记得取模 
                x[i][j]=(x[i][j]+v[i])%360;//下一秒状态。记得取模 
            } 
        } //标记完成 
        for (i=0;i<=359;i++)
        if (a[i]==5)//5个轮子在此处均为洞
        {
            printf("%d\n",t);//输出 
            return 0;
        } 
    } 
    printf("none\n");
    return 0; 
}
```

---

## 作者：王轩逸 (赞：5)

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=10,W=10;
/*
无论轮子的旋转速度是多少，经过 360 秒后，每一个轮子都回到了各自
开始的位置，也就是说，如果在[0, 359]秒内没有重合，那就不会重合了。
枚举记录[0,359]每一秒 5 个轮子的缺口所占的角度。
gap[i]记录角度 i 除的缺口数量，如果 gap[0]到 gap[359]中有一个为 5，
则表示 5 个轮子的缺口重合了。
*/ 
int gap[360];
struct Wheel{
	int sp,num,st[W],len[W]; //转动速度、缺口数量、缺口的起始位置和长度。
}w[N];
int main(){
	int n=5;//5 个轮子
	for(int i=1;i<=n;i++){
		cin>>w[i].sp>>w[i].num;//读取转动速度和缺口数量
		for(int j=1;j<=w[i].num;j++)
			cin>>w[i].st[j]>>w[i].len[j];//读取每个缺口的起始位置和长
	}
	for(int t=0;t<360;t++){//最多转动 360 秒后，所有轮子会回到初始位置。
		memset(gap,0,sizeof(gap));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=w[i].num;j++){//j 个缺口
				for(int k=0;k<=w[i].len[j];k++)
					gap[(w[i].st[j]+k)%360]++;
				w[i].st[j]=(w[i].st[j]+w[i].sp)%360;//模拟转动。
			}
		}
		for(int i=0;i<360;i++)
			if(gap[i]==5){
				cout<<t;
				return 0;
			}
	}
	cout<<"none";
	return 0;
}
```


---

## 作者：pigstd (赞：4)

方法：模拟

$sum[i]$代表角度为$i$的缺口数，如果$sum[i]$等于5，那么成立

其余解释在代码里

c++代码：
```
#include<bits/stdc++.h>
using namespace std;

const int M=365;
struct node
{
	int v,sum;
	int k[10],f[10];//k是宽度，f是初始位置
}a[10];

int sum[M];

int main()
{
	for (int i=1;i<=5;i++)
	{
		cin>>a[i].v>>a[i].sum;
		for (int j=1;j<=a[i].sum;j++)
			cin>>a[i].f[j]>>a[i].k[j];
	}
	for (int i=0;i<360;i++)//第i秒
	{
		memset(sum,0,sizeof (sum));//每次都要memset
		for (int j=1;j<=5;j++)//第j个轮子
			for (int k=1;k<=a[j].sum;k++)//第k个缺口
				for (int w=0;w<=a[j].k[k];w++)//w是缺口的度数
					sum[(a[j].f[k]+i*a[j].v+360+w)%360]++;//注意要%360,否则会RE
		for (int j=0;j<360;j++)
			if (sum[j]==5)
			{
				cout<<i;
				return 0;
			}
	}
	cout<<"none";//找不到
	return 0;
}
```

---

## 作者：yangyujia18 (赞：2)

### 模拟题，没什么好说的
```
#include<bits/stdc++.h>
using namespace std;
struct p//s为起点，w为宽度 
{
	int s,w;
};
int main()
{
	int numw=5,ans=0;//轮子数量和首次对齐的秒数 
	int kou[numw],speed[numw];//口数和速度 
	vector<p> kouwei[numw];//口 
	int is[400];//在第i度有几个缺口is[i] 
	
	for(int i=0;i<numw;i++)//输入 
	{
		cin>>speed[i]>>kou[i];
		for(int j=1;j<=kou[i];j++)
		{
			int s,w;
			cin>>s>>w;
			kouwei[i].push_back((p){s,w});
		}
	}
	while(ans<=360)//在第360秒时所有缺口一定转回原位 
	{
		memset(is,0,sizeof(is));//没有后果自负 
		for(int i=0;i<numw;i++)//转 
			for(int j=0;j<kou[i];j++)
			{
				for(int l=kouwei[i][j].s;l<=kouwei[i][j].s+kouwei[i][j].w;l++)//枚举口中的每一度 
					is[l%360]++;//l处多一个口 
				kouwei[i][j].s=(kouwei[i][j].s+speed[i])%360;//i号轮子转一秒（其实应该再写一个循环，这是节省的写法） 
			}
		for(int i=0;i<360;i++)//判断 
			if(is[i]==numw)//集齐五个口召唤神龙 
			{
				cout<<ans<<endl;
				return 0;
			}
		ans++;
	}
	cout<<"none"<<endl;//没有 
	return 0;
}
```
第二次写题解，大家多多支持！

---

## 作者：此后无良辰 (赞：2)

//其实和下楼做法差不多，但只是给用struct的人看下 //lth

```cpp
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int w[6],num[6],t;
int a[361];
struct {
    int sta[6];//kaishi
    int lon[6];//kuandu
    //int    now[6];
}s[30];
int main() {
    for(int i=1;i<=5;i++)
    {cin>>w[i]>>num[i];
        for(int j=1;j<=num[i];j++){
            cin>>s[i].sta[j]>>s[i].lon[j];//duru
                }}
for(int t=0;t<=360;t++){
memset(a,0,sizeof(a));//记得每次清0，原本我就错这
for(int i=1;i<=5;i++){
for(int j=1;j<=num[i];j++)    {
    for(int k=s[i].sta[j];k<=s[i].sta[j]+s[i].lon[j];k++)
        a[k%360]++;//biaojiyici
        s[i].sta[j]=(s[i].sta[j]+w[i])%360;//下一秒的状态
}}
//for(int i=0;i<=360;i++)
//cout<<a[i];//这一段打出来你可以明白这整个的过程，就很清楚了，提交的时候删掉
for(int i=0;i<=359;i++)
    if(a[i]==5){
        printf("%d",t);
        return 0;}
    }
 cout<<"none"<<endl;
return 0;}
```

---

## 作者：袁宇轩 (赞：1)

前往[题目](https://www.luogu.com.cn/problem/P2728)

很明显~~暴力~~模拟，预估时间复杂度O(360n)。

注意几个细节：

1.读入的是缺口的起点和宽度，而不是起点和终点；

2.轮子转一圈是0~359°，为防止爆数组，建议把指针%360；

3.外循环的时间只需从1到360，因为超过360之后都是重复的。

附上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int const SIZE=360+3;
int const N=30;
int t=0,n,vis[SIZE];
struct node{
	int v,l,r;
}a[N];
int main()
{
	for (int i=1;i<=5;i++)
	{
		int x,y;
		cin>>x>>y;
		while (y--)
		{
			int L,R;
			cin>>L>>R;
			a[++n].v=x;//速度 
			a[n].l=L;//左端点 
			a[n].r=L+R;//右端点 
			for (int i=L;i<=L+R;i++) vis[i%360]++;//标记缺口位置 
		}
	}
	for (int i=0;i<360;i++)//特判是否无需转动就可以通过 
	  if (vis[i]==5)
	  {
	  	  cout<<0<<endl;
	  	  return 0;
	  }
	t=1;
	while (t<=360)//最多360秒 
	{
		for (int i=1;i<=n;i++)//修改每个轮子缺口的位置 
		{
			int L=a[i].l+a[i].v;
			int R=a[i].r+a[i].v;
			for (int j=a[i].l;j<L;j++) vis[j%360]--;//左端点旋转的角度要-1 
		    for (int j=a[i].r+1;j<=R;j++) vis[j%360]++;//右端点旋转的角度要+1 
		    a[i].l=L%360;//修改左端点 
		    a[i].r=R%360;//修改右端点 
		}
		for (int i=0;i<360;i++)//判断是否有一束光能穿透 
		  if (vis[i]==5)//若vis[i]=5则这个角度有5个缺口，光能穿过 
		  {
		  	  cout<<t<<endl;
		  	  return 0;
		  }
		t++;
	}
	puts("none");//无解 
	return 0;
}
```


---

## 作者：傅思维666 (赞：1)

模拟。其实没什么好说的，读入处理可以有很多种方法，最后枚举时间，一层一层枚举缺口，最后就能AC掉。

### 我在这里想和大家探讨一下关于这种圆轮题怎么处理：
先上代码再解释：
```cpp
#include<cstdio>
#include<cstring> 
using namespace std;
int speed[6];
int s[6];
int p[6][6],width[6][6];
int v[361]; 
int main() 
{
    for(int i=1;i<=5;i++)
    {
        scanf("%d%d",&speed[i],&s[i]);
        for(int j=1;j<=s[i];j++)
            scanf("%d%d",&p[i][j],&width[i][j]);
    }
    for(int t=0;t<=360;t++)
    {
        memset(v,0,sizeof(v));
        for(int i=1;i<=5;i++)
            for(int j=1;j<=s[i];j++)
            {
                for(int k=p[i][j];k<=p[i][j]+width[i][j];k++)
                    v[k%360]++; 
                p[i][j]=(p[i][j]+speed[i])%360; 
            }
        for(int i=0;i<=359;i++)
            if (v[i]==5)
            {
                printf("%d",t); 
                return 0;
            } 
    }  
    printf("none");
    return 0; 
}
```
在这里我采用了~~合理的~~压行。

所谓**圆轮题**是我给起的名，大体就是那种收尾相连的串，如果用数组的话会越界，再就会WA，因为根据题意，1的前面是n，n的后面是1，如果用数组模拟的话，我的想法是开三倍的数组，然后把串复制三份扔进去，再...

#### 哇，麻烦死了。

### 所以我们想到了另外一种做法。

我们的数组不用开三倍，开一倍的即可，当我们需要找数组下标时怎么办呢?

很简单，把枚举到的数（可能会超出n的范围），对n取模即可。

很好理解吧！然后就可以进行后续的操作。

针对本题，不仅在v[k%360]的时候用到了这个思想，在它的下一行——p[i][j]=(p[i][j]+width[i][j])%360的时候也同样用到了这样的原理。

希望同学们多多体会。

### 也希望管理大大给过！！

最后祝大家生活愉快！！——FSW

---

## 作者：Marginal_world (赞：1)

```cpp
#include<bits/stdc++.h>//伟大的万能头文件
using namespace std;
struct s{
	int p,q;
}a[100][100];//定义一个结构体，p代表缺口起始位置，q代表宽度
int b[10],c[10],d[500],i,j,l,sum;//b数组是速度，c数组是缺口个数，sum是最早的结果，d数组计数
int main(){
	for(i=1;i<=5;i++){
		cin>>b[i]>>c[i];
		for(j=1;j<=c[i];j++)
		cin>>a[i][j].p>>a[i][j].q;
	}//输入，不解释
	while(sum<=360){
		memset(d,0,sizeof(d));//一定要清空，否则后果自负
		for(i=1;i<=5;i++){
			for(j=1;j<=c[i];j++){
				for(l=a[i][j].p;l<=a[i][j].p+a[i][j].q;l++)
				d[l%360]++;//有缺口的位置计数
				a[i][j].p=(a[i][j].p+b[i])%360;//模拟一秒下来
			}
		}
		for(i=0;i<=359;i++)
		if(d[i]==5){//如果五个轮子在一块儿
			cout<<sum;
			return 0;
		}
		sum++;//记得++
    } 
	cout<<"none";
	return 0;
}
```


---

