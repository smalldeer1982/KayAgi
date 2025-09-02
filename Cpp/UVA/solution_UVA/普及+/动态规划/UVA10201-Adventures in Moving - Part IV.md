# Adventures in Moving - Part IV

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=14&page=show_problem&problem=1142

[PDF](https://uva.onlinejudge.org/external/102/p10201.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10201/382e6b4004094692dc950c88f7e270509288eaf7.png)

## 样例 #1

### 输入

```
1
500
100 999
150 888
200 777
300 999
400 1009
450 1019
500 1399```

### 输出

```
450550```

# 题解

## 作者：GK0328 (赞：3)

AC的第一道灰题诶，发个题解纪念一下~~lalala~~

先给一个题目描述吧。。。

题目的意思是，有一辆车，从起点0到终点len，途中有n个加油站，汽车从0出发，一开始有100L油，油箱的容量为200L，每走一公里需要耗费一升油，你可以在加油站加油，需要你在到达终点时油箱内的油量大于等于100L，如果达终点时油箱内的油量小于100L或者无法到达终点，则输出‘Impossible’

这是一道动态规划。。。

f[i][j]表示到达第i个加油站，油箱内还有jL油的最小花费。

DP分为两步：

①求出到达i的最小花费

DP方程：

**f[i][j]:=min(f[i][j],f[k][j+d[k][i]])  **

**[0<=k<i]**

注意，当j+d[k][i]大于油箱容量时就应该停止了！

②计算加多少油

DP方程：

**f[i][k]:=f[i][j]+(k-j)*a[i][2];   ** 

**[j<k<=200]**

注意，需要保证f[i][j]是可以到达的，且i不是终点。

Pascal Code：

```cpp
//uses math;
var
  f:array[0..405,0..405]of int64;
  d:array[0..405,0..405]of longint;
  a:array[0..405,0..10]of longint;
  n,i,j,k,zty,len,kong:longint;
  ans,inf:int64;
  s,s1:string;
  ch:char;
function min(x,y:int64):int64;
begin
  if x<y then
    exit(x);
  exit(y);
end;
begin
  inf:=1000000000000007;
  readln(zty);
  while zty<>0 do
  begin
    dec(zty);
    readln(len);
    n:=0;
    repeat//读入比较恶心，一不小心就会格式错误
      readln(s);
      if s='' then
        break;
      kong:=pos(' ',s);
      s1:=copy(s,1,kong-1);
      delete(s,1,kong);
      inc(n);
      val(s1,a[n][1]);
      val(s,a[n][2]);
    until false;
    if a[n][1]<>len then//将终点也作为一个加油站
    begin
      inc(n);
      a[n][1]:=len;
      a[n][2]:=0;
    end;
    for i:=0 to n do
      for j:=0 to 200 do
        f[i][j]:=inf;
    for i:=0 to n do
      for j:=i to n do
        d[i][j]:=a[j][1]-a[i][1];//计算加油站之间的距离
    f[0][100]:=0;//显然的初始化
    for i:=1 to n do
      for j:=0 to 200 do
      begin
        for k:=i-1 downto 0 do//第一种情况
          if j+d[k][i]<=200 then
            f[i][j]:=min(f[i][j],f[k][j+d[k][i]]) else
            break;
        if (a[i][2]<>0) and (f[i][j]<>inf) then//第二种情况
        begin
          for k:=j+1 to 200 do
            f[i][k]:=f[i][j]+(k-j)*a[i][2];
        end;
      end;
    ans:=inf;
    for i:=100 to 200 do
      ans:=min(ans,f[n][i]);//只要>=100L均为可行解
    if ans=inf then
      writeln('Impossible') else
      writeln(ans);
    if zty<>0 then
      writeln;//格式。。。
  end;
end.
```





---

## 作者：happy_dengziyue (赞：1)

### 1 题意

输入数据组数 $t$。

对于每组数据，输入终点坐标 $d$，然后输入若干行，每行 $2$ 个数字，代表加油站的坐标与每升油的油费。

一辆车想要从 $0$ 点跑到 $d$ 点。这辆车的油箱容量为 $200$ 升，初始时有 $100$ 升油，每升油跑一个单位长度。这辆车抵达终点时至少要有 $100$ 升油。

这辆车可以跑到终点时还有 $100$ 升油吗？如果可以，输出最小花费，否则输出 `Impossible`。

### 2 思路

这是动规题。

设 $i$，$j$，$k$，表示，到达 $i$ 号加油站时充完 $k$ 升油后有 $j$ 升油。

设 $l$ 为第 $i-1$ 个加油站到第 $i$ 个加油站的距离。

设 $dp[i][j]$ 为，到达第 $i$ 个加油站时有 $j$ 升油的最小代价。

设 $d[i]$ 和 $c[i]$ 表示每个加油站的坐标和油费。

那么，单次加油的费用就是：

$$c[i]\times k$$

综合来看，动规方程就是：

$$dp[i]=\operatorname{min}(dp[i-1][j+l-k]+c[i]\times k)(j+l-k\le200)$$

注意毒瘤的输入格式。别用 `gets` 函数，不然评测姬能把你 CE 到怀疑人生。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<string>
using namespace std;
int t;//测试数据组数
#define max_n 100//最大加油站数量
int n;//加油站数量
int d;//距离
struct G{
	int d;//坐标
	int c;//花费
}g[max_n+2];//加油站
string str;//字符串
char s[max_n+2];//字符串
int dp[max_n+2][202];//动规数组
int inf;//一个很大的数
inline int mi(int a,int b){
	return a<b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("UVA10201_1.in","r",stdin);
	freopen("UVA10201_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	for(int ca=1;ca<=t;++ca){
		n=0;
		scanf("%d",&d);getline(cin,str);
		while(getline(cin,str)){
			//printf("/n=%d %s\n",n,s);
			if(str[0]=='\0'||str[0]=='\n')break;
			for(int i=0;i<str.size();++i)s[i]=str[i];
			s[str.size()]='\0';
			++n;
			sscanf(s,"%d%d",&g[n].d,&g[n].c);
			if(g[n].d>d)--n;
		}
		memset(dp,100,sizeof(dp));
		dp[0][100]=0;
		inf=dp[0][0];
		//printf("n=%d\n",n);
		for(int i=1,l;i<=n;++i){
			l=g[i].d-g[i-1].d;
			for(int j=0;j<=200;++j){
				for(int k=0;k<=j;++k){
					if(j+l-k<=200&&dp[i-1][j+l-k]!=inf){
						dp[i][j]=mi(dp[i][j],dp[i-1][j+l-k]+g[i].c*k);
						//printf("i=%d j=%d dp[i][j]=%d\n",i,j,dp[i][j]);
					}
				}
			}
		}
		if(d-g[n].d>100||dp[n][d-g[n].d+100]==inf)printf("Impossible\n");
		else printf("%d\n",dp[n][d-g[n].d+100]);
		if(ca<t)printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/54712298)

By **dengziyue**

---

## 作者：Jin_Yichen (赞：0)

## 题意简化
~~简化了跟没简化一样~~

一共 $t$ 组数据。

对于每组数据，都有一个终点 $d$，接下来有若干行，每行两个数字，代表一个加油站的位置与油的单价。

一辆车想要从原点跑到 $d$ 点，途径这些加油站。车的初始油量有 $100$ 升，油箱容量有 $200$ 升，每公里消耗 $1$ 升油，且要求到达终点时油量至少有 $100$ 升。

如果可以跑到终点，输出最小花费，否则输出`Impossible`。

## 思路
一眼动规，但我似乎不是很会，借鉴了一下大佬的思路。

建立每个加油站的结构体 $g$，其中 $d$ 和 $c$ 分别表示加油站的位置和油的单价。

再建立动规数组 $dp_{i,j}$，表示到达第 $i$ 个加油站后剩 $j$ 升油的最小花费。

设 $k_i$ 表示到了第 $i$ 个加油站后加了 $k$ 升油，$l$ 为第 $i-1$ 个加油站到第 $i$ 个加油站之间的距离。有每次加油的花费为 $c_i \times k_i$。

所以可得动规方程 $dp_{i,j}= \text{min}(dp_{i-1,j+l-k}+c_i \times k_i)$

注意题目没给出每个数据中加油站的数量，而是在两个数据之间使用空行，所以只能用`getline`和`sscanf`函数。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100;
int t,n,d,INF,dp[maxn+2][202];
struct G{int d,c;}g[maxn+2];
string str;char s[maxn+2];
int main(){
	scanf("%d",&t);
	while(t--){
		n=0;scanf("%d",&d);getline(cin,str);
		while(getline(cin,str)){
			if(str[0]=='\0'||str[0]=='\n')break;
			for(int i=0;i<str.size();++i)s[i]=str[i];
			s[str.size()]='\0';n++;
			sscanf(s,"%d%d",&g[n].d,&g[n].c);
			if(g[n].d>d)--n;
		}
		memset(dp,100,sizeof(dp));
		dp[0][100]=0;
		INF=dp[0][0];
		for(int i=1,l;i<=n;++i){
			l=g[i].d-g[i-1].d;
			for(int j=0;j<=200;j++)
			for(int k=0;k<=j;k++)
			if(j+l-k<=200&&dp[i-1][j+l-k]!=INF)
			dp[i][j]=min(dp[i][j],dp[i-1][j+l-k]+g[i].c*k);
		}
		if(d-g[n].d>100||dp[n][d-g[n].d+100]==INF)printf("Impossible\n");
		else printf("%d\n\n",dp[n][d-g[n].d+100]);
	}
	return 0;
}
```

---

