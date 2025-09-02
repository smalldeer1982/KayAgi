# Multiplication Table

## 题目描述

Petya studies positional notations. He has already learned to add and subtract numbers in the systems of notations with different radices and has moved on to a more complicated action — multiplication. To multiply large numbers one has to learn the multiplication table. Unfortunately, in the second grade students learn only the multiplication table of decimals (and some students even learn it in the first grade). Help Petya make a multiplication table for numbers in the system of notations with the radix $ k $ .

## 样例 #1

### 输入

```
10
```

### 输出

```
1  2  3  4  5  6  7  8  9
2  4  6  8 10 12 14 16 18
3  6  9 12 15 18 21 24 27
4  8 12 16 20 24 28 32 36
5 10 15 20 25 30 35 40 45
6 12 18 24 30 36 42 48 54
7 14 21 28 35 42 49 56 63
8 16 24 32 40 48 56 64 72
9 18 27 36 45 54 63 72 81
```

## 样例 #2

### 输入

```
3
```

### 输出

```
1  2
2 11```

# 题解

## 作者：sandwich (赞：6)

# 打表的“思想”
既然还没有人来写打表，我就来当第一了，数据只有2~10，可以说是很水了

反正，万物可打表，打表的话就不用说什么了，一行行手动转换就好了呀

那么代码就这么出来了

我这个~~肝帝~~完了20分钟左右，手动打表真的辛苦！！！
你们加油哦！！！

这道题目也太简单了，真的……

### 当然，我这么辛辛苦苦打出来的表这么能让你们弄走呢？加了一些非常简单的防抄袭，滑稽滑稽！！！
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
    cin>>n;
    if(n==2)
    cout<<"1";
    if(n==3)
    cout<<"1  2"<<endl<<"2 11";
    if(n==4)
    {
        cout<<"1  2  3"<<endl;
        cout<<"2 10 12"<<endl;
        cout<<"3 12 21"<<endl;
	}
	if(n==5)
	{
		cout<<"1  2  3  4"<<endl;
        cout<<"2  4 11 13"<<endl;
        cout<<"3 11 14 22"<<endl;
        cout<<"4 13 22 31"<<endl;
	}
	if(n==6)
	{
		cout<<"1  2  3  4  5"<<endl;
        cout<<"2  4 10 12 14"<<endl;
        cout<<"3 10 13 20 23"<<endl;
        cout<<"4 12 20 24 32"<<endl;
    }
	if(n==7)
	{
		cout<<"1  2  3  4  5  6"<<endl;
        cout<<"2  4  6 11 13 15"<<endl;
        cout<<"3  6 12 15 21 24"<<endl;
        cout<<"4 11 15 22 26 33"<<endl;
        cout<<"5 13 21 26 34 42"<<endl;
	}
	if(n==8)
	{
		cout<<"1  2  3  4  5  6  7"<<endl;
        cout<<"2  4  6 10 12 14 16"<<endl;
        cout<<"3  6 11 14 17 22 25"<<endl;
        cout<<"4 10 14 20 24 30 34"<<endl;
        cout<<"5 12 17 24 31 36 43"<<endl;
        cout<<"6 14 22 30 36 44 52"<<endl;
	}
	if(n==9)
	{
		cout<<"1  2   3  4  5  6  7  8"<<endl;
        cout<<"2  4   6  8 11 13 15 17"<<endl;
        cout<<"3  6  10 13 16 20 23 26"<<endl;
        cout<<"4  8  13 17 22 26 31 35"<<endl;
        cout<<"5  11 16 22 27 33 38 44"<<endl;
        cout<<"6  13 20 26 33 40 46 53"<<endl;
        cout<<"7  15 23 31 38 46 54 62"<<endl;
	}
	if(n==10)
	{
		cout<<"1  2  3  4  5  6  7  8  9"<<endl;
        cout<<"2  4  6  8 10 12 14 16 18"<<endl;
        cout<<"3  6  9 12 15 18 21 24 27"<<endl;
        cout<<"4  8 12 16 20 24 28 32 36"<<endl;
        cout<<"5 10 15 20 25 30 35 40 45"<<endl;
        cout<<"6 12 18 24 30 36 42 48 54"<<endl;
        cout<<"7 14 21 28 35 42 49 56 63"<<endl;
        cout<<"8 16 24 32 40 48 56 64 72"<<endl;
	}
    return 0;
}
```


---

## 作者：Nortrom (赞：5)

# 看了各位大佬的题解，发现没有像我这样用数组直接代表位的
本人用了个笨方法，就是先把每位数先除出来，放进数组里，最后在处理成数。

处理如下：

------------

```cpp
int cl(int x)
{
	int s=0,i=0,w[101];
	while(x>=1)
	{
		w[++i]=x%n;//++i=i++;w[i]=x%n;
		x=x/n;
	}
	for(int j=i;j>=1;j--)
	   s=s*10+w[j];
	return s;
}
```

------------

完整代码如下：


------------

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,a[11][11];
int cl(int x)
{
	int s=0,i=0,w[101];
	while(x>=1)
	{
		w[++i]=x%n;
		x=x/n;
	}
	for(int j=i;j>=1;j--)
	   s=s*10+w[j];
	return s;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	for(int j=1;j<n;j++)
	{
		a[i][j]=i*j;
		a[i][j]=cl(a[i][j]);
	}//方便检查
	for(int i=1;i<n;i++)
	{
		for(int j=1;j<n;j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
```


