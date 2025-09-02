# Snow Walking Robot

## 题目描述

有一个机器人，站在一个平面直角坐标系上，开始时他的坐标为$(0,0)$

给出一个指令序列$s$，它只由`L`,`R`,`U`,`D` 四个大写字母组成  
若机器人当前坐标为$(x,y)$  
- 如果当前字母为 `L`，那么机器人就会向左移动到$x-1,y$  
- 如果当前字母为 `R`，那么机器人就会向右移动到$x+1,y$  
- 如果当前字母为 `U`，那么机器人就会向上移动到$x,y+1$  
- 如果当前字母为 `D`，那么机器人就会向下移动到$x,y-1$

如果一个坐标的点被走过了两次（除$(0,0)$外），那么机器人就会爆炸  
一个操作序列合法，当且仅当中途机器人不会爆炸，并且满足指令序列结束时，机器人的坐标为$(0,0)$（也就是最后回到原点）  
当然，空指令序列也是合法的

我们发现，所有的指令序列不一定都合法

给出一个指令序列$s$，你的任务是通过删除指令和重排序列，让指令序列合法，并且满足删除的指令数最小

## 说明/提示

$1 \le q \le 2\cdot 10^4$，$\sum|s| \le 10^5$  
其中$|s|$为字符串$s$的长度  
感谢 @_Wolverine 提供的翻译

## 样例 #1

### 输入

```
6
LRU
DURLDRUDRULRDURDDL
LRUDDLRUDRUL
LLLLRRRR
URDUR
LLL
```

### 输出

```
2
LR
14
RUURDDDDLLLUUR
12
ULDDDRRRUULL
2
LR
2
UD
0

```

# 题解

## 作者：woshishei (赞：3)

注意到题目中只需要给出任意一种排列，这样就可以用到贪心的思想。不难想出，只需要**让机器人走出一个长、宽都尽量大的矩形**，就可以使每个点（原点除外）都满足被访问不超过$2$次，且终点位于原点。

具体来说，选择矩形的原因是“凹”形（下图左半部分）相比于与其效果相同的矩形，浪费了两个$AB$的长度。而“凸”形（下图右半部分）等价于虚线的矩形，而矩形比“凸”形简单，所以选择矩形。

