# Flag

## 题目描述

根据一项新的 ISO 标准，每一个国家的国旗应该是一个 $n\times m$ 的格子场，其中每个格子最多有 $10$ 种不同的颜色。并且国旗应该有条纹：旗帜的每一行应包含相同颜色的方块，相邻的行的颜色应该是不同的。Berland 政府要求你找出他们的国旗是否符合新的 ISO 标准。

## 样例 #1

### 输入

```
3 3
000
111
222
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
3 3
000
000
111
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
3 3
000
111
002
```

### 输出

```
NO
```

# 题解

## 作者：Siyuan (赞：10)

各位大佬似乎都用O(n\*m)的空间复杂度诶！于是本蒟蒻来发一个O(1)的空间题解！

## 本题思路

1. 将该行首位字符读入，如果接下来的字符与其不同则直接输出“NO”并退出程序。

2. 此时该行字符相同，上一行字符也保证了相同。于是将该行字符与上一行字符比较，如果不同则直接输出“NO”并退出程序。

3. 最后如果满足所有条件，则输出“YES”。

上代码：（注释不写了吧……）
```
//luogu-siyuan
#include<cstdio>
using namespace std;
int n,m;
char f,last=' ';     //last初始化，保证第一次比较上一行时的结果一定为false
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;i++)
	{
		f=getchar();
		while(f<'0'||f>'9')  f=getchar();
		for(register int j=2;j<=m;j++)
		{
			char t=getchar();
			if(t!=f) {printf("NO");return 0;}
		}
		if(last==f){printf("NO");return 0;}
		last=f;
	}
	printf("YES");
	return 0;			
}
```


---

## 作者：xiayifei (赞：4)

### CF16A【FLAG】题解
[题目链接](https://www.luogu.com.cn/problem/CF16A)
#### 这道题题意十分简单
##### ~~我才不会告诉你我做了很久~~



------------
**一些本蒟蒻做题时遇到的问题**
-  _输入的数字不带空格，因此要用 char类型的数组_
-  _代码中我用到的用来标记上一行颜色和这一行颜色的变量，最后一定要 last=now_

**这么聪明的你们肯定不会犯和我一样的错误的对不对**

上代码


------------
**思路都在注释里了**





```cpp
#include<bits/stdc++.h>//万能头我的最爱
using namespace std;
int last=10,now;//这里的last是上一行的颜色，now也就是现在这行的颜色
char a[105][105];//接上一行，因为题目中说旗帜有0~9 十种颜色，将last初始化为10，就不会有问题
int n,m;
int main()
{
	//freopen("***.in","r",stdin);
	//freopen("***.out","w",stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];//以上输入
	for(int i=1;i<=n;i++){
		now=a[i][1];//将本行的颜色设为这一行的第一个数字
		if(now==last)//如果此行颜色和上一行相同就直接输出并返回
		{
			cout<<"NO"<<endl;
			return 0;//不够华丽的结束
		}//这边不用担心第一个数字与本行其他数字不同，因为那样也是不合法的
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]!=now)//这边再判断这一行数字是否一致
			{
				cout<<"NO"<<endl;
				return 0;//不够华丽的结束
			}
		}
		last=now;//千万别忘了即将搜索下一行时要把现在的颜色变成 last
	}
	cout<<"YES"<<endl;//活到最后的才是合法的！

 	return 0;//华丽地结束
}

```


------------
### ~~一点闲话~~
这是本蒟蒻的第一篇题解

望大神们多多关照! 

( ^_^ )/~~拜拜


---

## 作者：_Qer (赞：4)

本题难度不大，模拟一遍检查旗子的过程即可

检查每一行是否都是同一个字符

检查所有相邻行的第一个字符是否是相等的

如果检查都合法了，那么输出"YES",否则输出"NO"

```cpp
#include<iostream>
using namespace std;
int n,m;//旗帜的长和宽
char flag[110][110];//存旗帜每个点
int main(){
    cin>>n>>m;
    for(int i=0;i<n;++i){//一重循环，每次输入一行
        cin>>flag[i];
    }
    for(int i=0;i<n;++i){//循环每一行
        if(i!=n-1&&flag[i][0]==flag[i+1][0]){
            cout<<"NO";//如果这不是最后一行且它和下一行开头一样
            return 0;//直接结束，免得输出多个结果，下同
        }
        for(int j=0;j<m;++j){
            if(flag[i][j]!=flag[i][0]){//如果某一行出现了多种颜色
                cout<<"NO";
                return 0;
            }
        }
    }
    cout<<"YES";//此时的旗帜一定是合格的
    return 0;
}
```

---

## 作者：Tarensev (赞：3)

~~看见没有pascal的，赶紧来一发。~~

这是一道模拟题，我们需要按照题意来模拟。

由于数字之间没有空格，我们需要用字符来读入。

看了楼上的题解之后，我认为没必要把字符转化为数字，每个ascii码都是一样的。

我的思路是：如果第一个格子已经被涂了，就要判断是否相等，第一行已经被涂了，就得判断其他行与上一行是否不同。

这里贴代码

```pascal
var a:array[1..100,1..100] of char;
    i,n,j,m:longint;
begin
 readln(n,m);
 for i:=1 to n do
  for j:=1 to m do
   read(a[i,j]);
 for i:=1 to n do
  for j:=1 to m do
   begin
    if j>1 then
	 if a[i,j]<>a[i,j-1] then{字符会按照ascii码直接比较}
	  begin
	   writeln('no');
	   exit;{只要有一处地方不同，就意味着flag不标准，所以这样可以节省时间，还防止重复输出}
	  end;
	if i>1 then
	 if a[i,j]=a[i-1,j] then
	  begin
	   writeln('no');
	   exit;
	  end;
   end;
 writeln('yes');{此时不用判断yes or no，因为已经排除掉no的存在了}
end.
```
~~看在码字那么辛苦的份上，帮我审核通过吧~~

这是蒟蒻发表的第一篇题解，有不好的请提出意见，有时候我可能会遗忘一些细节，请见谅

---

## 作者：Mint_Flipped (赞：2)

### **这道比较水，我们只要判断所有行的第一个是否满足相邻颜色不同，和每一行是否满足颜色都相同。**
### **那么代码如下：**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n,m;
    char s[105][105];
    cin>>n>>m;
    for(int i=0; i<n; ++i)
        cin>>s[i];
    for(int i=0; i<n; ++i)
    {
        int te=s[i][0];  //取每行的第一个
        if(te==s[i+1][0]) //与下一行第一个进行比较
        {
            cout<<"NO"<<endl;
            goto bye;   //使用goto语句跳出，比较方便
        }
        for(int j=1; j<m; ++j)
        {
            if(te!=s[i][j]) //与每行的其他元素进行比较
            {  
                cout<<"NO"<<endl;
                goto bye;
            }
        }
    }
    cout<<"YES"<<endl;
bye:  
    return 0;
}
```



---

## 作者：Lolierl (赞：1)

这题较为简单，按照题意模拟即可。


```cpp
#include<iostream>
using namespace std;

