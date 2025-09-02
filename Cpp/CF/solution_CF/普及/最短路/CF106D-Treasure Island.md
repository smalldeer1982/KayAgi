# Treasure Island

## 题目描述

我们勇敢的旅行者到达一个岛上，海盗在那里埋下了财宝。然而，当船即将停泊时，船长发现藏宝图被老鼠吃掉了一部分。

藏宝图可以表示为一个大小为$n\times m$的网格图。每个单元格代表地图上的一块正方形（正方形的边长等于一英里）。有些单元格代表海洋，它们是不可达的。所有其他单元格都是可达的，其中一些单元格有视野。

此外，地图还有一套共$k$个指令。每个指令的格式如下：“沿$y$方向走$n$英里”

可能的方向有：北、南、东和西。如果你仔细地遵循这些指示（你应该一个接一个地完成所有的指示），那么你应该准确地到达埋藏宝藏的地方。

不幸的是，船长不知道从哪个单元格开始执行指令，因为地图上的那一部分已经丢失了。但是船长很清楚地记得那个单元格有视野。另外，船长知道整个过程都经过岛上的可达单元格。

船长想知道哪些单元格值得一看。

## 样例 #1

### 输入

```
6 10
##########
#K#..#####
#.#..##.##
#..L.#...#
###D###A.#
##########
4
N 2
S 1
E 1
W 2
```

### 输出

```
AD```

## 样例 #2

### 输入

```
3 4
####
#.A#
####
2
W 1
N 2
```

### 输出

```
no solution```

# 题解

## 作者：ikunTLE (赞：10)

