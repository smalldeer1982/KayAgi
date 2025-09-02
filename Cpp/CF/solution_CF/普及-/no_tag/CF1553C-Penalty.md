# Penalty

## 题目描述

Consider a simplified penalty phase at the end of a football match.

A penalty phase consists of at most $ 10 $ kicks, the first team takes the first kick, the second team takes the second kick, then the first team takes the third kick, and so on. The team that scores more goals wins; if both teams score the same number of goals, the game results in a tie (note that it goes against the usual football rules). The penalty phase is stopped if one team has scored more goals than the other team could reach with all of its remaining kicks. For example, if after the $ 7 $ -th kick the first team has scored $ 1 $ goal, and the second team has scored $ 3 $ goals, the penalty phase ends — the first team cannot reach $ 3 $ goals.

You know which player will be taking each kick, so you have your predictions for each of the $ 10 $ kicks. These predictions are represented by a string $ s $ consisting of $ 10 $ characters. Each character can either be 1, 0, or ?. This string represents your predictions in the following way:

- if $ s_i $ is 1, then the $ i $ -th kick will definitely score a goal;
- if $ s_i $ is 0, then the $ i $ -th kick definitely won't score a goal;
- if $ s_i $ is ?, then the $ i $ -th kick could go either way.

Based on your predictions, you have to calculate the minimum possible number of kicks there can be in the penalty phase (that means, the earliest moment when the penalty phase is stopped, considering all possible ways it could go). Note that the referee doesn't take into account any predictions when deciding to stop the penalty phase — you may know that some kick will/won't be scored, but the referee doesn't.

## 说明/提示

Consider the example test:

In the first test case, consider the situation when the $ 1 $ -st, $ 5 $ -th and $ 7 $ -th kicks score goals, and kicks $ 2 $ , $ 3 $ , $ 4 $ and $ 6 $ are unsuccessful. Then the current number of goals for the first team is $ 3 $ , for the second team is $ 0 $ , and the referee sees that the second team can score at most $ 2 $ goals in the remaining kicks. So the penalty phase can be stopped after the $ 7 $ -th kick.

In the second test case, the penalty phase won't be stopped until all $ 10 $ kicks are finished.

In the third test case, if the first team doesn't score any of its three first kicks and the second team scores all of its three first kicks, then after the $ 6 $ -th kick, the first team has scored $ 0 $ goals and the second team has scored $ 3 $ goals, and the referee sees that the first team can score at most $ 2 $ goals in the remaining kicks. So, the penalty phase can be stopped after the $ 6 $ -th kick.

In the fourth test case, even though you can predict the whole penalty phase, the referee understands that the phase should be ended only after the $ 9 $ -th kick.

## 样例 #1

### 输入

```
4
1?0???1001
1111111111
??????????
0100000000```

### 输出

```
7
10
6
9```

# 题解

## 作者：精神小伙！ (赞：3)

