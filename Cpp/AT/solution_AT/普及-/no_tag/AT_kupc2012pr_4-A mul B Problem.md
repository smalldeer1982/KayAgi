# A mul B Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/kupc2012pr/tasks/kupc2012pr_4



# 题解

## 作者：liuyifan (赞：2)

## 一道重载运算符的模板题
我们只需要对矩阵的*运算进行定义即可

然后直接在读入后puts(a*b==c?"YES":"NO")即可,方便快捷

重载运算符的格式下面有讲,更多的看[这里](http://www.runoob.com/cplusplus/cpp-overloading.html)(个人认为写的还可以)

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register//在某些时候(CCF老年机等)可加速
using namespace std;//不加有时会出问题
vector<vector<double> >a,b,c;//中间不加空格某些古老G++会报错([Error] '>>' should be '> >' within a nested template argument list)
//二维vector的写法,同结构体vector
vector<double>tmp;
int n,x;
inline vector<vector<double> >operator *(vector<vector<double> >arra,vector<vector<double> >arrb)//开始重载运算符了
//记住上面一行的格式,下面的就和一般函数一样了,return运算后的值
//还可以加inline(用途同register,避免卡常)
{
    reg vector<vector<double> >res;//存结果
    //因为是一种特殊的函数,所以也可以用register
    if(arra[0].size()!=arrb.size())return res;//不满足(本题并没有)、
    //arra[0].size():arra[0]这个vector的大小,arrb.size():整个vector的大小
   	res.resize(arra.size());//以下模拟正常矩阵乘法过程
    for(reg int i=0;i<arra.size();i++)res[i].resize(arrb[0].size());
    for(reg int i=0;i<arra.size();i++)
	for(reg int j=0;j<arrb[0].size();j++)
	for(reg int k=0;k<arra[0].size();k++)res[i][j]+=arra[i][k]*arrb[k][j];
    return res;//返回运算结果
}
int main()
{
	scanf("%d",&n);//输入n
	for(reg int i=1;i<=n;i++)
	{
		tmp.clear();
		for(reg int j=1;j<=n;j++)scanf("%d",&x),tmp.push_back(x);
		a.push_back(tmp);
	}
	for(reg int i=1;i<=n;i++)
	{
		tmp.clear();
		for(reg int j=1;j<=n;j++)scanf("%d",&x),tmp.push_back(x);
		b.push_back(tmp);
	}
	for(reg int i=1;i<=n;i++)
	{
		tmp.clear();
		for(reg int j=1;j<=n;j++)scanf("%d",&x),tmp.push_back(x);
		c.push_back(tmp);
	}//输入矩阵a,b,c的值(我想不出更短的写法了)
	puts(a*b==c?"YES":"NO");//输出结果,是不是很方便?
	return 0;//完美的结束
}
```
Ps:72个点真爽
![72个点真爽](https://s1.ax1x.com/2018/10/24/isDZyn.png)

---

## 作者：Post_Malone (赞：1)

## 矩阵乘法模板题  
~~似乎比模板还简单~~  
#### 思路1(0分)  
看题目：$mul=multiplication$，因此：  
```cpp
int a,b,c;
scanf("%d%d%d",&a,&b,&c);
if(c==a*b)printf("YES");
else printf("NO");
```
  
结果显然是WA，仔细一看，原来是**矩阵乘法**  
#### 思路2(100分)  
矩阵乘法定义：(知道的大佬请手动跳过)  
如果$A$是$m * p$的矩阵，$B$是$p * n$的矩阵，$C$是$m * n$的矩阵，且$C$是$A$和$B$的乘积(记作$C=AB$)  
那么有
$$C_{i,j}=\sum_{k=1}^pA_{i,k}B_{k,j}$$  
这题甚至更水，甚至直接使$m=n=p$，这无疑使难度大大降低  
  
定义$A$,$B$,$C$,$D$四个矩阵，分别输入$A$,$B$,$C$，根据公式计算$D=AB$，再比较$C$和$D$是否相同  
  
显然思路2空间上可以优化  
#### 思路3(100分)  
可以只定义$A$,$B$,$C$三个矩阵，分别输入，根据公式计算$C=C-AB$，若$C$为零矩阵则$C=AB$  
  
显然思路3时间和空间上仍可优化  
#### 思路4(100分)  
只定义$A$,$B$两个矩阵和变量$C$，先输入$A$,$B$，再依次输入$C=C_{i,j}$，根据公式计算$C=C-(AB)_{i,j}$，最后若$C=0$则继续，否则直接结束程序(节省时间)  
#### 思路5(?分)  
蒟蒻想不出更简便的方法了，欢迎各位大佬补充！

---

## 作者：雨伞CKY (赞：0)

# 题意简述
给定 $n$ 和 $3$ 个 $n\times n$ 的矩阵 $A,B,C$。判断这三个矩阵是否能满足 $A\cdot B=C$。

# 题目分析
数学中，矩阵乘法是一种根据两个矩阵得到第三个矩阵的二元运算，第三个矩阵即前两者的乘积，称为矩阵积。设 $A$ 是 $n\times m$ 的矩阵，$B$ 是 $m\times p$ 的矩阵，$A\cdot B=C$，则 $C$ 是 $n\times p$ 的矩阵。$A$ 中每一行的 $m$ 个元素都与 $B$ 中对应列的 $m$ 个元素对应相乘，这些乘积的和就是 $C$ 中的一个元素，即 $C_{i,j}=\sum \limits ^{n}_{k=1}A_{i,k}\cdot B_{k,j}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/6dl4cagc.png)

# 代码
```cpp
#include <iostream>
using namespace std;

int N,A[1010][1010],B[1010][1010],C[1010][1010],ans;

int main(){
	cin >> N;
	for (int i = 1;i <= N;i++) for (int j = 1;j <= N;j++) cin >> A[i][j];
	for (int i = 1;i <= N;i++) for (int j = 1;j <= N;j++) cin >> B[i][j];
	for (int i = 1;i <= N;i++) for (int j = 1;j <= N;j++) cin >> C[i][j];
	for (int i = 1;i <= N;i++){
		for (int j = 1;j <= N;j++){
            ans = 0;
			for (int k = 1;k <= N;k++) ans += A[i][k] * B[k][j];
			if (C[i][j] != ans){
				cout << "NO\n";
				return 0;
			}
		}
	}
	cout << "YES\n";
	return 0;
}
```

---

## 作者：YclarHIM0302 (赞：0)

### 注意：本题解是 Java 题解！
## 1.什么是矩阵乘法？
设 $A$ 为 $m\times p$ 的矩阵，$B$ 为 $p\times n$ 的矩阵，那么称 $m\times n$ 的矩阵 $C$ 为矩阵 $A$ 与 $B$ 的乘积，记作 $C=AB$ ，其中矩阵 $C$ 中的第 $m$ 行第 $n$ 列元素可以表示为：

$c_{i,j}=(AB)_{i,j}=\sum\limits_{k=1}^pa_{i,k}b_{k,j}$

也就是说，当

$A=\begin{bmatrix}a_{1,1}&a_{1,2}&a_{1,3}\\\\a_{2,1}&a_{2,2}&a_{2,3}\end{bmatrix}$

$B=\begin{bmatrix}b_{1,1}&b_{1,2}\\\\b_{2,1}&b_{2,2}\\\\b_{3,1}&b_{3,2}\end{bmatrix}$

时，

$C=\begin{bmatrix}a_{1,1}b_{1,1}+a_{1,2}b_{2,1}+a_{1,3}b_{3,1}&a_{1,1}b_{1,2}+a_{1,2}b_{2,2}+a_{1,3}b_{3,2}\\\\a_{2,1}b_{1,1}+a_{2,2}b_{2,1}+a_{2,3}b_{3,1}&a_{2,1}b_{1,2}+a_{2,2}b_{2,2}+a_{2,3}b_{3,2}\end{bmatrix}$

因此，这题只需要for循环判定就可以了！

## 2.代码
```java
import java.util.Scanner;
//载入扫描器
public class Main {
//注意类名为Main
	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		int[][] a=new int[1001][1001];
		int[][] b=new int[1001][1001];
		int[][] c=new int[1001][1001];
		int n;
		Scanner cin=new Scanner(System.in);
		n=cin.nextInt();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				a[i][j]=cin.nextInt();
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				b[i][j]=cin.nextInt();
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				c[i][j]=cin.nextInt();
			}
		cin.close();//关闭输入
		boolean flag=true;
		for(int i=1;i<=n;i++)//循环m
		{
			for(int j=1;j<=n;j++)//循环n
			{
				int res=0;
				for(int k=1;k<=n;k++)//循环p
				{
					res+=a[i][k]*b[k][j];
				}
				if(res!=c[i][j])//比较结果
				{
					System.out.println("NO");
					flag=false;//设 flag 弹出
					break;
				}
			}
			if(!flag) break;
		}
		if(flag) System.out.println("YES");
	}
}

