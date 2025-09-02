# Fight with Monsters

## 题目描述

There are $ n $ monsters standing in a row numbered from $ 1 $ to $ n $ . The $ i $ -th monster has $ h_i $ health points (hp). You have your attack power equal to $ a $ hp and your opponent has his attack power equal to $ b $ hp.

You and your opponent are fighting these monsters. Firstly, you and your opponent go to the first monster and fight it till his death, then you and your opponent go the second monster and fight it till his death, and so on. A monster is considered dead if its hp is less than or equal to $ 0 $ .

The fight with a monster happens in turns.

1. You hit the monster by $ a $ hp. If it is dead after your hit, you gain one point and you both proceed to the next monster.
2. Your opponent hits the monster by $ b $ hp. If it is dead after his hit, nobody gains a point and you both proceed to the next monster.

You have some secret technique to force your opponent to skip his turn. You can use this technique at most $ k $ times in total (for example, if there are two monsters and $ k=4 $ , then you can use the technique $ 2 $ times on the first monster and $ 1 $ time on the second monster, but not $ 2 $ times on the first monster and $ 3 $ times on the second monster).

Your task is to determine the maximum number of points you can gain if you use the secret technique optimally.

## 样例 #1

### 输入

```
6 2 3 3
7 10 50 12 1 8```

### 输出

```
5```

## 样例 #2

### 输入

```
1 1 100 99
100```

### 输出

```
1```

## 样例 #3

### 输入

```
7 4 2 1
1 3 5 4 2 7 6```

### 输出

```
6```

# 题解

## 作者：_6_awa (赞：5)

题目大意：有 $n$ 怪兽血量为 $h_i$，你的攻击力为 $a$，对面为 $b$。两人轮流打怪，如果你打死了怪则获得一分，你有 $k$ 次机会跳过敌方的回合，问你最多能获得多少分。

思路分析：我们可以先判断每个怪需要多少次机会才能获得一分。先将敌人的血量对 $(a + b)$ 取模（求剩余的零头）。如果取模后的结果 $\le a$，则说明你最后打死了怪，不用机会也能赢；否则你需要对剩余的血量 $- a$ 点进行跳过，共需要击打 $\left\lceil (h_i - a_i)\;/\;a_i\right\rceil$ 次（注意此时 $h_i$ 已经取模）。最后进行贪心排序，直接取用的最小机会即可。

附代码：

```cpp
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int n,a,b,c[255677],k,w,d[255677],sum;
int main()
{
    cin >> n >> a >> b >> k;
    for(int i = 1;i <= n;i ++)
    {
        cin >> c[i];
        int p = c[i] % (a + b);//先取模
        if(p == 0)p = a + b;//这里将0转换为a+b
        if(p <= a)d[i] = 0;
        else d[i] = ceil((p - a) / (double)a);//计算需要的次数
    }
    sort(d + 1,d + n + 1);//排序
    for(int i = 1;i <= n;i ++)
    {
        if(sum + d[i] > k)
        {
            cout << i - 1;//没机会直接跳出
            return 0;
        }
        sum += d[i];
    }
    cout << n;//还剩余直接输出
}
```

---

## 作者：Yizhixiaoyun (赞：4)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/17109226.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1296D)


简单题做了好久，哈哈。

## 题目分析

首先，对于单个怪物，先将它的血量通过取余处理到小于 $a+b$ 的时候，因为无论怪物血量多少，如果大于 $a+b$，显然不可能出现最后一击。

设余数为 $m$，在不用特殊能力的情况下就只能击杀 $m \le a$ 且 $m$ 不为 $0$ 的怪物。

然后枚举对于每一个怪物，如果想要击杀它需要耗费多少次特殊能力。由于每一个怪物的贡献都为 $1$，因此直接从小往大取即可。

时间复杂度：$O(n \log n)$。

## 贴上代码

