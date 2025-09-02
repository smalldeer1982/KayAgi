# [GCJ 2011 #1A] FreeCell Statistics

## 题目描述

我今天玩了 $D$（$D > 0$）局 FreeCell。每局 FreeCell 的结果只有两种——要么我赢了，要么我输了。我已经玩了很多年，到目前为止总共玩了 $G$ 局（显然 $G \geq D$）。

一天结束时，我查看游戏统计数据，看看自己表现如何。结果发现，今天的 $D$ 局中，我赢了恰好 $P_D$ 百分比的局数，而在我玩过的所有 $G$ 局中，我赢了恰好 $P_G$ 百分比的局数。令人惊奇的是，这两个百分比都是精确的，没有任何四舍五入！不幸的是，我不记得今天具体玩了多少局（$D$），也不记得总共玩了多少局（$G$）。我只知道今天玩的局数不会超过 $N$（即 $D \leq N$）。

请判断，这两个百分比是否可能出现，还是游戏统计计算器出错了？

## 说明/提示

**样例解释**

在第 3 个样例中，我今天可能玩了 $5$ 局（$D = 5$），总共玩了 $25$ 局（$G = 25$），今天赢了 $4$ 局（$5$ 的 $80\%$），总共赢了 $14$ 局（$25$ 的 $56\%$）。

**限制条件**

- $0 \leq P_D \leq 100$；
- $0 \leq P_G \leq 100$。

**小数据集（6 分，测试集 1 - 可见）**

- $1 \leq T \leq 100$；
- $1 \leq N \leq 10$。
- 时间限制：3 秒。

**大数据集（14 分，测试集 2 - 隐藏）**

- $1 \leq T \leq 2000$；
- $1 \leq N \leq 10^{15}$。
- 时间限制：6 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 100 50
10 10 100
9 80 56```

### 输出

```
Case #1: Possible
Case #2: Broken
Case #3: Possible```

# 题解

## 作者：qkj_qwq (赞：3)

## 解题思路

分类讨论。

- 当 $P_G=100$ 且 $P_D\ne100$ 时，即总共全部都赢了，但是今天没有全部都赢，不可能，输出 `Broken`；
- 当 $P_G=0$ 且 $P_D\ne0$ 时，即总共一次都没有赢，但是今天赢了，不可能，输出 `Broken`；
- 今天玩的最少次数 $D=\dfrac{100}{\gcd(100,P_D)}$（因为题目说 $P_D$ 为精确值，所以玩一场游戏的占比至多为 $\dfrac{\gcd(100,P_D)}{100}$，玩的次数为玩一场游戏的占比的倒数），题目说 $D\le N$，所以当 $D > N$ 时不可能，输出 `Broken`，否则输出 `Possible`；
- 至于 $G\ge D$，由于 $G$ 没有多少的限制，所以可以无限增加（他不累吗），所以成立，输出 `Possible`。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++)
	{
		cout<<"Case #"<<tt<<": ";
		int n,m,k;
		cin>>n>>m>>k;
		if(k==100&&m!=100
		 ||k==0&&m
		 ||100/__gcd(100ll,m)>n)cout<<"Broken\n";
		else cout<<"Possible\n";
	}
	return 0;
}
```

---

## 作者：zhangruiyi0117 (赞：1)

#### 题意说明
本题有 $T$ 个测试数据，每个数据有三个整数： $N,P_D,P_G$ 。   
 $N$ ：指今天最多玩了 $N$ 次游戏。  
 $P_D$ ：指今天游戏的胜利百分比（准确数）。  
 $P_G$ ：指总胜利百分比（准确数）。

每个测试点都在询问这种情况是否存在。

#### 解题思路
我们可以**分类讨论**这一道题：

- 当 $P_G$ 为 $0$ 时，说明他玩这个游戏从始至终都没有赢过，那么这时如果 $P_D>0$ ,说明他今天至少赢了一局，矛盾，输出`Broken` ，否则输出`Possible`。
- 当 $P_G$ 为 $100$ 时，说明他玩这个游戏从始至终都没有输过，那么这时如果 $P_D<100$ ,说明他今天至少输了一局，矛盾，输出`Broken` ，否则输出`Possible`。
- 当 $P_G>0$ 且 $P_G<100$ 时，这时候 $D$ 的最小值为 $\frac{100}{\gcd(100,P_D)}$ ，当 $D>N$ 时，输出`Broken` ，否则输出`Possible`。

#### 最终代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,pd,pg;
bool check(int n,int pd,int pg) {
	if(pg==0&&pd>0) return false;
	else if(pg==100&&pd<100) return false;
	else {
		int d=100/__gcd(pd,100ll);
		if(d>n) return false;
	}
	return true;
}
signed main() {
	scanf("%lld",&t);
	for(int i=1; i<=t; i++) {
		scanf("%lld%lld%lld",&n,&pd,&pg);
		printf("Case #%lld: ",i);
		if(check(n,pd,pg)) printf("Possible\n");
		else printf("Broken\n");
	}
	return 0;
}

```

