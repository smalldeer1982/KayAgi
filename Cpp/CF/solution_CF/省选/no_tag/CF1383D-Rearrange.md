# Rearrange

## 题目描述

Koa the Koala has a matrix $ A $ of $ n $ rows and $ m $ columns. Elements of this matrix are distinct integers from $ 1 $ to $ n \cdot m $ (each number from $ 1 $ to $ n \cdot       m $ appears exactly once in the matrix).

For any matrix $ M $ of $ n $ rows and $ m $ columns let's define the following:

- The $ i $ -th row of $ M $ is defined as $ R_i(M) = [         M_{i1}, M_{i2}, \ldots, M_{im} ] $ for all $ i $ ( $ 1 \le i         \le n $ ).
- The $ j $ -th column of $ M $ is defined as $ C_j(M) = [         M_{1j}, M_{2j}, \ldots, M_{nj} ] $ for all $ j $ ( $ 1 \le j         \le m $ ).

Koa defines $ S(A) = (X, Y) $ as the spectrum of $ A $ , where $ X $ is the set of the maximum values in rows of $ A $ and $ Y $ is the set of the maximum values in columns of $ A $ .

More formally:

- $ X = \{ \max(R_1(A)), \max(R_2(A)), \ldots, \max(R_n(A))         \} $
- $ Y = \{ \max(C_1(A)), \max(C_2(A)), \ldots, \max(C_m(A)) \} $

Koa asks you to find some matrix $ A' $ of $ n $ rows and $ m $ columns, such that each number from $ 1 $ to $ n \cdot       m $ appears exactly once in the matrix, and the following conditions hold:

- $ S(A') = S(A) $
- $ R_i(A') $ is bitonic for all $ i $ ( $ 1 \le i \le         n $ )
- $ C_j(A') $ is bitonic for all $ j $ ( $ 1 \le j \le         m $ )

 An array $ t $ ( $ t_1, t_2, \ldots, t_k $ ) is called bitonic if it first increases and then decreases.  More formally: $ t $ is bitonic if there exists some position $ p $ ( $ 1 \le p \le k $ ) such that: $ t_1 < t_2 <       \ldots < t_p > t_{p+1} > \ldots > t_k $ .

Help Koa to find such matrix or to determine that it doesn't exist.

## 说明/提示

Let's analyze the first sample:

For matrix $ A $ we have:

- Rows: 
  - $ R_1(A) = [3, 5, 6]; \max(R_1(A)) =               6 $
  - $ R_2(A) = [1, 7, 9]; \max(R_2(A)) = 9 $
  - $ R_3(A) = [4, 8, 2]; \max(R_3(A)) = 8 $
- Columns: 
  - $ C_1(A) = [3, 1, 4]; \max(C_1(A)) =               4 $
  - $ C_2(A) = [5, 7, 8]; \max(C_2(A)) = 8 $
  - $ C_3(A) = [6, 9, 2]; \max(C_3(A)) = 9 $

- $ X = \{ \max(R_1(A)), \max(R_2(A)), \max(R_3(A)) \} = \{ 6,         9, 8 \} $
- $ Y = \{ \max(C_1(A)), \max(C_2(A)), \max(C_3(A)) \} = \{ 4,         8, 9 \} $
- So $ S(A) = (X, Y) = (\{ 6, 9, 8 \}, \{ 4, 8, 9 \}) $

For matrix $ A' $ we have:

- Rows: 
  - $ R_1(A') = [9, 5, 1]; \max(R_1(A'))               = 9 $
  - $ R_2(A') = [7, 8, 2]; \max(R_2(A')) = 8 $
  - $ R_3(A') = [3, 6, 4]; \max(R_3(A')) = 6 $
- Columns: 
  - $ C_1(A') = [9, 7, 3]; \max(C_1(A')) =               9 $
  - $ C_2(A') = [5, 8, 6]; \max(C_2(A')) = 8 $
  - $ C_3(A') = [1, 2, 4]; \max(C_3(A')) = 4 $