![](https://cdn.luogu.com.cn/upload/image_hosting/xmg2vnyy.png)

然后可以选择任意一个可以构成矩形的移动顺序（$\text{L}\rightarrow \text{R}\rightarrow \text{U}\rightarrow \text{D}$不是一个可以构成矩形的移动顺序）。下图是$\text{L}\rightarrow \text{U}\rightarrow \text{R}\rightarrow \text{D}$的顺序。

![](https://cdn.luogu.com.cn/upload/image_hosting/upgifjef.png)

让矩形的长、宽尽量大，只要取`L`的个数与`R`的个数的最小值作为长，取`U`的个数与`D`的个数的最小值作为宽即可。

注意，如果矩形的长和宽中如果至少有一个为$0$，另一个不管有多少，都最多移动一格（即`LR`或`UD`）。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define debug printf("\n-------------\n")
using namespace std;
typedef long long ll;
const int INF1=(~0u>>2);
const ll INF2=(~0ull>>2),P1=10007,P2=998244353,P3=1000000007;
int len,l,r,u,d;//l,r,u,d分别为L,R,U,D的个数
char s[100010];
void solve()
{
	scanf("%s",s+1);
	len=strlen(s+1);
	l=r=u=d=0;
	for(int i=1;i<=len;i++)
		switch(s[i])
		{
			case 'L':l++;break;
			case 'R':r++;break;
			case 'U':u++;break;
			case 'D':d++;break;
			default:break;
		}
	l=min(l,r);
	r=min(l,r);
	u=min(u,d);
	d=min(u,d);//把l,r都取为原先l与r的最小值；把u,d都取为原先u与d的最小值
	if(l==0)//只能移动一格的情况
	{
		printf(u>0?"2\nUD\n":"0\n\n");
		return;
	}
	if(u==0)
	{
		printf(l>0?"2\nLR\n":"0\n\n");
		return;
	}
	printf("%d\n",l+r+u+d);
	for(int i=1;i<=l;i++)//l->R->U->D的顺序
		printf("L");
	for(int i=1;i<=u;i++)
		printf("U");
	for(int i=1;i<=r;i++)
		printf("R");
	for(int i=1;i<=d;i++)
		printf("D");
	printf("\n");
}
int main()
{
	int q;
	scanf("%d",&q);
	while(q--)
		solve();
	return 0;
}
```

---

## 作者：piggy123 (赞：1)

一道挺有意思的贪心题。

对于一个操作序列 $s$ ，我们定义其中 $L$ 的数量为    $cntl$ ， $R$ 的数量为 $cntr$ ， $U$ 的数量为 $cntu$ ， $D$ 的数量为 $cntd$ 。

首先根据题意不难想出仅当 $cntl==cntr$ 与 $cntu==cntd$ 时可以回到原点，题目要求长度最大，又只支持删除操作，所以将他们都置为两者之间**最小值**即可。

接下来满足每个点不被重复经过，一个很显然的结论是走成一个矩形可以满足这个条件，即先输出 $cntu$ 个 $U$ ，再输出 $cntl$ 个 $L$ ，再输出 $cntd$ 个 $D$ ，最后输出 $cntr$ 个 $R$ 。

特殊情况是，当 $cntu$ 和 $cntd$ 为 $0$ 时，$cntl$ 与 $cntr$ 只能为 $1$ ，反之，对于 $cntr$ 和 $cntl$ 为 $0$ 的情况依然如此。

另外：建议此题评橙或黄。

AC Code：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;


int main(){
	ll n;
	cin >> n;
	while(n--){
		string s;
		ll u=0,d=0,r=0,l=0;
		cin >> s;
		for (ll i=0;i<s.length();i++){
			if (s[i]=='U')u++;
			if (s[i]=='D')d++;
			if (s[i]=='R')r++;
			if (s[i]=='L')l++;
		}
		u=d=min(u,d);
		r=l=min(r,l);
		if (r==0&&l==0&&u>1){
			u=d=1;
		}
		if (u==0&&d==0&&l>1){
			l=r=1;
		}
		cout << u+r+d+l << endl;
		for (ll i=0;i<u;i++){
			cout << 'U';
		}
		for (ll i=0;i<r;i++){
			cout << 'R';
		}
		for (ll i=0;i<d;i++){
			cout << 'D';
		}
		for (ll i=0;i<l;i++){
			cout << 'L';
		}
		cout << endl;
	}
	return 0;
}
```


---

## 作者：pyz51 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1272B)

[CodeForces](https://codeforces.com/problemset/problem/1272/B)

[AC 记录](https://codeforces.com/contest/1272/submission/278223511)

不是，这个 CF 的题交不了很烦。
# 题解
由于题目要求不能重复走，并且走完一圈要返回原点，可以自然而然地想到走一个矩形。  
但是原本路线不一定是矩形，我们先考虑路线是封闭图形（能走回原点）：
## 第一种：

 ![](https://cdn.luogu.com.cn/upload/image_hosting/eudedkbw.png)

 可以**转换**为：

 ![](https://cdn.luogu.com.cn/upload/image_hosting/cqo7yyp2.png)
 
## 第二种：

 ![](https://cdn.luogu.com.cn/upload/image_hosting/nxabqgz1.png)

 可以**转换**为：

 ![](https://cdn.luogu.com.cn/upload/image_hosting/vhvtjkj0.png)

路线是非封闭图形也很好处理，由于矩形两长相等，两宽相等，因此仅需**长取 L，R 出现次数的最小值，宽取 U，D 出现次数的最小值即可**。  
接下来就可以输出啦！
# 特判
**当没有 U 或 D 时只能输出一个 L 和 R。**  
**当没有 L 或 R 时只能输出一个 U 和 D。**
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
map<char,int> mp;
int t;
int main(){
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        mp.clear();
        int l,r,u,d;
        for(int i=0;i<s.size();i++) mp[s[i]]++;
        l=r=min(mp['L'],mp['R']);
        u=d=min(mp['U'],mp['D']);
        if(u==0&&l!=0) l=r=1;
        if(l==0&&u!=0) u=d=1;
        cout<<l+r+u+d<<'\n';
        for(int i=0;i<l;i++) cout<<"L";
        for(int i=0;i<u;i++) cout<<"U";
        for(int i=0;i<r;i++) cout<<"R";
        for(int i=0;i<d;i++) cout<<"D";
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：zhu_wen (赞：0)

# Snow Walking Robot
## [原题传送门](https://codeforces.com/problemset/problem/1272/B)
## 题目意思
尽可能少的删除无效或重复指令，并重新排列指令，让指令序列合法，使机器人从原点出发，最后回到原点，并且在过程中不能重复经过某个点。
## 思路
本题就是通过一个**模拟**的思想来进行做题，遍历字符串，根据题目描述，将上下左右进行模拟，将变量进行累加。

根据题目描述，我们可以让机器人走一个矩形，最终走到原点。
#### 特殊情况
- 当指令中只出现 $\texttt L$ 和 $\texttt R$ 时或者只出现 $\texttt U$ 和 $\texttt D$ 时，我们就只输出 $\texttt {LR}$ 或 $\texttt {UD}$。

- 否则这几种情况都不满足，那么没有指令，输出 $ \text 0$。


## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
#define re register
#define swap(a, b) a ^= b, b ^= a, a ^= b
#define pb push_back
#define all(x) x.begin(), x.end()
#define fst                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);
typedef pair<int, int> PII;
const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int Max = 1e3 + 5;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;
int q;
signed main()
{
    fst;
    cin >> q;
    while (q--)
    {
        string s;
        int l = 0, r = 0, u = 0, d = 0; // 赋初值为0
        cin >> s;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == 'U')
                u++;
            if (s[i] == 'D')
                d++;
            if (s[i] == 'L')
                l++;
            if (s[i] == 'R')
                r++;
        }
        l = r = min(l, r); // 判断左右
        u = d = min(u, d); // 判断上下
        // 特判上下，不为0的情况
        if (u == 0 && d == 0 && l > 1)
        {
            l = r = 1;
        }
        // 特判左右，不为0的情况
        if (l == 0 && r == 0 && u > 1)
        {
            d = u = 1;
        }
        // 有效数量就是l+r+u+d
        cout << l + r + d + u << endl;
        for (int j = 0; j < l; j++)
        {
            cout << "L";
        }
        for (int j = 0; j < u; j++)
        {
            cout << "U";
        }
        for (int j = 0; j < r; j++)
        {
            cout << "R";
        }
        for (int j = 0; j < d; j++)
        {
            cout << "D";
        }
        cout << endl;
    }
    return 0;
}
```
## AC
![](https://cdn.luogu.com.cn/upload/image_hosting/wsklem4h.png)

---

## 作者：封禁用户 (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/snow-walking-robot-de-ti-jie/)
# 题目大意
给你一个机器人和机器人的 $n$ 个运动，要求你在给出的运动路径的基础上设计一种不会走重复的路径的方法，注意只能减少原来的步数而不能增加，其中 $1\le n\le 10^5$。
# 思路
因为这道题目可以自由的配置路径并且要求机器人在最后回到原来的位置，那么就应该要到一种适合所有的移动步数的方法。

![](https://espresso.codeforces.com/b8d040c328a3c50a5e36b8d6da86a6e5f2b67b52.png)

我们可以将所有的移动进行平移操作，把路径移动成下面这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/lkarb3be.png)

这样，对于所有的移动，在知道了步数之后，就可以用 $O(4\times n)$ 的时间快速输出了，$n$ 为边长。

因为题目给出的操作只能删除，而且要求回到最初的位置，所以向上、向下和向左、向右的数量应该就是一样的了，所以应该取最小值。

但是有一些特殊情况需要特判一下：当向上、向下或者向左、向右的数量有一个是 $0$ 的时候并不是不可以的，要注意向左紧接着向右或者向上之后紧接着向下也是合法的。

# AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,s[5];
char a[N];
void solve(){
	memset(s,0,sizeof(s));
	int ans=0;
	cin>>a+1,n=strlen(a+1);
	for(int i=1;i<=n;i++){
		if(a[i]=='R') s[1]++;
		if(a[i]=='D') s[2]++;
		if(a[i]=='L') s[3]++;
		if(a[i]=='U') s[4]++;
	}ans+=min(s[1],s[3])*2;
	ans+=min(s[2],s[4])*2;
	if(min(s[1],s[3])==0&&min(s[2],s[4])==0){puts("0\n");return;}
	if((min(s[1],s[3])==0)||(min(s[2],s[4])==0)){
		if(min(s[1],s[3])==0) cout<<"2\nDU\n";
		if(min(s[2],s[4])==0) cout<<"2\nLR\n";
		return;
	}
	cout<<ans<<endl;
	for(int i=1;i<=min(s[1],s[3]);i++) cout<<'R';
	for(int i=1;i<=min(s[2],s[4]);i++) cout<<'D';
	for(int i=1;i<=min(s[1],s[3]);i++) cout<<'L';
	for(int i=1;i<=min(s[2],s[4]);i++) cout<<'U';
	puts("");
	
}signed main(){
	int T;cin>>T;
	while(T--) solve();
	return 0;
}
```

---

