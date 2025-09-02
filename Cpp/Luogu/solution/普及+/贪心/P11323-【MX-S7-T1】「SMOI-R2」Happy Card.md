# 【MX-S7-T1】「SMOI-R2」Happy Card

## 题目背景

原题链接：<https://oier.team/problems/S7A>。

## 题目描述

LLL 在 NOIP 前想愉悦身心，于是设计了一个有趣的纸牌游戏。

该游戏中有 $n$ 种不同的牌，编号为 $1,2,\dots,n$，第 $i$ 种牌有 $v_i$ 张。

总共有四种出牌方法：

- **单牌**：出一张单牌。
- **对子**：出两张同种的牌。
- **炸**：出四张同种的牌。
- **三带一**：出三张同种的牌和一张不同种的牌。

当出完所有牌后即可获得游戏胜利。

LLL 想知道**最少需要出多少次牌**才能获得游戏胜利，请你帮他求出这个值。

## 说明/提示

**【样例解释 #1】**

对于第一组数据，可以先出 $1, 1, 1, 2$（**三带一**），再出 $1, 1$（**对子**）。

对于第二组数据，可以用 $4$ 次出完：

- 出 $1, 1, 1, 1$（**炸**）。
- 出 $2, 2, 2, 2$（**炸**）。
- 出 $3, 3, 3, 4$（**三带一**）。
- 出 $4, 4$（**对子**）。

**【样例 #2】**

见附件中的 `card/card2.in` 与 `card/card2.ans`。

该组样例满足测试点 $2\sim 3$ 的约束条件。

**【样例 #3】**

见附件中的 `card/card3.in` 与 `card/card3.ans`。

该组样例满足测试点 $5\sim 6$ 的约束条件。

**【样例 #4】**

见附件中的 `card/card4.in` 与 `card/card4.ans`。

该组样例满足测试点 $9\sim 10$ 的约束条件。

**【数据范围】**

对于所有测试数据，保证：$1\le T\le 10$，$1\le n\le3\times10^5$，$0\le v_i\le10^9$。

|测试点编号|$n\le$|$v_i\le$|
|:-:|:-:|:-:|
|$1$|$2$|$10^9$|
|$2\sim 3$|$5$|$5$|
|$4$|$5$|$10^9$|
|$5\sim 6$|$50$|$10^9$|
|$7$|$3\times 10^5$|$2$|
|$8$|$3\times 10^5$|$3$|
|$9\sim 10$|$3\times 10^5$|$10^9$|

## 样例 #1

### 输入

```
3
2
5 1
4
4 4 3 3
6
1 1 4 5 1 4```

### 输出

```
2
4
6```

# 题解

## 作者：larsr (赞：26)

对于"三带一"和"王炸"，可以合并成一种出牌方式，即三张同种的牌带上一个牌。可以发现一定是尽可能多出的四张牌。可以先把每三张同种的牌拿出来，那么每种牌只会剩下不超过 2 张牌。


对于剩下的牌，让它们与三张同种的牌配对，会有两种情况。

- 如果没有剩下的牌都配对完了，那么没有被配对的三张同种的牌就自行配对即可，这一定是最优的，因为会达到答案下界 $\lfloor \frac{n}{4} \rfloor + \lfloor \frac{n\mod 4}{2} \rfloor + (n\mod 2)$。
- 否则，优先让只剩下单独一张的牌先匹配，再匹配两张的，还有剩下的就出单牌和对子即可。

那么就可以 $O(n)$ 解决。

```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
int t, n;
void slove()
{
	ll sall = 0, s1 = 0, s2 = 0, ds = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		ll v;
		scanf("%lld", &v);
		ds += v;
		sall += v / 3;
		if(v % 3 == 1)s1++;
		if(v % 3 == 2)s2++;
	}
	if(s1 + s2 * 2 <= sall)
	{
		printf("%lld\n", ds / 4 + (ds / 2 % 2) + ds % 2);
		return;
	}
	ll la = sall;
	ll tmp = min(s1, sall);
	s1 -= tmp;
	sall -= tmp;
	tmp = min(s2 * 2, sall);
	s2 -= tmp / 2;
	sall -= tmp;
	printf("%lld\n", s1 + s2 + la);
}
int main()
{
	scanf("%d", &t);
	while(t--)slove();
	return 0;
}
```

---

## 作者：Exsinly (赞：16)

# 「SMOI-R2」Happy Card

上午的模拟赛第一题成功写挂了。本来分类讨论了一百多行喜提 $0$ 分，借助 dalao 的思路重构一下代码。

## 思路

相较于官方题解，感觉还是有不一样的地方。此题核心的思想就是贪心。对于所有的单张，必然要花费一次打出去，所以最好的情况是三带一打出去。

