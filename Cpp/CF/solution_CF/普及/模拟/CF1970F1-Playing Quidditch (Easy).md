# Playing Quidditch (Easy)

## 题目描述

今天下午，你打算出去散步，享受春天的第一缕阳光。在靠近魁地奇球场时，你听到了争吵声。原来是比赛比分又引起了争议，两队都坚信自己赢得了比赛！为了避免这种事情再次发生，你决定参与到比赛的裁判工作中。

现在，你将在体育场内观看比赛并计算得分。比赛结束后，你将宣布胜者。

今天参赛的有两支队伍：红色的格兰芬多队（R）和蓝色的拉文克劳队（B）。每支队伍由 $P$ 名球员组成（$1 \leq P \leq 10$）。

比赛的场地是一个由 $N$ 行 $M$ 列组成的矩形（$3 \leq N, M \leq 99$，且 $N$ 和 $M$ 是奇数）。场上所有位置均为整数，多名球员或多个物体可以占据同一个位置。比赛开始时，场地上有双方队伍的目标（每队可拥有1至5个目标），球员，以及一个鬼飞球。其他种类的球将在更复杂的问题中涉及。

比赛分为 $T$ 步（$0 \leq T \leq 10000$）。每一步中，场上的一个实体（球员或球）将执行一个动作。所有的实体都能移动。球员还可以接球或投掷他们携带的鬼飞球。要接球，球员需要和球在同一个位置。当球员携带鬼飞球时，球只会跟随他的移动，而不会执行其他动作。如果球员决定投掷鬼飞球，它就留在当前的位置。

得分的条件是，球员必须将鬼飞球放入对方队伍的目标中。成功时，该球员所在的队伍就会得一分，而鬼飞球会立刻返回到场地的正中央（即第 $(M+1)/2$ 列和第 $(N+1)/2$ 行的位置，从 1 开始计数）。场中心没有目标。如果球员不小心将球放进了自己的目标中，那么对方队伍会得一分。

## 说明/提示

在第一个示例中，一名蓝队球员走到网格中心收球，然后带球前往红色队的目标并成功得分！鬼飞球回到场地中心，随后一个红队球员也拿球成功得分。

在第二个示例中，红队球员拿到鬼飞球，移动并投掷，随后由蓝队球员接过，带球前往红队目标并得分。

在第三个例子中，红队球员将球投入自己的目标，因此蓝队得分。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5 5
.. R1 .. B1 ..
RG .. .. .. BG
RG R0 .Q B0 BG
RG .. .. .. BG
.. R2 .. B2 ..
13
B2 U
B2 U
B2 L
B2 C .Q
B2 L
B2 L
B2 T
R0 R
R0 C .Q
R0 D
R0 R
R0 R
R0 T```

### 输出

```
6 BLUE GOAL
12 RED GOAL
FINAL SCORE: 1 1```

## 样例 #2

### 输入

```
3 5
.. .. R0 .. ..
RG .. .Q .. BG
.. .. B0 .. ..
12
R0 D
R0 C .Q
R0 R
R0 T
R0 D
B0 R
B0 U
B0 C .Q
B0 L
B0 L
B0 L
B0 T```

### 输出

```
11 BLUE GOAL
FINAL SCORE: 0 1```

## 样例 #3

### 输入

```
3 5
.. .. R0 .. ..
RG .. .Q .. BG
.. .. B0 .. ..
5
R0 D
R0 C .Q
R0 L
R0 L
R0 T```

### 输出

```
4 BLUE GOAL
FINAL SCORE: 0 1```

# 题解

## 作者：Solune (赞：2)

# CF1970F1 Playing Quidditch (Easy) 题解
## 题目大意
红色的格兰芬多队 $R$ 和蓝色的拉文克劳队 $B$ ，每队有 $1$ 到 $10$ 名队员。
 
场地是一个 $N$ 行 $M$ 列的矩形，场地上有球门、球员和一个鬼飞球。
 
比赛有 $T$ 步，每一步一个球员可以移动、抓球或投球：抓住球时，球跟随球员移动；投球时，球被放在球员当前位置。
 
得分方式：将球放入对方球门，该队伍得一分，球移动到场地中央；如果将球放入自己球门，对方队伍得分。  
## 思路
一道模拟题。
 
开始时用一个数组记录球员位置，移动时改变位置，本题中魁地奇球位置可以不用计算。

投球时判断是在哪个球门进球然后加分。  
注意：在**蓝队球门**投球**红队**加分，在**红队球门**投球**蓝队**加分，~~这个地方卡了我半天~~。
## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

#define pair pair<int, int>
#define x first
#define y second
const int MAX = 1e2 + 10;
map<string, pair> p;  //记录球员位置
string a[MAX][MAX];
int rs = 0, bs = 0;  //记录两队分数

int main() {
  int n, m, t;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
      if (a[i][j] != "..") p[a[i][j]] = {i, j};
    }
  }
  cin >> t;
  for (int i = 0; i < t; ++i) {
    string id, s;
    char op;
    cin >> id >> op;
    if (op == 'U')
      --p[id].x;
    else if (op == 'D')
      ++p[id].x;
    else if (op == 'L')
      --p[id].y;
    else if (op == 'R')
      ++p[id].y;
    else if (op == 'C')
      cin >> s;
    else if (op == 'T') {
      if (a[p[id].x][p[id].y] == "BG") {
        ++rs;
        printf("%d RED GOAL\n", i);

      } else if (a[p[id].x][p[id].y] == "RG") {
        ++bs;
        printf("%d BLUE GOAL\n", i);
      }
    }
  }
  printf("FINAL SCORE: %d %d", rs, bs);//注意输出顺序
  return 0;
}

```

