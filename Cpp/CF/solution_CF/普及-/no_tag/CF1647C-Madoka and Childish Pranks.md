# Madoka and Childish Pranks

## 题目描述

Madoka as a child was an extremely capricious girl, and one of her favorite pranks was drawing on her wall. According to Madoka's memories, the wall was a table of $ n $ rows and $ m $ columns, consisting only of zeroes and ones. The coordinate of the cell in the $ i $ -th row and the $ j $ -th column ( $ 1 \le i \le n $ , $ 1 \le j \le m $ ) is $ (i, j) $ .

One day she saw a picture "Mahou Shoujo Madoka Magica" and decided to draw it on her wall. Initially, the Madoka's table is a table of size $ n \times m $ filled with zeroes. Then she applies the following operation any number of times:

Madoka selects any rectangular subtable of the table and paints it in a chess coloring (the upper left corner of the subtable always has the color $ 0 $ ). Note that some cells may be colored several times. In this case, the final color of the cell is equal to the color obtained during the last repainting.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647C/382bdf687e9360fce9f9a4f6fec3edc2a2101bb5.png)White color means $ 0 $ , black means $ 1 $ . So, for example, the table in the first picture is painted in a chess coloring, and the others are not.For better understanding of the statement, we recommend you to read the explanation of the first test.

Help Madoka and find some sequence of no more than $ n \cdot m $ operations that allows you to obtain the picture she wants, or determine that this is impossible.

## 说明/提示

The description of the first test case is below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1647C/5712ccf8799cc158d880a39b68cfedf66e8a3903.png)In the third test case, it is impossible to paint the desired picture.

In the fourth test case, the initial table is already the desired picture.

## 样例 #1

### 输入

```
4
4 5
01000
10100
01010
00110
2 3
001
010
3 3
110
101
000
1 1
0```

### 输出

```
4
1 1 3 3
3 3 4 4
4 3 4 4
4 2 4 3
1
1 2 2 3
-1
0```

# 题解

## 作者：happy_dengziyue (赞：2)

### 1 思路

首先要注意，我们在处理时要**先处理下面的，若行坐标一致则先处理右边的。**

设目标的矩阵为 $a$。

对于一个 $a[i][j]$，若 $a[i][j]=1$，那么有两种方案可以解决问题：

+ 若 $j>1$，那么进行 $(i,j-1,i,j)$ 操作；

+ 否则进行 $(i-1,j,i,j)$ 操作。

很明显的，因为我们的顺序，覆盖了前面的也没关系，到时候再处理嘛。

但是，如果 $a[1][1]=1$，那么很明显，无法处理，直接无解。

否则保证有解。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 100
int t;
int n;
int m;
int a[max_n+2][max_n+2];
struct O{
	int x1,y1,x2,y2;
}o[max_n*max_n*max_n+2];
bool ok;
int ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1647C_1.in","r",stdin);
	freopen("CF1647C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i){
			char s[max_n+2];
			scanf("%s",s+1);
			for(int j=1;j<=m;++j)a[i][j]=s[j]-'0';
		}
		ans=0;
		if(a[1][1]){
			printf("-1\n");
			continue;
		}
		for(int i=n;i>=1;--i){
			for(int j=m;j>=2;--j){
				if(a[i][j])o[++ans]=(O){i,j-1,i,j};
			}
			if(a[i][1])o[++ans]=(O){i-1,1,i,1};
		}
		printf("%d\n",ans);
		for(int i=1;i<=ans;++i)printf("%d %d %d %d\n",o[i].x1,o[i].y1,o[i].x2,o[i].y2);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/71288337)

By **dengziyue**

---

## 作者：GoodLuckCat (赞：1)

首先理解题意：

>每次染色可以将一个矩形染成国际象棋的颜色。

“国际象棋的颜色”指左上角为白色，而任意一个格子的颜色都不与它上、下、左、右的颜色相同。

在这里，我用 $1$ 表示黑色，$0$ 表示白色。这道题中没有限制染色次数，所以我们可以考虑对每一个黑格子染色。当然，如果这个结果的左上角就是黑色，那一定不可能染色成功，因为每一次染色都需要确保左上角为白色。而要将左上角染成黑色，是不可能的（即使染到了也一定是白色）。

但是如果左上角是白色，一定可以成功。我们可以想到这两块“棋盘”：

