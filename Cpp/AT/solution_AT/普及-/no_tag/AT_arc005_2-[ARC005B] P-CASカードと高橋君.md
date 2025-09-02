# [ARC005B] P-CASカードと高橋君

## 题目描述

高桥君为了准备即将到来的7月27日土用丑日，打算邮购一些高级鳗鱼食材，通过网上银行来支付。
高桥君使用的银行卡背面有下图所示的9×9密码表。支付的时候从表中某一位置开始根据指定的方向连续读4个数字作为验证码输入，验证是否是本人操作。
下图的例子是从左边第一列，上方第一行开始，按斜右下的方向连续读4个数字。此时读出来的数字是7930.
![从1行1列斜右下方读4个数字的例子](https://cdn.luogu.org/upload/vjudge_pic/AT212/1322cf9dc84e8f92c1d1bc5a04632c79ef77742b.png)
如果读数的过程中超过了边界，就要将方向改变，然后继续读剩余的数字。改变方向的规则如下：
- 原方向是上下左右时
 - 将原方向180°调转
- 原方向是斜向时
 - 在对角线上时
   - 将原方向180°调转
 - 遇到左右边界时
   - 上下方向不变，左右方向调转
 - 遇到上下边界时
   - 左右方向不变，上下方向调转
   
总之如下图所示
![方向改变规则一览](https://cdn.luogu.org/upload/vjudge_pic/AT212/3ac92d5cd0fc3557db9edd76ec244f9fa94d4afd.png)
给出密码表、起始位置和方向，要求输出相应的4位验证码。

## 说明/提示

### 样例1
- 3列5行，右方向
![](https://cdn.luogu.org/upload/vjudge_pic/AT212/5e27e15dada42139db5cd3b98f6db7752ae9a657.png)
### 样例2
- 8列9行，左上方向
![](https://cdn.luogu.org/upload/vjudge_pic/AT212/9dc284a6840179386ceb1db5c03530bf6fc8a940.png)
### 样例3
- 5列7行，下方向，遇到下边界，改变方向继续读数
![](https://cdn.luogu.org/upload/vjudge_pic/AT212/d911646cf5ec9ec68da2abe6f843348c89f7f7be.png)
### 样例4
- 2行2列，左上方向，遇到边界，改变方向继续读数
![](https://cdn.luogu.org/upload/vjudge_pic/AT212/f7d82020d9c29a8c427cfb43bd1e4427c999dbd7.png)
### 样例5
- 8行7列，右下方向，遇到边界，改变方向继续读数
![](https://cdn.luogu.org/upload/vjudge_pic/AT212/2aaec32b8dda904f581a7276183c4b15c70541a9.png)

# 题解

## 作者：Blikewsr (赞：10)

 - [$\color{orange}\text{[ AT212 原题链接 ]}$](https://www.luogu.com.cn/problem/AT212)
 
 - 题目描述                    
   高桥君为了准备即将到来的 $7$ 月 $27$ 日土用丑日 ，打算邮购一些高级鳗鱼食材，通过网上银行来支付。高桥君使用的银行卡背面有下图所示的 $9×9$ 密码表。支付的时候从表中某一位置开始根据指定的方向连续读 $4$ 个数字作为验证码输入，验证是否是本人操作。下图的例子是从左边第一列，上方第一行开始，按斜右下的方向连续读 $4$ 个数字。此时读出来的数字是 $7930$。如果读数的过程中超过了边界，就要将方向改变，然后继续读剩余的数字。改变方向的规则如下：       
   - 原方向是上下左右时
   - 将原方向180°调转
   - 原方向是斜向时
   - 在对角线上时
       - 将原方向180°调转
   - 遇到左右边界时
       - 上下方向不变，左右方向调转
   - 遇到上下边界时
       - 左右方向不变，上下方向调转   
       
   给出密码表、起始位置和方向，要求输出相应的 $4$ 位验证码。                        
   
 - 输入格式                     
   ```
   x y W
	c11 c12 ... c19
	c21 c22 ... c29
	:
	:
	c91 c92 ... c99

   ```
                   
 - 输出格式          
   ```
   输出一行四个整数，最后输出换行。
   ```
                 
 - 注意          
   1. 整数 $x$ 代表列 $(1≤x≤9)$，整数 $y$ 代表行 $(1≤y≤9)$，$W$ 表示方向
   2. $W$ 是 $R、L、U、D、RU、RD、LU、LD$ 的其中一种
      - $R$:右方向
      - $L$:左方向
      - $U$:上方向
      - $D$:下方向
      - $RU$:右上方向
      - $RD$:右下方向
      - $LU$:左上方向
      - $LD$:左下方向
      - 第 $2$ 行到第 $9$ 行是密码表中的整数 $C_{ij}(1≦i,j≦9)$    
      - $i$ 和 $j$ 表示第 $i$ 行第 $j$ 列数字 $C_{ij}$ 
      - $C_{ij}$ 的范围是 $0~9$    

 - 思路             
   因为验证码的第一位数字就是第 $x$ 列 $y$ 行的数字。所以，我们可以先直接输出 $C_{ij}$。然后，再找 $3$ 次验证码，再输出就行了。     
   
   但是要怎么找验证码呢？            
   
   首先，我们先定义一个字符数组 $mp$，用来输入密码表。再定义一个字符串数组 $s$，再把所有的命令分别赋值上去。然后，再定义 $mx$ 和 $my$ 变量，分别表示对应命令的行列移动，就例如：$RU$ 分别对应 $x=1$ 和 $y=-1$，接着用一个 string 类型的变量 $ans$ 用来储存验证码，并把 $mp_{xy}$ 赋值为 $ans$ 的第一位验证码。先用一个 for 循环找出输入的是哪一个指令，用 $k$ 记下来（下标从 $0$ 开始）。再找验证码的时候，会有两种情况，在边界内和边界外。如果边界内，那么就直接加进 $ans$ 里去，但如果在边界外的话，我们就把它本来的方向开改成反弹后的方向。 
   
   那要怎么改呢？     
   
   我们先看看下面这个图片吧。      
                                            
   ![](https://cdn.luogu.org/upload/vjudge_pic/AT212/3ac92d5cd0fc3557db9edd76ec244f9fa94d4afd.png)         
                                         
   再列举两个边界的移动和位置 $(mx,my),(x,y)$，例如：$(1,0),(9,8)$、$(1,-1),(1,1)$，将 $mx$ 和 $my$ 改变之后是 $(-1,0)$、$(1,1)$，我们发现，其实只用判断 $mx+x$ 与 $my+y$ 会不会出界就行了，如果出界，就会变成相反的方向移动。             
   
   该部分代码：       
   ```cpp
   if((mx[k]+x>9)||(mx[k]+x<1)) mx[k]=-mx[k];
   if((my[k]+y>9)||(my[k]+y<1)) my[k]=-my[k];
   x+=mx[k];
   y+=my[k];
   ans+=mp[y][x];
   ```
                                 
 - 代码实现             
 ```cpp
#include<bits/stdc++.h>  // 万能头
using namespace std;
int x,y,t=3;     // 初始位置和循环次数
string w;    // 指令
string s[9]={"R","L","U","D","RU","RD","LU","LD"}; // "指令大全"
int mx[9]={1,-1,0,0,1,1,-1,-1};   
int my[9]={0,0,-1,1,-1,1,-1,1};  
 // 对应指令的移动
char mp[10][10];    // 密码表
string ans;    // 验证码
int find_w(){   // 查找指令
	for(int i=0;i<9;i++)
		if(s[i]==w) return i;	
}
int main(){ 
	cin>>x>>y>>w;          
	for(int i=1;i<10;i++)
		for(int j=1;j<10;j++)
			cin>>mp[i][j];
    // 输入
	int k=find_w();
	ans=mp[y][x];
    // 先把第一个验证码确定好
	while(t){  // 循环
		t--;
		if((x+mx[k]<10)&&(x+mx[k]>0)&&(y+my[k]<10)&&(y+my[k]>0)){          // 边界内 
			x+=mx[k];    
			y+=my[k];    
            // 直接移动 
			ans+=mp[y][x];   // 储存验证码	
		}	
		else{        // 边界外
			if((mx[k]+x>9)||(mx[k]+x<1)) mx[k]=-mx[k];
			if((my[k]+y>9)||(my[k]+y<1)) my[k]=-my[k];
            // 分别判断
			x+=mx[k];
			y+=my[k];
            // 移动
			ans+=mp[y][x];   // 储存验证码
		}
	}
	cout<<ans<<'\n';    // 输出验证码
    return 0;
}
```

此代码仅供参考！             
谢谢！                  


---

## 作者：Doveqise (赞：4)

这个题是一个小模拟，按题意写即可 小小的判断一下边界 下见代码  
（跟刘汝佳学的dx dy数组骚操作233 不用各种switch）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int x,y;scanf("%d%d",&x,&y);
    x--;y--;
    string w;cin>>w;//操作
    char m[9][9];//密码表
    for(int i=0;i<9;i++){
		scanf("\n");//scanf要读空行QAQ
		for(int j=0;j<9;j++) scanf("%c",&m[i][j]);//读入密码表
	}
    int dx[8]={1,-1,1,0,0,-1,-1,1};//挪动x
    int dy[8]={0,0,-1,-1,1,1,-1,1};//挪动y
    string s[8]={"R","L","RU","U","D","LD","LU","RD"};//判断指令
    printf("%c",m[y][x]);//第一下不用移动
    int ddx,ddy;//移动
    for(int i=0;i<8;i++)
		if(w==s[i])ddy=dy[i],ddx=dx[i];//判断移动
    for(int i=0;i<3;i++){
        if(x+ddx<0||x+ddx>=9)ddx=-ddx;//x越界
        if(y+ddy<0||y+ddy>=9)ddy=-ddy;//y越界
        x+=ddx;y+=ddy;//移动
        printf("%c",m[y][x]);//输出密码
    }
    puts("");//万恶的换行
    return 0;
}

```


---

## 作者：YclarHIM0302 (赞：2)

### 注：可以先看一下这里代码的所有判断方向
![一张非常清晰的照片](https://cdn.luogu.com.cn/upload/image_hosting/yhn1mr0l.png)
如图所示，在这道题中有以下需要注意的点：
1. x,y与行列相反；
1. 不在壁上时要判定8个方向；
1. 在壁上时要进行“反弹”的碰壁检测；
1. 非上下左右的四个方向在碰壁时会有不同的“反弹”效果

Tips:图里少画一条线（鳡）

有人云：“暴力即是优雅！”

###### 我说的

所以就“优雅地”模拟出来就好啦~
# 那么就...上代码！
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define io_speed_up ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
string w;
int x,y;
char a[10][10],b[5];//a存放验证符 ，b存放后3位验证码 
int main()
{
    io_speed_up;//输入输出加快专用
	cin>>y>>x>>w;//行列与坐标相反 ，w存放移动方向 
	for(int i=1;i<=9;i++)
	{
		for(int j=1;j<=9;j++) cin>>a[i][j];//字符载入 
	}
	int x1=x,y1=y;
	char a1=char(a[x][y]);//第一位验证码 
	for(int i=1;i<=3;i++)
	{
		if(w[0]=='R'&&(w[1]!='U'&&w[1]!='D')) //向右 
		{
			if(y1+1>9)//碰壁检测 
			{
				w='L';//改变方向 
				b[i]=a[x1][--y1];
				continue;
			} 
			else b[i]=a[x1][++y1];//正常情况 
			continue;
		}
		if(w[0]=='L'&&(w[1]!='U'&& w[1]!='D')) //向左 
		{
			if(y1-1<1)//碰壁检测 
			{
				w='R';
				b[i]=a[x1][++y1];
				continue;
			} 
			else b[i]=a[x1][--y1];
			continue;
		}
		if(w[0]=='D') //向下 
		{
			if(x1+1>9)//碰壁检测 
			{
				w='U';
				b[i]=a[--x1][y1];
				continue;
			} 
			else b[i]=a[++x1][y1];
			continue;
		}
		if(w[0]=='U') //向上 
		{
			if(x1-1<1)//碰壁检测 
			{
				w='D';
				b[i]=a[++x1][y1];
				continue;
			} 
			else b[i]=a[--x1][y1];
			continue;
		}
		if(w[0]=='R'&&w[1]=='D') //向右下 
		{
			if(y1+1>9&&x1+1>9)//碰右下点检测 
			{
				w="LU";
				b[i]=a[--x1][--y1];
				continue;
			} 
			if(y1+1>9&&x1+1<=9)//碰右壁检测 
			{
				w="LD";
				b[i]=a[++x1][--y1];
				continue;
			}
			
			if(y1+1<=9&&x1+1>9)//碰下壁检测 
			{
				w="RU";
				b[i]=a[--x1][++y1];
				continue;
			} 
			if(y1+1<=9&&x1+1<=9) b[i]=a[++x1][++y1];
			continue;
	    }
	    if(w[0]=='R'&&w[1]=='U') //向右上 
		{
			if(y1+1>9&&x1-1<1)//碰右上点检测 
			{
				w="LD";
				b[i]=a[++x1][--y1];
				continue;
			} 
			if(y1+1<=9&&x1-1<1)//碰上壁检测 
			{
				w="RD";
				b[i]=a[++x1][++y1];
				continue;
			}
			if(y1+1>9&&x1-1>=1)//碰右壁检测 
			{
				w="LU";
				b[i]=a[--x1][--y1];
				continue;
			} 
			if(y1+1<=9&&x1-1>=1) b[i]=a[--x1][++y1];
			continue;
	    }
	    if(w[0]=='L'&& w[1]=='U') //向左上 
		{
			if(y1-1<1&&x1-1<1)//碰左上点检测 
			{
				w="RD";
				b[i]=a[++x1][++y1];
				continue;
			} 
			if(y1-1<1&&x1-1>=1)//碰左壁检测 
			{
				w="RU";
				b[i]=a[--x1][++y1];
				continue;
			}
			
			if(y1-1>=1&&x1-1<1)//碰上壁检测 
			{
				w="LD";
				b[i]=a[++x1][--y1];
				continue;
			} 
			if(y1-1>=1&&x1-1>=1) b[i]=a[--x1][--y1];
			continue;
		
	    }
	    if(w[0]=='L'&&w[1]=='D') //向左下 
		{
			if(y1-1<1&&x1+1>9)//碰左下点检测 
			{
				w="RU";
				b[i]=a[--x1][++y1];
				continue;
			} 
			if(y1-1<1&&x1+1<=9)//碰左壁检测 
			{
				w="RD";
				b[i]=a[++x1][++y1];
				continue;
			}
			if(y1-1>=1&&x1+1>9)//碰下壁检测 
			{
				w="LU";
				b[i]=a[--x1][--y1];
				continue;
			} 
			if(y1-1>=1&&x1+1<=9) b[i]=a[++x1][--y1];
			continue;
	    }
	}
	cout<<a1<<b[1]<<b[2]<<b[3]<<endl;//输出验证码 
    return 0;
}
```
~~不想暴力求解的不要用这种方法~~

---

## 作者：Level_Down (赞：2)

题意不再赘述，我们来看一看这题的方法。

首先，对于“D”“U”“L”“R”等方向的变化我们可以用x轴和y轴值的变化来呈现。

部分代码：

```cpp
for (int i = 0; i < 2; i++){
			if (s[i] == 'R') y = 1;//s是输入的字符串，如“R”“RU”
			if (s[i] == 'L') y = -1;
			if (s[i] == 'U') x = -1;
			if (s[i] == 'D') x = 1;
		}
```

在这个代码中，假如输入的是“LD”，就会将x赋值为1，y赋值为-1。

然后在每次移动的过程中，对于a[ n ] [ m ]，n += x, m += y，然后再进行输出。

接下来是本题的一个难点，如何在撞边之后改变x，y的值呢？

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT212/3ac92d5cd0fc3557db9edd76ec244f9fa94d4afd.png)

举例看最右边的两个，先看上边的，原来x = 0，y = 1，现在x = 0，y = -1。

再看下边的，原来x = 1， y = 1，现在x = 1，y = -1。

我们发现，对于同一条边而言，如果出了这条边，改变的是x还是y是固定的，如右边就固定改变y的值。

然后就能写出一段判断的代码了：

```cpp
if (n > 9 || n < 1 || m > 9 || m < 1){
					n -= x; m -= y;
					if (n + x < 1 || n + x > 9) x *= -1;
					if (m + y < 1 || m + y > 9) y *= -1; 
					n += x; m += y;
				}
```

但如果碰到四角呢？也是可以的，如碰到右下角的时候，右边和下边同时出界，x和y的值同时改变，完全OK。

然后我们就去AC这道题吧！

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,x,y;//n为行，m为列，x和y如上。
string s;
char a[10][10];
int main(){
	cin >> m >> n >> s;//题目先给列再给行，所以反着读。
	for (int i = 1; i <= 9; i++) for (int j = 1; j <= 9; j++) cin >> a[i][j];
	for (int i = 0; i < 2; i++){//如上。
			if (s[i] == 'R') y = 1;
			if (s[i] == 'L') y = -1;
			if (s[i] == 'U') x = -1;
			if (s[i] == 'D') x = 1;
		}
	for (int i = 1; i <= 4; i++){
			cout << a[n][m];
			n += x; m += y;
			if (n > 9 || n < 1 || m > 9 || m < 1){//判断出界，如上。
					n -= x; m -= y;
					if (n + x < 1 || n + x > 9) x *= -1;//改变x或y的值。
					if (m + y < 1 || m + y > 9) y *= -1; 
					n += x; m += y;
				}
		}	
	cout << endl;	//AT的题都要换行！
	return 0;//AC！	
 } 
```



---

## 作者：朱屹帆 (赞：1)

### 题目：[AT212 P-CASカードと高橋君](https://www.luogu.com.cn/problem/AT212)
### 题意：~~题目已经讲得很清楚了~~

### 思路：
这显然是一道需要分类讨论的题目，下面开始分类讨论：

令当前所在位置为$ (x,y), $即第$ x $行第$ y $列。

则由题意，可列出下列分类式：

- R  右方向 

 **当$y≤8$时**，_下一步至$(x,y+1)$中执行$R$命令。_ 

 **当$y=9$时**，_下一步至$(x,y-1)$中执行$L$命令_

- L  左方向 

 **当$y≥2$时**，_下一步至$(x,y-1)$中执行$L$命令。_ 

 **当$y=1$时**，_下一步至$(x,y+1)$中执行$R$命令_ 
 
- U  上方向 

 **当$x≥2$时**，_下一步至$(x-1,y)$中执行$U$命令。_ 
 
 **当$x=1$时**，_下一步至$(x+1,y)$中执行$D$命令_ 
 
- D  下方向 

 **当$x≤8$时**，_下一步至$(x+1,y)$中执行$D$命令。_ 
 
 **当$x=9$时**，_下一步至$(x-1,y)$中执行$U$命令_ 

- RU 右上方向 

 **当$x≠1$且$y≠9$时**，_下一步至$(x-1,y+1)$中执行$RU$命令。_ 

 **当$x=1$且$y≠9$时**，_下一步至$(x+1,y+1)$中执行$RD$命令。_ 

 **当$x≠1$且$y=9$时**，_下一步至$(x-1,y-1)$中执行$LU$命令。_ 

 **当$x=1$且$y=9$时**，_下一步至$(x+1,y-1)$中执行$LD$命令。_ 

- RD 右下方向 

 **当$x≠9$且$y≠9$时**，_下一步至$(x+1,y+1)$中执行$RD$命令。_ 

 **当$x=9$且$y≠9$时**，_下一步至$(x-1,y+1)$中执行$RU$命令。_ 

 **当$x≠9$且$y=9$时**，_下一步至$(x+1,y-1)$中执行$LD$命令。_ 

 **当$x=9$且$y=9$时**，_下一步至$(x-1,y-1)$中执行$LU$命令。_ 

- LU 左上方向 

 **当$x≠1$且$y≠1$时**，_下一步至$(x-1,y-1)$中执行$LU$命令。_ 

 **当$x=1$且$y≠1$时**，_下一步至$(x+1,y-1)$中执行$LD$命令。_ 

 **当$x≠1$且$y=1$时**，_下一步至$(x-1,y+1)$中执行$RU$命令。_ 

 **当$x=1$且$y=1$时**，_下一步至$(x+1,y-1)$中执行$RD$命令。_ 

- LD 左下方向 

 **当$x≠9$且$y≠1$时**，_下一步至$(x+1,y-1)$中执行$LD$命令。_ 

 **当$x=9$且$y≠1$时**，_下一步至$(x-1,y-1)$中执行$LU$命令。_ 

 **当$x≠9$且$y=1$时**，_下一步至$(x+1,y+1)$中执行$RD$命令。_ 

 **当$x=9$且$y=1$时**，_下一步至$(x-1,y+1)$中执行$RU$命令。_ 

列出上面分类式，我们基本就可以解决这一题了！

我们可以用四个循环来记录答案，当然我更喜欢用在函数里。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long q=0,w=1;
	char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')q=q*10+ch-'0',ch=getchar();
	return q*w;
} //快读 
const long long N = 1e3+5;
long long x,y,i,j; //(x,y)即输入初始坐标 
string order[N]={"","R","L","U","D","RU","RD","LU","LD"}; //记录所有命令 
string input,ans; //input即输入方向，ans记录答案 
char s[N][N]; //用字符串来记录数组 
void Route(long long a,long long b,long long len,string king){
	if(len==5)return ; //答案只要求了四位即可 
	ans=ans+s[a][b];
	if(king==order[1]){ //讨论R右方向 
		if(b<=8)Route(a,b+1,len+1,order[1]); //当y≤8时
		else Route(a,b-1,len+1,order[2]); //当y=9时
	}
	if(king==order[2]){ //讨论L左方向
		if(b>=2)Route(a,b-1,len+1,order[2]); //当y≥2时
		else Route(a,b+1,len+1,order[1]); //当y=1时
	}
	if(king==order[3]){ //讨论U上方向
		if(a>=2)Route(a-1,b,len+1,order[3]); //当x≥2时
		else Route(a+1,b,len+1,order[4]); //当x=1时
	}
	if(king==order[4]){ //讨论D下方向
		if(a<=8)Route(a+1,b,len+1,order[4]); //当x≤8时
		else Route(a-1,b,len+1,order[3]); //当x=9时
	}
	if(king==order[5]){ //讨论RU右上方向
		if(a!=1&&b!=9)Route(a-1,b+1,len+1,order[5]); //当x≠1且y≠9时
		if(a==1&&b!=9)Route(a+1,b+1,len+1,order[6]); //当x=1且y≠9时
		if(a!=1&&b==9)Route(a-1,b-1,len+1,order[7]); //当x≠1且y=9时
		if(a==1&&b==9)Route(a+1,b-1,len+1,order[8]); //当x=1且y=9时
	}
	if(king==order[6]){ //讨论RD右下方向
		if(a!=9&&b!=9)Route(a+1,b+1,len+1,order[6]); //当x≠9且y≠9时
		if(a==9&&b!=9)Route(a-1,b+1,len+1,order[5]); //当x=9且y≠9时
		if(a!=9&&b==9)Route(a+1,b-1,len+1,order[8]); //当x≠9且y=9时
		if(a==9&&b==9)Route(a-1,b-1,len+1,order[7]); //当x=9且y=9时
	}
	if(king==order[7]){ //讨论LU左上方向
		if(a!=1&&b!=1)Route(a-1,b-1,len+1,order[7]); //当x≠1且y≠1时
		if(a==1&&b!=1)Route(a+1,b-1,len+1,order[8]); //当x=1且y≠1时
		if(a!=1&&b==1)Route(a-1,b+1,len+1,order[5]); //当x≠1且y=1时
		if(a==1&&b==1)Route(a+1,b+1,len+1,order[6]); //当x=1且y=1时
	}
	if(king==order[8]){ //讨论LD左下方向
		if(a!=9&&b!=1)Route(a+1,b-1,len+1,order[8]); //当x≠9且y≠1时
		if(a==9&&b!=1)Route(a-1,b-1,len+1,order[7]); //当x=9且y≠1时
		if(a!=9&&b==1)Route(a+1,b+1,len+1,order[6]); //当x≠9且y=1时
		if(a==9&&b==1)Route(a-1,b+1,len+1,order[5]); //当x=9且y=1时
	}
	return ;
}
int main(){
	x=read(),y=read(),cin>>input; //输入 
	for(i=1;i<=9;i++)
		for(j=1;j<=9;j++)
			cin>>s[i][j];
	Route(y,x,1,input); //函数解决 
	cout<<ans<<endl;
	return 0; //完美收场 
}
```
### 注：
这一道题实际并不难，只要能够有耐心的将它演算完就可以解出答案！

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT212)

小学生又双叒叕来写题解啦！

翻了一下大家的代码，都好长好复杂，其实直接模拟就好了。

先说一个巨坑：发现**坐标与我们平时不同**，所以进行修改。

写一个函数，函数作用为找出下一位密码。

函数需要八种不同情况的判断，有点繁琐，唯一要注意的是**边界方向**的修改。

再次声明，代码有大量空间压行，但没必要，因为这样可以理解得更清楚。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
char a[15][15];
int x, y;
string W, ans;
void FindAnswer()
{
	ans += a[x][y];
	
	//printf("x = %d, y = %d;\n", x, y);
	//用以上语句调试超好用。 
	
	if (W == "R")  //往右。 
	{
		if (x == 9) x--, W = "L";
		else x++;
	}
	else if (W == "L") //往左。 
	{
		if (x == 1) x++, W = "R";
		else x--;
	}
	else if (W == "U")  //往上。 
	{
		if (y == 1) y++, W = "D";
		else y--;
	}
	else if (W == "D")  //往下。 
	{
		if (y == 9) y--, W = "U";
		else y++;
	}
	else if (W == "RU")  //往右上。
	{
		//x是列，y是行！！！ 
		if (x == 9 && y == 1) x--, y++, W = "LD";
		else if (x == 9) x--, y--, W = "LU";
		else if (y == 1) x++, y++, W = "RD"; 
		else x++, y--;
	}
	else if (W == "RD")  //往右下。
	{
		if (x == 9 && y == 9) x--, y--, W = "LU";
		else if (x == 9) x--, y++, W = "LD";
		else if (y == 9) x++, y--, W = "RU";
		else x++, y++;
	}
	else if (W == "LU")  //往左上。
	{
		if (x == 1 && y == 1) x++, y++, W = "RD";
		else if (x == 1) x++, y--, W = "RU";
		else if (y == 1) x--, y++, W = "LD";
		else x--, y--;
	} 
	else if (W == "LD")  //往左下。
	{
		if (x == 1 && y == 9) x++, y--, W = "RU";
		else if (x == 1) x++, y++, W = "RD";
		else if (y == 9) x--, y--, W = "LU";
		else x--, y++;
	} 
}
int main()
{
	cin >> x >> y >> W;
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
			cin >> a[j][i];  //由于题目的坐标与平时不同，所以要反向读入。 
	for (int i = 1; i <= 4; i++) FindAnswer();
	cout << ans << endl;  //记得按要求换行。 
	return 0;
}
```


---

## 作者：MattL (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT212)

这就是一题大模拟，根据题目套四次循环输出答案即可。

**干货：dx 和 dy**

这个数组在棋盘类问题中可以快速解决往各个方向时，坐标的变化

**四个方向：**

```cpp
//          ←，→，↓，↑
int dx4[]={ 0, 0, 1,-1};
int dy4[]={-1, 1, 0, 0};
```
**八个方向：**

```cpp
//         ↖，←，↙，↑，↓，↗，→，↘
int dx8[]={-1, 0, 1,-1, 1,-1, 0, 1};
int dy8[]={-1,-1,-1, 0, 0, 1, 1, 1};
```

细节和解释见代码  ↓

~~码字不易，求管理员通过~~

```cpp
#include <bits/stdc++.h>
using namespace std;
struct zb{int x,y;};
int dx8[]={-1,0,1,-1,1,-1,0,1};
int dy8[]={-1,-1,-1,0,0,1,1,1};
int mp[10][10];
zb start;
string fx_,t;
int fx;
int main()
{
	cin>>start.y>>start.x>>fx_;//注意！注意！先输入y，再输入x！
	if(fx_=="LU")//左上
	{
		fx=0;
	}
	if(fx_=="L")//左
	{
		fx=1;
	}
	if(fx_=="LD")//左下
	{
		fx=2;
	}
	if(fx_=="U")//上
	{
		fx=3;
	}
	if(fx_=="D")//下
	{
		fx=4;
	}
	if(fx_=="RU")//右上
	{
		fx=5;
	}
	if(fx_=="R")//右下
	{
		fx=6;
	}
	if(fx_=="RD")//右下
	{
		fx=7;
	}
	getline(cin,t);//读换行，我跳了亿会儿
	for(int i=1;i<=9;i++)
	{
		getline(cin,t);
		for(int o=1;o<=9;o++)
		{
			mp[i][o]=t[o-1]-'0';//存入数组
		}
	}
	for(int i=1;i<=4;i++)//枚举4位密码
	{
		cout<<mp[start.x][start.y];
		start.x+=dx8[fx];
		start.y+=dy8[fx];
		if(fx==0&&start.x<=0&&start.y<=0)//左上边界
		{
			start.x=start.y=2;
			fx=7;
			continue;
		}
		if(fx==0&&start.x<=0&&start.y>0&&start.y<=9)//上边界
		{
			start.x=2;
			fx=2;
			continue;
		}
		if(fx==0&&start.y<=0&&start.x>0&&start.x<=9)//左边界
		{
			start.y=2;
			fx=5;
			continue;
		}
		if(fx==1&&start.y<=0)//左边界
		{
			start.y=2;
			fx=6;
			continue;
		}
		if(fx==2&&start.x>9&&start.y<=0)//左下边界
		{
			start.x=8;start.y=2;
			fx=5;
			continue;
		}
		if(fx==2&&start.x>9&&start.y>0&&start.y<=9)//下边界
		{
			start.x=8;
			fx=0;
			continue;
		}
		if(fx==2&&start.y<=0&&start.x>0&&start.x<=9)//左边界
		{
			start.y=2;
			fx=7;
			continue;
		}
		if(fx==3&start.x<=0)//左边界
		{
			start.x=2;
			fx=4;
			continue;
		}
		if(fx==4&start.x>9)//右边界
		{
			start.x=8;
			fx=3;
			continue;
		}
		if(fx==5&&start.x<=0&&start.y>9)//右上边界
		{
			start.x=2;start.y=8;
			fx=2;
			continue;
		}
		if(fx==5&&start.x<=0&&start.y>0&&start.y<=9)//上边界
		{
			start.x=2;
			fx=7;
			continue;
		}
		if(fx==5&&start.y>9&&start.x>0&&start.x<=9)//右边界
		{
			start.y=8;
			fx=0;
			continue;
		}
		if(fx==6&start.y>9)//右边界
		{
			start.y=8;
			fx=1;
			continue;
		}
		if(fx==7&&start.x>9&&start.y>9)//右下边界
		{
			start.x=start.y=8;
			fx=0;
			continue;
		}
		if(fx==7&&start.x>9&&start.y>0&&start.y<=9)//下边界
		{
			start.x=8;
			fx=5;
			continue;
		}
		if(fx==7&&start.y>9&&start.x>0&&start.x<=9)//右边界
		{
			start.y=8;
			fx=2;
			continue;
		}
	}
	puts("");//岛国题常规换行
	return 0;
}
```


---

## 作者：Loxilante (赞：0)

这真是一道水题，像我这种~~喜欢重复不喜欢骚操作~~的人就老老实实Ctrl+v吧


------------

$Talking$
$is$
$cheap,$
$show$
$me$
$the$
$code:$

```cpp
#include<iostream>
#include<string>
#include<stdio.h>
#define AKIOI 1
using namespace std;
typedef long long ll;
int p[15][15];
int main(void)
{
	return AKIOI;
	int a, b;
	string w, ans;
	cin>>b>>a>>w;
	for(int i = 1; i <= 9; i++)
	{
		string str;
		cin>>str;
		for(int j = 0; j < 9; j++)
			p[i][j+1] = str[j]-'0';
	}
	ans+=p[a][b]+'0';
	for(int i = 1; i <= 3; i++)
	{
		if (a == 9 && b == 9 && w == "RD") w = "LU";      // 右下角 右下->左上 
		else if (a == 9 && b == 1 && w == "LD") w = "RU"; // 左下角 左下->右上 
		else if (a == 1 && b == 1 && w == "LU") w = "RD"; // 左上角 左上->右下 
		else if (a == 1 && b == 9 && w == "RU") w = "LD"; // 右上角 右上->左下 
		else if (a == 9 && w == "D" ) w = "U";  // 在最下边 下->上 
		else if (a == 9 && w == "RD") w = "RU"; // 在最下边 右下->右上 
		else if (a == 9 && w == "LD") w = "LU"; // 在最下边 左下->左上
		else if (a == 1 && w == "U" ) w = "D";  // 在最上边 上->下 
		else if (a == 1 && w == "RU") w = "RD"; // 在最上边 右上->右下 
		else if (a == 1 && w == "LU") w = "LD"; // 在最上边 左上->左下 
		else if (b == 9 && w == "R" ) w = "L";  // 在最右边 右->左 
		else if (b == 9 && w == "RU") w = "LU"; // 在最右边 右上->左上 
		else if (b == 9 && w == "RD") w = "LD"; // 在最右边 右下->左下 
		else if (b == 1 && w == "L" ) w = "R";  // 在最左边 左->右 
		else if (b == 1 && w == "LD") w = "RD"; // 在最左边 左下->右下 
		else if (b == 1 && w == "LU") w = "RU"; // 在最左边 左上->右上 
		// 根据方向移动坐标 
		if (w == "L") b--; // 向左移 
		else if (w == "R") b++; // 向右移
		else if (w == "U") a--; // 向上移
		else if (w == "D") a++; // 向下移
		else if (w == "RU") a--, b++; // 向左上移
		else if (w == "RD") a++, b++; // 向左下移
		else if (w == "LU") a--, b--; // 向右上移
		else if (w == "LD") a++, b--; // 向右下移
		ans+=p[a][b]+'0';
	}
	cout<<ans<<'\n';
	return 0;
}

```

###### ~~谁抄谁RE~~

---

## 作者：nanatsuhi (赞：0)

## 不大的模拟
~~等等这为什么是蓝题啊~~

由于密码只有短短的四位，只要按题意模拟就好。

此处建立了一个从字母方向到方向号的映射，每次都使用字母来操作。

移动的方式是通过映射得到方向序号再到数组里找一下。

代码如下：~~糟糕的冗长代码将就看看吧~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y;
string s,ans,board[10];
int dx[]={1,-1,0,0,1,1,-1,-1};  //dx和dy是移动数组
int dy[]={0,0,-1,1,-1,1,-1,1};
int main()
{
	
    cin>>x>>y>>s;
    x--,y--;  //数组下标从零开始(笑)
    for (int i=0;i<9;i++) 
        cin>>board[i];
    map<string,int> dir;  //建立映射
    dir["R"]=0,dir["L"]=1,dir["U"]=2,dir["D"]=3,dir["RU"]=4,dir["RD"]=5,dir["LU"]=6,dir["LD"]=7;  //定义字母对应的序号
    for (int i=0;i<4;i++)  //开始模拟
	{
        ans+=board[y][x];  //ans字符串加一位
        if(s=="R") //向右超出
		{
            if(x==8) s="L";
        }
        else if(s=="L")  //向左超出
		{
            if(x==0) s="R";
        }
        else if(s=="U")  //向上超出
		{
            if(y==0) s="D";
        }
        else if(s=="D")  //向下超出
		{
            if(y==8) s="U";
        }
        else if(s=="RU")  //向右上超出
		{
            if(x==8&&y==0) s="LD";
            else if(x==8) s="LU";
            else if(y==0) s="RD";
        }
        else if(s=="RD")  //向右下超出
		{
            if(x==8&&y==8) s="LU";
            else if(x==8) s="LD";
            else if(y==8) s="RU";
        }
        else if(s=="LU")  //向左上超出
		{
            if(x==0&&y==0) s="RD";
            else if(x==0) s="RU";
            else if(y==0) s="LD";
        }
        else  //向左下超出
		{
            if(x==0&&y==8) s="RU";
            else if(x==0) s="RD";
            else if(y==8) s="LU";
        }
        x+=dx[dir[s]],y+=dy[dir[s]]; //修改方向
    }
    cout<<ans<<endl; //输出结果
    return 0;  
}
```
完结撒花~

---

