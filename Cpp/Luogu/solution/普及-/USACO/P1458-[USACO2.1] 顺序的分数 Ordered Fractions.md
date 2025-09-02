# [USACO2.1] 顺序的分数 Ordered Fractions

## 题目描述

输入一个自然数 $n$，对于一个最简分数 $a/b$（分子和分母互质的分数），满足 $1 \le b \le n,0 \le a/b \le 1$，请找出所有满足条件的分数。

这有一个例子，当 $n=5$ 时，所有解为：

$$\frac01,\frac15,\frac14,\frac13,\frac25,\frac12,\frac35,\frac23,\frac34 ,\frac45,\frac11$$

给定一个自然数 $n$，请编程按分数值递增的顺序输出所有解。
 
注：   
1、$0$ 和任意自然数的最大公约数就是那个自然数。    
2、互质指最大公约数等于1的两个自然数。


## 说明/提示

【数据范围】    
对于 $100\%$ 的数据，$1\le n \le 160$。

USACO 2.1

翻译来自NOCOW


## 样例 #1

### 输入

```
5
```

### 输出

```
0/1
1/5
1/4
1/3
2/5
1/2
3/5
2/3
3/4
4/5
1/1
```

# 题解

## 作者：浮尘ii (赞：35)

发现很多题解都是枚举+sort做的……

这里介绍一种方法：分治。

我们假设有两个分数a/b<c/d。我们要从小到大输出这个区间上满足题意的分数。

我们令m = a + c, n = b + d。可证明a / b < m / n < c / d. （交叉相乘即可证明）

并且我们可以证明这些分数都是最简的。（并不会证明233）

那么我们只需要对m/n的左右两个区间继续分治，即可按顺序得到所求分数。

然后这种方法来源于做过的一道 分数树 的题。这里贴个链接：http://www.docin.com/p-1022648660.html

------------

(2019.7.11 upd) 对以上部分内容进行补充：

可以发现这样分治过程形成了一棵树，这样的树叫做 Stern-Brocot Tree。这棵树能够不重不漏的表示所有有理数（既约分数）。

构造方法是：第一层是 $\frac{0}{1}$ 和 $\frac{1}{0}$，每次在两个相邻分数 $\frac{m}{n}, \frac{m'}{n'}$ 之间插入 $\frac{m + m'}{n + n'}$，并把新生成的节点插入下一层中。

则有如下性质：对于任意构造阶段的两个相邻分数 $\frac{m}{n}, \frac{m'}{n'}$，有 $m'n - mn' = 1$，可以用归纳法证明得到。

接着由这个性质可以证明每个有理数都存在：假设 $\frac{a}{b}$ 不在任意一层序列中，则对于每一层找到最接近 $\frac{a}{b}$ 的两个分数 $\frac{m}{n} \lt \frac{a}{b} \lt \frac{m'}{n'}$，则有
$$an - bm \ge 1, bm' - an' \ge 1$$

于是：
$$(an - bm)(m'+n') + (bm' - an')(m+n) \ge m+n+m'+n'$$

又由 $m'n - mn' = 1$ 得：
$$a+b \ge m + n + m' + n'$$

而右边可以取到 $\infty$，矛盾。这样就证明了每个有理数都存在于这棵树中。

接着可以发现树中每个有理数是不重复的，因为 $\frac{a}{b} \lt \frac{a + a'}{b + b'} \lt \frac{a'}{b'}$。

这道题只需要从 $\frac{0}{1}$ 和 $\frac{1}{1}$ 中间夹的子树分治即可。

------------

然后上代码（Pas代码下面几篇题解里有，这里贴C++的）

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int    N;

void DFS(const int& l1, const int& l2, const int& r1, const int& r2)
{
    if(l2 > N || r2 > N)
        return;

    DFS(l1, l2, l1 + r1, l2 + r2);
    if(l2 + r2 <= N)
        printf("%d/%d\n", l1 + r1, l2 + r2);
    DFS(l1 + r1, l2 + r2, r1, r2);
}

int main()
{
    cin >> N;

    printf("0/1\n");
    DFS(0, 1, 1, 1);
    printf("1/1\n");

    return 0;
}
```

---

## 作者：重回巅峰！ (赞：15)

HX发明的超级不需排序法。

不懂得可以手动模拟

```cpp
var n:longint;
 procedure work(a,b,c,d:longint);
 var midx,midy:longint;
   begin
     midx:=a+c;midy:=b+d; //分子分母分别相加
     if midy>n then exit;//如果分母比N大就退出
     work(a,b,midx,midy);//二分继续递归
     writeln(midx,'/',midy);
     work(midx,midy,c,d);
   end;
begin
  readln(n);
  writeln('0/1');//直接输出第一个
  work(0,1,1,1);//求0/1~1/1之间的最简真分数
  writeln('1/1');//直接输出最后一个
end.
```

---

## 作者：jun1lesszZZ (赞：14)

看到没有大佬写深搜，我来一发递归DFS

递归的是分子，在子函数内循环枚举分母即可，不要忘了先输出一个“0/1”，最后输出一个“1/1” 

代码如下
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,dd,xx,yy,sum;
bool vis[200][200];
double ZZZ;
struct ujj{
    int x,y;
    double zzz;
}ans[100000];
int gcd(int x,int y){
    return y == 0 ?  x :  gcd(y,x % y);//三目运算符，求最大公约数
}
void dfs(int x){//分母
    if(x > n) return;
    for(int i = n;i >= x;i --){//枚举分母
        if(x < i){
            dd = gcd(x,i);//gcd函数求最大公约数
            xx = x / dd,yy = i / dd;//两个数同除最大公约数即可得到最简形式
            if(! vis[xx][yy]){//用vis数组来存储这个分数是否已经枚举过
                vis[xx][yy] = 1;
                ZZZ = xx * 1.0 / yy * 1.0;
                ans[++ sum] = {xx,yy,ZZZ};//结构体存储这个分数与分数的小数形式，方便排序后从小到大输出
            }
        }
            
    }
    dfs(x + 1);//寻找下一个分子
}
bool cmp(ujj x,ujj y){//自定义排序规则，按分数从小到大排
    return x.zzz < y.zzz;
}
int main(){
    scanf("%d",&n);
    dfs(1);
    sort(ans + 1,ans + sum + 1,cmp);
    printf("0/1\n");
    for(int i = 1;i <= sum;i ++)
        printf("%d/%d\n",ans[i].x,ans[i].y);
    printf("1/1");
}
```


