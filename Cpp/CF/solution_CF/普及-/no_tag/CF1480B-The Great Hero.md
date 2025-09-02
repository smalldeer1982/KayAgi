# The Great Hero

## 题目描述

### 题意

  我们定义一个人物为一个二元组$(x, y)$, 称其中 $x$ 为攻击力, $y$ 为血量. 一个英雄是一个人物. 现在有 $n$ 个怪物, 每个怪物是一个人物. 我们这样定义两个人物 $A$ 与 $B$ 交战:

- $A$ 的血量减少等同于 $B$ 的攻击力的数值, $B$ 的血量也减少等同于 $A$ 的攻击力的数值.
- 然后, $A$ 和 $B$ 中所有血量小于等于 $0$ 的人物死亡.

  现在英雄需要消灭所有怪物, 消灭怪物的方式是与之交战. 请求出英雄能不能消灭所有的怪物, 即使英雄本人在消灭所有怪物后死亡.

## 样例 #1

### 输入

```
5
3 17 1
2
16
10 999 3
10 20 30
100 50 30
1000 1000 4
200 300 400 500
1000 1000 1000 1000
999 999 1
1000
1000
999 999 1
1000000
999```

### 输出

```
YES
YES
YES
NO
YES```

# 题解

## 作者：云浅知处 (赞：3)