[题面](https://www.luogu.com.cn/problem/CF1553C)

## 题意

给定一个字符串 $s$。对于 $i$，如果 $i$ 为奇数，则属于队伍 $1$，否则属于队伍 $2$。

对于 $s_i$，如果 $s_i$ 是 ```1```，那么这一局得分；如果 $s_i$ 是 ```0```，那么这一局不得分。如果 $s_i$ 是 ```?```，那么两种都有可能。

现在你可以决定 ```?``` 的得分，求最少需要几轮结束比赛。

## 思路

判断每次罚球是哪支队伍得分。如果两个队伍中任意一个队伍的得分加上 ```?``` 的得分大于等于 $6$，则输出当前的轮数。

注意特判平局的情况。

## 代码

```cpp
#include<iostream>
using namespace std;
const int maxn=20;
int n;
int a,b,t;
//a 代表队伍 1 的得分，b 代表队伍 2 的得分，t 代表 ? 的得分
string s;
int main()
{
    std::ios::sync_with_stdio(0);
	cin>>n;
	while(n--)
	{
		a=0,b=0,t=0;
		bool f=0;
		cin>>s;
		for(int i=0;i<10;++i)
		{
			if(s[i]=='1') 
			{
				if(i&1) a++;
				else    b++;
			}
			else if(s[i]=='0')
			{
				if(i&1) b++;
				else    a++;
			}
			else   t++;
			if(a+t>=6||b+t>=6) 
			{
				cout<<i+1<<endl;
				f=1;
				break;
			}
		}
		if(!f) cout<<10<<endl;//特判平局
	}
	return 0;
}

```

---

## 作者：dthythxth_Huge_Brain (赞：3)

## 题目分析

>共有 $10$ 次罚球机会，其中奇数次属于队伍 $1$，偶数次属于队伍 $2$。在罚球开始前，你预先知道了每一次罚球是必定成功（字符 $1$），必定不成功（字符 $0$），还是由你操纵（字符 $?$）。当一次罚球成功时，所在的队伍就会得到 $1$ 分，最终得分高的队伍获胜。当裁判发现某个队伍必胜的时候，就会宣布停止罚球（注意，裁判并不能预知罚球结果）。现在，你希望罚球的轮数尽可能少，求出这个轮数。

这题十分简单，输入一个字符串，从第一个字符开始判断，若此字符所在的顺序为奇数，则队伍 $1$ 罚球，否则队伍 $2$ 罚球。判断这个字符，如果它是 $1$，则当前罚球队伍进球个数加 $1$。如果该位置上的字符是 $?$，我们假设其为进球，并将相应的进球数加 $1$ 和剩余踢球次数减去 $1$。最后，我们再把该队剩余的踢球次数减 $1$。

每一次循环结束后，我们都要判断一下此队伍剩余的踢球次数是否小于 $0$，若是，输出当前循环次数加 $1$。若一直持续到罚球结束后，则输出 $10$。

## 参考代码

```
#include <iostream>
#include <string> // 头文件
using namespace std;
int kick(const string &s){
    int team1=0; // 队伍1进球数
    int team2=0; // 队伍2进球数
    int Team1=5; // 队伍1剩余的踢球次数
    int Team2=5; // 队伍2剩余的踢球次数
    for(int i=0;i<10;i++){
        if(i%2==0){
            // 队伍1踢球
            if(s[i]=='1')team1++;
            else if(s[i]=='?'){
                team1++;
                Team1--;
            }
            Team1--;
        }
		else{
            // 队伍2踢球
            if(s[i]=='1')team2++;
            else if(s[i]=='?'){
                team2++;
                Team2--;
            }
            Team2--;
        }
        // 检查是否可以停止点球阶段
        int maxteam1=team1+Team1;
        int maxteam2=team2+Team2;
        if (maxteam1<team2||maxteam2<team1)return i+1; // 点球阶段在当前踢球之后停止
    }
    return 10; // 没有提前停止，点球阶段完成全部 10 次罚球
}
int main(){
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        int mink=kick(s);
        cout<<mink<<endl;
    }
    return 0; // 完结撒花！
}

```

---

## 作者：wheneveright (赞：2)

## 题意

两个球队进行点球比赛，比赛规则是两队轮流点球，总共点 $10$ 次，最后进球多的球队获胜，**注意，在这种比赛规则下，两个球队可能会出现平局**，$T$ 组询问每组询问给出一个长度为 $10$ 的字符串，字符串的第 $i$ 位代表第 $i$ 次点球的结果 `1` 代表成功，`0` 代表失败，`?` 代表不知道结果，现在想知道，在 `?` 的所有结果中，哪种可以让点球比赛最快结束，输出结束的时刻即可。

例如，当点球的结果为 `101010????` 时，无论如何第二队都不可能获得胜利，所以提前结束并且输出 $6$。

## 分析

首先，我们可以用 $2^{10} = 1024$ 的复杂度暴搜，然后再来判断当前这种情况的结束时刻。

现在我们通过爆搜获得了一个长度为 $10$ 的由 `0`、`1` 组成的字符串。然后维护两个数组 $a$、$b$，$a_i$ 维护的是 $i$ 队在当前时刻进球数量之后最多进球的数量，$b_i$ 维护的是 $i$ 队在当前时刻已经进球的数量，显然当有一队的当前进球数量比另外一队的预测数量还要多的时候结束。

时间复杂度：$1024T$。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

int T, N;
char s[15];
int stk[15], top, res;

void DFS (int id) { // 2^n 枚举
    if (id > top) { // On check
        int a[2] = {5, 5}, b[2] = {0, 0};
        for (int i = 1; i <= N; i++) {
            int j = (i & 1); // j:当前球队编号 j^1:另一个球队编号
            if (s[i] == '0') a[j]--; else b[j]++;
            if (b[j] > a[j ^ 1] || b[j ^ 1] > a[j]) {
                res = min (res, i); // 判断是否出现一个球队碾压的情况
                return ;
            }
        }
        return ;
    }
    // 修改问号的位置为 0 或者 1
    s[stk[id]] = '0';
    DFS (id + 1);
    s[stk[id]] = '1';
    DFS (id + 1);
    return ;
}

int main () {
    cin >> T; N = 10;
    while (T--) {
        cin >> (s + 1); top = 0; res = 10; // 将 ? 的位置记录下来，方便 DFS
        for (int i = 1; i <= N; i++) if (s[i] == '?') stk[++top] = i;
        DFS (1); cout << res << endl;
    }
}
```

---

## 作者：Noby_Glds (赞：1)

此题贪心。
### 思路：
让裁判尽快宣布停止的方法有两个，要么让队伍 $1$ 疯狂进球，要么让队伍 $2$ 疯狂进球。

那要怎么做呢？以第一种情况为例，出现问号时，如果是队伍 $1$，就进球，反之不进球。

情况二反过来就行了。

用 $c$ 和 $d$ 数组分别维护情况一，二两个队伍的分数。

如果出现一个队伍的分数加上该队还没踢的点球数仍要小于另一个队的分数，结束比赛。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[11];
int n,c[2],d[2];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int i=1;i<=10;i++) cin>>a[i];
		for(int i=1;i<=10;i++){
			if(a[i]=='1') c[i%2]++,d[i%2]++;
			if(a[i]=='?'){
				if(i%2==1) c[1]++;
				else d[0]++;
			}
			if((10-i+1)/2+c[0]<c[1]||(10-i)/2+d[1]<d[0]||i==10){
				cout<<i<<endl;
				break;
			}

		}
		c[0]=c[1]=d[0]=d[1]=0;
	}
	return 0;
}
```


---

## 作者：Sai_t (赞：1)

本题数据很小，可以考虑状压枚举，从0000000000到1111111111挨个尝试。

如何判断至少比几局呢？可以利用贪心的思想，从左到右把分加给双方，对于每一个位置，如果一方剩下全赢对方全输也无法胜利，即可停止比赛。

最后在所有状态中取最小值，即为答案。

时间复杂度 $O(qn2^n)$可过。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t;string s;
int main(){
	cin>>t;
	while(t--){
		cin>>s;int ans=10;
		for(int msk=0;msk<1024;msk++){
			bool fl=0;
			for(int i=0;i<10;i++)if((!!(msk&(1<<i)))!=(int)(s[i]-'0')&&s[i]!='?'){fl=1;break;}
			if(fl)continue;
			int a=0,b=0;
			for(int i=0;i<10;i++){
				if(i%2)a+=!!(msk&(1<<i));
				else b+=!!(msk&(1<<i));
				if(i==9||a+(10-i)/2<b||b+(9-i)/2<a){
					if(i==2)cout<<msk<<endl;
					ans=min(ans,i+1);
					break;
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：cunzai_zsy0531 (赞：1)

## CF1553C题解-by cunzai_zsy0531

[题面](https://www.luogu.com.cn/problem/CF1553C)

做法一：注意到一共只有十局比赛，对于 `?` 来说只有两种可能 `1` 和 `0`，那么可以 $2^{10}$ 枚举所有情况，然后判断每一种情况进行了多少局，取个 $\min$。

做法二：对最后谁赢了分类讨论。若先罚的赢了，把先罚的人的所有 `?` 都换成 `1`，后罚的换成 `0`，一定会让进行的局数最少。反过来同理。计算这两种情况最少的局数，取个 $\min$ 即可。

code（做法二）：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
inline void solve(){
	char s[20];
	scanf("%s",s+1);
	int cnt1=0,cnt2=0,res1=5,res2=5,ans1=10,ans2=10;//cnt1和cnt2是两个人进球的局数，res1和res2是两个人剩余的局数
	for(int i=1;i<=10;++i){
		if(i&1){
			if(s[i]!='0') ++cnt1;
			--res1;
		}
		else{
			if(s[i]=='1') ++cnt2;
			--res2;
		}
		if(cnt2+res2<cnt1){ans1=i;break;}//判断比赛是否已经结束
	}
	cnt1=0,cnt2=0,res1=5,res2=5;
	for(int i=1;i<=10;++i){
		if(i&1){
			if(s[i]=='1') ++cnt1;
			--res1;
		}
		else{
			if(s[i]!='0') ++cnt2;
			--res2;
		}
		if(cnt1+res1<cnt2){ans2=i;break;}
	}
	printf("%d\n",min(ans1,ans2));
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
//C
```


---

## 作者：YGB_XU (赞：1)

这道题我们主要需要判断一种情况：某队即便接下来全部进球也没有办法胜出，那么比赛就可以提前结束。

我们考虑下列贪心做法，设两个队伍分别为 $a$ 队，$b$ 队，则每次“支持”一队，即当遇到不能确定的情况时，默认**支持**的那一队**进球**，而**不支持**的一队则**不会进球**。用这种极端情况进行模拟就可以得到比赛提前结束的最早时间。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

string s;

inline int cal1(){//支持a队
	int al=5,bl=5,as=0,bs=0;//al表示a队剩下的进球机会，bl同理，as则是a队已经得到的分数，bs同理
	for(int i=0;i<=9;i++){
		if(i%2==0){//team#1
			al--;//别忘了处理剩下的进球机会
			if(s[i]=='?'){
				as++;//默认进球
			}else{
				as+=(int)s[i]-'0';//字符转换为数字
			}
		}else{//team#2
			bl--;
			if(s[i]=='?'){
				//什么都不做，即默认不进球
			}else{
				bs+=(int)s[i]-'0';
			}
		}
		if(bs+bl<as) return i+1;//这里i是字符串下标，转换成点球的轮数需要+1
	}
	return 10;//未提前结束比赛，则返回10轮需要全部进行
}

inline int cal2(){//支持b队，同上
	int al=5,bl=5,as=0,bs=0;
	for(int i=0;i<=9;i++){
		if(i%2==0){//team#1
			al--;
			if(s[i]=='?'){
				
			}else{
				as+=(int)s[i]-'0';
			}
		}else{//team#2
			bl--;
			if(s[i]=='?'){
				bs++;
			}else{
				bs+=(int)s[i]-'0';
			}
		}
		if(as+al<bs) return i+1;
	}
	return 10;
}

int main(){
	int t;//CF多组数据
	cin>>t;
	while(t--){
		cin>>s;
		printf("%d\n",min(cal1(),cal2()));
	}
	return 0;
}
```


---

## 作者：NXYorz (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1553C)

------
### 题目大意
 给定长度为 $10$ 字符串 $s$, 它的每一位只可能是 ```1``` 或 ```0``` 或 ```?```, 对于第 $i$ 位，如果 $i$ 为奇数，那么对应甲队，否则对应乙队。 如果 $s_i$ 为 ```1``` 那么其对应队伍得 $1$ 分， 如果 $s_i$ 为 ```0``` 那么不得分，如果 $s_i$ 为 ```？``` 那么二者都有可能。如果有一个队伍获得了绝对优势(即即使后面的比赛领先的队伍全部不得分，落后的队伍全部得分也无法挽回颓势。），游戏结束。
 
 问所有的可能中，游戏可能进行的最小局数。
 
 -------
 ### 分析
 发现最多有 $2^k$ 种可能， 其中 $k$ 为 ```?``` 的个数。 $0 \le k \le 10$。
 
 那么就可以直接枚举所有可能，暴力判断即可。
 
 时间复杂度$O(t\times 2^k)$
 
 --------
 ### $Code$
 ```cpp
 #include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int MAX_TIME = (1 << 10) + 10;

int t,n,cnt;
char s[11],a[MAX_TIME][11];

void work()
{
	cin>>s; n = 0;cnt = 1;
	for(int i = 0; i < 10; i++)
		if(s[i] == '?') n++;
	for(int i = 0; i < 1 << n; i++)
		for(int j = 0; j < 10; j++)
			if(s[j] != '?') a[i][j] = s[j];

	for(int i = 0; i < 1 << n; i++)
	{
		int bit = 0;
	//	if(i == 682) kkksc03();
		for(int j = 0; j < 10; j++)
			if(s[j] == '?')
			{	
				bit++;
				a[i][j] = (i >> (bit - 1)) & 1 ? '1' : '0';
			}
	}

	int ans = 10;
	for(int i = 0; i < 1 << n; i++)
	{
		int sco_a = 0; int sco_b = 0;
	//	if(i == 682) kkksc03();
		for(int j = 0; j < 10; j++)
		{
			int rc = j + 1; int max_a , max_b;
			if(rc & 1) max_a = max_b = (10 - rc + 1) / 2;
			else max_b = (10 - rc) / 2 + 1 , max_a = (10 - rc) / 2;

			if((sco_a > sco_b) && (sco_a - sco_b > max_b)) {ans = min(ans , j);break;}
			else if((sco_a < sco_b) && (sco_b - sco_a > max_a)) {ans = min(ans , j);break;}

			if(a[i][j] == '1')
				if((j + 1) & 1) sco_a++;
				else sco_b++;
		}
	}
	printf("%d\n",ans);
}

int main()
{
//	freopen("aa.in","r",stdin);
	scanf("%d",&t);
	while(t--)
		work();
}
 ```

---

## 作者：liruixiong0101 (赞：0)

## P0 前置知识：
贪心。

## P1 题意：
队伍 1 和队伍 2 轮流踢点球，从队伍 1 开始踢点球。你一开始知道一个字符串，`1` 代表这一个点球踢进了，`2` 代表这个点球没有踢进，`?` 代表这个球可以由你操控可以踢进也可以不踢进，踢进得一分，否则不得分。当裁判发现某个队伍必胜的时候，就会宣布停止罚球。现在，你希望罚球的轮数尽可能少，求出这个轮数。

## P2 思路：
既然是求这个最少的轮数，考虑极端情况，要让某一个队伍踢的点球最多，也就是让所有 `?` 的情况让这个队伍得分或两个队伍的得分不变。而这个队伍是哪个队伍呢？这是我们就需要分类讨论，选择让队伍 1 踢最多还是让队伍 2 踢最多。  

---
### 理清一下思路。

- 若选择队伍 1 踢的最多：那么就要让每一个 `?` 的情况让队伍 1 踢进或让队伍 2 不踢进。
- 若选择队伍 2 踢的最多：那么就要让每一个 `?` 的情况让队伍 2 踢进或让队伍 1 不踢进。

## P3 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s;
int main(){
	// freopen("text.in" , "r" , stdin);
	// freopen("ans.txt" , "w" , stdout);
	ios::sync_with_stdio(0);
	cin.tie(0) , cout.tie(0);
	int T;
	for(cin >> T; T-- && cin >> s;){
		n = s.size();
		s = " " + s;
		int cnt1 = 0 , cnt2 = 0;
		int ans = n;
		for(int i = 1; i <= n; i++){//让队伍1踢最多
			if(s[i] == '1'){
				if(i & 1) cnt1++;
				else cnt2++;
			}
			else if(s[i] == '0'){
				if(i & 1) cnt2++;
				else cnt1++;
			}
			else{
				cnt1++;
			}
			if(cnt1 > cnt2 + n - i + 1){
				ans = min(ans , i);
				break;
			}
			if(cnt2 > cnt1 + n - i + 1){
				ans = min(ans , i);
				break;
			}
		}
		cnt1 = cnt2 = 0;
		for(int i = 1; i <= n; i++){//让队伍2踢最多
			if(s[i] == '1'){
				if(i & 1) cnt1++;
				else cnt2++;
			}
			else if(s[i] == '0'){
				if(i & 1) cnt2++;
				else cnt1++;
			}
			else{
				cnt2++;
			}
			if(cnt1 > cnt2 + n - i + 1){
				ans = min(ans , i);
				break;
			}
			if(cnt2 > cnt1 + n - i + 1){
				ans = min(ans , i);
				break;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：miserExist (赞：0)

## 思路
一眼觉得是小贪心小暴力, 然后就做了。

我的做法是先把原数组中下标为奇数的数组拿出来放在数组 $a$ 中，

把下标为偶数的数组拿出来放在数组 $b$ 中。

然后分别预处理出2组4个数组，

其中两个是以 $a$ 数组为优先级，也就是数组 $a$ 中的?都变为1 

数组 $b$ 中的?都变为0，另外两个数组与之相反。

然后就是暴力time

从前往后遍历每组数组，并在遍历总和更新的同时进行答案可行性判断即可。

部分解释请看代码
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);//加速加速加速加速
    int t;
    cin >> t;
    while(t --)
    {
        int a[12];
        int b[12];

        for(int i = 1; i <= 10; i ++)
        {
            char x;
            cin >> x;
            if(i % 2 == 1)
            {
                if(x == '0')
                {
                    a[i + 1 >> 1] = 0;
                }
                else if(x == '1')
                {
                    a[i + 1 >> 1] = 1;
                }
                else a[i + 1 >> 1] = 2;
            }
            else if(i % 2 == 0)
            {
                if(x == '0')
                {
                    b[i >> 1] = 0;
                }
                else if(x == '1')
                {
                    b[i >> 1] = 1;
                }
                else b[i >> 1] = 2;
            }
            
        }

        int aa[12], ab[12];//以a为优先级
        int ba[12], bb[12];//以b为优先级
        for(int i = 1; i <= 5; i ++)
        {
            if(a[i] == 2)
            {
                aa[i] = 1;
                ba[i] = 0;
            }
            if(b[i] == 2)
            {
                ab[i] = 0;
                bb[i] = 1;
            }
            if(a[i] != 2)aa[i] = ba[i] = a[i];
            if(b[i] != 2)ab[i] = bb[i] = b[i]; 
        }
		int suma = 0, sumb = 0;//当前进球数
        int resa = 10;//一直可行resa resb不会更新 这里直接初始化为10
        for(int i = 1; i <= 5; i ++)//优先级为a
        {
            suma += aa[i];//a先更新
            
            if(suma > sumb + 5 - (i - 1))//当前a与b差着1位 判断不同
            {
                resa = (i - 1) * 2 + 1;
                break;
            }
            if(suma + (5 - i) < sumb)
            {
                resa = (i - 1) * 2 + 1;
                break;
            }
            sumb += ab[i];
            if(suma + 5 - i < sumb)
            {
                resa = i * 2;
                break;
            }
            if(suma > sumb + 5 - i)
            {
                resa = i * 2;
                break;
            }
        }
        int resb = 10;

        suma = 0, sumb = 0;

        for(int i = 1; i <= 5; i ++)//优先级为b
        {
            suma += ba[i];
            if(suma > sumb + 5 - (i - 1))
            {
                resb = (i - 1) * 2 + 1;
                break;
            }
            if(suma + 5 - i < sumb)
            {
                resb = (i - 1) * 2 + 1;
                break;
            }
            sumb += bb[i];
            if(suma + 5 - i < sumb)
            {
                resb = i * 2;
                break;
            }
            if(sumb + 5 - i < suma)
            {
                resb = i * 2;
                break;
            }
        }
        cout << min(resa, resb) << endl;
    }
    return 0;
}
```

---

## 作者：oceanfish (赞：0)

## 题目
[题目传送门](https://www.luogu.com.cn/problem/CF1553C)

题目拟定了一场罚球，共有 $10$ 次罚球机会，这十次罚球的结果用一个字符串表示，这个串有三种字符，分别是 $1$，$0$ 与 $?$，$1$ 表示第一队胜利，$0$ 表示第二队胜利，$?$ 是其中任意一种。由于最终获胜结果是可以提前预测的，所以题目要求输出当进行至哪一次罚球时，我们知道最终结果，输出此数。
## 思路
实际上，我们可以猜出这是一道贪心题，那么具体怎么贪呢？考虑到这是预测出结果，我们很快就知道了，只要让其中一方疯狂的胜利，直到其中一方胜利次数比另一方胜利次数与剩余罚球次数总和都要多就行了。

当然，这是双方性的，我们要选出其中较小的一种即可。

我们还要特判，当函数运行到最后都不知道谁胜时，返回 $10$ 就行了。
## 代码
```cpp
//对于第一队
#define Q (s[i]=='?')
int to(char c) {
	return int(c) - '0';
}
int f1(string s) {
	int a = 0, b = 0;
	int al = 5, bl = 5;
	for (int i = 0; i < 10; i++) {
		if (i & 1) {
			al--;
			if (Q)
				a++;
			else
				a += to(s[i]);
		} else {
			bl--;
			if (!Q)
				b += to(s[i]);
		}
		if (b + bl < a)
			return i + 1;
	}
	return 10;
}
```


---

## 作者：封禁用户 (赞：0)

## 题目描述

[Penalty](https://www.luogu.com.cn/problem/CF1553C)

## 算法思路

### 算法：暴力

我们先把可能的答案分为以下两种：

- 我们是队伍 $1$ 的铁粉，永远支持队伍 $1$。就在队伍 $1$ 罚球的时候如果是由我操纵，就一定投中。在每一个时刻 $i$，都判断一遍是否必胜。如果必胜，返回 $i$就行了，最后如果平局，返回 $10$。

- 我们是队伍 $2$ 的铁粉，永远支持队伍 $2$。就在队伍 $2$ 罚球的时候如果是由我操纵，就一定投中。在每一个时刻 $i$，都判断一遍是否必胜。如果必胜，返回 $i$就行了，最后如果平局，返回 $10$。

最后取两种情况的最小值就行了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
ll n;
string a;
ll solve()//永远支持队伍1
{
	ll x=0,y=0,xx=5,yy=5;//x表示队伍1进了x颗球，y表示队伍2进了y颗球，xx表示队伍1还能罚xx次，yy表示队伍2还能罚yy次 
	for(int i=0;i<(ll)a.size();i++)
	{
		if(i%2)//队伍1罚球
		{
			xx--;//次数-1 
			if(a[i]=='1'||a[i]=='?')//问号也算进 
			{
				x++;//进球数+1 
			}
		}
		else//队伍2罚球
		{
			yy--;//次数-1 
			if(a[i]=='1')//问号不算进
			{
				y++;//进球数+1
			}
		}
		if(x>y+yy)//队伍1必胜 
		{
			return i+1;//一共i+1次 
		}
	}
	return 10;//总共10次 
}
ll work()//永远支持队伍2
{
	ll x=0,y=0,xx=5,yy=5;//x表示队伍1进了x颗球，y表示队伍2进了y颗球，xx表示队伍1还能罚xx次，yy表示队伍2还能罚yy次 
	for(int i=0;i<(ll)a.size();i++)
	{
		if(i%2)//队伍1罚球
		{
			xx--;//次数-1 
			if(a[i]=='1')//问号不算进
			{
				x++;//进球数+1
			}
		}
		else//队伍2罚球
		{
			yy--;//次数-1
			if(a[i]=='1'||a[i]=='?')//问号也算进
			{
				y++;//进球数+1
			}
		}
		if(y>x+xx)//队伍2必胜 
		{
			return i+1;//一共i+1次
		}
	}
	return 10;//总共10次
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);//输入输出优化 
    cin>>n;
    while(n--)//n组数据 
    {
    	cin>>a;
    	cout<<min(solve(),work())<<"\n";//输出最小值 
	}
    return 0;
}
```

---