```
01

0
1
```
这两块棋盘中，黑色格子只有一个。所以可以考虑，对于每一个黑方格，做一个这种棋盘，覆盖上去。

但是如果你按照左上角到右下角的顺序染色，会出现一个问题。这两种棋盘如果放上去，会把它左边或者上面的一个格子顺便染成白色。解决这种问题的方法是从右下角染到左上角。即使把上面的格子染成白色，还可以再做一次操作来覆盖。

这代码中是按照先用一种染色方法染，当到边界时用另一种方法染。

代码：

```cpp
#include<iostream>
using namespace std;
char s[101][101];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m,p=0,e=0;
        cin>>n>>m;
        for(int x=1;x<=n;x++)
        {
            for(int y=1;y<=m;y++)
            {
                cin>>s[x][y];
                if(s[x][y]=='1')e++;
            }
        }
        if(s[1][1]=='1')cout<<"-1\n";
        else
        {
            cout<<e<<endl;
            for(int x=n;x>=1;x--)
            {
                for(int y=m;y>=1;y--)
                {
                    if(s[x][y]=='1')
                    {
                        if(x==1)printf("%d %d %d %d\n",x,y-1,x,y);
                        else printf("%d %d %d %d\n",x-1,y,x,y);
                    }
                }
            }
        }
    }
    return 0;
}
```

[用时 $62$ 毫秒 AC](https://www.luogu.com.cn/record/145894931)。

---

## 作者：封禁用户 (赞：1)

考虑上下或左右相邻的两个格子，如果将这个矩形染色，那么上（左）将会被染成白色，下（右）将会被染成黑色。

那么我们考虑对第二行到最后一行染色，从下往上染，如果有一个格子需要染成黑色，那么我们将这个格子与其上面的格子组成的矩形染色即可。

然后再对第一行的第二列到最后一列染色，从右往左染，如果有一个格子需要染成黑色，那么我们将这个格子与其左边面的格子组成的矩形染色即可。

最后在考虑 (1,1)，显然他只能是白色，所以如果 (1,1) 是黑色直接输出`NO`即可。
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=140;
int T,n,m,num,a[maxn][maxn];
int main()
{
    cin>>T;
    for(int x=1;x<=T;x++)
    {
        cin>>n>>m;
        num=0;
        for(int i=1;i<=n;++i)
        {
            getchar();
            for(int j=1;j<=m;j++)
            {
            	a[i][j]=getchar()-'0';
            	num+=a[i][j];
            }
        }
        if(a[1][1])
        {
            cout<<"-1\n";
            continue;
        }
        cout<<num<<"\n";
        for(int j=1;j<=m;j++)
        {
        	for(int i=n;i>1;--i)
        	{
        		if(a[i][j])
        		{
        			cout<<i-1<<" "<<j<<" "<<i<<" "<<j<<"\n";
        		}
        	}
        }
        for(int j=m;j>1;--j)
        {
        	if(a[1][j])
        	{
        		cout<<"1 "<<j-1<<" 1 "<<j<<"\n";
        	}
        }
        memset(a,0,sizeof(a));
    }
    return 0;
}
```

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1647C)

分两类讨论。

- 首先，左上角如果是黑色，就肯定涂不了。

- 否则，每个黑色格子和它上面的、左面的格子组成子矩阵，就直接涂色。

注意：想要防止黑色被覆盖，就要从**最后**开始涂。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
    int t;
	cin >>t;
	while(t--){
		int n,m;
		cin >>n>>m;
		char a[n][m];
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cin >>a[i][j];
			}
		}
		int s=0;//白色格子的个数 
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(a[i][j]=='1'){//白色格子
					s++;//数量加一 
				}
			}
		}
		if(a[0][0]=='1'){//特殊情况 
			cout<<-1<<endl;
		}else{
			cout<<s<<endl;//先输出白色格子的个数 
			for(int i=n-1;i>=0;i--){
				for(int j=m-1;j>=0;j--){//从后往前 
					if(a[i][j]=='0'){//是黑色格子 
						continue;//看下一个 
					}
					if(i>0){//i>0的情况（i!=0） 
						cout<<i<<" "<<j+1<<" "<<i+1<<" "<<j+1<<endl;
					}else{//i<=0的情况（i=0） 
						cout<<i+1<<" "<<j<<" "<<i+1<<" "<<j+1<<endl;
					}
				}
			}
		}
	}
	return 0;
}
```

---

## 作者：__O_w_O__ (赞：0)

首先，要知道国际象棋的颜色是什么样子的，不知道的可以自行百度，这里简单概括一下，大致就是左上角是白色，然后任意一个格子的颜色和它的上下左右的格子的颜色都不相同。

如此一来就可以想到无解的情况，题目没有限制染色的次数，那么无解的情况就只能是这个输入的矩阵的左上角就是黑色（因为每次染色的时候需要左上角是白色，然而将左上角染成黑色是不可能的），直接特判掉即可。

发现如果按照正常的思路正着枚举进行染色的话就会出现问题，因为正着染色会把当前格子的左边或者上边的格子也染色。

由此不难想到在染色的时候可以倒着枚举，即从右下角枚举到左上角。

至于染色的方法，可以先用一种染色发染，到达边缘的时候用另一种方法进行染色。

[通过记录](https://codeforces.com/problemset/submission/1647/278456459)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 110;
char s[N][N];
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%s", s[i] + 1);
            for (int j = 1; j <= m; j++) {
                if (s[i][j] == '1') cnt++;
            }
        }
        if (s[1][1] == '1') {
            printf("-1\n");
            continue;
        }
        printf("%d\n", cnt);
        for (int i = n; i >= 1; i--) {
            for (int j = m; j >= 1; j--) {
                if (s[i][j] == '1') {
                    if (i == 1) printf("%d %d %d %d\n", i, j - 1, i, j);
                    else printf("%d %d %d %d\n", i - 1, j, i, j);
                }
            }
        }
    }
    return 0;
}

