# [ICPC 2021 Nanjing R] Oops, It's Yesterday Twice More

## 题目描述

继 2018、2019 和 2020 年的巨大成功之后，南京航空航天大学（NUAA）将第四次举办国际大学生程序设计竞赛（ICPC）南京赛区。

2018 年和 2019 年，清华大学的队伍“Power of Two”和“三人行二”分别获得了冠军。2020 年，北京大学的队伍“Inverted Cross”赢得了冠军。2021 年，大约有 700 支队伍，包括卫冕冠军，参加了比赛。我们非常期待今年谁将获胜！

尽管由于疫情我们无法在南京聚集，但我们仍然应该感谢所有工作人员和志愿者为这次比赛所做的辛勤工作。感谢你们对这次比赛的巨大贡献！

在 2018 年的比赛中，问题 K，“Kangaroo Puzzle”，要求参赛者为游戏构建一个操作序列：

> 这个谜题是一个有 $n$ 行 $m$ 列的网格（$1 \le n, m \le 20$），其中有一些（至少 2 个）袋鼠站在网格中。玩家的目标是控制它们聚在一起。某些格子中有墙，袋鼠不能进入有墙的格子。其他格子是空的。袋鼠可以从一个空格子移动到相邻的空格子，方向有四个：上、下、左、右。
>
> 一开始每个空格子中恰好有一个袋鼠，玩家可以通过按键盘上的 U、D、L、R 按钮来控制袋鼠。袋鼠将根据你按下的按钮同时移动。
>
> 参赛者需要构建一个最多 $5 \times 10^4$ 步的操作序列，仅包含 U、D、L、R，以实现目标。

在 2020 年的比赛中，问题 A，“Ah, It's Yesterday Once More”，要求参赛者构建一个输入地图以破解之前描述的问题的以下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s = "UDLR";
int main()
{
  srand(time(NULL));
  for (int i = 1; i <= 50000; i++) putchar(s[rand() % 4]);
  return 0;
}
```

现在在 2021 年的比赛中，Paimon 为你准备了该问题的另一个版本。你得到一个有 $n$ 行 $n$ 列的网格（$2 \leq n \leq 500$）。所有格子都是空的，每个格子中有一个袋鼠。

同样，你可以通过按键盘上的 U、D、L、R 按钮来控制袋鼠。袋鼠将根据你按下的按钮同时移动。具体来说，对于位于第 $i$ 行第 $j$ 列的袋鼠，用 $(i,j)$ 表示：

- 按钮 U：如果 $i>1$，它将移动到 $(i-1,j)$。否则，它将停留在同一格子。
- 按钮 D：如果 $i<n$，它将移动到 $(i+1,j)$。否则，它将停留在同一格子。
- 按钮 L：如果 $j>1$，它将移动到 $(i,j-1)$。否则，它将停留在同一格子。
- 按钮 R：如果 $j<n$，它将移动到 $(i,j+1)$。否则，它将停留在同一格子。

你需要构建一个仅由字符 `U`、`D`、`L` 和 `R` 组成的操作序列。在应用它之后，你必须确保每只袋鼠都聚集在特定的格子 $(a,b)$。操作序列的长度不能超过 $3(n-1)$。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 3 3
```

### 输出

```
RRDD```

## 样例 #2

### 输入

```
4 3 2
```

### 输出

```
DLDLDLUR```

# 题解

## 作者：N_Position (赞：8)

## 题目翻译
在一个 $n\times n$ 的地图中，每个位置都有一只袋鼠，每次操作可以使每只袋鼠整体向上下左右四个方向移动一格，袋鼠不会超出地图范围，问：如何在 $3\times(n-1)$ 步及内将所有袋鼠移动到给定位置。
## 题目分析
共分为两个过程：汇集和移动到终点。

考虑汇集，显然只要所有袋鼠都在地图角落，便可汇集。

四个角中，显然要选取距离终点最近的。

最后只需要移到终点即可。

最会情况下移动到一个角上需要 $2\times(n-1)$ 次，移动到终点最多需要 $n-1$ 次，符合题意。

