# 『STA - R6』inkar-usi

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/n6w1yuda.png)

（题目背景图片来自 Arcaea 曲绘，如有侵权，请告知出题人。）

## 题目描述

给一个 $n\times m$ 的字符矩阵，有些位置有障碍（记为字符 `#`），需要在矩阵上找出一条起始点任意的路径（可以重复经过某个格子），使得字典序最大。

可以证明答案一定是有限的或者是由某个长度有限的字符串 $S$ 不断重复得到的。如果答案是有限的，直接输出之；如果答案是无限的，只需输出它的最短循环节。

## 说明/提示

**本题采用捆绑测试。**

数据范围：
- Subtask 1 (20pts)：字符矩阵中除了障碍就是字母 `A`。
- Subtask 2 (30pts)：$n,m\le 3$。
- Subtask 3 (50pts)：无特殊限制。

对于全部数据，$1\le n,m\le 10^3$，所有非障碍字符都是大写字母，矩阵至少有一个非障碍格。

## 样例 #1

### 输入

```
3 3
###
#A#
###```

### 输出

```
A```

## 样例 #2

### 输入

```
3 4
####
#AB#
####```

### 输出

```
BA```

## 样例 #3

### 输入

```
3 4
####
#AA#
####```

### 输出

```
A```

# 题解

## 作者：jijidawang (赞：14)

有显然的贪心策略是从最大的字符出发每次往旁边最大的格子走，注意到最大的字符旁边的格子肯定下一步会往最大的格子那里走。于是答案循环节的长度最大为 2，暴力枚举即可。

需要特殊处理路径长度为 1 和存在两个相邻最大格子的情况。
 
时间复杂度 $\Theta(nm)$。

---

## 作者：Genshin_ZFYX (赞：11)

首先，第一个字母必定是矩阵中字典序最大的字母。

第二个字母，是第一个字母旁边字典序最大的字母。

第三个字母是第二个字母旁边字典序最大的字母，不难想到肯定是第一个字母，这样就回到了第一步。

由此可得循环节长度 $\le 2$，具体做法就是找到第一个字母（可能有多个），枚举这个字母的上、下、左、右并连接成一个字符串，找出字典序最大的字符串即可。

有时候答案只有一个字母。

最后，如果答案有两个字母且两个字母相同，输出一个就行。

小技巧：如果要把字符强制转换成字符串，可以让一个空串加上这个字符。

AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define I return
#define love 0
#define FIRESTARS ;
string ans,space;
int n,m,dx[]={0,1,0,-1},dy[]={1,0,-1,0};
char a[1005][1005],maxn=0;
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
    	cin>>a[i][j];
    	maxn=max(maxn,a[i][j]);
	}
	ans=space+maxn;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    if(a[i][j]==maxn)
	for(int k=0;k<4;k++)
    {
    	int xx=dx[k]+i,yy=dy[k]+j;
    	if(xx>=1&&yy>=1&&xx<=n&&yy<=m&&a[xx][yy]!='#')
    	ans=max(ans,space+a[i][j]+a[xx][yy]);
	}
	if(ans.size()==1)cout<<ans;
	else
	{
		if(ans[0]==ans[1])cout<<ans[0];
		else cout<<ans;
	}
	I love FIRESTARS
}

```

---

## 作者：yzm0325 (赞：6)

很容易想到这道题的贪心策略：从最大的格子开始走，每次往周围最大的格子走。因为如果在某一位没有走最大格，那么最后字符串的字典序是一定小于走最大格形成的字符串（比字典序到这一位时前者会直接被 pass 掉）。

根据这个策略，我们从最大格开始，第一步走到周围一格，第二部时因为起点是周围格中最大的，所以又会回到起点，然后就进入了循环，也就是说循环节长度最大为 $2$。

然后就简单了，枚举每种走法，打擂台找最大的即可。注意特判路径长度为 $1$ 以及最大字符相邻（此时最小循环节是一位的）的情况。

```cpp
#include <bits/stdc++.h> 
using namespace std;
int n, m;
char a[1010][1010], ans1 = ' ', ans2 = ' ';
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) cin >> a[i][j];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) {
            if(a[i][j] == '#') continue; // 先判掉墙
            for(int k = 0; k < 4; k++) { // 然后移动
                int nx = i + dx[k], ny = j + dy[k];
                if(a[nx][ny] == '#') continue; // 判墙
                if(a[i][j] > ans1 || a[i][j] == ans1 && a[nx][ny] > ans2) // ans1, ans2 分别是答案的前两位
                    ans1 = a[i][j], ans2 = a[nx][ny]; // 更新
            }
        }
    if(ans1 == ' ')
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++)
                if(a[i][j] != '#' && a[i][j] > ans1) ans1 = a[i][j]; // 特判答案长度为 1
    if(ans1 == ans2) cout << ans1; // 特判两个最大相邻
    else cout << ans1 << ans2;
    return 0;
}
```

---

## 作者：fanfanhao (赞：5)

# P10677
 希望管理员能给本蒟蒻一次写题解的机会，谢谢。
 本蒟蒻的第一篇题解。
 其实这道题很简单，我们只需要找到字典序最大的字符，如果这个字符上下左右有其他的不为‘#’字符，就找上下左右中字典序最大的字符。\
 如果有多个字典序最大的的字符，就找（这个字符+上下左右字典序最大的一个不为‘#’的字符）中最大的组合。
 因为只要找到最大的一组，只要让那两个无限循环，可以保证字典序最大。
 最后只用输出最大的组合（两个字符）
 还有一些其他情况，代码中细说。\
 代码实现
 ```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1005][1005];//数组
