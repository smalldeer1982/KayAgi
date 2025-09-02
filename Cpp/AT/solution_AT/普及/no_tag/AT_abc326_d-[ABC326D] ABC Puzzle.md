# [ABC326D] ABC Puzzle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc326/tasks/abc326_d

整数 $ N $ と `A`, `B`, `C` からなる長さ $ N $ の文字列 $ R,C $ が与えられるので、以下の問題を解いてください。

$ N\ \times\ N $ のマス目があり、最初全てのマスは空きマスです。  
 各マスに `A`, `B`, `C` のうち高々 $ 1 $ 文字を書き込みます。( 空きマスのままにすることも許されます )

以下の条件を全て満たすことが可能であるか判定し、可能であれば書き込み方を $ 1 $ つ出力して下さい。

- 各行 / 各列 に `A`, `B`, `C` がちょうど $ 1 $ 個ずつ含まれる
- $ i $ 行目に書かれた文字の中で最も左にある文字は $ R $ の $ i $ 文字目と一致する
- $ i $ 列目に書かれた文字の中で最も上にある文字は $ C $ の $ i $ 文字目と一致する

## 说明/提示

### 制約

- $ N $ は $ 3 $ 以上 $ 5 $ 以下の整数
- $ R,C $ は `A`, `B`, `C` からなる長さ $ N $ の文字列
 
### Sample Explanation 1

出力例のマス目は以下の条件を全て満たすため、正解として扱われます。 - 全ての行に `A`, `B`, `C` がちょうど $ 1 $ 個ずつ含まれる - 全ての列に `A`, `B`, `C` がちょうど $ 1 $ 個ずつ含まれる - 各行に書かれた最も左の文字は上から順に `A`, `B`, `C`, `B`, `C` である - 各列に書かれた最も上の文字は左から順に `A`, `C`, `A`, `A`, `B` である

### Sample Explanation 2

この入力では、条件を満たす書き込み方は存在しません。

## 样例 #1

### 输入

```
5
ABCBC
ACAAB```

### 输出

```
Yes
AC..B
.BA.C
C.BA.
BA.C.
..CBA```

## 样例 #2

### 输入

```
3
AAA
BBB```

### 输出

```
No```

# 题解

## 作者：cherry2010 (赞：12)

## ABC326D ABC Puzzle 题解

题意：找到一个 $N\times N$ 的矩阵，使其每一行每一列都恰好有一个 $A$，$B$ 和 $C$，且第 $i$ 行中的最左边的字符与字符串 $R$ 的第 $i$ 个字符匹配，第 $i$ 列中的最上边的字符与字符串 $C$ 的第 $i$ 个字符匹配。

### 分析

------------

看到题目，脑海里浮现出了 [八皇后](https://www.luogu.com.cn/problem/P1219) 一题，想到**暴力枚举所有的矩阵**。想完看看 $N$ 的范围，$N$ 是 3 到 5 之间的一个整数；再看看时间限制，4 秒，此方法肯定能过。

重点就在于**如何枚举所有的矩阵**。本人码力弱到了极点……故思考结果为，从上至下建图，对于每一行的，枚举一个全排列，若第 $i$ 个数为 1，则填上 $A$；若第 $i$ 个数为 2，则填上 $B$；若第 $i$ 个数为 3，则填上 $C$。这样就可以保证每一行都恰好出现一个 $A$，$B$ 和 $C$。同时，需要维护每一列三个字母是否出现。

在建好矩阵后，就只需要判断这个矩阵是否满足条件即可。

> 补充：枚举全排列时推荐 `next_permutation` 函数，非常方便！

### 代码

------------

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
bool mark[10][3];//mark[i][j]指第i列中j是否出现（j=0指字母A,j=1指字母B,j=2指字母C）
string r,c;
char a[10][10];
void check(char p[][10])//判断这个矩阵是否合法 
{
	for(int i=1;i<=n;i++)//判断第一个条件
	{
		for(int j=1;j<=n;j++)
		{
			if(p[i][j]!='.')
			{
				if(p[i][j]!=r[i-1]) return;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)//判断第二个条件
	{
		for(int j=1;j<=n;j++)
		{
			if(p[j][i]!='.')
			{
				if(p[j][i]!=c[i-1]) return;
				break;
			}
		}
	}
	printf("Yes\n");//找到就输出 
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cout<<p[i][j];
		}
		printf("\n");
	}
	exit(0);
}
void graph(int x) //x表示当前已经排列好的行数 
{
	if(x==n)
	{
		check(a);
		return;
	}
	x++;
	int p[5]={1,2,3,4,5};
	do
	{
		bool flag=0;
		int fa=0,fb=0,fc=0;
		for(int i=0;i<=n-1;i++)
		{
			if(p[i]==1)//放字母A 
			{
				if(mark[i+1][0])//如果这一列已经出现过这个字母，这种排序就不满足题意 
				{
					flag=1;
					break;
				}
				fa=i+1;
				mark[i+1][0]=1;
				a[x][i+1]='A';
			}
			else if(p[i]==2)//放字母B
			{
				if(mark[i+1][1])
				{
					flag=1;
					break;
				}
				fb=i+1;
				mark[i+1][1]=1;
				a[x][i+1]='B';
			}
			else if(p[i]==3)//放字母C
			{
				if(mark[i+1][2])
				{
					flag=1;
					break;
				}
				fc=i+1;
				mark[i+1][2]=1;
				a[x][i+1]='C';
			}
			else a[x][i+1]='.';//什么都不放 
		}
		if(flag==0) graph(x);
		if(fa) mark[fa][0]=0;
		if(fb) mark[fb][1]=0;
		if(fc) mark[fc][2]=0;
	}
	while(next_permutation(p,p+n));//枚举全排列 
	return;
}
int main() {
	scanf("%d",&n);
	cin>>r>>c;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			a[i][j]='.';
		}
	}
	graph(0);
	printf("No\n");
	
	return 0;
}
```

---

## 作者：spire001 (赞：6)

## 题意

就是寻找一种情况满足题意。

每一行第一个字母拼起来的序列与字符串 $A$ 相等，每一列第一个字母拼起来的序列与字符串 $B$ 相等。

## 分析

从数据 $N\in[3,5]$ 可以得出本题思路为暴力枚举。

可以预处理出所有状态，最后并判断是否满足题意。

但我觉得有点慢，于是优化了一点点。

在添加每一行的时候判断一列中的字母是否超过三个，如果是，则不再需要继续搜索。

## 代码

```cpp
#pragma GCC optimize(2)
#include<iostream>
#include"cstdio"
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define mod 998244353
#include<stack>
#define N

namespace io{
	using std::cin;
	using std::cout;
	using std::max;
	using std::min;
	template <typename T>
	void Read(T &num)
	{
		num^=num;
		char t=cin.get();T f=1;
		while(t<'0'||t>'9') {if(t=='-') f=-f;t=cin.get();}
		while(t>='0'&&t<='9') {num=(num<<1)+(num<<3)+(t^48);t=cin.get();}
		num*=f;return;
	}
#ifdef _GLIBCXX_IOMANIP
	using std::fixed;
	using std::setprecision;
#endif

}using namespace io;
int n;
char a[7],b[7];
bool box[7][7];
struct node{
	int pa,pb,pc;//A,B,C的位置
	node(int pa,int pb,int pc) : pa(pa) , pb(pb) , pc(pc) {}//构造函数
};
std::vector <node> v;//由于我不想计算预处理个数，于是用了vector
int L;
char x[7][7];
void clear(int step)//回溯
{
	memset(x[step],0,sizeof(x[step]));
	return;
}
void pre()//预处理
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int p=1;p<=n;p++)
				if(i!=j&&i!=p&&j!=p)//记住不能位置重叠
					v.push_back(node(i,j,p));
	L=v.size();return;
}