------------

原创不易，如有雷同，纯属偶然。
拒绝抄代码应付。

---

## 作者：江户川·萝卜 (赞：2)

这道题大概有点谔评吧（预计只能评到红~橙

---
首先，我们观察样例，发现就是输出一个 $(k-1)(k-1)$  的方阵，第i行j列的元素是k进制下的 $ij$。

然后发现最多只有两位数，因为最小的三位数 $100_{(k)}=k^2>(k-1)(k-1)$ 。

所以假设转成k进制后的数第1位是x，第2位是y，则 $xk+y=ij,x=ij\div k ,y=ij \bmod k$。


注意格式问题。

Code:（在最优解第6名）
```cpp
#include<iostream>
#include<iomanip>
using namespace std;
int k;
int main(){
	cin>>k;
	for(int i=1;i<k;i++){
		cout<<i;
		for(int j=2;j<k;j++){
			if(i*j<k) cout<<"  "<<i*j%k;
			else cout<<setw(2)<<i*j/k<<i*j%k;
		}
		cout<<endl;
	}
}
```

---

## 作者：时律 (赞：2)

考虑一下，因为仅仅是【输出k进制下的乘法表】，所以只需把乘法表的每一项都转化为k进制即可。

打完代码提交后，看了一下题解，才发现不用输出多余的空格……

可是懒得改了。

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a;//我这个人喜欢abcde......不用题目中的字母
	cin>>a;
	for(int i=1;i<=a-1;i++,putchar('\n'))
		for(int j=1;j<=a-1;j++)
			if(j!=1) printf("%2d ",(i*j/a)*10+(i*j)%a);//因为转换为k进制后，得出的数字最高也就两位，可以直接算
			else printf("%d ",i*j);//......不晓得不用输出多余的空格......
}
```

~~另外我觉得，这题若是从2进制到16进制，会不会难做一点~~

---

## 作者：tobie (赞：1)

这道题题面看起来很迷惑，但是主要意思就是将一个九九乘法表转化成 $k$ 禁进制而已。

因为 $k$ 小得可怜，所以暴力就可以了。

代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int k;
int change(int a)//进制转换部分
{
    int ans=0,num=0,ans2[1005]={0};//这里是把k进制数按照数位变成10进制表示，输出会更方便。
    while(a>0)//进制转换过程
    {
        ans2[++num]=a%k;
        a/=k;
    }
    for(int i=num;i>=1;i--)
        ans=ans*10+ans2[i];
    return ans;
}
int main()
{
    scanf("%d",&k);
    for(int i=1;i<k;i++)
    {
        for(int j=1;j<k;j++)
        printf("%d ",change(i*j));
        printf("\n");
    }
    return 0;
}
```