---

## 作者：Const_ (赞：1)

## 题目分析：
大体思路很好想，这里给一个严谨证明吧。

这个题实际上有三个约束：

设总胜场为 $k$。

**约束1:（由每日的胜局是正整数推出）**

$D\times P_{D}\div {100} = k$，其中 $k\in N$。

故 $D=k\times 100\div P_{D}=k\times \dfrac{100}{\gcd(100,p_{D})}\div \dfrac{P_{D}}{\gcd(100,p_{D})}$。
根据 $\gcd$ 的定义，除号右边大于 $1$ 且与除号左边互质，所以要想使得 $D\in N$，$k$ 最小取 $\dfrac{P_{D}}{\gcd(100,p_{D})}$。此时 $D$ 取得最小非负整数解 $\dfrac{100}{\gcd(100,p_{D})}$。

故该条件转化为 $\dfrac{100}{\gcd(100,p_{D})}\leq N$。

**约束2:（由总胜局是正整数推出）**

设总胜场为 $r$。

$G\times P_{G}\div {100} = r$，其中 $r\in N$。

这个约束就很弱了，因为 $G$ 可以取足够大的 $100$ 的倍数使得 $k$ 是整数，从而总胜场也足够大。

**约束3:（特判）**

因为每天的胜场是总胜场的子集，所以：

- 若总对局里全胜，则今天不可能有负场。

- 若总对局里全负，则今天不可能有胜场。

翻译一下就是若 $P_{G}=0$，则 $P_{D}=0$，若 $P_{G}=100$，则 $P_{D}=100$。

## AC code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,i,n,d,g;
ll gcd(ll x,ll y)
{
    return !y?x:gcd(y,x%y);
}
bool check()
{
	if(g==0) return (d==0);
	if(g==100) return (d==100);
	return 100/gcd(100,d)<=n;
}
int main()
{
	cin>>t;
	for(i=1;i<=t;i++)
	{
		cin>>n>>d>>g;
		cout<<"Case #"<<i<<": "<<(check()?"Possible\n":"Broken\n");
	}
	return 0;
}
```

---

## 作者：chenzhuole1 (赞：1)

## 题解：P13365 [GCJ 2011 #1A] FreeCell Statistics

[题目链接](https://www.luogu.com.cn/problem/P13365)

### 思路

首先分类讨论：

当今日胜率 $P_D$ 为 $0\%$ 时，总局胜率 $P_G$ 不能是 $100\%$，因为今日至少玩了一局且全输；

当 $P_D$ 为 $100\%$时，$P_G$ 不能是 $0\%$，因为今日至少赢了一局。

对于 $1\%-99\%$ 的情况，需要计算最小可能的 $D$ 值，若这个最小 $D$ 超过 $N$ 则不可能。此外，$P_G$ 不能为 $0\%$ 或 $100\%$，否则会导致矛盾。

最后输出判断结果。

### Code


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,pd,pg;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    for(int cas=1;cas<=t;cas++){
        cin>>n>>pd>>pg;
        cout<<"Case #"<<cas<<": ";
        if(pd==0){
            if(pg!=100)cout<<"Possible\n";
            else cout<<"Broken\n";
        }
        else if(pd==100){
            if(pg!=0)cout<<"Possible\n";
            else cout<<"Broken\n";
        }
        else{
            int g=__gcd(pd,100ll);
            int d=100/g;
            if(d>n)cout<<"Broken\n";
            else{
                if(pg!=0&&pg!=100)cout<<"Possible\n";
                else cout<<"Broken\n";
            }
        }
    }
    return 0;
}
```

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13365)

