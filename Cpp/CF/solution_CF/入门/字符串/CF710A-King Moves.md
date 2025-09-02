# King Moves

## 题目描述

The only king stands on the standard chess board. You are given his position in format "cd", where $ c $ is the column from 'a' to 'h' and $ d $ is the row from '1' to '8'. Find the number of moves permitted for the king.

Check the king's moves here <a>https://en.wikipedia.org/wiki/King\_(chess)</a>.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF710A/c293477e407dd29c222477fd35652e45e6890a3c.png)King moves from the position e4

## 样例 #1

### 输入

```
e4
```

### 输出

```
8
```

# 题解

## 作者：dingcx (赞：6)

~~本题无疑是一道水题~~

**两种方法**

法一：

一堆if判断，再角上就是3，在边上就是5，在中间就是8。

代码：
```cpp
#include<cstdio>
using namespace std;
int main(){
	char c,d;
	scanf("%c%c",&c,&d);//输入
	if((c=='a'&&(d=='1'||d=='8'))||(c=='h'&&(d=='1'||d=='8'))) printf("3");//角上
	else if(c=='a'||c=='h'||d=='1'||d=='8') printf("5");//边上
	else printf("8");//中间
	return 0;//结束
}
```

法二（不寻常的方法）

**直接打表！**（连if都不用）

开一个8乘8的数组，每个点是几都标上就好了。。。

代码：
```cpp
#include<cstdio>
using namespace std;
int a[8][8]={3,5,5,5,5,5,5,3,
5,8,8,8,8,8,8,5,
5,8,8,8,8,8,8,5,
5,8,8,8,8,8,8,5,
5,8,8,8,8,8,8,5,
5,8,8,8,8,8,8,5,
5,8,8,8,8,8,8,5,
3,5,5,5,5,5,5,3};//打表
int main(){
    char c,d;
	scanf("%c%c",&c,&d);//输入
    printf("%d",a[c-'a'][d-'1']);//注意c要减'a',d要减'1'
    return 0;//华丽结束
}
```

---

## 作者：zhangjiacheng (赞：3)

#### 这么水的题没人发题解？~~还没几个人做出来~~。

#### 来发一波题解。
```pascal
var s:string;a:longint;
begin
  readln(s);//以字符串读入
  val(s[2],a);//把数字读取出来
  if (a>=2)and(a<=7)and(s[1]>='b')and(s[1]<='g')then//如果在内层，则输出8
    writeln(8)
  else if(a=1)and(s[1]='a')then writeln(3)//在边角上，输出3
  else if(a=1)and(s[1]='h')then writeln(3)//在边角上，输出3
  else if(a=8)and(s[1]='a')then writeln(3)//在边角上，输出3
  else if(a=8)and(s[1]='h')then writeln(3)//在边角上，输出3
  else writeln(5);//否则就输出5
end.
```

---

## 作者：Kevin_Zhen (赞：2)

写好方向数组，循环遍历一遍累加上可以访问的格子即可。  
## AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#define rint register int
using namespace std;

