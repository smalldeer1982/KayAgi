# Appleman and Easy Task

## 题目描述

Toastman came up with a very easy task. He gives it to Appleman, but Appleman doesn't know how to solve it. Can you help him?

Given a $ n×n $ checkerboard. Each cell of the board has either character 'x', or character 'o'. Is it true that each cell of the board has even number of adjacent cells with 'o'? Two cells of the board are adjacent if they share a side.

## 样例 #1

### 输入

```
3
xxo
xox
oxx
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
xxxo
xoxo
oxox
xxxx
```

### 输出

```
NO
```

# 题解

## 作者：xiaozeyu (赞：2)

# 纯暴力题！

**虽然已经有人交了三重循坏的暴力题，但可以找规律，更快暴力！（万一下次遇到更大的数据的话）**

**先看数据：**

```c
3
xxo
xox
oxx   YES
4
xxxo
xoxo
oxox
xxxx  NO
```

**第一反应，这是对称吗？？**

**发现似乎对称的可以**

**多举举例子，其实每个“o”周围四个字符中都有偶数个“x”的话，将其倒置后与原图一直一样。**
```c
#include<bits/stdc++.h>
using namespace std;
int n;
string s1,s2,s;//s为每次输入的，s1为原图,s2为处理后
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>s;
		s1+=s;//把s的加到s1上
	}
	s2=s1;//s2处理前为s1
	reverse(s2.begin(),s2.end());//将s2头尾倒置
	if(s2==s1) cout<<"YES";//判断
	else cout<<"NO";
}
```


---

## 作者：Bla_Bla (赞：1)

## 这么一道水题，不暴力一波都对不起这么水的题目！

中心思想：遍历全图，判断上下左右是否为 $o$，累加判断是否为偶数，AC。

这里要注意：0也是偶数！（~~我才不会告诉你我开始忘了然后样例一 一脸懵逼~~

然后我们就得到了代码：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,i,j,x,m=0;
	char a[105][105];//100*100的范围直接105,绝对够
	cin>>n;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			cin>>a[i][j];
		}
	}//枯燥读入 
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
				if(a[i-1][j]=='o')m++;
				if(a[i][j-1]=='o')m++;
				if(a[i][j+1]=='o')m++;//四个方向判断
				if(a[i+1][j]=='o')m++;//因为是从1开始记的,所以就不用判边,不会越界
				if(m%2!=0)
				{
					cout<<"NO";
					return 0;
				}//出现奇数就可以直接结束了
				m=0;
		}
	}//枯燥循环 
	cout<<"YES";
	return 0;//枯燥水题
}
```


---

## 作者：西宋太祖 (赞：1)

这一题的意思是判断每个点四周都有偶数个"o"。**但是由于题目数据较弱，所以简单的搜索就能通过。**

我们可以把这个代码分成两部分，分别是**读入数据**和**判断**。

#### 第一部分：读入数据
我们可以用一个字符型的二位数组来存储数据。
```cpp
int const N=100+5;
char a[N][N];
```
再用双重循环读入数据。
```cpp
for(i=1;i<=n;i++)//为了防止在下面的程序中出现下标为-1的情况，所以从1开始。
	for(j=1;j<=n;j++)
		cin>>a[i][j];
```
#### 第二部分：判断
我们可以先用双重循环枚举。
```cpp
for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
```
接着我们上下左右分别判断。
```cpp
if(a[i-1][j]=='o'&&i!=0)//上
    s++;
if(a[i+1][j]=='o'&&i!=n+1)//下
    s++;
if(a[i][j-1]=='o'&&j!=0)//左
    s++;
if(a[i][j+1]=='o'&&j!=n+1)//右
    s++;
```
### AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=100+5;
char a[N][N];
int n;
bool x()//为了使文章结构更清晰，所以使用了函数来进行判断。
{
    int i,j,s=0; 
	for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        {
            s=0; 
            if(a[i-1][j]=='o'&&i!=0)
                s++;
            if(a[i+1][j]=='o'&&i!=n+1)
                s++;
            if(a[i][j-1]=='o'&&j!=0)
                s++;
            if(a[i][j+1]=='o'&&j!=n+1)
                s++;
            if(s%2!=0)
                return false;
        }
    return true;   
}
int main()
{
    int i,j;
    cin>>n;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            cin>>a[i][j];
    if(x()==true)
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
    return 0;
}
```

---

## 作者：SKTelecomT1_Faker (赞：0)

先说思路：因为 $n\le 100$，所以直接暴力。

输入图之后逐位判断，循环里设一个累加器如果周围有奇数个 o 那就输出 `NO` 之后退出程序，最后输出 `YES`表示符合要求。
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int main()
{
    char a[101][101];
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++) cin>>a[i][j];//输入图
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)//暴力开始
    {
        int ans=0;//累加器初始化
        if(a[i][j-1]=='o'&&j!=0) ans++;
        if(a[i][j+1]=='o'&&j!=n-1) ans++;
        if(a[i-1][j]=='o'&&i!=0) ans++;
        if(a[i+1][j]=='o'&&i!=n-1) ans++;//判断+边界去除
        if(ans%2!=0)//不符合条件
        {
            cout<<"NO"<<endl;//输出NO
            return 0;//退出
        }
    }//没退出说明符合条件
    cout<<"YES"<<endl;//输出YES
    return 0;
}
```

---

## 作者：Protons (赞：0)

## 首先，这个题的翻译错了

英文原文的意思是每个点周围都有偶数个‘o’，但翻译翻译成了每个‘o’的周围有偶数个‘x’

然后……这题就很简单了，直接无脑暴力(毫无优化）

最后提醒大家一下，如果要用scanf("%c",&o);进行输入，请在输入二维数组前加一个o=getchar()以输入换行符，否则读入时会先读入换行符；另外，为了避免读入换行符，二维数组的列还要加一列

以下是~~高清无码~~的代码：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int a[105][105];
int n,x[4]={0,1,-1,0},y[4]={1,0,0,-1};
int main()
{
	scanf("%d",&n);
	char o;
	o=getchar();
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n+1;j++)
	{
		scanf("%c",&o);
		if(o=='x')a[i][j]=0;
		if(o=='o')a[i][j]=1;
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		int cnt=0;
		for(int k=0;k<4;k++)
		if(i+x[k]>0&&j+y[k]>0&&i+x[k]<=n&&j+y[k]<=n&&a[i+x[k]][j+y[k]]==1)cnt++;
		if(cnt==0)continue;
		if(cnt&1)
		{
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}
```

---

