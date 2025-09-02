# [GCJ 2013 Qualification] Tic-Tac-Toe-Tomek

## 题目描述

**Tic-Tac-Toe-Tomek** 是一种在 $4 \times 4$ 的方形棋盘上进行的游戏。游戏开始时棋盘是空的，仅可能存在一个特殊符号 `'T'` 在棋盘上的某个位置。游戏有两名玩家：X 和 O，他们轮流进行移动，玩家 X 先手。每一次移动时，玩家都必须将自己的符号放在棋盘上的一个空格中。玩家 X 的符号为 `'X'`，玩家 O 的符号为 `'O'`。

每次玩家落子后，如果棋盘上出现了一行、一列或一条对角线满足以下任意一个条件，则该玩家获胜，游戏立即结束：

- 该行（列或对角线）中有连续的 $4$ 个玩家自己的符号；
- 或者该行（列或对角线）中有连续的 $3$ 个玩家自己的符号和一个 `'T'` 符号。

若未出现上述情况，则游戏继续，由对方玩家进行下一步操作。如果棋盘全部填满且没有人获胜，则游戏以平局结束。具体请参照给出的样例输入和输出。

给定一个当前游戏状态的 $4 \times 4$ 的棋盘描述，棋盘中字符可能为 `'X'`, `'O'`, `'T'` 和 `'.'`（其中 `'.'` 表示空格），你的任务是判断当前游戏状态，可能的状态包括：

- `"X won"`（游戏已结束，X 胜利）
- `"O won"`（游戏已结束，O 胜利）
- `"Draw"`（游戏结束，平局）
- `"Game has not completed"`（游戏尚未结束）

注意：即使游戏结局已经可以明确预见，只要棋盘中存在空格且游戏尚未实际结束，都必须输出 `"Game has not completed"`。

## 说明/提示

**样例说明**

虽然你的浏览器可能无法显示样例输入中最后一个测试用例后的空行，但实际输入文件中确实存在该空行。

**限制条件**

- 题目给出的棋盘状态保证是通过正常进行 Tic-Tac-Toe-Tomek 游戏所能达到的状态。

**小数据集（10 分，测试集 1 - 可见）**

- $1 \leq T \leq 10$

**大数据集（20 分，测试集 2 - 不可见）**

- $1 \leq T \leq 1000$

翻译由 ChatGPT-4.5 完成。

## 样例 #1

### 输入

```
6
XXXT
....
OO..
....

XOXT
XXOO
OXOX
XXOO

XOX.
OX..
....
....

OOXX
OXXX
OX.T
O..O

XXXO
..O.
.O..
T...

OXXX
XO..
..O.
...O```

### 输出

```
Case #1: X won
Case #2: Draw
Case #3: Game has not completed
Case #4: O won
Case #5: O won
Case #6: O won```

# 题解

## 作者：ykhk10710o_o (赞：7)

# P13281 [GCJ 2013 Qualification] Tic-Tac-Toe-Tomek
# 题目大意
将整张图遍历一遍，若有 $X$ 或 $O$ 棋子连成四个，~~四子棋~~，则有人胜利，否则游戏平局或未结束。
# 判断方式
依题意，要判别胜负，有以下判断方式
1. 竖向
2. 横向
3. 自左向右斜下
4. 自右向左斜下
 
乍一看，挺简单，~~水题不是~~？

BUT 细节卡了我十分钟。。。（其实是一个小时）

# 细节
1. 如果有棋子已经赢了，那算游戏结束，但是若还没结束，尽管**再怎么下都是平局**，它都算没结束。
2. 题目有一个 $T$  ，它充当万能角色，若此行或列有一个 $T$ 和三个 $X$ , 算 $X$ 赢 ，不要输成 $T$ 了。
3. 最坑的点，只要判断过程中，出现了空格（即顿号），这行就没有结果，数组下标一弄错就输出顿号胜利~~顿号得了MVP~~, 一发现错误，就要四种情况全改。

剩下就是代码了

# 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
char a[10][10];
int F;
char ji;
int flag;
signed main(){
	cin>>T;
	for(int i=1;i<=T;i++){
		F=0;
		for(int j=1;j<=4;j++){
			cin>>a[j];
			for(int k=0;k<=3;k++){
				if(a[j][k]=='.'){
					F=1;//判断是否结束或平局，后面要考 
				} 
			}
		}
		for(int j=1;j<=4;j++){
			if(a[j][0]=='.'||a[j][1]=='.'){
                flag=1;
                continue;//没下完，无赢家，看下一行 
            }
			if(a[j][0]=='T')ji=a[j][1];
			else ji=a[j][0];//ji表示第一行的第一个棋子 
			flag=0;//默认有赢家 
			for(int k=0;k<=3;k++){
				if(a[j][k]!=ji&&a[j][k]!='T'){//如果这一行出现不同棋子，则无人在这行胜利 
					flag=1;//无赢家，打标记 
					break;
				}
			}
			if(!flag)break;//有赢家直接输出 
		}
		if(!flag){
			printf("Case #%d: %c won\n",i,ji);//如果只有X或O则输出赢家 
			continue;//终止以防多输出 
		}
		for(int j=0;j<=3;j++){//同上，换成列 
			if(a[1][j]=='.'||a[2][j]=='.'){
                flag=1;
                continue;//没下完，无赢家，看下一行 
            }
			if(a[1][j]=='T')ji=a[2][j];
			else ji=a[1][j];
			flag=0;
			for(int k=1;k<=4;k++){
				if(a[k][j]!=ji&&a[k][j]!='T'){
					flag=1;
					break;
				}
			}
			if(!flag)break;
		}
		if(!flag){
			printf("Case #%d: %c won\n",i,ji);
			continue;
		}
		if(a[1][0]!='.'&&a[2][1]!='.'){//时刻判一下
		if(a[1][0]=='T')ji=a[2][1];
		else ji=a[1][0];
		flag=0;
		for(int j=1;j<=4;j++){//右斜下对角线 
			if(a[j][j-1]!=ji&&a[j][j-1]!='T'){
				flag=1;
			}
		}
		if(!flag){
			printf("Case #%d: %c won\n",i,ji);
			continue;
		}
		}
		if(a[1][3]!='.'&&a[2][2]!='.'){
		if(a[1][3]=='T')ji=a[2][2];
		else ji=a[1][3];
		flag=0;
		for(int j=1;j<=4;j++){//右斜上对角线 
			if(a[j][4-j]!=ji&&a[j][4-j]!='T'){
				flag=1;
			}
		}
		if(!flag){
			printf("Case #%d: %c won\n",i,ji);
			continue;
		}	
		}
		if(F){//走到这里说明要么平局，要么未结束 
			printf("Case #%d: Game has not completed\n",i);//有空格，未结束 
		}else{
			printf("Case #%d: Draw\n",i);//结局注定 
		}
	}
} 
```

调了好久啊QAQ，中途网络还崩了，不看仔细点都不能短时间调出来。~~我是看评测结果改的人~~

---

## 作者：abc1234shi (赞：6)

# “题前”分析
“磨你题”。

最多模拟不超过十万次，加上一些杂七杂八的复杂度，模拟一定不会超时。

记住，数据范围很小且题目中有“**规则**怪谈”时（它给的规则大多很奇怪），这题就一定是**模拟题**。
# 思路
规则给的很清楚：判断**横竖斜**（行、列、对角线）是否有**四个同样**的或**三个同样**的**加个** `T`（细节：三个同样的不能是 `.`）。如果**没有**人获胜，且盘面没有被**填满**（存在 `.`），则游戏没有结束，否则输出**平局**。
# 思路解析
## 读入：  
 读入不必说，注意一点，你从哪**开始读入**就从哪枚举（`string` 字符串从 $0$ 枚举）。

## 判断空格：  
只要发现有一个字符是 `.`，就说明棋盘还没满，后面可能还要接着下。但我们不能确定是否已经下完，万一下完了，对手被秒了，结果你就输出没下完，活该过不了。所以最好使用一个**布尔变量**，标记为**假**。

 ### 检查谁赢了：
 
分三部分查：

- **每一行**：从左到右数。如果一行里 `X` 有 $4$ 个，或者 `X` 有 $3$ 个再加一个 `T`，X 方就赢了。O 方也是同理。  
 - **每一列**：从上到下数，规则同上。
 -  **两条对角线**：左上到右下、右上到左下，规则同上。

这边注意一下：如果是 `X` 有 $3$ 个再加一个 `T`，会有两种情况，别漏了。

只要任何一个方向满足条件，就可以直接输出了。但我建议定义两个布尔变量，如果 X 方获胜把对应的布尔变量**增加**（O 方获胜同理）。

### 输出结果：  
按照优先级输出（X 赢和 O 赢处于**同一优先级**，但**不可能**出现二人都赢的情况，所以为了方便判断，可以将任意一个**先判断**）：  
- 如果 X 赢了，输出 `"X won"`。  
 - 如果 O 赢了，输出 `"O won"`。  
 - 如果棋盘满了但没人赢，输出 `"Draw"`。  
- 如果还没满且没人赢，输出 `"Game has not completed"`。
# 代码

```cpp
#include <iostream>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        char b[5][5];
        bool full = 1, x = 0, o = 0;
        for (int i = 0; i < 4; ++i) cin >> b[i];
        
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (b[i][j] == '.') full = 0;
            }
        }
        
        for (int i = 0; i < 4; ++i) {
            int cx = 0, co = 0, ct = 0;
            for (int j = 0; j < 4; ++j) {
                if (b[i][j] == 'X') cx++;
                else if (b[i][j] == 'O') co++;
                else if (b[i][j] == 'T') ct++;
            }
            if (cx == 4 || (cx == 3 && ct == 1)) x = 1;
            if (co == 4 || (co == 3 && ct == 1)) o = 1;
        }
        
        for (int j = 0; j < 4; ++j) {
            int cx = 0, co = 0, ct = 0;
            for (int i = 0; i < 4; ++i) {
                if (b[i][j] == 'X') cx++;
                else if (b[i][j] == 'O') co++;
                else if (b[i][j] == 'T') ct++;
            }
            if (cx == 4 || (cx == 3 && ct == 1)) x = 1;
            if (co == 4 || (co == 3 && ct == 1)) o = 1;
        }
        
        int cx = 0, co = 0, ct = 0;
        for (int i = 0; i < 4; ++i) {
            if (b[i][i] == 'X') cx++;
            else if (b[i][i] == 'O') co++;
            else if (b[i][i] == 'T') ct++;
        }
        if (cx == 4 || (cx == 3 && ct == 1)) x = 1;
        if (co == 4 || (co == 3 && ct == 1)) o = 1;
        
        cx = 0, co = 0, ct = 0;
        for (int i = 0; i < 4; ++i) {
            if (b[i][3 - i] == 'X') cx++;
            else if (b[i][3 - i] == 'O') co++;
            else if (b[i][3 - i] == 'T') ct++;
        }
        if (cx == 4 || (cx == 3 && ct == 1)) x = 1;
        if (co == 4 || (co == 3 && ct == 1)) o = 1;
        
        cout << "Case #" << t << ": ";
        if (x) cout << "X won";
        else if (o) cout << "O won";
        else if (full) cout << "Draw";
        else cout << "Game has not completed";
        cout << endl;
    }
    return 0;
}
```

---

## 作者：nice_hamburger (赞：5)

# P13281 [GCJ 2013 Qualification] Tic-Tac-Toe-Tomek

## 题目大意
本题就是模拟 $T$ 局四子棋游戏，对于每局游戏按要求输出游戏结果，所以我们直接模拟就好了。

## 模拟

### 竖向

因为某个人赢的要求很简单，要么当前列全是他的棋子，要么当前列有 $3$ 个他的棋子和一个万能棋子 $T$，所以直接循环枚举就行了，注意判断当前位置不是 $.$ 以及万能棋子 $T$，不然会出错。

#### 部分代码


```cpp
//竖向 
		F = 0;
		for(int i = 1;i <= 4;i++){
			if(g[1][i] == '.'){
				continue;
			}
			fl = 1;
			now = g[1][i];
			if(now == 'T') now = g[2][i];
			if(now == '.') continue;
			for(int j = 1;j <= 4;j++){
				if(g[j][i] != now && g[j][i] != 'T'){
					fl = 0;
					break;
				}
			}
			if(fl == 1){
				cout << "Case #"<< ++cnt << ": " << now << " won\n";//答案输出
				F = 1;
				break;
			}	
		}
		if(F) continue;//当前已有解
