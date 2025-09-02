# [ICPC 2022 Jinan R] Frozen Scoreboard

## 题目描述

2000 年以前的秦朝，曾举办过一次 ICPC 比赛。比赛中有 $m$ 道题，$n$ 个团队。我们知道每个队完成了多少道题以及其历史记录的总用时。这些称作该团队的结果，但是我们不知道他们每道题是否完成、用时多久。

最近，我们发现了每个队**冻结的计分板**。从该计分板上，我们可以看到每个队在比赛中的提交情况，但是不知道在最后一小时内提交的判分。一些人发现，对于一些队来说，他们冻结的计分板可能与他们在历史记录中的最终成绩相矛盾。

请根据最终得分和冻结的计分板，为各队创建一个与其最终结果和冻结的计分板一致的最终计分板。

按照以下规则来计算计分板和总分：

对于给定的队伍 $i$，它**最终的计分板**是一个 $m$ 元数组，其中第 $j$ 个元素给出队伍 $i$ 在第 $j$ 题上的提交信息。

- 如果队伍 $i$ 没有提交问题 $j$，输出 ```.```。

- 如果队伍 $i$ 对问题 $j$ 提交了 $x$ 次但均未通过，输出 $-x$。

- 否则，考虑队伍 $i$ 在问题 $j$ 的所有评测结果。每次提交都有一个提交时间，设第一个通过的评测是第 $x$ 次评测，在第 $y$ 分钟时提交。输出 $+x/y$，其中 $0\leq y\leq299$。

在最终计分板上，只考虑第一次通过的提交。同一分钟内可能有多次提交。

一个队伍的最终得分是该队伍完成了多少道题，即该队最终计分板上 ```+``` 的个数。

一个队伍总用时按如下方式计算。如果队伍 $i$ 在第 $y$ 分钟完成了第 $j$ 道题，在完成前有 $x-1$ 次失败的提交（即最终计分板上第 $j$ 个问题的数为 $+x/y$），该问题的用时记为 $20(x-1)+y$。 如果队伍 $i$ 没有完成第 $j$ 道题，该问题的用时记为 $0$，无论是否提交过。队伍 $i$ 的总时间是每道题用时的总和。

## 样例 #1

### 输入

```
1 13
7 951
+ 1/6
? 3 4
+ 4/183
- 2
+ 3/217
.
.
.
+ 2/29
+ 1/91
.
+ 1/22
.```

### 输出

```
Yes
+ 1/6
+ 2/263
+ 4/183
- 2
+ 3/217
.
.
.
+ 2/29
+ 1/91
.
+ 1/22
.```

## 样例 #2

### 输入

```
6 2
1 100
.
? 3 4
2 100
+ 1/1
+ 1/2
0 0
- 5
- 6
2 480
? 100 100
? 100 100
2 480
? 99 100
? 100 100
1 2000
? 100 100
? 100 100```

### 输出

```
No
No
Yes
- 5
- 6
Yes
+ 1/240
+ 1/240
No
Yes
+ 87/280
- 100```

# 题解

## 作者：Field_Mouse (赞：2)

马上打 ICPC 了写篇题解涨涨 rp /kel

### 题意简述&题意分析

这一题最难的部分就是看懂题面，看懂了就是纯模拟。

给你 ICPC 队伍前四小时的提交记录，求出一种可能的最终得分。共 $n$ 次询问。

我们约定输入中的符号如下意：

- $+xy$ 第 $x$ 次提交通过了此题，最后一次提交为 $y$ 分时的提交。

由题目中的罚时可得，此题的用时认为是 $20\times (x-1)+y$.

- $-x$ 共计提交 $x$ 次均未通过此题，且在最后一小时内未通过此题。

这题的罚时记为 $0$.

- $.$ 整场比赛中未提交此题。

显然以上三种情况不用处理，直接保留到最终结果即可。

- $?xy$ 在前四小时内未通过此题，但在最后一小时内提交此题且未知是否通过。整场比赛中共计提交 $y$ 次，其中有 $x$ 次是在最后一小时内提交的。

这是本题唯一需要处理的部分。

### 做法简述

我们直接保留除了 $?xy$ 的全部信息，然后发现就是要把总时间 $b$ 分配给 $a$ 道通过的题。

