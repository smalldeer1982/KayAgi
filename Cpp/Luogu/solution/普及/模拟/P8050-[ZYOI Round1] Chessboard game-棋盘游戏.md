# [ZYOI Round1] Chessboard game/棋盘游戏

## 题目背景

子衿有一个游戏棋盘，此时准备拿出来玩玩。

## 题目描述

她的棋盘是 L 字形的，由上面一个 $n_1 \times m_1$ 的小长方形和下面一个 $n_2 \times m_2$ 的大长方形组成。棋盘初始状态所有格子上的数都为 $k$。

比如，当 $n_1 = 2$，$m_1 = 2$，$n_2 = 3$，$m_2 = 4$，$k = 0$ 时，棋盘初始是这样的：

```
0 0
0 0
0 0 0 0
0 0 0 0
0 0 0 0
```

现在她要进行若干次操作：将相邻的两个格子中的数同时加 $1$ 或减 $1$。操作完成后她会记住这些格子上的数。

可是她有一次不小心，经过若干次操作后忘掉了其中某一个数是多少了，于是在上面打了一个 $999999$。请你通过编程求出被打上 $999999$ 的数应该是多少。保证有且仅有一个格子被打上了 $999999$。

## 说明/提示

对于 $40\%$ 的数据，$n_1 = m_1 = 0$。

对于 $100\%$ 的数据，$m_1 < m_2$，$0 \le n_1,m_1,k \le 100$，$1 \le n_2,m_2 \le 100$，每个格子中的数 $\ge -1000$ 且 $\le 1000$，除前 $40\%$ 的数据外剩下的 $60\%$ 的数据保证 $n_1,m_1 > 0$。

**【样例说明】**

一开始棋盘是这样的：

```
0 0
0 0
0 0 0 0
0 0 0 0
0 0 0 0
```

下面给出一种可行的操作方案：

先将第 $2$ 行第 $1$ 个数与第 $3$ 行第 $1$ 个数同时加 $1$：

```
0 0
1 0
1 0 0 0
0 0 0 0
0 0 0 0
```

再将第 $3$ 行第 $1$ 个数与第 $3$ 行第 $2$ 个数同时加 $1$：

```
0 0
1 0
2 1 0 0
0 0 0 0
0 0 0 0
```

再将第 $3$ 行第 $3$ 个数与第 $4$ 行第 $3$ 个数同时加 $1$：

```
0 0
1 0
2 1 1 0
0 0 1 0
0 0 0 0
```

最后将第 $4$ 行第 $2$ 个数与第 $4$ 行第 $3$ 个数同时加 $1$：

```
0 0
1 0
2 1 1 0
0 1 2 0
0 0 0 0
```

可以得出被打上 $999999$ 的数（第 $4$ 行第 $3$ 个数）为 $2$。

操作方案可能不唯一，但可以证明答案是唯一的。

## 样例 #1

### 输入

```
2 2 3 4 0
0 0
1 0
2 1 1 0
0 1 999999 0
0 0 0 0```

### 输出

```
2```

# 题解

## 作者：gzlinzy (赞：11)

考虑将棋盘黑白染色。

将

```latex
0 0
0 0
0 0 0 0
0 0 0 0
0 0 0 0
```
染成

```latex
1 0
0 1
1 0 1 0
0 1 0 1
1 0 1 0
```

其中 1 代表黑色，0 代表白色。

此时白色格子相邻的格子一定是黑色，黑色格子相邻的格子一定是白色。因此将相邻的两个格子中的数同时加 1 或减 1，这两个格子必定一黑一白。那么每次操作后黑格子之和与白格子之和作差，差值不变。