---

## 作者：JOE_ZengYuQiao_0928 (赞：2)

### [先看题](https://vjudge.net.cn/problem/CodeForces-1970F1#author=GPT_zh)
### 思路分析
本题是一道大模拟。

在输入时，我们可以将各个球员的位置全部记录下来，后面进行移动时，再将各个球员的位置进行变化即可。

每次进球时，球员都会进行操作 T，那么我们只需要在球员进行 T 操作时看看这位球员是给红队还是给蓝队进球了即可。

注意：如果移动前魁地奇球与球员的位置在一起，那么人会带着魁地奇球走，那么魁地奇球的坐标也要跟着变。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string s[105][105];
struct nn{
	int x,y;
};
map<string,nn> mp;
int n,m,ans1,ans2; 
bool vis1[105][105];
bool vis2[105][105];
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s[i][j];
			mp[s[i][j]]={i,j};
		}
	}
	int T;
	cin>>T;
	for(int i=0;i<T;i++){
		string id;
		char ID;
		cin>>id>>ID;
		if(ID=='U'){
			if(mp[".Q"].x==mp[id].x&&mp[".Q"].y==mp[id].y){
				mp[".Q"].x--;
			}
			mp[id].x--;
		}
		if(ID=='D'){
			if(mp[".Q"].x==mp[id].x&&mp[".Q"].y==mp[id].y){
				mp[".Q"].x++;
			}
			mp[id].x++;
		}
		if(ID=='L'){
			if(mp[".Q"].x==mp[id].x&&mp[".Q"].y==mp[id].y){
				mp[".Q"].y--;
			}
			mp[id].y--;
		}
		if(ID=='R'){
			if(mp[".Q"].x==mp[id].x&&mp[".Q"].y==mp[id].y){
				mp[".Q"].y++;
			}
			mp[id].y++;
		}
		if(ID=='C'){
			string ss;
			cin>>ss;
		} 
		if(ID=='T'){
			if(s[mp[".Q"].x][mp[".Q"].y]=="BG"){
				cout<<i<<" RED GOAL\n";
				ans1++;
			}
			if(s[mp[".Q"].x][mp[".Q"].y]=="RG"){
				cout<<i<<" BLUE GOAL\n";
				ans2++;
			}
			mp[".Q"]={(n+1)/2,(m+1)/2};
		} 
	}
	cout<<"FINAL SCORE: "<<ans1<<" "<<ans2;
     return  0;
}