[题目传送门](https://www.luogu.com.cn/problem/CF106D)

### 思路

本题可以在**前缀和**的优化下模拟通过。由于每一次只会在直线上走，我们只需要预处理每一行和每一列可以走的路长。在模拟期间，就可以使用前缀和判断其路程中是否全是可以走的。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e3+10,M=1e5+10;
struct node{
	int x,y;
};vector<node>vc;
int n,m,r[N][N],c[N][N],op[M],len[M],
dx[]={0,-1,1,0,0},dy[]={0,0,0,-1,1};
char s[N][N];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		scanf("%s",s[i]+1);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			if(s[i][j]>='A'&&s[i][j]<='Z')
				vc.push_back({i,j});
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			r[i][j]=r[i][j-1]+(s[i][j]!='#');
			c[i][j]=c[i-1][j]+(s[i][j]!='#');
		}
	int T=read();
	for(int i=1;i<=T;++i){
		char ch[1];
		scanf("%s",ch);
		len[i]=read();
		if(ch[0]=='N')
			op[i]=1;
		else if(ch[0]=='S')
			op[i]=2;
		else if(ch[0]=='W')
			op[i]=3;
		else op[i]=4;
	}
	string ans="";
	for(auto it:vc){
		int bx=it.x,by=it.y;
		int x=it.x,y=it.y;
		bool flag=true;
		for(int i=1;i<=T;++i){
			int xx=x+dx[op[i]]*len[i];
			int yy=y+dy[op[i]]*len[i];
			if(xx<=0||xx>n||yy<=0||yy>m){
				flag=false;
				break;
			}
			int min_x=min(x,xx),min_y=min(y,yy);
			int max_x=max(x,xx),max_y=max(y,yy);
			if(op[i]>=3){
				if(r[max_x][max_y]-r[min_x][min_y-1]!=len[i]+1)
					flag=false;
			}
			else if(c[max_x][max_y]-c[min_x-1][min_y]!=len[i]+1)
				flag=false;
			if(!flag)
				break;
			x=xx,y=yy;
		}
		if(flag)
			ans+=s[bx][by];
	}
	if(ans.empty())
		cout<<"no solution\n";
	else{
		sort(ans.begin(),ans.end());
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：小明小红 (赞：3)

# CF106D题解

## 解法一（假）
这道题十分简单，只需要**遍历**每个起点的 $k$ 次操作，每次操作**暴力枚举**一个点一个点跳过去就可以了，献上代码。
### fake-code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,q;
char mapp[1009][1009];
ll dirr[4][2]= {{-1,0},{0,1},{1,0},{0,-1}};

struct operate {
	ll dir,dis;
} e[100009];
bool check(ll x,ll y) {
	for(ll i=1; i<=q; i++) {
		for(ll j=1; j<=e[i].dis; j++) {
			x=x+dirr[e[i].dir][0];
			y=y+dirr[e[i].dir][1];
			if(mapp[x][y]=='#') {
				return 0;
			}
		}
	}
	return 1;
}
int main() {
	cin>>n>>m;
	for(ll i=1; i<=n; i++) {
		for(ll j=1; j<=m; j++) {
			cin>>mapp[i][j];
		}
	}
	cin>>q;
	char c;
	for(ll i=1; i<=q; i++) {
		cin>>c>>e[i].dis;
		if(c=='N') {
			e[i].dir=0;
		}
		if(c=='E') {
			e[i].dir=1;
		}
		if(c=='S') {
			e[i].dir=2;
		}
		if(c=='W') {
			e[i].dir=3;
		}

	}
	string ans="";
	for(ll i=1; i<=n; i++) {
		for(ll j=1; j<=m; j++) {
			if(mapp[i][j]>='A'&&mapp[i][j]<='Z') {
				if(check(i,j)==1) {
					ans+=mapp[i][j];

				}
			}
		}
	}
	for(ll i=0; i<ans.size(); i++) {
		for(ll j=i+1; j<ans.size(); j++) {
			if(ans[i]>ans[j]) {
				swap(ans[i],ans[j]);
			}
		}
	}
	if(ans=="") {
		cout<<"no solution";
	} else {
		cout<<ans;
	}
	return 0;
} 
```
交上去，这代码竟然 $TLE$ 了，吓得我连忙看了一眼**数据大小**。这个算法的时间复杂度应为 $O(sk\max(n,m))$,其中 $s$ 指的是**起点个数**。而当三个值都为最大时，也就是 $s=26$，$k=10^5$，$\max(n,m)=10^3$ 时，该算法要执行高达 $26\times10^5\times10^3$ 次运算，也就是 $2.6\times10^9$ 次运算，直接原地**超时**，那么如何**优化**此算法？
## 解法二（真）
**思路**：我们采用**前缀和**优化方式。

**定义**：我们定义两个二维数组 $ans1$ 和 $ans2$，$ans1[i][j]$ 表示第 $i$ 行**前** $j$ 个位置共含有障碍物**的个数**，$ans2[i][j]$ 表示第 $i$ 列**前** $j$ 个位置共含有障碍物的**个数**。 

**如何优化原算法**：当我们要从 $(1,5)$ 走到 $(1,7)$ 时只需要看 $ans1[1][7]-ans1[1][4]$ **是否为零**就可以了，同理当我们要从 $(1,5)$ 走到 $(3,5)$ 时只需要看 $ans2[5][3]-ans1[5][0]$ **是否为零**即可，下面给出真正的代码。
### real-code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,q,kkk,ans1[2009][2009],ans2[2009][2009],viis[209];
char mapp[2009][2009];
ll dirr[4][2]= {{-1,0},{0,1},{1,0},{0,-1}};//提前处理方向 

struct operate {
	ll dir,dis;
} e[100009];
bool check(ll x,ll y) {
	ll tx,ty;
	for(ll i=1; i<=kkk; i++) {

		tx=x+dirr[e[i].dir][0]*e[i].dis;//求这次操作完到的节点 
		ty=y+dirr[e[i].dir][1]*e[i].dis;
		if(e[i].dir==0||e[i].dir==2) {//纵向前缀和优化 
			ll p=x;
			x=tx;
			y=ty;
			if(p>tx) {
				swap(p,tx);
			}
			if(ans2[y][tx]-ans2[y][p-1]!=0) {
				return 0;
			}
		} else {//横向前缀和优化 
			ll q=y;
			x=tx,y=ty;
			if(q>ty) {
				swap(q,ty);
			}
			if(ans1[x][ty]-ans1[x][q-1]!=0) {
				return 0;
			}
		}
	}
	return 1;
}
int main() {
	cin>>n>>m;
	for(ll i=1; i<=n; i++) {
		for(ll j=1; j<=m; j++) {
			cin>>mapp[i][j];
		}
	}
	for(ll i=1; i<=n; i++) {
		for(ll j=1; j<=m; j++) {
			ans1[i][j]=ans1[i][j-1];//横向前缀和优化 
			if(mapp[i][j]=='#') {
				ans1[i][j]++;
			}

		}
	}
	for(ll i=1; i<=m; i++) {
		for(ll j=1; j<=n; j++) {
			ans2[i][j]=ans2[i][j-1];//纵向前缀和优化 
			if(mapp[j][i]=='#') {
				ans2[i][j]++;
			}
		}
	}
	cin>>kkk;
	char c;
	for(ll i=1; i<=kkk; i++) {
		cin>>c>>e[i].dis;
		if(c=='N') {//处理方向，存储 
			e[i].dir=0;
		}
		if(c=='E') {
			e[i].dir=1;
		}
		if(c=='S') {
			e[i].dir=2;
		}
		if(c=='W') {
			e[i].dir=3;
		}

	}
	ll flag=0;
	for(ll i=1; i<=n; i++) {
		for(ll j=1; j<=m; j++) {
			if(mapp[i][j]>='A'&&mapp[i][j]<='Z') {
				if(check(i,j)==1) {
					flag=1;
					viis[mapp[i][j]-'A'+1]++;//标记可行起点 
				}
			}
		}
	}
	if(flag==0) {
		cout<<"no solution";//如果没有被标记过，说明没有起点适合 
	} else {
		for(ll i=1; i<=26; i++) {
			if(viis[i]==1) { 
				cout<<char('A'+i-1);//输出被标记的起点 
			}
		}
	}
	return 0;
}
```


---

## 作者：lizulong (赞：1)

## 题意
有一个 $n$ 行 $m$ 列的图，```#``` 不可走；```.``` 可走。所有大写字母为起点，有 $k$ 条命令，如果能从起点一直执行，说明该起点合法，否则不合法。按**字典序**输出所有合法起点，没有则输出 ```no solution```。

## 思路
模拟加前缀和优化。

对于每一个起点，模拟所走的路程，看途中是否有不合法操作（走到 ```#``` 上或超出边界）。如果全都执行完毕，记录并枚举下一点。
## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
#define L 27
#define M 1005
using namespace std;  
int len[N],sx[L],sy[L],ans[L];  
char a[M][M],turn[N];  
signed main()
{  
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);  
	int cnt=0,n,m,k,i,j,t;
	bool flagt=0;  
	cin>>n>>m;  
	for(i=1;i<=n;i++) for(j=1;j<=m;j++)
	{  
		cin>>a[i][j];  
		if(isupper(a[i][j])) sx[++cnt]=i,sy[cnt]=j;
	}
	cin>>k;
	for(i=1;i<=k;i++) cin>>turn[i]>>len[i];  
	for(t=1;t<=cnt;t++)//每个字母进行搜索 
	{  
		int x=sx[t],y=sy[t],t1;  
		bool flag=0,flag2=0;  
		for(t1=1;t1<=k;t1++) //四方向搜索 
		{   
			flag2=0;  
			if(turn[t1]=='N')
			{  
				x-=len[t1];   
				if(x<=0) {flag=1;break;}  
				for(i=x;i<=x+len[t1];i++) if(a[i][y]=='#') {flag2=1;break;}  
			}   
			else if(turn[t1]=='S')
			{  
				x+=len[t1];    
				if(x>n){flag=1;break;}  
				for(i=x-len[t1];i<=x;i++) if(a[i][y]=='#') {flag2=1;break;}  
			}   
			else if(turn[t1]=='E')
			{   
				y+=len[t1];   
				if(y>m){flag=1;break;}    
				for(i=y-len[t1];i<=y;i++) if(a[x][i]=='#'){flag2=1;break;}    
			}    
			else
			{    
				y-=len[t1];       
				if(y<=0){flag=1;break;}
				for(i=y;i<=y+len[t1];i++) if(a[x][i]=='#'){flag2=1;break;}   
			}
			if(flag2){flag=1;break;}    
		}   
		if(!flag) ans[a[sx[t]][sy[t]]-'A'+1]=1,flagt=1;    
	}    
	if(!flagt) cout<<"no solution";//无解
	else for(i=1;i<=26;i++) if(ans[i]) cout<<(char)(i+'A'-1);
	return 0;   
}   
```


---

## 作者：Bai_R_X (赞：0)

本题是一道大模拟，但很烦。观察题意，我们首先可以想到的就是暴力枚举每一步是否会掉海。

但这样会超时，题目里写了 $len$ 在 $0\sim10^3$ 的范围内，$k$ 最大 $10^5$。$10^3×10^5=10^8$，会超时，所以我们需要用二位前缀和来计算要走的每一大步要走的距离有没有越界和有没有海。

我们便可以得出代码了：
```cpp
#include<bits/stdc++.h>
#define check if(nx<1||ny<1||nx>n||ny>m)return 
using namespace std;
int n,m,sum[1005][1005],k;
bool mp[1005][1005],f;
map<char,pair<int,int>> p;
vector<pair<char,int>> v(1);
void dfs(int x,int y,char c)
{
	for(int i=1;i<=k;i++)
	{
		int xx=v[i].second,nx=x,ny=y;
		char op=v[i].first;
		if(op=='N')
		{
			nx-=xx;
			check;
			if(sum[x][y]-sum[x][y-1]-sum[nx-1][y]+sum[nx-1][y-1])return ;
		}
		else if(op=='S')
		{
			nx+=xx;
			check;
			if(sum[nx][y]-sum[nx][y-1]-sum[x-1][y]+sum[x-1][y-1])return ;
		}
		else if(op=='W')
		{
			ny-=xx;
			check;
			if(sum[x][y]-sum[x][ny-1]-sum[x-1][y]+sum[x-1][ny-1])return ;
		}
		else
		{
			ny+=xx;
			check;
			if(sum[x][ny]-sum[x][y-1]-sum[x-1][ny]+sum[x-1][y-1])return ;
		}
		x=nx;
		y=ny;
	}
	cout<<c;
	f=1;
}
int main()
{
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			char c;
			cin>>c;
			if(c=='#')mp[i][j]=1;
			else if(c!='.')p[c]=make_pair<int,int>(move(i),move(j));
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+mp[i][j];
		}
	}
	cin>>k;
	for(i=1;i<=k;i++)
	{
		char a;
		int b;
		cin>>a>>b;
		v.push_back(make_pair<char,int>(move(a),move(b)));
	}
	for(auto& it:p)dfs(it.second.first,it.second.second,it.first);
	if(!f)cout<<"no solution";
	return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF106D Treasure Island
