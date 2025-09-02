# [USACO23FEB] Stamp Grid B

## 题目描述

盖章绘画是一幅黑白画，绘制在一个 $N \times N$ 的画布上，其中某些格子被涂黑，而其他格子为空白。它可以用一个 $N \times N$ 的字符数组表示（$1 \leq N \leq 20$）。如果数组的第 $i$ 行第 $j$ 列的值为 `*`，说明该格子被涂黑；如果为 `.`，则说明该格子为空白。

Bessie 想要完成一幅盖章绘画，因此 Farmer John 借给了她一块 $K \times K$（$1 \leq K \leq N$）的盖章，以及一块空的 $N \times N$ 画布。Bessie 可以将盖章顺时针旋转 $90^\circ$，并在画布上的任意位置盖章，只要盖章完全在画布范围内即可。形式化地说，盖章时，Bessie 选择整数 $i,j$，满足 $i \in [1,N-K+1]$ 且 $j \in [1,N-K+1]$；对于每个 $(i',j')$，其中 $1 \leq i',j' \leq K$，画布上的格子 $(i+i'-1,j+j'-1)$ 会被涂黑，如果盖章在 $(i',j')$ 处有墨迹。Bessie 可以在每次盖章之前旋转盖章。一旦画布上的某个格子被涂黑，就会保持涂黑状态。

Farmer John 想知道，Bessie 是否可以用他的盖章完成她想要的盖章绘画。对于每个 $T$（$1 \leq T \leq 100$）个测试用例，帮助 Farmer John 回答这个问题。

## 样例 #1

### 输入

```
4

2
**
*.
1
*

3
.**
.**
***
2
.*
**

3
...
.*.
...
3
.*.
...
...

3
**.
.**
..*
2
.*
*.```

### 输出

```
YES
YES
NO
YES```

# 题解

## 作者：Furina_Hate_Comma (赞：7)

一道大**暴力**。

~~话说 USACO 是不是和 CCF 学的赛时放那么恶心的题。~~

回归正题：

由于格子只会由白变黑，不会由黑变白。

所以直接枚举 4 个方向判断有没有不应该黑的格子黑了（注意不是错了因为后面还可以印）。

