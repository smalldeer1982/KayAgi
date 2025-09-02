# [USACO25JAN] Astral Superposition B

## 题目描述

**注意：本题的时间限制为 4 秒，通常限制的 2 倍。**

Bessie 正在使用她超酷的望远镜拍摄夜空中所有星星的照片。她的望远镜能够拍摄到一张 $N \times N$（$1 \leq N \leq 1000$）的星星照片，其中每个像素是一颗星星或者空旷的天空。每颗星星可由恰好一个像素表示，并且没有两颗不同的星星位于同一像素内。

一夜之间，一些奇怪的事情发生在了天空中的星星之上。每颗星星要么消失，要么向右移动 $A$ 像素，并且向下移动 $B$ 像素（$0 \leq A,B \leq N$）。如果一颗星星消失或移动超出照片边界，它将不再出现在第二张照片中。

Bessie 在星星移动位置之前和之后拍了照片，但在 Mootoshop 中进行了一些实验后，她不小心将一张照片叠加到了另一张上。现在，她可以在两张照片都是天空的位置看到白色（white）像素，在星星仅存在于恰好一张照片的位置看到灰色（gray）像素，而在两张照片中都有星星的位置看到黑色（black）像素。Bessie 同时记得没有新的星星移动入第二张照片的范围，从而她的第一张照片包含了夜空中所有的星星。

对于 $T$（$1 \leq T \leq 1000$）个独立的测试用例，给定最终的照片，求在移动事件发生之前天空中星星的最小可能数量。如果不存在星星的排列可以产生给定的最终照片，输出 $-1$。

## 说明/提示

### 样例解释

在样例 #1 中，没有移动发生。第一张照片如下（. 表示天空，* 表示星星）：
```
..*
***
***
```
第二张照片中最下方一行的星星都消失了，如下：

```
..*
***
...
```
这是产生叠加后照片的唯一方式，所以初始时星星的最小可能数量为 $7$。

对于样例 #2，在第一个测试用例中，初始时至少有 $4$ 颗星星。如果我们令 $(r,c)$ 表示从上到下第 $r$ 行和从左到右第 $c$ 列的交点，一种可能性是它们最初位于 $(1,1)$，$(3,2)$，$(2,2)$ 和 $(1,3)$。除了位于 $(2,2)$ 的星星消失之外，其他所有星星都移动了。

在第二个测试用例中，在给定的移动方式下，没有任何初始照片中的星星排列可以产生中间的黑色像素。

在第三个测试用例中，初始时至少有 $4$ 颗星星。一种可能性是它们最初位于 $(1,1)$，$(1,2)$，$(1,3)$ 和 $(2,1)$。在第二张照片中，原先位于 $(1,1)$ 的星星消失了，原先位于 $(1,3)$ 的星星移出了照片边界。其他两颗星星向右移动了 $1$ 像素。

### 子任务

- 测试点 3：$A=B=0$。
- 测试点 4-7：$A=1$，$B=0$，$N\le 10$。
- 测试点 8-9：$A=1$，$B=0$。
- 测试点 10-12：没有额外限制。

## 样例 #1

### 输入

```
1
3 0 0
WWB
BBB
GGG```

### 输出

```
7```

## 样例 #2

### 输入

```
3
5 1 2
GWGWW
WGWWW
WBWGW
WWWWW
WWGWW
3 1 1
WWW
WBW
WWW
3 1 0
GGB
GGW
WWW```

### 输出

```
4
-1
4```

# 题解

## 作者：chzhh_111 (赞：6)

我是用通过模拟来判断是否存在可行的方案并记录数量。

我们首先用两个数组来记录 $\texttt{G}$ 和 $\texttt{B}$ 的位置。

接下来我们再用两个布尔数组 $p1$ 和 $p2$ 来分别记录来，这一个位置的星星是属于第一张照片还是属于第二张照片，当然，如果这个位置为黑色，那么这个位置的两个布尔数组都是 $true$。

然后我们再用两个变量 $sum1$ 和 $sum2$ 来分别记录第一张星星的数量和第二张星星的数量（实际上应该只要用一个就行了）。

我们可以十分肯定地确认，如果照片的某一个位置为 $\texttt{B}$，那么这个位置肯定就有第一张照片的星星和第二张照片的星星。所以如果一个位置为 $\texttt{B}$，那么我们可以从此位置向上移动 $B$ 个单位，再向左移动 $A$ 个单位，看一下移动后的位置：

