# A Mist of Florescence

## 题目描述

**题目大意：**

让你构造一个$n*m$矩阵，这个矩阵由4种字符填充构成，给定4个整数，即矩阵中每种字符构成的四联通块个数，$n,m$需要你自己定，但是不能超过50

## 样例 #1

### 输入

```
5 3 2 1
```

### 输出

```
4 7
DDDDDDD
DABACAD
DBABACD
DDDDDDD```

## 样例 #2

### 输入

```
50 50 1 1
```

### 输出

```
4 50
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
ABABABABABABABABABABABABABABABABABABABABABABABABAB
BABABABABABABABABABABABABABABABABABABABABABABABABA
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD```

## 样例 #3

### 输入

```
1 6 4 5
```

### 输出

```
7 7
DDDDDDD
DDDBDBD
DDCDCDD
DBDADBD
DDCDCDD
DBDBDDD
DDDDDDD```

# 题解

## 作者：yuzhechuan (赞：5)


**这是1 1 1 1的输出**

![](https://cdn.luogu.com.cn/upload/pic/21028.png)

**这是100 100 100 100的输出**

![](https://cdn.luogu.com.cn/upload/pic/21027.png)


------------


既然题目规定长宽最大50\*50，那么我就输到了50\*50

且每种花各占25\*25，这样的连通块的初值就都为1了

接下来只需要在对角线的大连通块里占据x-1块独立的小连通块就可以了

注意留出一行来保证大连通块的连通性

------------

```cpp
#include <bits/stdc++.h>
using namespace std;
int a,b,c,d,A[55][55];
int main()
{
	cin>>d>>c>>b>>a;
	a--;b--;c--;d--;//初始化
	for(int i=1;i<=25;i++)
		for(int j=1;j<=25;j++)
			A[i][j]=1;//A
	for(int i=1;i<=25;i++)
		for(int j=26;j<=50;j++)
			A[i][j]=2;//B
	for(int i=26;i<=50;i++)
		for(int j=1;j<=25;j++)
			A[i][j]=3;//C
	for(int i=26;i<=50;i++)
		for(int j=26;j<=50;j++)
			A[i][j]=4;//D
	int x=1,y=1;
	for(int i=1;i<=a;i++)
	{
		A[x][y]=4;//A里存D
		y+=2;//需要两列两列的替换
		if(y==26)y=1,x+=2;//若超出，则列还原（奇偶性要相反），行空一行
		if(y==27)y=2,x+=2;//下同...
	}
	x=1,y=26;
	for(int i=1;i<=b;i++)
	{
		A[x][y]=3;//B里存C
		y+=2;
		if(y==51)y=26,x+=2;
		if(y==52)y=27,x+=2;
	}
	x=26,y=1;
	for(int i=1;i<=c;i++)
	{
		A[x][y]=2;//C里存B
		y+=2;
		if(y==26)y=1,x+=2;
		if(y==27)y=2,x+=2;
	}
	x=26,y=26;
	for(int i=1;i<=d;i++)
	{
		A[x][y]=1;//D里存A
		y+=2;
		if(y==51)y=26,x+=2;
		if(y==52)y=27,x+=2;
	}
	cout<<50<<" "<<50<<endl;//直接输出...
	for(int i=1;i<=50;i++)//将数字转化为A B C D
	{
		for(int j=1;j<=50;j++)
		{
			char ans='A'+A[i][j]-1;
			cout<<ans;
		}
		puts("");
	}		
}
```


---

## 作者：灯芯糕 (赞：3)

## solution：

### 作为一道构造题，这题确实十分符合构造的一些通性----（我们需要找到一些规律，然后无脑循环）。个人认为这题规律很巧妙也很典型：

### 1. n,m不能超过50
### 2. **1<=**a,b,c,d<=100（大于1！）

### 根据题目这两个限制条件，我们不难猜出一个构造方法：

### 例如：一个B联通块+三个C联通块：

![](https://www.cnblogs.com/images/cnblogs_com/812-xiao-wen/1389970/o_1-3.png)

### 三个不够，来一百个：

![](https://www.cnblogs.com/images/cnblogs_com/812-xiao-wen/1389970/o_1-4.png)

### 注意了吗，我们现在才用11行，足够我们构造剩下三种字母了（以一种字母为背景，所以题目限制中a，b，c，d大于一！！！）

### 话不多说，上代码（应该最短了吧）

## code：
```cpp
#include<iostream>
using namespace std;
int main(){
	int a[4]; puts("44 49"); //这个千万不能忘啊！
	cin>>a[4]>>a[1]>>a[2]>>a[3];
	for(int i=1;i<=4;++i){
		char su='A'+i-1, pi=i==4?'A':su+1;
		for(int j=1;j<=5;++j,cout<<su<<endl){
			for(int o=1;o<=49;++o)cout<<su; puts("");
			for(int o=1;o<=24;++o)cout<<su<<(--a[i]>0?pi:su);
		}   for(int o=1;o<=49;++o)cout<<su; puts("");
	}return 0;
}

```
#### 细节之处可以细细品味

---

## 作者：dengyaotriangle (赞：3)

### 这道题看上去很难，但有很简单的做法(pj-级别)
因为要涂的每一种颜色必须大于1，且矩阵的大小给的非常富余，所以可以列一个表格

```
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
BABABABABABABABABABABABABABABABABABABABABABABABAAA
ABABABABABABABABABABABABABABABABABABABABABABABABAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
BABABABABABABABABABABABABABABABABABABABABABABABAAA
ABABABABABABABABABABABABABABABABABABABABABABABABAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
BABABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
CBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBBB
BCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
CBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBBB
BCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBCBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
CBCBCBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
DCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCCC
CDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
DCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCCC
CDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
DCDCDCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
ADADADADADADADADADADADADADADADADADADADADADADADADDD
DADADADADADADADADADADADADADADADADADADADADADADADADD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
ADADADADADADADADADADADADADADADADADADADADADADADADDD
DADADADADADADADADADADADADADADADADADADADADADADADADD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
ADADADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
```
这个表格的由一大块联通的ABCD组成，还有99个互相不联通的

只需要实现根据需求的不同来填上相应数量的不联通的ABCD即可

例如，在A=10,B=40,C=1,D=99时的结果会是这样的

```
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
BABABABABABABABABABABABABABABABABABABABABABABABAAA
ABABABABABABABABABABABABABABABAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
DCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCCC
CDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
DCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCCC
CDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCDCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
DCDCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
ADADADADADADADADADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
```
可以看到，只需要在相应位置填上适当的ABCD即可AC
### 代码
```
#include<bits/stdc++.h>

using namespace std;

const int maxn=55;
const int maxc=5;
const int c[6]={1,2,4,5,7,8};

char oa[maxn][maxn];
int v[maxc];

int main(){
	cin>>v[0]>>v[1]>>v[2]>>v[3];
	v[0]--;v[1]--;v[2]--;v[3]--;
	for(int i=0;i<4;i++){
		for(int j=0;j<10;j++){
			for(int k=0;k<50;k++){
				oa[i*10+j][k]='A'+i;
			}
		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<6;j++){
			for(int k=0;k<47;k+=2){
				if(v[(i+1)%4]!=0){
					oa[i*10+c[j]][k+j%2]='A'+(i+1)%4;
					v[(i+1)%4]--;
				}
			}
		}
	}
	cout<<40<<' '<<50;
	for(int i=0;i<40;i++){
		cout<<endl;
		for(int j=0;j<50;j++) cout<<oa[i][j];
	}
}
```

---

## 作者：Judgelight (赞：2)

令 $s_{i,j}$ 表示矩阵第 $i$ 行 第 $j$ 列的元素。

不妨先将其设置为四块相同大小的块：$s_{1\sim 10,1\sim 50}=A,s_{11\sim 20,1\sim 50}=B,s_{21\sim 30,1\sim 50}=C,s_{31\sim 40,1\sim 50}=D$。

先讨论 $A$ 的连通块的情况：假设为 $a$ 个，相当于我们还需要 $a-1$ 个连通块，可以在 $D$ 的矩阵里构造。

如图，设红色表示 $A$，绿色表示 $D$：

![](https://cdn.luogu.com.cn/upload/image_hosting/z237oy0r.png)

发现每一个红色的块都是一个关于 $A$ 的连通块。

故按照这样进行每一种颜色的连通块个数的添加。

```cpp
#include<bits/stdc++.h>
#define N 59
using namespace std;
int a,b,c,d;
char s[N][N];
void solvea(){
	for(int i=1;i<=min(25,a);i++)s[31][i*2]='A';
	if(a<=25)return ;
	else a-=25;
	for(int i=1;i<=min(25,a);i++)s[33][i*2]='A';
	if(a<=25)return ;
	else a-=25;
	for(int i=1;i<=min(25,a);i++)s[35][i*2]='A';
	if(a<=25)return ;
	else a-=25;
	for(int i=1;i<=min(25,a);i++)s[37][i*2]='A';
	if(a<=25)return ;
	else a-=25;
}
void solveb(){
	for(int i=1;i<=min(25,b);i++)s[1][i*2]='B';
	if(b<=25)return ;
	else b-=25;
	for(int i=1;i<=min(25,b);i++)s[3][i*2]='B';
	if(b<=25)return ;
	else b-=25;
	for(int i=1;i<=min(25,b);i++)s[5][i*2]='B';
	if(b<=25)return ;
	else b-=25;
	for(int i=1;i<=min(25,b);i++)s[7][i*2]='B';
	if(b<=25)return ;
	else b-=25;
}
void solvec(){
	for(int i=1;i<=min(25,c);i++)s[11][i*2]='C';
	if(c<=25)return ;
	else c-=25;
	for(int i=1;i<=min(25,c);i++)s[13][i*2]='C';
	if(c<=25)return ;
	else c-=25;
	for(int i=1;i<=min(25,c);i++)s[15][i*2]='C';
	if(c<=25)return ;
	else c-=25;
	for(int i=1;i<=min(25,c);i++)s[17][i*2]='C';
	if(c<=25)return ;
	else c-=25;
}
void solved(){
	for(int i=1;i<=min(25,d);i++)s[21][i*2]='D';
	if(d<=25)return ;
	else d-=25;
	for(int i=1;i<=min(25,d);i++)s[23][i*2]='D';
	if(d<=25)return ;
	else d-=25;
	for(int i=1;i<=min(25,d);i++)s[25][i*2]='D';
	if(d<=25)return ;
	else d-=25;
	for(int i=1;i<=min(25,d);i++)s[27][i*2]='D';
	if(d<=25)return ;
	else d-=25;
}
signed main(){
	scanf("%d%d%d%d",&a,&b,&c,&d),a--,b--,c--,d--;
	for(int i=1;i<=10;i++)for(int j=1;j<=50;j++)s[i][j]='A';
	for(int i=11;i<=20;i++)for(int j=1;j<=50;j++)s[i][j]='B';
	for(int i=21;i<=30;i++)for(int j=1;j<=50;j++)s[i][j]='C';
	for(int i=31;i<=40;i++)for(int j=1;j<=50;j++)s[i][j]='D';
	solvea();
	solveb();
	solvec();
	solved();
	printf("40 50\n");
	for(int i=1;i<=40;i++){
		for(int j=1;j<=50;j++)printf("%c",s[i][j]);
		printf("\n");
	}
	return 0;
}
```

---

## 作者：elijahqi (赞：2)

 http://www.elijahqi.win/archives/3662
 https://blog.csdn.net/elijahqi/article/details/80660532
 
考虑构造四个 区域 每个区域长度为50 宽度为9 然后类似三明治一样 考虑往中间i填写 往A里面 填写 B 往B里面填写A 然后这样恰好可以满足要求 即使4个100 用最多 36行也可以满足条件

形如

AAA

ABA

AAA

ABA

AAA
```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a,b,c,d;
char mp[55][55];
int main(){
	scanf("%d%d%d%d",&a,&b,&c,&d);
	puts("36 50");
	--a;--b;--c;--d;
	for (int i=1;i<=9;++i) 
		for (int j=1;j<=50;++j) mp[i][j]='a';
	for (int i=10;i<=18;++i)
		for (int j=1;j<=50;++j) mp[i][j]='b';
	for (int i=19;i<=27;++i)
		for (int j=1;j<=50;++j) mp[i][j]='c';
	for (int i=28;i<=36;++i)
		for (int j=1;j<=50;++j) mp[i][j]='d';
	int cnt=0;bool flag=0;
	if (b){
		for (int i=2;i<=8;i+=2){
			for (int j=2;j<=50;j+=2){
				++cnt;mp[i][j]='b';if (cnt==b) {flag=1;break;}	
			}if(flag) break;
		}
	}cnt=0;flag=0;
	if (a){
		for (int i=11;i<=17;i+=2){
			for (int j=2;j<=50;j+=2){
				++cnt;mp[i][j]='a';if (cnt==a) {flag=1;break;}	
			}if (flag) break;
		}
	}cnt=0;flag=0;
	if (d){
		for (int i=20;i<=26;i+=2){
			for (int j=2;j<=50;j+=2){
				++cnt;mp[i][j]='d';if (cnt==d) {flag=1;break;}	
			}if (flag) break;
		}
	}cnt=0;flag=0;
	if (c){
		for (int i=29;i<=35;i+=2){
			for (int j=2;j<=50;j+=2){
				++cnt;mp[i][j]='c';if (cnt==c) {flag=1;break;}	
			}if (flag) break;
		}
	}
	for (int i=1;i<=36;++i){
		for (int j=1;j<=50;++j) putchar(mp[i][j]);puts("");
	}
	return 0;
}
```

---

## 作者：Wander_E (赞：1)

# A Mist of Florescence 题解
### 思路
没有算法，纯构造。一种构造方式如下：

对于每个字母分配 $10$ 行 $50$ 列的矩阵，先用该字母将整个矩阵填满，再让其他字母隔行插空放即可。

例：如果只分配 $3$ 行 $4$ 列的矩阵效果如下：
```
A A A A        B A B A
A A A A  --->  A A A A
A A A A        B A B A

```
### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a, b, c, d;
char ans[500][500]; 

signed main()
{
	cin >> a >> b >> c >> d;
	cout << "40 50\n";
	for(int i = 1; i <= 10; i++)
		for(int j = 1; j <= 50; j++)
			ans[i][j] = 'A';
	for(int i = 11; i <= 20; i++)
		for(int j = 1; j <= 50; j++)
			ans[i][j] = 'B';
	for(int i = 21; i <= 30; i++)
		for(int j = 1; j <= 50; j++)
			ans[i][j] = 'C';
	for(int i = 31; i <= 40; i++)
		for(int j = 1; j <= 50; j++)
			ans[i][j] = 'D';
	a--, b--, c--, d--;
	int i = 1, j = 1;
	while(c--)
	{
		if(j > 50) i += 2, j = 1;
		ans[i][j] = 'C';
		j += 2;
	}
	i = 11, j = 1;
	while(d--)
	{
		if(j > 50) i += 2, j = 1;
		ans[i][j] = 'D';
		j += 2;
	}
	i = 21, j = 1;
	while(a--)
	{
		if(j > 50) i += 2, j = 1;
		ans[i][j] = 'A';
		j += 2;
	}
	i = 31, j = 1;
	while(b--)
	{
		if(j > 50) i += 2, j = 1;
		ans[i][j] = 'B';
		j += 2;
	}
	for(int i = 1; i <= 40; i++)
	{
		for(int j = 1; j <= 50; j++)
			cout << ans[i][j];
		cout << endl;
	}
	return 0;
}

```

---

## 作者：Vitamin_B (赞：0)

# 思路
把 $50\times50$ 的矩阵分割成四个 $25\times25$ 的小矩阵，分别存四个字母。然后因为方格充足，所以可以在不破坏原先 `A` 矩阵的情况下在其中存 $d-1$ 个 `D`，其余同理。因为资源充足，所以其中一种解决方案就是间隔着放字母。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int a, b, c, d, x, y;
char ans[55][55];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> a >> b >> c >> d;
	cout << "50 50";
	for (int i = 0; i < 25; ++ i)
		for (int j = 0; j < 25; ++ j)
			ans[i][j] = 'A';
	for (int i = 0; i < 25; ++ i)
		for (int j = 25; j < 50; ++ j)
			ans[i][j] = 'B';
	for (int i = 25; i < 50; ++ i)
		for (int j = 0; j < 25; ++ j)
			ans[i][j] = 'C';
	for (int i = 25; i < 50; ++ i)
		for (int j = 25; j < 50; ++ j)
			ans[i][j] = 'D';
	x = y = 1;
	while (-- d) {
		ans[x][y] = 'D';
		if ((y += 2) > 24)
			x += 2, y = 1;
	}
	x = 1, y = 26;
	while (-- c) {
		ans[x][y] = 'C';
		if ((y += 2) > 49)
			x += 2, y = 26;
	}
	x = 26, y = 1;
	while (-- b) {
		ans[x][y] = 'B';
		if ((y += 2) > 24)
			x += 2, y = 1;
	}
	x = y = 26;
	while (-- a) {
		ans[x][y] = 'A';
		if ((y += 2) > 49)
			x += 2, y = 26;
	}
	for (int i = 0; i < 50; ++ i)
		cout << '\n' << ans[i];
	return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路：
这道题看起来很难，但是实际上还比较简单。

考虑怎么构成连通块。连通块肯定越简单越好，那么最简单的连通块就是由一个字符构成的连通块了。

我们不难想到以下构造：
```
XXX
XYX
XXX
```
其中 `X` 和 `Y` 各是一个字符。

由于 $1 \le a,b,c,d \le 100$，空间足够，而且 $a,b,c,d$ 均大于 $1$，所以可以想到以下构造：
```
AAAAAAAAAAAAAA...
AAAAAAAAAAAAAA...
.................
BBBBBBBBBBBBBB...
BBBBBBBBBBBBBB...
.................
CCCCCCCCCCCCCC...
CCCCCCCCCCCCCC...
.................
DDDDDDDDDDDDDD...
DDDDDDDDDDDDDD...
```
可以在大块的 `ABCD` 上放置连通块。

为了节省空间，可以交错着放连通块，如下：
```
YXYXYXYXYX
XXXXXXXXXX
YXYXYXYXYX
XXXXXXXXXX
```
这就是我们的构造。

（注：将两行分开放置是因为不会出现上下两列联通的情况。）
### 代码：
```cpp
#define speedup ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define namesp using namespace std

#include <bits/stdc++.h>
namesp;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;

const int INF = INT_MAX;
const int UINF = INT_MIN;
const ll LINF = LONG_LONG_MAX;
const ll ULINF = LONG_LONG_MIN;

#define fp(i,a,b) for(i = a;i < b;i++)
#define fm(i,a,b) for(i = a;i > b;i--)
#define fl(i,a,b) for(i = a;i <= b;i++)
#define fg(i,a,b) for(i = a;i >= b;i--)
#define bk break
#define ctn continue
#define reg register

#define freo(n,m) freopen(n,"r",stdin),freopen(m,"w",stdout)
#define frec(n) fclose(stdin),fclose(stdout)

#define mp make_pair
#define fir first
#define sec second

#define pb push_back
#define pf push_front

#define il inline

#define int short

const int MAX = 50;//n、m 的限制
int c[4];//abcd，为了方便遍历放在数组里
char f[MAX][MAX];//答案数组
const char sz[] = "48 50\n";//这一行不要忘！
//PS1:行数设为 48 是因为它是最接近 50 （不超过）又能被 4 整除的数
//PS2:getchar 速度快，所以存在字符串里，方便输出

int read()//快读函数
{
    reg int x = 0,f = 1;
    reg char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-')
            f = -f;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0',ch = getchar();
    return x * f;
}

il void init()//初始化
{
	reg int i,j,k;
    fp(i,0,4)//i 是方便填字母
        fp(j,0,12)//每一个 ABCD 的大块的行数（48 / 4 所得）
            fp(k,0,MAX)//列数
                f[i*12+j][k] = 'A' + i;//填字母
}

il void input()//输入部分
{
	reg int i;
    fp(i,0,4)
        c[i] = read(),c[i]--;
}

il void solve()//填连通块
{
	reg int i;
    fp(i,0,3)//先循环 BCD
        while(c[i+1]--)//一个一个填，记得--
            f[12*i+((c[i+1]/25)<<1)][(c[i+1]%25)<<1] = 'B' + i;
            /*公式详解：
            第一个[]:
                12*i:ABCD 的大块的最上面一行
                c[i+1]/25:计算出额外的行数
                <<1:将两行分隔开，不会出现诸如
                    YXYXYXYXYX
                    YXYXYXYXYX
                    的情况。
            第二个[]:
                c[i+1]%25:计算出列数
                <<1:将两列分隔开。
            */

    while(c[0]--)//特判 i = 3 的情况。
            f[12*i+((c[0]/25)<<1)][(c[0]%25)<<1] = 'A';
}

il void output()//输出部分
{
	reg int i,j;
	fp(i,0,6)//输出大小不要忘！
		putchar(sz[i]);
    fp(i,0,48)//输出矩阵
    {
        fp(j,0,MAX)
            putchar(f[i][j]);
        putchar('\n');
    }
}

signed main()//主函数，不用多说
{
    init(); 
    input();
    solve();
    output();
    return 0;
}
```

---

## 作者：LG_ljc2022 (赞：0)

## 题目大意

给定四个数 $a, b, c, d$ ，现要求构造一个不超过 $50 \times 50$ 的矩阵，内部包含 $A,B,C,D$ 四个元素，使得每种元素组成的连通块个数是输入给定的四个数。

## Solution

本题是道构造题，方法很多，题解区的大佬们都给出了不同的做法。

其实思路很简单，就是利用间隔构造大小为 $1$ 的连通块，如以下形式：

```cpp
ABCD
BCDA
CDAB
DABC
``````

由此得到了第一种思路，按照上面的形式不断往下排，排不下就往右边排，这样每排一行每种元素的数量就会加一。最后多出来的元素补上就行了。

但是这种思路有些复杂~~（代码调爆了）~~，所以不妨换一种思路。

我们可以发现只要将两个不同的元素进行交替排列，每一个元素都是一个单独的连通块。而又由于每种元素的数量不超过 $100$ 个，排完一行（ $50$ 个元素）最多可以制造 $25$ 个连通块，所以只需要 $4$ 行就可以满足题目的所有数据了。

需要注意的是每两列之间需要有相同的元素隔开，这样才能使得分隔连通块的那些元素不会成为连通块（即不会被“反分隔”），因此完成一个元素的构造总共需要八行，四个元素的构造总共需要 $32$ 行，则矩阵大小定为 $32 \times 50$ 。

最后需要注意的是分隔元素使用的元素也会占据数量，需要留出 $1$ 个作为分隔符，互相用来分隔的两部分之间要注意隔开。

描述可能有些抽象，结合以下样例能更好的理解。

#### Input
```cpp
5 5 9 2
``````

#### Output
```cpp
ABABABABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB //ABAB式排列，排列四个留下一个作为分隔B的分隔大连通块
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA //互相分隔部分隔开，避免下方B与上方的分隔符合并失效
BABABABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA //同上
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
DCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD //同上
CDCDCDCDCDCDCDCDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
``````

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int A, B, C, D;
char ans[55][55];
int main()
{
	
	scanf("%d%d%d%d", &A, &B, &C, &D);
	int a = A, b = B, c = C, d = D;
	
	for (int i = 1; i <= 8; i++) //只需八行
		for (int j = 1; j <= 50; j++) ans[i][j] = 'B'; //设置分隔符
	b--;
	for (int i = 1; i <= 8 && a > 1; i += 2) //交替式排列 + 留下字符作为下次的分隔
		for (int j = 1; j <= 50 && a > 1; j += 2) ans[i][j] = 'A', a--;
	
	for (int i = 9; i <= 16; i++)
		for (int j = 1; j <= 50; j++) ans[i][j] = 'A';
	a--;
	for (int i = 10; i <= 16 && b >= 1; i += 2) //互相分隔的部分隔开
		for (int j = 1; j <= 50 && b >= 1; j += 2) ans[i][j] = 'B', b--;
	
	for (int i = 17; i <= 24; i++) //同上
		for (int j = 1; j <= 50; j++) ans[i][j] = 'C';
	c--;
	for (int i = 17; i <= 24 && d > 1; i += 2)
		for (int j = 1; j <= 50 && d > 1; j += 2) ans[i][j] = 'D', d--;
	
	for (int i = 25; i <= 32; i++)
		for (int j = 1; j <= 50; j++) ans[i][j] = 'D';
	d--;
	for (int i = 26; i <= 32 && c >= 1; i += 2)
		for (int j = 1; j <= 50 && c >= 1; j += 2) ans[i][j] = 'C', c--;
	
	
	printf("32 50\n"); //记得输出大小
	for (int i = 1; i <= 32; i++)
	{
		for (int j = 1; j <= 50; j++) printf("%c", ans[i][j]);
		printf("\n");
	}
	
	return 0;
}
``````

---

## 作者：mountain_climber (赞：0)

其实是较为简易的一道构造题，抓住重要条件 $1 \leq a,b,c,d$ 就能做出来。

容易发现，任意要求都呢能在 $50 \times 50$ 的最大矩阵中构造出来，所以我们不妨就直接在 $50 \times 50$ 的矩阵上构造。

对于 $a=b=c=d=1$ 的情况，可以构造出：

```
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
```

然后将一般情况就是在这个矩阵的基础上再构造出 $a-1,b-1,c-1,d-1$ 直接将一种字母的剩余构造到相邻的不同字符里即可，这是对 $a=b=c=d=100$ 的构造，思路很明显了。

```
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
ACACACACACACACACACAAAAAAACDCDCDCDCDCDCDCDCDCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
ACACACACACACACACACAAAAAAACDCDCDCDCDCDCDCDCDCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
ACACACACACACACACACAAAAAAACDCDCDCDCDCDCDCDCDCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
ACACACACACACACACAAAAAAAAACDCDCDCDCDCDCDCDCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
ACACACACACACACACAAAAAAAAACDCDCDCDCDCDCDCDCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
ACACACACACACACACAAAAAAAAACDCDCDCDCDCDCDCDCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
ACACACACACACACACAAAAAAAAACDCDCDCDCDCDCDCDCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
ACACACACACACACACAAAAAAAAACDCDCDCDCDCDCDCDCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
ACACACACACACACACAAAAAAAAACDCDCDCDCDCDCDCDCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
ACACACACACACACACAAAAAAAAACDCDCDCDCDCDCDCDCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
ACACACACACACACACAAAAAAAAACDCDCDCDCDCDCDCDCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
ACACACACACACACACAAAAAAAAACDCDCDCDCDCDCDCDCCCCCCCCC
AAAAAAAAAAAAAAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCC
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BABABABABABABABABABBBBBBBDBDBDBDBDBDBDBDBDBDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BABABABABABABABABABBBBBBBDBDBDBDBDBDBDBDBDBDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BABABABABABABABABABBBBBBBDBDBDBDBDBDBDBDBDBDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BABABABABABABABABBBBBBBBBDBDBDBDBDBDBDBDBDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BABABABABABABABABBBBBBBBBDBDBDBDBDBDBDBDBDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BABABABABABABABABBBBBBBBBDBDBDBDBDBDBDBDBDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BABABABABABABABABBBBBBBBBDBDBDBDBDBDBDBDBDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BABABABABABABABABBBBBBBBBDBDBDBDBDBDBDBDBDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BABABABABABABABABBBBBBBBBDBDBDBDBDBDBDBDBDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BABABABABABABABABBBBBBBBBDBDBDBDBDBDBDBDBDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BABABABABABABABABBBBBBBBBDBDBDBDBDBDBDBDBDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
BABABABABABABABABBBBBBBBBDBDBDBDBDBDBDBDBDDDDDDDDD
BBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDD
```

类似于：

```
xxxxxxxxx
x x x x x
xxxxxxxxx
x x x x x
xxxxxxxxx
x x x x x
xxxxxxxxx
x x x x x
xxxxxxxxx
```

注意到 $a-1,b-1,c-1,d-1 \leq 99$，因为 $(\lfloor \frac{25}{2} \rfloor)^{2}=144, 99 \lt 144$，所以这种构造方式一定可以构造出来。


下面放一下AC代码罢。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=100;
int a,b,c,d;
char ans[N][N];
void ipt(){
	scanf("%d%d%d%d",&a,&b,&c,&d);
}
void init(int l1,int r1,int l2,int r2,char tar){
	for(int i=l1;i<=r1;i++)
		for(int j=l2;j<=r2;j++)
			ans[i][j]=tar;
}
void put(int l1,int r1,int cnt,char tar){
	int x=l1,y=r1;
	for(int i=1;i<=12;i++){
		x=l1;
		for(int j=1;j<=12;j++){
			ans[x][y]=tar;
			cnt--;
			if(cnt==0) return;
			x+=2;
		}
		y+=2;
	}
}
void solve(){
	init(1,25,1,25,'A');
	init(26,50,1,25,'B');
	init(1,25,26,50,'C');
	init(26,50,26,50,'D');
	if(c-1>0) put(2,2,c-1,'C');
	if(d-1>0) put(2,27,d-1,'D');
	if(b-1>0) put(27,27,b-1,'B');
	if(a-1>0) put(27,2,a-1,'A');
	printf("50 50\n"); 
	for(int i=1;i<=50;i++){
		for(int j=1;j<=50;j++)
			printf("%c",ans[i][j]);
		printf("\n");
	}
}
int main(){
	ipt();
	solve();
	return 0;
}
```

[AC记录](https://codeforces.com/contest/989/submission/233880303)

---

## 作者：Drind (赞：0)

### 题目解析
这题要求我们构造一个图，其中各个字母的连通块个数给定。

我们发现图最大能有 2500 个格子，但是只会有最多 400 个连通块，所以考虑乱搞。

首先，我们先想一下样例里的那种构造能不能扩展，也就是外面一圈加上里面黑白染色。我们发现这么做很困难，因为可能一种颜色特别多，里面没法分割。

那么我们考虑用一种颜色做“墙”，分割出 300 个“房间”，让其他三种颜色住进去。但是这样作为墙的元素只有一个连通块，很麻烦。所以我们再拿出原本住进去的一个元素，再做一个不同颜色的墙，让原来的墙住进新的房间。

墙的样子大致是这样的：
```
XOXOXOXOXOX
XXXXXXXXXXX
OXOXOXOXOXX
```

代码里以 A,B 作为两次的墙。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;

int mp[51][51];

inline void fake_main(){
	int a,b,c,d,now; cin>>a>>b>>c>>d; a--;
	for(int i=1;i<=7;i++){//只需要最多七次建墙(每次消耗三行）
		mp[i*3-2][50]=mp[i*3-1][50]=mp[i*3][50]=1;//把最右边连上，保证每行的墙联通
		for(int j=1;j<=50;j++) mp[i*3-1][j]=1;
		for(int j=1;j<=50;j+=2) mp[i*3-2][j]=1;
		for(int j=2;j<=50;j+=2) mp[i*3][j]=1;//建墙
		for(int j=1;j<=49;j+=2){
			if(b!=1) mp[i*3][j]=2,b--;
			else if(c!=0) mp[i*3][j]=3,c--;
			else if(d!=0) mp[i*3][j]=4,d--;//住人，注意人住完了要放墙的元素进去占位。
			else mp[i*3][j]=1;
		}
		for(int j=2;j<=49;j+=2){
			if(b!=1) mp[i*3-2][j]=2,b--;
			else if(c!=0) mp[i*3-2][j]=3,c--;
			else if(d!=0) mp[i*3-2][j]=4,d--;
			else mp[i*3-2][j]=1;
		}
		if(b+c+d==1){
			for(int j=1;j<=50;j++) mp[i*3+1][j]=1;
			now=i*3+1; break;//如果住满了，那就收尾一下，在建一行的墙，和下面的分隔开。
		}
	}
	if(a!=0){//如果第一种元素还有剩余，拿第二种元素来建墙
		for(int i=1;i<=50;i++) mp[now+1][i]=2; now++;//先和上面的墙隔开
		for(int i=1;i<=3;i++){
			mp[i*3+now-2][50]=mp[i*3+now-1][50]=mp[i*3+now][50]=2;
			for(int j=1;j<=50;j++) mp[i*3+now-1][j]=2;
			for(int j=1;j<=50;j+=2) mp[i*3+now-2][j]=2;
			for(int j=2;j<=50;j+=2) mp[i*3+now][j]=2;//建墙
			for(int j=1;j<=49;j+=2){//住人
				if(a!=0) mp[i*3+now][j]=1,a--;
				else mp[i*3+now][j]=2;
			}
			for(int j=2;j<=49;j+=2){
				if(a!=0) mp[i*3+now-2][j]=1,a--;
				else mp[i*3+now-2][j]=2;
			}
			if(a==0){
				now=i*3+now; break;
			}
		}
		for(int i=now+1;i<=50;i++) for(int j=1;j<=50;j++) mp[i][j]=2;//如果还有空间就全部塞满
	}else{//如果第一种元素只有一个的话，那么不用建第二个墙了，直接塞满结束。
		for(int i=now+1;i<=50;i++) for(int j=1;j<=50;j++) mp[i][j]=1;
		mp[50][50]=2;//注意我们留了一个二号元素来建墙（但是墙没建成），所以给他塞回去。
	}
	cout<<"50 50\n";
	for(int i=1;i<=50;i++){
		for(int j=1;j<=50;j++){
			cout<<char('A'+mp[i][j]-1);
		}
		cout<<"\n";
	}
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：CQWDX (赞：0)

有一点人类智慧，但不多。

最开始有一个思路：在矩阵的上方间隔插入 ABCD 四种方块，然后在矩阵下方扔一整个连通块。

be like:

```cpp
1 2 1 2 1 2 1 2
3 1 3 1 3 1 2 1
4 3 4 3 4 3 1 1
1 1 1 1 1 1 1 1
```

然后发现好像会被 1 大 3 小的情况卡爆。会剩下几个类型相同的连通块。~~主要是不会写。~~

然后就换了个思路。

先考虑一下刚刚被卡的情况。发现可以用数量较少的连通块填充整个矩阵后在内部嵌入 $1\times 1$ 的小方块。

然后发现在矩阵足够大的情况下，这是个通解。

既然 $n$ 和 $m$ 可以自选，那么根据上述思路将其尽量往大了选。

即 $n=50,m=50$。

将矩阵分成 $4$ 个 $25\times25$ 的小矩阵，分别用 ABCD 填充。

```cpp
A A A B B B
A A A B B B
A A A B B B
C C C D D D
C C C D D D
C C C D D D
```

然后对于每个小矩阵，往里面嵌入若干个其他颜色，形成若干个连通块。

```cpp
A A A B B B
A D A B C B
A A A B B B
C C C D D D
C B C D A D
C C C D D D
```

注：若嵌入的不是其所在矩阵的对角线上对应的颜色，注意在矩阵的边缘留一行，用于隔离连通块。

为保证矩阵内部的“背景色”联通，需保证每个小方块之间相隔一行。

```cpp
A A A A A A A
A D A D A D A
A A A A A A A
A D A D A D A
A A A A A A A
A D A D A D A
A A A A A A A
```

对于每个矩阵，内部可嵌入 $\lfloor\frac{25}{2}\rfloor\times\lfloor\frac{25}{2}\rfloor=144>100$ 个连通块。可以保证方案的正确性。

~~时间复杂度 $O(n^2)$~~ 构造题要什么时间复杂度啊

```cpp
#include <bits/stdc++.h>
int a, b, c, d;
char f[120][120];
int main() {
	scanf("%d %d %d %d", &a, &b, &c, &d);
	printf("50 50\n");
	for(int i = 1; i <= 50; i++)
		for(int j = 1; j <= 50; j++) {
			if(i <= 25 && j <= 25) f[i][j] = 'A';
			else if(i <= 25 && j > 25) f[i][j] = 'B';
			else if(i > 25 && j <= 25) f[i][j] = 'C';
			else f[i][j] = 'D';
		}
	a--, b--, c--, d--;
	for(int i = 1; i < 25 && b > 0; i += 2)
		for(int j = 1; j < 25 && b > 0; j += 2, b--)
			f[i][j] = 'B';
	for(int i = 1; i < 25 && c > 0; i += 2)
		for(int j = 26; j < 50 && c > 0; j += 2, c--)
			f[i][j] = 'C';
	for(int i = 26; i < 50 && d > 0; i += 2)
		for(int j = 1; j < 25 && d > 0; j += 2, d--)
			f[i][j] = 'D';
	for(int i = 26; i < 50 && a > 0; i += 2)
		for(int j = 26; j < 50 && a > 0; j += 2, a--)
			f[i][j] = 'A';
	for(int i = 1; i <= 50; i++, printf("\n"))
		for(int j = 1; j <= 50; j++)
			printf("%c", f[i][j]);
	return 0;
}
```

---

## 作者：__LiChangChao__ (赞：0)

## 思路

首先注意到 $1\le a,b,c,d \le 100,1\le n,m \le 50$，所以有 $4\le a+b+c+d \le 400$ 以及每种花都会出现，同时我们还有至多 $2500$ 个格子来分配，所以直接设定 $n=m=50$。

那么先挑一种花打底，为了方便我直接选择 `A`。

先将整个矩阵填满我们选的打底花，然后考虑剩下的怎么办。

首先如果打底色还剩下一些，那么可以考虑再分一部分换一种打底花，这里我又为了方便选择了 `B`。

那么我们就可以将多出来的主打底花全部塞到分出来的这一部分，每个占据 $1\times 1$ 的小格，每隔一行或一列放一个，每个都是独立的连通块，例如：

```
BABABABABA
BBBBBBBBBB
BABABABABA
BBBBBBBBBB
```

由于 $1\le a \le 100$，则 $0\le a-1 \le 99,0\le 2\lceil \frac{a-1}{\frac{n}{2}}\rceil\le 8$，此时我们还有 $42$ 行来分配，剩下的也可以按照我们在 `B` 中放 `A` 的策略来放，由于   $2\le b-1+c+d \le 299,2\le 2\lceil \frac{b-1+c+d}{\frac{n}{2}}\rceil\le 24<42$，所以一定能全部放下。

于是这道题就构造完了。

## 代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
const int maxn=55;
int a,b,c,d;
char ans[maxn][maxn];
int n=50;
int main() {
	puts("50 50");
	scanf("%d%d%d%d",&a,&b,&c,&d);
	a--;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			ans[i][j]='A';
		}
	}
	if(a)b--;
	int s=ceil(a/25.0);
	for(int i=1; i<=2*s; i++) {
		for(int j=1; j<=50; j++)ans[i][j]='B';
		if(i%2) {
			for(int j=1; j<=50&&a; j+=2) {
				a--;
				ans[i][j]='A';
			}
		}
	}
	for(int i=2*s+1; i<=50; i++) {
		if(i%2==0) {
			for(int j=1; j<=50; j+=2) {
				if(b)b--,ans[i][j]='B';
				else if(c)c--,ans[i][j]='C';
				else if(d)d--,ans[i][j]='D';
				else break;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			putchar(ans[i][j]);
		}
		puts("");
	}
}

```

---