```cpp
#include<bits/stdc++.h>
// #define int long long
#define debug puts("Shiina_Mashiro_kawaii")
#define ok puts("T")
#define no puts("F")
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int maxn=2e5+5;
int n,a,b,k;
int ans;
int h[maxn];
inline void init(){
	n=read();a=read();b=read();k=read();
	for(register int i=1;i<=n;++i) h[i]=read()-1;
	for(register int i=1;i<=n;++i){
		h[i]%=a+b;h[i]/=a;
	}
	sort(h+1,h+n+1);
}
int main(){
	init();
	for(register int i=1;i<=n;++i){
		if(h[i]<=k){
			ans++;k-=h[i];
		}
	}
	printf("%d",ans);
}
```

---

## 作者：幻之陨梦 (赞：4)

$\textbf{解题思路：}$首先我们不难发现这道题其实就是一道贪心+排序的题。但是如何贪心呢？我首先想到的是将每个怪物的生命值取余 $a+b$ 然后在拿一个数组记录每个怪物需要用几次特殊的手段，最后再循环判断累加即可。但是这里出现了一个问题，如果一个怪物的生命值刚好取余 $a+b=0$ 那该怎么办？想了好久，我终于想到了一种办法，在每次取余的时候，将那个怪物的生命值减去 $1$ 再取余。用这样的方法就可以 $AC$ 了。

**AC code:**
```cpp
#include<bits/stdc++.h>
//这次用了万能头文件，因为不只有cstdio了(大雾弥漫）
using namespace std;
inline int read()//快速读入
{
    int x=0,k=1;char c=getchar();
    while(c<'0' || c>'9'){if(c=='-') k=0;c=getchar();}
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return k?x:-x;
}
int n,a,b,k,x,cost[200010],ans;
//cost 数组就是记录该怪物需要用多少次特殊的手段才能让自己得分
int main()
{
    n=read(),a=read(),b=read(),k=read();//输入
    for(int i=0;i<n;i++)
    {
        x=read();//输入每个怪物的生命值
        x=(x-1)%(a+b);//用上述方法取余 a+b
        cost[i]=x/a;//记录次数
    }
    sort(cost,cost+n);//将次数排序，从小到大依次判断
    for(int i=0;i<n;i++)
    {
        k-=cost[i];
        //将可以使用特殊手段的次数减去当前怪物需要用的次数
        if(k<0) break;
        //如果小于 0 就说明这个怪物你打不死了，所以直接跳出循环
        ans++;//计数器++
    }
    printf("%d",ans);//输出
    return 0;
}
```

---

## 作者：Priori_Incantatem (赞：3)

