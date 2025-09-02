# 古代象形符号 Ancient Messages

## 题目描述

为了理解早期文明，考古学家经常研究用古代语言编写的文本。在3000多年前的埃及使用的一种语言是基于称为象形文字的字符。如图显示了六个象形文字及其名称，在这个题目中，您需要编写一个程序来识别这六个字。

![]("C:\Users\白文礼\Desktop\4_1.png")

输入INPUT：
```

# 题解

## 作者：Anguei (赞：8)

**不是很明白为什么几乎所有人都要针对 $0-f$ 写十六次 `if` 判断，不累吗？万一出错，好调试吗？**

观察一下，可以发现：对于每个输入的十六进制字符，其代表的周围的像素数都与 $2$ 的幂有关。该数字越大，距离它越近的像素点就为 $1$；数字越小，距离远的就为 $1$。因为十六进制下的 $f$ 代表了四位二进制数字，所以只需要写 $4$ 个 `if` 就能够构造出图了。

```cpp
void input() {    
	const int hex[] = { 10, 11, 12, 13, 14, 15 }; // 十六进制字母部分的转换表
    for (int i = 1; i <= n; ++i) {
        scanf("%s", str + 1);
        for (int j = 1; j <= m; ++j) {
            int num = isdigit(str[j]) ? str[j] - 48 : hex[str[j] - 97]; // 十六进制转换
            if (num >= 8) map[i][((j - 1) << 2) + 1] = 1, num -= 8;
            if (num >= 4) map[i][((j - 1) << 2) + 2] = 1, num -= 4;
            if (num >= 2) map[i][((j - 1) << 2) + 3] = 1, num -= 2;
            if (num >= 1) map[i][((j - 1) << 2) + 4] = 1, num -= 1;
        }
    }
    m <<= 2;
    // 当然也可以用一次循环的方法代替 4 个 if，但 4 个 if 的写法已经够简单了，不想改了 QωQ。
}
```

剩下的就是 dfs 找连通块、判断圈数，应该没什么难的吧。如果实在不会可以参考楼下题解。

---

## 作者：happyZYM (赞：5)

首先，用一个表来解决输入问题（也可以动态生成）。
通过观察我们可以发现：每一个字符中的“白洞洞”的个数都不一样，因此可以用dfs数出每一个黑的联通块（字符）中的白洞洞的个数，加以区分。
细节得特别注意，代码如下：
```cpp
#include<cstdio>
#include<cstring>
//#include<conio.h>
const int maxn=205;
int mp[maxn][maxn];
char s[maxn];
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
int H,W;
#define set(a,b,c,d) mp[i][j<<2]=a,mp[i][(j<<2)+1]=b,mp[i][(j<<2)+2]=c,mp[i][(j<<2)+3]=d;
void init()
{
	for(int i=0;i<H;i++)
	{
		scanf("%s",s);
		for(int j=0;j<W;j++)
			switch(s[j])
			{
				case '0':set(0,0,0,0);break;
				case '1':set(0,0,0,1);break;
				case '2':set(0,0,1,0);break;
				case '3':set(0,0,1,1);break;
				case '4':set(0,1,0,0);break;
				case '5':set(0,1,0,1);break;
				case '6':set(0,1,1,0);break;
				case '7':set(0,1,1,1);break;
				case '8':set(1,0,0,0);break;
				case '9':set(1,0,0,1);break;
				case 'a':set(1,0,1,0);break;
				case 'b':set(1,0,1,1);break;
				case 'c':set(1,1,0,0);break;
				case 'd':set(1,1,0,1);break;
				case 'e':set(1,1,1,0);break;
				case 'f':set(1,1,1,1);break;
			}
	}
	W<<=2;
}
void dfs1(int y,int x,int co)
{
	if(y<0||y>=H||x<0||x>=W) return;
	if(mp[y][x]==-1||mp[y][x]!=co) return;
	mp[y][x]=-1;
	for(int i=0;i<4;i++)
		dfs1(y+dy[i],x+dx[i],co);
}
int dfs2(int y,int x)
{
	if(y<0||y>=H||x<0||x>=W) return 0;
	if(mp[y][x]==-1) return 0;
	int res=0;
	if(mp[y][x]==1)
	{
		mp[y][x]=-1;//注意！这玩意得放到里面来！
		for(int i=0;i<4;i++)
			res+=dfs2(y+dy[i],x+dx[i]);
	}
	else
	{
//		printf("\t\t\tfound zero! at x=%d y=%d\n",x,y);
		dfs1(y,x,0);
		return 1;
	}
	return res;
}
int cnt;
void print()
{
	for(int i=0;i<H;i++)
	{
		printf("\t");
		for(int j=0;j<W;j++) printf("%3d",mp[i][j]);
		printf("\n");
	}
}
void solve()
{
	for(int i=0;i<H;i++)
	{
		if(mp[i][0]==0) dfs1(i,0,0);
		if(mp[i][W-1]==0) dfs1(i,W-1,0);
	}
	for(int i=0;i<W;i++)
	{
		if(mp[0][i]==0) dfs1(0,i,0);
		if(mp[H-1][i]==0) dfs1(H-1,i,0);
	}
	int A,D,J,K,S,w;//w要小写（有个叫W的全局变量）
	A=D=J=K=S=w=0;
//	printf("process finished! H=%d W=%d\n",H,W);
//	print();
	for(int i=0;i<H;i++)
		for(int j=0;j<W;j++)
		{
//			printf("mp[%d][%d]=%d\n",i,j,mp[i][j]);
			if(mp[i][j]==1)
			{
//				printf("\t123\n");
				int t;
				switch(t=dfs2(i,j))
				{
					case 1:A++;break;
					case 3:J++;break;
					case 5:D++;break;
					case 4:S++;break;
					case 0:w++;break;
					case 2:K++;break;
				}
//				printf("\t\tfind %d holes at x=%d y=%d\n",t,j,i);
//				print();
//				getch();
			}
		}
	printf("Case %d: ",++cnt);
	while(A-->0) putchar('A');
	while(D-->0) putchar('D');
	while(J-->0) putchar('J');
	while(K-->0) putchar('K');
	while(S-->0) putchar('S');
	while(w-->0) putchar('W');
	printf("\n");
}
int main()
{
	while(scanf("%d%d",&H,&W)==2&&H&&W)
	{
		init();
		solve();
	}
	return 0;
}
```

---

## 作者：fanfansann (赞：4)

## 题目翻译
为了识别3000年前古埃及用到的6种象形文字。每组数据包含一个H行W列的字符矩阵（H≤200，W≤50 ），每个字符为4个相邻像素点的十六进制（例如，10011100对应的字符就是9c）。转化为二进制后1表示黑点，0表示白点。输入满足以下条件：

不会出现上述6种符号之外的其他符号。
输入至少包含一个符号，且每个黑像素都属于一个符号。输入至少包含一个符号，且每个黑像素都属于一个符号。
每个符号都是一个四连块，并且不同符号不会相互接触，也不会相互包含。
如果两个黑像素有公共顶点，则它们一定有一个相同的相邻黑像素（有公共边）。
符号的形状一定和题中的图形拓扑等价（可以随意拉伸但不能拉断）。

要求按照字典序输出出现的所有符号。

 ![在这里插入图片描述](https://img-blog.csdnimg.cn/20200218204121601.png)
 
输出说明：
For each test case, display its case number followed by a string containing one character for each
hieroglyph recognized in the image, using the following code:
Ankh: A
Wedjat: J
Djed: D
Scarab: S
Was: W
Akhet: K
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200218204132611.png)
**Sample Input**

```csharp
100 25
0000000000000000000000000
0000000000000000000000000
...(50 lines omitted)...
00001fe0000000000007c0000
00003fe0000000000007c0000
...(44 lines omitted)...
0000000000000000000000000
0000000000000000000000000
150 38
00000000000000000000000000000000000000
00000000000000000000000000000000000000
...(75 lines omitted)...
0000000003fffffffffffffffff00000000000
0000000003fffffffffffffffff00000000000
...(69 lines omitted)...
00000000000000000000000000000000000000
00000000000000000000000000000000000000
0 0
```

**Sample Output**

```csharp
Case 1: AKW
Case 2: AAAAA
```
那么根据《算法竞赛入门经典（第二版）》中关于本题的分析
> “随意拉伸但不能拉断”是一个让人头疼的条件。怎么办呢？看来不能拘泥于细节，而要从全局考虑，找到一个易于计算，而且在“随意拉伸”时还不会改变的“特征量”，通过计算和比较“特征量”完成识别。题目说过，每个符号都是一个四连块，即所有黑点都连在一起，而中间有一些白色的“洞”。数一数就能发现，题目表中的6个符号从左到右依次有1，3，5，4，0，2个洞，各不相同。这样，只需要数一数输入的符号有几个“白洞”，就能准确地知道它是哪个符号了。

可以得知我们需要知道有几个白洞就好了
根据题意，我们需要把输入的十六进制转化为二进制来显示地图，1是黑边，0是白边。
那么我们用一个`unordered_map<char,string>f16t2`用来把十六进制转化为二进制地图，注意要把地图的一圈加上一层白边，然后进行深搜，先把黑边外面的所有的白点+2，然后再搜里面，有几个白洞用ans表示一下，并用`unordered_map<int,char>toans`找到答案并加到`result`里输出即可

[C++11 unordered_map详细介绍](https://blog.csdn.net/weixin_45697774/article/details/104382942)

以下代码必须在C++11的编译环境中才能编译通过

[最新版Code::Blocks如何设置C++11](https://blog.csdn.net/weixin_45697774/article/details/104381035)


—
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e3+7;
const ll mod=2147483647;
ll h,w,ans,dir[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
unordered_map<char,string>f16t2={//把十六进制转换成二进制
  {'0',"0000"}, {'1',"0001"}, {'2',"0010"}, {'3',"0011"},
  {'4',"0100"}, {'5',"0101"}, {'6',"0110"}, {'7',"0111"},
  {'8',"1000"}, {'9',"1001"}, {'a',"1010"}, {'b',"1011"},
  {'c',"1100"}, {'d',"1101"}, {'e',"1110"}, {'f',"1111"}
};
unordered_map<int,char>toans={{1,'A'},{3,'J'},{5,'D'},{4,'S'},{0,'W'},{2,'K'}};//根据白洞的数量判断答案
vector<string>mp;//存地图
void dfs(ll x,ll y,char ch,ll &ans)
{
    mp[x][y]=(char)(ch+2);//把1变成3，把2变成4
    for(int k=0;k<4;++k)
    {
        ll nx=x+dir[k][0],ny=y+dir[k][1];//查连通块
        if(nx>=0&&nx<mp.size()&&ny>=0&&ny<mp[x].size()){
            if(ch=='1'&&mp[nx][ny]=='0'){//黑边里面有白洞就ans++
                ans++;
                dfs(nx,ny,'0',ans);
            }
            if(ch==mp[nx][ny])//两边相同就继续查下去
                dfs(nx,ny,ch,ans);
        }
    }
}
int main()
{
    int h,w;
    for(int ii=1;~scanf("%d%d%*c",&h,&w)&&h!=0;++ii){//%*c会自动忽略最后一个符号“*”符:用以表示该输入项,读入后不赋予相应的变量，即跳过该输入值。
        mp.resize(h+2);//分配内存
        mp.front()=string(w*4+2,'0');//填一层白边
        for(int i=1;i<=h;++i)
        {
            mp[i]="0";//再填一层白边
            string s;
            getline(cin,s);
            for(char ch:s)
                mp[i]+=f16t2[ch];//利用string的特性更方便
            mp[i]+="0";//再填一层白边
        }
        mp.back()=string(w*4+2,'0');//再填一层白边
        ll ans=0;
        string result="";//答案
        dfs(0,0,'0',ans);//先把外层的0搜完并全部改成2
        for(int i=0;i<mp.size();++i)
            for(int j=0;j<mp[i].size();++j){
                if(mp[i][j]=='1')
                {
                    ans=0;
                    dfs(i,j,'1',ans);
                    result+=toans[ans];//收集答案
                }
            }
        sort(result.begin(),result.end());//按字典序排序
        printf("Case %d: %s\n",ii,result.c_str());//把string转换成C语言风格的字符串再用printf输出
    }
    return 0;
}
```