---

## 作者：lzpclxf (赞：10)

ok，来吧

这道题，读完题目之后，应该题意是比较容易理解的；

题意就是给出一个数，

让您求分母在这个数的范围内并且整个分数要小于等于一的所有的分数，并且还要注意输出的时候是要有顺序的。

那么我们就可以直接枚举，判断并记录。

首先我们输入之后直接来枚举两层for循环找出所有能找出来的分数
```cpp
for(int i = 0; i <= n; i++)
		for(int j = 1; j <= n; j++) 
			if(i <= j) {//亲爱的们，这里是一个判断条件，只要分子比分母大我们才可以选他做分数
				int rom = gcd(i, j);
				if(rom == 1) {//其实这两个if完全可以合并到一起也就是只留第二个
					head++;
					num[head].x = i;
					num[head].y = j;
					num[head].mal = i * 1.0 / j * 1.0;
				} 
				else if(rom != 1) {
					head++;
					num[head].x = i / rom;
					num[head].y = j / rom;
					num[head].mal = (i / rom * 1.0) / (j / rom * 1.0);
				} 
			}
```

gcd 函数判断最大公约数

```cpp
int gcd(int x,int y) {
	return y == 0 ? x : gcd(y, x % y);
}
```
按照分数的大小来排序

```
int cmp(zero x,zero y) {
	return x.mal < y.mal;
}
```
最后干干净净的AC代码（个人喜好）


```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, head;
struct zero{
	int x, y;
	double mal;
}num[100000];
int gcd(int x,int y) {
	return y == 0 ? x : gcd(y, x % y);
}
int cmp(zero x,zero y) {
	return x.mal < y.mal;
}
int main() {
	scanf("%d",&n);
	for(int i = 0; i <= n; i++)
		for(int j = 1; j <= n; j++) 
			if(i <= j) {
				int rom = gcd(i, j);
				if(rom == 1) {
					head++;
					num[head].x = i;
					num[head].y = j;
					num[head].mal = i * 1.0 / j * 1.0;
				} 
				else if(rom != 1) {
					head++;
					num[head].x = i / rom;
					num[head].y = j / rom;
					num[head].mal = (i / rom * 1.0) / (j / rom * 1.0);
				} 
			}
	sort(num + 1, num + 1 + head,  cmp);
	for(int i = 1; i <= head; i++) 
		if(num[i].mal != num[i + 1].mal)
			printf("%d/%d\n",num[i].x, num[i].y);
	return 0;
}
```


---

## 作者：weak_ddb (赞：8)

    这种题目应该是排序初学者就能学会的题目（手动滑稽）

    废话不多说，直接分析题目
    
    思路1：所有分数互质：
    所以我们需要定义gcd函数
    
```cpp
int gcd(int x,int y)
{
	return (x%y==0)? y:gcd(y,x%y);
}

或

__gcd(x,y)//NOIP不允许
```

    思路2：分数按照分数值递增排序
    排序：sort函数大法好，但是我们平时的排序是单个的数排序，但是现在是分数排序，有两种思路
    
    one: 
```
bool cmp(fs a,fs b)
{
	double c,d;
	c=1.0*a.fz/a.fm;
	d=1.0*b.fz/b.fm;
	return c<d;
}
```

    two: 
```
bool cmp(fs a,fs b)
{
	return a.fz*b.fm<b.fz*a.fm;
}
```
~~就看您是大佬还是蒟蒻了~~


    思路3：N<=160
    这说明身为蒟蒻的我们可以双重穷举构造分数
    
```
for(int i=1;i<=n;i++)
	for(int j=1;j<=i-1;j++)//分子必须小于分母（0<=a/b<=1)(0和1的情况会在主程序里特殊体现）
		if(gcd(i,j)==1)
		{
			k++;
			x[k].fz=j;//保存分子
			x[k].fm=i;//保存分母
		}
```

    说到这里，也不用我多说了吧
    全部程序还是要贴一下的
    
    
```
#include<bits/stdc++.h>
using namespace std;
struct fs
{
	int fm,fz;
}x[1000005];//储存分数结构体，fm为分母，fz为分子
bool cmp(fs a,fs b)
{
	double c,d;
	c=1.0*a.fz/a.fm;
	d=1.0*b.fz/b.fm;
	return c<d;
}
int gcd(int x,int y)
{
	return (x%y==0)? y:gcd(y,x%y);
}
int main()
{
	int n,k=2;
	cin>>n;
	x[1].fz=0;//特殊考虑0和1的情况
	x[1].fm=1;
	x[2].fz=1;
	x[2].fm=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i-1;j++)
			if(gcd(i,j)==1)
			{
				k++;
				x[k].fz=j;
				x[k].fm=i;
			}
	sort(x+1,x+k+1,cmp);
	for(int i=1;i<=k;i++)
	printf("%d/%d\n",x[i].fz,x[i].fm);
	return 0;
}
```

---

## 作者：谦谦君子 (赞：6)

这题很水 用结构体和排序就行了 直接看代码 加了注释
```cpp
#include<bits/stdc++.h>
using namespace std;
struct number
{
	int x,y;
	double z;  //x,y是分子和分母，z是分数值
}a[1000001];
bool hz(long a,long b)
{
	for(int i=2;i<=200;i++)
	{
		if(a%i==0&&b%i==0)  //当a,b能同时整出一个数，返回0，即不互质
		{
			return 0;
		}
	}
	return 1;  //互质
}
int cmp(number a,number b) //结构体排序，用来给分数值排序
{
	return a.z<b.z;
}
int main()
{
	int n,sum=0;
	cin>>n;
	cout<<"0/1"<<endl;  //提前输出最小的0，最后输出最大的1，0，1必被包含
	for (int i=1;i<=n;i++)
	{
		for (int j=n;j>=1;j--)
		{
			if (i!=j&&i<j)  //根据题目条件：最简分数a/b（分子和分母互质的分数）,满足1<=b<=N,0<=a/b<=1
			{
				sum++;//分数个数
				a[sum].z=(i*1.0000)/(j*1.0000)*1.0000;  //分数值，因为i,j是整数，所以要乘1.0000
				a[sum].x=i;
				a[sum].y=j;
			}
		}
	}
	sort(a+1,a+sum+1,cmp);
	for(int i=1;i<=sum;i++)
	{
		if(hz(a[i].x,a[i].y)==1)  //分数需满足条件最简
		{
			cout<<a[i].x<<"/"<<a[i].y<<endl;
		}
	}
	cout<<"1/1"<<endl;
	return 0;
}
```