## 题目翻译
给定一个 $n\times m$ 的图，图上给定一些障碍和若干大写字母作为起点和若干操作（每个字母最多一次且至少一个大写字母）。每次操作给定方向和步数，求哪些字母为起点可以不撞障碍物完成所有操作，若都不行则输出 no solution。
## 隐秘的角落里隐藏着隐蔽的条件
这个题的破题点就在于大写英文字母一共 $26$ 个，于是我们可以以每个字母为起点暴力模拟其路径。\
但是有个问题，若一步一步模拟则肯定会超时，而若一次只模拟起点与终点，那么中间可能跨过障碍无法判断。\
接下来我们考虑一下一个操作若合法，仅当中间没有障碍。\
那我们可以对于每个点找到四个方向上距离它最近的点，若距离起点最近的障碍比终点还远那肯定合法，反之肯定不合法。\
找这个就比较好找了，设 $U_{ij},D_{i,j},L_{i,j},R_{i,j}$ 分别表示点 $(i,j)$ 离四个方向最近的障碍的距离，分四个方向 dp 转移即可。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,d[112345],L[1145][1145],R[1145][1145],U[1145][1145],D[1145][1145];
vector<pair<int,int> >vec;
char ch[1145][1145],op[112345];
bool flag,ANS;
string iu;
void dfs(int id,pair<int,int>dir){
    if(id==q+1)return;
    if(!flag)return;
    if(ch[dir.first][dir.second]=='#'){
        flag=0;return;
    }
    if(dir.first<1||dir.second<1||dir.first>n||dir.second>m){
        flag=0;return;
    }
    if(op[id]=='N'){
        if(d[id]>U[dir.first][dir.second]){
            flag=0;return;
        }
        dir.first-=d[id];
    }else if(op[id]=='S'){
        if(d[id]>D[dir.first][dir.second]){
            flag=0;return;
        }
        dir.first+=d[id];
    }else if(op[id]=='E'){
        if(d[id]>R[dir.first][dir.second]){
            flag=0;return;
        }
        dir.second+=d[id];
    }else{
        if(d[id]>L[dir.first][dir.second]){
            flag=0;return;
        }
        dir.second-=d[id];
    }
    dfs(id+1,dir);
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>ch[i][j];
            if(isupper(ch[i][j])){
                vec.push_back({i,j});
            }
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(ch[i][j-1]=='#')L[i][j]=0;
            else L[i][j]=L[i][j-1]+1;
        }
        for(int j=m;j>=1;--j){
            if(ch[i][j+1]=='#')R[i][j]=0;
            else R[i][j]=R[i][j+1]+1;
        }
    }
    for(int j=1;j<=m;++j){
        for(int i=1;i<=n;++i){
            if(ch[i-1][j]=='#')U[i][j]=0;
            else U[i][j]=U[i-1][j]+1;
        }
        for(int i=n;i>=1;--i){
            if(ch[i+1][j]=='#')D[i][j]=0;
            else D[i][j]=D[i+1][j]+1;
        }
    }
    cin>>q;
    for(int i=1;i<=q;++i){
        cin>>op[i]>>d[i];
    }
    for(auto p:vec){
        flag=1;
        dfs(1,p);
        if(flag){
            iu+=ch[p.first][p.second];
            ANS=1;
        }
    }
    if(!ANS)cout<<"no solution";
    else{
        sort(iu.begin(),iu.end());
        cout<<iu;
    }
    cout<<'\n';
    return 0;
}
```

---

## 作者：Dehydration (赞：0)

### 前言：

所需知识：前缀和优化，数组，模拟。

非常简单。

### 思路：

最先想到的是找出每个字母，从 $A$ 到 $Z$ 按字典序搜索，每个操作都模拟一遍，显然最 $\Theta(26\times k\times \max(n,m))=\Theta(2.6\times 10^9)$ 超时。

考虑优化，如果照这样枚举字母无法优化，每个操作也无法优化，只能将每个操作的 $\Theta(\max(n,m))$ 优化到 $\log$ 级别或者常数级别的才能过掉。

即转换成能否快速判断从一个图的一个点向 $FX$ 方向走 $LX$ 个点中间是否有障碍或是否出界。

是否出界：dfs 常规判断。

是否有障碍：用前缀和数组，记录同个方向的障碍个数，若终点障碍数与起点障碍数相同，则两点之间并无障碍。


### 细节：

首先就是存图和前缀和初始化，因为有 $4$ 个方向，但左，右本质相同，上下本质相同，只是方向反一下，所以定义两个前缀和数组，一个行一个列。

因为是要字典序输出，所以从 $A$ 到 $Z$ 记录他们的位置，代码里是 $x_i,y_i$。

初始化：

```cpp
void init(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;cin>>c;
			if(c=='#'){
				a[i][j]=-1;
			}else
			if(c=='.'){
				a[i][j]=0;
			}else
			if(c>='A'&&c<='Z'){//是有视野的
				a[i][j]=0;//有视野但也要走，是坑点
				x[c-'A'+1]=i,y[c-'A'+1]=j;
			}
		}
	}
	cin>>k;
	for(int i=1;i<=k;i++){
		cin>>fx[i]>>lc[i];//fx-->方向,lc-->路程
	}
	for(int i=1;i<=n;i++){//前缀和
		for(int j=1;j<=m;j++){
			sumx[i][j]=sumx[i-1][j]+(a[i][j]==-1);//记录的是障碍而不是空地
			sumy[i][j]=sumy[i][j-1]+(a[i][j]==-1);
		}
	}
}
```
然后就是判断是否可行。

常见坑点：前缀和是 $sum_{zd}-sum_{qd-1}$，其中 $zd$ 为终点，$qd$ 为起点，因为中间是否有障碍两头都要算。

有可能没有结果，设置一个 `Flg` 来看有没有解法即可。

然后就是判别方向一个一个来就可以了。

判断代码：

```cpp
void solve_and_print(){
	for(int i=1;i<=26;i++){
		if(!x[i]&&!y[i])continue;//x[i],y[i]分别代表 i+'A'-1 的位置
		int nowx=x[i],nowy=y[i];
		bool f=1;
		for(int j=1;j<=k;j++){
			int cjx=nowx,cjy=nowy;//等会nowx,nowy值会改变，记录原来的点
			if(fx[j]=='N'){//一一枚举即可
				nowx-=lc[j];
				if(nowx<0||sumx[nowx-1][nowy]-sumx[cjx][cjy]!=0){
					f=0;break;//f=0代表不可行，为了后面输出
				}
			}else
			if(fx[j]=='S'){
				nowx+=lc[j];
				if(nowx>n||sumx[nowx][nowy]-sumx[cjx-1][cjy]!=0){
					f=0;break;
				}
			}else
			if(fx[j]=='W'){
				nowy-=lc[j];
				if(nowy<0||sumy[nowx][nowy-1]-sumy[cjx][cjy]!=0){
					f=0;break;
				}
			}else
			if(fx[j]=='E'){
				nowy+=lc[j];
				if(nowy>m||sumy[nowx][nowy]-sumy[cjx][cjy-1]!=0){
					f=0;break;
				}
			}
		}
		if(!f)continue;
		flg=1;
		cout<<(char)(i+'A'-1);
	}
}
```

### 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int a[1005][1005];
char fx[100005];
int lc[100005];
int sumx[1005][1005],sumy[1005][1005];
int x[27],y[27];
bool flg=0;
void init(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char c;cin>>c;
			if(c=='#'){
				a[i][j]=-1;
			}else
			if(c=='.'){
				a[i][j]=0;
			}else
			if(c>='A'&&c<='Z'){
				a[i][j]=0;
				x[c-'A'+1]=i,y[c-'A'+1]=j;
			}
		}
	}
	cin>>k;
	for(int i=1;i<=k;i++){
		cin>>fx[i]>>lc[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			sumx[i][j]=sumx[i-1][j]+(a[i][j]==-1);
			sumy[i][j]=sumy[i][j-1]+(a[i][j]==-1);
		}
	}
}
void solve_and_print(){
	for(int i=1;i<=26;i++){
		if(!x[i]&&!y[i])continue;
		int nowx=x[i],nowy=y[i];
		bool f=1;
		for(int j=1;j<=k;j++){
			int cjx=nowx,cjy=nowy;
			if(fx[j]=='N'){
				nowx-=lc[j];
				if(nowx<0||sumx[nowx-1][nowy]-sumx[cjx][cjy]!=0){
					f=0;break;
				}
			}else
			if(fx[j]=='S'){
				nowx+=lc[j];
				if(nowx>n||sumx[nowx][nowy]-sumx[cjx-1][cjy]!=0){
					f=0;break;
				}
			}else
			if(fx[j]=='W'){
				nowy-=lc[j];
				if(nowy<0||sumy[nowx][nowy-1]-sumy[cjx][cjy]!=0){
					f=0;break;
				}
			}else
			if(fx[j]=='E'){
				nowy+=lc[j];
				if(nowy>m||sumy[nowx][nowy]-sumy[cjx][cjy-1]!=0){
					f=0;break;
				}
			}
		}
		if(!f)continue;
		flg=1;
		cout<<(char)(i+'A'-1);
	}
}
int main(){
	init();
	solve_and_print();
	if(!flg)cout<<"no solution\n";
	return 0;
}
/*
6 10
##########
#K#..#####
#.#..##.##
#..L.#...#
###D###A.#
##########
4
N 2
S 1
E 1
W 2
*/
```

