# The Game Of Parity

## 题目描述

There are $ n $ cities in Westeros. The $ i $ -th city is inhabited by $ a_{i} $ people. Daenerys and Stannis play the following game: in one single move, a player chooses a certain town and burns it to the ground. Thus all its residents, sadly, die. Stannis starts the game. The game ends when Westeros has exactly $ k $ cities left.

The prophecy says that if the total number of surviving residents is even, then Daenerys wins: Stannis gets beheaded, and Daenerys rises on the Iron Throne. If the total number of surviving residents is odd, Stannis wins and everything goes in the completely opposite way.

Lord Petyr Baelish wants to know which candidates to the throne he should support, and therefore he wonders, which one of them has a winning strategy. Answer to this question of Lord Baelish and maybe you will become the next Lord of Harrenholl.

## 说明/提示

In the first sample Stannis will use his move to burn a city with two people and Daenerys will be forced to burn a city with one resident. The only survivor city will have one resident left, that is, the total sum is odd, and thus Stannis wins.

In the second sample, if Stannis burns a city with two people, Daenerys burns the city with one resident, or vice versa. In any case, the last remaining city will be inhabited by two people, that is, the total sum is even, and hence Daenerys wins.

## 样例 #1

### 输入

```
3 1
1 2 1
```

### 输出

```
Stannis
```

## 样例 #2

### 输入

```
3 1
2 2 1
```

### 输出

```
Daenerys
```

## 样例 #3

### 输入

```
6 3
5 20 12 7 14 101
```

### 输出

```
Stannis
```

# 题解

## 作者：CASSINI_Thx (赞：2)

# Solution CF549C The Game Of Parity

[题目传送门]: https://www.luogu.com.cn/problem/CF549C

即将退役的蒟蒻的第一篇题解$QwQ$，如有不足请多包涵。



#### 题目大意：

有$n$个城市，每个城市有$a[i]$个人，两人轮流~~屠城~~对城市进行外科手术式的改造，若幸存者城市人口总数为奇数，那么先手胜，否则后手胜。



#### 分析：

题面虽然有亿点血腥，但透过”残忍“的表象我们不难看出这是一道博弈论。题目的关键在于最后幸存者城市人口总数的奇偶。



首先我们应该有一些算不上知识的前置芝士：

1.奇数*奇数=奇数

2.奇数*偶数=偶数

3.偶数*偶数=偶数

是的，这道题需要知道的就是这一点点众所周知的小学数学~~因为本蒟蒻太菜了只能做这种水题嚎啕大哭~~。



我们已知这道~~有手就行的~~题为博弈论，且决定胜负的关键为幸存者城市人口总数的奇偶，因而最后一次操作是谁就尤为重要。这里我们可以进行分类讨论。 

如若最后一次是先手~~屠城~~改造城市(即$m$为奇数)，我们易得：

1.剩下$k+1$个城市人口皆为偶数时，幸存者城市人口总数一定为偶数，后手必胜。

2.剩下$k+1$个城市人口皆为奇数时：

1)若$k$为奇数，幸存者城市人口总数一定为奇数，先手必胜。

2)若$k$为偶数，幸存者城市人口总数一定为偶数，后手必胜。

3.剩下$k+1$个城市人口有奇有偶时，

1)若先手摧毁一个人口为奇数的城市，幸存者城市人口总数一定为奇数，先手必胜。

2)若先手摧毁一个人口为偶数的城市，幸存者城市人口总数还是为奇数，先手必胜。

以上是最后一次为先手改造城市的情况，还是非常简单易懂的。接下来我们就可以类比着推出最后一次为后手改造城市(即$m$为偶数)的情况，如下：

1.剩下$k+1$个城市人口皆为偶数时，幸存者城市人口总数一定为偶数，后手必胜。

2.剩下$k+1$个城市人口皆为奇数时：

1)若$k$为奇数，幸存者城市人口总数一定为奇数，先手必胜。

2)若$k$为偶数，幸存者城市人口总数一定为偶数，后手必胜。

3.剩下$k+1$个城市人口有奇有偶时，

1)若此时城市人口为奇数，后手可以摧毁一个人口为奇数的城市，这样幸存者城市人口总数就变成了偶数，后手必胜。

2)若此时城市人口为偶数，后手可以摧毁一个人口为偶数的城市，这样幸存者城市人口总数也会变成偶数，后手必胜。

特别的，当$n==k$时，没有人有任何操作(城市保住了芜湖)，此时可按后手最后操作的情况来判。

