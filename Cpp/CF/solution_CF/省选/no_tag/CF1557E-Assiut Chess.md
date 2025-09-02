# Assiut Chess

## 题目描述

This is an interactive problem.

ICPC Assiut Community decided to hold a unique chess contest, and you were chosen to control a queen and hunt down the hidden king, while a member of ICPC Assiut Community controls this king.

You compete on an $ 8\times8 $ chessboard, the rows are numerated from top to bottom, and the columns are numerated left to right, and the cell in row $ x $ and column $ y $ is denoted as $ (x, y) $ .

In one turn you can move the queen to any of the squares on the same horizontal line, vertical line, or any of the diagonals. For example, if the queen was on square ( $ 4 $ , $ 5 $ ), you can move to ( $ q_1 $ , $ 5 $ ), ( $ 4 $ , $ q_1 $ ), ( $ q_1 $ , $ 9-q_1 $ ), or ( $ q_2 $ , $ q_2+1 $ ) where ( $ 1 \le q_1 \le 8 $ , $ q_1 \ne 4 $ , $ 1 \le q_2 \le 7 $ , $ q_2 \ne 4 $ ). Note that the queen cannot stay on its current cell.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1557E/98fc96b13e619e875242afc4fec289e7ef23aa4d.png)In one turn, the king can move "Right", "Left", "Up", "Down", "Down-Right", "Down-Left", "Up-Left", or "Up-Right" such that he doesn't get out of the board. The king cannot move into a cell that is on the same row, column or diagonal with the queen (including the position of the queen itself). For example, if the king was on square ( $ 4 $ , $ 5 $ ), he can move to ( $ 4+k_1 $ , $ 5+k_2 $ ) where ( $ -1 \le k_1,k_2 \le 1 $ , $ (k_1, k_2) \ne (0, 0) $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1557E/868e0fd195f7050098110890f61abc44d30b284c.png)At the start of the game, you should place the queen at any location on the board, and this is done once per game. After that the king is secretly placed at any cell different from the queen's location. You do not know the position of the king. Then, the king and the queen take turns with the king moving first. The king moves to one of the possible directions ("Right", "Down", "Up-Left", etc.), and you are only given the direction it moves to. After that, you should move your queen by declaring the square to which your queen will move. The game follows like this until you win the game or run out of moves.

You win if the king has no valid moves. You lose if after $ 130 $ moves of the queen the king still has valid moves.

## 说明/提示

In the example, the hidden king was at $ (8, 8) $ at the start. The game follows like this:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1557E/c803112a415698a590e340aaa8aa8d531bf7e5ed.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1557E/a45c792f12bda0c5a15e31a80c55652777a5408c.png)

## 样例 #1

### 输入

```
1
Left
Right
Done```

### 输出

```
7 5
7 6
7 7```

# 题解

## 作者：huayucaiji (赞：11)

## 前言

这篇题解可能会和普通题解不太一样，会很“生动”，希望大家喜欢~

## 解题思路

我们的主角是国王（K）和王后（Q），那就把舞台交给他们吧！

旁白：这一天王后发现国王藏私房钱，于是决定抓住他（什么辣鸡剧情啊喂！）。国王和王后移动方式见题目，国王率先进入棋盘，选择了一个位置，现在王后进场了……

Q：哼，反正我的攻击距离远，让让他。我就在 $(1,1)$ 好啦。**反正不管哪个位置开始，我都能抓住他。**

K：别说大话！

Q：等着瞧！我现在不知道你在哪里，**但我只要保证你一直在我下方就可以了！**我该什么时候下移呢？如果我在 $i$ 行，这个糟老头子在 $i+1$ 行，那么我往下，他可以往上，所以，**我一定要确保我和他的距离在 $2$ 行以上才能向下一行**。怎么做到这一点呢？真实伤脑筋。

K：嘿嘿！你抓不到我的！你就慢慢想吧！我先走一步喽！

Q：啊！我知道了，只要我从这一行 $(i,1)$ 位置出发，每次把这一行巡逻一遍，**由于国王没法移动两格，一定一直在我的右边**，为了不被我抓住，一定会向下逃走的！一旦他向下，我就向下，你跑不了！

旁白：A few moments later.

K：坏了，再这样下去，我一定会输的，她最多只需要 $8*8=64$ 步就够了。我不能一直往下，我可以先跑到离她相对较远的地方，然后往上到 $i+1$ 行！这样她就乱了阵脚了哈哈哈。只要我往上，她就没办法。

