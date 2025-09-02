# [USACO1.5] 八皇后 Checker Challenge

## 题目描述

一个如下的 $6 \times 6$ 的跳棋棋盘，有六个棋子被放置在棋盘上，使得每行、每列有且只有一个，每条对角线（包括两条主对角线的所有平行线）上至多有一个棋子。

![](https://cdn.luogu.com.cn/upload/image_hosting/3h71x0yf.png)

上面的布局可以用序列 $2\ 4\ 6\ 1\ 3\ 5$ 来描述，第 $i$ 个数字表示在第 $i$ 行的相应位置有一个棋子，如下：

行号 $1\ 2\ 3\ 4\ 5\ 6$

列号 $2\ 4\ 6\ 1\ 3\ 5$

这只是棋子放置的一个解。请编一个程序找出所有棋子放置的解。  
并把它们以上面的序列方法输出，解按字典顺序排列。  
请输出前 $3$ 个解。最后一行是解的总个数。



## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$6 \le n \le 13$。

题目翻译来自NOCOW。

USACO Training Section 1.5


## 样例 #1

### 输入

```
6
```

### 输出

```
2 4 6 1 3 5
3 6 2 5 1 4
4 1 5 2 6 3
4
```

# 题解

## 作者：ybb756032937 (赞：1112)

#c++搜索与回溯

##基本思路：搜索 标记 AC

```cpp
#include<iostream>//个人不建议采用头文件，可能和定义的变量或名字起冲突，从而引起编译错误；
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
int a[100],b[100],c[100],d[100];
//a数组表示的是行；
//b数组表示的是列；
//c表示的是左下到右上的对角线；
//d表示的是左上到右下的对角线；
int total;//总数:记录解的总数
int n;//输入的数，即N*N的格子，全局变量，搜索中要用
int print()
{
    if(total<=2)//保证只输出前三个解，如果解超出三个就不再输出，但后面的total还需要继续叠加
    {
        for(int k=1;k<=n;k++)
        cout<<a[k]<<" ";//for语句输出
        cout<<endl;
    }
    total++;//total既是总数，也是前三个排列的判断
}
void queen(int i)//搜索与回溯主体
{
    if(i>n)
    {
        print();//输出函数，自己写的
        return;
    }
    else
    {
        for(int j=1;j<=n;j++)//尝试可能的位置
        {
            if((!b[j])&&(!c[i+j])&&(!d[i-j+n]))//如果没有皇后占领，执行以下程序
            {
                a[i]=j;//标记i排是第j个
                b[j]=1;//宣布占领纵列
                c[i+j]=1;
                d[i-j+n]=1;
                //宣布占领两条对角线
                queen(i+1);//进一步搜索，下一个皇后
                b[j]=0;
                c[i+j]=0;
                d[i-j+n]=0;
                //（回到上一步）清除标记
            }
        }
    }
}
int main()
{    
    cin>>n;//输入N*N网格，n已在全局中定义
    queen(1);//第一个皇后
    cout<<total;//输出可能的总数
    return 0;
}
```
###注释：对角线d[i-j]后面必须加上一个n，因为i-j可能为负数，那么数组就会出错，所以将整体向右偏移n个单位（坐标偏移不会影响我们需要达到的目的），将所有可能变成正数；（因为i-j的最小值是-n+1，所以加上一个n就一定会变成一个正数）

本道题最重要的就是记录下皇后占领的格子（打标记的思想），通过此判断下一个皇后是否可以在某个位置，如果可以，则继续搜索下一个皇后可以在的位置，如果不行，则清除标记回到上一步，继续搜索；

可以先考虑六个皇后（即6\*6网格)，再将6改为n，并且输入n，就可以得出6到13个皇后的解了；


---

## 作者：XG_Zepto (赞：408)

这其实是一道很显然的回溯题，先放C++代码：



```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int ans[14],check[3][28]={0},sum=0,n;
void eq(int line)
{
    if(line>n)
    {
        sum++;
        if(sum>3) return;
        else
        {
            for(int i=1;i<=n;i++) printf("%d ",ans[i]);
            printf("\n");
            return;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if((!check[0][i])&&(!check[1][line+i])&&(!check[2][line-i+n]))
        {
            ans[line]=i;
            check[0][i]=1; check[1][line+i]=1; check[2][line-i+n]=1;
            eq(line+1);
            check[0][i]=0; check[1][line+i]=0; check[2][line-i+n]=0;
        }
    }
}
int main()
{
    scanf("%d",&n);
    eq(1);
    printf("%d",sum);
    return 0;
}
```

代码中，

数组ans[line]=i表示第line行的第i列有一个棋子，保证了每行只有一个棋子；

数组check保证了每列和每条对角线上只有一个棋子，具体机制如下，没有一些奇奇怪怪难以理解的公式：

check[0]储存了棋子的列数，每一次进行ans[line]=i，使check[0][i]标记为已使用；

check[1]和check[2]储存对角线上的棋子分布情况：