```

---

## 作者：The_foolishest_OIer (赞：0)

F1 和 F2 有点区别。

用几个结构体存储所有球员、球的位置和状态。

然后先让球员移动，最后判断是否进球（不用 map）。

但是 F1 真的没什么细节，只要记得如果球是被人携带的，那么球要和那个人同步（处于同一位置）。

直接模拟即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 105;
int n,m,t;
int redgoal,bluegoal;
struct where{
	int x,y;
};
struct Ball{
	int x,y;
	string catcher;
};
where r[15],b[15];
Ball ball[5];
string a[N][N];
void close(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
signed main(){
	close();
	cin >> n >> m;
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= m ; j++)
			cin >> a[i][j];
	for (int i = 1 ; i <= n ; i++){
		for (int j = 1 ; j <= m ; j++){
			if (a[i][j][1] == '.') continue;
			if (a[i][j][1] >= '0' && a[i][j][1] <= '9'){
				int num = a[i][j][1] - '0';
				if (a[i][j][0] == 'R'){
					r[num].x = i;
					r[num].y = j;
				}else{
					b[num].x = i;
					b[num].y = j;
				}
			}else if (a[i][j][0] == '.'){
				ball[1].x = i;
				ball[1].y = j;
				ball[1].catcher = "no";
			}
		}
	} // 预处理位置
	cin >> t;
	for (int p = 0 ; p < t ; p++){
		string name;
		char op;
		cin >> name >> op;
		if (op == 'D'){
			if (name[0] == 'R') r[name[1] - '0'].x++;
			else if (name[0] == 'B') b[name[1] - '0'].x++;
			else if (name[1] == 'Q') ball[1].x++;
		}else if (op == 'U'){
			if (name[0] == 'R') r[name[1] - '0'].x--;
			else if (name[0] == 'B') b[name[1] - '0'].x--;
			else if (name[1] == 'Q') ball[1].x--;
		}else if (op == 'L'){
			if (name[0] == 'R') r[name[1] - '0'].y--;
			else if (name[0] == 'B') b[name[1] - '0'].y--;
			else if (name[1] == 'Q') ball[1].y--;
		}else if (op == 'R'){
			if (name[0] == 'R') r[name[1] - '0'].y++;
			else if (name[0] == 'B') b[name[1] - '0'].y++;
			else if (name[1] == 'Q') ball[1].y++; // 移动
		}else if (op == 'C'){
			string ballname;
			cin >> ballname;
			if (ballname[1] == 'Q') ball[1].catcher = name;
		}else{
			ball[1].catcher = "no";
		}
		if (ball[1].catcher != "no"){
			if (ball[1].catcher[0] == 'R') ball[1].x = r[ball[1].catcher[1] - '0'].x;
			else ball[1].x = b[ball[1].catcher[1] - '0'].x;
			if (ball[1].catcher[0] == 'R') ball[1].y = r[ball[1].catcher[1] - '0'].y;
			else ball[1].y = b[ball[1].catcher[1] - '0'].y;
		}
		if (a[ball[1].x][ball[1].y] == "RG" && ball[1].catcher == "no"){
			bluegoal++;
			ball[1].x = n / 2 + 1;
			ball[1].y = m / 2 + 1;
			cout << p << " BLUE GOAL\n";
		}
		if (a[ball[1].x][ball[1].y] == "BG" && ball[1].catcher == "no"){
			redgoal++;
			ball[1].x = n / 2 + 1;
			ball[1].y = m / 2 + 1;
			cout << p << " RED GOAL\n";
		} // 是否进球
	}
	cout << "FINAL SCORE: " << redgoal << ' ' << bluegoal;
	return 0;
}
```

---

## 作者：Genshin_ZFYX (赞：0)

一道中模拟？

个人感觉处理鬼飞球、游走球更麻烦，所以认为三个版本相差不大。

我开了个结构体记录每位球员的位置，也开了个二维数组记录球场。这样既能通过对象找到位置，也能通过位置找到对象。

其他没什么好说的，较复杂的地方就是，进行移动，在鬼飞球放下的时候判断是那方球员投进了那方球门，很容易写错。

**忠告：大模拟比较难调，所以最好做一些注释，不要像我一样。**

本题解代码较为冗长且没有注释，放了也没有意义。

---

## 作者：lihongqian__int128 (赞：0)

# CF1970F1 Playing Quidditch (Easy)题解
一道大~~小~~模拟。

记录魁地奇球的位置与每个人的位置，进行操作即可。

