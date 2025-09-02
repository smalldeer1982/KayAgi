# 切木棍 Cutting Sticks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=944

[PDF](https://uva.onlinejudge.org/external/100/p10003.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10003/958525065661f78575790c5f6aa2ffbee907fc0b.png)

## 样例 #1

### 输入

```
100
3
25 50 75
10
4
4 5 7 8
0```

### 输出

```
The minimum cutting is 200.
The minimum cutting is 22.```

# 题解

## 作者：__Watcher (赞：17)

update 2020.01.06 使题解符合新版规定

看到下面的大佬都用搜索，那我这里就讲一种不用搜索的 dp

难点：乍一看，这题不是很简单吗？枚举 $i$ 从 $0$ 到 $n-1$ , $j$ 从 $i+2$ 到 $n$ ，k从 $i+1$ 到 $j-1$ ,就可以列出状态转移方程：
```cpp
f[i][j]=min{f[i][k]+f[k][j]|i<k<j}+a[j]-a[i]
```
但明显在求 `f[i][j]` 时并没有求出 `f[k][j]` ，所以我们要换一种枚举方式。

当我们先枚举 $j-i$ ，即木段里面的节点数，就不会出错了。

下面是dp的常规思路：

1、定义状态：$f_{i,j}$ 表示从第i个节点砍到第j个节点的最小花费

2、转移方程：`f[i][j]=min{f[i][k]+f[k][j]|i<k<j}+a[j]-a[i]`

3、注意事项：先枚举节点数
```cpp
#include<bits/stdc++.h>
using namespace std;
int l,n,a[1005],f[105][105];
int main(){
	while(cin>>l){
		if(!l)return 0;
		cin>>n;
		memset(f,10,sizeof(f));//重置数组
		for(int i=1;i<=n;i++){
			cin>>a[i];
			f[i][i+1]=0;//没有节点在中间，就不用切
		}
		a[n+1]=l;//添加一个末节点
		f[0][1]=0;//别忘了初节点
		for(int c=2;c<=n+1;c++){//枚举节点数
			for(int i=0;i+c<=n+1;i++){//枚举开头
				int j=i+c;//计算结尾
				int minn=1e9;
				for(int k=i+1;k<j;k++){
					minn=min(minn,f[i][k]+f[k][j]);
				}
				f[i][j]=minn+a[j]-a[i];//更新数据
			}
		}
		cout<<"The minimum cutting is "<<f[0][n+1]<<"."<<endl;//注意还有一个点
	}
}

```
特别鸣谢：[crxis](https://www.luogu.org/space/show?uid=14512)

---

## 作者：Otue (赞：6)

### 思路
设 $dp_{i,j}$ 为切割 $i$ 到 $j$ 的最优费用，则：

$dp_{i,j}=\min(dp_{i,k}+dp_{k,j}\,|\,i<k<j)+a_j-a_i$

其中最后一项 $a_j-a_i$ 代表第一刀的费用。切完之后，小木棍变成 $i$ 到 $k$ 和 $k$ 到 $j$ 两部分，状态转移方程由此可得。把切割点编号为 $1$ 到 $n$，左边界编号为 $0$，右边界编号为 $n+1$，则答案为 $dp_{0,n+1}$。

状态有 $O(n^2)$，每个状态的决策有 $O(n)$ 个，时间复杂度为 $O(n^3)$。值得一提的是，这题可以用[四边形不等式](https://blog.csdn.net/NOIAu/article/details/72514812)优化到 $O(n^2)$，大家可以试试。
### 四边形不等式
上面那个博客不太详细（看不懂），这里个大家详细介绍一下。

设 $m_{i,j}$ 表示动态规划的状态量（就是 $i$ 到 $j$ 的最优解）

$m_{i,j}$ 有类似如下的状态转移方程：

$m_{i,j}=\min(m_{i,k}+m_{k,j})(i\le k\le j)$

如果对于任意的 $a\le b\le c\le d$，有 $m_{a, c}+m{b, d}\le m_{a, d}+m_{b, c}$，那么 $m_{i,j}$ 满足四边形不等式。

这是使用四边形不等式优化的前题，只有先证明它满足这个条件才可以使用（一般用数学归纳法证明）

**四边形不等式的证明(这里以求min为例)：**

**证明 $s_{i, j-1}\le  s_{i, j} \le s_{i+1, j}$**

设 $d=s_{i, j}$（$i+1 \le k < d$）（$d$ 代表 $i$ 到 $j$ 的最优分割点)，

显然，$m_{i,j(k)}=m_{i,k}+m_{k,j}$

$m_{i,j(d)}=m_{i,d}+m_{d,j}$

且 $m_{i,j(k)} \ge m_{i,j(d)}$，（$m_{i, j}$ 在 $d$ 取到最小值）

构造一个原式：

$\begin{aligned}&m_{i+1,j(k)}-m_{i+1,j(d)}-(m_{i,j(k)}-m_{i,j(d)})\\=&(m_{i+1,j(k)}+m_{i,j(d)})-(m_{i+1,j(d)}+m_{i,j(k)})\\=&m_{i+1,k}+m_{k,j}+m_{i,d}+m_{d,j}-(m_{i+1,d}+m_{d,j}+m_{i,k}+m_{j,k})\\=&m_{i+1,k}+m_{i,d}-(m_{i+1}-m_{i,k})\end{aligned}$

$\because m$ 满足四边形不等式

$\therefore$ 对于 $i<i+1\le k<d$ 则有：

$m_{i,k}+m_{i+1,d}\le m_{i+1,k}+m_{i,d}$

带入原式可得：

$m_{i+1,j(k)}-m_{i+1,j(d)}\ge m_{i,j(k)}-m_{i,j(d)}$

$\because m_{i,j(k)}-m_{i,j(d)}\ge 0$

$\therefore m_{i+1,j(k)}-m_{i+1,j(d)}\ge 0$

$\therefore m_{i+1,j(k)}\ge m_{i+1,j(d)}$

设 $b=s_{i + 1, j}$（$b$ 是 $i+1$ 到 $j$ 上的最优分割点)

则有 $m_{i+1,j(k)}\ge m_{i+1,j(d)} 
\ge m_{i+1,j(b)}$（意思就是说在 $[i + 1, j]$ 上存在 $b$ 使得 $m_{i+1, j}$ 最小，很明显 $m_{i+1, j(k)}$ 不是最小的，而 $i+1 \le k<d$，也就是说 $b$ 肯定不在 $[i+1, d)$ 所以 $b \ge d$）

$\therefore s_{i, j} \le s_{i+1, j}$，同理可得  $s_{i, j-1} \le s_{i, j}$。

所以第三重循环的范围就可以从 $(i, j)$ 压缩到 $(s_{i, j-1}, s_{i+1, j})$。
### 说明
1. 这里不给代码，请自己完成。
2. 借用了一下紫皮书上的类容，所以不要说我是 TJ。

---

## 作者：DrownedFish (赞：4)

### 搜索

把整个木棍放到数轴上，左右端点以及切割点就成为了数轴上的点。

设整个木棍最左端端点为 $a[0]=0$，最右端端点为 $a[n+1]=l$，$a[1]$ ~ $a[n]$ 是各切割点坐标。

则切割一次 $left$ ~ $right$ 费用是 $a[right]-a[left]$ 。



------------


对于每一段木棍，枚举它的切割点，取费用最小的即可。

~~加个记忆化就能过了~~


### **Code**

```

#include <bits/stdc++.h>
#define INF 200004
#define maxn 100
using namespace std;

int l,n,a[maxn],rem[maxn][maxn];

int dfs(int x,int y)
{
	if(rem[x][y]!=-1) return rem[x][y];
	if(x+1==y)        return rem[x][y]=0; 
	
	int ans=INF;
	for(int i=x+1;i<y;i++)           // 枚举切割点 
	ans=min(ans,dfs(x,i)+dfs(i,y));  // 选费用最小的 
	
	return rem[x][y]=ans+a[y]-a[x];  // 记忆化 
}

int main()
{
	ios::sync_with_stdio(false);
	while(cin>>l)
	{
		if(!l) break; cin>>n;
		memset(rem,-1,sizeof(rem));
		for(int i=1;i<=n;i++) 
		cin>>a[i]; a[n+1]=l;
		printf("The minimum cutting is %d.\n",dfs(0,n+1));
	}
	return 0;
}

```

---

## 作者：fengjack (赞：4)

这道题不知怎么看着很眼熟，没错，它就是[石子合并]的变式题，只是把环型变为了线型（是不是有点恍然大悟啊QwQ）

这道题只要逆向思考一下就完全没问题啦（切割和合并本质上其实没什么区别~~）

下面放代码：（超级简单的）

```
#include <bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
int n,l;
int a[52],b[52],f[52][52];

int main()
{
  ios::sync_with_stdio(0);
  while(cin>>l && l)
  {
  	cin>>n;
  	memset(f,inf,sizeof(f));
  	n++;//有n+1段 
  	a[n]=l;
  	for(int i=1;i<n;i++)cin>>a[i];
  	for(int i=1;i<=n;i++)
  	{
  	  b[i]=a[i]-a[i-1];
  	  f[i][i]=0;
	}
	for(int len=1;len<n;len++)//枚举区间长度 
      for(int i=1;i+len<=n;i++)//枚举起点 
      {
      	int j=i+len;//终点 
      	for(int k=i;k<j;k++)//枚举分割点 
      	  f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]+a[j]-a[i-1]);//a[i]相当于前缀和 
	  }
	cout<<"The minimum cutting is "<<f[1][n]<<"."<<endl;
  }
  return 0;
}
```
希望能给大家提供一点帮助QwQ


---

## 作者：hutianjvn666 (赞：4)

### 题目大意：
一根棍子，有n个切割点，每次切的花费为当时木棍的长度
### 解题思路：
记忆化搜索，f[l,r]表示将第l个切割点 到 第r个切割点 所有切割点都切掉的最小花费，
并且第l个切割点与第r个切割点都被切割了
### 调试记录：
一遍AC
```pascal
program hu;
var
 l,n,i,j:longint;
 c:array[0..105] of longint;
 f:array[0..105,0..105] of longint;
function try(l,r:longint):longint;
var
 ans,k:longint;
begin
 if f[l,r]<>-1 then           //记忆化，如果求过，直接退出
   exit(f[l,r]);
 if r-l=1 then           //区间中没有一个切割点
   begin
    f[l,r]:=0;
    exit(f[l,r]);
   end;
 ans:=99999999;    //初值无穷大
 for k:=l+1 to r-1 do                //k表示先切割第几个切割点
   if try(l,k)+try(k,r)<ans then
     ans:=try(l,k)+try(k,r);        //切割，分成l到k 与 k到r两部分
 f[l,r]:=ans+c[r]-c[l];     //第一次切的要算上
 exit(f[l,r]);
end;
begin
 readln(l);
 while (l>0) do
   begin
    readln(n);
    c[0]:=0;
    c[n+1]:=l;    //两端的切割点初始成已被切过
    for i:=1 to n do
      read(c[i]);
    fillchar(f,sizeof(f),255);    //初始化255就是-1
    try(0,n+1);
    writeln('The minimum cutting is ',f[0,n+1],'.');
    read(l);
   end;
end.

```
~~希望管理员大大能通我这个蒟蒻发的题解~~

---

## 作者：zhowipc (赞：3)

#### 看到没有java题解 

看到这道我是很懵的  想了10多分钟把

最终还是翻开了题解 ~~发现一篇新大陆~~

最后总结了一下思路

我们从一个不确定的位置切下去（例子）

10

4

（0）4 5 7 8 （10）~a[i]数组 //首尾手动添加 方便使用

0 1 2 3 4 5 这是下标  方便我后面指明

直接上方程d[i][j] = {d[i][k] + d[k][j]|i<k<j}+a[j]-a[i];  

a[j] 为尾巴  a[i]为头

a[j]- a[i]为这一刀的花费

我们设d[i][j]代表从i~j段的最优费用

我们当i= 0，j = 5  k = 2时

k=2这一段切下去

那么花费就要 count = a[j]-a[i]=10-0=10;

那么总花费就是前一段的花费+后一段的花费 + 刚才那一刀的花费 = d[0][2] + d[2][5] +count
这样不段分解小问题

```
package com.zho.answers;

import java.util.Scanner;

public class Uva10003 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        while (true) {
            int l = input.nextInt();
            if (l == 0)
                break;
            int n = input.nextInt();
//            for (int i = 0; i < 1004; i++)
//                for (int j = 0; j < 1004; j++)
//                    d[i][j] = -1;
            for (int i = 1; i <= n; i++)
                a[i] = input.nextInt();
            a[0] = 0;
            a[n + 1] = l;
            //中间要隔开1  不然不能进行切割
            //（2，3）这样就不知道割哪了  （2，4）至少要这样
            for (int c = 2; c <= n + 1; c++) {
                for (int i = 0; i + c <= n + 1; i++) {
                    int j = i + c;
                    int count = Integer.MAX_VALUE;
                    for (int k = i + 1; k < j; k++) {
                        count = Math.min(count, d[i][k] + d[k][j]);
                    }
                    d[i][j] = count + a[j] - a[i];
                }
            }
            System.out.println("The minimum cutting is " + d[0][n + 1] + ".");
        }
    }

    static int[] a = new int[1010];
    static int[][] d = new int[1010][1010];

    
}

```

虽然菜  但手写也不容易 要个小♥



---

## 作者：安静学习 (赞：3)

~~怕不是个傻子，没关文件输入输出疯狂WA~~

回到正题，这题其实比较简单，就是CLRS上面的矩阵连乘问题的改版，只是我们要把状态方程稍微换一下而已。

首先，money数组表示在i到j长度的时候，最小开销，然后手动的在前面加上0和L以方便我们进行每一段的转移。

**转移方程就是money[i][j] = min(money[i][j], money[i][k] + money[k+1][j]) + (j - i + 1)。   我们在每一个大区间中找到两个分割出来的子区间的最小值**

我们找到了各个可能性，然后比较其中最小的那个。

~~用时590ms，该说还好没有递归实现吗~~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <fstream>
using namespace std;
const int maxn = 1010;
int money[maxn][maxn], best[maxn][maxn], l, n;//最少费用,最佳第一刀
int pos[60];

void init()
{
    for(int i = 0; i < n - 1; i++){
        int Left = pos[i] + 1, Right = pos[i + 1];
        money[Left][Right] = 0;
    }
}

void Dp()
{
    for(int i = 2; i <= n; i++){
        for(int j = 0; j + i <= n; j++){
            int Left = pos[j] + 1, Right = pos[j + i];
            int LeftNow = j, RightNow = j + i;
            int take = 0x3f3f3f3f;
            for(int k = LeftNow + 1; k < RightNow; k++){
                int mid = pos[k];
                take = min(take, money[Left][mid] + money[mid + 1][Right]);
            }
            money[Left][Right] = take + Right - Left + 1;
        }
    }
}

int main(){
    fstream file;
    file.open("out.txt", ios::out);
    while(cin >> l && l){
        memset(money, 0, sizeof(money));
        scanf("%d", &n);
        pos[0] = 0;
        for(int i = 1; i <= n; i++){scanf("%d", &pos[i]);}
        n++;
        pos[n] = l;
        init();
        Dp();
        printf("The minimum cutting is %d.\n", money[1][l]);
        //file << "The minimum cutting is " << money[1][l] << ".\n";
    }
    file.close();
    return 0;
}

```


---

## 作者：MC_Launcher (赞：2)

我来发篇题解

这题分割与合并是一样的，所以可以用区间dp来写

我们开一个f的二维数组，用$f_i,_j$ 来表示从第$i$个分割点到第$j$个分割点全部合并成一根木棍所需最小的代价。

于是乎，枚举一下所有可能的长度与要合并的这一段开头的节点就好。

这里的Minstick是两段木棍分割前各自最小的代价

`Minstick=min(Minstick,f[front][k]+f[k][tail]);`

也就是求出合并前的最小代价

接着
`f[front][tail]=Minstick+a[tail]-a[front];`

代表把两段木棍合并后的最小代价了

可能有些人会问为什么是a[tail]-a[front]而没有+1那我在这里给大家解释一下，很简单的 ~~但是我错在了这里~~

先扔个图 ~~画风简陋请原谅~~

![](https://cdn.luogu.com.cn/upload/image_hosting/sbzn8hxh.png)

其实这不就是个两端植树的植树问题吗？

假如起始点是1，结束是3，那么中间就有2个区间啦。

懂?

重要的地方都介绍完了就上代码吧，还有什么不懂到代码里注释找哈

```cpp
#include<bits/stdc++.h>
using namespace std;
int l,n,a[52],f[105][105];//棍子长度，切割点数，切割点，dp数组
int main()
{
	while(cin>>l)//持续读入，久到离谱
	{
		memset(f,sizeof(f),0);//初始化dp数组，否则在第一次循环时影响结果造成爆0
		if(l==0)return 0;//rt
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			f[i][i+1]=0;//两个相邻切割点之间无需切割
		}
		a[n+1]=l;//增加末节点
		for(int cd=2;cd<=n+1;cd++)//枚举长度
		{
			for(int front=0;front+cd<=n+1;front++)//枚举开头
			{
				int tail=cd+front,Minstick=10000000;//算出结尾
				for(int k=front+1;k<tail;k++)//不断更新最小值
				{
					Minstick=min(Minstick,f[front][k]+f[k][tail]);//已解释
				}
				f[front][tail]=Minstick+a[tail]-a[front];//+1
			}
		}
		cout<<"The minimum cutting is "<<f[0][n+1]<<"."<<endl;//输出
	}
}
```

其实这道题也可以用链表做呢。

可能有人会问为什么没有添加初节点，它不就是0吗我还去找它干啥？如果觉得它是1的人画个图秒懂，还是植树问题。。。

##### 拒绝抄袭，你我有责


---

## 作者：良心油条 (赞：2)

### 比较新颖的解法
其实这道题，不仅可以用dp，还可以用**记忆化搜索**来做。    
- $c$数组保存的是每一个切割点的**位置**，而$f[l][r]$则保存在$l+1$和$r-1$间花费精力的最小值。  
- 因为有多组数据，所以要多组输出，输入格式也要不同。输入如下（大佬勿喷）：   
```pascal
readln(l);
while l<>0 do
  begin
    readln(n);
    for i:=1 to n do
      read(c[i]);
    ....
    readln(l);
  end;