int main()
{
	int n,m;
	cin>>n>>m;
	char last='1';//表示字典序最大的字符
	int cnt=0;//不为"#"的字符数量。
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];//输入
			if(a[i][j]>='A'&&a[i][j]<='Z'){
				if(a[i][j]>last){
					last=a[i][j];//更新最大值
				}
				cnt++;//次数++
			} 
		}
	}
	char ans,ans2='0';//答案两个字符
	long long now=-10000000000; //两个字符的最大值
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==last){//如果搜寻到的字符字典序最大
				ans=a[i][j]; 
           //接下来四个方向搜寻，如果两个字符加起来的最大值大于原来的最大值，则更新最大值并修改答案。
				if(a[i+1][j]>='A'&&a[i+1][j]<='Z'&&a[i+1][j]+a[i][j]>=now){
					now=a[i+1][j]+a[i][j];
					ans2=a[i+1][j];
				}
				if(a[i-1][j]>='A'&&a[i-1][j]<='Z'&&a[i-1][j]+a[i][j]>=now){
					now=a[i-1][j]+a[i][j];
					ans2=a[i-1][j];
				}
				if(a[i][j+1]>='A'&&a[i][j+1]<='Z'&&a[i][j+1]+a[i][j]>=now){
					now=a[i][j+1]+a[i][j];
					ans2=a[i][j+1];
				}
				if(a[i][j-1]>='A'&&a[i][j-1]<='Z'&&a[i][j-1]+a[i][j]>=now){
					now=a[i][j-1]+a[i][j];
					ans2=a[i][j-1];
				}
			}
		}
	}
	if(cnt==1){//如果只有一个不为"#"字符，则直接输出那一个
		cout<<last;
		return 0;
	}
	if(ans2=='0'){
      //如果所有最大值四周都没有不为"#"的字符，则输出字典序最大的字符。
		cout<<ans;
		return 0;
	}
	if(ans==ans2){
      //如果搜寻到的答案的两个字符相等，则指输出一个，因为他俩可以重复。
		cout<<ans;
		return 0;
	}
	cout<<ans<<ans2;
	return 0;
}

---

## 作者：HsNu1ly7_ (赞：4)

## 思路

正常情况下会想到爆搜，可是数据有 $10^3$ 那么大。

考虑到要找到字典序最大的路线，只需要找到矩阵中最大的那个字母，在判断该字母周围四个格子最大的，字典序最大的路线就是在这两个字母之间来回横跳，可以证明，没有其他方案比这个方案字典序更大了。

时间复杂度为 $O(nm)$ ，代码就不贴了。

---

## 作者：JoeZYQ (赞：4)