```cpp
#include <bits/stdc++.h>
using namespace std ;
int t , n , m , x[25] , y[25] , c[25] , ga[100][100] , qx , qy , a , b ;
string p , s ;
char op ;
int f(string str)
{
	return str[1] - '0' + 1 + (str[0] == 'R') * 10 ;
}
int main()
{
	cin >> n >> m ;
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= m ; j++)
		{
			cin >> s ;
			if(s == ".Q")	qx = i , qy = j ;//记录魁地奇球的位置
			else if(s == "RG")	ga[i][j] = 1 ;
			else if(s == "BG")	ga[i][j] = 2 ;
			else if(s[0] != '.')	x[f(s)] = i , y[f(s)] = j ;
		}
	cin >> t ;
	for(int i = 1 ; i <= t ; i++)
	{
		cin >> p >> op ;
		if(op == 'U')	x[f(p)]-- , qx -= c[f(p)] ;//移动
		if(op == 'D')	x[f(p)]++ , qx += c[f(p)] ;//移动
		if(op == 'L')	y[f(p)]-- , qy -= c[f(p)] ;//移动
		if(op == 'R')	y[f(p)]++ , qy += c[f(p)] ;//移动
		if(op == 'C')//抓住球
		{
			cin >> s ;
			c[f(p)] = 1 ;
		}
		if(op == 'T')//放下球
		{
			c[f(p)] = 0 ;
			if(ga[x[f(p)]][y[f(p)]] == 1)
			{
				cout << i - 1 << " BLUE GOAL\n" ;//进球
				a++ ;
				qx = (n + 1) / 2 , qy = (m + 1) / 2 ;
			}
			if(ga[x[f(p)]][y[f(p)]] == 2)
			{
				cout << i - 1 << " RED GOAL\n" ;//进球
				b++ ;
				qx = (n + 1) / 2 , qy = (m + 1) / 2 ;
			}
		}
	}
	cout << "FINAL SCORE: " << b << ' ' << a ;//输出答案
	return 0 ;
}
```

---

## 作者：OIer_Hhy (赞：0)

一道~~大~~模拟题。

这道题可以用一个 `map` 记录球员及鬼飞球当时的坐标，
用一个数组 `a` 记录是否有人进球，用另一个数组 `b` 记录每位球员是否有鬼飞球。

当球员抓住鬼飞球后，鬼飞球跟着这个球员移动，直到这个球员投球。

话不多说，直接上代码。

My Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,t;
string a[110][110],s;
struct node{
	int x,y; 
};
map<string,node> mp; // 表示位置 
short c[10010]; // c[i]=1 表示 第i秒R进球，c[i]=2表示第i秒R进球
int blue,red;  
node middle;
int main(){
	cin>>n>>m;
	middle.x=(n+1)/2;
	middle.y=(m+1)/2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			string p=a[i][j];  
			mp[p]=(node){i,j};
		}
	}
	cin>>t;
	for(int i=0;i<t;i++){
		string player,action;
		cin>>player>>action;
		node axis=mp[player];
		if(action=="L"){
			axis.y--;
			mp[player]=axis;
		}else if(action=="R"){
			axis.y++;
			mp[player]=axis;
		}else if(action=="U"){
			axis.x--;
			mp[player]=axis;
		}else if(action=="D"){
			axis.x++;
			mp[player]=axis;
		}else if(action=="T"){
			if(a[axis.x][axis.y][1]=='G'){
				if(a[axis.x][axis.y][0]=='B'){
					red++;
					c[i]=1;
				}else{
					blue++;
					c[i]=2;
				}
				mp[".Q"]=middle;
			}
		}else{
			cin>>action; 
			mp[".Q"].x=mp[player].x;
			mp[".Q"].y=mp[player].y;
		}
	}
	for(int i=0;i<t;i++){
		if(c[i]==1) cout<<i<<" RED GOAL\n";
		else if(c[i]==2) cout<<i<<" BLUE GOAL\n";
	}
	cout<<"FINAL SCORE: "<<red<<' '<<blue<<endl;
	return 0;
}

