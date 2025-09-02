# Sweets Game

## 题目描述

Karlsson has visited Lillebror again. They found a box of chocolates and a big whipped cream cake at Lillebror's place. Karlsson immediately suggested to divide the sweets fairly between Lillebror and himself. Specifically, to play together a game he has just invented with the chocolates. The winner will get the cake as a reward.

The box of chocolates has the form of a hexagon. It contains 19 cells for the chocolates, some of which contain a chocolate. The players move in turns. During one move it is allowed to eat one or several chocolates that lay in the neighboring cells on one line, parallel to one of the box's sides. The picture below shows the examples of allowed moves and of an unacceptable one. The player who cannot make a move loses.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF63E/d39dc87a25b4bbc8e9ef90055ec2e2d8c38df358.png)Karlsson makes the first move as he is Lillebror's guest and not vice versa. The players play optimally. Determine who will get the cake.

## 样例 #1

### 输入

```
  . . .
 . . O .
. . O O .
 . . . .
  . . .
```

### 输出

```
Lillebror```

## 样例 #2

### 输入

```
  . . .
 . . . O
. . . O .
 O . O .
  . O .
```

### 输出

```
Karlsson```

# 题解

## 作者：xuchenhao2008 (赞：3)

### 题面翻译
有一个 19 个点组成的的六边形巧克力盒子，现在 Karlsson 和 Lillebror 在玩游戏， Karlsson 先手，每次可以取走在一条直线上连续的任意个数的巧克力。

输入这个盒子，用 'O' 表示巧克力， '.' 表示空位，数据保证盒子里只少有一颗巧克力；输出获胜者的名字。
### [AC记录（754ms/8.02MB）(目前洛谷最优解）](https://www.luogu.com.cn/record/70075076)


------------

### 思路点拨
首先，看到这道题目，我们可以将题面转换一下：

- 输入一个六边形的图，在同一条直线上的 'O' 是联通的
- 小K和小L依次将一条任意长度的联通 'O' 删除
- 当前玩家如果没有 'O' 可以删除，那他就输了
- 询问小K是否有**必胜策略**

于是，我们不难想到这道题可以运用**递归**的思想。每次当前玩家吃掉一定的巧克力之后，询问**另一位玩家对于剩下的巧克力，是否有必胜策略**，如果无论怎么吃巧克力，对手都有必胜策略，那么当前玩家对于当前状态的巧克力是必输的；否则如果对手有一种情况下不存在必胜策略（即必输），则当前玩家对于当前状态的巧克力存在必胜策略。

那么，这道题有些细节处理：

- 我们如何最大效率地存储剩余巧克力的状态？——（使用状态压缩）
- 我们如何模拟斜着吃的情况？ —— （用数组进行预先处理）
- 我们如何判断越界的问题？——（用数组进行预先处理）

最后，可以看一下我的完整代码，里面注释非常详细（从第112行看起）。时间复杂度最坏情况下是  _O（2*(2^19)）_ 