```

---

## 作者：Norsuman371 (赞：0)

# 思路

因为每次操作左上角都为 $0$，因此无论如何选择，都无法使 $(1,1)$ 变为 $1$，因此无解情况是仅当 $a_{1,1}$ 为 $1$，对于其他的，可以每次选择 $1 \times 2$ 的矩形，从最后一列开始填充，如 $a_{i,j}$ 为 $1$，那可以选择 $(i,j,i,j-1)$ 的矩形，由于是从最后一列开始，因此不用考虑覆盖问题。现在除第一列，都已经填充完毕，第一列同理，选择 $2 \times 1$ 的矩形，从 $(n,1)$ 填充变为 $(2,1)$，如此完成填充。

# Code

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 105;
char a[N][N];
struct node {
    int x1, y1, x2, y2;
};
void solve() {
    int n, m;
    vector < node > ans;
    scanf("%d%d", & n, & m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) scanf(" %c", & a[i][j]);
    if (a[1][1] == '1'){
        printf("-1\n");
        return;
    }
    for (int i = 1; i <= n; i++){
        for (int j = m; j >= 2; j--) {
            if (a[i][j] == '1') ans.push_back({
                i,
                j - 1,
                i,
                j
            });
        }
    }
    for (int i = n; i >= 2; i--){
        if (a[i][1] == '1') ans.push_back({
            i - 1,
            1,
            i,
            1
        });
    }
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
        int x1 = ans[i].x1;
        int y1 = ans[i].y1;
        int x2 = ans[i].x2;
        int y2 = ans[i].y2;
        printf("%d %d %d %d\n", x1, y1, x2, y2);
    }
}
int main() {
    int t = 1;
    scanf("%d", & t);
    while (t--) solve();
    return 0;
}
```

# 记录

