# Game of chess unfinished

## 题目描述

## 题意

一天Volodya在博物馆看到一个棋盘参展。棋盘上只剩下四个棋子：两个白车，白王和黑王。“啊哈，黑方肯定没赢！”Volodya肯定的说。你的任务是判断白方是否赢了。

棋盘上的每个棋子在一个正确的位置（每一个占据一个格子，没有两个棋子占据同一个格子，国王不能在同一个格子）。因此，你的任务是判断白方是否获胜。我们会提醒你，这意味着现在的黑王可以被对方的一个棋子吃掉，也不能移动到不败的位置。车可以移动水平或垂直的任意数量的格子（假设路径上没有其他棋子），国王可以移动到相邻的格子（或角或边）。当然，棋子不能离开棋盘。黑王可以吃掉白车（见样例3）。

## 样例 #1

### 输入

```
a6 b4 c8 a8
```

### 输出

```
CHECKMATE
```

## 样例 #2

### 输入

```
a6 c4 b6 b8
```

### 输出

```
OTHER
```

## 样例 #3

### 输入

```
a2 b1 a3 a1
```

### 输出

```
OTHER
```

# 题解

## 作者：清小秋ovo (赞：2)

# CF42B

一道细节蛮多的大模拟。

## 题意

比较简单，给出一个国际象棋残局（只有两个白车，白王，黑王），判断白方是否能赢。


## 解题思路

关键就在于“能赢”的这一条件转化：

通过思考不难发现，如果白方能赢，则黑王当前一定在被将军的情况下同时周围 $8$ 个方向均无法行走，此时输出 `CHECKMATE`, 否则输出 `OTHER`。

那么由此可以得到我们的解题思路，也就是首先标记出所有不能走的位置 （ 也就是两个白车和白王的攻击范围），随后分别模拟 $8$ 个不同的位置，判断是否可走。

当然这里也需要判断攻击范围内是否存在其他的棋子进行阻挡。

这里其实已经很麻烦了，但是最细节的一点就在于黑王还可以吃掉其他白子来~~苟延残喘~~确保游戏继续。

这里我的想法比较简单，就是标记出每个棋子可不可以吃，如果这个棋子可以吃，那么同样这个格子也是能走的。

那么如何应该判断一个棋子能不能吃呢？其实很简单。
只需要在扫描白棋 $a$ 的攻击范围时，如果扫描到了友军棋子 $b$，就说明倘若黑王吃掉了棋子 $b$，则会立马暴露在子 $a$ 的攻击范围之下，证明该棋子不可吃。

反之，如果在全部扫描完所有棋子的攻击范围后，国王找到了一个未被标记过的棋子，则说明吃掉该棋子后不会暴露在其他棋子的攻击范围下，证明该棋子可吃。

## 代码

代码有些长，所以我分批放了。

首先是棋子坐标的存储和棋盘状态的存储:
棋子用一个结构体存，棋盘用一个二维数组存储。

```cpp
struct pieces{int x, y;};

int conv(char  a){return (a-'a'+1);} //坐标转换函数

pieces a[5]; //a1为白车1,a2表示白车2，a3表示白王, a4表示黑王.
int vis[10][10]; //地图
bool is_attack; //当前是否有将军
int d[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}}; //8个方向
char x; //定义一个char做为输入
```


我们再来看一下主函数的内容: 

```cpp
int main()
{
   input(); //输入数据
   car_range(a[1].x, a[1].y); // 判断第一个车的有效攻击范围
   car_range(a[2].x, a[2].y); // 第二个车
   king_range(a[3].x,a[3].y); // 判断国王的攻击范围
   check_king(a[4].x,a[4].y); // 模拟国王所有可走的位置，找到可行的解
   cout<<"CHECKMATE"<<endl;  //如果此时程序还在运行，checkmate
   return 0;
}
```

首先是输入函数:

```cpp
void input(){
    for(int i=1;i<=4;i++){
        int x_pos,y_pos;
        cin>>x, x_pos = conv(x); cin>>y_pos;
        a[i].x = x_pos,a[i].y = y_pos;
        if(i<4) vis[x_pos][y_pos] = 1; //1 ->白棋
        else vis[x_pos][y_pos] = 2; //2 ->黑棋
    }
}
```

然后是判断两个车的攻击范围:

分别从那个车的左，右，上，下扫到头。

这里有几个细节：
1. 如果扫到国王则更改将军状态。
2. 如果扫到友军则标记为 $4$, 表示该棋子不可吃。
3. 攻击范围标记用数字 $3$ 表示。