---

## 作者：saipubw (赞：4)


首先，注意到不同象形符号内部的白块数量是不同的，并且一个象形符号的所有黑色像素都在一个联通块内。

思路如下：

1.读取数据，通过位运算将16进制转换为2进制。

2.dfs整张图的白色联通块

        当白色联通块触碰到边界->一定是白色背景
    
        否则，是象形符号内部的白块
    
            ->用一个数组w_in_b记录这个联通块
        
            实际上记录的是每一次dfs的初始坐标x,y
        
3.dfs整张图的黑色联通块

        任意一个黑色联通块都代表了一个象形符号，
    
        对整张图建一个color数组并赋值
        黑色像素的color值等于其所在联通块（象形文字）的编号。
    
4.统计每个黑色联通块（象形符号）内部的白块数量

        在w_in_b数组里，我们记录下了所有白色联通块（白色背景除外）
    
        这个白色联通块一定被一个黑色联通块包裹
    
        所以对之前记录的x,y，任取一个方向做while循环，直到找到黑色像素。
        则这个白色联通块属于该黑色像素对应的象形文字。
        具体是哪个象形文字根据黑色像素的color值来判断。
        
5.根据白块数量，将其转换为要输出的字符，并根据字典序排序，输出。

代码如下：
```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_weight 200
const int dir[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
int(*map)[max_weight];//图片
int(*color)[max_weight];//白色像素:染色，黑色像素：染色并记录该像素所属的象形文字编号
int(*w_in_b)[2];//白色联通块
int(*sta_data);//统计各个象形文字的联通块数量
int H, W, count=0,num_data=0;
void raw(void);//初始化
void do_input(void);
int dfs(int x,int y);//dfs白色联通块计数
void dfs2(int x, int y, int num);//dfs黑色联通块
void do_dfs(void);
void do_output(void);
void to_BW(char ch,int x,int y);//通过位运算将16进制数据化为2进制像素
int comp(const void *p1, const void *p2);
int main(void)
{
	while (scanf("%d%d", &H, &W) == 2 && H != 0 && W != 0)//多组数据
	{
		raw();//多组数据初始化
		do_input();
		W *= 4;//由于16进制转2进制，这里宽度要*=4
		do_dfs();//乱七八糟的dfs
		do_output();//数据处理输出
		free(map), free(color); free(w_in_b); free(sta_data);
	}
	return 0;
}
void raw(void)
{
	map=malloc(H*sizeof(int)*max_weight);
	color = calloc(H*max_weight,sizeof(int));
	w_in_b = calloc(H*W* 2, sizeof(int));
	count = 0;
	return;
}
void do_input(void)
{
	int i, j;
	char str[max_weight + 3];
	for (i = 0; i < H; i++)
	{
		scanf("%s", str);
		for (j = 0; j < W; j++)
			to_BW(str[j],i,j*4);
	}
	return;
}
int dfs(int x, int y)
{
	int i,ans=1;
	if (x >= H || x < 0 || y < 0 || y >= W) return 0;
	if (map[x][y] || color[x][y]) return 1;
	color[x][y] = 1;
	for (i = 0; i < 4; i++)
		if (dfs(x + dir[i][0], y + dir[i][1])==0) ans=0;
	return ans;
}
void do_dfs(void)
{
	int i, j,ans,num=1;
	for (i = 0; i < H; i++)
	{
		for (j = 0; j < W; j++)
		{
			ans=(color[i][j]||map[i][j])?0:dfs(i, j);
			if (ans) (w_in_b[count][0] = i, w_in_b[count++][1] = j);
		}
	}
	for (i = 0; i < H; i++)
		for (j = 0; j < W; j++)
			if (!color[i][j] && map[i][j]) dfs2(i, j,num++);
	sta_data = calloc(num, sizeof(int));
	sta_data[0] = num;
	return;
}
void do_output(void)
{
	int i,num=sta_data[0];
	for (i = 0; i < count; i++)
	{
		int x = w_in_b[i][0],y = w_in_b[i][1];
		while (!map[x][y]) x++;
		sta_data[color[x][y]]++;
	}
	for (i = 1; i < num; i++)
	{
		switch (sta_data[i])
		{
		case 0:
			sta_data[i] = 'W';
			break;
		case 1:
			sta_data[i] = 'A';
			break;
		case 2:
			sta_data[i] = 'K';
			break;
		case 3:
			sta_data[i] = 'J';
			break;
		case 4:
			sta_data[i] = 'S';
			break;
		case 5:
			sta_data[i] = 'D';
			break;
		default:
			sta_data[i] = 'w';
			break;
		}
	}
	sta_data[0] = 0x3f3f3f3f;
	qsort(sta_data, num, sizeof(int), comp);
	num--;
	printf("Case %d: ",++num_data);
	for (i = 0; i < num; i++)
		printf("%c", sta_data[i]);
	printf("\n");
	return;
}
void to_BW(char ch, int x, int y)
{
	unsigned int num;
	char str[2] = { ch,'\0' };
	int i;
	sscanf(str, "%x", &num);
	for (i = 3; i > 0; i--)
	{
		map[x][y+i] = (num & 1);
		num >>= 1;
	}
	map[x][y] = (num & 1);
	return;
}
void dfs2(int x, int y,int num)
{
	int i;
	if (x >= H || x<0 ||y<0||y >= W) return;
	if (!(!color[x][y] && map[x][y])) return;
	color[x][y] = num;
	for (i = 0; i < 4; i++)
		dfs2(x + dir[i][0], y + dir[i][1],num);
	return;
}
int comp(const void *p1, const void *p2)
{
	return *(int *)p1-*(int *)p2;
}

```

 最后，提供一个dubug网站：https://www.udebug.com/UVa/1103
 提交之前可以先过一下这里面的数据，基本能保证ac（~~然而我第一遍CE了~~）
 
 

