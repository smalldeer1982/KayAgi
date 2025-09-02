# [GCJ 2010 #1A] Rotate

## 题目描述

在激动人心的 Join-$K$ 游戏中，红色和蓝色棋子被投入一个 $N \times N$ 的棋盘。棋盘是竖直放置的，因此棋子会下落到该列最底部的空位。例如，考虑以下两种棋盘状态：

```
    - 合法状态 -

          .......
          .......
          .......
          ....R..
          ...RB..
          ..BRB..
          .RBBR..
   - 非法状态 -

          .......
          .......
          .......
          .......
   错误 -> ..BR...
          ...R...
          .RBBR..
```

在这些图中，每个 '.' 表示一个空位，每个 'R' 表示一个红色棋子，每个 'B' 表示一个蓝色棋子。左边的状态是合法的，而右边的状态不是。原因是第三列中有一个棋子（箭头所指）没有落到其下方的空位上。

如果某个玩家能够将至少 $K$ 个同色棋子连成一行（可以是横向、纵向或对角线），则该玩家获胜。四种可能的连线方向如下所示：

```
      - 四连子 -

     R   RRRR    R   R
     R          R     R
     R         R       R
     R        R         R
```

在题目开头的“合法状态”示意图中，两个玩家都已经连成了两个棋子，但都没有连成三个。

现在，你正处于一场激烈的 Join-$K$ 游戏中，并且你有一个巧妙的计划确保获胜！当你的对手不注意时，你准备将棋盘顺时针旋转 $90$ 度。然后，重力会让棋子在新方向上再次下落，形成如下状态：

```
    - 初始 -

     .......
     .......
     .......
     ...R...
     ...RB..
     ..BRB..
     .RBBR..
   - 旋转 -

     .......
     R......
     BB.....
     BRRR...
     RBB....
     .......
     .......
   - 重力作用 -

     .......
     .......
     .......
     R......
     BB.....
     BRR....
     RBBR...
```

不幸的是，你只有一次旋转的机会，在对手发现之前。

现在只剩下选择合适的时机出手了。给定一个棋盘状态，请你判断在顺时针旋转棋盘并让重力生效后，哪一方（或双方！）会在棋盘上连成 $K$ 个棋子。

### 注意
- 你只能旋转棋盘一次。
- 假设重力只在棋盘完全旋转后才会生效。
- 只有在重力作用结束后才检查是否有玩家获胜。

## 说明/提示

**数据范围**

- $1 \leqslant T \leqslant 100$。
- $3 \leqslant K \leqslant N$。

**小数据范围（11 分，测试点 1 - 可见）**

- $3 \leqslant N \leqslant 7$。

**大数据范围（12 分，测试点 2 - 隐藏）**

- $3 \leqslant N \leqslant 50$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
7 3
.......
.......
.......
...R...
...BB..
..BRB..
.RRBR..
6 4
......
......
.R...R
.R..BB
.R.RBR
RB.BBB
4 4
R...
BR..
BR..
BR..
3 3
B..
RB.
RB.```

### 输出

```
Case #1: Neither
Case #2: Both
Case #3: Red
Case #4: Blue```

# 题解

## 作者：zhou_hao_tian (赞：5)

这道题就是一道纯模拟题。



先定义两个二维字符数组。


```
char a[1010][1010],b[1010][1010];
```
再输入 $b$ 数组。

然后将其旋转，转移方程如下：


```
a[j][n-i+1]=b[i][j];
//i表示第i行，j表示第j列，n表示一个n*n的图
```

然后就是“自由落体”，我们一列一列来处理。


1. 定义两个指针都从大到小。

2. 判断第一个指针是否有没有人下棋，如果有，指针就减小。

3. 判断第二个指针是否有没有人下棋，如果没有，指针就减小。

4. 如果两个指针都不用往减小，就可以将第二个指针所指向的棋子，移到第一个指针所指向的位置，然后两个指针都减小。


