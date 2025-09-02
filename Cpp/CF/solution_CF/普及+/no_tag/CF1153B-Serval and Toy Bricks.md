# Serval and Toy Bricks

## 题目描述

Luckily, Serval got onto the right bus, and he came to the kindergarten on time. After coming to kindergarten, he found the toy bricks very funny.

He has a special interest to create difficult problems for others to solve. This time, with many $ 1 \times 1 \times 1 $ toy bricks, he builds up a 3-dimensional object. We can describe this object with a $ n \times m $ matrix, such that in each cell $ (i,j) $ , there are $ h_{i,j} $ bricks standing on the top of each other.

However, Serval doesn't give you any $ h_{i,j} $ , and just give you the front view, left view, and the top view of this object, and he is now asking you to restore the object. Note that in the front view, there are $ m $ columns, and in the $ i $ -th of them, the height is the maximum of $ h_{1,i},h_{2,i},\dots,h_{n,i} $ . It is similar for the left view, where there are $ n $ columns. And in the top view, there is an $ n \times m $ matrix $ t_{i,j} $ , where $ t_{i,j} $ is $ 0 $ or $ 1 $ . If $ t_{i,j} $ equals $ 1 $ , that means $ h_{i,j}>0 $ , otherwise, $ h_{i,j}=0 $ .

However, Serval is very lonely because others are bored about his unsolvable problems before, and refused to solve this one, although this time he promises there will be at least one object satisfying all the views. As his best friend, can you have a try?

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153B/892fb946899e684e9f00485d6d986f950463d851.png)The graph above illustrates the object in the first example.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153B/a8bc552639ccace3006e1268f62706db15eeac44.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1153B/6a8bc1ca2ef321ddf9fb17e1f2ba6516c5d76f73.png)The first graph illustrates the object in the example output for the second example, and the second graph shows the three-view drawing of it.

## 样例 #1

### 输入

```
3 7 3
2 3 0 0 2 0 1
2 1 3
1 0 0 0 1 0 0
0 0 0 0 0 0 1
1 1 0 0 0 0 0
```

### 输出

```
1 0 0 0 2 0 0
0 0 0 0 0 0 1
2 3 0 0 0 0 0
```

## 样例 #2

### 输入

```
4 5 5
3 5 2 0 4
4 2 5 4
0 0 0 0 1
1 0 1 0 0
0 1 0 0 0
1 1 1 0 0
```

### 输出

```
0 0 0 0 4
1 0 2 0 0
0 5 0 0 0
3 4 1 0 0
```

# 题解

## 作者：ST_AS_IS_ZHY (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1153B)

## 题意

给定一个由立方体摆成的空间构型的三视图，要求你构造出一种可行的小立方体摆放方案。

## 思路

就是将左视图和主视图最高值汇聚在同一个位置，具体操作就是在俯视图存在小立方体的情况下找到左视图和主视图中的最小值为当前格的小立方体数量。

## 代码
```c++
// Problem: Serval and Toy Bricks
//    薮猫和玩具积木
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1153B
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
bool f[1001][1001];
int n, m, a[1001], b[1001], c[1001][1001];
int main()
{
    cin >> n >> m;
    int meiyongde; cin >> meiyongde;
    for(int i = 1 ; i <= m ; i ++) cin >> b[i];
    for(int i = 1 ; i <= n ; i ++) cin >> a[i];
    for(int i = 1 ; i <= n ; i ++)
    {
        for(int j = 1 ; j <= m ; j ++)
        {
            cin >> f[i][j];
            if(f[i][j]) c[i][j] = min(a[i] , b[j]);
	}
    }
    for(int i = 1 ; i <= n ; i ++)
    {
        for(int j = 1 ; j <= m ; j ++) cout << c[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}
```

---

## 作者：nominater (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1153B)
### 题意
这道题其实是一个挺简单的思维题，遵循三视图的规则就行：主俯长对正、主左高平齐、俯左宽相等。
### 思路
已知 $a$ 所对应的是前视图，$b$ 对应的是左视图。三视图中前视图和左视图只会看到最高的那一堆方块，所以只需要使得 $c$ 等于 $a$，$b$ 中较小的数，这样便能满足左视图和前视图的要求。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=1e2+10;

