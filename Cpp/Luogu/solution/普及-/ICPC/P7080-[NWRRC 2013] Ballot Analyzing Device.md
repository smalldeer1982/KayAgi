# [NWRRC 2013] Ballot Analyzing Device

## 题目描述

平地的选举委员会正在为总统选举做准备。为了尽量减少人工因素在选票计数中的影响，他们决定开发一个自动化的选票分析设备（BAD）。

有 $n$ 名候选人竞选总统。选票上为每位候选人提供一个方框。选民必须在其中一个方框上做标记。如果没有标记任何方框或标记了两个或更多方框，则选票无效。每位选民将他的选票放入 BAD 的特殊扫描仪中。扫描仪分析选票上的标记并生成一个包含 $n$ 个字符的特殊投票字符串：标记的方框用 'X' 表示，未标记的用 '.' 表示。现在需要分析投票字符串以生成报告。你的任务是为 BAD 开发一个报告生成器。

给定所有选票的投票字符串，你的程序必须打印投票报告。报告中的候选人必须按得票数降序排列。如果两名候选人的得票数相同，他们在投票选票中的顺序也必须相同。对于每位候选人，计算他/她的得票百分比（如果候选人获得 $p$ 票，百分比结果为 $100p/m$）。报告的最后一行必须指明无效选票的百分比。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 7
Loudy
Apples
Dogman
Miller
.X..
X...
....
..X.
..XX
..X.
..X.
```

### 输出

```
Dogman 42.86%
Loudy 14.29%
Apples 14.29%
Miller 0.00%
Invalid 28.57%
```

# 题解

## 作者：ZBAA_MKC (赞：2)

本题根据题意模拟即可。

使用三个数组存储名字，一个存储选票，一个存储票数。

用二层循环，验证每一个人的选票是否有效，如果有效就记录他选的是哪个人，无效就计入无效选票的张数。

最后排序后按要求输出即可。

一开始我一直用的 `cin` 和 `printf` 的自带四舍五入但我发现总是会错个别的点（这题没有SPJ是真的恶心）， 于是我就手写了四舍五入函数，然后就AC了。

详情请见代码注释

```cpp
#include <bits/stdc++.h>
using namespace std;

string s[15];
char c[1005][15];
int cnt[15];

int n, m;
double sswr(int x)  //四舍五入函数
{
	double ans = x * 1.0 / m;
	return floor(ans * 10000 + 0.5) / 100.0;
}

int main()
{
    cin >> n >> m;
    int inv = 0; //储存无效票个数
    for (int i = 1; i <= n; i++)
	{
		cin >> s[i];
	} 
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> c[i][j];
		}
	} 
	for (int i = 1; i <= m; i++)
	{
		int t = 0;
		int id;
		for (int j = 1; j <= n; j++)
		{
			if (c[i][j] == 'X') //验证每个人的票是否属于有效票
			{
				t++;
				id = j;
			}
		}
		if (t != 1) //不是1就计入无效票
		{
			inv++;
		}
		else
		{
			cnt[id]++; //有效就给他记上
		}
	}
	for (int i = 1; i < n; i++) //手写冒泡排序，懒得写结构体
	{
		for (int j = 1; j < n; j++)
		{
			if (cnt[j] < cnt[j + 1])
			{
				swap(cnt[j], cnt[j + 1]);
				swap(s[j], s[j + 1]);
			}
		}
	}
	for (int i = 1; i <= n; i++) //输出（别忘换行）
	{
		cout << s[i] << " ";
		cout << sswr(cnt[i]) << "%" << endl;
	}
   	//还有无效票别忘了
	cout << "Invalid " << sswr(inv) << "%";
	return 0;
}
```


---

## 作者：D2T1 (赞：2)

## 题解

一道有一些细节的%你题。

可以使用 `struct` 来存储每一个人的名字、输入顺序、选票以及占比，然后用 `STL sort` 进行排序。

一些注意点：

- 注意无效票的处理

- 要先**四舍五入**，再进行排序。

## 代码

```cpp
//P7080
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

const int maxn=15;
string s[maxn],k;
struct people{string name;int id,tic;double ans;} a[maxn];
bool cmp(people a,people b){return a.ans!=b.ans?a.ans>b.ans:a.id<b.id;}