# 题目分析

首先，如果 $P_G=100$ 且 $P_D\ne 100$ 或 $P_G=0$ 且 $P_D\ne 0$，则一定出错了。

其次，设 $\frac{P_D}{100}$ 约分后为 $\frac{p}{q}$，其中 $p$ 和 $q$ 互素，若 $q>N$ 则必然出错。因为 $p\times D$ 是 $q$ 的倍数，$p$ 和 $q$ 互素，因此 $D$ 是 $q$ 的倍数，所以 $D>q>N$，与条件 $D\le N$ 矛盾。

若上述两条都不满足，则设 $x$ 为除了今天以外游戏总局数，$y$ 为除今天以外游戏中输的局数，则 $G=D+x$，赢的总局数为 $D\times \frac{P_D}{100}+x-y$。因此可以列出方程

$$\frac{D\times \frac{P_D}{100}+x-y}{D+x}=\frac{P_G}{100}$$

变形得

$$ P_D\times D+100x-100y=P_G\times D+P_Gx$$
$$(100-P_G)x-100y=D\times (P_G-P_D)$$

因此要求该方程有正整数解。首先考虑整数解，由裴蜀定理可得 $D\times (P_G-P_D)$ 是 $(100-P_G,100)$ 的倍数。设 $D=kq$（$q$ 的定义见上文第二段）。设 $\frac{q\times (P_G-P_D)}{(100-P_G,100)}$ 约分后为 $\frac{a}{b}$，则 $\frac{ka}{b}$ 为整数，因此 $b$ 整除 $k$。由于 $D\le N$，不妨令 $k=b$，此时 $D$ 最小。若此时 $D>N$，则是出错了。

下面考虑正整数解。设上面的方程有整数解 $(x_0,y_0)$，则该方程的所有解为 $(x_0+100t,y_0+(100-P_G)t)$，其中 $t$ 为任意整数。显然，由于 $100$ 与 $100-P_G$ 均为正数，所以只要选择恰当的 $t$，就一定能找到正整数解。

