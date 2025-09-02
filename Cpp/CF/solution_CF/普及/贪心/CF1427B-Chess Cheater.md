# Chess Cheater

## 题目描述

You like playing chess tournaments online.

In your last tournament you played $ n $ games. For the sake of this problem, each chess game is either won or lost (no draws). When you lose a game you get $ 0 $ points. When you win you get $ 1 $ or $ 2 $ points: if you have won also the previous game you get $ 2 $ points, otherwise you get $ 1 $ point. If you win the very first game of the tournament you get $ 1 $ point (since there is not a "previous game").

The outcomes of the $ n $ games are represented by a string $ s $ of length $ n $ : the $ i $ -th character of $ s $ is W if you have won the $ i $ -th game, while it is L if you have lost the $ i $ -th game.

After the tournament, you notice a bug on the website that allows you to change the outcome of at most $ k $ of your games (meaning that at most $ k $ times you can change some symbol L to W, or W to L). Since your only goal is to improve your chess rating, you decide to cheat and use the bug.

Compute the maximum score you can get by cheating in the optimal way.

## 说明/提示

Explanation of the first testcase. Before changing any outcome, the score is $ 2 $ . Indeed, you won the first game, so you got $ 1 $ point, and you won also the third, so you got another $ 1 $ point (and not $ 2 $ because you lost the second game).

An optimal way to cheat is to change the outcomes of the second and fourth game. Doing so, you end up winning the first four games (the string of the outcomes becomes WWWWL). Hence, the new score is $ 7=1+2+2+2 $ : $ 1 $ point for the first game and $ 2 $ points for the second, third and fourth game.

Explanation of the second testcase. Before changing any outcome, the score is $ 3 $ . Indeed, you won the fourth game, so you got $ 1 $ point, and you won also the fifth game, so you got $ 2 $ more points (since you won also the previous game).

An optimal way to cheat is to change the outcomes of the first, second, third and sixth game. Doing so, you end up winning all games (the string of the outcomes becomes WWWWWW). Hence, the new score is $ 11 = 1+2+2+2+2+2 $ : $ 1 $ point for the first game and $ 2 $ points for all the other games.

## 样例 #1

### 输入

```
8
5 2
WLWLL
6 5
LLLWWL
7 1
LWLWLWL
15 5
WWWLLLWWWLLLWWW
40 7
LLWLWLWWWLWLLWLWWWLWLLWLLWLLLLWLLWWWLWWL
1 0
L
1 1
L
6 1
WLLWLW```

### 输出

```
7
11
6
26
46
0
1
6```

# 题解

## 作者：houzhiyuan (赞：3)

算法：贪心

首先，想要得分最大，那么每次操作就必须将$L$转化为$W$。

我们记录$cnt$表示字符串中$W$的个数，那么易证操作完了之后的$W$个数就一定是$cnt+k$。

题目中又有特殊要求，在一段连续的$W$中，第一个的得分为$1$，其余为$2$，那么设操作完了之后的连续$W$的段数为$x$显然最后的得分就是$(cnt+k) \times 2-x$。