- 第一种情况，如果它已经在这个照片外，那么肯定没有合法方案。因为题目已经说了，第一个照片当中包含了所有的星星，而且第二张照片的星星必须得从第一张照片的星星转移过来。所以就可以判断，如果出现这样的情况，就不存在合法方案。

- 第二种情况就是这个位置为 $\texttt{W}$，同理这样也没有合法方案。

因此如果出现以上两种情况，就直接输出 $-1$。否则，我们就将移动后的位置和当今位置的 $p1$ 标记成 $true$，将当今位置的 $p2$ 也标记成 $true$，$sum1$ 和 $sum2$ 也随之改变。

接下来我们再考虑 $\texttt{G}$ 的位置：

- 第一种情况，如果这个位置我们之前已经标记过了就不用再判断了。

- 第二种情况，继续判断从此位置向上移动 $B$ 个单位，再向左移动 $A$ 个单位后的位置。如果它在照片外面或者这个位置为 $\texttt{W}$，则当今位置为第一张照片的星星，而且从此位置向下移动 $B$ 个单位，再向右移动 $A$ 个单位的位置如果为 $\texttt{G}$，且这个位置的 $p1$ 为 $false$，则这个位置为第二张照片的星星。

- 第三种情况，如果从此位置向上移动 $B$ 个单位，再向左移动 $A$ 个单位后的位置在照片内，且该位置的 $p1$ 为 $true$，那这个位置就为第二张照片的星星。

我们再进行相应的统计。

最后输出 $sum1$ 就是答案了。

代码部分：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1001;
int T,n,A,B,sum1,sum2;char a[N][N];
bool p1[N][N],p2[N][N];
struct dian{
    int x,y;
};
vector<dian>b,g;
void clean()
{
    memset(p1,0,sizeof(p1));
    memset(p2,0,sizeof(p2));
    sum1=sum2=0;
}
bool solve()
{
    for(dian i:b)
    {
        int x=i.x,y=i.y;
        if(x-B<1||y-A<1||a[x-B][y-A]=='W') return 0;
        sum1+=!p1[x-B][y-A];
        p1[x-B][y-A]=1;
        sum1+=!p1[x][y];
        p1[x][y]=1;
        p2[x][y]=1;
        sum2++;
    }
    for(dian i:g)
    {
        int x=i.x,y=i.y;
        if(p1[x][y]||p2[x][y]) continue;
        if(x-B<1||y-A<1||!p1[x-B][y-A])
        {
            p1[x][y]=1;
            sum1++;
            if(x+B<=n&&y+A<=n&&a[x+B][y+A]=='G'&&!p1[x+B][y+A])
            {
                p2[x+B][y+A]=1;
                sum2++;
            }
        }
        else if(x-B>=1&&y-A>=1&&p1[x-B][y-A]) p2[x][y]=1,sum2++;
    }
    return 1;
}
signed main()
{
    scanf("%lld",&T);
    while(T--)
    {
        clean();
        scanf("%lld%lld%lld",&n,&A,&B);
        b.clear(),g.clear();
        for(int i=1;i<=n;i++)
        {
            scanf("%s",a[i]+1);
            for(int j=1;j<=n;j++)
            {
                if(a[i][j]=='B') b.push_back((dian){i,j});
                if(a[i][j]=='G') g.push_back((dian){i,j});
            }
        }
        if(solve()) printf("%lld\n",sum1);
          else printf("-1\n");
    }
    return 0;
}
```

---

## 作者：vectorxyz (赞：4)

## Solution
[传送门](https://www.luogu.com.cn/problem/P11667)。

很好理解的一种方法。

不难发现，如果当前点是 $\tt{W}$，那么对我们的答案是没有贡献的。然后只剩下了两种情况，我们进行分类讨论。

我们先排除特殊情况，即 $a=b=0$，答案显然就是所有 $\tt{B}$ 点和 $\tt{G}$ 点的数量和。

若当前点是 $\tt{B}$，如果它不能靠一个格子移过来，那么就无解，理由很简单，因为操作只可能消失或移动，如果他是 $\tt{B}$，说明第一张图上一定有一个星星，要使第二张图上有星星，只能靠其他来移动。反之，如果有解，那么我们就将那个一个转移的格子打上标记，方便后续处理，马上会讲。

然后我们对于所有 $\tt{G}$ 点，并且 **没有打上标记** 的格子进行处理。

为什么一定是没有打上标记呢？因为打上标记的都是转移给黑色格子，这个点 **必须** 存在，如果不存在，也是其他点转移的那么就无解了。

处理就很显然了，如果这个点可以被转移来，那么这个点一开始就可以没有，我们一开始存下所有黑灰点数 $cnt$，然后这里让 $cnt-1$ 即可。

## Code
很好实现，就是有点细节，注意特判。
```cpp
// Problem: 
//     P11667 [USACO25JAN] Astral Superposition B
//   
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11667
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// By vectorxyz
// 
// Powered by CP Editor (https://cpeditor.org)
#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace std
{
    template<typename T>
    T read(T x)
    {
        T opt = 1,sum = 0;
        char ch = getchar();
        while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
        while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
        return opt * sum;
    }
}
#define read std::read(0ll)
#define rep(i, a, b) for(int i = a;i <= b;i ++ )
#define pre(i, a, b) for(int i = a;i >= b;i -- )