bool f[N][N];//判断格子知否有方块
int c[N][N];
int n,m,h;
int a[N],b[N];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>h;
    for(int i=1;i<=m;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    {
        cin>>b[i];
    }
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=m;j++)
    	{
    		cin>>f[i][j];
    	}
    }
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=m;j++)
        {
            if(f[i][j])//如果有
            c[i][j]=min(a[j],b[i]);//取小的一个
        }
    }
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=m;j++)
       	{
            cout<<c[i][j]<<" ";
        }
      	cout<<endl;
    }
    return 0;
}

```

---

## 作者：Moon_Lighter (赞：2)

### 题目大意：
由前视图，左视图的各行的高度，和俯视图是否存在，来推出积木的形状。

### 题目思路：
以俯视图为主体，每行每列都比较一下主视图和侧视图的最小值，即是结果。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int x,y,z,i,j,k,a[105],b[105],c[105][105];
	cin>>y>>z>>x;
	for(i=1;i<=z;i++)
	{
		scanf("%d",a+i);
	}
	for(i=1;i<=y;i++)
	{
		scanf("%d",b+i);
	}
	for(i=1;i<=y;i++)
	for(j=1;j<=z;j++)
	{
		scanf("%d",&c[i][j]);
		if(c[i][j])
			c[i][j]=min(a[j],b[i]);
	}
	for(i=1;i<=y;++i)
	{
		for(j=1;j<=z;++j)
		{
			printf("%d ",c[i][j]);
		}
	}
	return 0;
}
```

---

## 作者：hsfzLZH1 (赞：2)

## 题目大意

给定一个由若干个 $1\times 1\times 1$ 的正方体组成的包含在 $n\times m\times h$ 空间内的立体图形， $n,m,h$ 分别对应长、宽、高，保证在 **高** 这个维度上，正方体都是连续的一端为底的一段。

现在分别给出这个立体图形的主视图，左视图和俯视图，请你尝试还原这个立体图形。如果有多组解输出任意可能的一种。保证存在至少一组解。

主视图表示为 $a_1,a_2,...,a_m$ ，即在主视角看到的图形的每一列的高度。

左视图表示为 $b_1,b_2,...,b_n$ ，即在左视角看到的图形的每一列的高度。

俯视图表示为一个 $n\times m$ 的矩阵，如果该位是 $0$ 表示这一位置上没有正方体，为 $1$ 则表示该位置上有正方体。

$1\le n,m,h\le 100,0\le a_i,b_i\le h$

## 解题思路

观察到 $a_i$ 的值为还原图矩阵中第 $i$ 列中的高度最大值， $b_i$ 的值为还原图矩阵中第 $i$ 行中的高度最大值。

现在，我们有了若干个限制条件，需要给出矩阵的还原图。

此题有多种贪心方法，标准题解中给出的是若读入的矩阵中的值是 $1$ ，则输出对应的行和列上的值的最小值。

