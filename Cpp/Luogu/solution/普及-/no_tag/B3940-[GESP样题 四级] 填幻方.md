# [GESP样题 四级] 填幻方

## 题目描述

在一个 $N\times N$ 的正方形网格中，每个格子分别填上从 1 到 $N×N$ 的正整数，使得正方形中任一行、任一列及对角线的几个数之和都相等，则这种正方形图案就称为“幻方”（输出样例中展示了一个 $3×3$ 的幻方）。我国古代称为“河图”、“洛书”，又叫“纵横图”。

幻方看似神奇，但当 $N$ 为奇数时有很方便的填法：
1. 一开始正方形中没有填任何数字。首先，在第一行的正中央填上 $1$。
2. 从上次填数字的位置向上移动一格，如果已经在第一行，则移到同一列的最后一行；再向右移动一格，如果已经在最右一列，则移动至同一行的第一列。如果移动后的位置没有填数字，则把上次填写的数字的下一个数字填到这个位置。
3. 如果第 2 步填写失败，则从上次填数字的位置向下移动一格，如果已经在最下一行，则移到同一列的第一行。这个位置一定是空的（这可太神奇了！）。把上次填写的数字的下一个数字填到这个位置。
4. 重复 2、3 步骤，直到所有格子都被填满，幻方就完成了！

快来编写一个程序，按上述规则，制作一个 $N\times N$ 的幻方吧。

## 样例 #1

### 输入

```
3```

### 输出

```
8 1 6
3 5 7
4 9 2```

# 题解

## 作者：_Deer_Peach_ (赞：42)

纯模拟：

第一步：

把一填进第一行中央：
```
int x=0,y=n/2;
a[x][y]=1;
```
第二步：

需要变横、纵坐标：
```
int tx=(x+n-1)%n;//上次填数位置横轴变化
int ty=(y+1)%n;//上次填数位置纵轴变化
```
第三步：

第二步填数失败：
```
tx=(x+1)%n;//上次填数位置横轴变化
ty=y;//上次填数位置纵轴不变
```
最后：