## 代码实现
时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a,b;
	scanf("%d%d%d",&n,&a,&b);
	if(a <= n/2){
		for(int i=1;i<n;i++){
			printf("U");
		}
		for(int i=1;i<a;i++){
			printf("D");
		}
	}else{
		for(int i=1;i<n;i++){
			printf("D");
		}
		for(int i=1;i<n-a+1;i++){
			printf("U");
		}
	}
	if(b <= n/2){
		for(int i=1;i<n;i++){
			printf("L");
		}
		for(int i=1;i<b;i++){
			printf("R");
		}
	}else{
		for(int i=1;i<n;i++){
			printf("R");
		}
		for(int i=1;i<n-b+1;i++){
			printf("L");
		}
	}
}
```

---

## 作者：Shadows_of_Twilight (赞：3)

## 题目大意
有一个 $n \times n$ 的地图，每个格子里有一个袋鼠，要想让所有的袋鼠都到 $(a,b)$ 这个点。你有 $4$ 种操作，分别为 `U`，`D`，`L`，`R`。分别可以让每只袋鼠都往上下左右移动，如果某只袋鼠越界了，也就是超出地图，则不移动。求操作序列。注意，操作序列长度不超过 $3 \times (n-1)$。

## 解题思路
一个简单的模拟。

我们可以把所有袋鼠都用操作到地图的四个角中的一个，看哪个离目标点近，就到那个点，这样就可以在限制内完成。

## AC CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
int x,y;
int main(){
	int n,a,b;
	cin>>n>>a>>b;
	string ans="";
	if(a>n/2){
		for(int i=1;i<=n-1;i++)cout<<"D";
		x=n; 
	}else{ 
		for(int i=1;i<=n-1;i++)cout<<"U";
		x=1;
	}
	if(b>n/2){
		y=n;
		for(int i=1;i<=n-1;i++)cout<<"R";
	}else{
		y=1;
		for(int i=1;i<=n-1;i++)cout<<"L";
	}
	if(x==1&&y==1){
		for(int i=1;i<a;i++){
			cout<<"D";
		}
		for(int i=1;i<b;i++)cout<<"R";
	}
	if(x==1&&y==n){
		for(int i=1;i<a;i++){
			cout<<"D";
		}
		for(int i=n;i>b;i--)cout<<"L";
	}
	if(x==n&&y==1){
		for(int i=n;i>a;i--){
			cout<<"U";
		}
		for(int i=1;i<b;i++)cout<<"R";
	}
	if(x==n&&y==n){
		for(int i=n;i>a;i--){
			cout<<"U";
		}
		for(int i=n;i>b;i--)cout<<"L";
	}
	return 0;
}
```

---

## 作者：small_john (赞：2)

## 前言

Update：修改了一下表述问题。

## 题目大意

有一张 $n\times n$ 的网格图，每个格子上都有一只袋鼠。对于一只在 $(i,j)$ 的袋鼠，有下面四个按钮：

- 按钮 `U`：如果 $i>1$，移动到 $(i-1,j)$，否则，原地不动；
- 按钮 `D`：如果 $i<n$，移动到 $(i+1,j)$，否则，原地不动；
- 按钮 `L`：如果 $j>1$，移动到 $(i,j-1)$，否则，原地不动；
- 按钮 `R`：如果 $j<n$，移动到 $(i,j+1)$，否则，原地不动。

每次按下按钮，都会对**所有的**袋鼠生效。请输出一种使得所有袋鼠最终都在 $(a,b)$ 的操作序列，并且序列的长度小于等于 $3\times(n-1)$。

## 思路

很明显，按照上述的移动方式，从一个点到另一个点的步数就是他们的曼哈顿距离。

那么，我们先要把袋鼠移到一个角上，即移动到 $(1,1)$ 或 $(1,n)$ 或 $(n,1)$ 或 $(n,n)$，再由这个角移到 $(a,b)$。

那如何保证移到步数小于等于 $3\times(n-1)$ 呢？将袋鼠移到任何一个角上都需要 $2\times(n-1)$ 步，所以就移到离 $(a,b)$ 最近的一个角 $(x,y)$。这样就可以保证，$(x,y)$ 和 $(a,b)$ 的横纵坐标之差小于 $\frac{n}{2}$。总步数就一定小于等于 $3\times(n-1)$ 了。