[先看题](https://www.luogu.com.cn/problem/P10677)
### 思路分析
要使字典序最大，必然先走全图最大的字母，再走全图最大的字母周围最大的字母，然后，又可以回到全图最大的字母，陷入循环。

### 特别注意：
- 如果全图最大的字母周围最大的字母就是全图最大的字母，只用输出全图最大的字母。
- 全图最大的字母有多个，应每个都枚举一遍。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s[1000005];
int n,m;
char ACACAC=0,sum=0;
char pd(int x,int y){
	char maxi=0;
	if(s[x-1][y]>='A')maxi=max(maxi,s[x-1][y]);
	if(s[x-1][y]==ACACAC)exit(0);
	if(s[x][y-1]>='A')maxi=max(maxi,s[x][y-1]);
	if(s[x+1][y]==ACACAC)exit(0);
	if(s[x+1][y]>='A')maxi=max(maxi,s[x+1][y]);
	if(s[x][y-1]==ACACAC)exit(0);
	if(s[x][y+1]>='A')maxi=max(maxi,s[x][y+1]);
	if(s[x][y+1]==ACACAC)exit(0);
	return maxi;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i][j]>=ACACAC&&s[i][j]!='#')
				ACACAC=s[i][j];
	cout<<ACACAC;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i][j]==ACACAC)
				if(pd(i,j)!=ACACAC)sum=max(sum,pd(i,j));
	 if(sum!=0&&sum!=ACACAC)cout<<sum;
     return  0;
}
```

---

## 作者：qhr2023 (赞：3)

## 思路

显然，为求最大字典序，答案路径一定是从最大的字符开始，再在其旁边找一个最大的字符，但在旁边的字符继续找时，一定会找回那个最大的字符，所以答案一定不超过两个字符，暴力枚举所有最大字符即可，输出时再特判存在两个相邻最大字符的情况。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[1005][1005], mx, ch;
int n, m, dx[]={0, 0, -1, 1}, dy[]={1, -1, 0, 0};
int main () {
	cin >> n >> m;
	for (int i=1; i<=n; i++) 
		for (int j=1; j<=m; j++) 
			cin >> c[i][j],
			mx=max(mx, c[i][j]);
	for (int i=1; i<=n; i++) 
		for (int j=1; j<=m; j++) 
			if (c[i][j]==mx) 
				for (int k=0; k<4; k++) {
					int x=i+dx[k], y=j+dy[k];
					if (x>=1&&x<=n&&y>=1&&y<=m&&c[x][y]!='#') 
						ch=max(ch, c[x][y]);
				}
	if (mx!=ch)
		cout << mx;
	cout << ch;
	return 0;
}
```

---

## 作者：M4rkSELby (赞：3)

简易结论题。

容易想到，所求路径一定以整个矩阵内的最大字母开头。再找到所有最大字母所在位置，与这些位置的相邻位置中的最大字母即是路径的第二个位置，容易发现接下来的路径就是在这两个字母之间来回走。易用反证法证明这个一定是字典序最大的路径。循环节就是这两个字母。特别的，当这两个字母相邻时，循环节的长度为 $1$。

附上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define pii pair<int,int>
#define mk make_pair
#define mod 100000000
using namespace std;
il int rd(){
    int jya=0,tl=1;char jyt=getchar();
    while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
    while(isdigit(jyt)){jya=(jya<<1)+(jya<<3)+(jyt-'0');jyt=getchar();}
    return jya*tl;
}
il void wr(int jjy){
    if(jjy<0)putchar('-'),jjy=-jjy;
    if(jjy>9)wr(jjy/10);
    putchar(jjy%10+48);
}
il int max(int x,int y){return x>=y?x:y;}
il int min(int x,int y){return x<=y?x:y;}
const int JYAAKIOI=1145141919810;
int n,m,x,y,dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};
char a[1086][1086],maxn,ma;
queue<pii>q;
bool vis[1086][1086];
signed main(){
    //freopen("jytwcsnm.in","r",stdin);
    //freopen("jytwcsnm.out","w",stdout);
    n=rd();m=rd();
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            cin>>a[i][j];
            if(maxn<a[i][j]&&a[i][j]!='#'){
                maxn=a[i][j];
            }
        }
    }
    cout<<maxn;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(maxn==a[i][j]){
                q.push(mk(i,j));
            }
        }
    }
    while(!q.empty()){
        x=q.front().first,y=q.front().second;
        vis[x][y]=1;
        q.pop();
        for(int i=0;i<4;++i){
            int xx=x+dx[i],yy=y+dy[i];
            if(!vis[xx][yy]&&xx>=1&&xx<=n&&yy>=1&&yy<=m&&a[xx][yy]!='#'){
                vis[xx][yy]=1;
                if(ma<a[xx][yy])ma=a[xx][yy];
            }
        }
    }
    if(maxn!=ma)cout<<ma;
    return 0;
}
```
~~（谨以此题解致敬因此题封号的 @What__can__I__say 与 @jinytong）~~

---

## 作者：xyx404 (赞：2)

## 思路：
看题，需要在矩阵上找出一条起始点任意的路径（**可以重复**经过某个格子），使得字典序最大。

那么通过可以重复这四个字我们可以知道最后求出的字符串的长度一定是小于等于二的。

所以，我们可以在输入时查找最大的字母（为了保证字典序最大）用一个变量 $c$ 存下来，输入完之后，历遍矩阵，当历遍到的字母为我们找到的最大的字母时，查找他上下左右四个方向的最大的字母，然后用 $ch$ 存下来。

最后在循环结束后在 $c$ 与 $ch$ 不相同时输出 $ch$ 就可以了，相同的情况就不要输出了。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long 
int n,m;
char ch;
char jz[1500][1500]; 
int dx[]={1,-1,0,0},dy[]={0,0,-1,1};
int main(){ 
	int mx=0,my=0;
	char c='A'-1;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>jz[i][j];if(jz[i][j]!='#')if(jz[i][j]>c)c=jz[i][j];// 输入并查找最大的字母 
		}
	}
	cout<<c;// 为了保证字典序最大第一个字母一定是最大的可以直接输出 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(jz[i][j]!='#')if(jz[i][j]==c){
				mx=i;my=j;
				for(int i=0;i<4;i++){
					int tx=mx+dx[i],ty=dy[i]+my;
					if(tx<1||ty<1||tx>n||ty>m)continue; 
					if(jz[tx][ty]=='#')continue;
					if(ch<jz[tx][ty])ch=jz[tx][ty];
				}
			}
		}
	}
	if(ch!=c)cout<<ch;// 在不相等的时候才输出不然会输出两个相同的字母，如果不这样写就不满足题目中如果答案是无限的，只需输出它的最短循环节
	return 0;
}
```