inline void write(int x){
	if (x < 0) x = ~x + 1, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

const int N = 1e3 + 5, inf = 1e9 + 7;
int ans;
char c[N][N];
inline void case1()//特判
{
	cout << ans << endl;
}
int n, a, b;
int f;
bool vis[N][N];
inline void case2()
{
	rep(i, 1, n){
		rep(j, 1, n){
			if(c[i][j] == 'B'){
				if(i - a >= 1 && j - b >= 1){
				if(c[i - a][j - b] == 'G'){
					vis[i - a][j - b] = 1;
				}
				else if(c[i - a][j - b] != 'B') {
					f = -1;
					break;
				}}
				else {f = -1; break;
				}
			}
		}
	}
	if(f == -1) {cout << -1 << endl; return ;}
	rep(i, 1, n){
		rep(j, 1, n){
			if(!vis[i][j] && c[i][j] == 'G'){
				if(i - a >= 1 && j - b >= 1 && (c[i - a][j - b] == 'G' || c[i - a][j - b] == 'B') && !vis[i - a][j - b]){
					vis[i - a][j - b] = 1; vis[i][j] = 1;
					ans -- ;
				}
			}
		}
	}
	cout << ans << endl;
}

void work()
{
	n = read, a = read, b = read;
	f = 0;
	memset(vis, 0, sizeof(vis));
	ans = 0 ;
	swap(a, b);
	rep(i, 1, n) {
		rep(j, 1, n) {
			cin >> c[i][j];
			if(c[i][j] == 'G' || c[i][j] == 'B'){
				ans ++ ;
			}
		}
	}
	if(a == 0 && b == 0){
		case1(); return ;
	}
	case2(); return ;
}

signed main(){int T = read; rep(i, 1, T){work();}}
```

---

## 作者：coding_sealion (赞：4)

### 题目大意：

有一张图（ $0,1$ 组成，不是输入的图），以某种程度（ $x$ 轴移动 $a$ 格， $y$ 轴移动 $b$ 格）移动后，先后两张图重合在一起（相加），最终结果已知。求原来图中最少的星星（ $1$ ）的个数，如果无解就输出 $-1$ 。

### 解题思路：

本题是贪心。

以给出的图为准，假设为原图（移动前的图），按照要求， $x$ 轴移动 $a$ 格， $y$ 轴移动 $b$ 格。重叠的部分可能是星星移动后的位置，减去， $sum+1$ 。
剩下的部分若还有正数：正数大于一或无法到达该点，输出 $-1$ ；否则 $sum+1$ 。

####  $AC$ 代码


```cpp
//头文件自己写
int n,a,b,t;
char s;
int c[5005][5005],p[5005][5005];
bool m[5005][5005];
int main(){
	cin>>t;//有t组数据
	while(t--){
		int sum=0,ans=0;
		bool q=0,v=0;//赋初值
		cin>>n>>a>>b;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>s;
				if(s=='G')c[i][j]=1,m[i][j]=1;//G代表有一个
				else if(s=='B')c[i][j]=2,m[i][j]=1;//B代表两个都有
				else c[i][j]=0,m[i][j]=0;//W一个都没有
       //c数组用来记星星有几个，m记录原来有没有星星
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(!(i+b>n||j+a>n)&&c[i][j]>0){//判断是否出界
					c[i+b][j+a]--;
					sum++;
					c[i][j]--;//假设是原图消除，算做一个星星
				}else if((i+b>n||j+a>n)&&c[i][j]>0)sum++,c[i][j]--;//如果出界了，无法消除，但也是一个星星
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(c[i][j]>0){//如果仍未被消除
					if(i-b>0&&j-a>0&&m[i-b][j-a])sum++;//它其实可以被消除的情况
					else q=1;//否则标记-1，这里实际上可以break
				}
			}
		}
		if(q)cout<<-1<<endl;//如果被打了标记就输出-1
		else cout<<sum<<endl;//输出
	}
	return 0;
}
```

---

## 作者：UNDERTALE_RS (赞：2)

# P11667 [USACO25JAN] Astral Superposition B 题解

[题目传送门](https://www.luogu.com.cn/problem/P11667)

## 题目分析

看到题目，对于每个格子，我们根据其颜色来分类讨论。我们首先要判断这张合成照片是否可以产生，再去找最小值。

### 判断是否可以产生此照片
最小值要在**可行**的照片下才能求得，所以我们第一步就是判断其可行性。

我们分情况讨论：若该格子是**白色**，它一定是两张照片都没有出现，所以不用管它；若该格子是**灰色**，它可能是在第一张照片中存在，在第二张照片中**消失或移动**，可能是在第一张照片中不存在，在第二张照片中由**另外的星星移动**得到；若该格子是**黑色**，那么它**一定**是在第一张照片中存在，**且**在第二张照片中由**另外的星星移动**得到（因为第一张照片中的星星会消失或移动）。

我们可以发现，灰色的格子是很好应付的，它可以是一颗星星直接消失；而黑色的格子很难应付，它的第二张照片必须是另外的星星移动得到，否则这张照片就是**无法产生的**。  
因此，可行性的关键在于黑色格子。所以我们第一步就判断黑色格子。

为了方便后续判断，我们记录一下黑色格子是不是已经向之前的星星借过了（即是否已经由之前的星星移动得到过了，避免重复判断）。

代码如下：  
```cpp
cin >> T;
while(T--){
	memset(bor,0,sizeof(bor));
	int ans = 0;
	bool is_c = 1;
	cin >> n >> a >> b;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++){
			cin >> c;
			pt[i][j] = (c != 'W')*(c == 'G'?1:2); //很抽象，其实就是记录这个格子上俩照片总的星星个数
			if(pt[i][j] == 2){ //黑色格子
				if(j-a >= 1 && i-b >= 1 && pt[i-b][j-a] > 0)
            //移动前位置在照片范围内且有星星就可以由那颗星星移动得到第二张照片中的星星
					pt[i-b][j-a]--,ans++,pt[i][j]--,bor[i][j] = 1;
            //这里表明了存在原位在pt[i-b][j-a]的星星且它会移动而不是消失，我们提前计算它。
            //同时pt[i][j]格子已经可以算为灰色，并且它借过之前的格子。
				else is_c = 0; // 否则无法产生此照片
			}
		}
	if(!is_c){
		cout << "-1\n"; continue; //慢走不送
	}
