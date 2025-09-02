# Playing Quidditch (Hard)

## 题目描述

This afternoon, you decided to enjoy the first days of Spring by taking a walk outside. As you come near the Quidditch field, you hear screams. Once again, there is a conflict about the score: the two teams are convinced that they won the game! To prevent this problem from happening one more time, you decide to get involved in the refereeing of the matches.

Now, you will stay in the stadium to watch the game and count the score. At the end of the game, you will decide the winner.

Today, two teams are competing: the red Gryffindor (R) and the blue Ravenclaw (B) team. Each team is composed of $ P $ players ( $ 1 \leq P \leq 10 $ ).

The field is a rectangle of $ N $ lines and $ M $ columns ( $ 3 \leq N, M \leq 99 $ , $ N $ and $ M $ are odd). All the positions are integers, and several entities are allowed to be at the same position in the field. At the beginning of the game, the field contains goals for the two teams (each team can own between one and five goals), the players, and exactly one Quaffle. In this version of the problem, one Bludger and a Golden Snitch can be present.

A game is composed of $ T $ steps ( $ 0 \leq T \leq 10000 $ ). At each step, one entity on the field (a player or a ball) performs one action. All entities can move. A player can also catch a ball or throw the Quaffle that it is carrying. To catch a ball, a player must be located on the same cell as it. The Quaffle does not perform any action while it is being carried; it only follows the movements of the player. If a player carrying the Quaffle decides to throw it, the Quaffle is simply put at the current position of the player. If a player is on the same cell as a Bludger (either after a movement from the player or the Bludger), the player is eliminated. If the player is eliminated while it is carrying the Quaffle, the Quaffle remains on the cell containing both the player and the Bludger after the move. It is guaranteed that this never occurs while the player is in a cell containing a goal.

To win a point, a player must leave the Quaffle at a goal of the other team. When it does, the team of the player wins one point, and the Quaffle instantly moves to the middle of the field (the cell at the $ (M+1)/2 $ -th column of the $ (N+1)/2 $ -th line of the field, starting from 1). There is no goal in the middle of the field. If a player puts the ball in its own goal, the other team wins the point. If a player catches the Golden Snitch, their team wins 10 points and the game is over.

## 说明/提示

In the first example, the red player takes the Quaffle, move it and throw it. The blue player catches the ball, goes to the red goal and scores.

In the second example, the red player takes the ball and scores in the goal of their own team: the blue team wins a point.

In the third example, the Bludger goes at the position of R0: R0 is eliminated. Then, B0 moves to the position of the Bludger: B0 is eliminated too.

In the fourth example, a red player catches the Golden Snitch. Their team wins 10 points, and the game ends.

You can find one more example in the easy version of the problem

## 样例 #1

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

## 样例 #2

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

## 样例 #3

### 输入

```
5 5
.. .. .. .. ..
.. .. .. .. ..
RG R0 .Q B0 BG
.. .. .. .. ..
.. .. .B .. ..
5
.B L
.B U
.B U
B0 L
B0 L```

### 输出

```
2 R0 ELIMINATED
4 B0 ELIMINATED
FINAL SCORE: 0 0```

## 样例 #4

### 输入

```
5 5
.. R0 .S B0 ..
.. .. .. .. ..
RG .. .Q .. BG
.. .. .. .. ..
.. R1 .B B1 ..
4
.S D
R0 D
R0 R
R0 C .S```

### 输出

```
3 RED CATCH GOLDEN SNITCH
FINAL SCORE: 10 0```

# 题解

## 作者：JOE_ZengYuQiao_0928 (赞：2)

### [先看题](https://vjudge.net.cn/problem/CodeForces-1970F3#author=GPT_zh)
### 思路分析
本题是一道大模拟。

在输入时，我们可以将各个球员以及游走球的位置全部记录下来，后面进行移动时，再将各个球员和游走球的位置进行变化即可。

每次进球时，球员都会进行操作 $T$，那么我们只需要在球员进行 $T$ 操作时看看这位球员是给红队还是给蓝队进球了即可。

每次淘汰人，必须是在进行过一次移动之后，所以我们可以在进行完一次移动之后，再看看每个球员的位置，如果跟游走球位置一样，就可以被淘汰了。