```
### 注：本人在AtCoder通过，在洛谷上传时出现问题，但绝对是AC！

---

## 作者：·糯· (赞：0)

## 题目分析
此题只用将矩阵乘法的思路搬上来，再做一个判断的即可，注意矩阵乘法是多个数相乘后再相加，最后输出的答案字符串要全部大写。
## 代码展示
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1010][1010],b[1010][1010],c[1010][1010];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>b[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>c[i][j];
	bool flag;
	flag=true;//初始化
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			int sum=0;
			for(int k=1;k<=n;k++)
				sum+=a[i][k]*b[k][j];//矩阵乘法
			if(sum!=c[i][j]){
				flag=false;//不满足
				break;
			}
		}
	if(flag)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
	return 0;
}
```


---

## 作者：Jiyuu_no_Tsubasa (赞：0)

一道矩阵乘法裸题，

那么我们来重温一遍矩阵乘法。

矩阵乘法是一种运算，常用于提速。

如果有 $2$ 个可以分别表示为 $n\times r$ 与 $r\times m$ 的矩阵，

那么它们就可以进行矩阵乘法并得到 $n\times m$ 的答案矩阵。

其具体流程如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/wd8xi6ry.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

答案的 $i$ 行 $j$ 列的数，

即为第 $1$ 个的矩阵的 $i$ 行的每个数，