```

---

## 作者：KaMuaMua (赞：0)

**大概意思**

红队 
 $R$ 和蓝队 
 $B$，每队有 
 $1$ 到 
 $10$ 名队员。

场地是一个 
 $N$ 行 
 $M$ 列的矩形，场地上有球门、球员和一个球。

比赛有 
 $T$ 步，每一步一个球员可以移动、抓球或投球：抓住球时，球跟随球员移动；投球时，球被放在球员当前位置。

在比赛中，将球放入对方球门，该队伍得一分，球重新回到场地中央；如果将球放入自己球门，对方队伍得分。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
struct yee{
	long long x,y;
};
map<string,yee> mp;
string s[105][105];
long long n,m,sb,sd,T;
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s[i][j];
			mp[s[i][j]]={i,j};
		}
	}
	cin>>T;
	for(int i=0;i<T;i++){
		string mn;
		char nm;
		cin>>mn>>nm;
		if(nm=='U'){
			if(mp[".Q"].x==mp[mn].x&&mp[".Q"].y==mp[mn].y) mp[".Q"].x--;
			mp[mn].x--;
		}if(nm=='D'){
			if(mp[".Q"].x==mp[mn].x&&mp[".Q"].y==mp[mn].y) mp[".Q"].x++;
			mp[mn].x++;
		}if(nm=='L'){
			if(mp[".Q"].x==mp[mn].x&&mp[".Q"].y==mp[mn].y) mp[".Q"].y--;
			mp[mn].y--;
		}if(nm=='R'){
			if(mp[".Q"].x==mp[mn].x&&mp[".Q"].y==mp[mn].y) mp[".Q"].y++;
			mp[mn].y++;//ctrl+c ctrl+v 
		}if(nm=='C'){
			string dcb;
			cin>>dcb;
		} 
		if(nm=='T'){
			if(s[mp[".Q"].x][mp[".Q"].y]=="BG"){
				cout<<i<<" RED GOAL"<<endl;
				sb++;
			}if(s[mp[".Q"].x][mp[".Q"].y]=="RG"){
				cout<<i<<" BLUE GOAL"<<endl;
				sd++;
			}mp[".Q"]={(n+1)/2,(m+1)/2};
		}
	}cout<<"FINAL SCORE: "<<sb<<" "<<sd;
    return 0;
}
```
附：灵感与思路来自[@zhangyiyou35](https://www.luogu.com.cn/user/1123057)
[@JOE_ZengYuQiao_0928](https://www.luogu.com.cn/user/853792)

---

## 作者：albertting (赞：0)

## CF1970F1 题解

一道简单的模拟题，我们拆开每种操作分别写再合起来就好啦~~

### 输入

储存使用了 ```map```。

用 ```map``` 的话可以以球员（或球）的编号为下标存所在的位置，比较方便。

```cpp
void read_map()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            string s;
            cin >> s;
            mps[i][j] = s;
            /*  这里是为了存球门的位置
             *  球门有多个所以 map 会存不了
             */ 反正不会移动就用数组存好了
            mp[s] = make_pair(i, j);
        }
    }
}
```

### 移动

因为只有球员会自己动，所以直接判断方向就好了。

```cpp
string p, r, b;
cin >> p >> r;
if(r == "U")
{
    mp[p].first--;
}
else if(r == "D")
{
    mp[p].first++;
}
else if(r == "L")
{
    mp[p].second--;
}
else if(r == "R")
{
    mp[p].second++;
}
```
### 带球

首先我们要知道是谁带的球。

只需要在球员抓住鬼飞球的时候记录编号就可以了。

```cpp
else if(r == "C")
{
    cin >> b;
    if(b == ".Q")
    {
        pwq = p;
        // pwq == the Player With Quaffle
    }
}
```

然后在移动部分加一些东西：

```cpp
if(pwq == p)
{
    mp[".Q"].【球员的移动方式】;
}
```

就好啦！

### 进球

只要有人进球就加分。

有人把球扔了就留在原地。

进球之后鬼飞球会瞬移这点要注意。

```cpp
else if(r == "T")
{
    if(mps[mp[p].first][mp[p].second] == "BG")
    {
        rg++;
        printf("%d RED GOAL\n", t);
        mp[".Q"] = make_pair((n + 1) / 2, (m + 1) / 2);
    }
    else if(mps[mp[p].first][mp[p].second] == "RG")
    {
        bg++;
        printf("%d BLUE GOAL\n", t);
        mp[".Q"] = make_pair((n + 1) / 2, (m + 1) / 2);
    }
    pwq = "";
}
```

### 全代码

[代码太长鸟，就放这里了](https://www.luogu.com.cn/paste/kr5h0p1m)

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF1970F1)

## 思路

一道大模拟。

用 map 记录所有球员的位置，随后跟着操作改变位置即可。

注意判断哪个队进球。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,T,i,j,r,b;
string k,s,a[101][101];
char op;
struct node{
    int x,y;
};
map<string,node> f;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();cout.tie(0);
    cin>>n>>m;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++){
            cin>>a[i][j];
            if(a[i][j]!="..")
                f[a[i][j]]=(node){i,j};//记录位置
        }
    cin>>T;
    for(i=0;i<T;i++){
        cin>>k>>op;
        if(op=='U') f[k].x--;
        else if(op=='D') f[k].x++;
        else if(op=='L') f[k].y--;
        else if(op=='R') f[k].y++;
        else if(op=='C') cin>>s;
        else if(op=='T')
            if(a[f[k].x][f[k].y]=="BG") r++,cout<<i<<" RED GOAL\n";
            else if(a[f[k].x][f[k].y]=="RG") b++,cout<<i<<" BLUE GOAL\n";
    }
    cout<<"FINAL SCORE: "<<r<<" "<<b;
    return 0;
}
```

---