代码中给出的是另一种贪心方法，对于每一行每一列找到存在正方体的位置中，最大的 $a_i$ 或 $b_i$ 值，然后在这一位上填入对应的 $b_i$ 或 $a_i$ 值，没有被填过值的位在输出时改为 $1$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=110;
int n,m,hh,a[maxn],b[maxn],h[maxn][maxn],ans[maxn][maxn];
int main()
{
	scanf("%d%d%d",&n,&m,&hh);
	for(int i=1;i<=m;i++)scanf("%d",a+i);
	for(int i=1;i<=n;i++)scanf("%d",b+i);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",h[i]+j);
	for(int i=1;i<=m;i++)
	{
		int maxx=0;
		for(int j=1;j<=n;j++)if(h[j][i]&&b[j]>b[maxx])maxx=j;
		ans[maxx][i]=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		int maxx=0;
		for(int j=1;j<=m;j++)if(h[i][j]&&a[j]>a[maxx])maxx=j;
		ans[i][maxx]=b[i];
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)
	if(h[i][j]&&!ans[i][j])ans[i][j]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：fengxiaoyi (赞：0)

### 修改日志（按时间从晚到早从前往后排序）
2022/7/1：无序列表后加空行。

2022/7/1：把代码里的题解删除。

2022/7/1：删除结尾多余部分。
### 思路：
这道绿题实际上很简单，通过枚举 $t_{i,j}$ 来求高度。

定义 $p_{i,j}$ 表是第 $i$ 行第 $j$ 列的高度。

- 若 $t_{i,j}=1$，则：
$$p_{i,j}=\mathrm{min}(a_j,b_i)$$
- 若 $t_{i,j}=1$，说明这里没方块，则：
$$p_{i,j}=0$$

### 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,h,a[110],b[110],p[110][110];
bool t[110][110];
int main(){
	cin>>n>>m>>h;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>t[i][j];
			if(t[i][j]){
				p[i][j]=min(a[j],b[i]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cout<<p[i][j]<<' ';
		}
		cout<<endl;
	}
	return 0;
}
~~~

---

## 作者：xiaomimxl (赞：0)

# 题目大意：

给出一个立体图形，高度最高为 $h$，第一行给出 $n,m,h$，第二行给出正视图每一列的高度(共 $m$ 列)，第三行给出左视图每一列的高度(共 $n$ 列)，然后有$n \times m$个数，

若其值为 0，则意味着该处高度为 0；若其值为 1，则意味着该处高度不为 0。求满足题意的立体图形的每一处的高度。(有多个解输出任意一个即可)

# 思路分析:

设序列 $A$ 存储正视图 $m$ 列的高度，序列 $B$ 存储左视图 $n$ 列的高度，二维数组 $C$ 存储 $n \times m$ 的 01 矩阵，若 $C_{i,j}=0$，则该处答案为 0，(因为高度为 0 )否则输出 $min(A[i],B[j])$。

# AC code：

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std ;
 
int a[105];
int b[105];
int n,m,h;
 
int main()
{
    scanf("%d %d %d",&n,&m,&h);
    for(int i=0;i<m;i++)
        scanf("%d",&b[i]);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    int t;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&t);
            if(j)
                printf(" ");
            if(t==0)
                printf("0");
            else
                printf("%d",min(a[i],b[j]));
        }
        printf("\n");
    }
    return 0;
}
```


---

## 作者：user470883 (赞：0)

## 思路：
贪心构造。

学过小学数学（好像是四年级）的都应该知道如果我们想确定这个立体图形的样子，我们必须从俯视图看起，那么 $1$ 就是代表着又一个正方体，$0$ 则就没有。

我们经过观察样例，轻松可以发现一个贪心的策略，即如果有正方体（$1$）在 $a[i][j]$ 上面填上 $i$ 行最大值和 $j$ 列最大值两者的最小值即可。

**注意事项**：题目要求输出任一合法方案都可以，不要看错了。

## AC CODE:
```
#include<bits/stdc++.h>
#define yangzd long long
#define INF 2000000000
#define jerrlee int
#define CZY signed
#define piggy123 return 0;
using namespace std;

int a[114], b[114], c[114][514], d[114][514];//数组还是开外面好

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,m,h;
	cin >> n >> m >> h;//输入
	for(int i = 0 ; i < m ; i++)
	{
		cin >> a[i];
	}
	for(int i = 0 ; i < n ; i++)
	{
		cin >> b[i];
	}
	for(int i = 0 ; i < n ; i++)
	{
		for(int j = 0 ; j < m ; j++)
		{
			cin >> c[i][j];
		}
	}
	for(int i = 0 ; i < n ; i++)
	{
		for(int j = 0 ; j < m ; j++)
		{
			if(c[i][j])
			{
				d[i][j]=min(a[j],b[i]);
			}//按照贪心策略进行比较
		}
	}
	
	for(int i = 0 ; i < n ; i++)
	{
		for(int j = 0 ; j < m ; j++)
		{
			cout <<  d[i][j] << " ";
		}
		cout << endl;
	}//输出，别忘了空格和换行！
	
	return 0;
}

