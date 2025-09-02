# [NOIP 2011 提高组] Mayan 游戏

## 题目描述

Mayan puzzle 是最近流行起来的一个游戏。游戏界面是一个$7$ 行 $\times5$ 列的棋盘，上面堆放着一些方块，方块不能悬空堆放，即方块必须放在最下面一行，或者放在其他方块之上。游戏通关是指在规定的步数内消除所有的方块，消除方块的规则如下：

1. 每步移动可以且仅可以沿横向（即向左或向右）拖动某一方块一格：当拖动这一方块时，如果拖动后到达的位置（以下称目标位置）也有方块，那么这两个方块将交换位置（参见输入输出样例说明中的图 $6$ 到图 $7$）；如果目标位置上没有方块，那么被拖动的方块将从原来的竖列中抽出，并从目标位置上掉落（直到不悬空，参见下面图 $1$ 和图 $2$）；

![](https://cdn.luogu.com.cn/upload/image_hosting/gyse4ktp.png)

2. 任一时刻，如果在一横行或者竖列上有连续三个或者三个以上相同颜色的方块，则它们将立即被消除（参见图1 到图3）。

![](https://cdn.luogu.com.cn/upload/image_hosting/et7at5fd.png)

注意：

a) 如果同时有多组方块满足消除条件，几组方块会同时被消除（例如下面图 $4$，三个颜色为 $1$ 的方块和三个颜色为 $2$ 的方块会同时被消除，最后剩下一个颜色为 $2$ 的方块）。

b) 当出现行和列都满足消除条件且行列共享某个方块时，行和列上满足消除条件的所有方块会被同时消除（例如下面图5 所示的情形，$5$ 个方块会同时被消除）。

3. 方块消除之后，消除位置之上的方块将掉落，掉落后可能会引起新的方块消除。注意：掉落的过程中将不会有方块的消除。

上面图 $1$ 到图 $3$ 给出了在棋盘上移动一块方块之后棋盘的变化。棋盘的左下角方块的坐标为 $(0,0)$，将位于 $(3,3)$ 的方块向左移动之后，游戏界面从图 $1$ 变成图 $2$ 所示的状态，此时在一竖列上有连续三块颜色为 $4$ 的方块，满足消除条件，消除连续 $3$ 块颜色为 $4$ 的方块后，上方的颜色为 $3$ 的方块掉落，形成图 $3$ 所示的局面。


## 说明/提示

**【输入输出样例说明】**

按箭头方向的顺序分别为图 $6$ 到图 $11$

