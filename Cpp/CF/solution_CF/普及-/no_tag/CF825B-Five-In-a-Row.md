# Five-In-a-Row

## 题目描述

Alice and Bob play 5-in-a-row game. They have a playing field of size $ 10×10 $ . In turns they put either crosses or noughts, one at a time. Alice puts crosses and Bob puts noughts.

In current match they have made some turns and now it's Alice's turn. She wonders if she can put cross in such empty cell that she wins immediately.

Alice wins if some crosses in the field form line of length not smaller than 5. This line can be horizontal, vertical and diagonal.

## 样例 #1

### 输入

```
XX.XX.....
.....OOOO.
..........
..........
..........
..........
..........
..........
..........
..........
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
XXOXX.....
OO.O......
..........
..........
..........
..........
..........
..........
..........
..........
```

### 输出

```
NO
```

# 题解

## 作者：时律 (赞：2)

~~乍看无脑暴力，还真是无脑暴力~~

思路很简单：枚举每一个地方放下棋子后会不会获得胜利。

判断时注意只用扫放下棋子这块区域即可，否则可能会`TLE`。

~~判断好难写啊~~

```
#include<bits/stdc++.h>
using namespace std;
char x[15][15];
void f(int n,int m)
{
	for(int j=1;j<=6;j++)//横着判断
		if(m>=j and m<=j+4)
		{
			int flag=0;
			for(int k=j;k<=j+4;k++)
				if(x[n][k]!='X')
				{
					flag=1;
					break;
				}
			if(flag==0)
			{
				cout<<"YES";
				exit(0);//强制结束程序
			}
		}
	for(int i=1;i<=6;i++)//竖着判断
		if(n>=i and n<=i+4)
		{
			int flag=0;
			for(int k=i;k<=i+4;k++)
				if(x[k][m]!='X')
				{
					flag=1;
					break;
				}
			if(flag==0)
			{
				cout<<"YES";
				exit(0);
			}
		}
	for(int u=-4;u<=0;u++)//左上右下判断
	{
		int flag=0;
		for(int k=u;k<=u+4;k++)
			if(x[n+k][m+k]!='X')
			{
				flag=1;
				break;
			}
		if(flag==0)
		{
			cout<<"YES";
			exit(0);
		}
	}
	for(int u=-4;u<=0;u++)//左下右上判断
	{
		int flag=0;
		for(int k=u;k<=u+4;k++)
			if(x[n+k][m-k]!='X')
			{
				flag=1;
				break;
			}
		if(flag==0)
		{
			cout<<"YES";
			exit(0);
		}
	}
   //四个判断只要有一个符合即可
}
int main()
{
	for(int i=1;i<=10;i++)
		for(int j=1;j<=10;j++)
			cin>>x[i][j];
	for(int i=1;i<=10;i++)//暴力枚举
		for(int j=1;j<=10;j++)
			if(x[i][j]=='.')
			{
				x[i][j]='X';
				f(i,j);
				x[i][j]='.';
			}
	cout<<"NO";
}
```

---

## 作者：hensier (赞：1)

~~暴力出奇迹。——某大佬~~

由于五子棋盘大小为$10\times10$，因此我们可以暴力。~~当然，即使是暴力，也要有暴力的思路。~~

首先，如果要达成五个子，那么目前，棋盘上必须有至少四个$X$子。因此，我们对这个可以进行特判。

```cpp
int count()
{
    int s=0;
    for(int i=0;i<10;i++)for(int j=0;j<10;j++)s+=c[i][j]=='X';
    return s;
}
```

以上函数用于返回棋盘上$X$子的个数，如果最终$count()<4$，则不可能达成要求，于是输出$NO$并直接退出。

接着我们可以在$i∈[0,10),j∈[0,10)$区间（即每一个子）进行搜查。如果这个字符不是$X$就不进行判断，否则通过方向增量数组进行搜查，如果总共（包括原来的$X$）正好有$4$个$X$和$1$个$.$，就说明可以达成，输出$YES$。

$AC$代码：

```cpp
#include<cstdio>
char c[11][11];
int a[]={-1,-1,-1,0,0,1,1,1},b[]={-1,0,1,-1,1,-1,0,1},n,m;//方向增量数组
int count()
{
    int s=0;
    for(int i=0;i<10;i++)for(int j=0;j<10;j++)s+=c[i][j]=='X';
    return s;
}
int main()
{
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)scanf("%c",&c[i][j]);
        getchar();//scanf会读入换行，所以getchar接收掉
    }
    if(count()<4)//特判
    {
        printf("NO");
        return 0;
    }
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(c[i][j]-'X')continue;//不是X就不判断
            for(int k=0;k<8;k++)
            {
                int A=a[k],B=b[k],i1=i+A,j1=j+B,i2=i1+A,j2=j1+B,i3=i2+A,j3=j2+B,i4=i3+A,j4=j3+B;//分别标记
                if(i1<0||i1>9||i2<0||i2>9||i3<0||i3>9||i4<0||i4>9||j1<0||j1>9||j2<0||j2>9||j3<0||j3>9||j4<0||j4>9)continue;//只要有一个在棋盘外就不再进行判断
                n=(c[i1][j1]=='X')+(c[i2][j2]=='X')+(c[i3][j3]=='X')+(c[i4][j4]=='X');//舍去if，可以用bool值进行累加
                m=(c[i1][j1]=='.')+(c[i2][j2]=='.')+(c[i3][j3]=='.')+(c[i4][j4]=='.');//同理
                if(m==1&&n==3)//判断
                {
                    printf("YES");
                    return 0;
                }
            }
        }
    }
    printf("NO");
}
```


---

## 作者：Limury (赞：0)

### 题意

给定一个五子棋盘，判断再下一子能不能赢。

### 思路