```
- 记忆化搜索时，也有1种不可取的条件：如果$r-l=1$，也就是说中间无点，返回$0$。   
代码如下：~~请勿抄袭~~
```pascal
var
  f:array[0..105,0..105]of longint;
  c:array[0..51]of longint;
  l,i,n:longint; 
function try(l,r:longint):longint;//记忆化搜索
var
  i,ans:longint;
begin
  if f[l,r]<>0 then exit(f[l,r]);
  if r-l=1 then exit(0);
  ans:=maxlongint;
  for i:=l+1 to r-1 do
    if try(l,i)+try(i,r)<ans then
      ans:=try(l,i)+try(i,r);
  f[l,r]:=ans+c[r]-c[l];
  exit(f[l,r]);
end;
begin
  readln(l);
  while l<>0 do  //多组数据输入
  begin
    readln(n);
    for i:=1 to n do
      read(c[i]);
    c[0]:=0;
    c[n+1]:=l;
    fillchar(f,sizeof(f),0);   //我常提起的初始化
    try(0,n+1);   //调用function
    writeln('The minimum cutting is ',f[0,n+1],'.');     //注意格式！！
    readln(l);
  end;
end.
```
~~希望管理员大大让我通过~~

---

## 作者：autoint (赞：2)

刘爷书上的题，我码一遍分析吧。
## 【分析】
设d(i,j)为切割小木棍i～j的最优费用，则d(i,j)=min{d(i,k)+d(k,j)|i<k<j}+a[j]－a[i]，其
中最后一项a[j]－a[i]代表第一刀的费用。切完之后，小木棍变成i～k和k～j两部分，状态转
移方程由此可得。把切割点编号为1～n，左边界编号为0，右边界编号为n＋1，则答案
为d(0,n＋1)。
状态有O(n2)个，每个状态的决策有O(n)个，时间复杂度为O(n3)。

## 【实现】
递推版本要枚举区间长，我个人认为比较僵硬，于是我写的是记忆化搜索。
附上AC代码。（我的命名均是有意义的，结合分析应该能看懂，没有注释请见谅）。
```cpp
#include<bits/stdc++.h>
using namespace std;
template<class T> inline T read(T&x){
    T data=0;
int w=1;
    char ch=getchar();
    while(ch!='-'&&!isdigit(ch))
        ch=getchar();
    if(ch=='-')
        w=-1,ch=getchar();
    while(isdigit(ch))
        data=10*data+ch-'0',ch=getchar();
    return x=data*w;
}
/*
100
3
25 50 75
10
4
4 5 7 8
0
*/
const int maxn=55;
int c[maxn];
int d[maxn][maxn];