---

## 作者：zhanghy123 (赞：2)

### 思路
题目中要求在字符矩阵上走出一条路径，使得这条路径经过的点连成的字符串字典序最大。因为可以重复走，所以只要有两个挨在一起的非障碍点，就可以在这两个点上反复横跳，这时走出的路径长度为无穷，循环节就是这两个点上的字符。

那么，想让字典序最大，首先要**让起点上的字符尽量大**。遍历整个字符矩阵，找到字符最大的**几个**点（下文简称最大点），把它们的坐标存到 vector 数组中。

接下来，查询每一个最大点四周的非障碍点。因为走到最大点旁边的某个非障碍点后，**往回走的字典序显然比往外走到另一个点上得到的字典序要大**。所以，只要某个最大点上下左右四个方向有一个方向紧挨着一个非障碍点，就可以从最大点出发在这两个点上反复横跳，构成一条字典序较大的路径。

显然，紧贴在几个最大点四周的这些非障碍点中，最大的一个可以与其旁边的那个最大点连成一条路径，从最大点出发，在这两个点上反复横跳，就可以连成一条字典序最大的无限路径。

注意：**若最大点和它旁边的那个点相同，则实际循环节为 $1$，只输出最大点即可。**

若所有最大点都被障碍死死包围着，那么路径长度就只能是 $1$ 了，即它本身。


附：（[字典序的定义](https://baike.baidu.com/item/%E5%AD%97%E5%85%B8%E5%BA%8F/7786229?fr=ge_ala)）

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[1002][1002],maxx,sec;//maxx为最大点上的字符，sec为与最大点相邻的点上的字符 
int n,m;
vector<pair<int,int> >v;//用来存储每个最大点的坐标 
char Max(char a,char b)
{
	return a>b?a:b;
}
int main()
{
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++){
			cin>>c[i][j];
			if(c[i][j]!='#')//肯定是要找非障碍点 
			{
				if(c[i][j]>maxx){//有比当前最大点更大的了，之前的最大点全部清除 
					v.clear();
					maxx=c[i][j];
				}
				if(c[i][j]==maxx)
					v.push_back(make_pair(i,j));//将最大点的坐标存起来 
			}
		}
	for(int i=0; i<v.size(); i++)
	{
		int x=v[i].first,y=v[i].second;
		char c1=c[x-1][y],c2=c[x+1][y],c3=c[x][y-1],c4=c[x][y+1];
		sec=Max(sec,Max(c1,Max(c2,Max(c3,c4))));//sec为最大点四周的那些点中最大的一个 
	}
	if(sec=='#' || sec==0 || maxx==sec)//若最大点被障碍包围，只有最大点这一条长度为1的有限路径 
	//或两个最大点连在一起，在两个相同的点之间反复横跳，循环节实际为1 
		cout<<maxx;
	else 
		cout<<maxx<<sec;//最大点与四周的点中最大的一个连成一条反复横跳的路径 
	return 0;
}