---

## 作者：御·Dragon (赞：5)

# 用十字交叉法来手动排序，[十字交叉法](https://baike.so.com/doc/2798024-2953236.html) 

## 可以不用最大公因数来判断，我用的再正常不过的了,其实最要注意的是数组开小了，~~一开始还把判断大小的大于号写成小于号~~


## 话不多说，附上代码：


```
//已AC： 
#include<bits/stdc++.h>//万能头的粉丝在这里%%% 
using namespace std;

const int MAXN = 100000;//数组不能开160，被坑了好久 

int pd(int x,int y){//这里就没有直接判断最大公约数，直接的判断是否互质 
	if(x == 1 && y == 1)return 1;//只有1和1这种两个数一样的才行，其余像2和2的就pas掉 
	if(x == 0 && y != 1)return 0;//因为我不是判断最大公约数，所以要单独判断0和1的，0和其他的就不行 
	if(x >= y)return 0;//分子大于或等于分母（前面已经把1的单独判断了）就退出 
	for(int i = 2;i <= min(x,y); i++){//开始 ，从2开始 
		if(x % i == 0 && y % i == 0)return 0;//若有一样的就下一个 
	}
	return 1;//其余都是可以的 
}

int n;
int f[MAXN][5];//记录分子和分母 
int a = 1;//从下面记录有几个分数 

void px(){//手动排序 
	for(int i = 1;i <= a; i++)//枚举第一个数 
		for(int j = i + 1;j <= a; j++){//枚举第二个数 
			if((f[i][2] * f[j][1]) < (f[i][1] * f[j][2])){//这里是十字交叉法很好用
				//如果符合则交换 
				int x = f[i][1];
				f[i][1] = f[j][1];
				f[j][1] = x;
				x = f[i][2];
				f[i][2] = f[j][2];
				f[j][2] = x;
			}
		}
}

int main(){//骚年开始表演 
	cin>>n;
	
	for(int j = 1;j <= n; j++)//枚举分母 
		for(int i = 0;i <= n; i++){//枚举分子，注意分子可以为0 
			if(pd(i,j)){//判断
			//符合要求则记录下来 
				f[a][1] = i;
				f[a][2] = j;
				a++;//分数数加1 
			}
		}
	px();//手动排序 
	for(int i = 1;i < a; i++){//输出 
		cout<<f[i][1]<<"/"<<f[i][2]<<endl;//其实可以scnaf("%d/%d",f[i][1],f[i][2])的 
	}
	return 0;
}//完美收尾 
```

---

## 作者：开挂老司机 (赞：4)

没人用二分做吗？

来一发二分答案：
```cpp
#include<cstdio>
using namespace std;
int n;
void binary(int l1,int l2,int r1,int r2)
{
	int sum1=l1+r1,sum2=l2+r2;
	if(sum2>n)//如果大于n就停
	  return ;
	binary(l1,l2,sum1,sum2);//递归左路
	printf("%d/%d\n",sum1,sum2);//输出
	binary(sum1,sum2,r1,r2);//递归右路
}
int main()
{
	scanf("%d",&n);
	puts("0/1");
	binary(0,1,1,1);//二分答案
	puts("1/1");//先输出最小的和最大的
	return 0;
}
```

---

## 作者：ylsoi (赞：4)

好吧，这题思路很简单，就是从小到大来枚举每一个分数的分子分母，然后记录下他们的分子除以分母的小数值，最后可以写一个cmp函数来按照他们小数值来从小到大来排序；但是有一点要注意的是，每一组数据都会有一个一份之零

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn=160;
int n,len;
int find(int x,int y)
{
    if(x%y==0)return y;
    else return find(y,x%y);
}
struct node
{
    int a;
    int b;
    double a_b;//这里一定要开double才可以过的（当然我是没有试过float的）
}f[maxn*maxn];
bool cmp(node a,node b)
{
    return a.a_b<b.a_b;
}
int main()
{
    scanf("%d",&n);
    len++;
    f[len].a=0;
    f[len].b=1;
    f[len].a_b=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            if(find(i,j)==1)
            {
                len++;
                f[len].a=j;
                f[len].b=i;
                f[len].a_b=j*1.0/i;
            }
    sort(f+1,f+len+1,cmp);
    for(int i=1;i<=len;i++)
    printf("%d/%d\n",f[i].a,f[i].b);
    return 0;
}
```

---

## 作者：YczSS (赞：4)

优化

1.0/1,1/x不能漏了！有1/1


2.若是两个偶数，不用判断绝对不行


3.两个分数比较大小，只需交叉相乘即可，无需另开data储存具体值。

如：a1/b1<a2/b2 ==>a1\*b2<a2\*b1



[编辑] 快排


枚举所有的分数，判断其是否是最简（分母分子最大公约数＝1），用一个数列记录所有最简分数，然后用快排排序。


[编辑] 归并


显然，0/i 1/i 2/i...i/i这个序列是有序的 对于n个序列归并即可（相等则取分母最小的一个——这样显然是最简分数）


```cpp
var i,p,q,n:longint;
  a:array[1..1000]of longint;
begin
  readln(n);
  for i:=1 to n do a[i]:=0;
  repeat
    p:=a[1];
    q:=1;
    for i:=2 to n do
      if p*i>q*a[i] then begin
        p:=a[i];
        q:=i;
      end;
    writeln(p,'/',q);
    for i:=1 to n do
      if p*i=q*a[i] then inc(a[i]);
  until a[1]=2;