### 代码展示
```cpp
#include<bits/stdc++.h>

#pragma GCC optimize(3)

#define inf 0x7fffffff
#define INF 4611686018427387904
#define ll long long
#define pb push_back
#define dir4 dx[5]={-1,0,1,0},dy[5]={0,1,0,-1}
#define dir8 dx[10]={-1,-1,-1,0,1,1,1,0},dy[10]={-1,0,1,-1,-1,0,1,1}
#define dirh dx[10]={-2,-2,-1,1,2,2,1,-1},dy[10]={-1,1,2,2,1,-1,-2,-2}
#define rep(i,l,x) for(int i=l;i<x;i++)
#define repd(i,l,x) for(int i=l;i>=x;i--)
#define repn(i,l,x) for(int i=l;i<=x;i++)
#define xend putchar('\n')
#define xspace putchar(' ')
#define read2(a,b) a=read(),b=read()
#define read3(a,b,c) a=read(),b=read(),c=read()
#define read4(a,b,c,d) a=read(),b=read(),c=read(),d=read()
#define Lread2(a,b) a=Lread(),b=Lread()
#define Lread3(a,b,c) a=Lread(),b=Lread(),c=Lread()
#define Lread4(a,b,c,d) a=Lread(),b=Lread(),c=Lread(),d=Lread()
#define write4(a,b,c,d) write(a),xspace,write(b),xspace,write(c),xspace,write(d),xspace
using namespace std;
char gc(){//Do not read '\n' ' '
	char _ch=getchar();
	while(_ch=='\n'||_ch==' ') _ch=getchar();
	return _ch;
}
inline void Sread(char _SSS[]){
	char _ch=getchar();
	rep(i,0,10)
	if(_ch=='\n'||_ch==' ') _ch=getchar();
	else break;
	rep(i,0,inf){
		_SSS[i]=_ch;
		if((_ch=getchar())=='\n'||_ch==' ') return;
	}
}
inline int read(){
	int _res=0,_ch,_flag=0;
	if((_ch=getchar())=='\n') _ch=getchar();
	if(_ch=='-') _flag=1;
	else if(_ch>='0'&&_ch<='9') _res=_ch-'0';
	while((_ch=getchar())>='0'&&_ch<='9')
		_res=_res*10+_ch-'0';
	return _flag?-_res:_res;
}
inline ll Lread(){
	ll _res=0,_ch,_flag=0;
	if((_ch=getchar())=='\n') _ch=getchar();
	if(_ch=='-') _flag=1;
	else if(_ch>='0'&&_ch<='9') _res=_ch-'0';
	while((_ch=getchar())>='0'&&_ch<='9')
		_res=_res*10+_ch-'0';
	return _flag?-_res:_res;
}
inline void write(int _x){
	if(_x<0){
		putchar('-');
		_x=-_x;
	}
	if(_x>9) write(_x/10);
	putchar(_x%10+'0');
}
inline void Lwrite(ll _x){
	if(_x<0){
		putchar('-');
		_x=-_x;
	}
	if(_x>9) write(_x/10);
	putchar(_x%10+'0');
}
inline void Swrite(char _SSS[]){
	rep(i,0,strlen(_SSS)) putchar(_SSS[i]);
}
int gcd(int _fnum,int _snum){
	if(_snum!=0) return gcd(_snum,_fnum%_snum);
	else return _fnum;
}
ll Lgcd(ll _fnum,ll _snum){
	if(_snum!=0) return Lgcd(_snum,_fnum%_snum);
	else return _fnum;
}
int lcm(int _fnum,int _snum){
	return _fnum*_snum/gcd(_fnum,_snum);
}
ll Llcm(ll _fnum,ll _snum){
	return _fnum*_snum/Lgcd(_fnum,_snum);
}
float getDis(float _sx, float _sy, float _ex, float _ey){
	//The distance between two dots in Cartesian coordinates.
	return sqrt((_sx-_ex)*(_sx-_ex)+(_sy-_ey)*(_sy-_ey));
}
bool checkOverlap(int sx1,int sy1,int ex1,int ey1,int sx2,int sy2,int ex2,int ey2){
	// True for two areas overlapped.
	// sx<=ex,sy<=ey
	if(!(sx1<=ex1))swap(sx1,ex1);
	if(!(sx2<=ex2)) swap(sx2,ex2);
	if(!(sy1<=ey1)) swap(sy1,ey1);
	if(!(sy2<=ey2)) swap(sy2,ey2);
	return !((sx1>ex2)||(ex1<sx2)||(sy1>ey2)||(ey1<sy2));
}
void ChessRead(int &fnum, int &snum){
	fnum=gc()-'a';
	snum=8-(gc()-'0');
}
int cf_t;


//程序代码从这边开始 
const int maxn=(1<<19)+1;
int vis[3][maxn]={},ans[maxn]={};//vis数组的第二维和ans数组的第一维都用状态压缩来存储当前剩余的巧克力 
//row[i]表示第i块巧克力位于的行数(i从0开始)，len[row[i]]表示某一行的长度，pre[row[i]]表示某一行之前所有巧克力的总数 
int len[7]={0,3,4,5,4,3},pre[7]={0,0,3,7,12,16},boost[6]={0,4,5,5,4},deboost[5]={0,3,4,4,3},row[20]={1,1,1,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5};
 
int dfs(int pl,int cur){//pl用来表示当前是哪个玩家进行游戏，cur状态压缩存储当前剩余的巧克力 
	//加入记忆化，如果当前cur状态下有必胜策略，则返回pl(pl玩家可以获胜)；如果是必输的，则返回1-pl(pl玩家必定输) 
	if(ans[cur]==1) return pl;
	else if(ans[cur]==-1) return 1-pl;
	
	int to,res=1-pl;
	if(cur==0) return res;//如果没有巧克力了，依照题意，pl玩家就输了 
	
	rep(st,0,19){//枚举巧克力的位置，状态压缩即（1<<st) 
		if((cur & (1<<st))==0) continue;//如果当前位置没有巧克力则continue
		 
			to=cur;//横着吃巧克力 
			for(int i=st;i<pre[row[st]]+len[row[st]];i++){
				if((to & (1<<i))==0) break;//为了保证"eat one or several chocolates that lay in the neighboring cells on one line" 
				to-=(1<<i);//吃掉巧克力 
				if(vis[1-pl][to]==0){
					vis[1-pl][to]=1;
					res=dfs(1-pl,to);//询问在吃掉这么多巧克力的情况下，对手是否有必胜策略 
					vis[1-pl][to]=0;
					if(res==pl){ 
						ans[cur]=1;//如果对手没有必胜策略，则我方必定有必胜策略
						return res;
					}
					
				}
			}
			
			to=cur;//从左上往右下吃 
			for(int i=st;;){//同理 
				if((to & (1<<i))==0) break;
				to-=(1<<i);
				if(vis[1-pl][to]==0&&i!=st){
					vis[1-pl][to]=1;
					res=dfs(1-pl,to);
					vis[1-pl][to]=0;
					if(res==pl){
						ans[cur]=1;
						return res;
					}
					
				}
				if(row[i]==5) break;//如果吃到了最后一行就不可能继续往下吃了 
				if(i+boost[row[i]]>=pre[row[i]+1]+len[row[i]+1]) break;//判断越界 
				i+=boost[row[i]];//boost[row[i]]表示从当前往右下斜着吃，i的坐标需要增加多少 
			}
			
			to=cur;//从右上往左下吃 
			for(int i=st;;){//同理 
				if((to & (1<<i))==0) break;
				to-=(1<<i);
				if(vis[1-pl][to]==0&&i!=st){
					vis[1-pl][to]=1;
					res=dfs(1-pl,to);
					vis[1-pl][to]=0;
					if(res==pl){
						ans[cur]=1;
						return res;
					}
					
				}
				if(row[i]==5) break;
				if(i+deboost[row[i]]<pre[row[i]]+len[row[i]]) break;
				i+=deboost[row[i]];//deboost[row[i]]表示从当前往左下斜着吃，i的坐标需要增加多少 
			}
		}
		ans[cur]=-1;//当前cur不存在必胜策略——即无论怎样吃，对手都有必胜策略。 
		return res;//返回对手存在必胜策略 
}
void solve(){
	int orgi=0;
	rep(i,0,19) if(gc()==79) orgi+=(1<<i);//状态压缩 
	vis[0][orgi]=1;
	int res=dfs(0,orgi);
	printf((res==0)?"Karlsson":"Lillebror");
}
int main(){
/*	 //Online_Judge
	   freopen("input.txt","r",stdin);
	   freopen("output.txt","w",stdout);
*/

	cf_t=1;//scanf("%d",&cf_t);
	while(cf_t--) solve();

	return 0;
}





```



