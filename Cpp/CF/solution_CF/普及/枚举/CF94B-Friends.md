# Friends

## 题目描述

有一天，一个叫做伊戈尔-凯的人放弃编程，转攻数学题。一个深秋的夜晚，他坐在桌旁读书，想着数学问题。
书上有着一段话吸引了他的注意：“在任六人中有三个人互相认识或互相不认识。”
伊戈尔完全无法理解为什么至少有六个人。“那对不起，我觉得五个人也一样，”他脑子里开始胡思乱想“让我试试...马克思，利亚，瓦娃--他们互相认识，额..再加一个迪玛和欧莱格，对瓦娃来说他们三个互不认识！哈哈哈哈哈，这个定理就是一个渣渣。”
伊戈尔带着他的5个朋友，让他们记下来，他们中谁互为朋友。现在他想看看这五个人是否真的认识三对或三对不认识的人。

## 样例 #1

### 输入

```
4
1 3
2 3
1 4
5 3
```

### 输出

```
WIN
```

## 样例 #2

### 输入

```
5
1 2
2 3
3 4
4 5
5 1
```

### 输出

```
FAIL
```

# 题解

## 作者：lrq090403 (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF94B)

### 题目大意

给定一个含 $5$ 个点与 $m$ 条线的无向图，求是否至少有 $3$ 个点连通或不连通。

* 如果是，输出 `WIN`；否则输出 `FAIL`。
* $1 \le m \le 10$，保证无重边与自环。

### 题意分析

对于这个题目，楼上的神犇们都使用 $O(n^3+m)$ 的复杂度切掉了本题。但是这里有更快的 $O(m)$ 做法可供使用。

可使用分类讨论进行解答。

设这 $5$ 个点为 $a_{1},a_{2},a_{3},a_{4},a_{5}$，则通过对点 $a_{1}$ 的度数进行讨论。

1. $a_{1}$ 的度数为 $4$。

如图，此时 $a_{2},a_{3},a_{4},a_{5}$ 都不连通，但此图只要再连一条边就会有 $3$ 个点连通，易得此时输出 `WIN`。