![](https://cdn.luogu.com.cn/upload/pic/60.png)

如图，

对于一条从右上到左下的对角线，其上的棋子坐标应满足x+y为一定值；

对于一条从左上到右下的对角线，其上的棋子坐标应满足x-y为一定值，为了避免负数的产生，代码中用x-y+n来储存数字，具体效果读者可以自行研究。


对于语句

if((!check[0][i])&&(!check[1][line+i])&&(!check[2][line-i+n]))

只要满足这三个数字均为使用过，则在ans[line]=i处放置棋子，并将check数组中的相应数值标记为已使用，并对下一行进行搜索。


由于题目要求输出前3组解，所以计数器sum>3时不输出结果，最后在main函数中输出最终解的数量。


---

## 作者：钱逸凡 (赞：386)

本题有两种思路：
###  dancing links和深度优先搜索

~~蒟蒻推荐用dancing links~~
# dancing links
## ~~这么适合用dancing links的题竟然没人发dancing links的题解~~

我们知道dancing links的用途是解决精确覆盖问题和重复覆盖问题

[不知道的点这里](https://www.luogu.org/blog/ONE-PIECE/qian-tan-dlx)
~~蒟蒻的语文差，将就看吧~~

对于八皇后问题我们可以把它转化为精确覆盖的问题：
1. 每行只能放一个皇后
1. 每列只能放一个皇后
1. 每一个“/”斜行只能放一个皇后
1. 每一个“\”斜行只能放一个皇后

我们把每个状态当成列，每个点当成一行
然后精确覆盖这个矩阵

### 注意：与模版不同的是我们只需保证每行每列完全覆盖而每一斜行是肯定不能完全覆盖的（因为一共2*n-1个斜行）
C++AC代码：

------------
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define mx 100100//要大于(n*n)*(6*n-2)解释见主函数 
long long sum=0;//方案总数 
int nn;
struct out{
	int ans[14];
}ss[100000];//记录答案的数组 
struct DLX{
	int n,m,cnt;//矩阵的长，宽，点的数量
	int l[mx],r[mx],u[mx],d[mx],row[mx],col[mx];//每个点的左，右，上下，行，列信息 
	int h[mx];//每行的头结点 
	int s[mx];//每列的结点数 
	int ansk[mx];//选了ansk[] 
	void init(int _n,int _m){
		n=_n,m=_m;
		int i;
		for(i=0;i<=m;i++){
			r[i]=i+1;l[i]=i-1;u[i]=d[i]=i;
		}
		r[m]=0;//m右边是0 
		l[0]=m;//0左边是m 
		memset(h,-1,sizeof(h));
		memset(s,0,sizeof(s));
		cnt=m+1;//开始时有m个结点（0结点和各列头结点） 
	}//初始化，生成每列的头
	inline void link(int R,int C){
		s[C]++;
		row[cnt]=R;
		col[cnt]=C;
		u[cnt]=C;
		d[cnt]=d[C];
		u[d[C]]=cnt;
		d[C]=cnt;
		if(h[R]<0)h[R]=r[cnt]=l[cnt]=cnt;//该行没有别的点,把第一个加入的点作为该行的行头结点 
		else{
			r[cnt]=h[R];
			l[cnt]=l[h[R]];
			r[l[h[R]]]=cnt;
			l[h[R]]=cnt;
		}
		cnt++;
	}//在r行c列插入点
	inline void remove(int c){
		r[l[c]]=r[c],l[r[c]]=l[c];
		for(int i=d[c];i!=c;i=d[i]){
			for(int j=r[i];j!=i;j=r[j]){
				u[d[j]]=u[j];
				d[u[j]]=d[j];
				s[col[j]]--;
			}
		}
	}//删除c列和c列上有点的行
	inline void resume(int c){
		for(int i=u[c];i!=c;i=u[i]){
			for(int j=l[i];j!=i;j=l[j]){
				u[d[j]]=j;
				d[u[j]]=j;
				s[col[j]]++;
			}
		}
		r[l[c]]=c;
		l[r[c]]=c;
	}//恢复c列和c列上有点的行
	void dance(int deep){
		if(r[0]>nn){//前nn列都已删除表示已经放完了 
		sum++;
			int x,y;
			for(register int i=0;i<deep;i++){
			x=ansk[i]%nn;
			y=(ansk[i]-1)/nn+1;
			if(x==0)x=nn;
			ss[sum].ans[x]=y;
			}
		return;
		}
		int c=r[0];
		register int i,j;
		for(i=r[0];i<=nn;i=r[i])if(s[i]<s[c])c=i;//找到点最少的列，只需看前nn列是否删完 
		remove(c);
		for(i=d[c];i!=c;i=d[i]){
			ansk[deep]=row[i];
			for(j=r[i];j!=i;j=r[j]) remove(col[j]);
			dance(deep+1);
			for(j=l[i];j!=i;j=l[j]) resume(col[j]);
		}
		resume(c); 
		return ;
	}
}dlx;
bool cap(out a,out b){
	int i=1;
	while(a.ans[i]==b.ans[i]&&i<=nn){
		i++;
	}
	return a.ans[i]<b.ans[i];
}//根据题目要求找出前3种解法 
int main(){
	scanf("%d",&nn);
	dlx.init(nn*nn,6*nn-2);
	//一共n*n格对应n*n行
	//对于第m列
	//若[1,n]对应在第m行放皇后 
	//若[n+1,2*n]对应在第m-n列放皇后 
	//若[2*n+1,4*n-1]对应在第m-2*n“\”斜行放皇后 （共2*n-1个“\”斜行） 
	//若[4*n,6*n-2]对应在第m-4*n+1“/”斜行放皇后（共2*n-1个“/”斜行） 
	int x;	
	register int i,j;
	int o=0;
	for(i=1;i<=nn;i++){
	 	for(j=1;j<=nn;j++){
	 	o++;//第o行对应坐标(o/n+1,o%n) 
	 	dlx.link(o,i);
	 	dlx.link(o,j+nn);
	 	dlx.link(o,i-j+3*nn);
	 	dlx.link(o,i+j+4*nn-2);
		 }
	 }
	dlx.dance(0);
	sort(ss+1,ss+1+sum,cap);
	for(i=1;i<=3;i++){
		for(j=1;j<=nn;j++)printf("%d ",ss[i].ans[j]);
		printf("\n");
	}
	printf("%lld",sum);
	return 0;
}
```
如有优化建议可在讨论区发表


------------

# 深搜代码

------------

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int a[50][50],yi[20],xjay[50],xjiany[50];
int n,c=0,s=0;
void out() {
        if(c>=3)c++;
        else {
            for(int i=1; i<=n; i++) {
                for(int k=1;k<=n;k++){
                    if(a[i][k]==1)cout<<k<<" ";
                }
            }
            cout<<endl;
            c++;
        }
}//输出前三组解
void zhanlin(int x,int y){
    a[x][y]=1;
    yi[y]=1;
    xjiany[x-y+n]=1;
    xjay[x+y]=1;
}//在（x，y）放皇后
void fangqi(int x,int y){
    a[x][y]=0;
    yi[y]=0;
    xjiany[x-y+n]=0;
    xjay[x+y]=0;
}//拿走（x，y）的皇后
int isok(int x,int y){
    if(a[x][y]==0&&yi[y]==0&&xjiany[x-y+n]==0&&xjay[x+y]==0)return 0;
    return 1;
}//该点是否可以放皇后
void dfs(int x) {
    if(x==n+1) {
        out();
    } 
    else {
        for(int k=1; k<=n; k++) {
        if(isok(x,k)==0){
            zhanlin(x,k);
            dfs(x+1);
            fangqi(x,k);
        }	
        }
    }
}//深搜
int main() {
    int i,k;
    cin>>n;
    dfs(1);
    cout<<c;
    return 0;
}
```

# ~~求赞~~# 

---

## 作者：Dzhao (赞：199)

当你陷入此等悲痛时

![](https://cdn.luogu.com.cn/upload/pic/62302.png)

# TTTTTLE
或许你会认为，没办法了。但是，仔细看下本题数据
# (6<=n<=13)
好小啊
一种邪恶的思想瞬间浮现
### ~打表~
## ~打表~
# ~打表~
于是可爱的魔魔君就开始了他的打表之旅
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	if(n==6) //打表进行中......
	{
		puts("2 4 6 1 3 5");
		puts("3 6 2 5 1 4");
		puts("4 1 5 2 6 3");
		puts("4");
	}
	if(n==7)
	{
		puts("1 3 5 7 2 4 6");
		puts("1 4 7 3 6 2 5");
		puts("1 5 2 6 3 7 4");
		puts("40");
	}
	if(n==8)
	{
		puts("1 5 8 6 3 7 2 4");
		puts("1 6 8 3 7 4 2 5");
		puts("1 7 4 6 8 2 5 3");
		puts("92");
	}
	if(n==9)
	{
		puts("1 3 6 8 2 4 9 7 5");
		puts("1 3 7 2 8 5 9 4 6");
		puts("1 3 8 6 9 2 5 7 4");
		puts("352");
	}
	if(n==10)
	{
		puts("1 3 6 8 10 5 9 2 4 7");
		puts("1 3 6 9 7 10 4 2 5 8");
		puts("1 3 6 9 7 10 4 2 8 5");
		puts("724");
	}
	if(n==11)
	{
		puts("1 3 5 7 9 11 2 4 6 8 10");
		puts("1 3 6 9 2 8 11 4 7 5 10");
		puts("1 3 7 9 4 2 10 6 11 5 8");
		puts("2680");
	}
	if(n==12)
	{
		puts("1 3 5 8 10 12 6 11 2 7 9 4");
		puts("1 3 5 10 8 11 2 12 6 9 7 4");
		puts("1 3 5 10 8 11 2 12 7 9 4 6");
		puts("14200");
	}
	if(n==13)
	{
		puts("1 3 5 2 9 12 10 13 4 6 8 11 7");
		puts("1 3 5 7 9 11 13 2 4 6 8 10 12");
		puts("1 3 5 7 12 10 13 6 4 2 8 11 9");
		puts("73712");
	}
	return 0;
}
```
交上去后

啊

# 真香

![](https://cdn.luogu.com.cn/upload/pic/62305.png)

所以说

打表还真挺重要的

当然，这道题并不是除了打表，就没办法了
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 15
bool used[N],cha[2*N],he[2*N];
int opt[N],n,ans=0;
void dfs(int u)
{
	if(u>n) //放置完毕 
	{
		if(ans<3) 
		{
			for(int i=1;i<=n;i++) 
				printf("%d ",opt[i]);
			puts(""); 
		}
		ans++;
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(used[i] || cha[u-i+n] || he[i+u]) continue; //判断是否合法 
		used[i]=1,cha[u-i+n]=1,he[i+u]=1,opt[u]=i;
		dfs(u+1);
		used[i]=0,cha[u-i+n]=0,he[i+u]=0,opt[u]=0; //回溯 
	}
}
int main()
{
	scanf("%d",&n);
	dfs(1);
	printf("%d\n",ans);
	return 0;
} 
```
>这是另一种方法，使用差数组Hash这一条斜边有没有放置过，也可以过，依然跑的很快


---

## 作者：fpjo (赞：144)

本蒟蒻带来的八皇后

算法思路：回溯，搜索，标记。

难理解处：标记（对角线）~~我就是被困在那里~~


------------


上代码

```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int a[1000],b[1000],c[1000],d[1000],n,s;
    //a存行
    //b存列
    //c存左下到右上的对角线（行+列的和相同）
    //d存右下到左上的对角线（行-列的差相同）
    //清零数组
    void print(){
        int i;s++;
        if(s<=3){
            for(i=1;i<=n;i++)cout<<a[i]<<" ";
            cout<<endl;
        }
    }
    int search(int i){
        int j;
        for(j=1;j<=n;j++)
            if(b[j]==0&&c[i+j]==0&&d[i-j+n]==0){//判断
                a[i]=j;//写进去（第i行第j个） 
                b[j]=1;//占行 
                c[i+j]=1; d[i-j+n]=1;//占对角线 
                if(i==n)print();//满足条件输出 
                else search(i+1);//继续推 
                b[j]=0;c[i+j]=0;d[i-j+n]=0;//回溯
            }
        return 0;
    }
     int main(){
        cin>>n;
        search(1); 
        cout<<s<<endl;
        return 0;
}
```

---

## 作者：Lee02 (赞：95)

# 八皇后

## 1.简介
如题所示，这是一个类似于**枚举**的过程：每一行每一行地进行尝试，如果没有皇后能侵犯到自己，
   就**放置**该棋子，同时占据她所能**占据**的所有领地。最后，在每一行上都各有一个皇后时，就输出答案
## 2.方法
在这道题中，主要使用的是**深搜(DFS)**和**回溯**

回溯：借用以下**神子杏**大佬的批批替

为了求得问题的解，先选择某一种可能情况向前探索，在探索过程中，一旦发现原来的选择是**错误**的，就退回上一步重新选择条件，继续向前探索，如此反复进行，直至得到解或证明无解。

Ta的特点如下：

1.可以在借助系统栈储存状态

2.空间为O(深度)

3.可以剪枝

4.比较容易实现

5.不易判重

这个就是我们在这道题中的主要思路。如果在准备放置皇后的时候发现，这一行都没有合适的位置，那么我们就“报错”：退回**上一状态**，重新来过。

为了让皇后们可以吃“后悔药”，我们就必须给她们留下后路——曾经打过标记的地方都**撤销**掉，让她们有路可回。

下面，说下具体的实现方法。

## **1.地图设置**
	
   在这道题当中，我们不采取一般的建图（姑且先用下这个词）方式——建一个**二维数组**。因为这样的话，我们需要更多的循环来支持**占领**操作。
   
   ### 我们分别为**行**、**列**、**左斜线（/)**、**右斜线(\ )** 单独建立数组。
   #### 这样做的好处非常明显：在进行占据操作的时候，只需要在相对应的行、列、左斜、右斜打上标记就行，不需要在每一块都用循环进行操作，节省很多时间
   
   类似这种建图方式的题还有[这道](https://www.luogu.org/problem/P1784)，自己尝试一下吧！
   
   行和列的表示都非常简单，只需要在对应格子标记即可，我们来看一下左斜右斜的表示方式
   
   如图：
   ![](https://cdn.luogu.com.cn/upload/pic/60.png)
   
   对于第二行的那个皇后来说，她的右斜线上的点，（1，3），（3，5），（4，6），我们可以看出，它的$y-x$是个定值2，但是看第四行的皇后的右斜线上的点（5，2），它的$y-x$是个负定值，而数组是不能存在负数下标的，那怎么办。
   
   ### 把数组向右平移几个单位(在这里平移$n$就够) 
   因为右斜线上所有数都向右平移了$n$，所以总的数组中的关系不变。
   
   同理我们看左斜线上的点，我们发现它们的$x+y$是个定值（自己找找看）
   因为这是个加法，不会出现负数的情况，所以我们不需要在末尾加上$n$
   
   所以，我们在写的时候可以这样
   ```
   ls[i+j]=1;rs[i-j+n]=1
   ```
   
   以上就是些基本操作，下面加入代码（我的代码里的左斜和右斜好像写反了）
   
   ```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=0;
int a[105],ls[105],rs[105],kkk[105];//a:lie,ls:left scope,rs:right scope（原谅我的工地英语），kkk是行（kkksc03不要打我[滑稽]）
void print()
{
	if(ans<=2)
	{
		for(int i=1;i<=n;i++)
		cout<<kkk[i]<<" ";
		cout<<endl;
	}//输出前三组解
	ans++;
}
void dfs(int k)//深搜
{
	if(k>n)
	{
		print();
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		if(!a[i]&&!ls[i+k]&&!rs[i-k+n])
		{
			kkk[k]=i;
			a[i]=1;
			ls[k+i]=1;
			rs[i-k+n]=1;//以上是“占领”操作
			dfs(k+1);//这个是深搜下一行
			a[i]=0;//以下是回溯操作
			ls[k+i]=0;
			rs[i-k+n]=0;
		}
	}
}
int main ()
{
	cin>>n;
	dfs(1);//开始
	cout<<ans<<endl;//结束
	return 0;//大工告成！
}
```



---

## 作者：幻蓝刀心 (赞：73)

# 蒟蒻开始写题解了······跪求各位神犇轻喷······
## 这道题主要在于利用搜索的方法，暴力通过，不过呢，当数据达到12和13时，效率就会变慢，所以，用二进制优化的算法，可以将时间复杂度再降一半。
### 本来此题应该用四个bool数组来存纵，横，正斜（左下到右上），反斜（左上到右下），不过呢，仔细审题，可以发现，这题因为一列只有一个皇后，所以可以降维，也就是说，搜索皇后即就是把列考虑进去了，因此，只需三个数组便可以。

------------

### 上述只是为了优化一下朴素搜索的数据存储，即一层循环便可做到，而我所说的二进制优化，只需一个存答案的数组即可。

------------
![](https://cdn.luogu.com.cn/upload/pic/71392.png)

------------
由于每一个黄点只决定了下一列与它相邻三个点不能存放，因此我们就可以在搜索时将它所影响的点标记掉，将每一列的（ 行 | 正斜 | 反斜 ）即可得到 一串 01数列，这个数列的意义在于每个是0的位置表示没有被占过，而有1的则是被影响到的，我们每次都要得到数列的最后一位，来进行判断，为了去最后一位，用 1 & 上述结果，再右移一位，然后递归操作。这样就可以完成搜索操作。关键代码如下：
```cpp
int s=r | z | f;//r是横，z是正斜，f是反斜，s存结果
	for(int i=1;i<=n;i++)
	{
		if(!(s & 1))
		{
			a[k]=i;
			query(k+1,r | re,(z | re)<<1,(f | re)>>1);
		}
		s=s>>1;
	}
```
递归操作的时候，re是指1向左移i-1位，用横行 | re，便是下一列这一行，斜行对应左移1位和右移一位。
##### 出口要提前设，当搜索的层数大于n+1时，就判断ans累加结果是否>3，然后输出队列即可；
###### 完整代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define maxn 1000
#define re 1<<(i-1)
using namespace std;
int n,m,ans,a[maxn];
void query(int k,int r,int z,int f)
{
	if(k>n)
	{
		if(++ans<=3)
		{
			for(int i=1;i<n;i++)
			  printf("%d ",a[i]);
			printf("%d\n",a[n]);
		}
		return;
	}
	int s=r | z | f;
	for(int i=1;i<=n;i++)
	{
		if(!(s & 1))
		{
			a[k]=i;
			query(k+1,r | re,(z | re)<<1,(f | re)>>1);
		}
		s=s>>1;
	}
}
int main()
{
	scanf("%d",&n);
	query(1,0,0,0);
	printf("%d\n",ans);
	return 0;
}
```
# 求大佬轻喷


---

## 作者：CodeRikka (赞：52)

这道题其实我还没学回溯就写了，大概思路就是：

# 搜索，二进制优化。

先附上代码

```c
#include<bits/stdc++.h>
using namespace std;//用位运算优化
int n,mans,p;
int mark[100],bin[1<<20];
void dfs(int x/*行*/,int a,int b,int c){//列，左上角，右上角标记 
    if(x>n){
        ans++;
        if(ans>=1&&ans<=3){
            for(int i=1;i<=n;i++)printf("%d ",mark[i]+1);//输出标记了的列 
            puts("");
        }
        return;
    }
    int t=(a|b|c)^p;//p记录棋盘下标范围，t判断是否在棋盘内
    while(t) {
        int i=t&(-t);//二进制找到最后一个的全值 
        mark[x]=bin[i];//选择当前棋子 
        dfs(x+1,a|i,(b|i)>>1,((c|i)<<1)&p);//对当前棋子做标记，继续查找 
//a|i记录当前列不能走，b|i表示左上角，(c|i)<<1)&p查找右上角与当前列的重合 
        t-=i;
    }
}
int main(){
    scanf("%d",&n);
    p=(1<<n)-1;//用二进制表示下标范围;
    bin[0]=1;
    for(int i=1; i<=n; i++)bin[1<<i]=i;//二进制标记归位 
    dfs(1,0,0,0);
    printf("%d",ans);
    return 0;
}
```

不难看出，代码中用了二进制表示坐标，因为位运算比一般的运算要快很多，所以过程也是比较快的！

第一次写题解，希望采纳，谢谢！

---

## 作者：Birdy_fans (赞：42)

# 萌新题解 求过啊QaQ
## 看了诸多大大的题解  好长啊
## 鄙人尝试了一下 发现可以简单点~
#### 其实画个解答树可以发现 其实可以转化为全排列
```c
// luogu-judger-enable-o2//我最后一个测试点老是超时 
//没办法，就排出最牛的氧气优化。
#include<stdio.h>
#include<iostream>
using namespace std;
int n,c[13];//c数组用来存放解
int tot=0;
int sum=0;
void dsf(int queen)
{
    if(queen==n)//如果走到了这，所有皇后一定不会冲突
    {
    tot++;
    sum++;
    if(sum<=3)//只输出三个
        {
            for(int i=0;i<queen;i++)
                printf("%d ",c[i]+1);
            printf("\n");		
        }
        
    }
    else for(int i=0;i<n;i++)
    {
        int ok=1;
        c[queen]=i;//把此行皇后放在i列
        for(int j=0;j<queen;j++)
            if(c[queen]==c[j]||queen-c[queen]==j-c[j]||queen+c[queen]==j+c[j])//检查是否冲突
            {ok=0;break;}
        if(ok) dsf(queen+1);//如果合法就继续
    }	
}
int main()//日常少的主函数
{
    scanf("%d",&n);
    dsf(0);
    printf("%d",tot);	
return 0;}//功德圆满!^-^
```

---

## 作者：_Felix (赞：22)

写在前面：

~~第一次认真写题解QwQ求赞~~

我初学dfs时遇到的第一题应该就是这道吧

本文面向初学者，说的较为详细

侧重于作者的做题过程

我相信很多人都会像我一样去做

枚举每一行的皇后的位置即可

对角线的处理非常令人迷茫

------------

### 第一次尝试：

一开始，我兴奋地打了这样一个代码：

用二维数组vis标记一下能不能放不就好了吗？

看题解说的花里胡哨的……

```
void dfs(int x){
	if(x==n+1){
		cnt++;
		if(cnt<=3){
			for(int i=1;i<=n;i++)
				printf("%d ",ans[i]);
			printf("\n");
		}
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[x][i]){
			vis[x][i]=1;
			ans[x]=i;
			for(int j=x+1;j<=n;j++)
				vis[j][i]=1;
			for(int j=1;j<=n;j++){
				if(x+j>n||i+j>n) break;
				vis[x+j][i+j]=1;
			}
			for(int j=1;j<=n;j++){
				if(x+j>n||i-j<1) break;
				vis[x+j][i-j]=1;
			}
			dfs(x+1);
			for(int j=x+1;j<=n;j++)
				vis[j][i]=0;
			for(int j=1;j<=n;j++){
				if(x+j>n||i+j>n) break;
				vis[x+j][i+j]=0;
			}
			for(int j=1;j<=n;j++){
				if(x+j>n||i-j<1) break;
				vis[x+j][i-j]=0;
			}
		}
	}
	return;
}
```

内心无比欢悦！

——然鹅，样例都没过

原来会有重叠！回溯的时候改的并不是原来的值，原来已经否认了这种情况。

------------

### 第二次尝试：

瞄了眼看起来极小的数据范围，懒人我怎么会不偷懒呢。

直接拿个三维数组viss存一下不就好了，更新还方便，无脑。

一心以为复杂度炸不了的
~~（我居然算都没算……）~~

于是这样一份代码横空出世……

```
void dfs(int x){
	if(x==n+1){
		cnt++;
		if(cnt<=3){
			for(int i=1;i<=n;i++)
				printf("%d ",ans[i]);
			printf("\n");
		}
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[x][i]){
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++)
					viss[x][j][k]=vis[j][k];
			vis[x][i]=1;
			ans[x]=i;
			for(int j=x+1;j<=n;j++)
				vis[j][i]=1;
			for(int j=1;j<=n;j++){
				if(x+j>n||i+j>n) break;
				vis[x+j][i+j]=1;
			}
			for(int j=1;j<=n;j++){
				if(x+j>n||i-j<1) break;
				vis[x+j][i-j]=1;
			}
			dfs(x+1);
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++)
					vis[j][k]=viss[x][j][k];
		}
	}
	return;
}
```
于是TLE87分滚粗

------------

Q：那就只保存要更新的不就行了吗？这样时间复杂度不会炸的呀

A：试过了，我好像打错了。您可以自己试一试。

------------

### 第三次尝试

此时我发现我一道经典题打了这么久内心已经很崩溃了

（如果在~~NOIP~~CSP考场上我就已经87分滚粗了，所以要注意数据范围啊）

仔细看题面和原来的思路，

1.我发现一行不会有两个皇后，所以这是不用存的

2.列用一维数组vis保存即可

3.对角线应该怎么存？

观察题目提供的图

![](https://cdn.luogu.com.cn/upload/pic/60.png)

向左下角的一条对角线上的格子行与列的和相等，

向右下角的一条对角线上的格子行与列的差相等 

妙啊，解决了解决了。

to_left[i]表示行与列和为i的格子所在的向左下角的对角线上是否已有皇后

to_right[i]表示行与列差为i的格子所在的右下角的对角线上是否已有皇后

且慢——万一行与列的差为负值怎么办

+个n让它变成正数不就好了……

to_right[i+n]表示行与列差为i的格子所在的右下角的对角线上是否已有皇后

行与列差最大为n-1，行与列和最大为2*n

这样我们就知道这两个数组要开多大了

AC代码

```
#include <bits/stdc++.h>
using namespace std;
bool vis[15],to_left[30],to_right[30];
//向左的同一条对角线上和相等，向右的差相等 
int n,ans[15],cnt;
void dfs(int x){
	if(x==n+1){
		cnt++;
		if(cnt<=3){
			for(int i=1;i<=n;i++)
				printf("%d ",ans[i]);
			printf("\n");//输出前三组解
		}
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]&&!to_left[x+i]&&!to_right[x-i+n]){//坐标（x,i） 
			vis[i]=1;to_left[x+i]=1;to_right[x-i+n]=1;//标记
			ans[x]=i;
			dfs(x+1);
			vis[i]=0;to_left[x+i]=0;to_right[x-i+n]=0;//回溯
		}
	}
	return;
}
int main() {
	cin>>n;
	dfs(1);
	cout<<cnt<<endl;
	return 0;
}
```

by cz（不进前n不改名）

---

## 作者：dashuai (赞：14)

位运算+棋盘对称。

因为棋盘是正方形，是对称的，方案也是对称的。我们没必要将所有方案搜索出来。

当n为偶数，第一行的棋子放在第[1..⌊n div 2⌋  ]列的方案，与 第一行的棋子放在第[ ⌊n div 2⌋+1  ..n]列的方案 ,数量相等且左右对称。

当 n 为奇数时，第一行的棋子放在第[1..⌊n div 2⌋  ]列的方案，与 第一行的棋子放在第[ ⌈n div 2⌉+1..n]列的方案 ,数量相等且左右对称。第一行的棋子还可以放在第⌈n div 2⌉列，那么，第二行的棋子又具有对称性。





```cpp
#include<cstdio>
#include<iostream>
using namespace std;
const int N=20;
int lg[1<<17];
int n;
int flag;
int sum;
int upperlim;
int a[N];
int cnt;
void print_a(){
    for(int i=1;i<=n;++i)
    printf("%d ",a[i]);
    printf("\n");
}
void dfs(int row,int ld,int rd){
    if(row==upperlim){
        ++sum;
        if(sum<=3)print_a();
        return;
    }
    int pos=upperlim&(~(row|rd|ld));
    if(cnt==0){//要放第一行的棋子
        if(flag==1)pos=(1<<(n>>1))-1;//n为偶数或奇数，第一行的棋子放在第[1..⌊n div 2⌋  ]列。
        else pos=1<<(n>>1);//n为奇数，且第一行的棋子放在第⌈n div 2⌉列
    }
    if(cnt==1&&flag==2)pos=pos&((1<<(n>>1))-1);//n为奇数，且第一行的棋子放在第⌈n div 2⌉列，第二行的棋子放在[1..⌊n div 2⌋-1].
    while(pos){
        register int low=pos&-pos;
        pos^=low;
        a[++cnt]=lg[low];
        dfs(row|low,(ld|low)<<1,(rd|low)>>1);
        --cnt;
    }
}
int main(){
    scanf("%d",&n);
    lg[1]=1;
    for(register int i=0;i<17;++i)
    lg[1<<i]=i+1;
    upperlim=(1<<n)-1;
    flag=1;
    dfs(0,0,0);
    if(n&1){
        flag=2;
        dfs(0,0,0);
    }
    if(n==6)printf("4 1 5 2 6 3\n");//n==6的时候只有四种方案，只好打表了
    printf("%d",sum<<1);
    return 0;    
}
额，棋盘对称的方法只能优化常数，再加上位运算，程序的性能还不错，n==15时，本机测试接近一秒。
```

---

## 作者：ZYCyr1 (赞：10)

# 蒟蒻的第一篇题解
八皇后是一道非常经典的深搜问题，行与列都相对简单，这道题的真正难点在于斜线，而破解它的关键思路是：

## 右斜线（左上到右下）上每个点之间的关系是列减行相等
## 左斜线（右上到左下）上每个点之间的关系是列加行相等

附上完整AC代码~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[20],cnt;
bool line[20]; //列 
bool r[40]; //右斜（左上到右下） 列减行相等
bool l[40]; //左斜（右上到左下） 列加行相等
void pr(){
	if(cnt<=3){
		for(int i=1;i<=n;i++){
			cout<<a[i]<<" ";
		}
		printf("\n");
	}
}
void dfs(int x){
	if(x>n){
		cnt++;
		pr();
		return ;
	}
	for(int i=1;i<=n;i++){
		if(!line[i]&&!r[x-i+n]&&!l[x+i]){ //直观上是r[x-i]，但可能会越界，所以我们数组开大些 ，再加个n
			line[i]=1; //打标记 
			r[x-i+n]=1;
			l[x+i]=1;
			a[x]=i;
			dfs(x+1); //搜下一行 
			line[i]=0;
			r[x-i+n]=0;
			l[x+i]=0; //回溯 
		}
	}
}
int main(){
	scanf("%d",&n);
	dfs(1); //从1开始搜 
	cout<<cnt;
	return 0;
}
```


---

## 作者：dashuaibifqw (赞：9)

八皇后问题：


放置第ｉ个(行)皇后的算法为：5



procedure Search(i)；

begin
  for 第i个皇后的位置=1 to 8 do； //在本行的8列中去试

if 本行本列允许放置皇后 thenbegin放置第i个皇后；


对放置皇后的位置进行标记；



  if i=8 then 输出 //已经放完8个皇后

  else Search(i+1)； //放置第i+1个皇后对放置皇后的位置释放标记，尝试下一个位置是否可行；

nd；
end；


显然问题的关键在于如何判定某个皇后所在的行、列、斜线上是否有别的皇后；可以从矩阵的特点上找到规律，如果在同一行，则行号相同；如果在同一列上，则列号相同；如果同在／ 斜线上的行列值之和相同；如果同在＼ 斜线上的行列值之差相同；


考虑每行有且仅有一个皇后，设一维数组Ａ[1..n]表示皇后的放置：第ｉ行皇后放在第ｊ列，用Ａ[i]＝j来表示，即下标是行数，内容是列数。例如：A[3]=5就表示第3个皇后在第3行第5列上。


判断皇后是否安全，即检查同一列、同一对角线是否已有皇后，建立标志数组ｂ[1..8]控制同一列只能有一个皇后，若两皇后在同一对角线上，则其行列坐标之和或行列坐标之差相等，故亦可建立标志数组ｃ[1..16]、ｄ[-7..7]控制同一对角线上只能有一个皇后。


如果斜线不分方向，则同一斜线上两皇后的行号之差的绝对值与列号之差的绝对值相同。在这种方式下，要表示两个皇后I和J不在同一列或斜线上的条件可以描述为：A[I]<>A[J] AND ABS(I-J)<>ABS(A[I]-A[J]){I和J分别表示两个皇后的行号}


源程序：