**完美撒花!**

---

## 作者：zjhzs666 (赞：0)

# 题意
给你一张 $n$ 行 $m$ 列的地图，其中 `#` 表示为海，不可行走；`.` 为可行走区域，当然，有一些可行走区域会表示成字母，为起点。现在你需要严格按照 $k$ 条指令行走，如果掉入海中便说明该路径及起点不合法，请按照字典序输出可行起点，如果没有可行的起点输出 `no solution`。


# 思路
将可行走区域赋值为 $0$，不可行走区域赋值为 $1$，定义 $2$ 个二维数组分别记录每个位置 $x$ 坐标的前缀和以及 $y$ 坐标的前缀和，然后从每一个起点出发执行每一条指令，当行走路径中经过了海就提前退出，每次模拟完一条路径后便判断该路径是否可行，如果可行就给对应字母下标赋值为 $1$。


# 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,m,k,h[100101],z[30][5],r,a[1021][1021],c[1021][1021],cc[1021][1021],dd,rr[30],x;
char aa,f[100150];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>aa;
			if(aa>='A'&&aa<='Z'){//判断该位置是否为起点
				r++;
				z[r][0]=aa-'A';//记录字母
				z[r][1]=i;//记录x坐标
				z[r][2]=j;//记录y坐标
			}
			if(aa=='#')a[i][j]=1;//判断是否为海
			c[i][j]=c[i-1][j]+a[i][j];//对x坐标进行前缀和
			cc[i][j]=cc[i][j-1]+a[i][j];//对y坐标进行前缀和
		}
	cin>>k;
	for(int i=1;i<=k;i++)cin>>f[i]>>h[i];
	for(int i=1;i<=r;i++){
		int ff=0;
		for(int j=1;j<=k;j++){
			if(f[j]=='N'){
				if(z[i][1]-h[j]>1&&c[z[i][1]][z[i][2]]-c[z[i][1]-h[j]-1][z[i][2]]==0){//判断是否越界以及行走路径中是否存在海
					z[i][1]-=h[j];
				}
				else{
					ff=1;//有海提前退出并标记不可行
					break;
				}
			}
			if(f[j]=='S'){
				if(z[i][1]+h[j]<n&&c[z[i][1]+h[j]][z[i][2]]-c[z[i][1]][z[i][2]]==0){
					z[i][1]+=h[j];
				}
				else{
					ff=1;
					break;
				}
			}
			if(f[j]=='E'){
				if(z[i][2]+h[j]<m&&cc[z[i][1]][z[i][2]+h[j]]-cc[z[i][1]][z[i][2]]==0){
					z[i][2]+=h[j];
				}
				else{
					ff=1;
					break;
				}
			}
			if(f[j]=='W'){
				if(z[i][2]-h[j]>1&&cc[z[i][1]][z[i][2]]-cc[z[i][1]][z[i][2]-h[j]-1]==0){
					z[i][2]-=h[j];
				}
				else{
					ff=1;
					break;
				}
			}
		}
		if(ff==0){//该路径可行
			rr[z[i][0]]=1; //该字母为可行解
			dd=1;//标记有可行路径
		}
	}
	for(int i=0;i<26;i++)if(rr[i]==1)cout<<char(i+'A');//依题意输出
	if(dd==0)cout<<"no solution";
    return 0;
}
```


---

## 作者：Moon_Wind (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF106D)


------------

前言：今天模拟赛考了这道题，就来写写题解吧。


------------


**题意简述**：

有一个 $n \times m$ 的矩阵，有的点是不能通过的。给出几个点和一组操作，判断出有哪些点是能够完整地执行给定的整个操作的。如果无解，输出 `no solution`。




------------



**算法分析**：

我们首先想到的肯定是进行模拟，模拟每个点每一步所走的路程。判断有没有走出边界或经过海洋。如果经过，就枚举下一个点。

当字母个数为 $L$ 个时，时间复杂度是 $O(L k \times len)$，显然无法通过极限数据。

我们考虑用二维前缀和进行优化。将每一行，每一列中含有的 `#` 的个数进行前缀和，等到对于每一次操作是否经过海洋或越界时调用即可，这样就避免了每一步都要模拟的局面。
 

