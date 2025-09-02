# 题目信息

# Dima and a Bad XOR

## 题目描述

来自克雷姆兰德的学生迪马有一个大小为 $n \times m$ 的矩阵，其中只包含非负整数。

他希望从矩阵的每一行中选出一个整数，使得所选整数的按位异或严格大于零。

也就是说，他想选择一个整数序列 $c_1,c_2,\dots,c_n$ $(1\leq c_j \leq m)$ 使得不等式 $a_{1,c_1}\oplus a_{2,c_2}\dots \oplus a_{n,c_n} > 0$成立，其中 $a_{i,j}$ 是第 $i$ 行和第 $j$ 列的矩阵元素。

$x\oplus y$ 表示 $x$ 和 $y$ [按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)，这里是他的定义。

## 说明/提示

在第一个例子中，矩阵中的所有数字都是0，因此不可能在表的每一行中选择一个数字，以使它们的按位异或严格大于零。

在第二个例子中，所选数字是 $7$（第一行中的第一个数字）和$10$（第二行中的第三个数字），$7 \oplus 10 = 13$ , $13$ 大于 $0$ ，因此找到了答案。

## 样例 #1

### 输入

```
3 2
0 0
0 0
0 0
```

### 输出

```
NIE
```

## 样例 #2

### 输入

```
2 3
7 7 7
7 7 10
```

### 输出

```
TAK
1 3 
```

# AI分析结果

### 题目内容
# Dima and a Bad XOR

## 题目描述

来自克雷姆兰德的学生迪马有一个大小为 $n \times m$ 的矩阵，其中只包含非负整数。

他希望从矩阵的每一行中选出一个整数，使得所选整数的按位异或严格大于零。

也就是说，他想选择一个整数序列 $c_1,c_2,\dots,c_n$ $(1\leq c_j \leq m)$ 使得不等式 $a_{1,c_1}\oplus a_{2,c_2}\dots \oplus a_{n,c_n} > 0$成立，其中 $a_{i,j}$ 是第 $i$ 行和第 $j$ 列的矩阵元素。

$x\oplus y$ 表示 $x$ 和 $y$ [按位异或运算](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)，这里是他的定义。

## 说明/提示

在第一个例子中，矩阵中的所有数字都是0，因此不可能在表的每一行中选择一个数字，以使它们的按位异或严格大于零。

在第二个例子中，所选数字是 $7$（第一行中的第一个数字）和$10$（第二行中的第三个数字），$7 \oplus 10 = 13$ , $13$ 大于 $0$ ，因此找到了答案。

## 样例 #1

### 输入

```
3 2
0 0
0 0
0 0
```

### 输出

```
NIE
```

## 样例 #2

### 输入

```
2 3
7 7 7
7 7 10
```

### 输出

```
TAK
1 3 
```

### 算法分类
位运算、构造

### 题解分析与结论

本题的核心是通过构造每一行的选择，使得最终的异或和大于零。题解中主要有以下几种思路：

1. **随机化方法**：通过多次随机选择，期望在足够多的尝试中找到满足条件的解。这种方法虽然简单，但效率较低，且无法保证一定能找到解。
2. **构造法**：通过分析异或性质，构造一个满足条件的解。具体来说，先尝试将所有行的第一个元素异或起来，如果结果不为零，则直接输出；否则，尝试替换某一行的一个元素，使得异或和不为零。
3. **位运算与分类讨论**：将每一行的元素按二进制位进行分类，通过统计每一行的某些位是否为1，来判断是否可以构造出满足条件的解。

### 评分较高的题解