我们可以求出一开始黑格子之和与白格子之和的差，再求出操作后除未知格外黑格子之和与白格子之和的差，二者相减便是答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n1,m1,n2,m2,k,x,inf=999999,suma,sumb,sum,flag;
int main(){
	cin>>n1>>m1>>n2>>m2>>k;
	for(int i=1;i<=n1;i++){
		for(int j=1;j<=m1;j++){
			cin>>x;
			if(x==inf){		//若是未知格 
				x=0;		//不计录它的值 
				if((i&1)==(j&1))flag=1;		//记录它的颜色 
			}
			if((i&1)==(j&1)){  //若是黑色格 
				suma+=x;
				sumb++;
			}
			else{		//若是白色格 
				suma-=x;
				sumb--;
			}
		}
	}
	for(int i=n1+1;i<=n1+n2;i++){
		for(int j=1;j<=m2;j++){
			cin>>x;
			if(x==inf){		//同上 
				x=0;
				if((i&1)==(j&1))flag=1;
			}
			if((i&1)==(j&1)){
				suma+=x;
				sumb++;
			}
			else{
				suma-=x;
				sumb--;
			}
		}
	}
	sum=suma-sumb*k;	//sumb 表示黑色格子数与白色格子数之差，乘 k表示黑格子之和与白格子之和的差
	if(flag)sum*=-1;	//根据未知格颜色确定答案 
	cout<<sum;
	return 0;
}
```

无注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n1,m1,n2,m2,k,x,inf=999999,suma,sumb,sum,flag;
int main(){
	cin>>n1>>m1>>n2>>m2>>k;
	for(int i=1;i<=n1;i++){
		for(int j=1;j<=m1;j++){
			cin>>x;
			if(x==inf){ 
				x=0; 
				if((i&1)==(j&1))flag=1; 
			}
			if((i&1)==(j&1)){ 
				suma+=x; 
				sumb++;
			}
			else{ 
				suma-=x;
				sumb--;
			}
		}
	}
	for(int i=n1+1;i<=n1+n2;i++){
		for(int j=1;j<=m2;j++){
			cin>>x;
			if(x==inf){ 
				x=0;
				if((i&1)==(j&1))flag=1;
			}
			if((i&1)==(j&1)){
				suma+=x;
				sumb++;
			}
			else{
				suma-=x;
				sumb--;
			}
		}
	}
	sum=suma-sumb*k; 
	if(flag)sum*=-1; 
	cout<<sum;
	return 0;
}
```


---

## 作者：c7h5n3o6_tnt (赞：9)

这应该是目前，最短的代码了吧。

~~作为 MOer，不写一篇题解，不应该啊。~~

## 分析：

首先，我们可以将棋盘黑白二染色。例如 $n_1 = 2$，$m_1 = 2$，$n_2 = 3$，$m_2 = 4$ 时，我们可以这样染色：