```

### 横向

与竖向同理，不作赘述。

#### 部分代码


```cpp
//横向 
		char now;
		bool fl,F;
		F = 0;
		for(int i = 1;i <= 4;i++){
			if(g[i][1] == '.'){
				continue;
			}
			fl = 1;
			now = g[i][1];
			if(now == 'T') now = g[i][2];
			if(now == '.') continue;
			for(int j = 1;j <= 4;j++){
				if(g[i][j] != now && g[i][j] != 'T'){
					fl = 0;
					break;
				}			
//				cout << i << ' ' << j <<'\n';
			}
			if(fl == 1){
				cout << "Case #"<< ++cnt << ": " << now << " won\n";
				F = 1;
				break;
			}
		}
		if(F) continue;
```

### 两个斜向

比横向和竖向简单多了，同样要记得判断，不作赘述。

#### 部分代码


```cpp
//斜向 1
		F = 0;
		now = g[1][1];
		if(now == 'T') now = g[2][2];
		if(now != '.'){
			fl = 1;
			for(int i = 1;i <= 4;i++){
				if(g[i][i] != now && g[i][i] != 'T'){
					fl = 0;
					break;
				}
//				cout << i << ' ' << i <<'\n';
			}	
			if(fl){
				cout << "Case #"<< ++cnt << ": " << now << " won\n";
				continue;
			}
		}
		
		 //斜向2 
		F = 0;
		now = g[1][4];
		if(now != '.'){
			fl = 1;
			if(now == 'T') now = g[2][3];
			for(int i = 1;i <= 4;i++){
				if(g[i][4 - i + 1] != now && g[i][4 - i + 1] != 'T'){
					fl = 0;
					break;
				}
//				cout << i << ' ' << 4 - i + 1<<'\n';
			}		
			if(fl){
				cout << "Case #"<< ++cnt << ": " << now << " won\n";
				continue;
			}
		}
```

### 其他情况

就是 _游戏结束，平局_ 或 _游戏尚未结束_ ，在输入时判断即可。

#### 部分代码


```cpp
        bool full = 1;//标记
		for(int i = 1;i <= 4;i++){
			for(int j = 1;j <= 4;j++){
				cin >> g[i][j];
				if(g[i][j] == '.'){
					full = 0;
				}
			}
		}
//中间的代码在上面，省略
        if(full){
  			cout << "Case #"<< ++cnt << ": Draw" << "\n";
  			continue;
  		}
  		else {
  			cout << "Case #"<< ++cnt << ": Game has not completed" << "\n";
  		}
```

## 总结

是一道考验处理细节能力的模拟题，需要耐着性子做一做，不然还真的很难调出来（本蒟蒻卡了20分钟才调好QAQ，[记录](https://www.luogu.com.cn/record/224593478)）。

---

## 作者：wanghaotian0227 (赞：4)

# P13281 题解
## 题意
题目的意思是让我们判断游戏的状态，有四种情况，需要用`if-else`结构判断：

- `X 获胜`
- `O 获胜`
- `平局`
- `尚未结束`

而获胜有三种情况（同上）：

1.纵列获胜
2.横行获胜
3.对角线获胜

只需要加入~~亿~~一点特判就可以了
## 程序
判断纵列时，检测每一列，若是字符不为`X`和`T`（`O`同理），那么这一列就不可能获胜，继续检测。
用两个 $fx,fo$ 变量来检测。
```cpp
for(int i=1;i<=4;i++)//检测纵向列是否达成要求 
	{
		int fx=1,fo=1;//flag检测
		for(int j=1;j<=4;j++)
		{
			if(p[i][j]!='X'&&p[i][j]!='T') fx=0;
			if(p[i][j]!='O'&&p[i][j]!='T') fo=0; 
		}
		if(fx==1){cout<<"Case #"<<t<<": X won"<<endl;return;}
		if(fo==1){cout<<"Case #"<<t<<": O won"<<endl;return;}
	}
```
判断横行时，与纵列同理，同样是检测字符。
```cpp
for(int i=1;i<=4;i++)//检测横向行是否达成要求 
	{
		int fx=1,fo=1;
		for(int j=1;j<=4;j++)
		{
			if(p[j][i]!='X'&&p[j][i]!='T') fx=0;
			if(p[j][i]!='O'&&p[j][i]!='T') fo=0; 
		}
		if(fx==1){cout<<"Case #"<<t<<": X won"<<endl;return;}
		if(fo==1){cout<<"Case #"<<t<<": O won"<<endl;return;}
	}
```
判断对角线时，一定要注意 $p$ 数组下标。而且 $4 \times 4$ 的方格对角线有两条。一定不要写错下标。
```cpp
int fx3=1,fo3=1,fx4=1,fo4=1;
	for(int i=1;i<=4;i++)//检测对角线 
	{
		if(p[i][i]!='X'&&p[i][i]!='T') fx3=0;//左上到右下 
		if(p[i][i]!='O'&&p[i][i]!='T') fo3=0;
		if(p[i][5-i]!='X'&&p[i][5-i]!='T') fx4=0;//右上到左下 
		if(p[i][5-i]!='O'&&p[i][5-i]!='T') fo4=0;
	}
	if(fx3==1){cout<<"Case #"<<t<<": X won"<<endl;return;}
	if(fo3==1){cout<<"Case #"<<t<<": O won"<<endl;return;}
	if(fx4==1){cout<<"Case #"<<t<<": X won"<<endl;return;}
	if(fo4==1){cout<<"Case #"<<t<<": O won"<<endl;return;}
```
获胜时的情况判断完了，接下来还剩平局和尚未结束。因为平局这种情况发生时棋盘一定是满的，不会出现空格`.`。所以我们可以通过检测棋盘，如果发现`.`就是尚未结束，没有发现则是平局。
```cpp
for(int i=1;i<=4;i++)//检测完成，若没有达成要求，就只有没结束或平局两种情况 
	{
		for(int j=1;j<=4;j++)
		{
			if(p[i][j]=='.')//若出现空格则肯定是没有结束 
			{
				cout<<"Case #"<<t<<": Game has not completed"<<endl;
				return;
			}
		}
	}
	cout<<"Case #"<<t<<": Draw"<<endl;//排除所有情况就一定平局