int main(){
	ios::sync_with_stdio(false); 
	int n,m,inv=0;
	cin >> n >> m;
	for(int i=0; i<n; ++i)
		cin >> s[i],a[i].name=s[i],a[i].id=i;
	for(int i=0; i<m; ++i){
		int sum=0,add=0;
		cin >> k;
		for(int j=0; j<n; ++j)
			if(k[j]=='X') add=j,++sum;
		if(sum==0||sum>1) ++inv;//无效选票
		else ++a[add].tic;//有效选票
	}
	for(int i=0; i<n; ++i)
		a[i].ans=double(round((double)a[i].tic*10000.0/m)/100.0);//使用round进行四舍五入
	sort(a,a+n,cmp);//排序
	for(int i=0; i<n; ++i)
		cout << fixed << setprecision(2) << a[i].name << ' ' << a[i].ans << "%\n";
	cout << fixed << setprecision(2) << "Invalid " << double(round((double)inv/m*10000.0)/100.0) << "%\n";
	return 0;
}
```


---

## 作者：Talanton_Cerydra (赞：1)

[P7080](https://www.luogu.com.cn/problem/P7080)

## 主要思路:暴力

首先建立一个结构体(方便后面的排序),存储**每个人的以下信息**:

1. 选手的名字

2. 选手的得票数和得票率

3. 选手的出场顺序

如下:

```cpp
struct dalao//存储每个选手的信息,方便排序
{
    string name;//名字
    int t=0,pl;//t为票数,pl为出现的先后序号
    double p;//得票率
}lwn[11];//数组存储
```


读入每个选手的名字,将其存入结构体中.同时记录其出场顺序(编号越小越先出场),如下:

```cpp
    for(int i=1;i<=n;i++)
    {
        cin>>lwn[i].name;
        lwn[i].pl=i;//记录顺序(就是当前i值)
    }
```


接着枚举每个选手的得票数.

对于每个投票人,逐个读入字符,同时记录投票数,并标记被投票的选手编号.

如果投票数等于 $1$ 则将其票数 $+1$ ,不等于 $1$ 就特判为无效票.这段稍有复杂:

```cpp
for(int i=1;i<=m;i++)//开始投票
    {
        int ee=0,op;//ee为投给了多少人(用来判断是否合法),op为投给的人(如果合法)
        for(int j=1;j<=n;j++)//判断每个人
        {
            char c;
            cin>>c;//读入每个字符
            if(c=='X')//如果投了这个人的票
            {
                ee++;//投给的人数++
                if(ee>=2)//不合法
                {
                    continue;//不管,继续(其实换成break也不是问题)
                }
                op=j;//标记投给的人
            }
        }
        if(ee!=1)//ee不等于1便为不合法
        {
            cnt++;//无效票数量++
            continue;//跳过,下一个投票者
        }
        lwn[op].t++;//投票成功
    }
```


下一步对每个人做除法,算出得票率(包括无效票也要算占比),同时四舍五入(这点是难点,在后面我们会提到).

再用 sort 按照得票率高低排序即可.**注意,如果有得票率相同的,要根据他们的出场顺序特判,这里就要用到我们开始标记的序号.**

```cpp
bool cmp(dalao x,dalao y)//本次sort所需的排序函数
{
    if(x.p==y.p)//得票率相同
    {
        return x.pl<y.pl;//谁先出现谁在前面,序号越小越先
    }
    return x.p>y.p;//得票率不同,比得票率
}
```

最后按规则输出即可.

时间复杂度: $O(nm)$

数据范围很小,可以过.

# 难点&坑点:四舍五入

题目中说需要四舍五入再进行排序,那么如何解决这个问题呢?

我们可以用到 C++ 自带的 round() 函数,**它可以将一个小数自动四舍五入到各位.**

因此,要保留 $2$ 位小数点,我们可以将要四舍五入的小数乘上 $100$ ,接着调用 round() 函数,最后除以 $100$ 恢复原状.这样我们就完成了四舍五入的过程.

就如下面这样:(假设 $a$ 是要四舍五入的小数)

```cpp
a=(double)(round(a*100.0)/100.0);
```

便可达到目标.

## AC代码:

```cpp
#include <bits/stdc++.h>
using namespace std;
struct dalao//存储每个选手的信息,方便排序
{
    string name;//名字
    int t=0,pl;//t为票数,pl为出现的先后序号
    double p;//得票率
}lwn[11];//数组存储
double in;//无效票占比
int n,m,cnt=0;//cnt为无效票个数
bool cmp(dalao x,dalao y)//本次sort所需的排序函数
{
    if(x.p==y.p)//得票率相同
    {
        return x.pl<y.pl;//谁先出现谁在前面,序号越小越先
    }
    return x.p>y.p;//得票率不同,比得票率
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        cin>>lwn[i].name;
        lwn[i].pl=i;//标记序号
    }
    for(int i=1;i<=m;i++)//开始投票
    {
        int ee=0,op;//ee为投给了多少人(用来判断是否合法),op为投给的人(如果合法)
        for(int j=1;j<=n;j++)//判断每个人
        {
            char c;
            cin>>c;//读入每个字符
            if(c=='X')//如果投了这个人的票
            {
                ee++;//投给的人数++
                if(ee>=2)//不合法
                {
                    continue;//不管,继续(其实换成break也不是问题)
                }
                op=j;//标记投给的人
            }
        }
        if(ee!=1)//ee不等于1便为不合法
        {
            cnt++;//无效票数量++
            continue;//跳过,下一个投票者
        }
        lwn[op].t++;//投票成功
    }
    for(int i=1;i<=n;i++)//计算得票率
    {
        lwn[i].p=(double)lwn[i].t/m*100;//需要乘上100(记得为double形式)
        lwn[i].p=(double)(round(lwn[i].p*100.0)/100.0);//四舍五入
    }
    //同理
    in=(double)cnt/m*100;
    in=(double)(round(in*100.0)/100.0);
    sort(lwn+1,lwn+n+1,cmp);//排序
    for(int i=1;i<=n;i++)
    {
        cout<<lwn[i].name<<" ";//输出名字
        printf("%0.2f%\n",lwn[i].p);//输出得票率,换行
    }
    printf("Invalid %0.2f%%",in);//输出无效票率
    return 0;
}
```

**求个赞~~**

[彩蛋](https://www.luogu.com.cn/blog/paiwyz314/)

---

## 作者：GoldenCreeper (赞：0)

> [P7080 [NWRRC2013]Ballot Analyzing Device](https://www.luogu.com.cn/problem/P7080)

------------

是一道比较简单的模拟题。

可以使用结构体来存储每个选手的信息，然后 `sort` 排序。

细节问题参见注释。

参考代码：
```
#include <bits/stdc++.h>
using namespace std;