end.
```

---

## 作者：大魔鬼灿灿 (赞：2)

### 这题不是很难，就是几个知识点放在一起了，细心认真就能轻易做出来

#### 主要思路：先判断所有数是不是和其他数互质，当然0和1特判，再循环枚举每两个不互质的数组成的分数，当然不重复，所有的分数用结构体存，最后按大小排序，从小到大输出来就行了

### 代码注意事项：

#### 1.结构体为满足条件的分数的分子，分母，结构体开到160 * 160就行了

#### 2.t是不同分数的个数，flag判断互质，f数组是分数存分数，使每个分数只出现一次

#### 3.排序，如果分子相等，只需判断分母的大小，如果分子不等，判断分数大小

#### 4.主函数里先清空pd数组，再让0和1与所有数都互质，然后再判断其他数是不是互质

#### 5.枚举每个分数，如果这个分数没出现，结构体就记录，然后再按从小到大排序，最后输出就行了

## 话不多说，上代码
```
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
struct node
{
    int x,y;
}q[25921];
int n,t=0,flag;
bool pd[161][161];
bool f[20000001]={0};
bool cmp(const node &a,const node &b)
{
    if(a.x==b.x)
    {
        if(a.y<b.y) return 0;
        else return 1;
    }
    if(a.x!=b.x)
    {
        if(((float)a.x/a.y)<((float)b.x/b.y)) return 1;
        else return 0;
    }
}
int main()
{
    memset(pd,0,sizeof(pd));
    scanf("%d",&n);
    for(int i=0;i<=1;i++)
    {
    	for(int j=0;j<=n;j++)
    	{
    		pd[i][j]=pd[j][i]=1;
		}
	}
    for(int i=2;i<n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            flag=0;
            for(int q=2;q<=sqrt(i);q++)
            {
                if(i%q==0&&j%q==0)
                {
                    flag=1;
					break;
                }
            }
            if(flag) 
			{
			    pd[i][j]=pd[j][i]=0;
				continue;
			}
            if(!flag) 
			{
			    pd[i][j]=pd[j][i]=1;
				continue;
			}
        }
    }
    for(int i=0;i<=n;i++)
    {
    	for(int j=1;j<=n;j++)
    	{
    		if(pd[i][j]&&!f[(int)(((float)i/j)*100000)]&&(float)i/j<=1)
    		{
    			q[++t].x=i,q[t].y=j,f[(int)(((float)i/j)*100000)]=1;
			}
		}
	} 
    sort(q+1,q+t+1,cmp);
    for(int i=1;i<=t;i++)
      printf("%d/%d\n",q[i].x,q[i].y);
    return 0;
}
```

---

## 作者：robin2333 (赞：2)

前面很多题解都说过了，这题可以用分治的数学方法做出来，其实这个东西就是[法雷数列](https://baike.baidu.com/item/%E6%B3%95%E9%9B%B7%E6%95%B0%E5%88%97/3575595)。

它的形式是对于两个**最简真分数**$a/b<c/d$。设$m=a+c$,$n=b+d$。则有
1. $a/b<m/n<c/d$.
2. $m/n$是一个最简分数。即$gcd(m,n)=1$。

下面考虑对着两个性质进行证明。

性质1很好证明，做差即可。

$\frac{m}{n}-\frac{a}{b} = \frac{bc-ad}{b(b+d)}$

十字相乘即可得$ad<bc$，故而$a/b<m/n$，同理可证$m/n<c/d$.

对于性质2，我们考虑使用反证法证明。

假设$\frac{a+c}{b+d}$不是一个最简分数。

则必然可以构造$\frac{x(a_0+c_0)}{y(b_0+d_0)}$.

其中$x=\gcd(a,c)$，$y=\gcd(b,d)$.

且$\gcd(x,y)\neq1$

将式子展开，得到

$\frac{x*a_0+x*b_0}{y*c_0+y*d_0}$

其中$a=x*a0,c=y*c_0$

易得$\gcd(x*a_0,y*a_0) \neq 1$

但是$\gcd(a,b)=1$

矛盾，假设不成立，故性质2得证。

还是放一下代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;

void dfs(int a1,int a2,int b1,int b2){
	if(b2>n||b1>n)return;
	dfs(a1,a1+a2,b1,b1+b2);
	if(b1+b2<=n)cout<<a1+a2<<"/"<<b1+b2<<endl;
	dfs(a1+a2,a2,b1+b2,b2);
}

int main(){
	cin>>n;
	cout<<0<<"/"<<1<<endl;
	dfs(0,1,1,1);
	cout<<1<<"/"<<1<<endl;
}
```

---

## 作者：1433223o (赞：2)

# P1458题解
### 这道题是一道大模拟
 整体思路：用一个数组存分数，分数有分子分母和分数值，为了排序方便所以采用结构体。先输入n，然后先输出0/1，再逐个生成分数（如果最简分数不存）最后结构体排序，按照分数值从小到大排序，最后扫一遍输出，再输出1/1。
### 这道题思维难度较低，但是比较考验代码能力，还有很多细节上的东西需要注意。
# 上代码：
```cpp
# include <bits/stdc++.h>      //万能头文件
using namespace std;
const int NR = 40000;         //数组的常量，我们要定义一个struct数组,用来存分数分子分母和分数值
struct node
{
    int x, y;             //分子和分母（int）
    double z;            //分数值（double）                 
};
bool cmp(node x, node y)
{
    return x.z < y.z;
}  //cmp，排序用
node a[NR];             //用来存分数的数组
int gcd(int x, int y)       //求最大公约数的函数，后面判断最简分数用用
{
    if (y == 0) return x;
    return gcd(y, x % y);
}                  //最大公约数的递归求法，也可以用别的方法
int main()
{
    int n;              //定义n
    scanf("%d", &n);        //输入n
    printf("0/1\n");        //先把0/1输出，然后进行下面的操作
    int sz = 0;          //a的大小
    for (int i = 1; i <= n; i++)          //枚举分子
        for (int j = i + 1; j <= n; j++)      // 枚举分母ing
        {
            if (gcd(i, j) != 1) continue;    //如果不是最简，就不符合题目要求，跳过
            sz++;            //如果符合，说明多了一个最简分数，a的长度++
            a[sz].x = i;      //i就是分子
            a[sz].y = j;     //j就是分母   
            a[sz].z = 1.0 * i / j;    //分数值就是i/j
        }
    sort(a + 1, a + 1 + sz, cmp);     //按照分数值从小到大
    for (int i = 1; i <= sz; i++)     //然后依次输出就行了
        printf("%d/%d\n", a[i].x, a[i].y);
    printf("1/1\n");        //最后别忘了1/1
    return 0;             //完美结束
}
```
#### 细节：在c++里，整数除以整数它的结果还是整数，除出来是小数也 会被舍去小数部分，所以这里将其中的一个整数*1.0，这个整数就变成了小数类型了，然后再相除，结果就是小数了）

---

## 作者：Jezemy (赞：1)

看到这道题目，我就知道我PY大法又可以发挥优势了

首先呢，Python有个内置的类Fraction是处理分数的,具体使用方式如下