```
核心部分结束，因为这是典型的二维数组题，故时间复杂度为 $O(n^2)$ 。


ps:这道题的输出有点特殊（算是GCJ的特殊吧）。一定要开一个全局变量 $t$ 来储存当前是第几个测试点，如果开局部变量的话函数部分没法引用。
## 代码
本题的完整代码
```cpp
#include <iostream>
#include <string>
using namespace std;
int t;//t表示现在是第几个测试用例 
void solve()
{
	char p[5][5];string s;
	for(int i=1;i<=4;i++)
	{
		cin>>s;//用string类型输入，转成数组（不转也可以） 
		for(int j=1;j<=4;j++)
		{
			p[i][j]=s[j-1];//我习惯for循环从1开始 
		}
	}
	for(int i=1;i<=4;i++)//检测纵向列是否达成要求 
	{
		int fx=1,fo=1;//flag检测
		for(int j=1;j<=4;j++)
		{
			if(p[i][j]!='X'&&p[i][j]!='T') fx=0;
			if(p[i][j]!='O'&&p[i][j]!='T') fo=0; 
		}
		if(fx==1){cout<<"Case #"<<t<<": X won"<<endl;return;}
		if(fo==1){cout<<"Case #"<<t<<": O won"<<endl;return;}
	}
	for(int i=1;i<=4;i++)//检测横向行是否达成要求 
	{
		int fx=1,fo=1;
		for(int j=1;j<=4;j++)
		{
			if(p[j][i]!='X'&&p[j][i]!='T') fx=0;
			if(p[j][i]!='O'&&p[j][i]!='T') fo=0; 
		}
		if(fx==1){cout<<"Case #"<<t<<": X won"<<endl;return;}
		if(fo==1){cout<<"Case #"<<t<<": O won"<<endl;return;}
	}
	int fx3=1,fo3=1,fx4=1,fo4=1;
	for(int i=1;i<=4;i++)//检测对角线 
	{
		if(p[i][i]!='X'&&p[i][i]!='T') fx3=0;//左上到右下 
		if(p[i][i]!='O'&&p[i][i]!='T') fo3=0;
		if(p[i][5-i]!='X'&&p[i][5-i]!='T') fx4=0;//右上到左下 
		if(p[i][5-i]!='O'&&p[i][5-i]!='T') fo4=0;
	}
	if(fx3==1){cout<<"Case #"<<t<<": X won"<<endl;return;}
	if(fo3==1){cout<<"Case #"<<t<<": O won"<<endl;return;}
	if(fx4==1){cout<<"Case #"<<t<<": X won"<<endl;return;}
	if(fo4==1){cout<<"Case #"<<t<<": O won"<<endl;return;}
	for(int i=1;i<=4;i++)//检测完成，若没有达成要求，就只有没结束或平局两种情况 
	{
		for(int j=1;j<=4;j++)
		{
			if(p[i][j]=='.')//若出现空格则肯定是没有结束 
			{
				cout<<"Case #"<<t<<": Game has not completed"<<endl;
				return;
			}
		}
	}
	cout<<"Case #"<<t<<": Draw"<<endl;//排除所有情况就一定平局 
	return;
}
int main()
{
	int T;
	cin>>T;
	for(t=1;t<=T;t++)
	{
		solve();
	}
	return 0;//好习惯 
}
```

---

## 作者：gaoyangyang (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P13281) 

[前往我的博客观看可能会更方便食用](https://www.luogu.com.cn/article/hrotml9f)

拿到一道新题，我们还是需要秉持一个原则“先看懂题，再去做题”。

所以我们的第一步就是深度的了解题目，提取关键词，讲文字语言转化成编程语言。

## 理解题意
当我们再重读一遍题目后可以发现如下要点：

- 我们需要在 $4 \times 4$ 的棋盘中找到一行（或一列，对角线）是同一种“棋子”（包括 ```'T'```）。
- 输入中有且仅有 ```'X'```,```'O'```,```'T'```,```'.'```四种。
- 最后输出有且仅有 X 胜利，O 胜利，平局和游戏尚未结束，从这里可以发现玩家 X 和玩家 O 其实是等价的，只需要判断好其中一个，复制即可。
- 题目中明确标注 **“注意”** 即使游戏结局已经可以明确预见，只要棋盘中存在空格且游戏尚未实际结束，都必须输出 ```"Game has not completed"```（因为其重要性，所以这句话照抄）

到现在审题要点基本是看完了，因为如果你注意到你是因为审题问题而没有AC，现在不要往下翻，可以去修改代码了。

## 解题结构

细细的读完题目就需要开始解题了，解题我们应当由“宏观”到“微观”，即从代码框架入手，再补全细节。

经过审题，我们可以清晰的得到如下三步：

1. 变量初始化，输入。
2. 分析处理，判断结果属于哪种情况。
3. 依照判断结果输出。

显然第二步是我们的重点，对于这类“全称量”条件（即比如一行 **全** 是同类字符）我给出如下 **建议**(仅供参考)。

```cpp
bool flag;//定义一个变量描述是否成立
flag=0;   //初始化，赋值为1也是可行的
for (int i;;)
{
    ......
}         //相关的判断以及处理，修改（或不修改）flag的值

//此时我们根据flag的值相应的输出（进行下一步操作）即可
if (flag)
{
    ......
{
```

我们可以想到分别判断行，列，对角线，用判断结果影响最终状态，以此得借，依照此思路，我们回归题目。

对于行的判断，只需要保证：存在一个 $i$ 使得任意 $j$ 的 $(i,j)$ 均相等。

而对于列的判断，与行相似，只需要保证：存在一个 $j$ 使得任意 $i$ 的 $(i,j)$ 均相等。

由于两者过于相似，所以可以一起判断（分开也不会错），参考代码如下。

```
for (int i=1;i<=4;i++)
{	
    lx=lo=hx=ho=1;//初始化行与列的状态变量
    for (int j=1;j<=4;j++)
    {
	if (_map[i][j]!='X' and _map[i][j]!='T')hx=0;
	if (_map[i][j]!='O' and _map[i][j]!='T')ho=0;
	if (_map[j][i]!='X' and _map[j][i]!='T')lx=0;
	if (_map[j][i]!='O' and _map[j][i]!='T')lo=0;	
	//相关处理

	if (hx==1 or lx==1)//更改关于X的最终状态
	{
	    fx=1;break;
	}
	if (ho==1 or lo==1)//更改关于O的最终状态
	{
	    fo=1;break;
	}
    }
}
```

对于由左上到右下对角线的情况，我们不难发现只需要判断是否所有的 $(i,i)$ 均相等（通俗的讲）。

相似的，对于由右上到左下对角线的情况也就是判断是否所有的 $(i,4-i+1)$ 均相等。

参考代码如下：


```cpp
for (int i=1;i<=4;i++)
{
    if (_map[i][i]!='X' and _map[i][i]!='T' )zx=0;
    if (_map[i][i]!='O' and _map[i][i]!='T' )zo=0;
    if (_map[i][4-i+1]!='X' and _map[i][4-i+1]!='T' )yx=0;
    if (_map[i][4-i+1]!='O' and _map[i][4-i+1]!='T' )yo=0;		
}//此处初始化与对于最终状态的影响与前面行列过于相似，所以省略	
```

最后如果判断下来 $X$ 与 $O$ 均没有赢，判断棋盘中是否还有空位，相应的进行输出即可。

参考代码展示：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n;
bool fx,fo,d;
bool hx,ho,zx,zo,yx,yo,lx,lo;
char _map[5][5];
int main()
{
	cin>>n;
	for (int T=1;T<=n;T++)
	{
		fx=fo=d=0;
		hx=ho=zx=zo=yx=yo=lx=lo=1;
		for (int i=1;i<=4;i++)
		{
			for (int j=1;j<=4;j++)
			{
				cin>>_map[i][j];
				if (_map[i][j]=='.')d=1;//判断是否有空位 
			}
		}
		for (int i=1;i<=4;i++)//对角线 
		{
			if (_map[i][i]!='X' and _map[i][i]!='T' )zx=0;
			if (_map[i][i]!='O' and _map[i][i]!='T' )zo=0;
			if (_map[i][4-i+1]!='X' and _map[i][4-i+1]!='T' )yx=0;
			if (_map[i][4-i+1]!='O' and _map[i][4-i+1]!='T' )yo=0;		
		}		
		for (int i=1;i<=4;i++)//行与列 
		{	
			lx=lo=hx=ho=1;
			for (int j=1;j<=4;j++)
			{
				if (_map[i][j]!='X' and _map[i][j]!='T')hx=0;
				if (_map[i][j]!='O' and _map[i][j]!='T')ho=0;
				if (_map[j][i]!='X' and _map[j][i]!='T')lx=0;
				if (_map[j][i]!='O' and _map[j][i]!='T')lo=0;	
			}
			if (hx==1 or lx==1)
			{
				fx=1;break;
			}
			if (ho==1 or lo==1)
			{
				fo=1;break;
			}
		}
		
		if (hx==1 or lx==1 or zx==1 or yx==1)//最后的判断 
			fx=1;
		if (ho==1 or lo==1 or zo==1 or yo==1)
			fo=1;
			
		if (fx==1)//输出 
			printf("Case #%d: X won\n",T);
		else if (fo==1)
			printf("Case #%d: O won\n",T);
		else if (fx==0 and fo==0 and d==0)
			printf("Case #%d: Draw\n",T);
		else
			printf("Case #%d: Game has not completed\n",T);
	}
	return 0;
}
```

谢谢观看，如果有帮助到你，请留下一个赞吧~

---

## 作者：qkj_qwq (赞：3)

## 解题思路
模拟。

首先想结果：
- 若 X 和 O 都获胜，或者 X 和 O 都没获胜且棋盘满了时，平手，输出 `Draw`；
- 若 X 和 O 有一方获胜，输出 `X won` 或 `O won`；
- 否则，棋盘还未结束，输出 `Game has not completed`。

接着只需要判断获胜即可。若该行（列或对角线）中有连续的 $4$ 个玩家自己的符号，或者该行（列或对角线）中有连续的 $3$ 个玩家自己的符号和一个 `T` 符号，则该玩家获胜。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char c[10][10];
bool pd(char cc)
{
	for(int i=1;i<=4;i++)
	{
		bool f=1,ff=1;
		for(int j=1;j<=4;j++)
		{
			if(c[i][j]!=cc&&c[i][j]!='T')f=0;
			if(c[j][i]!=cc&&c[j][i]!='T')ff=0;
		}
		if(f||ff)return 1;
	}
	bool f=1,ff=1;
	for(int j=1;j<=4;j++)
	{
		if(c[j][j]!=cc&&c[j][j]!='T')f=0;
		if(c[5-j][j]!=cc&&c[5-j][j]!='T')ff=0;
	}
	return f||ff;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++)
	{
		cout<<"Case #"<<tt<<": ";
		bool f=1;
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++)
			{
				cin>>c[i][j];
				if(c[i][j]=='.')f=0;
			}
		bool x=pd('X');
		bool o=pd('O');
		if(x&&o||f&&!x&&!o)cout<<"Draw\n";
		else if(x)cout<<"X won\n";
		else if(o)cout<<"O won\n";
		else cout<<"Game has not completed\n";
	}
	return 0;
}
```

---

## 作者：shentianxing (赞：2)

检查每行每列和对角线。如果有四个 `X` 或 `O` 一行，就输出谁赢了就行。对于 `T`，因为它可以是 `X` 也可以是 `O`，所以给 `X` 和 `O` 的数量都加上 $1$。

中途统计 `.` 的数量。最后如果没有胜负，有 `.` 就是游戏未完成，没 `.` 就是平局。

注意输出中间是英文冒号加空格，而不是一个中文冒号。

具体看代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

signed main(){
	int t;cin>>t;
	for(int q=1;q<=t;q++){
		string a[4];
		for(int i=0;i<4;i++){
			cin>>a[i];
		}
		bool f=0;int X=0,O=0;
		for(int i=0;i<4;i++){
			int x=0;int o=0;
			for(int j=0;j<4;j++){
				if(a[i][j]=='X') x++;
				if(a[i][j]=='O') o++;
				if(a[i][j]=='.') f=1;
				if(a[i][j]=='T'){
					x++;o++;
				}
			}
			X=max(X,x);O=max(O,o); 
		}
		for(int i=0;i<4;i++){
			int x=0;int o=0;
			for(int j=0;j<4;j++){
				if(a[j][i]=='X') x++;
				if(a[j][i]=='O') o++;
				if(a[j][i]=='.') f=1;
				if(a[j][i]=='T'){
					x++;o++;
				}
			}
			X=max(X,x);O=max(O,o); 
		}
		int x=0,o=0;
		for(int i=0;i<4;i++){
			if(a[i][i]=='X') x++;
			if(a[i][i]=='O') o++;
			if(a[i][i]=='.') f=1;
			if(a[i][i]=='T'){
				x++;o++;
			}
		}
		X=max(X,x);O=max(O,o);
		x=0,o=0;
		for(int i=0;i<4;i++){
			if(a[i][3-i]=='X') x++;
			if(a[i][3-i]=='O') o++;
			if(a[i][3-i]=='.') f=1;
			if(a[i][3-i]=='T'){
				x++;o++;
			}
		}
		X=max(X,x);O=max(O,o);
		if(X==4){
			cout<<"Case #"<<q<<": X won"<<endl;
			continue; 
		}
		if(O==4){
			cout<<"Case #"<<q<<": O won"<<endl;
			continue; 
		}
		if(f){
			cout<<"Case #"<<q<<": Game has not completed"<<endl;
			continue; 
		}
		cout<<"Case #"<<q<<": Draw"<<endl;
	} 
	return 0;
}
```