Q：糟了，这该怎么办？**我不知道他现在是否在 $i+1$​ 行，只能再巡逻一次了**，但是他一直这样往怎么办，我的步数就要变成了 $(8+x)*8$​ 次了（$x$​ 表示 K 往上的次数）。不对，**$x$ ​好像是有范围的，他最多只能往上 $7$ 次**，那么我的巡逻次数最多是 $120$ 次。老娘完全不虚你~

旁白：最后王后抓住了国王，拿回了他的钱。The End！！！

不知道这样的形式怎么样，我也不知道怎么心血来潮就写成这样了。。。。

**反正核心思想就是关注国王的竖向移动，一旦往下，我们就往下，一旦往上，我们就重新巡逻这一行，由于国王最多往上 $7$ 次，我们一定抓得住他。**至于为什么是 $7$ 次，~~读者自证不难~~

## 代码

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int MAXN=131;

int n,pos;

string PLA(int x,int y) {
	if(x==0||y==0) {
		puts("???");
	}
	//please let me know the answer (((
	printf("%d %d\n",x,y);
	pos=y;
	//fflush(stdout);
	string s;
	cin>>s;
	return s;
}

bool patrol(int x) {
	for(int i=(pos==1? 2:1);i<=8;i++) {
		string s=PLA(x,i);
		if(s=="Done") {
			return 1;
		}
		if(s[0]=='D') {
			return 0;
		}
		if(s[0]=='U') {
			return patrol(x);
		}
	}
	return 0;
} 
void work() {
	pos=1;
	for(int i=1;i<=8;i++) {
		if(PLA(i,pos)=="Done") {
			return ;
		}
		if(patrol(i)) {
			return ;
		}
	}
}

signed main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	
	int t=read();
	
	while(t--) {
		work(); 
	}  


	//fclose(stdin);
	//fclose(stdout);
	return 0;
}