与第 $2$ 个矩阵的 $j$ 行的每个数分别相乘结果的和。

以上面那张图来说就是：

$1\times 7+2\times 9+3\times 11 = 58$。

因此，我们就可以写代码了。

```
#include<iostream>
using namespace std;
const int N=1010;
int a[N][N],b[N][N];
int c[N][N],ans[N][N];
int main(){
    int n; cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>b[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>c[i][j];
    for(int i=1;i<=n;i++)//矩阵乘法 
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
                ans[i][j]+=a[i][k]*b[k][j];
    bool flag=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(c[i][j]!=ans[i][j]){
                flag=0; break;
            }
    cout<<(flag?"YES":"NO")<<endl;//AT题库输出完毕后需加换行
    //三目运算符，写成（a?b:c），意为若 a 成立，返回 b ，否则返回 c
}
```
## 更新日志
$2021.2.25$：发现图炸了，更换图床。

---

## 作者：1lgorithm (赞：0)

### 裸的矩阵乘法。

这道题我们既可以用重载运算符，函数和主函数直接计算来写。

我用的是直接计算。

矩阵乘法的法则：

如果 C=A*B ,当且仅当 $ C_{i,j}=\sum^{n}_{k=1} A_{i,k}*B_{k,j} $

所以我们直接模拟计算即可。

代码：
```cpp
#include<iostream>
using namespace std;
int n;
int a[1001][1001],b[1001][1001],c[1001][1001],x[1001][1001];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>b[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>x[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				c[i][j]+=a[i][k]*b[k][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(c[i][j]!=x[i][j]){
				cout<<"NO"<<endl;
				return 0;
			}
	cout<<"YES"<<endl;
}
```


---

## 作者：翼德天尊 (赞：0)

## STEP 1 题目大意

给定三个矩阵 $A$，$B$，$C$，问用矩阵乘法是否 $A\times B=C$。

## STEP 2 浅谈解法

这道题都是围绕**矩阵乘法**展开的，那么到底什么是**矩阵乘法**呢？

>矩阵相乘最重要的方法是一般矩阵乘积。它只有在第一个矩阵的列数（column）和第二个矩阵的行数（row）相同时才有意义——百度百科

简单来说，设 $A$ 矩阵和 $B$ 矩阵的乘积为 $D$ 矩阵，则矩阵乘法的公式如下：

$$D_{i,j}=\sum_{k=1}^p A_{i,k}B_{k,j}$$

也就是说，假设：

$$A=\begin{bmatrix}a_{1,1}&a_{1,2}&a_{1,3}\\a_{2,1}&a_{2,2}&a_{2,3}\end{bmatrix}$$

$$B=\begin{bmatrix}b_{1,1}&b_{1,2}\\b_{2,1}&b_{2,2}\\b_{3,1}&b_{3,2}\end{bmatrix}$$

那么：

$$D=AB=\begin{bmatrix}a_{1,1}b_{1,1}+a_{1,2}b_{2,1}+a_{1,3}b_{3,1}&a_{1,1}b_{1,2}+a_{1,2}b_{2,2}+a_{1,3}b_{3,2}\\a_{2,1}b_{1,1}+a_{2,2}b_{2,1}+a_{2,3}b_{3,1}&a_{2,1}b_{1,2}+a_{2,2}b_{2,2}+a_{2,3}b_{3,2}\end{bmatrix}$$