![](https://cdn.luogu.com.cn/upload/image_hosting/n2mfoj4r.png)

显然：对于每一次操作，黑白格数字和的差是不变的。

于是我们可以创建一个 `sum` 变量，当我们见到黑格时，`sum` 就会加上 `x-k`，反之，就减去 `x-k`。最后，通过 `sum` 的值，输出结果。这样，空间是 $O(1)$ 的。

## 代码：

```cpp
#include <iostream>
using namespace std;
int n1, m1, n2, m2, k, x, sum = 0, times, bk;
//变量bk的含义是：如果当前格子是黑格，则bk=1；否则bk=-1。
int main() {
    cin >> n1 >> m1 >> n2 >> m2 >> k;
    for (int i = 1; i <= n1; i++)
        for (int j = 1; j <= m1; j++) {
            cin >> x;
            bk = ((i + j) % 2) ? 1 : -1;
            if (x == 999999)
                times = bk;
            else
                sum += bk * (x - k);
        }
    for (int i = 1; i <= n2; i++)
        for (int j = 1; j <= m2; j++) {
            cin >> x;
            bk = ((i + j + n1) % 2) ? 1 : -1;
            if (x == 999999)
                times = bk;
            else
                sum += bk * (x - k);
        }
    cout << k - sum * times;
    return 0;
}
```

---

## 作者：Inter12 (赞：5)

好不容易拿到 AC，看到各位大佬用的是**黑白染色**的方法，非常简单，但是~~蒟蒻没有这个实力想到这一块去~~我想发一个 BFS 的写法。

## 前记

### 黑白染色的结论与原理

其实大佬们已经讲的很清楚了，在这里先把结论抛出：

$$\sum^{a_{i, j}}_{i = 0, j = 0(mod \ 2)} - \sum^{a_{i, j}}_{i = 1, j = 1(mod \ 2)} = k$$

简而言之，就是将格子按照国际象棋一样黑白染色，然后黑格子中的总值与白格子中的总值，无论操作多少次，都不变。

按照反证法，假设上述结论不成立，每一次操作都有可能改变原差值：

那么改变的差值必定在 $1$ 和 $2$ 中。

首先判断改变差值 $2$, 唯一的操作就是：改变两个同种类格子。由于黑白染色遵寻条件：任何相邻两格都不是同一种格子，因此改变不了两个同种类格子。

其次判断改变差值 $1$,但很显然，要想达到这一点，就只能更改一个格子，与原题不符。

故原假设不成立，反证完毕。

剩下的操作，这里不再累赘。

## 正题：分析

### 运用 BFS 的原理

我们发现，由于没有操作限制，可以将进行的操改为移动，如下：（Word 文档绘制）

![?](https://cdn.luogu.com.cn/upload/image_hosting/zrrd1snz.png)

我们执行两次操作，这样就可以达到当前的格子移动了，不过值会取反：

![?](https://cdn.luogu.com.cn/upload/image_hosting/l1upssvz.png)

这样，就会实现一个移动的目标。

我们在选择一个值的时候，将其他的值忽略，就如上图我们所选的 $2$ 一样，移动一格，变成其的相反数。

**然而，我们这么理解有什么用吗？**

当然有用。在我们找到那个我们所需求的值的时候，将所有非初始状态下的数（除了所求值之外）都**一步一步挪到**所求值的格子里去（注意每挪一步就要变一次相反数），随后我们就会~~惊奇的~~发现，格子变成了这样：（按照样例所给）

![?](https://cdn.luogu.com.cn/upload/image_hosting/9w8ily9t.png)

那一个仅剩的格子中的值正好是答案的相反数！

**为什么呢？**

首先，我们得知道，这个“在选择一个值的时候，将其他的值忽略，就如上图我们所选的 $2$ 一样，移动一格，变成其的相反数”的操作是可行的。因为他也是由一个一个**合法的**操作组成的，只是为了理解起来更方便。

其次，**我们按照逆思维，转换目标**，于是目标就变为了让棋盘恢复初始状态，也就是所有格子上的数都恢复为 $k$,那么，我们用一个个的**合法的**操作，按上述要求执行，最后会得到一个除了未知值，其他棋盘格子全都是要求数值。

但是，要想让当前的格子**也恢复**初始值，那么就需要变动它本身。因为整个棋盘中只有加减法操作，因此将他的初始值设为他的相反数就可以抵消模拟的数值。

**我按你的方法去做了，却仍然WA了，为什么？**

因为其中有一个名叫 $k$ 的捣蛋鬼！这一切推论只是在 $k$ **为零**的情况下进行的。

那么，我们就用最粗暴的办法：将所有值全部减去一个 $k$,使得初始棋盘的默认值变为 $0$。

**注意，结果应该扩大** $k$,**因为实际上的** $k$ **非零。**

### 如何运用 BFS

按照上述推论，我们可以对于每一个非默认的值跑一遍 $DFS/BFS$，模拟整个过程。

时间复杂度 $O(n^4)$，理论上可过，但还有优化。

注：这里的 $n$ 只是笼统的计算，无需在意。

**那么，优化呢？**

有两种优化方法。

- 第一种：直接计算曼哈顿距离，时间复杂度 $O(n^2)$

这一种应该是很简便的吧。

数学课中我们就可以知道，当一个数 $a$ 前面出现了很多次相反数操作，也可以叫做添了很多负号的时候，化简符号的方法便是**奇负偶正**。因此计算曼哈顿距离，可以直接知道到达地方的数值。

只需暴力枚举所有单元格即可。

- 第二种：BFS 优化，时间复杂度 $O(n^2)$

这一种略显复杂。

我们发现，暴力是一个多起点，单终点的 DFS/BFS，我们可以**逆思维，将其转化为一个单起点，多终点的** BFS。

仍是**奇负偶正**，直接求解即可。

## 代码核心：（第二种优化）

```cpp
void bfs(int x, int y)
{
	queue<node> q;
	vis[x][y] = true;
	node cur = {x, y, 0};
	q.push(cur);
	while(!q.empty())
	{
		node cur = q.front();
		q.pop();
		if(cur.x != x || cur.y != y)
		{
			if(cur.step % 2 == 0)
				sum += a[cur.x][cur.y];
			if(cur.step % 2 == 1)
				sum -= a[cur.x][cur.y];
		}
		for(int i = 1; i <= 4ll; i++)
		{
			int nx = cur.x + dx[i];
			int ny = cur.y + dy[i];
			if(!vis[nx][ny] && nx <= n1 + n2 && ny <= m2 && (ny <= m1 || (ny > m1 && nx > n1)) && ny > 0 && nx > 0)
			{
				node nxt = {nx, ny, cur.step + 1};
				q.push(nxt);
				
				vis[nx][ny] = true;
			}
		}
	}
	return ;
}
```

---

## 作者：C_S_L (赞：3)

采用常见的黑白染色法。

将棋盘黑白间隔染色。

举个例子：

对样例中的棋盘进行黑白染色：

![黑白染色-样例](https://cdn.luogu.com.cn/upload/image_hosting/fephklfy.png)

记初始所有黑格中的数的和为 $S_1$，所有白格中的数的和为 $S_2$，操作后所有黑格中的数的和为 $S_3$，所有白格中的数的和为 $S_4$。

因为每次操作选择相邻的两个格子（必然为一个黑格与一个白格）中的数同时加 $1$ 或减  $1$，所以，任何时候，所有黑格中的数的和与所有白格中的数的和的差保持不变。

由此我们可以得出：$S_1-S_2=S_3-S_4$。

而实际上缺了一个黑格或一个白格中的数，所以将 $S_3$ 和 $S_4$ 算出来，用上面的式子进行计算，求出缺少的那个数。

代码难度不高，模拟即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int n1,m1,n2,m2,k,a,s1,s2,s3,s4;
bool flag;
int main(){
	scanf("%d%d%d%d%d",&n1,&m1,&n2,&m2,&k);
	for(int i=1;i<=n1;++i){
		for(int j=1;j<=m1;++j){
			scanf("%d",&a);
			if(a==999999){
				flag=(i%2==j%2);
				a=0;
			}
			if(i%2==j%2){
				s1+=k;
				s3+=a;
			}
			else{
				s2+=k;
				s4+=a;
			}
		}
	}
	for(int i=n1+1;i<=n1+n2;++i){
		for(int j=1;j<=m2;++j){
			scanf("%d",&a);
			if(a==999999){
				flag=(i%2==j%2);
				a=0;
			}
			if(i%2==j%2){
				s1+=k;
				s3+=a;
			}
			else{
				s2+=k;
				s4+=a;
			}
		}
	}
	if(flag){
		printf("%d\n",s1-s2+s4-s3);
	}
	else{
		printf("%d\n",s2-s1+s3-s4);
	}
	return 0;
}
```


---

## 作者：qcf2010 (赞：2)

## 思路
考虑将整个棋盘染成像国际象棋棋盘一样的黑白色。

![](https://cdn.luogu.com.cn/upload/image_hosting/dezt3bct.png)

[图片的原作者。](https://www.luogu.com.cn/user/461745)

为什么要这么做呢？

观察这个棋盘，可以发现三个结论：
- 任意两个相邻的格子颜色总是不同。
- 黑色格子数一定是等于白色格子数的。
- 由第二点进一步得到，在最开始时，黑白格子上方的数之和也是相等的。

这些结论有什么用吗？

仔细思考一下，假设现在按照题意，对任意两个相邻格子上的数同时加 $1$，那么一个数必定就加在了黑格子上，另一个数必定就加在了白格子上。对于减 $1$，也是同理。

所以，如果所有操作都正确，黑白格子上的数之和应该是相等的。反之，若某一个格子上的数不知道了，又已知该格子是什么颜色，那么就可以顺利地求出该格子上的数。问题解决。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n1,m1,n2,m2,k,x,t,id,now;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n1>>m1>>n2>>m2>>k;
	for(int i=1;i<=n1;i++){
		for(int j=1;j<=m1;j++){
			cin>>x;
			t=(((i+j)%2)?1:-1);
			if(x==999999) id=t;
			else now+=(x-k)*t;
		}
	}
	for(int i=1;i<=n2;i++){
		for(int j=1;j<=m2;j++){
			cin>>x;
			t=(((i+j+n1)%2)?1:-1); //注意这里的判断条件
			if(x==999999) id=t;
			else now+=(x-k)*t;
		}
	}
	cout<<k-now*id;
	return 0;
}

```

---

## 作者：2012_Zhang_ (赞：2)

## 思路解析
[题目传送门](https://www.luogu.com.cn/problem/P8050)\
首先，这道题可以用黑白染色解决。\
将相邻格子以黑白隔开，可以保证每次操作必定在一黑一白两格中进行，不管是同时加一，还是减一，黑白格的操作造成改变的总和之差必定不变，它的初始值是 $0$。\
既然如此可以统计黑白格各自的改变的总和，并找出差，计算出缺漏，加上 $k$ 就是答案。

奉上代码：
## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n1,m1,n2,m2,k,ans=0;
    bool f=0;
    cin>>n1>>m1>>n2>>m2>>k;
    for(int i=1;i<=n1;i++){
        for(int j=1;j<=m1;j++){
            int now;
            cin>>now;
            if(now==999999){
                if((i+j)%2==0) f=1;
                else f=0;//确定未知值处于黑格还是白格
            }else{
                if((i+j)%2==0) ans+=now-k;
                else ans-=now-k;//计算改变的总值之差
            } 
        }
    }
    for(int i=1;i<=n2;i++){//操作如上
        for(int j=1;j<=m2;j++){
            int now;
            cin>>now;
            if(now==999999){
                if((i+j+n1)%2==0) f=1;
                else f=0;
            }else{
                if((i+j+n1)%2==0) ans+=now-k;
                else ans-=now-k;
            } 
        }
    }
    if(f) cout<<k-ans;
    else cout<<k+ans;
    return 0;
}

---

## 作者：pjh0625 (赞：1)

考虑将棋盘黑白染色。

其中 1 代表黑色，0 代表白色。

此时白色格子相邻的格子一定是黑色，黑色格子相邻的格子一定是白色。因此将相邻的两个格子中的数同时加 1 或减 1，这两个格子必定一黑一白。那么每次操作后黑格子之和与白格子之和作差，差值不变。

我们可以求出一开始黑格子之和与白格子之和的差，再求出操作后除未知格外黑格子之和与白格子之和的差，二者相减便是答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n1,m1,n2,m2,k,x,y,a,b;
int main(){
	cin>>n1>>m1>>n2>>m2>>k;
	for(int i=1;i<=n1;i++){
		for(int j=1;j<=m1;j++){
			cin>>x;
			y=(((i+j)%2)?1:-1);
			if(x==999999)  a=y;
			else  b+=(x-k)*y;
		}
	}
	for(int i=1;i<=n2;i++){
		for(int j=1;j<=m2;j++){
			cin>>x;
			y=(((i+j+n1)%2)?1:-1); 
			if(x==999999)  a=y;
			else  b+=(x-k)*y;
		}
	}
	cout<<k-b*a;
	return 0;
}
```

---

## 作者：keepwatcher_kensap (赞：1)

## Part 1 题意

有一个 $L$ 行的棋盘，这个棋盘每个格子的初始值都是 $k$，可以对这个棋盘进行若干次操作，每次操作都是对棋盘相邻的两格同时加 $1$ 或减 $1$，已知这个棋盘现在每一格的状况，求出未知格的状态。

## Part 2 思路

对于每一次操作，必定是对相邻的两格进行操作。那我们就很容易想到将整个棋盘分为黑白两区：


```
1 0 1 0
0 1 0 1
1 0 1 0
0 1 0 1 0 1 0
1 0 1 0 1 0 1
0 1 0 1 0 1 0
1 0 1 0 1 0 1
```

为什么呢？因为无论每一次操作，都是会改变一个黑格子和一个白格子的数值，并且改变的程度也都是一样的。换言之：

- 黑格子总值与白格子总值的差的绝对值成定值。

知道棋盘的初始状况，我们可以求出上述定值，再判断未知格子时位于黑区还是白区。如果是黑区，求出白区的总和和黑区目前的总和就可以推出答案了，如果是白区则相反。

## Part 3 代码

```
#include <bits/stdc++.h>
using namespace std;
int n1,m1,n2,m2,a[205][205],sum1,sum2,sum3,sum4,k,op;
bool check(int x,int y)
{
	return ((x+y)%2==0)?true:false;
}
int main()
{
	cin>>n1>>m1>>n2>>m2>>k;
	for (int i=1;i<=n1;i++)
	{
		for (int j=1;j<=m1;j++)
		{
			cin>>a[i][j];
			if (a[i][j]==999999)
			{
				if (check(i,j)) sum1+=k,op=1; else sum2+=k,op=0;
			}
			else if (check(i,j)) sum1+=k,sum3+=a[i][j];
			else sum2+=k,sum4+=a[i][j];
		}
	}
	for (int i=n1+1;i<=n1+n2;i++)
	{
		for (int j=1;j<=m2;j++)
		{
			cin>>a[i][j];
			if (a[i][j]==999999)
			{
				if (check(i,j)) sum1+=k,op=1; else sum2+=k,op=0;
			}
			else if (check(i,j)) sum1+=k,sum3+=a[i][j];
			else sum2+=k,sum4+=a[i][j];
		}
	}
	if (op==1) cout<<sum4-sum3-(sum2-sum1)<<endl;
	else cout<<sum3-sum4-(sum1-sum2)<<endl;
	return 0;
}

```

---

## 作者：V1mnkE (赞：1)

~~一道很经典的小学奥数题~~


## 思路
第一眼看到这道题，这不染色吗，让我们回顾一下小学学的知识。

-----------------------------
染色方法是一种对题目所研究的对象用直观形象的染色来进行分类的方法。象国际象棋的棋盘那样,我们可以把研究的对象染上不同的颜色,使问题变得浅显明了，方便研究 。 ----------- 百度。

就拿样例来说，把棋盘黑白染色（这里用 01 代替），得到如下的图。
```cpp
1 0
0 1
1 0 1 0
0 1 0 1
1 0 1 0
```
可以看出相邻的两个格子必然是一黑一白，那么每次操作完黑格之和与白格之和的差显然是不变的，那么根据这个，我们不算未知格，计算一开始黑格的和与白格的和的差，然后计除未知格之外黑格的和与白格的和的差，用后者减去前者就得到了未知格的数。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,n_,m_,k;
int h,w,a,b,flag,l[205][105]; 
int main(){
	cin>>n>>m>>n_>>m_>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>l[i][j];
			if(l[i][j]==999999){  
				if(i%2!=j%2){ 
					a+=k;
					flag=1;
				}
				else{
					b+=k;
					flag=0;
				}
			}
			else{ 
				if(i%2!=j%2){
					a+=k;
					h+=l[i][j];
				}
				else{
					b+=k;
					w+=l[i][j];
				}
			}
		}
	}
	for(int i=n+1;i<=n+n_;i++){
		for(int j=1;j<=m_;j++){
			cin>>l[i][j];
			if(l[i][j]==999999){
				if(i%2!=j%2){
					a+=k;
					flag=1;
				}
                else{
					b+=k;
					flag=0;
				}
			}
            else{ 
				if(i%2!=j%2){
					a+=k;
					h+=l[i][j];
				}
				else{
					b+=k;
					w+=l[i][j];
				}
			}
		}
	}
	if(flag)cout<<w-h-(b-a);
	else cout<<h-w-(a-b); 
	return 0;
}
```


---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8050)

给整个棋盘黑白染色，规定横纵坐标奇偶性相同的为黑格，否则为白格。

对于每次操作，选定的两个格子是相邻的，必然有一个是黑格，另一个是白格。所以无论如何操作，黑格中数和与白格中数和之差永远是不变的。

所以我们可以事先处理初始状态中黑格与白格中数和之差，以及最终状态中除去空格后黑格与白格中数和之差，给这两个结果作差即可求出答案。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n1, n2, m1, m2, k, a[201][201], col[201][201], n, m, f, sum, sumk;
signed main(){
	scanf("%d%d%d%d%d", &n1, &m1, &n2, &m2, &k);
	for (int i = 1; i <= n1; i++)
		for (int j = 1; j <= m1; j++){
			scanf("%d", &a[i][j]);
			int op = (i % 2 == j % 2 ? 1 : -1);//判断奇偶性
			sumk += k * op;//计算初始和
			if (a[i][j] != 999999) sum += a[i][j] * op;//计算最终和
			else f = op;
		}
	for (int i = n1 + 1; i <= n1 + n2; i++)
		for (int j = 1; j <= m2; j++){
			scanf("%d", &a[i][j]);
			int op = (i % 2 == j % 2 ? 1 : -1);
			sumk += k * op;
			if (a[i][j] != 999999) sum += a[i][j] * op;
			else f = op;
		}//同上
	printf("%d\n", (sumk - sum) / f);
	return 0;
}
```

---

## 作者：Vct14 (赞：0)

暑假调了一天没调出来，今天又看到结果十分钟调出来了。死因：未知格子没算初始格子上的数。

小奥典题。将棋盘黑白染色，相邻格同加减黑白差不变。求出未知格的颜色，再求出黑白现在的差和最开始的差（为黑白格子数的差乘 $k$）并作差即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

int n1,m1,n2,m2,k;
bool blk=true,lb=true,x;
int sum,c;

void rec(int n,int m){ // 处理一个长方形
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			int a;cin>>a;
			if(a==999999){
				x=blk;
				if(x) c+=k;
				else c-=k;
				blk=!blk;
				continue;
			}
			if(blk) sum+=a,c+=k;
			else sum-=a,c-=k;
			blk=!blk;
		}
		lb=!lb;
		if(lb) blk=true;
		else blk=false;
	}
}

int main(){
	cin>>n1>>m1>>n2>>m2>>k;
	rec(n1,m1);rec(n2,m2);
	cout<<(x?c-sum:sum-c);
	return 0;
}
```

---