---

## 作者：Elairin176 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF63E)    
因为题面是本人重置的，故不再重复题面。   
## 解法
注意到一共只有 19 的点，故我们考虑状压 dp。  
将每个点的状态压成二进制，预处理可以取的所有情况即可。     
时间复杂度为 $\mathcal{O}(2^n)$，$n$ 为点数，本题为 $19$。

```cpp
//luogu paste jo5j6ogx
char c[15][15];
int t,tot,mp[15][15],len[10]={0,3,4,5,4,3},st[10]={0,3,2,1,2,3};
il int get(int sx,int sy,int x,int y,int t,int len){
//	write(sx);spe;write(sy);spe;write(x);spe;write(y);spe;
	int ans=0;
	for(int i=0;i<len;i++){
		if(t&(1<<i)) ans|=(1<<mp[sx][sy]);
		sx+=x,sy+=y;	
	}
//	bwrite(t,len);spe;bwrite(ans,tot);edl;
	ret ans;
}
vector<int>ok;
int f[(1<<20)+1];
il bool dfs(int x){
	if(f[x]!=-1) ret f[x];
	for(auto i:ok){
		if((i&x)==i&&(!dfs(x^i))){
			ret f[x]=1;
		}
	}
	ret f[x]=0;
}
il bool check(int x,int len){
	bool b=0;
	int l=0;
	for(int i=0;i<len;i++){
		if((1<<i)&x){
			if(!b) b=1;
			else if(!l) ret 0;
		}
		l=(1<<i)&x;
	}
	ret 1;
}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	memset(f,-1,sizeof(f));
	for(int i=1;i<=5;i++){
		for(int j=1;j<=len[i];j++){
			c[i][st[i]+(j-1)*2]=readc();
			if(c[i][st[i]+(j-1)*2]=='O'){
				t|=(1<<tot);
			}
			mp[i][st[i]+(j-1)*2]=tot++;
		}
	}
	for(int i=1;i<(1<<3);i++){
		if(!check(i,3)) continue;
		ok.push_back(get(1,3,0,2,i,3));
		ok.push_back(get(1,3,1,-1,i,3));
		ok.push_back(get(1,7,1,1,i,3));
		ok.push_back(get(3,1,1,1,i,3));
		ok.push_back(get(3,9,1,-1,i,3));
		ok.push_back(get(5,3,0,2,i,3));
	}
	for(int i=1;i<(1<<4);i++){
		if(!check(i,4)) continue;
		ok.push_back(get(1,5,1,-1,i,4));
		ok.push_back(get(1,5,1,1,i,4));
		ok.push_back(get(4,2,0,2,i,4));
		ok.push_back(get(2,2,0,2,i,4));
		ok.push_back(get(2,2,1,1,i,4));
		ok.push_back(get(2,8,1,-1,i,4));
	}
	for(int i=1;i<(1<<5);i++){
		if(!check(i,5)) continue;
		ok.push_back(get(1,3,1,1,i,5));
		ok.push_back(get(1,7,1,-1,i,5));
		ok.push_back(get(3,1,0,2,i,5));
	}
	if(dfs(t)){
		write("Karlsson");
	}else{
		write("Lillebror");
	}
	ret 0;
}
```

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
给定一个长度为 $3$ 的正六边形的棋盘，若为 $O$ 则表示这个位置有糖果。

