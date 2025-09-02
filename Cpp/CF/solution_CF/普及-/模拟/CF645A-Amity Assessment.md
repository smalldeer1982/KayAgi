# Amity Assessment

## 题目描述

Bessie the cow and her best friend Elsie each received a sliding puzzle on Pi Day. Their puzzles consist of a $ 2×2 $ grid and three tiles labeled 'A', 'B', and 'C'. The three tiles sit on top of the grid, leaving one grid cell empty. To make a move, Bessie or Elsie can slide a tile adjacent to the empty cell into the empty cell as shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF645A/dea7f0e6f6bd920a326a8e3da7a33cbf3667be5d.png)In order to determine if they are truly Best Friends For Life (BFFLs), Bessie and Elsie would like to know if there exists a sequence of moves that takes their puzzles to the same configuration (moves can be performed in both puzzles). Two puzzles are considered to be in the same configuration if each tile is on top of the same grid cell in both puzzles. Since the tiles are labeled with letters, rotations and reflections are not allowed.

## 说明/提示

The solution to the first sample is described by the image. All Bessie needs to do is slide her 'A' tile down.

In the second sample, the two puzzles can never be in the same configuration. Perhaps Bessie and Elsie are not meant to be friends after all...

## 样例 #1

### 输入

```
AB
XC
XB
AC
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
AB
XC
AC
BX
```

### 输出

```
NO
```

# 题解

## 作者：MZY666 (赞：10)