如果捉住了金色飞贼，那么必定会输入操作 $C .S$，反之，只要输入操作 $C .S$，那就一定捉住了金色飞贼。

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
void cao_zuo(string x,int i){ 
	if(mp[".B"].x==mp[x].x&&mp[".B"].y==mp[x].y){
		cout<<i<<" "<<x<<" ELIMINATED\n";
		mp[x]={0,0};
	}
	return;
}
signed main(){
	cin>>n>>m;
	mp[".B"]={n+1,m+1};
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
		if(mp[id].x==0||mp[id].y==0)continue;
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
			if(ss==".S"){
				if(id[0]=='R'){
					cout<<i<<" RED CATCH GOLDEN SNITCH\n";
					ans1+=10;
				}
				if(id[0]=='B'){
					cout<<i<<" BLUE CATCH GOLDEN SNITCH\n";
					ans2+=10;
				}
				break;
			}
		} 
		if(ID=='T'){
			if(s[mp[id].x][mp[id].y]=="BG"){
				cout<<i<<" RED GOAL\n";
				ans1++;
				mp[".Q"]={(n+1)/2,(m+1)/2};
			}
			if(s[mp[id].x][mp[id].y]=="RG"){
				cout<<i<<" BLUE GOAL\n";
				ans2++;
				mp[".Q"]={(n+1)/2,(m+1)/2};
			}
		} 
		cao_zuo("B0",i);
		cao_zuo("B1",i);
		cao_zuo("B2",i);
		cao_zuo("B3",i);
		cao_zuo("B4",i);
		cao_zuo("B5",i);
		cao_zuo("B6",i);
		cao_zuo("B7",i);
		cao_zuo("B8",i);
		cao_zuo("B9",i);
		cao_zuo("R0",i);
		cao_zuo("R1",i);
		cao_zuo("R2",i);
		cao_zuo("R3",i);
		cao_zuo("R4",i);
		cao_zuo("R5",i);
		cao_zuo("R6",i);
		cao_zuo("R7",i);
		cao_zuo("R8",i);
		cao_zuo("R9",i);
	}
	cout<<"FINAL SCORE: "<<ans1<<" "<<ans2;
     return  0;
}
```

---

## 作者：Solune (赞：1)

# CF1970F3 Playing Quidditch (Hard) 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1970F3)
## 思路
用一个 `map` 类型数组记录球和球员的位置，移动时更新，因为只有在**携带**鬼飞球时才能投球，所以鬼飞球的位置可以**不用**记。

抓球时判断一下是否是金色飞贼 `.S` ，如果是，则抓球方加 $10$ 分，输出比分，结束。

在每个动作结束时，判断每个球员的位置是否和游走球一样，如果一样就淘汰，注意如果有几名队员在同一时间被淘汰，按字典序输出事件。

投球时判断是在哪个球门进球然后加分，注意：在**蓝队球门**投球**红队**加分；在**红队球门**投球**蓝队**加分。
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define pair pair<int, int>
#define x first
#define y second
const int MAX = 1e2 + 10;
map<string, pair> mp;  //记录位置
string a[MAX][MAX];
int rs = 0, bs = 0;  //记录两队分数

bool check(string id) {
  if (a[mp[id].x][mp[id].y][1] != 'G' && mp[id] == mp[".B"]) {
    mp.erase(id);
    return true;
  }
  return false;
}

int main() {
  int n, m, t;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cin >> a[i][j];
      if (a[i][j] != "..") mp[a[i][j]] = {i, j};
    }
  }
  cin >> t;
  for (int i = 0; i < t; ++i) {
    string id;
    char op;
    cin >> id >> op;
    if (op == 'U')
      --mp[id].x;
    else if (op == 'D')
      ++mp[id].x;
    else if (op == 'L')
      --mp[id].y;
    else if (op == 'R')
      ++mp[id].y;
    else if (op == 'C') {
      string s;
      cin >> s;
      if(s == ".S"){
      	if (id[0]=='B') {
      	  bs+=10;
      	  cout << i << " " << "BLUE " << "CATCH GOLDEN SNITCH\n"; 
		} else {
      	  rs+=10;	
      	  cout << i << " " << "RED " << "CATCH GOLDEN SNITCH\n"; 
		}
      	break;
	  }
      //判断一下抓的是不是金色飞贼，如果是就加10分，结束比赛 
    } else if (op == 'T') {
      //进球加分 
      if (a[mp[id].x][mp[id].y] == "BG") {
        ++rs;
        cout << i << " RED GOAL\n";
      } else if (a[mp[id].x][mp[id].y] == "RG") {
        ++bs;
        cout << i << " BLUE GOAL\n";
      }
    }
    //检测淘汰
    for (int j = 0; j < 10; ++j) {
      string str = "B";
      str += ('0' + j);
      if (mp.find(str) != mp.end())
        if (check(str)) cout << i << " " << str << " ELIMINATED\n";
    }
    for (int j = 0; j < 10; ++j) {
      string str = "R";
      str += ('0' + j);
      if (mp.find(str) != mp.end())
        if (check(str)) cout << i << " " << str << " ELIMINATED\n";
    }
  }
  printf("FINAL SCORE: %d %d", rs, bs);
  return 0;
}
```
Codeforces 上 AC。

---

## 作者：Genshin_ZFYX (赞：1)

请先阅读：

