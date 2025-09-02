# Playing Quidditch (Medium)

## 题目描述

今天下午，你决定出门感受春天的气息。当你走到魁地奇球场附近时，突然听到有人大喊。果然，又是在争谁赢了比赛！为了避免这一情况再次发生，你决定参与到比赛的判罚当中。

你留在体育场观看比赛，并记录得分。比赛结束时，你将宣布获胜者。

今天参赛的两支队伍是：红色的格兰芬多（R）和蓝色的拉文克劳（B）。每队有 $P$ 名球员（$1 \leq P \leq 10$）。

场地是一个 $N$ 行 $M$ 列的矩形（$3 \leq N, M \leq 99$，$N$ 和 $M$ 均为奇数）。所有位置都是整数值，并且允许多个实体同时位于同一位置。比赛开始时，场地上有两队的球门（每队有一个到五个球门）、球员以及一个鬼飞球。在这一版本的问题中，可能还会出现一个游走球。而在更难的版本中，还会有另一种球。

比赛由 $T$ 个步骤组成（$0 \leq T \leq 10000$）。每一步中，场上的一个实体（球员或者球）都会执行一个动作。所有实体都可以移动。球员还可以接球或者投掷手中的鬼飞球。要接球，球员必须与球处于同一格子。当球员持有鬼飞球时，鬼飞球不会进行任何动作，只是随球员一起移动。如果球员决定投出鬼飞球，它将留在球员当前的位置。如果球员和游走球同时处于同一格子（无论是球员移动还是游走球移动导致的结果），该球员将被淘汰。如果球员被淘汰时正持球，鬼飞球将留在原地，与淘汰球员和游走球同处一格。可以保证不会在球员位于球门时发生这种情况。

想要得分，球员必须将鬼飞球放在对方的球门。当球员得分时，该球员的队伍获得一分，鬼飞球将立即移动至场地中央（从1开始计数的第 $(N+1)/2$ 行、第 $(M+1)/2$ 列）。中央没有球门。如果球员把球放进自家球门，那对方队伍将获得一分。

## 说明/提示

在第一个例子中，红队球员拿起鬼飞球，移动并投出。蓝队球员接住球，向红队球门进攻并取得分数。

在第二个例子中，红队球员拿球并不小心把它投入自家球门，结果蓝队得分。

在第三个例子中，游走球移动到 `R0` 的位置，导致 `R0` 被淘汰。随后，`B0` 也移到游走球的位置，结果 `B0` 也被淘汰。

 **本翻译由 AI 自动生成**

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

# 题解

## 作者：FFTotoro (赞：2)