```



### 最小化答案
现在如果这张照片是可产生的，那么我们就去让答案尽可能的小。

在之前，通过我们的操作这张照片只剩下了灰色格子。如果要让我们的答案尽可能小，那么这个灰色格子就要尽量是由**之前的星星移动**得到，否则这里就要有一颗星星。

对于每一个灰色格子，如果它可以由**之前的星星移动**得到，并且它还没借过（不是黑色格子，黑色之前已计算过），那么这个格子一开始就省了颗星星。

同时，我们要对 $A = 0,B = 0$ 的情况分类讨论，这种情况下它是不能借的，否则这里就会有两颗星星。

最终代码如下：  
```cpp
#include <iostream>
#include <cstring>
using namespace std;
int T,n,a,b;
int pt[1005][1005];
bool bor[1005][1005];
char c;
int main(){
	cin >> T;
	while(T--){
		memset(bor,0,sizeof(bor));
		int ans = 0;
		bool is_c = 1;
		cin >> n >> a >> b;
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++){
				cin >> c;
				pt[i][j] = (c != 'W')*(c == 'G'?1:2);
				if(pt[i][j] == 2){
					if(j-a >= 1 && i-b >= 1 && pt[i-b][j-a] > 0)
						pt[i-b][j-a]--,pt[i][j]--,ans++,bor[i][j] = 1;
					else is_c = 0;
				}
			}
		if(!is_c){
			cout << "-1\n"; continue;
		}
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++)
				if(pt[i][j] == 1){
					if(!(!bor[i][j] && j-a >= 1 && i-b >= 1 && pt[i-b][j-a] > 0 && (a||b)))
						ans++; //借不了
					else pt[i][j]--; //可以借别人的，但同时它不能被借了
				}
		cout << ans << "\n";
	}
	return 0;
}
```


## 总结
是一道基础的题，看似简单，实则细节较多，考察贪心及一些细节部分。

感谢您的阅读！

---

## 作者：Doraeman (赞：1)

## 提示
此题使用时间复杂度为 $O(N^2T)$ 的算法并不会超时，因为题目保证所有的 $N^2$ 之和不超过 $10^7$。
## 思路
使用数组 $t$ 表示第一次的天空状态（简称“状态 $1$”）下 各个位置的星星（$0$ 表示无，$1$ 表示有）。  
使用数组 $a$ 表示状态 $1$ 和第二次天空（简称状态 $2$）的星星重合后的天空状态下各个位置的星星（$0$ 表示白，$1$ 表示灰，$2$ 表示黑）。
## 更新数组
如果 $(i,j)$ 前后两种状态下都没有星星，那么显然状态 $1$ 也没有星星。

同理，如果 $(i,j)$ 前后两种状态下都有星星，此时状态 $1$ 必然有有星星。  
此外，我们还要关注状态 $2$ 下有没有星星，也就是 $(i-B,j-A)$ 的位置是否有星星。  
如果该位置有星星，那么才可能出现重合后 $(i,j)$ 位置为黑色的情况。  
反之，如果该位置没有星星，那么 $(i,j)$ 位置不可能为黑色，不符合题意，直接输出 $-1$。

最后，考虑天空是灰色的情况。  
此时 $(i,j)$ 为灰色，可能是状态 $1$ 有星星，也可能是状态 $2$ 有星星。分类讨论。  
1. 如果重合后 $(i+B,j+A)$ 位置是黑色，那么状态 $1$ 的 $(i,j)$ 位置必然存在星星，并在状态 $2$ 中挪动到 $(i+B,j+A)$ 位置。此时有状态 $1$ 必然有星星。
2. 否则，如果状态 $2$ 的 $(i,j)$ 位置没有星星来自状态 $1$ 的 $(i-B,j-A)$ 位置，即唯一的一颗星星一定来自状态 $1$ 的 $(i,j)$ 位置。此时有状态 $1$ 必然有星星。
3. 否则，如果状态 $2$ 的 $(i,j)$ 位置有星星来自状态 $1$ 的 $(i-B,j-A)$ 位置，即唯一的一颗星星来自状态 $2$，也就是状态 $1$ 的 $(i-B,j-A)$ 位置。此时无需状态 $1$ 的 $(i,j)$ 位置贡献星星。

将以上全部内容变成代码，并加入适当调整，即可 AC。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+5;
int a[N][N];
int main(){
	int T; cin >> T;
	while(T--){
		memset(a, 0, sizeof(a));
		int n, x, y; cin >> n >> x >> y;
		
		for(int i=1; i<=n; i++){
			string s; cin >> s; 
			// 直接用 char 读入会读到 \n，不好处理，可以使用 string 
			for(int j=0; j<n; j++){
				if(s[j] == 'B')
					a[i][j+1] = 2;
				if(s[j] == 'G')
					a[i][j+1] = 1;
			}
		}
		
		bool t[N][N] = {0}, flag = 0;
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				int px = max(0, i - y),	
					py = max(0, j - x);	
				// 状态2的位置为(i, j)的星星在状态1时的位置为(px, py)
				// 如果(px, py)不在矩阵内，设其为(0, 0)，该位置没有星星 
					
				if(a[i][j] == 1){
					if(a[min(n+1,i+y)][min(n+1,j+x)] == 2)
						// 状态1中位置在(i, j)的星星需要挪动到(i+B, j+A)位置，使该位置成为黑色 
						t[i][j] = 1;
					if(t[px][py] == 0)
						// 状态2的(i, j)没有星星来自状态1的(px, py)，即灰色的星星一定来自状态1的(i, j) 
						t[i][j] = 1;
					// 省略了判断条件：t[px][py] == 1，
					// 此时状态2的(i, j)位置已经有星星，无需状态1的(i, j)位置存在星星 
				}
				
				if(a[i][j] == 2){
					t[i][j] = 1;
					if(t[px][py] == 0){
						flag = 1;
						break;
					}
				}
				
			}
			if(flag)
				break;
		}
		if(flag){
			cout << "-1\n";
			continue;
		}
		int ans = 0;
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				ans += t[i][j];
		cout << ans << '\n';
	}
	return 0; 
}




/*
数组 bool t[i][j] 表示第一次这里的星星
更新方法：
a[i][j]=0:
	t[i][j]=0
	
	
a[i][j]=1:
	a[i+x][j+y]=2:
		t[i][j]=1
		continue
		
	t[i-x][j-y]=0:
		t[i][j]=1
		
	t[i-x][j-y]=1:
		t[i][j]=0
		
		
a[i][j]=2:
	t[i-x][j-y]=0:
		输出 -1
	t[i-x][j-y]=1:
		t[i][j]=1


 
每个星星的出现状态：
a[i][j]=0:
	本来就没有
	
a[i][j]=1:
	检查 a[i-x][j-y]:
		如果 a[i-x][j-y] == 0:
			a[i][j] 是自己产生
			答案 +1
		如果 a[i-x][j-y] == 1:
			a[i][j] 是它移过来的 
*/
```