```python
from fractions import Fraction
# 初始化
print(Fraction(16,-10)) # -8/5
print(Fraction(123)) # 123
print(Fraction()) # 0
print(Fraction('3/7')) # 3/7
print(Fraction(2.5)) # 5/2

num = Fraction('10/15')
print(num) # 默认约分2/3
print(num.numerator) # 约分分子
print(num.denominator) # 约分分母
print(num*30) # 20
print(num**2) # 4/9

```

这个类就跟int一样，可以直接进行加减乘除模运算，另外Fraction类在初始化后就会自动约分。

接着就是按题意枚举所有分数出来，去重，然后排列，输出就可以了。

以下是代码

```python
from fractions import Fraction

N = int(input())
arr = set()
for i in range(N+1):
	for j in range(1,N+1):
		if i<=j:
			arr.add(Fraction(i,j))
List = list(arr)
List.sort()
for num in List:
	print("%d/%d"%(num.numerator,num.denominator))

```

---

## 作者：liaokq (赞：1)

# 貌似大伙儿都在用DFS

## 那我就发一个模拟+排序吧

~~其实是我不会DFS~~

我的想法是这样：先找出所有分母小于等于n的最简真分数，再将它们进行排序，最后将结果输出。

## 一种简单的分数的排序方法

设a/b和c/d两个分数，如果a×d大于c×b，那么a/b就大于c/d。

### 为什么呢？

我们都知道，分数的排序就是将两个分数进行通分，再比较大小。通分其实就是找分母的公倍数（不一定是最小），就可以以两个分母的积为公倍数，即a×d/b×d和c×b/d×b,这时比较分子的大小，就欧凯了。即a×d和c×b。

说完了，上AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int i,j,k=1,t,tt;
int f[40000][3];

bool gcd(int i,int j)//最大公约数，即判断这个分数是不是最简
{
	int x;
	for(x=min(i,j);x>=2;x--)
	{
		if(i%x==0&&j%x==0)return 0;
	}
	return 1;
}

int main()
{
	scanf("%d",&n);
	printf("0/1\n");//特判1
	for(i=1;i<=n;i++)
	{
		for(j=i+1;j<=n;j++)
		{
			if(gcd(i,j)==1)
			{
				f[k][1]=i;f[k][2]=j;k++;
                //k记录最简真分数的个数
			}
		}
	}
	for(i=1;i<k;i++)//选择排序
	{
		t=i;
		for(j=i+1;j<k;j++)
		{
			if(f[t][1]*f[j][2]>f[j][1]*f[t][2])t=j;
            //a×d与c×b
		}
		if(t!=i)
		{
			tt=f[t][1];f[t][1]=f[i][1];f[i][1]=tt;
			tt=f[t][2];f[t][2]=f[i][2];f[i][2]=tt;
            //交换
		}
	}
	for(i=1;i<k;i++)
	{
		printf("%d/%d\n",f[i][1],f[i][2]);
	}
	printf("1/1\n");//特判2
	return 0;
 } 
```


---

## 作者：tql_____ (赞：1)

 **给一个不用dfs的方法。**                                                     
## 思路： 


------------







### 1. 枚举分子，分母，判断是否互质，用结构体number保存      
注意，“0/1”和“1/1”的情况手动输出就可以了。分母从2开始枚举，分子从1开始枚举，循环时分子一定小于分母。判断互质用求最大公约数的方式，最大公约数是1，就是互质。（[辗转相除法](https://baike.baidu.com/item/%E8%BE%97%E9%99%A4%E6%B3%95/5124765?fr=aladdin)）


------------




### 2. sort函数排序，手写一个cmp函数。用交叉相乘比较分数大小。        
交叉相乘比较相对死算，更准确，也不会出现一些奇奇怪怪的错误，至于证明嘛。。。还是举例呗！                                                             举例万岁！    


------------

1/2>1/3 可以看成 1:2>1:3 外项乘外项，内项乘内项，3>2,因此，1/2>1/3。还是不懂？
1/2<3/4 可以看成 1:2<3:4 外项乘外项，内项乘内项，4<6,因此，1/2<3/4。这懂了吧？所以，a,b两个分数比较，如果a的分子乘b的分母大于a的分母乘b的分子，说明a大于b。
### 3. 输出结果。。。     



------------
#### 代码：
```c
#include<bits/stdc++.h>
using namespace std;
int n;
int cnt;
struct number//把分数写成结构体，简单易懂，好排序
{
    int fenzi;
    int fenmu;
} a[1000001];
bool cmp(number a,number b)//排序，经典写法，一定要会
{
    return (a.fenzi*b.fenmu)<(a.fenmu*b.fenzi);
}
bool huzhi(int x, int y)//辗转相除判互质
{
    if(x <=0 || y<=0 || x==y)   
    return false;
    else if(x==1 || y==1)     
    return true;
    else
    {
        while(1)
        {
            int t = x%y;
            if(t == 0)
                break;
            else
            {
                x = y;
                y = t;
            }
        }
        if( y > 1)   
            return false;
        else    
            return true;
    }
}

int main()
{
    cin>>n;
    printf("0/1\n");//特殊的，单独输


    for(int i=2; i<=n; i++)//枚举分母
    {
        for(int j=1; j<i; j++)//枚举分子
        {
            if(huzhi(i,j))
            {
                cnt++;
                a[cnt].fenmu=i;
                a[cnt].fenzi=j;//保存
            }
        }
    }

    
        
    sort(a+1,a+cnt+1,cmp);//排序

    for(int i=1; i<=cnt; i++)
        cout<<a[i].fenzi<<"/"<<a[i].fenmu<<endl;

    printf("1/1\n");//特殊的，单独输
    
    return 0;
}

```


---

## 作者：蒟蒻lxy (赞：1)

### 楼下的dalao们已经把思路讲的很明白了吧
但是代码就有些看不懂了
### 我来发一个注释代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
void erfen(int a,int b,int c,int d)//二分，从a/b到c/d 
{
	if(a>n || b>n || c>n || d>n)//如果有超界的
		return;
	//a+b在上一层输出 
	erfen(a,b,a+c,b+d);//进入下一层二分，从a/b到a+c/b+d
	//因为当a/b<c/d时，a/b<(a+c)/(b+d)<c/d 
	//所以这样二分
	if(b+d<=n)//如果下一个的分母没超界 
		cout << a+c <<'/'<< b+d << endl;//输出(a+c)/(b+d)
	erfen(a+c,b+d,c,d);//进入下一层二分，从a/b到a+c/b+d
	//（c/d在上一层输出） 
}
int main()
{
	cin >> n;
	cout <<"0/1\n";//把头先输出了 
	erfen(0,1,1,1);//从0/1到1/1
	cout <<"1/1\n";//输出最后一个 
	return 0;
}

```
希望能帮到你们