那么我们先提出所有的三张，跟剩下的数量的牌从小到大分开组合。对于所有都是三张，就要拆开有三张的牌进行组合。实际上我们把炸弹和三带一看成一种东西。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 10;
long long a[MAXN];
int main()
{
    int T,n;
    long long sum = 0;
    long long cnt1 = 0 , cnt2 = 0 , cnt3 = 0;
    cin >> T; // 输入询问次数
    for (int t = 1 ; t <= T ; ++t)
	{
        memset(a,0,sizeof(a));
        cnt1 = cnt2 = cnt3 = sum = 0;
        cin >> n;
        for (int i = 1 ; i <= n ; ++i)
		{
            cin >> a[i]; // 输入每种牌的数量
            sum += a[i];
            cnt3 += a[i]/3;// 累加可以组成三张的组合
        }
        if (cnt3 > sum/4) // 如果所有“三张”的总数足以覆盖至少四张一组的分布
		{
            if (sum % 4 == 1) cout << sum / 4 + 1 << endl;
            else if (sum % 4 ==2) cout << sum / 4 + 1 << endl;
            else if (sum % 4 == 3) cout << sum / 4 + 2 << endl;
            else if (sum % 4 == 0) cout << sum / 4 << endl;
        }
        else if (cnt3 <= sum/4)
		{
            for (int i = 1 ; i <= n ; i++)
			{
                if (a[i] % 3 == 1) cnt1++;// 模 3 余 1 的牌数量
                else if (a[i] % 3 == 2) cnt2++;// 模 3 余 2 的牌数量
            }
            if (cnt3 <= cnt1) cout << cnt1 + cnt2 << endl;// 如果“三张”不足够，使用余数牌
            else if (cnt3 > cnt1) cout << cnt3 + cnt2 - (cnt3 - cnt1) / 2 << endl;// 用余数的 2 补充“三带一”或其他牌
        }
    }

    return 0;
}
```

---

## 作者：Guderian_houjt (赞：9)

# P11323【MX-S7-T1】「SMOI-R2」Happy Card

本题思维难度较大，难度应为黄题~绿题。

## 思路

这题乍一看需要朴素的模拟，但这样毫无头绪，因为时间复杂度极劣（相当于搜索，为组合数级别
）。

于是我们来分析题目中的定义：

- 单牌：出一张单牌。
 
- 对子：出两张同种的牌。
 
- 炸：出四张同种的牌。
  
- 三带一：出三张同种的牌和一张不同种的牌。

通过观察可以发现， $3$ 张类型相同的牌与**任意类型**的 $1$ 张牌（包括与它类型相同的牌）组合，无论是“炸”还是“三带一”均可一起打出。即：**$3$ 张相同的牌与单牌组合可以最大程度上增加一次打出的牌的数量。**

我们不妨把所有牌按每相同三张牌一组来划分，统计每组牌的数量，同时记录划分后剩下的“单牌”和“对子”的数量。借助上述**贪心**思想，我们想到用**三张牌的牌组**组合“单牌”打出，因为**一次打出四张牌必然是最优的出牌方案。** 如果牌组数过多，可以考虑将“对子”拆为“单牌”，再与牌组组合。

但注意到我们最多需要总牌数的 $1/4$ 的牌组数来消耗“单牌”（即将牌全部等分为牌组和“单牌”）,如果实际的牌组数大于我们需要的数量，那么我们完全可以将剩余的牌组以 $4$ 张一组组合，多出来的一定为同类牌，可能是 $1$ 张”单牌“， $1$ 张“对子”，或 $1$ 张”单牌“和 $1$ 张“对子”，打出即可。

**综上，牌组数小于等于总牌数的 $1/4$ 时，将牌组与“单牌”尽可能组合，必要时将“对子”拆为“单牌”。**
 
 **若牌组数大于总牌数的 $1/4$ 时，将牌每四张一组打出，最后剩下的相同的牌特判即可。**


## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3e5+10;
long long thrd,sgl,dbl;
long long sum;
int vol[MAXN];
int n;
vector<long long> res;
void init()
{
    memset(vol,0,sizeof(vol));
    sum=thrd=sgl=dbl=0;//记得清零
}
int main()
{
    //freopen("card4.in","r",stdin);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n;
        init();
        for(int i=1;i<=n;i++)
        {
            cin>>vol[i];
            sum+=vol[i];
            if(vol[i]%3 == 1) sgl++;
            if(vol[i]%3 == 2) dbl++;
            thrd+=vol[i]/3;//统计最优的出牌方法
        }
        long long ans=0;
        if(thrd > sum/4)//均可四张一组打出
        {
            if(sum%4 == 1 || sum%4 == 2) ans=sum/4+1;
            if(sum%4 == 3) ans=sum/4+2;
            if(sum%4 == 0) ans=sum/4;
        }
        else
        {
            if(thrd < sgl) ans=sgl+dbl;//牌组数小于单牌数
            else if(sgl <= thrd && thrd <= sgl+dbl*2) ans=thrd+(dbl*2+sgl-thrd)/2+(dbl*2+sgl-thrd)%2;//拆对子
        }
        res.push_back(ans);
    }
    for(auto p:res)
    {
        cout<<p<<endl;
    }
    return 0;
}

```

---

## 作者：cff_0102 (赞：5)

一个炸可以看成一个特殊的三带一。注意到只有三带一允许出两个不同种类的牌，单牌和对子都不行，所以把每一个种类的牌分成若干份 $3$ 再说（多余的再分为 $1$ 或 $2$）。尽量把 $3$ 用完，因为这样可以一次出四张牌，是最多的。如果还剩下 $3$ 就分情况讨论让它们自己消完就可以了，如果还剩下一些 $1$ 或 $2$ 也是一样的。因为刚开始所有出的牌都是四个一组，所以这种出法一定最优。