---

## 作者：f_K_e1207 (赞：1)

建议降黄，~~因为我不能切绿~~。

题面比较长，简单概括，第一张照片包含所有的星星，第二张照片相比第一张照片，所有的星星都消失或向右移动 $B$ 位，**并且**向下移动 $A$ 位，但是不能不做任何操作。将两张照片叠加，如何在两张照片上该位置都有星星，那么该位置是黑色的，如果仅在一张照片中该位置有星星，那么该位置是灰色的，如果两张照片上该位置都没有星星，那么该位置是白色的，需要求出第一张照片至少有几个星星。

显然，白色的区域是不用考虑的，灰色的区域在第一张照片中都有可能有星星，但是既然要求出最小值，那我们就应该让它尽可能没有星星。如果位置 $c_{i,j}$ 是灰色的且位置 $c_{i-B,j-A}$ 在第一张照片是有星星的，那么位置 $c_{i,j}$ 就有可能是在第二张照片中有星星，且是从第一张照片中的 $c_{i-B,j-A}$ 位置的星星移动过来的。否则，该位置在第一张照片中一定有星星。

再考虑黑色的位置，黑色的位置在第一张照片和第二张照片中都必定有星星。黑色的位置是用于判断是否存在合法方案的，如果 $c_{i,j}$ 位置是黑色的，但是 $c_{i-B,j-A}$ 是白色的，就不可能有合法方案，因为在第一张图片中没有星星可以转移到 $c_{i,j}$ 位置，所以第二张图片在该位置上不可能有星星。或者 $i<B$ 或 $j<A$，因为题目中说没有新的星星进入第二张照片，所以也没有星星能够移动到 $c_{i,j}$ 位置。