[珂能并不会有更好的阅读体验](https://yunqian-qwq.github.io/post/solution-cf1480b)

------------

### Description

[题目 Link](https://codeforces.com/contest/1480/problem/B)

>- 珂朵莉需要把 $\color{skyblue}\text{『深浅值藏的第六兽}\cdot\text{Timere}\cdot\text{恐惧』}$ 全部杀光。
>- 珂朵莉的攻击力为 $A$，生命值为 $B$。
>- 一共有 $n$ 只「第六兽」，第 $i$ 只兽的攻击力为 $a_i$，生命值为 $b_i$。
>- 在珂朵莉和第 $i$ 只「第六兽」的战斗中，珂朵莉每次可以对这只兽造成 $A$ 点伤害，但同时，兽也会对珂朵莉造成 $a_i$ 点伤害。
>- 如果兽的生命值 $\le 0$，那么这只兽就死了。
>- 同理，如果珂朵莉的生命值 $\le 0$，那么珂朵莉的灵魂就会化作『星尘』消失，只剩下一具没有灵魂的躯壳。
>- 但特殊的是，如果此时只剩一只「第六兽」；
>- 并且此时这只「第六兽」剩余的生命值低于珂朵莉的攻击力 $A$，但珂朵莉剩余的生命值也低于这只「第六兽」的攻击力；
>- 那么珂朵莉在化作『星尘』消散前，还可以发动一次攻击，杀死这只兽，也就是杀死了所有兽。
>- 现在给定每只兽与珂朵莉的生命值与攻击力，请你帮珂朵莉算出来，她是否能杀光所有的「第六兽」。
>- $t$ 组数据，$1\le t\le 10^5,1\le A,B,a_i,b_i\le 10^6,\sum n\le 10^5$。
>（设定是我瞎编的，与原作可能不太符合，不管啦qwq）

![](https://s3.ax1x.com/2021/02/17/ygLmxf.png)

------------
### Solution

对于第 $i$ 只兽，珂朵莉需要 $\left\lceil\dfrac{b_i}{A}\right\rceil$ 次攻击才能杀死。

也就是说，珂朵莉想要杀死第 $i$ 只兽，需要消耗 $\left\lceil\dfrac{b_i}{A}\right\rceil\cdot a_i$ 点生命值。

那消灭所有兽之后，珂朵莉的生命值会减少 $\sum\limits_{i=1}^n\left\lceil\dfrac{b_i}{A}\right\rceil\cdot a_i$，也就是还剩 $B-\sum\limits_{i=1}^n\left\lceil\dfrac{b_i}{A}\right\rceil\cdot a_i$ 点生命值。

如果这个值大于 $0$，那就代表着：珂朵莉可以杀光所有兽，并且最后存活。

那就不用管了，直接就是 `YES`。

但是如果这个值小于等于 $0$，那么有可能珂朵莉还能通过最后一击杀光所有兽，与最后一只兽同归于尽。

唔，这样的话......

那么我们考虑这个值：$d_k=B-\sum\limits_{i=1}^n\left\lceil\dfrac{b_i}{A}\right\rceil\cdot a_i+a_k$。

如果这个值大于 $0$，那么就说明珂朵莉能够杀光所有兽，且最后杀的一只是第 $k$ 只兽。

小于等于 $0$，则说明珂朵莉无论如何都杀不掉最后一只兽。

那么我们先 $O(n)$ 计算 $\sum\limits_{i=1}^n\left\lceil\dfrac{b_i}{A}\right\rceil\cdot a_i$，然后 $O(n)$ 计算出 $d_1,d_2,\cdots,d_n$。

只要 $d_1,d_2,\cdots,d_n$ 中有一个大于 $0$，那就说明珂朵莉可以杀光所有兽，输出 `YES`。

都小于 $0$ 则输出 `NO`。

时间复杂度 $O(n)$。

然而 $\sum\limits_{i=1}^n\left\lceil\dfrac{b_i}{A}\right\rceil\cdot a_i$ 最大可以到 $10^6\times10^6\times10^5=10^{17}$，所以：

**记！得！开！`long long`！**

```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<iostream>

#define MAXN 100005
#define int long long

using namespace std;

int A,B,n;
int t;

int a[MAXN],b[MAXN];

int myceil(int x,int y){
    if(x%y==0)return x/y;
    else return (int)(x/y)+1;
}

void solve(){
    
    cin>>A>>B>>n;

    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }

    int sum=0;
    for(int i=1;i<=n;i++){
        sum+=myceil(b[i],A)*a[i];
    }

    bool f=0;
    for(int i=1;i<=n;i++){
        if(B-sum+a[i]>0){
            cout<<"YES\n";
            f=1;
            break;
        }
    }
    if(!f)cout<<"NO\n";
}

signed main(void){

    cin>>t;
    while(t--){
        solve();
    }

    return 0;
}
```

---

## 作者：fls233666 (赞：2)

看到题目，首先一种简单直接的思路就是**模拟英雄一个一个的杀怪物**，如果能全部杀完就是成功，中途死掉就是失败。总时间复杂度为 $O( \sum n)$。

如果按照这个思路写，最后会 $\color{red}Wrong \  Answer$。

仔细思考我们发现，问题出在最后一个怪物上。

简单来说，**因为英雄可以与最后一个怪物同归与尽，导致如果直接按顺序模拟的方案不一定是最优方案。**

那么如何保证方案最优？

**一种靠谱的贪心思路是让英雄先挑攻击力低的怪物杀**。这样英雄可以尽可能保存更多的生命值，进而杀掉更多的怪物，而最终成功杀死所有的怪物可能性也大。显然这样的方案比直接按顺序杀怪更加优秀。

而代码方面的改进，**只需要在模拟之前把所有怪物按照攻击力排序即可**。剩下的部分大致相同。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
#define rgt register int
using namespace std;
 
const int mxn = 1e5+5;
ll mobs[mxn][2],tm,ft;
pair <ll,ll> p[mxn];
//first:攻击力，second:生命
 
int main(){
	bool fail;  //判定是否失败
	int test,n;
	scanf("%d",&test);
	while(test--){
		fail=false;
		scanf("%lld%lld%d",&p[0].first,&p[0].second,&n);
        //读入英雄的攻击力和生命
        
		for(rgt i=1;i<=n;i++)
			scanf("%lld",&p[i].first);
		for(rgt i=1;i<=n;i++)
			scanf("%lld",&p[i].second);
            //读入怪物的攻击力和生命
            
		sort(p+1,p+1+n);  //排序
        
		for(rgt i=1;i<=n;i++){  //模拟杀怪
			tm=p[i].second/p[0].first;
			if(p[i].second%p[0].first)
				tm++;  //不能整除时要多砍一刀
			ft=tm*p[i].first;  //算伤害
			if(p[0].second-ft<=0){
				if(i!=n){  //特判最后一只怪
					fail=true;
					break;
				}else{
					if(p[0].second-(tm-1)*p[i].first<=0){
						fail=true;
						break;
					}
				}
			}
			p[0].second-=ft;
		}
        
		if(fail)  //输出结果
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}
```



---

## 作者：fanfansann (赞：2)

**Problem 1480B - The Great Hero**

我们的攻击力为 $A$ ，血量为 $B$ ，面对 $n$ 只怪，其中第 $i$ 只怪的攻击力为 $a_i$ ，血量为 $b_i$ ，我们可以无限次地攻击任意一只怪，每次我们和怪都会掉血，规则参见正常的 RPG 游戏，就是当血量小于等于 $0$ 时，死亡，每次我们和一只怪激情对砍，我们掉 $a_i$ 的血量，怪掉 $A$ 的血量，请问我们最后能否消灭所有的怪，哪怕在最后一击之后同归于尽。

**Solution**

一个简单的贪心。开始还以为是一个模拟，然后立马发现，因为可以同归于尽，**所以我们最后一击要用到正确的地方**。因为我们打的顺序无所谓，所以可能存在一种情况，我随便打，中间死了，但是我把攻击力最大的哪个怪，放到最后跟他同归于尽，就会最后死，答案从 `NO` 变成了 `YES`。

然后再来分析这么解决。

首先很明显，对于第 $i$ 只怪，我们需要 $\lceil \frac{b_i}{A} \rceil$ 次才能打死它，然后每次会掉 $a_i$ 的血，如果直接打死它的话，会掉 $\lceil \frac{b_i}{A} \rceil\times a_i$ 的血。 

所以我们就先模拟一遍，打一遍，然后最后的血量加上攻击力最大的那只怪的攻击力，相当于就是把这只放到最后打，要是加上之后的血量大于 $0$，说明成功，否则中间就死了...

因为我特判的是 $>0$ 而不是 $\ge0$ ，我先扣掉了所有的血，再加上最大攻击力，如果我这时候剩余的血量 $>0$ 说明我活到了最后一只攻击力最大的怪 例如这个

```cpp
1
10 10 2
2 1000
50 10
```

答案就是 `NO` ，我的代码也是 `NO`，我没办法活到 $1000$ 的那个怪 ~


**Code**

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> PLL;
typedef int itn;
const int N = 5e5 + 7, M = 1e6 + 7, mod = 1e9 + 7;
const ll INF = 1e18 + 7;
ll n, m, t;
ll A, B;
PLL a[N];
bool solve()
{
    scanf("%lld%lld%lld", &A, &B, &n);
    ll maxx = -INF;
    for(int i = 1; i <= n; ++ i) {
        scanf("%lld", &a[i].x);
        maxx = max(maxx, a[i].x);
    }
    for(int i = 1; i <= n; ++ i) {
        scanf("%lld", &a[i].y);
    }

    ll sum = 0;
    for(int i = 1; i <= n; ++ i) {
        ll cnt = ceil(a[i].y * 1.0 / A);
        sum += cnt * a[i].x;
    }
    B -= sum;
    B += maxx;
    if(B > 0) return true;
    else return false;
}

int main()
{
    scanf("%lld", &t);
    while(t -- ) {
        bool ans = solve();
        if(ans) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：CSP_Sept (赞：1)

**CF1480** Codeforces Round #700 Sol [A](/blog/supervise/solution-cf1480a) / B / [C](/blog/supervise/solution-cf1479a)

### 分析

考虑开个结构体，排序方式：

```cpp
bool cmp(Node x, Node y){
	return x.a == y.a ? x.b < y.b : x.a < y.a;
}
```

先打血量小、攻击力小的怪物，再打其他的。

注意判断，注意细节。

判断分情况讨论：

- 当正在打的不是最后一个怪物时，若打完后血量 $\le0$ 则输出 `NO`。
- 当正在打的是最后一个怪物时，若打完后血量 $+a_n\le0$ 则输出 `NO`。
- 否则输出 `YES`。

### 代码

[$\text{Link}$](https://codeforces.com/contest/1480/submission/107684591)

---