int dp(int l,int r){
	if(d[l][r]!=-1)
		return d[l][r];
	if(r-l==1)
		return d[l][r]=0;
	int minans=200000;
	for(int k=l+1;k<=r-1;++k)
		if(dp(l,k)+dp(k,r)<minans)
			minans=dp(l,k)+dp(k,r);
	return d[l][r]=minans+c[r]-c[l];
}

int main(){
	int l,n;
	while(read(l)){
		read(n);
		c[0]=0,c[n+1]=l;
		for(int i=1;i<=n;++i)
			read(c[i]);
		memset(d,-1,sizeof(d));
		dp(0,n+1);
		printf("The minimum cutting is %d.\n",d[0][n+1]);
	}
	return 0;
}

```
###### 手打好累，请管理员AC

---

## 作者：caotianhao (赞：1)

## 插句题外话
1. 本蒟蒻第 $2$ 次写题解；
2. 看到这题我居然想到了 [POJ1159](https://vjudge.net/problem/POJ-1159)（都是区间 DP）；
3. 不会记搜好吧（~~暴搜都不会~~），DP 大法好啊。
## 题目翻译
[传送门](https://www.luogu.com.cn/problem/UVA10003)  
你得把一根木棍砍成几段。根据被切割的木棍的长度收费。他们的工作程序要求他们一次只切一刀。很容易注意到，在切割顺序上的不同选择可能导致不同的价格。例如，考虑一根长度为 $10$ 米的棍子，$2$ 米，$4$ 米和 $7$ 米处可以被切割。有几种选择。我们可以先从 $2$ 点开始切割，然后是 $4$ 点，然后是 $7$ 点。这导致了 $10 + 8 + 6 = 24$ 的价格，因为第一根棍子的长度是 $10$ 米，结果是 $8$，最后一根是 $6$。另一个顺序是 $4$，$2$，$7$。这将导致  $10 + 4 + 6 = 20$，这是一个更好的价格。你的老板信任你的计算机能力，相信你能找出切一根给定的棍子所需的最低成本。
## 题目大意
就是切一根木棍，长度为 $l$，有 $n$ 个要切的点，分别为距离起点长 $a_1$,$a_2$……$a_n$ 的点（递增排序）。每切一次，需要花等同于切之前木棍的长度的钱，问最小花费。     
**切之前长度**：以翻译的第 $2$ 个样例为例，第 $1$ 次切，长度为 $10$；第 $2$ 次切，长度为 $4$（$4$ 号点切断了，分成 $4$ 和 $6$ 两部分，切 $2$ 在 $4$ 的那部分）；第 $3$ 次切，长度为 $6$（同上，切 $7$ 在 $6$ 的那部分）。  
## 解题思路
### DP 要素之一——状态定义
刚刚也说了，这题是区间 DP，那状态就很简单  
$dp_{i,j}$ 表示从第 $i$ 个结点到第 $j$ 个结点之间切木棍的最小花费。
### DP 要素之二——状态转移
我们可以枚举区间（$i,j$）和区间中的切点（$k$），然后推出转移方程：  
$dp_{i,j}=\min(dp_{i,j},dp_{i,k}+dp_{k,j}+(a_j-a_i))$  
$dp_{i,k}+dp_{k,j}+(a_j-a_i)$：从 $k$ 处切割所得的最小花费。  
但是我们会发现一个问题，在算 $dp_{i,j}$ 时，$dp_{k,j}$ 还没算。所以我们改为枚举区间起始点和区间长度（结点个数）。  
### DP 要素之三——状态初始化
1. 如果中间截不了了（$dp_{i,i+1}$），赋值为 $0$；
2. 加上起始结点（$a_0=0$）和末结点（$a_{n+1}=l$）；
------------
解决完 DP，剩下的就都是细节问题了，会在代码中一一展示。
## ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
int l,n,a[1005],dp[55][55];
const int INF=0x3f3f3f3f;
int main(){
	while(scanf("%d",&l)==1){//多组输入数据 
		if(l==0){
			break;
		}
		memset(dp,INF,sizeof(dp));//细节1：初始化为INF，因为后面要求min 
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			dp[i][i+1]=0;
		}
		a[n+1]=l;//加末结点（想一想，为什么不用加起始结点） 
		dp[0][1]=0;//细节2：dp[i][i+1]初始化的时候从1开始，没加dp[0][1] 
		for(int cnt=2;cnt<=n+1;cnt++){//细节3：枚举结点个数时，一个区间至少2个结点，至多n+1个结点 
			for(int i=0;i+cnt<=n+1;i++){//细节4：枚举起始结点要注意从0开始和末结点不能超过n+1 
				int j=i+cnt;//计算末结点	
				for(int k=i+1;k<=j-1;k++){//细节5：切的点不能是起始结点和末结点 
					dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]+(a[j]-a[i]));//转移方程 
				}
			}
		}
		printf("The minimum cutting is %d.\n",dp[0][n+1]);//输出，注意.和换行（vj上在这错了2遍） 
	}
	return 0;
}
```