```
for(int j=1;j<=n;j++)//一列列处理
{
	for(int i=n,l=n;l>=1;)//两个指针
	{
		if(a[l][j]!='.'&&a[i][j]=='.')
		{
			a[i][j]=a[l][j],a[l][j]='.';
			//将第二个指针所指向的棋子，移到第一个指针所指向的位置
			l--,i--;	
		}
		if(a[i][j]!='.') i--;
		//第一个指针是否有没有人下棋，如果有，指针就减小
		if(a[l][j]=='.') l--;
		//第二个指针是否有没有人下棋，如果没有，指针就减小
		if(l>=i) l=i-1;
		//如果第一个指针移到第二个指针上面了，就将第二个指针移上来
	}
}
```
然后是判断是否能连续k个

1. 然后可以定义两个方向数组，分别表示行和列。


```
int fx[8]=[1,-1,0, 0,1,-1, 1, -1];//行
int fy[8]=[0, 0,1,-1,1,-1,-1,  1];//列
```


2. 然后一个个进行枚举每一个棋子，它能从任何方向连成的最大长度。

（这个时候方向数组就能起到作用了）


```
for(int i:1-n)
{
	for(int j:1-n)
	{
		if(a[i][j]!='.')//这里必须要有棋子
		{
      		int sum=0;
      		for(int f:0-7)//8个方向
      		{
      			int ans=1;//连成的棋子数
      			while(a[i+ans*fx[f]][j+ans*fy[f]]==a[i][j])//要和原来的棋子颜色相同
      				ans++;
      			sum=max(sum,ans);//求能连成的最大值
      		}
		}
		
	}
}
```
3. 枚举完这颗棋子后，判断这种颜色是否达到连续k个及以上。如果达到，然后判断颜色，标记这个颜色出现过。




最后输出。


```
//f表示红色，f2表示蓝色
//true出现过，false表示没有
cout<<"Case #"<</*第几轮*/<<": ";
if(f==true)
{
	if(f2==true) cout<<"Both\n";
	else cout<<"Red\n";
}
else
{
	if(f2==true) cout<<"Blue\n";
	else cout<<"Neither\n";
}
```

---

## 作者：jiangjiangQwQ (赞：5)

## 思路
首先模拟矩阵旋转 $90$ 度后的样子，重力会产生怎样的作用效果呢？它会把一列上**所有的方块**全部堆积到底下。然后就是判断有无 $k$ 连子的情况。下文分开讲解旋转函数 rotate 和 check 函数。
### rotate函数
发现一个点坐标 $(i,j)$ 旋转之后就会变成 $(j,n-i+1)$，所以我们可以开一个临时数组将 $b_{i,j}$ 赋值成 $a_{j,n-i+1}$。然后将每一列的棋子用字符串存储起来，依次放到底下，详见代码。
```cpp
void rotate(){
    char b[N][N];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            b[j][n-i+1]=a[i][j];
        }
    }//旋转
    for(int j=1;j<=n;j++){
        string s="";
        for(int i=n;i>=1;i--){
            if(b[i][j]!='.')
            s+=b[i][j];
        }//存储棋子
        int p=0;
        for(int i=n;i>=1;i--){
            if(p<s.size()) b[i][j]=s[p++];
            else b[i][j]='.';
        }//将棋子放到底下
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            a[i][j]=b[i][j];
}
```
### check函数
忽略非棋子的格点，设方向数组 $dir$ 存储 $8$ 个方向。即上下左右，左上左下右上右下。然后在棋子各点枚举八个方向，判断该方向包括自己是否能够构成 $k$ 连子。
```cpp
int check(){
    int R=0,B=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]=='.') continue;
            for(int e=0;e<8;e++){
                int p=0;
                while(_in(i+dir[e][0]*p,j+dir[e][1]*p)&&a[i+dir[e][0]*p][j+dir[e][1]*p]==a[i][j]) p++;//能走一直走,_in函数用于判断棋子是否有出界
                if(p==k){//刚好构成k连子
                    if(a[i][j]=='R')R=1;
                    else B=1;
                    break;
                }
            }
        }
    }
    //返回对局情况
    if(!R&&!B) return 0;
    else if(R&&!B)return 1;
    else if(B&&!R) return 2;
    else return 3;
}
```

