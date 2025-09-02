# President's Office

## 样例 #1

### 输入

```
3 4 R
G.B.
.RR.
TTT.
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 3 Z
...
.H.
..Z
```

### 输出

```
0
```

# 题解

## 作者：henry09 (赞：9)

### 我想和大家比一下谁是最短代码奖得主
### （本人22行）

#### 本人采用的是~~~~最简单的~~（自认为是）~~

## 主要思想是先把整个地图扫一遍，一遇到总统桌颜色，就逐个判断上下左右！

# 重中之重的是要加入一个set中!



	#include<bits/stdc++.h>
	using namespace std;
	int n,m;
	char c,s[105][105];
	set<char> se;
	int main()
	{
		cin>>n>>m>>c;
 		for (int i=0;i<n;i++)
 			cin>>s[i];	//样例中没有空格，所以要整行的读入
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
				if (s[i][j]==c)
				{
					if (s[i][j+1]!=c&&s[i][j+1]!='.'&&j+1<m) se.insert(s[i][j+1]);
					if (s[i+1][j]!=c&&s[i+1][j]!='.'&&i+1<n) se.insert(s[i+1][j]);
					if (s[i][j-1]!=c&&s[i][j-1]!='.'&&j-1>=0) se.insert(s[i][j-1]);
					if (s[i-1][j]!=c&&s[i-1][j]!='.'&&i-1>=0) se.insert(s[i-1][j]);
                    //上下左右依次判断由于
				}
		cout<<se.size()<<endl;  //由于在前面已经加入过set中了，可以直接用size()来取长度
		return 0;
	}




---

## 作者：AkiwaZawa (赞：7)

## DFS——暴力出奇迹！
（详情注释请看代码）


```
#include<bits/stdc++.h>
using namespace std;
int n,m,s;
char p;//总统的桌子 
char a[104][104];
bool vis[27];//标记其他的桌子 
int tx[5]={1,0,-1,0};
int ty[5]={0,1,0,-1};
inline void dfs(int x,int y)
{
	register int i,j;
	for(i=0;i<4;i++)
	{
		int x1=x+tx[i];
		int y1=y+ty[i];
		if(x1<0 || x1>=n || y1<0 ||y1>=m)
			continue;
		if(a[x1][y1]!='.')//如果是桌子 
		{
			if(a[x1][y1]!=p)//如果不是总统桌子的其他部分 
			{
				vis[a[x1][y1]-'A']=1;//标记其他桌子 
				a[x1][y1]='.';//再见桌子 
			}
			else//如果是总统桌子的其他部分 
			{
				a[x1][y1]='.';//再见桌子 
				dfs(x1,y1);//从那里继续搜 
			}
		}
	}
	return ; 
}
int main()
{
	cin>>n>>m>>p;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>a[i][j];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(a[i][j]==p)//如果是总统的桌子 
			{
				dfs(i,j);//从那里开始搜索 
				break;//搜完退出 
			}
		}
	}
	for(int i=0;i<26;i++)//统计在总统旁的桌子 
		if(vis[i])	s++; 
	cout<<s<<endl;
	return 0;
}
```


---

## 作者：小闸蟹 (赞：4)

```cpp
// 这道题就是一道标准的DFS题，各种套路都是很基础的
// 具体见代码
#include <iostream>
#include <string>
#include <vector>
#include <array>

std::vector<std::string> Map;   // 整张地图
std::array<bool, 26> Num{ 0 };  // 标记搜到过的桌子，这里类似桶排，就不用写判重了
std::array<int, 4> dx{ 0, 1, -1, 0 }, dy{ -1, 0, 0, 1 };
// 注意是四个方向而不是八个方向

int n, m;   // 宽和长
char p; // 总统桌的字母

void DFS(int x, int y)
{
    // 超出边界了就立即返回
    if (x < 0 || x >= n || y < 0 || y >= m)
    {
        return;
    }
    else
    {
        if (Map[x][y] != '.')   // 如果有桌子
        {
            if (Map[x][y] == p) // 如果是总统桌
            {
                Map[x][y] = '.';    // 就标记一下已经搜过了

                for (int i = 0; i < 4; ++i) // 和总统桌连着的四个方向搜下去
                {
                    DFS(x + dx[i], y + dy[i]);
                }
            } 
            else   // 如果是总统桌以外的桌子
            {
                Num[Map[x][y] - 'A'] = true;    // 就标记这个字母的桌子被搜到了
                Map[x][y] = '.';    // 标记一下已经被搜过了
            }
        }
    }
}

int main()
{
    std::cin >> n >> m >> p;
    std::string Str;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> Str;
        Map.push_back(Str);
    }

    int x, y;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (Map[i][j] == p) // 找总统桌的位置
            {
                x = i;
                y = j;
                goto Outside;   // 用goto跳出多重循环很方便的
            }
        }
    }

Outside:
    DFS(x, y);  // 从第一张总统桌的位置往下搜

    int Sum = 0;
    for (int i = 0; i < 26; ++i)
    {
        if (Num[i])
        {
            ++Sum;  // 统计有多少张被搜到的桌子
        }
    }
    std::cout << Sum << std::endl;

    return 0;
}
```

