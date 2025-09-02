# Sponsor of Your Problems

## 题目描述

对于两个整数 $a$ 和 $b$，我们定义 $f(a, b)$ 为 $a$ 和 $b$ 的十进制表示中，相同位置上数字相同的位数。例如，$f(12, 21) = 0$，$f(31, 37) = 1$，$f(19891, 18981) = 2$，$f(54321, 24361) = 3$。

现在给定两个十进制表示长度相同的整数 $l$ 和 $r$，考虑所有满足 $l \leq x \leq r$ 的整数 $x$。你的任务是求出 $f(l, x) + f(x, r)$ 的最小值。

## 说明/提示

在第一个测试用例中，可以选择 $x = 1$，此时 $f(1, 1) + f(1, 1) = 1 + 1 = 2$。

在第二个测试用例中，可以选择 $x = 2$，此时 $f(2, 2) + f(2, 3) = 1 + 0 = 1$。

在第三个测试用例中，可以选择 $x = 5$，此时 $f(4, 5) + f(5, 6) = 0 + 0 = 0$。

在第四个测试用例中，可以选择 $x = 15$，此时 $f(15, 15) + f(15, 16) = 2 + 1 = 3$。

在第五个测试用例中，可以选择 $x = 18$，此时 $f(17, 18) + f(18, 19) = 1 + 1 = 2$。

在第六个测试用例中，可以选择 $x = 200$，此时 $f(199, 200) + f(200, 201) = 0 + 2 = 2$。

在第七个测试用例中，可以选择 $x = 900$，此时 $f(899, 900) + f(900, 999) = 0 + 1 = 1$。

在第八个测试用例中，可以选择 $x = 1992$，此时 $f(1990, 1992) + f(1992, 2001) = 3 + 0 = 3$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
14
1 1
2 3
4 6
15 16
17 19
199 201
899 999
1990 2001
6309 6409
12345 12501
19987 20093
746814 747932
900990999 900991010
999999999 999999999```

### 输出

```
2
1
0
3
2
2
1
3
3
4
3
5
12
18```

# 题解

## 作者：zhouwenbo1234 (赞：5)

## 题解：CF2121E Sponsor of Your Problems
### 思路
**情况一：**
如果两个数第 $i$ 位相等，那无论怎么放，一定有 $S3_i=S1_i$ 和 $S3_i=S2_i$，所以 $ans + 2$。![](https://cdn.luogu.com.cn/upload/image_hosting/y8zvuhrz.png)
这里前五位只能填 $11451$，所以无论怎样都会和 $S1_i$ 和 $S2_i$ 相同，所以 $ans = 10$。  
**情况二：**
如果 $S2_i - S1_i = 1$，那么你填的数要么和 $S1_i$ 相同，要么和 $S2_i$ 相同，所以 $ans + 1$。比如上面那个例子，第 $6$ 位 $4$ 和 $5$ 相差 $1$。所以 $ans = 10 + 1 = 11$。  
**情况三：**
如果 $S2_i - S1_i \ge 2$，那么后面就可以填即不等于 $S1_i$ 又不等于 $S2_i$ 的数了，$ans$ 也就不变了。 
## Code

```
#include <bits/stdc++.h>
using namespace std;

int t,a,b;
string s1,s2;

int read(){
	int x=0,f=1;char c=getchar();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
	return x*f;
}