```

---

## 作者：Kotobuki_Tsumugi (赞：2)

可以先这么想：想要字典序最大那肯定是前面的字符尽可能大。那么贪心，直接选整个矩阵中最大的字母 $u$。

下一步怎么走？继续选 $u$ 四联通中最大的字母 $v$，会遇到两种情况。

1. $v$ 不如 $u$ 大。那么直接走下去。

2. $v$ 和 $u$ 是同一个字符，这样路径不好统计了。

但其实不管 $v$ 是什么，再下一步依然会选择与 $v$ 四联通中最大的字母。这个字母就是 $u$，即我们又走了回来。所以其实就一直在这两个字母间踱步。

想到这里，我们就可以想到：对于上面的第一种情况，答案（最短循环节）就是 $u$ 再加上 $v$；对于第二种情况，答案就是 $u$。

在实现的时候注意：最大的 $u$ 可能有多个。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+10;
int n,m,maxn,k,top,sum,op;
int dx[10] = {0,0,0,1,-1};
int dy[10] = {0,1,-1,0,0};
char a[N][N];
bool vis[N][N],e[N][N];
queue<pair<int,int> > q; 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=m;j++){
			cin>>a[i][j];
			if(a[i][j] == '#')
				vis[i][j] = true;
			if(a[i][j] > maxn){
				while(!q.empty()) q.pop();
				maxn = a[i][j];
				q.push(make_pair(i,j));
			}
			else if(a[i][j] == maxn) 
				q.push(make_pair(i,j));
		}
	}
	char top = a[q.front().first][q.front().second];
	cout<<top;
	while(!q.empty()){
		pair<int,int> f = q.front();
		q.pop();
		int x = f.first;
		int y = f.second;
		int maxn = 0;
		for(int i = 1;i<=4;i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(vis[nx][ny]) continue;
			maxn = max(maxn,int(a[nx][ny]));
		}
		op = max(op,maxn);
	}
	if(top != op) cout<<char(op)<<endl;
	return 0;
}
```

---

## 作者：matrixPower (赞：2)

[传送门](https://www.luogu.com.cn/problem/P10677)

贪心。

考虑到要让字典序最大，那么答案最多只会有两位，答案为这两位循环。

我们可以先把最大的字母找出来，记为 $x$，若四周全为 `#`，则答案就是那个字母，且并不是无限循环（样例一）。

若四周最大的字母（记为 $y$）跟他本身一样，则答案是最大的字母（样例三），因为它可以反复横跳。

否则答案就是先 $y$ 再 $x$（样例二）。

代码：

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define lowbit(x) ((x)&-(x))
#define small priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>
using namespace std;

typedef long long ll;
typedef double db;
typedef __int128 III;
const db eqs=1e-6;
const int inf=1e9;
void ll_cmax(char &a,char b){a=a>b?a:b;}
void ll_cmin(ll &a,ll b){a=a<b?a:b;}
void int_cmax(char &a,char b){a=a>b?a:b;}
void int_cmin(int &a,int b){a=a<b?a:b;}
bool db_eq(db a,db b){return fabs(a-b)<eqs;}
bool minuscule(char ch){return ch>='a' && ch<='z';}
bool number(char ch){return ch>='0' && ch<='9';}

const int MAXN=1000+5;
char a[MAXN][MAXN];
int n,m;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	int x,y;
	char maxn1=0;
	for(int i=0;i<=n+1;i++) a[i][0]='#',a[i][m+1]='#';
	for(int i=0;i<=m+1;i++) a[0][i]='#',a[n+1][i]='#';
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];
			if(a[i][j]!='#' && a[i][j]>maxn1) maxn1=a[i][j],x=i,y=j;
		}
	}
	char maxn=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]==maxn1)
			{
				char maxn2=0;
				if(a[i+1][j]!='#') int_cmax(maxn2,a[i+1][j]);
				if(a[i-1][j]!='#') int_cmax(maxn2,a[i-1][j]);
				if(a[i][j+1]!='#') int_cmax(maxn2,a[i][j+1]);
				if(a[i][j-1]!='#') int_cmax(maxn2,a[i][j-1]);
				int_cmax(maxn,maxn2);
			}
		}
	}
	if(maxn==0 || maxn==maxn1) cout<<maxn1<<endl;
	else cout<<maxn1<<maxn<<endl;
	return 0;
}