显然要使段数尽量少，那么就用贪心将$k$次操作 填充至两段$W$的空隙中，具体实现方法见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){//快读，防止TLE
	int t=0,f=0;char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
int _,a[1000001];
char ch[1000001];
int main(){
	_=read();
	while(_--){
		int tot=0;//tot表示原来连续W之间的空隙数
		int n,k,cnt=0,x=0;
		n=read();
		k=read();
		bool ff=0;//将最前面出现的L去掉
		scanf("%s",ch+1);
		for(int i=1,s=0;i<=n;i++){
			if(ch[i]=='W')ff=1,cnt++;
			if(ch[i]=='L'&&ff){
				s++;
			}
			else{
				if(s>0)a[++tot]=s,s=0;//将连续W的长度放入a中
			}
		}
		if(cnt+k>=n){//如果可以全部变W，直接输出
			cout<<2*n-1<<endl;
			continue;
		}
		sort(a+1,a+tot+1);//贪心，尽量将小的空隙填充
		int t=0;
		for(int i=1;i<=tot;i++){
			t+=a[i];
			if(t>k){//超过k，统计段数
				x=tot-i+2;//有i-1个空隙被填充，一共有tot+1段W，段数为tot+1-(i-1)=tot-i+2
				break;
			}
		}
		if(t<=k&&(cnt||k)){//如果可以填充所有空隙，且cnt与k至少有一个不是0，段数只有1
			x=1;
		}
		printf("%d\n",(cnt+k)*2-x);//用上面推出的式子
	}
}
```


---

## 作者：钓鱼王子 (赞：1)

贪心。

最优情况下我们肯定将 $L$ 变为 $W$。

首先，将所有连续的 $W$ 视为一个连通块，则我们要尽量减少连通块的个数，也就是说，我们要尽量合并原来的连通块。

将两两 $W$ 之间的距离存下来，满足尽量多的即可，可以不用管两个边界，但需要处理全部变为 $W$ 的情况。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
int n,m,t,a[1000002],b[1000002],ans,sum,cnt,lst,ll;
char s[200002];
int main(){
	t=read();
	while(t--){
		n=read(),m=read();sum=ll=ans=0;
		scanf("%s",s+1);
		for(re int i=1;i<=n;++i)sum+=(s[i]=='L'),ll|=(s[i]=='W'),ans+=(s[i]=='W');
		m=min(sum,m);ans+=max(0,(ll?m*2:m*2-1));
		cnt=lst=0;
		for(re int i=1;i<=n;++i){
			if(s[i]=='W'){
				if(lst)a[++cnt]=i-lst-1;
				lst=i;
			}
		}
		sort(a+1,a+cnt+1);
		for(re int i=1;i<=cnt;++i){
			if(m>=a[i])m-=a[i],++ans;
		}
		printf("%d\n",ans);
	}
}
```


---

## 作者：Tsz1024_AK (赞：0)

### 友情链接
- [原题链接](https://www.luogu.com.cn/problem/CF1427B)
### 理解题意
- 本题描述比较完整，但还是得注意一下，题目中的 $k$ 不是改变顺序，而是改变字符，即把 `L` 改成 `W`。
- 在看题目的同时也看看样例是一种不错的办法！
### 做题思路
- AC 本题需要以下几步：
1. 按格式输入，先输入 $T$，再用 `while(T--)` 输入本组样例的数据；
2. 先排除特殊情况：如果 $k$ 是 $0$，并且全部字符都是 `L`，那么直接输出 $0$ 并换行（先 `if(k==0)` 再用循环语句一个一个判断这个字符是不是 `L`，是的话计数器 $ans$ 累加，如果 $ans$ 等于 $n$ 那么输出 $0$ 并进入下一层循环）；
3. 如果不是特殊情况，那么把 `L` 改成 `W`，一次一次去遍历，看把哪一个改掉得分最多（尽量改掉两个 `W` 间并且间隙最小的，这样子能得到的分数越多，因为题目中说赢得一场比赛时，若上一局比赛也赢了，则这场比赛得 $2$ 分，所以可以得到更多的分数，建议简单画图，让思维更加清晰），再用 $\max()$ 函数去比较，最后得出最高分，就是这一组数据的答案了；
4. 输出最大的分数即可。
- 关于时间复杂度，需要注意以下，因为遍历的次数随着 $n$ 和 $k$ 的变大就会增大，一些地方需要稍微改动一下，能减哪里的时间复杂度就减那里的时间复杂度；
- 如果你哪里出错了，那你可以再看一遍题目，是不是理解错了的问题。
- 本题的核心部分有点难，需要仔细思考一下。
### 赠送样例
#### 输入
```cpp
4
5 2
LWWLLW
5 1
WWLLW
10 3
LLLWLWWWLL
10 2
WWLWLLLWLL
```
#### 输出
```cpp
7
6
13
10
```
### 示例代码
详见你的脑袋瓜中——

因为，你的大脑就像一台计算机一样，可以把思路转换成代码，交换来你 AC 的欢乐！

也因为——

- 成功是自己得来的才有用~
- 越是漆黑的路，越要你自己走~
#### 最后，愿——你能 AC 本题！

---

## 作者：Nygglatho (赞：0)

定义一个“段”表示输入的字符串中的一个子串，且这个子串是 $\tt WLL\dots LLW$ 形式。

显然，把 $\tt W$ 改为 $\tt L$ **一定不优**。

发现一些性质：
- 将 $\tt \dots WLL\dots$ 变成 $\tt\dots WWL\dots$ 会增加两分。
- 将 $\tt \dots LLW\dots$ 变成 $\tt\dots LWW\dots$ 会增加两分。
- 将 $\tt \dots WLW\dots$ 变成 $\tt \dots WWW\dots$ 会增加三分。

为了使分数尽可能高，贪心的想，需要让增加三分的次数尽可能多，在此之下，让增加两分的次数尽可能多。

由于我们不知道需要多少次才能用完这 $k$ 次机会，所以显然应该让增加三分的操作尽量放在前面，也就是前面修改的段的长度 **越短越好**。在此基础上，需要尽可能多地进行增加两分的操作，即尽量把刚好在 $\tt W$ 后面的 $\tt L$ 改为 $\tt W$。

举个例子：原串为 $\tt WWLLLLWLLLW$，$k = 5$。

| 操作次数 | 此时的字符串 | 分数 |
| :----------: | :----------: | :----------: |
| $0$ | $\tt WWLLLLWLLLW$ | $5$ |
| $1$ | $\tt WWLLLLW\color{blue}W\color {black}LLW$ | $7$ |
| $2$ | $\tt WWLLLLW\color{blue}WW\color {black}LW$ | $9$ |
| $3$ | $\tt WWLLLLW\color{blue}WWW\color {black}W$ | $12$ |
| $4$ | $\tt WW\color{blue}W\color{black}LLLW\color{blue}WWW\color {black}W$ | $14$ |
| $5$ | $\tt WW\color{blue}WW\color{black}LLW\color{blue}WWW\color {black}W$ | $16$ |

如果修改完了，但是修改的次数没有到 $k$，那么此时的字符串就是这样的形式：$\tt LL\dots LLWW\dots WWLL\dots LL$。

发现将 $\tt W$ 前面的 $\tt L$ 改成 $\tt W$，或者将 $\tt W$ 后面的 $\tt L$ 改成 $\tt W$ 都会增加两分。那么我们就可以尽可能多地使用这种操作，直到没有 $\tt L$ 或者修改的次数到 $k$。

```c
#include "bits/stdc++.h"
// #pragma GCC optimize(3, "Ofast", "inline")
using namespace std;

int Q, n, k, cnt, W, L, ans;
string s;

struct g {
	int l, r, p;
}t[114514];

int f[114514];

bool cmp(g x, g y) {
	return x.p < y.p;
}

int main() {
//	freopen ("game.in", "r", stdin);
//	freopen ("game.out", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> Q;
	while (Q--) {
		cin >> n >> k >> s;
		cnt = ans = 0;
		W = L = 0;//变量 W 表示 'W' 的数量，L 表示 'L' 的数量
		for (int i = 0; i < n; ++i) {
			if (s[i] == 'W') {
				f[++cnt] = i;
				++W;
				if (s[i - 1] == 'W') ans += 2;
				else ++ans;//先算出初始分数
			} else {
				++L;
			}
		}
		if (cnt == 0) {
			cout << max(2 * min(n, k) - 1, 0) << '\n';//特判全是 L 的情况
			continue;
		}
		for (int i = 2; i <= cnt; ++i) {
			t[i - 1].l = f[i - 1] + 1; t[i - 1].r = f[i] - 1; t[i - 1].p = f[i] - f[i - 1] - 1;//存储每一段
		}
		sort(t + 1, t + cnt, cmp);//排序，使修改的段长度越小越好
		for (int i = 1; i < cnt; ++i) {
			bool flg = 1;
			if (t[i].p == 0) continue;
			for (int j = t[i].l; j <= t[i].r; ++j) {
				if (k == 0 || L == 0) {
					flg = 0; break;
				}
				--L; ++W; --k; 
				ans += 2;
			}
			if (flg == 1) ++ans;//额外增加 1 分（相当于加 3 分）
			else break;
		} 
		while (k > 0 && L > 0) {
			--k, --L, ans += 2;
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：7KByte (赞：0)

我们先求出初始串的答案。

现在我们要将一些$L$修改成$W$，如果我们修改的位置与$W$相邻，则可以额外加一个贡献，如果两边同时相邻，则可以加两个贡献。

这样我们可以把问题转换一下。若干个$W$把序列分成若干个连续的$L$段。每修改一个，可以增加两个贡献，如果一段被选完了，可以额外增加一个贡献。

所以我们将这些段按大小排序，优先把短的段处理完。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,k;char s[N];
vector<int>c;
void solve(){
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	int sum=0,ans=0;
	rep(i,1,n){
		sum+=s[i]=='L';
		ans+=s[i]=='W';
		ans+=(s[i]=='W'&&s[i-1]=='W');
	}
	k=min(k,sum);
	if(k==sum){printf("%d\n",n*2-1);return ;}
	c.clear();int pre=0;
	rep(i,2,n-1){
		if(s[i]=='L'&&s[i-1]=='W')pre=i;
		if(s[i]=='L'&&s[i+1]=='W'&&pre)c.push_back(i-pre+1);
	}
	sort(c.begin(),c.end());
	for(int i=0;i<(int)c.size();i++){
		if(c[i]<=k){
			k-=c[i];ans+=c[i]*2+1;
		}
		else{
			ans+=k*2;k=0;
		}
	}
	if(sum==n&&k)printf("%d\n",ans+k*2-1);
	else printf("%d\n",ans+k*2);
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
/*
g++ now.cpp -o now -Wall -std=c++11
*/
```

---

## 作者：icefake (赞：0)

## 关于翻译
你一共进行了 $n$ 场比赛，输赢的结果用一串字符表示，$W$ 表示胜，$L$ 表示败。

每获胜一场可以加一点，连胜额外增加一点，失败则增加零点。

现在该比赛出现了漏洞，你可以通过该漏洞对你的比赛结果进行修改，最多修改 $k$ 次。

需要你求出你最终最多可以获得的点数并输出它。

## 关于做法

每次输入一串只含 $W$ 和 $L$ 的字符串，因为失败并不能增加点数，所以我们一定是把 $L$ 修改为 $W$，这样才能使点数最大。

而我们又发现，如果把一个 $W$ 后面的 $L$ 修改成 $W$，那么总点数将会增加 $2$，而如果这个 $L$ 后面还有一个 $W$ 的话，总点数就会额外增加 $1$。

因此，我们可以得到做法：找出字符串中所有的 $L$ 的连续长度，并用一个数组储存，将其长度进行排序，从小到大累加，直到大于 $k$ 为止，记录增加的点数，加上原来的点数得出答案。

程序中在稍微注意一点**细节**

比如：包含第一场和最后一场的连续 $L$ 串不进入排序。

还有一些**小优化**

若该 $L$ 串长度为 $1$ 直接 ```k --``` 并 ```cnt += 3```

---