---

## 作者：殇尘 (赞：2)

我的思路是先将白色区域染色，只留下文字内部的白色区域，然后在扫描文字时计算一下扫到的内部白色块，安装文字对应的内部空白数保存好答案，然后排序输出。
```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
struct node{
    int x, y;
} arr[60010];
struct queue{
    int h, t;
    void pop(){ ++h; }
    void push(int x, int y){
        arr[t].x = x;
        arr[t].y = y;
        ++t;
    }
    bool empty(){ return h == t; }
} q;
int book[210][210];
char g2[210][60];
char g[210][210];
char hex[16][5];
char hieroglyphs[7] = "WAKJSD";
char sign[41000], len;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};
int n, m;
void convert(int r, int c){//16进制位图转2进制
    for(int i = 0; i < r; i++){
        g[i + 1][0] = '0';
        int k = 1;
        for(int j = 0; j < c; j++){
            int k2;
            if(g2[i][j] < 'a') k2 = g2[i][j] - '0';
            else k2 = g2[i][j] - 'a' + 10;
            for(int r = 0; r < 4; r++)
                g[i + 1][k++] = hex[k2][r];
        }
        g[i + 1][k] = '0';
        g[i + 1][k + 1] = '\0';
    }
    for(int i = 0; i < m; i++)
        g[0][i] = g[n - 1][i] = '0';
    g[0][m] = g[n - 1][m] = '\0';
}
void init(){//预先储存哈希值
    char code[5];
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 4; j++)
            if(i & (1 << j))
                code[3 - j] = '1';
            else code[3 - j] = '0';
        code[5] = '\0';
        strcpy(hex[i], code);
    }
}
bool isValid(int x, int y){
    return x >= 0 && y >= 0 && x < n && y < m;
}
void floodfill_white(int x, int y, char c1, char c2){//队列BFS
    q.h = q.t = 0;
    q.push(x, y);
    memset(book, 0, sizeof(book));
    book[x][y] = 1;
    while(!q.empty()){
        int kx = arr[q.h].x;
        int ky = arr[q.h].y;
        q.pop();
        g[kx][ky] = c2;
        for(int i = 0; i < 4; i++){
            int nx = kx + dx[i];
            int ny = ky + dy[i];
            if(isValid(nx, ny) && g[nx][ny] == c1 && book[nx][ny] == 0)
                book[nx][ny] = 1, q.push(nx, ny);
        }
    }
}
int floodfill_black(int x, int y, char c1, char c2){//DFS扫描文字
    g[x][y] = c2;
    int ans = 0;
    for(int i = 0; i < 4; i++){
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(isValid(nx, ny)){
            if(g[nx][ny] == '0')//某个像素点邻接有白色
                ++ans, floodfill_white(nx, ny, '0', 'w');
            else if(g[nx][ny] == '1')
                ans += floodfill_black(nx, ny, c1, c2);
        }
    }
    return ans;
}
int main(){
    init();
    int r, c, t = 1;
    while(scanf("%d%d", &r, &c), (r || c)){
        getchar();
        for(int i = 0; i < r; i++)
            gets(g2[i]);
        n = r + 2;
        m = c * 4 + 2;
        convert(r, c);//转换
        floodfill_white(0, 0, '0', 'w');//外部区域染色
        len = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(g[i][j] == '1'){
                    int white_size = floodfill_black(i, j, '1', 'b');//扫描文字并得到内部白色块数量
                    sign[len++] = hieroglyphs[white_size];
                }
        std::sort(sign, sign + len);//排序结果
        sign[len] = '\0';
        printf("Case %d: %s\n", t++, sign);
    }
}

```