这个时候就可以写代码了，我采用的是标记法。先遍历判断哪些位置在第一张图片中必定有星星，将其标记，最后再遍历一遍统计答案，时间复杂度为 $O(n^2)$。贴在下面：
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,b,ans;
char g[1010][1010];
bool flag,vis[1010][1010];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>T;
	while(T--)
	{
		ans=0;
		flag=0;
		memset(vis,0,sizeof(vis));
		memset(g,0,sizeof(g));
		cin>>n>>a>>b;
		for (int i=0;i<n;i++)
			cin>>g[i];
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<n;j++)
			{
				if (g[i][j]=='B')
				{
					vis[i][j]=1;
					if (i>=b&&j>=a&&g[i-b][j-a]!='W') vis[i-b][j-a]=1;
					else
					{
						flag=1;
						break;
					}
				}
				else if (g[i][j]=='G')
					if (!(i>=b&&j>=a&&g[i-b][j-a]!='W'&&vis[i-b][j-a])) vis[i][j]=1;
			}
			if (flag)
			{
				cout<<-1<<'\n';
				break;
			}
		}
		if (!flag)
		{
			for (int i=0;i<n;i++)
				for (int j=0;j<n;j++)
					if (vis[i][j]) ans++;
			cout<<ans<<'\n';
		}
	}
	return 0;
}
~~~

---

## 作者：Explorer67 (赞：1)

## 一：
特判不存在星星的排列可以产生给定的最终照片的情况：如果字母是 $B$ ，向左 $A$ 像素，向上 $B$ 像素的位置是 $W$ 或在照片外时，输出  $-1$。   
         
同时，当字母是 $B$ ，向左 $A$ 像素，向上 $B$ 像素的位置是 $G$ 时，就把 `mp[i-b][j-a]` 设为 $T$。 