---

## 作者：__F__ (赞：2)

## 题目大意  
这道题说白了就是在一个 $4\times 4$ 的方形棋盘上下四子棋，谁先把四个子连成一条线谁就胜利。符号`T`可以理解为一个万能符号，既可以作为`X`，帮`X`连成一条线；也可以作为`O`，帮`O`连成一条线。最后判断不同的游戏状态，根据题意输出即可。  
## 思路分析  
根据题意模拟即可。直接暴力判断所有行、列和对角线的字符组成情况，如果某一行、某一列或某一条对角线有 $4$ 个相同的字符或有三个相同的字符和一个`T`,那么游戏就是已经分出胜负的状态。如果所有行、列、对角线都没有能连成一条线的字符，判断棋盘还有无空格。如果有空格，说明游戏尚未结束；如果没有空格，说明游戏结束，二人平局。  
## [AC](https://www.luogu.com.cn/record/224340824) code  
~~代码有些抽象，不喜勿喷~~  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
char a[10][10];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	for(int t=1;t<=T;t++){
		bool o=0,x=0;//o和x分别存储双方的输赢状态，0为输，1为赢 
		bool f=1;//f判断棋盘是否下满，1为下满，0为未下满 
		for(int i=1;i<=4;i++){
			for(int j=1;j<=4;j++){
				cin>>a[i][j];
				if(a[i][j]=='.'){//如果棋盘上还有空格 
					f=0;//说明棋盘未下满 
				}
			}
		}
		for(int i=1;i<=4;i++){//横着查找 
			if(a[i][1]=='X'||a[i][1]=='T'){
				if((a[i][2]=='T'||a[i][2]=='X')&&(a[i][3]=='T'||a[i][3]=='X')&&(a[i][4]=='T'||a[i][4]=='X')){
					x=1;
					break;
				}
			}if(a[i][1]=='O'||a[i][1]=='T'){
				if((a[i][2]=='T'||a[i][2]=='O')&&(a[i][3]=='T'||a[i][3]=='O')&&(a[i][4]=='T'||a[i][4]=='O')){
					o=1;
					break;
				}
			}
		}
		for(int j=1;j<=4;j++){//竖着查找 
			if(a[1][j]=='X'||a[1][j]=='T'){
				if((a[2][j]=='T'||a[2][j]=='X')&&(a[3][j]=='T'||a[3][j]=='X')&&(a[4][j]=='T'||a[4][j]=='X')){
					x=1;
					break;
				}
			}if(a[1][j]=='O'||a[1][j]=='T'){
				if((a[2][j]=='T'||a[2][j]=='O')&&(a[3][j]=='T'||a[3][j]=='O')&&(a[4][j]=='T'||a[4][j]=='O')){
					o=1;
					break;
				}
			}
		}
		if(a[1][1]=='X'||a[1][1]=='T'){//斜着查找 
			if((a[2][2]=='X'||a[2][2]=='T')&&(a[3][3]=='X'||a[3][3]=='T')&&(a[4][4]=='X'||a[4][4]=='T')) {
				x=1;
			}
		}if(a[1][1]=='O'||a[1][1]=='T'){
			if((a[2][2]=='O'||a[2][2]=='T')&&(a[3][3]=='O'||a[3][3]=='T')&&(a[4][4]=='O'||a[4][4]=='T')) {
				o=1;
			}
		}
		
		if(a[1][4]=='X'||a[1][4]=='T'){
			if((a[2][3]=='X'||a[2][3]=='T')&&(a[3][2]=='X'||a[3][2]=='T')&&(a[4][1]=='X'||a[4][1]=='T')){
				x=1;
			}
		}if(a[1][4]=='O'||a[1][4]=='T'){
			if((a[2][3]=='O'||a[2][3]=='T')&&(a[3][2]=='O'||a[3][2]=='T')&&(a[4][1]=='O'||a[4][1]=='T')){
				o=1;
			}
		}
		if(x==1) cout<<"Case #"<<t<<": X won"<<"\n";//x胜利 
		else if(o==1) cout<<"Case #"<<t<<": O won"<<"\n";//o胜利 
		else if(x==0&&o==0&&f==1) cout<<"Case #"<<t<<": Draw"<<"\n";//棋盘上无空格，游戏结束，平局 
		else if(x==0&&o==0&&f==0) cout<<"Case #"<<t<<": Game has not completed"<<"\n";//棋盘上还有空格，游戏未结束  
	}	
	return 0;
}