void s(int i,int step)//添加每一行
{
	x[step][v[i].pa]='A';
	x[step][v[i].pb]='B';
	x[step][v[i].pc]='C';
	return;
}
int cnt;
bool check()
{
	int na1=0,nb1=0,nc1=0;
	for(int i=1;i<=n;i++)
	{
		na1=nb1=nc1=0;
		for(int j=1;j<=n;j++)
		{
			if(x[j][i]=='A') na1++;
			else if(x[j][i]=='B') nb1++;
			else if(x[j][i]=='C') nc1++;
		} 
		if(na1!=1||nc1!=1||nb1!=1) return false;//a和b和c的数量如果有一个不为1则不满足题意
	}
	//cout<<'\n';
	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(x[i][j]&&x[i][j]!=a[i-1]) return false;//与字符串A判断相等
			else if(x[i][j])break;//这里不能直接写break;因为字符有可能是'.'
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(x[j][i]&&x[j][i]!=b[i-1]) return false;//与字符串B判断相等
			else if(x[j][i])break;
		}
	return true;
}
bool check(int step)//函数重载
{
	int na1=0,nb1=0,nc1=0;
	for(int i=1;i<=step;i++)
	{
		na1=nb1=nc1=0;
		for(int j=1;j<=n;j++)
		{
			if(x[j][i]=='A') na1++;
			else if(x[j][i]=='B') nb1++;
			else if(x[j][i]=='C') nc1++;
		}
		if(na1>1||nc1>1||nb1>1) return false;//优化
	}
	return true;
}
void dfs(int step)
{
	if(step==n)
	{
		if(check())
		{
			cout<<"Yes\n";
			for(int i=1;i<=n;i++)
			{
				for(int j=1;j<=n;j++)
					cout<<(x[i][j]?x[i][j]:'.');
				cout<<'\n';
			}
			exit(0);//直接结束程序
		}
		return;
	}
	for(int i=0;i<L;i++)
	{
		s(i,step+1);
		if(check(step+1)) dfs(step+1);
		clear(step+1);
	}
}
int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	Read(n);pre();
	cin>>a>>b;
	dfs(0);cout<<"No";//别忘了"No"
	return 0;
}

```

---

## 作者：_ZML_ (赞：3)

[题目链接](https://www.luogu.com.cn/problem/AT_abc326_d)

## 解法分析

这个问题是一个经典的排列谜题，通过回溯算法来穷举所有可能的字符排列，然后验证是否满足行和列约束。这个解决方案可以用于解决类似的谜题，其中需要满足一定的排列条件。通过仔细考虑约束条件，可以加快解决问题的速度，减少不必要的计算。

更详细的我写在代码里了。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long;

// chmax和chmin是模板函数，用于在满足条件时更新值。
template<class T> bool chmax(T &a, const T &b) { if (a < b) { a = b; return true; } return false; }
template<class T> bool chmin(T &a, const T &b) { if (b < a) { a = b; return true; } return false; }

// 定义一些宏和常量
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define mp make_pair
#define si(x) int(x.size())
const int mod = 998244353, MAX = 300005, INF = 1 << 30;

char S[6][6]; // 一个二维字符数组，用于存储网格的当前状态
string R, C; // 字符串R和C表示行和列的约束
int N; // 网格的大小（N x N）

// “solve”函数是一个递归函数，用于尝试解决这个谜题。
void solve(int u) {
    if (u == N) { // 如果我们已经填满了所有行，检查解是否有效。
        // 检查行约束是否满足。
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (S[i][j] != '.') {
                    if (R[i] != S[i][j]) return; // 如果行中的字符与约束不匹配，返回。
                    break;
                }
            }
        }
        
        // 检查列约束是否满足。
        for (int j = 0; j < N; j++) {
            set<char> SE;
            for (int i = 0; i < N; i++) {
                if (S[i][j] == '.') continue;
                if (SE.count(S[i][j])) return; // 如果列中有字符重复，返回。
                SE.insert(S[i][j]);
            }
            if (si(SE) <= 2) return; // 如果列中有超过2个字符，返回。
            for (int i = 0; i < N; i++) {
                if (S[i][j] == '.') continue;
                if (C[j] != S[i][j]) return; // 如果列中的字符与约束不匹配，返回。
                break;
            }
        }
        
        // 如果所有约束都满足，打印解并退出。
        cout << "Yes\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) cout << S[i][j];
            cout << "\n";
        }
        exit(0);
    }
    
    // 尝试当前行的所有可能字符组合。
    for (int a = 0; a < N; a++) {
        for (int b = 0; b < N; b++) {
            if (a == b) continue;
            for (int c = 0; c < N; c++) {
                if (a == c || b == c) continue;
                
                // 检查当前组合是否满足当前行的约束。
                if (R[u] == 'A') {
                    if (!(a < b && a < c)) continue;
                }
                if (R[u] == 'B') {
                    if (!(b < a && b < c)) continue;
                }
                if (R[u] == 'C') {
                    if (!(c < a && c < b)) continue;
                }
                // 填充当前行的字符。
                S[u][a] = 'A';
                S[u][b] = 'B';
                S[u][c] = 'C';
                // 递归尝试解决下一行。
                solve(u + 1);
                // 重置字符以进行回溯。
                S[u][a] = '.';
                S[u][b] = '.';
                S[u][c] = '.';
            }
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    cin >> N >> R >> C; // 读取网格大小和行/列约束。
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            S[i][j] = '.'; // 用空单元格初始化网格。
    solve(0); // 从第一行开始解决谜题。
    cout << "No\n"; // 如果找不到解，打印"No"。
}

```

---

## 作者：_Above_the_clouds_ (赞：2)

# 思路：
要求一个 $n \times n$ 的序列，保证以下条件：

- 每行每列都有且只有 `A`，`B`，`C` 三个字符
- 第 $i$ 行最左边第一个字母与 $R$ 的第 $i$ 个字符相同。
- 第 $i$ 列最上边第一个字母与 $C$ 的第 $i$ 个字符相同。

直接暴搜，每次找到第 $x$ 行第 $y$ 列都没有出现的字符，就将当前位置赋值为这个字母，并将第 $x$ 行和第 $y$ 列的这个字母标记。

如果当前行或列 $n$ 与非字母数量的差小于三，说明当前行或列已经无法满足条件一，直接去除。

当序列构造完成时，搜索每一行每一列是否都满足条件一。

然后再看这个序列是否满足条件二和三，如果都满足，输出即可。

# 代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read() {
    int f=0,t=0;
    char c=getchar();
    while(!isdigit(c)) t|=(c=='-'),c=getchar();
    while(isdigit(c)) f=(f<<3)+(f<<1)+c-48,c=getchar();
    return t?-f:f;
}

inline void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar('0'+x%10);
}

const int Max = 10 + 5, mod = 1e9 + 7;
int n = read(), cnt;
string r, c;

char a[Max][Max], ch[] = {'.', 'A', 'B', 'C'};
int vis[Max][500], vis2[Max][500];

bool check() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			if (a[i][j] == '.') continue;
			if (a[i][j] != r[i - 1]) return 0;
			else break;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			if (a[j][i] == '.') continue;
			if (a[j][i] != c[i - 1]) return 0;
			else break;
		}
	return 1;
}