---

## 作者：NKL丶 (赞：2)

## $PS$：此篇题解后半部分纯属娱乐，真的可忽略 ~~（是为了争最短代码）~~。
## 主要的思路大概是这样子的：  
首先，**总统桌只有一张，且周围的桌子颜色都是唯一的** ~~（其实是我后来才发现的）~~。  
**换句话来说，绝对不会出现以下的样例（此处忽略$n$和$m$，且总统桌字符串统一为$A$）**
```
..AAA..
.......
AAA....
.......
```
又或者是这一种样例：
```
......
...B..
.AAAA.
...B..
......
```
利用这一个特性，我们可以建立一个数组$vis$。  
$vis_i$代表总统桌旁边是否有颜色为$i$的桌子。（此处可以直接利用ASCII码来作下标）  
然后，如果找到一个总统桌的字母（有点绕口），便看看它的四周，如果该字母不是`.`且它没有被记录过，则$ans$++，并将它记录下来。  
思路还是十分简单明了的，所以附上一个正常的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum,vis[1000],n,m;
char v,a[105][105];
int main()
{
    cin>>n>>m>>v;
    vis['.']=vis[v]=1;//此处进行预处理，将总统桌和.先筛掉
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>a[i][j];//进行输入
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(a[i][j]==v)//此乃总统桌也（滑稽）
            {
                if(i-1>0&&vis[a[i-1][j]]==0)sum++,vis[a[i-1][j]]=1;//上方未被标记（一定要判断边界），则sum++，并标记
                if(i+1<=n&&vis[a[i+1][j]]==0)sum++,vis[a[i+1][j]]=1;//下方
                if(j+1<=m&&vis[a[i][j+1]]==0)sum++,vis[a[i][j+1]]=1;//右侧
                if(j-1>0&&vis[a[i][j-1]]==0)sum++,vis[a[i][j-1]]=1;//左侧
            }
    cout<<sum;//输出
    return 0;
}
```
$$\text{你以为这篇文章就这样结束了？}$$
$$\text{并没有！}$$
看了[这一篇题解](https://www.luogu.org/blog/henry09/solution-cf6b)中我感到很不爽，~~因为实际上还能再短~~  
于是我便码出了这个不算注释有17行的代码 ~~（他也缩进了一行，我也缩进了一行）~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum,vis[1000],n,m,dx[4]={0,0,1,-1},dy[4]={1,-1,0,0};
//此处dx和dy记录的是上下左右的方向（有点BFS的感觉）
char v;//同上一个代码
string a[105];//此处用了string是因为用string输入会减少一个for循环（对于char来说）
int main()
{
    cin>>n>>m>>v;
    for(int i=0;i<n;i++)
        cin>>a[i];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            for(int k=0;k<4;k++)//k枚举的是方向
                if((a[i][j]==v)&&(i+dx[k]>=0&&i+dx[k]<n&&j+dy[k]>=0&&j+dy[k]<m)&&(a[i+dx[k]][j+dy[k]]!=v)&&(a[i+dx[k]][j+dy[k]]!='.')&&(vis[a[i+dx[k]][j+dy[k]]]==0))sum++,vis[a[i+dx[k]][j+dy[k]]]=1;
    //此处的压行分开来讲：
    //第一个括号判断是否为总统桌
    //第二个括号判断的是边界（因为我的行和列都是从0开始的）
    //第三个括号筛出非总统桌
    //第四个括号筛出普通单元格
    //第五个括号判断是否被标记过
    cout<<sum;
    return 0;
}
```