仔细体会一下？

那么这道题就好做了，暴力算出 $D$ 矩阵后与 $C$ 矩阵比较即可。

## STEP 3 AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1005][1005],b[1005][1005],c[1005][1005],d[1005][1005];
int read(){//快读
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
} 
int main(){
    n=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            a[i][j]=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            b[i][j]=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            c[i][j]=read();//读入
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int p=1;p<=n;p++)
                d[i][j]+=a[i][p]*b[p][j];//按照公式计算
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if (c[i][j]!=d[i][j]){
                puts("NO");
                return 0;
            }//比较
    puts("YES");
    return 0;
}
```


---

## 作者：LiveZoom (赞：0)

[博客食用效果更佳](https://www.luogu.com.cn/blog/lza/solution-at195)
# 题解 AT195 【A mul B Problem】
本题其实是道矩阵乘法模板题  
- 矩阵乘法

有三个矩阵$a,b,c$  
矩阵乘法就是任意
$$c_{i,j}=\sum_{k=1}^{n}{a_{i,k}\times b_{k,j}}$$
知道这个就好办了
- 代码实现

本题实现用结构体+重载运算符最清爽（~~我太弱了，不会用class来写~~）

结构体：

```cpp
struct matrix{
	int a[1005][1005];//定义二维数组
	friend matrix operator *(const matrix &m1,const matrix &m2){//重载矩阵乘法
		matrix cur;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					cur.a[i][j]+=m1.a[i][k]*m2.a[k][j];
				}
				
			}
		}
		return cur;
	}
	friend bool operator ==(const matrix &m1,const matrix &m2){//重载等号
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(m1.a[i][j]!=m2.a[i][j]){
					return false;
				}
			}
		}
		return true;
	}
};
```
清爽主函数：

```cpp
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){//输入
			scanf("%d",&x.a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&y.a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&z.a[i][j]);
		}
	}
	if(x*y==z)puts("YES");//判断
	else puts("NO");
    return 0;
}
```
完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct matrix{
	int a[1005][1005];
	friend matrix operator *(const matrix &m1,const matrix &m2){
		matrix cur;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					cur.a[i][j]+=m1.a[i][k]*m2.a[k][j];
				}
				
			}
		}
		return cur;
	}
	friend bool operator ==(const matrix &m1,const matrix &m2){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(m1.a[i][j]!=m2.a[i][j]){
					return false;
				}
			}
		}
		return true;
	}
};
matrix x,y,z;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&x.a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&y.a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&z.a[i][j]);
		}
	}
	if(x*y==z)puts("YES");
	else puts("NO");
    return 0;
}
```
虽然没有防作弊，但也不要Ctrl+C哦~

求通过
# The end

---

## 作者：hensier (赞：0)

~~本蒟蒻看到标题A mul B Problem之后，花了一点时间找到自己珍藏已久的高精度乘法模板……~~

开门见山，首先是矩阵乘法的定义。对于矩阵大小分别为$n\times n,n\times n$的矩阵$A,B$，和用来保存矩阵乘法运算结果的大小为$n\times n$的矩阵$C$，我们规定：

$$c[i][j]=\sum_{k=1}^n a[i][k]·b[k][j]=a[i][1]·b[1][j]+...+a[i][n]+b[n][j]$$

因此，我们在运算之后只需对原矩阵进行判断即可。

$AC$代码：

```cpp
#include<cstdio>
#define F(x,y)for(int i=x;i<=y;i++)
int n,i,j,k,a[1001][1001],b[1001][1001],c[1001][1001],d[1001][1001];
inline void f(int x[][1001]){for(i=1;i<=n;i++)for(j=1;j<=n;j++)scanf("%d",&x[i][j]);}//输入二维数组的函数
int main()
{
    scanf("%d",&n);
    f(a);
    f(b);
    f(c);//三次输入用函数替代
    for(i=1;i<=n;i++)for(j=1;j<=n;j++)for(k=1;k<=n;k++)d[i][j]+=a[i][k]*b[k][j];//矩阵乘法的定义
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(c[i][j]-d[i][j])//只要一个元素不相等就输出NO
            {
                printf("NO\n");
                return 0;
            }
        }
    }
    printf("YES\n");//否则输出YES
}
```

---