赛时代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int a[4];
void mian(){
	int n;cin>>n;
	int ans=0;
	//炸可以看成三带一
	a[0]=a[1]=a[2]=a[3]=0;
	for(int i=1;i<=n;i++){
		int x;cin>>x;
		a[3]+=x/3;
		a[x%3]++;
	}
	ans=min(a[1],a[3]);
	a[1]-=ans,a[3]-=ans;
	int tmp=min(a[2]*2,a[3]);
	ans+=tmp;
	a[3]-=tmp;
	if(tmp&1){
		a[2]-=tmp/2+1,a[1]++;
	}else{
		a[2]-=tmp/2;
	}
	ans+=a[1]+a[2];
	//0 2 2 3 3 5 5 6 6
	ans+=a[3]/4*3;
	if(a[3]%4==1)ans++;
	ans+=a[3]%4;
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
//	system("FC card4.out card4.ans");
//	freopen("card4.in","r",stdin);
//	freopen("card4.out","w",stdout);
	int t;cin>>t;
	while(t--)mian();
	return 0;
}
```

---

## 作者：UncleEric (赞：4)

## 题解 P11323 【MX-S7-T1】「SMOI-R2」Happy Card

[原题链接](https://www.luogu.com.cn/problem/P11323)

### 题意介绍

给出一副扑克牌，在仅出单张、对子、三带一、炸弹的情况下以尽量少的次数出完所有牌。

### 题目分析

首先，我们可以发现，炸弹可以视作一种特殊的三带一，即三带一带了相同的牌。

因而，出牌的情况减少为三种，即为单张、对子、三带一。

发现三带一可以一次性出 $4$ 张牌，而对子可以一次性出 $2$ 张牌。因而按照 三带一 $>$ 对子 $>$ 单张 的顺序打牌，可以保证出牌的次数尽可能少。

考虑按上述分析进行贪心。

---

### 解法说明

由于每次三带一的时候，牌库内都会有四张牌的消耗，因此我们可以优先处理出初始的 $3$ 张牌组合的数量和对子的数量。

此时，我们正在贪心选取尽可能多的三带一，因此对于每种牌，我们肯定会优先将所有 $3$ 张进行组合，然后再考虑对子。因而，这一步的预处理变得轻松：

**对于每种牌，先以该种牌张数除以 $3$ 的结果增加 $3$ 张牌组合的数量，再看其在此次处理后剩余的张数（肯定小于 $3$），若其为 $2$，则将这两张组合成对子增加对子的数量。**

---

接下来，我们需要对 $3$ 张牌组合的数量做分类讨论。原因是：$3$ 张牌的组合可能不够，在出完三带一后还需要额外出对子和单牌才能将这一副牌打完；$3$ 张牌的组合可能会过多，在出完一部分三带一后，剩余的均为 $3$ 张牌的组合，此时就必须拆开某些 $3$ 张牌的组合，才能继续将剩余的牌打完。

将上一段分号往前的内容作为情况 $1$，分号往后的内容作为情况 $2$。

在正式开始分类讨论之前，我们需要先考虑一下分类讨论的前提。可以发现每次出三带一的时候需要从你的手牌中打出四张牌。因此将卡牌总数去掉所有形成 $3$ 张牌组合的卡牌，剩余的卡牌数如果能将 $3$ 张牌的组合全部使用，则进入情况 $1$ 的讨论，否则进入情况 $2$ 的讨论。

**对于上一段分类讨论的前提，我们没有必要考虑对子。** 如果你可以出两次三带一，其一定比你先出对子再分别拆掉两组 $3$ 张牌使用的次数更少。

#### 情况 $1$

对于所有出三带一的次数相同的情况，不难发现，出完三带一后使得剩余的对子更多的情况肯定更优。举个例子，一共四种牌分别有 $3,3,2,2$ 张。如果用三张第一种牌带了一张第三种牌，三张第二种牌带了一张第四种牌，这样到最后会剩余一张第三种牌和一张第四种牌，共需要 $4$ 次。这样就不如保留第四种牌作为对子，第一种牌和第二种牌的三带一都带第三种牌，共需要 $3$ 次。

综上，对于情况 $1$ ，以优先带没组成对子的牌贪心出完所有的三带一，这样就可以在三带一全部出完后尽可能多地出掉对子。情况 $1$ 的思路部分结束。

#### 情况 $2$

我们会发现，如果 $3$ 张牌组合的数量太多，在出完三带一后直接拆剩下的组合其实没那么方便。这时我们就应该考虑更简单的做法了。

这时回到题目分析时提到的部分，我们每次出三带一，会让剩余的牌减少 $4$ 张。同时我们发现，如果 $3$ 张牌的组合数量过多，优先让 $3$ 张牌去组合落单的牌，最后剩下无法组合的牌一定都是 $3$ 张牌的组合。而三张相同的牌，可以很自由地拆成单张或对子。这样的好处是，**多余的 $3$ 张牌组合既可以拆单张去继续与其他 $3$ 张牌组合形成三带一，又可以拆成对子在最后贪心地减少次数。**

这样我们就可以丢下一部分三张牌的组合不管了。因为可以出三带一的次数在此情况下是富余的，我们可以出掉所有的三带一，这样到了最后，剩下的牌数一定不大于 $3$ （原因可以向上回溯到刚刚的题目分析中）。而由于 $3$ 张牌组合的富余且可拆分情况更加自由（见上一段），我们到最后剩下的牌一定出自于同一个 $3$ 张牌的组合。于是，我们可以直接贪心出完最后的牌了。

---

综上，本题的思路部分大体结束。思路的核心在于优先出完所有的三带一，并在出三带一的前提下保留尽量多的对子。题解中一些比较细节的部分可能比较难以理解，需要多加阅读并带以自己思考。

答案统计在实现得当的情况下可以做到 $O(1)$，因而本题的时间复杂度瓶颈在于预处理，总体时间复杂度 $O(\sum n)$。

本题解的代码实现进行了大量的压行，建议各位读者根据题解内容自行实现而不要直接抄袭。代码如下：


```cpp
#include<bits/stdc++.h>
int T,n,p[300005];
int main(){
	std::cin>>T;
	while(T--){
		long long pairs=0,triples=0,tot=0;std::cin>>n;
		for(int i=1;i<=n;i++) std::cin>>p[i],tot+=p[i],triples+=p[i]/3,pairs+=(p[i]%3==2);
		std::cout<<((triples<=2*pairs+(tot-triples*3-pairs*2))?triples+(tot-4*triples>=2*pairs?pairs+tot-4*triples-2*pairs:(tot-4*triples)/2+(tot-4*triples)%2):(tot/4+((tot%4>0)?(tot%4>2)?2:1:0)))<<'\n';
	}
}
```

篇末注意事项：

1. 不要压行，可读性会很低。
2. 本题读入量较大，实现部分写丑很可能 TLE，请进行读入优化。
3. 本题数据最大可达 $10^5\times10^9$ ，因此一部分数据需要开```long long```。

---

## 作者：cxy_ (赞：3)

**简单的一道贪心题，但是细节很多，建议在看懂题面后食用该题解**

题目中有四种出牌方式，
> 单牌：出一张单牌。
> 
> 对子：出两张同种的牌。
> 
> 炸：出四张同种的牌。
> 
> 三带一：出三张同种的牌和一张不同种的牌
> 
**可以把炸看做三带一**，相信大家都能知道是什么意思，那么就压缩成了三种出牌方式。可以看出，为了让所有牌出完并且**出的次数最小**，就要多出三带一，在没有三带一的情况下，就要多出对子，最后实在不行就要出单牌了。

所以，三带一的时候，要先带单牌，尽量不要拆散现有的对子或三张同样的牌。如果把单牌都带完了，就把对子拆散并且尽量拆散的对子少一些。最后再依次出对子或单牌。

于是，有了两种情况：

一、所有的牌配对完后有剩余的对子或单，这种情况只用模拟就可以了

二、所有的牌配对完后有剩余的三张牌，这种情况可以通过找规律得到最少的出牌次数了

|三张牌的个数|1|2|3|4|5|6|7|8|...|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|最少出牌次数|2|2|3|3|5|5|6|6|...|

不难发现，规律用代码表示就是
```cpp
if(_3>=1 && _1==0 && _2==0){
  if(_3%4==3 || _3%4==0){
    ans+=1;
  }
  ans+=(_3-1)/4*3+2;
}
```
接下来是我的代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l[1000005];
signed main(){
	int t;
	cin >> t;
	for(int p=1;p<=t;p++){
		int ans=0,_3=0,_2=0,_1=0;
		int n;
		cin >> n;
		for(int i=1;i<=n;i++){
			cin >> l[i];
			if(l[i]>3 && l[i]%3==1){
				l[i]-=4;
				ans+=1;
				_3+=l[i]/3;
				l[i]=0;
			}if(l[i]>3 && l[i]%3==2){
				_3+=l[i]/3;
				l[i]=0;
				_2+=1;
			}if(l[i]%3==0){
				_3+=l[i]/3;
				l[i]=0;
			}if(l[i]==1){
				_1+=1;
			}if(l[i]==2){
				_2+=1;
			}
		}if(_3>=_1){
			ans+=_1;
			_3-=_1;
			_1=0;
		}else{
			ans+=_3;
			_1-=_3;
			_3=0;
			ans+=_1;
			_1=0;
		}if(_3>=_2*2){
			ans+=_2*2;
			_3-=_2*2;
			_2=0;
		}else{
			_2=_2*2;
			ans+=_3;
			_2-=_3;
			_3=0;
			ans+=(_2-1)/2+1;
		}if(_3>=1 && _1==0 && _2==0){
			if(_3%4==3 || _3%4==0){
				ans+=1;
			}
			ans+=(_3-1)/4*3+2;
		}cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：sansesantongshun (赞：3)

本题乍一看好像没什么思路，考虑将牌型进行转化。

我们发现炸可以看做三张同种的牌和一张同种的牌，即可以将三带一和炸合并为一种情况，即三带一是三张同种的牌加上任意一张牌。

设有 $x$ 个单牌，$y$ 个对子，$z$ 个三张，那么最终答案为 $x+y$，同时需满足 $z \le x$。

初始把所有牌设为单张，如果把三张同种牌合并为三张，答案将减少 $3$，如果把两张同种牌合并为对子，答案将减少 $1$。根据贪心策略，应尽可能在允许的情况下尽量将单牌合并为三张，然后在允许的情况下将单牌合并为对子。

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
long long a[300005],sum,san,er,x;
int main()
{
	cin>>t;
	while (t--)
	{
		scanf("%d",&n);
		sum=0;
		for (int i=1;i<=n;++i)
		{
			scanf("%lld",&a[i]);
			sum+=a[i];//看做单牌
		}
		san=0;
		for (int i=1;i<=n;++i)
		if (a[i]>=3)
		{
			x=min(a[i]/3,sum-san>>2);
			a[i]-=3*x;
			sum-=3*x;
			san+=x;
		}//合并三张
		er=sum-san>>1;
		for (int i=1;i<=n;++i)
		if (a[i]>=2)
		{
			x=min(a[i]>>1,er);
			sum-=x;
			er-=x;
		}//合并对子
		cout<<sum<<'\n';
	}
}
```