### 主函数部分
```cpp
int main(){
    cin>>T;
    int tot=0;
    while(T--){
        printf("Case #%d: ",++tot);
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cin>>a[i][j];
            }
        }
        rotate();
        int st=check();
        if(st==0) printf("Neither\n");
        else if(st==1) printf("Red\n");
        else if(st==2) printf("Blue\n");
        else printf("Both\n");
    }
    return 0;
}
```

---

## 作者：wenqinghua1001 (赞：3)

## 前言

> 一道牛顿喜欢的题。

[题目传送门](https://www.luogu.com.cn/problem/P13390)

## 思路

没什么好想的，大模拟，题目让你干什么，你就干什么。

本题分为三大部分，一部分是旋转，一部分是掉落，一部分是判断连线。

### 旋转

将输入的 $b$ 数组旋转，然后存进 $a$ 数组。

如何旋转呢？我们发现，第一行的棋子，旋转后到了第最后一列。第一列的棋子，旋转后到了第一行。它们是沿右上角到左下角的对角线反射的，所以旋转赋值语句是 `a[i][j]=b[n-j+1][i]`。

```cpp
#include<bits/stdc++.h>
using namespace std;
char b[600][600];
char a[600][600];
int main(){
	int t;
	cin>>t;
	for(int d=1;d<=t;d++){
		memset(a,'.',sizeof(a));
		memset(b,'.',sizeof(b));
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			string x;
			cin>>x;
			for(int j=1;j<=n;j++){
				b[i][j]=x[j-1];
			}
		} 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=b[n-j+1][i];
			}
		}
```

现在旋转后的 $b$ 数组存进了 $a$ 数组。

### 掉落

~~我们将问题给牛顿。~~

现将棋子存入 $tmp$ 数组，再位置从低到高重新放进 $a$ 数组，其他位置标为 `.`。

```cpp
		for(int j=1;j<=n;j++){
			char tmp[1001];
			int id=0,tmpid=0;
			for(int i=n;i>=1;i--){
				if(a[i][j]!='.')
					tmp[++id]=a[i][j];
			}
			for(int i=n;i>=1;i--){
				if(tmpid==id)
					a[i][j]='.';
				else
					a[i][j]=tmp[++tmpid];
			}
		}
```

### 判断连线

最后就是判断是否存在连成 $k$ 个棋子。这个部分比较难，暴力枚举每一个点，向八个方向遍历，判断这条直线上是否还存在 $k-1$ 个点。$3 \le n \le 50$，时间复杂度能过。用 check 函数来查找所有点，用 findnode 函数来找以一个点为中心向八个方向最多的连棋个数。

主函数内：

```cpp
		cout<<"Case #"<<d<<": ";
		int ans=check(n,k);
		if(ans==0) cout<<"Neither";
		if(ans==1) cout<<"Red";
		if(ans==2) cout<<"Blue";
		if(ans==3) cout<<"Both";
		cout<<endl;
	}
	return 0;
}
```

check 函数：

```cpp
int check(int n,int k){
	bool ansb=0,ansr=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]=='B'&&ansb==0){
				int ans=findnode(i,j,'B',n);
				if(ans>=k)
					ansb=1;
			}
			if(a[i][j]=='R'&&ansr==0){
				int ans=findnode(i,j,'R',n);
				if(ans>=k)
					ansr=1;
			}
		} 
	}
	if(ansb==0&&ansr==0) return 0;
	if(ansb==1&&ansr==0) return 2;
	if(ansb==0&&ansr==1) return 1;
	if(ansb==1&&ansr==1) return 3;
}
```

findroot 函数：

```cpp
int findnode(int x,int y,char op,int n){
	int f[9];
	memset(f,0,sizeof(f));
	for(int j=y-1;j>=1;j--){if(a[x][j]==op){f[1]++;} else{break;}}// 向左情况 
	for(int j=y+1;j<=n;j++){if(a[x][j]==op){f[2]++;} else{break;}}// 向右情况 
	for(int i=x-1;i>=1;i--){if(a[i][y]==op){f[3]++;} else{break;}}// 向上情况 
	for(int i=x+1;i<=n;i++){if(a[i][y]==op){f[4]++;} else{break;}}// 向下情况
	for(int i=x-1,j=y-1;i>=1&&j>=1;i--,j--){if(a[i][j]==op){f[5]++;} else{break;}}// 向左上情况
	for(int i=x+1,j=y-1;i<=n&&j>=1;i++,j--){if(a[i][j]==op){f[6]++;} else{break;}}// 向左下情况
	for(int i=x-1,j=y+1;i>=1&&j<=n;i--,j++){if(a[i][j]==op){f[7]++;} else{break;}}// 向右上情况
	for(int i=x+1,j=y+1;i<=n&&j<=n;i++,j++){if(a[i][j]==op){f[8]++;} else{break;}}// 向右下情况
	return max(max(f[1]+f[2],f[3]+f[4]),max(f[5]+f[8],f[6]+f[7]))+1;
} 
```

## 代码

[AC 记录](https://www.luogu.com.cn/record/227146447)

```cpp
#include<bits/stdc++.h>
using namespace std;
char b[600][600];
char a[600][600];
int findnode(int x,int y,char op,int n){
	int f[9];
	memset(f,0,sizeof(f));
	for(int j=y-1;j>=1;j--){if(a[x][j]==op){f[1]++;} else{break;}}// 向左情况 
	for(int j=y+1;j<=n;j++){if(a[x][j]==op){f[2]++;} else{break;}}// 向右情况 
	for(int i=x-1;i>=1;i--){if(a[i][y]==op){f[3]++;} else{break;}}// 向上情况 
	for(int i=x+1;i<=n;i++){if(a[i][y]==op){f[4]++;} else{break;}}// 向下情况
	for(int i=x-1,j=y-1;i>=1&&j>=1;i--,j--){if(a[i][j]==op){f[5]++;} else{break;}}// 向左上情况
	for(int i=x+1,j=y-1;i<=n&&j>=1;i++,j--){if(a[i][j]==op){f[6]++;} else{break;}}// 向左下情况
	for(int i=x-1,j=y+1;i>=1&&j<=n;i--,j++){if(a[i][j]==op){f[7]++;} else{break;}}// 向右上情况
	for(int i=x+1,j=y+1;i<=n&&j<=n;i++,j++){if(a[i][j]==op){f[8]++;} else{break;}}// 向右下情况
	return max(max(f[1]+f[2],f[3]+f[4]),max(f[5]+f[8],f[6]+f[7]))+1;
} 
int check(int n,int k){
	bool ansb=0,ansr=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(a[i][j]=='B'&&ansb==0){
				int ans=findnode(i,j,'B',n);
				if(ans>=k)
					ansb=1;
			}
			if(a[i][j]=='R'&&ansr==0){
				int ans=findnode(i,j,'R',n);
				if(ans>=k)
					ansr=1;
			}
		} 
	}
	if(ansb==0&&ansr==0) return 0;
	if(ansb==1&&ansr==0) return 2;
	if(ansb==0&&ansr==1) return 1;
	if(ansb==1&&ansr==1) return 3;
}
int main(){
	int t;
	cin>>t;
	for(int d=1;d<=t;d++){
		memset(a,'.',sizeof(a));
		memset(b,'.',sizeof(b));
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			string x;
			cin>>x;
			for(int j=1;j<=n;j++){
				b[i][j]=x[j-1];
			}
		} 
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=b[n-j+1][i];
			}
		}
		for(int j=1;j<=n;j++){
			char tmp[1001];
			int id=0,tmpid=0;
			for(int i=n;i>=1;i--){
				if(a[i][j]!='.')
					tmp[++id]=a[i][j];
			}
			for(int i=n;i>=1;i--){
				if(tmpid==id)
					a[i][j]='.';
				else
					a[i][j]=tmp[++tmpid];
			}
		}
		cout<<"Case #"<<d<<": ";
		int ans=check(n,k);
		if(ans==0) cout<<"Neither";
		if(ans==1) cout<<"Red";
		if(ans==2) cout<<"Blue";
		if(ans==3) cout<<"Both";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：wenhaoran11 (赞：2)

## 题目简介
给出一个边长为 $n$ 的矩阵，其中有三种字符。判断在顺时针旋转再按重力落下来后，是否有 $R$ 或 $B$ 以横着，竖着或者对角线的方式连成 $k$ 个。

## 主要思路
模拟即可，接下来我将按照题意一一分析三个主要的操作。
## 第一个
将矩阵顺时针旋转。

观察发现旋转时高变成了宽，矩阵的长是高减原来的宽加一，所以就有代码。
```cpp
for(int i=1;i<=n;i++){//矩阵顺时针变换。 
    for(int j=1;j<=n;j++){
        b[j][n-i+1]=a[i][j];
    }
}
```
## 第二个
按照重力往下。

我们可以把每一列从下往上遍历，定义一个指针指向底部，如果有棋子就和底部交换，所以就有代码。
```cpp
for(int j=1;j<=n;j++){//按照重力影响进行操作。 
    int t=n;
    for(int i=n;i>=1;i--){
        if(b[i][j]!='.'){
            char u=b[i][j];
            b[i][j]='.';
            b[t--][j]=u;
        }
    }
}
```
## 第三个
如何判断是否有连成 $k$ 个的线。

这里先看代码会更好理解一些。
```cpp
bool check(char c){//判断是否有连成k个的。 
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(b[i][j]!=c) continue;//不是我们当前想找的R或B。
            for(int k=0;k<4;k++){
                int ans=1;
                int x=i+dx[k];
                int y=j+dy[k];
                while(x>=1&&x<=n&&y>=1&&y<=n&&b[x][y]==c){//满足不能延伸到数组外面与延伸后还是想要的字符。 
                    ans++;
                    x+=dx[k],y+=dy[k];
                    if(ans>=::k) return true;            
                }
            } 
        }
    }
    return false;
} 
```
我们一点一点分析。

首先 $i$ 和 $j$ 的循环就是遍历，而字符 $c$ 表示要判断哪个字符，而 $k$ 则是四个方向。

记录答案的变量初始就要设为一，应为他自己本身也是目标字符，而 $x$ 和 $y$ 表示的就是当前的方向。

还有一点要注意，在循环中不仅要判断新的位置是否是目标字符，还要不能遍历到数组外边去。

如果一切都满足，记录答案的变量加一，将 $x$ 和 $y$ 两个记录位置的变量更新，至此，代码的主要内容就讲完了，接下来按照题意判断输出即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=55;
int T,n,k;
int p=0;
char a[N][N],b[N][N];
int dx[]={0,1,1,1};
int dy[]={1,0,1,-1};
bool check(char c){//判断是否有连成k个的。 
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(b[i][j]!=c) continue;//不是我们当前想找的R或B。
            for(int k=0;k<4;k++){
                int ans=1;
                int x=i+dx[k];
                int y=j+dy[k];
                while(x>=1&&x<=n&&y>=1&&y<=n&&b[x][y]==c){//满足不能延伸到数组外面与延伸后还是想要的字符。 
                    ans++;
                    x+=dx[k],y+=dy[k];
                    if(ans>=::k) return true;            
                }
            } 
        }
    }
    return false;
} 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        p++;
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cin>>a[i][j];
            }
        }
        for(int i=1;i<=n;i++){//矩阵顺时针变换。 
            for(int j=1;j<=n;j++){
                b[j][n-i+1]=a[i][j];
            }
        }
        for(int j=1;j<=n;j++){//按照重力影响进行操作。 
            int t=n;
            for(int i=n;i>=1;i--){
                if(b[i][j]!='.'){
                    char u=b[i][j];
                    b[i][j]='.';
                    b[t--][j]=u;
                }
            }
        }
        bool ans1=check('R');
        bool ans2=check('B');
        if(ans1==1&&ans2==1) printf("Case #%d: Both\n",p);//输出环节 
        else if(ans1==1) printf("Case #%d: Red\n",p);
        else if(ans2==1) printf("Case #%d: Blue\n",p);
        else printf("Case #%d: Neither\n",p);
    }
    return 0;
}
```