```

---

## 作者：mairuisheng (赞：1)

- 题目链接：[P13281 [GCJ 2013 Qualification] Tic-Tac-Toe-Tomek](https://www.luogu.com.cn/problem/P13281)。

- 主要算法：模拟。

- 分析：

以下是模拟过程（按顺序执行）：

①判断每一行、每一列和两条对角线上有几个 `X` 或 `T`，只要其中有一行或一列或一条对角线上有 $4$ 个 `X` 或 `T`，那么游戏已结束，X 胜利。

②判断每一行、每一列和两条对角线上有几个 `O` 或 `T`，只要其中有一行或一列或一条对角线上有 $4$ 个 `O` 或 `T`，那么游戏已结束，O 胜利。

③如果棋盘上还有 `.`，那么游戏尚未结束。

④否则游戏结束，平局。

- 参考代码：

```cpp
//Author: mairuisheng
//#pragma GCC optimize(3)
#include<cstdio>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char s;
	s=getchar();
	while(s<48||s>57)
	{
		if(s=='-')f=-f;
		s=getchar();
	}
	while(s>47&&s<58)
	{
		x=(x<<3)+(x<<1)+s-48;
		s=getchar();
	}
	return x*f;
}
int main()
{
	int T,n,i,j,cnt;
	char a[4][4];
	T=read();
	for(n=1;n<=T;++n)
	{
		printf("Case #%d: ",n);
		scanf("%s",a[0]);
		scanf("%s",a[1]);
		scanf("%s",a[2]);
		scanf("%s",a[3]);
		//判断玩家 X 是否有一列满足要求 
		for(i=0;i<4;++i)
		{
			cnt=0;
			if(a[i][0]=='X'||a[i][0]=='T')++cnt;
			if(a[i][1]=='X'||a[i][1]=='T')++cnt;
			if(a[i][2]=='X'||a[i][2]=='T')++cnt;
			if(a[i][3]=='X'||a[i][3]=='T')++cnt;
			if(cnt==4)
			{
				puts("X won");
				goto nxt;
			}
		}
		//判断玩家 X 是否有一行满足要求 
		for(i=0;i<4;++i)
		{
			cnt=0;
			if(a[0][i]=='X'||a[0][i]=='T')++cnt;
			if(a[1][i]=='X'||a[1][i]=='T')++cnt;
			if(a[2][i]=='X'||a[2][i]=='T')++cnt;
			if(a[3][i]=='X'||a[3][i]=='T')++cnt;
			if(cnt==4)
			{
				puts("X won");
				goto nxt;
			}
		}
		//判断玩家 X 是否有对角线满足要求 
		cnt=0;
		for(i=0;i<4;++i)
		{
			if(a[i][i]=='X'||a[i][i]=='T')++cnt;
		}
		if(cnt==4)
		{
			puts("X won");
			continue;
		}
		cnt=0;
		for(i=0;i<4;++i)
		{
			if(a[i][4-i-1]=='X'||a[i][4-i-1]=='T')++cnt;
		}
		if(cnt==4)
		{
			puts("X won");
			continue;
		}
		//判断玩家 O 是否有一列满足要求。 
		for(i=0;i<4;++i)
		{
			cnt=0;
			if(a[i][0]=='O'||a[i][0]=='T')++cnt;
			if(a[i][1]=='O'||a[i][1]=='T')++cnt;
			if(a[i][2]=='O'||a[i][2]=='T')++cnt;
			if(a[i][3]=='O'||a[i][3]=='T')++cnt;
			if(cnt==4)
			{
				puts("O won");
				goto nxt;//转去代码倒数第四行的 nxt，即 continue。 
			}
		}
		//判断玩家 0 是否有一行满足要求。 
		for(i=0;i<4;++i)
		{
			cnt=0;
			if(a[0][i]=='O'||a[0][i]=='T')++cnt;
			if(a[1][i]=='O'||a[1][i]=='T')++cnt;
			if(a[2][i]=='O'||a[2][i]=='T')++cnt;
			if(a[3][i]=='O'||a[3][i]=='T')++cnt;
			if(cnt==4)
			{
				puts("O won");
				goto nxt;
			}
		}
		//判断玩家 O 是否有对角线满足要求。 
		cnt=0;
		for(i=0;i<4;++i)
		{
			if(a[i][i]=='O'||a[i][i]=='T')++cnt;
		}
		if(cnt==4)
		{
			puts("O won");
			continue;
		}
		cnt=0;
		for(i=0;i<4;++i)
		{
			if(a[i][4-i-1]=='O'||a[i][4-i-1]=='T')++cnt;
		}
		if(cnt==4)
		{
			puts("O won");
			continue;
		}
		//判断游戏是否结束。 
		for(i=0;i<4;++i)
		{
			for(j=0;j<4;++j)
			{
				if(a[i][j]=='.')
				{
					puts("Game has not completed");
					goto nxt;
				}
			}
		}
		//否则是平局。 
        puts("Draw");
		nxt:continue;
	}
	return 0;
}
```

---

## 作者：shaoxqy (赞：1)

## 读题
~~显而易见，这是一篇模拟。~~

题目想让我们判断 $4*4$ 棋盘的状态，并且输出我们判断。其中，执 `X` 方或执 `O` 方的棋子4个连成一条线（斜着也行）就为胜利，否则为平局或未完成。
## 思路
开一个三维 `bool` 数组 `place[7][7][7]` ，用于记录各个棋子的位置。第一个下标表示 `X` 方棋子或 `O` 方棋子，第二三个下标则用于记录该棋子的坐标。

简单来说，就是将棋盘分为仅有 `X` 棋子（简称 `X` 棋盘）与仅有 `O` 棋子（简称 `O` 棋盘）的两半（ `T` 棋子在 `X` 棋盘视为 `X` 棋子，在 `O` 棋盘视为`O`棋子）。

然后，分别判断 `X` 棋盘与 `O` 棋盘是否达成胜利条件。
## 代码实现
首先，先输入棋盘（这时已经可以直接分成 `X` 棋盘和 `O` 棋盘了）。

```cpp
			if(a!='.'){
				if(a=='T'){//特别留意T棋子
					place[1][i][j]=true;
					place[2][i][j]=true;
				}
				place[f(a)][i][j]=true;//f(a)是分X棋盘和O棋盘的步骤
				n++;
			}
```
然后判断各个棋盘的每一行，每一列，以及两个对角线是否达成胜利条件。

```cpp
int search(int x){
	for(int i=1;i<=4;i++){
		if(place[x][i][1]&&place[x][i][2]&&place[x][i][3]&&place[x][i][4]){
			return x;
		}
	}
	for(int j=1;j<=4;j++){
		if(place[x][1][j]&&place[x][2][j]&&place[x][3][j]&&place[x][4][j]){
			return x;
		}
	}
	if(place[x][1][1]&&place[x][2][2]&&place[x][3][3]&&place[x][4][4]){
		return x;
	}
	if(place[x][4][1]&&place[x][3][2]&&place[x][2][3]&&place[x][1][4]){
		return x;
	}
	return 0;
}
```
判断完后，就可以输出啦~

但是，我们还要判断未完成与平局的区别，这好办，我们可以在输入时使用变量 `n` 来记录棋子的数量，若 `n==16` 则棋盘已满，为平局；否则为未完成。
## 代码
附上我的代码~

```cpp
#include<iostream>
using namespace std;

bool place[7][7][7];
int n=0;

int f(char x){
	if(x=='.'){
		return 0;
	}
	if(x=='X'){
		return 1;
	}
	if(x=='O'){
		return 2;
	}
	return 3;
}

void _clear(){
	n=0;
	for(int x=1;x<=2;x++){
		for(int y=1;y<=4;y++){
			for(int z=1;z<=4;z++){
				place[x][y][z]=false;
			}
		}
	}
}

void in(){
	char a;
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			cin>>a;
			if(a!='.'){
				if(a=='T'){
					place[1][i][j]=true;
					place[2][i][j]=true;
				}
				place[f(a)][i][j]=true;
				n++;
			}	
		}
	}
}

int search(int x){
	for(int i=1;i<=4;i++){
		if(place[x][i][1]&&place[x][i][2]&&place[x][i][3]&&place[x][i][4]){
			return x;
		}
	}
	for(int j=1;j<=4;j++){
		if(place[x][1][j]&&place[x][2][j]&&place[x][3][j]&&place[x][4][j]){
			return x;
		}
	}
	if(place[x][1][1]&&place[x][2][2]&&place[x][3][3]&&place[x][4][4]){
		return x;
	}
	if(place[x][4][1]&&place[x][3][2]&&place[x][2][3]&&place[x][1][4]){
		return x;
	}
	return 0;
}

int main(){
	int T,t=1;
	cin>>T;
	while(t<=T){
		_clear();
		in();
		if(search(1)){
			cout<<"Case #"<<t<<": X won"<<endl;
		}
		if(search(2)){
			cout<<"Case #"<<t<<": O won"<<endl;
		}
		if((!search(1))&&(!search(2))){
			if(n==16){
				cout<<"Case #"<<t<<": Draw"<<endl;
			}
			else{
				cout<<"Case #"<<t<<": Game has not completed"<<endl;
			}
		}
		t++;
	}
	return 0;
} 
```
## 注意事项
每个编号输入前要记得清空 `place` 和 `n` 。

---

## 作者：huhengrui2013 (赞：1)

### 题解：P13281 [GCJ 2013 Qualification] Tic-Tac-Toe-Tomek

[传送门](https://www.luogu.com.cn/problem/P13281)

### 思路：

纯模拟，枚举每行每列与每条对角线判断是否存在连续四个相同字符或三个相同字符和一个万能字符（即 T ）即可。

### AC Code:
```cpp

#include<bits/stdc++.h>

using namespace std;