---

## 作者：nothing__ (赞：2)

这题赛时秒出思路。

对于这一题，我们需要求出最少次数使得手上的所有牌出完。

那么想要出牌次数尽可能少，那么对于每次出牌，我们应该做到尽可能多。

我们观察到三带一和炸是最优的，对子次之，单牌最次。

思路：

* 我们记录有多少组三张一样的牌。
* 对于每种牌，如果进行记录操作后是单数，那么我们将他入队，在后续三带一时优先带走，因为如果不优先带走，最后剩下他时可能会导致不是最优的，这一点我们观察样例一的第二组数据可以发现。
* 接下来我们先处理队列里的，再枚举每一个位置，知道三带一用光或者枚举完。
* 如果枚举完，那么剩下的多组三张一样的牌，可以随意组合出炸或者三带一，直到不能组合以后再判断剩下的需要几次出完，具体实现可以看代码理解。
* 如果没有枚举完，那我们接着枚举，对于每一个位置，我们判断最少需要出几次牌。

代码如下：
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read() {
	int x=0, w=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') w=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+(ch-'0'); ch=getchar();}
	return x*w;
}
const int N=2e6+10;
int n, c[N];
queue<int> q1;
signed main() {
	int T; T=read();
	while(T--) {
		n=read();
		int res=0, ans=0;
		for(int i=1;i<=n;i++) {
			c[i]=read();
			if(c[i]>=3) {
				res+=c[i]/3;
				c[i]%=3;
			}
			if(c[i]&1) q1.push(i);
		}
		while(q1.size()) {
			int x=q1.front(); q1.pop();
			if(res) res--, c[x]--, ans++;
			else break;
		}
		for(int i=1;i<=n;i++) {
			if(c[i]<=res) {
				ans+=c[i];
				res-=c[i];
				c[i]=0;
			}
			else {
				ans+=res;
				c[i]-=res;
				res=0;
				break;
			}
		}
		if(res>0) {
			int cnt=res*3;
			ans+=(cnt/4);
			int yu=cnt%4;
			ans+=(yu+1)/2;
		}
		else {
			for(int i=1;i<=n;i++) {
				if(c[i]>0) {
					ans+=(c[i]+1)/2;
				}
			}
		}
		printf("%lld\n", ans);
		while(q1.size()) q1.pop();
	}
	return 0;
}
```

---

## 作者：Lyco_Reco (赞：2)

考虑这样一个贪心：将每三张点数相同的牌归为一组，再将每两张点数相同的牌归为一组，最后剩下的单张牌，每一张单独看作一组。

我们把炸弹看成三带一，不难发现尽可能地出三带一肯定是更优的（打出三张牌需要两次操作，而三带一可以一次操作打出四张牌）。

分别使用变量 $s1$，$s2$，$s3$ 记录三种组的组数，贪心地配凑三带一，再将剩下的牌打出即可。

注意在配凑三带一时，优先用单牌组里的牌，避免将对子拆开而增加操作次数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
#define inf 0x3f3f3f3f3f3f3f3f
#define ull unsigned long long
#define pii pair<int,int>
#define fi first
#define se second
#define arr basic_string
#define pc putchar
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define per(i,r,l) for(int i=(r);i>=(l);i--)
#define maxn 300010
namespace Main{
	int n,s1,s2,s3,ans,a[maxn];
	int rd(){
		int x=0,f=1;
		char ch=getchar();
		while(ch<'0'||ch>'9'){
			if(ch=='-'){
				f=-1;
			}
			ch=getchar();
		}
		while(ch>='0'&&ch<='9'){
			x=x*10+ch-'0';
			ch=getchar();
		}
		return x*f;
	}
	void wrt(int x){
		int len=1;
		ull y=10;
		if(x<0){
			pc('-');
			x=-x;
		}
		while(y<=x){
			y*=10;
			len++;
		}
		while(len--){
			y/=10;
			pc(x/y+'0');
			x%=y;
		}
	}
	void MAIN(){
		int _=rd();
		while(_--){
			s1=s2=s3=ans=0;
			n=rd();
			rep(i,1,n){
				a[i]=rd();
				s3+=a[i]/3;
				if(a[i]%3==1){
					s1++;
				}
				else if(a[i]%3==2){
					s2++;
				}
			}
			if(s1+s2*2>=s3){
				if(s1>s3){
					s1-=s3;
					ans+=s3;
					s2*=2;
				}
				else{
					s3-=s1;
					ans+=s1;
					s1=0;
					s2*=2;
					s2-=s3;
					ans+=s3;
				}
				ans+=s1+s2/2+s2%2;
			}
			else{
				s3-=s1+s2*2;
				s3*=3;
				ans=s1+s2*2+s3/4+(s3-s3/4*4)/2+(s3-s3/4*4)%2;
			}
			wrt(ans),pc('\n');
		}
	}
}
signed main(){
//	freopen("card4.in","r",stdin);
//	freopen("1.txt","w",stdout);
//	cin.tie(nullptr)->sync_with_stdio(false);
	Main::MAIN();
    return 0;
}
```

---

## 作者：0xyz (赞：1)

### T1 P11323 【MX-S7-T1】「SMOI-R2」Happy Card