---

## 作者：HellolWorld (赞：2)

先把背景扣掉

数数每个图形中有多少块空白就能判断是哪个文字了

具体看代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
int M[3300][900];
char ch[5000];
int a, b;
int code(char ch)
{
    if (ch <= '9')
        return ch - '0';
    return ch - 'a' + 10;
}
int mk;
void dfs1(int x, int y)
{
    if (x < 1 || x > a || y < 1 || y > b * 4)
        return;
    if (M[x][y])
        return;
    M[x][y] = -1;
    dfs1(x + 1, y);
    dfs1(x - 1, y);
    dfs1(x, y + 1);
    dfs1(x, y - 1);
}
void dfs2(int x, int y)
{
    if (x < 1 || x > a || y < 1 || y > b * 4)
        return;
    if (M[x][y] == -1)
        return;
    if (M[x][y] == 1)
    {
        M[x][y] = -1;
        for (int i = x - 1; i <= x + 1; ++i)
            for (int j = y - 1; j <= y + 1; ++j)
                dfs2(i, j);
    }
    else
    {
        ++mk;
        dfs1(x, y);
    }
}
priority_queue<char, vector<char>, greater<char> > pq;
char D[] = {'W', 'A', 'K', 'J', 'S', 'D'};
int main()
{
    int cas = 0;
    while (1)
    {
        ++cas;
        memset(M, 0, sizeof(M));
        scanf("%d%d", &a, &b);
        if (!a || !b)
            break;
        for (int i = 1; i <= a; ++i)
        {
            scanf("%s", ch + 1);
            for (int j = 1; j <= b; ++j)
            {
                int x = code(ch[j]);
                int n = 1;
                for (int k = j * 4; k > j * 4 - 4; --k, n <<= 1)
                    M[i][k] = (x & n) != 0;
            }
        }
        //扣背景
        for (int i = 1; i <= a; ++i)
            dfs1(i, 1), dfs1(i, b * 4);
        for (int j = 1; j <= b * 4; ++j)
            dfs1(1, j), dfs1(a, j);
            
            
        for (int j = 1; j <= b * 4; ++j)
            for (int i = 1; i <= a; ++i)
                if (M[i][j] == 1)
                {
                    mk = 0;
                    dfs2(i, j);
                    pq.push(D[mk]);
                }
        printf("Case %d: ", cas);
        while (!pq.empty())
        {
            putchar(pq.top());
            pq.pop();
        }
        putchar('\n');
    }
    return 0;
}