[简单版本](https://www.luogu.com.cn/article/188w8lc8)

[中等版本](https://www.luogu.com.cn/article/3v2hvvlq)

困难版本就加了个最容易处理的金色飞贼。请先完成简单和中等版本再来看此篇题解。

每当有人抓住金色飞贼，我们**先加分**，再直接结束游戏。

还是放个代码算了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,tim,blue,red,rs,bs;
struct node{
    int x,y;
    int ball,d;
}b[15],r[15],gf,yz,fz;
int qm[105][105];
bool dir[15],dib[15];
void end()
{
	cout<<"FINAL SCORE: "<<rs<<" "<<bs;
	exit(0);
}
void died(int l,int num)
{
	if(l==1&&!dir[num])
	{
		dir[num]=1;
		blue--;
		b[num].x=b[num].y=0;
		cout<<tim<<" B"<<num<<" ELIMINATED"<<'\n';
	}
	if(l==2&&!dib[num])
	{
		dib[num]=1;
		red--;
		r[num].x=r[num].y=0;
		cout<<tim<<" R"<<num<<" ELIMINATED"<<'\n';
	}
}
void zb(node &mb,int x,int y){mb.x=x;mb.y=y;}
void ballcz(node &mb,char c,bool isgf)
{
	if(c=='U')mb.x--;
	if(c=='D')mb.x++;
	if(c=='L')mb.y--;
	if(c=='R')mb.y++;
	if(isgf)
	{
		for(int i=0;i<=9;i++)
		{
			if(b[i].x==0||b[i].y==0)continue;
			if(yz.x==b[i].x&&yz.y==b[i].y)
			died(1,i);
		}
		for(int i=0;i<=9;i++)
		{
			if(r[i].x==0||r[i].y==0)continue;
			if(yz.x==r[i].x&&yz.y==r[i].y)
			died(2,i);
		}
	}
}
void pan(int l,int num)
{
	if(l==1)
	{
		if(yz.x==r[num].x&&yz.y==r[num].y)
			died(2,num);
	}
	if(l==2)
	{
		if(yz.x==b[num].x&&yz.y==b[num].y)
			died(1,num);
	}
}
void cz(string s,char c)
{
	int num;
	if(s[0]!='.')num=s[1]-'0';
	else
	{
		if(s==".B")ballcz(yz,c,true);
		/*
		if(s==".Q")
		{
			gf.d=gf.ball=0;
			ballcz(gf,c,false);
		}*/
		if(s==".S")ballcz(fz,c,false);
		return;
	}
	if(c=='U')
	{
		if(s[0]=='B')b[num].x--,pan(2,num);
		else r[num].x--,pan(1,num);
	}
	if(c=='D')
	{
		if(s[0]=='B')b[num].x++,pan(2,num);
		else r[num].x++,pan(1,num);
	}
	if(c=='L')
	{
		if(s[0]=='B')b[num].y--,pan(2,num);
		else r[num].y--,pan(1,num);
	}
	if(c=='R')
	{
		if(s[0]=='B')b[num].y++,pan(2,num);
		else r[num].y++,pan(1,num);
	}
	if(c=='C')
	{
		string ball;cin>>ball;
		if(ball==".Q")
		{
			if(s[0]=='R')gf.ball=1,gf.d=num;
			else gf.ball=2,gf.d=num;
		}
		if(ball==".S")
		{
			cout<<tim;
			if(s[0]=='R')rs+=10,cout<<" RED";
			else bs+=10,cout<<" BLUE";
			cout<<" CATCH GOLDEN SNITCH"<<'\n';
			end();
		}
	}
	if(c=='T')
	{
		if(s[0]=='R')
		{
			if(gf.ball!=1||gf.d!=num)return;
			if(qm[r[num].x][r[num].y]==1)
			{
				cout<<tim<<" BLUE GOAL"<<'\n';
				bs++;gf.x=(n+1)/2;gf.y=(m+1)/2;
			}
			if(qm[r[num].x][r[num].y]==2)
			{
				cout<<tim<<" RED GOAL"<<'\n';
				rs++;gf.x=(n+1)/2;gf.y=(m+1)/2;
			}
		}
		if(s[0]=='B')
		{
			if(gf.ball!=2||gf.d!=num)return;
			if(qm[b[num].x][b[num].y]==1)
			{
				cout<<tim<<" BLUE GOAL"<<'\n';
				bs++;gf.x=(n+1)/2;gf.y=(m+1)/2;
			}
			if(qm[b[num].x][b[num].y]==2)
			{
				cout<<tim<<" RED GOAL"<<'\n';
				rs++;gf.x=(n+1)/2;gf.y=(m+1)/2;
			}
		}
	}
}
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	yz.x=yz.y=100;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        string s;
        cin>>s;
        if(s=="RG")qm[i][j]=1;
        else if(s=="BG")qm[i][j]=2;
        else if(s[0]=='R')
		{
			red++;
			zb(r[s[1]-'0'],i,j);
		}
        else if(s[0]=='B')
		{
			blue++;
			zb(b[s[1]-'0'],i,j);
		}
        else if(s==".Q")zb(gf,i,j);
        else if(s==".B")zb(yz,i,j);
        else if(s==".S")zb(fz,i,j);
    }
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        string s;char c;
        cin>>s>>c;
        cz(s,c);
        tim++;
    }
    end();
    return 0;
}
```

---

## 作者：The_foolishest_OIer (赞：0)

大模拟 ~~（实际上一点也不大）~~。

用几个结构体存储所有球员、球的位置和状态。


```cpp
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
		}else{
			if (a[i][j][1] == 'Q'){
				ball[1].x = i;
				ball[1].y = j;
				ball[1].catcher = "no";
			}else if (a[i][j][1] == 'B'){
				ball[2].x = i;
				ball[2].y = j;
				ball[2].catcher = "no";
			}else{
				ball[3].x = i;
				ball[3].y = j;
				ball[3].catcher = "no";
			}
		}
	}
}
```


操作一共 $2$ 大类：

移动类：共 `U D L R` 四种，直接改变坐标即可。

```cpp
if (op == 'D'){
	if (name[0] == 'R') r[name[1] - '0'].x++;
	else if (name[0] == 'B') b[name[1] - '0'].x++;
	else if (name[1] == 'Q') ball[1].x++;
	else if (name[1] == 'B') ball[2].x++;
	else ball[3].x++;
}else if (op == 'U'){
	if (name[0] == 'R') r[name[1] - '0'].x--;
	else if (name[0] == 'B') b[name[1] - '0'].x--;
	else if (name[1] == 'Q') ball[1].x--;
	else if (name[1] == 'B') ball[2].x--;
	else ball[3].x--;
}else if (op == 'L'){
	if (name[0] == 'R') r[name[1] - '0'].y--;
	else if (name[0] == 'B') b[name[1] - '0'].y--;
	else if (name[1] == 'Q') ball[1].y--;
	else if (name[1] == 'B') ball[2].y--;
	else ball[3].y--;
}else if (op == 'R'){
	if (name[0] == 'R') r[name[1] - '0'].y++;
	else if (name[0] == 'B') b[name[1] - '0'].y++;
	else if (name[1] == 'Q') ball[1].y++;
	else if (name[1] == 'B') ball[2].y++;
	else ball[3].y++;
}
```

因为如果有人抓住了球，球应该跟着人动，所以再加几行：

```
if (ball[1].catcher != "no"){
	if (ball[1].catcher[0] == 'R') ball[1].x = r[ball[1].catcher[1] - '0'].x;
	else ball[1].x = b[ball[1].catcher[1] - '0'].x;
	if (ball[1].catcher[0] == 'R') ball[1].y = r[ball[1].catcher[1] - '0'].y;
	else ball[1].y = b[ball[1].catcher[1] - '0'].y;
}
```

与球有关：共 `C T` $2$ 种，直接改即可：

```cpp
else if (op == 'C'){
	string ballname;
	cin >> ballname;
	if (ballname[1] == 'Q') ball[1].catcher = name;
	else ball[3].catcher = name;
}else{
	ball[1].catcher = "no";
}
```

接下来先判断有没有进球：

```cpp
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
}
```

再判断是否有球员接住金球（$10$ 分球）：


```cpp
if (ball[3].x != 0 && ball[3].catcher != "no"){
	if (ball[3].catcher[0] == 'R'){
		redgoal += 10;
		cout << p << " RED CATCH GOLDEN SNITCH\n";
	}else{
		bluegoal += 10;
		cout << p << " BLUE CATCH GOLDEN SNITCH\n";
	}
	break;
}
```

最后判断是否有球员被创，直接枚举即可：

```cpp
if (ball[2].x == 0) continue; // 先判断是否有这个球
for (int i = 0 ; i <= 9 ; i++){
	if (b[i].x == ball[2].x && b[i].y == ball[2].y){
		cout << p << ' ' << 'B' << i << " ELIMINATED\n";
		b[i].x = 0;
	}
}
for (int i = 0 ; i <= 9 ; i++){
	if (r[i].x == ball[2].x && r[i].y == ball[2].y){
		cout << p << ' ' << 'R' << i << " ELIMINATED\n";
		r[i].x = 0;
	}
}
```

完整代码：

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
			}else{
				if (a[i][j][1] == 'Q'){
					ball[1].x = i;
					ball[1].y = j;
					ball[1].catcher = "no";
				}else if (a[i][j][1] == 'B'){
					ball[2].x = i;
					ball[2].y = j;
					ball[2].catcher = "no";
				}else{
					ball[3].x = i;
					ball[3].y = j;
					ball[3].catcher = "no";
				}
			}
		}
	}
	cin >> t;
	for (int p = 0 ; p < t ; p++){
		string name;
		char op;
		cin >> name >> op;
		if (op == 'D'){
			if (name[0] == 'R') r[name[1] - '0'].x++;
			else if (name[0] == 'B') b[name[1] - '0'].x++;
			else if (name[1] == 'Q') ball[1].x++;
			else if (name[1] == 'B') ball[2].x++;
			else ball[3].x++;
		}else if (op == 'U'){
			if (name[0] == 'R') r[name[1] - '0'].x--;
			else if (name[0] == 'B') b[name[1] - '0'].x--;
			else if (name[1] == 'Q') ball[1].x--;
			else if (name[1] == 'B') ball[2].x--;
			else ball[3].x--;
		}else if (op == 'L'){
			if (name[0] == 'R') r[name[1] - '0'].y--;
			else if (name[0] == 'B') b[name[1] - '0'].y--;
			else if (name[1] == 'Q') ball[1].y--;
			else if (name[1] == 'B') ball[2].y--;
			else ball[3].y--;
		}else if (op == 'R'){
			if (name[0] == 'R') r[name[1] - '0'].y++;
			else if (name[0] == 'B') b[name[1] - '0'].y++;
			else if (name[1] == 'Q') ball[1].y++;
			else if (name[1] == 'B') ball[2].y++;
			else ball[3].y++;
		}else if (op == 'C'){
			string ballname;
			cin >> ballname;
			if (ballname[1] == 'Q') ball[1].catcher = name;
			else ball[3].catcher = name;
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
		}
		if (ball[3].x != 0 && ball[3].catcher != "no"){
			if (ball[3].catcher[0] == 'R'){
				redgoal += 10;
				cout << p << " RED CATCH GOLDEN SNITCH\n"; 
			}else{
				bluegoal += 10;
				cout << p << " BLUE CATCH GOLDEN SNITCH\n";
			}
			break;
		}
		if (ball[2].x == 0) continue;
		for (int i = 0 ; i <= 9 ; i++){
			if (b[i].x == ball[2].x && b[i].y == ball[2].y){
				cout << p << ' ' << 'B' << i << " ELIMINATED\n";
				b[i].x = 0;
			}
		}
		for (int i = 0 ; i <= 9 ; i++){
			if (r[i].x == ball[2].x && r[i].y == ball[2].y){
				cout << p << ' ' << 'R' << i << " ELIMINATED\n";
				r[i].x = 0;
			}
		}
	}
	cout << "FINAL SCORE: " << redgoal << ' ' << bluegoal;
	return 0;
}
```