void dfs(int x, int y) {
	if (cnt == n * n) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= 3; j++)
				if (!vis[i][ch[j]] || !vis2[i][ch[j]])
					return ;
		if (check()) {
			cout << "Yes\n";
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++)
					cout << a[i][j];
				cout << "\n";
			}
			exit(0);
		}
		return ;
	}
	if (n - vis[x]['.'] < 3 || n - vis2[y]['.'] < 3) return ;
	cnt++;
	for (int i = 1; i <= 3; i++) {
		if (!vis[x][ch[i]] && !vis2[y][ch[i]]) {
			a[x][y] = ch[i];
			vis[x][ch[i]] = 1;
			vis2[y][ch[i]] = 1;
			if (y + 1 <= n) dfs(x, y + 1);
			else dfs(x + 1, 1);
			vis[x][ch[i]] = 0;
			vis2[y][ch[i]] = 0;
		}
	}
	a[x][y] = '.';
	vis[x]['.']++;
	vis2[y]['.']++;
	if (y + 1 <= n) dfs(x, y + 1);
	else dfs(x + 1, 1);
	vis[x]['.']--;
	vis2[y]['.']--;
	cnt--;
}

signed main() {
	cin >> r >> c;
	dfs(1, 1);
	cout << "No";
	return 0;
}
/*

*/

```


---

## 作者：xu222ux (赞：1)

# [ABC326D](https://www.luogu.com.cn/problem/AT_abc326_d)


## 思路
直接暴力。

每行枚举 3 个位置，每个位置的字母也要枚举。

最后看矩阵满不满足条件。

```c++
#include<bits/stdc++.h>
using namespace std;
int n;
string a,b;
bool f[6][3];
char ans[6][6];
void dfs(int d){
	if(d==n+1){
		for(int j=1;j<=n;j++){
			for(int i=1;i<=n;i++){
				if(ans[i][j]!='.'){
					if(ans[i][j]!=b[j-1])return ;
					else break;
				}
			}
		}
		cout<<"Yes\n";
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)cout<<ans[i][j];
			cout<<endl;
		}
		exit(0);
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			for(int k=j+1;k<=n;k++){
				if(f[i][a[d-1]-'A'])break;
				ans[d][i]=a[d-1];
				f[i][a[d-1]-'A']=true;
				for(int jj=0;jj<3;jj++){
					for(int kk=0;kk<3;kk++){
						 if(!(jj!=kk&&jj!=a[d-1]-'A'&&kk!=a[d-1]-'A'))continue;
						 if(f[j][jj])break;
						 if(f[k][kk])continue;
						 f[j][jj]=f[k][kk]=true;
						 ans[d][j]=char(jj+'A');
						 ans[d][k]=char(kk+'A');
						 dfs(d+1);
						 ans[d][j]=ans[d][k]='.';
						 f[j][jj]=f[k][kk]=false;
					}
				}
				ans[d][i]='.';
				f[i][a[d-1]-'A']=false;
			}
		}
	}
}
int main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)ans[i][j]='.';
	dfs(1);
	cout<<"No";
	return 0;
}
```

---

## 作者：CQ_Bab (赞：1)

# 思路
不难。

发现只有三个字母时果断状压，通过观察我们可以发现 $n$ 和 $m$ 都很小，然后我们就可以想到暴搜了，我们可以对于每一行一行的去填数，这里我们发现只需要是的满足题目给出的那两个串的条件即可。

这里我们定义 $hang_i,lie_i$ 表示第 $i$ 行和第 $i$ 列的状态（二进制下第 $i$ 位为一表示第 $i$ 个大写字母已经选过了），然后我们就可以发现如果第 $i$ 行已经到了最后一个我们就可以去判断一下这一行填的第 $1$ 个数是否与要求填的第一个数相同，若相同则继续往后填，如果这一列还没有填数则将要填的数和想要填的数进行比较即可。

细节见代码。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;i--)
#define fire signed
#define kong putchar(' ')
#define end putchar('\n')
#define in(x) scanf("%lld",&x)
#define lcm(x,y) x*y/__gcd(x,y)
#define il inline
il void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
int n;
string s,t;
char c[10][10];
int lie[10],hang[10];
char nowx[10],nowy[10]; 
bool check(int x,int y,int i,int j,char c) { //判断是否匹配
	if(x==0) if(c!=t[j]) return false;
	if(y==0) if(c!=s[i]) return false;
	return 1;
}
void dfs(int x,int y) {
	if(x==n+1&&y==1) {
		int f=0;
		rep(i,1,n) if(lie[i]!=7||hang[i]!=7) return ; //判断每一行和每一列上是否都用到了三个字母
		puts("Yes");
		rep(i,1,n) {
			rep(j,1,n) {
				cout<<c[i][j];
			}
			cout<<endl;
		}
		exit(0);
	}
	rep(i,0,2) {
		if((lie[y]&(1<<i))!=(1<<i)&&(hang[x]&(1<<i))!=(1<<i)&&check(lie[y],hang[x],x,y,i+'A')) {//判断是否冲突
			int ip=1<<i;
			lie[y]|=(1<<i);
			hang[x]|=ip;
			c[x][y]=(i+'A');
			if((y+1)>n&&hang[x]==7) dfs(x+1,1); //跳到下一行第一个
			else if(y+1<=n)dfs(x,y+1); //这一行的下一个
			lie[y]^=ip;
			hang[x]^=ip;
		}
	}
	c[x][y]='.';
	if((y+1)>n&&hang[x]==7) dfs(x+1,1);
	else if(y+1<=n)dfs(x,y+1);
}
fire main() {
	cin>>n>>s>>t;
	s=" "+s;
	t=" "+t;
	dfs(1,1);
	puts("No");
	return false;
}

```

---

## 作者：_7Mr (赞：1)

# 前言
考试的时候没想出来，还是太蒟蒻了，看了大佬的代码才想出来。

# 思路
$n \le 5$ 直接爆搜。对于每一行我们枚举 ```ABC``` 的位置，并标记。当枚举的行数，大于 $n$ 我们判断当前行不行，如果不行就舍弃，如果行输出并退出。具体看代码。

# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
#define INF INT_MAX
using namespace std;
const int maxn=1e2+5;
int n;
int vis[maxn][maxn];
char ans[maxn][maxn];
string r,c;
bool ok() {//判断是否可行
	int flag=1;
	for(int i=1; i<=n; i++) {//看竖着的
		for(int j=1; j<=n; j++) {
			if(ans[i][j]!='.') {
				if(ans[i][j]!=r[i]) flag=0;
				break;
			}
		}
		if(!flag) break;
	}
	if(!flag) return false;
	for(int i=1; i<=n; i++) {//看横着的
		for(int j=1; j<=n; j++) {
			if(ans[j][i]!='.') {
				if(ans[j][i]!=c[i]) flag=0;
				break;
			}
		}
		if(!flag) break;
	}
	if(!flag) return false;
	return true;
}
void print() {//输出答案
	cout<<"Yes"<<endl;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			cout<<ans[i][j];
		}
		cout<<endl;
	}
	exit(0);
}
void dfs(int x) {
	if(x>n) {//如果当前搜完了，判断一下
		if(ok()) print();
		return;
	}
	for(int i=1; i<=n; i++) {//枚举ABC的位置
		for(int j=1; j<=n; j++) {
			if(i==j) continue;
			for(int k=1; k<=n; k++) {
				if(i==k || j==k) continue;
				if(!vis[i][1] && !vis[j][2] && !vis[k][3]) {//如果这些位置没被占，那就搜下一行
					vis[i][1]=vis[j][2]=vis[k][3]=1;//标记
					ans[x][i]='A';//填ABC
					ans[x][j]='B';
					ans[x][k]='C';
					dfs(x+1);//下一行
					vis[i][1]=vis[j][2]=vis[k][3]=0;//回溯
					for(int p=1;p<=n;p++) ans[x][p]='.'; //初始化这一行，为下一次做准备。
				}
			}
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>r>>c;
	for(int p=1; p<=n; p++) {//初始化一下
		for(int q=1; q<=n; q++) {
			ans[p][q]='.';
		}
	}
	r=" "+r;
	c=" "+c;
	dfs(1);//爆搜
	cout<<"No"<<endl;//都不行输出No
	return 0;
}

```

---

## 作者：kkxacj (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc326_d)

#### 思路

直接枚举每一个点的状态在判断毫无疑问会超时，不如考虑暴枚每个满足第$i$ 行中最左边的字符与 $R$ 的第 $i$ 个字符匹配，且这一行只有三个不同的字符，这样每一行只有 $20$ 种状态，因为如果第$i$ 行中最左边的字符与 $R$ 的第 $i$ 个字符匹配那么剩下的字符只能在 $i + 1$ 到 $n$ 之间选两个，判断一下是否满足其他条件就可以了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,b,c,d;
char a[10][10];
string s,s1;
void dfs(int x)
{
	if(x == n)
	{	
		l = 0;	
		for(int j = 0;j < n;j++)//是否满足条件 3 
		{
			for(int i = 0;i < n;i++)
			{
				if(a[i][j] != '.')
				{
					if(s1[j] != a[i][j]) l = 1;
					break;
				}
			}
			if(l) break;
		}	
		if(l) return;
		for(int i = 0;i < n;i++)
		{
			l = b = c = d = 0;//由于枚举是已经保证了一行只有 ABC 三个一样一个，所以不用再去判断 
			for(int j = 0;j < n;j++)
			{
				if((a[j][i] == 'A' && b) || (a[j][i] == 'B' && c) || (a[j][i] == 'C' && d))
				{
					l = 1;
					break;
				}
				if(a[j][i] == 'A') b = 1;
				else if(a[j][i] == 'B') c = 1;
				else if(a[j][i] == 'C') d = 1;
			}
			if(l) break;
		}
		if(!l)
		{
			cout << "Yes" << endl;
			for(int i = 0;i < n;i++,cout << endl)
				for(int j = 0;j < n;j++)
					cout << a[i][j];
			exit(0);
		}
		return; 
	}
	for(int i = 0;i < n;i++) 
	{
		a[x][i] = s[x];
		for(int j = i + 1;j < n;j++)
			for(int z = i + 1;z < n;z++)
				if(j != z) 
				{
					if(s[x] == 'A') a[x][j] = 'C',a[x][z] = 'B',dfs(x + 1),a[x][j] = '.',a[x][z] = '.';
					else if(s[x] == 'B') a[x][j] = 'C',a[x][z] = 'A',dfs(x + 1),a[x][j] = '.',a[x][z] = '.';
					else if(s[x] == 'C') a[x][j] = 'B',a[x][z] = 'A',dfs(x + 1),a[x][j] = '.',a[x][z] = '.';
				}
		a[x][i] = '.';
	}
}
int main()
{
	scanf("%d",&n); cin >> s >> s1;
	for(int i = 0;i < n;i++)//初始化 
		for(int j = 0;j < n;j++) a[i][j] = '.';
	dfs(0);
	printf("No");
    return 0;
}

```


---

## 作者：dream_on_screen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc326_d)

我们可以暴力枚举所有的方法，首先枚举出来第一行，然后枚举出来第一列，然后枚举中间的部分。

需要特别注意的一点是， `.` 不算做字符，第一个字符是指的第一个非 `.` 的字符。

然后就可以开始暴力枚举了：

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int n;
string a,b;
int ca[3],cb[3];
int A=0,B=1,C=2,nop=3,undefined=9;
int c[10][10]={9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,};
int tmp[10];
void getx(int x)
{
	tmp[0]=tmp[1]=tmp[2]=0;
	for(int i=1;i<=n;i++)
		tmp[c[x][i]]++;
}
void gety(int x)
{
	tmp[0]=tmp[1]=tmp[2]=0;
	for(int i=1;i<=n;i++)
		tmp[c[i][x]]++;
}
void ptchar(int x)
{
	if(x==A)
		cout<<'A';
	else if(x==B)
		cout<<'B';
	else if(x==C)
		cout<<'C';
	else if(x==nop)
		cout<<'.';
}
void nextceil(int &x,int &y)
{
	y++;
	if(y>n)
		y=2,x++;
	if(x>n)
		x=999,y=999;
}
void dfs3(int x,int y)
{
	if(x==999&&y==999)
	{
		for(int i=1;i<=n;i++)
		{
			if(c[i][1]!=nop&&c[i][1]!=a[i]-'A')
				return;
			if(c[1][i]!=nop&&c[1][i]!=b[i]-'A')
				return;
		}
		//行 
		for(int i=1;i<=n;i++)
		{
			getx(i);
			for(int j=0;j<=2;j++)
				if(tmp[j]!=1)
					return;
		}
		//列
		for(int i=1;i<=n;i++)
		{
			gety(i);
			for(int j=0;j<=2;j++)
				if(tmp[j]!=1)
					return;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(c[i][j]==nop)
					continue;
				if(c[i][j]!=a[i]-'A')
					return;
				else
					break;
			}
			for(int j=1;j<=n;j++)
			{
				if(c[j][i]==nop)
					continue;
				if(c[j][i]!=b[i]-'A')
					return;
				else
					break;
			}
		}
		cout<<"Yes\n"; 
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(c[i][j]==A)
					cout<<'A';
				else if(c[i][j]==B)
					cout<<'B';
				else if(c[i][j]==C)
					cout<<'C';
				else if(c[i][j]==nop)
					cout<<'.';
			}
			cout<<"\n";
		}
		exit(0);
		return;
	}
	int nx=x,ny=y;
	nextceil(nx,ny);
	int xx[3]={};
	getx(x);
	for(int i=0;i<=2;i++) xx[i]=tmp[i];
	int yy[3]={};
	gety(y);
	for(int i=0;i<=2;i++) yy[i]=tmp[i];
	bool flag[3]={false};
	for(int i=0;i<=2;i++)
		if(xx[i]==0&&yy[i]==0)
			flag[i]=true;
	for(int i=0;i<=2;i++)
		if(flag[i])
		{
			c[x][y]=i;
			dfs3(nx,ny);
		}
	c[x][y]=nop;
	dfs3(nx,ny);
	c[x][y]=undefined;
	return ;
}
void dfs2(int step)//确定一个第一行
{
	if(step>n)
	{
		getx(1);
		if(tmp[0]!=1||tmp[1]!=1||tmp[2]!=1)
			return ;
		dfs3(2,2);
		return ;
	}
	getx(1);
	if(tmp[b[step]-'A']==0)
	{
		c[1][step]=b[step]-'A';
		dfs2(step+1);
	}
	c[1][step]=nop;
	dfs2(step+1);
	c[1][step]=undefined;
}
void dfs1(int step)//确定一个第一列 
{
	if(step>n)
	{
		gety(1);
		if(tmp[0]!=1||tmp[1]!=1||tmp[2]!=1)
			return ;
		if(c[1][1]!=nop&&c[1][1]!=b[1]-'A')
			return ;
		dfs2(2);
		return ;
	}
	gety(1);
	if(tmp[a[step]-'A']==0)
	{
		c[step][1]=a[step]-'A';
		dfs1(step+1);
	}
	c[step][1]=nop;
	dfs1(step+1);
	c[step][1]=undefined;
}
int main()
{
	cin>>n;
	cin>>a>>b;//列，行 
	a=' '+a;
	b=' '+b;
	for(int i=1;i<=n;i++)
	{
		ca[a[i]-'A']++;
		cb[b[i]-'A']++;
	}
	if(!(ca[1]>=1&&ca[2]>=1&&ca[0]>=1)||!(cb[1]>=1&&cb[2]>=1&&cb[0]>=1))
	{
		cout<<"No";
		return 0;
	}
	dfs1(1);
	cout<<"No";
}
```

---

## 作者：KυρωVixen (赞：0)

# ABC326D 题解
大爆搜，大模拟，神仙剪枝题，总之肯定比 E 难一丢丢的。

建议难度黄或者绿，挺难的基础题。

## 解法：
这个数据范围不用想了，直接爆搜。

枚举每个格子分别为 ```.```、```A```、```B```、```C``` 的 naive 方式显然 T 飞，所以我们考虑通过记录和枚举相关信息（摆了多少个，对应字母类型有没有出现过）的方式来剪枝出不考虑字符串限制条件时合适的摆法，按照官方题解的说法共有六万多个，然后暴力判断是否列和行开头的字符拼起来是要求字符串即可。

暴力判断 $O(N^2)$，爆搜状态数约为六万个，可以通过。

## 代码：
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define endl '\n'
using namespace std;
int n,p1[7],p2[7];
string s1,s2;
char m[7][7];
const char *k=".ABC";
bool chk(){
	int a,b,c;
	rep(i,1,n){
		a=b=c=0;
		rep(j,1,n){
			if(m[i][j]=='A') a++;
			if(m[i][j]=='B') b++;
			if(m[i][j]=='C') c++;
		}
		if(a!=1||b!=1||c!=1) return 0;
	}
	rep(j,1,n){
		a=b=c=0;
		rep(i,1,n){
			if(m[i][j]=='A') a++;
			if(m[i][j]=='B') b++;
			if(m[i][j]=='C') c++;
		}
		if(a!=1||b!=1||c!=1) return 0;
	}
	rep(i,1,n){
		char f='.';
		rep(j,1,n)
			if(m[i][j]!='.'){
				f=m[i][j]; break;
			}
		if(f!=s1[i-1]) return 0;
	}
	rep(j,1,n){
		char f='.';
		rep(i,1,n)
			if(m[i][j]!='.'){
				f=m[i][j]; break;
			}
		if(f!=s2[j-1]) return 0;
	}
	return 1;
}
void dfs(int x,int y){
	if(n-x+1<3-p2[y]||n-y+1<3-p1[x]) return;
	if(x==n+1){
		if(chk()){
			cout<<"Yes"<<endl;
			rep(i,1,n){
				rep(j,1,n)
					cout<<m[i][j];
				cout<<endl;
			}
			exit(0);
		}
		return;
	}
	rep(i,0,3){
		char tmp=k[i];
		if(i==0){
			m[x][y]=tmp; dfs(x+(y==n),(y==n)?1:y+1);
		}
		else{
			bool flag=1;
			rep(i,1,x-1) if(m[i][y]==tmp) {flag=0; break;}
			rep(i,1,y-1) if(m[x][i]==tmp) {flag=0; break;}
			if(!flag) continue;
			m[x][y]=tmp;
			p1[x]++; p2[y]++;
			dfs(x+(y==n),(y==n)?1:y+1);
			p1[x]--; p2[y]--;
		}
	}
}
signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>s1>>s2;
	dfs(1,1);
	cout<<"No"<<endl;
}

```