分类讨论解决问题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10); 
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
int n,a,b; 
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(a),read(b);
	int d1 = a+b-2,d2 = n+a-b-1,d3 = n-a+b-1,d4 = 2*n-a-b,mn = min({d1,d2,d3,d4});//处理出到四个角的距离以及最小距离
	if(d1==mn)//左上角
	{
		for(int i = 1;i<n;i++) putchar('U'),putchar('L');
		for(int i = 1;i<a;i++) putchar('D');
		for(int i = 1;i<b;i++) putchar('R');
	}
	else if(d2==mn)//右上角
	{
		for(int i = 1;i<n;i++) putchar('U'),putchar('R');
		for(int i = 1;i<a;i++) putchar('D');
		for(int i = n;i>b;i--) putchar('L');
	}
	else if(d3==mn)//左下角
	{
		for(int i = 1;i<n;i++) putchar('D'),putchar('L');
		for(int i = n;i>a;i--) putchar('U');
		for(int i = 1;i<b;i++) putchar('R');
	}
	else//右下角
	{
		for(int i = 1;i<n;i++) putchar('D'),putchar('R');
		for(int i = n;i>a;i--) putchar('U');
		for(int i = n;i>b;i--) putchar('L');
	}
	return 0;
}
```

---

## 作者：yszkddzyh (赞：1)

### 前言

模拟题。有一点考验思维。

### 题目大意

有一个 $n\times n$ 的场地，每个方格内有一头牛，你可以操控它们**同时**上下左右移动，抵倒墙的牛不移动，你得操控**不超过** $3(n-1)$ 次，使所有奶牛都移动到给定的一个格子 $(a,b)$ 中。

### 思路分析

最后要让所有牛到 $(a,b)$ 内，所以有一种显然的思路是：

1. 先将所有奶牛移动到同一格子内。

2. 再让它们一起移动到 $(a,b)$。

如何实现第 $1$ 步？发现只有当一些牛抵倒墙，且另一些牛朝这些牛移动时，才能“合并”若干个格子（好好理解一下，这是关键）。不然的话所有牛都一起动，相对位置不会改变，也就不能做到把多头牛赶到同一个格子中。

完成了第 $1$ 步，第 $2$ 步也不在话下了，就是简单模拟。

第 $1$ 步还有个问题：要用尽可能少的操作。我们先让 $n\times n$ 头牛移动到一行中，这只需要 $(n-1)$ 次上或下的操作就行了；然后再让这 $1\times n$ 头牛移动到一列中，变成 $1\times1$，类似地，我们只需要进行 $(n-1)$ 次左或右的操作即可。可以证明，这是第 $1$ 步的**最优**方案，需要 $2(n-1)$ 次操作，证明比较简单，请自行思考。

但是仍然有问题，按上述的操作，我们是将所有牛移动至一个位于角上的格子里，但具体是哪一个角呢？我们可以将整块场地平均分成 $4$ 小块（如果 $n$ 是奇数，那么最中间那一行或列随便分在哪一小块都行，不会产生影响），这时每个小块中都有一个角，我们看 $(a,b)$ 在哪个小块中，就去哪个小块对应的角。这样也可以使操作数尽可能的少。

按照上述操作，最坏情况下，即 $(a,b)$ 在原场地正中间的情况下（“正中间”隐含着 $n$ 为奇数），它离它所在小块所包含的角的曼哈顿距离在某种特定情况下取得最大值，为 $\frac{n-1}{2}+\frac{n-1}{2}=n-1$，也就是说从此小块的角到 $(a,b)$ 需要的距离不超过 $n-1$，再加上前面将所有奶牛移动至一个格子中所需的 $2(n-1)$ 步，总共不超过 $3(n-1)$ 步，正好符合题意。

于是代码就有了。

### 代码

```cpp
/* 赛时代码，可能有些乱 */

#include <bits/stdc++.h>
using namespace std;

int n, a, b;