```cpp
bool check(){
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(i-b>0&&j-a>0){
                if(mp[i][j]=='B'&&mp[i-b][j-a]=='W'){
                    return 1;
                }
            }
            if(!(i-b>0&&j-a>0)&&mp[i][j]=='B')
                return 1;
            if(i-b>0&&j-a>0)
                if(mp[i][j]=='B'&&mp[i-b][j-a]=='G')
                    mp[i-b][j-a]='T';
        }
    }
    return 0;
}
```

## 二：
再次遍历，如果不是 $W$ 就将星星最小可能数量加 $1$ 。    
      
注意：**如果字母是 $B$ 或 $G$ ，向右 $A$ 像素，向下 $B$ 像素的位置是 $G$ ，就将其设为 $W$ 。**

```cpp
for(int i=1;i<=n;++i){
    for(int j=1;j<=n;++j){
        if(mp[i][j]=='T')
            ans++;
        if(mp[i][j]=='G'||mp[i][j]=='B'){
            if(i+b<=n&&j+a<=n){
                if(mp[i+b][j+a]=='G'){
                    mp[i+b][j+a]='W';
                    ans++;
                }
                else 
                    ans++;
            }
            else 
                ans++;
        }
    }
}
```




## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define M 1100

int t,n,a,b;
char mp[M][M];

bool check(){
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            if(i-b>0&&j-a>0){
                if(mp[i][j]=='B'&&mp[i-b][j-a]=='W'){
                    return 1;
                }
            }
            if(!(i-b>0&&j-a>0)&&mp[i][j]=='B')
                return 1;
            if(i-b>0&&j-a>0)
                if(mp[i][j]=='B'&&mp[i-b][j-a]=='G')
                    mp[i-b][j-a]='T';
        }
    }
    return 0;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>a>>b;
        int ans=0;
        memset(mp,0,sizeof(mp));
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                cin>>mp[i][j];
            }
        }
        if(check()){
            cout<<-1<<'\n';
            continue;
        }
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                if(mp[i][j]=='T')
                    ans++;
                if(mp[i][j]=='G'||mp[i][j]=='B'){
                    if(i+b<=n&&j+a<=n){
                   		if(mp[i+b][j+a]=='G'){
                     		mp[i+b][j+a]='W';
                        	ans++;
                    	}
                        else 
                            ans++;
                    }
                    else 
                        ans++;
                }
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：lkjlkjlkj2012 (赞：1)

### 思路
1. 如果一个方格是黑色的，那么显然它的位置一开始有一颗星星，并且有一颗星星移动到那里。
2. 之后考虑灰色方格，它要么是一开始这里有星星，要么是有星星移动到这里。
3. 最后就可以愉快的输出答案啦。
### 实现细节
1. 处理黑色方格时可以只处理移动到这里的那颗星星，转化为灰色方格情况。
2. 处理灰色方格时注意到 $a, b \ge 0$ ，可以在标记星星时预先把移动到的位置处理成白色。
### 代码
```cpp
// Problem: Problem 1. Astral Superposition
// Contest: USACO - USACO 2025 January Contest, Bronze
// URL: https://usaco.org/index.php?page=viewproblem&cpid=1455
// Memory Limit: 256 MB
// Time Limit: 4000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
int t, n, a, b, c[1005][1005], sum;
bool sh[1005][1005];  // there should have a star
// bool no[1005][1005];   // there no star
// bool dis[1005][1005];  // no star or disappear
// bool d[1005][1005];  // do
void solve() {
  cin >> n >> a >> b;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      char ch;
      do {
        ch = cin.get();
      } while (isspace(ch));
      if (ch == 'W')
        c[i][j] = 0;
      else if (ch == 'G')
        c[i][j] = 1;
      else
        c[i][j] = 2;
      sum += c[i][j];
    }
  // int fi,se;
  // if(sum==sum/2*2)
  // fi=se=sum/2;
  // else
  // fi=(sum+1)/2,se=sum/2;
  // we want fi star in first and se star in second
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (c[i][j] == 2) {
        if (i <= b || j <= a) {
          cout << -1 << endl;
          return;
        }
        c[i][j]--;
        c[i - b][j - a]--;
        sh[i - b][j - a] = true;
        // if (i + b <= n && j + a <= n && c[i + b][j + a]) c[i + b][j + a]--;
      }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      if (c[i][j] == 1) {
        c[i][j]--;
        sh[i][j] = true;
        if (i + b <= n && j + a <= n && c[i + b][j + a]) c[i + b][j + a]--;
      }
    }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (c[i][j] != 0) {
        cout << -1 << endl;
        return;
      }
  int ans = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (sh[i][j]) ans++;  //, cout << i << " " << j << endl;
  cout << ans << endl;
}
void clear() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      c[i][j] = 0;
      sh[i][j] = false;
      // no[i][j] = false;
      // d[i][j] = false;
    }
  }
  n = a = b = sum = 0;
}
int main() {
  cin >> t;
  while (t--) {
    solve();
    clear();
  }
}
```
### 题外话
考场上时先写了一个顺次考虑每个方格的做法，总是通不过样例。后来改成了记忆化搜索，还是有问题。最后做完后两题才想出现在这个做法。代码里也可以看到很多乱搞痕迹……