int t;
char a[6][6];
bool check(char x){
    //枚举每行＋判断
    for(int i=1;i<=4;i++)
        if(a[i][1]==x||(a[i][1]=='T'&&a[i][2]==x))
            if(a[i][2]==x||a[i][2]=='T')
                if(a[i][3]==x||a[i][3]=='T')
                    if(a[i][4]==x||a[i][4]=='T') return 1;
    //枚举每列＋判断
    for(int i=1;i<=4;i++)
        if(a[1][i]==x||(a[1][i]=='T'&&a[2][i]==x))
            if(a[2][i]==x||a[2][i]=='T')
                if(a[3][i]==x||a[3][i]=='T')
                    if(a[4][i]==x||a[4][i]=='T') return 1;
    //枚举每条对角线＋判断
    if(a[1][1]==x||(a[1][1]=='T'&&a[2][2]==x))
        if(a[2][2]==x||a[2][2]=='T')
            if(a[3][3]==x||a[3][3]=='T')
                if(a[4][4]==x||a[4][4]=='T') return 1;
    if(a[1][4]==x||(a[1][4]=='T'&&a[2][3]==x))
        if(a[2][3]==x||a[2][3]=='T')
            if(a[3][2]==x||a[3][2]=='T')
                if(a[4][1]==x||a[4][1]=='T') return 1;
    return 0;
}
bool ck(){//判断是否已经下满 
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)
            if(a[i][j]=='.') return 0;
    return 1;
}
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cout<<"Case #"<<i<<": ";
        for(int i=1;i<=4;i++)
            for(int j=1;j<=4;j++) cin>>a[i][j];
        if(check('X')) cout<<"X won\n";
        else if(check('O')) cout<<"O won\n";
        else if(ck()) cout<<"Draw\n";
        else cout<<"Game has not completed\n";
    }
    
}
```

---

## 作者：qwq_Furry (赞：1)

## 题目简述
### 赢或者输
 - 下四子棋，有一颗棋子是 $T$，它可以表示为任何一方的棋子，任何一方都可以利用它。

 - 如果 $O$ 横着、竖着或者对角线有 $4$ 颗 $O$ 棋子或者是有 $3$ 颗 $O$ 棋子和 $1$ 颗 $T$ 棋子，那么 $O$ 获胜。

 - $T$ 也同理。

### 平局
 - 如果没有空白格子并且也没有分出胜负，那么就是平局。

### 没下完
 - 如果有空白格子并且没有分出胜负，那么没下完。

## 解题思路
### 第一步
 - 创建变量 $T$ 和 $pri$，$pri$ 代表当前测试数据编号（后面所有 $i$ 和 $j$ 分别为行数和列数，且初始值均为 $1$）。

### 第二步
 - 创建二维字符数组 $chess$，代表棋盘；整型变量 $ch$，用于记录空白格子的数量；布尔变量 $fl_1$，初始化为 flase，代表是否找到了答案。

 - 在输入 $chess_{i,j}$ 的时候顺便判断该格子是否为空白格子，如果是，那么让 $ch$ 加上 $1$。

### 第三步
- 创建变量 $o, x, t$，分别表示为 $o, x, t$ 的棋子数量。

- 进入循环后，先判断横着的四格，将会有以下 $3$ 种情况：

  - $chess_{i,j} = O$，那么将 $o$ 加上 $1$。

  - $chess_{i,j} = X$，那么将 $x$ 加上 $1$。
 
  - $chess_{i,j} = T$，那么将 $t$ 加上 $1$。
 
- 然后再判断是否有赢的情况，有以下 $2$ 种情况：

  - 如果 $o = 4$ 或者 $o + t = 4$，那么输出答案，并将 $pri$ 加上 $1$，$fl_1$ 设为 true。

  - 如果 $x = 4$ 或者 $x + t = 4$，那么输出答案，并将 $pri$ 加上 $1$，$fl_1$ 设为 true。
 
 - 最后把每个变量设置为 $0$。并判断 $fl_1$，有以下 $2$ 种情况：

   - 如果是 true，那么直接跳过一次关于 $T$ 的循环，进入下一个测试样例。

   - 如果是 false，那么不用管他。
  
### 第三步 及 第四步
 - 第三步判断竖着的，思路与上面相同，只是将 $chess_{i,j}$ 改为 $chess_{j,i}$ 去判断就行。

 - 第四步判断对角线，思路与上面也相同，但是有 $2$ 种情况：

   - 从左上角到右下角，判断条件加上 $i = j$，如果成立，就继判断，如果不成立，就不管。
  
   - 从右上角到左下角，判断条件加上 $i + j = 5$，如果成立，就继判断，如果不成立，就不管。
  
### 第五步
 - 判断是否为平局：

   - 如果 $ch = 0$ 并且 $fl_1 = false$，就是没有空白格子并且也没有决出胜负，输出平局，并且让 $pri$ 加上 $1$即可。
  
- 判断是否为没下完：

  - 如果 $ch > 0$ 并且 $fl_1 = false$，就是有空白格子并且没有决出胜负，那么输出没下完，并且让 $pri$ 加上 $1$即可。

## 时间复杂度及空间复杂度分析
按照此思路来写，时间复杂度是 $O(T)$，题目限制是 $1 \le T \le 1000$，可以通过此题目。

空间复杂度是 $O(1)$，题目限制是 $1$ GB，可以通过此题目。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int T, pri = 1; cin >>T;
    while(T--) {
        char chess[10][10];
        int ch = 0; //ch用来检测有几个空白格子
        for(int i = 1; i <= 4; i++) {
            for(int j = 1; j <= 4; j++) {
                cin >>chess[i][j];
                if(chess[i][j] == '.') ch++;
            }
        }
        //先开始横着找
        int o = 0, x = 0, t = 0;
        bool fl1 = false; //如果fl1变为true，那就是已经有了答案了，直接跳到下一次while循环里面
        for(int i = 1; i <= 4; i++) {
            if(fl1) break;
            for(int j = 1; j <= 4; j++) {
                if(chess[i][j] == 'O') o++;
                if(chess[i][j] == 'X') x++;
                if(chess[i][j] == 'T') t++;
            }
            if(o + t == 4 || o == 4) {
                cout <<"Case #" <<pri++ <<": O won \n";
                fl1 = true;
            }
            else if(x + t == 4 || x == 4) {
                cout <<"Case #" <<pri++ <<": X won \n";
                fl1 = true;
            }
            o = 0, x = 0, t = 0;
        }
        if(fl1) continue;
        fl1 = false; //这里就是普通地维护一下fl1，没什么实际作用
        o = 0, t = 0, x = 0;
        //然后开始竖着找
        for(int i = 1; i <= 4; i++) {
            if(fl1) break;
            for(int j = 1; j <= 4; j++) {
                if(chess[j][i] == 'O') o++;
                if(chess[j][i] == 'X') x++;
                if(chess[j][i] == 'T') t++;
            }
            if(o + t == 4 || o == 4) {
                cout <<"Case #" <<pri++ <<": O won \n";
                fl1 = true;
            }
            else if(x + t == 4 || x == 4) {
                cout <<"Case #" <<pri++ <<": X won \n";
                fl1 = true;
            }
            o = 0, x = 0, t = 0;
        }
        if(fl1) continue;
        fl1 = false;
        x = 0, o = 0, t = 0;
        //最后找对角线的
        //从左上到右下
        for(int i = 1; i <= 4; i++) {
            if(fl1) break;
            for(int j = 1; j <= 4; j++) {
                if(i == j) { //不想写一起，因为写一起太多了，所以拆开来判断是否i == j
                    if(chess[i][j] == 'O') o++;
                    if(chess[i][j] == 'X') x++;
                    if(chess[i][j] == 'T') t++;
                }
            }
            if(o + t == 4 || o == 4) {
                cout <<"Case #" <<pri++ <<": O won \n";
                fl1 = true;
            }
            else if(x + t == 4 || x == 4) {
                cout <<"Case #" <<pri++ <<": X won \n";
                fl1 = true;
            }
        }
        if(fl1) continue;
        fl1 = false;
        o = 0, x = 0, t = 0;
        //从右上到右下
        for(int i = 1; i <= 4; i++) {
            if(fl1) break;
            for(int j = 1; j <= 4; j++) {
                if(i + j == 5) {
                    if(chess[i][j] == 'O') o++;
                    if(chess[i][j] == 'X') x++;
                    if(chess[i][j] == 'T') t++;
                }
            }
            if(o + t == 4 || o == 4) {
                cout <<"Case #" <<pri++ <<": O won \n";
                fl1 = true;
            }
            else if(x + t == 4 || x == 4) {
                cout <<"Case #" <<pri++ <<": X won \n";
                fl1 = true;
            }
        }
        //开始找平局
        if(ch == 0 && fl1 == false) {
            cout <<"Case #" <<pri++ <<": Draw \n";
        }
        else if(ch > 0 && fl1 == false) {
            cout <<"Case #" <<pri++ <<": Game has not completed \n";
        }
    }
    return 0;
}
```

---

## 作者：yangdezuo (赞：0)

## 解析
### 题目大意
判断这场比赛的目前情况，谁赢、未结束或者平局

### 方法
这显然是一道模拟题，**要注意字符串的输入。**

首先不管有没有 `T`，对每行每列进行判断，如果有四个 `X`，则 X 获胜，如果有四个 `O`，则 O 获胜，对角线同理。

如果此时没有任何人获胜，考虑字符 `T`。对于每行每列，与上述条件相比，只需要三个相同字符且必须要有字符 `T`。如果没有又字符 `T`，需要判断棋盘是否被填满，若填满，则平局，反之游戏尚未结束。

具体详见下面代码。

**避雷：** 模拟时要注意对字符串的处理。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
using namespace std;
const int N=1e6+5;
int t,tx,ty,hang[5][3],lie[5][3];
bool f;//未结束 
string s[5];
int check(){
	// 0 平局 或 未结束
	// 1 X 
	// 2 O
	for(int i=1;i<=4;i++) 
		if(s[i]=="XXXX") return 1;
	for(int i=1;i<=4;i++) 
		if(s[i]=="OOOO") return 2;
	//行
	for(int i=1;i<=4;i++) 
		if(lie[i][1]==4) return 1;
	for(int i=1;i<=4;i++) 
		if(lie[i][2]==4) return 2;
	//列 
	if(s[1][0]=='X'&&s[2][1]=='X'&&s[3][2]=='X'&&s[4][3]=='X') return 1;
	if(s[1][0]=='O'&&s[2][1]=='O'&&s[3][2]=='O'&&s[4][3]=='O') return 2;
	if(s[1][3]=='X'&&s[2][2]=='X'&&s[3][1]=='X'&&s[4][0]=='X') return 1;
	if(s[1][3]=='O'&&s[2][2]=='O'&&s[3][1]=='O'&&s[4][0]=='O') return 2;
	//对角线
	if(tx==-1) return 0;
	for(int i=1;i<=4;i++) 
		if(hang[i][1]==3&&tx==i) return 1;
	for(int i=1;i<=4;i++) 
		if(hang[i][2]==3&&tx==i) return 2;
	//行
	for(int i=1;i<=4;i++) 
		if(lie[i][1]==3&&ty==i) return 1;
	for(int i=1;i<=4;i++) 
		if(lie[i][2]==3&&ty==i) return 2;
	//列 
	if(tx!=ty&&tx+ty!=5) return 0;
	int s1=0,s2=0;
	for(int i=1;i<=4;i++)
		if(s[i][i-1]=='X') s1++;
	if(s1==3&&tx==ty) return 1;
	s1=0;
	for(int i=1;i<=4;i++)
		if(s[i][4-i]=='X') s1++;
	if(s1==3&&tx+ty==5) return 1;
	for(int i=1;i<=4;i++)
		if(s[i][i-1]=='O') s2++;
	if(s2==3&&tx==ty) return 2;
	s2=0;
	for(int i=1;i<=4;i++)
		if(s[i][4-i]=='O') s2++;
	if(s2==3&&tx+ty==5) return 2;
	//含有 T 
	return 0;
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>t;
	for(int o=1;o<=t;o++){
		for(int i=1;i<=4;i++)
			cin>>s[i];
		tx=ty=-1;
		f=true;
		memset(hang,0,sizeof(hang));
		memset(lie,0,sizeof(lie));
		for(int i=1;i<=4;i++)
			for(int j=0;j<4;j++)
				if(s[i][j]=='T') tx=i,ty=j+1;
				else if(s[i][j]=='.') f=false;
				else if(s[i][j]=='X') hang[i][1]++,lie[j+1][1]++;
				else hang[i][2]++,lie[j+1][2]++;
		int p=check();
		if(p==1) cout<<"Case #"<<o<<": "<<"X won\n";
		else if(p==2) cout<<"Case #"<<o<<": "<<"O won\n";
		else if(f) cout<<"Case #"<<o<<": "<<"Draw\n";
		else cout<<"Case #"<<o<<": "<<"Game has not completed\n";
	}
}
```

---

## 作者：Luogu_916767 (赞：0)

### 题目大意

输入棋盘，判断是否有任意一方胜利。

### 思路分析

分别检查 `O` 和 `X` 是否胜利，检查时将 `T` 替换成对应符号。

检查很简单，枚举每种胜利的可能，检查就好，详见代码。

### Code

```cpp
#include<bits/stdc++.h>