---

## 作者：judgejudge (赞：2)

# 四个方向搜索+删除

首先尴尬的是一开始我认为桌子的颜色不是唯一的，有了一下做法：

1. 我们知道要找的是总统办公桌周围的桌子，那么先**查找到总统办公桌的位置**，在对其四个方向进行搜索。如果满足以下条件：
    1. **没有超出范围**
    1. **既不是总统办公桌，也不是'.'**
    
    那么我们认为这是**与其相邻**的办公桌，总数++
1. 由于一开始认为不是唯一的，所以我就想到一个方法：

我们查找到一个与其相邻的办公桌，就干脆把它的整一个桌子找齐，然后**以防重复查找，就把它替换成'.'**。

这样的话就有两个函数：**1.查找桌子位置并记录 2.查找归属于桌子其他部分并删除**

下面奉上AC代码：
```cpp
#include <iostream>
using namespace std;
int n,m;
char c[101][101];//由于范围不大
int a[27];//这里为了方便找到程序漏洞我用了ASCII码的方法，可直接用sum
int sum=0,ans=0;
char pre,alp;
int dp(int row,int col){
	int i,j;
	if(row>0&&row<=n&&col>0&&col<=m){//确保没超出范围
		if(c[row][col]==alp){//如果是“同类”
		    c[row][col]='.';//替换
		    dp(row-1,col);
		    dp(row+1,col);
		    dp(row,col-1);
		    dp(row,col+1);//继续搜索四个方向，把整个桌子替换掉，就会防止f函数漏判或多判
		}
	}
}
int f(int row,int col){
	int i,j;
	if(row>0&&row<=n&&col>0&&col<=m){//确保没超出范围
		if(c[row][col]!=pre&&c[row][col]!='.'){//如果符合条件
			a[c[row][col]-'A']++;
			alp=c[row][col];//此处为了方便dp函数查找归属于相同桌子的部分“同类”
			c[row][col]='.';//注意：因为我们搜索四个方向，不包括其本身，所以在这里我们就要替换
			dp(row-1,col);
			dp(row+1,col);
			dp(row,col-1);
			dp(row,col+1);///搜索四个方向
		}
	}
}
int main(){
	int i,j,k;
	cin>>n>>m>>pre;//pre记录总统办公桌的样貌
	for(i=1;i<=n;i++)
	for(j=1;j<=m;j++)cin>>c[i][j];
	for(i=1;i<=n;i++)
	for(j=1;j<=m;j++){
		if(c[i][j]==pre){//如果查找到总统办公桌，搜索四个方向
			f(i,j-1);
			f(i,j+1);
			f(i-1,j);
			f(i+1,j);
		}
	}
	for(i=0;i<26;i++)
	if(a[i]>0)ans+=a[i];
	cout<<ans<<endl;
	return 0; 
}
```
当然，如果颜色是默认唯一的，那么就有一个更简单的做法：

此处我们不能直接用sum,而是将ASCII码转换成数字作为数组进行储存，这样防止多判：
```cpp
#include <iostream>
using namespace std;
int n,m;
char c[101][101];
int a[27];
int sum=0,ans=0;
char pre,alp;
int f(int row,int col){
	int i,j;
	if(row>0&&row<=n&&col>0&&col<=m){
		if(c[row][col]!=pre&&c[row][col]!='.')a[c[row][col]-'A']++;//此处我们用数组记录，就可以很好的记录相邻的桌子
	}
}
int main(){//main函数与上一个代码类似
	int i,j,k;
	cin>>n>>m>>pre;
	for(i=1;i<=n;i++)
	for(j=1;j<=m;j++)cin>>c[i][j];
	for(i=1;i<=n;i++)
	for(j=1;j<=m;j++){
		if(c[i][j]==pre){
			f(i,j-1);
			f(i,j+1);
			f(i-1,j);
			f(i+1,j);
		}
	}
	for(i=0;i<26;i++)
	if(a[i]>0)ans++;//这里有所不同，不能+=a[i]!
	cout<<ans<<endl;
	return 0; 
}
```



---

## 作者：s5_gan (赞：1)