string s;
int dx[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
int dy[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
int x1, y1;
bool flag[10][10] = { false };
int ans = 0;

int main() {
	for (rint i = 1; i <= 8; ++i) for (rint j = 1; j <= 8; ++j) flag[i][j] = true; 
	cin >> s;
	x1 = s[0] - 'a' + 1; y1 = s[1] - '0';
	for (rint i = 0; i < 8; ++i) if (flag[x1 + dx[i]][y1 + dy[i]]) ++ans;
	printf("%d", ans);
	return 0;
}
```
## 感谢观赏！

---

## 作者：Valhalla_Is_Calling (赞：2)

## ~~这么弱的题~~居然没人做！

### 还是那句话：把思路搞明白最重要！

这道题的思路就是判断，由于本蒟蒻水平不行，做不到像楼上那样用BFS，所以还是乖乖地判断吧！

一共就只有这么几个情况：角落、最外面的一排和中间的。

对于角落：

```cpp
if(x=='a'&&y==1) cout<<3;
if(x=='a'&&y==8) cout<<3;
if(x=='h'&&y==1) cout<<3;
if(x=='h'&&y==8) cout<<3;
```


对于最外面的一边：

```cpp
if(x=='a'&&y>1&&y<8) cout<<5;
if(x=='h'&&y>1&&y<8) cout<<5;
```

对于普通情况：

```cpp
if(x!='a'&&x!='h'&&y>1&&y<8) cout<<8;
```
完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char x;
int y;
int main()
{
	cin>>x>>y;
	if(x=='a'&&y>1&&y<8) cout<<5;
	if(x=='a'&&y==1) cout<<3;
	if(x=='a'&&y==8) cout<<3;
	if(x=='h'&&y==1) cout<<3;
	if(x=='h'&&y==8) cout<<3;
	if(x=='h'&&y>1&&y<8) cout<<5;
	if(x!='a'&&x!='h'&&y>1&&y<8) cout<<8;
	return 0;
}
```
## 杜绝作弊，请勿抄袭

---

## 作者：我是蒟弱 (赞：1)

## 暴力出奇迹，我不用暴力！小小bfs，增加AC率！

就执行一遍不算bfs的bfs就行了。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int pre[8][2]={{1,0},{0,1},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};//方向数组
char x;
int a,b,tx,ty,ans=0;
int main(){
	cin>>x>>b;//输入
	a=x-'a'+1;//把字母转成数字
	for(register int i=0;i<8;i++){
		tx=a+pre[i][0];//新的x轴坐标
		ty=b+pre[i][1];//新的y轴坐标
		if(tx<1||tx>8||ty<1||ty>8){//越界
			continue;//执行下一次循环
		}
		ans++;//没有continue，ans+1
	}
	printf("%d",ans);//输出答案
	return 0;//结束
} 
```

---

## 作者：FourteenObsidian (赞：1)

CF的水题……

只要暴力模拟就好……

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a,b;
bool f1=0,f2=0;
int main(){
	scanf("%c%c",&a,&b);
	if(a=='h'||a=='a')//在边界
		f1=1;
	if(b=='1'||b=='8')//同上
		f2=1;
	if(f1==1&&f2==1){//如果在角落
		printf("3\n");
		return 0;
	}
	if(f1==1||f2==1){//如果只靠在一边上
		printf("5\n");
		return 0;
	}
	printf("8\n");//不然就在中间
	return 0;		
} 
```

---

## 作者：黯黑の夜 (赞：0)

### 这种题目，只需要判断'a','h','1','8'就好啦

#### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    char a,b;
    cin>>a>>b;
    if(a=='a'&&b=='1'||a=='a'&&b=='8'||a=='h'&&b=='1'||a=='h'&&b=='8')//判断是否在边角上
    printf("3\n");//是就输出3
    else if(b=='1'&&a!='a'&&a!='h'||b=='8'&&a!='a'&&a!='h'||a=='a'&&b!='1'&&b!='8'||a=='h'&&b!='1'&&b!='8')// 判断是否在边缘上&&不再边角上（前面已经判断过了）
    printf("5\n");//是就输出5
    else printf("8\n");//都不是就输出8（在中间）
    return 0;
}
```

其实呢

还有另一种解法

# 打表大法! ! !

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
  int a1[8][8]={{3,5,5,5,5,5,5,3},
  {5,8,8,8,8,8,8,5},
  {5,8,8,8,8,8,8,5},
  {5,8,8,8,8,8,8,5},
  {5,8,8,8,8,8,8,5},
  {5,8,8,8,8,8,8,5},
  {5,8,8,8,8,8,8,5},
  {3,5,5,5,5,5,5,3}};//打表
  char a,b;
  cin>>a>>b;
  printf("%d\n",a1[a-'a'][b-'1']);//注意是b-'1',不是 b-'0'
  return 0;
}
```
---
---
# 别忘了换行! ! !

小声BB:请问char和string和double和float的scanf,printf格式是什么

---

## 作者：土川崇贺 (赞：0)

		这道题只需判断行是否为a或h，列是否为1或8即可。
        奉上代码：
 ```cpp
#include<iostream>
using namespace std;
int main()
{
    char hang,lie;
    int c=8;//计数器
    cin>>hang>>lie;
    if(hang=='a' || hang=='h')//判断行
    {
    	c-=3;
    	if(lie=='1' || lie=='8') //判断列
    	{
    		c-=2;
		}
	}
	else if(lie=='1' || lie=='8') //判断列
	{
		c-=3;
		if(hang=='a' || hang=='h')//判断行
		{
			c-=2;
		}
	}
	cout<<c;  //输出计数器
	return 0;
}

```

---

## 作者：徐豪辰 (赞：0)

~~无聊至极，何不来CF题库一刷水题~~


------------


闲话不多说，下面开始题解时间

其实这道题完完全全就是一道大模拟题，比一比耐性，大概每一个像我一样的蒟蒻都可以在十分钟到半个小时通过的


------------
我的方法非常简单，模拟一个棋盘，将边界都赋值为1，而将棋盘赋值为零，开一个bool数组二维即可（如下图）

P.S：其实空间开销也不是很大，但没有做到最优，详情参见这篇题解的其他巨佬的题解。

最后的话，判断一下上下左右对角线的格子是不是1，应该都知道八皇后的套路了吧！

```cpp
1111111111
1000000001
1000000001
1000000001
1000000001
1000000001
1000000001
1000000001
1*00000001
1111111111
```

P.S:不要尝试贴代码
#### 上代码！！！

------------


```cpp
#include<bits/stdc++.h>//万能头
using namespace std;//命名空间
char a,b;//题面中既有字母，又有数字，干脆读字符咯
bool chess[10][10];//模拟棋盘
int x,y,ans = 8;//x,y储存坐标。ans就不用说了吧
int main(){//愉快的主函数
    cin>>a>>b;//生命苦短，我用cin
    x=a-'a';y=b-'0';x++;//参见，ACSII码
    
    //测试区
//    printf("x:%d\ny:%d\n",x,y);

    for(int i=0;i<=9;i++){//开始处理边界
        for(int j=0;j<=9;j++){//二维循环
            if(i==0||i==9){//简单的判断
				chess[i][j] = 1;//简单的赋值
          		continue;//简单的跳过
	       }else{//简单的否则
            if(j==0||j==9)chess[i][j]=1;//简单的。。
        	}
    	}
	}
    while(1);
    if(chess[x][y+1]==1)ans--;//简单的判断
    if(chess[x+1][y]==1)ans--;
    if(chess[x][y-1]==1)ans--;
    if(chess[x-1][y]==1)ans--;
    if(chess[x+1][y+1]==1)ans--;
    if(chess[x+1][y-1]==1)ans--;
    if(chess[x-1][y+1]==1)ans--;
    if(chess[x-1][y-1]==1)ans--;
    cout<<ans<<endl;//生命苦短，我用cout
    return 0;//再见
}
```

---

## 作者：RioBlu (赞：0)


在一副![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF710A/c293477e407dd29c222477fd35652e45e6890a3c.png)
这样子的棋盘中告诉你国王的位置，问他能走的地方有几处？

先设ans=8

本题只要判断国王是否在边界，如果国王在a或h位置ans=ans-3;

如果国王在1或8位置ans=ans-3;

#### 但是注意了！如果棋在a1怎么办？那么将ans=ans+1;
#### 之类的情况可以打表或 ： if(ans==2)ans++;

附件如下：
```
#include<bits/stdc++.h>
using namespace std;
string a;
long long b;
bool x,y;
int main()
{
	cin>>a;
	if(a[0]=='h'||a[0]=='a')x=1;
	if(a[1]=='8'||a[1]=='1')y=1;
	if(x==1&&y==1)b++;
	if(x==1)b=b-3;
	if(y==1)b=b-3;
	cout<<b+8<<endl;
}
```

---

## 作者：神谕者 (赞：0)

## 这题真心水。
#### 只要找到与国王距离小于等于1的格子就行了。
#### 上代码
```
#include<bits/stdc++.h>
using namespace std;
char s[9]={'0','a','b','c','d','e','f','g','h'};
char a;
int b,c;
int ans;
int main()
{
	cin>>a>>b;//输入行，列；
	for(int i=1;i<=8;++i)//找出行是第几行。
	{
		if(s[i]==a)
		c=i;
	}
	for(int i=1;i<=8;++i)//枚举整个棋盘。
	for(int j=1;j<=8;++j)
	{
		if(abs(b-j)<=1&&abs(c-i)<=1)
		ans++;//如果距离小于等于1，就加一。
	}
	cout<<ans-1;//把自己算进去了。
	return 0;
}
```


---

## 作者：花落丶宸星 (赞：0)

### 这道题是一道较为简单的字符串或字符操作题。主要是细心！！！      
这道题一定要把所有的可能性都考虑进去。    
因为我太蒻了，所以我直接贴代码，没有注释了。。。
```pascal
var
  ch1,ch2:char;
begin
  readln(ch1,ch2);
  if ((ch1='a')and(ch2='1'))or((ch1='a')and(ch2='8'))or((ch1='h')and(ch2='1'))or((ch1='h')and(ch2='8'))then
    writeln('3') else
  if ((ch1='a')and(ch2<>'1')and(ch2<>'8'))or((ch1='h')and(ch2<>'1')and(ch2<>'8'))or((ch2='1')and(ch1<>'a')and(ch1<>'h'))or((ch2='8')and(ch1<>'a')and(ch1<>'h')) then
    writeln('5') else
    writeln('8');

end.

```

---