```cpp
void car_range(int x, int y){
    for(int i=y+1;i<=8;i++){ //横向
        if(i>8)break;
        if(vis[x][i]==0||vis[x][i]==3)vis[x][i]=3;
        else if(vis[x][i]==2)is_attack = true;
        else if(vis[x][i]==1){
            if(i!=y)vis[x][i]=4;
            break;
        }else break;
    }
    for(int i=y-1;i>=1;i--){
        if(i<1)break;
        if(vis[x][i]==0||vis[x][i]==3) vis[x][i]=3;
        else if(vis[x][i]==2) is_attack = true;
        else if(vis[x][i]==1){
            if(i!=y)vis[x][i]=4;
            break;
        }else break;
    }
    for(int i=x+1;i<=8;i++){ //纵向
        if(i>8)break;
        if(vis[i][y]==0||vis[i][y]==3)vis[i][y]=3;
        else if(vis[i][y]==2)is_attack = true;
        else if(vis[i][y]==1){
            if(i!=x)vis[i][y]=4;
            break;
        }else break;
    }
    for(int i=x-1;i>=1;i--){
        if(i<1)break;
        if(vis[i][y]==0||vis[i][y]==3)vis[i][y]=3;
        else if(vis[i][y]==2) is_attack = true;
        else if(vis[i][y]==1){
            if(i!=x)vis[i][y]=4;
            break;
        }else break;
    }
}
```
然后是模拟国王的 $8$ 个不同走法，进行染色，方法通上。

```cpp
void king_range(int x, int y){
    for(int i=0;i<8;i++){
        int x1 = x+d[i][0];
        int y1 = y+d[i][1];
        if(x1<1||y1<1||x1>8||y1>8)continue;
        if(vis[x1][y1]==0||vis[x1][y1]==3)vis[x1][y1]=3;
        if(vis[x1][y1]==1)vis[x1][y1]=4;
        if(vis[x1][y1]==2)is_attack=true;
    }
}
```
最后是检查黑王的所有走法，看是否存在合法的，只要格子是 $0$ 或者 $1$ 就可以走。

如果都不可以走就判断当前是否将军。如果不将军就可以呆在原地。

```cpp
void check_king(int x, int y){
    for(int i=0;i<8;i++){
        int x1 = x+d[i][0];
        int y1 = y+d[i][1];
        if(x1<1||y1<1||x1>8||y1>8)continue;
        if(vis[x1][y1]==0||vis[x1][y1]==1){
            if(x1!=a[3].x||y1!=a[3].y){
                cout<<"OTHER"<<endl;
                exit(0);
            }
        }
    }
    if(!is_attack){
        cout<<"OTHER"<<endl;
        exit(0);
    }
}
```

然后就完美过掉啦!