[原题传送门](https://www.luogu.com.cn/problem/CF645A)。
[在窝的博客中食用更佳](https://www.luogu.com.cn/blog/MZY666/solution-cf645a)。

### 【 题意翻译 + 概括 】

（目前还没有翻译）

输入两组数据，每一组数据有两行，每行两个字符。

每组数据中的字符只可能是 $A$，$B$，$C$，$X$。其中 $X$ 表示为空。

求能否通过移动第一组数据中的 $A$，$B$，$C$ 使得与第二组数据相同。

能则输出 `YES`，否则输出 `NO` 。

移动规则：每次移动只能把 $A$，$B$，$C$ 移动到相邻且为空的格子上。

### 【 思路 】

用一个外层循环多循环几次，每次循环都按**同一种**方法去改变第一组数据。

每次改变后都判断能否和第二组数据完全相同。若相同则输出 `YES` 并终止程序。随后在循环外输出 `NO` 即可。

其它细节见代码吧。

### 【 代码实现 + 注释 】

```cpp
#include<bits/stdc++.h>//万能头文件好
using namespace std;
#define ll long long//个人习惯
char a[5],b[5];//数组最好放外面
bool s(){//移动第一组数据+判断的bool类型函数
	bool flag;//定义返回值
	int x,i;//x用于记录空的那一位的数组下标，i为循环变量
	if(a[1]==b[1]&&a[2]==b[2]&&a[3]==b[3]&&a[4]==b[4])
		flag=true;
	//如果和第二组数据完全相同，则返回值为真，但还得移动，不能立刻退出
	else flag=false;//否则返回值为假
	for(x=1;x<=4;x++){
		if(a[x]=='X')break;//找到空的那一位
	}
	if(x==1){
		a[1]=a[2];//移动
		a[2]='X';//移动
	}
	if(x==2){
		a[2]=a[4];//移动
		a[4]='X';//移动
	}
	if(x==3){
		a[3]=a[1];//移动
		a[1]='X';//移动
	}
	if(x==4){
		a[4]=a[3];//移动
		a[3]='X';//移动
	}
	return flag;//返回此函数值
}
int main(){//主函数
	char sp;//过滤空格
	scanf("%c%c%c%c%c%c%c%c%c%c%c",&a[1],&a[2],&sp,&a[3],&a[4],&sp,&b[1],&b[2],&sp,&b[3],&b[4]);
	//输入（懒得用循环）
	for(int i=1;i<=16;i++){//开始循环移动第一组数据+判断
		if(s()){//如果函数返回值为真
			printf("YES\n");//输出YES，换行是个好习惯
			return 0;//提前结束程序
		}
	}
	printf("NO\n");//如果做不到则输出NO
	return 0;//over~
}
```

另：作者已自愿禁言一年，因此有建议请私信，否则**无法**回复您哦！

完结撒花~（疯狂暗示๑乛◡乛๑

---

## 作者：小之森夏音 (赞：1)

看到没人写 Python 题解，本蒟蒻来写一篇。

## 题目分析
思路很简单，只需要模拟按照同一方向（如逆时针）滑动方格一中的方块，并在每次滑动后判断方格一与方格二是否相同，若相同则输出 `YES` ，否则继续滑动。若滑动次数达到上限（本篇题解的代码中上限设置为 $20$ ）后仍未使方格一与方格二相同，则输出 `NO` 。

写成代码十分简洁，只有九行。

## 代码
```python
a,b,c=list(input()+input()),list(input()+input()),0
while c<20 and (a[0]!=b[0] or a[1]!=b[1] or a[2]!=b[2] or a[3]!=b[3]):
	a0,b0=a.index("X"),b.index("X")
	if a0==0:a[0],a[1]=a[1],a[0]
	if a0==1:a[1],a[3]=a[3],a[1]
	if a0==2:a[0],a[2]=a[2],a[0]
	if a0==3:a[2],a[3]=a[3],a[2]
	c+=1
print("YES" if c<20 else "NO")
```

---

## 作者：皮卡丘最萌 (赞：1)

这道题目由于数据范围只有$2\times2$，所以可以列举出所有的情况。

先假设这个矩阵为：

$x_1$  $x_2$ 

$x_3$  $x_4$ 

其中必定有一个字母为$X$,我们把他记为$0$。

为了移动方便，我们先把$0$移到矩阵的右下角：

$x_1$  $x_2$ 

$x_3$  $0$ 

接下来就可以移动出$12$种不同的图形：

第$1$种：

$x_1$ $x_2$

$x_3$ $0$    

第$2$种：

$x_1$ $x_2$

$0$ $x_3$

第$3$种：

$x_1$ $0$

$x_3$ $x_2$

第$4$种：

$0$ $x_2$

$x_1$ $x_3$

第$5$种：

$0$ $x_1$

$x_3$ $x_2$

第$6$种：

$x_2$ $0$

$x_1$ $x_3$

第$7$种：

$x_3$ $x_1$

$0$ $x_2$

第$8$种：

$x_2$ $x_3$ 

$x_1$ $0$

第$9$种：

$x_3$ $x_1$

$x_2$ $0$

第$10$种：

$x_2$ $x_3$

$0$ $x_1$

第$11$种：

$x_3$ $0$

$x_2$ $x_1$

第$12$种：

$0$ $x_3$

$x_2$ $x_1$

接下来就只需要判断这$12$种方法中是否有$1$种符合题意即可。

代码:
```pascal
var a,b,c:array[1..4] of char;
function pd:boolean;
begin
if (a[1]=b[1])and(a[2]=b[2])and(a[3]=b[3])and(a[4]=b[4]) then exit(true);
if (a[1]=b[1])and(a[2]=b[2])and(a[4]=b[3])and(a[3]=b[4]) then exit(true);
if (a[1]=b[1])and(a[4]=b[2])and(a[3]=b[3])and(a[2]=b[4]) then exit(true);
if (a[4]=b[1])and(a[2]=b[2])and(a[1]=b[3])and(a[3]=b[4]) then exit(true);
if (a[4]=b[1])and(a[1]=b[2])and(a[3]=b[3])and(a[2]=b[4]) then exit(true);
if (a[2]=b[1])and(a[4]=b[2])and(a[1]=b[3])and(a[3]=b[4]) then exit(true);
if (a[3]=b[1])and(a[1]=b[2])and(a[4]=b[3])and(a[2]=b[4]) then exit(true);
if (a[2]=b[1])and(a[3]=b[2])and(a[1]=b[3])and(a[4]=b[4]) then exit(true);
if (a[3]=b[1])and(a[1]=b[2])and(a[2]=b[3])and(a[4]=b[4]) then exit(true);
if (a[2]=b[1])and(a[3]=b[2])and(a[4]=b[3])and(a[1]=b[4]) then exit(true);
if (a[3]=b[1])and(a[4]=b[2])and(a[2]=b[3])and(a[1]=b[4]) then exit(true);
if (a[4]=b[1])and(a[3]=b[2])and(a[2]=b[3])and(a[1]=b[4]) then exit(true);       
                 //任意1种符合就输出YES
exit(false);         //都不符合输出NO
end;           //判断是否可行

procedure change;
begin
if a[1]='X' then
  begin
  c[1]:=a[3]; c[2]:=a[2]; c[3]:=a[4]; c[4]:=a[1];
  a:=c; exit;
  end;                   //‘x’在左上角
if a[2]='X' then
  begin
  c[1]:=a[1]; c[2]:=a[4]; c[3]:=a[3]; c[4]:=a[2];
  a:=c; exit;
  end;                   //‘x’在右上角
if a[3]='X' then
  begin
  c[1]:=a[1]; c[2]:=a[2]; c[3]:=a[4]; c[4]:=a[3];
  a:=c; exit;
  end;                   //‘x’在左下角
if a[4]='X' then exit;
end;                   //把‘X’移到右下角

begin
readln(a[1],a[2]);
readln(a[3],a[4]);
change;             //把‘X’移到右下角
readln(b[1],b[2]);
readln(b[3],b[4]);
if pd then writeln('YES') else writeln('NO');
                       //输出答案
end.
```


---

## 作者：liuyifan (赞：1)

## 2*2的八数码问题
本题不需要搜索，直接判断顺序就可以了

注意当n为奇数时直接特判

更多说明间代码注释

code:
```cpp
#include<bits/stdc++.h>//万能头文件
#define reg register//register卡常
#define ll long long
using namespace std;
string a1,a2,b1,b2,s;//string的直接定义
inline int f(reg string s1,reg string s2)//判断两两间的可行性
{
    reg int tmp=0,ansa,ansc;
    swap(s2[0],s2[1]);//预处理一下（题目中的变换方式）
    s=s1+s2;//转换为一维处理问题
    for(reg int i=0;i<=3;i++)//注意string下表从0开始
	{
        if(s[i]=='X')continue;
        if(s[i]=='A')ansa=tmp;
        if(s[i]=='C')ansc=tmp;//依次枚举
        tmp++;
    }
    return ansc==ansa+1||ansa==2&&ansc==0;//注意这里的优先级问题,&&和||为同级运算,按照左右顺序
}
int main()
{
    cin>>a1>>a2>>b1>>b2;//输入排列方式
	puts(f(a1,a2)==f(b1,b2)?"YES":"NO");//当f(a1,a2)==f(b1,b2)时输出YES，反之NO
	return 0;
}
```


---

## 作者：cyrxdzj (赞：0)

### 一、思路

本题可以采用暴力模拟。

首先，先找出初始的空格。

然后，重复以下判断 $12$ 遍：

- 如果空格在左上角，则将左下角的方格往上移；

- 如果空格在左下角，则将右下角的方格往左移；

- 如果空格在右下角，则将右上角的方格往下移；

- 如果空格在右上角，则将左上角的空格往右移。

每一步过后，判断两个方阵是否一致。如果一致，直接输出 `YES`。

如果移动了 $12$ 次，还没有一致的情况，则输出 `NO`。

移动 $12$ 次过后，方阵恰好形成一个循环。所以只用移动 $12$ 次。

### 二、完整代码

```cpp
#include<cstdio>
using namespace std;
char graph1[3][3],graph2[3][3],oper_graph[3][3];
int space_x,space_y;
bool equal(char a[3][3],char b[3][3])//判断方阵是否一致。
{
	for(int i=1;i<=2;i++)
	{
		for(int j=1;j<=2;j++)
		{
			if(a[i][j]!=b[i][j])
			{
				return false;
			}
		}
	}
	return true;
}
int main()
{
	for(int i=1;i<=2;i++)
	{
		char str[3];
		scanf("%s",&str);
		for(int j=1;j<=2;j++)
		{
			graph1[i][j]=str[j-1];
			if(graph1[i][j]=='X')//获取空格位置。
			{
				space_x=i;
				space_y=j;
			}
		}
	}
	for(int i=1;i<=2;i++)
	{
		char str[3];
		scanf("%s",&str);
		for(int j=1;j<=2;j++)
		{
			graph2[i][j]=str[j-1];
		}
	}
	for(int i=1;i<=2;i++)
	{
		for(int j=1;j<=2;j++)
		{
			oper_graph[i][j]=graph1[i][j];
		}
	}
	for(int i=1;i<=12;i++)//移动并判断。
	{
		if(space_x==1&&space_y==1)
		{
			oper_graph[1][1]=oper_graph[2][1];
			oper_graph[2][1]='X';
			if(equal(oper_graph,graph2))
			{
				printf("YES\n");
				return 0;
			}
			space_x=2;
		}
		else if(space_x==2&&space_y==1)
		{
			oper_graph[2][1]=oper_graph[2][2];
			oper_graph[2][2]='X';
			if(equal(oper_graph,graph2))
			{
				printf("YES\n");
				return 0;
			}
			space_y=2;
		}
		else if(space_x==2&&space_y==2)
		{
			oper_graph[2][2]=oper_graph[1][2];
			oper_graph[1][2]='X';
			if(equal(oper_graph,graph2))
			{
				printf("YES\n");
				return 0;
			}
			space_x=1;
		}
		else if(space_x==1&&space_y==2)
		{
			oper_graph[1][2]=oper_graph[1][1];
			oper_graph[1][1]='X';
			if(equal(oper_graph,graph2))
			{
				printf("YES\n");
				return 0;
			}
			space_y=1;
		}
	}
	printf("NO\n");
	return 0;//完结撒花！
}

```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：SegTre (赞：0)

# 思路
发现一个重要的规律：一个拼图怎么移，都不会改变其顺时针（或逆时针）顺序。比如题目中这张拼图：不论怎么移动，其顺时针顺序都是 $A$ $B$ $C$

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF645A/dea7f0e6f6bd920a326a8e3da7a33cbf3667be5d.png)

这一点很容易证明，一块拼图有顺时针移动、逆时针移动两种可能，逆时针移动（以上图为例，移动了 $A$ 拼图）会使原来拼图顺序中跳开的空格变成移动的那个拼图（$A$），而这块拼图（$A$）之前的顺序不变（$BC$），之后只多了一个空格不影响顺序。顺时针同理。

所以我们只判断两个拼图的顺时针顺序是否为循环同构串即可。

# Code

读入顺序 $0123$ ，顺时针（左上开始）顺序就是 $0132$ 。代码配个图，方便理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/dd0q7hxy.png)

