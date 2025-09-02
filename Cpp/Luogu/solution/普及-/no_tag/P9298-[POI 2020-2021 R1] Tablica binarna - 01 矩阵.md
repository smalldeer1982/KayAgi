# [POI 2020/2021 R1] Tablica binarna / 01 矩阵

## 题目背景

**题目译自 [XXVIII Olimpiada Informatyczna – I etap](https://sio2.mimuw.edu.pl/c/oi28-1/dashboard/) [Tablica binarna](https://sio2.mimuw.edu.pl/c/oi28-1/p/tab/)。**

## 题目描述

矩阵 $A$ 有 $n$ 行 $m$ 列，行自上到下编号为 $1$ 至 $n$，列自左到右编号为 $1$ 到 $m$，因此可以用 $(i,j)$ 表示矩阵的第 $i$ 行第 $j$ 列的元素。且矩阵 $A$ 中每个元素的值为 $0$ 或 $1$。

最初，矩阵内的所有元素的值均为 $0$。接下来可以对该矩阵执行 $q$ 次修改操作。每次操作将给出四个参数 $i_1,j_1,i_2,j_2$，表示将以 $(i_1,j_1)$ 为左上角，$(i_2,j_2)$ 为右下角的矩形内的所有元素的值翻转（从 $0$ 变成 $1$，或从 $1$ 变为 $0$）。

如果一次操作中，矩形的左上角与矩阵的左上角重合（即 $i_1=j_1=1$），则称这次修改操作是**简单的**。

现在你想要知道，在每次对矩阵执行修改操作后，需要执行至少多少次**简单的**修改操作，使得矩阵内所有元素的值全部变为 $0$。

## 说明/提示

【样例解释1】：

![](https://s1.ax1x.com/2023/04/04/pp4jI2T.png)

【数据范围】：

所有测试点均满足：$1 \leq n,m \leq 10^3$，$1 \leq q \leq 10^5$。

| 子任务编号 | 约束          | 分值 |
| :----------: | :-------------: | :----: |
| $1$        | $n,m \leq 2$  | $14$ |
| $2$        | $q=1$         | $16$ |
| $3$        | $n=1$         | $21$ |
| $4$        | $n,m \leq 10$ | $9$  |
| $5$        | $n,m \leq 80$ | $10$ |
| $6$        | 无附加约束    | $30$ |

## 样例 #1

### 输入

```
2 3 3
1 2 2 2
1 1 2 1
1 2 1 3```

### 输出

```
2
1
3```

## 样例 #2

### 输入

```
4 4 16
1 1 1 1
1 2 1 2
1 3 1 3
1 4 1 4
2 1 2 1
2 2 2 2
2 3 2 3
2 4 2 4
3 1 3 1
3 2 3 2
3 3 3 3
3 4 3 4
4 1 4 1
4 2 4 2
4 3 4 3
4 4 4 4```

### 输出

```
1
1
1
1
3
3
3
1
3
3
3
1
3
3
3
1```

# 题解

## 作者：qwerty12346 (赞：6)


# [题目传送门](https://www.luogu.com.cn/problem/P9298)

### 题意+思路 

题目就是让我们求在很多次修改过后，需要执行至少多少次修改操作，让矩阵内所有元素的值全部变为 $0$。然后我们又发现奇数个翻转的位置每次操作只有 $4$ 个，所以只用打暴力即可。

### 代码
如下：
```
#include<bits/stdc++.h>
using namespace std;
int n,m,q,x,y,z,k,ret,a[1005][1005],s[1005][1005];
void w(int x,int y){
    if(x<1||y<1||x>n||y>m)return ;//判断是否出界
    ret-=s[x][y];
    s[x][y]^=1;
    ret+=s[x][y];
}
int main(){
    cin>>n>>m>>q;
    for(int i=1;i<=q;i++)
    {
	cin>>x>>y>>z>>k;
	w(x-1,y-1);
	w(z,k);
	w(x-1,k);				
	w(z,y-1); 
	cout<<ret<<endl;
    } 
    return 0;
}
```

---

## 作者：mbzdf (赞：4)

# P9298 题解

[传送门](https://www.luogu.com.cn/problem/P9298)

## 题目大意
> 有一个 $n$ 行 $m$ 列的 $01$ 矩阵 $(1 \le n, m \le 10^3)$，初始全为 $0$。每次将它的一个子矩阵反转，求每次反转过后，将原矩阵以简单反转还原为全是 $0$ 最少需要几次。（一个子矩阵，以原矩阵的 $(1, 1)$ 为它的一个顶点，以原矩阵任意点为另一个顶点，反转此矩阵被称为简单反转）

## 分析一下

我们发现，将任意一个矩阵反转，至多只需要 $4$ 次简单反转。
>
>```text
>012345
>1.....
>2..##.
>3..##.
>4..##.
>5.....
>```
>我们只需要以 $(4, 4)$、$(1, 4)$、$(2, 4)$ 和 $(1, 2)$ 为另一个顶点进行四次简单反转就能够还原了。

即当 $(x_1, y_1),(x_2, y_2)$ 被反转时，我们只需要以 $(x_1-1, y_1-1)$，$(x_1-1, y_2)$，$(x_2, y_1-1)$ 和 $(x_2, y_2)$ 为另一个顶点进行简单反转就行了。

并且当我们需要反转两次同一个矩阵时，不用反转。

#### 那么具体思路呢

记录每一个点的反转次数。记录上一次询问的答案，这里记为 $ans$。

当需要反转一个点时，如果它已经被反转了奇数次，则代表我们这次反转及上次反转都不用了，$ans$ 应减少 $1$，而如果是偶数次，则代表我们应反转一次这个点，$ans$ 应增加 $1$。

### 一个需要注意的事情

越界，即需要反转的点 $(x, y)$ 中，满足 $x < 1$，$x > n$，$y < 1$ 或 $y > m$，则不用反转。

## AC 代码
```cpp
#include <iostream>
using namespace std;
int n, m, q;
int a[1005][1005];
bool f[1005][1005];
long long int ans;
void set(int x, int y)
{
	if(!(x >= 1 && x <= n && y >= 1 && y <= m))
		return;
	if(f[x][y] == 1)
		--ans;
	else
		++ans;
	f[x][y] ^= 1;
}
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	int x1, y1, x2, y2;
	while(scanf("%d%d%d%d", &x1, &y1, &x2, &y2) != EOF)
	{
		set(x1 - 1, y1 - 1);
		set(x2, y2);
		set(x1 - 1, y2);
		set(x2, y1 - 1);
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：cryozwq (赞：3)

摘自 [POI 2020 题解](https://282751.blog.luogu.org/poi-2020-ti-xie)。


首先考虑给你一个矩阵算答案，每个点显然最多当成右端点一次，那么设 $s_{i,j}$ 表示这个点是否要进行操作，$s_{i,j}=1$ 当且仅当其右下方所有 $s_{i,j}$ 异或和不等于 $a_{i,j}$。写成代码大概就是：

```cpp
s[i][j]=s[i+1][j+1]^s[i+1][j]^s[i][j+1]^a[i][j];
ans+=s[i][j];
s[i][j]=s[i+1][j+1]^s[i+1][j]^s[i][j+1]^s[i][j];
```

然后把上面那个带入下面那个，发现 $s_{i,j}$ 的二维后缀和就是 $a_{i,j}$。
 
因此上述代码等价于：


```cpp
s[i][j]=a[i+1][j+1]^a[i+1][j]^a[i][j+1]^a[i][j];
ans+=s[i][j]; 
```

我们发现，这四个值有偶数个翻转的时候答案不变，而有奇数个翻转的位置每次操作只有 $4$ 个，暴力即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q; 
int a[3005][3005];
int s[3005][3005];
int ans=0;
void modify(int x,int y){
	if(x<1||y<1||x>n||y>m)return ;
	ans-=s[x][y];
	s[x][y]^=1;
	ans+=s[x][y];
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	while(q--){
		int ax,ay,bx,by;
		scanf("%d%d%d%d",&ax,&ay,&bx,&by);
		modify(ax-1,ay-1);
		modify(bx,by);
		modify(ax-1,by);				
		modify(bx,ay-1); 
		 
		//s[i][j]=a[i][j]^a[i+1][j]^a[i][j+1]^a[i+1][j+1]   
		
		printf("%d\n",ans);
	} 
	return 0;
}
```

---

## 作者：zhangzirui66 (赞：1)

这题有点像二维前缀和（个人认为）。

思路比较简单，修改奇数次的点，不用改，$ans-1$，修改偶数次，就翻转一次，$ans+1$。

反转的位置有四个，详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool c[1005][1005];
int ans, n, m, q;
void work(int x, int y){
	if(!(x >= 1 && x <= n && y >= 1 && y <= m)) return;
	if(c[x][y]) ans --;
	else ans ++;
	c[x][y] ^= 1;//修改0为1,1为0，这里使用位运算，加速且偷懒
}
int main(){
	cin >> n >> m >> q;
	while(q --){
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		work(x1 - 1, y1 - 1);//四个位置
		work(x1 - 1, y2);
		work(x2, y1 - 1);
		work(x2, y2);
		cout << ans << "\n";
	}
	return 0;
}

```

---

## 作者：Guoliyuan2023 (赞：1)

本蒟蒻的第五篇题解，烦请管理员包容亿下……
# 正题：P9298 [POI2020] Tablica binarna
## 题目
[P9298 原题传送门](https://www.luogu.com.cn/problem/P9298)

给一个矩阵，每一个元素的值只能为 $1$ 或者 $0$，初始化为 $0$。每次操作给定两个端点，把这两个端点围成矩阵之内的每个元素翻转。求在每次对矩阵执行修改操作后，需要执行至少多少次简单的修改操作，才能令矩阵内所有元素的值全部改为 $0$。
## 思路
经过思考之后，发现：

这四个值有偶数个翻转的时候答案不变，有奇数个翻转的位置每次操作只有 $4$ 个，所以：

暴力！！！
## 上代码（码风奇特，勿喷）
```
#include <bits/stdc++.h>    //万能头
using namespace std;    //命名空间
int n , m , ans , a[1001][1001];    //一堆变量和数组，数组自动清0
void run(int x , int y) //函数
{
    if(x < 1 || y < 1 || x > n || y > m)    //特判如果出界
    {
        return ;    //直接return
    }
    ans -= a[x][y];
    a[x][y] ^= 1;   //按位异或^应该都懂吧
    ans += a[x][y];
}
int main()  //主函数
{
    int t , x , y , p , q;  //变量不多解释
    cin >> n >> m >> t; //输入
    for(int i = 1; i <= t; i++) //循环t次操作
    {
    	cin >> x >> y >> p >> q;    //输入
    	run(x - 1 , y - 1); //四个全都run一遍
    	run(p , q);
    	run(x - 1 , q);
    	run(p , y - 1);
    	cout << ans << endl;    //输出
    }
    return 0;   //完美结束Perfect
}
```

## 温馨提示：

题目千万条，诚信第一条，代码不规范，棕名两行泪。

别抄了昂，就这题你也抄？看看思路行了昂。
## The end

---

## 作者：王逸辰 (赞：0)

# P9298 [POI2020] Tablica binarna 题解
## 思路
把给定二维数组所有元素反转成 $0$。

只有四种操作，直接暴力。

不用函数会很复杂，~~这一点我深有体会。~~

具体操作看代码。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int xxx,n,m,q,x,y,z,k,ans,a[1010][1010],s[1010][1010];
int main(){
    cin>>n>>m>>q;
    for(int i=1; i<=q; i++){
		cin>>x>>y>>z>>k;
	    if(x-1<1||y-1<1||x-1>n||y-1>m) xxx=0;
	    else ans-=s[x-1][y-1],s[x-1][y-1]^=1,ans+=s[x-1][y-1];
	    
	    
	    if(z<1||k<1||z>n||k>m) xxx=0;
	    else ans-=s[z][k],s[z][k]^=1,ans+=s[z][k];
	    
	    
	    if(x-1<1||k<1||x-1>n||k>m) xxx=0;
		else ans-=s[x-1][k],s[x-1][k]^=1,ans+=s[x-1][k];	
		
			
	    if(z<1||y-1<1||z>n||y-1>m) xxx=0;
		else  ans-=s[z][y-1],s[z][y-1]^=1,ans+=s[z][y-1];
		cout<<ans<<endl;
    } 
    return 0;
}
````

---

## 作者：forever516 (赞：0)

## 题意
给一个矩阵，每一个元素的值只能为 
1
或者
0，初始化为 
0。每次操作给定两个端点，把这两个端点围成矩阵之内的每个元素翻转。

求在每次对矩阵执行修改操作后，需要执行至少多少次简单的修改操作，才能令矩阵内所有元素的值全部改为 
0。

## 代码
题意部分已讲清做法，这里不做过多解释。

我们发现，这四个值有偶数个翻转的时候答案不变，而有奇数个翻转的位置每次操作只有 
4
个，暴力即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1001;
int n , m , ans , a[N][N],t , x , y , p , q;
void run(int x , int y){
    if(x < 1 || y < 1 || x > n || y > m)return;
    ans -= a[x][y];
    a[x][y] ^= 1;
    ans += a[x][y];
}
int main(){
    cin >> n >> m >> t;
    for(int i = 1; i <= t; i++){
    	cin >> x >> y >> p >> q;
    	run(x - 1 , y - 1);
    	run(p , q);
    	run(x - 1 , q);
    	run(p , y - 1);
    	cout << ans <<"\n";
    }
    return 0;
}
```

---

## 作者：florrygg (赞：0)

# P9298 [POI2020] Tablica binarna 题解

[题目传送门](https://www.luogu.com.cn/problem/P9298)

## 思路

题目就是问你让矩阵内所有元素的值全部变为 $0$ 需要执行多少次修改。可以发现奇数个翻转的位置每次操作只有 $4$ 个，所以直接模拟。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define endl '\n'

const int maxn=1001;
int n,m,q,sum,a[maxn][maxn],b[maxn][maxn];

void move(int x,int y)
{
	if(x<1||y<1||x>n||y>m)
	{
		return;
	}
	sum-=b[x][y];
	b[x][y]^=1;
	sum+=b[x][y];
}

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++)
	{
		int x,y,z,k;
		cin>>x>>y>>z>>k;
		move(x-1,y-1);
		move(x-1,k);
		move(z,y-1);
		move(z,k);
		cout<<sum<<endl;
	}
	return 0;
}
```

---