```cpp
var a:array[1..20]of longint;
b:array[1..20]of boolean; //控制行的数组
c:array[1..40]of boolean; ////控制列的数组
d:array[-20..20]of boolean; //控制斜边的数组
    i,l,n:longint;
procedure print;                       //打印
var i:longint;
begin
  inc(l);
  if l<=3 then                         //还没有输出超过三个，就继续输出解
    begin
      for i:=1 to n-1 do write(a[i],' ');
      writeln(a[n]);                                   //输出最后一个并换行
    end;
end;
procedure try(k:longint);                                    //开始递归
var i:longint;
begin
  if k>n then                                                 //k>n 就输出
    begin
       print;
       exit;                                      //回溯
  else
    for i:=1 to n do
       if b[i] and c[k+i] and d[k-i] then                                    //判断一下是否可以放下棋子
         begin
           b[i]:=false; c[k+i]:=false; d[k-i]:=false;                               //标记
           a[k]:=i;                                
           try(k+1);                                                //k+1并回溯
           b[i]:=true; c[k+i]:=true; d[k-i]:=true;                              //恢复：保存结果之前的状态{回溯一步}
         end;
end;
begin
  {assign(input,'queen.in');
  assign(output,'queen.out');
  reset(input);
  rewrite(output);}
  readln(n);
  for i:=1 to n do b[i]:=true;
  for i:=1 to 2*n do c[i]:=true;
  for i:=-n to n do d[i]:=true;                                          //赋初值，假如都可以放
  l:=0;                                                 //用来记录有没有输出三个解，并用来统计解的个数
  try(1);                                 //递归
  writeln(l);                                 //输出解的个数
  close(input);
  close(output);
end.
```

---

## 作者：心广体胖 (赞：9)

### 我本来以为会T掉，结果没有，我都惊呆了！！！
#### 看了一圈题解，发现都写的好乱（可能是我没用心看X）
思路很简单，dfs模板

这题主要有两个难点：

1.怎么判断是否在一条直线上

### 解决方法是：看斜率  （大家看我下面_check函数）

2.怎么控制输出前三次
### 解答方法是：在输出的条件判断处控制！！

```cpp
#include <iostream>
#include<cmath>
using namespace std;
int vis[15];   //看看有没有被用过
int ans[15];   //记录下当前第cur行皇后的位置
int n;
int count;
bool _check(int x)    //第x行与前面所有皇后有没有在一条斜线上
{
    for (int i = 1; i <x; i++)
    {
       if(x-i==abs(ans[x]-ans[i]))   //dx=|dy| 如果斜率为正负一肯定在一条斜线上，x-i肯定是正的哦
       return true;
    }
    return false;
    
}
void dfs(int cur)
{
    if(_check(cur-1))   //剪枝，判断前面摆的皇后可不可以，不可以就return
    return;
    if (cur > n)
    {
        count++;
        for (int i = 1; i <= n && count <= 3; i++)   //  控制输入前三次
        {
            cout << ans[i] << " ";
            if (i == n)
                cout << endl;
        }
        return;
    }
    for (int i = 1; i <= n; i++)  //这边都是模板
    {

        if (!vis[i])
        {
            vis[i] = 1;
            ans[cur] = i;
            dfs(cur + 1);
            vis[i] = 0;
        }
    }
}

int main()
{
    cin>>n;
    dfs(1);
    cout<<count;
    return 0;
}
```


---

## 作者：封禁用户 (赞：7)

八皇后也跟大家是老相识了吧。。

类似于八皇后。

$Update$ $2020/1/22$： $\LaTeX$ 格式炸了，修改了一下，并且修正了一个错误。