```cpp
#include<cstdio>
#include<cctype>
using namespace std;
char s[4],s1[3],s2[3];
int main() {
	int p=0;
	for(int i=0;i<4;++i) while(!isalpha(s[i]=getchar())); //按照 0123 顺序读入 
	if(s[0]!='X') s1[p++]=s[0];
	if(s[1]!='X') s1[p++]=s[1];
	if(s[3]!='X') s1[p++]=s[3];
	if(s[2]!='X') s1[p++]=s[2]; // s1 存第一张图顺时针顺序，X 跳开 
	p=0;
	for(int i=0;i<4;++i) while(!isalpha(s[i]=getchar()));
	if(s[0]!='X') s2[p++]=s[0];
	if(s[1]!='X') s2[p++]=s[1];
	if(s[3]!='X') s2[p++]=s[3];
	if(s[2]!='X') s2[p++]=s[2];
	p=0;
	while(s1[0]!=s2[p]) p++;
	for(int i=0;i<3;++i)
		if(s1[i]!=s2[(i+p)%3]) { // 顺时针排列 0 ~ 2 ，2 过后还是 0 ——模 3 即可实现 
			printf("NO");
			return 0;
		}
	printf("YES");
	return 0;
}
```



---

## 作者：Farkas_W (赞：0)