![](https://cdn.luogu.com.cn/upload/image_hosting/3xhrsrl4.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

2. $a_{1}$ 的度数为 $3$。

如图，此时 $a_{2},a_{3},a_{4}$ 不连通，但此图只要再在这些点间连一条边就会有 $3$ 个点连通，易得此时输出 `WIN`。

![](https://cdn.luogu.com.cn/upload/image_hosting/ux8i4v7n.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

3. $a_{1}$ 的度数为 $2$。

此时 $a_{2},a_{3}$ 的度数为 $1$，所以可以选择连接 $a_{4}$ 或 $a_{5}$（否则将会转化为上面两条）。  
但当它们都连接一个点时另一个点必会与 $2$ 个点互不连通，输出 `WIN`。  
否则 $a_{4},a_{5}$ 的度数都为 $1$，连接它们即可使所有点的度数为 $2$，易证得无任意 $3$ 点连通或不连通，输出 `FAIL`。

**所以当所有点的度数都为** $2$ **时，输出** `FAIL` **，其余情况输出** `WIN`。

### 代码实现
```cpp
#include<iostream>
using namespace std;
int d[6],m,i,a,b;//d 数组用来存各个点的度数。
int main(){
	cin>>m;
	for(i=1;i<=m;++i){
		cin>>a>>b;
		++d[a],++d[b];
	}
	for(i=1;i<=5;++i)
		if(d[i]^2){//等价于 if(d[i]!=2)
			printf("WIN");
			return 0;
		}
	printf("FAIL");
	return 0;
}

```

---

## 作者：ncwzdlsd (赞：2)

一道比较简单的图论题，可以分情况讨论解决。

先把问题转化成图论题：给定一个有 $5$ 个点与 $m$ 条边的无向图，求是否有不少于三个点连通或不连通。

先统计每个点的度数，然后考虑对一个点入度的几个值进行分情况讨论。画图可知，如果一个点的度数为 $3$ 或 $4$，只要再连一条边就可以实现题目要求，所以一定输出 `WIN`。但是对于度数为 $2$ 的点，无论如何连边都不可能使得有不少于三个点连通或不连通，所以是 `FAIL`。

于是乎问题变得简单了，统计所有点的度数，当前节点所有点的度数都为 $2$ 时，输出 `FAIL`，否则输出 `WIN`。时间复杂度为 $O(m)$。

主体代码如下：

```cpp
for(int i=1;i<=m;i++)
	cin>>a>>b,du[a]++,du[b]++;
for(int i=1;i<=5;i++)
	if(du[i]!=2)
		puts("WIN"),exit(0);
	puts("FAIL");
```

---

## 作者：Farkas_W (赞：2)

$$\texttt{题目大意}$$

$\quad$题目的意思是如果 $5$ 人有 $3$ 个人都认识或都不认识则证明这个定理就是一个渣渣，伊戈尔·凯赢("WIN")，不存在即证明他输了("FAIL")

$$\texttt{思路}$$

$\quad$一开始以为是并查集，结果发现 $m<=10$，$a_i<=5$，$b_i<=5$，暴力枚举即可，那么这题也估计就红题的难度，时间复杂度 $O(5^3)$。

$\quad$用 $a_{i,j}=1$ 表示 $i$ 和 $j$ 互相认识，从这五个人中枚举三个人 $(i,j,k)$ 判断这三人都认识或都不认识即可。

```
if((a[i][j]&&a[i][k]&&a[j][k])||(!a[i][j]&&!a[i][k]&&!a[j][k]))flag=1;//核心代码
```
$\quad$用 $flag$ 来判断，为 $1$ 表示存在即输出 "WIN"，否则为 $0$ 输出 "FAIL"。

$\quad$**Code**
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define re register int
using namespace std;
int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
int n,a[6][6],flag;
signed main()
{
	n=read();
	for(re i=1,x,y;i<=n;i++)x=read(),y=read(),a[x][y]=a[y][x]=1;
	for(re i=1;i<=3;i++)  //注意i，j，k不重复
	{
    for(re j=i+1;j<=4;j++)
		{
      for(re k=j+1;k<=5;k++)
			if((a[i][j]&&a[i][k]&&a[j][k])||(!a[i][j]&&!a[i][k]&&!a[j][k]))
			flag=1;//核心代码，标记
		}
	}	
	if(flag)puts("WIN");else puts("FAIL");
	return 0;
}
```
~~希望能过~~

---

## 作者：dby_718 (赞：0)

# 题目描述

这是一道图论题，给一个有 $5$ 个点和 $m$ 条边的无向图，求是否有不少于三个点连通或不连通。

# 题目分析

先统计每个点的度数（即经过每个点的边数），对其进行分类讨论。

如果一个点的度数为 $3$ 或 $4$，那么只需要连接一条边就满足题意。

对于度数为 $2$ 的点，无论怎么连都无法使得有不少于三个点连通或不联通。

所以只有每个点度数都为 $2$ 的时候不满足题意，其它情况均满足题意。

接下来就是代码了。

```cpp
#include<iostream>
using namespace std;
int q[7],n,a,d;//q 数组统计每个点的度数， a 和 d 表示每条边连接的两个点
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a>>d;
        q[a]++;q[d]++;//统计每个点度数
    }
    for(int i=1;i<=5;i++){
        if(q[i]!=2){//只要有一个点度数不为 2 ，就满足题意，输出，结束程序
            cout<<"WIN"<<endl;return 0;
        }
    }
    cout<<"FAIL"<<endl;return 0;//此时每个点度数均为 2 ，不满足题意
}
```

求过。

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF94B)

## 思路

一道简单的图论题。

我们统计每个点的入度，之后循环遍历点编号是 $1$ 到 $5$ 的点。如果这个点入度不为 $2$，说明这几个人中有互相不认识的，直接输出 ``WIN``，结束程序。

如果遍历完所有的点编号，没有互相不认识的，输出 ``FAIL``。

完整代码这里就不放了。

---

## 作者：Cutler (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF94B)

看到第一眼感觉是并查集，但第二个样例都没过，我才发现这里面的坑点，$\texttt a$ 认识 $\texttt b$，$\texttt b$ 认识 $\texttt c$，$\texttt a$ 却不一定认识 $\texttt c$，不能用并查集。

好了，第一个方案 $\texttt{pass}$ 掉，瞄一眼数据范围，总共 5 个人，可以直接暴力求解。然后这题就解决了，枚举所有可能的匹配，看看是否存在互相认识或互相不认识，是就输出 $\texttt{"WIN"}$，否则输出 $\texttt{"FAIL"}$。时间复杂度 $O(5^3)$，空间复杂度 $O(5^2)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

int n = 5, m, f[6][6];

int main(){
    scanf("%d", & m);

    int a, b;
    while(m --){
        scanf("%d%d", & a,& b);
        f[a][b] = f[b][a] = 1;
    }

    for(int i = 1;i <= 3;++ i)
        for(int j = i + 1;j <= 4;++ j)
            for(int k = j + 1;k <= 5;++ k){
                if(f[i][j] & f[i][k] & f[j][k]){puts("WIN");return 0;}
                if(f[i][j] | f[i][k] | f[j][k]) continue;
                puts("WIN");return 0;
            }

    puts("FAIL");
    return 0;
}
```