---

## 作者：Jeremiahy (赞：1)

## 分析

考虑区间 dp，采用递归实现以及记忆化。设 $d_{i,j}$ 为切割小木棍 $i\sim j$ 的最优费用，则 $d_{i,j}=\min\{d_{i,k}+d_{k,j}|i<k<j\}+a_j-a_i$，其中最后一项 $a_j-a_i$代表第一刀的费用。切完之后，小木棍变成 $i\sim k$ 和 $k\sim j$ 两部分，状态转移方程由此可得。把切割点编号为 $1\sim n$，左边界编号为 $0$，右边界编号为 $n+1$，则答案为 $d_{0,n+1}$。


状态有 $O(n^2)$ 个，每个状态的决策有 $O(n)$ 个，时间复杂度为 $O(n^3)$。

值得一提的是，本题可以用四边形不等式优化到 $O(n^2)$（~~然而我太蒻了~~）。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, L, a[53], vis[53][53], d[53][53];
int dp(int i, int j) {
  	if (i >= j - 1) //长度 <= 1，无法切割
	  	return 0;
  	if (vis[i][j])  //已经算过
	  	return d[i][j];
  	vis[i][j] = 1; //记忆化
  	int& ans = d[i][j]; //引用
  	ans = -1;//初始化
  	for (register int k = i + 1; k <= j - 1; k++) {
    	int v = dp(i, k) + dp(k, j) + a[j] - a[i];//状态转移
    	if(ans < 0 || v < ans) //更新答案
			ans = v;
  	}
  	return ans;
}
signed main() {
  	while (cin >> L >> n && L) {
    	for (register int i = 1; i <= n; i++) 
			cin >> a[i];
    	a[0] = 0, a[n + 1] = L;//边界
    	memset(vis, 0, sizeof(vis));//多测清空
    	cout << "The minimum cutting is " << dp(0, n + 1) << ".\n";
  	}
  	return 0;
}
```

注：本题解借用刘汝佳大神的思路进行讲解。


---

## 作者：pokefunc (赞：1)

## 题意

给你一根木棍，上面有 $n$ 个切割点，现在要把木棍从每个切割点切断，每次切割的代价为原木棍的长度，求最小代价。

## 思路

这是一道DP题。

我们定义 $f(l,r)$ 为把从左往右第 $l$ 个切割点到第 $r$ 个切割点之间（不含两端）所有切割点都切断的最小代价。

特别地，我们定义第 $0$ 个切割点为木棍的左端点，第 $n+1$ 个切割点为木棍的右端点。

则答案显而易见的是 $f(0,n+1)$。

转移时枚举 $l$ 到 $r$ 之间（不含两端）的所有切割点，取其中的最小值，最后加上 $l$ 到 $r$ 的间距。

使用转移式可描述为 $f(i,j)=\min\limits_{k=i+1}^{j-1} (f(i,k)+f(k,j) )+a_j-a_i$，其中 $a_i$ 为第 $i$ 个切割点到左端的距离。

边界为 $f(i,i+1)=0$（两个切割点之间如果没有点就不需要切割）。

时间复杂度为 $\Theta(n^3)$。

不过需要注意的是，这道题的难点在于转移顺序。如果按 $i,j,k$ 的顺序转移就会出现需要的状态没算出来的情况。

我直接为了省事的用记忆化搜索（不需要考虑顺序）。

然后就可以AC了。

## Code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long LL;
const int M=53;
const int INF=0x7f7f7f7f;
int L,n,c[M],d[M][M];

int dp(int l,int r){
	int &a=d[l][r]; //引用，能省一点码量也能看得更清晰
	if(a!=-1)return a;
	if(l+1==r)return a=0;
	a=INF;
	for(int i=l+1;i<=r;++i){
		a=std::min(c[r]-c[l]+dp(l,i)+dp(i,r),a);
	}
	return a;
}
 
int main(){
	while(scanf("%d",&L)==1&&L){
		scanf("%d",&n);
		c[0]=0,c[n+1]=L;
		for(int i=1;i<=n;++i)scanf("%d",&(c[i]));
		memset(d,-1,sizeof(d)); //重复利用的数组一定要初始化
		printf("The minimum cutting is %d.\n",dp(0,n+1));
	}
	return 0;
}
```