```

---

## 作者：xiaolin000 (赞：2)

#### 思路：表中6个符号从左至右依次有1(A)，3(J)，5(D)，4(S)，0(W)，2(K)个圈，各不相同。所以判断圈的个数即可。
#### 用以下列数据演示：
10 3
000
778
548
748
578
700
000
7f0
1e0
000

初始状态：

![初始图](https://images.cnblogs.com/cnblogs_com/linme/1591753/o_1912030934231.JPG "初始图")

## 实现方法：
 
1. 黑色块包裹的圈内白色块肯定不会四连块连接到边缘的块去，所以遍历4条边，并且标记这些非圈内白块。（如图）

![图1](https://images.cnblogs.com/cnblogs_com/linme/1591753/o_1912030934282.JPG "图1")

2. 开始遍历找黑块，找到一个后进入dfs标记连通块，由题意，一个黑色块最终能标记一整个符号。 继续找黑色块，如果还有，那就是第二个符号，依次类推，同时给符号的标记做区分处理，顺便记录符号个数。

![图2](https://images.cnblogs.com/cnblogs_com/linme/1591753/o_1912030934323.JPG "图2")
 
 3. 找白色块，此时找到的都是圈内的，找到第一个就dfs标记所有该圈内的白色块（用-2）。 此时判断白色块属于哪个符号：如第一个白色块坐标为(x,y)，那么(x-1,y)肯定是黑色块，因为经过了这个黑色块才能进圈。

![图3](https://images.cnblogs.com/cnblogs_com/linme/1591753/o_1912030934364.JPG "图3")

4. 字典序输出结果。
### 注释代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int pic[200][200], ascii[6]={87,65,75,74,83,68},H, W,n = 0,
    t[16][4] = {{0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 0, 1, 1},
                {0, 1, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1},
                {1, 0, 0, 0}, {1, 0, 0, 1}, {1, 0, 1, 0}, {1, 0, 1, 1},
                {1, 1, 0, 0}, {1, 1, 0, 1}, {1, 1, 1, 0}, {1, 1, 1, 1}};
void filled()//输入图
{
    char temp;
    for (int i = 0; i < H; i++)
        for (int k = 0, c = 0; k < W; k++)
        {
            scanf(" %c", &temp); //空格吸收回车，字符串读入
            if (temp > 96)  temp -= 87; //97为a
            else            temp -= 48;
            for (int f = 0; f < 4; f++)   //输入的转为4个二进制
                pic[i][c++] = t[temp][f]; //c为当前行第几个，换行时清零
        }
}
void dfs(int y, int x, int f, int a) //y行 x列 f需要标记的值  a要连通的格子类型
{
    if (x >= 4 * W || x < 0 || y >= H || y < 0 || pic[y][x] != a) return; //出界OR不是要爬的格子
    pic[y][x] = f; //标记当前格为f
    dfs(y - 1, x, f, a);
    dfs(y + 1, x, f, a);
    dfs(y, x - 1, f, a);
    dfs(y, x + 1, f, a);
}
int main()
{
    while (cin >> H >> W) //H行 W列
    {
        if (H == 0)
            break; //结束条件0 0
        filled();
        cout << "Case " << ++n << ": ";
        int n = 4, c[100] = {0},cnt=0;    //c数组存放符号n的圈的个数
        for (int i = 0; i < H; i++) //功能：遍历四条边的每一点
        {
            int q = 4 * W;
            if (i == 0 || i == H - 1) q = 2;
            for (int j = 0; j < 4 * W; j += q - 1)
                dfs(i, j, -1, 0);
        }
        for (int i = 0; i < H; i++) //功能：标记每个黑块组成的符号
            for (int j = 0; j < 4 * W; j++)
                if (pic[i][j] == 1)
                    dfs(i, j, n++, 1); //防止混淆，n初始为4，当前符号标记为4
        for (int i = 0; i < H; i++) //功能：找白块
            for (int j = 0; j < 4 * W; j++)
                if (pic[i][j] == 0)
                {
                    c[pic[i][j - 1]]++; //直接找前一个黑块的值作为该符号的号码，表示增加一个圈
                    dfs(i, j, -2, 0);   //用-2标记已经计算过的圈内白块
                }
        for (int i = 4; i < n; i++) c[i]=ascii[c[i]]; //将值换成ASCII码存放
		sort(c+4,c+n);//对c数组第4个到第n-1个升序排序
        for (int i = 4; i < n; i++) printf("%c",c[i]); //字典序输出 n初始是从4开始算
        cout << endl;
    }
    return 0;
}
```