int main(){
	
	cin >> n >> a >> b;
	int t = n / 2;
	if(a <= t && b <= t){
		for(int i = 1; i < n; i++)
			printf("U");
		for(int i = 1; i < n; i++)
			printf("L");
		for(int i = 1; i < a; i++)
			printf("D");
		for(int i = 1; i < b; i++)
			printf("R");
	}
	if(a <= t && b > t){
		for(int i = 1; i < n; i++)
			printf("U");
		for(int i = 1; i < n; i++)
			printf("R");
		for(int i = 1; i < a; i++)
			printf("D");
		for(int i = n; i > b; i--)
			printf("L");
	}
	if(a > t && b <= t){
		for(int i = 1; i < n; i++)
			printf("D");
		for(int i = 1; i < n; i++)
			printf("L");
		for(int i = n; i > a; i--)
			printf("U");
		for(int i = 1; i < b; i++)
			printf("R");
	}
	if(a > t && b > t){
		for(int i = 1; i < n; i++)
			printf("D");
		for(int i = 1; i < n; i++)
			printf("R");
		for(int i = n; i > a; i--)
			printf("U");
		for(int i = n; i > b; i--)
			printf("L");
	}
	
	return 0;
}

/* MADE IN CHINA */
```

---

## 作者：yangzichen1203 (赞：0)

# Problem

[题目传送门](https://www.luogu.com.cn/problem/P9840)

# Solution

这里提供一种比较暴力的做法：

先把所有袋鼠放到一角，然后把它们移到目标位置。

移到离目标位置最近的一角（与中心点比较）是最优的，易证。

代码正确性：移到一个角上花 $2\times(n-1)$ 次，由于这个角距离目标点曼哈顿距离最大为 $(n-1)$ 次，所有共计 $3\times(n-1)$ 次，符合题意。

# Code

```
#include<bits/stdc++.h>
using namespace std;
void f(int k){
	switch(k){
		case 1:cout<<'L';break;
		case 2:cout<<'R';break;
		case 3:cout<<'U';break;
		case 4:cout<<'D';break;
	}
}
int main(){
	int n,a,b;
	cin>>n>>a>>b;
	int mid=(n+1)/2; 
	if(a<=mid&&b<=mid){//LU
		for(int i=1;i<n;i++) f(1);
		for(int i=1;i<n;i++) f(3);
		for(int i=1;i<b;i++) f(2);
		for(int i=1;i<a;i++) f(4);
	}
	if(a<=mid&&b>mid){//RU
		for(int i=1;i<n;i++) f(2);
		for(int i=1;i<n;i++) f(3);
		for(int i=n;i>b;i--) f(1);
		for(int i=1;i<a;i++) f(4);
	}
	if(a>mid&&b<=mid){//LD
		for(int i=1;i<n;i++) f(1);
		for(int i=1;i<n;i++) f(4);
		for(int i=1;i<b;i++) f(2);
		for(int i=n;i>a;i--) f(3);
	}
	if(a>mid&&b>mid){//RD
		for(int i=1;i<n;i++) f(2);
		for(int i=1;i<n;i++) f(4);
		for(int i=n;i>b;i--) f(1);
		for(int i=n;i>a;i--) f(3);
	}
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/problem/P9840)

---

## 作者：Aveiro7 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9840)

## 题意：

有一张 $n\times n$ 的网格图，每个格子上都有一只袋鼠。对于一只在 $(i,j)$ 的袋鼠，有下面四个按钮：

- 按钮 `U`：如果 $i>1$，移动到 $(i-1,j)$，否则，原地不动；
- 按钮 `D`：如果 $i<n$，移动到 $(i+1,j)$，否则，原地不动；
- 按钮 `L`：如果 $j>1$，移动到 $(i,j-1)$，否则，原地不动；
- 按钮 `R`：如果 $j<n$，移动到 $(i,j+1)$，否则，原地不动。

每次按下按钮，都会对**所有的**袋鼠生效。请输出一种使得所有袋鼠最终都在 $(a,b)$ 的操作序列，并且序列的长度小于等于 $3\times(n-1)$。

## 思路：