[AC](https://www.luogu.com.cn/record/167558616)

---

## 作者：sf_wyc (赞：0)

题意：

有一个 $n × m$ 的矩阵（其实简单理解就是二维数组），最初所有格子都是白色的（也就是 $1$），没有黑色格子（也就是 $-1$）。你最多进行 $n × m$ 次操作，你每次可以选择一个大小任意的非空子矩阵，将这个子矩阵的第 $i$ 行，第 $j$ 列染成 $-1$ 的 $i+j$  次幂（请注意，矩阵左上一直是白色）。给定一个目标状态，问是否可以在规定次数的操作内将原矩阵变成目标状态。

如果染色的话，那么这个格子的上、左会被染成白色，下、右则会是黑色

所以我们先考虑从左至右，在考虑从上至下。

最后在查找 `ans[1][1]` 的位置，显然他只能是白色，所以如果 `ans[1][1]` 是黑色直接输出 `-1` 就行。

代码不长，只有四十几行：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mx = 140;

int main() {
	long long int cs;
	long long int n, m, cnt, ans[mx][mx];
	cin >> cs;
	
	for (int k = 1; k <= cs; k++) {
		cin >> n >> m;
		cnt = 0;
		for (int i = 1; i <= n; i++) {
			getchar();
			for (int j = 1; j <= m; j++) {
				ans[i][j] = getchar() - '0';
				num += ans[i][j];
			}
		}
		if (ans[1][1] == true) 
		{
			cout << "-1" << endl;
			continue;
		}
		cout << cnt << endl;
		for (int j = 1; j <= m; j++) {
			for (int i = n; i > 1; i--) {
				if (ans[i][j] == true) {
					cout << i - 1 << " " << j << " " << i << " " << j << endl;
				}
			}
		}
		for (int j = m; j > 1; j--) {
			if (ans[1][j] == true) {
				cout << "1 " << j - 1 << " 1 " << j << endl;
			}
		}
		for(int i = 0;i < mx;i++)
			for(int j = 0;j < mx;j++) 
				ans[i][j] = 0;
	}
	return 0;
}

```

---

## 作者：BMTXLRC (赞：0)

既然题目不要求求出最小方案数，我们考虑如何贪心。

假设我们现在遇到了这么一种情况：

```
011
```

那么很显然我们的方案应该是：

```
1 2 1 3
1 1 1 2
```

这两个操作是不可以倒过来的，也就是说对于一行 $1$，我必须从右往左进行覆盖。

那如果第一列是 $1$ 呢，同理可得，一定要从下往上进行覆盖。

这时就不难发现不满足要求的矩阵一定是最左上角为 $1$ 的，因为这个地方无法找到一个在他上面或左边的方块进行涂色。

所以我们贪心方案即为：从右下往左上遍历，遇到一个黑色的就输出这个覆盖长方形，是上面的还是左边的取决于是否在第一列。

由于我们对于每个黑色方块都要进行一次覆盖，所以我们这个贪心方案的方案数就应该是整个矩阵中黑色方块的数量。

```cpp
//CF1647-C
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int T,n,m;
char a[N][N];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&n,&m);
        int ans=0;
        for(register int i=1;i<=n;i++){
            scanf("%s",a[i]+1),a[i][m+1]='\0';
            for(register int j=1;j<=m;j++) ans+=(a[i][j]=='1');
        }
        if(a[1][1]=='1'){
            printf("-1\n");
            continue;
        }
        printf("%d\n",ans);
        for(register int i=n;i>=1;i--){
            for(register int j=m;j>=1;j--){
                if(a[i][j]=='1'&&j!=1) printf("%d %d %d %d\n",i,j-1,i,j);
                if(a[i][j]=='1'&&j==1) printf("%d %d %d %d\n",i-1,j,i,j);
            }
        }
    }
}
```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1647C](https://www.luogu.com.cn/problem/CF1647C)

* **【题目翻译】**

有一个 $n\times m$ 的矩阵，开始时里面的值全为 $1$（$1$ 为白，$-1$ 为黑）。你最多可以进行 $nm$ 次操作，每次可以选择一个任意大小的非空子矩阵，将这个子矩阵的第 $i$ 行第 $j$ 列变成 $(-1)^{i+j}$（棋盘状染色，左上角总是白色）。给定一个目标状态，问是否可以在规定次数的操作内将原矩阵变成目标状态。

* **【解题思路】**

首先加入目标状态第一行第一列为黑（$-1$），那么显然无解。否则，我们可以每找到一个黑格就在原矩阵执行以下操作：

* 如果该黑格在第一行，设它的位置为 $(1,j)$，选定子矩阵 $(1,j-1)\sim(1,j)$。

* 否则，设它的位置为 $(i,j)$，选定子矩阵 $(i-1,j)\sim(i,j)$。

另外，后面的操作会覆盖前面的操作，所以我们找黑格要从最后一行开始倒序枚举行，处理第一行时要倒序枚举列。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>
 
using namespace std;
 
array<array<char,100>,100> grid;
 
int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		int line,row,cnt=0;
		cin>>line>>row;
		for(int i=0;i<line;i++)
			for(int j=0;j<row;j++)
				cin>>grid[i][j],cnt+=grid[i][j]-'0';
		if(grid[0][0]=='1')
		{
			cout<<-1<<'\n';
			goto nextcase;
		}
		cout<<cnt<<'\n';
		for(int i=line-1;i;i--)
			for(int j=0;j<row;j++)
				if(grid[i][j]=='1')
					cout<<i<<' '<<j+1<<' '<<i+1<<' '<<j+1<<'\n';
		for(int j=row-1;j;j--)
			if(grid[0][j]=='1')
				cout<<1<<' '<<j<<' '<<1<<' '<<j+1<<'\n';
		nextcase:;
	}
	return 0;
}
```