---

## 作者：ShineEternal (赞：2)

# 写在前面：
如想获取更佳阅读效果，请点击[这里](https://blog.csdn.net/kkkksc03/article/details/87731523)，任何疑问欢迎私信作者！
# 题目链接：
https://www.luogu.org/problemnew/show/UVA1103
# 题目分析：
我们可以先进行矩阵的还原

```cpp
for(int k=1;k<=4;k++)
{
	a[i][++cnt]=(tmp>>(4-k))&1;
}
```
这种使用for语句的方法在其他题解内貌似没有提及，（~~但其实就是把anguei的化简了一下~~）
这样就能复原出原始的数据（01矩阵）

然后我们可以发现每一个象形文字都有可放缩性，但空白的个数是一定的。例如虫子图案就有4个空白处。

这样我们可以利用这一特性来解决问题了。

接下来用的算法是dfs乃至bfs入门都很常见的经典模型——水洼（或细胞个数）。

我们可以先判断与矩阵边缘联通的空白，全部消掉，然后剩下的空白就是文字中的了。

那么如何判断是哪个文字中的空白呢？

算法1：
刚开始，我是想先把每个文字复制一份到另一个数组里，那么在数组里经过边缘处理后剩下的空白联通块个数即为这个文字的个数。

### 但是后来发现没有必要。
算法2：
我们可以直接找黑点，找到一个开始扩张，扩张到的白点就是该文字的了。。。

## 还有就是千万不要犯一个错误：
输出的顺序是题目中图形出现的先后顺序而不是空白的个数为顺序。

# $end$
# 代码：

```cpp
//主要思路：先把二进制的01矩阵还原出来，记在a数组里，然后一一把每个象形文字单独放到b数组里，用从外向内缩0的办法找出在图形内的空白0，然后数出来，结束。 
#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
using namespace std;
int a[205][205];
int aa[5]={0,1,-1,0,0};
int bb[5]={0,0,0,-1,1};

int ans;
int jl[7];
int H,W;
char st[6]={'W','A','K','J','S','D'};
void pd(int xx,int yy)
{
	a[xx][yy]=2;
	for(int i=1;i<=4;i++)
	{
		int x=xx+aa[i];
		int y=yy+bb[i];
		if(x>0&&y>0&&x<=H&&y<=W&&a[x][y]==0)
		{
			a[x][y]=2;
			pd(x,y);
		}
	}
}
void search(int xx,int yy)
{
	a[xx][yy]=2;
	for(int i=1;i<=4;i++)
	{
		int x=xx+aa[i];
		int y=yy+bb[i];
		if(x>0&&y>0&&x<=H&&y<=W&&a[x][y]!=2)
		{
			
			if(a[x][y]==0)
			{
				ans++;
				pd(x,y);
			}
			else
			if(a[x][y]==1)	search(x,y);
			
		}
	}
}

int main()
{
	char s[55];
	int cntt=0;
	while(~scanf("%d%d",&H,&W)&&H!=0&&W!=0)
	{
		memset(jl,0,sizeof(jl));
		memset(a,0,sizeof(a));
		ans=0;
		cntt++;
		for(int i=1;i<=H;i++)
		{
			cin>>s;
			int cnt=0;
			for(int j=1;j<=W;j++)
			{
				int tmp;
				sscanf(s+j-1,"%1x",&tmp);
				//printf("%1x",tmp);
				//printf("\n");
				for(int k=1;k<=4;k++)
				{
					a[i][++cnt]=(tmp>>(4-k))&1;
				}
			}
		}
		W*=4;
		
		/*for(int i=1;i<=H;i++)
		{
			for(int j=1;j<=W;j++)
			{
				printf("%d",a[i][j]);
			}
			printf("\n");
		}*/
		for(int k=1;k<=H;k++)
		{
			if(a[k][1]==0)pd(k,1);
			if(a[k][W]==0)pd(k,W);
		}
		for(int k=1;k<=W;k++)
		{
			if(a[1][k]==0)pd(1,k);
			if(a[H][k]==0)pd(H,k);
		}
				/*	for(int qwq=1;qwq<=H;qwq++)
				{
					for(int qaq=1;qaq<=W;qaq++)
					{
						printf("%d",a[qwq][qaq]);
					}
					printf("\n");
				}*/
		for(int i=1;i<=H;i++)
		{
			for(int j=1;j<=W;j++)
			{
				/*printf("--------\n");
				for(int qwq=1;qwq<=H;qwq++)
				{
					for(int qaq=1;qaq<=W;qaq++)
					{
						printf("%d",a[qwq][qaq]);
					}
					printf("\n");
				}*/
				if(a[i][j]==1)
				{
					//print();
					ans=0;
					search(i,j);
					//printf("ans=%d\n",ans);
					jl[ans]++;
					//printf("ans=%d\n",ans);
				}
		/*		for(int i=1;i<=H;i++)
		{
			for(int j=1;j<=W;j++)
			{
				printf("%d",a[i][j]);
			}
			printf("\n");
		}*/
			}
		}
		printf("Case %d: ",cntt);
		for(int j=1;j<=jl[1];j++)
			{
				printf("%c",st[1]);
			}
		for(int j=1;j<=jl[5];j++)
			{
				printf("%c",st[5]);
			}
			for(int j=1;j<=jl[3];j++)
			{
				printf("%c",st[3]);
			}
			for(int j=1;j<=jl[2];j++)
			{
				printf("%c",st[2]);
			}
			for(int j=1;j<=jl[4];j++)
			{
				printf("%c",st[4]);
			}
			for(int j=1;j<=jl[0];j++)
			{
				printf("%c",st[0]);
			}
		printf("\n");//qaqqwqwedffg
	
	}
	return 0;return 0;
}
```
撒花~


---

## 作者：Insouciant21 (赞：1)

### 题意

输入一个 $\textrm H$ 行 $\textrm W$ 列的十六进制字符矩阵，**按字典序输出**解读出的象形文字。

注意输入格式是每四个像素（ $\textrm 0$ 是白像素， $\textrm1$ 是黑像素 ）的十六进制表示，所以我们可以这样表示：

```cpp
string hex[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
```

所以实际的字符矩阵行数为 $\textrm H$ ，列数为 $\textrm 4\times W$ 。 

输入代码
```cpp
void input() {
    string g;
    string hex[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    for (int i = 1; i <= H; i++) {
        cin >> g;
        for (int j = 0, point = 1; j < W; j++, point += 4) {
            for (int k = 0; k < 4; k++)
                graph[i][k + point] = hex[isdigit(g[j]) ? g[j] - '0' : g[j] - 'a' + 10][k] - '0'; 
                // 每一位 16 进制码对应四位像素， point 指向当前 16 进制码对应的位置开头，从 1 开始是为了完全去除背景白色像素。
        }
    }
    W *= 4; 
}
```


### 实现

先把象形文字周围的白色像素去除，为了完全去除背景，我们需要在原矩阵周围多添加一圈。

```cpp
void removeBackground() { // BFS 求联通块
    queue<Point> q;
    q.push({0, 0}); // 原字符矩阵从 (1,1) 开始
    graph[0][0] = -1;
    while (!q.empty()) {
        Point prs = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            Point ftr = prs;
            ftr.move(i);
            if (ftr.x < 0 || ftr.y < 0 || ftr.x > H + 1 || ftr.y > W + 1)
                continue;
            if (graph[ftr.x][ftr.y] == 1 || graph[ftr.x][ftr.y] == -1)
                continue;
            graph[ftr.x][ftr.y] = -1;
            q.push(ftr);
        }
    }
}
```

将背景去除以后，扫描黑色像素，因为题目明确了每一个象形文字都是四连块，所以找到一个黑色像素后就可对整个四连块进行标记并编号。

但是注意到，题目中提到了象形文字可以被扭曲、拉伸，所以无法仅根据四连块的形状判定象形文字。

![](https://cdn.luogu.org/upload/pic/38685.png)

注意到每一个象形文字中的空白部分的个数都不一样，且文字无法被撕裂，所以空白的个数可被用于识别象形文字。

```cpp
void detectPixel(int color) { // color = 1 为黑色， 0 为白色
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            if (graph[i][j] != color)
                continue;
            if (vis[i][j])
                continue;
            mark({i, j}, color);
        }
    }
}

void mark(Point g, int mode) {
    queue<Point> q;
    q.push(g);
    vis[g.x][g.y] = (mode) ? ++cnt : -1; // 如果是黑色编号，白色做标记
    bool marked = false;
    if (mode)
        blank.push_back(0);
    while (!q.empty()) {
        Point prs = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            Point ftr = prs;
            ftr.move(i);
            if (ftr.x < 1 || ftr.y < 1 || ftr.x > H || ftr.y > W)
                continue;
            if (graph[ftr.x][ftr.y] != mode) {
                if (!mode && graph[ftr.x][ftr.y] == 1 && !marked) {
                    marked = true;
                    blank[vis[ftr.x][ftr.y] - 1]++; 
                    /*
                    	此处白色像素块遇到边缘
                        因为题目中提到了象形文字不会接触或是包含
                        所以此时遇到的黑色像素一定是白色像素块所对应的象形文字
                    */
                }
                continue;
            }
            if (vis[ftr.x][ftr.y])
                continue;
            vis[ftr.x][ftr.y] = (mode) ? cnt : -1;
            q.push(ftr);
        }
    }
}
```

统计完每个象形文字的白色块数目以后，就可以计算结果了。
```cpp
void output() {
    cout << "Case " << kase << ": ";
    sort(blank.begin(), blank.end(), [](int a, int b) { return convert[a] < convert[b]; }); // 按字典序输出
    for (auto i : blank)
        cout << convert[i];
    cout << endl;
}
```

### 完整代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int H, W;

int graph[205][205];
int vis[205][205];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

vector<int> blank;

int cnt = 0;
int kase = 0;

char convert[] = {'W', 'A', 'K', 'J', 'S', 'D'}; // 从0个空白块到5个空白块分别对应的字符

struct Point {
    int x, y;
    void move(int mode) { x += dx[mode], y += dy[mode]; }
};

void init();
void input();
void removeBackground();
void detectPixel(int color);
void mark(Point g, int mode);
void output();

int main() {
    while (cin >> H >> W && H && W) {
        init();
        input();
        removeBackground();
        detectPixel(1);
        detectPixel(0);
        output();
    }
    return 0;
}

void init() { // 多组数据输入初始化
    kase++;
    cnt = 0;
    memset(graph, 0, sizeof graph);
    memset(vis, 0, sizeof vis);
    blank.clear();
}

void input() {
    string g;
    string hex[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    for (int i = 1; i <= H; i++) {
        cin >> g;
        for (int j = 0, point = 1; j < W; j++, point += 4) {
            for (int k = 0; k < 4; k++)
                graph[i][k + point] = hex[isdigit(g[j]) ? g[j] - '0' : g[j] - 'a' + 10][k] - '0';
        }
    }
    W *= 4;
}

void removeBackground() {
    queue<Point> q;
    q.push({0, 0});
    graph[0][0] = -1;
    while (!q.empty()) {
        Point prs = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            Point ftr = prs;
            ftr.move(i);
            if (ftr.x < 0 || ftr.y < 0 || ftr.x > H + 1 || ftr.y > W + 1)
                continue;
            if (graph[ftr.x][ftr.y] == 1 || graph[ftr.x][ftr.y] == -1)
                continue;
            graph[ftr.x][ftr.y] = -1;
            q.push(ftr);
        }
    }
}

void detectPixel(int color) {
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            if (graph[i][j] != color)
                continue;
            if (vis[i][j])
                continue;
            mark({i, j}, color);
        }
    }
}

void mark(Point g, int mode) {
    queue<Point> q;
    q.push(g);
    vis[g.x][g.y] = (mode) ? ++cnt : -1;
    bool marked = false;
    if (mode)
        blank.push_back(0);
    while (!q.empty()) {
        Point prs = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            Point ftr = prs;
            ftr.move(i);
            if (ftr.x < 1 || ftr.y < 1 || ftr.x > H || ftr.y > W)
                continue;
            if (graph[ftr.x][ftr.y] != mode) {
                if (!mode && graph[ftr.x][ftr.y] == 1 && !marked) {
                    marked = true;
                    blank[vis[ftr.x][ftr.y] - 1]++;
                }
                continue;
            }
            if (vis[ftr.x][ftr.y])
                continue;
            vis[ftr.x][ftr.y] = (mode) ? cnt : -1;
            q.push(ftr);
        }
    }
}

void output() {
    cout << "Case " << kase << ": ";
    sort(blank.begin(), blank.end(), [](int a, int b) { return convert[a] < convert[b]; });
    for (auto i : blank)
        cout << convert[i];
    cout << endl;
}
```


---

