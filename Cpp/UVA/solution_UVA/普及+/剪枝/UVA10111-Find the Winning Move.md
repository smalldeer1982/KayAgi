# Find the Winning Move

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1052

[PDF](https://uva.onlinejudge.org/external/101/p10111.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10111/ebca7c72e9448d503158b6014fa855835320092f.png)

## 样例 #1

### 输入

```
?
....
.xo.
.ox.
....
?
o...
.ox.
.xxx
xooo
$```

### 输出

```
#####
(0,1)```

# 题解

## 作者：创世游戏科技 (赞：3)

## 题目大意
 Tic-Tac-Toe 游戏是在四行四列的棋盘上 进行。有两名玩家  A  和  B  ，分别执  `X`  和  `O` ，  A  和  B  轮流走子，玩家  A  先行。如果某位玩家先于对方将己方的四个棋子沿着同一行、或同一列、或同一对角线连成直线则获胜。

**给定一个已经部分完成的棋盘状态,接下来是玩家  A  行棋。编写程序,确定玩家  A  是否具有必胜策略。**

## 思路分析

对于一个局面 $ M $ ，其为一位玩家的**必胜态**的充要条件为存在 $ Q $ 为 $ M $ 的后继状态，使得 $ Q $ 为另一位玩家的**必败态**。

通俗来说就是可以通过选择把必败的局面留给对方，自己就必胜了。

那么必败态的定义就是任意 $ Q $ 为 $ M $ 的后继状态，$ Q $ 都为另一位玩家**必胜态**。

通俗来说就是无论怎么选对方都是必胜，自己就必败了。

**那么平局怎么考虑呢？**

我们研究问题是对  A  考虑的，那么形成平局也是与必胜态相对的必败态。

具体而言，如果形成平局的是  A  ，对于  A  就是必败态，反之对于  B  就是必败态。

考虑到数据范围，我们可以采用搜索的方式解决问题。

对于每个局面，我们枚举所有可能。同时求出后继状态有无另一个玩家的必败态，有则为必胜态，反之为必败态。

当胜负已分或者平局的时候，我们直接返回该玩家是否胜利即可。

我们发现如果对于一个已经确定了的状态，我们如果已经处理过，就没必要再次处理。可以直接返回。

对于一个棋盘最多 $ 3^{16} $ 种状态，时间复杂度可以接受。

  check  函数直接暴力展开，显著优化代码速度。


```
#include <bits/stdc++.h>
using namespace std;
int mp[4][4],mpg[4][4];
int nowx=0,nowy=0;
int check(){
	if(mp[0][0]+mp[0][1]+mp[0][2]+mp[0][3]==4&&mp[0][0]&&mp[0][1]&&mp[0][2]&&mp[0][3])return true;
	if(mp[1][0]+mp[1][1]+mp[1][2]+mp[1][3]==4&&mp[1][0]&&mp[1][1]&&mp[1][2]&&mp[1][3])return true;
	if(mp[2][0]+mp[2][1]+mp[2][2]+mp[2][3]==4&&mp[2][0]&&mp[2][1]&&mp[2][2]&&mp[2][3])return true;
	if(mp[3][0]+mp[3][1]+mp[3][2]+mp[3][3]==4&&mp[3][0]&&mp[3][1]&&mp[3][2]&&mp[3][3])return true;
	if(mp[0][0]+mp[0][1]+mp[0][2]+mp[0][3]==8&&mp[0][0]&&mp[0][1]&&mp[0][2]&&mp[0][3])return false;
	if(mp[1][0]+mp[1][1]+mp[1][2]+mp[1][3]==8&&mp[1][0]&&mp[1][1]&&mp[1][2]&&mp[1][3])return false;
	if(mp[2][0]+mp[2][1]+mp[2][2]+mp[2][3]==8&&mp[2][0]&&mp[2][1]&&mp[2][2]&&mp[2][3])return false;
	if(mp[3][0]+mp[3][1]+mp[3][2]+mp[3][3]==8&&mp[3][0]&&mp[3][1]&&mp[3][2]&&mp[3][3])return false;
	if(mp[0][0]+mp[1][0]+mp[2][0]+mp[3][0]==4&&mp[0][0]&&mp[1][0]&&mp[2][0]&&mp[3][0])return true;
	if(mp[0][1]+mp[1][1]+mp[2][1]+mp[3][1]==4&&mp[0][1]&&mp[1][1]&&mp[2][1]&&mp[3][1])return true;
	if(mp[0][2]+mp[1][2]+mp[2][2]+mp[3][2]==4&&mp[0][2]&&mp[1][2]&&mp[2][2]&&mp[3][2])return true;
	if(mp[0][3]+mp[1][3]+mp[2][3]+mp[3][3]==4&&mp[0][3]&&mp[1][3]&&mp[2][3]&&mp[3][3])return true;
	if(mp[0][0]+mp[1][0]+mp[2][0]+mp[3][0]==8&&mp[0][0]&&mp[1][0]&&mp[2][0]&&mp[3][0])return false;
	if(mp[0][1]+mp[1][1]+mp[2][1]+mp[3][1]==8&&mp[0][1]&&mp[1][1]&&mp[2][1]&&mp[3][1])return false;
	if(mp[0][2]+mp[1][2]+mp[2][2]+mp[3][2]==8&&mp[0][2]&&mp[1][2]&&mp[2][2]&&mp[3][2])return false;
	if(mp[0][3]+mp[1][3]+mp[2][3]+mp[3][3]==8&&mp[0][3]&&mp[1][3]&&mp[2][3]&&mp[3][3])return false;
	if(mp[0][0]+mp[1][1]+mp[2][2]+mp[3][3]==4&&mp[0][0]&&mp[1][1]&&mp[2][2]&&mp[3][3])return true;
	if(mp[0][0]+mp[1][1]+mp[2][2]+mp[3][3]==8&&mp[0][0]&&mp[1][1]&&mp[2][2]&&mp[3][3])return false;
	if(mp[0][3]+mp[1][2]+mp[2][1]+mp[3][0]==4&&mp[0][3]&&mp[1][2]&&mp[2][1]&&mp[3][0])return true;
	if(mp[0][3]+mp[1][2]+mp[2][1]+mp[3][0]==8&&mp[0][3]&&mp[1][2]&&mp[2][1]&&mp[3][0])return false;
	return 2;
}

bool full(){
	bool flag=true;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(!mp[i][j])flag=false;
		}
	}
	return flag;
}
int has(){
	int t=0;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			t=t*3+mp[i][j];
		}
	}
	return t;
}
unordered_map<int,bool>vis;
int dfs(int op){//op=1时为A，op=0时为B
	if(vis.find(has())!=vis.end())return vis[has()];
	int ans=check();
	if(ans!=2){
		return op==ans;
        //胜负已分
	}
	if(full()&&ans==2){
		return !op;
        //平局
	}
	bool flag=false;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(mp[i][j]!=0)continue;
			if(op==1)mp[i][j]=1;
			else mp[i][j]=2;
			flag=max(flag,!dfs(op^1));
			mp[i][j]=0;
		}
	}
    //枚举后继状态
	vis[has()]=flag;
	return flag;
}
int main(){
	label:char s;
	while(cin>>s&&s=='?'){
		vis.clear();
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				char str;cin>>str;
				if(str=='.')mpg[i][j]=0;
				else if(str=='x')mpg[i][j]=1;
				else if(str=='o')mpg[i][j]=2;
			}
		}
        bool flag=false;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				memcpy(mp,mpg,sizeof mpg);
				if(mp[i][j])continue;
				mp[i][j]=1;
                //A先操作
				if(!dfs(0)){
                     //如果是B的必败局，那么就是A的必胜局
					cout<<"("<<i<<","<<j<<")"<<endl;
					break;
				}
			}
            if(flag)break;
		}
        if(!flag)cout<<"#####"<<endl;
	}
	return 0;
}
```

---

## 作者：Lacuna (赞：2)

### 思路：

爆搜肯定不行，考虑 Minimax 加 Alpha-Beta 剪枝。不会的可以看[这里](https://oi-wiki.org/search/alpha-beta/)。

我们通过 Minimax 算法模拟两名玩家交替下棋的过程，枚举可供落子的点，落子后继续搜索之后的状态，直到出现以下情况：

1. 某一方获胜，此时返回一个状态，例如我方获胜返回 $1$，敌方获胜返回 $-1$。我方获胜的返回值需大于敌方获胜的返回值，因为后面的 Alpha-Beta 剪枝要用。

2. 棋盘填满，此时返回 $0$。返回的值介于两者中间。

再设一个可能达到的最大下界，用 $alpha$ 表示，同理设一个可能达到的最小上界，用 $beta$ 表示，当 $alpha \ge beta$ 时，就可以将剩下的状态减掉。因为我们不可能在搜到比这更优的方案。仔细观察发现这里的 $alpha$ 和 $beta$ 其实就是我们设的那三种状态，按对我方的有利程度从大到小排序。

最开始时我们枚举一个我方落子的点，若能获胜直接返回坐标，否则跑 Minimax 搜索去评估在这个点落子的优劣性，若返回值等于 $1$，说明我方有必胜策略，返回该点坐标。

否则输出无解。

### 实现细节：

棋盘落子需改变棋盘的状态，为了方便，我们用临时数组存储落子后棋盘的状态，搜索时当做参数传进去即可。

### 代码，可以看看注释：


```cpp
#include<bits/stdc++.h>
using namespace std;
#define gc getchar
template<typename T>inline void read(T&x){x=0;char ch=gc();while(ch<'0'||ch>'9')ch=gc();while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=gc();}}
template<typename T,typename ...T1>inline void read(T&x,T1&...x1){read(x);read(x1...);}
const int ri=105;
struct node{int x,y; node(int l=-1,int r=-1):x(l),y(r){}};//结构体存坐标 
char T[ri][ri]; string s,a[ri]; int tot;
bool check(char E[ri][ri],char player){//判断player这方是否获胜 
  for(int i=0;i<4;i++){
  	if(E[i][0]==player&&E[i][1]==E[i][2]&&E[i][2]==E[i][3]&&E[i][0]==E[i][1])
  	  return true;
  }
  for(int i=0;i<4;i++){
  	if(E[0][i]==player&&E[1][i]==E[2][i]&&E[2][i]==E[3][i]&&E[0][i]==E[1][i])
  	  return true;
  }
  if(E[1][1]==player&&E[2][2]==player&&E[3][3]==player&&E[0][0]==player)
    return true;
  if(E[0][3]==player&&E[1][2]==player&&E[2][1]==player&&E[3][0]==player)
    return true;
  return false;
}bool full(char E[ri][ri]){//判断棋盘是否被填满，即平局 
  for(int i=0;i<4;i++) for(int j=0;j<4;j++) if(E[i][j]=='.') return false;
  return true;
}int alpha_beta(char Y[ri][ri],int alpha,int beta,bool ismax){//Minimax搜索+Alpha-Beta剪枝 
  if(check(Y,'x')) return 1;//我方获胜 
  if(check(Y,'o')) return -1;//敌方获胜 
  if(full(Y)) return 0;//平局 
  if(ismax){//取最优值，即我方落子 
  	int mx=-0x3f3f3f3f;
  	for(int i=0;i<4;i++){//枚举可以落子的点 
      for(int j=0;j<4;j++){
  	    if(Y[i][j]=='.'){
          char T[ri][ri];
  	      for(int x=0;x<4;x++) for(int y=0;y<4;y++) T[x][y]=Y[x][y];
		  T[i][j]='x'; int tmp=alpha_beta(T,alpha,beta,false);
		  mx=max(mx,tmp); alpha=max(alpha,tmp);//更新，取最优值 
		  if(beta<=alpha) break;//Alpha-Beta剪枝 
		}
	  }
	  if(beta<=alpha) break;
    }
	return mx;
  }else{////取最劣值，即敌方落子 
  	int mi=0x3f3f3f3f;
  	for(int i=0;i<4;i++){//同理，枚举可以落子的点 
      for(int j=0;j<4;j++){
  	    if(Y[i][j]=='.'){
          char T[ri][ri];
  	      for(int x=0;x<4;x++) for(int y=0;y<4;y++) T[x][y]=Y[x][y];
		  T[i][j]='o'; int tmp=alpha_beta(T,alpha,beta,true); 
		  mi=min(mi,tmp); beta=min(beta,tmp);//更新，取最劣值 
		  if(beta<=alpha) break;
		}
	  }
	  if(beta<=alpha) break;
    }
	return mi;
  }
}node move(char E[ri][ri]){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(E[i][j]=='.'){//枚举可以落子的点 
        char T[ri][ri];
        for(int x=0;x<4;x++) for(int y=0;y<4;y++) T[x][y]=E[x][y];
	    T[i][j]='x'; if(check(T,'x')) return node(i,j);//直接获胜 
	    if(alpha_beta(T,-0x3f3f3f3f,0x3f3f3f3f,false)==1)  return node(i,j);//有必胜策略 
	  }
	}
  }
  return node();//没有必胜策略 
}
int main(){
  while(getline(cin,s)&&s!="$") a[++tot]=s;
  for(int i=1;i<=tot; ){
  	if(a[i]=="?"){
  	  i++; char T[ri][ri];//临时存棋盘 
	  for(int x=0;x<4;x++,i++) for(int y=0;y<4;y++) T[x][y]=a[i][y];
	  node mov=move(T);
	  if(mov.y==-1) puts("#####");
	  else printf("(%d,%d)\n",mov.x,mov.y);
	}else i++;
  }
  return 0;
}
```

---

## 作者：Wilson_Lee (赞：1)

既然还没有人写题解，那我就来补一篇……

#### 一.题意

![题意](https://cdn.luogu.com.cn/upload/image_hosting/fp58ao7w.png)

#### 二.解法

很明显这是一道博弈论题目，对于这一类题目有以下结论：

 $1$ .若当前局面的下一局面均为必胜局面（对于另一玩家），那么该局面为必败局面（对当前玩家）。

 $2$ .若当前局面的下一局面存在必败局面（对于另一玩家），那么该局面为必胜局面（对当前玩家）。

在本题中，状态为四 x 相连的局面为初始必胜局面。

然后就可以愉快的暴搜了。

但直接搜很显然会超时，因为可能状态共有 $3^{16}$ 种，会 TLE 。

然而本蒟蒻并不会 alpha-beta 剪枝，只能靠记忆化来维持一下复杂度。

~~然而管理大大觉得说的过于简单，那我就详细讲一下暴搜的过程qwq%%%~~

总共分四步：

 $1$ .判断当前状态是否已经被搜过（即是否能确认必胜或必败）。

 $2$ .判断当前局面是否为必胜局面，如果是，那么当前玩家输了（因为是上一个人走到的这个局面）。

 $3$ .试填空格，模拟玩家填 x 或 o （搜到必胜态直接返回）。

 $4$ .如果没有找到必胜态，那么只能是必败态或平局，二者在本题中均可视为必败态。

```cpp
int dfs(int player)
{
	//第一步
    //判断当前状态是否已经被搜过（即是否能确认必胜或必败）
    if(player==X)  //记忆化不用多说
    {
        if(wx.find(broad)!=wx.end()) return X_WIN;
        if(lx.find(broad)!=lx.end()) return X_LOSE;
    }
    
    //第二步
    //判断当前局面是否为必胜局面，如果是，那么当前玩家输了（因为是上一个人走到的这个局面）
    if(player==X && iswin(broad)) return X_LOSE;
    if(player==O && iswin(broad>>16)) return O_LOSE;
    
    //第三步
    //试填空格，模拟玩家填 x 或 o
    for(int i=1;i<=tot;++i)
    {
        if(used[i]) continue;  //如果这个空格之前被填过了就不用再填了
        used[i]=1;
        if(player==X) broad|=(1<<(16+empty[i]));  //这里还要左移16位的原因是前16位存的是X的状态，后16位存的是O的状态，如果当前玩家是X，我们需要改变的是X的状态
        else broad|=(1<<empty[i]);
        int nxt=dfs(player^1);
        used[i]=0;    //注意回溯
        if(player==X) broad^=(1<<(16+empty[i]));
        else broad^=(1<<empty[i]);
        if(player==X && nxt==O_LOSE)
        {
            wx.insert(broad);
            return X_WIN;
        }
        if(player==O && nxt==X_LOSE) return O_WIN;
    }
    
    //第四步
    if(player==X)  //无必胜策略，即必输和平局可视为同一种情况
    {
        lx.insert(broad);
        return X_LOSE;
    }
    return O_LOSE;
}
```

#### 三.代码

~~其实给不给都无所谓了，实现主要还是个人写法的区别。~~

这里用 int 存储 x 和 o 的当前局面（ int 能存 $32$ 位，前 $16$ 位存 x ，后 $16$ 位存 o ）。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int X=0,O=1;
const int X_WIN=0,X_LOSE=1,O_WIN=2,O_LOSE=3;
string bits[10]={     //这里存储获胜局面（共16种），这里相当于是把棋盘拉成一条线，坐标(x,y)转化为x*4+y(从0开始编号)
    "1111000000000000","0000111100000000","0000000011110000","0000000000001111",
    "1000100010001000","0100010001000100","0010001000100010","0001000100010001",
    "1000010000100001","0001001001001000"
};
int win[10],empty[16];  //获胜局面转化为整型（方便判断），存储空格位置
set<int>wx,lx;    //记忆化
bool used[16];
int broad,tot,cnt;
bool iswin(int now)
{
    for(int i=0;i<10;++i)
        if((now&win[i])==win[i]) return 1;
    return 0;
}
int dfs(int player)
{
    if(player==X)
    {
        if(wx.find(broad)!=wx.end()) return X_WIN;
        if(lx.find(broad)!=lx.end()) return X_LOSE;
    }
    //判断当前局面是否为必胜局面，如果是，那么当前玩家输了（因为是上一个人走到的这个局面）
    if(player==X && iswin(broad)) return X_LOSE;
    if(player==O && iswin(broad>>16)) return O_LOSE;
    for(int i=1;i<=tot;++i)
    {
        if(used[i]) continue;
        used[i]=1;
        if(player==X) broad|=(1<<(16+empty[i]));
        else broad|=(1<<empty[i]);
        int nxt=dfs(player^1);
        used[i]=0;
        if(player==X) broad^=(1<<(16+empty[i]));
        else broad^=(1<<empty[i]);
        if(player==X && nxt==O_LOSE)
        {
            wx.insert(broad);
            return X_WIN;
        }
        if(player==O && nxt==X_LOSE) return O_WIN;
    }
    if(player==X)  //无必胜策略，即必输和平局可视为同一种情况
    {
        lx.insert(broad);
        return X_LOSE;
    }
    return O_LOSE;
}
int main()
{
    ios::sync_with_stdio(false);
    for(int i=0;i<10;++i)
    {
        bitset<16>now(bits[i]);
        win[i]=(int)now.to_ulong();
    }
    char tmp;
    while(cin>>tmp && tmp!='$')
    {
        if(tmp!='?') continue;
        broad=tot=cnt=0;
        while(cnt<16)
        {
            cin>>tmp;
            if(tmp!='.' && tmp!='x' && tmp!='o') continue;
            if(tmp=='.') empty[++tot]=cnt;
            else if(tmp=='x') broad|=(1<<(16+cnt));
            else broad|=(1<<cnt);
            ++cnt;
        }
        memset(used,0,sizeof(used));
        bool flag=0;
        for(int i=1;i<=tot;++i)
        {
            if(!used[i])
            {
                used[i]=1;
                broad|=(1<<(16+empty[i]));
                if(dfs(O)==O_LOSE)   //如果有必胜策略
                {
                    cout<<"("<<(empty[i]/4)<<","<<empty[i]%4<<")"<<endl;
                    flag=1;
                    break;
                }
                used[i]=0;
                broad^=(1<<(16+empty[i]));
            }
        }
        if(!flag) cout<<"#####"<<endl;
    }
    return 0;
}
```


---