- Note that each of this arrays are bitonic.
- $ X = \{ \max(R_1(A')), \max(R_2(A')), \max(R_3(A')) \} = \{         9, 8, 6 \} $
- $ Y = \{ \max(C_1(A')), \max(C_2(A')), \max(C_3(A')) \} = \{         9, 8, 4 \} $
- So $ S(A') = (X, Y) = (\{ 9, 8, 6 \}, \{ 9, 8, 4 \}) $

## 样例 #1

### 输入

```
3 3
3 5 6
1 7 9
4 8 2```

### 输出

```
9 5 1
7 8 2
3 6 4```

## 样例 #2

### 输入

```
2 2
4 1
3 2```

### 输出

```
4 1
3 2```

## 样例 #3

### 输入

```
3 4
12 10 8 6
3 4 5 7
2 11 9 1```

### 输出

```
12 8 6 1
10 11 9 2
3 4 5 7```

# 题解

## 作者：Lynkcat (赞：14)

显然我们可以考虑将每个元素降序填入，且用一个队列来维护所有的位置。

对于 $i$ 这个数，如果它是一个行的最大值或者一个列的最大值那么我们需要新开一行或一列，然后将其上方的位置和左边的位置从下往上或者从右往左塞进队列。

首先左边的元素在队列中塞入的先后顺序是合法的，而又因为元素是降序填入的所以右边的一定比左边的要小，上下同理，所以一定合法。

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>

using namespace std;

inline int read(){
    int x = 0; char ch = getchar(); bool positive = 1;
    for (; !isdigit(ch); ch = getchar())	if (ch == '-')	positive = 0;
    for (; isdigit(ch); ch = getchar())	x = x * 10 + ch - '0';
    return positive ? x : -x;
}
inline void write(int a){
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
inline void writesp(int a){
    if(a>=10)write(a/10);
    putchar('0'+a%10);
    printf(" ");
}
inline void writeln(int a){
    if(a<0){
    	a=-a; putchar('-');
    }
    write(a); puts("");
}

int n,m,a[1005][1005],R[1005],C[1005],b1[1000005],b2[1000005],x1,y1,ans[1005][1005];
queue<pair<int,int> >q;

signed main()
{
	n=read(),m=read();
	for (int i=1;i<=n;i++)
	  for (int j=1;j<=m;j++)
	  {
	  	a[i][j]=read();
	  	R[i]=max(R[i],a[i][j]);
	  	C[j]=max(C[j],a[i][j]);
	  }
	for (int i=1;i<=n;i++) b1[R[i]]=1;
	for (int i=1;i<=m;i++) b2[C[i]]=1;
	for (int i=n*m;i>=1;i--)
	{
		if (b1[i]) x1++;
		if (b2[i]) y1++;
		if (b1[i]||b2[i])
			ans[x1][y1]=i; 
		else
		{
			ans[q.front().first][q.front().second]=i;
			q.pop();
		}
		if (b1[i])
		{
			for (int j=y1-1;j>=1;j--) q.push(make_pair(x1,j));
		}
		if (b2[i])
		{
			for (int j=x1-1;j>=1;j--) q.push(make_pair(j,y1));
		}
	}
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=m;j++) writesp(ans[i][j]);
		puts("");
	}
}

```

---

## 作者：Booksnow (赞：8)

# 构造

## 题目大意

给定 $n\times m$ 的整数矩阵 $A$ , $A$ 中的数是 $1$ 到 $nm$ 的排列。定义 $S(A)=(X,Y)$ ，其中 $X$ 是**行最大值**的集合， $Y$ 是**列最大值**的集合。找到一个 $n\times m$ 的整数矩阵 $A'$ ， $A'$ 中的数也是 $1$ 到 $nm$ 的排列，满足 $S(A')=S(A)$ ，且 $A'$ 的每行每列都满足**先增后减**。

## 分析

该题的做法能够从样例中得到一些启发。

![](https://cdn.luogu.com.cn/upload/image_hosting/dozsbk9z.png)

如图是第一组样例，用蓝圈圈起来的是行最大值，用红圈圈起来的是列最大值。我们观察被构造出的矩形，能够发现这些最大值最后都呈**阶梯型**排放而下，观察其他样例，同样能够发现这个规律，那么考虑为什么。

本题有一个显然的性质，就是**不能有多个行最大放在同一行**，**不能有多个列最大放在同一列**。

考虑如果我们**从左上角开始**填充矩阵，对于每一个行最大，要新开一行；对于每一个列最大，要新开一列；对于同时满足行最大和列最大的数，要新开一个行列。执行到代码里我们可以使用两个指针记录目前行和列被“**占领**”的情况。

如果再加入其它非最大最小值的数，我们依然考虑呈阶梯型排放(具体意思就是**紧靠着已经排放的数**排放且不能超过目前行和列的限制)，只要我们**从大到小**来填充这些数，就能够构造出最后的答案。

这么构造为什么对呢？由于我们是从大到小排放的，且是紧靠着已经排放的数排放，那么对于每一行每一列，其实行最大或者列最大就是该行该列的最高峰，而往他们周围的数按照排放的顺序是**越来越小**的，恰好满足题目要求的先增大后减小，所以按照此法构建出的新矩阵即为所求。

## CODE

```cpp
#include <bits/stdc++.h>
using namespace std;
const int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
const int N=3e2+10;
int n,m;
int line[N],row[N],matrix[N][N]; 
int Judge[N*N],ans[N][N];
int R_line[N],L_line[N];
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int main()
{
	n=read(),m=read();
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			matrix[i][j]=read();
			line[i]=max(line[i],matrix[i][j]); //维护行最大值 
			row[j]=max(row[j],matrix[i][j]); //维护列最大值 
		}
	}
	for(register int i=1;i<=n;i++) Judge[line[i]]=1; //存入行最大值
	for(register int i=1;i<=m;i++){ //存入列最大值 
		if(!Judge[row[i]]) Judge[row[i]]=2;
		else Judge[row[i]]=3;
	}
	//行的边界，列边界 
	int x=0,y=0;
	for(register int k=n*m;k>=1;k--){ //从大到小开始放置 
		if(Judge[k]==3) { ans[++x][++y]=k; L_line[x]=R_line[x]=y; } //新开行列放置 
		else if(Judge[k]==2) { ans[x][++y]=k; R_line[x]=y; } //新开一列放置  
		else if(Judge[k]==1) { ans[++x][y]=k; L_line[x]=R_line[x]=y; } //新开一行放置 
		else{ //非行列最大值，阶梯型放置 
			for(register int i=1;i<=x;i++){ //枚举行 
				bool flag=false;
				for(register int j=L_line[i]-1;j>=1;j--)
					if(!ans[i][j]&&ans[i-1][j]) {  ans[i][j]=k,flag=true; L_line[i]=j;  break; }
				if(flag) break;
				for(register int j=R_line[i]+1;j<=y;j++)
					if(!ans[i][j]&&ans[i+1][j]) {  ans[i][j]=k,flag=true; R_line[i]=j; break; }
				if(flag) break;
			} 
		}
	}
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++)
			printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：Illusory_dimes (赞：7)

#### 这是俺谷生中第一个灰题题解，还请各位大佬多多点赞$qwq$（虽然目测实际难度也就蓝到紫把
## $CF1383D$ $Rearrange$ $solution$

先把所谓的$S(A)$求出来，很简单

然后降序开始填：

先只考虑$S(A)$中有的数降序填，就从位置$(1,1)$开始填吧（实际上四个角都可以，只要方向搞的对

最大的数肯定在$(1,1)$上，不用说；

如果是行最大值，横坐标$+1$，因为不能与前一个冲突；

如果是列最大值，纵坐标$+1$，同理；

如果都是，横坐标和纵坐标都$+1$，也同理。

可以证明$S(A)$中最小的一个数一定在$(n,m)$上：

因为一共$n$行，$m$列，横坐标就从$1$加到$n$，纵坐标从$1$加到$m$（实际上是从$(0,0)$开始，但最大数肯定是行和列上的最大数，就直接填在$(1,1)$

再考虑不是$S(A)$中有的数

感性理解一下把（阿巴阿巴

只要在$S(A)$中最大数和当前已遇到的$S(A)$中最小数形成的小矩形中填就行，就是不影响已填的$S(A)$中的数。

就完了

放个代码，应该和其他人的代码差别不小把（竟然是$luogu$目前$top2$

```cpp
#include<bits/stdc++.h>
#define reg register
#define uns unsigned
using namespace std;
typedef long long ll;
const int N=250+10,M=7e4;
int n,m,a[N][N],sig[M],pos1=1,pos2=1;
int m1[M],m2[M],id1[M],id2[M],tot;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline void work()
{
	n=read(),m=read();
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			a[i][j]=read();
			if(m1[i]<a[i][j])
			{
				id1[i]=j;
				m1[i]=a[i][j];
			}
			if(m2[j]<a[i][j])
			{
				id2[j]=i;
				m2[j]=a[i][j];
			}
		}
	}
	for(int i=1;i<=n;++i)sig[m1[i]]+=1,m1[i]=id1[i]=0;
	for(int i=1;i<=m;++i)sig[m2[i]]+=2,m2[i]=id2[i]=0;
	id1[n*m]=pos1,id2[n*m]=pos2;
	for(int i=n*m-1;i>0;--i)
	{
		if(!sig[i])continue;
		if(sig[i]==3)
		{
			++pos1,++pos2;
			int x=pos1,y=pos2-1;
			while(1)
			{
				if(y<1)break;
				m1[++tot]=x,m2[tot]=y,--y;
			}
			x=pos1-1,y=pos2;
			while(1)
			{
				if(x<1)break;
				m1[++tot]=x,m2[tot]=y,--x;
			}
		}
		else if(sig[i]==1)
		{
			++pos1;
			int x=pos1,y=pos2-1;
			while(1)
			{
				if(y<1)break;
				m1[++tot]=x,m2[tot]=y,--y;
			}
		}
		else if(sig[i]==2)
		{
			++pos2;
			int x=pos1-1,y=pos2;
			while(1)
			{
				if(x<1)break;
				m1[++tot]=x,m2[tot]=y,--x;
			}
		}
		id1[i]=pos1,id2[i]=pos2;
	}
	tot=0;
	for(int i=n*m-1;i>0;--i)
	{
		if(!sig[i])
		{
			++tot;
			id1[i]=m1[tot];
			id2[i]=m2[tot];
		}
	}
	for(int i=n*m;i>0;--i)sig[(id1[i]-1)*m+id2[i]]=i;
	for(int i=1;i<=n*m;++i)
	{
		if(i%m)printf("%d ",sig[i]);
		else printf("%d\n",sig[i]);
	}
}
int main()
{
	work();
	return 0;
}
```
### 完结散花
只求能帮助到几个人罢。。

---