---

## 作者：DreamInk (赞：1)

# 题目简述
将一个 $N \times N$ 的棋盘**顺时针旋转一次**，重力会让旋转后的棋盘上的棋子直线垂直下落。判断在顺时针旋转棋盘并让重力生效后，哪一方会在棋盘上连成 $K$ 个棋子，**$K$ 个同色棋子连成一行（可以是横向，纵向或对角线）**，这些题目都给出了示例 [传送门](https://www.luogu.com.cn/problem/P13390) 其实就是一道纯模拟题。

# 思路
### Part.1
先将棋盘顺时针旋转一次。
![](https://cdn.luogu.com.cn/upload/image_hosting/7oilqrwr.png)
我们可以发现原棋盘 $(n-i+1,j) \to $ 新棋盘 $(j,i)$，实现如下（$b$ 数组指新棋盘，$a$ 数组指原棋盘）：
```cpp
b[j][i]=a[n-i+1][j];
```
### Part.2
接着实现重力下移，就是一颗棋子，直线下移，一直到它的正下方有棋子为止，我们可以暴力实现。
```cpp
for (int i=n;i>=1;i--){
    for (int j=1;j<=n;j++){
        if(b[i][j]!='.'){//判断它是一个棋子
          int q=i;//用来记录最大能下移到的位置
          for (int k=i+1;k<=n;k++){//暴力枚举它的直线下方
              if(b[k][j]!='.')break;//这个位置有棋子了，不能下移了
              q=k;//记录
          }
          if(q!=i)b[i][j]='.', b[q][j]=b[i][j];//可以往下移，那么原来的位置便没有棋子，在新位置赋值
        }
    }
}
```
### Part.3
分别判断两种棋子时候是否刚好连成 $K$ 个棋子，可以采用很多方法，我这里便用 dfs 解决，也可以参考楼上几位大佬的做法。（~~蒟蒻太弱了，只会用这个~~）。

```cpp
void dfs(int x,int y,char c,int dir,int cnt){
	if(x<1 || x>n || y<1 || y>n)return ;//判断想x，y越界
	if(f==1)return;//已经可以连成k个棋子便不需要继续搜索
	if(cnt==k){//刚好满足k个棋子
		f=1;//标记
		return ;
	}
  //一直那个方向走
	if(dir==1 && b[x+1][y]==c) dfs(x+1,y,c,1,cnt+1);//横向
	else if(dir==2 && b[x][y+1]==c) dfs(x,y+1,c,2,cnt+1);//纵向
	else if(dir==3 && b[x+1][y-1]==c) dfs(x+1,y-1,c,3,cnt+1);//左斜对角
	else if(dir==4 && b[x+1][y+1]==c) dfs(x+1,y+1,c,4,cnt+1);//右斜对角
}
```
# 完整Code
上面解释这里便不再重复叙述了。
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=55;
int T,n,k,f,f1,f2;
char a[N][N],b[N][N];
void dfs(int x,int y,char c,int dir,int cnt){
	if(x<1 || x>n || y<1 || y>n)return ;
	if(f==1)return;
	if(cnt==k){
		f=1;
		return ;
	}
	if(dir==1 &&b[x+1][y]==c) dfs(x+1,y,c,1,cnt+1);
	else if(dir==2&&b[x][y+1]==c) dfs(x,y+1,c,2,cnt+1);
	else if(dir==3&&b[x+1][y-1]==c)	dfs(x+1,y-1,c,3,cnt+1);
	else if(dir==4&&b[x+1][y+1]==c) dfs(x+1,y+1,c,4,cnt+1);
}
void rotate(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			b[j][i]=a[n-i+1][j];
		}
	}
	for (int i=n;i>=1;i--){
		for (int j=1;j<=n;j++){
			if(b[i][j]!='.'){
				int qi=i;
				for(int k=i+1;k<=n;k++){
					if(b[k][j]!='.')break;
					qi=k;
				}
				if(qi!=i){
                    b[qi][j]=b[i][j];
                    b[i][j]='.';
                }
			}
		}
	}
} 
void work(char x){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f=0;
			if(b[i][j]==x){//往四个方向搜索 
				dfs(i,j,b[i][j],1,1);
				dfs(i,j,b[i][j],2,1);
				dfs(i,j,b[i][j],3,1);
				dfs(i,j,b[i][j],4,1);
			}
			if(f==1)break;//成立便直接退出，不需要继续找 
		}
		if(f==1)break;//退！退！TUI！
	}
}
void solve(){
	memset(b,0,sizeof b);
	for(int i=1;i<=n;i++){//输入原棋盘 
		for(int j=1;j<=n;j++) {
			cin>>a[i][j];
		}
	}
	rotate();//旋转+重力下移 
	f1=0,f2=0;//标记两种棋子是否连成k个棋子 
	work('R');//分别判断两种棋子 
	if(f==1)f1=1;
	work('B');
	if(f==1)f2=1;
	//输出相应结果，注意开头大写 ！！！
	if(f1==1 && f2==1)	cout<<"Both"<<endl;
	else if(f1==0 && f2==0)  cout<<"Neither"<<endl;
	else if(f1==1)	cout<<"Red"<<endl;
	else cout<<"Blue"<<endl;
}