```

---

## 作者：_H17_ (赞：1)

## 题目分析

贪心题，千万不要想复杂。

字典序最大意味着什么？显然是**首字母最大**，**第二个次大**。

又由于可以重复走，我们可以先找最大，然后找它**相邻的最大**，即可行的次大值。

例如如下数据输入：

```
7 5
#####
#ZAA#
#####
#BZB#
#####
#BZA#
#####
```

首先找到最大的 $3$ 个 `Z`，然后找其中次大的，其中第二和三个 `Z`，可以有 `B` 最优。

然后怎么办？找 `A`？错错错，`A` 太小了，我们应该回到 `Z`，来进行反复横跳。

于是答案是 `ZB`。

注意如果最大的字母没有相邻的或者相邻的字母与之相同时不要多输出。

例如：

```
3 3
###
#A#
###
```

和

```
3 4
####
#AA#
####
```

答案都是 `A` 而不是 `AA`。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,dx[]={0,0,1,-1},dy[]={1,-1,0,0},s[3];
char a[1001][1001];
bool check(int i,int j){
    return 1<=i&&i<=n&&1<=j&&j<=m&&a[i][j]!='#';
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){//枚举每个位置
            if(a[i][j]!='#'){
                if(a[i][j]>s[0]){//更大
                    s[0]=a[i][j],s[1]=0;
                    for(int k=0,nx,ny;k<4;k++){//相邻的
                        nx=i+dx[k],ny=j+dy[k];
                        if(check(nx,ny))
                            s[1]=max(s[1],(int)a[nx][ny]);//更大的
                    }
                }
                else if(a[i][j]==s[0]){//相同
                    for(int k=0,nx,ny;k<4;k++){
                        nx=i+dx[k],ny=j+dy[k];
                        if(check(nx,ny)&&a[nx][ny]>s[1])
                            s[1]=a[nx][ny];//更大的
                    }
                    
                }
            }
        }
    cout<<(char)s[0];
    if(s[1]&&s[1]!=s[0])
        cout<<(char)s[1];//特判
    return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：1)

## 背景

把人家鸽了，感觉废了。

## 分析

这道题刚看到题目的时候很多人会想爆搜，但是因为 $10^3$ 的数据范围，所以应该去想一想是不是有什么性质。

我们稍微想一想就会发现，题目上提到了可以重复走，那么对于一般情况（就是有由不同字母构成的联通块）而言，直接找到两个字典序最大的字母，然后一直在它们之间兜圈子不就可以了？

考虑字典序是按照字母顺序一个一个排的，所以容易证明这个思路是正确的。

所以得到初步思路，枚举所有非 `#` 方格，然后找到字典序最大的方格，并对每个字典序最大的方格找到其四个角对应的最大字符，那么答案就是依次输出这两个字符。

考虑一点细节。当只有一种合法字符或只有一个合法字符时，因为要输出最小循环节，所以特判一下并只输出一个字符即可。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
//const int mod=10000007;
const int maxn=1e6+10;
int n,m;
char c[3000][3000];
int dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};
signed main()
{
//	freopen("list.in","r",stdin);
//	freopen("list.out","w",stdout);
	cin>>n>>m;
	char ma=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>c[i][j];
			if(c[i][j]!='#')
			ma=max(ma,c[i][j]);
		}
		c[i][0]=c[i][m+1]='#';
	}
	for(int i=1;i<=m;i++)c[0][i]=c[n+1][i]='#';
	char cma=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(c[i][j]==ma)
			{
				for(int k=0;k<4;k++)
				{
					int ii=i+dx[k],jj=j+dy[k];
					if(c[ii][jj]!='#')
					{
						cma=max(cma,c[ii][jj]);
					}
				}
			}
		}
	}
	if(cma==0||cma==ma)cout<<ma;
	else cout<<ma<<cma;
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10677)

## 思路

一道贪心。

读入数据后保存 `ASCII` 值最大的字符的位置为开始位置，如果多于一个就保存多个。统计出现的字母数，如果只出现了一种就输出它，直接结束程序。

用一个返回值类型为字符串的函数进行深搜，每次上下左右找 `ASCII` 值最大的字母继续搜索（如果有多个最大的就都搜）。返回搜索结果字典序最大的字符串。每次搜到一个位置判断是否越界，和当前搜索结果是否已经出现循环节。如果出现了，记录当前搜索结果，直接返回主函数。找循环节可以用 `map`。

- 每次从一个位置开始新一轮搜索前别忘清空变量和标记用的 `map`。

返回主函数后直接双重循环找循环节，输出即可（第一层枚举循环节长度，第二层枚举在这种条件下是否可以构成循环）。

- 可以用 `unordered_map` 代替 `map`，复杂度更优。