---

## 作者：HEzzz (赞：0)

## 题目大意 ： 

给你一个长度为 $L$ 的木棍，还有 $n$ 个切割点的位置,你的任务

是在这些切割点的位置处把棍子切成 $n + 1$ 部分使得总切割费用最小。

## 思路 ：

我们可以看见“切割”，这很能让我们联想到区间 DP 中的“枚举断点”。

我们还能观察到 $n$ 的范围很小,只有 $50$ 个这就能证明区间 DP 能行！


## 区间 DP 的框架

```cpp
/*
区间DP框架
不喜勿喷
*/ 
for(int len=2;len<=n;len++)//枚举区间长度 
{
	for(int i=1;i+len-1<=n;i++)//枚举区间左端点 
	{
		int j=i+len-1;//计算出区间右端点 
		for(int k=i;k<j;k++) //枚举断点 
		{
			//状态转移方程 
		}
	}
 } 
```

## 状态转移方程

乍一看 , 似乎很简单耶

``dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]+(a[j]-a[i]);``

## Code 自己写吧

完结撒花

---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA10003)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/05/16/UVA10003%20Cutting%20Sticks/)

## 前言

从紫书上看见的，区间DP 入门题目

### 前置芝士

区间DP

## 分析

这个题的题面很像石子合并，我们不妨考虑区间DP。

