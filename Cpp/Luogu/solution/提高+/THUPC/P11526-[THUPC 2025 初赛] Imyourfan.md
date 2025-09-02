# [THUPC 2025 初赛] Imyourfan

## 题目描述

W 老师正在和他的粉丝 Menji 玩一个游戏。

桌上有 $n$ 张卡片，编号为 $1\sim n$，每张卡片有一个字母 $s_i$，其中 $s_i$ 为 $\texttt{X},\texttt{W},\texttt{M}$ 中的一个，且保证至少存在一个 $\texttt{W}$ 和至少一个 $\texttt{M}$。

W 老师和 Menji 轮流操作，W 老师先手，当轮到一名玩家操作时，他会选择一个区间 $[l,r](1\leq l\leq r\leq n)$，满足区间中不存在写有字母 $\texttt{X}$ 的卡片，然后拿走区间内所有卡片。

若在某次操作过后，所有的 $\texttt{W},\texttt{M}$ 卡片都已经被拿走，那么游戏平局，否则若某次操作后所有的 $\texttt{W}$ 都被拿走，那么 W 老师获胜，如果某次操作后所有的 $\texttt{M}$ 都被拿走，那么 Menji 获胜。

W 老师和 Menji 都是绝顶聪明的，现在给定所有的 $s_1\dots s_n$，请判断游戏的结果，若 W 老师获胜则输出 `Water`，如果 Menji 获胜则输出 `Menji`，如果平局则输出 `Draw`。

## 说明/提示

- 对于第一组数据，若 W 老师直接拿走所有的卡片，那么游戏是平局，否则 W 老师无法同时拿走两张写有 $\texttt{W}$ 的卡片，Menji 可以此时拿走写有 $\texttt{M}$ 的卡片并获胜。所以 W 老师一定会拿走所有卡片，游戏结果为平局。

- 对于第二组数据，W 老师直接拿走 $\texttt{W}$ 即可获胜。


#### 题目来源

来自 2025 清华大学学生程序设计竞赛暨高校邀请赛（THUPC2025）初赛。

题解等资源可在 <https://gitlink.org.cn/thusaa/thupc2025pre/tree/master> 查看。

## 样例 #1

### 输入

```
6
WMW
MWM
WMWXMWM
WWWXMMMXWWW
MMMXWWWXMMM
WMWMWMWWMWW```

### 输出

```
Draw
Water
Draw
Menji
Water
Draw```

# 题解

## 作者：fish_love_cat (赞：6)

好久没有这么酣畅淋漓的分讨过了。依我看这坨仍是史中史。