$$\text{题目大意}$$

$\quad$有一个 2$\times$2 的网格，每个格子中是字母 $A,B,C,X$ 中的一个；

$\quad$你可以进行若干次操作：每次操作中，你选择含字母 $X$ 的格子和一个与之相邻的格子交换；

$\quad$给定网格的初始状态和最终状态，问是否可以通过有限次操作从初始状态到达最终状态？

$$\text{思路}$$

$\quad$根据多年~~划水~~经验，只需要判断三个字母 $A,B,C$ 之间的位置关系即可，因为可以和含 $X$ 的格子交换，所以忽略这个格子，考虑顺时针顺序即可。

$\quad$可以[玩玩Windows上的小游戏](https://jingyan.baidu.com/article/54b6b9c0074abc6d593b4746.html)，这个叫图片拼图板，找找规律(一本正经)。

![](https://cdn.luogu.com.cn/upload/image_hosting/34zl2b0n.png)

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define re register int
#define il inline
using namespace std;
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
il int min(int x,int y){return x<y?x:y;}
int t1,t2;
char a[4],b[4];
signed main()
{
	for(re i=1;i<=4;i++)
	{
		cin>>a[i-1];
		if(a[i-1]=='A')t1=i;//找出A的位置
	}
	for(re i=1;i<=4;i++)
	{
		cin>>b[i-1];
		if(b[i-1]=='A')t2=i;
	}
	int x,y;//判断顺时针方向A的下一个字母
	if(t1==1)x=a[1]!='X'?a[1]:a[3];
	else if(t1==2)x=a[3]!='X'?a[3]:a[2];
	else if(t1==3)x=a[0]!='X'?a[0]:a[1];
	else x=a[2]!='X'?a[2]:a[0];
	if(t2==1)y=b[1]!='X'?b[1]:b[3];
	else if(t2==2)y=b[3]!='X'?b[3]:b[2];
	else if(t2==3)y=b[0]!='X'?b[0]:b[1];
	else y=b[2]!='X'?b[2]:b[0];
	if(x==y)puts("YES");else puts("NO");
	return 0;
}
```
$$\text{后话}$$

$\quad$本题的双倍经验：[P7724 远古档案馆（Ancient Archive）](https://www.luogu.com.cn/problem/P7724)

$\quad$我的记录

![](https://cdn.luogu.com.cn/upload/image_hosting/7gfjeamq.png)

---

## 作者：BF_AlphaShoot (赞：0)

这道题我们或许会首先想到列举出每一种情况，但这样太麻烦。这道题还是**有规律可循**。

自己列举几种情况后可以发现，无论初始状态是什么样，无论怎么挪动，在不算 $\mathtt{X}$ 时，顺时针方向上 **$\mathtt{A,B,C}$ 的顺序恒定**。

因此使用数组储存初始顺序，再将其与给出的结果顺序比较，若不一样则输出 $\mathtt{NO}$，否则输出 $\mathtt{YES}$。

这道题还有很多代码实现的细节，将在代码中给出讲解。

View code:
```cpp
#include<bits/stdc++.h>
using namespace std;

#define ri register int

char b[2][2],f[2][2],s[4],s2[4];

signed main(){
	for(ri i=0;i<=1;i++)
		for(ri j=0;j<=1;j++){
			cin>>b[i][j];
			if(b[i][j]<'A'||b[i][j]>'Z')//在使用scanf时会把回车也算上，因此要避免
				cin>>b[i][j];
		}
	
	for(ri i=0;i<=1;i++)
		for(ri j=0;j<=1;j++){
			cin>>f[i][j];
			if(f[i][j]<'A'||f[i][j]>'Z')
				cin>>f[i][j];
		}
	if(b[0][0]=='X')
		s[0]=b[0][1],s[1]=b[1][1],s[2]=b[1][0];
	if(b[1][0]=='X')
		s[0]=b[0][0],s[1]=b[0][1],s[2]=b[1][1];
	if(b[1][1]=='X')
		s[0]=b[1][0],s[1]=b[0][0],s[2]=b[0][1];
	if(b[0][1]=='X')
		s[0]=b[1][1],s[1]=b[1][0],s[2]=b[0][0];
	if(f[0][0]=='X')
		s2[0]=f[0][1],s2[1]=f[1][1],s2[2]=f[1][0];
	if(f[1][0]=='X')
		s2[0]=f[0][0],s2[1]=f[0][1],s2[2]=f[1][1];
	if(f[1][1]=='X')
		s2[0]=f[1][0],s2[1]=f[0][0],s2[2]=f[0][1];
	if(f[0][1]=='X')
		s2[0]=f[1][1],s2[1]=f[1][0],s2[2]=f[0][0];
	s[3]=s[0],s2[3]=s2[0];//数组存储时，最后一位字母的后一位应该存为第一位的字母，构成环
	for(ri i=0;i<=2;i++)
		for(ri j=0;j<=2;j++)
			if(s[i]==s2[j]&&s[i+1]!=s2[j+1]){
				printf("NO");
				return 0;
			}
	printf("YES");
	return 0;
}
```

---

## 作者：_Legacy (赞：0)

#### 分析

我们先看样例：

```
AB
XC
XB
AC
```

这一个样例要是顺时针排列(不算'X’)不难发现因为他们是通过滑动得到的相同结果的方格，所以结果是一样的:

```
ABC BCA
ABC=ABC(A可以调到头上，因为是同样的顺序)
```

所以判断两个方格是否相同只要看顺序是否相同就行了。

#### 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(char ax[4],char bx[4]){//两个顺序字符串
	int t=1,x;
	for(int i=0;i<3;i++){
		t=1;
		for(int j=0;j<3;j++){
			if(i+j>=3) x=i+j-3;//多出来的回到头上
			else x=i+j;
			if(ax[x]!=bx[j]){
				t=0;
			} 
		}
		//实现判断顺序的功能
		if(t) return 1; 
	}
	return 0;
}
int main(){
	char a[4],b[4],ax[4]={' '},bx[4]={' '};
	int len=0;
	cin >> a[0] >> a[1] >> a[3] >> a[2] >> b[0] >> b[1] >> b[3] >> b[2];
	//顺时针输入
	for(int i=0;i<4;i++){
		if(a[i]!='X'){
			ax[len]=a[i];
			len++;
		}
	}
	len=0;
	for(int i=0;i<4;i++){
		if(b[i]!='X'){
			bx[len]=b[i];
			len++;
		}
	}
	//制造顺序字符串
	if(cmp(ax,bx)) cout << "YES";
	else cout << "NO";
}
//CF645A
```

---