我们先要将所有袋鼠移到同一个位置，随后在统一移动所有的袋鼠，我们可以将所有的袋鼠移到一个角落里去计算，哪个角落离 $(a,b)$ 距离更近就去哪个角落。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll i,j,t;
int main()
{
	ll a,b,n;
	cin>>n>>a>>b;
	ll x1=n/2,kx=0,ky=0;
	bool f1=true,f2=true;
	if(a<=x1)
	{
		f1=true;
		kx=a-1;
		for(i=1;i<n;i++) cout<<"U";
	}
	else
	{
		f1=false;
		kx=n-a;
		for(i=1;i<n;i++) cout<<"D";
	}
	if(b<=x1)
	{
		f2=true;
		ky=b-1;
		for(i=1;i<n;i++) cout<<"L";
	}
	else
	{
		f2=false;
		ky=n-b;
		for(i=1;i<n;i++) cout<<"R";
	}
	if(f1==true) for(i=1;i<=kx;i++) cout<<"D";
	else for(i=1;i<=kx;i++) cout<<"U";
	if(f2==true) for(i=1;i<=ky;i++) cout<<"R";
	else for(i=1;i<=ky;i++) cout<<"L";
	return 0;
}
```


---

## 作者：jqQt0220 (赞：0)

## 题意翻译

派蒙 ~~（原题就这么说的不要说我 op）~~ 给了你一个 $n\times n$ 的矩阵，每个格子上有一只袋鼠。

你可以用 `U`,`D`,`L`,`R` 四种命令，假设某个袋鼠坐标为 $(i,j)$ $(1\le i,j\le n)$，四种命令效果如下：
- 命令 `U`：移动到 $(i-1,j)$，若越界则不动。
- 命令 `D`：移动到 $(i+1,j)$，若越界则不动。
- 命令 `L`：移动到 $(i,j-1)$，若越界则不动。
- 命令 `R`：移动到 $(i,j+1)$，若越界则不动。

你需要生成一个以 `U`,`D`,`L`,`R` 组成的字符串，每个字符代表一个命令，长度不超过 $3(n-1)$，并且执行完这些命令后，所有袋鼠要聚集在格子 $(a,b)$ 上。

## 思路

既然他说了“若越界则不动”，就可以利用这个把所有袋鼠聚在一个角上，然后统一移动到目标格子，目标格子离哪个角更近就到哪个。因为命令顺序的问题，所以这题有 SPJ。

AC Code:（删去了连头文件一起的一些奇奇怪怪初始化）
```cpp
int n,a,b;
int main()
{
    ___();//不用管这个
    cin>>n>>a>>b;
    if(a<=n/2)//上半部分
    {
        for(int i=1;i<n;i++)//全挤到上面的边界上
            cout<<'U';
        if(b<=n/2)//左上
        {
            for(int i=1;i<n;i++)//挤到左上角
                cout<<'L';
            for(int i=1;i<b;i++)//向右移和目标格同一列
                cout<<'R';
            for(int i=1;i<a;i++)//向下移和目标格同一行
                cout<<'D';
        }
        else//和上面大差不差
        {
            for(int i=1;i<n;i++)
                cout<<'R';
            for(int i=n;i>b;i--)
                cout<<'L';
            for(int i=1;i<a;i++)
                cout<<'D';
        }
    }
    else//和上面大差不差
    {
        for(int i=1;i<n;i++)
            cout<<'D';
        if(b<=n/2)
        {
            for(int i=1;i<n;i++)
                cout<<'L';
            for(int i=1;i<b;i++)
                cout<<'R';
            for(int i=n;i>a;i--)
                cout<<'U';
        }
        else
        {
            for(int i=1;i<n;i++)
                cout<<'R';
            for(int i=n;i>b;i--)
                cout<<'L';
            for(int i=n;i>a;i--)
                cout<<'U';
        }
    }
    return 0;//完美结束 QwQ
}
```

---

## 作者：mayike (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P9840)

## 题意

在一个 $n \times n$ 的方阵中，每个点都站着一只袋鼠。玩家的目标是控制他们聚在 $(a,b)$。当在边缘点时，操作有越界情况是会待在原点的。袋鼠可以由四个方向从一个点移动到相邻的点：向上、向下、向左和向右，分别对应 U，D，L，R。对其操作次数，要求不超过 $3 \times (n-1)$。 

## 思路

想一下，每只袋鼠都分散着是十分麻烦的，看了看操作限制，明显是可以把所有袋鼠集中在四个角中的一个顶点的，最大操作次数是 $2 \times (n-1)$，就可以变成一个点的行动了。但若 $(a,b)$ 距离这个点过远怎么办？当然就找另一个哈曼顿距离离 $(a,b)$ 更近的点就好了。如此可设想极端情况，即 $(a,b)$ 在方阵的中心，那么四角最大到此点的操作次数也才 $\frac{n}{2} + \frac{n}{2} - 1 = n - 1$，即最大总操作次数为 $2 \times (n-1) + n - 1 = 3 \times (n-1)$ 不超过限制，所以此方法成立。

------------

代码就不发了，比较简单，相信大家能写出来的。

---

## 作者：_Flora_ (赞：0)

## Solution

分类讨论，先判断离哪个角落更近，再将袋鼠聚集到那个角落，最后一起走到 $(a,b)$。

## Code

```cpp
#include <bits/stdc++.h> 
using namespace std;

