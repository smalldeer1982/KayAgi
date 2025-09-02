# Treblecross

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1502

[PDF](https://uva.onlinejudge.org/external/105/p10561.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10561/31bc60cd2679d5a858bab6338b6a91a761cb246d.png)

## 样例 #1

### 输入

```
4
.....
X.....X..X.............X....X..X
.X.X...X
...............................................```

### 输出

```
WINNING
3
LOSING
WINNING
3
WINNING
1 12 15 17 20 24 28 31 33 36 47```

# 题解

## 作者：_J_C_ (赞：3)

容我先吐槽一下……


首先这道题样例有毒……如果无解的时候注意要在正常行末换行的基础上额外输出一个换行（"\n"）、、、
就因为这个我调了几个小时……然后吓的VS都开起来了……
网上粘了代码后才发现问题，然后又以为是别的地方有问题，又对拍了半个小时……



吐完了，说正经的。

对于给定的一个字符串，很显然如果有XX或者X.X存在，先手就赢了，而必胜的方法只有一类：把任意的XX或X.X补全（否则就被对手填上了）

所以我们要做的是：当这个字符串里没有XX或X.X该怎么办

（注意，接下来讨论的字符串都不存在XX或X.X）

比如说，如果字符串里存在X..X，那么这两个X中间是肯定不能填X的，不然就会变成X.XX或XX.X，对手就赢了

那么X...X,X....X也是如此

所以我们发现：对于一个字符串，任意一个X边上两个内都是不能够填入X的，否则对手就赢了

所以原问题可以转换为：给定一个字符串，在这个字符串中两个玩家轮流加入X，在已存在的X左右两个内不能加入X，当玩家无法落子时游戏结束且无法落子的玩家输，求字符串X是必胜还是必输

那么我们将每一个可以落子的空间提出来，比如X.....X....可以看成是X12.21X12..，其中'.'是可以落子的空间，它的子状态是落了子之后的可落子空间

如"X........."(即"X12.......")可以提成"......."，它的子状态有:

"X......" => "X12...." => "...."

".X....." => "1X12..." => "..."

"..X...." => "21X12.." => ".."

"...X..." => ".21X12." => "." 与 "."

……


那么SG函数的参数就好确定了：既然这个空间是由'.'组成的，唯一的变量就是它的长度。

显然我们可以非常方便的枚举子状态，也可以非常方便的将子状态的SG值求NIM和（SG定理），那么SG函数的值就可以求了

关于必胜下一步怎么走嘛，我们尝试在任何一个合法的地方加入'X'，然后判断一下敌方是否必败就好了

然后就是组合游戏的套路了……

```cpp

#include <cstdio>
#include <cstdlib>
#include <cstring>


int sg[256];
bool bVis[256][256];
char str[256];

int t, size;

int GetSG(int len)//求SG值，个人习惯记忆话搜索
{
	if (sg[len] != -1) return sg[len];
	sg[len] = 0;
	for (int i(0); i != len; ++i)
	{
		int val(0);
		if (i >= 2)
		{
			val ^= GetSG(i - 2);//求子状态的NIM和
		}
		if (len - i - 3 >= 0)
		{
			val ^= GetSG(len - i - 3);//求子状态的NIM和
		}
		bVis[len][val] = true;
	}
	while (bVis[len][sg[len]]) ++sg[len];//找到mex值
	return sg[len];
}


int judge()//判断当前状态是否必胜
{
	bool win(0);
	for (int i(0); i != size; ++i)
	{
		if (str[i] == 'X')
		{
			int cnt(1);
			for (int j(i + 1); j < size && str[j] == 'X'; ++j)
			{
				++cnt;
			}
			if (cnt == 2) win = 1;//如果有两个棋子连着，下一步必胜
			if (cnt >= 3) return 0;//当然，如果已经出现了三个棋子，就已经必败了，甭管下一步了
			if (i + 2 < size && str[i + 2] == 'X') win = 1;//如果有X.X，下一步必胜
		}
	}
	if (win) return win;//当前还没有输而且下一步必胜，那就赢啦
	int ret(0);
	int front(0);
	for (int i(0); i != size; ++i)
	{
		if (str[i] == 'X')//找到一个X
		{
			if (i - 3 >= front) ret ^= GetSG(i - 2 - front);//将X与X之间的可落子位置的长度提取出来
			front = i + 3;
		}
	}
	if (size > front) ret ^= GetSG(size - front);//剩余的可落子位置长度
	return ret;
}

int main()
{
	memset(sg, -1, sizeof(sg));
	sg[0] = 0;
	scanf("%d", &t);
	for (int i(0); i != t; ++i)
	{
		scanf("%s", str);
		size = 0;
		while (str[size]) ++size;
		if (judge())
		{
			printf("WINNING\n");
			bool bFirst(true);
			for (int i(0); i != size; ++i)
			{
				if (str[i] == '.')
				{
					str[i] = 'X';//尝试在这里落子
					if (judge() == 0)//这么下敌方必败
					{
						if (!bFirst) printf(" ");
						else bFirst = false;
						printf("%d", i + 1);
					}
					str[i] = '.';
				}
			}
			printf("\n");
		}
		else
		{
			printf("LOSING\n\n");//输出两个空行……这一点弄得我心力憔悴……
		}
	}
	return 0;
}
```



---

## 作者：Tenshi (赞：1)

这题细节还挺多的。

## 分析
拿到题目先拿样例找一下性质。

对于最初的局面，发现如果有一个位置出现 `X`，那么它的左边两个或者右边两个位置只要存在 `X`，那么先手必然胜利。

如果不存在上面的情况，我们就可以枚举一下先手决策的位置，看看所得到的状态能不能让后手必输。

这时候我们想到用 sg 函数来刻画这一点。

> 方便起见，我们约定 `X` 的左右两个位置为“禁着点”（记为 `O`）（因为谁在这个地方下了 `X` 谁就输了）。

用 $f[x]$ 表示空棋盘（也就是 $x$ 个 `.`）的 sg 函数值。

我们以 $x=10$ 为例（`..........`）：

当下了一个 `X` 时在位置 $p=5$ 时，棋盘变为 `..OOXOO...`。

剩下的部分可以看成两个棋盘，大小分别为 $2, 3$。

----

一般地，对于落点 $p$，得到的两个新棋盘的 sg 函数值为 $f[\max(0, p-3)],~f[\max(0, x-p-2)]$。

类似地枚举落点的位置，我们可以得到 $f[x]$：
$$f[x] = {\rm mex}_{p=1}^{x} (f[\max(0, p-3)]\oplus  f[\max(0, x-p-2)])$$

> mex（minimal exdudant）函数

> 设 $S$ 表示一个非负整数集合。定义 ${\rm mex{(S)}}$ 为求出不属于集合 $S$ 的最小非负整数的运算。
如：{ $0,1,3$ } 对应的 ${\rm mex}$ 值 就是 $2$。



------------

最后还要提醒一下输出问题：
- 每一行输出行末不要空格！
- 如果判断得到的是 `LOSING`，要额外输出一个空行。

~~高清程序~~
```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define debug(x) cerr << #x << ": " << x << endl
#define pb(a) push_back(a)
#define set0(a) memset(a,0,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define ceil(a,b) (a+(b-1))/b
#define INF 0x3f3f3f3f
#define ll_INF 0x7f7f7f7f7f7f7f7f
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<double,double> PDD;

inline void read(int &x) {
    int s=0;x=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=220;

int n;
string str, tmp;

vector<int> res;

int f[N];

int sg(int x){
	if(~f[x]) return f[x];
	
	unordered_set<int> buf;
	rep(i,1,x){ // 枚举决策求 sg 函数
		int len1=i-3, len2=x-i-2;
		len1=max(len1, 0), len2=max(len2, 0);
		int t=sg(len1)^sg(len2);
		buf.insert(t);
	}
	
	int p=0;
	while(buf.count(p)) p++;
	return f[x]=p;
}

void init(){
	memset(f, -1, sizeof f);
	f[0]=0;
	f[1]=f[2]=f[3]=1;
	
	rep(i,1,N-1) sg(i);
}

int main(){
	init(); // 预处理出 sg 函数并存在 f[] 中
	
	int T; cin>>T;
	while(T--){
		res.clear(); // 记得清空 res
		cin>>str;
		n=str.size();
		
		str="##"+str+"##"; // 减少特判边界，加上边界符号
		
		bool ok=false; // 特殊判断一开始的局面是否存在 "XX." "X.X" ".XX" 的情况
		rep(i,2,n+1) if(str[i]=='.'){
			bool fl=false;
			if(str[i-1]=='X' && str[i-2]=='X') ok=fl=true;
			if(str[i+1]=='X' && str[i+2]=='X') ok=fl=true;
			if(str[i-1]=='X' && str[i+1]=='X') ok=fl=true;
			if(fl) res.pb(i);
		}
		
		if(ok){
			puts("WINNING");
			rep(i,0,res.size()-1){
				if(!i) cout<<res[i]-1;
				else cout<<' '<<res[i]-1;
			}
			cout<<endl;
			
			continue;
		}
		
		rep(i,2,n+1) if(str[i-2]!='X' && str[i-1]!='X' && str[i]!='X' && str[i+1]!='X' && str[i+2]!='X'){
			tmp=str; 
			tmp[i]='X';
			
			int t=0;
			rep(j,2,n+1){
				if(tmp[j]=='.'){ // 将连续的 "." 区域拿来讨论。
					int l=j;
					while(tmp[j]=='.') j++; 
					j--;
					int r=j;
					
					int len=r-l+1; 
					if(tmp[l-1]=='X') len-=2; 
					if(tmp[r+1]=='X') len-=2;
					len=max(len, 0);

					t^=f[len];
				}
			}
			
			if(!t) res.pb(i);
		}
		
		if(res.size()){
			puts("WINNING");
			rep(i,0,res.size()-1){
				if(!i) cout<<res[i]-1;
				else cout<<' '<<res[i]-1;
			}
			cout<<endl;
		}
		else puts("LOSING\n");
	}	
    return 0;
}	
```

---

## 作者：yszs (赞：0)

[传送门](https://www.luogu.com.cn/problem/UVA10561)
## $\texttt{Description}$
给定一行 $n$ 个格子，格子上会有一些 `X` ，有两个玩家轮流操作，可以在一个格子上填上一个 `X` ，如果有**三个连续的 `X` 出现**，操作者胜利，你先手，问是否有必胜策略，如果有，输出第一次操作的位置。

$3\leq n \leq 200$
## $\texttt{Solution}$

我们考虑将这个复杂的游戏分解成若干个子游戏。

性质 $1$ ：一个 `X` 的周围两格除非能赢不然是不能填的。(因为你一填对手就可以连成 $3$ 个连续的)

所以我们对初始局面进行一个划分，我们将连续的没有被性质 $1$ 影响的格子称为一个子游戏，每个子游戏就是在一段空的格子上填 `X` 。 


下图红括号框起来的就是一个子游戏，红色的叉就是初始 `X` 。 
![](https://cdn.luogu.com.cn/upload/image_hosting/sgljnaxw.png)

~~画的太丑了，请原谅~~

接下来我们定义 $SG$ 函数

 $\text{SG}[i]$ 表示有 $i$ 个格子的 $\text{SG}$ 值

 $\text{SG}[0]=0$ , $\text{SG}[1]=1$ , $\text{SG}[2]=1$ , $\text{SG}[3]=1$ 。

注意，这些 $<3$ 的都是因为是划分之后的。

现在来求$\text{SG}$函数的值

 $$\text{SG}[i]=\operatorname{mex} \{ \text{SG}[i-3],\text{SG}[i-4],\text{SG}[1] \operatorname{xor} \text{SG}[i-6],\text{SG}[2] \operatorname{xor} \text{SG}[i-7] ...... \} $$

怎么理解呢？

 $\text{SG}[i-3]$ 表示在最左边放了一个 `X` 这时还剩 $i-3$ 个格子

 $\text{SG}[i-4]$ 表示在左边第二个格子放一个 `X` 这时还剩 $i-4$ 个格子

 $\text{SG}[1]\operatorname{xor}\text{SG}[i-6]$ 如图所示

![](https://cdn.luogu.com.cn/upload/image_hosting/t9thjrj4.png)

这就相当于把一个游戏分裂成两个游戏，直接异或起来。

所以打个表就完了。

然后考虑第一次操作的位置，暴力进行一次循环填 `X` 如果这个位置填了以后，是必败态，那么当前位置就是必胜态，直接填。

## $\texttt{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int SG[N],vis[N],a[N],wi,to[N],ans[N];
void getSG(int n)
{
	SG[0]=0;
	SG[1]=1;
	to[1]=
	SG[2]=1;
	SG[3]=1;
	for(int i=4;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		for(int j=3;j<=i;j++)
		{
			if(j>5)
			{
				vis[SG[i-j]^SG[j-5]]=1;
			}
			else vis[SG[i-j]]=1;
		}
		for(int j=0;j<=n;j++)
		{
			if(vis[j]==0)
			{
				SG[i]=j;
				break;
			}
		}
	}
}
bool Win(string s)
{
	int siz=s.size();
	for(int i=1;i<siz-1;i++)
	{
		if(s[i]=='X'&&s[i-1]=='X'&&s[i+1]=='X') return false;
	}
	int bef=0,flag=0,anss=0;
	int tot=0;
	for(int i=0;i<siz;i++)
	{
		if(s[i]=='X') tot++;
	}
	if(tot==0)
	{
		if(SG[siz]!=0)
		{
			return true;
		}
		else return false;
	}
	for(int i=0;i<siz;i++)
	{
		if(s[i]=='X'&&flag==0)
		{
			if(i>=2)
			{
				anss^=SG[i-2];
			}
			bef=i;
			flag=1;
		}
		else if(flag==1&&s[i]=='X')
		{
			if(i-bef==1&&(i+1<siz||bef-1>=0))
			{
				return true;
			}
			else if(i-bef==2)
			{
				return true;
			}
			else if(i-bef>=5)
			{
				anss^=SG[i-bef-5];
			}
			bef=i;
		}
	}
	if(siz-1-bef>=2)
	{
		anss^=SG[siz-1-bef-2];
	}
	return anss!=0;
}
int main()
{
//	freopen("123.txt","w",stdout); 
	getSG(201);
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		if(!Win(s))
		{
			cout<<"LOSING"<<endl<<endl;
		}
		else
		{
			cout<<"WINNING"<<endl;
			int siz=s.size();
			int tot=0;
			for(int i=0;i<siz;i++)
			{
				if(s[i]=='.')
				{
					s[i]='X';
					if(!Win(s))
					{
						ans[++tot]=i+1;
					}
					s[i]='.';
				}
			}
			cout<<ans[1];
			for(int i=2;i<=tot;i++)
			{
				cout<<" "<<ans[i];
			}
			cout<<endl;
		}
	}
	return 0;
}

```
完结撒花

---