---

## 作者：nbhs23a28 (赞：1)

一道朴素的贪心模拟题。

首先我们根据题面，很容易想到贪心：由于黑色像素一定是由变换前后两颗星叠加的，所以可以先处理黑色像素顺便更新从该点变换达的像素（注意若可变换达的点为灰像素，考虑是否必要从该像素变换使另一黑像素合理），然后统一处理灰像素，开个计数变量，很容易就得到正解了。

[Code](https://www.luogu.com.cn/paste/finoqnvs)

---

## 作者：zhenghuangzhe (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P11667)

## 题意概括

Bessie 拍了两张关于星星的照片，第一张照片没有任何改动，第二张图片里的每颗星星要么消失，要么向右移动 $A$ 像素，**并且**向下移动 $B$ 像素。现在将两张照片叠起来，已知叠起来的照片，求第一张照片中星星的**最小**可能数量。

## 分析过程

第一眼看到题目，我们便想到要**逆推模拟**，也就是将重叠的还原为第一张图片。

此时我们要引入三个数组：

- used，用来标记哪个位置有星星
- g，消除上一个点的影响（避免重复统计）
- g1，原数组的备份（原因后面会讲，见代码注释）

枚举每一个点，先要判断**有没有越界**（因为我们要访问这个点），如果上一个位置，也就是 $(i - a, j - b)$ 这个点有一颗星星，可想而知一定是**多余的星星**，将该点减去一个星星。

接下来分类讨论：

如果该点只有一颗星星，就只要 used 增加 $1$，然后计数变量增加 $1$，就可以继续循环了。

但如果有两颗星星，就有点复杂了。

在两颗星星的情况下，其一定受到前面，即 $(i - a, j - b)$ 这个点的影响，毕竟一颗星星总不能消失两次，通过这个就可以判断是否不满足条件了。

最后还有特殊情况：$A$ 和 $B$ 均为 $0$，此时所有有星星的方格都可以算在里面。

每种情况都判断好后，代码也就呼之欲出了。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a, b, ans;
int g[1001][1001], g1[1001][1001], used[1001][1001]; //used 标记哪个位置有星星 g 消除上一个点的影响 
void check()
{
	memset(g, 0, 4 * 1001 * 1001);
	memset(g1, 0, 4 * 1001 * 1001);
	memset(used, 0, 4 * 1001 * 1001);
	ans = 0;
	scanf("%d %d %d", &n, &b, &a);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			char x;
			cin >> x;
			// 为方便枚举，将字符转换为数字 
			if(x == 'W') g[i][j] = 0;
			else if(x == 'G') g[i][j] = 1;
			else g[i][j] = 2;
		}
	} 
	memcpy(g1, g, 4 * 1001 * 1001); // g1 备份 
	if(a == 0 && b == 0) //特殊情况：a、b都是0，只要有星星都算 
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				if(g[i][j] > 0)
				{
					ans++; 
				}
			}
		}
		printf("%d\n", ans);
		return ;
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(i - a >= 1 && j - b >= 1) // 判断是否越界，消除上一个点的影响，避免重复统计 
			{
				if(used[i - a][j - b])
				{
					g[i][j]--;
				}
			}
			if(g[i][j] == 2) // 如果有两颗星星 
			{
				used[i][j] = 1;
				ans++;
				if(i - a >= 1 && j - b >= 1 && g1[i - a][j - b]) // g 由于修改过，会影响判断，故使用 g1 
				{
					if(used[i - a][j - b] == 0)
					{
						ans++;
					}
				}
				else
				{
					printf("-1\n");
					return ;
				}
			}
			else if(g[i][j] == 1) // 如果有一颗星星 
			{
				ans++;
				used[i][j] = 1;
			}
			else used[i][j] = 0; // 如果有零颗星星（可选） 
		}
	}
	printf("%d\n", ans);
}
int main()
{
	scanf("%d", &t);
	while(t--) check();
	return 0;
}

```

---

