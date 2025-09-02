# Sereja and Contests

## 题目描述

Sereja is a coder and he likes to take part in Codesorfes rounds. However, Uzhland doesn't have good internet connection, so Sereja sometimes skips rounds.

Codesorfes has rounds of two types: $ Div1 $ (for advanced coders) and $ Div2 $ (for beginner coders). Two rounds, $ Div1 $ and $ Div2 $ , can go simultaneously, ( $ Div1 $ round cannot be held without $ Div2 $ ) in all other cases the rounds don't overlap in time. Each round has a unique identifier — a positive integer. The rounds are sequentially (without gaps) numbered with identifiers by the starting time of the round. The identifiers of rounds that are run simultaneously are different by one, also the identifier of the $ Div1 $ round is always greater.

Sereja is a beginner coder, so he can take part only in rounds of $ Div2 $ type. At the moment he is taking part in a $ Div2 $ round, its identifier equals to $ x $ . Sereja remembers very well that he has taken part in exactly $ k $ rounds before this round. Also, he remembers all identifiers of the rounds he has taken part in and all identifiers of the rounds that went simultaneously with them. Sereja doesn't remember anything about the rounds he missed.

Sereja is wondering: what minimum and what maximum number of $ Div2 $ rounds could he have missed? Help him find these two numbers.

## 说明/提示

In the second sample we have unused identifiers of rounds 1, 6, 7. The minimum number of rounds Sereja could have missed equals to 2. In this case, the round with the identifier 1 will be a usual $ Div2 $ round and the round with identifier $ 6 $ will be synchronous with the $ Div1 $ round.

The maximum number of rounds equals $ 3 $ . In this case all unused identifiers belong to usual $ Div2 $ rounds.

## 样例 #1

### 输入

```
3 2
2 1
2 2
```

### 输出

```
0 0```

## 样例 #2

### 输入

```
9 3
1 2 3
2 8
1 4 5
```

### 输出

```
2 3```

## 样例 #3

### 输入

```
10 0
```

### 输出

```
5 9```

# 题解

## 作者：N_z_ (赞：2)

## 思路
最多的场数就是$1$到$n-1$的编号中没有记录的场次数。

最少的场数就是每连续两场未记录的场次记成一个$div1$和一个$div2$。

模拟即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool b[40000];
int main()
{
    int n,k;
    cin>>n>>k;
    for(int x=1;x<=k;x++)
    {
        int y;
        cin>>y;
        int o,p;
        if(y==2)cin>>o,b[o]=true;
        else cin>>o>>p,b[o]=b[p]=true;
    }
    int ans1=0;
    for(int x=1;x<n;x++)
    if(b[x]==false)ans1++;
    int ans2=ans1;
    for(int x=1;x<n;x++)
    if(b[x]==false&&b[x+1]==false&&x+1<n)ans2--,x++;
    cout<<ans2<<' '<<ans1<<endl;
}
```

---

## 作者：Camellia_Spoil (赞：0)

# 思路
根据我们的观察可知，错过最多的其实就是 $1$ 到 $n-1$ 中没参加的轮数，最少的就是在未参加过的中连续参加两场，一场为 div1，一场为 div2，这样就可以将 div2 的场数降到最少。

# AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 4010
#define ull unsigned long long
using namespace std;
inline long long read()
{
	long  long x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int vis[N];
int main(){
	int x,n;
	x=read();n=read();
	for(int i=1;i<=n;i++)
	{
		int op;
		op=read();
		if(op==1)
		{
			int a,b;
			a=read();b=read();
			vis[a]=vis[b]=1;
		}
		else 
		{
			int a;
			a=read();
			vis[a]=1;
		}
	}
	int len=0,mx=0,mi=0;
	for(int i=1;i<x;i++)
	{
		if(!vis[i])
		{
			len++;mx++;
		}
		else
		{
			mi+=len/2;
			if(len%2==1) mi++;
			len=0;
		}
	}
	if(len!=0)
	{
		mi+=len/2;
		if(len%2==1) mi++;
	}
	printf("%d %d",mi,mx);
	return 0;
}

```

---

## 作者：helongyun (赞：0)

这是一道模拟题，按照题目的意思，求最大错过比赛和最小错过比赛。
# 分析
- 要求最多的场数，实际上就是从为 $1$ 至 $n-1$ 中**没有**被记录的场次的数量。
- 要求最少的场数，实际上就是求连续两场比赛相邻编号差为 $1$ 的数量。

这里就不给代码了，按题意模拟即可。

---

## 作者：KevinHu0402 (赞：0)

这道题是一个小模拟题目，按照题目的要求，我们要从参加的比赛中算出**最少错过的比赛数**和**最多错过的比赛数**。然后就可以开始模拟。注意需要特判一些情况，这样某些测试点就无法把我们的代码卡掉。