using namespace std;

int t;
char a[5][5];

bool work(char ch){
    if (a[1][1] == ch && a[1][2] == ch && a[1][3] == ch && a[1][4] == ch) return true;
    if (a[2][1] == ch && a[2][2] == ch && a[2][3] == ch && a[2][4] == ch) return true;
    if (a[3][1] == ch && a[3][2] == ch && a[3][3] == ch && a[3][4] == ch) return true;
    if (a[4][1] == ch && a[4][2] == ch && a[4][3] == ch && a[4][4] == ch) return true;

    if (a[1][1] == ch && a[2][1] == ch && a[3][1] == ch && a[4][1] == ch) return true;
    if (a[1][2] == ch && a[2][2] == ch && a[3][2] == ch && a[4][2] == ch) return true;
    if (a[1][3] == ch && a[2][3] == ch && a[3][3] == ch && a[4][3] == ch) return true;
    if (a[1][4] == ch && a[2][4] == ch && a[3][4] == ch && a[4][4] == ch) return true;

    if (a[1][1] == ch && a[2][2] == ch && a[3][3] == ch && a[4][4] == ch) return true;
    if (a[1][4] == ch && a[2][3] == ch && a[3][2] == ch && a[4][1] == ch) return true;

    return false;
}

bool check(char ch){
    if(work(ch)) return true;
    for(int i = 1; i <= 4; i++){
        for(int j = 1; j <= 4; j++){
            if(a[i][j] == 'T'){
                a[i][j] = ch;
                bool res = work(ch);
                a[i][j] = 'T';
                if(res) return true;
            }
        }
    }
    return false;
}

int main(){
    cin>>t;
    for(int _ = 1; _ <= t; _ ++ ){
        cout<<"Case #"<<_<<": ";
        for(int i = 1; i <= 4; i ++ ){
            for(int j = 1; j <= 4; j ++ ){
                cin>>a[i][j];
            }
        }
        if(check('O')){
            cout<<"O won\n";
        }else if(check('X')){
            cout<<"X won\n";
        }else{
            bool flag = 0;
            for(int i = 1; i <= 4; i ++ ){
                for(int j = 1; j <= 4; j ++ ){
                    if(a[i][j] == '.'){
                        flag = 1;
                        cout<<"Game has not completed\n";
                    }
                    if(flag)break;
                }
                if(flag)break;
            }
            if(!flag)cout<<"Draw\n";
        }
    }
}
```

---

## 作者：IkillDream (赞：0)

# P13281 题解

## 思路

因为这题的数据很水，用暴力都能过所以我们只需要遍历所有行、列和对角线，并检查是否存在连续的 $4$ 个相同符号（$X$ 或 $O$）或者 $3$ 个相同符号加一个 $T$ 符号，最后判断以下就好了。

## [AC](https://www.luogu.com.cn/record/224564547) 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t,brd[5][5],x,o,tt;
    cin>>t;
    for(int kkk01=1;kkk01<=t;kkk01++){
        for(int i=0;i<4;i++)
        for(int j=0;j<4;j++){
            char c;
            cin>>c;
            if(c=='X')brd[i][j]=1;
            else if(c=='O')brd[i][j]=2;
            else if(c=='T')brd[i][j]=3;
            else brd[i][j]=0;
        }
        string ans="Draw";
        for(int i=0;i<4;i++){
            x=o=tt=0;
            for(int j=0;j<4;j++)
            if(brd[i][j]==1)x++;
            else if(brd[i][j]==2)o++;
            else if(brd[i][j]==3)tt++;
            if(x==4||(x==3&&tt==1))ans="X won";
            if(o==4||(o==3&&tt==1))ans="O won";
        }
        for(int j=0;j<4;j++){
            x=o=tt=0;
            for(int i=0;i<4;i++)
            if(brd[i][j]==1)x++;
            else if(brd[i][j]==2)o++;
            else if(brd[i][j]==3)tt++;
            if(x==4||(x==3&&tt==1))ans="X won";
            if(o==4||(o==3&&tt==1))ans="O won";
        }
        x=o=tt=0;
        for(int i=0;i<4;i++)
        if(brd[i][i]==1)x++;
        else if(brd[i][i]==2)o++;
        else if(brd[i][i]==3)tt++;
        if(x==4||(x==3&&tt==1))ans="X won";
        if(o==4||(o==3&&tt==1))ans="O won";
        x=o=tt=0;
        for(int i=0;i<4;i++)
        if(brd[i][3-i]==1)x++;
        else if(brd[i][3-i]==2)o++;
        else if(brd[i][3-i]==3)tt++;
        if(x==4||(x==3&&tt==1))ans="X won";
        if(o==4||(o==3&&tt==1))ans="O won";
        if(ans=="Draw")
        for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        if(brd[i][j]==0)ans="Game has not completed";
        cout<<"Case #"<<kkk01<<": "<<ans<<endl;
    }
    return 0;
}
```
最后我为了方便大家察看，让 deepseek 优化了一下格式，~~但我感觉根更难看了~~。

---

## 作者：YuTinMin (赞：0)

## 思路

四子棋，求谁赢（~~为什么不直接眼睛看，还要用代码~~），题目给出四种情况，分别是 O 赢，X 赢，平局和未结束。

前三种好弄，一个一个检查就可以了（~~四个循环，秒了~~）。斜边的实现，就是用两个 $i$，或者一个 $i$ 一个 $5 - i$ 的数组循环就行了，具体的去看代码。

未结束的要在检查前三种完之后，再来一个 `else` 判断有没有空余的，没有那就是平局，有就是没结束（~~没结束还让我判断~~）

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char g[10][10];

bool check(char c)
{
	//检查行 
	for(int i = 1;i <= 4;i++)
	{
		int cnt = 0, t = 0;
		for(int j = 1;j <= 4;j++)
		{
			if(g[i][j] == c) cnt++;
			else if(g[i][j] == 'T') t++;
		}
		if(cnt == 4 || (cnt == 3 && t == 1)) return true;
	}
	//检查列 
	for(int j = 1;j <= 4;j++)
	{
		int cnt = 0, t = 0;
		for(int i = 1;i <= 4;i++)
		{
			if(g[i][j] == c) cnt++;
			else if(g[i][j] == 'T') t++;
		}
		if(cnt == 4 || (cnt == 3 && t == 1)) return true;
	}
	//检查斜边 
	int cnt = 0, t = 0;
	for(int i = 1;i <= 4;i++)
	{
		if(g[i][i] == c) cnt++;
		else if(g[i][i] == 'T') t++;
	}
	if(cnt == 4 || (cnt == 3 && t == 1)) return true;
	
	cnt = 0, t = 0;
	for(int i = 1;i <= 4;i++)
	{
		if(g[i][5 - i] == c) cnt++;
		else if(g[i][5 - i] == 'T') t++;
	}
	if(cnt == 4 || (cnt == 3 && t == 1)) return true;
	
	//说明没有 
	return false;
}

int main()
{
	
	int t;
	cin >> t;
	for(int kkk = 1;kkk <= t;kkk++)
	{
		for(register int i = 1;i <= 4;i++)
			for(register int j = 1;j <= 4;j++)
				cin >> g[i][j];
		if(check('X'))
			printf("Case #%d: X won\n", kkk);
		else if(check('O'))
			printf("Case #%d: O won\n", kkk);	
		else
		{
			bool flag = false;
			for(int i = 1;i <= 4;i++)
			{
				for(int j = 1;j <= 4;j++)
					if(g[i][j] == '.') flag = true;
			}
			if(flag) printf("Case #%d: Game has not completed\n", kkk);
			else printf("Case #%d: Draw\n", kkk);
		}
	}
	
	return 0;
}
```

---

## 作者：Natural_Selection (赞：0)

# 题解：[P13281](https://www.luogu.com.cn/problem/P13281)

## 思路

很简单的一道题，我们只需模拟行、列和对角线的状态，然后输出即可。对于特殊的两种情况：

+ `"Draw"`：场上已经没有多余的 `.` 且无法判断输赢。
+ `"Game has not completed"`：场上还有多余的 `.` 且无法判断输赢。

接下来就是——

## [AC](https://www.luogu.com.cn/record/224488271) Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int k;
int main(){
    cin>>t;
    while(t--){
        bool ch=0;
        int kong=0;
        char a[5][5];
        for(int i=0;i<4;i++){cin>>a[i]; for(int j=0;j<4;j++) if(a[i][j]=='.') kong++;}
        printf("Case #%d: ",++k);
        for(int i=0;i<4;i++){
            int cntx=0,cnto=0,cntt=0;
            for(int j=0;j<4;j++){
                if(a[i][j]=='X') cntx++;
                if(a[i][j]=='O') cnto++;
                if(a[i][j]=='T') cntt++;
            }
            if((cntx==4||cntx+cntt==4&&cntt==1)&&!ch){
                cout<<"X won\n";
                ch=1;
                break;
            }else if((cnto==4||cnto+cntt==4&&cntt==1)&&!ch){
                cout<<"O won\n";
                ch=1;
                break;
            }
        }
        for(int i=0;i<4;i++){
            int cntx=0,cnto=0,cntt=0;
            for(int j=0;j<4;j++){
                if(a[j][i]=='X') cntx++;
                if(a[j][i]=='O') cnto++;
                if(a[j][i]=='T') cntt++;
            }
            if((cntx==4||cntx+cntt==4&&cntt==1)&&!ch){
                cout<<"X won\n";
                ch=1;
                break;
            }else if((cnto==4||cnto+cntt==4&&cntt==1)&&!ch){
                cout<<"O won\n";
                ch=1;
                break;
            }
        }
        int cntx=0,cnto=0,cntt=0;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(i==j){
                    if(a[i][j]=='X') cntx++;
                    if(a[i][j]=='O') cnto++;
                    if(a[i][j]=='T') cntt++;
                }
            }
        }
        if((cntx==4||cntx+cntt==4&&cntt==1)&&!ch){
            cout<<"X won\n";
            ch=1;
        }else if((cnto==4||cnto+cntt==4&&cntt==1)&&!ch){
            cout<<"O won\n";
            ch=1;
        }
        cntx=0,cnto=0,cntt=0;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(i+j==3){
                    if(a[i][j]=='X') cntx++;
                    if(a[i][j]=='O') cnto++;
                    if(a[i][j]=='T') cntt++;
                }
            }
        }
        if((cntx==4||cntx+cntt==4&&cntt==1)&&!ch){
            cout<<"X won\n";
            ch=1;
        }else if((cnto==4||cnto+cntt==4&&cntt==1)&&!ch){
            cout<<"O won\n";
            ch=1;
        }
        if(!ch){
            if(kong==0){
                cout<<"Draw\n";
            }else{
                cout<<"Game has not completed\n";
            }
        }
    }
    return 0;
}
```
蒟蒻代码，较长轻喷。