根据上面的分析即可解题。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long gcd(long long a,long long b){
    if(b==0){
        return a;
    }
    return gcd(b,a%b);
}
int main(){
    int t;
    cin>>t;
    for(int o=1;o<=t;o++){
        cout<<"Case #"<<o<<": ";
        long long n;
        long long pd,pg;
        cin>>n>>pd>>pg;
        long long g1=gcd(100,pd);
        if(100/g1>n){
            cout<<"Broken"<<endl;
            continue;
        }
        if(pg==100&&pd!=100){
            cout<<"Broken"<<endl;
            continue;
        }
        if(pg==0&&pd!=0){
            cout<<"Broken"<<endl;
            continue;
        }
        long long g=gcd(100,100-pg);
        if((pg-pd)*(100/g1)%g==0){
            cout<<"Possible"<<endl;
            continue;
        }
        else{
            long long g0=gcd((pg-pd)*(100/g1),g);
            long long t=g/g0;
            if(t*(100/g1)<=n){
                cout<<"Possible"<<endl;
                continue;
            }
        }
        cout<<"Broken"<<endl;
    }
    return 0;
}
```

---

## 作者：xtzhangziche (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13365)

## 思路
我们需要判断是否存在满足条件的 $D$ 和 $G$，使得：

- $D \leq N$（今天玩的局数不超过 $N$）。

- $\dfrac{D \times P_D}{100}$ 是整数（今天赢的局数为整数）。

- $\dfrac{G \times P_G}{100}$ 是整数（总赢的局数为整数）。

- $G \geq D$（总局数不少于今天玩的局数）。

`Broken` 的情况，直接排除以下不可能的情况：

- $P_G = 0$ 且 $P_D > 0$（总胜率为 $0\%$ 时，今天不可能有正胜率）。

- $P_G = 100$ 且 $P_D < 100$（总胜率为 $100\%$ 时，今天不可能有非全胜）。

- 最小 $D > N$（今天玩的局数不可能超过 $N$）。

求最小 $D$ 的方法。
我们需要找到最小的 $D$ 使得 $D \times P_D \equiv 0 \pmod{100}$。

设 $g = \gcd(P_D, 100)$。

设 $k$ 和 $m$。

分解：

$P_D = g \times k$。

$g \times m = 100$。

其中 $\gcd(k, m) = 1$（$k$ 和 $m$ 互质）。

最小 $D$ 必须满足 $D \times k \equiv 0 \pmod{m}$。

因为 $\gcd(k, m) = 1$，所以 $D$ 必须是 $m$ 的倍数。

因此，最小 $D = m = \dfrac{100}{g}$。

若 $P_G = 0$ 且 $P_D > 0$，或 $P_G = 100$ 且 $P_D < 100$，或 $\dfrac{100}{\gcd(P_D, 100)} > N$，则输出 `Broken`。

否则输出 `Possible`。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,t;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>T;
    while(T--)
    {
        int n,pd,pg;
        cin>>n>>pd>>pg;
        int d=100/__gcd(pd,100ll);
        cout<<"Case #"<<++t<<": ";
        if((pg==0&&pd>0)||(pg==100&&pd<100)||(d>n)) cout<<"Broken";
        else cout<<"Possible";
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：liuyuantao (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13365)  
我们在以下用 $p_D$ 表示 $P_D\%$，$p_G$ 表示 $P_G\%$。  
分析题目，我们可以得到两个条件：  
* 总局数不少于今日局数，即 $0<D \le G$。
* 今日局数不超过 $N$，即 $D \le N$。

进一步分析得：  
* 总胜场**不少于**今日胜场。即 $D \times p_D \le G \times p_G$。
* 总负场**不少于**今日负场。即 $D \times (1-p_D) \le G \times (1-p_G)$。
* $D \times p_D$，$G \times p_G$ 为**整数**。

我们依次分析输出 ```Broken``` 的条件。不妨令 $p_D=\frac{k}{q}(q,k$ **互质**且 $q,k$ 为正整数 $)$。由 $D \times p_D$ 为整数可知 $q \mid D$（即 $q$ 整除 $D$）。为了让 $D \le N$ 成立，我们应求出**最小**的 $D$（不然它都比 $N$ 大比它大的肯定更大）。显然最小的 $D=q$。于是第一个判断条件为 $q > N$。这一步用 $\gcd$ 约分即可。  
之后我们发现 $G$ 的值**没有限制**，可以随意调整。我们为了尽可能满足后两个不等式，假定 $G$ 足够大且 $G \times p_G$ 为整数。考虑倒数第二个不等式。易得 $G \times p_G \ge 0$，当且仅当 $p_G=0$ 时取等，否则其值足够大。而 $p_D=0$ 时原不等式取等号成立，故不成立的条件即为 $p_D \ne 0$ 且 $p_G =0$。  
最后一个不等式推理过程类似（读者可自证），最终条件即为 $p_D<1$ 且 $p_G=1$。  
由于满足其一即可，故用或来判断。记得将 $p_D,p_G$ 和 $P_D,P_G$ 转换，注意输出格式。  
时间复杂度 $O(T)$。  
[AC code](https://www.luogu.com.cn/record/225947234)  

```cpp
#include <bits/stdc++.h>

using namespace std;

#define LL long long
#define min(mina,minb) ((mina<minb)?(mina):(minb))

const int N=1e3+5;

string s;
LL T,n,m,k,cnt,ans,gf,inf=1e16;
int fx[5]={0,-1,1,-1,1},gx[5]={0,-1,-1,1,1};
char c;

LL gcd(LL x,LL y){
	if(x<y)swap(x,y);
	if(!y)return x;
	return gcd(y,x%y);
}

int main(){
	ios::sync_with_stdio(0);
	cin>>T;
	for(int ap=1;ap<=T;ap++){
		cin>>n>>m>>k;
		cnt=100/gcd(m,100);
		if(cnt>n||(k==0&&m>0)||(k==100&&m<100)){
			cout<<"Case #"<<ap<<": Broken"<<endl;
		}
		else{
			cout<<"Case #"<<ap<<": Possible"<<endl;
		}
	}
	
	
	
	return 0;
}
```

---