而未知用时的题目只有 $?xy$ 的题目，而总题目数又很小，所以可以直接枚举子集，贪心的分配时间。

时间复杂度是 $O(2^m\times nmx)$ 的 $x$ 是每题最大提交数。

细节看代码注释。

```
#include<bits/stdc++.h>
#define AC return 0;
#define pr(n) printf("%d",(n))
#define hh puts("")
#define kg printf(" ")
using namespace std;
namespace fr{
	int read()
	{
		int x=0,flag=1;
		char ch=getchar();
		for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')flag=-1;
		for(;ch<='9'&&ch>='0';ch=getchar())x=(x<<3)+(x<<1)+ch-'0';
		return flag*x;
	}
}
using namespace fr;
const int N = 1e3+3;
struct node{
	char opt;
	int x,y;
}ans[N],kn[N];
int a,b;
int n=read(),m=read();
vector<int> yiw;
int tims,cnt;
bool flag;
void init()
{
	a=read(),b=read();
	tims=0,cnt=0;
	yiw.clear();
	for(int i=1;i<=m;i++)
	{
		char c;
		cin>>c;
		kn[i].opt=c;
		if(c=='.'){ans[i].opt='.';continue;}
		if(c=='+')
		{
			++cnt;
			kn[i].x=read(),kn[i].y=read();
			tims+=20*(kn[i].x-1)+kn[i].y;//罚时/kel
			ans[i]=kn[i];
		}
		if(c=='-')
		{
			kn[i].y=read();
			ans[i]=kn[i];
		}
		if(c=='?')
		{
			kn[i].x=read(),kn[i].y=read();
			yiw.push_back(i);
		}
	}//处理输入，/yiw存尚且不确定的几个结果，下面处理
}
void out()
{
	if(!flag){puts("No");return ;}
	puts("Yes");
	for(int i=1;i<=m;i++)
	{
		if(ans[i].opt=='.'){puts(".");continue;}	
		if(ans[i].opt=='+'){cout<<"+ "<<ans[i].x<<"/"<<ans[i].y<<endl;continue;}
		if(ans[i].opt=='-'){cout<<"- "<<ans[i].y<<endl;continue;}
	}
}
void sol()
{
	init();
	int T = yiw.size();
	flag=0;
	for(int i=0;i<(1<<T);++i)//直接枚举全部子集
	{
		int ncnt=cnt,maxn=tims,minn=tims;
		for(int j=0;j<T;++j)
		{
			if((i>>j)&1)
			{
				++ncnt;
				minn+=240+20*(kn[yiw[j]].y-kn[yiw[j]].x);
				maxn+=299+20*(kn[yiw[j]].y-1);
			}
		}//求出当前方案罚时的取值范围
		if(ncnt==a&&minn<=b&&b<=maxn)//有解
		{
			flag=1;
			b-=minn;//可以直接消去当前方案的最小罚时
			for(int j=0;j<T;++j)
			{
				if((i>>j)^1)ans[yiw[j]].opt='-',ans[yiw[j]].y=kn[yiw[j]].y;//不选睡觉
				if((i>>j)&1)//选择这一题
				{
					ans[yiw[j]].opt='+';
					int l=240+20*(kn[yiw[j]].y-kn[yiw[j]].x);
					int r=299+20*(kn[yiw[j]].y-1);//当前最大可能时间与最小可能时间
					if(b>=r-l)
					{
						b-=r-l;
						ans[yiw[j]].x=kn[yiw[j]].y;
						ans[yiw[j]].y=299;//罚时还很多
					}
					else if(!b)
					{
						ans[yiw[j]].x=kn[yiw[j]].y-kn[yiw[j]].x+1;
						ans[yiw[j]].y=240;//罚时不够了
					}
					else
					{
						for(int k=0;k<kn[yiw[j]].x;++k)
						{
							int now=b-k*20;
							if(0<=now&&now<=59)
							{
								ans[yiw[j]].x=kn[yiw[j]].y-kn[yiw[j]].x+k+1;
								ans[yiw[j]].y=240+now;
								b=0;
								break;//罚时还剩一点
							}
						}
					}
				}
			}	
		}//重复枚举这个方案
	}
	out();
}
int main()
{
	while(n--){
		sol();
	}
	AC
}
```

---

## 作者：Tsumugi_Mirai (赞：0)