代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define neverTLE ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define reg register
#define endl '\n'
int t,n,k;
int main(){
	neverTLE;
	cin>>t;
	while(t--){
		cin>>n;
		char mp[30][30]={0},st[30][30]={0},bd[30][30]={0};
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>mp[i][j];
			}
		}
		cin>>k;
		for(int i=1;i<=k;i++){
			for(int j=1;j<=k;j++){
				cin>>st[i][j];
			}
		}
		
		for(int i=1;i+k-1<=n;i++){
			for(int j=1;j+k-1<=n;j++){
				bool flag=1;
				for(int ii=i,iii=1;ii<=i+k-1;ii++,iii++){
					for(int jj=j,jjj=1;jj<=j+k-1;jj++,jjj++){
						if(mp[ii][jj]!=st[iii][jjj]&&mp[ii][jj]=='.'){
							flag=0;
						}
					}
				}
				if(flag){
				for(int ii=i,iii=1;ii<=i+k-1;ii++,iii++){
					for(int jj=j,jjj=1;jj<=j+k-1;jj++,jjj++){
						if(bd[ii][jj]!='*')	bd[ii][jj]=st[iii][jjj];
					}
				}
				}
				flag=1;
				for(int ii=i,jjj=k;ii<=i+k-1;ii++,jjj--){
					for(int jj=j,iii=1;jj<=j+k-1;jj++,iii++){
						if(mp[ii][jj]!=st[iii][jjj]&&mp[ii][jj]=='.'){
							flag=0;
						}
					}
				}
				if(flag){
				for(int ii=i,jjj=k;ii<=i+k-1;ii++,jjj--){
					for(int jj=j,iii=1;jj<=j+k-1;jj++,iii++){
							if(bd[ii][jj]!='*')bd[ii][jj]=st[iii][jjj];
					}
				}
				}
				flag=1;
				for(int ii=i,iii=k;ii<=i+k-1;ii++,iii--){
					for(int jj=j,jjj=k;jj<=j+k-1;jj++,jjj--){
						if(mp[ii][jj]!=st[iii][jjj]&&mp[ii][jj]=='.'){
							flag=0;
						}
					}
				}
				if(flag){
				for(int ii=i,iii=k;ii<=i+k-1;ii++,iii--){
					for(int jj=j,jjj=k;jj<=j+k-1;jj++,jjj--){
						if(bd[ii][jj]!='*')	bd[ii][jj]=st[iii][jjj];
					}
				}
				}
				flag=1;
				for(int ii=i,jjj=1;ii<=i+k-1;ii++,jjj++){
					for(int jj=j,iii=k;jj<=j+k-1;jj++,iii--){
						if(mp[ii][jj]!=st[iii][jjj]&&mp[ii][jj]=='.'){
							flag=0;
						}
					}
				}
				if(flag){
				for(int ii=i,jjj=1;ii<=i+k-1;ii++,jjj++){
					for(int jj=j,iii=k;jj<=j+k-1;jj++,iii--){
						if(bd[ii][jj]!='*')	bd[ii][jj]=st[iii][jjj];
					}
				}
				}
			}
		}
		int flagg=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(bd[i][j]!=mp[i][j]&&mp[i][j]=='*'){
					flagg=1;
					goto jump;
				}
			}
		}
		jump:
		/*for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cout<<bd[i][j]<<' ';
			}
			cout<<endl;
		}
		*/
		if(flagg){
			cout<<"NO"<<endl;
		}
		else{
			cout<<"YES"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：ivyjiao (赞：6)

题意：给一块 $N\times N$ 的画布（初始为白，给出的是目标状态，颜色非黑即白）和一块 $K\times K$ 的印章（状态给定，颜色非黑即白），每次可以把印章旋转任意次 $90$ 度再在画布的任意一个地方涂色，**画布上不可以有多余的黑色**，你需要判断这个印章能否将一块纯白的画布涂成给定的目标状态。

思路：直接暴力旋转印章再暴力比较是否有多余的黑色，如果没有，进行涂色即可，不需要任何优化。

**注意：画布不可以旋转**。赛时被 deepl 坑了，WA 了一发。

代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
long long t,n,k;
char a[21][21],b[21][21],c[21][21];
bool p[21][21],boo,boo2;
int main(){
    cin>>t;
    while(t--){
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(c,0,sizeof(c));
        memset(p,0,sizeof(p));
        boo=0;
        boo2=0;
        cin>>n;
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a[i][j];
        cin>>k;
        for(int i=1;i<=k;i++) for(int j=1;j<=k;j++) cin>>b[i][j];
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(a[i][j]=='.') p[i][j]=1;
        for(int v=1;v<=4;v++){
            //for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) c[j][n-i+1]=a[i][j];
            //for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=c[i][j];
            for(int i=1;i<=n-k+1;i++){
                for(int j=1;j<=n-k+1;j++){
                	for(int w=1;w<=4;w++){
	                    boo=0;
						for(int f=1;f<=k;f++) for(int g=1;g<=k;g++) c[g][k-f+1]=b[f][g];
						for(int f=1;f<=k;f++) for(int g=1;g<=k;g++) b[f][g]=c[f][g];
	                    for(int f=i;f<=i+k-1;f++) for(int g=j;g<=j+k-1;g++) if(a[f][g]=='.'&&b[f-i+1][g-j+1]=='*') boo=1;
	                    if(!boo) for(int f=i;f<=i+k-1;f++) for(int g=j;g<=j+k-1;g++) if(a[f][g]=='*'&&b[f-i+1][g-j+1]=='*') p[f][g]=1;
					}
                }
            }
        }
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(!p[i][j]) boo2=1;
        if(!boo2) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}

```

---

## 作者：chlchl (赞：6)

第二题模拟属实是有点恶心，差点没调出来。

## Solution
设大矩阵为纸面，小矩阵为印章。

贪心，因为印章可以旋转，所以对于纸面的每个位置，都尝试从四个角度盖印章。只要不出现纸面是白的，印章的相应位置是黑的，就能够盖上去。

这样一定可以保证最后覆盖到的黑点最多。

接下来讲讲实现。

每次预处理出四次旋转的印章，具体的式子留给读者自行推导，也可以看代码。

然后枚举放的左上角，分四次枚举即可。善用函数可以帮助你减少码量。

还要开个数组记录每个位置是否已经被覆盖过，这个在实现过程中应该是比较容易想到的。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 20 + 5;
int T, n, k, g[N][N], st[N][N], st1[N][N], st2[N][N], st3[N][N];
bool vis[N][N];
char s[N];

void trying(int a[][N], int x, int y){
	bool f = 1;
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++){
			if(a[i][j] && !g[i + x - 1][j + y - 1]){
				f = 0;
				break;
			}
		}
		if(!f)
			break;
	}
	if(f){
		for(int i=1;i<=k;i++)
			for(int j=1;j<=k;j++)
				if(a[i][j])
					vis[i + x - 1][j + y - 1] = 1;
	}
}

void meiju(int x, int y){//贪心，只要能印你就印它 
	trying(st, x, y);
	trying(st1, x, y);
	trying(st2, x, y);
	trying(st3, x, y);
}

int main(){
	scanf("%d", &T);
	while(T--){
		memset(vis, 0, sizeof(vis));
		scanf("%d", &n);
		for(int i=1;i<=n;i++){
			scanf("%s", s + 1);
			for(int j=1;j<=n;j++)
				g[i][j] = (s[j] == '*' ? 1 : 0);
		}
		scanf("%d", &k);
		for(int i=1;i<=k;i++){
			scanf("%s", s + 1);
			for(int j=1;j<=k;j++)
				st[i][j] = (s[j] == '*' ? 1 : 0);
		}
		//预处理旋转三次的矩阵 
		for(int i=1;i<=k;i++)
			for(int j=1;j<=k;j++)
				st1[j][k - i + 1] = st[i][j];
		
		for(int i=1;i<=k;i++)
			for(int j=1;j<=k;j++)
				st2[j][k - i + 1] = st1[i][j];

		for(int i=1;i<=k;i++)
			for(int j=1;j<=k;j++)
				st3[j][k - i + 1] = st2[i][j];
		
		for(int x=1;x<=n-k+1;x++)
			for(int y=1;y<=n-k+1;y++)
				meiju(x, y);//左上角 
		bool ok = 1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(g[i][j] && !vis[i][j]){
					ok = 0;
					printf("NO\n");
					break;
				}
			}
			if(!ok)//避免多次输出 NO 
				break;
		}
		if(ok)
			printf("YES\n");
	}
	return 0;
}
/*这个样例可以帮你检查是否旋转正确 
3
...
...
..*
2
*.
..
*/
```


---

## 作者：incra (赞：5)

## 题解
题意都看得懂吧，不放了。

拿一块新画布（注意新画布是全白的），把盖章在新画布上盖。当遇到在某一处盖章时，画布上的图案相比与目标画布，没有多余的黑色。（这里多余是指，当目标画布某一格上是白的，那么新画布上同一位置的格子一定也是白的；当目标画布某一格上是黑的，那么新画布上同一位置的格子**两种颜色都有可能**）注意到题目中有提到可以旋转盖章 $90^\circ$，所以我们就把盖章再每一个角度下在新画布上盖，并使得盖了之后与目标画布相比没有多余的黑色。

当四个方向都改完之后，我们直接判断新画布与目标画布是否相同即可。

这里再来重点讲一下旋转。

设一个矩阵 $a=\left\lbrack\begin{matrix}1&2&3\\4&5&6\\7&8&9\end{matrix}\right\rbrack$，把它顺时针旋转 $90^\circ$ 后得到新矩阵 $b=\left\lbrack\begin{matrix}7&4&1\\8&5&2\\9&6&3\\\end{matrix}\right\rbrack$。我们可以看一下对应数的变化位置：$(1,1)\Longrightarrow(1,3),(3,2)\Longrightarrow(2,1),(2,2)\Longrightarrow(2,2)$。
相信大家肯定都能发现，一个点 $(x,y)$，在顺时针旋转 $90^\circ$ 后移到 $(y,m-x+1)$。（$m$ 是矩阵边长，这里是 $3$）

Talk is cheap,show me the code.
## 代码
```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int N = 30;
int n,m;
char a[N][N],b[N][N];
char ans[N][N];
char tmp[N][N];
void rotate () {
	for (int i = 1;i <= m;i++) {
		for (int j = 1;j <= m;j++) tmp[j][m - i + 1] = b[i][j];
	}
	for (int i = 1;i <= m;i++) {
		for (int j = 1;j <= m;j++) b[i][j] = tmp[i][j];
	}
}
void work (int x,int y) {
	for (int i = 1;i <= m;i++) {
		for (int j = 1;j <= m;j++) {
			if (a[x + i - 1][y + j - 1] == '.' && b[i][j] == '*') return ;
		}
	}
	for (int i = 1;i <= m;i++) {
		for (int j = 1;j <= m;j++) {
			if (b[i][j] == '*') ans[x + i - 1][y + j - 1] = '*';
		}
	}
}
int main () {
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1;i <= n;i++) cin >> a[i] + 1;
		cin >> m;
		for (int i = 1;i <= m;i++) cin >> b[i] + 1;
		memset (ans,'.',sizeof (ans));
		for (int i = 0;i < 4;i++) {
			rotate ();
			for (int i = 1;i <= n - m + 1;i++) {
				for (int j = 1;j <= n - m + 1;j++) work (i,j);
			}
		}
		bool flag = true;
		for (int i = 1;i <= n;i++) {
			for (int j = 1;j <= n;j++) {
				if (a[i][j] != ans[i][j]) {
					flag = false;
					break;
				}
			}
		}
		if (flag) puts ("YES");
		else puts ("NO");
	}
	return 0;
}
```

---

## 作者：Xy_top (赞：4)

这题刚看觉得很难，再一看数据范围。躺着都能过！

暴力思路：

由于板子可以旋转，且涂过色后就不会消掉了。所以我们枚举每一个位置，看看板子能不能放进去并且不涂到不想涂的地方，可以的话就标记一下。

做完后我们再把板子旋转 $90$ 度，这样三次之后我们看所有被标记的位置有没有和目标画板重合，如果没有那就不行，否则就行。

最后一句话，多测不清空见祖宗！

代码虽然长，可是它好写啊。

```cpp
#include <iostream>
using namespace std;
int T, n, k;
char a[25][25], c[25][25], d[25][25], t[25][25];
void change () {
	for (int i = 1; i <= k; i ++) {
		for (int j = 1; j <= k; j ++) t[i][j] = c[k - j + 1][i];
	}
	for (int i = 1; i <= k; i ++) {
		for (int j = 1; j <= k; j ++) c[i][j] = t[i][j];
	}
}
void paint (int x, int y) {
	for (int i = x; i <= x + k - 1; i ++) {
		for (int j = y; j <= y + k - 1; j ++) if (c[i - x + 1][j - y + 1] == '*' && a[i][j] != '*') return;
	}
	for (int i = x; i <= x + k - 1; i ++) {
		for (int j = y; j <= y + k - 1; j ++) if (c[i - x + 1][j - y + 1] == '*') {
			a[i][j] = '*';
			d[i][j] = '*';
		}
	}
}
void check () {
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) if (a[i][j] == '*' && d[i][j] != '*') {
			cout << "NO" << "\n";
			return;
		}
	}
	cout << "YES" << "\n";
}
int main () {
	cin >> T;
	while (T --) {
		cin >> n;
		for (int i = 1; i <= n; i ++) {
			for (int j = 1; j <= n; j ++) {
				cin >> a[i][j];
				d[i][j] = '.';
			}
		}
		cin >> k;
		for (int i = 1; i <= k; i ++) {
			for (int j = 1; j <= k; j ++) cin >> c[i][j];
		}
		for (int i = 1; i <= 4; i ++) {
			change ();
			for (int i = 1; i <= n - k + 1; i ++) {
				for (int j = 1; j <= n - k + 1; j ++) paint (i, j);
			}
		}
		check ();
	}
	return 0;
}
```


---

## 作者：是青白呀 (赞：3)

## 题目大意 
有一个 $n\times n$ 的染布 $A$ 和 $k \times k$ 的染布 $B$，均只包含黑白两色。现在可以使用染布 $B$ 在一张与 $A$ 大小相同的全为白色的染布上染色，$B$ 上所有的黑色都会将白布的对应位置染黑，且染黑后不再变白。若可以染色任意多次且 $B$ 可以任意旋转 $90^{\circ}$，问是否能将白布染成与染布 $A$ 相同的图案。设 ```*``` 表示黑色，```.``` 表示白色。

## 解决方案
考虑贪心。由于已经染黑的位置可以被多次任意覆盖染色而不会改变颜色，所以我们只需要保证要求为白色的位置不被染黑即可。考虑模拟 $B$ 的四个方向，每个方向分别枚举每个合法的覆盖位置。若此时 $B$ 上所有黑色所对应 $A$ 的位置都为黑色，则进行一次染色操作。所有位置、方向都枚举完后，看白布上图案与 $A$ 的图案是否一致即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=25;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int t,n,k;
int st[N][N],mp[N][N],mi[N][N],co[N][N];
void color(int x,int y){//染色区域左上角的位置为（x,y）
	bool ok=1;
	for(int i=1;i<=k;i++){//判断能否染色
		int xx,yy;//A/白布上实际位置
		xx=i+x-1;
		for(int j=1;j<=k;j++){
			yy=j+y-1;
			if(st[i][j]&&!mp[xx][yy])ok=0;
		}
	}
	if(!ok)return;
	for(int i=1;i<=k;i++){//染色
		int xx,yy;
		xx=i+x-1;
		for(int j=1;j<=k;j++){
			yy=j+y-1;
			if(st[i][j])co[xx][yy]=1;
		}
	}
}
void rotate(){//旋转，mi数组保存旋转前 B 的图案
	for(int i=1;i+k-1<=n;i++){
		for(int j=1;j+k-1<=n;j++)
		    color(i,j);
	}
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++)
		    mi[i][j]=st[i][j];
	}
	for(int i=1;i<=k;i++){
		for(int j=1;j<=k;j++)
		    st[j][k-i+1]=mi[i][j];
	}
}
int main(){
	read(t);
	while(t--){
		memset(co,0,sizeof(co));
		read(n);
		for(int i=1;i<=n;i++){
			string c;
			getline(cin,c);
			for(int j=1;j<=n;j++){
				if(c[j-1]=='*')mp[i][j]=1;
				else mp[i][j]=0;
			}
		}
		read(k);
		for(int i=1;i<=k;i++){
			string c;
			getline(cin,c);
			for(int j=1;j<=k;j++){
				if(c[j-1]=='*')st[i][j]=1;
				else st[i][j]=0;
			}
		}
		for(int i=1;i<=4;i++)
		    rotate();
		bool ok=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)
	            if(mp[i][j]!=co[i][j])ok=0;
		}
		if(!ok)printf("NO\n");
		else printf("YES\n"); 
	}
	return 0;
}
```


---

## 作者：Bulyly (赞：2)


### 思路
- 用章凑布，显然有些位置是不能被盖的，否则要求是空的地方也会被染色。

- 先考虑没有翻转的情况，我们排除掉不能染色的位置，将能染色的位置全部染色，最后用能够被染色的位置来判断能否使所有目标布中的染色位置全部染色。

- 接下来考虑布的翻转的处理，**翻转是相对的**，将章翻转效果是一样的，所以综上所述，将章的四种情况，相当于有四种章，一一判断每一种章能染色的位置，最后检查能不能完整地凑出这张布。

下附代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N=30;
char s[N][N];
char s1[10][N][N];
bool st[N][N];
int T,n,m;


int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(st,0,sizeof st);
		scanf("%d",&n);
	    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
	    scanf("%d",&m);
	    for(int i=1;i<=m;i++) scanf("%s",s1[1][i]+1);
	    for(int t=2;t<=4;t++)
		{
			for(int i=1;i<=m;i++)
				for(int j=1;j<=m;j++)
					s1[t][j][m-i+1]=s1[t-1][i][j];
		}
		
		
	    for(int i=1;i<=4;i++)   
		{
			for(int j=1;j<=n-m+1;j++)
		    {
		    	for(int t=1;t<=n-m+1;t++)
		    	{
		    		bool sg=0;
					for(int j1=j;j1<=j+m-1;j1++)
		    		{
		    			for(int t1=t;t1<=t+m-1;t1++)
		    			{
		    				if(s[j1][t1]=='.' && s1[i][j1-j+1][t1-t+1]=='*')
		    				{
		    					sg=1;
		    					break;
							}
						}
					}
					if(!sg)
					{
						for(int j1=j;j1<=j+m-1;j1++)
			    		{
			    			for(int t1=t;t1<=t+m-1;t1++)
			    			{
			    				if(s1[i][j1-j+1][t1-t+1]=='*') st[j1][t1]=1;
							}
						}
					}
				}
			}
		}  
		bool sg=0;
	    for(int i=1;i<=n;i++)  
	    {
	    	for(int j=1;j<=n;j++)
	    	{
	    		if(st[i][j]==0 && s[i][j]=='*')  sg=1;
			}
		}
	    if(!sg)  puts("YES");
	    else puts("NO");
	       
	}
	
	
	return 0;
}
```