int main(){
	cin>>T;
	for(int i=1;i<=T;i++){//主程序读入(这应该不用解释吧) 
        cout<<"Case #"<<i<<": ";
		cin>>n>>k;
		solve();
	}	
	return 0;
}
```
# 完结撒花
这虽然是一道橙题，但非常考验写代码和调试代码的能力，蒟蒻写题解不易，求您点个赞吧！

管理员大大您辛苦了，这是蒟蒻的第二篇题解，求过。

---

## 作者：weapons (赞：1)

## 题意
  给你一个方阵，将其顺时针旋转 $90$ 度后，模拟重力效果，记录目标字符是否在同一横，列，斜向上能连成 k 个字符。
## 实现
  纯模拟，模拟重力只需在旋转后枚举每一个字符，看下面是不是点，如果是的话就交换，这里需要注意从下往上枚举，然后继续看这一个字符下面是不是点，重复以上操作，直到下面不是点。处理完后，再每一个字符跑 DFS 检查在同一字符连成的同一排中是否有目标个字符，最后输出即可。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char mp[55][55];
int T, n, k, cx[5] = {0, 0, 1, 1, 1}, cy[5] = {0, 1, 0, -1, 1}, ans1, ans2, pan1, pan2;//ans1 记录B连成一排的最大数量，ans2记录R的，pan1，pan2记录是否有k个  
void find(int x, int y, int nwb, int nwr, int a) {
	ans1 = max(ans1, nwb);
	ans2 = max(ans2, nwr);
	if (x + cx[a] <= n && y + cy[a] <= n && x + cx[a] >= 1 && y + cy[a] >= 1) {
		int nx = x + cx[a], ny = y + cy[a];
		if (mp[nx][ny] == mp[x][y]) {
			if (mp[nx][ny] == 'B') {
				find(nx, ny, nwb + 1, 0, a);
			}
			if (mp[nx][ny] == 'R') {
				find(nx, ny, 0, nwr + 1, a);
			} else if (mp[nx][ny] == '.')find(nx, ny, 0, 0, a);
		} else {
			if (mp[nx][ny] == 'B') {
				find(nx, ny, 1, 0, a);
			}
			if (mp[nx][ny] == 'R') {
				find(nx, ny, 0, 1, a);
			} else if (mp[nx][ny] == '.')find(nx, ny, 0, 0, a);
		}
	}
}//检查同一字符连成一排中是否有k个字符 
void J() {
	if (ans1 >= k)pan1 = 1;
	if (ans2 >= k)pan2 = 1;
	ans1 = ans2 = 0;
}// 判断是否有k个 
int main() {
	cin >> T;
	for (int v = 1; v <= T; v++) {
		cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				mp[i][j] = '.';
			}
		}//初始化 
		for (int i = n; i >= 1; i--) {
			for (int j = 1; j <= n; j++) {
				cin >> mp[j][i];
			}
		}//先输入列再输入行就能达到旋转效果 
		for (int i = n; i >= 1; i--) {
			for (int j = 1; j <= n; j++) {
				if (mp[i][j] != '.') {
					char c = mp[i][j];
					for (int t = i + 1; t <= n && mp[t][j] == '.'; t++) {
						mp[t][j] = c;
						mp[t - 1][j] = '.';//其实就是swap 
					}
				}
			}
		}//模拟重力 
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int aa = 0, bb = 0;
				if (mp[i][j] == 'B')aa = 1;
				if (mp[i][j] == 'R')bb = 1;
				for (int w = 1; w <= 4; w++) {
					find(i, j, aa, bb, w);
				}//每个字符跑dfs 
			}
		}
		J();
		cout << "Case #" << v << ": ";
		if (pan1 && pan2) {
			cout << "Both" << endl;
		}
		else if (pan1) {
			cout << "Blue" << endl;
		}
		else if (pan2) {
			cout << "Red" << endl;
		}
		else if (!pan1 && !pan2) {
			cout << "Neither" << endl;
		}
		ans1 = ans2 = pan1 = pan2 = 0; 
	}
}
```