struct Candidate { //结构体 包含每个选手的名字 票数 和总占比
    string name;
    int votes;
    double vote_rate;
};

// 四舍五入函数
double round(double x) {
    return floor(x * 100 + 0.5) / 100.0;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<Candidate> candidates(n); // 存储每个候选人的信息
    for (int i = 0; i < n; i++) {
        cin >> candidates[i].name;
        candidates[i].votes = 0;
        candidates[i].vote_rate = 0.0;
    }

    int invalid_votes = 0; // 记录无效票数

    // 统计每个候选人的得票数
    for (int i = 1; i <= m; i++) {
        int valid_votes = 0; // 统计每张票中有效票的数量
        int candidate_id; // 记录该张票的选票者选择的候选人的 id
        for (int j = 0; j < n; j++) {
            char vote;
            cin >> vote;
            if (vote == 'X') {
                valid_votes++;
                candidate_id = j;
            }
        }
        if (valid_votes != 1) invalid_votes++;
        else candidates[candidate_id].votes++;
    }

    // 计算每个候选人的得票率
    for (int i = 0; i < n; i++)
        candidates[i].vote_rate = round(candidates[i].votes * 100.0 / m);

    // 使用 sort 和匿名函数排序 
    sort(candidates.begin(), candidates.end(),[](Candidate a, Candidate b) {return a.votes > b.votes;});

    // 输出每个候选人的得票率
    for (int i = 0; i < n; i++)
        cout << candidates[i].name << " " << fixed << setprecision(2) << candidates[i].vote_rate << "%" << endl;

    // 输出无效票的比例
    double invalid_rate = round(invalid_votes * 100.0 / m);
    printf("Invalid %.2lf%\n", invalid_rate);

    return 0;
}