int main()
{
	int i,n,a1,b1,a2,b2;
	
	cin>>n>>a1>>b1;
	
	a2=1,b2=1;
	
	if((a1-a2)+(b1-b2)<=(n-1))
	{
		for(i=1;i<=n-1;i++)
		{
			cout<<"L"; 
		}
		for(i=1;i<=n-1;i++)
		{
			cout<<"U"; 
		}
		for(i=1;i<=b1-b2;i++)
		{
			cout<<"R"; 
		}
		for(i=1;i<=a1-a2;i++)
		{
			cout<<"D"; 
		}		
		return 0; 
	} 
	
	a2=1,b2=n;

	if((a1-a2)+(b2-b1)<=(n-1))
	{
		for(i=1;i<=n-1;i++)
		{
			cout<<"R"; 
		}
		for(i=1;i<=n-1;i++)
		{
			cout<<"U"; 
		}
		for(i=1;i<=b2-b1;i++)
		{
			cout<<"L"; 
		}
		for(i=1;i<=a1-a2;i++)
		{
			cout<<"D"; 
		}		
		return 0; 
	} 	
		
	a2=n,b2=1;

	if((a2-a1)+(b1-b2)<=(n-1))
	{
		for(i=1;i<=n-1;i++)
		{
			cout<<"L"; 
		}
		for(i=1;i<=n-1;i++)
		{
			cout<<"D"; 
		}
		for(i=1;i<=b1-b2;i++)
		{
			cout<<"R"; 
		}
		for(i=1;i<=a2-a1;i++)
		{
			cout<<"U"; 
		}		
		return 0; 
	} 
	
	
	a2=n,b2=n;

	if((a2-a1)+(b2-b1)<=(n-1))
	{
		for(i=1;i<=n-1;i++)
		{
			cout<<"R"; 
		}
		for(i=1;i<=n-1;i++)
		{
			cout<<"D"; 
		}
		for(i=1;i<=b2-b1;i++)
		{
			cout<<"L"; 
		}
		for(i=1;i<=a2-a1;i++)
		{
			cout<<"U"; 
		}		
		return 0; 
	} 
	
	return 0;
} 
```


---

## 作者：Clarinet (赞：0)

这么水的题居然没人？我来水一篇题解！

[博客食用观感更佳](https://www.luogu.com.cn/blog/Czel-X/ti-xie-17-post)
# 简要题意
有一张长和宽都为 $n$ 的网格图，每个点都有一只袋鼠，求在所有袋鼠共同行动下到达给定点要怎么走。
# 分析
模拟题，建议评红或橙都可以。

这题给人的感觉就像创纸使所有纸都对齐一样，我们可以通过袋鼠不会超过边界的特性来使所有袋鼠都移动到边界，那么他们的某一坐标就会相等。

至于是移动到哪一边界，就取决于定点到哪里近，具体表现为 $2 \times i$、$2 \times j$ 和 $n$ 的大小关系。很明显超过 $n$ 的一半肯定就往 $n$ 的方向走了。

为了代码简便点，我们先搞定横坐标，再搞定纵坐标也是没问题的。
# 代码
~~好像是目前题解区最短的~~。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
int main(){
	cin>>n>>x>>y;
	if(2*x<=n){
		for(int i=1;i<n;i++)cout<<"U";
		for(int i=1;i<x;i++)cout<<"D";
	}
	else{
		for(int i=1;i<n;i++)cout<<"D";
		for(int i=n;i>x;i--)cout<<"U";
	}
	if(2*y<=n){
		for(int i=1;i<n;i++)cout<<"L";
		for(int i=1;i<y;i++)cout<<"R";
	}
	else{
		for(int i=1;i<n;i++)cout<<"R";
		for(int i=n;i>y;i--)cout<<"L";
	}
	return 0;
}
```
感谢阅读！

---