int main(){
	t=read();
	while (t--){
		a=0;
		b=0;
		int ans=0;
		cin >>s1>>s2;
		bool mark=0;
		for (int i=0;i<s1.size();i++){
			a=a*10+s1[i]-'0';
			b=b*10+s2[i]-'0';
			if ((b-a)>=2)
				mark=1;
			if (!mark){
				if (s1[i]==s2[i])
					ans+=2;
				else
					ans+=1;
			}
		}
		cout <<ans<<endl;
	}
	return 0;
}
```

---

## 作者：DX3906_ourstar (赞：4)

~~超级无敌人类智慧题。~~

## 结论

以字符串形式读入 $l,r$ 并从左往右扫描，记当前扫过的所有位置拼出的十进制数为 $a,b$；那么如果 $b-a\ge2$，则不再扫描；如果 $r_i-l_i=1$，则将答案加 $1$；如果 $l_i=r_i$，则将答案加 $2$。

## 证明

在从左到右扫描的过程中，只要 $l$ 和 $r$ 在当前位置相等，我们就可以构造 $x$ 使得该位同时等于 $l$ 和 $r$，即 $f(l, x) + f(x, r)$ 增加 $2$；  

如果当前位 $l_i \ne r_i$，那么可以构造 $x$ 的该位为 $l_i$ 或 $r_i$，使得 $f(l, x) + f(x, r)$ 增加 $1$；  

一旦在某一位之后无法保证 $x$ 保持在 $l$ 和 $r$ 的“共同前缀”的夹缝之间（即 $b - a \ge 2$），后续位就无法保证任何相同，因此不会再贡献相同位数。

因此结论正确。

## 举例

我们再举一个例子。令 $l=14414,r=14530$。

扫描前，我们令 $res=0$。

当 $i=1$ 时，$l_i=r_i=1$，于是 $res$ 加 $2$，变为 $2$；

当 $i=2$ 时，$l_i=r_i=4$，那么 $res$ 变为 $4$；

当 $i=3$ 时，$l_i=4,r_i=5$，此时 $r_i-l_i=1$，因此 $res$ 加 $1$，变成 $5$；

当 $i=4$ 时，$a=1441,b=1453$，$b-a=12$，不再扫描。

所以 $res$ 的最终值为 $5$。

## 代码

```
#include<iostream>
using namespace std;

int T;
string l,r;