```

---

## 作者：honey_ (赞：0)

## 读题
  简述：求出所有人票数和得分率，排序后输出。
## 算法
  模拟+排序
## 具体思路
  读入 $n,m$ 和姓名后，每次读入 $n$ 个字符，如果字符 $=X，sum++$ 。  
  便利结束后   
  * 如果 $sum==0 || sum>1$  那么投票失败；
  * 否则 对应人的票数加一；
  
  求出所有人的得票率，排序。
  
  最后输出所有人的名字，得票率以及无效票的得分率。   
  注：需手写四舍五入，否则会丢失精度！
  
# code
```cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;
struct node
{
    string name;
    int t=0,id;
    double p;
    bool operator < (const node k) const //分数相等按id排序，否则按得票率排序
    {
    	if(p==k.p) return id<k.id;
    	return p>k.p;
	}
}d[11];
char c;
double noans;
int n,m,cnt=0;
int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) cin>>d[i].name,d[i].id=i;
    for(int i=1;i<=m;i++)
    {
        int sum=0,step;
        for(int j=1;j<=n;j++)
        {
            cin>>c;
            if(c=='X') sum++,step=j;  //有人投票，则sum++,被投票人为j
        }
        if(!sum || sum>1) cnt++;  //无效票
        else d[step].t++;
    }
    for(int i=1;i<=n;i++) d[i].p=(double)d[i].t/m*100,d[i].p=(double)(round(d[i].p*100.0)/100.0);
    noans=(double)cnt/m*100,noans=(double)(round(noans*100.0)/100.0);  //手写四舍五入
    sort(d+1,d+n+1);
    for(int i=1;i<=n;i++)
    {
        cout<<d[i].name<<" ";
        printf("%0.2f%\n",d[i].p);
    }
    printf("Invalid %0.2f%%",noans);
    return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 名选手参加一个比赛，有 $m$ 个人为他们投票。第 $i$ 个人的投票情况用一个长度为 $n$，并且仅包含 `.` 和 `X` 两个字符的字符串，其中，如果第 $j$ 位是 `X`，则第 $i$ 个人将票投给了第 $j$ 名选手，否则没有。规定每个投票者能且仅能将票投给一个人，否则都算无效票（即投的票数 $\geqslant 2$ 或者 $=0$）。请将每名选手按照他们所得到的票的比例排序（如果有两名选手得到的票的比例相同，在投票次序中先出现的那名选手排在前面），并输出他们的名字和得票比例，最后还要输出无效票所占的比例。

比例输出为百分数，$\%$ 前面的部分四舍五入到 $2$ 位小数。

**数据范围：$2\leqslant n\leqslant 10,1\leqslant m\leqslant 1000$。**
## Solution
直接按照题意模拟就好，不过要注意四舍五入的问题。`printf` 的自动四舍五入有时候会出现 bug 导致 `WA on test 19`，所以需要自己手写一个函数来处理四舍五入。具体实现可以参考这里的代码。
## Code
```cpp
int n, m, in;
string tp;
struct user {
	string name;
	int val, id;
	bool operator < (const user& cz) const {return val > cz.val || (val == cz.val && id < cz.id);}
}a[17];

inline void judge(string s) {
	int len = s.size(), xnum = 0, xpl;
	F(i, 0, len - 1) if(s[i] == 'X') xnum++, xpl = i + 1;
	if(xnum != 1) {in++; return;}
	a[xpl].val++;
}
inline double getans(int x) {
	double ans = x * 1.0 / m, aa = ans * 10000;
	return floor(aa + 0.5) / 100.0;
}

int main() {
	n = Rint, m = Rint;
	F(i, 1, n) {
		cin >> a[i].name;
		a[i].id = i;
	}
	F(i, 1, m) {
		cin >> tp;
		judge(tp);
	}
	sort(a + 1, a + n + 1);
	F(i, 1, n) {
		cout << a[i].name << ' ';
		double ans = getans(a[i].val);
		printf("%.2lf%%\n", ans);
	} 
	printf("Invalid %.2lf%%\n", getans(in));
	return 0;
}
```

---

## 作者：Sora1336 (赞：0)

题面翻译：有 $m$ 个人给 $n$ 个人投票，每个人最多给一个人投票。如果投了两个人或者没有投票的话，那么这张票就算无效。按照票数高低排序，如果票数相同，就按照一开始的顺序输出。无效的比例也算在内。

这不是模拟吗... 但是四舍五入非常恶心，我不得不编写了一个函数来支持这个功能。浮点数保留小数点后的数据，有时会自动四舍五入，有时不会...

模拟的话还是放一下代码吧。

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
char s[114514];
pair<int, pair<int, string> > p[114514];
void Fun(double a, double *h) {		//四舍五入 
	int t=(a*1000+5)/10;
    *h =(float)t/100;
}
int main() {
	int n, m;
	scanf("%d%d",&n, &m);
	for(int i = 0; i < n; i ++) cin >> p[i].second.second, p[i].second.first = n - i;
	int t = 0;
	for(int i = 0; i < m; i ++) {	//投票情况处理
		scanf("%s",s);
		int flag = 0,cnt = 0;
		for(int j = 0; j < n; j ++) if(s[j]=='X') flag = j, cnt ++;
		if(cnt == 0 || cnt > 1) t ++;
		else p[flag].first ++;
	} sort(p,p + n);
	for(int i = n - 1; i >= 0; i --) {
		cout << p[i].second.second << " ";
		double a;
		Fun(100.00 * p[i].first / m, &a);
		printf("%.2f%%\n", a);
	} printf("Invalid %.2f%%\n", 100.00 * t / m);
}
```

---