```



---

## 作者：Kubic (赞：9)

这一个可以踩标算的做法。

考虑维护一个 $8\times 8$ 的 $01$ 矩阵表示当前国王可能在的位置，目标即为把它变成全 $0$。

初始将皇后放在 $(1,1)$。

假设当前皇后的位置为 $(x,y)$，那么考虑两种情况：

- 如果第 $x+1$ 行没有 $1$，那么让皇后走到 $(x+1,y)$。

- 如果第 $x+1$ 行有 $1$，设为 $(x+1,p)$，那么让皇后走到 $(x,p)$。

重复这个过程即可。

**正确性证明：**

设 $\phi_1$ 为剩下 $1$ 的个数，$\phi_2=8-x$。

- 如果第 $x+1$ 行没有 $1$，此时我们花费 $1$ 步的代价使 $\phi_2$ 减少 $1$。

- 如果第 $x+1$ 行有 $1$：

  - 如果国王的行动是 `Down-Left` 或者 `Down-Right`，那么此时第 $x+1$ 行一定没有 $1$，于是下一步中皇后会走到 $(x+1,y)$。此时我们花费 $2$ 步的代价使 $\phi_2$ 减少 $1$。

  - 如果不是，那么说明原来的 $(x+1,p)$ 位置一定不是国王。此时我们花费 $1$ 步的代价使 $\phi_1$ 减少至少 $1$。
  
初始 $\phi_1=63,\phi_2=7$，因此这个算法的理论步数上界为 $\phi_1+2\phi_2=77$。实际上这个上界根本不可能达到，不进行任何细节优化的情况下在官方数据下 $20$ 步以内完全能够解决，大部分都在 $15$ 步以内。

此算法的细节处还有可以进行优化的地方（没有必要）：

- 如果有多行都全 $0$，直接全部跳过。

- 第二种情况中如果国王的行动是 `Down-Left` 或者 `Down-Right`，那么直接模仿它的行动。

代码写的很丑陋，放上来有失优美性（

真的看懂了的话代码实现一点难度都没有吧（

---

## 作者：KaisuoShutong (赞：5)

# CF1557E Assiut Chess

自闭彩笔不会交互。

## 题意

**交互题。**  
给了你一张 $8\times8$ 棋盘和一个皇后一个国王。你控制皇后，电脑控制国王。开始时，你可以随意将皇后放置在棋盘上，国王会在你放置后由电脑放置，但你并不知道国王的位置。

国王先执棋。请你在 $130$ 步内将死国王。棋子的移动规则参考国际象棋。

## 题解

首先要说明的是，这题的交互器很不高明，hack 机制似乎也很拉胯，所以一大堆乱搞可以过。

本文阐述的是官方的正解。

不妨考虑一颗棋子将死对方的办法。似乎唯一的就是将其逼到棋盘四周。  
四周？为了不让它~~乱说乱动~~，最好的地方就是四个角落。

算一下 $130$ 大约是 $8\times 8$ 的两倍，也就是说皇后可以经过每个格子至少一次。

有了以上提示，我们就~~能~~想出这样的做法。

最开始，皇后被放置在 $(1,1)$ 的位置上。随着国王的第一步，国王一定在第 $2$ 行及以下。

设当前皇后在第 $i$ 行。我们让皇后向下逼近国王。  

1. 如果国王不在第 $i+1$ 行而在第 $(i+2)-8$ 行，皇后直接向下移动一行。
2. 如果国王在第 $i+1$ 行，如果直接向下，国王就可以向上了。所以不妨让皇后沿着 $1-8$ 列走一遍。这样其一定会起身躲避，那么因为第 $i$ 行被皇后控制，所以一定向下。此时再向下就没问题了。


这样我们就有了详细策略：  
沿着当前行，遍历所有列。如果发现国王向下移动，立刻也向下。否则在遍历完后向下。

但这样看似完美的策略实则有个大问题。如果国王在第 $i+2$ 行，我们动着动着他就向上移了一下，你就迷惑了，万一他在你刚刚遍历过的地方呢？所以我们选择重来一遍，重头再走。根据势能，他向上动的总势能只有 $6$，每动一次消耗 $1$ 的势能，所以只有最多 $6\times8$ 的步数被消耗。所以总共是 $6\times8+8\times8=112$ 左右的步数，可以通过。

实现上大概会有 $8$ 左右的边角询问。

**参考**代码：

```cpp
//月亮照耀青窗，窗里窗外皆有青色的光。
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
int f[10];
signed main() {
	for(int i=1;i<9;i++) f[i]=i;
	int cas;cin>>cas;
	while(cas--) {
		cout<<1<<' '<<1<<endl;cin>>s;if(s=="Done") goto ED;
		for(int i=1,j=1;i<9;) {
			char ic=0,lic=0;//changed i or not
			char uc=0;//went up or not
			if(j^f[1]) reverse(f+1,f+9);
			for(int k=2;k<9;k++) {
				cout<<i<<' '<<f[k]<<endl;cin>>s;
				if(s=="Done") goto ED;
				if(s[0]=='U') uc=1;
				else if(s[0]=='D') ic=1,lic=k,uc=0,++i;
			}j=f[8];
			if(!uc&&!ic) ++i;
			if(!uc&&(!ic||(lic==8))) {
				while(233) {
					cout<<i<<' '<<j<<endl;cin>>s;if(s=="Done") goto ED;
					if(s[0]=='D') ++i;else break;
				}
			}
		}ED:;
	}
	return 0;
}
```

---

## 作者：Saliеri (赞：4)

大家好，这里是一个因为一个傻逼错误调了两个半小时这题的屑。

___

上午 vp 了这场，胡出了一个奇怪的做法，很难写，但是比较好想？

- 好像 CF 讨论区里有这个做法（

___

Q1：如果我们确切地知道国王在哪一格，给出将死它的策略。

A1：先将王后移到国王所在的行，然后保持后在王的角处，这样一定可以逼死王。

详细解释：我们先这么走，王一定会离开这一行。

![1.png](https://s2.loli.net/2022/03/01/eajsvPQWp6ruTGZ.png)

- 可能会是其他位置关系，但是对称的，不重要。

然后我们保持这样一个位置关系，王怎么走后怎么走，一定可以逼到角落：

![1.png](https://s2.loli.net/2022/03/01/UKxle7C1fLQ6JSY.png)

这样单次将死王非常松的上界是 14 步，可以卡常，但是代码中没有实现。

Q2：我们不是不知道王在哪里吗？

A2：考虑这样一个事情，每一次后走到一个位置，都可以使得一些位置上保证没有王，后只要走的步数足够多，那么王可能在的位置也会足够少。

- 为了防 Hack，我们让后**随机**游走。按实际数据测试，只需要随机 8 步就可以让王的位置集合足够小。

于是这个题就做完了。

这种做法细节很多，相比较官方正解很难写，但是在 CF 的测试数据中将死王的步数均小于 20 步。

___

Code：写的是真的 s**t，不喜勿喷。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
using namespace std;
int ban[10][10],tmp[10][10];
int T,X,Y;string op;
int R(int l,int r){return rand()%(r-l+1)+l;}
map<string,pii> dlt;
void gVis(pii pos,vector<pii> &Vec){
	for(int i=1;i<=8;++i)
		if(i != pos.first)Vec.push_back(make_pair(i,pos.second));
	for(int i=1;i<=8;++i)
		if(i != pos.second)Vec.push_back(make_pair(pos.first,i));
	for(int i=1;i<=8;++i)
		if(i != pos.first){
			int y1 = pos.second+(i-pos.first),y2 = pos.second-(i-pos.first);
			if(1 <= y1 && y1 <= 8)Vec.push_back(make_pair(i,y1));
			if(1 <= y2 && y2 <= 8)Vec.push_back(make_pair(i,y2));
		}
}
bool CHECK(int nx,int ny){
	if(nx < 1 || nx > 8 || ny < 1 || ny > 8)return 0;
	if(X == nx && Y == ny)return 0;
	if(X == nx || Y == ny)return 1;
	else if(X+Y == nx+ny)return 1;
	else if(X-Y == nx-ny)return 1;
	else return 0;
}
vector <pii> legal;
bool Checkmate(pii pos){
	if(pos.first < 1 || pos.first > 8 || pos.second < 1 || pos.second > 8)return 0;
	if(X != pos.first)
		cout << (X = pos.first) << ' ' << Y << endl;
	else return 0;
	pii dis = make_pair(0,Y>pos.second?1:-1),delta = make_pair(0,0);
	while(1){
		cin >> op;
		if(op == "Done")return 1;
		pii d = dlt[op];
		pos.first += d.first,pos.second += d.second;
		delta.first += d.first,delta.second += d.second;
		if(!dis.first){
			dis.first = -d.first;
			if(d.first == 0)break;
		}
		else if(d.first == dis.first || d.second == dis.second || (d.first == -dis.first && d.second == -dis.second))break;
		int nx = pos.first+dis.first,ny = pos.second+dis.second;
		if(!CHECK(nx,ny))break;
		cout << (X = nx) << ' ' << (Y = ny) << endl; 
	}
	for(pii &p:legal)p.first += delta.first,p.second += delta.second;
	return 0;
}
int main(){
	srand(time(0));
	cin >> T;
	dlt["Left"] = make_pair(0,-1);
	dlt["Right"] = make_pair(0,1);
	dlt["Up"] = make_pair(-1,0);
	dlt["Down"] = make_pair(1,0);
	dlt["Down-Right"] = make_pair(1,1);
	dlt["Up-Right"] = make_pair(-1,1);
	dlt["Up-Left"] = make_pair(-1,-1);
	dlt["Down-Left"] = make_pair(1,-1);
	while(T--){
		X = R(1,8),Y = R(1,8);
		memset(ban,0,sizeof(ban));
		int CNT = 8,FLAG = 0;
		while(CNT--){
			cout << X << ' ' << Y << endl;
			cin >> op;if(op == "Done"){FLAG = 1;break;}
			int dx = dlt[op].first,dy = dlt[op].second;
			for(int i=1;i<=8;++i)
				for(int j=1;j<=8;++j)
					tmp[i][j] = ban[i-dx][j-dy];
			memcpy(ban,tmp,sizeof(tmp));
			for(int i=1;i<=8;++i)
				for(int j=1;j<=8;++j)
					if(i-dx > 8 || i-dx < 1 || j-dy > 8 || j-dy < 1)
						ban[i][j] = 1;
			vector<pii> to;
			gVis(make_pair(X,Y),to);
			for(pii pos:to)ban[pos.first][pos.second] = 1;
			int rp = R(0,to.size()-1);
			if(CNT)X = to[rp].first,Y = to[rp].second;
		}
		if(FLAG)continue;
		legal.clear();
		for(int i=1;i<=8;++i)
			for(int j=1;j<=8;++j)
				if(!ban[i][j])legal.push_back(make_pair(i,j));
		for(pii pos:legal)
			if(Checkmate(pos))break;
	}
	return 0;
}
```