[点这里前往游记。](https://www.luogu.com.cn/article/u3edqf6r)

本来觉得这种大模拟挺无聊的，但是昨晚补题的时候发现把赛时 F1 的 AC 代码改一改不仅过了 F2，还同时抢到了 F1 F2 最短解，于是决定写一下 F2 的题解供参考。

因为题目保证了所有操作合法，所以我们记录需要的信息即可，如下：

- 每个球员 / 球（在 F2 中包含鬼飞球 Quaffle 和游走球 Bludger）的位置，使用 `std::map<std::string,std::pair<int,int> >` 存储；
- 红方得分和蓝方得分，在进球时给对应的得分 $+1$ 即可；

当游走球 Bludger 移动到某一个位置时，扫一遍 `map`，如果这个位置有球员就按顺序把这个位置上的全部球员淘汰（由于 `map` 自动对第一关键字排序所以扫到直接输出即可）；当某个球员移动到某一个位置时，如果 Bludger 在上面那么就将他淘汰掉。

如果你 WA on Test 5 并且数组下标和我一样是从 $0$ 开始的，那么注意，**场上可能没有 Bludger**，此时如果一个球员到了 $(0,0)$ 的位置，判断该位置上有没有 Bludger 时，因为 `map` 没有存储 Bludger 的信息，所以查出来的值也是 $(0,0)$，如果你直接判相等就寄了。

剩下细节参考代码注释。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int n,m,cr=0,cb=0; cin>>n>>m;
  vector a(n,vector<string>(m));
  for(auto &i:a)for(auto &j:i)cin>>j;
  map<string,pair<int,int> > s; // map 用来记录位置
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
      s[a[i][j]]=make_pair(i,j); // 记录初始位置
  int q; cin>>q;
  for(int i=0;i<q;i++){
    string w; char op; cin>>w>>op;
    auto &[x,y]=s[w];
    switch(op){
      case 'C':cin>>w; break;
        // 这个操作在 F2 没啥意义，因为可以接的球只有一种
      case 'U':x--; break; // 往上走
      case 'D':x++; break; // 往下走
      case 'L':y--; break; // 往左走
      case 'R':y++; break; // 往右走
      default:
        if(a[x][y][1]=='G'){
          if(a[x][y][0]=='R')cout<<i<<" BLUE GOAL\n",cb++;
          else cout<<i<<" RED GOAL\n",cr++;
        } // 扔球，统计得分
    } // 按操作分类
    if(w==".B"){
      for(auto [p,l]:s)
        if(p[0]!='.'&&l==s[w]) // 特判 .Q 的情况
          cout<<i<<' '<<p<<" ELIMINATED\n";
    } // 游走球到了某个位置，淘汰该位置上所有球员
    else if(w!=".Q"){
      if(s.find(".B")!=s.end()&&s[".B"]==s[w])
        cout<<i<<' '<<w<<" ELIMINATED\n";
    } // 球员到了某个位置，判断有没有鬼飞球
      // 如果有再判断一下位置对不对
  }
  cout<<"FINAL SCORE: "<<cr<<' '<<cb<<endl;
  return 0;
}
```

---

## 作者：JOE_ZengYuQiao_0928 (赞：2)

### [先看题](https://vjudge.net.cn/problem/CodeForces-1970F2#author=GPT_zh)
### 思路分析
本题是一道大模拟。

在输入时，我们可以将各个球员以及游走球的位置全部记录下来，后面进行移动时，再将各个球员和游走球的位置进行变化即可。

每次进球时，球员都会进行操作 $T$，那么我们只需要在球员进行 $T$ 操作时看看这位球员是给红队还是给蓝队进球了即可。

每次淘汰人，必须是在进行过一次移动之后，所以我们可以在进行完一次移动之后，再看看每个球员的位置，如果跟游走球位置一样，就可以被淘汰了。

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

# CF1970F2 Playing Quidditch （Medium）题解
## [传送门](https://www.luogu.com.cn/problem/CF1970F2)
## 题目大意
红色的格兰芬多队 $R$ 和蓝色的拉文克劳队 $B$ 比赛每队有 $1$ 到 $10$ 名队员。
 
场地是一个 $N$ 行 $M$ 列的矩形，场地上有球门、球员、一个鬼飞球和一个游走球。
 
比赛有 $T$ 步，每一步一个实体动作，球员可以移动、抓球或投球，游走球可以移动，抓住球时，鬼飞球跟随球员移动；投球时，鬼飞球被放在球员当前位置。

如果球员和游走球在同一位置（但在球门不会）就会被淘汰，当携带鬼飞球被淘汰时，鬼飞球会留当前位置。
 
将球放入对方球门，该队伍得一分，球移动到场地中央。如果将球放入自己球门，对方队伍得分。
## 思路
比 Easy 版多了一个游走球，~~和 Easy 版一样水~~。
 
用一个 `map` 类型数组记录球和球员的位置，移动时更新，因为只有在**携带**鬼飞球时才能投球，所以鬼飞球的位置可以**不用**记。

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

//检测球员是否和游走球在同一格
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
      //因为只有鬼飞球能抓，所以输入后就不用管了
    } else if (op == 'T') {
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

---

## 作者：The_foolishest_OIer (赞：0)

F2 和 F3 没什么区别吧（就是少了一个十分球）。

用几个结构体存储所有球员、球的位置和状态（甚至不用 map）。

然后先让球员移动，接着判断是否进球，最后判断是否有人被游走球重伤下场。

注意事项：

- 一分球如果有球员带着它走，那么一分球的坐标也要改变。

- 如果游走球不存在，一定要特判！

- `U` 操作要让 $x$ 坐标减 $1$，不要写反。

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
				}
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
			else if (name[1] == 'B') ball[2].x++;
		}else if (op == 'U'){
			if (name[0] == 'R') r[name[1] - '0'].x--;
			else if (name[0] == 'B') b[name[1] - '0'].x--;
			else if (name[1] == 'Q') ball[1].x--;
			else if (name[1] == 'B') ball[2].x--;
		}else if (op == 'L'){
			if (name[0] == 'R') r[name[1] - '0'].y--;
			else if (name[0] == 'B') b[name[1] - '0'].y--;
			else if (name[1] == 'Q') ball[1].y--;
			else if (name[1] == 'B') ball[2].y--;
		}else if (op == 'R'){
			if (name[0] == 'R') r[name[1] - '0'].y++;
			else if (name[0] == 'B') b[name[1] - '0'].y++;
			else if (name[1] == 'Q') ball[1].y++;
			else if (name[1] == 'B') ball[2].y++; // 移动
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
			ball[1].y = m / 2 + 1; // 重置
			cout << p << " BLUE GOAL\n";
		}
		if (a[ball[1].x][ball[1].y] == "BG" && ball[1].catcher == "no"){
			redgoal++;
			ball[1].x = n / 2 + 1;
			ball[1].y = m / 2 + 1;
			cout << p << " RED GOAL\n";
		} // 是否进球
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
			} // 是否有人被游走球打
		}
	}
	cout << "FINAL SCORE: " << redgoal << ' ' << bluegoal;
	return 0;
}
```