# 搜索大法
### 这道题其实不用搜索
###### 但是为了~~内容不重复~~让大家看得更懂我就用了

解法只要找出总统桌在四周用bool标记其他桌子，最后统计就好。
```
#include<bits/stdc++.h> 
using namespace std;
const int next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//const方向
int n,m;
bool vis[26];//统计26颜色
char c,s[101][101];
int dfs(int x,int y)  
{  
    int mx, my;  //mx和my表示总统桌四周的方位
    for(int i=0;i<4;i++)  
    {
    	mx=x+next[i][0];  
        my=y+next[i][1]; 
        if(mx<0||my<0||mx>=n||my>=m)  //如果超出办公室范围（即mx，my在边缘）
            continue;  //跳出循环
        if(s[mx][my]!='.')  //判断是否是桌子
        {
            if(s[mx][my]!=c)  //判断是否是自己的另一部份
            {  
                vis[s[mx][my]-'A']=1;  //标记它
                s[mx][my]='.';  //标记完就不要了
            }  
            else  //如果是自己的另一部分
            {  
                s[mx][my]='.';  //还是扔掉
                dfs(mx,my);  //直接从那里再次开始搜索
            }  
        }  
    }
}  
int main()  
{
	cin>>n>>m>>c;
    int ans=0;  
    memset(vis,0,sizeof(vis));//初始化vis为0
    for(int i=0;i<n;i++)  
    for(int j=0;j<m;j++)
		cin>>s[i][j];
    for(int i=0;i<n;i++)  
    for(int j=0;j<m;j++)
    {  
        if(s[i][j]==c)//搜索总统桌
        {  
            dfs(i,j);//进入函数
            break;  
        }  
 	}
    for(int i=0; i<26; ++i)  
    	if(vis[i])  
    	ans++; //统计
    cout<<ans;
    return 0;  
}
```

---

## 作者：LYR_ (赞：0)

可至博客查看：[点击此处](https://www.cnblogs.com/Ryan-juruo/p/12231173.html)
#### 看到大致思路一致的题解，决定发一篇运用STL不用dfs的题解~~好久不发题解，心里不爽~~
### 思路： 
		1.输入的同时找到总统桌子的位置，用vector<pair <int,int> >记录横坐标和纵坐标
		2.在总统桌子周围找到其他桌子，并用set记录（set可以去重）
		3.打印set的长度，即周围桌子的数量


------------
Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=110;
char c[N][N];
int n,m;
char pt;
set<char> s;
vector< pair<int,int> > v;
int dx[4]={0,0,-1,1},dy[4]={1,-1,0,0};
int main() {
	cin>>n>>m;
	cin>>pt;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			cin>>c[i][j];
			if(c[i][j]==pt) v.push_back(make_pair(i,j));
		}
	}
	for(int i=0;i<v.size();i++) {
		int x,y;
		x=v[i].first;
		y=v[i].second;
		for(int j=0;j<4;j++) {
			int nx=x+dx[j],ny=y+dy[j];
			if(c[nx][ny]>='A' && c[nx][ny]<='Z' && c[nx][ny]!=pt) s.insert(c[nx][ny]);
		}
	}
	cout<<s.size()<<endl;
	return 0;
}
```


---

## 作者：Loner_Knowledge (赞：0)


---

题目保证每个桌子的颜色是唯一的，由于搜索会更麻烦，暴力查找即可。

```cpp
#include<cstdio>
const int Const[2][4]={{-1,0,1,0},{0,1,0,-1}};	//存储四个方向
bool mark[26];		//标记数组
char s[101][102];
int main() {
	int n,m,ans=0;
	char c;
	scanf("%d %d %c",&n,&m,&c);
	for(int i=0;i<n;++i)
		scanf("%s",s[i]);
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			if(s[i][j]==c)
				for(int k=0,x,y;k<4;++k) {	//当确定当前是总统桌时向四个方向查找
					x=i+Const[0][k];
					y=j+Const[1][k];
					if(x>=0&&x<n&&y>=0&&y<m&&s[x][y]!='.'&&s[x][y]!=c&&!mark[s[x][y]-'A'])
						mark[s[x][y]-'A']=1;	//查找到则标记
				}
	for(int i=0;i<26;++i)
		ans+=mark[i];		//最后统计标记
	printf("%d",ans);
	return 0;
}
```



---


---