题目：[Link](https://www.luogu.com.cn/problem/CF1296D)

~~同样是1500，为什么这比C题还水......~~ 直接 贪心+排序

对于不用特殊操作可以自己打死的怪兽，直接计入答案  
对于剩下的，我们求出每一个怪兽需要多少次特殊操作，才能得到分 ~~抢到人头~~ 。并将这些次数排序，最后用贪心的方法选次数最小的怪兽即可

下面讲一下怎样判断是否能直接得到分（不用特殊操作）

首先，我们把两人轮流攻击一次当成一个循环，这一次循环造成的伤害为 $a+b$。  
当怪兽的健康值小于 $a+b$ 时，说明即将要决出胜负（得不得分）了。所以，计算时先将怪兽健康值 $h_i \bmod (a+b)$

接下来：若 $h_i=0$ 或 $h_i>a$，说明怪兽会被对手打死  
否则，将会被自己打死

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int Maxn=200000+10,inf=0x3f3f3f3f;
int a[Maxn];
int n,x,y,k,ans,cnt;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),x=read(),y=read(),k=read();
	
	for(int i=1;i<=n;++i)
	{
		int cur=read();
		cur%=(x+y);
		if(!cur)cur=x+y;
		if(cur<=x)++ans;
		else
		{
			cur-=x;
			a[++cnt]=cur/x;
			if(cur%x)++a[cnt]; // 求出需要用多少次特殊操作
		}
	}
	n=cnt;
	sort(a+1,a+1+n);
	for(int i=1;i<=n;++i) // 贪心
	{
		if(k>=a[i])++ans,k-=a[i];
		else break;
	}
	printf("%d\n",ans);
	
	return 0;
}
```

---

## 作者：123456zmy (赞：2)

~~抢人头~~

计算出每个怪需要跳过几次~~才抢到人头~~，排序后贪心，计算方式在代码里有。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,k,h,ans1[200001],ans;
int main()
{
	scanf("%d%d%d%d",&n,&a,&b,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&h);
		h=(h-1)%(a+b)+1-a;
		ans1[i]=(h+a-1)/a;
	}
	sort(ans1,ans1+n+1);
	for(int i=1;i<=n;i++)
	{
		k-=ans1[i];
		if(k<0)break;
		++ans;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：万物一 (赞：1)

题目大意是：你和你的对手一起打小怪兽，$n$个小怪兽排成一排且各自有自己的血量，你和你的对手攻击力分别是$a$和$b$，回合制打怪兽，你先打然后轮到对手然后又轮到你以此类推，你和你的对手每打一下小怪兽会扣除攻击者攻击力的生命，如果最后你打死了怪兽你就能得到一分，如果对手打死了怪兽则你不得分(题目要求按顺序打怪兽)

并且作为一名科学家，你拥有一些特殊的科(外)技(挂),你的科技可以使用$k$次，每一次使用的可以跳过你对手的一个回合，现在问你你最多可以的多少分。

看到题目就想到贪心，首先打死每个怪物对得分的贡献都是1，假设打死第i个怪物你需要开挂 $h_i$ 次肯定是从$h_i$小的往大的打

其中(hp为怪物的血量)
$$
h_i = \lceil\frac{hp_i \mod (a+ b)}{a}\rceil - 1
$$
代码就很好写了

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 2e5 + 10;

int h[maxn];

int main() {
    int n, a, b, k;
    cin >> n >> a >> b >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
        h[i] %= a + b;
        if(h[i] == 0) h[i] = a + b;
        h[i] = int(h[i] / a) + (h[i] % a != 0) - 1;
    }
    sort(h + 1, h + 1 + n);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if(k - h[i] < 0) break;
        k -= h[i];
        ++ans;
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：pigstd (赞：1)

注意：**对于每一个怪兽，你都是第1个开始攻击的。**

所以我们只要算出对于每一个怪，如果想要得分需要用“某种能力”多少次，然后贪心就好啦（方法在注释里）。

c++代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=1e6+5;
int l[M],n,ans,k,a,b,sum;

int main()
{
	scanf("%d%d%d%d",&n,&a,&b,&k);
	for (int i=1;i<=n;i++)
	{
		int h;
		scanf("%d",&h);
		h=h%(a+b);//首先，让他们轮流攻击
		if (h==0)
			h=a+b;
		if (h%a==0)//如果剩下的血量是a的倍数，那么使用h/a-1次就可以了（想不懂的人可以自己举例子）
			l[i]=h/a-1;
		else//如果剩下的血量不是a的倍数，那么要使用h/a-1+1次，即h/a次（想不懂的人还是可以自己举例子）
			l[i]=h/a;
	}
	sort(l+1,l+1+n);//排序，贪心
	for (int i=1;i<=n;i++)
	{
		if (sum+l[i]>k)//sum为当前使用的次数
			break;
		sum+=l[i],ans++;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：HDZmessi (赞：0)

赤裸裸的贪心排序没有任何技巧！！！

首先不难想到，要让分尽量多，就要让被自己终结的怪物尽量多，遇到不能被自己终结的怪物，就要使用“某种办法”，但 $k$ 本来就不多，所以就要自己和敌人轮流打怪，最后再使用“某种办法”使自己每个怪物都被自己终结；简而言之意思就是不到迫不得已就不使用“某种办法”，这是这道题的核心思想。

这道题分几个步骤：

## step 1

首先算出最节省的情况下每个怪物花费的时间。每次让怪物的血量对自己和敌人的伤害量取余，剩下的如果是零，则更新为自己和敌人的血量之和。接下来如果现在剩下来的对自己的伤害取余为零，数组中存入剩下数字除以自己伤害减一，否则把除以自己伤害向下取整加入数组。

## step 2
接着排序，就是贪心，不细讲。

## step 3
最后遍历数组，每次答案加一，累加器加数组每一项，直到累加器大于 $k$ 输出答案！


AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,a,b,k,c[200005],len;
int main(){
	cin>>n>>a>>b>>k;
	for(int i=1;i<=n;i++){
		cin>>x;
		int f=x%(a+b);
		f= f==0?a+b:f;
		c[++len]=f%a==0?f/a-1:f/a;
	}
	sort(c+1,c+len+1);
	int ans=0,num=0;
	for(int i=1;i<=len;i++){
		if(num+c[i]>k){
			cout<<ans;
			return 0; 
		}
		num+=c[i],ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```