![](https://cdn.luogu.com.cn/upload/image_hosting/xr2hm8w0.png)

上一次抑郁成这样还是[这个](https://www.luogu.com.cn/article/ujc3qvgx)。

错的点主要是细节不到位和复制导致的输出写错。

我的锅，我对不起队伍。

~~但咱就是说这什么运气一开赛就开这题创似了呢……~~

---

首先可以把 $\texttt{X}$ 视作分割线，将原字符串砍成若干段不含 $\texttt{X}$ 的字符串。

注意到卡片是一段一段取走的，所以对于一段连续的 $\texttt{M\dots M}$ 或 $\texttt{W\dots W}$ 可以直接压缩成为等价的 $\texttt{M}$ 或 $\texttt{W}$。

对于处理后的字符串，我们发现两人轮流对其进行操作一个回合后，固定会消除一对 $\texttt{MW}$ 或者 $\texttt{WM}$。

据此我们可以进一步转化：

+ 形如 $\texttt{MMM\dots M}$ 的字符串，进行一定消除后会变成 $\texttt{M}$。

+ 形如 $\texttt{WWW\dots W}$ 的字符串，进行一定消除后会变成 $\texttt{W}$。

+ 形如 $\texttt{MWM\dots W}$ 的字符串，进行一定消除后会变成 $\texttt{MW}$。

+ 形如 $\texttt{WMW\dots M}$ 的字符串，进行一定消除后会变成 $\texttt{WM}$。

+ 形如 $\texttt{MWM\dots WM}$ 的字符串，进行一定消除后会变成 $\texttt{MWM}$。

+ 形如 $\texttt{WMW\dots MW}$ 的字符串，进行一定消除后会变成 $\texttt{WMW}$。

然后分别统计六种字符串的数量，记为 $a_0,a_1,a_2,a_3,a_4,a_5$。

具体做法：

```cpp
	for(int i=1;i<s.size();i++){
		if(s[i]=='X'){
			if(x.size()==0)continue;
			if(x[0]==x[x.size()-1]){
				if(x[0]=='M'&&x.size()==1)a[0]++;
				else if(x[0]=='M')a[4]++;
				else if(x.size()!=1)a[5]++;
				else a[1]++;
			}else{
				if(x[0]=='M')a[2]++;
				else a[3]++;
			}
			x="";
		}else if(s[i]!=s[i-1])x+=s[i];
	}
```

---

我们还要明确一下这些值的意义。

+ $a_0,a_1$ 显然要优先消除，因为是纯粹的自己人，消除起来放心。这两者可以先互相消耗掉，对结果没什么影响。

```cpp
	int flc=min(a[0],a[1]);
	a[0]-=flc;
	a[1]-=flc;
```

我们令 $a_0,a_1$ 重新赋值为处理后的结果。

+ $a_2,a_3$ 没有意义，显然可以在不变先后手的情况下轮流消除。

+ $a_4,a_5$ 有的时候可以连着一起爆了，让对手讨不到好闹个平局。这就是为什么要分讨统计这两个值的原因。

那么接下来我们可以开始分讨了。

---

+ 当 $a_0\ne0$ 时：
+ + 当 $a_5<a_0+a_4$ 时，W 老师可以挖掉 $a_4$ 中间的 $\texttt{W}$，增加 $a_0$ 数量与 Menji 对耗，此时 Menji 最优解显然是消 $a_0$，所以最后局面会变成只剩余 $a_0,a_5$。由原式得 $a_5<a_0$，此时 W 老师不顾对方棋子硬吃 $a_5$ 都能赢。答案为 `Water`。
  + 当 $a_5=a_0+a_4$ 时：
  + + 当 $a_4=0$ 时，原式可转化为 $a_5=a_0$，此时 W 老师先手，赢。答案仍为 `Water`。
    + 当 $a_4=1$ 时，原式可转化为 $a_5-1=a_0$，当 $a_0$ 消完后，会残留有 $1$ 个 $a_5$。虽然仍为 W 老师先手，但此时只要 Menji 单取中间就赢了，W 老师被迫选择全吃平局。答案为 `Draw`。
    + 当 $a_4>1$ 时，原式可转化为 $a_5>a_0+1$：
    + + 若仍旧按照上述方案实施，等到 $a_0$ 消完后仍会残留有大量 $a_5$。此时虽仍为 W 老师先手，但只要 Menji 出手，W 老师立马被动，结局必输，而此时连平局的选择都没有。
      + 所以 W 老师要用新方案，不管 $a_4$ 直接从头到尾将 $a_5$ 整个拿掉。此时 Menji 显然还是会优先消 $a_0$。对于剩下的 $a_4$，如果分开拿 $\texttt{M}$，W 老师消完 $a_5$ 若反将一军陷入被动的将会是 Menji。所以 Menji 也会整个拿。最后会刚好留下 $1$ 个 $a_4$，此时 Menji 先手，最优解是全拿平局。答案为 `Draw`。
  + 当 $a_5=a_0+a_4+1$ 时，一样不理 $a_4$，拿 $a_5$ 直接爆，与上一段区别在于现在最后会留下的是 $a_5$，而先手是 W 老师。最优解一样是全拿。答案为 `Draw`。
  + 当 $a_5>a_0+a_4+1$ 时，无论怎样，最后一定会出现如下局面：只剩下了若干 $a_5$，先手 Menji。W 老师显然是被压着打的死局。答案 `Menji`。
+ 当 $a_1\ne 0$ 时，我们可以先将 $a_1$ **自减**，然后先后手互换。也就是说我们完全可以将 Menji 和 W 老师互换身份了。那么关于答案的处理显然也是基本一致。然后我们继续分类讨论：
+ + 当 $a_1\ne 0$ 时，处理同上文 $a_0\ne 0$。注意互换身份，判断条件中先后手的相关数值也要记得更替。
  + 当 $a_0=a_1=0$ 时，处理同下文 $a_0=a_1=0$。修改注意点同上。~~真的不是懒而是控制题解篇幅（）~~
+ 当 $a_0=a_1=0$ 时：
+ + 当 $a_4=a_5=0$ 时，那说明要么此时还剩了 $a_2$ 或 $a_3$，要么就是前面第一轮纯种互爆清干净了。不管怎么样，肯定是后手来不及，顺出局先手必定领先一步。答案 `Water`。
  + 当 $a_4>a_5$ 时，W 老师清完 $a_5$ 后轮到她先手时一定还有 $a_4$ 剩余，此时就可以把 Menji 压着打了。答案仍为 `Water`。
  + 当 $a_4=a_5$ 时，W 老师清完以后，剩 Menji 和一个 $a_4$，Menji 一口闷，平。答案 `Draw`。
  + 当 $a_4+1=a_5$ 时，Menji 清空 $a_4$ 后，剩的变成了 W 老师和她的一只 $a_5$。W 老师也只好一口闷，也是平。答案又是 `Draw`。
  + 当 $a_4+1<a_5$ 时，Menji 清空后，看着 W 老师和一群 $a_5$。W 老师在吃掉一个 $a_5$ 后，还剩有一堆 $a_5$，陷入大被动成功被压着打了。答案 `Menji`。

分讨完成！

---

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
	string s;
	cin>>s;
	string x;
	x+=s[0];
	s+='X';
	if(x=="X")x="";
	int top=0;
	int a[6]={};//M W MW WM MWM WMW 
	for(int i=1;i<s.size();i++){
		if(s[i]=='X'){
			if(x.size()==0)continue;
			if(x[0]==x[x.size()-1]){
				if(x[0]=='M'&&x.size()==1)a[0]++;
				else if(x[0]=='M')a[4]++;
				else if(x.size()!=1)a[5]++;
				else a[1]++;
			}else{
				if(x[0]=='M')a[2]++;
				else a[3]++;
			}
			x="";
		}else if(s[i]!=s[i-1])x+=s[i];
	}
//	cout<<a[0]<<' '<<a[1]<<' '<<a[2]<<' '<<a[3]<<' '<<a[4]<<' '<<a[5]<<'\n';
	int flc=min(a[0],a[1]);
	a[0]-=flc;
	a[1]-=flc;
	if(a[0]){
		if(a[5]<a[0]+a[4]||a[5]==a[0]+a[4]&&a[4]==0){
			puts("Water");
			return;
		}else if(a[5]==a[0]+a[4]+1||a[5]==a[0]+a[4]){
			puts("Draw");
			return;
		}else{
			puts("Menji");
			return;
		}
	}else if(a[1]){
		a[1]--;
		if(a[1]){
			if(a[4]<a[1]+a[5]||a[4]==a[1]+a[5]&&a[5]==0){
				puts("Menji");
			return;
			}else if(a[4]==a[1]+a[5]+1||a[4]==a[1]+a[5]){
				puts("Draw");
			return;
			}else{
				puts("Water");
			return;
			}
		}else{
			if(!a[4]&&!a[5]){
				puts("Menji");
			return;
			}else if(a[4]<a[5]){
				puts("Menji");
			return;
			}else if(a[4]==a[5]+1||a[4]==a[5]){
				puts("Draw");
			return;
			}else{
				puts("Water");
			return;
			}
		}
	}else{
		if(!a[4]&&!a[5]){
			puts("Water");
			return;
		}else if(a[4]>a[5]){
			puts("Water");
			return;
		}else if(a[4]+1==a[5]||a[4]==a[5]){
			puts("Draw");
			return;
		}else{
			puts("Menji");
			return;
		}
	}
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
//WXWXMMWMXMWMXMWWMMX
```

疑似全世界最繁琐的做法。

---

[循](https://www.luogu.com.cn/record/200367619) [序](https://www.luogu.com.cn/record/200372491) [渐](https://www.luogu.com.cn/record/200431350) [进](https://www.luogu.com.cn/record/200458133)。

诶话说为什么总觉得 $a_5$ 被我写的跟只鸡一样（）

---

## 作者：Mr_Az (赞：3)

# [P11526 [THUPC 2025 初赛] Imyourfan](https://www.luogu.com.cn/problem/P11526)

### Algorithm:

分类讨论。

### Solution:

首先我们会发现 $X$ 会把这个字符串分割成若干段，同时我们手玩后还发现每段字符串可以被抽象为以下类型的字符串：

1. `m` 只有 $m$ 的字符串。
2. `w` 只有 $w$ 的字符串。
3. `wm` 开头结尾分别为 $w$ 和 $m$（顺序不重要）。
4. `wmw` 开头结尾为 $w$，中间出现了 $m$。
5. `mwm` 开头结尾为 $m$，中间出现了 $w$。

这时候就可以贪心选择了，此处只讲 `Water` 的选择优先级：

1. 有 `w` 的话就消掉，因为没有影响。
2. 有 `wm` 的话就消掉，变为 $1$ 个 `m`。
3. 有 `wmw` 的话就消掉。
4. 有 `mwm` 的话就消掉，变为 $1$ 个 `m`。

`Menji` 同理。对于 $3,4$ 的分讨，给一个 hack：

输入：`WMWXMWMMXWXMWWM`。

输出：`Draw`。

原因是留着对方夹着自己的，对方要消掉就必须把自己消掉，可能可以达成 `Draw`，但是我们如果交换 $3,4$ 则有可能自己留下一个 `wmw -> w` 导致对方胜利。平局的优先级显然大于失败。

直接模拟就行，最差的时间复杂度也只有 $\text{O}(\sum |S|)$。原因是一次操作至少删除掉一个字符。

### Code:（分段的代码可能有点丑，但是贪心的部分很清晰）

```cpp
namespace Mr_Az{
	int T;
	string s;
	int m,w,wm,mwm,wmw;
	inline bool check(){
		if(!m&&!wm&&!wmw&&!mwm){
			if(!w){puts("Draw");return 1;}
			else{puts("Menji");return 1;}
		}
		else if(!w&&!wm&&!wmw&&!mwm){puts("Water");return 1;}
		return 0;
	}
	inline void solve(){
		cin>>s;s+='X';
		m=w=wm=mwm=wmw=0;
		char ch;
		bool f1=0,f2=0;
		for(rint i=0,j=0;i<s.size();i++){
			if(s[i]=='X') continue;
			f1=f2=0;ch=s[i];j=i+1;
			while(j<s.size()&&s[j]!='X'&&s[j+1]!='X'){
				if(s[j]=='W') f1=1;
				if(s[j]=='M') f2=1;
				j++;
			}
			if(s[j]=='X') j--;
			if(s[i]=='W'){
				if(s[j]=='W') f2?wmw++:w++;
				else wm++;
			}
			else{
				if(s[j]=='M') f1?mwm++:m++;
				else wm++;
			}
			i=j+1;
		}
		while(1){
			if(w) w--;
			else if(wm) wm--,m++;
			else if(wmw) wmw--;
			else if(mwm) mwm--,m++;
			
			if(check()) break;
			
			if(m) m--;
			else if(wm) wm--,w++;
			else if(mwm) mwm--;
			else if(wmw) wmw--,w++;
			
			if(check()) break;
		}
	}
	inline void mian(){if(!T) read(T);while(T--) solve();}
}
```

---

## 作者：ELECTRODE_kaf (赞：3)

首先解析字符串，以 `X` 为分隔符分离出所有子串。

将分离出的子串分为几类：`W`，`M`，`WMW`，和 `MWM`，分别代表全 `W`，全 `M`，开头结尾均为 `W`，和开头结尾均为 `M`。记它们的个数为 $w$，$m$，$wmw$，和 $mwm$。其实还有开头结尾不同的情况，但是注意到对于这种子串，双方的最佳决策一定是一人取一次，所以可以转化为一个 `W` 和一个 `M`。

四种显然的情况：

- 若只有 `W` 和 `M`：一人取一个，若 $w\le m$ 则先手胜，否则后手胜。
- 若只有 `WMW` 和 `MWM`：同样一人取一个，显然应该取以自己的字母为头尾的子串（取对方的则一人一步还帮对方完成一个）。所以 $wmw<mwm$ 则先手胜，$wmw>mwm+1$ 则后手胜，否则平局（因为谁取最后一个都是双方的字母同时被取完）。
- 若 $w+wmw<m+mwm$：经过前面的分析，我们知道，先手的决策应该是先取 `W`，再取 `WMW`，还剩 `MWM` 则取中间部分（可见若进行到这一步则先手必胜，所以我们可以认为先手只要取完 `W` 和 `WMW` 即可获胜）。此时先手必胜。
- 若 $w+wmw>m+mwm+1$：同理，后手必胜。

对于其余情况，首先双方会取走 `W` 和 `M` 直到其一被取完。又前文分讨可知此时 $w+wmw=m+mwm$ 或 $w+wmw=m+mwm+1$。

- 若 $w+wmw=m+mwm$：此时平局，但有一个特例：若 $mwm=0$，则最后剩下的是 `M`，先手胜。
- 若 $w+wmw=m+mwm+1$：同理，此时平局，但有一个特例：若 $wmw=0$，则最后剩下的是 `W`，后手胜。注意特判 $w+wmw=1$，此时若剩下 `W` 则后手胜，若剩下 `WMW` 则平局。

```cpp
ll Q,n,w,m,wmw,mwm;
string s;

int main() {
	cin>>Q;

	count(Q) {
		cin>>s;
		n=s.size();
		s.pb('X');
		w=m=wmw=mwm=0;
		ll cntw=0,cntm=0;

		rep(i,0,n) {
			if(s[i]=='X') {
				if(cntw+cntm==0) ctn;

				if(cntm==0) w++;
				elif(cntw==0) m++;
				elif(s[i-1]=='W' and s[i-cntm-cntw]=='W') wmw++;
				elif(s[i-1]=='M' and s[i-cntm-cntw]=='M') mwm++;
				else {
					w++;
					m++;
				}

				cntw=cntm=0;
			} else {
				if(s[i]=='W') cntw++;
				else cntm++;
			}
		}

//		cout<<"w="<<w<<",m="<<m<<'\n';
//		pause;
		srt ans;

		if(wmw+mwm==0) {
			if(w<=m) ans=1;
			else ans=0;
		}
		elif(w+m==0) {
			if(wmw<mwm) ans=1;
			elif(wmw>mwm+1) ans=0;
			else ans=2;
		}
		elif(w+wmw<m+mwm) ans=1;
		elif(w+wmw>m+mwm+1) ans=0;
		else {
			ll tmp=min(w,m);
			w-=tmp;
			m-=tmp;

			if(w+wmw==m+mwm){
				if(mwm==0) ans=1;
				else ans=2;
			}elif(w+wmw==1){
				if(wmw==0) ans=0;
				else ans=2;
			}else{
				if(w) w--;
				else wmw--;
				
				if(wmw==0) ans=0;
				else ans=2;
			}
		}
		
		if(ans==1) cout<<"Water";
		elif(ans==0) cout<<"Menji";
		else cout<<"Draw";
		
		endl;
	}
}
/*
3
WWWXMMMXWWW
WMWXMWMXWMWWWXM
XXWMWXMW
ans:
Menji
Draw
Draw
*/
```

写分讨有点小累，确定不点个赞再走么。

---

## 作者：ty_mxzhn (赞：1)

没做出来！愤怒！愤怒！愤怒！

发现 X 相当于把原序列分成了若干个部分，但是我们这是非对称博弈所以不能 SG。

我们其实可以注意到最后每一个部分的种类其实不多。具体的来说有以下几种。

+ W 型。W 可以一步拿走，M 拿了没啥用。M 型同理。
+ WM 型。W 可以拿走自己的留下 M 的，M 当然也可以。
+ WMW 型。W 如果想拿走自己的，必须带上 M。但是 M 可以拿走自己的留下 W 的。MWM 型同理。

如果你想用分讨维护博弈的过程，那你就输了。因为实际上这些类型的区间其实可以模拟博弈。

首先 WM 型可以拆成 W 型和 M 型。这样子只有四种物品，W 型，M 型，WMW 型，MWM 型。

W 和 M 显然首先要尽量拿 W 型和 M 型。等到自己的拿完以后再考虑当前的情况。

假设 W 已经拿完 W 型了，那么他肯定先去拿 MWM 型。然后再去拿 WMW 型。

模拟即可。

---

## 作者：ztlh (赞：1)

## Solution

对所有串分类：

- 全为 $\texttt{W}$，记为 $\texttt{W}$；
- 全为 $\texttt{M}$，记为 $\texttt{M}$；
- 有 $\texttt{W}$ 和 $\texttt{M}$ 且开头结尾均为 $\texttt{W}$，记为 $\texttt{WMW}$；
- 有 $\texttt{W}$ 和 $\texttt{M}$ 且开头结尾均为 $\texttt{M}$，记为 $\texttt{MWM}$；
- 有 $\texttt{W}$ 和 $\texttt{M}$ 且开头结尾一端为 $\texttt{W}$ 一端为 $\texttt{M}$，记为 $\texttt{WM}$。

对于双方而言，最优策略的核心思想一定是让自己的操作次数尽量少，同时最大化对方的操作次数，于是上面五条中原串和缩减串等价。注意到 $\texttt{WM}$ 一定是 Water 和 Menji 各取一次，可将其拆为一个 $\texttt{W}$ 和一个 $\texttt{M}$。

考虑其中一人的策略（例如 Water）。每次操作中他有三种取法：

- 取走一个 $\texttt{W}$。由于该串中不含 $\texttt{M}$，该操作对 Menji 的操作次数无影响。
- 取走一个 $\texttt{WMW}$。由于该串中间含有 $\texttt{M}$，若让 Menji 先取则会使其操作次数增加。
- 取走一个 $\texttt{WMW}$ 中的某个 $\texttt{W}$，显然不优。
- 取走一个 $\texttt{MWM}$ 中间的 $\texttt{W}$。由于 Menji 取走整个串时能顺带取走这个 $\texttt{W}$，让 Menji 先取会更优。

综上，Water 一定会优先取 $\texttt{W}$。Menji 同理。所以我们可以先让 $\texttt{W}$ 和 $\texttt{M}$ 的个数均减去两者较小值。

定义 $\texttt{W}$ 和 $\texttt{WMW}$ 为**属于 Water 的串**，其余两类为**属于 Menji 的串**。

易见两人均会优先取属于自己的串。定义每个**回合**为两人（先后）各取走一个属于自己的串。

若干个回合后，属于两人的串数均等于 $1$ 或某人已取完自己的串时，我们来分析一下策略是否会有所不同：

- 若此时 Water 已取完自己的串，Menji 剩大于等于 $1$ 串。若游戏仍未结束，必然还存在 $\texttt{MWM}$ 串。此时 Water 先手，每个 $\texttt{MWM}$ 串中必然是 $\texttt{W}$ 先于 $\texttt{M}$ 被取完或同时被取完，Water 必胜。
- 若此时 Menji 已取完自己的串，Water 剩大于等于 $2$ 串。Water 先手取走一个属于自己的串后情况类似于上一类（相当于两人先后手转换），Menji 必胜。
- 若两人各剩 $1$ 串：
  
1. 若 Menji 剩下的是 $\texttt{M}$ 串（即 $\texttt{MWM}$ 串从一开始就不存在），Water 取走自己的串即胜。
2. 若 Menji 剩下的是 $\texttt{MWM}$ 串，Water 一定会优先取走自己的串，Menji 只能将自己的串整个取走以求平局。

- 若此时 Menji 已取完自己的串，Water 恰剩 $1$ 串：

1. 若该串是 $\texttt{W}$ 则 Menji 已胜。
2. 若该串是 $\texttt{WMW}$ 则 Water 只能整个取走得到平局。

到这里我们的分讨就结束了。

PS：为避免细节错误，我在最前面加了两类特判：

- 无 $\texttt{WMW}$ 和 $\texttt{MWM}$ 串
- 无 $\texttt{W}$ 和 $\texttt{M}$ 串，

做法均平凡，分讨即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
char s[100005];
int cm,cw;
int cnt[15];
int main(){
	scanf("%d",&T);
	while(T--){
		for(int i=1;i<=n+1;i++) s[i]='\0';
		scanf("%s",s+1);
		n=strlen(s+1);
		for(int i=1;i<=6;i++) cnt[i]=0;
		cm=cw=0; s[n+1]='X';
		for(int i=1;i<=n+1;i++){
			if(s[i]=='X'){
				if(!cw&&!cm) continue;
				if(!cm) cnt[1]++;
				else if(!cw) cnt[2]++;
				else if(s[i-1]=='W'&&s[i-cw-cm]=='W') cnt[3]++;
				else if(s[i-1]=='M'&&s[i-cw-cm]=='M') cnt[4]++;
				else cnt[1]++,cnt[2]++;
				cw=cm=0;
			}
			else{
				if(s[i]=='W') cw++;
				else cm++;
			}
		}
		if(!cnt[3]&&!cnt[4]){
			if(cnt[1]<=cnt[2]) printf("Water\n");
			else printf("Menji\n");
			continue;
		}
		if(!cnt[1]&&!cnt[2]){
			if(cnt[3]<cnt[4]) printf("Water\n");
			else if(cnt[3]==cnt[4]||cnt[3]==cnt[4]+1) printf("Draw\n");
			else printf("Menji\n");
			continue;
		}
		if(cnt[1]>=cnt[2]){
			cnt[1]-=cnt[2];
			cnt[2]=0;
		}
		else{
			cnt[2]-=cnt[1];
			cnt[1]=0;
		}
		if(cnt[1]+cnt[3]<cnt[2]+cnt[4]){
			printf("Water\n");
			continue;
		}
		if(cnt[1]+cnt[3]>cnt[2]+cnt[4]+1){
			printf("Menji\n");
			continue;
		}
		if(cnt[1]+cnt[3]==cnt[2]+cnt[4]){
			if(cnt[2]&&!cnt[4]) printf("Water\n");
			else printf("Draw\n");
			continue;
		}
		else{
			if(cnt[1]) cnt[1]--;
			else cnt[3]--;
			if(cnt[1]&&!cnt[3]) printf("Menji\n");
			else printf("Draw\n");
			continue;
		}
	}
	return 0;
}
```

---