---

## 作者：清烛 (赞：0)

题意：$n\times m$ 网格，一次可以选择一个矩形区域然后进行“棋盘染色”。棋盘染色说的是，左上角为白色，相邻格子的颜色相反。请构造方案从空白局面染成给定局面或报告无解。

注意到这种染色问题，后涂的色会覆盖掉前涂的色。

然后，遇到一个 $1$ 的时候，我们可以以左边的格子为“棋盘的左上角”，染 $1\times 2$ 的区域。但是若遇到最左边的 $1$ 的话，需要借助形如下面的方法染色：

```
10
01
```

所以很明显，若整个棋盘左上角为 $1$，则肯定是无解的。

那么我们就从右下角开始，一步步往左往上遍历，可以发现前面涂好色的格子不会再被影响。于是本题得到解决。

```cpp
const int maxn = 105;
char a[maxn][maxn];
int n, m;

#define mkpr make_pair
#define fi first
#define se second

int main() {
    int T; read(T);
    while (T--) {
        read(n, m);
        FOR(i, 1, n) read(a[i] + 1);
        if (a[1][1] == '1') {
            print(-1);
            continue;
        }
        vector<pair<pair<int, int>, pair<int, int> > > ans;
        DEC(i, n, 1) DEC(j, m, 1) {
            if (a[i][j] == '0') continue;
            if (j == 1) ans.push_back(mkpr(mkpr(i - 1, j), mkpr(i, j)));
            else ans.push_back(mkpr(mkpr(i, j - 1), mkpr(i, j)));
        }
        print(ans.size());
        for (auto &p : ans) print(p.fi.fi, p.fi.se, p.se.fi, p.se.se);
    }
    return output(), 0;
}
```

---

## 作者：ArrogHie (赞：0)

## 题解

因为不限于操作次数，所以很容易想到对于每一个黑块单独处理。手玩样例即可发现：对于一个位于 $(x,y)$ 的黑块，若 $y \neq 1$，则直接选 $(x,y-1)\sim (x,y)$ 这段格子染色；若 $y=1$，则选择 $(x-1,y)\sim (x,y)$ 染色。从右下角到左上角依次处理每一个黑块即可。若 $(1,1)$ 为黑色则无解，否则都能通过上述构造方法构造。

---

## 作者：JS_TZ_ZHR (赞：0)

## 题意：

给定一个初始全是白色的矩阵，矩阵里只能涂黑白两种颜色，你可以选择一个子矩阵，坐上角涂白色，相邻格子不同颜色的涂。最后你要得到一个指定矩阵。

## 题解：

左上角为黑色肯定涂不了。对于其他情况，每个黑色格子和它上方/左边的格子组成子矩阵直接涂色。为了放止黑色被覆盖，从最后开始涂。

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long 
using namespace std;
int T,n,m,cnt;
char s[1005][1005];
signed main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		bool flag=1;
		for(int i=1;i<=n;i++)cin>>s[i]+1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(s[i][j]=='1')cnt++;
			}
		}
		
		if(s[1][1]=='1')puts("-1"),cnt=0;
		else{
			cout<<cnt<<endl;
			cnt=0;
			for(int i=n;i>=1;i--){
				for(int j=m;j>=1;j--){
					if(s[i][j]=='0')continue;
					if(i>1){
						cout<<i-1<<' '<<j<<' '<<i<<' '<<j<<endl;
					}
					else{
						cout<<i<<' '<<j-1<<' '<<i<<' '<<j<<endl;
					}
				}
			}
		}
	}
} 
```


---