一般对于这种题，还是要推性质，猜策略，合并一些本质相同的操作。“炸”可以看为“自己带自己”的“三带一”，所以我们就可以将问题视为尽量进行“三带一”（四消），然后剩下的每种牌不超过 $2$ 的边角料用“单牌”（单消）和“对子”（二消）去处理即可。

我们需要用“三带一”尽量清除边角料 $1$ 和 $2$，由于实际上打“单牌”比打“对子”更加消耗操作，并且清除 $1$ 边角料比清除 $2$ 边角料所需要的“三带”个数更少，所以我们优先尽力清除 $1$ 边角料，然后再尽力清除 $2$ 边角料（注意剩余“三带”个数是奇数时会带来新的 $1$ 个 $1$ 边角料，这是由于总牌数是奇数我们必须进行至少 $1$ 次单消，所以这个不可避免）。

注意到如果一共有 $x$ 张牌，由于每次只能清除 $4,2,1$ 张牌，所以答案的理论最小值是 $\lfloor\frac{x}{4}\rfloor+\text{popcount}(x\bmod 4)$。

所以我们的策略就是将所有“三带”拿出来，优先清除 $1$ 边角料，然后再清除 $2$ 边角料，剩下的边角料用“单牌”和“对子”处理，剩下的“三带”则可以取到理论最小值。

如何证明这一点？

如果剩下的是边角料，那么显然我们已经进行了最多次数的四消，在此基础上单消最少，所以最优。

如果剩下的是“三带”，首先显然任意四个“三带”可以拆开一个满足另外三个，全部都是四消。然后，我们只会剩下 $1,2,3$ 个“三带”，如果拆开一个去满足剩下的，会分别剩下相同 $3,2,1$ 张牌，所以二消和单消分别最多出现一次，达到理论最小。

时间复杂度 $O(Tn)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,x,p[3],d1,d2,w,s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;w=s=p[1]=p[2]=0;
		for(ll i=1;i<=n;i++)cin>>x,s+=x/3,p[x%3]++;
		d1=min(p[1],s);
		s-=d1;p[1]-=d1;w+=d1;
		d2=min(p[2]*2,s);
		if(d2&1)p[2]-=(d2+1)/2,s=0,p[1]++,w+=d2;
		else p[2]-=d2/2,s-=d2,w+=d2;
		s*=3;
		cout<<w+p[1]+p[2]+s/4+__builtin_popcount(s&3)<<'\n';
	}
	return 0;
}
```

---

## 作者：I_am_Lord_Voldemort (赞：1)

考虑贪心策略，一共四种操作，三带一和炸显然更赚，那么那种更优呢？我们发现可以把炸转化为特殊的三带一。因此只有三种打法。单张，对子，三带一。

那么做法就明确了：尽量把三张一样的放在一起，有单张就打。单张打完了，有对子就拆开打两次。实在打完了就拆开三张打三次。最后剩一点单张和对子。若三张打完了，单张和对子没用完就全部打出去。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,x,sum3,sum2,sum1,ans;
signed main(){
	ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	int T;cin>>T;
	while(T--){
		cin>>n;sum3=sum2=sum1=ans=0;
		for(int i=1;i<=n;i++){
			cin>>x;
			sum3+=(x/3);
			if(x%3==1) sum1++;
			if(x%3==2) sum2++; 
		}
		if(sum1>sum3) ans+=sum3,sum1-=sum3,sum3=0;
		else ans+=sum1,sum3-=sum1,sum1=0;
		if(sum2*2>sum3) ans+=sum3,sum2-=(sum3+1)/2,sum1+=sum3%2,sum3=0;
		else ans+=sum2*2,sum3-=sum2*2,sum2=0;
		if(sum1||sum2){
			ans+=sum1+sum2;
		}
		else{
			ans+=(sum3/4)*3;sum3%=4;
			if(sum3==1) ans+=2;
			if(sum3==2) ans+=2;
			if(sum3==3) ans+=3;
		}
		cout<<ans<<"\n";
	}
}
```

---

## 作者：SpringQinHao (赞：1)

场上一遍过

**思路**：首先大家都知道的就是如果**单着的牌**很多，则更多的打出三带一肯定更优，但是数据在随机的情况下，单着的牌绝大部分是由三带一所消耗的三余下产生的，**而且**我们没有那么多“一”给那么多“三”消耗，这时只好**拆散对子以及“三”**。所以在此时很有可能打出更多的炸弹更优。

例：

```
114154 9191810
```
这种大数据多打三带一就必定会拆散很多很多“三”，必然多打四更优。

听起来好麻烦！所以我们用**两种计数方式**，多打三还是多打四我们取两种方案的最小值。

附上我的AC代码。
```cpp
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
const ll N=6e5+5;
ll read()
{
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x*=10,x+=c-'0';
		c=getchar();
	}
	return x*f;
}
ll T,n,a[N],ans,t[N];
ll wq[10],w[5],res;
ll work(ll one,ll two,ll three)
{
	ll ans=0;
	if(one>=three){
		ans+=one+two;
		return ans;
	}
	else if(one+2*two>=three){
		ll t=one+2*two-three;
		ans+=ceil(t*1.0/2);
		ans+=three;
		return ans;
	}
	else{
		ans+=one+2*two;
		three-=one+2*two;
		ans+=3*(three/4);
		ll t=three%4;
		if(t==1) ans+=2;
		if(t==2) ans+=2;
		if(t==3) ans+=3;
		return ans;
	}
}
int main()
{
//	freopen("card4.in","r",stdin);
//	freopen("card.out","w",stdout); 
	T=read();
	while(T--){
		ans=0,res=0;
		n=read();
		for(ll i=1;i<=5;i++) wq[i]=0,w[i]=0;
		for(ll i=1;i<=n;i++){
			ll x=read();
			a[i]=x;
			if(x==1) wq[1]++,w[1]++;
			else if(x==2) wq[2]++,w[2]++;
			else if(x==3) wq[3]++,w[3]++;
			else if(x==4) wq[4]++,res++,ans++;
			else{
				res+=x/4;
				w[(x%4)]++;
				wq[3]+=x/3;
				wq[(x%3)]++;
			}
		}
		printf("%lld\n",min(ans+work(wq[1],wq[2],wq[3]),res+work(w[1],w[2],w[3])));		
	}
	return 0;
}
```

---

## 作者：xmkxk (赞：1)

我们将炸弹视为三带一，然后贪心地出牌。

1. 尽可能出三张带单张。
2. 如果三张全部出完，将单张和对子全部打出，否则将对子拆成三张带单张打出。
3. 如果剩下的是对子直接打出，否则将三张拆成三张带单张打出，再将剩下的出完。

**注意**，将三张拆成三带一时如果刚好剩下一组三张要打两次。

模拟即可。

### 代码