## 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=1010;
char c[N][N],mx;
int n,m;
vector<pii>ve;
string ans;
bool flag;
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
int tom[N];
unordered_map<string,bool>mp;
string dfs(int x,int y,string s,int ex,int ey){
	if(flag||x<1||x>n||y<1||y>m||c[x][y]=='#')return s;
	if(x==ex&&y==ey&&s.size()){//又走到起点一定会循环。
		flag=1;
		return s;
	}
	s+=c[x][y];
	if(s.size()%2==0&&mp[s.substr(0,s.size()/2)]){//判断是否已经循环。
		flag=1;
		return s;
	}
	mp[s]=1;
	char mx=max({c[x-1][y],c[x+1][y],c[x][y-1],c[x][y+1]});
	string res="";
	for(int i=0;i<4;++i){
		if(c[dx[i]+x][dy[i]+y]==mx){//找 ASCII 值最大的搜索。
			res=max(res,dfs(dx[i]+x,dy[i]+y,s,ex,ey));
		}
	}
	return res;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cin>>c[i][j];
			if(c[i][j]=='#')continue;
			if(mx<c[i][j])ve.clear(),ve.pb({i,j}),mx=c[i][j];
			else if(mx==c[i][j])ve.pb({i,j});
			if(c[i][j]!='#')++tom[c[i][j]-'A'];
		}
	}
	int cnt=0;
	for(int i=0;i<26;++i)if(tom[i])++cnt;//判断出现字符数。
	if(cnt==1){
		cout<<mx;
		return 0;
	}
	for(auto i:ve){//遍历每个起点搜索。
		ans=max(ans,dfs(i.fi,i.se,"",i.fi,i.se));
		flag=0;
		mp.clear();
	}
	for(int i=1;i<=ans.size();++i){
		if(ans.size()%i==0){
			bool ok=1;
			for(int j=i;j<ans.size();++j){
				if(ans[j]!=ans[j%i]){
					ok=0;
					break;
				}
			}
			if(ok){
				ans=ans.substr(0,i);//构成循环，记录并退出。
				break;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/163514328)

---

## 作者：Breath_of_the_Wild (赞：0)

题意：求迷宫中的字典序最大的一条路径，并求它最短的循环节。

考虑贪心。首先起点显然应该选最大的字符。其次，下一步应该走次大的。这时，如果不回到起点，无论怎么走，都不可能取到比起点更大的值（因为起点就是最大的）。

因此，第一步走最大的，第二步走次大的，第三步走最大的，依次循环。显然，循环节最多有两位，即第一步和第二步。

另外，需要特判长度为 $1$ 的字符串和第一步第二步相同。
```cpp
	//mx 为最大的字符，即起点。
	//aa 初始值为 char(0)，以便后面判断字符串为 1 的。
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		if(a[i][j]==mx){
			if(a[i+1][j]!='#'&&i+1<=n) aa=max(aa,a[i+1][j]);
			if(a[i-1][j]!='#'&&i-1>0) aa=max(aa,a[i-1][j]);
			if(a[i][j-1]!='#'&&j-1>0) aa=max(aa,a[i][j-1]);
			if(a[i][j+1]!='#'&&j+1<=m) aa=max(aa,a[i][j+1]);
		}
	}
}
if(aa==mx||aa==0) cout<<mx;
else cout<<mx<<aa;

---

## 作者：JYX0924 (赞：0)

这道题可以直接枚举每一个字典序最大的位置，然后枚举一下这个位置四周的位置，找到最大的。

需要特判的是答案的两个字符相等，只需要输出其中一个。

下面是我的 AC 代码。

```c
#include<bits/stdc++.h>
using namespace std;
int n,m;
char s[1005][1005],zd,tt;
int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>m; for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>s[i][j];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(s[i][j]!='#') zd=max(zd,s[i][j]);
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
	if(s[i][j]==zd)
	{
	    if(i+1<=n&&s[i+1][j]!='#') tt=max(tt,s[i+1][j]);
	    if(i-1>=1&&s[i-1][j]!='#') tt=max(tt,s[i-1][j]);
	    if(j+1<=m&&s[i][j+1]!='#') tt=max(tt,s[i][j+1]);
	    if(j-1>=1&&s[i][j-1]!='#') tt=max(tt,s[i][j-1]);
	}
	if(zd==tt) cout<<zd;
	else cout<<zd<<tt;
	return 0;
}
```
谢谢大家！！！

---

## 作者：HHC883 (赞：0)

# 题目分析
容易发现，若矩阵中的最大连通块的大小为 $1$（也就是不存在两个点能互相到达），所求路径一定有限，这时答案就是所有点对应的字母中最大的那一个；否则，所求路径一定无限，因为按字典序比较时，长度大的优先。那么这个无限的路径是什么呢？很简单，先找到所有点对应的字母中最大的一个，再找到这个点周围的四个点对应的字母中最大的那个，这两个点便组成了一个循环节。原因如下：首先，路径长度已经是无限的了，那么只需要比较对应位置上的字母，所以对应的字母最大的点肯定优先。至于为什么要选择两个，是因为一个点自己肯定不可能组成循环节。注意，当选择的两个点对应的字母相同时，只要输出一个。

于是，这题就以 $O(nm)$ 的时间复杂度做完了。
# 参考代码
```cpp
#include<iostream>
using namespace std;
int n,m;
char mp[1005][1005],maxf,maxs,maxn;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>mp[i]+1;
	for(int i=1;i<=n;i++) mp[i][0]=mp[i][m+1]='#';
	for(int i=1;i<=m;i++) mp[0][i]=mp[n+1][i]='#';
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mp[i][j]=='#') continue;
			if(mp[i][j]>maxn) maxn=mp[i][j];
			if(!(mp[i-1][j]=='#'&&mp[i][j-1]=='#'&&mp[i+1][j]=='#'&&mp[i][j+1]=='#')){
				if(mp[i][j]>maxf){
					maxf=mp[i][j];
					maxs=max(max(max(mp[i-1][j],mp[i][j-1]),mp[i+1][j]),mp[i][j+1]);
				}
				if(mp[i][j]==maxf){
					maxs=max(maxs,max(max(max(mp[i-1][j],mp[i][j-1]),mp[i+1][j]),mp[i][j+1]));
				}
			}
		}
	}
	if(maxf){
		if(maxf==maxs) cout<<maxf;
		else cout<<maxf<<maxs;
	}else cout<<maxn;
	return 0;
}
  