---

## 作者：_liuyi_ (赞：0)

# 思路
$3\le n \le 5$，明显搜索。直接暴力枚举矩阵，然后判断合不合法。这样会超时，考虑怎么优化，在填每行或每列第一个时，只能填与当前 $R$、$C$ 相同的，然后就过了。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define fi first
#define se second
#define pb push_back
#define mem(a,x) memset(a,x,sizeof(a))
#define all(x) x.begin(),x.end()
#define lisan(x) {sort(all(x));x.erase(unique(all(x)),x.end());}
#define SZ(x) ((int)((x).size()))
#define debug(x) cout<<#x<<"="<<x<<"\n";
#define ti (db)((db)clock() / CLOCKS_PER_SEC)
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef vector<int> VI;
typedef vector<vector<int>> VII;
typedef vector<ll> VL;
typedef vector<vector<ll>> VLL;
typedef unsigned long long ull;
typedef double db;
template<typename T> inline void cmax(T &a,const T b){if(a<b) a=b;}
template<typename T> inline void cmin(T &a,const T b){if(a>b) a=b;}
template<typename T> inline T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
constexpr int N=100;
constexpr int mod=1e9+7;
//constexpr int mod=998244353;
int n,num[2][N],fst1[N],fst2[N];
char ans[N][N],s[N][N];
bool v1[3][N],v2[3][N],ok;
string r,c;
inline bool check(){
    mem(num,0);
    rep(i,1,n){
        rep(j,1,n){
            if(s[i][j]!='.') num[0][i]++,num[1][j]++;
        }
    }
    rep(i,1,n) if(num[0][i]!=3||num[0][i]!=3) return false;
    return true;
}
inline void dfs(int x,int y){
    if(ok) return;
    if(x==n+1){
        if(check()){
            ok=true;
            rep(i,1,n)
                rep(j,1,n) ans[i][j]=s[i][j];
        } 
        return;
    }
    int nx=x,ny=y+1;
    if(ny==n+1) nx++,ny=1;            
    s[x][y]='.';
    dfs(nx,ny);
    rep(i,0,2){
        char tmp=i+'A';
        if(!v1[i][x]&&!v2[i][y]){
            if((tmp==r[x-1]||fst1[x])&&(tmp==c[y-1]||fst2[y])){
                s[x][y]=tmp;
                if(!fst1[x]) fst1[x]=y;
                if(!fst2[y]) fst2[y]=x;
                v1[i][x]=v2[i][y]=true;
                dfs(nx,ny);
                if(fst1[x]==y) fst1[x]=0;
                if(fst2[y]==x) fst2[y]=0;
                v1[i][x]=v2[i][y]=false;
                s[x][y]='.';
            }
        }
    }
}
inline void solve(){
    cin>>n>>r>>c;
    rep(i,1,n)
        rep(j,1,n) s[i][j]='.';
    dfs(1,1);    
    if(ok){
        puts("Yes");
        rep(i,1,n){
            rep(j,1,n) printf("%c",ans[i][j]);
            puts("");
        }
    }
    else puts("No");
}
int main(){
    int T=1;
    //scanf("%d",&T);
    while(T--) solve();
}
```


---

## 作者：vicky2048_2 (赞：0)

爆搜剪枝，碰到不合法的状态直接剪掉就行了。

------------

考虑 $n=5$ 时每行的合法状态数，一行中只包含三种字母各一个，且第一个字母的顺序确定，则有两种合法状态数的计算方法：

下文称第 $i$ 个字母的位置为 $pl_i$。

- 按第一个字母的位置分讨（显然有 $pl_1\in[1,3]$）：

	- $pl_1=1$，此时另外两个字母的排列数为 $4\times3$。
    
    - $pl_1=2$，此时另外两个字母的排列数为 $3\times2$。
    
    - $pl_1=3$，此时另外两个字母的排列数为 $2\times1$。
    
    - 于是每行的合法状态数为 $4\times3+3\times2+2\times1=20$。

- 先计算三个字母的排列方案（$5\times4\times3$），因为每行第一个字母确定，所以要把第一个字母不合法的状态去掉，即 $\frac{5\times4\times3}3=20$。

一共 $5$ 行，所以保证每行状态合法的情况下总状态数为 $20^5=3.2\times 10^6$，$\text{4s}$ 完全够跑了。

------------

```cpp
#include<bits/stdc++.h>
#define N 15
using namespace std;
int n,ro[N][4],col[N][4];
char r[N],c[N],ans[N][N];
void dfs(int,int,int);
signed main(){
    scanf("%d%s%s",&n,r+1,c+1);
    for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) ans[i][j]='.';
    dfs(1,1,0);
    printf("No");
    return 0;
}
void dfs(int x,int y,int ly){
    if(x>n){
        printf("Yes\n");
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j)
                putchar(ans[i][j]);
            putchar('\n');
        }
        exit(0);
    }
    if(ly>n+y-4) return ;
    if(y>3) dfs(x+1,1,0);
    for(int i=ly+1;i<=n;++i){
        if(y==1){
            if(!col[i][c[i]-'A']){
                if(r[x]!=c[i]) continue;
                else
                    ans[x][i]=r[x],col[i][c[i]-'A']=x,ro[x][r[x]-'A']=i,dfs(x,y+1,i),
                    ans[x][i]='.',col[i][c[i]-'A']=0,ro[x][r[x]-'A']=0;
            }
            else if(col[i][r[x]-'A']) continue;
            else
                ans[x][i]=r[x],col[i][r[x]-'A']=x,ro[x][r[x]-'A']=i,dfs(x,y+1,i),
                ans[x][i]='.',col[i][r[x]-'A']=0,ro[x][r[x]-'A']=0;
            continue;
        }
        for(int j=0;j<3;++j){
            if(ro[x][j]||col[i][j]||(!col[i][c[i]-'A']&&c[i]-'A'!=j)) continue;
            ans[x][i]='A'+j,col[i][j]=x,ro[x][j]=i,dfs(x,y+1,i),
            ans[x][i]='.',col[i][j]=0,ro[x][j]=0;
        }
        dfs(x,y,i);
    }
}
```


---

## 作者：forever_nope (赞：0)

## 看题

事实上，即使在 $N=5$ 的情况下，也只有 $66240$ 个网格满足「每行/每列恰好包含一个 `A`、`B` 和 `C`」。——官方题解

其实看到这道题，就感觉是搜索，这很显然。

但是我们会发现，最最最 native 的搜索，是 $4^{5\times5}=2^{50}$ 的。

感觉不大可过，但是似乎又不太大。

考虑到原题中的限制很多很多，所以可以考虑剪枝。

下面的思路与 [官方题解](https://atcoder.jp/contests/abc326/editorial/7548) 的类似。

## 分析

题目中的限制有：

1. 每行和每列恰好包含一个 `A`、一个 `B` 和一个 `C`。
2. 第 $x$ 行最左边的字符是 $R_x$。
3. 第 $x$ 列最上面的字符是 $C_x$。

我们一条一条的看，可以怎么剪枝。

**0x01**

限制：每行和每列恰好包含一个 `A`、一个 `B` 和一个 `C`。

于是，我们可以按行搜索，即每次递归填入一整行的字符。

然后我们在搜索的过程中记录：$\mathit{have}_{i,0/1/2}$ 表示第 $i$ 列是否有 `A`/`B`/`C`。

然后在填入每一行的字符时，我们限制只能填入一个 `A`、一个 `B` 和一个 `C`。

**0x02**

限制：每行的第一个字符一定是 $R_x$。

于是，我们可以枚举每个字符填入的位置。

我们枚举 $i$ 表示 $R_x$ 填入的位置，然后枚举 $j,k$ 表示其余两个字母的位置。

注意到除了后面两个字符的位置 $j,k$（在符合其余限制的情况下）可以调换：

$$
\begin{array}{r}
i\leftarrow[0,n)\\
j,k\leftarrow(i,n)
\end{array}
$$

**0x03**

限制：每一列第一个字符一定是 $C_x$。

于是，我们可以记录一个 $\mathit{cover}_i$ 表示此时第 $i$ 列上方是否已经被其他字符覆盖。

当我们填入字符的时候，如果 $\mathit{cover}_i=0$ 就需要判断这个字符是否等于 $C_i$。

## 代码

评测记录：<https://atcoder.jp/contests/abc326/submissions/47081201>

跑的嘎嘎快（

```cpp
#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)