![](https://cdn.luogu.com.cn/upload/image_hosting/vmb8yy6n.png)

样例输入的游戏局面如上面第一个图片所示，依次移动的三步是：$(2,1)$ 处的方格向右移动，$(3,1)$ 处的方格向右移动，$(3,0)$ 处的方格向右移动，最后可以将棋盘上所有方块消除。

**【数据范围】**

对于 $30\%$ 的数据，初始棋盘上的方块都在棋盘的最下面一行；

对于 $100\%$ 的数据，$0<n \le 5$。

## 样例 #1

### 输入

```
3
1 0
2 1 0
2 3 4 0
3 1 0
2 4 3 4 0```

### 输出

```
2 1 1
3 1 1
3 0 1```

# 题解

## 作者：坏耶 (赞：21)

## 萌新~~年~~日常打卡
### 思路~~很简单~~，就模拟
##### ~~题目要你干什么那就干什么(废话)~~
###### 大部分的题解已经讲了怎么模拟了
###### 不过我还是我还是讲一遍吧
- 模拟思路   
- 枚举所有可能的移动，用搜索的方法即可，建议使用dfs   
- 重要的部分在时间优化上(虽然我不知道不优化能不能过)

关于剪枝   
首先搜索移动的时候，并不用全部往下搜，   
如果左边有块,不向左移动(这个各位大佬都讲了)   
因为左边的块会向右移动且字典序更小   
我想说的是，另一个剪枝!   
现在如果我说不可以剪交换相同各位可以理解吧   
但是交换相同颜色其实是可以优化的   
可以发现无论交换哪个地方的相同颜色结果相同   
所以只要保留字典序最小的交换相同颜色即可   
就是每层dfs搜到第一次相同的就允许,再搜到就剪掉   
这样既可以优化又不会被故意浪费步数的数据卡   
#### 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()//快速读入
{
    int sum=0,flag=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')ch=getchar();ch=getchar();}
    while(ch<='9'&&ch>='0'){sum=sum*10+ch-'0';ch=getchar();}
    return sum*flag;
}
struct node{int x,y,z;}c[7];//储存答案
int  n,a[7][9],    b[7][7][9];
//   读入数据   存放dfs前的备份数据
queue<node>q;
//消除块的队列(也可以用bool数组,但我觉得这样消除时快将近一半的时间)
void fz(int k)//从a备份内容到b
{
    for(int i=1;i<=5;i++)
    for(int j=1;j<=7;j++)
    b[k][i][j]=a[i][j];
}
void zf(int k)//从b还原内容到a
{
    for(int i=1;i<=5;i++)
    for(int j=1;j<=7;j++)
    a[i][j]=b[k][i][j];
}
bool jc()//检测是不是没有块了
{
    for(int i=1;i<=5;i++)//只要检测最下排即可
    if(a[i][1])return 0;
    return 1;
}
bool xc()//消除判定
{
    for(int i=1;i<=5;i++)for(int j=1;j<=7;j++)
    {//判定可消除,一定不要直接赋值0
        if(a[i][j]&&a[i-1][j]==a[i][j]&&a[i+1][j]==a[i][j])q.push({i,j,0});
        if(a[i][j]&&a[i][j-1]==a[i][j]&&a[i][j+1]==a[i][j])q.push({i,j,1});
    }
    if(q.empty())return 0;//没有动
    while(!q.empty())//处理删除的块
    {
        node k=q.front();q.pop();
        if(k.z)a[k.x][k.y]=a[k.x][k.y-1]=a[k.x][k.y+1]=0;
        else a[k.x][k.y]=a[k.x-1][k.y]=a[k.x+1][k.y]=0;
    }
    return 1;//动了
}
void dl()//掉落判定
{
    for(int i=1;i<=5;i++)
    for(int j=2;j<=7;j++)
    if(a[i][j]&&!a[i][j-1])//如果一个块踩空
    for(int k=j-1;k>=0;k--)//一直往下找到一个非空块
    if(a[i][k])//找到了
    {
        swap(a[i][j],a[i][k+1]);//交换
        break;
    }
}
void yd(int x,int y,int k)//移动函数
{
    swap(a[x][y],a[x+k][y]);
    if(!a[x][y])dl();//这个应该很好理解,只有和空气交换才会掉落
    while(xc())dl();//需要循环判定!!!
}
void dfs(int k)//搜索
{
    if(!k)//移动完检测
    {
        if(jc())//检测
        {//输出
            for(int i=n;i>0;i--)printf("%d %d %d\n",c[i].x-1,c[i].y-1,c[i].z);
            exit(0);//直接退出程序
        }
        return;//否则返回继续搜
    }
    fz(k);//先备份a
    bool flag=0;//标记,用来做相同色优化
    for(int i=1;i<=5;i++)
    for(int j=1;j<=7;j++)
    if(a[i][j])//枚举每个点,如果有色就继续
    {
        if(i>1&&!a[i-1][j])//如果不在最左边且左边是空的就左移
        {
            yd(i,j,-1);//移动
            c[k]={i,j,-1};//记录答案
            dfs(k-1);//继续搜
            zf(k);//恢复a
        }
        if(i<5)//如果不在最右边都右移
        {
            if(a[i][j]==a[i+1][j]&&flag)continue;//已经有一个了,其余剪掉
            if(a[i][j]==a[i+1][j])flag=1;//第一个放走,然后标记
            yd(i,j,1);//移动
            c[k]={i,j,1};//记录答案
            dfs(k-1);//继续搜
            zf(k);//恢复a
        }
    }
}
int main()//主函数
{
    n=read();//读n
    for(int i=1;i<=5;i++)a[i][0]=2147483647;//这个在掉落判定中有用(10以上的数都可以)
    for(int i=1;i<=5;i++)
    for(int j=1;j<=8;j++)
    {//读入
        a[i][j]=read();
        if(!a[i][j])break;
    }
    dfs(n);//搜索,n是层数(可能大部分人会写1)
    cout<<-1;//无解输出-1,因为如果有解在dfs里就退出了
    return 0;
}
```
### 欢迎 ~~挑刺与找茬~~ 指出错误

---

## 作者：lihongru (赞：8)

### 题目分析

本题没有什么特别的办法，只能尝试每一个步骤的走法。说到尝试，就一定是搜索了。不过本题的搜索比较复杂，夹杂了模拟。我认为本题难度主要在代码上。

为了方便，我们将本题的编号起点 $(0, 0)$ 调整为 $(1, 1)$，并在最后输出时 $-1$。

### 移动-move 函数

先不管如何搜索操作步骤。对于每一次移动块，先要交换块，然后进行删除，删除后出现新的空，需要进行下落，下落后又有新的块……由此，我们可以先来实现一个移动的函数。

```cpp
void move(int x, int y, int k){
	swap(mp[x][y], mp[x+k][y]); // 1交换
	down(); // 2下落
	while (remove()) down(); // 3判定并继续下落
}
```

其中 `remove` 表示消除（返回值为是否进行了至少一组的消除），`down` 表示下落。

### 下落-down 函数

接下来我们就可以开始完成这两个函数了。先来看 `down` 函数。

首先我们知道，下落**不会引起列交换**。所以我们对于 $5$ 列，分别处理。快速的办法就是新建一个数组，将所有不为 $0$ 的块拷贝进去（不留空白），再重新拷贝出来。例如一列 $0010230$，进入数组后 $1230000$，再回到这一列就变成了 $1230000$，比朴素向下找方便。

```cpp
void down(){
	for (int i = 1; i <= 5; i++){
		int b[10] = {}, cnt = 0; // 此处将b数组清0了
		for (int j = 1; j <= 7; j++){
			if (mp[i][j]) b[++cnt] = mp[i][j]; // 加入新数组
		}
		for (int j = 1; j <= 7; j++){
			mp[i][j] = b[j]; // 移回原数组，并覆盖多余部分
		}
	}
}
```

### 移除-remove 函数

接下来就是 `remove` 函数。这是比较复杂的一个函数。因为可能出现题目描述中“共享方块”的问题，我们不能直接修改原数组。这个时候我们就需要一个辅助数组了。

一旦找到某个块可以作为消除块的中间，标记到辅助数组。最终把辅助数组中的标记和原数组中的被标记位置一同清空，并检查是否消除了块。一定注意，**空白不能作为一个“空白块”的中间位置，遇到空白要跳过**，否则可能会出现死循环。


```cpp
bool remove(){
	for (int i = 1; i <= 5; i++){
		for (int j = 1; j <= 7; j++){
			if (!mp[i][j]) continue; // 空白块要跳过
			if (mp[i-1][j] == mp[i][j] && mp[i+1][j] == mp[i][j])
				v[i-1][j] = v[i][j] = v[i+1][j] = 1; // 标记横向块
			if (mp[i][j-1] == mp[i][j] && mp[i][j+1] == mp[i][j])
				v[i][j-1] = v[i][j] = v[i][j+1] = 1; // 标记纵向块
		}
	}
	bool ret = false; // 寻找是否消除
	for (int i = 1; i <= 5; i++){
		for (int j = 1; j <= 7; j++){
			if (v[i][j]) {
				mp[i][j] = v[i][j] = 0;
				ret = true;
			}
		}
	}
	return ret;
}
```

三个函数都完成了，接下来就可以进入重点的搜索部分了。

### 搜索-dfs 函数

要说搜索，我们可以枚举 $5 \times 7$ 个块判断消除，这是完全没有问题的。最坑的地方就是回溯，因为**无法还原出原状态**。

当然，解决办法也很简单——再加辅助数组。在找之前，先把原数据复制过来，每次回溯再复制回去。

另外，除了剪枝，我们还得使用数组记录答案，最终还需要一个判断是否完成的函数 `check`，具体怎么写见下一部分。

```cpp
void dfs(int x){
	if (flag) return ;
	if (check()){
		for (int i = 1; i <= n; i++){
			cout << ans[i][1] << " " << ans[i][2] << " " << ans[i][3] << endl;
		}
		flag = true;
		return ;
	}
	if (x > n) return ;
	int tmp[10][10];
	memcpy(tmp, mp, sizeof tmp);
	for (int i = 1; i <= 5; i++){
		for (int j = 1; j <= 7; j++){
			if (!mp[i][j]) break;
			if (i < 5){
				ans[x][1] = i - 1;
				ans[x][2] = j - 1;
				ans[x][3] = 1;
				move(i, j, 1); dfs(x+1);
				memcpy(mp, tmp, sizeof mp);
			}
			if (i > 1 && !mp[i-1][j]){
				ans[x][1] = i - 1;
				ans[x][2] = j - 1;
				ans[x][3] = -1;
				move(i, j, -1); dfs(x+1);
				memcpy(mp, tmp, sizeof mp);
			}
		}
	}
}
```

注意：$1$ 优先于 $-1$，**一定要先搜索向右移动**。向右移动，右边只要不为空，即可移动。向左移动需要注意不能移到空白处。

### 检查-check 函数

非常简单，由于我们可以保证在执行 `check` 函数时，数组状态完全合法，所以只找第一横行是否有块即可。

```cpp
bool check(){
	for (int i = 1; i <= 5; i++){
		if (mp[i][1]) return false;
	}
	return true;
}
```

### 关于 Hack 数据

Hack 数据仅需 $1$ 步即可完成，但它的输入 $n$ 大于 $1$。我的代码最开始被 Hack 了，是因为判断向右的时候多加了不相同才换的条件。对于这种情况，需要通过“无效交换”“拖延”步数，所以不能加“不相同才换”的条件。

### 题目总结与参考代码

本题主要难度是如何进行搜索，以及搜索过程中的模拟。调代码的难度也是比较大的，可以通过加辅助输出或者 `return` 来调错。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, mp[10][10], v[10][10], ans[10][5];
bool flag;

void down(){
	for (int i = 1; i <= 5; i++){
		int b[10] = {}, cnt = 0;
		for (int j = 1; j <= 7; j++){
			if (mp[i][j]) b[++cnt] = mp[i][j];
		}
		for (int j = 1; j <= 7; j++){
			mp[i][j] = b[j];
		}
	}
}

bool remove(){
	for (int i = 1; i <= 5; i++){
		for (int j = 1; j <= 7; j++){
			if (!mp[i][j]) continue;
			if (mp[i-1][j] == mp[i][j] && mp[i+1][j] == mp[i][j])
				v[i-1][j] = v[i][j] = v[i+1][j] = 1;
			if (mp[i][j-1] == mp[i][j] && mp[i][j+1] == mp[i][j])
				v[i][j-1] = v[i][j] = v[i][j+1] = 1;
		}
	}
	bool ret = false;
	for (int i = 1; i <= 5; i++){
		for (int j = 1; j <= 7; j++){
			if (v[i][j]) {
				mp[i][j] = v[i][j] = 0;
				ret = true;
			}
		}
	}
	return ret;
}

bool check(){
	for (int i = 1; i <= 5; i++){
		if (mp[i][1]) return false;
	}
	return true;
}

void move(int x, int y, int k){
	swap(mp[x][y], mp[x+k][y]);
	down();
	while (remove()) down();
}

void dfs(int x){
	if (flag) return ;
	if (check()){
		for (int i = 1; i <= n; i++){
			cout << ans[i][1] << " " << ans[i][2] << " " << ans[i][3] << endl;
		}
		flag = true;
		return ;
	}
	if (x > n) return ;
	int tmp[10][10];
	memcpy(tmp, mp, sizeof tmp);
	for (int i = 1; i <= 5; i++){
		for (int j = 1; j <= 7; j++){
			if (!mp[i][j]) break;
			if (i < 5){
				ans[x][1] = i - 1;
				ans[x][2] = j - 1;
				ans[x][3] = 1;
				move(i, j, 1); dfs(x+1);
				memcpy(mp, tmp, sizeof mp);
			}
			if (i > 1 && !mp[i-1][j]){
				ans[x][1] = i - 1;
				ans[x][2] = j - 1;
				ans[x][3] = -1;
				move(i, j, -1); dfs(x+1);
				memcpy(mp, tmp, sizeof mp);
			}
		}
	}
}

int main(){
	cin >> n;
	for (int i = 1; i <= 5; i++){
		int p = 0, x; cin >> x;
		while (x) {
			mp[i][++p] = x;
			cin >> x;
		}
	}
	dfs(1);
	if (!flag) 
		cout << -1 << endl;
	return 0;
}
```

---

## 作者：hexuchen (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P1312)

[更好的阅读体验？](https://www.luogu.com.cn/article/vgn3ocap)

## 题目大意

一款消消乐游戏，有 $7 \times 5$ 的棋盘。每次可以横向挪动一个方块，相同颜色的 $3$ 个方块可以消除。求消除所有方块的最小次数。

## 思路分析

一道毒瘤的模拟、深搜题。

此题思路不难。枚举每一个方块所有可能的移动，用 dfs 搜索即可。回溯有些麻烦，要先用一个辅助数组存下原数组，回溯时将原数组的值替换成辅助数组的值。

注意直接搜索会 TLE，所以要加剪枝。在向左移动方块时要判断左边是否为空。如果为空，则没有移动的必要，直接退出。

[坑点见此贴](https://www.luogu.com.cn/discuss/1055695)

## 代码分解

这题难难在代码上。为了方便，本题解采用数组的顺序存储棋盘，即左上角的坐标是 $(1,1)$。

注：只展示重要的函数，零散小函数不展示

### down 函数

该函数用于实现将某一个方块落下。

```cpp
void down(int x,int y){
	if(s[x][y]==0){ //格子为空则没必要下落
		return ;
	}
	for(int i=x;i<7;i++){ //遍历到底部
		if(s[i+1][y]==0){ //下面为空
			swap(s[i+1][y],s[i][y]);
		}
		else{ //落到方块上了
			break;
		}
	}
}
```

### move 函数

该函数用于移动方块。

```cpp
void move(int x,int y,int r,int c){
	swap(s[x][y],s[r][c]); //交换方块位置
	down(r,c);
	for(int i=x-1;i>=1;i--){ //方块下落
		down(i,y);
	}
}
```

### proccess 函数

该函数用于消除 $3$ 个连着的方块并下落。但是题目有一个坑：

![](https://cdn.luogu.com.cn/upload/image_hosting/et7at5fd.png)

> （如图 5）当出现行和列都满足消除条件且行列共享某个方块时，行和列上满足消除条件的所有方块会被同时消除

所以判断不能直接在原数组上判断，要用辅助数组进行判断，原数组进行消除。

```cpp
void proccess(){
	a_to_b(s,s2); //这是自己定义的一个简单函数，负责将原数组 s 的值复制给辅助数组 s2
	for(int i=1;i<=7;i++){ //横向的三个
		for(int j=1;j<=3;j++){
			if(s2[i][j]==s2[i][j+1] && s2[i][j+1]==s2[i][j+2]){ //有三个连在一起的，注意用辅助数组判断
				s[i][j]=s[i][j+1]=s[i][j+2]=0; //用原数组消除
			}
		}
	}
	for(int i=1;i<=5;i++){ //纵向的三个
		for(int j=1;j<=5;j++){
			if(s2[j+1][i]==s2[j+2][i] && s2[j+2][i]==s2[j+3][i]){
				s[j+1][i]=s[j+2][i]=s[j+3][i]=0;
			}
		}
	}
	for(int i=7;i>=1;i--){ //记得下落
		for(int j=1;j<=5;j++){
			down(i,j);
		}
	}
}
```

#### dfs 函数

```cpp
void dfs(int step){
	if(check()){ //check 负责判断棋盘是否全空
		print(); //print 负责输出
		return ;
	}
	if(step>n){ //步数超了
		return ;
	}
	int s3[8][6]; //辅助数组，负责回溯
	for(int j=1;j<=5;j++){ //先列再行
		for(int i=7;i>=1;i--){ //从大到小（因为代码是倒着存的，这样可以使字典序最小）
			if(s[i][j]==0){
				continue;
			}
			if(j<=4){ //可以右移
				a_to_b(s,s3); //辅助数组更新
				ans1[step]=j-1;
				ans2[step]=7-i;
				ans3[step]=1;
				move(i,j,i,j+1); //移方块
				for(int k=1;k<=(num/3+1);k++){ //注意可能会存在连续消除的情况，num 为方块个数
					proccess();
				}
				dfs(step+1);
				a_to_b(s3,s); //回溯
			}
			if(j>=2 && s[i][j-1]==0){ //左移，剪枝
				a_to_b(s,s3);
				ans1[step]=j-1;
				ans2[step]=7-i;
				ans3[step]=-1;
				move(i,j,i,j-1);
				for(int k=1;k<=(num/3+1);k++){
					proccess();
				}
				dfs(step+1);
				a_to_b(s3,s);
			}
		}
	}
}
```

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,s[8][6],s2[8][6],ans1[6],ans2[6],ans3[6],num=0;
void a_to_b(int (&a)[8][6],int (&b)[8][6]){
	for(int i=1;i<=7;i++){
		for(int j=1;j<=5;j++){
			b[i][j]=a[i][j];
		}
	}
}
void down(int x,int y){
	if(s[x][y]==0){
		return ;
	}
	for(int i=x;i<7;i++){
		if(s[i+1][y]==0){
			swap(s[i+1][y],s[i][y]);
		}
		else{
			break;
		}
	}
}
void move(int x,int y,int r,int c){
	swap(s[x][y],s[r][c]);
	down(r,c);
	for(int i=x-1;i>=1;i--){
		down(i,y);
	}
}
void proccess(){
	a_to_b(s,s2);
	for(int i=1;i<=7;i++){
		for(int j=1;j<=3;j++){
			if(s2[i][j]==s2[i][j+1] && s2[i][j+1]==s2[i][j+2]){
				s[i][j]=s[i][j+1]=s[i][j+2]=0;
			}
		}
	}
	for(int i=1;i<=5;i++){
		for(int j=1;j<=5;j++){
			if(s2[j+1][i]==s2[j+2][i] && s2[j+2][i]==s2[j+3][i]){
				s[j+1][i]=s[j+2][i]=s[j+3][i]=0;
			}
		}
	}
	for(int i=7;i>=1;i--){
		for(int j=1;j<=5;j++){
			down(i,j);
		}
	}
}
bool check(){
	for(int i=1;i<=7;i++){
		for(int j=1;j<=5;j++){
			if(s[i][j]!=0){
				return false;
			}
		}
	}
	return true;
}
void print(){
	for(int i=1;i<=n;i++){
		cout<<ans1[i]<<' '<<ans2[i]<<' '<<ans3[i]<<'\n';
	}
	exit(0);
}
void dfs(int step){
	if(check()){
		print();
		return ;
	}
	if(step>n){
		return ;
	}
	int s3[8][6];
	for(int j=1;j<=5;j++){
		for(int i=7;i>=1;i--){
			if(s[i][j]==0){
				continue;
			}
			if(j<=4){
				a_to_b(s,s3);
				ans1[step]=j-1;
				ans2[step]=7-i;
				ans3[step]=1;
				move(i,j,i,j+1);
				for(int k=1;k<=(num/3+1);k++){
					proccess();
				}
				dfs(step+1);
				a_to_b(s3,s);
			}
			if(j>=2 && s[i][j-1]==0){
				a_to_b(s,s3);
				ans1[step]=j-1;
				ans2[step]=7-i;
				ans3[step]=-1;
				move(i,j,i,j-1);
				for(int k=1;k<=(num/3+1);k++){
					proccess();
				}
				dfs(step+1);
				a_to_b(s3,s);
			}
		}
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=5;i++){
		int a;
		for(int j=7;j>=0;j--){
			cin>>a;
			if(a==0){
				break;
			}
			s[j][i]=a;
			num++;
		}
	}
	dfs(1);
    cout<<-1;
	return 0;
}
```

---

## 作者：furina_yyds (赞：3)

## 思路

本题为 DFS。

创建三个函数，实现三个模块。

- `down`： 实现方块的下落。
- `del`： 实现方块的消除。
- `dfs`： 实现主要生成函数。

对于左移部分，如果左边为空才需要左移，否则，这个方块会被其他方块右移得到相同的效果。

## 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
struct Node{
	int x, y, op;
};
Node b[10]; 
int a[10][10];
int n;
inline void down(){
	for (int i = 1; i <= 5; i++){
		int sz = 0;
		for (int j = 1; j <= 7; j++)
			if (a[i][j]) a[i][++sz] = a[i][j];
		for (int j = sz + 1; j <= 7; j++) a[i][j] = 0;
	}
}
inline bool del(){
	int t[10][10];
	memcpy(t, a, sizeof(a));
	bool flag = false;
	for (int i = 1; i <= 5; i++){
		for (int j = 1; j <= 7; j++){
			if (!a[i][j]) continue;
			if (a[i][j] == a[i - 1][j] && a[i][j] == a[i + 1][j]){
				t[i][j] = t[i - 1][j] = t[i + 1][j] = 0;
				flag = true;
			}
			if (a[i][j] == a[i][j - 1] && a[i][j] == a[i][j + 1]){
				t[i][j] = t[i][j - 1] = t[i][j + 1] = 0;
				flag = true;
			}
		}
	}
	memcpy(a, t, sizeof(t));
	return flag;
}
inline void dfs(int step){
	down();
	while (del()) down();
	if (step > n){
		for (int i = 1; i <= 5; i++)
			if (a[i][1]) return;
		for (int i = 1; i <= n; i++)
			cout << b[i].x - 1 << " " << b[i].y - 1 << " " << b[i].op << endl;
		exit(0);
	}
	int t[10][10];
	memcpy(t, a, sizeof(a));
	for (int i = 1; i <= 5; i++){
		for (int j = 1; j <= 7; j++){
			if (a[i][j] == 0) break;
			if (i < 5){
				swap(a[i][j], a[i + 1][j]);
				b[step] = {i, j, 1};
				dfs(step + 1);
				memcpy(a, t, sizeof(t));
			}
			if (i > 1 && a[i - 1][j] == 0){
				swap(a[i][j], a[i - 1][j]);
				b[step] = {i, j, -1};
				dfs(step + 1);
				memcpy(a, t, sizeof(t));
			}
		}
	}
}
int main(){
	cin >> n;
	for (int i = 1; i <= 5; i++){
		for (int j = 1; j <= 8; j++){
			int x;
			cin >> x;
			if (x == 0) break;
			a[i][j] = x;
		}
	}	
	dfs(1);
	cout << -1 << endl;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/198613738)

---

## 作者：KukCair (赞：1)

### 基本思路

首先观察数据范围，$n$ 顶顶到 $5$，整个棋盘也最多有 $35$ 个块，这你不搜？？？

直接搜每一次动哪个块，下落和消除直接模拟。

### 代码

（我这里把棋盘倒过来了，第一行是底部，行列从 $(1,1)$ 开始，横纵坐标也是反的。）

- 下落

判断每个块上方是否为空，空就往上找，不然让其挪到当前块。

```cpp
void fall(){
	for(int i = 1; i <= 7; i++){
		for(int j = 1; j <= 5; j++){
			for(int k = 1; k <= 7 - i && !p[i][j]; k++){
                /* 其实这个 for 等价于
                while(!p[i][j]) k++, p[i][j] = p[i + k][j], p[i + k][j] = 0; */
				p[i][j] = p[i + k][j];
				p[i + k][j] = 0;
			}
		}
	}
}
```

- 消除

每当遇到符合要求的都标记一遍，切不可直接删（如图 $5$）。

以及删除时会带来连锁反应，用的时候得判断是否删完了，弄个 while 就完了。

```cpp
bool del(){
	int fl = 0;
	memset(f, 0, sizeof f);
    /*行*/
	for(int i = 1; i <= 7; i++){
		for(int j = 1; j <= 3; j++){
			if(!p[i][j]) continue;
			if(p[i][j] == p[i][j + 1] && p[i][j] == p[i][j + 2])
				f[i][j] = f[i][j + 1] = f[i][j + 2] = fl = 1;
		}
	}
    /*列*/
	for(int i = 1; i <= 5; i++){
		for(int j = 1; j <= 5; j++){
			if(!p[i][j]) continue;
			if(p[i][j] == p[i + 1][j] && p[i][j] == p[i + 2][j])
				f[i][j] = f[i + 1][j] = f[i + 2][j] = fl = 1;
		}
	}
	for(int i = 1; i <= 7; i++){
		for(int j = 1; j <= 5; j++){
			if(f[i][j]) p[i][j] = 0;
		}
	}
	fall(); // 删完了一定要落下，不能留空
	return fl;
}
```

- dfs

虽然看起来很长，但其实就是直接搜。

```cpp
void dfs(int step){
	if(step > n){
		for(int i = 1; i <= 7; i++)
			for(int j = 1; j <= 5; j++)
				if(p[i][j]) return; // 有没有消除的就不成立
		for(int i = 1; i <= n; i++)
			cout << path[i].y - 1 << ' ' << path[i].x - 1 << ' ' << path[i].g << '\n'; // -1 是因为我行列是从(1,1) 开始的，先y后x是因为我一开始就反了（懒得改）
		exit(0);
	}
	int a[8][8];
	for(int i = 1; i <= 7; i++)
		for(int j = 1; j <= 5; j++)
			a[i][j] = p[i][j]; // 保存当前这步的棋盘状态，要回溯
		for(int j = 1; j <= 5; j++){
	for(int i = 1; i <= 7; i++){
			if(!p[i][j]) continue; // ！！！空的不能操作！！！重点！！！
			if(j != 5){ // →
				path[step] = {i, j, 1};
				swap(p[i][j + 1], p[i][j]);
				fall();
				while(del());
				dfs(step + 1);
				for(int i = 1; i <= 7; i++)
					for(int j = 1; j <= 5; j++)
						p[i][j] = a[i][j];
			}
			if(j != 1 && !p[i][j - 1]){ // ←
                /*!p[i][j - 1]：这是一个小剪枝，若左边有块的话，让左边的块往右移字典序会更优*/
				path[step] = {i, j, -1};
				swap(p[i][j - 1], p[i][j]);
				fall();
				while(del());
				dfs(step + 1);
				for(int i = 1; i <= 7; i++)
					for(int j = 1; j <= 5; j++)
						p[i][j] = a[i][j];
			}
		}
	}
}
```

- 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int x, y, g;
} path[6];
int n, p[8][8];
bool f[8][8];
void fall(){
	for(int i = 1; i <= 7; i++){
		for(int j = 1; j <= 5; j++){
			for(int k = 1; k <= 7 - i && !p[i][j]; k++){
				p[i][j] = p[i + k][j];
				p[i + k][j] = 0;
			}
		}
	}
}
bool del(){
	int fl = 0;
	memset(f, 0, sizeof f);
	for(int i = 1; i <= 7; i++){
		for(int j = 1; j <= 3; j++){
			if(!p[i][j]) continue;
			if(p[i][j] == p[i][j + 1] && p[i][j] == p[i][j + 2])
				f[i][j] = f[i][j + 1] = f[i][j + 2] = fl = 1;
		}
	}
	for(int i = 1; i <= 5; i++){
		for(int j = 1; j <= 5; j++){
			if(!p[i][j]) continue;
			if(p[i][j] == p[i + 1][j] && p[i][j] == p[i + 2][j])
				f[i][j] = f[i + 1][j] = f[i + 2][j] = fl = 1;
		}
	}
	for(int i = 1; i <= 7; i++){
		for(int j = 1; j <= 5; j++){
			if(f[i][j]) p[i][j] = 0;
		}
	}
	fall();
	return fl;
}
void dfs(int step){
	if(step > n){
		for(int i = 1; i <= 7; i++)
			for(int j = 1; j <= 5; j++)
				if(p[i][j]) return;
		for(int i = 1; i <= n; i++)
			cout << path[i].y - 1 << ' ' << path[i].x - 1 << ' ' << path[i].g << '\n';
		exit(0);
	}
	int a[8][8];
	for(int i = 1; i <= 7; i++)
		for(int j = 1; j <= 5; j++)
			a[i][j] = p[i][j];
		for(int j = 1; j <= 5; j++){
	for(int i = 1; i <= 7; i++){
			if(!p[i][j]) continue;
			if(j != 5){
				path[step] = {i, j, 1};
				swap(p[i][j + 1], p[i][j]);
				fall();
				while(del());
				dfs(step + 1);
				for(int i = 1; i <= 7; i++)
					for(int j = 1; j <= 5; j++)
						p[i][j] = a[i][j];
			}
			if(j != 1 && !p[i][j - 1]){
				path[step] = {i, j, -1};
				swap(p[i][j - 1], p[i][j]);
				fall();
				while(del());
				dfs(step + 1);
				for(int i = 1; i <= 7; i++)
					for(int j = 1; j <= 5; j++)
						p[i][j] = a[i][j];
			}
		}
	}
}
int main(){
	cin >> n;
	for(int i = 1; i <= 5; i++){
		int x, k = 0;
		while(cin >> x){
			if(!x) break;
			k++;
			p[k][i] = x;
		}
	}
	dfs(1);
	cout << -1;
	return 0;
}
```

### 尾附

![](https://img.3dmgame.com/uploads/images/thumbkwdfirst/20180619/1529389957_913902.jpg)

---

## 作者：LionBlaze (赞：1)

首先一看，这题显然是搜索题。

为什么呢？首先进行分析。容易注意到通常情况下向右移动永远可以和向左移动替换，而字典序显然更小，于是可以只枚举向右移动。但是有特例就是左边没有元素，此时只能左移。

设 $r$ 为行数（在本题 $=7$），$c$ 为列数（在本题 $=5$）。直接爆搜时间复杂度是 $\mathcal O((rc)^n \times krc) = \mathcal O(k(rc)^{n+1})$，其中 $k$ 是平均情况下一次消除所需要的消除轮数，应当接近于 $1$。取 $k=1$，则时间复杂度计算结果在本题低达 $1,838,265,625$，而爆搜实际上应当跑不满，所以应当能过。

代码：

```cpp
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int a[10][10][10];

constexpr int r = 7, c = 5; // 使用 constexpr 声明编译期常量。通常情况下不劣于 const，但是功能相似。

// 下落
// 保证严格 O(rc)
// 唉唉唉 cache 不太友好
void qwqdown(int id)
{
	// 枚举每一列，在单独的列上下落
	for (int i = 1; i <= c; i++)
	{
		int cur = r;
		for (int j = r; j >= 1; j--)
		{
			if (a[id][j][i]) swap(a[id][j][i], a[id][cur][i]);
			if (a[id][cur][i]) cur--;
		}
	}
}

// 消除
// 大概 O(krc)
void tmp(int id)
{
	auto a = ::a[id];
	int cnt = 0;
	do
	{
		cnt = 0;
		bool** t = new bool*[r + 5];
		for (int i = 1; i <= r; i++)
		{
			t[i] = new bool[c + 5];
			for (int j = 1; j <= c; j++)
			{
				if (!a[i][j])
				{
					t[i][j] = false;
					continue;
				}
				if (i >= 3 && a[i][j] == a[i - 1][j] && a[i][j] == a[i - 2][j] ||
					i >= 2 && i <= r - 1 && a[i][j] == a[i - 1][j] && a[i][j] == a[i + 1][j] ||
					i <= r - 2 && a[i][j] == a[i + 1][j] && a[i][j] == a[i + 2][j] ||
					j >= 3 && a[i][j] == a[i][j - 1] && a[i][j] == a[i][j - 2] ||
					j >= 2 && j <= c - 1 && a[i][j] == a[i][j - 1] && a[i][j] == a[i][j + 1] ||
					j <= c - 2 && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j + 2]
					) t[i][j] = true;
				else t[i][j] = false;
			}
		}
		for (int i = 1; i <= r; i++)
		{
			for (int j = 1; j <= c; j++)
			{
				if ((cnt += t[i][j]) * t[i][j]) a[i][j] = 0;
			}
			delete[] t[i];
		}
		delete[] t;
		qwqdown(id);
	} while (cnt);
}

class step
{
public:
	int x, y, f;
	step() {}
	step(int x, int y, int f) { this->x = x; this->y = y; this->f = f; }
	friend bool operator==(const step& x, const step& y) { return x.x == y.x && x.y == y.y && x.f == y.f; }
} steps[10];

void dfs(int n, int id)
{
	auto a = ::a[id];
	if (id > n)
	{
		// a = ::a[n];
		for (int i = 1; i <= c; i++)
		{
			if (a[r][i]) return;
		}
		for (int i = 1; i <= n; i++)
		{
			printf("%d %d %d\n", steps[i].x, steps[i].y, steps[i].f);
		}
		exit(0);
	}
	for (int j = 1; j <= c; j++)
	{
		for (int i = r; i >= 1; i--)
		{
			if (a[i][j] == 0) continue;
			auto b = ::a[id + 1];
			if (j != c)
			{
				copy(a[0], a[9] + 10, b[0]);
				swap(b[i][j], b[i][j + 1]);
				steps[id] = { j-1, r - i, 1 };
				if (b[i][j] == 0) qwqdown(id + 1);
				tmp(id + 1);
				dfs(n, id + 1);
			}

			if (j != 1)
			{
				if (a[i][j - 1]) continue;
				copy(a[0], a[9] + 10, b[0]);
				swap(b[i][j], b[i][j - 1]);
				steps[id] = { j-1, r - i, -1 };
				if (b[i][j] == 0) qwqdown(id + 1);
				tmp(id + 1);
				dfs(n, id + 1);
			}
		}
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= c; i++)
	{
		for (int j = 1;; j++)
		{
			scanf("%d", a[1][r - j + 1] + i);
			if (a[1][r - j + 1][i] == 0) break;
		}
	}
	dfs(n, 1);
	printf("-1\n");
	return 0;
}
// manim puzzle（幻视）
// 3B1B：我做的 python lib 不是用来玩的啊……等等……damn
```

---

## 作者：tc291311 (赞：1)

# [NOIP 2011] Mayan 游戏

**~~这题其实挺简单的吧……。~~**

其实比想象中的好写很多，就是烦，有很多的优化。

## 思路

这题的话我们可以编写很多的函数来模拟这个过程，例如**下落，清理，判空**等等，最后呢再利用深搜遍历左移和右移，注意两个方向的优先，一定要小心变量名不要写错，别问为什么，~~调了一个下午没调出来~~。

## 函数内容
### empty 函数

函数功能：判断区域内是否已经被清空。
```cpp
bool empty()//判断是否已经清空
{
    for(int i=0;i<5;i++)
        for(int j=0;j<7;j++)
            if(a[i][j])return false;
    return true;
}
```

### copy 函数
函数功能：将数组 $x$ 中的内容赋值到数组 $y$ 上面，一会有用处。
```cpp
void copy(int x[10][10],int y[10][10])
{
    for(int i=0;i<5;i++)
        for(int j=0;j<7;j++)
            y[i][j]=x[i][j];
}
```

### drop 函数
函数功能：判断区块是否掉落。

```cpp
void drop()//判断掉落
{
    memset(c,0,sizeof(c));
    for(int i=0;i<5;i++)
        for(int j=0,k=0;j<7;j++)
            if(a[i][j])c[i][k++]=a[i][j];
    copy(c,a);
}
```
### clear 函数
函数功能：按照横向和纵向判断区块数量，可以理解成枚举。

```cpp
bool clear()
{
    bool flag=false;
    int xx,yy,up,dn;
    for(int i=0;i<3;i++)//横向判断块数不小于 3
        for(int j=0;j<7;j++)
        if(a[i][j])
        {
            for(xx=i;xx<5&&a[xx+1][j]==a[i][j];xx++);//横向
            if(xx-i+1>=3)
            {
                for(int k=i;k<=xx;k++)
                {
                    up=j;dn=j;
                    while(up+1<7&&a[k][up+1]==a[k][j])up++;
                    while(dn-1>=0&&a[k][dn-1]==a[k][j])dn--;
                    if(up-dn+1>=3)
                        for(int l=dn;l<=up;l++)
                            a[k][l]=0;
                    else a[k][j]=0;
                }
                flag=true;
            }
        }
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)//纵向判断块数不小于 3
        if(a[i][j])
        {
            for(yy=j;yy+1<7&&a[i][yy+1]==a[i][j];yy++);//纵向
            if(yy-j+1>=3)
            {
                for(int k=j;k<=yy;k++)
                {
                    up=i;dn=i;
                    while(up+1<7&&a[up+1][k]==a[i][k])up++;
                    while(dn-1>=0&&a[dn-1][k]==a[i][k])dn--;
                    if(up-dn+1>=3)
                        for(int l=dn;l<=up;l++)
                            a[l][k]=0;
                    else a[i][k]=0;
                }
                flag=true;
            }
        }
    return flag;
}
```
深搜就不用说啦，~~应该有基础的人都知道吧~~，但是唯一的难点就是**回溯**，我们需要用几个辅助的容器，把数据复制，这就是前面 copy 函数的作用了。

主函数就更不用说了吧，直接输入然后调用函数就好了。

放一下完整的代码，调了好久啊啊啊啊啊啊啊
## 代码


```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[10][10],c[10][10],sum[20];
struct node{int x,y,dir;}ans[10];
bool empty()//判断是否已经清空
{
    for(int i=0;i<5;i++)
        for(int j=0;j<7;j++)
            if(a[i][j])return false;
    return true;
}
void copy(int x[10][10],int y[10][10])
{
    for(int i=0;i<5;i++)
        for(int j=0;j<7;j++)
            y[i][j]=x[i][j];
}
void drop()//判断掉落
{
    memset(c,0,sizeof(c));
    for(int i=0;i<5;i++)
        for(int j=0,k=0;j<7;j++)
            if(a[i][j])c[i][k++]=a[i][j];
    copy(c,a);
}
bool clear()
{
    bool flag=false;
    int xx,yy,up,dn;
    for(int i=0;i<3;i++)//横向判断块数不小于3
        for(int j=0;j<7;j++)
        if(a[i][j])
        {
            for(xx=i;xx<5&&a[xx+1][j]==a[i][j];xx++);//横向
            if(xx-i+1>=3)
            {
                for(int k=i;k<=xx;k++)
                {
                    up=j;dn=j;
                    while(up+1<7&&a[k][up+1]==a[k][j])up++;
                    while(dn-1>=0&&a[k][dn-1]==a[k][j])dn--;
                    if(up-dn+1>=3)
                        for(int l=dn;l<=up;l++)
                            a[k][l]=0;
                    else a[k][j]=0;
                }
                flag=true;
            }
        }
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)//纵向判断块数不小于3
        if(a[i][j])
        {
            for(yy=j;yy+1<7&&a[i][yy+1]==a[i][j];yy++);//纵向
            if(yy-j+1>=3)
            {
                for(int k=j;k<=yy;k++)
                {
                    up=i;dn=i;
                    while(up+1<7&&a[up+1][k]==a[i][k])up++;
                    while(dn-1>=0&&a[dn-1][k]==a[i][k])dn--;
                    if(up-dn+1>=3)
                        for(int l=dn;l<=up;l++)
                            a[l][k]=0;
                    else a[i][k]=0;
                }
                flag=true;
            }
        }
    return flag;
}
void dfs(int step)
{
    if(step>n)//达到步数
    {
        if(empty())
        {
            for(int i=1;i<=n;i++)
                if(ans[i].dir)printf("%d %d -1\n",ans[i].x+1,ans[i].y);
                else printf("%d %d 1\n",ans[i].x,ans[i].y);
            exit(0);
        }
        return;
    }
    memset(sum,0,sizeof(sum));
    for(int i=0;i<5;i++)
        for(int j=0;j<7;j++)
            sum[a[i][j]]++;
    for(int i=1;i<=10;i++)//若当前状态里同种颜色方块数量不足3，直接返回
        if(sum[i]>0&&sum[i]<3)return;
    for(int i=0;i<4;i++)//右移优先于左移
        for(int j=0;j<7;j++)
            if(a[i][j]!=a[i+1][j])//若颜色相同则没有移动的必要
            {
                int b[10][10];
                copy(a,b);
                ans[step]=(node){i,j,!a[i][j]};//注意判断当前方块是否为空
                swap(a[i][j],a[i+1][j]);
                drop();
                while(clear())drop();
                dfs(step+1);
                copy(b,a);
            }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<5;i++)
        for(int j=0;;j++)
        {
            scanf("%d",&a[i][j]);
            if(!a[i][j])break;
        }
    dfs(1);
    printf("-1\n");
    return 0;//好习惯
}
```
补充一下 Hack 数据

一开始被 Hack 掉了，这个数据主要就是一个关于无效交换的特判，在往右边时不应该多加**不同才交换**。

---

## 作者：wsm52 (赞：1)

# 前言
恶心**模拟**、**搜索**和**剪枝**。
# 思路
首先，要记录下每个颜色的数量。

```cpp
int main(){
	scanf("%d",&n);
	for(int i=0;i<5;i++){
		int y=0,t;
		while(cin>>t,t){
			m[i][y++]=t;
			cnt[0]++;//0是方块总数量
			cnt[t]++;
		}
	}
	if(dfs(0)) for(int i=0;i<n;i++) printf("%d %d %d\n",path[i].x,path[i].y,path[i].l);
	else printf("-1\n");
	return 0;
}
```
然后，进行搜索，请看注释理解。

```cpp
bool dfs(int pos){//pos：移动步数
	if(pos==n) return !cnt[0];//判断总方块数量是否为0
	for(int i=1;i<=10;i++) if(cnt[i]&&cnt[i]<3) return false;//剪枝：如果当前存在一种方块的数量小于3且大于0，那它肯定删不完，所以没必要继续搜索。
	memcpy(cm[pos],m,sizeof m);//备份，用于回溯
	memcpy(kcnt[pos],cnt,sizeof cnt);
	for(int x=0;x<5;x++){
		for(int y=0;y<7;y++){
			if(m[x][y]){
				if(x+1<5){
					path[pos]={x,y,1};//向右移
					move(x,y,x+1);
					if(dfs(pos+1)) return true;
					memcpy(m,cm[pos],sizeof cm[pos]);//回溯
					memcpy(cnt,kcnt[pos],sizeof kcnt[pos]);
				}
				if(x-1>=0&&!m[x-1][y]){//由于右移的优先级大于左移，因此左移的时候要判断左移到的位置是否为空
					path[pos]={x,y,-1};//向左移
					move(x,y,x-1);
					if(dfs(pos+1)) return true;
					memcpy(m,cm[pos],sizeof cm[pos]);//回溯
					memcpy(cnt,kcnt[pos],sizeof kcnt[pos]);
				}
			}
		}
	}
	return false;
}
```
最重要的是实现 $\operatorname{move}$ 函数，也是这道题的难点。主要有一下三个难点。

- 处理掉落方块。
- 方块消除时的连锁反应。
- 类似此图的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/frzgg5mz.png)

## 难点一

![](https://cdn.luogu.com.cn/upload/image_hosting/mmgldame.png)

解决方块掉落的方法如下。

![](https://cdn.luogu.com.cn/upload/image_hosting/ldpewr1v.png)

因此，掉落方块处理的代码如下。

```cpp
for(int x=0;x<5;x++){
    int z=0;
    for(int y=0;y<7;y++) if(m[x][y]) m[x][z++]=m[x][y];
    while(z<7) m[x][z++]=0; 
}
```
## 难点三

消除方块的部分比较简单，我不过多讲述，请看代码。

```cpp
bool flag=false;
memset(vis,0,sizeof vis);
for(int x=0;x<5;x++){
	for(int y=0;y<7;y++){
		if(m[x][y]){
			int l=x,r=x;
			while(l-1>=0&&m[l-1][y]==m[x][y]) l--;//左扩
			while(r+1<5&&m[r+1][y]==m[x][y]) r++;//右扩
			if(r-l+1>=3){
				vis[x][y]=true;//由于需要将整个棋盘遍历一遍，因此没必要一次将所有可消除的方块打标记
				flag=true;//有方块可以消除
			}else{
				l=r=y;
				while(l-1>=0&&m[x][l-1]==m[x][y]) l--;//上扩
				while(r+1<7&&m[x][r+1]==m[x][y]) r++;//下扩
				if(r-l+1>=3){
					vis[x][y]=true;
					flag=true;
				}
			}
		} 
	}
}
if(flag){//消除方块
	for(int x=0;x<5;x++){
		for(int y=0;y<7;y++){
			if(vis[x][y]){
				cnt[m[x][y]]--;
				cnt[0]--;
				m[x][y]=0;
			}
		}
	}
}else break; 
```
但是，你有没有发现，上面呈现出的代码正好可以解决**难点三**。其实，**难点三**就是普通消除方块。
## 难点二
你肯定看到了消除方块的代码的最后的 **break**。其实，将上述代码结合起来，再套一个 **while true** 循环就行了。
# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m[10][10],cm[6][10][10],cnt[50],kcnt[10][50];
bool vis[10][10];
struct nb{
	int x,y,l;
}path[10];
void move(int a,int b,int c){
	swap(m[a][b],m[c][b]);//交换方块位置
	while(true){//处理连锁反应
		for(int x=0;x<5;x++){//处理掉落方块
			int z=0;
			for(int y=0;y<7;y++) if(m[x][y]) m[x][z++]=m[x][y];
			while(z<7) m[x][z++]=0; 
		}
		bool flag=false;
		memset(vis,0,sizeof vis);
		for(int x=0;x<5;x++){//判断可消除的方块
			for(int y=0;y<7;y++){
				if(m[x][y]){
					int l=x,r=x;
					while(l-1>=0&&m[l-1][y]==m[x][y]) l--;//左扩
					while(r+1<5&&m[r+1][y]==m[x][y]) r++;//右扩
					if(r-l+1>=3){
						vis[x][y]=true;//由于需要将整个棋盘遍历一遍，因此没必要一次将所有可消除的方块打标记
						flag=true;
					}else{
						l=r=y;
						while(l-1>=0&&m[x][l-1]==m[x][y]) l--;上扩
						while(r+1<7&&m[x][r+1]==m[x][y]) r++;//下扩
						if(r-l+1>=3){
							vis[x][y]=true;
							flag=true;
						}
					}
				} 
			}
		}
		if(flag){//消除方块
			for(int x=0;x<5;x++){
				for(int y=0;y<7;y++){
					if(vis[x][y]){
						cnt[m[x][y]]--;
						cnt[0]--;
						m[x][y]=0;
					}
				}
			}
		}else break;//如果当前已经没有方块可消除了，那就跳出循环
	}
}
bool dfs(int pos){//pos：移动步数
	if(pos==n) return !cnt[0];//判断总方块数量是否为0
	for(int i=1;i<=10;i++) if(cnt[i]&&cnt[i]<3) return false;//剪枝：如果当前存在一种方块的数量小于3且大于0，那它肯定删不完，所以没必要继续搜索。
	memcpy(cm[pos],m,sizeof m);//备份，用于回溯
	memcpy(kcnt[pos],cnt,sizeof cnt);
	for(int x=0;x<5;x++){
		for(int y=0;y<7;y++){
			if(m[x][y]){
				if(x+1<5){
					path[pos]={x,y,1};//向右移
					move(x,y,x+1);
					if(dfs(pos+1)) return true;
					memcpy(m,cm[pos],sizeof cm[pos]);//回溯
					memcpy(cnt,kcnt[pos],sizeof kcnt[pos]);
				}
				if(x-1>=0&&!m[x-1][y]){//由于右移的优先级大于左移，因此左移的时候要判断左移到的位置是否为空
					path[pos]={x,y,-1};//向左移
					move(x,y,x-1);
					if(dfs(pos+1)) return true;
					memcpy(m,cm[pos],sizeof cm[pos]);//回溯
					memcpy(cnt,kcnt[pos],sizeof kcnt[pos]);
				}
			}
		}
	}
	return false;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<5;i++){
		int y=0,t;
		while(cin>>t,t){
			m[i][y++]=t;
			cnt[0]++;//0是方块总数量
			cnt[t]++;
		}
	}
	if(dfs(0)) for(int i=0;i<n;i++) printf("%d %d %d\n",path[i].x,path[i].y,path[i].l);
	else printf("-1\n");
	return 0;
}
```

---

## 作者：niuzh (赞：1)

### 思路
很明显，此题使用 dfs。

枚举每一步可能的移动即可。（由于 $n$ 极小无比）

难度在于代码实现。

#### 定义变量

这里用 $mp$ 数组存储图 $del$ 存储在消除方格时存储要消除的变量（不能直接删的原因详见题面图 $5$），$last$ 数组用作备份移动前棋盘的样子。

对 $last$ 数组的解释：由于不能通过消除并下落后的棋盘还原出移动前棋盘的样子，所以必须需要备份数组。而需要 $3$ 维的原因在于防止在往下搜索后把当前的备份覆盖，第一维开 $15$ 是因为深搜不会同时搜索相同深度的不同状态，用搜索深度标记备份即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,mp[15][18],last[15][15][18];
bitset<20> del[20];//等同于 bool del[20][20];
struct node
{
	int a,b,c;
};
vector<node> ans;
```
#### 备份函数

没什么可以说的，就是根据编号存储与还原棋盘。
```cpp
void save_last(int x)
{
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=7;j++)
		{
			last[x][i][j]=mp[i][j];
		}
	}
}
void turn_back(int x)
{
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=7;j++)
		{
			mp[i][j]=last[x][i][j];
		}
	}
}
```
#### 消除相同

关于 $del$ 数组的用处，上文已经提到。

这里枚举的是 $3$ 个连续同颜色格子的中间格子，枚举左端点或右端点的格子也可以。

返回 $0$ 代表没有消除格子，返回 $1$ 代表消除了格子，只要消除了格子就可能需要再次下落，而没有消除就不用。
```cpp
bool delete_same()
{
	for(int i=1;i<=5;i++)
	{
		del[i].reset();
	}
	bool flag=0;
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=7;j++)
		{
			if(i>=2&&i<=4&&mp[i][j]&&mp[i][j]==mp[i-1][j]&&mp[i][j]==mp[i+1][j])//判断是否越界，格子里有没有东西，颜色是否相等
			{
				flag=1;//需要消除格子
				del[i][j]=del[i-1][j]=del[i+1][j]=1;//记录需要消除的格子
			}
			if(j>=2&&j<=6&&mp[i][j]&&mp[i][j]==mp[i][j-1]&&mp[i][j]==mp[i][j+1])//同上
			{
				flag=1;
				del[i][j]=del[i][j-1]=del[i][j+1]=1;
			}
		}
	}
	if(!flag)
	{
		return 0;
	}
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=7;j++)
		{
			if(del[i][j])
			{
				mp[i][j]=0;//消除
			}
		}
	}
	return 1;
}
```
#### 下落 ~~drop it！~~

从下到上枚举每一位，$cnt$ 用做存储当前格子可以下落的格子数量，如果格子不是空的，就下落，不用将 $cnt$ 清 $0$，因为当前格子下落会使下面的 $cnt$ 个空格子去到格子上面。

![](https://cdn.luogu.com.cn/upload/image_hosting/ibnkifk9.png?x-oss-process=image/resize,m_lfit,h_850,w_1125)
```cpp
void drop()
{
	for(int i=1;i<=5;i++)//枚举每一列
	{
		int cnt=0;
		for(int j=1;j<=7;j++)//从下到上枚举每一行
		{
			if(!mp[i][j])//格子是空的
			{
				cnt++;//记录下落个数
			}
			else//格子需要下落
			{
				if(!cnt)//无法下落
				{
					continue;
				}
				swap(mp[i][j],mp[i][j-cnt]);//下落
			}
		}
	}
}
```
#### 移动格子

**注意要先下落再消除。**

因为可能与空气交换，所以需要先下落。$op$ 是 $1$ 时往左移；是 $-1$ 时往右移动。
```cpp
void move(int x,int y,int op)
{
	swap(mp[x][y],mp[x+op][y]);//交换
	do
	{
		drop();//下落
	}while(delete_same());//如果消除了，就要再次下落
}
```

#### 检查是否消干净

同样每什么可以说的，检查是否有剩余就行了。由于移动后直接完成消除与下落，所以可以直接判断最底层是否消完。
```cpp
bool check()
{
	for(int i=1;i<=5;i++)
	{
		if(mp[i][1])
		{
			return false;
		}
	}
	return true;
}
```

#### 搜索

标准的深搜板子。

注意输出时棋盘右下角是 $(0,0)$。
```cpp
void dfs(int x)
{
	if(x>n)
	{
		if(!check())//检查是否消完
		{
			return;
		}
		for(auto i:ans)//输出
		{
			cout<<i.a-1<<" "<<i.b-1<<" "<<i.c<<'\n';
		}
		exit(0);
	}
	save_last(x);//按照搜索层次备份。
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=7;j++)
		{
			if(mp[i][j])//格子不是空的
			{
				if(i<=4)//不会越界
				{
					move(i,j,1);//移动
					ans.push_back({i,j,1});//记录操作
					dfs(x+1);//往下搜
					ans.pop_back();//删除操作
					turn_back(x);//还原备份
				}
				if(i>=2)//同上
				{
					move(i,j,-1);
					ans.push_back({i,j,-1});
					dfs(x+1);
					ans.pop_back();
					turn_back(x);
				}
			}
		}
	}
}
```
#### 主程序

没什么可以说的。
```cpp
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1,x;i<=5;i++)
	{
		x=0;
		while(cin>>mp[i][++x])//输入
		{
			if(!mp[i][x])
			{
				break;
			}
		}
	}
	dfs(1);
	cout<<-1;//此时没退出代表无法完成。
	return 0;
}
```
### 代码

把上文的函数直接连起来就行。

~~但出于人道主义，~~ 这里提供一个无注释的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,mp[15][18],last[15][15][18];
bitset<20> del[20];
struct node
{
	int a,b,c;
};
vector<node> ans;
bool check()
{
	for(int i=1;i<=5;i++)
	{
		if(mp[i][1])
		{
			return false;
		}
	}
	return true;
}
void save_last(int x)
{
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=7;j++)
		{
			last[x][i][j]=mp[i][j];
		}
	}
}
void turn_back(int x)
{
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=7;j++)
		{
			mp[i][j]=last[x][i][j];
		}
	}
}
bool delete_same()
{
	for(int i=1;i<=5;i++)
	{
		del[i].reset();
	}
	bool flag=0;
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=7;j++)
		{
			if(i>=2&&i<=4&&mp[i][j]&&mp[i][j]==mp[i-1][j]&&mp[i][j]==mp[i+1][j])
			{
				flag=1;
				del[i][j]=del[i-1][j]=del[i+1][j]=1;
			}
			if(j>=2&&j<=6&&mp[i][j]&&mp[i][j]==mp[i][j-1]&&mp[i][j]==mp[i][j+1])
			{
				flag=1;
				del[i][j]=del[i][j-1]=del[i][j+1]=1;
			}
		}
	}
	if(!flag)
	{
		return false;
	}
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=7;j++)
		{
			if(del[i][j])
			{
				mp[i][j]=0;
			}
		}
	}
	return true;
}
void drop()
{
	for(int i=1;i<=5;i++)
	{
		int cnt=0;
		for(int j=1;j<=7;j++)
		{
			if(!mp[i][j])
			{
				cnt++;
			}
			else
			{
				if(!cnt)
				{
					continue;
				}
				swap(mp[i][j],mp[i][j-cnt]);
			}
		}
	}
}
void move(int x,int y,int op)
{
	swap(mp[x][y],mp[x+op][y]);
	do
	{
		drop();
	}while(delete_same());
}
void dfs(int x)
{
	if(x>n)
	{
		if(!check())
		{
			return;
		}
		for(auto i:ans)
		{
			cout<<i.a-1<<" "<<i.b-1<<" "<<i.c<<'\n';
		}
		exit(0);
	}
	save_last(x);
	for(int i=1;i<=5;i++)
	{
		for(int j=1;j<=7;j++)
		{
			if(mp[i][j])
			{
				if(i<=4)
				{
					move(i,j,1);
					ans.push_back({i,j,1});
					dfs(x+1);
					ans.pop_back();
					turn_back(x);
				}
				if(i>=2)
				{
					move(i,j,-1);
					ans.push_back({i,j,-1});
					dfs(x+1);
					ans.pop_back();
					turn_back(x);
				}
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1,x;i<=5;i++)
	{
		x=0;
		while(cin>>mp[i][++x])
		{
			if(!mp[i][x])
			{
				break;
			}
		}
	}
	dfs(1);
	cout<<-1;
	return 0;
}
```

---

## 作者：lihongqian__int128 (赞：0)

一眼搜索。

下面的代码均以最上面一行为第一行，最左边一列为第一列（和题目的上下是反的）。

首先，先写一个判空函数。

```cpp
bool empty(){
	for(int i=1;i<=7;i++)
		for(int j=1;j<=5;j++)
			if(w[i][j])
				return 0;
	return 1;
}
```

非常好理解，不再赘述。

然后是消除函数。

```cpp
bool d[8][6];//判断是否被删除
bool elim(){
	bool flag=0;
	memset(d,0,sizeof d);
	for(int i=1;i<=7;i++)
		for(int j=1;j<=5;j++){
			if(i<6&&w[i][j]&&w[i][j]==w[i+1][j]&&w[i][j]==w[i+2][j])//一行连着三个
				d[i][j]=d[i+1][j]=d[i+2][j]=1;
			if(j<4&&w[i][j]&&w[i][j]==w[i][j+1]&&w[i][j]==w[i][j+2])//一列连着三个
				d[i][j]=d[i][j+1]=d[i][j+2]=1;
		}
	for(int i=1;i<=7;i++)
		for(int j=1;j<=5;j++)
			if(d[i][j])
				w[i][j]=0,flag=1;//删除
	return flag;
}
```

为什么要返回 `bool` 类型呢？因为可能会多次消除，需要判断是否有清空的。

接着是下落函数。

```cpp
void down(){
	for(int i=7;i;i--)
		for(int j=1;j<=5;j++){
			if(!w[i][j])continue;
			int t=i;
			while(t<7&&!w[t+1][j])swap(w[t][j],w[t+1][j]),t++;
		}
}
```

为什么要从下面的行开始枚举呢？因为下面的方块下落可能导致上面的方块下落。

写一个输出函数，方便找到答案直接输出。

```cpp
void output(){
	for(int i=1;i<=n;i++)
		cout<<y[i]-1<<' '<<7-x[i]<<' '<<g[i]<<'\n';
	exit(0);
}
```

然后就是搜索了。

```cpp
void dfs(int st){
	if(st>n){
		if(empty())output();//空了就输出
		return;
	}
	int t[8][6];
	memcpy(t,w,sizeof t);
	for(int j=1;j<=5;j++)//！！！一定要先枚举 j！！！（否则优先级就不对了）
		for(int i=7;i;i--){
			if(!w[i][j])continue;
			if(j<5){
				swap(w[i][j],w[i][j+1]);//交换
				down();//先下落一次
				while(elim())down();//只要能消除，就一直下落
				x[st]=i,y[st]=j,g[st]=1;//记录
				dfs(st+1);
				memcpy(w,t,sizeof w);//赋回来
			}
			if(j>1){
				if(w[i][j-1])continue;//小优化（如果左边的是有方块的，那么交换字典序一定不优）
				swap(w[i][j],w[i][j-1]);
				down();//先下落一次
				while(down())elim();//只要能消除，就一直下落
				x[st]=i,y[st]=j,g[st]=-1;//记录
				dfs(st+1);
				memcpy(w,t,sizeof w);//赋回来
			}
		}
}
```

然后就写完了。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w[8][6],x[6],y[6],g[6];
void output(){
	for(int i=1;i<=n;i++)
		cout<<y[i]-1<<' '<<7-x[i]<<' '<<g[i]<<'\n';
	exit(0);
}
bool empty(){
	for(int i=1;i<=7;i++)
		for(int j=1;j<=5;j++)
			if(w[i][j])
				return 0;
	return 1;
}
bool d[8][6];
bool elim(){
	bool flag=0;
	memset(d,0,sizeof d);
	for(int i=1;i<=7;i++)
		for(int j=1;j<=5;j++){
			if(i<6&&w[i][j]&&w[i][j]==w[i+1][j]&&w[i][j]==w[i+2][j])
				d[i][j]=d[i+1][j]=d[i+2][j]=1;
			if(j<4&&w[i][j]&&w[i][j]==w[i][j+1]&&w[i][j]==w[i][j+2])
				d[i][j]=d[i][j+1]=d[i][j+2]=1;
		}
	for(int i=1;i<=7;i++)
		for(int j=1;j<=5;j++)
			if(d[i][j])
				w[i][j]=0,flag=1;
	return flag;
}
void down(){
	for(int i=7;i;i--)
		for(int j=1;j<=5;j++){
			if(!w[i][j])continue;
			int t=i;
			while(t<7&&!w[t+1][j])swap(w[t][j],w[t+1][j]),t++;
		}
}
void dfs(int st){
	if(st>n){
		if(empty())output();
		return;
	}
	int t[8][6];
	memcpy(t,w,sizeof t);
	for(int j=1;j<=5;j++)
		for(int i=7;i;i--){
			if(!w[i][j])continue;
			if(j<5){
				swap(w[i][j],w[i][j+1]);
				down();
				while(elim())down();
				x[st]=i,y[st]=j,g[st]=1;
				dfs(st+1);
				memcpy(w,t,sizeof w);
			}
			if(j>1){
				if(w[i][j-1])continue;
				swap(w[i][j],w[i][j-1]);
				down();
				while(elim())down();
				x[st]=i,y[st]=j,g[st]=-1;
				dfs(st+1);
				memcpy(w,t,sizeof w);
			}
		}
}
int main(){
	cin>>n;
	for(int i=1;i<=5;i++)
		for(int j=7;cin>>w[j][i],w[j][i];j--);
	dfs(1);
	cout<<-1;
	return 0;
}
```

---