------------

**复杂度分析**：

时间复杂度是 $O(mn)$，空间复杂度是 $O(mn)$，可以通过本题。
 
**代码部分**：


------------

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char c[1500][1500],dir[100010];
int a[1500][1500],qzh[1500][1500],qzl[1500][1500],len[100010],t[27],n,m,k,flag=1;
bool run(int x,int y){//进行操作。
     for(int i=1;i<=k;i++){
        if(dir[i]=='W'){//向西方走。
	    int nx=x,ny=y-len[i];
	    if(nx<1||nx>n||ny<1||ny>m) return 0;
	    if(qzh[x][y]-qzh[x][ny-1]) return 0;
	    x=nx,y=ny;
	 }
          if(dir[i]=='E'){//向东方走。
	      int nx=x,ny=y+len[i];
	      if(nx<1||nx>n||ny<1||ny>m) return 0;
	      if(qzh[x][ny]-qzh[x][y-1]) return 0;
	      x=nx,y=ny;
	 }
	  if(dir[i]=='S'){//向南方走。
	      int nx=x+len[i],ny=y;
	      if(nx<1||nx>n||ny<1||ny>m) return 0;
	      if(qzl[nx][y]-qzl[x][y]) return 0;
              x=nx,y=ny;
	 }
	  if(dir[i]=='N'){//向北方走。
	      int nx=x-len[i],ny=y;
	      if(nx<1||nx>n||ny<1||ny>m) return 0;
	      if(qzl[x][y]-qzl[nx-1][y]) return 0;
               x=nx,y=ny;
	 }
    }
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);
        cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>c[i][j];
			a[i][j]=(c[i][j]=='#'?1:0);
			qzh[i][j]=qzh[i][j-1]+a[i][j];//前缀和优化。
			qzl[i][j]=qzl[i-1][j]+a[i][j];
		}
	cin>>k;
	for(int i=1;i<=k;i++) cin>>dir[i]>>len[i];
	for(int i=1;i<=n;i++)
	    for(int j=1;j<=m;j++){
		if(c[i][j]!='#'&&c[i][j]!='.'){
        		op=run(i,j);
			if(op){
			    t[c[i][j]-'A']++;
			    flag=0;
			}
		    }
		}
	for(int i=0;i<=26;i++)
	    if(t[i]) cout<<char(i+'A');
	if(flag)
             cout<<"no solution";
	return 0;
}
```




---

## 作者：Light_Star_RPmax_AFO (赞：0)

## 前言

长沙市一中 8 机房 0720 思维训练 3

[传送门](https://www.luogu.com.cn/problem/CF106D)

[blog](https://www.luogu.com.cn/blog/JJL0610666/solution-cf106d)

## 题目描述

在图上已知点中，找到所有执行所有指令不会碰到 `#` 号的点，按字典序打印。