```cpp
#include <bits/stdc++.h>
template <typename T>inline void read(T& aim){T num=0,f=1;int ch=getchar();for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())num=num*10+ch-'0';aim=num*f;}
template <typename T>inline void write(T x){static int sta[40];int top=0;if(!x){putchar('0');return;}if(x<0)putchar('-'),x=-x;while(x)sta[++top]=x%10,x/=10;while(top)putchar(sta[top--]+'0');}
template <typename T>inline void print(T x,char ch=' '){write(x);putchar(ch);}
inline void nl(){putchar('\n');}
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
const int N=3e5+9;


int n,v[N];
LL cnt[10];
int main(){
	int T;read(T);
	while(T--){
		read(n);
		cnt[1]=cnt[2]=cnt[3]=0;
		for(int i=1;i<=n;i++){
			read(v[i]);
			int gr=v[i]/3;
			cnt[3]+=gr;cnt[v[i]%3]++;
		}
		LL thr=min(cnt[3],cnt[1]),ans=0;
		ans+=thr;cnt[1]-=thr;cnt[3]-=thr;
		if(!cnt[3]){
			ans+=cnt[1];ans+=cnt[2];
		}
		else{
			if(cnt[2]*2>cnt[3]){
				ans+=cnt[3];cnt[2]-=cnt[3]/2;
				ans+=cnt[2];
			}
			else{
				ans+=cnt[2]*2;cnt[3]-=cnt[2]*2;
				ans+=cnt[3]*3/4+((cnt[3]*3)%4!=0)+((cnt[3]*3)%4==3);
			}
		}
		print(ans,'\n');
	}
	
	
	
	return 0;
}
```
~~这题怎么是绿的不应该是橙的吗。~~

---

## 作者：Ratio_Y (赞：0)

## 思路

比较好想到炸弹等价于三带一，因此本质只有三种出牌类型。并且三带一一次能出掉四张牌，显然优先打三带一是很优的。所以我们处理出三带的个数以及剩下零牌中对子的个数，然后分讨。

- 如果三带的个数少于零牌数，此时策略比较好想：三带全部打出，多余的零牌中尽量打对子。

- 如果二者数量相等，那么一直打三带一就结束了。

- 如果三带的个数多于零牌数，我们就要考虑将零牌带完后如何将三带拆开打出。容易发现四个三带可以通过拆掉一个来在三轮内打出，这样依然是最优的一次出四张牌的出法，因此优先选。那么之后只可能剩 $0,1,2,3$ 个三带，简单分讨即可。

那么就做完了，整体思路不难，解题瓶颈在于将炸弹拆成三带一的形式。时间复杂度 $\mathcal{O(n)}$。

## 实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int Ratio = 0;

namespace Wisadel
{
    short main()
    {
        int T, n, x; scanf("%d", &T);
        while(T--)
        {
            scanf("%d", &n);
            ll sum3 = 0, sum2 = 0, sum1 = 0, ans = 0;
            for(int i = 1; i <= n; i++)
            {
                scanf("%d", &x);
                sum3 += x / 3;
                sum1 += x % 3;
                if(x % 3 == 2) sum2++;
            }
            if(sum3 < sum1)
            { // 三带不完，全带，剩下考虑对
                ll zc = sum1 - sum3; // 剩下 zc 张
                ll tim = 0; // 出对子数量
                tim = min(sum2, zc / 2);
                zc -= tim * 2;
                ans = sum3 + zc + tim;
            }
            else if(sum3 == sum1) ans = sum3;
            else
            { // 三带多了，拆多的三带
                ll zc = sum3 - sum1;
                ll tim = zc / 4; // 四个三带三次可出完
                if(zc % 4 == 1) ans = 2; // 1 + 2
                else if(zc % 4 == 2) ans = 2; // 3.1 + 2
                else if(zc % 4 == 3) ans = 3; // (3.1) * 2 + 1
                ans += tim * 3 + sum1;
            }
            printf("%lld\n", ans);
        }
        return Ratio;
    }
}
signed main(){return Wisadel::main();}
// All talk and never answer
```



---

完结撒花~

---

## 作者：_sin_ (赞：0)

首先，观察到炸弹和三带一是本质相同的（炸弹相当于三带一带了一个相同的数），所以本质上只有三种出牌方式：
- 单牌
- 对子
- 三带一

根据贪心的思想，想要尽快走完应该优先出三带一，这样走掉的牌多。\
先让所有能出三带的牌组成最多组三张相同的牌，如果剩下的牌的牌数足够让上述的牌组成三带一，就直接组成。否则考虑拆开其他的三带。\
记录 $f_i$ 为只剩下 $i$ 组牌没有被匹配，转移方程为：
$$f_i=\min\{f_{i-1}+2,f_{i-4}+3\}$$
$$f_i=\min\{f_{i-4}+6,f_{i-4}+3\}$$
$$f_i=f_{i-4}+3$$
其中 $f_0=0,f_1=2,f_2=2,f_3=3$。\
观察状态转移方程可得：$f_{i}=f_{i \bmod 4}+\lfloor \frac{i}{4} \rfloor \times 3$。\
然后这道题就做完了，代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||'9'<ch){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return f*x;
}

const int N = 3e6+5;
ll T,n,t[N],ls[N],cnt,sls,ans,f[N];

void solve(){
    n=read();cnt=sls=ans=0;
    for(int i=1;i<=n;i++){
        t[i]=read();
        ls[i]=t[i]%3;
        cnt+=t[i]/3;
        sls+=ls[i];
    }
    if(sls>=cnt){// 优先用单牌
        for(int i=1;i<=n;i++)if(ls[i]==1){
            cnt--,ans++,ls[i]=0;
        }if(cnt>0){// 然后再拆对子
            for(int i=1;i<=n;i++)if(ls[i]==2){
                while(cnt&&ls[i])ans++,ls[i]--,cnt--;
            }
        }
        for(int i=1;i<=n;i++)if(ls[i])ans++;
        printf("%lld\n",ans);return void();
    }else{
        ans+=sls;cnt-=sls;
        printf("%lld\n",ans+(f[cnt%4]+(cnt/4)*3));return void();
    }
}

int main(){
    f[0]=0,f[1]=2,f[2]=2,f[3]=3;
    // for(int i=4;i<N;i++)f[i]=f[i-4]+3;
    T=read();while(T--)solve();
    return 0;
}
```

---

## 作者：forever_nope (赞：0)

结论题。

**结论一**：对于任意 $v_i=3c_i+r,(0\le r<3)$，将 $v_i$ 拆为 $c_i$ 个 $3$ 和一个 $r$ 不影响答案。

证明：

+ 对于单：显然不影响。

+ 对于对：显然不影响。

+ 对于三带一：注意到这个拆分的过程本质就是一个三带一的过程。