不难发现，我们需要处理的只有每个 `？` 提交，且每个 `？` 提交可以贡献的的罚时一定是一段区间。（240 ~ 299）
因为题目数量很少，可以暴力枚举每一个题目是否通过，然后计算总罚时是不是在对应的区间和里，最后贪心地求出每道题的贡献。
时间复杂度 $O(nm2^m)$ 

**代码**：


```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define infi 0x3f3f3f3f3f3f3f3f
using namespace std;

typedef long long ll;

const int N = 1020;
const int M = 20;

int n, m;

struct node {
    int sor, plt;
    int nsor, nplt;
    char c[M];
    int tries[M], time[M], extr[M];
    int check;
} team[N];

void solve(int p) {
    for (int i = 0; i < (1 << m); i++) {
        int splt = team[p].nplt, mplt = team[p].nplt;
        int cot = 0;
        for (int j = 0; j < m; j++) {
            if (((i >> j) & 1) && team[p].c[j + 1] == '?') {
                cot++;
                splt += (team[p].tries[j + 1] - team[p].extr[j + 1]) * 20;
                splt += 240;
                mplt += (team[p].tries[j + 1] - 1) * 20;
                mplt += 299;
            }
        }
        if (cot + team[p].nsor != team[p].sor)
            continue;
        int dis = team[p].plt - splt;
        if (dis >= 0 && mplt >= team[p].plt) {
            team[p].check = 1;
            for (int j = 0; j < m; j++) {
                if (((i >> j) & 1) && team[p].c[j + 1] == '?') {
                    team[p].c[j + 1] = '+';
                    int add = dis / 20;
                    if (add > team[p].extr[j + 1] - 1) {
                        dis -= (team[p].extr[j + 1] - 1) * 20;
                    } else {
                        dis -= add * 20;
                        team[p].tries[j + 1] -= (team[p].extr[j + 1] - add - 1);
                    }
                    if (dis > 59) {
                        dis -= 59;
                        team[p].time[j + 1] = 299;
                    } else {
                        team[p].time[j + 1] = 240 + dis;
                        dis = 0;
                    }
                } // 贪心地分配时间
            }
            return;
        }
    }
}

void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> team[i].sor >> team[i].plt;
        for (int j = 1; j <= m; j++) {
            cin >> team[i].c[j];
            if (team[i].c[j] == '.') {
                continue;
            } else if (team[i].c[j] == '+') {
                team[i].nsor++;
                string s, t = "", m = "";
                cin >> s;
                bool pd = true;
                for (int k = 0; k < (int)s.size(); k++) {
                    if (s[k] != '/' && pd) {
                        t += s[k];
                    } else if (s[k] != '/' && !pd) {
                        m += s[k];
                    } else {
                        pd = false;
                    }
                }
                team[i].tries[j] = stoi(t);
                team[i].time[j] = stoi(m);
                team[i].nplt += (team[i].tries[j] - 1) * 20 + team[i].time[j];
            } else if (team[i].c[j] == '-') {
                cin >> team[i].tries[j];
            } else if (team[i].c[j] == '?') {
                cin >> team[i].extr[j] >> team[i].tries[j];
            }
        }
        if (team[i].nplt < team[i].plt) {
            solve(i);
        } else if (team[i].nplt == team[i].plt) {
            team[i].check = 1;
        }
    }
}

void output() {
    for (int i = 1; i <= n; i++) {
        int sor = 0, plt = 0;
        for (int j = 1; j <= m; j++) {
            if (team[i].c[j] == '+') {
                sor++;
                plt += (team[i].tries[j] - 1) * 20 + team[i].time[j];
            }
        }
        if(sor != team[i].sor || plt != team[i].plt) team[i].check = 0; // 检查贪心结果的正确性
        if (team[i].check == 0) {
            cout << "No\n";
            continue;
        }
        cout << "Yes\n";
        for (int j = 1; j <= m; j++) {
            if (team[i].c[j] == '+') {
                cout << team[i].c[j] << " ";
                cout << team[i].tries[j] << "/" << team[i].time[j];
            } else if (team[i].c[j] == '-' || team[i].c[j] == '?') {
                cout << '-' << " ";
                cout << team[i].tries[j];
            } else if (team[i].c[j] == '.') {
                cout << ".";
            }
            cout << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    init();
    output();
    return 0;
}
```

---