---

## 作者：周子衡 (赞：3)

我们考虑用后逐渐限制王的活动范围，从而最后杀王。

先把后放到左上角。我们考虑逐步把王向下逼，这样把王逼到最后一行后就可以直接杀王。

假设现在后处在第 $i$ 行，那么王必然处在 $\geq i+1$ 的某一行。我们如果能确定王处在 $\geq i+2$ 的行，那么就可以把后向下走一步，进入下一个阶段。我们发现，只要王往左下、右下、下走了任何一步，那么它必然不在第 $i+1$ 行，我们直接把后往下走即可。

假如王在第 $i+1$ 行左右走，我们怎么把它逼下去呢？可以发现，我们只要在 $(i,1)$，$(i,3)$，$(i,5)$，$(i,7)$ 分别走一次后，那么王不可能再在第 $i+1$ 行走下去。这样我们便能再往下逼一步。

还剩下一个小问题：如果王趁着后在巡逻第 $i$ 行的时候偷偷上来怎么办？这也是很好解决的。只要侦测到王向上，我们立刻重新进行巡逻。由于王只能下 $7$ 步，所以至多也只能上 $7$ 步，这样并不会耗费过多的步数。

综上我们边解决了本题。

---

## 作者：hgcnxn (赞：0)

## CF1557E Assiut Chess题解