inline void work(){
	cin>>l>>r;
	int len=l.size();
	int res=0,a=0,b=0;
	for(int i=0;i<len;++i){
		a*=10,b*=10;
		a+=(l[i]^48),b+=(r[i]^48);
		if(b-a>=2)break ;
		if(l[i]==r[i])res+=2;
		else ++res;
	}
	cout<<res<<"\n";
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

## 作者：fengzhaoyu (赞：4)

## 题意
~~题目给得很清楚了吧？不再赘述。~~
## 思路
贪心地思考问题。

如果某一位数，我选的数字与约束它的两个数字不同（当然得介于它们之间），那后面位的数字是不是就可以摆脱前面的约束，从而“完美避开”约束它的数，从而不增加答案？

但是，当约束它的 $l$ 和 $r$ 同一位数字 $l_i$ 和 $r_i$ 的值差小于等于 1，那你就不得不选一个数字（$l_i$ 或 $r_i$），此时答案就会更新。那具体有哪些情况呢？

1. 答案加一的情况：当前位差一并且上一位相等。或者，上一位相差一且当前位 $l_i$ 为 9，$r_i$ 为 0，这样的话你还是只能选 0 或 1。或者，上一位 $l_i-1$ 为 9，$r_i-1$ 为 0，这一位也 $l_i$ 为 9，$r_i$ 为 0，原因同理。
2. 答案加二的情况：上一位和当前位都相等，只有这种情况你才不得不使这一位与约束它的数字**都**相同。
3. 答案不加的情况：即非上述情况的情况，而且一旦出现此情况，后面都可以摆脱约束，不增加答案了。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10],b[10];
int n;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		char ll[10],rr[10];
		cin>>ll>>rr;
		n=strlen(ll);
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			a[i]=ll[i-1]-'0';
			b[i]=rr[i-1]-'0';
		}
		for(int i=1;i<=n;i++)
		{
			if((a[i]+1==b[i]&&a[i-1]==b[i-1])||((a[i]==9&&b[i]==0)&&(a[i-1]+1==b[i-1]))||(a[i]==9&&a[i-1]==9&&b[i]==0&&b[i-1]==0))
			{
				ans++;
			}
			else if(a[i]==b[i]&&a[i-1]==b[i-1])
			{
				ans+=2;
			}
			else 
			{
				break;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：shiziyu111 (赞：3)

# 题目大意

令 $f(a,b)$ 为 $a$ 与 $b$ 相同位数之和，请找到一个数 $x$，使得 $l\le x \le r$，并且 $f(l,x)+f(x,r)$ 最小，求出最小的 $f(l,x)+f(x,r)$，保证 $l$ 和 $r$ 位数相同。
# 分析

很明显，我们需要从高位向低位逐渐判断，每一位会产生三种情况。

1. $l_i+2\le r_i$，此时我们可以选取 $l$ 和 $r$ 的中间数，很明显，之后的数我们就可以自由选择，我们只需要选择与 $l$ 和 $r$ 完全不一样的数字，就可以在毫无花费的情况下解决问题，此时我们的答案就是正确答案。
2. $l_i=r_i$，此时我们只能使 $x_i=l_i$，产生 $2$ 的花费。
3. $l_i+1=r_i$，此时我们可以选择 $l_i$ 或 $r_i$，产生 $1$ 的花费，但是我们还需要考虑到下一位，所以我们可以从 $r_i$ 借走 $1$ 给下一位，即给 $r_{i+1}$ 加上 $10$，再比较下一位。

最终答案就是所求的花费。
# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[11],b[11];
string l,r;
int answer(int u,int mode,int ans)
{
	if(u==l.size()+1)
	{
		return ans;
	}
	if(mode==1)
	{
		b[u]+=10;
	}
	if(abs(a[u]-b[u])>=2)
	{
		return ans;
	}
	if(abs(a[u]-b[u])==1)
	{
		return answer(u+1,1,ans+1);
	}
	if(a[u]==b[u])
	{
		return answer(u+1,2,ans+2);
	}
}
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{	
		cin>>l>>r;
		for(int i=0;i<l.size();i++)
		{
			a[i+1]=l[i]-'0';
			b[i+1]=r[i]-'0';
		}
		cout<<answer(1,2,0)<<"\n";
	}
	return 0;
}
```

---

## 作者：StarLinkOvO (赞：3)

# [E. Sponsor of Your Problems](https://codeforces.com/contest/2121/problem/E)

[也许更好的阅读体验](https://www.cnblogs.com/StarLink/p/18950549)

## 题目简述

定义 $f(a, b)$ 表示这两个数的十进制下数字相同的位数，如 $f(21,12) = 0$，$f(54321, 24361) = 3$。

给两个位数相同的十进制数 $l$ 和 $r$，求 $l \leq x \leq r$ 中 $f(l, x) + f(x, r)$ 的最小值。

## 思路

分类讨论，我们从简单到难分析。

首先如果 $l = r$，答案就是数字位数乘二，直接输出。

接下来考虑一般的请况，我们假设现在 $l = 1239971$，$r = 1240056$。

我们从高位到低位看，发现它们的最高两位是相同的，那么在它们之间的数都是 $12 \dots$ 的形式，和第一种相似，直接将一样的位数乘二加到答案里（但是一定要是从最高位开始都一样）。

第三、四、五位是我们讨论的重点所以我们暂时跳过一下。

我们看倒数第二位，发现如果选 $6$ 的话就完美绕开限制了，既然题目中让我们求最小值那肯定是能绕就绕，而且这一位之后的数字肯定存在和 $l$ 与 $r$ 上对应位置的数字不同的，即后面也不会对答案有贡献。所以，**当同一位上的数字之差大于 1，就直接输出答案**。

举一个其它例子，当 $l = 369, r = 531$ 时，我们最高位取了 $4$ 之后，后面的数无论怎么选都是在 $l$ 和 $r$ 这个区间里的，就一定有 473 这样每一位都和 $l, r$ 不同的，那么这之后的答案贡献就是 0。

回看第三位，即同一位上的数字相差为 1 怎么办。

那么当前位肯定是要**在两位中选一个**了，我们先将**答案加上一**再考虑后面的。

容易发现，它的下一位是几乎没有限制的，也就是对答案的贡献为 0。\
但是如果像我们举的这个例子一样，出现了 $l$ 上这一位为 9 另一个为 0，那就等于是在 39 和 40 中选一个，**答案加一**，然后考虑下一位什么情况；\
如果很不幸下一位还是这种情况，到这里相当于 399 和 400 中选，就只能一直选下去。

不过如果某一位出现了不一样的情况，像我们举的例子一样出现了其他的数字，那就相当于后面的数字又可以随便选了，后面的答案贡献都是 0，我们直接输出答案跑路就 OK 了。

如果还有不太懂的可以自己写个数想一想，还是很好推的。

思路清晰后代码就很好写了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int x, y, len, ans, tpos;
int a[3][11];

void part(int x, int op) {
    int l = 0;
    while (x) {
        a[op][++l] = x % 10;
        x /= 10;
    }
    len = l;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        tpos = ans = 0;
        cin >> x >> y;
        part(x, 1), part(y, 2);

        if (x == y) { // 特判
            cout << 2 * len << endl;
            continue;
        }

        for (int i = len; i; i--) { // 判断相等的情况
            if (a[1][i] != a[2][i]) {
                tpos = i;
                break;
            }
            ans += 2;
        }

        int f = 0; // f:是否出现数字相差 1
        for (int i = tpos; i; i--) {
            // 相差为一且前面都是相等的
            if (a[1][i] + 1 == a[2][i] && !f) {
                ans++; // 只能选一个，答案肯定加一
                f = 1;
                continue;
            }
            // 前面有相差为一的情况且第一个数当前位是9另一个是0
            else if (a[1][i] == 9 && a[2][i] == 0 && f) {
                ans++; // 同样二选一
                continue;
            }

            break; // 都不符合：一定有和两个数字都不同的情况，直接输出答案
        }

        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：BaiBaiShaFeng (赞：3)

## 思路

没有多想，最近数位 dp 写的多，所以直接写了一个记忆化搜索。

非常无脑，我们像数位动态规划的记搜实现一样把几个数字拆开，然后搜索时记录有没有到上界或者下界，从高位往低位填数字，填完返回。

## 代码↓


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[20][20][4][4], a[15], b[15], len;
int dfs(int pos, bool limit, bool below, int sum){
    if(!pos) return sum;
    if(dp[pos][sum][limit][below]!=-1) return dp[pos][sum][limit][below];
    int up=limit?a[pos]:9, down=below?b[pos]:0, res=0x3f3f3f3f;
    for(int i=down; i<=up; ++i){
        res=min(res,dfs(pos-1,limit&&i==up,below&&i==down,sum+(i==a[pos])+(i==b[pos])));
    }
    if(!limit&&!below) dp[pos][sum][limit][below]=res;
    return res;
}
int solve(int x, int y){
    len=0;
    while(x&&y){
        a[++len]=x%10; x/=10; 
        b[len]=y%10; y/=10;
    }
    return dfs(len,true,true,0);
}
signed main(){
    memset(dp,-1,sizeof(dp));
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T; cin>>T; while(T--){
        int l, r; cin>>r>>l; cout<<solve(l,r)<<'\n';
    }
    return 0;
}
```

---

## 作者：zhangjizhi (赞：3)

[原题传送门](https://codeforces.com/contest/2121/problem/E)

## 题意
定义函数 $f(x,y)$ 在数字 $x$ 和 $y$ 的十进制表示中，相同数位上数字相同的位数总和。给你 $t$ 组数据，对于每组数据，给定 $l,r$（$1\le l\le r\le 10^9$），求一个数 $x$ 使得 $f(l,x)+f(x,r)$ 最小且 $l\le x\le r$。保证 $l$ 和 $r$ 的位数相等。
## 做法
很巧妙的一道分类讨论题。

设 $a_i$ 为 $l$ 从高到低第 $1$ 到 $i$ 位组成的数字，$b_i$ 为 $r$ 从高到低第 $1$ 到 $i$ 位组成的数字。比如 $l=114514$，$r=191981$，则 $a_3=114$，$b_4=1919$。

我们从最高位开始遍历到最低位。设答案为 $ans$，遍历到第 $i$ 位。
- 如果 $a_i=b_i$，很明显 $x$ 从高到低的第 $1$ 到 $i$ 位只能选择 $a_i$（或 $b_i$）。此时 $ans$ 加 $2$。
- 如果 $b_i-a_i=1$，此时 $x$ 从高到低的第 $1$ 到 $i$ 位要么选择 $a_i$，要么选择 $b_i$。此时 $ans$ 加 $1$。
- 如果 $b_i-a_i\ge 1$，则之后可以任意选，$ans$ 不变。

举个例子：假设 $l=1149111$，$r=1150811$。

当 $i=1$ 时，$a_i=1$，$b_i=1$，$a_i=b_i$，此时 $x$ 的第一位只能为 $1$。由于 $x$ 的第一位与 $l$，$r$ 都相同，所以 $ans$ 加 $2$。

当 $i=2$ 时，与 $i=1$ 时同理。

当 $i=3$ 时，$a_i=114$，$b_i=115$，$b_i-a_i=1$，此时 $x$ 的第三位要么为 $4$，要么为 $5$。无论如何 $x$ 的第三位都与且只与一个数相同，所以 $ans$ 加 $1$。

当 $i=4$ 时，与 $i=3$ 时同理。

当 $i=5$ 时，$a_i=11491$，$b_i=11508$，$b_i-a_i\ge 1$，此时 $x$ 的第五位可取一个数（可以不只一个），使得第五位不与 $l$，$r$ 的第五位相等，很明显，$ans$ 不变。

当 $i=6$ 时，虽然 $l$，$r$ 的第六位相等，但是 $b_i-a_i\ge 1$，所以 $ans$ 依旧不变。

当 $i=7$ 时，与 $i=6$ 时同理。

所以最终 $ans=6$。

## 代码
这部分可能读起来起来比较晕，但看一看代码和例子大概率就能搞清楚了。

[AC记录](https://codeforces.com/contest/2121/submission/330446025)
```cpp
#include<bits/stdc++.h>
#define huan puts("");
using namespace std;
string a,b;//方便遍历
int aa,bb;
int res=0,t;
signed main()
{
	cin>>t;
	while(t--)
	{
		int flag=1;
		cin>>a>>b;
		res=0;
		aa=0,bb=0;//多测要清空
		for(int i=0;i<a.size();i++)
		{
			aa=aa*10+a[i]-'0';//这里不需要储存，所以没有下标。题解中的下标只是为了方便理解。
			bb=bb*10+b[i]-'0';
			if(bb-aa>=2) flag=0;
			if(flag)
			{
				if(a[i]==b[i]) res+=2;
				else res++;
			}
		}
		cout<<res<<'\n';
	}
	return 0;
}
```
希望这篇题解能对你有帮助。

---

## 作者：xiangxiyu (赞：2)

# 思路：
数位顶多只有九位， $t$ 也不是很大，$l$  $r$ 位数一样，赛时写了个类似数位DP的爆搜，就是要注意剪一下枝，同时维护枚举到当前位数时，是否是下限的极限和上限的极限。

# 具体实现（含注释）

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string l,r;
int anser=0x3f3f3f3f;
void dfs(int x,int opt,int opt2,int ans){//当前位数  l有没有到上界   r有没有到上界  当前的代价 
	if (ans >= anser) return;//剪枝  不剪会T   
	if(x==l.size()){
		anser=min(anser,ans);
		return;
	}
	int a1=l[x]-'0';
	int b1=r[x]-'0';
	int up1=0,up2=9;
	if(opt==1) up1=a1;// l 到上界确定当前这一位数的下限 
	if(opt2==1) up2=b1;// r 到上界确定当前这一位数的上限 
	for(int i=up1;i<=up2;i++){
		dfs(x+1,opt&(i==a1),opt2&(i==b1),ans+(i==a1)+(i==b1));//数位DP同款写法 
	}
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		anser=0x3f3f3f3f;
		cin>>l>>r;
		dfs(0,1,1,0);
		cout<<anser<<endl;
	}
}
```

---

## 作者：CommandSR (赞：2)

## 思路

设输入的两个数是 $a$ 和 $b$。

从高位到低位枚举，直到 $a_i \ne b_i$，前面每一位都加上 $2$。

若当前位 $a_i + 1 < b_i$，则只需要当前位填 $a_i+1$，后面每一位都填不一样的即可，不会增加答案。

否则 $a_i + 1 = b_i$，当前位需要在 $a_i$ 和 $b_i$ 间选择。

如果选 $a_i$，且 $a_{i+1} = 9$，则下一位必须填 $9$，会再将答案增加 $1$。如果选 $b_i$，且 $b_{i+1} = 0$，则下一位必须填 $0$，也会再将答案增加 $1$。

所以一直往后枚举每一位，一直到第一个位数 $i$ 满足 $a_i \ne 9$ 或 $b_i \ne 0$ 就跳出循环即可。


## AC Code

```cpp
#include <bits/stdc++.h>
#define F(i, a, b) for (int i = a; i <= b; ++i)
#define _F(i, a, b) for (int i = a; i >= b; --i)
#define ll long long
using namespace std;
ll a[12], b[12], ca, cb, ans = 0, f[12];
void Solve() {
	ll aa, bb; cin >> aa >> bb;
	ca = cb = ans = 0;
	while (aa) {
		a[++ca] = aa % 10;
		aa /= 10;
	}
	while (bb) {
		b[++cb] = bb % 10;
		bb /= 10;
	}
	reverse(a + 1, a + 1 + ca);
	reverse(b + 1, b + 1 + cb);
	ll p = 1;
	while (a[p] == b[p] && p <= ca) ans += 2, ++p;
	if (p > ca) {
		cout << ans << '\n';
		return;
	}
	if ((a[p] + 1) % 10 == b[p]) {
		++ans, ++p;
		while (p <= ca) {
			bool fa = (a[p] == 9);
			bool fb = (b[p] == 0);
			if (!fa) {
				cout << ans << '\n';
				return;
			} else if (!fb) {
				cout << ans << '\n';
				return;
			}
			++p, ++ans;
		}
		cout << ans << '\n';
	} else {
		cout << ans << '\n';
		return;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	ll T; cin >> T; while (T--) Solve();
	return 0;
}
```

---

## 作者：__KevinMZ__ (赞：1)

# [题解：CF2121E Sponsor of Your Problems](https://www.luogu.com.cn/problem/CF2121E)

这题结论题。

## 结论

设 $a,b$ 分别是扫描的“前缀”$l,r$。

- 若 $b-a\ge2$，则直接输出答案。
- 若当前位 $l,r$ 相等，答案 $+2$；
- 若当前位 $l,r$ 不等，答案 $+1$。

# 证明

若 $b-a\ge2$，则从此以后的每一位都可以不同于 $l,r$ 当前位。

- 若前面扫描出的 $l,r$ 不等，则当前位 $x$ 可取任意值。
- 若 $r$ 当前位 $-l$ 当前位 $\ge 2$，则 $x$ 当前位取中间的值。

这两种情况我都构造出了不做贡献的情况。

则直接输出答案。

若当前位 $l,r$ 相等，$x$ 当前位也只能取 $l,r$ 当前位，答案 $+2$；
若当前位 $l,r$ 不等，则 $l,r$ 当前位差 $1$，则 $x$ 当前位只能取 $l,r$ 当前位中的一个，答案 $+1$。

$\text{QED!}$

## 代码

```cpp
#include<bits/stdc++.h>
#define ONLINE_JUDGE
using namespace std;
int t;
signed main(){
#ifndef ONLINE_JUDGE
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	cin>>t;
	while(t--){
		string a,b;
		int s=0,r=0,ans=0;
		cin>>a>>b;
		for(int i=0;i<a.size();i++){
			s*=10,r*=10;
			s+=a[i]-'0',r+=b[i]-'0';
			if(r-s>=2)
				break;
			if(a[i]==b[i])
				ans++;
			ans++;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：songhy_QWQ (赞：1)

## CF2121E Sponsor of Your Problems
[**题目传送门**](https://codeforces.com/contest/2121/problem/E)
### Solution
对于两个整数 $a$ 和 $b$，我们定义 $f(a,b)$ 为在 $a$ 和 $b$ 的十进制表示中，数字相同的位数。考虑所有满足 $a≤x≤b$ 的整数 $x$，你的任务是找到 $f(a,x)+f(x,b)$ 的最小值。\
  对于这个问题，我们可以将数位拆分开求解，即将**数字转化为字符串**。分三种情况：
1. 数位相同，改变不了 $x$ 在这一位上的取值，`ans+=2`。
2. 位数差距大于等于 $2$，后面的数位怎么改都可以，直接`break`。
3. 数位差距等于 $1$，只能改后面的，将两个字符串进行`while`循环，不难发现：小的数每一位数在遇到**非 $9$ 数**之前都会产生为 $1$ 的代价；大的数每一位数在遇到**非 $0$ 数**之前都会产生为 $1$ 的代价。
### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string a,b;
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b;
		int ans=0;
		for(int i=0;i<a.size();i++){
			if(a[i]==b[i]){
				ans+=2;//若这一位上的数相同，改不了ans+2 
			}
			else if(abs(a[i]-b[i])>=2){
				break;//差距大于等于2，后面的都随便选择 
			}
			else{//差距刚好1 
				int mi=20,pos=i+1;
				while(pos<a.size()&&a[pos]=='9')pos++;
				mi=min(mi,pos-i);
				//小的数每一位数在遇到非9数之前都会产生代价 
				pos=i+1;
				while(pos<b.size()&&b[pos]=='0')pos++;
				mi=min(mi,pos-i);
				//大的数每一位数在遇到非0数之前都会产生代价 
				ans+=mi;
				break;
			}
		} 
		cout<<ans<<endl;
	}
} 
```

_**~~完结撒花~~**_  ^_^

---

## 作者：nydry (赞：0)

# 题意
对于正整数 $a$ 和 $b$，定义 $f(a,b)$ 表示 $a$ 和 $b$ 在十进制表示下数字相同的有几位。题目保证调用时 $a$ 和 $b$ 的总位数相等。给出 $T$ 组询问，每次给定 $l$ 和 $r$，求 $f(l,x)+f(x,r)$ 的最小值，其中 $l\le x \le r$，保证 $l$ 和 $r$ 的总位数相等。

# 做法
从高位往低位考虑，假设当前在第 $i$ 高的位，且更高的位上 $l$ 和 $r$ 相等。分以下三种情况：

1. 这一位上 $l$ 和 $r$ 仍然相等。此时 $x$ 在这一位上只有一种选择，答案加二。

2. 这一位上 $l$ 和 $r$ 不相等，且差值至少为 $2$。此时 $x$ 可以在这一位上选择一个在中间的数，更低位可以随便选，所以不会再有答案了，结束。

3. 这一位上 $l$ 和 $r$ 不相等，且差值为 $1$。$x$ 可以选择取两个值中的一个。如果选择较小者，则在 $l$ 出现非 $9$ 的数字之前，都会有贡献。同理，选择较大者会在 $r$ 出现非 $0$ 的数字之前有贡献。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void solve(){
	string l,r;
	cin>>l>>r;
	int res=0;
	for(int i=0;i<l.length();i++){
		if(l[i]==r[i])res+=2;
		else if(l[i]+1==r[i]){
			int tmp=0x3f3f3f3f;
			int pos=i+1;
			while(pos<l.length()&&l[pos]=='9')pos++;
			tmp=min(tmp,pos-i);
			pos=i+1;
			while(pos<r.length()&&r[pos]=='0')pos++;
			tmp=min(tmp,pos-i);
			res+=tmp;
			break;
		}
		else{
			break;
		}
	}
	cout<<res<<"\n";
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tt;
	cin>>tt;
	while(tt--)solve();
	return 0;
}
```

---

## 作者：exCat (赞：0)

首先，因为只有两个数，所以如果一旦没有上下界的限制，就可以保证后面都不会有贡献。所以我们可以思考最早什么时候没有限制。从高到低位枚举分讨即可。

- 如果当前位 $r-l>1$，选择 $[l+1,r-1]$ 之间的任何数都可以不受限制，直接退出。
- 如果 $r=l$，没得选答案加二。
- 如果 $r=l+1$，这种情况是本题的难点。我们发现当且一定答案加一，我们可以选 $l$ 接下来保证下界或者选 $r$ 接下来保证上界，但是现在不知道选什么，所以先放着，往后看。
  - 如果接下来的位上 $r=0,l=9$ 我们发现不管上一位选什么这一位都必须压着边界，答案一定加一。但是我们还是不知道选什么，所以只能往后看。
  - 如果 $r\ne 0$ 或 $l\ne 9$，就一定可以前面顶上界当前选 $x<r$ 或前面顶下界当前选 $x>l$ 不受限制且不会对答案做贡献，直接退出。 

代码模拟上面的思路即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=20;
char l[N],r[N];
void solve()
{
	cin>>l>>r;
	int n=strlen(l),ans=0,flag=0;
	for(int i=0;i<n;i++)
	{
		int x=l[i]-'0',y=r[i]-'0';
		if(!flag)
		{
			if(y-x>1)break;
			if(x==y)ans+=2;
			else ans+=1,flag=1;
		}
		else
		{
			if(x==y)break;
			if(y!=0||x!=9)break;
			ans++;
		}
	} 
	cout<<ans<<'\n';
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--)solve();
	return 0;
 } 
```

---

## 作者：postpone (赞：0)

> 思路来自 [capps 老师](https://codeforces.com/profile/Capps)。

要找 $f(l, x) + f(x, r)$ 的最小值，不妨分为两部分处理。

- 首先是 $l$ 和 $r$ 的最长公共前缀，因为 $x$ 的选取要在两者之间，因此这部分不得不产生贡献。

- 然后是后面的部分，似乎 $x$ 可以乱取让后面的部分不产生任何贡献，但有一些特殊情况。

  - 例如 $l=11$，$r=12$，$x$ 的个位要么取 $1$ 要么取 $2$，都会产生 $1$ 个贡献。
 
  - 例如 $l=119999$，$r=120000$，在公共前缀之后，每一位仍然产生 $1$ 个贡献。
 
  - 但如果 $l=119934$，$r=120073$，最后两位就不会产生贡献。
 
  可以发现由于进位的原因，我们在取完最长公共前缀之后，还需要判定两个东西：最长公共前缀之后的一位，是不是只相差 $1$？如果是，紧接着有多少连续的位置满足 $l_i=9$ 和 $r_i=0$？

按照上面两步走，这道题就做出来了。

```cpp
void solve() {
    string l, r;
    cin >> l >> r;

    const int n = l.size();

    int i = 0, ans = 0;
    for (; i < n; i++) {
        if (l[i] == r[i]) {
            ans += 2;
        } else {
            break;
        }
    }

    if (i < n and r[i] - l[i] == 1) {
        ans++;
        i++;
        while (i < n and l[i] == '9' and r[i] == '0') {
            ans++;
            i++;
        }
    }
    cout << ans << "\n";
}
```

---