我们用 $a[i]$ 表示每个断点的位置，为了方便转移，不妨设 $a[0] = 0$，$a[n + 1] = L$。

我们用 $f[l][r]$ 表示第 $l$ 个断点到第 $r$ 和断点这段区间内的最小费用，那我们按照经典做法枚举中间点 $k$ 可以得到转移方程
$$
f[l][r] = \min_{l<k<r}(f[l][r], f[l][k] + f[k][r] + a[r] - a[l])
$$
转移方程推完了，我们考虑初始化，其中两个断点之间的木棍是不用切割的，所以初始化为
$$
f[i][i + 1] = 0 (0 \le i \le n)
$$
最后的结果就是 $f[0][n + 1]$ (注意有个坑点就是枚举区间长度的时候要枚举到 $n + 2$ )

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 1010;
int a[N];
int f[N][N];

int main()
{
    int L;
    scanf("%d", &L);
    while (L)
    {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        a[n + 1] = L; // 特殊处理
        memset(f, 0x3f, sizeof f);
        for (int i = 0; i <= n; i++)
            f[i][i + 1] = 0;
        for (int len = 3; len <= n + 2; len++) // 区间长度从3到n + 2
            for (int l = 0; l + len - 1 <= n + 1; l++) // 枚举左端点
            {
                int r = l + len - 1;
                for (int k = l + 1; k < r; k++)
                    f[l][r] = min(f[l][r], f[l][k] + f[k][r] + a[r] - a[l]);
            }
        printf("The minimum cutting is %d.\n", f[0][n + 1]);
        scanf("%d", &L);
    }   
    return 0;
}
```



---