```

---

## 作者：lcfollower (赞：0)

~~虽然比赛时只想着骗分，骗完就下了。~~

不过细想还是简单的。

如果想要结果的字典序最大，那么第一个字符一定是矩阵中最大的那个**非墙壁**字符，即为 $res$。

那么下一个目标即为上下左右中最大的字符，即为 $nxt$。

接着返回 $res$ 的位置，形成一个 $res + nxt$ 的循环节。

考虑到 $res$ 可能有多个，那么每次把最优的情况筛出来，然后打擂台即可。

但是还要注意 $nxt = res$ 或者 $nxt$ 还是原本的初始值（即为 $res$ 的格子周围都是墙），只需要输出一个 $res$ 即可。


------------

```cpp
#include<bits/stdc++.h>

#define int long long
#define _Dark_Star exit(0)
#define inf 1e18
#define up(i,x,y) for(register int i=x;i<=y;i++)
#define dn(i,x,y) for(register int i=x;i>=y;i--)
#define max(x ,y) x > y ? x : y
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return x*f;}
inline void write(int x){if(x<0)putchar('-'),x=-x;if(x>9)write(x/10);putchar(x%10|48);}
inline void writeln(int x){write(x),putchar('\n');}
inline void writesp(int x){write(x),putchar(' ');}
char a[1005][1005];

char str = '0';
char res;

signed main(){
  int n = read() ,m = read();
  up(i,1,n) up(j,1,m) {
      cin >> a[i][j];
      if(a[i][j] != '#') res = max(res ,a[i][j]);
    }
  up(i,1,n)
    up(j,1,m)
      if(a[i][j] == res){
        char nxt = '0';
        /* 比最大值。*/
        if(a[i + 1][j] != '#') nxt = a[i + 1][j];
        if(a[i][j + 1] != '#') nxt = max(nxt ,a[i][j + 1]);
        if(a[i - 1][j] != '#') nxt = max(nxt ,a[i - 1][j]);
        if(a[i][j - 1] != '#') nxt = max(nxt ,a[i][j - 1]);
        if(nxt > str && nxt != '0') str = nxt;
      }
    if(str == '0' || res == str) cout << res << endl;//注意特判。
    else cout << res << str << endl;
  _Dark_Star;
}
```

---

## 作者：gavinliu266 (赞：0)

字典序最大，所以从最大那格开始走。

当走了两格时，形成了路径，因为是从大的走过来，就可以退回去了，这样字典序一定是最大的。

所以循环节长度最大为 $2$。

记得特判长度为 $1$ 循环节和只有一个空位的情况。

时间复杂度 $O(nm)$。

---

