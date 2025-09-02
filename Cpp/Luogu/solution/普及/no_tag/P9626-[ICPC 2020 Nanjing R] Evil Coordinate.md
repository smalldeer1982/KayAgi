# [ICPC 2020 Nanjing R] Evil Coordinate

## 题目描述

一个机器人站在一个无限的二维平面上。它被编程为一个长度为 $n$ 的字符串 $s_1s_2\cdots s_n$，其中 $s_i \in \{\text{`U'}, \text{`D'}, \text{`L'}, \text{`R'}\}$，机器人将从 $(0, 0)$ 开始移动，并按照字符串中的字符指令进行移动。

更正式地说，设 $(x, y)$ 为机器人的当前位置。机器人从 $(0, 0)$ 开始，重复以下过程 $n$ 次。在第 $i$ 次时：

- 如果 $s_i = \text{`U'}`，机器人从 $(x, y)$ 移动到 $(x, y+1)$；
- 如果 $s_i = \text{`D'}`，机器人从 $(x, y)$ 移动到 $(x, y-1)$；
- 如果 $s_i = \text{`L'}`，机器人从 $(x, y)$ 移动到 $(x-1, y)$；
- 如果 $s_i = \text{`R'}`，机器人从 $(x, y)$ 移动到 $(x+1, y)$。

然而，在坐标 $(m_x, m_y)$ 下埋有一个地雷。如果机器人在移动过程中踩到 $(m_x, m_y)$，它将被炸成碎片。可怜的机器人！

你的任务是重新排列字符串中的字符，使得机器人不会踩到 $(m_x, m_y)$。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
1 1
RURULLD
0 5
UUU
0 3
UUU
0 2
UUU
0 0
UUU
```

### 输出

```
LDLRUUR
UUU
Impossible
Impossible
Impossible
```

# 题解

## 作者：WhitD (赞：3)

## 题目大意
你有一个机器人，初始坐标位于 $(0,0)$，有一个地雷位于 $(x,y)$，给你一串操作符（由 `U,D,L,R` 构成）。

`U` 能让机器人从 $(x,y)$ 移动到 $(x,y+1)$，`D` 能让机器人从 $(x,y)$ 移动到 $(x,y-1)$，`L` 能让机器人从 $(x,y)$ 移动到 $(x-1,y)$，`R` 能让机器人从 $(x,y)$ 移动到 $(x+1,y)$。

你可以将操作符重新排序（只能改变顺序，不能改变个数），问是否存在一种方案使机器人不会踩到地雷，如果存在则输出此方案，否则输出 `Impossible`。
## 思路
我们发现同一种操作符的先后顺序变化是没有影响的，那我们可以把同种字符串都放到一起执行，例如样例中的 `RURULLD` 实际上等价于 `RRUULLD`。

而不同种操作符的先后顺序变化是有影响的，所以我们可以暴力枚举每种操作符在操作序列中的先后顺序，事实上共有 $4!=24$ 种排列方案（其实就是全排列），然后判断每种方案是否合法。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main()
{
	cin>>T;
	while(T--)
	{
		int x,y,u=0,d=0,l=0,r=0,p[5],op=0;
		string s;
		cin>>x>>y>>s;swap(x,y);
		int len=s.size();
		for(int i=0;i<len;i++)
		{
			if(s[i]=='U')
				u++;
			if(s[i]=='D')
				d++;
			if(s[i]=='L')
				l++;
			if(s[i]=='R')
				r++;
		}
		for(int i=1;i<=4;i++)
			p[i]=i;
		do
		{
			int dx=0,dy=0,flag=1;
			for(int i=1;i<=4;i++)
			{
				if(p[i]==3&&dx==x&&y>=dy-l&&y<=dy)
				{
					flag=0;
					break;
				}
				else if(p[i]==4&&dx==x&&y<=dy+r&&y>=dy) 
				{
					flag=0;
					break;
				} 
				else if(p[i]==1&&dy==y&&x>=dx&&x<=dx+u)
				{
					flag=0;
					break;
				} 
				else if(p[i]==2&&dy==y&&x>=dx-d&&x<=dx)
				{
					flag=0;
					break;
				}
					if(p[i]==1)
						dx+=u;
					if(p[i]==2)
						dx-=d;
					if(p[i]==3)
						dy-=l; 
					if(p[i]==4)
						dy+=r;
			}
			if(flag)
			{
				for(int i=1;i<=4;i++)
				{
					if(p[i]==1)
						for(int j=1;j<=u;j++)
							cout<<"U";
					if(p[i]==2)
						for(int j=1;j<=d;j++)
							cout<<"D";
					if(p[i]==3)
						for(int j=1;j<=l;j++)
							cout<<"L";
					if(p[i]==4)
						for(int j=1;j<=r;j++)
							cout<<"R";
				}
				cout<<endl;
				op=1;
				break;
			}
		}while(next_permutation(p+1,p+5));
		if(!op)
			cout<<"Impossible"<<endl;
	}
	return 0;
}
```


---

## 作者：DX3906_ourstar (赞：1)

相信大家都见过这种图吧：

![](https://cdn.luogu.com.cn/upload/image_hosting/3k0ilw7g.png)

在这张图中，黑色线段的长度之和等于红色线段的长度之和。这可以通过平移来证明：红色线段实质上就是把同一方向不同位置的黑色线段拼在了一起。

类似地，对于本题，我们可以将同类操作合到一起来解决，这并不影响正确性。

怎么合到一起呢？我们可以开一个 `map` 来记录各个操作出现的次数，然后构造新的字符串；这一个新的字符串即为各操作合在一起后的操作序列。

对于这样一个序列，我们并不关心同种操作间谁先谁后；我们要考虑的是不同操作间的先后关系。不妨使用四个 `for` 循环来枚举，这样实际上是过了一遍全排列，总的循环次数即为 $4!=24$。~~常数略大，无伤大雅。~~

对于每次枚举得到的操作序列，我们都单独实现一个 `chk` 函数，用于判断这一序列是否合法。而 `chk` 函数要做的也很简单——遍历一遍操作序列并作出相应移动，判断是否会移动到地雷上即可。

上面这堆文字可能有点抽象，看代码：

```
#include<iostream>
#include<string>
#include<map>
using namespace std;

int T;

string s;

int mx,my;

int n;
map<char,int>cnt;//cnt[c] -> 操作 c 的总数
bool vis[4];//vis[i] -> 某一操作是否已经在当前遍历的操作序列中出现过
char dict[]="UDLR";//顾名思义
string op[4];//op[i] -> 第 i 种操作合在一起后的操作序列

inline bool chk(string s){
	int x=0,y=0;
	for(int i=0;i<n;++i){
		if(x==mx&&y==my)return 0;
		if(s[i]=='U')++y;
		if(s[i]=='D')--y;
		if(s[i]=='L')--x;
		if(s[i]=='R')++x;
	}
    if(x==mx&&y==my)return 0;//结束时还要再判断一遍
	else return 1;
}

inline void work(){
	cin>>mx>>my;
	cin>>s;
	n=s.size();
	cnt.clear();
	for(int i=0;i<4;++i)vis[i]=0;
	for(int i=0;i<4;++i)op[i]="";//多测清空
	for(int i=0;i<n;++i)++cnt[s[i]];
	for(int i=0;i<4;++i){//构造 op
		for(int j=0;j<cnt[dict[i]];++j){//将 op[i] 设为 cnt[dict[i]] 个操作 i 组成的序列，其中 cnt[dict[i]] 即为操作 i 的总数
			op[i]+=dict[i];
		}
	}
	for(int a=0;a<4;++a){//枚举第一种操作
		vis[a]=1;//打标记，避免重复统计
		for(int b=0;b<4;++b){//第二种操作 
			if(vis[b])continue ;
			vis[b]=1;
			for(int c=0;c<4;++c){//同上
				if(vis[c])continue ;
				vis[c]=1;
				for(int d=0;d<4;++d){
					if(vis[d])continue ;
					s=op[a]+op[b]+op[c]+op[d];//得到的操作序列
					if(chk(s))return cout<<s<<"\n",void(); 
				}
				vis[c]=0;
			}
			vis[b]=0;
		}
		vis[a]=0;//取标记，防止影响下一轮循环
	}
	cout<<"Impossible\n";
	return ;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)work();
	return 0;
}
```

---

## 作者：StayAlone (赞：0)

思路是从队伍来的。

先把起点终点是炸弹的情况判掉。

考虑使用 `LR` 和 `UD` 互怼，使得位置回到 $(0, 0)$。显然是一定可以的，因为炸弹只能遮挡最多一个方向。

这样之后会剩下一些操作。

- 若没有剩下，直接输出；

- 若剩下了两种不同的操作，那么一定有两条不相交（除了终点和起点）的路径通往终点，那么一定有一条是不经过炸弹的。找到那一条，输出即可；

- 若剩下了一种操作，稍微有些复杂。

这种情况下，如果直接走剩下的那种操作，可能会正好被炸弹挡在路中间。因此考虑找到一对垂直方向的操作，通过微调顺序避开炸弹。画个图更好理解：

![](https://s1.ax1x.com/2023/09/10/pPcbCod.png)

终点为 $(5, 0)$，炸弹在 $(3, 0)$。若剩下一堆 `R`，直接过去会被炸；所以先向上，再向右，最后向下即可。

代码有点丑。

```cpp
int x, y, n, cnt[5], del[5];
char s[MAXN], s2[MAXN];
const string g = "UDLR";

il int get(char ch) {
	if (ch == 'U') return 0;
	if (ch == 'D') return 1;
	if (ch == 'L') return 2;
	return 3;
}

il pii find(int x, int y, char *s) {
	rep1(i, 1, n) {
		int k = get(s[i]);
		x += dx[k]; y += dy[k];
	} return mp(x, y);
}

il bool check(char *s) {
	int xn = 0, yn = 0;
	rep1(i, 1, n) {
		int k = get(s[i]);
		xn += dx[k]; yn += dy[k];
		if (mp(xn, yn) == mp(x, y)) return false;
	} return true;
}

il int assign() {
	rep1(i, 0, 3) del[i] = cnt[i];
	int t1 = min(del[0], del[1]); del[0] -= t1; del[1] -= t1;
	int t2 = min(del[2], del[3]); del[2] -= t2; del[3] -= t2;
	if (mp(0, 1) == mp(x, y)) {
		rep1(i, 1, t1) s2[i * 2 - 1] = 'D', s2[i << 1] = 'U';
	} else {
		rep1(i, 1, t1) s2[i * 2 - 1] = 'U', s2[i << 1] = 'D';
	} int now = t1 * 2;
	
	if (mp(1, 0) == mp(x, y)) {
		rep1(i, 1, t2) s2[++now] = 'L', s2[++now] = 'R';
	} else {
		rep1(i, 1, t2) s2[++now] = 'R', s2[++now] = 'L';
	} return now;
}

il char rget(int x) {
	for (auto v : g) if (get(v) == x) return v;
	return 0;
}

int main() {
	for (int T = read(); T--; ) {
		read(x, y); scanf("%s", s + 1); n = strlen(s + 1);
		rep1(i, 0, n + 5) s2[i] = 0;
		memset(cnt, 0, sizeof cnt);
		rep1(i, 1, n) ++cnt[get(s[i])];
		pii ed = find(0, 0, s);
		if (mp(x, y) == mp(0, 0) || ed == mp(x, y)) {
			puts("Impossible");
			continue;
		}
		int now = assign();
		vector <char> use;
		for (auto v : g) if (del[get(v)]) use.eb(v);
		if (use.size() == 2) {
			int idx = now;
			for (auto v : use) {
				int k = get(v);
				rep1(i, 1, del[k]) s2[++idx] = v;
			}
			if (check(s2)) {
				puts(s2 + 1);
				continue;
			} reverse(use.begin(), use.end());
			
			idx = now;
			for (auto v : use) {
				int k = get(v);
				rep1(i, 1, del[k]) s2[++idx] = v;
			} puts(s2 + 1);
		} else if (use.size() == 1) {
			char v = use[0]; int idx = now;
			int k = get(v);
			rep1(i, 1, del[k]) s2[++idx] = v;
			if (check(s2)) {
				puts(s2 + 1);
				continue;
			}
			int op = k >= 2 ? 0 : 2;
			if (cnt[op] && cnt[op + 1]) {
				--cnt[op]; --cnt[op + 1];
				idx = assign();
				s2[++idx] = rget(op);
				rep1(i, 1, del[k]) s2[++idx] = v;
				s2[++idx] = rget(op + 1);
				if (check(s2)) puts(s2 + 1);
				else puts("Impossible");
			} else puts("Impossible");
		} else puts(s2 + 1);
	}
	rout;
}
```

---

## 作者：hellolin (赞：0)


# P9626 [ICPC2020 Nanjing R] Evil Coordinate 题解

建议前往 [note.hellolin.cf](https://note.hellolin.cf/solutions/p9626/) 获得更好的阅读体验！

题目的意思是初始有个机器人站在 $(0, 0)$ 位置，给你一个 UDLR 序列，你需要把这个序列重新排序，使得机器人按照这个序列走的时候不会经过 $(m_x, m_y)$，输出排序后的序列，或报告无解。

首先我们统计出来 UDLR 的数量，统计完了这个序列就没鸟用了，我们主要考虑这些方向的数量。

``` cpp
std::cin >> tx >> ty >> s;
u = l = r = d = 0;
for(char i : s) {
    u += i == 'U';
    l += i == 'L';
    r += i == 'R';
    d += i == 'D';
}
if(u - d == ty && r - l == tx) { // 因为无论怎么排序终点都是不变的，所以这种情况可以直接判定无解
    std::cout << "Impossible\n";
    return;
}
```

之后就是爆搜，没错就是搜，不过这里有一个优化的小技巧。

``` cpp
std::string ans;
bool ok;
void dfs(int x, int y) {
    if(x == tx && y == ty) return; // 踩上了，这条路径不行
    if(x == tx) { // 如果 x 坐标和地雷的 x 坐标的一样了
        // 并且此时不能变更 x 坐标（l 和 r 已经用完）
        // 如果机器人的 y 坐标比地雷的小，且耗尽所用移动次数后又比地雷的大，那么机器人一定会经过地雷
        // 同理，如果机器人的 y 坐标大，且耗尽所有移动次数后又小，也是一定会经过地雷的
        // 可以使用异或的特性来简化代码
        if(!l && !r && (y > ty) ^ (y+u-d > ty)) return;
    }
    if(y == ty) { // 和上面的一样
        if(!u && !d && (x > tx) ^ (x+r-l > tx)) return;
    }
    if(!u && !l && !r && !d) return ok=1, void(); // 没有踩到地雷，这条路径就是可行的
    if(l) { // 如果还能向左走
        --l;
        ans.push_back('L');
        dfs(x-1, y);
        if(ok) return; // 如果路径已经合法了直接返回，不需要继续搜索
        ans.pop_back(); // 如果路径不合法就回溯
        ++l;
    }
    // 下面三个同理
    if(r) {
        --r;
        ans.push_back('R');
        dfs(x+1, y);
        if(ok) return;
        ans.pop_back();
        ++r;
    }
    if(d) {
        --d;
        ans.push_back('D');
        dfs(x, y-1);
        if(ok) return;
        ans.pop_back();
        ++d;
    }
    if(u) {
        --u;
        ans.push_back('U');
        dfs(x, y+1);
        if(ok) return;
        ans.pop_back();
        ++u;
    }
}
```

温馨提示：多测记得清空！

``` cpp
ans.clear();
ok = 0;
dfs(0, 0);
if(ok) std::cout << ans << '\n';
else std::cout << "Impossible\n";
```

---

## 作者：lraM41 (赞：0)

小清新模拟题。

很容易证明在有解的情况下至少有一条路径是沿着一个方向一直走的。如下：（ $*$ 表示地雷， $1$ 表示路径，该图表示地雷在边界、中间的情况）

```
111 11* 100
0*1 010 111
001 011 *01
```

思路：先记录每个方向要走多少次，再安排四个方向走的顺序即可（用全排列）。

主要注释在代码里。


```
#include<bits/stdc++.h> 
using namespace std;
int dx[]={-1,1,0,0},dy[]={0,0,1,-1};//上下右左四个方向（表示 LRUD ）。
int mx,my,t,x,y,a[4],nx[4];// a 记录每个方向走几次， nx 记录四方向的顺序。
string str,ans="LRUD";//输出时用。
bool f,flag;//判解。
signed main(){
   cin>>t;
   for(;t;t--){
      cin>>mx>>my>>str;
      a[0]=a[1]=a[2]=a[3]=x=y=0;// xy 表示起点、终点。
      for(int i=0;i<str.size();i++){
         if(str[i]=='L') a[0]++,x--;//按题意模拟。
         if(str[i]=='R') a[1]++,x++;
         if(str[i]=='U') a[2]++,y++;
         if(str[i]=='D') a[3]++,y--;
      }
      if((!mx&&!my)||(mx==x&&my==y)){//判无解的部分情况。
         puts("Impossible");
         continue;
      }
      for(int i=0;i<4;i++) nx[i]=i;//初始方向。
      f=0;//判断当前询问是否有解。
      do{
         x=y=flag=0;//重新模拟走的路径， flag 判当前顺序是否有解。
         for(int i=0;i<4;i++){//四方向。
            for(int j=1;j<=a[nx[i]];j++){//每个方向走到底。
               x+=dx[nx[i]],y+=dy[nx[i]];//模拟。
               if(x==mx&&y==my){//判断当前顺序不可行。
                  flag=1;break;
               }
            }
            if(flag) break;//若一个方向已经不可行了就直接退出。
         }
         if(!flag){//当前顺序有解
            f=1;
            for(int _=0;_<4;_++)
               for(int i=1;i<=a[nx[_]];i++)
                  cout<<ans[nx[_]];//四方向输出。
            puts("");break;
         }
      }while(next_permutation(nx,nx+4));//方向顺序的全排列。
      if(!f) puts("Impossible");//还是无解。
   }
   return 0; 
}

---