---

## 作者：ziyaojia (赞：0)

## P13281 [GCJ 2013 Qualification] Tic-Tac-Toe-Tomek

这道题是一道简单的模拟题，我们要注意的就是 T 在行列或对角线中只能用一次，所以我们可以用两个变量分别存储 T 和 X 或 O 的数量，最后判断是否连成了一条线就好了。

### [AC](https://www.luogu.com.cn/record/224471458) Code：


```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n=4;
char a[5][5];
bool check(char x){
    for(int i=1;i<=n;i++){
        int cnt=0,t=0;
        for(int j=1;j<=n;j++){
            if(a[i][j]==x)cnt++;
            if(a[i][j]=='T')t++;
        }
        if(cnt==4||(cnt==3&&t==1))
            return 1;
    }
    for(int i=1;i<=n;i++){
        int cnt=0,t=0;
        for(int j=1;j<=n;j++){
            if(a[j][i]==x)cnt++;
            if(a[j][i]=='T')t++;
        }
        if(cnt==4||(cnt==3&&t==1))
            return 1;
    }
    int cnt=0,t=0;
    for(int i=1;i<=n;i++){
        if(a[i][i]==x)cnt++;
        if(a[i][i]=='T')t++;
    }
    if(cnt==4||(cnt==3&&t==1))
        return 1;
    cnt=0;t=0;
    for(int i=1;i<=n;i++){
        if(a[i][n-i+1]==x)cnt++;
        if(a[i][n-i+1]=='T')t++;
    }
    if(cnt==4||(cnt==3&&t==1))
        return 1;
    return 0;
}
bool draw(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(a[i][j]=='.')
                return 0;
    return 1;
}
int main(){
    cin>>T;
    for(int k=1;k<=T;k++){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                cin>>a[i][j];
        printf("Case #%d: ",k);
        if(check('O'))cout<<"O won";
        else if(check('X'))cout<<"X won";
        else if(draw())cout<<"Draw";
        else cout<<"Game has not completed";
        cout<<"\n";
    }
    return 0;
}
```

---

## 作者：shaoyu_parents_die (赞：0)

# 洛谷 P13281 题解：

这道题其实很简单，只需定义一个函数，在其内部判断行列和对角线，是否存在四个相同的 $X$ 或 $O$ 即可。如果最后函数对两个玩家的返回均是假，则判断棋盘是否为满。若是，则证明为平局。否则 则为游戏尚未结束。（多的全在代码的注释上）

## 判断行和列：

```cpp
for(int i = 1; i <= 4; i++) {
        bool f1 = true, f2 = true;  // f1标记行，f2标记列
        for(int j = 1; j <= 4; j++) {
            // 检查当前行是否全为c或'T'
            if(qipan[i][j] != c && qipan[i][j] != 'T') f1 = false;
            // 检查当前列是否全为c或'T'
            if(qipan[j][i] != c && qipan[j][i] != 'T') f2 = false;
        }
        // 如果任意一行或一列满足条件，返回true
        if(f1 || f2) return true;
    }
```

## 判断对角线：


```cpp
bool d1 = true, d2 = true;  // d1主对角线，d2副对角线
    for(int i = 1; i <= 4; i++) {
        // 检查主对角线
        if(qipan[i][i] != c && qipan[i][i] != 'T') d1 = false;
        // 检查副对角线(5-i计算对称位置)
        if(qipan[i][5-i] != c && qipan[i][5-i] != 'T') d2 = false;
    }
    // 如果任意一条对角线满足条件，返回true
    return d1 || d2;
```

## 判断平局和未结束：


```cpp
bool fdraw = true;
for(int i = 1; i <= 4; i++)
    for(int j = 1; j <= 4; j++)
        if(qipan[i][j] == '.') fdraw = false;  // 发现空位
            
if(fdraw) printf("Draw\n");
else printf("Game has not completed\n");
```

## AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 10;
char qipan[N][N];  // 存储棋盘状态的二维数组

// 检查玩家X或O是否获胜的函数
bool ch(char c) {
    // 检查行和列
    for(int i = 1; i <= 4; i++) {
        bool f1 = true, f2 = true;  // f1标记行，f2标记列
        for(int j = 1; j <= 4; j++) {
            // 检查当前行是否全为c或'T'
            if(qipan[i][j] != c && qipan[i][j] != 'T') f1 = false;
            // 检查当前列是否全为c或'T'
            if(qipan[j][i] != c && qipan[j][i] != 'T') f2 = false;
        }
        // 如果任意一行或一列满足条件，返回true
        if(f1 || f2) return true;
    }
    
    // 检查两条对角线
    bool d1 = true, d2 = true;  // d1主对角线，d2副对角线
    for(int i = 1; i <= 4; i++) {
        // 检查主对角线
        if(qipan[i][i] != c && qipan[i][i] != 'T') d1 = false;
        // 检查副对角线(5-i计算对称位置)
        if(qipan[i][5-i] != c && qipan[i][5-i] != 'T') d2 = false;
    }
    // 如果任意一条对角线满足条件，返回true
    return d1 || d2;
}

int main() {
    int n;  // 测试用例数量
    cin >> n;
    
    // 处理每个测试用例
    for(int t = 1; t <= n; t++) {
        // 读取棋盘状态
        for(int i = 1; i <= 4; i++)
            for(int j = 1; j <= 4; j++)
                cin >> qipan[i][j];
                
        printf("Case #%d: ", t);  // 输出用例编号
        
        // 检查X是否获胜
        if(ch('X')) printf("X won\n");
        // 检查O是否获胜
        else if(ch('O')) printf("O won\n");
        else {
            // 检查是否为平局(棋盘已满)
            bool fdraw = true;
            for(int i = 1; i <= 4; i++)
                for(int j = 1; j <= 4; j++)
                    if(qipan[i][j] == '.') fdraw = false;  // 发现空位
            
            if(fdraw) printf("Draw\n");
            else printf("Game has not completed\n");
        }
    }
    
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/224329979)

---

## 作者：Little_d (赞：0)

## 思路
枚举每一行，每一列，每一个斜线，每枚举一条线，记录下这条线中每种字符的数量，如果 X 的数量加 T 的数量刚好为 4 就是第一个人赢了，如果 O 的数量加 T 的数量刚好为 4 就是第二个人赢了。如果枚举完了仍然没有找到答案，判断矩阵中有没有空位，如果有，说明游戏还没有结束，否则说明平局。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
char c[5][5];
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>T;
    int temp=T;
    while(T--){
        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                cin>>c[i][j];
            }
        }
        cout<<"Case #"<<temp-T<<": ";
        bool flag=false;
        for(int i=1;i<=4;i++){
            int a=0,b=0,d=0;
            for(int j=1;j<=4;j++){
                if(c[i][j]=='X')a++;
                if(c[i][j]=='O')b++;
                if(c[i][j]=='T')d++;
            }
            if(a==4||(a==3&&d==1)){
                cout<<"X won\n";
                flag=true;
                break;
            }else if(b==4||(b==3&&d==1)){
                cout<<"O won\n";
                flag=true;
                break;
            }
        }
        if(flag)continue;
        for(int i=1;i<=4;i++){
            int a=0,b=0,d=0;
            for(int j=1;j<=4;j++){
                if(c[j][i]=='X')a++;
                if(c[j][i]=='O')b++;
                if(c[j][i]=='T')d++;
            }
            if(a==4||(a==3&&d==1)){
                cout<<"X won\n";
                flag=true;
                break;
            }else if(b==4||(b==3&&d==1)){
                cout<<"O won\n";
                flag=true;
                break;
            }
        }
        if(flag)continue;
        int a=0,b=0,d=0;
        for(int i=1;i<=4;i++){
            if(c[i][i]=='X')a++;
            if(c[i][i]=='O')b++;
            if(c[i][i]=='T')d++; 
        }
        if(a==4||(a==3&&d==1)){
            cout<<"X won\n";
            flag=true;
            continue;
        }else if(b==4||(b==3&&d==1)){
            cout<<"O won\n";
            flag=true;
            continue;
        }
        a=0,b=0,d=0;
        for(int i=1;i<=4;i++){
            if(c[i][4-i+1]=='X')a++;
            if(c[i][4-i+1]=='O')b++;
            if(c[i][4-i+1]=='T')d++; 
        }
        if(a==4||(a==3&&d==1)){
            cout<<"X won\n";
            flag=true;
            continue;
        }else if(b==4||(b==3&&d==1)){
            cout<<"O won\n";
            flag=true;
            continue;
        }
        if(flag)continue;
        flag=true;
        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                if(c[i][j]=='.'){
                    flag=false;
                    break;
                }
            }
            if(!flag)break;
        }
        if(!flag)cout<<"Game has not completed\n";
        else cout<<"Draw\n";
    }
    return 0;
}
```

---