#### 题解1：作者：fuxuantong123 (赞：5)
- **星级**：4星
- **关键亮点**：通过构造法，先尝试将所有行的第一个元素异或起来，如果结果不为零，则直接输出；否则，尝试替换某一行的一个元素，使得异或和不为零。这种方法简单且高效。
- **代码实现**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[510][510];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	int x;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	x=a[1][1];
	for(int i=2;i<=n;i++){
		x^=a[i][1];
	}
	if(x>0){
		printf("TAK\n");
		for(int i=1;i<=n;i++){
			printf("1 ");
		}
		return 0;
	}
	for(int i=1;i<=n;i++){
		for(int j=2;j<=m;j++){
			if(a[i][j]!=a[i][1]){
				printf("TAK\n");
				for(int x=1;x<i;x++){
					printf("1 ");
				}
				printf("%d ",j);
				for(int y=i+1;y<=n;y++){
					printf("1 ");
				}
				return 0;
			}
		}
	}
	printf("NIE");
return 0;
}
```

#### 题解2：作者：litble (赞：2)
- **星级**：4星
- **关键亮点**：将每一行分为A类（只有一种数字）和B类（至少有两种不同数字），通过分类讨论，构造出满足条件的解。这种方法思路清晰，且复杂度较低。
- **代码实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
int n,m,now,ans;
int v1[505],id2[505],v2[505],kans[505];

int main()
{
	scanf("%d%d",&n,&m);
	for(RI i=1;i<=n;++i) {
		scanf("%d",&v1[i]),v2[i]=-1;
		for(RI j=2;j<=m;++j) {
			int x;scanf("%d",&x);
			if(x!=v1[i]) v2[i]=x,id2[i]=j;
		}
		if(v2[i]==-1) now^=v1[i];
	}
	for(RI i=1;i<=n;++i) {
		if(v2[i]==-1) kans[i]=1;
		else {
			if((now^v1[i])==0) now^=v2[i],kans[i]=id2[i];
			else now^=v1[i],kans[i]=1;
		}
	}
	if(now==0) puts("NIE");
	else {
		puts("TAK");
		for(RI i=1;i<=n;++i) printf("%d ",kans[i]);
		puts("");
	}
	return 0;
}
```

#### 题解3：作者：_Fontainebleau_ (赞：3)
- **星级**：4星
- **关键亮点**：通过位运算和分类讨论，先计算所有行的第一个元素的异或和，如果不为零则直接输出，否则尝试替换某一行的一个元素，使得异或和不为零。这种方法思路清晰，且复杂度较低。
- **代码实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int tc,n,m;
int p[502],a[502][502];
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	int val=0;
	n=read(),m=read();
	for(int i=1;i<=n;i++)	
		for(int j=1;j<=m;j++)
			a[i][j]=read();
	for(int i=1;i<=n;i++)
		val^=a[i][1],p[i]=1;
	bool flag=true;
	if(!val)
	{
		flag=false; 
		for(int i=n;i>=1;i--)
		{
			for(int j=2;j<=m;j++)
				if(a[i][j]!=a[i][1])
				{
					flag=true;
					p[i]=j;
					break;
				}
			if(flag)	break;
		}	
	}
	if(flag)
	{
		puts("TAK");
		for(int i=1;i<=n;i++)
			printf("%d ",p[i]);
		puts(""); 
	}
	else	puts("NIE");
	return 0;
}
```

### 最优关键思路或技巧
1. **构造法**：通过先计算所有行的第一个元素的异或和，如果不为零则直接输出，否则尝试替换某一行的一个元素，使得异或和不为零。这种方法简单且高效。
2. **位运算与分类讨论**：将每一行的元素按二进制位进行分类，通过统计每一行的某些位是否为1，来判断是否可以构造出满足条件的解。

### 可拓展之处
本题的解法可以拓展到其他需要构造满足特定条件的序列的问题，尤其是涉及位运算的题目。类似的题目可以通过分类讨论和构造法来解决。

### 推荐题目
1. [P1463 [POI2001] 异或序列](https://www.luogu.com.cn/problem/P1463)
2. [P1464 [POI2001] 异或序列2](https://www.luogu.com.cn/problem/P1464)
3. [P1465 [POI2001] 异或序列3](https://www.luogu.com.cn/problem/P1465)

---
处理用时：61.00秒