语文不好，不注释了。

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1296D)    
本来想复杂了（       
## 题意
两个人打怪，先手伤害是 $a$，后手伤害是 $b$。共有 $n$ 个怪，第 $i$ 个怪血量为 $h_i$。       
打怪按照“先手先打，后手后打”的方式进行循环，当一个怪最后一个攻击是先手打出时，先手积分增加 $1$。    
现在可以跳过后手攻击 $k$ 次，求先手最多能获得多少积分。    
## 解法
显然，只有最后一轮攻击是对答案有贡献的。     
那么我们用最后一轮攻击算出先手击败每个怪需跳跃多少次后手攻击，再贪心地从小到大排序，用 $k$ 扫一遍即可。      
我们扫的时候每次都要减掉跳跃次数并将结果加一，如果不够减了就直接输出结果。    
接下来说如何求出跳跃次数：        
一轮攻击可以造成 $a+b$ 的伤害，因此我们把所有的 $h_i$ 模上这个值，结果就是我们实际需要处理的。    
我们设这个值为 $t$，明显，我们想要击败这个怪需要 $\left\lfloor\dfrac{t}{a}\right\rfloor$ 次跳跃。     
但是我们发现一个问题：如果 $t\le a$，那么次数应该都是 $0$（其实还有很多类似的问题）。   
这个问题想解决也很简单，这里先给出结论：我们输入时把所有的 $h_i$ 减一即可。     
为什么这是对的呢？    
- 首先如果是 $t=0$ 的情况，减一后 $t=a+b-1$，代入原式为 $\left\lfloor\dfrac{a+b-1}{a}\right\rfloor$，这明显是正确的。   
- 如果 $t\le a$，那么减一后 $t<a$，代入原式，也是正确的。    
- 如果 $t>a$，那么减一后 $t\ge a$，因为 $a\ne0$ 且 $t\ne0$ 的原因，这里的 $t$ 一定大于 $1$。那么有了这些条件，就可以得出：减一后可以使答案正确。      