---

## 作者：yangmingshuo114514 (赞：1)

### 题目大意：

问用一个尺寸为 $ K \times K $ 的给定图案的黑白印章，通过旋转、印刷，能否在一张尺寸为 $ N \times N $ 的画布上画出指定的黑白画。

注意：沾了墨水的是黑色，没沾墨水的是白色。如果画布上的一个格子沾上了墨水，那么它就会一直沾着墨水。

### 算法分析：

1. 印章有四种方向，分别是原来的、顺时针旋转 $ 90\degree$ 的、顺时针旋转 $ 180 \degree$ 的、顺时针旋转 $ 270 \degree$ 的。

1. 我们只要枚举印章在画布上可能占的位置，再枚举这四种方向，看看印章上墨水的位置在期望画布上是否都有墨水。

1. 如果是的话，那就标记在实际画布的这个地方对应印章上墨水的位置的格子已经沾上墨水了，否则就不标记。

1. 最后检验在期望画布上有墨水在实际画布上是否都有墨水。如果是，输出 $\verb!YES!$，否则输出 $\verb!NO!$。

**注意**：期望画布上有墨水的位置在印章上不一定有墨水，因为期望画布上有墨水的位置可能以其它的印章方式而印上。

### 代码：

码量虽然大，但是思维难度却不难。