结合代码：
```
#include<bits/stdc++.h>
using namespace std;
int n;
int a[25][25];
int main(){
	cin>>n;//输入
	int x=0,y=n/2;//初始坐标
	a[x][y]=1;//第一步操作：第一行中间填1
	for(int cnt=2;cnt<=n*n;cnt++){//重复第二步和第三步操作
		int tx=(x+n-1)%n;//上次填数位置横轴变化
		int ty=(y+1)%n;//上次填数位置纵轴变化
		if(a[tx][ty]==0){//第二步填数成功
			a[tx][ty]=cnt;//填数
		}else{//第二步没成功做第三步操作
			tx=(x+1)%n;//上次填数位置横轴变化
			ty=y;//上次填数位置纵轴不变
			a[tx][y]=cnt;//填数
		}
		x=tx;//更新横轴
		y=ty;//更新纵轴
	}
	for(int i=0;i<n;i++){//输出
		for(int j=0;j<n;j++){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;//结束
}

---

## 作者：lgydkkyd (赞：12)

本来这是一道要自己总结规律的构造题，但是由于本题告诉了我们构造幻方的规则，于是就变成了一道模拟，按照规则写即可，提示：输出别忘了换行。

------------
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int b[501][501];//定义幻方数组
int main(){
    int n;
    cin>>n;
    int j=0,k=n/2;
    b[j][k]=1;
    for(int i=2;i<=n*n;i++){
        if(j==0&&k!=n-1){
            b[n-1][k+1]=i;
            j=n-1;
            k++;
        }
        else if(k==n-1&&j!=0){
            b[j-1][0]=i;
            j--;
            k=0;
        }
        else if(j==0&&k==n-1){
            b[j+1][k]=i;
            j++;
        }
        else if(j!=0&&k!=n-1){
            if(b[j-1][k+1]==0){
                b[j-1][k+1]=i;
                j--;
                k++;
            }
            else{
                b[j+1][k]=i;
                j++;
            }
        }
    } 
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<b[i][j]<<" ";
        } 
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：LostKeyToReach (赞：10)

双倍经验：[P2615 [NOIP2015 提高组] 神奇的幻方](https://www.luogu.com.cn/problem/P2615)

这道题很简单，模拟即可。

设幻方为 $a$，$c$ 表示要填的数，则：
- 先设 $c$ 为 $1$。
- 将 $c$ 填入 $a_{1,\lceil \frac{n}{2} \rceil}$。
- 然后我们循环遍历直到 $c \ge n^2$（想一想，为什么不是 $c > n^2$），执行以下操作：
	- 设 $nx$ 为 $x$，$ny$ 为 $y$。
   - 将 $nx$ 减 $1$。如果 $nx$ 原来是 $1$，那么将 $nx$ 设为 $n$。
   - 将 $ny$ 加 $1$。如果 $ny$ 原来是 $n$，那么将 $ny$ 设为 $1$。
   - 这时候判断 $a_{nx,ny}$ 是否填过。如果没有填，那么将 $c$ 加 $1$，然后将 $c$ 填入 $a_{nx,ny}$，再令 $x=nx$，$y=ny$，跳过即可。
   - 否则，还原 $nx$ 和 $ny$，并将 $nx$ 加 $1$。如果 $nx$ 原来是 $n$，那么将 $nx$ 设为 $1$。
   - 再将 $c$ 加 $1$，填入 $a_{nx,ny}$ 即可。
   
重复以上步骤，幻方就可以填好，代码如下（增加了防抄袭字符！）：
```cpp
#include <iostream>
using namespace std;
int a[23][23];
int main() {
	int n;
	cin >> n;
	a[1][n / 2 + 1] = 1;
	int cnt = 1;
	int x = 1, y = n / 2 + 1;
	while (cnt < n * n) {
		int nx = x, ny = y;
		nx = ((nx == 1) ? n : nx - 1);
		ny = ((ny == n) ? 1 : ny + 1);
		if (a[nx][ny] == 0) {
			a[nx][ny] = ++cnt;
			x = nx, y = ny;
			continue;
		}
		nx = x, ny = y;
		nx = ((nx == n) ? 1 : nx + 1);
		a[nx][ny] = ++cnt;
		x = nx, y = ny;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << a[i][j] << ' ';
		}
		cout << endl;
	}
}
```

---

## 作者：Programming_Konjac (赞：6)

# 思路
~~双倍经验：此题与[P2615 NOIP2015 提高组 神奇的幻方](https://www.luogu.com.cn/problem/P2615)是一样的。~~

思路：暴力枚举。

我们用一个对组（pair）存储当前填的数的二维数组的下标 $pos$，初始化 $pos$ 的第一项（简称 `first`）等于 $1$，然后第二项（简称 `second`）是 $\lceil\frac{n}{2}\rceil$，然后设二维数组 $ans_{i,j}$ 存储的是第 $i$ 行第 $j$ 列的数字。

然后用 $i$ 从 $1$ 循环到 $n^2$，然后每一次循环先把 $ans_{pos_1,pos_2}=i$，然后进行判断：

- 如果 $ans_{((pos_1-2+n)\bmod n) + 1,(pos_2\bmod n)+1}$ 没有存过数（没有存过会等于 $0$），那么 $pos_1=((pos_1-2+n)\bmod n) + 1,pos_2=(pos_2\bmod n)+1$，第一项 $((pos_1-2+n)\bmod n) + 1$ 减 $2$ 再加 $1$，是为了防止出错，如果是 $(pos_1-1+n)\bmod n$，那么 $pos_1=1$ 的时候会出错。

- 否则 $pos_1=(pos_1\bmod n)+1$。

最后双层循环输出 $ans$ 数组即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[45][45];
pair<int,int> pos;
int main(){
	int n;
	cin>>n;
	pos={1,n/2+1};
	for(int i=1; i<=n*n; i++){
		ans[pos.first][pos.second]=i;
		ans[(pos.first-2+n)%n+1][pos.second%n+1]==0?(pos={(pos.first-2+n)%n+1,pos.second%n+1}):(pos={pos.first%n+1,pos.second});//运用了三步运算符进行赋值
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++) cout<<ans[i][j]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：huangzhixia (赞：5)

[**题目传送门**](https://www.luogu.com.cn/problem/B3940)

模拟题，个人觉得难度为红吧，橙有点过了。

按照题目中说的一步步模拟。

很简单，按照操作，早方阵的正中央也就是 $a_{\frac{n}{2},\frac{n}{2}}$。这里的 $a$ 表示存方阵的数组，$n$ 表示方阵的长度。

设当前位置为 $(i,j)$，要填的数为 $top$。

需要在 $a_{i -1.j}$ 的位置填 $top$。如果此时 $i$ 减之前等于 $1$，就把 $top$ 填在 $a_{n,j}$，接着把 $top + 1$，将 $top$ 填在 $a_{i,j+1}$ 的位置，同理，如果 $j$ 加一之前就等于 $n$ 了，将 $top$ 填在 $a_{i,1}$。

如果我以上说的不能完成，就做题目中的操作 3。

然后操作 3 如题目中的进行模拟。

一直进行操作 3，知道把 $top$ 等于 $n^2$ 为止。

~~你想要代码？不给！我没写（）~~

---

## 作者：2021zjhs005 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/B3940)。

如果说按照如上题目给定步骤操作，那么 $N$ 一定是奇数。

所以大胆地模拟即可。

- 令 $t$ 为当前填的数，$(x,y)$ 为当前坐标（未填）。


- 首先填入 $c$ 至 $a_{1,\frac{n}{2}}$。

- $x$ 减少 $1$，若 $x=0$ 则将 $x$ 设置为 $n$。

- $y$ 增加 $1$，如果 $y=n+1$，则将 $y$ 设置为 $1$。

- 如果 $a_{x,y}$ 有值了，需要向下填入 $(prex-1,prey)$，倒退回去即为 $(x+2,y-1)$，随后判断 $x$ 是否等于 $n+1$，是则将其修改为 $1$，随后填入 $t+1$。

- 反之 $a_{x,y} = 0$，直接填入 $t+1$。

- 最后 $t\to t+1$。

填完所有的 $n^2$ 个数即可。

代码容易实现，不展示了（~~明明是你要用[神奇的幻方](https://www.luogu.com.cn/problem/P2615)代码提交了，这题就懒得写。~~)

---

## 作者：yu1128_AKIOI (赞：0)

# 思路
按题目模拟即可，注意在第二条行不通时 $i,j$ 要赋为原值。
# 代码
```c
#include<bits/stdc++.h>
using namespace std;
int n,sum=1,a[22][22];
bool ck(){
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(!a[i][j]) return 0;
    return 1;
}
int main(){
    cin>>n;
    a[1][(n+1)/2]=1;
    int i=1,j=(n+1)/2;
    while(!ck()){
        int k=i,l=j;
        if(i>1) i--;
        else i=n;
        if(j+1<=n) j++;
        else j=1;
        if(!a[i][j]) a[i][j]=++sum;
        else{
            i=k;
            j=l;
            if(i<n) i++;
            else i=1;
            a[i][j]=++sum;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout<<a[i][j]<<" "; 
        cout<<endl;
    } 
 }
```

---