[CODE](https://www.luogu.com.cn/paste/h08wi8e1)

---

## 作者：Fan_Tuan (赞：0)

# 题意
$n$只怪兽，对应血量为$h_i$,你的攻击伤害为$a$, 你对手的攻击伤害为$b$, 你和你的对手轮流攻击怪兽，谁将怪兽打死，谁得一分。现在你有$k$次机会，使用一次，可让对手暂停一回合，求你的最大得分。
# 思路
要使得分最大的话，就要使你每得一分所消耗的次数尽量少，所以我们可以算出每只怪兽你打死所需要的最少次数，然后求$ans$即可。

那么怎么求最小次数呢？你可以用$h_i$对$(a + b)$ 取mod。

**对于$mod\ne0$的情况：**

$\mathit{1}.$ 如果$mod$是$a$的一倍或者不足$a$的一倍，那么这只怪兽所需要的最少次数为$0$；（因为当前轮到$a$攻击）

$\mathit{2}.$如果$mod$是$a$的整数倍，那么最少次数为$mod / a$;

$\mathit{3}.$若以上条件都不成立， 那么最少次数为$mod/a - 1$;

**对于$mod = 0$的情况：**

$\mathit{1}.$如果$a \geqslant b$ 那么最少次数为$1$; （只需将$b$的最后一次攻击推迟）

$\mathit{2}.$如果$a < b$且$b$是$a$的整数倍，最小次数为$b/a$, 否则为$b/a + 1$。

把每个$h_i$ 的最小次数扔优队里，求$ans$就行了。

# 代码
```c
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

const int maxn = 2e5 + 10;
int n, a, b, k;

priority_queue<int, vector<int>, greater<int> > q;

signed main () {
    scanf("%d%d%d%d", &n, &a, &b, &k);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        if (x % (a + b) == 0) {
            if (a >= b) q.push(1);
            else {
                if (b % a != 0) q.push(b / a + 1);
                else q.push(b / a);
            }
        }
        else {
            int mod = x % (a + b);
            int sum = mod / a;
            mod %= a;
            if (sum == 1 && mod == 0) q.push(0);
            else if (sum == 0) q.push(0);
            else if (mod != 0) q.push(sum);
            else q.push(sum - 1);
        }
    }
    int ans = 0;
    while (!q.empty()) {
        int p = q.top();
        q.pop();
        if (k - p >= 0) k -= p, ans++;
        else break;
    }
    printf ("%d", ans);
    return 0;
}
```


---

## 作者：jscblack (赞：0)

简单的贪心处理，排个序即可。

显然每一个怪物的击杀是由自己和队友所交替攻击完成的（如果不使用~~黑魔法~~的话）

而如果我们想要去确保一个怪物能够被自己杀掉而非队友，就需要在队友补最后一刀前提前去将怪物击杀。显然每一轮次的攻击力为二者总和。对其取余我们就可以得到最后一轮次的血量情况，此时我a一刀+队友a一刀都会使得怪物死亡，且如果队友a出来了那人头就是队友的了（~~队友k头石锤~~）

所以我们通过多次使用黑魔法将攻击的主动权放在自己手上即可保证这个人头是自己的。而正确的贪心策略就体现在优先使用最少次的黑魔法上

**优先找到需要更少次需要~~黑魔法~~就可以使我得到这一分的怪**（包括**0**次）。

注释当中对关键步骤有解释↓

```cpp
/*
 * @Author: Gehrychiang
 * @Date: 2020-02-04 21:39:16
 * @Website: www.yilantingfeng.site
 * @E-mail: gehrychiang@aliyun.com
 */
#include <bits/stdc++.h>
using namespace std;
int monster[200005];
int main()
{
    int n; //怪物总数
    int a; //我的攻击力
    int b; //队友攻击力
    int k; //可跳过回合次数
    cin >> n >> a >> b >> k;
    int tol_atk = a + b;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        tmp %= tol_atk;//获取最后一轮的剩余血量
        if (tmp == 0)
        {
            tmp = tol_atk;
        }
        monster[i] = tmp;
    }
    sort(monster, monster + n);
    int point = 0;
    for (int i = 0; i < n; i++)
    {
        if (k >= 1)
        {
            k -= (ceil((double)monster[i] / a) - 1);//减去需要跳过的次数
            point++;
            if (k < 0)//边际条件
            {
                point--;
                break;
            }
        }
    }
    cout << point << endl;
    return 0;
}
```


---

## 作者：GIFBMP (赞：0)

我们把 $a+b$ 看成一个循环，将所有的怪物的生命值对其取模。

当 $h_i\equiv0 \ (\bmod {\ a+b})$ 时，我们令其等于 $a+b$。

计算需要用多少次特殊能力，排序后贪心即可。

Code:

```cpp
#include <cstdio>
#include <algorithm>
using namespace std ;
const int MAXN = 2e5 + 10 ;
int n , a , b , k , h[MAXN] , f[MAXN] , ans , cnt ;
int main () {
	scanf ("%d %d %d %d" , &n , &a , &b , &k) ;
	for (int i = 1 ; i <= n ; i++) {
		scanf ("%d" , &h[i]) ;
		h[i] %= (a + b) ;
		if (!h[i]) h[i] = a + b ;
		if (h[i] <= a) {
			ans++ ;
			continue ;
		}
		h[i] -= a ; f[++cnt] = h[i] / a ; h[i] %= a ;
		if (h[i]) f[cnt]++ ;
	}
	sort (f + 1 , f + cnt + 1) ;
	for (int i = 1 ; i <= cnt ; i++)
		if (k - f[i] >= 0) {
			k -= f[i] ;
			ans++ ;
		}
	printf ("%d" , ans) ;
	return 0 ;
}
```

---