```cpp
#include<cstdio>
#include<cstring>
int t,n,k;
bool vis[23][23],f;
char c[23][23],s[23][23];
int main(){
	scanf("%d",&t);
	while(t--){
		memset(vis,0,sizeof(vis));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				do c[i][j]=getchar(); while(c[i][j]!='*'&&c[i][j]!='.');
		scanf("%d",&k);
		for(int i=1;i<=k;i++)
			for(int j=1;j<=k;j++)
				do s[i][j]=getchar(); while(s[i][j]!='*'&&s[i][j]!='.');
		for(int i=0;i<n-k+1;i++)
			for(int j=0;j<n-k+1;j++){
				f=1;
				for(int p=1;p<=k;p++)
					for(int q=1;q<=k;q++)
						if(s[p][q]=='*'&&c[p+i][q+j]=='.')
							f=0;
				if(f)
					for(int p=1;p<=k;p++)
						for(int q=1;q<=k;q++)
							if(s[p][q]=='*') vis[p+i][q+j]=1;
				f=1;
				for(int p=1;p<=k;p++)
					for(int q=1;q<=k;q++)
						if(s[q][k-p+1]=='*'&&c[p+i][q+j]=='.')
							f=0;
				if(f)
					for(int p=1;p<=k;p++)
						for(int q=1;q<=k;q++)
							if(s[q][k-p+1]=='*') vis[p+i][q+j]=1;
				f=1;
				for(int p=1;p<=k;p++)
					for(int q=1;q<=k;q++)
						if(s[k-q+1][p]=='*'&&c[p+i][q+j]=='.')
							f=0;
				if(f)
					for(int p=1;p<=k;p++)
						for(int q=1;q<=k;q++)
							if(s[k-q+1][p]=='*') vis[p+i][q+j]=1;
				f=1;
				for(int p=1;p<=k;p++)
					for(int q=1;q<=k;q++)
						if(s[k-p+1][k-q+1]=='*'&&c[p+i][q+j]=='.')
							f=0;
				if(f)
					for(int p=1;p<=k;p++)
						for(int q=1;q<=k;q++)
							if(s[k-p+1][k-q+1]=='*') vis[p+i][q+j]=1;
			}
		f=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(c[i][j]=='*')
					if(!vis[i][j])
						f=0;
		printf(f?"YES\n":"NO\n");
	}
	return 0;
}


---