两人轮流吃糖果，每次可以选择在一条直线上的任意个糖果吃，不能吃的人为败者。
## 分析
首先就是博弈论，状态压缩，记忆化搜索，启动！

这题规模非常非常的小，可以考虑直接爆搜。因为我比较懒，所以爆搜就是最好的方法，但是建议你们自己去想更好的方法因为某些题可能规模特大。

首先对棋盘的每个位置标号，若位置 $i$ 有 $O$，就用一个二进制数的第 $i$ 为 $1$ 表示出来。

搜索过程中，如果转移过去的状态不是当前状态的子集，显然是不行的，break 就行。

假设转移过去的 $O$ 标号是 $k$，那么只需标记 $k$ 左移一位表示拿走了这个糖果。
## 代码

```cpp
#include <bits/stdc++.h>//大量位运算形成的视觉盛宴，请慢用。
using namespace std;
const int dx[]={0,1,1};
const int dy[]={2,1,-1};
int mp[15][15];
int dp[1<<21];
int solve(int mask) {
    if(!mask) return 0;
    if(dp[mask]!=-1) return dp[mask];
    dp[mask] = 1;
    for(int x=0;x<5;x++)
        for(int y=0;y<9;y++){
            if(mp[x][y]==-1) continue;
            for(int i=0;i<3;i++){
                int tmp=mask;
                for(int xx=x,yy=y;xx<5&&xx>=0&&yy<9&&yy>=0;xx+=dx[i],yy+=dy[i]) {
                    if(mp[xx][yy]==-1) break;
                    int k=mp[xx][yy];
                    if((tmp&(1<<k))==0) break;
                    tmp^=1<<k;
                    dp[mask]&=solve(tmp);
                }
            }
        }
    return dp[mask]^=1;
}
int main() {
    memset(dp,-1,sizeof dp);
    memset(mp,-1,sizeof mp);
    int k=0;
    for(int i=2;i<=6;i+=2) mp[0][i]=k++;
    for(int i=1;i<=7;i+=2) mp[1][i]=k++;
    for(int i=0;i<=8;i+=2) mp[2][i]=k++;
    for(int i=1;i<=7;i+=2) mp[3][i]=k++;
    for(int i=2;i<=6;i+=2) mp[4][i]=k++;
    int mask=0;
    string s;
    for(int i=0;i<5;i++) {
        getline(cin,s);
        for(int j=0; j<s.length();j++)
            if(s[j]=='O') mask|=1<<mp[i][j];
    }
    if(solve(mask)) puts("Karlsson");
    else puts("Lillebror");
}
```

---