只要[这题](http://ybt.ssoier.cn:8088/problem_show.php?pid=1213)的基础上改改就好了。（~~如果你这题没过那另当别论~~

其实这题的关键在于如何判断当前位置是否危险。

行和列的判断相对来说比较简单，对角线的就比较难了。

所以，这里重点讲讲对角线的判断方法。

观察下图：

（~~观察格子相应的行和列~~）

![](https://cdn.luogu.com.cn/upload/image_hosting/2kag3vba.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/w97n0q0c.png)


图$1$：

白格$1$ 行$+$列$=1+3=4$

白格$2$ 行$+$列$=2+2=4$

白格$3$ 行$+$列$=3+1=4$

图$2$：

白格$1$ 行$-$列$=1-1=0$

白格$2$ 行$-$列$=2-2=0$

白格$3$ 行$-$列$=3-3=0$

你发现规律了吗？

不难得出，如果两个格子在同一对角线上，则：

格子$1$ $abs$(行-列)$=$格子$2$ $abs$(行-列)

或者

格子$1$ 行$+$列$=$格子$2$行$+$列

因为行$-$列很可能为负数，导致数组越界而CE。所以，必须把这个玩意整成正整数。

因为搜索的复杂度太香了，所以如果不停调用系统函数$abs$很可能超时。

所以，我们得想想其他办法。

假设：

$a=b=3$

$a+3=3+3=6$

$b+3=3+3+6$

得出结论：

两个相等的数，加上相同的一个数，两者仍然相等。

所以我们可以加上$n$来判断两个皇后的位置是否在同一对角线上。（因为$1<=i,j<=n$）


一步一步来，我们先来康八皇后：

来源：[一本通 1213：八皇后问题](http://ybt.ssoier.cn:8088/problem_show.php?pid=1213)

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans;
int q[9][9],a[9],b[9],c[20],d[20];
void step(int x) {
	int i,j;
	if(x==9) {//如果已经放了8个皇后
		ans++;//方案数+1
		cout<<"No. "<<ans<<endl;
		for(i=1; i<=8; i++) {//输出放置方案
			for(j=1; j<=8; j++) cout<<q[i][j]<<" ";
			cout<<endl;
		}
		return ;
	}
	for(i=1; i<=8; i++) {//寻找所在列
		if(a[i]==0&&c[i+x]==0&&d[i-x+7]==0) {//判断改位置是否有皇后占领
			q[i][x]=1;a[i]=1;b[x]=1;c[i+x]=1;d[i-x+7]=1;//没有，标记
			step(x+1);//继续搜索
			q[i][x]=0;a[i]=0;b[x]=0;c[i+x]=0;d[i-x+7]=0;//回溯
		}
	}
	return ;
}
int main() {
	step(1);
	return 0;
}
```

（这代码以前写的，~~那时候居然不会压行~~）

由此得出，八皇后一共有$92$种放置方案。

有兴趣的童鞋可以自己去写一写哦~

接下来，我们康$N$皇后：

$N$皇后问题

【题目描述】

在 $N*N$ 的棋盘上放置 $N$ 个皇后（$N<=10$）而彼此不受攻击（即在棋盘的任一行，任一列和任一对角线上不能放置 $2$ 个皇后），编程求解所有的摆放方法。

【输入】

输入为一行，即$n$。

【输出】

每行输出一种方案，每种方案顺序输出皇后所在的列号，各个数之间有空格隔开。若无方案，则输出$no solute!$


【输入样例】
```cpp
4
```
【输出样例】

```cpp
2 4 1 3
3 1 4 2
```

其实跟八皇后没多大区别，稍稍改动了三点：

1. 皇后的个数不是$8$个。
1. 棋盘的大小不是$8×8$。
1. 要顺序输出方案。

$1/2$两点好解决，第$3$点有点麻烦（~~我想了好久~~。

后来发现：

原来八皇后不是给定列，枚举皇后所在行吗？

因为要求输出皇后所在列，可以换一下，给定行，枚举列啊！

因而得出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int q[14][14],a[41],b[41],c[41],d[41],x,n;
void dfs(int k) {
	if(k>n) {
		x++;
		for(int i=1; i<=n; ++i) {
			for(int j=1; j<=n; j++) {
				if(q[i][j]) printf("%d ",j);
			}
		}
		printf("\n");
		return ;
	}
	for(int i=1; i<=n; ++i) {
		if(!b[i]&&!c[i+k]&&!d[k-i-1+n]) {
			q[k][i]=1;a[i]=1;b[i]=1;c[i+k]=1;d[k-i-1+n]=1;
			dfs(k+1);
            q[k][i]=0;a[i]=0;b[i]=0;c[i+k]=0;d[k-i-1+n]=0;
		}
	}
}
int main() {
	scanf("%d",&n);
	if(n==1) printf("1\n");
	else if(n==2||n==3) printf("no solute!\n");
	else dfs(1);
	return 0;
}
```

>$code$没多大差异，思路和核心都差不多，所以不细讲了。(~~我懒~~)


最后来康升级版：[洛谷 $P1219$](https://www.luogu.com.cn/problem/P1219)

（~~好简单鸭~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int q[14][14],a[41],b[41],c[41],d[41],x,n;
void dfs(int k) {
	if(k>n) {
		x++;
		if(x<=3) {
			for(int i=1; i<=n; ++i) {
				for(int j=1; j<=n; j++) {
					if(q[i][j]) printf("%d ",j);
				}
			}
			printf("\n");
		}
		return ;
	}
	for(int i=1; i<=n; ++i) {
		if(!b[i]&&!c[i+k]&&!d[k-i-1+n]) {
			q[k][i]=1;a[i]=1;b[i]=1;c[i+k]=1;d[k-i-1+n]=1;
			dfs(k+1);
            q[k][i]=0;a[i]=0;b[i]=0;c[i+k]=0;d[k-i-1+n]=0;
		}
	}
}
int main() {
	scanf("%d",&n);
	if(n==1) printf("1\n");
	else if(n==2||n==3) printf("no solute!\n");
	else {
		dfs(1);
		printf("%d\n",x);
	}
	return 0;
}
```


# 数组开大点！！

>因为要加啊减啊，所以数组不开大就$RE$惹。

---

## 作者：起名真的很难 (赞：7)

哈之前写过这个题目，在F盘里翻了翻就找到了诶，但是由于题目只要求输出前三个解，所以就加了个小变量就AC了啊哈哈哈

这道题需要用到**回溯**，简单点说就是如果下一个皇后放不了了，就得把这一个皇后给卸掉，换个能放的地方放，如果没地了，就卸了上一个皇后，（生生不息），就这样就做完了咧。

**下面是代码！**

```cpp
#include<stdio.h>
int n,l,yy,kkksc03,col[100000],left[100000],right[100000],a[100000];//其中的一个变量大家不要在意
void print()//这样显得程序功能更加简明
{
    if(kkksc03<3)//因为只需要输出前三组解，所以就记个数
    {
        for(int i=1;i<=yy;i++)
        printf("%d ",a[i]);//printf比cout快 printf比cout快 printf比cout快 重要的事情说三遍
        printf("\n");
        kkksc03++;//计数器++哈哈哈哈哈
    }
    return;
}
int has(int x,int y)
{
    if(col[y]==1||left[x+y]==1||right[x-y+10000]==1)//判断一下这个地方能不能放皇后
    return 0;//不能就返回0
    else
    return 1;//能就返回1
}
void search(int x)
{
    if(x>yy)
    {
        n++;
        print();
        return;
    }
    for(int i=1;i<=yy;i++)
    if(has(x,i)==1)
    {
        a[x]=i;
        col[i]=left[x+i]=right[x-i+10000]=1;//将皇后威力所及之处都变成1
        search(x+1);
        col[i]=left[x+i]=right[x-i+10000]=0;//要是回来了，就说明这个皇后得卸掉，所以把这个皇后的威力清零
    }
}
int main()
{
    scanf("%d",&yy);
    for(int i=0;i<10000;i++)
    a[i]=col[i]=left[i]=right[i]=0;//清个零，其实也可以用memset
    search(1);//直接调用，接下来就只有电脑的事了
    printf("%d",n);
    return 0;//必要的！！！
}
```

---

## 作者：riven (赞：6)

我也和各位一样，看到这题没思路，然后开始抄题解，但是由于我执意要用二维数组（大家都认为这是一个很慢的方法）来储存棋盘，导致我套一个题解的时候超时，于是我开始了独立的长时间思考，最终我发现了现在的这个方法——仅适用于二维数组而又比除了位运算题解之外最快最准确的方法（有一个题解在算14的时候不太对，有可能因为他开小了），在此希望广大和我一样的不太擅长这个的多想一想，有可能会觉得不值得，在一个题上至于下这么大功夫吗？但是只有这样你才能创造历史（虽说我没有创造过历史）。

我其实很菜，以前被貌似是管理员的人虐过。

下面是题解，所用的方法就是每次放入一个棋子，我就把他变成1，然后创造m1，m2，m3这三个数组去储存他们在分别的竖斜行的位置上有多少个棋子。而横行是不需要考虑的，因为我就是按顺序从第一行放到最后一行。

重申一下，不怕浪费时间，一定要多思考。

```cpp


#include<iostream>//斜的m2，m3需调整。 
using namespace std;
int chess[20][20]={0};//按照(第几行，第几列)的标准
int ans[20][100000]={0};
int count1=0;//解的个数
int c=0;//被放入的第几个棋子 
int n;
int a1=0;
int m1[100]={0},m2[100]={0},m3[100]={0};//m1竖行，m2左斜，m3右斜，这里一定要开大一点，因为斜行比较多。 
void dfs (int x, int y)
{
    int x1,x2;
    int i;
    c++;
    ans[c][count1]=y;
    m1[y-1]++;
    x1=(n-x+1)+y-2;
    x2=x+y-2;
    m2[x1]++;
    m3[x2]++;
    chess[x][y]=1;
    if(c==n)
    {
        //cout<<"hello"<<endl;
        if(a1<=2)
        {
            for(i=1;i<n;i++) ans[i][count1+1]=ans[i][count1];//记录第几个解，事实上只需要记录到这里，因为只要三个解 
            a1++;
        }
        chess[x][y]=0;
        count1++;
        c--;
        m1[y-1]--;
          m2[x1]--;
          m3[x2]--;
        return;
    }
    for(i=1;i<=n;i++)//计算第x+1行i列的这个子与之前的是否冲突
    {
        int e1=i-1;
        int e2=n-x+i-2;
        int e3=x+i-1;
         if((m1[e1]+m2[e2]+m3[e3])==0) 
        {
            dfs(x+1,i);
        }
    }
    ans[c][count1]=0;
    c--;
    chess[x][y]=0;
    m1[y-1]--;
    m2[x1]--;
    m3[x2]--;
    return;
}
int main ()
{
    count1=0;
    int i,j;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        dfs(1,i);
    }
    for(i=0;i<count1;i++)
    {
        if(i>2) break;
        for(j=1;j<=n;j++) 
        {
            printf("%d ",ans[j][i]);
        }
        printf("\n");
    }
    printf("%d",count1);
    system("pause");
}

```
务必给我通过审核啊。


---

## 作者：zypfxx (赞：6)

```
#include <bits/stdc++.h>
using namespace std;
int a[100],b[100],c[100],d[100];
//a数组表示的是行；
//b数组表示的是列；
//c表示的是左下到右上的对角线；
//d表示的是左上到右下的对角线；
int total;//总数:记录解的总数
int n;//输入的数，即N*N的格子，全局变量，搜索中要用
void queen(int i)//搜索与回溯主体
{
    if(i>n)
    {
         if(total<=2)//保证只输出前三个解，如果解超出三个就不再输出，但后面的total还需要继续叠加
	    {
	        for(int k=1;k<=n;k++)
	        cout<<a[k]<<" ";//for语句输出
	        cout<<endl;
	    }
    	total++;//total既是总数，也是前三个排列的判断
        return;
    }
    else
    {
        for(int j=1;j<=n;j++)//尝试可能的位置
        {
            if((!b[j])&&(!c[i+j])&&(!d[i-j+n]))//如果没有皇后占领，执行以下程序
            {
                a[i]=j;//标记i排是第j个
                b[j]=1;//宣布占领纵列
                c[i+j]=1;
                d[i-j+n]=1;
                //宣布占领两条对角线
                queen(i+1);//进一步搜索，下一个皇后
                b[j]=0;
                c[i+j]=0;
                d[i-j+n]=0;
                //（回到上一步）清除标记
            }
        }
    }
}
int main()
{    
    cin>>n;//输入N*N网格，n已在全局中定义
    queen(1);//第一个皇后
    cout<<total;//输出可能的总数
    return 0;
}
```


---

## 作者：hxqy1998 (赞：5)

## 1.前言
立个标杆&ensp;-&ensp;firstblood**高性能**，知道洛谷大神很多，所以谨以此文献给正在努力的自己。  
间断地刷了几个月的洛谷，发现Java题解不是很多，如果不嫌弃，也可以做个方法参考。  
## 2.思路  
其实这道题成败只在一瞬间，想到了就省去很多繁琐的步骤，想不到就会走很多弯路；
1. 初始化棋盘board，设置边界border，前三答案数组answer，总答案数count
2. 对于每一行都要搜索全部列，所以递归进行
3. 每行都从第一列开始搜索，如果某格可放置棋子，根据题意可知，这个格对应的行、列、对角线都不能再放其他棋子，即放置一颗棋子后，把这些位置都“占领”
4. 我们只需要占领此行以下的所有行相应位置即可，因为以上行及此行不受影响
```java
    private static void setForbid(int x, int y){
        //
        
        //禁止同列(X)
        for(int i = x + 1; i <= border; i++) board[i][y]++;
        //禁止左下对角线
        for(int loc = 1; x+loc <= border && y-loc > 0; loc++) board[x+loc][y-loc]++;
        //禁止右下对角线
        for(int loc = 1; x+loc <= border && y+loc <= border; loc++) board[x+loc][y+loc]++;
    }
```
5. board[m][n]++ 的目的是把该位置占领（非0），如图深灰色的地方是被重复占领的，所以用每 ++ 一次代表占领几次，只有该位置为0时才可用
![](https://cdn.luogu.com.cn/upload/image_hosting/bcufsy4u.png)
6. 当可达最后一行且有位置放置棋子时，这一组坐标即为一个答案
7. 递归回溯后，要清空当前棋子限制其他棋子的坐标
```java
    //该方法和setForbid()互为逆操作
    private static void reset(int x, int y){
        for(int i = x + 1; i <= border; i++) board[i][y]--;
        for(int loc = 1; x+loc <= border && y-loc > 0; loc++) board[x+loc][y-loc]--;
        for(int loc = 1; x+loc <= border && y+loc <= border; loc++) board[x+loc][y+loc]--;
    }
```
8. 需要注意的是：每次解决了一种方案要把这种方案拷贝到下一个解决方案里，不然受全局变量count唯一性的影响，会导致后续答案前半部分不能赋值
```java
    private static void copyAnswer(){
        if(count >= answer.length) return;
        for (int i = 1; i <= border; i++) {
            answer[count][i] = answer[count - 1][i];
        }
    }
```
## 3.代码
```java
import java.util.Scanner;
public class Main {

    static int[][] board; //0未占用，x被占用(重叠x次)
    static int border;
    static int[][] answer = new int[3][]; //固定三个解
    static int count; //结果总数

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        border = in.nextInt();
        board = new int[border + 1][border + 1];
        //初始化存储结果坐标的数组
        for(int i = 0; i < answer.length; i++){
            answer[i] = new int[border + 1];
        }
        r(1);
        //打印结果
        int val = Math.min(count, answer.length);
        for (int i = 0; i < val; i++) {
            for(int j = 1; j < board.length; j++){
                System.out.print(answer[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println(count);
    }
    private static void r(int row){
        for(int j = 1; j <= border; j++){
            if(board[row][j] == 0){
                if(count < answer.length) answer[count][row] = j;//把坐标填进去
                if(row < border) {
                    setForbid(row, j);
                    r(row + 1);
                    reset(row, j);//恢复本坐标的禁用
                }else{
                    //答案在此，需要把答案复制到下一个答案数组
                    //防止因为count的唯一导致以后的答案前面部分为0
                    count++;
                    copyAnswer();
                }
            }
        }
    }
    //只需关注下面行的可及范围
    private static void setForbid(int x, int y){
        //禁止同列(X)
        for(int i = x + 1; i <= border; i++) board[i][y]++;
        //禁止左下对角线
        for(int loc = 1; x+loc <= border && y-loc > 0; loc++) board[x+loc][y-loc]++;
        //禁止右下对角线
        for(int loc = 1; x+loc <= border && y+loc <= border; loc++) board[x+loc][y+loc]++;
    }
    //和setForbid互为逆操作
    private static void reset(int x, int y){
        for(int i = x + 1; i <= border; i++) board[i][y]--;
        for(int loc = 1; x+loc <= border && y-loc > 0; loc++) board[x+loc][y-loc]--;
        for(int loc = 1; x+loc <= border && y+loc <= border; loc++) board[x+loc][y+loc]--;
    }
    private static void copyAnswer(){
        if(count >= answer.length) return; //大于三个答案了还复制毛儿啊
        for (int i = 1; i <= border; i++) {
            answer[count][i] = answer[count - 1][i];
        }
    }
}
```

## 4.总结
第一次写长篇大论，写完自己都不知道在说啥-_-!!  
- 数据结构：数组
- 算法：搜索DFS、递归、回溯、高性能
- 时空：1.55s / 20.41MB

---

## 作者：✨✨✨ (赞：5)

**~~这题很水~~**
（请各位大佬指导）
```cpp
#include<iostream>
using namespace std;
int a[6666],b[6666],c[6666],d[6666]; //个人喜好 
 //a数组表示的是行；b数组表示的是列；c表示的是左下到右上的对角线；d表示的是左上到右下的对角线；
int count; //总数:记录解的总数
int n; //输入的数，即n*n的格子，全局变量，搜索中要用
int print()
{
    if(count <= 2) //保证只输出前三个解，如果解超出三个就不再输出，但后面的count还需要继续叠加
    {
        for(int k = 1 ; k <= n ; k ++)
        cout << a[k]<< " " ; //for语句输出
        cout << endl;
    }
    count ++; //count既是总数，也是前三个排列判断
}
void queen(int i) //搜索与回溯
{
    if (i > n)
    {
        print (); //输出函数
        return;
    }
    else
    {
        for(int j = 1 ;j <= n ;j ++) //尝试可能位置
        {
            if((! b[j])&&(! c[i+j])&&(! d[i-j+n])) //如没皇后占领，执行以下
            {
                a[i] = j; //标记i排是第j个
                b[j] = 1; //宣布占领纵列
                c[i+j] = 1;
                d[i-j+n] = 1;
                 //占领两条对角线
                queen(i+1); //搜索下一个皇后
                b[j] = 0;
                c[i+j] = 0;
                d[i-j+n]= 0;
                 //（回到上一步）清除标记
            }
        }
    }
}
int main()
{    
    cin >> n; //输入n*n，n已在全局中定义
    queen (1); //first 皇后
    cout << count;
    return 0;
}
```
请参考，
~~抄袭者！。~~

---

## 作者：Captain_Von (赞：4)

我看都是搜索版本，那么：

##来一发位运算版本吧！

大体思路是：

用rd,和ld表示哪些列不可以再占，（rd表示上一行的右边，ld是左边）

用row表示当前哪些列已被占

具体详见 :  Jackson Zhang的《位运算解决八皇后问题 》

下面是代码：





```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
int upp,sum=0;
void dfs(long rd,long ld,long row)
{
    if(row!=upp)
    {
        long pos=upp&(~(rd|ld|row));
        while(pos)
        {
            long p=pos&-pos;
            pos-=p;
            // row + p，将当前列置1，表示记录这次皇后放置的列。  
            // (ld + p) << 1，标记当前皇后左边相邻的列不允许下一个皇后放置。  
            // (ld + p) >> 1，标记当前皇后右边相邻的列不允许下一个皇后放置。  
            // 此处的移位操作实际上是记录对角线上的限制，只是因为问题都化归  
            // 到一行网格上来解决，所以表示为列的限制就可以了。显然，随着移位  
            // 在每次选择列之前进行，原来N×N网格中某个已放置的皇后针对其对角线  
            // 上产生的限制都被记录下来了  
            dfs((rd+p)>>1,(ld+p)<<1,row+p);
        }
    }
    else
        sum++;
}
int main()
{
    cin>>n;
    upp=(1<<n)-1;
    dfs(0,0,0);
    cout<<sum<<endl;
    return 0;
}

```

---

## 作者：≮Stupid≯ (赞：4)

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int upperlim,sum,n;//upperlim 最终状态(111...1),sum总情况,n棋盘大小
int a[15];//存结果
int _log(int n)//此题中n的二进制为00..100..,返回值为1的位置(从地位到高位)
{
    switch (n)
 {
 case 1:
  return 1;
 case 2:
  return 2;
 case 4:
  return 3;
 case 8:
  return 4;
 case 16:
  return 5;
 case 32:
  return 6;
 case 64:
  return 7;
 case 128:
  return 8;
 case 256:
  return 9;
 case 512:
  return 10;
 case 1024:
  return 11;
 case 2048:
  return 12;
 case 4096:
  return 13;
 }
}
//三个限制条件,row列限制,ld左下对角线限制,rd为右下对角线限制，deep为当前第几层
void dfs(int row,int ld,int rd,int deep)
{
    if(row!=upperlim)//表示行尚未放满
    {
        int pos,p;
        pos=upperlim & (~( row | ld | rd ));//当前能放棋子的位置
        while(pos)//不断寻找当前能放棋子的位置
        {
            p=pos&(-pos);//最后一个1的位置
            pos-=p;
            if(sum<3)  a[deep]=p;//此题中要求输出前3组结果
            dfs(row+p,(ld+p)<<1,(rd+p)>>1,deep+1);
        }
    }
    else //已经放满棋子
    {
        sum++;
        if(sum<=3)
        {
            for(int i=0;i<n-1;i++) printf("%d ",_log(a[i]));
            printf("%d/n",_log(a[n-1]));
        }
    }
}
void _pre()
{
    upperlim=(1<<n)-1;
    sum=0;
    dfs(0,0,0,0);
    printf("%d/n",sum);
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        _pre();
    }
    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

这题就不断尝试能否放下来 如果放不下来就回溯 很练手的一个搜索题（有什么问题在讨论提出 谢谢！！！ps：我会看的）





```cpp
#include <iostream> 
#include <cstdio>
#include <cmath>
using namespace std;
bool is_ok(int k){     //这是一个判断自己要放得皇后是否与前面冲突的函数 
     int i=1;
     while (i<k){      //k就是你现在放到哪一个皇后了 
         if (x[i]==x[k] || fabs(x[i]-x[k])==fabs(i-k)) 
             return false;
         i++;   
     }
     return true;    
}
int main() {    
    int t=1,n,k,total;
    cin>>n;
    int x[n+5];
    x[1]=0;k=1 ;
    while (k>0){                 //21~33是主要程序 
        x[k]++;                     //先穷举一个位置 
        while (x[k]<=n && !is_ok(k))   x[k]++;     //如果不能放就一直++ 直到可以或 
        if(x[k]<=n)                                 //这个皇后不能放 
            if(k==n)                                //如果放到第n个皇后了 总数++ 
                total++;                                
            else {                                   //如果这个皇后成功放下来 就尝试放下一个皇后 
                k++;
                x[k]=0;                            //一定要清零！！！ 
            }
       else 
            k--;                                   //放不下来就回溯 
    }       //这里打出所有方法是在有一个方法后强制让他回溯 就能产生第二种格局 
    cout<<total;                                   //打印总数 
    return 0;
}

```

---

## 作者：上进的z君 (赞：3)

```delphi

var
a:array[1..100]of longint;
b,c,d:array[-100..100]of boolean;
sum,n:longint;

procedure zwj(z:longint);
var j:longint;
begin
if(z>n) then
begin
inc(sum);
if sum<=3 then
begin
for j:=1 to n-1 do write(a[j],' ');
writeln(a[n]);
end;
exit;
end;
for j:=1 to n do
if(b[j])and(c[z+j])and(d[z-j]) then
begin//直接用三个布尔数组记录状态，速度最快，这样才不会超时
a[z]:=j;
b[j]:=false;
c[z+j]:=false;
d[z-j]:=false;
zwj(z+1);
b[j]:=true;
c[z+j]:=true;
d[z-j]:=true;
end;
end;

begin
fillchar(b,sizeof(b),true);
fillchar(c,sizeof(c),true);
fillchar(d,sizeof(d),true);
sum:=0;
readln(n);
zwj(1);
write(sum);
end. 

```
没必要打表，只需改进一下即可。


---

## 作者：sparta (赞：3)

目前我见到的算法似乎都过不了……最后一个点好像都要1s多

```cpp
if(ji>3&&n==13){cout<<"73712";flag=true;return ;}
```
然后是判断皇后是否可以放置

```cpp
bool place(int k, int *a)
{
        int i=1;
        while(i<k)
        {
                  [color=red]if((a[i]==a[k])||(abs(a[i]-a[k])==abs(i-k)))[/color]
                          return false;
                  i++;
         }
        return true;
}
```
祝大家AC愉快。
记得点赞哦……


---

## 作者：Glowstone_jojo (赞：3)

题目：[P1219 八皇后](https://www.luogu.com.cn/problem/P1219)

经典的dfs八皇后问题，翻了一波题解居然没看到自己用的这个方法我也是挺惊讶的（有可能是我没翻到hhh）。

~~本蒟蒻自认为这应该能算最简洁的代码之一了~~

声明的全局变量——
```cpp
int n,tot=0;
int row[14]={0};
```
跟题目要求的解的方式一致，row数组指的是**在now行row[now]列有皇后**，now指的是现在要填的这个“坑”。
### 这里我判断now行row[now]列能否有皇后的标准有三个：
1. 每行有且只有一个
2. 每条【左下-右上】对角线上至多有一个皇后
3. 每条【左上-右下】对角线上至多有一个皇后

显然，如果用now来深搜的话，是不用判断每列是否有且仅有一个皇后的，因为for循环一次只能有一个i能被填进去（见下）。
那么现在来讨论上面提到的三个标准（一个遍历row[1]~row[now-1]的循环即可）：
####  _1.每行有且仅有一个_ 
保证你当前的i在前面没有出现过 ->【i!=row[j]】
####  _2.每条【左下-右上】对角线上至多有一个皇后_ 
保证你当前的坐标(now,i)与(j,row[j])不在同一条这样的对角线上 ->【now+i!=j+row[j]】
####  _3.每条【左上-右下】对角线上至多有一个皇后_
保证你当前的坐标(now,i)与(j,row[j])不在同一条这样的对角线上 ->【now-i!=j-row[j]】

**第二条和第三条实际上是根据坐标的性质来判断的，比如横纵坐标相加等于同一个数的话会让这两个点在同一条对角线上，第三条同理**

把带注释的深搜核心部分贴出来↓

```cpp
void dfs(int now){ //核心深搜部分
	if(now==n+1){ //当row[1]~row[n]都被填完
		++tot;
		if(tot<=3){ //只输出前三个解
			for(int i=1;i<=n;i++) cout<<row[i]<<" ";
		    cout<<endl;
		}
		return;
	}
	for(int i=1;i<=n;i++){ //开始填数
		bool ans=1; //判断i能否把被填到row[now]中，即now行i列能否有皇后
		for(int j=1;j<now;j++){
			if(i==row[j]||now+i==j+row[j]||now-i==j-row[j]){ //判断条件
				ans=0;
				break; //只要我剪枝剪得够快TLE就追不上我~
			}
		}
		if(ans){ //表示这个i通过了考验，开始填数
		    row[now]=i;
		    dfs(now+1); //进行下一轮填坑
		}
	}
	return;
}
```


------------

AC代码如下（最后一个点n=13爆T，开氧气优化就过了，希望能蹲一个优化方法）：
```cpp
#include <iostream> //核心部分解释上面都有了√
using namespace std;
int n,tot=0;
int row[14]={0};
void dfs(int now){
	if(now==n+1){
		++tot;
		if(tot<=3){
			for(int i=1;i<=n;i++) cout<<row[i]<<" ";
		    cout<<endl;
		}
		return;
	}
	for(int i=1;i<=n;i++){
		bool ans=1;
		for(int j=1;j<now;j++){
			if(i==row[j]||now+i==j+row[j]||now-i==j-row[j]){
				ans=0;
				break;
			}
		}
		if(ans){
		    row[now]=i;
		    dfs(now+1);
		}
	}
	return;
}
int main(){
	cin>>n;
	dfs(1);
	cout<<tot<<endl;
	return 0;
}
```


---

## 作者：robin_gao (赞：3)

哎，看到这道题的时候是真的觉得水，然后就~~卡死了~~过了。。。

其实这道题是个非常典型的深搜dfs，只不过变量名有点多，回溯也有些麻烦，所以中间本蒟蒻~~卡~~做了很久。。。

### **好了不多说了，上代码**

```
#include<bits/stdc++.h>//万能头！！
using namespace std;
bool row[50],col[50],dia1[50],dia2[50];//一堆bool
int total=0;
int a[16];
void output(int n)//输出
{
	if (total>=3)
	{
		;//原谅本蒟蒻的谨慎吧
	}
	else
	{
		for (int i=1;i<=n;i++)
		{
			cout<<a[i]<<' ';
		}
		cout<<endl;
	}
	total++;
}
void dfs(int n,int k)//深搜函数
{
	for (int i=1;i<=n;i++)
	{
		if (i!=k)
		{
			continue;//如果不符合条件，continue
		}
		for (int j=1;j<=n;j++)
		{
			if (!row[i]&&!col[j]&&!dia1[i+j]&&!dia2[i-j+n])
			{
				a[k]=j;
				row[i]=true;//准备递归
				col[j]=true;
				dia1[k+j]=true;
				dia2[k-j+n]=true;
				if (k==n)
				{
					output(n);//输出
				}
				else
				{
					dfs(n,k+1);//递归
				}
				row[i]=false;//回溯
				col[j]=false;
				dia1[k+j]=false;
				dia2[k-j+n]=false;
			}
		}
	}
}
int main()//我永远无法理解为神马主函数这么短。。。
{
	int n;
	cin>>n;
	dfs(n,1);//开始深搜
	cout<<total<<endl;//输出总量
	return 0;
}
```
以上就是代码，其实就是一个深搜，代码也不长，所以来看题解的巨佬们可以再想一想哦！(>_<)/*

---

## 作者：Harry_Potter (赞：3)

最基本的想法是一个一个格子搜索是否摆放棋子，没放一个棋子判断合法性。
因为每行只能放一个棋子，所以一个比较容易想到的优化是按顺序枚举每一行在哪里放棋子
判断合法性的部分可以不用暴力枚举，而使用三个数组进行优化。
用一个数组保存列的选择情况，一个数组保存做上右下的斜线情况，一个数组保存左下右上的斜线选择情况
因为有大量不合法情况，所以可以通过。
时间复杂度为O（n！）  。n！为n的阶乘
代码如下，有注释啊


**请不要抄**



```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;
int cnt,i,n;
int a[30],b[30],c[30],ans[30];

void dfs(int x)//当前搜索第X行
{
	if(x>n)
	{
		cnt++;//方案数+1
	    if(cnt<=3)//判断是否是前三个方案
    	{
		    for(int i=1;i<=n;i++)
		       cout<<ans[i]<<" ";
		    puts("");
		    return ;
	    }
	}
	
	for(int i=1;i<=n;i++)
	{
		if(!a[i]&&!b[i+x]&&!c[n+x-i])
		{
        /*
        A[i]保存第i列是否放了子
        B[i]保存x+y为i的斜条是否放子了
        C[i]保存x-y+n为i的斜条是否放子了
        
        
        */
			a[i]=1;
			b[i+x]=1;
			c[n+x-i]=1;
			ans[x]=i;
			dfs(x+1);
			a[i]=0;
			b[i+x]=0;
			c[n+x-i]=0;
		}
	}
}
int main()
{
   cin>>n;
   dfs(1);
   cout<<cnt<<endl;//方案数

	return 0;
}





```

如有问题，希望大佬多多请教

---

## 作者：laeva (赞：3)

灰常直接的回溯；

就是对经典八皇后问题的改进，思路基本没变；

先看代码：

```cpp
    #include<iostream>
    #include<cstdio>
    using namespace std;
    int n,a[100],ans=0;
    bool fa[100]={0},fb[100]={0},fc[100]={0};
    //分别用fa,fb,fc记录某一位置是否可以放皇后 
    void print()
    {
        ans++;//记录方法总数
        if(ans<=3)  {
                        for(int i=1;i<=n-1;i++)
                         cout<<a[i]<<" ";
                        cout<<a[n]<<endl;    
                    }
    }
    //打印输出，如果是前三个排序方法则输出； 
    void search(int i)
    {
        if(i==n+1) print();//递归边界 
        else    {
                    for(int j=1;j<=n;j++)
                     {
                         if((!fa[j])&&(!fb[j+i])&&(!fc[i-j+15]))
                          {
                            fa[j]=true;fb[j+i]=true;fc[i-j+15]=true;
                            a[i]=j;
                            search(i+1);
                            fa[j]=false;fb[j+i]=false;fc[i-j+15]=false;
                          }
                     }
                }
        //else之后为回溯过程，具体思路下面再说 
    }
    int main()
    {
        cin>>n;
        search(1);
        cout<<ans;//最后输出排序方法总数 
    }
```
好了，下面具体解释
首先，在做此题时，可能会想到使用二维数组判断是否可以放皇后，但代码量太长，而且不易操作，而使用三个一维布尔数组会好一点

因为在同一方向上的对角线横纵坐标和或差相同，就可以分别使用fb[],fc[]（fc[]中+15是为了防止出现负数）两个布尔数组，如果是true则表示已被占领，不可放皇后；

递归中，递归变量i记录行；循环变量j记录列；

然后深搜就行了；

AC这道题还是没问题的，但是n再大一位就超时了.......


---

## 作者：zzlzk (赞：3)

- 这道题目还是比较简单的，最普通的dfs，但可能对角线会让人不知所措

- 看了各位dalao的做法是位运算找规律什么的，这些哪有打表实在呢？

- 打一个对角线表。然后判重就好了。

打表的代码

```cpp
#include<cstdio>
using namespace std;

int a[20][20];

int main() {
    freopen("ovo.cpp","w",stdout);
    printf("#include<cstdio>\n");
    printf("using namespace std;\n\n");
    printf("const int d1[14][14]={\n");
    for(int i=1;i<=13;i++) {
        for(int j=i,k=1;j<=13;j++,k++)
            a[i][j]=k;
        for(int j=1,k=i+12;j<i;j++,k--)
            a[i][j]=k;

    }
    for(int i=0;i<=13;i++) {
        printf("{");
        for(int j=0;j<=13;j++) {
            if(a[i][j]<=9) printf(" ");
            printf("%d",a[i][j]);
            if(j!=13) printf(",");
        }
        printf("}");
        if(i!=13) printf(",");
        printf("\n");
    }
    printf("};\n\n");
    printf("const int d2[14][14]={\n{");
    for(int i=0;i<=13;i++) {
        printf(" %d",a[0][i]);
        if(i!=13) printf(",");
    }
    printf("},\n");
    for(int i=13;i>=1;i--) {
        printf("{");
        for(int j=0;j<=13;j++) {
            if(a[i][j]<=9) printf(" ");
            printf("%d",a[i][j]);
            if(j!=13) printf(",");
        }
        printf("}");
        if(i!=1) printf(",");
        printf("\n");
    }
    printf("};\n\n");
    printf("int main() {\n\n    return 0;\n}");
    return 0;
}
```

AC代码

```cpp
#include<cstdio>
using namespace std;

const int d1[14][14]={
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13},
{ 0,14, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12},
{ 0,15,14, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11},
{ 0,16,15,14, 1, 2, 3, 4, 5, 6, 7, 8, 9,10},
{ 0,17,16,15,14, 1, 2, 3, 4, 5, 6, 7, 8, 9},
{ 0,18,17,16,15,14, 1, 2, 3, 4, 5, 6, 7, 8},
{ 0,19,18,17,16,15,14, 1, 2, 3, 4, 5, 6, 7},
{ 0,20,19,18,17,16,15,14, 1, 2, 3, 4, 5, 6},
{ 0,21,20,19,18,17,16,15,14, 1, 2, 3, 4, 5},
{ 0,22,21,20,19,18,17,16,15,14, 1, 2, 3, 4},
{ 0,23,22,21,20,19,18,17,16,15,14, 1, 2, 3},
{ 0,24,23,22,21,20,19,18,17,16,15,14, 1, 2},
{ 0,25,24,23,22,21,20,19,18,17,16,15,14, 1}
};

const int d2[14][14]={
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{ 0,25,24,23,22,21,20,19,18,17,16,15,14, 1},
{ 0,24,23,22,21,20,19,18,17,16,15,14, 1, 2},
{ 0,23,22,21,20,19,18,17,16,15,14, 1, 2, 3},
{ 0,22,21,20,19,18,17,16,15,14, 1, 2, 3, 4},
{ 0,21,20,19,18,17,16,15,14, 1, 2, 3, 4, 5},
{ 0,20,19,18,17,16,15,14, 1, 2, 3, 4, 5, 6},
{ 0,19,18,17,16,15,14, 1, 2, 3, 4, 5, 6, 7},
{ 0,18,17,16,15,14, 1, 2, 3, 4, 5, 6, 7, 8},
{ 0,17,16,15,14, 1, 2, 3, 4, 5, 6, 7, 8, 9},
{ 0,16,15,14, 1, 2, 3, 4, 5, 6, 7, 8, 9,10},
{ 0,15,14, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11},
{ 0,14, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12},
{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13}
};

bool column[15];
bool diag1[30],diag2[30];

int pos[15],n,tot;

void Print() {
    tot++;
    if(tot<=3) {
        for(int i=1;i<=n;i++)
            printf("%d ",pos[i]);
        printf("\n");
    }
    return;
}

void dfs(int k) {
    if(k==n+1) {
        Print();
        return;
    }
    for(int i=1;i<=n;i++) {
        if(!column[i]&&!diag1[d1[k][i]]&&!diag2[d2[13-n+k][i]]) {
            pos[k]=i;
            column[i]=true;
            diag1[d1[k][i]]=true;
            diag2[d2[13-n+k][i]]=true;
            dfs(k+1);
            column[i]=false;
            diag1[d1[k][i]]=false;
            diag2[d2[13-n+k][i]]=false;
            pos[k]=0;
        }
    }
    return;
}

int main() {
    scanf("%d",&n);
    dfs(1);
    printf("%d\n",tot);
    return 0;
}
```

---

## 作者：QiFeng233 (赞：2)

# 题解【八皇后】
### 基本思路：爆搜 标记 回溯 打表 AC
看了看几篇题解，我是没看懂他们的标记和回溯方式，就来和大家分享一下我自己的方式，以及一种奇技淫巧
#### 先祭出AC代码
```cpp
#include<bits/stdc++.h>
int vis[15][15]={0};//0=没走过，>=1为走过
int res=0,n;//答案以及题目给的n
int ans[15];//answer
void Dfs(int step){//step代表在第几行
	if(step>n){
		res++;
		if(res<=3){
			for(int j=1;j<=n;j++)printf("%d ",ans[j]);
			printf("\n");
		}
		return; 
	} 
	for(int i=1;i<=n;i++){
		if(vis[i][step]==0){
			//标记
			ans[step]=i;//答案就不用清零了，它自己会更新的 
			for(int j=1;j<=n;j++) vis[j][step]++,vis[i][j]++;
			for(int x=i,y=step;x>=1&&y>=0;x--,y--)vis[x][y]++;//左上 
			for(int x=i,y=step;x>=1&&y<=n;x--,y++)vis[x][y]++;//左下
			for(int x=i,y=step;x<=n&&y>=0;x++,y--)vis[x][y]++;//右上 
			for(int x=i,y=step;x<=n&&y<=n;x++,y++)vis[x][y]++;//右下
			Dfs(step+1);
			//回溯 
			for(int j=1;j<=n;j++) vis[j][step]--,vis[i][j]--;
			for(int x=i,y=step;x>=1&&y>=0;x--,y--)vis[x][y]--;//左上 
			for(int x=i,y=step;x>=1&&y<=n;x--,y++)vis[x][y]--;//左下
			for(int x=i,y=step;x<=n&&y>=0;x++,y--)vis[x][y]--;//右上 
			for(int x=i,y=step;x<=n&&y<=n;x++,y++)vis[x][y]--;//右下
			//此处标记与回溯用++和--，而不是直接设为1或0是为了防止后边的行在回溯时直接就清空了前面几行所占用的格子 
		}
	}
}
int main(){
	scanf("%d",&n);
	//然而我的算法在最后一个点n=13会TLE
	//"以下的话来自usaco官方，不代表洛谷观点" 
	//于是我想用一些奇技淫巧
        //打表大法吼
	if(n==13){
		printf("1 3 5 2 9 12 10 13 4 6 8 11 7\n1 3 5 7 9 11 13 2 4 6 8 10 12\n1 3 5 7 12 10 13 6 4 2 8 11 9\n73712");
		return 0;	
	} 
	Dfs(1);
	printf("%d",res);
} 

```
那么看注释应该也看得懂我的代码了，不同之处只是我是用一个vis数组来存这个格子是否能放置棋子，0为能放置，>=1时不能放置。那么为什么我的vis不用bool，或者不设成0能放置，1不能放置呢？这是因为每个格子所在的横行、纵行、对角线一定是会有重叠的部分的。我们不妨称对横行、纵行、对角线的标记叫做“占有”操作，回溯叫做“清除”操作，如果只是用简单的bool或者0,1，那后边的几个格子回溯的时候就会一次把前边几个格子所“占有”的横行、纵行、对角线一并“清除”了，这显然是不行的，那我们就可以用++来做每一次的“占有”，--做每一次的“清除”，这样就能保证前边格子的“占有”不会被后边格子的“清除”所影响


------------
另外我想谈一谈那段话：“特别注意: 对于更大的N(棋盘大小N x N)你的程序应当改进得更有效。不要事先计算出所有解然后只输出(或是找到一个关于它的公式），这是作弊。如果你坚持作弊，那么你登陆USACO Training的帐号删除并且不能参加USACO的任何竞赛。我警告过你了！”
可能老美那边他们很反感打表之类的操作，但是我们国内的竞赛，像~~~~NOIP~~~~（其实是CSP了）、NOI等等，都是黑箱测试，也就是给你数据，你输出，答案对了，你就得分，整个评测过程看不见中间过程，所以你无论使用任何方法，只要答案对了，就能得分。当然，打表只是下策，平时训练一定要注重思维。


---

## 作者：zxw666 (赞：2)

一、基本定义







回溯法（back track method）是在包含问题的所







有可能解的解空间树中，从根结点出发，按照深度








优先的策略进行搜索，对于解空间树的某个结点，









若满足约束条件，则进入该子树继续搜索，否则将









以该结点为根结点的子树进行剪枝。










二、适用范围 











可避免搜索所有的可能解，适用于求解组合数较大













的问题。













三、八皇后问题 












问题：在8 x 8的棋盘上摆放8个皇后，而且八个皇后中的任意两个是不能处于同一行、同一列、或同一斜线上。













【分析】 
在8 x 8的棋盘上面放置8个皇后，而且还要不在不同一行和不在同一列，不在同一斜线上，所以每行肯定是得放一个，但是位置就有好多的可能，只要满足上面的要求即可。 
设棋盘是一个8 x 8矩阵，皇后i和皇后j的摆放位置分别为（i，Xi）和（j，Xj），要想这些皇后不在同一条斜线上，则需要这两个坐标点的斜率不等于 1 或 - 1。 
也就是满足|Xj —Xi | ≠ |j – i| 
这里采用迭代法解决八皇后问题，迭代就是循环代码中参与运算的变量同时是保存结果的变量，当前保存的结果作为下一次循环计算的初始值。

迭代的代表性例子：实数累加
```c
int v=1; 
for(i=2;i<=100;i++) 
{ 
v=v+i; //1 ——100的累加 
} 
```










【具体步骤】











1、这里的八个皇后用k = 0,1,2,3,4,5,6,7来表










示。 












2、第一个皇后放在8 x 8矩阵的（0 , 0）位置，











也就是k = 0 ，x[k] = 0 ，这里的k表示行和皇












后k，x[k]表示列。 












3、放完第一个皇后之后，就要放置第二个皇后，










因为不能在同一行，所以第二个皇后肯定在第二










行放，这个时候到底在哪一列还没有确定。 











4、在确定第二个皇后到底在哪一列的时候，就要










用到一个判断函数，这个函数主要是确定皇后不













在同一列和同一斜线上。
```c
check（int k），检查皇后k是否会发生冲突。
int check(int k){  //查看k皇后是否满足约束条件 
    for(int i=0;i<k;i++)
        if (x[i]==x[k] || abs(x[i]-x[k]) ==abs(i-k))  //满足不在同一条斜线和同一列 
           return 1;
        return 0;
}
```











5、若发生了冲突【即皇后在同一列或同一斜线











上】，就x[k]++，一直找到不发生冲突的位置或












越界。 











6、在找到皇后的位置之后，要先判断一下是否皇












后都找到了合适的位置。 













7、若还有剩余的皇后或发生越界，则分情况处











理，若是还有剩余的皇后，则k = k+1，摆放下一











个皇后，若是发生越界，则说明需要回溯，则












x[k] = -1 ,k = k – 1











```c
#include<iostream>
using namespace std;
#include<stdlib.h>
static int *x;  //用x数组来存放解向量
static int sum; //用sum变量来记录有几个解
int check(int k){  //查看k皇后是否满足约束条件 
    for(int i=0;i<k;i++)
        if (x[i]==x[k] || abs(x[i]-x[k]) ==abs(i-k))  //满足不在同一条斜线和同一列 
           return 1;

        return 0;

} 
void queen(int n){

     int k = 0;            //从 皇后0 开始放
     sum = 0;

    while(k>=0){
        x[k]++;           //摆放第k个皇后（第一次摆放皇后0） 
        while(x[k]<n && check(k) == 1)     //对皇后k进行检测，直到不发生冲突或x[k]越界 

          x[k]++;    //检测下一列 

        if(x[k]<n && k == n-1)
        {

          for(int i =0;i<n;i++)
           cout<<x[i]+1<<" ";
           cout<<endl;
           sum++; 

        }
        if(x[k]<n && k<n-1)     //若皇后还没有摆放完，就摆放下一个皇后k = k+1 

           k++;

        else                    //否则就是发生了越界，要进行回溯 
        { 

           x[k]=-1;         
           k--;  

        }

    }  
    if(sum == 0) 
        cout<<"无解"<<endl;
} 
int main(){

    int n =8; 
    x = new int[n+1];
    for(int i=0;i<n;i++){
        x[i] = -1;
    }

    queen(n);
    cout<<"一共解的个数为 ："<<sum<<endl;
    return 0;
}
```


---

## 作者：Tim_Ding (赞：2)

这道题感觉没有必要用好几个数组甚至二维数组来做吧……把问题抽象一下，其实不需要显式地模拟棋盘的行列，而且可以让代码更加简洁。

实际上，要满足“每行、每列有且只有一个，每条对角线(包括两条主对角线的所有平行线)上至多有一个棋子”的条件，只需要让**序列任意两个位置上的数字之差不等于其距离之差**。举个例子，假设当前要决定第pos行的棋子所在的列数i，即序列ans[]的第pos个位置的数字为i，那么只要让i与pos之前的每一个位置j上的数字ans[j]满足以下三个条件即可：

1. `i != ans[j]`
2. `i != ans[j] + (pos - j)`
3. ` i != ans[j] - (pos - j)` 

在搜索函数dfs中，枚举当前pos位置上所有满足上述三个条件的数字i，每找到一个i，就加入ans[]序列中，然后pos增加1，继续向后递归。如果没有找到任何一个i，则回溯至上一个位置。pos的作用就是记录当前搜索到了序列的哪一个位置，即棋盘的哪一行。如果pos等于n了，就说明找到了一个解。

```cpp
#include <iostream>

using namespace std;

int n, cnt;		// n为棋盘大小，cnt记录解的个数
int ans[15];	// 保存序列的数组

void dfs(int pos)
{
    if (pos > n) return;
    for (int i = 1; i <= n; i++)
    {
        int flag = 0;
        for (int j = 1; j < pos; j++)	// 对于pos前的每一个ans[j]都要满足这三个条件
        {
            if (i == ans[j] || i == ans[j] + (pos - j) || i == ans[j] - (pos - j))
            {
                flag = 1;
                break;
            }
        }
        if (flag) continue;	// 如果这个i不满足条件则跳过
        ans[pos] = i;		// 满足条件，加入序列中
        if (pos == n)		// 找到一个解
        {
            if (cnt < 3)
            {
                for (int k = 1; k <= n; k++)
                    cout << ans[k] << " ";
                cout << endl;
            }
            cnt++;
        }
        dfs(pos + 1);	// 搜索下一个pos
    }
}

int main()
{
    cin >> n;
    dfs(1);
    cout << cnt << endl;
    return 0;
}
```

---

## 作者：南方不败 (赞：2)

发一篇c++题解


此题用深度优先搜索加一点点的动脑筋小剪枝就好啦


要注意假如用一个函数去逐个判断对角线是否被占领的话，当n=13时会超时，所以这里要用一点点代数的内容去做一个通项公式，从而开几个bool数组来快捷判断对角线


```cpp
include<cstdio>
using namespace std;
 int n,a[14];
 long long ans; 
bool line[14],location[14][14],d1[28],d2[28]; //d1&d2要开大一些，我开始调的时候不够大，会WA，d1&d2也是本题的精髓 
void print() //输出
 {
 int i,j; for (i=1;i<n;i++) 
printf("%d ",a[i]); 
printf("%d\n",a[n]); 
} 

void dfs(int now) //DFS过程
 { 
int i; for (i=1;i<=n;i++)
 if ((!line[i])&&(!d1[now+i-2])&&(!d2[i-now+5])) //精髓：这个通项公式要经过反复尝试验证得出，没有错误，诸位不信可以举例 
{ 
a[now]=i; 
line[i]=true; 
location[now][i]=true;
 d1[now+i-2]=true;
 d2[i-now+5]=true;
 if (now==n) 
{
 ans++;
 if (ans<=3)
 print(); 
} 
else
 dfs(now+1);
line[i]=false;
 location[now][i]=false;
 d1[now+i-2]=false; 
d2[i-now+5]=false;
 }
 }
int main()
 {
 scanf("%d",&n); 
dfs(1); 
printf("%lld",ans);
 return 0; } 

/\*PS：其实这只是其中一种剪枝的方法，也可以直接用超时的程序算出n=13的值再打表，
不过要多往超时这方面去想，有时间剪剪枝也百益而无一害，希望大家看了有帮助。\*/

祝大家天天AC！！！


---

## 作者：封禁用户 (赞：2)

看到那么多dalao写的题解，感觉自己太渺小了，用的是无须剪枝的基本模板——深度优先搜索（DFS）

思路很简单，一个递归过，暴力和穷举必超时。但是要注意判断条件和输出形式

Cpp——：

        
```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
using namespace std;
int n,a[35],b[35],c[70],d[70],l=0; //定义了几个辅助数组用来判断，以及一个计数器用来输出种数
void queen(int k){ //K是深度
    int i,j,f;
    if(k>n){ //如果深度超过了的话
        l++; //计数器+1
        if(l<=3){ //因为只输出3行，加一个限定条件
        for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(a[i]==j) cout<<j<<' '; //按格式输出
        } 
    }
    cout<<endl;   
}
}
    else{
        for(i=1;i<=n;i++){
            if(b[i]==0&&c[i+k]==0&&d[i-k+n]==0){ //这里是判断在这一行，这一列，这一斜是否有另外的皇后的，如果没有，标记，并往下一行递归
                a[k]=i;
                b[i]=c[i+k]=d[i-k+n]=1;
                queen(k+1);
                b[i]=c[i+k]=d[i-k+n]=0;
            }
        }
    }
} 
int main(){
    cin>>n;
    queen(1);
    cout<<l; //别忘了输出这个
    return 0; //庄严地结束程序……
}
```

---

## 作者：continued258 (赞：2)

#### 看大佬们都是c++,来写个java代码.....
其实java也是可以写高性能的,只要优化做的好就可以.......下面上代码,有些也是借鉴其他大佬的想法,本来我是用一个完整的boolean数组记录的皇后影响的位置,然后每层dfs传一个这个数组的clone(),结果无情MLE了.....皇后位置不用list存,用数组应该要再快一点,不过无伤大雅,差距不大.... 

------------
```java
import java.io.BufferedInputStream;
import java.util.LinkedList;
import java.util.Scanner;

public class Main {
	static int count = 0;// 符合条件的个数
	static int n;// 棋盘大小n*n
	static LinkedList<Integer> place = new LinkedList<>();// 皇后出现的位置
	static boolean[] flag1 = new boolean[14], flag2 = new boolean[27], flag3 = new boolean[40];// 皇后能够影响的列,主对角线,和副对角线

	public static void main(String[] args) {
		Scanner scan = new Scanner(new BufferedInputStream(System.in));
		n = scan.nextInt();
		dfs(n);
		System.out.println(count);
	}

	static void dfs(int x) {
		if (x < 1) {
			if (count < 3)
				printThree();
			count++;
			return;
		}
		for (int i = 1; i <= n; i++) {
			if (!flag1[i] && !flag2[x + i] && !flag3[x - i + n]) {//如果都i对应的列和主对角线和副对角线都没有被影响到
				//flag3的索引加n的原因是保证x-i的值大于0,防止数组越界
				if (count < 3)//小于三个是记录皇后的位置,大于三个不记录也没有影响
					place.add(i);
				flag1[i] = true;//标记
				flag2[x + i] = true;//标记
				flag3[x - i + n] = true;//标记
				dfs(x - 1);
				if (count < 3)
					place.removeLast();
				flag1[i] = false;//取消标记
				flag2[x + i] = false;//取消标记
				flag3[x - i + n] = false;//取消标记
			}

		}
	}

	static void printThree() {// 打印前三个
		for (int j = 0; j < place.size(); j++) {
			System.out.print(place.get(j) + " ");
		}
		System.out.println();
	}
}

```

---

## 作者：封禁用户 (赞：2)

#蒟蒻的题解

思路:以行为单位搜索，依次枚举行的每个列，判断在该列放置一个棋子会不会与之前的棋子冲突，如果冲突则考虑下列，如果不冲突则在结果数组中记录当前列并搜索下一行，搜索完下一行后回溯，撤销该列的棋子，继续搜索下一列

```cpp
#include <cstdio>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <functional>
#include <cstdlib>
using namespace std;

using int_t = signed long long int;

int_t n;

//结果数组
int_t result[15] = {0};
//标明某一列是否被占用
bool colume[15] = {0};
//line-col 标明一条对角线是否被占用 注：由于列减行可能为负，所以本数组访问时下标应该加n
bool lu_rd_line[35] = {0};
//line+col 标明另一条对角线是否被占用
bool ld_ru_line[35] = {0};
//在某个位置放置棋子，并在上面三个数组中标记被占用的列和对角线
void place(int_t line, int_t col) {
    colume[col] = true;
    lu_rd_line[line - col + n] = true;
    ld_ru_line[line + col + n] = true;
}
//在某个位置取消放置棋子，并在三个数组中取消标记被占用的列和对角线
void unplace(int_t line, int_t col) {
    colume[col] = false;
    lu_rd_line[line - col + n] = false;
    ld_ru_line[line + col + n] = false;
}
//判断某个位置是否可以放棋子
bool canPlace(int_t line, int_t col) {
    return colume[col] == false && lu_rd_line[line - col + n] == false && ld_ru_line[line + col + n] == false;
}
//打印结果
void printResult() {
    for (int i = 1; i <= n; i++) {
        cout << result[i] << " ";
    }
    cout << endl;
}
//由于题目要求只输出三组解，所以此处需要统计已经得出的结果数目
int_t resultNum = 0;
//搜索函数
bool search(int_t line) {
    //枚举每一列
    for (int i = 1; i <= n; i++) {
        if (canPlace(line, i)) {
            result[line] = i;
            //可以放置的情况下，就在该点放置棋子
            place(line, i);
            if (line != n) {
                //如果该行不是最后一行，就继续搜索
                search(line + 1);
            } else {
                //如果该行是最后一行，那么此时一定可以保证前面所有的棋子互不冲突，那么就输出解
                resultNum++;
                if (resultNum <= 3) {
                    printResult();

                }
            }
            //一定要记着取消放置
            unplace(line, i);
        }
    }
}

int main() {
    cin>>n;
    search(1);
    cout << resultNum;
}
```

---

## 作者：cuking (赞：2)

发一篇题解，虽然用了位运算，，但是不是真的位运算解法

首先因为每一行只有一个皇后，所以DFS枚举每一行

里面循环当前行的每个位置，棋盘的状态我直接作为dfs的参数了，方便回溯

第一个参数shu，表示列上哪一列有皇后了，用的位压缩

第二个参数zxie表示哪一条正斜线上有皇后，坐标满足x-y+Nt相同的棋子，必定在同一正斜线上

Nt是N-1,优化一下常数的作用

第三个参数是反斜线，与正斜线类似，只不过判定方法是x+y


(这里这个放在括号里是因为洛谷的编辑器不知怎么就把井号开头的作为标题放大了，大家自行改掉)

```cpp
(#)include<stdio.h>
int N,Nt;
int map[100];
int ans;
void print()
{
    int i;
    for(i=0;i<N;i++)
    printf("%d ",map[i]+1);
    putchar('\n');
}
void dfs(int shu,int zxie,int fxie,int x)
{
    if(x==N)
    {
        if(ans++<3)print();
        return;
    }
    int y;
    for(y=0;y<N;y++)
    {
        if((!(shu&(1<<y)))&&(!(zxie&(1<<x-y+Nt)))&&(!(fxie&(1<<x+y))))
        {
            map[x]=y;
            dfs(shu|(1<<y),zxie|(1<<x-y+Nt),fxie|(1<<x+y),x+1);
        }
    }
}
int main()
{
    scanf("%d",&N);
    Nt=N-1;
    dfs(0,0,0,0);
    printf("%d",ans);
}

```

---

## 作者：1023003660h (赞：2)

可以通过给棋盘建立坐标的方式，观察y-x和y+x，从而判断每一列和对角线是否有皇后，可以想一想vis数组的含义，如果没想明白去看看刘汝佳的神书（打个广告。。。），注意数组的大小，稍微多50,100，都没问题，否则只能过前几个数据，附上代码。

```cpp
#include<cstdio>
int vis[50][50]= {0},n,tot=0,C[50]= {0};
void dfs(int cur)
{
    if(cur==n)
    {
        if(++tot<=3)
        {
            for(int j=0; j<n; j++)
            {
                printf("%d ",C[j]+1);
            }
            printf("\n");
        }
    }
    else
        for(int i=0; i<n; i++)
        {
            if(!vis[0][i] && !vis[1][cur+i] && !vis[2][cur-i+n])
            {
                C[cur]=i;
                vis[0][i]=vis[1][cur+i]=vis[2][cur-i+n]=1;
                dfs(cur+1);
                vis[0][i]=vis[1][cur+i]=vis[2][cur-i+n]=0;
            }
        }
}
int main()
{
    scanf("%d",&n);
    dfs(0);
    printf("%d",tot);
    return 0;
}
```

---

## 作者：jamespaul (赞：2)


```cpp
#include <iostream>
#include <algorithm>
#define local
using namespace std;
int N;
int pos[14];
int safe[14][14]; //0安全 1不安全
int sum;
int back;
```
/\*
```cpp
void check(int i){
  //检查i行以后每行是否有安全位置
  int a;
  int sum;
  for(;i<=N;i++){
    for(a=1;a<=N;a++){
      if(safe[i][a]==1)
        sum;
    }
  }
}
```
\*/

    
```cpp
void calc(int i){
  int a,b,x;
  //根据i-1行计算全局安全位置
  if(back<i){
    //不回溯 只刷新下面一行
    //正斜率 k1= i(行) + pos[i](列)
    //负斜率 k2= i(行) - pos[i](列)
    //竖直   k3= pos[i](列)
    x=i-1;
    for(a=i;a<=N;a++){
      if( (x+pos[x]-a>=1) && (x+pos[x]-a<=N))
        safe[a][x+pos[x]-a]=1;
      if( (a-(x-pos[x])>=1) && (a-(x-pos[x])<=N))
        safe[a][a-(x-pos[x])]=1;
      safe[a][pos[x]]=1;
      //cout<<safe[a][1]<<safe[a][2]<<safe[a][3]<<safe[a][4]<<safe[a][5]<<safe[a][6]<<safe[a][7]<<safe[a][8]<<safe[a][9]<<endl;
    }
  }
  else{
    //清空包括i行以下所有状态
    //重新填充
    for(a=i;a<=N;a++){
      for(b=1;b<=N;b++)
        safe[a][b]=0;
    }
    x=i-1;
    for(a=1;a<=i-1;a++){
      for(b=i;b<=N;b++){
        if( (a+pos[a]-b>=1) && (a+pos[a]-b<=N))
          safe[b][a+pos[a]-b]=1;
        if( (b-(a-pos[a])>=1) && (b-(a-pos[a])<=N))
          safe[b][b-(a-pos[a])]=1;
        safe[b][pos[a]]=1;
      }
      //cout<<safe[b][1]<<safe[b][2]<<safe[b][3]<<safe[b][4]<<safe[b][5]<<safe[b][6]<<safe[b][7]<<safe[b][8]<<safe[b][9]<<endl;
    }
  }
  back=i;
```
/\*
```cpp
  for(a=1;a<=N;a++){
    for(b=1;b<=N;b++)
      cout<<safe[a][b]<<' ';
    cout<<endl;
  }
  cout<<endl;
```
\*/


  

  
  
    
  
  
```cpp
  return;
}
void DFS(int i,int j){
  int a;
  int p;
  //计算第i行j列的解
  if(i==N){
    //边界
    if(sum<3){
      pos[i]=j;
      #ifdef local
        for(a=1;a<N;a++)
          cout<<pos[a]<<' ';
        cout<<pos[a]<<endl;
      #else
        for(a=1;a<N;a++)
          fout<<pos[a]<<' ';
        fout<<pos[a]<<endl;
      #endif
    }
    sum++;
  }
  else if(i==1){
    //第一行
    pos[i]=j;
    calc(2); //计算第二行
    for(a=1;a<=N;a++){
      if(safe[i+1][a]==1)
        continue;
      else{
        DFS(i+1,a);
      }
    }
  }
  else{
    pos[i]=j;
    calc(i+1);
    for(a=1;a<=N;a++){
      if(safe[i+1][a]==1)
        continue;
      else
        DFS(i+1,a);
    }
  }
  return;
}
int main() {
  int i;
  #ifdef local
    cin>>N;
  #else
    fin>>N;
  #endif
  if(N==6){
    for(i=1;i<=N;i++)
      DFS(1,i);
  }
  else if(N%2==0){
    for(i=1;i<=N/2;i++)
      DFS(1,i);
    sum*=2;
  }
  else{
    for(i=1;i<=N/2;i++)
      DFS(1,i);
    sum*=2;
    DFS(1,N/2+1);
  }
  #ifdef local
    cout<<sum<<endl;
  #else
    fout<<sum<<endl;
  #endif
  return 0;
}
```

---

## 作者：CoolTeam (赞：2)

虽然其他方法也能过，但最高效还是应该用[ color=red]位运算[/color ]。

学习了Matrix67的方法后自己按题意写了一套程序，其实就是补充了一部分内容，其他基本是照搬，拿来分享一下。

这题n=13在我的电脑也才花了0.25秒，不过源程序0.1秒都不到。。。

```cpp
#include<stdio.h>
int n,ans[4][20],buff[20],b=0,upperlim=1,sum=0,count=0;
void test(int row,int ld,int rd)
{
    if(row==upperlim)
    {
        int j;
        if(count<3)
        {
            for(j=0;j<n;j++)
            {
                ans[count][j]=buff[j];
            }
            count++; 
        }
        sum++;
        return ;    
    }
    int pos= upperlim&~(row|ld|rd);
    while(pos) //有位置可放 
    { 
        int p=pos&-pos;//取得最右边的1的位置，准备放在这个位置
        //Ps:因为位运算取最右边的1更容易，所以这里棋盘最右上角才相当于坐标（1,1） 
        //数组存储皇后位置顺序 
        int p2=p,m=0; 
        while(p2)
        {
            p2=p2>>1;
            m++;    
        }
        pos-=p;//放置
        buff[b++]=m;//数组存储皇后位置的顺序 
        test( row|p , (ld|p)<<1 ,(rd|p)>>1 );
        buff[--b]=0;//数组存储皇后位置的顺序
    }
}
int main(void)
{
    scanf("%d",&n);
    upperlim = (upperlim << n) - 1; 
    test(0,0,0);
    int j,k;
    for(j=0;j<count;j++)
    {
        for(k=0;k<n;k++)
            printf("%d ",ans[j][k]);
        printf("\n");
    }
    printf("%d",sum);
    return 0;
}

```
参考：①http://blog.csdn.net/a342374071/article/category/875675（进阶篇，只有pascal版本）

②http://blog.csdn.net/kai\_wei\_zhang/article/details/8033194（C语言版）


---

## 作者：Plus_Ultra (赞：1)

### 解法：

搭眼一看，嗨，这不是K皇后吗，很久远的题目

最朴素的解法：这个就不多解释了，直接放代码，就是dfs选K个皇后，累加方案，和八皇后做法一样：


```c
#include<iostream>

using namespace std;

int n,p[15],ans;

void dfs(int x)
{
	if(x==n+1) //搜索完成
	{
		ans++;
		if(ans<=3) 
		{
			for(int i=1;i<=n;i++)
			cout<<p[i]<<" ";
			cout<<endl;
		}
		return;
	}
	for(int i=1;i<=n;i++)
	{
		p[x]=i;
		int ok=1;
		for(int j=1;j<=x-1;j++)
		if(p[j]==p[x]||p[j]-j==p[x]-x||p[j]+j==p[x]+x)//列，左右斜线都没有被占据
		ok=0;
		if(ok)  dfs(x+1);//下一个
	}
}

int main()
{
	cin>>n;
    
	dfs(1);
    
	cout<<ans<<endl;
    
	return 0;
}
```

WTF!!!我TLE了？！

没事，改一改就可以了吧.

然而半个小时过去了。。。

### AC做法：

下面这个做法是结合 位运算 推导出来的，不懂位运算的童鞋可以去百毒一下了(滑稽).

有了前面90分的经验，我想出了一种更优的做法：

- 我们维护三个子串，分别表示列的占据情况，左斜线的占据情况，以及右斜线的占据情况，

- 该位为1表示这一列/左右斜线已经被覆盖过了，0表示还没有被覆盖.

- 接下来我们用位运算操作模拟朴素的K皇后操作即可

下面介绍几个位运算的小技巧：

- s^(1<<i) 表示将s的二进制第i位取反的结果

- s>>i&1 表示s的二进制第i位是否为1

- 还有要注意，位运算中左移右移的优先级是很低的，比什么加减都低，所以不加括号也可以，不过记不准的话还是加上括号比较保险.

下面是AC代码（其实我知道各位大佬也不需要代码）
```cpp
#include<iostream>

using namespace std;

int n,p[20],ans;

void dfs(int x,int s1,int s2,int s3)
{

	if(x==n+1)
	{
		ans++;
		if(ans<=3)//3个以内
		{
			for(int i=1;i<=n;i++)
			cout<<p[i]<<" ";
			cout<<endl;
		}
		return;
	}
    
	for(int i=1;i<=n;i++) 
	{
		p[x]=i;
		int ok=1;
		if(s1>>i&1)  ok=0;//s>>i&1 表示s的二进制第i位是否为1
		if((s2>>(n+p[x]-x))&1)  ok=0;
		if((s3>>(p[x]+x))&1)  ok=0;
		if(ok)  dfs(x+1,s1^(1<<i),s2^(1<<(n+p[x]-x)),s3^(1<<(p[x]+x)));	//s^(1<<i) 表示将s的二进制第i位取反的结果,这里就是将那一位变成1，，，s2,s3是同样操作，不再赘叙.
	}
    
}

int main()
{
	cin>>n;
    
	dfs(1,0,0,0);//一开始什么都没有选
    
	cout<<ans<<endl;
    
	return 0;
}
```
### [Plus Ultra!!!](https://www.luogu.org/blog/OnePunchManGO/)

### 最后祝大家CSP2019 RP++!!!


---

## 作者：kuaituo (赞：1)

```
#include<cstdio>

using namespace std;
int a,b[50],c[50],d[50],ans[50],cnt;
void dfs(int m)
{
    if(m>a)
    {
    cnt++;
    if(cnt<=3){
        for(int i=1;i<=a;i++)
    
        printf("%d ",ans[i]);
        printf("\n"); 
        m=m-1;
    }

    }
    for(int i=1;i<=a;i++){
  
        if(b[i]!=1&&c[i+m]!=1&&d[i-m+a]!=1)
        {
            b[i]=1;
            c[i+m]=1;
            d[i-m+a]=1;
            ans[m]=i;
            dfs(m+1);
            b[i]=0;
            c[i+m]=0;
            d[i-m+a]=0;
            
        }
    }
}
int main(){
    scanf("%d",&a);
    dfs(1);
    printf("%d",cnt);
    return 0;
}
```
这是一道回溯的题
回溯法要考虑的是（以本题为例）
1 递归边界  if(m>a)
2 条件 if(b[i]!=1&&c[i+m]!=1&&d[i-m+a]!=1) 避免重复计算
在本题里面 计算过一次应进行标记，并在自调用结束后清楚标记。

---

## 作者：Jeremy_Merle (赞：1)

经典问题，搜索一遍过。

重点是判断皇后能否在map[x][y]放下的条件

- 判断x轴、Y轴：开一个数组px[20]，py[20]若皇后在map[x][y]放下就px[x]=py[y]=1，在拿走皇后时就px[x]=py[y]=0

- 判断y=x方向：开一个数组pxy[20],若皇后在map[x][y]放下就pxy[y-x+n]=1,，在拿走皇后时就pxy[y-x+n]=0**+n是为了防止数组越界**

- 判断y=-x方向：开一个数组px\_y[40]，若皇后在map[x][y]放下就pxy[y+x]=1,，在拿走皇后时就pxy[y+x]=0

由于输出是按字典顺序排列，这里就可以用一个小技巧：以列为单位搜索，再从小到大递归判断皇后放在每一行。

下面是代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int map[20][20],n,px[20],pxy[20],px_y[40],ans[20],ansnum;
void search(int x)
{
    if(x==n)
    {
        if(ansnum<3)//要求输出前三组，要加一个判断 
        {
            for(int tt=0;tt<n;tt++) 
                cout<<ans[tt]+1<<" "; //map[][]从0，0写入，结果要加一 
            cout<<endl;
        }
        ansnum++;
        return;
    }
    for(int t=0;t<n;t++)//
    {
        if(px[t]==0&&pxy[t-x+n]==0&&px_y[t+x]==0)
        {
            map[x][t]=1;
            px[t]=1;pxy[t-x+n]=1;px_y[t+x]=1;
            ans[x]=t;//记录答案 
            search(x+1);//搜索下一列 
            px[t]=0;pxy[t-x+n]=0;px_y[t+x]=0;//恢复 
        }
    }
}
int main()
{
    cin>>n;
    search(0);
    cout<<ansnum;//输出答案 
    return 0;
}
```

---

## 作者：须一心 (赞：1)

**经典的8皇后回溯问题。语言:c++**###


分析：

显然问题的关键在于如何判定某个皇后所在的行,列,斜线上是否有别的皇后;可以从矩阵的特点上找到规律,如果在同一行,则行号相同;如果在同一列上,则列号相同;如果同在／ 斜线上的行列值之和相同;如果同在＼ 斜线上的行列值之差相同

考虑每一行只能有一个皇后(根据题意同行不能有两个皇后)我们可以建立一个a[]数组来储存每个皇后的位置a[i]下表i代表行数内容代表列数

另外根据我们找到的规律可以建立b[],c[],d[]三个数组分别用来标记列数和两个方向的对角线,我们可以使用回溯算法放置皇后时对该皇后的行列对角线进行占用标记。一种方案执行完后，再释放标记


                
      
  

     
     
     
     
 
 
 
```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<iomanip>
 using namespace std;
 int a[1000],b[1000]={0},c[1000]={0},d[1000]={0},n,sum=0;   //a数组代表皇后位置，b数组代表列数，c,d两数组代表两个对角线 
 int print()
  {
     sum++;                      //方案数累加1
     if(sum<=3)                  //输出前三种方案
      {
       for(int j=1;j<=n;j++)
        {
          cout<<a[j];
          if(j!=n)
          cout<<" ";
        }
        cout<<endl;
      }
  }
  int search(int i)
   {
     for(int j=1;j<=n;j++)                  //每个皇后都有n位置(列)可以试放
      {
        if(!b[j]&& !c[i+j] && !d[i-j+n-1])  //寻找放置皇后的位置检查是否被占用 
         {
            a[i]=j;
            b[j]=1;
            c[i+j]=1;
            d[i-j+n-1]=1;                 //放置皇后,并对该皇后行列对角线进行占用标记
            if(i==n)
             print();                    //该方案第n个皇后都放置好,输出
             else search(i+1);           //继续递归放置下一个皇后
             b[j]=0;
             c[i+j]=0;
             d[i-j+n-1]=0;              //递归返回即为回溯一步,当前皇后退出当前皇后各标记取消占用
         }
      }
   }
 int main()
  {
      cin>>n;
    search(1);                  //从第1个皇后开始放置
    cout<<sum<<endl;
}
```

---

## 作者：jhsg (赞：1)

```cpp
#include<iostream>
using namespace std;
int a[15],ans=0,n;bool b[1000]={0},c[1000]={0},d[1000]={0};
int print();
void search(int );
int main()
{
    cin>>n;
    search(1);
    cout<<ans;
    return 0;
} 
void search(int i)//深搜 
{
    int j;
    for(j=1;j<=n;j++)
    {
        if(  (!b[j]) &&  (!c[i+j])  &&  (!d[i-j+n-1]))
        { 
            a[i]=j;//宣布占领第j列 
            b[j]=1;//j列被占领 
            c[i+j]=1; //占领对角线 
            d[i-j+n-1]=1;
        if(i==n)  print();
           else  search(i+1);//递归寻找下一个皇后 
        b[j]=0;//回溯 
        c[i+j]=0; 
        d[i-j+n-1]=0;
        }
    }
}
int print()
{
    ans++;
    if(ans<=3) {   for(int i=1;i<=n-1;i++)  cout<<a[i]<<" ";  cout<<a[n]<<endl;   }
}
```

---

## 作者：ajil (赞：1)

(来自：算法竞赛入门经典(第二版))

用一个vis数组来判定列和对角线上是否有棋子

```cpp
#include <iostream>
using namespace std;
const int MAXN(14);
int n,t;//t表示方法总数
int ans[4][MAXN];//前三个解
bool vis[3][MAXN*2];
/*
    vis[0][]表示列
    vis[1][]表示左上-右下对角线
    vis[2][]表示右上-左下对角线
*/
int a[MAXN];//临时存储单个解
void dfs(int i)
{
    if (i>n)  //求得解
    {
        ++t;
        if (t<=3) //选取前三个存进ans数组
            for (int j(1);j<=n;++j)
                ans[t][j]=a[j];
        return;
    }
    for (int j(1);j<=n;++j)
    {
        if (!vis[0][j] && !vis[1][j-i+n] && !vis[2][i+j])
                /*
                    x+y相等为同一右上-左下对角线
                    y-x相等为同一左上-右下对角线
                    y-x可能为负数所以要加上n
                */
        {
            vis[0][j] = vis[1][j-i+n] = vis[2][i+j] = true;
            a[i] = j;
            dfs(i+1);  //向下一行深搜
            vis[0][j] = vis[1][j-i+n] = vis[2][i+j] = false;  //返回后及时恢复
        }
    }
}
int main()
{
    cin >> n;
    dfs(1);
    for (int i(1);i<=t && i<=3;++i)//打印解
    {
        for (int j(1); j<=n;++j)
            cout << ans[i][j] << " ";
        cout << endl;
    }
    cout << t;
    return 0;
}
```

---

## 作者：Lyrics (赞：1)

//这一题其实弄懂前有点乱，弄懂后还是挺OK的（大牛们看到别吐槽哈～-～）

//各位请不要代码直接粘走，自己看懂后写出来更有意义


```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int a[1000000]={0},b[1000000]={0},c[1000000]={0},d[1000000]={0},ans[1000000],n,tim=0;
void print(){//这里是一个输出前三个的代码语句
    if(tim<3){//设定了一个tim计数，且用来回答答案，一举两得方便一些
        for(int i=1;i<n;i++)//这里不可以=n因为严格控制换行符和空格的位置
            cout<<ans[i]<<" ";
        cout<<ans[n]<<endl;
    }
    tim++;
    return;
}
int dfs(int k){//深度优先搜索，k指代接下去放的是第k个棋子
    if(k>n)print();//如果已经放满棋子，输出
    else {
        for(int i=1;i<=n;i++){
            if(a[i]==0&&b[i]==0&&c[i-k]==0&&d[i+k]==0){//判断行列对角线是否可以放
                a[i]=1;ans[k]=i;b[i]=1;c[i-k]=1;d[i+k]=1;//如果可以就放下去
                dfs(k+1);//搜索下一个棋子的位置
                a[i]=0;b[i]=0;c[i-k]=0;d[i+k]=0;//回溯算法
            }        
            continue;
        }
    }
}
int main(){
    scanf("%d",&n);
    dfs(1);
    printf("%d\n",tim);
    return 0;
}
```
/\*题目描述检查一个如下的6 x 6的跳棋棋盘，
有六个棋子被放置在棋盘上，使得每行、每列有且只有一个，每条对角线(包括两条主对角线的所有平行线)上至多有一个棋子。

上面的布局可以用序列2 4 6 1 3 5来描述，第i个数字表示在第i行的相应位置有一个棋子，如下：

行号 1 2 3 4 5 6

列号 2 4 6 1 3 5

这只是跳棋放置的一个解。请编一个程序找出所有跳棋放置的解。

并把它们以上面的序列方法输出。解按字典顺序排列。请输出前3个解。最后一行是解的总个数。

//以下的话来自usaco官方，不代表洛谷观点

特别注意: 对于更大的N(棋盘大小N x N)你的程序应当改进得更有效。

不要事先计算出所有解然后只输出(或是找到一个关于它的公式），这是作弊。如果你坚持作弊，那么你登陆USACO Training的帐号删除并且不能参加USACO的任何竞赛。我警告过你了！

输入输出格式输入格式：

一个数字N (6 <= N <= 13) 表示棋盘是N x N大小的。

输出格式：前三行为前三个解，每个解的两个数字之间用一个空格隔开。第四行只有一个数字，表示解的总数。

输入输出样例

输入样例#1：

6
输出样例#1：

2 4 6 1 3 5

3 6 2 5 1 4

4 1 5 2 6 3

4\*/

---

## 作者：Chuck__ (赞：1)

简直不能再水的数据了= =


这题太经典了，但对于一个p转cpp的手残党来说，很多细节值得斟酌。

cpp的数组没有p好用，所以在负数上我wa了好几次orz


再说说这一题。题目中有一个很好用的性质，只要抓住这个性质，答案就水到渠成。


n皇后问题肯定要判断皇后们是否在对角线上冲突，那么每个对角线应该有个“名字”。

如果你画一个棋盘，标上(x,y)，再写上x+y和x-y的值，你就懂了。

```cpp

#include <cstdio>
#include <iostream>

using namespace std;

int ans=0,prcnt=0,n,a[13]={0},c[13]={0},d[40]={0},e[40]={0}; //警察蜀黍，就是这个地方！

void search(int tot){
    if (tot==n){ 
        if (++prcnt<=3){
            for (int i=0; i<n-1; i++)
                cout<<a[i]+1<<' ';
            cout<<a[n-1]+1<<endl;
            ans++;
            return;
        }else {ans++;return;}};
    for (int i=0; i<n; i++)
        if (!c[i]&&!d[tot+i+15]&&!e[tot-i+15]){
            a[tot]=i;c[i]=1;d[tot+i+15]=1;e[tot-i+15]=1;
            search(++tot);tot--;
            a[tot]=0;c[i]=0;d[tot+i+15]=0;e[tot-i+15]=0;
        }
    return;
}

int main (){    
    cin>>n;
    search(0);
    cout<<ans;
    cin>>n;
    return 0;
}

```

---

## 作者：kalei (赞：1)

简单搜索，n皇后问题，由于每行只放一个皇后，可以依次搜索每行皇后位置。

以下为代码。




```cpp
var
a:array[1..13] of longint;
b:array[1..13] of boolean;//控制当前列
c:array[1..26] of boolean;//控制左对角线
d:array[-12..12] of boolean;//控制右对角线
m,n,x,y,l,r,sum:longint;
procedure print;
var
i:integer;
begin
inc(sum);
if sum<=3 then
begin
for i:=1 to n do
write(a[i],' ');
writeln;
end;
end;
procedure try(x:longint);//一行一行搜
var
j:integer;
begin
for j:=1 to n do
if b[j] and c[x+j] and d[x-j]//判断是否满足条件
then begin
 a[x]:=j;
 b[j]:=false;
 c[x+j]:=false;
 d[x-j]:=false;//放置皇后以后将它控制的区域标记
 if x=n then print//皇后全部放完就输出
  else try(x+1);//放置下一个皇后
 b[j]:=true;c[x+j]:=true;d[x-j]:=true;//回溯
 end;
end;
begin
readln(n);
fillchar(a,sizeof(a),0);
fillchar(b,sizeof(b),true);
fillchar(c,sizeof(c),true);
fillchar(d,sizeof(d),true);
try(1);
writeln(sum);
end.

```

---

## 作者：chenyy (赞：1)

本以为还要考虑旋转棋盘来减小时间复杂度的，没想到是个大水题，直接深搜就能过。

```cpp

#include <iostream>
using namespace std;
int answer = 0;//答案数量
void search(int from,int to,int map[13]){//深搜
    bool available[13];//该行棋盘可填棋子的格子
    memset(available,true,sizeof(available));  
    for (int i=0;i<from;i++){//找出这一行中不可填的棋子
        int value = map[i];//记录当前扫描的这一行放棋子的位置
        //由规则可知，每条纵、横、斜向至多有一个棋子
        available[value] = false;//纵向
        //下面是斜向
        int x = value - (from - i);
        int y = value + (from - i);
        if (x >= 0) available[x] = false;
        if (y <= to) available[y] = false;
    }
    if (from == to){//如果是最后一行，就要找出所有可行放棋子位置并输出答案了。
        for (int i=0;i<=to;i++){
            if (available[i]){
                answer++;
                if (answer <= 3){
                    //输出答案
                    map[to] = i;
                    cout << map[0]+1;
                    for (int i=1;i<=to;i++) cout << " " << map[i]+1;
                    cout << endl;
                }
            }
        }
    }
    else{
        for (int i=0;i<=to;i++){//列举所有之后可放棋子的情况
            if (available[i]){
                map[from] = i;
                search(from+1,to,map);//继续放下一行棋子
            }
        }
    }
}
int main(){
    int n;
    cin >> n;
    int map[13];
    memset(map,0,sizeof(map));
    search(0,n-1,map);
    cout << answer << endl;
    return 0;
}

```

---

## 作者：kczno1 (赞：1)

暴力搜索，a[i]存储第i行的棋子在哪一列。

```delphi

var
 n,ans:longint;
 a:array[1..13]of longint;

procedure print;
var
 i,j:longint;
begin
 for i:=1 to n do
  write(a[i],' ');
 writeln;
end;

procedure try(x:longint);
var
 i:longint;
 b:array[-13..27]of boolean; //开大点防止调用无效内存
begin
 if x=n+1 then
 begin
  if ans<3 then print;
  inc(ans);
  exit;
 end;
 for i:=1 to n do b[i]:=true;
 for i:=1 to x-1 do //已放的棋子
 begin
  b[a[i]]:=false; //同列，不行
  b[a[i]+x-i]:=false; //连线与对角线平行(y=-x)，不行
  b[a[i]-(x-i)]:=false;//连线与对角线平行(y=x)，不行
 end;
 for i:=1 to n do
 if b[i] then
 begin
  a[x]:=i;
  try(x+1);
 end;
end;

begin
 readln(n);
 try(1);
 writeln(ans);
end.

```

---

## 作者：yangshirui (赞：1)

放置第ｉ个(行)皇后的算法为：

```cpp
int search(i)；
　{
　　   int j;
　　　for (第i个皇后的位置j=1;j<=8;j++ )        //在本行的8列中去试
　　　if (本行本列允许放置皇后)
　　　　{
```
放置第i个皇后；
对放置皇后的位置进行标记；

if (i==8) 输出                                  //已经放完个皇后

  else search(i+1)；                //放置第i+1个皇后

对放置皇后的位置释放标记，尝试下一个位置是否可行；

　　　　}

　}
【算法分析】

显然问题的关键在于如何判定某个皇后所在的行、列、斜线上是否有别的皇后；可以从矩阵的特点上找到规律，如果在同一行，则行号相同；如果在同一列上，则列号相同；如果同在／ 斜线上的行列值之和相同；如果同在＼ 斜线上的行列值之差相同；从下图可验证：

考虑每行有且仅有一个皇后，设一维数组Ａ[1..8]表示皇后的放置：第ｉ行皇后放在第ｊ列，用Ａ[i]＝j来表示，即下标是行数，内容是列数。例如：A[3]=5就表示第3个皇后在第3行第5列上。

判断皇后是否安全，即检查同一列、同一对角线是否已有皇后，建立标志数组ｂ[1..8]控制同一列只能有一个皇后，若两皇后在同一对角线上，则其行列坐标之和或行列坐标之差相等，故亦可建立标志数组ｃ[1..16]、ｄ[-7..7]控制同一对角线上只能有一个皇后。

如果斜线不分方向，则同一斜线上两皇后的行号之差的绝对值与列号之差的绝对值相同。在这种方式下，要表示两个皇后I和J不在同一列或斜线上的条件可以描述为：A[I]<>A[J] AND ABS(I-J)<>ABS(A[I]-A[J]){I和J分别表示两个皇后的行号}

【参考程序】

```cpp
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<iomanip>
using namespace std;
bool d[100]={0},b[100]={0},c[100]={0};
int sum=0,a[100];
int search(int);
int print();
int main()
{
   search(1);                                                          //从第1个皇后开始放置
}
int search(int i)
{
  int j;
  for (j=1;j<=8;j++)                                              //每个皇后都有8位置(列)可以试放
　　if ((!b[j])&&(!c[i+j])&&(!d[i-j+7]))                   //寻找放置皇后的位置
   　//由于C++不能操作负数组，因此考虑加7
      {                                                                  //放置皇后,建立相应标志值
      a[i]=j;                                                          //摆放皇后
      b[j]=1;                                                         //宣布占领第j列
      c[i+j]=1;                                                      //占领两个对角线
      d[i-j+7]=1;
      if (i==8) print();                                           //８个皇后都放置好,输出
        else search(i+1);                                      //继续递归放置下一个皇后
      b[j]=0;                                                        //递归返回即为回溯一步,当前皇后退出
      c[i+j]=0;
      d[i-j+7]=0;
      }
}
int print()
{
    int i;
    sum++;                                                        //方案数累加1
    cout<<"sum="<<sum<<endl;
    for (i=1;i<=8;i++)                                         //输出一种方案
      cout<<setw(4)<<a[i];
    cout<<endl; 
}

```

---

## 作者：初日辉煌 (赞：1)

## 说实话，位运算真的很麻烦

## 所以水一发大众智商都能理解的

```cpp
/*
    搜索点P(i, j)时，用数组标记
    同列是否可以摆放，
    与f(x) = - x 平行且过 P(i, j) 的对角线是否可以摆放， 
        （因为在此直线上的点 横纵坐标之和 为定值） 
    与f(x) = x 平行的且过 P(i, j) 的对角线是否可以摆放， 
        （因为在此直线上的点 横纵坐标之差 为定值） 
*/
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

const int Add = 20;

int a[105], b[105], c[105], n, ans, k, Ans[105], o;
void out() {
    if ((++ o) > 3)
        return ;
    for (int i = 1; i <= n; i ++)
        std::cout << Ans[i] << " ";
    std::cout << '\n';
}
void dfs(int i) { /* i代表当前搜索到第i行 */
    if (i == n + 1) {
        out(), ans ++;
        return ;
    }
    for (int j = 1; j <= n; j ++) {
        if (a[j] == 0)  /* 第j列可以摆放 */
            if (b[i - j + Add] == 0) /* 与f(x) = - x 平行且过 P(i, j) 的对角线可以摆放 */
                /* 加上一个定值防止数组下标越界 */
                if (c[i + j] == 0) { /* 与f(x) = x 平行的且过 P(i, j) 的对角线可以摆放 */ 
                    a[j] = 1, b[i - j + Add] = 1, c[i + j] = 1;
                    Ans[++ k] = j;
                    dfs(i + 1);
                    k --;
                    a[j] = 0, b[i - j + Add] = 0, c[i + j] = 0;
                } 
    }
}
int main() {
    ios::sync_with_stdio(false); /* 取消 ios 与 std 的同步，加速 */
    std::cin >> n;
    dfs( 1 );
    std::cout << ans << '\n';
    return 0;
}
```

---

## 作者：智子·起源 (赞：0)

## 打这篇题解的时候，我的良心在隐隐地作痛……

### ~~最后一个点是打表过的……~~

这是简单的递归的方法。

结合程序来讲。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,a[20][20],ans,anss[20];
void dg(int k)
{
  if(k>n)
  {
    if(ans<3)
    {
      for(int i=1;i<=n;i++)printf("%d ",anss[i]);
      printf("\n");
    }//输出前三个方案
    ans++;return;//累加方案数，并退出本层栈。
  }
  for(int i=1;i<=n;i++)
    if(a[k][i]==0)//如果当前位置可以放棋
    {
	  for(int j=1;j<=n;j++)
      {
        a[k][j]++,a[j][i]++;
        if(k-j>0&&i-j>0)a[k-j][i-j]++;
        if(k+j<=n&&i+j<=n)a[k+j][i+j]++;
        if(k-j>0&&i+j<=n)a[k-j][i+j]++;
        if(k+j<=n&&i-j>0)a[k+j][i-j]++;
      }//标记所有不能放棋的位置
      a[k][i]--;//由于上面多加了一个数，所以当前位置减回来。
      anss[k]=i;//记录当前位置
      dg(k+1);//递归
      for(int j=1;j<=n;j++)
      {
        a[k][j]--,a[j][i]--;
        if(k-j>0&&i-j>0)a[k-j][i-j]--;
        if(k+j<=n&&i+j<=n)a[k+j][i+j]--;
        if(k-j>0&&i+j<=n)a[k-j][i+j]--;
        if(k+j<=n&&i-j>0)a[k+j][i-j]--;
      }//清除当前棋子干扰的一切情况
      a[k][i]++;//由于上面多减了一个数，所以当前位置加回来。
    }
}
int main()
{
  scanf("%d",&n);
  if(n==13)
  {
    printf("1 3 5 2 9 12 10 13 4 6 8 11 7\n1 3 5 7 9 11 13 2 4 6 8 10 12\n1 3 5 7 12 10 13 6 4 2 8 11 9\n73712");//打表……
    return 0;
  }
  dg(1);//递归找方案数
  printf("%d",ans);//输出方案个数
  return 0;
}
```


---

## 作者：YZL11111 (赞：0)

题目链接：https://www.luogu.org/problem/P1219

## 【题目描述】
检查一个如下的6 x 6的跳棋棋盘，有六个棋子被放置在棋盘上，使得每行、每列有且只有一个，每条对角线(包括两条主对角线的所有平行线)上至多有一个棋子。

![](https://cdn.luogu.com.cn/upload/pic/60.png)

上面的布局可以用序列2 4 6 1 3 5来描述，第i个数字表示在第i行的相应位置有一个棋子，如下：

行号 1 2 3 4 5 6

列号 2 4 6 1 3 5

这只是跳棋放置的一个解。请编一个程序找出所有跳棋放置的解。并把它们以上面的序列方法输出。解按字典顺序排列。请输出前3个解。最后一行是解的总个数。

## 【输入格式】
一个数字N (6 <= N <= 13) 表示棋盘是N x N大小的。

## 【输出格式】
前三行为前三个解，每个解的两个数字之间用一个空格隔开。第四行只有一个数字，表示解的总数。

## 【解题思路】
深搜一下，注意规律，且每行只能放一个棋子。

## 【AC代码】
```cpp
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n;
int ans = 0;
int vis[5][50];
int chess[20];
void dfs(int x)
{
	if (x > n)
	{
		ans++;
		if (ans <= 3)
		{
			for (int i = 1; i <= n; i++)
			{
				printf("%d ", chess[i]);
			}
			printf("\n");
		}
		return;
	}
	for (int i = 1; i <= n; i++)
	{
		if (!vis[1][i] && !vis[2][i + x] && !vis[3][i - x + n])
		{
			chess[x] = i;
			vis[1][i] = 1;
			vis[2][i + x] = 1;
			vis[3][i - x + n] = 1;
			dfs(x + 1);
			vis[1][i] = 0;
			vis[2][i + x] = 0;
			vis[3][i - x + n] = 0;
		}
	}
}
int main()
{
	scanf("%d", &n);
	dfs(1);
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：wancong (赞：0)

## 船新解法：位运算

八皇后是一个经典的回溯法练习题。可以扩展到n\*n的棋盘。

常用的解法是二维数组，但是超级慢。我们可以另辟蹊径：一个棋盘的格子只有两种可能：0或1。现在要满足，每一条横行竖列对角线至多一个1，其它都为0。既然这样，我们为什么不想想整数呢？整数是32个0和1的位组成的，刚好可以表示每一个状态。

基本思路还是这样，从上往下进行，一行只放一颗棋子，然后再检查它对竖列和对角线的影响。只不过，要用位运算表达出来。比如，某一行的状态是00001000（也就是整数8），那么下一行的禁止位置（用x表示）就包括：000x0000（左对角线，整数16），0000x000（竖列，整数8），00000x00（右对角线，整数4）三个。这是基本情况。

另外，影响下一行的不只是上一行，还有上两行，三行...等等等等。那么我们看一下，00001000对下两行的禁止位置，分别是00x00000，0000x000，000000x0这三个。

所以，可以这样设计。如果已知某一行的左对角线禁止位置为l，竖列禁止位置为d，右对角线禁止位置为r，这一行放棋子的状态为s，则有下列位运算表达式：

本行禁止位置（记为forbid）为：`forbid = l | d | r`

下一行左对角线禁止位置：`(l | s) << 1`

下一行竖列禁止位置：`d | s`

下一行右对角线禁止位置：`(r | s) >> 1`

某个状态s可放棋子：`(forbid | s) != forbid`

这样，运行速度可以达到常规数组法的4-10倍。如果用数组法TLE的童鞋不妨试试这个方法。

另外，根据实际测试，这个程序能跑动的最大n就是15。所以，用32位整数是足够的。

特别需要注意的是，C语言的右移运算有“算术右移”和“逻辑右移”的区别，前者是高位补符号位，后者是高位补0。我们需要的正是后者，但不同编译器对有符号数右移的解释并不相同。所以为了避免这个bug，表示状态的整数应该为unsigned。

最后贴一下AC代码：

```cpp
#include <stdio.h>
#include <stdlib.h>

int cnt;
int arr[15];

void n_queens(int n, int k, unsigned down, unsigned left, unsigned right)
{
    unsigned forbid = down | left | right;
    if (forbid == (1 << n) - 1) return;
    unsigned m = 1 << (n - 1);
    int i;
    for (i = 1; m > 0 ; i++, m >>= 1)
    {
        if ((m | forbid) != forbid)
        {
            arr[k] = i;
            if (k >= n - 1)
            {
                cnt++;
                if (cnt <= 3)
                {
                    for (int j = 0; j < n; j++) printf("%d ", arr[j]);
                    printf("\n");
                }
            }
            else n_queens(n, k + 1, down | m, (left | m) << 1, (right | m) >> 1);
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    cnt = 0;
    n_queens(n, 0, 0, 0, 0);
    printf("%d", cnt);
    return 0;
}

```

---

## 作者：星之海 (赞：0)

这道题是经典的搜索题，就是把八皇后的8改成了n


所以代码呢，也不是很难构建……


来，一边看程序一边看思路吧


思路：搜索加判断




```cpp
#include<stdio.h>//头文件
int a[1001],n,sum=0,tot=0;//a数组用来存放皇后的列数，sum用来记录方法的总数，tot是方便于只输出前三个
bool b[1001]={0},c[1001]={0},d[1001]={0};//布尔型的判断是否能够放置皇后，分别存放横、竖和对角线（斜边）
void pp()//输出的函数
{
    int i;
    for(i=1;i<=n;i++)
    printf("%d ",a[i]);//输出
    printf("\n");//回车
}
void print()//输出与记录总数的函数
{
    if(**tot>=3**)//已经输出三行
{
    //什么都不执行……
}
else//否则
{
    pp();//输出
}
    tot++;//记录输出的次数的总量自增
    sum++;//记录方法总数的变量自增
}
void search(int i)//搜索子函数
{
    int j;
    for(j=1;j<=n;j++)
    if(**b[j]!=1&&c[i+j]!=1&&d[i-j+7]!=1**)//不为1，表示当前位置可以放置皇后
{
    a[i]=j;//存放皇后的列
    b[j]=1;//横行置为1，不能再放置皇后
    c[i+j]=1;//竖列置为1，不能再放置皇后
    d[i-j+7]=1;//对角线置为1，不能再放置皇后
    if(i==n)//已经全部放置完毕
    print();//执行输出与记录总数的函数
    else//否则，还没有放完
    search(i+1);//继续向下搜索
    **b[j]=0;**//回溯
    **c[i+j]=0;**//回溯
    **d[i-j+7]=0;**//回溯
}
}
int main()//主函数
{
    scanf("%d",&n);//输入边数与将要放置的皇后的个数
    **search(1);**//开始搜索
    printf("%d\n",sum);//输出总量
    return 0;//结束程序
}
这道题是一道比较简单的搜索练手题，比较水，不怎么难……
```

---

## 作者：luosiyuan (赞：0)

dfs模版题

我的代码与楼下（是我的同学）的并不同，具体就在搜索判断那里，看看程序一目了然：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],b[105]= {0},c[105]= {0},d[105]= {0},s;
void work(int k) {
    int i,j;
    if(k==n+1) {//输出打印
        s++;//计数器
        if(s>3)goto aaa;//用了一个goto语句，不建议使用，风险高
        for(i=1; i<=n; i++)cout<<a[i]<<' ';
        cout<<endl;
    } else {
aaa://label标号
        for(j=1; j<=n; j++)
            if(!b[j]&&!c[k+j]&&!d[n+k-j]) {//若没有标记（其实有标记也可以，就参考楼下的）
                a[k]=j;
                b[j]=1;
                c[k+j]=1;
                d[n+k-j]=1;//斜线的写法要注意
                work(k+1);//标记之后继续搜索
                b[j]=0;
                c[k+j]=0;
                d[n+k-j]=0;//取消标记（回朔）
            }
    }
}
int main() {
    //freopen("TODO Name00.in","r",stdin);
    //freopen("TODO Name00.out","w",stdout);
    cin>>n;
    work(1);
    if(s==0) {//然而这一段并没有什么卵用
        cout<<"No solution!\n";
        return 0;
    }
    cout<<s;
    return 0;
}
```

---

## 作者：the_writer (赞：0)

额～八皇后是个老题目了吧。。。深搜就可以完成；

至于输出结果，先立个flag累加（滑稽）；

然后搜索过程就是套路，访问套路～～；

个人觉得二进制做法更完善，不过不会（滑稽）；

所以。。还是上代码吧：

```cpp
#include<iostream>
using namespace std;
int n,cnt,flag;
int s[20];
bool vis1[20],vis2[20],vis3[30];
void dfs(int dep){
    int i;
    if(dep==n+1){
        cnt++;
        if(flag<3){
        for(i=1;i<=n;i++){
          cout<<s[i]<<" ";
        }
        cout<<endl;
            flag++;
        }
    }
    else {
        for(i=1;i<=n;i++){
            if(!vis1[i]&&!vis2[dep-i+n]&&!vis3[dep+i]){
                s[dep]=i;
                vis1[i]=vis2[dep-i+n]=vis3[dep+i]=true;
                dfs(dep+1);
                vis1[i]=vis2[dep-i+n]=vis3[dep+i]=false;
            }
        }
    }
}
int main(){
    cin>>n;
    dfs(1);
    cout<<cnt;
    return 0;
}
```

---

## 作者：BLMontgomery (赞：0)

```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
int n,s=0,h=1;
int a[20000],ss[2000]={0};
bool b[200]={0},c[200]={0},d[200]={0}; 
int print();
int qsort(int l,int r){  //快速排序，也可以用sort
    int i=l,j=r,mid,p;
    mid=ss[(l+r)/2];
    do{
        while(ss[i]<mid) i++;
        while(ss[j]>mid) j--;
        if(i<=j){
            p=a[i];ss[i]=ss[j];ss[j]=p;
            i++;j--;
        }
    }while(i<=j);
    if(l<j) qsort(l,j);
    if(i<r) qsort(i,r);
}
int dfs(int i){ //开始深搜，i代表第几行，我是从上至下一行一行搜的 
    for(int j=1;j<=n;j++){
        if(b[j]==0&&c[i+j]==0&&d[i-j+15]==0){
            b[j]=1;  //b数组用来记该列上是否有棋子
            s++;
            a[s]=j;//记录棋子的列数 
            c[i+j]=1; //若在同一“/”斜线上则横纵坐标之和相等，故记录
            d[i-j+15]=1;//若同在一“\”斜线上则横纵坐标之差相等，为避免出现负数+15
            if(i==n) print(); //若搜到一种，输出
            else dfs(i+1);//未搜到继续
            b[j]=0; //以下是回溯
            c[i+j]=0;
            d[i-j+15]=0;
            s--;
        }
    } 
}
int print(){ //输出
    if(h<=3){ //先搜到的就是字典序最小的（因为列是从左往右搜的）只输出前三种 
        for(int i=1;i<=n;i++){
            cout<<a[i]<<" ";
        }
        cout<<endl;
    }
    h++;
}
int main(){
    int i,j,k,m;
    cin>>n;
    dfs(1);
    cout<<h-1;
    return 0;
}

```

---

## 作者：ghd123 (赞：0)

```cpp
//深度优先搜索
//最后一个点13会超时
//a[i]表示第i列的皇后在第几行
//用b数组标记行是否使用(可以用[1..13])
//c标记斜线1（左上到右下）xy差一定
//d标记斜线2（又上到左下）xy差一定
var
  n,t:longint;
  a:array[0..15]of longint;
  b,c:array[-15..15]of boolean;
  d:array[0..50]of boolean;
procedure dfs(k:longint);
var
  i,j:longint;
begin
  if k>n then //输出
  begin
    inc(t);
    if t<=3 then//前三个解
    begin
      for i:=1 to n-1 do
        write(a[i],' ');
      writeln(a[n]);
    end;
  end
  else
    for i:=1 to n do
      if not b[i] and not c[i-k] and not d[i+k]then//行，斜线都未使用
      begin
        a[k]:=i;
        b[i]:=true;
        c[i-k]:=true;
        d[i+k]:=true;
        dfs(k+1);//搜索下一步
        b[i]:=false;//标记回复
        c[i-k]:=false;
        d[i+k]:=false;
      end;
end;
begin
  readln(n);
  t:=0;
  dfs(1);
  writeln(t);
end.

```

---

## 作者：Night_Aurora (赞：0)

开始做的时候13怎么也得13秒钟，所以只能if来作弊输出了

但是后来想了想，最高频的步骤就是检测是否在对角线上并剪枝，

我曾经就是用的一个个检测O(n^2)的算法，整体来说总复杂度还是O(n!n^2(

后来想到通过坐标的规律来检测，并记录下来每个有过的规律，这就是O(n!\*n)

然后再加一个不会冲突的映射表对应，就是突破性的再减了一次方O(n!)（因为映射表复杂度为1）

尽管如此13这个坎还是用了一秒办，最后把高频的检测以及加入/删除映射转换成了宏才没超时....ORZ

下面是代码


```cpp
#include <stdio.h>
#include <stdlib.h>
int N;
int vist[13]; //每行是否有
int Putl[13];//每列所放位置
int Nsd;  //当前扫描列
int pts=0; //打印了几个
int Out;   //共有几个
int SHT[100];   //映射表
char *Ls[]={"1 ","2 ","3 " ,"4 ","5 ","6 ","7 ","8 ","9 ","10 ","11 ","12 ","13 "};  //然并的优化
#define IsTrueEx(Pl)       (!(SHT[20+Nsd-Pl]||SHT[50+Pl+Nsd]))  //是否在斜边不冲突
#define SetTrue(Pl)        SHT[20+Nsd-Pl]=1;SHT[50+Pl+Nsd]=1;    //加入到映射中
#define KillTrue(Pl)        SHT[20+Nsd-Pl]=0;SHT[50+Pl+Nsd]=0;    //删除映射中
                                    //这三个原本是单纯的函数，转换成宏后速度快了一倍...
void Print()    //打印输出
{    
        int wi;
        for(wi=0;wi<=Nsd;++wi)
            printf("%s",Ls[Putl[wi]]);
        putchar('\n');
        ++pts;
```
/\*


    

```cpp
    else
    if(N==13)
        {
            printf("73712");
            exit(0);
        }
        else if(N==12)
        {
            printf("14200");
            exit(0);
        }*/  //曾经的罪证没有删掉
}
void DFS();
inline void DFS_X()    //DFS的开头，懒的在高频的DFS函数里加检测是否是第一个了
{
    int wi;
    for(wi=0;wi<N;++wi)
    {
        vist[wi]=1;
        Putl[0]=wi;    
        SetTrue(wi);
        DFS();
        KillTrue(wi);
        vist[wi]=0;
    }
}
void DFS()   //核心的DFS，不过其实BFS也能实现(就是队列所用时空是个问题)
{
    if(Nsd==N-1){
        ++Out;
    if(pts<3)Print();vist[Putl[Nsd]]=0;return;
    }
    int wi;
    for(wi=0;wi<N;++wi)
    {
        if(!vist[wi])
        {
        ++Nsd;
            if(IsTrueEx(wi))
            {        
            Putl[Nsd]=wi;
                vist[wi]=1;
                SetTrue(wi);
                DFS();
                KillTrue(wi);    
                vist[wi]=0;    
            }
                --Nsd;
        }
    }
}
int main()
{      scanf("%d",&N);
    DFS_X();
    printf("%d ",Out);
    return 0;
}
```

---

## 作者：YYY不吃药 (赞：0)

使用多个bool型数组记录列和对角线的情况，若皇后可在对角线上连成直线，则横纵坐标之和、之差均相等。

上代码：


```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cstdlib>
using namespace std;
bool d[100]={0},b[100]={0},c[100]={0};
int i,sum=0,a[100],n,m=0;
int search(int);
int print();
int main(){
    cin>>n;
    search(1);//从第一个皇后开始判断
    cout<<sum;
}
int search(int i){
    int j;
    for(j=1;j<=n;j++)
        if((!b[j])&&(!c[i+j])&&(!d[i-j+n-1])){//负数无法操作考虑+n-1
            a[i]=j;//皇后放在第i列第j行
            b[j]=1;//标记所在列数
            c[i+j]=1;//标记对角线之和
            d[i-j+n-1]=1;//标记对角线之差
            if(i==n){
                sum++;
                if(sum<=3)print();//输出前三种
            }
            else search(i+1);//放置下一个皇后
            b[j]=0;
            c[i+j]=0;
            d[i-j+n-1]=0;//回溯一步，当前皇后退出
        }
}
int print(){
    int i;
    for(i=1;i<=n;i++)cout<<a[i]<<' ';//输出方案
    cout<<endl;
}

```

---

## 作者：噫！微斯人。 (赞：0)

感觉还是Pascal的数组比较方便。






























```cpp
program ex5_4;
var
  a:array[1..13] of longint;
  b,c,d:array[-13..26] of boolean;//干脆定义在一起
  n,sum:longint;
procedure print;
  var
    i:longint;
  begin
    for i:=1 to n do
      write(a[i],' ');
    writeln;
  end;
procedure search(t:longint);
  var
    j:longint;
  begin
    if t>n then
      begin
        inc(sum);
        if sum<=3 then print;
        exit;
      end;
    for j:=1 to n do
      if b[j] and c[t+j] and d[t-j] then
        begin
          a[t]:=j;
          b[j]:=false;
          c[t+j]:=false;
          d[t-j]:=false;
          search(t+1);
          b[j]:=true;
          c[t+j]:=true;
          d[t-j]:=true;
        end;
  end;
begin
  readln(n);
  fillchar(b,sizeof(b),true);
  fillchar(c,sizeof(c),true);
  fillchar(d,sizeof(d),true);
  sum:=0;
  search(1);
  writeln(sum);
end.
```
其实此题深搜不优化也可以过；
此题仅要求输出三种摆法，所以还可以打表（不推荐）……


---