# 思路

如果暴力，完全超时。

优化使用前缀和找到当前点可以向四个方向走的长度，如果走的超过了长度那么肯定碰到了障碍物。

否则就一直模拟直到走完为止，记录答案。

字典序输出应该怎么办？可以使用 `sort` 可以以字典序排序。

# AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[810][810],sum[810][810];
bool ok = 0;

struct dot{
    int x,y;
    char c;
}d[27];

struct direction{
    int temp;
    char dir;
}dis[100010];

char maps[1010][1010];
int num = 0;

int N[1010][1010],E[1010][1010],W[1010][1010],S[1010][1010];


bool check(int x,int y){
    for(int i = 1;i <= k;i++){
        char dir = dis[i].dir;
        int go = dis[i].temp;
        switch (dir)
        {
        case 'N':
            if(go >= N[x][y])
                return 0;
            x -= go;
            break;
        case 'S':
            if(go >= S[x][y])
                return 0;
            x += go;
            break;
        case 'E':
            if(go >= E[x][y])
                return 0;
            y += go;
            break;
        default:
            if(go >= W[x][y])
                return 0;
            y -= go;
            break;
        }
    }
    return 1;
}

signed main(){
    cin>>n>>m;
    for(int i = 1;i <= n;i++)
        scanf("%s",maps[i] + 1);
	cin>>k;
    for(int i = 1;i <= k;i++){
        cin>>dis[i].dir>>dis[i].temp;
    }
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            if(maps[i][j] >= 'A' && maps[i][j] <= 'Z')
                d[++num] = dot{i,j,maps[i][j]};
    for(int i = 1;i <= m;i++)
        for(int j = 1;j <= n;j++)
        N[j][i] = (maps[j][i] == '#' ? 0 : N[j - 1][i] + 1);
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
        W[i][j] = (maps[i][j] == '#' ? 0 : W[i][j - 1] + 1);
    for(int i = 1;i <= n;i++)
        for(int j = m;j >= 1;j--)
        E[i][j] = (maps[i][j] == '#' ? 0 : E[i][j + 1] + 1);
    for(int i = 1;i <= m;i++)
        for(int j = n;j >= 1;j--)
        S[j][i] = (maps[j][i] == '#' ? 0 : S[j + 1][i] + 1);
    char z[27];int ans = 0;
    for(int i = 1;i <= num;i++){
        if(check(d[i].x,d[i].y)){
			ok = 1;
            z[++ans] = d[i].c;
        }
    }
    sort(z + 1,z + 1 + ans);
    for(int i = 1;i <= ans;i++){
        cout<<z[i];
    }
	if(ok)cout<<endl;
	else cout<<"no solution";
}
```

---

## 作者：DPair (赞：0)

## 【题意】
你有一张宝藏地图地图，并且你知道怎么走可以找到宝藏（当然走的过程中没有障碍物），但你不知道准确的出发点。现在告诉你所有可能为出发点的点，问这些点按已知的走路顺序来走能否完全不碰到障碍物。

## 【思路】
题意十分明确了，观察数据范围发现$k\leq10^5$，并且我们知道字母表中只有$26$个字母。设有$p$个可能的出发点，因此$p\leq26$，所以复杂度为$O(pk)$的算法可以通过本题。即考虑对于每一个可能的出发点进行$O(k)$D的模拟。

我们知道每一步都是向某一个方向前进$len_i$步，一个可行的解要求这$len_i$步中没有一个点是障碍物，$O(len_i)$的暴力模拟显然不行，因此考虑用二维前缀和维护（具体实现方式见代码）。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
vector <char> ans;
int n, m, len[100010];
char a[1010][1010];
char dis[100010];
int b[1010][1010];
int main()
{
	scanf("%d%d", &n, &m);
	for (register int i = 1;i <= n;i ++) scanf("%s", a[i] + 1);
	for (register int i = 1;i <= n;i ++)//维护二维前缀和，b[i][j]表示a[1~i][1~j]的和，递推实现
	{
		for (register int j = 1;j <= m;j ++)
		{
			b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + (a[i][j] == '#'? 1 : 0);
		}
	}
	int p;
	scanf("%d", &p);
	for (register int i = 1;i <= p;i ++)
	{cin >> dis[i] >> len[i];}
	for (register int i = 1;i <= n;i ++)
	{
		for (register int j = 1;j <= m;j ++)
		{
			if(a[i][j] >= 'A' && a[i][j] <= 'Z')//若可能为出发点
			{
				bool ck = true;
				int x = i, y = j;
				for (register int k = 1;k <= p;k ++)//模拟
				{
					int xx = x, yy = y;
					if(dis[k] == 'N') x -= len[k];
					if(dis[k] == 'S') x += len[k];
					if(dis[k] == 'W') y -= len[k];
					if(dis[k] == 'E') y += len[k];
					if(x < 1 || x > n || y < 1 || y > m || (b[max(x, xx)][max(y, yy)] - b[min(x, xx) - 1][max(y, yy)] - b[max(x, xx)][min(y, yy) - 1] + b[min(xx, x) - 1][min(y, yy) - 1]))//通过二维前缀和作差判断区间和，区间和为零则说明路径上没有障碍物
					{
						ck = false;
						break;
					}
				}
				if(ck) ans.push_back(a[i][j]);

			}
		}
	}
	if(ans.size() == 0)//无解
	{
		printf("no solution\n");
		return 0;
	}
	sort(ans.begin(), ans.end());//排序
	for (register int i = 0;i < ans.size();i ++) putchar(ans[i]);
	putchar(10);
}
```

---

