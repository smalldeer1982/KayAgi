# 谜题 Puzzle

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=4&page=show_problem&problem=163

[PDF](https://uva.onlinejudge.org/external/2/p227.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA227/952149a2874e339bbc22a79a1cd1d063e89e1421.png)

## 样例 #1

### 输入

```
TRGSJ
XDOKI
M VLN
WPABE
UQHCF
ARRBBL0
ABCDE
FGHIJ
KLMNO
PQRS
TUVWX
AAA
LLLL0
ABCDE
FGHIJ
KLMNO
PQRS
TUVWX
AAAAABBRRRLL0
Z```

### 输出

```
Puzzle #1:
T R G S J
X O K L I
M D V B N
W P   A E
U Q H C F

Puzzle #2:
  A B C D
F G H I E
K L M N J
P Q R S O
T U V W X

Puzzle #3:
This puzzle has no final configuration.```

# 题解

## 作者：HanPi (赞：10)

**~~真就考输入输出?!~~**

![](https://cdn.luogu.com.cn/upload/image_hosting/7vgy6sct.png)

模拟部分很简单,输入简直了.
说一下几个坑点:

+ 其中恰好有一个格子是空的我感觉是坑你的,因为我不判断就不过 ~~(虽然其他大佬的题解没考虑也过了)~~
+ 注意处理当空格在该行最后一个位置的情况
+ 格式问题:
	+ 输出末尾必须有且只允许有1个换行符
   + 每两个Puzzle的输出间要空一行
+ 操作可能是断行的,由 `'0'` 标识结束
+ 遇到 `'Z'` 终止程序(虽然可能会出现网格中有 `'Z'` 但样例没有,所以不用管)

**代码**:

```c
/* UVA227 谜题 Puzzle */
#include <stdio.h>
#include <string.h>

#define SWAP(a,b) ((a)^=(b)^=(a)^=(b))	// 这样更块
char map[10][10];
char op[10086];
#define print(j,k) for (j = 0; j < 5; j++){for (k = 0; k < 5; k++){putchar(map[j][k]); if (k != 4)putchar(' ');}putchar('\n');}  

int main()
{
    int i, j, k, si, sj, flag = 0, cnt = 0;
    int is13 = 0, isFirst = 1; // 特判避免多输出换行
    while (++cnt)
    {
        is13 = 0; // 用于特判空格在末尾会读入换行
        si = -1, sj = -1;
        flag = 0;
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 5; j++)
            {
                map[i][j] = getchar();
                if (map[i][0] == 'Z')
                {
                    return 0;
                }
                if (!map[i][j] || map[i][j] == '\n'||map[i][j]=='\r')map[i][j] = ' ', is13 = 1;
                if (map[i][j] == ' ')
                {
                    if (si != -1 && sj != -1)flag = 1;
                    // 特判多个空格
                    si = i, sj = j;
                }
            }
            if(!is13)getchar();
        }
        i = 0;
        while (op[i]=getchar()) // 读入操作
        {
            if (op[i] == '0')break;
            if (op[i] == '\n' || op[i] == '\r')i--;
            i++;
        }
        getchar();
        i = 0;
        if(!flag)
            while (op[i] != '0') // 简单的模拟,不解释
        {
            if (op[i] == 'A')
            {
                if (si == 0)
                {
                    flag = 1;
                    break;
                }
                SWAP(map[si][sj], map[si - 1][sj]);
                si--;
            }
            else if (op[i] == 'B')
            {
                if (si == 4)
                {
                    flag = 1;
                    break;
                }
                SWAP(map[si][sj], map[si + 1][sj]);
                si++;
            }
            else if (op[i] == 'L')
            {
                if (sj == 0)
                {
                    flag = 1;
                    break;
                }
                SWAP(map[si][sj], map[si][sj - 1]);
                sj--;
            }
            else if (op[i] == 'R')
            {
                if (sj == 4)
                {
                    flag = 1;
                    break;
                }
                SWAP(map[si][sj], map[si][sj + 1]);
                sj++;
            }
            else
            {
                flag = 1;
                break;
            }
            i++;
        }
        if (isFirst) // 特判要不要换行
        {
            isFirst = 0;
        }
        else
        {
            putchar('\n');
        }
        printf("Puzzle #%d:\n", cnt);
        if (flag)
        {
            printf("This puzzle has no final configuration.\n");
        }
        else
        {
            print(j, k);
        }
    }
    return 0;
}
```

------------


**Tips**

- 提交时最好挂个梯子,不然非常慢
- UVA的C语言编译标准是很老的标准,for循环,注释等需要改

[UVA连接](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=163 "要挂梯子")
[vjudge连接](https://vjudge.net/problem/UVA-227 "还是要挂梯子") 

---

## 作者：Zlc晨鑫 (赞：10)

[_My blog_](https://www.luogu.com.cn/blog/Zlc/)

[PDF传送门](https://onlinejudge.org/external/2/p227.pdf)

请欣赏一波 _string_ 的 ~~骚操作~~ 实用技巧。

注意：样例中的第二、三组数据的空格没打上，所以怎么调都过不了样例，需要手动加上空格。

一开始的时候觉得这道题挺简单的，心想还有这么水的黄题。没想到这么多坑，说实话，这题是真的不容易过。如果你想轻而易举地水过这道题，我劝你还是放弃吧。不然的话你是真的强。另外[**UVA的格式**](https://www.luogu.com.cn/blog/Zlc/guan-yu-uva-di-ping-ce-biao-zhun)也是需要注意的。（觉得不够详细可以自行查资料）

说了这么多，开始分析题目吧。拿到这种字符串的题目，首先就要考虑输入。（不要觉得我无聊，输入是真的麻烦）。

这道题没有给出数据的个数，但以大写字母 _Z_ 结尾，所以我们在读入时要先读入一个字符，判断它是不是 _Z_。

```cpp
ch = getchar();
if (ch == 'Z') return 0;
```

这时，第一个坑就出现了，如果你只加一个 _getchar_ ，那么恭喜你，你把换行读进去了。那好，你可能会想，那我再加一个 _getchar_ ，像下面这样：

```cpp
getchar(); ch = getchar();
if (ch == 'Z') return 0;
```

那么再次恭喜你，你把第一组数据的首字母“吃”掉了。所以，正确的写法是：

```cpp
ch = getchar();
if (ch == '\n') ch = getchar();
if (ch == 'Z') return 0;
```

不要着急，这仅仅是本题的第一个坑，请接着往下看。

读入完之后，如果它不是 _Z_ ，又该怎么办呢？答案是将它存进字符串。这里我用的是一个 _string_ 数组来存，存完第一个字符还要接着存第 _1 \~ 5_ 行的其他字符。这也就是为什么我要用 _string_ 的一个原因了，_string_ 中有一个重载运算符 _+=_， 我们只需简单的将用 _getline_读入的字符串累加到 _a\[i\]_ 中即可：

```cpp
string a[5], s;
a[0] += ch;
for (int i = 0; i < 5; i++)
{
	// 读到换行符为止，不会读换行
	getline(cin, s, '\n');
    a[i] += s;
}
```
按照我们的习惯，一般是将数组定义在 _main_ 函数外，但这时，又恭喜你，你的字符串不会清零，到第二组数据时会累加到第一组数据后面（不行的话自己输出试试）。所以，要么定义在循环体内部，要么就清零。

```cpp
// 或者定义在循环体内
for (int i = 0; i < 5; i++)
	a[i] = "";
```

接下来就是读入指令串，这也是用 *string* 的原因之一。*getline* 的第三个参数是终止符，也就是读到这个字符为止（这个字符不会被读，不信可以自己输出实验）。所以，可以这样写：

```cpp
string s;
getline(cin, s, '0');
```

为了执行指令，需要找空格，这也是为何样例过不了的原因（样例中第四个字母之后直接就是换行，没有空格）：

```cpp
int p = 0, q = 0;
for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
        if (a[i][j] == ' ')
        {
            p = i;
            q = j;
            break;
        }
```

然后就是处理指令了，因为只有四种指令，所以列出每一种指令的即可。这里需要注意的是，在一次**成功**交换后，**p或q的值也需要改变**！不然的话会出现不止一个空格。（表问我怎么知道的）

最后，关于输出的格式，可以设置一个变量来判断当前行是不是第一行，如果不是，则输出一个空行。还有就是UVA要求

```cpp
bool first = true;
// 注意这两句不能写反！
if (!first) puts("");
if (first) first = 0;
```
这里我为了差错方便写了个debug函数，请自行忽略。

呼\~\~，终于说完了，最后给出AC代码：

```cpp
#include <cstdio>
#include <iostream>
#include <string>

#define error "This puzzle has no final configuration."

using namespace std;

string a[5];

void debug()
{
    puts("");
    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", a[i].c_str());
    }
    puts("");
}

int main(void)
{
    int kase = 0;
    bool first = 1;
    while (true)
    {
        // 每一次都要把矩阵清零
        for (int i = 0; i < 5; i++)
            a[i] = "";
        // 开始读入
        char ch = getchar();
        if (ch == '\n') ch = getchar(); // 过滤换行
        if (ch == 'Z') return 0;        // 如果是Z就直接退出程序
        a[0] += ch;                     // 否则将ch接到a[0]后面
        string s;
        for (int i = 0; i < 5; i++)
        {
            getline(cin, s, '\n');
            a[i] += s;
        }
        getline(cin, s, '0');      // 读入以0结尾的指令串

        // debug();

        // 开始处理指令
        // 寻找空格位置
        int p = 0, q = 0;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (a[i][j] == ' ')
                {
                    p = i;
                    q = j;
                    break;
                }
        bool flag = false;
        int len = s.size();
        for (int i = 0; i < len; i++)
        {
            // debug();

            // 分别处理四种指令
            if (s[i] == 'A')
            {
                if (p - 1 < 0)
                {
                    flag = true;
                    break;
                }
                a[p][q] = a[p-1][q];
                a[p-1][q] = ' ';
                // 操作完之后空格上移了一行
                p--;
            }
            else if (s[i] == 'B')
            {
                if (p + 1 >= 5)
                {
                    flag = true;
                    break;
                }
                a[p][q] = a[p+1][q];
                a[p+1][q] = ' ';
                // 操作完之后空格下移了一行
                p++;
            }
            else if (s[i] == 'L')
            {
                if (q - 1 < 0) 
                {
                    flag = true;
                    break;
                }
                a[p][q] = a[p][q-1];
                a[p][q-1] = ' ';
                // 空格左移
                q--;
            }
            else if (s[i] == 'R')
            {
                if (q + 1 >= 5)
                {
                    flag = true;
                    break;
                }
                a[p][q] = a[p][q+1];
                a[p][q+1] = ' ';
                // 空格右移
                q++;
            }
            // 每次处理完都输出矩阵
            // debug();
        }

        // 开始输出
        if (!first) putchar('\n'); // 如果不是第一组数据就换行
        if (first) first = 0;      // 如果是第一组数据就将first设置为false
        printf("Puzzle #%d:\n", ++kase);
        if (flag) puts(error);     // 如果无解则输出错误信息
        else                       // 否则输出该puzzle
        {
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 4; j++)
                    printf("%c ", a[i][j]);
                putchar(a[i][4]);  // UVA要求行末无空格
                putchar('\n');
            }
        }
    }    
    return 0;
}
```

---

## 作者：封禁用户 (赞：7)

### 伟大的C++题解来啦！

~~没有C++题解，我真的慌啊~~

于是，我打算拯救C++的同胞们！

这题。。。很明显的模拟啦～～～

不过，这道需要字符串处理~~(对C++字符串处理不熟悉的我WA了n次啊)~~

我们将$5* 5$的数组读进来后，操作字符全读入再操作，用离线操作，不用在线操作~~(反正这不是交互题)~~

下附代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char m[8][8];
char mr[10050];
int main()
{
    char c;int cc=1;
    while(1)
    {
        memset(mr,'\0',sizeof(mr));//清空数组
        if (cc>1) getchar();//让没有用的‘\n’滚蛋
        c=getchar();
        if (c=='Z') return 0;//其实，这里有个小漏洞，但是，AC了就好
        if (cc!=1) cout<<endl;//按题意输出
        m[1][1]=c;
        for (int i=1;i<=5;i++)
        {
            int j;
            for (j=1;j<=5;j++)
            {
                if(i==1&&j==1) continue;//第一个已经读过了，就不要再读了
                m[i][j]=getchar();
            }
            getchar();//除掉‘\n’
        }
        int x,y;
        for (int i=1;i<=5;i++)
          for (int j=1;j<=5;j++)
            if (m[i][j]==' ')//寻找到原始图像中的空格的位置
            {
				x=i;
				y=j;//记录一下
			}
        int i=0;
        while (1)//处理操作符
        {
            char x;
            cin>>x;
            mr[i++]=x;
            if (x=='0') break;
        }
        int l=strlen(mr);bool flag=true;
        for (int i=0;i<l-1;i++)//进行操作
        {
            char ch=mr[i],t;
            if (ch=='A')
            {
                if(x-1<1)
				{
					flag=false;
					break;
				}
                t=m[x-1][y];
				m[x-1][y]=' ';
				m[x][y]=t;
                x=x-1;
            }
            else if (ch=='B')
            {
                if(x+1>5)
				{
					flag=false;
					break;
				}
                t=m[x+1][y];
				m[x+1][y]=' ';
				m[x][y]=t;
                x=x+1;
            }
            else if (ch=='L')
            {
                if(y-1<1)
				{
					flag=false;
					break;
				}
                t=m[x][y-1];
				m[x][y-1]=' ';
				m[x][y]=t;
                y=y-1;
            }
            else if (ch=='R')
            {
                if(y+1>5)
				{
					flag=false;
					break;
				}
                t=m[x][y+1];
				m[x][y+1]=' ';
				m[x][y]=t;
                y=y+1;
            }
            else
			{
				flag=false;
				break;
			}
        }
        printf("Puzzle #%d:\n",cc++);
        if(flag==false)
            printf("This puzzle has no final configuration.\n");
        else
            for(int i=1;i<=5;i++)
            {
                for(int j=1;j<=5;j++)
                {
                    if(j==1)
                        cout<<m[i][j];
                    else
                        cout<<" "<<m[i][j];
                }
                cout<<endl;
            }
    }
    return 0;
}
```

---

## 作者：zylll (赞：6)

不难的模拟题，考输入输出。

真的调这种东西心态爆炸。。。

要认真看题目。。。

对于棋盘，先读入第一行。要特判一些东西。

对于命令，则使用**string**的骚操作，直接累加最后汇到总命令中。

然后一个getchar()把那个\n读掉。

然后就模拟情况。

注意，对于总命令中最后一个值如果不是0也算是违法。。。

然后就是奇怪的输出，注意格式。

真的很想调侃一下啊。。。。耗了许多时间。

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <iostream>
#include <algorithm>
static const int MAXN=10;
using namespace std;
char s[MAXN][MAXN];
bool flag;
int cnt;
string ins,opt;
inline bool get_line(char* s){
	char c;
	for(int i=0;(c=getchar())!='\n';i++){
		if(c==EOF) return false;
		s[i]=c;
	}
	return true;
}
inline void find_pos(int& x,int& y){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(s[i][j]==' '){
				x=i;y=j;
				return ;
			}
		}
	}
}
inline void init(){
	memset(s,' ',sizeof(s));
	opt.clear();
	flag=false;
}
int main(){
	while(1){
		init();
		if(!get_line(s[0])||s[0][0]=='Z') return 0;
		if(cnt) printf("\n");
		for(int i=1;i<=4;i++) if(!get_line(s[i])) return 0;
		int x,y; 
		find_pos(x,y);
		while(1){
			cin>>ins;opt+=ins;
			ins.clear();
			if(opt[opt.length()-1]=='0') break;
		}
		getchar();
		for(int i=0;i<opt.length()-1;i++){
			if(flag) break;
			if(opt[i]=='A'){
				if(x==0){
					flag=true;
					continue;
				}
				swap(s[x][y],s[x-1][y]);
				x--;
			}
			else if(opt[i]=='B'){
				if(x==4){
					flag=true;
					continue;
				}
				swap(s[x][y],s[x+1][y]);
				x++;
			}
			else if(opt[i]=='L'){
				if(y==0){
					flag=true;
					continue;
				}
				swap(s[x][y],s[x][y-1]);
				y--;
			}
			else if(opt[i]=='R'){
				if(y==4){
					flag=true;
					continue;
				}
				swap(s[x][y],s[x][y+1]);
				y++;
			}
			else if(opt[i]!='0'){
				flag=true;
				continue;
			}
		}
		printf("Puzzle #%d:\n",++cnt);
		if(!flag){
			for(int i=0;i<5;i++){
				for(int j=0;j<5;j++){
					printf("%c%c",s[i][j],j==4?'\n':' ');
				}
			}
		}
		else printf("This puzzle has no final configuration.\n");
		flag=false;
	}
	return 0;
}
```

---

## 作者：AlienZhan (赞：4)

萌新的第一篇题解

本题模拟即可，先特判Z决定循环是否继续，然后把谜面存入二维字符数组，找到空格的位置，之后就好操作了

- **本题主要注意“输出”格式**

- **输入中的“空格”在每行最后一个位置时，实际上那不是空格而是换行符**

- **使用scanf和gechar时要注意换行符的回收，防止下一次直接读取空格导致出错**

- **注意谜题解之间要有空行，但最后的解之后仅换行**

- **解的每行最后一个字符后无空格**

- **出现WA可能实际是PE，即结果表达错误，记得检查Uva的邮件确认**

以下是代码：
```c
#include<stdio.h>
#define R 5
#define C 5
int n = 0;	//用于记录谜题数
int main() 
{
    while (1)
    {
        char p[R][C] = { 0 };		//初始化，重置数组
        int r, c;			//用于记录空格位置
        for (int i = 0; i < R; ++i)
        {
            for (int j = 0; j < C; ++j)
            {
                scanf("%c", &p[i][j]);
                if (p[0][0] == 'Z') 
                    return 0;		//判断第一个输入的字符是不是'Z'，若是，直接结束
                if (p[i][j] == ' ' || p[i][j] == '\n')//如果找到空格或者行末为换行
                {
                    r = i; c = j;	//则记录该位置
                }
            }
            if (p[i][4] != '\n')
                getchar();		//如果行末不是换行，回收接下输入的换行符，避免被scanf读取
        }
        p[r][c] = ' ';			//如果空格的位置实际是换行，则把换行符换成空格
        char cc; int r1 = r, c1 = c, cnt = 0;	//cnt用来记录非法指令
        while ((cc = getchar()) != '0')		//读取指令并判断指令是否结束
        {
            if (cc != 'A' && cc != 'B' && cc != 'L' && cc != 'R' && cc != '\n')
            //判断是否有非法指令，注意'\n'是可以存在的
            {
                ++cnt;
            }
            else if (cc == 'A')
            {
                if (r - 1 >= 0)
                    r1 = r - 1;		//合法则记下操作位置
                else ++cnt;		//不合法则记录，下同
            }
            else if (cc == 'B')
            {
                if (r + 1 < R)
                    r1 = r + 1; 
                else ++cnt;
            }
            else if (cc == 'L')
            {
                if (c - 1 >= 0)
                    c1 = c - 1;
                else ++cnt;
            }
            else if (cc == 'R')
            {
                if (c + 1 < C)
                    c1 = c + 1;
                else ++cnt;
            }
            p[r][c] = p[r1][c1]; p[r1][c1] = ' ';	//执行合法的指令
            r = r1; c = c1;		//重新记录空格位置
        }
        getchar();	//回收输入'0'之后多余的换行，防止被在下一个谜题输入时被scanf读取
        if (n)printf("\n");	//根据谜题数判断是否要在谜题解之前输出空行，第一个解之前不输出
        ++n; 		//增加谜题序数，使其变为当前谜题序数
        printf("Puzzle #%d:\n", n);
        if (cnt)	//判断是否出现了非法操作，有则打印无解 
            printf("This puzzle has no final configuration.\n");
        else   		//无则输出结果
            for (int i = 0; i < R; ++i)
            {
                for (int j = 0; j < C; ++j)
                {
                    if (j == 0)
                        printf("%c", p[i][j]);		//每行第一个字符前不打印空格
                    else
                        printf(" %c", p[i][j]);		//通过在字符前打印空格，实现每行最后一个字符后无空格
                }
                printf("\n");	//打印完一行则换一次行
            }
    }
    return 0;
}
```


---

## 作者：__天__ (赞：3)

看了很多题的题解，绝大部分都是c或者c++的，就绕我来搞个Java版的
题目不难，有点水，就是输出需要仔细注意一点，还是初学者，我就用的最暴力的方法解出来的，难的也不会。第一次写，求过
```java
import java.util.*;
public class lalala {
    public static void main(String args[]) {
        Scanner reader = new Scanner(System.in);
        int g = 0;// 游戏序号
        while (reader.hasNext()) {
            int e = 0;
            char a = ' ';
            char[][] c = new char[5][5];// 存放5行5列的方格
            for (int i = 0; i < 5; i++) {
                String s = reader.nextLine();
                if (s.length() < 5) {
                    s += " ";// 如果空格在莫一行的最后一个，将空格添加进去
                }
                char[] d = new char[5];
                d = s.toCharArray();
                if (d[0] == 'Z') {
                    a = 'Z';
                    break;
                }
                for (int j = 0; j < 5; j++) {
                    c[i][j] = d[j];// 把每一行读入的字符串一次存放进数组
                }
            }
            if (a == 'Z') {
                break;
            }
            String s1 = reader.nextLine();// 读取指令行列
            for (;;) {
                if (s1.charAt(s1.length() - 1) != '0') {
                    s1 += reader.nextLine();
                } else {
                    break;
                }// 不读到0就一直读取
            }
            for (int k = 0; k < s1.length() - 1; k++) {
                if (s1.charAt(k) == 'A') {
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 5; j++) {
                            if (c[i][j] == ' ') {
                                if (i - 1 < 0) {
                                    e = 1;
                                    break;
                                }// 如果指令非法，标记e，跳出循环
                                c[i][j] = c[i - 1][j];
                                c[i - 1][j] = ' ';
                                e = 2;
                                break;// 交换完成，跳出此次循环
                            }
                        }
                        if (e == 2) {
                            e = 0;
                            break;
                        }// 还原e，继续跳出循环，执行下一个指令
                        if (e == 1)
                            break;// 直接跳出
                    }
                    if (e == 1)
                        break;
                }
                if (s1.charAt(k) == 'B') {
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 5; j++) {
                            if (c[i][j] == ' ') {
                                if (i + 1 > 4) {
                                    e = 1;
                                    break;
                                }
                                c[i][j] = c[i + 1][j];
                                c[i + 1][j] = ' ';
                                e = 2;
                                break;
                            }
                        }
                        if (e == 2) {
                            e = 0;
                            break;
                        }
                        if (e == 1)
                            break;
                    }
                    if (e == 1)
                        break;
                }
                if (s1.charAt(k) == 'L') {
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 5; j++) {
                            if (c[i][j] == ' ') {
                                if (j - 1 < 0) {
                                    e = 1;
                                    break;
                                }
                                c[i][j] = c[i][j - 1];
                                c[i][j - 1] = ' ';
                                e = 2;
                                break;
                            }
                        }
                        if (e == 2) {
                            e = 0;
                            break;
                        }
                        if (e == 1)
                            break;
                    }
                    if (e == 1)
                        break;
                }
                if (s1.charAt(k) == 'R') {
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 5; j++) {
                            if (c[i][j] == ' ') {
                                if (j + 1 > 4) {
                                    e = 1;
                                    break;
                                }
                                c[i][j] = c[i][j + 1];
                                c[i][j + 1] = ' ';
                                e = 2;
                                break;
                            }
                        }
                        if (e == 2) {
                            e = 0;
                            break;
                        }
                        if (e == 1)
                            break;
                    }
                }
                if (e == 1)
                    break;
            }
            if (++g>1) {
                System.out.println();
            }
            System.out.println("Puzzle #" + g + ":");// 标题输出
            if (e == 1) {
                System.out.println("This puzzle has no final configuration.");// 非法指令输出
            } 
            else {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5; j++) {
                        if (j == 4) {
                            System.out.print(c[i][j]);
                            break;
                        }
                        System.out.print(c[i][j] + " ");
                    }
                    System.out.println();
                }
            }
        }
    }
}
```

---

## 作者：Vincent9966 (赞：1)

#### **~~这个题实属水题~~， 暴力模拟，需要注意的就是答案输入输出的处理**

##### 话不多说，上代码：
```c
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

#define _for(i, a, b) for (int i = (a); i < (b); ++i)
const int N = 10;
char g[N][N];
int dx[] = { -1, 0, 1, 0 }, dy[] = { 0, 1, 0, -1 };
int x, y;
bool first = true;

inline bool init() {
	if (!first) getchar();

	_for(i, 0, 5) {
		_for(j, 0, 5) {
			g[i][j] = getchar();
			if (g[i][j] == 'Z') return false;
			if (g[i][j] == ' ') x = i, y = j;
		}

		if (g[i][4] == '\n') {
			g[i][4] = ' ';
			x = i, y = 4;
		}
		else getchar();
	}
	return true;
}

inline bool slove() {
	char op;
	bool flag = true;

	while ((op = getchar()) != '0') {
		int opt;
		if (op == 'A') opt = 0;
		else if (op == 'R') opt = 1;
		else if (op == 'B') opt = 2;
		else if (op == 'L') opt = 3;
		else continue;

		int a = x + dx[opt], b = y + dy[opt];
		if (a >= 0 && a < 5 && b >= 0 && b < 5) {
			swap(g[x][y], g[a][b]);
			x = a, y = b;
		}
		else flag = false;
	}
	return flag;
}

int main() {
	int cnt = 0;

	while (init()) {
		if (first) first = false;
		else puts("");

		printf("Puzzle #%d:\n", ++cnt);
		if (slove()) {
			_for(i, 0, 5) {
				_for(j, 0, 5) printf("%s%c",(j ? " " : ""), g[i][j]);
				puts("");
			}
		}
		else puts("This puzzle has no final configuration.");
	}
	return 0;
}
```


---

## 作者：天轰穿 (赞：1)

考虑到一个5*5的表格里面的坐标如下，我们填充的时候按照 行为x，竖为y

00 01 02 03 04

10 11 12 13 14

20 21 22 23 24

30 31 32 33 34

40 41 42 43 44

那么表格中的任何一个格子的上、下均可设置为在行上 加一或者减一， 而右左则可以设置为竖上加一或者减一
按这个思路，操作只有四个方向，上则x-1，y不动，左则y1-，x不动 
要在行上左右移动，那就 x 做加减
要在列上上下移动，那就 y 做加减 

具体实现就简单了

1、把5*5的方阵读取到数组中去，并且把空格的具体坐标找到

2、拆分操作字符，一个个去移动操作

3、打印出操作后的数组 或者 无法操作这个结果 

```c
#include<stdio.h>
#include<string.h>
#include <ctype.h>
#define maxn 5

//用户输入的谜题 
char a[maxn][maxn];

int main() {
    int t = 0;			//申明变量t 作为每一段的标题计数器 
    while(gets(a[0])) {//注意读的是第一行到数组第一行gets()函数的作用和scanf()差不多，但不同的是他能够把空格读出来，而不是跳过 

        if(a[0][0] ==0) {	//如果出现在循环开始时候读取第一格得不到东西，那么就继续读取值来填充第一行
			gets(a[0]);
		}
		
		if(a[0][0] == 'Z') 
			break;//判断读取到的这一行的第一个字母是Z，就完全终止本轮循环 
		
		
        int m = 0, n = 0;	//用两个时变量，在循环中找到空格就存坐标，存下来，等后面输入方向的时候才有个依据撒 
        
        //这里只读4行，再读就读到操作命令哪一行了，而且必须从第二行开始读，第一行被他的循环爸爸读过了 
		for(int i = 0; i <= 4; ++i) {
        	//如果i=0，就不读，因为外层循环已经读过了 
        	//因为，样例输入是输入多段 
            if(i)
				gets(a[i]);
				
            // 每读一行就循环当前行的列，去找下是否有空格，有的话就把空格的坐标存下来 
            for(int j = 0; j <= 4; ++j) {
                if(a[i][j] == ' '||a[i][j] == 0) {	//如果为空 或者 为0，就表示抓到了 
                    a[i][j] = ' ';					//将这一格设置为 空 
                    m = i; n = j;					//将空的位置记下来
                    break; 				//反正里面只会有一个空格，只要找到了就没有必要继续循环这一行了，就跳出去，能节约一步算一步啊 
                }
            }
        }
        

        //读取操作命令字符串，实施移动，两种情况表示操作无效    操作符无效 和 把表格插破了  
        //这里是利用getchar()一个个字符的读取，读一个操作一次 
        bool ok = true;			//设置一个标识符，如果移动的时候找不到路了，就标识为非，给后面的人说这是个错 
        for (;;) {				//花样死循环（要不是我是做教程，我自己都忘记了还有这么多作死的方法，哇哈哈哈哈哈） 
            char c = getchar();	//getchar()对屏幕上的字符依次读取，别问我他读是什么，反正就是依次，该函数以无符号 char 强制转换为 int 的形式返回读取的字符，如果到达文件末尾或发生读错误，则返回 EOF。 
            
            if(isspace(c)){		//isspace(c)：检查参数c是否为空白字符，是为真，否为假 
            	ok = false;
			}				
				
			if (c == '0') {		//如果遇到0，表示结束了，不用继续了 				
                break;			//跳出循环 
            }
            
            int x=m,y=n;			//m和n要记录原来的，不能拿来运算，所以搞两个新变量来计算，并作为新位置的记录
            //根据命令计算空格要移动的目标格子的坐标 
            if(c=='A'){			//向上-1 
            	x-=1;
			} 
			else if(c=='B'){	//向下+1 
            	x+=1;
			}
			else if(c=='L'){	//向左-1 
            	y-=1;
			} 
			else if(c=='R'){	//向右+1 
            	y+=1;
			} 
            
            //看看坐标还对不对，别都跑到火星上去了(超出数组界限了) 
            if (x < 0 || x > 4 || y < 0 || y > 4) {	//如果超过表格的限制       
                ok = false;	//设置标志为 非 
                
                //特别注意一下，这个破地方，本循环是一次只读一个字符，这里直接就跳出去的话，屏幕上的字还没读完，所以必须把剩下的读完
				while(c!='\n'){
					c=getchar();
				}
                
                break;		//结束循环，只要有一个不对，后面的都没必要继续了 
            }
            
            a[m][n] = a[x][y];	//将移动位置上的字母给空的位置
            a[x][y] = ' ';		//将新位置为空
            m = x, n = y;		//重新记新的位置
        }

        //输出
        if (t) {		//如果不是第一段，就给一个换行 
            puts("");		//作用与printf("\n")相同,这个主要用于输出字符串并换行，但不如printf还能格式化 
        }
        
        printf("Puzzle #%d:\n", ++t);
        if (ok) {
            for(int i = 0; i <= 4; ++i) {		//循环输出行 
                for(int j = 0; j <= 4; ++j) {	//循环输出列 
                    if (j) {					//一个字符前面不要空，后面都是每个字符一个空格 
                        printf(" ");			//输空格用的，最后字母后没空格
                    }
                    printf("%c", a[i][j]);
                }
                puts("");						//换行 ,当前这个等同于 printf("/n") 
            }
        }
        else {
            puts("This puzzle has no final configuration.");
        }
    }
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

[此题](https://www.luogu.com.cn/problem/UVA227)坑点不少

1. 要正确处理空格和换行的问题，所以应该选用 getchar 进行读入。
1. 如何交换空格与周围方格。
1. 注意第 5 列后不得出现空格，否则喜提 Presentation Error.
1. 还有每次 Puzzle 之间有 1 行间隙。

所以我的思路是：将空格替换为数字（题目说了网格中不存在数字），并直接进行交换操作，最后把交换后数字的位置保留位空位即可。

```
// Problem: UVA227 谜题 Puzzle
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/UVA227
// Memory Limit: 0 MB
// Time Limit: 3000 ms
//
// Powered by CP Editor (https://cpeditor.org)
#include <bits/stdc++.h>
using namespace std;

int cnt;   //统计第 n 个 Puzzle
int x, y;  //记录空格位置
char maps[7][7];
bool flag;

bool moved(bool pd) {//判断是否存在非法操作以及进行交换处理
  char moves;
  while ((moves = getchar()) != '0') {
    // printf("%c", moves);
    if (moves != 'A' && moves != 'B' && moves != 'L' && moves != 'R' &&
        moves != '\n') {
      ++pd;
    } else if (moves == 'A') {
      if (x - 1 >= 1)
        swap(maps[x][y], maps[x - 1][y]), x--;
      else
        ++pd;
    } else if (moves == 'B') {
      if (x + 1 <= 5)
        swap(maps[x][y], maps[x + 1][y]), x++;
      else
        ++pd;
    } else if (moves == 'L') {
      if (y - 1 >= 1)
        swap(maps[x][y], maps[x][y - 1]), y--;
      else
        ++pd;
    } else if (moves == 'R') {
      if (y + 1 <= 5)
        swap(maps[x][y], maps[x][y + 1]), y++;
      else
        ++pd;
    }
  }
  getchar();
  return pd;//返回值不为 0 则存在非法操作
}
int main() {
  // init();

  while (++cnt) {
    flag = 0;

    for (int i = 1; i <= 5; i++) {
      for (int j = 1; j <= 5; j++) {
        scanf("%c", &maps[i][j]);
        if (maps[1][1] == 'Z') return 0;
        if (maps[i][j] == ' ' || maps[i][j] == '\n') x = i, y = j;//记录原网格中空格位置
      }
      if (maps[i][5] != '\n') getchar();//吃掉换行
    }
    maps[x][y] = '2';//将原网格中的空格位置替换为数字 2
    if (cnt != 1) printf("\n");//第 1 个 Puzzle 上面无空行
    printf("Puzzle #%d:\n", cnt);
    if (moved(flag))
      printf("This puzzle has no final configuration.\n");
    else {
      for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
          if (maps[i][j] == '2') {
            if (j != 5)
              printf("  ");
            else if (j == 5)
              printf(" ");
          } else {
            if (j != 5)
              printf("%c ", maps[i][j]);
            else if (j == 5)
              printf("%c", maps[i][j]);
          }
        }
        printf("\n");
      }
    }
  }
  return 0;
}
```

[AC 记录见此](https://www.luogu.com.cn/record/69021849)。

---

## 作者：wangzeyu (赞：0)

## 一道模拟题

只需要按照题目的说明，按照要求执行就可以了。  
字符串处理可能会很~~麻烦~~

## 提示

1. 注意换行符，UVA的换行符是 '\\n' ，注意每读完一行都要用 getchar() 跳过一个换行符，否则矩阵中的内容会乱。
2. 输入的指令可能不在一行里，因此要处理中间的换行符。
3. 这道题要多次循环，**注意清空和初始化**
4. 虽然可以一次性读入完再处理，但是我~~个人习惯~~读一个处理一个

## 下面是代码

```C++
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string.h>
using namespace std;
bool is_illegal=false;char temp[5]; char letter;
char table[5][5];//用于储存谜题的内容 标号从0起
int space_x,space_y;//空格的x，y坐标
char order;//x,y
long long question_number=0;//用于记录数据的组数
void move(char ope)
{
	switch (ope)
	{
		case 'A':
			if(space_y==4)//判断边界
			{
				is_illegal=true;break;
			}
			else
			{
				letter=table[space_x][space_y+1];//取这个格子上方的字母
				table[space_x][space_y+1]=' ';//将上方标记为空格
				table[space_x][space_y]=letter;//将当前格更改为字母
				space_y++;break;//更新空格的坐标
			}
			/*以下的三个和上边的原理类似，不在注释*/
		case 'B':
			if(space_y==0)
			{
				is_illegal=true;break;
			}
			else
			{
				letter=table[space_x][space_y-1];
				table[space_x][space_y-1]=' ';
				table[space_x][space_y]=letter;
				space_y--;break;
			}
		case'L':
			if(space_x==0)
			{
				is_illegal=true;break;
			}
			else
			{
				letter=table[space_x-1][space_y];
				table[space_x-1][space_y]=' ';
				table[space_x][space_y]=letter;
				space_x--;break;
			}
		case'R':
			if(space_x==4)
			{
				is_illegal=true;break;
			}
			else
			{
				letter=table[space_x+1][space_y];
				table[space_x+1][space_y]=' ';
				table[space_x][space_y]=letter;
				space_x++;break;
			}		
	}
}
int main()
{
	for(;;)
	{
		is_illegal=false;//初始化
		question_number++;
		for(int y=4;y>=0;y--)//我的代码中以puzzle的左下角为坐标原点，横向为x轴，纵向为y轴
		{
			for(int x=0;x<=4;x++)
			{
			/*此题中由于空格的位置是不确定的，因此只能使用逐字符读入*/
				table[x][y]=getchar();
				if(table[x][y]=='Z')
				{
					return 0;//读到Z就是结束
				}
				if(table[x][y]==' ')//读到空格时标记空格的x，y坐标
				{
					space_x=x;space_y=y;
				}
			}
			getchar();//处理输入数据行末的换行符
		}
		for(;;)
		{
			order=getchar();//开始处理指令
			if(order=='0')//读到0就是结束
			{
				break;
			}
			else
			{/*此时不需要判断是否非法，即使非法了也这样进行移动直到结束，因为有
			一个全局变量来判断，一旦曾经非法了，就不可能再合法了，所以移动也就无所谓了*/
				move(order);//移动空格
			}
		}
		getchar();//处理行末换行符，便于下一个格子的读入
		if(question_number!=1)
		{
			printf("\n");
		}
		/*因为题目要求在每一个puzzle过后空一行，也就是每一个puzzle过后输出两个换行符
		但是最后一个puzzle只能输出一个换行符，我们不知道什么时候结束，所以在每个puzzle开始时输出一个换行符(第一个除外)，最后再输出一个(适用于所有的)，就可以解决这个问题*/
		printf("Puzzle #%d:\n",question_number);
		if(is_illegal==true)//无解
		{
			printf("This puzzle has no final configuration.\n");
			continue;
		}
		else
		{
			for(int y=4;y>=0;y--)
			{
				for(int x=0;x<=4;x++)
				{
					printf("%c",table[x][y]);
					if(x!=4)
					{//最后一个字符之后不能有空格
						printf(" ");
					}
				}
					printf("\n");
			}
			continue;
		}	
	}
	return O;
}
```

## 对UVA使用的提示

1. UVA的题目为ACM赛制，只有一个测试点，正确得分，错误不得分。
2. UVA对格式非常敏感。当一行有多余一个元素时，中间必须使用要求的分隔符，并且行末**不允许有多余的空格**，否则按格式错误处理。
3. 最后一行输出完后，**必须换行且只能换一行**。对于中间有空行的题目（例如此题），最后一行输出完后也是只换一行，如果不换行或换多行，按格式错误处理。
4. 如果你使用了洛谷RemoteJudge做UVA的题，当洛谷上显示WA时，一定要登录UVA进行确认，因为洛谷不支持PE(Presentation Error 格式错误) 的显示，如果PE了洛谷会显示WA。
   有图为证
   ![在UVA提交被判格式错误，但是洛谷却显示WA](https://cdn.luogu.com.cn/upload/image_hosting/scpzrz68.png)  
   ![在UVA提交被判格式错误，但是洛谷却显示WA](https://cdn.luogu.com.cn/upload/image_hosting/u4n55xh5.png)  
   **做UVA的题要有耐心，我是提交了4次，重写了6次才通过，不要被~~卡格式~~阻拦了前进的脚步**
5. 为了节省时间，强烈建议使用UVA的result Email 服务~~（免费的)~~。

###### 温馨提示：代码已进行反作弊处理

如果CE了麻烦管理员修改以下，管理员辛苦了。

---

