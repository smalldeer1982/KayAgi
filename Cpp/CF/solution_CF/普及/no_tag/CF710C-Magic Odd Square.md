# Magic Odd Square

## 题目描述

Find an $ n×n $ matrix with different numbers from $ 1 $ to $ n^{2} $ , so the sum in each row, column and both main diagonals are odd.

## 样例 #1

### 输入

```
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
```

### 输出

```
2 1 4
3 5 7
6 9 8
```

# 题解

## 作者：Liweiang (赞：5)

**题目：** [CF710C Magic Odd Square](https://www.luogu.com.cn/problem/CF710C)



------------


## 题意：
构造一个 n 阶幻方，使每行，每列，以及主对角线的和（也就是幻和）都为奇数，给定 n  为奇数。



------------


## 思路：
这道题的代码 [P2615 神奇的幻方](https://www.luogu.com.cn/problem/P2615) 的代码一模一样，因为当 n 为奇数时，n 阶幻方的幻和就是奇数，推一遍幻和公式就知道了，见下：


已知一个 n 阶的幻方，一共有 $n^2$ 个数，

$\therefore$ 它们的和 $S=1+2+3+...+n^2=\displaystyle\frac{n^2\times(1+n^2)}{2}$。


$\because$ n 阶幻方共有 n 行，每行的和为 N， 

$\therefore N_n=\displaystyle\frac{n^2\times(1+n^2)}{2}\rightarrow N=n\times\displaystyle\frac{1+n^2}{2}$。


下面判断一下奇偶性就行了：


$\because$ n 为奇数，

$\therefore 1+n^2$ 的值为偶数 $\rightarrow\displaystyle\frac{1+n^2}{2}$ 的值也为偶数，

$\therefore n\times\displaystyle\frac{1+n^2}{2}$ 的值为奇数，即幻和 N 为奇数。 



然后我们就可以套用 [P2615 神奇的幻方](https://www.luogu.com.cn/problem/P2615) 的代码啦！



------------


## AC code：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int s[500][500];
int main(){
	int n,x,y,ans;
	cin>>n;
	s[1][n/2+1]=1; x=1; y=n/2+1;
	for(ans=2;ans<=n*n;ans++){
		if(x==1&&y!=n){ //填在最后一行,右一列 
			s[n][y+1]=ans;
			x=n; y++;
			continue;
		}
		if(y==n&&x!=1){ //填在第一列,上一行 
			s[x-1][1]=ans;
			x--; y=1;
			continue;
		}
		if(x==1&&y==n){ //填在正下方 
			s[x+1][y]=ans;
			x++;
			continue;
		}
		if(x!=1&&y!=n){
			if(s[x-1][y+1]==0){ //判断右上方有没有填过 
				s[x-1][y+1]=ans;
				x--; y++;
				continue;
			} 
			else{ //填在正下方 
				s[x+1][y]=ans;
				x++;
				continue;
			}
		}		
	}
	for(int i=1;i<=n;i++,puts("")){
		for(int j=1;j<=n;j++)
			cout<<s[i][j]<<" ";
	}
	return 0;
}
```

------

**后话：** 本蒟蒻的讲解过程如有不当之处还请各位 dalao 指出，谢谢大家！

---

## 作者：zcs_ (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF710C)

## 思路：

首先，创建一个大小为 $n \times n$ 的二维数组 $a$，并将其所有元素初始化为 $0$。这个数组将用来存储最终构造好的魔术奇数方阵。

接下来，我们需要确定数字的放置顺序和位置。我们从数字 $1$ 开始，将其放置在第一行的中间列，即 $row = 0$，$col = n \div 2$。

然后，我们进入一个循环，从数字 $2$ 开始，直到 $n \times n$。在每次循环中，我们将当前数字放置在当前位置 $(row, col)$，并将数字加 $1$。

根据奇数阶幻方的构造规则，我们可以获得下一个位置 $(next_{row}, next_{col})$。如果这个位置还没有被填充过数字，则将下一个位置设置为当前位置 $(next_{row},next_{col})$。否则，将下一个位置的行加 $1$，即 $(row + 1) \bmod n$。

重复这个循环过程，直到填充完所有数字。

最后，遍历二维数组 $a$，将其中的数字逐行打印输出。

### 具体代码（加注释版）：

```cpp
#include <bits/stdc++.h>
using namespace std;
void fun(int n){
    //创建一个n×n的二维数组，并将其所有元素初始化为0
    vector<vector<int>>a(n,vector<int>(n,0));
    //数字从1开始，放置在第一行的中间列
    int num=1;
    int row=0,col=n/2;
    //循环直到填充完所有数字
    while(num<=n*n){
        //将当前数字放置在当前位置，并将数字加1
        a[row][col]=num;
        num++;
        //获取下一个位置
        int next_row=(row-1+n)%n;
        int next_col=(col+1)%n;
        //如果下一个位置还未填充数字，则将下一个位置设置为当前位置
        if (a[next_row][next_col]==0){
            row=next_row;
            col=next_col;
        }
        else{
            row=(row+1)%n;
            //如果下一个位置已经填充了数字，则将下一个位置的行加1
        }
    }
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main(){
    int n;
    cin>>n;
    fun(n);
    return 0;
}
```

---

## 作者：Marshall001 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF710C)

## 题目大意

给你一个数 $n$（$n$ 为奇数），构造出一个 $n\times n$ 的幻方，使得每行每列和两个主对角线和都为奇数。

## 思路

这道题其实就是 [P2615](https://www.luogu.com.cn/problem/P2615)，一模一样的代码可以同时通过，简称双倍经验。

可是这一道题与 P2615 最不一样的地方就是，一个什么也没有要求，一个要求了每行每列还有两个主对角线都是奇数。也就是幻和是奇数。那么我们就要证明奇数阶幻方的幻和一定是奇数，具体证明如下：

我们设 $sum$ 代表 $n$ 阶幻方的所有数字之和，也就是 $1+2+3...+n^2$，可以用等差数列求和公式来计算。$sum=(1+n^2)\div 2 \times n^2$。

幻和 $N=sum \div n=(1+n^2)\div 2 \times n$。

接下来就可以判断奇偶性了：

$n$ 为奇数，$n^2$ 就是奇数，$n^2+1$ 就是偶数。

$(n^2+1)\div 2$ 一定是奇数。因为 $n$ 的末尾一定是 $1,3,5,7,9$，这几个数，然而：

- $(1 \times 1+1)\div 2=1$
- $(3 \times 3+1)\div 2=5$
- $(5 \times 5+1)\div 2=13$
- $(7 \times 7+1)\div 2=25$
- $(9 \times 9+1)\div 2=41$

都是奇数，于是我们得出结论：$(n^2+1)\div 2$ 一定是奇数。

那么$(1+n^2)\div 2 \times n$ 就是奇数。这样，证明就结束了。

至于怎么构造幻方，可以看看 [P2615](https://www.luogu.com.cn/problem/P2615) 的题目描述，也就是罗伯构造法。

## 代码

```cpp
#include <iostream>
using namespace std;
const int MAXN=50;//开大点儿，不会错
int a[MAXN][MAXN];
int main(){
	int n;
	cin>>n;
	int x=1,y=n/2+1;//记录现在的位置
	for(int i=1;i<=n*n;i++){
		a[x][y]=i;
		int nx=x,ny=y;
		nx--;//更新
		ny++;
		if(nx==0){
			nx=n;
		}
		if(ny==n+1){
			ny=1;
		}
		if(a[nx][ny]!=0){
			x++;
		}
		else{
			x=nx;
			y=ny;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Siteyava_145 (赞：1)

第一篇C题题解~~

- 简述题意，就是构造一个 $n$ 阶幻方，并且 $n$ 是奇数。

- 《小学奥数题》构造奇数阶幻方，要遵循几个规则：

1. 第一行的中间是 $1$。

2. 如果右上方有空位，就填下一个数字，否则填在正下方。

3. 如果右上方超出边界，那就将要填的这个格子平移到第 $1$ 列或第 $n$ 行，填下一个数字。

4. 在右上角的，下一个数填在正下方。       ------**罗伯构造法**

详见[这位大佬](https://blog.csdn.net/nameofcsdn/article/details/104896318)
叙述

这样，幻方就构造好了~~~

不过在此之前，要确定一件事，题目要求幻和为**奇数**！

~~浅证一下~~。

幻和 $=\frac{(1+2+……+(n^2-1)+n^2)}{n}$。

化简得幻和 $=\frac{n(n^2+1)}{2}$。

因为 $n$ 为奇数，所以 $n^2$ 为奇数，且除以 $4$ 的余数为 $1$。

所以$2\mid{n(n^2+1)}$ 且 $4\nmid{n(n^2+1)}$。

所以幻和 $\frac{n(n^2+1)}{2}$ 为奇数，因为分子不含有因子 $4$。

AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[1005][1005];
int main()
{
	int n;
	cin>>n;
	ans[1][n/2+1]=1;//初始的1 在第一行中间 
	int ax=1,ay=n/2+1;// x=行，y=列 
	for(int i=2;i<=pow(n,2);i++)
	{
		if(ax==1&&ay!=n){ //如果在第一行，且不是右上角： 
			ans[n][ay+1]=i;//右上平移到最下面 ，也就是第n行,第y+1 列。 
			ax=n; 
			ay+=1;//更新 
		}
		else if(ay==n&&ax!=1){ //如果在最后一列，且不是右上角： 
			ans[ax-1][1]=i;//右上平移到第一列，也就是第x-1行，第1列 
			ax-=1; 
			ay=1;//更新 
		}
		else if(ax==1&&ay==n){ //右上角 
			ans[ax+1][ay]=i;//填在下面一格 
			ax++;//更新 
		}
		else if(ax!=1&&ay!=n){//无特殊情况 
			if(ans[ax-1][ay+1]==0){
				ans[ax-1][ay+1]=i;
				ax--; 
				ay++;
			}else{
				ans[ax+1][ay]=i;
				ax++;
			}
		}
	}
	for(int i=1;i<=n;i++){//全部输出 
		for(int j=1;j<=n;j++){
			cout<<ans[i][j]<<' ';
		}
		cout<<"\n";
	} 
	return 0;
}
```
完结撒花~~~

---

## 作者：MattL (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/CF710C) & [原题链接](http://codeforces.com/problemset/problem/710/C)

[双倍经验](https://www.luogu.com.cn/problem/P2615)

---

**题意**

由于每行，每列，以及主对角线的和都为奇数，符合幻方的描述，所以就是构造一个 $n\times n$ 的幻方。
（是 `SPJ`，不用管样例）

---


**解题**

众所周知，智慧的古人给出了构造幻方的方法，如下。
1. 从第一行中间开始放
1. 往右上放数
2. 不行就往下放

---

**代码**

就和那个双倍经验一样（记得数组开大些）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[600][600],x,y;
int main(){
    cin>>n;
    x=1,y=(n+1)/2,a[x][y]=1;
    for(int i=2;i<=n*n;i++)
        if(!a[(x-2+n)%n+1][y%n+1]) 
            x=(x-2+n)%n+1,y=y%n+1,a[x][y]=i;
        else 
            x=x%n+1,a[x][y]=i;
    for(int i=1;i<=n;i++,cout<<endl)
        for(int j=1;j<=n;j++)
            cout<<a[i][j]<<' ';
} 
```

---

## 作者：yangyuanxi44 (赞：1)

这道题就让你构造一个 $n$ （ $n$ 为奇数）阶幻方，但是让你的横纵对角线皆为奇数，现在就需证明是否普通的构造方式让幻方横纵对角线皆为奇数。

那么用普通的构造方式推导：

$∴$ 有 $n$ 个数自然我们让中间数 $\frac{n+1}{2}$ 放在中心那么这一串数就会以：

$∴$ $a_1$  $a_n$ $,$ $a_2$  $a_{n-1}$  $···$   两两组合与 $\frac{n+1}{2}$ 相加。

$∵$ $n$ 为奇数所以 $\frac{n+1}{2}$ 也一定为奇数。

$∴$ $a_i + a_{n-i+1} + \frac{n+1}{2}$ $=$ 奇 $+$ 奇 $+$ 奇 $=$ 奇 或者 偶 $+$ 偶 $+$ 奇 $=$ 奇（不懂的可以用，$n=3$ 推导下）所以普通的构造方式可用。

~~那么我们可以用 P2615 神奇的幻方的代码了。~~

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[40][40];
int main(){
	memset(a,0,sizeof(a));
	int n;
	cin>>n;
	int cnt=1;
	int nowx,nowy;
	while(cnt!=n*n+1){
		if(cnt==1){
			a[1][(n+1)/2]=cnt;
			nowx=1;
			nowy=(n+1)/2;
			cnt++;
		}else if(nowx-1<1&&nowy+1>n){
			     nowx++;
				 a[nowx][nowy]=cnt;
				 cnt++;
		     }
		    else if(nowx-1<1){
				nowx=n;
				nowy++;
				a[nowx][nowy]=cnt;
				cnt++;
			}else if(nowy+1>n){
				nowx--;
				nowy=1;
				a[nowx][nowy]=cnt;
				cnt++;
			}else if(a[nowx-1][nowy+1]!=0){
				nowx++;
				a[nowx][nowy]=cnt;
				cnt++;
			}else{
				nowx=nowx-1;
				nowy=nowy+1;
				a[nowx][nowy]=cnt;
				cnt++;
			}
		}
		for(int i=1 ; i<=n ; i++){
		    for(int j=1 ; j<=n ; j++)
			    cout<<a[i][j]<<" ";
		    cout<<endl;
	    }
	return 0;
}
	

```

谢谢大家阅读，谢谢管理员审核。

---

## 作者：Mint_Flipped (赞：1)

思维题

举个例子：

2 1 4

3 5 7

6 9 8

保证 1 3 5 7这些位置的是奇数，其他位置填偶数即可。

规律：一个矩阵，就是一个正方形，取正方形的四条边的中点，构成一个新的正方形，被该正方形覆盖的矩阵上的点，填奇数，否则填偶数。

代码如下：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define lowbit(a) a&(-a)
#define inf 0x3f3f3f3f
using namespace std;
const int maxn=3e5+5;
const int mod=1e9+7;
const double eps=1e-10;
int a[55][55]= {0};
int main()
{
    int n;
    cin>>n;
    int t=(n+1)/2;
    int l=t,r=t;
    int p=1;
    for(int i=1; i<=(n+1)/2; ++i)
    {
        for(int j=l; j<=r; ++j)
        {
            a[i][j]=p;
            p+=2;
        }
        l--,r++;
    }
    l=t,r=t;
    for(int i=n; i>(n+1)/2; --i)
    {
        for(int j=l; j<=r; ++j)
        {
            a[i][j]=p;
            p+=2;
        }
        l--,r++;
    }
    p=2;
    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=n; ++j)
        {
            if(a[i][j]==0){
                a[i][j]=p;
                p+=2;
            }
            cout<<a[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
```


---

## 作者：XioasDog (赞：0)

# CF710C

因为只需要是奇数，而偶数是不能凑出奇数的，又只有奇数个奇数才能凑出奇数，那构造方法就很明了了。

首先把中间一行一列涂为奇数。

![](https://cdn.luogu.com.cn/upload/image_hosting/ilyo0mbh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

然后剩余未使用的奇数只需要均匀地分在四周就行（对称可以保证题目性质）。

譬如这样

![](https://cdn.luogu.com.cn/upload/image_hosting/zecd15b0.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

剩余的空格随便乱填就可以啦！

---

## 作者：ryl_ahu (赞：0)

### 题目解读：

现给定 $n$ ，
请按下述方法构造 $n \times n$ 的幻方。
首先将 $1$ 写在第一行的中间，
然后，按如下方式从小到大依次填写每个数 $K \ (K=2,3,\cdots,n \times n)$ ：

1. 若 $(K-1)$ 在第一行但不在最后一列，则将 $K$ 填在最后一行， $(K-1)$ 所在列的右一列；
2. 若 $(K-1)$ 在最后一列但不在第一行，则将 $K$ 填在第一列， $(K-1)$ 所在行的上一行；
3. 若 $(K-1)$ 在第一行最后一列，则将 $K$ 填在 $(K-1)$ 的正下方；
4. 若 $(K-1)$ 既不在第一行，也不在最后一列，如果 $(K-1)$ 的右上方还未填数，则将 $K$ 填在 $(K-1)$ 的右上方，否则将 $K$ 填在 $(K-1)$ 的正下方。

### 于是我们就可以按照上述的方法开写！

我用 $x$ 和 $y$ 来表示 $K$ 的位置。

---
###### 第一步：确定 $1$ 的位置
```
mz[1][n / 2 + 1] = 1;
x = 1;
y = n / 2 + 1;
```
---
###### 第二步：按照方法 $1$ 进行判断
```
if (x == 1 and y != n) {
	mz[n][y + 1] = i;
	x = n;
	y = y + 1;
}
```
---
###### 第三步：按照方法 $2$ 进行判断
```
if (x != 1 and y == n) {
	mz[x - 1][1] = i;
	x = x - 1;
	y = 1;
}
```
---
###### 第四步：按照方法 $3$ 进行判断
```
if (x == 1 and y == n) {
	mz[x + 1][y] = i;
	x = x + 1;
}
```
---
###### 第五步：按照方法 $4$ 进行判断（这次的判断分两步走）
```
if (x != 1 and y != n) {
	if (mz[x - 1][y + 1] == 0) { // 判断不为零
		mz[x - 1][y + 1] = i;
		x = x - 1;
		y = y + 1;
	} else {
		mz[x + 1][y] = i;
		x = x + 1;
	}
}
```
---
###### 第六步：输出
```
for (int i = 1; i <= n; i++) {
	for (int j = 1; j <= n; j++) {
		cout << mz[i][j] << " ";
	}
	cout << endl;
}
```
---
### 附上总代码！
```
#include <bits/stdc++.h>
using namespace std;

int n;
int mz[1000][1000];     // 初始化
bool vis[1000][1000]; 
int x, y;

int main() {
	cin >> n;
	mz[1][n / 2 + 1] = 1;  // 第一步
	x = 1;
	y = n / 2 + 1;
	for (int i = 2; i <= n * n; i++) { // 遍历
		if (x == 1 and y != n) {  // 第二步
			mz[n][y + 1] = i;
			x = n;
			y = y + 1;
		} else if (x != 1 and y == n) { // 第三步
			mz[x - 1][1] = i;
			x = x - 1;
			y = 1;
		} else if (x == 1 and y == n) { // 第四步
			mz[x + 1][y] = i;
			x = x + 1;
		} else if (x != 1 and y != n) { // 第五步
			if (mz[x - 1][y + 1] == 0) {
				mz[x - 1][y + 1] = i;
				x = x - 1;
				y = y + 1;
			} else {
				mz[x + 1][y] = i;
				x = x + 1;
			}
		}
	}
	for (int i = 1; i <= n; i++) { // 输出
		for (int j = 1; j <= n; j++) {
			cout << mz[i][j] << " ";
		}
		cout << endl;
	}
	return 0; // 华丽结束！
}
```


---

## 作者：WaterSky (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF710C)。

做这道题之前，先看[这题](https://www.luogu.com.cn/problem/P2615)，里面提供了构造这个数阵的方法。

幻方是一种很神奇的 $N\times N$ 矩阵：它由数字 $1,2,3,\cdots \cdots ,N \times N$ 构成，且每行、每列及两条对角线上的数字之和都相同。

当 $N$ 为奇数时，我们可以通过下方法构建一个幻方：

首先将 $1$ 写在第一行的中间。

之后，按如下方式从小到大依次填写每个数 $K (K=2,3,\cdots,N \times N)$：

1. 若 $(K-1)$ 在第一行但不在最后一列，则将 $K$ 填在最后一行，$(K-1)$ 所在列的右一列；
2. 若 $(K-1)$ 在最后一列但不在第一行，则将 $K$ 填在第一列，$(K-1)$ 所在行的上一行；
3. 若 $(K-1)$ 在第一行最后一列，则将 $K$ 填在 $(K-1)$ 的正下方；
4. 若 $(K-1)$ 既不在第一行，也不在最后一列，如果 $(K-1)$ 的右上方还未填数，则将 $K$ 填在 $(K-1)$ 的右上方，否则将 $K$ 填在 $(K-1)$ 的正下方。

现给定 $N$，请按上述方法构造 $N \times N$ 的幻方。

在题目中可以知道填写幻方的方法，所以这一道题就是纯模拟。

再看现在的这一题。有很多人就会有疑问，为什么这道题可以使用 P2615 的代码。由于两道题目都有一个条件：$N$ 为奇数。每一个数阵的数的和为：$1+2+...+N$。由于 $N$ 为奇数，所以这些和也为奇数。又由于奇数 $\div$ 奇数一定等于奇数，所以这一道题可以使用 P2615 的代码。

```
#include<bits/stdc++.h>
using namespace std;
int n,a[105][105],x,y;
int main(){
	scanf("%d",&n);
   //以下代码是通过 P2615 的题目来模拟的。
	x=1,y=(n+1)/2;
	for(int i=1;i<=n*n;i++)
	{
		a[x][y]=i;
		if(!a[(x-2+n)%n+1][y%n+1]) x=(x-2+n)%n+1,y=y%n+1;
		else x=x%n+1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) printf("%d ",a[i][j]);
		printf("\n");
	}
	return 0;
} 
```

以样例来举例，样例输入为 $3$。

我们这个程序的输出为：
```
8 1 6
3 5 7
4 9 2
```
但样例输出为：
```
2 1 4
3 5 7
6 9 8
```
并不一样，可这就代表我的代码错误了吗？不急，一步一步验证。

每一行，每一列，每一条对角线的都和为：$15$。

再自己用另一个输入：$5$。

输出为：
```
17 24 1 8 15
23 5 7 14 16
4 6 13 20 22
10 12 19 21 3
11 18 25 2 9
```

每一行，每一列，每一条对角线的和都为：$65$。

也可以举其他的~~栗~~例子，都可以得出答案正确的结果。所以按下你的提交键！

---

## 作者：rain_dew (赞：0)

题目链接：[CF710C Magic Odd Square](https://www.luogu.com.cn/problem/CF710C)

### 思路：
这道题实际上是让我们构建一个 $n \times n$ 的幻方。

幻方构建可以参照[P2615](https://www.luogu.com.cn/problem/P2615)（罗伯法）构建。

1. 定义数组，并设计 $1$ 的位置于数组第一行的正中间。

1. 其次，进入设计幻方的函数部分。

- 正常的数据（不在数组的边界或没有重复的数据）都放到前一个数据的右上角。

- 如果这个数据超出了顶行就放到它的底行的右一列。

- 如果这个数据超出了尾列就放到它的首列的上一行。

- 如果这个数据既超出顶行又超出尾列（或者它的位置有其他的数据存在），那么它就要往下一行放入数据。

3. 最后，输出我们的答案。


### 代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[50][50];
void dp(int so,int x,int y)
{
	if (so>n*n)
		return ;
	if (x==1 && y!=n)
	{
		a[n][y+1]=so;
		dp(so+1,n,y+1);
	}
	if (y==n && x!=1)
	{
		a[x-1][1]=so;
		dp(so+1,x-1,1);
	}
	if (x==1 && y==n)
	{
		a[x+1][y]=so;
		dp(so+1,x+1,y);
	}
	if (x!=1 && y!=n)
	{
		if (!a[x-1][y+1])
		{
			a[x-1][y+1]=so;
			dp(so+1,x-1,y+1);
		}
		else
		{
			a[x+1][y]=so;
			dp(so+1,x+1,y);
		}
	}
	return ;	
}
int main()
{
	scanf("%d",&n);
	a[1][n/2+1]=1;
	dp(2,1,n/2+1);
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=n;j++)
			printf("%d ",a[i][j]);
		printf("\n");
	}
	return 0;
}
```

### 做题反思：
做完这个题后，我们会发现：**不论我们如何放置数据**，幻方都会**有往右往上的趋势的**，即使**我们把这一顶行（尾列）放入对应的底行（首列）**，而为了处理**重复占用的数值**，我们把它们放于下一行中也是**没有改变这一趋势的**。

---

## 作者：Back_Stuff (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF710C)

### [双倍经验：P2615 神奇的幻方](https://www.luogu.com.cn/problem/P2615)

这两道题目的代码其实一模一样，只需要证明一下按那种构造方式可以满足这道题的条件就行了。

幻和求解公式证明：

幻和 $=1+2+3+...+(n^2-1)+n^2$

化简后的幻和 $= \frac{n(n^2+1)}{2}$

每行数值和 $= \frac{n^2+1}{2}$

将 $n$ 带入试试：

- $n=1,\frac{n^2+1}{2}=\frac{1+1}{2}=1$，是奇数。

- $n=3,\frac{n^2+1}{2}=\frac{9+1}{2}=5$，是奇数。

- $n=5,\frac{n^2+1}{2}=\frac{25+1}{2}=13$，也是奇数。

所以我们可以初步判定 $\frac{n^2+1}{2}$ 为奇数。

$n$ 也是奇数，因为 $\text{奇数} \times \text{奇数} = \text{奇数}$，所以 $= \frac{n(n^2+1)}{2}$ 是奇数。

证明完成，开始写代码。代码很丑，不喜勿喷。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,prev_x,prev_y,cnt,g[55][55];
bool vis[55][55];
int main(){
    cin>>n;
    prev_x=1,prev_y=n/2+1;
    vis[prev_x][prev_y]=true;
    g[prev_x][prev_y]=++cnt;
    while(true){
        if(prev_y+1<=n&&prev_x==1&&prev_y!=n){//最后一行，上个数的右一列
            prev_x=n,prev_y++;
            vis[prev_x][prev_y]=true;
            g[prev_x][prev_y]=++cnt;
        }else if(prev_x>=2&&prev_y==n&&prev_x!=1){//第一列，上个数的上一行
            prev_x--,prev_y=1;
            vis[prev_x][prev_y]=true;
            g[prev_x][prev_y]=++cnt;
        }else if(prev_x+1<=n&&prev_x==1&&prev_y==n){//上个位置的正下方
            prev_x++;
            vis[prev_x][prev_y]=true;
            g[prev_x][prev_y]=++cnt;
        }else if(prev_x!=1&&prev_y!=n){
            if(prev_x>=2&&prev_y+1<=n&&!vis[prev_x-1][prev_y+1]){//上个数的右上方
                prev_x--,prev_y++;
                vis[prev_x][prev_y]=true;
                g[prev_x][prev_y]=++cnt;
            }else if(prev_x+1<=n){//上个数的正下方
                prev_x++;
                vis[prev_x][prev_y]=true;
                g[prev_x][prev_y]=++cnt;
            }
        }
        bool flag=false;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(!vis[i][j]){
                    flag=true;
                    break;
                }
            }
        }
        if(!flag) break;//如果填满了，退出循环
    }
    for(int i=1;i<=n;i++){//输出
        for(int j=1;j<=n;j++) cout<<g[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}

```

---

## 作者：G__G (赞：0)

# [醒目的传送门](https://www.luogu.com.cn/problem/CF710C)


简单来说，这题就是构造一个 $n$ 阶幻方。

构造幻方的方法：罗伯构造法

1. 第一行的中间是 $1$ 。

2. 如果右上方有空位，就填下一个数字，否则填在正下方。

3. 如果右上方超出边界，那就将要填的这个格子平移到第 $1$ 列或第 $n$ 行，填下一个数字。

4. 在右上角的，下一个数填在正下方。

讲完了，是时候

## 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100][100],x,y;
int main(){
	cin>>n;
	x=1,y=(n+1)/2;
	for(int i=1;i<=n*n;i++){
		a[x][y]=i;
		if(!a[(x-2+n)%n+1][y%n+1]){
			x=(x-2+n)%n+1;
			y=y%n+1;
		}
		else{
			x=x%n+1;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
} 
```

### [$AC$](https://www.luogu.com.cn/record/90596141) 证明

---

## 作者：_lgh_ (赞：0)

## 思路：
每次判断下一个位置是否非零，如果是就行列都往后跳，不是就只跳行

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[50][50];
int main(){
	scanf("%d",&n);
	for(int x=0,y=(n>>1),i=0;i<n*n;i++) {
    a[x][y]=i+1;
    if(!a[(x+n-1)%n][(y+1)%n]) x=(x+n-1)%n,y=(y+1)%n;
    else x=(x+1)%n;
  }
  for(int i=0;i<n;puts(""),i++)
    for(int j=0;j<n;j++) 
      printf("%d ",a[i][j]);
  return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
构造出一个 $n\times n$ 的矩阵，使得这个矩阵由 $1\sim n^2$ 这些数字组成，并且这个矩阵的每行，每列，以及对角线的和都为奇数。

**数据范围：$1\leqslant n\leqslant 49$。$n$ 为奇数。**
## Solution
这题其实就是 $\texttt{NOIP2015}$ 提高组的 $\texttt{D1T1}$，因为——都是奇数幻方，都是要求每行，每列，以及对角线的和都相等。只不过这道题目要求和都为奇数罢了。

但是，只要你利用 P2615 的代码随便弄几个幻方观察一下，你就会发现：矩阵的每行，每列，以及对角线的和都等于一个奇数。

所以直接将 P2615 的代码蒯过来就好了……

代码就不贴了，建议没做 P2615 的先去做那一题。

---