---

## 作者：YuTinMin (赞：0)

## 思路

模拟，太有实力了，牛顿最爱的一题。

题目说要把棋盘顺时针旋转90度，先写一个函数 `rot` 实现顺时针旋转，并存储在 `b` 里面。旋转的时候，原来的高变成了宽，高就成了矩阵的长减去原来的宽加一，就是 `b[j][n - i + 1] = a[i][j]`。

重力怎么办呢？那就把 `b` 从下往上遍历，一列一列地遍历，然后定义一个指针来指向底部，遇到棋子的时候就与底部交换。

现在写一个 `check` 就简单了，就一直沿着一个方向走下去，要是记录到的数量大于 `K`，那就是可以了，直接返回 `true`。然后四个方向，分别是左右、上下和两条斜边。

主函数就更简单了，定义 `bool` 变量，判断是否胜利，如果两个都为真，就是平局。只有一个为真，就是为真的赢。如果全为假，那就输出 `Neither`。

看代码吧。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 55;
char a[MAX][MAX], b[MAX][MAX];
int dx[] = {0, 1, 1, 1};
int dy[] = {1, 0, 1, -1};
int n, k;

// 旋转90度顺时针
void rot()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            b[j][n - i + 1] = a[i][j];
        }
    }
}

// 重力作用
void grav()
{
    for (int j = 1; j <= n; j++)
    {
        int p = n;
        for (int i = n; i >= 1; i--)
        {
            if (b[i][j] != '.')
            {
                char t = b[i][j];
                b[i][j] = '.';
                b[p--][j] = t;
            }
        }
    }
}

// 检查是否连成K个
bool check(char c)
{

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (b[i][j] != c)
                continue;
            for (int d = 0; d < 4; d++)
            {
                int cnt = 1;
                int x = i + dx[d];
                int y = j + dy[d];
                while (x >= 1 && x <= n && y >= 1 && y <= n && b[x][y] == c)
                {
                    cnt++;
                    x += dx[d];
                    y += dy[d];
                    if (cnt >= k)
                        return true;
                }
            }
        }
    }

    return false;
}

int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> a[i][j];
        rot();
        grav();

        bool rl = check('R');
        bool bl = check('B');

        if (rl && bl)
            printf("Case #%d: Both \n", t);
        else if (rl)
            printf("Case #%d: Red \n", t);
        else if (bl)
            printf("Case #%d: Blue \n", t);
        else
            printf("Case #%d: Neither \n", t);
    }

    system("pause");
    return 0;
}

```

---