using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;

int n; string r, c; 
vvi ans;

void print(vvi &x) {
    for (auto i : x) {
        for (auto j : i) j == -1 ? putchar('.') : putchar('A' + j);
        putchar('\n');
    }
}

#define td(a, b, c, _a, _b, _c) (a) = (_a), (b) = (_b), (c) = (_c)

void dfs(int x, vb iscover, vb have[3]) {
    if (x == n) {
        for (int sb = 0; sb < 3; ++sb)
            for (int t : have[sb]) if (!t) return;
        printf("Yes\n");
        print(ans), exit(0);
    } int op1 = r[x], op2, op3;
    if (op1 == 'A') op2 = 'B', op3 = 'C';
    else if (op1 == 'B') op2 = 'A', op3 = 'C';
    else op2 = 'A', op3 = 'B';
    int sb1 = op1 - 'A', sb2 = op2 - 'A', sb3 = op3 - 'A';
    int t1, t2, t3; for (int i = 0; i < n - 2; ++i) {
        if (!iscover[i] && c[i] != op1) continue;
        if (have[sb1][i]) continue;
        for (int j = i + 1; j < n; ++j) {
            if (!iscover[j] && c[j] != op2) continue;
            if (have[sb2][j]) continue;
            for (int k = i + 1; k < n; ++k) {
                if (j == k) continue;
                if (!iscover[k] && c[k] != op3) continue;
                if (have[sb3][k]) continue;
                td(t1, t2, t3, iscover[i], iscover[j], iscover[k]);
                iscover[i] = iscover[j] = iscover[k] = 1;
                ans[x][i] = sb1, ans[x][j] = sb2, ans[x][k] = sb3;
                have[sb1][i] = have[sb2][j] = have[sb3][k] = 1;
                // fprintf(stderr, "= JOIN (%d, %c) (%d, %c) (%d, %c)\n", i, op1, j, op2, k, op3);
                dfs(x + 1, iscover, have);
                // fprintf(stderr, "= THROW (%d, %c) (%d, %c) (%d, %c)\n", i, op1, j, op2, k, op3);
                td(iscover[i], iscover[j], iscover[k], t1, t2, t3);
                ans[x][i] = -1, ans[x][j] = -1, ans[x][k] = -1;
                have[sb1][i] = have[sb2][j] = have[sb3][k] = 0;
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> r >> c;
    rep(_, n) ans.push_back(vi(n, -1));
    vb x = vb(n); vb t[3] = {x, x, x};
    dfs(0, x, t); printf("No\n");
    return 0;
}
```


---

## 作者：rainygame (赞：0)

搜索题。

暴力枚举整个矩阵是 $O(4^{N^2})$ 的，肯定超时。所以我们考虑从中优化一下。

发现每一行只会有 `A`、`B` 和 `C` 各一个，所以只需要枚举 $i,j,k$ 表示 `A`、`B` 和 `C` 的列数即可。注意单列也同样需要考虑。

搜完之后直接求出它的 $R^\prime$、$C^\prime$ 来和 $R$、$C$ 比较即可。

时间复杂度 $O(N^{3N})$。加上高级剪枝可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, cnt;
string r, c;
char ch[6][6];
set<char> st[6];

bool check(){
    string t1, t2;
    for (int i(0); i<n; ++i){
        for (int j(0); j<n; ++j){
            if (ch[i][j] != '.'){
                t1 += ch[i][j];
                break;
            }
        }
    }
    for (int i(0); i<n; ++i){
        for (int j(0); j<n; ++j){
            if (ch[j][i] != '.'){
                t2 += ch[j][i];
                break;
            }
        }
    }
    return t1 == r && t2 == c;
}

void dfs(int x){
    if (x == n){
        if (check()){
            cout << "Yes\n";
            for (int i(0); i<n; ++i){
                for (int j(0); j<n; ++j) cout << ch[i][j];
                cout << '\n';
            }
            exit(0);
        }
        return;
    }

    for (int i(0); i<n; ++i){
        for (int j(0); j<n; ++j){
            for (int k(0); k<n; ++k){
                if (i == j || j == k || i == k) continue;
                if (st[i].count('A') || st[j].count('B') || st[k].count('C')) continue;
                ch[x][i] = 'A';
                ch[x][j] = 'B';
                ch[x][k] = 'C';
                st[i].insert('A');
                st[j].insert('B');
                st[k].insert('C');
                dfs(x+1);
                st[i].erase('A');
                st[j].erase('B');
                st[k].erase('C');
                ch[x][i] = ch[x][j] = ch[x][k] = '.';
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(ch, '.', sizeof(ch));

    cin >> n >> r >> c;
    dfs(0);
    cout << "No";

    return 0;
}

```

顺带一题，样例一的答案在我这个 dfs 中是第 $10381$ 个被搜索到的完整矩阵。

---

## 作者：2huk (赞：0)

可以发现 $n \le 5$，所以又是 AtCoder 经典暴搜题。

一个格子有 $4$ 种状态（空或 `ABC`），那么直接 $4^{5 \times 5}$ 会超时，因此不能直接暴搜。

我们可以按行搜索。由于每行只能的 `ABC` 只能存在一次，那么不妨对于每一行枚举它的 `ABC` 的所在位置。然后将 $n$ 行枚举完后判断。这样做是 $\mathcal O((n^3)^n \cdot n^2) = \mathcal O(n^{3n+2})$ 的。仍然超时，因此考虑剪枝。

这样枚举出的 $n^{3n+2}$ 个状态中，大部分状态是因为某一列存在不止一个 `ABC` 而废掉的。因此考虑在枚举过程中将这些状态舍去，最后根据题意判断是否每一列的首字母为 $R$ 且每一行的首字母为 $C$ 即可。

定义三个 $\text{bool}$ 数组 $A_i, B_i, C_i$ 表示第 $i$ 列是否分别存在 `ABC`，在枚举过程中把假的状态提前排除即可。

```cpp
int n;
char a[N], b[N];
int res[N][N];		// -1 表示空, 0 表示 'A', 1 表示 'B', 2 表示 'C'

bool chk()
{
	for (int i = 1; i <= n; ++ i )
		for (int j = 1; j <= n; ++ j )
			if (~res[i][j])
				if (res[i][j] != a[i] - 'A') return false;
				else break;
	
	for (int j = 1; j <= n; ++ j )
		for (int i = 1; i <= n; ++ i )
			if (~res[i][j])
				if (res[i][j] != b[j] - 'A') return false;
				else break;
	
	return true;
}

bool A[N], B[N], C[N];

void dfs(int u)
{
	if (u > n)
	{
		if (chk())
		{
			puts("Yes");
			for (int i = 1; i <= n; ++ i )
				for (int j = 1; j <= n; ++ j )
				{
					if (res[i][j] == -1) putchar('.');
					else putchar(res[i][j] + 'A');
					if (j == n) puts("");
				}
				
			exit(0);
		}
		return;
	}
	
	for (int i = 1; i <= 5; ++ i )
		for (int j = 1; j <= 5; ++ j )
			if (i != j)
				for (int k = 1; k <= 5; ++ k )
					if (i != k && j != k)
						if (!A[i] && !B[j] && !C[k])
						{
							res[u][i] = 0, res[u][j] = 1, res[u][k] = 2;
							A[i] = B[j] = C[k] = 1;
							dfs(u + 1);
							res[u][i] = res[u][j] = res[u][k] = -1;
							A[i] = B[j] = C[k] = 0;
						}
	
	return;
}

int main()
{
	memset(res, -1, sizeof res);
	cin >> n;
	for (int i = 1; i <= n; ++ i ) cin >> a[i];
	for (int j = 1; j <= n; ++ j ) cin >> b[j];
	dfs(1);
	puts("No");
	return 0;
}
```



---

## 作者：_smart_stupid_ (赞：0)

# [题目](https://www.luogu.com.cn/problem/AT_abc326_d)

前言：我赛时死也没有想到这题是个 DFS。

## 思路：

DFS 层数，一次性在每层放三个，让最左边的字符和 $r$ 的对应层数的地方相等，DFS 完所有层数后在判断一次是否合法，时间复杂度合格，低于。

## 判断合法：

首先判断他每列从上到下第一个字符，不是 $c$ 对应的位置就不合法，再统计每行每列 ```A```、```B```、```C``` 的数量，如果有一个不是只有一个的字符，就不合法，否则，合法。

## 时间复杂度：

对于每层，一共有30种方法，其中合法的只有10种，整个矩阵一共有 $10^n$ 种方法，放完整个矩阵后判断合法时间复杂度是 $O(n^2)$，所以总的时间复杂度为 $10^n \cdot n^2$，又 $n \leq 6$，所以不会 TLE。 

## AC code：

``` cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<list>
#include<set>
using namespace std;
int n;
char r[10],c[10];
char ans[10][10];
void printans(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%c",ans[i][j]);
		}
		printf("\n");
	}
}
bool get_ans;
void dfs(int x){
	if(x>n){
		for(int i=1;i<=n;i++){
			bool flag=0;
			for(int j=1;j<=n;j++){
				if(ans[j][i]!='.'&&flag==0){
					if(ans[j][i]!=c[i]&&flag==0){
						return ;
					}
					flag=1;
				}
			}
		}
		for(int i=1;i<=n;i++){
			int ca=0,cb=0,cc=0; //记录A、B、C的数量
			for(int j=1;j<=n;j++){
				if(ans[i][j]=='A'){
					if(ca==0) ca=1;
					else return ;
				}
				if(ans[i][j]=='B'){
					if(cb==0) cb=1;
					else return ;
				}
				if(ans[i][j]=='C'){
					if(cc==0) cc=1;
					else return ;
				}
			}
			if(ca+cb+cc!=3) return ;
		}
		for(int i=1;i<=n;i++){
			int ca=0,cb=0,cc=0;
			for(int j=1;j<=n;j++){
				if(ans[j][i]=='A'){
					if(ca==0) ca=1;
					else return ;
				}
				if(ans[j][i]=='B'){
					if(cb==0) cb=1;
					else return ;
				}
				if(ans[j][i]=='C'){
					if(cc==0) cc=1;
					else return ;
				}
			}
			if(ca+cb+cc!=3) return ;
		}
		printf("Yes\n");
		printans();
		get_ans=1;
		exit(0);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			for(int k=1;k<=n;k++){
			if(i==k||j==k) continue;
				if(r[x]=='A'){
					if(j<i||k<i) continue;
				}
				if(r[x]=='B'){
					if(i<j||k<j) continue;
				}
				if(r[x]=='C'){
					if(k>i||k>j) continue;
				}
				ans[x][i]='A';
				ans[x][j]='B';
				ans[x][k]='C';
				dfs(x+1);
				ans[x][i]='.';
				ans[x][j]='.';
					ans[x][k]='.';
			}
		}
   }
}
int main(){
	scanf("%d",&n);
	scanf("%s",r+1);
	scanf("%s",c+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans[i][j]='.';
		}
	}
	dfs(1);
	if(get_ans==0){
		printf("No");
	}
	return 0;
}
```

---

## 作者：Mortidesperatslav (赞：0)

我们尝试剪枝 dfs 完成。

显然暴力搜会超时，所以我们限定同行同列不能放两个 `a`、`b` 或 `c`，并判定每一行放完是否满足条件即可。

代码更详细：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[7],b[7];
char mp[7][7];
bool vis[7][7];
bool aa[7],bb[7],cc[7];
bool raa[7],rbb[7],rcc[7];
int n;
bool ansed=0;
bool check(){//保险起见，判断每一行每一列
	for(int i=0;i<n;i++){
		int fa=0,fb=0,fc=0;
		for(int j=0;j<n;j++){
			if(mp[i][j]=='A')fa++;
			if(mp[i][j]=='B')fb++;
			if(mp[i][j]=='C')fc++;
		}
		if(fa!=1||fb!=1||fc!=1)return 0;
	}
	for(int i=0;i<n;i++){
		int fa=0,fb=0,fc=0;
		for(int j=0;j<n;j++){
			if(mp[j][i]=='A')fa++;
			if(mp[j][i]=='B')fb++;
			if(mp[j][i]=='C')fc++;
		}
		if(fa!=1||fb!=1||fc!=1)return 0;
	}
	char cpa[7],cpb[7];//这里是判断每一行最左和最上的数是否合规
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			if(mp[i][j]!='.'){
				cpa[i]=mp[i][j];
				break;
			}
	}
	for(int i=0;i<n;i++)if(cpa[i]!=a[i])return 0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
			if(mp[j][i]!='.'){
				cpb[i]=mp[j][i];
				break;
			}
	}
	for(int i=0;i<n;i++)if(cpb[i]!=b[i])return 0;
	return 1;
}
void print(int x){
	cout<<"Yes\n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)cout<<mp[i][j];
		cout<<"\n";
	}
	ansed=x;//注意标记一下找到了答案
}
void dfs(int x,int y){
	if(vis[x][y])dfs(x,y+1);
	if(y==n){
		int fa=0,fb=0,fc=0;
		for(int i=0;i<n;i++){
			if(mp[x][i]=='A')fa++;
			if(mp[x][i]=='B')fb++;
			if(mp[x][i]=='C')fc++;
		}
		if(fa!=1||fb!=1||fc!=1)return;//判定当前行是否满足条件
		dfs(x+1,0);
		return;
	}
	if(x==n){
		if(check()){
			print(1);
			exit(0);
		}
		return;
	}
	//cout<<x<<" "<<y<<"\n";
	//print(0);
	if(raa[x]==0&&aa[y]==0){//这一段就是判定搜索的格子是否满足条件
		vis[x][y]=1;
		mp[x][y]='A';
		raa[x]=1;
		aa[y]=1;
		dfs(x,y+1);
		vis[x][y]=0;
		raa[x]=0;
		aa[y]=0;
	}
	if(rbb[x]==0&&bb[y]==0){
		vis[x][y]=1;
		mp[x][y]='B';
		rbb[x]=1;
		bb[y]=1;
		dfs(x,y+1);
		vis[x][y]=0;
		rbb[x]=0;
		bb[y]=0;
	}
	if(rcc[x]==0&&cc[y]==0){
		vis[x][y]=1;
		mp[x][y]='C';
		rcc[x]=1;
		cc[y]=1;
		dfs(x,y+1);
		vis[x][y]=0;
		rcc[x]=0;
		cc[y]=0;
	}
	vis[x][y]=1;
	mp[x][y]='.';//注意可以不放
	dfs(x,y+1);
	vis[x][y]=0;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	cin>>a>>b;
	dfs(0,0);
	if(ansed==0)cout<<"No";
}
```

---

## 作者：yhx0322 (赞：0)

## Description
给定两个字符串 $R$ 和 $C$，分别由 `A`、`B` 和 `C` 组成。

有一个 $N \times N$ 网格。在每个格中，最多只能写 `A`、`B`  和 `C` 中的一个字符。

确定是否可以满足以下所有条件，如果可以，打印。

- 每行和每列恰好包含一个 `A`、一个 `B` 和一个 `C` 。

- 第 $i$ 行中最左边的字符与 $R$ 的第 $i$ 个字符匹配。

- 第 $i$ 列中最上面的字符与 $C$ 的第 $i$ 个字符匹配。

## Solution
暴力 DFS + 剪枝。

注意一些小优化的细节：

我们可以在 DFS 的过程中，判断目前搜索出来的方案是否合法，如果不合法，直接 return。

不能在搜索完毕之后在判断是否合法，否则时间复杂度极大，可能会被卡。

其他的就是搜索，没什么好说的。

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;
int n, ans[10][10];
bool nowx[10][4], nowy[10][4];
string s, t;

void dfs(int x, int y) {
    if (x == n) {
        for (int i = 0; i < n; i++)
            if (nowx[i][3] + nowx[i][1] + nowx[i][2] + nowy[i][3] + nowy[i][1] + nowy[i][2] != 6) return;
        printf("Yes\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                if (!ans[i][j]) putchar('.');
                else printf("%c", 'A' - 1 + ans[i][j]);
            printf("\n");
        }
        exit(0);
    }
    int nx = x, ny = y + 1;
    if (ny >= n) nx++, ny = 0;
    if (!nowx[x][3] && !nowx[x][1] && !nowx[x][2]) {
        if ((nowy[y][3] || nowy[y][1] || nowy[y][2] || s[x] == t[y]) && (!nowy[y][s[x] - 'A' + 1])) {
            ans[x][y] = s[x] - 'A' + 1;
            nowx[x][s[x] - 'A' + 1] = 1;
            nowy[y][s[x] - 'A' + 1] = 1;
            dfs(nx, ny);
            nowx[x][s[x] - 'A' + 1] = 0;
            nowy[y][s[x] - 'A' + 1] = 0;
        }
        ans[x][y] = 0;
        dfs(nx, ny);
    } else {
        for (int i = 1; i <= 3; i++) {
            if ((!nowx[x][i]) && (nowy[y][3] || nowy[y][1] || nowy[y][2] || t[y] - 'A' + 1 == i) && (!nowy[y][i])) {
                ans[x][y] = i;
                nowx[x][i] = 1;
                nowy[y][i] = 1;
                dfs(nx, ny);
                nowx[x][i] = 0;
                nowy[y][i] = 0;
            }
        }
        ans[x][y] = 0;
        dfs(nx, ny);
    }
}

int main() {
    cin >> n >> s >> t;
    dfs(0, 0);
    printf("No");
    return 0;
}
```

---