+ 对于炸：注意到一个 $\texttt A$ 的炸等价于三个 $\texttt A$ 带一个 $\texttt A$，因此是正确的。

因此，我们可以将问题全部转化为 $v_i\le3$ 的情况，不考虑炸的情况。

**结论二**：对于 $v_i\in\{1,2,3\}$ 按照如下操作，一定最优：

1. 尽可能多的用一个 $3$ 带走一个 $1$。

2. 尽可能多的用两个 $3$ 带走一个 $2$。

3. 尽可能多的用一个 $3$ 将一个 $2$ 转化为一个 $1$。

4. 注意到此时，要么剩下的都是 $3$ 要么不剩下 $3$。

   1. 如果不剩下 $3$，每个 $1,2$ 按照 $1$ 的系数拿走即可。
  
   2. 如果只剩下 $3$，按照如下策略：
  
5. 对于四个 $3$，令其中三个一次消去另外一个，即每消去 $4$ 个需要 $3$ 步。

6. 对于剩下的 $0,1,2,3$ 个三，容易知道只需要分别 $0,2,2,3$ 步即可。

核心代码：

```
int cnt3[4] = {0, 2, 2, 3};

int calc(int cnt) {
	return 3 * (cnt / 4) + cnt3[cnt % 4];
}

int solve(int *cnt) {
	int res = 0;

	// 用 3 把 1 消去
	int v31 = min(cnt[3], cnt[1]);
	cnt[3] -= v31;
	cnt[1] -= v31;
	res += v31;

	// 用两个 3 把 2 消去
	int v32 = min(cnt[3] >> 1, cnt[2]);
	cnt[3] -= v32 << 1;
	cnt[2] -= v32;
	res += v32 << 1;

	// 剩余的 3 把 2 消成 1 一个
	int v33 = min(cnt[3], cnt[2]);
	cnt[3] -= v33;
	cnt[2] -= v33;
	cnt[1] += v33;
	res += v33;

	// 对于 1 和 2 直接消去 3 特殊处理
	res += cnt[1] + cnt[2] + calc(cnt[3]);
	return res;
}

void Main() {
	int T = read<int>();
	while (T--) {
		int cnt[5] = {0};
		int n = read<int>();
		for (int i = 1; i <= n; ++i) {
			int x = read<int>();
			++cnt[x % 3];
			cnt[3] += x / 3;
		}
		writeln(solve(cnt));
	}
	return;
}
```

---

## 作者：Night_sea_64 (赞：0)

场上一个多小时不会这题，然后 T2 做完回来才会。。

首先可以发现，炸也可以当成三带一。然后这个问题就简单了。

把原来的 $n$ 种牌，每种牌分成尽量多的 $3$ 张牌组合，剩下的作为单牌或对子。记录三种牌组的数量分别为 $c_1,c_2,c_3$。

$3$ 张牌的当然跟单牌配对比较好，所以先打出若干个三带一。

此时分为两种情况：如果 $3$ 张牌的没了，那剩下的就全都按照单牌或对子出。

否则还剩下 $3$ 张牌的和对子。这时应该把对子拆成单牌，再继续打三带一。如果拆 $3$ 张牌的，答案一定不优，因为这样对子就只能当对子出了。

这时如果 $3$ 张牌的没了，剩下的也全都按单牌或对子出（$3$ 张牌的组合个数为奇数的话会剩一张单牌）。

否则就是只剩 $3$ 张牌的了。尝试 $3$ 张牌的组合分别有 $1,2,3,4$ 组时，最少打完的次数分别为 $2,2,3,3$。其中 $4$ 组的话 $3$ 次打完，每次都能打出 $4$ 张（其中三组都是一起打出来，第四组的三张分别被前三组带走了）。所以对于 $k$ 组（$k\ge4$）的情况，先按上述方案打出 $4$ 组变为 $k-4$ 组，这样的方案是最优的。算一下即可。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int t,n,a[300010];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        long long c1=0,c2=0,c3=0,ans=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            c3+=a[i]/3;
            if(a[i]%3==1)c1++;
            else if(a[i]%3==2)c2++;
        }
        int now=min(c1,c3);
        ans+=now;
        c1-=now,c3-=now;
        if(c3==0)printf("%lld\n",ans+c1+c2);
        else
        {
            ans+=min(c2*2,c3);
            if(c2*2>c3)
            {
                if(c3%2==0)
                {
                    c2-=c3/2;
                    printf("%lld\n",ans+c2);
                }
                else
                {
                    c2-=c3/2+1;
                    printf("%lld\n",ans+c2+1);
                }
            }
            else
            {
                c3-=c2*2,c2=0;
                ans+=(c3+3)/4*3-1;
                if(c3%4==3||c3%4==0)ans++;
                printf("%lld\n",ans);
            }
        }
    }
    return 0;
}
```

---

## 作者：Misserina (赞：0)

很好的贪心模拟题。

四种出牌方式中，“炸”可以视为三张相同的牌带上另一张相同的牌，也就是一种特殊的三带一。

因此，出牌方式可以简化为三类：单牌、对子、三带一。

其中，三带一一次可以打出 $4$ 张，可以更快地出掉全部牌，因此考虑尽可能多出三带一。

证明“多出三带一”策略的正确性：

- $4$ 张相同牌时，贪心策略为三带一（炸），出牌次数为 $1$；不使用三带一时最佳策略为两个对子，出牌次数为 $2$。
- $5$ 张相同牌时，贪心策略为三带一（炸）加单牌，出牌次数为 $2$；不使用三带一时最佳策略为两个对子加单牌，出牌次数为 $3$。
- $6$ 张相同牌时，贪心策略为三带一（炸）加对子，出牌次数为 $2$；不使用三带一时最佳策略为三个对子，出牌次数为 $3$。
- $7$ 张相同牌时，贪心策略为三带一（炸）加对子加单牌，出牌次数为 $3$；不使用三带一时最佳策略为三个对子加单牌，出牌次数为 $4$。
- $3$ 张 A 牌加 $1$ 张 B 牌时，贪心策略为三带一，出牌次数为 $1$；不使用三带一时最佳策略为对子加两个单牌，出牌次数为 $3$。
- $3$ 张 A 牌加 $2$ 张 B 牌时，贪心策略为三带一加单牌，出牌次数为 $2$；不使用三带一时最佳策略为两个对子加单牌，出牌次数为 $3$。
- $3$ 张 A 牌加 $3$ 张 B 牌时，贪心策略为三带一加对子，出牌次数为 $2$；不使用三带一时最佳策略为两个对子加两个单牌，出牌次数为 $4$。
- 相同牌数超过 $7$ 张时，最优策略为三带一（炸）后再执行 $4 \sim 7$ 张时的最优解。

由上可以看出，尽可能多出“三带一”，一定能尽快出完全部牌。

记录每种牌最多提供的“三张”个数，剩下的 $1$ 张或 $2$ 张即为无法成为“三张”的牌，定义其为“孤牌”。

例如手牌为 `1 2 2 3 3 3 4 4 4 4 5 5 5 5 5 6 6 6 6 6 6`，$3$、$4$、$5$ 各能提供 $1$ 个“三张”，$6$ 能提供两个“三张”，剩下的 $1$ 张 $1$，$2$ 张 $2$，$1$ 张 $4$，$2$ 张 $5$ 即为“孤牌”。

分类讨论“三张”个数与“孤牌”个数大小关系：

如果“三张”个数大于剩余全部“孤牌”数，那么意味着全部“孤牌”都能够被“三张”带走，此时“三张”有多余。

- 多余 $1$ 个“三张”时：出对子加单牌，出牌次数加上 $2$。
- 多余 $2$ 个“三张”时：出对子加三带一，出牌次数加上 $2$。
- 多余 $3$ 个“三张”时：出两个三带一加单牌（`AAAC BBBC C`），出牌次数加上 $3$。
- 多余 $4$ 个“三张”时：出三个三带一（`AAAD BBBD CCCD`，出牌次数加上 $3$。

发现多余 $4$ 个“三张”时已经是最快速的方法（即每次都能出 $4$ 张牌），因此，如果多余“三张”个数大于 $4$，不断按照类似 `AAAD BBBD CCCD` 形式出牌肯定更快。

如果“孤牌”个数大于“三张”个数：意味着“三张”带不走全部孤牌，孤牌有多余，此时显然应该尽可能将孤牌多留给能成对的牌，也就是让“三张”尽可能带走不能成对的孤牌。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,v[300005];
long long n1,n2,n3,res;
int main() {
	scanf("%d",&t);
	while (t--) {
		n1=0,n2=0,n3=0,res=0;
		scanf("%d",&n);
		for (int i=1;i<=n;i++) {
			scanf("%d",&v[i]);
			n3+=v[i]/3;
			if (v[i]%3==1) n1++;
			if (v[i]%3==2) n2+=2;
		}
		if (n3>=n1+n2) { //三张能带走全部孤牌
			res=n1+n2;
			n3-=res;
			res+=(n3/4)*3;
			n3%=4;
			res+=(n3/3)*3;
			n3%=3;
			res+=(n3/2)*2;
			n3%=2;
			res+=n3*2;
		}
		else if (n3>=n1) { //三张能带走全部无法成对的孤牌，但是带不走全部能成对的孤牌
			res=n3;
			n2-=(n3-n1);
			res+=(n2/2)+(n2%2);
		}
		else res=n1+n2/2; //三张带不走全部无法成对的孤牌
		printf("%lld\n",res);
	}
}
```