[![Tz8yGD.jpg](https://s4.ax1x.com/2022/01/06/Tz8yGD.jpg)](https://imgtu.com/i/Tz8yGD)















---

## 作者：Mint_Flipped (赞：2)

这道题就是在判断黑王会不会被吃掉。

黑王可以选择不动或者移动到相邻的格子（或角或边），一共9种情况 。

只要有一种情况下不被吃掉，那么就输出OTHER，否则就输出CHECKMATE。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string a,b,c,d;
    int a1[2],b1[2],c1[2],d1[2];
    cin>>a>>b>>c>>d;
    a1[0]=a[0]-96,a1[1]=a[1]-48; //首先记录4个棋子的位置
    b1[0]=b[0]-96,b1[1]=b[1]-48;
    c1[0]=c[0]-96,c1[1]=c[1]-48;
    d1[0]=d[0]-96,d1[1]=d[1]-48;
    for(int i=-1; i<2; ++i)
    {
        for(int j=-1; j<2; ++j)
        {                       //模拟黑王的移动
            int x=d1[0]+i; 
            int y=d1[1]+j; 
            bool judge[4]= {0}; //判断移动后能否吃掉其他棋子
            if(x>0&&x<9&&y>0&&y<9)
            {
                if(x==a1[0]&&y==a1[1])
                    judge[1]=1;
                else if(x==b1[0]&&y==b1[1])
                    judge[2]=1;
                else if(x==c1[0]&&y==c1[1])
                    judge[3]=1;
                bool mapp[10][10]= {0}; //定义一张棋盘
                if(!judge[1]) //白车1没被吃掉的情况
                {
                    int te=-1; //模拟车可以移动水平或垂直的任意数量的格子（假设路径上没有其他棋子）
                    for(int k=1; k<9; ++k)
                        if(a1[0]==c1[0]&&k==c1[1])
                            te=k;
                    if(te==-1)
                        for(int k=1; k<9; ++k)
                            mapp[a1[0]][k]=1;
                    else if(te<a1[1])
                        for(int k=te+1; k<9; ++k)
                            mapp[a1[0]][k]=1;
                    else
                        for(int k=1; k<te; ++k)
                            mapp[a1[0]][k]=1;
                    te=-1;
                    for(int k=1; k<9; ++k)
                        if(k==c1[0]&&a1[1]==c1[1])
                            te=k;
                    if(te==-1)
                        for(int k=1; k<9; ++k)
                            mapp[k][a1[1]]=1;
                    else if(te<a1[0])
                        for(int k=te+1; k<9; ++k)
                            mapp[k][a1[1]]=1;
                    else
                        for(int k=1; k<te; ++k)
                            mapp[k][a1[1]]=1;
                }
                if(!judge[2]) //白车2没被吃掉的情况
                {
                    int te=-1;  //模拟车可以移动水平或垂直的任意数量的格子（假设路径上没有其他棋子）
                    for(int k=1; k<9; ++k)
                        if(b1[0]==c1[0]&&k==c1[1])
                            te=k;
                    if(te==-1)
                        for(int k=1; k<9; ++k)
                            mapp[b1[0]][k]=1;
                    else if(te<b1[1])
                        for(int k=te+1; k<9; ++k)
                            mapp[b1[0]][k]=1;
                    else
                        for(int k=1; k<te; ++k)
                            mapp[b1[0]][k]=1;
                    te=-1;
                    for(int k=1; k<9; ++k)
                        if(k==c1[0]&&b1[1]==c1[1])
                            te=k;
                    if(te==-1)
                        for(int k=1; k<9; ++k)
                            mapp[k][b1[1]]=1;
                    else if(te<b1[0])
                        for(int k=te+1; k<9; ++k)
                            mapp[k][b1[1]]=1;
                    else
                        for(int k=1; k<te; ++k)
                            mapp[k][b1[1]]=1;
                }
                if(!judge[3]) //白王没被吃掉的情况
                    for(int ti=-1; ti<2; ++ti)
                        for(int tj=-1; tj<2; ++tj)
                            mapp[c1[0]+ti][c1[1]+tj]=1;
                if(mapp[x][y]==0) //如果有一种情况没被吃掉就输出OTHER，结束
                {
                    cout<<"OTHER"<<endl;
                    return 0;
                }
            }
        }
    }
    cout<<"CHECKMATE"<<endl; //否则输出CHECKMATE，结束
    return 0;
}

```


---

## 作者：zsseg (赞：1)

### 题意：

给出两个白车和白王、黑王的位置，判断黑王是否会被吃掉。

我们使用红色代表白方能够控制的格子，显然，要满足黑王被吃掉，就要使它所在的格子和能走到的格子都被控制，如下图所示：
![1](https://cdn.luogu.com.cn/upload/image_hosting/cua62pzy.png)
所以，我们只需要判断黑王自己及其周围一圈的格子是否都被染成红色就可以了。

根据题目，我们可以看出，一个车能控制的范围就是它所在的行和列，**但是不包括本身所在的格子。** 如下图所示：
![2](https://cdn.luogu.com.cn/upload/image_hosting/7amesft5.png)

这样，我们就能写出车控制格子的代码：
```cpp
cin>>s;
for(int i=1;i<=8;i++){
	if(i==s[1]-'0')continue;//不包含自己
	mp[s[0]-'a'+1][i]++;
}
for(int i=1;i<=8;i++){
	if(i==s[0]-'a'+1)continue;//不包含自己
	mp[i][s[1]-'0']++;
}
```
接下来，我们来看国王，国王控制的是周围的 8 个格子，如下图所示：![3](https://cdn.luogu.com.cn/upload/image_hosting/9g6ab6ww.png)

这样，我们就能写出相应程序了。
```cpp
cin>>s;
int sx=s[0]-'a'+1,sy=s[1]-'0';
for(int i=1;i<=8;i++){
	if(sx+dx[i]<1||sx+dx[i]>8||sy+dy[i]<1||sy+dy[i]>8)continue;//考虑越界
	mp[sx+dx[i]][sy+dy[i]]++;
}
```
**但是，我们考虑下面的情况：**

![4](https://cdn.luogu.com.cn/upload/image_hosting/wgun552i.png)

如图所示，国王挡住了车的攻击使得车无法攻击到国王另一侧的格子，这时，我们考虑开一个数组记录车的坐标，我们把国王摆好后，看是否有车与国王同行/同列。如果有，那么另一侧的格子就不能被染色。（但是如果另一个车能攻击到，还是会被染色。）
```cpp

for(int j=1;j<=2;j++){
	if(roots[j][0]==sx){//行相同
		if(roots[j][1]>sy)for(int i=1;i<=sy-1;i++)mp[sx][i]--;//在左侧
		else for(int i=sy+1;i<=8;i++)mp[sx][i]--;//在右侧
	}
	if(roots[j][1]==sy){//列相同
		if(roots[j][0]>sx)for(int i=1;i<=sx-1;i++)mp[i][sy]--;//在上侧
		else for(int i=sx+1;i<=8;i++)mp[i][sy]--;//在下侧
	}
}
```
这样，将所有格子染完色以后，只要判断黑王的 9 个格子是否都被染色就可以了。

```cpp
cin>>s;
sx=s[0]-'a'+1,sy=s[1]-'0';
for(int i=0;i<=8;i++){
	if(sx+dx[i]<1||sx+dx[i]>8||sy+dy[i]<1||sy+dy[i]>8)continue;//越界
	if(!mp[sx+dx[i]][sy+dy[i]]){
		cout<<"OTHER";//如果有一个没被染色，那么就不会被吃
		return 0;
	}
}
cout<<"CHECKMATE";
```

### 完整代码：
```cpp
#include <bits/stdc++.h>
#define f(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int mp[9][9];
char s[2];
int dx[9]={0,0,0,1,-1,1,1,-1,-1};
int dy[9]={0,1,-1,0,0,1,-1,1,-1};
int roots[3][2];
int main(){
	f(i,1,2){//两个车
		cin>>s;
		roots[i][0]=s[0]-'a'+1;//坐标转换，下面同理
		roots[i][1]=s[1]-'0';
		f(i,1,8){//将这行染色
			if(i==s[1]-'0')continue;
			mp[s[0]-'a'+1][i]++;
		}
		f(i,1,8){//这列也染色
			if(i==s[0]-'a'+1)continue;
			mp[i][s[1]-'0']++;
		}
	}
	cin>>s;//处理白王
	int sx=s[0]-'a'+1,sy=s[1]-'0';
	f(i,1,8){
		if(sx+dx[i]<1||sx+dx[i]>8||sy+dy[i]<1||sy+dy[i]>8)continue;
		mp[sx+dx[i]][sy+dy[i]]++;
	}
	f(j,1,2){//检测是否挡住车
		if(roots[j][0]==sx){
			if(roots[j][1]>sy)f(i,1,sy-1)mp[sx][i]--;
			else f(i,sy+1,8)mp[sx][i]--;
		}
		if(roots[j][1]==sy){
			if(roots[j][0]>sx)f(i,1,sx-1)mp[i][sy]--;
			else f(i,sx+1,8)mp[i][sy]--;
		}
	}
	cin>>s;
	sx=s[0]-'a'+1,sy=s[1]-'0';
	f(i,0,8){//检测黑王周围格子
		if(sx+dx[i]<1||sx+dx[i]>8||sy+dy[i]<1||sy+dy[i]>8)continue;
		if(!mp[sx+dx[i]][sy+dy[i]]){
			cout<<"OTHER";//能走掉
			return 0;
		}
	}
	cout<<"CHECKMATE";
	return 0;
}

```
$$END$$

---

## 作者：Essinsop (赞：1)

对于初始的局面，黑王共有 9 种选择，除了 8 个方向，还有不动

在这五种移动选择中，若有一种白方不能杀死黑王，则输出 other

对于每一种情况，我们要判断王的位置以及车的位置：

1.该位置是否在白王移动范围内，即白王和黑王是相邻的

2.该位置是否在白车的移动范围内，**并且白车移动到该位置没有被棋子挡住**

如果这两个条件均为“否”，则该位置是可以的，因此得到如下代码：

```
#include <bits/stdc++.h>
using namespace std;
char a, b, c, d;
int x, y, xx, yy, ex, ey, sx, sy;
int fx[8][2] = {0, 1, 0, -1, 1, 0, -1, 0, -1, -1, -1, 1, 1, -1, 1, 1};
bool checkc(int cx, int cy, int px, int py) {
	if(cx == px) {//判断车移动到该位置是否有棋子挡住
		if(cy > py) {
			for(int i = cy - 1;i >= py;i --) {
				if((cx == x && i == cy) || (cx == xx && i == cy) || (cx == ex && i == ey)) {
					if(i != py) return false;
				}
			}
		}
		else {
			for(int i = cy + 1;i <= py;i ++) {
				if((cx == x && i == cy) || (cx == xx && i == cy) || (cx == ex && i == ey)) {
					if(i != py) return false;
				}
			}
		}
	}
	else {
		if(cx > px) {
			for(int i = cx - 1;i >= px;i --) {
				if((cy == y && i == x) || (cy == yy && i == xx) || (cy == ey && i == ex)) {
					if(i != px) return false;
				}
			}
		}
		else {
			for(int i = cx + 1;i <= px;i ++) {
				if((cy == y && i == x) || (cy == yy && i == xx) || (cy == ey && i == ex)) {
					if(i != px) return false;
				}
			}
		}
	}
	return true;
}
bool check(int p1, int p2) {
	if(p1 < 1 || p1 > 8 || p2 < 1 || p2 > 8) return false;
	if(p1 == x && p2 != y) {
		if(checkc(x, y, p1, p2)) return false;
	}
	if(p1 != x && p2 == y) {
		if(checkc(x, y, p1, p2)) return false;
	}
	if(p1 == xx && p2 != yy) {
		if(checkc(xx, yy, p1, p2)) return false;
	}
	if(p1 != xx && p2 == yy) {
		if(checkc(xx, yy, p1, p2)) return false;
	}
	if(p1 == ex + 1 && p2 == ey) return false;//判断白王是否可以移动到该位置
	if(p1 == ex - 1 && p2 == ey) return false;
	if(p1 == ex && p2 == ey + 1) return false;
	if(p1 == ex && p2 == ey - 1) return false;
	if(p1 == ex + 1 && p2 == ey + 1) return false;
	if(p1 == ex + 1 && p2 == ey - 1) return false;
	if(p1 == ex - 1 && p2 == ey + 1) return false;
	if(p1 == ex - 1 && p2 == ey - 1) return false;
	return true;
}
int main() {
	cin >> a >> y >> b >> yy >> c >> ey >> d >> sy;
	x = a - 'a' + 1;//把坐标换成数字表示
	xx = b - 'a' + 1;
	ex = c - 'a' + 1;
	sx = d - 'a' + 1;
	if(check(sx, sy)) {//判断黑王不动
		cout << "OTHER" << endl;
		return 0;
	}
	for(int i = 0;i <= 7;i++) {
		int cx = sx + fx[i][0];
		int cy = sy + fx[i][1];
		if(check(cx, cy)) {//判断8个方向
			cout << "OTHER" << endl;//只要有一种移动方案可行,输出other
			return 0;
		}
	}
	cout << "CHECKMATE" << endl;
	return 0;
}
```


---

## 作者：OIer_Hhy (赞：0)

这道题真的有点恶心，调了我 1 hr……

考虑将两个白车，一个白王能攻击到的位置做上标记。

然而……

白王有可能挡住车！

于是，记白王的坐标为 $(wkx,wky)$，若白车 $(wrx,wry)$ 和白王在同一行（$wkx=wrx$）而且白车在白王左边，白车的攻击范围就只能从第 $1$ 列到第 $wkx-1$ 列；若白车和白王在同一行且在白王右边，白车的攻击范围就只能从第 $wkx+1$ 列到第 $8$ 列。

若白车和白王在同一列且在白王上边，白车的攻击范围就只能从第 $1$ 行到第 $wky-1$ 行；若白车和白王在同一列且在白王上边，白车的攻击范围就只能从第 $wky+1$ 行到第 $8$ 行。

白王的攻击范围很简单，就是周围 $8$ 个地方和它本身。

枚举每一个黑王可以走的地方，如果都有标记，说明黑棋被绝杀了；如果有一个地方没标记，说明黑王还可以逃。

如果你这样写完后交上去，那就 WA 了！

黑王可能可以吃掉白子，脱离险境！

于是，我们再特判，如果黑王能吃掉白子，就输出 "OTHER"。

结果……你满怀希望地交上去，又是听取 WA 声一片！

如果黑王能吃掉白子，却又被另一个白子吃掉，还是绝杀！

于是，我们标记一个坐标上有多少个白子在守卫，若没有，自然可以逃；若仅有一个，且能吃掉，那也苟延残喘；否则黑王被绝杀。

代码如下：
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
#define endl '\n'
using namespace std;
inline void FIO(){
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
string a,b,c,d;
string board[10][10];
int cnt[10][10]; 
struct node{
	int x,y;
}wr1,wr2,wk,bk; // wr1,wr2 白车 wk 白王 bk 黑王
signed main(){
	FIO();
	cin>>a>>b>>c>>d;
	wr1.x=a[0]-96;
	wr1.y=a[1]-48;
	wr2.x=b[0]-96;
	wr2.y=b[1]-48;
	wk.x=c[0]-96;
	wk.y=c[1]-48;
	bk.x=d[0]-96;
	bk.y=d[1]-48;
	if(wr1.x==wk.x){
		for(int i=1;i<=8;i++) board[i][wr1.y]+='1';
		if(wr1.y<wk.y){
			for(int i=1;i<wk.y;i++) board[wr1.x][i]+='1';
		}else{
			for(int i=wk.y+1;i<=8;i++) board[wr1.x][i]+='1';
		}
	}else if(wr1.y==wk.y){
		for(int i=1;i<=8;i++) board[wr1.x][i]+='1';
		if(wr1.x<wk.x){
			for(int i=1;i<wk.x;i++) board[i][wr1.y]+='1';
		}else{
			for(int i=wk.x+1;i<=8;i++) board[i][wr1.y]+='1';
		}
	}else{
		for(int i=1;i<=8;i++) board[wr1.x][i]+='1',board[i][wr1.y]+='1';
	}
	
	
	if(wr2.x==wk.x){
		for(int i=1;i<=8;i++) board[i][wr2.y]+='2';
		if(wr2.y<wk.y){
			for(int i=1;i<wk.y;i++) board[wr2.x][i]+='2';
		}else{
			for(int i=wk.y+1;i<=8;i++) board[wr2.x][i]+='2';
		}
	}else if(wr2.y==wk.y){
		for(int i=1;i<=8;i++) board[wr2.x][i]='2';
		if(wr2.x<wk.x){
			for(int i=1;i<wk.x;i++) board[i][wr2.y]+='2';
		}else{
			for(int i=wk.x+1;i<=8;i++) board[i][wr2.y]+='2';
		}
	}else{
		for(int i=1;i<=8;i++) board[wr2.x][i]+='2',board[i][wr2.y]+='2';
	}
	
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			int ni=i+wk.x;
			int nj=j+wk.y;
			if(ni>0&&ni<=8&&nj>0&&nj<=8){
				board[ni][nj]+='K';
				cnt[ni][nj]++;
			}
		}
	}
//	for(int i=1;i<=8;i++){
//		for(int j=1;j<=8;j++) cout<<setw(5)<<board[i][j];
//		cout<<endl;
//	} 
	for(int i=1;i<=8;i++){
		for(int j=1;j<=8;j++){
			int pos2=board[i][j].find("2"),pos1=board[i][j].find("1"),posk=board[i][j].find("K");
			cnt[i][j]=(pos2!=-1)+(pos1!=-1)+(posk!=-1);
		}
	}
//	for(int i=1;i<=8;i++){
//		for(int j=1;j<=8;j++) cout<<setw(5)<<cnt[i][j];
//		cout<<endl;
//	}
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			int ni=i+bk.x;
			int nj=j+bk.y;
			if(ni>0&&ni<=8&&nj>0&&nj<=8){
				if(cnt[ni][nj]>1) continue;
//				cout<<ni<<' '<<nj<<' '<<wr2.x<<' '<<wr2.y<<endl;
				int pos2=board[ni][nj].find("2"),pos1=board[ni][nj].find("1"),posk=board[ni][nj].find("K");
				if(ni==wr1.x&&nj==wr1.y&&pos2==-1&&posk==-1){
					cout<<"OTHER";
					return 0;
				} 
				if(ni==wr2.x&&nj==wr2.y&&pos1==-1&&posk==-1){
					cout<<"OTHER";
					return 0;
				}
				if(ni==wk.x&&nj==wk.y&&pos2==-1&&pos1==-1){
					cout<<"OTHER";
					return 0;
				}
				if(!cnt[ni][nj]){
					cout<<"OTHER";
					return 0;
				}
			}
		}
	}
	cout<<"CHECKMATE\n";
	return 0;
}

```

---

## 作者：XL4453 (赞：0)

### 解题思路：

真的好题，刷新了我对于细节的认识。

思路其实很简单，就是将所有被控制的点染色，然后在黑王旁边找是否有没有被控制的点。

可惜想过这题没有这么简单。

---

我在这份代码中考虑的细节：

1. 当黑王珂以直接吃掉白王时就获胜了，属于其他情况。

2. 当白挡住车的时候被挡住的部分不能染色。

3. 黑王不可以离开棋盘，也就是判断边界。

4. 黑王可以选择不动。

5. （或许不算细节）王是八向移动。

---
总体还是比较简单。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int mp[15][15];
int car1[2],car2[2],baiking[2],heiking[2];
int dx[10]={0, 1, 1, 1, 0, 0,-1,-1,-1};
int dy[10]={0,-1, 1, 0, 1,-1, 1,-1, 0};
char a;
char get(){
	char c=getchar();
	while(c=='\n'||c==' '||c=='\r')c=getchar();
	return c;
}
int main(){
	a=get();car1[0]=a-'a'+1;
	scanf("%1d",&car1[1]);
	a=get();car2[0]=a-'a'+1;
	scanf("%1d",&car2[1]);
	a=get();baiking[0]=a-'a'+1;
	scanf("%1d",&baiking[1]);
	a=get();heiking[0]=a-'a'+1;
	scanf("%1d",&heiking[1]);
	
	for(int i=car1[1];i<=8;i++){
		mp[car1[0]][i]++;
		if(car1[0]==baiking[0]&&i==baiking[1])break;
	}
	for(int i=car1[1];i>=1;i--){
		mp[car1[0]][i]++;
		if(car1[0]==baiking[0]&&i==baiking[1])break;
	}
	
	for(int i=car1[0];i<=8;i++){
		mp[i][car1[1]]++;
		if(i==baiking[0]&&car1[1]==baiking[1])break;
	}
	for(int i=car1[0];i>=1;i--){
		mp[i][car1[1]]++;
		if(i==baiking[0]&&car1[1]==baiking[1])break;
	}
	mp[car1[0]][car1[1]]-=4;
	
	for(int i=car2[1];i<=8;i++){
		mp[car2[0]][i]++;
		if(car2[0]==baiking[0]&&i==baiking[1])break;
	}
	for(int i=car2[1];i>=1;i--){
		mp[car2[0]][i]++;
		if(car2[0]==baiking[0]&&i==baiking[1])break;
	}
	
	for(int i=car2[0];i<=8;i++){
		mp[i][car2[1]]++;
		if(i==baiking[0]&&car2[1]==baiking[1])break;
	}
	for(int i=car2[0];i>=1;i--){
		mp[i][car2[1]]++;
		if(i==baiking[0]&&car2[1]==baiking[1])break;
	}
	mp[car2[0]][car2[1]]-=4;
	
	for(int i=1;i<=8;i++)
	mp[baiking[0]+dx[i]][baiking[1]+dy[i]]++;
	mp[baiking[0]][baiking[1]]=0;
	
//	for(int i=1;i<9;i++){
//		for(int j=1;j<9;j++)
//		printf("%d",mp[i][j]);
//		printf("\n");
//	}
	
	for(int i=0;i<=8;i++)
	if(heiking[0]+dx[i]<=8&&heiking[0]+dx[i]>=1&&
	heiking[1]+dy[i]<=8&&heiking[1]+dy[i]>=1&&
	mp[heiking[0]+dx[i]][heiking[1]+dy[i]]<=0){
		printf("OTHER\n");
		return 0;
	}
	printf("CHECKMATE\n");
	return 0;
}
```


---

## 作者：liuli688 (赞：0)

其实这道题如果代码写好了还是很简单的。
### 思路：
如果白方能赢，则黑王此时所在和周围 $8$ 个方向均处在白子攻击范围内，则输出 `CHECKMATE`。

所以，只要模拟标出白车和白王的攻击范围即可。代码如下。
```cpp
#define STR string
#define BK break
#define CTN continue
#define FP(i,a,b) for(i = a;i < b;i++)
#define FM(i,a,b) for(i = a;i > b;i--)
#define FL(i,a,b) for(i = a;i <= b;i++)
#define FG(i,a,b) for(i = a;i >= b;i--)
STR r1,r2,wk,bk;
int xx,yy,i,j;

bool c[8][8],atk[8][8];//c 是标记是否有棋子，atk 是攻击范围
void markr(int x,int y)//标记车
{
	FG(i,x,0)
	{
		if(i == x)//注意棋子本身不在攻击范围内
			CTN;
		else
			atk[i][y] = true;
		if(c[i][y])//如果碰到棋子，跳出，赋值后判定保证棋子本身会被覆盖到
			BK; 
	}
	FP(i,x,8)
	{
		if(i == x)
			CTN;
		else
			atk[i][y] = true;
		if(c[i][y])
			BK;
	}
	FG(i,y,0)
	{
		if(i == y)
			CTN;
		else
			atk[x][i] = true;
		if(c[x][i])
			BK;
	}
	FP(i,y,8)
	{
		if(i == y)
			CTN;
		else
			atk[x][i] = true;
		if(c[x][i])
			BK;
	}
}
void markk(int x,int y)//标记白王
{
	FL(i,-1,1)
		FL(j,-1,1)
		{
			xx = x + i;
			yy = y + j;
			if(xx >= 0 && xx < 8 && yy >= 0 && yy < 8)//防止 RE
				atk[xx][yy] = true;
		}
	atk[x][y] = false;//棋子同样不在攻击范围内
}
```
但是，棋子的攻击范围可能会被其它棋子阻挡。上文的代码由于棋子本身不在攻击范围内，所以黑王可以通过吃掉白子来生存。由于碰到棋子后的跳出在赋值后，判定保证棋子本身会被覆盖到。所以棋子如果处在另一个棋子的攻击范围内黑王不能吃。

然后，就是开始的输入、标记和判定。
```cpp
void check(int x,int y)
{
	FL(i,-1,1)
		FL(j,-1,1)
		{
			xx = x + i;
			yy = y + j;
			if(xx >= 0 && xx < 8 && yy >= 0 && yy < 8)//注意此处 9 个格子均需判定
				if(!atk[xx][yy])
				{
					OUT("OTHER");
					return ;
				}
		}
	OUT("CHECKMATE");//如果全在攻击范围内，输出 CHECKMATE
} 
MAIN
{
	SPEEDUP;
	IN(r1 >> r2 >> wk >> bk);
	c[r1[0]-'a'][r1[1]-'1'] = true;//标记棋子
	c[r2[0]-'a'][r2[1]-'1'] = true;
	c[wk[0]-'a'][wk[1]-'1'] = true;
	c[bk[0]-'a'][bk[1]-'1'] = true;
	markr(r1[0]-'a',r1[1]-'1');//车
	markr(r2[0]-'a',r2[1]-'1');
	markk(wk[0]-'a',wk[1]-'1');//白王
	check(bk[0]-'a',bk[1]-'1');//判定
	END;
}
```
这段代码看起来很完美，于是提交。CF 上结果如下。
```cpp
7
Time: 0 ms, memory: 4 KB
Verdict: WRONG_ANSWER
Input
a1 a2 c4 c2
Participant's output
OTHER
Jury's answer
CHECKMATE
Checker comment
wrong answer 1st words differ - expected: 'CHECKMATE', found: 'OTHER'
```
WA 了。手动模拟一下攻击范围（`R` 表示车，`W` 表示白王，`B` 表示黑王，`x` 表示攻击范围）
```cpp
 12345678
aRR------
bxxxxx...
cxBxKx...
dx.xxx...
ex.......
fx.......
gx.......
hx.......
```
我们发现，d2 这个位置没有被覆盖，事实上王即使走到了 d2 也会暴露在 a2 的车下面。于是我们作如下改动：
```cpp
MAIN
{
	SPEEDUP;
	IN(r1 >> r2 >> wk >> bk);
	c[r1[0]-'a'][r1[1]-'1'] = true;//标记棋子
	c[r2[0]-'a'][r2[1]-'1'] = true;
	c[wk[0]-'a'][wk[1]-'1'] = true;
	//c[bk[0]-'a'][bk[1]-'1'] = true;注释掉，代表黑王即使移动也会暴露在攻击范围下
	markr(r1[0]-'a',r1[1]-'1');//车
	markr(r2[0]-'a',r2[1]-'1');
	markk(wk[0]-'a',wk[1]-'1');//白王
	check(bk[0]-'a',bk[1]-'1');//判定
	END;
}
```
于是就 AC 啦！
### 代码：
```cpp
#define MAIN signed main()
#define SPEEDUP ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define USING using namespace std
#define END return 0
#define LL long long
#define ULL unsigned long long
#define LD long double
#define STR string
#define EL '\n'
#define BK break
#define CTN continue
#define INF INT_MAX
#define UINF INT_MIN
#define IN(n) cin >> n
#define OUT(n) cout << n
#define OUTL(n) cout << n << EL
#define FP(i,a,b) for(i = a;i < b;i++)
#define FM(i,a,b) for(i = a;i > b;i--)
#define FL(i,a,b) for(i = a;i <= b;i++)
#define FG(i,a,b) for(i = a;i >= b;i--)

#include <bits/stdc++.h>
USING;
STR r1,r2,wk,bk;
int xx,yy,i,j;

bool c[8][8],atk[8][8];
void markr(int x,int y)
{
	FG(i,x,0)
	{
		if(i == x)
			CTN;
		else
			atk[i][y] = true;
		if(c[i][y])
			BK; 
	}
	FP(i,x,8)
	{
		if(i == x)
			CTN;
		else
			atk[i][y] = true;
		if(c[i][y])
			BK;
	}
	FG(i,y,0)
	{
		if(i == y)
			CTN;
		else
			atk[x][i] = true;
		if(c[x][i])
			BK;
	}
	FP(i,y,8)
	{
		if(i == y)
			CTN;
		else
			atk[x][i] = true;
		if(c[x][i])
			BK;
	}
}
void markk(int x,int y)
{
	FL(i,-1,1)
		FL(j,-1,1)
		{
			xx = x + i;
			yy = y + j;
			if(xx >= 0 && xx < 8 && yy >= 0 && yy < 8)
				atk[xx][yy] = true;
		}
	atk[x][y] = false;
}
void check(int x,int y)
{
	FL(i,-1,1)
		FL(j,-1,1)
		{
			xx = x + i;
			yy = y + j;
			if(xx >= 0 && xx < 8 && yy >= 0 && yy < 8)
				if(!atk[xx][yy])
				{
					OUT("OTHER");
					return ;
				}
		}
	OUT("CHECKMATE");
} 
MAIN
{
	SPEEDUP;
	IN(r1 >> r2 >> wk >> bk);
	c[r1[0]-'a'][r1[1]-'1'] = true;
	c[r2[0]-'a'][r2[1]-'1'] = true;
	c[wk[0]-'a'][wk[1]-'1'] = true;
	markr(r1[0]-'a',r1[1]-'1');
	markr(r2[0]-'a',r2[1]-'1');
	markk(wk[0]-'a',wk[1]-'1');
	check(bk[0]-'a',bk[1]-'1');
	END;
}
```

---