---

## 作者：Valk_R (赞：0)

#### 本蒟蒻的第二篇题解


[题目传送门](https://www.luogu.com.cn/problem/CF39H)

## 题意
输出 $k$ 进制下的乘法表。

## 分析
观察数据范围，发现并不大， $k$ 小于等于 $10$ 。那么我们直接进行模拟。有以下两步：

1. 用十进制乘出每个数；
1. 再将这个数转换成对应的进制进行输出（进制转换方法见代码注释）。

这个做法速度较慢，但是这题不用担心是否会超时，因为数据范围很小。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int work(int n,int k)
{
	int ans=0,p=0;
	while(n)
	{
		ans+=(n%k)*pow(10,p);
		n/=k;
		p++;
	}
    	//用取余法，取余得到的每一位存在ans中
        //就像我们手算十进制转换成二进制时，每次除2，若第n次余几，第n位就是几
        //我们只需要把这个余下来的数加到ans前面就好了
        //因为这个数是加在前面，所以加在ans上时需要乘10的n-1次方，用p记录n-1
	return ans;
}
int k;
int main()
{
	cin>>k;
	for(int i=1;i<k;i++)//注意是i<k,因为乘法表只需要个位数进行相乘，而i=k时i转换为k进制就是两位数了
	{
		for(int j=1;j<k;j++)
		{
			cout<<work(i*j,k)<<" ";//i*j即为十进制对应的数，用work()函数将其转换成k进制
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：_cmh (赞：0)

在最优解第一页并且代码可能最好理解，最短的蒟蒻过来水个题解。

多简单的一道题，为啥各位大佬代码都写这么长？

用双重 $for$ 循环，注意规模时 $(n-1)\times(n-1)$ 的，循环 $1\sim(n-1)$ 即可。

容易发现乘法表每一位的数字为 $i\times j$ 再转化为 $n$ 进制，而转化后的数字最多不超过 $2$ 位，所以直接输出 $(i\times j\div a)\mod a + (i\times j)\mod a$即可。

最短代码：

```cpp
#include<iostream>
using namespace std;
int n;
int main(){
	cin>>n;
	for(int i=1;i<n;i++,cout<<endl) for(int j=1;j<n;j++) cout<<(i*j/n)%n*10+(i*j)%n<<" ";
    return 0;
}
```

求赞！

---

## 作者：CrTsIr400 (赞：0)

这道题就是给你 $n$ ，求出 $(n-1)\times (n-1)$ **大小** 的一个 $n$ 进制乘法表。

看了看别人的题解，发现转换函数都写得比较复杂，于是来个简单点的解法。

```cpp
int turn(int x,int k)
{
	int res=0,js=1;
	while(x)res+=js*(x%k),x/=k,js*=10;
	return res;
}
```

Q：这个`js`的意义何在？

A：这个`js`是为了方便转化整数位。

比如说窝想把 $1279$ 化成 $8$ 进制数。

转化出来的结果就是 $2377_{(8)}$。

但是，因为最后要求整数输出，`return`的值必须为 $2377$ ，所以要`*=10`。

这个`res+=js*(x%k)`如何理解呢？

因为$2377=2\times 10^3 + 3\times 10^2 +7\times 10 + 7$

但是其实在程序里这个`res`的值其实是这样变化的：

`7`

`77`

`377`

`2377`

原因读者自己思考。

Q：`res`不会爆炸吗？

A：确实有可能，比如说转化个$2048_{(2)}$，它就爆了。

但是因为题目范围不大，所以能过。

Q：球完整代码

A：

```cpp
int n;
inline int turn(int x,int k)
{
	int res=0,jzt=1;
	while(x)res+=jzt*(x%k),x/=k,jzt*=10;
	return res;
}
int main()
{
	cin>>n;
	Fu(i,1,n-1)
	{
		Fu(j,1,n-1)
		cout<<turn(i*j,n)<<" ";
		cout<<endl;
	}
	return 0;
}
//BY Segment_Tree_Juruo (2020严誉沣)

```

---

## 作者：封禁用户 (赞：0)

题目传送门：[CF39H Multiplication Table](https://www.luogu.com.cn/problem/CF39H)

题目大意：求k进制下的乘法表。

**解决：** 输入$k$，直接两个循环输出$k$进制的$i\times j$。

$Code:$

```cpp
#include<cstdio>
using namespace std;
inline int read(){
   long long s=0;bool w=1;char ch=getchar();
   while(ch<'0' || ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0' && ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int k;
int zh(int a){//进制转换
    int x=0,y=0,z[1005]={0};
    while(a>0){
        z[++y]=a%k;
        a/=k;
    }
    for(int i=y;i>=1;i--)//倒着输出
        x=x*10+z[i];
    return x;
}
int main(){
    k=read();
    for(int i=1;i<k;i++){
        for(int j=1;j<k;j++)
            printf("%d ",zh(i*j));//输出k进制的i*j
        printf("\n");
    }
    return 0;
}
```


---

## 作者：Tune_ (赞：0)

看了各位大佬的题解，发现没有像我这么暴力的。。。

反正数据不大，直接循环~

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int k,a[11][11]={0};
	cin>>k;
	for(int i=1;i<k;i++)
		a[i][1]=a[1][i]=i;
	if(k==10)//省点时间QAQ
	{
		for(int i=1;i<k;i++)
		{
			for(int j=1;j<k;j++)
			{
				if(i==1||j==1)
				{
					cout<<a[i][j]<<" ";
					continue;
				}
				cout<<a[i][1]*a[1][j]<<" ";
			}
			cout<<endl;
		}
	}
	else
	{
		for(int i=1;i<k;i++)
		{
			for(int j=1;j<k;j++)
			{
				if(i==1||j==1)//边上直接输出
				{
					cout<<a[i][j]<<" ";
					continue;
				}
				int t=a[i][1]*a[1][j];
				int x=1;
				while(t)//转换进制
				{
					a[i][j]+=(t%k)*x;
					x*=10;//第几位
					t/=k;
				}
				cout<<a[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	return 0;//结束了~~~
}

```
如果喜欢我的代码，就点个赞吧~

---

## 作者：溪水瑶 (赞：0)

## 这题可以枚举出每个i,j 位置的数
>需要用到进制转换
```cpp
int zh(int x){
	long long sum=0,i=0;
	while(x){
		sum=sum+((x%n)*pow(10,i));
		i++;
		x/=n;
	}
	return sum;
}
```
上面是进制转换代码，n表示n进制
将进制转换封装起来，在枚举每个位置，先见第一排和第一列全赋值再进行枚举。
## 以下是整个代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[11][11];
int zh(int x){
	long long sum=0,i=0;
	while(x){
		sum=sum+((x%n)*pow(10,i));
		i++;
		x/=n;
	}
	return sum;
}
int main(){
	cin>>n;
	for(int i=1;i<n;i++)a[1][i]=a[i][1]=i;
	for(int i=2;i<n;i++){
		for(int j=2;j<n;j++){
			a[i][j]=zh(i*j);
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<n;j++)
			cout<<a[i][j]<<" ";
		puts("");
	}
	return 0;
}
```

---

## 作者：_Dominater (赞：0)

### ~~这道题,无非就是普通的进制问题,好简单哦~~ 
# 上函数! ! !
```
int itoa(int s)
{
	int r=0,k=0;//k表示位数-1
	while(s>=1)//用数学方法转换进制
	{
		r+=s%n*pow(10,k);//省略数组
		s/=n;//更新一次s
		k++;//进一位
	}
	return r;为后续代码做铺垫!!!
}
```
### 然后,只需排版即可!
```
for(int i=1;i<=n-1;i++)
    for(int j=1;j<=n-1;j++)
    {
    	cout<<itoa(i*j);
        if(j==n-1) cout<<endl;//判断是否为最后的数
    	else if(j==1&&itoa((j+1)*i)<10)cout<<"  ";//判断每行第一个数是否为两位数
        else if(itoa(i*j)<10&&itoa((j+1)*i)<10) cout<<"  ";//判断下一个数是否为两位数
    	else cout<<" ";//情况都不满足,打一空格
     }
```
# 上完整代码! ! !
```
#include<bits/stdc++.h>
using namespace std;
short n;
int itoa(int s)
{
	int r=0,k=0,x[2];
	while(s>=1)
	{
		r+=s%n*pow(10,k);
		s/=n;
		k++;
	}
	return r; 
}
int main()
{
    cin>>n;
    if(n==10)//特判10进制,免得TLE!!!
        for(int i=1;i<=n-1;i++)
    	    for(int j=1;j<=n-1;j++)
    	    {
    	    	cout<<i*j;
    	    	if(j==n-1) cout<<endl;
    		    else if(j==1&&(j+1)*i<10) cout<<"  ";
    		    else if(i*j<10&&(j+1)*i<10) cout<<"  ";
    		    else cout<<" ";
			}    
    else
        for(int i=1;i<=n-1;i++)
    	    for(int j=1;j<=n-1;j++)
    	    {
    		    cout<<itoa(i*j);
    		    if(j==n-1) cout<<endl;
    		    else if(j==1&&itoa((j+1)*i)<10) cout<<"  ";
    		    else if(itoa(i*j)<10&&itoa((j+1)*i)<10) cout<<"  ";
    		    else cout<<" ";
		    }	     
	return 0;
}
```
数据很小,应该只有9个测试点!
# 怎么样,是不是很简单?




---

## 作者：defense (赞：0)


* 评测：进制转换的练手题
* 方法：进制转换，先将十进制下的表~~打~~算出，然后暴力转换就可以了
* 进制转换有两种写法，这里给出递归，~~(如果再写循环题解就要被拒了)~~
* 代码：
```
#include <cstdio>
#include <cmath>
#define MAX 10
long long change(int num,int HEX,int step){//递归法进制转换
	long long ans=0;
	if(!num){return ans;}
		ans+=(num%HEX)*pow(10,step);
		return ans+change(num/HEX,HEX,step+1);
}
int read(){ 
    int F=1,Num=0; 
    char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-'){F=-1;}ch=getchar();}
    while(ch>='0'&&ch<='9'){ Num=Num*10+ch-'0';ch=getchar();}
    return Num*F;
}
int k;
long long map[MAX][MAX];
int main(){
    k=read();
    for(int i=1;i<k;i++){
    	for(int j=1;j<k;j++){
    		map[i][j]=i*j;
		}
	}
	for(int i=1;i<k;i++){for(int j=1;j<k;j++){map[i][j]=change(map[i][j],k,0);}}
    for(int i=1;i<k;i++){
    	for(int j=1;j<k;j++){
    		printf("%lld ",map[i][j]);
		}
		printf("\n");
	}	   
	return 0;
}

```


---

## 作者：__Unknown (赞：0)

### 这个题目也不是很难哈，我还是来发的暴力题解
### 我们举4为例，先列出十进制下的乘法表
```
1  2  3 
1  2  3
2 10 12
3 12 21
```

### 然后把它转化为四进制


```
2  4  6 
3  6  9 
```

### 最后输出即可！（注意了要向右对齐，且乘法表中在n进制下不可能出现三位数（毕竟最多就一位数乘一位数），那么用printf("%2d",XX)输出就好了）
## ~~废话少说，放码过来~~

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n,result[15][15];
int turn(int x){
    int ans=0,cnt=1,ans1;
    while(x!=0){
        int m;
        m=x%n;
        m=m*cnt;
        cnt*=10;
        ans+=m;
        x/=n;
    }
    return ans;
}
int main()
{
    cin>>n;
    for(int i=0;i<n-1;i++){
        result[0][i] = i+1;
        result[i][0] = i+1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            result[i][j] = (i+1)*(j+1);
            result[i][j] = turn(result[i][j]);
        }
    }	
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            if(!j)
            printf("%d",result[i][j]);
            else
            printf("%2d",result[i][j]);
            cout<<" \n"[j == n-2];
        }
    }
    return 0;
}
```



---