---

## 作者：xibaohe (赞：0)

# 题目大意
给你一些牌，有四种出牌方式，你需要用最少的步数把所有牌出完。

# 题目分析
既然有多种方式，首先考虑动态规划，但不难注意到本题的 $n$ 和 $v_i$ 很大，因此不考虑动态规划。

然后考虑贪心。在四种方法中，单牌、对子、炸都是比较好操作的，唯一难操作的是三带一。**我们可以考虑合并两种操作，即将炸和三带一合并**。简单来说，就是把所有牌都拆成三个一组，这样既可以三个牌与同种单牌合并成炸，也可以将三个牌与不同种单牌合并成三带一。

# 代码实现
我们可以用三个计数器记录一个牌、两个牌和三个牌的情况。

```cpp
int cnt3=0,cnt2=0,cnt1=0;
```

在输入的时候，我们将同种牌分为三个一组，并记录剩下的牌是两张还是一张。

```cpp
for(int i=1;i<=n;i++)
{
	cnt3+=a[i]/3;
	a[i]%=3;
	if(a[i]==2) cnt2++;
	if(a[i]==1) cnt1++;
}
```

然后我们首先考虑三加一的情况，如果三张牌与一张牌数量相同，那么直接输出答案。


```cpp
if(cnt3==cnt1)
{
	cout<<cnt3+cnt2<<endl;
}
```

随后我们考虑三张牌大于一张牌的情况。

既然三比一多，那么我们就将一先消耗完。


```cpp
int ans=0;
ans+=cnt1;
cnt3-=cnt1;
```

消耗完之后我们进行分类讨论，考虑将一个二拆成两个一去配两个三，然后记录答案，将剩下的二和配对过的三输出。如果配对之后还有剩余的三，就将其四四配对输出。


```cpp
if(cnt3>=cnt2*2)
{
	ans+=cnt2*2;
	cnt3-=cnt2*2;
	ans+=cnt3/4*3;
	cnt3%=4;
	if(cnt3==1) ans+=2;
	else ans+=cnt3;
	cout<<ans<<endl;
}
else
{
	cnt2-=cnt3/2;
	ans+=cnt3/2*2;
	cnt3%=2;
	if(cnt3>0)
	{
		cnt2--;
		ans+=2;
	}
	ans+=cnt2;
	cout<<ans<<endl;
}
```

同理，如果三比一少，那么只需要将配对后三加一的个数与剩下的一输出即可。


```cpp
else
{
	cout<<cnt1+cnt2<<endl;
}
```

# 温馨提示

- 不开 `long long` 见祖宗。

# 满分代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int n,a[300005]; 
void solve()
{
	int cnt3=0,cnt2=0,cnt1=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		cnt3+=a[i]/3;
		a[i]%=3;
		if(a[i]==2) cnt2++;
		if(a[i]==1) cnt1++;
	}
	//cout<<cnt1<<" "<<cnt2<<" "<<cnt3<<" "<<endl;
	if(cnt3==cnt1)
	{
		cout<<cnt3+cnt2<<endl;
	}
	else if(cnt3>cnt1)
	{
		int ans=0;
		ans+=cnt1;
		cnt3-=cnt1;
		if(cnt3>=cnt2*2)
		{
			ans+=cnt2*2;
			cnt3-=cnt2*2;
			ans+=cnt3/4*3;
			cnt3%=4;
			if(cnt3==1) ans+=2;
			else ans+=cnt3;
			cout<<ans<<endl;
		}
		else
		{
			cnt2-=cnt3/2;
			ans+=cnt3/2*2;
			cnt3%=2;
			if(cnt3>0)
			{
				cnt2--;
				ans+=2;
			}
			ans+=cnt2;
			cout<<ans<<endl;
		}
	}
	else
	{
		cout<<cnt1+cnt2<<endl;
	}
}
signed main()
{
	//freopen("card4.in","r",stdin);
	//freopen("myans.out","w",stdout);
	cin>>T;
	while(T--)
	{
		solve();
	}
	return 0;
}


```

---