---

## 作者：albertting (赞：0)

## CF1970F2 题解

### 球员移动及鬼飞球相关

[这里](https://www.luogu.com.cn/article/lf2exnti)

### 游走球

书接上回。

游走球自己会跑，但是我们可以发现，它和球员的移动代码一模一样，就不用单独写啦！

只要我们在每次操作之后看一下球员有没有被砸掉下来就好了。

```cpp
void check_eliminated(string p, int t)
{
    if(p == ".B")
    {
        for(int i = 0; i <= 19; i++)
        {
            if(mp[ps[i]] == mp[".B"])
            {
                cout << t << " " << ps[i] << " ELIMINATED\n";
            }
        }
    }
    else
    {
        if(mp[p] == mp[".B"])
        {
            cout << t << " " << p << " ELIMINATED\n";
        }
    }
}
```

传参的话。。。

如果某次操作是球员进行的，那么被砸下来的只可能是他，直接判就好了。

如果是游走球的话，可能会砸下来任何一个人，所以要把所有球员给遍历一遍。

### 全代码

[代码太长鸟，就放这里了](https://www.luogu.com.cn/paste/6vi6pr04)

---

## 作者：OIer_Hhy (赞：0)

[CF1970F1 Playing Quidditch (Easy)](https://www.luogu.com.cn/article/z9upawaj)

这题比 F1 就加了一个游走球，还是很水。

还是用 `map` 数组记录坐标，当游走球的坐标与选手的坐标重叠时，该选手即被淘汰。

注意：如在同一秒淘汰多人时，要按字典序输出。

我们可以用一个 `vector<string>` 数组 `d` 来记录每一秒被淘汰的球员名单，排序后输出。

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

完结撒花

---

## 作者：Genshin_ZFYX (赞：0)

请先阅读：

[简单版本](https://www.luogu.com.cn/article/188w8lc8)

中等版本就加了一个游走球来撞人。

除了游走球自己会走动，有的人也会自己走到游走球的位置，这种情况也算这个悲催的人淘汰，所以我们干脆在每次移动（包括球员和游走球）后判断一下是否有人被淘汰。

本题解代码较为冗长且没有注释，放了也没有意义。

---

## 作者：lihongqian__int128 (赞：0)

# CF1970F2 Playing Quidditch (Medium)题解
就比简单版本多了一个游走球，记录它的位置，每次移动时判断是否有人撞到了游走球即可。


```cpp
#include <bits/stdc++.h>
using namespace std ;
int t , n , m , x[25] , y[25] , c[25] , ga[100][100] , qx , qy , a , b , yx , yy ;
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
			else if(s == "RG")	ga[i][j] = 1 ;
			else if(s == "BG")	ga[i][j] = 2 ;
			else if(s[0] != '.')	x[f(s)] = i , y[f(s)] = j ;
		}
	cin >> t ;
	for(int i = 1 ; i <= t ; i++)
	{
		cin >> p >> op ;
		if(op == 'U')//移动
		{
			if(p == ".Q")	qx-- ;
			else if(p == ".B")
			{
				yx-- ;
				for(int j = 1 ; j <= 20 ; j++)	if(x[j] == yx && y[j] == yy)	cout << i - 1 << ' ' << q(j) << " ELIMINATED\n" ;//判断是否有人撞到了游走球
			}
			else
			{
				x[f(p)]-- , qx -= c[f(p)] ;
				if(x[f(p)] == yx && y[f(p)] == yy)	cout << i - 1 << ' ' << p << " ELIMINATED\n" ;//判断这个人是否撞到了游走球
			}
		}
		if(op == 'D')//移动
		{
			if(p == ".Q")	qx++ ;
			else if(p == ".B")
			{
				yx++ ;
				for(int j = 1 ; j <= 20 ; j++)	if(x[j] == yx && y[j] == yy)	cout << i - 1 << ' ' << q(j) << " ELIMINATED\n" ;//判断是否有人撞到了游走球
			}
			else
			{
				x[f(p)]++ , qx += c[f(p)] ;
				if(x[f(p)] == yx && y[f(p)] == yy)	cout << i - 1 << ' ' << p << " ELIMINATED\n" ;//判断这个人是否撞到了游走球
			}
		}
		if(op == 'L')//移动
		{
			if(p == ".Q")	qy-- ;
			else if(p == ".B")
			{
				yy-- ;
				for(int j = 1 ; j <= 20 ; j++)	if(x[j] == yx && y[j] == yy)	cout << i - 1 << ' ' << q(j) << " ELIMINATED\n" ;//判断是否有人撞到了游走球
			}
			else
			{
				y[f(p)]-- , qy -= c[f(p)] ;
				if(x[f(p)] == yx && y[f(p)] == yy)	cout << i - 1 << ' ' << p << " ELIMINATED\n" ;//判断这个人是否撞到了游走球
			}
		}
		if(op == 'R')//移动
		{
			if(p == ".Q")	qy++ ;
			else if(p == ".B")
			{
				yy++ ;
				for(int j = 1 ; j <= 20 ; j++)	if(x[j] == yx && y[j] == yy)	cout << i - 1 << ' ' << q(j) << " ELIMINATED\n" ;//判断是否有人撞到了游走球
			}
			else
			{
				y[f(p)]++ , qy += c[f(p)] ;
				if(x[f(p)] == yx && y[f(p)] == yy)	cout << i - 1 << ' ' << p << " ELIMINATED\n" ;//判断这个人是否撞到了游走球
			}
		}
		if(op == 'C')//抓住球
		{
			cin >> s ;
			c[f(p)] = 1 ;
		}
		if(op == 'T')//放下球
		{
			c[f(p)] = 0 ;
			if(ga[x[f(p)]][y[f(p)]] == 1)//进球
			{
				cout << i - 1 << " BLUE GOAL\n" ;
				a++ ;
				qx = (n + 1) / 2 , qy = (m + 1) / 2 ;
			}
			if(ga[x[f(p)]][y[f(p)]] == 2)//进球
			{
				cout << i - 1 << " RED GOAL\n" ;
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