---

## 作者：ABCDXYZ (赞：1)

好吧，又有许久没写过题解了，久违来一发。

代码比较清晰，解释都在下面了（主要是结构体与排序的考察）

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int gcd(int x,int y){
    int t;
    while(y>0){
        t=y;
        y=x%y;
        x=t;
    }
    return x;//求最大公约数不解释 
}
struct node{
    double value;int x;int y;
}a[1000010];//value为分数值大小 
bool cmp(node a,node b){
    if(a.value>b.value)return false;
    return true;
}//bool型自定义sort排序 
int main (){
    int m,n,j,k,i;
    int cnt=0;
    scanf("%d",&n);
    printf("0/1");
    printf("\n");
    for(i=1;i<=n;i++){
        for(j=i-1;j>=1;j--){
            if(gcd(i,j)){
                cnt++;
                a[cnt].value=j*1.0/i;
                a[cnt].x=j;
                a[cnt].y=i;//分别存储分数值，分子，分母 
            }
        }
    }
    sort(a+1,a+cnt+1,cmp);
    for(i=1;i<=cnt;i++)
        cout<<a[i].x<<"/"<<a[i].y<<endl;
    printf("1/1");
}
```

---

## 作者：Skywalker_David (赞：1)

枚举+排序，（主要数据只有160）所以最简单的模拟即可AC


下面附上本人代码：




```cpp
**_var_**
**_n,a,b,i,j:longint;_**
**_fa,fb:array[1..100001] of longint;_**
**_f:array[1..100001] of extended;_**                       //注意一定是实形哦，因为牵扯到分数。
**_function gcd(x,y:longint):longint;_**                     //最大公约数，求互质的，没必要说了。。。。。。
**_begin_**
**_if x mod y=0 then exit(y)_**
**_else exit(gcd(y,x mod y));_**
**_end;_**
**_procedure qsort(l,r:longint);_**         //快排
**_var_**
**_i,j,x:longint;_**
**_t,mid:extended;_**
**_begin_**
**_i:=l;j:=r;mid:=f[(l+r) div 2];_**
**_repeat_**
**_while f[i]<mid do inc(i);_**
**_while f[j]>mid do dec(j);_**
**_if i<=j then begin_**
**_t:=f[i];f[i]:=f[j];f[j]:=t;_**
**_x:=fa[i];fa[i]:=fa[j];fa[j]:=x;_**            // 这两行在主程序里会提到，在快排的同时注意交换分子和分母。
**_x:=fb[i];fb[i]:=fb[j];fb[j]:=x;_**          //
**_inc(i);dec(j);_**
**_end;_**
**_until i>j;_**
**_if i<r then qsort(i,r);_**
**_if l<J then qsort(l,j);_**
**_end;_**
**_begin_**
**_readln(n);_**
**_i:=0;_**
**_writeln('0/1');_**
**_for b:=1 to n do begin_**                     //传说中的枚举。
**_for a:=1 to b do_**
**_if gcd(a,b)=1 then begin_**
**_inc(i);_**
**_fa[i]:=a;_**                   //
**_fb[i]:=b;_**                     //
**_f[i]:=fa[i]/fb[i];_**                 //记录分数值以及分子、分母。
**_end;_**
**_end;_**
**_qsort(1,i);_**
**_for j:=1 to i do_**
**_writeln(fa[j],'/',fb[j]);_**          //输出
**_end._**
```

---

## 作者：「QQ红包」 (赞：1)

题解by：redbag

AC记录：http://www.luogu.org/record/show?rid=776906

原文地址：http://redbag.duapp.com/?p=1132

我的博客：http://redbag.duapp.com/

欢迎来踩

枚举每一种方案，去掉未化简的，单独输出0/1，然后对其他的进行排序，用sort排序。见代码。

/\*
ID: ylx14271

PROG: frac1

LANG: C++

\*/
```cpp
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
struct ha
{
    int x,y;
}a[25700];
int n,i,j,p;
int gcd(int aa,int bb)
{
    if (aa%bb==0) return bb;
    return gcd(bb,aa%bb);
}
int cmp(ha aa,ha bb)//排序，先按照行，行相同的情况下按照列 
{//ad-bc,aa.x bb.y aa.y bb.x 
    if ((aa.x*bb.y-aa.y*bb.x)>0)//aa比bb大
    //通分后是(ad-bc)/bd,因为分母一定>0所以只要判断分子了
        return 0; 
        else return 1;
}
int main()
{
    freopen("frac1.in","r",stdin);
    freopen("frac1.out","w",stdout); 
    scanf("%d",&n);
    printf("0/1\n");
    for (i=1;i<=n;i++)
        for (j=i;j<=n;j++)
        if (gcd(i,j)==1)//互质
        {
            p++; 
            a[p].x=i;a[p].y=j; //存起来 
        } 
    sort(a+1,a+p+1,cmp);//排序
    for (i=1;i<=p;i++)
    printf("%d/%d\n",a[i].x,a[i].y);//输出
    return 0;
}
```

---

## 作者：hfuuwh (赞：1)

         
```cpp
#include"stdio.h"
int x[20000],y[20000];
int fun(int a,int b)
{
    return b==0?a:fun(b,a%b);
}
int main()
{
    int n,i,j,k=0,t1,t2;
    double l1,l2;
    scanf("%d",&n);
    printf("0/1\n");
    for(i=n;i>0;i--)
     for(j=1;j<=i;j++)
     {
         if(fun(i,j)==1)//找到这些分数 
         {
             x[k]=i;
             y[k]=j; 
             k++;
         }
     }
    for(i=0;i<k-1;i++)//对分数进行排序 
       for(j=i+1;j<k;j++)
       {
             l1=y[i]/(1.0*x[i]);
             l2=1.0*y[j]/x[j];
             if(l1>l2)
             {
                 t1=x[i];  t2=y[i];
                 x[i]=x[j];  y[i]=y[j];
                 x[j]=t1;  y[j]=t2;
             }
       }
       for(i=0;i<k;i++)//输出结果 
         printf("%d/%d\n",y[i],x[i]);
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

去重用什么，当然选 `set`。

但是像这题一样，如何让分数去重呢？

自己重载一个$<$运算符就可以了。

注：在`set`中使用自定义结构体必须重载$<$运算符。

又因`set`自身有序，直接用迭代器输出即可。

其实我的分数比较该写个eps的...
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include <utility>
#include <functional>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define dec(i,a,b) for(int i=(a);i>=(b);--i)
#define endll putchar('\n');
#define RI register int 
#define gc() getchar()
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
inline ll read(){
    char ch=getchar();ll x=0,f=1;
    while(ch<'0'||ch >'9') {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while('0'<=ch&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline void print(ll k){
    if(k<0) k=-k,putchar('-');
    if(k>9) print(k/10);
    putchar(k%10+48);
}
inline void println(ll k){
    print(k);
    endll;
}
inline void printsp(ll p){
    print(p);
    putchar(' ');
}
inline void printspfirst(ll p){
    putchar(' ');
    print(p);
}
struct frac{
    int upp,down;
    frac(){}
    frac(int _upp,int _down){upp=_upp;down=_down;}
    //构造函数
};
inline void printfrac(frac a){
    print(a.upp);
    putchar('/');
    println(a.down);
} //输出比较方便
bool operator <(const frac &a,const frac &b){
    return (double)a.upp/a.down<(double)b.upp/b.down;
}//重载的运算符
int n;
set<frac> se;
int main(){
    n=read();
    rep(i,1,n)
        rep(j,1,i)
            se.insert(frac(j,i));
    printf("0/1\n"); //特殊输出
    for(set<frac>::iterator it=se.begin();it!=se.end();++it){
        frac tmp=*it;
        printfrac(tmp);
    }
    return 0;
}
```

---

## 作者：enjoycolin (赞：1)

结构体封装一下会很好看

```cpp
/*
ID: hnpengj1
PROG: castle
LANG: C++11
*/
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

struct Fraction
{
    int n,    //numerator
        d;    //denominator

    bool operator < (const Fraction & tmp)
    {
        return n * tmp.d < tmp.n * d;
    }
    
    short print()
    {
        cout << n << '/' << d;
        return 0;
    }
};

bool sort_cmp(Fraction &a, Fraction &b)
{
    return a < b;
}

int gcd(int x, int y)
{
    if (x < y)
        swap(x, y);
    int tmp = x % y;
    if (tmp == 0)
        return y;
    else
        return gcd(y, tmp);
}

int main()
{
    //freopen("crypt1.in", "r", stdin);
    //freopen("crypt1.out", "w", stdout);

    int n;
    vector<Fraction> res;
    res.push_back({ 0, 1 });
    cin >> n;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            if (gcd(j, i) == 1)
            {
                res.push_back({ j, i });
            }
        }
    }
    res.push_back({ 1, 1 });

    sort(&res[0] + 0, &res[0] + res.size(), sort_cmp);

    for (int i = 0; i < res.size(); i++)
    {
        res[i].print();
        cout << endl;
    }

    //fclose(stdin);
    //fclose(stdout);

    return 0;
}


/*
SAMPLE INPUT
5

SAMPLE OUTPUT
0/1
1/5
1/4
1/3
2/5
1/2
3/5
2/3
3/4
4/5
1/1

*/
```

---

## 作者：袁宇轩 (赞：0)

前往[题目](https://www.luogu.com.cn/problem/P1458)

看题解中都是用除法算出商，在进行比较，个人认为肯定存在精度误差，要是真有卡精度的数据，那么就...

那我怎么做呢？

其实很简单。

a/b ? c/d
=a:b ? c:d=ad ? bc

所以我们只需要比较前一个数的分子和后一个数的分母的乘积与后一个数的分子和前一个数的分母的乘积的大小。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	int x,y;
}a[23456];
bool cmp(node A,node B)
{
	if (A.x*B.y!=A.y*B.x) return A.x*B.y<A.y*B.x;
	else return A.x<B.x;//如果两个乘积相等，那么分子小的排前，因为分子最小的一点是最简的 
}
int main()
{
	cin>>n;
	int cnt=0;
	a[++cnt].x=0;
	a[cnt].y=1;
	a[++cnt].x=1;
	a[cnt].y=1;//头和尾先处理了 
	for (int i=1;i<=n;i++)
	  for (int j=i+1;j<=n;j++)
	    a[++cnt].x=i,a[cnt].y=j;//枚举所有可能的分数，因为分数的<=1，所有分母>=分子 
	sort(a+1,a+cnt+1,cmp);
	for (int i=1;i<=cnt;i++)
	{
	  if (i>1 && a[i].x*a[i-1].y==a[i].y*a[i-1].x) continue;//相等是就不用输出了 
	  cout<<a[i].x<<'/'<<a[i].y<<endl;
	}
	return 0;
}
```


---

## 作者：wubaiting2020 (赞：0)

清新易懂的爆搜……  
思路：  
1.枚举分子分母判断是否互质  
2.按大小排序  
于是这道题就氵过去了   
代码：
```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
int n,cnt;
struct node{int fm,fz;double num;}a[40005];
bool cmp(node x,node y){return x.num<y.num;}//按大小排序 
int Gcd(int x,int y){return y?Gcd(y,x%y):x;}
int pd(int x,int y)
{
	if(Gcd(x,y)==1)return 1;//如果互质最大公约数为1 
	return 0;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=0;j<=i;j++)
			if(pd(i,j))
			{
				a[++cnt].fm=i;
				a[cnt].fz=j;
				a[cnt].num=(double)j/i;//记录满足条件的分数 
			}
	sort(a+1,a+cnt+1,cmp);//从小到大排序 
	for(int i=1;i<=cnt;i++)
	{
		printf("%d/%d\n",a[i].fz,a[i].fm);
	}
	return 0;
}


```
QAQ

---

## 作者：jinhangjie2006 (赞：0)

强模拟，列举每一个合格的分数，然后按分数值从小到大排序，输出
```cpp
var
  i,j,c,d,e,b,n,m:longint;
  a:array[1..100000] of string;
  s,s1,t:string;
  tt:double;
  x:array[1..100000] of double;
 function zx(x,y:longint):longint;//算最大公因数的子程序
   begin
    if x mod y<>0 then exit(zx(y,x mod y)) else exit(y);
  end;
begin
  writeln('0/1');
  readln(n);
for i:=1 to n do
  for j:=1 to n do
    begin
     if i<=j then//一定是<=1的分数
     if zx(i,j)=1 then//最大公因数是1
        begin
         inc(e);
         x[e]:=i/j;//把这个分数的值记录下来
         str(i,s);//数字转成字符
         str(j,s1);//数字转成字符
       a[e]:=s+'/'+s1;//这个分数记下来
  end;
end;
for i:=1 to e-1 do
  for j:=i+1 to e do
    if x[i]>x[j] then begin t:=a[i];a[i]:=a[j];a[j]:=t;//分数的大小排个序
                            tt:=x[i];x[i]:=x[j];x[j]:=tt;//分数本身也要排序
                               end;
  for i:=1 to e do
    writeln(a[i]);//小到大输出这些分数
  end.

```

---

## 作者：御·Dragon (赞：0)

## 其实就是使用判断互质、分数快排的集合，很简单。枚举爆搜就可以了，搜完合法保存，最后快排 

```

#include<bits/stdc++.h>//万能头人人必备
using namespace std;

const int MAXN = 100000;

bool pd(int x,int y){//bool型判断是否互质 
	//先进行特判 
	if(x == 1 && y == 1)return 1;//特判1与1 
	if(x == 0 && y != 1)return 0;//0不行 
	if(x >= y)return 0;//如果为假分数也退出 
	for(int i = 2;i <= min(x,y); i++){//开始判断 
		if(x % i == 0 && y % i == 0)return false;//只要有公因数且不为1则退出 
	}
	return true;//合法 
}

int n;
int f[MAXN][5];//记录每个分数的分母和分子 
int a = 1;//记录目前有几个分数 

void px(){//分数快排 
	for(int i = 1;i <= a; i++)
		for(int j = i + 1;j <= a; j++){//枚举分母与分子
			if((f[i][2] * f[j][1]) < (f[i][1] * f[j][2])){//比其小就冒泡交换 
				int x = f[i][1];//交换分子 
				f[i][1] = f[j][1];
				f[j][1] = x;
				x = f[i][2];//交换分母 
				f[i][2] = f[j][2];
				f[j][2] = x;
			}
		}
}

int main(){
	cin>>n;
	for(int j = 1;j <= n; j++)
		for(int i = 0;i <= n; i++){//枚举分母和分子 
			if(pd(i,j)){//如果合法 
				f[a][1] = i;//记录分子 
				f[a][2] = j;//记录分母 
				a++;//个数加1 
			}
		}
	px();//这里是分数快排 
	for(int i = 1;i < a; i++){//依次输出 
		cout<<f[i][1]<<"/"<<f[i][2]<<endl;//输出分子分母 
	}
	return 0;
}

```


---

## 作者：dengjun (赞：0)

我这个程序使用平常的方法做的。

1. 首先，最重要的是判断互质：
```cpp
long aaa(long a,long b)  //a是分子，b是分母
{
    for(int i=2;i<=200;i++)
        if(a%i==0&&b%i==0)
            return 0;         //不互质
    return 1;               //互质
}
```
2. 搜索0~1的所有满足1<=b<=N,0<=a/b<=1的分数
```cpp

    for(int i=1;i<=n;i++)
        for(int j=n;j>=1;j--)
            if(i!=j&&i<j)
            {
                o++;
                b[o]=(i*1.00000000)/(j*1.00000000)*1.00000000;    //排序用
                x[o]=i;
                y[o]=j;
            }          //暴力搜索
```
3. 从小到大排序(我用了冒泡排序,也可以用结构体快排)。
```cpp
    for(int i=1;i<=o-1;i++)
        for(int j=i+1;j<=o;j++)
        {
            if(b[i]>b[j])
            {
                t=b[i];
                b[i]=b[j];
                b[j]=t;
                t1=x[i];
                x[i]=x[j];
                x[j]=t1;
                t1=y[i];
                y[i]=y[j];
                y[j]=t1;
            }
        }           //冒泡排序
```
4. 输出
```cpp

    for(int i=1;i<=o;i++)
        if(aaa(x[i],y[i])==1)
            cout<<x[i]<<"/"<<y[i]<<endl;    //输出
```
```cpp
#include<iostream>
using namespace std;
long n,o,x[1000001],y[1000001],t1;
double t,b[1000001];
long aaa(long a,long b)      //判断互质
{
    for(int i=2;i<=200;i++)
        if(a%i==0&&b%i==0)
            return 0;
    return 1;
}
int main()
{
    cin>>n;
    cout<<"0/1"<<endl;
    for(int i=1;i<=n;i++)
        for(int j=n;j>=1;j--)
            if(i!=j&&i<j)
            {
                o++;
                b[o]=(i*1.00000000)/(j*1.00000000)*1.00000000;
                x[o]=i;
                y[o]=j;
            }          //暴力搜索
    for(int i=1;i<=o-1;i++)
        for(int j=i+1;j<=o;j++)
        {
            if(b[i]>b[j])
            {
                t=b[i];
                b[i]=b[j];
                b[j]=t;
                t1=x[i];
                x[i]=x[j];
                x[j]=t1;
                t1=y[i];
                y[i]=y[j];
                y[j]=t1;
            }
        }           //冒泡排序
    for(int i=1;i<=o;i++)
        if(aaa(x[i],y[i])==1)
            cout<<x[i]<<"/"<<y[i]<<endl;    //输出
    cout<<"1/1"<<endl;
    return 0;
}
```

---

## 作者：Bzy_temp (赞：0)

###简单的题目，直接有点数论知识19行直接出




```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//流操作命名空间
//node类型，记录分子分母及其浮点值
struct node{
    double value;
    int up,down;
};
bool cmp(node a,node b){return a.value<b.value;}//sort比较浮点值大小
int gys(int a,int b){return a%b==0?b:gys(b,a%b);}//判断最大公因数
node all[100000];int now;//变量定义，不解释
int main(){
    int a;cin>>a;cout<<"0/1\n";//输入，输出特殊情况
    for(int i=1;i<=a;i++)for(int j=1;j<=i-1;j++)if(gys(i,j)==1){all[now].up=j;all[now].down=i;all[now].value=j*1.0/i;now++;}//暴力判断是否合法
    sort(all,all+now,cmp);//排序
    for(int i=0;i<=now-1;i++)cout<<all[i].up<<"/"<<all[i].down<<"\n";cout<<"1/1";//输出//特殊情况
}
```

---

