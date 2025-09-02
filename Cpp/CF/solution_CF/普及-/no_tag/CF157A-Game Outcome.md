# Game Outcome

## 题目描述

## 题意
福尔摩斯和华生在一个n * n的棋盘上玩添数游戏。在游戏期间，他们放置一些数到棋盘上，（其中的规则我们不知道）。然而，现在游戏结束了，棋盘中都有一个数字。要知道谁赢，他们需要计算获胜方块的数量。如果要确定特定的方块是否获胜，你需要做到以下几点。分别计算出这个方块所在的纵列上所有数的和（包括自身）和计算出这个方块所在的横列上所有数的和（包括自身）。如果纵列的和大于横列的和，那么这个方块就算一个获胜方块。
如图所示，真是一个结束的棋局。
然后，紫色格子获胜，因为其纵列之和（8+3+6+7=24）大于其横列（9+5+3+2=19）之和，以及24>1924>1924>19。

## 样例 #1

### 输入

```
1
1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2
1 2
3 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
5 7 8 4
9 5 3 2
1 6 6 4
9 5 7 3
```

### 输出

```
6
```

# 题解

## 作者：Gavin0576 (赞：2)

~~蒟蒻题解来了~~  
那么这道题就是很简单的暴力一下就可以过的，数据也是小的一批，~~反正闲的没事干~~，我觉得可以试试压缩程序长度。  
应该是14行的程序
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int a[35][35],z[35],h[35];//a数组表示各个位置的数值，z是纵列的和，h是横列的和。
int main(){
	int n,ans=0;cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) z[i]+=a[j][i],h[i]+=a[i][j];//直接算完横列纵列和
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) if(z[i]>h[j]) ans++;//如果大于，ans++，最后输出即可
	cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：清清老大 (赞：0)

## 思路

本题数据范围很小， $O(n^3)$ 都能过，但是可以优化成 $O(n^2)$ 。

因为有很多方格所在的行或列都是一样的，所以可以把每行和每列的和算出来并保存，再依次比较。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,row[50] = {0},column[50] = {0},x;
    cin >> n;
    for(int i = 0;i < n;i ++)
    {
        for(int j = 0;j < n;j ++)
        {
            cin >> x;
            row[i] += x; // 求出每行的总和
            column[j] += x; // 求出每列的总和
        }
    }
    x = 0; // 重复利用x变量
    for(int i = 0;i < n;i ++)
    {
        for(int j = 0;j < n;j ++)
        {
            if(column[i] > row[j]) // 如果行大于列，计数器加一
            {
                x ++;
            }
        }
    }
    cout << x;
    return 0;
}
```


---

## 作者：Waaifu_D (赞：0)

## 题意：

给定一个数字矩阵，找其中有多少个格子满足他所在的纵行数字总和大于他所在的横行数字总和。

## 做法：

极为简单，我们按照题意一个个输入，顺便求出这一行和这一列的数字总和即可（完全不用考虑时间复杂度，因为这题数据保证小于$35$）。

## AC Code

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n;
int m;
int ans;
int x[50],y[50];
int main()
{
	cin>>n;
	for(int i=1; i<=n;i++)//i为行，j为列
	{
		for(int j=1; j<=n;j++)
		{
			cin>>m;
			x[i]+=m;//这一行的总和
			y[j]+=m;//这一列的总和
		}
	}
	for(int i=1; i<=n;i++)
	{
		for(int j=1; j<=n;j++)
		{
			if(x[i]<y[j]) ans++;
		}
	}
	cout<<ans;
	return 0;
}
}
```

---

## 作者：Yydy_RedDust (赞：0)

~~又将有一个水题题解装进我的水博客了~~  
说实话，这道题很水，真的不能再水，正常人都能做出来
## 解法：  
1、求出每一横行和每一纵行和  
2、由于数据很小，直接二重循环判断每个方块，如果该点所在纵列和大于横行和那么它就是一个获胜方块  
## 代码：  
```cpp
#include<bits/stdc++.h>
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define AC return 0
#define N 35
using namespace std;
int n,ans=0,a[N][N],x[N],y[N];
int main()
{
	//freopen("CF157A.in","r",stdin);
	//freopen("CF157A.out","w",stdout);
	cin>>n;
	rep(i,1,n)
		rep(j,1,n)
		{
			cin>>a[i][j];
			x[i]+=a[i][j]; //求每一横行和 
			y[j]+=a[i][j]; //求每一纵列和 
		}
	rep(i,1,n)
		rep(j,1,n)
			if(x[i]<y[j])
				ans++;
	cout<<ans<<endl;
	//fclose(stdin);
	//fclose(stdout);
    AC;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
有一个 $n\times n$ 的矩阵，每个元素都有一个权值。求所有满足其所在纵列所有元素权值和大于其所在横列所有元素权值和的元素个数。

**数据范围：$1\leqslant n\leqslant 30$。**
## Solution
直接对于每个元素暴力求出其所在纵列所有元素权值和以及其所在横列所有元素权值和，再进行比较加入计数器。复杂度 $\mathcal{O}(n^3)$，别说这题 $30$ 的数据范围了，我看给个 $n\leqslant 500$ 也不为过。
## Code
```cpp
int n, a[37][37], ans;

int main() {
	n = Rint;
	F(i, 1, n) F(j, 1, n) a[i][j] = Rint;
	F(i, 1, n) F(j, 1, n) {
		int sum1 = 0, sum2 = 0;
		F(k, 1, n) sum1 += a[k][j];
		F(k, 1, n) sum2 += a[i][k];
		ans += (sum1 > sum2);
	}
	return write(ans), 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 前言

题目其实还好，~~但是数据水呀！~~，$1\le n\le30$ , 别说$n^{2}$了，就是$n^{3}$都可以过！

## 分析

按照题目要求，先读入一个矩阵，然后，双重循环枚举一个数。

将这个数的纵和列算出来，比较一下，如果纵的和大于列的和，那么ans++，最后输出ans。

## 解决

Code :

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=35;
int n,data[INF][INF],z,l,ans;// n代表矩阵是n*n，data是读入的矩阵，z是纵列之和，l是横列之和，ans是最终的答案。
int main()
{
	scanf("%d",&n);//读入n
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			scanf("%d",&data[i][j]);//读入data矩阵
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)//暴力双重循环枚举每个点
			{
				l=0;
				z=0;//非常非常要注意，这里必须清零，否则会把上一次的数据带过来。
				for (int k=1;k<=n;k++)
					{
						l=l+data[i][k];//算出横列之和。
						z=z+data[k][j];//算出纵列之和。
					}
				if (z>l) ans++;//比较，如果纵列大于横列那么+1。
			}
	printf("%d\n",ans);//输出最终的结果。
	return 0;
}
```


## 写在后面的话

我这篇题解如果有错误，那么请在评论区里留言，我将会很感谢反映的人。

谢谢观赏！

---

## 作者：Strange_S (赞：0)

```cpp
#include<iostream>
using namespace std;
int n,ans=0;
int z[32][32];
void Sherlock(int x,int y){
	int i,j,s=0,k=0;
	for(i=1;i<=n;i++){
		s+=z[i][y];      //计算纵列
		k+=z[x][i];      //计算横列
	}
	if(s>k){             //如果纵列大于横列
		ans++;          //答案++
	}
}
int main(){
	int i,j;
	cin>>n;//输入
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			cin>>z[i][j];
		}
	}
	for(i=1;i<=n;i++){      //遍历每一个方格
		for(j=1;j<=n;j++){
			Sherlock(i,j);
		}
	}
	cout<<ans;           //输出
	return 0;
}
```

---