我们可以在读入时顺便处理一下人口总数为奇数的城市数$odd$，人口总数为偶数的城市数$even$和操作数$m$，详见代码。



#### Code

接下来就是喜闻乐见的代码环节。(码风不好，见谅$QwQ$)

~~话说为啥那么多测试点啊喂~~

```cpp
#include<bits/stdc++.h>	//挚爱万能头 
#define re register int //小小优化（不过的确似乎没什么用
using namespace std;
int n,k,m;	//如题解所示 
int odd,even;
void xianshou()	//最后一次操作为先手的情况 
{
	if((m>>1)>=odd)
	{
		printf("Daenerys\n");
		return ;	//因为只有一组数据所以也可以直接exit(0) ,下同 
	} 
	if((m>>1)>=even && !(k&1)) 
	{
		printf("Daenerys\n");
		return ;
	}
    printf("Stannis\n");
}
void houshou()	//最后一次操作为后手的情况 
{
	if((m>>1)>=odd) 
	{
		printf("Daenerys\n");
		return ;
	}
    if((m>>1)>=even && (k&1)) 
    {
    	printf("Stannis\n");
    	return ; 
	} 
	printf("Daenerys\n");
}
inline int qr() //快读板子(其实这道题也不需要，只是个人习惯而已) 
{
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int pre()	//读入及其它预处理 
{
	n=qr(),k=qr();
	m=n-k;	//操作数的计算 
	for(re i=1;i<=n;i++)
	{
		int a=qr();
		if(a&1) odd++;
		else even++; 
	}	//统计人口总数为奇数的城市数和人口总数为偶数的城市数
} 
int main()
{
	pre();	//见上
	if(!m)	//没有操作的情况，可直接根据odd个数判断 
	{
		if(odd&1) printf("Stannis\n");
		else printf("Daenerys\n");
		return 0;
	}
	if(m&1) xianshou();	//见上
	else houshou();	//见上
	return 0;	
}
```

完结撒花~	预祝各位明天$NOIp$   $rp++$!

---

## 作者：233zhang (赞：1)

# 题意：



有 $n$ 个城市，第 $i$ 个城市住着 $a_{i}$ 个人。丹妮莉丝和史坦尼斯玩了下面的游戏：在一次移动中，玩家选择一个特定的城镇，并把它摧毁。由史坦尼斯开始比赛，当还剩下 $k$ 个城市时，游戏就结束了。如果幸存居民的总数是偶数，那么丹妮莉丝赢了，反之则史坦尼斯赢了。请问哪位候选人有获胜的策略。



# 思路：



最后剩下 $k$ 个城市，也就是说，我们要删去 $n-k$ 个城市，故史坦尼斯操作数为 $\lceil \frac{(n-k)}{2} \rceil$，丹妮莉丝的操作数为 $\lfloor \frac{(n-k)}{2} \rfloor$。

对于城市总人数，我们发现，人数为奇数的城市才是影响最终人数为奇还是偶的关键，因为删去偶数城市对人数的奇偶性没有变化。

我们很快想到，如果单数的城市数小于丹妮莉丝的操作数，也就是说，丹妮莉丝肯定可以将单数人数的城市删光，最后只会留下双数。此时。

当 $n-k$ 为奇数时，最后由史坦尼斯最后删城市，如果此时奇数城市和偶数城市均存在，那么史坦尼斯就可以确保最后总人数的奇偶数，那么丹妮莉丝该如何赢？我们不难发现，如果丹妮莉丝可以将所有偶数城市删去，即 $\lfloor \frac{(n-k)}{2} \rfloor$ 大于偶数城市数，并且 $k$ 为偶数时，丹妮莉丝才能赢。

$n-k$ 为偶数时与上类同。代码如下：

```c++
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N=5e6+5;
const int inf=0x3f3f3f;
const int mod=1e9+7;

int n,k,m,x,odd,even;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin>>n>>k;
    m=n-k;
    for (int i=1;i<=n;i++) {
        cin>>x;
        if (x&1) odd++;
        else even++;
    }
    if (m==0) {
        if (odd&1) cout<<"Stannis\n";
        else cout<<"Daenerys\n";
        return 0;
    }
    if ((m>>1)>=odd) {
        cout<<"Daenerys\n";return 0;
    }
    if (m&1) {
        if ((m>>1)>=even&&(!(k&1))) {cout<<"Daenerys\n";return 0;}
        cout<<"Stannis\n";
    }
    else {
        if ((m>>1)>=even&&(k&1)) {cout<<"Stannis\n";return 0;}
        cout<<"Daenerys\n";
    }


    return 0;
}
```

---