/*Things to check before submit:
1. did you forget long long ?
2. did you still CE?
3. = or == , n or m ,++ or -- , i or j , > or >= , < or <=
4. If contains "not", why not Reverse thinking or few affect?
5. is there anything extra to output?
6. keep it simple
7. can part of the code can with c++function replace?
8. smile while submit the code*/
```

有问题私我！

---

## 作者：智子·起源 (赞：0)

# 有史以来AC的第一道绿题！
# (2019.11.5祭)

### 是不是太简单了……
不BB了，开始讲吧！

### 在得到每一个方向视角的时候都把答案图形更改一遍即可！
其实思路是很简单的。
看不懂的话可以再参考一下下面的程序^_^

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,h,nn[100+5],mm[100+5],hh[100+5][100+5],a[100+5][100+5];
int main()
{
  scanf("%d%d%d",&n,&m,&h);
  for(int i=1;i<=m;i++)scanf("%d",&mm[i]);
  for(int i=1;i<=m;i++)
    for(int j=1;j<=n;j++)
      a[j][i]=mm[i];
//读入前面的视角，更新答案图形。
  for(int i=1;i<=n;i++)scanf("%d",&nn[i]);
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
      if(a[i][j]>nn[i])a[i][j]=nn[i];
//读入左边的视角，再次更新答案图形。
  for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
      scanf("%d",&hh[i][j]);
//读入上方视角。
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=m;j++)
      if(hh[i][j]==0)printf("0 ");
        else printf("%d ",a[i][j]);
    printf("\n");
  }
//在输出时判断一下从上方视角可不可以观测到。（可以就输出当前高度，否则就输出0）
  return 0;
}
```

由于这是妾身发的第一篇绿题题解，大家的每一个赞，无疑都是对妾身最大的鼓励！^_^

---

## 作者：StudyingFather (赞：0)

并不算难的构造题。

一种简单粗暴的构造方法就是，对于有方块的格子，高度直接取为主视图对应列的高度和左视图对应行的高度的最小值。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int a[105],b[105],h[105][105],res[105][105];
int main()
{
 int n,m,w;
 scanf("%d%d%d",&n,&m,&w);
 for(int i=1;i<=m;i++)
  scanf("%d",&a[i]);
 for(int i=1;i<=n;i++)
  scanf("%d",&b[i]);
 for(int i=1;i<=n;i++)
  for(int j=1;j<=m;j++)
   scanf("%d",&h[i][j]);
 for(int i=1;i<=n;i++)
  for(int j=1;j<=m;j++)
   if(h[i][j]==0)res[i][j]=0;
   else res[i][j]=min(a[j],b[i]);
 for(int i=1;i<=n;i++)
 {
  for(int j=1;j<=m;j++)
   printf("%d ",res[i][j]);
  puts("");
 }
 return 0;
}
```


---

## 作者：hpbl (赞：0)

一道很妙的题目。

想不到它竟然是我们学校那两个毒瘤学长出的（不要来找我出气

首先将问题转化成已知$a_i = max_{1 \le j \le n}h_{j,i}$，$b_i=max_{1 \le j \le m}h_{i,j}$，$t_{i,j}=[h_{i,j}>0]$，求出一个可能的$h$数组

由此我们可以知道，若$t_{i,j}=0$，则$h_{i,j}=0$，否则$h_{i,j} \le min(a_j,b_i)$

综合起来就是$h_{i,j} \le t_{i,j} \times min(a_j,b_i)$

记$m_{i,j}=t_{i,j} \times min(a_j,b_i)$，我们的方案中的$a_i$和$b_i$分别对应$a_i^`$和$b_i^`$

则$h_{i,j}$的最大值为$m_{i,j}$，$a_i = a_i^`$，$b_i = b_i^`$

这时候我们可以想一想

若$h_{i,j} < m_{i,j}$，那么它并不能把$a_j^`$和$b_i^`$变大

若$h_{i,j} = m_{i,j}$，那么它可能可以把它们变大，而又让它们不超过$a_j$和$b_i$

所以这样看来，让$h_{i,j}=m_{i,j}$是最好的。

可以看出这个时候是对的。

Code：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,h,x[101],y[101];
int main()
{
	scanf("%d %d %d",&n,&m,&h);
	for(int i=1;i<=m;i++) scanf("%d",&x[i]);
	for(int i=1;i<=n;i++) scanf("%d",&y[i]);
	for(int i=1,t;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&t);
			printf("%d%c",t*min(y[i],x[j]),j==m?'\n':' ');
		}
	}
}
```


---