int main()
{
    int n,m;
    cin>>n>>m;
    int a[n+1][m+1];//定义
    
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            char t;
            cin>>t;
            a[i][j]=t-48;//按照字符读入并存储。
        }
    
    bool f=true;
    for(int i=1;i<=n;i++)
        for(int j=2;j<=m;j++)
            if(a[i][j]!=a[i][1]){f=false;break;}//第一次判断，如   果同一行颜色不一就输出no
    
    if(!f){cout<<"NO";return 0;}
    for(int i=2;i<=n;i++)
        if(a[i][1]==a[i-1][1]){f=false;break;} //第二次判断，相邻两行颜色一样就输出no，由于前面判断过同一行颜色一样，所以只需比较第一个数即可。
    if(!f){cout<<"NO";return 0;}
    
    cout<<"YES";//输出
    return 0;
}
```

---

## 作者：loi_hjh (赞：0)

# 天生爱暴力

附上代码：

```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,a[101][101];
char x;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>x;//读入 
			a[i][j]=x-'0';
		}
	for(int i=1;i<=n;i++){
		if(i!=1) if(a[i][1]==a[i-1][1]){//第i行中有没有不一样的数 
				 	printf("NO");
				 	return ~~(0-0);
				 }
		for(int j=2;j<=m;j++)
			if(a[i][j]!=a[i][j-1]){//每行的第一个相不相同 
				printf("NO");//这里不需要必要每一行除了第一个是否与上下一样，因为他们本来就和行首的一样 
				return ~~(0-0);
			}
	}
	printf("YES");
	return ~~(0-0);
}
```

---

## 作者：zhangyuhan (赞：0)

还没有用字符串数组做的，来一波~~

字符串数组在每行的比较中比较方便。

此题重在模拟，并没什么难点，直接上代码（内有注释）

```cpp
#include<iostream>
#include<string>
using namespace std;
string str[110];
int n,m;
bool hang(int a)//判断该行有没有重复的颜色 
{
	for(int i=1;i<m;i++)
	{
		if(str[a][i]!=str[a][i-1])
			return false;
	}
	return true;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>str[i];
	if(!hang(1))//第一行不能忘判断 
	{
		cout<<"NO";
		return 0;//强制结束程序，下同 
	}
	for(int i=2;i<=n;i++)
	{
		if(!hang(i))
		{
			cout<<"NO";
			return 0;		
		}
		if(str[i]==str[i-1])//判断每两行是否有重复的字符 
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}
```

---