---

## 作者：_JF_ (赞：0)

[CF1970F3 Playing Quidditch (Hard) ](https://www.luogu.com.cn/problem/CF1970F3)

做法没有什么好讲的，纯模拟。不算很难。主要是模拟的时候没啥技巧性的东西，就是写。

这样有***2300**？？比较逆天。

注意不能在原图上操作，因为人可以重叠和穿插/kx，所以我们存下每个人的位置来模拟。

讲一些细节的地方？

- 题目好像保证了不会走出边界。
- 三种球都是可以游走的，比如我一开始就默认 `.Q` 是不能游走的。（在 `.Q` 游走的时候，保证没有人拿着它？这点我不知道题目有无保证，我没写也过了/yun）
- 如果 `.B` 和某个人的位置重合，那么人就淘汰了，并不一定是 `.B` 主动去撞人。
- 注意顺序，如果多个人被淘汰，那么要先输出 `B` 再输出 `R`。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
const int Max=301;
int n,m,PointB,PointR,Youzoux,Youzouy,Ballx,Bally,Get[3][N],dx[4]={0,0,-1,1},dy[4]={-1,1,0,0};
int Flyx,Flyy,goal[Max][Max];
struct node{
	int x,y,live;
}Dus[3][N];
int change(string x){
	if(x=="L")	return 0;
	if(x=="R")	return 1;
	if(x=="U")	return 2;
	else	return 3;
}
void walk(int Op,int num,string x,int Time){
	if(Op==1||Op==0){
		Dus[Op][num].x+=dx[change(x)],Dus[Op][num].y+=dy[change(x)];
		if(Get[Op][num]==1)
			Ballx=Dus[Op][num].x,Bally=Dus[Op][num].y;
	}
	else if(Op==2){
		Youzoux+=dx[change(x)],Youzouy+=dy[change(x)];
		for(int i=0;i<=10;i++){
			if(Dus[0][i].live&&Dus[0][i].x==Youzoux&&Dus[0][i].y==Youzouy){
				Dus[0][i].live=0,Get[0][i]=0;
				cout<<Time<<' '<<'B'<<i<<' '<<"ELIMINATED"<<endl;
			}
		}
		for(int i=0;i<=10;i++){
			if(Dus[1][i].live&&Dus[1][i].x==Youzoux&&Dus[1][i].y==Youzouy){
				Dus[1][i].live=0,Get[1][i]=0;
				cout<<Time<<' '<<'R'<<i<<' '<<"ELIMINATED"<<endl;
			}
		}
	}
	else if(Op==3){
		Flyx+=dx[change(x)],Flyy+=dy[change(x)];
	}
	else{
		Ballx+=dx[change(x)],Bally+=dy[change(x)];
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			char x,y; cin>>x>>y;
			if(x=='R'){
				if(y=='G')	goal[i][j]=1;
				else{
					int num=y-'0'; 
					Dus[1][num].x=i,Dus[1][num].y=j,Dus[1][num].live=1;
				}
			}
			else if(x=='B'){
				if(y=='G')	goal[i][j]=-1;
				else{
					int num=y-'0'; 
					Dus[0][num].x=i,Dus[0][num].y=j,Dus[0][num].live=1;
				}	
			}
			if(y=='B')	Youzoux=i,Youzouy=j;
			if(y=='S')	Flyx=i,Flyy=j;
			if(y=='Q')	Ballx=i,Bally=j;
		}
//	cout<<Ballx<<' '<<Bally<<endl;
	int Q;
	cin>>Q;
	for(int i=1;i<=Q;i++){
		string p,x; cin>>p>>x; int op=0;
		if(p[0]=='R')	op=1;
		if(p[0]=='R'||p[0]=='B'){
			int num=p[1]-'0';
			if(Dus[op][num].live==0)	continue;
			if(x=="T"){
				if(goal[Dus[op][num].x][Dus[op][num].y]!=0&&Get[op][num]==1){
					cout<<i-1<<' ';
					if(goal[Dus[op][num].x][Dus[op][num].y]==1)	cout<<"BLUE"<<' ',PointB++;
					else	cout<<"RED"<<' ',PointR++;
					cout<<"GOAL"<<endl;
					Ballx=(n+1)/2,Bally=(m+1)/2;
				}
				Get[op][num]=0;
			}
			else if(x=="C"){
				string predus; cin>>predus;
				if(predus==".Q")
					Get[op][num]=1,Dus[op][num].x=Ballx,Dus[op][num].y=Bally;
				else{
					cout<<i-1<<' ';
					if(op==1)	cout<<"RED"<<' ',PointR+=10;
					else	cout<<"BLUE"<<' ',PointB+=10;
					cout<<"CATCH GOLDEN SNITCH"<<endl;
					break;
				}
			}
			else{
				walk(op,num,x,0);//cout<<"fuck"<<" "<<Dus[op][num].x<<' '<<Dus[op][num].y<<endl;
				if(Dus[op][num].x==Youzoux&&Dus[op][num].y==Youzouy){
					Dus[op][num].live=0,Get[op][num]=0;
					cout<<i-1<<' '<<((op==1)?'R':'B')<<num<<' '<<"ELIMINATED"<<endl;
				}
			}
		}
		else{
			int op=2;
			if(p[1]=='S')	op=3;
			if(p[1]=='Q')	op=4;
			walk(op,0,x,i-1);
		}
		
//		cout<<Ballx<<' '<<Bally<<endl;
	}
	cout<<"FINAL SCORE: "<<PointR<<' '<<PointB<<endl;
	return 0;
}
```

---

## 作者：albertting (赞：0)

## CF1970F3 题解

### 球员移动、鬼飞球和游走球

[球员移动和鬼飞球](/article/lf2exnti)

[游走球](/article/my3hhcre)

### 金色飞贼

书又接上回。

金色飞贼的规则比较简单。

在写的时候呢，如果输入了 ```C```，特判一下抓住的是 ```.Q``` 还是 ```.S``` 就好了，金色飞贼加十分，鬼飞球加一分。

虽然它本身也会动，但是和球员的移动还是一样的，不用单独写。

```cpp
else if(r == "C")
{
    cin >> b;
    if(b == ".Q")
    {
        pwq = p;
    }  //这里是游走球
    if(b == ".S")
    {
        cout << t << ((p[0] == 'R')? " RED" : " BLUE");
        cout << " CATCH GOLDEN SNITCH\n";
        if(p[0] == 'R')
            rg += 10;
        else bg += 10;
        return; // 撒花~~
    }
}
```

### 全代码

[代码太长鸟，就放这里了](https://www.luogu.com.cn/paste/u3wp8ihn)

---

## 作者：lihongqian__int128 (赞：0)

# CF1970F3 Playing Quidditch (Hard)题解
就比中等版本多了一个金色飞贼，记录它的位置，抓球时判断是否抓住了金色飞贼即可。


```cpp
#include <bits/stdc++.h>
using namespace std ;
int t , n , m , x[25] , y[25] , c[25] , ga[100][100] , qx , qy , a , b , yx , yy , fx , fy ;
string p , s ;
char op ;
int f(string str)
{
	return str[1] - '0' + 1 + (str[0] == 'R') * 10 ;
}
string q(int x)
{
	string tmp = (x < 11 ? "B" : "R") ;
	tmp += char((x - 1) % 10 + '0') ;
	return tmp ;
}
int main()
{
	cin >> n >> m ;
	for(int i = 1 ; i <= n ; i++)
		for(int j = 1 ; j <= m ; j++)
		{
			cin >> s ;
			if(s == ".Q")	qx = i , qy = j ;//记录魁地奇球的位置
			else if(s == ".B")	yx = i , yy = j ;//记录游走球的位置
			else if(s == ".S")	fx = i , fy = j ;//记录金色飞贼的位置
			else if(s == "RG")	ga[i][j] = 1 ;//球门
			else if(s == "BG")	ga[i][j] = 2 ;//球门
			else if(s[0] != '.')	x[f(s)] = i , y[f(s)] = j ;
		}
	cin >> t ;
	for(int i = 1 ; i <= t ; i++)
	{
		cin >> p >> op ;
		if(op == 'U')//移动
		{
			if(p == ".Q")	qx-- ;
			else if(p == ".S")	fx-- ;
			else if(p == ".B")
			{
				yx-- ;
				for(int j = 1 ; j <= 20 ; j++)	if(x[j] == yx && y[j] == yy)	cout << i - 1 << ' ' << q(j) << " ELIMINATED\n" ;//判断是否有人装上了游走球
			}
			else
			{
				x[f(p)]-- , qx -= c[f(p)] ;
				if(x[f(p)] == yx && y[f(p)] == yy)	cout << i - 1 << ' ' << p << " ELIMINATED\n" ;//判断这个人是否装上了游走球
			}
		}
		if(op == 'D')//移动
		{
			if(p == ".Q")	qx++ ;
			else if(p == ".S")	fx++ ;
			else if(p == ".B")
			{
				yx++ ;
				for(int j = 1 ; j <= 20 ; j++)	if(x[j] == yx && y[j] == yy)	cout << i - 1 << ' ' << q(j) << " ELIMINATED\n" ;//判断是否有人装上了游走球
			}
			else
			{
				x[f(p)]++ , qx += c[f(p)] ;
				if(x[f(p)] == yx && y[f(p)] == yy)	cout << i - 1 << ' ' << p << " ELIMINATED\n" ;//判断这个人是否装上了游走球
			}
		}
		if(op == 'L')//移动
		{
			if(p == ".Q")	qy-- ;
			else if(p == ".S")	fy-- ;
			else if(p == ".B")
			{
				yy-- ;
				for(int j = 1 ; j <= 20 ; j++)	if(x[j] == yx && y[j] == yy)	cout << i - 1 << ' ' << q(j) << " ELIMINATED\n" ;//判断是否有人装上了游走球
			}
			else
			{
				y[f(p)]-- , qy -= c[f(p)] ;
				if(x[f(p)] == yx && y[f(p)] == yy)	cout << i - 1 << ' ' << p << " ELIMINATED\n" ;//判断这个人是否装上了游走球
			}
		}
		if(op == 'R')//移动
		{
			if(p == ".Q")	qy++ ;
			else if(p == ".S")	fy++ ;
			else if(p == ".B")
			{
				yy++ ;
				for(int j = 1 ; j <= 20 ; j++)	if(x[j] == yx && y[j] == yy)	cout << i - 1 << ' ' << q(j) << " ELIMINATED\n" ;//判断是否有人装上了游走球
			}
			else
			{
				y[f(p)]++ , qy += c[f(p)] ;
				if(x[f(p)] == yx && y[f(p)] == yy)	cout << i - 1 << ' ' << p << " ELIMINATED\n" ;//判断这个人是否装上了游走球
			}
		}
		if(op == 'C')//抓住球或飞贼
		{
			cin >> s ;
			if(s == ".Q")	c[f(p)] = 1 ;
			else//这个人抓住了金色飞贼
			{
				if(p[0] == 'R')	b += 10 , cout << i - 1 << " RED CATCH GOLDEN SNITCH\n" ;
				else	a += 10 , cout << i - 1 << " BLUE CATCH GOLDEN SNITCH\n" ;
				break ;
			}
		}
		if(op == 'T')//放下球
		{
			c[f(p)] = 0 ;
			if(ga[x[f(p)]][y[f(p)]] == 1)
			{
				cout << i - 1 << " BLUE GOAL\n" ;
				a++ ;
				qx = (n + 1) / 2 , qy = (m + 1) / 2 ;
			}
			if(ga[x[f(p)]][y[f(p)]] == 2)
			{
				cout << i - 1 << " RED GOAL\n" ;
				b++ ;
				qx = (n + 1) / 2 , qy = (m + 1) / 2 ;
			}
		}
	}
	cout << "FINAL SCORE: " << b << ' ' << a ;//输出
	return 0 ;
}
```

---

## 作者：OIer_Hhy (赞：0)

[CF1970F1 Playing Quidditch (Easy)](https://www.luogu.com.cn/article/z9upawaj)

[CF1970F2 Playing Quidditch (Medium)](https://www.luogu.com.cn/article/j9ekahc5)

有了前两题的经验，这道题就太轻松了。

仍然用 `map` 记录坐标，`map[".S"]` 表示金色飞贼的坐标。 

当有人抓到金色飞贼时（选手的坐标和飞贼的坐标重叠）直接退出就行了。

My Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t;
string a[110][110],s;
struct node{
	int x,y; 
};
map<string,node> mp; // mp表示位置 
map<string,bool> haveQ;// 鬼飞球 
short c[10010]; // c[i]=1 表示 第i秒R进球，c[i]=2表示第i秒R进球
vector<string> d[10010]; // d[i] 表示 第i秒被淘汰的人 
int blue,red;  
node middle;
signed main(){
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
		if(player!=".B"){
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
				string thing;
				cin>>thing; 
				if(thing==".Q")
					haveQ[player]=1; 
				else{
					if(player[0]=='R'){
						cout<<i<<" RED CATCH GOLDEN SNITCH\n";
						red+=10;
						break;
					}else{
						cout<<i<<" BLUE CATCH GOLDEN SNITCH\n";
						blue+=10;
						break;
					}
					
				}
			}
			node axisB=mp[".B"];
			if(axisB.x==axis.x&&axisB.y==axis.y){
				d[i].push_back(player);
				haveQ[player]=0;
			}
			if(haveQ[player]) mp[".Q"]=axis;
		}else{
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
			}
			for(int t=0;t<2;t++){
				string tmp="00";
				if(t) tmp[0]='B';
				else tmp[0]='R'; 
				for(int j=0;j<10;j++){
					tmp[1]=char(j+48);
					node axisp=mp[tmp];
					if(axisp.x==axis.x&&axisp.y==axis.y)
						d[i].push_back(tmp); 		
				}
			}
			
		}
		sort(d[i].begin(),d[i].end());
		for(int j=0;j<d[i].size();j++) cout<<i<<' '<<d[i][j]<<" ELIMINATED\n";
		
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

## 作者：EXODUS (赞：0)

# Part 1：前言

一个不是很恶心的小模拟。

# Part 2：正文

这里只提及一些模拟的细节。

- 由于到后面的版本，球和球，球和人以及人和人之间会重合，所以尽量使用坐标存下每个点的位置，而不是直接在原地图上模拟。
- 在 F2、F3 版本中，每个球员只会被淘汰一次。所以球员被淘汰时要及时打上标记，避免重复淘汰。
- 注意除 Bludger 以外，Quaffle、Golden Snitch 均会移动（不是兄弟你家球自己会动啊？[流汗黄豆]），而这一点似乎在题面里没有提及，所以要维护这些东西的移动。
- Bludger 走到某个节点时，可能同时淘汰多个球员，所以按照题目中的顺序判断每一个球员是否被淘汰。
- 如果你使用了一个新集合存下了球员的位置，注意在球员移动的同时移动集合中球员的位置。
- 如果你的写法下标从 0 开始，所以不存在 Bludger 时需要将其位置设为一个界外位置。

# Part 3：代码

尝试了一下面向对象的写法，但是由于是自己编的所以可能不那么面向对象呃。

```cpp
// I'll be dancing like nobody is watching
// 我翩跹而舞好似身旁空无一人
// And I wanna be all you need for a second
// 那一瞬 我只想属于你一人
// 'Cause I'm into you
// 只因我对你一见倾心
// Now I'm trying to get your attention
// 此刻 我希望引起你的关注
// So I'm calling you up on my best intentions
// 所以还不死心 打电话给你
// 'Cause I'm into you
// 因我钟情于你
// I'm into you
// 沦陷于你

#include<bits/stdc++.h>
using namespace std;

int n,m;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
int round_cnt;

struct goal_t{
	int x,y;
	bool belong;
	goal_t(){x=y=0,belong=-1;}
	goal_t(int _x,int _y,int _belong):x(_x),y(_y),belong(_belong){}
};
struct player_t{
	int x,y,idx;
	bool catching_quaffle,eliminated;
	player_t(){x=y=0,idx=-1,catching_quaffle=false;eliminated=true;}
	player_t(int _x,int _y,int _idx,bool _catching_quaffle,bool _eliminated):
		x(_x),y(_y),idx(_idx),catching_quaffle(_catching_quaffle),eliminated(_eliminated){}
	void move(int dir){
		x+=dx[dir],y+=dy[dir];
	}
	bool operator ==(const player_t& rhs)const{
		return idx==rhs.idx;
	}
};
struct quaffle_t{
	int x,y;
	bool catched;
	void move(int dir){
		x+=dx[dir],y+=dy[dir];
	}
};
struct bludger_t{
	int x,y;
	bludger_t(){x=y=-1;}
	void move(int dir){
		x+=dx[dir],y+=dy[dir];
	}
};

struct golden_snitch_t{
	int x,y;
	golden_snitch_t(){x=y=-1;}
	void move(int dir){
		x+=dx[dir],y+=dy[dir];
	}
};

struct team_t{
	player_t player[10];
	int score;
};

team_t team[2];
vector<tuple<int,int,int>>event;

void score(quaffle_t& quaffle,goal_t& goal){
	assert(!quaffle.catched&&quaffle.x==goal.x&&quaffle.y==goal.y);
	event.emplace_back(round_cnt,goal.belong^1,0);
	quaffle.x=n/2,quaffle.y=m/2;
	team[goal.belong^1].score++;
}

void throw_quaffle(player_t& player,quaffle_t& quaffle,vector<goal_t>& goal_set){
	assert(player.catching_quaffle&&quaffle.catched);
	assert(player.x==quaffle.x&&player.y==quaffle.y);
	player.catching_quaffle=0;
	quaffle.catched=0;
	for(auto& goal:goal_set)
		if(goal.x==quaffle.x&&goal.y==quaffle.y){
			score(quaffle,goal);
			break;
		}
}

void eliminate(bludger_t& bludger,player_t& player,quaffle_t& quaffle){
	assert(bludger.x==player.x&&bludger.y==player.y);
	event.emplace_back(round_cnt,2+(player.idx<0),abs(player.idx)-1);
	if(player.catching_quaffle){
		vector<goal_t>goal_set;
		throw_quaffle(player,quaffle,goal_set);
	}
	player.eliminated=true;
}

void move(player_t& player,quaffle_t& quaffle,bludger_t& bludger,int dir){
	player.move(dir);
	if(player.catching_quaffle&&quaffle.catched){
		quaffle.move(dir);
		assert(player.x==quaffle.x&&player.y==quaffle.y);
	}
	if(player.x==bludger.x&&player.y==bludger.y){
		eliminate(bludger,player,quaffle);
	}
}

void move(quaffle_t& quaffle,int dir){
	assert(!quaffle.catched);
	quaffle.move(dir);
}

void move(golden_snitch_t& golden_snitch,int dir){
	golden_snitch.move(dir);
}

void move(bludger_t& bludger,quaffle_t& quaffle,vector<player_t>& player_set,int dir){
	bludger.move(dir);
	vector<player_t>lis;
	for(auto& player:player_set){
		if(bludger.x==player.x&&bludger.y==player.y){
			eliminate(bludger,player,quaffle);
		}
	}
}

void catch_quaffle(player_t& player,quaffle_t& quaffle){
	assert(!player.catching_quaffle&&!quaffle.catched);
	assert(player.x==quaffle.x&&player.y==quaffle.y);
	player.catching_quaffle=1;
	quaffle.catched=1;
}

void catch_golden_snitch(player_t& player,golden_snitch_t& golden_snitch){
	assert(player.x==golden_snitch.x&&player.y==golden_snitch.y);
	team[player.idx<0].score+=10;
	event.emplace_back(round_cnt,4+(player.idx<0),0);
}

vector<player_t> get_player_set(){
	vector<player_t>player_set;
	for(int i=0;i<10;i++){
		if(!team[0].player[i].eliminated)
			player_set.emplace_back(team[0].player[i]);
	}
	
	for(int i=0;i<10;i++){
		if(!team[1].player[i].eliminated)
			player_set.emplace_back(team[1].player[i]);
	}
	return player_set;
}


vector<goal_t>goal_set;
quaffle_t quaffle;
bludger_t bludger;
golden_snitch_t golden_snitch;

int main(){
	// cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			string s;
			cin>>s;
			if(s[0]=='B'&&s[1]=='G')goal_set.emplace_back(i,j,0);
			if(s[0]=='R'&&s[1]=='G')goal_set.emplace_back(i,j,1);
			if(s[0]=='B'&&isdigit(s[1]))
				team[0].player[s[1]-'0'].x=i,team[0].player[s[1]-'0'].y=j,
				team[0].player[s[1]-'0'].idx=s[1]+1-'0',team[0].player[s[1]-'0'].eliminated=false;
			if(s[0]=='R'&&isdigit(s[1]))
				team[1].player[s[1]-'0'].x=i,team[1].player[s[1]-'0'].y=j,
				team[1].player[s[1]-'0'].idx=-(s[1]+1-'0'),team[1].player[s[1]-'0'].eliminated=false;
			if(s[1]=='B')
				bludger.x=i,bludger.y=j;
			if(s[1]=='Q')
				quaffle.x=i,quaffle.y=j;
			if(s[1]=='S')
				golden_snitch.x=i,golden_snitch.y=j;
		}
	int T;
	cin>>T;
	for(int i=0;i<T;i++){
		string s;
		cin>>s;
		if(s[0]=='B'||s[0]=='R'){
			player_t& current_player=(s[0]=='B'?team[0].player[s[1]-'0']:team[1].player[s[1]-'0']);
			char opt;
			cin>>opt;
			if(opt=='U')move(current_player,quaffle,bludger,0);
			if(opt=='D')move(current_player,quaffle,bludger,1);
			if(opt=='L')move(current_player,quaffle,bludger,2);
			if(opt=='R')move(current_player,quaffle,bludger,3);
			if(opt=='C'){
				string ball;
				cin>>ball;
				if(ball[1]=='Q'){
					catch_quaffle(current_player,quaffle);
				}
				if(ball[1]=='S'){
					catch_golden_snitch(current_player,golden_snitch);
					break;
				}
			}
			if(opt=='T'){
				throw_quaffle(current_player,quaffle,goal_set);
			}
		}else if(s[1]=='Q'){
			char opt;
			cin>>opt;
			if(opt=='U')move(quaffle,0);
			if(opt=='D')move(quaffle,1);
			if(opt=='L')move(quaffle,2);
			if(opt=='R')move(quaffle,3);
		}else if(s[1]=='B'){
			vector<player_t>player_set=get_player_set();
			char opt;
			cin>>opt;
			if(opt=='U')move(bludger,quaffle,player_set,0);
			if(opt=='D')move(bludger,quaffle,player_set,1);
			if(opt=='L')move(bludger,quaffle,player_set,2);
			if(opt=='R')move(bludger,quaffle,player_set,3);
		}else if(s[1]=='S'){
			char opt;
			cin>>opt;
			if(opt=='U')move(golden_snitch,0);
			if(opt=='D')move(golden_snitch,1);
			if(opt=='L')move(golden_snitch,2);
			if(opt=='R')move(golden_snitch,3);
		}
		++round_cnt;
		// cout<<team[1].player[0].x<<' '<<team[1].player[0].y<<' '<<golden_snitch.x<<' '<<golden_snitch.y<<'\n';
	}
	for(auto [rnd,evt,idx]:event){
		if(evt==0)
			cout<<rnd<<" BLUE GOAL\n";
		if(evt==1)
			cout<<rnd<<" RED GOAL\n";
		if(evt==2)
			cout<<rnd<<" B"<<idx<<" ELIMINATED\n";
		if(evt==3)
			cout<<rnd<<" R"<<idx<<" ELIMINATED\n";
		if(evt==4)
			cout<<rnd<<" BLUE CATCH GOLDEN SNITCH\n";
		if(evt==5)
			cout<<rnd<<" RED CATCH GOLDEN SNITCH\n";
	}
	cout<<"FINAL SCORE: "<<team[1].score<<' '<<team[0].score<<'\n';
	return 0;
}
```

---