### 思路

观察步数限制。$130>2\times 8\times 8$，我们大概可以让后遍历棋盘两次。

一个比较显然的思路是初始时将后摆在第一行，将后所在的那一行遍历一遍，保证国王不能待在下一行，从而不断将国王往下赶。但是，国王可能在后往下走的时候往上逃，而这是我们需要避免的。

假设后从某一行的第一列开始，依次遍历了改行的所有格子。如果在遍历时，国王往下移动，那么他一定不在下一行，后是可以直接向下移动，去遍历下一行。事实上，在后遍历的过程中，国王一定要离开下一行至少一次，或者国王最初根本不在下一行。所以，如果在遍历时国王始终不向上移动，那么他也一定不在下一行，后可以去下一行。

如果国王在遍历过程中向上移动怎么办？此时，我们因该从头开始，重新遍历这一行。由于国王每向下移动一次，后也会向下移动一次，所以国王至多从第 $8$ 行移动到第 $2$ 行，也就是最多向上移动 $6$ 次。那么，我们至多需要 $8\times 8+6\times 8=112$ 次移动即可将杀国王，就算实现不太好，也绰绰有余。

事实上，代码实现不难，故不放我丑陋的代码了。

---

## 作者：intel_core (赞：0)

注意到 $130>2\times 8^2$，意味着我们大概可以把棋盘扫两遍。

这启发我们采用地毯式搜索，从第一行开始一直往下扫。

然后发现这种搜索方式有个 bug，在扫第 $k$ 行时如果国王一直在第 $k+2$ 行苟着，然后在我们将要去扫 $k+1$ 行时突然向上走到第 $k$ 行，那么就前功尽弃了。

因此国王向上的时候必须足够警惕，具体来说在扫完 $k$ 行时必须确保国王不在 $k+1$ 行，然后才能向下。如果国王突然向上，那我们只能在第 $k$ 行接着扫。

只要在国王往下的时候我们也跟进，就能不断压缩国王的空间，从而保证扫描的次数。

因为我们无论如何都不会往上，一行最多只会扫两次，因此次数是对的。

---

## 作者：张晟轩 (赞：0)

## 题目分析：
思路：从点 $(1,1)$ 开始，使王一直在后的下方。从 $1$ 开始扫描每一行，保证王不在下一行后走到下一行。  
对于第 $row$ 行，从 $(row,1)$ 开始往右走一格，直到走到 $(row,8)$，能保证王一直在后的左边。若途中遇到 `Down`，说明王一定不在 $row+1$ 行，走到下一行。若中途遇到 `Up`，则在往左移动后王不一定在右边，重新扫描这一行。  
总共最多出现 $7$ 次 `Up`，所以询问次数最多为 $7\times8+7\times8<130$。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,col;
string s;
void mov(int x,int y){
	printf("%d %d\n",x,y);
	col=y;
	cin>>s;
}//查询
int scan(int row){
	for(int c=(col==1?2:1);c<=8;++c){
		mov(row,c);
		if(s=="Done") return true;
		if(s=="Down") return false;
		if(s=="Up") return scan(row);
	}
	return false;
}//扫描每一行
int main(){
	scanf("%d",&T);
	while(T--){
		col=1;
		for(int row=1;row<=7;row++){
			mov(row,col);
			if(col!=1){
				if(s=="Done") break;
				col=1;mov(row,col);
			}
			//若 col!=1, 令 col=1, 从最左端开始
			if(s=="Done") break;
			if(scan(row)) break;
		}
	}
	return 0;
}

```

---