优雅撒花。

---

## 作者：Hiro_Akiba (赞：0)

## 题意

给出五个人之间的关系（认识或不认识），判断是否有人与其余的两个人彼此不认识或彼此认识。

## 思路

一开始被题意绕了好久，后来才明白。

我们统计一个人与几个人认识，设  $f [ a ]$ 表示 $a$ 与几个人认识。

我们再把人抽象成点，认识抽象成边。

当 $f[a]=1$ 或者 $f[a]=0$ 时：

![](https://cdn.luogu.com.cn/upload/image_hosting/ss6qd9hx.png)

很明显，有一个点是孤立的，因为无论这个点与哪个点连都不会是 $1$ 。

然后每一个点都只有一条边，意味着必定会有超过两个人彼此不认识，
所以当 $f[a]=1$ 或者 $f[a]=0$ 就成功了。

当 $f[a]=2$ 时：

![](https://cdn.luogu.com.cn/upload/image_hosting/zpjngjp4.png)


每一个点都有两条边，意味着他认识的人互不认识，如果出现重边就另说，但题目中不会给出两次。

所以当 $f[a]$ 都等于 $2$ 时，一定不会成功。

当 $f[a]=3$ 或$f[a]=4$  时：

![](https://cdn.luogu.com.cn/upload/image_hosting/6xhdpwen.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/hz9n7sb5.png)

此时，没有一个点孤立，第一个条件成立，直接成功。

综上知，当 $f[a]$ 都为 $2$ 时失败，否则成功。

## 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int b[100];//记录每个人认识几个。
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
    	int x,y;
    	cin>>x>>y;
    	b[x]++;
    	b[y]++;
	}
	for(int i=1;i<=5;i++){
		if(b[i]!=2){//有一个不是 2 就行。
			cout<<"WIN";
			return 0;
		}
		
	}
	cout<<"FAIL";
	return 0;
}

```





















---

## 作者：人间凡人 (赞：0)

这道题其实是一道**大暴力**！！！

$f[i][j]$表示$i$与$j$是否认识。

若$f[i][j]=true$ 说明$i$与$j$认识，反之就不认识。

思路：输入$x$，$y$ 将$f[x][y]$变为$true$。 然后就只用O($5^3$)的暴力枚举任意三个人即可。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,f[6][6];
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		f[x][y]=f[y][x]=true;
	}
	for(int i=1;i<=5;i++)
		for(int j=i+1;j<=5;j++)
			for(int k=j+1;k<=5;k++){
				if(f[i][j]&&f[j][k]&&f[i][k]){
             //任意三个人认识
					printf("WIN\n");
					return 0;
				}
				if(!f[i][j]&&!f[j][k]&&!f[i][k]){
             //任意三个人不认识
					printf("WIN\n");
					return 0;
				}
			}
	printf("FAIL\n");
	return 0;
}

```



---