由于棋盘大小固定，为 $10 \times 10$ ，所以可以放心模拟解题。我们可以两重循环枚举每一个可以下子的地方，判断在这个位置下棋是否可以构成五子，是就输出，否则继续循环。如果最后依旧未输出，就可得知无解。

在判断是否构成五子时，我们可以定义变量 $sum$ ，分别统计从四个方向竖直，水平，左倾，右倾出发，查找有多少子与此时查找的位置相连，变量 $sum$ 的初值应该为一，因为要把此时查找的位置也算进去。记得统计每个方向前都要将 $sum$ 置为一，并且统计时需注意边界。最后判断 $sum$ 是否大于五即可。

### 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int ma[15][15];

bool check(int i,int j){
	if(i>=1&&i<=10&&j>=1&&j<=10&&ma[i][j]==1){
		return 1;
	}
	return 0;
}

bool dfs(int i,int j){
	int sum=1,a=i-1,b=j;
	while(check(a,b)){
		sum++;
		a--;
	}
	a=i+1,b=j;
	while(check(a,b)){
		sum++;
		a++;
	}
	if(sum>=5){
		return 1;
	}
	
	sum=1,a=i,b=j-1;
	while(check(a,b)){
		sum++;
		b--;
	}
	a=i,b=j+1;
	while(check(a,b)){
		sum++;
		b++;
	}
	if(sum>=5){
		return 1;
	}
	
	sum=1,a=i-1,b=j+1;
	while(check(a,b)){
		sum++;
		a--;
		b++;
	}
	a=i+1,b=j-1;
	while(check(a,b)){
		sum++;
		a++;
		b--;
	}
	if(sum>=5){
		return 1;
	}
	
	sum=1,a=i+1,b=j+1;
	while(check(a,b)){
		sum++;
		b++;
		a++;
	}
	a=i-1,b=j-1;
	while(check(a,b)){
		sum++;
		a--;
		b--;
	}
	if(sum>=5){
		return 1;
	}
	return 0;
}

int main(){
	for(int i=1;i<=10;i++){
		scanf("\n");
		for(int j=1;j<=10;j++){
			char ch;
			scanf("%c",&ch);
			if(ch=='X'){
				ma[i][j]=1;
			}
			else if(ch=='O'){
				ma[i][j]=2;
			}
		}
	}
	for(int i=1;i<=10;i++){
		for(int j=1;j<=10;j++){
			if(!ma[i][j]&&dfs(i,j)){
				printf("YES");
				return 0;
			}
		}
	}
	printf("NO");
	return 0;
}
```


---

## 作者：shAdomOvO (赞：0)

[CF825B](https://www.luogu.com.cn/problem/CF825B)
### 题目大意
这题其实很简单，就是纯暴力，对每一给点进行判断。就是跟你一个棋盘，上面已经下了一些子了，问你X能否直接取胜。
### 分析
能否直接取胜，就是问你联在一起的五个格子中，是否有四个 $X$ 并且没有 $O$   。

而五子棋可以横着，竖着，或斜着。

那么总共有四种方法。我们可以用一个二维数组储存，第一维表示横竖那种方法，第二维表示第几个数。可以减少很多的代码。即：
```cpp
int x[5][6]{{0},{0,-2,-1,0,1,2},{0,0},{0,-2,-1,0,1,2},{0,-2,-1,0,1,2}},y[5][10]{{0},{0,0},{0,-2,-1,0,1,2},{0,-2,-1,0,1,2},{0,2,1,0,-1,-2}}；
```

#### 最后，给出总代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,n,m,t,x[5][6]{{0},{0,-2,-1,0,1,2},{0,0},{0,-2,-1,0,1,2},{0,-2,-1,0,1,2}},y[5][10]{{0},{0,0},{0,-2,-1,0,1,2},{0,-2,-1,0,1,2},{0,2,1,0,-1,-2}},tx,ty;
int ans1=0,ans2=0;
char a[11][11];
int main(){
	for(i=1;i<=10;i++)//输入
		for(j=1;j<=10;j++){
			cin>>a[i][j];
		}
	for(i=1;i<=10;i++)
		for(j=1;j<=10;j++){
			for(t=1;t<=4;t++){
				for(int p=1;p<=5;p++){//进行判断
					tx=i+x[t][p];
					ty=j+y[t][p];
					if(tx<1||tx>10||ty<1||ty>10)break;
					if(a[tx][ty]=='X')ans1++;
					if(a[tx][ty]=='.')ans2++;
				}
				if((ans1==4&&ans2==1)||ans1==5){
						cout<<"YES";
						return 0;//直接结束程序，防止多输出
					}
				ans1=0;
				ans2=0;
			}
		}
	cout<<"NO";
	return 0;//完结撒花！！！
}
```




---

## 作者：LinkyChristian (赞：0)

对这个问题考虑一个 dp ，设 $dp_i$ 表示路径长度 $\bmod m=i$ 的路径条数。设两层之间长度为 $i$ 的路径有 $num_i$ 条，可以得出转移式：

$$
dp_{i\bmod m}=\sum_{j=0}^i f_j\times w_{i-j}
$$

发现题目有个特殊性质：每一层之间的边都是相同的。所以每一层之间的转移都是相同的。

我们设 $g_i=w_i$ , $f_i$ 为第 $i$ 层的 dp 数组，这玩意就转化成了一个类似卷积的形式，转移式为 $f_{i+1}=f_i\cdot g_i$ 。那么由于每一层的 $g_i$ 是相同的，因此 $f_i=f_0\cdot g_i^i$ 我们可以用快速幂来优化转移。

这里注意一个细节，由于到了最后一层的点之后，只能从相应的连向汇点的边到达汇点，因此我们需要把连向最后一层的边和连向汇点的边合起来一起转移。

---