代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 4005
int a[maxn];
int main(){
    int x,k;
    int num,a2,b2;
    while(cin >> x >> k){
        memset(a,0,sizeof(a));
        while(k--){
            cin >> num;
            if(num == 1){
                cin >> a2 >> b2;
                a[a2] = 1;a[b2] = 1;
            }
            else{
                cin >> a2;
                a[a2] = 1;
            }
        }
        a[0] = 1;a[x] = 1;
        int minn = 0,maxx = 0,x2 = 0;
        for(int i = 1;i <= x;i++){
            if(a[i]==0){
                x2++;
                maxx++;
            }
            else if(a[i] != 0){
                if(x2 % 2 == 0) minn += x2 / 2;
                else minn += (x2 / 2 + 1);
                x2 = 0;
            }
        }
        cout << minn << " " << maxx << endl;
    }
    return 0;
}
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述

Sereja 是一名程序员，他喜欢参加 Codesorfes 比赛。不过，乌兹兰的网络连接不太好，所以 Sereja 有时会跳过比赛。

Codesorfes 有两种类型的比赛，分为 Div1 和 Div2。 Div1 和 Div2 这两轮可以同时进行（Div1 轮不能在没有 Div2 的情况下进行）。每一轮都有一个唯一的标识符，各轮按开始时间顺序编号。同时运行的各轮标识符相差一个，而且 Div1 轮的标识符总是较大。

Sereja 是一名初学者，因此他只能参加 Div2 类型的比赛。此刻他正在参与 Div2 回合，其标识符为 $x$。Sereja 清楚地记得，在这一轮之前，他正好下过 $k$ 轮。此外，他还记得他参加过的各轮比赛的所有标识符，以及与它们同时进行的各轮比赛的所有标识符。Sereja 不记得他错过的任何一轮比赛。

Sereja 想知道他错过的 Div2 轮最少和最多会是多少？帮他找出这两个数字。

## 题目分析

可以先将这 $k+1$ 轮比赛排序，算出每两轮之间错过的场数，设为 $a$，如果要是最多，那么这 $a$ 轮都是 div2。要是最少的话，就要让 div1 和 div2 同时进行的场数尽可能多，即最多有 $\lfloor \frac{a}{2} \rfloor$ 轮，有可能 $a$ 是奇数，那么还要多一轮 div2，所以最少的场数就是 $\lfloor \frac{a}{2} \rfloor+a \bmod 2$，累加即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define random(a,b) (rand()%(b-a+1)+a)
#define se second
#define fi first
#define pr pair<int,int>
#define pb push_back
#define ph push
#define ft front
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
#define mem(a,b) memset(a,b,sizeof a)
const int N=4100;
int x,k,opt,ans1,ans2;
pr a[N];
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>x>>k;
    For(i,1,k)
    {
    	cin>>opt;
		if(opt==2)
		{
			cin>>a[i].fi;
			a[i].se=a[i].fi;
		}
		else
		{
			cin>>a[i].fi>>a[i].se;
		}
	}
	a[k+1].fi=x;
	sort(a+1,a+1+k);
	For(i,1,k+1)
	{
		int temp=a[i].fi-a[i-1].se-1;
		ans1+=temp/2+(temp%2);
		ans2+=temp;
	}
	cout<<ans1<<" "<<ans2;
	return 0;
}
```

---

## 作者：_int123_ (赞：0)

## 题意：

输入 $n$，$x$，表示你现在正在参加的比赛和你参加了几场比赛，求你最少和最多错过参加的比赛数。

## 思路：

这个题目我们可以先模拟一下，不难发现：

1. 最多的场数其实就是编号为 $1$ 至 $n-1$ 中没有被记录的场次的数量，即 $a_i$ 为 $0$ 的数量。

2. 最少的场数就是连续两场相邻编号数差 $1$ 的数量。

## AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件
int n,k,b,c,d,t1;
int a[4005];
using namespace std;
int main()
{
	scanf("%d%d",&n,&k);//输入
    memset(a,0,sizeof(a));//初始化
    for(int i=0;i<k;i++)
    {
        cin>>b;
        if(b==2) cin>>t1,a[t1]=1;//只有 div2
        else cin>>c>>d,a[c]=a[d]=1;//div1 和 div2 都有
    }
    int anss=0,t=0;
    for(int i=1;i<n;i++)//求编号为 1 至 n-1 中没有被记录的场次的数量
        if(a[i]==0)
			ans[t]=i,t++;//这样让后面好判断
    for(int i=0;i<t;i++)//判有哪两个相邻编号数差 1 的
    {
        if((ans[i+1]-ans[i])==1) i++;//下一个判过了，i++，判下下个
        anss++;
    }
    cout<<anss<<" "<<t;//输出
    return 0;
}
```

完结撒花！！！

---

